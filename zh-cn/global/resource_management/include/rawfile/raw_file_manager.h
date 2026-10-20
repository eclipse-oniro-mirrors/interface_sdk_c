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
 * @brief 通过rawfile模块，开发者可以在Native层访问rawfile目录或目录下的资源文件，包括遍历、打开、读取、定位和关闭等。
 * <br> 遍历目录：打开rawfile目录，获取目录下的文件列表，遍历文件名称，支持多级目录遍历。
 * <br> 读取文件：打开rawfile文件，读取文件内容，调整文件偏移位置，获取文件大小和当前偏移量，获取文件描述符，支持2GB以上的大文件。
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file raw_file_manager.h
 *
 * @brief 通过本模块可以创建、释放NativeResourceManager对象，以及打开rawfile文件和目录。
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
 * @brief 表示Native层的ResourceManager对象。NativeResourceManager对JavaScript ResourceManager的Native实现进行封装，可以通过
 * {@link OH_ResourceManager_InitNativeResourceManager}函数获取。
 *
 * @since 8
 * @version 1.0
 */
typedef struct NativeResourceManager NativeResourceManager;

/**
 * @brief 初始化NativeResourceManager对象。
 *
 * @param env 输入参数。指向JavaScript Native Interface（napi）环境的指针。
 * @param jsResMgr 输入参数。表示JavaScript ResourceManager对象的引用。
 * @return 返回NativeResourceManager对象的指针。若初始化失败，返回NULL，可能原因为参数env或jsResMgr无效。
 *     <br>该指针由此函数分配内存，使用完后须调用{@link OH_ResourceManager_ReleaseNativeResourceManager}释放。
 * @since 8
 * @version 1.0
 */
NativeResourceManager *OH_ResourceManager_InitNativeResourceManager(napi_env env, napi_value jsResMgr);

/**
 * @brief 释放NativeResourceManager对象及其关联资源。
 *
 * @param resMgr 输入参数。指向要释放的NativeResourceManager对象的指针。释放后resMgr指针失效，不可用于其他操作。
 * @since 8
 * @version 1.0
 */
void OH_ResourceManager_ReleaseNativeResourceManager(NativeResourceManager *resMgr);

/**
 * @brief 打开rawfile目录。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针。
 * @param dirName 输入参数。待打开的目录路径。相对于rawfile根目录的路径，例如"images/icons"。当为空字符串时表示打开rawfile根目录。
 * @return 返回指向RawDir对象的指针。若调用失败或mgr为空，则返回NULL。使用完后须调用{@link OH_ResourceManager_CloseRawDir}释放。
 * @see {@link OH_ResourceManager_InitNativeResourceManager}
 * @see {@link OH_ResourceManager_CloseRawDir}
 * @since 8
 * @version 1.0
 */
RawDir *OH_ResourceManager_OpenRawDir(const NativeResourceManager *mgr, const char *dirName);

/**
 * @brief 打开rawfile文件并返回RawFile对象，用于读取rawfile文件内容。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针。
 * @param fileName 输入参数。待打开的文件路径。相对于rawfile根目录的路径，例如"images/icons/1.png"。
 * @return 返回指向RawFile对象的指针。若调用失败或输入参数为空，则返回NULL。使用完后须调用{@link OH_ResourceManager_CloseRawFile}释放。
 * @see {@link OH_ResourceManager_InitNativeResourceManager}
 * @see {@link OH_ResourceManager_CloseRawFile}
 * @since 8
 * @version 1.0
 */
RawFile *OH_ResourceManager_OpenRawFile(const NativeResourceManager *mgr, const char *fileName);

/**
 * @brief 打开rawfile文件并返回RawFile对象，用于读取rawfile文件内容。支持2GB以上的大文件。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针。
 * @param fileName 输入参数。待打开的文件路径。相对于rawfile根目录的路径，例如"images/icons/1.png"。
 * @return 返回指向RawFile对象的指针。若调用失败或输入参数为空，则返回NULL。使用完后须调用{@link OH_ResourceManager_CloseRawFile64}释放。
 * @see {@link OH_ResourceManager_InitNativeResourceManager}
 * @see {@link OH_ResourceManager_CloseRawFile64}
 * @since 11
 * @version 1.0
 */
RawFile64 *OH_ResourceManager_OpenRawFile64(const NativeResourceManager *mgr, const char *fileName);

/**
 * @brief 判断指定路径是否为rawfile的子目录。用于在遍历目录前，判断对应路径是否为目录，或在打开文件前，判断对应路径是否为文件。
 *
 * @param mgr 输入参数。指向NativeResourceManager对象的指针。
 * @param path 待判断的路径。相对于rawfile根目录的路径，如"images/icons"。
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