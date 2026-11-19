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
 * @brief Provides certificate management capabilities, including querying and importing certificates and credentials
 * for applications.
 *
 * @since 22
 */
/**
 * @file cm_native_api.h 
 *
 * @brief Defines APIs for querying the list and details of different types of certificates and credentials and
 * importing USB key certificates.
 * @syscap SystemCapability.Security.CertificateManager
 * @include <security/device_certificate/certmanager/cm_native_api.h>
 * @library libohcert_manager.z.so
 * @kit DeviceCertificateKit
 * @since 22
 */

#ifndef CM_NATIVE_API_H
#define CM_NATIVE_API_H

#include "cm_native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Obtains the detail list of USB certificate credentials. After the call is complete,
 * call OH_CertManager_FreeUkeyCertificate to release the certificateList memory.
 *
 * @param keyUri Pointer to the URI that stores the USB certificate credentials, in string format.
 * @param ukeyInfo Pointer to the property information of the USB certificate credential.
 * @param certificateList Pointer to the USB certificate credential detail list obtained.
 * @return <ul>
 * <li>{@link OH_CM_ErrorCode} : </li>
 * <li>**OH_CM_SUCCESS = 0**: Operation successful.</li>
 * <li>**OH_CM_HAS_NO_PERMISSION = 201**: Permission verification failed.</li>
 * <li>**OH_CM_CAPABILITY_NOT_SUPPORTED = 801**: The device is not supported.</li>
 * <li>**OH_CM_PARAMETER_VALIDATION_FAILED = 17500011**: Input parameter verification failed. Possible causes:
 * 1. Incorrect parameter format.
 * 2. Invalid parameter value range.</li>
 * <li>**OH_CM_INNER_FAILURE = 17500001**: Internal error. Possible causes:
 * 1. IPC failure.
 * 2. Memory operation error.
 * 3. File operation error.</li>
 * <li>**OH_CM_NOT_FOUND = 17500002**: The certificate does not exist.</li>
 * <li>**OH_CM_ACCESS_UKEY_SERVICE_FAILED = 17500010**: Failed to access the USB certificate credential.</li>
 * </ul>
 * @permission ohos.permission.ACCESS_CERT_MANAGER
 * @since 22
 */
int32_t OH_CertManager_GetUkeyCertificate(const OH_CM_Blob *keyUri,
    const OH_CM_UkeyInfo *ukeyInfo, OH_CM_CredentialDetailList *certificateList);

/**
 * @brief Obtains the details of a private certificate credential of a specific application.
 * After the call is complete, call OH_CertManager_FreeCredential to release the certificate memory.
 *
 * @param keyUri Pointer to the URI that stores the application's private certificate credentials, in string format.
 * @param certificate Pointer to the details of the application's private credentials obtained.
 * @return <ul>
 * <li>{@link OH_CM_ErrorCode} : </li>
 * <li>**OH_CM_SUCCESS = 0**: Operation successful.</li>
 * <li>**OH_CM_HAS_NO_PERMISSION = 201**: Permission verification failed.</li>
 * <li>**OH_CM_PARAMETER_VALIDATION_FAILED = 17500011**: Input parameter verification failed. Possible causes:
 * 1. Incorrect parameter format.
 * 2. Invalid parameter value range.</li>
 * <li>**OH_CM_INNER_FAILURE = 17500001**: Internal error. Possible causes:
 * 1. IPC failure.
 * 2. Memory operation error.
 * 3. File operation error.</li>
 * <li>**OH_CM_NOT_FOUND = 17500002**: The certificate does not exist.</li>
 * </ul>
 * @permission ohos.permission.ACCESS_CERT_MANAGER
 * @since 22
 */
int32_t OH_CertManager_GetPrivateCertificate(const OH_CM_Blob *keyUri, OH_CM_Credential *certificate);

/**
 * @brief Obtains the details of a public certificate credential of a specific user.
 * After the call is complete, call OH_CertManager_FreeCredential to release the certificate memory.
 *
 * @param keyUri Pointer to the URI that stores the user's public certificate credentials, in string format.
 * @param certificate Pointer to the details of the user's public certificate credential obtained.
 * @return <ul>
 * <li>{@link OH_CM_ErrorCode} : </li>
 * <li>**OH_CM_SUCCESS = 0**: Operation successful.</li>
 * <li>**OH_CM_HAS_NO_PERMISSION = 201**: Permission verification failed.</li>
 * <li>**OH_CM_PARAMETER_VALIDATION_FAILED = 17500011**: Input parameter verification failed. Possible causes:
 * 1. Incorrect parameter format.
 * 2. Invalid parameter value range.</li>
 * <li>**OH_CM_INNER_FAILURE = 17500001**: Internal error. Possible causes:
 * 1. IPC failure.
 * 2. Memory operation error.
 * 3. File operation error.</li>
 * <li>**OH_CM_NOT_FOUND = 17500002**: The certificate does not exist.</li>
 * <li>**OH_CM_NO_AUTHORIZATION = 17500005**: The application is not authorized.</li>
 * </ul>
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

/**
 * @brief This interface is used to query the USB key certificate credential list. After the call is complete, call
 * OH_CertManager_FreeUkeyCertificate to release the certificateList memory.
 *
 * @param ukeyProvider [Input parameter] USB key vendor name.
 * @param ukeyInfo [Input parameter] USB certificate credential attribute information.
 * @param certificateList [Output parameter] Obtained USB certificate credential list.
 * @return Certificate management error code. For the definition of the error code, see {@link OH_CM_ErrorCode}.<ul>
 *     <li>{@link OH_CM_SUCCESS}: Operation succeeded. </li>
 *     <li>{@link OH_CM_HAS_NO_PERMISSION}: Permission verification failed. </li>
 *     <li>{@link OH_CM_CAPABILITY_NOT_SUPPORTED}: The device does not support this function. </li>
 *     <li>__LINK__4_: Internal error. Possible causes:
 *     <br>1. The IPC communication fails.
 *     <br>2. Memory operation error.
 *     <br>3. File operation error. </li>
 *     <li>{@link OH_CM_ACCESS_UKEY_SERVICE_FAILED}: Failed to access the USB certificate credentials. </li>
 *     <li>{@link OH_CM_PARAMETER_VALIDATION_FAILED}: Input parameter validation failed. Possible causes:
 *     <br>1. The parameter format is incorrect.
 *     <br>2. The parameter range is invalid. </li>
 *     </ul>
 * @permission ohos.permission.ACCESS_CERT_MANAGER
 * @since 26.1.0
 */
int32_t OH_CertManager_GetUkeyCertificateList(const OH_CM_Blob *ukeyProvider,
    const OH_CM_UkeyInfo *ukeyInfo, OH_CM_CredentialDetailList *certificateList);

/**
 * @brief Import the certificate to the USB key device.
 *
 * @param keyUri [Input parameter] Unique identifier of the USB certificate (character string format).
 * @param cert [Input parameter] Certificate file to be imported.
 * @param ukeyInfo [Input parameter] USB certificate credential attribute information.
 * @return Certificate management error code. For details about the error code definition, see
 *     {@link OH_CM_ErrorCode}.<ul>
 *     <li>{@link OH_CM_SUCCESS}: Operation succeeded. </li>
 *     <li>{@link OH_CM_HAS_NO_PERMISSION}: Permission verification failed. </li>
 *     <li>{@link OH_CM_CAPABILITY_NOT_SUPPORTED}: The device does not support this function. </li>
 *     <li>__LINK__4_: Internal error. Possible causes:
 *     <br>1. The IPC communication fails.
 *     <br>2. Memory operation error.
 *     <br>3. File operation error. </li>
 *     <li>{@link OH_CM_NOT_FOUND}: The certificate credential specified by keyUri does not exist. </li>
 *     <li>{@link OH_CM_ACCESS_UKEY_SERVICE_FAILED}: Failed to access the USB certificate credentials. </li>
 *     <li>{@link OH_CM_PARAMETER_VALIDATION_FAILED}: Input parameter validation failed. Possible causes:
 *     <br>1. The parameter format is incorrect.
 *     <br>2. The parameter range is invalid. </li>
 *     </ul>
 * @permission ohos.permission.ACCESS_CERT_MANAGER
 * @since 26.1.0
 */
int32_t OH_CertManager_ImportUkeyCert(const OH_CM_Blob *keyUri,
    const OH_CM_Blob *cert, const OH_CM_UkeyInfo *ukeyInfo);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* CM_NATIVE_API_H */