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
 *
 * @brief Provide C interface for the Transient task management.
 *
 * @since 13
 * @version 1.0
 */

/**
 * @file transient_task_api.h
 *
 * @brief Declares the APIs for Transient task management.
 *
 * @library libtransient_task.so
 * @kit BackgroundTasksKit
 * @syscap SystemCapability.ResourceSchedule.BackgroundTaskManager.TransientTask
 * @since 13
 */

#ifndef OHOS_BACKGROUOND_TASK_MANAGER_TRANSIENT_TASK_API_H
#define OHOS_BACKGROUOND_TASK_MANAGER_TRANSIENT_TASK_API_H

#include <stdint.h>

#include "transient_task_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Requests a transient task.
 *
 * @param reason Reason for requesting the transient task.
 * @param callback Callback used to notify the application that the transient task is about to time out. Generally, the
 *     callback is invoked 6 seconds before the timeout.
 * @param info Indicates the info of delay request.
 * @return <ul><li>{@link ERR_TRANSIENT_TASK_OK} 0 - Success.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_INVALID_PARAM} 401 - Invalid parameter.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_PARCEL_FAILED} 9800002 - Parcelable failed.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_TRANSACTION_FAILED} 9800003 - Transact failed.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_SYS_NOT_READY} 9800004 - System service not ready.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_CLIENT_INFO_VERIFICATION_FAILED} 9900001 - uid or pid info verify failed.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_SERVICE_VERIFICATION_FAILED} 9900002 - Transient task verification failed.</li>
 *     </ul>
 * @syscap SystemCapability.ResourceSchedule.BackgroundTaskManager.TransientTask
 * @since 13
 * @version 1.0
 */
int32_t OH_BackgroundTaskManager_RequestSuspendDelay(const char* reason,
    TransientTask_Callback callback, TransientTask_DelaySuspendInfo *info);

/**
 * @brief Obtains the remaining time of a transient task.
 *
 * @param requestId Request ID of the transient task.
 * @param delayTime Pointer to the remaining time of the transient task, in ms.
 * @return <ul><li>{@link ERR_TRANSIENT_TASK_OK} 0 - Success.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_INVALID_PARAM} 401 - Invalid parameter.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_PARCEL_FAILED} 9800002 - Parcelable failed.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_TRANSACTION_FAILED} 9800003 - Transact failed.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_SYS_NOT_READY} 9800004 - System service not ready.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_CLIENT_INFO_VERIFICATION_FAILED} 9900001 - uid or pid info verify failed.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_SERVICE_VERIFICATION_FAILED} 9900002 - Transient task verification failed.</li>
 *     </ul>
 * @syscap SystemCapability.ResourceSchedule.BackgroundTaskManager.TransientTask
 * @since 13
 * @version 1.0
 */
int32_t OH_BackgroundTaskManager_GetRemainingDelayTime(int32_t requestId, int32_t *delayTime);

/**
 * @brief Cancels a transient task.
 *
 * @param requestId Request ID of the transient task.
 * @return <ul><li>{@link ERR_TRANSIENT_TASK_OK} 0 - Success.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_INVALID_PARAM} 401 - Invalid parameter.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_PARCEL_FAILED} 9800002 - Parcelable failed.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_TRANSACTION_FAILED} 9800003 - Transact failed.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_SYS_NOT_READY} 9800004 - System service not ready.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_CLIENT_INFO_VERIFICATION_FAILED} 9900001 - uid or pid info verify failed.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_SERVICE_VERIFICATION_FAILED} 9900002 - Transient task verification failed.</li>
 *     </ul>
 * @syscap SystemCapability.ResourceSchedule.BackgroundTaskManager.TransientTask
 * @since 13
 * @version 1.0
 */
int32_t OH_BackgroundTaskManager_CancelSuspendDelay(int32_t requestId);

/**
 * @brief Obtains all information about a transient task, including the remaining quota of the current day.
 *
 * @param transientTaskInfo All information about a transient task. For details, see
 *     {@link TransientTask_TransientTaskInfo}.
 * @return <ul><li>{@link ERR_TRANSIENT_TASK_OK} 0 - Success.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_CLIENT_INFO_VERIFICATION_FAILED} 9900001 - uid or pid info verify failed.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_PARCELABLE_FAILED} 9900003 - Failed to write data into parcel.</li>
 *     <li>{@link ERR_TRANSIENT_TASK_SERVICE_NOT_READY} 9900004 - System service operation failed.</li>
 *     </ul>
 * @since 20
 * @version 1.0
 */
int32_t OH_BackgroundTaskManager_GetTransientTaskInfo(TransientTask_TransientTaskInfo *transientTaskInfo);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
