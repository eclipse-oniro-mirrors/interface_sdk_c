/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup TransientTask
 * @{

 * @brief Provide C interface for the transient task management.
 * @since 13
 * @version 1.0
 */

/**
 * @file transient_task_type.h
 *
 * @brief Defines the data structures for the C APIs of transient task.
 *
 * @library libtransient_task.so
 * @kit BackgroundTasksKit
 * @syscap SystemCapability.ResourceSchedule.BackgroundTaskManager.TransientTask
 * @since 11
 */

#ifndef OHOS_BACKGROUOND_TASK_MANAGER_TRANSIENT_TASK_TYPE_H
#define OHOS_BACKGROUOND_TASK_MANAGER_TRANSIENT_TASK_TYPE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the maximum number of transient tasks at the same time.
 * 
 * @since 20
 */
#define TRANSIENT_TASK_MAX_NUM 3

/**
 * @brief Enumerates the error codes available for a transient task.
 * 
 * @since 13
 */
typedef enum TransientTask_ErrorCode {
    /**
     * Operation successful.
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_OK = 0,
    /**
     * Parameter check failed. Possible causes: 1. Mandatory parameters are not passed. 2. Incorrect parameter types.
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_INVALID_PARAM = 401,
    /**
     * Parcel read/write operation failed.
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_PARCEL_FAILED = 9800002,
    /**
     * IPC failed.
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_TRANSACTION_FAILED = 9800003,
    /**
     * System service failed.
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_SYS_NOT_READY = 9800004,
    /**
     * Failed to verify the client information of the transient task.
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_CLIENT_INFO_VERIFICATION_FAILED = 9900001,
    /**
     * Failed to verify the server information of the transient task.
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_SERVICE_VERIFICATION_FAILED = 9900002,
    /**
     * Parcel read/write operation failed for the transient task. Possible causes:
     *     1. The parameter is invalid.
     *     2. Memory allocation fails.
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_PARCELABLE_FAILED = 9900003,
    /**
     * System service failed.
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_SERVICE_NOT_READY = 9900004,
} TransientTask_ErrorCode;

/**
 * @brief A struct that describes the returned information about a transient task. The struct returns the ID and
 * remaining time of the transient task.
 * 
 * @since 13
 * @version 1.0
 */
typedef struct TransientTask_DelaySuspendInfo {
    /**
     * Request ID of a transient task.
     *
     * @since 13
     */
    int32_t requestId;
    /**
     * Remaining time, in ms.
     *
     * @since 13
     */
    int32_t actualDelayTime;
} TransientTask_DelaySuspendInfo;

/**
 * @brief A struct that describes all transient task information. The struct returns all transient task information,
 * including the remaining quota of the current day.
 * 
 * @since 20
 * @version 1.0
 */
typedef struct TransientTask_TransientTaskInfo {
    /**
     * Remaining quota of the current day, in ms.
     *
     * @since 20
     */
    int32_t remainingQuota;
    /** The info of delay suspend
     *
     * @since 20
     */
    TransientTask_DelaySuspendInfo transientTasks[TRANSIENT_TASK_MAX_NUM];
} TransientTask_TransientTaskInfo;

/**
 * @brief Defines a callback for transient task timeout.
 * 
 * @since 13
 */
typedef void (*TransientTask_Callback)(void);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
