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
 * @file oh_predicates.h
 *
 * @include database/rdb/oh_predicates.h
 * @brief 表示关系型数据库（RDB）的谓词。
 *
 * @kit ArkData
 * @library libnative_rdb_ndk.z.so
 * @syscap SystemCapability.DistributedDataManager.RelationalStore.Core
 * @since 10
 */

#ifndef OH_PREDICATES_ZH_CN_H
#define OH_PREDICATES_ZH_CN_H

#include <stdint.h>

#include <stddef.h>
#include "database/rdb/oh_value_object.h"
#include "database/data/oh_data_values.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 排序方式。
 *
 * @since 10
 */
typedef enum OH_OrderType {
    /**
     * 升序排列。
     */
    ASC = 0,
    /**
     * 降序排列。
     */
    DESC = 1,
} OH_OrderType;

/**
 * @brief 表示谓词。
 *
 * @since 10
 */
typedef struct OH_Predicates OH_Predicates;

/**
 * @brief 表示谓词。
 *
 * @since 10
 */
typedef struct OH_Predicates {
    /**
     * OH_Predicates结构体的唯一标识符。
     */
    int64_t id;

    /**
     * @brief 函数指针，配置谓词以匹配数据字段等于指定值的字段。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates, OH_VObject.
     * @since 10
     */
    OH_Predicates *(*equalTo)(OH_Predicates *predicates, const char *field, OH_VObject *valueObject);

    /**
     * @brief 函数指针，配置谓词以匹配数据字段不等于指定值的字段。
     * <br>该方法等同于SQL语句中的“!=”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates, OH_VObject.
     * @since 10
     */
    OH_Predicates *(*notEqualTo)(OH_Predicates *predicates, const char *field, OH_VObject *valueObject);

    /**
     * @brief 函数指针，向谓词添加左括号。
     * <br>该方法等同于SQL语句中的“(”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @return 返回带有左括号的谓词。
     * @see OH_Predicates.
     * @since 10
     */
    OH_Predicates *(*beginWrap)(OH_Predicates *predicates);

    /**
     * @brief 函数指针，向谓词添加右括号。
     * <br>该方法等同于SQL语句中的“)”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @return 返回带有右括号的谓词。
     * @see OH_Predicates.
     * @since 10
     */
    OH_Predicates *(*endWrap)(OH_Predicates *predicates);

    /**
     * @brief 函数指针，将或条件添加到谓词中。
     * <br>该方法等同于SQL语句中的“OR”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @return 返回带有或条件的谓词。
     * @see OH_Predicates.
     * @since 10
     */
    OH_Predicates *(*orOperate)(OH_Predicates *predicates);

    /**
     * @brief 函数指针，向谓词添加和条件。
     * <br>该方法等同于SQL语句中的“AND”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @return 返回带有和条件的谓词。
     * @see OH_Predicates.
     * @since 10
     */
    OH_Predicates *(*andOperate)(OH_Predicates *predicates);

    /**
     * @brief 函数指针，配置谓词以匹配值为null的字段。
     * <br>该方法等同于SQL语句中的“IS NULL”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates.
     * @since 10
     */
    OH_Predicates *(*isNull)(OH_Predicates *predicates, const char *field);

    /**
     * @brief 函数指针，配置谓词以匹配值不为null的指定字段。
     * <br>该方法等同于SQL语句中的“IS NOT NULL”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates.
     * @since 10
     */
    OH_Predicates *(*isNotNull)(OH_Predicates *predicates, const char *field);

    /**
     * @brief 函数指针，配置谓词以匹配数据字段为field且值类似于指定字符串的字段。
     * <br>该方法等同于SQL语句中的“LIKE”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates, OH_VObject.
     * @since 10
     */
    OH_Predicates *(*like)(OH_Predicates *predicates, const char *field, OH_VObject *valueObject);

    /**
     * @brief 函数指针，将谓词配置为匹配数据字段为field且其值在给定范围内的指定字段。
     * <br>该方法等同于SQL语句中的“BETWEEN”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates, OH_VObject.
     * @since 10
     */
    OH_Predicates *(*between)(OH_Predicates *predicates, const char *field, OH_VObject *valueObject);

    /**
     * @brief 函数指针，配置谓词以匹配数据字段为field且其值不在给定范围内的指定字段。
     * <br>该方法等同于SQL语句中的“NOT BETWEEN”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates, OH_VObject.
     * @since 10
     */
    OH_Predicates *(*notBetween)(OH_Predicates *predicates, const char *field, OH_VObject *valueObject);

    /**
     * @brief 函数指针，配置谓词以匹配数据字段为field且值大于指定值valueObject的字段。
     * <br>该方法等同于SQL语句中的“>”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates, OH_VObject.
     * @since 10
     */
    OH_Predicates *(*greaterThan)(OH_Predicates *predicates, const char *field, OH_VObject *valueObject);

    /**
     * @brief 函数指针，配置谓词以匹配数据字段为field且值小于指定值valueObject的字段。
     * <br>该方法等同于SQL语句中的“<”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates, OH_VObject.
     * @since 10
     */
    OH_Predicates *(*lessThan)(OH_Predicates *predicates, const char *field, OH_VObject *valueObject);

    /**
     * @brief 函数指针，配置谓词以匹配数据字段为field且值大于或等于指定值valueObject的字段。
     * <br>该方法等同于SQL语句中的“>=”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates, OH_VObject.
     * @since 10
     */
    OH_Predicates *(*greaterThanOrEqualTo)(OH_Predicates *predicates, const char *field, OH_VObject *valueObject);

    /**
     * @brief 函数指针，配置谓词以匹配数据字段为field且值小于或等于指定值valueObject的字段。
     * <br>该方法等同于SQL语句中的“<=”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates, OH_VObject.
     * @since 10
     */
    OH_Predicates *(*lessThanOrEqualTo)(OH_Predicates *predicates, const char *field, OH_VObject *valueObject);

    /**
     * @brief 函数指针，配置谓词以匹配其值按升序或降序排序的列。
     * <br>该方法等同于SQL语句中的“ORDER BY”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @param type 排序类型。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates, OH_OrderType.
     * @since 10
     */
    OH_Predicates *(*orderBy)(OH_Predicates *predicates, const char *field, OH_OrderType type);

    /**
     * @brief 函数指针，配置谓词以过滤重复记录并仅保留其中一个。
     * <br>该方法等同于SQL语句中的“DISTINCT”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @return 返回可用于过滤重复记录的谓词。
     * @see OH_Predicates.
     * @since 10
     */
    OH_Predicates *(*distinct)(OH_Predicates *predicates);

    /**
     * @brief 函数指针，设置最大数据记录数的谓词。
     * <br>该方法等同于SQL语句中的“LIMIT”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param value 表示最大数据记录数。
     * @return 返回可用于设置最大数据记录数的谓词。
     * @see OH_Predicates.
     * @since 10
     */
    OH_Predicates *(*limit)(OH_Predicates *predicates, unsigned int value);

    /**
     * @brief 函数指针，配置谓词以指定返回结果的起始位置。
     * <br>该方法等同于SQL语句中的“OFFSET”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param rowOffset 返回结果的起始位置，取值为正整数。
     * @return 返回具有指定返回结果起始位置的谓词。
     * @see OH_Predicates.
     * @since 10
     */
    OH_Predicates *(*offset)(OH_Predicates *predicates, unsigned int rowOffset);

    /**
     * @brief 函数指针，配置谓词按指定列分组查询结果。
     * <br>该方法等同于SQL语句中的“GROUP BY”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param fields 表示分组依赖的列名。
     * @param length 该参数为输入参数，表示fields数组的长度。
     * @return 返回分组查询列的谓词。
     * @see OH_Predicates.
     * @since 10
     */
    OH_Predicates *(*groupBy)(OH_Predicates *predicates, char const *const *fields, int length);

    /**
     * @brief 函数指针，配置谓词以匹配数据字段为field且其值在给定集合内的指定字段。
     * <br>该方法等同于SQL语句中的“IN”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates, OH_VObject.
     * @since 10
     */
    OH_Predicates *(*in)(OH_Predicates *predicates, const char *field, OH_VObject *valueObject);

    /**
     * @brief 函数指针，配置谓词以匹配数据字段为field且其值不在给定集合内的指定字段。
     * <br>该方法等同于SQL语句中的“NOT IN”。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @param field 表示数据库表中的列名。
     * @param valueObject 表示指向{@link OH_VObject}实例的指针。
     * @return 返回与指定字段匹配的谓词。
     * @see OH_Predicates, OH_VObject.
     * @since 10
     */
    OH_Predicates *(*notIn)(OH_Predicates *predicates, const char *field, OH_VObject *valueObject);

    /**
     * @brief 函数指针，清空谓词。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @return 返回清空后的谓词。
     * @see OH_Predicates.
     * @since 10
     */
    OH_Predicates *(*clear)(OH_Predicates *predicates);

    /**
     * @brief 销毁OH_Predicates对象，并回收该对象占用的内存。
     *
     * @param predicates 表示指向{@link OH_Predicates}实例的指针。
     * @return 返回操作是否成功，出错时返回对应的错误码。详细信息请参阅{@link OH_Rdb_ErrCode}。
     * @see OH_Predicates.
     * @since 10
     */
    int (*destroy)(OH_Predicates *predicates);
};

/**
 * @brief 设置OH_Predicates以匹配数据类型为字符串且值不类似于指定值的字段。
 * <br>此方法类似于SQL语句中的“Not like”。
 *
 * @param predicates 表示指向{@link OH_Predicates}实例的指针。
 * @param field 表示数据库表中的列名，不能为空。
 * @param pattern 表示要比较的指定值，不能为空。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
*/
int OH_Predicates_NotLike(OH_Predicates *predicates, const char *field, const char *pattern);

/**
 * @brief 设置OH_Predicates以匹配指定字段（数据类型为字符串）且值包含通配符的字段。
 * <br>与like方法不同，此方法的输入参数区分大小写。
 *
 * @param predicates 表示指向{@link OH_Predicates}实例的指针。
 * @param field 表示数据库表中的列名，不能为空。
 * @param pattern 表示与谓词匹配的值，不能为空。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
*/
int OH_Predicates_Glob(OH_Predicates *predicates, const char *field, const char *pattern);

/**
 * @brief 设置OH_Predicates以不匹配指定字段（数据类型为字符串）且值包含通配符的字段。
 * <br>与Not Like方法不同，此方法的输入参数区分大小写。
 *
 * @param predicates 表示指向{@link OH_Predicates}实例的指针。
 * @param field 表示数据库表中的列名，不能为空。
 * @param pattern 表示要比较的指定值，不能为空。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
*/
int OH_Predicates_NotGlob(OH_Predicates *predicates, const char *field, const char *pattern);

/**
 * @brief 设置OH_Predicates以指定条件来过滤分组结果，这些结果将出现在最终结果中。
 *
 * @param predicates 表示指向{@link OH_Predicates}实例的指针。
 * @param conditions 表示having子句中的过滤条件，不能为空且不能为空字符串。
 * @param values 表示指向{@link OH_Data_Values}实例的指针。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
*/
int OH_Predicates_Having(OH_Predicates *predicates, const char *conditions, const OH_Data_Values *values);
#ifdef __cplusplus
};
#endif

/** @} */

#endif // OH_PREDICATES_ZH_CN_H
