/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @file os_account.h
 *
 * @brief Defines the APIs for accessing and managing OS account information.
 *
 * @library libos_account_ndk.so
 * @kit BasicServicesKit
 * @syscap SystemCapability.Account.OsAccount
 * @since 12
 */
#ifndef OS_ACCOUNT_H
#define OS_ACCOUNT_H

#include <stddef.h>
#include <stdint.h>
#include "os_account_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Obtains the name of the OS account, to which the caller process belongs.
 *
 * @param buffer Character array of the OS account name, which must contain the OS account name
 *     and the null terminator ('\0'). The maximum length is defined by **LOGIN_NAME_MAX**.
 * @param buffer_size Size of the OS account name's character array.
 * @return <ul>
 *         <li>{@link OS_ACCOUNT_ERR_OK} The operation is successful.</li>
 *         <li>{@link OS_ACCOUNT_ERR_INTERNAL_ERROR} An internal error occurs.</li>
 *         <li>{@link OS_ACCOUNT_ERR_INVALID_PARAMETER} The buffer is a null pointer or the size of the OS account
 *         name's character array (including **\0**) is greater than the value of **buffer_size**.</li>
 *         </ul>
 * @since 12
 */
OsAccount_ErrCode OH_OsAccount_GetName(char *buffer, size_t buffer_size);

/**
 * @brief Obtains the name of the target OS account based on its local ID.
 *
 * @permission ohos.permission.GET_LOCAL_ACCOUNT_IDENTIFIERS
 * @param localId Local ID of the target OS account.
 * @param name Character array of the OS account name, which must contain the OS account name
 *     and the null terminator ('\0'). The maximum length is defined by **LOGIN_NAME_MAX**.
 * @param name_size Size of the OS account name's character array.
 * @return <ul>
 *         <li>{@link OS_ACCOUNT_ERR_OK} The operation is successful.</li>
 *         <li>{@link OS_ACCOUNT_ERR_PERMISSION_DENIED} Permission is denied.</li>
 *         <li>{@link OS_ACCOUNT_ERR_INTERNAL_ERROR} An internal error occurs.</li>
 *         <li>{@link OS_ACCOUNT_ERR_INVALID_PARAMETER} The name is a null pointer or the size of the OS account
 *         name's character array (including **\0**) is greater than the value of **name_size**.</li>
 *         <li>{@link OS_ACCOUNT_ERR_ACCOUNT_NOT_FOUND} The account is not found.</li>
 *         <li>{@link OS_ACCOUNT_ERR_RESTRICTED_ACCOUNT} The account is restricted and cannot be queried.</li>
 *         </ul>
 * @since 26.0.0
 */
OsAccount_ErrCode OH_OsAccount_GetNameByLocalId(int32_t localId, char *name, size_t name_size);

#ifdef __cplusplus
}
#endif

/** @} */

#endif // OS_ACCOUNT_H