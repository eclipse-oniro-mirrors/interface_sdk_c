/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef NET_SSL_C_H
#define NET_SSL_C_H

#include <stdbool.h>

/**
 * @addtogroup netstack
 * @{
 *
 * @brief Provides C APIs for the SSL/TLS certificate chain verification module.
 *
 * @since 11
 * @version 1.0
 */

/**
 * @addtogroup netstack
 * @{
 *
 * @brief Provides C APIs for the SSL/TLS certificate chain verification module.
 *
 * @since 11
 * @version 1.0
 */

/**
 * @file net_ssl_c.h
 *
 * @brief Defines C APIs for the SSL/TLS certificate chain verification module.
 *
 * @library libnet_ssl.so
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */

#include "net_ssl_c_type.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Provides certificate chain verification APIs for external systems.
 *
 * @param cert Certificate to be verified.
 * @param caCert Certificate specified by the user. If this parameter is left blank, the preset certificate is used for
 *     verification.
 * @return **0**: Success.
 *     <br>**2305001**: Unknown error.
 *     <br>**2305002**: Failed to obtain the issuer certificate.
 *     <br>**2305003**: Failed to obtain the certificate revocation list (CRL).
 *     <br>**2305004**: Failed to decrypt the certificate signature.
 *     <br>**2305005**: Failed to decrypt the CRL signature.
 *     <br>**2305006**: Failed to decode the issuer public key.
 *     <br>**2305007**: Failed to sign the certificate.
 *     <br>**2305008**: Failed to sign the CRL.
 *     <br>**2305009**: Certificate not activated.
 *     <br>**2305010**: Certificate expired.
 *     <br>**2305011**: CRL not activated.
 *     <br>**2305012**: CRL expired.
 *     <br>**2305023**: Certificate revoked.
 *     <br>**2305024**: Invalid certificate authority (CA).
 *     <br>**2305027**: Untrusted certificate.
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
uint32_t OH_NetStack_CertVerification(const struct NetStack_CertBlob *cert, const struct NetStack_CertBlob *caCert);

/**
 * @brief Obtains the certificate lock information.
 *
 * @param hostname Host name.
 * @param pin Defines the certificate lock information structure.
 * @return **0**: Success.
 *     <br>**401**: Parameter error.
 *     <br>**2305999**: Memory error.
 * @syscap SystemCapability.Communication.NetStack
 * @since 12
 * @version 1.0
 */
int32_t OH_NetStack_GetPinSetForHostName(const char *hostname, NetStack_CertificatePinning *pin);

/**
 * @brief Obtains the certificate information.
 *
 * @param hostname Host name.
 * @param certs Defines the certificate information structure.
 * @return **0**: Success.
 *     <br>**401**: Parameter error.
 *     <br>**2305999**: Memory error.
 * @syscap SystemCapability.Communication.NetStack
 * @since 12
 * @version 1.0
 */
int32_t OH_NetStack_GetCertificatesForHostName(const char *hostname, NetStack_Certificates *certs);

/**
 * @brief Releases the certificate content.
 *
 * @param certs Represents the certificate information.
 * @syscap SystemCapability.Communication.NetStack
 * @since 12
 * @version 1.0
 */
void OH_Netstack_DestroyCertificatesContent(NetStack_Certificates *certs);

/**
 * @brief Boolean value indicating whether plaintext HTTP is allowed.
 *
 * @permission ohos.permission.INTERNET
 * @return **0**: Success.
 *     <br>**201**: Permission denied.
 *     <br>**401**: Parameter error.
 * @param isCleartextPermitted Boolean value indicating whether plaintext HTTP is allowed. The value **true** means
 *     that plaintext HTTP is allowed, and the value **false** means the opposite.
 * @since 18
 */
int32_t OH_Netstack_IsCleartextPermitted(bool *isCleartextPermitted);

/**
 * @brief Boolean value indicating whether host name–based plaintext HTTP is allowed.
 *
 * @permission ohos.permission.INTERNET
 * @return **0**: Success.
 *     <br>**201**: Permission denied.
 *     <br>**401**: Parameter error.
 * @param hostname Host name.
 * @param isCleartextPermitted Boolean value indicating whether host name–based plaintext HTTP is allowed. The value **
 *     true** means that host name–based plaintext HTTP is allowed, and the value **false** means the opposite.
 * @since 18
 */
int32_t OH_Netstack_IsCleartextPermittedByHostName(const char *hostname, bool *isCleartextPermitted);

/**
 * @brief Checks whether plaintext HTTP interception is enabled.
 *
 * @return **0**: Success.
 *     <br>**2100001**: Invalid parameter value.
 * @param component Component name. The following components are supported: Network Kit and ArkWeb.
 * @param componentCfg Output parameter, which indicates whether plaintext HTTP interception is enabled. The value **
 *     true** indicates that plaintext HTTP interception is enabled, and the value **false** indicates the opposite.
 * @since 20
 */
int32_t OH_Netstack_IsCleartextCfgByComponent(const char *component, bool *componentCfg);

/**
 * @brief Creates and verifies a sorted certificate chain.
 *
 * @detail This function verifies the provided certificate chain and constructs
 *         a sorted chain output. It allocates memory for the output chain,
 *         which must be explicitly freed by the caller to avoid memory leaks.
 *
 * @param cert Certificate chain to be verified. Cannot be NULL or empty.
 * @param certCount Certificate number of param cert.
 * @param caCert CA certificate specified by the user. If NULL, the preset certificate is used.
 * @param hostname The expected server hostname.
 * @param outSortedChain Pointer to receive the sorted certificate chain.
 *                     Can be NULL if the caller does not need the chain data.
 *                     Valid only if return value is 0.
 *                     Allocated memory must be freed using OH_NetStack_FreeCertChain.
 * @param outSortedCount Pointer to receive the count of sorted certificates.
 * @return 0 - success.
 *         2305001 - Unspecified error.
 *         2305002 - Unable to get issuer certificate.
 *         2305004 - Unable to decrypt certificate signature.
 *         2305006 - Unable to decode issuer public key.
 *         2305007 - Certificate signature failure.
 *         2305009 - Certificate is not yet valid.
 *         2305010 - Certificate has expired.
 *         2305024 - Invalid certificate authority (CA).
 *         2305062 - Hostname verification failed.
 *         2305027 - Certificate is untrusted.
 * @stagemodelonly
 * @since 26.0.0
 * @note After use, you must call {@link OH_NetStack_FreeCertChain} to release the
 *       allocated memory pointed by outSortedChain. Failure to do so will cause memory leaks.
 */
uint32_t OH_NetStack_CreateAndVerifySortedCertChain(const struct NetStack_CertBlob *cert, size_t certCount,
    const struct NetStack_CertBlob *caCert, const char *hostname,
    struct NetStack_CertBlob **outSortedChain, size_t *outSortedCount);

/**
 * @brief Frees the certificate chain allocated by OH_NetStack_CreateAndVerifySortedCertChain.
 *
 * @detail This function must be used to free the memory pointed to by outSortedChain
 *         from OH_NetStack_CreateAndVerifySortedCertChain.
 *         Do NOT use free() or malloc() directly on this memory.
 *
 * @param certChain The certificate chain pointer received from outSortedChain.
 *                  If NULL, this function does nothing.
 * @param certCount The number of certificates in the chain.
 * @stagemodelonly
 * @since 26.0.0
 */
void OH_NetStack_FreeCertChain(struct NetStack_CertBlob *certChain, size_t certCount);

#ifdef __cplusplus
}
#endif

/** @} */

#endif // NET_SSL_C_H