/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup HiDebug
 * @{
 *
 * @brief Provides debug functions.
 *
 * For example, you can use these functions to obtain cpu uage, memory, heap, capture trace.
 *
 * @since 12
 */

/**
 * @file hidebug.h
 *
 * @brief Defines the APIs for debugging.
 *
 * @library libohhidebug.so
 * @kit PerformanceAnalysisKit
 * @syscap SystemCapability.HiviewDFX.HiProfiler.HiDebug
 * @since 12
 */

#ifndef HIVIEWDFX_HIDEBUG_H

#define HIVIEWDFX_HIDEBUG_H

#include <stdint.h>
#include <stdbool.h>
#include "hidebug_type.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Obtains the CPU usage of the system. Note that this API involves cross-process communication and takes a long
 * time. Therefore, you are advised not to call this API in the main thread.
 *
 * @return Returns the system CPU usage if the operation is successful. Returns **0** if the operation fails.
 * @since 12
 */
double OH_HiDebug_GetSystemCpuUsage();

/**
 * @brief Obtains the CPU usage of an application. Note that this API involves cross-process communication and takes a
 * long time. Therefore, you are advised not to call this API in the main thread.
 *
 * @return Application CPU usage obtained if the operation is successful. If **0** is returned, the CPU usage of the
 *     current application is too low.
 * @since 12
 */
double OH_HiDebug_GetAppCpuUsage();

/**
 * @brief Obtains the CPU usage of all threads of an application. Note that this API involves cross-process
 * communication and takes a long time. Therefore, you are advised not to call this API in the main thread.
 *
 * @return CPU usage of all threads. For details, see {@link HiDebug_ThreadCpuUsagePtr}.
 *     <br>If null is returned, the thread data may not be obtained.
 * @since 12
 */
HiDebug_ThreadCpuUsagePtr OH_HiDebug_GetAppThreadCpuUsage();

/**
 * @brief Releases the **HiDebug_ThreadCpuUsagePtr**.
 *
 * @param threadCpuUsage Pointer to the available CPU buffer of all threads of the application. For details, see
 *     {@link HiDebug_ThreadCpuUsagePtr}. The input parameter is obtained by **OH_HiDebug_GetAppThreadCpuUsage()**.
 * @since 12
 */
void OH_HiDebug_FreeThreadCpuUsage(HiDebug_ThreadCpuUsagePtr *threadCpuUsage);

/**
 * @brief Obtains system memory information.
 *
 * @param systemMemInfo Pointer to {@link HiDebug_SystemMemInfo}. If the struct data is empty after the function is
 *     called, the calling fails.
 * @since 12
 */
void OH_HiDebug_GetSystemMemInfo(HiDebug_SystemMemInfo *systemMemInfo);

/**
 * @brief Obtains the memory information of an application process. Note that this API needs to read the **\/proc/{pid}/
 * smaps_rollup** node information, which takes a long time. Therefore, you are advised not to call this API in the
 * main thread.
 *
 * @param nativeMemInfo Pointer to {@link HiDebug_NativeMemInfo}. If the struct data is empty after the function is
 *     called, the calling fails.
 * @since 12
 */
void OH_HiDebug_GetAppNativeMemInfo(HiDebug_NativeMemInfo *nativeMemInfo);

/**
 * @brief Obtains the memory information of an application process. This API has a cache mechanism to improve its
 * performance. The cache value is valid for 5 minutes. Note that this API needs to read the **\/proc/{pid}/
 * smaps_rollup** node information, which takes a long time. Therefore, you are advised not to call this API in the
 * main thread.
 *
 * @param nativeMemInfo Pointer to {@link HiDebug_NativeMemInfo}. If the struct data is empty after the function is
 *     called, the calling fails.
 * @param forceRefresh Whether to ignore the cache validity and forcibly update the cache value.
 *     <br>The value **true** means to directly obtain the current memory data and update the cache value.
 *     <br>The value **false** means to directly return the cache value if the cache is valid and obtain the current
 *     memory data and update the cache value if the cache is invalid.
 * @since 20
 */
void OH_HiDebug_GetAppNativeMemInfoWithCache(HiDebug_NativeMemInfo *nativeMemInfo, bool forceRefresh);

/**
 * @brief Obtains the memory limit of an application process.
 *
 * @param memoryLimit Pointer to {@link HiDebug_MemoryLimit}. If the struct data is empty after the function is called,
 *     the calling fails.
 * @since 12
 */
void OH_HiDebug_GetAppMemoryLimit(HiDebug_MemoryLimit *memoryLimit);

/**
 * @brief Starts application trace collection.
 *
 * @param flag Type of the thread (the main thread or all threads of the application) to trace.
 * @param tags Modules or subsystems to trace.
 * @param limitSize Maximum size of the trace file (in bytes), which is 500 MB.
 * @param fileName Buffer for the output trace file.
 * @param length Length of the buffer for the output trace file.
 * @return **0** - The operation is successful.
 *     <br>{@link HIDEBUG_INVALID_ARGUMENT} 401 - The **fileName** parameter is a null pointer, the input **length**
 *     parameter is too small, or the **limitSize** parameter is less than or equal to 0.
 *     <br>**11400102** - A trace is already started.
 *     <br>**11400103** - You do not have the permission to start the trace function.
 *     <br>**11400104** - An internal system error occurs.
 * @since 12
 */
HiDebug_ErrorCode OH_HiDebug_StartAppTraceCapture(HiDebug_TraceFlag flag,
    uint64_t tags, uint32_t limitSize, char* fileName, uint32_t length);

/**
 * @brief Stops application trace collection.
 *
 * @return **0** - The operation is successful.
 *     <br>**11400104** - An internal system error occurs.
 *     <br>**11400105** - No trace collection is running.
 * @since 12
 */
HiDebug_ErrorCode OH_HiDebug_StopAppTraceCapture();

/**
 * @brief Requests application trace capture with specified configuration.
 *
 * @param config Indicates the trace request configuration. See {@link OH_HiDebug_RequestTraceConfig}.
 * @param callback Indicates the callback for the trace request. See {@link OH_HiDebug_RequestTraceCallback}.
 * @return Result code.
 *         {@link HIDEBUG_SUCCESS} The operation is successful.
 *         {@link HIDEBUG_TRACE_ABNORMAL} Remote service exception.
 *         {@link OH_HIDEBUG_TRACE_STORAGE_LIMIT} Trace storage limit reached.
 *         {@link HIDEBUG_RESOURCE_UNAVAILABLE} Resource unavailable.
 * @since 24
 */
HiDebug_ErrorCode OH_HiDebug_RequestTrace(OH_HiDebug_RequestTraceConfig *config,
    OH_HiDebug_RequestTraceCallback callback);

/**
 * @brief Obtains the size of the GPU memory. Note that this API involves multiple cross-process communications and may
 * take more than 1 second. Therefore, you are advised not to call this API in the main thread.
 *
 * @param value Pointer to the variable that stores the size (in KB) of the obtained GPU memory.
 * @return **0** - The API is obtained successfully.
 *     <br>**401** - The parameter is a null pointer, which is invalid.
 *     <br>**11400104** - An internal system error occurs.
 * @since 14
 */
HiDebug_ErrorCode OH_HiDebug_GetGraphicsMemory(uint32_t *value);

/**
 * @brief Sets the **MallocDispatch** table in the basic C library to temporarily replace the original memory operation
 * functions (such as **malloc**, **free**, **calloc**, **realloc**, **mmap**, and **munmap**) with the custom memory
 * operation functions. The **MallocDispatch** table is a struct that encapsulates memory operation functions such as **
 * malloc**, **calloc**, **realloc**, and **free** in the basic C library. **HiDebug_MallocDispatch** is only a part of
 * the **MallocDispatch** struct.
 *
 * @param dispatchTable Pointer to the {@link HiDebug_MallocDispatch} struct that contains the custom memory operation
 *     functions.
 * @return For details, see {@link HiDebug_ErrorCode}.
 *     <ul><li>{@link HIDEBUG_SUCCESS}: The custom memory operation function is set successfully.</li>
 *     <li>{@link HIDEBUG_INVALID_ARGUMENT}: Invalid parameter.</li></ul>
 * @since 20
 */
HiDebug_ErrorCode OH_HiDebug_SetMallocDispatchTable(struct HiDebug_MallocDispatch *dispatchTable);

/**
 * @brief Obtains the default MallocDispatch table of the system C library. You can call
 * {@link OH_HiDebug_RestoreMallocDispatchTable} to restore the table.
 *
 * @return Pointer to the default {@link HiDebug_MallocDispatch} struct of the current C library.
 * @since 20
 */
HiDebug_MallocDispatch* OH_HiDebug_GetDefaultMallocDispatchTable(void);

/**
 * @brief Restores the MallocDispatch table of the system C library.
 *
 * @since 20
 */
void OH_HiDebug_RestoreMallocDispatchTable(void);

/**
 * @brief Performs stack back-tracing based on the given fp address. This function is async-signal-safe.
 *
 * @param object Object obtained by the {@link OH_HiDebug_CreateBacktraceObject} API for stack backtracing.
 * @param startFp Start frame pointer for stack backtracing.
 * @param pcArray Array of PC addresses obtained from stack backtracing.
 * @param size Length of the PC address array obtained by stack backtracing.
 * @return Number of stack frames that are successfully backtraced and written to **pcArray**. If 0 is returned, stack
 *     backtracing may fail.
 * @since 20
 */
int OH_HiDebug_BacktraceFromFp(HiDebug_Backtrace_Object object, void* startFp, void** pcArray, int size);

/**
 * @brief If the {@link OH_HiDebug_SymbolicAddress} API is successfully called, the parsed stack information is
 * returned to the caller through this function. Note: This API involves multiple I/O operations and takes a long time.
 * Therefore, you are advised not to call this API in the main thread.
 *
 * @param pc PC address transferred to the {@link OH_HiDebug_SymbolicAddress} API for parsing.
 * @param arg arg value of the {@link OH_HiDebug_SymbolicAddress} API.
 * @param frame Pointer to {@link HiDebug_StackFrame}, which is obtained by parsing the PC address passed to the
 *     {@link OH_HiDebug_SymbolicAddress} API. What the pointer points to is valid only in the function scope.
 * @since 20
 */
typedef void (*OH_HiDebug_SymbolicAddressCallback)(void* pc, void* arg, const HiDebug_StackFrame* frame);

/**
 * @brief Obtains detailed symbol information based on the specified PC address. This function is not asyn-signal-safe.
 *
 * @param object Object created by the {@link OH_HiDebug_CreateBacktraceObject} API.
 * @param pc PC address obtained through the {@link OH_HiDebug_BacktraceFromFp} API.
 * @param arg Reserved custom parameter. After the symbol is successfully parsed, this parameter is passed to
 *     {@link OH_HiDebug_SymbolicAddressCallback}.
 * @param callback Callback used to return the parsed stack information.
 * @return For details, see {@link HiDebug_ErrorCode}.
 *     <ul><li>{@link HIDEBUG_SUCCESS}: The detailed stack information is successfully obtained, and the callback
 *     input by the function is called.</li>
 *     <li>{@link HIDEBUG_INVALID_ARGUMENT}: Invalid parameter.</li>
 *     <li>{@link HIDEBUG_INVALID_SYMBOLIC_PC_ADDRESS}: Failed to find the corresponding symbol based on the input
 *     PC address.</li></ul>
 * @since 20
 */
HiDebug_ErrorCode OH_HiDebug_SymbolicAddress(HiDebug_Backtrace_Object object, void* pc, void* arg,
    OH_HiDebug_SymbolicAddressCallback callback);

/**
 * @brief Creates an object for stack backtracing and parsing. This function is not asyn-signal-safe.
 *
 * @return Pointer to the created object. If the object fails to be created, NULL is returned.
 * @since 20
 */
HiDebug_Backtrace_Object OH_HiDebug_CreateBacktraceObject(void);

/**
 * @brief Destroys the object created by {@link OH_HiDebug_CreateBacktraceObject} to release the resources applied for
 * during stack backtracing and parsing. This function is not asyn-signal-safe.
 *
 * @param object Object to destroy.
 * @since 20
 */
void OH_HiDebug_DestroyBacktraceObject(HiDebug_Backtrace_Object object);

/**
 * @brief Obtains the detailed GPU memory usage of an application.
 *
 * @param interval Interval that the cached GPU memory data exists, in seconds. If the duration exceeds the value of
 *     interval, the API obtains the latest data and updates the buffer. Otherwise, the API directly returns the cached
 *     data.
 *     <br>The value range of interval is [2, 3600]. If the passed-in interval is out of the range, **300** is used as
 *     the default value.
 * @param summary Pointer to {@link HiDebug_GraphicsMemorySummary}.
 * @return For details, see {@link HiDebug_ErrorCode}.
 *     <ul><li>{@link HIDEBUG_SUCCESS}: The GPU memory information of the application is obtained successfully.</li>
 *     <li>{@link HIDEBUG_INVALID_ARGUMENT}: Invalid parameter.</li>
 *     <li>{@link HIDEBUG_TRACE_ABNORMAL}: Internal system error.</li></ul>
 * @since 21
 */
HiDebug_ErrorCode OH_HiDebug_GetGraphicsMemorySummary(uint32_t interval, HiDebug_GraphicsMemorySummary *summary);

/**
 * @brief Triggered for the lightweight Perf sampling stack content. Note: The sampling data is valid only during the
 * execution of this callback. If you need to use the data outside the function, deep copy the sampling stack content.
 *
 * @param stacks Content of the sampling call stack.
 * @since 22
 */
typedef void (*OH_HiDebug_ThreadLiteSamplingCallback)(const char* stacks);

/**
 * Performs Perf sampling on the specified threads and returns the sampling stack content after the call is complete.
 * Note: After this function is called, the current thread is blocked until the sampling process ends. The system
 * strictly limits the number of times that this API is called. If the number of times that this API is called exceeds
 * the upper limit, the error code {@link HIDEBUG_RESOURCE_UNAVAILABLE} is returned.
 * @param config Pointer to the {@link HiDebug_ProcessSamplerConfig} struct.
 * @param stacksCallback Callback used to return the sampling result when the sampling is complete.
 * @return Result code.
 *     <ul><li>{@link HIDEBUG_SUCCESS}: Sampling successful.</li>
 *     <li>{@link HIDEBUG_INVALID_ARGUMENT}: Invalid parameter.</li>
 *     <li>{@link HIDEBUG_NOT_SUPPORTED}: Perf sampling not supported.</li>
 *     <li>{@link HIDEBUG_UNDER_SAMPLING}: A sampling task is in progress.</li>
 *     <li>{@link HIDEBUG_RESOURCE_UNAVAILABLE}: Sampling resources are insufficient or the upper call limit is
 *     reached.</li></ul>
 * @since 22
 */
HiDebug_ErrorCode OH_HiDebug_RequestThreadLiteSampling(
    HiDebug_ProcessSamplerConfig* config, OH_HiDebug_ThreadLiteSamplingCallback stacksCallback);

/**
 * @brief Adds debugging information to the crash logs. This function is used together with
 * {@link OH_HiDebug_ResetCrashObj}. If a program crashes between **OH_HiDebug_SetCrashObj** and **
 * OH_HiDebug_ResetCrashObj**, the debugging information set by **OH_HiDebug_SetCrashObj** is added to the crash logs.
 *
 * @param type Data type of the debugging information. For details, see {@link HiDebug_CrashObjType}.
 * @param addr Address of the debugging information. The address must be valid when a crash occurs.
 * @return Object of the debugging information that was set last time. If no debugging information is set last time,
 *     the value is **0**.
 * @since 23
 */
uint64_t OH_HiDebug_SetCrashObj(HiDebug_CrashObjType type, void* addr);

/**
 * @brief Resets the debugging information object to the state before **OH_HiDebug_SetCrashObj** is used.
 *
 * @param crashObj Return value of the **OH_HiDebug_SetCrashObj** function.
 * @since 23
 */
void OH_HiDebug_ResetCrashObj(uint64_t crashObj);

/**
 * @brief Starts Resource Profiler for the current process asynchronously.
 * The callback is invoked only after profiling stops, including auto-stop caused by the maximum duration.
 * When profiling output is available, the callback carries the output file path. If profiling stops without
 * producing output, the callback is invoked with a NULL file path.
 *
 * @param type Type of resource to be profiled.
 * @param config Configuration parameters for the profiler.
 * @param callback Callback to receive the profiling result. See {@link OH_HiDebug_ProfilingCallback}.
 * @return Result code
 *         {@link HIDEBUG_RES_PROF_SUCCESS} Resource profiler started successfully.
 *         {@link HIDEBUG_RES_PROF_INVALID_ARG} Invalid resource profiler argument.
 *         {@link HIDEBUG_RES_PROF_INVALID_MAX_DURATION} Invalid maximum duration.
 *         {@link HIDEBUG_RES_PROF_INVALID_FILTER_SIZE} Invalid filter size.
 *         {@link HIDEBUG_RES_PROF_INVALID_MAX_STACK_DEPTH} Invalid maximum stack depth.
 *         {@link HIDEBUG_RES_PROF_INVALID_STATISTICS_INTERVAL} Invalid statistics interval.
 *         {@link HIDEBUG_RES_PROF_INVALID_SAMPLE_INTERVAL} Invalid sample interval.
 *         {@link HIDEBUG_RES_PROF_INVALID_RESOURCE_TYPE} Invalid resource type.
 *         {@link HIDEBUG_RES_PROF_PERMISSION_DENIED} Resource profiler permission denied.
 *         {@link HIDEBUG_RES_PROF_ALREADY_STARTED} Resource profiler already started.
 *         {@link HIDEBUG_RES_PROF_PROCESS_OVERLIMIT} Resource profiler process count exceeds the limit.
 *         {@link HIDEBUG_RES_PROF_CONFLICT} Resource profiler conflicts with CLI tools or system profiling tasks.
 *         {@link HIDEBUG_RES_PROF_DAILY_QUOTA_EXCEEDED} Daily quota exceeded during resource profiling.
 *         {@link HIDEBUG_RES_PROF_CPU_OVERLOADED} System is experiencing high CPU utilization.
 *         {@link HIDEBUG_RES_PROF_MEM_PRESSURE_CRITICAL} Insufficient available memory.
 *         {@link HIDEBUG_RES_PROF_STORAGE_PRESSURE_CRITICAL} Insufficient available storage space.
 *         {@link HIDEBUG_RES_PROF_FAILURE} Failed to start the resource profiler.
 * @since 24
 */
HiDebug_ErrorCode OH_HiDebug_StartProfiler(OH_HiDebug_ResourceType type, OH_HiDebug_ResProfilerConfig* config,
    OH_HiDebug_ProfilingCallback callback);

/**
 * @brief Stops resource profiler for the current process. This API can be called after the
 * {@link OH_HiDebug_StartProfiler} API and the call duration must be within the maximum duration.
 *
 * @return Result code
 *         {@link HIDEBUG_RES_PROF_SUCCESS} Resource profiler stopped successfully.
 *         {@link HIDEBUG_RES_PROF_NOT_STARTED} Resource profiler not started.
 *         {@link HIDEBUG_RES_PROF_FAILURE} Failed to stop the resource profiler.
 * @since 24
 */
HiDebug_ErrorCode OH_HiDebug_StopProfiler(void);

/**
 * @brief Callback triggered for listening. You can use FDs to write memory data in your app so that you can export the
 *     data using the hidumper command.
 *
 * @param fd FD used to write memory data in the app.
 * @param tag Callback type. You can process the related logic based on the callback type.
 * @param mayReportToOEM Whether the data will be uploaded to the OEM. If the value is true, the data will be uploaded
 *     to the OEM. Pay attention to data privacy and security issues.
 * @param arg Callback argument. You can pass different arguments based on the value of type.
 * @return Whether the operation is successful.
 * @since 26.0.0
 */
typedef bool (*OH_HiDebug_MemDumpListener)(int32_t fd, OH_HiDebug_MemListenerType tag,
                                           bool mayReportToOEM, const char* arg);

/**
 * @brief Registers a listener triggered when the memory watermark of an app is high or the memory information is
 *     manually exported by hidumper. The third-party app framework or app developer calls back the registered function
 *     to dump the app's internal memory information to hidumper or upload the information to the OME vendor through
 *     commercial gray release.
 * OH_HiDebug_UnregisterMemDumpListener is used to unregister the listener.
 * @param name Consumer type ID.
 * @param listener Callback triggered for listening.
 * @return Result code.
 * {@link HIDEBUG_SUCCESS } Operation succeeded.
 * {@link HIDEBUG_INVALID_ARGUMENT } Invalid argument.
 * @since 26.0.0
 */
HiDebug_ErrorCode OH_HiDebug_RegisterMemDumpListener(const char* name, OH_HiDebug_MemDumpListener listener);

/**
 * @brief Unregisters a memory dump listener that has been successfully registered.
 * @param name Consumer type ID.
 * @return Result code.
 * {@link HIDEBUG_SUCCESS } Operation succeeded.
 * {@link HIDEBUG_INVALID_ARGUMENT } Invalid argument.
 * @since 26.0.0
 */
HiDebug_ErrorCode OH_HiDebug_UnregisterMemDumpListener(const char* name);

/**
 * @brief Profiler helper interfaces, acquire a AsyncContext for further using.
 *      The corresponding unregister function is as follows: OH_HiDebug_ReleaseAsyncContext.
 *
 * @return AsyncContext.
 * @since 26.0.0
 */
uint64_t OH_HiDebug_AcquireAsyncContext();

/**
 * @brief Profiler helper interfaces, push AsyncContext to the running context.
 *
 * @param ctx The context acquired by {@link OH_Hidebug_AcquireAsyncContext}.
 * @since 26.0.0
 */
void OH_HiDebug_PushAsyncContext(uint64_t ctx);

/**
 * @brief Profiler helper interfaces, pop AsyncContext from the running context.
 *
 * @param ctx The context acquired by {@link OH_Hidebug_AcquireAsyncContext}.
 * @since 26.0.0
 */
void OH_HiDebug_PopAsyncContext(uint64_t ctx);

/**
 * @brief Profiler helper interfaces, release AsyncContext to system.
 *
 * @param ctx The context acquired by {@link OH_Hidebug_AcquireAsyncContext}.
 * @since 26.0.0
 */
void OH_HiDebug_ReleaseAsyncContext(uint64_t ctx);

#ifdef __cplusplus
}
#endif // __cplusplus

/** @} */

#endif // HIVIEWDFX_HIDEBUG_H
