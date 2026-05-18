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
 * @brief The **background_process_manager.h** file declares the APIs for background child process management. You can
 * use these APIs to suppress and unsuppress child processes to prevent child processes from occupying too many system
 * resources and causing system stuttering. The APIs take effect only for the child processes created through
 * {@link OH_Ability_StartNativeChildProcess}.
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
 * @brief Enumerates child process priorities.
 * 
 * @since 17
 */
typedef enum BackgroundProcessManager_ProcessPriority {
    /**
     * @brief Compared with **PROCESS_INACTIVE**, this priority has a more obvious suppression effect. Child processes can obtain less CPU resources. You are advised to set this priority when executing background child processes that cannot be perceived by users, such as background image-text pages.
     * 
     */
    PROCESS_BACKGROUND = 1,

    /**
     * @brief You are advised to set this priority when executing background child processes that can be perceived by users, such as audio playback and navigation.
     * 
     */
    PROCESS_INACTIVE = 2,
} BackgroundProcessManager_ProcessPriority;

/**
 * @brief Enumerates the error codes used by the background child process management.
 * 
 * @since 17
 */
typedef enum BackgroundProcessManager_ErrorCode {
    /**
     * @error result is OK.
     */
    ERR_BACKGROUND_PROCESS_MANAGER_SUCCESS = 0,

    /**
     * @error invalid parameter. Possible causes:
     * 1. priority is out of range.
     */
    ERR_BACKGROUND_PROCESS_MANAGER_INVALID_PARAM = 401,

    /**
     * @error remote error. Possible causes:
     * 1. remote is not work.
     */
    ERR_BACKGROUND_PROCESS_MANAGER_REMOTE_ERROR = 31800001,
} BackgroundProcessManager_ErrorCode;

/**
 * @brief Sets the child process priority. After a child process is suppressed, the CPU resources that can be obtained
 * will be limited. If the scheduling policy of the main process changes, for example, from the background to the
 * foreground, the child process changes with the main process. To suppress the child process, call this API again.
 * 
 * @param pid ID of the child process to be suppressed, which is the value of the **pid** parameter after the child
 * process is created through the {@link OH_Ability_StartNativeChildProcess} API.
 * @param priority Suppression priority.
 * @return {@link ERR_BACKGROUND_PROCESS_MANAGER_SUCCESS} is returned if the suppression parameter is sent successfully.
 * {@link ERR_BACKGROUND_PROCESS_MANAGER_INVALID_PARAM} is returned if the parameter check fails.
 * @since 17
 */
int OH_BackgroundProcessManager_SetProcessPriority(int pid, BackgroundProcessManager_ProcessPriority priority);

/**
 * @brief Unsuppresses the child process. In this case, the child process follows the scheduling policy of the main
 * process. If the scheduling policy of the main process changes, for example, from the background to the foreground,
 * the child process changes with the main process. The effect is the same as calling **resetProcessPriority**.
 * 
 * @param pid ID of the child process, which is the value of the **pid** parameter of the
 * {@link OH_Ability_StartNativeChildProcess} API.
 * @return {@link ERR_BACKGROUND_PROCESS_MANAGER_SUCCESS} is returned if the suppression parameter is sent successfully.
 * @since 17
 */
int OH_BackgroundProcessManager_ResetProcessPriority(int pid);
#ifdef __cplusplus
};
#endif
#endif // RESOURCESCHEDULE_BACKGROUND_PROCESS_MANAGER_H
/** @} */
