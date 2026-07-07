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
 * @brief 时间日期规则。
 *
 * @since 22
 */
typedef struct DateTimeRule {
    /**
     * @brief 月份。月份从0开始计数，0表示一月。
     */
    int32_t month;

    /**
     * @brief 当月的第几天。
     */
    int32_t dayOfMonth;

    /**
     * @brief 当周的第几天。
     */
    int32_t dayOfWeek;
    
    /**
     * @brief 当月的第几周。
     */
    int32_t weekInMonth;

    /**
     * @brief 从当天凌晨0点开始到当前时间的毫秒值。
     */
    int32_t millisInDay;

    /**
     * @brief 日期规则类型。
     */
    DateRuleType dateRuleType;

    /**
     * @brief 时间规则类型。
     */
    TimeRuleType timeRuleType;
} DateTimeRule;

/**
 * @brief 起始时区规则。
 *
 * @since 22
 */
typedef struct InitialTimeZoneRule {
    /**
     * @brief 时区的原始偏移量，单位为毫秒（ms）。
     */
    int32_t rawOffset;

    /**
     * @brief 夏令时的偏移量，单位为毫秒（ms）。
     */
    int32_t dstSavings;
} InitialTimeZoneRule;

/**
 * @brief 起始时间戳数组定义的时区规则。
 *
 * @since 22
 */
typedef struct TimeArrayTimeZoneRule {
    /**
     * @brief 时区规则的名称。
     */
    char* name;

    /**
     * @brief 时区的原始偏移量，单位为毫秒（ms）。
     */
    int32_t rawOffset;

    /**
     * @brief 夏令时的偏移量，单位为毫秒（ms）。
     */
    int32_t dstSavings;

    /**
     * @brief 规则生效的起始时间戳数组，起始时间戳单位为毫秒（ms）。
     */
    double* startTimes;

    /**
     * @brief 规则生效的起始时间戳数组的大小。
     */
    int32_t numStartTimes;

    /**
     * @brief 时间规则类型。
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
 * @brief 每年生效的时区规则。
 *
 * @since 22
 */
typedef struct AnnualTimeZoneRule {
    /**
     * @brief 时区规则的名称。
     */
    char* name;
    
    /**
     * @brief 时区规则生效的起始年份。
     */
    int32_t startYear;

    /**
     * @brief 时区规则生效的终止年份。
     */
    int32_t endYear;

    /**
     * @brief 时区的原始偏移量，单位为毫秒（ms）。
     */
    int32_t rawOffset;

    /**
     * @brief 夏令时的偏移量，单位为毫秒（ms）。
     */
    int32_t dstSavings;

    /**
     * @brief 时间日期规则。
     */
    DateTimeRule dateTimeRule;
} AnnualTimeZoneRule;

/**
 * @brief 完整的时区规则，包括起始时区规则、起始时间戳数组定义的时区规则和每年生效的时区规则，能够全面描述时区的历史和未来规则。
 *
 * @since 22
 */
typedef struct TimeZoneRules {
    /**
     * @brief 起始时区规则。
     */
    InitialTimeZoneRule initial;

    /**
     * @brief 起始时间戳数组定义的时区规则数组。
     */
    TimeArrayTimeZoneRule* timeArrayRules;

    /**
     * @brief 每年生效的时区规则数组。
     */
    AnnualTimeZoneRule* annualRules;

    /**
     * @brief 起始时间戳数组定义的时区规则数组的大小。
     */
    size_t numTimeArrayRules;

    /**
     * @brief 表示 每年生效的时区规则数组的大小。
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
 * @brief 用于传入查询的信息，并接收查询的结果。
 *
 * @since 22
 */
typedef struct TimeZoneRuleQuery {
    /**
     * @brief 查询的基准时间，单位为毫秒（ms），采用Unix时间戳格式。
     */
    double base;

    /**
     * @brief 上一次的时区原始偏移量，单位为毫秒（ms）。
     */
    int32_t prevRawOffset;

    /**
     * @brief 上一次的夏令时偏移量，单位为毫秒（ms）。
     */
    int32_t prevDSTSavings;

    /**
     * @brief 查询结果是否包含基准时间。true：查询结果包含基准时间；false：查询结果不包含基准时间。
     */
    bool inclusive;

    /**
     * @brief 查询结果，单位为毫秒（ms），采用Unix时间戳格式。
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
