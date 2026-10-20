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
 * @since 11
 */

/**
 * @file data_asset.h
 *
 * @include database/data/data_asset.h
 * @brief 提供资产类型数据结构。
 * <br>资产是指一种可以在数据管理中使用的数据结构，可以存储及查询一个文件的名称、绝对路径、相对路径、创建时间、修改时间、状态、占用空间等属性。
 *
 * @kit ArkData
 * @library libnative_rdb_ndk.z.so
 * @syscap SystemCapability.DistributedDataManager.RelationalStore.Core
 * @since 11
 */

#ifndef DATA_ASSET_ZH_CN_H
#define DATA_ASSET_ZH_CN_H

#include <stddef.h>

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 资产状态值类型。
 *
 * @since 11
 */
typedef enum Data_AssetStatus {
    /**
     * @brief 表示资产为空。
     *
     */
    ASSET_NULL = 0,

    /**
     * @brief 表示资产状态正常。
     *
     */
    ASSET_NORMAL,

    /**
     * @brief 表示资产需要插入到云端。
     *
     */
    ASSET_INSERT,

    /**
     * @brief 表示资产需要更新到云端。
     *
     */
    ASSET_UPDATE,

    /**
     * @brief 表示资产需要在云端删除。
     *
     */
    ASSET_DELETE,

    /**
     * @brief 表示资产状态异常。
     *
     */
    ASSET_ABNORMAL,

    /**
     * @brief 表示资产正在下载到本地设备。
     *
     */
    ASSET_DOWNLOADING
} Data_AssetStatus;

/**
 * @brief 表示资产附件类型的数据。<br>提供资产附件的信息。
 *
 * @since 11
 */
typedef struct Data_Asset Data_Asset;

/**
 * @brief 设置资产类型数据的名称。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param name 表示要设置的名称。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset
 * @since 11
 */
int OH_Data_Asset_SetName(Data_Asset *asset, const char *name);

/**
 * @brief 设置资产类型数据在系统里的绝对路径，即URI。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param uri 表示要设置的URI。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset
 * @since 11
 */
int OH_Data_Asset_SetUri(Data_Asset *asset, const char *uri);

/**
 * @brief 设置资产类型数据在应用沙箱里的相对路径。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param path 表示要设置的相对路径。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset
 * @since 11
 */
int OH_Data_Asset_SetPath(Data_Asset *asset, const char *path);

/**
 * @brief 设置资产类型数据创建的时间。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param createTime 表示要设置的创建时间。无特定单位。开发者可自行指定。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset
 * @since 11
 */
int OH_Data_Asset_SetCreateTime(Data_Asset *asset, int64_t createTime);

/**
 * @brief 设置资产类型数据最后修改的时间。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param modifyTime 表示要设置的最后修改的时间。无特定单位。开发者可自行指定。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset
 * @since 11
 */
int OH_Data_Asset_SetModifyTime(Data_Asset *asset, int64_t modifyTime);

/**
 * @brief 设置资产类型数据占用空间的大小。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param size 表示要设置的占用空间的大小（单位为字节（Byte），取值为非负整数）。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset
 * @since 11
 */
int OH_Data_Asset_SetSize(Data_Asset *asset, size_t size);

/**
 * @brief 设置资产类型数据的状态码。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param status 表示需要设置的状态码。详细信息可以查看{@link Data_AssetStatus}。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset, Data_AssetStatus
 * @since 11
 */
int OH_Data_Asset_SetStatus(Data_Asset *asset, Data_AssetStatus status);

/**
 * @brief 获取资产类型数据的名称。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param name 该参数是输出参数，资产类型数据的名称会以字符串形式写入该变量。
 * @param length 表示name的长度。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_ERR表示函数执行异常。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset
 * @since 11
 */
int OH_Data_Asset_GetName(Data_Asset *asset, char *name, size_t *length);

/**
 * @brief 获取资产类型数据的绝对路径。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param uri 参数是输出参数，资产类型数据的绝对路径会以字符串形式写入该变量。
 * @param length 表示uri的长度。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_ERR表示函数执行异常。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset
 * @since 11
 */
int OH_Data_Asset_GetUri(Data_Asset *asset, char *uri, size_t *length);

/**
 * @brief 获取资产类型数据的相对路径。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param path 参数是输出参数，资产类型数据的相对路径会以字符串形式写入该变量。
 * @param length 表示path的长度。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_ERR表示函数执行异常。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset
 * @since 11
 */
int OH_Data_Asset_GetPath(Data_Asset *asset, char *path, size_t *length);

/**
 * @brief 获取资产类型数据的创建时间。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param createTime 参数是输出参数，资产类型数据的创建时间会以int64_t形式写入该变量。无特定单位。开发者可自行指定。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_ERR表示函数执行异常。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset
 * @since 11
 */
int OH_Data_Asset_GetCreateTime(Data_Asset *asset, int64_t *createTime);

/**
 * @brief 获取资产类型数据的最后修改的时间。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param modifyTime 参数是输出参数，资产类型数据的最后修改时间会以int64_t形式写入该变量。无特定单位。开发者可自行指定。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_ERR表示函数执行异常。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset
 * @since 11
 */
int OH_Data_Asset_GetModifyTime(Data_Asset *asset, int64_t *modifyTime);

/**
 * @brief 获取资产类型数据占用空间的大小。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param size 参数是输出参数，资产类型数据的占用空间大小会以size_t形式写入该变量。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_ERR表示函数执行异常。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset
 * @since 11
 */
int OH_Data_Asset_GetSize(Data_Asset *asset, size_t *size);

/**
 * @brief 获取资产类型数据的状态码。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @param status 参数是输出参数，资产类型数据的状态码会以{@link Data_AssetStatus}形式写入该变量。
 * @return 返回特定的错误码值。详细信息可以查看{@link OH_Rdb_ErrCode}。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @see Data_Asset Data_AssetStatus.
 * @since 11
 */
int OH_Data_Asset_GetStatus(Data_Asset *asset, Data_AssetStatus *status);

/**
 * @brief 创建一个{@link Data_Asset}类型实例。
 *
 * @return 创建成功则返回一个指向{@link Data_Asset}结构体实例的指针，否则返回NULL。
 *     <br>使用完成后，必须通过{@link OH_Data_Asset_DestroyOne}接口释放内存。
 * @see Data_Asset.
 * @since 11
 */
Data_Asset *OH_Data_Asset_CreateOne(void);

/**
 * @brief 销毁{@link Data_Asset} 对象并回收该对象占用的内存。
 *
 * @param asset 表示指向{@link Data_Asset}实例的指针。
 * @return 返回操作是否成功，成功时返回RDB_OK，出错时返回对应的错误码。详细信息可以查看{@link OH_Rdb_ErrCode}。
 * @see Data_Asset, OH_Rdb_ErrCode.
 * @since 11
 */
int OH_Data_Asset_DestroyOne(Data_Asset *asset);

/**
 * @brief 创建指定数量的{@link Data_Asset}类型实例。
 *
 * @param count 表示要创建的{@link Data_Asset}类型实例的数量。
 * @return 创建成功则返回一个指向{@link Data_Asset}结构体指针数组的指针，否则返回NULL。
 *     <br>使用完成后，必须通过{@link OH_Data_Asset_DestroyMultiple}接口释放内存。
 * @see Data_Asset.
 * @since 11
 */
Data_Asset **OH_Data_Asset_CreateMultiple(uint32_t count);

/**
 * @brief 销毁多个{@link Data_Asset} 对象并回收该对象占用的内存。
 *
 * @param assets 表示指向{@link Data_Asset}结构体指针数组的指针。
 * @param count 代表需要销毁的{@link Data_Asset}类型对象的数量。
 * @return 返回操作是否成功，成功时返回RDB_OK，出错时返回对应的错误码。详细信息可以查看{@link OH_Rdb_ErrCode}。
 * @see Data_Asset, OH_Rdb_ErrCode.
 * @since 11
 */
int OH_Data_Asset_DestroyMultiple(Data_Asset **assets, uint32_t count);
#ifdef __cplusplus
};
#endif

/** @} */

#endif // DATA_ASSET_ZH_CN_H
