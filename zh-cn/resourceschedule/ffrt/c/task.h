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
 * @file task.h
 *
 * @brief 声明FFRT任务的C接口，提供任务属性的初始化与销毁、任务QoS设置与获取、
 * 任务延迟时间管理、并发队列任务优先级管理、任务栈大小管理、任务提交调度执行、
 * 任务句柄引用计数管理以及任务等待等功能。
 *
 * @library libffrt.z.so
 * @kit FunctionFlowRuntimeKit
 * @syscap SystemCapability.Resourceschedule.Ffrt.Core
 * @since 10
 */

#ifndef FFRT_API_C_TASK_H
#define FFRT_API_C_TASK_H

#include <stdint.h>
#include "type_def.h"

/**
 * @brief 初始化任务属性。
 *
 * 调用成功后，任务属性将被设置为默认值（如默认QoS为{@link ffrt_qos_default}）。
 * 使用完毕后须调用{@link ffrt_task_attr_destroy}释放任务属性。
 *
 * @param attr 指向任务属性的指针。
 * @return 任务属性初始化成功时返回`0`；
 *         否则返回`-1`。
 * @since 10
 */
FFRT_C_API int ffrt_task_attr_init(ffrt_task_attr_t* attr);

/**
 * @brief 设置任务属性的名称。
 *
 * @param attr 指向任务属性的指针。
 * @param name 指向任务名称的指针。
 * @since 10
 */
FFRT_C_API void ffrt_task_attr_set_name(ffrt_task_attr_t* attr, const char* name);

/**
 * @brief 获取任务属性的名称。
 *
 * @param attr 指向任务属性的指针。
 * @return 任务名称获取成功时返回非空的任务名称指针；
 *         否则返回空指针。
 * @since 10
 */
FFRT_C_API const char* ffrt_task_attr_get_name(const ffrt_task_attr_t* attr);

/**
 * @brief 销毁任务属性。
 *
 * 必须在已通过{@link ffrt_task_attr_init}初始化的任务属性上调用本接口，用于释放属性持有的资源。
 * 销毁后该任务属性不可再使用。
 *
 * @param attr 指向任务属性的指针。
 * @since 10
 */
FFRT_C_API void ffrt_task_attr_destroy(ffrt_task_attr_t* attr);

/**
 * @brief 设置任务属性的QoS。
 *
 * QoS用于控制任务的调度优先级。例如，对用户交互型任务配置高QoS以保证响应速度，
 * 对后台或维护型任务配置低QoS以减少其对系统资源的占用。
 *
 * @param attr 指向任务属性的指针。
 * @param qos 待设置的QoS等级，取值参考{@link ffrt_qos_t}。
 * @since 10
 */
FFRT_C_API void ffrt_task_attr_set_qos(ffrt_task_attr_t* attr, ffrt_qos_t qos);

/**
 * @brief 获取任务属性的QoS。
 *
 * @param attr 指向任务属性的指针。
 * @return QoS等级，默认返回`ffrt_qos_default`。
 * @since 10
 */
FFRT_C_API ffrt_qos_t ffrt_task_attr_get_qos(const ffrt_task_attr_t* attr);

/**
 * @brief 设置任务属性的延迟时间。
 *
 * @param attr 指向任务属性的指针。
 * @param delay_us 任务延迟时间，单位是微秒。
 * @since 10
 */
FFRT_C_API void ffrt_task_attr_set_delay(ffrt_task_attr_t* attr, uint64_t delay_us);

/**
 * @brief 获取任务属性的延迟时间。
 *
 * @param attr 指向任务属性的指针。
 * @return 任务延迟时间，单位是微秒。
 * @since 10
 */
FFRT_C_API uint64_t ffrt_task_attr_get_delay(const ffrt_task_attr_t* attr);

/**
 * @brief 设置任务属性的优先级。
 *
 * @param attr 指向任务属性的指针。
 * @param priority 并发队列任务的执行优先级，取值参考{@link ffrt_queue_priority_t}；
 *                 在同一并发队列内，高优先级任务优先于低优先级任务被调度。超出合法范围的值会被静默忽略。
 * @since 12
 */
FFRT_C_API void ffrt_task_attr_set_queue_priority(ffrt_task_attr_t* attr, ffrt_queue_priority_t priority);

/**
 * @brief 获取任务属性的优先级。
 *
 * @param attr 指向任务属性的指针。
 * @return 并发队列任务的优先级。
 * @since 12
 */
FFRT_C_API ffrt_queue_priority_t ffrt_task_attr_get_queue_priority(const ffrt_task_attr_t* attr);

/**
 * @brief 设置任务属性的栈大小。
 *
 * @param attr 指向任务属性的指针。
 * @param size 任务栈大小，单位是字节。需大于系统支持的最小栈大小，否则可能导致栈溢出；
 *             设置过大时可能导致内存分配失败。
 * @since 12
 */
FFRT_C_API void ffrt_task_attr_set_stack_size(ffrt_task_attr_t* attr, uint64_t size);

/**
 * @brief 获取任务属性的栈大小。
 *
 * @param attr 指向任务属性的指针。
 * @return 任务栈大小，单位是字节。
 * @since 12
 */
FFRT_C_API uint64_t ffrt_task_attr_get_stack_size(const ffrt_task_attr_t* attr);

/**
 * @brief 更新当前任务的QoS。
 *
 * 在任务执行过程中需要根据运行阶段动态调整调度优先级时使用本接口。
 * 例如，一个后台同步任务在用户触发相关操作后，可通过本接口提升QoS等级以加快处理速度。
 *
 * @param qos 任务待更新的QoS等级，取值参考{@link ffrt_qos_t}。
 * @return QoS更新成功，或新QoS与当前QoS相同时返回`0`；
 *         QoS映射未注册、当前任务为空，或当前任务非通用类型任务（即非通过{@link ffrt_submit_base}或{@link ffrt_submit_h_base}提交的任务）时返回`1`。
 * @see ffrt_this_task_get_qos
 * @since 10
 */
FFRT_C_API int ffrt_this_task_update_qos(ffrt_qos_t qos);

/**
 * @brief 获取当前任务的QoS。
 *
 * @return 任务QoS。
 * @since 12
 */
FFRT_C_API ffrt_qos_t ffrt_this_task_get_qos(void);

/**
 * @brief 获取当前任务的ID。
 *
 * @return 当前运行任务的唯一任务ID。
 * @since 10
 */
FFRT_C_API uint64_t ffrt_this_task_get_id(void);

/**
 * @brief 申请函数执行结构体的内存。
 *
 * 申请的内存用作任务执行体封装，在通过{@link ffrt_submit_base}或{@link ffrt_submit_h_base}提交任务时传入。
 * 该内存在所提交任务执行完成后由FFRT运行时自动释放，调用方无需手动释放。
 *
 * @param kind 函数执行结构体类型。通用类型适用于通过{@link ffrt_submit_base}或{@link ffrt_submit_h_base}
 *             提交的任务，队列类型适用于通过并发队列提交接口提交的任务。
 * @return 内存申请成功时返回非空指针；
 *         否则返回空指针。
 * @see ffrt_submit_base
 * @see ffrt_submit_h_base
 * @since 10
 */
FFRT_C_API void* ffrt_alloc_auto_managed_function_storage_base(ffrt_function_kind_t kind);

/**
 * @brief 提交任务调度执行。
 *
 * 任务执行体、输入依赖、输出依赖和任务属性被一同提交到FFRT调度器，
 * 调度器根据依赖关系和任务QoS确定任务的执行时机并选择工作线程执行该任务。
 * 本接口为底层提交接口，若任务不需要销毁回调，可使用简化接口{@link ffrt_submit_f}。
 * 与{@link ffrt_submit_h_base}的区别在于本接口不返回任务句柄，
 * 适用于不需要对已提交任务进行后续依赖管理或等待的场景。
 * 若任务属性中已通过{@link ffrt_task_attr_set_delay}设置延迟时间，
 * 则输入输出依赖关系不再生效，任务在延迟结束后被调度。
 *
 * @param f 任务执行体封装的指针，需通过{@link ffrt_alloc_auto_managed_function_storage_base}申请内存，
 *          且必须包含任务销毁回调函数。
 * @param in_deps 指向输入依赖的指针。
 * @param out_deps 指向输出依赖的指针。
 * @param attr 指向任务属性的指针。
 * @see ffrt_submit_h_base
 * @since 10
 */
FFRT_C_API void ffrt_submit_base(ffrt_function_header_t* f, const ffrt_deps_t* in_deps, const ffrt_deps_t* out_deps,
    const ffrt_task_attr_t* attr);

/**
 * @brief 提交任务调度执行并返回任务句柄。
 *
 * 任务执行体、输入依赖、输出依赖和任务属性被一同提交到FFRT调度器，调度器根据依赖关系确定任务的执行时机。
 * 返回的任务句柄可用于通过{@link ffrt_wait_deps}等待任务完成，
 * 或作为其他任务的输入依赖以构建任务间的依赖关系。
 * 本接口为返回任务句柄的底层提交接口，若任务不需要销毁回调，可使用简化接口{@link ffrt_submit_h_f}。
 * 返回的任务句柄需通过{@link ffrt_task_handle_destroy}销毁，
 * 引用计数可通过{@link ffrt_task_handle_inc_ref}和{@link ffrt_task_handle_dec_ref}管理。
 *
 * @param f 任务执行体封装的指针，需通过{@link ffrt_alloc_auto_managed_function_storage_base}申请内存，
 *          且必须包含任务销毁回调函数。
 * @param in_deps 指向输入依赖的指针。
 * @param out_deps 指向输出依赖的指针。
 * @param attr 指向任务属性的指针。
 * @return 任务提交成功时返回非空的任务句柄；
 *         否则返回空指针。
 * @see ffrt_submit_base
 * @since 10
 */
FFRT_C_API ffrt_task_handle_t ffrt_submit_h_base(ffrt_function_header_t* f, const ffrt_deps_t* in_deps,
    const ffrt_deps_t* out_deps, const ffrt_task_attr_t* attr);

/**
 * @brief 提交任务调度执行，是{@link ffrt_submit_base}接口的简化形式。
 *
 * 该接口将给定的任务函数及其参数包装为通用任务结构体（`ffrt_function_kind_general`），
 * 其中用于处理执行后清理的任务销毁回调（after_func）会被设为NULL，
 * 因而省略任何额外清理动作。封装后的任务结构体随后通过{@link ffrt_submit_base}接口提交。
 * 若任务属性中已通过{@link ffrt_task_attr_set_delay}设置延迟时间，
 * 则输入输出依赖关系不再生效，任务在延迟结束后被调度。
 *
 * @param func 待执行的任务函数。
 * @param arg 指向传递给任务函数的参数或闭包数据的指针。
 * @param in_deps 指向输入依赖的指针。
 * @param out_deps 指向输出依赖的指针。
 * @param attr 指向任务属性的指针。
 * @see ffrt_submit_base
 * @since 20
 */
FFRT_C_API void ffrt_submit_f(ffrt_function_t func, void* arg, const ffrt_deps_t* in_deps, const ffrt_deps_t* out_deps,
    const ffrt_task_attr_t* attr);

/**
 * @brief 提交任务调度执行并返回任务句柄，是{@link ffrt_submit_h_base}接口的简化形式。
 *
 * 该接口将给定的任务函数及其参数包装为通用任务结构体（`ffrt_function_kind_general`），
 * 其中用于处理执行后清理的任务销毁回调（after_func）会被设为NULL，
 * 因而省略任何额外清理动作。封装后的任务结构体随后通过{@link ffrt_submit_h_base}接口提交。
 * 若任务属性中已通过{@link ffrt_task_attr_set_delay}设置延迟时间，
 * 则输入输出依赖关系不再生效，任务在延迟结束后被调度。
 * 返回的任务句柄需通过{@link ffrt_task_handle_destroy}销毁。
 *
 * @param func 待执行的任务函数。
 * @param arg 指向传递给任务函数的参数或闭包数据的指针。
 * @param in_deps 指向输入依赖的指针。
 * @param out_deps 指向输出依赖的指针。
 * @param attr 指向任务属性的指针。
 * @return 任务提交成功时返回非空的任务句柄；
 *         否则返回空指针。
 * @see ffrt_submit_h_base
 * @since 20
 */
FFRT_C_API ffrt_task_handle_t ffrt_submit_h_f(ffrt_function_t func, void* arg, const ffrt_deps_t* in_deps,
    const ffrt_deps_t* out_deps, const ffrt_task_attr_t* attr);

/**
 * @brief 增加任务句柄的引用计数。
 *
 * 任务句柄的引用计数加一，并返回增加前的引用计数值。
 *
 * @param handle 任务句柄，由{@link ffrt_submit_h_base}或{@link ffrt_submit_h_f}返回。
 * @return 任务句柄增加前的引用计数值；若`handle`为null则返回`UINT_MAX`。
 * @since 12
 */
FFRT_C_API uint32_t ffrt_task_handle_inc_ref(ffrt_task_handle_t handle);

/**
 * @brief 减少任务句柄的引用计数。
 *
 * 任务句柄的引用计数减一，并返回减少前的引用计数值。
 * 本接口应与{@link ffrt_task_handle_inc_ref}配对使用，句柄不再使用时需通过{@link ffrt_task_handle_destroy}销毁。
 *
 * @param handle 任务句柄。
 * @return 任务句柄减少前的引用计数值；若`handle`为null则返回`UINT_MAX`。
 * @since 12
 */
FFRT_C_API uint32_t ffrt_task_handle_dec_ref(ffrt_task_handle_t handle);

/**
 * @brief 销毁任务句柄。
 *
 * 调用后，任务句柄被销毁并释放关联的资源，句柄不可再使用。
 *
 * @param handle 任务句柄。
 * @since 10
 */
FFRT_C_API void ffrt_task_handle_destroy(ffrt_task_handle_t handle);

/**
 * @brief 阻塞当前任务，等待依赖任务完成后再继续执行。
 *
 * @param deps 指向依赖任务列表的指针。阻塞当前任务，直到该依赖列表引用的所有任务执行完毕。
 * @since 10
 */
FFRT_C_API void ffrt_wait_deps(const ffrt_deps_t* deps);

/**
 * @brief 阻塞当前任务，等待所有已提交任务完成后再继续执行。
 *
 * @since 10
 */
FFRT_C_API void ffrt_wait(void);

#endif // FFRT_API_C_TASK_H
/** @} */
