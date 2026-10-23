/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
 * @addtogroup HiLog
 * @{
 *
 * @brief Provides logging functions.
 *
 * For example, you can use these functions to output logs of the specified log type, service domain, log tag,
 * and log level.
 *
 * @since 8
 */

/**
 * @file log.h
 *
 * @brief Defines the logging functions of the HiLog module. Before outputting logs, you must define the service domain,
 *  and log tag, use the API with the specified log type and level, and specify the privacy identifier.
 * <br>**Service domain**: service domain of logs. You can define the value as required. Its value is a hexadecimal
 * integer ranging from 0x0 to 0xFFFF. If the value exceeds the range, logs cannot be printed.
 * <br>**Log tag**: a string used to identify the class, file, or service behavior.
 * <br>**Log level**: DEBUG, INFO, WARN, ERROR, or FATAL.
 * <br>**Parameter format**: printf format string, which starts with a % character, including a parameter type
 * identifier and a variable parameter.
 * <br>**Privacy identifier**: **{public}** or **{private}** added between the % character and the parameter type
 * identifier in each parameter. **Note**: If no privacy identifier is added, the parameter is considered to be **
 * private**.
 *
 * @kit PerformanceAnalysisKit
 * @include <hilog/log.h>
 * @library libhilog_ndk.z.so
 * @syscap SystemCapability.HiviewDFX.HiLog
 * @since 8
 */

#ifndef HIVIEWDFX_HILOG_H
#define HIVIEWDFX_HILOG_H

#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
#ifndef LOG_DOMAIN
#define LOG_DOMAIN 0
#endif
#ifndef LOG_TAG
#define LOG_TAG NULL
#endif

/**
 * @brief Enumerates the log types. You can use this function to specify the type of output logs. Currently, only **
 * LOG_APP** is available.
 *
 * @since 8
 */
typedef enum {
    /**
     * @brief Application log.
     */
    LOG_APP = 0
} LogType;

/**
 * @brief Enumerates the log levels. You are advised to select log levels based on their respective use cases. Log
 * levels:
 * <br>**DEBUG**: provides more detailed process information than INFO logs to help developers analyze service
 * processes and locate faults. DEBUG logs are not recorded in official versions by default. They are available in
 * debug versions or in official versions with the debug function enabled.
 * <br>**INFO**: indicates the key service process nodes and exceptions (for example, no network signal or login
 * failure) that occur during service running. These logs should be recorded by the dominant module in the service to
 * avoid repeated logging conducted by multiple invoked modules or low-level functions.
 * <br>**WARN**: indicates a severe, unexpected fault that has little impact on users and can be rectified by the
 * programs themselves or through simple operations.
 * <br>**ERROR**: indicates a program or functional error that affects the normal running or use of the functionality
 * and can be fixed at a high cost, for example, by resetting data.
 * <br>**FATAL**: indicates that a program or functionality is about to crash and the fault cannot be rectified.
 *
 * @since 8
 */
typedef enum {
    /**
     * @brief DEBUG level to be used by **OH_LOG_DEBUG**.
     */
    LOG_DEBUG = 3,
    /**
     * @brief INFO level to be used by **OH_LOG_INFO**.
     */
    LOG_INFO = 4,
    /**
     * @brief WARN level to be used by **OH_LOG_WARN**.
     */
    LOG_WARN = 5,
    /**
     * @brief ERROR level to be used by **OH_LOG_ERROR**.
     */
    LOG_ERROR = 6,
    /**
     * @brief FATAL level to be used by **OH_LOG_FATAL**.
     */
    LOG_FATAL = 7
} LogLevel;

/**
 * @brief Enumerates the preference strategies. This enum is used in {@link OH_LOG_SetLogLevel}. The minimum log level
 * that takes effect varies according to the strategy.
 *
 * @since 21
 */
typedef enum {
    /**
     * @brief The setting is cleared. The minimum log level that actually takes effect is the system-controlled minimum
     * log level.
     */
    UNSET_LOGLEVEL = 0,
    /**
     * @brief The minimum log level that actually takes effect is the larger value of the new log level and the system-
     * controlled minimum log level.
     */
    PREFER_CLOSE_LOG = 1,
    /**
     * @brief The minimum log level that actually takes effect is the smaller value of the new log level and the system-
     * controlled minimum log level.
     */
    PREFER_OPEN_LOG = 2
} PreferStrategy;

/**
 * @brief Outputs logs of the specified **type**, **level**, **domain**, **tag**, and variables determined by the
 * format specifier and privacy identifier in the printf format.
 *
 * @param type Log type. The type for third-party applications is defined by **LOG_APP**.
 * @param level Log level. The value can be **LOG_DEBUG**, **LOG_INFO**, **LOG_WARN**, **LOG_ERROR**, and **LOG_FATAL**.
 * @param domain Service domain. Its value is a hexadecimal integer ranging from 0x0 to 0xFFFF. If the value exceeds
 *     the range, logs cannot be printed.
 * @param tag Log tag, which is a string used to identify the class, file, or service. A tag can contain a maximum of
 *     31 bytes. If a tag exceeds this limit, it will be truncated. Chinese characters are not recommended because
 *     garbled characters or alignment problems may occur.
 * @param fmt Format string, which is an enhancement of a printf format string and supports the privacy identifier.
 *     Specifically, **{public}** or **{private}** is added between the % character and the format specifier in each
 *     parameter.
 * @param ... Parameter list corresponding to the parameter type in the format string. The number and type of
 *     parameters must be mapped onto the identifier in the format string.
 * @return **0** or a larger value if the operation is successful; a value smaller than **0** otherwise.
 *     <br>Possible failure causes: The **LogLevel** passed in is lower than the allowed log level; the **domain** is
 *     out of range; the **tag** is a null pointer; the CPU is overloaded; the memory is insufficient; the number of
 *     logs on the device is too large.
 * @since 8
 */
int OH_LOG_Print(LogType type, LogLevel level, unsigned int domain, const char *tag, const char *fmt, ...)
    __attribute__((__format__(os_log, 5, 6)));

/**
 * @brief Outputs constant log strings of the specified **type**, **level**, **domain**, and **tag**.
 *
 * @param type Log type. The type for third-party applications is defined by **LOG_APP**.
 * @param level Log level. The value can be **LOG_DEBUG**, **LOG_INFO**, **LOG_WARN**, **LOG_ERROR**, and **LOG_FATAL**.
 * @param domain Service domain. Its value is a hexadecimal integer ranging from 0x0 to 0xFFFF. If the value exceeds
 *     the range, logs cannot be printed.
 * @param tag Log tag, which is a string used to identify the class, file, or service. A tag can contain a maximum of
 *     31 bytes. If a tag exceeds this limit, it will be truncated. Chinese characters are not recommended because
 *     garbled characters or alignment problems may occur.
 * @param message Constant log string.
 * @return **0** or a larger value if the operation is successful; a value smaller than **0** otherwise.
 *     <br>Possible failure causes: The **LogLevel** passed in is lower than the allowed log level; the **domain** is
 *     out of range; the **tag** is a null pointer; the CPU is overloaded; the memory is insufficient; the number of
 *     logs on the device is too large.
 * @since 18
 */
int OH_LOG_PrintMsg(LogType type, LogLevel level, unsigned int domain, const char *tag, const char *message);

/**
 * @brief Outputs log constant strings of the specified **domain**, **tag**, and **level**. The tag and string length
 * must be specified. Unlike **OH_LOG_PrintMsg**, this API allows strings without terminators.
 *
 * @param type Log type. The type for third-party applications is defined by **LOG_APP**.
 * @param level Log level. The value can be **LOG_DEBUG**, **LOG_INFO**, **LOG_WARN**, **LOG_ERROR**, and **LOG_FATAL**.
 * @param domain Service domain. Its value is a hexadecimal integer ranging from 0x0 to 0xFFFF. If the value exceeds
 *     the range, logs cannot be printed.
 * @param tag Log tag, which is a string used to identify the class, file, or service. A tag can contain a maximum of
 *     31 bytes. If a tag exceeds this limit, it will be truncated. Chinese characters are not recommended because
 *     garbled characters or alignment problems may occur.
 * @param tagLen Length of the tag.
 * @param message Constant log string.
 * @param messageLen Length of the constant string, which is less than 3500 characters.
 * @return **0** or a larger value if the operation is successful; a value smaller than **0** otherwise.
 *     <br>Possible failure causes: The **LogLevel** passed in is lower than the allowed log level; the **domain** is
 *     out of range; the **tag** is a null pointer; the CPU is overloaded; the memory is insufficient; the number of
 *     logs on the device is too large.
 * @since 18
 */
int OH_LOG_PrintMsgByLen(LogType type, LogLevel level, unsigned int domain, const char *tag, size_t tagLen,
    const char *message, size_t messageLen);

/**
 * @brief Outputs logs of the specified **type**, **level**, **domain**, **tag**, and variables determined by the
 * format specifier and privacy identifier in the printf format. The variables are of the **va_list** type.
 *
 * @param type Log type. The type for third-party applications is defined by **LOG_APP**.
 * @param level Log level. The value can be **LOG_DEBUG**, **LOG_INFO**, **LOG_WARN**, **LOG_ERROR**, and **LOG_FATAL**.
 * @param domain Service domain. Its value is a hexadecimal integer ranging from 0x0 to 0xFFFF. If the value exceeds
 *     the range, logs cannot be printed.
 * @param tag Log tag, which is a string used to identify the class, file, or service. A tag can contain a maximum of
 *     31 bytes. If a tag exceeds this limit, it will be truncated. Chinese characters are not recommended because
 *     garbled characters or alignment problems may occur.
 * @param fmt Format string, which is an enhancement of a printf format string and supports the privacy identifier.
 *     Specifically, **{public}** or **{private}** is added between the % character and the format specifier in each
 *     parameter.
 * @param ap Parameter list of the **va_list** type that corresponds to the parameter type in the format string. The
 *     number and type of parameters must be mapped onto the identifier in the format string.
 * @return **0** or a larger value if the operation is successful; a value smaller than **0** otherwise.
 *     <br>Possible failure causes: The **LogLevel** passed in is lower than the allowed log level; the **domain** is
 *     out of range; the **tag** is a null pointer; the CPU is overloaded; the memory is insufficient; the number of
 *     logs on the device is too large.
 * @since 18
 */
int OH_LOG_VPrint(LogType type, LogLevel level, unsigned int domain, const char *tag, const char *fmt, va_list ap)
    __attribute__((__format__(os_log, 5, 0)));

/**
 * @brief Checks whether logs of the specified service domain, tag, and level can be printed.
 *
 * @param domain Service domain. Its value is a hexadecimal integer ranging from 0x0 to 0xFFFF. If the value exceeds
 *     the range, logs cannot be printed.
 * @param tag Log tag, which is a string used to identify the class, file, or service. A tag can contain a maximum of
 *     31 bytes. If a tag exceeds this limit, it will be truncated. Chinese characters are not recommended because
 *     garbled characters or alignment problems may occur.
 * @param level Log level. The value can be **LOG_DEBUG**, **LOG_INFO**, **LOG_WARN**, **LOG_ERROR**, and **LOG_FATAL**.
 * @return **true** if the specified logs can be output; **false** otherwise.
 * @since 8
 */
bool OH_LOG_IsLoggable(unsigned int domain, const char *tag, LogLevel level);

/**
 * @brief Outputs debug logs. This is a function-like macro.
 *
 * Before calling this function, define the log service domain and log tag. Generally, you need to define them at
 * the beginning of the source file. \n
 *
 * @param type Indicates the log type. The type for third-party applications is defined by {@link LOG_APP}.
 * @param fmt Indicates the format string, which is an enhancement of a printf format string and supports the
 * privacy identifier. Specifically, {public} or {private} is added between the % character and the format specifier
 * in each parameter. \n
 * @param ... Indicates a list of parameters. The number and type of parameters must map onto the format specifiers
 * in the format string.
 * @link OH_LOG_Print
 * @since 8
 */
#define OH_LOG_DEBUG(type, ...) ((void)OH_LOG_Print((type), LOG_DEBUG, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief Outputs informational logs. This is a function-like macro.
 *
 * Before calling this function, define the log service domain and log tag. Generally, you need to define them
 * at the beginning of the source file. \n
 *
 * @param type Indicates the log type. The type for third-party applications is defined by {@link LOG_APP}.
 * @param fmt Indicates the format string, which is an enhancement of a printf format string and supports the privacy
 * identifier. Specifically, {public} or {private} is added between the % character and the format specifier in
 * each parameter. \n
 * @param ... Indicates a list of parameters. The number and type of parameters must map onto the format specifiers
 * in the format string.
 * @link OH_LOG_Print
 * @since 8
 */
#define OH_LOG_INFO(type, ...) ((void)OH_LOG_Print((type), LOG_INFO, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief Outputs warning logs. This is a function-like macro.
 *
 * Before calling this function, define the log service domain and log tag. Generally, you need to define them
 * at the beginning of the source file. \n
 *
 * @param type Indicates the log type. The type for third-party applications is defined by {@link LOG_APP}.
 * @param fmt Indicates the format string, which is an enhancement of a printf format string and supports the
 * privacy identifier. Specifically, {public} or {private} is added between the % character and the format specifier
 * in each parameter. \n
 * @param ... Indicates a list of parameters. The number and type of parameters must map onto the format specifiers
 * in the format string.
 * @link OH_LOG_Print
 * @since 8
 */
#define OH_LOG_WARN(type, ...) ((void)OH_LOG_Print((type), LOG_WARN, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief Outputs error logs. This is a function-like macro.
 *
 * Before calling this function, define the log service domain and log tag. Generally, you need to define
 * them at the beginning of the source file. \n
 *
 * @param type Indicates the log type. The type for third-party applications is defined by {@link LOG_APP}.
 * @param fmt Indicates the format string, which is an enhancement of a printf format string and supports the privacy
 * identifier. Specifically, {public} or {private} is added between the % character and the format specifier in each
 * parameter. \n
 * @param ... Indicates a list of parameters. The number and type of parameters must map onto the format specifiers
 * in the format string.
 * @link OH_LOG_Print
 * @since 8
 */
#define OH_LOG_ERROR(type, ...) ((void)OH_LOG_Print((type), LOG_ERROR, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief Outputs fatal logs. This is a function-like macro.
 *
 * Before calling this function, define the log service domain and log tag. Generally, you need to define them at
 * the beginning of the source file. \n
 *
 * @param type Indicates the log type. The type for third-party applications is defined by {@link LOG_APP}.
 * @param fmt Indicates the format string, which is an enhancement of a printf format string and supports the privacy
 * identifier. Specifically, {public} or {private} is added between the % character and the format specifier in
 * each parameter. \n
 * @param ... Indicates a list of parameters. The number and type of parameters must map onto the format specifiers
 * in the format string.
 * @link OH_LOG_Print
 * @since 8
 */
#define OH_LOG_FATAL(type, ...) ((void)OH_LOG_Print((type), LOG_FATAL, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief Customizes the processing of HiLog logs in the callback.
 *
 * @param type Log type. The third-party application log type is {@link LOG_APP}.
 * @param level Log level. The value can be **LOG_DEBUG**, **LOG_INFO**, **LOG_WARN**, **LOG_ERROR**, and **LOG_FATAL**.
 * @param domain Service domain. Its value is a hexadecimal integer ranging from 0x0 to 0xFFFF. If the value exceeds
 *     the range, logs cannot be printed.
 * @param tag Indicates the log tag, which is a string used to identify the class, file, or service behavior.
 * @param msg Indicates the log message itself, which is a formatted log string.
 * @since 11
 */
typedef void (*LogCallback)(const LogType type, const LogLevel level, const unsigned int domain, const char *tag,
    const char *msg);

/**
 * @brief Registers a callback function. After this function is called, the custom callback can receive all HiLog logs
 * of the current process.
 * <br>Note that whether this API is called or not, it does not change the default log processing of the current
 * process.
 *
 * @param callback Custom callback function. If processing of logs is not needed, a null pointer can be transferred.
 * @since 11
 */
void OH_LOG_SetCallback(LogCallback callback);

/**
 * @brief Sets the minimum log level.
 * <br>NOTE:
 * <br>1. If the set log level is lower than the {@link global log level}, the setting does not take effect.
 * <br>2. This function does not take effect for debug applications.
 *
 * @param level Log level.
 * @since 15
 */
void OH_LOG_SetMinLogLevel(LogLevel level);

/**
 * @brief Sets the minimum log level of the current application process.
 * <br>You can configure different preference strategies using the **prefer** parameter. The **PREFER_CLOSE_LOG**
 * strategy has the same effect as the **OH_LOG_SetMinLogLevel()** function.
 * <br>Note: This function does not take effect for debug applications.
 *
 * @param level Log level.
 * @param prefer Preference strategy.
 * @since 21
 */
void OH_LOG_SetLogLevel(LogLevel level, PreferStrategy prefer);

#ifdef __cplusplus
}
#endif
/** @} */

#ifdef HILOG_RAWFORMAT
#include "hilog/log_inner.h"
#endif

#endif  // HIVIEWDFX_HILOG_C_H