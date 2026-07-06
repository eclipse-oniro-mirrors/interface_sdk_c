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
 * @addtogroup CryptoDigestApi
 * @{
 * @brief 描述OpenHarmony为应用提供的摘要算法接口。
 * @since 12
 */

/**
 * @file crypto_digest.h
 * @brief 定义摘要算法接口。
 * @syscap SystemCapability.Security.CryptoFramework
 * @library libohcrypto.so
 * @kit CryptoArchitectureKit
 * @since 12
 */

#ifndef CRYPTO_DIGEST_H
#define CRYPTO_DIGEST_H

#include "crypto_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 摘要结构体，表示摘要上下文。
 * @since 12
 */
typedef struct OH_CryptoDigest OH_CryptoDigest;

/**
 * @brief 根据给定的算法名称创建摘要上下文。
 * @param algoName [in] 摘要算法名称，不能为NULL。取值如下：
 *     - 从API version 12开始支持"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"、"MD5"、"SM3"。
 *     - 从API version 22开始支持"SHA3-256"、"SHA3-384"、"SHA3-512"。
 * @param ctx [out] 指向摘要上下文指针的指针。ctx不能为NULL，*ctx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx为NULL、algoName为NULL、或algoName不是支持的摘要算法名称。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 摘要操作失败。</li>
 *         </ul>
 * @release crypto_digest/OH_DigestCrypto_Destroy {ctx}
 * @since 12
 * @see {@link OH_CryptoDigest_Update} 更新摘要数据。
 */
OH_Crypto_ErrCode OH_CryptoDigest_Create(const char *algoName, OH_CryptoDigest **ctx);

/**
 * @brief 更新摘要数据。
 * @param ctx [in] 摘要上下文。不能为NULL。
 * @param in [in] 待计算摘要的数据。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx或in为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 摘要更新失败。</li>
 *         </ul>
 * @since 12
 * @see {@link OH_CryptoDigest_Final} 完成摘要操作，输出摘要结果。
 */
OH_Crypto_ErrCode OH_CryptoDigest_Update(OH_CryptoDigest *ctx, Crypto_DataBlob *in);

/**
 * @brief 完成摘要操作，输出摘要结果。
 * @param ctx [in] 摘要上下文。不能为NULL。
 * @param out [out] 指向用于存储摘要结果的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将out初始化为{0}，不要预分配out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx或out为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 摘要完成操作失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoDigest_Final(OH_CryptoDigest *ctx, Crypto_DataBlob *out);

/**
 * @brief 获取摘要结果的长度。
 * @param ctx [in] 摘要上下文。不能为NULL。
 * @return 返回摘要结果的字节长度。 特殊说明：如果输入参数ctx为NULL，返回401；其他失败场景返回0。
 * @since 12
 */
uint32_t OH_CryptoDigest_GetLength(OH_CryptoDigest *ctx);

/**
 * @brief 获取摘要上下文的算法名称。
 * @param ctx [in] 摘要上下文。不能为NULL。
 * @return 返回摘要算法名称，不需要调用者释放，在上下文销毁后不可使用。
 * @since 12
 */
const char *OH_CryptoDigest_GetAlgoName(OH_CryptoDigest *ctx);

/**
 * @brief 销毁摘要上下文。
 * @param ctx [in] 摘要上下文。
 * @since 12
 */
void OH_DigestCrypto_Destroy(OH_CryptoDigest *ctx);

#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_DIGEST_H */
/** @} */
