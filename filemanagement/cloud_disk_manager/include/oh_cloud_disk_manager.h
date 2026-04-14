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
     * @brief The cloud disk is idle and not performing any synchronization.
     *
     * @since 21
     */
    IDLE = 0,
    /**
     * @brief The cloud disk is currently synchronizing.
     *
     * @since 21
     */
    SYNCING = 1,
    /**
     * @brief The cloud disk synchronization completed successfully.
     *
     * @since 21
     */
    SYNC_SUCCEEDED = 2,
    /**
     * @brief The cloud disk synchronization failed.
     *
     * @since 21
     */
    SYNC_FAILED = 3,
    /**
     * @brief The cloud disk synchronization was canceled.
     *
     * @since 21
     */
    SYNC_CANCELED = 4,
    /**
     * @brief The cloud disk synchronization encountered a conflict.
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
     * @brief Create a file or folder.
     *
     * @since 21
     */
    CREATE = 0,
    /**
     * @brief Delete a file or folder.
     *
     * @since 21
     */
    DELETE = 1,
    /**
     * @brief Move a file or folder from a source location.
     *
     * @since 21
     */
    MOVE_FROM = 2,
    /**
     * @brief Move a file or folder to a target location.
     *
     * @since 21
     */
    MOVE_TO = 3,
    /**
     * @brief Close a file after writing to operations.
     *
     * @since 21
     */
    CLOSE_WRITE = 4,
    /**
     * @brief The sync folder path is invalid.
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
     * @brief The specified file does not exist.
     *
     * @since 21
     */
    NO_SUCH_FILE = 1,
    /**
     * @brief There is no space left on the device.
     *
     * @since 21
     */
    NO_SPACE_LEFT = 2,
    /**
     * @brief The operation is out of the valid range.
     *
     * @since 21
     */
    OUT_OF_RANGE = 3,
    /**
     * @brief The sync state is not set for the cloud disk.
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
     * @brief The file path as a null-terminated string.
     *
     * @since 21
     */
    char *value;
    /**
     * @brief Length of the file path, excluding the '0' character at the end.
     *
     * @since 21
     */
    size_t length;
} CloudDisk_PathInfo;

/**
 * @brief Defines the file ID information.
 * @since 21
 */
typedef CloudDisk_PathInfo CloudDisk_FileIdInfo;

/**
 * @brief Defines the sync folder path information.
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
     * @brief The update sequence number for the change event.
     * Increases by 1 each time the file is changed, and is monotonically increasing.
     * Used for incremental change queries.
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
     * @brief The size of the file in bytes.
     *
     * @since 21
     */
    uint64_t size{0};
    /**
     * @brief The last modified time of the file, in milliseconds.
     *
     * @since 21
     */
    uint64_t mtime{0};
    /**
     * @brief The timestamp of the change event, in milliseconds.
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
     * @brief The next update sequence number for incremental queries.
     *
     * @since 21
     */
    uint64_t nextUsn{0};
    /**
     * @brief Indicates whether the end of the change log is reached.
     * If true, all file changes have been returned.
     *
     * @since 21
     */
    bool isEof{false};
    /**
     * @brief The number of change data items in the array.
     *
     * @since 21
     */
    size_t bufferLength{0};
    /**
     * @brief The array of file change data items.
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
     * @brief Indicates whether the synchronization operation was successful.
     * If true, syncState is valid; if false, errorReason is valid.
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
     * @brief Indicates that the state of sync folder is inactive.
     *
     * @since 21
     */
    INACTIVE = 0,
    /**
     * @brief Indicates that the state of sync folder is active.
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
     * @brief Indicates the user-defined alias.
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
