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
 * @addtogroup CryptoAsymKeyApi
 * @{
 * @brief 描述OpenHarmony为应用提供的非对称密钥相关接口。
 * @since 12
 */

/**
 * @file crypto_asym_key.h
 * @brief 定义非对称密钥接口。
 * @syscap SystemCapability.Security.CryptoFramework
 * @library libohcrypto.so
 * @kit CryptoArchitectureKit
 * @since 12
 */

#ifndef CRYPTO_ASYM_KEY_H
#define CRYPTO_ASYM_KEY_H

#include "crypto_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 密钥对结构体，表示密钥对。
 * @since 12
 */
typedef struct OH_CryptoKeyPair OH_CryptoKeyPair;

/**
 * @brief 公钥结构体，表示公钥。
 * @since 12
 */
typedef struct OH_CryptoPubKey OH_CryptoPubKey;

/**
 * @brief 私钥结构体，表示私钥。
 * @since 20
 */
typedef struct OH_CryptoPrivKey OH_CryptoPrivKey;

/**
 * @brief 定义非对称密钥参数类型。
 * @since 12
 */
typedef enum {
    /**
     * @brief 表示DSA算法的素数p。
     * @since 12
     */
    CRYPTO_DSA_P_DATABLOB = 101,
    /**
     * @brief 表示DSA算法的子素数q。
     * @since 12
     */
    CRYPTO_DSA_Q_DATABLOB = 102,
    /**
     * @brief 表示DSA算法的基g。
     * @since 12
     */
    CRYPTO_DSA_G_DATABLOB = 103,
    /**
     * @brief 表示DSA算法的私钥。
     * @since 12
     */
    CRYPTO_DSA_SK_DATABLOB = 104,
    /**
     * @brief 表示DSA算法的公钥。
     * @since 12
     */
    CRYPTO_DSA_PK_DATABLOB = 105,

    /**
     * @brief 表示椭圆曲线(EC)素数域的素数p。
     * @since 12
     */
    CRYPTO_ECC_FP_P_DATABLOB = 201,
    /**
     * @brief 表示椭圆曲线的第一个系数a。
     * @since 12
     */
    CRYPTO_ECC_A_DATABLOB = 202,
    /**
     * @brief 表示椭圆曲线的第二个系数b。
     * @since 12
     */
    CRYPTO_ECC_B_DATABLOB = 203,
    /**
     * @brief 表示基点g的仿射x坐标。
     * @since 12
     */
    CRYPTO_ECC_G_X_DATABLOB = 204,
    /**
     * @brief 表示基点g的仿射y坐标。
     * @since 12
     */
    CRYPTO_ECC_G_Y_DATABLOB = 205,
    /**
     * @brief 表示基点g的阶。
     * @since 12
     */
    CRYPTO_ECC_N_DATABLOB = 206,
    /**
     * @brief 表示椭圆曲线的余因子。
     * @since 12
     */
    CRYPTO_ECC_H_INT = 207,
    /**
     * @brief 表示ECC私钥的私钥值。
     * @since 12
     */
    CRYPTO_ECC_SK_DATABLOB = 208,
    /**
     * @brief 表示ECC公钥中公钥点的仿射x坐标。
     * @since 12
     */
    CRYPTO_ECC_PK_X_DATABLOB = 209,
    /**
     * @brief 表示ECC公钥中公钥点的仿射y坐标。
     * @since 12
     */
    CRYPTO_ECC_PK_Y_DATABLOB = 210,
    /**
     * @brief 表示椭圆曲线有限域类型。
     * @since 12
     */
    CRYPTO_ECC_FIELD_TYPE_STR = 211,
    /**
     * @brief 表示有限域的比特长度。
     * @since 12
     */
    CRYPTO_ECC_FIELD_SIZE_INT = 212,
    /**
     * @brief 表示SECG标准的曲线名称。
     * @since 12
     */
    CRYPTO_ECC_CURVE_NAME_STR = 213,

    /**
     * @brief 表示RSA算法的模数n。
     * @since 12
     */
    CRYPTO_RSA_N_DATABLOB = 301,
    /**
     * @brief 表示RSA算法的私钥指数d。
     * @since 12
     */
    CRYPTO_RSA_D_DATABLOB = 302,
    /**
     * @brief 表示RSA算法的公钥指数e。
     * @since 12
     */
    CRYPTO_RSA_E_DATABLOB = 303,

    /**
     * @brief 表示DH算法的素数p。
     * @since 12
     */
    CRYPTO_DH_P_DATABLOB = 401,
    /**
     * @brief 表示DH算法的生成元g。
     * @since 12
     */
    CRYPTO_DH_G_DATABLOB = 402,
    /**
     * @brief 表示DH算法中私钥长度的比特数。
     * @since 12
     */
    CRYPTO_DH_L_INT = 403,
    /**
     * @brief 表示DH私钥的私钥值。
     * @since 12
     */
    CRYPTO_DH_SK_DATABLOB = 404,
    /**
     * @brief 表示DH公钥的公钥值。
     * @since 12
     */
    CRYPTO_DH_PK_DATABLOB = 405,

    /**
     * @brief 表示ED25519私钥的私钥值。
     * @since 12
     */
    CRYPTO_ED25519_SK_DATABLOB = 501,
    /**
     * @brief 表示ED25519公钥的公钥值。
     * @since 12
     */
    CRYPTO_ED25519_PK_DATABLOB = 502,
    /**
     * @brief 表示X25519私钥的私钥值。
     * @since 12
     */
    CRYPTO_X25519_SK_DATABLOB = 601,
    /**
     * @brief 表示X25519公钥的公钥值。
     * @since 12
     */
    CRYPTO_X25519_PK_DATABLOB = 602,
} CryptoAsymKey_ParamType;

/**
 * @brief 定义编码类型。
 * @since 12
 */
typedef enum {
    /**
     * @brief PEM格式。
     * @since 12
     */
    CRYPTO_PEM = 0,
    /**
     * @brief DER格式。
     * @since 12
     */
    CRYPTO_DER = 1,
} Crypto_EncodingType;

/**
 * @brief 非对称密钥生成器结构体，表示非对称密钥生成器。
 * @since 12
 */
typedef struct OH_CryptoAsymKeyGenerator OH_CryptoAsymKeyGenerator;

/**
 * @brief 根据给定的算法名称创建非对称密钥生成器。
 * @param algoName [in] 非对称密钥算法名称，不能为NULL。取值如下：
 *     - 从API version 12开始支持RSA系列："RSA512"、"RSA768"、"RSA1024"、"RSA2048"、"RSA3072"、"RSA4096"、"RSA8192"。
 *     支持多素数格式，示例："RSA1024|PRIMES_3"、"RSA4096|PRIMES_4"、"RSA8192|PRIMES_5"。
 *     - 从API version 12开始支持ECC系列："ECC224"、"ECC256"、"ECC384"、"ECC521"。
 *     - 从API version 12开始支持ECC BrainPool系列："ECC_BrainPoolP160r1"、"ECC_BrainPoolP160t1"、"ECC_BrainPoolP192r1"、
 *     "ECC_BrainPoolP192t1"、"ECC_BrainPoolP224r1"、"ECC_BrainPoolP224t1"、"ECC_BrainPoolP256r1"、"ECC_BrainPoolP256t1"、
 *     "ECC_BrainPoolP320r1"、"ECC_BrainPoolP320t1"、"ECC_BrainPoolP384r1"、"ECC_BrainPoolP384t1"、"ECC_BrainPoolP512r1"、
 *     "ECC_BrainPoolP512t1"。
 *     - 从API version 12开始支持"SM2_256"、"Ed25519"、"X25519"。
 *     - 从API version 12开始支持DSA系列："DSA1024"、"DSA2048"、"DSA3072"。
 *     - 从API version 12开始支持DH系列："DH_modp1536"、"DH_modp2048"、"DH_modp3072"、"DH_modp4096"、
 *     "DH_modp6144"、"DH_modp8192"、"DH_ffdhe2048"、"DH_ffdhe3072"、"DH_ffdhe4096"、"DH_ffdhe6144"、"DH_ffdhe8192"。
 *     - 从API version 14开始支持"ECC_Secp256k1"。
 *     - 从API version 26.0.0开始支持"ECC192"。
 * @param ctx [out] 指向非对称密钥生成器指针的指针。ctx不能为NULL，*ctx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx为NULL或algoName为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_asym_key/OH_CryptoAsymKeyGenerator_Destroy {ctx}
 * @since 12
 * @see {@link OH_CryptoAsymKeyGenerator_Generate} 生成非对称密钥对。
 * @see {@link OH_CryptoAsymKeyGenerator_Convert} 将非对称密钥数据转换为密钥对。
 */
OH_Crypto_ErrCode OH_CryptoAsymKeyGenerator_Create(const char *algoName, OH_CryptoAsymKeyGenerator **ctx);

/**
 * @brief 生成非对称密钥对。
 * @param ctx [in] 非对称密钥生成器。不能为NULL。
 * @param keyCtx [out] 指向密钥对指针的指针。keyCtx不能为NULL，*keyCtx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx或keyCtx为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存操作失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_asym_key/OH_CryptoKeyPair_Destroy {keyCtx}
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoAsymKeyGenerator_Generate(OH_CryptoAsymKeyGenerator *ctx, OH_CryptoKeyPair **keyCtx);

/**
 * @brief 将非对称密钥数据转换为密钥对。
 * @param ctx [in] 非对称密钥生成器。不能为NULL。
 * @param type [in] 编码类型。
 * @param pubKeyData [in] 公钥数据，不能与priKeyData同时为NULL。
 * @param priKeyData [in] 私钥数据，不能与pubKeyData同时为NULL。
 * @param keyCtx [out] 指向密钥对指针的指针。keyCtx不能为NULL，*keyCtx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} ctx为NULL，pubKeyData和priKeyData同时为NULL，keyCtx为NULL
 *         或type不是有效的Crypto_EncodingType。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的密钥格式。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密钥转换失败。可能的原因：
 *            密钥数据损坏或不是有效的PEM/DER格式，密钥数据与算法不匹配，或加密私钥的密码不正确。</li>
 *         </ul>
 * @release crypto_asym_key/OH_CryptoKeyPair_Destroy {keyCtx}
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoAsymKeyGenerator_Convert(OH_CryptoAsymKeyGenerator *ctx, Crypto_EncodingType type,
    Crypto_DataBlob *pubKeyData, Crypto_DataBlob *priKeyData, OH_CryptoKeyPair **keyCtx);

/**
 * @brief 获取非对称密钥生成器的算法名称。
 * @param ctx [in] 非对称密钥生成器。不能为NULL。
 * @return <ul>
 *         <li>返回非对称密钥算法名称，不需要调用者释放，在生成器销毁后不可使用。</li>
 *         <li>返回NULL，如果ctx是NULL。</li>
 *         </ul>
 * @since 12
 */
const char *OH_CryptoAsymKeyGenerator_GetAlgoName(OH_CryptoAsymKeyGenerator *ctx);

/**
 * @brief 销毁非对称密钥生成器。
 * @param ctx [in] 非对称密钥生成器。
 * @since 12
 */
void OH_CryptoAsymKeyGenerator_Destroy(OH_CryptoAsymKeyGenerator *ctx);

/**
 * @brief 销毁密钥对。
 * @param keyCtx [in] 密钥对。
 * @since 12
 */
void OH_CryptoKeyPair_Destroy(OH_CryptoKeyPair *keyCtx);

/**
 * @brief 获取密钥对中的公钥。
 * @param keyCtx [in] 密钥对。不能为NULL。
 * @return <ul>
 *         <li>返回密钥对中的公钥。为内部引用，不需要单独销毁，在密钥对销毁后不可使用。</li>
 *         <li>返回NULL，如果keyCtx为NULL或公钥不存在。</li>
 *         </ul>
 * @since 12
 */
OH_CryptoPubKey *OH_CryptoKeyPair_GetPubKey(OH_CryptoKeyPair *keyCtx);

/**
 * @brief 获取密钥对中的私钥。
 * @param keyCtx [in] 密钥对。不能为NULL。
 * @return <ul>
 *         <li>返回密钥对中的私钥。为内部引用，不需要单独销毁，在密钥对销毁后不可使用。</li>
 *         <li>返回NULL，如果keyCtx为NULL或私钥不存在。</li>
 *         </ul>
 * @since 20
 */
OH_CryptoPrivKey *OH_CryptoKeyPair_GetPrivKey(OH_CryptoKeyPair *keyCtx);

/**
 * @brief 对公钥进行编码。
 * @param key [in] 公钥。不能为NULL。
 * @param type [in] 编码类型。
 * @param encodingStandard [in] 编码标准，支持"X509"。不能为NULL。
 * @param out [out] 指向用于存储编码结果的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将out初始化为{0}，不要预分配out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} key、out或encodingStandard为NULL，type不是
 *            有效的Crypto_EncodingType，或编码标准与密钥类型不兼容。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的编码格式。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 编码失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoPubKey_Encode(OH_CryptoPubKey *key, Crypto_EncodingType type,
    const char *encodingStandard, Crypto_DataBlob *out);

/**
 * @brief 获取公钥的指定参数。
 * @param key [in] 公钥。不能为NULL。
 * @param item [in] 非对称密钥参数类型。
 * @param value [out] 指向用于存储输出数据的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将value初始化为{0}，不要预分配
 *     value->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_INVALID_PARAMS} key或value为NULL，或该参数类型不支持该密钥算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的参数类型。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 获取参数失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {value}
 * @since 12
 */
OH_Crypto_ErrCode OH_CryptoPubKey_GetParam(OH_CryptoPubKey *key, CryptoAsymKey_ParamType item, Crypto_DataBlob *value);

/**
 * @brief 设置非对称密钥生成器的密码。如果需要使用{@link OH_CryptoAsymKeyGenerator_Convert}将加密的私钥数据转换为密钥对，请调用此方法
 * 设置密码。
 * @param ctx [in] 非对称密钥生成器。不能为NULL。
 * @param password [in] 密码。本接口会对password中的数据进行深拷贝，调用者在接口返回后可立即释放password。不能为NULL。
 * @param passwordLen [in] 密码的字节长度。必须大于0。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或password为NULL，或passwordLen为0。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoAsymKeyGenerator_SetPassword(OH_CryptoAsymKeyGenerator *ctx, const unsigned char *password,
    uint32_t passwordLen);

/**
 * @brief 私钥编码参数结构体，表示私钥编码参数。
 * @since 20
 */
typedef struct OH_CryptoPrivKeyEncodingParams OH_CryptoPrivKeyEncodingParams;

/**
 * @brief 定义私钥编码参数类型。
 * @since 20
 */
typedef enum {
    /**
     * @brief 表示密码字符串。
     * @since 20
     */
    CRYPTO_PRIVATE_KEY_ENCODING_PASSWORD_STR = 0,

    /**
     * @brief 对称加密算法名称，通过{@link OH_CryptoPrivKeyEncodingParams_SetParam}设置。
     * 取值："DES-EDE3-CBC"、"AES-128-CBC"、"AES-192-CBC"、"AES-256-CBC"。
     * @since 20
     */
    CRYPTO_PRIVATE_KEY_ENCODING_SYMMETRIC_CIPHER_STR = 1,
} CryptoPrivKeyEncoding_ParamType;

/**
 * @brief 创建私钥编码参数。
 * @param ctx [out] 指向私钥编码参数指针的指针。ctx不能为NULL，*ctx必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_asym_key/OH_CryptoPrivKeyEncodingParams_Destroy {ctx}
 * @since 20
 * @see {@link OH_CryptoPrivKeyEncodingParams_SetParam} 设置私钥编码参数。
 */
OH_Crypto_ErrCode OH_CryptoPrivKeyEncodingParams_Create(OH_CryptoPrivKeyEncodingParams **ctx);

/**
 * @brief 设置私钥编码参数。
 * @param ctx [in] 私钥编码参数。不能为NULL。
 * @param type [in] 私钥编码参数类型。
 * @param value [in] 私钥编码参数值。本接口会对value中的数据进行深拷贝，调用者在接口返回后可立即释放value。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} ctx或value为NULL，
 *            value->data为NULL，value->len为0，或type无法识别。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 深拷贝内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoPrivKeyEncodingParams_SetParam(OH_CryptoPrivKeyEncodingParams *ctx,
    CryptoPrivKeyEncoding_ParamType type, Crypto_DataBlob *value);

/**
 * @brief 销毁私钥编码参数。
 * @param ctx [in] 私钥编码参数。
 * @since 20
 */
void OH_CryptoPrivKeyEncodingParams_Destroy(OH_CryptoPrivKeyEncodingParams *ctx);

/**
 * @brief 对私钥进行编码。
 * @param key [in] 私钥。不能为NULL。
 * @param type [in] 编码类型。
 * @param encodingStandard [in] 编码标准，支持"PKCS8"和"PKCS1"。其中"PKCS1"仅支持RSA私钥。不能为NULL。
 * @param params [in] 私钥编码参数，可以为NULL，如果需要加密私钥，应设置此参数。
 * @param out [out] 指向用于存储编码结果的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将out初始化为{0}，不要预分配out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} key、out或encodingStandard为NULL，
 *            type不是有效的Crypto_EncodingType，或编码标准与密钥类型不兼容。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的编码格式。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 编码失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoPrivKey_Encode(OH_CryptoPrivKey *key, Crypto_EncodingType type,
    const char *encodingStandard, OH_CryptoPrivKeyEncodingParams *params, Crypto_DataBlob *out);

/**
 * @brief 获取私钥的指定参数。
 * @param key [in] 私钥。不能为NULL。
 * @param item [in] 非对称密钥参数类型。
 * @param value [out] 指向用于存储输出数据的Crypto_DataBlob结构体的指针。不能为NULL。 调用前需将value初始化为{0}，不要预分配
 *     value->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} key或value为NULL，或该参数类型不支持该密钥算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的参数类型。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 获取参数失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {value}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoPrivKey_GetParam(OH_CryptoPrivKey *key, CryptoAsymKey_ParamType item,
    Crypto_DataBlob *value);

/**
 * @brief 非对称密钥规格结构体，表示非对称密钥规格。
 * @since 20
 */
typedef struct OH_CryptoAsymKeySpec OH_CryptoAsymKeySpec;

/**
 * @brief 定义非对称密钥规格类型。
 * @since 20
 */
typedef enum {
    /**
     * @brief 通用参数规格。
     * @since 20
     */
    CRYPTO_ASYM_KEY_COMMON_PARAMS_SPEC = 0,
    /**
     * @brief 私钥规格。
     * @since 20
     */
    CRYPTO_ASYM_KEY_PRIVATE_KEY_SPEC = 1,
    /**
     * @brief 公钥规格。
     * @since 20
     */
    CRYPTO_ASYM_KEY_PUBLIC_KEY_SPEC = 2,
    /**
     * @brief 密钥对规格。
     * @since 20
     */
    CRYPTO_ASYM_KEY_KEY_PAIR_SPEC = 3,
} CryptoAsymKeySpec_Type;

/**
 * @brief 生成EC通用参数规格。
 * @param curveName [in] ECC曲线的NID（Name Identifier）字符串名称，不能为NULL。例如"NID_X9_62_prime256v1"、"NID_secp384r1"、
 *     "NID_secp521r1"、"NID_sm2"。
 * @param spec [out] 指向非对称密钥规格指针的指针。spec不能为NULL，*spec必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} curveName或spec为NULL，或曲线名不是有效的椭圆曲线。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的曲线。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 生成规格失败。</li>
 *         </ul>
 * @release crypto_asym_key/OH_CryptoAsymKeySpec_Destroy {spec}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoAsymKeySpec_GenEcCommonParamsSpec(const char *curveName, OH_CryptoAsymKeySpec **spec);

/**
 * @brief 生成DH通用参数规格。
 * @param pLen [in] 素数p的比特长度。
 * @param skLen [in] 私钥的比特长度。
 * @param spec [out] 指向非对称密钥规格指针的指针。spec不能为NULL，*spec必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} spec为NULL，
 *            pLen为负数，skLen为负数，或skLen大于pLen。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_asym_key/OH_CryptoAsymKeySpec_Destroy {spec}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoAsymKeySpec_GenDhCommonParamsSpec(int pLen, int skLen, OH_CryptoAsymKeySpec **spec);

/**
 * @brief 根据给定的算法名称和规格类型创建非对称密钥规格。
 * @param algoName [in] 非对称密钥规格算法名称，不能为NULL。取值如下：
 *     - 从API version 20开始支持"RSA"、"ECC"、"DSA"、"SM2"、"Ed25519"、"X25519"、"DH"。
 * @param type [in] 非对称密钥规格类型。
 * @param spec [out] 指向非对称密钥规格指针的指针。spec不能为NULL，*spec必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} algoName或spec为NULL，
 *            algoName不是支持的算法名称。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_asym_key/OH_CryptoAsymKeySpec_Destroy {spec}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoAsymKeySpec_Create(const char *algoName, CryptoAsymKeySpec_Type type,
    OH_CryptoAsymKeySpec **spec);

/**
 * @brief 设置非对称密钥规格的指定参数。
 * @param spec [in] 非对称密钥规格。不能为NULL。
 * @param type [in] 非对称密钥参数类型。
 * @param value [in] 输入数据。本接口会对value中的数据进行深拷贝，调用者在接口返回后可立即释放value。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} spec或value为NULL，
 *            value->data为NULL，value->len为0，或该参数类型不支持该算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 深拷贝内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoAsymKeySpec_SetParam(OH_CryptoAsymKeySpec *spec, CryptoAsymKey_ParamType type,
    Crypto_DataBlob *value);

/**
 * @brief 将通用参数规格设置到非对称密钥规格中。
 * @param spec [in] 非对称密钥规格。不能为NULL。
 * @param commonParamsSpec [in] 通用参数规格。本接口会对commonParamsSpec中的数据进行深拷贝，
 *     调用者在接口返回后可立即释放commonParamsSpec。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} spec或commonParamsSpec为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoAsymKeySpec_SetCommonParamsSpec(OH_CryptoAsymKeySpec *spec,
    OH_CryptoAsymKeySpec *commonParamsSpec);

/**
 * @brief 获取非对称密钥规格的指定参数。
 * @param spec [in] 非对称密钥规格。不能为NULL。
 * @param type [in] 非对称密钥参数类型。
 * @param value [out] 指向用于存储输出数据的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将value初始化为{0}，不要预分配
 *     value->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} spec或value为NULL，或该参数类型不支持该算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {value}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoAsymKeySpec_GetParam(OH_CryptoAsymKeySpec *spec, CryptoAsymKey_ParamType type,
    Crypto_DataBlob *value);

/**
 * @brief 销毁非对称密钥规格。
 * @param spec [in] 非对称密钥规格。
 * @since 20
 */
void OH_CryptoAsymKeySpec_Destroy(OH_CryptoAsymKeySpec *spec);

/**
 * @brief 基于规格的非对称密钥生成器结构体，表示基于规格的非对称密钥生成器。
 * @since 20
 */
typedef struct OH_CryptoAsymKeyGeneratorWithSpec OH_CryptoAsymKeyGeneratorWithSpec;

/**
 * @brief 根据非对称密钥规格创建密钥生成器。
 * @param keySpec [in] 非对称密钥规格。不能为NULL。
 * @param generator [out] 指向基于规格的非对称密钥生成器指针的指针。generator不能为NULL，*generator必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} keySpec或generator为NULL，
 *            或密钥规格参数不完整或无效。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 创建生成器失败。</li>
 *         </ul>
 * @release crypto_asym_key/OH_CryptoAsymKeyGeneratorWithSpec_Destroy {generator}
 * @since 20
 * @see {@link OH_CryptoAsymKeyGeneratorWithSpec_GenKeyPair} 根据非对称密钥规格生成密钥对。
 */
OH_Crypto_ErrCode OH_CryptoAsymKeyGeneratorWithSpec_Create(OH_CryptoAsymKeySpec *keySpec,
    OH_CryptoAsymKeyGeneratorWithSpec **generator);

/**
 * @brief 根据非对称密钥规格生成密钥对。
 * @param generator [in] 基于规格的非对称密钥生成器。不能为NULL。
 * @param keyPair [out] 指向密钥对指针的指针。keyPair不能为NULL，*keyPair必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} generator或keyPair为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 生成密钥对失败。可能的原因：密钥规格参数不完整或不一致。</li>
 *         </ul>
 * @release crypto_asym_key/OH_CryptoKeyPair_Destroy {keyPair}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoAsymKeyGeneratorWithSpec_GenKeyPair(OH_CryptoAsymKeyGeneratorWithSpec *generator,
    OH_CryptoKeyPair **keyPair);

/**
 * @brief 销毁根据规格创建的非对称密钥生成器。
 * @param generator [in] 基于规格的非对称密钥生成器。
 * @since 20
 */
void OH_CryptoAsymKeyGeneratorWithSpec_Destroy(OH_CryptoAsymKeyGeneratorWithSpec *generator);

/**
 * @brief 椭圆曲线点结构体，表示椭圆曲线上的点。
 * @since 20
 */
typedef struct OH_CryptoEcPoint OH_CryptoEcPoint;

/**
 * @brief 创建椭圆曲线点。
 * @param curveName [in] 椭圆曲线的NID（Name Identifier）字符串名称，不能为NULL。例如"NID_X9_62_prime256v1"、"NID_secp384r1"、
 *     "NID_secp521r1"、"NID_sm2"。
 * @param ecKeyData [in] 椭圆曲线点数据，支持"04 || x || y"、"02 || x"或"03 || x"格式。可以为NULL。如果ecKeyData参数为NULL，
 * 将创建一个空的椭圆曲线点规格。
 * @param point [out] 指向椭圆曲线点指针的指针。point不能为NULL，*point必须为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} curveName或point为NULL，或曲线名称无效。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的曲线。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 创建EC点失败。可能的原因：点数据格式不正确。</li>
 *         </ul>
 * @release crypto_asym_key/OH_CryptoEcPoint_Destroy {point}
 * @since 20
 * @see {@link OH_CryptoEcPoint_GetCoordinate} 获取椭圆曲线点的x和y坐标。
 * @see {@link OH_CryptoEcPoint_SetCoordinate} 设置椭圆曲线点的x和y坐标。
 */
OH_Crypto_ErrCode OH_CryptoEcPoint_Create(const char *curveName, Crypto_DataBlob *ecKeyData, OH_CryptoEcPoint **point);

/**
 * @brief 获取椭圆曲线点的x和y坐标。
 * @param point [in] 椭圆曲线点。不能为NULL。
 * @param x [out] 指向用于存储x坐标的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将x初始化为{0}，不要预分配x->data内存。
 * @param y [out] 指向用于存储y坐标的Crypto_DataBlob结构体的指针。不能为NULL。调用前需将y初始化为{0}，不要预分配y->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} point、x或y为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {y}
 * @release crypto_common/OH_Crypto_FreeDataBlob {x}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoEcPoint_GetCoordinate(OH_CryptoEcPoint *point, Crypto_DataBlob *x, Crypto_DataBlob *y);

/**
 * @brief 设置椭圆曲线点的x和y坐标。
 * @param point [in] 椭圆曲线点。不能为NULL。
 * @param x [in] 椭圆曲线点的x坐标。本接口会对x和y中的数据进行深拷贝，调用者在接口返回后可立即释放x和y。不能为NULL。
 * @param y [in] 椭圆曲线点的y坐标。不能为NULL。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} point、x或y为NULL。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的操作或算法。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 深拷贝内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 密码操作失败。</li>
 *         </ul>
 * @since 20
 * @see {@link OH_CryptoEcPoint_Encode} 将椭圆曲线点编码为指定格式。
 */
OH_Crypto_ErrCode OH_CryptoEcPoint_SetCoordinate(OH_CryptoEcPoint *point, Crypto_DataBlob *x, Crypto_DataBlob *y);

/**
 * @brief 将椭圆曲线点编码为指定格式。
 * @param point [in] 椭圆曲线点。不能为NULL。
 * @param format [in] 编码格式，不能为NULL。支持"UNCOMPRESSED"和"COMPRESSED"。
 * @param out [out] 指向用于存储编码后椭圆曲线点数据的Crypto_DataBlob结构体的指针。不能为NULL。 调用前需将out初始化为{0}，不要预分配
 *     out->data内存。
 * @return <ul>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_SUCCESS} 操作成功。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_PARAMETER_CHECK_FAILED} point、format或out为NULL，
 *            或格式字符串不是有效的点格式。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_NOT_SUPPORTED} 不支持的格式。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_MEMORY_ERROR} 内存分配失败。</li>
 *         <li>{@link OH_Crypto_ErrCode#CRYPTO_OPERTION_ERROR} 编码失败。可能的原因：该点不是有效的曲线点。</li>
 *         </ul>
 * @release crypto_common/OH_Crypto_FreeDataBlob {out}
 * @since 20
 */
OH_Crypto_ErrCode OH_CryptoEcPoint_Encode(OH_CryptoEcPoint *point, const char *format, Crypto_DataBlob *out);

/**
 * @brief 销毁椭圆曲线点。
 * @param point [in] 椭圆曲线点。
 * @since 20
 */
void OH_CryptoEcPoint_Destroy(OH_CryptoEcPoint *point);

#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_ASYM_KEY_H */
/** @} */
