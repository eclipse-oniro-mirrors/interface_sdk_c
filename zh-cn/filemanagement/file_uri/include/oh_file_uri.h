/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup fileUri
 * @{
 *
 * @brief 文件统一资源标识符（File Uniform Resource Identifier）。\n
 * 支持fileUri与路径之间的转换，以及fileUri的格式校验。\n
 * 该模块主要用于URI格式验证和URI转换处理，URI用于应用间文件分享场景，可将应用沙箱路径按系统规则转换为URI，避免直接传递沙箱路径。\n
 * 调用者需保证所有接口入参的有效性，接口按照固定规则转换输出结果，并不检查对应文件或目录是否存在。
 * @syscap SystemCapability.FileManagement.AppFileService
 * @since 12
 */

/**
 * @file oh_file_uri.h
 * @kit CoreFileKit
 *
 * @brief 提供URI和路径之间的相互转换、目录URI获取以及URI格式校验的方法，适用于文件分享场景中的URI转换和校验。
 * @library libohfileuri.so
 * @syscap SystemCapability.FileManagement.AppFileService
 * @since 12
 */

#ifndef FILE_MANAGEMENT_OH_FILE_URI_H
#define FILE_MANAGEMENT_OH_FILE_URI_H

#include "error_code.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 通过传入的路径生成应用自己的URI；\n
 * 将路径转URI时，路径中的中文及非数字字母的特殊字符将会被百分号编码，拼接在URI中。
 *
 * @param path 表示要转换的路径。
 * @param length 表示要转换路径字符串的字节长度，需与path实际长度一致。
 * @param result 输出参数，表示转换后的URI，需要使用standard library标准库的free()方法释放申请的资源。
 * @return 返回特定的错误码值，详细信息可以查看{@link FileManagement_ErrCode}。\n
 *         {@link ERR_INVALID_PARAMETER}  401 - 输入参数无效。可能的原因：\n
 *                  1. 参数path为空指针；\n
 *                  2. 参数result为空指针；\n
 *                  3. 输入的path长度与length不一致。\n
 *         {@link ERR_UNKNOWN} 13900042 - 未知错误。转换后的URI长度为0会返回此错误。\n
 *         {@link ERR_ENOMEM} 13900011 - 分配或者拷贝内存失败。\n
 *         {@link ERR_OK} 0 - 接口调用成功。
 * @syscap SystemCapability.FileManagement.AppFileService
 * @since 12
 */
FileManagement_ErrCode OH_FileUri_GetUriFromPath(const char *path, unsigned int length, char **result);

/**
 * @brief 将URI转换成对应的沙箱路径。\n
 * 1、URI转路径过程中会将URI中存在的百分号编码字符进行解码后拼接在原处，非系统接口生成的URI中可能存在不符合编码规范的字符，导致字符串无法正常拼接。\n
 * 2、转换处理为系统约定的字符串替换规则（规则随系统演进可能会发生变化），转换过程中不进行路径校验操作，无法保证转换结果一定可以访问。
 *
 * @param uri 表示要转换的URI，需符合系统URI格式规范。
 * @param length 表示要转换URI字符串的字节长度，需与uri实际长度一致。
 * @param result 输出参数，表示转换后的路径。\n
 * 需要使用standard library标准库的free()方法释放申请的资源。
 * @return 返回特定的错误码值，详细信息可以查看{@link FileManagement_ErrCode}。\n
 *         {@link ERR_INVALID_PARAMETER}  401 - 输入参数无效。可能的原因：\n
 *                  1. 参数uri为空指针；\n
 *                  2. 参数result为空指针；\n
 *                  3. 输入的uri长度与length不一致。\n
 *         {@link ERR_UNKNOWN} 13900042 - 未知错误。转换后的路径path长度为0会返回此错误。\n
 *         {@link ERR_ENOMEM}  13900011 - 分配或者拷贝内存失败。
 *         {@link ERR_OK} 0 - 接口调用成功。
 * @syscap SystemCapability.FileManagement.AppFileService
 * @since 12
 */
FileManagement_ErrCode OH_FileUri_GetPathFromUri(const char *uri, unsigned int length, char **result);

/**
 * @brief 获取所在路径URI。URI指向文件则返回所在路径的URI，URI指向目录则不处理直接返回原串；\n
 * 如果URI指向的文件不存在，或无法获取文件属性，则返回空串。
 *
 * @param uri 表示要获取目录的原始URI。
 * @param length 表示原始URI字符串的字节长度，需与uri实际长度一致。
 * @param result 输出参数，表示获取到的目录URI，需要使用standard library标准库的free()方法释放申请的资源。
 * @return 返回特定的错误码值，详细信息可以查看{@link FileManagement_ErrCode}。\n
 *         {@link ERR_INVALID_PARAMETER}  401 - 输入参数无效。可能的原因：\n
 *                  1. 参数uri为空指针；\n
 *                  2. 参数result为空指针；\n
 *                  3. 输入的uri长度与length不一致。\n
 *         {@link ERR_ENOMEM} 13900011 - 分配或者拷贝内存失败。\n
 *         {@link ERR_ENOENT} 13900002 - 没有该文件或目录。\n
 *         {@link ERR_UNKNOWN} 13900042 - 未知错误。获取到的目录URI长度为0会返回此错误。\n
 *         {@link ERR_OK} 0 - 接口调用成功。
 * @syscap SystemCapability.FileManagement.AppFileService
 * @since 12
 */
FileManagement_ErrCode OH_FileUri_GetFullDirectoryUri(const char *uri, unsigned int length, char **result);

/**
 * @brief 判断传入的URI格式是否正确。\n
 * 仅校验URI是否满足系统定义的格式规范，不校验URI的有效性。
 *
 * @param uri 表示需要校验的URI。
 * @param length 表示需要校验URI字符串的字节长度。
 * @return true表示传入URI是有效的URI；false表示传入的URI是无效的URI。
 * @syscap SystemCapability.FileManagement.AppFileService
 * @since 12
 */
bool OH_FileUri_IsValidUri(const char *uri, unsigned int length);

/**
 * @brief 通过传入的URI获取文件名称。\n
 * 如果文件名中存在百分号编码字符，将会被解码处理后拼接在原处。
 *
 * @param uri 传入的URI，需符合系统URI格式规范。
 * @param length 表示传入URI字符串的字节长度，需与uri实际长度一致。
 * @param result 输出参数，表示转换后的名称。\n
 * 需要使用standard library标准库的free()方法释放申请的资源。
 * @return 返回特定的错误码值，详细信息可以查看{@link FileManagement_ErrCode}。\n
 *         {@link ERR_INVALID_PARAMETER}  401 - 输入参数无效。可能的原因：\n
 *                  1. 参数uri为空指针；\n
 *                  2. 参数result为空指针；\n
 *                  3. 输入的uri长度与length不一致；\n
 *                  4. uri格式不正确。\n
 *         {@link ERR_ENOMEM} 13900011 - 分配或者拷贝内存失败。\n
 *         {@link ERR_OK} 0 - 接口调用成功。
 * @syscap SystemCapability.FileManagement.AppFileService
 * @since 13
 */
FileManagement_ErrCode OH_FileUri_GetFileName(const char *uri, unsigned int length, char **result);
#ifdef __cplusplus
};
#endif
/** @} */
#endif // FILE_MANAGEMENT_OH_FILE_URI_H
