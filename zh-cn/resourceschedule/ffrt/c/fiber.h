/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @since 20
 */

/**
 * @file fiber.h
 *
 * @brief 声明纤程的C接口。
 *
 * 纤程是一种轻量级的用户态线程，用于在用户空间内实现高效的任务调度和上下文切换。
 *
 * @library libffrt.z.so
 * @kit FunctionFlowRuntimeKit
 * @syscap SystemCapability.Resourceschedule.Ffrt.Core
 * @since 20
 */

#ifndef FFRT_API_C_FIBER_H
#define FFRT_API_C_FIBER_H

#include <stddef.h>
#include "type_def.h"

/**
 * @brief 初始化纤程。
 *
 * 初始化纤程结构，使其准备好被执行。调用者需负责分配`stack`指向的栈内存，并保证该内存在纤程整个生命周期内有效。
 *
 * @param fiber 指向待初始化的纤程结构的指针。
 * @param func 纤程将执行的入口函数。
 * @param arg 传递给入口函数的参数。
 * @param stack 指向纤程栈所用内存区域的指针。
 * @param stack_size 栈的大小，单位是字节。必须足以容纳纤程上下文。
 * @return 纤程初始化成功时返回`ffrt_success`；
 *         `stack_size`过小（不足以容纳纤程上下文）时返回`ffrt_error_inval`。
 * @since 20
 */
FFRT_C_API int ffrt_fiber_init(ffrt_fiber_t* fiber, void(*func)(void*), void* arg, void* stack, size_t stack_size);

/**
 * @brief 在两个纤程间切换执行上下文。
 *
 * 将当前执行上下文保存到`from`指定的纤程中，并从`to`指定的纤程恢复执行上下文。
 *
 * `from`和`to`都必须指向已通过{@link ffrt_fiber_init}初始化的纤程实例；否则行为未定义。
 *
 * @param from 指向用于保存当前上下文的纤程的指针。
 * @param to 指向用于恢复执行上下文的纤程的指针。
 * @see ffrt_fiber_init
 * @since 20
 */
FFRT_C_API void ffrt_fiber_switch(ffrt_fiber_t* from, ffrt_fiber_t* to);

#endif // FFRT_API_C_FIBER_H
/** @} */
