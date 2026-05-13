/*
 * Copyright (C) 2024-2026 Huawei Device Co., Ltd.
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
 * @addtogroup OsAccount
 * @{
 *
 * @brief Provide the definition of the C interface for the native OsAccount.
 * @since 12
 */

/**
 * @file os_account_common.h
 *
 * @brief 提供OsAccount接口的公共类型定义
 *
 * @library libos_account_ndk.so
 * @kit BasicServicesKit
 * @syscap SystemCapability.Account.OsAccount
 * @since 12
 */
#ifndef OS_ACCOUNT_COMMON_H
#define OS_ACCOUNT_COMMON_H
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 枚举错误码。
 *
 * @since 12
 */
typedef enum OsAccount_ErrCode {
    /**
     * 成功。
     */
    OS_ACCOUNT_ERR_OK = 0,

    /**
     * 没有权限。<br>**起始版本：** 26.0.0
     */
    OS_ACCOUNT_ERR_PERMISSION_DENIED = 201,

    /**
     * 内部错误。
     */
    OS_ACCOUNT_ERR_INTERNAL_ERROR = 12300001,

    /**
     * 无效的参数。
     */
    OS_ACCOUNT_ERR_INVALID_PARAMETER = 12300002,

    /**
     * 账号不存在。<br>**起始版本：** 26.0.0
     */
    OS_ACCOUNT_ERR_ACCOUNT_NOT_FOUND = 12300003,

    /**
     * 受限账号。<br>**起始版本：** 26.0.0
     */
    OS_ACCOUNT_ERR_RESTRICTED_ACCOUNT = 12300008
} OsAccount_ErrCode;
#ifdef __cplusplus
}
#endif

/** @} */
#endif // OS_ACCOUNT_COMMON_H