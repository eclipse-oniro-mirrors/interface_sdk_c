/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup BackgroundProcessManager
 * @{
 *
 * @brief BackgroundProcessManager provides APIs.
 *
 * @since 17
 */
/**
 * @file background_process_manager.h
 *
 * @brief 本模块提供了后台子进程管控接口。开发者可以通过本模块接口对子进程进行压制、解压制，避免子进程过多占用系统资源，导致系统使用卡顿。本模块接口仅对通过
 * {@link OH_Ability_StartNativeChildProcess}接口创建的子进程生效。
 *
 * @library libbackground_process_manager.z.so
 * @kit BackgroundTasksKit
 * @syscap SystemCapability.Resourceschedule.BackgroundProcessManager
 * @since 17
 */

#ifndef RESOURCESCHEDULE_BACKGROUND_PROCESS_MANAGER_H
#define RESOURCESCHEDULE_BACKGROUND_PROCESS_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 子进程压制档位。
 *
 * @since 17
 */
typedef enum BackgroundProcessManager_ProcessPriority {
    /**
     * @brief 该档位相较PROCESS_INACTIVE压制效果更显著，获取到的CPU资源更少。推荐执行处于后台的图文页面等用户无感知业务的后台子进程时设置该档位。
     *
     * @since 17
     */
    PROCESS_BACKGROUND = 1,

    /**
     * @brief 推荐正在执行播放音频、导航等用户可感知业务的后台子进程时设置该档位。
     *
     * @since 17
     */
    PROCESS_INACTIVE = 2,
} BackgroundProcessManager_ProcessPriority;

/**
 * @brief 定义后台子进程管控错误码。
 *
 * @since 17
 */
typedef enum BackgroundProcessManager_ErrorCode {
    /**
     * @error result is OK.
     *
     * @since 17
     */
    ERR_BACKGROUND_PROCESS_MANAGER_SUCCESS = 0,

    /**
     * @error invalid parameter. Possible causes:
     * 1. priority is out of range.
     *
     * @since 17
     */
    ERR_BACKGROUND_PROCESS_MANAGER_INVALID_PARAM = 401,

    /**
     * @error remote error. Possible causes:
     * 1. remote is not work.
     *
     * @since 17
     */
    ERR_BACKGROUND_PROCESS_MANAGER_REMOTE_ERROR = 31800001,
} BackgroundProcessManager_ErrorCode;

/**
 * @brief 设置子进程的压制档位，子进程被压制后可获得的CPU资源将会受到限制。如果主进程调度策略发生变化，如从后台切至前台等，子进程会跟随主进程一同变化，子进程如需继续压制，需要重新调用本接口。
 *
 * @param pid 需要被压制子进程的进程号，{@link OH_Ability_StartNativeChildProcess}接口创建子进程后的pid参数，即为子进程进程号。
 * @param priority 压制档位。
 * @return 返回 {@link ERR_BACKGROUND_PROCESS_MANAGER_SUCCESS}，表示压制参数发送成功。
 * 返回 {@link ERR_BACKGROUND_PROCESS_MANAGER_INVALID_PARAM}，表示参数检查失败。
 * @since 17
 */
int OH_BackgroundProcessManager_SetProcessPriority(int pid, BackgroundProcessManager_ProcessPriority priority);

/**
 * @brief 为子进程解压制，即子进程策略恢复为主进程调度策略。若主进程调度策略发生变化，如从后台切至前台等，子进程会跟随主进程一同变化，等效于执行一次resetProcessPriority动作。
 *
 * @param pid 子进程的进程号，{@link OH_Ability_StartNativeChildProcess}接口创建子进程后的pid参数，即为子进程进程号。
 * @return 返回 {@link ERR_BACKGROUND_PROCESS_MANAGER_SUCCESS}，表示压制参数发送成功。
 * @since 17
 */
int OH_BackgroundProcessManager_ResetProcessPriority(int pid);
#ifdef __cplusplus
};
#endif
#endif // RESOURCESCHEDULE_BACKGROUND_PROCESS_MANAGER_H
/** @} */
