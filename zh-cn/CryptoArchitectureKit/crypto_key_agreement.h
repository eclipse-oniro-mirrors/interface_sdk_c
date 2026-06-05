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
 * @addtogroup CryptoKeyAgreementApi
 * @{
 * @brief 描述OpenHarmony为应用提供的密钥协商接口。
 * @since 20
 */

/**
 * @file crypto_key_agreement.h
 * @brief 定义密钥协商接口。
 * @syscap SystemCapability.Security.CryptoFramework
 * @library libohcrypto.so
 * @kit CryptoArchitectureKit
 * @since 20
 */

#ifndef CRYPTO_KEY_AGREEMENT_H
#define CRYPTO_KEY_AGREEMENT_H

#include "crypto_common.h"
#include "crypto_asym_key.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 密钥协商结构体，表示密钥协商上下文。
 * @since 20
 */
typedef struct OH_CryptoKeyAgreement OH_CryptoKeyAgreement;

/**
 * @brief 根据给定的算法名称创建密钥协商上下文。
 * @param algoName [in] 密钥协商算法名称，不能为NULL。取值如下：
 *     - 从API version 20开始支持ECDH系列："ECC224"、"ECC256"、"ECC384"、"ECC521"。
 *     - 从API version 20开始支持ECDH BrainPool系列："ECC_BrainPoolP160r1"、"ECC_BrainPoolP160t1"、
 *     "ECC_BrainPoolP192r1"、"ECC_BrainPoolP192t1"、"ECC_BrainPoolP224r1"、"ECC_BrainPoolP224t1"、
 *     "ECC_BrainPoolP256r1"、"ECC_BrainPoolP256t1"、"ECC_BrainPoolP320r1"、"ECC_BrainPoolP320t1"、
 *     "ECC_BrainPoolP384r1"、"ECC_BrainPoolP384t1"、"ECC_BrainPoolP512r1"、"ECC_BrainPoolP512t1"。
 *     - 从API version 20开始支持"ECC_Secp256k1"。
 *     - 从API version 20开始支持"X25519"。
 *     - 从API version 20开始支持DH系列："DH_modp1536"、"DH_modp2048"、"DH_modp3072"、"DH_modp4096"、
 *     "DH_modp6144"、"DH_modp8192"、"DH_ffdhe2048"、"DH_ffdhe3072"、"DH_ffdhe4096"、
 *     "DH_ffdhe6144"、"DH_ffdhe8192"。
 *     - 从API version 26.0.0开始支持"ECC192"。
 * @param ctx [out] 指向密钥协商上下文指针的指针。ctx不能为NULL，*ctx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} algoName或ctx为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密钥协商操作失败。</li>
 *         </ul>
 * @release crypto_key_agreement/OH_CryptoKeyAgreement_Destroy {ctx}
 * @since 20
 * @see {@link OH_CryptoKeyAgreement_GenerateSecret} 生成共享秘密值。
 */
OH_Crypto_ErrCode OH_CryptoKeyAgreement_Create(const char *algoName, OH_CryptoKeyAgreement **ctx);

/**
 * @brief 生成共享秘密值。
 * @param ctx [in] 密钥协商上下文。不能为NULL。
 * @param privkey [in] 私钥。不能为NULL。
 * @param pubkey [in] 公钥。不能为NULL。
 * @param secret [out] 指向用于存储共享秘密值的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将secret初始化为{0}，不要预分配secret->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx、privkey、pubkey或secret为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密钥协商操作失败。可能的原因：公钥和私钥不属于同一曲线或算法，或公钥数据无效。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {secret}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoKeyAgreement_GenerateSecret(OH_CryptoKeyAgreement *ctx, OH_CryptoPrivKey *privkey,
    OH_CryptoPubKey *pubkey, Crypto_DataBlob *secret);

/**
 * @brief 销毁密钥协商上下文。
 * @param ctx [in] 密钥协商上下文。
 * @since 20
 */
void OH_CryptoKeyAgreement_Destroy(OH_CryptoKeyAgreement *ctx);

#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_KEY_AGREEMENT_H */
/** @} */
