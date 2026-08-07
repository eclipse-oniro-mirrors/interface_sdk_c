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
 * @brief 实现日志打印功能。
 *
 * 使用这些接口可以输出指定日志类型、业务领域、日志标签和日志级别的日志。
 *
 * @since 8
 */

/**
 * @file log.h
 *
 * @brief 定义HiLog模块的日志功能。
 *
 * 在输出日志之前，先定义日志所属业务领域、日志标签，然后按照日志类型、日志级别选择对应接口，并指定隐私标识符。 \n
 * <ul><li>业务领域： 用于标识服务的子系统或模块，其值为0x0到0xFFFF的十六进制整数。 \n
 * <li>日志标签：字符串常量，用于标识调用所在的类或者业务。</li> \n
 * <li>日志级别：<b>DEBUG</b>、<b>INFO</b>、<b>WARN</b>、<b>ERROR</b>和<b>FATAL</b></li> \n
 * <li>参数格式：以%字符开头的printf格式字符串，包括格式说明符和可变参数。</li> \n
 * <li>隐私参数标识：在每个参数中%字符和格式说明符之间增加{public}、{private}标识。请注意，每个参数都有一个隐私标识符。
 * 如果未添加隐私标识符，缺省为隐私。</li></ul> \n
 *
 * 示例代码：\n
 * 定义业务领域和日志标签：\n
 *     #include <hilog/log.h>\n
 *     #define LOG_DOMAIN 0x0201\n
 *     #define LOG_TAG "MY_TAG"\n
 * 输出日志：\n
 *     HILOG_WARN({@link LOG_APP}, "Failed to visit %{private}s, reason:%{public}d.", url, errno);\n
 * 输出结果：\n
 *     05-06 15:01:06.870 1051 1051 W 0201/MY_TAG: Failed to visit <private>, reason:503.\n
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

/**
 * @brief 定义日志文件的业务领域。
 *
 * 业务领域用于标识服务的子系统和模块，其值为0x0到0xFFFF的十六进制整数。如果值超出范围，其有效位将被自动截断。 \n
 *
 * @since 8
 */
#ifndef LOG_DOMAIN
#define LOG_DOMAIN 0
#endif

/**
 * @brief 定义用于标识类、文件或服务的字符串常量。
 *
 * @since 8
 */
#ifndef LOG_TAG
#define LOG_TAG NULL
#endif

/**
 * @brief 枚举日志类型。
 *
 * 目前可用的是<b>LOG_APP</b>。 \n
 *
 * @since 8
 */
typedef enum {
    /** 第三方应用日志 */
    LOG_APP = 0,
} LogType;

/**
 * @brief 日志级别枚举。
 *
 * 建议根据各自的适用场景选择日志级别：\n
 * <ul><li><b>DEBUG</b>：用于调试，商业发布版本中禁用</li> \n
 * <li><b>INFO</b>：用于记录重要系统运行状态和关键进程中的步骤</li> \n
 * <li><b>WARN</b>：用于记录对用户体验影响不大且可自动恢复的意外异常。通常在检测和捕获此类异常时输出此级别的日志。</li> \n
 * <li><b>ERROR</b>：用于记录影响用户体验且无法自动恢复的故障</li>\n
 * <li><b>FATAL</b>：用于记录严重影响了用户体验且不应发生的重大异常。</li></ul> \n
 *
 * @since 8
 */
typedef enum {
    /** DEBUG日志级别，使用{@link OH_LOG_DEBUG}接口打印。 */
    LOG_DEBUG = 3,
    /** INFO日志级别，使用{@link OH_LOG_INFO}接口打印。 */
    LOG_INFO = 4,
    /** WARN日志级别，使用{@link OH_LOG_WARN}接口打印。 */
    LOG_WARN = 5,
    /** ERROR日志级别，使用{@link OH_LOG_ERROR}接口打印。 */
    LOG_ERROR = 6,
    /** FATAL日志级别，使用{@link OH_LOG_FATAL}接口打印。 */
    LOG_FATAL = 7,
} LogLevel;

/**
 * @brief 枚举在 {@link OH_LOG_SetLogLevel} 中使用的偏好策略。
 *
 * 建议根据各自的适用场景选择偏好策略。
 *
 * @since 21
 */
typedef enum {
    /** 清除日志级别设置
     */
    UNSET_LOGLEVEL = 0,
    /**
     * 实际生效的最低日志级别是新设置的级别和系统控制的最低级别两个值的较大值。
     * 等效于调用OH_LOG_SetMinLogLevel。
     */
    PREFER_CLOSE_LOG = 1,
    /**
     * 实际生效的最低日志级别是新设置的级别和系统控制的最低级别两个值的较小值。
     */
    PREFER_OPEN_LOG = 2,
} PreferStrategy;

/**
 * @brief 输出日志。
 *
 * 使用此接口根据指定的日志类型、日志级别、业务领域、日志标签以及printf格式中格式说明符和隐私标识符确定的可变参数来输出日志。
 *
 * @param type 日志类型，三方应用日志类型为{@link LOG_APP}。
 * @param level 日志级别，日志级别包括<b>LOG_DEBUG</b>, <b>LOG_INFO</b>, <b>LOG_WARN</b>, <b>LOG_ERROR</b>, and <b>LOG_FATAL</b>.
 * @param domain 日志业务领域，16进制整数，范围0x0~0xFFFF。
 * @param tag 日志标签，这是一个用于标识调用所在的类或者业务的字符串。
 * @param fmt 格式化字符串，基于类printf格式的增强，支持隐私参数标识，即在格式字符串每个参数中'%'符号后类型前
 * 增加{public}、{private}标识。 \n
 * @param ... 参数列表，参数数目、参数类型必须与格式字符串中的标识一一对应。
 * @return 大于等于<b>0</b>表示成功；小于<b>0</b>表示失败。
 * @since 8
 */
int OH_LOG_Print(LogType type, LogLevel level, unsigned int domain, const char *tag, const char *fmt, ...)
    __attribute__((__format__(os_log, 5, 6)));

/**
 * @brief 输出日志。
 *
 * 使用此接口根据指定的日志类型、日志级别、业务领域、日志标签以及printf格式中格式说明符和隐私标识符确定的va_list
 * 而不是可变参数来输出日志。
 *
 * @param type 日志类型，三方应用日志类型为{@link LOG_APP}。
 * @param level 日志级别，日志级别包括<b>LOG_DEBUG</b>, <b>LOG_INFO</b>, <b>LOG_WARN</b>, <b>LOG_ERROR</b>, and <b>LOG_FATAL</b>.
 * @param domain 日志业务领域，16进制整数，范围0x0~0xFFFF。
 * @param tag 日志标签，这是一个用于标识调用所在的类或者业务的字符串。
 * @param message 日志字符串。
 * @return 大于等于<b>0</b>表示成功；小于<b>0</b>表示失败。
 * @since 18
 */
int OH_LOG_PrintMsg(LogType type, LogLevel level, unsigned int domain, const char *tag, const char *message);
 
/**
 * @brief 输出日志。
 *
 * 使用此接口根据指定的日志类型、日志级别、业务领域、日志标签、消息文本和消息长度输出日志。
 *
 * @param type 日志类型，三方应用日志类型为{@link LOG_APP}。
 * @param level 日志级别，日志级别包括<b>LOG_DEBUG</b>, <b>LOG_INFO</b>, <b>LOG_WARN</b>, <b>LOG_ERROR</b>, and <b>LOG_FATAL</b>.
 * @param domain 日志业务领域，16进制整数，范围0x0~0xFFFF。
 * @param tag 日志标签，这是一个用于标识调用所在的类或者业务的字符串。
 * @param tagLen 标签长度。
 * @param message 日志字符串。
 * @param messageLen 日志字符串长度。
 * @return 大于等于<b>0</b>表示成功；小于<b>0</b>表示失败。
 * @since 18
 */
int OH_LOG_PrintMsgByLen(LogType type, LogLevel level, unsigned int domain, const char *tag, size_t tagLen,
    const char *message, size_t messageLen);
 
/**
 * @brief 输出日志。
 *
 * 使用此接口根据指定的日志类型、日志级别、业务领域、日志标签以及printf格式中格式说明符和隐私标识符确定的va_list
 * 而不是可变参数来输出日志。
 *
 * @param type 日志类型，三方应用日志类型为{@link LOG_APP}。
 * @param level 日志级别，日志级别包括<b>LOG_DEBUG</b>, <b>LOG_INFO</b>, <b>LOG_WARN</b>, <b>LOG_ERROR</b>, and <b>LOG_FATAL</b>。
 * @param domain 日志业务领域，16进制整数，范围0x0~0xFFFF。
 * @param tag 日志标签，这是一个用于标识调用所在的类或者业务的字符串。
 * @param fmt 格式化字符串，基于类printf格式的增强，支持隐私参数标识，即在格式字符串每个参数中符号后类型前增加{public}、{private}标识。 \n
 * @param ap 参数列表。参数数目、参数类型必须与格式字符串中的格式说明符对应。
 * @return 大于等于<b>0</b>表示成功；小于<b>0</b>表示失败。
 * @since 18
 */
int OH_LOG_VPrint(LogType type, LogLevel level, unsigned int domain, const char *tag, const char *fmt, va_list ap)
    __attribute__((__format__(os_log, 5, 0)));

/**
 * @brief 检查指定业务领域、TAG、级别的日志是否可以打印。
 *
 * @param domain 日志业务领域，16进制整数，范围0x0~0xFFFF。
 * @param tag 日志标签，这是一个用于标识调用所在的类或者业务的字符串。
 * @param level 日志级别，日志级别包括<b>LOG_DEBUG</b>, <b>LOG_INFO</b>, <b>LOG_WARN</b>, <b>LOG_ERROR</b>, and <b>LOG_FATAL</b>.
 * @return 如果指定的日志可以输出，返回<b>true</b>；否则返回<b>false</b>。
 * @since 8
 */
bool OH_LOG_IsLoggable(unsigned int domain, const char *tag, LogLevel level);

/**
 * @brief DEBUG级别写日志，宏封装接口。
 *
 * 在调用此函数之前，需要先定义LOG_DOMAIN和LOG_TAG。通常，一般在源文件起始处统一定义一次。 \n
 *
 * @param type 日志类型，三方应用日志类型为{@link LOG_APP}。
 * @param fmt 格式化字符串，基于类printf格式的增强，支持隐私参数标识，即在格式字符串每个参数中符号后类型前增加{public}、{private}标识。 \n
 * @param ... 与格式字符串里参数类型对应的参数列表，参数数目、参数类型必须与格式字符串中的标识一一对应。
 * @see OH_LOG_Print
 * @since 8
 */
#define OH_LOG_DEBUG(type, ...) ((void)OH_LOG_Print((type), LOG_DEBUG, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief INFO级别写日志，宏封装接口。
 *
 * 使用时需要先定义LOG_DOMAIN和LOG_TAG，一般在源文件起始处统一定义一次。 \n
 *
 * @param type 日志类型，三方应用日志类型为{@link LOG_APP}。
 * @param fmt 格式化字符串，基于类printf格式的增强，支持隐私参数标识，即在格式字符串每个参数中符号后类型前增加{public}、{private}标识。 \n
 * @param ... 与格式字符串里参数类型对应的参数列表，参数数目、参数类型必须与格式字符串中的标识一一对应。
 * @see OH_LOG_Print
 * @since 8
 */
#define OH_LOG_INFO(type, ...) ((void)OH_LOG_Print((type), LOG_INFO, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief WARN级别写日志，宏封装接口。
 *
 * 使用时需要先定义LOG_DOMAIN和LOG_TAG，一般在源文件起始处统一定义一次。 \n
 *
 * @param type 日志类型，三方应用日志类型为{@link LOG_APP}。
 * @param fmt 格式化字符串，基于类printf格式的增强，支持隐私参数标识，即在格式字符串每个参数中符号后类型前增加{public}、{private}标识。 \n
 * @param ... 与格式字符串里参数类型对应的参数列表，参数数目、参数类型必须与格式字符串中的标识一一对应。
 * @see OH_LOG_Print
 * @since 8
 */
#define OH_LOG_WARN(type, ...) ((void)OH_LOG_Print((type), LOG_WARN, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief ERROR级别写日志，宏封装接口。
 *
 * 使用时需要先定义LOG_DOMAIN和LOG_TAG，一般在源文件起始处统一定义一次。 \n
 *
 * @param type 日志类型，三方应用日志类型为{@link LOG_APP}。
 * @param fmt 格式化字符串，基于类printf格式的增强，支持隐私参数标识，即在格式字符串每个参数中符号后类型前增加{public}、{private}标识。 \n
 * @param ... 与格式字符串里参数类型对应的参数列表，参数数目、参数类型必须与格式字符串中的标识一一对应。
 * @see OH_LOG_Print
 * @since 8
 */
#define OH_LOG_ERROR(type, ...) ((void)OH_LOG_Print((type), LOG_ERROR, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief FATAL级别写日志，宏封装接口。
 *
 * 使用时需要先定义LOG_DOMAIN和LOG_TAG，一般在源文件起始处统一定义一次。 \n
 *
 * @param type 日志类型，三方应用日志类型为{@link LOG_APP}。
 * @param fmt 格式化字符串，基于类printf格式的增强，支持隐私参数标识，即在格式字符串每个参数中符号后类型前增加{public}、{private}标识。 \n
 * @param ... 与格式字符串里参数类型对应的参数列表，参数数目、参数类型必须与格式字符串中的标识一一对应。
 * @see OH_LOG_Print
 * @since 8
 */
#define OH_LOG_FATAL(type, ...) ((void)OH_LOG_Print((type), LOG_FATAL, LOG_DOMAIN, LOG_TAG, __VA_ARGS__))

/**
 * @brief 函数指针，开发者自定义回调函数内容，在回调函数中，可自行对hilog日志进行处理。
 *
 * @param type 日志类型，三方应用日志类型为{@link LOG_APP}。
 * @param level 日志级别，日志级别包括<b>LOG_DEBUG</b>, <b>LOG_INFO</b>, <b>LOG_WARN</b>, <b>LOG_ERROR</b>, and <b>LOG_FATAL</b>。
 * @param domain 日志业务领域，16进制整数，范围0x0~0xFFFF。
 * @param tag 日志标签，这是一个用于标识调用所在的类或者业务的字符串。
 * @param msg 日志内容，格式化之后的日志字符串。
 * @since 11
 */
typedef void (*LogCallback)(const LogType type, const LogLevel level, const unsigned int domain, const char *tag,
    const char *msg);

/**
 * @brief 注册函数。
 *
 * 调用此函数后，用户实现的回调函数可以接收当前进程的所有hilog日志。
 * 请注意，无论是否调用该接口，它都不会更改当前进程的hilog日志的默认行为。 \n
 *
 * @param callback 用户实现的回调函数。如果不需要处理hilog日志，可以传输空指针。
 * @since 11
 */
void OH_LOG_SetCallback(LogCallback callback);

/**
 * @brief 设置应用日志打印的最低日志级别。
 *
 * @param level 日志级别。
 * @since 15
 */
void OH_LOG_SetMinLogLevel(LogLevel level);

/**
 * @brief 设置当前应用程序进程的最低日志级别。
 *
 * @param level 日志级别。
 * @param prefer 偏好策略。参见 {@link PreferStrategy}。
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
