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
 * @addtogroup CertManagerType
 * @{
 *
 * @brief Defines the macros, enumerated values, data structures,
 * and error codes used by OpenHarmony Certificate Manager APIs.
 *
 * @since 22
 */
/**
 * @file cm_native_type.h
 *
 * @brief Provides the enums, structs, macros, and error codes used by **CertManager** APIs.
 *
 * @library libohcert_manager.so
 * @kit DeviceCertificateKit
 * @syscap SystemCapability.Security.CertificateManager
 * @since 22
 */

#ifndef CM_NATIVE_TYPE_H
#define CM_NATIVE_TYPE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OH_CM_MAX_LEN_CERTIFICATE_CHAIN   24588
#define OH_CM_MAX_LEN_URI              256
#define OH_CM_MAX_LEN_CERT_ALIAS       129
#define OH_CM_MAX_LEN_TYPE_NAME       1025

/**
 * @brief Enumerates error codes.
 *
 * @since 22
 */
typedef enum {
    /**
     * Operation succeeded.
     */
    OH_CM_SUCCESS = 0,
    /**
     * Permission verification failed.
     */
    OH_CM_HAS_NO_PERMISSION = 201,
    /**
     * Not supported by the device.
     */
    OH_CM_CAPABILITY_NOT_SUPPORTED = 801,
    /**
     * Internal error. Possible causes: 1. IPC failure. 2. Memory operation error. 3. File operation error.
     */
    OH_CM_INNER_FAILURE = 17500001,
    /**
     * The certificate does not exist.
     */
    OH_CM_NOT_FOUND = 17500002,
    /**
     * The keystore format is invalid or the keystore password is incorrect.
     */
    OH_CM_INVALID_CERT_FORMAT = 17500003,
    /**
     * The number of certificates or credentials reaches the upper limit.
     */
    OH_CM_MAX_CERT_COUNT_REACHED = 17500004,
    /**
     * The application is not authorized.
     */
    OH_CM_NO_AUTHORIZATION = 17500005,
    /**
     * The device enters the advanced security mode.
     */
    OH_CM_DEVICE_ENTER_ADVSECMODE = 17500007,
    /**
     * The device does not support the specified certificate storage path.
     */
    OH_CM_STORE_PATH_NOT_SUPPORTED = 17500009,
    /**
     * Failed to access the USB certificate credential.
     */
    OH_CM_ACCESS_UKEY_SERVICE_FAILED = 17500010,
    /**
     * Parameter verification fails. For example, the parameter format or range is invalid.
     */
    OH_CM_PARAMETER_VALIDATION_FAILED = 17500011,
} OH_CM_ErrorCode;

/**
 * @brief Enumerates the certificate credential purposes.
 *
 * @since 22
 */
typedef enum {
    /**
     * Default purpose, which is used for credential signing.
     */
    OH_CM_CERT_PURPOSE_DEFAULT = 0,
    /**
     * All purposes, which are used to query credential functionalities.
     */
    OH_CM_CERT_PURPOSE_ALL = 1,
    /**
     * Signing purpose.
     */
    OH_CM_CERT_PURPOSE_SIGN = 2,
    /**
     * Encryption purpose.
     */
    OH_CM_CERT_PURPOSE_ENCRYPT = 3,
} OH_CM_CertificatePurpose;

/**
 * @brief Defines a struct for a binary large object (BLOB).
 *
 * @since 22
 */
typedef struct {
    /**
     * Data size.
     */
    uint32_t size;
    /**
     * Pointer to the memory in which the data is stored.
     */
    uint8_t *data;
} OH_CM_Blob;

/**
 * @brief Defines a struct for the certificate credential details.
 *
 * @since 22
 */
typedef struct {
    /**
     * Whether a certificate data exists.
     */
    uint32_t isExist;
    /**
     * Indicates the type of Credential. The value include the terminator('\0')  char.
     */
    char type[OH_CM_MAX_LEN_TYPE_NAME];
    /**
     * Indicates the alias of Credential. The value include the terminator('\0')  char.
     */
    char alias[OH_CM_MAX_LEN_CERT_ALIAS];
    /**
     * Indicates the uri of Credential.
     */
    char keyUri[OH_CM_MAX_LEN_URI];
    /**
     * Number of certificates contained in the credential.
     */
    uint32_t certNum;
    /**
     * Number of keys contained in the credential.
     */
    uint32_t keyNum;
    /**
     * Binary data of a credential. The value contains up to 20480 bytes.
     */
    OH_CM_Blob credData;
    /**
     * Purpose of a certificate credential.
     */
    OH_CM_CertificatePurpose certPurpose;
} OH_CM_Credential;

/**
 * @brief Defines a struct for the certificate credential detail list.
 *
 * @since 22
 */
typedef struct {
    /**
     * Number of certificate credential details.
     */
    uint32_t credentialCount;
    /**
     * Indicates the credential data.
     */
    OH_CM_Credential *credential;
} OH_CM_CredentialDetailList;

/**
 * @brief Defines a struct for the USB certificate credential information.
 *
 * @since 22
 */
typedef struct {
    /**
     * Purpose of a certificate credential.
     */
    OH_CM_CertificatePurpose certPurpose;
} OH_CM_UkeyInfo;

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* CM_NATIVE_TYPE_H */
