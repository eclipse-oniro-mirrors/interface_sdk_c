/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @addtogroup rawfile
 * @{
 *
 * @brief Provides native functions for the resource manager to operate raw file directories and their raw files.
 *
 * You can use the resource manager to traverse, open, seek, read, and close raw files.
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file raw_dir.h
 *
 * @brief 提供rawfile目录相关功能，包括遍历和关闭rawfile目录。
 *
 * @syscap SystemCapability.Global.ResourceManager
 * @library librawfile.z.so
 * @kit LocalizationKit
 * @since 8
 * @version 1.0
 */
#ifndef GLOBAL_RAW_DIR_H
#define GLOBAL_RAW_DIR_H

#ifdef __cplusplus
extern "C" {
#endif

struct RawDir;

/**
 * @brief 提供对rawfile目录的访问。
 *
 * @since 8
 * @version 1.0
 */
typedef struct RawDir RawDir;

/**
 * @brief 通过索引获取rawfile文件名称。可以使用此方法遍历rawfile目录。
 *
 * @param rawDir 表示指向{@link RawDir}的指针。
 * @param index 表示文件在{@link RawDir}中的索引位置。
 * @return 通过索引返回文件名称，此返回值可以作为{@link OH_ResourceManager_OpenRawFile}的输入参数。
 *     <br>如果遍历完所有文件仍未找到，则返回NULL。
 * @see OH_ResourceManager_OpenRawFile
 * @since 8
 * @version 1.0
 */
const char *OH_ResourceManager_GetRawFileName(RawDir *rawDir, int index);

/**
 * @brief 获取{@link RawDir}中的rawfile数量。通过此方法可以获取{@link OH_ResourceManager_GetRawFileName}中可用的索引。
 *
 * @param rawDir 表示指向{@link RawDir}的指针。
 * @return 返回rawDir下的文件个数。如果rawDir为空时返回0。
 * @see OH_ResourceManager_GetRawFileName
 * @since 8
 * @version 1.0
 */
int OH_ResourceManager_GetRawFileCount(RawDir *rawDir);

/**
 * @brief 关闭已打开的{@link RawDir}并释放所有相关联资源。
 *
 * @param rawDir 表示指向{@link RawDir}的指针。
 * @see OH_ResourceManager_OpenRawDir
 * @since 8
 * @version 1.0
 */
void OH_ResourceManager_CloseRawDir(RawDir *rawDir);

#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_RAW_DIR_H
