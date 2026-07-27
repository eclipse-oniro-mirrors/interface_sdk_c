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
 * @file sleep.h
 *
 * @brief 声明{@link ffrt_usleep}和{@link ffrt_yield}的C接口。
 *
 * @library libffrt.z.so
 * @kit FunctionFlowRuntimeKit
 * @syscap SystemCapability.Resourceschedule.Ffrt.Core
 * @since 10
 */

#ifndef FFRT_API_C_SLEEP_H
#define FFRT_API_C_SLEEP_H

#include <stdint.h>
#include "type_def.h"

/**
 * @brief 将调用线程挂起指定的时长。
 *
 * 若`usec`超过支持的最大值则按最大值截断。
 *
 * @param usec 调用线程被挂起的时长，单位是微秒。
 * @return `ffrt_success`。该函数不会失败。
 * @since 10
 */
FFRT_C_API int ffrt_usleep(uint64_t usec);

/**
 * @brief 将控制权让出给其他任务，使其有机会被执行。
 *
 * @since 10
 */
FFRT_C_API void ffrt_yield(void);

#endif // FFRT_API_C_SLEEP_H
/** @} */
