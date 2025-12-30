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

import argparse
import re
import sys
import os
import subprocess
import tempfile
from typing import Optional, Tuple, Pattern, List


# 不需要处理的头文件，一般为系统文件或者三方库文件
_DIR_NOT_PROCESS = [
    "aarch64-linux-ohos",
    "arm-linux-ohos",
    "asm-generic",
    "asm-loongarch",
    "asm-mips",
    "asm-riscv",
    "EGL",
    "GLES2",
    "GLES3",
    "i686-linux-ohos",
    "linux",
    "x86_64-linux-ohos",
    "TEEKit"
]


class HeaderProcessor:
    MAX_LINE_LENGTH = 120  # 最大行长度限制（超过则换行显示版本宏）


    def __init__(self):
        # 头文件保护宏正则
        self.guard_pattern = re.compile(r'^#define\s+([A-Za-z0-9_]+_H(_)?)\s*$', re.MULTILINE)

        # 先匹配带@since的注释块
        self.since_comment_pattern = re.compile(
            r'(?P<comment>/\*\*[^\*]*(?:\*(?!/)[^\*]*)*@since\s+\S+[^\*]*(?:\*(?!/)[^\*]*)*\*/)'  # 带@since的完整注释块
            r'(?P<whitespace>[\s\n\r]*)'  # 注释块后仅允许空格/制表符（无空行)
            r'(?P<code_start>\w+|extern)', # 后续代码的起始特征（字段/接口）
            re.MULTILINE | re.DOTALL
        )

        # 字段判断正则
        self.extern_field_start_pattern = re.compile(r'^extern\s+(?!\"C\"\s*\{)[^(){}\[\]]*?;', re.DOTALL)
        # 接口判断正则
        self.func_interface_start_pattern = re.compile(
            r'^(?!typedef|.*inline)'  # 排除typedef和含inline的声明
            r'[\w\s\*]+?\b\w+\s*\('  # 匹配返回值+函数名+左括号（支持指针类型）
            r'[^;]*?'  # 匹配任意参数（包括__restrict、const等修饰符），直到遇到分号
            r'\)\s*;'  # 右括号+分号（确保是纯声明，非函数体）
            , re.MULTILINE | re.DOTALL
        )

        # @since 支持: 
        #   - 纯数字: 22
        #   - 三段: 26.0.1
        #   - 三段+括号: 5.0.3(15)
        self.since_pattern = re.compile(
            r'@since\s+(\d+(?:\.\d+\.\d+(?:\(\d+\))?)?)'
        )
        # @deprecated since仅支持数字格式
        self.deprecated_pattern = re.compile(r'@deprecated since\s+(\d+)')

        # 严格注释验证正则（允许*/前有空格/制表符）
        self.strict_comment_pattern = re.compile(r'^\s*\*/\s*$', re.MULTILINE)


    def process_file(self, file_path: str) -> None:
        """处理单个头文件"""
        try:
            with open(file_path, 'r+', encoding='utf-8') as f:
                content = f.read()
                modified, has_changes = self._process_content(content)

                if has_changes:
                    f.seek(0)
                    f.write(modified)
                    f.truncate()
                    print(f"modify success: {file_path}")
                else:
                    print(f"No modifications are needed: {file_path}")
        except Exception as e:
            print(f"Processing failed. {file_path}: {str(e)}")


    def _process_content(self, content: str) -> tuple[str, bool]:
        """处理文件内容逻辑：先处理注释块关联的字段/接口，最后添加版本引用"""
        original_content = content
        # 处理所有带@since注释块关联的字段/接口
        content = self._process_since_comment_related_code(content)

        has_changes = content != original_content
        if has_changes:
            # 有改动则添加头文件
            content = self._add_version_include(content)

        return content, has_changes


    def _process_since_comment_related_code(self, content: str) -> str:
        """处理带@since注释块关联的字段或接口"""
        # 找到所有带@since且后续有代码的合规注释块
        comment_matches = list(self.since_comment_pattern.finditer(content))
        # 倒序处理：先修改后面的注释块，避免前面修改导致后面索引错位
        for match in reversed(comment_matches):
            comment_block = match.group('comment')
            whitespace = match.group('whitespace')
             # 代码块起始索引
            code_start_idx = match.start('code_start')

            # 提取注释块后的第一个完整代码块（字段或接口）
            code_block, code_end_idx = self._extract_single_code_block(content, code_start_idx)
            if not code_block:
                continue  # 无有效代码块，跳过

            # 提取版本信息
            since_version = self._extract_tag(comment_block, self.since_pattern)
            if not since_version:
                continue  # 无@since版本，跳过
            deprecated_version = self._extract_tag(comment_block, self.deprecated_pattern) or '0'

            # 根据版本信息生成宏
            version_macro = self._get_version_macro(since_version, deprecated_version)
            # 格式化代码块
            formatted_code = self._format_declaration(code_block.rstrip(';'), version_macro) + ';'

            # 替换原注释块+代码块内容
            old_segment = comment_block + whitespace + content[code_start_idx:code_end_idx]
            new_segment = comment_block + whitespace + formatted_code
            content = content.replace(old_segment, new_segment, 1)

        return content


    def _extract_single_code_block(self, content: str, start_idx: int) -> Tuple[Optional[str], int]:
        """从start_idx提取第一个完整代码块（字段或接口），仅取紧接注释块的第一个"""
        remaining_content = content[start_idx:]

        # 判断是否为extern字段
        field_match = self.extern_field_start_pattern.match(remaining_content)
        if field_match:
            field_content = field_match.group(0).strip()
            end_idx = start_idx + field_match.end()
            return (field_content, end_idx)

        # 判断是否为函数接口（支持多行，通过括号配对确认完整性）
        interface_match = self.func_interface_start_pattern.match(remaining_content)
        if interface_match:
            interface_content = interface_match.group(0).strip()
            end_idx = start_idx + interface_match.end()
            # 二次确认括号完整性
            if interface_content.count('(') == interface_content.count(')'):
                return (interface_content, end_idx)

        # 非字段/接口或不完整代码块
        return (None, -1)


    def _add_version_include(self, content: str) -> str:
        """在头文件保护宏后添加#include "info/application_target_sdk_version.h"，无保护宏则在第一个#include前添加"""
        target_include = '#include "info/application_target_sdk_version.h"'

        # 尝试在头文件保护宏后添加
        def replacer(match):
            return f"{match.group(0)}\n{target_include}"
        content_with_include = self.guard_pattern.sub(replacer, content, count=1)

        # 若未添加成功（未匹配到保护宏），在第一个#include前插入
        if target_include not in content_with_include:
            first_include_match = re.search(r'^\s*#include', content_with_include, re.MULTILINE)
            if first_include_match:
                insert_pos = first_include_match.start()
                content_with_include = (
                    content_with_include[:insert_pos]
                    + f"{target_include}\n"
                    + content_with_include[insert_pos:]
                )

        return content_with_include


    def _get_version_macro(self, since_version: str, deprecated_version: str) -> str:
        """
        根据 @since 的值生成对应的 API 可用性宏。
        支持格式：
        - 纯数字：15                → __API_VERSION(15,0,0)
        - 三段式：15.0.0 / 15.0.1   → __API_VERSION(15,0,0) / __API_VERSION(15,0,1)
        - 四段式：5.0.3(15)         → __API_VERSION(15,0,0)  （取括号内为主版本）
        """
        # 匹配 x.y.z(n) 格式，例如 5.0.3(15)
        distributeos_pattern = re.compile(r'^(\d+)\.(\d+)\.(\d+)\((\d+)\)$')
        # 匹配 x.y.z 格式，例如 15.0.1
        triple_pattern = re.compile(r'^(\d+)\.(\d+)\.(\d+)$')

        major = minor = patch = None

        if since_version.isdigit():
            # 格式1: @since 15
            major = since_version
            minor = '0'
            patch = '0'
        elif distributeos_pattern.match(since_version):
            # 格式2: @since 5.0.3(15) → 使用括号内的 15 作为主版本
            n = distributeos_pattern.match(since_version).group(4)
            major = n
            minor = '0'
            patch = '0'
        elif triple_pattern.match(since_version):
            # 格式3/4: @since 15.0.0 或 15.0.1
            m = triple_pattern.match(since_version)
            major = m.group(1)
            minor = m.group(2)
            patch = m.group(3)
        else:
            # 未知格式，保守处理为纯数字（可选：也可报错或跳过）
            raise ValueError(f"Invalid since_version format: {since_version}")
            major = since_version
            minor = '0'
            patch = '0'

        base_macro = f'__attribute__((__availability__(ohos, introduced={major}.{minor}.{patch})))'
        return base_macro


    def _format_declaration(self, decl: str, macro: str) -> str:
        """格式化声明：根据行长度决定单行或换行显示，保留原缩进"""
        last_line = decl.split('\n')[-1]
        # 计算原缩进长度
        indent_length = len(last_line) - len(last_line.lstrip())
        indent = ' ' * indent_length

        # 尝试单行显示
        combined = f"{decl.rstrip()} {macro}"
        if len(combined) <= self.MAX_LINE_LENGTH:
            return combined

        # 单行超宽，换行显示宏
        return f"{decl.rstrip()}\n{indent}{macro}"


    def _extract_tag(self, text: str, pattern: re.Pattern) -> Optional[str]:
        """从文本中提取指定标签的值（如@since、@deprecated since）"""
        tag_match = pattern.search(text)
        return tag_match.group(1) if tag_match else None


def _is_blacklist_dir(rel_path: str) -> bool:
    """判断目录是否需要处理（仅检查第一级子目录）"""
    first_level_dir = rel_path.split(os.sep)[0]
    return first_level_dir in _DIR_NOT_PROCESS


def _process_root_files(root: str, processor: HeaderProcessor) -> None:
    """处理根目录下的文件"""
    for file_name in os.listdir(root):
        if file_name.endswith('.h'):
            processor.process_file(os.path.join(root, file_name))


def _process_subdir_files(root: str, processor: HeaderProcessor) -> None:
    """处理子目录下的所有.h文件"""
    for file_name in os.listdir(root):
        if file_name.endswith('.h'):
            processor.process_file(os.path.join(root, file_name))


def check_file_api_version(root: str, sdk_api_version: int) -> List[str]:
    violation_files = []
    since_pattern = re.compile(r'@since\s+([^\s\n\r]+)')

    for file_name in os.listdir(root):
        if not file_name.endswith('.h'):
            continue
        file_path = os.path.join(root, file_name)

        file_results = process_single_file(file_path, since_pattern, sdk_api_version)
        if file_results:
            violation_files.append(file_path)
    return violation_files


def process_single_file(file_path: str, since_pattern: Pattern, sdk_api_version: int) -> Optional[List[str]]:
    """处理单个文件，返回匹配的since值列表"""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
    except Exception as e:
        print(f"读取文件失败")
        return None

    matches = since_pattern.findall(content)
    if not matches:
        return None

    # 检查是否需要运行解析器
    if _has_violation_version(matches, sdk_api_version):
        return matches

    return None


def _has_violation_version(matches: List[str], sdk_api_version: int) -> bool:
    """检查是否存在违规版本号"""
    for since_value in matches:
        if not since_value.isdigit():
            continue
        if int(since_value) > sdk_api_version:
            return True
    return False


def run_capi_parser(input_path, sdk_api_version):
    """
    调用Python脚本并传递--input参数
    Args:
        script_path: 要调用的Python脚本路径
        input_path: 输入文件/文件夹路径
    """
    # 获取当前脚本的绝对路径
    current_script_path = os.path.abspath(__file__)
    script_path = os.path.join(os.path.dirname((current_script_path)), "parse_interfaces_since.py")

    # 创建临时文件并写入所有路径
    with tempfile.NamedTemporaryFile(mode='w', delete=False, suffix='.txt') as f:
        for path in input_path:
            f.write(f"{path}\n")
        input_list_filename = f.name
    try:
        # 使用当前Python解释器运行脚本
        result = subprocess.run([
            sys.executable,  # 使用当前Python解释器
            script_path,
            '--input', str(input_list_filename),
            '--sdk-api-version', str(sdk_api_version)
        ], capture_output=True, text=True, check=True)

        if result.stdout:
            print(f"API校验成功: {result.stdout}")

    except subprocess.CalledProcessError as e:
        err_msg = f"校验API版本失败，返回: {e.stderr}"
        raise ValueError(err_msg)
    except FileNotFoundError:
        err_msg = f"文件未找到: {script_path}"
        raise ValueError(err_msg)
    except Exception as e:
        err_msg = f"执行过程中发生错误: {e}"
        raise ValueError(err_msg)

    finally:
        # 确保临时文件被清理
        try:
            if os.path.exists(input_list_filename):
                os.unlink(input_list_filename)
                print(f"临时文件已清理: {input_list_filename}")
        except Exception as cleanup_error:
            print(f"清理临时文件时出错: {cleanup_error}")


def add_files_to_process(header_path, recursive=True):
    """遍历目录并处理符合条件的头文件"""
    abs_root_dir = os.path.abspath(header_path)
    header_processor = HeaderProcessor()

    for root, dirs, files in os.walk(abs_root_dir, topdown=True):
        rel_dir_path = os.path.relpath(root, abs_root_dir)

        if root == abs_root_dir:
            _process_root_files(root, header_processor)
            continue

        if _is_blacklist_dir(rel_dir_path):
            dirs[:] = []
            print(f"the dir is in blacklists: {root}")
            continue

        _process_subdir_files(root, header_processor)


def check_api_version_method(options):
    """遍历目录并检查API LEVEL"""
    abs_root_dir = os.path.abspath(options.input)
    sdk_api_version = options.sdk_api_version
    if not sdk_api_version.isdigit():
        raise ValueError(f"api version must be digits!")
    sdk_version_num = int(sdk_api_version)
    if sdk_version_num == 0:
        print("无需校验！")
        return

    violation_files = []  # 保存违规文件列表
    for root, dirs, files in os.walk(abs_root_dir, topdown=True):
        violation_files.extend(check_file_api_version(root, sdk_version_num))

    if violation_files:
        run_capi_parser(violation_files, options.sdk_api_version)


def main():
    parser = argparse.ArgumentParser(description="Process ndk header files to add version macros.")
    parser.add_argument('--input', required=True, help="头文件路径")
    parser.add_argument('--sdk-api-version', required=True, help="当前构建API版本")
    args = parser.parse_args()

    if not os.path.exists(args.input):
        print(f"ndk header path does not exist -> {args.input}")
        exit(1)

    check_api_version_method(args)

    add_files_to_process(args.input)


if __name__ == '__main__':
    sys.exit(main())
