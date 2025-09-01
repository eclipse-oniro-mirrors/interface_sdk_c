#!/usr/bin/env python
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

import os
import re
import argparse
import shutil
import json
import stat
from typing import List

# ani header file list
_ANI_HEADER_LISTS = [
]

# Precompiled regular expression
_HEADER_PATTERN = re.compile(
    r'^\s*#\s*include\s+["<](.*/)?({})[">]'.format(
        '|'.join(map(re.escape, _ANI_HEADER_LISTS))
    )
)


def process_header_file(file_path):
    """processing single header file"""
    modified = False
    try:
        with open(file_path, 'r+', encoding='utf-8') as f:
            content = f.read()
            # Use a regular expression to process all rows at once
            new_content = []
            for line in content.splitlines():
                if not _HEADER_PATTERN.match(line):
                    new_content.append(line)
                else:
                    modified = True
            
            if modified:
                f.seek(0)
                f.write('\n'.join(new_content))
                f.truncate()
    except Exception as e:
        print(f"process file {file_path} failed: {str(e)}")
    return modified


def clean_ndk_ani_headers(ndk_header_path):
    if not _ANI_HEADER_LISTS:
        print("Warning: ani header file list")
        return

    # all files to be processed
    file_paths = []
    for root, _, files in os.walk(ndk_header_path):
        for file in files:
            if not file.endswith('.h'):
                continue
                
            file_path = os.path.join(root, file)
            if file in _ANI_HEADER_LISTS:
                try:
                    os.remove(file_path)
                    print(f"Deleted ani header file: {file_path}")
                except OSError as e:
                    print(f"Error deleting {file_path}: {str(e)}")
            else:
                file_paths.append(file_path)
    
    # Bulk processing file include
    for file_path in file_paths:
        process_header_file(file_path)


# Clear the ani header file in the systemCapability configuration json file
def clean_json_systemCapability_headers(capability_header_path):
    try:
        with open(capability_header_path, 'r') as f:
            systemCapabilitys = json.load(f)
    except Exception as e:
        print(f"Error reading JSON file: {str(e)}")
        return

    # Traverse all levels of items
    for _systemCapability in systemCapabilitys:
        # filtering ani header file
        systemCapabilitys[_systemCapability] = [item for item in systemCapabilitys[_systemCapability]
            if os.path.basename(item) not in _ANI_HEADER_LISTS]

    # Saving the modified JSON
    try:
        fd = os.open(capability_header_path, os.O_WRONLY | os.O_TRUNC | os.O_CREAT,
                     stat.S_IRUSR | stat.S_IWUSR)
        with os.fdopen(fd, 'w') as f:
            json.dump(systemCapabilitys, f, indent=2)
        print("JSON file updated successfully")
    except Exception as e:
        print(f"Error saving JSON file: {str(e)}")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--ndk-header-path', help='ndk header path', required=True)
    parser.add_argument('--system-capability-header-config', required=True)
    args = parser.parse_args()
    
    if not os.path.isdir(args.ndk_header_path):
        print(f"Error：path {args.ndk_header_path} is not exist!")
        return
    
    clean_ndk_ani_headers(args.ndk_header_path)
    clean_json_systemCapability_headers(args.system_capability_header_config)
    print("Ani Header file cleanup complete!")


if __name__ == '__main__':
    main()
