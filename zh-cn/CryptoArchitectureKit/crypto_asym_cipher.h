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
 * @addtogroup CryptoAsymCipherApi
 * @{
 * @brief 描述OpenHarmony为应用提供的非对称加解密接口。
 * @since 20
 */

/**
 * @file crypto_asym_cipher.h
 * @brief 定义非对称加解密接口。
 * @syscap SystemCapability.Security.CryptoFramework
 * @library libohcrypto.so
 * @kit CryptoArchitectureKit
 * @since 20
 */

#ifndef CRYPTO_ASYM_CIPHER_H
#define CRYPTO_ASYM_CIPHER_H

#include "crypto_common.h"
#include "crypto_asym_key.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 非对称加解密结构体，表示非对称加解密上下文。
 * @since 20
 */
typedef struct OH_CryptoAsymCipher OH_CryptoAsymCipher;

/**
 * @brief 根据给定的算法名称创建非对称加解密上下文。
 * @param algoName [in] 非对称加解密算法名称，不能为NULL。取值如下：
 *     - RSA算法PKCS1填充模式：取值为"RSA|PKCS1"。
 *     - RSA算法OAEP填充模式：格式为"RSA|PKCS1_OAEP|摘要|MGF1摘要"，示例："RSA|PKCS1_OAEP|SHA256|MGF1_SHA256"。
 *     摘要支持"MD5"、"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"。
 *     MGF1摘要支持"MGF1_SHA1"、"MGF1_SHA224"、"MGF1_SHA256"、"MGF1_SHA384"、"MGF1_SHA512"。
 *     - RSA算法NoPadding填充模式：取值为"RSA|NoPadding"。
 *     - SM2算法：格式为"SM2|摘要"，示例："SM2|SM3"。
 *     摘要支持"MD5"、"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"、"SM3"。
 * @param ctx [out] 指向非对称加解密上下文指针的指针。ctx不能为NULL，*ctx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} algoName或ctx为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 加解密操作失败。</li>
 *         </ul>
 * @release crypto_asym_cipher/OH_CryptoAsymCipher_Destroy {ctx}
 * @since 20
 * @see {@link OH_CryptoAsymCipher_Init} 初始化非对称加解密上下文。
 */
OH_Crypto_ErrCode OH_CryptoAsymCipher_Create(const char *algoName, OH_CryptoAsymCipher **ctx);

/**
 * @brief 使用给定的加解密模式和密钥初始化非对称加解密上下文。
 * @param ctx [in] 非对称加解密上下文。不能为NULL。
 * @param mode [in] 加解密模式，加密或解密。
 * @param key [in] 非对称密钥。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或key为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 加解密初始化失败。</li>
 *         </ul>
 * @since 20
 * @see {@link OH_CryptoAsymCipher_Final} 结束加解密操作。
 */
OH_Crypto_ErrCode OH_CryptoAsymCipher_Init(OH_CryptoAsymCipher *ctx, Crypto_CipherMode mode, OH_CryptoKeyPair *key);

/**
 * @brief 结束加解密操作。
 * @param ctx [in] 非对称加解密上下文。不能为NULL。
 * @param in [in] 待加密或解密的数据。不能为NULL。
 * @param out [out] 指向用于存储加密或解密结果的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将out初始化为{0}，不要预分配
 *     out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx、in或out为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 加解密完成失败。可能的原因：RSA加密时明文超过密钥长度和填充模式允许
 *         的最大长度；RSA解密时密钥错误或密文损坏；SM2解密时密钥错误或密文损坏；SM2密文的ASN.1结构无效。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoAsymCipher_Final(OH_CryptoAsymCipher *ctx, const Crypto_DataBlob *in, Crypto_DataBlob *out);

/**
 * @brief 销毁非对称加解密上下文。
 * @param ctx [in] 非对称加解密上下文。
 * @since 20
 */
void OH_CryptoAsymCipher_Destroy(OH_CryptoAsymCipher *ctx);

/**
 * @brief SM2密文规格结构体，表示SM2密文规格。
 * @since 20
 */
typedef struct OH_CryptoSm2CiphertextSpec OH_CryptoSm2CiphertextSpec;

/**
 * @brief 定义SM2密文规格项类型。
 * @since 20
 */
typedef enum {
    /**
     * @brief 公钥x，也称为C1x。
     * @since 20
     */
    CRYPTO_SM2_CIPHERTEXT_C1_X = 0,
    /**
     * @brief 公钥y，也称为C1y。
     * @since 20
     */
    CRYPTO_SM2_CIPHERTEXT_C1_Y = 1,
    /**
     * @brief 密文数据，也称为C2。
     * @since 20
     */
    CRYPTO_SM2_CIPHERTEXT_C2 = 2,
    /**
     * @brief 消息摘要（哈希值），也称为C3。
     * @since 20
     */
    CRYPTO_SM2_CIPHERTEXT_C3 = 3,
} CryptoSm2CiphertextSpec_item;

/**
 * @brief 创建SM2密文规格。
 * @param sm2Ciphertext [in] DER格式的SM2密文，如果为NULL则创建空的SM2密文规格。
 * @param spec [out] 指向SM2密文规格指针的指针。spec不能为NULL，*spec必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} spec为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 解析SM2密文失败。可能的原因：输入数据不是有效的DER编码SM2密文。</li>
 *         </ul>
 * @release crypto_asym_cipher/OH_CryptoSm2CiphertextSpec_Destroy {spec}
 * @since 20
 * @see {@link OH_CryptoSm2CiphertextSpec_GetItem} 获取SM2密文的指定项。
 * @see {@link OH_CryptoSm2CiphertextSpec_SetItem} 设置SM2密文规格的指定项。
 */
OH_Crypto_ErrCode OH_CryptoSm2CiphertextSpec_Create(Crypto_DataBlob *sm2Ciphertext, OH_CryptoSm2CiphertextSpec **spec);

/**
 * @brief 获取SM2密文的指定项。
 * @param spec [in] SM2密文规格。不能为NULL。
 * @param item [in] SM2密文规格项。
 * @param out [out] 指向用于存储输出数据的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将out初始化为{0}，不要预分配out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} spec或out为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 加解密操作失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoSm2CiphertextSpec_GetItem(OH_CryptoSm2CiphertextSpec *spec,
    CryptoSm2CiphertextSpec_item item, Crypto_DataBlob *out);

/**
 * @brief 设置SM2密文规格的指定项。
 * @param spec [in] SM2密文规格。不能为NULL。
 * @param item [in] SM2密文规格项。
 * @param in [in] 输入数据。不能为NULL。本接口会对输入数据进行深拷贝，调用者在接口返回后可立即释放in。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} spec或in为NULL、in->data为NULL或in->len为0。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 深拷贝的内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 加解密操作失败。</li>
 *         </ul>
 * @since 20
 * @see {@link OH_CryptoSm2CiphertextSpec_Encode} 将SM2密文规格编码为DER格式密文。
 */
OH_Crypto_ErrCode OH_CryptoSm2CiphertextSpec_SetItem(OH_CryptoSm2CiphertextSpec *spec,
    CryptoSm2CiphertextSpec_item item, Crypto_DataBlob *in);

/**
 * @brief 将SM2密文规格编码为DER格式密文。
 * @param spec [in] SM2密文规格。不能为NULL。
 * @param out [out] 指向用于存储编码数据的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将out初始化为{0}，不要预分配out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} spec或out为NULL，
 *            或SM2密文字段（C1X、C1Y、C2、C3）未设置，或C3（hashData）长度不为32字节。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 编码失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoSm2CiphertextSpec_Encode(OH_CryptoSm2CiphertextSpec *spec, Crypto_DataBlob *out);

/**
 * @brief 销毁SM2密文规格。
 * @param spec [in] SM2密文规格。
 * @since 20
 */
void OH_CryptoSm2CiphertextSpec_Destroy(OH_CryptoSm2CiphertextSpec *spec);

#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_ASYM_CIPHER_H */
/** @} */
