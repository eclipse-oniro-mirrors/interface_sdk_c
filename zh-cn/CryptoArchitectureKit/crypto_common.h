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
 * @addtogroup CryptoCommonApi
 * @{
 * @brief 描述OpenHarmony为应用提供的加解密通用接口。
 * @since 12
 */

/**
 * @file crypto_common.h
 * @brief 定义加解密通用的数据结构和错误码。
 * @syscap SystemCapability.Security.CryptoFramework
 * @library libohcrypto.so
 * @kit CryptoArchitectureKit
 * @since 12
 */

#ifndef CRYPTO_COMMON_H
#define CRYPTO_COMMON_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 加解密数据结构体。
 * @since 12
 */
typedef struct Crypto_DataBlob {
    /**
     * @brief 数据缓冲区。
     * @since 12
     */
    uint8_t *data;
    /**
     * @brief 数据长度。
     * @since 12
     */
    size_t len;
} Crypto_DataBlob;

/**
 * @brief 枚举错误码。
 * @since 12
 */
typedef enum {
    /**
     * @brief 表示操作成功。
     * @since 12
     */
    CRYPTO_SUCCESS = 0,
    /**
     * @brief 表示输入参数无效。
     * @since 12
     */
    CRYPTO_INVALID_PARAMS = 401,
    /**
     * @brief 表示不支持的功能或算法。
     * @since 12
     */
    CRYPTO_NOT_SUPPORTED = 801,
    /**
     * @brief 表示内存操作失败。
     * @since 12
     */
    CRYPTO_MEMORY_ERROR = 17620001,
    /**
     * @brief 表示参数校验失败。
     * @since 20
     */
    CRYPTO_PARAMETER_CHECK_FAILED = 17620003,
    /**
     * @brief 表示无效的函数调用。
     * @since 26.0.0
     */
    CRYPTO_INVALID_CALL = 17620004,
    /**
     * @brief 表示加解密操作错误。
     * @since 12
     */
    CRYPTO_OPERTION_ERROR = 17630001,
} OH_Crypto_ErrCode;

/**
 * @brief 定义加解密模式。
 * @since 12
 */
typedef enum {
    /**
     * @brief 表示加密操作。
     * @since 12
     */
    CRYPTO_ENCRYPT_MODE = 0,
    /**
     * @brief 表示解密操作。
     * @since 12
     */
    CRYPTO_DECRYPT_MODE = 1,
} Crypto_CipherMode;

/**
 * @brief 释放数据Blob的内存。
 * @param dataBlob [in] 待释放的数据Blob。
 * @since 12
 */
void OH_Crypto_FreeDataBlob(Crypto_DataBlob *dataBlob);

#ifdef __cplusplus
}
#endif

#endif /* CRYPTO_COMMON_H */
/** @} */
