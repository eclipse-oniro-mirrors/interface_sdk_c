/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup FFRT
 * @{
 *
 * @brief 提供Function Flow Runtime（FFRT）C接口。
 *
 * FFRT是一种基于任务的并发运行时库，根据任务依赖关系自动调度任务，
 * 开发者无需手动管理线程。
 *
 * @since 12
 */

/**
 * @file timer.h
 *
 * @brief 声明定时器的C接口。
 *
 * 提供基于QoS等级的定时器能力，支持在指定超时时间后执行回调函数，可用于延时任务调度等场景。
 *
 * @library libffrt.z.so
 * @kit FunctionFlowRuntimeKit
 * @syscap SystemCapability.Resourceschedule.Ffrt.Core
 * @since 12
 */

#ifndef FFRT_API_C_TIMER_H
#define FFRT_API_C_TIMER_H

#include <stdbool.h>
#include "type_def.h"

/**
 * @brief 在FFRT工作线程上启动定时器。
 *
 * 避免在`cb`中调用`exit`或{@link ffrt_timer_stop}，以防止未定义行为或死锁。
 *
 * @param qos 运行定时器的工作线程的QoS等级。
 * @param timeout 超时时间，单位是毫秒。
 * @param data 传递给`cb`的用户数据。
 * @param cb 超时后执行的用户回调函数。
 * @param repeat 是否重复执行该定时器。`true`表示重复，`false`表示只执行一次。
 * @return 定时器句柄；若回调函数为空指针或QoS映射未注册则返回`-1`。
 * @see ffrt_timer_stop
 * @since 12
 */
FFRT_C_API ffrt_timer_t ffrt_timer_start(ffrt_qos_t qos, uint64_t timeout, void* data, ffrt_timer_cb cb, bool repeat);

/**
 * @brief 停止FFRT工作线程上的定时器。
 *
 * 该接口为阻塞接口。请避免在回调函数内调用该接口，以防止死锁或同步问题。当`handle`对应的回调正在执行时，
 * 该函数会等待回调完成后再返回。
 *
 * @param qos 运行定时器的工作线程的QoS等级。必须与{@link ffrt_timer_start}中使用的QoS等级一致。
 * @param handle 目标定时器句柄，由{@link ffrt_timer_start}返回。
 * @return 操作成功时返回`0`；
 *         否则返回`-1`。
 * @see ffrt_timer_start
 * @since 12
 */
FFRT_C_API int ffrt_timer_stop(ffrt_qos_t qos, ffrt_timer_t handle);

#endif // FFRT_API_C_TIMER_H
/** @} */
