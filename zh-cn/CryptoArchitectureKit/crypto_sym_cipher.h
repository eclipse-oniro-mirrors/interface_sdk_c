/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @addtogroup CryptoSymCipherApi
 * @{
 * @brief 描述OpenHarmony为应用提供的对称密钥加解密接口。
 * @since 12
 */

/**
 * @file crypto_sym_cipher.h
 * @brief 定义对称密钥加解密接口。
 * @syscap SystemCapability.Security.CryptoFramework
 * @library libohcrypto.so
 * @kit CryptoArchitectureKit
 * @since 12
 */

#ifndef CRYPTO_SYM_CIPHER_H
#define CRYPTO_SYM_CIPHER_H

#include "crypto_common.h"
#include "crypto_sym_key.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义加解密参数类型。
 * @since 12
 */
typedef enum {
    /**
     * @brief 初始化向量(IV)参数。
     * @since 12
     */
    CRYPTO_IV_DATABLOB = 100,
    /**
     * @brief AEAD模式（如GCM、CCM）下的附加认证数据(AAD)。
     * @since 12
     */
    CRYPTO_AAD_DATABLOB = 101,
    /**
     * @brief AEAD模式（如GCM、CCM）中的认证标签(Tag)，用于数据完整性校验。
     * @since 12
     */
    CRYPTO_TAG_DATABLOB = 102,
} CryptoSymCipher_ParamsType;

/**
 * @brief 对称密钥加解密结构体，表示对称密钥加解密上下文。
 * @since 12
 */
typedef struct OH_CryptoSymCipher OH_CryptoSymCipher;

/**
 * @brief 对称密钥加解密参数结构体，表示对称密钥加解密参数。
 * @since 12
 */
typedef struct OH_CryptoSymCipherParams OH_CryptoSymCipherParams;

/**
 * @brief 创建对称密钥加解密参数。
 * @param params [out] 指向加解密参数指针的指针。params不能为NULL，*params必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} params为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 加解密操作失败。</li>
 *         </ul>
 * @release crypto_sym_cipher/OH_CryptoSymCipherParams_Destroy {params}
 * @since 12
 * @see {@link OH_CryptoSymCipherParams_SetParam} 设置加解密参数。
 */
OH_Crypto_ErrCode OH_CryptoSymCipherParams_Create(OH_CryptoSymCipherParams **params);

/**
 * @brief 设置加解密参数。
 * @param params [in] 加解密参数。不能为NULL。
 * @param paramsType [in] 设置的加解密参数类型。
 * @param value [in] 参数值。本接口为浅拷贝，不会复制value中的数据。 调用者必须确保value指向的内存在{@link OH_CryptoSymCipher_Init}
 *     调用完成前保持有效。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} params或value为NULL，或paramsType无法识别。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 加解密操作失败。</li>
 *         </ul>
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoSymCipherParams_SetParam(OH_CryptoSymCipherParams *params,
    CryptoSymCipher_ParamsType paramsType, Crypto_DataBlob *value);

/**
 * @brief 销毁加解密参数。
 * @param params [in] 加解密参数。
 * @since 12
 */
void OH_CryptoSymCipherParams_Destroy(OH_CryptoSymCipherParams *params);

/**
 * @brief 根据给定的算法名称创建对称密钥加解密上下文。
 * @param algoName [in] 对称加解密算法名称，不能为NULL。格式为"算法|模式|填充"，各部分以"|"分隔。
 *     算法包括：AES128、AES192、AES256、SM4_128、3DES192、DES64、ChaCha20、RC2、Blowfish、CAST。
 *     模式包括：ECB、CBC、CTR、OFB、CFB、CFB1、CFB8、CFB64、CFB128、GCM、CCM、XTS、Poly1305。
 *     填充包括：NoPadding、PKCS5、PKCS7。
 *     各算法支持情况如下：
 *     - 从API version 12开始支持AES系列：AES128、AES192、AES256算法，ECB、CBC、CTR、OFB、CFB、GCM、CCM模式，填充为NoPadding、
 *     PKCS7。 示例："AES128|GCM"、"AES256|CBC|PKCS7"。
 *     - 从API version 12开始支持3DES系列：3DES192算法，ECB、CBC、OFB、CFB模式，填充为NoPadding、PKCS5、PKCS7。
 *     示例："3DES192|CBC|PKCS5"。
 *     - 从API version 12开始支持SM4系列：SM4_128算法，ECB、CBC、CTR、OFB、CFB、CFB128、GCM模式，填充为NoPadding、PKCS7。
 *     示例："SM4_128|CBC|PKCS7"、"SM4_128|GCM|NoPadding"。
 *     - 从API version 20开始支持DES系列：DES64算法，ECB、CBC、OFB、CFB模式，填充为NoPadding、PKCS5、PKCS7。
 *     示例："DES64|CBC|PKCS5"。
 *     - 从API version 22开始支持AES128_WRAP、AES192_WRAP、AES256_WRAP算法。 示例："AES128_WRAP"、"AES192_WRAP"、
 *     "AES256_WRAP"。
 *     - 从API version 22开始支持"ChaCha20"、"ChaCha20|Poly1305"。 示例："ChaCha20|Poly1305"、"ChaCha20"。
 *     - 从API version 26.0.0开始支持AES算法，XTS模式。 示例："AES128|XTS"、"AES256|XTS"。注意不支持AES192。
 *     - 从API version 26.0.0开始支持RC2算法，ECB、CBC、OFB、CFB模式，填充为NoPadding、PKCS5、PKCS7。 示例："RC2|CBC|PKCS5"。
 *     - 从API version 26.0.0开始支持"RC4"。 示例："RC4"。
 *     - 从API version 26.0.0开始支持Blowfish算法，ECB、CBC、OFB、CFB模式，填充为NoPadding、PKCS5、PKCS7。
 *     示例："Blowfish|CBC|PKCS5"。
 *     - 从API version 26.0.0开始支持CAST算法，ECB、CBC、OFB、CFB模式，填充为NoPadding、PKCS5、PKCS7。 示例："CAST|CBC|PKCS5"。
 *     填充说明：
 *     - ECB、CBC模式涉及填充：当明文长度不是算法分组大小的整数倍时，必须使用PKCS5或PKCS7填充；使用NoPadding时，输入数据
 *     长度必须是算法分组大小的整数倍（AES和SM4为16字节，DES、3DES、RC2、Blowfish和CAST为8字节）。
 *     - CTR、OFB、CFB、CFB1、CFB8、CFB64、CFB128、GCM、CCM模式将分组密码转化为流模式，不需要填充，指定任意填充均按NoPadding处理。
 *     - XTS模式不涉及填充，不需要指定填充字段，指定任意填充均按NoPadding处理。
 *     - ChaCha20为流密码算法，不需要指定填充字段，指定任意填充均按NoPadding处理。
 * @param ctx [out] 指向对称密钥加解密上下文指针的指针。ctx不能为NULL，*ctx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx为NULL或algoName为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} 参数无效。 [since 20]</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 加解密操作失败。</li>
 *         </ul>
 * @release crypto_sym_cipher/OH_CryptoSymCipher_Destroy {ctx}
 * @since 12
 * @see {@link OH_CryptoSymCipher_Init} 使用给定的加解密模式、密钥和参数初始化加解密操作。
 */
OH_Crypto_ErrCode OH_CryptoSymCipher_Create(const char *algoName, OH_CryptoSymCipher **ctx);

/**
 * @brief 使用给定的加解密模式、密钥和参数初始化加解密操作。
 * @param ctx [in] 对称密钥加解密上下文。不能为NULL。
 * @param mod [in] 加解密模式，加密或解密。
 * @param key [in] 对称密钥。不能为NULL。
 * @param params [in] 算法参数，例如IV。ECB模式下需为NULL，其他模式不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx或key为NULL，或非ECB模式下IV缺失或长度错误。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} 参数无效。 [since 20]</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 加解密初始化失败。可能的原因：密钥长度与算法不匹配。</li>
 *         </ul>
 * @since 12
 * @see {@link OH_CryptoSymCipher_Update} 更新加解密数据，输出已加密或已解密的数据。
 * @see {@link OH_CryptoSymCipher_Final} 结束加解密操作，输出最终结果。
 */
OH_Crypto_ErrCode OH_CryptoSymCipher_Init(OH_CryptoSymCipher *ctx, Crypto_CipherMode mod,
    OH_CryptoSymKey *key, OH_CryptoSymCipherParams *params);

/**
 * @brief 更新加解密数据，输出已加密或已解密的数据。
 * @param ctx [in] 对称密钥加解密上下文。不能为NULL。
 * @param in [in] 待加密或解密的数据。不能为NULL。
 * @param out [out] 指向用于存储更新数据的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将out初始化为{0}，不要预分配out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx、in或out为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} 参数无效。 [since 20]</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 加解密更新失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 12
 * @see {@link OH_CryptoSymCipher_Final} 结束加解密操作，输出最终结果。
 */
OH_Crypto_ErrCode OH_CryptoSymCipher_Update(OH_CryptoSymCipher *ctx, Crypto_DataBlob *in, Crypto_DataBlob *out);

/**
 * @brief 结束加解密操作，输出最终结果。
 * @param ctx [in] 对称密钥加解密上下文。不能为NULL。
 * @param in [in] 待加密或解密的数据。如果数据已通过{@link OH_CryptoSymCipher_Update}接口更新了所有数据，此参数可以为NULL。
 * @param out [out] 指向用于存储最终结果的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将out初始化为{0}，不要预分配out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx或out为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} 参数无效。 [since 20]</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 加解密完成失败。可能的原因：解密时IV或密钥错误；AEAD（GCM/CCM）
 *         认证标签验证失败（TAG、AAD、密文或密钥错误）；分组密码（如AES-CBC/ECB）解密时密文长度不是分组大小的整数倍；分组密码使用NoPadding
 *         加密时明文长度不是分组大小的整数倍。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoSymCipher_Final(OH_CryptoSymCipher *ctx, Crypto_DataBlob *in, Crypto_DataBlob *out);

/**
 * @brief 获取对称密钥加解密算法名称。
 * @param ctx [in] 对称密钥加解密上下文。不能为NULL。
 * @return 返回对称密钥加解密算法名称，不需要调用者释放，在上下文销毁后不可使用。
 * @since 12
 */
const char *OH_CryptoSymCipher_GetAlgoName(OH_CryptoSymCipher *ctx);

/**
 * @brief 销毁对称密钥加解密上下文。
 * @param ctx [in] 对称密钥加解密上下文。
 * @since 12
 */
void OH_CryptoSymCipher_Destroy(OH_CryptoSymCipher *ctx);

#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_SYM_CIPHER_H */
/** @} */
