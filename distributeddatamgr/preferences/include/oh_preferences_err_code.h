/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup PREFERENCES
 * @{
 *
 * @brief Provides APIs for processing data in the form of key-value (KV) pairs.
 * You can use the APIs provided by the Preferences module to query, modify, and persist KV pairs.
 * The key is of the string type, and the value can be a number, a string, a boolean value.
 *
 * @since 13
 */

/**
 * @file preferences_err_code.h
 *
 * @brief Defines the status codes used in the Preferences module.
 *
 * @kit ArkData
 * @library libohpreferences.so
 * @syscap SystemCapability.DistributedDataManager.Preferences.Core
 *
 * @since 13
 */


#ifndef OH_PREFERENCES_ERR_CODE_H
#define OH_PREFERENCES_ERR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the status codes.
 *
 * @since 13
 */
typedef enum OH_Preferences_ErrCode {
    /** @error Operation successful. */
    PREFERENCES_OK = 0,
    /* @error Invalid args. */
    PREFERENCES_E_INVALID_PARAM = 401,
    /* @error Capability not supported. */
    PREFERENCES_NOT_SUPPORTED = 801,
    /* @error Base error code. */
    PREFERENCES_BASE = 15500000,
    /* @error Inner error. */
    PREFERENCES_E_INNER_ERROR = PREFERENCES_BASE,
    /* @error Failed to delete a file. */
    PREFERENCES_DELETE_FILE_FAIL = (PREFERENCES_BASE + 10),
    /* @error Failed to get DataObsMgrClient. */
    PREFERENCES_GET_DATAOBSMGRCLIENT_FAIL = (PREFERENCES_BASE + 19),
} OH_Preferences_ErrCode;

#ifdef __cplusplus
};
#endif

#endif // OH_PREFERENCES_ERR_CODE_H
