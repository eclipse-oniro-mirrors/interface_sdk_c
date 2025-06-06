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
 * @brief max number for transient task.
 *
 * @since 20
 */
#define TRANSIENT_TASK_MAX_NUM 3

/**
 * @brief Enum for transient task error code.
 * @since 13
 */
typedef enum TransientTask_ErrorCode {
    /**
     * @error result is ok.
     */
    ERR_TRANSIENT_TASK_OK = 0,
    /**
     * @error Parameter error. Possible causes:
     * 1. Mandatory parameters are left unspecified;
     * 2. Incorrect parameters types.
     */
    ERR_TRANSIENT_TASK_INVALID_PARAM = 401,
    /**
     * @error Parcel operation failed.
     */
    ERR_TRANSIENT_TASK_PARCEL_FAILED = 9800002,
    /**
     * @error Internal transaction failed.
     */
    ERR_TRANSIENT_TASK_TRANSACTION_FAILED = 9800003,
    /**
     * @error System service operation failed.
     */
    ERR_TRANSIENT_TASK_SYS_NOT_READY = 9800004,
    /**
     * Caller information verification failed for a transient task.
     */
    ERR_TRANSIENT_TASK_CLIENT_INFO_VERIFICATION_FAILED = 9900001,
    /**
     * Transient task verification failed.
     */
    ERR_TRANSIENT_TASK_SERVICE_VERIFICATION_FAILED = 9900002,
    /**
     * @error Failed to write data into parcel. Possible reasons:
     * 1. Invalid parameters;
     * 2. Failed to apply for memory.
     */
    ERR_TRANSIENT_TASK_PARCELABLE_FAILED = 9900003,
    /**
     * @error System service operation failed.
     */
    ERR_TRANSIENT_TASK_SERVICE_NOT_READY = 9900004,
} TransientTask_ErrorCode;

/**
 * @brief Define DelaySuspendInfo for TransientTask.
 *
 * @since 13
 * @version 1.0
 */
typedef struct TransientTask_DelaySuspendInfo {
    /** The unique identifier of the delay request */
    int32_t requestId;
    /** The actual delay duration (ms) */
    int32_t actualDelayTime;
} TransientTask_DelaySuspendInfo;

/**
 * @brief Define TransientTaskInfo for an application.
 *
 * @since 20
 * @version 1.0
 */
typedef struct TransientTask_TransientTaskInfo {
    /** The remaining quota of the delay request */
    int32_t remainingQuota;
    /** The info of delay suspend */
    TransientTask_DelaySuspendInfo transientTasks[TRANSIENT_TASK_MAX_NUM];
} TransientTask_TransientTaskInfo;

/**
 * @brief Define a callback function when delay time expired.
 * @since 13
 */
typedef void (*TransientTask_Callback)(void);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
