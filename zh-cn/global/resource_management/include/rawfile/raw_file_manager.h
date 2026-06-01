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
 * @brief 提供资源管理rawfile相关功能，可以使用ResourceManager打开rawfile进行后续相关操作，像搜索和读取等。
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
 * @brief 代表native侧的ResourceManager。此类封装了JavaScript resource manager的native实现，<b>ResourceManager</b>指针可以通过调用
 * {@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 *
 * @since 8
 * @version 1.0
 */
typedef struct NativeResourceManager NativeResourceManager;

/**
 * @brief 基于JavaScript侧的ResourceManager获取native侧的ResourceManager，用来完成rawfile相关功能。
 *
 * @param env 表示JavaScript Native Interface（napi）环境指针。
 * @param jsResMgr 表示JavaScript resource manager。
 * @return 返回{@link NativeResourceManager}指针，如果失败返回空指针。
 * @since 8
 * @version 1.0
 */
NativeResourceManager *OH_ResourceManager_InitNativeResourceManager(napi_env env, napi_value jsResMgr);

/**
 * @brief 释放native侧ResourceManager。
 *
 * @param resMgr 表示{@link NativeResourceManager}指针。
 * @since 8
 * @version 1.0
 */
void OH_ResourceManager_ReleaseNativeResourceManager(NativeResourceManager *resMgr);

/**
 * @brief 打开rawfile目录，打开后可以遍历对应目录下的rawfile文件。
 *
 * @param mgr 表示指向{@link NativeResourceManager}的指针，此指针是通过调用{@link OH_ResourceManager_InitNativeResourceManager}方法获取的。
 * @param dirName 表示要打开的rawfile目录名称，当传递一个空字符串时表示打开rawfile根目录。
 * @return 返回{@link RawDir}指针。使用完此指针后，调用{@link OH_ResourceManager_CloseRawDir}释放。如果失败或者mgr为空时返回空指针。
 * @see OH_ResourceManager_InitNativeResourceManager
 * @see OH_ResourceManager_CloseRawDir
 * @since 8
 * @version 1.0
 */
RawDir *OH_ResourceManager_OpenRawDir(const NativeResourceManager *mgr, const char *dirName);

/**
 * @brief 打开rawfile文件，打开后可以读取它的数据。
 *
 * @param mgr 表示指向{@link NativeResourceManager}的指针，此指针通过调用{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param fileName 表示基于rawfile根目录的相对路径下的文件名称。
 * @return 返回{@link RawFile}指针。当使用完此指针，调用{@link OH_ResourceManager_CloseRawFile}释放。如果失败或者mgr和fileName为空时返回空指针。
 * @see OH_ResourceManager_InitNativeResourceManager
 * @see OH_ResourceManager_CloseRawFile
 * @since 8
 * @version 1.0
 */
RawFile *OH_ResourceManager_OpenRawFile(const NativeResourceManager *mgr, const char *fileName);

/**
 * @brief 打开较大的rawfile文件，打开后可以读取它的数据。
 *
 * @param mgr 表示指向{@link NativeResourceManager}的指针，此指针通过调用{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param fileName 表示基于rawfile根目录的相对路径下的文件名称。
 * @return 返回{@link RawFile64}指针。当使用完此指针，调用{@link OH_ResourceManager_CloseRawFile64}释放。如果失败或者mgr和fileName为空时返回空指针。
 * @see OH_ResourceManager_InitNativeResourceManager
 * @see OH_ResourceManager_CloseRawFile64
 * @since 11
 * @version 1.0
 */
RawFile64 *OH_ResourceManager_OpenRawFile64(const NativeResourceManager *mgr, const char *fileName);

/**
 * @brief 判断路径是否是rawfile下的目录。
 *
 * @param mgr 表示指向{@link NativeResourceManager}的指针，此指针通过调用{@link OH_ResourceManager_InitNativeResourceManager}方法获取。
 * @param path rawfile路径。
 * @return 返回true表示是rawfile下的目录，返回false表示不是rawfile下的目录。
 * @since 12
 * @version 1.0
 */
bool OH_ResourceManager_IsRawDir(const NativeResourceManager *mgr, const char *path);

#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_NATIVE_RESOURCE_MANAGER_H
