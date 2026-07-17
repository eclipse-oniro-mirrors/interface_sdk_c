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
 * @brief 提供用户空间存储换出换入的API。
 *
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @since 26.0.0
 */

/**
 * @file oh_swapfs.h
 *
 * @brief 定义swapfs（交换文件系统）的native API，提供文件系统交换空间的创建、挂载、卸载等操作接口。\n
 * swapfs模块用于管理和监控应用的swap分区使用情况。\n
 * 该模块支持交换空间的创建、挂载、卸载等操作，适用于需要优化内存管理、提升应用运行性能的场景。\n
 * 支持将数据换出到磁盘并进行管理，在后续需要取回时换入，来实现对内存的灵活管理与性能提升。\n
 * 该模块能够帮助开发者有效利用系统swap资源，改善内存不足情况下的应用体验。
 *
 * @library libohswapfs.so
 * @kit CoreFileKit
 * @include <filemanagement/swapfs/oh_swapfs.h>
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
 * @brief Direct I/O（直接I/O）缓冲区的最小对齐要求。
 * @systemapi
 * @since 26.0.0
 */
#define SWAPFS_DIO_ALIGNMENT 4096U

/**
 * @brief 被swapfs换出的数据将以key（换出数据交换单元）的形式被swapfs管理，该枚举定义已经被swapfs换出的key的状态。
 * @systemapi
 * @since 26.0.0
 */
typedef enum OH_SwapfsKeyStatus {
    /**
     * @brief key处于活跃状态，可用于换入、查询或删除操作。
     * @since 26.0.0
     */
    OH_SWAPFS_KEY_STATUS_ACTIVE = 0,
    /**
     * @brief key已被删除。新的换入或查询操作将被拒绝。
     * @since 26.0.0
     */
    OH_SWAPFS_KEY_STATUS_REMOVING = 1
} OH_SwapfsKeyStatus;

/**
 * @brief 定义换出功能被禁用的原因。仅在featureEnabled为false时有效。
 * @systemapi
 * @since 26.0.0
 */
typedef enum OH_SwapfsDisableReason {
    /**
     * @brief 换出功能已启用。
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
 * @brief 该结构体用于执行与swapfs管理器交互相关的操作。使用前需通过{@link OH_Swapfs_CreateManager}函数创建有效的管理器实例。\n
 * 该结构体用于管理swapfs的生命周期和配置，提供交换分区的创建、销毁、扩展等管理能力。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsManager OH_SwapfsManager;

/**
 * @brief 用于配置swapfs管理器的初始化参数，包括数据存储路径、空间限制和IO方式等。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsConfig {
    /**
     * @brief 存储换出数据的根路径。设置不同的根路径会影响swapfs数据的存储位置和访问性能，确保路径具有足够的存储空间和读写权限。\n
     * swapfs使用固定的 “swapfs” 子目录。当为空指针或空字符串时，使用应用沙箱下的默认临时根路径 “/data/storage/el2/base/temp/swapfs”。
     * @since 26.0.0
     */
    const char *swapRootPath;
    /**
     * @brief 最大换出空间，单位：Byte。当spaceLimitBytes为0时，默认限制为1,073,741,824 Bytes（即1GB）。
     * @since 26.0.0
     */
    uint64_t spaceLimitBytes;
    /**
     * @brief 是否对换出操作强制使用Direct I/O。为false时使用缓冲IO；为true时使用Direct I/O，将对缓冲区进行强制对齐，未对齐的缓冲区将导致错误。
     * @since 26.0.0
     */
    bool useDirectIo;
} OH_SwapfsConfig;

/**
 * @brief 换出操作的请求参数。用于在应用需要释放内存时，主动触发数据换出到交换分区的场景，例如内存紧张时将部分数据临时换出。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsSwapOutRequest {
    /**
     * @brief 指向待换出数据缓冲区的指针。不可为空指针。传入空指针时返回错误码{@link SWAPFS_E_INVAL}。
     * @since 26.0.0
     */
    const void *buffer;
    /**
     * @brief 待换出数据缓冲区的大小，单位：Byte。必须大于0。传入0时返回错误码{@link SWAPFS_E_INVAL}。
     * @since 26.0.0
     */
    uint64_t bufferSize;
} OH_SwapfsSwapOutRequest;

/**
 * @brief 换入操作的请求参数。该结构体用于描述换入操作所需的参数，包括换出时返回的keyId、接收换入数据的缓冲区及其大小。\n
 * 开发者需通过{@link OH_Swapfs_SwapOut}获取keyId，再使用本结构体中的参数调用换入接口将数据换入内存。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsSwapInRequest {
    /**
     * @brief 由先前{@link OH_Swapfs_SwapOut}返回的keyId。用于唯一标识需要换入的数据。
     * @since 26.0.0
     */
    uint64_t keyId;
    /**
     * @brief 指向接收换入数据的缓冲区指针。不可为空指针。\n
     * 在Direct I/O模式下，缓冲区地址和大小必须对齐到SWAPFS_DIO_ALIGNMENT，且bufferSize必须大于等于occupiedSize。\n
     * 在缓冲模式下，bufferSize必须大于等于dataSize。\n
     * Direct I/O模式直接读写磁盘，不经过系统缓存；缓冲模式使用系统缓存。occupiedSize表示数据实际占用的存储大小，dataSize表示数据的逻辑大小。
     * @since 26.0.0
     */
    void *buffer;
    /**
     * @brief 接收缓冲区的大小，单位：Byte。\n
     * 在Direct I/O模式下必须大于等于occupiedSize且对齐到SWAPFS_DIO_ALIGNMENT。\n
     * 在缓冲模式下必须大于等于dataSize。建议根据实际数据大小设置合适的缓冲区大小以提升性能。\n
     * 取值范围：大于等于换入数据的大小，且必须大于0。超出范围或传入无效值时接口返回错误。
     * @since 26.0.0
     */
    uint64_t bufferSize;
} OH_SwapfsSwapInRequest;

/**
 * @brief 单个key的信息。用于在应用需要精确管理换出数据条目的元信息时（如查询换出状态、监控换出大小等）。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsDataInfo {
    /**
     * @brief 交换数据条目的标识符，用于唯一标识交换数据，不同keyId对应不同的数据条目。
     * @since 26.0.0
     */
    uint64_t keyId;
    /**
     * @brief 换出时调用方提供的原始数据大小，单位：Byte。该大小决定了数据占用的空间和读取时的性能表现。
     * @since 26.0.0
     */
    uint64_t dataSize;
    /**
     * @brief 磁盘上占用的文件大小，单位：Byte。\n
     * 在Direct I/O模式下为dataSize向上对齐到SWAPFS_DIO_ALIGNMENT的值；在缓冲模式下等于dataSize。
     * @since 26.0.0
     */
    uint64_t occupiedSize;
    /**
     * @brief key创建时的时间戳（Unix纪元，单位为ms）。该时间戳用于记录数据创建时间，可用于数据排序、过期策略判断等。
     * @since 26.0.0
     */
    int64_t createTime;
    /**
     * @brief key的当前状态。不同状态值表示key的不同使用阶段，如是否可用、是否正在交换中、是否已删除等。
     * @since 26.0.0
     */
    OH_SwapfsKeyStatus status;
    /**
     * @brief 该key是否可被换入。\n
     * 如果key的{@link OH_SwapfsKeyStatus}状态处于OH_SWAPFS_KEY_STATUS_REMOVING则为false，若key活跃未被清理则为true。
     * @since 26.0.0
     */
    bool canSwapIn;
} OH_SwapfsDataInfo;

/**
 * @brief OH_SwapfsStats用于获取swapfs管理器的统计信息，包括活跃key数量、数据大小、空间使用情况等。\n
 * 适用于需要监控swapfs状态、分析存储使用情况的场景，帮助开发者了解系统的交换空间使用情况。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_SwapfsStats {
    /**
     * @brief 管理器中活跃key的总数。
     * @since 26.0.0
     */
    uint64_t totalKeys;
    /**
     * @brief 所有key的原始数据总大小，单位：Byte。
     * @since 26.0.0
     */
    uint64_t totalDataSize;
    /**
     * @brief 所有key的对齐后文件总大小，单位：Byte。
     * @since 26.0.0
     */
    uint64_t totalOccupiedSize;
    /**
     * @brief 配置的交换空间上限，单位：Byte。
     * @since 26.0.0
     */
    uint64_t spaceLimitBytes;
    /**
     * @brief 换出功能是否已启用。当设备空间低于5GB或控制策略禁用该功能时为false。
     * @since 26.0.0
     */
    bool featureEnabled;
    /**
     * @brief 换出功能被禁用的原因。仅在featureEnabled为false时有效。
     * @since 26.0.0
     */
    OH_SwapfsDisableReason disableReason;
    /**
     * @brief 成功换出操作累计写入量，单位：Byte。
     * @since 26.0.0
     */
    uint64_t accumulatedWriteBytes;
    /**
     * @brief 最近一次检查设备空间的时间戳（Unix纪元，单位为ms）。
     * @since 26.0.0
     */
    int64_t lastSpaceCheckTime;
    /**
     * @brief 最近一次检查时缓存设备的可用存储空间，单位：Byte。
     * @since 26.0.0
     */
    uint64_t availableDeviceSpace;
} OH_SwapfsStats;

/**
 * @brief 创建swapfs管理器。
 *
 * @param config 指向配置的指针，若为空指针，则config默认使用临时目录，spaceLimitBytes限制为1GB，useDirectIo为false。
 * @param manager 双指针，用于接收创建的{@link OH_SwapfsManager}句柄。不可为空指针。失败时，所指向的值被设置为空指针。
 * @return 返回执行的错误码。
 *         <ul>
 *         <li>SWAPFS_E_OK：执行成功。</li>
 *         <li>SWAPFS_E_INVAL：manager为空指针。</li>
 *         <li>SWAPFS_E_NOMEM：内存分配失败。</li>
 *         <li>SWAPFS_E_ACCES：换出根路径权限被拒绝。</li>
 *         <li>SWAPFS_E_PATH_UNAVAILABLE：换出根路径无法创建。</li>
 *         <li>202：非系统应用调用此系统API。请确保为系统应用。</li>
 *         </ul>
 * @release swapfs/OH_Swapfs_DestroyManager {manager}
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @systemapi
 * @see OH_Swapfs_ErrCode
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_CreateManager(const OH_SwapfsConfig *config, OH_SwapfsManager **manager);

/**
 * @brief 销毁swapfs管理器并释放所有资源。\n
 * 等待最多5s以使操作完成。如果所有操作在等待时间内完成，管理器拥有的所有交换数据将被自动删除，管理器将被销毁。\n
 * 如果等待超时，此函数取消关闭状态并返回{@link SWAPFS_E_BUSY}；调用方可稍后重试。\n
 * 操作完成后，该功能进入关闭状态，拒绝新的{@link OH_Swapfs_SwapOut}、{@link OH_Swapfs_SwapIn}、{@link OH_Swapfs_RemoveData}和{@link OH_Swapfs_RemoveAllData}操作。
 *
 * @param manager 指向待销毁的OH_SwapfsManager对象的指针。不可为空指针。
 * @return 返回执行的错误码。
 *         <ul>
 *         <li>SWAPFS_E_OK：执行成功。</li>
 *         <li>SWAPFS_E_INVAL：manager为空指针。</li>
 *         <li>SWAPFS_E_BUSY：存在进行中的活跃操作。</li>
 *         <li>202：非系统应用调用此系统API。请确保为系统应用。</li>
 *         </ul>
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @systemapi
 * @see OH_Swapfs_ErrCode
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_DestroyManager(OH_SwapfsManager *manager);

/**
 * @brief 将数据从内存换出到磁盘。\n
 * 当{@link OH_SwapfsConfig}中的useDirectIo为false时，使用缓冲IO。为true时，要求使用Direct I/O，未对齐的缓冲区将导致错误。\n
 * 在Direct I/O模式下，换出文件大小会被填充到SWAPFS_DIO_ALIGNMENT（occupiedSize大于等于dataSize）。
 *
 * @param manager 指向OH_SwapfsManager对象的指针。不可为空指针。
 * @param request 指向换出请求的指针，包含数据缓冲区及其大小。不可为空指针。
 * @param keyId 指向用于接收此换出数据生成的keyId的指针。不可为空指针。失败时，所指向的值不变。
 * @return 返回执行的错误码。
 *         <ul>
 *         <li>SWAPFS_E_OK：执行成功。</li>
 *         <li>SWAPFS_E_INVAL：manager为空指针、request为空指针、keyId为空指针、buffer为空指针，或bufferSize为0。</li>
 *         <li>SWAPFS_E_DIO_ALIGN：useDirectIo为true且buffer未对齐到SWAPFS_DIO_ALIGNMENT。</li>
 *         <li>SWAPFS_E_NOSPC：设备存储空间不足。</li>
 *         <li>SWAPFS_E_QUOTA_EXCEEDED：换出空间配额超限。</li>
 *         <li>SWAPFS_E_FEATURE_DISABLED：换出功能因空间不足或策略被禁用。</li>
 *         <li>SWAPFS_E_IO_ERROR：IO写入失败。</li>
 *         <li>SWAPFS_E_NOMEM：内存分配失败。</li>
 *         <li>SWAPFS_E_ACCES：权限被拒绝。</li>
 *         <li>SWAPFS_E_BUSY：{@link OH_Swapfs_RemoveAllData}正在进行或并发操作过多。</li>
 *         <li>SWAPFS_E_SHUTTING_DOWN：管理器正在关闭。</li>
 *         <li>202：非系统应用调用此系统API。请确保为系统应用。</li>
 *         </ul>
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @systemapi
 * @see OH_Swapfs_ErrCode
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_SwapOut(OH_SwapfsManager *manager, const OH_SwapfsSwapOutRequest *request,
    uint64_t *keyId);

/**
 * @brief 将数据从磁盘换入内存。\n
 * 在Direct I/O模式下，缓冲区地址和大小必须对齐到SWAPFS_DIO_ALIGNMENT，且bufferSize必须大于等于occupiedSize。\n
 * 在缓冲模式下，bufferSize必须大于等于dataSize。\n
 * 成功时，readSize接收原始dataSize（非occupiedSize）。
 *
 * @param manager 指向OH_SwapfsManager对象的指针。不可为空指针。
 * @param request 指向换入请求的指针，包含keyId、buffer和bufferSize。不可为空指针。
 * @param readSize 指向用于接收原始数据大小（原始数据大小单位：Byte）的指针，如调用方不需要可为空指针。成功时接收原始dataSize。失败时所指向的值不变。
 * @return 返回执行的错误码。
 *         <ul>
 *         <li>SWAPFS_E_OK：执行成功。</li>
 *         <li>SWAPFS_E_INVAL：manager为空指针、request为空指针、keyId为0、buffer为空指针，或bufferSize为0。</li>
 *         <li>SWAPFS_E_DIO_ALIGN：缓冲区地址或大小未对齐到SWAPFS_DIO_ALIGNMENT。</li>
 *         <li>SWAPFS_E_BUFFER_TOO_SMALL：bufferSize小于所需大小。</li>
 *         <li>SWAPFS_E_KEY_NOT_FOUND：keyId不存在。</li>
 *         <li>SWAPFS_E_KEY_STATE_INVALID：key处于 OH_SWAPFS_KEY_STATUS_REMOVING 状态。</li>
 *         <li>SWAPFS_E_IO_ERROR：IO读取失败。</li>
 *         <li>SWAPFS_E_NOMEM：内存分配失败。</li>
 *         <li>SWAPFS_E_ACCES：权限被拒绝。</li>
 *         <li>SWAPFS_E_BUSY：并发操作过多。</li>
 *         <li>SWAPFS_E_SHUTTING_DOWN：管理器正在关闭。</li>
 *         <li>202：非系统应用调用此系统API。请确保为系统应用。</li>
 *         </ul>
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @systemapi
 * @see OH_Swapfs_ErrCode
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_SwapIn(OH_SwapfsManager *manager, const OH_SwapfsSwapInRequest *request,
    uint64_t *readSize);

/**
 * @brief 查询特定swapfs key的信息，包括key的状态、数据大小等。
 *
 * @param manager 指向OH_SwapfsManager对象的指针。不可为空指针。
 * @param keyId 待查询的keyId。
 * @param info 指向用于接收key信息的{@link OH_SwapfsDataInfo}结构体的指针。不可为空指针。失败时，内容不变。
 * @return 返回执行的错误码。
 *         <ul>
 *         <li>SWAPFS_E_OK：执行成功。</li>
 *         <li>SWAPFS_E_INVAL：manager为空指针、keyId为0，或info为空指针。</li>
 *         <li>SWAPFS_E_KEY_NOT_FOUND：keyId不存在。</li>
 *         <li>SWAPFS_E_KEY_STATE_INVALID：key处于 OH_SWAPFS_KEY_STATUS_REMOVING 状态。</li>
 *         <li>202：非系统应用调用此系统API。请确保为系统应用。</li>
 *         </ul>
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @systemapi
 * @see OH_Swapfs_ErrCode
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_QueryData(OH_SwapfsManager *manager, uint64_t keyId, OH_SwapfsDataInfo *info);

/**
 * @brief 获取当前swapfs管理器的统计信息。
 *
 * @param manager 指向OH_SwapfsManager对象的指针。不可为空指针。
 * @param stats 指向用于接收统计信息的{@link OH_SwapfsStats}结构体的指针。不可为空指针。失败时，内容不变。
 * @return 返回执行的错误码。
 *         <ul>
 *         <li>SWAPFS_E_OK：执行成功。</li>
 *         <li>SWAPFS_E_INVAL：manager为空指针，或stats为空指针。</li>
 *         <li>202：非系统应用调用此系统API。请确保为系统应用。</li>
 *         </ul>
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @systemapi
 * @see OH_Swapfs_ErrCode
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_GetStats(OH_SwapfsManager *manager, OH_SwapfsStats *stats);

/**
 * @brief 逻辑删除指定的swapfs key。触发后key立即被标记OH_SWAPFS_KEY_STATUS_REMOVING状态。\n
 * 触发时若已有{@link OH_Swapfs_SwapIn}操作则仍可完成swapin，完成后开始删除。\n
 * 开始删除后，对该key的新{@link OH_Swapfs_SwapIn}或{@link OH_Swapfs_QueryData}操作将返回{@link SWAPFS_E_KEY_STATE_INVALID}。
 *
 * @param manager 指向OH_SwapfsManager对象的指针。不可为空指针。
 * @param keyId 待删除的keyId。
 * @return 返回执行的错误码。
 *         <ul>
 *         <li>SWAPFS_E_OK：执行成功。</li>
 *         <li>SWAPFS_E_INVAL：manager为空指针或keyId为0。</li>
 *         <li>SWAPFS_E_KEY_NOT_FOUND：keyId不存在。</li>
 *         <li>SWAPFS_E_KEY_STATE_INVALID：key已处于OH_SWAPFS_KEY_STATUS_REMOVING状态。</li>
 *         <li>SWAPFS_E_NOMEM：内存分配失败。</li>
 *         <li>SWAPFS_E_BUSY：并发操作过多。</li>
 *         <li>SWAPFS_E_SHUTTING_DOWN：管理器正在关闭。</li>
 *         <li>202：非系统应用调用此系统API。请确保为系统应用。</li>
 *         </ul>
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @systemapi
 * @see OH_Swapfs_ErrCode
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_RemoveData(OH_SwapfsManager *manager, uint64_t keyId);

/**
 * @brief 删除管理器中的所有swapfs key。\n
 * 如果存在进行中的操作（{@link OH_Swapfs_SwapOut}或{@link OH_Swapfs_SwapIn}），或任何key处于OH_SWAPFS_KEY_STATUS_REMOVING状态，\n
 * 此函数返回{@link SWAPFS_E_BUSY}而不开始任何删除操作。
 *
 * @param manager 指向OH_SwapfsManager对象的指针。不可为空指针。
 * @return 返回执行的错误码。
 *         <ul>
 *         <li>SWAPFS_E_OK：执行成功。</li>
 *         <li>SWAPFS_E_INVAL：manager为空指针。</li>
 *         <li>SWAPFS_E_NOMEM：内存分配失败。</li>
 *         <li>SWAPFS_E_BUSY：存在进行中的活跃操作或有key处于OH_SWAPFS_KEY_STATUS_REMOVING状态。</li>
 *         <li>SWAPFS_E_SHUTTING_DOWN：管理器正在关闭。</li>
 *         <li>202：非系统应用调用此系统API。请确保为系统应用。</li>
 *         </ul>
 * @syscap SystemCapability.FileManagement.File.Swapfs
 * @systemapi
 * @see OH_Swapfs_ErrCode
 * @since 26.0.0
 */
OH_Swapfs_ErrCode OH_Swapfs_RemoveAllData(OH_SwapfsManager *manager);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // FILE_MANAGEMENT_SWAPFS_OH_SWAPFS_H
