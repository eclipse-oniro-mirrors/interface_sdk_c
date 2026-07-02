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
 * @file content_embed_extension.h
 *
 * @brief 定义服务端应用OE Extension相关数据结构和操作接口。
 *
 * @library libcontent_embed_ndk.so
 * @kit ContentEmbedKit
 * @syscap SystemCapability.ContentEmbed.ObjectEditor
 * @since 24
 */

#ifndef OHOS_CONTENT_EMBED_EXTENSION_H
#define OHOS_CONTENT_EMBED_EXTENSION_H

#include <stdint.h>
#include <stdlib.h>
#include "content_embed_common.h"
#include "AbilityKit/ability_runtime/extension_ability.h"
#include "AbilityKit/ability_runtime/context.h"
#include "AbilityKit/ability_runtime/start_options.h"
#include "AbilityKit/ability_base/want.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief 声明OE文档结构体类型。封装了被嵌入文档的元数据、内容和存储结构。
 *
 * @since 24
 */
typedef struct ContentEmbed_Document ContentEmbed_Document;

/**
 * @brief 声明OE Extension上下文的结构体类型。
 *
 * @since 24
 */
typedef struct ContentEmbed_ExtensionContext ContentEmbed_ExtensionContext;

/**
 * @brief 声明OE Extension上下文对象指针类型。
 *
 * @since 24
 */
typedef struct ContentEmbed_ExtensionContext* ContentEmbed_ExtensionContextHandle;

/**
 * @brief 声明OE Extension实例的结构体类型。管理扩展的生命周期、回调注册和客户端OE对象关联等核心功能。
 *
 * @since 24
 */
typedef struct ContentEmbed_ExtensionInstance ContentEmbed_ExtensionInstance;

/**
 * @brief 声明OE Extension实例对象指针类型。
 *
 * @since 24
 */
typedef struct ContentEmbed_ExtensionInstance* ContentEmbed_ExtensionInstanceHandle;

/**
 * @brief 声明ContentEmbed_Object结构体类型。用于指向OE文档在服务端封装的文档嵌入和编辑的程序对象（简称服务端OE对象）。
 *
 * @since 24
 */
typedef struct ContentEmbed_Object ContentEmbed_Object;

/**
 * @brief 声明ContentEmbed_Object对象指针类型。
 *
 * @since 24
 */
typedef struct ContentEmbed_Object* ContentEmbed_ObjectHandle;

/**
 * @brief 从OE Extension实例中获取其对应的OE Extension上下文对象。
 *
 * @param ceInstance OE Extension实例对象的指针。
 * @param ceContext 输出参数。调用成功后，该指针指向OE Extension实例的上下文对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_GetContentEmbedContext(ContentEmbed_ExtensionInstanceHandle ceInstance,
                                                                        ContentEmbed_ExtensionContextHandle *ceContext);

/**
 * @brief 从OE Extension上下文中获取AbilityRuntime上下文。
 *
 * @param ceContext OE Extension上下文对象的指针。
 * @param context 输出参数。调用成功后，该指针指向{@link AbilityRuntime_ContextHandle}上下文对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_GetContext(ContentEmbed_ExtensionContextHandle ceContext,
                                                            AbilityRuntime_ContextHandle *context);

/**
 * @brief 从ExtensionAbility基类实例中获取对应的OE Extension实例。
 *
 * @param baseInstance {@link AbilityRuntime_ExtensionInstanceHandle}实例。
 * @param ceInstance 输出参数。调用成功后，该指针指向OE Extension实例对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_GetExtensionInstance(
    AbilityRuntime_ExtensionInstanceHandle baseInstance,
    ContentEmbed_ExtensionInstanceHandle *ceInstance);

/**
 * @brief OE Extension实例创建时的生命周期函数类型。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Extension_RegisterOnCreateFunc}注册到OE Extension实例。
 *
 * @param instance OE Extension实例对象的指针。
 * @param want {@link AbilityBase_Want}实例的指针。
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnCreateFunc)(
    ContentEmbed_ExtensionInstanceHandle instance, AbilityBase_Want *want);

/**
 * @brief OE Extension实例销毁时的生命周期函数类型。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Extension_RegisterOnDestroyFunc}注册到OE Extension实例。
 *
 * @param instance OE Extension实例对象的指针。
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnDestroyFunc)(
    ContentEmbed_ExtensionInstanceHandle instance);

/**
 * @brief 当客户端OE对象连接到OE Extension实例时触发此回调函数，用于执行服务端OE对象关联后的初始化操作。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Extension_RegisterOnObjectAttachFunc}注册到OE Extension实例。
 *
 * @param instance OE Extension实例对象的指针。
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnObjectAttachFunc)(
    ContentEmbed_ExtensionInstanceHandle instance, ContentEmbed_ObjectHandle object);

/**
 * @brief 当客户端OE对象从OE Extension实例断开连接时触发此回调函数，用于执行服务端OE对象断开连接后的清理操作。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Extension_RegisterOnObjectDetachFunc}注册到OE Extension实例。
 *
 * @param instance OE Extension实例对象的指针。
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnObjectDetachFunc)(
    ContentEmbed_ExtensionInstanceHandle instance, ContentEmbed_ObjectHandle object);

/**
 * @brief 当服务端OE对象写入OE文档数据流时的回调函数类型。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Extension_RegisterOnWriteToDataStreamFunc}注册到服务端OE对象。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnWriteToDataStreamFunc)(
    ContentEmbed_ObjectHandle object);

/**
 * @brief 当客户端OE对象请求获取OE文档快照时的回调函数类型。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Extension_RegisterOnGetSnapshotFunc}注册到服务端OE对象。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnGetSnapshotFunc)(
    ContentEmbed_ObjectHandle object);

/**
 * @brief 当客户端OE对象请求编辑OE文档时的回调函数类型。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Extension_RegisterOnDoEditFunc}注册到服务端OE对象。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnDoEditFunc)(
    ContentEmbed_ObjectHandle object);

/**
 * @brief 当客户端OE对象请求OE文档编辑状态时的回调函数类型。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Extension_RegisterOnGetEditStatusFunc}注册到服务端OE对象。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param isEditing 输出参数。表示OE文档是否正在编辑，true表示正在编辑；false表示未编辑。
 * @param isModified 输出参数。表示OE文档是否已被修改，true表示已被修改；false表示未修改。
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnGetEditStatusFunc)(
    ContentEmbed_ObjectHandle object, bool *isEditing, bool *isModified);

/**
 * @brief 当客户端OE对象查询OE Extension实例支持能力时的回调函数类型。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Extension_RegisterOnGetCapabilityFunc}注册到服务端OE对象。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param bitmask 输出参数，表示OE Extension实例支持的能力，由{@link ContentEmbed_CapabilityCode}中的值组合而成。
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnGetCapabilityFunc)(
    ContentEmbed_ObjectHandle object, uint32_t *bitmask);

/**
 * @brief 注册OE Extension实例创建时的生命周期函数。
 *
 * @param instance 指向OE Extension实例对象的指针。
 * @param onCreateFunc 要注册的{@link OH_ContentEmbed_Extension_OnCreateFunc}生命周期函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnCreateFunc(
    ContentEmbed_ExtensionInstanceHandle instance, OH_ContentEmbed_Extension_OnCreateFunc onCreateFunc);

/**
 * @brief 注册OE Extension实例销毁时的生命周期函数。
 *
 * @param instance 指向OE Extension实例对象的指针。
 * @param onDestroyFunc 要注册的{@link OH_ContentEmbed_Extension_OnDestroyFunc}生命周期函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnDestroyFunc(
    ContentEmbed_ExtensionInstanceHandle instance, OH_ContentEmbed_Extension_OnDestroyFunc onDestroyFunc);

/**
 * @brief 注册客户端OE对象连接时的回调函数。
 * <br>可以通过调用{@link OH_ContentEmbed_Extension_UnRegisterOnObjectAttachFunc}取消注册。
 *
 * @param instance 指向OE Extension实例对象的指针。
 * @param onObjectAttachFunc 要注册的{@link OH_ContentEmbed_Extension_OnObjectAttachFunc}回调函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnObjectAttachFunc(
    ContentEmbed_ExtensionInstanceHandle instance,
    OH_ContentEmbed_Extension_OnObjectAttachFunc onObjectAttachFunc);

/**
 * @brief 取消注册客户端OE对象连接时的回调函数。
 *
 * @param instance 指向OE Extension实例对象的指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_UnRegisterOnObjectAttachFunc(
    ContentEmbed_ExtensionInstanceHandle instance);

/**
 * @brief 注册客户端OE对象断开连接时的回调函数。
 * <br>可以通过调用{@link OH_ContentEmbed_Extension_UnRegisterOnObjectDetachFunc}取消注册。
 *
 * @param instance 指向OE Extension实例对象的指针。
 * @param onObjectDetachFunc 要注册的{@link OH_ContentEmbed_Extension_OnObjectDetachFunc}回调函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnObjectDetachFunc(
    ContentEmbed_ExtensionInstanceHandle instance,
    OH_ContentEmbed_Extension_OnObjectDetachFunc onObjectDetachFunc);

/**
 * @brief 取消注册客户端OE对象断开连接时的回调函数。
 *
 * @param instance 指向OE Extension实例对象的指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_UnRegisterOnObjectDetachFunc(
    ContentEmbed_ExtensionInstanceHandle instance);

/**
 * @brief 注册服务端OE对象写入OE文档数据流时的回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param onWriteToDataStreamFunc 要注册的{@link OH_ContentEmbed_Extension_OnWriteToDataStreamFunc}回调函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnWriteToDataStreamFunc(
    ContentEmbed_ObjectHandle object,
    OH_ContentEmbed_Extension_OnWriteToDataStreamFunc onWriteToDataStreamFunc);

/**
 * @brief 注册客户端OE对象请求获取OE文档快照时的回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param onGetSnapshotFunc 要注册的{@link OH_ContentEmbed_Extension_OnGetSnapshotFunc}回调函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnGetSnapshotFunc(
    ContentEmbed_ObjectHandle object, OH_ContentEmbed_Extension_OnGetSnapshotFunc onGetSnapshotFunc);

/**
 * @brief 注册客户端OE对象请求编辑OE文档时的回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param onDoEditFunc 要注册的{@link OH_ContentEmbed_Extension_OnDoEditFunc}回调函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnDoEditFunc(
    ContentEmbed_ObjectHandle object, OH_ContentEmbed_Extension_OnDoEditFunc onDoEditFunc);

/**
 * @brief 注册客户端OE对象请求OE文档编辑状态时的回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param onGetEditStatusFunc 要注册的{@link OH_ContentEmbed_Extension_OnGetEditStatusFunc}回调函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnGetEditStatusFunc(
    ContentEmbed_ObjectHandle object, OH_ContentEmbed_Extension_OnGetEditStatusFunc onGetEditStatusFunc);

/**
 * @brief 注册客户端OE对象查询OE Extension实例支持能力时的回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param onGetCapabilityFunc 要注册的{@link OH_ContentEmbed_Extension_OnGetCapabilityFunc}回调函数。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnGetCapabilityFunc(
    ContentEmbed_ObjectHandle object, OH_ContentEmbed_Extension_OnGetCapabilityFunc onGetCapabilityFunc);

/**
 * @brief 获取服务端OE对象关联的OE文档实例。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param ceDocument 输出参数。调用成功后，该指针指向关联的OE文档实例。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_GetContentEmbedDocument(
    ContentEmbed_ObjectHandle object, ContentEmbed_Document **ceDocument);

/**
 * @brief 触发客户端OE对象注册的OE文档更新回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED}：表示客户端回调未注册。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_FAILED}：表示客户端回调执行失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_CallbackToOnUpdate(
    ContentEmbed_ObjectHandle object);

/**
 * @brief 触发客户端OE对象注册的OE文档错误回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param code 表示错误码，详细定义参见{@link ContentEmbed_ErrorCode}。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED}：表示客户端回调未注册。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_FAILED}：表示客户端回调执行失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_CallbackToOnError(
    ContentEmbed_ObjectHandle object, ContentEmbed_ErrorCode code);

/**
 * @brief 触发客户端OE对象注册的OE文档编辑完成回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param dataModified 表示文档数据是否已被修改。true表示有修改，false表示无修改。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED}：表示客户端回调未注册。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_FAILED}：表示客户端回调执行失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_CallbackToOnEditingFinished(
    ContentEmbed_ObjectHandle object, bool dataModified);

/**
 * @brief 触发OE Extension关联的所有客户端OE对象注册的OE Extension停止时的回调函数。
 *
 * @param instance 指向OE Extension实例对象的指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED}：表示客户端回调未注册。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_FAILED}：表示客户端回调执行失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_CallbackToOnExtensionStopped(
    ContentEmbed_ExtensionInstanceHandle instance);

/**
 * @brief 设置客户端OE对象关联的OE文档快照图像。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param pixelMap 文档快照的像素图对象，详细信息参考{@link OH_PixelmapNative}。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *     <li>{@link CE_ERR_IMAGE_PACKER_OPERATION_FAILED}：表示图像操作失败。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_SetSnapshot(
    ContentEmbed_ObjectHandle object, OH_PixelmapNative *pixelMap);

/**
 * @brief 通过OE Extension上下文启动自身的{@link UIAbility}。
 *
 * @param context 指向OE Extension上下文对象的指针。
 * @param want 启动UIAbility时传递的参数，详细信息参考{@link AbilityBase_Want}。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL}：表示系统服务异常。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_ContextStartSelfUIAbility(
    ContentEmbed_ExtensionContextHandle context, AbilityBase_Want *want);

/**
 * @brief 使用启动选项启动OE Extension上下文自身的{@link UIAbility}。
 *
 * @param context 指向OE Extension上下文对象的指针。
 * @param want 启动UIAbility时传递的参数，详细信息参考{@link AbilityBase_Want}。
 * @param options 启动UIAbility时的附加选项，详细信息参考{@link AbilityRuntime_StartOptions}。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL}：表示系统服务异常。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_ContextStartSelfUIAbilityWithStartOptions(
    ContentEmbed_ExtensionContextHandle context,
    AbilityBase_Want *want, AbilityRuntime_StartOptions *options);

/**
 * @brief 销毁OE Extension。
 *
 * @param context 指向OE Extension上下文对象的指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL}：表示系统服务异常。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_ContextTerminateAbility(
    ContentEmbed_ExtensionContextHandle context);

#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_CONTENT_EMBED_EXTENSION_H