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
 * @brief 提供ModularObjectExtensionAbility的C接口定义。
 *
 * @since 26.0.0
 */

/**
 * @file modular_object_extension_ability.h
 *
 * @brief 声明ModularObjectExtensionAbility实例的接口，包括注册生命周期回调函数和获取上下文等能力。
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 26.0.0
 */

#ifndef ABILITY_RUNTIME_MODULAR_OBJECT_EXTENSION_ABILITY_H
#define ABILITY_RUNTIME_MODULAR_OBJECT_EXTENSION_ABILITY_H

#include "AbilityKit/ability_base/want.h"
#include "ability_runtime_common.h"
#include "extension_ability.h"
#include "IPCKit/ipc_cparcel.h"
#include "modular_object_extension_context.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义OH_AbilityRuntime_ModObjExtensionInstance结构体。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ModularObjectExtensionInstance OH_AbilityRuntime_ModObjExtensionInstance;

/**
 * @brief 定义指向OH_AbilityRuntime_ModObjExtensionInstance的指针。
 *
 * @since 26.0.0
 */
typedef OH_AbilityRuntime_ModObjExtensionInstance* OH_AbilityRuntime_ModObjExtensionInstanceHandle;

/**
 * @brief ModularObjectExtensionAbility创建时触发的回调函数，用于初始化。
 *
 * @param instance 指向{@link OH_AbilityRuntime_ModObjExtensionInstance}实例的指针。
 * @param want 表示创建ModularObjectExtensionAbility时的Want信息。详细内容参考{@link AbilityBase_Want}.
 *
 * @since 26.0.0
 */
typedef void (*OH_AbilityRuntime_ModObjExtensionAbility_OnCreateFunc)(
    OH_AbilityRuntime_ModObjExtensionInstanceHandle instance, AbilityBase_Want *want);

/**
 * @brief ModularObjectExtensionAbility销毁前触发的回调函数。
 *
 * @param instance 指向{@link OH_AbilityRuntime_ModObjExtensionInstance}实例的指针。
 * @since 26.0.0
 */
typedef void (*OH_AbilityRuntime_ModObjExtensionAbility_OnDestroyFunc)(
    OH_AbilityRuntime_ModObjExtensionInstanceHandle instance);

/**
 * @brief ModularObjectExtensionAbility被连接时触发的回调函数。
 *
 * @param instance 指向{@link OH_AbilityRuntime_ModObjExtensionInstance}实例的指针。
 * @param want 表示创建ModularObjectExtensionAbility时的Want信息。
 *
 * @since 26.0.0
 */
typedef OHIPCRemoteStub* (*OH_AbilityRuntime_ModObjExtensionAbility_OnConnectFunc)(
    OH_AbilityRuntime_ModObjExtensionInstanceHandle instance, AbilityBase_Want *want);

/**
 * @brief 当前ModularObjectExtensionAbility的所有连接都断开时触发的回调函数。
 *
 * @param instance 指向{@link OH_AbilityRuntime_ModObjExtensionInstance}实例的指针。
 * @since 26.0.0
 */
typedef void (*OH_AbilityRuntime_ModObjExtensionAbility_OnDisconnectFunc)(
    OH_AbilityRuntime_ModObjExtensionInstanceHandle instance);

/**
 * @brief 向{@link OH_AbilityRuntime_ModObjExtensionInstance}注册
 * {@link OH_AbilityRuntime_ModObjExtensionAbility_OnCreateFunc}回调函数。
 *
 * @param instance 指向{@link OH_AbilityRuntime_ModObjExtensionInstance}实例的指针。
 * @param onCreateFunc 表示待注册的OnCreate回调函数。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} 参数校验失败。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjExtensionAbility_RegisterOnCreateFunc(
    OH_AbilityRuntime_ModObjExtensionInstanceHandle instance,
    OH_AbilityRuntime_ModObjExtensionAbility_OnCreateFunc onCreateFunc);

/**
 * @brief 向{@link OH_AbilityRuntime_ModObjExtensionInstance}注册
 * {@link OH_AbilityRuntime_ModObjExtensionAbility_OnDestroyFunc}回调函数。
 *
 * @param instance 指向{@link OH_AbilityRuntime_ModObjExtensionInstance}实例的指针。
 * @param onDestroyFunc 表示待注册的OnDestroy回调函数。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} 参数校验失败。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjExtensionAbility_RegisterOnDestroyFunc(
    OH_AbilityRuntime_ModObjExtensionInstanceHandle instance,
    OH_AbilityRuntime_ModObjExtensionAbility_OnDestroyFunc onDestroyFunc);

/**
 * @brief 向{@link OH_AbilityRuntime_ModObjExtensionInstance}注册
 * {@link OH_AbilityRuntime_ModObjExtensionAbility_OnConnectFunc}回调函数。
 *
 * @param instance 指向{@link OH_AbilityRuntime_ModObjExtensionInstance}实例的指针。
 * @param onConnectFunc 表示待注册的OnConnect回调函数。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} 参数校验失败。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjExtensionAbility_RegisterOnConnectFunc(
    OH_AbilityRuntime_ModObjExtensionInstanceHandle instance,
    OH_AbilityRuntime_ModObjExtensionAbility_OnConnectFunc onConnectFunc);

/**
 * @brief 向{@link OH_AbilityRuntime_ModObjExtensionInstance}注册
 * {@link OH_AbilityRuntime_ModObjExtensionAbility_OnDisconnectFunc}回调函数。
 *
 * @param instance 指向{@link OH_AbilityRuntime_ModObjExtensionInstance}实例的指针。
 * @param onDisconnectFunc 表示待注册的OnDisconnect回调函数。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} 参数校验失败。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjExtensionAbility_RegisterOnDisconnectFunc(
    OH_AbilityRuntime_ModObjExtensionInstanceHandle instance,
    OH_AbilityRuntime_ModObjExtensionAbility_OnDisconnectFunc onDisconnectFunc);


/**
 * @brief 从ModularObjectExtensionAbility实例中获取ExtensionAbility上下文。
 *
 * @param instance 指向{@link OH_AbilityRuntime_ModObjExtensionInstance}实例的指针。
 * @param context 指向{@link OH_AbilityRuntime_ModObjExtensionContextHandle}的指针，用于接收ExtensionAbility上下文。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} 参数校验失败。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjExtensionAbility_GetContextFromInstance(
    OH_AbilityRuntime_ModObjExtensionInstanceHandle instance, OH_AbilityRuntime_ModObjExtensionContextHandle* context);

/**
 * @brief 从基础ExtensionAbility实例中获取ModularObjectExtensionAbility实例。
 *
 * @param baseExtensionInstance 指向{@link AbilityRuntime_ExtensionInstance}的指针。
 * @param modObjExtensionInstance 指向{@link OH_AbilityRuntime_ModObjExtensionInstance}的指针，
 *     用于接收ModularObjectExtensionAbility实例，作为输出参数。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} 参数校验失败。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE}
 *     ExtensionAbility实例不是ModularObjectExtensionAbility类型。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjExtensionAbility_GetInstanceFromBase(
    AbilityRuntime_ExtensionInstanceHandle baseExtensionInstance,
    OH_AbilityRuntime_ModObjExtensionInstanceHandle* modObjExtensionInstance);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // ABILITY_RUNTIME_MODULAR_OBJECT_EXTENSION_ABILITY_H

