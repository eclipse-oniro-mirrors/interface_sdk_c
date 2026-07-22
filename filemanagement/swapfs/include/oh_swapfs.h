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
 * @brief Provides APIs for user-space storage swapping.
 *
 * @since 26.0.0
 */

/**
 * @file oh_swapfs.h
 *
 * @brief Defines the native APIs for swapfs.
 *
 * @library libohswapfs.so
 * @kit CoreFileKit
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @since 26.0.0
 */

#ifndef FILE_MANAGEMENT_SWAPFS_OH_SWAPFS_H
#define FILE_MANAGEMENT_SWAPFS_OH_SWAPFS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "swapfs_errcode.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Minimum alignment requirement for Direct IO buffers.
 * @systemapi
 * @since 26.0.0
 */
#define SWAPFS_DIO_ALIGNMENT 4096U

/**
 * @brief Defines the status of a swap key.
 * @systemapi
 * @since 26.0.0
 */
typedef enum OH_SwapfsKeyStatus {
    /**
     * @brief The key is active and available for swap-in, query, or removal.
     * @since 26.0.0
     */
    OH_SWAPFS_KEY_STATUS_ACTIVE = 0,
    /**
     * @brief The key is logically deleted. New swap-in or query operations will be rejected.
     * @since 26.0.0
     */
    OH_SWAPFS_KEY_STATUS_REMOVING = 1
} OH_SwapfsKeyStatus;

/**
 * @brief Defines the reason why the swap-out feature is disabled.
 * @systemapi
 * @since 26.0.0
 */
typedef enum OH_SwapfsDisableReason {
    /**
     * @brief The feature is enabled (no disable reason).
     * @since 26.0.0
     */
    OH_SWAPFS_DISABLE_REASON_NONE = 0,
    /**
     * @brief Device storage space is insufficient.
     * @since 26.0.0
     */
    OH_SWAPFS_DISABLE_REASON_NOSPC = 1
} OH_SwapfsDisableReason;

/**
 * @brief The struct is used to perform operations related to swapfs manager.
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsManager OH_SwapfsManager;

/**
 * @brief Configuration for creating a swapfs manager.
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsConfig {
    /**
     * @brief Base path for swap data storage. Swapfs uses the fixed "swapfs" child directory.
     * When NULL or empty, a default temporary base path under the application sandbox is used.
     * @since 26.0.0
     */
    const char *swapRootPath;
    /**
     * @brief Maximum swap space in bytes. When 0, the default limit is 1GB (1073741824).
     * @since 26.0.0
     */
    uint64_t spaceLimitBytes;
    /**
     * @brief Whether to enforce Direct IO for swap-out operations. When false, buffered IO is used;
     * when true, Direct IO is required and misaligned buffers will cause an error.
     * @since 26.0.0
     */
    bool useDirectIo;
} OH_SwapfsConfig;

/**
 * @brief Request parameters for swap-out operation.
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsSwapOutRequest {
    /**
     * @brief Pointer to the data buffer to be swapped out. Must not be NULL.
     * @since 26.0.0
     */
    const void *buffer;
    /**
     * @brief Size of the data buffer in bytes. Must be greater than 0.
     * @since 26.0.0
     */
    uint64_t bufferSize;
} OH_SwapfsSwapOutRequest;

/**
 * @brief Request parameters for swap-in operation.
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsSwapInRequest {
    /**
     * @brief The keyId returned by a previous swap-out operation.
     * @since 26.0.0
     */
    uint64_t keyId;
    /**
     * @brief Pointer to the buffer for receiving swapped-in data. Must not be NULL.
     * In DIO mode, the buffer address and size must be aligned to SWAPFS_DIO_ALIGNMENT,
     * and bufferSize must be greater than or equal to occupiedSize. In buffered mode,
     * bufferSize must be greater than or equal to dataSize.
     * @since 26.0.0
     */
    void *buffer;
    /**
     * @brief Size of the receiving buffer in bytes.
     * @since 26.0.0
     */
    uint64_t bufferSize;
} OH_SwapfsSwapInRequest;

/**
 * @brief Information about a single swap key.
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsDataInfo {
    /**
     * @brief The keyId identifying this swap data entry.
     * @since 26.0.0
     */
    uint64_t keyId;
    /**
     * @brief Original data size in bytes as provided by the caller during swap-out.
     * @since 26.0.0
     */
    uint64_t dataSize;
    /**
     * @brief File size in bytes occupied on disk. In DIO mode this is dataSize aligned up to
     * SWAPFS_DIO_ALIGNMENT; in buffered mode it equals dataSize.
     * @since 26.0.0
     */
    uint64_t occupiedSize;
    /**
     * @brief Timestamp when the key was created (Unix epoch in milliseconds).
     * @since 26.0.0
     */
    int64_t createTime;
    /**
     * @brief Current status of the key.
     * @since 26.0.0
     */
    OH_SwapfsKeyStatus status;
    /**
     * @brief Whether the key can be swapped in. False if the key is in REMOVING state.
     * @since 26.0.0
     */
    bool canSwapIn;
} OH_SwapfsDataInfo;

/**
 * @brief Statistics of the current swapfs manager.
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsStats {
    /**
     * @brief Total number of active keys in the manager.
     * @since 26.0.0
     */
    uint64_t totalKeys;
    /**
     * @brief Total original data size of all keys in bytes.
     * @since 26.0.0
     */
    uint64_t totalDataSize;
    /**
     * @brief Total aligned file size of all keys in bytes.
     * @since 26.0.0
     */
    uint64_t totalOccupiedSize;
    /**
     * @brief Configured swap space limit in bytes.
     * @since 26.0.0
     */
    uint64_t spaceLimitBytes;
    /**
     * @brief Whether swap-out is currently enabled. False when device space is below 5GB or
     * control policy disables the feature.
     * @since 26.0.0
     */
    bool featureEnabled;
    /**
     * @brief Reason for feature disablement.
     * @since 26.0.0
     */
    OH_SwapfsDisableReason disableReason;
    /**
     * @brief Accumulated bytes written by successful swap-out operations.
     * @since 26.0.0
     */
    uint64_t accumulatedWriteBytes;
    /**
     * @brief Timestamp of the last device space check (Unix epoch in milliseconds).
     * @since 26.0.0
     */
    int64_t lastSpaceCheckTime;
    /**
     * @brief Cached available device storage space in bytes at the last check time.
     * @since 26.0.0
     */
    uint64_t availableDeviceSpace;
} OH_SwapfsStats;

/**
 * @brief Creates a swapfs manager.
 *
 * @param config [in] Pointer to the configuration, or NULL to use the default configuration
 *     (default temporary directory, 1GB limit, useDirectIo=false).
 * @param manager [out] Double pointer to receive the created OH_SwapfsManager handle.
 *     Must not be NULL. On failure, the pointed value is set to NULL.
 * @return Returns the error code of the execution.
 *         <ul>
 *         <li>{@link SWAPFS_E_OK} if the execution is successful.</li>
 *         <li>{@link SWAPFS_E_INVAL} manager is nullptr.</li>
 *         <li>{@link SWAPFS_E_NOMEM} memory allocation failed.</li>
 *         <li>{@link SWAPFS_E_ACCES} permission denied for the swap root path.</li>
 *         <li>{@link SWAPFS_E_PATH_UNAVAILABLE} swap root path cannot be created.</li>
 *         <li>202 if a non-system application calls this system API.</li>
 *         </ul>
 * @release swapfs/OH_Swapfs_DestroyManager {manager}
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_CreateManager(const OH_SwapfsConfig *config, OH_SwapfsManager **manager);

/**
 * @brief Destroys a swapfs manager and releases all resources.
 *
 * This function enters the shutting-down state and rejects new swap-out, swap-in, remove,
 * and remove-all operations. It waits up to 5 seconds for active operations to complete.
 * If all operations complete within the timeout, all swap data owned by the manager is
 * automatically removed and the manager is destroyed. If the wait times out, this function
 * cancels the shutting-down state and returns SWAPFS_E_BUSY; the caller can retry later.
 *
 * @param manager [in] Pointer to the OH_SwapfsManager object to destroy. Must not be NULL.
 * @return Returns the error code of the execution.
 *         <ul>
 *         <li>{@link SWAPFS_E_OK} if the execution is successful.</li>
 *         <li>{@link SWAPFS_E_INVAL} manager is nullptr.</li>
 *         <li>{@link SWAPFS_E_BUSY} there are active operations in progress.</li>
 *         <li>202 if a non-system application calls this system API.</li>
 *         </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_DestroyManager(OH_SwapfsManager *manager);

/**
 * @brief Swaps out data from memory to disk.
 *
 * When config.useDirectIo is false, buffered IO is used. When true, Direct IO is required
 * and misaligned buffers cause an error. In DIO mode, the swap file size is padded to
 * SWAPFS_DIO_ALIGNMENT (occupiedSize is greater than or equal to dataSize).
 *
 * @param manager [in] Pointer to the OH_SwapfsManager object. Must not be NULL.
 * @param request [in] Pointer to the swap-out request containing the data buffer and its size.
 *     Must not be NULL.
 * @param keyId [out] Pointer to receive the generated keyId for this swap data. Must not be NULL.
 *     On failure, the pointed value is unchanged.
 * @return Returns the error code of the execution.
 *         <ul>
 *         <li>{@link SWAPFS_E_OK} if the execution is successful.</li>
 *         <li>{@link SWAPFS_E_INVAL} manager is nullptr, request is nullptr, keyId is nullptr,
 *             buffer is nullptr, or bufferSize is 0.</li>
 *         <li>{@link SWAPFS_E_DIO_ALIGN} useDirectIo is true and buffer is not aligned.</li>
 *         <li>{@link SWAPFS_E_NOSPC} insufficient device storage space.</li>
 *         <li>{@link SWAPFS_E_QUOTA_EXCEEDED} swap space quota exceeded.</li>
 *         <li>{@link SWAPFS_E_FEATURE_DISABLED} swap-out is disabled due to low space or policy.</li>
 *         <li>{@link SWAPFS_E_IO_ERROR} IO write failure.</li>
 *         <li>{@link SWAPFS_E_NOMEM} memory allocation failed.</li>
 *         <li>{@link SWAPFS_E_ACCES} permission denied.</li>
 *         <li>{@link SWAPFS_E_BUSY} RemoveAllData is in progress or too many concurrent operations.</li>
 *         <li>{@link SWAPFS_E_SHUTTING_DOWN} manager is shutting down.</li>
 *         <li>202 if a non-system application calls this system API.</li>
 *         </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_SwapOut(OH_SwapfsManager *manager, const OH_SwapfsSwapOutRequest *request,
    uint64_t *keyId);

/**
 * @brief Swaps in data from disk back to memory.
 *
 * In DIO mode, the buffer address and size must be aligned to SWAPFS_DIO_ALIGNMENT, and
 * bufferSize must be greater than or equal to occupiedSize. In buffered mode, bufferSize
 * must be greater than or equal to dataSize. On success, readSize receives the original
 * dataSize (not occupiedSize).
 *
 * @param manager [in] Pointer to the OH_SwapfsManager object. Must not be NULL.
 * @param request [in] Pointer to the swap-in request containing keyId, buffer, and bufferSize.
 *     Must not be NULL.
 * @param readSize [out] Pointer to receive the original data size in bytes, or NULL if the
 *     caller does not need it. On success, receives the original dataSize. On failure, the pointed
 *     value is unchanged.
 * @return Returns the error code of the execution.
 *         <ul>
 *         <li>{@link SWAPFS_E_OK} if the execution is successful.</li>
 *         <li>{@link SWAPFS_E_INVAL} manager is nullptr, request is nullptr, keyId is 0,
 *             buffer is nullptr, or bufferSize is 0.</li>
 *         <li>{@link SWAPFS_E_DIO_ALIGN} buffer address or size is not aligned to SWAPFS_DIO_ALIGNMENT.</li>
 *         <li>{@link SWAPFS_E_BUFFER_TOO_SMALL} bufferSize is smaller than the required size.</li>
 *         <li>{@link SWAPFS_E_KEY_NOT_FOUND} keyId does not exist.</li>
 *         <li>{@link SWAPFS_E_KEY_STATE_INVALID} key is in REMOVING state.</li>
 *         <li>{@link SWAPFS_E_IO_ERROR} IO read failure.</li>
 *         <li>{@link SWAPFS_E_NOMEM} memory allocation failed.</li>
 *         <li>{@link SWAPFS_E_ACCES} permission denied.</li>
 *         <li>{@link SWAPFS_E_BUSY} too many concurrent operations.</li>
 *         <li>{@link SWAPFS_E_SHUTTING_DOWN} manager is shutting down.</li>
 *         <li>202 if a non-system application calls this system API.</li>
 *         </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_SwapIn(OH_SwapfsManager *manager, const OH_SwapfsSwapInRequest *request,
    uint64_t *readSize);

/**
 * @brief Queries information about a specific swap key.
 *
 * @param manager [in] Pointer to the OH_SwapfsManager object. Must not be NULL.
 * @param keyId [in] The keyId to query.
 * @param info [out] Pointer to the OH_SwapfsDataInfo structure to receive the key information.
 *     Must not be NULL. On failure, the content is unchanged.
 * @return Returns the error code of the execution.
 *         <ul>
 *         <li>{@link SWAPFS_E_OK} if the execution is successful.</li>
 *         <li>{@link SWAPFS_E_INVAL} manager is nullptr, keyId is 0, or info is nullptr.</li>
 *         <li>{@link SWAPFS_E_KEY_NOT_FOUND} keyId does not exist.</li>
 *         <li>{@link SWAPFS_E_KEY_STATE_INVALID} key is in REMOVING state.</li>
 *         <li>202 if a non-system application calls this system API.</li>
 *         </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_QueryData(OH_SwapfsManager *manager, uint64_t keyId, OH_SwapfsDataInfo *info);

/**
 * @brief Obtains statistics of the current swapfs manager.
 *
 * @param manager [in] Pointer to the OH_SwapfsManager object. Must not be NULL.
 * @param stats [out] Pointer to the OH_SwapfsStats structure to receive the statistics.
 *     Must not be NULL. On failure, the content is unchanged.
 * @return Returns the error code of the execution.
 *         <ul>
 *         <li>{@link SWAPFS_E_OK} if the execution is successful.</li>
 *         <li>{@link SWAPFS_E_INVAL} manager is nullptr, or stats is nullptr.</li>
 *         <li>202 if a non-system application calls this system API.</li>
 *         </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_GetStats(OH_SwapfsManager *manager, OH_SwapfsStats *stats);

/**
 * @brief Logically deletes a specific swap key.
 *
 * The key is marked as REMOVING state immediately. Existing swap-in operations can still complete.
 * New swap-in or query operations on this key will return SWAPFS_E_KEY_STATE_INVALID.
 * This function does not return SWAPFS_E_BUSY for concurrent swap-in operations.
 *
 * @param manager [in] Pointer to the OH_SwapfsManager object. Must not be NULL.
 * @param keyId [in] The keyId to remove.
 * @return Returns the error code of the execution.
 *         <ul>
 *         <li>{@link SWAPFS_E_OK} if the execution is successful.</li>
 *         <li>{@link SWAPFS_E_INVAL} manager is nullptr or keyId is 0.</li>
 *         <li>{@link SWAPFS_E_KEY_NOT_FOUND} keyId does not exist.</li>
 *         <li>{@link SWAPFS_E_KEY_STATE_INVALID} key is already in REMOVING state.</li>
 *         <li>{@link SWAPFS_E_NOMEM} memory allocation failed.</li>
 *         <li>{@link SWAPFS_E_BUSY} too many concurrent operations.</li>
 *         <li>{@link SWAPFS_E_SHUTTING_DOWN} manager is shutting down.</li>
 *         <li>202 if a non-system application calls this system API.</li>
 *         </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_RemoveData(OH_SwapfsManager *manager, uint64_t keyId);

/**
 * @brief Removes all swap keys in the manager.
 *
 * If there are active operations in progress (swap-out or swap-in), or any key is in REMOVING
 * state, this function returns SWAPFS_E_BUSY without starting any removal.
 *
 * @param manager [in] Pointer to the OH_SwapfsManager object. Must not be NULL.
 * @return Returns the error code of the execution.
 *         <ul>
 *         <li>{@link SWAPFS_E_OK} if the execution is successful.</li>
 *         <li>{@link SWAPFS_E_INVAL} manager is nullptr.</li>
 *         <li>{@link SWAPFS_E_NOMEM} memory allocation failed.</li>
 *         <li>{@link SWAPFS_E_BUSY} there are active operations in progress or pending keys in REMOVING state.</li>
 *         <li>{@link SWAPFS_E_SHUTTING_DOWN} manager is shutting down.</li>
 *         <li>202 if a non-system application calls this system API.</li>
 *         </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_RemoveAllData(OH_SwapfsManager *manager);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // FILE_MANAGEMENT_SWAPFS_OH_SWAPFS_H
