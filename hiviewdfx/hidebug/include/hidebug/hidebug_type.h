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
 * @file hidebug_type.h
 *
 * @brief Defines the code of the HiDebug module.
 *
 * @kit PerformanceAnalysisKit
 * @library libohhidebug.so
 * @syscap SystemCapability.HiviewDFX.HiProfiler.HiDebug
 * @since 12
 */

/**
 * @addtogroup HiDebug
 * @{
 *
 * @brief Provides debug code define.
 *
 * For example, you can use these code for check result or parameter of HiDebug function.
 *
 * @since 12
 */

#ifndef HIVIEWDFX_HIDEBUG_TYPE_H
#define HIVIEWDFX_HIDEBUG_TYPE_H

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Enumerates the error codes used in the HiDebug module.
 *
 * @since 12
 */
typedef enum HiDebug_ErrorCode {
    /**
     * Operation successful.
     */
    HIDEBUG_SUCCESS = 0,

    /**
     * Invalid parameter. Possible causes: 1. The parameter value is incorrect. 2. The parameter type is incorrect.
     */
    HIDEBUG_INVALID_ARGUMENT = 401,

    /**
     * Repeated collection.
     */
    HIDEBUG_TRACE_CAPTURED_ALREADY = 11400102,

    /**
     * No file write permission.
     */
    HIDEBUG_NO_PERMISSION = 11400103,

    /**
     * Internal system error.
     */
    HIDEBUG_TRACE_ABNORMAL = 11400104,

    /**
     * No trace task is running.
     */
    HIDEBUG_NO_TRACE_RUNNING = 11400105,

    /**
     * Trace storage limit reached
     * @since 24
     */
    OH_HIDEBUG_TRACE_STORAGE_LIMIT = 11400120,

    /**
     * PC address passed to the symbol parsing function is invalid.
     * @since 20
     */
    HIDEBUG_INVALID_SYMBOLIC_PC_ADDRESS = 11400200,

    /**
 * Current device is not supported.
 * @since 22
 */
    HIDEBUG_NOT_SUPPORTED = 11400300,

    /**
 * Current process is being sampled.
 * @since 22
 */
    HIDEBUG_UNDER_SAMPLING = 11400301,

    /**
     * Sampling resources are unavailable.
     * @since 22
     */
    HIDEBUG_RESOURCE_UNAVAILABLE = 11400302,

    /**
     * Resource profiler started/stopped successfully.
     * @since 24
     */
    HIDEBUG_RES_PROF_SUCCESS = 11400400,

    /**
     * Invalid resource profiler argument.
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_ARG = 11400410,

    /**
     * Invalid maximum duration.
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_MAX_DURATION = 11400411,

    /**
     * Invalid filter size.
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_FILTER_SIZE = 11400412,

    /**
     * Invalid maximum stack depth.
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_MAX_STACK_DEPTH = 11400413,

    /**
     * Invalid statistics interval.
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_STATISTICS_INTERVAL = 11400414,

    /**
     * Invalid sample interval.
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_SAMPLE_INTERVAL = 11400415,

    /**
     * Invalid resource type.
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_RESOURCE_TYPE = 11400416,

    /**
     * Resource profiler permission denied.
     * @since 24
     */
    HIDEBUG_RES_PROF_PERMISSION_DENIED = 11400420,

    /**
     * Resource profiler already started.
     * @since 24
     */
    HIDEBUG_RES_PROF_ALREADY_STARTED = 11400421,

    /**
     * Resource profiler not started.
     * @since 24
     */
    HIDEBUG_RES_PROF_NOT_STARTED = 11400422,

    /**
     * Resource profiler process count exceeds the limit.
     * @since 24
     */
    HIDEBUG_RES_PROF_PROCESS_OVERLIMIT = 11400423,

    /**
     * Resource profiler conflicts with CLI tools or system profiling tasks.
     * @since 24
     */
    HIDEBUG_RES_PROF_CONFLICT = 11400424,

    /**
     * Resource profiler automatically stopped due to the duration limit.
     * @since 24
     */
    HIDEBUG_RES_PROF_AUTO_STOPPED_BY_DURATION = 11400425,

    /**
     * Daily quota exceeded during resource profiling.
     * @since 24
     */
    HIDEBUG_RES_PROF_DAILY_QUOTA_EXCEEDED = 11400426,

    /**
     * System is experiencing high CPU utilization.
     * @since 24
     */
    HIDEBUG_RES_PROF_CPU_OVERLOADED = 11400427,

    /**
     * Insufficient available memory.
     * @since 24
     */
    HIDEBUG_RES_PROF_MEM_PRESSURE_CRITICAL = 11400428,

    /**
     * Insufficient available storage space.
     * @since 24
     */
    HIDEBUG_RES_PROF_STORAGE_PRESSURE_CRITICAL = 11400429,

    /**
 * Failed to start/stop the resource profiler.
 * @since 24
 */
    HIDEBUG_RES_PROF_FAILURE = 11400430
} HiDebug_ErrorCode;

/**
 * @brief Defines the struct for the CPU usage of all threads of an application.
 *
 * @since 12
 */
typedef struct HiDebug_ThreadCpuUsage {
    /**
     * Thread ID.
     */
    uint32_t threadId;
    /**
     * Thread CPU usage, in percentage.
     */
    double cpuUsage;
    /**
     * Pointer to the CPU usage of the next thread.
     */
    struct HiDebug_ThreadCpuUsage *next;
} HiDebug_ThreadCpuUsage;

/**
 * @brief Defines pointer of HiDebug_ThreadCpuUsage.
 *
 * @since 12
 */
typedef HiDebug_ThreadCpuUsage* HiDebug_ThreadCpuUsagePtr;

/**
 * @brief Defines a struct for the system memory information.
 *
 * @since 12
 */
typedef struct HiDebug_SystemMemInfo {
    /**
     * Total memory of the system, in KB.
     */
    uint32_t totalMem;
    /**
     * Free memory of the system, in KB.
     */
    uint32_t freeMem;
    /**
     * Available memory of the system, in KB.
     */
    uint32_t availableMem;
} HiDebug_SystemMemInfo;

/**
 * @brief Defines the struct for the local memory information of the application process.
 *
 * @since 12
 */
typedef struct HiDebug_NativeMemInfo {
    /**
     * Proportional set size, in KB.
     */
    uint32_t pss;
    /**
     * Virtual memory size, in KB.
     */
    uint32_t vss;
    /**
     * Resident set size, in KB.
     */
    uint32_t rss;
    /**
     * Size of the shared dirty memory, in KB.
     */
    uint32_t sharedDirty;
    /**
     * Size of the private dirty memory, in KB.
     */
    uint32_t privateDirty;
    /**
     * Size of the shared clean memory, in KB.
     */
    uint32_t sharedClean;
    /**
     * Size of the private clean memory, in KB.
     */
    uint32_t privateClean;
} HiDebug_NativeMemInfo;

/**
 * @brief Defines the struct for the memory limit of the application process.
 *
 * @since 12
 */
typedef struct HiDebug_MemoryLimit {
    /**
     * Limit on the physical memory size of the application process, in KB. Currently, the system does not limit the
     * physical memory size of the process. However, the available physical memory of the process cannot exceed the
     * maximum physical memory of the device. You can call {@link OH_HiDebug_GetSystemMemInfo} to obtain the physical
     * memory usage of the device.
     */
    uint64_t rssLimit;
    /**
     * Limit on the virtual set size, in KB.
     */
    uint64_t vssLimit;
} HiDebug_MemoryLimit;

/**
 * @brief Enumerates the thread types for trace collection.
 *
 * @since 12
 */
typedef enum HiDebug_TraceFlag {
    /**
     * Only the main thread of the current application.
     */
    HIDEBUG_TRACE_FLAG_MAIN_THREAD = 1,

    /**
     * All threads of the application.
     */
    HIDEBUG_TRACE_FLAG_ALL_THREADS = 2
} HiDebug_TraceFlag;

/**
 * @brief Defines trace request configuration.
 *
 * @since 24
 */
typedef struct OH_HiDebug_RequestTraceConfig {
    /**
     * Identifier used as the prefix of the output trace file name.
     * @since 24
     */
    const char* identifier;
    /**
     * The buffer size of the trace file, in kb.
     * @since 24
     */
    uint32_t bufferSizeKb;
    /**
     * The duration of the trace, in ms.
     * @since 24
     */
    uint32_t durationMs;
    /**
     * Reserved field for future use. Set to 0.
     * @since 24
     */
    uint32_t reserved;
} OH_HiDebug_RequestTraceConfig;

/**
 * @brief Defines callback type for trace request.
 *
 * @param errorCode Result code, see {@link HiDebug_ErrorCode}.
 * @param filePath Path of the generated trace file, may be NULL on failure.
 * @since 24
 */
typedef void (*OH_HiDebug_RequestTraceCallback)(HiDebug_ErrorCode errorCode, const char* filePath);

/**
 * @brief Defines the struct types of the replaceable/restorable **HiDebug_MallocDispatch** table of the application
 * process.
 *
 * @since 20
 */
typedef struct HiDebug_MallocDispatch {
    void* (*malloc)(size_t);
    void* (*calloc)(size_t, size_t);
    void* (*realloc)(void*, size_t);
    void  (*free)(void*);
    void* (*mmap)(void*, size_t, int, int, int, off_t);
    int   (*munmap)(void*, size_t);
} HiDebug_MallocDispatch;

/**
 * @brief Defines a struct for the JS stack frame content.
 *
 * @since 20
 */
typedef struct HiDebug_JsStackFrame {
    /**
     * Relative PC address, which is the offset of the current PC relative to the start address of its mapping area (
     * such as an executable file or shared library).
     */
    uint64_t relativePc;
 
    /**
     * Line number of the code corresponding to the current stack frame in the file.
     */
    int32_t line;
 
    /**
     * Column number of the code corresponding to the current stack frame in the specified line.
     */
    int32_t column;
 
    /**
     * Name of the mapping area to which the current stack frame belongs.
     */
    const char* mapName;
 
    /**
     * Name of the function corresponding to the current stack frame.
     */
    const char* functionName;
 
    /**
     * URL of the code file corresponding to the current stack frame. It can be used to find the corresponding code
     * file in the local path or on the remote server.
     */
    const char* url;
 
    /**
     * Name of the package to which the code corresponding to the current stack frame belongs.
     */
    const char* packageName;
} HiDebug_JsStackFrame;

/**
 * @brief Defines the native stack frame content.
 *
 * @since 20
 */
typedef struct HiDebug_NativeStackFrame {
    /**
     * Relative PC address, which is the offset of the current PC relative to the start address of its mapping area (
     * such as an executable file or shared library).
     */
    uint64_t relativePc;
 
    /**
     * Offset of the function corresponding to the current stack frame in its mapping area (such as an executable file
     * or shared library).
     */
    uint64_t funcOffset;
 
    /**
     * Name of the mapping area to which the current stack frame belongs.
     */
    const char* mapName;
 
    /**
     * Name of the function corresponding to the current stack frame.
     */
    const char* functionName;
 
    /**
     * Build ID that uniquely identifies the current mapping area (such as an executable file or shared library).
     * During debugging and symbol parsing, **buildId** ensures that the symbol file version matches the actual binary
     * file version.
     */
    const char* buildId;
 
    /**
     * Reserved field for future extension.
     */
    const char* reserved;
} HiDebug_NativeStackFrame;

/**
 * @brief Enumerates the stack frame types.
 *
 * @since 20
 */
typedef enum HiDebug_StackFrameType {
    /**
     * JS stack frame.
     */
    HIDEBUG_STACK_FRAME_TYPE_JS = 1,

    /**
     * Native stack frame.
     */
    HIDEBUG_STACK_FRAME_TYPE_NATIVE = 2
} HiDebug_StackFrameType;

/**
 * @brief Defines the stack frame content.
 *
 * @since 20
 */
typedef struct HiDebug_StackFrame {
    /**
     * Type of the current stack.
     */
    HiDebug_StackFrameType type;

    /** frame content. */
    union {
        /** Js stack frame defined in {@link HiDebug_JsStackFrame} */
        struct HiDebug_JsStackFrame js;
        /** Native frame defined in {@link HiDebug_NativeStackFrame} */
        struct HiDebug_NativeStackFrame native;
    } frame;
} HiDebug_StackFrame;

/**
 * @brief Defines an object used for stack backtracing and stack parsing.
 *
 * @since 20
 */
typedef struct HiDebug_Backtrace_Object__* HiDebug_Backtrace_Object;

/**
 * @brief Defines a struct for the application graphics memory usage details.
 *
 * @since 21
 */
typedef struct HiDebug_GraphicsMemorySummary {
    /**
     * GL memory size (memory occupied by RenderService for loading required resources, such as images and textures),
     * in KB.
     */
    uint32_t gl;

    /**
     * Graph memory size (DMA memory usage of the process), in KB, including the DMA buffers obtained directly through
     * the API and those obtained through **allocator_host**.
     */
    uint32_t graph;
} HiDebug_GraphicsMemorySummary;

/**
 * @brief Defines a struct for sampling configuration.
 *
 * @since 22
 */
typedef struct HiDebug_ProcessSamplerConfig {
    /**
     * Array of thread IDs to sample. A maximum of 10 threads can be sampled at the same time. If the array length
     * exceeds 10, the first 10 threads are sampled.
     */
    uint32_t* tids;

    /**
     * Length of the array to which **tids** points.
     */
    uint32_t size;

    /**
     * Sampling frequency, in Hz. The value ranges from 1 to 200. If the value is out of the range, the default value **
     * 100** is used.
     */
    uint32_t frequency;

    /**
     * Sampling duration, in ms. The value ranges from 1000 to 10000. If the value is less than 1000, the API call is
     * abnormal. If the value is greater than 10000, 10000 is used.
     */
    uint32_t duration;

    /**
     * Reserved.
     */
    uint32_t reserved;
} HiDebug_ProcessSamplerConfig;

/**
 * @brief Enumerates the data types of debugging information.
 *
 * @since 23
 */
typedef enum HiDebug_CrashObjType {
    /**
      * String.
      */
    HIDEBUG_CRASHOBJ_STRING = 0,

    /**
      * 64-byte memory block.
      */
    HIDEBUG_CRASHOBJ_MEMORY_64B = 1,

    /**
      * 256-byte memory block.
      */
    HIDEBUG_CRASHOBJ_MEMORY_256B = 2,

    /**
     * 1024-byte memory block.
     */
    HIDEBUG_CRASHOBJ_MEMORY_1024B = 3,

    /**
      * 2048-byte memory block.
      */
    HIDEBUG_CRASHOBJ_MEMORY_2048B = 4,

    /**
     * 4096-byte memory block.
     */
    HIDEBUG_CRASHOBJ_MEMORY_4096B = 5
} HiDebug_CrashObjType;

/**
 * @brief Defines a struct for the resource profiler configuration.
 *
 * @since 24
 */
typedef struct OH_HiDebug_ResProfilerConfig {
    /**
     * Maximum collection duration, in seconds.
     * @since 24
     */
    uint32_t maxDuration;
    /**
     * Filter size, in bytes.
     * @since 24
     */
    uint32_t filterSize;
    /**
     * Maximum stack trace depth, in frames.
     * @since 24
     */
    uint32_t maxStackDepth;
    /**
     * Statistics interval, in seconds.
     * @since 24
     */
    uint32_t statisticsInterval;
    /**
     * Sample interval, in bytes.
     * In sampling mode, if the memory allocation size is less than or equal to the sample interval,
     * it will be sampled probabilistically, otherwise, it will be sampled fully.
     * @since 24
     */
    uint32_t sampleInterval;
} OH_HiDebug_ResProfilerConfig;

/**
 * @brief Defines an enum for the resource profiler types.
 *
 * @since 24
 */
typedef enum OH_HiDebug_ResourceType {
    /**
     * File descriptor
     * @since 24
     */
    OH_RES_TYPE_FD,

    /**
     * Thread
     * @since 24
     */
    OH_RES_TYPE_THREAD,

    /**
     * Native memory
     * @since 24
     */
    OH_RES_TYPE_NATIVE,

    /**
     * GPU memory
     * @since 24
     */
    OH_RES_TYPE_GPU,

    /**
     * Global handle
     * @since 24
     */
    OH_RES_TYPE_GLOBAL_HANDLE
} OH_HiDebug_ResourceType;

/**
 * @brief Encapsulates result of a single profiling request operation.
 *        It represents data delivered via OH_HiDebug_ProfilingCallback.
 *
 * @since 24
 */
typedef struct OH_HiDebug_ProfilingResult {
    /**
     * Profiled resource type.
     * @since 24
     */
    OH_HiDebug_ResourceType resourceType;
    /**
     * File path of the profiling result data. Null if the profiling fails.
     * @since 24
     */
    const char* filePath;
} OH_HiDebug_ProfilingResult;

/**
 * @brief Callback signature for the resource profiling result.
 *
 * @param result Pointer to the OH_HiDebug_ProfilingResult structure.
 * @since 24
 */
typedef void (*OH_HiDebug_ProfilingCallback)(OH_HiDebug_ProfilingResult* result);

/**
 * @brief Defines an enum for memory listener callbacks.
 * @since 26.0.0
 */
typedef enum OH_HiDebug_MemListenerType {
    /**
     * Default value. No processing is required.
     * @since 26.0.0
     */
    OH_HIDEBUG_DO_NOTHING = 0,

    /**
     * GC operation
     * @since 26.0.0
     */
    OH_HIDEBUG_RUNNING_GC = 1,

    /**
     * Dump memory snapshot
     * @since 26.0.0
     */
    OH_HIDEBUG_DUMP_SNAPSHOT = 2
} OH_HiDebug_MemListenerType;

#ifdef __cplusplus
}
#endif // __cplusplus

/**
 * @brief FFRT tasks.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_FFRT (1ULL << 13)

/**
 * @brief Common library subsystem tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_COMMON_LIBRARY (1ULL << 16)

/**
 * @brief HDF subsystem tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_HDF (1ULL << 18)

/**
 * @brief Net tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_NET (1ULL << 23)

/**
 * @brief NWeb tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_NWEB (1ULL << 24)

/**
 * @brief Distributed audio tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_DISTRIBUTED_AUDIO (1ULL << 27)

/**
 * @brief File management tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_FILE_MANAGEMENT (1ULL << 29)

/**
 * @brief OHOS generic tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_OHOS (1ULL << 30)

/**
 * @brief Ability Manager tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_ABILITY_MANAGER (1ULL << 31)

/**
 * @brief Camera module tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_CAMERA (1ULL << 32)

/**
 * @brief Media module tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_MEDIA (1ULL << 33)

/**
 * @brief Image module tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_IMAGE (1ULL << 34)

/**
 * @brief Audio module tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_AUDIO (1ULL << 35)

/**
 * @brief Distributed data manager module tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_DISTRIBUTED_DATA (1ULL << 36)

/**
 * @brief Graphics module tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_GRAPHICS (1ULL << 38)

/**
 * @brief ARKUI development framework tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_ARKUI (1ULL << 39)

/**
 * @brief Notification module tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_NOTIFICATION (1ULL << 40)

/**
 * @brief MISC module tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_MISC (1ULL << 41)

/**
 * @brief Multimodal input module tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_MULTIMODAL_INPUT (1ULL << 42)

/**
 * @brief RPC tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_RPC (1ULL << 46)

/**
 * @brief ARK tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_ARK (1ULL << 47)

/**
 * @brief Window manager tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_WINDOW_MANAGER (1ULL << 48)

/**
 * @brief Distributed screen tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_DISTRIBUTED_SCREEN (1ULL << 50)

/**
 * @brief Distributed camera tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_DISTRIBUTED_CAMERA (1ULL << 51)

/**
 * @brief Distributed hardware framework tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_DISTRIBUTED_HARDWARE_FRAMEWORK (1ULL << 52)

/**
 * @brief Global resource manager tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_GLOBAL_RESOURCE_MANAGER (1ULL << 53)

/**
 * @brief Distributed hardware device manager tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_DISTRIBUTED_HARDWARE_DEVICE_MANAGER (1ULL << 54)

/**
 * @brief SA tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_SAMGR (1ULL << 55)

/**
 * @brief Power manager tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_POWER_MANAGER (1ULL << 56)

/**
 * @brief Distributed scheduler tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_DISTRIBUTED_SCHEDULER (1ULL << 57)

/**
 * @brief Distributed input tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_DISTRIBUTED_INPUT (1ULL << 59)

/**
 * @brief bluetooth tag.
 *
 * @since 12
 */
#define HIDEBUG_TRACE_TAG_BLUETOOTH (1ULL << 60)

/** @} */

#endif // HIVIEWDFX_HIDEBUG_TYPE_H
