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
 * @brief Defines enums, structs, macros, and error codes in HUKS.
 *
 * @library libhuks_ndk.z.so
 * @syscap SystemCapability.Security.Huks.Core
 *
 * @include <huks/native_huks_type.h>
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
 * @brief Maximum user authentication timeout interval, in seconds.
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

/**
 * @brief Enumerates the key purposes. Multiple purposes can be combined using bitwise OR (\|).
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_KeyPurpose {
    /**
     * Used to encrypt the plaintext.
     */
    OH_HUKS_KEY_PURPOSE_ENCRYPT = 1,
    /**
     * Used to decrypt the cipher text.
     */
    OH_HUKS_KEY_PURPOSE_DECRYPT = 2,
    /**
     * Used for signing.
     */
    OH_HUKS_KEY_PURPOSE_SIGN = 4,
    /**
     * Used to verify the signature.
     */
    OH_HUKS_KEY_PURPOSE_VERIFY = 8,
    /**
     * Used to derive a key.
     */
    OH_HUKS_KEY_PURPOSE_DERIVE = 16,
    /**
     * Used for exporting a key in ciphertext.
     */
    OH_HUKS_KEY_PURPOSE_WRAP = 32,
    /**
     * Used for importing a key in ciphertext.
     */
    OH_HUKS_KEY_PURPOSE_UNWRAP = 64,
    /**
     * Used to generate a message authentication code (MAC).
     */
    OH_HUKS_KEY_PURPOSE_MAC = 128,
    /**
     * Used for key agreement.
     */
    OH_HUKS_KEY_PURPOSE_AGREE = 256,
} OH_Huks_KeyPurpose;

/**
 * @brief Enumerates the digest algorithms.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_KeyDigest {
    /**
     * No digest algorithm.
     */
    OH_HUKS_DIGEST_NONE = 0,
    /**
     * MD5.
     */
    OH_HUKS_DIGEST_MD5 = 1,
    /**
     * SM3.
     */
    OH_HUKS_DIGEST_SM3 = 2,
    /**
     * SHA-1.
     */
    OH_HUKS_DIGEST_SHA1 = 10,
    /**
     * SHA-224.
     */
    OH_HUKS_DIGEST_SHA224 = 11,
    /**
     * SHA-256.
     */
    OH_HUKS_DIGEST_SHA256 = 12,
    /**
     * SHA-384.
     */
    OH_HUKS_DIGEST_SHA384 = 13,
    /**
     * SHA-512.
     */
    OH_HUKS_DIGEST_SHA512 = 14,
} OH_Huks_KeyDigest;

/**
 * @brief Enumerates the padding algorithm types.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_KeyPadding {
    /**
     * No padding algorithm.
     */
    OH_HUKS_PADDING_NONE = 0,
    /**
     * OAEP.
     */
    OH_HUKS_PADDING_OAEP = 1,
    /**
     * PSS.
     */
    OH_HUKS_PADDING_PSS = 2,
    /**
     * PKCS1_V1_5.
     */
    OH_HUKS_PADDING_PKCS1_V1_5 = 3,
    /**
     * PKCS #5.
     */
    OH_HUKS_PADDING_PKCS5 = 4,
    /**
     * PKCS #7.
     */
    OH_HUKS_PADDING_PKCS7 = 5,
    /**
     * ISO IEC 9796-2.
     * @since 18
     */
    OH_HUKS_PADDING_ISO_IEC_9796_2 = 6,
    /** ISO IEC 9797-1.
     * @since 18
     */
    OH_HUKS_PADDING_ISO_IEC_9797_1 = 7,
} OH_Huks_KeyPadding;

/**
 * @brief Cipher mode.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_CipherMode {
    /**
     * ECB.
     */
    OH_HUKS_MODE_ECB = 1,
    /**
     * CBC.
     */
    OH_HUKS_MODE_CBC = 2,
    /**
     * CTR.
     */
    OH_HUKS_MODE_CTR = 3,
    /**
     * OFB.
     */
    OH_HUKS_MODE_OFB = 4,
    /**
     * CFB.
     * @since 12
     */
    OH_HUKS_MODE_CFB = 5,
    /**
     * CCM.
     */
    OH_HUKS_MODE_CCM = 31,
    /**
     * GCM.
     */
    OH_HUKS_MODE_GCM = 32,
} OH_Huks_CipherMode;

/**
 * @brief Enumerates the key sizes of different algorithms.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_KeySize {
    /**
     * RSA key of 512 bits.
     */
    OH_HUKS_RSA_KEY_SIZE_512 = 512,
    /**
     * RSA key of 768 bits.
     */
    OH_HUKS_RSA_KEY_SIZE_768 = 768,
    /**
     * RSA key of 1024 bits.
     */
    OH_HUKS_RSA_KEY_SIZE_1024 = 1024,
    /**
     * RSA key of 2048 bits.
     */
    OH_HUKS_RSA_KEY_SIZE_2048 = 2048,
    /**
     * RSA key of 3072 bits.
     */
    OH_HUKS_RSA_KEY_SIZE_3072 = 3072,
    /**
     * RSA key of 4096 bits.
     */
    OH_HUKS_RSA_KEY_SIZE_4096 = 4096,

    /**
     * ECC key of 224 bits.
     */
    OH_HUKS_ECC_KEY_SIZE_224 = 224,
    /**
     * ECC key of 256 bits.
     */
    OH_HUKS_ECC_KEY_SIZE_256 = 256,
    /**
     * ECC key of 384 bits.
     */
    OH_HUKS_ECC_KEY_SIZE_384 = 384,
    /**
     * ECC key of 521 bits.
     */
    OH_HUKS_ECC_KEY_SIZE_521 = 521,

    /**
     * AES key of 128 bits.
     */
    OH_HUKS_AES_KEY_SIZE_128 = 128,
    /**
     * AES key of 192 bits.
     */
    OH_HUKS_AES_KEY_SIZE_192 = 192,
    /**
     * AES key of 256 bits.
     */
    OH_HUKS_AES_KEY_SIZE_256 = 256,
    /**
     * AES key of 512 bits.
     */
    OH_HUKS_AES_KEY_SIZE_512 = 512,

    /**
     * Curve25519 key of 256 bits.
     */
    OH_HUKS_CURVE25519_KEY_SIZE_256 = 256,

    /**
     * DH key of 2048 bits.
     */
    OH_HUKS_DH_KEY_SIZE_2048 = 2048,
    /**
     * DH key of 3072 bits.
     */
    OH_HUKS_DH_KEY_SIZE_3072 = 3072,
    /**
     * DH key of 4096 bits.
     */
    OH_HUKS_DH_KEY_SIZE_4096 = 4096,

    /**
     * SM2 key of 256 bits.
     */
    OH_HUKS_SM2_KEY_SIZE_256 = 256,
    /**
     * SM4 key of 128 bits.
     */
    OH_HUKS_SM4_KEY_SIZE_128 = 128,

    /** DES key of 64 bits.
     * @since 18
     */
    OH_HUKS_DES_KEY_SIZE_64 = 64,
    /** 3DES key of 128 bits.
     * @since 18
     */
    OH_HUKS_3DES_KEY_SIZE_128 = 128,
    /** 3DES key of 192 bits.
     * @since 18
     */
    OH_HUKS_3DES_KEY_SIZE_192 = 192,
} OH_Huks_KeySize;

/**
 * @brief Enumerates the algorithms for keys.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_KeyAlg {
    /**
     * RSA.
     */
    OH_HUKS_ALG_RSA = 1,
    /**
     * ECC.
     */
    OH_HUKS_ALG_ECC = 2,
    /**
     * DSA.
     */
    OH_HUKS_ALG_DSA = 3,

    /**
     * Advanced Encryption Standard (AES).
     */
    OH_HUKS_ALG_AES = 20,
    /**
     * HMAC algorithm.
     */
    OH_HUKS_ALG_HMAC = 50,
    /**
     * HKDF.
     */
    OH_HUKS_ALG_HKDF = 51,
    /**
     * PBKDF2.
     */
    OH_HUKS_ALG_PBKDF2 = 52,

    /**
     * ECDH.
     */
    OH_HUKS_ALG_ECDH = 100,
    /**
     * X25519.
     */
    OH_HUKS_ALG_X25519 = 101,
    /**
     * Ed25519.
     */
    OH_HUKS_ALG_ED25519 = 102,
    /**
     * DH.
     */
    OH_HUKS_ALG_DH = 103,

    /**
     * ShangMi2 (SM2).
     */
    OH_HUKS_ALG_SM2 = 150,
    /**
     * SM3.
     */
    OH_HUKS_ALG_SM3 = 151,
    /**
     * SM4.
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
    OH_HUKS_ALG_CMAC = 162,
} OH_Huks_KeyAlg;

/**
 * @brief Enumerates the algorithm suites that can be used for importing of a key in ciphertext.
 * <br>Key material format for **OH_HUKS_UNWRAP_SUITE_X25519_AES_256_GCM_NOPADDING**:
 * | x25519_plain_pubkey_length  (4 Byte) | x25519_plain_pubkey |  agreekey_aad_length (4 Byte) | agreekey_aad
 * |   agreekey_nonce_length     (4 Byte) |   agreekey_nonce    | agreekey_aead_tag_len(4 Byte) | agreekey_aead_tag
 * |    kek_enc_data_length      (4 Byte) |    kek_enc_data     |    kek_aad_length    (4 Byte) | kek_aad
 * |      kek_nonce_length       (4 Byte) |      kek_nonce      |   kek_aead_tag_len   (4 Byte) | kek_aead_tag
 * |   key_material_size_len     (4 Byte) |  key_material_size  |   key_mat_enc_length (4 Byte) | key_mat_enc_data
 *
 * <br>Key material format for **OH_HUKS_UNWRAP_SUITE_ECDH_AES_256_GCM_NOPADDING**:
 * |  ECC_plain_pubkey_length    (4 Byte) |  ECC_plain_pubkey   |  agreekey_aad_length (4 Byte) | agreekey_aad
 * |   agreekey_nonce_length     (4 Byte) |   agreekey_nonce    | agreekey_aead_tag_len(4 Byte) | agreekey_aead_tag
 * |    kek_enc_data_length      (4 Byte) |    kek_enc_data     |    kek_aad_length    (4 Byte) | kek_aad
 * |      kek_nonce_length       (4 Byte) |      kek_nonce      |   kek_aead_tag_len   (4 Byte) | kek_aead_tag
 * |   key_material_size_len     (4 Byte) |  key_material_size  |   key_mat_enc_length (4 Byte) | key_mat_enc_data
 *
 * <br>Key material format for **OH_HUKS_UNWRAP_SUITE_SM2_SM4_ECB_NOPADDING**:
 * |     kek_SM4_enc_length      (4 Byte) |      EN_SM4_key     | importkey_enc_length (4 Byte) | importkey_enc
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_AlgSuite {
    /**
     * Key material in Length-Value format, using X25519 for key agreement and AES-256-GCM for encryption and
     * decryption. For details about the material format, see the preceding description.
     */
    OH_HUKS_UNWRAP_SUITE_X25519_AES_256_GCM_NOPADDING = 1,

    /**
     * Key material in Length-Value format, using ECDH-p256 for key agreement and AES-256-GCM for encryption and
     * decryption. For details about the material format, see the preceding description.
     */
    OH_HUKS_UNWRAP_SUITE_ECDH_AES_256_GCM_NOPADDING = 2,
    /**
     * @brief Key material in Length-Value format, using the temporary SM4 key to encrypt the imported key and using
     * the SM2 key that has been imported to HUKS to encrypt the SM4 key. For details about the material format, see
     * the preceding description.
     *
     * @since 23
     */
    OH_HUKS_UNWRAP_SUITE_SM2_SM4_ECB_NOPADDING = 5,
} OH_Huks_AlgSuite;

/**
 * @brief Enumerates the types of the key generated.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_KeyGenerateType {
    /**
     * Key generated by default.
     */
    OH_HUKS_KEY_GENERATE_TYPE_DEFAULT = 0,
    /**
     * Derived key.
     */
    OH_HUKS_KEY_GENERATE_TYPE_DERIVE = 1,
    /**
     * Key generated by key agreement.
     */
    OH_HUKS_KEY_GENERATE_TYPE_AGREE = 2,
} OH_Huks_KeyGenerateType;

/**
 * @brief Enumerates the key generation types.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_KeyFlag {
    /**
     * Import a public key using a function.
     */
    OH_HUKS_KEY_FLAG_IMPORT_KEY = 1,
    /**
     * Generate a key by using a function.
     */
    OH_HUKS_KEY_FLAG_GENERATE_KEY = 2,
    /**
     * Generate a key by using a key agreement function.
     */
    OH_HUKS_KEY_FLAG_AGREE_KEY = 3,
    /**
     * Derive a key by using a function.
     */
    OH_HUKS_KEY_FLAG_DERIVE_KEY = 4,
} OH_Huks_KeyFlag;

/**
 * @brief Enumerates the key storage types.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_KeyStorageType {
    /**
     * Return the key to the service via the API.
     */
    OH_HUKS_STORAGE_TEMP = 0,
    /**
     * Store the key in HUKS.
     */
    OH_HUKS_STORAGE_PERSISTENT = 1,
    /**
     * Store the key generated from key derivation or key agreement in HUKS.
     */
    OH_HUKS_STORAGE_ONLY_USED_IN_HUKS = 2,
    /**
     * Return the key generated from key derivation or key agreement to the service.
     */
    OH_HUKS_STORAGE_KEY_EXPORT_ALLOWED = 3,
} OH_Huks_KeyStorageType;

/**
 * @brief Enumerates the types of the key to import. By default, a public key is imported. This field is not required
 * when a symmetric key is imported.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_ImportKeyType {
    /**
     * Public key.
     */
    OH_HUKS_KEY_TYPE_PUBLIC_KEY = 0,
    /**
     * Private key.
     */
    OH_HUKS_KEY_TYPE_PRIVATE_KEY = 1,
    /**
     * Public and private key pair.
     */
    OH_HUKS_KEY_TYPE_KEY_PAIR = 2,
} OH_Huks_ImportKeyType;

/**
 * @brief Enumerates the length types of the salt value in PSS padding mode of the RSA algorithm.
 *
 * @since 10
 * @version 1.0
 */
typedef enum OH_Huks_RsaPssSaltLenType {
    /**
     * The salt length is set to the digest length.
     */
    OH_HUKS_RSA_PSS_SALT_LEN_DIGEST = 0,
    /**
     * The salt length is set to the maximum length.
     */
    OH_HUKS_RSA_PSS_SALT_LEN_MAX = 1,
} OH_Huks_RsaPssSaltLenType;

/**
 * @brief Enumerates error codes.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_ErrCode {
    /**
     * Success.
     */
    OH_HUKS_SUCCESS = 0,
    /**
     * Permission verification failed.
     */
    OH_HUKS_ERR_CODE_PERMISSION_FAIL = 201,
    /**
     * Invalid parameter (universal).
     */
    OH_HUKS_ERR_CODE_ILLEGAL_ARGUMENT = 401,
    /**
     * The API is not supported.
     */
    OH_HUKS_ERR_CODE_NOT_SUPPORTED_API = 801,

    /**
     * The feature is not supported.
     */
    OH_HUKS_ERR_CODE_FEATURE_NOT_SUPPORTED = 12000001,
    /**
     * Key algorithm parameters are missing.
     */
    OH_HUKS_ERR_CODE_MISSING_CRYPTO_ALG_ARGUMENT = 12000002,
    /**
     * Invalid key algorithm parameter.
     */
    OH_HUKS_ERR_CODE_INVALID_CRYPTO_ALG_ARGUMENT = 12000003,
    /**
     * File operation failed.
     */
    OH_HUKS_ERR_CODE_FILE_OPERATION_FAIL = 12000004,
    /**
     * The process communication failed.
     */
    OH_HUKS_ERR_CODE_COMMUNICATION_FAIL = 12000005,
    /**
     * Crypto operation failed.
     */
    OH_HUKS_ERR_CODE_CRYPTO_FAIL = 12000006,
    /**
     * Failed to access the key because the key has expired.
     */
    OH_HUKS_ERR_CODE_KEY_AUTH_PERMANENTLY_INVALIDATED = 12000007,
    /**
     * Failed to access the key because the authentication has failed.
     */
    OH_HUKS_ERR_CODE_KEY_AUTH_VERIFY_FAILED = 12000008,
    /**
     * Key access timed out.
     */
    OH_HUKS_ERR_CODE_KEY_AUTH_TIME_OUT = 12000009,
    /**
     * The number of key operation sessions has reached the limit.
     */
    OH_HUKS_ERR_CODE_SESSION_LIMIT = 12000010,
    /**
     * The entity does not exist.
     */
    OH_HUKS_ERR_CODE_ITEM_NOT_EXIST = 12000011,
    /**
     * Internal error.
     */
    OH_HUKS_ERR_CODE_INTERNAL_ERROR = 12000012,
    /**
     * The authentication credential does not exist.
     */
    OH_HUKS_ERR_CODE_CREDENTIAL_NOT_EXIST = 12000013,
    /**
     * Insufficient memory.
     */
    OH_HUKS_ERR_CODE_INSUFFICIENT_MEMORY = 12000014,
    /**
     * Failed to invoke the service.
     */
    OH_HUKS_ERR_CODE_CALL_SERVICE_FAILED = 12000015,
    /**
     * The lock screen password required is not set.
     * @since 11
     */
    OH_HUKS_ERR_CODE_DEVICE_PASSWORD_UNSET = 12000016,
    /**
     * A key with the same name already exists.
     * @since 20
     */
    OH_HUKS_ERR_CODE_KEY_ALREADY_EXIST = 12000017,
    /**
     * An input parameter is invalid.
     * @since 20
     */
    OH_HUKS_ERR_CODE_INVALID_ARGUMENT = 12000018,

    /**
     * The entity already exists.
     * @since 22
     */
    OH_HUKS_ERR_CODE_ITEM_EXISTS = 12000019,

    /**
     * The provider or UKey internal execution fails.
     * @since 22
     */
    OH_HUKS_ERR_CODE_EXTERNAL_MODULE = 12000020,

    /**
     * The PIN is locked.
     * @since 22
     */
    OH_HUKS_ERR_CODE_PIN_LOCKED = 12000021,

    /**
     * Incorrect PIN.
     * @since 22
     */
    OH_HUKS_ERR_CODE_PIN_INCORRECT = 12000022,

    /**
     * PIN authentication fails.
     * @since 22
     */
    OH_HUKS_ERR_CODE_PIN_NO_AUTH = 12000023,

    /**
     * The provider or UKey resources are being used.
     * @since 22
     */
    OH_HUKS_ERR_CODE_BUSY = 12000024,

    /**
     * The resource limit is exceeded.
     * @since 22
     */
    OH_HUKS_ERR_CODE_EXCEED_LIMIT = 12000025,
} OH_Huks_ErrCode;

/**
 * @brief Enumerates parameter types.
 *
 * @see OH_Huks_Param
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_TagType {
    /**
     * Invalid tag type.
     */
    OH_HUKS_TAG_TYPE_INVALID = 0 << 28,
    /**
     * int32_t.
     */
    OH_HUKS_TAG_TYPE_INT = 1 << 28,
    /**
     * uint32_t.
     */
    OH_HUKS_TAG_TYPE_UINT = 2 << 28,
    /**
     * uint64_t.
     */
    OH_HUKS_TAG_TYPE_ULONG = 3 << 28,
    /**
     * Boolean.
     */
    OH_HUKS_TAG_TYPE_BOOL = 4 << 28,
    /**
     * {@link OH_Huks_Blob}.
     */
    OH_HUKS_TAG_TYPE_BYTES = 5 << 28,
} OH_Huks_TagType;

/**
 * @brief Enumerates the user authentication types in key access control.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_UserAuthType {
    /**
     * Fingerprint authentication.
     */
    OH_HUKS_USER_AUTH_TYPE_FINGERPRINT = 1 << 0,
    /**
     * Facial authentication.
     */
    OH_HUKS_USER_AUTH_TYPE_FACE = 1 << 1,
    /**
     * PIN authentication.
     */
    OH_HUKS_USER_AUTH_TYPE_PIN = 1 << 2,
    /**
     * TUI PIN authentication.
     * @since 20
     */
    OH_HUKS_USER_AUTH_TYPE_TUI_PIN = 1 << 5,
} OH_Huks_UserAuthType;

/**
 * @brief Enumerates the rules for invalidating a key.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_AuthAccessType {
    /**
     * The key becomes invalid after the password is cleared.
     */
    OH_HUKS_AUTH_ACCESS_INVALID_CLEAR_PASSWORD = 1 << 0,
    /**
     * The key becomes invalid after a new biometric feature is enrolled.
     */
    OH_HUKS_AUTH_ACCESS_INVALID_NEW_BIO_ENROLL = 1 << 1,
    /**
     * The key is always valid.
     * @since 11
     */
    OH_HUKS_AUTH_ACCESS_ALWAYS_VALID = 1 << 2,
} OH_Huks_AuthAccessType;

/**
 * @brief Enumerates the security levels for storing the key generated or imported.
 *
 * @since 11
 */
typedef enum OH_Huks_AuthStorageLevel {
    /**
     * The key can be accessed only after the device is started.
     * @since 11
     */
    OH_HUKS_AUTH_STORAGE_LEVEL_DE = 0,
    /**
     * The key can be accessed only after the first unlock of the device.
     * @since 11
     */
    OH_HUKS_AUTH_STORAGE_LEVEL_CE = 1,
    /**
     * The key can be accessed only when the device is unlocked.
     * @since 11
     */
    OH_HUKS_AUTH_STORAGE_LEVEL_ECE = 2,
} OH_Huks_AuthStorageLevel;

/**
 * @brief Enumerates the user authentication modes in key access control.
 *
 * @since 12
 * @version 1.0
 */
typedef enum OH_Huks_UserAuthMode {
    /**
     * Local authentication.
     * @since 12
     */
    OH_HUKS_USER_AUTH_MODE_LOCAL = 0,
    /**
     * Cross-device collaborative authentication.
     * @since 12
     */
    OH_HUKS_USER_AUTH_MODE_COAUTH = 1,
} OH_Huks_UserAuthMode;

/**
 * @brief Enumerates the types of the challenge generated when a key is used.
 *
 * @see OH_Huks_ChallengePosition
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_ChallengeType {
    /**
     * Normal challenge, which is of 32 bytes by default.
     */
    OH_HUKS_CHALLENGE_TYPE_NORMAL = 0,
    /**
     * Custom challenge, which supports one-time authentication for multiple keys. The valid value of a custom
     * challenge is of 8 bytes.
     */
    OH_HUKS_CHALLENGE_TYPE_CUSTOM = 1,
    /**
     * Challenge is not required.
     */
    OH_HUKS_CHALLENGE_TYPE_NONE = 2,
} OH_Huks_ChallengeType;

/**
 * @brief Enumerates the positions of the 8-byte valid value in a custom challenge generated.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_ChallengePosition {
    /**
     * Bytes 0 to 7.
     */
    OH_HUKS_CHALLENGE_POS_0 = 0,
    /**
     * Bytes 8 to 15.
     */
    OH_HUKS_CHALLENGE_POS_1 = 1,
    /**
     * Bytes 16 to 23.
     */
    OH_HUKS_CHALLENGE_POS_2 = 2,
    /**
     * Bytes 24 to 31.
     */
    OH_HUKS_CHALLENGE_POS_3 = 3,
} OH_Huks_ChallengePosition;

/**
 * @brief Enumerates the signature types of the key generated or imported.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_SecureSignType {
    /**
     * The signature carries authentication information. This field is specified when a key is generated or imported.
     * When the key is used for signing, the data will be added with the authentication information and then be signed.
     * Note: The carried authentication information includes identity information. You need to describe the purpose,
     * retention policy, and destruction method of the identity information in the privacy statement.
     */
    OH_HUKS_SECURE_SIGN_WITH_AUTHINFO = 1,
} OH_Huks_SecureSignType;

/**
 * @brief Key type.
 *
 * @since 22
 */
typedef enum OH_Huks_KeyClassType {
    /**
     * @brief Default type. The key is stored in HUKS.
     *
     * @since 22
     */
    OH_HUKS_KEY_CLASS_DEFAULT = 0,
    /**
     * @brief The key is stored in an external encryption capability provider.
     *
     * @since 22
     */
    OH_HUKS_KEY_CLASS_EXTENSION = 1,
} OH_Huks_KeyClassType;

/**
 * Enumerates the wrap type of the key generated or imported.
 * @since 20
 */
typedef enum OH_Huks_KeyWrapType {
    /**
     * Wrap type of the unique hardware key.
     * @since 20
     */
    OH_HUKS_KEY_WRAP_TYPE_HUK_BASED = 2,
} OH_Huks_KeyWrapType;

/**
 * @brief Enumerates the tags contained in a parameter set.
 * <br>1 to 200: key parameter tag values.
 * <br>301 to 500: tag values related to access control and authentication of key usage.
 * <br>501 to 600: tag values related to key authentication.
 * <br>601 to 1000: reserved values for other types of tag values.
 * <br>1001 to 9999: extended tag values.
 * <br>11000 to 12000: reserved values.
 * <br>20001 to N: reserved tag values.
 *
 * @since 9
 * @version 1.0
 */
typedef enum OH_Huks_Tag {
    /**
     * Algorithm type. For details, see {@link OH_Huks_KeyAlg}.
     */
    OH_HUKS_TAG_ALGORITHM = OH_HUKS_TAG_TYPE_UINT | 1,
    /**
     * Key purpose. For details, see {@link OH_Huks_KeyPurpose}.
     */
    OH_HUKS_TAG_PURPOSE = OH_HUKS_TAG_TYPE_UINT | 2,
    /**
     * Key length, in bits. For details, see {@link OH_Huks_KeySize}.
     */
    OH_HUKS_TAG_KEY_SIZE = OH_HUKS_TAG_TYPE_UINT | 3,
    /**
     * Digest algorithm. For details, see {@link OH_Huks_KeyDigest}.
     */
    OH_HUKS_TAG_DIGEST = OH_HUKS_TAG_TYPE_UINT | 4,
    /**
     * Padding algorithm. For details, see {@link OH_Huks_KeyPadding}.
     */
    OH_HUKS_TAG_PADDING = OH_HUKS_TAG_TYPE_UINT | 5,
    /** Encryption mode. For details, see {@link OH_Huks_CipherMode}. */
    OH_HUKS_TAG_BLOCK_MODE = OH_HUKS_TAG_TYPE_UINT | 6,
    /**
     * Key type.
     */
    OH_HUKS_TAG_KEY_TYPE = OH_HUKS_TAG_TYPE_UINT | 7,
    /**
     * Associated authentication data.
     */
    OH_HUKS_TAG_ASSOCIATED_DATA = OH_HUKS_TAG_TYPE_BYTES | 8,
    /**
     * **NONCE** field for key encryption and decryption.
     */
    OH_HUKS_TAG_NONCE = OH_HUKS_TAG_TYPE_BYTES | 9,
    /**
     * Initialized vector (IV).
     */
    OH_HUKS_TAG_IV = OH_HUKS_TAG_TYPE_BYTES | 10,

    /**
     * Information generated during key derivation.
     */
    OH_HUKS_TAG_INFO = OH_HUKS_TAG_TYPE_BYTES | 11,
    /**
     * Salt value used for key derivation.
     */
    OH_HUKS_TAG_SALT = OH_HUKS_TAG_TYPE_BYTES | 12,
    /**
     * Number of iterations for key derivation.
     */
    OH_HUKS_TAG_ITERATION = OH_HUKS_TAG_TYPE_UINT | 14,

    /**
     * Type of the generated key. For details, see {@link OH_Huks_KeyGenerateType}.
     */
    OH_HUKS_TAG_KEY_GENERATE_TYPE = OH_HUKS_TAG_TYPE_UINT | 15,
    /**
     * Algorithm used in key agreement.
     */
    OH_HUKS_TAG_AGREE_ALG = OH_HUKS_TAG_TYPE_UINT | 19,
    /**
     * Alias of the public key used for key agreement.
     */
    OH_HUKS_TAG_AGREE_PUBLIC_KEY_IS_KEY_ALIAS = OH_HUKS_TAG_TYPE_BOOL | 20,
    /**
     * Alias of the private key used for key agreement.
     */
    OH_HUKS_TAG_AGREE_PRIVATE_KEY_ALIAS = OH_HUKS_TAG_TYPE_BYTES | 21,
    /**
     * Public key used for key agreement.
     */
    OH_HUKS_TAG_AGREE_PUBLIC_KEY = OH_HUKS_TAG_TYPE_BYTES | 22,
    /**
     * Key alias.
     */
    OH_HUKS_TAG_KEY_ALIAS = OH_HUKS_TAG_TYPE_BYTES | 23,
    /**
     * Size of the derived key, in bytes.
     */
    OH_HUKS_TAG_DERIVE_KEY_SIZE = OH_HUKS_TAG_TYPE_UINT | 24,
    /**
     * Type of the imported key. For details, see {@link OH_Huks_ImportKeyType}.
     */
    OH_HUKS_TAG_IMPORT_KEY_TYPE = OH_HUKS_TAG_TYPE_UINT | 25,
    /**
     * Suite of the imported encryption key. For details, see {@link OH_Huks_AlgSuite}.
     */
    OH_HUKS_TAG_UNWRAP_ALGORITHM_SUITE = OH_HUKS_TAG_TYPE_UINT | 26,
    /**
     * Storage type of the derived key or key produced after key agreement. For details, see
     * {@link OH_Huks_KeyStorageType}.
     */
    OH_HUKS_TAG_DERIVED_AGREED_KEY_STORAGE_FLAG = OH_HUKS_TAG_TYPE_UINT | 29,
    /**
     * Salt length type when the padding mode of the RSA algorithm is PSS. For details, see
     * {@link OH_Huks_RsaPssSaltLenType}.
     */
    OH_HUKS_TAG_RSA_PSS_SALT_LEN_TYPE = OH_HUKS_TAG_TYPE_UINT | 30,

    /**
     * All users in the multi-user scenario.
     */
    OH_HUKS_TAG_ALL_USERS = OH_HUKS_TAG_TYPE_BOOL | 301,
    /** Multi-user ID. */
    OH_HUKS_TAG_USER_ID = OH_HUKS_TAG_TYPE_UINT | 302,
    /**
     * Whether key access control is required.
     */
    OH_HUKS_TAG_NO_AUTH_REQUIRED = OH_HUKS_TAG_TYPE_BOOL | 303,
    /**
     * User authentication mode in key access control. For details, see {@link OH_Huks_UserAuthType}.
     */
    OH_HUKS_TAG_USER_AUTH_TYPE = OH_HUKS_TAG_TYPE_UINT | 304,
    /**
     * Timeout duration for key access in key access control, in seconds.
     */
    OH_HUKS_TAG_AUTH_TIMEOUT = OH_HUKS_TAG_TYPE_UINT | 305,
    /**
     * Authentication token for the key.
     */
    OH_HUKS_TAG_AUTH_TOKEN = OH_HUKS_TAG_TYPE_BYTES | 306,
    /**
     * Key access control type, which must be set together with the user authentication type. For details, see
     * {@link OH_Huks_AuthAccessType}.
     */
    OH_HUKS_TAG_KEY_AUTH_ACCESS_TYPE = OH_HUKS_TAG_TYPE_UINT | 307,
    /**
     * Signature type of the key generated or imported.
     */
    OH_HUKS_TAG_KEY_SECURE_SIGN_TYPE = OH_HUKS_TAG_TYPE_UINT | 308,
    /**
     * Challenge type. For details, see {@link OH_Huks_ChallengeType}.
     */
    OH_HUKS_TAG_CHALLENGE_TYPE = OH_HUKS_TAG_TYPE_UINT | 309,
    /**
     *  Position of the 8-byte valid value in a custom challenge. For details, see {@link OH_Huks_ChallengePosition}.
     */
    OH_HUKS_TAG_CHALLENGE_POS = OH_HUKS_TAG_TYPE_UINT | 310,

    /**
     * Type of the key authentication purpose.
     */
    OH_HUKS_TAG_KEY_AUTH_PURPOSE = OH_HUKS_TAG_TYPE_UINT | 311,

    /**
     * Security levels for storing the key. For details, see {@link OH_Huks_AuthStorageLevel}.
     * @since 11
     */
    OH_HUKS_TAG_AUTH_STORAGE_LEVEL = OH_HUKS_TAG_TYPE_UINT | 316,

    /**
     * User authentication mode in key access control. For details, see {@link OH_Huks_UserAuthMode}.
     * @since 12
     */
    OH_HUKS_TAG_USER_AUTH_MODE = OH_HUKS_TAG_TYPE_UINT | 319,

    /**
     * Challenge value used in the attestation.
     */
    OH_HUKS_TAG_ATTESTATION_CHALLENGE = OH_HUKS_TAG_TYPE_BYTES | 501,
    /**
     * ID of the application that has the key during key authentication.
     */
    OH_HUKS_TAG_ATTESTATION_APPLICATION_ID = OH_HUKS_TAG_TYPE_BYTES | 502,
    /**
     * Key alias.
     */
    OH_HUKS_TAG_ATTESTATION_ID_ALIAS = OH_HUKS_TAG_TYPE_BYTES | 511,
    /**
     * Security level used in key attestation.
     */
    OH_HUKS_TAG_ATTESTATION_ID_SEC_LEVEL_INFO = OH_HUKS_TAG_TYPE_BYTES | 514,
    /**
     * Version information used in key attestation.
     */
    OH_HUKS_TAG_ATTESTATION_ID_VERSION_INFO = OH_HUKS_TAG_TYPE_BYTES | 515,
    /**
     * @brief Whether to overwrite the key with the same name.
     *
     * @since 20
     */
    OH_HUKS_TAG_KEY_OVERRIDE = OH_HUKS_TAG_TYPE_BOOL | 520,
    /**
     * @brief Length of the specified AEAD in CCM mode.
     *
     * @since 22
     */
    OH_HUKS_TAG_AE_TAG_LEN = OH_HUKS_TAG_TYPE_UINT | 521,
    /**
     * @brief Key type, which is used to distinguish the key managed by HUKS on the device from the key stored in an
     * external device.
     *
     * @since 22
     */
    OH_HUKS_TAG_KEY_CLASS = OH_HUKS_TAG_TYPE_UINT | 522,
    /**
     * @brief Group ID. Keys can be shared among the same group of developers with the same developer ID.
     *
     * @since 23
     */
    OH_HUKS_TAG_KEY_ACCESS_GROUP = OH_HUKS_TAG_TYPE_BYTES | 523,
    /**
     * Whether it is a key alias.
     */
    OH_HUKS_TAG_IS_KEY_ALIAS = OH_HUKS_TAG_TYPE_BOOL | 1001,
    /**
     * Key storage mode. For details, see {@link OH_Huks_KeyStorageType}.
     */
    OH_HUKS_TAG_KEY_STORAGE_FLAG = OH_HUKS_TAG_TYPE_UINT | 1002,
    /**
     * Whether to allow the key to be wrapped.
     */
    OH_HUKS_TAG_IS_ALLOWED_WRAP = OH_HUKS_TAG_TYPE_BOOL | 1003,
    /**
     * Key wrap type.
     */
    OH_HUKS_TAG_KEY_WRAP_TYPE = OH_HUKS_TAG_TYPE_UINT | 1004,
    /**
     * Authentication ID.
     */
    OH_HUKS_TAG_KEY_AUTH_ID = OH_HUKS_TAG_TYPE_BYTES | 1005,
    /**
     * Role of the key.
     */
    OH_HUKS_TAG_KEY_ROLE = OH_HUKS_TAG_TYPE_UINT | 1006,
    /**
     * Key flag. For details, see {@link OH_Huks_KeyFlag}.
     */
    OH_HUKS_TAG_KEY_FLAG = OH_HUKS_TAG_TYPE_UINT | 1007,
    /**
     * Whether the invocation is asynchronous.
     */
    OH_HUKS_TAG_IS_ASYNCHRONIZED = OH_HUKS_TAG_TYPE_UINT | 1008,
    /**
     * Key domain.
     */
    OH_HUKS_TAG_KEY_DOMAIN = OH_HUKS_TAG_TYPE_UINT | 1011,
    /**
     * Whether the key is accessible only when the user sets a lock screen password.<br> **true** indicates that the
     * key can be generated and used only when a password is set. **false** indicates that the key can be generated and
     * used without setting a password.
     * @since 11
     */
    OH_HUKS_TAG_IS_DEVICE_PASSWORD_SET = OH_HUKS_TAG_TYPE_BOOL | 1012,

    /**
     * AEAD in GCM mode.
     */
    OH_HUKS_TAG_AE_TAG = OH_HUKS_TAG_TYPE_BYTES | 10009,

    /**
     * Symmetric key data.
     */
    OH_HUKS_TAG_SYMMETRIC_KEY_DATA = OH_HUKS_TAG_TYPE_BYTES | 20001,
    /**
     * Public key data of the asymmetric key pair.
     */
    OH_HUKS_TAG_ASYMMETRIC_PUBLIC_KEY_DATA = OH_HUKS_TAG_TYPE_BYTES | 20002,
    /**
     * Private key data of the asymmetric key pair.
     */
    OH_HUKS_TAG_ASYMMETRIC_PRIVATE_KEY_DATA = OH_HUKS_TAG_TYPE_BYTES | 20003,
} OH_Huks_Tag;

/**
 * @brief Defines the returned data, including a status code and related description.
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_Huks_Result {
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
} OH_Huks_Result;

/**
 * @brief Defines the struct of a binary large object (BLOB).
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_Huks_Blob {
    /** Data size in bytes. */
    uint32_t size;
    /**
     * Pointer to the data.
     */
    uint8_t *data;
} OH_Huks_Blob;

/**
 * @brief Defines the types of the parameters in a parameter set.
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_Huks_Param {
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
} OH_Huks_Param;

/**
 * @brief Defines the struct of a parameter set.
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_Huks_ParamSet {
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
} OH_Huks_ParamSet;

/**
 * @brief Defines the struct of a certificate chain.
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_Huks_CertChain {
    /**
     * Pointer to the certificate data.
     */
    struct OH_Huks_Blob *certs;
    /**
     * Number of certificates.
     */
    uint32_t certsCount;
} OH_Huks_CertChain;

/**
 * @brief Defines the struct of key information.
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_Huks_KeyInfo {
    /**
     * Key alias.
     */
    struct OH_Huks_Blob alias;
    /**
     * Pointer to the key parameter set.
     */
    struct OH_Huks_ParamSet *paramSet;
} OH_Huks_KeyInfo;

/**
 * @brief Defines the struct of a public key.
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_Huks_PubKeyInfo {
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
     * Placeholder size, intended for memory alignment or reserving space for future algorithmic extensions.
     */
    uint32_t placeHolder;
} OH_Huks_PubKeyInfo;

/**
 * @brief Defines the struct for an RSA key.
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_Huks_KeyMaterialRsa {
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
} OH_Huks_KeyMaterialRsa;

/**
 * @brief Defines the struct for an ECC key.
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_Huks_KeyMaterialEcc {
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
    /** Length of **z**, which corresponds to the size of the private key d. */
    uint32_t zSize;
} OH_Huks_KeyMaterialEcc;

/**
 * @brief Defines the struct for a DSA key.
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_Huks_KeyMaterialDsa {
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
} OH_Huks_KeyMaterialDsa;

/**
 * @brief Defines the struct for a DH key.
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_Huks_KeyMaterialDh {
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
     * Reserved field.
     */
    uint32_t reserved;
} OH_Huks_KeyMaterialDh;

/**
 * @brief Defines a struct of a 25519 key.
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_Huks_KeyMaterial25519 {
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
     * Reserved field.
     */
    uint32_t reserved;
} OH_Huks_KeyMaterial25519;

/**
 * @brief Defines the struct of a key alias set.
 *
 * @since 20
 * @version 1.0
 */
typedef struct OH_Huks_KeyAliasSet {
    /**
     * Number of key aliases.
     */
    uint32_t aliasesCnt;
    /**
     * Pointer to the key alias set.
     */
    struct OH_Huks_Blob *aliases;
} OH_Huks_KeyAliasSet;

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* NATIVE_OH_HUKS_TYPE_H */
