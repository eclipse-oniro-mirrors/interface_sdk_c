/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
 * @file raw_file_manager.h
 *
 * @brief This module allows you to create and release `NativeResourceManager` objects, and open rawfiles and
 * directories.
 *
 * @syscap SystemCapability.Global.ResourceManager
 * @library librawfile.z.so
 * @kit LocalizationKit
 * @since 8
 * @version 1.0
 */
#ifndef GLOBAL_NATIVE_RESOURCE_MANAGER_H
#define GLOBAL_NATIVE_RESOURCE_MANAGER_H

#include "napi/native_api.h"
#include "raw_dir.h"
#include "raw_file.h"

#ifdef __cplusplus
extern "C" {
#endif

struct NativeResourceManager;

/**
 * @brief Represents a `ResourceManager` object at the Native layer. `NativeResourceManager` encapsulates the Native
 * implementation of JavaScript ResourceManager, and can be obtained through
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 *
 * @since 8
 * @version 1.0
 */
typedef struct NativeResourceManager NativeResourceManager;

/**
 * @brief Initializes a `NativeResourceManager` object.
 *
 * @param env Input parameter. Pointer to the JavaScript Native Interface (napi) environment.
 * @param jsResMgr Input parameter. Reference to the JavaScript `ResourceManager` object.
 * @return Pointer to the `NativeResourceManager` object. If the initialization fails, `NULL` is returned. The possible
 *     cause is that the `env` or `jsResMgr` parameter is invalid.
 *     <br>The memory is allocated by this function and must be released through
 *     {@link OH_ResourceManager_ReleaseNativeResourceManager} after use.
 * @since 8
 * @version 1.0
 */
NativeResourceManager *OH_ResourceManager_InitNativeResourceManager(napi_env env, napi_value jsResMgr);

/**
 * @brief Releases a `NativeResourceManager` object and its associated resources.
 *
 * @param resMgr Input parameter. Pointer to the `NativeResourceManager` object to be released. After the release, the
 *     `resMgr` pointer becomes invalid and cannot be used for other operations.
 * @since 8
 * @version 1.0
 */
void OH_ResourceManager_ReleaseNativeResourceManager(NativeResourceManager *resMgr);

/**
 * @brief Opens the `rawfile` directory.
 *
 * @param mgr Input parameter. Pointer to the `NativeResourceManager` object.
 * @param dirName Input parameter. Path of the directory to be opened. Path relative to the `rawfile` root directory,
 *     for example, `images/icons`. If the value is an empty string, the `rawfile` root directory is opened.
 * @return Pointer to the `RawDir` object. If the call fails or `mgr` is null, `NULL` is returned. After use, call
 *     {@link OH_ResourceManager_CloseRawDir} to release it.
 * @see {@link OH_ResourceManager_InitNativeResourceManager}
 * @see {@link OH_ResourceManager_CloseRawDir}
 * @since 8
 * @version 1.0
 */
RawDir *OH_ResourceManager_OpenRawDir(const NativeResourceManager *mgr, const char *dirName);

/**
 * @brief Opens a rawfile and returns a `RawFile` object for reading the rawfile content.
 *
 * @param mgr Input parameter. Pointer to the `NativeResourceManager` object.
 * @param fileName Input parameter. Path of the file to be opened. Path relative to the `rawfile` root directory, for
 *     example, `images/icons/1.png`.
 * @return Pointer to the `RawFile` object. If the call fails or the input parameter is null, `NULL` is returned. After
 *     use, call {@link OH_ResourceManager_CloseRawFile} to release it.
 * @see {@link OH_ResourceManager_InitNativeResourceManager}
 * @see {@link OH_ResourceManager_CloseRawFile}
 * @since 8
 * @version 1.0
 */
RawFile *OH_ResourceManager_OpenRawFile(const NativeResourceManager *mgr, const char *fileName);

/**
 * @brief Opens a rawfile and returns a `RawFile` object for reading the rawfile content. Files larger than 2 GB are
 * supported.
 *
 * @param mgr Input parameter. Pointer to the `NativeResourceManager` object.
 * @param fileName Input parameter. Path of the file to be opened. Path relative to the `rawfile` root directory, for
 *     example, `images/icons/1.png`.
 * @return Pointer to the `RawFile` object. If the call fails or the input parameter is null, `NULL` is returned. After
 *     use, call {@link OH_ResourceManager_CloseRawFile64} to release it.
 * @see {@link OH_ResourceManager_InitNativeResourceManager}
 * @see {@link OH_ResourceManager_CloseRawFile64}
 * @since 11
 * @version 1.0
 */
RawFile64 *OH_ResourceManager_OpenRawFile64(const NativeResourceManager *mgr, const char *fileName);

/**
 * @brief Checks whether the specified path is a subdirectory of `rawfile`. It is used to determine whether the
 * specified path is a directory before traversing it, or whether the specified path is a file before opening it.
 *
 * @param mgr Input parameter. Pointer to the `NativeResourceManager` object.
 * @param path Path to be checked. Path relative to the `rawfile` root directory, for example, `images/icons`.
 * @return **true** if the path is a subdirectory in the **rawfile** directory; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_ResourceManager_IsRawDir(const NativeResourceManager *mgr, const char *path);

#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_NATIVE_RESOURCE_MANAGER_H