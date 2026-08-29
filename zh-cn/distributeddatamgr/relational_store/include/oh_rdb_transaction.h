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
 * @file oh_rdb_transaction.h
 *
 * @include database/rdb/oh_rdb_transaction.h
 * @brief 提供与数据库事务相关的函数和枚举。
 *
 * @kit ArkData
 * @library libnative_rdb_ndk.z.so
 * @syscap SystemCapability.DistributedDataManager.RelationalStore.Core
 *
 * @since 18
 */

#ifndef OH_RDB_TRANSACTION_ZH_CN_H
#define OH_RDB_TRANSACTION_ZH_CN_H

#include "database/rdb/oh_cursor.h"
#include "database/rdb/oh_predicates.h"
#include "database/rdb/oh_values_bucket.h"
#include "database/data/oh_data_values.h"
#include "database/data/oh_data_values_buckets.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 表示关系型数据库事务类型。
 *
 * @since 18
 */
typedef enum OH_RDB_TransType {
    /**
     * @brief 在首次访问数据库之前，事务默认设置不会启动。
     *
     */
    RDB_TRANS_DEFERRED = 0,
    /**
     * @brief 数据库连接立即开始新的写入，而无需等待写入语句。
     *
     */
    RDB_TRANS_IMMEDIATE,
    /**
     * @brief 与RDB_TRANS_IMMEDIATE类型相似，写事务会立即启动。
     * <br>RDB_TRANS_EXCLUSIVE和RDB_TRANS_IMMEDIATE类型在WAL模式下相同，但在其他日志模式下，RDB_TRANS_EXCLUSIVE会阻止其他数据库连接在事务进行时读取数据库。
     *
     */
    RDB_TRANS_EXCLUSIVE,
    /**
     * RDB事务类型的最大值。
     */
    RDB_TRANS_BUTT,
} OH_RDB_TransType;

/**
 * @brief 定义OH_RDB_TransOptions结构体类型。
 *
 * @since 18
 */
typedef struct OH_RDB_TransOptions OH_RDB_TransOptions;

/**
 * @brief 定义OH_Rdb_Transaction结构体类型。
 *
 * @since 18
 */
typedef struct OH_Rdb_Transaction OH_Rdb_Transaction;

/**
 * @brief 创建事务配置对象。
 *
 * @return 执行成功时返回指向{@link OH_RDB_TransOptions}实例的指针。否则返回nullptr。
 *     <br>使用完成后，必须通过{@link OH_RdbTrans_DestroyOptions}接口释放内存。
 * @see OH_RdbTrans_DestroyOptions.
 * @since 18
 */
OH_RDB_TransOptions *OH_RdbTrans_CreateOptions(void);

/**
 * @brief 销毁事务配置对象。
 *
 * @param options 指向{@link OH_RDB_TransOptions}实例的指针。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_RdbTrans_DestroyOptions(OH_RDB_TransOptions *options);

/**
 * @brief 设置关系型数据库事务类型。
 *
 * @param options 指向{@link OH_RDB_TransOptions}实例的指针。
 * @param type 表示关系型数据库事务类型。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_RdbTransOption_SetType(OH_RDB_TransOptions *options, OH_RDB_TransType type);

/**
 * @brief 提交事务。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已经关闭。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误码：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误码：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误码：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误码：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误码：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误码：磁盘I/O错误。
 * @since 18
 */
int OH_RdbTrans_Commit(OH_Rdb_Transaction *trans);

/**
 * @brief 回滚事务。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已经关闭。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误码：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误码：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误码：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误码：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误码：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误码：磁盘I/O错误。
 * @since 18
 */
int OH_RdbTrans_Rollback(OH_Rdb_Transaction *trans);

/**
 * @brief 将一行数据插入到目标表中。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param table 要插入的目标表名。
 * @param row 要插入到表中的数据行。
 * @param rowId 输出参数，表示插入后返回的行号。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已经关闭。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL日志文件大小超过默认值。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误码：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误码：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误码：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误码：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误码：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误码：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误码：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误码：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误码：数据类型不匹配。
 * @since 18
 */
int OH_RdbTrans_Insert(OH_Rdb_Transaction *trans, const char *table, const OH_VBucket *row, int64_t *rowId);

/**
 * @brief 将一行数据插入到目标表中，支持冲突解决。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param table 要插入的目标表名。
 * @param row 表示要插入到表中的数据。
 * @param resolution 表示发生冲突时的解决策略。
 * @param rowId 输出参数，表示插入成功后返回的行号。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示输入参数无效。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已关闭。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL日志文件大小超过默认值。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误码：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误码：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误码：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误码：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误码：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误码：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误码：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误码：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误码：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误码：违反约束导致操作中止。
 * @since 20
 */
int OH_RdbTrans_InsertWithConflictResolution(OH_Rdb_Transaction *trans, const char *table, const OH_VBucket *row,
    Rdb_ConflictResolution resolution, int64_t *rowId);

/**
 * @brief 将一组数据批量插入到目标表中。
 * <br>单次插入参数的最大数量限制为32766，超出上限会返回RDB_E_INVALID_ARGS错误码。参数数量计算方式为插入数据条数乘以插入数据的所有字段的并集大小。
 * <br>例如：插入数据的所有字段的并集大小为10，则最多可以插入3276条数据（3276*10=32760）。
 * <br>请确保在调用接口时遵守此限制，以避免因参数数量过多而导致错误。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param table 要插入的目标表名。
 * @param rows 表示要插入到表中的一组数据。
 * @param changes 输出参数，表示插入成功的次数。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已经关闭。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL日志文件大小超过默认值。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误码：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误码：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误码：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误码：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误码：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误码：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误码：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误码：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误码：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误码：SQLite约束。
 * @since 18
 */
int OH_RdbTrans_BatchInsert(OH_Rdb_Transaction *trans, const char *table, const OH_Data_VBuckets *rows,
    int64_t *changes);

/**
 * @brief 根据指定的条件更新数据库中的数据。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param row 表示要更新到表中的数据行。
 * @param predicates 表示{@link OH_Predicates}指定的更新条件。
 * @param changes 输出参数，表示更新成功的行数。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已经关闭。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL日志文件大小超过默认值。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误码：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误码：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误码：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误码：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误码：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误码：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误码：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误码：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误码：数据类型不匹配。
 * @since 18
 */
int OH_RdbTrans_Update(OH_Rdb_Transaction *trans, const OH_VBucket *row, const OH_Predicates *predicates,
    int64_t *changes);

/**
 * @brief 根据指定条件更新数据库中的数据，并支持冲突解决。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param row 表示要更新到表中的数据。
 * @param predicates 表示{@link OH_Predicates}指定的更新条件。
 * @param resolution 表示发生冲突时的解决策略。
 * @param changes 输出参数，表示更新成功的行数。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示输入参数无效。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已关闭。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL日志文件大小超过默认值。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误码：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误码：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误码：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误码：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误码：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误码：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误码：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误码：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误码：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误码：违反约束导致操作中止。
 * @since 20
 */
int OH_RdbTrans_UpdateWithConflictResolution(OH_Rdb_Transaction *trans, const OH_VBucket *row,
    const OH_Predicates *predicates, Rdb_ConflictResolution resolution, int64_t *changes);

/**
 * @brief 根据指定条件从数据库中删除数据。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param predicates 表示{@link OH_Predicates}指定的删除条件。
 * @param changes 输出参数，表示删除成功的次数。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已经关闭。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL日志文件大小超过默认值。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误码：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误码：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误码：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误码：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误码：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误码：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误码：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误码：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误码：数据类型不匹配。
 * @since 18
 */
int OH_RdbTrans_Delete(OH_Rdb_Transaction *trans, const OH_Predicates *predicates, int64_t *changes);

/**
 * @brief 根据指定的条件查询数据库中的数据。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param predicates 表示{@link OH_Predicates}指定的查询条件。
 * @param columns 表示要查询的列。如果值为空数组，则查询适用于所有列。
 * @param len 传入的columns数组的长度。若len大于columns数组的实际长度，则会访问越界。
 * @return 如果执行成功，则返回指向{@link OH_Cursor}实例的指针。如果数据库已关闭或数据库没有响应，则返回空。
 * @since 18
 */
OH_Cursor *OH_RdbTrans_Query(OH_Rdb_Transaction *trans, const OH_Predicates *predicates, const char *columns[],
    int len);

/**
 * @brief 根据指定的条件查询数据库中的数据，不计算行数。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param predicates {@link OH_Predicates}指定的查询条件。
 * @param columns 要查询的列，如果传入空值，则查询所有列。
 * @param len 传入的columns数组的长度。若len大于columns数组的实际长度，则会访问越界。
 * @return 如果执行成功，则返回指向{@link OH_Cursor}实例的指针。如果数据库已关闭或数据库没有响应，则返回nullptr。
 * @since 23
 */
OH_Cursor *OH_RdbTrans_QueryWithoutRowCount(OH_Rdb_Transaction *trans, const OH_Predicates *predicates,
    const char *const columns[], int len);

/**
 * @brief 根据SQL语句查询数据库中的数据。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param sql 表示要执行的SQL语句。
 * @param args 指向{@link OH_Data_Values}的指针。
 * @return 如果执行成功，则返回指向{@link OH_Cursor}实例的指针。如果数据库已关闭或数据库没有响应，则返回空。
 * @since 18
 */
OH_Cursor *OH_RdbTrans_QuerySql(OH_Rdb_Transaction *trans, const char *sql, const OH_Data_Values *args);

/**
 * @brief 根据SQL语句查询数据库中的数据，不计算行数。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param sql 要执行的SQL语句。
 * @param args 指向{@link OH_Data_Values}的指针。
 * @return 如果执行成功，则返回指向{@link OH_Cursor}实例的指针。如果数据库已关闭或数据库没有响应，则返回nullptr。
 * @since 23
 */
OH_Cursor *OH_RdbTrans_QuerySqlWithoutRowCount(OH_Rdb_Transaction *trans, const char *sql, const OH_Data_Values *args);

/**
 * @brief 执行包含指定参数的SQL语句。
 * <br>不支持开头包含注释的语句。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param sql 表示要执行的SQL语句。
 * @param args SQL语句中包含的参数。
 * @param result 执行成功时指向{@link OH_Data_Value}实例的指针。使用完成后，必须通过{@link OH_Value_Destroy}接口释放内存。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已经关闭。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL日志文件大小超过默认值。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误码：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误码：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误码：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误码：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误码：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误码：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误码：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误码：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误码：数据类型不匹配。
 * @see OH_Value_Destroy.
 * @since 18
 */
int OH_RdbTrans_Execute(OH_Rdb_Transaction *trans, const char *sql, const OH_Data_Values *args, OH_Data_Value **result);

/**
 * @brief 销毁事务对象。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @return 返回错误码。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 * @since 18
 */
int OH_RdbTrans_Destroy(OH_Rdb_Transaction *trans);
/**
 * @brief 将一组数据批量插入到目标表中。
 * <br>单次插入参数的最大数量限制为32766，超出上限会返回RDB_E_INVALID_ARGS错误码。参数数量计算方式为插入数据条数乘以插入数据的所有字段的并集大小。
 * <br>例如：插入数据的所有字段的并集大小为10，则最多可以插入3276条数据（3276*10=32760）。
 * <br>请确保在调用接口时遵守此限制，以避免因参数数量过多而导致错误。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param table 要插入的目标表名。
 * @param rows 表示要插入到表中的一组数据。
 * @param resolution 表示发生冲突时的解决策略。
 * @param changes 输出参数，表示插入成功的次数。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已经关闭。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL日志文件大小超过默认值。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误码：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误码：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误码：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误码：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误码：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误码：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误码：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误码：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误码：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误码：SQLite约束。
 * @since 18
 */
int OH_RdbTrans_BatchInsert(OH_Rdb_Transaction *trans, const char *table, const OH_Data_VBuckets *rows,
    Rdb_ConflictResolution resolution, int64_t *changes);

/**
 * @brief 将批量数据插入目标表，并将变更信息输出到上下文中。
 * <br>一次最多可以插入32766个参数。如果参数数量超过上限，则返回错误代码RDB_E_INVALID_ARGS。
 * <br>参数数量计算方式为插入数据条数乘以插入数据时所有字段的并集大小。
 * <br>例如：插入数据的所有字段的并集大小为10则最多可以插入3276条数据（3276*10=32760）。
 * <br>请确保在调用接口时遵守此限制，以避免因参数数量过多而导致错误。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param table 要插入的目标表名。
 * @param rows 要插入到表中的行数据。
 * @param resolution 发生冲突时的解决策略{@link Rdb_ConflictResolution}，不建议使用RDB_CONFLICT_FAIL，因为失败时会抛异常，
 *     <br>无法正常获取实际的变更数据。
 * @param context 指向{@link OH_RDB_ReturningContext}实例的指针。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示执行成功。
 *     <br>返回RDB_E_INVALID_ARGS表示输入参数无效。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL文件大小超过默认限制。
 *     <br>返回RDB_E_NOT_SUPPORTED表示不支持的操作。
 *     <br>返回RDB_E_DATABASE_BUSY表示数据库忙。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已关闭。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误：发生某种磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误：由于违反约束而中止。
 *     <br>返回RDB_E_SQLITE_ERROR表示SQLite错误。可能原因：语法错误，例如表或列不存在。
 *     <br>具体错误码可参考{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Transaction, OH_Data_VBuckets, OH_Rdb_ErrCode, OH_RDB_ReturningContext.
 * @since 23
 */
int OH_RdbTrans_BatchInsertWithReturning(OH_Rdb_Transaction *trans, const char *table, const OH_Data_VBuckets *rows,
    Rdb_ConflictResolution resolution, OH_RDB_ReturningContext *context);

/**
 * @brief 根据指定条件更新数据库中的数据并输出更改信息到上下文。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param row 要更新到表中的行数据。
 * @param predicates 指向{@link OH_Predicates}实例的指针。
 * @param resolution 发生冲突时的解决策略{@link Rdb_ConflictResolution}，不建议使用RDB_CONFLICT_FAIL，因为失败时会抛异常，
 *     <br>无法正常获取实际的变更数据。
 * @param context 指向{@link OH_RDB_ReturningContext}实例的指针。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示执行成功。
 *     <br>返回RDB_E_INVALID_ARGS表示输入参数无效。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL文件大小超过默认限制。
 *     <br>返回RDB_E_NOT_SUPPORTED表示不支持的操作。
 *     <br>返回RDB_E_EMPTY_VALUES_BUCKET表示值桶为空。
 *     <br>返回RDB_E_DATABASE_BUSY表示数据库忙。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已关闭。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误：发生某种磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误：由于违反约束而中止。
 *     <br>返回RDB_E_SQLITE_ERROR表示SQLite错误。可能原因：语法错误，例如表或列不存在。
 *     <br>具体错误码可参考{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Transaction, OH_Data_VBuckets, OH_Predicates, OH_Rdb_ErrCode, OH_RDB_ReturningContext.
 * @since 23
 */
int OH_RdbTrans_UpdateWithReturning(OH_Rdb_Transaction *trans, OH_VBucket *row, OH_Predicates *predicates,
    Rdb_ConflictResolution resolution, OH_RDB_ReturningContext *context);

/**
 * @brief 根据指定条件从数据库中删除数据并输出更改信息到上下文。
 *
 * @param trans 指向{@link OH_Rdb_Transaction}实例的指针。
 * @param predicates 指向{@link OH_Predicates}实例的指针。
 * @param context 指向{@link OH_RDB_ReturningContext}实例的指针。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示执行成功。
 *     <br>返回RDB_E_INVALID_ARGS表示输入参数无效。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL文件大小超过默认限制。
 *     <br>返回RDB_E_NOT_SUPPORTED表示不支持的操作。
 *     <br>返回RDB_E_DATABASE_BUSY表示数据库忙。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已关闭。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误：发生某种磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_ERROR表示SQLite错误。可能原因：语法错误，例如表或列不存在。
 *     <br>具体错误码可参考{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Transaction, OH_Predicates, OH_Rdb_ErrCode, OH_RDB_ReturningContext.
 * @since 23
 */
int OH_RdbTrans_DeleteWithReturning(
    OH_Rdb_Transaction *trans, OH_Predicates *predicates, OH_RDB_ReturningContext *context);

#ifdef __cplusplus
};
#endif
#endif // OH_RDB_TRANSACTION_ZH_CN_H
/** @} */
