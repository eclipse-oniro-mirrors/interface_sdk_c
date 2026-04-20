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
 * @library libohcert_manager.so
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
 * @brief Obtains the detail list of USB certificate credentials.
 *
 * @param keyUri Pointer to the URI that stores the USB certificate credentials, in string format.
 * @param ukeyInfo Pointer to the property information of the USB certificate credential.
 * @param certificateList Pointer to the USB certificate credential detail list obtained.
 * @return {@link OH_CM_ErrorCode}:
 *     **OH_CM_SUCCESS = 0**: Operation successful.
 *     **OH_CM_HAS_NO_PERMISSION = 201**: Permission verification failed.
 *     **OH_CM_CAPABILITY_NOT_SUPPORTED = 801**: The device is not supported.
 *     **OH_CM_PARAMETER_VALIDATION_FAILED = 17500011**: Input parameter verification failed. Possible causes:
 *         1. Incorrect parameter format.
 *         2. Invalid parameter value range.
 *     **OH_CM_INNER_FAILURE = 17500001**: Internal error. Possible causes:
 *         1. IPC failure.
 *         2. Memory operation error.
 *         3. File operation error.
 *     **OH_CM_NOT_FOUND = 17500002**: The certificate does not exist.
 *     **OH_CM_ACCESS_UKEY_SERVICE_FAILED = 17500010**: Failed to access the USB certificate credential.
 * @permission ohos.permission.ACCESS_CERT_MANAGER
 * @since 22
 */
int32_t OH_CertManager_GetUkeyCertificate(const OH_CM_Blob *keyUri,
    const OH_CM_UkeyInfo *ukeyInfo, OH_CM_CredentialDetailList *certificateList);

/**
 * @brief Obtains the details of a private certificate credential of a specific application.
 *
 * @param keyUri Pointer to the URI that stores the application's private certificate credentials, in string format.
 * @param certificate Pointer to the details of the application's private credentials obtained.
 * @return {@link OH_CM_ErrorCode}:
 *     **OH_CM_SUCCESS = 0**: Operation successful.
 *     **OH_CM_HAS_NO_PERMISSION = 201**: Permission verification failed.
 *     **OH_CM_PARAMETER_VALIDATION_FAILED = 17500011**: Input parameter verification failed. Possible causes:
 *         1. Incorrect parameter format.
 *         2. Invalid parameter value range.
 *     **OH_CM_INNER_FAILURE = 17500001**: Internal error. Possible causes:
 *         1. IPC failure.
 *         2. Memory operation error.
 *         3. File operation error.
 *     **OH_CM_NOT_FOUND = 17500002**: The certificate does not exist.
 * @permission ohos.permission.ACCESS_CERT_MANAGER
 * @since 22
 */
int32_t OH_CertManager_GetPrivateCertificate(const OH_CM_Blob *keyUri, OH_CM_Credential *certificate);

/**
 * @brief Obtains the details of a public certificate credential of a specific user.
 *
 * @param keyUri Pointer to the URI that stores the user's public certificate credentials, in string format.
 * @param certificate Pointer to the details of the user's public certificate credential obtained.
 * @return {@link OH_CM_ErrorCode}:
 *     **OH_CM_SUCCESS = 0**: Operation successful.
 *     **OH_CM_HAS_NO_PERMISSION = 201**: Permission verification failed.
 *     **OH_CM_PARAMETER_VALIDATION_FAILED = 17500011**: Input parameter verification failed. Possible causes:
 *         1. Incorrect parameter format.
 *         2. Invalid parameter value range.
 *     **OH_CM_INNER_FAILURE = 17500001**: Internal error. Possible causes:
 *         1. IPC failure.
 *         2. Memory operation error.
 *         3. File operation error.
 *     **OH_CM_NOT_FOUND = 17500002**: The certificate does not exist.
 *     **OH_CM_NO_AUTHORIZATION = 17500005**: The application is not authorized.
 * @permission ohos.permission.ACCESS_CERT_MANAGER
 * @since 22
 */
int32_t OH_CertManager_GetPublicCertificate(const OH_CM_Blob *keyUri, OH_CM_Credential *certificate);

/**
 * @brief Destroys the certificate detail list.
 *
 * @param certificateList Pointer to the certificate credential detail list to be destroyed.
 * @since 22
 */
void OH_CertManager_FreeUkeyCertificate(OH_CM_CredentialDetailList *certificateList);

/**
 * @brief Destroys the certificate details.
 *
 * @param certificate Pointer to the certificate credential details to be destroyed.
 * @since 22
 */
void OH_CertManager_FreeCredential(OH_CM_Credential *certificate);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* CM_NATIVE_API_H */
