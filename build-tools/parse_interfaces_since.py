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
import tempfile
from typing import List, Dict, Set, Optional, Any
import clang.cindex
from clang.cindex import Config, Index, CursorKind, TypeKind


class InterfaceExtractor:
    """接口提取类，封装所有相关功能"""

    def __init__(self, libclang_path: str):
        """初始化Clang配置"""
        self._configure_clang(libclang_path)
        # 记录已经处理过的枚举名称、结构体和联合体，避免重复处理
        self.processed_enums: Set[str] = set()
        self.processed_structs: Set[str] = set()
        self.processed_unions: Set[str] = set()


    def extract_interfaces(self, filename: str) -> List[Dict]:
        """提取文件中的所有接口"""
        abs_filename = os.path.abspath(filename)

        # 编译参数
        args = [
            '-x', 'c++',
            '-std=c++11', # 编译标准
            '-D__OH_AVAILABILITY(x)=',  # 忽略可用性属性
            '-D__OH_VERSION(a,b)=',     # 忽略版本宏
            '-I./include', # 添加头文件搜索路径
        ]

        index = None
        tu = None
        try:
            # 创建并解析TU
            index = Index.create()
            tu = index.parse(abs_filename, args=args)
        except Exception as e:
            err_msg = f"Clang parsing {abs_filename} failed for: {e}"
            raise ValueError(err_msg)

        interfaces = []
        self.processed_enums.clear()    # 清空已处理枚举
        self.processed_structs.clear()  # 清空已处理结构体
        self.processed_unions.clear()   # 清空已处理联合体

        def traverse_ast(cursor):
            """遍历AST的回调函数"""
            if cursor.location.file and cursor.location.file.name == abs_filename:
                try:
                    if cursor.kind == CursorKind.ENUM_DECL:
                        self._process_enum_decl(cursor, interfaces)
                    elif cursor.kind == CursorKind.UNION_DECL:
                        self._process_union_decl(cursor, interfaces)
                    elif cursor.kind == CursorKind.STRUCT_DECL:  # 处理结构体声明
                        self._process_struct_decl(cursor, interfaces)
                    elif cursor.kind == CursorKind.TYPEDEF_DECL:
                        self._process_typedef_decl(cursor, interfaces)
                    else:
                        self._process_other_declarations(cursor, interfaces)
                except Exception as e:
                    print(f"处理节点时出错 {cursor.kind.name}: {e}")

            # 递归处理子节点
            for child in cursor.get_children():
                traverse_ast(child)

        try:
            traverse_ast(tu.cursor)
        except Exception as e:
            print(f"遍历AST时出错: {e}")
        finally:
            if tu is not None:
                if hasattr(tu, 'dispose'):
                    tu.dispose()
                else:
                    del tu
            if index is not None:
                if hasattr(index, 'dispose'):
                    index.dispose()
                else:
                    del index
        return interfaces


    def _configure_clang(self, libclang_path: str) -> None:
        """配置Clang库路径"""
        if not Config.loaded:
            if os.path.exists(libclang_path):
                Config.set_library_file(libclang_path)
            else:
                print(f"Clang库路径不存在: {libclang_path}，使用系统默认路径")


    def _extract_since_version(self, comment: str) -> Optional[str]:
        """提取since版本号"""
        if not comment:
            return None
        matches = re.findall(r'@since\s+([^\s\n\r]+)', comment)
        # 出现多段注释且@since有多个时，使用最后一个作为判断标准
        return matches[-1] if matches else None


    def _create_interface_info(self, cursor, node_type: str, interface_name: Optional[str] = None, parent_type: Optional[str] = None) -> Dict[str, Any]:
        """创建统一的接口信息字典"""
        # 根据参数决定interface_name
        if interface_name is None or interface_name == "":
            interface_name = cursor.spelling

        return {
            'interface_name': interface_name,
            'since_version': self._extract_since_version(cursor.raw_comment),
            'node_type': node_type,
            'cursor_kind': cursor.kind.name,
            'location': f"{cursor.location.file.name}:{cursor.location.line}",
            'comment': cursor.raw_comment.strip() if cursor.raw_comment else "",
            'display_name': cursor.displayname,
            'parent_type': parent_type,  # 父节点类型
            'line': f"(行号:{cursor.location.line})"
        }


    def _process_member(self, cursor, interfaces: List[Dict], parent_name: str, member_type: str) -> None:
        """统一的成员处理函数"""
        if cursor.raw_comment and "@since" in cursor.raw_comment:
            interface_info = self._create_interface_info(
                cursor, f"{member_type}_member", cursor.spelling, parent_name
            )
            interfaces.append(interface_info)


    def _process_composite_decl(self, cursor, interfaces: List[Dict], decl_type: str) -> None:
        """处理复合类型声明（枚举、结构体、联合体）"""
        if not cursor.spelling:
            return

        type_name = cursor.spelling
        # 检查是否已处理过
        processed_sets = {
            "enum": self.processed_enums,
            "struct": self.processed_structs,
            "union": self.processed_unions
        }

        if decl_type in processed_sets and type_name in processed_sets[decl_type]:
            return

        # 检查类型本身的@since注释
        if cursor.raw_comment and "@since" in cursor.raw_comment:
            interface_info = self._create_interface_info(cursor, decl_type, type_name)
            interfaces.append(interface_info)
            if decl_type not in processed_sets:
                processed_sets[decl_type] = set()
            processed_sets[decl_type].add(type_name)

        # 处理成员
        member_kind = CursorKind.ENUM_CONSTANT_DECL if decl_type == "enum" else CursorKind.FIELD_DECL
        for child in cursor.get_children():
            if child.kind == member_kind:
                self._process_member(child, interfaces, type_name, decl_type)


    def _process_enum_decl(self, cursor, interfaces: List[Dict]) -> None:
        """处理枚举类型声明"""
        self._process_composite_decl(cursor, interfaces, "enum")


    def _process_struct_decl(self, cursor, interfaces: List[Dict]) -> None:
        """处理结构体类型声明"""
        self._process_composite_decl(cursor, interfaces, "struct")


    def _process_union_decl(self, cursor, interfaces: List[Dict]) -> None:
        """处理联合体类型声明"""
        self._process_composite_decl(cursor, interfaces, "union")


    def _process_typedef_decl(self, cursor, interfaces: List[Dict]) -> None:
        """处理typedef声明"""
        underlying_type = cursor.underlying_typedef_type
        if not underlying_type:
            return

        # 处理 elaborated type (通常是枚举、结构体、联合体)
        if underlying_type.kind == TypeKind.ELABORATED:
            self._process_elaborated_typedef(cursor, interfaces)
        # 处理函数指针
        elif underlying_type.kind == TypeKind.POINTER:
            self._process_function_pointer_typedef(cursor, interfaces)


    def _process_elaborated_typedef(self, cursor, interfaces: List[Dict]) -> None:
        """处理 elaborated typedef (枚举、结构体、联合体)"""
        underlying_decl = cursor.underlying_typedef_type.get_declaration()

        # 根据底层声明类型分别处理
        type_handlers = {
            CursorKind.UNION_DECL: ("union", self.processed_unions),
            CursorKind.STRUCT_DECL: ("struct", self.processed_structs),
            CursorKind.ENUM_DECL: ("enum", self.processed_enums)
        }

        if underlying_decl.kind in type_handlers:
            type_name, processed_set = type_handlers[underlying_decl.kind]
            self._process_typedef_composite(cursor, underlying_decl, interfaces, type_name, processed_set)


    def _process_typedef_composite(self, cursor, underlying_decl, interfaces: List[Dict],
                                  type_name: str, processed_set: set) -> None:
        """统一处理typedef复合类型（枚举、结构体、联合体）"""
        # 检查是否已处理
        if cursor.spelling in processed_set:
            return

        # 处理typedef声明
        if cursor.raw_comment and "@since" in cursor.raw_comment:
            interface_info = self._create_interface_info(cursor, f"typedef_{type_name}")
            interfaces.append(interface_info)

        # 处理成员
        member_kind = CursorKind.ENUM_CONSTANT_DECL if type_name == "enum" else CursorKind.FIELD_DECL
        for child in underlying_decl.get_children():
            if child.kind == member_kind:
                self._process_member(child, interfaces, cursor.spelling, type_name)


    def _process_enum_typedef(self, cursor, interfaces: List[Dict]) -> None:
        """处理枚举typedef（兼容旧版本调用）"""
        underlying_decl = cursor.underlying_typedef_type.get_declaration() if cursor.underlying_typedef_type else None
        if underlying_decl:
            self._process_typedef_composite(cursor, underlying_decl, interfaces, "enum", self.processed_enums)


    def _process_function_pointer_typedef(self, cursor, interfaces: List[Dict]) -> None:
        """处理函数指针typedef"""
        if cursor.raw_comment and "@since" in cursor.raw_comment:
            interface_info = self._create_interface_info(cursor, "typedef_function_pointer")
            interfaces.append(interface_info)


    def _process_other_declarations(self, cursor, interfaces: List[Dict]) -> None:
        """处理其他类型的声明（函数、变量、结构体等）"""
        node_type_map = {
            CursorKind.FUNCTION_DECL: "function",
            CursorKind.VAR_DECL: "variable",
        }

        node_type = node_type_map.get(cursor.kind)
        if node_type and cursor.raw_comment and "@since" in cursor.raw_comment:
            interface_info = self._create_interface_info(cursor, node_type)
            interfaces.append(interface_info)


def get_libclang_path() -> str:
    """获取libclang库路径"""
    current_script_path = os.path.abspath(__file__)
    great_grandparent_dir = os.path.dirname(
        os.path.dirname(
            os.path.dirname(
                os.path.dirname(current_script_path)
            )
        )
    )

    lib_path = "prebuilts/clang/ohos/linux-x86_64/llvm/lib/libclang.so"
    libclang_path = os.path.join(great_grandparent_dir, lib_path)
    return libclang_path


def extract_include_part_str(path_str: str) -> str:
    """提取include及之后的部分"""
    path_parts = path_str.split(os.sep)
    try:
        include_index = path_parts.index('include')
    except ValueError:
        return path_str
    return os.sep.join(path_parts[include_index:])


def splice_check_results(interfaces: List[Dict], sdk_api_version: str, path: str,
        violation_list: List[str] = None) -> None:
    """拼接检查结果"""
    if not sdk_api_version.isdigit():
        raise ValueError(f"--sdk-api-version must be digits!")
    sdk_version_num = int(sdk_api_version)

    for interface in interfaces:
        since_version = interface.get('since_version')
        if not since_version or not since_version.isdigit() or int(since_version) <= sdk_version_num:
            continue

        # 错误信息格式拼接
        line_parts = [path]

        # 处理结构体/联合体成员的特殊情况
        if interface.get('node_type') and interface.get('parent_type'):
            line_parts.extend([interface['parent_type'], interface['interface_name']])
        else:
            line_parts.append(interface['interface_name'])
        violation_line = "{}{}\n".format("#".join(line_parts), interface['line'])

        # 如果传入了violation_list，也追加到该列表中
        if violation_list is not None:
            violation_list.append(violation_line)


def find_since_define_pattern_with_line_numbers(file_path):
    """在文件中查找匹配指定正则表达式的模式，并返回包含行号的信息"""
    # 正则表达式格式:包括@since注释块、可选的@version注释、#define结束标志
    pattern = r'^\s*\* @since (\d+)(?:\s*\*\s*@version \d+(?:\.\d+)?)?\s*\*/\s*\n#define\s+(\w+)'

    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            content = file.read()

        matches_info = []
        for match in re.finditer(pattern, content, re.MULTILINE | re.DOTALL):
            since_number = match.group(1)
            macro_name = match.group(2)

            # 计算行号：统计 match.start() 之前的换行符数量
            line_number = content.count('\n', 0, match.start()) + 1

            # 获取 #define 所在的具体行
            match_text = match.group(0)

            # 计算 #define 在匹配文本中的相对位置
            define_pos_in_match = match_text.find('#define')

            if define_pos_in_match != -1:
                # 计算 #define 在完整内容中的绝对位置
                define_abs_pos = match.start() + define_pos_in_match
                # 重新计算行号，这次是基于 #define 的位置
                define_line_number = content.count('\n', 0, define_abs_pos) + 1

                matches_info.append({
                    'since_number': since_number,
                    'macro_name': macro_name,
                    'line_number': define_line_number,
                })
        return matches_info
    except FileNotFoundError:
        logging.error(f"文件 {file_path} 不存在")
        return []
    except Exception as e:
        logging.error(f"读取文件 {file_path} 时出错: {e}")
        return []


def replace_pragma_pack(file_paths):
    """查找并替换 #pragma pack(数字) 为空白行"""
    # 读取输入文件内容
    with open(file_paths, 'r', encoding='utf-8') as f:
        content = f.read()

    # 正则表达式匹配 #pragma pack(数字) 模式
    pattern = r'#pragma\s+pack\(\d+\)'

    matches = re.findall(pattern, content, re.DOTALL)
    if matches:
        # 使用正则表达式替换匹配的行为空行
        new_content = re.sub(pattern, '', content, flags=re.MULTILINE)

        # 创建临时文件
        temp_fd, temp_path = tempfile.mkstemp(suffix='.txt', prefix='temp_', text=True)
        try:
            # 写入临时文件
            with os.fdopen(temp_fd, 'w', encoding='utf-8') as f:
                f.write(new_content)
            print(f"已创建临时文件: {temp_path}")
            return temp_path
        except Exception as e:
            os.close(temp_fd)
            if os.path.exists(temp_path):
                os.unlink(temp_path)
            raise e

    else:
        print(f"{file_paths} 文件未找到匹配")
        return None


def check_files_for_pattern(file_paths: str, interfaces: List[Dict]):
    """检查多个文件中是否存在该模式，并记录行号"""
    # 使用新的函数获取包含行号的匹配信息
    matches_info = find_since_define_pattern_with_line_numbers(file_paths)

    if matches_info:
        for i, match_info in enumerate(matches_info, 1):
            since_number = match_info['since_number']
            macro_name = match_info['macro_name']
            line_number = match_info['line_number']

            interface_info = {
                'interface_name': macro_name,
                'since_version': since_number,
                'node_type': "macro",
                'cursor_kind': "",
                'location': f"{file_paths}:{line_number}",
                'comment': match_info.get('match_text', ''),
                'display_name': "",
                'parent_type': "",
                'line': f"(行号:{str(line_number)})"
            }
            interfaces.append(interface_info)
    else:
        print(f"{file_paths} 文件未找到匹配")


def process_with_temp_file(extractor: InterfaceExtractor, temp_path: str):
    """使用临时文件处理接口信息"""
    try:
        # 从临时文件提取接口信息
        return extractor.extract_interfaces(temp_path)
    except FileNotFoundError:
        err_msg = f"临时文件未找到: {temp_path}"
        raise ValueError(err_msg)
    except Exception as e:
        err_msg = f"提取接口时发生错误: {e}"
        raise ValueError(err_msg)
    finally:
        # 确保清理临时文件
        try:
            if os.path.exists(temp_path):
                os.unlink(temp_path)
                print(f"已清理临时文件: {temp_path}")
        except Exception as cleanup_error:
            print(f"清理临时文件时出错: {cleanup_error}")


def get_interfaces_info(path: str):
    """获取接口信息"""
    # 初始化提取器
    extractor = InterfaceExtractor(get_libclang_path())

    temp_path = replace_pragma_pack(path)

    # 如果使用临时文件，确保清理
    if temp_path:
        return process_with_temp_file(extractor, temp_path)
    else:
        # 直接处理原始文件
        return extractor.extract_interfaces(path)


def main():
    """主函数"""
    parser = argparse.ArgumentParser(description="提取带有@since注解的接口")
    parser.add_argument('--input', required=True, help="头文件路径列表")
    parser.add_argument('--sdk-api-version', required=True, help="当前构建API版本")

    args = parser.parse_args()

    if not os.path.exists(args.input):
        print(f"header path list does not exist -> {args.input}")
        exit(1)

    # 从文件读取输入路径
    try:
        with open(args.input, 'r', encoding='utf-8') as f:
            input_paths = [line.strip() for line in f if line.strip()]
    except Exception as e:
        print(f"错误: 无法读取输入文件 {args.input}: {e}", file=sys.stderr)
        sys.exit(1)

    # 处理每个输入路径
    violation_lines = []
    for i, path in enumerate(input_paths, 1):
        # 检查输入文件
        if not os.path.exists(path):
            continue

        interfaces = get_interfaces_info(path)

        #查找是否有define
        check_files_for_pattern(path, interfaces)
        if not interfaces:
            print("未找到带有@since注解的接口")
            continue

        # 处理结果
        file_path = extract_include_part_str(path)
        splice_check_results(interfaces, args.sdk_api_version, file_path, violation_lines)

    if violation_lines:
        check_result = "当前API最高版本号不得高于" + args.sdk_api_version + "，以下接口版本号不合规，请检查！\n"
        check_result += "".join(violation_lines)
        raise ValueError(check_result)


if __name__ == '__main__':
    sys.exit(main())
