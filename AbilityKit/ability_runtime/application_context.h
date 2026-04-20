/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
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
 * @brief Describe the functions provided by the application context.
 * @since 13
 */
/**
 * @file application_context.h
 *
 * @brief The file declares the APIs related to the application-level context.
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 13
 */

#ifndef ABILITY_RUNTIME_APPLICATION_CONTEXT_H
#define ABILITY_RUNTIME_APPLICATION_CONTEXT_H

#include <stdint.h>
#include <stddef.h>
#include <AbilityKit/ability_base/want.h>
#include "ability_runtime_common.h"
#include "context_constant.h"
#include "start_options.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Obtains the application-level cache directory of the application.
 *
 * @param buffer Pointer to the buffer, which is used to receive the application-level cache directory of the
 *      application.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes) when
 *      {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**:
 *      The passed-in value of **buffer** or **writeLength** is null, or the
 *      buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 13
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetCacheDir(
    char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the application-level file data encryption level of the application.
 *
 * @param areaMode Pointer to the encryption level of the received data.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 13
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetAreaMode(AbilityRuntime_AreaMode* areaMode);

/**
 * @brief Obtains the bundle name of the application.
 *
 * @param buffer Pointer to the buffer, which is used to receive the bundle name.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes)
 *      when {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 13
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetBundleName(
    char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the application-level temporary file directory of the application.
 *
 * @param buffer Pointer to the buffer, which is used to receive the temporary file directory.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes)
 *      when {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetTempDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the application-level common file directory of the application.
 *
 * @param buffer Pointer to the buffer, which is used to receive the common file directory.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes)
 *      when {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetFilesDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the application-level database file directory of the application.
 *
 * @param buffer Pointer to the buffer, which is used to receive the database file directory.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes)
 *      when {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetDatabaseDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the application-level preferences file directory of the application.
 *
 * @param buffer Pointer to the buffer, which is used to receive the preferences file directory.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes)
 *      when {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetPreferencesDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the application-level installation file directory of the application.
 *
 * @param buffer Pointer to the buffer, which is used to receive the installation file directory.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes)
 *      when {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetBundleCodeDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the application-level distributed file directory of the application.
 *
 * @param buffer Pointer to the buffer, which is used to receive the distributed file directory.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes)
 *      when {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetDistributedFilesDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the application-level cloud file directory of the application.
 *
 * @param buffer Pointer to the buffer, which is used to receive the cloud file directory.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes)
 *      when {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 16
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetCloudFileDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the application-level resource directory of the application.
 *
 * @param moduleName Pointer to the module name.
 * @param buffer Pointer to the buffer, which is used to receive the resource directory.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes)
 *      when {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 20
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetResourceDir(const char* moduleName,
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Starts the UIAbility of the current application.
 *
 * @permission {@code ohos.permission.NDK_START_SELF_UI_ABILITY}
 * @param want Pointer to the Want information required for starting the UIAbility.
 * @return **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PERMISSION_DENIED**: Permission verification for the caller fails.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: Parameter verification for the caller fails.
 *      **ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED**: The device type is not supported.
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_SUCH_ABILITY**: The specified ability name does not exist.
 *      **ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE**: The ability type is incorrect.
 *      **ABILITY_RUNTIME_ERROR_CODE_CROWDTEST_EXPIRED**: The crowdtesting application expires.
 *      **ABILITY_RUNTIME_ERROR_CODE_WUKONG_MODE**: The ability is started or stopped in Wukong mode.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTROLLED**: The application is under control.
 *      **ABILITY_RUNTIME_ERROR_CODE_EDM_CONTROLLED**: The application is under control by EDM.
 *      **ABILITY_RUNTIME_ERROR_CODE_CROSS_APP**: Redirecting to third-party applications
 *      is not allowed in API versions later than 11.
 *      **ABILITY_RUNTIME_ERROR_CODE_INTERNAL**: An internal error occurs.
 *      **ABILITY_RUNTIME_ERROR_CODE_NOT_TOP_ABILITY**: The application is not a top one.
 *      **ABILITY_RUNTIME_ERROR_CODE_UPPER_LIMIT_REACHED** (available since API version 17):
 *      The number of instances has reached the upper limit.
 *      **ABILITY_RUNTIME_ERROR_CODE_APP_INSTANCE_KEY_NOT_SUPPORTED** (available since API version 17): Setting **
 *      APP_INSTANCE_KEY** is not supported.
 *      For details, see **AbilityRuntime_ErrorCode**.
 * @since 15
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_StartSelfUIAbility(AbilityBase_Want *want);

/**
 * @brief Starts the UIAbility of the current application using **StartOptions**.
 *
 * @permission {@code ohos.permission.NDK_START_SELF_UI_ABILITY}
 * @param want Pointer to the Want information required for starting the UIAbility.
 * @param options Pointer to **StartOptions** required for starting the UIAbility.
 *      If the value of {@link startVisibility}
 *      is not null, ensure that the current application has been added to the status bar.
 *      Otherwise, the {@link ABILITY_RUNTIME_ERROR_VISIBILITY_SETTING_DISABLED} error code is returned.
 * @return **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PERMISSION_DENIED**: Permission verification for the caller fails.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: Parameter verification for the caller fails.
 *      **ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED**: The device type is not supported.
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_SUCH_ABILITY**: The specified ability name does not exist.
 *      **ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE**: The ability type is incorrect.
 *      **ABILITY_RUNTIME_ERROR_CODE_CROWDTEST_EXPIRED**: The crowdtesting application expires.
 *      **ABILITY_RUNTIME_ERROR_CODE_WUKONG_MODE**: The ability is started or stopped in Wukong mode.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTROLLED**: The application is under control.
 *      **ABILITY_RUNTIME_ERROR_CODE_EDM_CONTROLLED**: The application is under control by EDM.
 *      **ABILITY_RUNTIME_ERROR_CODE_CROSS_APP**: Redirecting to third-party applications
 *      is not allowed in API versions later than 11.
 *      **ABILITY_RUNTIME_ERROR_CODE_INTERNAL**: An internal error occurs.
 *      **ABILITY_RUNTIME_ERROR_CODE_NOT_TOP_ABILITY**: The application is not a top one.
 *      **ABILITY_RUNTIME_ERROR_VISIBILITY_SETTING_DISABLED**:
 *      Setting the window visibility during startup is not allowed.
 *      **ABILITY_RUNTIME_ERROR_CODE_MULTI_APP_NOT_SUPPORTED**:
 *      The application does not support clone or multi-instance mode.
 *      **ABILITY_RUNTIME_ERROR_CODE_INVALID_APP_INSTANCE_KEY**: The multi-instance key is invalid.
 *      **ABILITY_RUNTIME_ERROR_CODE_UPPER_LIMIT_REACHED**: The number of instances has reached the upper limit.
 *      **ABILITY_RUNTIME_ERROR_MULTI_INSTANCE_NOT_SUPPORTED**: The application does not support multi-instance mode.
 *      **ABILITY_RUNTIME_ERROR_CODE_APP_INSTANCE_KEY_NOT_SUPPORTED**: Setting **APP_INSTANCE_KEY** is not supported.
 *      For details, see **AbilityRuntime_ErrorCode**.
 * @since 17
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_StartSelfUIAbilityWithStartOptions(AbilityBase_Want *want,
    AbilityRuntime_StartOptions *options);

/**
 * @brief Obtains the application version code.
 *
 * @param versionCode The version code of the application.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: **versionCode** is null.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 *      **ABILITY_RUNTIME_ERROR_CODE_GET_APPLICATION_INFO_FAILED**: Failed to obtain the application information.
 * @since 21
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetVersionCode(int64_t* versionCode);

/**
 * @brief Obtains **WantParams** passed for the initial launch of the UIAbility of the current application. For details
 * about **WantParams**, see {@link parameters in Want}.
 *
 * @param buffer Pointer to the buffer, which is used to receive **WantParams**.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes)
 *      when {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 21
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetLaunchParameter(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains **WantParams** passed for the mose recent launch of the UIAbility of the current application. For
 * details about **WantParams**, see {@link parameters in Want}.
 *
 * @param buffer Pointer to the buffer, which is used to receive **WantParams**.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes)
 *      when {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 21
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetLatestParameter(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Starts the UIAbility of the current application using **StartOptions** and obtains the process ID of the
 * target UIAbility.
 *
 * @permission ohos.permission.NDK_START_SELF_UI_ABILITY
 * @param want Pointer to the Want information required for starting the UIAbility.
 * @param options Pointer to **StartOptions** required for starting the UIAbility.
 *      If the value of {@link startVisibility} is not null, ensure that the current application has been added
 *      to the status bar. Otherwise, the {@link ABILITY_RUNTIME_ERROR_VISIBILITY_SETTING_DISABLED}
 *      error code is returned.
 * @param targetPid Pointer to the process ID of the target UIAbility.
 * @return **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PERMISSION_DENIED**: Permission verification for the caller fails.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: Parameter verification for the caller fails.
 *      **ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED**: The device type is not supported.
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_SUCH_ABILITY**: The specified ability name does not exist.
 *      **ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE**: The ability type is incorrect.
 *      **ABILITY_RUNTIME_ERROR_CODE_CROWDTEST_EXPIRED**: The crowdtesting application expires.
 *      **ABILITY_RUNTIME_ERROR_CODE_WUKONG_MODE**: The ability is started or stopped in Wukong mode.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTROLLED**: The application is under control.
 *      **ABILITY_RUNTIME_ERROR_CODE_EDM_CONTROLLED**: The application is under control by EDM.
 *      **ABILITY_RUNTIME_ERROR_CODE_CROSS_APP**: Redirecting to third-party applications
 *      is not allowed in API versions later than 11.
 *      **ABILITY_RUNTIME_ERROR_CODE_INTERNAL**: An internal error occurs.
 *      **ABILITY_RUNTIME_ERROR_CODE_NOT_TOP_ABILITY**: The application is not a top one.
 *      **ABILITY_RUNTIME_ERROR_VISIBILITY_SETTING_DISABLED**:
 *      Setting the window visibility during startup is not allowed.
 *      **ABILITY_RUNTIME_ERROR_CODE_MULTI_APP_NOT_SUPPORTED**:
 *      The application does not support clone or multi-instance mode.
 *      **ABILITY_RUNTIME_ERROR_CODE_INVALID_APP_INSTANCE_KEY**: The multi-instance key is invalid.
 *      **ABILITY_RUNTIME_ERROR_CODE_UPPER_LIMIT_REACHED**: The number of instances has reached the upper limit.
 *      **ABILITY_RUNTIME_ERROR_MULTI_INSTANCE_NOT_SUPPORTED**: The application does not support multi-instance mode.
 *      **ABILITY_RUNTIME_ERROR_CODE_APP_INSTANCE_KEY_NOT_SUPPORTED**: Setting **APP_INSTANCE_KEY** is not supported.
 *      **ABILITY_RUNTIME_ERROR_CODE_START_TIMEOUT**: Starting the UIAbility times out.
 *      **ABILITY_RUNTIME_ERROR_CODE_MAIN_THREAD_NOT_SUPPORTED**:
 *      The function cannot be called on the main thread of the application.
 * @since 21
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_StartSelfUIAbilityWithPidResult(AbilityBase_Want *want,
    AbilityRuntime_StartOptions *options, int32_t *targetPid);

/**
 * @brief Obtains the application-level log file directory of the application.
 *
 * @param buffer Pointer to the buffer, which is used to receive the log file directory.
 * @param bufferSize Buffer size, in bytes.
 * @param writeLength Pointer to the length of the string written to the buffer (measured in bytes)
 *      when {@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} is returned.
 * @return One of the following execution results:
 *      **ABILITY_RUNTIME_ERROR_CODE_NO_ERROR**: The operation is successful.
 *      **ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID**: The passed-in value of **buffer** or **writeLength** is null,
 *      or the buffer size is less than the size of the string to be written.
 *      **ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST**: The application context does not exist. For example, the
 *      application-level context does not exist in the {@link child process} created by the application.
 * @since 22
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextGetLogFileDir(
    char* buffer, const int32_t bufferSize, int32_t* writeLength);

/**
 * @brief This API can be called only from third-party frameworks. Each time a third-party framework switches pages, it
 * notifies the system of the target page information (including the target page path, the length of the target page
 * path, and the window ID corresponding to the target page). The system can adjust or recover the page according to
 * product policies.
 *
 * @param targetPageName Target page path.
 * @param targetPageNameLength Length of the target page path.
 * @param windowId {@link Window ID} corresponding to the target page.
 * @return One of the following execution results:
 *      ABILITY_RUNTIME_ERROR_CODE_NO_ERROR: The operation is successful.
 *      ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID:
 *      The input parameter **targetPageName** is empty orthe windowId is invalid.
 *      **ABILITY_RUNTIME_ERROR_CODE_INTERNAL**: An internal error occurs.
 * @since 23
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ApplicationContextNotifyPageChanged(
    const char* targetPageName, int32_t targetPageNameLength, int32_t windowId);

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
#endif // ABILITY_RUNTIME_APPLICATION_CONTEXT_H
