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
 * @brief Swapfs模块提供swap文件系统相关的错误码定义，用于管理和监控应用的swap分区使用情况。\n
 * 该模块支持swap分区的创建、挂载、卸载等操作，适用于需要优化内存管理、提升应用运行性能的场景。\n
 * 该模块能够帮助开发者有效利用系统swap资源，改善内存不足情况下的应用体验。
 *
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @since 26.0.0
 */

/**
 * @file swapfs_errcode.h
 *
 * @brief 声明swapfs模块的错误码，包括文件系统操作过程中的各类错误状态定义。
 *
 * @library libohswapfs.so
 * @kit CoreFileKit
 * @include <filemanagement/swapfs/swapfs_errcode.h>
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @since 26.0.0
 */

#ifndef FILE_MANAGEMENT_SWAPFS_ERRCODE_H
#define FILE_MANAGEMENT_SWAPFS_ERRCODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief swapfs模块的错误码。
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
     * @brief 无效参数。可能的原因包括空指针、零长度或无效的配置值。请检查传入参数是否合法。
     *
     * @since 26.0.0
     */
    SWAPFS_E_INVAL = 36200001,
    /**
     * @brief Direct I/O缓冲区地址或长度未对齐到SWAPFS_DIO_ALIGNMENT。
     *
     * @since 26.0.0
     */
    SWAPFS_E_DIO_ALIGN = 36200002,
    /**
     * @brief 换入缓冲区大小小于所需大小（Direct I/O模式下为occupiedSize，缓冲模式下为dataSize）。\n
     * dataSize为实际写入的数据字节数。\n
     * occupiedSize为磁盘上占用的物理空间字节数（Direct I/O模式下对齐到 4096，等于dataSize向上取整到SWAPFS_DIO_ALIGNMENT的倍数）。
     *
     * @since 26.0.0
     */
    SWAPFS_E_BUFFER_TOO_SMALL = 36200003,
    /**
     * @brief 指定的keyId在当前管理器中不存在。请确认keyId是否正确或已创建。
     *
     * @since 26.0.0
     */
    SWAPFS_E_KEY_NOT_FOUND = 36200004,
    /**
     * @brief key处于OH_SWAPFS_KEY_STATUS_REMOVING状态，无法进行操作。请等待key删除完成或使用其他可用的key。
     *
     * @since 26.0.0
     */
    SWAPFS_E_KEY_STATE_INVALID = 36200005,
    /**
     * @brief 检测到并发冲突。\n
     * {@link OH_Swapfs_RemoveAllData}或{@link OH_Swapfs_DestroyManager}检测到有活跃操作正在进行。请稍后重试或等待当前操作完成。
     *
     * @since 26.0.0
     */
    SWAPFS_E_BUSY = 36200006,
    /**
     * @brief 设备存储空间不足。请清理存储空间后重试。
     *
     * @since 26.0.0
     */
    SWAPFS_E_NOSPC = 36200007,
    /**
     * @brief 换出空间配额超限。总占用空间已达到配置的上限。请清理已换出的数据或调整配额上限。
     *
     * @since 26.0.0
     */
    SWAPFS_E_QUOTA_EXCEEDED = 36200008,
    /**
     * @brief IO读取或写入失败。原因可能包括：实际读取/写入字节数少于请求字节数（短读/短写）、数据持久化失败（fsync失败）或文件重命名失败。
     *
     * @since 26.0.0
     */
    SWAPFS_E_IO_ERROR = 36200009,
    /**
     * @brief 换出功能因设备存储空间不足或控制策略被禁用。
     *
     * @since 26.0.0
     */
    SWAPFS_E_FEATURE_DISABLED = 36200010,
    /**
     * @brief 权限被拒绝。请检查应用权限或文件访问权限。
     *
     * @since 26.0.0
     */
    SWAPFS_E_ACCES = 36200011,
    /**
     * @brief 换出根路径无法创建或不可用。请检查路径配置或存储设备状态。
     *
     * @since 26.0.0
     */
    SWAPFS_E_PATH_UNAVAILABLE = 36200012,
    /**
     * @brief 管理器正在关闭。\n
     * 新的{@link OH_Swapfs_SwapOut}、{@link OH_Swapfs_SwapIn}、{@link OH_Swapfs_RemoveData}或{@link OH_Swapfs_RemoveAllData}操作将被拒绝。
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
