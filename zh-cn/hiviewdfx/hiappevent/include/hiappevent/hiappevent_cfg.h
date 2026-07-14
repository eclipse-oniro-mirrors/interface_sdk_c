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
 * @brief 提供应用事件日志记录功能。
 *
 * 为应用提供事件日志功能，记录故障、统计、安全、用户行为等
 * 运行过程中上报的事件。通过事件信息，可以分析应用程序
 * 的运行情况。
 *
 * @since 8
 */

/**
 * @file hiappevent_cfg.h
 *
 * @brief 定义事件日志配置函数的所有配置项名称。
 *
 * 如果要配置事件日志功能，可以直接使用配置项常量。
 *
 * 示例代码:
 * <pre>
 *     bool res = OH_HiAppEvent_Configure(MAX_STORAGE, "100M");
 * </pre>
 *
 * @syscap SystemCapability.HiviewDFX.HiAppEvent
 * @library libhiappevent_ndk.z.so
 * @kit PerformanceAnalysisKit
 * @since 8
 */

#ifndef HIVIEWDFX_HIAPPEVENT_CONFIG_H
#define HIVIEWDFX_HIAPPEVENT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 事件日志记录开关。
 *
 * @since 8
 */
#define DISABLE "disable"

/**
 * @brief 事件文件目录存储配额大小。
 *
 * @since 8
 */
#define MAX_STORAGE "max_storage"

#ifdef __cplusplus
}
#endif
/** @} */
#endif // HIVIEWDFX_HIAPPEVENT_CONFIG_H