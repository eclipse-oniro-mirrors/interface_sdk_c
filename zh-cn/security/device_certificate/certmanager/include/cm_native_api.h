/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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
 * @addtogroup CertManager
 * @{
 *
 * @brief Describes the OpenHarmony Certificate Manager capabilities, including certificate and credential management
 * operations, provided for applications.
 *
 * @since 22
 */

/**
 * @file cm_native_api.h
 *
 * @brief Declares the APIs used to obtain details of specific certificates.
 *
 * @library libohcert_manager.z.so
 * @kit DeviceCertificateKit
 * @syscap SystemCapability.Security.CertificateManager
 * @since 22
 */

#ifndef CM_NATIVE_API_H
#define CM_NATIVE_API_H

#include "cm_native_type.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 获取USB证书凭据的详情信息列表。调用完成后，需要调用OH_CertManager_FreeUkeyCertificate释放certificateList内存。
*
 * @param keyUri 存放USB证书凭据的唯一标识符（字符串格式）。
 * @param ukeyInfo USB证书凭据属性信息。
 * @param certificateList 获取到的USB证书凭据详情列表。
 * @return <ul>
* <li>{@link OH_CM_ErrorCode} : </li>
* <li>**OH_CM_SUCCESS = 0**: 操作成功。</li>
* <li>**OH_CM_HAS_NO_PERMISSION = 201**: 权限校验失败。</li>
* <li>**OH_CM_CAPABILITY_NOT_SUPPORTED = 801**: 设备不支持。</li>
* <li>**OH_CM_PARAMETER_VALIDATION_FAILED = 17500011**: 入参校验失败。可能原因：
* 1.参数格式错误。
* 2.参数范围无效。</li>
* <li>**OH_CM_INNER_FAILURE = 17500001**: 内部错误。可能原因：
* 1.IPC通讯失败。
* 2.内存操作错误。
* 3.文件操作错误。</li>
* <li>**OH_CM_NOT_FOUND = 17500002**: 证书不存在。</li>
* <li>**OH_CM_ACCESS_UKEY_SERVICE_FAILED = 17500010**: USB证书凭据访问失败。</li>
* </ul>
 * @permission ohos.permission.ACCESS_CERT_MANAGER
 * @since 22
 */
int32_t OH_CertManager_GetUkeyCertificate(const OH_CM_Blob *keyUri,
    const OH_CM_UkeyInfo *ukeyInfo, OH_CM_CredentialDetailList *certificateList);
/**
 * @brief 获取特定应用私有证书凭据详细信息。
 * 
 * @param keyUri 存放应用私有证书凭据的唯一标识符（字符串格式）。
 * @param certificate 获取到的应用私有凭据的详情。
 * @return <ul>
 * <li>{@link OH_CM_ErrorCode}：</li>
 * <li>OH_CM_SUCCESS = 0 ：操作成功。</li>
 * <li>OH_CM_HAS_NO_PERMISSION = 201 ：权限校验失败。</li>
 * <li>OH_CM_PARAMETER_VALIDATION_FAILED = 17500011 ：入参校验失败。可能原因：</li>
 * 1.参数格式错误。
 * 2.参数范围无效。</li>
 * <li>OH_CM_INNER_FAILURE = 17500001 ：内部错误。可能原因：
 * 1.IPC通讯失败。
 * 2.内存操作错误。
 * 3.文件操作错误。</li>
 * <li>OH_CM_NOT_FOUND = 17500002 ：证书不存在。</li>
 * </ul>
 * @permission ohos.permission.ACCESS_CERT_MANAGER
 * @since 22
 */
int32_t OH_CertManager_GetPrivateCertificate(const OH_CM_Blob *keyUri, OH_CM_Credential *certificate);
/**
 * @brief 获取特定用户公共证书凭据详细信息。调用完成后，需要调用OH_CertManager_FreeCredential释放certificate内存。
*
 * @param keyUri 存放用户公共证书凭据的唯一标识符（字符串格式）。
 * @param certificate 获取到的用户公共证书凭据的详情。
 * @return <ul>
* <li>{@link OH_CM_ErrorCode} ： </li>
* <li>OH_CM_SUCCESS = 0 ：操作成功。</li>
* <li>OH_CM_HAS_NO_PERMISSION = 201 ：权限校验失败。</li>
* <li>OH_CM_PARAMETER_VALIDATION_FAILED = 17500011 ：入参校验失败。可能原因：
* 1.参数格式错误。
* 2.参数范围无效。</li>
* <li>OH_CM_INNER_FAILURE = 17500001 ：内部错误。可能原因：
* 1.IPC通讯失败。
* 2.内存操作错误。
* 3.文件操作错误。</li>
* <li>OH_CM_NOT_FOUND = 17500002 ：证书不存在。</li>
* <li>OH_CM_NO_AUTHORIZATION =  17500005 ：应用未经用户授权。</li>
* </ul>
 * @permission ohos.permission.ACCESS_CERT_MANAGER
 * @since 22
 */
int32_t OH_CertManager_GetPublicCertificate(const OH_CM_Blob *keyUri, OH_CM_Credential *certificate);

/**
 * @brief 销毁证书详情信息列表。
 * 
 * @param certificateList 待销毁的证书凭据详细列表。
 * @since 22
 */
void OH_CertManager_FreeUkeyCertificate(OH_CM_CredentialDetailList *certificateList);

/**
 * @brief 销毁证书详情。
 * 
 * @param certificate 待销毁的证书凭据详情。
 * @since 22
 */
void OH_CertManager_FreeCredential(OH_CM_Credential *certificate);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* CM_NATIVE_API_H */