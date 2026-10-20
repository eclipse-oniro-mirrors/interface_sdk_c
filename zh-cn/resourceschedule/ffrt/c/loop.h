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
 * @file loop.h
 *
 * @brief 声明事件循环的C接口。
 *
 * @library libffrt.z.so
 * @kit FunctionFlowRuntimeKit
 * @syscap SystemCapability.Resourceschedule.Ffrt.Core
 * @since 12
 */

#ifndef FFRT_API_C_LOOP_H
#define FFRT_API_C_LOOP_H

#include <stdbool.h>
#include "type_def.h"
#include "queue.h"

/**
 * @brief loop句柄，用于标识不同的loop。
 *
 * @since 12
 */
typedef void* ffrt_loop_t;

/**
 * @brief 在指定的队列上创建loop，用于运行事件循环。
 *
 * @param queue 队列。
 * @return loop创建成功时返回非空的loop句柄；
 *         否则返回空指针。
 * @since 12
 */
FFRT_C_API ffrt_loop_t ffrt_loop_create(ffrt_queue_t queue);

/**
 * @brief 销毁loop。
 *
 * 调用该接口可释放与loop关联的资源。
 *
 * @param loop loop句柄。
 * @return loop销毁成功时返回`0`；
 *         否则返回`-1`。
 * @since 12
 */
FFRT_C_API int ffrt_loop_destroy(ffrt_loop_t loop);

/**
 * @brief 启动一次loop循环。
 *
 * 该函数会独占调用线程，在当前调用线程中同步运行事件循环，直到调用{@link ffrt_loop_stop}后才会返回。
 *
 * @param loop loop句柄。
 * @return loop运行成功时返回`0`；
 *         否则返回`-1`。
 * @see ffrt_loop_stop
 * @since 12
 */
FFRT_C_API int ffrt_loop_run(ffrt_loop_t loop);

/**
 * @brief 停止loop循环。
 *
 * 调用后，正在执行{@link ffrt_loop_run}的线程将停止循环并返回。
 *
 * @param loop loop句柄。
 * @see ffrt_loop_run
 * @since 12
 */
FFRT_C_API void ffrt_loop_stop(ffrt_loop_t loop);

/**
 * @brief 在ffrt loop上控制epoll文件描述符。
 *
 * 在目标文件描述符上添加、修改或删除监听的事件。
 *
 * @param loop loop句柄。
 * @param op 在目标文件描述符上执行的操作类型，如添加、修改或删除。
 * @param fd 执行操作的目标文件描述符。
 * @param events 监听的事件类型（如可读、可写等），支持按位或组合。
 * @param data 传递给`cb`的用户数据。
 * @param cb 当目标fd被轮询到时执行的用户回调函数。
 * @return 操作成功时返回`0`；
 *         否则返回`-1`。
 * @since 12
 */
FFRT_C_API int ffrt_loop_epoll_ctl(ffrt_loop_t loop, int op, int fd, uint32_t events, void* data, ffrt_poller_cb cb);

/**
 * @brief 在ffrt loop上启动定时器。
 *
 * 超时后调用回调函数；若`repeat`为`true`，则周期性重复触发。
 *
 * @param loop loop句柄。
 * @param timeout 超时时间，单位是毫秒，取值范围为[0, +∞)。
 * @param data 传递给`cb`的用户数据。
 * @param cb 超时后执行的用户回调函数。
 * @param repeat 是否重复执行该定时器。`true`表示重复，`false`表示只执行一次。
 * @return 定时器句柄；若`loop`或`cb`为空则返回`-1`。
 * @see ffrt_loop_timer_stop
 * @since 12
 */
FFRT_C_API ffrt_timer_t ffrt_loop_timer_start(
    ffrt_loop_t loop, uint64_t timeout, void* data, ffrt_timer_cb cb, bool repeat);

/**
 * @brief 在ffrt loop上停止定时器。
 *
 * 调用后，该定时器不再触发。
 *
 * @param loop loop句柄。
 * @param handle 定时器句柄，由{@link ffrt_loop_timer_start}返回。
 * @return 操作成功时返回`0`；
 *         否则返回`-1`。
 * @see ffrt_loop_timer_start
 * @since 12
 */
FFRT_C_API int ffrt_loop_timer_stop(ffrt_loop_t loop, ffrt_timer_t handle);

#endif // FFRT_API_C_LOOP_H
/** @} */
