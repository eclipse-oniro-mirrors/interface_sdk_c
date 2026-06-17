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
 * @addtogroup CryptoSymKeyApi
 * @{
 * @brief 描述OpenHarmony为应用提供的对称密钥相关接口。
 * @since 12
 */

/**
 * @file crypto_sym_key.h
 * @brief 定义对称密钥接口。
 * @syscap SystemCapability.Security.CryptoFramework
 * @library libohcrypto.so
 * @kit CryptoArchitectureKit
 * @since 12
 */

#ifndef CRYPTO_SYM_KEY_H
#define CRYPTO_SYM_KEY_H

#include "crypto_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 对称密钥结构体，表示对称密钥。
 * @since 12
 */
typedef struct OH_CryptoSymKey OH_CryptoSymKey;

/**
 * @brief 对称密钥生成器结构体，表示对称密钥生成器。
 * @since 12
 */
typedef struct OH_CryptoSymKeyGenerator OH_CryptoSymKeyGenerator;

/**
 * @brief 根据给定的算法名称创建对称密钥生成器。例如AES256。
 * @param algoName [in] 对称密钥算法名称，不能为NULL。取值如下：
 *     - 从API version 12开始支持"AES128"、"AES192"、"AES256"、"3DES192"、"HMAC|SHA1"、"HMAC|SHA224"、
 *     "HMAC|SHA256"、"HMAC|SHA384"、"HMAC|SHA512"、"HMAC|SM3"、"HMAC|MD5"。
 *     从API version 26.0.0开始支持"HMAC|SHA3-256"、"HMAC|SHA3-384"、"HMAC|SHA3-512"。
 *     - 从API version 12开始支持"SM4_128"。
 *     - 从API version 20开始支持"DES64"。
 *     - 从API version 22开始支持"ChaCha20"。
 *     - 从API version 26.0.0开始支持"RC2"、"RC4"、"Blowfish"、"CAST"。注意仅支持将对称密钥数据转换为对称密钥，不支持随机生成。
 * @param ctx [out] 指向对称密钥生成器指针的指针。ctx不能为NULL，*ctx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx为NULL或algoName为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_sym_key/OH_CryptoSymKeyGenerator_Destroy {ctx}
 * @since 12
 * @see {@link OH_CryptoSymKeyGenerator_Generate} 随机生成对称密钥。
 * @see {@link OH_CryptoSymKeyGenerator_Convert} 将对称密钥数据转换为对称密钥。
 */
OH_Crypto_ErrCode OH_CryptoSymKeyGenerator_Create(const char *algoName, OH_CryptoSymKeyGenerator **ctx);

/**
 * @brief 随机生成对称密钥。
 * @param ctx [in] 对称密钥生成器。不能为NULL。
 * @param keyCtx [out] 指向对称密钥指针的指针。keyCtx不能为NULL，*keyCtx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx或keyCtx为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_CALL} 无效的函数调用。可能的原因：算法不支持随机生成密钥
 *           （如RC2、RC4、Blowfish、CAST），请使用OH_CryptoSymKeyGenerator_Convert接口。[since 26.0.0]</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_sym_key/OH_CryptoSymKey_Destroy {keyCtx}
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoSymKeyGenerator_Generate(OH_CryptoSymKeyGenerator *ctx, OH_CryptoSymKey **keyCtx);

/**
 * @brief 将对称密钥数据转换为对称密钥。
 * @param ctx [in] 对称密钥生成器。不能为NULL。
 * @param keyData [in] 用于生成对称密钥的数据。不能为NULL。
 * @param keyCtx [out] 指向对称密钥指针的指针。keyCtx不能为NULL，*keyCtx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx、keyData或keyCtx为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_sym_key/OH_CryptoSymKey_Destroy {keyCtx}
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoSymKeyGenerator_Convert(OH_CryptoSymKeyGenerator *ctx,
    const Crypto_DataBlob *keyData, OH_CryptoSymKey **keyCtx);

/**
 * @brief 获取对称密钥生成器的算法名称。
 * @param ctx [in] 对称密钥生成器。不能为NULL。
 * @return 返回对称密钥算法名称，不需要调用者释放，在生成器销毁后不可使用。
 * @since 12
 */
const char *OH_CryptoSymKeyGenerator_GetAlgoName(OH_CryptoSymKeyGenerator *ctx);

/**
 * @brief 销毁对称密钥生成器。
 * @param ctx [in] 对称密钥生成器。
 * @since 12
 */
void OH_CryptoSymKeyGenerator_Destroy(OH_CryptoSymKeyGenerator *ctx);

/**
 * @brief 从对称密钥中获取对称密钥算法名称。
 * @param keyCtx [in] 对称密钥。不能为NULL。
 * @return 返回算法名称，不需要调用者释放，在密钥销毁后不可使用。
 * @since 12
 */
const char *OH_CryptoSymKey_GetAlgoName(OH_CryptoSymKey *keyCtx);

/**
 * @brief 从对称密钥中获取对称密钥数据。
 * @param keyCtx [in] 对称密钥。不能为NULL。
 * @param out [out] 指向用于存储密钥数据的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将out初始化为{0}，不要预分配out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} keyCtx或out为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoSymKey_GetKeyData(OH_CryptoSymKey *keyCtx, Crypto_DataBlob *out);

/**
 * @brief 销毁对称密钥。
 * @param keyCtx [in] 对称密钥。
 * @since 12
 */
void OH_CryptoSymKey_Destroy(OH_CryptoSymKey *keyCtx);

#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_SYM_KEY_H */
/** @} */
