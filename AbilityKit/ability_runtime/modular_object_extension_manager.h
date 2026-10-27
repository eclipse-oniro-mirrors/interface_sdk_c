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
 * @brief Provides the definition of the C interface for the modular object extension manager.
 *
 * @since 26.0.0
 */

/**
 * @file modular_object_extension_manager.h
 *
 * @brief Declares the APIs for managing ModularObjectExtensionAbility, including querying
 * ModularObjectExtensionAbility information, connecting to and disconnecting from it.
 * Developers can use the APIs provided by this module to query the information of all
 * registered ModularObjectExtensionAbility instances in the current app (including the startup mode,
 * process mode, thread mode, component name, and disabled state), and establish or disconnect the communication
 * connection with ModularObjectExtensionAbility as needed.
 *
 * **File to include:** <AbilityKit/ability_runtime/modular_object_extension_manager.h>
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
 * @brief Represents the information handle of a single ModularObjectExtensionAbility. The handle points
 * to the complete information of a ModularObjectExtensionAbility, including attributes such as
 * the launch mode, process mode, thread mode, component name (AbilityBase_Element), and disabled state.
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ModularObjectExtensionInfo* OH_AbilityRuntime_ModObjExtensionInfoHandle;

/**
 * @brief Represents a handle to the collection of all ModularObjectExtensionAbility information in the current app.
 * You can obtain this handle through {@link OH_AbilityRuntime_AcquireSelfModularObjectExtensionInfos}.
 * This handle points to a collection containing multiple {@link OH_AbilityRuntime_ModObjExtensionInfoHandle}
 * objects. You can obtain the number of elements in the collection through
 * {@link OH_AbilityRuntime_GetCountFromAllModObjExtensionInfos}, and obtain the
 * information of a single ModularObjectExtensionAbility by index through
 * {@link OH_AbilityRuntime_GetModObjExtensionInfoByIndex}. After use, release the collection through
 * {@link OH_AbilityRuntime_ReleaseAllExtensionInfos}.
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_AllModularObjectExtensionInfos* OH_AbilityRuntime_AllModObjExtensionInfosHandle;

/**
 * @brief Defines the launch mode of a ModularObjectExtensionAbility.
 * @since 26.0.0
 */
typedef enum OH_AbilityRuntime_LaunchMode {
    /**
     * @brief All extensions under the same bundle share a single process.
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_LAUNCH_MODE_IN_PROCESS = 0,

    /**
     * @brief Allow modular object extension abilities to be started across processes.
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_LAUNCH_MODE_CROSS_PROCESS = 1,
} OH_AbilityRuntime_LaunchMode;

/**
 * @brief Defines the process mode of a ModularObjectExtensionAbility.
 * @since 26.0.0
 */
typedef enum OH_AbilityRuntime_ProcessMode {
    /**
     * @brief All modular object extensions under the same bundle share a single process.
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_PROCESS_MODE_BUNDLE = 0,

    /**
     * @brief Modular object extensions with the same name share a single process.
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_PROCESS_MODE_TYPE = 1,

    /**
     * @brief Each modular object extension instance is a process.
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_PROCESS_MODE_INSTANCE = 2,
} OH_AbilityRuntime_ProcessMode;

/**
 * @brief Defines the thread mode of a ModularObjectExtensionAbility.
 * @since 26.0.0
 */
typedef enum OH_AbilityRuntime_ThreadMode {
    /**
     * @brief All modular object extensions under the same bundle share a single thread.
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_THREAD_MODE_BUNDLE = 0,

    /**
     * @brief Modular object extensions with the same name share a single thread.
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_THREAD_MODE_TYPE = 1,

    /**
     * @brief Each modular object extension instance is a thread.
     * @since 26.0.0
     */
    OH_ABILITY_RUNTIME_THREAD_MODE_INSTANCE = 2,
} OH_AbilityRuntime_ThreadMode;

/**
 * @brief Obtains the startup mode from the specified ModularObjectExtensionAbility information.
 *
 * @param extensionInfo The modular object extension info from which to get the launch mode.
 * @param launchMode The launch mode obtained from the extension info.
 * @return Returns a specific error code.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} if the arguments provided are invalid.
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetModularObjectExtensionInfoLaunchMode(
    OH_AbilityRuntime_ModObjExtensionInfoHandle extensionInfo, OH_AbilityRuntime_LaunchMode *launchMode);

/**
 * @brief Obtains the process mode from the specified ModularObjectExtensionAbility information.
 *
 * @param extensionInfo The modular object extension info to get the process mode from.
 * @param processMode The process mode obtained from the extension info.
 * @return Returns a specific error code.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} if the arguments provided are invalid.
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetModularObjectExtensionInfoProcessMode(
    OH_AbilityRuntime_ModObjExtensionInfoHandle extensionInfo, OH_AbilityRuntime_ProcessMode *processMode);

/**
 * @brief Obtains the thread mode from the specified ModularObjectExtensionAbility information.
 *
 * @param extensionInfo The modular object extension info to get the thread mode from.
 * @param threadMode The thread mode obtained from the extension info.
 * @return Returns a specific error code.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} if the arguments provided are invalid.
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetModularObjectExtensionInfoThreadMode(
    OH_AbilityRuntime_ModObjExtensionInfoHandle extensionInfo, OH_AbilityRuntime_ThreadMode *threadMode);

/**
 * @brief Gets the component name (AbilityBase_Element) from the specified ModularObjectExtensionAbility information.
 * The bundleName, moduleName, and abilityName in element are non-owning pointers that point to the internal data of
 * extensionInfo. Do not release them separately. They are available only while extensionInfo is valid.
 *
 * @param extensionInfo The modular object extension info to get the element name from.
 * @param element The element name obtained from the extension info.
 * @return Returns a specific error code.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} if the arguments provided are invalid.
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetModularObjectExtensionInfoElementName(
    OH_AbilityRuntime_ModObjExtensionInfoHandle extensionInfo, AbilityBase_Element *element);

/**
 * @brief Obtains the disabled state from the specified ModularObjectExtensionAbility information.
 *
 * @param extensionInfo The modular object extension info.
 * @param isDisabled Whether the extension is disabled.
 * @return Returns a specific error code.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} if the arguments provided are invalid.
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetModularObjectExtensionInfoDisableState(
    OH_AbilityRuntime_ModObjExtensionInfoHandle extensionInfo, bool *isDisabled);

/**
 * @brief Gets the information about all registered ModularObjectExtensionAbility instances of the current
 * application and returns a handle to the ModularObjectExtensionAbility information set.
 * Use {@link OH_AbilityRuntime_GetCountFromAllModObjExtensionInfos} to obtain the information count of the set,
 * and use {@link OH_AbilityRuntime_GetModObjExtensionInfoByIndex} to traverse each ModularObjectExtensionAbility
 * information by index to obtain attributes such as the launch mode, process mode, and thread mode. After use,
 * call {@link OH_AbilityRuntime_ReleaseAllExtensionInfos} to release the handle to avoid memory leaks.
 *
 * @param outOwnedAllExtensionInfos Information about all extensions within the self application.
 * @return Returns a specific error code.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} if the arguments provided are invalid.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED} if the device does not support.
 * @release OH_AbilityRuntime_ReleaseAllExtensionInfos {outOwnedAllExtensionInfos}
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_AcquireSelfModularObjectExtensionInfos(
    OH_AbilityRuntime_AllModObjExtensionInfosHandle *outOwnedAllExtensionInfos);

/**
 * @brief Releases the ModularObjectExtensionAbility information collection obtained by
 * {@link OH_AbilityRuntime_AcquireSelfModularObjectExtensionInfos}. When the ModularObjectExtensionAbility
 * information collection is no longer needed, you must call this API to release the related resources to
 * avoid memory leaks.
 *
 * @param allExtensionInfos The all modular object extension infos to be released.
 * @return Returns a specific error code.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} if the arguments provided are invalid.
 * @see OH_AbilityRuntime_AcquireSelfModularObjectExtensionInfos
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ReleaseAllExtensionInfos(
    OH_AbilityRuntime_AllModObjExtensionInfosHandle *allExtensionInfos);

/**
 * @brief Obtains the number of ModularObjectExtensionAbility information items contained in the
 * ModularObjectExtensionAbility information collection. The returned count can be used to determine the upper
 * limit of the index when traversing the collection, and works with
 * {@link OH_AbilityRuntime_GetModObjExtensionInfoByIndex} to access each ModularObjectExtensionAbility information
 * item in the collection.
 *
 * @param allExtensionInfos The handle representing the collection of all modular object extension infos.
 * @param count Return value to receive the count of extensions in the collection.
 * @return Returns a specific error code.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} if the arguments provided are invalid.
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetCountFromAllModObjExtensionInfos(
    OH_AbilityRuntime_AllModObjExtensionInfosHandle allExtensionInfos, size_t *count);

/**
 * @brief Obtains the specified ModularObjectExtensionAbility information from the ModularObjectExtensionAbility
 * information collection by index. The valid index range is [0, count), where count can be obtained through
 * {@link OH_AbilityRuntime_GetCountFromAllModObjExtensionInfos}. The obtained ModularObjectExtensionAbility
 * information handle can be used to query the startup mode, process mode, thread mode, and other attributes
 * of the ModularObjectExtensionAbility. The returned extensionInfo is a non-owning handle that points to the
 * internal storage of the allExtensionInfos collection. Do not release it separately. It is available only while
 * allExtensionInfos is valid.
 *
 * @param allExtensionInfos Information about all extensions within the self application.
 * @param index The index of the extension to retrieve. Must be strictly less than the count.
 * @param extensionInfo The retrieved single modular object extension info handle for the specified index.
 * @return Returns a specific error code.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} if the operation is successful.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} if the arguments provided are invalid.
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetModObjExtensionInfoByIndex(
    OH_AbilityRuntime_AllModObjExtensionInfosHandle allExtensionInfos, size_t index,
    OH_AbilityRuntime_ModObjExtensionInfoHandle *extensionInfo);

/**
 * @brief Connects to a ModularObjectExtensionAbility.
 *
 * @param want Indicates the modular object extension ability to connect.
 * For details, see {@link AbilityBase_Want}.
 * @param connectOptions Indicates the connection options.
 * @param connectionId Indicates the connection id that is a output param.
 * @return <ul>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} if the call is successful.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} if the arguments provided are invalid.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED} if the device does not support connecting modular
 *      object extension ability.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_NO_SUCH_ABILITY} if the target ability does not exist.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE} if the ability type is incorrect.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_VISIBILITY_VERIFICATION_FAILED} - Cannot start an invisible
 *      component.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_STATIC_CFG_PERMISSION} The specified process does not have
 *      the permission.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_CROSS_USER_OPERATION} Cross-user operations are not allowed.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_CROWDTEST_EXPIRED} if the crowdtesting application expires.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} if an internal error occurs.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_NOT_TOP_ABILITY} if the caller is not a foreground process.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_UPPER_LIMIT_REACHED} The number of instances with the same
 *      ability name is more than twenty.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_NO_RUNNING_ABILITIES_WITH_UI} if the target application does not have
 *      running abilities with UI.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_UPPER_RATE_LIMIT} The API call frequency is too high and
 *      exceeds 20 times per second.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_UPPER_CONNECTION_NUMBER_LIMIT} The number of connections to
 *      the same ability name from the same pid exceeds five.</li>
 *      <li>{@link ABILITY_RUNTIME_ERROR_CODE_CROSS_APP_IN_PROCESS} Caller and target are not in the
 *      same application for {@link OH_ABILITY_RUNTIME_LAUNCH_MODE_IN_PROCESS} mode.</li>
 *      </ul>
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ConnectModularObjectExtensionAbility(AbilityBase_Want *want,
    OH_AbilityRuntime_ConnectOptions *connectOptions, int64_t *connectionId);

/**
 * @brief Disconnects from the ModularObjectExtensionAbility.
 *
 * @param connectionId Indicates the connection ID.
 * @return Returns a specific error code.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} if the call is successful.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} if the arguments provided are invalid.
 *          {@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} if an internal error occurs.
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_DisconnectModularObjectExtensionAbility(int64_t connectionId);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // ABILITY_RUNTIME_MODULAR_OBJECT_EXTENSION_MANAGER_H
