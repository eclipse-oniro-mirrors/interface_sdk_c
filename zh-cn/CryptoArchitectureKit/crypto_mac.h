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
 * @addtogroup CryptoMacApi
 * @{
 * @brief 描述OpenHarmony为应用提供的消息认证码(MAC)接口。
 * @since 20
 */

/**
 * @file crypto_mac.h
 * @brief 定义消息认证码接口。
 * @syscap SystemCapability.Security.CryptoFramework
 * @library libohcrypto.so
 * @kit CryptoArchitectureKit
 * @since 20
 */

#ifndef CRYPTO_MAC_H
#define CRYPTO_MAC_H

#include "crypto_common.h"
#include "crypto_sym_key.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief MAC结构体，表示MAC上下文。
 * @since 20
 */
typedef struct OH_CryptoMac OH_CryptoMac;

/**
 * @brief 定义MAC算法参数类型。
 * @since 20
 */
typedef enum {
    /**
     * @brief HMAC的消息摘要算法名称，通过{@link OH_CryptoMac_SetParam}设置。
     * 取值："SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"、"SM3"、"MD5"。
     * 从API version 26.0.0开始支持"SHA3-256"、"SHA3-384"、"SHA3-512"。
     * @since 20
     */
    CRYPTO_MAC_DIGEST_NAME_STR = 0,

    /**
     * @brief CMAC的对称加密算法名称，通过{@link OH_CryptoMac_SetParam}设置。
     * 取值："AES128"、"AES256"。
     * @since 20
     */
    CRYPTO_MAC_CIPHER_NAME_STR = 1,
} CryptoMac_ParamType;

/**
 * @brief 根据给定的算法名称创建MAC上下文。
 * @param algoName [in] MAC算法名称，不能为NULL。支持“HMAC”和“CMAC”。
 * @param ctx [out] 指向MAC上下文指针的指针。ctx不能为NULL，*ctx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} algoName或ctx为NULL，或algoName不是"HMAC"或"CMAC"。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_mac/OH_CryptoMac_Destroy {ctx}
 * @since 20
 * @see {@link OH_CryptoMac_SetParam} 设置MAC上下文的指定参数。
 */
OH_Crypto_ErrCode OH_CryptoMac_Create(const char *algoName, OH_CryptoMac **ctx);

/**
 * @brief 设置MAC上下文的指定参数。
 * @param ctx [in] MAC上下文。不能为NULL。
 * @param type [in] MAC参数类型。
 * @param value [in] 参数值。本接口会对value中的数据进行深拷贝，调用者在接口返回后可立即释放value。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx、value或value->data为NULL，
 *            type对当前MAC算法无效，或摘要/加密算法名称不支持。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 参数拷贝内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @since 20
 * @see {@link OH_CryptoMac_Init} 使用对称密钥初始化MAC上下文。
 */
OH_Crypto_ErrCode OH_CryptoMac_SetParam(OH_CryptoMac *ctx, CryptoMac_ParamType type, const Crypto_DataBlob *value);

/**
 * @brief 使用对称密钥初始化MAC上下文。
 * @param ctx [in] MAC上下文。不能为NULL。
 * @param key [in] 对称密钥。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或key为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} MAC初始化失败。可能的原因：密钥长度与算法不匹配
 *           （例如CMAC使用AES-128需要16字节密钥）。</li>
 *         </ul>
 * @since 20
 * @see {@link OH_CryptoMac_Update} 更新MAC数据。
 */
OH_Crypto_ErrCode OH_CryptoMac_Init(OH_CryptoMac *ctx, const OH_CryptoSymKey *key);

/**
 * @brief 更新MAC数据。
 * @param ctx [in] MAC上下文。不能为NULL。
 * @param in [in] 待更新的数据。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或in为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} MAC更新失败。</li>
 *         </ul>
 * @since 20
 * @see {@link OH_CryptoMac_Final} 结束MAC操作。
 */
OH_Crypto_ErrCode OH_CryptoMac_Update(OH_CryptoMac *ctx, const Crypto_DataBlob *in);

/**
 * @brief 结束MAC操作。
 * @param ctx [in] MAC上下文。不能为NULL。
 * @param out [out] 指向用于存储MAC结果的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将out初始化为{0}，不要预分配out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或out为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} MAC完成操作失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoMac_Final(OH_CryptoMac *ctx, Crypto_DataBlob *out);

/**
 * @brief 获取MAC结果的长度。
 * @param ctx [in] MAC上下文。不能为NULL。
 * @param length [out] MAC结果的字节长度。不能为NULL。由调用者分配内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或length为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoMac_GetLength(OH_CryptoMac *ctx, uint32_t *length);

/**
 * @brief 销毁MAC上下文。
 * @param ctx [in] MAC上下文。
 * @since 20
 */
void OH_CryptoMac_Destroy(OH_CryptoMac *ctx);

#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_MAC_H */
/** @} */
