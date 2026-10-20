/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup RDB
 * @{
 *
 * @brief 分布式数据管理（Distributed Data Manager，data）支持单设备的各种结构化数据的持久化，以及端云间的同步、共享功能。
 * 分布式数据管理定义了一系列数据类型，可以对数据进行增删改查。
 *
 * @since 10
 */

/**
 * @file oh_rdb_crypto_param.h
 *
 * @include database/rdb/oh_rdb_crypto_param.h
 * @brief 提供与关系型数据库加密参数相关的函数和枚举。
 *
 * @kit ArkData
 * @library libnative_rdb_ndk.z.so
 * @syscap SystemCapability.DistributedDataManager.RelationalStore.Core
 *
 * @since 20
 */

#ifndef OH_RDB_CRYPTO_PARAM_ZH_CN_H
#define OH_RDB_CRYPTO_PARAM_ZH_CN_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 数据库加密算法。
 *
 * @since 20
 */
typedef enum Rdb_EncryptionAlgo {
    /**
     * @brief 表示数据库使用RDB_AES_256_GCM加密。
     *
     */
    RDB_AES_256_GCM = 0,
    /**
     * @brief 表示数据库使用RDB_AES_256_CBC加密。
     *
     */
    RDB_AES_256_CBC,
    /**
     * @brief 表示数据库不加密。
     *
     * @since 22
     */
    RDB_PLAIN_TEXT,
} Rdb_EncryptionAlgo;

/**
 * @brief 打开数据库时支持的HMAC算法。
 *
 * @since 20
 */
typedef enum Rdb_HmacAlgo {
    /**
     * @brief RDB_HMAC_SHA1算法。
     *
     */
    RDB_HMAC_SHA1 = 0,
    /**
     * @brief RDB_HMAC_SHA256算法。
     *
     */
    RDB_HMAC_SHA256,
    /**
     * @brief RDB_HMAC_SHA512算法。
     *
     */
    RDB_HMAC_SHA512,
} Rdb_HmacAlgo;

/**
 * @brief 打开数据库时支持的KDF算法。
 *
 * @since 20
 */
typedef enum Rdb_KdfAlgo {
    /**
     * @brief RDB_KDF_SHA1算法。
     *
     */
    RDB_KDF_SHA1 = 0,
    /**
     * @brief RDB_KDF_SHA256算法。
     *
     */
    RDB_KDF_SHA256,
    /**
     * @brief RDB_KDF_SHA512算法。
     *
     */
    RDB_KDF_SHA512,
} Rdb_KdfAlgo;

/**
 * @brief 指定打开加密数据库时使用的加密参数。
 *
 * @since 20
 */
typedef struct OH_Rdb_CryptoParam OH_Rdb_CryptoParam;

/**
 * @brief 创建一个{@link OH_Rdb_CryptoParam}实例对象。
 *
 * @return 成功时返回指向{@link OH_Rdb_CryptoParam}实例的指针。
 *     <br>否则返回nullptr。使用完成后，必须通过{@link OH_Rdb_DestroyCryptoParam}接口释放内存。
 * @see OH_Rdb_DestroyCryptoParam.
 * @since 20
 */
OH_Rdb_CryptoParam *OH_Rdb_CreateCryptoParam(void);

/**
 * @brief 销毁一个{@link OH_Rdb_CryptoParam}实例对象。
 *
 * @param param 表示指向{@link OH_Rdb_CryptoParam}实例的指针。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
 */
int OH_Rdb_DestroyCryptoParam(OH_Rdb_CryptoParam *param);

/**
 * @brief 设置{@link OH_Rdb_CryptoParam}对象的密钥数据。
 *
 * @param param 表示指向{@link OH_Rdb_CryptoParam}实例的指针。
 * @param key 表示指向密钥数据的指针。
 * @param length 表示密钥数组的大小。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
 */
int OH_Crypto_SetEncryptionKey(OH_Rdb_CryptoParam *param, const uint8_t *key, int32_t length);

/**
 * @brief 设置打开加密数据库时使用的KDF算法迭代次数。
 *
 * @param param 表示指向{@link OH_Rdb_CryptoParam}实例的指针。
 * @param iteration 表示迭代次数。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
 */
int OH_Crypto_SetIteration(OH_Rdb_CryptoParam *param, int64_t iteration);

/**
 * @brief 设置打开加密数据库时使用的加密算法。
 *
 * @param param 表示指向{@link OH_Rdb_CryptoParam}实例的指针。
 * @param algo 表示加密算法。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
 */
int OH_Crypto_SetEncryptionAlgo(OH_Rdb_CryptoParam *param, int32_t algo);

/**
 * @brief 设置打开加密数据库时使用的HMAC算法。
 *
 * @param param 表示指向{@link OH_Rdb_CryptoParam}实例的指针。
 * @param algo 表示HMAC算法。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
 */
int OH_Crypto_SetHmacAlgo(OH_Rdb_CryptoParam *param, int32_t algo);

/**
 * @brief 设置打开加密数据库时使用的KDF算法。
 *
 * @param param 表示指向{@link OH_Rdb_CryptoParam}实例的指针。
 * @param algo 表示KDF算法。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
 */
int OH_Crypto_SetKdfAlgo(OH_Rdb_CryptoParam *param, int32_t algo);

/**
 * @brief 设置打开加密数据库时使用的页大小。
 *
 * @param param 表示指向{@link OH_Rdb_CryptoParam}实例的指针。
 * @param size 表示页大小，单位为字节，取值应为2的幂值，最小值为1024，最大值65536。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
 */
int OH_Crypto_SetCryptoPageSize(OH_Rdb_CryptoParam *param, int64_t size);

#ifdef __cplusplus
};
#endif
#endif
/** @} */
