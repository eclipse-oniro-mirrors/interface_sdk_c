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
 * @file hiappevent_event.h
 *
 * @brief 定义所有预定义事件的事件名称。
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

#ifndef HIVIEWDFX_HIAPPEVENT_EVENT_H
#define HIVIEWDFX_HIAPPEVENT_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用户登录事件。
 *
 * @since 8
 */
#define EVENT_USER_LOGIN "hiappevent.user_login"

/**
 * @brief 用户登出事件。
 *
 * @since 8
 */
#define EVENT_USER_LOGOUT "hiappevent.user_logout"

/**
 * @brief 分布式服务事件。
 *
 * @since 8
 */
#define EVENT_DISTRIBUTED_SERVICE_START "hiappevent.distributed_service_start"

/**
 * @brief 崩溃事件。
 *
 * @since 12
 */
#define EVENT_APP_CRASH "APP_CRASH"

/**
 * @brief 应用冻屏事件。
 *
 * @since 12
 */
#define EVENT_APP_FREEZE "APP_FREEZE"

/**
 * @brief 启动耗时事件。
 *
 * @since 12
 */
#define EVENT_APP_LAUNCH "APP_LAUNCH"

/**
 * @brief 滑动丢帧事件。
 *
 * @since 12
 */
#define EVENT_SCROLL_JANK "SCROLL_JANK"

/**
 * @brief CPU高负载事件。
 *
 * @since 12
 */
#define EVENT_CPU_USAGE_HIGH "CPU_USAGE_HIGH"

/**
 * @brief 24h功耗器件分解统计事件。
 *
 * @since 12
 */
#define EVENT_BATTERY_USAGE "BATTERY_USAGE"

/**
 * @brief 资源泄漏事件。
 *
 * @since 12
 */
#define EVENT_RESOURCE_OVERLIMIT "RESOURCE_OVERLIMIT"

/**
 * @brief 地址越界事件。
 *
 * @since 12
 */
#define EVENT_ADDRESS_SANITIZER "ADDRESS_SANITIZER"

/**
 * @brief 主线程超时事件。
 *
 * @since 12
 */
#define EVENT_MAIN_THREAD_JANK "MAIN_THREAD_JANK"

/**
 * @brief 用于设置主线程超时事件配置策略。
 *
 * @since 22
 */
#define EVENT_MAIN_THREAD_JANK_V2 "MAIN_THREAD_JANK_V2"

/**
 * @brief 任务执行超时事件。
 *
 * @since 18
 */
#define EVENT_APP_HICOLLIE "APP_HICOLLIE"

/**
 * @brief OS作用域。
 *
 * @since 12
 */
#define DOMAIN_OS "OS"

/**
 * @brief 应用终止事件。
 *
 * @since 20
 */
#define EVENT_APP_KILLED "APP_KILLED"

/**
 * @brief 音频卡顿事件。
 *
 * @since 21
 */
#define EVENT_AUDIO_JANK_FRAME "AUDIO_JANK_FRAME"

/**
 * @brief 应用冻屏告警事件。
 *
 * @since 26.0.0
 */
#define OH_EVENT_APP_FREEZE_WARNING "APPFREEZE_WARNING"

#ifdef __cplusplus
}
#endif
/** @} */
#endif // HIVIEWDFX_HIAPPEVENT_EVENT_H