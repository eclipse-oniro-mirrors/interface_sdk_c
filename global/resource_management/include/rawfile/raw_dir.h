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
 * @brief Through the `rawfile` module, you can access the `rawfile` directory or resource files in the directory at
 * the native layer, including traversing, opening, reading, seeking, and closing.
 * <br>Traversing the directory: Open the `rawfile` directory, obtain the list of files under it, and iterate through
 * the file names. Multi‑level directory traversal is supported.
 * <br> Reading a file: Open a file, read file content, adjust the offset position of the file, obtain the file size
 * and current offset, and obtain the file descriptor. Files larger than 2 GB are supported.
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file raw_dir.h
 *
 * @brief Provides functions related to `rawfile` directory operations, including directory traversal, file count
 * retrieval, file name retrieval, and directory closing.
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
 * @brief `RawDir` represents an opened rawfile directory object, which can be used to traverse the directory and files
 * within it. It is obtained through {@link OH_ResourceManager_OpenRawDir}, and must be closed and released through
 * {@link OH_ResourceManager_CloseRawDir} after use.
 *
 * @since 8
 * @version 1.0
 */
typedef struct RawDir RawDir;

/**
 * @brief Obtains the file name in the `rawfile` directory by index. When you need to traverse the `rawfile` directory,
 * you can use this function together with {@link OH_ResourceManager_GetRawFileCount} to iterate through the directory
 * in a loop.
 *
 * @param rawDir Input parameter. Pointer to a `RawDir` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawDir}.
 * @param index Input parameter. Index of the file in the `rawfile` directory, ranging from [0, total file count - 1].
 * @return Pointer to the file name string, which can be used as an input parameter of
 *     {@link OH_ResourceManager_OpenRawFile}.
 *     <br>`NULL` is returned upon failure. Possible causes include `rawDir` being `NULL`, `index` being out of the
 *     valid range, or the directory being empty.
 *     <br>After {@link OH_ResourceManager_CloseRawDir} is called, this pointer is also released. If the file name
 *     needs to be preserved, you must copy the string content in a timely manner.
 * @see {@link OH_ResourceManager_OpenRawFile}
 * @since 8
 * @version 1.0
 */
const char *OH_ResourceManager_GetRawFileName(RawDir *rawDir, int index);

/**
 * @brief Obtains the number of subdirectories and files under `rawfile`. When traversal of the `rawfile` directory is
 * needed, this function can be used with {@link OH_ResourceManager_GetRawFileName} to iterate through the directory in
 * a loop.
 *
 * @param rawDir Input parameter. Pointer to a `RawDir` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawDir}.
 * @return Number of rawfile subdirectories and files, without recursively counting files and directories within
 *     `rawfile` subdirectories. `0` is returned if `rawDir` is `NULL` or the directory is empty.
 * @see {@link OH_ResourceManager_GetRawFileName}
 * @since 8
 * @version 1.0
 */
int OH_ResourceManager_GetRawFileCount(RawDir *rawDir);

/**
 * @brief Closes an opened `RawDir` object and releases all associated resources. After traversing the `rawfile`
 * directory, this function must be called to close the directory and release resources.
 *
 * @param rawDir Input parameter. Pointer to a `RawDir` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawDir}. After the release, the pointer becomes invalid and cannot be used for
 *     other operations.
 * @see {@link OH_ResourceManager_OpenRawDir}
 * @since 8
 * @version 1.0
 */
void OH_ResourceManager_CloseRawDir(RawDir *rawDir);

#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_RAW_DIR_H