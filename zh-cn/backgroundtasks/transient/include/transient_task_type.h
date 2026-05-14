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

#ifndef OHOS_BACKGROUOND_TASK_MANAGER_TRANSIENT_TASK_TYPE_H
#define OHOS_BACKGROUOND_TASK_MANAGER_TRANSIENT_TASK_TYPE_H

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

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 同一时刻最大短时任务数量。
 * 
 * @since 20
 */
#define TRANSIENT_TASK_MAX_NUM 3

/**
 * @brief 定义短时任务错误码。
 * 
 * @since 13
 */
typedef enum TransientTask_ErrorCode {
    /**
     * 成功。
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_OK = 0,
    /**
     * 参数检查失败。可能原因：1.必选参数没有传入。2.参数类型错误。
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_INVALID_PARAM = 401,
    /**
     * Parcel读写操作失败
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_PARCEL_FAILED = 9800002,
    /**
     * IPC通信失败。
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_TRANSACTION_FAILED = 9800003,
    /**
     * 系统服务失败。
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_SYS_NOT_READY = 9800004,
    /**
     * 短时任务客户端信息校验失败。
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_CLIENT_INFO_VERIFICATION_FAILED = 9900001,
    /**
     * 短时任务服务端校验失败。
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_SERVICE_VERIFICATION_FAILED = 9900002,
    /**
     * 短时任务Parcel读写操作失败。可能原因：1.参数非法。2.申请内存失败。
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_PARCELABLE_FAILED = 9900003,
    /**
     * 系统服务失败。
     *
     * @since 13
     */
    ERR_TRANSIENT_TASK_SERVICE_NOT_READY = 9900004,
} TransientTask_ErrorCode;

/**
 * @brief 定义短时任务返回信息结构体。用于返回当前短时任务的任务ID和剩余时间。
 * 
 * @since 13
 * @version 1.0
 */
typedef struct TransientTask_DelaySuspendInfo {
    /**
     * 短时任务请求ID。
     *
     * @since 13
     */
    int32_t requestId;
    /**
     * 剩余时间。单位：ms。
     *
     * @since 13
     */
    int32_t actualDelayTime;
} TransientTask_DelaySuspendInfo;

/**
 * @brief 定义所有短时任务信息结构体。用于返回当日剩余总配额和已申请的所有短时任务信息。
 * 
 * @since 20
 * @version 1.0
 */
typedef struct TransientTask_TransientTaskInfo {
    /**
     * 当日剩余总配额。单位：ms。
     *
     * @since 20
     */
    int32_t remainingQuota;
    /** 已申请的所有短时任务信息。包括短时任务请求ID、剩余时间。单位：ms。
     *
     * @since 20
     */
    TransientTask_DelaySuspendInfo transientTasks[TRANSIENT_TASK_MAX_NUM];
} TransientTask_TransientTaskInfo;

/**
 * @brief 定义短时任务超时回调类型。
 * 
 * @since 13
 */
typedef void (*TransientTask_Callback)(void);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
