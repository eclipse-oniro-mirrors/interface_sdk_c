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
 * @brief 内容嵌入（ContentEmbed）模块提供对象编辑（Object Editor，简称OE）功能框架，支持应用间文档的嵌入与协同编辑。<br>
 * 模块采用客户端-服务端架构：服务端应用通过扩展（extension）接口实现OE Extension；
 * 客户端应用通过代理（proxy）接口查询服务端应用注册的OE Extension信息并与该OE Extension交互。<br>
 * 通过OE技术实现的被嵌入文档（简称OE文档），在客户端界面可呈现为缩略图或快照（Snapshot），或以OE格式序列化为二进制数据，保存在内存或文件（称为OE格式文件）中。
 *
 * @syscap SystemCapability.ContentEmbed.ObjectEditor
 * @since 24
 */

/**
 * @file content_embed_extension.h
 *
 * @brief 定义服务端应用OE Extension相关数据结构和操作接口，提供OE Extension实例生命周期管理、客户端OE对象关联与回调注册、快照获取及编辑操作等能力，适用于在服务端处理文档嵌入与编辑场景。
 *
 * @library libcontent_embed_ndk.so
 * @kit ContentEmbedKit
 * @include <ContentEmbedKit/content_embed/content_embed_extension.h>
 * @syscap SystemCapability.ContentEmbed.ObjectEditor
 * @since 24
 */

#ifndef OHOS_CONTENT_EMBED_EXTENSION_H
#define OHOS_CONTENT_EMBED_EXTENSION_H

#include <stdbool.h>
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
 * @brief 声明OE文档结构体类型。封装了被嵌入文档的元数据、内容和存储结构，用于在应用中统一管理嵌入文档的数据，便于对嵌入文档进行访问、解析与存储。<br>开发者可根据数据来源选取：<br>拥有OEID时使用
 * {@link OH_ContentEmbed_CreateDocumentByOEid}；<br>拥有源文件并需嵌入/链接时使用{@link OH_ContentEmbed_CreateDocumentByFile}；<br>
 * 拥有已保存的OE格式文件时使用{@link OH_ContentEmbed_LoadDocumentFromFile}。
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
 * @brief 声明OE Extension上下文对象指针类型。该指针对象用于在ContentEmbed Extension流程中承载和管理OE Extension的运行上下文信息。<br>可通过
 * {@link OH_ContentEmbed_Extension_GetContentEmbedContext}从OE Extension实例获取，支持通过
 * {@link OH_ContentEmbed_Extension_GetContext}获取AbilityRuntime上下文、
 * {@link OH_ContentEmbed_Extension_ContextStartSelfUIAbility}或
 * {@link OH_ContentEmbed_Extension_ContextStartSelfUIAbilityWithStartOptions}启动自身UIAbility及
 * {@link OH_ContentEmbed_Extension_ContextTerminateAbility}销毁OE Extension等操作。
 *
 * @since 24
 */
typedef struct ContentEmbed_ExtensionContext* ContentEmbed_ExtensionContextHandle;

/**
 * @brief 声明OE Extension实例的结构体类型。管理扩展的生命周期、回调注册和客户端OE对象关联等核心功能。适用于服务端应用需要嵌入OE扩展能力并完成扩展与客户端OE文档之间生命周期同步、回调监听及对象关联绑定的场景。
 *
 * @since 24
 */
typedef struct ContentEmbed_ExtensionInstance ContentEmbed_ExtensionInstance;

/**
 * @brief 声明OE Extension实例对象指针类型。需要在{@link OH_AbilityRuntime_OnNativeExtensionCreate}函数实现里通过
 * {@link OH_ContentEmbed_Extension_GetExtensionInstance}方法，在OE Extension被系统启动时获取OE Extension实例对象。
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
 * @brief 声明ContentEmbed_Object对象指针类型。当客户端连接服务端时，系统创建该对象实例，并回调
 * {@link OH_ContentEmbed_Extension_RegisterOnObjectAttachFunc}注册的{@link OH_ContentEmbed_Extension_OnObjectAttachFunc}
 * 函数，并传入该类型的实例指针。
 *
 * @since 24
 */
typedef struct ContentEmbed_Object* ContentEmbed_ObjectHandle;

/**
 * @brief 从OE Extension实例中获取其对应的OE Extension上下文对象。支持通过{@link OH_ContentEmbed_Extension_GetContext}获取AbilityRuntime上下文、
 * {@link OH_ContentEmbed_Extension_ContextStartSelfUIAbility}或
 * {@link OH_ContentEmbed_Extension_ContextStartSelfUIAbilityWithStartOptions}启动自身UIAbility及
 * {@link OH_ContentEmbed_Extension_ContextTerminateAbility}销毁OE Extension等操作。
 *
 * @param ceInstance OE Extension实例对象的指针。
 * @param ceContext 输出参数。调用成功后，该指针指向OE Extension实例的上下文对象。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_NULL_POINTER：表示出现空指针错误。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_GetContentEmbedContext(ContentEmbed_ExtensionInstanceHandle ceInstance,
                                                                        ContentEmbed_ExtensionContextHandle *ceContext);

/**
 * @brief 从OE Extension上下文中获取AbilityRuntime上下文。
 *
 * @param ceContext OE Extension上下文对象的指针。
 * @param context 输出参数。调用成功后，该指针指向{@link AbilityRuntime_ContextHandle}上下文对象。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_NULL_POINTER：表示出现空指针错误。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_GetContext(ContentEmbed_ExtensionContextHandle ceContext,
                                                            AbilityRuntime_ContextHandle *context);

/**
 * @brief 从ExtensionAbility基类实例中获取对应的OE Extension实例。
 * <br>建议在{@link OH_AbilityRuntime_OnNativeExtensionCreate}函数实现里调用，获取实例后应调用
 * {@link OH_ContentEmbed_Extension_RegisterOnCreateFunc}和
 * {@link OH_ContentEmbed_Extension_RegisterOnDestroyFunc}注册OE Extension生命周期回调函数。
 *
 * @param baseInstance 指向{@link AbilityRuntime_ExtensionInstanceHandle}基类实例的指针。
 * @param ceInstance 输出参数。调用成功后，该指针指向OE Extension实例对象。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_NULL_POINTER：表示出现空指针错误。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
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
 * @param want 指向{@link AbilityBase_Want}实例的指针，包含OE Extension创建时传递的启动参数。
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
 * @brief 当客户端OE对象连接到OE Extension实例时的回调函数类型，用于执行服务端OE对象关联后的初始化操作。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Extension_RegisterOnObjectAttachFunc}注册到OE Extension实例。在此回调中，开发者需要调用
 * {@link OH_ContentEmbed_Extension_RegisterOnWriteToDataStreamFunc}、
 * {@link OH_ContentEmbed_Extension_RegisterOnGetCapabilityFunc}、{@link OH_ContentEmbed_Extension_RegisterOnDoEditFunc}、
 * {@link OH_ContentEmbed_Extension_RegisterOnGetSnapshotFunc}和
 * {@link OH_ContentEmbed_Extension_RegisterOnGetEditStatusFunc}函数注册用于响应客户端OE对象请求的回调函数。
 *
 * @param instance OE Extension实例对象的指针。
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnObjectAttachFunc)(
    ContentEmbed_ExtensionInstanceHandle instance, ContentEmbed_ObjectHandle object);

/**
 * @brief 当客户端OE对象从OE Extension实例断开连接时的回调函数类型，用于执行服务端OE对象断开连接后的清理操作。
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
 * <br>在此回调中，开发者需要调用{@link OH_ContentEmbed_Extension_SetSnapshot}设置OE文档快照图像，以响应客户端的快照获取请求。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @since 24
 */
typedef void (*OH_ContentEmbed_Extension_OnGetSnapshotFunc)(
    ContentEmbed_ObjectHandle object);

/**
 * @brief 当客户端OE对象请求编辑OE文档时的回调函数类型。
 * <br>开发者需要实现此函数并通过{@link OH_ContentEmbed_Extension_RegisterOnDoEditFunc}注册到服务端OE对象。
 * <br>在此回调中，可以通过{@link OH_ContentEmbed_Extension_ContextStartSelfUIAbility}和
 * {@link OH_ContentEmbed_Extension_ContextStartSelfUIAbilityWithStartOptions}拉起本应用的UIAbility进行编辑。编辑完成后，开发者需要调用
 * {@link OH_ContentEmbed_Extension_CallbackToOnEditingFinished}通知客户端编辑已完成。
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
 * <br>该回调注册后不支持取消注册，在实例生命周期内持续有效。
 *
 * @param instance 指向OE Extension实例对象的指针。
 * @param onCreateFunc 要注册的{@link OH_ContentEmbed_Extension_OnCreateFunc}生命周期函数。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnCreateFunc(
    ContentEmbed_ExtensionInstanceHandle instance, OH_ContentEmbed_Extension_OnCreateFunc onCreateFunc);

/**
 * @brief 注册OE Extension实例销毁时的生命周期函数。
 * <br>该回调注册后不支持取消注册，在实例生命周期内持续有效。
 *
 * @param instance 指向OE Extension实例对象的指针。
 * @param onDestroyFunc 要注册的{@link OH_ContentEmbed_Extension_OnDestroyFunc}生命周期函数。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
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
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnObjectAttachFunc(
    ContentEmbed_ExtensionInstanceHandle instance,
    OH_ContentEmbed_Extension_OnObjectAttachFunc onObjectAttachFunc);

/**
 * @brief 取消注册客户端OE对象连接时的回调函数。可以通过调用{@link OH_ContentEmbed_Extension_RegisterOnObjectAttachFunc}重新注册。
 *
 * @param instance 指向OE Extension实例对象的指针。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
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
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnObjectDetachFunc(
    ContentEmbed_ExtensionInstanceHandle instance,
    OH_ContentEmbed_Extension_OnObjectDetachFunc onObjectDetachFunc);

/**
 * @brief 取消注册客户端OE对象断开连接时的回调函数。可以通过调用{@link OH_ContentEmbed_Extension_RegisterOnObjectDetachFunc}重新注册。
 *
 * @param instance 指向OE Extension实例对象的指针。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_UnRegisterOnObjectDetachFunc(
    ContentEmbed_ExtensionInstanceHandle instance);

/**
 * @brief 注册服务端OE对象写入OE文档数据流时的回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param onWriteToDataStreamFunc 要注册的{@link OH_ContentEmbed_Extension_OnWriteToDataStreamFunc}回调函数。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
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
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnGetSnapshotFunc(
    ContentEmbed_ObjectHandle object, OH_ContentEmbed_Extension_OnGetSnapshotFunc onGetSnapshotFunc);

/**
 * @brief 注册客户端OE对象请求编辑OE文档时的回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param onDoEditFunc 要注册的{@link OH_ContentEmbed_Extension_OnDoEditFunc}回调函数。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnDoEditFunc(
    ContentEmbed_ObjectHandle object, OH_ContentEmbed_Extension_OnDoEditFunc onDoEditFunc);

/**
 * @brief 注册客户端OE对象请求OE文档编辑状态时的回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param onGetEditStatusFunc 要注册的{@link OH_ContentEmbed_Extension_OnGetEditStatusFunc}回调函数。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnGetEditStatusFunc(
    ContentEmbed_ObjectHandle object, OH_ContentEmbed_Extension_OnGetEditStatusFunc onGetEditStatusFunc);

/**
 * @brief 注册客户端OE对象查询OE Extension实例支持能力时的回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param onGetCapabilityFunc 要注册的{@link OH_ContentEmbed_Extension_OnGetCapabilityFunc}回调函数。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_RegisterOnGetCapabilityFunc(
    ContentEmbed_ObjectHandle object, OH_ContentEmbed_Extension_OnGetCapabilityFunc onGetCapabilityFunc);

/**
 * @brief 获取服务端OE对象关联的OE文档实例。文档实例的生命周期由系统管理，无需手动释放。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param ceDocument 输出参数。调用成功后，该指针指向关联的OE文档实例。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_NULL_POINTER：表示出现空指针错误。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_GetContentEmbedDocument(
    ContentEmbed_ObjectHandle object, ContentEmbed_Document **ceDocument);

/**
 * @brief 触发客户端OE对象注册的OE文档更新回调函数。
 * <br>当服务端OE文档内容发生变化后调用，通知客户端刷新文档显示。建议在文档数据修改完成后调用，避免在修改过程中频繁触发。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_NULL_POINTER：表示出现空指针错误。
 *     <br>CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED：表示客户端回调未注册。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_CLIENT_CALLBACK_FAILED：表示客户端回调执行失败。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_CallbackToOnUpdate(
    ContentEmbed_ObjectHandle object);

/**
 * @brief 触发客户端OE对象注册的OE文档错误回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param code 表示错误码，详细定义参见{@link ContentEmbed_ErrorCode}。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_NULL_POINTER：表示出现空指针错误。
 *     <br>CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED：表示客户端回调未注册。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_CLIENT_CALLBACK_FAILED：表示客户端回调执行失败。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_CallbackToOnError(
    ContentEmbed_ObjectHandle object, ContentEmbed_ErrorCode code);

/**
 * @brief 触发客户端OE对象注册的OE文档编辑完成回调函数。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param dataModified 表示文档数据是否已被修改。true表示有修改，false表示无修改。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_NULL_POINTER：表示出现空指针错误。
 *     <br>CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED：表示客户端回调未注册。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_CLIENT_CALLBACK_FAILED：表示客户端回调执行失败。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_CallbackToOnEditingFinished(
    ContentEmbed_ObjectHandle object, bool dataModified);

/**
 * @brief 触发OE Extension关联的所有客户端OE对象注册的OE Extension停止时的回调函数。
 *
 * @param instance 指向OE Extension实例对象的指针。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_NULL_POINTER：表示出现空指针错误。
 *     <br>CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED：表示客户端回调未注册。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_CLIENT_CALLBACK_FAILED：表示客户端回调执行失败。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_CallbackToOnExtensionStopped(
    ContentEmbed_ExtensionInstanceHandle instance);

/**
 * @brief 设置客户端OE对象关联的OE文档快照图像。
 *
 * @param object {@link ContentEmbed_ObjectHandle}实例。
 * @param pixelMap 文档快照的像素图对象，详细信息参考{@link OH_PixelmapNative}。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_NULL_POINTER：表示出现空指针错误。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 *     <br>CE_ERR_IMAGE_PACKER_OPERATION_FAILED：表示ImagePacker操作失败。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_SetSnapshot(
    ContentEmbed_ObjectHandle object, OH_PixelmapNative *pixelMap);

/**
 * @brief 通过OE Extension上下文启动自身的[UIAbility](../apis-ability-kit/js-apis-app-ability-uiAbility.md#uiability)。
 * 如需指定启动选项，参考{@link OH_ContentEmbed_Extension_ContextStartSelfUIAbilityWithStartOptions}。
 *
 * @param context 指向OE Extension上下文对象的指针。
 * @param want 启动UIAbility时传递的参数，详细信息参考{@link AbilityBase_Want}。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_NULL_POINTER：表示出现空指针错误。
 *     <br>CE_ERR_SYSTEM_ABNORMAL：表示系统服务异常。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_ContextStartSelfUIAbility(
    ContentEmbed_ExtensionContextHandle context, AbilityBase_Want *want);

/**
 * @brief 使用启动选项启动OE Extension上下文自身的[UIAbility](../apis-ability-kit/js-apis-app-ability-uiAbility.md#uiability)。
 * 如果不需要指定启动选项，参考{@link OH_ContentEmbed_Extension_ContextStartSelfUIAbility}。
 *
 * @param context 指向OE Extension上下文对象的指针。
 * @param want 启动UIAbility时传递的参数，详细信息参考{@link AbilityBase_Want}。
 * @param options 启动UIAbility时的附加选项，详细信息参考{@link AbilityRuntime_StartOptions}。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_NULL_POINTER：表示出现空指针错误。
 *     <br>CE_ERR_SYSTEM_ABNORMAL：表示系统服务异常。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_ContextStartSelfUIAbilityWithStartOptions(
    ContentEmbed_ExtensionContextHandle context,
    AbilityBase_Want *want, AbilityRuntime_StartOptions *options);

/**
 * @brief 销毁OE Extension。当OE Extension不再需要提供服务时调用，通过上下文销毁Extension实例并释放相关资源。建议在所有客户端OE对象断开连接且完成资源清理后调用，
 * 销毁后关联的客户端OE对象将收到Extension停止通知。
 *
 * @param context 指向OE Extension上下文对象的指针。
 * @return 返回特定的错误码：
 *     <br>CE_ERR_OK：表示操作成功。
 *     <br>CE_ERR_PARAM_INVALID：表示参数检查失败。
 *     <br>CE_ERR_NULL_POINTER：表示出现空指针错误。
 *     <br>CE_ERR_SYSTEM_ABNORMAL：表示系统服务异常。
 *     <br>CE_ERR_DEVICE_NOT_SUPPORTED：表示设备不支持。
 *     <br>CE_ERR_IN_DLP_SANDBOX：表示应用在DLP沙箱中，不支持此操作。
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Extension_ContextTerminateAbility(
    ContentEmbed_ExtensionContextHandle context);

#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_CONTENT_EMBED_EXTENSION_H
