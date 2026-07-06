/*
* Copyright (C) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup AbilityBase
 * @{
 *
 * @brief Provide the definition of the C interface for the native AbilityBase
 * @since 15
 */
/**
 * @file ability_base_common.h
 *
 * @brief The file declares the error codes defined by AbilityBase.
 *
 * @library libability_base_want.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityBase
 * @since 15
 */

#ifndef ABILITY_BASE_COMMON_H
#define ABILITY_BASE_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the error codes of AbilityBase.
 *
 * @since 15
 */
typedef enum {
    /**
     * Operation successful.
     *
     * @since 15
     */
    ABILITY_BASE_ERROR_CODE_NO_ERROR = 0,
    /**
     * Invalid parameter.
     *
     * @since 15
     */
    ABILITY_BASE_ERROR_CODE_PARAM_INVALID = 401,
} AbilityBase_ErrorCode;

#ifdef __cplusplus
}
#endif

/** @} */
#endif // ABILITY_BASE_COMMON_H
