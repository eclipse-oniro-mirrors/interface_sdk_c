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

import os
import stat


def sort_by_kit(result_info_list: list, output_path):
    """
    Description:列表按kit排序
    """
    sort_by_kit_list = []
    if 1 == len(result_info_list):
        sort_by_kit_list.extend(result_info_list)
        write_data_in_md(result_info_list[0].kit_name, result_info_list, output_path)
        return sort_by_kit_list
    if result_info_list:
        kit_list = sorted(result_info_list, key=lambda obj: obj.kit_name)
        first_kit_name = kit_list[0].kit_name
        same_element = []
        for obj_element in kit_list:
            if obj_element.kit_name == first_kit_name:
                same_element.append(obj_element)
            else:
                sorted_data = sort_by_file_path(same_element)
                write_data_in_md(first_kit_name, sorted_data, output_path)
                sort_by_kit_list.extend(sorted_data)
                first_kit_name = obj_element.kit_name
                same_element = [obj_element]
        if same_element:
            sorted_data = sort_by_file_path(same_element)
            write_data_in_md(first_kit_name, sorted_data, output_path)
            sort_by_kit_list.extend(sorted_data)

    return sort_by_kit_list


def sort_by_file_path(result_info_list_kit: list):
    """
    Description:列表按文件路径排序
    """
    sorted_by_file_list = []
    if 1 == len(result_info_list_kit):
        sorted_by_file_list.extend(result_info_list_kit)
        return sorted_by_file_list
    if result_info_list_kit:
        file_list = sorted(result_info_list_kit, key=lambda obj: obj.api_file_path)
        first_file_name = file_list[0].api_file_path
        same_element = []
        for obj_element in file_list:
            if obj_element.api_file_path == first_file_name:
                same_element.append(obj_element)
            else:
                sorted_data = sort_by_type(same_element)
                sorted_by_file_list.extend(sorted_data)
                first_file_name = obj_element.api_file_path
                same_element = [obj_element]
        if same_element:
            sorted_data = sort_by_type(same_element)
            sorted_by_file_list.extend(sorted_data)

    return sorted_by_file_list


def sort_by_type(result_info_list_file: list):
    """
    Description:列表按操作类型排序
    """
    sorted_by_type_list = []
    if result_info_list_file:
        sorted_by_type_list = sorted(result_info_list_file, key=lambda obj: obj.diff_type.name)

    return sorted_by_type_list


def change_to_md_data(data):
    """
    Description:将列表中字典元素数据转为str的数据
    """
    headers = list(data[0].keys())
    markdown_table = '{}{}{}'.format("|", "|".join(headers), "|\n")
    markdown_table += '{}{}{}'.format("|", "|".join(["---"] * len(headers)), "|\n")
    for element in data:
        markdown_table += '{}{}{}'.format("|", "|".join(str(element[header]) for header in headers), "|\n")
    return markdown_table


def change_list_obj_to_dict(list_of_obj: list):
    """
    Description:将列表中对象元素数据转为字典元素数据
    """
    data_list = []
    if list_of_obj:
        for obj_element in list_of_obj:
            obj_dict = {
                '操作': obj_element.diff_type.name,
                '旧版本': obj_element.old_api_full_text.replace('\n', '<br />'),
                '新版本': obj_element.new_api_full_text.replace('\n', '<br />'),
                '.h文件': obj_element.api_file_path
            }
            data_list.append(obj_dict)

    return data_list


def write_data_in_md(kit_name: str, write_data: list, output_path):
    """
    Description:生成.md表格
    """
    if not kit_name:
        kit_name = r'nullOfKit'
    file_name = '{}{}'.format(kit_name, '.md')
    list_element_dict = change_list_obj_to_dict(write_data)
    md_data = change_to_md_data(list_element_dict)
    if md_data:
        diff_str = r'diff合集'
        path_str = os.path.abspath(os.path.join(output_path, diff_str))
        if not os.path.exists(path_str):
            os.mkdir(path_str)
        md_name = os.path.abspath(os.path.join(path_str, file_name))
        modes = stat.S_IRWXO | stat.S_IRWXG | stat.S_IRWXU
        fd = os.open(md_name, os.O_WRONLY | os.O_CREAT | os.O_TRUNC, mode=modes)
        os.write(fd, md_data.encode())
        os.close(fd)


def write_md_entrance(result_info_list, output_path):
    """
    Description:将数据生成.md表格入口
    """
    sorted_data = sort_by_kit(result_info_list, output_path)
    return sorted_data
