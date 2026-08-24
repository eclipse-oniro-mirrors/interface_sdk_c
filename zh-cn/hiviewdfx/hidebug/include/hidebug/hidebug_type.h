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

#ifndef HIVIEWDFX_HIDEBUG_TYPE_H
#define HIVIEWDFX_HIDEBUG_TYPE_H
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

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief 错误码定义。用于HiDebug模块各功能接口的返回状态标识，包括成功、参数错误、权限问题、系统内部错误、设备不支持等多种情况。开发者可根据错误码定位问题原因并采取相应的错误处理措施。
 *
 * @since 12
 */
typedef enum HiDebug_ErrorCode {
/**
     * 成功。
     */
    HIDEBUG_SUCCESS = 0,
/**
     * 无效参数，可能的原因： 1.参数传值问题；2.参数类型问题。
     */
    HIDEBUG_INVALID_ARGUMENT = 401,
/**
     * 重复采集。
     */
    HIDEBUG_TRACE_CAPTURED_ALREADY = 11400102,
/**
     * 没有写文件的权限。
     */
    HIDEBUG_NO_PERMISSION = 11400103,
/**
     * 系统内部错误。
     */
    HIDEBUG_TRACE_ABNORMAL = 11400104,
/**
     * 当前没有trace正在运行。
     */
    HIDEBUG_NO_TRACE_RUNNING = 11400105,
    /**
     * trace文件存储达到限制。
     * @since 24
     */
    OH_HIDEBUG_TRACE_STORAGE_LIMIT = 11400120,
    /**
     * 传入符号解析函数的pc地址是无效的。
     * @since 20
     */
    HIDEBUG_INVALID_SYMBOLIC_PC_ADDRESS = 11400200,
    /**
     * 当前设备不支持。
     * @since 22
     */
    HIDEBUG_NOT_SUPPORTED = 11400300,
    /**
     * 当前进程正在采样。
     * @since 22
     */
    HIDEBUG_UNDER_SAMPLING = 11400301,
    /**
     * 采样资源不可用。
     * @since 22
     */
    HIDEBUG_RESOURCE_UNAVAILABLE = 11400302,
    /**
     * 资源采集启动/停止成功。
     * @since 24
     */
    HIDEBUG_RES_PROF_SUCCESS = 11400400,
    /**
     * 资源采集参数无效。
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_ARG = 11400410,
    /**
     * 资源采集最大持续时间参数无效。
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_MAX_DURATION = 11400411,
    /**
     * 资源采集过滤大小参数无效。
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_FILTER_SIZE = 11400412,
    /**
     * 资源采集最大回栈深度参数无效。
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_MAX_STACK_DEPTH = 11400413,
    /**
     * 资源采集统计间隔参数无效。
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_STATISTICS_INTERVAL = 11400414,
    /**
     * 资源采集采样大小参数无效。
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_SAMPLE_INTERVAL = 11400415,
    /**
     * 资源采集资源类型参数无效。
     * @since 24
     */
    HIDEBUG_RES_PROF_INVALID_RESOURCE_TYPE = 11400416,
    /**
     * 资源采集权限不足，采集资源的目标进程仅支持调用接口进程本身。
     * @since 24
     */
    HIDEBUG_RES_PROF_PERMISSION_DENIED = 11400420,
    /**
     * 资源采集重复启动。
     * @since 24
     */
    HIDEBUG_RES_PROF_ALREADY_STARTED = 11400421,
    /**
     * 资源采集未启动，停止失败。
     * @since 24
     */
    HIDEBUG_RES_PROF_NOT_STARTED = 11400422,
    /**
     * 资源采集进程数超出 4 个限制。
     * @since 24
     */
    HIDEBUG_RES_PROF_PROCESS_OVERLIMIT = 11400423,
    /**
     * 资源采集与命令行工具或系统采集任务冲突。
     * @since 24
     */
    HIDEBUG_RES_PROF_CONFLICT = 11400424,
    /**
     * 资源采集到达指定最大持续时间限制自动停止。
     * @since 24
     */
    HIDEBUG_RES_PROF_AUTO_STOPPED_BY_DURATION = 11400425,
    /**
     * 资源采集每日配额超出 10 次限制。
     * @since 24
     */
    HIDEBUG_RES_PROF_DAILY_QUOTA_EXCEEDED = 11400426,
    /**
     * 系统 CPU 处于高负载状态，CPU 占用率超过 70%。
     * @since 24
     */
    HIDEBUG_RES_PROF_CPU_OVERLOADED = 11400427,
    /**
     * 内存可用空间紧张，可用空间少于 15%。
     * @since 24
     */
    HIDEBUG_RES_PROF_MEM_PRESSURE_CRITICAL = 11400428,
    /**
     * 存储可用空间紧张，可用空间少于 15%。
     * @since 24
     */
    HIDEBUG_RES_PROF_STORAGE_PRESSURE_CRITICAL = 11400429,
    /**
     * 资源采集启动/停止失败。
     * @since 24
     */
    HIDEBUG_RES_PROF_FAILURE = 11400430,
    /**
     * @brief 无效的最大异步嵌套深度。
     *
     * @since 26.1.0
     */
    HIDEBUG_RES_PROF_INVALID_MAX_ASYNC_NESTING_DEPTH = 11400431,
    /**
     * @brief 无效的最大异步任务栈深度。
     *
     * @since 26.1.0
     */
    HIDEBUG_RES_PROF_INVALID_MAX_ASYNC_TASK_STACK_DEPTH = 11400432
} HiDebug_ErrorCode;

/**
 * @brief 当前进程所有线程的CPU使用率结构体定义。<br>使用场景：<br>应用性能监控：获取线程CPU使用率，监控应用的运行状态和性能瓶颈。<br>线程性能优化：分析各线程的CPU占用情况，优化线程调度和资源分配。<br>
 * 系统调试：在调试阶段追踪线程的CPU使用情况，定位性能问题。
 *
 * @since 12
 */
typedef struct HiDebug_ThreadCpuUsage {
    /**
     * 线程ID。
     */
    uint32_t threadId;
    /**
     * 线程CPU使用率百分比。
     */
    double cpuUsage;
    /**
     * 下一个线程的使用率信息。
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
 * @brief 系统内存信息结构类型定义。用于获取系统内存的总量、空闲量、可用量等关键信息，适用于系统性能分析、内存监控、故障诊断等场景，帮助开发者了解系统内存使用状况，优化内存管理策略。
 *
 * @since 12
 */
typedef struct HiDebug_SystemMemInfo {
    /**
     * 系统总的内存，以KB为单位。
     */
    uint32_t totalMem;
    /**
     * 系统空闲的内存，以KB为单位。
     */
    uint32_t freeMem;
    /**
     * 系统可用的内存，以KB为单位。
     */
    uint32_t availableMem;
} HiDebug_SystemMemInfo;

/**
 * @brief 应用程序进程本机内存信息结构类型定义。
 *
 * @since 12
 */
typedef struct HiDebug_NativeMemInfo {
    /**
     * 进程比例集大小内存，以KB为单位。
     */
    uint32_t pss;
    /**
     * 虚拟内存大小，以KB为单位。
     */
    uint32_t vss;
    /**
     * 常驻集大小，以KB为单位。
     */
    uint32_t rss;
    /**
     * 共享脏内存的大小，以KB为单位。
     */
    uint32_t sharedDirty;
    /**
     * 专用脏内存的大小，以KB为单位。
     */
    uint32_t privateDirty;
    /**
     * 共享干净内存的大小，以KB为单位。
     */
    uint32_t sharedClean;
    /**
     * 专用干净内存的大小，以KB为单位。
     */
    uint32_t privateClean;
} HiDebug_NativeMemInfo;

/**
 * @brief 应用程序进程内存限制结构类型定义。
 *
 * @since 12
 */
typedef struct HiDebug_MemoryLimit {
    /**
     * 应用程序进程可用的物理内存限制，以KB为单位，实际当前系统未对进程可用物理内存做限制，但是进程的可用物理内存仍然不会超过设备的实际最大可用物理内存，当前设备的物理内存使用情况可通过
     * {@link OH_HiDebug_GetSystemMemInfo}获取。
     */
    uint64_t rssLimit;
    /**
     * 应用程序进程的虚拟内存限制，以KB为单位。
     */
    uint64_t vssLimit;
} HiDebug_MemoryLimit;

/**
 * @brief 采集trace线程的类型。
 *
 * @since 12
 */
typedef enum HiDebug_TraceFlag {
/**
     * 只采集当前应用主线程。
     */
    HIDEBUG_TRACE_FLAG_MAIN_THREAD = 1,
/**
     * 采集当前应用下所有线程。
     */
    HIDEBUG_TRACE_FLAG_ALL_THREADS = 2
} HiDebug_TraceFlag;

/**
 * @brief 请求trace采集的配置结构类型定义。用于在应用性能分析和调试场景中配置trace采集参数，如定位应用启动慢、UI卡顿、CPU占用高等性能问题。
 *
 * @since 24
 */
typedef struct OH_HiDebug_RequestTraceConfig {
    /**
     * 采集trace输出的文件名前缀。文件名前缀只取字符串前20个字符，超过部分将抛弃。前20个字符只包含大小写字母和下划线，若不符合则默认为空字符串。
     * @since 24
     */
    const char* identifier;
    /**
     * trace文件的缓存大小，以KB为单位。取值范围为[1024, 15360]，传入参数超过取值范围，参数将被设置为最近的边界值。
     * @since 24
     */
    uint32_t bufferSizeKb;
    /**
     * trace采集时长，以ms为单位。取值范围为[1000, 15000]，传入参数超过取值范围，参数将被设置为最近的边界值。
     * @since 24
     */
    uint32_t durationMs;
    /**
     * 预留字段，可以设置为0。
     * @since 24
     */
    uint32_t reserved;
} OH_HiDebug_RequestTraceConfig;

/**
 * @brief 请求trace采集的回调类型定义。
 *
 * @param errorCode 返回结果码，参考{@link HiDebug_ErrorCode}。
 * @param filePath 返回采集的trace文件，失败时可能是空指针。
 * @since 24
 */
typedef void (*OH_HiDebug_RequestTraceCallback)(HiDebug_ErrorCode errorCode, const char* filePath);

/**
 * @brief 应用程序进程可替换/恢复的HiDebug_MallocDispatch表结构类型定义。通过该结构体，开发者可以自定义内存管理函数指针，实现对进程内存分配和释放的监控与定制。主要特点包括：支持动态替换和恢复内存管理函数、
 * 提供全面的内存操作接口（malloc、calloc、realloc、free、mmap、munmap）、不影响系统默认内存管理行为。使用场景包括：内存泄漏检测、内存使用性能分析、自定义内存分配策略、内存安全监控等。
 * 能够帮助开发者及时发现和解决内存问题，提升应用稳定性和性能。
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
 * @brief js栈帧内容的定义。用于在性能分析和调试场景中，记录js调用栈的帧信息，包括代码位置、函数名称、映射区域等关键信息。
 *
 * @since 20
 */
typedef struct HiDebug_JsStackFrame {
    /**
     * 相对pc地址。当前pc相对于其所在的映射区域（如可执行文件或共享库）起始地址的偏移量。
     */
    uint64_t relativePc;

    /**
     * 代码所在的行号。当前栈帧对应的代码位于文件的具体行位置。
     */
    int32_t line;

    /**
     * 代码所在的列号。当前栈帧对应的代码在指定行的具体列位置。
     */
    int32_t column;

    /**
     * 映射名称。当前栈帧所属的映射区域的名称。
     */
    const char* mapName;

    /**
     * 函数名称。当前栈帧对应的函数的名称。
     */
    const char* functionName;

    /**
     * URL地址。当前栈帧对应代码的文件的URL，无论是本地文件路径还是远程服务器上的文件地址，通过该URL能找到对应的代码文件。
     */
    const char* url;

    /**
     * 包名。当前栈帧对应的代码所属包的名称。
     */
    const char* packageName;
} HiDebug_JsStackFrame;

/**
 * @brief native栈帧内容的定义。
 *
 * @since 20
 */
typedef struct HiDebug_NativeStackFrame {
    /**
     * 相对pc地址。当前pc相对于其所在的映射区域（如可执行文件或共享库）起始地址的偏移量。
     */
    uint64_t relativePc;

    /**
     * 函数偏移量。当前栈帧对应的函数在其所在的映射区域（如可执行文件或共享库）内的偏移量。
     */
    uint64_t funcOffset;

    /**
     * 映射名称。当前栈帧所属的映射区域的名称。
     */
    const char* mapName;

    /**
     * 函数名称。当前栈帧对应的函数的名称。
     */
    const char* functionName;

    /**
     * 构建标识符。当前映射区域（如可执行文件或共享库）相关的唯一标识符。在调试和符号解析时，buildId可确保使用的符号文件与实际运行的二进制文件版本一致。
     */
    const char* buildId;

    /**
     * 保留字段。为了后续扩展预留的字段。
     */
    const char* reserved;
} HiDebug_NativeStackFrame;

/**
 * @brief 栈帧类型的枚举值定义。
 *
 * @since 20
 */
typedef enum HiDebug_StackFrameType {
/**
     * js类型栈帧。
     */
    HIDEBUG_STACK_FRAME_TYPE_JS = 1,
/**
     * native类型栈帧。
     */
    HIDEBUG_STACK_FRAME_TYPE_NATIVE = 2
} HiDebug_StackFrameType;

/**
 * @brief 栈帧内容的定义。该结构体用于表示调试时的栈帧信息，支持获取当前栈的类型以及对应的js栈帧或Native栈帧内容，帮助开发者进行问题定位和调试分析。
 *
 * @since 20
 */
typedef struct HiDebug_StackFrame {
    /**
     * 当前栈的类型。
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
 * @brief 用于栈回溯及栈解析的对象。该对象封装了栈回溯所需的上下文信息，包括调用栈地址、线程状态等数据，通过相关接口可获取详细的栈帧信息和符号解析结果。该对象通过HiDebug相关接口创建，使用后需要调用对应的销毁接口释放资源。
 *
 * @since 20
 */
typedef struct HiDebug_Backtrace_Object__* HiDebug_Backtrace_Object;

/**
 * @brief 应用图形显存占用详情的结构定义。
 *
 * @since 21
 */
typedef struct HiDebug_GraphicsMemorySummary {
    /**
     * gl内存大小，RenderService渲染进程加载所需资源占用的内存，例如图片、纹理等，以KB为单位。
     */
    uint32_t gl;

    /**
     * graph内存大小，进程统计的DMA内存占用，包括直接通过接口申请的DMA buffer和通过allocator_host申请的DMA buffer，以KB为单位。
     */
    uint32_t graph;
} HiDebug_GraphicsMemorySummary;

/**
 * @brief 采样配置的结构定义。
 *
 * @since 22
 */
typedef struct HiDebug_ProcessSamplerConfig {
    /**
     * 待采样的线程号数组。最大支持10个线程的同时采样，数组长度超出时，将取前10个线程进行采样。
     */
    uint32_t* tids;

    /**
     * tids指向的数组长度。该值必须与tids数组的实际长度一致。
     */
    uint32_t size;

    /**
     * 采样频率，取值范围[1-200]，单位Hz。超出取值范围时取默认值100。
     */
    uint32_t frequency;

    /**
     * 采样时长，取值范围[1000-10000]，单位ms。小于1000时，接口调用异常；大于10000时，取10000。
     */
    uint32_t duration;

    /**
     * 保留字段。
     */
    uint32_t reserved;
} HiDebug_ProcessSamplerConfig;

/**
 * @brief 维测信息数据类型的枚举。
 *
 * @since 23
 */
typedef enum HiDebug_CrashObjType {
/**
      * 字符串
      */
    HIDEBUG_CRASHOBJ_STRING = 0,
/**
      * 64字节内存块
      */
    HIDEBUG_CRASHOBJ_MEMORY_64B = 1,
/**
      * 256字节内存块
      */
    HIDEBUG_CRASHOBJ_MEMORY_256B = 2,
/**
     * 1024字节内存块
     */
    HIDEBUG_CRASHOBJ_MEMORY_1024B = 3,
/**
      * 2048字节内存块
      */
    HIDEBUG_CRASHOBJ_MEMORY_2048B = 4,
/**
     * 4096字节内存块
     */
    HIDEBUG_CRASHOBJ_MEMORY_4096B = 5
 } HiDebug_CrashObjType;

/**
 * @brief 定义资源采集类型的枚举。
 *
 * @since 24
 */
typedef enum OH_HiDebug_ResourceType {
    /**
     * 文件描述符
     * @since 24
     */
    OH_RES_TYPE_FD,
    /**
     * 线程
     * @since 24
     */
    OH_RES_TYPE_THREAD,
    /**
     * Native 内存
     * @since 24
     */
    OH_RES_TYPE_NATIVE,
    /**
     * GPU 内存
     * @since 24
     */
    OH_RES_TYPE_GPU,
    /**
     * 全局句柄
     * @since 24
     */
    OH_RES_TYPE_GLOBAL_HANDLE,
    /**
     * @brief DMA内存
     *
     * @since 26.1.0
     */
    OH_RES_TYPE_DMA,

    /**
     * @brief 匿名共享内存
     *
     * @since 26.1.0
     */
    OH_RES_TYPE_ASHMEM,

    /**
     * @brief 组合堆
     *
     * @since 26.1.0
     */
    OH_RES_TYPE_COMPOSITE_HEAP
} OH_HiDebug_ResourceType;

/**
 * @brief 封装单次资源采集的结果。
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
 * @brief 定义资源采集回调函数。
 *
 * @param result 资源采集回调函数的参数。
 * @since 24
 */
typedef void (*OH_HiDebug_ProfilingCallback)(OH_HiDebug_ProfilingResult* result);

/**
 * @brief 定义资源采集配置结构体类型。
 *
 * @since 24
 */
typedef struct OH_HiDebug_ResProfilerConfig {
    /**
     * 最大采集时长，取值范围为 [1, 3600]，单位为秒。<br>传入参数超出取值范围，接口将返回错误码{@link HIDEBUG_RES_PROF_INVALID_MAX_DURATION}。
     * @since 24
     */
    uint32_t maxDuration;
    /**
     * 过滤大小，取值范围为 [1, 4294967295]，单位为字节。<br>传入参数超出取值范围，接口将返回错误码{@link HIDEBUG_RES_PROF_INVALID_FILTER_SIZE}。
     * @since 24
     */
    uint32_t filterSize;
    /**
     * 最大栈追踪深度，取值范围为 [0, 30]，单位为帧。建议根据实际需求设置合适的栈深度，深度越大采集开销越大。<br>传入参数超出取值范围，接口将返回错误码
     * {@link HIDEBUG_RES_PROF_INVALID_MAX_STACK_DEPTH}。
     * @since 24
     */
    uint32_t maxStackDepth;
    /**
     * 统计间隔，取值范围为 [0, 3600]，单位为秒。<br>传入参数超出取值范围，接口将返回错误码{@link HIDEBUG_RES_PROF_INVALID_STATISTICS_INTERVAL}。
     * @since 24
     */
    uint32_t statisticsInterval;
    /**
     * 采样大小，取值范围为 [384, 4294967295]，单位为字节。<br>在采样模式下，如果内存分配大小小于等于采样大小，则概率性采样，否则全量采样。<br>传入参数超出取值范围，接口将返回错误码
     * {@link HIDEBUG_RES_PROF_INVALID_SAMPLE_INTERVAL}。
     * @since 24
     */
    uint32_t sampleInterval;
} OH_HiDebug_ResProfilerConfig;

/**
 * @brief 内存监听回调的类型枚举。开发者根据回调类型处理相关逻辑。
 *
 * @since 26.0.0
 */
typedef enum OH_HiDebug_MemListenerType {
    /**
     * 无特定操作，仅通知回调。
     * @since 26.0.0
     */
    OH_HIDEBUG_DO_NOTHING = 0,
    /**
     * 垃圾回收（GC）操作。
     * @since 26.0.0
     */
    OH_HIDEBUG_RUNNING_GC = 1,
    /**
     * 导出内存快照。
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