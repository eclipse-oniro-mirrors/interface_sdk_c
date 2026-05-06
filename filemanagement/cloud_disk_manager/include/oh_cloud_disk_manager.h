/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 *
 * @since 21
 * @version 1.0
 */
/**
 * @file oh_cloud_disk_manager.h
 *
 * @brief This file defines the APIs for the cloud disk management module.
 *
 * @library libohclouddiskmanager.so
 * @kit CoreFileKit
 * @syscap SystemCapability.FileManagement.CloudDiskManager
 * @since 21
 * @version 1.0
 */

#ifndef FILEMANAGEMENT_KIT_OH_CLOUD_DISK_MANAGER_NDK_H
#define FILEMANAGEMENT_KIT_OH_CLOUD_DISK_MANAGER_NDK_H

#include <cstddef>
#include <cstdint>

#include "cloud_disk_error_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the file sync states.
 *
 * @since 21
 *
 */
typedef enum CloudDisk_SyncState {
    /**
     * @brief The file is idle, and no sync operation is performed.
     *
     * @since 21
     */
    IDLE = 0,
    /**
     * @brief The file is being synced.
     *
     * @since 21
     */
    SYNCING = 1,
    /**
     * @brief The file is synced successfully.
     *
     * @since 21
     */
    SYNC_SUCCEEDED = 2,
    /**
     * @brief The file fails to be synced.
     *
     * @since 21
     */
    SYNC_FAILED = 3,
    /**
     * @brief The file sync is canceled.
     *
     * @since 21
     */
    SYNC_CANCELED = 4,
    /**
     * @brief The file sync conflicts.
     *
     * @since 21
     */
    SYNC_CONFLICTED = 5,
} CloudDisk_SyncState;

/**
 * @brief Enumerates the file change types.
 *
 * @since 21
 */
typedef enum CloudDisk_OperationType {
    /**
     * @brief Create a file or directory.
     *
     * @since 21
     */
    CREATE = 0,
    /**
     * @brief Delete a file or directory.
     *
     * @since 21
     */
    DELETE = 1,
    /**
     * @brief Move this file or directory.
     *
     * @since 21
     */
    MOVE_FROM = 2,
    /**
     * @brief Move to this file or directory.
     *
     * @since 21
     */
    MOVE_TO = 3,
    /**
     * @brief Close the file after the write operation.
     *
     * @since 21
     */
    CLOSE_WRITE = 4,
    /**
     * @brief Invalid sync root path.
     *
     * @since 21
     */
    SYNC_FOLDER_INVALID = 5,
} CloudDisk_OperationType;

/**
 * @brief Enumerates the file sync failure causes.
 *
 * @since 21
 */
typedef enum CloudDisk_ErrorReason {
    /**
     * @brief The input parameter is invalid.
     *
     * @since 21
     */
    INVALID_ARGUMENT = 0,
    /**
     * @brief The file or directory does not exist.
     *
     * @since 21
     */
    NO_SUCH_FILE = 1,
    /**
     * @brief The remaining space on the device is insufficient.
     *
     * @since 21
     */
    NO_SPACE_LEFT = 2,
    /**
     * @brief The file is not in the sync root path.
     *
     * @since 21
     */
    OUT_OF_RANGE = 3,
    /**
     * @brief The sync state is not set.
     *
     * @since 21
     */
    NO_SYNC_STATE = 4,
} CloudDisk_ErrorReason;

/**
 * @brief A struct that encapsulates the file path information.
 *
 * @since 21
 */
typedef struct CloudDisk_PathInfo {
    /**
     * @brief Pointer to the file path, which ends with '\0'.
     *
     * @since 21
     */
    char *value;
    /**
     * @brief Length of the file path, excluding the '\0' character at the end.
     *
     * @since 21
     */
    size_t length;
} CloudDisk_PathInfo;

/**
 * @brief a struct that encapsulates the file ID.
 * @since 21
 */
typedef CloudDisk_PathInfo CloudDisk_FileIdInfo;

/**
 * @brief a struct that encapsulates the sync root path.
 * @since 21
 */
typedef CloudDisk_PathInfo CloudDisk_SyncFolderPath;

/**
 * @brief A struct that encapsulates the file sync state.
 *
 * @since 21
 */
typedef struct CloudDisk_FileSyncState {
    /**
     * @brief File path information.
     *
     * @since 21
     */
    CloudDisk_PathInfo filePathInfo;
    /**
     * @brief File sync state.
     *
     * @since 21
     */
    CloudDisk_SyncState syncState;
} CloudDisk_FileSyncState;

/**
 * @brief A struct that encapsulates the event data generated when a single file under the sync root path is changed.
 * It includes the file's unique ID, the parent directory's unique ID, relative path, change type, file size, and
 * timestamp.
 *
 * @since 21
 */
typedef struct CloudDisk_ChangeData {
    /**
     * @brief Update sequence number of the change event.
     * It is incremented by 1 monotonically each time a file is changed,
     * and is used for incremental change query. Value range: [0, 2^64 – 1]
     *
     * @since 21
     */
    uint64_t updateSequenceNumber{0};
    /**
     * @brief Globally unique file ID. It remains unchanged within the lifecycle of the file.
     *
     * @since 21
     */
    CloudDisk_FileIdInfo fileId;
    /**
     * @brief Unique ID of the parent directory to which the file or directory belongs.
     *
     * @since 21
     */
    CloudDisk_FileIdInfo parentFileId;
    /**
     * @brief Relative path of the file under the sync root path.
     *
     * @since 21
     */
    CloudDisk_PathInfo relativePathInfo;
    /**
     * @brief Change operation type of the file (for example, create, delete, and move).
     *
     * @since 21
     */
    CloudDisk_OperationType operationType;
    /**
     * @brief File size, in bytes.
     *
     * @since 21
     */
    uint64_t size{0};
    /**
     * @brief File modification time, in milliseconds.
     *
     * @since 21
     */
    uint64_t mtime{0};
    /**
     * @brief Time when a change event occurs, in milliseconds.
     *
     * @since 21
     */
    uint64_t timeStamp{0};
} CloudDisk_ChangeData;

/**
 * @brief A struct that encapsulates the file change result under the sync root path. It includes the next change
 * sequence number, end flag, and an array of change data items.
 *
 * @since 21
 */
typedef struct CloudDisk_ChangesResult {
    /**
     * @brief Valid start change sequence number that can be queried next time.
     *
     * @since 21
     */
    uint64_t nextUsn{0};
    /**
     * @brief Whether the change is the last entry in the sync root path's change history.
     * The value true means it is the last one; the value false means it is not.
     *
     * @since 21
     */
    bool isEof{false};
    /**
     * @brief Number of elements in the change history array.
     *
     * @since 21
     */
    size_t bufferLength{0};
    /**
     * @brief Change history array.
     *
     * @since 21
     */
    CloudDisk_ChangeData changeDatas[];
} CloudDisk_ChangesResult;

/**
 * @brief A struct that encapsulates the list of files that failed to synchronize. It includes the file path
 * information and the specific failure cause.
 *
 * @since 21
 */
typedef struct CloudDisk_FailedList {
    /**
     * @brief Absolute path information of the file that failed to synchronize.
     *
     * @since 21
     */
    CloudDisk_PathInfo pathInfo;
    /**
     * @brief Reason why the file fails to be synchronized.
     *
     * @since 21
     */
    CloudDisk_ErrorReason errorReason;
} CloudDisk_FailedList;

/**
 * @brief A struct that encapsulates the file sync result. It includes the absolute path of the file, sync result, and
 * sync state or failure cause.
 *
 * @since 21
 */
typedef struct CloudDisk_ResultList {
    /**
     * @brief Absolute path information of the file.
     *
     * @since 21
     */
    CloudDisk_PathInfo pathInfo;
    /**
     * @brief Whether the operation is successful. The value true indicates the operation is successful;
     * the value false (default) indicates the opposite.
     *
     * @since 21
     */
    bool isSuccess{false};
    /**
     * @brief File sync state. It takes effect only when **isSuccess** is set to true.
     *
     * @since 21
     */
    CloudDisk_SyncState syncState;
    /**
     * @brief Reason why the file sync state fails to be obtained.
     * It takes effect only when **isSuccess** is set to **false**.
     *
     * @since 21
     */
    CloudDisk_ErrorReason errorReason;
} CloudDisk_ResultList;

/**
 * @brief Enumerates the sync root path states.
 *
 * @since 21
 */
typedef enum CloudDisk_SyncFolderState {
    /**
     * @brief The sync root path is inactive.
     *
     * @since 21
     */
    INACTIVE = 0,
    /**
     * @brief The sync root path is active.
     *
     * @since 21
     */
    ACTIVE = 1,
} CloudDisk_SyncFolderState;

/**
 * @brief A struct that encapsulates the display name of the sync root path.
 *
 * @since 21
 */
typedef struct CloudDisk_DisplayNameInfo {
    /**
     * @brief Static resource ID corresponding to the display name of the application's sync root path.
     *
     * @since 21
     */
    uint32_t displayNameResId;
    /**
     * @brief Pointer to the custom alias, which cannot contain the following characters: \/*?<>|:".
     * Additionally, the full name cannot be composed solely of spaces, a single dot (.), or two consecutive dots (..).
	 *
     * @since 21
     */
    char *customAlias;
    /**
     * @brief Length of the custom alias. Value range: [0, 255].
     *
     * @since 21
     */
    size_t customAliasLength;
} CloudDisk_DisplayNameInfo;

/**
 * @brief A struct that encapsulates the sync root property information.
 *
 * @since 21
 */
typedef struct CloudDisk_SyncFolder {
    /**
     * @brief Sync root path.
     *
     * @since 21
     */
    CloudDisk_SyncFolderPath path;
    /**
     * @brief State of the sync root path.
     *
     * @since 21
     */
    CloudDisk_SyncFolderState state;
    /**
     * @brief Alias of the sync root path.
     *
     * @since 21
     */
    CloudDisk_DisplayNameInfo displayNameInfo;
} CloudDisk_SyncFolder;

/**
 * @brief Registers a callback to obtain file changes in the sync root path.
 *
 * @param syncFolderPath Sync root path. For details, see {@link CloudDisk_PathInfo}.
 * @param callback Registered callback.
 * @return Returns {@link CLOUD_DISK_OK} if the API is called successfully; returns {@link CloudDisk_ErrorCode}
 *     otherwise.
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_RegisterSyncFolderChanges(const CloudDisk_SyncFolderPath syncFolderPath,
    void (*callback)(const CloudDisk_SyncFolderPath syncFolderPath,
                     const CloudDisk_ChangeData changeDatas[],
                     size_t bufferLength));

/**
 * @brief Unregisters the callback for file changes in the sync root path.
 *
 * @param syncFolderPath Sync root path. For details, see {@link CloudDisk_PathInfo}.
 * @return Returns {@link CLOUD_DISK_OK} if the API is called successfully; returns {@link CloudDisk_ErrorCode}
 *     otherwise.
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_UnregisterSyncFolderChanges(const CloudDisk_SyncFolderPath syncFolderPath);

/**
 * @brief Obtains the change history in the sync root path.
 *
 * @param syncFolderPath Sync root path. For details, see {@link CloudDisk_PathInfo}.
 * @param startUsn Start change sequence number. The value range is [0, 2^64 – 1].
 * @param count Number of file changes. The value range is [1, 100].
 * @param changesResult File change result. For details, see {@link CloudDisk_ChangesResult}.
 * @return Returns {@link CLOUD_DISK_OK} if the API is called successfully; returns {@link CloudDisk_ErrorCode}
 *     otherwise.
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_GetSyncFolderChanges(const CloudDisk_SyncFolderPath syncFolderPath,
                                                      uint64_t startUsn,
                                                      size_t count,
                                                      CloudDisk_ChangesResult **changesResult);

/**
 * @brief Sets the file sync state in the sync root path.
 *
 * @param syncFolderPath Sync root path. For details, see {@link CloudDisk_PathInfo}.
 * @param fileSyncStates The array of {@link CloudDisk_FileSyncState} specifying the file paths and their target sync
 *     states.
 * @param bufferLength Length of the sync state array to be set. The value range is [1, 100].
 * @param failedLists Double pointer to the {@link CloudDisk_FailedList} array that contains files whose sync states
 *     failed to be set.
 * @param failedCount Pointer to the length of the file list array whose sync states failed to be set.
 * @return Returns {@link CLOUD_DISK_OK} if the API is called successfully; returns {@link CloudDisk_ErrorCode}
 *     otherwise.
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_SetFileSyncStates(const CloudDisk_SyncFolderPath syncFolderPath,
                                                   const CloudDisk_FileSyncState fileSyncStates[],
                                                   size_t bufferLength,
                                                   CloudDisk_FailedList **failedLists,
                                                   size_t *failedCount);

/**
 * @brief Obtains the file sync state in the sync root path.
 *
 * @param syncFolderPath Sync root path. For details, see {@link CloudDisk_PathInfo}.
 * @param paths The array of file paths to query.
 * @param bufferLength Length of the sync state array. The value range is [1, 100].
 * @param resultLists Double pointer to the file sync result. For details, see {@link CloudDisk_ResultList}.
 * @param resultCount Pointer to the number of files that fail to be synchronized.
 * @return Returns {@link CLOUD_DISK_OK} if the API is called successfully; returns {@link CloudDisk_ErrorCode}
 *     otherwise.
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_GetFileSyncStates(const CloudDisk_SyncFolderPath syncFolderPath,
                                                   const CloudDisk_PathInfo paths[],
                                                   size_t bufferLength,
                                                   CloudDisk_ResultList **resultLists,
                                                   size_t *resultCount);

/**
 * @brief Registers a sync root.
 *
 * @param syncFolder Sync root path to be registered. For details, see {@link CloudDisk_SyncFolder}.
 * @return Returns {@link CLOUD_DISK_OK} if the API is called successfully; returns {@link CloudDisk_ErrorCode}
 *     otherwise.
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_RegisterSyncFolder(const CloudDisk_SyncFolder *syncFolder);

/**
 * @brief Unregisters the sync root.
 *
 * @param syncFolderPath Sync root path. For details, see {@link CloudDisk_PathInfo}.
 * @return Returns {@link CLOUD_DISK_OK} if the API is called successfully; returns {@link CloudDisk_ErrorCode}
 *     otherwise.
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_UnregisterSyncFolder(const CloudDisk_SyncFolderPath syncFolderPath);

/**
 * @brief Activates the sync root.
 *
 * @param syncFolderPath Sync root path. For details, see {@link CloudDisk_PathInfo}.
 * @return Returns {@link CLOUD_DISK_OK} if the API is called successfully; returns {@link CloudDisk_ErrorCode}
 *     otherwise.
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_ActiveSyncFolder(const CloudDisk_SyncFolderPath syncFolderPath);

/**
 * @brief Deactivates the sync root.
 *
 * @param syncFolderPath Sync root path. For details, see {@link CloudDisk_PathInfo}.
 * @return Returns {@link CLOUD_DISK_OK} if the API is called successfully; returns {@link CloudDisk_ErrorCode}
 *     otherwise.
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_DeactiveSyncFolder(const CloudDisk_SyncFolderPath syncFolderPath);

/**
 * @brief Obtains all sync roots.
 *
 * @param syncFolders Double pointer to the sync root path array {@link CloudDisk_SyncFolder}.
 * @param count Pointer to the number of sync roots registered by the current cloud disk.
 * @return Returns {@link CLOUD_DISK_OK} if the API is called successfully; returns {@link CloudDisk_ErrorCode}
 *     otherwise.
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_GetSyncFolders(CloudDisk_SyncFolder **syncFolders, size_t *count);

/**
 * @brief Updates the sync root alias.
 *
 * @param syncFolderPath Sync root path. For details, see {@link CloudDisk_PathInfo}.
 * @param customAlias Indicates the user-defined alias.
 * @param customAliasLength Length of the custom alias. Value range: [0, 255].
 * @return Returns {@link CLOUD_DISK_OK} if the API is called successfully; returns {@link CloudDisk_ErrorCode}
 *     otherwise.
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_UpdateCustomAlias(
    const CloudDisk_SyncFolderPath syncFolderPath, const char *customAlias, size_t customAliasLength);
#ifdef __cplusplus
};
#endif
/** @} */
#endif // FILEMANAGEMENT_KIT_OH_CLOUD_DISK_MANAGER_NDK_H
