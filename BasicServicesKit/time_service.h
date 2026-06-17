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

#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H

/**
 * @addtogroup TimeService
 * @{
 *
 * @brief Declares the time zone capabilities provided by TimeService to an application.
 * @since 12
 */
/**
 * @file time_service.h
 *
 * @brief Declares the APIs for obtaining the time zone information.
 * @library libtime_service_ndk.so
 * @kit BasicServicesKit
 * @syscap SystemCapability.MiscServices.Time
 * @since 12
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the error codes.
 *
 * @since 12
 */
typedef enum TimeService_ErrCode {
    /**
     * Operation successful.
     */
    TIMESERVICE_ERR_OK = 0,

    /**
     * Failed to obtain system parameters.
     */
    TIMESERVICE_ERR_INTERNAL_ERROR = 13000001,

    /**
     * Invalid parameter.
     */
    TIMESERVICE_ERR_INVALID_PARAMETER = 13000002,
} TimeService_ErrCode;

/**
 * @brief Obtains the current system time zone.
 *
 * @param timeZone Pointer to the buffer for one time zone ID string. If the time zone is obtained, its ID is written.
 *     Otherwise, an empty string is written. The string ends with **\0**.
 * @param len Capacity of the buffer pointed to by **timeZone**, in bytes, including the end character **\0**.
 *     There is no maximum limit. You are advised to allocate at least 31 bytes.
 * @return Returns **TIMESERVICE_ERR_OK** if the operation is successful;
 *     <br>returns **TIMESERVICE_ERR_INTERNAL_ERROR** if the system parameters fail to be obtained;
 *     <br>returns **TIMESERVICE_ERR_INVALID_PARAMETER** if **timeZone** is a null pointer or the length of the time
 *     zone name (excluding the end character **\0**) is greater than or equal to the value of **len**.
 * @syscap SystemCapability.MiscServices.Time
 * @since 12
 */
TimeService_ErrCode OH_TimeService_GetTimeZone(char *timeZone, uint32_t len);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* TIME_SERVICE_H */