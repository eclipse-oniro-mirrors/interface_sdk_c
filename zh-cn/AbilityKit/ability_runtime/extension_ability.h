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
 * @brief 提供ExtensionAbility回调函数类型声明和入口函数名称声明。
 *
 * @since 24
 */

/**
 * @file extension_ability.h
 *
 * @brief 提供ExtensionAbility回调函数类型声明和入口函数名称声明。
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 24
 */

#ifndef ABILITY_RUNTIME_EXTENSION_ABILITY_H
#define ABILITY_RUNTIME_EXTENSION_ABILITY_H

#include "ability_runtime_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义AbilityRuntime_ExtensionInstance结构体类型。
 *
 * @since 24
 */
struct AbilityRuntime_ExtensionInstance;

/**
 * @brief 定义AbilityRuntime_ExtensionInstance对象指针。
 *
 * @since 24
 */
typedef struct AbilityRuntime_ExtensionInstance* AbilityRuntime_ExtensionInstanceHandle;

/**
 * @brief ExtensionAbility创建回调函数类型。ExtensionAbility中必须实现的回调函数类型，用于实例化ExtensionAbility。
 *
 * @since 24
 */
typedef void AbilityRuntime_Extension_CreateFunc(
    AbilityRuntime_ExtensionInstanceHandle handle, const char *abilityName);

/**
 * @brief ExtensionAbility入口函数名称声明。开发者需要实现一个类型为{@link AbilityRuntime_Extension_CreateFunc}的函数，
 * 并将其命名为OH_AbilityRuntime_OnNativeExtensionCreate。系统会自动查找并调用此函数来完成ExtensionAbility实例的初始化。
 *
 * @since 24
 */
AbilityRuntime_Extension_CreateFunc OH_AbilityRuntime_OnNativeExtensionCreate;

#ifdef __cplusplus
}
#endif

/** @} */
#endif // ABILITY_RUNTIME_EXTENSION_ABILITY_H