/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup AbilityRuntime
 * @{
 *
 * @brief 声明ExtensionAbility的连接选项，包括连接成功、断开连接和连接失败时的回调函数。
 *
 * @since 26.0.0
 */

/**
 * @file connect_options.h
 *
 * @brief 声明ExtensionAbility的连接选项，包括连接成功、断开连接和连接失败的回调接口。
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 26.0.0
 */

#ifndef ABILITY_RUNTIME_CONNECT_OPTIONS_H
#define ABILITY_RUNTIME_CONNECT_OPTIONS_H

#include <stdint.h>
#include "ability_runtime_common.h"
#include "AbilityKit/ability_base/want.h"
#include "IPCKit/ipc_cparcel.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义OH_AbilityRuntime_ConnectOptions结构体类型。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ConnectOptions OH_AbilityRuntime_ConnectOptions;

/**
 * @brief 回调接口已成功连接。
 *
 * @param connectOptions 表示指向{@link OH_AbilityRuntime_ConnectOptions}实例的指针。
 * @param element 表示模块对象扩展功能的元素名称。
 * @param proxy 表示远程对象实例。
 *
 * @since 26.0.0
 */
typedef void (*OH_AbilityRuntime_ConnectOptions_OnConnectCallback)(
    OH_AbilityRuntime_ConnectOptions *connectOptions, AbilityBase_Element *element, OHIPCRemoteProxy *proxy);

/**
 * @brief 回调接口已成功断开连接。
 *
 * @param connectOptions 表示指向{@link OH_AbilityRuntime_ConnectOptions}实例的指针。
 * @param element 表示模块对象扩展功能的元素名称。
 *
 * @since 26.0.0
 */
typedef void (*OH_AbilityRuntime_ConnectOptions_OnDisconnectCallback)(
    OH_AbilityRuntime_ConnectOptions *connectOptions, AbilityBase_Element *element);

/**
 * @brief 连接失败时调用回调接口。
 *
 * @param connectOptions 表示指向{@link OH_AbilityRuntime_ConnectOptions}实例的指针。
 * @param code 表示失败的错误代码。
 *
 * @since 26.0.0
 */
typedef void (*OH_AbilityRuntime_ConnectOptions_OnFailedCallback)(
    OH_AbilityRuntime_ConnectOptions *connectOptions, AbilityRuntime_ErrorCode code);

/**
 * @brief 创建一个ConnectOptions对象。
 *
 * @return 返回新创建的OH_AbilityRuntime_ConnectOptions对象。
 *     <br>调用方需调用{@link OH_AbilityRuntime_DestroyConnectOptions}销毁返回的对象，避免内存泄漏。
 * @since 26.0.0
 */
OH_AbilityRuntime_ConnectOptions* OH_AbilityRuntime_CreateConnectOptions();

/**
 * @brief 销毁指定的ConnectOptions对象。
 *
 * @param connectOptions 待销毁的ConnectOptions对象。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 操作成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} connectOptions无效。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_DestroyConnectOptions(OH_AbilityRuntime_ConnectOptions *connectOptions);

/**
 * @brief 将回调{@link OH_AbilityRuntime_ConnectOptions_OnConnectCallback}设置为
 * {@link OH_AbilityRuntime_ConnectOptions}。
 *
 * @param connectOptions 表示指向{@link OH_AbilityRuntime_ConnectOptions}实例的指针，在其中设置。
 * @param onConnectCallback 表示{@link OH_AbilityRuntime_ConnectOptions_OnConnectCallback}实例，
 * 将在其中设置。
 * @return 返回特定的错误码。
 * {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}-成功。
 * {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID}-参数校验失败。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ConnectOptions_SetOnConnectCallback(
    OH_AbilityRuntime_ConnectOptions *connectOptions,
    OH_AbilityRuntime_ConnectOptions_OnConnectCallback onConnectCallback);

/**
 * @brief 将回调{@link OH_AbilityRuntime_ConnectOptions_OnDisconnectCallback}设置为
 * {@link OH_AbilityRuntime_ConnectOptions}。
 *
 * @param connectOptions 表示指向{@link OH_AbilityRuntime_ConnectOptions}实例的指针，在其中设置。
 * @param onDisconnectCallback 表示{@link OH_AbilityRuntime_ConnectOptions_OnDisconnectCallback}实例，
 * 将在其中设置。
 * @return 返回特定的错误码。
 * {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}-成功。
 * {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID}-参数校验失败。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ConnectOptions_SetOnDisconnectCallback(
    OH_AbilityRuntime_ConnectOptions *connectOptions,
    OH_AbilityRuntime_ConnectOptions_OnDisconnectCallback onDisconnectCallback);

/**
 * @brief 将回调{@link OH_AbilityRuntime_ConnectOptions_OnFailedCallback}设置为
 * {@link OH_AbilityRuntime_ConnectOptions}。
 *
 * @param connectOptions 表示指向{@link OH_AbilityRuntime_ConnectOptions}实例的指针，在其中设置。
 * @param onFailedCallback 表示{@link OH_AbilityRuntime_ConnectOptions_OnFailedCallback}实例，
 * 将在其中设置。
 * @return 返回特定的错误码。
 * {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}-成功。
 * {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID}-参数校验失败。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ConnectOptions_SetOnFailedCallback(
    OH_AbilityRuntime_ConnectOptions *connectOptions,
    OH_AbilityRuntime_ConnectOptions_OnFailedCallback onFailedCallback);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // ABILITY_RUNTIME_CONNECT_OPTIONS_H
