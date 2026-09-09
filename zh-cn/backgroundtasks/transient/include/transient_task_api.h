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
 * @brief 提供短时任务申请、查询、取消功能。
 *
 * 短时任务允许应用在后台获得有限的时间延长以完成关键操作。
 * 系统为每个应用分配每日配额限制，超时前通过回调通知应用，超时后系统会挂起应用。
 *
 * @include <transient_task/transient_task_api.h>
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
 * @brief 申请短时任务。用于在应用进入后台或被挂起时，继续执行一些需要短时间的后台操作，如数据同步、状态保存等场景。
 *
 * @param reason 申请短时任务的原因。
 * @param callback 短时任务即将超时的回调，一般在超时前6秒，通过此回调通知应用。
 * @param info 返回短时任务信息。
 * @return 返回0，表示申请成功。
 *     <br>返回401，表示入参错误。
 *     <br>返回9800002，表示Parcel读写操作失败。
 *     <br>返回9800003，表示IPC通信失败。
 *     <br>返回9800004，表示系统服务失败。
 *     <br>返回9900001，表示短时任务客户端信息校验失败。
 *     <br>返回9900002，表示短时任务服务端校验失败。
 *     <br>错误码的具体信息请参考[TransientTask_ErrorCode](capi-transient-task-type-h.md#transienttask_errorcode)。
 * @since 13
 * @version 1.0
 */
int32_t OH_BackgroundTaskManager_RequestSuspendDelay(const char* reason,
    TransientTask_Callback callback, TransientTask_DelaySuspendInfo *info);

/**
 * @brief 获取本次短时任务的剩余时间。
 *
 * @param requestId 短时任务的请求ID。
 * 为[OH_BackgroundTaskManager_RequestSuspendDelay]{@link OH_BackgroundTaskManager_RequestSuspendDelay}成功返回的requestId。
 * @param delayTime 短时任务的剩余时间，单位：ms。
 * @return 返回0，表示查询成功。
 *     <br>返回401，表示入参错误。
 *     <br>返回9800002，表示Parcel读写操作失败。
 *     <br>返回9800003，表示IPC通信失败。
 *     <br>返回9800004，表示系统服务失败。
 *     <br>返回9900001，表示短时任务客户端信息校验失败。
 *     <br>返回9900002，表示短时任务服务端校验失败。
 *     <br>错误码的具体信息请参考[TransientTask_ErrorCode](capi-transient-task-type-h.md#transienttask_errorcode)。
 * @since 13
 * @version 1.0
 */
int32_t OH_BackgroundTaskManager_GetRemainingDelayTime(int32_t requestId, int32_t *delayTime);

/**
 * @brief 取消短时任务。
 *
 * @param requestId 短时任务的请求ID。
 * 为[OH_BackgroundTaskManager_RequestSuspendDelay]{@link OH_BackgroundTaskManager_RequestSuspendDelay}成功返回的requestId。
 * @return 返回0，表示取消成功。
 *     <br>返回401，表示入参错误。
 *     <br>返回9800002，表示Parcel读写操作失败。
 *     <br>返回9800003，表示IPC通信失败。
 *     <br>返回9800004，表示系统服务失败。
 *     <br>返回9900001，表示短时任务客户端信息校验失败。
 *     <br>返回9900002，表示短时任务服务端校验失败。
 *     <br>错误码的具体信息请参考[TransientTask_ErrorCode](capi-transient-task-type-h.md#transienttask_errorcode)。
 * @since 13
 * @version 1.0
 */
int32_t OH_BackgroundTaskManager_CancelSuspendDelay(int32_t requestId);

/**
 * @brief 获取所有短时任务信息，如当日剩余总配额等。
 *
 * @param transientTaskInfo 所有短时任务信息，
 * 具体请参考[TransientTask_TransientTaskInfo](capi-transienttask-transienttask-transienttaskinfo.md)。
 * @return 返回0，表示获取成功。
 *     <br>返回9900001，表示短时任务客户端信息校验失败。
 *     <br>返回9900003，表示Parcel读写操作失败。
 *     <br>返回9900004，表示系统服务失败。
 *     <br>错误码的具体信息请参考[TransientTask_ErrorCode](capi-transient-task-type-h.md#transienttask_errorcode)。
 * @since 20
 * @version 1.0
 */
int32_t OH_BackgroundTaskManager_GetTransientTaskInfo(TransientTask_TransientTaskInfo *transientTaskInfo);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
