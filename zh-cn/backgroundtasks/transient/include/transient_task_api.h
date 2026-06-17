/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @brief 申请短时任务。
 *
 * @param reason 申请短时任务的原因。
 * @param callback 短时任务即将超时的回调，一般在超时前6秒，通过此回调通知应用。
 * @param info 返回短时任务信息。
 * @return 返回0，表示申请成功。
 *     返回401，表示入参错误。
 *     返回9800002，表示Parcel读写操作失败。
 *     返回9800003，表示IPC通信失败。
 *     返回9800004，表示系统服务失败。
 *     返回9900001，表示短时任务客户端信息校验失败。
 *     返回9900002，表示短时任务服务端校验失败。
 *     错误码的具体信息请参考{@link TransientTask_ErrorCode}。
 * @since 13
 * @version 1.0
 */
int32_t OH_BackgroundTaskManager_RequestSuspendDelay(const char* reason,
    TransientTask_Callback callback, TransientTask_DelaySuspendInfo *info);

/**
 * @brief 获取本次短时任务的剩余时间。
 *
 * @param requestId 短时任务的请求ID。
 * @param delayTime 短时任务的剩余时间，单位：ms。
 * @return 返回0，表示查询成功。
 *     返回401，表示入参错误。
 *     返回9800002，表示Parcel读写操作失败。
 *     返回9800003，表示IPC通信失败。
 *     返回9800004，表示系统服务失败。
 *     返回9900001，表示短时任务客户端信息校验失败。
 *     返回9900002，表示短时任务服务端校验失败。
 *     错误码的具体信息请参考{@link TransientTask_ErrorCode}。
 * @since 13
 * @version 1.0
 */
int32_t OH_BackgroundTaskManager_GetRemainingDelayTime(int32_t requestId, int32_t *delayTime);

/**
 * @brief 取消短时任务。
 *
 * @param requestId 短时任务的请求ID。
 * @return 返回0，表示取消成功。
 *     返回401，表示入参错误。
 *     返回9800002，表示Parcel读写操作失败。
 *     返回9800003，表示IPC通信失败。
 *     返回9800004，表示系统服务失败。
 *     返回9900001，表示短时任务客户端信息校验失败。
 *     返回9900002，表示短时任务服务端校验失败。
 *     错误码的具体信息请参考{@link TransientTask_ErrorCode}。
 * @since 13
 * @version 1.0
 */
int32_t OH_BackgroundTaskManager_CancelSuspendDelay(int32_t requestId);

/**
 * @brief 获取所有短时任务信息，如当日剩余总配额等。
 *
 * @param transientTaskInfo 所有短时任务信息，具体请参考{@link TransientTask_TransientTaskInfo}。
 * @return 返回0，表示获取成功。
 *     返回9900001，表示短时任务客户端信息校验失败。
 *     返回9900003，表示Parcel读写操作失败。
 *     返回9900004，表示系统服务失败。
 *     错误码的具体信息请参考{@link TransientTask_ErrorCode}。
 * @since 20
 * @version 1.0
 */
int32_t OH_BackgroundTaskManager_GetTransientTaskInfo(TransientTask_TransientTaskInfo *transientTaskInfo);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
