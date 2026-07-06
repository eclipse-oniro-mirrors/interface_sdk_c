/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup CloudDisk
 * @{
 *
 * @brief Provides APIs and error code for managing cloud disks.
 * @since 21
 * @version 1.0
 */
/**
 * @file oh_cloud_disk_error_code.h
 *
 * @brief 提供云盘管理模块的错误码定义。
 *
 * @library libohclouddiskmanager.so
 * @kit CoreFileKit
 * @syscap SystemCapability.FileManagement.CloudDiskManager
 * @since 21
 * @version 1.0
 */

#ifndef FILEMANAGEMENT_KIT_OH_CLOUD_DISK_MANAGER_ERROR_CODE_H
#define FILEMANAGEMENT_KIT_OH_CLOUD_DISK_MANAGER_ERROR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义云盘管理模块的错误码。
 *
 * @since 21
 */
typedef enum CloudDisk_ErrorCode {
    /**
     * @brief 接口调用成功。
     *
     * @since 21
     */
    CLOUD_DISK_OK = 0,
    /**
     * @brief 接口权限校验失败。
     *
     * @since 21
     */
    CLOUD_DISK_PERMISSION_DENIED = 201,
    /**
     * @brief 当前设备不支持此功能。
     *
     * @since 21
     */
    CLOUD_DISK_NOT_SUPPORTED = 801,
    /**
     * @brief 输入参数无效。
     *
     * @since 21
     */
    CLOUD_DISK_INVALID_ARG = 34400001,
    /**
     * @brief 同步根路径未授权。
     *
     * @since 21
     */
    CLOUD_DISK_SYNC_FOLDER_PATH_UNAUTHORIZED = 34400002,
    /**
     * @brief IPC连接失败。
     *
     * @since 21
     */
    CLOUD_DISK_IPC_FAILED = 34400003,
    /**
     * @brief 同步根路径数量超过允许的限制。
     *
     * @since 21
     */
    CLOUD_DISK_SYNC_FOLDER_LIMIT_EXCEEDED = 34400004,
    /**
     * @brief 同步根路径和该应用现有的同步根路径发生冲突。
     *
     * @since 21
     */
    CLOUD_DISK_CONFLICT_THIS_APP = 34400005,
    /**
     * @brief 同步根路径和其他应用现有的同步根路径发生冲突。
     *
     * @since 21
     */
    CLOUD_DISK_CONFLICT_OTHER_APP = 34400006,
    /**
     * @brief 同步根路径注册失败。
     *
     * @since 21
     */
    CLOUD_DISK_REGISTER_SYNC_FOLDER_FAILED = 34400007,
    /**
     * @brief 同步根路径未注册。
     *
     * @since 21
     */
    CLOUD_DISK_SYNC_FOLDER_NOT_REGISTERED = 34400008,
    /**
     * @brief 同步根路径取消注册失败。
     *
     * @since 21
     */
    CLOUD_DISK_UNREGISTER_SYNC_FOLDER_FAILED = 34400009,
    /**
     * @brief 同步根路径不存在。
     *
     * @since 21
     */
    CLOUD_DISK_SYNC_FOLDER_PATH_NOT_EXIST = 34400010,
    /**
     * @brief 变更的监听未注册。
     *
     * @since 21
     */
    CLOUD_DISK_LISTENER_NOT_REGISTERED = 34400011,
    /**
     * @brief 变更的监听已注册。
     *
     * @since 21
     */
    CLOUD_DISK_LISTENER_ALREADY_REGISTERED = 34400012,
    /**
     * @brief 无效的变更序列，建议进行全部查询。
     *
     * @since 21
     */
    CLOUD_DISK_INVALID_CHANGE_SEQUENCE = 34400013,
    /**
     * @brief 临时失败，建议重试（如：底层io负载过大、内存不足等）。
     *
     * @since 21
     */
    CLOUD_DISK_TRY_AGAIN = 34400014,
    /**
     * @brief 当前设备不允许执行此功能。
     *
     * @since 21
     */
    CLOUD_DISK_NOT_ALLOWED = 34400015,
} CloudDisk_ErrorCode;

#ifdef __cplusplus
}
#endif
/** @} */
#endif // FILEMANAGEMENT_KIT_OH_CLOUD_DISK_MANAGER_ERROR_CODE_H
