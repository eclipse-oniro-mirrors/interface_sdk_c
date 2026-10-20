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
 * @brief 描述TimeService向应用提供时间时区能力。
 * 典型使用场景：应用获取当前系统时区ID，用于时间相关的业务处理。
 * @since 12
 */
/**
 * @file time_service.h
 *
 * @brief 声明获取时间时区信息的API。
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
     * 获取系统参数失败。请稍后重试，若问题持续存在请检查系统服务状态。
     */
    TIMESERVICE_ERR_INTERNAL_ERROR = 13000001,

    /**
     * 无效的参数。请检查timeZone是否为NULL指针，或时区名称（不包括结束字符（'\0'））的大小是否大于或等于len。
     */
    TIMESERVICE_ERR_INVALID_PARAMETER = 13000002,
} TimeService_ErrCode;

/**
 * @brief 获取当前系统时区。
 *
 * @param timeZone 时区ID字符数组，成功时写入当前系统时区ID字符串，当timeZone不为NULL且操作失败时写入空字符串，字符串以'\0'结尾。
 * @param len 时区ID字符数组分配的内存大小，当前时区字符串没有最大长度规格，建议申请足够多的内存，至少不能低于31字节。
 * 当len小于或等于实际时区字符串长度（不含结束符）时，返回TIMESERVICE_ERR_INVALID_PARAMETER。
 * @return 返回`TIMESERVICE_ERR_OK`表示成功。
 *     <br>返回`TIMESERVICE_ERR_INTERNAL_ERROR`表示获取系统参数失败。请稍后重试，若问题持续存在请检查系统服务状态。
 *     <br>返回`TIMESERVICE_ERR_INVALID_PARAMETER`表示timeZone为NULL指针或时区名称（不包括结束字符（'\0'））的大小大于或等于len。
 *     请确保timeZone为有效指针且len大于时区ID的实际长度。
 * @syscap SystemCapability.MiscServices.Time
 * @since 12
 */
TimeService_ErrCode OH_TimeService_GetTimeZone(char *timeZone, uint32_t len);

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* TIME_SERVICE_H */