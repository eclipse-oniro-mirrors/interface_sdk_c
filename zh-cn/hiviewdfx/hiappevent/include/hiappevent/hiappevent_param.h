/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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
 * @addtogroup HiAppEvent
 * @{
 *
 * @brief 提供应用事件打点功能。
 *
 * 为应用提供事件打点功能，记录故障、统计、安全、用户行为等
 * 运行过程中上报的事件。通过事件信息，可以分析应用程序的
 * 运行情况。
 *
 * @since 8
 */

/**
 * @file hiappevent_param.h
 *
 * @brief 定义所有预定义事件的param名称。
 *
 * 除了与特定应用关联的自定义事件之外，您还可以使用预定义事件进行打点。
 *
 * 示例代码：
 * <pre>
 *     ParamList list = OH_HiAppEvent_CreateParamList();
 *     OH_HiAppEvent_AddInt32Param(list, PARAM_USER_ID, 123);
 *     int res = OH_HiAppEvent_Write("user_domain", EVENT_USER_LOGIN, BEHAVIOR, list);
 *     OH_HiAppEvent_DestroyParamList(list);
 * </pre>
 *
 * @syscap SystemCapability.HiviewDFX.HiAppEvent
 * @library libhiappevent_ndk.z.so
 * @kit PerformanceAnalysisKit
 * @since 8
 */

#ifndef HIVIEWDFX_HIAPPEVENT_PARAM_H
#define HIVIEWDFX_HIAPPEVENT_PARAM_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用户ID。可用于预定义事件打点。
 *
 * @since 8
 */
#define PARAM_USER_ID "user_id"

/**
 * @brief 分布式服务名称。可用于预定义事件打点。
 *
 * @since 8
 */
#define PARAM_DISTRIBUTED_SERVICE_NAME "ds_name"

/**
 * @brief 分布式服务实例ID。可用于预定义事件打点。
 *
 * @since 8
 */
#define PARAM_DISTRIBUTED_SERVICE_INSTANCE_ID "ds_instance_id"

/**
 * @brief 用于MAIN_THREAD_JANK_V2事件，主线程超时检测采集日志的类型。
 *
 * @since 22
 */
#define MAIN_THREAD_JANK_PARAM_LOG_TYPE "log_type"

/**
 * @brief 用于MAIN_THREAD_JANK_V2事件，主线程超时检测间隔和采样间隔，单位为ms。
 *
 * @since 22
 */
#define MAIN_THREAD_JANK_PARAM_SAMPLE_INTERVAL "sample_interval"

/**
 * @brief 用于MAIN_THREAD_JANK_V2事件，应用启动期间忽略主线程超时检测的时间，单位为s。
 *
 * @since 22
 */
#define MAIN_THREAD_JANK_PARAM_IGNORE_STARTUP_TIME "ignore_startup_time"

/**
 * @brief 用于MAIN_THREAD_JANK_V2事件，主线程超时检测的采样栈的次数。
 *
 * @since 22
 */
#define MAIN_THREAD_JANK_PARAM_SAMPLE_COUNT "sample_count"

/**
 * @brief 用于MAIN_THREAD_JANK_V2事件，每个应用PID一个生命周期内，主线程超时采样上报的次数，一个生命周期内只能设置一次。
 *
 * @since 22
 */
#define MAIN_THREAD_JANK_PARAM_REPORT_TIMES_PER_APP "report_times_per_app"

/**
 * @brief 用于MAIN_THREAD_JANK_V2事件，主线程超时结束时，是否停止采样主线程堆栈。
 *
 * @since 22
 */
#define MAIN_THREAD_JANK_PARAM_AUTO_STOP_SAMPLING "auto_stop_sampling"

/**
 * @brief 用于设置APP_CRASH事件中的CPP_CRASH类型的日志规格，是否打印PC、LR寄存器扩展字节范围的内存内容。
 *
 * @since 24
 */
#define OH_APP_CRASH_PARAM_EXTEND_PC_LR_PRINTING "extend_pc_lr_printing"

/**
 * @brief 用于设置APP_CRASH事件中的CPP_CRASH类型的日志规格，按设置的参数值大小截断CPP_CRASH日志。
 *
 * @since 24
 */
#define OH_APP_CRASH_PARAM_LOG_FILE_CUTOFF_SZ_BYTES "log_file_cutoff_sz_bytes"

/**
 * @brief 用于设置APP_CRASH事件中的CPP_CRASH类型的日志规格，是否只打印崩溃日志中出现的地址所属的VMA映射信息，以减小CPP_CRASH日志文件大小。
 *
 * @since 24
 */
#define OH_APP_CRASH_PARAM_SIMPLIFY_VMA_PRINTING "simplify_vma_printing"

/**
 * @brief 用于设置APP_CRASH事件中的CPP_CRASH类型的日志规格，是否在CPP_CRASH场景拼接应用沙箱中指定文件的日志。
 *
 * @since 24
 */
#define OH_APP_CRASH_PARAM_MERGE_CPPCRASH_APP_LOG "merge_cppcrash_app_log"

/**
 * @brief 用于设置APP_CRASH事件中的CPP_CRASH类型的日志规格，是否在CPP_CRASH场景收集minidump日志并通过external_log返回。
 *
 * @since 26.0.0
 */
#define OH_APP_CRASH_PARAM_COLLECT_MINIDUMP "collect_minidump"

#ifdef __cplusplus
}
#endif
/** @} */
#endif // HIVIEWDFX_HIAPPEVENT_PARAM_H