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
 * @addtogroup AbilityAccessControl
 * @{
 *
 * @brief Provides the capability to manage access token.
 *
 * @since 12
 */

/**
 * @file ability_access_control.h
 *
 * @brief Declares the APIs for implementing application access control.
 *
 * @syscap SystemCapability.Security.AccessToken
 * @include <accesstoken/ability_access_control.h>
 * @library libability_access_control.so
 * @kit AbilityKit
 * @since 12
 */

#ifndef ABILITY_ACCESS_CONTROL_H
#define ABILITY_ACCESS_CONTROL_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 校验应用是否被授予指定的权限。
 * @param permission - 需要校验的权限名称。
 * @return 如果应用已经被授予该权限，则返回true。反之，返回false。
 * @since 12
 */
bool OH_AT_CheckSelfPermission(const char *permission);

/**
 * @brief 访问控制操作的错误码。
 *
 * @since 26.1.0
 */
typedef enum OH_AT_AbilityAccessControlErrorCode {
    /**
     * @brief 操作成功。
     * @since 26.1.0
     */
    OH_AT_ABILITY_ACCESS_CONTROL_SUCCESS = 0,
    /**
     * @brief 不支持此能力。
     * @since 26.1.0
     */
    OH_AT_ABILITY_ACCESS_CONTROL_NOT_SUPPORTED_ERROR = 801,
    /**
     * @brief 参数错误。权限数组为NULL、权限包含NULL或空字符串、permCount <= 0、permCount > 1024或NULL回调。
     * @since 26.1.0
     */
    OH_AT_ABILITY_ACCESS_CONTROL_INVALID_PARAMETER_ERROR = 12100001,
    /**
     * @brief 系统服务工作异常。
     * @since 26.1.0
     */
    OH_AT_ABILITY_ACCESS_CONTROL_SERVICE_EXCEPTION_ERROR = 12100007,
    /**
     * @brief 服务内部错误，例如拉起弹窗或获取用户操作结果失败。
     * @since 26.1.0
     */
    OH_AT_ABILITY_ACCESS_CONTROL_COMMON_INNER_ERROR = 12100009,
    /**
     * @brief 进程类型不允许。
     * @since 26.1.0
     */
    OH_AT_ABILITY_ACCESS_CONTROL_NOT_PERMITTED_PROCESS_TYPE_ERROR = 12100016
} OH_AT_AbilityAccessControlErrorCode;

/**
 * @brief 权限请求的结果枚举。
 *
 * @since 26.1.0
 */
typedef enum OH_AT_PermissionOperResult {
    /**
     * @brief 已授权。
     * @since 26.1.0
     */
    OH_AT_PERMISSION_OPER_GRANTED = 0,
    /**
     * @brief 未授权。结合{@link OH_AT_PermissionsRequestResult.dialogShownResults}进一步判断原因：若dialogShownResults为true，表示用户在本次申请中明确拒绝；若为false，表示当前状态无需再弹窗，通常需要用户前往“设置”修改权限的授权状态。
     * @since 26.1.0
     */
    OH_AT_PERMISSION_OPER_SETTING = 1,
    /**
     * @brief 权限名称无效。
     * @since 26.1.0
     */
    OH_AT_PERMISSION_OPER_INVALID_NAME = 2,
    /**
     * @brief 拉起方应用或独立二进制（BIN）未声明该权限。
     * @since 26.1.0
     */
    OH_AT_PERMISSION_OPER_NOT_DECLARED = 3,
    /**
     * @brief 不满足对应权限的申请条件，例如部分位置权限需要满足附加前提条件。当前仅位置权限涉及，包括ohos.permission.LOCATION与ohos.permission.APPROXIMATELY_LOCATION。
     * @since 26.1.0
     */
    OH_AT_PERMISSION_OPER_CONSTRAINTS_NOT_MET = 4,
    /**
     * @brief 该权限的授权模式与本接口不匹配。例如，该权限为manual_settings类型，需要用户前往“设置”开启对应开关。
     * @since 26.1.0
     */
    OH_AT_PERMISSION_OPER_GRANT_MODE_MISMATCH = 5,
    /**
     * @brief 用户未同意隐私声明。
     * @since 26.1.0
     */
    OH_AT_PERMISSION_OPER_PRIVACY_STATEMENT_REQUIRED = 6,
    /**
     * @brief 该权限不支持通过权限弹窗进行申请，可能是申请方式受限或被系统策略管控。该权限无法修改授权状态。
     * @since 26.1.0
     */
    OH_AT_PERMISSION_OPER_POP_UP_RESTRICTED = 7
} OH_AT_PermissionOperResult;

/**
 * @brief 权限请求结果。
 * @since 26.1.0
 */
typedef struct OH_AT_PermissionsRequestResult {
    /**
     * @brief 请求错误码，具体见{@link OH_AT_AbilityAccessControlErrorCode}。
     * @since 26.1.0
     */
    OH_AT_AbilityAccessControlErrorCode errorCode;
    /**
     * @brief 本次请求的权限数组。
     * @since 26.1.0
     */
    const char **permissions;
    /**
     * @brief 请求授权的权限数量。
     * @since 26.1.0
     */
    int32_t permCount;
    /**
     * @brief 每个权限的操作结果，与权限一一对应。
     * @since 26.1.0
     */
    OH_AT_PermissionOperResult *operResults;
    /**
     * @brief 表示每个权限在本次申请过程中是否真正展示过授权弹窗，true表示系统已展示授权弹窗，false表示系统未展示弹窗。
     * @since 26.1.0
     */
    bool *dialogShownResults;
} OH_AT_PermissionsRequestResult;

/**
 * @brief 权限请求结果回调函数类型。
 * 回调可能并发触发，且触发顺序不保证。
 *
 * @param result [in] 权限请求结果。不得为NULL。仅在回调执行期间有效，回调返回后失效。调用者不得持有或释放该结果。
 * @param userData [in,out] 传递给回调的用户数据。可以为空。回调可能修改 userData 指向的内容。其生命周期由调用者负责，且必须覆盖回调的整个执行过程。
 *
 * @since 26.1.0
 */
typedef void (*OH_AT_PermissionsRequestResultCallback)(
    const OH_AT_PermissionsRequestResult *result,
    void *userData);

/**
 * @brief 支持独立二进制拉起弹窗，请求用户授权。
 *
 * @param permissions [in] 待请求的权限数组。不得为NULL，且不得包含NULL或空字符串。
 *     权限必须在拉起方应用中进行声明。本函数返回前，系统会拷贝权限名称，因此调用者在函数返回后可释放该数组及其中的字符串。
 * @param permCount [in] 权限的数量，取值范围为(0, 1024]。
 * @param callback [in] 用于接收每个权限的授权结果的回调函数。不得为NULL。
 *     传递给回调的结果仅在回调执行期间有效。如果本函数返回错误码，则不会触发回调。
 * @param userData [in] 传递给回调的用户数据。可以为NULL。
 *     其生命周期由调用者负责，且必须覆盖回调的整个执行过程。
 * @return <ul>
 *     <li>{@link OH_AT_ABILITY_ACCESS_CONTROL_SUCCESS} 权限请求成功。</li>
 *     <li>{@link OH_AT_ABILITY_ACCESS_CONTROL_NOT_SUPPORTED_ERROR} 不支持此能力。</li>
 *     <li>{@link OH_AT_ABILITY_ACCESS_CONTROL_INVALID_PARAMETER_ERROR} 参数错误。可能原因：
 *     1. 权限包含NULL或空字符串。
 *     2. permCount <= 0或permCount > 1024。
 *     3. 空回调。</li>
 *     <li>{@link OH_AT_ABILITY_ACCESS_CONTROL_SERVICE_EXCEPTION_ERROR} 服务异常。</li>
 *     <li>{@link OH_AT_ABILITY_ACCESS_CONTROL_COMMON_INNER_ERROR} 服务内部错误，例如创建弹窗或获取用户操作结果失败。</li>
 *     <li>{@link OH_AT_ABILITY_ACCESS_CONTROL_NOT_PERMITTED_PROCESS_TYPE_ERROR} 进程类型不允许。</li>
 *     </ul>
 * @since 26.1.0
 */
OH_AT_AbilityAccessControlErrorCode OH_AT_RequestPermissionsFromUser(
    const char *permissions[],
    int32_t permCount,
    OH_AT_PermissionsRequestResultCallback callback,
    void *userData);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* ABILITY_ACCESS_CONTROL_H */