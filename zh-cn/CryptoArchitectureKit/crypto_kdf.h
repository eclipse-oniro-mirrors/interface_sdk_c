/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
 * @addtogroup CryptoKdfApi
 * @{
 * @brief 描述OpenHarmony为应用提供的密钥派生(KDF)接口。
 * @since 20
 */

/**
 * @file crypto_kdf.h
 * @brief 定义密钥派生接口。
 * @syscap SystemCapability.Security.CryptoFramework
 * @library libohcrypto.so
 * @kit CryptoArchitectureKit
 * @since 20
 */

#ifndef CRYPTO_KDF_H
#define CRYPTO_KDF_H

#include "crypto_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief KDF结构体，表示KDF上下文。
 * @since 20
 */
typedef struct OH_CryptoKdf OH_CryptoKdf;

/**
 * @brief KDF参数结构体，表示KDF参数。
 * @since 20
 */
typedef struct OH_CryptoKdfParams OH_CryptoKdfParams;

/**
 * @brief 定义KDF参数类型。
 * @since 20
 */
typedef enum {
    /**
     * @brief 表示KDF的密钥或密码。
     * @since 20
     */
    CRYPTO_KDF_KEY_DATABLOB = 0,

    /**
     * @brief 表示KDF的盐值。
     * @since 20
     */
    CRYPTO_KDF_SALT_DATABLOB = 1,

    /**
     * @brief 表示KDF的Info信息。
     * @since 20
     */
    CRYPTO_KDF_INFO_DATABLOB = 2,

    /**
     * @brief 表示PBKDF2的迭代次数。
     * @since 20
     */
    CRYPTO_KDF_ITER_COUNT_INT = 3,

    /**
     * @brief 表示SCRYPT KDF的n参数。
     * @since 20
     */
    CRYPTO_KDF_SCRYPT_N_UINT64 = 4,

    /**
     * @brief 表示SCRYPT KDF的r参数。
     * @since 20
     */
    CRYPTO_KDF_SCRYPT_R_UINT64 = 5,

    /**
     * @brief 表示SCRYPT KDF的p参数。
     * @since 20
     */
    CRYPTO_KDF_SCRYPT_P_UINT64 = 6,

    /**
     * @brief 表示SCRYPT KDF的最大内存参数。
     * @since 20
     */
    CRYPTO_KDF_SCRYPT_MAX_MEM_UINT64 = 7,
} CryptoKdf_ParamType;

/**
 * @brief 创建KDF参数。
 * @param algoName [in] KDF参数算法名称，不能为NULL。取值如下：
 *     - 从API version 20开始支持"HKDF"、"PBKDF2"、"SCRYPT"。
 *     - 从API version 22开始支持"X963KDF"。
 * @param params [out] 指向KDF参数指针的指针。params不能为NULL，*params必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} algoName或params为NULL，
 *            或者algoName不是支持的KDF类型。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_kdf/OH_CryptoKdfParams_Destroy {params}
 * @since 20
 * @see {@link OH_CryptoKdfParams_SetParam} 设置KDF参数。
 */
OH_Crypto_ErrCode OH_CryptoKdfParams_Create(const char *algoName, OH_CryptoKdfParams **params);

/**
 * @brief 设置KDF参数。
 * @param params [in] KDF参数。不能为NULL。
 * @param type [in] KDF参数类型。
 * @param value [in] KDF参数值。本接口会对value中的数据进行深拷贝，调用者在接口返回后可立即释放value。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} params或value为NULL，
 *            value->data为NULL，或者type对于KDF算法无效。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 参数拷贝内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoKdfParams_SetParam(OH_CryptoKdfParams *params, CryptoKdf_ParamType type,
    Crypto_DataBlob *value);

/**
 * @brief 销毁KDF参数。
 * @param params [in] KDF参数。
 * @since 20
 */
void OH_CryptoKdfParams_Destroy(OH_CryptoKdfParams *params);

/**
 * @brief 根据给定的算法名称创建KDF上下文。
 * @param algoName [in] KDF算法名称。不能为NULL。格式为"KDF类型|摘要算法"，取值如下：
 *     - 从API version 20开始支持"PBKDF2|SHA1"、"PBKDF2|SHA224"、"PBKDF2|SHA256"、
 *     "PBKDF2|SHA384"、"PBKDF2|SHA512"、"PBKDF2|SM3"。
 *     从API version 26.0.0开始支持"PBKDF2|SHA3-256"、"PBKDF2|SHA3-384"、"PBKDF2|SHA3-512"。
 *     - 从API version 20开始支持"HKDF|SHA1"、"HKDF|SHA224"、"HKDF|SHA256"、"HKDF|SHA384"、"HKDF|SHA512"、"HKDF|SM3"。
 *     HKDF支持可选的第三个参数指定模式："EXTRACT_AND_EXPAND"（默认）、
 *     "EXTRACT_ONLY"、"EXPAND_ONLY"，示例："HKDF|SHA256|EXTRACT_ONLY"。
 *     从API version 26.0.0开始支持"HKDF|SHA3-256"、"HKDF|SHA3-384"、"HKDF|SHA3-512"。
 *     - 从API version 20开始支持"SCRYPT"。
 *     - 从API version 22开始支持"X963KDF|SHA1"、"X963KDF|SHA224"、
 *     "X963KDF|SHA256"、"X963KDF|SHA384"、"X963KDF|SHA512"。
 *     从API version 26.0.0开始支持"X963KDF|SHA3-256"、"X963KDF|SHA3-384"、"X963KDF|SHA3-512"。
 * @param ctx [out] 指向KDF上下文指针的指针。ctx不能为NULL，*ctx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} algoName或ctx为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_kdf/OH_CryptoKdf_Destroy {ctx}
 * @since 20
 * @see {@link OH_CryptoKdf_Derive} 派生密钥。
 */
OH_Crypto_ErrCode OH_CryptoKdf_Create(const char *algoName, OH_CryptoKdf **ctx);

/**
 * @brief 派生密钥。
 * @param ctx [in] KDF上下文。不能为NULL。
 * @param params [in] KDF参数。不能为NULL。
 * @param keyLen [in] 派生密钥的字节长度。
 * @param key [out] 指向用于存储派生密钥的Crypto_DataBlob结构体的指针。不能为NULL。 调用前需将key初始化为{0}，不要预分配
 *     key->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx、params或key为NULL，
 *            或者keyLen小于等于0，或者缺少必需的参数（如HKDF的密钥、Scrypt的密码或盐值）。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密钥派生失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {key}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoKdf_Derive(OH_CryptoKdf *ctx, const OH_CryptoKdfParams *params, int keyLen,
    Crypto_DataBlob *key);

/**
 * @brief 销毁KDF上下文。
 * @param ctx [in] KDF上下文。
 * @since 20
 */
void OH_CryptoKdf_Destroy(OH_CryptoKdf *ctx);

#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_KDF_H */
/** @} */
