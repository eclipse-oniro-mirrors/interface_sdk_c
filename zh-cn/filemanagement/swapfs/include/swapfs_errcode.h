/*
 * Copyright (C) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup Swapfs
 * @{
 *
 * @brief Provide the definition of the error codes for swapfs module.
 *
 * @since 26.0.0
 */

/**
 * @file swapfs_errcode.h
 *
 * @brief Declare the error codes of swapfs module.
 *
 * @library libohswapfs.so
 * @kit CoreFileKit
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @since 26.0.0
 */

#ifndef FILE_MANAGEMENT_SWAPFS_ERRCODE_H
#define FILE_MANAGEMENT_SWAPFS_ERRCODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief swapfs模块错误码
 *
 * @systemapi
 * @since 26.0.0
 */
typedef enum OH_Swapfs_ErrCode {
    /**
     * @brief 操作成功。
     *
     * @since 26.0.0
     */
    SWAPFS_E_OK = 0,
    /**
     * @brief 无效参数，包括空指针、零长度或非法配置值。
     *
     * @since 26.0.0
     */
    SWAPFS_E_INVAL = 36200001,
    /**
     * @brief DIO缓冲区地址或长度未按SWAPFS_DIO_ALIGNMENT对齐。
     *
     * @since 26.0.0
     */
    SWAPFS_E_DIO_ALIGN = 36200002,
    /**
     * @brief SwapIn缓冲区大小小于所需大小（DIO模式为occupiedSize，缓冲模式为dataSize）。
     *
     * @since 26.0.0
     */
    SWAPFS_E_BUFFER_TOO_SMALL = 36200003,
    /**
     * @brief 指定的keyId在当前管理器中不存在。
     *
     * @since 26.0.0
     */
    SWAPFS_E_KEY_NOT_FOUND = 36200004,
    /**
     * @brief key处于REMOVING状态，无法对其进行操作。
     *
     * @since 26.0.0
     */
    SWAPFS_E_KEY_STATE_INVALID = 36200005,
    /**
     * @brief 检测到并发冲突。RemoveAllData或DestroyManager检测到有活动操作正在进行。
     *
     * @since 26.0.0
     */
    SWAPFS_E_BUSY = 36200006,
    /**
     * @brief 设备存储空间不足。
     *
     * @since 26.0.0
     */
    SWAPFS_E_NOSPC = 36200007,
    /**
     * @brief 交换空间配额超出。总占用空间已达到配置的限制。
     *
     * @since 26.0.0
     */
    SWAPFS_E_QUOTA_EXCEEDED = 36200008,
    /**
     * @brief IO读写失败，包括读取不完整、写入不完整、fsync失败或rename失败。
     *
     * @since 26.0.0
     */
    SWAPFS_E_IO_ERROR = 36200009,
    /**
     * @brief 由于设备空间不足或控制策略，SwapOut功能已被禁用。
     *
     * @since 26.0.0
     */
    SWAPFS_E_FEATURE_DISABLED = 36200010,
    /**
     * @brief 权限被拒绝。
     *
     * @since 26.0.0
     */
    SWAPFS_E_ACCES = 36200011,
    /**
     * @brief 无法创建交换根路径或该路径不可用。
     *
     * @since 26.0.0
     */
    SWAPFS_E_PATH_UNAVAILABLE = 36200012,
    /**
     * @brief 管理器正在关闭。新的swap-out、swap-in、remove或remove-all操作将被拒绝。
     *
     * @since 26.0.0
     */
    SWAPFS_E_SHUTTING_DOWN = 36200013,
    /**
     * @brief 内存分配失败。
     *
     * @since 26.0.0
     */
    SWAPFS_E_NOMEM = 36200014
} OH_Swapfs_ErrCode;

#ifdef __cplusplus
}
#endif
/** @} */
#endif // FILE_MANAGEMENT_SWAPFS_ERRCODE_H
