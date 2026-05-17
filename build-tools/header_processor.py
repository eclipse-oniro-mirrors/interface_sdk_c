#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2025 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
import sys
import re
import shutil
import json
import subprocess
import tempfile
import argparse
import time
from pathlib import Path
from typing import List, Tuple, Optional, Dict, Any, Set
import logging


class SystemApiRemover:
    # 需要检查的 AST 节点类型：
    # FunctionDecl   — 函数声明
    # TypedefDecl    — typedef（函数指针、前向声明、struct/enum typedef）
    # EnumDecl       — 裸 enum 定义
    # RecordDecl     — 裸 struct 定义（C 模式）
    # CXXRecordDecl  — 裸 struct/class 定义（C++ 模式）
    # VarDecl        — 全局变量声明
    SYSTEMAPI_NODE_KINDS = {'FunctionDecl', 'TypedefDecl', 'EnumDecl', 'RecordDecl', 'CXXRecordDecl', 'VarDecl'}



    def __init__(self, input_dir: str, output_dir: str, napi_dir: Optional[str] = None,
                 verbose: bool = False, log_file: Optional[str] = None,
                 force_regex: bool = False):
        self.start_time = time.time()
        self.input_dir = Path(input_dir).resolve()
        self.output_dir = Path(output_dir).resolve()
        self.napi_dir = Path(napi_dir).resolve() if napi_dir else None
        self.force_regex = force_regex

        self._init_stats()

        self.verbose = verbose

        # 日志配置：控制台输出 INFO 级别，verbose 模式下文件记录 DEBUG 级别
        log_level = logging.DEBUG if verbose else logging.INFO
        self.logger = logging.getLogger(__name__)
        self.logger.setLevel(log_level)
        self.logger.handlers.clear()

        formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')

        console_handler = logging.StreamHandler(sys.stdout)
        console_handler.setLevel(logging.INFO)
        console_handler.setFormatter(formatter)
        self.logger.addHandler(console_handler)

        if log_file:
            try:
                log_path = Path(log_file)
                log_path.parent.mkdir(parents=True, exist_ok=True)
                file_handler = logging.FileHandler(log_path, encoding='utf-8')
                file_handler.setLevel(log_level)
                file_handler.setFormatter(formatter)
                self.logger.addHandler(file_handler)
                self.logger.info(f"Logging to file: {log_path.absolute()}")
            except Exception as e:
                self.logger.warning(f"Failed to create log file {log_file}: {e}")

        # 启动时检查 clang 是否可用
        self.check_clang()


    def _build_clang_command(self, include_paths: List[str], fake_include_dir: Path) -> List[str]:
        compile_args = [
            '-x', 'c++-header',
            '-std=c++11',
            '-Dbool=_Bool',
            '-Dtrue=1',
            '-Dfalse=0',
            '-D__bool_true_false_are_defined=1',
            '-D__STDC_VERSION__=199901L',
            '-D__cplusplus=201103L',
            '-D_GNU_SOURCE',
            '-D_POSIX_C_SOURCE=200809L',
            '-D_Bool=bool',
            '-Wno-unknown-attributes',
            '-Wno-pragma-pack',
            '-Wno-ignored-attributes',
            '-Wno-deprecated-declarations',
            '-Wno-typedef-redefinition',
            '-Wno-incomplete-umbrella',
            '-Wno-implicit-function-declaration',
            '-Wno-c++11-compat',
            '-Wno-unknown-pragmas',
            '-Wno-unused-parameter',
            '-Wno-missing-field-initializers',
            '-Wno-initializer-overrides',
            '-Wno-builtin-requires-header',
            '-Wno-incompatible-pointer-types',
            '-Wno-int-conversion',
            '-Wno-implicit-int',
            '-Wno-nullability-completeness',
            '-Wno-everything',
            '-ferror-limit=0',
            '-fms-compatibility',
            '-fallow-editor-placeholders',
            '-fdelayed-template-parsing',
            '-target', 'x86_64-linux-gnu',
        ]
        compile_args.extend(include_paths)
        compile_args.append(f"-I{fake_include_dir}")
        return compile_args


    def _check_and_collect_node(self, node: Dict[str, Any], source_lines: List[str],
                                source_text: str, node_kind: str,
                                to_remove: List[Tuple[int, int, str]]) -> bool:
        """检查单个 AST 节点是否匹配 @systemapi，若匹配则添加删除范围。返回是否匹配"""
        if node_kind not in self.SYSTEMAPI_NODE_KINDS or not self._is_from_main_file(node):
            return False

        node_name = node.get('name', 'unknown') or node_kind
        self.stats['functions_found'] += 1
        comment = self.extract_comment_before_node(node, source_lines, node_name, source_text)

        if not self.has_systemapi_tag(comment):
            return False

        self.stats['functions_with_systemapi'] += 1
        if self.verbose:
            self.logger.debug(f"  Found @systemapi in {node_kind} {node_name}")

        start_line, end_line = self.get_node_location(node, source_text, source_lines)
        if not start_line or not end_line:
            self.logger.debug(f"    Skipping {node_name}: no location info")
            return False

        comment_start_line = start_line
        line_num = start_line - 2
        found_comment = False
        while line_num >= 0 and line_num < len(source_lines):
            line = source_lines[line_num].strip()
            is_comment = (line.startswith('//') or line.startswith('/*') or
                          line.startswith('/**') or line.startswith('/*!') or
                          '*/' in line or
                          (line.startswith('*') and not line.startswith('*/')))
            if is_comment:
                found_comment = True
                comment_start_line = line_num + 1
                line_num -= 1
                continue
            if line == '' and not found_comment:
                comment_start_line = line_num + 1
                line_num -= 1
                continue
            break

        to_remove.append((comment_start_line, end_line, node_name))
        return True


    def _check_macro_comment(self, lines: List[str], start: int) -> Optional[Tuple[int, int]]:
        """检查注释块后是否跟 #define 宏，返回 (comment_start, decl_end) 或 None"""
        comment_content = []
        comment_end = start
        while comment_end < len(lines):
            comment_content.append(lines[comment_end])
            if '*/' in lines[comment_end]:
                comment_end += 1
                break
            comment_end += 1
        comment_text = '\n'.join(comment_content)
        if not self._has_strict_systemapi(comment_text):
            return None
        j = comment_end
        while j < len(lines) and lines[j].strip() == '':
            j += 1
        if j >= len(lines) or not re.match(r'#\s*define', lines[j].strip()):
            return None
        actual_start = self._find_contiguous_comment_start(lines, start)
        decl_end = j
        for k2 in range(j, len(lines)):
            decl_end = k2
            if not lines[k2].rstrip().endswith('\\'):
                break
        return (actual_start, decl_end)

    @staticmethod
    @staticmethod
    def _find_block_comment_open(lines: List[str], close_line: int) -> Optional[int]:
        """从块注释结尾行向上查找对应的 /* 开头行，返回行号或 None"""
        bk = close_line - 1
        while bk >= 0:
            bs = lines[bk].strip()
            if bs.startswith('/*') or bs.startswith('/**') or bs.startswith('/*!'):
                return bk
            if bs.startswith('*') or bs.endswith('*/'):
                bk -= 1
                continue
            return None
        return None

    @staticmethod
    def _find_contiguous_comment_start(lines: List[str], start: int) -> int:
        """从含 @systemapi 的注释块起始行向上回溯，找到紧贴的连续注释块的最早起始行"""
        actual_start = start
        k = start - 1
        while k >= 0:
            s = lines[k].strip()
            if s == '':
                break
            if s.endswith('*/'):
                open_line = SystemApiRemover._find_block_comment_open(lines, k)
                if open_line is not None:
                    actual_start = open_line
                    k = open_line - 1
                else:
                    break
            elif s.startswith('*'):
                actual_start = k
                k -= 1
            else:
                break
        return actual_start


    @staticmethod
    def _classify_comment_line(stripped: str, found_comment: bool,
                               comment_style: Optional[str] = None) -> Tuple[str, bool, Optional[str]]:
        """分类一行源码，返回 (动作, 更新后的 found_comment, 更新后的 comment_style)。
        动作: 'insert'=插入并继续, 'insert_stop'=插入并停止,
              'stop'=停止, 'skip'=跳过并继续
        comment_style: 追踪当前注释风格 ('block' 或 'line')，防止跨风格收集
        """
        if stripped.startswith('//'):
            if comment_style == 'block':
                return 'stop', found_comment, comment_style
            return 'insert', True, 'line'
        if '*/' in stripped:
            if comment_style == 'line':
                return 'stop', found_comment, comment_style
            return 'insert', True, 'block'
        if stripped.startswith('*') and not stripped.startswith('/*') and not stripped.startswith('/**'):
            return 'insert', found_comment, comment_style
        if stripped.startswith('/**') or stripped.startswith('/*') or stripped.startswith('/*!'):
            if comment_style == 'line':
                return 'stop', found_comment, comment_style
            return 'insert_stop', True, 'block'
        if stripped == '' and found_comment:
            return 'insert', found_comment, comment_style
        if stripped == '':
            return 'skip', found_comment, comment_style
        if found_comment:
            return 'stop', found_comment, comment_style
        return 'stop', found_comment, comment_style


    SKIP_DIR_NAMES = {'third_party'}

    def _collect_header_files(self) -> List[Path]:
        """收集输入目录中所有头文件"""
        all_header_files = []
        for root, dirs, files in os.walk(self.input_dir):
            dirs[:] = [d for d in dirs if d not in self.SKIP_DIR_NAMES]
            root_path = Path(root)
            for file in files:
                file_path = root_path / file
                if self.is_header_file(file_path):
                    all_header_files.append(file_path)
        return all_header_files


    def _collect_missing_headers(self, compile_args: List[str],
                                 input_file: Path) -> Set[str]:
        """预处理头文件，收集所有 'file not found' 的缺失头文件名"""
        preprocess_cmd = [self.clang_binary, '-E'] + compile_args + [str(input_file)]
        preprocess_result = subprocess.run(preprocess_cmd, capture_output=True)
        preprocess_result.stdout = preprocess_result.stdout.decode('utf-8', errors='replace')
        preprocess_result.stderr = preprocess_result.stderr.decode('utf-8', errors='replace')
        missing_headers = set()
        if preprocess_result.stderr:
            matches = re.findall(r"'(.*?)' file not found", preprocess_result.stderr)
            for match in matches:
                missing_headers.add(match)
        return missing_headers


    def _collect_output_headers(self) -> List[Path]:
        """收集输出目录中所有头文件"""
        output_headers = []
        for root, dirs, files in os.walk(self.output_dir):
            root_path = Path(root)
            for file in files:
                file_path = root_path / file
                if self.is_header_file(file_path):
                    output_headers.append(file_path)
        return output_headers


    def _copy_non_header_files(self) -> None:
        """将非头文件直接拷贝到输出目录（保持目录结构）"""
        for root, dirs, files in os.walk(self.input_dir):
            dirs[:] = [d for d in dirs if d not in self.SKIP_DIR_NAMES]
            root_path = Path(root)
            rel_path = root_path.relative_to(self.input_dir)
            output_root = self.output_dir / rel_path
            for file in files:
                file_path = root_path / file
                self.stats['total_files_scanned'] += 1
                if not self.is_header_file(file_path):
                    self.stats['non_header_files'] += 1
                    output_file = output_root / file
                    output_file.parent.mkdir(parents=True, exist_ok=True)
                    shutil.copy2(file_path, output_file)


    def _create_basic_fake_headers(self, fake_include_dir: Path) -> None:
        """为基础系统头文件（stddef.h 等）创建 fake header"""
        basic_headers = ['stddef.h', 'stdint.h', 'stdbool.h', 'stdarg.h', 'limits.h']
        for header in basic_headers:
            fake_file = fake_include_dir / header
            if not fake_file.exists():
                self.create_fake_header(header, fake_include_dir)


    @staticmethod
    def _extract_enum_and_struct_names(content: str) -> Set[str]:
        """从内容中提取所有 enum 和 struct 标签名"""
        symbols = set()
        for m in re.finditer(r'\benum\s+(\w+)\s*\{', content):
            symbols.add(m.group(1))
        for m in re.finditer(r'\bstruct\s+(\w+)\s*\{', content):
            symbols.add(m.group(1))
        for m in re.finditer(r'\bstruct\s+(\w+)\s*;', content):
            symbols.add(m.group(1))
        return symbols


    def _extract_exported_symbols(self, header_path: Path) -> Set[str]:
        """从头文件中提取所有导出的符号名，用于判断 #include 是否仍被需要。
        提取：typedef 名、enum 标签、struct 标签、函数名、全大写宏名。"""
        symbols = set()
        try:
            with open(header_path, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
        except Exception:
            return symbols

        symbols |= self._extract_typedef_names(content)
        symbols |= self._extract_enum_and_struct_names(content)
        symbols |= self._extract_function_names(content)
        symbols |= self._extract_macro_names(content)

        symbols = {s for s in symbols if s not in ('Copyright', 'License', 'NULL')}
        return symbols


    @staticmethod
    def _extract_function_names(content: str) -> Set[str]:
        """从内容中提取所有函数名（排除 C 语言关键字）"""
        keywords = ('if', 'for', 'while', 'switch', 'return', 'sizeof')
        symbols = set()
        for m in re.finditer(r'^\s*(?:extern\s+)?[\w\s\*]+?\s+(\w+)\s*\(', content, re.MULTILINE):
            name = m.group(1)
            if name not in keywords:
                symbols.add(name)
        return symbols


    def _extract_local_includes(self, lines: List[str]) -> List[Tuple[int, str, str]]:
        """从行列表中提取所有本地 #include "xxx.h" 的索引和名称"""
        include_lines = []
        for idx, line in enumerate(lines):
            stripped = line.strip()
            m = re.match(r'#\s*include\s+"([^"]+)"', stripped)
            if m:
                include_lines.append((idx, m.group(1), stripped))
        return include_lines


    @staticmethod
    def _extract_macro_names(content: str) -> Set[str]:
        """从内容中提取全大写的宏名（排除 include guard 和以下划线开头的内部宏）"""
        guard_macros = set()
        for m in re.finditer(r'#\s*ifndef\s+(\w+)', content):
            guard_macros.add(m.group(1))
        for m in re.finditer(r'#\s*if\s*!\s*defined\s*\(\s*(\w+)\s*\)', content):
            guard_macros.add(m.group(1))

        symbols = set()
        for m in re.finditer(r'#\s*define\s+(\w+)', content):
            macro = m.group(1)
            if not macro.startswith('_') and macro == macro.upper():
                if macro not in guard_macros:
                    symbols.add(macro)
        return symbols


    @staticmethod
    def _extract_typedef_names(content: str) -> Set[str]:
        """从内容中提取所有 typedef 名称"""
        symbols = set()
        for m in re.finditer(r'typedef\s+.*?\s+(\*?\s*\w+)\s*;', content):
            name = m.group(1).replace('*', '').strip()
            if name and not name.startswith('('):
                symbols.add(name)
        for m in re.finditer(r'typedef\s+(?:struct|enum)\s*\{[^}]*\}\s*(\w+)\s*;', content, re.DOTALL):
            symbols.add(m.group(1))
        for m in re.finditer(r'typedef\s+(?:struct|enum)\s+\w+\s*\{[^}]*\}\s*(\w+)\s*;', content, re.DOTALL):
            symbols.add(m.group(1))
        for m in re.finditer(r'typedef\s+struct\s+(\w+)\s*\*', content):
            symbols.add(m.group(1))
        return symbols


    @staticmethod
    def _find_brace_block_end(lines: List[str], start: int) -> int:
        """查找 struct/class/enum 花括号块的结束行"""
        decl_end = start
        brace_count = 0
        for k in range(start, len(lines)):
            if '{' in lines[k]:
                brace_count += lines[k].count('{')
            if '}' in lines[k]:
                brace_count -= lines[k].count('}')
            if brace_count == 0 and k > start:
                decl_end = k
                if k + 1 < len(lines) and ';' in lines[k + 1]:
                    decl_end = k + 1
                break
        return decl_end


    def _find_cross_file_unused(self, lines: List[str],
                                include_lines: List[Tuple[int, str, str]]) -> Set[int]:
        """检查跨文件 include 是否仍被使用，返回不再使用的行索引集合"""
        lines_to_remove = set()
        include_indices = {inc_idx for inc_idx, _, _ in include_lines}
        body_content = '\n'.join(
            line for idx, line in enumerate(lines)
            if idx not in include_indices
        )

        for inc_idx, inc_name, inc_line in include_lines:
            inc_output = self._find_output_include(inc_name)
            if not inc_output:
                continue

            symbols = self._extract_exported_symbols(inc_output)
            if not symbols:
                lines_to_remove.add(inc_idx)
                if self.verbose:
                    self.logger.debug(f"    [cross-file] Remove include: {inc_line} (no symbols left in {inc_name})")
                continue

            if not self._symbols_used_in_content(symbols, body_content):
                lines_to_remove.add(inc_idx)
                if self.verbose:
                    self.logger.debug(f"    [cross-file] Remove include: {inc_line} (no symbols used)")

        return lines_to_remove


    @staticmethod
    def _find_define_end(lines: List[str], start: int) -> int:
        """查找 #define 宏定义的结束行"""
        decl_end = start
        for k in range(start, len(lines)):
            decl_end = k
            if not lines[k].rstrip().endswith('\\'):
                break
        return decl_end


    def _find_include_file(self, include_name: str, current_file: Path) -> Optional[Path]:
        """在输入目录和 napi 目录中查找被 #include 引用的文件"""
        candidates = [
            current_file.parent / include_name,
            self.input_dir / include_name,
        ]
        if self.napi_dir:
            for root, dirs, files in os.walk(self.napi_dir):
                candidate = Path(root) / include_name
                if candidate.exists():
                    candidates.append(candidate)
                    break

        for root, dirs, files in os.walk(self.input_dir):
            candidate = Path(root) / include_name
            if candidate.exists():
                candidates.append(candidate)
                break

        for c in candidates:
            if c.exists():
                return c.resolve()
        return None


    def _find_macro_removal_ranges(self, lines: List[str]) -> List[Tuple[int, int]]:
        """扫描源码行，找到所有带 @systemapi 注释的 #define 宏的起止行号范围"""
        ranges = []
        i = 0
        while i < len(lines):
            line = lines[i]
            if '/*' in line or '/**' in line:
                result = self._check_macro_comment(lines, i)
                if result:
                    ranges.append(result)
                    i = result[1] + 1
                    continue
                comment_end = i
                while comment_end < len(lines) and '*/' not in lines[comment_end]:
                    comment_end += 1
                i = comment_end + 1
                continue
            else:
                i += 1
        return ranges


    def _find_output_include(self, inc_name: str) -> Optional[Path]:
        """在输出目录中查找被引用的头文件（处理后的版本）"""
        for root, dirs, files in os.walk(self.output_dir):
            candidate = Path(root) / inc_name
            if candidate.exists() and candidate.is_file():
                return candidate
            candidate = Path(root) / Path(inc_name).name
            if candidate.exists() and candidate.is_file():
                return candidate
        return None


    def _find_raw_comment(self, source_lines: List[str],
                          start_line: int) -> Optional[List[str]]:
        """从声明行向上回溯，收集原始注释行"""
        comment_lines = []
        line_idx = start_line - 2
        found_comment = False
        comment_style = None

        while line_idx >= 0:
            if line_idx >= len(source_lines):
                break
            line = source_lines[line_idx]
            stripped = line.strip()
            action, found_comment, comment_style = self._classify_comment_line(stripped, found_comment, comment_style)
            if action == 'insert':
                comment_lines.insert(0, line)
                line_idx -= 1
            elif action == 'insert_stop':
                comment_lines.insert(0, line)
                break
            elif action == 'stop':
                break
            else:
                line_idx -= 1

        return comment_lines if comment_lines else None


    @staticmethod
    def _find_typedef_aggregate_end(lines: List[str], start: int, decl_line: str) -> int:
        """查找 typedef enum/struct 类型的结束行"""
        decl_end = start
        if '{' not in decl_line:
            return decl_end
        brace_count = 0
        for k in range(start, len(lines)):
            if '{' in lines[k]:
                brace_count += lines[k].count('{')
            if '}' in lines[k]:
                brace_count -= lines[k].count('}')
            if brace_count == 0 and k > start:
                decl_end = k
                if k + 1 < len(lines) and ';' in lines[k + 1]:
                    decl_end = k + 1
                break
        return decl_end


    @staticmethod
    def _find_typedef_simple_end(lines: List[str], start: int) -> int:
        """查找简单 typedef 声明的结束行（找到分号）"""
        decl_end = start
        for k in range(start, len(lines)):
            if ';' in lines[k]:
                decl_end = k
                break
        return decl_end


    def _find_unused_local_includes(self, lines: List[str],
                                    current_file: Path) -> Set[int]:
        """查找内容中不再使用的本地 #include 行索引集合"""
        lines_to_remove = set()
        include_lines = self._extract_local_includes(lines)
        if not include_lines:
            return lines_to_remove

        include_indices = {inc_idx for inc_idx, _, _ in include_lines}
        body_content = '\n'.join(
            line for idx, line in enumerate(lines)
            if idx not in include_indices
        )

        for inc_idx, inc_name, inc_line in include_lines:
            inc_file = self._find_include_file(inc_name, current_file)
            if not inc_file:
                continue

            symbols = self._extract_exported_symbols(inc_file)
            if not symbols:
                continue

            if not self._symbols_used_in_content(symbols, body_content):
                lines_to_remove.add(inc_idx)
                if self.verbose:
                    self.logger.debug(f"    Remove unused include: {inc_line}")

        return lines_to_remove


    def _generate_fake_header_content(self, header_path: str) -> str:
        """生成 fake header 文件的完整内容，包含基础类型定义供 clang 解析使用"""
        macro_name = f"_FAKE_{header_path.replace('/', '_').replace('.', '_').upper()}"
        parts = [
            f'#ifndef {macro_name}\n#define {macro_name}\n',
            f'// Auto-generated fake header for {header_path}\n',
            '#include <stddef.h>\n#include <stdint.h>\n#include <stdbool.h>\n',
            '#ifdef __cplusplus\nextern "C" {\n#endif\n',
            self._get_fake_bool_types(),
            self._get_fake_size_types(),
            self._get_fake_int_types(),
            self._get_fake_napi_types(),
            self._get_fake_arkui_types(),
            self._get_fake_common_macros(),
            '#ifdef __cplusplus\n}\n#endif\n\n#endif\n',
        ]
        return '\n'.join(parts)


    @staticmethod
    def _get_fake_arkui_types() -> str:
        """返回 fake header 中 ArkUI 类型的字符串片段"""
        return (
            '// ============ ArkUI Types ============\n'
            'struct ArkUI_ProgressLinearStyleOption;\n'
            'typedef struct ArkUI_ProgressLinearStyleOption ArkUI_ProgressLinearStyleOption;\n\n'
            'struct ArkUI_Node;\ntypedef struct ArkUI_Node ArkUI_Node;\n'
        )


    @staticmethod
    def _get_fake_bool_types() -> str:
        """返回 fake header 中 bool 类型定义的字符串片段"""
        return (
            '// ============ Basic Type Definitions ============\n'
            '#ifndef __cplusplus\ntypedef _Bool bool;\n#else\ntypedef bool bool;\n#endif\n\n'
            '#define true 1\n#define false 0\n#define __bool_true_false_are_defined 1\n'
        )


    @staticmethod
    def _get_fake_common_macros() -> str:
        """返回 fake header 中常用宏定义的字符串片段"""
        return (
            '// ============ Common Macros ============\n'
            '#ifndef NULL\n#define NULL ((void*)0)\n#endif\n\n'
            '#ifndef SIZE_MAX\n#define SIZE_MAX ((size_t)-1)\n#endif\n'
        )


    @staticmethod
    def _get_fake_int_types() -> str:
        """返回 fake header 中固定宽度整数类型的字符串片段"""
        return (
            '// ============ Fixed-width Integer Types ============\n'
            '#ifndef int8_t\ntypedef signed char int8_t;\n#endif\n\n'
            '#ifndef uint8_t\ntypedef unsigned char uint8_t;\n#endif\n\n'
            '#ifndef int16_t\ntypedef short int16_t;\n#endif\n\n'
            '#ifndef uint16_t\ntypedef unsigned short uint16_t;\n#endif\n\n'
            '#ifndef int32_t\ntypedef int int32_t;\n#endif\n\n'
            '#ifndef uint32_t\ntypedef unsigned int uint32_t;\n#endif\n\n'
            '#ifndef int64_t\ntypedef long long int64_t;\n#endif\n\n'
            '#ifndef uint64_t\ntypedef unsigned long long uint64_t;\n#endif\n'
        )


    @staticmethod
    def _get_fake_napi_types() -> str:
        """返回 fake header 中 NAPI 类型的字符串片段"""
        return (
            '// ============ NAPI Types ============\n'
            'struct napi_env__;\ntypedef struct napi_env__ *napi_env;\n\n'
            'struct napi_value__;\ntypedef struct napi_value__ *napi_value;\n\n'
            'struct napi_callback_info__;\ntypedef struct napi_callback_info__ *napi_callback_info;\n\n'
            'typedef enum {\n'
            '    napi_ok = 0,\n'
            '    napi_invalid_arg,\n'
            '    napi_oom,\n'
            '    napi_pending_exception,\n'
            '    napi_cancelled\n'
            '} napi_status;\n'
        )


    @staticmethod
    def _get_fake_size_types() -> str:
        """返回 fake header 中 size_t 等大小类型的字符串片段"""
        return (
            '// ============ Size Types ============\n'
            '#ifndef size_t\ntypedef __SIZE_TYPE__ size_t;\n#endif\n\n'
            '#ifndef ssize_t\ntypedef __SIZE_TYPE__ ssize_t;\n#endif\n\n'
            '#ifndef off_t\ntypedef long off_t;\n#endif\n\n'
            '#ifndef ptrdiff_t\ntypedef __PTRDIFF_TYPE__ ptrdiff_t;\n#endif\n'
        )


    def _init_stats(self):
        self.stats = {
            'total_files_scanned': 0,
            'header_files': 0,
            'non_header_files': 0,
            'clang_processed': 0,
            'clang_modified': 0,
            'regex_processed': 0,
            'regex_modified': 0,
            'regex_no_api': 0,
            'modified_headers': 0,
            'apis_removed': 0,
            'clang_timeout': 0,
            'clang_errors': 0,
            'functions_found': 0,
            'functions_with_systemapi': 0,
            'fake_headers_created': 0,
            'includes_removed': 0,
            'empty_headers_removed': 0,
        }

        self.clang_files: List[Path] = []
        self.clang_modified_files: List[Path] = []
        self.regex_files: List[Path] = []
        self.regex_modified_files: List[Path] = []
        self.failed_files: List[Tuple[Path, str]] = []
        self.validation_errors: List[Tuple[Path, str]] = []
        self.clang_error_files: List[Tuple[Path, str]] = []
        self.public_ref_errors: List[Tuple[Path, str, List[str]]] = []
        self.all_deleted_names: Dict[str, Set[Path]] = {}


    def _is_from_main_file(self, node: Dict[str, Any]) -> bool:
        """判断 AST 节点是否来自主文件（而非 #include 进来的文件）。
        只检查 includedFrom 字段：
        - 有 includedFrom → 来自 #include 文件 → 跳过
        - 无 includedFrom → 主文件中的声明 → 处理

        注意：不检查 file 字段。因为主文件中使用外部类型的函数声明
        （如 void Func(const ExternalType* p)）的 loc 也会带 file 字段，
        但它们确实是在主文件中声明的，不应被过滤。"""
        loc = node.get('loc', {})
        if isinstance(loc, dict):
            if 'includedFrom' in loc:
                return False
        return True


    def _log_processing_start(self, total_headers: int) -> None:
        """输出处理开始前的日志信息"""
        self.logger.info(f"Starting processing...")
        self.logger.info(f"Input directory:  {self.input_dir}")
        self.logger.info(f"Output directory: {self.output_dir}")
        if self.napi_dir:
            self.logger.info(f"NAPI directory:   {self.napi_dir}")
        self.logger.info(f"Total header files to process: {total_headers}")


    def _parse_clang_output(self, stdout_text: str) -> Optional[Dict[str, Any]]:
        if not stdout_text or not stdout_text.strip():
            return None
        stdout = stdout_text
        json_start = -1
        for i, char in enumerate(stdout):
            if char in '{[':
                json_start = i
                break

        if json_start >= 0:
            stdout = stdout[json_start:]

        try:
            return json.loads(stdout)
        except json.JSONDecodeError:
            return None


    def _parse_comment_text(self, comment_lines: List[str]) -> Optional[str]:
        """从原始注释行中提取注释正文文本"""
        full_comment = '\n'.join(comment_lines)

        if '/*' in full_comment or '/**' in full_comment:
            match = re.search(r'/\*+([\s\S]*?)\*/', full_comment)
            if match:
                comment_content = match.group(1).strip()
            else:
                comment_content = full_comment
        else:
            comment_lines_only = [
                line.split('//', 1)[1].strip()
                for line in comment_lines
                if '//' in line
            ]
            comment_content = '\n'.join(comment_lines_only)

        comment_content = re.sub(r'^\s*[*!]\s?', '', comment_content, flags=re.MULTILINE)
        comment_content = comment_content.strip()
        return comment_content if comment_content else None


    def _print_error_stats(self):
        if self.failed_files and len(self.failed_files) <= 10:
            print()
            print("? FAILED FILES:")
            print("-" * 70)
            for file_path, reason in self.failed_files[:10]:
                try:
                    rel_path = file_path.relative_to(self.input_dir)
                except ValueError:
                    rel_path = file_path
                print(f"  ? {rel_path}")

        if self.clang_error_files:
            print()
            print("?? CLANG ERROR FILES (regex fallback used):")
            print("-" * 70)
            for file_path, reason in self.clang_error_files:
                try:
                    rel_path = file_path.relative_to(self.input_dir)
                except ValueError:
                    rel_path = file_path
                print(f"  ?? {rel_path}")
                print(f"     Reason: {reason}")

        if self.public_ref_errors:
            print()
            print("? ERROR: Public API references @systemapi type (should be blocked upstream):")
            print("-" * 70)
            for file_path, deleted_type, refs in self.public_ref_errors:
                try:
                    rel_path = file_path.relative_to(self.input_dir)
                except ValueError:
                    rel_path = file_path
                print(f"  File: {rel_path}")
                print(f"  Deleted @systemapi type: {deleted_type}")
                for ref in refs:
                    print(f"    Referenced by: {ref}")
                print()


    def _collect_deleted_names(self, input_file: Path, deleted_names: List[str]) -> None:
        for name in deleted_names:
            if name not in self.all_deleted_names:
                self.all_deleted_names[name] = set()
            self.all_deleted_names[name].add(input_file)

    def _check_public_references_across_files(self) -> None:
        if not self.all_deleted_names:
            return
        skip_names = {
            'bool', '_Bool', 'true', 'false', 'NULL',
            'size_t', 'ssize_t', 'ptrdiff_t', 'nullptr_t',
            'int8_t', 'int16_t', 'int32_t', 'int64_t',
            'uint8_t', 'uint16_t', 'uint32_t', 'uint64_t',
            'intptr_t', 'uintptr_t',
            'int_least8_t', 'int_least16_t', 'int_least32_t', 'int_least64_t',
            'uint_least8_t', 'uint_least16_t', 'uint_least32_t', 'uint_least64_t',
            'int_fast8_t', 'int_fast16_t', 'int_fast32_t', 'int_fast64_t',
            'uint_fast8_t', 'uint_fast16_t', 'uint_fast32_t', 'uint_fast64_t',
            'intmax_t', 'uintmax_t',
        }
        output_contents: Dict[Path, str] = {}
        for output_file in self.output_dir.rglob('*'):
            if output_file.is_file() and self.is_header_file(output_file):
                try:
                    with open(output_file, 'r', encoding='utf-8', errors='ignore') as f:
                        output_contents[output_file] = f.read()
                except Exception:
                    pass
        for name in self.all_deleted_names:
            if name in skip_names:
                continue
            deleted_in_files = self.all_deleted_names[name]
            for output_file, content in output_contents.items():
                input_file = self.input_dir / output_file.relative_to(self.output_dir)
                refs = []
                for idx, line in enumerate(content.split('\n')):
                    stripped = line.strip()
                    if not stripped or stripped.startswith('//') or stripped.startswith('/*'):
                        continue
                    if stripped.startswith('*') or stripped.startswith('/**'):
                        continue
                    if re.search(rf'\b{re.escape(name)}\b', line):
                        ctx = self._get_declaration_context(content.split('\n'), idx)
                        refs.append(ctx)
                if refs:
                    self.public_ref_errors.append((input_file, name, refs))

    def _get_declaration_context(self, lines: List[str], target_idx: int) -> str:
        start = target_idx
        while start > 0:
            prev = lines[start - 1].strip()
            if prev == '' or prev.startswith('//') or prev.startswith('/*') or prev.startswith('*') or prev.endswith('*/'):
                break
            if not prev.endswith(','):
                break
            start -= 1
        end = target_idx
        while end < len(lines) - 1:
            curr = lines[end].strip()
            if curr.endswith(';') or curr.endswith('}'):
                break
            end += 1
        snippet = ' '.join(l.strip() for l in lines[start:end + 1] if l.strip())
        if len(snippet) > 120:
            snippet = snippet[:120] + '...'
        return snippet

    def _print_file_stats(self):
        print("?? FILE STATISTICS:")
        print("-" * 70)
        print(f"  Total files scanned:        {self.stats['total_files_scanned']}")
        print(f"  Header files:               {self.stats['header_files']}")
        print(f"  Non-header files:           {self.stats['non_header_files']}")
        print(f"  Fake headers created:       {self.stats['fake_headers_created']}")
        print()


    def _print_modification_stats(self):
        print("?? MODIFICATION RESULTS:")
        print("-" * 70)
        print(f"  Modified headers:           {self.stats['modified_headers']}")
        print(f"  Unchanged headers:          {self.stats['header_files'] - self.stats['modified_headers']}")
        print(f"  Total APIs removed:         {self.stats['apis_removed']}")
        print(f"  Unused includes removed:    {self.stats['includes_removed']}")
        print(f"  Empty headers removed:      {self.stats['empty_headers_removed']}")
        print()


    def _print_node_stats(self):
        print("?? NODE STATISTICS:")
        print("-" * 70)
        print(f"  Functions found:            {self.stats['functions_found']}")
        print(f"  Functions with @systemapi:  {self.stats['functions_with_systemapi']}")
        print()



    def _process_header_with_clang(self, input_file: Path, output_file: Path,
                                   ast: Dict[str, Any], source_lines: List[str],
                                   content: str) -> bool:
        self.stats['clang_processed'] += 1
        self.clang_files.append(input_file)

        to_remove: List[Tuple[int, int, str]] = []
        self.collect_functions_to_remove(ast, source_lines, content, to_remove)

        output_file.parent.mkdir(parents=True, exist_ok=True)

        result_content = content
        removed_count = 0
        deleted_names = []

        if to_remove:
            new_source_lines, clang_removed = self.remove_ranges_from_source(source_lines, to_remove)
            result_content = '\n'.join(new_source_lines)
            removed_count += clang_removed
            deleted_names = list(dict.fromkeys(name for _, _, name in to_remove))

        result_content, macro_removed = self.remove_macro_systemapi(result_content)
        if macro_removed > 0:
            removed_count += macro_removed
            self.logger.debug(f"    Removed {macro_removed} macro(s) with @systemapi")

        regex_content, regex_removed, _, regex_names = self.regex_remove_systemapi(result_content, input_file)
        if regex_removed > 0:
            result_content = regex_content
            removed_count += regex_removed
            deleted_names.extend(regex_names)
            self.logger.debug(f"    Removed {regex_removed} conditional-compiled API(s)")

        result_content = self._cleanup_orphan_semicolons(result_content)

        if removed_count == 0:
            shutil.copy2(input_file, output_file)
            return False

        result_content, inc_removed = self.remove_unused_includes(result_content, input_file)
        if inc_removed > 0:
            self.stats['includes_removed'] += inc_removed
            self.logger.debug(f"    Removed {inc_removed} unused include(s)")

        if deleted_names:
            self._collect_deleted_names(input_file, deleted_names)

        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(result_content)

        self.stats['clang_modified'] += 1
        self.clang_modified_files.append(input_file)
        self.stats['apis_removed'] += removed_count
        self.stats['modified_headers'] += 1
        self.logger.debug(f"  Modified (clang+regex): removed {removed_count} API(s)")
        return True


    def _process_header_with_regex(self, input_file: Path, output_file: Path,
                                   content: str, clang_errors: List[str]) -> bool:
        # 第三关：Regex 正则表达式回退（备用路径）
        self.stats['clang_errors'] += 1
        error_detail = '; '.join(clang_errors) if clang_errors else 'unknown'
        self.clang_error_files.append((input_file, error_detail))
        self.logger.warning(f"  Clang parsing failed for {input_file.name}, using regex fallback...")
        self.logger.warning(f"    Reason: {error_detail}")

        self.stats['regex_processed'] += 1
        self.regex_files.append(input_file)

        new_content, removed_count, found_systemapi, deleted_names = self.regex_remove_systemapi(content, input_file)
        new_content = self._cleanup_orphan_semicolons(new_content)

        output_file.parent.mkdir(parents=True, exist_ok=True)

        if removed_count > 0:
            result_content, inc_removed = self.remove_unused_includes(new_content, input_file)
            if inc_removed > 0:
                self.stats['includes_removed'] += inc_removed
                self.logger.debug(f"    Removed {inc_removed} unused include(s)")
            else:
                result_content = new_content

            self._collect_deleted_names(input_file, deleted_names)

            with open(output_file, 'w', encoding='utf-8') as f:
                f.write(result_content)
            self.stats['regex_modified'] += 1
            self.regex_modified_files.append(input_file)
            self.stats['apis_removed'] += removed_count
            self.stats['modified_headers'] += 1
            self.logger.debug(f"  Modified (regex): removed {removed_count} API(s)")
            return True
        else:
            self.stats['regex_no_api'] += 1
            shutil.copy2(input_file, output_file)
            return False


    def _process_single_cross_file(self, output_file: Path) -> int:
        """处理单个输出文件的跨文件 include 清理，返回清理数量"""
        try:
            with open(output_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
        except Exception:
            return 0

        lines = content.split('\n')
        include_lines = self._extract_local_includes(lines)
        if not include_lines:
            return 0

        lines_to_remove = self._find_cross_file_unused(lines, include_lines)
        if lines_to_remove:
            new_lines = [line for idx, line in enumerate(lines) if idx not in lines_to_remove]
            with open(output_file, 'w', encoding='utf-8') as f:
                f.write('\n'.join(new_lines))
            self.logger.debug(f"  [cross-file] {output_file.name}: removed {len(lines_to_remove)} unused include(s)")
            return len(lines_to_remove)
        return 0


    def _regex_check_in_aggregate(self, lines: List[str], comment_start: int) -> Tuple[bool, int, Optional[str]]:
        in_aggregate = False
        aggregate_start_line = -1
        aggregate_type = None

        for k in range(comment_start - 1, -1, -1):
            line_check = lines[k]
            if ('enum' in line_check and '{' in line_check) or ('typedef' in line_check and 'enum' in line_check and '{' in line_check):
                aggregate_end_line = self._find_brace_block_end(lines, k)
                if aggregate_end_line >= comment_start:
                    in_aggregate = True
                    aggregate_start_line = k
                    aggregate_type = 'enum'
                break
            if ('struct' in line_check and '{' in line_check) or ('typedef' in line_check and 'struct' in line_check and '{' in line_check):
                aggregate_end_line = self._find_brace_block_end(lines, k)
                if aggregate_end_line >= comment_start:
                    in_aggregate = True
                    aggregate_start_line = k
                    aggregate_type = 'struct'
                break
            if ('union' in line_check and '{' in line_check) or ('typedef' in line_check and 'union' in line_check and '{' in line_check):
                aggregate_end_line = self._find_brace_block_end(lines, k)
                if aggregate_end_line >= comment_start:
                    in_aggregate = True
                    aggregate_start_line = k
                    aggregate_type = 'union'
                break

        return in_aggregate, aggregate_start_line, aggregate_type


    def _regex_collect_comment_block(self, lines: List[str], start: int) -> Tuple[str, int]:
        comment_start = start
        comment_end = start
        in_comment = True
        comment_content = []

        while comment_end < len(lines) and in_comment:
            comment_content.append(lines[comment_end])
            if '*/' in lines[comment_end]:
                in_comment = False
            comment_end += 1

        comment_text = '\n'.join(comment_content)
        return comment_text, comment_end


    def _regex_find_aggregate_end(self, lines: List[str], agg_start: int) -> int:
        """查找 aggregate（enum/struct）体的结束行"""
        return self._find_brace_block_end(lines, agg_start)


    def _regex_find_decl_end(self, lines: List[str], comment_end: int) -> Optional[int]:
        """从注释结束位置向下查找声明的结束行号。
        跳过紧贴的后续注释块（无空行分隔），遇到空行后的注释则视为不关联。
        """
        j = self._skip_attached_comments(lines, comment_end)
        if j is None or j >= len(lines):
            return None
        return self._resolve_decl_end(lines, j)


    def _regex_handle_systemapi_comment(self, lines: List[str], i: int,
                                        to_remove: List[bool]) -> Tuple[int, int]:
        """处理单个含 /* 的注释块，若含 @systemapi 则标记删除范围。
        返回 (下一扫描位置, 删除计数)"""
        comment_text, comment_end = self._regex_collect_comment_block(lines, i)
        if not self._has_strict_systemapi(comment_text):
            return comment_end, 0

        in_aggregate, agg_start, agg_type = self._regex_check_in_aggregate(lines, i)
        if in_aggregate and agg_start >= 0:
            if agg_type in ('struct', 'enum', 'union'):
                if self._regex_should_skip_struct_field(lines, agg_start):
                    return comment_end, 0
            aggregate_end = self._regex_find_aggregate_end(lines, agg_start)
            for k in range(agg_start, aggregate_end + 1):
                if k < len(to_remove):
                    to_remove[k] = True
            return aggregate_end + 1, 1

        decl_end = self._regex_find_decl_end(lines, comment_end)
        if decl_end is not None:
            actual_start = self._find_contiguous_comment_start(lines, i)
            for k in range(actual_start, decl_end + 1):
                if k < len(to_remove):
                    to_remove[k] = True
            return decl_end + 1, 1

        return comment_end, 0


    def _regex_should_skip_struct_field(self, lines: List[str], agg_start: int) -> bool:
        agg_comment_has_systemapi = False
        for k in range(agg_start - 1, -1, -1):
            line_check = lines[k].strip()
            if line_check.startswith('*') or line_check.startswith('/*') or line_check.startswith('/**') or line_check.startswith('/*!') or line_check == '' or '*/' in line_check:
                stripped = line_check.lstrip('/').lstrip('*').lstrip('!').strip()
                stripped = stripped.rstrip('/').rstrip('*').strip()
                if stripped == '@systemapi':
                    agg_comment_has_systemapi = True
            else:
                break
        return not agg_comment_has_systemapi


    def _resolve_missing_headers(self, missing_headers: Set[str],
                                 input_file: Path,
                                 fake_include_dir: Path) -> None:
        """为缺失的头文件创建符号链接或 fake header"""
        for header in missing_headers:
            real_header = self.find_header_file(header, input_file)
            if real_header:
                fake_header = fake_include_dir / header
                fake_header.parent.mkdir(parents=True, exist_ok=True)
                os.symlink(real_header, fake_header)
                if self.verbose:
                    self.logger.debug(f"Linked existing header: {header} -> {real_header}")
            else:
                self.create_fake_header(header, fake_include_dir)


    def _run_ast_dump(self, input_file: Path,
                      compile_args: List[str]) -> Tuple[Optional[Dict[str, Any]], List[str]]:
        """执行 clang AST dump 并解析结果，返回 AST 或错误列表"""
        cmd = [self.clang_binary, '-Xclang', '-ast-dump=json', '-fsyntax-only'] + compile_args + [str(input_file)]
        if self.verbose:
            self.logger.debug(f"Parsing: {input_file.name}")
        result = subprocess.run(cmd, capture_output=True, timeout=30)
        result.stdout = result.stdout.decode('utf-8', errors='replace')
        result.stderr = result.stderr.decode('utf-8', errors='replace')
        ast = self._parse_clang_output(result.stdout)
        if ast is not None:
            return ast, []
        if result.returncode != 0 and result.stderr:
            error_lines = result.stderr.strip().split('\n')
            first_errors = [line.strip() for line in error_lines[:5] if 'error:' in line.lower()]
            for line in first_errors:
                self.logger.info(f"    {line}")
            return None, first_errors
        return None, []


    def _symbols_used_in_content(self, symbols: Set[str], content: str) -> bool:
        """检查符号集合中是否有任一符号在内容中被使用"""
        for sym in symbols:
            pattern = rf'\b{re.escape(sym)}\b'
            if re.search(pattern, content):
                return True
        return False


    def build_include_paths(self, input_file: Path) -> List[str]:
        """构建 clang 编译时的 include 搜索路径列表"""
        include_paths = []

        include_paths.append(f"-I{input_file.parent}")

        if self.napi_dir and self.napi_dir.exists():
            include_paths.append(f"-I{self.napi_dir}")
            for subdir in ['include', 'inc', 'public', 'base', 'utils']:
                candidate = self.napi_dir / subdir
                if candidate.exists():
                    include_paths.append(f"-I{candidate}")

        include_paths.append(f"-I{self.input_dir}")

        return include_paths


    def _try_find_clang_binary(self, binary_path: str) -> bool:
        """尝试检测指定路径的 clang 是否可用，成功返回 True"""
        try:
            result = subprocess.run([binary_path, '--version'], capture_output=True,
                                    check=True)
            result.stdout = result.stdout.decode('utf-8', errors='replace')
            version_line = result.stdout.split('\n')[0]
            self.logger.info(f"Found clang: {version_line}")
            self.clang_binary = binary_path
            return True
        except (subprocess.CalledProcessError, FileNotFoundError):
            return False

    def check_clang(self):
        """检查系统是否安装了 clang，未安装则自动切换到正则表达式模式"""
        self.clang_binary = None
        for binary in ['clang++', 'clang']:
            if self._try_find_clang_binary(binary):
                return
        if sys.platform == 'win32':
            for path in [r'C:\Program Files\LLVM\bin\clang++.exe',
                         r'C:\Program Files (x86)\LLVM\bin\clang++.exe']:
                if os.path.isfile(path) and self._try_find_clang_binary(path):
                    return
        self.logger.warning("clang not found, automatically switching to regex mode")
        self.force_regex = True


    def collect_functions_to_remove(self, node: Dict[str, Any], source_lines: List[str],
                                    source_text: str,
                                    to_remove: List[Tuple[int, int, str]]) -> None:
        """递归遍历 AST 树，收集所有带 @systemapi 标签的声明。
        对每个匹配节点：
        1. 过滤非主文件节点
        2. 提取上方注释，检查 @systemapi
        3. 向上回溯扩展删除范围到注释起始行
        4. 加入删除列表，且不再递归子节点（避免 typedef enum 等重复匹配）
        """
        node_kind = node.get('kind')
        if not node_kind:
            return

        matched = self._check_and_collect_node(node, source_lines, source_text, node_kind, to_remove)

        if not matched and 'inner' in node and isinstance(node['inner'], list):
            for child in node['inner']:
                self.collect_functions_to_remove(child, source_lines, source_text, to_remove)


    def create_fake_header(self, header_path: str, fake_include_dir: Path) -> Path:
        """生成假头文件，包含基础类型定义，让 clang 能在缺少依赖时继续解析。
        包含：_Bool/bool、size_t、int8_t~uint64_t、napi_env/value/status、ArkUI 类型等。
        """
        fake_header = fake_include_dir / header_path
        fake_header.parent.mkdir(parents=True, exist_ok=True)

        content = self._generate_fake_header_content(header_path)

        with open(fake_header, 'w') as f:
            f.write(content)

        self.stats['fake_headers_created'] += 1
        if self.verbose:
            self.logger.debug(f"Created fake header: {header_path}")

        return fake_header


    def cross_file_include_cleanup(self) -> int:
        """第二轮扫描：所有文件处理完后，检查跨文件 include 依赖。
        读取输出版本（已删除 @systemapi）的被引用文件，提取剩余符号，
        如果引用方不再使用任何符号，则移除 include。
        返回总共清理的 include 数量。
        """
        total_removed = 0
        output_headers = self._collect_output_headers()

        for output_file in output_headers:
            total_removed += self._process_single_cross_file(output_file)

        return total_removed

    @staticmethod
    def _remove_empty_conditionals_pass(lines: List[str]) -> Tuple[List[str], bool]:
        """单趟扫描移除空条件编译块，返回 (新行列表, 是否有变更)"""
        new_lines = []
        changed = False
        i = 0
        while i < len(lines):
            stripped = lines[i].strip()
            if re.match(r'#\s*if(?:n?def)?\b', stripped):
                endif_line = SystemApiRemover._find_empty_conditional_range(lines, i)
                if endif_line is not None:
                    changed = True
                    i = endif_line + 1
                    continue
            new_lines.append(lines[i])
            i += 1
        return new_lines, changed

    def _cleanup_orphan_semicolons(self, content: str) -> str:
        """删除由裁剪残留的孤立分号行（仅含分号和空白）。
        典型场景：多行声明的分号独占一行，regex 路径的 _resolve_decl_end
        默认分支只返回当前行，未向前扫描到分号，导致分号行残留。
        同时也处理 ;; 或 ; ; 等写法。
        """
        lines = content.split('\n')
        new_lines = [line for line in lines if not re.match(r'^\s*(;\s*)+$', line)]
        return '\n'.join(new_lines)

    def _cleanup_empty_conditionals(self, content: str) -> str:
        """移除删除 @systemapi 后产生的空 #ifdef/#if/#ifndef ... #endif 块"""
        changed = True
        while changed:
            lines = content.split('\n')
            new_lines, changed = self._remove_empty_conditionals_pass(lines)
            content = '\n'.join(new_lines)
        return content


    def extract_comment_before_node(self, node: Dict[str, Any], source_lines: List[str],
                                    func_name: str,
                                    source_text: Optional[str] = None) -> Optional[str]:
        """从 AST 节点声明的上方向上回溯，提取完整的注释块内容。
        支持 /** */ 和 // 两种注释风格，也处理注释前的空行。
        """
        start_line, _ = self.get_node_location(node, source_text, source_lines)
        if not start_line or start_line <= 1:
            return None

        comment_lines = self._find_raw_comment(source_lines, start_line)
        if not comment_lines:
            return None

        return self._parse_comment_text(comment_lines)


    def find_header_file(self, header_path: str, base_file: Path) -> Optional[Path]:
        """在多个搜索路径中查找被引用的头文件"""
        header_parts = Path(header_path).parts

        search_dirs = [base_file.parent]

        if self.napi_dir:
            search_dirs.append(self.napi_dir)
            for part in header_parts[:-1]:
                candidate = self.napi_dir / part
                if candidate.exists():
                    search_dirs.append(candidate)

        search_dirs.append(self.input_dir)

        # 向上遍历 5 层父目录
        current = base_file.parent
        for _ in range(5):
            search_dirs.append(current)
            current = current.parent

        # 去重，保持顺序
        search_dirs = list(dict.fromkeys(search_dirs))

        for search_dir in search_dirs:
            candidate = search_dir / header_path
            if candidate.exists() and candidate.is_file():
                return candidate
            # 只按文件名搜索（忽略路径中的目录部分）
            candidate_name = search_dir / Path(header_path).name
            if candidate_name.exists() and candidate_name.is_file():
                return candidate_name

        return None


    def get_node_location(self, node: Dict[str, Any],
                          source_text: Optional[str] = None,
                          source_lines: Optional[List[str]] = None) -> Tuple[Optional[int], Optional[int]]:
        """从 AST 节点中提取声明的起止行号。
        优先从 range.begin/end.line 获取，若无 line 字段则回退到名称搜索。
        """
        start_line = None
        end_line = None

        if 'range' in node and isinstance(node['range'], dict):
            range_info = node['range']
            if 'begin' in range_info and 'end' in range_info:
                begin = range_info['begin']
                end = range_info['end']
                if 'line' in begin:
                    start_line = begin['line']
                if 'line' in end:
                    end_line = end['line']

        if start_line is None and 'loc' in node and isinstance(node['loc'], dict):
            loc = node['loc']
            if 'line' in loc:
                start_line = loc['line']

        if start_line is None:
            start_line, end_line = self._find_node_by_name(node, source_lines)
            if start_line is None:
                return None, None

        if end_line is None:
            end_line = self._find_declaration_end_in_source(source_lines, start_line)
            if end_line is None:
                end_line = start_line

        return start_line, end_line

    def _find_node_by_name(self, node: Dict[str, Any],
                           source_lines: Optional[List[str]]) -> Tuple[Optional[int], Optional[int]]:
        """当 clang 未提供行号时，通过节点名称在源文件中搜索定位。"""
        if not source_lines:
            return None, None
        node_name = node.get('name')
        if not node_name:
            return None, None
        node_kind = node.get('kind', '')
        pattern = re.compile(rf'\b{re.escape(node_name)}\b')
        for i, line in enumerate(source_lines):
            if pattern.search(line):
                return i + 1, i + 1
        return None, None


    def _has_strict_systemapi(self, text: str) -> bool:
        for line in text.split('\n'):
            stripped = line.strip()
            stripped = stripped.lstrip('/').lstrip('*').lstrip('!').strip()
            stripped = stripped.rstrip('/').rstrip('*').strip()
            if stripped == '@systemapi':
                return True
        return False

    def has_systemapi_tag(self, comment: Optional[str]) -> bool:
        for line in (comment or '').split('\n'):
            stripped = line.strip()
            stripped = stripped.lstrip('/').lstrip('*').lstrip('!').strip()
            stripped = stripped.rstrip('/').rstrip('*').strip()
            if stripped == '@systemapi':
                return True
        return False


    def is_header_file(self, file_path: Path) -> bool:
        """根据扩展名判断是否为头文件"""
        header_extensions = {'.h', '.hpp', '.hxx', '.hh', '.inl', '.h++', '.hp'}
        return file_path.suffix in header_extensions


    def offset_to_line(self, source_text: str, offset: int) -> Optional[int]:
        """将字节偏移量转换为行号（1-based）。
        某些 AST 节点只有 offset 没有 line 字段时使用。
        """
        if offset is None or offset < 0 or offset > len(source_text):
            return None
        return source_text[:offset].count('\n') + 1


    def parse_header_with_clang(self, input_file: Path) -> Optional[Dict[str, Any]]:
        """使用 clang++ 解析头文件，返回 JSON 格式的 AST。
        处理流程：
        1. 构建编译参数（抑制所有警告，允许继续解析）
        2. 预处理收集缺失头文件列表
        3. 为缺失头文件创建符号链接或生成 fake header
        4. 执行 -ast-dump=json 获取 AST
        5. 从输出中提取 JSON（跳过前面的非 JSON 内容）
        """
        try:
            fake_include_dir = Path(tempfile.mkdtemp())
            include_paths = self.build_include_paths(input_file)
            compile_args = self._build_clang_command(include_paths, fake_include_dir)

            self._create_basic_fake_headers(fake_include_dir)
            missing_headers = self._collect_missing_headers(compile_args, input_file)
            self._resolve_missing_headers(missing_headers, input_file, fake_include_dir)

            ast, errors = self._run_ast_dump(input_file, compile_args)
            if ast is not None:
                return ast, []
            return None, errors

        except subprocess.TimeoutExpired:
            self.logger.info(f"    Timeout parsing {input_file.name} (30s)")
            self.stats['clang_timeout'] += 1
            return None, ['Clang parsing timeout (30s)']
        except Exception as e:
            if self.verbose:
                self.logger.debug(f"Parse failed: {e}")
            return None, [str(e)]
        finally:
            if 'fake_include_dir' in locals():
                shutil.rmtree(fake_include_dir, ignore_errors=True)


    def print_stats(self):
        """输出处理统计报告"""
        elapsed_time = time.time() - self.start_time

        print("\n" + "=" * 70)
        print("PROCESSING COMPLETE")
        print("=" * 70)
        print(f"??  Script execution time:     {elapsed_time:.2f} seconds")
        print()
        self._print_file_stats()
        self._print_modification_stats()
        self._print_node_stats()
        self._print_error_stats()

        print(f"Input directory:  {self.input_dir}")
        print(f"Output directory: {self.output_dir}")
        if self.napi_dir:
            print(f"NAPI directory:   {self.napi_dir}")
        print("=" * 70)


    def process_directory(self) -> bool:
        """处理整个输入目录：遍历文件、分发处理、保持目录结构"""
        try:
            if not self.input_dir.exists():
                self.logger.error(f"Input directory not found: {self.input_dir}")
                return False

            all_header_files = self._collect_header_files()
            total_headers = len(all_header_files)
            self._log_processing_start(total_headers)
            self.output_dir.mkdir(parents=True, exist_ok=True)
            self._copy_non_header_files()

            for idx, file_path in enumerate(all_header_files, 1):
                self.stats['total_files_scanned'] += 1
                self.stats['header_files'] += 1
                rel_path = file_path.relative_to(self.input_dir)
                output_file = self.output_dir / rel_path
                if self.verbose:
                    self.logger.debug(f"[{idx}/{total_headers}] Processing: {rel_path}")
                self.process_header_file(file_path, output_file)

            cross_removed = self.cross_file_include_cleanup()
            if cross_removed > 0:
                self.stats['includes_removed'] += cross_removed
                self.logger.debug(f"Cross-file include cleanup: removed {cross_removed} include(s)")

            self._remove_empty_output_files()

            self._check_public_references_across_files()
            self._validate_output_files()

            return True

        except Exception as e:
            self.logger.error(f"Error processing directory: {e}")
            return False


    def process_header_file(self, input_file: Path, output_file: Path) -> bool:
        """处理单个头文件的主入口。
        流程：
        1. Clang 解析 → 收集删除范围 → 删除 → 清理 #include → 写入
        2. Clang 失败 → regex 回退 → 清理 #include → 写入
        返回 True 表示文件被修改，False 表示未修改。
        """
        try:
            with open(input_file, 'r', encoding='utf-8') as f:
                content = f.read()
                source_lines = content.split('\n')

            if not source_lines:
                return False

            self.logger.debug(f"  Parsing: {input_file.name}")
            clang_errors = []
            if self.force_regex:
                ast = None
            else:
                ast, clang_errors = self.parse_header_with_clang(input_file)
            if ast:
                return self._process_header_with_clang(input_file, output_file, ast, source_lines, content)

            return self._process_header_with_regex(input_file, output_file, content, clang_errors)

        except Exception as e:
            self.logger.error(f"Error processing {input_file.name}: {e}")
            self.failed_files.append((input_file, str(e)))
            return False


    def regex_remove_systemapi(self, content: str, file_path: Path) -> Tuple[str, int, bool, List[str]]:
        """正则表达式方式删除 @systemapi 声明。仅在 Clang 解析失败时使用。
        返回 (新内容, 删除数, 是否找到systemapi, 被删名称列表)
        """
        removed_count = 0
        found_systemapi = False
        lines = content.split('\n')
        to_remove = [False] * len(lines)

        i = 0
        while i < len(lines):
            line = lines[i]
            stripped = line.strip()
            if '/*' in line or '/**' in line:
                next_i, count = self._regex_handle_systemapi_comment(lines, i, to_remove)
                if count > 0:
                    removed_count += count
                    found_systemapi = True
                i = max(next_i, i + 1)
            elif stripped.startswith('//'):
                next_i, count = self._regex_handle_line_comment(lines, i, to_remove)
                if count > 0:
                    removed_count += count
                    found_systemapi = True
                i = max(next_i, i + 1)
            else:
                i += 1

        if any(to_remove):
            deleted_names = self._extract_deleted_names_from_lines(lines, to_remove)
            new_lines = [lines[idx] for idx in range(len(lines)) if not to_remove[idx]]
            return '\n'.join(new_lines), removed_count, found_systemapi, deleted_names

        return content, 0, found_systemapi, []

    def _extract_deleted_names_from_lines(self, lines: List[str], to_remove: List[bool]) -> List[str]:
        import re as _re
        name_pattern = _re.compile(
            r'\b(?:typedef\s+(?:struct|enum|union)\s+\w*\s+|'
            r'typedef\s+\w+\s+|'
            r'(?:struct|enum|union)\s+(\w+)|'
            r'(?:void|int\d+_t|uint\d+_t|char|float|double|long|short|unsigned|signed|bool|size_t)\s*\*?\s*'
            r'(\w+)\s*\()'
        )
        names = []
        for idx in range(len(lines)):
            if not to_remove[idx]:
                continue
            line = lines[idx].strip()
            if line.startswith('//') or line.startswith('/*') or line.startswith('*') or line.startswith('/**'):
                continue
            typedef_match = _re.search(r'typedef\s+(?:struct\s+\w*|enum\s+\w*|union\s+\w*|\w+)\s+(\w+)\s*;', line)
            if not typedef_match:
                typedef_match = _re.search(r'typedef\s+(?:struct\s+\w*|enum\s+\w*|union\s+\w*)\s*\{[^}]*\}\s*(\w+)', line)
            if not typedef_match:
                typedef_match = _re.search(r'typedef\s+.*?\(\s*\*\s*(\w+)\s*\)', line)
            if not typedef_match:
                typedef_match = _re.search(r'\benum\s+(\w+)\s*\{', line)
            if not typedef_match:
                typedef_match = _re.search(r'\b(?:struct|union)\s+(\w+)\s*\{', line)
            if not typedef_match:
                func_match = _re.search(r'\b(\w+)\s*\(', line)
                if func_match:
                    name = func_match.group(1)
                    if name not in ('if', 'while', 'for', 'switch', 'return', 'sizeof', 'typedef', 'struct', 'enum', 'union'):
                        names.append(name)
            else:
                names.append(typedef_match.group(1))
        return list(dict.fromkeys(names))


    def remove_macro_systemapi(self, content: str) -> Tuple[str, int]:
        """删除带 @systemapi 注释的 #define 宏定义（含续行）。
        Clang AST 不含宏节点，需用正则补充扫描。
        Regex 主流程中已处理，此方法供 Clang 路径补充调用。
        """
        lines = content.split('\n')
        ranges = self._find_macro_removal_ranges(lines)
        if not ranges:
            return content, 0

        to_remove = set()
        for start, end in ranges:
            for k in range(start, end + 1):
                to_remove.add(k)
        new_lines = [lines[idx] for idx in range(len(lines)) if idx not in to_remove]
        return '\n'.join(new_lines), len(ranges)


    def remove_ranges_from_source(self, source_lines: List[str],
                                  ranges: List[Tuple[int, int, str]]) -> Tuple[List[str], int]:
        """从源文件中删除指定行范围。
        处理步骤：
        1. 按起始行号排序
        2. 合并重叠或相邻的范围（如 typedef enum 同时匹配 TypedefDecl 和 EnumDecl）
        3. 从文件末尾向前删除，避免行号偏移
        """
        if not ranges:
            return source_lines, 0

        # 排序并合并重叠范围
        sorted_ranges = sorted(ranges, key=lambda x: x[0])
        merged = [sorted_ranges[0]]
        for start, end, name in sorted_ranges[1:]:
            if start <= merged[-1][1] + 1:
                merged[-1] = (merged[-1][0], max(merged[-1][1], end), merged[-1][2])
            else:
                merged.append((start, end, name))

        # 从末尾向前删除，避免前面的删除影响后面的行号
        merged.sort(key=lambda x: x[0], reverse=True)

        result = source_lines.copy()
        removed_count = 0

        for start, end, name in merged:
            start_idx = start - 1
            end_idx = end - 1

            if 0 <= start_idx < len(result) and 0 <= end_idx < len(result):
                del result[start_idx:end_idx + 1]
                removed_count += 1

        return result, removed_count


    def remove_unused_includes(self, content: str, current_file: Path) -> Tuple[str, int]:
        """删除不再使用的 #include "xxx.h"（本地引用）。
        系统头文件（<xxx.h> 形式）不会被清理。
        判断逻辑：提取被引用文件中定义的所有符号名，检查这些符号
        是否在删除 @systemapi 后的剩余内容中被使用。全未使用则移除。
        """
        lines = content.split('\n')
        lines_to_remove = self._find_unused_local_includes(lines, current_file)

        if not lines_to_remove:
            return content, 0

        new_lines = [line for idx, line in enumerate(lines) if idx not in lines_to_remove]
        return '\n'.join(new_lines), len(lines_to_remove)

    @staticmethod
    def _skip_block_comment(lines: List[str], j: int, stripped: str) -> int:
        """跳过块注释，返回注释结束后的行号"""
        if '*/' in stripped:
            return j + 1
        j += 1
        while j < len(lines) and '*/' not in lines[j]:
            j += 1
        if j < len(lines):
            j += 1
        return j

    def _skip_attached_comments(self, lines: List[str], j: int) -> Optional[int]:
        """跳过紧贴的后续注释块（无空行分隔），返回下一个待处理行号。
        遇到空行后的注释则返回 None（表示不关联）。
        """
        crossed_blank = False
        while j < len(lines):
            stripped = lines[j].strip()
            if stripped == '':
                crossed_blank = True
                j += 1
                continue
            if crossed_blank and (stripped.startswith('//') or stripped.startswith('/*')
                                  or stripped.startswith('/**') or stripped.startswith('/*!')):
                return None
            if not crossed_blank:
                if stripped.startswith('//'):
                    j += 1
                    continue
                if stripped.startswith('/*') or stripped.startswith('/**') or stripped.startswith('/*!'):
                    j = self._skip_block_comment(lines, j, stripped)
                    continue
                if stripped.startswith('*') and not stripped.startswith('*/'):
                    j += 1
                    continue
            break
        return j

    def _resolve_decl_end(self, lines: List[str], j: int) -> Optional[int]:
        """根据声明行类型，查找声明结束行号。遇到预处理指令返回 None（不删除）"""
        decl_line = lines[j].strip()
        if re.match(r'#\s*(if|ifdef|ifndef|endif|else|elif|include|pragma|error|warning)\b', decl_line):
            return None
        if re.match(r'#\s*define', decl_line):
            return self._find_define_end(lines, j)
        if 'typedef' in decl_line and ('enum' in decl_line or 'struct' in decl_line or 'union' in decl_line):
            return self._find_typedef_aggregate_end(lines, j, decl_line)
        if decl_line.startswith('typedef'):
            return self._find_typedef_simple_end(lines, j)
        if re.match(r'^(struct|class|enum|union)\s+\w+\s*\{', decl_line):
            return self._find_brace_block_end(lines, j)
        return j

    def _regex_handle_line_comment(self, lines: List[str], i: int,
                                   to_remove: List[bool]) -> Tuple[int, int]:
        """处理 // 或 //! 行注释，若含 @systemapi 则标记删除范围。
        连续的 // 行视为同一组注释，一起删除。
        返回 (下一扫描位置, 删除计数)"""
        comment_lines = []
        comment_end = i
        while comment_end < len(lines) and lines[comment_end].strip().startswith('//'):
            comment_lines.append(lines[comment_end])
            comment_end += 1

        comment_text = '\n'.join(comment_lines)
        if not self._has_strict_systemapi(comment_text):
            return comment_end, 0

        in_aggregate, agg_start, agg_type = self._regex_check_in_aggregate(lines, i)
        if in_aggregate and agg_start >= 0:
            if agg_type in ('struct', 'enum', 'union'):
                if self._regex_should_skip_struct_field(lines, agg_start):
                    return comment_end, 0
            aggregate_end = self._regex_find_aggregate_end(lines, agg_start)
            for k in range(agg_start, aggregate_end + 1):
                if k < len(to_remove):
                    to_remove[k] = True
            return aggregate_end + 1, 1

        decl_end = self._regex_find_decl_end(lines, comment_end)
        if decl_end is not None:
            actual_start = self._find_contiguous_comment_start(lines, i)
            for k in range(actual_start, decl_end + 1):
                if k < len(to_remove):
                    to_remove[k] = True
            return decl_end + 1, 1

        return comment_end, 0

    @staticmethod
    def _find_empty_conditional_range(lines: List[str], start: int) -> Optional[int]:
        """从 #if/#ifdef/#ifndef 行开始，查找对应的空条件块结束行。
        如果该条件块内部无实质内容（只有预处理指令和空行），返回 #endif 行号；否则返回 None。"""
        depth = 1
        j = start + 1
        inner_non_empty = False
        while j < len(lines) and depth > 0:
            s = lines[j].strip()
            if re.match(r'#\s*if(?:n?def)?\b', s):
                depth += 1
            elif re.match(r'#\s*endif\b', s):
                depth -= 1
                if depth == 0:
                    break
            if (s != ''
                    and not re.match(r'#\s*(?:if|ifdef|ifndef|endif|else|elif)\b', s)
                    and not re.match(r'^(;\s*)+$', s)):
                inner_non_empty = True
            j += 1
        if j < len(lines) and not inner_non_empty:
            return j
        return None

    def _is_content_effectively_empty(self, content: str) -> bool:
        """判断文件内容是否只剩空行、include guard、版权头注释，无任何实际代码。
        版权头判断标准：文件开头的连续注释块（含 Copyright/License 等关键词）。
        """
        lines = content.split('\n')
        past_header = False
        for line in lines:
            s = line.strip()
            if s == '':
                continue
            if re.match(r'^#\s*(ifndef|define|endif|pragma\s+once)\b', s):
                continue
            if not past_header:
                if (s.startswith('/*') or s.startswith('/**') or s.startswith('/*!') or
                    s.startswith('//') or s.startswith('*') or s == '*/' or s.endswith('*/')):
                    continue
                past_header = True
            if past_header:
                return False
        return True

    def _remove_deleted_includes_from_file(self, output_file: Path,
                                            deleted_names: Set[str],
                                            deleted_basenames: Set[str]) -> bool:
        """从单个文件中移除对已删除文件的 #include，返回是否有变更"""
        try:
            with open(output_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
        except Exception:
            return False
        lines = content.split('\n')
        new_lines = []
        changed = False
        for line in lines:
            stripped = line.strip()
            m = re.match(r'#\s*include\s+"([^"]+)"', stripped)
            if m:
                inc_path = m.group(1)
                if inc_path in deleted_names or Path(inc_path).name in deleted_basenames:
                    changed = True
                    pass
                    continue
            new_lines.append(line)
        if changed:
            with open(output_file, 'w', encoding='utf-8') as f:
                f.write('\n'.join(new_lines))
            self.stats['includes_removed'] += 1
        return changed

    def _clean_includes_of_deleted_files(self, deleted_names: Set[str],
                                          deleted_basenames: Set[str]) -> None:
        """清理其他文件中对已删除文件的 #include"""
        for output_file in list(self.output_dir.rglob('*.h')):
            if output_file.is_file():
                self._remove_deleted_includes_from_file(output_file, deleted_names, deleted_basenames)

    def _remove_empty_output_files(self) -> None:
        """删除输出目录中内容为空的头文件，并清理其他文件中对它们的 #include"""
        deleted_files = []
        for output_file in list(self.output_dir.rglob('*.h')):
            try:
                with open(output_file, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
            except Exception:
                continue
            if not self._is_content_effectively_empty(content):
                continue
            rel = output_file.relative_to(self.output_dir)
            self.logger.debug(f"  Removing empty header: {rel}")
            deleted_files.append(rel)
            output_file.unlink()
        if not deleted_files:
            return

        self.stats['empty_headers_removed'] = len(deleted_files)
        deleted_names = {str(p) for p in deleted_files}
        deleted_basenames = {p.name for p in deleted_files}
        self._clean_includes_of_deleted_files(deleted_names, deleted_basenames)

    def _validate_single_file_syntax(self, output_file: Path) -> Optional[str]:
        """用 clang 校验单个文件语法，返回错误字符串或 None"""
        cmd = [self.clang_binary, '-x', 'c-header', '-fsyntax-only', '-Wno-everything', str(output_file)]
        try:
            result = subprocess.run(cmd, capture_output=True, timeout=30)
            result.stderr = result.stderr.decode('utf-8', errors='replace')
        except (subprocess.TimeoutExpired, FileNotFoundError):
            return None
        if result.returncode != 0:
            errors = [line.strip() for line in result.stderr.strip().split('\n') if ': error:' in line]
            if errors:
                return '\n'.join(errors)
        return None

    def _validate_output_files(self) -> None:
        """用 clang -fsyntax-only 校验所有修改过的输出文件，语法错误则阻断构建"""
        if self.force_regex or not self.clang_binary:
            return
        modified = set(self.clang_modified_files + self.regex_modified_files)
        if not modified:
            return
        for input_file in sorted(modified):
            rel = input_file.relative_to(self.input_dir)
            output_file = self.output_dir / rel
            if not output_file.exists():
                continue
            errs = self._validate_single_file_syntax(output_file)
            if errs:
                self.validation_errors.append((output_file, errs))
        if self.validation_errors:
            print("\n? ERROR: Output file syntax validation failed (build blocked):")
            print("-" * 70)
            for file_path, errs in self.validation_errors:
                print(f"  File: {file_path.name}")
                for e in errs.split('\n'):
                    print(f"    {e}")
            print()

    @staticmethod
    def _find_brace_end_in_source(source_lines: List[str], idx: int) -> Optional[int]:
        """从含 { 的行开始，查找花括号块结束行号"""
        brace_count = 0
        for k in range(idx, len(source_lines)):
            brace_count += source_lines[k].count('{')
            brace_count -= source_lines[k].count('}')
            if brace_count == 0 and k > idx:
                if k + 1 < len(source_lines) and ';' in source_lines[k + 1]:
                    return k + 2
                return k + 1
        return None

    def _find_declaration_end_in_source(self, source_lines: Optional[List[str]],
                                        start_line: Optional[int]) -> Optional[int]:
        """当 clang AST 未提供 end_line 时，通过扫描源码查找声明结束行"""
        if not source_lines or start_line is None or start_line <= 0:
            return None
        idx = start_line - 1
        if idx >= len(source_lines):
            return start_line
        line = source_lines[idx]
        if '{' in line:
            result = self._find_brace_end_in_source(source_lines, idx)
            return result if result is not None else start_line
        for k in range(idx, len(source_lines)):
            if ';' in source_lines[k]:
                return k + 1
        return start_line


def parse_arguments():
    parser = argparse.ArgumentParser(
        description='Remove APIs with @systemapi tag from C/C++ header files (Hybrid: clang + regex)'
    )

    parser.add_argument('-i', '--input', type=str, required=True, help='Input directory')
    parser.add_argument('-o', '--output', type=str, required=True, help='Output directory')
    parser.add_argument('--napi-dir', type=str, default=None, help='NAPI top-level directory for dependency resolution')
    parser.add_argument('-v', '--verbose', action='store_true', help='Enable verbose output')
    parser.add_argument('--log', type=str, default=None, help='Log file path')
    parser.add_argument('--dry-run', action='store_true', help='Dry run')
    parser.add_argument('--force-regex', action='store_true', help='Force regex fallback (skip clang)')
    parser.add_argument('--extensions', type=str, nargs='+',
                       default=['.h', '.hpp', '.hxx', '.hh', '.inl', '.h++', '.hp'],
                       help='Header file extensions')

    return parser.parse_args()


def _run_dry_mode(processor: SystemApiRemover) -> None:
    print("DRY RUN MODE - No changes will be made")
    print(f"Input directory:  {processor.input_dir}")
    print(f"Output directory: {processor.output_dir}")
    if processor.napi_dir:
        print(f"NAPI directory:   {processor.napi_dir}")
    print("\nFiles that would be processed:")

    for root, dirs, files in os.walk(processor.input_dir):
        root_path = Path(root)
        for file in files:
            file_path = root_path / file
            if processor.is_header_file(file_path):
                print(f"  - {file_path.relative_to(processor.input_dir)}")

    sys.exit(0)


def main():
    args = parse_arguments()

    processor = SystemApiRemover(args.input, args.output, args.napi_dir, args.verbose, args.log,
                                force_regex=getattr(args, 'force_regex', False))

    if args.extensions:
        header_extensions = set(args.extensions)

        def custom_is_header(file_path):
            return file_path.suffix in header_extensions
        processor.is_header_file = custom_is_header

    if args.dry_run:
        _run_dry_mode(processor)

    processor.process_directory()
    processor.print_stats()

    if processor.public_ref_errors:
        sys.exit(1)

    if processor.validation_errors:
        sys.exit(1)


if __name__ == "__main__":
    main()

