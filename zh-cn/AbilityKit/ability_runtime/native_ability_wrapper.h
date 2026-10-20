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
 * @brief 提供NativeAbility包装器的C接口定义
 *
 * @since 26.0.0
 */

/**
 * @file native_ability_wrapper.h
 *
 * @brief 提供NativeAbility数据信息相关接口，用于获取Ability实例ID、Ability名称和napi_env等信息。
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 26.0.0
 */

#ifndef ABILITY_RUNTIME_NATIVE_ABILITY_WRAPPER_H
#define ABILITY_RUNTIME_NATIVE_ABILITY_WRAPPER_H

#include <stdint.h>
#include <napi/native_api.h>
#include "ability_runtime_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义AbilityRuntime_NativeAbilityWrapper结构体类型，用于封装{@link UIAbility}的相关信息。
 *
 * @since 26.0.0
 */
typedef struct AbilityRuntime_NativeAbilityWrapper AbilityRuntime_NativeAbilityWrapper;

/**
 * @brief 从NativeAbility数据信息中获取Ability实例ID。
 *
 * @param nativeAbilityWrapper NativeAbility数据信息指针。
 * @param buffer 接收实例ID字符串的缓冲区指针。实例ID为UUID格式，长度为37字节。
 * @param bufferSize 缓冲区长度，必须至少为37字节。确保缓冲区至少有额外一个字节用于'\0'。
 * @return 返回错误码。
 *     <br>返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}表示操作成功。
 *     <br>返回{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID}表示nativeAbilityWrapper或buffer为空指针，或bufferSize小于37。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetAbilityInstanceId(
    const AbilityRuntime_NativeAbilityWrapper* nativeAbilityWrapper, char* buffer, const int32_t bufferSize);

/**
 * @brief 从NativeAbility数据信息中获取Ability名称。
 *
 * @param nativeAbilityWrapper NativeAbility数据信息指针。
 * @param buffer 接收Ability名称字符串的缓冲区指针。传入nullptr可查询Ability名称长度。
 * @param bufferSize 缓冲区长度（字节）。确保缓冲区至少有额外一个字节用于'\0'。
 * @param writeLength 输出Ability名称字符串长度。
 * @return 返回错误码。
 *     <br>返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}表示操作成功。
 *     <br>返回{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID}表示nativeAbilityWrapper或writeLength为空指针，或缓冲区太小无法存储Ability名称。
 *     <br>返回{@link ABILITY_RUNTIME_ERROR_CODE_ABILITY_WRAPPER_INVALID}表示NativeAbility数据信息无效或不完整。
 *     <br>返回{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL}表示内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetAbilityName(
    const AbilityRuntime_NativeAbilityWrapper *nativeAbilityWrapper, char *buffer, const int32_t bufferSize,
    int32_t *writeLength);

/**
 * @brief 从NativeAbility数据信息中获取napi_env。
 *
 * @param nativeAbilityWrapper NativeAbility数据信息指针。
 * @param env 接收napi_env值的指针。napi_env在进程终止前一直有效。
 * @return 返回错误码。
 *     <br>返回{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR}表示操作成功。
 *     <br>返回{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID}表示nativeAbilityWrapper或env为空指针。
 *     <br>返回{@link ABILITY_RUNTIME_ERROR_CODE_ABILITY_WRAPPER_INVALID}表示NativeAbility数据信息无效或不完整。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetEnv(
    const AbilityRuntime_NativeAbilityWrapper* nativeAbilityWrapper, napi_env* env);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // ABILITY_RUNTIME_NATIVE_ABILITY_WRAPPER_H

