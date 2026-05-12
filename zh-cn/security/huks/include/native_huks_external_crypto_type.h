
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup HuksExternalCryptoTypeApi
 * @{
 *
 * @brief Defines the macros, enumerated values, data structures,
 *    used by OpenHarmony Universal KeyStore (HUKS) APIs.
 *
 * @since 22
 * @version 1.0
 */

/**
 * @file native_huks_external_crypto_type.h
 *
 * @brief 定义面向外部密钥管理扩展的结构体与枚举类型。
 *
 * @library libhuks_external_crypto.z.so
 * @syscap SystemCapability.Security.Huks.CryptoExtension
 *
 *     include "huks/include/native_huks_type.h"
 * @kit UniversalKeystoreKit
 * @since 22
 * @version 1.0
 */

#ifndef NATIVE_HUKS_EXTERNAL_CRYPTO_TYPE_H
#define NATIVE_HUKS_EXTERNAL_CRYPTO_TYPE_H

#include "native_huks_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义provider名称的最大字节长度。
 *
 * @since 22
 */
#define OH_HUKS_EXTERNAL_CRYPTO_MAX_PROVIDER_NAME_LEN 100

/**
 * @brief 定义资源ID的最大字节长度。
 *
 * @since 22
 */
#define OH_HUKS_EXTERNAL_CRYPTO_MAX_RESOURCE_ID_LEN   512

/**
 * @brief 定义参数集合中单个参数的结构体。
 *
 * @since 22
 */
typedef struct OH_Huks_ExternalCryptoParam {
    /**
     * @brief 标签值。
     *
     * @since 22
     */
    uint32_t tag;
    /**
     * @brief 标签内容。
     *
     * @since 22
     */
    union {
        /**
         * @brief 布尔类型参数。
         *
         * @since 22
         */
        bool boolParam;
        /**
         * @brief int32_t类型参数。
         *
         * @since 22
         */
        int32_t int32Param;
        /**
         * @brief uint32_t类型参数。
         *
         * @since 22
         */
        uint32_t uint32Param;
        /**
         * @brief uint64_t类型参数。
         *
         * @since 22
         */
        uint64_t uint64Param;
        /**
         * @brief OH_Huks_Blob类型参数。
         *
         * @since 22
         */
        struct OH_Huks_Blob blob;
    };
} OH_Huks_ExternalCryptoParam;

/**
 * @brief 定义外部加密参数集合的结构。
 *
 * @since 22
 */
typedef struct OH_Huks_ExternalCryptoParamSet {
    /**
    * @brief 参数集合所占内存大小，单位：Byte。
    *
    * @since 22
    */
    uint32_t paramSetSize;
    /**
    * @brief 参数集合中的参数数量。
    *
    * @since 22
    */
    uint32_t paramsCnt;
    /**
    * @brief 参数数组，大小由paramSetSize与paramsCnt决定。
    *
    * @since 22
    */
    OH_Huks_ExternalCryptoParam params[];
} OH_Huks_ExternalCryptoParamSet;

/**
 * @brief 列举参数集合中使用的标签值。
 *
 * @since 22
 */
typedef enum OH_Huks_ExternalCryptoTag {
    /**
     * @brief PIN码。
     *
     * @since 22
     */
    OH_HUKS_EXT_CRYPTO_TAG_UKEY_PIN = OH_HUKS_TAG_TYPE_BYTES | 200001,

    /**
     * @brief 能力名称。
     *
     * @since 22
     */
    OH_HUKS_EXT_CRYPTO_TAG_ABILITY_NAME = OH_HUKS_TAG_TYPE_BYTES | 200002,

    /**
     * @brief 附加数据。
     *
     * @since 22
     */
    OH_HUKS_EXT_CRYPTO_TAG_EXTRA_DATA = OH_HUKS_TAG_TYPE_BYTES | 200003,

    /**
     * @brief 调用方的UID。
     *
     * @since 22
     */
    OH_HUKS_EXT_CRYPTO_TAG_UID = OH_HUKS_TAG_TYPE_INT | 200004,

    /**
     * @brief 证书链用途。
     *
     * @since 22
     */
    OH_HUKS_EXT_CRYPTO_TAG_PURPOSE = OH_HUKS_TAG_TYPE_INT | 200005,

    /**
     * @brief 获取属性操作的超时时间，单位：s。
     *
     * @since 22
     */
    OH_HUKS_EXT_CRYPTO_TAG_TIMEOUT = OH_HUKS_TAG_TYPE_UINT | 200006
} OH_Huks_ExternalCryptoTag;

/**
 * @brief 列举Ukey PIN码认证状态。
 *
 * @since 22
 */
typedef enum OH_Huks_ExternalPinAuthState {
    /**
     * @brief PIN码未认证。
     *
     * @since 22
     */
    OH_HUKS_EXT_CRYPTO_PIN_NO_AUTH = 0,

    /**
     * @brief PIN码认证成功。
     *
     * @since 22
     */
    OH_HUKS_EXT_CRYPTO_PIN_AUTH_SUCCEEDED = 1,

    /**
     * @brief PIN码被锁。
     *
     * @since 22
     */
    OH_HUKS_EXT_CRYPTO_PIN_LOCKED = 2
} OH_Huks_ExternalPinAuthState;

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* NATIVE_HUKS_EXTERNAL_CRYPTO_TYPE_H */