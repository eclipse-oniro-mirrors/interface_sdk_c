/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup Print
 * @{
 *
 * @brief Provides the definition of the C interface for the print module.
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file ohprint.h
 *
 * @brief Declares APIs for discovering and connecting to printers, printing
 * files, and querying the list of added printers and printer information.
 *
 * @library libohprint.so
 * @kit BasicServicesKit
 * @syscap SystemCapability.Print.PrintFramework
 * @since 12
 * @version 1.0
 */

#ifndef OH_PRINT_H
#define OH_PRINT_H

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
     * 操作成功。
     */
    PRINT_ERROR_NONE = 0,
    /**
     * 权限校验失败。
     */
    PRINT_ERROR_NO_PERMISSION = 201,
    /**
     * 参数无效。
     */
    PRINT_ERROR_INVALID_PARAMETER = 401,
    /**
     * 通用内部错误。
     */
    PRINT_ERROR_GENERIC_FAILURE = 24300001,
    /**
     * RPC 通信错误。
     */
    PRINT_ERROR_RPC_FAILURE = 24300002,
    /**
     * 服务端错误。
     */
    PRINT_ERROR_SERVER_FAILURE = 24300003,
    /**
     * 无效的扩展。
     */
    PRINT_ERROR_INVALID_EXTENSION = 24300004,
    /**
     * 无效的打印机。
     */
    PRINT_ERROR_INVALID_PRINTER = 24300005,
    /**
     * 无效的打印任务。
     */
    PRINT_ERROR_INVALID_PRINT_JOB = 24300006,
    /**
     * 读写文件失败。
     */
    PRINT_ERROR_FILE_IO = 24300007,
    /**
     * 未知错误。
     */
    PRINT_ERROR_UNKNOWN = 24300255,
} Print_ErrorCode;

/**
 * @brief 表示打印机状态。
 *
 * @since 12
 */
typedef enum {
    /**
     * 打印机空闲。
     */
    PRINTER_IDLE,
    /**
     * 打印机忙。
     */
    PRINTER_BUSY,
    /**
     * 打印机不可用。
     */
    PRINTER_UNAVAILABLE,
} Print_PrinterState;

/**
 * @brief 表示打印机发现事件。
 *
 * @since 12
 */
typedef enum {
    /**
     * 发现打印机。
     */
    PRINTER_DISCOVERED = 0,
    /**
     * 丢失打印机。
     */
    PRINTER_LOST = 1,
    /**
     * 正在连接打印机。
     */
    PRINTER_CONNECTING = 2,
    /**
     * 打印机已连接。
     */
    PRINTER_CONNECTED = 3,
} Print_DiscoveryEvent;

/**
 * @brief 表示打印机变更事件。
 *
 * @since 12
 */
typedef enum {
    /**
     * 打印机已添加。
     */
    PRINTER_ADDED = 0,
    /**
     * 打印机已删除。
     */
    PRINTER_DELETED = 1,
    /**
     * 打印机状态已变更。
     */
    PRINTER_STATE_CHANGED = 2,
    /**
     * 打印机信息已变更。
     */
    PRINTER_INFO_CHANGED = 3,
} Print_PrinterEvent;

/**
 * @brief 表示字符串列表。
 *
 * @since 12
 */
typedef struct {
    /**
     * 字符串数量。
     */
    uint32_t count;
    /**
     * 字符串指针数组。
     */
    char **list;
} Print_StringList;

/**
 * @brief 表示打印机属性。
 *
 * @since 12
 */
typedef struct {
    /**
     * 属性关键字。
     */
    char *key;
    /**
     * 属性值。
     */
    char *value;
} Print_Property;

/**
 * @brief 打印机属性列表。
 *
 * @since 12
 */
typedef struct {
    /**
     * 属性数量。
     */
    uint32_t count;
    /**
     * 属性指针数组。
     */
    Print_Property *list;
} Print_PropertyList;

/**
 * @brief 表示以 dpi 为单位的打印分辨率。
 *
 * @since 12
 */
typedef struct {
    uint32_t horizontalDpi;
    uint32_t verticalDpi;
} Print_Resolution;

/**
 * @brief 表示打印边距。
 *
 * @since 12
 */
typedef struct {
    /**
     * 左边距，单位：毫米。
     */
    uint32_t leftMargin;
    /**
     * 上边距，单位：毫米。
     */
    uint32_t topMargin;
    /**
     * 右边距，单位：毫米。
     */
    uint32_t rightMargin;
    /**
     * 下边距，单位：毫米。
     */
    uint32_t bottomMargin;
} Print_Margin;

/**
 * @brief 表示纸张尺寸信息。
 *
 * @since 12
 */
typedef struct {
    /**
     * 纸张 ID。
     */
    char *id;
    /**
     * 纸张名称。
     */
    char *name;
    /**
     * 纸张宽度，单位：毫米。
     */
    uint32_t width;
    /**
     * 纸张高度，单位：毫米。
     */
    uint32_t height;
} Print_PageSize;

/**
 * @brief 表示双面打印模式。
 *
 * @since 12
 */
typedef enum {
    /**
     * 单面模式。
     */
    DUPLEX_MODE_ONE_SIDED = 0,
    /**
     * 长边翻转双面模式。
     */
    DUPLEX_MODE_TWO_SIDED_LONG_EDGE = 1,
    /**
     * 短边翻转双面模式。
     */
    DUPLEX_MODE_TWO_SIDED_SHORT_EDGE = 2,
} Print_DuplexMode;

/**
 * @brief 表示色彩模式。
 *
 * @since 12
 */
typedef enum {
    /**
     * 黑白模式。
     */
    COLOR_MODE_MONOCHROME = 0,
    /**
     * 彩色模式。
     */
    COLOR_MODE_COLOR = 1,
    /**
     * 自动模式。
     */
    COLOR_MODE_AUTO = 2,
} Print_ColorMode;

/**
 * @brief 表示方向模式。
 *
 * @since 12
 */
typedef enum {
    /**
     * 纵向模式。
     */
    ORIENTATION_MODE_PORTRAIT = 0,
    /**
     * 横向模式。
     */
    ORIENTATION_MODE_LANDSCAPE = 1,
    /**
     * 反向横向模式。
     */
    ORIENTATION_MODE_REVERSE_LANDSCAPE = 2,
    /**
     * 反向纵向模式。
     */
    ORIENTATION_MODE_REVERSE_PORTRAIT = 3,
    /**
     * 未指定。
     */
    ORIENTATION_MODE_NONE = 4,
} Print_OrientationMode;

/**
 * @brief 表示打印质量。
 *
 * @since 12
 */
typedef enum {
    /**
     * 草稿质量模式
     */
    PRINT_QUALITY_DRAFT = 3,
    /**
     * 正常质量模式
     */
    PRINT_QUALITY_NORMAL = 4,
    /**
     * 高质量模式
     */
    PRINT_QUALITY_HIGH = 5
} Print_Quality;

/**
 * @brief 表示文档的 MIME 媒体类型。
 *
 * @since 12
 */
typedef enum {
    /**
     * MIME 类型：application/octet-stream。
     */
    DOCUMENT_FORMAT_AUTO,
    /**
     * MIME 类型：image/jpeg。
     */
    DOCUMENT_FORMAT_JPEG,
    /**
     * MIME 类型：application/pdf。
     */
    DOCUMENT_FORMAT_PDF,
    /**
     * MIME 类型：application/postscript。
     */
    DOCUMENT_FORMAT_POSTSCRIPT,
    /**
     * MIME 类型：text/plain。
     */
    DOCUMENT_FORMAT_TEXT,
} Print_DocumentFormat;

/**
 * @brief 表示打印任务文档适配器状态。
 *
 * @since 13
 */
typedef enum {
    /**
     * 打印任务预览能力销毁。
     */
    PRINT_DOC_ADAPTER_PREVIEW_ABILITY_DESTROY = 0,
    /**
     * 打印任务成功。
     */
    PRINT_DOC_ADAPTER_PRINT_TASK_SUCCEED = 1,
    /**
     * 打印任务失败。
     */
    PRINT_DOC_ADAPTER_PRINT_TASK_FAIL = 2,
    /**
     * 打印任务取消。
     */
    PRINT_DOC_ADAPTER_PRINT_TASK_CANCEL = 3,
    /**
     * 打印任务阻塞。
     */
    PRINT_DOC_ADAPTER_PRINT_TASK_BLOCK = 4,
    /**
     * 因取消导致的打印任务预览能力销毁。
     */
    PRINT_DOC_ADAPTER_PREVIEW_ABILITY_DESTROY_FOR_CANCELED = 5,
    /**
     * 因启动导致的打印任务预览能力销毁。
     */
    PRINT_DOC_ADAPTER_PREVIEW_ABILITY_DESTROY_FOR_STARTED = 6,
} Print_JobDocAdapterState;

/**
 * @brief 表示打印机能力。
 *
 * @since 12
 */
typedef struct {
    /**
     * 支持的色彩模式数组。
     */
    Print_ColorMode *supportedColorModes;
    /**
     * 支持的色彩模式数量。
     */
    uint32_t supportedColorModesCount;
    /**
     * 支持的双面打印模式数组。
     */
    Print_DuplexMode *supportedDuplexModes;
    /**
     * 支持的双面打印模式数量。
     */
    uint32_t supportedDuplexModesCount;
    /**
     * 支持的纸张尺寸数组。
     */
    Print_PageSize *supportedPageSizes;
    /**
     * 支持的纸张尺寸数量。
     */
    uint32_t supportedPageSizesCount;
    /**
     * JSON 字符串数组格式的支持的打印介质类型。
     */
    char *supportedMediaTypes;
    /**
     * 支持的打印质量数组。
     */
    Print_Quality *supportedQualities;
    /**
     * 支持的打印质量数量。
     */
    uint32_t supportedQualitiesCount;
    /**
     * JSON 字符串数组格式的支持的纸张来源。
     */
    char *supportedPaperSources;
    /**
     * 支持的份数。
     */
    uint32_t supportedCopies;
    /**
     * 支持的打印机分辨率数组。
     */
    Print_Resolution *supportedResolutions;
    /**
     * 支持的打印机分辨率数量。
     */
    uint32_t supportedResolutionsCount;
    /**
     * 支持的方向数组。
     */
    Print_OrientationMode *supportedOrientations;
    /**
     * 支持的方向数量。
     */
    uint32_t supportedOrientationsCount;
    /**
     * JSON 格式的高级能力。
     */
    char *advancedCapability;
} Print_PrinterCapability;

/**
 * @brief 表示当前属性。
 *
 * @since 12
 */
typedef struct {
    /**
     * 默认色彩模式。
     */
    Print_ColorMode defaultColorMode;
    /**
     * 默认双面模式。
     */
    Print_DuplexMode defaultDuplexMode;
    /**
     * 默认介质类型。
     */
    char *defaultMediaType;
    /**
     * 默认纸张尺寸 ID。
     */
    char *defaultPageSizeId;
    /**
     * 默认边距。
     */
    Print_Margin defaultMargin;
    /**
     * 默认纸张来源。
     */
    char *defaultPaperSource;
    /**
     * 默认打印质量。
     */
    Print_Quality defaultPrintQuality;
    /**
     * 默认份数。
     */
    uint32_t defaultCopies;
    /**
     * 默认打印机分辨率。
     */
    Print_Resolution defaultResolution;
    /**
     * 默认方向。
     */
    Print_OrientationMode defaultOrientation;
    /**
     * JSON 格式的其他默认值。
     */
    char *otherDefaultValues;
} Print_DefaultValue;

/**
 * @brief 表示打印机信息。
 *
 * @since 12
 */
typedef struct {
    /**
     * 打印机状态。
     */
    Print_PrinterState printerState;
    /**
     * 打印机能力。
     */
    Print_PrinterCapability capability;
    /**
     * 打印机当前属性值。
     */
    Print_DefaultValue defaultValue;
    /**
     * 默认打印机
     */
    bool isDefaultPrinter;
    /**
     * 打印机 ID。
     */
    char *printerId;
    /**
     * 打印机名称。
     */
    char *printerName;
    /**
     * 打印机描述。
     */
    char *description;
    /**
     * 打印机位置。
     */
    char *location;
    /**
     * 打印机品牌和型号信息。
     */
    char *makeAndModel;
    /**
     * 打印机 URI。
     */
    char *printerUri;
    /**
     * JSON 格式的详细信息。
     * <br>支持的键包括：
     * <br>- **printerAlias**：string类型，表示打印机别名，**起始版本：** 24。
     * <br>- **vendorId**：int类型，表示usb打印机的vid，**起始版本：** 12。
     * <br>- **productId**：int类型，表示usb打印机的pid，**起始版本：** 12。
     * <br>- **protocol**：string数组，表示探测到的打印机支持的协议列表，**起始版本：** 24。
     * <br>- **ipp**：string类型，表示探测到的ipp协议对应的打印机URI，**起始版本：** 24。
     * <br>- **ipps**：string类型，表示探测到的ipps协议对应的打印机URI，**起始版本：** 24。
     * <br>- **lpd**：string类型，表示探测到的lpd协议对应的打印机URI，**起始版本：** 24。
     * <br>- **socket**：string类型，表示探测到的socket协议对应的打印机URI，**起始版本：** 24。
     */
    char *detailInfo;
} Print_PrinterInfo;

/**
 * @brief 表示打印机任务结构体。
 *
 * @since 12
 */
typedef struct {
    /**
     * 任务名称。
     */
    char *jobName;
    /**
     * 待打印的文件描述符数组。
     */
    uint32_t *fdList;
    /**
     * 待打印的文件描述符数量。
     */
    uint32_t fdListCount;
    /**
     * 打印机 ID。
     */
    char *printerId;
    /**
     * 打印份数。
     */
    uint32_t copyNumber;
    /**
     * 纸张来源。
     */
    char *paperSource;
    /**
     * 介质类型。
     */
    char *mediaType;
    /**
     * 纸张尺寸 ID。
     */
    char *pageSizeId;
    /**
     * 彩色模式。
     */
    Print_ColorMode colorMode;
    /**
     * 双面模式。
     */
    Print_DuplexMode duplexMode;
    /**
     * 以 dpi 为单位的打印分辨率。
     */
    Print_Resolution resolution;
    /**
     * 打印边距。
     */
    Print_Margin printMargin;
    /**
     * 无边距。
     */
    bool borderless;
    /**
     * 方向模式。
     */
    Print_OrientationMode orientationMode;
    /**
     * 打印质量。
     */
    Print_Quality printQuality;
    /**
     * 文档格式。
     */
    Print_DocumentFormat documentFormat;
    /**
     * JSON 格式的高级选项。<br>支持的键包括：<br>- **isReverseOrder**: 布尔类型, 表示是否逆序打印。<br>- **isCollate**: 布尔类型, 表示是否逐份打印。
     */
    char *advancedOptions;
} Print_PrintJob;

/**
 * @brief 表示打印范围结构体。
 *
 * @since 13
 */
typedef struct {
    /**
     * 打印起始页。
     */
    uint32_t startPage;
    /**
     * 打印结束页。
     */
    uint32_t endPage;
    /**
     * 打印页数组长度。
     */
    uint32_t pagesArrayLen;
    /**
     * 打印页数组。
     */
    uint32_t* pagesArray;
} Print_Range;

/**
 * @brief 表示打印属性结构体。
 *
 * @since 13
 */
typedef struct {
    /**
     * 打印范围。
     */
    Print_Range pageRange;
    /**
     *打印纸张尺寸。
     */
    Print_PageSize pageSize;
    /**
     * 打印边距。
     */
    Print_Margin pageMargin;
    /**
     * 份数。
     */
    uint32_t copyNumber;
    /**
     * 双面模式。
     */
    uint32_t duplexMode;
    /**
     * 色彩模式。
     */
    uint32_t colorMode;
    /**
     * 顺序打印。<br>true表示顺序打印，false表示逆序打印。
     */
    bool isSequential;
    /**
     * 打印方向（是否横向）。<br>true表示打印方式为横向，false表示打印方向为竖向。
     */
    bool isLandscape;
    /**
     * 打印选项标志。<br>true表示有打印选项，false表示没有打印选项。
     */
    bool hasOption;
    /**
     * 打印选项。
     */
    char options[256];
} Print_PrintAttributes;

/**
 * @brief 写文件结果回调。
 *
 * @param jobId 打印任务的 ID。
 * @param code 写文件的结果。
 * @since 13
 */
typedef void(*Print_WriteResultCallback)(const char *jobId, uint32_t code);

/**
 * @brief 打印开始布局回调。
 *
 * @param jobId 打印任务的 ID。
 * @param fd 待写入的文件描述符。
 * @param oldAttrs 上一次的属性。
 * @param newAttrs 当前的属性。
 * @param writeCallback 写文件结果回调。
 * @since 13
 */
typedef void(*Print_OnStartLayoutWrite)(const char *jobId,
                                        uint32_t fd,
                                        const Print_PrintAttributes *oldAttrs,
                                        const Print_PrintAttributes *newAttrs,
                                        Print_WriteResultCallback writeCallback);

/**
 * @brief 打印任务状态回调。
 *
 * @param jobId 打印任务的 ID。
 * @param state 当前打印任务的状态。
 * @since 13
 */
typedef void(*Print_OnJobStateChanged)(const char *jobId, uint32_t state);

/**
 * @brief 表示打印文档状态回调结构体。
 *
 * @since 13
 */
typedef struct {
    /**
     * 打印开始布局回调。
     */
    Print_OnStartLayoutWrite startLayoutWriteCb;
    /**
     * 打印任务状态回调。
     */
    Print_OnJobStateChanged jobStateChangedCb;
} Print_PrintDocCallback;

/**
 * @brief 打印机发现回调。
 *
 * @param event 打印机发现过程中的发现事件。
 * @param printerInfo 发现事件发生时的打印机信息。
 * @since 12
 */
typedef void (*Print_PrinterDiscoveryCallback)(Print_DiscoveryEvent event, const Print_PrinterInfo *printerInfo);

/**
 * @brief 打印机变更回调。
 *
 * @param event 打印服务运行期间的打印机变更事件。
 * @param printerInfo 变更事件发生时的打印机信息。
 * @since 12
 */
typedef void (*Print_PrinterChangeCallback)(Print_PrinterEvent event, const Print_PrinterInfo *printerInfo);

/**
 * @brief 此 API 检查并拉起打印服务，初始化打印客户端，并建立与打印服务的连接。
 *
 * @permission {@code ohos.permission.PRINT}
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 ohos.permission.PRINT 权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE} cups 服务无法启动。
 * @since 12
 */
Print_ErrorCode OH_Print_Init();

/**
 * @brief 此 API 关闭与打印服务的连接，解散先前的回调，并释放打印客户端资源。
 *
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>当前不会返回其他错误码。
 * @since 12
 */
Print_ErrorCode OH_Print_Release();

/**
 * @brief 此 API 开始发现打印机。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param callback 打印机发现事件的 {@link Print_PrinterDiscoveryCallback}。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 ohos.permission.PRINT 权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE} 从 BMS 查询打印扩展列表失败。
 *     <br>{@link PRINT_ERROR_INVALID_EXTENSION} 未找到可用的打印扩展。
 * @since 12
 */
Print_ErrorCode OH_Print_StartPrinterDiscovery(Print_PrinterDiscoveryCallback callback);

/**
 * @brief 此 API 停止发现打印机。
 *
 * @permission {@code ohos.permission.PRINT}
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 ohos.permission.PRINT 权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 * @since 12
 */
Print_ErrorCode OH_Print_StopPrinterDiscovery();

/**
 * @brief 此 API 使用打印机 ID 连接打印机。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId 待连接的打印机 ID。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 ohos.permission.PRINT 权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER} 打印机应在已发现的打印机列表中。
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE} 无法找到负责该打印机的扩展。
 * @since 12
 */
Print_ErrorCode OH_Print_ConnectPrinter(const char *printerId);

/**
 * @brief 此 API 开始发起打印任务。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printJob 指向指定打印任务信息的 {@link Print_PrintJob} 实例的指针。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 ohos.permission.PRINT 权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER} 打印机应在已连接的打印机列表中。
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE} 无法在打印服务中创建打印任务。
 *     <br>{@link PRINT_ERROR_INVALID_PRINT_JOB} 无法在任务队列中找到该任务。
 * @since 12
 */
Print_ErrorCode OH_Print_StartPrintJob(const Print_PrintJob *printJob);

/**
 * @brief 此 API 注册打印机变更回调。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param callback 待注册的 {@link Print_PrinterChangeCallback}。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 ohos.permission.PRINT 权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务能力。
 * @since 12
 */
Print_ErrorCode OH_Print_RegisterPrinterChangeListener(Print_PrinterChangeCallback callback);

/**
 * @brief 此 API 注销打印机变更回调。
 *
 * @permission {@code ohos.permission.PRINT}
 * @since 12
 */
void OH_Print_UnregisterPrinterChangeListener();

/**
 * @brief 此 API 查询已添加的打印机列表。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerIdList 用于存储查询到的打印机 ID 列表的 {@link Print_StringList} 实例指针。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 ohos.permission.PRINT 权限。
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER} printerIdList 为 NULL。
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER} 无法查询任何已连接的打印机。
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE} 无法复制打印机 ID 列表。
 * @since 12
 */
Print_ErrorCode OH_Print_QueryPrinterList(Print_StringList *printerIdList);

/**
 * @brief 此 API 释放用于查询的打印机列表内存。
 *
 * @param printerIdList 待释放的已查询打印机 ID 列表。
 * @since 12
 */
void OH_Print_ReleasePrinterList(Print_StringList *printerIdList);

/**
 * @brief 此 API 根据打印机 ID 查询打印机信息。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId 待查询的打印机 ID。
 * @param printerInfo 用于存储打印机信息的 {@link Print_PrinterInfo} 指针的指针。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 ohos.permission.PRINT 权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER} printerId 为 NULL 或 printerInfo 为 NULL。
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER} 无法在已连接的打印机列表中找到该打印机。
 * @since 12
 */
Print_ErrorCode OH_Print_QueryPrinterInfo(const char *printerId, Print_PrinterInfo **printerInfo);

/**
 * @brief 此 API 释放用于查询的打印机信息内存。
 *
 * @param printerInfo 待释放的已查询打印机信息指针。
 * @since 12
 */
void OH_Print_ReleasePrinterInfo(Print_PrinterInfo *printerInfo);

/**
 * @brief 此 API 启动系统的打印机管理窗口。
 *
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE} 无法启动打印机管理窗口。
 * @since 12
 */
Print_ErrorCode OH_Print_LaunchPrinterManager();

/**
 * @brief 此 API 根据属性关键字列表查询对应的打印机属性值。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId 待查询的打印机 ID。
 * @param propertyKeyList 待查询的属性关键字列表。
 * @param propertyList 查询到的打印机属性值列表。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 ohos.permission.PRINT 权限。
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER} 参数之一为 NULL 或关键字列表为空。
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER} 无法找到指定打印机的属性。
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE} 无法复制打印机属性。
 * @since 12
 */
Print_ErrorCode OH_Print_QueryPrinterProperties(const char *printerId, const Print_StringList *propertyKeyList,
    Print_PropertyList *propertyList);

/**
 * @brief 此 API 释放用于查询的属性列表内存。
 *
 * @param propertyList 待释放的已查询打印机属性值指针。
 * @since 12
 */
void OH_Print_ReleasePrinterProperties(Print_PropertyList *propertyList);

/**
 * @brief 此 API 根据属性键值对列表设置打印机属性。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId 待设置的打印机 ID。
 * @param propertyList 待设置的打印机属性值列表。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 ohos.permission.PRINT 权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 * @since 12
 */
Print_ErrorCode OH_Print_UpdatePrinterProperties(const char *printerId, const Print_PropertyList *propertyList);

/**
 * @brief 此 API 根据属性关键字列表将打印机属性恢复为默认设置。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId 待恢复的打印机 ID。
 * @param propertyKeyList 待恢复的属性关键字列表。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 ohos.permission.PRINT 权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 * @since 12
 */
Print_ErrorCode OH_Print_RestorePrinterProperties(const char *printerId, const Print_StringList *propertyKeyList);

/**
 * @brief 此 API 提供启动打印对话框的能力。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printJobName 此打印任务的名称。
 * @param printDocCallback 打印文档状态回调。
 * @param context 调用方应用的上下文。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 ohos.permission.PRINT 权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 * @since 13
 */
Print_ErrorCode OH_Print_StartPrintByNative(const char *printJobName,
                                            Print_PrintDocCallback printDocCallback,
                                            void *context);

/**
 * @brief 表示打印任务状态。
 *
 * @since 24
 */
typedef enum {
    /**
     * 打印任务成功。
     */
    OH_PRINT_JOB_SUCCEED = 0,
    /**
     * 打印任务失败。
     */
    OH_PRINT_JOB_FAIL = 1,
    /**
     * 打印任务取消。
     */
    OH_PRINT_JOB_CANCEL = 2,
    /**
     * 打印任务阻塞。
     */
    OH_PRINT_JOB_BLOCK = 3,
} OH_Print_JobState;

/**
 * @brief 打印任务状态回调。
 *
 * @param jobId 打印任务的 ID。
 * @param state 当前打印任务的状态。
 * @since 24
 */
typedef void(*OH_Print_OnJobStateChanged)(const char *jobId, OH_Print_JobState state);

/**
 * @brief 此API下发打印任务，并附带任务状态变更回调功能。
 *
 * @permission ohos.permission.PRINT
 * @param printJob 打印任务结构体。
 * @param jobStateChangedCb 打印任务状态回调。
 * @return {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 表示需要 {@link ohos.permission.PRINT} 权限。
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER} jobStateChangedCb为NULL。
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE} 表示无法复制回调函数。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 表示无法连接到打印服务。
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE} 表示打印服务中无法创建打印任务结构体。
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER} 无法在已连接的打印机列表中找到该打印机。
 *     <br>{@link PRINT_ERROR_INVALID_PRINT_JOB} 表示无法在任务队列中找到该任务。
 * @since 24
 */
Print_ErrorCode OH_Print_StartPrintWithJobStateCallback(const Print_PrintJob *printJob,
                                                        OH_Print_OnJobStateChanged jobStateChangedCb);

#ifdef __cplusplus
}
#endif

#endif // OH_PRINT_H
/** @} */