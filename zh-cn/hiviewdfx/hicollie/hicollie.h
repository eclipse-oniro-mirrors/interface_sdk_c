/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @addtogroup HiCollie
 * @{
 *
 * @brief 提供检测业务线程卡死、卡顿的能力。请注意，该线程不应与主线程相同。
 *
 * 可应用于以下两种场景：
 * (1) 业务线程卡死6秒；
 * (2) 业务线程短暂卡顿，通常小于1秒。
 *
 * @since 12
 */

/**
 * @file hicollie.h
 *
 * @brief 定义HiCollie模块的接口。
 *
 * @library libohhicollie.so
 * @kit PerformanceAnalysisKit
 * @syscap SystemCapability.HiviewDFX.HiCollie
 * @since 12
 */

#ifndef HIVIEWDFX_HICOLLIE_H
#define HIVIEWDFX_HICOLLIE_H

#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief 错误码定义。
 *
 * @since 12
 */
typedef enum HiCollie_ErrorCode {
    /**
     * 成功。
     *
     * @since 12
     */
    HICOLLIE_SUCCESS = 0,
    /**
     * 无效参数。
     *
     * @since 12
     */
    HICOLLIE_INVALID_ARGUMENT = 401,
    /**
     * 调用线程错误。
     *
     * @since 12
     */
    HICOLLIE_WRONG_THREAD_CONTEXT = 29800001,
    /**
     * 远程调用错误。
     *
     * @since 12
     */
    HICOLLIE_REMOTE_FAILED = 29800002,
    /**
     * 无效的计时器名称。
     *
     * @since 18
     */
    HICOLLIE_INVALID_TIMER_NAME = 29800003,
    /**
     * 无效的函数执行超时时间阈值。
     *
     * @since 18
     */
    HICOLLIE_INVALID_TIMEOUT_VALUE = 29800004,
    /**
     * 函数执行超时检测接入进程错误。
     *
     * @since 18
     */
    HICOLLIE_WRONG_PROCESS_CONTEXT = 29800005,
    /**
     * 用于保存返回的计时器id的指针不应为NULL。
     *
     * @since 18
     */
    HICOLLIE_WRONG_TIMER_ID_OUTPUT_PARAM = 29800006,
    /**
     * 上报频率超过限制。
     *
     * @since 24
     */
    OH_HICOLLIE_REACH_REPORT_LIMIT = 29800007,
} HiCollie_ErrorCode;

/**
 * @brief 在业务线程卡死检测中，通过实现该函数来检测业务线程是否卡住。
 * HiCollie将在业务线程中每3秒调用一次该函数。
 * 例如：该函数可实现向业务线程发送消息，在业务线程接收到消息之后，设置一个标记，检查这个标记，确定业务线程是否卡住。
 *
 * @since 12
 */
typedef void (*OH_HiCollie_Task)(void);

/**
 * @brief 卡顿检测中，需要在业务线程处理事件前后各插入一个桩函数。该函数在每个事件处理前插入。
 * 由HiCollie检查事件的执行时间。如果超过预设阈值，上报jank事件。
 * 该函数在每个事件处理前插入。
 *
 * @param eventName 业务线程处理事件的名字。
 * @since 12
 */
typedef void (*OH_HiCollie_BeginFunc)(const char* eventName);

/**
 * @brief 卡顿检测中，该函数用于记录业务线程处理事件的结束时间。该函数在每个事件处理后插入。
 * 由HiCollie检查事件的执行时间。如果超过预设阈值，上报jank事件。
 * 该函数在每个事件处理后插入。
 *
 * @param eventName 业务线程处理事件的名字。
 * @since 12
 */
typedef void (*OH_HiCollie_EndFunc)(const char* eventName);

/**
 * @brief 检测业务线程卡顿的相关参数。请注意，API 12及以上支持。
 *
 * @since 12
 */
typedef struct HiCollie_DetectionParam {
    /**
     * 卡顿场景下，触发采样栈的时间阈值。
     */
    int sampleStackTriggerTime;
    /**
     * 扩展参数以供将来使用。
     */
    int reserved;
} HiCollie_DetectionParam;

/**
 * @brief 注册应用业务线程卡死的周期性检测任务。用户实现回调函数, 用于定时检测业务线程卡死情况。
 * 默认检测时间：3s上报BUSSINESS_THREAD_BLOCK_3S告警事件，6s上报BUSSINESS_THREAD_BLOCK_6S卡死事件。
 *
 * @param task 每3秒执行一次的周期性检测任务，用于检测业务线程是否卡住。
 * @return {@link HICOLLIE_SUCCESS} 0 - 成功。
 * {@link HICOLLIE_WRONG_THREAD_CONTEXT} 29800001 - 调用线程错误。仅能在非主线程中调用该函数。
 * 具体可参考{@link HiCollie_ErrorCode}。
 * @since 12
 */
HiCollie_ErrorCode OH_HiCollie_Init_StuckDetection(OH_HiCollie_Task task);

/**
 * @brief 注册应用业务线程卡死的周期性检测任务。用户实现回调函数, 用于定时检测业务线程卡死情况。
 * 开发者可以设置卡死检测时间，可设置的时间范围：[3, 15]，单位：秒。
 *
 * @param task 每stuckTimeout时间执行一次的周期性检测任务，用于检测业务线程是否卡住。
 * @param stuckTimeout 检测业务线程卡死时间。任务执行超过stuckTimeout时间上报卡死告警事件；任务超过stuckTimeout * 2时间上报卡死事件。
 * 单位：秒。规定：最大值15秒，最小值3秒。
 * @return {@link HICOLLIE_SUCCESS} 0 - 成功。
 * {@link HICOLLIE_INVALID_ARGUMENT} 401 - 卡死检测时间设置错误。
 * {@link HICOLLIE_WRONG_THREAD_CONTEXT} 29800001 - 调用线程错误。仅能在非主线程中调用该函数。
 * 具体可参考{@link HiCollie_ErrorCode}。
 * @since 18
 */
HiCollie_ErrorCode OH_HiCollie_Init_StuckDetectionWithTimeout(OH_HiCollie_Task task, uint32_t stuckTimeout);

/**
 * @brief 注册应用业务线程卡顿检测的回调函数。
 * 线程卡顿监控功能需要开发者实现两个卡顿检测回调函数, 分别放在业务线程处理事件的前后。作为插桩函数，监控业务线程处理事件执行情况。
 *
 * @param beginFunc 检测业务线程处理事件前的函数。
 * @param endFunc 检测业务线程处理事件后的函数。
 * @param param 扩展参数以供将来使用。
 * @return {@link HICOLLIE_SUCCESS} 0 - 成功。
 * {@link HICOLLIE_INVALID_ARGUMENT} 401 - 开始函数和结束函数两者都必须有值或为空，否则将返回该错误值。
 * {@link HICOLLIE_WRONG_THREAD_CONTEXT} 29800001 - 调用线程错误。仅能在非主线程中调用该函数。
 * 具体可参考{@link HiCollie_ErrorCode}。
 * @since 12
 */
HiCollie_ErrorCode OH_HiCollie_Init_JankDetection(OH_HiCollie_BeginFunc* beginFunc,
    OH_HiCollie_EndFunc* endFunc, HiCollie_DetectionParam param);

/**
 * @brief 上报应用业务线程卡死事件，生成卡死故障日志，辅助定位应用卡死问题。
 * 先调用OH_HiCollie_Init_StuckDetection或OH_HiCollie_Init_StuckDetectionWithTimeout接口，初始化检测的task；
 * 如果task任务超时，结合业务逻辑，调用OH_HiCollie_Report接口上报卡死事件。
 *
 * @param isSixSecond 布尔指针。如果卡住6秒，则为true。如果卡住3秒，则为false。
 * @return {@link HICOLLIE_SUCCESS} 0 - 成功。
 * {@link HICOLLIE_INVALID_ARGUMENT} 401 - 开始函数和结束函数两者都必须有值或为空，否则将返回该错误值。
 * {@link HICOLLIE_WRONG_THREAD_CONTEXT} 29800001 - 调用线程错误。仅能在非主线程中调用该函数。
 * {@link HICOLLIE_REMOTE_FAILED} 29800002 - 远程调用错误。请求IPC远程服务失败。
 * 具体可参考{@link HiCollie_ErrorCode}。
 * @since 12
 */
HiCollie_ErrorCode OH_HiCollie_Report(bool* isSixSecond);

/**
 * @brief 上报应用输入无响应事件，生成卡死故障日志，辅助定位应用卡死问题。如果在PC或平板设备上，还会弹窗提示用户继续等待或关闭应用，其他设备不会弹窗。建议如下两种方式使用该接口。
 * 方式一（推荐）：配合OH_HiCollie_Report、OH_HiCollie_Init_StuckDetection或OH_HiCollie_Init_StuckDetectionWithTimeout接口使用，
 * 业务线程通过上述接口周期性检测自身卡死情况，当满足业务线程卡死且有输入事件（如屏幕点击、鼠标点击、键盘输入等）条件时再调用OH_HiCollie_ReportInputBlock接口。
 * 方式二：业务线程不通过OH_HiCollie_Report、OH_HiCollie_Init_StuckDetection或OH_HiCollie_Init_StuckDetectionWithTimeout接口也能检测自身卡死情况，
 * 则应用结合业务线程卡死情况和输入事件再调用OH_HiCollie_ReportInputBlock接口。
 *
 * @return {@link HICOLLIE_SUCCESS} 0 - 成功。
 * {@link HICOLLIE_REMOTE_FAILED} 29800002 - 远程调用错误。请求IPC远程服务失败。
 * 具体可参考{@link HiCollie_ErrorCode}。
 * @since 24
 */
HiCollie_ErrorCode OH_HiCollie_ReportInputBlock();

/**
 * @brief 当用户调用{@link OH_HiCollie_SetTimer}后，未在其自定义的任务超时时间阈值内调用{@link OH_HiCollie_CancelTimer}，回调函数将被执行。
 *
 * @since 18
 */
typedef void (*OH_HiCollie_Callback)(void*);

/**
 * @brief 定义函数执行超时时发生的动作。
 *
 * @since 18
 */
typedef enum HiCollie_Flag {
    /**
     * 默认动作，生成日志及执行恢复动作。
     */
    HICOLLIE_FLAG_DEFAULT = (~0),
    /**
     * 仅执行回调函数。
     */
    HICOLLIE_FLAG_NOOP = (0),
    /**
     * 生成日志。
     */
    HICOLLIE_FLAG_LOG = (1 << 0),
    /**
     * 执行恢复动作。
     */
    HICOLLIE_FLAG_RECOVERY = (1 << 1)
} HiCollie_Flag;

/**
 * @brief 定义OH_HiCollie_SetTimer函数的输入参数。
 *
 * @since 18
 */
typedef struct HiCollie_SetTimerParam {
    /**
     * timer 任务名称。
     */
    const char *name;
    /**
     * 任务超时时间阈值，单位：秒。
     */
    unsigned int timeout;
    /**
     * 超时发生时执行的回调函数。
     */
    OH_HiCollie_Callback func;
    /**
     * 回调函数的参数。
     */
    void *arg;
    /**
     * 超时发生时执行的动作，参考{@link HiCollie_Flag}。
     */
    HiCollie_Flag flag;
} HiCollie_SetTimerParam;

/**
 * @brief 注册定时器，用于检测函数或代码块执行是否超过自定义时间。
 * 结合OH_HiCollie_CancelTimer接口配套使用，应在调用耗时的函数之前使用。
 *
 * @param param 定义定时器的参数，参考{@link HiCollie_SetTimerParam}输入参数。
 * @param id 返回的计时器id的指针不应为NULL。
 * @return {@link HICOLLIE_SUCCESS} 0 - 成功。
 * {@link HICOLLIE_INVALID_TIMER_NAME} 29800003 - 无效的计时器名称，不应为NULL或空字符串。
 * {@link HICOLLIE_INVALID_TIMEOUT_VALUE} 29800004 - 无效的超时值。
 * {@link HICOLLIE_WRONG_PROCESS_CONTEXT} 29800005 - 无效的接入检测进程上下文，appspawn与nativespawn进程中不可调用。
 * {@link HICOLLIE_WRONG_TIMER_ID_OUTPUT_PARAM} 29800006 - 用于保存返回的计时器id的指针，不应该为NULL。
 * 具体可参考{@link HiCollie_ErrorCode}。
 * @since 18
 */
HiCollie_ErrorCode OH_HiCollie_SetTimer(HiCollie_SetTimerParam param, int *id);

/**
 * @brief 取消定时器。
 * 结合OH_HiCollie_SetTimer接口配套使用，执行函数或代码块后使用，OH_HiCollie_CancelTimer通过id将该任务取消；
 * 若未在自定义时间内取消，则执行回调函数，在特定自定义超时动作下，生成故障日志。
 *
 * @param id 执行{@link OH_HiCollie_SetTimer}函数后更新的计时器id。
 * @since 18
 */
void OH_HiCollie_CancelTimer(int id);

/**
 * @brief 定义FreezeCallback返回的冻屏事件类型。
 *
 * @since 24
 */
typedef enum OH_HiCollie_Freeze_Type {
    /**
     * @brief 主线程超时一个周期。
     *
     * @since 24
     */
    OH_THREAD_BLOCK_3S,
    /**
     * @brief 主线程超时两个周期。
     *
     * @since 24
     */
    OH_THREAD_BLOCK_6S,
    /**
     * @brief Ability生命周期超时一个周期。
     *
     * @since 24
     */
    OH_LIFECYCLE_HALF_TIMEOUT,
    /**
     * @brief Ability生命周期超时两个周期。
     *
     * @since 24
     */
    OH_LIFECYCLE_TIMEOUT,
    /**
     * @brief 输入事件超时。
     *
     * @since 24
     */
    OH_APP_INPUT_BLOCK,
    /**
     * @brief 通过{@link OH_HiCollie_Report}上报3秒冻屏事件。
     *
     * @since 24
     */
    OH_BUSINESS_THREAD_BLOCK_3S,
    /**
     * @brief 通过{@link OH_HiCollie_Report}上报6秒冻屏事件。
     *
     * @since 24
     */
    OH_BUSINESS_THREAD_BLOCK_6S,
    /**
     * @brief 通过{@link OH_HiCollie_ReportInputBlock}上报冻屏事件。
     *
     * @since 24
     */
    OH_BUSINESS_INPUT_BLOCK
} OH_HiCollie_Freeze_Type;

/**
 * @brief 冻屏事件使用的回调。
 *
 * @param type 冻屏事件类型。
 * @param buffer 系统提供的日志缓冲区，其内容将被迁移到APP_FREEZE或APP_HICOLLIE事件中。
 * @param size 可使用的缓冲区大小，最大值为64KB。
 * @return 已使用的缓冲区大小，单位字节。
 * @since 24
 */
typedef size_t (*OH_HiCollie_FreezeCallback)(OH_HiCollie_Freeze_Type type, void* buffer, size_t size);

/**
 * @brief 将冻屏回调设置进系统，系统将在冻屏事件发生时回调此函数。
 *
 * @param callback 回调函数。
 * @return 本进程内上次传入的回调函数。
 * @since 24
 */
void* OH_HiCollie_SetFreezeCallback(OH_HiCollie_FreezeCallback callback);

/**
 * @brief 报告一个进程的冻屏事件，此时会生成APP_HICOLLIE类型HiAppEvent事件。
 *
 * @param isFreezeEvent 上报事件类型。true：上报6秒冻屏事件。false：上报3秒冻屏事件。
 * @return HICOLLIE_SUCCESS：0 - 成功。
 * OH_HICOLLIE_REACH_REPORT_LIMIT：29800007 - 上报频率过高。
 * @since 24
 */
HiCollie_ErrorCode OH_HiCollie_AssociateProcessReport(bool isFreezeEvent);

#ifdef __cplusplus
}
#endif
/** @} */

#endif // HIVIEWDFX_HICOLLIE_H
