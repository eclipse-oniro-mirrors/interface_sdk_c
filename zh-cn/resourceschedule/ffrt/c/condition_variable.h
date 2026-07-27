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
 * @file condition_variable.h
 *
 * @brief 声明条件变量的C接口。
 *
 * @library libffrt.z.so
 * @kit FunctionFlowRuntimeKit
 * @syscap SystemCapability.Resourceschedule.Ffrt.Core
 * @since 10
 */

#ifndef FFRT_API_C_CONDITION_VARIABLE_H
#define FFRT_API_C_CONDITION_VARIABLE_H

#include <time.h>
#include "type_def.h"

/**
 * @brief 初始化条件变量。
 *
 * 该条件变量不再使用时，必须通过{@link ffrt_cond_destroy}销毁。
 *
 * @param cond 指向条件变量的指针。
 * @param attr 指向条件变量属性的指针。
 * @return 条件变量初始化成功时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @since 10
 */
FFRT_C_API int ffrt_cond_init(ffrt_cond_t* cond, const ffrt_condattr_t* attr);

/**
 * @brief 唤醒至少一个阻塞在条件变量上的线程。
 *
 * @param cond 指向条件变量的指针。
 * @return 线程被唤醒时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @see ffrt_cond_wait
 * @since 10
 */
FFRT_C_API int ffrt_cond_signal(ffrt_cond_t* cond);

/**
 * @brief 唤醒当前阻塞在条件变量上的所有线程。
 *
 * @param cond 指向条件变量的指针。
 * @return 线程被唤醒时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @see ffrt_cond_wait
 * @since 10
 */
FFRT_C_API int ffrt_cond_broadcast(ffrt_cond_t* cond);

/**
 * @brief 将调用线程阻塞在条件变量上。
 *
 * 调用线程在进入时必须持有该mutex。阻塞期间会原子地释放该mutex，并在函数返回前重新获取，
 * 因此调用方在唤醒时重新获得mutex的所有权。线程由另一个线程调用{@link ffrt_cond_signal}
 * 或{@link ffrt_cond_broadcast}唤醒。调用方需在唤醒后重新检查谓词，以防止虚假唤醒。
 *
 * @param cond 指向条件变量的指针。
 * @param mutex 指向调用线程持有的mutex的指针。
 * @return 阻塞后被成功唤醒时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @see ffrt_cond_timedwait
 * @see ffrt_cond_signal
 * @see ffrt_cond_broadcast
 * @since 10
 */
FFRT_C_API int ffrt_cond_wait(ffrt_cond_t* cond, ffrt_mutex_t* mutex);

/**
 * @brief 将调用线程阻塞至给定的时间点。
 *
 * 如果在到达`time_point`前没有调用{@link ffrt_cond_signal}或{@link ffrt_cond_broadcast}来唤醒线程，
 * 线程会被自动唤醒。
 *
 * @param cond 指向条件变量的指针。
 * @param mutex 指向mutex的指针。
 * @param time_point 等待到期的绝对时间点。
 * @return 阻塞后被成功唤醒时返回`ffrt_success`；
 *         未被唤醒且到达`time_point`时返回`ffrt_error_timedout`；
 *         `cond`、`mutex`或`time_point`任一为null时返回`ffrt_error_inval`。
 * @see ffrt_cond_wait
 * @see ffrt_cond_signal
 * @see ffrt_cond_broadcast
 * @since 10
 */
FFRT_C_API int ffrt_cond_timedwait(ffrt_cond_t* cond, ffrt_mutex_t* mutex, const struct timespec* time_point);

/**
 * @brief 销毁条件变量。
 *
 * 该条件变量必须已通过{@link ffrt_cond_init}初始化，且在调用本接口时不得被任何线程引用。
 *
 * @param cond 指向条件变量的指针。
 * @return 条件变量销毁成功时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @since 10
 */
FFRT_C_API int ffrt_cond_destroy(ffrt_cond_t* cond);

#endif // FFRT_API_C_CONDITION_VARIABLE_H
/** @} */
