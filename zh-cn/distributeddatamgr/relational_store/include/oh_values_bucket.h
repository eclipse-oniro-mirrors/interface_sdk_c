/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @file oh_values_bucket.h
 *
 * @include database/rdb/oh_values_bucket.h
 * @brief 用于存储键值对的类型。
 *
 * @kit ArkData
 * @library libnative_rdb_ndk.z.so
 * @syscap SystemCapability.DistributedDataManager.RelationalStore.Core
 * @since 10
 */

#ifndef OH_VALUES_BUCKET_ZH_CN_H
#define OH_VALUES_BUCKET_ZH_CN_H

#include <stdint.h>

#include "database/data/data_asset.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于存储键值对的类型。
 *
 * @since 10
 */
typedef struct OH_VBucket OH_VBucket;


/**
 * @brief 用于存储键值对的类型。
 *
 * @since 10
 */
typedef struct OH_VBucket {
    /**
     * OH_VBucket结构体的唯一标识符。
     */
    int64_t id;

    /**
     * 表示结构体的存储键值对的数量。
     */
    uint16_t capability;

    /**
     * @brief 将char*值放入给定列名的OH_VBucket对象中。
     *
     * @param bucket 表示指向{@link OH_VBucket}实例的指针。
     * @param field 表示数据库表中的列名，不能为空指针。
     * @param value 数据库表中指定列名对应的值。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     *     <br>RDB_OK 表示成功。
     *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
     * @see OH_VBucket.
     * @since 10
     */
    int (*putText)(OH_VBucket *bucket, const char *field, const char *value);

    /**
     * @brief 将int64_t值放入给定列名的OH_VBucket对象中。
     *
     * @param bucket 表示指向{@link OH_VBucket}实例的指针。
     * @param field 表示数据库表中的列名，不能为空指针。
     * @param value 数据库表中指定列名对应的值。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     *     <br>RDB_OK 表示成功。
     *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
     * @see OH_VBucket.
     * @since 10
     */
    int (*putInt64)(OH_VBucket *bucket, const char *field, int64_t value);

    /**
     * @brief 将double值放入给定列名的OH_VBucket对象中。
     *
     * @param bucket 表示指向{@link OH_VBucket}实例的指针。
     * @param field 表示数据库表中的列名，不能为空指针。
     * @param value 数据库表中指定列名对应的值。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     *     <br>RDB_OK 表示成功。
     *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
     * @see OH_VBucket.
     * @since 10
     */
    int (*putReal)(OH_VBucket *bucket, const char *field, double value);

    /**
     * @brief 将const uint8_t *值放入给定列名的OH_VBucket对象中。
     *
     * @param bucket 表示指向{@link OH_VBucket}实例的指针。
     * @param field 表示数据库表中的列名，不能为空指针。
     * @param value 表示const uint8_t *类型的值。
     * @param size 表示value的长度。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     *     <br>RDB_OK 表示成功。
     *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
     * @see OH_VBucket.
     * @since 10
     */
    int (*putBlob)(OH_VBucket *bucket, const char *field, const uint8_t *value, uint32_t size);

    /**
     * @brief 将NULL值放入给定列名的OH_VBucket对象中。
     *
     * @param bucket 表示指向{@link OH_VBucket}实例的指针。
     * @param field 表示数据库表中的列名，不能为空指针。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     *     <br>RDB_OK 表示成功。
     *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
     * @see OH_VBucket.
     * @since 10
     */
    int (*putNull)(OH_VBucket *bucket, const char *field);

    /**
     * @brief 清空{@link OH_VBucket}对象。
     *
     * @param bucket 表示指向{@link OH_VBucket}实例的指针。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     *     <br>RDB_OK 表示成功。
     *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
     * @see OH_VBucket.
     * @since 10
     */
    int (*clear)(OH_VBucket *bucket);

    /**
     * @brief 销毁{@link OH_VBucket}对象，并回收该对象占用的内存。
     *
     * @param bucket 表示指向{@link OH_VBucket}实例的指针。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     *     <br>RDB_OK 表示成功。
     *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
     * @see OH_VBucket.
     * @since 10
     */
    int (*destroy)(OH_VBucket *bucket);
};

/**
 * @brief 将{@link Data_Asset} 类型的对象放入给定列名的{@link OH_VBucket}对象中。
 *
 * @param bucket 表示指向{@link OH_VBucket}实例的指针。
 * @param field 数据库表中的列名，不能为空。
 * @param value 数据库表中指定列名对应的值。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_VBucket.
 * @since 11
 */
int OH_VBucket_PutAsset(OH_VBucket *bucket, const char *field, Data_Asset *value);

/**
 * @brief 将{@link Data_Asset} 类型的对象数组放入给定列名的{@link OH_VBucket}对象中。
 *
 * @param bucket 表示指向{@link OH_VBucket}实例的指针。
 * @param field 数据库表中的列名，不能为空。
 * @param value 数据库表中指定列名对应的值。
 * @param count 表示传入的{@link Data_Asset}对象数组元素的个数。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_VBucket.
 * @since 11
 */
int OH_VBucket_PutAssets(OH_VBucket *bucket, const char *field, Data_Asset **value, uint32_t count);

/**
 * @brief 将float数组类型对象放入给定列名的{@link OH_VBucket}对象中。
 *
 * @param bucket 表示指向{@link OH_VBucket}实例的指针。
 * @param field 数据库表中的列名，不能为空。
 * @param vec 表示指向float数组的指针。
 * @param len 表示float数组的大小。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_VBucket.
 * @since 18
 */
int OH_VBucket_PutFloatVector(OH_VBucket *bucket, const char *field, const float *vec, size_t len);

/**
 * @brief 将任意长度的整数类型对象放入给定列名的{@link OH_VBucket}对象中。
 *
 * @param bucket 表示指向{@link OH_VBucket}实例的指针。
 * @param field 数据库表中的列名，不能为空。
 * @param sign 表示整数类型对象是正数还是负数，0表示正数，1表示负数。
 * @param trueForm 表示指向整数类型数组的指针。
 * @param len 表示整数数组的大小。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_VBucket.
 * @since 18
 */
int OH_VBucket_PutUnlimitedInt(OH_VBucket *bucket, const char *field, int sign, const uint64_t *trueForm, size_t len);
#ifdef __cplusplus
};
#endif

/** @} */

#endif // OH_VALUES_BUCKET_ZH_CN_H
