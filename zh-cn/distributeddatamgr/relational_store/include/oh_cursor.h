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
 * @file oh_cursor.h
 *
 * @include database/rdb/oh_cursor.h
 * @brief 提供通过查询数据库生成的数据库结果集的访问方法。结果集是指用户调用关系型数据库查询接口之后返回的结果集合，提供了多种灵活的数据访问方式，以便用户获取各项数据。
 *
 * @kit ArkData
 * @library libnative_rdb_ndk.z.so
 * @syscap SystemCapability.DistributedDataManager.RelationalStore.Core
 * @since 10
 */

#ifndef OH_CURSOR_ZH_CN_H
#define OH_CURSOR_ZH_CN_H

#include <stdint.h>

#include <stddef.h>
#include <stdbool.h>
#include "database/data/data_asset.h"
#include "database/data/oh_data_value.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 表示结果集。提供通过查询数据库生成的数据库结果集的访问方法。
 *
 * @since 10
 */
typedef struct OH_Cursor OH_Cursor;

/**
 * @brief 表示结果集。提供通过查询数据库生成的数据库结果集的访问方法。
 *
 * @since 10
 */
typedef struct OH_Cursor {
    /**
     * OH_Cursor结构体的唯一标识符。
     */
    int64_t id;
    /**
     * @brief 函数指针，获取结果集中的列数。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param count 该参数是输出参数，列数写入此变量。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 10
     */
    int (*getColumnCount)(OH_Cursor *cursor, int *count);

    /**
     * @brief 函数指针，根据指定的列索引获取列类型。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param columnIndex 表示结果集中指定列的索引，索引值从0开始。
     * @param columnType 该参数是输出参数，列值类型写入此变量。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor, OH_ColumnType.
     * @since 10
     */
    int (*getColumnType)(OH_Cursor *cursor, int32_t columnIndex, OH_ColumnType *columnType);

    /**
     * @brief 函数指针，根据指定的列名获取列索引。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param name 表示列名。
     * @param columnIndex 该参数是输出参数，给定列的索引写入此变量。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 10
     */
    int (*getColumnIndex)(OH_Cursor *cursor, const char *name, int *columnIndex);

    /**
     * @brief 函数指针，根据指定的列索引获取列名。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param columnIndex 表示结果集中指定列的索引，索引值从0开始。
     * @param name 该参数是输出参数，给定索引的列名写入此变量。
     * @param length 该参数为输入参数，表示开发者传入的包括终止符在内的列名字符串的总长度。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 10
     */
    int (*getColumnName)(OH_Cursor *cursor, int32_t columnIndex, char *name, int length);

    /**
     * @brief 函数指针，获取结果集中的行数。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param count 该参数是输出参数，结果集中的行数写入此变量。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 10
     */
    int (*getRowCount)(OH_Cursor *cursor, int *count);

    /**
     * @brief 函数指针，转到结果集的下一行。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 10
     */
    int (*goToNextRow)(OH_Cursor *cursor);

    /**
     * @brief 函数指针，当结果集中列的数据类型是BLOB或者TEXT时，获取其值所需的内存。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param columnIndex 表示结果集中指定列的索引，索引值从0开始。
     * @param size 该参数是输出参数，请求列的值大小写入此变量。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 10
     */
    int (*getSize)(OH_Cursor *cursor, int32_t columnIndex, size_t *size);

    /**
     * @brief 函数指针，以字符串形式获取当前行中指定列的值。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param columnIndex 表示结果集中指定列的索引，索引值从0开始。
     * @param value 该参数是输出参数，请求列的值以char *形式写入此变量。
     * @param length 该参数是输入参数，表示value的长度，该值可通过getSize获取。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 10
     */
    int (*getText)(OH_Cursor *cursor, int32_t columnIndex, char *value, int length);

    /**
     * @brief 函数指针，以int64_t形式获取当前行中指定列的值。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param columnIndex 表示结果集中指定列的索引，索引值从0开始。
     * @param value 该参数是输出参数，请求列的值以int64_t形式写入此变量。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 10
     */
    int (*getInt64)(OH_Cursor *cursor, int32_t columnIndex, int64_t *value);

    /**
     * @brief 函数指针，以double形式获取当前行中指定列的值。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param columnIndex 表示结果集中指定列的索引，索引值从0开始。
     * @param value 该参数是输出参数，请求列的值以double形式写入此变量。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 10
     */
    int (*getReal)(OH_Cursor *cursor, int32_t columnIndex, double *value);

    /**
     * @brief 函数指针，以字节数组的形式获取当前行中指定列的值。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param columnIndex 表示结果集中指定列的索引，索引值从0开始。
     * @param value 该参数是输出参数，请求列的值以字节数组形式写入此变量。
     * @param length 该参数为输入参数，表示传入的value的长度，该值可通过getSize获取。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 10
     */
    int (*getBlob)(OH_Cursor *cursor, int32_t columnIndex, unsigned char *value, int length);

    /**
     * @brief 函数指针，检查当前行中指定列的值是否为null。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param columnIndex 表示结果集中指定列的索引，索引值从0开始。
     * @param isNull 该参数是输出参数，列值是否为null写入此变量。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 10
     */
    int (*isNull)(OH_Cursor *cursor, int32_t columnIndex, bool *isNull);

    /**
     * @brief 函数指针，关闭结果集。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 10
     */
    int (*destroy)(OH_Cursor *cursor);

    /**
     * @brief 函数指针，以资产的形式获取当前行中指定列的值。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param columnIndex 表示结果集中指定列的索引，索引值从0开始。
     * @param value 该参数是输出参数，请求列的值以{@link Data_Asset}实例写入此变量。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 11
     */
    int (*getAsset)(OH_Cursor *cursor, int32_t columnIndex, Data_Asset *value);

    /**
     * @brief 函数指针，以资产数组的形式获取当前行中指定列的值。
     *
     * @param cursor 表示指向{@link OH_Cursor}实例的指针。
     * @param columnIndex 表示结果集中指定列的索引，索引值从0开始。
     * @param value 该参数是输出参数，请求列的值以{@link Data_Asset}实例写入此变量。
     * @param length 既是入参又是出参：作为入参，需要开发者传入一个uint32_t类型的变量，表示输入缓冲区的大小；
     * <br>作为出参，表示函数执行后，length指向的变量会被更新为实际返回的资产数组的长度。
     * @return 返回操作是否成功，出错时返回对应的错误码。
     * @see OH_Cursor.
     * @since 11
     */
    int (*getAssets)(OH_Cursor *cursor, int32_t columnIndex, Data_Asset **value, uint32_t *length);
};

/**
 * @brief 获取当前行中指定列的浮点数数组大小。
 *
 * @param cursor 表示指向{@link OH_Cursor}实例的指针。
 * @param columnIndex 表示结果集中指定列的索引，索引值从0开始。
 * @param length 该参数是输出参数，结果集中指定列的浮点数数组大小会写入该变量。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_STEP_RESULT_CLOSED表示查询到的结果集已经关闭。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已经关闭。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误码：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误码：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误码：数据类型不匹配。
 * @since 18
 */
int OH_Cursor_GetFloatVectorCount(OH_Cursor *cursor, int32_t columnIndex, size_t *length);

/**
 * @brief 以浮点数数组的形式获取当前行中指定列的值。
 *
 * @param cursor 表示指向{@link OH_Cursor}实例的指针。
 * @param columnIndex 表示结果集中指定列的索引，索引值从0开始。
 * @param val 该参数是输出参数，结果集中指定列的值会以浮点数数组形式写入该变量，调用者需要申请数组内存。
 * @param inLen 表示申请的浮点数数组大小。
 * @param outLen 该参数是输出参数，表示实际浮点数数组的大小。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_STEP_RESULT_CLOSED表示查询到的结果集已经关闭。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已经关闭。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误码：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误: 磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误码：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误码：数据类型不匹配。
 * @see OH_Cursor_GetFloatVectorCount.
 * @since 18
 */
int OH_Cursor_GetFloatVector(OH_Cursor *cursor, int32_t columnIndex, float *val, size_t inLen, size_t *outLen);

#ifdef __cplusplus
};
#endif

/** @} */

#endif // OH_CURSOR_ZH_CN_H
