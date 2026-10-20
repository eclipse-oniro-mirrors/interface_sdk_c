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
 * @file relational_store_error_code.h
 *
 * @include database/rdb/relational_store_error_code.h
 * @brief 声明关系型数据库（RDB）的错误码信息。
 *
 * @kit ArkData
 * @library libnative_rdb_ndk.z.so
 * @syscap SystemCapability.DistributedDataManager.RelationalStore.Core
 * @since 10
 */

#ifndef RELATIONAL_STORE_ERRNO_CODE_ZH_CN_H
#define RELATIONAL_STORE_ERRNO_CODE_ZH_CN_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 表示错误码信息。
 *
 * @since 10
 */
typedef enum OH_Rdb_ErrCode {
    /**
     * 执行出错。
     */
    RDB_ERR = -1,

    /**
     * 执行成功。
     */
    RDB_OK = 0,

    /**
     * @brief 异常错误代码的基础。
     *
     */
    E_BASE = 14800000,

    /**
     * @brief RDB不具备该能力。
     *
     */
    RDB_E_NOT_SUPPORTED = 801,

    /**
     * @brief 常见异常的错误代码。
     *
     */
    RDB_E_ERROR = E_BASE,

    /**
     * @brief 参数非法。
     *
     */
    RDB_E_INVALID_ARGS = (E_BASE + 1),

    /**
     * @brief 无法更新只读数据库。
     *
     */
    RDB_E_CANNOT_UPDATE_READONLY = (E_BASE + 2),

    /**
     * @brief 删除文件失败。
     *
     */
    RDB_E_REMOVE_FILE = (E_BASE + 3),

    /**
     * @brief 表名为空。
     *
     */
    RDB_E_EMPTY_TABLE_NAME = (E_BASE + 5),

    /**
     * @brief 键值对内容为空。
     *
     */
    RDB_E_EMPTY_VALUES_BUCKET = (E_BASE + 6),

    /**
     * @brief 查询时执行的SQL语句错误。
     *
     */
    RDB_E_EXECUTE_IN_STEP_QUERY = (E_BASE + 7),

    /**
     * @brief 列索引非法。
     *
     */
    RDB_E_INVALID_COLUMN_INDEX = (E_BASE + 8),

    /**
     * @brief 列类型非法。
     *
     */
    RDB_E_INVALID_COLUMN_TYPE = (E_BASE + 9),

    /**
     * @brief 文件名称为空。
     *
     */
    RDB_E_EMPTY_FILE_NAME = (E_BASE + 10),

    /**
     * @brief 文件路径非法。
     *
     */
    RDB_E_INVALID_FILE_PATH = (E_BASE + 11),

    /**
     * @brief 开启事务执行出错。
     *
     */
    RDB_E_TRANSACTION_IN_EXECUTE = (E_BASE + 12),

    /**
     * @brief SQL语句预编译出错。
     *
     */
    RDB_E_INVALID_STATEMENT = (E_BASE + 13),

    /**
     * @brief 在读连接中执行写操作。
     *
     */
    RDB_E_EXECUTE_WRITE_IN_READ_CONNECTION = (E_BASE + 14),

    /**
     * @brief 在读连接中开启事务。
     *
     */
    RDB_E_BEGIN_TRANSACTION_IN_READ_CONNECTION = (E_BASE + 15),

    /**
     * @brief 在数据库会话中不存在开启的事务。
     *
     */
    RDB_E_NO_TRANSACTION_IN_SESSION = (E_BASE + 16),

    /**
     * @brief 在一个数据库会话中执行多次查询。
     *
     */
    RDB_E_MORE_STEP_QUERY_IN_ONE_SESSION = (E_BASE + 17),

    /**
     * @brief 查询得到的结果集不存在任何记录。
     *
     */
    RDB_E_NO_ROW_IN_QUERY = (E_BASE + 18),

    /**
     * @brief SQL语句中绑定的参数个数非法。
     *
     */
    RDB_E_INVALID_BIND_ARGS_COUNT = (E_BASE + 19),

    /**
     * @brief 对象类型非法。
     *
     */
    RDB_E_INVALID_OBJECT_TYPE = (E_BASE + 20),

    /**
     * @brief 冲突解决类型非法。
     *
     */
    RDB_E_INVALID_CONFLICT_FLAG = (E_BASE + 21),

    /**
     * @brief HAVING关键字只能用于GROUP BY之后。
     *
     */
    RDB_E_HAVING_CLAUSE_NOT_IN_GROUP_BY = (E_BASE + 22),

    /**
     * @brief 不支持step形式数据库结果集。
     *
     */
    RDB_E_NOT_SUPPORTED_BY_STEP_RESULT_SET = (E_BASE + 23),

    /**
     * @brief 跨线程使用结果集查询出错。
     *
     */
    RDB_E_STEP_RESULT_SET_CROSS_THREADS = (E_BASE + 24),

    /**
     * @brief 结果集查询语句未被执行。
     *
     */
    RDB_E_STEP_RESULT_QUERY_NOT_EXECUTED = (E_BASE + 25),

    /**
     * @brief 结果集的游标已经处于最后一行。
     *
     */
    RDB_E_STEP_RESULT_IS_AFTER_LAST = (E_BASE + 26),

    /**
     * @brief 结果集查询次数已经超过上限。
     *
     */
    RDB_E_STEP_RESULT_QUERY_EXCEEDED = (E_BASE + 27),

    /**
     * @brief SQL语句未被预编译。
     *
     */
    RDB_E_STATEMENT_NOT_PREPARED = (E_BASE + 28),

    /**
     * @brief 数据库执行结果异常。
     *
     */
    RDB_E_EXECUTE_RESULT_INCORRECT = (E_BASE + 29),

    /**
     * @brief 结果集已经关闭。
     *
     */
    RDB_E_STEP_RESULT_CLOSED = (E_BASE + 30),

    /**
     * @brief 相对路径。
     *
     */
    RDB_E_RELATIVE_PATH = (E_BASE + 31),

    /**
     * @brief 新的密钥文件为空。
     *
     */
    RDB_E_EMPTY_NEW_ENCRYPT_KEY = (E_BASE + 32),

    /**
     * @brief 将非加密的数据库更改为加密数据库。
     *
     */
    RDB_E_CHANGE_UNENCRYPTED_TO_ENCRYPTED = (E_BASE + 33),

    /**
     * @brief 在数据库繁忙时更新数据库密钥。
     *
     */
    RDB_E_CHANGE_ENCRYPT_KEY_IN_BUSY = (E_BASE + 34),

    /**
     * @brief 预编译的SQL语句未被初始化。
     *
     */
    RDB_E_STEP_STATEMENT_NOT_INIT = (E_BASE + 35),

    /**
     * @brief 在WAL日志模式下不支持ATTACH操作。
     *
     */
    RDB_E_NOT_SUPPORTED_ATTACH_IN_WAL_MODE = (E_BASE + 36),

    /**
     * @brief 创建文件夹失败。
     *
     */
    RDB_E_CREATE_FOLDER_FAIL = (E_BASE + 37),

    /**
     * @brief SQL语句构建失败。
     *
     */
    RDB_E_SQLITE_SQL_BUILDER_NORMALIZE_FAIL = (E_BASE + 38),

    /**
     * @brief 数据库会话暂未提供连接。
     *
     */
    RDB_E_STORE_SESSION_NOT_GIVE_CONNECTION_TEMPORARILY = (E_BASE + 39),

    /**
     * @brief 数据库会话不具有当前的事务。
     *
     */
    RDB_E_STORE_SESSION_NO_CURRENT_TRANSACTION = (E_BASE + 40),

    /**
     * @brief 不支持当前操作。
     *
     */
    RDB_E_NOT_SUPPORT = (E_BASE + 41),

    /**
     * @brief 当前PARCEL非法。
     *
     */
    RDB_E_INVALID_PARCEL = (E_BASE + 42),

    /**
     * @brief 执行query查询出错。
     *
     */
    RDB_E_QUERY_IN_EXECUTE = (E_BASE + 43),

    /**
     * @brief 设置WAL模式下数据库文件的持久化时出错。
     *
     */
    RDB_E_SET_PERSIST_WAL = (E_BASE + 44),

    /**
     * @brief 数据库不存在。
     *
     */
    RDB_E_DB_NOT_EXIST = (E_BASE + 45),

    /**
     * @brief 设置的读连接数大于上限。
     *
     */
    RDB_E_ARGS_READ_CON_OVERLOAD = (E_BASE + 46),

    /**
     * @brief WAL日志文件大小超过默认值。
     *
    */
    RDB_E_WAL_SIZE_OVER_LIMIT = (E_BASE + 47),

    /**
     * @brief 数据库连接数已用完。
     *
     */
    RDB_E_CON_OVER_LIMIT = (E_BASE + 48),

    /**
     * @brief 数据库已关闭。
     *
     * @since 18
     */
    RDB_E_ALREADY_CLOSED = (E_BASE + 50),

    /**
     * @brief 数据库繁忙。
     *
     * @since 18
     */
    RDB_E_DATABASE_BUSY = (E_BASE + 51),

    /**
     * @brief 数据库损坏。
     *
     * @since 18
     */
    RDB_E_SQLITE_CORRUPT = (E_BASE + 52),

    /**
     * @brief SQLite错误码：访问权限被拒绝。
     *
     * @since 18
     */
    RDB_E_SQLITE_PERM = (E_BASE + 53),

    /**
     * @brief SQLite错误码：数据库文件被锁定。
     *
     * @since 18
     */
    RDB_E_SQLITE_BUSY = (E_BASE + 54),

    /**
     * @brief SQLite错误码：数据库中的表被锁定。
     *
     * @since 18
     */
    RDB_E_SQLITE_LOCKED = (E_BASE + 55),

    /**
     * @brief SQLite错误码：数据库内存不足。
     *
     * @since 18
     */
    RDB_E_SQLITE_NOMEM = (E_BASE + 56),

    /**
     * @brief SQLite错误码：尝试写入只读数据库。
     *
     * @since 18
     */
    RDB_E_SQLITE_READONLY = (E_BASE + 57),

    /**
     * @brief SQLite错误码：磁盘I/O错误。
     *
     * @since 18
     */
    RDB_E_SQLITE_IOERR = (E_BASE + 58),

    /**
     * @brief SQLite错误码：数据库已满。
     *
     * @since 18
     */
    RDB_E_SQLITE_FULL = (E_BASE + 59),

    /**
     * @brief SQLite错误码：无法打开数据库文件。
     *
     * @since 18
     */
    RDB_E_SQLITE_CANT_OPEN = (E_BASE + 60),

    /**
     * @brief SQLite错误码：TEXT或BLOB超出大小限制。
     *
     * @since 18
     */
    RDB_E_SQLITE_TOO_BIG = (E_BASE + 61),

    /**
     * @brief SQLite错误码：数据类型不匹配。
     *
     * @since 18
     */
    RDB_E_SQLITE_MISMATCH = (E_BASE + 62),

    /**
     * @brief 存储数据为空。
     *
     * @since 18
     */
    RDB_E_DATA_TYPE_NULL = (E_BASE + 63),

    /**
     * @brief 数据类型不匹配。
     *
     * @since 18
     */
    RDB_E_TYPE_MISMATCH = (E_BASE + 64),

    /**
     * @brief SQLite错误码：SQLite约束。
     *
     * @since 18
     */
    RDB_E_SQLITE_CONSTRAINT = (E_BASE + 65),

    /**
     * @brief 订阅数量超过限制。
     *
     * @since 22
     */
    RDB_E_SUB_LIMIT_REACHED = (E_BASE + 66),

    /**
     * @brief SQLite错误码。可能原因：语法错误，例如表或列不存在。
     *
     * @since 23
     */
    RDB_E_SQLITE_ERROR = (E_BASE + 67),
} OH_Rdb_ErrCode;

#ifdef __cplusplus
};
#endif

/** @} */

#endif // RELATIONAL_STORE_ERRNO_CODE_ZH_CN_H
