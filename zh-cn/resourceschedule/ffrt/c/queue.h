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
 * @since 10
 */

/**
 * @file queue.h
 *
 * @brief 声明队列的C接口。
 *
 * @library libffrt.z.so
 * @kit FunctionFlowRuntimeKit
 * @syscap SystemCapability.Resourceschedule.Ffrt.Core
 * @since 10
 */

#ifndef FFRT_API_C_QUEUE_H
#define FFRT_API_C_QUEUE_H

#include <stdbool.h>
#include "type_def.h"

/**
 * @brief 枚举队列类型。
 *
 * @since 12
 */
typedef enum {
    /** 串行队列。 */
    ffrt_queue_serial,
    /** 并发队列。 */
    ffrt_queue_concurrent,
    /** 最大有效队列类型值，作为哨兵使用（例如用于迭代）。 */
    ffrt_queue_max
} ffrt_queue_type_t;

/**
 * @brief 队列句柄，用于标识不同的队列。
 *
 * @since 10
 */
typedef void* ffrt_queue_t;

/**
 * @brief 初始化队列属性。
 *
 * 该队列属性不再使用时，必须通过{@link ffrt_queue_attr_destroy}销毁。
 *
 * @param attr 指向队列属性的指针。
 * @return 队列属性初始化成功时返回`0`；
 *         否则返回`-1`。
 * @since 10
 */
FFRT_C_API int ffrt_queue_attr_init(ffrt_queue_attr_t* attr);

/**
 * @brief 销毁队列属性。
 *
 * 该队列属性必须已通过{@link ffrt_queue_attr_init}初始化。
 *
 * @param attr 指向队列属性的指针。
 * @since 10
 */
FFRT_C_API void ffrt_queue_attr_destroy(ffrt_queue_attr_t* attr);

/**
 * @brief 设置队列属性的QoS。
 *
 * @param attr 指向队列属性的指针。
 * @param qos QoS等级，取值范围参见{@link ffrt_qos_t}枚举定义。
 * @since 10
 */
FFRT_C_API void ffrt_queue_attr_set_qos(ffrt_queue_attr_t* attr, ffrt_qos_t qos);

/**
 * @brief 获取队列属性的QoS。
 *
 * @param attr 指向队列属性的指针。
 * @return QoS等级，取值范围参见{@link ffrt_qos_t}枚举定义。
 * @since 10
 */
FFRT_C_API ffrt_qos_t ffrt_queue_attr_get_qos(const ffrt_queue_attr_t* attr);

/**
 * @brief 设置队列属性的任务执行超时时长。
 *
 * @param attr 指向队列属性的指针。
 * @param timeout_us 队列任务执行超时时长，单位是微秒。下限为1000微秒（1毫秒），
 *                   低于1000的值会被强制设为1000。
 * @since 10
 */
FFRT_C_API void ffrt_queue_attr_set_timeout(ffrt_queue_attr_t* attr, uint64_t timeout_us);

/**
 * @brief 获取队列属性的任务执行超时时长。
 *
 * @param attr 指向队列属性的指针。
 * @return 队列任务执行超时时长，单位是微秒。
 * @since 10
 */
FFRT_C_API uint64_t ffrt_queue_attr_get_timeout(const ffrt_queue_attr_t* attr);

/**
 * @brief 设置队列属性的超时回调函数。
 *
 * 当队列中的任务执行时间超过通过{@link ffrt_queue_attr_set_timeout}设置的超时时长时触发该回调。
 *
 * @param attr 指向队列属性的指针。
 * @param f 队列超时回调函数。
 * @since 10
 */
FFRT_C_API void ffrt_queue_attr_set_callback(ffrt_queue_attr_t* attr, ffrt_function_header_t* f);

/**
 * @brief 获取队列属性的超时回调函数。
 *
 * @param attr 指向队列属性的指针。
 * @return 队列任务超时回调函数。
 * @since 10
 */
FFRT_C_API ffrt_function_header_t* ffrt_queue_attr_get_callback(const ffrt_queue_attr_t* attr);

/**
 * @brief 设置并发队列属性的最大并发度。
 *
 * @param attr 指向队列属性的指针。
 * @param max_concurrency 队列可并发执行的最大任务数。
 * @since 12
 */
FFRT_C_API void ffrt_queue_attr_set_max_concurrency(ffrt_queue_attr_t* attr, const int max_concurrency);

/**
 * @brief 获取并发队列属性的最大并发度。
 *
 * @param attr 指向队列属性的指针。
 * @return 队列的最大并发度。
 * @since 12
 */
FFRT_C_API int ffrt_queue_attr_get_max_concurrency(const ffrt_queue_attr_t* attr);

/**
 * @brief 设置队列属性的执行模式。
 *
 * 该接口指定队列中的任务是以协程模式还是线程模式执行。默认以协程模式执行。
 * 将mode设为`true`时启用基于线程的执行。
 *
 * @param attr 指向队列属性的指针。
 * @param mode 是否启用基于线程的执行模式。
 *             - `true`：任务以原生线程执行（线程模式）。
 *             - `false`：任务以协程执行（默认）。
 * @since 20
 */
FFRT_C_API void ffrt_queue_attr_set_thread_mode(ffrt_queue_attr_t* attr, bool mode);

/**
 * @brief 获取队列属性的执行模式。
 *
 * @param attr 指向队列属性的指针。
 * @return 任务以原生线程执行（线程模式）时返回`true`；
 *         任务以协程执行（默认）时返回`false`。
 * @since 20
 */
FFRT_C_API bool ffrt_queue_attr_get_thread_mode(const ffrt_queue_attr_t* attr);

/**
 * @brief 创建队列。
 *
 * 该队列不再使用时，必须通过{@link ffrt_queue_destroy}销毁。
 *
 * @param type 队列类型。`ffrt_queue_serial`适用于任务需按顺序执行的场景；
 *             `ffrt_queue_concurrent`适用于任务可并发执行以提高吞吐量的场景。
 * @param name 指向队列名称的指针。
 * @param attr 指向队列属性的指针。
 * @return 队列创建成功时返回非空的队列句柄；
 *         否则返回空指针。
 * @since 10
 */
FFRT_C_API ffrt_queue_t ffrt_queue_create(ffrt_queue_type_t type, const char* name, const ffrt_queue_attr_t* attr);

/**
 * @brief 销毁队列。
 *
 * 该队列必须已通过{@link ffrt_queue_create}创建。销毁时会取消尚未开始执行的任务，
 * 并阻塞等待正在执行的任务完成。
 *
 * @param queue 队列句柄。
 * @since 10
 */
FFRT_C_API void ffrt_queue_destroy(ffrt_queue_t queue);

/**
 * @brief 提交任务到队列。
 *
 * @param queue 队列句柄。
 * @param f 指向任务执行体的指针。
 * @param attr 指向任务属性的指针。
 * @see ffrt_queue_submit_h
 * @since 10
 */
FFRT_C_API void ffrt_queue_submit(ffrt_queue_t queue, ffrt_function_header_t* f, const ffrt_task_attr_t* attr);

/**
 * @brief 提交任务到队列，并获取任务句柄。
 *
 * @param queue 队列句柄。
 * @param f 指向任务执行体的指针。
 * @param attr 指向任务属性的指针。
 * @return 任务提交成功时返回非空的任务句柄；
 *         否则返回空指针。
 * @see ffrt_queue_submit
 * @since 10
 */
FFRT_C_API ffrt_task_handle_t ffrt_queue_submit_h(
    ffrt_queue_t queue, ffrt_function_header_t* f, const ffrt_task_attr_t* attr);

/**
 * @brief 提交任务到队列，是{@link ffrt_queue_submit}接口的简化形式。
 *
 * 该接口将给定的任务函数及其参数包装为用于队列提交的任务包装器（`ffrt_function_kind_queue`）。
 * 其中用于处理执行后清理的任务销毁回调（after_func）会被设为NULL，因而省略任何额外清理动作。
 * 生成的任务包装器随后通过{@link ffrt_queue_submit}接口被提交到指定队列。
 *
 * @param queue 队列句柄。
 * @param func 要执行的任务函数。
 * @param arg 指向传递给任务函数的参数或闭包数据的指针。
 * @param attr 指向任务属性的指针。
 * @see ffrt_queue_submit
 * @since 20
 */
FFRT_C_API void ffrt_queue_submit_f(ffrt_queue_t queue, ffrt_function_t func, void* arg, const ffrt_task_attr_t* attr);

/**
 * @brief 提交任务到队列并获取任务句柄，是{@link ffrt_queue_submit_h}接口的简化形式。
 *
 * 该接口将给定的任务函数及其参数包装为用于队列提交的任务包装器（`ffrt_function_kind_queue`）。
 * 其中用于处理执行后清理的任务销毁回调（after_func）会被设为NULL，因而省略任何额外清理动作。
 * 生成的任务包装器随后通过{@link ffrt_queue_submit_h}接口被提交到指定队列。
 *
 * @param queue 队列句柄。
 * @param func 要执行的任务函数。
 * @param arg 指向传递给任务函数的参数或闭包数据的指针。
 * @param attr 指向任务属性的指针。
 * @return 任务提交成功时返回非空的任务句柄；
 *         否则返回空指针。
 * @see ffrt_queue_submit_h
 * @since 20
 */
FFRT_C_API ffrt_task_handle_t ffrt_queue_submit_h_f(
    ffrt_queue_t queue, ffrt_function_t func, void* arg, const ffrt_task_attr_t* attr);

/**
 * @brief 等待队列中的任务执行完成。
 *
 * @param handle 任务句柄。
 * @since 10
 */
FFRT_C_API void ffrt_queue_wait(ffrt_task_handle_t handle);

/**
 * @brief 取消队列中的任务。
 *
 * 已开始执行的任务无法被取消。
 *
 * @param handle 任务句柄。
 * @return 任务取消成功时返回`0`；
 *         任务已执行完毕或已从队列中移除时返回`1`；
 *         `handle`为空时返回`-1`。
 * @since 10
 */
FFRT_C_API int ffrt_queue_cancel(ffrt_task_handle_t handle);

/**
 * @brief 获取应用主线程队列。
 *
 * @return 应用主线程队列。
 * @since 12
 */
FFRT_C_API ffrt_queue_t ffrt_get_main_queue(void);

/**
 * @brief 获取应用Worker（ArkTS）线程队列。
 *
 * @return 应用Worker（ArkTS）线程队列。
 * @deprecated since 18
 * @since 12
 */
FFRT_C_API ffrt_queue_t ffrt_get_current_queue(void);

#endif // FFRT_API_C_QUEUE_H
/** @} */
