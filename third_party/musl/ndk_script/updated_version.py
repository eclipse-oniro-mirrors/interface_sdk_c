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

import argparse


# 插入新版宏内容
def updated_version(file_path: str, new_version: int):
    version_define = '#define OH_API_VERSION_'
    version_current_define = '#define OH_CURRENT_API_VERSION OH_API_VERSION_'
    # 需要插入的内容
    new_content = ''
    # 插入的标志位置
    insert_after_line = '#define SDK_VERSION_9 9'
    # 旧版本
    old_version = 9
    # 更新需插入的内容
    for i in range(new_version - old_version):
        new_content += '{}{} {}\n'.format(version_define, old_version + i + 1, old_version + i + 1)
    new_content_tag = '{}{}\n'.format(version_current_define, new_version)
    new_content += new_content_tag

    with open(file_path, 'r') as fp:
        lines = fp.readlines()

    # 查找插入位置的索引
    insert_position = None
    for i, line in enumerate(lines):
        if insert_after_line in line:
            insert_position = i + 1  # 插入在该行之后
            break

    # 如果找到插入位置
    if (insert_position is not None) and (new_content_tag not in lines):
        # 插入新内容
        lines.insert(insert_position, new_content)
        # 更新修改后的内容
        with open(file_path, 'w') as fp:
            fp.writelines(lines)
    elif insert_position is None:
        raise Exception('未找到插入位置: {}，写入失败'.format(insert_after_line))


# 入口
def process_target_version():
    try:
        parser = argparse.ArgumentParser(description='Updated version')
        # 定义命令行参数
        parser.add_argument('-p', '--path', type=str, required=True, help='Path to the input file')
        parser.add_argument('-v', '--version', type=str, required=True, help='Version of the api')
        args = parser.parse_args()
        # 获取文件路径和版本
        input_file = args.path
        api_version = int(args.version)
        # 写入新版宏内容
        updated_version(input_file, api_version)
    except Exception as e:
        raise e


if __name__ == '__main__':
    process_target_version()
