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


from coreImpl.diff.diff_file import check_diff_entrance
from typedef.check.check import CheckOutPut
from typedef.check.check_compatibility import match_diff_and_check_scene_dict, CheckCompatibilityErrorMessage


def process_each_diff_data(diff_data: list, compatibility_rule: list):
    check_compatibility_result_list = []
    for element in diff_data:
        diff_type_message = element.diff_type.name
        match_check_rule = match_diff_and_check_scene_dict.get(diff_type_message)
        if (not element.is_compatible) and match_check_rule and match_check_rule in compatibility_rule:
            old_different_content = str(element.old_differ_content)
            new_different_content = str(element.new_differ_content)
            match_check_message = (CheckCompatibilityErrorMessage.get_rule_message(match_check_rule)
                                   .replace('$$', old_different_content).replace('&&', new_different_content))
            old_declara = element.old_api_declara
            new_declara = element.new_api_declara
            content_line = element.api_line
            if element.file_doc_line != 0:
                content_line = element.file_doc_line
            main_buggy_code = 'Old since:{}\nNew since:{}'.format(old_declara, new_declara)
            result_obj = CheckOutPut(element.api_file_path, content_line, match_check_rule, match_check_message,
                                     main_buggy_code, content_line)
            check_compatibility_result_list.append(result_obj)

    return check_compatibility_result_list


def check_compatibility_entrance(old_dir, new_dir, compatibility_rule: list):
    diff_data = check_diff_entrance(old_dir, new_dir)
    check_compatibility_data_list = process_each_diff_data(diff_data, compatibility_rule)

    return check_compatibility_data_list
