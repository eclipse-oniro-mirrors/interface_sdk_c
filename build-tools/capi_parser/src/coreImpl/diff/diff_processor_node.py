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

import json
import subprocess
import os
import re
from collections import OrderedDict
from clang.cindex import CursorKind
from coreImpl.diff.diff_processor_permission import compare_permission, RangeChange
from typedef.diff.diff import TAGS, DiffType, DiffInfo, Scene
from utils.constants import RegularExpressions

current_file = os.path.dirname(__file__)
change_data_total = []


def get_not_api_kind_list():
    not_api_kind_list = [
        'MACRO_DEFINITION',
        'TRANSLATION_UNIT',
        'MACRO_INSTANTIATION',
        'INCLUSION_DIRECTIVE'
    ]
    return not_api_kind_list


def set_result_common_infor(node_infor, diff_info: DiffInfo):
    diff_info.set_api_name(node_infor['name'])
    diff_info.set_api_type(node_infor['kind'])
    diff_info.set_api_line(node_infor['location']['location_line'])
    diff_info.set_api_column(node_infor['location']['location_column'])
    diff_info.set_api_file_path(node_infor['location']['location_path'])
    diff_info.set_kit_name(node_infor['kit_name'])
    diff_info.set_sub_system(node_infor['sub_system'])
    diff_info.set_class_name(node_infor.get('class_name'))
    diff_info.set_unique_id(node_infor.get('unique_id'))


def wrap_diff_info(old_info, new_info, diff_info: DiffInfo):
    struct_union_enum = [Scene.STRUCT_DECL.value, Scene.ENUM_DECL.value, Scene.UNION_DECL.value,
                         Scene.TYPEDEF_DECL.value]
    if old_info is not None:
        if 'temporary_name' in old_info['name']:
            old_info['name'] = ''
        set_result_common_infor(old_info, diff_info)
        if 'NA' == old_info.get('is_system_api'):
            diff_info.set_is_system_api(False)
        else:
            diff_info.set_is_system_api(True)
        if 'content' in old_info['node_content']:
            if old_info['kind'] in struct_union_enum:
                api_declare = old_info['type']
            else:
                api_declare = old_info['node_content']['content']

        else:
            api_declare = old_info['name']
        if old_info['kind'] != 'TRANSLATION_UNIT':
            diff_info.set_old_api_declara(api_declare)
        old_content = '类名:{};\nAPI声明:{};\n差异内容:{}\n'.format(diff_info.class_name, api_declare,
                                                            diff_info.old_differ_content)
        diff_info.set_old_api_full_text(old_content)

    if new_info is not None:
        if 'temporary_name' in new_info['name']:
            new_info['name'] = ''
        set_result_common_infor(new_info, diff_info)
        if 'NA' == new_info.get('is_system_api'):
            diff_info.set_is_system_api(False)
        else:
            diff_info.set_is_system_api(True)
        if 'content' in new_info['node_content']:
            if new_info['kind'] in struct_union_enum:
                api_declare = new_info['type']
            else:
                api_declare = new_info['node_content']['content']
        else:
            api_declare = new_info['name']
        if new_info['kind'] != 'TRANSLATION_UNIT':
            diff_info.set_new_api_declara(api_declare)
        new_content = '类名:{};\nAPI声明:{};\n差异内容:{}\n'.format(diff_info.class_name, api_declare,
                                                            diff_info.new_differ_content)

        diff_info.set_new_api_full_text(new_content)

    return diff_info


def parse_file_result(result):
    result_map = {}
    key = 1
    for member in result:
        if member["name"] == '':
            name = 'temporary_name'
            member["name"] = '{}{}'.format(name, key)
            key += 1
        result_map.setdefault(f'{member["name"]}-{member["kind"]}', member)
    return result_map


def get_member_result_diff(old_target, new_target):
    old_member_result_map = parse_file_result(old_target)
    new_member_result_map = parse_file_result(new_target)
    merged_dict = OrderedDict(list(old_member_result_map.items()) + list(new_member_result_map.items()))
    all_key_list = merged_dict.keys()
    return old_member_result_map, new_member_result_map, all_key_list


def get_initial_result_obj(diff_type: DiffType, old_differ_content, new_differ_content):
    result_message_obj = DiffInfo(diff_type, old_differ_content, new_differ_content)

    return result_message_obj


def process_function(old, new):
    diff_info_list = []
    process_func_return(old, new, diff_info_list)  # 处理返回值
    process_func_param(old, new, diff_info_list)  # 处理参数
    return diff_info_list


def process_func_return(old, new, diff_info_list):
    if old['return_type'] != new['return_type']:
        old_return_content = old['return_type']
        new_return_content = new['return_type']
        result_message_obj = get_initial_result_obj(DiffType.FUNCTION_RETURN_CHANGE,
                                                    old_return_content, new_return_content)
        diff_info = wrap_diff_info(old, new, result_message_obj)
        diff_info_list.append(diff_info)


def process_func_param_location(old_param_list, new_param_list, old, new):
    result_list = []
    old_param_str_list = get_param_name_and_type(old_param_list)
    new_param_str_list = get_param_name_and_type(new_param_list)
    old_param_str_content = ' '.join(old_param_str_list)
    new_param_str_content = ' '.join(new_param_str_list)
    if old_param_str_content == new_param_str_content:
        return result_list
    old_len = len(old_param_list)
    for i, element in enumerate(old_param_str_list):
        if element not in new_param_str_list:
            return result_list
        if i != new_param_str_list.index(element) and i + 1 <= old_len:
            old_differ_content = old_param_list[i]['node_content']['content']
            new_differ_content = new_param_list[i]['node_content']['content']
            result_obj = wrap_diff_info(old, new, DiffInfo(DiffType.FUNCTION_PARAM_POS_CHANGE,
                                                           old_differ_content, new_differ_content))
            result_list.append(result_obj)
    return result_list


def get_param_name_and_type(param_list):
    param_str_list = []
    for param in param_list:
        if 'name' in param and 'type' in param:
            param_str = '{} {}'.format(param.get('type'), param.get('name'))
            param_str_list.append(param_str)
    return param_str_list


def process_each_param(old, new, old_len, new_len, diff_info_list):
    for i in range(max(old_len, new_len)):
        if (i + 1) > new_len:  # 减少参数
            old_param_content = old['parm'][i]['node_content']['content']
            new_param_content = 'NA'
            result_message_obj = get_initial_result_obj(DiffType.FUNCTION_PARAM_REDUCE,
                                                        old_param_content, new_param_content)
            diff_info = wrap_diff_info(old, new, result_message_obj)
            diff_info_list.append(diff_info)

        elif (i + 1) > old_len:  # 增加参数
            old_param_content = 'NA'
            new_param_content = new['parm'][i]['node_content']['content']
            result_message_obj = get_initial_result_obj(DiffType.FUNCTION_PARAM_ADD,
                                                        old_param_content, new_param_content)
            diff_info = wrap_diff_info(old, new, result_message_obj)
            diff_info_list.append(diff_info)

        else:
            diff_info_result = process_param_scene(old['parm'], new['parm'], i, old, new)
            diff_info_list.extend(diff_info_result)


def get_param_content(param_infor: list):
    if not param_infor:
        param_content = 'NA'
        return param_content
    if 1 == len(param_infor):
        param_content = '({})'.format(param_infor[0]['node_content']['content'])
        return param_content
    param_content = '('
    for element in param_infor:
        param_content = '{},{}'.format(param_content, element['node_content']['content'])
    param_content = '{}{}'.format(param_content, ')')
    return param_content


def process_func_param(old, new, diff_info_list):
    if 'parm' in old and 'parm' in new:
        old_len = len(old['parm'])
        new_len = len(new['parm'])
        result_obj_list = []
        if old_len == new_len:
            result_obj_list = process_func_param_location(old['parm'], new['parm'], old, new)
            diff_info_list.extend(result_obj_list)
        if not result_obj_list:
            process_each_param(old, new, old_len, new_len, diff_info_list)

    elif 'parm' not in old and 'parm' in new:  # 旧无新有
        old_param_content = 'NA'
        new_param_content = get_param_content(new['parm'])
        if new_param_content != 'NA':
            result_message_obj = get_initial_result_obj(DiffType.FUNCTION_PARAM_ADD,
                                                        old_param_content, new_param_content)
            diff_info = wrap_diff_info(old, new, result_message_obj)
            diff_info_list.append(diff_info)

    elif 'parm' in old and 'parm' not in new:  # 旧有新无
        old_param_content = get_param_content(old['parm'])
        new_param_content = 'NA'
        if old_param_content != 'NA':
            result_message_obj = get_initial_result_obj(DiffType.FUNCTION_PARAM_REDUCE,
                                                        old_param_content, new_param_content)
            diff_info = wrap_diff_info(old, new, result_message_obj)
            diff_info_list.append(diff_info)


def process_param_scene(old_param, new_param, index, parent_old, parent_new):
    diff_info_list = []
    if old_param[index]['type'] != new_param[index]['type']:
        old_param_type_content = old_param[index]['type']
        new_param_type_content = new_param[index]['type']
        result_message_obj = get_initial_result_obj(DiffType.FUNCTION_PARAM_TYPE_CHANGE,
                                                    old_param_type_content, new_param_type_content)
        diff_info = wrap_diff_info(parent_old, parent_new, result_message_obj)
        diff_info_list.append(diff_info)

    if old_param[index]['name'] != new_param[index]['name']:
        old_param_name_content = old_param[index]['name']
        new_param_name_content = new_param[index]['name']
        result_message_obj = get_initial_result_obj(DiffType.FUNCTION_PARAM_NAME_CHANGE,
                                                    old_param_name_content, new_param_name_content)
        diff_info = wrap_diff_info(parent_old, parent_new, result_message_obj)
        diff_info_list.append(diff_info)

    return diff_info_list


def process_define(old, new):
    diff_define_list = []
    process_define_name(old, new, diff_define_list)  # 处理宏名
    process_define_text(old, new, diff_define_list)  # 处理宏文本
    return diff_define_list


def process_define_name(old, new, diff_define_list):
    if old['name'] != new['name']:
        old_define_name = old['name']
        new_define_name = new['name']
        result_message_obj = get_initial_result_obj(DiffType.DEFINE_NAME_CHANGE,
                                                    old_define_name, new_define_name)
        diff_info = wrap_diff_info(old, new, result_message_obj)
        diff_define_list.append(diff_info)


def process_define_text(old, new, diff_define_list):
    if 'text' not in old and 'text' in new:  # 旧无新有
        old_define_text = 'NA'
        new_define_text = new['text']
        result_message_obj = get_initial_result_obj(DiffType.DEFINE_TEXT_CHANGE,
                                                    old_define_text, new_define_text)
        diff_info = wrap_diff_info(old, new, result_message_obj)
        diff_define_list.append(diff_info)
    elif 'text' in old and 'text' not in new:  # 旧有新无
        old_define_text = old['text']
        new_define_text = 'NA'
        result_message_obj = get_initial_result_obj(DiffType.DEFINE_TEXT_CHANGE,
                                                    old_define_text, new_define_text)
        diff_info = wrap_diff_info(old, new, result_message_obj)
        diff_define_list.append(diff_info)
    elif 'text' in old and 'text' in new:
        if old['text'] != new['text']:
            old_define_text = old['text']
            new_define_text = new['text']
            result_message_obj = get_initial_result_obj(DiffType.DEFINE_TEXT_CHANGE,
                                                        old_define_text, new_define_text)
            diff_info = wrap_diff_info(old, new, result_message_obj)
            diff_define_list.append(diff_info)


def process_struct(old, new):
    diff_struct_list = []
    process_struct_name(old, new, diff_struct_list)  # 处理结构体名
    process_struct_member(old, new, diff_struct_list)  # 处理结构体成员
    return diff_struct_list


def process_struct_name(old, new, diff_struct_list):
    if old['name'] != new['name']:
        old_struct_name = old['name']
        new_struct_name = new['name']
        result_message_obj = get_initial_result_obj(DiffType.STRUCT_NAME_CHANGE,
                                                    old_struct_name, new_struct_name)
        diff_info = wrap_diff_info(old, new, result_message_obj)
        diff_struct_list.append(diff_info)


def get_member_content(member_infor: list):
    if not member_infor:
        member_content = 'NA'
        return member_content
    if member_infor[0]['type'] == 'FIELD_DECL':
        end_float = ';'
    else:
        end_float = ','
    if 1 == len(member_infor):
        member_content = '{}'.format(member_infor[0]['node_content']['content'])
        return member_content
    member_content = ''
    for element in member_infor:
        member_content = '{}{}{}'.format(member_content, end_float, element['node_content']['content'])
    return member_content


def process_struct_member(old, new, diff_struct_list):
    if 'members' in old and 'members' in new:  # 都有
        old_member_result, new_member_result, all_key_result = get_member_result_diff(old['members'],
                                                                                      new['members'])
        for key in all_key_result:
            if old_member_result.get(key) is None:
                old_member_content = 'NA'
                new_member_content = new_member_result.get(key)['node_content']['content']
                result_message_obj = get_initial_result_obj(DiffType.STRUCT_MEMBER_ADD,
                                                            old_member_content, new_member_content)
                diff_info = wrap_diff_info(old_member_result.get(key), new_member_result.get(key),
                                           result_message_obj)
                diff_struct_list.append(diff_info)
            elif new_member_result.get(key) is None:
                old_member_content = old_member_result.get(key)['node_content']['content']
                new_member_content = 'NA'
                result_message_obj = get_initial_result_obj(DiffType.STRUCT_MEMBER_REDUCE,
                                                            old_member_content, new_member_content)
                diff_info = wrap_diff_info(old_member_result.get(key), new_member_result.get(key),
                                           result_message_obj)
                diff_struct_list.append(diff_info)
            else:
                process_struct_member_scene(old_member_result.get(key),
                                            new_member_result.get(key), diff_struct_list)

    elif 'members' not in old and 'members' in new:  # 旧无新有
        old_member_content = 'NA'
        new_member_content = get_member_content(new['members'])
        if new_member_content != 'NA':
            result_message_obj = get_initial_result_obj(DiffType.STRUCT_MEMBER_ADD,
                                                        old_member_content, new_member_content)
            diff_info = wrap_diff_info(old, new, result_message_obj)
            diff_struct_list.append(diff_info)

    elif 'members' in old and 'members' not in new:  # 旧有新无
        old_member_content = get_member_content(old['members'])
        new_member_content = 'NA'
        if old_member_content != 'NA':
            result_message_obj = get_initial_result_obj(DiffType.STRUCT_MEMBER_REDUCE,
                                                        old_member_content, new_member_content)
            diff_info = wrap_diff_info(old, new, result_message_obj)
            diff_struct_list.append(diff_info)


def process_struct_member_scene(old_member, new_member, diff_struct_list):
    special_data = []  # 存储嵌套的体系
    if (old_member['kind'] == Scene.STRUCT_DECL.value) and \
            (new_member['kind'] == Scene.STRUCT_DECL.value):  # 结构体套结构体
        special_data = process_struct(old_member, new_member)

    elif (old_member['kind'] == Scene.UNION_DECL.value) and \
            (new_member['kind'] == Scene.UNION_DECL.value):  # 结构体套联合体
        special_data = process_union(old_member, new_member)

    elif (old_member['kind'] == Scene.ENUM_DECL.value) and \
            (new_member['kind'] == Scene.ENUM_DECL.value):  # 结构体套枚举
        special_data = process_enum(old_member, new_member)
    diff_struct_list.extend(special_data)

    if (not (old_member['location']['location_path'] in old_member['type'])) and \
            (not (new_member['location']['location_path'] in new_member['type'])):
        if old_member['type'] != new_member['type']:
            old_member_type = old_member['type']
            new_member_type = new_member['type']
            result_message_obj = get_initial_result_obj(DiffType.STRUCT_MEMBER_TYPE_CHANGE,
                                                        old_member_type, new_member_type)
            diff_info = wrap_diff_info(old_member, new_member,
                                       result_message_obj)
            diff_struct_list.append(diff_info)

    if old_member['name'] != new_member['name']:
        old_member_name = old_member['name']
        new_member_name = new_member['name']
        result_message_obj = get_initial_result_obj(DiffType.STRUCT_MEMBER_NAME_CHANGE,
                                                    old_member_name, new_member_name)
        diff_info = wrap_diff_info(old_member, new_member,
                                   result_message_obj)
        diff_struct_list.append(diff_info)


def process_union(old, new):
    diff_union_list = []
    process_union_name(old, new, diff_union_list)  # 处理联合体名
    process_union_member(old, new, diff_union_list)  # 处理联合体成员
    return diff_union_list


def process_union_name(old, new, diff_union_list):
    if old['name'] != new['name']:
        old_union_name = old['name']
        new_union_name = new['name']
        result_message_obj = get_initial_result_obj(DiffType.UNION_NAME_CHANGE,
                                                    old_union_name, new_union_name)
        diff_info = wrap_diff_info(old, new, result_message_obj)
        diff_union_list.append(diff_info)


def process_union_member(old, new, diff_union_list):
    if 'members' in old and 'members' in new:  # 都有
        old_member_result, new_member_result, all_key_result = get_member_result_diff(old['members'],
                                                                                      new['members'])
        for key in all_key_result:
            if old_member_result.get(key) is None:
                old_member_content = 'NA'
                new_member_content = new_member_result.get(key)['node_content']['content']
                result_message_obj = get_initial_result_obj(DiffType.UNION_MEMBER_ADD,
                                                            old_member_content, new_member_content)

                diff_info = wrap_diff_info(old_member_result.get(key), new_member_result.get(key),
                                           result_message_obj)
                diff_union_list.append(diff_info)
            elif new_member_result.get(key) is None:
                old_member_content = old_member_result.get(key)['node_content']['content']
                new_member_content = 'NA'
                result_message_obj = get_initial_result_obj(DiffType.UNION_MEMBER_REDUCE,
                                                            old_member_content, new_member_content)

                diff_info = wrap_diff_info(old_member_result.get(key), new_member_result.get(key),
                                           result_message_obj)
                diff_union_list.append(diff_info)
            else:
                process_union_member_scene(old_member_result.get(key),
                                           new_member_result.get(key), diff_union_list)

    elif 'members' not in old and 'members' in new:  # 旧无新有
        old_member_content = 'NA'
        new_member_content = get_member_content(new['members'])
        if new_member_content != 'NA':
            diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.UNION_MEMBER_ADD,
                                                          old_member_content, new_member_content))
            diff_union_list.append(diff_info)

    elif 'members' in old and 'members' not in new:  # 旧有新无
        old_member_content = get_member_content(old['members'])
        new_member_content = 'NA'
        if old_member_content != 'NA':
            diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.UNION_MEMBER_REDUCE,
                                                          old_member_content, new_member_content))
            diff_union_list.append(diff_info)


def process_union_member_scene(old_member, new_member, diff_union_list):
    special_data = []  # 存储嵌套的体系
    if (old_member['kind'] == Scene.STRUCT_DECL.value) and \
            (new_member['kind'] == Scene.STRUCT_DECL.value):  # 联合体套结构体
        special_data = process_struct(old_member, new_member)

    elif (old_member['kind'] == Scene.UNION_DECL.value) and \
            (new_member['kind'] == Scene.UNION_DECL.value):  # 联合体套联合体
        special_data = process_union(old_member, new_member)

    elif (old_member['kind'] == Scene.ENUM_DECL.value) and \
            (new_member['kind'] == Scene.ENUM_DECL.value):  # 联合体套枚举
        special_data = process_enum(old_member, new_member)
    diff_union_list.extend(special_data)

    if (not (old_member['location']['location_path'] in old_member['type'])) and \
            (not (new_member['location']['location_path'] in new_member['type'])):
        if old_member['type'] != new_member['type']:
            old_member_type = old_member['type']
            new_member_type = new_member['type']
            diff_info = wrap_diff_info(old_member, new_member, DiffInfo(DiffType.UNION_MEMBER_TYPE_CHANGE,
                                                                        old_member_type, new_member_type))
            diff_union_list.append(diff_info)

    if old_member['name'] != new_member['name']:
        old_member_name = old_member['name']
        new_member_name = new_member['name']
        diff_info = wrap_diff_info(old_member, new_member, DiffInfo(DiffType.UNION_MEMBER_NAME_CHANGE,
                                                                    old_member_name, new_member_name))
        diff_union_list.append(diff_info)


def process_enum(old, new):
    diff_enum_list = []
    process_enum_name(old, new, diff_enum_list)  # 处理枚举名
    process_enum_member(old, new, diff_enum_list)  # 处理枚举成员
    return diff_enum_list


def process_enum_name(old, new, diff_enum_list):
    if old['name'] != new['name']:
        old_enum_name = old['name']
        new_enum_name = new['name']
        diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.ENUM_NAME_CHANGE, old_enum_name, new_enum_name))
        diff_enum_list.append(diff_info)


def process_enum_member(old, new, diff_enum_list):
    if 'members' in old and 'members' in new:  # 都有
        old_member_result, new_member_result, all_key_result = get_member_result_diff(old['members'],
                                                                                      new['members'])
        for key in all_key_result:
            if old_member_result.get(key) is None:
                old_member_content = 'NA'
                new_member_content = new_member_result.get(key)['node_content']['content']
                diff_info = wrap_diff_info(old_member_result.get(key), new_member_result.get(key),
                                           DiffInfo(DiffType.ENUM_MEMBER_ADD, old_member_content,
                                                    new_member_content))
                diff_enum_list.append(diff_info)
            elif new_member_result.get(key) is None:
                old_member_content = old_member_result.get(key)['node_content']['content']
                new_member_content = 'NA'
                diff_info = wrap_diff_info(old_member_result.get(key), new_member_result.get(key),
                                           DiffInfo(DiffType.ENUM_MEMBER_REDUCE, old_member_content,
                                                    new_member_content))
                diff_enum_list.append(diff_info)
            else:
                process_enum_member_scene(old_member_result.get(key),
                                          new_member_result.get(key), diff_enum_list)

    elif 'members' not in old and 'members' in new:  # 旧无新有
        old_member_content = 'NA'
        new_member_content = get_member_content(new['members'])
        if new_member_content != 'NA':
            diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.ENUM_MEMBER_ADD,
                                                          old_member_content, new_member_content))
            diff_enum_list.append(diff_info)

    elif 'members' in old and 'members' not in new:  # 旧有新无
        old_member_content = get_member_content(new['members'])
        new_member_content = 'NA'
        if old_member_content != 'NA':
            diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.ENUM_MEMBER_REDUCE,
                                                          old_member_content, new_member_content))
            diff_enum_list.append(diff_info)


def process_enum_member_scene(old_member, new_member, diff_union_list):
    if old_member['value'] != new_member['value']:
        old_enum_value = old_member['value']
        new_enum_value = new_member['value']
        diff_info = wrap_diff_info(old_member, new_member,
                                   DiffInfo(DiffType.ENUM_MEMBER_VALUE_CHANGE, old_enum_value, new_enum_value))
        diff_union_list.append(diff_info)

    if old_member['name'] != new_member['name']:
        old_member_name = old_member['name']
        new_member_name = new_member['name']
        diff_info = wrap_diff_info(old_member, new_member,
                                   DiffInfo(DiffType.ENUM_MEMBER_NAME_CHANGE, old_member_name, new_member_name))
        diff_union_list.append(diff_info)


def process_variable_const(old, new):
    diff_var_or_con = []
    if 'is_const' in old:
        if old['is_const']:  # 处理常量
            if 'is_const' in new and new['is_const']:
                process_constant_type(old, new, diff_var_or_con)  # 处理常量类型
            elif 'is_const' in new and (not new['is_const']):  # 处理常量变变量
                process_const_change_variable(old, new, diff_var_or_con)
            process_constant_name(old, new, diff_var_or_con)  # 处理常量名
            process_constant_value(old, new, diff_var_or_con)  # 处理常量值

        else:  # 处理变量
            if 'is_const' in new and new['is_const']:
                process_variable_change_const(old, new, diff_var_or_con)  # 处理变量变常量
            elif 'is_const' in new and (not new['is_const']):
                process_variable_type(old, new, diff_var_or_con)  # 处理变量类型
            process_variable_name(old, new, diff_var_or_con)  # 处理变量名
            process_variable_value(old, new, diff_var_or_con)  # 处理变量值

    return diff_var_or_con


def process_const_change_variable(old, new, diff_variable_list):
    if 'is_const' in new and (not new['is_const']):
        old_const_type = old['type']
        new_const_type = new['type']
        diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.CONSTANT_CHANGE_TO_VARIABLE,
                                                      old_const_type, new_const_type))
        diff_variable_list.append(diff_info)


def process_variable_change_const(old, new, diff_variable_list):
    if 'is_const' in new and new['is_const']:
        old_variable_type = old['type']
        new_variable_type = new['type']
        diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.VARIABLE_CHANGE_TO_CONSTANT,
                                                      old_variable_type, new_variable_type))
        diff_variable_list.append(diff_info)


def process_variable_name(old, new, diff_variable_list):
    if old['name'] != new['name']:
        old_variable_name = old['name']
        new_variable_name = new['name']
        diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.VARIABLE_NAME_CHANGE,
                                                      old_variable_name, new_variable_name))
        diff_variable_list.append(diff_info)


def process_variable_type(old, new, diff_variable_list):
    if old['type'] != new['type']:
        old_variable_type = old['type']
        new_variable_type = new['type']
        diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.VARIABLE_TYPE_CHANGE,
                                                      old_variable_type, new_variable_type))
        diff_variable_list.append(diff_info)


def process_variable_value(old, new, diff_variable_list):
    if 'children' in old and 'children' in new:
        if len(old['children']) and len(new['children']) \
                and old['children'][0]['node_content']['content'] != new['children'][0]['node_content']['content']:
            old_variable_value = old['children'][0]['node_content']['content']
            new_variable_value = new['children'][0]['node_content']['content']
            diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.VARIABLE_VALUE_CHANGE,
                                                          old_variable_value, new_variable_value))
            diff_variable_list.append(diff_info)

    elif 'children' not in old and 'children' in new and len(new['children']):
        old_variable_value = 'NA'
        new_variable_value = new['children'][0]['node_content']['content']
        diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.VARIABLE_VALUE_CHANGE,
                                                      old_variable_value, new_variable_value))
        diff_variable_list.append(diff_info)

    elif 'children' in old and 'children' not in new and len(old['children']):
        old_variable_value = old['children'][0]['node_content']['content']
        new_variable_value = 'NA'
        diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.VARIABLE_VALUE_CHANGE,
                                                      old_variable_value, new_variable_value))
        diff_variable_list.append(diff_info)


def process_constant_to_variable(old, new, diff_constant_list):
    if not new['is_const']:
        old_const_type = old['type']
        new_const_type = new['type']
        diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.CONSTANT_CHANGE_TO_VARIABLE,
                                                      old_const_type, new_const_type))
        diff_constant_list.append(diff_info)


def process_constant_name(old, new, diff_constant_list):
    if old['name'] != new['name']:
        old_const_name = old['name']
        new_const_name = new['name']
        diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.CONSTANT_NAME_CHANGE, old_const_name, new_const_name))
        diff_constant_list.append(diff_info)


def process_constant_type(old, new, diff_constant_list):
    if old['type'] != new['type']:
        old_const_type = old['type']
        new_const_type = new['type']
        diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.CONSTANT_TYPE_CHANGE, old_const_type, new_const_type))
        diff_constant_list.append(diff_info)


def process_constant_value(old, new, diff_constant_list):
    if 'children' in old and 'children' in new:
        if len(old['children']) and len(new['children']) \
                and old['children'][0]['node_content']['content'] != new['children'][0]['node_content']['content']:
            old_const_value = old['children'][0]['node_content']['content']
            new_const_value = new['children'][0]['node_content']['content']
            diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.CONSTANT_VALUE_CHANGE,
                                                          old_const_value, new_const_value))
            diff_constant_list.append(diff_info)

    elif 'children' not in old and 'children' in new and len(new['children']):
        old_none = None
        old_const_value = 'NA'
        new_const_value = new['children'][0]['node_content']['content']
        diff_info = wrap_diff_info(old_none, new, DiffInfo(DiffType.CONSTANT_VALUE_CHANGE,
                                                           old_const_value, new_const_value))
        diff_constant_list.append(diff_info)

    elif 'children' in old and 'children' not in new and len(old['children']):
        new_none = None
        old_const_value = old['children'][0]['node_content']['content']
        new_const_value = 'NA'
        diff_info = wrap_diff_info(old, new_none, DiffInfo(DiffType.CONSTANT_VALUE_CHANGE, old_const_value,
                                                           new_const_value))
        diff_constant_list.append(diff_info)


def process_typedef(old, new):
    diff_typedef_list = []
    process_typedef_name(old, new, diff_typedef_list)  # 处理命名

    if 'children' in old and 'children' in new:  # 处理子节点
        process_typedef_child(old['children'], new['children'], diff_typedef_list)

    return diff_typedef_list


def process_typedef_name(old, new, diff_typedef_list):
    if old['name'] != new['name']:
        old_typedef_name = old['name']
        new_typedef_name = new['name']
        diff_info = wrap_diff_info(old, new, DiffInfo(DiffType.TYPEDEF_NAME_TYPE_CHANGE,
                                                      old_typedef_name, new_typedef_name))
        diff_typedef_list.append(diff_info)


def process_typedef_child(old_child, new_child, diff_typedef_list):
    special_data = []  # 存储嵌套的体系
    for i, _ in enumerate(old_child):
        if old_child[i]['name'] == '' and new_child[i]['name'] == '':
            if old_child[i]['kind'] == Scene.STRUCT_DECL.value and \
                    new_child[i]['kind'] == Scene.STRUCT_DECL.value:
                special_data = process_struct(old_child[i], new_child[i])

            elif old_child[i]['kind'] == Scene.UNION_DECL.value and \
                    new_child[i]['kind'] == Scene.UNION_DECL.value:
                special_data = process_union(old_child[i], new_child[i])

            elif old_child[i]['kind'] == Scene.ENUM_DECL.value and \
                    new_child[i]['kind'] == Scene.ENUM_DECL.value:
                special_data = process_enum(old_child[i], new_child[i])

            diff_typedef_list.extend(special_data)


def process_anonymous_enum_member(old_info, new_info):
    result_obj_list = []
    if old_info and new_info:
        if old_info['name'] != new_info['name']:
            change_message_obj = DiffInfo(DiffType.ENUM_MEMBER_NAME_CHANGE, old_info['name'], new_info['name'])
            result_obj_list.append(wrap_diff_info(old_info, new_info, change_message_obj))
        if old_info['value'] != new_info['value']:
            change_message_obj = DiffInfo(DiffType.ENUM_MEMBER_VALUE_CHANGE, old_info['value'], new_info['value'])
            result_obj_list.append(wrap_diff_info(old_info, new_info, change_message_obj))
    else:
        if old_info:
            change_message_obj = DiffInfo(DiffType.ENUM_MEMBER_REDUCE, old_info['node_content']['content'], 'NA')
            result_obj_list.append(wrap_diff_info(old_info, new_info, change_message_obj))

        elif new_info:
            change_message_obj = DiffInfo(DiffType.ENUM_MEMBER_ADD, 'NA', new_info['node_content']['content'])
            result_obj_list.append(wrap_diff_info(old_info, new_info, change_message_obj))

    return result_obj_list


process_data = {
    Scene.FUNCTION_DECL.value: process_function,
    Scene.MACRO_DEFINITION.value: process_define,
    Scene.STRUCT_DECL.value: process_struct,
    Scene.UNION_DECL.value: process_union,
    Scene.ENUM_DECL.value: process_enum,
    Scene.VAR_DECL.value: process_variable_const,
    Scene.TYPEDEF_DECL.value: process_typedef,
    Scene.ENUM_CONSTANT_DECL.value: process_anonymous_enum_member,
}


def get_ch_api_kind(dict_key):
    if dict_key == Scene.ENUM_CONSTANT_DECL.value:
        key = 'ENUM_DECL'
    else:
        key = dict_key
    api_kind_dict = {
        'FUNCTION_DECL': '函数类型',
        'MACRO_DEFINITION': '宏定义类型',
        'STRUCT_DECL': '结构体类型',
        'UNION_DECL': '联合体类型',
        'ENUM_DECL': '枚举类型',
        'VAR_DECL': '常/变量类型',
        'TYPEDEF_DECL': '重命名类型',
        'TRANSLATION_UNIT': 'NA'
    }
    return api_kind_dict.get(key)


def collect_change_data_total(data: dict, diff_info_list):
    for element in diff_info_list:
        element.set_api_node_name(data['name'])
        if (data['kind'] == Scene.STRUCT_DECL.value or data['kind'] == Scene.UNION_DECL.value
           or data['kind'] == Scene.ENUM_DECL.value) and (not data['name']):
            element.set_api_node_name(data['type'])
        element.set_current_api_unique_id(data['unique_id'])
        element.set_open_close_api(data['open_close_api'])
        element.set_is_third_party_api(data['is_third_party_api'])
        element.set_current_api_type(get_ch_api_kind(data['kind']))
    change_data_total.append(diff_info_list)


def set_is_api_change_result(result_data, key_extern):
    for element in result_data:
        if key_extern:
            element.set_is_api_change(True)


def process_add_node(add_infor, key_extern, struct_union_enum):
    diff_info_list = []
    old_infor = None
    if add_infor['kind'] == Scene.TRANSLATION_UNIT.value:
        return diff_info_list
    if 'is_extern' in add_infor and add_infor['is_extern']:
        key_extern = True
    if add_infor['kind'] == Scene.ENUM_CONSTANT_DECL.value:
        result_obj_list = process_anonymous_enum_member(old_infor, add_infor)
        diff_info_list.extend(result_obj_list)
    else:
        if add_infor['kind'] in struct_union_enum:
            new_api_content = add_infor['type']
        else:
            new_api_content = add_infor['node_content']['content']
        diff_info_list.append(wrap_diff_info(old_infor, add_infor, DiffInfo(DiffType.ADD_API,
                                                                            'NA', new_api_content)))
    set_is_api_change_result(diff_info_list, key_extern)
    collect_change_data_total(add_infor, diff_info_list)

    return diff_info_list


def process_reduce_node(reduce_infor, key_extern, struct_union_enum):
    diff_info_list = []
    new_infor = None
    if reduce_infor['kind'] == Scene.TRANSLATION_UNIT.value:
        return diff_info_list
    if 'is_extern' in reduce_infor and reduce_infor['is_extern']:
        key_extern = True
    if reduce_infor['kind'] == Scene.ENUM_CONSTANT_DECL.value:
        result_obj_list = process_anonymous_enum_member(reduce_infor, new_infor)
        diff_info_list.extend(result_obj_list)
    else:
        if reduce_infor['kind'] in struct_union_enum:
            old_api_content = reduce_infor['type']
        else:
            old_api_content = reduce_infor['node_content']['content']
        diff_info_list.append(wrap_diff_info(reduce_infor, new_infor, DiffInfo(DiffType.REDUCE_API,
                                                                               old_api_content, 'NA')))
    set_is_api_change_result(diff_info_list, key_extern)
    collect_change_data_total(reduce_infor, diff_info_list)

    return diff_info_list


def judgment_entrance(old, new, data_type=0):
    """
    Args:
        old: ***
        new: ***
        data_type(int): 数据处理类型。1-文件新增或删除；0-其他
    """
    diff_info_list = []
    struct_union_enum = [Scene.STRUCT_DECL.value, Scene.UNION_DECL.value,
                         Scene.ENUM_DECL.value, Scene.TYPEDEF_DECL.value]
    key_extern = False
    if old is None and new is None:
        return diff_info_list
    if old is None:
        diff_info_list.extend(process_add_node(new, key_extern, struct_union_enum))
        return diff_info_list
    if new is None:
        diff_info_list.extend(process_reduce_node(old, key_extern, struct_union_enum))
        return diff_info_list
    kind = new['kind']
    if 'is_extern' in old and old['is_extern']:
        key_extern = True
    diff_info_list.extend(process_comment_str(old, new))
    if kind in process_data:
        diff_info_list.extend(process_data[kind](old, new))
    if diff_info_list:
        set_is_api_change_result(diff_info_list, key_extern)
        collect_change_data_total(new, diff_info_list)
    return diff_info_list


def process_tag_addtogroup(old_tag, new_tag, old_info, new_info):
    diff_info_list = []
    if old_tag is None:
        diff_info_list.append(
            wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_ADDTOGROUP_NA_TO_HAVE,
                                                        'NA', new_tag['name'])))
        return diff_info_list
    if new_tag is None:
        diff_info_list.append(
            wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_ADDTOGROUP_HAVE_TO_NA,
                                                        old_tag['name'], 'NA')))
        return diff_info_list
    if old_tag['name'] != new_tag['name']:
        diff_info_list.append(wrap_diff_info(old_info, new_info,
                                             DiffInfo(DiffType.DOC_TAG_ADDTOGROUP_A_TO_B, old_tag['name'],
                                                      new_tag['name'])))
    return diff_info_list


def process_tag_brief(old_tag, new_tag, old_info, new_info):
    diff_info_list = []
    if old_tag is None:
        diff_info_list.append(wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_BRIEF_NA_TO_HAVE,
                                                                          'NA',
                                                                          f'{new_tag["name"]} '
                                                                          f'{new_tag["description"]}')))
        return diff_info_list
    if new_tag is None:
        diff_info_list.append(wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_BRIEF_HAVE_TO_NA,
                                                                          f'{old_tag["name"]} '
                                                                          f'{old_tag["description"]}',
                                                                          'NA')))
        return diff_info_list
    old_brief = f'{old_tag["name"]} {old_tag["description"]}'
    new_brief = f'{new_tag["name"]} {new_tag["description"]}'
    if old_brief != new_brief:
        diff_info_list.append(
            wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_BRIEF_A_TO_B, old_brief, new_brief)))
    return diff_info_list


def process_tag_deprecated(old_tag, new_tag, old_info, new_info):
    diff_info_list = []
    if old_tag is None:
        diff_info_list.append(wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_DEPRECATED_NA_TO_HAVE,
                                                                          'NA',
                                                                          f'{new_tag["name"]} '
                                                                          f'{new_tag["description"]}')))
        return diff_info_list
    if new_tag is None:
        diff_info_list.append(wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_DEPRECATED_HAVE_TO_NA,
                                                                          f'{old_tag["name"]} '
                                                                          f'{old_tag["description"]}',
                                                                          'NA')))
        return diff_info_list
    old_deprecated = f'{old_tag["name"]} {old_tag["description"]}'
    new_deprecated = f'{new_tag["name"]} {new_tag["description"]}'
    if old_deprecated != new_deprecated:
        diff_info_list.append(wrap_diff_info(old_info, new_info,
                                             DiffInfo(DiffType.DOC_TAG_DEPRECATED_A_TO_B, old_deprecated,
                                                      new_deprecated)))
    return diff_info_list


def process_tag_file(old_tag, new_tag, old_info, new_info):
    diff_info_list = []
    if old_tag is None:
        diff_info_list.append(
            wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_FILE_NA_TO_HAVE, 'NA', new_tag['name'])))
        return diff_info_list
    if new_tag is None:
        diff_info_list.append(
            wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_FILE_HAVE_TO_NA, old_tag['name'], 'NA')))
        return diff_info_list
    if old_tag['name'] != new_tag['name']:
        diff_info_list.append(wrap_diff_info(old_info, new_info,
                                             DiffInfo(DiffType.DOC_TAG_FILE_A_TO_B, old_tag['name'], new_tag['name'])))
    return diff_info_list


def process_tag_library(old_tag, new_tag, old_info, new_info):
    diff_info_list = []
    if old_tag is None:
        library_result_obj = DiffInfo(DiffType.DOC_TAG_LIBRARY_NA_TO_HAVE, 'NA', new_tag['name'])
        set_file_doc_content_snippet(old_tag, new_tag, library_result_obj)
        diff_info_list.append(wrap_diff_info(old_info, new_info, library_result_obj))
        return diff_info_list
    if new_tag is None:
        library_result_obj = DiffInfo(DiffType.DOC_TAG_LIBRARY_HAVE_TO_NA, old_tag['name'], "NA")
        set_file_doc_content_snippet(old_tag, new_tag, library_result_obj)
        diff_info_list.append(wrap_diff_info(old_info, new_info, library_result_obj))
        return diff_info_list
    if old_tag['name'] != new_tag['name']:
        library_result_obj = DiffInfo(DiffType.DOC_TAG_LIBRARY_A_TO_B, old_tag['name'], new_tag['name'])
        set_file_doc_content_snippet(old_tag, new_tag, library_result_obj)
        diff_info_list.append(wrap_diff_info(old_info, new_info, library_result_obj))
    return diff_info_list


def process_tag_param(old_tag, new_tag, old_info, new_info):
    diff_info_list = []
    if old_tag is None:
        diff_info_list.append(
            wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_PARAM_NA_TO_HAVE, 'NA', new_tag['name'])))
        return diff_info_list
    if new_tag is None:
        diff_info_list.append(
            wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_PARAM_HAVE_TO_NA, old_tag["name"], 'NA')))
        return diff_info_list
    if old_tag["name"] != new_tag['name']:
        diff_info_list.append(wrap_diff_info(old_info, new_info,
                                             DiffInfo(DiffType.DOC_TAG_PARAM_NAME_A_TO_B, old_tag["name"],
                                                      new_tag['name'])))
    if old_tag["description"] != new_tag['description']:
        diff_info_list.append(wrap_diff_info(old_info, new_info,
                                             DiffInfo(DiffType.DOC_TAG_PARAM_A_TO_B, old_tag["description"],
                                                      new_tag['description'])))
    return diff_info_list


def set_file_doc_content_snippet(old_tag, new_tag, diff_obj):
    if old_tag is not None:
        if old_tag.get('source'):
            diff_obj.set_file_doc_line(old_tag.get('source')[0].get('number'))
            diff_obj.set_old_api_declara(old_tag.get('source')[0].get('source'))
    if new_tag is not None:
        if new_tag.get('source'):
            diff_obj.set_file_doc_line(new_tag.get('source')[0].get('number'))
            diff_obj.set_new_api_declara(new_tag.get('source')[0].get('source'))


def process_tag_permission(old_tag, new_tag, old_info, new_info):
    diff_info_list = []
    if old_tag is None:
        permission_result_obj = DiffInfo(DiffType.DOC_TAG_PERMISSION_NA_TO_HAVE, 'NA', f'{new_tag["name"]} '
                                                                                       f'{new_tag["description"]}')
        set_file_doc_content_snippet(old_tag, new_tag, permission_result_obj)
        diff_info_list.append(wrap_diff_info(old_info, new_info, permission_result_obj))
        return diff_info_list
    if new_tag is None:
        permission_result_obj = DiffInfo(DiffType.DOC_TAG_PERMISSION_HAVE_TO_NA, f'{old_tag["name"]} '
                                                                                 f'{old_tag["description"]}', 'NA')
        set_file_doc_content_snippet(old_tag, new_tag, permission_result_obj)
        diff_info_list.append(wrap_diff_info(old_info, new_info, permission_result_obj))
        return diff_info_list
    old_permission = f'{old_tag["name"]} {old_tag["description"]}'
    new_permission = f'{new_tag["name"]} {new_tag["description"]}'
    if old_permission != new_permission:
        compare_value = compare_permission(old_permission, new_permission)
        if compare_value.state_range == RangeChange.DOWN.value:
            permission_result_obj = DiffInfo(DiffType.DOC_TAG_PERMISSION_RANGE_SMALLER, old_permission, new_permission)
            set_file_doc_content_snippet(old_tag, new_tag, permission_result_obj)
            diff_info_list.append(wrap_diff_info(old_info, new_info, permission_result_obj))
        elif compare_value.state_range == RangeChange.UP.value:
            permission_result_obj = DiffInfo(DiffType.DOC_TAG_PERMISSION_RANGE_BIGGER, old_permission, new_permission)
            set_file_doc_content_snippet(old_tag, new_tag, permission_result_obj)
            diff_info_list.append(wrap_diff_info(old_info, new_info, permission_result_obj))
        elif compare_value.state_range == RangeChange.CHANGE.value:
            permission_result_obj = DiffInfo(DiffType.DOC_TAG_PERMISSION_RANGE_CHANGE, old_permission, new_permission)
            set_file_doc_content_snippet(old_tag, new_tag, permission_result_obj)
            diff_info_list.append(wrap_diff_info(old_info, new_info, permission_result_obj))
    return diff_info_list


def process_tag_return(old_tag, new_tag, old_info, new_info):
    diff_info_list = []
    return diff_info_list


def process_tag_since(old_tag, new_tag, old_info, new_info):
    diff_info_list = []
    if old_tag is None:
        diff_info_list.append(wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_SINCE_NA_TO_HAVE,
                                                                          'NA',
                                                                          f'{new_tag["name"]} '
                                                                          f'{new_tag["description"]}')))
        return diff_info_list
    if new_tag is None:
        diff_info_list.append(wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_SINCE_HAVE_TO_NA,
                                                                          f'{old_tag["name"]} '
                                                                          f'{old_tag["description"]}',
                                                                          'NA')))
        return diff_info_list
    old_since = f'{old_tag["name"]} {old_tag["description"]}'
    new_since = f'{new_tag["name"]} {new_tag["description"]}'
    if old_since != new_since:
        diff_info_list.append(
            wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_SINCE_A_TO_B, old_since, new_since)))
    return diff_info_list


def process_tag_syscap(old_tag, new_tag, old_info, new_info):
    diff_info_list = []
    if old_tag is None:
        syscap_result_obj = DiffInfo(DiffType.DOC_TAG_SYSCAP_NA_TO_HAVE, 'NA', f'{new_tag["name"]} '
                                                                               f'{new_tag["description"]}')
        set_file_doc_content_snippet(old_tag, new_tag, syscap_result_obj)
        diff_info_list.append(wrap_diff_info(old_info, new_info, syscap_result_obj))
        return diff_info_list
    if new_tag is None:
        syscap_result_obj = DiffInfo(DiffType.DOC_TAG_SYSCAP_HAVE_TO_NA, f'{old_tag["name"]} '
                                                                         f'{old_tag["description"]}', 'NA')
        set_file_doc_content_snippet(old_tag, new_tag, syscap_result_obj)
        diff_info_list.append(wrap_diff_info(old_info, new_info, syscap_result_obj))
        return diff_info_list
    old_syscap = f'{old_tag["name"]} {old_tag["description"]}'
    new_syscap = f'{new_tag["name"]} {new_tag["description"]}'
    if old_syscap != new_syscap:
        syscap_result_obj = DiffInfo(DiffType.DOC_TAG_SYSCAP_A_TO_B, old_syscap, new_syscap)
        set_file_doc_content_snippet(old_tag, new_tag, syscap_result_obj)
        diff_info_list.append(wrap_diff_info(old_info, new_info, syscap_result_obj))
    return diff_info_list


def process_tag_left_brace(old_tag, new_tag, old_info, new_info):
    diff_info_list = []
    if old_tag is None:
        diff_info_list.append(
            wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_LEFT_BRACE_NA_TO_HAVE, 'NA', new_tag["name"])))
        return diff_info_list
    if new_tag is None:
        diff_info_list.append(
            wrap_diff_info(old_info, new_info, DiffInfo(DiffType.DOC_TAG_LEFT_BRACE_HAVE_TO_NA, old_tag['name'], 'NA')))
        return diff_info_list
    return diff_info_list


def process_tag_right_brace(old_tag, new_tag, old_info, new_info):
    diff_info_list = []
    if old_tag is None:
        diff_info_list.append(wrap_diff_info(old_info, new_info,
                                             DiffInfo(DiffType.DOC_TAG_RIGHT_BRACE_NA_TO_HAVE, 'NA', new_tag["name"])))
        return diff_info_list
    if new_tag is None:
        diff_info_list.append(wrap_diff_info(old_info, new_info,
                                             DiffInfo(DiffType.DOC_TAG_RIGHT_BRACE_HAVE_TO_NA, old_tag['name'], 'NA')))
        return diff_info_list
    return diff_info_list


process_tag_function = {
    TAGS['ADD_TO_GROUP'].value: process_tag_addtogroup,
    TAGS['BRIEF'].value: process_tag_brief,
    TAGS['DEPRECATED'].value: process_tag_deprecated,
    TAGS['FILE'].value: process_tag_file,
    TAGS['LIBRARY'].value: process_tag_library,
    TAGS['PARAM'].value: process_tag_param,
    TAGS['PERMISSION'].value: process_tag_permission,
    TAGS['RETURN'].value: process_tag_return,
    TAGS['SINCE'].value: process_tag_since,
    TAGS['SYSCAP'].value: process_tag_syscap,
    TAGS['LEFT_BRACE'].value: process_tag_left_brace,
    TAGS['RIGHT_BRACE'].value: process_tag_right_brace,
}


def process_comment(comment: str):
    '''
    处理comment数据，通过node调用comment-parser解析doc注释
    '''
    result_json = []
    if comment == "none_comment":
        return result_json
    result = subprocess.check_output(
        ['node', os.path.abspath(os.path.join(current_file, "../comment_parser.js")), comment])  # 解析comment
    result_json: list = json.loads(result.decode('utf-8'))
    return result_json


def get_tag_dict_from_list(tag_list):
    tag_dict = dict()
    for tag in tag_list:
        if tag['tag'] in tag_dict.keys():
            tag_dict[tag['tag']].append(tag)
        else:
            tag_dict[tag['tag']] = [tag]
    return tag_dict


def process_doc(old_doc, new_doc, old_info, new_info):
    diff_info_list = []
    old_tag_list = old_doc['tags']
    new_tag_list = new_doc['tags']
    old_tag_dict = get_tag_dict_from_list(old_tag_list)
    new_tag_dict = get_tag_dict_from_list(new_tag_list)
    for item in old_tag_dict.keys() | new_tag_dict.keys():
        if item not in process_tag_function.keys():
            continue
        old_tag = []
        new_tag = []
        if item in old_tag_dict.keys():
            old_tag = old_tag_dict.get(item)
        if item in new_tag_dict.keys():
            new_tag = new_tag_dict.get(item)
        max_length = max(len(old_tag), len(new_tag))
        while len(old_tag) < max_length:
            old_tag += [None] * (max_length - len(old_tag))
        while len(new_tag) < max_length:
            new_tag += [None] * (max_length - len(new_tag))
        tag_process = process_tag_function[item]
        index = 0
        while index < max_length:
            diff_info_list.extend(tag_process(old_tag[index], new_tag[index], old_info, new_info))
            index += 1

    return diff_info_list


def process_doc_list(old_doc_list: list, new_doc_list: list, old_info, new_info):
    diff_info_list = []
    old_length = len(old_doc_list)
    new_length = len(new_doc_list)
    index = 0
    while index < max(old_length, new_length):
        if index >= old_length != new_length:
            diff_info_list.append(wrap_diff_info(old_info, new_info,
                                                 DiffInfo(DiffType.ADD_DOC, old_doc_list[index], new_doc_list[index])))
            break
        if index >= new_length != old_length:
            diff_info_list.append(wrap_diff_info(old_info, new_info, DiffInfo(DiffType.REDUCE_DOC, old_doc_list[index],
                                                                              new_doc_list[index])))
            break
        diff_info_list.extend(process_doc(old_doc_list[index], new_doc_list[index], old_info, new_info))
        index += 1

    return diff_info_list


def get_eligible_labels_doc(doc_element):
    addtogroup_doc_list_right = []
    file_doc_list_right = []
    if 'tags' in doc_element:
        for element in doc_element['tags']:
            if element.get('tag') and 'addtogroup' == element.get('tag'):
                addtogroup_doc_list_right.append(doc_element)
                break
            elif element.get('tag') and 'file' == element.get('tag'):
                file_doc_list_right.append(doc_element)
                break
    return addtogroup_doc_list_right, file_doc_list_right


def get_addtogroup_and_file_doc(doc_list: list):
    addtogroup_doc_list = []
    file_doc_list = []
    for doc_element in doc_list:
        result_of_addtogroup_list, result_of_file_list = get_eligible_labels_doc(doc_element)
        addtogroup_doc_list.extend(result_of_addtogroup_list)
        file_doc_list.extend(result_of_file_list)

    return addtogroup_doc_list, file_doc_list


def filtrate_comments(comment: str):  # 获取每个头文件的最开始注释
    file_comment = ''
    if comment:
        pattern = RegularExpressions.START_COMMENT.value
        matches = re.finditer(pattern, comment, re.DOTALL | re.MULTILINE)
        for mat in matches:
            file_comment = '{}{}\n'.format(file_comment, mat.group())
    return file_comment


def process_addtogroup_and_file_list(old_list, new_list, old_info, new_info, num_key):
    old_len = len(old_list)
    new_len = len(new_list)
    result_list = []
    # addtogroup tag
    if 1 == num_key:
        if old_len > new_len:
            old_file_comment = filtrate_comments(old_info['comment'])
            new_file_comment = 'NA'
            result_list.append(wrap_diff_info(old_info, new_info,
                                              DiffInfo(DiffType.DOC_TAG_ADDTOGROUP_DECREASE, old_file_comment,
                                                       new_file_comment)))
        elif old_len < new_len:
            old_file_comment = 'NA'
            new_file_comment = filtrate_comments(new_info['comment'])
            result_list.append(wrap_diff_info(old_info, new_info,
                                              DiffInfo(DiffType.DOC_TAG_ADDTOGROUP_INCREASE, old_file_comment,
                                                       new_file_comment)))
        else:
            result_list.extend(process_doc_list(old_list, new_list, old_info, new_info))
    # file tag
    elif 0 == num_key:
        if old_len > new_len:
            old_file_comment = filtrate_comments(old_info['comment'])
            new_file_comment = 'NA'
            result_list.append(wrap_diff_info(old_info, new_info,
                                              DiffInfo(DiffType.DOC_TAG_FILE_DECREASE, old_file_comment,
                                                       new_file_comment)))
        elif old_len < new_len:
            old_file_comment = 'NA'
            new_file_comment = filtrate_comments(new_info['comment'])
            result_list.append(wrap_diff_info(old_info, new_info,
                                              DiffInfo(DiffType.DOC_TAG_FILE_INCREASE, old_file_comment,
                                                       new_file_comment)))
        else:
            result_list.extend(process_doc_list(old_list, new_list, old_info, new_info))
    return result_list


def process_comment_str(old_info, new_info):
    diff_info_list = []
    if old_info['comment'] == new_info['comment']:
        return diff_info_list
    if old_info['comment'] == 'none_comment':
        diff_info_list.append(wrap_diff_info(old_info, new_info, DiffInfo(DiffType.ADD_DOC, "NA", new_info['comment'])))
        return diff_info_list
    if new_info['comment'] == 'none_comment':
        diff_info_list.append(
            wrap_diff_info(old_info, new_info, DiffInfo(DiffType.REDUCE_DOC, old_info['comment'], "NA")))
        return diff_info_list
    old_doc_list = process_comment(old_info['comment'])
    new_doc_list = process_comment(new_info['comment'])
    if new_info['kind'] == CursorKind.TRANSLATION_UNIT.name:
        old_addtogroup_doc_list, old_file_doc_list = get_addtogroup_and_file_doc(old_doc_list)
        new_addtogroup_doc_list, new_file_doc_list = get_addtogroup_and_file_doc(new_doc_list)
        diff_info_list.extend(process_addtogroup_and_file_list(old_addtogroup_doc_list, new_addtogroup_doc_list,
                                                               old_info, new_info, 1))
        diff_info_list.extend(process_addtogroup_and_file_list(old_file_doc_list, new_file_doc_list,
                                                               old_info, new_info, 0))
    else:
        if len(old_doc_list) > len(new_doc_list):
            diff_info_list.append(wrap_diff_info(old_info, new_info, DiffInfo(DiffType.REDUCE_DOC, old_info['comment'],
                                                                              new_info['comment'])))
        elif len(old_doc_list) < len(new_doc_list):
            diff_info_list.append(wrap_diff_info(old_info, new_info,
                                                 DiffInfo(DiffType.ADD_DOC, old_info['comment'], new_info['comment'])))
        else:
            diff_info_list.extend(process_doc_list(
                [old_doc_list[len(old_doc_list) - 1]], [new_doc_list[len(new_doc_list) - 1]],
                old_info, new_info))
    return diff_info_list
