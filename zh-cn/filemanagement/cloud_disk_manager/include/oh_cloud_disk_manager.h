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
 *
 * @since 21
 * @version 1.0
 */
/**
 * @file oh_cloud_disk_manager.h
 *
 * @brief 云盘管理模块的接口定义。
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
 * @brief 文件同步状态的枚举值。
 *
 * @since 21
 *
 */
typedef enum CloudDisk_SyncState {
    /**
     * @brief 目前处于空闲状态，未执行任何同步操作。
     *
     * @since 21
     */
    IDLE = 0,
    /**
     * @brief 文件正在同步。
     *
     * @since 21
     */
    SYNCING = 1,
    /**
     * @brief 文件同步成功。
     *
     * @since 21
     */
    SYNC_SUCCEEDED = 2,
    /**
     * @brief 	文件同步失败。
     *
     * @since 21
     */
    SYNC_FAILED = 3,
    /**
     * @brief 文件同步取消。
     *
     * @since 21
     */
    SYNC_CANCELED = 4,
    /**
     * @brief 文件同步冲突。
     *
     * @since 21
     */
    SYNC_CONFLICTED = 5,
} CloudDisk_SyncState;

/**
 * @brief 文件变更类型枚举值。
 *
 * @since 21
 */
typedef enum CloudDisk_OperationType {
    /**
     * @brief 创建文件或目录。
     *
     * @since 21
     */
    CREATE = 0,
    /**
     * @brief 删除文件或目录。
     *
     * @since 21
     */
    DELETE = 1,
    /**
     * @brief 移动此文件或目录。
     *
     * @since 21
     */
    MOVE_FROM = 2,
    /**
     * @brief 移动到此文件或目录。
     *
     * @since 21
     */
    MOVE_TO = 3,
    /**
     * @brief 在写入操作后关闭文件。
     *
     * @since 21
     */
    CLOSE_WRITE = 4,
    /**
     * @brief 同步根路径无效。
     *
     * @since 21
     */
    SYNC_FOLDER_INVALID = 5,
} CloudDisk_OperationType;

/**
 * @brief 文件同步失败原因的枚举值。
 *
 * @since 21
 */
typedef enum CloudDisk_ErrorReason {
    /**
     * @brief 输入的参数无效。
     *
     * @since 21
     */
    INVALID_ARGUMENT = 0,
    /**
     * @brief 操作的文件或目录不存在。
     *
     * @since 21
     */
    NO_SUCH_FILE = 1,
    /**
     * @brief 设备上的剩余空间不足。
     *
     * @since 21
     */
    NO_SPACE_LEFT = 2,
    /**
     * @brief 超出有效范围。
     *
     * @since 21
     */
    OUT_OF_RANGE = 3,
    /**
     * @brief 同步状态未设置。
     *
     * @since 21
     */
    NO_SYNC_STATE = 4,
} CloudDisk_ErrorReason;

/**
 * @brief 文件路径信息。
 *
 * @since 21
 */
typedef struct CloudDisk_PathInfo {
    /**
     * @brief 文件的路径，以'\0'字符结尾。
     *
     * @since 21
     */
    char *value;
    /**
     * @brief 文件路径的长度，不包括结尾的'0'字符。
     *
     * @since 21
     */
    size_t length;
} CloudDisk_PathInfo;

/**
 * @brief 定义的文件ID。
 *
 * @since 21
 */
typedef CloudDisk_PathInfo CloudDisk_FileIdInfo;

/**
 * @brief 定义的同步根路径。
 *
 * @since 21
 */
typedef CloudDisk_PathInfo CloudDisk_SyncFolderPath;

/**
 * @brief 文件的同步状态。
 *
 * @since 21
 */
typedef struct CloudDisk_FileSyncState {
    /**
     * @brief 文件的路径信息。
     *
     * @since 21
     */
    CloudDisk_PathInfo filePathInfo;
    /**
     * @brief 文件的同步状态。
     *
     * @since 21
     */
    CloudDisk_SyncState syncState;
} CloudDisk_FileSyncState;

/**
 * @brief 定义了同步根路径下单个文件变更事件的数据结构。该结构包含有关文件变更的详细信息，包括唯一ID、父目录的唯一ID、相对路径、变更类型、文件大小和时间戳。
 *
 * @since 21
 */
typedef struct CloudDisk_ChangeData {
    /**
     * @brief 变更事件的更新序列号。每次文件更改时单调递增加1，用于增量变更查询。范围：[0, 2^64 - 1]。
     *
     * @since 21
     */
    uint64_t updateSequenceNumber{0};
    /**
     * @brief 全局唯一的文件ID。在文件的生命周期内保持不变。
     *
     * @since 21
     */
    CloudDisk_FileIdInfo fileId;
    /**
     * @brief 文件或目录所属父目录的唯一ID。
     *
     * @since 21
     */
    CloudDisk_FileIdInfo parentFileId;
    /**
     * @brief 同步根路径下的文件，相对于同步根路径的相对路径。
     *
     * @since 21
     */
    CloudDisk_PathInfo relativePathInfo;
    /**
     * @brief 此文件的变更操作类型（如：创建、删除、移动等）。
     *
     * @since 21
     */
    CloudDisk_OperationType operationType;
    /**
     * @brief 文件大小，单位：Byte。
     *
     * @since 21
     */
    uint64_t size{0};
    /**
     * @brief 文件修改时间，单位：ms。
     *
     * @since 21
     */
    uint64_t mtime{0};
    /**
     * @brief 变更事件发生时间，单位：ms。
     *
     * @since 21
     */
    uint64_t timeStamp{0};
} CloudDisk_ChangeData;

/**
 * @brief 查询同步根路径中文件变更的结果。该结构体包含同步根路径中文件的变更数据，包括下一个更新序列号、结尾标志以及变更数据项数组。
 *
 * @since 21
 */
typedef struct CloudDisk_ChangesResult {
    /**
     * @brief 下一次可查询的有效起始变更序列号。
     *
     * @since 21
     */
    uint64_t nextUsn{0};
    /**
     * @brief 本次变更是否为同步根路径中记录的最后的修改记录。true：表示是最后的修改记录；false：表示不是最后的修改记录。
     *
     * @since 21
     */
    bool isEof{false};
    /**
     * @brief 历史变更记录数组中的元素数量。
     *
     * @since 21
     */
    size_t bufferLength{0};
    /**
     * @brief 历史变更记录数组。
     *
     * @since 21
     */
    CloudDisk_ChangeData changeDatas[];
} CloudDisk_ChangesResult;

/**
 * @brief 同步操作中失败的文件列表信息。该结构包含文件路径信息以及失败的具体错误原因。
 *
 * @since 21
 */
typedef struct CloudDisk_FailedList {
    /**
     * @brief 失败文件的绝对路径信息。
     *
     * @since 21
     */
    CloudDisk_PathInfo pathInfo;
    /**
     * @brief 文件同步失败的原因。
     *
     * @since 21
     */
    CloudDisk_ErrorReason errorReason;
} CloudDisk_FailedList;

/**
 * @brief 表示一个文件同步操作的结果。该结构体包含文件的绝对路径、同步结果，以及同步状态或失败原因。
 *
 * @since 21
 */
typedef struct CloudDisk_ResultList {
    /**
     * @brief 文件的绝对路径信息。
     *
     * @since 21
     */
    CloudDisk_PathInfo pathInfo;
    /**
     * @brief 表示操作是否成功。true：表示操作成功；false：表示操作失败。默认值为false。
     *
     * @since 21
     */
    bool isSuccess{false};
    /**
     * @brief 文件的同步状态。当isSuccess为true时才生效。
     *
     * @since 21
     */
    CloudDisk_SyncState syncState;
    /**
     * @brief 文件同步状态获取失败的原因。当isSuccess为false时才生效。
     *
     * @since 21
     */
    CloudDisk_ErrorReason errorReason;
} CloudDisk_ResultList;

/**
 * @brief 同步根路径状态的枚举值。
 *
 * @since 21
 */
typedef enum CloudDisk_SyncFolderState {
    /**
     * @brief 表示同步根路径的状态是未激活的。
     *
     * @since 21
     */
    INACTIVE = 0,
    /**
     * @brief 表示同步根路径的状态是激活的。
     *
     * @since 21
     */
    ACTIVE = 1,
} CloudDisk_SyncFolderState;

/**
 * @brief 定义同步根路径的显示名称信息。
 *
 * @since 21
 */
typedef struct CloudDisk_DisplayNameInfo {
    /**
     * @brief 应用同步根路径显示名称对应的静态资源ID。
     *
     * @since 21
     */
    uint32_t displayNameResId;
    /**
     * @brief 自定义的别名，不能包含字符：\/*?<>|:"，以及不能以"."、".."和纯空格作为完整名称。
     *
     * @since 21
     */
    char *customAlias;
    /**
     * @brief 自定义别名的长度，范围：[0, 255]。
     *
     * @since 21
     */
    size_t customAliasLength;
} CloudDisk_DisplayNameInfo;

/**
 * @brief 同步根属性信息。
 *
 * @since 21
 */
typedef struct CloudDisk_SyncFolder {
    /**
     * @brief 同步根路径
     *
     * @since 21
     */
    CloudDisk_SyncFolderPath path;
    /**
     * @brief 同步根路径状态。
     *
     * @since 21
     */
    CloudDisk_SyncFolderState state;
    /**
     * @brief 同步根路径别名信息。
     *
     * @since 21
     */
    CloudDisk_DisplayNameInfo displayNameInfo;
} CloudDisk_SyncFolder;

/**
 * @brief 应用注册一个回调函数，用于获取同步根路径下文件的变更。
 *
 * @param syncFolderPath 表示同步根路径，参考：{@link CloudDisk_PathInfo}。
 * @param callback 注册的回调函数。
 * @return 如果接口调用成功，返回{@link CLOUD_DISK_OK}；否则返回云盘管理模块的错误码{@link CloudDisk_ErrorCode}。
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_RegisterSyncFolderChanges(const CloudDisk_SyncFolderPath syncFolderPath,
    void (*callback)(const CloudDisk_SyncFolderPath syncFolderPath,
                     const CloudDisk_ChangeData changeDatas[],
                     size_t bufferLength));

/**
 * @brief 应用取消注册同步根路径下文件变更的回调。
 *
 * @param syncFolderPath 表示同步根路径，参考：{@link CloudDisk_PathInfo}。
 * @return 如果接口调用成功，返回{@link CLOUD_DISK_OK}；否则返回云盘管理模块的错误码{@link CloudDisk_ErrorCode}。
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_UnregisterSyncFolderChanges(const CloudDisk_SyncFolderPath syncFolderPath);

/**
 * @brief 获取同步根路径下的历史操作记录。
 *
 * @param syncFolderPath 查询的同步根路径，参考：{@link CloudDisk_PathInfo}。
 * @param startUsn 查询起始的变更序列，范围：[0, 2^64 - 1]。
 * @param count 查询文件变更的数量，范围：[1, 100]。
 * @param changesResult 表示查询文件变更的结果。详情请参阅{@link CloudDisk_ChangesResult}。
 * @return 如果接口调用成功，返回{@link CLOUD_DISK_OK}；否则返回云盘管理模块的错误码{@link CloudDisk_ErrorCode}。
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_GetSyncFolderChanges(const CloudDisk_SyncFolderPath syncFolderPath,
                                                      uint64_t startUsn,
                                                      size_t count,
                                                      CloudDisk_ChangesResult **changesResult);

/**
 * @brief 应用设置同步根路径下文件的同步状态。
 *
 * @param syncFolderPath 待设置的同步根路径，参考：{@link CloudDisk_PathInfo}。
 * @param fileSyncStates The array of {@link CloudDisk_FileSyncState} specifying the file paths and their target sync
 *     states.
 * @param bufferLength 待设置同步状态数组的长度，范围：[1, 100]。
 * @param failedLists 输出参数。返回一个指向{@link CloudDisk_FailedList}数组的指针，该数组包含设置失败的文件。
 * @param failedCount 输出参数。设置同步状态失败的文件列表数组长度。
 * @return 如果接口调用成功，返回{@link CLOUD_DISK_OK}；否则返回云盘管理模块的错误码{@link CloudDisk_ErrorCode}。
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_SetFileSyncStates(const CloudDisk_SyncFolderPath syncFolderPath,
                                                   const CloudDisk_FileSyncState fileSyncStates[],
                                                   size_t bufferLength,
                                                   CloudDisk_FailedList **failedLists,
                                                   size_t *failedCount);

/**
 * @brief 应用查询同步根路径下文件同步状态。
 *
 * @param syncFolderPath 待查询的同步根路径，参考：{@link CloudDisk_PathInfo}。
 * @param paths The array of file paths to query.
 * @param bufferLength 待查询同步状态的数组的长度，范围：[1, 100]。
 * @param resultLists 输出参数。返回一个查询到的文件同步操作结果，详情可参考：{@link CloudDisk_ResultList}。
 * @param resultCount 输出参数。返回失败的文件数量。
 * @return 如果接口调用成功，返回{@link CLOUD_DISK_OK}；否则返回云盘管理模块的错误码{@link CloudDisk_ErrorCode}。
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_GetFileSyncStates(const CloudDisk_SyncFolderPath syncFolderPath,
                                                   const CloudDisk_PathInfo paths[],
                                                   size_t bufferLength,
                                                   CloudDisk_ResultList **resultLists,
                                                   size_t *resultCount);

/**
 * @brief 应用注册同步根。
 *
 * @param syncFolder 待注册的同步根路径，参考：{@link CloudDisk_SyncFolder}。
 * @return 如果接口调用成功，返回{@link CLOUD_DISK_OK}；否则返回云盘管理模块的错误码{@link CloudDisk_ErrorCode}。
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_RegisterSyncFolder(const CloudDisk_SyncFolder *syncFolder);

/**
 * @brief 应用取消注册同步根。
 *
 * @param syncFolderPath 需要取消注册的同步根路径，参考：{@link CloudDisk_PathInfo}。
 * @return 如果接口调用成功，返回{@link CLOUD_DISK_OK}；否则返回云盘管理模块的错误码{@link CloudDisk_ErrorCode}。
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_UnregisterSyncFolder(const CloudDisk_SyncFolderPath syncFolderPath);

/**
 * @brief 应用激活同步根。
 *
 * @param syncFolderPath 需要激活监听的同步根路径，参考：{@link CloudDisk_PathInfo}。
 * @return 如果接口调用成功，返回{@link CLOUD_DISK_OK}；否则返回云盘管理模块的错误码{@link CloudDisk_ErrorCode}。
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_ActiveSyncFolder(const CloudDisk_SyncFolderPath syncFolderPath);

/**
 * @brief 应用取消激活同步根。
 *
 * @param syncFolderPath 取消激活监听的同步根路径，参考：{@link CloudDisk_PathInfo}。
 * @return 如果接口调用成功，返回{@link CLOUD_DISK_OK}；否则返回云盘管理模块的错误码{@link CloudDisk_ErrorCode}。
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_DeactiveSyncFolder(const CloudDisk_SyncFolderPath syncFolderPath);

/**
 * @brief 应用获取所有同步根。
 *
 * @param syncFolders 输出参数。返回同步根路径数组{@link CloudDisk_SyncFolder}。
 * @param count 输出参数。当前网盘注册的所有同步根的数量。
 * @return 如果接口调用成功，返回{@link CLOUD_DISK_OK}；否则返回云盘管理模块的错误码{@link CloudDisk_ErrorCode}。
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_GetSyncFolders(CloudDisk_SyncFolder **syncFolders, size_t *count);

/**
 * @brief 应用更新同步根别名。
 *
 * @param syncFolderPath 待更新别名的同步根路径，参考：{@link CloudDisk_PathInfo}。
 * @param customAlias 用户定义的别名，不能包含字符：\\\/\*\?\<\>\|\:\"，以及不能以"."、".."和纯空格作为完整名称。
 * @param customAliasLength 用户定义的别名长度，范围：[0, 255]。
 * @return 如果接口调用成功，返回{@link CLOUD_DISK_OK}；否则返回云盘管理模块的错误码{@link CloudDisk_ErrorCode}。
 * @since 21
 */
CloudDisk_ErrorCode OH_CloudDisk_UpdateCustomAlias(
    const CloudDisk_SyncFolderPath syncFolderPath, const char *customAlias, size_t customAliasLength);
#ifdef __cplusplus
};
#endif
/** @} */
#endif // FILEMANAGEMENT_KIT_OH_CLOUD_DISK_MANAGER_NDK_H
