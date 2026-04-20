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
 * @brief Provides native functions for the resource manager to operate raw file directories and their raw files.
 *
 * You can use the resource manager to traverse, open, seek, read, and close raw files.
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file raw_file_manager.h
 *
 * @brief Provides file management functions for the **rawfile** directory. You can use the **ResourceManager** to open
 * a rawfile and perform operations such as data search and reading.
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
 * @brief Represents the native **ResourceManager**. This class encapsulates the native implementation of the
 * JavaScript **ResourceManager**. The pointer to **ResourceManager** can be obtained by using
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 *
 * @since 8
 * @version 1.0
 */
typedef struct NativeResourceManager NativeResourceManager;

/**
 * @brief Obtains the native **ResourceManager** based on the JavaScript **ResourceManager** to implement rawfile-
 * specific functions.
 *
 * @param env Pointer to the JavaScript Native API (napi) environment.
 * @param jsResMgr JavaScript **ResourceManager** object.
 * @return Pointer to {@link NativeResourceManager}. If the operation fails, a null pointer is returned.
 * @since 8
 * @version 1.0
 */
NativeResourceManager *OH_ResourceManager_InitNativeResourceManager(napi_env env, napi_value jsResMgr);

/**
 * @brief Releases the native **ResourceManager**.
 *
 * @param resMgr Pointer to {@link NativeResourceManager}.
 * @since 8
 * @version 1.0
 */
void OH_ResourceManager_ReleaseNativeResourceManager(NativeResourceManager *resMgr);

/**
 * @brief Traverses all files in the **rawfile** directory.
 *
 * @param mgr Pointer to {@link NativeResourceManager}, which is obtained by calling
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param dirName Pointer to the name of the directory to open. If this field is left empty, the root directory will be
 * opened.
 * @return Pointer to {@link RawDir}. After using the pointer, call {@link OH_ResourceManager_CloseRawDir} to release
 * it. If the operation fails or **mgr** is empty, a null pointer is returned.
 * @see OH_ResourceManager_InitNativeResourceManager
 * @see OH_ResourceManager_CloseRawDir
 * @since 8
 * @version 1.0
 */
RawDir *OH_ResourceManager_OpenRawDir(const NativeResourceManager *mgr, const char *dirName);

/**
 * @brief Opens a rawfile and reads the data in it.
 *
 * @param mgr Pointer to {@link NativeResourceManager}, which is obtained by calling
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param fileName Pointer to the name of the file in the relative path of the **rawfile** root directory.
 * @return Pointer to {@link RawDir}. After using the pointer, call {@link OH_ResourceManager_CloseRawFile} to release
 * it. If the operation fails or **mgr** or **fileName** is empty, a null pointer is returned.
 * @see OH_ResourceManager_InitNativeResourceManager
 * @see OH_ResourceManager_CloseRawFile
 * @since 8
 * @version 1.0
 */
RawFile *OH_ResourceManager_OpenRawFile(const NativeResourceManager *mgr, const char *fileName);

/**
 * @brief Opens a large rawfile and reads the data in it.
 *
 * @param mgr Pointer to {@link NativeResourceManager}, which is obtained by calling
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param fileName Pointer to the name of the file in the relative path of the **rawfile** root directory.
 * @return Pointer to {@link RawFile64}. After using this pointer, call {@link OH_ResourceManager_CloseRawFile64} to
 * release it. If the operation fails or **mgr** or **fileName** is empty, a null pointer is returned.
 * @see OH_ResourceManager_InitNativeResourceManager
 * @see OH_ResourceManager_CloseRawFile64
 * @since 11
 * @version 1.0
 */
RawFile64 *OH_ResourceManager_OpenRawFile64(const NativeResourceManager *mgr, const char *fileName);

/**
 * @brief Checks whether the path of a raw file is a subdirectory in the **rawfile** directory.
 *
 * @param mgr Pointer to {@link NativeResourceManager}, which is obtained by calling
 * {@link OH_ResourceManager_InitNativeResourceManager}.
 * @param path Path of a rawfile.
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
