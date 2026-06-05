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
 * @addtogroup CryptoSignatureApi
 * @{
 * @brief 描述OpenHarmony为应用提供的签名验签接口。
 * @since 12
 */

/**
 * @file crypto_signature.h
 * @brief 定义签名验签接口。
 * @syscap SystemCapability.Security.CryptoFramework
 * @library libohcrypto.so
 * @kit CryptoArchitectureKit
 * @since 12
 */

#ifndef CRYPTO_SIGNATURE_H
#define CRYPTO_SIGNATURE_H

#include "crypto_common.h"
#include "crypto_asym_key.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义签名参数类型。
 * @since 12
 */
typedef enum {
    /**
     * @brief 表示消息摘要函数的算法名称。
     * @since 12
     */
    CRYPTO_PSS_MD_NAME_STR = 100,
    /**
     * @brief 表示掩码生成函数的算法名称。
     * @since 12
     */
    CRYPTO_PSS_MGF_NAME_STR = 101,
    /**
     * @brief 表示MGF1掩码生成函数的消息摘要参数。
     * @since 12
     */
    CRYPTO_PSS_MGF1_NAME_STR = 102,
    /**
     * @brief 表示盐值的字节长度。
     * @since 12
     */
    CRYPTO_PSS_SALT_LEN_INT = 103,
    /**
     * @brief 表示尾部字段的值。
     * @since 12
     */
    CRYPTO_PSS_TRAILER_FIELD_INT = 104,
    /**
     * @brief 表示SM2算法的用户ID值。
     * @since 12
     */
    CRYPTO_SM2_USER_ID_DATABLOB = 105,
} CryptoSignature_ParamType;

/**
 * @brief 验签结构体，表示验签上下文。
 * @since 12
 */
typedef struct OH_CryptoVerify OH_CryptoVerify;

/**
 * @brief 签名结构体，表示签名上下文。
 * @since 20
 */
typedef struct OH_CryptoSign OH_CryptoSign;

/**
 * @brief 根据给定的算法名称创建验签上下文。
 * @param algoName [in] 验签算法名称，不能为NULL。取值如下：
 *     - RSA PKCS1模式：格式为"RSA|PKCS1|摘要"，示例："RSA|PKCS1|SHA256"、"RSA|PKCS1|SHA512"。
 *     摘要支持"MD5"、"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"。
 *     - RSA PSS模式：格式为"RSA|PSS|摘要|MGF1摘要"，示例："RSA|PSS|SHA256|MGF1_SHA256"。
 *     摘要支持"MD5"、"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"。
 *     MGF1摘要支持"MGF1_MD5"、"MGF1_SHA1"、"MGF1_SHA224"、"MGF1_SHA256"、"MGF1_SHA384"、"MGF1_SHA512"。
 *     - RSA验签恢复：格式为"RSA|PKCS1|摘要|Recover"，示例："RSA|PKCS1|SHA256|Recover"、"RSA|PKCS1|SHA512|Recover"。
 *     摘要支持"NoHash"、"MD5"、"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"。
 *     - ECDSA算法：格式为"ECC|摘要"，示例："ECC|SHA256"、"ECC|SHA384"。
 *     摘要支持"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"。
 *     - DSA算法：格式为"DSA|摘要"，示例："DSA|SHA256"、"DSA|SHA384"。
 *     摘要支持"NoHash"、"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"。
 *     - SM2算法：取值为"SM2|SM3"。
 *     - Ed25519算法：取值为"Ed25519"。
 * @param verify [out] 指向验签上下文指针的指针。verify不能为NULL，*verify必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} verify为NULL，algoName为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持该算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_signature/OH_CryptoVerify_Destroy {verify}
 * @since 12
 * @see {@link OH_CryptoVerify_Init} 使用给定的公钥初始化验签上下文。
 */
OH_Crypto_ErrCode OH_CryptoVerify_Create(const char *algoName, OH_CryptoVerify **verify);

/**
 * @brief 使用给定的公钥初始化验签上下文。
 * @param ctx [in] 验签上下文。不能为NULL。
 * @param pubKey [in] 公钥。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx或pubKey为NULL，或密钥类型与签名算法不匹配。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 验签初始化失败。</li>
 *         </ul>
 * @since 12
 * @see {@link OH_CryptoVerify_Update} 追加待验签的消息数据。
 * @see {@link OH_CryptoVerify_Final} 验签消息数据。
 * @see {@link OH_CryptoVerify_Recover} 恢复签名数据。
 */
OH_Crypto_ErrCode OH_CryptoVerify_Init(OH_CryptoVerify *ctx, OH_CryptoPubKey *pubKey);

/**
 * @brief 追加待验签的消息数据。
 * @param ctx [in] 验签上下文。不能为NULL。
 * @param in [in] 待验签的数据。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx或in为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_CALL} 无效的函数调用。 [since 26.0.0]</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 验签更新失败。</li>
 *         </ul>
 * @since 12
 * @see {@link OH_CryptoVerify_Final} 验签消息数据。
 */
OH_Crypto_ErrCode OH_CryptoVerify_Update(OH_CryptoVerify *ctx, Crypto_DataBlob *in);

/**
 * @brief 验签消息数据。
 * @param ctx [in] 验签上下文。不能为NULL。
 * @param in [in] 待验签的数据。如果数据已通过{@link OH_CryptoVerify_Update}接口更新了所有数据，此参数可以为NULL。
 * @param signData [in] 签名数据。不能为NULL。
 * @return 返回bool类型的验签结果。返回true表示验签通过，返回false表示验签失败。可能的原因：公钥不正确、签名数据损坏、摘要算法不匹配、
 *     填充模式不匹配，或数据与原始签名数据不匹配。
 * @since 12
 */
bool OH_CryptoVerify_Final(OH_CryptoVerify *ctx, Crypto_DataBlob *in, Crypto_DataBlob *signData);

/**
 * @brief 恢复签名数据，仅支持RSA算法。
 * @param ctx [in] 验签上下文。不能为NULL。
 * @param signData [in] 签名数据。不能为NULL。
 * @param rawSignData [out] 指向用于存储原始签名数据的Crypto_DataBlob结构体的指针。不能为NULL。 调用前需将rawSignData初始化为{0}，
 *     不要预分配rawSignData->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx、signData或rawSignData为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_CALL} 无效的函数调用。 [since 26.0.0]</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 恢复失败。可能的原因：签名数据长度与RSA密钥模数大小不匹配。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {rawSignData}
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoVerify_Recover(OH_CryptoVerify *ctx, Crypto_DataBlob *signData,
    Crypto_DataBlob *rawSignData);

/**
 * @brief 获取验签上下文的算法名称。
 * @param ctx [in] 验签上下文。不能为NULL。
 * @return 返回验签算法名称，不需要调用者释放，在上下文销毁后不可使用。
 * @since 12
 */
const char *OH_CryptoVerify_GetAlgoName(OH_CryptoVerify *ctx);

/**
 * @brief 设置验签上下文的指定参数。
 * @param ctx [in] 验签上下文。不能为NULL。
 * @param type [in] 签名参数类型。
 * @param value [in] 输入数据。本接口会对value中的数据进行深拷贝，调用者在接口返回后可立即释放value。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx或value为NULL，value->data为NULL，
 *            value->len与type期望的大小不匹配，或type不是有效的CryptoSignature_ParamType。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 设置参数失败。</li>
 *         </ul>
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoVerify_SetParam(OH_CryptoVerify *ctx, CryptoSignature_ParamType type,
    Crypto_DataBlob *value);

/**
 * @brief 获取验签上下文的指定参数。
 * @param ctx [in] 验签上下文。不能为NULL。
 * @param type [in] 签名参数类型。
 * @param value [out] 指向用于存储输出数据的Crypto_DataBlob结构体的指针。不能为NULL。 调用前需将value初始化为{0}，不要预分配
 *     value->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx或value为NULL，或type不是有效的CryptoSignature_ParamType。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 输出数据的内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 获取参数失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {value}
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoVerify_GetParam(OH_CryptoVerify *ctx, CryptoSignature_ParamType type,
    Crypto_DataBlob *value);

/**
 * @brief 销毁验签上下文。
 * @param ctx [in] 验签上下文。
 * @since 12
 */
void OH_CryptoVerify_Destroy(OH_CryptoVerify *ctx);

/**
 * @brief 根据给定的算法名称创建签名上下文。
 * @param algoName [in] 签名算法名称，不能为NULL。取值如下：
 *     - RSA PKCS1模式：格式为"RSA|PKCS1|摘要"，示例："RSA|PKCS1|SHA256"、"RSA|PKCS1|SHA512"。
 *     摘要支持"MD5"、"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"。
 *     - RSA PSS模式：格式为"RSA|PSS|摘要|MGF1摘要"，示例："RSA|PSS|SHA256|MGF1_SHA256"。
 *     摘要支持"MD5"、"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"。
 *     MGF1摘要支持"MGF1_MD5"、"MGF1_SHA1"、"MGF1_SHA224"、"MGF1_SHA256"、"MGF1_SHA384"、"MGF1_SHA512"。
 *     - RSA仅签名：格式为"RSA|PKCS1|摘要|OnlySign"，示例："RSA|PKCS1|SHA256|OnlySign"、"RSA|PKCS1|SHA512|OnlySign"。
 *     摘要支持"NoHash"、"MD5"、"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"。
 *     - ECDSA算法：格式为"ECC|摘要"，示例："ECC|SHA256"、"ECC|SHA384"。
 *     摘要支持"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"。
 *     - DSA算法：格式为"DSA|摘要"，示例："DSA|SHA256"、"DSA|SHA384"。
 *     摘要支持"NoHash"、"SHA1"、"SHA224"、"SHA256"、"SHA384"、"SHA512"。
 *     - SM2算法：取值为"SM2|SM3"。
 *     - Ed25519算法：取值为"Ed25519"。
 * @param sign [out] 指向签名上下文指针的指针。sign不能为NULL，*sign必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} sign或algoName为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持该算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_signature/OH_CryptoSign_Destroy {sign}
 * @since 20
 * @see {@link OH_CryptoSign_Init} 初始化签名上下文。
 */
OH_Crypto_ErrCode OH_CryptoSign_Create(const char *algoName, OH_CryptoSign **sign);

/**
 * @brief 初始化签名上下文。
 * @param ctx [in] 签名上下文。不能为NULL。
 * @param privKey [in] 私钥。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或privKey为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 签名初始化失败。</li>
 *         </ul>
 * @since 20
 * @see {@link OH_CryptoSign_Update} 更新待签名的数据。
 * @see {@link OH_CryptoSign_Final} 结束签名操作。
 */
OH_Crypto_ErrCode OH_CryptoSign_Init(OH_CryptoSign *ctx, OH_CryptoPrivKey *privKey);

/**
 * @brief 更新待签名的数据。
 * @param ctx [in] 签名上下文。不能为NULL。
 * @param in [in] 待签名的数据。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或in为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_CALL} 无效的函数调用。 [since 26.0.0]</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 签名更新失败。</li>
 *         </ul>
 * @since 20
 * @see {@link OH_CryptoSign_Final} 结束签名操作。
 */
OH_Crypto_ErrCode OH_CryptoSign_Update(OH_CryptoSign *ctx, const Crypto_DataBlob *in);

/**
 * @brief 结束签名操作。
 * @param ctx [in] 签名上下文。不能为NULL。
 * @param in [in] 待签名的数据。如果数据已通过{@link OH_CryptoSign_Update}接口更新了所有数据，此参数可以为NULL。
 * @param out [out] 指向用于存储签名结果的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将out初始化为{0}，不要预分配out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或out为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 签名失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoSign_Final(OH_CryptoSign *ctx, const Crypto_DataBlob *in, Crypto_DataBlob *out);

/**
 * @brief 获取签名上下文的算法名称。
 * @param ctx [in] 签名上下文。不能为NULL。
 * @return 返回签名算法名称，不需要调用者释放，在上下文销毁后不可使用。
 * @since 20
 */
const char *OH_CryptoSign_GetAlgoName(OH_CryptoSign *ctx);

/**
 * @brief 设置签名上下文的指定参数。
 * @param ctx [in] 签名上下文。不能为NULL。
 * @param type [in] 签名参数类型。
 * @param value [in] 输入数据。本接口会对value中的数据进行深拷贝，调用者在接口返回后可立即释放value。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或value为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoSign_SetParam(OH_CryptoSign *ctx, CryptoSignature_ParamType type,
    const Crypto_DataBlob *value);

/**
 * @brief 获取签名上下文的指定参数。
 * @param ctx [in] 签名上下文。不能为NULL。
 * @param type [in] 签名参数类型。
 * @param value [out] 指向用于存储输出数据的Crypto_DataBlob结构体的指针。不能为NULL。 调用前需将value初始化为{0}，不要预分配
 *     value->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或value为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {value}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoSign_GetParam(OH_CryptoSign *ctx, CryptoSignature_ParamType type, Crypto_DataBlob *value);

/**
 * @brief 销毁签名上下文。
 * @param ctx [in] 签名上下文。
 * @since 20
 */
void OH_CryptoSign_Destroy(OH_CryptoSign *ctx);

/**
 * @brief ECC签名规格结构体，表示ECC签名规格。
 * @since 20
 */
typedef struct OH_CryptoEccSignatureSpec OH_CryptoEccSignatureSpec;

/**
 * @brief 创建ECC签名规格，同时支持SM2签名。
 * @param eccSignature [in] DER格式的ECC签名数据，如果为NULL则创建空的签名规格。
 * @param spec [out] 指向ECC签名规格指针的指针。spec不能为NULL，*spec必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} spec为NULL或*spec不为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 解析eccSignature失败，
 *            或eccSignature包含无效的DER编码ECDSA-Sig-Value。</li>
 *         </ul>
 * @release crypto_signature/OH_CryptoEccSignatureSpec_Destroy {spec}
 * @since 20
 * @see {@link OH_CryptoEccSignatureSpec_GetRAndS} 获取ECC签名规格中的r和s值。
 * @see {@link OH_CryptoEccSignatureSpec_SetRAndS} 设置ECC签名规格中的r和s值。
 */
OH_Crypto_ErrCode OH_CryptoEccSignatureSpec_Create(Crypto_DataBlob *eccSignature,
    OH_CryptoEccSignatureSpec **spec);

/**
 * @brief 获取ECC签名规格中的r和s值。
 * @param spec [in] ECC签名规格。不能为NULL。
 * @param r [out] 指向用于存储r值的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将r初始化为{0}，不要预分配r->data内存。
 * @param s [out] 指向用于存储s值的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将s初始化为{0}，不要预分配s->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} spec、r或s为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {s}
 * @release crypto_common/OH_Crypto_FreeDataBlob {r}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoEccSignatureSpec_GetRAndS(OH_CryptoEccSignatureSpec *spec, Crypto_DataBlob *r,
    Crypto_DataBlob *s);

/**
 * @brief 设置ECC签名规格中的r和s值。
 * @param spec [in] ECC签名规格。不能为NULL。
 * @param r [in] r值。本接口会对r和s中的数据进行深拷贝，调用者在接口返回后可立即释放r和s。不能为NULL。
 * @param s [in] s值。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} spec、r或s为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @since 20
 * @see {@link OH_CryptoEccSignatureSpec_Encode} 将ECC签名规格编码为DER格式的签名数据。
 */
OH_Crypto_ErrCode OH_CryptoEccSignatureSpec_SetRAndS(OH_CryptoEccSignatureSpec *spec, Crypto_DataBlob *r,
    Crypto_DataBlob *s);

/**
 * @brief 将ECC签名规格编码为DER格式的签名数据。
 * @param spec [in] ECC签名规格。不能为NULL。
 * @param out [out] 指向用于存储编码签名数据的Crypto_DataBlob结构体的指针。不能为NULL。 调用前需将out初始化为{0}，不要预分配
 *     out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} spec或out为NULL，或尚未通过
 *            {@link OH_CryptoEccSignatureSpec_SetRAndS}设置r和s值。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 编码失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoEccSignatureSpec_Encode(OH_CryptoEccSignatureSpec *spec, Crypto_DataBlob *out);

/**
 * @brief 销毁ECC签名规格。
 * @param spec [in] ECC签名规格。
 * @since 20
 */
void OH_CryptoEccSignatureSpec_Destroy(OH_CryptoEccSignatureSpec *spec);

#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_SIGNATURE_H */
/** @} */
