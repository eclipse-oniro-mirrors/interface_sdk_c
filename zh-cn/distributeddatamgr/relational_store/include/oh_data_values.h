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
 * @file oh_data_values.h
 *
 * @include database/data/oh_data_values.h
 * @brief 提供与多条数据值相关的函数和枚举。
 *
 * @kit ArkData
 * @library libnative_rdb_ndk.z.so
 * @syscap SystemCapability.DistributedDataManager.RelationalStore.Core
 *
 * @since 18
 */
#ifndef OH_DATA_VALUES_ZH_CN_H
#define OH_DATA_VALUES_ZH_CN_H
#include <inttypes.h>
#include <stdbool.h>

#include "database/data/data_asset.h"
#include "database/data/oh_data_value.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief OH_Data_Values结构类型，用于存储多条数据值。
 *
 * @since 18
 */
typedef struct OH_Data_Values OH_Data_Values;

/**
 * @brief 创建{@link OH_Data_Values}实例，用于存储多个数据值。
 *
 * @return 执行成功时返回指向{@link OH_Data_Values}实例的指针，否则返回nullptr。
 *     <br>使用完成后，必须通过{@link OH_Values_Destroy}接口释放内存。
 * @see OH_Values_Destroy.
 * @since 18
 */
OH_Data_Values *OH_Values_Create(void);

/**
 * @brief 销毁{@link OH_Data_Values}对象。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_Destroy(OH_Data_Values *values);

/**
 * @brief 添加OH_Data_Value类型数据给OH_Data_Values对象。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param val 表示指向{@link OH_Data_Value}对象的指针。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_Put(OH_Data_Values *values, const OH_Data_Value *val);

/**
 * @brief 添加空数据给OH_Data_Values对象。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_PutNull(OH_Data_Values *values);

/**
 * @brief 添加整型数据给OH_Data_Values对象。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param val 表示整型数据。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_PutInt(OH_Data_Values *values, int64_t val);

/**
 * @brief 添加REAL类型数据给OH_Data_Values对象。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param val 表示REAL类型数据。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_PutReal(OH_Data_Values *values, double val);

/**
 * @brief 添加字符串类型数据给OH_Data_Values对象。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param val 表示字符串类型数据。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_PutText(OH_Data_Values *values, const char *val);

/**
 * @brief 添加BLOB类型数据给OH_Data_Values对象。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param val 表示BLOB类型数据。
 * @param length 该参数为输入参数，表示开发者传入的BLOB类型数据的大小。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_PutBlob(OH_Data_Values *values, const unsigned char *val, size_t length);

/**
 * @brief 添加ASSET类型数据给OH_Data_Values对象。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param val 表示指向{@link Data_Asset}对象的指针。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_PutAsset(OH_Data_Values *values, const Data_Asset *val);

/**
 * @brief 添加ASSETS类型数据给OH_Data_Values对象。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param val 表示指向{@link Data_Asset}对象的指针。
 * @param length 该参数为输入参数，表示开发者传入的{@link Data_Asset}对象数组元素的个数。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_PutAssets(OH_Data_Values *values, const Data_Asset * const * val, size_t length);

/**
 * @brief 添加float数组类型数据给OH_Data_Values对象。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param val 表示指向float数组对象的指针。
 * @param length 该参数为输入参数，表示开发者传入的float数组的长度。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_PutFloatVector(OH_Data_Values *values, const float *val, size_t length);

/**
 * @brief 添加任意长度的整型数组数据给OH_Data_Values对象。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param sign 表示正负数，0表示正整数，1表示负整数。
 * @param trueForm 表示指向整型数组的指针。
 * @param length 该参数为输入参数，表示开发者传入的整型数组的大小。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_PutUnlimitedInt(OH_Data_Values *values, int sign, const uint64_t *trueForm, size_t length);

/**
 * @brief 获取数据个数。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param count 一个输出参数，表示values中数据的个数。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_Count(OH_Data_Values *values, size_t *count);

/**
 * @brief 获取数据类型。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param type 一个输出参数，表示数据类型。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_GetType(OH_Data_Values *values, int index, OH_ColumnType *type);

/**
 * @brief 获取OH_Data_Value类型数据。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param val 一个输出参数，表示指向{@link OH_Data_Value}实例的指针。
 *     <br>无需申请内存和释放内存。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_Get(OH_Data_Values *values, int index, OH_Data_Value **val);

/**
 * @brief 检查数据是否为空。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param val 一个输出参数，true表示空，false表示不为空。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_Values_IsNull(OH_Data_Values *values, int index, bool *val);

/**
 * @brief 获取整型数据。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param val 一个输出参数，表示指向整型数据的指针。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_DATA_TYPE_NULL表示存储数据为空。
 *     <br>返回RDB_E_TYPE_MISMATCH表示数据类型不匹配。
 * @since 18
 */
int OH_Values_GetInt(OH_Data_Values *values, int index, int64_t *val);

/**
 * @brief 获取REAL类型数据。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param val 一个输出参数，表示指向REAL类型数据的指针。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_DATA_TYPE_NULL表示存储数据为空。
 *     <br>返回RDB_E_TYPE_MISMATCH表示数据类型不匹配。
 * @since 18
 */
int OH_Values_GetReal(OH_Data_Values *values, int index, double *val);

/**
 * @brief 获取字符串类型数据。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param val 一个输出参数，表示指向字符串类型数据的指针。
 *     <br>无需申请内存和释放内存。
 *     <br>val的生命周期遵循values中index的值。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_DATA_TYPE_NULL表示存储数据为空。
 *     <br>返回RDB_E_TYPE_MISMATCH表示数据类型不匹配。
 * @since 18
 */
int OH_Values_GetText(OH_Data_Values *values, int index, const char **val);

/**
 * @brief 获取BLOB类型数据。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param val 一个输出参数，表示指向BLOB类型数据的指针。
 *     <br>无需申请内存和释放内存。
 *     <br>val的生命周期遵循values中index的值。
 * @param length 该参数为输出参数，表示BLOB类型数组的大小。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_DATA_TYPE_NULL表示存储数据为空。
 *     <br>返回RDB_E_TYPE_MISMATCH表示数据类型不匹配。
 * @since 18
 */
int OH_Values_GetBlob(OH_Data_Values *values, int index, const uint8_t **val, size_t *length);

/**
 * @brief 获取ASSET类型数据。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param val 表示指向{@link Data_Asset}对象的指针。
 *     <br>需要申请数据内存。
 *     <br>此函数仅填充数据，否则执行失败。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_DATA_TYPE_NULL表示存储数据为空。
 *     <br>返回RDB_E_TYPE_MISMATCH表示数据类型不匹配。
 * @since 18
 */
int OH_Values_GetAsset(OH_Data_Values *values, int index, Data_Asset *val);

/**
 * @brief 获取ASSETS类型数据的大小。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param length 该参数为输出参数，表示ASSETS类型数据的大小。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_DATA_TYPE_NULL表示存储数据为空。
 *     <br>返回RDB_E_TYPE_MISMATCH表示数据类型不匹配。
 * @since 18
 */
int OH_Values_GetAssetsCount(OH_Data_Values *values, int index, size_t *length);

/**
 * @brief 获取ASSETS类型数据。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param val 表示指向{@link Data_Asset}对象的指针。
 *     <br>使用时需要申请数据内存。
 *     <br>此函数仅填充数据，否则执行失败。
 * @param inLen 表示val的大小。可以通过{@link OH_Values_GetAssetsCount}获取。
 * @param outLen 一个输出参数，表示实际获取的数据大小。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_DATA_TYPE_NULL表示存储数据为空。
 *     <br>返回RDB_E_TYPE_MISMATCH表示数据类型不匹配。
 * @see OH_Values_GetAssetsCount.
 * @since 18
 */
int OH_Values_GetAssets(OH_Data_Values *values, int index, Data_Asset **val, size_t inLen, size_t *outLen);

/**
 * @brief 获取float数组类型数据的大小。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param length 该参数为输出参数，表示float数组类型数据的大小。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_DATA_TYPE_NULL表示存储数据为空。
 *     <br>返回RDB_E_TYPE_MISMATCH表示数据类型不匹配。
 * @since 18
 */
int OH_Values_GetFloatVectorCount(OH_Data_Values *values, int index, size_t *length);

/**
 * @brief 获取float数组类型数据。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param val 表示指向float数组的指针。
 *     <br>需要申请数据内存。
 *     <br>此函数仅填充数据，否则执行失败。
 * @param inLen 表示val的大小。可以通过{@link OH_Values_GetFloatVectorCount}获取。
 * @param outLen 一个输出参数，表示实际获取的数据大小。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_DATA_TYPE_NULL表示存储数据为空。
 *     <br>返回RDB_E_TYPE_MISMATCH表示数据类型不匹配。
 * @see OH_Values_GetFloatVectorCount.
 * @since 18
 */
int OH_Values_GetFloatVector(OH_Data_Values *values, int index, float *val, size_t inLen, size_t *outLen);

/**
 * @brief 获取任意长度的整型数据的大小。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param length 该参数为输出参数，表示整型数组的大小。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_DATA_TYPE_NULL表示存储数据为空。
 *     <br>返回RDB_E_TYPE_MISMATCH表示数据类型不匹配。
 * @since 18
 */
int OH_Values_GetUnlimitedIntBand(OH_Data_Values *values, int index, size_t *length);

/**
 * @brief 获取任意长度的整型数据。
 *
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @param index 表示values中目标数据的从零开始的索引。
 * @param sign 一个输出参数，表示正负数，0表示正整数，1表示负整数。
 * @param trueForm 表示指向整型数组的指针。
 *     <br>需要申请数据内存。
 *     <br>此函数仅填充数据，否则执行失败。
 * @param inLen 表示trueForm的大小。可以通过{@link OH_Values_GetUnlimitedIntBand}获取。
 * @param outLen 一个输出参数，表示实际获取的数据大小。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_DATA_TYPE_NULL表示存储数据为空。
 *     <br>返回RDB_E_TYPE_MISMATCH表示数据类型不匹配。
 * @see OH_Values_GetUnlimitedIntBand.
 * @since 18
 */
int OH_Values_GetUnlimitedInt(OH_Data_Values *values, int index, int *sign, uint64_t *trueForm, size_t inLen,
    size_t *outLen);

#ifdef __cplusplus
};
#endif
#endif
/** @} */
