#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright (c) 2023 Huawei Device Co., Ltd.
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

import enum
from coreImpl.parser import parser
from coreImpl.check import check, check_syntax
from coreImpl.diff import diff


class ToolNameType(enum.Enum):
    COLLECT = 'collect'
    DIFF = 'diff'
    CHECK = 'check'
    COLLECT_H = 'collect_h'
    COLLECT_FILE = 'collect_file'
    CHECK_SYNTAX = 'check_syntax'


tool_name_type_set = [
    member.value for name_tool,
    member in ToolNameType.__members__.items()
]


class FormatType(enum.Enum):
    JSON = 'json'
    EXCEL = 'excel'


format_set = [
    member.value for name_format,
    member in FormatType.__members__.items()
]


def run_tools(options):
    tool_name = options.tool_name
    print(tool_name)
    if tool_name == ToolNameType["COLLECT"].value:
        parser.parser(options.parser_path)
    elif tool_name == ToolNameType["DIFF"].value:
        diff.process_dir(options.diff_path_old, options.diff_path_new, options.output_path)
    elif tool_name == ToolNameType["CHECK"].value:
        check.curr_entry(options.path, options.checker, options.output)
    elif tool_name == ToolNameType['COLLECT_H'].value:
        parser.parser_direct(options.parser_path, options.dependent_path)
    elif tool_name == ToolNameType['COLLECT_FILE'].value:
        parser.parser_file_level(options.output_path)
    elif tool_name == ToolNameType['CHECK_SYNTAX'].value:
        check_syntax.check_syntax_entrance(options.parser_path, options.dependent_path, options.output_path)
    else:
        print("工具名称错误")


class Config(object):
    name = 'parser'
    version = '0.1.0'
    description = 'Compare the parser the NDKS'
    commands = [
        {
            "name": "--tool-name",
            "abbr": "-N",
            "required": False,
            "choices": tool_name_type_set,
            "type": str,
            "default": ToolNameType["CHECK"].value,
            "help": "工具名称,命令中不写-N的话，默认为check工具"
        },
        {
            "name": "--parser-path",
            "abbr": "-P",
            "required": False,
            "type": str,
            "help": "解析路径"
        },
        {
            "name": "--output-path",
            "abbr": "-O",
            "required": False,
            "type": str,
            "help": "工具输出文件路径"
        },
        {
            "name": "--dependent-path",
            "abbr": "-D",
            "required": False,
            "type": str,
            "help": "依赖文件路径"
        },
        {
            "name": "--codecheck--path",
            "abbr": "--path",
            "required": False,
            "type": str,
            "help": "codecheck解析文件路径"
        },
        {
            "name": "--check-command",
            "abbr": "--checker",
            "required": False,
            "type": str,
            "help": "校验命令"
        },
        {
            "name": "--check-output",
            "abbr": "--output",
            "required": False,
            "type": str,
            "help": "输出路径"
        },
        {
            "name": "--diff-path-old",
            "abbr": "-old",
            "required": False,
            "type": str,
            "help": "旧文件路径"
        },
        {
            "name": "--diff-path-new",
            "abbr": "-new",
            "required": False,
            "type": str,
            "help": "新文件路径"
        }

    ]
