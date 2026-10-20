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
 * @since 18
 */

/**
 * @file shared_mutex.h
 *
 * @brief 声明读写锁（rwlock）的C接口。
 *
 * @library libffrt.z.so
 * @kit FunctionFlowRuntimeKit
 * @syscap SystemCapability.Resourceschedule.Ffrt.Core
 * @since 18
 */

#ifndef FFRT_API_C_SHARED_MUTEX_H
#define FFRT_API_C_SHARED_MUTEX_H

#include "type_def.h"

/**
 * @brief 初始化rwlock。
 *
 * 该rwlock不再使用时，必须通过{@link ffrt_rwlock_destroy}销毁。
 *
 * @param rwlock 指向rwlock的指针。
 * @param attr 指向rwlock属性的指针。
 *             当前仅支持默认模式，需设置为空指针。
 * @return rwlock初始化成功且attr为空指针时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @since 18
 */
FFRT_C_API int ffrt_rwlock_init(ffrt_rwlock_t* rwlock, const ffrt_rwlockattr_t* attr);

/**
 * @brief 加写锁。
 *
 * 锁不可用时阻塞当前线程。成功时，调用线程持有排他写锁，直至通过{@link ffrt_rwlock_unlock}
 * 释放。写锁具有排他性，不允许与任何读锁同时持有。
 *
 * @param rwlock 指向rwlock的指针。
 * @return rwlock加锁成功时返回`ffrt_success`；
 *         `rwlock`为空指针时返回`ffrt_error_inval`。
 * @see ffrt_rwlock_rdlock
 * @see ffrt_rwlock_trywrlock
 * @since 18
 */
FFRT_C_API int ffrt_rwlock_wrlock(ffrt_rwlock_t* rwlock);

/**
 * @brief 尝试加写锁。
 *
 * 不会阻塞当前线程。成功时，调用线程持有排他写锁，直至通过{@link ffrt_rwlock_unlock}释放。
 *
 * @param rwlock 指向rwlock的指针。
 * @return rwlock加锁成功时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`或`ffrt_error_busy`。
 * @see ffrt_rwlock_wrlock
 * @since 18
 */
FFRT_C_API int ffrt_rwlock_trywrlock(ffrt_rwlock_t* rwlock);

/**
 * @brief 加读锁。
 *
 * 锁不可用时阻塞当前线程。成功时，调用线程持有读锁，直至通过{@link ffrt_rwlock_unlock}释放。
 * 多个读者可同时持有该锁，但不允许与写锁同时持有。
 *
 * @param rwlock 指向rwlock的指针。
 * @return rwlock加锁成功时返回`ffrt_success`；
 *         `rwlock`为空指针时返回`ffrt_error_inval`。
 * @see ffrt_rwlock_wrlock
 * @see ffrt_rwlock_tryrdlock
 * @since 18
 */
FFRT_C_API int ffrt_rwlock_rdlock(ffrt_rwlock_t* rwlock);

/**
 * @brief 尝试加读锁。
 *
 * 不会阻塞当前线程。成功时，调用线程持有读锁，直至通过{@link ffrt_rwlock_unlock}释放。
 *
 * @param rwlock 指向rwlock的指针。
 * @return rwlock加锁成功时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`或`ffrt_error_busy`。
 * @see ffrt_rwlock_rdlock
 * @since 18
 */
FFRT_C_API int ffrt_rwlock_tryrdlock(ffrt_rwlock_t* rwlock);

/**
 * @brief 解锁rwlock。
 *
 * 调用线程必须已持有该rwlock，且该锁之前由{@link ffrt_rwlock_rdlock}、{@link ffrt_rwlock_tryrdlock}、
 * {@link ffrt_rwlock_wrlock}或{@link ffrt_rwlock_trywrlock}获取。
 *
 * @param rwlock 指向rwlock的指针。
 * @return rwlock解锁成功时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @since 18
 */
FFRT_C_API int ffrt_rwlock_unlock(ffrt_rwlock_t* rwlock);

/**
 * @brief 销毁rwlock。
 *
 * 该rwlock必须已通过{@link ffrt_rwlock_init}初始化，且在调用本接口时不得被任何线程以读锁或写锁持有。
 *
 * @param rwlock 指向rwlock的指针。
 * @return rwlock销毁成功时返回`ffrt_success`；
 *         否则返回`ffrt_error_inval`。
 * @since 18
 */
FFRT_C_API int ffrt_rwlock_destroy(ffrt_rwlock_t* rwlock);

#endif // FFRT_API_C_SHARED_MUTEX_H
/** @} */
