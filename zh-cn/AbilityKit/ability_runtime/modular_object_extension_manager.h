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
 * @brief 提供模ModularObjectExtensionAbility的C接口定义。
 *
 * @since 26.0.0
 */

/**
 * @file modular_object_extension_manager.h
 *
 * @brief 声明用于管理ModularObjectExtensionAbility的接口，包括查询ModularObjectExtensionAbility信息、连接与断开连接等能力。
 * 开发者可以通过本模块提供的接口查询当前应用内所有已注册的ModularObjectExtensionAbility的信息（包括启动模式、进程模式、线程模式、组件名称及禁用状态等），
 * 并根据需要建立或断开与ModularObjectExtensionAbility的通信连接。
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 26.0.0
 */

#ifndef ABILITY_RUNTIME_MODULAR_OBJECT_EXTENSION_MANAGER_H
#define ABILITY_RUNTIME_MODULAR_OBJECT_EXTENSION_MANAGER_H

#include <stdbool.h>
#include <stddef.h>
#include "AbilityKit/ability_base/want.h"
#include "ability_runtime_common.h"
#include "context.h"
#include "connect_options.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 表示单个ModularObjectExtensionAbility的信息句柄。该句柄指向一个ModularObjectExtensionAbility的完整信息，包含启动模式、进程模式、线程模式、组件名称（
 * {@link AbilityBase_Element}）以及禁用状态等属性。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ModularObjectExtensionInfo* OH_AbilityRuntime_ModObjExtensionInfoHandle;

/**
 * @brief 表示当前应用内所有ModularObjectExtensionAbility信息的集合句柄。该句柄指向一个包含多个{@link OH_AbilityRuntime_ModObjExtensionInfoHandle}
 * 的集合，可通过{@link OH_AbilityRuntime_GetCountFromAllModObjExtensionInfos} 获取集合中元素的数量，并通过
 * {@link OH_AbilityRuntime_GetModObjExtensionInfoByIndex} 按索引遍历获取单个ModularObjectExtensionAbility信息。使用完毕后需通过
 * {@link OH_AbilityRuntime_ReleaseAllExtensionInfos} 释放该集合。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_AllModularObjectExtensionInfos* OH_AbilityRuntime_AllModObjExtensionInfosHandle;

/**
 * @brief 定义ModularObjectExtensionAbility的启动模式。
 *
 * @since 26.0.0
 */
typedef enum OH_AbilityRuntime_LaunchMode {
    /**
     * @brief 表示ModularObjectExtensionAbility将在调用方（客户端）进程中启动。在此模式下，ModularObjectExtensionAbility与调用方共享同一个进程，
     * 适用于对进程隔离无要求的场景。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_LAUNCH_MODE_IN_PROCESS = 0,

    /**
     * @brief 表示ModularObjectExtensionAbility允许跨进程启动。在此模式下，ModularObjectExtensionAbility运行在独立的进程中，与调用方进程隔离，
     * 适用于需要进程级隔离以提高稳定性和安全性的场景。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_LAUNCH_MODE_CROSS_PROCESS = 1,
} OH_AbilityRuntime_LaunchMode;

/**
 * @brief 定义ModularObjectExtensionAbility的进程模式。
 *
 * @since 26.0.0
 */
typedef enum OH_AbilityRuntime_ProcessMode {
    /**
     * @brief 表示同一应用下的所有ModularObjectExtensionAbility实例共享一个进程。所有实例运行在同一进程中，减少系统资源消耗。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_PROCESS_MODE_BUNDLE = 0,

    /**
     * @brief 表示Ability名称相同的ModularObjectExtensionAbility实例共享一个进程。具有相同Ability名称的Extension实例被分配到同一进程中，
     * 不同Ability名称的实例运行在不同进程中。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_PROCESS_MODE_TYPE = 1,

    /**
     * @brief 表示每个ModularObjectExtensionAbility实例独占一个进程。每个Extension实例拥有独立的进程空间，实现最大程度的进程隔离，适用于对稳定性和安全性要求极高的场景。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_PROCESS_MODE_INSTANCE = 2,
} OH_AbilityRuntime_ProcessMode;

/**
 * @brief 定义ModularObjectExtensionAbility的线程模式。
 *
 * @since 26.0.0
 */
typedef enum OH_AbilityRuntime_ThreadMode {
    /**
     * @brief 表示同一应用下的所有ModularObjectExtensionAbility实例共享一个线程。所有实例在同一线程中依次执行，资源开销最小，但需注意避免单实例阻塞影响其他实例。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_THREAD_MODE_BUNDLE = 0,

    /**
     * @brief 表示Ability名称相同的ModularObjectExtensionAbility实例共享一个线程。具有相同类型的Extension实例共享线程，不同类型的实例使用不同线程，在资源消耗与并发性能之间取得平衡。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_THREAD_MODE_TYPE = 1,

    /**
     * @brief 表示每个ModularObjectExtensionAbility实例独占一个线程。每个Extension实例拥有独立的线程，互不干扰，适用于需要高并发或对响应时间有严格要求的场景。
     *
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_THREAD_MODE_INSTANCE = 2,
} OH_AbilityRuntime_ThreadMode;

/**
 * @brief 从指定的ModularObjectExtensionAbility信息中获取启动模式。
 *
 * @param extensionInfo 目标ModularObjectExtensionAbility的信息句柄。
 * @param launchMode 指向{@link OH_AbilityRuntime_LaunchMode}的指针，用于接收启动模式。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} extensionInfo或launchMode为空。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetModularObjectExtensionInfoLaunchMode(
    OH_AbilityRuntime_ModObjExtensionInfoHandle extensionInfo, OH_AbilityRuntime_LaunchMode *launchMode);

/**
 * @brief 从指定的ModularObjectExtensionAbility信息中获取进程模式。
 *
 * @param extensionInfo 目标ModularObjectExtensionAbility的信息句柄。
 * @param processMode 指向{@link OH_AbilityRuntime_ProcessMode}的指针，用于接收进程模式。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} extensionInfo或processMode为空。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetModularObjectExtensionInfoProcessMode(
    OH_AbilityRuntime_ModObjExtensionInfoHandle extensionInfo, OH_AbilityRuntime_ProcessMode *processMode);

/**
 * @brief 从指定的ModularObjectExtensionAbility信息中获取线程模式。
 *
 * @param extensionInfo 目标ModularObjectExtensionAbility的信息句柄。
 * @param threadMode 指向{@link OH_AbilityRuntime_ThreadMode}的指针，用于接收线程模式。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} extensionInfo或threadMode为空。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetModularObjectExtensionInfoThreadMode(
    OH_AbilityRuntime_ModObjExtensionInfoHandle extensionInfo, OH_AbilityRuntime_ThreadMode *threadMode);

/**
 * @brief 从指定的ModularObjectExtensionAbility信息中获取组件名称（{@link AbilityBase_Element}）。
 *
 * @param extensionInfo 目标ModularObjectExtensionAbility的信息句柄。
 * @param element 指向{@link AbilityBase_Element}的指针，用于接收组件名称。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} extensionInfo或element为空。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetModularObjectExtensionInfoElementName(
    OH_AbilityRuntime_ModObjExtensionInfoHandle extensionInfo, AbilityBase_Element *element);

/**
 * @brief 从指定的ModularObjectExtensionAbility信息中获取禁用状态。
 *
 * @param extensionInfo 目标ModularObjectExtensionAbility的信息句柄。
 * @param isDisabled 指向布尔值的指针，用于接收禁用状态。true表示已禁用，不允许其他应用连接；false表示未禁用，允许其他应用连接。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} extensionInfo或isDisabled为空。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetModularObjectExtensionInfoDisableState(
    OH_AbilityRuntime_ModObjExtensionInfoHandle extensionInfo, bool *isDisabled);

/**
 * @brief 获取当前应用所有已注册的ModularObjectExtensionAbility信息。该接口返回一个包含当前应用所有已注册的ModularObjectExtensionAbility信息集合句柄。开发者可通过
 * {@link OH_AbilityRuntime_GetCountFromAllModObjExtensionInfos}和
 * {@link OH_AbilityRuntime_GetModObjExtensionInfoByIndex}遍历集合中的各个ModularObjectExtensionAbility信息，
 * 进而获取每个ModularObjectExtensionAbility的启动模式、进程模式、线程模式等属性。
 *
 * @param outOwnedAllExtensionInfos 指向{@link OH_AbilityRuntime_AllModObjExtensionInfosHandle}的指针，
 *     用于接收ModularObjectExtensionAbility信息集合。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} outOwnedAllExtensionInfos为空。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED} 设备不支持该操作。
 * @release OH_AbilityRuntime_ReleaseAllExtensionInfos {outOwnedAllExtensionInfos}
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_AcquireSelfModularObjectExtensionInfos(
    OH_AbilityRuntime_AllModObjExtensionInfosHandle *outOwnedAllExtensionInfos);

/**
 * @brief 释放由{@link OH_AbilityRuntime_AcquireSelfModularObjectExtensionInfos}获取的ModularObjectExtensionAbility信息集合。
 * 当不再需要使用ModularObjectExtensionAbility信息集合时，必须调用此接口释放相关资源，避免内存泄漏。
 *
 * @param allExtensionInfos 指向需要释放的ModularObjectExtensionAbility信息集合句柄的指针。释放后该指针将被置空。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} allExtensionInfos为空。
 * @see OH_AbilityRuntime_AcquireSelfModularObjectExtensionInfos
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ReleaseAllExtensionInfos(
    OH_AbilityRuntime_AllModObjExtensionInfosHandle *allExtensionInfos);

/**
 * @brief 获取ModularObjectExtensionAbility信息集合中包含的ModularObjectExtensionAbility信息数量。返回的数量可用于确定遍历集合时的索引上限，配合
 * {@link OH_AbilityRuntime_GetModObjExtensionInfoByIndex}逐个访问集合中的ModularObjectExtensionAbility信息。
 *
 * @param allExtensionInfos ModularObjectExtensionAbility信息集合句柄。
 * @param count 指向size_t的指针，用于接收ModularObjectExtensionAbility信息的数量。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} allExtensionInfos或count为空。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetCountFromAllModObjExtensionInfos(
    OH_AbilityRuntime_AllModObjExtensionInfosHandle allExtensionInfos, size_t *count);

/**
 * @brief 根据索引从ModularObjectExtensionAbility信息集合中获取指定的ModularObjectExtensionAbility信息。索引的有效范围为[0, count)，其中count可通过
 * {@link OH_AbilityRuntime_GetCountFromAllModObjExtensionInfos}获取。
 * 获取到的ModularObjectExtensionAbility信息句柄可用于查询该ModularObjectExtensionAbility的启动模式、进程模式、线程模式等属性。
 *
 * @param allExtensionInfos ModularObjectExtensionAbility信息集合句柄。
 * @param index 目标ModularObjectExtensionAbility信息在集合中的索引，必须小于集合包含的ModularObjectExtensionAbility信息数量。
 * @param extensionInfo 指向{@link OH_AbilityRuntime_ModObjExtensionInfoHandle}的指针，
 *     用于接收指定索引处的ModularObjectExtensionAbility信息句柄。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} allExtensionInfos或extensionInfo为空，
 *     <br>或index大于等于集合中ModularObjectExtensionAbility信息数量。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetModObjExtensionInfoByIndex(
    OH_AbilityRuntime_AllModObjExtensionInfosHandle allExtensionInfos, size_t index,
    OH_AbilityRuntime_ModObjExtensionInfoHandle *extensionInfo);

/**
 * @brief 连接ModularObjectExtensionAbility。
 *
 * @param want 连接ModularObjectExtensionAbility需要的Want信息。详细内容参考{@link AbilityBase_Want}。
 * @param connectOptions 连接选项。详细内容参考{@link OH_AbilityRuntime_ConnectOptions}。
 * @param connectionId 指向int64_t的指针，用于接收连接ID。可以在后续调用{@link OH_AbilityRuntime_DisconnectModularObjectExtensionAbility}
 *     时使用。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} 传入参数无效。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED} 设备不支持连接ModularObjectExtensionAbility。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_SUCH_ABILITY} 目标Ability不存在。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE} Ability类型不正确。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_VISIBILITY_VERIFICATION_FAILED} 无法启动不可见组件。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_STATIC_CFG_PERMISSION} 指定进程无相应权限。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_CROSS_USER_OPERATION} 不允许跨用户操作。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_CROWDTEST_EXPIRED} 众测应用已过期。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NOT_TOP_ABILITY} 调用方进程不在前台。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_UPPER_LIMIT_REACHED} 同名Ability的实例数超过20个。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_RUNNING_ABILITIES_WITH_UI} 目标应用无正在运行的UIAbility或UIExtensionAbility。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_UPPER_RATE_LIMIT} API调用频率过高，超过每秒20次。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_UPPER_CONNECTION_NUMBER_LIMIT} 同一进程最多连接5个同名的Ability。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_CROSS_APP_IN_PROCESS} 在{@link OH_ABILITY_RUNTIME_LAUNCH_MODE_IN_PROCESS}
 *     模式下，调用方与目标Ability不在同一应用。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ConnectModularObjectExtensionAbility(AbilityBase_Want *want,
    OH_AbilityRuntime_ConnectOptions *connectOptions, int64_t *connectionId);

/**
 * @brief 断开与ModularObjectExtensionAbility的连接。
 *
 * @param connectionId 表示连接ID。由{@link OH_AbilityRuntime_ConnectModularObjectExtensionAbility}返回。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} 传入参数无效。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_DisconnectModularObjectExtensionAbility(int64_t connectionId);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // ABILITY_RUNTIME_MODULAR_OBJECT_EXTENSION_MANAGER_H

