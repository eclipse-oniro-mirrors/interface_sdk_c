/*
* Copyright (C) 2024-2025 Huawei Device Co., Ltd.
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
 * @brief Provide the definition of the C interface for the native AbilityRuntime
 * @since 13
 */
/**
 * @file ability_runtime_common.h
 *
 * @brief The file declares the error codes of the AbilityRuntime module.
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 13
 */

#ifndef ABILITY_RUNTIME_COMMON_H
#define ABILITY_RUNTIME_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the error codes of the AbilityRuntime module.
 *
 * @since 13
 */
typedef enum {
    /**
     * Operation successful.
     *
     * @since 13
     */
    ABILITY_RUNTIME_ERROR_CODE_NO_ERROR = 0,
    /**
     * Permission verification fails.
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_PERMISSION_DENIED = 201,
    /**
     * Invalid parameter.
     *
     * @since 13
     */
    ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID = 401,
    /**
     * The device type is not supported.
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED = 801,
    /**
     * The specified ability name does not exist.
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_NO_SUCH_ABILITY = 16000001,
    /**
     * The ability type is incorrect.
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE = 16000002,
    /**
     * The crowdtesting application expires.
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_CROWDTEST_EXPIRED = 16000008,
    /**
     * An ability cannot be started or stopped in Wukong mode.
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_WUKONG_MODE = 16000009,
    /**
     * The context does not exist.
     *
     * @since 13
     */
    ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST = 16000011,
    /**
     * The application is under control.
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_CONTROLLED = 16000012,
    /**
     * The application is under control by EDM.
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_EDM_CONTROLLED = 16000013,
    /**
     * Redirection to third-party applications is not allowed in API versions later than 11.
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_CROSS_APP = 16000018,
    /**
     * Internal server error.
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_INTERNAL = 16000050,
    /**
     * The application is not on top.
     *
     * @since 15
     */
    ABILITY_RUNTIME_ERROR_CODE_NOT_TOP_ABILITY = 16000053,
    /**
     * Setting the window visibility during startup is not allowed.
     *
     * @since 17
     */
    ABILITY_RUNTIME_ERROR_VISIBILITY_SETTING_DISABLED = 16000067,
    /**
     * The application does not support clone or multi-instance mode.
     *
     * @since 17
     */
    ABILITY_RUNTIME_ERROR_CODE_MULTI_APP_NOT_SUPPORTED = 16000072,
    /**
     * The multi-instance key is invalid.
     *
     * @since 17
     */
    ABILITY_RUNTIME_ERROR_CODE_INVALID_APP_INSTANCE_KEY = 16000076,
    /**
     * The number of instances has reached the upper limit.
     *
     * @since 17
     */
    ABILITY_RUNTIME_ERROR_CODE_UPPER_LIMIT_REACHED = 16000077,
    /**
     * The application does not support multi-instance mode.
     *
     * @since 17
     */
    ABILITY_RUNTIME_ERROR_MULTI_INSTANCE_NOT_SUPPORTED = 16000078,
    /**
     * Setting **APP_INSTANCE_KEY** is not supported.
     *
     * @since 17
     */
    ABILITY_RUNTIME_ERROR_CODE_APP_INSTANCE_KEY_NOT_SUPPORTED = 16000079,
    /**
     * Failed to obtain the application information.
     *
     * @since 21
     */
    ABILITY_RUNTIME_ERROR_CODE_GET_APPLICATION_INFO_FAILED = 16000081,
    /**
     * Starting the UIAbility times out.
     *
     * @since 21
     */
    ABILITY_RUNTIME_ERROR_CODE_START_TIMEOUT = 16000133,
    /**
     * The function cannot be called on the main thread of the application.
     *
     * @since 21
     */
    ABILITY_RUNTIME_ERROR_CODE_MAIN_THREAD_NOT_SUPPORTED = 16000134,
} AbilityRuntime_ErrorCode;

#ifdef __cplusplus
}
#endif

/** @} */
#endif // ABILITY_RUNTIME_COMMON_H
