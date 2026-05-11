/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup HuksTypeApi
 * @{
 *
 * @brief Defines the macros, enumerated values, data structures,
 *    and error codes used by OpenHarmony Universal KeyStore (HUKS) APIs.
 *
 * @since 9
 * @version 1.0
 */

/**
 * @file native_huks_type.h
 *
 * @brief Defines the enums, structs, and macros used in the HUKS functions.
 *
 * @library libhuks_ndk.z.so
 * @syscap SystemCapability.Security.Huks.Core
 *
 * @kit UniversalKeystoreKit
 * @since 9
 * @version 1.0
 */
#ifndef NATIVE_OH_HUKS_TYPE_H
#define NATIVE_OH_HUKS_TYPE_H
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Length of the AEAD authentication tag, in bytes.
 *
 * @since 9
 * @version 1.0
 */
#define OH_HUKS_AE_TAG_LEN 16

/**
 * @brief Number of bits in each byte.
 *
 * @since 9
 * @version 1.0
 */
#define OH_HUKS_BITS_PER_BYTE 8

/**
 * @brief Maximum key size, in bytes.
 *
 * @since 9
 * @version 1.0
 */
#define OH_HUKS_MAX_KEY_SIZE 2048

/**
 * @brief 密钥用途类型。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_KeyPurpose {
    /**
 * 表示密钥用于对明文进行加密操作。
 */
    OH_HUKS_KEY_PURPOSE_ENCRYPT = 1,
    /**
 * 表示密钥用于对密文进行解密操作。
 */
    OH_HUKS_KEY_PURPOSE_DECRYPT = 2,
    /**
 * 表示密钥用于对数据进行签名。
 */
    OH_HUKS_KEY_PURPOSE_SIGN = 4,
    /**
 * 表示密钥用于验证签名后的数据。
 */
    OH_HUKS_KEY_PURPOSE_VERIFY = 8,
    /**
 * 表示密钥用于派生密钥。
 */
    OH_HUKS_KEY_PURPOSE_DERIVE = 16,
    /**
 * 表示密钥用于加密导出。
 */
    OH_HUKS_KEY_PURPOSE_WRAP = 32,
    /**
 * 表示密钥加密导入。
 */
    OH_HUKS_KEY_PURPOSE_UNWRAP = 64,
    /**
 * 表示密钥用于生成mac消息验证码。
 */
    OH_HUKS_KEY_PURPOSE_MAC = 128,
    /**
 * 表示密钥用于进行密钥协商。
 */
    OH_HUKS_KEY_PURPOSE_AGREE = 256
};

/**
 * @brief 摘要算法类型。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_KeyDigest {
    /**
 * 无摘要算法。
 */
    OH_HUKS_DIGEST_NONE = 0,
    /**
 * MD5摘要算法。
 */
    OH_HUKS_DIGEST_MD5 = 1,
    /**
 * SM3摘要算法。
 */
    OH_HUKS_DIGEST_SM3 = 2,
    /**
 * SHA1摘要算法。
 */
    OH_HUKS_DIGEST_SHA1 = 10,
    /**
 * SHA224摘要算法。
 */
    OH_HUKS_DIGEST_SHA224 = 11,
    /**
 * SHA256摘要算法。
 */
    OH_HUKS_DIGEST_SHA256 = 12,
    /**
 * SHA384摘要算法。
 */
    OH_HUKS_DIGEST_SHA384 = 13,
    /**
 * SHA512摘要算法。
 */
    OH_HUKS_DIGEST_SHA512 = 14
};

/**
 * @brief 填充算法类型。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_KeyPadding {
    /**
 * 不使用填充算法。
 */
    OH_HUKS_PADDING_NONE = 0,
    /**
 * 使用OAEP填充算法。
 */
    OH_HUKS_PADDING_OAEP = 1,
    /**
 * 使用PSS填充算法。
 */
    OH_HUKS_PADDING_PSS = 2,
    /**
 * 使用PKCS1_V1_5填充算法。
 */
    OH_HUKS_PADDING_PKCS1_V1_5 = 3,
    /**
 * 使用PKCS5填充算法。
 */
    OH_HUKS_PADDING_PKCS5 = 4,
    /**
 * 使用PKCS7填充算法。
 */
    OH_HUKS_PADDING_PKCS7 = 5,
    /** ISO IEC 9796-2
 * @since 18
 */
    OH_HUKS_PADDING_ISO_IEC_9796_2 = 6,
    /** ISO IEC 9797-1
 * @since 18
 */
    OH_HUKS_PADDING_ISO_IEC_9797_1 = 7
};

/**
 * @brief 加密模式。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_CipherMode {
    /**
 * 使用ECB模式。
 */
    OH_HUKS_MODE_ECB = 1,
    /**
 * 使用CBC模式。
 */
    OH_HUKS_MODE_CBC = 2,
    /**
 * 使用CTR模式。
 */
    OH_HUKS_MODE_CTR = 3,
    /**
 * 使用OFB模式。
 */
    OH_HUKS_MODE_OFB = 4,
    /**
 * 使用CFB模式。
 * @since 12
 */
    OH_HUKS_MODE_CFB = 5,
    /**
 * 使用CCM模式。
 */
    OH_HUKS_MODE_CCM = 31,
    /**
 * 使用GCM模式。
 */
    OH_HUKS_MODE_GCM = 32
};

/**
 * @brief 算法密钥长度。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_KeySize {
    /**
 * 使用RSA算法的密钥长度为512bit。
 */
    OH_HUKS_RSA_KEY_SIZE_512 = 512,
    /**
 * 使用RSA算法的密钥长度为768bit。
 */
    OH_HUKS_RSA_KEY_SIZE_768 = 768,
    /**
 * 使用RSA算法的密钥长度为1024bit。
 */
    OH_HUKS_RSA_KEY_SIZE_1024 = 1024,
    /**
 * 使用RSA算法的密钥长度为2048bit。
 */
    OH_HUKS_RSA_KEY_SIZE_2048 = 2048,
    /**
 * 使用RSA算法的密钥长度为3072bit。
 */
    OH_HUKS_RSA_KEY_SIZE_3072 = 3072,
    /**
 * 使用RSA算法的密钥长度为4096bit。
 */
    OH_HUKS_RSA_KEY_SIZE_4096 = 4096,

    /**
 * 使用ECC算法的密钥长度为224bit。
 */
    OH_HUKS_ECC_KEY_SIZE_224 = 224,
    /**
 * 使用ECC算法的密钥长度为256bit。
 */
    OH_HUKS_ECC_KEY_SIZE_256 = 256,
    /**
 * 使用ECC算法的密钥长度为384bit。
 */
    OH_HUKS_ECC_KEY_SIZE_384 = 384,
    /**
 * 使用ECC算法的密钥长度为521bit。
 */
    OH_HUKS_ECC_KEY_SIZE_521 = 521,

    /**
 * 使用AES算法的密钥长度为128bit。
 */
    OH_HUKS_AES_KEY_SIZE_128 = 128,
    /**
 * 使用AES算法的密钥长度为192bit。
 */
    OH_HUKS_AES_KEY_SIZE_192 = 192,
    /**
 * 使用AES算法的密钥长度为256bit。
 */
    OH_HUKS_AES_KEY_SIZE_256 = 256,
    /**
 * 使用AES算法的密钥长度为512bit。
 */
    OH_HUKS_AES_KEY_SIZE_512 = 512,

    /**
 * 使用CURVE25519算法的密钥长度为256bit。
 */
    OH_HUKS_CURVE25519_KEY_SIZE_256 = 256,

    /**
 * 使用DH算法的密钥长度为2048bit。
 */
    OH_HUKS_DH_KEY_SIZE_2048 = 2048,
    /**
 * 使用DH算法的密钥长度为3072bit。
 */
    OH_HUKS_DH_KEY_SIZE_3072 = 3072,
    /**
 * 使用DH算法的密钥长度为4096bit。
 */
    OH_HUKS_DH_KEY_SIZE_4096 = 4096,

    /**
 * 使用SM2算法的密钥长度为256bit。
 */
    OH_HUKS_SM2_KEY_SIZE_256 = 256,
    /**
 * 使用SM4算法支持的密钥长度为128bit。
 */
    OH_HUKS_SM4_KEY_SIZE_128 = 128,

    /**
 * 使用DES算法的密钥长度为64bit。
 * @since 18
 */
    OH_HUKS_DES_KEY_SIZE_64 = 64,
    /**
 * 使用3DES算法的密钥长度为128bit。
 * @since 18
 */
    OH_HUKS_3DES_KEY_SIZE_128 = 128,
    /**
 * 使用3DES算法的密钥长度为192bit。
 * @since 18
 */
    OH_HUKS_3DES_KEY_SIZE_192 = 192
};

/**
 * @brief 密钥使用的算法。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_KeyAlg {
    /**
 * 使用RSA算法。
 */
    OH_HUKS_ALG_RSA = 1,
    /**
 * 使用ECC算法。
 */
    OH_HUKS_ALG_ECC = 2,
    /**
 * 使用DSA算法。
 */
    OH_HUKS_ALG_DSA = 3,

    /**
 * 使用AES算法。
 */
    OH_HUKS_ALG_AES = 20,
    /**
 * 使用HMAC算法。
 */
    OH_HUKS_ALG_HMAC = 50,
    /**
 * 使用HKDF算法。
 */
    OH_HUKS_ALG_HKDF = 51,
    /**
 * 使用PBKDF2算法。
 */
    OH_HUKS_ALG_PBKDF2 = 52,

    /**
 * 使用ECDH算法。
 */
    OH_HUKS_ALG_ECDH = 100,
    /**
 * 使用X25519算法。
 */
    OH_HUKS_ALG_X25519 = 101,
    /**
 * 使用ED25519算法。
 */
    OH_HUKS_ALG_ED25519 = 102,
    /**
 * 使用DH算法。
 */
    OH_HUKS_ALG_DH = 103,

    /**
 * 使用SM2算法。
 */
    OH_HUKS_ALG_SM2 = 150,
    /**
 * SM3摘要算法。
 */
    OH_HUKS_ALG_SM3 = 151,
    /**
 * 使用SM4算法。
 */
    OH_HUKS_ALG_SM4 = 152,
    /** DES.
 * @since 18
 */
    OH_HUKS_ALG_DES = 160,
    /** 3DES.
 * @since 18
 */
    OH_HUKS_ALG_3DES = 161,
    /** CMAC.
 * @since 18
 */
    OH_HUKS_ALG_CMAC = 162
};

/**
 * @brief 密文导入所需的算法套件类型。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_AlgSuite {
    /**
 *  密文导入密钥材料格式（Length-Value格式）采用X25519密钥协商同时采用AES-256-GCM加解密。
 *  | x25519_plain_pubkey_length  (4 Byte) | x25519_plain_pubkey |  agreekey_aad_length (4 Byte) | agreekey_aad
 *  |   agreekey_nonce_length     (4 Byte) |   agreekey_nonce    |
 *  |   agreekey_aead_tag_len     (4 Byte) |  agreekey_aead_tag  |
 *  |    kek_enc_data_length      (4 Byte) |    kek_enc_data     |    kek_aad_length    (4 Byte) | kek_aad
 *  |      kek_nonce_length       (4 Byte) |      kek_nonce      |   kek_aead_tag_len   (4 Byte) | kek_aead_tag
 *  |   key_material_size_len     (4 Byte) |  key_material_size  |   key_mat_enc_length (4 Byte) | key_mat_enc_data
 */
    OH_HUKS_UNWRAP_SUITE_X25519_AES_256_GCM_NOPADDING = 1,

    /**
 * 密文导入密钥材料格式（Length-Value格式）采用ECDH-p256密钥协商同时采用AES-256-GCM加解密。
 *  |  ECC_plain_pubkey_length    (4 Byte) |  ECC_plain_pubkey   |  agreekey_aad_length (4 Byte) | agreekey_aad
 *  |   agreekey_nonce_length     (4 Byte) |   agreekey_nonce    |
 *  |   agreekey_aead_tag_len     (4 Byte) | agreekey_aead_tag   |
 *  |    kek_enc_data_length      (4 Byte) |    kek_enc_data     |    kek_aad_length    (4 Byte) | kek_aad
 *  |      kek_nonce_length       (4 Byte) |      kek_nonce      |   kek_aead_tag_len   (4 Byte) | kek_aead_tag
 *  |   key_material_size_len     (4 Byte) |  key_material_size  |   key_mat_enc_length (4 Byte) | key_mat_enc_data
 */
    OH_HUKS_UNWRAP_SUITE_ECDH_AES_256_GCM_NOPADDING = 2,
    /**
 * @brief Use SM2 and then use SM4-ECB-NoPadding to encrypt the key
 *
 * @since 23
 */
    OH_HUKS_UNWRAP_SUITE_SM2_SM4_ECB_NOPADDING = 5
};

/**
 * @brief 生成的密钥类型。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_KeyGenerateType {
    /**
 * 默认生成的密钥。
 */
    OH_HUKS_KEY_GENERATE_TYPE_DEFAULT = 0,
    /**
 * 派生生成的密钥。
 */
    OH_HUKS_KEY_GENERATE_TYPE_DERIVE = 1,
    /**
 * 协商生成的密钥。
 */
    OH_HUKS_KEY_GENERATE_TYPE_AGREE = 2
};

/**
 * @brief 密钥的产生方式。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_KeyFlag {
    /**
 * 通过导入公钥接口导入的密钥。
 */
    OH_HUKS_KEY_FLAG_IMPORT_KEY = 1,
    /**
 * 通过生成密钥接口生成的密钥。
 */
    OH_HUKS_KEY_FLAG_GENERATE_KEY = 2,
    /**
 * 通过生成密钥协商接口生成的密钥。
 */
    OH_HUKS_KEY_FLAG_AGREE_KEY = 3,
    /**
 * 通过生成密钥派生接口生成的密钥。
 */
    OH_HUKS_KEY_FLAG_DERIVE_KEY = 4
};

/**
 * @brief 密钥的存储方式。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_KeyStorageType {
    /**
 * 通过接口返回给业务。
 */
    OH_HUKS_STORAGE_TEMP = 0,
    /**
 * 密钥托管在HUKS中。
 */
    OH_HUKS_STORAGE_PERSISTENT = 1,
    /**
 * 在进行密钥派生或协商时，结果密钥托管在HUKS中。
 */
    OH_HUKS_STORAGE_ONLY_USED_IN_HUKS = 2,
    /**
 * 在进行密钥派生或协商时，结果密钥可以返回给业务。
 */
    OH_HUKS_STORAGE_KEY_EXPORT_ALLOWED = 3
};

/**
 * @brief 导入密钥的类型，默认为导入公钥，导入对称密钥时不需要该字段。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_ImportKeyType {
    /**
 * 导入的密钥类型为公钥。
 */
    OH_HUKS_KEY_TYPE_PUBLIC_KEY = 0,
    /**
 * 导入的密钥类型为私钥。
 */
    OH_HUKS_KEY_TYPE_PRIVATE_KEY = 1,
    /**
 * 导入的密钥类型为公私钥对。
 */
    OH_HUKS_KEY_TYPE_KEY_PAIR = 2
};

/**
 * @brief PSS填充模式下盐值长度类型。
 *
 * @since 10
 * @version 1.0
 */
enum OH_Huks_RsaPssSaltLenType {
    /**
 * 以摘要长度设置盐值长度。
 */
    OH_HUKS_RSA_PSS_SALT_LEN_DIGEST = 0,
    /**
 * 以最大长度设置盐值长度。
 */
    OH_HUKS_RSA_PSS_SALT_LEN_MAX = 1
};

/**
 * @brief 错误码。
 *
 * @since 9
 * @version 1.0
 */
enum  OH_Huks_ErrCode {
    /**
 * 成功。
 */
    OH_HUKS_SUCCESS = 0,
    /**
 * 权限校验失败。
 */
    OH_HUKS_ERR_CODE_PERMISSION_FAIL = 201,
    /**
 * 非法参数（通用）。
 */
    OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401,
    /**
 * 不支持该API。
 */
    OH_HUKS_ERR_CODE_NOT_SUPPORTED_API = 801,

    /**
 * 不支持该子功能（特性）。
 */
    OH_HUKS_ERR_CODE_FEATURE_NOT_SUPPORTED = 12000001,
    /**
 * 缺少密钥算法参数。
 */
    OH_HUKS_ERR_CODE_MISSING_CRYPTO_ALG_ARGUMENT = 12000002,
    /**
 * 无效的密钥算法参数。
 */
    OH_HUKS_ERR_CODE_INVALID_CRYPTO_ALG_ARGUMENT = 12000003,
    /**
 * 文件错误。
 */
    OH_HUKS_ERR_CODE_FILE_OPERATION_FAIL = 12000004,
    /**
 * 进程通信错误。
 */
    OH_HUKS_ERR_CODE_COMMUNICATION_FAIL = 12000005,
    /**
 * 算法库操作失败。
 */
    OH_HUKS_ERR_CODE_CRYPTO_FAIL = 12000006,
    /**
 * 密钥访问失败 - 密钥已失效。
 */
    OH_HUKS_ERR_CODE_KEY_AUTH_PERMANENTLY_INVALIDATED = 12000007,
    /**
 * 密钥访问失败 - 密钥认证失败。
 */
    OH_HUKS_ERR_CODE_KEY_AUTH_VERIFY_FAILED = 12000008,
    /**
 * 密钥访问失败 - 密钥访问超时。
 */
    OH_HUKS_ERR_CODE_KEY_AUTH_TIME_OUT = 12000009,
    /**
 * 密钥操作会话数已达上限。
 */
    OH_HUKS_ERR_CODE_SESSION_LIMIT = 12000010,
    /**
 * 该项实体不存在。
 */
    OH_HUKS_ERR_CODE_ITEM_NOT_EXIST = 12000011,
    /**
 * 内部错误。
 */
    OH_HUKS_ERR_CODE_INTERNAL_ERROR = 12000012,
    /**
 * 认证凭据不存在。
 */
    OH_HUKS_ERR_CODE_CREDENTIAL_NOT_EXIST = 12000013,
    /**
 * 内存不足。
 */
    OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY = 12000014,
    /**
 * 调用服务失败。
 */
    OH_HUKS_ERR_CODE_CALL_SERVICE_FAILED = 12000015,
    /**
 * 需要锁屏密码，但没有设置。
 *
 * @since 11
 */
    OH_HUKS_ERR_CODE_DEVICE_PASSWORD_UNSET = 12000016,
    /**
 * 同名密钥已存在。
 *
 * @since 20
 */
    OH_HUKS_ERR_CODE_KEY_ALREADY_EXIST = 12000017,
    /**
 * 输入的参数无效。
 *
 * @since 20
 */
    OH_HUKS_ERR_CODE_INVALID_ARGUMENT = 12000018,

    /**
 * 该项实体已存在
 *
 * @since 22
 */
    OH_HUKS_ERR_CODE_ITEM_EXISTS = 12000019,

    /**
 * 提供者或Ukey内部执行失败。
 *
 * @since 22
 */
    OH_HUKS_ERR_CODE_EXTERNAL_MODULE = 12000020,

    /**
 * Pin码被锁定
 *
 * @since 22
 */
    OH_HUKS_ERR_CODE_PIN_LOCKED = 12000021,

    /**
 * Pin码错误。
 *
 * @since 22
 */
    OH_HUKS_ERR_CODE_PIN_INCORRECT = 12000022,

    /**
 * Pin码未认证通过。
 *
 * @since 22
 */
    OH_HUKS_ERR_CODE_PIN_NO_AUTH = 12000023,

    /**
 * 提供者或Ukey中的资源正在被使用。
 *
 * @since 22
 */
    OH_HUKS_ERR_CODE_BUSY = 12000024,

    /**
 * 资源超过限制。
 *
 * @since 22
 */
    OH_HUKS_ERR_CODE_EXCEED_LIMIT = 12000025
};

/**
 * @brief Defines the types of the parameters in a parameter set.
 *
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Param {
    /**
     * Tag value.
     */
    uint32_t tag;

    union {
        /** Parameter of the Boolean type. */
        bool boolParam;
        /** Parameter of the int32_t type. */
        int32_t int32Param;
        /** Parameter of the uint32_t type. */
        uint32_t uint32Param;
        /** Parameter of the uint64_t type. */
        uint64_t uint64Param;
        /** Parameter of the struct OH_Huks_Blob type. */
        struct OH_Huks_Blob blob;
    };
};

/**
 * @brief 参数集中参数的类型。
 *
 * @see OH_Huks_Param
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_TagType {
    /**
 * 非法的Tag类型。
 */
    OH_HUKS_TAG_TYPE_INVALID = 0 << 28,
    /**
 * 该Tag的数据类型为int32_t类型。
 */
    OH_HUKS_TAG_TYPE_INT = 1 << 28,
    /**
 * 该Tag的数据类型为uin32_t类型。
 */
    OH_HUKS_TAG_TYPE_UINT = 2 << 28,
    /**
 * 该Tag的数据类型为uin64_t类型。
 */
    OH_HUKS_TAG_TYPE_ULONG = 3 << 28,
    /**
 * 该Tag的数据类型为bool类型。
 */
    OH_HUKS_TAG_TYPE_BOOL = 4 << 28,
    /**
 * {@link OH_Huks_Blob}.
 */
    OH_HUKS_TAG_TYPE_BYTES = 5 << 28
};

/**
 * @brief 密钥访问控制中的用户认证类型。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_UserAuthType {
    /**
 * 用户认证类型为指纹。
 */
    OH_HUKS_USER_AUTH_TYPE_FINGERPRINT = 1 << 0,
    /**
 * 用户认证类型为人脸。
 */
    OH_HUKS_USER_AUTH_TYPE_FACE = 1 << 1,
    /**
 * 用户认证类型为PIN码。
 */
    OH_HUKS_USER_AUTH_TYPE_PIN = 1 << 2,
    /**
 * 用户认证类型为TUI PIN码。
 *
 * @since 20
 */
    OH_HUKS_USER_AUTH_TYPE_TUI_PIN = 1 << 5
};

/**
 * @brief 安全访问控制类型，表示密钥失效的原则。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_AuthAccessType {
    /**
 * 安全访问控制类型为清除密码后密钥无效。
 */
    OH_HUKS_AUTH_ACCESS_INVALID_CLEAR_PASSWORD = 1 << 0,
    /**
 * 安全访问控制类型为新录入生物特征后密钥无效。
 */
    OH_HUKS_AUTH_ACCESS_INVALID_NEW_BIO_ENROLL = 1 << 1,
    /**
 * 安全访问控制类型为该密钥总是有效。
 *
 * @since 11
 */
    OH_HUKS_AUTH_ACCESS_ALWAYS_VALID = 1 << 2
};

/**
 * @brief 表示生成或导入密钥时，指定该密钥的存储安全等级。
 *
 * @since 11
 */
enum OH_Huks_AuthStorageLevel {
    /**
 * 表示密钥仅在开机后可访问。
 * @since 11
 */
    OH_HUKS_AUTH_STORAGE_LEVEL_DE = 0,
    /**
 * 表示密钥仅在首次解锁后可访问。
 * @since 11
 */
    OH_HUKS_AUTH_STORAGE_LEVEL_CE = 1,
    /**
 * 表示密钥仅在解锁状态时可访问。
 * @since 11
 */
    OH_HUKS_AUTH_STORAGE_LEVEL_ECE = 2
};

/**
 * @brief 密钥访问控制中的用户认证模式。
 *
 * @since 12
 * @version 1.0
 */
enum OH_Huks_UserAuthMode {
    /**
 * 本地认证模式。
 * @since 12
 */
    OH_HUKS_USER_AUTH_MODE_LOCAL = 0,
    /**
 * 跨端协同认证模式。
 * @since 12
 */
    OH_HUKS_USER_AUTH_MODE_COAUTH = 1
};

/**
 * @brief 密钥使用时生成challenge的类型。
 *
 * @see OH_Huks_ChallengePosition
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_ChallengeType {
    /**
 * challenge为普通类型，默认32字节。
 */
    OH_HUKS_CHALLENGE_TYPE_NORMAL = 0,
    /**
 * challenge为用户自定义类型。支持使用多个密钥仅一次认证，challenge长度8字节有效。
 */
    OH_HUKS_CHALLENGE_TYPE_CUSTOM = 1,
    /**
 * 免challenge类型。
 */
    OH_HUKS_CHALLENGE_TYPE_NONE = 2
};

/**
 * @brief challenge类型为用户自定义类型时，生成的challenge有效长度仅为8字节连续的数据，且仅支持4种位置。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_ChallengePosition {
    /**
 * 0~7字节为当前密钥的有效challenge。
 */
    OH_HUKS_CHALLENGE_POS_0 = 0,
    /**
 * 8~15字节为当前密钥的有效challenge。
 */
    OH_HUKS_CHALLENGE_POS_1,
    /**
 * 16~23字节为当前密钥的有效challenge。
 */
    OH_HUKS_CHALLENGE_POS_2,
    /**
 * 24~31字节为当前密钥的有效challenge。
 */
    OH_HUKS_CHALLENGE_POS_3
};

/**
 * @brief 生成或导入密钥时，指定该密钥的安全签名类型。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_SecureSignType {
    /**
 * 签名类型为携带认证信息。生成或导入密钥时指定该字段，则在使用密钥进行签名时，
 * 对待签名的数据添加认证信息后进行签名。
 * 注意：携带的认证信息包含身份信息，开发者需在其隐私声明中对此身份信息的使用目的、存留策略和销毁方式进行说明。
 */
    OH_HUKS_SECURE_SIGN_WITH_AUTHINFO = 1
};

/**
 * @brief 密钥类型。
 *
 * @since 22
 */
typedef enum OH_Huks_KeyClassType {
    /**
 * @brief The default type specifics the key is stored in huks.
 *
 * @since 22
 */
    OH_HUKS_KEY_CLASS_DEFAULT = 0,
    /**
 * @brief The key is stored in external crypto provider.
 *
 * @since 22
 */
    OH_HUKS_KEY_CLASS_EXTENSION = 1
} OH_Huks_KeyClassType;

/**
 * 生成或导入密钥时，指定该密钥的封装类型。
 * @since 20
 */
enum OH_Huks_KeyWrapType {
    /**
 * 硬件唯一密钥的封装类型。
 *
 * @since 20
 */
    OH_HUKS_KEY_WRAP_TYPE_HUK_BASED = 2
};

/**
 * @brief 参数集所用的TAG值枚举。
 * <br>1-200：密钥参数标签值。
 * <br>301-500：密钥使用访问控制和使用认证相关的标签值。
 * <br>501-600：密钥认证相关的标签值。
 * <br>601-1000：其他类型的标签值预留值。
 * <br>1001-9999：扩展标签值。
 * <br>11000-12000：预留值。
 * <br>20001-N：其他标签预留值。
 *
 * @since 9
 * @version 1.0
 */
enum OH_Huks_Tag {

    /**
 * 算法类型。
 */
    OH_HUKS_TAG_ALGORITHM = OH_HUKS_TAG_TYPE_UINT | 1,
    /**
 * 密钥用途。
 */
    OH_HUKS_TAG_PURPOSE = OH_HUKS_TAG_TYPE_UINT | 2,
    /**
 * 密钥长度。
 */
    OH_HUKS_TAG_KEY_SIZE = OH_HUKS_TAG_TYPE_UINT | 3,
    /**
 * 摘要算法。
 */
    OH_HUKS_TAG_DIGEST = OH_HUKS_TAG_TYPE_UINT | 4,
    /**
 * 填充算法。
 */
    OH_HUKS_TAG_PADDING = OH_HUKS_TAG_TYPE_UINT | 5,
    /**
 * 加密模式。
 */
    OH_HUKS_TAG_BLOCK_MODE = OH_HUKS_TAG_TYPE_UINT | 6,
    /**
 * 密钥类型。
 */
    OH_HUKS_TAG_KEY_TYPE = OH_HUKS_TAG_TYPE_UINT | 7,
    /**
 * 附加身份验证数据。
 */
    OH_HUKS_TAG_ASSOCIATED_DATA = OH_HUKS_TAG_TYPE_BYTES | 8,
    /**
 * 密钥加解密的NONCE字段。
 */
    OH_HUKS_TAG_NONCE = OH_HUKS_TAG_TYPE_BYTES | 9,
    /**
 * 初始化的向量。
 */
    OH_HUKS_TAG_IV = OH_HUKS_TAG_TYPE_BYTES | 10,

    /**
 * 密钥派生时的信息。
 */
    OH_HUKS_TAG_INFO = OH_HUKS_TAG_TYPE_BYTES | 11,
    /**
 * 派生盐值。
 */
    OH_HUKS_TAG_SALT = OH_HUKS_TAG_TYPE_BYTES | 12,
    /**
 * 派生迭代次数。
 */
    OH_HUKS_TAG_ITERATION = OH_HUKS_TAG_TYPE_UINT | 14,

    /**
 * Type of the generated key. For details, see {@link OH_Huks_KeyGenerateType}.
 */
    OH_HUKS_TAG_KEY_GENERATE_TYPE = OH_HUKS_TAG_TYPE_UINT | 15,
    /**
 * 密钥协商时的算法类型。
 */
    OH_HUKS_TAG_AGREE_ALG = OH_HUKS_TAG_TYPE_UINT | 19,
    /**
 * 密钥协商时的公钥别名。
 */
    OH_HUKS_TAG_AGREE_PUBLIC_KEY_IS_KEY_ALIAS = OH_HUKS_TAG_TYPE_BOOL | 20,
    /**
 * 密钥协商时的私钥别名。
 */
    OH_HUKS_TAG_AGREE_PRIVATE_KEY_ALIAS = OH_HUKS_TAG_TYPE_BYTES | 21,
    /**
 * 用于协商的公钥。
 */
    OH_HUKS_TAG_AGREE_PUBLIC_KEY = OH_HUKS_TAG_TYPE_BYTES | 22,
    /**
 * 密钥认证时的别名。
 */
    OH_HUKS_TAG_KEY_ALIAS = OH_HUKS_TAG_TYPE_BYTES | 23,
    /**
 * 派生密钥大小。
 */
    OH_HUKS_TAG_DERIVE_KEY_SIZE = OH_HUKS_TAG_TYPE_UINT | 24,
    /**
 * Type of the imported key. For details, see {@link OH_Huks_ImportKeyType}.
 */
    OH_HUKS_TAG_IMPORT_KEY_TYPE = OH_HUKS_TAG_TYPE_UINT | 25,
    /**
 * 导入加密密钥的套件。
 */
    OH_HUKS_TAG_UNWRAP_ALGORITHM_SUITE = OH_HUKS_TAG_TYPE_UINT | 26,
    /**
 * Storage type of the derived key or key produced after key agreement.
 * For details, see {@link OH_Huks_KeyStorageType}.
 */
    OH_HUKS_TAG_DERIVED_AGREED_KEY_STORAGE_FLAG = OH_HUKS_TAG_TYPE_UINT | 29,
    /**
 * RSA算法，填充模式为PSS时的盐值长度类型。
 */
    OH_HUKS_TAG_RSA_PSS_SALT_LEN_TYPE = OH_HUKS_TAG_TYPE_UINT | 30,

    /**
 * 多用户中的所有用户。
 */
    OH_HUKS_TAG_ALL_USERS = OH_HUKS_TAG_TYPE_BOOL | 301,
    /**
 * 表示多用户id。
 */
    OH_HUKS_TAG_USER_ID = OH_HUKS_TAG_TYPE_UINT | 302,
    /**
 * 表示是否需要密钥访问控制。
 */
    OH_HUKS_TAG_NO_AUTH_REQUIRED = OH_HUKS_TAG_TYPE_BOOL | 303,
    /**
 * 表示密钥访问控制中用户认证类型。
 */
    OH_HUKS_TAG_USER_AUTH_TYPE = OH_HUKS_TAG_TYPE_UINT | 304,
    /**
 * 表示密钥访问控制类型中密钥访问的超时时间。
 */
    OH_HUKS_TAG_AUTH_TIMEOUT = OH_HUKS_TAG_TYPE_UINT | 305,
    /**
 * 表示密钥访问控制中使用密钥时传入的authtoken的类型。
 */
    OH_HUKS_TAG_AUTH_TOKEN = OH_HUKS_TAG_TYPE_BYTES | 306,
    /**
 *  Access control type. For details, see {@link OH_Huks_AuthAccessType}.
 *  This parameter must be set together with the user authentication type.
 */
    OH_HUKS_TAG_KEY_AUTH_ACCESS_TYPE = OH_HUKS_TAG_TYPE_UINT | 307,
    /**
 * 表示生成或导入密钥时，指定该密钥的签名类型。
 */
    OH_HUKS_TAG_KEY_SECURE_SIGN_TYPE = OH_HUKS_TAG_TYPE_UINT | 308,
    /**
 * Challenge type. For details, see {@link OH_Huks_ChallengeType}.
 */
    OH_HUKS_TAG_CHALLENGE_TYPE = OH_HUKS_TAG_TYPE_UINT | 309,
    /**
 *  Position of the 8-byte valid value in a custom challenge.
 *  For details, see {@link OH_Huks_ChallengePosition}.
 */
    OH_HUKS_TAG_CHALLENGE_POS = OH_HUKS_TAG_TYPE_UINT | 310,

    /**
 * 表示密钥认证用途的类型。
 */
    OH_HUKS_TAG_KEY_AUTH_PURPOSE = OH_HUKS_TAG_TYPE_UINT | 311,

    /**
 * 密钥文件存储访问控制的类别，类型可在枚举{@link OH_Huks_AuthStorageLevel}中选择。
 *
 * @since 11
 */
    OH_HUKS_TAG_AUTH_STORAGE_LEVEL = OH_HUKS_TAG_TYPE_UINT | 316,

    /**
 * 表示密钥访问控制中用户认证模式，类型可在枚举{@link OH_Huks_UserAuthMode}中选择。
 *
 * @since 12
 */
    OH_HUKS_TAG_USER_AUTH_MODE = OH_HUKS_TAG_TYPE_UINT | 319,

    /**
 * 密钥认证时的挑战值。
 */
    OH_HUKS_TAG_ATTESTATION_CHALLENGE = OH_HUKS_TAG_TYPE_BYTES | 501,
    /**
 * 密钥认证时拥有该密钥的application的Id。
 */
    OH_HUKS_TAG_ATTESTATION_APPLICATION_ID = OH_HUKS_TAG_TYPE_BYTES | 502,
    /**
 * 密钥认证时的别名。
 */
    OH_HUKS_TAG_ATTESTATION_ID_ALIAS = OH_HUKS_TAG_TYPE_BYTES | 511,
    /**
 * 密钥认证时的安全凭据。
 */
    OH_HUKS_TAG_ATTESTATION_ID_SEC_LEVEL_INFO = OH_HUKS_TAG_TYPE_BYTES | 514,
    /**
 * 密钥认证时的版本号。
 */
    OH_HUKS_TAG_ATTESTATION_ID_VERSION_INFO = OH_HUKS_TAG_TYPE_BYTES | 515,
    /**
 * @brief The tag indicates whether to overwrite the key with same alias
 *
 * @since 20
 */
    OH_HUKS_TAG_KEY_OVERRIDE = OH_HUKS_TAG_TYPE_BOOL | 520,
    /**
 * @brief The tag indicates the length of AEAD for CCM mode.
 *
 * @since 22
 */
    OH_HUKS_TAG_AE_TAG_LEN = OH_HUKS_TAG_TYPE_UINT | 521,
    /**
 * @brief The tag indicates the key class type.
 *
 * @since 22
 */
    OH_HUKS_TAG_KEY_CLASS = OH_HUKS_TAG_TYPE_UINT | 522,

    /**
 * 是否是密钥别名。
 */
    OH_HUKS_TAG_IS_KEY_ALIAS = OH_HUKS_TAG_TYPE_BOOL | 1001,
    /**
 * Key storage mode. For details, see {@link OH_Huks_KeyStorageType}.
 */
    OH_HUKS_TAG_KEY_STORAGE_FLAG = OH_HUKS_TAG_TYPE_UINT | 1002,
    /**
 * 是否允许密钥封装。
 */
    OH_HUKS_TAG_IS_ALLOWED_WRAP = OH_HUKS_TAG_TYPE_BOOL | 1003,
    /**
 * 密钥封装的类型。
 */
    OH_HUKS_TAG_KEY_WRAP_TYPE = OH_HUKS_TAG_TYPE_UINT | 1004,
    /**
 * 密钥认证的ID。
 */
    OH_HUKS_TAG_KEY_AUTH_ID = OH_HUKS_TAG_TYPE_BYTES | 1005,
    /**
 * 密钥角色。
 */
    OH_HUKS_TAG_KEY_ROLE = OH_HUKS_TAG_TYPE_UINT | 1006,
    /**
 * Key flag. For details, see {@link OH_Huks_KeyFlag}.
 */
    OH_HUKS_TAG_KEY_FLAG = OH_HUKS_TAG_TYPE_UINT | 1007,
    /**
 * 是否异步。
 */
    OH_HUKS_TAG_IS_ASYNCHRONIZED = OH_HUKS_TAG_TYPE_UINT | 1008,
    /**
 * 密钥域。
 */
    OH_HUKS_TAG_KEY_DOMAIN = OH_HUKS_TAG_TYPE_UINT | 1011,
    /**
 * 表示密钥锁屏密码访问控制字段，可限制密钥只有在用户设置了锁屏密码时可用。
 * True表示只有在密码设置时才能生成和使用密钥。
 *
 * @since 11
 */
    OH_HUKS_TAG_IS_DEVICE_PASSWORD_SET = OH_HUKS_TAG_TYPE_BOOL | 1012,

    /**
 * 用于传入GCM模式中的AEAD数据的字段。
 */
    OH_HUKS_TAG_AE_TAG = OH_HUKS_TAG_TYPE_BYTES | 10009,

    /**
 * 非对称密钥公钥数据。
 */
    OH_HUKS_TAG_SYMMETRIC_KEY_DATA = OH_HUKS_TAG_TYPE_BYTES | 20001,
    /**
 * 非对称密钥公钥数据。
 */
    OH_HUKS_TAG_ASYMMETRIC_PUBLIC_KEY_DATA = OH_HUKS_TAG_TYPE_BYTES | 20002,
    /**
 * 非对称密钥私钥数据。
 */
    OH_HUKS_TAG_ASYMMETRIC_PRIVATE_KEY_DATA = OH_HUKS_TAG_TYPE_BYTES | 20003,
    /**
 * @brief 该标签表示具有相同开发者ID的应用之间的共享密钥组。
 *
 * @since 23
 */
    OH_HUKS_TAG_KEY_ACCESS_GROUP = OH_HUKS_TAG_TYPE_BYTES | 523
};

/**
 * @brief Defines the returned data, including a status code and related description.
 *
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Result {
    /**
     * Status code. For details, see {@link OH_Huks_ErrCode}.
     */
    int32_t errorCode;
    /**
     * Description of the status code.
     */
    const char *errorMsg;
    /**
     * Other data.
     */
    uint8_t *data;
};

/**
 * @brief Defines the struct of a parameter set.
 *
 * @since 9
 * @version 1.0
 */
struct OH_Huks_ParamSet {
    /**
     * Memory size of the parameter set.
     */
    uint32_t paramSetSize;
    /**
     * Number of parameters in the parameter set.
     */
    uint32_t paramsCnt;
    /** Parameter array. */
    struct OH_Huks_Param params[];
};

/**
 * @brief Defines the struct of a certificate chain.
 *
 * @since 9
 * @version 1.0
 */
struct OH_Huks_CertChain {
    /**
     * Pointer to the certificate data.
     */
    struct OH_Huks_Blob *certs;
    /**
     * Number of certificates.
     */
    uint32_t certsCount;
};

/**
 * @brief Defines the struct of a binary large object (BLOB).
 *
 * @since 9
 * @version 1.0
 */
struct OH_Huks_Blob {
    /**
     * Data size.
     */
    uint32_t size;
    /**
     * Pointer to the memory in which the data is stored.
     */
    uint8_t *data;
};

/**
 * @brief Defines the struct of key information.
 *
 * @since 9
 * @version 1.0
 */
struct OH_Huks_KeyInfo {
    /**
     * Alias used in key attestation.
     */
    struct OH_Huks_Blob alias;
    /**
     * Pointer to the key parameter set.
     */
    struct OH_Huks_ParamSet *paramSet;
};

/**
 * @brief Defines the struct of a public key.
 *
 * @since 9
 * @version 1.0
 */
struct OH_Huks_PubKeyInfo {
    /**
     * Algorithm of the public key.
     */
    enum OH_Huks_KeyAlg keyAlg;
    /**
     * Length of the public key.
     */
    uint32_t keySize;
    /**
     * Length of **n** or **X**.
     */
    uint32_t nOrXSize;
    /**
     * Length of **e** or **Y**.
     */
    uint32_t eOrYSize;
    /**
     * Placeholder size.
     */
    uint32_t placeHolder;
};

/**
 * @brief Defines the struct of an RSA key.
 *
 * @since 9
 * @version 1.0
 */
struct OH_Huks_KeyMaterialRsa {
    /**
     * Algorithm of the key.
     */
    enum OH_Huks_KeyAlg keyAlg;
    /**
     * Length of the key.
     */
    uint32_t keySize;
    /**
     * Length of **n**.
     */
    uint32_t nSize;
    /**
     * Length of **e**.
     */
    uint32_t eSize;
    /**
     * Length of **d**.
     */
    uint32_t dSize;
};

/**
 * @brief Defines the struct of an Elliptic Curve Cryptography (ECC) key.
 *
 * @since 9
 * @version 1.0
 */
struct OH_Huks_KeyMaterialEcc {
    /**
     * Algorithm of the key.
     */
    enum OH_Huks_KeyAlg keyAlg;
    /**
     * Length of the key.
     */
    uint32_t keySize;
    /**
     * Length of **x**.
     */
    uint32_t xSize;
    /**
     * Length of **y**.
     */
    uint32_t ySize;
    /**
     * Length of **z**.
     */
    uint32_t zSize;
};

/**
 * @brief Defines the struct for a DSA key.
 *
 * @since 9
 * @version 1.0
 */
struct OH_Huks_KeyMaterialDsa {
    /**
     * Algorithm of the key.
     */
    enum OH_Huks_KeyAlg keyAlg;
    /**
     * Length of the key.
     */
    uint32_t keySize;
    /**
     * Length of **x**.
     */
    uint32_t xSize;
    /**
     * Length of **y**.
     */
    uint32_t ySize;
    /**
     * Length of **p**.
     */
    uint32_t pSize;
    /**
     * Length of **q**.
     */
    uint32_t qSize;
    /**
     * Length of **g**.
     */
    uint32_t gSize;
};

/**
 * @brief Defines the struct for a DH key.
 *
 * @since 9
 * @version 1.0
 */
struct OH_Huks_KeyMaterialDh {
    /**
     * Algorithm of the key.
     */
    enum OH_Huks_KeyAlg keyAlg;
    /**
     * Length of the DH key.
     */
    uint32_t keySize;
    /**
     * Length of the public key.
     */
    uint32_t pubKeySize;
    /**
     * Length of the private key.
     */
    uint32_t priKeySize;
    /**
     * Reserved.
     */
    uint32_t reserved;
};

/**
 * @brief Defines a struct of a 25519 key.
 *
 * @since 9
 * @version 1.0
 */
struct OH_Huks_KeyMaterial25519 {
    /**
     * Algorithm of the key.
     */
    enum OH_Huks_KeyAlg keyAlg;
    /**
     * Length of the 25519 key.
     */
    uint32_t keySize;
    /**
     * Length of the public key.
     */
    uint32_t pubKeySize;
    /**
     * Length of the private key.
     */
    uint32_t priKeySize;
    /**
     * Reserved.
     */
    uint32_t reserved;
};

/**
 * @brief Defines the struct of a key alias set.
 *
 * @since 20
 * @version 1.0
 */
struct OH_Huks_KeyAliasSet {
    /**
     * Number of key aliases.
     */
    uint32_t aliasesCnt;
    /**
     * Pointer to the key alias set.
     */
    struct OH_Huks_Blob *aliases;
};

/**
 * @brief Length of the AEAD one-time random number, in bytes.
 *
 * @since 9
 * @version 1.0
 */
#define OH_HUKS_AE_NONCE_LEN 12

/**
 * @brief Maximum length of a key alias, in bytes.
 *
 * @since 9
 * @version 1.0
 */
#define OH_HUKS_MAX_KEY_ALIAS_LEN 64

/**
 * @brief Maximum length of a process name, in bytes.
 *
 * @since 9
 * @version 1.0
 */
#define OH_HUKS_MAX_PROCESS_NAME_LEN 50

/**
 * @brief Maximum length of a random number, in bytes.
 *
 * @since 9
 * @version 1.0
 */
#define OH_HUKS_MAX_RANDOM_LEN 1024

/**
 * @brief Minimum length of the signature result, in bytes.
 *
 * @since 9
 * @version 1.0
 */
#define OH_HUKS_SIGNATURE_MIN_SIZE 64

/**
 * @brief Maximum size of the exported data, in bytes.
 *
 * @since 9
 * @version 1.0
 */
#define OH_HUKS_MAX_OUT_BLOB_SIZE (5 * 1024 * 1024)

/**
 * @brief Maximum size of the key to be imported, in bytes.
 *
 * @since 9
 * @version 1.0
 */
#define OH_HUKS_WRAPPED_FORMAT_MAX_SIZE (1024 * 1024)

/**
 * @brief Maximum number of data blocks of the key to be imported, in bytes.
 *
 * @since 9
 * @version 1.0
 */
#define OH_HUKS_IMPORT_WRAPPED_KEY_TOTAL_BLOBS 10

/**
 * @brief Byte length of the challenge value during access control.
 *
 * @since 9
 * @version 1.0
 */
#define TOKEN_CHALLENGE_LEN 32

/**
 * @brief Byte length of the SHA-256 signature.
 *
 * @since 9
 * @version 1.0
 */
#define SHA256_SIGN_LEN 32

/**
 * @brief Byte length of the challenge value during access control.
 *
 * @since 9
 * @version 1.0
 */
#define TOKEN_SIZE 32

/**
 * @brief Maximum user authentication timeout.
 *
 * @since 9
 * @version 1.0
 */
#define MAX_AUTH_TIMEOUT_SECOND 60

/**
 * @brief Version of the secure signature data.
 *
 * @since 9
 * @version 1.0
 */
#define SECURE_SIGN_VERSION 0x01000001
#ifdef __cplusplus
}
#endif

/** @} */
#endif /* NATIVE_OH_HUKS_TYPE_H */