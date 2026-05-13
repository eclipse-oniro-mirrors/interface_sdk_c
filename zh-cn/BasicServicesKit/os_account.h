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
 * @brief 声明访问和管理系统账号信息的API。
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
 * @brief 获取调用方进程所属的系统账号的名称。
 *
 * @param buffer 名称字符数组，其应具有能够存放名称（最大长度为LOGIN_NAME_MAX）和结束字符（'\0'）的空间。
 * @param buffer_size 名称字符数组的大小。
 * @return <ul>
 *         <li>{@link OS_ACCOUNT_ERR_OK} 表示成功；</li>
 *         <li>{@link OS_ACCOUNT_ERR_INTERNAL_ERROR} 表示内部错误；</li>
 *         <li>{@link OS_ACCOUNT_ERR_INVALID_PARAMETER} 表示buffer为NULL指针，或名称（不包括结束字符'\0'）的长度大于等于buffer_size。</li>
 *         </ul>
 * @since 12
 */
OsAccount_ErrCode OH_OsAccount_GetName(char *buffer, size_t buffer_size);

/**
 * @brief 根据本地ID获取目标系统账号的名称。
 *
 * @permission ohos.permission.GET_LOCAL_ACCOUNT_IDENTIFIERS
 * @param localId 目标系统账号的本地ID。
 * @param name 名称字符数组应包含名称及终止符（'\0'），最大长度为LOGIN_NAME_MAX（256）。
 * @param name_size 名称字符数组的大小。
 * @return <ul>
 *         <li>{@link OS_ACCOUNT_ERR_OK} 表示成功；</li>
 *         <li>{@link OS_ACCOUNT_ERR_PERMISSION_DENIED} 表示权限被拒绝；</li>
 *         <li>{@link OS_ACCOUNT_ERR_INTERNAL_ERROR} 表示内部错误；</li>
 *         <li>{@link OS_ACCOUNT_ERR_INVALID_PARAMETER} 表示name为空指针或名称长度（包括结束符'\0'）大于name_size；</li>
 *         <li>{@link OS_ACCOUNT_ERR_ACCOUNT_NOT_FOUND} 表示未找到账号；</li>
 *         <li>{@link OS_ACCOUNT_ERR_RESTRICTED_ACCOUNT} 表示账号受限，无法查询；</li>
 *         </ul>
 * @since 26.0.0
 */
OsAccount_ErrCode OH_OsAccount_GetNameByLocalId(int32_t localId, char *name, size_t name_size);
#ifdef __cplusplus
}
#endif

/** @} */
#endif // OS_ACCOUNT_H