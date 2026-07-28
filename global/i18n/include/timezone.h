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
 * @addtogroup i18n
 * @{
 *
 * @brief Provides internationalization APIs for application localization, and relies on libohi18n.z.so when used.
 * @since 22
 */

/**
 * @file timezone.h
 *
 * @brief Provides the capability of obtaining time zone information.
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
 * @brief Enumerates the types of rules for defining dates.
 *
 * @since 22
 */
typedef enum DateRuleType {
    /**
     * @brief Indicates that day of the month. For example, October 16 in 2025 is the 16th day of October.
     */
    DOM = 0,

    /**
     * @brief Indicates that weekday of the month. For example, October 16 in 2025 is the third Thursday of October.
     */
    DOW = 1,

    /**
     * @brief Indicates that first weekday after the specified day of the month.
     * For example, October 16 in 2025 is the first Thursday after the 13th, 14th, or 15th day of October.
     */
    DOW_GEQ_DOM = 2,
    
    /**
     * @brief Indicates that last weekday before the specified day of the month.
     * For example, October 16 in 2025 is the last Thursday before the 20th day of October.
     */
    DOW_LEQ_DOM = 3
} DateRuleType;

/**
 * @brief Enumerates the types of rules for defining time.
 *
 * @since 22
 */
typedef enum TimeRuleType {
    /**
     * @brief Indicates that local clock time (not subject to time zone offset).
     */
    WALL_TIME = 0,
    
    /**
     * @brief Indicates that local standard time (not subject to DST offset).
     */
    STANDARD_TIME = 1,

    /**
     * @brief Indicates that world standard time (UTC time).
     */
    UTC_TIME = 2,
} TimeRuleType;

/**
 * @brief Defines the date and time rules to specify a date and time.
 *
 * @since 22
 */
typedef struct DateTimeRule {
    /**
     * @brief Indicates the month. The month starts from **0**, indicating January.
     */
    int32_t month;

    /**
     * @brief Indicates the day of a month.
     */
    int32_t dayOfMonth;

    /**
     * @brief Indicates the day of a week.
     */
    int32_t dayOfWeek;
    
    /**
     * @brief Indicates the week in a month.
     */
    int32_t weekInMonth;

    /**
     * @brief Indicates the millisecond value from 00:00 on the current day to the current time.
     */
    int32_t millisInDay;

    /**
     * @brief Indicates the date rule type.
     */
    DateRuleType dateRuleType;

    /**
     * @brief Indicates the time rule type.
     */
    TimeRuleType timeRuleType;
} DateTimeRule;

/**
 * @brief Defines the initial rule of a timezone which has no clear start time.
 *
 * @since 22
 */
typedef struct InitialTimeZoneRule {
    /**
     * @brief Indicates the raw offset of the time zone, in milliseconds.
     */
    int32_t rawOffset;

    /**
     * @brief Indicates the daylight saving time offset, in milliseconds.
     */
    int32_t dstSavings;
} InitialTimeZoneRule;

/**
 * @brief Defines time zone rule defined by the start timestamp array.
 *
 * @since 22
 */
typedef struct TimeArrayTimeZoneRule {
    /**
     * @brief Indicates the name of the time zone rule.
     */
    char* name;

    /**
     * @brief Indicates the raw offset of the time zone, in milliseconds.
     */
    int32_t rawOffset;

    /**
     * @brief Indicates the daylight saving time offset, in milliseconds.
     */
    int32_t dstSavings;

    /**
     * @brief Indicates the array of start timestamps when the rule takes effect. The timestamp unit is milliseconds.
     * The caller is responsible for releasing the array.
     */
    double* startTimes;

    /**
     * @brief Indicates the size of the start timestamp array of the rule.
     */
    int32_t numStartTimes;

    /**
     * @brief Indicates the TimeRule of the rule to specify the time.
     */
    TimeRuleType timeRuleType;
} TimeArrayTimeZoneRule;

/**
 * @brief Indicates the maximum year when the rule takes effective in AnnualTimeZoneRule.
 *
 * @since 22
 */
#define MAX_YEAR_IN_ANNUAL_TIMEZONE_RULE 0x7fffffff

/**
 * @brief Defines the time zone rule that takes effect annually.
 *
 * @since 22
 */
typedef struct AnnualTimeZoneRule {
    /**
     * @brief Indicates the name of the time zone rule.
     */
    char* name;
    
    /**
     * @brief Indicates the start year when the rule takes effective.
     */
    int32_t startYear;

    /**
     * @brief Indicates the end year when the rule takes effective.
     */
    int32_t endYear;

    /**
     * @brief Indicates the raw offset of the time zone, in milliseconds.
     */
    int32_t rawOffset;

    /**
     * @brief Indicates the daylight saving time offset, in milliseconds.
     */
    int32_t dstSavings;

    /**
     * @brief Indicates the rule of time and date.
     */
    DateTimeRule dateTimeRule;
} AnnualTimeZoneRule;

/**
 * @brief A complete time zone rule includes the start time zone rule, time zone rule defined by the start timestamp
 * array, and time zone rule that takes effect every year. It can comprehensively describe both the historical and
 * future rules of a time zone.
 *
 * @since 22
 */
typedef struct TimeZoneRules {
    /**
     * @brief Indicates the InitialTimeZoneRule of a timezone.
     */
    InitialTimeZoneRule initial;

    /**
     * @brief Indicates the TimeArrayTimeZoneRules of a timezone. The caller is responsible for releasing the array.
     */
    TimeArrayTimeZoneRule* timeArrayRules;

    /**
     * @brief Indicates the AnnualTimeZoneRules of a timezone. The caller is responsible for releasing the array.
     */
    AnnualTimeZoneRule* annualRules;

    /**
     * @brief Indicates the size of the time zone rule array defined by the start timestamp array.
     */
    size_t numTimeArrayRules;

    /**
     * @brief Indicates the size of the time zone rule array that takes effect annually.
     */
    size_t numAnnualRules;
} TimeZoneRules;

/**
 * @brief Obtains the timezone rules by timezone ID.
 *
 * @param timeZoneID Indicates the timezone ID, such as **Asia/Shanghai**.
 * @param rules Indicates the TimeZoneRules{@link TimeZoneRules} of timezoneID.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - Invalid parameter. Possible causes: Parameter verification failed.
 *         {@link UNEXPECTED_ERROR} 8900050 - Unexpected error, such as memory error.
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetTimeZoneRules(const char* timeZoneID, TimeZoneRules* rules);

/**
 * @brief Used to input the query information and receive the query result.
 *
 * @since 22
 */
typedef struct TimeZoneRuleQuery {
    /**
     * @brief Indicates the reference time for the query, in milliseconds. The value is Unix timestamp.
     */
    double base;

    /**
     * @brief Indicates the previous raw offset of the time zone, in milliseconds.
     */
    int32_t prevRawOffset;

    /**
     * @brief Indicates the previous daylight saving time offset, in milliseconds.
     */
    int32_t prevDSTSavings;

    /**
     * @brief Indicates whether the query result contains the base time. The value **true** indicates that the query
     * result contains the base time. The value **false** indicates the opposite.
     */
    bool inclusive;

    /**
     * @brief Indicates the query result, in milliseconds. The value is Unix timestamp.
     */
    double result;
} TimeZoneRuleQuery;

/**
 * @brief Obtains the time when the TimeArrayTimeZoneRule first took effect.
 *
 * @param rule Indicates the rule defined by TimeArrayTimeZoneRule{@link TimeArrayTimeZoneRule}.
 * @param query Indicates the query information and query result.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - Invalid parameter. Possible causes:
 *     Parameter verification failed.
 *         {@link UNEXPECTED_ERROR} 8900050 - Unexpected error, such as memory error.
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetFirstStartFromTimeArrayTimeZoneRule(TimeArrayTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief Obtains the time when the AnnualTimeZoneRule first took effect.
 *
 * @param rule Indicates the rule defined by AnnualTimeZoneRule{@link AnnualTimeZoneRule}.
 * @param query Indicates the query information and query result.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - Invalid parameter. Possible causes:
 *     Parameter verification failed.
 *         {@link UNEXPECTED_ERROR} 8900050 - Unexpected error, such as memory error.
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetFirstStartFromAnnualTimeZoneRule(AnnualTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief Obtains the time when the TimeArrayTimeZoneRule final took effect.
 *
 * @param rule Indicates the rule defined by TimeArrayTimeZoneRule{@link TimeArrayTimeZoneRule}.
 * @param query Indicates the query information and query result.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - Invalid parameter. Possible causes:
 *     Parameter verification failed.
 *         {@link UNEXPECTED_ERROR} 8900050 - Unexpected error, such as memory error.
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetFinalStartFromTimeArrayTimeZoneRule(TimeArrayTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief Obtains the time when the AnnualTimeZoneRule final took effect.
 *
 * @param rule Indicates the rule defined by AnnualTimeZoneRule{@link AnnualTimeZoneRule}.
 * @param query Indicates the query information and query result.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - Invalid parameter. Possible causes:
 *     Parameter verification failed.
 *         {@link UNEXPECTED_ERROR} 8900050 - Unexpected error, such as memory error.
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetFinalStartFromAnnualTimeZoneRule(AnnualTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief Obtains the time when the TimeArrayTimeZoneRule next took effect.
 *
 * @param rule Indicates the rule defined by TimeArrayTimeZoneRule{@link TimeArrayTimeZoneRule}.
 * @param query Indicates the query information and query result.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - Invalid parameter. Possible causes:
 *     Parameter verification failed.
 *         {@link UNEXPECTED_ERROR} 8900050 - Unexpected error, such as memory error.
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetNextStartFromTimeArrayTimeZoneRule(TimeArrayTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief Obtains the time when the AnnualTimeZoneRule next took effect.
 *
 * @param rule Indicates the rule defined by AnnualTimeZoneRule{@link AnnualTimeZoneRule}.
 * @param query Indicates the query information and query result.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - Invalid parameter. Possible causes:
 *     Parameter verification failed.
 *         {@link UNEXPECTED_ERROR} 8900050 - Unexpected error, such as memory error.
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetNextStartFromAnnualTimeZoneRule(AnnualTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief Obtains the time when the TimeArrayTimeZoneRule previous took effect.
 *
 * @param rule Indicates the rule defined by TimeArrayTimeZoneRule{@link TimeArrayTimeZoneRule}.
 * @param query Indicates the query information and query result.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - Invalid parameter. Possible causes:
 *     Parameter verification failed.
 *         {@link UNEXPECTED_ERROR} 8900050 - Unexpected error, such as memory error.
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetPrevStartFromTimeArrayTimeZoneRule(TimeArrayTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief Obtains the time when the AnnualTimeZoneRule previous took effect.
 *
 * @param rule Indicates the rule defined by AnnualTimeZoneRule{@link AnnualTimeZoneRule}.
 * @param query Indicates the query information and query result.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - Invalid parameter. Possible causes:
 *     Parameter verification failed.
 *         {@link UNEXPECTED_ERROR} 8900050 - Unexpected error, such as memory error.
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetPrevStartFromAnnualTimeZoneRule(AnnualTimeZoneRule* rule, TimeZoneRuleQuery* query);

/**
 * @brief Obtain the effective start time of a specific rule in the TimeArrayTimeZoneRule.
 *
 * @param rule Indicates the rule defined by TimeArrayTimeZoneRule{@link TimeArrayTimeZoneRule}.
 * @param index Index of the start time. Value range: [0, rule.numStartTimes - 1].
 * @param result Time when the rule takes effect, in milliseconds. The value is Unix timestamp.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - Invalid parameter. Possible causes:
 *     Parameter verification failed.
 *         {@link UNEXPECTED_ERROR} 8900050 - Unexpected error, such as memory error.
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetStartTimeAt(TimeArrayTimeZoneRule* rule, int32_t index, double* result);

/**
 * @brief Obtain the effective start time of a specific rule for target year in the AnnualTimeZoneRule.
 *
 * @param rule Indicates the rule defined by AnnualTimeZoneRule{@link AnnualTimeZoneRule}.
 * @param year Indicates the year used to get the rule defined by AnnualTimeZoneRule.
 * @param query Indicates the query information and result.
 * @return {@link SUCCESS} 0 - Success.
 *         {@link ERROR_INVALID_PARAMETER} 8900001 - Invalid parameter. Possible causes:
 *     Parameter verification failed.
 *         {@link UNEXPECTED_ERROR} 8900050 - Unexpected error, such as memory error.
 * @since 22
 */
I18n_ErrorCode OH_i18n_GetStartInYear(AnnualTimeZoneRule* rule, int32_t year, TimeZoneRuleQuery* query);

#ifdef __cplusplus
};
#endif
#endif // GLOBAL_I18N_TIMEZONE_H
/** @} */
