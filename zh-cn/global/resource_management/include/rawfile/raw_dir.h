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
 * @brief 通过rawfile模块，开发者可以在Native层访问rawfile目录或目录下的资源文件，包括遍历、打开、读取、定位和关闭等。
 * <br> 遍历目录：打开rawfile目录，获取目录下的文件列表，遍历文件名称，支持多级目录遍历。
 * <br> 读取文件：打开rawfile文件，读取文件内容，调整文件偏移位置，获取文件大小和当前偏移量，获取文件描述符，支持2GB以上的大文件。
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file raw_dir.h
 *
 * @brief 提供rawfile目录操作相关的函数，包括遍历目录、获取文件数量、获取文件名称、关闭目录等功能。
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
 * @brief RawDir表示一个已打开的rawfile目录对象，可用于遍历目录和目录下文件。通过{@link OH_ResourceManager_OpenRawDir}函数获取，使用完后须调用
 * {@link OH_ResourceManager_CloseRawDir}关闭并释放。
 *
 * @since 8
 * @version 1.0
 */
typedef struct RawDir RawDir;

/**
 * @brief 通过索引获取rawfile目录中的文件名称。当需要遍历rawfile目录时，可以与{@link OH_ResourceManager_GetRawFileCount}搭配使用，通过循环遍历目录。
 *
 * @param rawDir 输入参数。指向RawDir对象的指针，通过{@link OH_ResourceManager_OpenRawDir}获取。
 * @param index 输入参数。文件在rawfile目录中的索引，取值范围为[0, 文件总数量-1]。
 * @return 返回文件名称字符串指针，可作为{@link OH_ResourceManager_OpenRawFile}的输入参数。
 *     <br>失败时返回NULL，可能原因是rawDir为NULL、index超出有效范围或目录为空。
 *     <br>调用{@link OH_ResourceManager_CloseRawDir}后，该指针同时会被释放，若需保存文件名，开发者需及时复制字符串内容。
 * @see {@link OH_ResourceManager_OpenRawFile}
 * @since 8
 * @version 1.0
 */
const char *OH_ResourceManager_GetRawFileName(RawDir *rawDir, int index);

/**
 * @brief 获取rawfile下子目录和文件数量。当需要遍历rawfile目录时，可以与{@link OH_ResourceManager_GetRawFileName}搭配使用，通过循环遍历目录。
 *
 * @param rawDir 输入参数。指向RawDir对象的指针，通过{@link OH_ResourceManager_OpenRawDir}获取。
 * @return 返回rawfile子目录和文件数量，不递归统计rawfile子目录下的文件和目录数量。若rawDir为NULL或目录为空，则返回0。
 * @see {@link OH_ResourceManager_GetRawFileName}
 * @since 8
 * @version 1.0
 */
int OH_ResourceManager_GetRawFileCount(RawDir *rawDir);

/**
 * @brief 关闭已打开的RawDir对象并释放所有相关资源。遍历rawfile目录后，须调用此函数关闭目录和释放资源。
 *
 * @param rawDir 输入参数。指向RawDir对象的指针，通过{@link OH_ResourceManager_OpenRawDir}获取。关闭后，该指针失效，不可再用于其他操作。
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