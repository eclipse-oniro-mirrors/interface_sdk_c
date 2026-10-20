/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @file oh_data_values_buckets.h
 *
 * @include database/data/oh_data_values_buckets.h
 * @brief 提供与存储数据值相关的结构定义、函数和枚举。
 *
 * @kit ArkData
 * @library libnative_rdb_ndk.z.so
 * @syscap SystemCapability.DistributedDataManager.RelationalStore.Core
 *
 * @since 18
 */


#ifndef OH_VALUES_BUCKETS_ZH_CN_H
#define OH_VALUES_BUCKETS_ZH_CN_H
#include "database/rdb/oh_values_bucket.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义OH_Data_VBuckets结构体类型。
 *
 * @since 18
 */
typedef struct OH_Data_VBuckets OH_Data_VBuckets;

/**
 * @brief 创建OH_Data_VBuckets实例。
 *
 * @return 执行成功时返回指向{@link OH_Data_VBuckets}实例的指针。否则返回nullptr。
 *     <br>使用完成后，必须通过{@link OH_VBuckets_Destroy}接口释放内存。
 * @see OH_VBuckets_Destroy.
 * @since 18
 */
OH_Data_VBuckets *OH_VBuckets_Create(void);

/**
 * @brief 销毁OH_Data_VBuckets对象。
 *
 * @param buckets 表示指向{@link OH_Data_VBuckets}实例的指针。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_VBuckets_Destroy(OH_Data_VBuckets *buckets);

/**
 * @brief 添加OH_VBucket类型数据。
 *
 * @param buckets 表示指向{@link OH_Data_VBuckets}实例的指针。
 * @param row 表示指向{@link OH_VBucket}实例的指针。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_VBuckets_PutRow(OH_Data_VBuckets *buckets, const OH_VBucket *row);

/**
 * @brief 添加OH_Data_VBuckets类型数据。
 *
 * @param buckets 表示指向{@link OH_Data_VBuckets}实例的指针。
 * @param rows 表示指向{@link OH_Data_VBuckets}实例的指针。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_VBuckets_PutRows(OH_Data_VBuckets *buckets, const OH_Data_VBuckets *rows);

/**
 * @brief 获取OH_Data_VBuckets中OH_VBucket的行数。
 *
 * @param buckets 表示指向{@link OH_Data_VBuckets}实例的指针。
 * @param count 一个输出参数，表示{@link OH_Data_VBuckets}中{@link OH_VBucket}的个数。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_VBuckets_RowCount(OH_Data_VBuckets *buckets, size_t *count);

#ifdef __cplusplus
};
#endif
#endif
/** @} */
