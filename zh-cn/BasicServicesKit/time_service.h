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
 * @brief 枚举错误码。
 *
 * @since 12
 */
typedef enum TimeService_ErrCode {
    /**
     * 成功。
     */
    TIMESERVICE_ERR_OK = 0,

    /**
     * 获取系统参数失败。
     */
    TIMESERVICE_ERR_INTERNAL_ERROR = 13000001,

    /**
     * 无效的参数。
     */
    TIMESERVICE_ERR_INVALID_PARAMETER = 13000002,
} TimeService_ErrCode;

/**
 * @brief 获取当前系统时区。
 *
 * @param timeZone 用于写入一个时区ID字符串的缓冲区，成功时写入当前系统时区ID字符串，失败时写入空字符串，字符串以'\0'结尾。
 * @param len 参数timeZone所指向缓冲区的容量，单位为字节，包含结束字符'\0'。当前时区字符串没有最大长度规格，建议分配至少31字节。
 * @return 返回`TIMESERVICE_ERR_OK`表示成功。
 *     <br>返回`TIMESERVICE_ERR_INTERNAL_ERROR`表示获取系统参数失败。
 *     <br>返回`TIMESERVICE_ERR_INVALID_PARAMETER`表示timeZone为NULL指针或时区名称（不包括结束字符（'\0'））的大小大于或等于len。
 * @syscap SystemCapability.MiscServices.Time
 * @since 12
 */
TimeService_ErrCode OH_TimeService_GetTimeZone(char *timeZone, uint32_t len);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* TIME_SERVICE_H */