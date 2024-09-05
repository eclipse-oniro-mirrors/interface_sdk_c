#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright (c) 2024 Huawei Device Co., Ltd.
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
from typedef.diff.diff import DiffType


class CheckCompatibilityErrorMessage(enum.Enum):
    API_CHANGE_INCOMPATIBLE_01 = ('API check error of [api compatibility errors]:Deleting [$$] API is prohibited.'
                                  'Please resolve it.')
    API_CHANGE_INCOMPATIBLE_02 = ('API check error of [api compatibility errors]:Changing API name [$$] to API name '
                                  '[&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_03 = ('API check error of [api compatibility errors]:Deleting [$$] file is prohibited.'
                                  'Please resolve it.')
    API_CHANGE_INCOMPATIBLE_04 = ('API check error of [api compatibility errors]:Changing [$$] file path is prohibited.'
                                  'Please resolve it.')
    API_CHANGE_INCOMPATIBLE_05 = ('API check error of [api compatibility errors]:Changing function name [$$] to '
                                  'function name [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_06 = ('API check error of [api compatibility errors]:Changing function return type [$$] '
                                  'to function return type [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_07 = ('API check error of [api compatibility errors]:Changing function param location [$$] '
                                  'to function param location [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_08 = ('API check error of [api compatibility errors]:Adding new function param [&&] is '
                                  'prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_09 = ('API check error of [api compatibility errors]:Deleting function param [$$] is '
                                  'prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_10 = ('API check error of [api compatibility errors]:Changing function param type [$$] '
                                  'to function param type [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_11 = ('API check error of [api compatibility errors]:Changing variable name [$$] to '
                                  'variable name [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_12 = ('API check error of [api compatibility errors]:Changing const name [$$] to const '
                                  'name [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_13 = ('API check error of [api compatibility errors]:Changing variable type [$$] to '
                                  'variable type [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_14 = ('API check error of [api compatibility errors]:Changing const type [$$] to const '
                                  'type [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_15 = ('API check error of [api compatibility errors]:Changing variable [$$] to const [&&] '
                                  'is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_16 = ('API check error of [api compatibility errors]:Changing const [$$] to variable [&&] '
                                  'is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_17 = ('API check error of [api compatibility errors]:Changing variable value [$$] to '
                                  'variable value [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_18 = ('API check error of [api compatibility errors]:Changing const value [$$] to const '
                                  'value [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_19 = ('API check error of [api compatibility errors]:Deleting variable [$$] is prohibited.'
                                  'Please resolve it.')
    API_CHANGE_INCOMPATIBLE_20 = ('API check error of [api compatibility errors]:Deleting const [$$] is prohibited.'
                                  'Please resolve it.')
    API_CHANGE_INCOMPATIBLE_21 = ('API check error of [api compatibility errors]:Changing macro name [$$] to macro '
                                  'name [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_22 = ('API check error of [api compatibility errors]:Changing macro value [$$] to macro '
                                  'value [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_23 = ('API check error of [api compatibility errors]:Deleting macro define [$$] is '
                                  'prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_24 = ('API check error of [api compatibility errors]:Changing enum name [$$] to enum name '
                                  '[&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_25 = ('API check error of [api compatibility errors]:Changing enum member name [$$] to '
                                  'enum member name [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_26 = ('API check error of [api compatibility errors]:Changing enum member value [$$] to '
                                  'enum member name [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_27 = ('API check error of [api compatibility errors]:Deleting enum [$$] is prohibited.'
                                  'Please resolve it.')
    API_CHANGE_INCOMPATIBLE_28 = ('API check error of [api compatibility errors]:Deleting enum member [$$] is '
                                  'prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_29 = ('API check error of [api compatibility errors]:Changing struct name [$$] to struct '
                                  'name [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_30 = ('API check error of [api compatibility errors]:Adding struct member [&&] is '
                                  'prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_31 = ('API check error of [api compatibility errors]:Deleting struct member [$$] is '
                                  'prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_32 = ('API check error of [api compatibility errors]:Changing struct member type [$$] to '
                                  'struct member type [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_33 = ('API check error of [api compatibility errors]:Changing struct member name [$$] to '
                                  'struct member name [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_34 = ('API check error of [api compatibility errors]:Deleting struct [$$] is prohibited.'
                                  'Please resolve it.')
    API_CHANGE_INCOMPATIBLE_35 = ('API check error of [api compatibility errors]:Changing struct since [$$] to '
                                  'struct since [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_36 = ('API check error of [api compatibility errors]:Changing union name [$$] to '
                                  'union name [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_37 = ('API check error of [api compatibility errors]:Adding union member [&&] is '
                                  'prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_38 = ('API check error of [api compatibility errors]:Deleting union member [$$] is '
                                  'prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_39 = ('API check error of [api compatibility errors]:Changing union member type [$$] to '
                                  'union member type [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_40 = ('API check error of [api compatibility errors]:Changing union member name [$$] to '
                                  'union member name [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_41 = ('API check error of [api compatibility errors]:Deleting union [$$] is prohibited.'
                                  'Please resolve it.')
    API_CHANGE_INCOMPATIBLE_42 = ('API check error of [api compatibility errors]:Changing union since [$$] to union '
                                  'since [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_43 = ('API check error of [api compatibility errors]:Changing the @library in comments '
                                  'from no to [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_44 = ('API check error of [api compatibility errors]:Changing the @library in comments '
                                  'from [$$] to no is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_45 = ('API check error of [api compatibility errors]:Changing the @library in comments '
                                  'from [$$] to [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_46 = ('API check error of [api compatibility errors]:Changing the @permission in comments '
                                  'is prohibited.Add and relation permission.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_47 = ('API check error of [api compatibility errors]:Changing the @permission in comments '
                                  'is prohibited.Reduce or relation permission.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_48 = ('API check error of [api compatibility errors]:Changing the @permission in comments '
                                  'is prohibited.Permission value change.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_49 = ('API check error of [api compatibility errors]:Changing the @syscap in comments '
                                  'from no to [&&] is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_50 = ('API check error of [api compatibility errors]:Changing the @syscap in comments '
                                  'from [$$] to no is prohibited.Please resolve it.')
    API_CHANGE_INCOMPATIBLE_51 = ('API check error of [api compatibility errors]:Changing the @syscap in comments '
                                  'from [$$] to [&&] is prohibited.Please resolve it.')

    @classmethod
    def get_rule_message(cls, rule):
        return cls[rule].value if rule in cls.__members__ else 'None'


check_compatibility_command_message = [
    member.name for name_compatibility_tool,
    member in CheckCompatibilityErrorMessage.__members__.items()
]


match_diff_and_check_scene_dict = {
    DiffType.REDUCE_API.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_01.name,
    DiffType.REDUCE_FILE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_03.name,
    DiffType.FUNCTION_NAME_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_05.name,
    DiffType.FUNCTION_RETURN_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_06.name,
    DiffType.FUNCTION_PARAM_POS_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_07.name,
    DiffType.FUNCTION_PARAM_ADD.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_08.name,
    DiffType.FUNCTION_PARAM_REDUCE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_09.name,
    DiffType.FUNCTION_PARAM_TYPE_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_10.name,
    DiffType.VARIABLE_NAME_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_11.name,
    DiffType.CONSTANT_NAME_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_12.name,
    DiffType.VARIABLE_TYPE_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_13.name,
    DiffType.CONSTANT_TYPE_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_14.name,
    DiffType.VARIABLE_CHANGE_TO_CONSTANT.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_15.name,
    DiffType.CONSTANT_CHANGE_TO_VARIABLE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_16.name,
    DiffType.VARIABLE_VALUE_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_17.name,
    DiffType.CONSTANT_VALUE_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_18.name,
    DiffType.DEFINE_NAME_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_21.name,
    DiffType.DEFINE_TEXT_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_22.name,
    DiffType.ENUM_NAME_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_24.name,
    DiffType.ENUM_MEMBER_NAME_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_25.name,
    DiffType.ENUM_MEMBER_VALUE_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_26.name,
    DiffType.ENUM_MEMBER_REDUCE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_28.name,
    DiffType.STRUCT_NAME_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_29.name,
    DiffType.STRUCT_MEMBER_ADD.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_30.name,
    DiffType.STRUCT_MEMBER_REDUCE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_31.name,
    DiffType.STRUCT_MEMBER_TYPE_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_32.name,
    DiffType.STRUCT_MEMBER_NAME_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_33.name,
    DiffType.UNION_NAME_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_36.name,
    DiffType.UNION_MEMBER_ADD.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_37.name,
    DiffType.UNION_MEMBER_REDUCE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_38.name,
    DiffType.UNION_MEMBER_TYPE_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_39.name,
    DiffType.UNION_MEMBER_NAME_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_40.name,
    DiffType.DOC_TAG_LIBRARY_NA_TO_HAVE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_43.name,
    DiffType.DOC_TAG_LIBRARY_HAVE_TO_NA.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_44.name,
    DiffType.DOC_TAG_LIBRARY_A_TO_B.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_45.name,
    DiffType.DOC_TAG_PERMISSION_RANGE_SMALLER: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_47.name,
    DiffType.DOC_TAG_PERMISSION_RANGE_CHANGE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_48.name,
    DiffType.DOC_TAG_SYSCAP_NA_TO_HAVE.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_49.name,
    DiffType.DOC_TAG_SYSCAP_HAVE_TO_NA.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_50.name,
    DiffType.DOC_TAG_SYSCAP_A_TO_B.name: CheckCompatibilityErrorMessage.API_CHANGE_INCOMPATIBLE_51.name,
}
