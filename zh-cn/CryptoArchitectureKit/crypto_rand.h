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
 * @addtogroup CryptoRandApi
 * @{
 * @brief 描述OpenHarmony为应用提供的随机数生成接口。
 * @since 20
 */

/**
 * @file crypto_rand.h
 * @brief 定义随机数生成器接口。
 * @syscap SystemCapability.Security.CryptoFramework
 * @library libohcrypto.so
 * @kit CryptoArchitectureKit
 * @since 20
 */

#ifndef CRYPTO_RAND_H
#define CRYPTO_RAND_H

#include "crypto_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 随机数生成器结构体，表示随机数生成器上下文。
 * @since 20
 */
typedef struct OH_CryptoRand OH_CryptoRand;

/**
 * @brief 创建随机数生成器上下文。
 * @param ctx [out] 指向随机数生成器上下文指针的指针。ctx不能为NULL，*ctx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_rand/OH_CryptoRand_Destroy {ctx}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoRand_Create(OH_CryptoRand **ctx);

/**
 * @brief 生成随机数。
 * @param ctx [in] 随机数生成器上下文。不能为NULL。
 * @param len [in] 随机数的字节长度。
 * @param out [out] 指向用于存储随机数的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将out初始化为{0}，不要预分配out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或out为NULL，或len小于等于0。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoRand_GenerateRandom(OH_CryptoRand *ctx, int len, Crypto_DataBlob *out);

/**
 * @brief 获取随机数生成器的算法名称。
 * @param ctx [in] 随机数生成器上下文。不能为NULL。
 * @return 返回随机数生成器的算法名称，不需要调用者释放，上下文销毁后不可使用。
 * @since 20
 */
const char *OH_CryptoRand_GetAlgoName(OH_CryptoRand *ctx);

/**
 * @brief 设置随机数生成器的种子。
 * @param ctx [in] 随机数生成器上下文。不能为NULL。
 * @param seed [in] 种子数据。本接口会对seed中的数据进行深拷贝，调用者在接口返回后可立即释放seed。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx为NULL，
 *            或seed无效（seed为NULL、seed->data为NULL、seed->len为0、或seed->len超过INT_MAX）。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoRand_SetSeed(OH_CryptoRand *ctx, Crypto_DataBlob *seed);

/**
 * @brief 启用硬件熵源。
 * @param ctx [in] 随机数生成器上下文。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @since 21
 */
OH_Crypto_ErrCode OH_CryptoRand_EnableHardwareEntropy(OH_CryptoRand *ctx);

/**
 * @brief 销毁随机数生成器上下文。
 * @param ctx [in] 随机数生成器上下文。
 * @since 20
 */
void OH_CryptoRand_Destroy(OH_CryptoRand *ctx);

#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_RAND_H */
/** @} */
