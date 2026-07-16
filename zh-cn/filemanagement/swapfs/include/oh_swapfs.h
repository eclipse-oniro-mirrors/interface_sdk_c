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
 * @brief Direct IO缓冲区的最低对齐要求。
 * @systemapi
 * @since 26.0.0
 */
#define SWAPFS_DIO_ALIGNMENT 4096U

/**
 * @brief 定义swap key的状态。
 * @systemapi
 * @since 26.0.0
 */
typedef enum OH_SwapfsKeyStatus {
    /**
     * @brief key处于活动状态，可用于换入、查询或删除。
     * @since 26.0.0
     */
    OH_SWAPFS_KEY_STATUS_ACTIVE = 0,
    /**
     * @brief key被逻辑删除。新的换入或查询操作将被拒绝。
     * @since 26.0.0
     */
    OH_SWAPFS_KEY_STATUS_REMOVING = 1
} OH_SwapfsKeyStatus;

/**
 * @brief 定义了禁用换出特性的原因。
 * @systemapi
 * @since 26.0.0
 */
typedef enum OH_SwapfsDisableReason {
    /**
     * @brief 功能已启用（无禁用原因）。
     * @since 26.0.0
     */
    OH_SWAPFS_DISABLE_REASON_NONE = 0,
    /**
     * @brief 设备存储空间不足。
     * @since 26.0.0
     */
    OH_SWAPFS_DISABLE_REASON_NOSPC = 1
} OH_SwapfsDisableReason;

/**
 * @brief 该结构体用于执行swapfs manager的相关操作。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsManager OH_SwapfsManager;

/**
 * @brief 创建swapfs管理器的配置。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsConfig {
    /**
     * @brief 交换数据存储的根路径。当为NULL或为空时，使用应用沙箱下默认的临时目录。
     * @since 26.0.0
     */
    const char *swapRootPath;
    /**
     * @brief 最大交换空间（以字节为单位）。为0时，默认限制为1GB (1073741824)。
     * @since 26.0.0
     */
    uint64_t spaceLimitBytes;
    /**
     * @brief 是否为换出操作强制实施直接IO。如果为false，则使用缓冲IO；
     * 如果为true，使用直接IO，未对齐的缓冲区将导致错误。
     * @since 26.0.0
     */
    bool useDirectIo;
} OH_SwapfsConfig;

/**
 * @brief 换出操作请求参数。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsSwapOutRequest {
    /**
     * @brief 指向要换出的数据缓冲区的指针。不能为NULL。
     * @since 26.0.0
     */
    const void *buffer;
    /**
     * @brief 数据缓冲区的大小，以字节为单位。必须大于0。
     * @since 26.0.0
     */
    uint64_t bufferSize;
} OH_SwapfsSwapOutRequest;

/**
 * @brief 换入操作的请求参数。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsSwapInRequest {
    /**
     * @brief 上一次换出操作返回的keyId。
     * @since 26.0.0
     */
    uint64_t keyId;
    /**
     * @brief 接收换入数据的缓冲区指针。不能为NULL。
     * DIO模式下，buffer地址和大小必须对齐SWAPFS_DIO_ALIGNMENT。
     * 且bufferSize必须大于等于OccupiedSize。在缓冲模式下，
     * bufferSize必须大于等于dataSize。
     * @since 26.0.0
     */
    void *buffer;
    /**
     * @brief 接收缓冲区大小，以字节为单位。
     * @since 26.0.0
     */
    uint64_t bufferSize;
} OH_SwapfsSwapInRequest;

/**
 * @brief 单个swap key的信息。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsDataInfo {
    /**
     * @brief 标识此交换数据条目的keyId。
     * @since 26.0.0
     */
    uint64_t keyId;
    /**
     * @brief 在换出期间由调用方提供的原始数据大小（以字节为单位）。
     * @since 26.0.0
     */
    uint64_t dataSize;
    /**
     * @brief 磁盘上占用的文件大小（以字节为单位）。在DIO模式下，这是将dataSize对齐到
     * SWAPFS_DIO_ALIGNMENT；在缓冲模式下，它等于dataSize。
     * @since 26.0.0
     */
    uint64_t occupiedSize;
    /**
     * @brief 创建Key时的时间戳（Unix epoch，以毫秒为单位）。
     * @since 26.0.0
     */
    int64_t createTime;
    /**
     * @brief key的当前状态。
     * @since 26.0.0
     */
    OH_SwapfsKeyStatus status;
    /**
     * @brief key对应的数据是否可以换入。如果Key处于删除状态，则为False。
     * @since 26.0.0
     */
    bool canSwapIn;
} OH_SwapfsDataInfo;

/**
 * @brief 当前swapfs管理器的统计信息。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsStats {
    /**
     * @brief 管理器中的活动Key总数。
     * @since 26.0.0
     */
    uint64_t totalKeys;
    /**
     * @brief 所有Key的原始数据总大小，以字节为单位。
     * @since 26.0.0
     */
    uint64_t totalDataSize;
    /**
     * @brief 所有Key的总对齐文件大小（以字节为单位）。
     * @since 26.0.0
     */
    uint64_t totalOccupiedSize;
    /**
     * @brief 配置的交换空间限制（以字节为单位）。
     * @since 26.0.0
     */
    uint64_t spaceLimitBytes;
    /**
     * @brief 当前是否启用了换出。当设备空间低于5GB或
     * 控制策略禁用该功能。
     * @since 26.0.0
     */
    bool featureEnabled;
    /**
     * @brief 功能关闭的原因。
     * @since 26.0.0
     */
    OH_SwapfsDisableReason disableReason;
    /**
     * @brief 成功的换出操作写入的累计字节数。
     * @since 26.0.0
     */
    uint64_t accumulatedWriteBytes;
    /**
     * @brief 上次设备空间检查的时间戳（Unix epoch，以毫秒为单位）。
     * @since 26.0.0
     */
    int64_t lastSpaceCheckTime;
    /**
     * @brief 上次检查时缓存的可用设备存储空间（以字节为单位）。
     * @since 26.0.0
     */
    uint64_t availableDeviceSpace;
} OH_SwapfsStats;

/**
 * @brief 创建swapfs管理器。
 *
 * @param config 【in】指向配置的指针，若为NULL则使用默认配置
 * （默认临时目录，1GB限制，useDirectIo=false）。
 * @param manager 【out】接收创建的OH_SwapfsManager句柄的指针。
 * 不能为NULL。失败时，指向的值被设置为NULL。
 * @return 返回执行的错误代码。
 * <ul>
 * <li>{@link SWAPFS_E_OK}执行成功</li>
 * <li>{@link SWAPFS_E_INVAL}管理器为空。</li>
 * <li>{@link SWAPFS_E_IO_ERROR}内存分配失败。</li>
 * 交换根路径的<li>{@link SWAPFS_E_ACCES}权限被拒绝。</li>
 * <li>{@link SWAPFS_E_PATH_UNAVAILABLE}交换根路径无法创建。</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * </ul>
 * @release swapfs/OH_Swapfs_DestroyManager {manager}
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_CreateManager(const OH_SwapfsConfig *config, OH_SwapfsManager **manager);

/**
 * @brief 销毁swapfs管理器并释放所有资源。
 *
 * 该功能进入关闭状态，拒绝新的换出、换入、移除、
 * 和remove-all操作。它最多等待5秒，以便活动操作完成。
 * 如果所有操作在超时时间内完成，则管理器拥有的所有交换数据
 * 自动删除，管理器被销毁。如果等待超时，此函数
 * 取消关闭状态并返回SWAPFS_E_BUSY；调用者可以稍后重试。
 *
 * @param manager 【in】指向要销毁的OH_SwapfsManager对象的指针。不能为NULL。
 * @return 返回执行的错误码。
 * <ul>
 * <li>{@link SWAPFS_E_OK}执行成功</li>
 * <li>{@link SWAPFS_E_INVAL}管理器为空。</li>
 * <li>{@link SWAPFS_E_BUSY}有正在进行的活动操作。</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_DestroyManager(OH_SwapfsManager *manager);

/**
 * @brief 将数据从内存交换到磁盘。
 *
 * 当config.useDirectIo为false时，使用缓冲IO。如果为true，则需要直接IO
 * 和未对齐的缓冲区会导致错误。在DIO模式下，交换文件的大小被填充为
 * SWAPFS_DIO_ALIGNMENT（大于等于dataSize）。
 *
 * @param manager 【in】指向OH_SwapfsManager对象的指针。不能为NULL。
 * @param request 【in】指针，指向换出请求，包含数据缓冲区及其大小。
 * 不能为NULL。
 * @param keyId 【out】接收此交换数据生成的keyId的指针。不能为NULL。
 * 失败时，指向的值不变。
 * @return 返回执行的错误代码。
 * <ul>
 * <li>{@link SWAPFS_E_OK}执行成功</li>
 * <li>{@link SWAPFS_E_INVAL}管理器为nullptr，请求为nullptr, keyId为nullptr。
 * buffer为nullptr，或者bufferSize为0。</li>
 * <li>{@link SWAPFS_E_DIO_ALIGN} useDirectIo为真且缓冲区未对齐。</li>
 * <li>{@link SWAPFS_E_NOSPC}设备存储空间不足。</li>
 * <li>{@link SWAPFS_E_QUOTA_EXCEEDED}超出交换空间配额。</li>
 * <li>{@link SWAPFS_E_FEATURE_DISABLED}由于空间或策略不足而禁用了换出。</li>
 * <li>{@link SWAPFS_E_IO_ERROR} IO写入失败。</li>
 * <li>{@link SWAPFS_E_ACCES}权限被拒绝。</li>
 * <li>{@link SWAPFS_E_BUSY} RemoveAllData正在进行或并发操作太多。</li>
 * <li>{@link SWAPFS_E_SHUTING_DOWN}管理器正在关闭。</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_SwapOut(OH_SwapfsManager *manager, const OH_SwapfsSwapOutRequest *request,
    uint64_t *keyId);

/**
 * @brief 将数据从磁盘交换回内存。
 *
 * 在DIO模式下，缓冲区地址和大小必须对齐SWAPFS_DIO_ALIGNMENT。
 * bufferSize必须大于或等于占用的大小。在缓冲模式下，bufferSize
 * 必须大于或等于dataSize。成功后，readSize会收到原
 * dataSize（不占用）。
 *
 * @param manager 【in】指向OH_SwapfsManager对象的指针。不能为NULL。
 * @param request 【in】指针类型，指向swap-in请求，包含keyId、buffer和bufferSize。
 * 不能为NULL。
 * @param readSize 【out】以字节为单位接收原始数据大小的指针，如果调用者不需要它，则为NULL。成功时，接收原始的dataSize。失败时，指向的值不变。
 * @return 返回执行的错误代码。
 * <ul>
 * <li>{@link SWAPFS_E_OK}执行成功</li>
 * <li>{@link SWAPFS_E_INVAL}管理器为nullptr，请求为nullptr, keyId为0，
 * buffer为nullptr，或者bufferSize为0。</li>
 * <li>{@link SWAPFS_E_DIO_ALIGN}缓冲区地址或大小未与SWAPFS_DIO_ALIGNMENT对齐。</li>
 * <li>{@link SWAPFS_E_BUFFER_TOO_SMALL} bufferSize小于所需的大小。</li>
 * <li>{@link SWAPFS_E_KEY_NOT_FOUND} keyId不存在。</li>
 * <li>{@link SWAPFS_E_KEY_STATE_INVALID}项处于删除状态。</li>
 * <li>{@link SWAPFS_E_IO_ERROR} IO读取失败。</li>
 * <li>{@link SWAPFS_E_ACCES}权限被拒绝。</li>
 * <li>{@link SWAPFS_E_BUSY}并发操作过多。</li>
 * <li>{@link SWAPFS_E_SHUTING_DOWN}管理器正在关闭。</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_SwapIn(OH_SwapfsManager *manager, const OH_SwapfsSwapInRequest *request,
    uint64_t *readSize);

/**
 * @brief 查询指定swap key的信息。
 *
 * @param manager 【in】指向OH_SwapfsManager对象的指针。不能为NULL。
 * @param keyId 【in】要查询的keyId。
 * @param info 【out】指向OH_SwapfsDataInfo结构体的指针，用于接收key信息。
 * 不能为NULL。失败时，内容不变。
 * @return 返回执行的错误码。
 * <ul>
 * <li>{@link SWAPFS_E_OK}执行成功</li>
 * <li>{@link SWAPFS_E_INVAL}管理器为nullptr, keyId为0，或者info为nullptr。</li>
 * <li>{@link SWAPFS_E_KEY_NOT_FOUND} keyId不存在。</li>
 * <li>{@link SWAPFS_E_KEY_STATE_INVALID}项处于删除状态。</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_QueryData(OH_SwapfsManager *manager, uint64_t keyId, OH_SwapfsDataInfo *info);

/**
 * @brief 获取当前swapfs管理器的统计信息。
 *
 * @param manager 【in】指向OH_SwapfsManager对象的指针。不能为NULL。
 * @param stats 【out】指向OH_SwapfsStats结构体的指针，用于接收统计信息。
 * 不能为NULL。失败时，内容不变。
 * @return 返回执行的错误码。
 * <ul>
 * <li>{@link SWAPFS_E_OK}执行成功</li>
 * <li>{@link SWAPFS_E_INVAL}管理器为nullptr，或者stats为nullptr。</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_GetStats(OH_SwapfsManager *manager, OH_SwapfsStats *stats);

/**
 * @brief 逻辑删除指定的swap key。
 *
 * 键被标记为立即删除状态。现有的换入操作仍然可以完成。
 * 在此密钥上进行新的换入或查询操作将返回SWAPFS_E_KEY_STATE_INVALID。
 * 对于并发的swap-in操作，该函数不会返回SWAPFS_E_BUSY。
 *
 * @param manager 【in】指向OH_SwapfsManager对象的指针。不能为NULL。
 * @param keyId 【in】要删除的keyId。
 * @return 返回执行的错误码。
 * <ul>
 * <li>{@link SWAPFS_E_OK}如果执行成功</li>
 * <li>{@link SWAPFS_E_INVAL}管理器为nullptr或keyId为0。</li>
 * <li>{@link SWAPFS_E_KEY_NOT_FOUND} keyId不存在。</li>
 * <li>{@link SWAPFS_E_KEY_STATE_INVALID}项已处于删除状态。</li>
 * <li>{@link SWAPFS_E_BUSY}并发操作过多。</li>
 * <li>{@link SWAPFS_E_SHUTING_DOWN}管理器正在关闭。</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_RemoveData(OH_SwapfsManager *manager, uint64_t keyId);

/**
 * @brief 删除管理器中的所有交换密钥。
 *
 * 如果有正在进行的活动操作（换出或换入），或者有任何键在
 * 状态，此函数返回SWAPFS_E_BUSY，而不启动任何删除。
 *
 * @param manager 【in】指向OH_SwapfsManager对象的指针。不能为NULL。
 * @return 返回执行的错误码。
 * <ul>
 * <li>{@link SWAPFS_E_OK}执行成功</li>
 * <li>{@link SWAPFS_E_INVAL}管理器为空。</li>
 * <li>{@link SWAPFS_E_BUSY}存在正在进行的活动操作或处于删除状态的挂起密钥。</li>
 * <li>{@link SWAPFS_E_SHUTING_DOWN}管理器正在关闭。</li>
 * <li>202如果非系统应用程序调用此系统API。</li>
 * </ul>
 * @systemapi
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_RemoveAllData(OH_SwapfsManager *manager);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // FILE_MANAGEMENT_SWAPFS_OH_SWAPFS_H
