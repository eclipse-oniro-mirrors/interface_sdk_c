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
 * @file oh_rdb_types.h
 *
 * @include database/rdb/oh_rdb_types.h
 * @brief 提供与数据值相关的类型定义。
 *
 * @kit ArkData
 * @library libnative_rdb_ndk.z.so
 * @syscap SystemCapability.DistributedDataManager.RelationalStore.Core
 *
 * @since 18
 */

#ifndef OH_RDB_TYPES_ZH_CN_H
#define OH_RDB_TYPES_ZH_CN_H
#include <inttypes.h>
#include "database/rdb/oh_cursor.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 表示冲突解决策略的枚举。
 *
 * @since 18
 */
typedef enum Rdb_ConflictResolution {
    /**
     * @brief 发生冲突时不执行任何操作。
     *
     */
    RDB_CONFLICT_NONE = 1,
    /**
     * @brief 发生冲突时抛出错误码，同时回滚本次事务。
     *
     */
    RDB_CONFLICT_ROLLBACK,
    /**
     * @brief 发生冲突时抛出错误码，同时回滚本次修改。
     *
     */
    RDB_CONFLICT_ABORT,
    /**
     * @brief 发生冲突时抛出错误码，不回滚冲突前的修改同时终止本次修改。
     *
     */
    RDB_CONFLICT_FAIL,
    /**
     * @brief 发生冲突时忽略冲突的数据，继续执行后续修改。
     *
     */
    RDB_CONFLICT_IGNORE,
    /**
     * @brief 发生冲突时，尝试删除后插入，如果还是冲突则等同于RDB_CONFLICT_ABORT。
     *
     */
    RDB_CONFLICT_REPLACE,
} Rdb_ConflictResolution;

/**
 * @brief returning相关接口的上下文。
 *
 * @since 23
 */
typedef struct OH_RDB_ReturningContext OH_RDB_ReturningContext;

/**
 * @brief 创建{@link OH_RDB_ReturningContext}的实例对象。
 *
 * @return 执行成功时返回指向{@link OH_RDB_ReturningContext}实例的指针。
 *     <br>否则返回nullptr。使用完成后必须通过{@link OH_RDB_DestroyReturningContext}接口释放内存。
 * @see OH_RDB_DestroyReturningContext.
 * @since 23
 */
OH_RDB_ReturningContext *OH_RDB_CreateReturningContext(void);

/**
 * @brief 销毁{@link OH_RDB_ReturningContext}实例对象。
 *
 * @param context 指向{@link OH_RDB_ReturningContext}实例的指针。
 * @since 23
 */
void OH_RDB_DestroyReturningContext(OH_RDB_ReturningContext *context);

/**
 * @brief 设置结果集中返回的字段。
 *
 * @param context 指向{@link OH_RDB_ReturningContext}实例的指针。
 * @param fields 要返回的字段名。
 * @param len 字段数量。
 * @return 返回执行结果。
 *     <br>执行成功返回RDB_OK。
 *     <br>输入参数无效返回RDB_E_INVALID_ARGS。
 * @since 23
 */
int OH_RDB_SetReturningFields(OH_RDB_ReturningContext *context, const char *const fields[], int32_t len);

/**
 * @brief 设置返回结果集的最大行数量。
 *
 * @param context 指向{@link OH_RDB_ReturningContext}实例的指针。
 * @param count 表示返回结果集的最大行数量。
 * @return 返回执行结果。
 *     <br>执行成功返回RDB_OK。
 *     <br>输入参数无效返回RDB_E_INVALID_ARGS。
 * @since 23
 */
int OH_RDB_SetMaxReturningCount(OH_RDB_ReturningContext *context, int32_t count);

/**
 * @brief 获取数据变化的游标，默认包含1024行。
 *
 * @param context 指向{@link OH_RDB_ReturningContext}实例的指针。
 * @return 返回指向{@link OH_Cursor}结构体实例的指针。
 *     <br>如果获取游标失败，则返回nullptr。使用{@link OH_RDB_DestroyReturningContext}接口释放内存时会销毁游标，无需单独释放。
 * @since 23
 */
OH_Cursor *OH_RDB_GetReturningValues(OH_RDB_ReturningContext *context);

/**
 * @brief 获取受此操作影响的数据行的数量。
 *
 * @param context 指向{@link OH_RDB_ReturningContext}实例的指针。
 * @return 返回已更改的条目数，如果获取变更失败则返回-1。
 * @since 23
 */
int64_t OH_RDB_GetChangedCount(OH_RDB_ReturningContext *context);
#ifdef __cplusplus
};
#endif
#endif
/** @} */
