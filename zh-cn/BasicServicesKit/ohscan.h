/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup OH_Scan
 * @{
 *
 * @brief Provides the definition of the C interface for the scan module.
 *
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file ohscan.h
 *
 * @brief 声明用于发现和连接扫描仪、从扫描仪扫描图片、获取图片扫描进度和设置扫描仪参数等功能的API，适用于需要在应用内集成扫描仪相关操作的场景。
 *
 * @library libohscan.so
 * @kit BasicServicesKit
 * @syscap SystemCapability.Print.PrintFramework
 * @include <ohscan.h>
 * @since 12
 * @version 1.0
 */

#ifndef OH_SCAN_H
#define OH_SCAN_H
#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义错误码。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 操作成功
     */
    SCAN_ERROR_NONE = 0,

    /**
     * 权限验证失败，需申请接口所需权限
     */
    SCAN_ERROR_NO_PERMISSION = 201,

    /**
     * 参数无效。例如指针为空或字符串为空，请检查传入的参数是否合法
     */
    SCAN_ERROR_INVALID_PARAMETER = 401,

    /**
     * 通用内部错误，请稍后重试
     */
    SCAN_ERROR_GENERIC_FAILURE = 24300101,

    /**
     * RPC通信错误，请检查扫描服务状态后重试
     */
    SCAN_ERROR_RPC_FAILURE = 24300102,

    /**
     * 表示扫描过程中发生错误，请稍后重试
     */
    SCAN_ERROR_SERVER_FAILURE = 24300103,

    /**
     * 不支持的操作，请检查当前扫描仪是否支持该操作
     */
    SCAN_ERROR_UNSUPPORTED = 24300104,

    /**
     * 操作已取消，请重新发起扫描
     */
    SCAN_ERROR_CANCELED = 24300105,

    /**
     * 扫描仪繁忙，请稍后重试
     */
    SCAN_ERROR_DEVICE_BUSY = 24300106,

    /**
     * 数据无效（包括打开时无设备），请检查扫描仪连接状态
     */
    SCAN_ERROR_INVALID = 24300107,

    /**
     * 文档进纸器卡纸，请清除卡纸后重试
     */
    SCAN_ERROR_JAMMED = 24300108,

    /**
     * 文档进纸器缺纸，请在进纸器中放入文档后重试
     */
    SCAN_ERROR_NO_DOCS = 24300109,

    /**
     * 扫描仪盖板打开，请关闭盖板后重试
     */
    SCAN_ERROR_COVER_OPEN = 24300110,

    /**
     * 扫描仪I/O错误，请检查扫描仪连接并重试
     */
    SCAN_ERROR_IO_ERROR = 24300111,

    /**
     * 内存不足，请释放资源后重试
     */
    SCAN_ERROR_NO_MEMORY = 24300112
} Scan_ErrorCode;

/**
 * @brief Scan_ScannerDevice表示扫描仪设备信息，包含扫描仪ID、制造商、型号、发现模式和序列号等属性，用于在扫描仪发现流程中获取设备详情，
 * 开发者可通过扫描仪发现相关接口获取该结构体以选择目标扫描仪设备进行扫描操作。相关模块设计逻辑请参见{@link OH_Scan}。
 *
 * @since 12
 */
typedef struct {
    /**
     * 扫描仪ID。
     */
    const char *scannerId;
    /**
     * 扫描仪制造商。
     */
    const char *manufacturer;
    /**
     * 扫描仪型号。
     */
    const char *model;
    /**
     * 扫描仪发现模式，表示扫描仪设备被系统发现的方式。值为"TCP"时，表示扫描仪通过网络发现；值为"USB"时，表示扫描仪通过USB连接发现。
     */
    const char *discoverMode;
    /**
     * 扫描仪序列号。
     */
    const char *serialNumber;
} Scan_ScannerDevice;

/**
 * @brief 表示扫描仪扫描图片的进度。该结构体包含进度值（progress）、文件描述符（fd）及是否为最后扫描的图片（isFinal），适用于需要在应用中实时跟踪图片扫描状态、获取扫描结果文件的场景。详细实现机制请参见
 * {@link OH_Scan}。
 *
 * @since 12
 */
typedef struct {
    /**
     * 图片的扫描进度，取值范围[0, 100]，单位：百分比。0表示扫描刚开始，100表示扫描完成。
     */
    int32_t progress;
    /**
     * 扫描仪扫描图片的文件描述符，用于读取扫描仪传输的图片数据。仅当progress为100时，该fd为有效文件描述符。
     */
    int32_t fd;
    /**
     * 指示该图片是否为最后扫描的图片。true表示是最后扫描的图片，false表示不是最后扫描的图片。仅当progress为100时，该isFinal为有效标识符。
     */
    bool isFinal;
} Scan_PictureScanProgress;

/**
 * @brief 表示一个扫描仪的可设置参数选项，用于配置扫描仪的参数，支持配置选项标题、描述、可设置范围及选项数量。每个选项由一组标题（titles）、描述（descriptions）和可设置范围（ranges）组成，
 * 三者以平行数组的形式存储，optionCount表示选项的总数量，开发者可通过索引i（需满足0 ≤ i < optionCount）同时访问titles[i]、descriptions[i] 和ranges[i]
 * 来获取第i个选项的完整信息。需保证titles、descriptions、ranges三者的数组长度一致且等于optionCount，否则可能无法正确获取选项的完整信息。
 *
 * @since 12
 */
typedef struct {
    /**
     * 选项标题
     */
    char **titles;
    /**
     * 选项描述
     */
    char **descriptions;
    /**
     * 选项可设置的范围
     */
    char **ranges;
    /**
     * 选项数量
     */
    int32_t optionCount;
} Scan_ScannerOptions;

/**
 * @brief 扫描仪设备发现回调，通过{@link OH_Scan_StartScannerDiscovery}注册。
 *
 * @param devices 所有发现的扫描仪设备列表，devices指针指向的内存将在回调函数结束时释放
 * @param deviceCount 发现的扫描仪数量
 * @since 12
 */
typedef void (*Scan_ScannerDiscoveryCallback)(Scan_ScannerDevice** devices, int32_t deviceCount);

/**
 * @brief 此API检查并拉起扫描服务，初始化扫描客户端，并建立与扫描服务的连接。应先调用此API初始化扫描服务，再调用其他扫描API。在使用完毕后，需调用 {@link OH_Scan_Exit} 释放资源。
 *
 * @permission {@code ohos.permission.PRINT}
 * @return {@link SCAN_ERROR_NONE} 表示扫描服务成功启动
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 * @since 12
 */
int32_t OH_Scan_Init();

/**
 * @brief 此API开始发现扫描仪，注册回调函数处理发现的扫描仪设备。注册的回调将在调用 {@link OH_Scan_Exit} 时注销。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param callback 扫描仪发现事件的{@link Scan_ScannerDiscoveryCallback}回调函数，不能为NULL
 * @return {@link SCAN_ERROR_NONE} 表示成功开始扫描仪搜索
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 * @since 12
 */
int32_t OH_Scan_StartScannerDiscovery(Scan_ScannerDiscoveryCallback callback);

/**
 * @brief 此API连接到扫描仪设备。设备使用完毕后，可调用 {@link OH_Scan_CloseScanner} 关闭。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 用于连接扫描仪的ID，取值应为已发现的有效扫描仪设备ID。
 * @return {@link SCAN_ERROR_NONE} 表示扫描仪成功连接
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 *     <br>{@link SCAN_ERROR_DEVICE_BUSY} 表示扫描仪繁忙
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER} 表示输入参数无效
 *     <br>{@link SCAN_ERROR_IO_ERROR} 表示与扫描仪通信时发生错误
 *     <br>{@link SCAN_ERROR_NO_MEMORY} 表示可用内存不足
 * @since 12
 */
int32_t OH_Scan_OpenScanner(const char* scannerId);

/**
 * @brief 此API用于关闭已连接的扫描仪设备。一般在扫描仪使用完毕后调用此API关闭连接。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 用于断开扫描仪连接的ID，取值应为已连接的有效扫描仪设备ID。
 * @return {@link SCAN_ERROR_NONE} 表示扫描仪连接成功关闭
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER} 表示输入参数无效
 * @since 12
 */
int32_t OH_Scan_CloseScanner(const char* scannerId);

/**
 * @brief 此API可用于获取扫描仪可设置的选项列表。返回的结构体指针指向的内存会在{@link OH_Scan_Exit}时自动释放，每个扫描仪型号在内存中只会存储一份副本。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 用于获取扫描仪参数的ID，取值应为已连接的有效扫描仪设备ID。
 * @param errorCode 不能为NULL。如果执行成功，errorCode返回{@link SCAN_ERROR_NONE}，否则返回特定的错误码，参考{@link Scan_ErrorCode}。
 * @return 成功时返回扫描仪参数选项结构体指针，可用于获取和设置扫描仪参数选项；失败时返回NULL。
 * @since 12
 */
Scan_ScannerOptions* OH_Scan_GetScannerParameter(const char* scannerId, int32_t* errorCode);

/**
 * @brief 此API可用于设置扫描仪的某个选项参数。传入的选项和值从{@link OH_Scan_GetScannerParameter}获取。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 此ID用于设置特定扫描仪的选项，取值应为已连接的有效扫描仪设备ID。
 * @param option 要设置的选项编号。取值范围从0到optionCount - 1，从{@link Scan_ScannerOptions}获取。
 * @param value 要设置的选项值，有效值从{@link Scan_ScannerOptions}的ranges中获取。
 * @return {@link SCAN_ERROR_NONE} 表示扫描仪参数设置成功
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER} 表示输入参数无效
 * @since 12
 */
int32_t OH_Scan_SetScannerParameter(const char* scannerId, const int32_t option, const char* value);

/**
 * @brief 此API用于启动扫描仪的扫描任务。成功初始化扫描服务，并连接扫描仪完成参数设置后，可以调用此API开始扫描。扫描过程中可调用 {@link OH_Scan_GetPictureScanProgress} 获取扫描进度，
 * 可调用 {@link OH_Scan_CancelScan} 取消扫描。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 此ID用于启动指定扫描仪的扫描任务，取值应为已连接的有效扫描仪设备ID。
 * @param batchMode 是否以批处理模式启动扫描仪。true表示开启批处理模式，扫描仪可连续扫描多页文档（通常经文档进纸器连续进纸）；false表示关闭批处理模式，仅扫描单页。
 * @return {@link SCAN_ERROR_NONE} 表示扫描仪成功启动扫描任务
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 *     <br>{@link SCAN_ERROR_JAMMED} 表示文档进纸器卡纸
 *     <br>{@link SCAN_ERROR_NO_DOCS} 表示文档进纸器缺纸
 *     <br>{@link SCAN_ERROR_COVER_OPEN} 表示扫描仪盖板打开
 *     <br>{@link SCAN_ERROR_IO_ERROR} 表示与扫描仪通信时发生错误
 *     <br>{@link SCAN_ERROR_NO_MEMORY} 表示可用内存不足
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER} 表示输入参数无效
 *     <br>{@link SCAN_ERROR_DEVICE_BUSY} 表示扫描仪繁忙，应稍后重试操作
 * @since 12
 */
int32_t OH_Scan_StartScan(const char* scannerId, bool batchMode);

/**
 * @brief 此API用于取消扫描仪正在进行的扫描任务。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 此ID用于取消指定扫描仪的扫描任务，取值应为已连接的有效扫描仪设备ID。
 * @return {@link SCAN_ERROR_NONE} 表示扫描仪成功取消扫描任务
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER} 表示输入参数无效
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 * @since 12
 */
int32_t OH_Scan_CancelScan(const char* scannerId);

/**
 * @brief 此API可获取扫描仪扫描图片的进度。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 用于查询扫描仪图片扫描进度的ID，取值应为已连接的有效扫描仪设备ID。
 * @param prog 扫描图片的{@link Scan_PictureScanProgress}，必须传入非空值，扫描进度将写入prog指针指向的结构体。
 * @return {@link SCAN_ERROR_NONE} 表示扫描仪成功查询到扫描图片的进度
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER} 表示输入参数无效
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 *     <br>{@link SCAN_ERROR_JAMMED} 表示文档进纸器卡纸
 *     <br>{@link SCAN_ERROR_NO_DOCS} 表示文档进纸器缺纸
 *     <br>{@link SCAN_ERROR_COVER_OPEN} 表示扫描仪盖板打开
 *     <br>{@link SCAN_ERROR_IO_ERROR} 表示与扫描仪通信时发生错误
 *     <br>{@link SCAN_ERROR_NO_MEMORY} 表示可用内存不足
 *     <br>{@link SCAN_ERROR_DEVICE_BUSY} 表示扫描仪繁忙，应稍后重试操作
 * @since 12
 */
int32_t OH_Scan_GetPictureScanProgress(const char* scannerId, Scan_PictureScanProgress* prog);

/**
 * @brief 此API可用于退出扫描服务，释放扫描框架内存，并注销扫描仪设备发现回调。扫描服务退出后，将无法再调用其他扫描API。
 *
 * @permission {@code ohos.permission.PRINT}
 * @return {@link SCAN_ERROR_NONE} 表示扫描服务成功退出
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 * @since 12
 */
int32_t OH_Scan_Exit();

#ifdef __cplusplus
}
#endif
#endif  // OH_SCAN_H

/** @} */