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
 * @brief 提供获取时区信息的能力。
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
 * @brief 日期规则类型的枚举。
 *
 * @since 22
 */
typedef enum DateRuleType {
    /**
     * @brief 当月的第几天，以2025年为例，十月十六日为：十月的第十六天。
     */
    DOM = 0,

    /**
     * @brief 当月的第几个星期几，以2025年为例，十月十六日为：十月的第三个星期四。
     */
    DOW = 1,

    /**
     * @brief 当月第几天之后的第一个星期几，以2025年为例，十月十六日为：十月第十三天/十四天/十五天之后的第一个星期四。
     */
    DOW_GEQ_DOM = 2,
    
    /**
     * @brief 当月第几天之前的最后一个星期几，以2025年为例，十月十六日为：十月第二十天之前的最后一个星期四。
     */
    DOW_LEQ_DOM = 3
} DateRuleType;

/**
 * @brief 时间规则类型的枚举。
 *
 * @since 22
 */
typedef enum TimeRuleType {
    /**
     * @brief 本地时钟时间（不考虑时区偏移）。
     */
    WALL_TIME = 0,
    
    /**
     * @brief 本地标准时间（不考虑夏令时偏移）。
     */
    STANDARD_TIME = 1,

    /**
     * @brief 世界标准时间（UTC时间）。
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
 * @brief 每年生效时区规则的年份最大值。
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
     * @brief 每年生效的时区规则数组的大小。
     */
    size_t numAnnualRules;
} TimeZoneRules;

/**
 * @brief 通过时区ID，获取完整的时区规则。
 *
 * @param timeZoneID 时区ID，例如“Asia/Shanghai”。
 * @param rules 与时区ID对应的完整时区规则TimeZoneRules。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 传入参数无效。
 *         {@link UNEXPECTED_ERROR} 8900050 - 预期之外的错误，例如内存错误。
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
 * @brief 根据TimeArrayTimeZoneRule，获取时区规则的首次生效时间。
 *
 * @param rule 起始时间戳数组定义的时区规则[TimeArrayTimeZoneRule](docroot://reference/apis-localization-kit/capi-i18n-timearraytimezonerule.md)。
 * @param query 用于传入查询的信息，并接收查询的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 传入参数无效。
 *         {@link UNEXPECTED_ERROR} 8900050 - 预期之外的错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetFirstStartFromTimeArrayTimeZoneRule(TimeArrayTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 根据AnnualTimeZoneRule，获取时区规则的首次生效时间。
 *
 * @param rule 每年生效的时区规则[AnnualTimeZoneRule](docroot://reference/apis-localization-kit/capi-i18n-annualtimezonerule.md)。
 * @param query 用于传入查询的信息，并接收查询的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 传入参数无效。
 *         {@link UNEXPECTED_ERROR} 8900050 - 预期之外的错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetFirstStartFromAnnualTimeZoneRule(AnnualTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 根据TimeArrayTimeZoneRule，获取时区规则的最后一次生效时间。
 *
 * @param rule 起始时间戳数组定义的时区规则[TimeArrayTimeZoneRule](docroot://reference/apis-localization-kit/capi-i18n-timearraytimezonerule.md)。
 * @param query 用于传入查询的信息，并接收查询的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 传入参数无效。
 *         {@link UNEXPECTED_ERROR} 8900050 - 预期之外的错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetFinalStartFromTimeArrayTimeZoneRule(TimeArrayTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 根据AnnualTimeZoneRule，获取时区规则的最后一次生效时间。
 *
 * @param rule 每年生效的时区规则[AnnualTimeZoneRule](docroot://reference/apis-localization-kit/capi-i18n-annualtimezonerule.md)。
 * @param query 用于传入查询的信息，并接收查询的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 传入参数无效。
 *         {@link UNEXPECTED_ERROR} 8900050 - 预期之外的错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetFinalStartFromAnnualTimeZoneRule(AnnualTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 根据TimeArrayTimeZoneRule，获取时区规则在基准时间之后的下一次生效时间。
 *
 * @param rule 起始时间戳数组定义的时区规则[TimeArrayTimeZoneRule](docroot://reference/apis-localization-kit/capi-i18n-timearraytimezonerule.md)。
 * @param query 用于传入查询的信息，并接收查询的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 传入参数无效。
 *         {@link UNEXPECTED_ERROR} 8900050 - 预期之外的错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetNextStartFromTimeArrayTimeZoneRule(TimeArrayTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 根据AnnualTimeZoneRule，获取时区规则在基准时间之后的下一次生效时间。
 *
 * @param rule 每年生效的时区规则[AnnualTimeZoneRule](docroot://reference/apis-localization-kit/capi-i18n-annualtimezonerule.md)。
 * @param query 用于传入查询的信息，并接收查询的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 传入参数无效。
 *         {@link UNEXPECTED_ERROR} 8900050 - 预期之外的错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetNextStartFromAnnualTimeZoneRule(AnnualTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 根据TimeArrayTimeZoneRule，获取时区规则在基准时间之前的上一次生效时间。
 *
 * @param rule 起始时间戳数组定义的时区规则[TimeArrayTimeZoneRule](docroot://reference/apis-localization-kit/capi-i18n-timearraytimezonerule.md)。
 * @param query 用于传入查询的信息，并接收查询的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 传入参数无效。
 *         {@link UNEXPECTED_ERROR} 8900050 - 预期之外的错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetPrevStartFromTimeArrayTimeZoneRule(TimeArrayTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 根据AnnualTimeZoneRule，获取时区规则在基准时间之前的上一次生效时间。
 *
 * @param rule 每年生效的时区规则[AnnualTimeZoneRule](docroot://reference/apis-localization-kit/capi-i18n-annualtimezonerule.md)。
 * @param query 用于传入查询的信息，并接收查询的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 传入参数无效。
 *         {@link UNEXPECTED_ERROR} 8900050 - 预期之外的错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetPrevStartFromAnnualTimeZoneRule(AnnualTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief 根据TimeArrayTimeZoneRule，获取时区规则指定索引的起始时间。
 *
 * @param rule 起始时间戳数组定义的时区规则[TimeArrayTimeZoneRule](docroot://reference/apis-localization-kit/capi-i18n-timearraytimezonerule.md)。
 * @param index 起始时间的索引。取值范围：[0, rule.numStartTimes - 1]。
 * @param result 规则生效的起始时间，单位为毫秒（ms），采用Unix时间戳格式。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 传入参数无效。
 *         {@link UNEXPECTED_ERROR} 8900050 - 预期之外的错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetStartTimeAt(TimeArrayTimeZoneRule* rule, int32_t index, double* result);

/**
 * @brief 根据AnnualTimeZoneRule，获取时区规则在指定年份的生效时间。
 *
 * @param rule 每年生效的时区规则[AnnualTimeZoneRule](docroot://reference/apis-localization-kit/capi-i18n-annualtimezonerule.md)。
 * @param year 查询的年份。
 * @param query 用于传入查询的信息，并接收查询的结果。
 * @return {@link SUCCESS} 0 - 成功。
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - 传入参数无效。
 *         {@link UNEXPECTED_ERROR} 8900050 - 预期之外的错误，例如内存错误。
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetStartInYear(AnnualTimeZoneRule* rule, int32_t year, TimeZoneRuleQuery* query);

#ifdef __cplusplus
};
#endif
#endif // GLOBAL_I18N_TIMEZONE_H
/** @} */
