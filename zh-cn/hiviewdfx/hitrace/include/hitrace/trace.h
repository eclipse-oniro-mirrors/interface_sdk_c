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
 * @brief HiTraceMeter和HiTraceChain模块接口定义，通过这些接口实现性能打点和分布式跟踪功能。支持应用性能分析、跨服务调用链追踪、性能瓶颈定
 * 位、等场景，能够解决分布式系统中调用链路难以追踪、性能问题难以定位的问题，提升系统可观测性和问题排查效率。性能打点通过在代码关键位置插入标记，
 * 记录函数执行时间；分布式跟踪通过HiTraceId实现跨线程、跨进程、跨设备的调用链追踪。
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
 * @brief HiTraceId是否有效标志。
 *
 * @since 12
 */
typedef enum HiTraceId_Valid {
    /**
     * @brief 无效HiTraceId。
     *
     * @since 12
     */
    HITRACE_ID_INVALID = 0,

    /**
     * @brief 有效HiTraceId。
     *
     * @since 12
     */
    HITRACE_ID_VALID = 1
} HiTraceId_Valid;

/**
 * @brief HiTrace版本号。
 *
 * @since 12
 */
typedef enum HiTrace_Version {
    /**
     * @brief 版本1。
     *
     * @since 12
     */
    HITRACE_VER_1 = 0
} HiTrace_Version;

/**
 * @brief HiTrace跟踪标志。
 *
 * @since 12
 */
typedef enum HiTrace_Flag {
    /**
     * @brief 默认标志。
     *
     * @since 12
     */
    HITRACE_FLAG_DEFAULT = 0,

    /**
     * @brief 异步调用标志。
     * 设置该标志，同时跟踪同步和异步调用；默认只跟踪同步调用。
     *
     * @since 12
     */
    HITRACE_FLAG_INCLUDE_ASYNC = 1 << 0,

    /**
     * @brief 无分支标志。
     * 设置该标志，不创建分支信息；默认创建分支信息。
     *
     * @since 12
     */
    HITRACE_FLAG_DONOT_CREATE_SPAN = 1 << 1,

    /**
     * @brief 埋点标志。
     * 调试场景下设置该标志，调用信息埋点接口{@link OH_HiTrace_Tracepoint}时，会打印埋点信息hilog日志；默认不打印埋点信息hilog日志。
     *
     * @since 12
     */
    HITRACE_FLAG_TP_INFO = 1 << 2,

    /**
     * @brief 无开始结束信息标志。
     * 调试场景下设置该标志，调用开始跟踪接口{@link OH_HiTrace_BeginChain}和结束跟踪接口{@link OH_HiTrace_EndChain}时，分别会打印开始、
     * 结束跟踪信息hilog日志；
     * 默认不打印开始、结束跟踪信息hilog日志。
     *
     * @since 12
     */
    HITRACE_FLAG_NO_BE_INFO = 1 << 3,

    /**
     * @brief 日志关联标志。
     * 设置该标志，不会在hilog日志中附加HiTraceId信息；默认会在hilog日志中附加HiTraceId信息。
     *
     * @since 12
     */
    HITRACE_FLAG_DONOT_ENABLE_LOG = 1 << 4,

    /**
     * @brief 故障触发标志。预置标志，暂未启用。
     *
     * @since 12
     */
    HITRACE_FLAG_FAULT_TRIGGER = 1 << 5,

    /**
     * @brief 设备间埋点标志。{@link HITRACE_FLAG_TP_INFO}的一个子集，调试场景下使用。
     * 当已设置{@link HITRACE_FLAG_TP_INFO}标志时，{@link HITRACE_FLAG_D2D_TP_INFO}标志不生效；当未设置
     * {@link HITRACE_FLAG_TP_INFO}标志时，设置{@link HITRACE_FLAG_D2D_TP_INFO}标志，此时调用信息埋点接口
     * {@link OH_HiTrace_Tracepoint}，仅当mode参数为设备间通信
     * {@link HITRACE_CM_DEVICE}的情况下，会打印埋点信息hilog日志。
     *
     * @since 12
     */
    HITRACE_FLAG_D2D_TP_INFO = 1 << 6
} HiTrace_Flag;

/**
 * @brief 跟踪埋点类型枚举。
 *
 * @since 12
 */
typedef enum HiTrace_Tracepoint_Type {
    /**
     * @brief 客户端发送。
     *
     * @since 12
     */
    HITRACE_TP_CS = 0,

    /**
     * @brief 客户端接收。
     *
     * @since 12
     */
    HITRACE_TP_CR = 1,

    /**
     * @brief 服务端发送。
     *
     * @since 12
     */
    HITRACE_TP_SS = 2,

    /**
     * @brief 服务端接收。
     *
     * @since 12
     */
    HITRACE_TP_SR = 3,

    /**
     * @brief 通用类型，标识HITRACE_TP_CS、HITRACE_TP_CR、HITRACE_TP_SS、HITRACE_TP_SR四种场景之外的埋点。
     *
     * @since 12
     */
    HITRACE_TP_GENERAL = 4
} HiTrace_Tracepoint_Type;

/**
 * @brief 跟踪通信类型枚举。
 *
 * @since 12
 */
typedef enum HiTrace_Communication_Mode {
    /**
     * @brief 默认通信类型。
     *
     * @since 12
     */
    HITRACE_CM_DEFAULT = 0,

    /**
     * @brief 线程间通信。
     *
     * @since 12
     */
    HITRACE_CM_THREAD = 1,

    /**
     * @brief 进程间通信。
     *
     * @since 12
     */
    HITRACE_CM_PROCESS = 2,

    /**
     * @brief 设备间通信。
     *
     * @since 12
     */
    HITRACE_CM_DEVICE = 3
} HiTrace_Communication_Mode;

/**
 * @brief HiTrace输出级别。低于系统跟踪输出级别阈值的打点将不会生效。log版本阈值为{@link HITRACE_LEVEL_INFO}；nolog版本阈值为
 * {@link HITRACE_LEVEL_COMMERCIAL}。
 *
 * @since 19
 */
typedef enum HiTrace_Output_Level {
    /**
     * @brief 仅用于调试的输出级别，优先级最低。
     *
     * @since 19
     */
    HITRACE_LEVEL_DEBUG = 0,

    /**
     * @brief 用于log版本的输出级别。
     *
     * @since 19
     */
    HITRACE_LEVEL_INFO = 1,

    /**
     * @brief 用于log版本的输出级别，优先级高于{@link HITRACE_LEVEL_INFO}。
     *
     * @since 19
     */
    HITRACE_LEVEL_CRITICAL = 2,

    /**
     * @brief 用于nolog版本的输出级别，优先级最高。
     *
     * @since 19
     */
    HITRACE_LEVEL_COMMERCIAL = 3,

    /**
     * @brief 输出级别范围限制。
     *
     * @since 19
     */
    HITRACE_LEVEL_MAX = HITRACE_LEVEL_COMMERCIAL
} HiTrace_Output_Level;

/**
 * @brief 用于标识调用链的结构体。
 *
 * @since 12
 */
typedef struct HiTraceId {
#if __BYTE_ORDER == __LITTLE_ENDIAN
    /**
     * HiTraceId是否有效，1表示有效，0表示无效。用于判断HiTraceId结构体是否包含有效的跟踪信息。
     * @since 12
     */
    uint64_t valid : 1;
    /**
     * HiTraceId的版本号，用于表示HiTraceId结构体的版本。不同版本可能有不同的字段布局或功能特性。
     * @since 12
     */
    uint64_t ver : 3;
    /**
     * HiTraceId的跟踪链标识，用于唯一标识跨进程/跨设备的调用链。在整个分布式跟踪过程中保持不变，用于关联同一业务流程的所有跟踪信息。
     * @since 12
     */
    uint64_t chainId : 60;
    /**
     * HiTraceId的跟踪标识位，用于指定跟踪选项或特性。不同的标志位组合可以控制跟踪的详细程度和行为。
     * @since 12
     */
    uint64_t flags : 12;
    /**
     * HiTraceId的分支标识，用于标识调用链中的当前调用节点。每次创建新的分支时会产生新的spanId，用于构建调用树结构。
     * @since 12
     */
    uint64_t spanId : 26;
    /**
     * HiTraceId的父分支标识，用于标识调用链中当前节点的父节点。通过parentSpanId可以追溯调用的来源，实现调用链的层级关系。
     * @since 12
     */
    uint64_t parentSpanId : 26;
#elif __BYTE_ORDER == __BIG_ENDIAN
    /**
     * HiTraceId的跟踪链标识，用于唯一标识跨进程/跨设备的调用链。在整个分布式跟踪过程中保持不变，用于关联同一业务流程的所有跟踪信息。
     * @since 12
     */
    uint64_t chainId : 60;
    /**
     * HiTraceId的版本号，用于表示HiTraceId结构体的版本。不同版本可能有不同的字段布局或功能特性。
     * @since 12
     */
    uint64_t ver : 3;
    /**
     * HiTraceId是否有效，1表示有效，0表示无效。用于判断HiTraceId结构体是否包含有效的跟踪信息。
     * @since 12
     */
    uint64_t valid : 1;
    /**
     * HiTraceId的父分支标识，用于标识调用链中当前节点的父节点。通过parentSpanId可以追溯调用的来源，实现调用链的层级关系。
     * @since 12
     */
    uint64_t parentSpanId : 26;
    /**
     * HiTraceId的分支标识，用于标识调用链中的当前调用节点。每次创建新的分支时会产生新的spanId，用于构建调用树结构。
     * @since 12
     */
    uint64_t spanId : 26;
    /**
     * HiTraceId的跟踪标识位，用于指定跟踪选项或特性。不同的标志位组合可以控制跟踪的详细程度和行为。
     * @since 12
     */
    uint64_t flags : 12;
#else
#error "ERROR: No BIG_LITTLE_ENDIAN defines."
#endif
} HiTraceId;

/**
 * @brief 定义应用trace捕获开关状态切换时的回调函数类型。
 *
 * @param traceStatus 当前应用trace捕获开关状态。
 *     true：开启；false：关闭。
 * @since 22
 */
typedef void (*OH_HiTrace_TraceEventListener)(bool traceStatus);

/**
 * @brief 开始跟踪。
 * 当前线程TLS（Thread Local Storage，线程本地存储）中不存在有效的HiTraceId时，生成有效的HiTraceId并设置到当前线程TLS中，返回该HiTraceId；
 * 当前线程TLS中已存在有效的HiTraceId时，不会开始新的跟踪，返回各属性值均为0的无效HiTraceId。
 *
 * @param name 跟踪业务名，用于标识被跟踪的业务流程。建议使用简洁明了的名称，便于在分析时识别。
 * @param flags 跟踪标志组合，见{@link HiTrace_Flag}。
 * @return {@link HiTraceId}结构体。
 * @since 12
 */
HiTraceId OH_HiTrace_BeginChain(const char *name, int flags);

/**
 * @brief 结束跟踪。
 * 结束跟踪并将当前线程TLS中的HiTraceId设置为无效。
 *
 * @since 12
 */
void OH_HiTrace_EndChain();

/**
 * @brief
 * Obtains the {@link HiTraceId} in the TLS of the current thread.
 *
 * @return {@link HiTraceId}结构体。
 * @since 12
 */
HiTraceId OH_HiTrace_GetId();

/**
 * @brief
 * Sets the given {@link HiTraceId} to the TLS of the current thread. If the input parameter is invalid, no
 * operation is performed.
 *
 * @param id 要设置的{@link HiTraceId}。
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
 * @brief 创建跟踪分支。
 * 创建一个{@link HiTraceId}，使用当前线程TLS中的chainId、spanId初始化其chainId、parentSpanId，并为其生成一个新的spanId。
 *
 * @return {@link HiTraceId}结构体。
 * @since 12
 */
HiTraceId OH_HiTrace_CreateSpan(void);

/**
 * @brief HiTraceMeter跟踪信息埋点。
 * type为客户端发送{@link HITRACE_TP_CS}和服务端接收{@link HITRACE_TP_SR}时，进行同步HiTraceMeter开始打点；type为客户端接收
 * {@link HITRACE_TP_CR}和服务端发送{@link HITRACE_TP_SS}时，进行同步HiTraceMeter结束打点；type为通用类型
 * {@link HITRACE_TP_GENERAL}时，不会进行HiTraceMeter打点。 type为客户端发送{@link HITRACE_TP_CS}和客户端接收
 * {@link HITRACE_TP_CR}的信息埋点需配套使用；type为服务端接收{@link HITRACE_TP_SR}和服务端发送{@link HITRACE_TP_SS}的信息埋点需
 * 配套使用。否则，HiTraceMeter开始与结束打点无法正常匹配。
 *
 * @param mode 跟踪通信模式，见{@link HiTrace_Communication_Mode}。
 * @param type 跟踪信息类型，见{@link HiTrace_Tracepoint_Type}。
 * @param id 实施信息埋点操作的{@link HiTraceId}。
 * @param fmt HiTraceMeter打点操作传入的trace说明信息的格式化字符串，遵循 **ISO C（C89/C99/C17）printf 格式规范**。
 * @since 12
 */
void OH_HiTrace_Tracepoint(
    HiTrace_Communication_Mode mode, HiTrace_Tracepoint_Type type, const HiTraceId *id, const char *fmt, ...);

/**
 * @brief 初始化{@link HiTraceId}。
 *
 * @param id 需要初始化的{@link HiTraceId}。
 * @since 12
 */
void OH_HiTrace_InitId(HiTraceId *id);

/**
 * @brief 根据字节数组创建{@link HiTraceId}。
 *
 * @param id 需要创建的{@link HiTraceId}。
 * @param pIdArray 字节数组。
 * @param len 字节数组长度。
 * @since 12
 */
void OH_HiTrace_IdFromBytes(HiTraceId *id, const uint8_t *pIdArray, int len);

/**
 * @brief 判断{@link HiTraceId}是否有效。
 *
 * @param id 需要判断是否有效的{@link HiTraceId}。
 * @return true：{@link HiTraceId}有效；false：{@link HiTraceId}无效。
 * @since 12
 */
bool OH_HiTrace_IsIdValid(const HiTraceId *id);

/**
 * @brief 判断{@link HiTraceId}是否启用了跟踪标志flag。
 *
 * @param id 需要判断指定跟踪标志是否启用的{@link HiTraceId}。
 * @param flag 指定的跟踪标志，见{@link HiTrace_Flag}。
 * @return true：{@link HiTraceId}已启用flag；false：{@link HiTraceId}未启用flag。
 * @since 12
 */
bool OH_HiTrace_IsFlagEnabled(const HiTraceId *id, HiTrace_Flag flag);

/**
 * @brief 启用{@link HiTraceId}中指定的跟踪标志。
 *
 * @param id 需要启用指定跟踪标志的{@link HiTraceId}。
 * @param flag 指定的跟踪标志，见{@link HiTrace_Flag}。
 * @since 12
 */
void OH_HiTrace_EnableFlag(const HiTraceId *id, HiTrace_Flag flag);

/**
 * @brief 获取{@link HiTraceId}中设置的跟踪标志位。
 *
 * @param id 需要获取跟踪标志位的{@link HiTraceId}。
 * @return {@link HiTraceId}中设置的跟踪标志位。
 * @since 12
 */
int OH_HiTrace_GetFlags(const HiTraceId *id);

/**
 * @brief 设置跟踪标志位到{@link HiTraceId}中。
 *
 * @param id 需要设置跟踪标志位的{@link HiTraceId}。
 * @param flags 指定的跟踪标志位，见{@link HiTrace_Flag}。
 * @since 12
 */
void OH_HiTrace_SetFlags(HiTraceId *id, int flags);

/**
 * @brief 获取{@link HiTraceId}中的跟踪链ID。
 *
 * @param id 需要获取跟踪链ID的{@link HiTraceId}。
 * @return 跟踪链ID。
 * @since 12
 */
uint64_t OH_HiTrace_GetChainId(const HiTraceId *id);

/**
 * @brief 设置跟踪链ID到{@link HiTraceId}中。
 *
 * @param id 需要设置跟踪链ID的{@link HiTraceId}。
 * @param chainId 需要设置的跟踪链ID。
 * @since 12
 */
void OH_HiTrace_SetChainId(HiTraceId *id, uint64_t chainId);

/**
 * @brief 获取当前{@link HiTraceId}中的分支ID。
 *
 * @param id 需要获取分支ID的{@link HiTraceId}。
 * @return {@link HiTraceId}中设置的分支ID。
 * @since 12
 */
uint64_t OH_HiTrace_GetSpanId(const HiTraceId *id);

/**
 * @brief 设置分支ID到{@link HiTraceId}中。
 *
 * @param id 需要设置分支ID的{@link HiTraceId}。
 * @param spanId 需要设置的分支ID。
 * @since 12
 */
void OH_HiTrace_SetSpanId(HiTraceId *id, uint64_t spanId);

/**
 * @brief 获取当前{@link HiTraceId}中的父分支ID。
 *
 * @param id 需要获取父分支ID的{@link HiTraceId}。
 * @return {@link HiTraceId}中设置的父分支ID。
 * @since 12
 */
uint64_t OH_HiTrace_GetParentSpanId(const HiTraceId *id);

/**
 * @brief 设置{@link HiTraceId}结构的parentSpanId字段。
 *
 * @param id 需要设置父分支ID的{@link HiTraceId}。
 * @param parentSpanId 需要设置的父分支ID。
 * @since 12
 */
void OH_HiTrace_SetParentSpanId(HiTraceId *id, uint64_t parentSpanId);

/**
 * @brief 将{@link HiTraceId}转换为字节数组，用于缓存或者通信传递。
 *
 * @param id 需要转换的{@link HiTraceId}。
 * @param pIdArray 字节数组。
 * @param len 字节数组长度。
 * @return 转换后的字节数组长度。
 * @since 12
 */
int OH_HiTrace_IdToBytes(const HiTraceId* id, uint8_t* pIdArray, int len);

/**
 * @brief 标记一个同步跟踪耗时任务的开始。
 * 同步跟踪打点接口{@link OH_HiTrace_StartTrace}和{@link OH_HiTrace_FinishTrace}必须配对使用。
 * {@link OH_HiTrace_StartTrace}和{@link OH_HiTrace_FinishTrace}函数对可以嵌套使用，跟踪解析时使用栈式数据结构进行匹配。
 * 从API version 19开始，建议使用{@link OH_HiTrace_StartTraceEx}接口，以便分级控制跟踪输出。
 *
 * @param name 跟踪的名字。
 *     由于单条trace记录的总长度限制为512Byte，超出部分将被截断，建议name的长度不要超过420Byte。
 * @since 10
 */
void OH_HiTrace_StartTrace(const char *name);

/**
 * @brief 标记一个同步跟踪耗时任务的结束。
 * 必须和{@link OH_HiTrace_StartTrace}配对使用。跟踪解析时，和其前执行流程中最近的{@link OH_HiTrace_StartTrace}进行匹配。
 * 从API version 19开始，建议使用{@link OH_HiTrace_FinishTraceEx}接口，以便分级控制跟踪输出。
 *
 * @since 10
 */
void OH_HiTrace_FinishTrace(void);

/**
 * @brief 标记一个异步跟踪耗时任务的开始。
 * 用于在异步操作前调用进行开始打点，异步跟踪开始和结束数据由于不是顺序发生的，所以解析时需要通过一个唯一的taskId进行识别。
 * 必须和{@link OH_HiTrace_FinishAsyncTrace}配对使用，参数name和taskId相同的开始与结束打点相匹配，构成一个异步跟踪耗时任务。
 * 如果有多个相同name的任务需要跟踪或者对同一个任务跟踪多次，并且任务同时被执行，则每次调用的taskId需不相同。
 * 如果具有相同name的任务是串行执行的，则taskId可以相同。
 * 从API version 19开始，建议使用{@link OH_HiTrace_StartAsyncTraceEx}接口，以便分级控制跟踪输出与跟踪聚类。
 *
 * @param name 异步跟踪任务的名字，用于标识要测量的异步操作，需与对应的结束接口的name参数相同。
 * @param taskId 异步跟踪的ID。 异步跟踪开始和结束由于不是顺序发生的，所以需要通过name和每次执行唯一的taskId进行开始和结束的匹配。
 * @since 10
 */
void OH_HiTrace_StartAsyncTrace(const char *name, int32_t taskId);

/**
 * @brief 标记一个异步跟踪耗时任务的结束。
 * 在异步操作完成后如回调函数中调用，进行结束打点。
 * 和{@link OH_HiTrace_StartAsyncTrace}配对使用，参数name和taskId必须与异步跟踪的开始打点接口的对应参数值保持一致。
 * 从API version 19开始，建议使用{@link OH_HiTrace_FinishAsyncTraceEx}接口，以便分级控制跟踪输出。
 *
 * @param name 异步跟踪任务的名字，需与对应的开始接口的name参数保持一致，用于匹配对应的异步跟踪任务。
 * @param taskId 异步跟踪的ID。异步跟踪开始和结束由于不是顺序发生的，所以需要通过name和每次执行唯一的taskId进行开始和结束的匹配。
 * @since 10
 */
void OH_HiTrace_FinishAsyncTrace(const char *name, int32_t taskId);

/**
 * @brief 用于跟踪给定整数变量名和整数值。
 * 多次执行该接口可以跟踪给定整数变量在不同时刻的数值变化。
 * 从API version 19开始，建议使用{@link OH_HiTrace_CountTraceEx}接口，以便分级控制跟踪输出。
 *
 * @param name 整数变量跟踪的名字，不必与真实变量名相同。
 *     由于单条trace记录的总长度限制为512Byte，超出部分将被截断，建议name的长度不要超过420Byte。
 * @param count 要记录的整数值，用于跟踪该变量在不同时刻的数值变化。
 * @since 10
 */
void OH_HiTrace_CountTrace(const char *name, int64_t count);

/**
 * @brief 标记一个同步跟踪耗时任务的开始，分级控制跟踪输出。
 * 同步跟踪打点接口{@link OH_HiTrace_StartTraceEx}和{@link OH_HiTrace_FinishTraceEx}必须配对使用。
 * {@link OH_HiTrace_StartTraceEx}和{@link OH_HiTrace_FinishTraceEx}函数对可以嵌套使用，跟踪解析时使用栈式数据结构进行匹配。
 *
 * @param level 跟踪输出级别。低于系统跟踪输出级别阈值的打点将不会生效。log版本阈值为{@link HITRACE_LEVEL_INFO}；nolog版本阈值为
 * {@link HITRACE_LEVEL_COMMERCIAL}。
 * @param name 同步跟踪的名字。由于单条trace记录的总长度限制为512Byte，超出部分将被截断，建议name和customArgs的长度之和不要超过420Byte。
 * @param customArgs 自定义键值对参数，用于附加额外的跟踪信息，多个键值对使用逗号分隔，例'key1=value1,key2=value2'。这些参数可以在性能分
 * 析时帮助过滤或标记特定的跟踪点。由于单条trace记录的总长度限制为512Byte，超出部分将被截断，建议name和customArgs的长度之和不要超过420Byte。
 * @since 19
 */
void OH_HiTrace_StartTraceEx(HiTrace_Output_Level level, const char* name, const char* customArgs);

/**
 * @brief 标记一个同步跟踪耗时任务的结束，分级控制跟踪输出。必须和{@link OH_HiTrace_StartTraceEx}配对使用，参数level必须与同步跟踪的开始
 * 打点接口{@link OH_HiTrace_StartTraceEx}的对应参数值一致。跟踪数据解析时，和其前执行流程中最近的{@link OH_HiTrace_StartTraceEx}进行
 * 匹配。
 *
 * @param level 跟踪输出级别。
 * @since 19
 */
void OH_HiTrace_FinishTraceEx(HiTrace_Output_Level level);

/**
 * @brief 标记一个异步跟踪耗时任务的开始，分级控制跟踪输出。
 * 用于在异步操作执行前进行开始打点，异步跟踪开始和结束数据由于不是顺序发生的，所以解析时需要通过一个唯一的taskId进行识别。
 * 和{@link OH_HiTrace_FinishAsyncTraceEx}配对使用，参数name和taskId相同的开始与结束打点相匹配，构成一个异步跟踪耗时任务。
 * 如果有多个相同name的任务需要跟踪或者对同一个任务跟踪多次，并且任务同时被执行，则每次调用的taskId需不相同。
 * 如果具有相同name的任务是串行执行的，则taskId可以相同。
 * 不同进程的taskId不会相互干扰。
 *
 * @param level 跟踪输出级别。
 * @param name 异步跟踪的名字。
 *     由于单条trace记录的总长度限制为512Byte，超出部分将被截断，建议name、customCategory和customArgs的长度之和不要超过420Byte。
 * @param taskId 异步跟踪的ID。异步跟踪开始和结束由于不是顺序发生的，所以需要通过name和每次执行唯一的taskId进行开始和结束的匹配。
 * @param customCategory 自定义聚类名称，用于聚合同一类异步跟踪打点。
 *     由于单条trace记录的总长度限制为512Byte，超出部分将被截断，建议name、customCategory和customArgs的长度之和不要超过420Byte。
 * @param customArgs 键值对，多个键值对使用逗号分隔，例"key1=value1,key2=value2"。
 *     由于单条trace记录的总长度限制为512Byte，超出部分将被截断，建议name、customCategory和customArgs的长度之和不要超过420Byte。
 * @since 19
 */
void OH_HiTrace_StartAsyncTraceEx(HiTrace_Output_Level level, const char* name, int32_t taskId,
    const char* customCategory, const char* customArgs);

/**
 * @brief 标记一个异步跟踪耗时任务的结束，分级控制跟踪输出。
 * 用于在异步操作完成后进行结束打点，例如在回调函数中调用。
 * 和{@link OH_HiTrace_StartAsyncTraceEx}配对使用，参数level、name和taskId必须与异步跟踪开始打点接口的对应参数值保持一致。
 *
 * @param level 跟踪输出级别。
 * @param name 异步跟踪的名字。
 *     由于单条trace记录的总长度限制为512Byte，超出部分将被截断，建议name的长度不要超过420Byte。
 * @param taskId 异步跟踪的ID。异步跟踪开始和结束由于不是顺序发生的，所以需要通过name和每次执行唯一的taskId进行开始和结束的匹配。
 * @since 19
 */
void OH_HiTrace_FinishAsyncTraceEx(HiTrace_Output_Level level, const char* name, int32_t taskId);

/**
 * @brief 标记一个跟踪的整数变量，分级控制跟踪输出。
 *
 * @param level 跟踪输出级别。
 * @param name 整数变量的名称，不必与实际变量名相同。
 *     由于单条trace记录的总长度限制为512Byte，超出部分将被截断，建议name的长度不要超过420Byte。
 * @param count 要记录的整数值，用于跟踪该变量在不同时刻的数值变化。
 * @since 19
 */
void OH_HiTrace_CountTraceEx(HiTrace_Output_Level level, const char* name, int64_t count);

/**
 * @brief 判断当前是否开启应用trace捕获。
 *
 * @return 使用hitrace命令行工具等方式开启采集时返回true。
 *     未开启采集或停止采集后返回false，此时调用HiTraceMeter性能跟踪打点接口无效。
 * @since 19
 */
bool OH_HiTrace_IsTraceEnabled(void);

/**
 * @brief 注册应用trace捕获开关通知回调，使用callback异步回调。
 * 注册成功后，立即执行一次回调函数，后续回调函数由应用trace捕获开关状态变化触发执行。回调函数保存在应用进程内，一个进程最多可以注册10个回调函数。
 * 若注册的回调包含耗时操作，当回调被执行时，注册或注销行为会被阻塞（等待回调执行完成）。因此，建议不要在应用主线程中注册或注销包含耗时操作的回调，
 * 避免发生应用冻屏。
 *
 * @param callback 注册的回调函数。应避免耗时操作，否则会阻塞注册或注销操作；建议不在主线程注册或注销含耗时操作的回调，避免应用冻屏。
 * @return 回调注册状态。
 *     >= 0：注册成功，返回用于注销的回调索引，索引范围0到9；
 *     -1：已达到最大回调函数注册数量；
 *     -2：无效参数，参数非{@link OH_HiTrace_TraceEventListener}类型。
 * @since 22
 */
int32_t OH_HiTrace_RegisterTraceListener(OH_HiTrace_TraceEventListener callback);

/**
 * @brief 注销应用trace捕获开关通知回调。
 * 使用{@link OH_HiTrace_RegisterTraceListener}返回的回调索引，注销该索引关联的回调函数。
 *
 * @param index 已注册回调函数索引，有效取值范围为0到9。
 * @return 回调注销状态。
 *     0：注销成功；
 *     -1：目标索引的回调函数未注册；
 *     -2：无效索引，参数index值不在0到9的范围内。
 * @since 22
 */
int32_t OH_HiTrace_UnregisterTraceListener(int32_t index);

#ifdef __cplusplus
}
#endif
/** @} */

#endif // HIVIEWDFX_HITRACE_H