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
import os.path
import re
from typedef.check.check import (CheckOutPut, CheckErrorMessage)


def check_large_hump(api_info, kind, parent_kind):
    api_result_info_list = []
    # 结构体
    if kind == 'STRUCT_DECL':
        api_result_info_list = processing_check_data('LARGE_HUMP', api_info,
                                                     CheckErrorMessage.API_NAME_UNIVERSAL_05.name)
    # 枚举
    if kind == 'ENUM_DECL':
        api_result_info_list = processing_check_data('LARGE_HUMP', api_info,
                                                     CheckErrorMessage.API_NAME_UNIVERSAL_03.name)
    # 联合体
    if kind == 'UNION_DECL':
        api_result_info_list = processing_check_data('LARGE_HUMP', api_info,
                                                     CheckErrorMessage.API_NAME_UNIVERSAL_07.name)
    return api_result_info_list


def check_function_name(api_info, kind, parent_kind):
    api_result_info_list = []
    function_name = api_info['name']
    # 自研函数
    if is_self_developed_function(function_name):
        self_developed_function_result = re.match(r'^[OH|OS]+([\_]([A-Z]+[a-z0-9]*)+)*$', function_name)
        if self_developed_function_result is None:
            chck_output = set_value_to_result(api_info, CheckErrorMessage.API_NAME_UNIVERSAL_01.name)
            api_result_info_list.append(chck_output)
    # 一般函数
    if not is_self_developed_function(function_name):
        ordinary_function_result = re.match(r'^([A-Z][a-z0-9]*)*$', function_name)
        if ordinary_function_result is None:
            chck_output = set_value_to_result(api_info, CheckErrorMessage.API_NAME_UNIVERSAL_10.name)
            api_result_info_list.append(chck_output)
    return api_result_info_list


def set_value_to_result(api_info, command):
    content = api_info['node_content']['content']
    node_name = api_info['name']
    if api_info['kind'] == 'MACRO_DEFINITION' and api_info.get('def_func_name'):
        node_name = api_info.get('def_func_name')
    descriptive_message = CheckErrorMessage.__getitem__(command).value.replace('$$', node_name)
    return CheckOutPut(os.path.abspath(os.path.join(api_info['gn_path'], api_info['location']['location_path'])),
                       api_info['location']['location_line'], command, descriptive_message,
                       content, api_info['location']['location_line'])


def is_self_developed_function(function_name):
    return function_name.startswith('OH_') or function_name.startswith('OS_') or function_name.startswith('HMS_')


def check_variable_name(api_info, kind, parent_kind):
    api_result_info_list = []
    is_const = api_info['is_const']
    # 常量
    if is_const:
        api_result_info_list = processing_check_data('ALL_UPPERCASE_HUMP',
                                                     api_info, CheckErrorMessage.API_NAME_UNIVERSAL_02.name)
    # 全局变量
    if not is_const:
        api_result_info_list = processing_check_data('GLOBAL_VARIABLE', api_info,
                                                     CheckErrorMessage.API_NAME_UNIVERSAL_09.name)
    return api_result_info_list


def check_small_hump(api_info, kind, parent_kind):
    api_result_info_list = []
    # 函数参数
    if parent_kind == 'FUNCTION_DECL':
        api_result_info_list = processing_check_data('SMALL_HUMP', api_info,
                                                     CheckErrorMessage.API_NAME_UNIVERSAL_11.name)
    # 结构体成员
    if parent_kind == 'STRUCT_DECL':
        api_result_info_list = processing_check_data('SMALL_HUMP', api_info,
                                                     CheckErrorMessage.API_NAME_UNIVERSAL_06.name)
    # 联合体成员
    if parent_kind == 'UNION_DECL':
        api_result_info_list = processing_check_data('SMALL_HUMP', api_info,
                                                     CheckErrorMessage.API_NAME_UNIVERSAL_08.name)
    return api_result_info_list


def check_macro_definition(api_info, kind, parent_kind):
    api_result_info_list = []
    name = api_info['name']
    # 宏定义
    if not api_info['is_def_func']:
        result = re.match(CheckName['MACRO_DEFINITION'].value, name)
        if result is None:
            api_result_info_list.append(set_value_to_result(api_info, CheckErrorMessage.API_NAME_UNIVERSAL_12.name))
    # 函数式宏
    if api_info['is_def_func']:
        name = api_info['def_func_name']
        result = re.match(CheckName['MACRO_DEFINITION'].value, name)
        if result is None:
            api_result_info_list.append(set_value_to_result(api_info, CheckErrorMessage.API_NAME_UNIVERSAL_13.name))
    return api_result_info_list


def check_all_uppercase_hump(api_info, kind, parent_kind):
    # 枚举值
    api_result_info_list = processing_check_data('ALL_UPPERCASE_HUMP', api_info,
                                                 CheckErrorMessage.API_NAME_UNIVERSAL_04.name)
    return api_result_info_list


def check_file_name(file_info):
    api_result_info_list = []
    file_name = os.path.basename(file_info['name'])
    result = re.match(CheckName['FILE_NAME'].value, file_name)
    if result is None:
        check_output = CheckOutPut(os.path.abspath(os.path.join(file_info['gn_path'], file_info['name'])), 0,
                                   CheckErrorMessage.API_NAME_UNIVERSAL_14.name,
                                   CheckErrorMessage.API_NAME_UNIVERSAL_14.value.replace('$$', file_name), '', 0)
        api_result_info_list.append(check_output)
    return api_result_info_list


def processing_check_data(function_type, api_info, command):
    api_result_info_list = []
    name = api_info['name']
    result = re.match(CheckName[function_type].value, name)
    if result is None:
        chck_output = set_value_to_result(api_info, command)
        api_result_info_list.append(chck_output)
    return api_result_info_list


class CheckName(enum.Enum):
    LARGE_HUMP = r'^([A-Z][a-z0-9]*)*([\_]([A-Z][a-z0-9]*)*)*$'
    SMALL_HUMP = r'^([a-z][A-Z0-9]*)*([\_]([a-z][A-Z0-9]*)*)*$'
    ALL_UPPERCASE_HUMP = r'^[A-Z]+[0-9]*([\_][A-Z0-9]*)*$'
    GLOBAL_VARIABLE = r'^g_([a-z][A-Z0-9]*)*$'
    FILE_NAME = r'^[a-z]+[a-z0-9]+([\_][a-z0-9]+)*\.h$'
    MACRO_DEFINITION = r'^[\_]*[A-Z]+[0-9]*([\_][A-Z0-9]*)*$'


process_tag_function = {
    # 函数
    'FUNCTION_DECL': check_function_name,
    # 结构体
    'STRUCT_DECL': check_large_hump,
    # 枚举
    'ENUM_DECL': check_large_hump,
    # 联合体
    'UNION_DECL': check_large_hump,
    # 变量
    'VAR_DECL': check_variable_name,
    # 参数
    'PARM_DECL': check_small_hump,
    # 结构体、联合体成员
    'FIELD_DECL': check_small_hump,
    # 宏定义
    'MACRO_DEFINITION': check_macro_definition,
    # 枚举值
    'ENUM_CONSTANT_DECL': check_all_uppercase_hump,
}


def check_api_name(api_info, parent_kind):
    api_result_info_list = []
    kind = api_info['kind']
    if kind not in process_tag_function.keys():
        return api_result_info_list
    name_process = process_tag_function[kind]
    return name_process(api_info, kind, parent_kind)
