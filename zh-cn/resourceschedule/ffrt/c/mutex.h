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
 * @file mutex.h
 *
 * @brief 声明互斥锁（mutex）的C接口，用于在并发任务间提供互斥访问，保护共享资源免受竞争条件影响。
 *
 * @library libffrt.z.so
 * @kit FunctionFlowRuntimeKit
 * @syscap SystemCapability.Resourceschedule.Ffrt.Core
 * @since 10
 */

#ifndef FFRT_API_C_MUTEX_H
#define FFRT_API_C_MUTEX_H

#include "type_def.h"

/**
 * @brief 初始化mutex属性。
 *
 * 初始化成功后，mutex属性被设置为默认值。该mutex属性不再使用时，必须通过{@link ffrt_mutexattr_destroy}销毁。
 *
 * @param attr 指向mutex属性的指针。
 * @return mutex属性初始化成功时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @since 12
 */
FFRT_C_API int ffrt_mutexattr_init(ffrt_mutexattr_t* attr);

/**
 * @brief 设置mutex属性的类型。
 *
 * 类型可以是`ffrt_mutex_normal`（普通互斥锁）或`ffrt_mutex_recursive`（递归互斥锁，
 * 允许同一任务多次获取该锁）。
 *
 * @param attr 指向mutex属性的指针。
 * @param type mutex类型，取值为`ffrt_mutex_normal`、`ffrt_mutex_recursive`或`ffrt_mutex_default`（等价于`ffrt_mutex_normal`）。
 * @return mutex属性类型设置成功时返回`ffrt_success`；
 *         当attr为空指针，或mutex属性类型既不是`ffrt_mutex_normal`也不是`ffrt_mutex_recursive`时
 *         返回`ffrt_error_inval`。
 * @see ffrt_mutex_type
 * @since 12
 */
FFRT_C_API int ffrt_mutexattr_settype(ffrt_mutexattr_t* attr, int type);

/**
 * @brief 获取mutex属性的类型。
 *
 * 调用成功后，类型值通过出参`type`返回。
 *
 * @param attr 指向mutex属性的指针。
 * @param type 指向mutex类型的指针，用于接收获取的类型值（`ffrt_mutex_normal`或`ffrt_mutex_recursive`）。
 * @return mutex属性类型获取成功时返回`ffrt_success`；
 *         attr或type为空指针时返回`ffrt_error_inval`。
 * @since 12
 */
FFRT_C_API int ffrt_mutexattr_gettype(ffrt_mutexattr_t* attr, int* type);

/**
 * @brief 销毁mutex属性。
 *
 * 该mutex属性必须已通过{@link ffrt_mutexattr_init}初始化。
 *
 * @param attr 指向mutex属性的指针。
 * @return mutex属性销毁成功时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @since 12
 */
FFRT_C_API int ffrt_mutexattr_destroy(ffrt_mutexattr_t* attr);

/**
 * @brief 初始化mutex。
 *
 * 该mutex不再使用时，必须通过{@link ffrt_mutex_destroy}销毁。通过`attr`传入已配置的mutex属性，或传入空指针使用默认值。
 *
 * @param mutex 指向mutex的指针。
 * @param attr 指向mutex属性的指针，或传入空指针使用默认值。
 * @return mutex初始化成功时返回`ffrt_success`；
 *         `mutex`为空，或`attr`非空但未指定合法的mutex类型时返回`ffrt_error_inval`。
 * @since 10
 */
FFRT_C_API int ffrt_mutex_init(ffrt_mutex_t* mutex, const ffrt_mutexattr_t* attr);

/**
 * @brief 加锁mutex。
 *
 * 若mutex已被其他线程持有，则阻塞当前线程直到mutex可用。成功时，调用线程持有该mutex，
 * 直至通过{@link ffrt_mutex_unlock}释放。
 *
 * @param mutex 指向mutex的指针。
 * @return mutex加锁成功时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @see ffrt_mutex_trylock
 * @since 10
 */
FFRT_C_API int ffrt_mutex_lock(ffrt_mutex_t* mutex);

/**
 * @brief 解锁mutex。
 *
 * 调用线程必须已持有该mutex，且该锁之前由{@link ffrt_mutex_lock}或{@link ffrt_mutex_trylock}获取。
 *
 * @param mutex 指向mutex的指针。
 * @return mutex解锁成功时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @since 10
 */
FFRT_C_API int ffrt_mutex_unlock(ffrt_mutex_t* mutex);

/**
 * @brief 尝试加锁mutex。
 *
 * 该接口为非阻塞操作：若mutex已被其他线程持有，则立即返回错误码。成功时，调用线程
 * 持有该mutex，直至通过{@link ffrt_mutex_unlock}释放。
 *
 * @param mutex 指向mutex的指针。
 * @return mutex加锁成功时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`或`ffrt_error_busy`。
 * @see ffrt_mutex_lock
 * @since 10
 */
FFRT_C_API int ffrt_mutex_trylock(ffrt_mutex_t* mutex);

/**
 * @brief 销毁mutex。
 *
 * 调用成功后，mutex占用的资源被释放，该mutex对象不可再使用。该mutex必须已通过{@link ffrt_mutex_init}
 * 初始化，且在调用本接口时不得被任何线程持有。
 *
 * @param mutex 指向mutex的指针。
 * @return mutex销毁成功时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @since 10
 */
FFRT_C_API int ffrt_mutex_destroy(ffrt_mutex_t* mutex);

#endif // FFRT_API_C_MUTEX_H
/** @} */
