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
 * @brief Provides functions related to rawfile directories, including traversing and closing rawfile directories.
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
 * @brief Provides access to the **rawfile** directory.
 *
 * @since 8
 * @version 1.0
 */
typedef struct RawDir RawDir;

/**
 * @brief Obtains the name of a file in **rawfile** based on the index. You can use this function to traverse the **
 * rawfile** directory.
 *
 * @param rawDir Pointer to {@link RawDir}.
 * @param index Index of the rawfile in {@link RawDir}.
 * @return File name obtained if the rawfile exists in the directory. The file name returned can be used as the input
 * parameter of {@link OH_ResourceManager_OpenRawFile}.
 * If no file is found after all files in the directory are traversed, **NULL** is returned.
 * @see OH_ResourceManager_OpenRawFile
 * @since 8
 * @version 1.0
 */
const char *OH_ResourceManager_GetRawFileName(RawDir *rawDir, int index);

/**
 * @brief Obtains the number of rawfiles in {@link RawDir}. You can use this function to obtain available indexes in
 * {@link OH_ResourceManager_GetRawFileName}.
 *
 * @param rawDir Pointer to {@link RawDir}.
 * @return Number of files in rawDir. If rawDir is empty, 0 is returned.
 * @see OH_ResourceManager_GetRawFileName
 * @since 8
 * @version 1.0
 */
int OH_ResourceManager_GetRawFileCount(RawDir *rawDir);

/**
 * @brief Closes an opened {@link RawDir} and releases all associated resources.
 *
 * @param rawDir Pointer to {@link RawDir}.
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
