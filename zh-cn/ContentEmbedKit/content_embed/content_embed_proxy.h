/*
 * Copyright (c) 2026-2026 Huawei Device Co., Ltd.
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
 * @addtogroup ContentEmbed
 * @{
 *
 * @brief 内容嵌入（ContentEmbed）模块提供对象编辑（Object Editor，简称OE）功能框架与技术，支持应用间文档的嵌入与协同编辑。
 * 通过OE技术实现的被嵌入文档（简称OE文档），在客户端界面中可能呈现为缩略图或者快照（Snapshot），
 * 也可能以标准格式序列化为一段二进制数据保存在内存或者某个文件（称为OE格式文件）中。
 *
 * @syscap SystemCapability.ContentEmbed.ObjectEditor
 * @since 24
 */

/**
 * @file content_embed_proxy.h
 *
 * @brief 为客户端应用提供服务端应用注册的OE Extension信息查询接口和与服务端OE Extension对象交互的数据结构及相关操作接口。
 *
 * @library libcontent_embed_ndk.so
 * @kit ContentEmbedKit
 * @syscap SystemCapability.ContentEmbed.ObjectEditor
 * @since 24
 */

#ifndef OHOS_CONTENT_EMBED_PROXY_H
#define OHOS_CONTENT_EMBED_PROXY_H

#include <stdint.h>
#include <stdlib.h>
#include <multimedia/image_framework/image/pixelmap_native.h>
#include "content_embed_common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief 定义{@link ContentEmbed_Format}中名称字段的最大字符数限制。
 *
 * @since 24
 */
#define MAX_NAME_LENGTH (1 * 1024)

/**
 * @brief 定义{@link ContentEmbed_Format}中描述字段的最大字符数限制。
 *
 * @since 24
 */
#define MAX_DESCRIPTION_LENGTH (1 * 1024)

/**
 * @brief 声明ContentEmbed_Info结构体类型。通过{@link OH_ContentEmbed_GetContentEmbedInfo}查询当前所有服务端应用注册的
 * OE文档信息，然后通过{@link OH_ContentEmbed_GetFormatCountFromInfo}获取当前查询{@link ContentEmbed_Format}实例的数量，
 * 并通过{@link OH_ContentEmbed_GetFormatFromInfo}获取指定索引位置的实例对象。
 *
 * @since 24
 */
typedef struct ContentEmbed_Info ContentEmbed_Info;

/**
 * @brief 声明ContentEmbed_Format结构体类型，包含服务端应用OE Extension注册的OE文档信息。具体可通过
 * {@link OH_ContentEmbed_GetOEidFromFormat}获取OEID、{@link OH_ContentEmbed_GetNameAndDescriptionFromFormat}获取名称和
 * 描述、{@link OH_ContentEmbed_GetIconFromFormat}获取图标和{@link OH_ContentEmbed_GetFileNameExtensionsFromFormat}获取
 * 文件扩展名列表。
 *
 * @since 24
 */
typedef struct ContentEmbed_Format ContentEmbed_Format;

/**
 * @brief 创建{@link ContentEmbed_Info}实例。
 * <br>开发者可通过{@link OH_ContentEmbed_DestroyContentEmbedInfo}销毁实例，以避免内存泄漏。
 *
 * @param info 输出参数。该指针指向新创建的{@link ContentEmbed_Info}对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyContentEmbedInfo {info}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_CreateContentEmbedInfo(ContentEmbed_Info **info);

/**
 * @brief 销毁{@link ContentEmbed_Info}实例。
 *
 * @param info 指向{@link ContentEmbed_Info}对象指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_DestroyContentEmbedInfo(ContentEmbed_Info *info);

/**
 * @brief 根据区域设置获取{@link ContentEmbed_Info}实例。
 *
 * @permission ohos.permission.CONNECT_OBJECTEDITOR_EXTENSION
 * @param locale 表示区域ID的字符串，由语言、脚本、国家地区组成，例如"zh-Hans-CN"。当locale为空时，默认使用系统区域设置。
 * @param info 输出参数。该指针指向ContentEmbed_Info对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_PERMISSION_DENIED}：表示权限校验失败。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL}：表示系统服务工作异常。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetContentEmbedInfo(const char *locale, ContentEmbed_Info *info);

/**
 * @brief 获取{@link ContentEmbed_Info}实例中的{@link ContentEmbed_Format}实例的数量。
 *
 * @param info 指向{@link ContentEmbed_Info}对象指针。
 * @param count 输出参数。存储{@link ContentEmbed_Format}实例的数量。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetFormatCountFromInfo(const ContentEmbed_Info *info, uint32_t *count);

/**
 * @brief 从{@link ContentEmbed_Info}实例中获取指定索引位置的{@link ContentEmbed_Format}实例。
 *
 * @param info 指向{@link ContentEmbed_Info}对象指针。
 * @param index 要获取的format的索引位置，从0开始。
 * @param format 输出参数。获取成功后，返回指向info索引为index的{@link ContentEmbed_Format}实例的指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetFormatFromInfo(const ContentEmbed_Info *info, uint32_t index,
                                                         ContentEmbed_Format **format);

/**
 * @brief 创建{@link ContentEmbed_Format}实例。
 * <br>开发者可通过{@link OH_ContentEmbed_DestroyContentEmbedFormat}销毁实例，以避免内存泄漏。
 *
 * @param format 输出参数。该指针指向新创建的{@link ContentEmbed_Format}对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyContentEmbedFormat {format}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_CreateContentEmbedFormat(ContentEmbed_Format **format);

/**
 * @brief 销毁{@link ContentEmbed_Format}实例。
 *
 * @param format 指向{@link ContentEmbed_Format}对象指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_DestroyContentEmbedFormat(ContentEmbed_Format *format);

/**
 * @brief 根据OEID和区域设置获取{@link ContentEmbed_Format}实例。
 *
 * @permission ohos.permission.CONNECT_OBJECTEDITOR_EXTENSION
 * @param oeid 文档格式的唯一标识符字符串。
 * @param locale 表示区域ID的字符串，由语言、脚本、国家地区组成，例如"zh-Hans-CN"。当locale为空时，默认使用系统区域设置。
 * @param format 输出参数。该指针指向{@link ContentEmbed_Format}对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_PERMISSION_DENIED}：表示权限校验失败。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL}：表示系统服务工作异常。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetContentEmbedFormatByOEidAndLocale(const char *oeid,
                                                                            const char *locale,
                                                                            ContentEmbed_Format *format);

/**
 * @brief 获取{@link ContentEmbed_Format}实例的OEID。
 *
 * @param format 指向{@link ContentEmbed_Format}对象指针。
 * @param oeid 输出参数。用于存储标识符OEID字符串的字符数组。建议数组长度为{@link MAX_OEID_LENGTH}。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetOEidFromFormat(const ContentEmbed_Format *format, char *oeid);

/**
 * @brief 从{@link ContentEmbed_Format}实例中获取其本地化的显示名称和描述信息。
 *
 * @param format 指向{@link ContentEmbed_Format}对象指针。
 * @param name 输出参数。用于存储名称的字符数组。建议数组长度为{@link MAX_NAME_LENGTH}。
 * @param description 输出参数。用于存储描述信息的字符数组。建议数组长度为{@link MAX_DESCRIPTION_LENGTH}。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetNameAndDescriptionFromFormat(const ContentEmbed_Format *format,
                                                                       char *name, char *description);

/**
 * @brief 获取{@link ContentEmbed_Format}实例的图标。
 *
 * @param format 指向{@link ContentEmbed_Format}对象指针。
 * @param icon 输出参数。用于存储图标的{@link OH_PixelmapNative}实例指针。
 *             <br>开发者需要调用{@link OH_PixelmapNative_Destroy}销毁，以避免内存泄漏。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetIconFromFormat(const ContentEmbed_Format *format, OH_PixelmapNative **icon);

/**
 * @brief 获取{@link ContentEmbed_Format}实例的文件扩展名列表。
 *
 * @param format 指向{@link ContentEmbed_Format}对象指针。
 * @param count 输出参数。存储返回的文件扩展名数量。
 * @return 返回文件扩展名字符串数组的指针。
 * @since 24
 */
char** OH_ContentEmbed_GetFileNameExtensionsFromFormat(const ContentEmbed_Format *format, unsigned int *count);

/**
 * @brief 声明ContentEmbed_ExtensionProxy结构体类型。用于指向OE文档在客户端封装的文档嵌入和编辑的程序对象（简称客户端OE对象）。
 *
 * @since 24
 */
typedef struct ContentEmbed_ExtensionProxy ContentEmbed_ExtensionProxy;

/**
 * @brief 声明OE文档结构体类型。封装了被嵌入的文档的元数据、内容和存储结构。
 *
 * @since 24
 */
typedef struct ContentEmbed_Document ContentEmbed_Document;

/**
 * @brief 声明ContentEmbed_Capability结构体类型。
 *
 * @since 24
 */
typedef struct ContentEmbed_Capability ContentEmbed_Capability;

/**
 * @brief 创建{@link ContentEmbed_ExtensionProxy}实例。
 * <br>开发者可通过{@link OH_ContentEmbed_DestroyExtensionProxy}销毁实例，以避免内存泄漏。
 *
 * @param document 指向OE文档实例的指针。
 * @param proxy 输出参数。该指针指向新创建的{@link ContentEmbed_ExtensionProxy}对象。
 * @param contextPtr 上下文实例的指针，用于传递应用上下文信息。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyExtensionProxy {proxy}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_CreateExtensionProxy(ContentEmbed_Document *document,
                                                            ContentEmbed_ExtensionProxy **proxy,
                                                            void *contextPtr);

/**
 * @brief 销毁{@link ContentEmbed_ExtensionProxy}实例。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_DestroyExtensionProxy(ContentEmbed_ExtensionProxy *proxy);

/**
 * @brief OE文档更新时通知客户端的回调函数类型。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Proxy_RegisterOnUpdateFunc}将此函数注册到客户端OE对象。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @since 24
 */
typedef void (*OH_ContentEmbed_ClientCallbackOnUpdateFunc)(
    ContentEmbed_ExtensionProxy *proxy);

/**
 * @brief OE文档错误时通知客户端的回调函数类型。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Proxy_RegisterOnErrorFunc}将此函数注册到客户端OE对象。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @param error 表示发生的错误码，详细定义参见{@link ContentEmbed_ErrorCode}。
 * @since 24
 */
typedef void (*OH_ContentEmbed_ClientCallbackOnErrorFunc)(
    ContentEmbed_ExtensionProxy *proxy, ContentEmbed_ErrorCode error);

/**
 * @brief OE文档编辑完成时通知客户端的回调函数类型。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Proxy_RegisterOnEditingFinishedFunc}将此函数注册到客户端OE对象。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @param dataModified 表示OE文档数据是否被修改。true表示OE文档已修改；false表示未修改。
 * @since 24
 */
typedef void (*OH_ContentEmbed_ClientCallbackOnEditingFinishedFunc)(
    ContentEmbed_ExtensionProxy *proxy, bool dataModified);

/**
 * @brief OE Extension停止时回调函数类型。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Proxy_RegisterOnExtensionStoppedFunc}将此函数注册到客户端OE对象。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @since 24
 */
typedef void (*OH_ContentEmbed_ClientCallbackOnExtensionStoppedFunc)(
    ContentEmbed_ExtensionProxy *proxy);

/**
 * @brief 向客户端OE对象注册OE文档更新时的回调函数。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @param onUpdateFunc 要注册的{@link OH_ContentEmbed_ClientCallbackOnUpdateFunc}回调函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_RegisterOnUpdateFunc(
    ContentEmbed_ExtensionProxy *proxy, OH_ContentEmbed_ClientCallbackOnUpdateFunc onUpdateFunc);

/**
 * @brief 向客户端OE对象注册OE文档触发错误时回调函数。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @param onErrorFunc 要注册的{@link OH_ContentEmbed_ClientCallbackOnErrorFunc}回调函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_RegisterOnErrorFunc(
    ContentEmbed_ExtensionProxy *proxy, OH_ContentEmbed_ClientCallbackOnErrorFunc onErrorFunc);

/**
 * @brief 向客户端OE对象注册OE文档编辑完成时的回调函数。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @param onEditingFinishedFunc 要注册的{@link OH_ContentEmbed_ClientCallbackOnEditingFinishedFunc}回调函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_RegisterOnEditingFinishedFunc(
    ContentEmbed_ExtensionProxy *proxy, OH_ContentEmbed_ClientCallbackOnEditingFinishedFunc onEditingFinishedFunc);

/**
 * @brief 向客户端OE对象注册OE Extension停止时的回调函数。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @param onExtensionStoppedFunc 要注册的{@link OH_ContentEmbed_ClientCallbackOnExtensionStoppedFunc}回调函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_RegisterOnExtensionStoppedFunc(
    ContentEmbed_ExtensionProxy *proxy, OH_ContentEmbed_ClientCallbackOnExtensionStoppedFunc onExtensionStoppedFunc);

/**
 * @brief 连接服务端OE Extension，建立与OE Extension的通信通道。
 *
 * @permission ohos.permission.CONNECT_OBJECTEDITOR_EXTENSION
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_PERMISSION_DENIED}：表示权限校验失败。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED}：表示必要的客户端回调未注册。</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL}：表示系统服务异常。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *     <li>{@link CE_ERR_CONNECT_LIMIT_EXCEED}：表示OE Extension连接数超出限制。</li>
 *     <li>{@link CE_ERR_FILE_NOT_GRANT}：表示文件未被授权。</li>
 *     <li>{@link CE_ERR_DISK_FULL}：表示磁盘已满。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_StartWork(ContentEmbed_ExtensionProxy *proxy);

/**
 * @brief 断开与OE Extension的通信通道。
 *
 * @permission ohos.permission.CONNECT_OBJECTEDITOR_EXTENSION
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_PERMISSION_DENIED}：表示权限校验失败。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL}：表示系统服务异常。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_StopWork(ContentEmbed_ExtensionProxy *proxy);

/**
 * @brief 从客户端OE对象获取当前OE文档的快照图像，用于预览或缩略图显示。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @param snapshot 输出参数。用于存储文档快照的{@link OH_PixelmapNative}实例指针。
 *        <br>开发者需要调用{@link OH_PixelmapNative_Destroy}销毁，以避免内存泄漏。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_EXTENSION_ERROR}：表示OE Extension发生错误。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *     <li>{@link CE_ERR_EXTENSION_NOT_SUPPORT}：表示OE Extension不支持该能力。</li>
 *         </ul>
 * @release OH_PixelmapNative_Destroy {snapshot}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_GetSnapshot(ContentEmbed_ExtensionProxy *proxy,
                                                         OH_PixelmapNative **snapshot);

/**
 * @brief 客户端OE对象请求OE Extension实例进入编辑模式。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_EXTENSION_ERROR}：表示OE Extension发生错误。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *     <li>{@link CE_ERR_EXTENSION_NOT_SUPPORT}：表示OE Extension不支持该能力。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_DoEdit(ContentEmbed_ExtensionProxy *proxy);

/**
 * @brief 查询服务端OE Extension实例对OE文档的当前编辑状态和修改状态。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @param isEditing 输出参数。表示内容嵌入文档是否正在编辑。true表示正在编辑；false表示未在编辑。
 * @param isModified 输出参数。表示内容嵌入文档是否已被修改。true表示已修改；false表示未修改。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_EXTENSION_ERROR}：表示OE Extension发生错误。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_GetEditStatus(ContentEmbed_ExtensionProxy *proxy,
                                                           bool *isEditing, bool *isModified);

/**
 * @brief 获取服务端OE Extension实例拥有的能力，以位掩码形式返回，各位的含义参见{@link ContentEmbed_CapabilityCode}。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @param bitmask 输出参数。表示服务端OE Extension实例拥有的能力，由{@link ContentEmbed_CapabilityCode}中的值组合而成。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_EXTENSION_ERROR}：表示OE Extension发生错误。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_GetCapability(ContentEmbed_ExtensionProxy *proxy,
                                                           uint32_t *bitmask);

/**
 * @brief 从客户端OE对象获取其关联的OE文档对象。
 * <br>该OE文档对象通过{@link OH_ContentEmbed_CreateDocumentByOEid}、{@link OH_ContentEmbed_CreateDocumentByFile}或
 * {@link OH_ContentEmbed_LoadDocumentFromFile}方式创建。
 * <br>当该OE文档不再需要时，应调用{@link OH_ContentEmbed_DestroyDocument}将其销毁。
 *
 * @param proxy 指向{@link ContentEmbed_ExtensionProxy}对象的指针。
 * @param ceDocument 输出参数。用于存储OE文档实例的指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyDocument {ceDocument}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_GetDocument(ContentEmbed_ExtensionProxy *proxy,
                                                         ContentEmbed_Document **ceDocument);

#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_CONTENT_EMBED_PROXY_H
