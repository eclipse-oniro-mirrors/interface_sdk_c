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
 * @brief Error codes of swapfs module.
 *
 * @systemapi
 * @since 26.0.0
 */
typedef enum OH_Swapfs_ErrCode {
    /**
     * @brief Operation successful.
     *
     * @since 26.0.0
     */
    SWAPFS_E_OK = 0,
    /**
     * @brief Invalid parameter. Possible causes a null pointer, zero length, or an invalid configuration value.
     *
     * @since 26.0.0
     */
    SWAPFS_E_INVAL = 36200001,
    /**
     * @brief DIO buffer address or length is not aligned to SWAPFS_DIO_ALIGNMENT.
     *
     * @since 26.0.0
     */
    SWAPFS_E_DIO_ALIGN = 36200002,
    /**
     * @brief SwapIn buffer size is smaller than the required size (occupiedSize for DIO mode and
     * dataSize for buffered mode).
     *
     * @since 26.0.0
     */
    SWAPFS_E_BUFFER_TOO_SMALL = 36200003,
    /**
     * @brief The specified keyId does not exist in the current manager.
     *
     * @since 26.0.0
     */
    SWAPFS_E_KEY_NOT_FOUND = 36200004,
    /**
     * @brief The key is in the REMOVING state and cannot be operated on.
     *
     * @since 26.0.0
     */
    SWAPFS_E_KEY_STATE_INVALID = 36200005,
    /**
     * @brief Concurrent conflict detected. RemoveAllData or DestroyManager detected active operations in progress.
     *
     * @since 26.0.0
     */
    SWAPFS_E_BUSY = 36200006,
    /**
     * @brief Insufficient device storage space.
     *
     * @since 26.0.0
     */
    SWAPFS_E_NOSPC = 36200007,
    /**
     * @brief Swap space quota exceeded. The total occupied space has reached the configured limit.
     *
     * @since 26.0.0
     */
    SWAPFS_E_QUOTA_EXCEEDED = 36200008,
    /**
     * @brief I/O read or write failure, including a short read, short write, fsync failure, or rename failure.
     *
     * @since 26.0.0
     */
    SWAPFS_E_IO_ERROR = 36200009,
    /**
     * @brief The SwapOut feature is disabled due to insufficient device storage space or control policy.
     *
     * @since 26.0.0
     */
    SWAPFS_E_FEATURE_DISABLED = 36200010,
    /**
     * @brief Permission denied.
     *
     * @since 26.0.0
     */
    SWAPFS_E_ACCES = 36200011,
    /**
     * @brief Swap root path cannot be created or is unavailable.
     *
     * @since 26.0.0
     */
    SWAPFS_E_PATH_UNAVAILABLE = 36200012,
    /**
     * @brief The manager is shutting down. New swap-out, swap-in, remove, or remove-all operations will be rejected.
     *
     * @since 26.0.0
     */
    SWAPFS_E_SHUTTING_DOWN = 36200013,
    /**
     * @brief Memory allocation failed.
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
