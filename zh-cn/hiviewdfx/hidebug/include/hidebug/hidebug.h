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

#include "hidebug_type.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief 获取系统的CPU资源占用情况百分比。注意：由于该接口涉及跨进程通信，耗时较长，建议不要在主线程中直接调用。
 *
 * @return 返回系统CPU资源占用情况百分比。如果返回结果为0，可能的原因是获取失败。
 * @since 12
 */
double OH_HiDebug_GetSystemCpuUsage();

/**
 * @brief 获取进程的CPU使用率百分比。注意：由于该接口涉及跨进程通信，耗时较长，建议不要在主线程中直接调用。
 *
 * @return 返回进程的CPU使用率百分比。如果返回结果为0，可能因当前应用的CPU使用率过低导致。
 * @since 12
 */
double OH_HiDebug_GetAppCpuUsage();

/**
 * @brief 获取应用所有线程CPU使用情况。注意：由于该接口涉及跨进程通信，耗时较长，建议不要在主线程中直接调用。
 *
 * @return 返回所有线程CPU使用情况，见{@link HiDebug_ThreadCpuUsagePtr}。
 *     <br>若返回结果为null，可能因未获取到线程相关数据所致。
 * @since 12
 */
HiDebug_ThreadCpuUsagePtr OH_HiDebug_GetAppThreadCpuUsage();

/**
 * @brief 释放线程数据结构。
 *
 * @param threadCpuUsage 应用的所有线程可用CPU使用缓冲区指针，见{@link HiDebug_ThreadCpuUsagePtr}。
 *     传入的参数是要由OH_HiDebug_GetAppThreadCpuUsage()得到的。
 * @since 12
 */
void OH_HiDebug_FreeThreadCpuUsage(HiDebug_ThreadCpuUsagePtr *threadCpuUsage);

/**
 * @brief 获取系统内存信息。
 *
 * @param systemMemInfo 表示指向{@link HiDebug_SystemMemInfo}。函数调用后，若结构体数据为空，则表明调用失败。
 * @since 12
 */
void OH_HiDebug_GetSystemMemInfo(HiDebug_SystemMemInfo *systemMemInfo);

/**
 * @brief 获取应用程序进程的内存信息。注意：由于该接口需要读取/proc/{pid}/smaps_rollup节点信息，耗时较长，建议不要在主线程中直接调用。
 *
 * @param nativeMemInfo 表示指向{@link HiDebug_NativeMemInfo}。函数调用后，若结构体数据为空，则表明调用失败。
 * @since 12
 */
void OH_HiDebug_GetAppNativeMemInfo(HiDebug_NativeMemInfo *nativeMemInfo);

/**
 * @brief 获取应用程序进程的内存信息，该接口存在缓存机制以提高接口性能。缓存值的有效期为5分钟。注意：由于该接口需要读取/proc/{pid}/smaps_rollup节点信息，耗时较长，建议不要在主线程中直接调用。
 *
 * @param nativeMemInfo 表示指向{@link HiDebug_NativeMemInfo}。函数调用后，若结构体数据为空，则表明调用失败。
 * @param forceRefresh 是否需要无视缓存有效性，强制更新缓存值。
 *     <br>当为true时，直接获取当前内存数据并更新缓存值；
 *     <br>当为false时，缓存有效时，直接返回缓存值，缓存失效时，获取当前内存数据并更新缓存值。
 * @since 20
 */
void OH_HiDebug_GetAppNativeMemInfoWithCache(HiDebug_NativeMemInfo *nativeMemInfo, bool forceRefresh);

/**
 * @brief 获取应用程序进程的内存限制。
 *
 * @param memoryLimit 表示指向{@link HiDebug_MemoryLimit}。函数调用后，若结构体数据为空，则表明调用失败。
 * @since 12
 */
void OH_HiDebug_GetAppMemoryLimit(HiDebug_MemoryLimit *memoryLimit);

/**
 * @brief 启动应用trace采集。
 *
 * @param flag 采集线程trace方式。
 * @param tags 采集trace场景标签。
 * @param limitSize trace文件的最大大小（以字节为单位），最大为 500MB。
 * @param fileName 输出trace文件名缓冲区。
 * @param length 输出trace文件名缓冲区长度。
 * @return 0 - 成功。
 *     <br>{@link HIDEBUG_INVALID_ARGUMENT} 401 - fileName参数为空指针或者传入的length参数过小或者limitSize参数小于等于0。
 *     <br>11400102 - 已经开启了一个trace。
 *     <br>11400103 - 没有权限去开启trace。
 *     <br>11400104 - 系统内部错误。
 * @since 12
 */
HiDebug_ErrorCode OH_HiDebug_StartAppTraceCapture(HiDebug_TraceFlag flag,
    uint64_t tags, uint32_t limitSize, char* fileName, uint32_t length);

/**
 * @brief 停止采集应用程序trace。
 *
 * @return 0 - 成功。
 *     <br>11400104 - 系统内部错误。
 *     <br>11400105 - 当前没有trace正在运行
 * @since 12
 */
HiDebug_ErrorCode OH_HiDebug_StopAppTraceCapture();

/**
 * @brief 根据设置的采集配置请求trace采集。
 *
 * @param config trace采集的采集配置参数，参考{@link OH_HiDebug_RequestTraceConfig}。
 * @param callback trace采集的回调函数，参考{@link OH_HiDebug_RequestTraceCallback}。
 * @return 返回结果码：
 *     <br>HIDEBUG_SUCCESS：采集成功。
 *     <br>HIDEBUG_TRACE_ABNORMAL：远程服务异常或状态异常。
 *     <br>OH_HIDEBUG_TRACE_STORAGE_LIMIT：trace存储达到限制。目录下存储的trace文件大于等于3份时，返回失败。
 *     <br>HIDEBUG_RESOURCE_UNAVAILABLE：采集资源限制。
 * @since 24
 */
HiDebug_ErrorCode OH_HiDebug_RequestTrace(OH_HiDebug_RequestTraceConfig *config,
    OH_HiDebug_RequestTraceCallback callback);

/**
 * @brief 获取应用GPU显存大小。注意：由于该接口涉及多次跨进程通信，其耗时可能超过1秒，建议不要在主线程中直接调用该接口。
 *
 * @param value 指向用来保存接口获取到的应用显存大小（单位KB）的变量的指针。
 * @return 0 - 接口获取成功。
 *     <br>401 - 无效参数，所传递参数为空指针。
 *     <br>11400104 - 系统内部错误。
 * @since 14
 */
HiDebug_ErrorCode OH_HiDebug_GetGraphicsMemory(uint32_t *value);

/**
 * @brief 通过设置基础库C库中的MallocDispatch表，将原始内存操作函数
 * （例如：malloc/free/calloc/realloc/mmap/munmap）临时替换为开发者自定义的内存操作函数。
 * MallocDispatch表是基础库C库中封装malloc/calloc/realloc/free等内存操作函数的结构体，
 * HiDebug_MallocDispatch只是MallocDispatch结构体的一部分。
 *
 * @param dispatchTable 指向开发者自定义内存操作函数{@link HiDebug_MallocDispatch}结构体指针。
 * @return 返回结果具体可参考{@link HiDebug_ErrorCode}：
 *     <br>{@link HIDEBUG_SUCCESS} 成功设置自定义内存操作函数。
 *     <br>{@link HIDEBUG_INVALID_ARGUMENT} 无效参数。
 * @since 20
 */
HiDebug_ErrorCode OH_HiDebug_SetMallocDispatchTable(struct HiDebug_MallocDispatch *dispatchTable);

/**
 * @brief 获取基础库C库当前默认MallocDispatch表，调用{@link OH_HiDebug_RestoreMallocDispatchTable}可恢复。
 *
 * @return 当前C库默认的{@link HiDebug_MallocDispatch}结构体指针。
 * @since 20
 */
HiDebug_MallocDispatch* OH_HiDebug_GetDefaultMallocDispatchTable(void);

/**
 * @brief 恢复基础库C库MallocDispatch表。
 *
 * @since 20
 */
void OH_HiDebug_RestoreMallocDispatchTable(void);

/**
 * @brief 根据给定的fp地址进行栈回溯，该函数异步信号安全。
 *
 * @param object 由{@link OH_HiDebug_CreateBacktraceObject}接口获取到的用来栈回溯的对象。
 * @param startFp 栈回溯的起始栈帧地址。
 * @param pcArray 保存栈回溯得到的pc地址的数组。
 * @param size 保存栈回溯得到的pc地址的数组长度。
 * @return 成功回溯并写入到pcArray中的栈帧数量。如果返回结果为0，原因可能是栈回溯失败。
 * @since 20
 */
int OH_HiDebug_BacktraceFromFp(HiDebug_Backtrace_Object object, void* startFp, void** pcArray, int size);

/**
 * @brief 若{@link OH_HiDebug_SymbolicAddress}接口调用成功，将通过该函数将解析后的栈信息返回给调用者。注意：由于该接口涉及多次IO操作，耗时较长，建议不要在主线程中直接调用。
 *
 * @param pc 传入{@link OH_HiDebug_SymbolicAddress}接口的需要解析的pc地址。
 * @param arg 传入{@link OH_HiDebug_SymbolicAddress}接口的arg值。
 * @param frame 由传入{@link OH_HiDebug_SymbolicAddress}接口的pc地址解析后的得到栈信息{@link HiDebug_StackFrame}指针，该指针指向内容仅在该函数作用域内有效。
 * @since 20
 */
typedef void (*OH_HiDebug_SymbolicAddressCallback)(void* pc, void* arg, const HiDebug_StackFrame* frame);

/**
 * @brief 通过给定的pc地址获取详细的符号信息，该函数非异步信号安全。
 *
 * @param object 由{@link OH_HiDebug_CreateBacktraceObject}接口创建的对象。
 * @param pc 由{@link OH_HiDebug_BacktraceFromFp}接口获取到的pc地址。
 * @param arg 保留的自定义参数，符号解析成功后系统内部会将该参数传递给回调函数{@link OH_HiDebug_SymbolicAddressCallback}。
 * @param callback 用于返回解析后栈信息的回调函数。
 * @return 返回结果具体可参考{@link HiDebug_ErrorCode}：
 *     <br>{@link HIDEBUG_SUCCESS} 成功获取到详细的栈信息，且该函数传入的callback被调用。
 *     <br>{@link HIDEBUG_INVALID_ARGUMENT} 无效参数。
 *     <br>{@link HIDEBUG_INVALID_SYMBOLIC_PC_ADDRESS} 无法根据传入的pc地址找到对应的符号。
 * @since 20
 */
HiDebug_ErrorCode OH_HiDebug_SymbolicAddress(HiDebug_Backtrace_Object object, void* pc, void* arg,
    OH_HiDebug_SymbolicAddressCallback callback);

/**
 * @brief 创建一个用于栈回溯及栈解析的对象，该函数非异步信号安全。
 *
 * @return 返回创建的对象的指针，当创建失败时返回NULL。
 * @since 20
 */
HiDebug_Backtrace_Object OH_HiDebug_CreateBacktraceObject(void);

/**
 * @brief 销毁由{@link OH_HiDebug_CreateBacktraceObject}创建的对象，以释放栈回溯及栈解析过程中申请的资源，该函数非异步信号安全。
 *
 * @param object 需要被销毁的对象。
 * @since 20
 */
void OH_HiDebug_DestroyBacktraceObject(HiDebug_Backtrace_Object object);

/**
 * @brief 获取应用显存占用的详细数据。
 *
 * @param interval 当显存数据缓存值存在时间超过设定间隔interval（单位：秒）时，接口会获取最新的显存数据并更新缓存；否则，接口将直接返回缓存值。
 *     <br>interval的取值范围为[2，3600]，若传入的interval超出取值范围时，将使用300作为默认值。
 * @param summary 表示指向{@link HiDebug_GraphicsMemorySummary}的指针。
 * @return 返回结果具体可参考{@link HiDebug_ErrorCode}：
 *     <br>HIDEBUG_SUCCESS 成功获取到应用显存数据。
 *     <br>HIDEBUG_INVALID_ARGUMENT 无效参数。
 *     <br>HIDEBUG_TRACE_ABNORMAL 系统内部错误。
 * @since 21
 */
HiDebug_ErrorCode OH_HiDebug_GetGraphicsMemorySummary(uint32_t interval, HiDebug_GraphicsMemorySummary *summary);

/**
 * @brief 轻量级Perf采样栈内容的回调函数定义。注意：采样数据仅在该回调函数执行期间有效，若需在函数外使用，务必对采样栈内容进行深拷贝。
 *
 * @param stacks 采样得到的调用栈内容。
 * @since 22
 */
typedef void (*OH_HiDebug_ThreadLiteSamplingCallback)(const char* stacks);

/**
 * 对指定的数个线程进行Perf采样，并在调用结束后返回采样栈内容。
 * 注意：调用该函数后会阻塞当前线程，直至采样过程完全结束。
 * 系统对该接口的调用次数有严格限制，频繁调用超出限额后，将返回
 * {@link HIDEBUG_RESOURCE_UNAVAILABLE}错误码。
 * @param config 指向Perf采样配置结构体{@link HiDebug_ProcessSamplerConfig}的指针。
 * @param stacksCallback 采样结束时的回调函数，用于返回采样结果。
 * @return 返回结果码：
 *     <br>HIDEBUG_SUCCESS：采样成功完成。
 *     <br>HIDEBUG_INVALID_ARGUMENT：无效参数。
 *     <br>HIDEBUG_NOT_SUPPORTED：当前设备不支持Perf采样。
 *     <br>HIDEBUG_UNDER_SAMPLING：已有采样任务正在执行中。
 *     <br>HIDEBUG_RESOURCE_UNAVAILABLE：采样资源不足或已达调用上限。
 * @since 22
 */
HiDebug_ErrorCode OH_HiDebug_RequestThreadLiteSampling(
    HiDebug_ProcessSamplerConfig* config, OH_HiDebug_ThreadLiteSamplingCallback stacksCallback);

/**
 * @brief 将维测信息添加到崩溃日志中，与{@link OH_HiDebug_ResetCrashObj}配对使用。
 * 若程序在OH_HiDebug_SetCrashObj与OH_HiDebug_ResetCrashObj之间发生崩溃，
 * 会将OH_HiDebug_SetCrashObj设置的维测信息添加到记录本次崩溃的日志中。
 *
 * @param type 维测信息的数据类型{@link HiDebug_CrashObjType}。
 * @param addr 维测信息的地址，崩溃时该地址必须保持有效。
 * @return 上次设置的维测信息的对象，如果上次没有设置则为0。
 * @since 23
 */
uint64_t OH_HiDebug_SetCrashObj(HiDebug_CrashObjType type, void* addr);

/**
 * @brief 将维测信息对象还原到使用OH_HiDebug_SetCrashObj之前的状态。
 *
 * @param crashObj 函数OH_HiDebug_SetCrashObj的返回值。
 * @since 23
 */
void OH_HiDebug_ResetCrashObj(uint64_t crashObj);

/**
 * @brief 异步启动当前进程资源采集功能。
 * <br>回调函数只在终止采集（含系统自动停止采集）时调用，其携带采集资源类型和采集文件路径。
 * <br>若采集异常，则文件路径为NULL。
 *
 * @param type 资源采集类型。
 * @param config 资源采集配置参数。
 * @param callback 资源采集回调结果函数。
 * @return 返回结果码：
 *     <br>HIDEBUG_RES_PROF_SUCCESS：启动资源采集成功。
 *     <br>HIDEBUG_RES_PROF_INVALID_ARG：资源采集参数无效。
 *     <br>HIDEBUG_RES_PROF_INVALID_MAX_DURATION：资源采集最大持续时间参数无效。
 *     <br>HIDEBUG_RES_PROF_INVALID_FILTER_SIZE：资源采集过滤大小参数无效。
 *     <br>HIDEBUG_RES_PROF_INVALID_MAX_STACK_DEPTH：资源采集最大回栈深度参数无效。
 *     <br>HIDEBUG_RES_PROF_INVALID_STATISTICS_INTERVAL：资源采集统计间隔参数无效。
 *     <br>HIDEBUG_RES_PROF_INVALID_SAMPLE_INTERVAL：资源采集采样大小参数无效。
 *     <br>HIDEBUG_RES_PROF_INVALID_RESOURCE_TYPE：资源采集类型参数无效。
 *     <br>HIDEBUG_RES_PROF_PERMISSION_DENIED：资源采集权限不足，采集资源的目标进程仅支持调用接口进程本身。
 *     <br>HIDEBUG_RES_PROF_ALREADY_STARTED：资源采集重复启动。
 *     <br>HIDEBUG_RES_PROF_PROCESS_OVERLIMIT：资源采集进程数超出 4 个限制。
 *     <br>HIDEBUG_RES_PROF_CONFLICT：资源采集与命令行工具或系统采集任务冲突。
 *     <br>HIDEBUG_RES_PROF_DAILY_QUOTA_EXCEEDED：资源采集每日配额超出 10 次限制。
 *     <br>HIDEBUG_RES_PROF_CPU_OVERLOADED：系统 CPU 处于高负载状态，CPU 占用率超过 70%。
 *     <br>HIDEBUG_RES_PROF_MEM_PRESSURE_CRITICAL：内存可用空间紧张，可用空间少于 15%。
 *     <br>HIDEBUG_RES_PROF_STORAGE_PRESSURE_CRITICAL：存储可用空间紧张，可用空间少于 15%。
 *     <br>HIDEBUG_RES_PROF_FAILURE：启动资源采集失败。
 * @since 24
 */
HiDebug_ErrorCode OH_HiDebug_StartProfiler(OH_HiDebug_ResourceType type, OH_HiDebug_ResProfilerConfig* config,
    OH_HiDebug_ProfilingCallback callback);

/**
 * @brief 停止当前进程资源采集功能。该接口可在{@link OH_HiDebug_StartProfiler}接口调用后使用，
 * 且调用间隔不能超过最大持续时间。
 *
 * @return 返回结果码：
 *     <br>HIDEBUG_RES_PROF_SUCCESS：已成功停止资源采集。
 *     <br>HIDEBUG_RES_PROF_NOT_STARTED：资源采集未启动，停止失败。
 *     <br>HIDEBUG_RES_PROF_FAILURE：停止资源采集失败。
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
 * @brief 注册内存导出监听。当应用的内存占用较高，或通过{@link hidumper命令}手动导出内存信息时，系统会主动调用已注册的回调函数。
 * <br>第三方应用框架或开发者可借此将应用内部内存信息转储到hidumper中，或通过商业灰度上传至OEM厂商。
 * <br>对应的注销函数为：{@link OH_HiDebug_UnregisterMemDumpListener}。
 *
 * @param name 监听器的唯一标识。用于标识本次注册的监听，注销时需传入相同的name。
 *     <br>相同name只能注册一次，重复注册将返回HIDEBUG_INVALID_ARGUMENT；如需更新，请先注销原监听器。
 * @param listener 触发监听的回调函数。
 * @return 返回结果码：
 *     <br>HIDEBUG_SUCCESS：操作成功。
 *     <br>HIDEBUG_INVALID_ARGUMENT：无效参数。
 * @since 26.0.0
 */
HiDebug_ErrorCode OH_HiDebug_RegisterMemDumpListener(const char* name, OH_HiDebug_MemDumpListener listener);

/**
 * @brief 注销已经注册成功的内存导出监听。
 *
 * @param name 监听器的唯一标识。需要与注册时传入的name保持一致。
 * @return 返回结果码：
 *     <br>HIDEBUG_SUCCESS：操作成功。
 *     <br>HIDEBUG_INVALID_ARGUMENT：无效参数。
 * @since 26.0.0
 */
HiDebug_ErrorCode OH_HiDebug_UnregisterMemDumpListener(const char* name);

/**
 * @brief Profiler helper接口，获取一个AsyncContext以便进一步使用。
 * 对应的注销函数为：OH_HiDebug_ReleaseAsyncContext
 *
 * @return AsyncContext.
 * @since 26.0.0
 */
uint64_t OH_HiDebug_AcquireAsyncContext();

/**
 * @brief Profiler helper接口，将AsyncContext推送到运行上下文。
 *
 * @param ctx {@link OH_Hidebug_AcquireAsyncContext}获取的上下文。
 * @since 26.0.0
 */
void OH_HiDebug_PushAsyncContext(uint64_t ctx);

/**
 * @brief Profiler helper接口，从运行上下文中弹出AsyncContext。
 *
 * @param ctx {@link OH_Hidebug_AcquireAsyncContext}获取的上下文。
 * @since 26.0.0
 */
void OH_HiDebug_PopAsyncContext(uint64_t ctx);

/**
 * @brief Profiler helper接口，将AsyncContext释放到系统。
 *
 * @param ctx {@link OH_Hidebug_AcquireAsyncContext}获取的上下文。
 * @since 26.0.0
 */
void OH_HiDebug_ReleaseAsyncContext(uint64_t ctx);

#ifdef __cplusplus
}
#endif // __cplusplus

/** @} */

#endif // HIVIEWDFX_HIDEBUG_H
