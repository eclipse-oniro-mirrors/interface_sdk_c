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

operation_mark_dict = {
    'ADD_FILE': '新增文件',
    'REDUCE_FILE': '删除文件',
    'ADD_API': '新增API',
    'REDUCE_API': '删除API',
    'ADD_DOC': '增加doc',
    'REDUCE_DOC': '删除doc',
    'ADD_DOC_TAG': '增加注释标签',
    'REDUCE_DOC_TAG': '删除注释标签',
    'FUNCTION_PARAM_POS_CHANGE': '函数参数位置改变',

    'DEFINE_NAME_CHANGE': '修改宏名',
    'DEFINE_TEXT_CHANGE': '修改宏文本',

    'FUNCTION_NAME_CHANGE': '修改函数名',
    'FUNCTION_RETURN_CHANGE': '修改函数返回值',
    'FUNCTION_PARAM_NAME_CHANGE': '修改函数参数名',
    'FUNCTION_PARAM_TYPE_CHANGE': '修改函数参数类型',
    'FUNCTION_PARAM_ADD': '增加函数参数',
    'FUNCTION_PARAM_REDUCE': '删除函数参数',

    'STRUCT_NAME_CHANGE': '修改结构体名',
    'STRUCT_MEMBER_NAME_CHANGE': '修改结构体成员名',
    'STRUCT_MEMBER_TYPE_CHANGE': '修改结构体成员类型',
    'STRUCT_MEMBER_ADD': '增加结构体成员',
    'STRUCT_MEMBER_REDUCE': '删除结构体成员',

    'UNION_NAME_CHANGE': '修改联合体名',
    'UNION_MEMBER_NAME_CHANGE': '修改联合体成员名',
    'UNION_MEMBER_TYPE_CHANGE': '修改联合体成员类型',
    'UNION_MEMBER_ADD': '增加联合体成员',
    'UNION_MEMBER_REDUCE': '删除联合体成员',

    'ENUM_NAME_CHANGE': '修改枚举名',
    'ENUM_MEMBER_NAME_CHANGE': '修改枚举成员名',
    'ENUM_MEMBER_VALUE_CHANGE': '修改枚举值',
    'ENUM_MEMBER_ADD': '增加枚举成员',
    'ENUM_MEMBER_REDUCE': '删除枚举成员',

    'VARIABLE_NAME_CHANGE': '修改变量名',
    'VARIABLE_TYPE_CHANGE': '修改变量类型',
    'VARIABLE_VALUE_CHANGE': '修改变量值',
    'VARIABLE_CHANGE_TO_CONSTANT': '修改变量为常量',

    'CONSTANT_NAME_CHANGE': '修改常量名',
    'CONSTANT_TYPE_CHANGE': '修改常量类型',
    'CONSTANT_VALUE_CHANGE': '修改常量值',
    'CONSTANT_CHANGE_TO_VARIABLE': '修改常量为变量',

    'TYPEDEF_NAME_TYPE_CHANGE': '修改重命名的名',

    'DOC_TAG_ADDTOGROUP_NA_TO_HAVE': '增加addtogroup标签',
    'DOC_TAG_ADDTOGROUP_HAVE_TO_NA': '删除addtogroup标签',
    'DOC_TAG_ADDTOGROUP_A_TO_B': '修改addtogroup标签',
    'DOC_TAG_BRIEF_NA_TO_HAVE': '增加brief标签',
    'DOC_TAG_BRIEF_HAVE_TO_NA': '删除brief标签',
    'DOC_TAG_BRIEF_A_TO_B': '修改brief标签',
    'DOC_TAG_DEPRECATED_NA_TO_HAVE': '增加deprecated标签',
    'DOC_TAG_DEPRECATED_HAVE_TO_NA': '删除deprecated标签',
    'DOC_TAG_DEPRECATED_A_TO_B': '修改deprecated标签',
    'DOC_TAG_FILE_NA_TO_HAVE': '增加file标签',
    'DOC_TAG_FILE_HAVE_TO_NA': '删除file标签',
    'DOC_TAG_FILE_A_TO_B': '修改file标签',
    'DOC_TAG_LIBRARY_NA_TO_HAVE': '增加library标签',
    'DOC_TAG_LIBRARY_HAVE_TO_NA': '删除library标签',
    'DOC_TAG_LIBRARY_A_TO_B': '修改library标签',
    'DOC_TAG_PARAM_NA_TO_HAVE': '增加param标签',
    'DOC_TAG_PARAM_HAVE_TO_NA': '删除param标签',
    'DOC_TAG_PARAM_NAME_A_TO_B': '修改param标签',
    'DOC_TAG_PARAM_A_TO_B': '修改param标签值',
    'DOC_TAG_PERMISSION_NA_TO_HAVE': '增加permission标签',
    'DOC_TAG_PERMISSION_HAVE_TO_NA': '删除permission标签',
    'DOC_TAG_PERMISSION_RANGE_BIGGER': '权限变大',
    'DOC_TAG_PERMISSION_RANGE_SMALLER': '权限变小',
    'DOC_TAG_PERMISSION_RANGE_CHANGE': '修改权限',
    'DOC_TAG_SINCE_NA_TO_HAVE': '增加since标签',
    'DOC_TAG_SINCE_HAVE_TO_NA': '删除since标签',
    'DOC_TAG_SINCE_A_TO_B': '修改since标签',
    'DOC_TAG_SYSCAP_NA_TO_HAVE': '增加syscap标签',
    'DOC_TAG_SYSCAP_HAVE_TO_NA': '删除syscap标签',
    'DOC_TAG_SYSCAP_A_TO_B': '修改syscap标签',
    'DOC_TAG_LEFT_BRACE_NA_TO_HAVE': '增加{标签',
    'DOC_TAG_LEFT_BRACE_HAVE_TO_NA': '删除{标签',
    'DOC_TAG_RIGHT_BRACE_NA_TO_HAVE': '增加}标签',
    'DOC_TAG_RIGHT_BRACE_HAVE_TO_NA': '删除}标签',
    'DOC_TAG_ADDTOGROUP_INCREASE': '文件有addtogroup标签, 增加addtogroup标签',
    'DOC_TAG_ADDTOGROUP_DECREASE': '文件有多个addtogroup标签，删除addtogroup标签',
    'DOC_TAG_FILE_INCREASE': '文件有file标签, 增加file标签',
    'DOC_TAG_FILE_DECREASE': '文件有多个file标签，删除file标签',
}


class Scene(enum.Enum):
    FUNCTION_DECL = 'FUNCTION_DECL'
    MACRO_DEFINITION = 'MACRO_DEFINITION'
    STRUCT_DECL = 'STRUCT_DECL'
    UNION_DECL = 'UNION_DECL'
    ENUM_DECL = 'ENUM_DECL'
    VAR_DECL = 'VAR_DECL'
    TYPEDEF_DECL = 'TYPEDEF_DECL'
    TRANSLATION_UNIT = 'TRANSLATION_UNIT'
    ENUM_CONSTANT_DECL = 'ENUM_CONSTANT_DECL'


class TAGS(enum.Enum):
    ADD_TO_GROUP = 'addtogroup'
    BRIEF = 'brief'
    DEPRECATED = 'deprecated'
    FILE = 'file'
    LIBRARY = 'library'
    PARAM = 'param'
    PERMISSION = 'permission'
    RETURN = 'return'
    SINCE = 'since'
    SYSCAP = 'syscap'
    LEFT_BRACE = '{'
    RIGHT_BRACE = '}'


class DiffType(enum.Enum):
    DEFAULT = ''
    ADD_FILE = 'add file'
    REDUCE_FILE = 'delete file'
    ADD_API = 'add api'
    REDUCE_API = 'delete api'
    ADD_DOC = 'add doc'
    REDUCE_DOC = 'delete doc'
    ADD_DOC_TAG = 'add doc tag'
    REDUCE_DOC_TAG = 'delete doc tag'
    FUNCTION_PARAM_POS_CHANGE = 'change param site in function'

    DEFINE_NAME_CHANGE = 'change define name'
    DEFINE_TEXT_CHANGE = 'change define text'

    FUNCTION_NAME_CHANGE = 'change function name'
    FUNCTION_RETURN_CHANGE = 'change function return value'
    FUNCTION_PARAM_NAME_CHANGE = 'change param name in function'
    FUNCTION_PARAM_TYPE_CHANGE = 'change param type in function'
    FUNCTION_PARAM_ADD = 'add param in function'
    FUNCTION_PARAM_REDUCE = 'delete param in function'

    STRUCT_NAME_CHANGE = 'change struct name'
    STRUCT_MEMBER_NAME_CHANGE = 'change member name in struct'
    STRUCT_MEMBER_TYPE_CHANGE = 'change member type in struct'
    STRUCT_MEMBER_ADD = 'add member in struct'
    STRUCT_MEMBER_REDUCE = 'delete member in struct'

    UNION_NAME_CHANGE = 'change union name'
    UNION_MEMBER_NAME_CHANGE = 'change member name in union'
    UNION_MEMBER_TYPE_CHANGE = 'change member type in union'
    UNION_MEMBER_ADD = 'add member in union'
    UNION_MEMBER_REDUCE = 'delete member in union'

    ENUM_NAME_CHANGE = 'change enum name'
    ENUM_MEMBER_NAME_CHANGE = 'change member name in enum'
    ENUM_MEMBER_VALUE_CHANGE = 'change member value in enum'
    ENUM_MEMBER_ADD = 'add member in enum'
    ENUM_MEMBER_REDUCE = 'delete member in enum'

    VARIABLE_NAME_CHANGE = 'change variable name'
    VARIABLE_TYPE_CHANGE = 'change variable type'
    VARIABLE_VALUE_CHANGE = 'change variable value'
    VARIABLE_CHANGE_TO_CONSTANT = 'change variable to constant'

    CONSTANT_NAME_CHANGE = 'change constant name'
    CONSTANT_TYPE_CHANGE = 'change constant type'
    CONSTANT_VALUE_CHANGE = 'change constant value'
    CONSTANT_CHANGE_TO_VARIABLE = 'change constant to variable'

    TYPEDEF_NAME_TYPE_CHANGE = 'change typedef name type'

    DOC_TAG_ADDTOGROUP_NA_TO_HAVE = 'add addtogroup tag'
    DOC_TAG_ADDTOGROUP_HAVE_TO_NA = 'delete addtogroup tag'
    DOC_TAG_ADDTOGROUP_A_TO_B = 'change addtogroup tag'
    DOC_TAG_BRIEF_NA_TO_HAVE = 'add brief tag'
    DOC_TAG_BRIEF_HAVE_TO_NA = 'delete brief tag'
    DOC_TAG_BRIEF_A_TO_B = 'change brief tag'
    DOC_TAG_DEPRECATED_NA_TO_HAVE = 'add deprecated tag'
    DOC_TAG_DEPRECATED_HAVE_TO_NA = 'delete deprecated tag'
    DOC_TAG_DEPRECATED_A_TO_B = 'change deprecated tag'
    DOC_TAG_FILE_NA_TO_HAVE = 'add file tag'
    DOC_TAG_FILE_HAVE_TO_NA = 'delete file tag'
    DOC_TAG_FILE_A_TO_B = 'change file tag'
    DOC_TAG_LIBRARY_NA_TO_HAVE = 'add library tag'
    DOC_TAG_LIBRARY_HAVE_TO_NA = 'delete library tag'
    DOC_TAG_LIBRARY_A_TO_B = 'change library tag'
    DOC_TAG_PARAM_NA_TO_HAVE = 'add param tag'
    DOC_TAG_PARAM_HAVE_TO_NA = 'delete param tag'
    DOC_TAG_PARAM_NAME_A_TO_B = 'change param tag name'
    DOC_TAG_PARAM_A_TO_B = 'change param tag value'
    DOC_TAG_PERMISSION_NA_TO_HAVE = 'add permission tag'
    DOC_TAG_PERMISSION_HAVE_TO_NA = 'delete permission tag'
    DOC_TAG_PERMISSION_RANGE_BIGGER = 'increased permissions, ex: add "or" or remove "and"'
    DOC_TAG_PERMISSION_RANGE_SMALLER = 'reduced permissions, ex: add "and" or remove "or"'
    DOC_TAG_PERMISSION_RANGE_CHANGE = 'change permissions, before not included after and after not included before'
    DOC_TAG_SINCE_NA_TO_HAVE = 'add since tag'
    DOC_TAG_SINCE_HAVE_TO_NA = 'delete since tag'
    DOC_TAG_SINCE_A_TO_B = 'change since tag'
    DOC_TAG_SYSCAP_NA_TO_HAVE = 'add syscap tag'
    DOC_TAG_SYSCAP_HAVE_TO_NA = 'delete syscap tag'
    DOC_TAG_SYSCAP_A_TO_B = 'change syscap tag'
    DOC_TAG_LEFT_BRACE_NA_TO_HAVE = 'add { tag'
    DOC_TAG_LEFT_BRACE_HAVE_TO_NA = 'delete { tag'
    DOC_TAG_RIGHT_BRACE_NA_TO_HAVE = 'add } tag'
    DOC_TAG_RIGHT_BRACE_HAVE_TO_NA = 'delete } tag'
    DOC_TAG_ADDTOGROUP_INCREASE = 'The file has addtogroup tag, add the addtogroup tag'
    DOC_TAG_ADDTOGROUP_DECREASE = 'The file has multiple addtogroup tags. Delete the addtogroup tag'
    DOC_TAG_FILE_INCREASE = 'The file has file tag, add the file tag'
    DOC_TAG_FILE_DECREASE = 'The file has multiple file tags. Delete the file tag'


compatible_list = [
    DiffType.ADD_API,
    DiffType.ADD_DOC,
    DiffType.ADD_DOC_TAG,
    DiffType.ENUM_MEMBER_ADD,
    DiffType.FUNCTION_PARAM_NAME_CHANGE,
    DiffType.DOC_TAG_ADDTOGROUP_NA_TO_HAVE,
    DiffType.DOC_TAG_ADDTOGROUP_HAVE_TO_NA,
    DiffType.DOC_TAG_ADDTOGROUP_A_TO_B,
    DiffType.DOC_TAG_BRIEF_NA_TO_HAVE,
    DiffType.DOC_TAG_BRIEF_HAVE_TO_NA,
    DiffType.DOC_TAG_BRIEF_A_TO_B,
    DiffType.DOC_TAG_DEPRECATED_NA_TO_HAVE,
    DiffType.DOC_TAG_DEPRECATED_HAVE_TO_NA,
    DiffType.DOC_TAG_DEPRECATED_A_TO_B,
    DiffType.DOC_TAG_FILE_NA_TO_HAVE,
    DiffType.DOC_TAG_FILE_HAVE_TO_NA,
    DiffType.DOC_TAG_FILE_A_TO_B,
    DiffType.DOC_TAG_PARAM_A_TO_B,
    DiffType.DOC_TAG_PERMISSION_HAVE_TO_NA,
    DiffType.DOC_TAG_PERMISSION_RANGE_BIGGER,
    DiffType.DOC_TAG_SINCE_NA_TO_HAVE,
    DiffType.DOC_TAG_SINCE_A_TO_B,
    DiffType.DOC_TAG_LEFT_BRACE_NA_TO_HAVE,
    DiffType.DOC_TAG_LEFT_BRACE_HAVE_TO_NA,
    DiffType.DOC_TAG_RIGHT_BRACE_NA_TO_HAVE,
    DiffType.DOC_TAG_RIGHT_BRACE_HAVE_TO_NA,
    DiffType.DOC_TAG_ADDTOGROUP_DECREASE,
    DiffType.DOC_TAG_ADDTOGROUP_INCREASE,
    DiffType.DOC_TAG_FILE_DECREASE,
    DiffType.DOC_TAG_FILE_INCREASE
]

api_new_list = [DiffType.ADD_API]

api_delete_list = [DiffType.REDUCE_API]

non_api_change_list = [
    DiffType.ADD_DOC,
    DiffType.REDUCE_DOC,
    DiffType.ADD_DOC_TAG,
    DiffType.REDUCE_DOC_TAG
]

api_prototype_change_list = [
    DiffType.DEFINE_NAME_CHANGE,
    DiffType.DEFINE_TEXT_CHANGE,
    DiffType.FUNCTION_PARAM_POS_CHANGE,
    DiffType.FUNCTION_NAME_CHANGE,
    DiffType.FUNCTION_RETURN_CHANGE,
    DiffType.FUNCTION_PARAM_NAME_CHANGE,
    DiffType.FUNCTION_PARAM_TYPE_CHANGE,
    DiffType.FUNCTION_PARAM_REDUCE,
    DiffType.FUNCTION_PARAM_ADD,
    DiffType.STRUCT_NAME_CHANGE,
    DiffType.STRUCT_MEMBER_TYPE_CHANGE,
    DiffType.STRUCT_MEMBER_NAME_CHANGE,
    DiffType.STRUCT_MEMBER_ADD,
    DiffType.STRUCT_MEMBER_REDUCE,
    DiffType.UNION_MEMBER_TYPE_CHANGE,
    DiffType.UNION_MEMBER_NAME_CHANGE,
    DiffType.UNION_NAME_CHANGE,
    DiffType.UNION_MEMBER_ADD,
    DiffType.UNION_MEMBER_REDUCE,
    DiffType.ENUM_NAME_CHANGE,
    DiffType.ENUM_MEMBER_NAME_CHANGE,
    DiffType.ENUM_MEMBER_VALUE_CHANGE,
    DiffType.ENUM_MEMBER_ADD,
    DiffType.ENUM_MEMBER_REDUCE,
    DiffType.VARIABLE_NAME_CHANGE,
    DiffType.VARIABLE_TYPE_CHANGE,
    DiffType.VARIABLE_VALUE_CHANGE,
    DiffType.VARIABLE_CHANGE_TO_CONSTANT,
    DiffType.CONSTANT_NAME_CHANGE,
    DiffType.CONSTANT_TYPE_CHANGE,
    DiffType.CONSTANT_VALUE_CHANGE,
    DiffType.CONSTANT_CHANGE_TO_VARIABLE,
    DiffType.TYPEDEF_NAME_TYPE_CHANGE
]

api_constraint_change_list = [
    DiffType.DOC_TAG_ADDTOGROUP_NA_TO_HAVE,
    DiffType.DOC_TAG_ADDTOGROUP_HAVE_TO_NA,
    DiffType.DOC_TAG_ADDTOGROUP_A_TO_B,
    DiffType.DOC_TAG_BRIEF_NA_TO_HAVE,
    DiffType.DOC_TAG_BRIEF_HAVE_TO_NA,
    DiffType.DOC_TAG_BRIEF_A_TO_B,
    DiffType.DOC_TAG_DEPRECATED_NA_TO_HAVE,
    DiffType.DOC_TAG_DEPRECATED_HAVE_TO_NA,
    DiffType.DOC_TAG_DEPRECATED_A_TO_B,
    DiffType.DOC_TAG_FILE_NA_TO_HAVE,
    DiffType.DOC_TAG_FILE_HAVE_TO_NA,
    DiffType.DOC_TAG_FILE_A_TO_B,
    DiffType.DOC_TAG_LIBRARY_NA_TO_HAVE,
    DiffType.DOC_TAG_LIBRARY_HAVE_TO_NA,
    DiffType.DOC_TAG_LIBRARY_A_TO_B,
    DiffType.DOC_TAG_PARAM_NA_TO_HAVE,
    DiffType.DOC_TAG_PARAM_HAVE_TO_NA,
    DiffType.DOC_TAG_PARAM_NAME_A_TO_B,
    DiffType.DOC_TAG_PARAM_A_TO_B,
    DiffType.DOC_TAG_PERMISSION_NA_TO_HAVE,
    DiffType.DOC_TAG_PERMISSION_HAVE_TO_NA,
    DiffType.DOC_TAG_PERMISSION_RANGE_BIGGER,
    DiffType.DOC_TAG_PERMISSION_RANGE_SMALLER,
    DiffType.DOC_TAG_PERMISSION_RANGE_CHANGE,
    DiffType.DOC_TAG_SINCE_NA_TO_HAVE,
    DiffType.DOC_TAG_SINCE_A_TO_B,
    DiffType.DOC_TAG_SYSCAP_NA_TO_HAVE,
    DiffType.DOC_TAG_SYSCAP_HAVE_TO_NA,
    DiffType.DOC_TAG_SYSCAP_A_TO_B,
    DiffType.DOC_TAG_LEFT_BRACE_NA_TO_HAVE,
    DiffType.DOC_TAG_LEFT_BRACE_HAVE_TO_NA,
    DiffType.DOC_TAG_RIGHT_BRACE_NA_TO_HAVE,
    DiffType.DOC_TAG_RIGHT_BRACE_HAVE_TO_NA,
    DiffType.DOC_TAG_ADDTOGROUP_DECREASE,
    DiffType.DOC_TAG_ADDTOGROUP_INCREASE,
    DiffType.DOC_TAG_FILE_DECREASE,
    DiffType.DOC_TAG_FILE_INCREASE
]

api_modification_type_dict = {
    'api_new_list': 'API新增',
    'api_delete_list': 'API删除',
    'non_api_change_list': '非API变更',
    'api_prototype_change_list': 'API修改（原型修改）',
    'api_constraint_change_list': 'API修改（约束变化）'
}


class ApiInfo:
    is_api_change = False

    def set_is_api_change(self, is_api_change):
        self.is_api_change = is_api_change

    def get_is_api_change(self):
        return self.is_api_change


class DiffInfo:
    api_name: str = ''
    api_type: str = ''
    diff_type: DiffType = DiffType.DEFAULT
    diff_message: str = ''
    old_api_full_text: str = ''
    new_api_full_text: str = ''
    api_line: int = 0
    api_column: int = 0
    api_file_path: str = ''
    is_compatible = False
    is_api_change = False
    api_modification_type = ''
    kit_name = ''
    sub_system = ''
    class_name = ''
    api_node_name = ''
    unique_id = ''
    current_api_unique_id = ''
    is_system_api = False
    operation_diff_type: str = ''
    old_differ_content: str = ''
    new_differ_content: str = ''
    open_close_api: str = ''
    is_third_party_api = False
    current_api_type: str = ''

    def __init__(self, diff_type: DiffType, old_differ_content, new_differ_content):
        self.diff_type = diff_type
        self.diff_message = diff_type.value
        self.set_diff_type(diff_type)
        self.set_api_modification_type(diff_type)
        self.set_operation_diff_type(diff_type)
        self.old_differ_content = old_differ_content
        self.new_differ_content = new_differ_content

    def set_api_line(self, api_line):
        self.api_line = api_line

    def get_api_line(self):
        return self.api_line

    def set_api_column(self, api_column):
        self.api_column = api_column

    def get_api_column(self):
        return self.api_column

    def set_api_file_path(self, api_file_path):
        self.api_file_path = api_file_path

    def get_api_file_path(self):
        return self.api_file_path

    def set_api_name(self, api_name):
        self.api_name = api_name

    def get_api_name(self):
        return self.api_name

    def set_api_type(self, api_type):
        self.api_type = api_type

    def get_api_type(self):
        return self.api_type

    def set_diff_type(self, diff_type):
        if diff_type in compatible_list:
            self.is_compatible = True
        self.diff_type = diff_type

    def get_diff_type(self):
        return self.diff_type

    def set_diff_message(self, diff_message):
        self.diff_message = diff_message

    def get_diff_message(self):
        return self.diff_message

    def set_old_api_full_text(self, old_api_full_text):
        self.old_api_full_text = old_api_full_text

    def get_old_api_full_text(self):
        return self.old_api_full_text

    def set_new_api_full_text(self, new_api_full_text):
        self.new_api_full_text = new_api_full_text

    def get_new_api_full_text(self):
        return self.new_api_full_text

    def set_is_compatible(self, is_compatible):
        self.is_compatible = is_compatible

    def get_is_compatible(self):
        return self.is_compatible

    def set_is_api_change(self, is_api_change):
        self.is_api_change = is_api_change

    def get_is_api_change(self):
        return self.is_api_change

    def set_api_modification_type(self, diff_type):
        if diff_type in api_new_list:
            self.api_modification_type = api_modification_type_dict.get('api_new_list')
        elif diff_type in api_delete_list:
            self.api_modification_type = api_modification_type_dict.get('api_delete_list')
        elif diff_type in non_api_change_list:
            self.api_modification_type = api_modification_type_dict.get('non_api_change_list')
        elif diff_type in api_prototype_change_list:
            self.api_modification_type = api_modification_type_dict.get('api_prototype_change_list')
        elif diff_type in api_constraint_change_list:
            self.api_modification_type = api_modification_type_dict.get('api_constraint_change_list')

    def get_api_modification_type(self):
        return self.api_modification_type

    def set_kit_name(self, kit_name):
        self.kit_name = kit_name

    def get_kit_name(self):
        return self.kit_name

    def set_sub_system(self, sub_system):
        self.sub_system = sub_system

    def get_sub_system(self):
        return self.sub_system

    def set_class_name(self, class_name):
        self.class_name = class_name

    def get_class_name(self):
        return self.class_name

    def set_api_node_name(self, api_node_name):
        self.api_node_name = api_node_name

    def get_api_node_name(self):
        return self.api_node_name

    def set_unique_id(self, unique_id):
        self.unique_id = unique_id

    def get_unique_id(self):
        return self.unique_id

    def set_current_api_unique_id(self, current_api_unique_id):
        self.current_api_unique_id = current_api_unique_id

    def get_current_api_unique_id(self):
        return self.current_api_unique_id

    def set_is_system_api(self, is_system_api):
        self.is_system_api = is_system_api

    def get_is_system_api(self):
        return self.is_system_api

    def set_operation_diff_type(self, diff_type):
        if diff_type.name in operation_mark_dict:
            self.operation_diff_type = operation_mark_dict.get(diff_type.name)

    def get_operation_diff_type(self):
        return self.operation_diff_type

    def set_old_differ_content(self, old_differ_content):
        self.old_differ_content = old_differ_content

    def get_old_differ_content(self):
        return self.old_differ_content

    def set_new_differ_content(self, new_differ_content):
        self.new_differ_content = new_differ_content

    def get_new_differ_content(self):
        return self.new_differ_content

    def set_open_close_api(self, open_close_api):
        self.open_close_api = open_close_api

    def get_open_close_api(self):
        return self.open_close_api

    def set_is_third_party_api(self, is_third_party_api):
        self.is_third_party_api = is_third_party_api

    def get_is_third_party_api(self):
        return self.is_third_party_api

    def set_current_api_type(self, current_api_type):
        self.current_api_type = current_api_type

    def get_current_api_type(self):
        return self.current_api_type


class OutputJson:
    api_name: str = ''
    api_type: str = ''
    diff_type: str = ''
    diff_message: str = ''
    old_api_full_text: str = ''
    new_api_full_text: str = ''
    api_line: int = 0
    api_column: int = 0
    api_file_path: str = ''
    is_compatible = False
    is_api_change = False
    api_modification_type = ''
    kit_name = ''
    sub_system = ''
    class_name = ''
    unique_id = ''
    is_system_api = False

    def __init__(self, diff_info):
        self.api_name = diff_info.api_name
        self.api_type = diff_info.api_type
        self.diff_type = diff_info.operation_diff_type
        self.diff_message = diff_info.diff_message
        self.old_api_full_text = diff_info.old_api_full_text
        self.new_api_full_text = diff_info.new_api_full_text
        self.api_line = diff_info.api_line
        self.api_column = diff_info.api_column
        self.api_file_path = diff_info.api_file_path
        self.is_compatible = diff_info.is_compatible
        self.is_api_change = diff_info.is_api_change
        self.api_modification_type = diff_info.api_modification_type
        self.kit_name = diff_info.kit_name
        self.sub_system = diff_info.sub_system
        self.class_name = diff_info.class_name
        self.unique_id = diff_info.unique_id
        self.is_system_api = diff_info.is_system_api


class ApiChangeData:
    api_name: str = ''
    kit_name: str = ''
    sub_system: str = ''
    is_api_change = False
    class_name: str = ''
    diff_type: str = ''
    change_type: str = ''
    compatible = {}
    change_num = {}
    old_all_text: str = ''
    new_all_text: str = ''
    compatible_total = False
    unique_id: str = ''
    is_system_api = False
    open_close_api: str = ''
    is_third_party_api = False
    api_type: str = ''
    current_api_type: str = ''

    def set_api_name(self, api_name):
        self.api_name = api_name

    def get_api_name(self):
        return self.api_name

    def set_kit_name(self, kit_name):
        self.kit_name = kit_name

    def get_kit_name(self):
        return self.kit_name

    def set_sub_system(self, sub_system):
        self.sub_system = sub_system

    def get_sub_system(self):
        return self.sub_system

    def set_is_api_change(self, is_api_change):
        self.is_api_change = is_api_change

    def get_is_api_change(self):
        return self.is_api_change

    def set_class_name(self, class_name):
        self.class_name = class_name

    def get_class_name(self):
        return self.class_name

    def set_diff_type(self, diff_type):
        self.diff_type = diff_type

    def get_diff_type(self):
        return self.diff_type

    def set_change_type(self, change_type):
        self.change_type = change_type

    def get_change_type(self):
        return self.change_type

    def set_compatible(self, compatible):
        self.compatible = compatible

    def get_compatible(self):
        return self.compatible

    def set_change_num(self, change_num):
        self.change_num = change_num

    def get_change_num(self):
        return self.change_num

    def set_old_all_text(self, old_all_text):
        self.old_all_text = old_all_text

    def get_old_all_text(self):
        return self.old_all_text

    def set_new_all_text(self, new_all_text):
        self.new_all_text = new_all_text

    def get_new_all_text(self):
        return self.new_all_text

    def set_compatible_total(self, compatible_total):
        self.compatible_total = compatible_total

    def get_compatible_total(self):
        return self.compatible_total

    def set_unique_id(self, unique_id):
        self.unique_id = unique_id

    def get_unique_id(self):
        return self.unique_id

    def set_is_system_api(self, is_system_api):
        self.is_system_api = is_system_api

    def get_is_system_api(self):
        return self.is_system_api

    def set_open_close_api(self, open_close_api):
        self.open_close_api = open_close_api

    def get_open_close_api(self):
        return self.open_close_api

    def set_is_third_party_api(self, is_third_party_api):
        self.is_third_party_api = is_third_party_api

    def get_is_third_party_api(self):
        return self.is_third_party_api

    def set_api_type(self, api_type):
        self.api_type = api_type

    def get_api_type(self):
        return self.api_type

    def set_current_api_type(self, current_api_type):
        self.current_api_type = current_api_type

    def get_current_api_type(self):
        return self.current_api_type


class IgnoreFileDirectory:
    ignore_file_dict = {
        'arm-linux-ohos': '',
        'aarch64-linux-ohos': '',
        'x86_64-linux-ohos': '',
        'i686-linux-ohos': '',
        'tee': '',
        'linux': ''
    }

    def get_ignore_file_dict(self):
        return self.ignore_file_dict
