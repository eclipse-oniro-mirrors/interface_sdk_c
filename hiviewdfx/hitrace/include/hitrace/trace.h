/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup HiTrace
 * @{
 *
 * @brief hiTraceMeter provides APIs for system performance trace.
 *
 * You can call the APIs provided by hiTraceMeter in your own service logic to effectively
 * track service processes and check the system performance.
 *
 * @brief hitraceChain provides APIs for cross-thread and cross-process distributed tracing.
 * hiTraceChain generates a unique chain ID for a service process and passes it to various information (including
 * application events, system events, and logs) specific to the service process.
 * During debugging and fault locating, you can use the unique chain ID to quickly correlate various information
 * related to the service process.
 *
 * @since 10
 */

/**
 * @file trace.h
 *
 * @brief Defines APIs of the **HiTraceMeter** and **HiTraceChain** modules for performance tracing and distributed
 * tracing.
 * The vertical bar (\|) is used as the separator in user-mode trace format. Therefore, the string parameters
 * passed by the HiTraceMeter APIs must exclude this character to avoid trace parsing exceptions.
 * The maximum length of a user-mode trace is 512 characters. Excess characters will be truncated.
 *
 * @kit PerformanceAnalysisKit
 * @library libhitrace_ndk.z.so
 * @syscap SystemCapability.HiviewDFX.HiTrace
 * @since 10
 */

#ifndef HIVIEWDFX_HITRACE_H
#define HIVIEWDFX_HITRACE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates whether a **HiTraceId** instance is valid.
 *
 * @since 12
 */
typedef enum HiTraceId_Valid {
    /**
     * @brief Invalid **HiTraceId**.
     *
     * @since 12
     */
    HITRACE_ID_INVALID = 0,

    /**
     * @brief Valid **HiTraceId**.
     *
     * @since 12
     */
    HITRACE_ID_VALID = 1
} HiTraceId_Valid;

/**
 * @brief Enumerates the HiTrace versions.
 *
 * @since 12
 */
typedef enum HiTrace_Version {
    /**
     * @brief Version 1.
     *
     * @since 12
     */
    HITRACE_VER_1 = 0
} HiTrace_Version;

/**
 * @brief Enumerates the HiTrace flags.
 *
 * @since 12
 */
typedef enum HiTrace_Flag {
    /**
     * @brief Default flag.
     *
     * @since 12
     */
    HITRACE_FLAG_DEFAULT = 0,

    /**
     * @brief Asynchronous call flag.
     * When this flag is set, both synchronous and asynchronous calls are traced. By default, only synchronous
     * calls are traced.
     *
     * @since 12
     */
    HITRACE_FLAG_INCLUDE_ASYNC = 1 << 0,

    /**
     * @brief No span flag.
     * When this flag is set, no span information is created. By default, span information is created.
     *
     * @since 12
     */
    HITRACE_FLAG_DONOT_CREATE_SPAN = 1 << 1,

    /**
     * @brief Trace point flag.
     * When this flag is set in the debugging scenario, the HiLog logs about the trace point are printed when the
     * {@link OH_HiTrace_Tracepoint} API is called. By default, the HiLog logs about the trace point are not printed.
     *
     * @since 12
     */
    HITRACE_FLAG_TP_INFO = 1 << 2,

    /**
     * @brief No begin and end flag.
     * When this flag is set in the debugging scenario, the HiLog logs about the start and end of tracing are
     * printed when the {@link OH_HiTrace_BeginChain} and {@link OH_HiTrace_EndChain} APIs are called. By default, the
     * HiLog logs about the start and end of tracing are not printed.
     *
     * @since 12
     */
    HITRACE_FLAG_NO_BE_INFO = 1 << 3,

    /**
     * @brief Log association flag.
     * When this flag is set, the **HiTraceId** information is not added to the HiLog logs. By default, the **
     * HiTraceId** information is added to the HiLog logs.
     *
     * @since 12
     */
    HITRACE_FLAG_DONOT_ENABLE_LOG = 1 << 4,

    /**
     * @brief Failure trigger flag. This is a reserved flag.
     *
     * @since 12
     */
    HITRACE_FLAG_FAULT_TRIGGER = 1 << 5,

    /**
     * @brief Device-to-device trace point flag. It is a subset of {@link HITRACE_FLAG_TP_INFO}, which is used in
     * debugging scenarios.
     * When the {@link HITRACE_FLAG_TP_INFO} flag is set, the {@link HITRACE_FLAG_D2D_TP_INFO} flag does not take
     * effect.
     * When the {@link HITRACE_FLAG_TP_INFO} flag is not set, set the {@link HITRACE_FLAG_D2D_TP_INFO} flag. In
     * this case, when the information tracing API {@link OH_HiTrace_Tracepoint} is called, the HiLog of the tracing
     * point information is printed only when the **mode** parameter is set to {@link HITRACE_CM_DEVICE}.
     *
     * @since 12
     */
    HITRACE_FLAG_D2D_TP_INFO = 1 << 6
} HiTrace_Flag;

/**
 * @brief Enumerates the trace point types.
 *
 * @since 12
 */
typedef enum HiTrace_Tracepoint_Type {
    /**
     * @brief CS trace point.
     *
     * @since 12
     */
    HITRACE_TP_CS = 0,

    /**
     * @brief CR trace point.
     *
     * @since 12
     */
    HITRACE_TP_CR = 1,

    /**
     * @brief SS trace point.
     *
     * @since 12
     */
    HITRACE_TP_SS = 2,

    /**
     * @brief SR trace point.
     *
     * @since 12
     */
    HITRACE_TP_SR = 3,

    /**
     * @brief General type, which identifies the trace points except **HITRACE_TP_CS**, **HITRACE_TP_CR**, **
     * HITRACE_TP_SS**, and **HITRACE_TP_SR**.
     *
     * @since 12
     */
    HITRACE_TP_GENERAL = 4
} HiTrace_Tracepoint_Type;

/**
 * @brief Enumerates the trace communication types.
 *
 * @since 12
 */
typedef enum HiTrace_Communication_Mode {
    /**
     * @brief Default communication.
     *
     * @since 12
     */
    HITRACE_CM_DEFAULT = 0,

    /**
     * @brief Inter-thread communication.
     *
     * @since 12
     */
    HITRACE_CM_THREAD = 1,

    /**
     * @brief Inter-process communication (IPC).
     *
     * @since 12
     */
    HITRACE_CM_PROCESS = 2,

    /**
     * @brief Inter-device communication.
     *
     * @since 12
     */
    HITRACE_CM_DEVICE = 3
} HiTrace_Communication_Mode;

/**
 * @brief Enumerates the HiTrace output levels. The trace output level lower than the threshold does not take effect.
 * The threshold for the log version is {@link HITRACE_LEVEL_INFO}, and that for the no-log version is
 * {@link HITRACE_LEVEL_COMMERCIAL}.
 *
 * @since 19
 */
typedef enum HiTrace_Output_Level {
    /**
     * @brief Level used only for debugging, which has the lowest priority.
     *
     * @since 19
     */
    HITRACE_LEVEL_DEBUG = 0,

    /**
     * @brief Level for the log version.
     *
     * @since 19
     */
    HITRACE_LEVEL_INFO = 1,

    /**
     * @brief Level for the log version, which has a higher priority than **INFO**.
     *
     * @since 19
     */
    HITRACE_LEVEL_CRITICAL = 2,

    /**
     * @brief Level for the nolog version, which has the highest priority.
     *
     * @since 19
     */
    HITRACE_LEVEL_COMMERCIAL = 3,

    /**
     * @brief The maximum output level.
     *
     * @since 19
     */
    HITRACE_LEVEL_MAX = HITRACE_LEVEL_COMMERCIAL
} HiTrace_Output_Level;

/**
 * @brief Defines a **HiTraceId** instance.
 *
 * @since 12
 */
typedef struct HiTraceId {
#if __BYTE_ORDER == __LITTLE_ENDIAN
    /**
     * Whether a **HiTraceId** instance is valid.
     * @since 12
     */
    uint64_t valid : 1;
    /**
     * Version number of **HiTraceId**.
     * @since 12
     */
    uint64_t ver : 3;
    /**
     * Trace chain ID of **HiTraceId**.
     * @since 12
     */
    uint64_t chainId : 60;
    /**
     * Trace flag of **HiTraceId**.
     * @since 12
     */
    uint64_t flags : 12;
    /**
     * Span ID of **HiTraceId**.
     * @since 12
     */
    uint64_t spanId : 26;
    /**
     * Parent span ID of **HiTraceId**.
     * @since 12
     */
    uint64_t parentSpanId : 26;
#elif __BYTE_ORDER == __BIG_ENDIAN
    /**
     * Trace chain ID of **HiTraceId**.
     * @since 12
     */
    uint64_t chainId : 60;
    /**
     * Version number of **HiTraceId**.
     * @since 12
     */
    uint64_t ver : 3;
    /**
     * Whether a **HiTraceId** instance is valid.
     * @since 12
     */
    uint64_t valid : 1;
    /**
     * Parent span ID of **HiTraceId**.
     * @since 12
     */
    uint64_t parentSpanId : 26;
    /**
     * Span ID of **HiTraceId**.
     * @since 12
     */
    uint64_t spanId : 26;
    /**
     * Trace flag of **HiTraceId**.
     * @since 12
     */
    uint64_t flags : 12;
#else
#error "ERROR: No BIG_LITTLE_ENDIAN defines."
#endif
} HiTraceId;

/**
 * @brief Defines a callback to listen for whether the trace capture is enabled.
 *
 * @param traceStatus Whether the trace capture is enabled for the current application.
 *     The value **true** indicates that the trace capture is enabled, and **false** indicates the opposite.
 * @since 22
 */
typedef void (*OH_HiTrace_TraceEventListener)(bool traceStatus);

/**
 * @brief Starts tracing.
 * If the current thread's TLS does not contain a valid HiTrace ID, this function generates one, stores it in TLS,
 * and returns it.
 * If the current thread's TLS already contains a valid HiTrace ID, this function does not start tracing and
 * returns an invalid HiTrace ID with all property values being 0.
 *
 * @param name Name of the traced service.
 * @param flags Trace flags. For details, see {@link HiTrace_Flag}.
 * @return The {@link HiTraceId} struct.
 * @since 12
 */
HiTraceId OH_HiTrace_BeginChain(const char *name, int flags);

/**
 * @brief Stops tracing.
 * Stops tracing and sets the HiTrace ID in the TLS of the current thread to invalid.
 *
 * @since 12
 */
void OH_HiTrace_EndChain();

/**
 * @brief
 * Obtains the {@link HiTraceId} in the TLS of the current thread.
 *
 * @return The {@link HiTraceId} struct.
 * @since 12
 */
HiTraceId OH_HiTrace_GetId();

/**
 * @brief
 * Sets the given {@link HiTraceId} to the TLS of the current thread. If the input parameter is invalid, no
 * operation is performed.
 *
 * @param id {@link HiTraceId} to set.
 * @since 12
 */
void OH_HiTrace_SetId(const HiTraceId *id);

/**
 * @brief
 * Sets the {@link HiTraceId} in the TLS of the current thread to invalid.
 *
 * @since 12
 */
void OH_HiTrace_ClearId(void);

/**
 * @brief Creates a trace span.
 * Creates a {@link HiTraceId}, uses the **chainId** and **spanId** in the TLS of the current thread to initialize
 * its **chainId** and **parentSpanId**, and generates a new **spanId** for it.
 *
 * @return The {@link HiTraceId} struct.
 * @since 12
 */
HiTraceId OH_HiTrace_CreateSpan(void);

/**
 * @brief Adds a trace point for the HiTraceMeter logging.
 * When **type** is set to {@link HITRACE_TP_CS} (client sending) or {@link HITRACE_TP_SR} (server receiving), the
 * synchronous HiTraceMeter logging starts. When type is set to {@link HITRACE_TP_CR} (client receiving) or
 * {@link HITRACE_TP_SS} (server sending), the synchronous HiTraceMeter logging ends. When **type** is set to
 * {@link HITRACE_TP_GENERAL}, HiTraceMeter logging is not performed.
 * The trace points must be used in pairs: {@link HITRACE_TP_CS} with {@link HITRACE_TP_CR}, and
 * {@link HITRACE_TP_SR} with {@link HITRACE_TP_SS}. Otherwise, the start and end trace points of HiTraceMeter cannot
 * match each other.
 *
 * @param mode Trace communication mode. For details, see {@link HiTrace_Communication_Mode}.
 * @param type Trace information type. For details, see {@link HiTrace_Tracepoint_Type}.
 * @param id {@link HiTraceId} for implementing trace points.
 * @param fmt Formatted string of the trace description information passed by the HiTraceMeter logging.
 * @since 12
 */
void OH_HiTrace_Tracepoint(
    HiTrace_Communication_Mode mode, HiTrace_Tracepoint_Type type, const HiTraceId *id, const char *fmt, ...);

/**
 * @brief Initializes a {@link HiTraceId}.
 *
 * @param id {@link HiTraceId} to initialize.
 * @since 12
 */
void OH_HiTrace_InitId(HiTraceId *id);

/**
 * @brief Creates a {@link HiTraceId} based on a byte array.
 *
 * @param id {@link HiTraceId} to create.
 * @param pIdArray Byte array.
 * @param len Length of the byte array.
 * @since 12
 */
void OH_HiTrace_IdFromBytes(HiTraceId *id, const uint8_t *pIdArray, int len);

/**
 * @brief Checks whether a {@link HiTraceId} is valid.
 *
 * @param id {@link HiTraceId} to check.
 * @return The value **true** indicates that {@link HiTraceId} is valid, and **false** indicates the opposite.
 * @since 12
 */
bool OH_HiTrace_IsIdValid(const HiTraceId *id);

/**
 * @brief Checks whether a trace flag is enabled for a {@link HiTraceId}.
 *
 * @param id {@link HiTraceId} to check.
 * @param flag Trace flag. For details, see {@link HiTrace_Flag}.
 * @return The value **true** indicates that the flag is enabled for the {@link HiTraceId}, and **false** indicates the
 *     opposite.
 * @since 12
 */
bool OH_HiTrace_IsFlagEnabled(const HiTraceId *id, HiTrace_Flag flag);

/**
 * @brief Enables the trace flag specified in {@link HiTraceId}.
 *
 * @param id {@link HiTraceId} for which the trace flag is enabled.
 * @param flag Trace flag. For details, see {@link HiTrace_Flag}.
 * @since 12
 */
void OH_HiTrace_EnableFlag(const HiTraceId *id, HiTrace_Flag flag);

/**
 * @brief Obtains the trace flag set in {@link HiTraceId}.
 *
 * @param id {@link HiTraceId} for which the trace flag is obtained.
 * @return Trace flag set in {@link HiTraceId}.
 * @since 12
 */
int OH_HiTrace_GetFlags(const HiTraceId *id);

/**
 * @brief Sets the trace flag to {@link HiTraceId}.
 *
 * @param id {@link HiTraceId} to which the trace flag is set.
 * @param flags Trace flag. For details, see {@link HiTrace_Flag}.
 * @since 12
 */
void OH_HiTrace_SetFlags(HiTraceId *id, int flags);

/**
 * @brief Obtains the trace chain ID from {@link HiTraceId}.
 *
 * @param id {@link HiTraceId} for which the trace chain ID is obtained.
 * @return Trace chain ID.
 * @since 12
 */
uint64_t OH_HiTrace_GetChainId(const HiTraceId *id);

/**
 * @brief Sets the trace chain ID to {@link HiTraceId}.
 *
 * @param id {@link HiTraceId} to which the trace chain ID is to be set.
 * @param chainId Trace chain ID to set.
 * @since 12
 */
void OH_HiTrace_SetChainId(HiTraceId *id, uint64_t chainId);

/**
 * @brief Obtains the span ID from the current {@link HiTraceId}.
 *
 * @param id {@link HiTraceId} for which span ID is obtained.
 * @return Span ID set in {@link HiTraceId}.
 * @since 12
 */
uint64_t OH_HiTrace_GetSpanId(const HiTraceId *id);

/**
 * @brief Sets the span ID to {@link HiTraceId}.
 *
 * @param id {@link HiTraceId} to which the span ID is set.
 * @param spanId Span ID to set.
 * @since 12
 */
void OH_HiTrace_SetSpanId(HiTraceId *id, uint64_t spanId);

/**
 * @brief Obtains the parent span ID from the current {@link HiTraceId}.
 *
 * @param id {@link HiTraceId} for which the parent span ID is obtained.
 * @return Parent span ID set in {@link HiTraceId}.
 * @since 12
 */
uint64_t OH_HiTrace_GetParentSpanId(const HiTraceId *id);

/**
 * @brief Sets the **parentSpanId** field in the {@link HiTraceId} struct.
 *
 * @param id {@link HiTraceId} to which the parent span ID is set.
 * @param parentSpanId Parent span ID to set.
 * @since 12
 */
void OH_HiTrace_SetParentSpanId(HiTraceId *id, uint64_t parentSpanId);

/**
 * @brief Converts a {@link HiTraceId} to a byte array for caching or communication.
 *
 * @param id {@link HiTraceId} to convert.
 * @param pIdArray Byte array.
 * @param len Length of the byte array.
 * @return Returns the length of the byte array after conversion.
 * @since 12
 */
int OH_HiTrace_IdToBytes(const HiTraceId* id, uint8_t* pIdArray, int len);

/**
 * @brief Marks the start of a synchronous trace.
 * The synchronous tracing APIs {@link OH_HiTrace_StartTrace} and {@link OH_HiTrace_FinishTrace} must be used in
 * pairs.
 * The {@link OH_HiTrace_StartTrace} and {@link OH_HiTrace_FinishTrace} function pairs can be nested. During
 * tracing and parsing, the stack data structure is used for matching.
 * Since API version 19, you are advised to use the {@link OH_HiTrace_StartTraceEx} API to specify the trace output
 * level.
 *
 * @param name Name of a synchronous trace.
 * @since 10
 */
void OH_HiTrace_StartTrace(const char *name);

/**
 * @brief Marks the end of a synchronous trace.
 * This function must be used together with {@link OH_HiTrace_StartTrace}. During trace parsing, this function
 * matches the latest {@link OH_HiTrace_StartTrace} in the implementation process.
 * Since API version 19, you are advised to use {@link OH_HiTrace_FinishTraceEx} to control trace output by level.
 *
 * @since 10
 */
void OH_HiTrace_FinishTrace(void);

/**
 * @brief Marks the start of an asynchronous trace.
 * This API is used to start tracing before an asynchronous operation. The start and end of an asynchronous trace
 * do not occur in sequence. Therefore, a unique task ID is required to identify them.
 * It must be used with {@link OH_HiTrace_FinishAsyncTrace} in pairs. The start and end identified by the same name
 * and task ID constitute an asynchronous trace task.
 * If multiple trace tasks with the same name need to be performed at the same time or a trace task needs to be
 * performed multiple times concurrently, different task IDs must be specified.
 * If the trace tasks with the same name are not performed at the same time, the same **taskId** can be used.
 * Since API version 19, you are advised to use {@link OH_HiTrace_StartAsyncTraceEx} to control trace output and
 * clustering by level.
 *
 * @param name Name of the asynchronous trace.
 * @param taskId ID of the asynchronous trace. The start and end of an asynchronous trace do not occur in sequence.
 *     Therefore, the start and end of an asynchronous trace need to be matched based on the task name and the unique
 *     task ID together.
 * @since 10
 */
void OH_HiTrace_StartAsyncTrace(const char *name, int32_t taskId);

/**
 * @brief Marks the end of an asynchronous trace.
 * This API is called in the callback function after an asynchronous trace is complete.
 * It is used with {@link OH_HiTrace_StartAsyncTrace} in pairs. The **name** and **taskId** must be the same as
 * those of the **OH_HiTrace_StartAsyncTrace** API.
 * Since API version 19, you are advised to use {@link OH_HiTrace_FinishAsyncTraceEx} to control trace output by
 * level.
 *
 * @param name Name of the asynchronous trace.
 * @param taskId ID of the asynchronous trace. The start and end of an asynchronous trace do not occur in sequence.
 *     Therefore, the start and end of an asynchronous trace need to be matched based on the task name and the unique
 *     task ID together.
 * @since 10
 */
void OH_HiTrace_FinishAsyncTrace(const char *name, int32_t taskId);

/**
 * @brief Traces the value change of an integer variable based on its name.
 * This API can be executed for multiple times to trace the value change of a given integer variable at different
 * time points.
 * Since API version 19, you are advised to use {@link OH_HiTrace_CountTraceEx} to control the trace output by
 * level.
 *
 * @param name Name of the integer variable. It does not need to be the same as the real variable name.
 * @param count Integer value.
 * @since 10
 */
void OH_HiTrace_CountTrace(const char *name, int64_t count);

/**
 * @brief Marks the start of a synchronous trace task with the trace output level specified.
 * The synchronous tracing APIs {@link OH_HiTrace_StartTraceEx} and {@link OH_HiTrace_FinishTraceEx} must be used
 * in pairs.
 * The {@link OH_HiTrace_StartTraceEx} and {@link OH_HiTrace_FinishTraceEx} function pairs can be nested. During
 * tracing and parsing, the stack data structure is used for matching.
 *
 * @param level Trace output level.
 * @param name Name of a synchronous trace.
 * @param customArgs Key-value pair. Use commas (,) to separate multiple key-value pairs, for example, **"key1=value1,
 *     key2=value2"**.
 * @since 19
 */
void OH_HiTrace_StartTraceEx(HiTrace_Output_Level level, const char* name, const char* customArgs);

/**
 * @brief Marks the end of a synchronous trace task with the trace output level specified.
 * It must be used in pair with {@link OH_HiTrace_StartTraceEx}. The **level** parameter must be the same as that
 * of {@link OH_HiTrace_StartTraceEx}.
 * During trace data parsing, this function matches the latest {@link OH_HiTrace_StartTraceEx} in the
 * implementation process.
 *
 * @param level Trace output level.
 * @since 19
 */
void OH_HiTrace_FinishTraceEx(HiTrace_Output_Level level);

/**
 * @brief Marks the start of an asynchronous trace task with the trace output level specified.
 * This API is used to start tracing before an asynchronous operation. The start and end of an asynchronous trace
 * do not occur in sequence. Therefore, a unique task ID is required to identify them.
 * It is used with {@link OH_HiTrace_FinishAsyncTraceEx} in pairs. The start and end identified by the same name
 * and task ID constitute an asynchronous trace task.
 * If multiple trace tasks with the same name need to be performed at the same time or a trace task needs to be
 * performed multiple times concurrently, different task IDs must be specified.
 * If the trace tasks with the same name are not performed at the same time, the same **taskId** can be used.
 * Task IDs of different processes does not interfere with each other.
 *
 * @param level Trace output level.
 * @param name Name of the asynchronous trace.
 * @param taskId ID of the asynchronous trace.
 * @param customCategory Custom category name, which is used to collect asynchronous trace data of the same type.
 * @param customArgs Key-value pair. Use commas (,) to separate multiple key-value pairs, for example, **"key1=value1,
 *     key2=value2"**.
 * @since 19
 */
void OH_HiTrace_StartAsyncTraceEx(HiTrace_Output_Level level, const char* name, int32_t taskId,
    const char* customCategory, const char* customArgs);

/**
 * @brief Marks the end of an asynchronous trace task with the trace output level specified.
 * This API is used to stop tracing after an asynchronous operation is complete, for example, in a callback
 * function.
 * It is used with {@link OH_HiTrace_StartAsyncTraceEx} in pairs. The **level**, **name**, and **taskId**
 * parameters must be the same as those of the **OH_HiTrace_StartAsyncTraceEx** API.
 *
 * @param level Trace output level.
 * @param name Name of the asynchronous trace.
 * @param taskId ID of the asynchronous trace.
 * @since 19
 */
void OH_HiTrace_FinishAsyncTraceEx(HiTrace_Output_Level level, const char* name, int32_t taskId);

/**
 * @brief Marks an integer variable trace task with the trace output level specified.
 *
 * @param level Trace output level.
 * @param name Name of the integer variable. It does not need to be the same as the actual variable name.
 * @param count Integer value.
 * @since 19
 */
void OH_HiTrace_CountTraceEx(HiTrace_Output_Level level, const char* name, int64_t count);

/**
 * @brief Checks whether trace capture is enabled for an application.
 *
 * @return When it is enabled, **true** is returned;
 *     when it is disabled or stopped, **false** is returned. In this case, calling the HiTraceMeter API does not
 *     take effect.
 * @since 19
 */
bool OH_HiTrace_IsTraceEnabled(void);

/**
 * @brief Registers a callback to notify whether the application trace capture is enabled. This API uses a synchronous
 * callback to return the result.
 * After the registration is successful, the callback is executed immediately. Subsequent callbacks are executed
 * when the application trace capture status changes.
 * Callbacks are stored in the application process. A maximum of 10 callbacks can be registered in a process.
 * If the callback contains time-consuming operations, the registration or unregistration will be blocked (waiting
 * for the callback execution to complete) when the callback is executed.
 * Therefore, you are advised not to register or unregister callbacks containing time-consuming operations in the
 * main thread of the application to avoid application freeze.
 *
 * @param callback Registered callback.
 * @return Callback registration status.
 *     >= **0**: The registration is successful. The callback index for unregistration is returned. The index
 *     ranges from 0 to 9.
 *     **-1**: The maximum number of callbacks has been reached.
 *     **-2**: Invalid parameter. The parameter is not of the {@link OH_HiTrace_TraceEventListener} type.
 * @since 22
 */
int32_t OH_HiTrace_RegisterTraceListener(OH_HiTrace_TraceEventListener callback);

/**
 * @brief Unregisters the callback used to notify whether the application trace capture is enabled.
 * You can use this function to unregister the callback function associated with the callback index returned by
 * {@link OH_HiTrace_RegisterTraceListener}.
 *
 * @param index Index of the registered callback.
 * @return Callback unregistration status.
 *     **0**: Unregistration succeeded.
 *     **-1**: The callback corresponding to the index is not registered.
 *     **-2**: Invalid index. The index value is not within the range of 0 to 9.
 * @since 22
 */
int32_t OH_HiTrace_UnregisterTraceListener(int32_t index);

#ifdef __cplusplus
}
#endif
/** @} */

#endif // HIVIEWDFX_HITRACE_H