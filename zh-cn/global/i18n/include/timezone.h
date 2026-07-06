/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup i18n
 * @{
 *
 * @brief 为应用提供国际化能力，依赖libohi18n.z.so。
 * @since 22
 */

/**
 * @file timezone.h
 *
 * @brief 提供获取时区偏移量的能力
 *
 * @library libohi18n.so
 * @kit LocalizationKit
 * @syscap SystemCapability.Global.I18n
 * @since 22
 */

#ifndef GLOBAL_I18N_TIMEZONE_H
#define GLOBAL_I18N_TIMEZONE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "errorcode.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 枚举用于定义日期的规则类型。
 *
 * @since 22
 */
typedef enum DateRuleType {
    /**
     * @brief 表示日期由月份中的第几天（day_of_month）指定。
     */
    DOM = 0,

    /**
     * @brief 表示日期由星期几（day_of_week）指定。
     */
    DOW = 1,

    /**
     * @brief 表示日期由月份中的第几天（day_of_month）及之后最近的星期几（day_of_week）指定。
     */
    DOW_GEQ_DOM = 2,
    
    /**
     * @brief 表示日期由月份中的第几天（day_of_month）及之前最近的星期几（day_of_week）指定。
     */
    DOW_LEQ_DOM = 3
} DateRuleType;

/**
 * @brief 枚举用于定义时间的规则类型。
 *
 * @since 22
 */
typedef enum TimeRuleType {
    /**
     * @brief 表示时间由本地墙钟时间（wall time）指定。
     */
    WALL_TIME = 0,
    
    /**
     * @brief 表示时间由标准时间（standard time）指定。
     */
    STANDARD_TIME = 1,

    /**
     * @brief 表示时间由协调世界时（UTC time）指定。
     */
    UTC_TIME = 2,
} TimeRuleType;

/**
 * @brief 定义用于指定具体日期和时间的规则。
 *
 * @since 22
 */
typedef struct DateTimeRule {
    /**
     * @brief 表示月份。
     */
    int32_t month;

    /**
     * @brief 表示月份中的第几天。
     */
    int32_t dayOfMonth;

    /**
     * @brief 表示星期几。
     */
    int32_t dayOfWeek;
    
    /**
     * @brief 表示月份中的第几周。
     */
    int32_t weekInMonth;

    /**
     * @brief 表示一天中的毫秒数（从午夜开始计算）。
     */
    int32_t millisInDay;

    /**
     * @brief 表示日期规则类型。
     */
    DateRuleType dateRuleType;

    /**
     * @brief 表示时间规则类型。
     */
    TimeRuleType timeRuleType;
} DateTimeRule;

/**
 * @brief 定义没有明确起始时间的时区初始规则。
 *
 * @since 22
 */
typedef struct InitialTimeZoneRule {
    /**
     * @brief 表示时区的原始偏移量（相对于UTC）。
     */
    int32_t rawOffset;

    /**
     * @brief 表示时区的夏令时节省偏移量。
     */
    int32_t dstSavings;
} InitialTimeZoneRule;

/**
 * @brief 通过规则生效时间数组定义一组时区规则。
 *
 * @since 22
 */
typedef struct TimeArrayTimeZoneRule {
    /**
     * @brief 表示时区名称。
     */
    char* name;

    /**
     * @brief 表示时区的原始偏移量。
     */
    int32_t rawOffset;

    /**
     * @brief 表示时区的夏令时节省偏移量。
     */
    int32_t dstSavings;

    /**
     * @brief 表示规则生效的起始时间数组。调用者负责释放该数组。
     */
    double* startTimes;

    /**
     * @brief 表示规则生效起始时间的数量。
     */
    int32_t numStartTimes;

    /**
     * @brief 表示用于指定时间的规则时间类型。
     */
    TimeRuleType timeRuleType;
} TimeArrayTimeZoneRule;

/**
 * @brief 表示 AnnualTimeZoneRule 中规则生效的最大年份。
 *
 * @since 22
 */
#define MAX_YEAR_IN_ANNUAL_TIMEZONE_RULE 0x7fffffff

/**
 * @brief 通过指定规则生效的起始年份和结束年份来定义一组时区规则。
 *
 * @since 22
 */
typedef struct AnnualTimeZoneRule {
    /**
     * @brief 表示时区名称。
     */
    char* name;
    
    /**
     * @brief 表示规则生效的起始年份。
     */
    int32_t startYear;

    /**
     * @brief 表示规则生效的结束年份。
     */
    int32_t endYear;

    /**
     * @brief 表示时区的原始偏移量。
     */
    int32_t rawOffset;

    /**
     * @brief 表示时区的夏令时节省偏移量。
     */
    int32_t dstSavings;

    /**
     * @brief 表示用于指定日期和时间的 DateTimeRule 规则。
     */
    DateTimeRule dateTimeRule;
} AnnualTimeZoneRule;

/**
 * @brief 定义某个时区的一组时区规则。
 *
 * @since 22
 */
typedef struct TimeZoneRules {
    /**
     * @brief 表示时区的初始时区规则。
     */
    InitialTimeZoneRule initial;

    /**
     * @brief 表示时区的 TimeArrayTimeZoneRule 数组。调用者负责释放该数组。
     */
    TimeArrayTimeZoneRule* timeArrayRules;

    /**
     * @brief 表示时区的 AnnualTimeZoneRule 数组。调用者负责释放该数组。
     */
    AnnualTimeZoneRule* annualRules;

    /**
     * @brief 表示 TimeArrayTimeZoneRule 的数量。
     */
    size_t numTimeArrayRules;

    /**
     * @brief 表示 AnnualTimeZoneRule 的数量。
     */
    size_t numAnnualRules;
} TimeZoneRules;

/**
 * @brief 根据时区ID获取时区规则。
 *
 * @param timeZoneID 表示时区ID，例如 "Asia/Shanghai"。
 * @param rules 表示对应时区ID的 TimeZoneRules 结构体。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 参数无效。可能原因：参数校验失败。
 *         {@link UNEXPECTED_ERROR} 8900050 - 意外错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetTimeZoneRules(const char* timeZoneID, TimeZoneRules* rules);

/**
 * @brief 定义查询信息和查询结果。
 *
 * @since 22
 */
typedef struct TimeZoneRuleQuery {
    /**
     * @brief 表示查询下一次或上一次起始时间时的基准时间。
     */
    double base;

    /**
     * @brief 表示上一次的原始偏移量。
     */
    int32_t prevRawOffset;

    /**
     * @brief 表示上一次的夏令时节省偏移量。
     */
    int32_t prevDSTSavings;

    /**
     * @brief 表示基准时间是否包含在查询范围内。
     */
    bool inclusive;

    /**
     * @brief 表示查询结果。
     */
    double result;
} TimeZoneRuleQuery;

/**
 * @brief 获取 TimeArrayTimeZoneRule 首次生效的时间。
 *
 * @param rule 表示由 TimeArrayTimeZoneRule 定义的规则。
 * @param query 表示查询信息和查询结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 参数无效。可能原因：参数校验失败。
 *         {@link UNEXPECTED_ERROR} 8900050 - 意外错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetFirstStartFromTimeArrayTimeZoneRule(TimeArrayTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 获取 AnnualTimeZoneRule 首次生效的时间。
 *
 * @param rule 表示由 AnnualTimeZoneRule 定义的规则。
 * @param query 表示查询信息和查询结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 参数无效。可能原因：参数校验失败。
 *         {@link UNEXPECTED_ERROR} 8900050 - 意外错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetFirstStartFromAnnualTimeZoneRule(AnnualTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 获取 TimeArrayTimeZoneRule 最后一次生效的时间。
 *
 * @param rule 表示由 TimeArrayTimeZoneRule 定义的规则。
 * @param query 表示查询信息和查询结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 参数无效。可能原因：参数校验失败。
 *         {@link UNEXPECTED_ERROR} 8900050 - 意外错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetFinalStartFromTimeArrayTimeZoneRule(TimeArrayTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 获取 AnnualTimeZoneRule 最后一次生效的时间。
 *
 * @param rule 表示由 AnnualTimeZoneRule 定义的规则。
 * @param query 表示查询信息和查询结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 参数无效。可能原因：参数校验失败。
 *         {@link UNEXPECTED_ERROR} 8900050 - 意外错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetFinalStartFromAnnualTimeZoneRule(AnnualTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 获取 TimeArrayTimeZoneRule 下一次生效的时间。
 *
 * @param rule 表示由 TimeArrayTimeZoneRule 定义的规则。
 * @param query 表示查询信息和查询结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 参数无效。可能原因：参数校验失败。
 *         {@link UNEXPECTED_ERROR} 8900050 - 意外错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetNextStartFromTimeArrayTimeZoneRule(TimeArrayTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 获取 AnnualTimeZoneRule 下一次生效的时间。
 *
 * @param rule 表示由 AnnualTimeZoneRule 定义的规则。
 * @param query 表示查询信息和查询结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 参数无效。可能原因：参数校验失败。
 *         {@link UNEXPECTED_ERROR} 8900050 - 意外错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetNextStartFromAnnualTimeZoneRule(AnnualTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 获取 TimeArrayTimeZoneRule 上一次生效的时间。
 *
 * @param rule 表示由 TimeArrayTimeZoneRule 定义的规则。
 * @param query 表示查询信息和查询结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 参数无效。可能原因：参数校验失败。
 *         {@link UNEXPECTED_ERROR} 8900050 - 意外错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetPrevStartFromTimeArrayTimeZoneRule(TimeArrayTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 获取 AnnualTimeZoneRule 上一次生效的时间。
 *
 * @param rule 表示由 AnnualTimeZoneRule 定义的规则。
 * @param query 表示查询信息和查询结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 参数无效。可能原因：参数校验失败。
 *         {@link UNEXPECTED_ERROR} 8900050 - 意外错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetPrevStartFromAnnualTimeZoneRule(AnnualTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 获取 TimeArrayTimeZoneRule 中特定规则的生效起始时间。
 *
 * @param rule 表示由 TimeArrayTimeZoneRule 定义的规则。
 * @param index 表示规则索引。
 * @param result 表示规则的起始时间。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 参数无效。可能原因：参数校验失败。
 *         {@link UNEXPECTED_ERROR} 8900050 - 意外错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetStartTimeAt(TimeArrayTimeZoneRule* rule, int32_t index, double* result);

/**
 * @brief 获取 AnnualTimeZoneRule 中目标年份特定规则的生效起始时间。
 *
 * @param rule 表示由 AnnualTimeZoneRule 定义的规则。
 * @param year 表示用于获取 AnnualTimeZoneRule 定义规则的年份。
 * @param query 表示查询信息和结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 参数无效。可能原因：参数校验失败。
 *         {@link UNEXPECTED_ERROR} 8900050 - 意外错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetStartInYear(AnnualTimeZoneRule* rule, int32_t year, TimeZoneRuleQuery* query);

#ifdef __cplusplus
};
#endif
#endif // GLOBAL_I18N_TIMEZONE_H
/** @} */
