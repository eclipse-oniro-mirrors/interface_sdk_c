/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
 * @addtogroup HuksParamSetApi
 * @{
 *
 * @brief Defines the capabilities of OpenHarmony Universal KeyStore (HUKS) parameter sets.
 *    The HUKS APIs can be used to perform parameter set lifecycle management,
 *    including initializing a parameter set, adding parameters to a parameter set, constructing
 *    a parameter set, and destroying a parameter set.
 *    They can also be used to obtain parameters, copy parameter sets, and check parameter validity.
 *
 * @since 9
 * @version 1.0
 */

/**
 * @file native_huks_param.h
 *
 * @brief Provides APIs for constructing, using, and destroying a parameter set.
 *
 * @library libhuks_ndk.z.so
 * @syscap SystemCapability.Security.Huks.Core
 *
 * @kit UniversalKeystoreKit
 * @since 9
 * @version 1.0
 */
#ifndef NATIVE_HUKS_PARAM_H
#define NATIVE_HUKS_PARAM_H
#include "native_huks_type.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes a parameter set. No parameter information is required, and the default available memory space is
 * allocated to the parameter set. The initialized parameter set needs to be released by using
 * {@link OH_Huks_FreeParamSet}. To add parameters to a parameter set, you need to use {@link OH_Huks_AddParams} to add
 * parameters and use {@link OH_Huks_BuildParamSet} to construct the parameter set.
 *
 * @param paramSet {@link struct OH_Huks_ParamSet} Double pointer to the parameter set to initialize.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS = 0: Initialization successful.
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY = 12000014: Insufficient memory.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401: **paramSet** is invalid.
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_InitParamSet(struct OH_Huks_ParamSet **paramSet);

/**
 * @brief Adds parameters to a parameter set.
 *
 * @param paramSet Pointer to the parameter set to which parameters are to be added.
 * @param params Pointer to an array of parameters to add.
 * @param paramCnt Number of parameters to add.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>{@link OH_HUKS_SUCCESS} = 0: Operation successful.
 *     <br>{@link OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT} = 401: **params** is a null pointer or **paramSet** is invalid.
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_AddParams(struct OH_Huks_ParamSet *paramSet,
    const struct OH_Huks_Param *params, uint32_t paramCnt);

/**
 * @brief Builds a parameter set. After the parameter set is initialized and parameters are added, the parameter set is
 * serialized and the data of the BLOB type is copied to the adjacent memory area at the end of the **paramSet** struct.
 *
 * @param paramSet Double pointer to the parameter set to build.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS = 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401: **paramSet** is invalid.
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY = 12000014: Insufficient memory.
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_BuildParamSet(struct OH_Huks_ParamSet **paramSet);

/**
 * @brief Frees a parameter set.
 *
 * @param paramSet Pointer to the parameter set to free.
 * @since 9
 * @version 1.0
 */
void OH_Huks_FreeParamSet(struct OH_Huks_ParamSet **paramSet);

/**
 * @brief Copies a parameter set (deep copy).
 *
 * @param fromParamSet Pointer to the parameter set to copy.
 * @param fromParamSetSize Size of the memory occupied by the copied parameter set.
 * @param paramSet Double pointer to the new parameter set generated.
 * @return {@link OH_Huks_ErrCode} :
 *     <br>OH_HUKS_SUCCESS = 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401: **fromParamSet**, **fromParamSetSize**, or **paramSet** is invalid.
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY = 12000014: Insufficient memory.
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_CopyParamSet(const struct OH_Huks_ParamSet *fromParamSet,
    uint32_t fromParamSetSize, struct OH_Huks_ParamSet **paramSet);

/**
 * @brief Obtains a parameter from a parameter set.
 *
 * @param paramSet Indicates the pointer to the target parameter set.
 * @param tag Name of the parameter to obtain.
 * @param param Double pointer to the obtained parameter.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS = 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401: **paramSet** or **param** is invalid, or **param** is not in **
 *     paramSet**.
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_GetParam(const struct OH_Huks_ParamSet *paramSet, uint32_t tag,
    struct OH_Huks_Param **param);

/**
 * @brief Refreshes the {@link OH_Huks_Blob} data in the parameter set.
 *
 * @param paramSet Pointer to the parameter set to check.
 * @param isCopy If the value is **true**, the address of the {@link OH_Huks_Blob} data is refreshed and copied to the
 *     parameter set. If the value is **false**, only the address of the {@link OH_Huks_Blob} data is refreshed.
 * @return (capi-hukstypeapi-oh-huks-result.md) {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS = 0: Operation successful.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401: **paramSet** is invalid.
 *     <br>OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY = 12000014: Insufficient memory.
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_FreshParamSet(struct OH_Huks_ParamSet *paramSet, bool isCopy);

/**
 * @brief Checks whether the parameters in a parameter set are valid.
 *
 * @param paramSet Pointer to the parameter set to check.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS = 0: All parameters in **paramSet** are valid.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401: **paramSet** is invalid, or the parameter set contains invalid,
 *     duplicate, or incorrect tags.
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_IsParamSetTagValid(const struct OH_Huks_ParamSet *paramSet);

/**
 * @brief Checks whether a parameter set is of the valid size.
 *
 * @param paramSet Pointer to the parameter set to check.
 * @param size Memory size occupied by the parameter set.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS = 0: The size of the parameter set is valid.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401: **paramSet** is invalid.
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_IsParamSetValid(const struct OH_Huks_ParamSet *paramSet, uint32_t size);

/**
 * @brief Checks whether two parameters are the same.
 *
 * @param baseParam Pointer to the first parameter to compare.
 * @param param Pointer to the second parameter to compare.
 * @return {@link OH_Huks_ErrCode}:
 *     <br>OH_HUKS_SUCCESS = 0: The two parameters to be compared are the same.
 *     <br>OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401: One of the parameter sets is invalid, the parameters do not match,
 *     <br>or there is an invalid tag internally.
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result OH_Huks_CheckParamMatch(const struct OH_Huks_Param *baseParam, const struct OH_Huks_Param *param);

/**
 * @brief Destroys the parameter set of a key alias.
 *
 * @param keyAliasSet Pointer to the parameter set of the key alias to destroy.
 * @since 20
 * @version 1.0
 */
void OH_Huks_FreeKeyAliasSet(struct OH_Huks_KeyAliasSet *keyAliasSet);
#ifdef __cplusplus
}
#endif

/** @} */
#endif /* NATIVE_HUKS_PARAM_H */