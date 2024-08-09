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


class ErrorType(enum.Enum):
    DEFAULT = {
        'id': -1,
        'description': '',
    }
    UNKNOW_DECORATOR = {
        'id': 0,
        'description': 'unknow decorator',
    }
    MISSPELL_WORDS = {
        'id': 1,
        'description': 'misspell words',
    }
    NAMING_ERRORS = {
        'id': 2,
        'description': 'naming errors',
    }
    UNKNOW_PERMISSION = {
        'id': 3,
        'description': 'unknow permission',
    }
    UNKNOW_SYSCAP = {
        'id': 4,
        'description': 'unknow syscap',
    }
    UNKNOW_DEPRECATED = {
        'id': 5,
        'description': 'unknow deprecated',
    }
    WRONG_ORDER = {
        'id': 6,
        'description': 'wrong order',
    }
    WRONG_VALUE = {
        'id': 7,
        'description': 'wrong value',
    }
    WRONG_SCENE = {
        'id': 8,
        'description': 'wrong scene',
    }
    PARAMETER_ERRORS = {
        'id': 9,
        'description': 'wrong parameter',
    }
    API_PAIR_ERRORS = {
        'id': 10,
        'description': 'limited api pair errors',
    }
    ILLEGAL_ANY = {
        'id': 11,
        'description': 'illegal any',
    }
    API_CHANGE_ERRORS = {
        'id': 12,
        'description': 'api change errors',
    }
    EMPTY_TAG = {
        'id': 13,
        'description': 'miss tag value',
    }
    ERROR_TAG = {
        'id': 14,
        'description': 'error tag name',
    }
    SYNTAX_ERRORS = {
        'id': 15,
        'description': 'syntax errors',
    }


class LogType(enum.Enum):
    DEFAULT = ''
    LOG_API = 'Api'
    LOG_JSDOC = 'JsDoc'
    LOG_FILE = 'File'


class ErrorLevel(enum.Enum):
    HIGH = 3
    MIDDLE = 2
    LOW = 1


class ErrorMessage(enum.Enum):
    EMPTY_TAG = 'the [$$] tag value is empty. Please supplement the default value'
    USE_UPPER_TAG = "the [$$] tag is upper. Should use lower: [$$]"
    REPEAT_FILE_TAG = 'the [$$] tag is repeat. Please check the tag in file'
    ERROR_INFO_VALUE_TAG = 'the [$$] tag value is incorrect. Please check the usage method'
    ERROR_INFO_VALUE_LIBRARY = 'the [library] tag value is incorrect. This tag must be end with .so or .a, \
or is NA. Please check the usage method'
    ERROR_INFO_VALUE_PARAM = 'the value of the [$$] [param] tag is incorrect. Please check if it matches \
the [$$] parameter name'
    ERROR_INFO_COUNT_PARAM = 'the count of the [param] tag is wrong. Please check the parameters and Doc'
    ERROR_INFO_VALUE_PERMISSION = 'the [permission] tag value is incorrect. Please check if the permission \
field has been configured or update the configuration file'
    ERROR_INFO_VALUE_SINCE = 'the [since] tag value is incorrect. Please check if the tag value is a numerical value'
    ERROR_INFO_VALUE_SYSCAP = 'the [syscap] tag value is incorrect. Please check if the syscap field is configured'
    ERROR_USE_LEFT_BRACE = 'the validity verification of the Doc tag failed. The [{] tag is not allowed to used \
in Doc which not has addtogroup tag, or used in the wrong place.'
    ERROR_REPEAT_LEFT_BRACE = 'the validity verification of the Doc tag failed. The [{] tag is not allowed to \
reuse in Doc which has addtogroup tag.'
    ERROR_USE_RIGHT_BRACE = 'the validity verification of the JSDoc tag failed. The [}] tag is not allowed to \
be reused please delete the extra tags.'
    ERROR_FILE_HAS_ONE_LOSE_OTHER = 'the file has the $$, but do not has the $$.'
    ERROR_FILE_LOSE_ONE = 'the file missing $$'
    ERROR_LOST_LABEL = 'JSDoc tag validity verification failed. Please confirm if the [$$] tag is missing'

    FUNCTION_DECL = 'This name [$$] should use the big hump naming style or beginning with OH/OS,and \
        using "_" segmentation.'
    STRUCT_DECL = 'This name [$$] should use the big hump naming style.'
    ENUM_DECL = 'This name [$$] should use the big hump naming style.'
    UNION_DECL = 'This name [$$] should use the big hump naming style.'
    VAR_DECL = 'This name [$$] should use the small hump naming style.'
    PARM_DECL = 'This name [$$] should use the small hump naming style.'
    MACRO_PARAMETERS_TYPE_NAMING_ERROR = 'This name [$$] should use the small hump naming style.'
    FIELD_DECL = 'This name [$$] should use the small hump naming style.'
    MEMBERS_OF_THE_CONSORTIUM_TYPE_NAMING_ERROR = 'This name [$$] should use the small hump naming style.'
    MACRO_DEFINITION = 'This name [$$] should use all uppercase, separated by underscores naming style.'
    ENUM_CONSTANT_DECL = 'This name [$$] should use all uppercase, separated by underscores naming style.'
    GOTO_LABEL_TYPE_NAMING_ERROR = 'This name [$$] should use all uppercase, separated by \
        underscores naming style.'
    GLOBAL_VARIABLE_TYPE_NAMING_ERROR = 'This name [$$] should increase "g_" prefix.'
    TRANSLATION_UNIT = 'This name [$$] should be all lowercase, separated by underscores.'


class CheckErrorMessage(enum.Enum):
    API_NAME_UNIVERSAL_01 = ('API check error of [naming errors]:The [$$] of self-developed '
                             'functions in APIs must start with OH_ or OS_ or HMS_ and comply '
                             'with the large hump case format.')
    API_NAME_UNIVERSAL_02 = ('API check error of [naming errors]:The [$$] of constants in '
                             'APIs must be in uppercase and separated by underscores.')
    API_NAME_UNIVERSAL_03 = ('API check error of [naming errors]:The [$$] of enumeration '
                             'types should follow the big hump rule.')
    API_NAME_UNIVERSAL_04 = ('API check error of [naming errors]:The [$$] of enumeration '
                             'values should follow the all uppercase rule and separated by underscores.')
    API_NAME_UNIVERSAL_05 = ('API check error of [naming errors]:The [$$] of struct should '
                             'follow the rules of the Great Hump.')
    API_NAME_UNIVERSAL_06 = ('API check error of [naming errors]:The [$$] of members in the '
                             'structure should follow the small hump format.')
    API_NAME_UNIVERSAL_07 = ('API check error of [naming errors]:The [$$] of the consortium '
                             'should follow the format of the Great hump.')
    API_NAME_UNIVERSAL_08 = ('API check error of [naming errors]:The [$$] of members in the '
                             'consortium should follow the small hump format.')
    API_NAME_UNIVERSAL_09 = ('API check error of [naming errors]:The [$$] of a global variable '
                             'must be prefixed with g_ in the small camel case format.')
    API_NAME_UNIVERSAL_10 = ('API check error of [naming errors]:The [$$] of general functions '
                             'should follow the big hump format.')
    API_NAME_UNIVERSAL_11 = ('API check error of [naming errors]:Function parameter [$$] should '
                             'follow the small hump format.')
    API_NAME_UNIVERSAL_12 = ('API check error of [naming errors]:Macro [$$] should follow all '
                             'uppercase format and separated by underscores.')
    API_NAME_UNIVERSAL_13 = ('API check error of [naming errors]:Functional macro [$$] should '
                             'follow all uppercase format and separated by underscores.')
    API_NAME_UNIVERSAL_14 = ('API check error of [naming errors]:The [$$] file name should be all '
                             'lowercase and separated by underscores.')
    API_DOC_GLOBAL_01 = ('API check error of [api doc errors]:The [file] tag is repeat. Please '
                         'check the tag in file.')
    API_DOC_GLOBAL_02 = ('API check error of [api doc errors]:The file has the [addtogroup] tag, '
                         'but do not has the [brief] tag.')
    API_DOC_GLOBAL_03 = ('API check error of [api doc errors]:The file miss [file] tag, '
                         'or the file comment is not at the beginning of the file')
    API_DOC_GLOBAL_04 = ('API check error of [api doc errors]:The [addtogroup] tag is repeat. '
                         'Please check the tag in file.')
    API_DOC_GLOBAL_05 = ('API check error of [api doc errors]:The file has the [addtogroup] tag,'
                         'but do not has the start tag [{].')
    API_DOC_GLOBAL_06 = ('API check error of [api doc errors]:The [{] tag is not allowed to reuse '
                         'in Doc which has [addtogroup] tag.')
    API_DOC_GLOBAL_09 = ('API check error of [api doc errors]:The file missing [addtogroup] tag, '
                         'or the file comment is not at the beginning of the file')
    API_DOC_GLOBAL_10 = ('API check error of [api doc errors]:The file has the [addtogroup] tag,'
                         'but do not has the end tag [}].')
    API_DOC_GLOBAL_11 = ('API check error of [api doc errors]:The [addtogroup] tag value is empty,'
                         'please supplement the default value.')
    API_DOC_GLOBAL_12 = ('API check error of [api doc errors]:The [file] tag value is empty,please '
                         'supplement the default value.')
    API_DOC_GLOBAL_13 = ('API check error of [api doc errors]:The [library] tag value must be end '
                         'with .so or .a, please check the usage method.')
    API_DOC_GLOBAL_14 = ('API check error of [api doc errors]:The [{] tag is not allowed to used '
                         'in Doc which not the [addtogroup] tag,or used in the wrong place.'),
    API_DOC_GLOBAL_15 = 'API check error of [api doc errors]:Non lowercase labels used in API Doc information.'
    API_DOC_GLOBAL_16 = 'API check error of [api doc errors]:The name after the [library] tag should be in lowercase.'
    API_DOC_GLOBAL_17 = ('API check error of [api doc errors]:The file has the [file] tag, but do '
                         'not has the [brief] tag.')
    API_DOC_GLOBAL_18 = ('API check error of [api doc errors]:The file has the [file] tag, but do not '
                         'has the [library] tag.')
    API_DOC_GLOBAL_19 = ('API check error of [api doc errors]:The file has the [file] tag, but do not '
                         'has the [syscap] tag.')
    API_DOC_GLOBAL_20 = ('API check error of [api doc errors]:APIDoc tag validity verification failed. '
                         'Please confirm if the [since] tag is missing.')
    API_DOC_GLOBAL_21 = ('API check error of [api doc errors]:The validity verification of the APIDoc tag '
                         'failed. The [}] tag is not allowed to be reused please delete the extra tags')
    API_DOC_FUNCTION_01 = ('API check error of [api doc errors]:The count of the [param] tag is wrong.'
                           'Please check the parameters and Doc.')
    API_DOC_FUNCTION_02 = ('API check error of [api doc errors]:The value of the [$$] [param] tag is '
                           'incorrect. Please check if it matches the [&&] parameter name.')
    API_DOC_UNIVERSAL_01 = ('API check error of [api doc errors]:The [deprecated] tag value is incorrect.'
                            'Please check the usage method.')
    API_DOC_UNIVERSAL_02 = ('API check error of [api doc errors]:The [permission] tag value is incorrect. '
                            'Please check if the permission field has been configured or update the '
                            'configuration file.')
    API_DOC_UNIVERSAL_03 = ('API check error of [api doc errors]:The [since] tag value is empty.Please '
                            'supplement the default value.')
    API_DOC_UNIVERSAL_04 = ('API check error of [api doc errors]:The [since] tag value is incorrect.'
                            'Please check if the tag value is a numerical value or version number(number).')
    API_DOC_UNIVERSAL_05 = ('API check error of [api doc errors]:The [syscap] tag value is empty.'
                            'Please supplement the default value.')
    API_DOC_UNIVERSAL_06 = ('API check error of [api doc errors]:The [syscap] tag value is incorrect.'
                            'Please check if the syscap field is configured.')


check_command_message = [
    member.name for name_tool,
    member in CheckErrorMessage.__members__.items()
]


class CheckOutPut:
    analyzerName = 'apiengine'
    buggyFilePath = ''
    codeContextStartLine = -1
    defectLevel = 0
    defectType = ''
    description = ''
    language = 'c'
    mainBuggyCode = ''
    mainBuggyLine = -1

    def __init__(self, buggy_file_path, code_context_start_line, defect_type, description,
                 main_buggy_code, main_buggy_line):
        self.analyzerName = 'apiengine'
        self.buggyFilePath = buggy_file_path
        if code_context_start_line == -1:
            code_context_start_line = 0
        self.codeContextStartLine = code_context_start_line
        self.defectLevel = 2
        self.defectType = defect_type
        self.description = description
        self.language = 'c++'
        self.mainBuggyCode = main_buggy_code
        if main_buggy_line == -1:
            main_buggy_line = 0
        self.mainBuggyLine = main_buggy_line


class OutputTxt:
    id = -1
    level = -1
    since = ''
    location = ''
    file_path = ''
    message = ''

    def __init__(self, id_param, level_param, api_since, location_param, file_path_param, message_param):
        self.id = id_param
        self.level = level_param
        self.since = api_since
        self.location = location_param
        self.file_path = file_path_param
        self.message = message_param

    def get_id(self):
        return self.id

    def set_id(self, id_param):
        self.id = id_param

    def get_level(self):
        return self.level

    def set_level(self, level_param):
        self.level = level_param

    def get_since(self):
        return self.since

    def set_since(self, api_since):
        self.level = api_since

    def get_location(self):
        return self.location

    def set_location(self, location_param):
        self.location = location_param

    def get_file_path(self):
        return self.file_path

    def set_file_path(self, file_path_param):
        self.file_path = file_path_param

    def get_message(self):
        return self.message

    def set_message(self, message_param):
        self.message = message_param


class ApiResultInfo:
    error_type: ErrorType = ErrorType.DEFAULT.value
    error_info = ''
    error_content = ''
    level: ErrorLevel = -1
    api_name = ''
    api_since = ''
    api_full_text = ''
    file_name = ''
    location = ''
    location_line = -1
    location_column = -1
    type: LogType = LogType.DEFAULT.value
    version = -1
    basename = ''

    def __init__(self, error_type_param=None, error_info_param='', api_name_param=''):
        if error_type_param is None:
            error_type_param = ErrorType.DEFAULT.value
        self.error_type = error_type_param
        self.error_info = error_info_param
        self.api_name = api_name_param

    def get_error_type(self):
        return self.error_type

    def set_error_type(self, error_type_param):
        self.error_type = error_type_param

    def get_file_name(self):
        return self.file_name

    def set_file_name(self, file_name_param):
        self.file_name = file_name_param

    def get_type(self):
        return self.type

    def set_type(self, type_param):
        self.type = type_param

    def get_error_info(self):
        return self.error_info

    def set_error_info(self, error_info_param):
        self.error_info = error_info_param

    def get_version(self):
        return self.version

    def set_version(self, version_param):
        self.version = version_param

    def get_basename(self):
        return self.basename

    def set_basename(self, basename_param):
        self.basename = basename_param

    def get_level(self):
        return self.level

    def set_level(self, level_param):
        self.level = level_param

    def get_api_name(self):
        return self.api_name

    def set_api_name(self, api_name_param):
        self.api_name = api_name_param

    def get_api_since(self):
        return self.api_since

    def set_api_since(self, api_since):
        self.api_since = api_since

    def get_api_full_text(self):
        return self.api_full_text

    def set_api_full_text(self, api_full_text_param):
        self.api_full_text = api_full_text_param

    def get_location_line(self):
        return self.location_line

    def set_location_line(self, location_line_param):
        self.location_line = location_line_param

    def get_location_column(self):
        return self.location_column

    def set_location_column(self, location_column_param):
        self.location_column = location_column_param

    def get_location(self):
        return self.location

    def set_location(self, location_param):
        self.location = location_param

    def get_error_content(self):
        return self.error_content

    def set_error_content(self, error_content):
        self.error_content = error_content


class DocInfo:
    group = ''
    brief = ''
    deprecated = ''
    file = ''
    permission = ''
    since = ''
    syscap = ''
    param_index = -1
    throw_index = -1


class FileDocInfo:
    is_in_group_tag = False
    group_name = None
    group_brief = None
    group_library = None
    group_syscap = None
    group_comment_str = ''
    has_group_start = False
    has_group_end = False
    is_in_file_tag = False
    file_name = None
    file_brief = None
    file_library = None
    file_syscap = None
    file_since = False
    file_comment_str = ''
    curr_doc_info = DocInfo()


class CommentStartEndValue(enum.Enum):
    DEFAULT_START = 0,
    DEFAULT_END = 0

