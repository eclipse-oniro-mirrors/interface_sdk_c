/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @file ohscan.h
 *
 * @brief Declares APIs for discovering and connecting to scanners, scanning pictures, querying the scan progress, and
 * setting parameters for scanning.
 *
 * @library libohscan.so
 * @kit BasicServicesKit
 * @syscap SystemCapability.Print.PrintFramework
 * @since 12
 * @version 1.0
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
#ifndef OH_SCAN_H
#define OH_SCAN_H
#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义错误码
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
     * 权限验证失败
     */
    SCAN_ERROR_NO_PERMISSION = 201,

    /**
     * 参数无效。例如指针为空或字符串为空
     */
    SCAN_ERROR_INVALID_PARAMETER = 401,

    /**
     * 通用内部错误
     */
    SCAN_ERROR_GENERIC_FAILURE = 24300101,

    /**
     * RPC通信错误
     */
    SCAN_ERROR_RPC_FAILURE = 24300102,

    /**
     * 服务器错误
     */
    SCAN_ERROR_SERVER_FAILURE = 24300103,

    /**
     * 不支持的操作
     */
    SCAN_ERROR_UNSUPPORTED = 24300104,

    /**
     * 操作已取消
     */
    SCAN_ERROR_CANCELED = 24300105,

    /**
     * 设备繁忙，请稍后重试
     */
    SCAN_ERROR_DEVICE_BUSY = 24300106,

    /**
     * 数据无效（包括打开时无设备）
     */
    SCAN_ERROR_INVALID = 24300107,

    /**
     * 文档进纸器卡纸
     */
    SCAN_ERROR_JAMMED = 24300108,

    /**
     * 文档进纸器缺纸
     */
    SCAN_ERROR_NO_DOCS = 24300109,

    /**
     * 扫描仪盖板打开
     */
    SCAN_ERROR_COVER_OPEN = 24300110,

    /**
     * 设备I/O错误
     */
    SCAN_ERROR_IO_ERROR = 24300111,

    /**
     * 内存不足
     */
    SCAN_ERROR_NO_MEMORY = 24300112
} Scan_ErrorCode;

/**
 * @brief 表示扫描仪设备信息
 *
 * @since 12
 */
typedef struct {
    /**
     * 扫描仪ID
     */
    const char *scannerId;
    /**
     * 扫描仪制造商
     */
    const char *manufacturer;
    /**
     * 扫描仪型号
     */
    const char *model;
    /**
     * 扫描仪发现模式
     */
    const char *discoverMode;
    /**
     * 扫描仪序列号
     */
    const char *serialNumber;
} Scan_ScannerDevice;

/**
 * @brief 表示扫描仪扫描图片的进度
 *
 * @since 12
 */
typedef struct {
    /**
     * 图片的扫描进度，从0到100，单位：百分比。
     */
    int32_t progress;
    /**
     * 扫描仪文件句柄
     */
    int32_t fd;
    /**
     * 指示该图像是否为最后扫描的图像。true表示该图像是最后扫描的图像，false表示该图像不是最后扫描的图像。
     */
    bool isFinal;
} Scan_PictureScanProgress;

/**
 * @brief 表示一个扫描仪的所有参数选项。
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
     * 可设置的参数选项数量
     */
    int32_t optionCount;
} Scan_ScannerOptions;

/**
 * @brief 扫描仪设备发现回调，通过{@link OH_Scan_StartScannerDiscovery}注册指针指向的内存将在回调函数结束时释放
 *
 * @param devices 所有发现的扫描仪设备列表
 * @param deviceCount 发现的扫描仪数量
 * @since 12
 */
typedef void (*Scan_ScannerDiscoveryCallback)(Scan_ScannerDevice** devices, int32_t deviceCount);

/**
 * @brief 此API检查并拉起扫描服务，初始化扫描客户端，并建立与扫描服务的连接
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
 * @brief 此API开始发现扫描仪，注册回调函数处理发现的扫描仪设备
 *
 * @permission {@code ohos.permission.PRINT}
 * @param callback 扫描仪发现事件的{@link Scan_ScannerDiscoveryCallback}回调函数
 * @return {@link SCAN_ERROR_NONE} 表示成功开始扫描仪搜索
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 * @since 12
 */
int32_t OH_Scan_StartScannerDiscovery(Scan_ScannerDiscoveryCallback callback);

/**
 * @brief 此API连接到扫描仪设备
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 用于连接扫描仪的ID
 * @return {@link SCAN_ERROR_NONE} 表示扫描仪成功连接
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 *     <br>{@link SCAN_ERROR_DEVICE_BUSY} 表示扫描仪繁忙
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER} 表示输入参数无效
 *     <br>{@link SCAN_ERROR_IO_ERROR} 表示与设备通信时发生错误
 *     <br>{@link SCAN_ERROR_NO_MEMORY} 表示可用内存不足
 * @since 12
 */
int32_t OH_Scan_OpenScanner(const char* scannerId);

/**
 * @brief 此API用于关闭已连接的扫描仪设备
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 用于断开扫描仪连接的ID
 * @return {@link SCAN_ERROR_NONE} 表示扫描仪连接成功关闭
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER} 表示输入参数无效
 * @since 12
 */
int32_t OH_Scan_CloseScanner(const char* scannerId);

/**
 * @brief 此API可用于获取扫描仪可设置的选项列表返回的结构体指针指向的内存会在{@link OH_Scan_Exit}时自动释放，每个型号在内存中只会存储一份副本
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 用于获取扫描仪参数的ID
 * @param errorCode 如果执行成功，errorCode返回{@link SCAN_ERROR_NONE}，否则返回特定的错误码，参考{@link Scan_ErrorCode}
 * @return 返回一个{@link Scan_ScannerOptions}实例对象的指针，如果创建失败则返回nullptr。
 * @since 12
 */
Scan_ScannerOptions* OH_Scan_GetScannerParameter(const char* scannerId, int32_t* errorCode);

/**
 * @brief 此API可用于设置扫描仪的某个选项参数传入的选项和值从{@link OH_Scan_GetScannerParameter}获取
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 此ID用于设置特定扫描仪的选项
 * @param option 要设置的选项编号。取值范围从0到 optionCount - 1，从{@link Scan_ScannerOptions}获取
 * @param value 要设置的选项值，有效值从ranges获取，从{@link Scan_ScannerOptions}获取
 * @return {@link SCAN_ERROR_NONE} 表示扫描仪参数设置成功
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER} 表示参数无效
 * @since 12
 */
int32_t OH_Scan_SetScannerParameter(const char* scannerId, const int32_t option, const char* value);

/**
 * @brief 此API允许扫描仪开始扫描
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 此ID用于启动指定扫描仪的扫描任务
 * @param batchMode 是否以批处理模式启动扫描仪
 * @return {@link SCAN_ERROR_NONE} 表示扫描仪成功启动扫描任务
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 *     <br>{@link SCAN_ERROR_JAMMED} 表示文档进纸器卡纸
 *     <br>{@link SCAN_ERROR_NO_DOCS} 表示文档进纸器缺纸
 *     <br>{@link SCAN_ERROR_COVER_OPEN} 表示扫描仪盖板打开
 *     <br>{@link SCAN_ERROR_IO_ERROR} 表示与设备通信时发生错误
 *     <br>{@link SCAN_ERROR_NO_MEMORY} 表示可用内存不足
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER} 表示输入参数无效
 *     <br>{@link SCAN_ERROR_DEVICE_BUSY} 表示设备繁忙，应稍后重试操作
 * @since 12
 */
int32_t OH_Scan_StartScan(const char* scannerId, bool batchMode);

/**
 * @brief 此API允许扫描仪取消扫描
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 此ID用于取消指定扫描仪的扫描任务
 * @return {@link SCAN_ERROR_NONE} 表示扫描仪成功取消扫描任务
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER} 表示指针为空或字符串为空
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 * @since 12
 */
int32_t OH_Scan_CancelScan(const char* scannerId);

/**
 * @brief 此API可获取扫描仪扫描图片的进度。必须传入非空值，扫描进度将写入指针指向的结构体
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId 用于查询扫描仪图像扫描进度的ID
 * @param prog 扫描图片的{@link Scan_PictureScanProgress}，必须为非空值
 * @return {@link SCAN_ERROR_NONE} 表示扫描仪成功查询到扫描图像的进度
 *     <br>{@link SCAN_ERROR_NO_PERMISSION} 表示无权限使用此接口
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER} 表示指针为空或字符串为空
 *     <br>{@link SCAN_ERROR_RPC_FAILURE} 表示RPC通信错误
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE} 表示扫描过程中发生错误
 *     <br>{@link SCAN_ERROR_JAMMED} 表示文档进纸器卡纸
 *     <br>{@link SCAN_ERROR_NO_DOCS} 表示文档进纸器缺纸
 *     <br>{@link SCAN_ERROR_COVER_OPEN} 表示扫描仪盖板打开
 *     <br>{@link SCAN_ERROR_IO_ERROR} 表示与扫描仪通信时发生错误
 *     <br>{@link SCAN_ERROR_NO_MEMORY} 表示可用内存不足
 *     <br>{@link SCAN_ERROR_DEVICE_BUSY} 表示设备繁忙，应稍后重试操作
 * @since 12
 */
int32_t OH_Scan_GetPictureScanProgress(const char* scannerId, Scan_PictureScanProgress* prog);

/**
 * @brief 此API可用于退出扫描服务，释放扫描框架内存，并注销扫描仪发现回调
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