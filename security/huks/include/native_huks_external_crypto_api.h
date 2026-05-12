
/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup HuksExternalCryptoApi
 * @{
 *
 * @brief Describes the OpenHarmony Universal KeyStore (HUKS) capabilities specifical for external crypto extensions,
 * including provider management and ukey pin management and other operations, provided for applications.
 *
 * @since 22
 */

/**
 * @file native_huks_external_crypto_api.h
 *
 * @brief Defines the OpenHarmony Universal KeyStore (HUKS) APIs for external key management extensions.
 *
 * @library libhuks_external_crypto.z.so
 * @syscap SystemCapability.Security.Huks.CryptoExtension
 *
 *     include "huks/include/native_huks_external_crypto_type.h"
 * @kit UniversalKeystoreKit
 * @since 22
 */

#ifndef NATIVE_HUKS_EXTERNAL_CRYPTO_API_H
#define NATIVE_HUKS_EXTERNAL_CRYPTO_API_H

#include "native_huks_external_crypto_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Registers an external key management extension provider.
 *
 * @permission ohos.permission.CRYPTO_EXTENSION_REGISTER
 * @param providerName Name of the provider.
 * @param paramSet Pointer to the registration parameters.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_PERMISSION_FAIL 201: Permission verification fails. Apply for the required permission
 *     first.
 *     <br>OH_HUKS_ERR_CODE_NOT_SUPPORTED_API 801: Unsupported API.
 *     <br>OH_HUKS_ERR_CODE_MISSING_CRYPTO_ALG_ARGUMENT 12000002: Failed to obtain the provider parameters.
 *     <br>OH_HUKS_ERR_CODE_COMMUNICATION_FAIL 12000005: IPC communication failed.
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014: Insufficient memory.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT 12000018: Invalid **providerName** or **paramSet**.
 *     <br>OH_HUKS_ERR_CODE_ITEM_NOT_EXIST 12000019: The provider has been registered.
 *     <br>OH_HUKS_ERR_CODE_EXTERNAL_ERROR 12000020: An error occurs in the dependent module.
 *     <br>OH_HUKS_ERR_CODE_EXCEED_LIMIT 12000025: The number of providers exceeds the upper limit.
 * @since 22
 */
struct OH_Huks_Result OH_Huks_RegisterProvider(
    const struct OH_Huks_Blob *providerName, const OH_Huks_ExternalCryptoParamSet *paramSet);

/**
 * @brief Unregisters an external key management extension provider.
 *
 * @permission ohos.permission.CRYPTO_EXTENSION_REGISTER
 * @param providerName Name of the provider.
 * @param paramSet Pointer to the registration parameters.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_PERMISSION_FAIL 201: Permission verification fails. Apply for the required permission
 *     first.
 *     <br>OH_HUKS_ERR_CODE_NOT_SUPPORTED_API 801: Unsupported API.
 *     <br>OH_HUKS_ERR_CODE_COMMUNICATION_FAIL 12000005: IPC communication failed.
 *     <br>OH_HUKS_ERR_CODE_ITEM_NOT_EXIST 12000011: The specified provider is not found.
 *     <br>OH_HUKS_ERR_CODE_INTERNAL_ERROR 12000012: An internal system error occurs. The key management
 *     extension module is not loaded.
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014: Insufficient memory.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT 12000018: Invalid **providerName**.
 * @since 22
 */
struct OH_Huks_Result OH_Huks_UnregisterProvider(
    const struct OH_Huks_Blob *providerName, const OH_Huks_ExternalCryptoParamSet *paramSet);

/**
 * @brief Opens a resource based on the specified resource ID.
 * <br>Note: The opened resource must be closed using {@link OH_Huks_CloseResource}.
 *
 * @param resourceId Resource ID of the specified provider.
 * @param paramSet Pointer to the handle operation parameters.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_NOT_SUPPORTED_API 801: Unsupported API.
 *     <br>OH_HUKS_ERR_CODE_COMMUNICATION_FAIL 12000005: IPC communication failed.
 *     <br>OH_HUKS_ERR_CODE_CRYPTO_FAIL 12000006: Ukey driver error.
 *     <br>OH_HUKS_ERR_CODE_ITEM_NOT_EXIST 12000011: The cached resource handle is not found. Open the resource
 *     based on the resource ID first.
 *     <br>OH_HUKS_ERR_CODE_INTERNAL_ERROR 12000012: An internal system error occurs. The processing function is
 *     not found.
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014: Insufficient memory.
 *     <br>OH_HUKS_ERR_CODE_KEY_ALREADY_EXIST 12000017: The resource is already open.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT 12000018: Invalid **resourceId** or **paramSet**.
 *     <br>OH_HUKS_ERR_CODE_EXTERNAL_ERROR 12000020: Provider execution fails.
 *     <br>OH_HUKS_ERR_CODE_BUSY 12000024: The provider or Ukey is busy.
 *     <br>OH_HUKS_ERR_CODE_EXCEED_LIMIT 12000025: The number of opened resources exceeds the limit.
 * @since 22
 */
struct OH_Huks_Result OH_Huks_OpenResource(
    const struct OH_Huks_Blob *resourceId, const OH_Huks_ExternalCryptoParamSet *paramSet);

/**
 * @brief Closes a resource based on the specified resource ID.
 *
 * @param resourceId Resource ID of the specified provider.
 * @param paramSet Pointer to the handle operation parameters.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_NOT_SUPPORTED_API 801: Unsupported API.
 *     <br>OH_HUKS_ERR_CODE_COMMUNICATION_FAIL 12000005: IPC communication failed.
 *     <br>OH_HUKS_ERR_CODE_CRYPTO_FAIL 12000006: Ukey driver error.
 *     <br>OH_HUKS_ERR_CODE_INTERNAL_ERROR 12000012: An internal system error occurs. The processing function is
 *     not found.
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014: Insufficient memory.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT 12000018: Invalid **resourceId** or **paramSet**.
 *     <br>OH_HUKS_ERR_CODE_EXTERNAL_ERROR 12000020: Provider execution fails.
 *     <br>OH_HUKS_ERR_CODE_BUSY 12000024: The provider or Ukey is busy.
 * @since 22
 */
struct OH_Huks_Result OH_Huks_CloseResource(
    const struct OH_Huks_Blob *resourceId, const OH_Huks_ExternalCryptoParamSet *paramSet);

/**
 * @brief Obtains the PIN authorization state of the specified Ukey resource ID.
 *
 * @param resourceId Resource ID of the specified provider.
 * @param paramSet Pointer to the PIN authorization parameters.
 * @param authState Whether a specified index is authorized.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_NOT_SUPPORTED_API 801: Unsupported API.
 *     <br>OH_HUKS_ERR_CODE_COMMUNICATION_FAIL 12000005: IPC communication failed.
 *     <br>OH_HUKS_ERR_CODE_CRYPTO_FAIL 12000006: Ukey driver error.
 *     <br>OH_HUKS_ERR_CODE_ITEM_NOT_EXIST 12000011: The specified resource ID is invalid.
 *     <br>OH_HUKS_ERR_CODE_INTERNAL_ERROR 12000012: An internal system error occurs. The processing function is
 *     not found.
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014: Insufficient memory.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT 12000018: Invalid **resourceId** or **paramSet**.
 *     <br>OH_HUKS_ERR_CODE_EXTERNAL_ERROR 12000020: Provider execution fails.
 *     <br>OH_HUKS_ERR_CODE_BUSY 12000024: The provider or Ukey is busy.
 * @since 22
 */
struct OH_Huks_Result OH_Huks_GetUkeyPinAuthState(
    const struct OH_Huks_Blob *resourceId, const OH_Huks_ExternalCryptoParamSet *paramSet,
    OH_Huks_ExternalPinAuthState *authState);

/**
 * @brief Obtains the property information of the external key management extension provider.
 *
 * @param resourceId Resource ID of the specified provider.
 * @param propertyId Name of the property function defined by GMT 0016-2023.
 * @param paramSetIn Pointer to the input operation parameters.
 * @param paramSetOut Pointer to the output parameters, which must contain the **OH_HUKS_EXT_CRYPTO_TAG_EXTRA_DATA**
 *     parameter.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_NOT_SUPPORTED_API 801: Unsupported API.
 *     <br>OH_HUKS_ERR_CODE_COMMUNICATION_FAIL 12000005: IPC communication failed.
 *     <br>OH_HUKS_ERR_CODE_CRYPTO_FAIL 12000006: Driver error.
 *     <br>OH_HUKS_ERR_CODE_ITEM_NOT_EXIST 12000011: The specified handle in the cache is not found.
 *     <br>OH_HUKS_ERR_CODE_INTERNAL_ERROR 12000012: An internal system error occurs. The processing function is
 *     not found.
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014: Insufficient memory.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT 12000018: Invalid **resourceId**, **propertyId**, **paramSet**, or
 *     callback.
 *     <br>OH_HUKS_ERR_CODE_EXTERNAL_ERROR 12000020: The provider or Ukey internal execution fails.
 *     <br>OH_HUKS_ERR_CODE_PIN_LOCKED 12000021: The PIN is locked.
 *     <br>OH_HUKS_ERR_CODE_PIN_NO_AUTH 12000023: PIN authentication fails.
 *     <br>OH_HUKS_ERR_CODE_BUSY 12000024: The resources in the provider or Ukey are being used.
 * @since 22
 */
struct OH_Huks_Result OH_Huks_GetProperty(const struct OH_Huks_Blob *resourceId,
    const struct OH_Huks_Blob *propertyId, const OH_Huks_ExternalCryptoParamSet *paramSetIn,
    OH_Huks_ExternalCryptoParamSet **paramSetOut);

/**
 * @brief Initializes a parameter set.
 *
 * @param paramSet Level-2 pointer to the parameter set to initialize.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014: Insufficient memory.
 *     <br>OH_HUKS_ERR_CODE_INVALID_ARGUMENT 12000018: **params** is NULL or **paramSet** is invalid.
 * @since 22
 */
struct OH_Huks_Result OH_Huks_InitExternalCryptoParamSet(OH_Huks_ExternalCryptoParamSet **paramSet);

/**
 * @brief Adds parameters to a parameter set.
 *
 * @param paramSet Pointer to the parameter set to which parameters are to be added.
 * @param params Pointer to the parameter array to be added.
 * @param paramCnt Number of parameters to be added.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_INVALID_ARGUMENT 12000018: **params** is NULL or **paramSet** is invalid.
 * @since 22
 */
struct OH_Huks_Result OH_Huks_AddExternalCryptoParams(OH_Huks_ExternalCryptoParamSet *paramSet,
    const OH_Huks_ExternalCryptoParam *params, uint32_t paramCnt);

/**
 * @brief Builds a parameter set.
 *
 * @param paramSet Level-2 pointer to the parameter set to build.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_INVALID_ARGUMENT 12000018 - Invalid **paramSet**.
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY 12000014: Insufficient memory.
 * @since 22
 */
struct OH_Huks_Result OH_Huks_BuildExternalCryptoParamSet(OH_Huks_ExternalCryptoParamSet **paramSet);

/**
 * @brief Destroys a parameter set and releases related memory.
 *
 * @param paramSet Level-2 pointer to the parameter set to destroy.
 * @since 22
 */
void OH_Huks_FreeExternalCryptoParamSet(OH_Huks_ExternalCryptoParamSet **paramSet);

/**
 * @brief Obtains a specified parameter from a parameter set.
 *
 * @param paramSet Pointer to the target parameter set.
 * @param tag Tag value of the parameter to obtain.
 * @param param Level-2 pointer used to return the obtained parameter.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_INVALID_ARGUMENT 12000018 - **paramSet** or **param** is invalid, or the parameter does
 *     not exist in the set.
 * @since 22
 */
struct OH_Huks_Result OH_Huks_GetExternalCryptoParam(OH_Huks_ExternalCryptoParamSet *paramSet,
    const uint32_t tag, OH_Huks_ExternalCryptoParam **param);
#ifdef __cplusplus
}
#endif

/** @} */
#endif /* NATIVE_HUKS_EXTERNAL_CRYPTO_API_H */