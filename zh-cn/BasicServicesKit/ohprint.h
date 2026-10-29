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
 * @brief 声明用于发现和连接打印机、通过打印机打印文件、查询已添加打印机列表及其内部打印机信息等功能的API。适用于需要在应用内集成打印能力的场景，帮助开发者便捷地实现打印机发现、连接、任务下发及状态监控等打印流程管理。
 *
 * @library libohprint.so
 * @kit BasicServicesKit
 * @syscap SystemCapability.Print.PrintFramework
 * @include <ohprint.h>
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
     * 权限校验失败，请确认已在应用配置中声明对应的权限。
     */
    PRINT_ERROR_NO_PERMISSION = 201,
    /**
     * 参数无效，请检查传入参数的类型和取值范围。
     */
    PRINT_ERROR_INVALID_PARAMETER = 401,
    /**
     * 通用内部错误，请检查打印服务运行状态后重试。
     */
    PRINT_ERROR_GENERIC_FAILURE = 24300001,
    /**
     * RPC通信错误，请确认打印服务已正常启动后重试。
     */
    PRINT_ERROR_RPC_FAILURE = 24300002,
    /**
     * 服务端错误，请检查打印服务运行状态。
     */
    PRINT_ERROR_SERVER_FAILURE = 24300003,
    /**
     * 无效的扩展，请确认已安装有效的打印扩展。
     */
    PRINT_ERROR_INVALID_EXTENSION = 24300004,
    /**
     * 无效的打印机，请确认打印机已在已发现或已连接的打印机列表中。
     */
    PRINT_ERROR_INVALID_PRINTER = 24300005,
    /**
     * 无效的打印任务，请确认打印任务信息完整且打印机已连接。
     */
    PRINT_ERROR_INVALID_PRINT_JOB = 24300006,
    /**
     * 读写文件失败，请检查文件路径及访问权限。
     */
    PRINT_ERROR_FILE_IO = 24300007,
    /**
     * 未知错误，请检查打印服务状态后重试，若问题持续请联系技术支持。
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
 * @brief 表示字符串列表，用于在打印模块中传递多个字符串数据。该结构体通过count字段记录字符串数量、list字段指向字符串数组，适用于需要批量传递多个字符串数据的场景。相关接口请参见{@link OH_Print}。
 *
 * @since 12
 */
typedef struct {
    /**
     * 字符串数量，表示list数组中的元素数量。
     */
    uint32_t count;
    /**
     * 指向字符串数组的指针，数组元素数量须与count值一致。
     */
    char **list;
} Print_StringList;

/**
 * @brief Print_Property表示打印机属性，以键值对形式描述打印机的各类属性信息，开发者可通过该结构体获取或设置打印机的属性参数。
 *
 * @since 12
 */
typedef struct {
    /**
     * 属性键，用于标识打印机属性的类型，取值须为{@link OH_Print}模块定义的有效属性名称。
     */
    char *key;
    /**
     * 属性值，与属性键key对应的值内容，其格式和有效范围取决于对应的属性键。
     */
    char *value;
} Print_Property;

/**
 * @brief 打印机属性列表，用于存储和管理打印机属性，支持通过属性数量和属性数组的指针对打印机属性进行批量访问和操作。其中count表示属性数量，list为指向属性数组的指针，两者配合表示一组完整的打印机属性，
 * 适用于需要查询或设置打印机多项属性信息的场景。
 *
 * @since 12
 */
typedef struct {
    /**
     * 属性数量。与list指向的属性数组实际元素数一致。
     */
    uint32_t count;
    /**
     * 指向属性数组的指针，用于存储打印机属性信息。须与count配合使用，数组长度由count指定。
     */
    Print_Property *list;
} Print_PropertyList;

/**
 * @brief Print_Resolution用于表示以dpi为单位的打印分辨率，可控制打印输出的精细度与质量。
 *
 * @since 12
 */
typedef struct {
    uint32_t horizontalDpi;
    uint32_t verticalDpi;
} Print_Resolution;

/**
 * @brief Print_Margin用于表示打印页面的边距信息，支持设置左、上、右、下四个方向的边距，控制可打印内容区域。适用于需要在打印时精确控制内容与纸张边缘距离的场景，通过合理配置边距可以避免内容溢出或被裁剪。
 *
 * @since 12
 */
typedef struct {
    /**
     * 左边距，单位：毫米。取值原则：大于0。
     */
    uint32_t leftMargin;
    /**
     * 上边距，单位：毫米。取值原则：大于0。
     */
    uint32_t topMargin;
    /**
     * 右边距，单位：毫米。取值原则：大于0。
     */
    uint32_t rightMargin;
    /**
     * 下边距，单位：毫米。取值原则：大于0。
     */
    uint32_t bottomMargin;
} Print_Margin;

/**
 * @brief Print_PageSize用于表示打印任务中的纸张尺寸信息，包含纸张ID、名称、宽度与高度等关键属性，适用于需要在打印配置流程中指定或查询纸张规格的场景。
 *
 * @since 12
 */
typedef struct {
    /**
     * 纸张尺寸的唯一标识ID，用于区分不同标准纸张规格。
     */
    char *id;
    /**
     * 纸张尺寸的名称，如"A4"、"Letter"等标准纸张规格。
     */
    char *name;
    /**
     * 纸张宽度，单位：密尔（千分之一英寸）。取值原则：大于0。
     */
    uint32_t width;
    /**
     * 纸张高度，单位：密尔（千分之一英寸）。取值原则：大于0。
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
     * 草稿质量模式。
     */
    PRINT_QUALITY_DRAFT = 3,
    /**
     * 正常质量模式。
     */
    PRINT_QUALITY_NORMAL = 4,
    /**
     * 高质量模式。
     */
    PRINT_QUALITY_HIGH = 5
} Print_Quality;

/**
 * @brief 表示文档的MIME媒体类型。
 *
 * @since 12
 */
typedef enum {
    /**
     * MIME类型：application/octet-stream。
     */
    DOCUMENT_FORMAT_AUTO,
    /**
     * MIME类型：image/jpeg。
     */
    DOCUMENT_FORMAT_JPEG,
    /**
     * MIME类型：application/pdf。
     */
    DOCUMENT_FORMAT_PDF,
    /**
     * MIME类型：application/postscript。
     */
    DOCUMENT_FORMAT_POSTSCRIPT,
    /**
     * MIME类型：text/plain。
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
 * @brief 表示打印机能力，包含支持的色彩模式、双面打印模式、纸张尺寸、介质类型、打印质量、纸张来源、份数、分辨率、打印方向模式及高级能力等属性，适用于需要查询或匹配打印机能力的场景，帮助开发者根据打印机能力进行打印任务配置和适配。
 *
 * @since 12
 */
typedef struct {
    /**
     * 支持的色彩模式数组，数组长度由supportedColorModesCount决定。
     */
    Print_ColorMode *supportedColorModes;
    /**
     * 支持的色彩模式数量，与supportedColorModes数组实际元素数一致。
     */
    uint32_t supportedColorModesCount;
    /**
     * 支持的双面打印模式数组，数组长度由supportedDuplexModesCount决定。
     */
    Print_DuplexMode *supportedDuplexModes;
    /**
     * 支持的双面打印模式数量，与supportedDuplexModes数组实际元素数一致。
     */
    uint32_t supportedDuplexModesCount;
    /**
     * 支持的打印纸张尺寸数组，数组长度由supportedPageSizesCount决定。
     */
    Print_PageSize *supportedPageSizes;
    /**
     * 支持的打印纸张尺寸数量，与supportedPageSizes数组实际元素数一致。
     */
    uint32_t supportedPageSizesCount;
    /**
     * 支持的打印介质类型，以JSON数组格式字符串表示，具体取值由打印机决定。
     */
    char *supportedMediaTypes;
    /**
     * 支持的打印质量数组，数组长度由supportedQualitiesCount决定。
     */
    Print_Quality *supportedQualities;
    /**
     * 支持的打印质量数量，与supportedQualities数组实际元素数一致。
     */
    uint32_t supportedQualitiesCount;
    /**
     * 支持的纸张来源，以JSON数组格式字符串表示，具体取值由打印机决定。
     */
    char *supportedPaperSources;
    /**
     * 支持的份数，取值由打印机能力决定。
     */
    uint32_t supportedCopies;
    /**
     * 支持的打印机分辨率数组，数组长度由supportedResolutionsCount决定。
     */
    Print_Resolution *supportedResolutions;
    /**
     * 支持的打印机分辨率数量，与supportedResolutions数组实际元素数一致。
     */
    uint32_t supportedResolutionsCount;
    /**
     * 支持的打印方向模式数组，数组长度由supportedOrientationsCount决定。
     */
    Print_OrientationMode *supportedOrientations;
    /**
     * 支持的打印方向模式数量，与supportedOrientations数组实际元素数一致。
     */
    uint32_t supportedOrientationsCount;
    /**
     * 高级能力，以JSON对象格式字符串表示，用于描述不属于上述标准能力字段的打印机特性，JSON对象的具体字段名和取值由打印机决定，开发者需根据实际返回的JSON内容进行解析。
     */
    char *advancedCapability;
} Print_PrinterCapability;

/**
 * @brief 表示打印机的默认属性值，包含色彩模式、双面模式、介质类型、纸张尺寸、边距、纸张来源、打印质量、份数、分辨率、方向等默认打印参数。
 *
 * @since 12
 */
typedef struct {
    /**
     * 默认色彩模式，表示打印输出的色彩方式，具体取值由打印机支持的色彩模式决定。
     */
    Print_ColorMode defaultColorMode;
    /**
     * 默认双面模式，表示打印的单双面方式，具体取值由打印机支持的双面模式决定。
     */
    Print_DuplexMode defaultDuplexMode;
    /**
     * 默认介质类型，表示打印所使用的介质类型（如普通纸、光面纸等），具体取值由打印机支持的介质类型决定。
     */
    char *defaultMediaType;
    /**
     * 默认纸张尺寸ID，表示打印所使用的纸张尺寸标识（如"A4"、"Letter"等），具体取值由打印机支持的纸张尺寸决定。
     */
    char *defaultPageSizeId;
    /**
     * 默认边距，表示打印输出页面的边距设置，具体取值由打印机支持的边距决定。
     */
    Print_Margin defaultMargin;
    /**
     * 默认纸张来源，表示打印所使用的纸张来源（如自动进纸器、手动进纸等），具体取值由打印机支持的纸张来源决定。
     */
    char *defaultPaperSource;
    /**
     * 默认打印质量，表示打印输出的质量等级设置，具体取值由打印机支持的打印质量决定。
     */
    Print_Quality defaultPrintQuality;
    /**
     * 默认份数，取值原则：不小于1。
     */
    uint32_t defaultCopies;
    /**
     * 默认分辨率，表示打印输出的分辨率，具体取值由打印机支持的分辨率决定。
     */
    Print_Resolution defaultResolution;
    /**
     * 默认打印方向，表示打印内容的方向模式（如纵向、横向等），具体取值由打印机支持的打印方向决定。
     */
    Print_OrientationMode defaultOrientation;
    /**
     * JSON格式的其他默认值，用于表示未在上述成员变量中单独列出的额外打印默认属性，具体可设置的键值对由打印机支持的扩展能力决定。
     */
    char *otherDefaultValues;
} Print_DefaultValue;

/**
 * @brief Print_PrinterInfo表示打印机信息，包含打印机的状态、能力、默认属性以及标识信息（如打印机ID、名称、描述、位置、品牌型号、URI等），适用于应用在打印场景中获取和展示打印机详细信息的场景，
 * 帮助开发者根据打印机能力与属性选择合适的打印设备。可通过 {@link OH_Print_StartPrinterDiscovery} 或 {@link OH_Print_QueryPrinterInfo} 获取。
 *
 * @since 12
 */
typedef struct {
    /**
     * 打印机的当前运行状态。
     */
    Print_PrinterState printerState;
    /**
     * 打印机支持的能力集合，如支持的纸张尺寸、色彩模式等。
     */
    Print_PrinterCapability capability;
    /**
     * 打印机默认属性，如默认纸张尺寸、色彩模式等。
     */
    Print_DefaultValue defaultValue;
    /**
     * 是否为默认打印机。true表示是默认打印机，false表示不是默认打印机。
     */
    bool isDefaultPrinter;
    /**
     * 打印机ID。
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
     * 打印机URI，用于定位和访问打印机。格式形如scheme://[user@]host[:port]/resource。
     */
    char *printerUri;
    /**
     * JSON格式的详细信息。
     * <br>支持的键包括：
     * <br>- **printerAlias**：string类型，表示打印机别名，**起始版本：** 24。
     * <br>- **vendorId**：int类型，表示USB打印机的VID，取值范围 [0, 65535]，**起始版本：** 12。
     * <br>- **productId**：int类型，表示USB打印机的PID，取值范围 [0, 65535]，**起始版本：** 12。
     * <br>- **protocol**：string数组，表示探测到的打印机支持的协议列表，取值包括ipp、ipps、lpd、socket，**起始版本：** 24。
     * <br>- **ipp**：string类型，表示探测到的IPP协议对应的打印机URI，**起始版本：** 24。
     * <br>- **ipps**：string类型，表示探测到的IPPS协议对应的打印机URI，**起始版本：** 24。
     * <br>- **lpd**：string类型，表示探测到的LPD协议对应的打印机URI，**起始版本：** 24。
     * <br>- **socket**：string类型，表示探测到的Socket协议对应的打印机URI，**起始版本：** 24。
     */
    char *detailInfo;
} Print_PrinterInfo;

/**
 * @brief 表示打印任务结构体，用于配置打印任务的各项属性参数（如打印份数、纸张来源、色彩模式、双面模式、分辨率、边距、方向模式、打印质量、文档格式及高级选项等）。开发者通过填充该结构体并向打印模块接口提交以发起打印任务。
 *
 * @since 12
 */
typedef struct {
    /**
     * 任务名称，用于标识和区分不同的打印任务。
     */
    char *jobName;
    /**
     * 待打印的文件描述符数组。需与fdListCount配合使用，fdListCount应等于该数组的元素数量。
     */
    uint32_t *fdList;
    /**
     * 待打印的文件描述符数量。取值原则：大于等于1，且需与fdList数组长度一致。
     */
    uint32_t fdListCount;
    /**
     * 打印机ID。
     */
    char *printerId;
    /**
     * 打印份数。取值原则：大于等于1。
     */
    uint32_t copyNumber;
    /**
     * 纸张来源，用于指定打印纸张的进纸方式。具体可选取值取决于打印机支持的纸张来源选项。
     */
    char *paperSource;
    /**
     * 介质类型，用于指定打印介质的种类，如普通纸、光面纸、照片纸等。具体可选取值取决于打印机支持的介质类型选项。
     */
    char *mediaType;
    /**
     * 纸张尺寸ID，用于指定打印纸张的尺寸规格，如ISO A4、Letter、A3等。具体可选取值取决于打印机支持的尺寸选项。
     */
    char *pageSizeId;
    /**
     * 彩色模式。
     */
    Print_ColorMode colorMode;
    /**
     * 双面模式。单面模式适合单面打印需求，长边翻转双面适合纵向翻页文档（如书籍），短边翻转双面适合横向翻页文档（如日历）。
     */
    Print_DuplexMode duplexMode;
    /**
     * 以dpi为单位的打印分辨率。高分辨率适合图片等精细内容，较低分辨率适合纯文本或草稿打印以节省耗材与打印时间。
     */
    Print_Resolution resolution;
    /**
     * 以毫米为单位的打印边距。建议根据文档类型和打印机支持的最小边距合理设置，过小的边距可能导致打印内容被裁切。
     */
    Print_Margin printMargin;
    /**
     * 是否无边距打印。true表示无边距打印，false表示有边距打印。
     */
    bool borderless;
    /**
     * 方向模式。纵向模式适合常规文档打印，横向模式适合表格、图表等宽幅内容，反向横向模式适合需要镜像翻转的横向内容，反向纵向模式适合需要镜像翻转的纵向内容，未指定表示由系统自动选择方向。
     */
    Print_OrientationMode orientationMode;
    /**
     * 打印质量。高质量模式适合最终输出或正式文档，正常模式适合日常打印，草稿模式适合快速预览以节省耗材。
     */
    Print_Quality printQuality;
    /**
     * 文档的MIME媒体类型，如PDF（application/pdf）、JPEG（image/jpeg）等。
     */
    Print_DocumentFormat documentFormat;
    /**
     * @brief JSON格式的高级选项。
     * <br>支持的键为以下几种：
     * <br>- **isReverse**：布尔类型，表示是否逆序打印。
     * <br>- **isCollate**：布尔类型，表示是否逐份打印。
     * <br>- **printPages**：整数类型，表示实际打印的页数。取值必须大于等于1，默认值为1。
     */
    char *advancedOptions;
} Print_PrintJob;

/**
 * @brief 表示打印范围结构体，用于指定打印任务中的页码范围。可通过startPage和endPage指定连续页码范围，或通过pagesArray和pagesArrayLen指定不连续的打印页码数组。
 *
 * @since 13
 */
typedef struct {
    /**
     * 打印起始页，页码从1开始计数，取值应为文档中的有效页码且需小于等于endPage。
     */
    uint32_t startPage;
    /**
     * 打印结束页，页码从1开始计数，取值应为文档中的有效页码且需大于等于startPage。
     */
    uint32_t endPage;
    /**
     * 打印页码数组长度，须与pagesArray数组实际元素数一致，仅在pagesArray不为NULL时有效。
     */
    uint32_t pagesArrayLen;
    /**
     * 打印页码数组，每个元素表示一个需要打印的页码，页码从1开始计数，取值应为文档中的有效页码，数组长度由pagesArrayLen决定。
     */
    uint32_t *pagesArray;
} Print_Range;

/**
 * @brief 表示打印属性结构体，用于配置打印任务的各项属性（如打印范围、纸张尺寸、边距、份数、双面模式、色彩模式、打印方向及打印选项等），适用于需要对打印输出进行精细化控制的场景。
 *
 * @since 13
 */
typedef struct {
    /**
     * 打印范围。
     */
    Print_Range pageRange;
    /**
     * 打印纸张尺寸。
     */
    Print_PageSize pageSize;
    /**
     * 以毫米为单位的打印边距。建议根据文档类型和打印机支持的最小边距合理设置，过小的边距可能导致打印内容被裁切。
     */
    Print_Margin pageMargin;
    /**
     * 打印份数。取值原则：大于等于1。
     */
    uint32_t copyNumber;
    /**
     * 双面模式。单面模式适合单面打印需求，长边翻转双面适合纵向翻页文档（如书籍），短边翻转双面适合横向翻页文档（如日历）。
     */
    uint32_t duplexMode;
    /**
     * 彩色模式。
     */
    uint32_t colorMode;
    /**
     * 顺序打印。<br>true表示顺序打印，false表示逆序打印。
     */
    bool isSequential;
    /**
     * 打印方向（是否横向）。<br>true表示打印方向为横向，false表示打印方向为纵向。
     */
    bool isLandscape;
    /**
     * 打印选项标志。<br>true表示有打印选项（options字段有效），false表示没有打印选项（options字段无效）。
     */
    bool hasOption;
    /**
     * 打印选项，用于传递额外的打印配置参数。仅在hasOption为true时生效，最大长度255个字符。
     */
    char options[256];
} Print_PrintAttributes;

/**
 * @brief 写文件结果回调。
 *
 * @param jobId 打印任务的ID。
 * @param code 写文件的结果。0表示文件创建成功；1表示文件创建失败；2表示文件创建成功但未渲染。
 * @since 13
 */
typedef void(*Print_WriteResultCallback)(const char *jobId, uint32_t code);

/**
 * @brief 打印开始布局回调。
 *
 * @param jobId 打印任务的ID。
 * @param fd 待写入的文件描述符。
 * @param oldAttrs 上一次打印任务的打印属性。
 * @param newAttrs 当前打印任务的打印属性。
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
 * @param jobId 打印任务的ID。
 * @param state 当前打印任务的状态，取值及各状态含义可参考 {@link OH_Print_JobState} 枚举。
 * @since 13
 */
typedef void(*Print_OnJobStateChanged)(const char *jobId, uint32_t state);

/**
 * @brief 表示打印文档回调结构体。用于C/C++原生应用向打印框架提供文件生成和任务状态接收能力。
 *
 * @since 13
 */
typedef struct {
    /**
     * 打印开始布局写入回调。当打印任务开始布局时，系统将调用此回调函数，要求应用写入打印文件内容。
     */
    Print_OnStartLayoutWrite startLayoutWriteCb;
    /**
     * 打印任务状态变化回调。当打印任务状态发生变化时，系统将调用此回调函数通知应用打印任务状态变更。
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
 * @brief 此API用于检查并拉起打印服务，初始化打印客户端，并建立与打印服务的连接。调用其它打印API前，必须先调用此方法完成初始化，否则将因打印服务连接未建立而导致其他API无法正常工作。在使用完毕后，
 * 需调用OH_Print_Release()关闭连接并释放打印客户端资源，否则会导致打印服务连接未关闭及客户端资源泄漏。
 *
 * @permission {@code ohos.permission.PRINT}
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要ohos.permission.PRINT权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE} cups服务无法启动。
 * @since 12
 */
Print_ErrorCode OH_Print_Init();

/**
 * @brief 此API用于关闭与打印服务的连接，注销所有已注册的回调，并释放打印客户端资源。
 *
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>当前不会返回其他错误码。
 * @since 12
 */
Print_ErrorCode OH_Print_Release();

/**
 * @brief 此API用于开始发现打印机。发现过程中，可通过传入的Print_PrinterDiscoveryCallback回调通知打印机发现事件和获取Print_PrinterInfo打印机信息。
 * 完成发现后可调用OH_Print_StopPrinterDiscovery()停止发现流程，否则导致发现流程持续运行，消耗系统资源。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param callback 打印机发现事件的 {@link Print_PrinterDiscoveryCallback}。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要ohos.permission.PRINT权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE} 从BMS查询打印扩展列表失败。
 *     <br>{@link PRINT_ERROR_INVALID_EXTENSION} 未找到可用的打印扩展。
 * @since 12
 */
Print_ErrorCode OH_Print_StartPrinterDiscovery(Print_PrinterDiscoveryCallback callback);

/**
 * @brief 此API用于停止发现打印机。
 *
 * @permission {@code ohos.permission.PRINT}
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要ohos.permission.PRINT权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 * @since 12
 */
Print_ErrorCode OH_Print_StopPrinterDiscovery();

/**
 * @brief 此API用于使用打印机ID连接打印机。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId 待连接的打印机ID，应为已发现的打印机列表中的打印机，不能为NULL。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要ohos.permission.PRINT权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER} 打印机应在已发现的打印机列表中。
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE} 无法找到负责该打印机的扩展。
 * @since 12
 */
Print_ErrorCode OH_Print_ConnectPrinter(const char *printerId);

/**
 * @brief 此API用于开始发起打印任务。调用此API前，待使用的打印机应在已连接的打印机列表中。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printJob 指向指定打印任务信息的 {@link Print_PrintJob} 实例的指针，不能为NULL，其中引用的打印机需已通过OH_Print_ConnectPrinter连接。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要ohos.permission.PRINT权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER} 打印机应在已连接的打印机列表中。
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE} 无法在打印服务中创建打印任务。
 *     <br>{@link PRINT_ERROR_INVALID_PRINT_JOB} 无法在任务队列中找到该任务。
 * @since 12
 */
Print_ErrorCode OH_Print_StartPrintJob(const Print_PrintJob *printJob);

/**
 * @brief 此API用于注册打印机变更回调。当不再需要监听打印机变更事件时，需调用OH_Print_UnregisterPrinterChangeListener()注销回调。未注销回调会导致回调持续生效，
 * 可能引发不必要的回调调用和资源占用。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param callback 打印机变更回调，用于在打印服务运行期间接收打印机添加、删除、状态变更、信息变更等事件通知，不能为NULL。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要ohos.permission.PRINT权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 * @since 12
 */
Print_ErrorCode OH_Print_RegisterPrinterChangeListener(Print_PrinterChangeCallback callback);

/**
 * @brief 此API用于注销打印机变更回调。
 *
 * @permission {@code ohos.permission.PRINT}
 * @since 12
 */
void OH_Print_UnregisterPrinterChangeListener();

/**
 * @brief 此API用于查询已添加的打印机列表。在使用完毕后，需调用OH_Print_ReleasePrinterList()释放查询结果所占内存，否则可能导致内存泄漏。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerIdList 用于存储查询到的打印机ID列表的 {@link Print_StringList} 实例指针，不能为NULL。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要ohos.permission.PRINT权限。
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER} printerIdList为NULL。
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER} 无法查询任何已连接的打印机。
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE} 无法复制打印机ID列表。
 * @since 12
 */
Print_ErrorCode OH_Print_QueryPrinterList(Print_StringList *printerIdList);

/**
 * @brief 此API用于释放打印机列表内存。传入的指针应来自OH_Print_QueryPrinterList()的查询结果。
 *
 * @param printerIdList 待释放的已查询打印机ID列表。
 * @since 12
 */
void OH_Print_ReleasePrinterList(Print_StringList *printerIdList);

/**
 * @brief 此API用于根据打印机ID查询打印机信息。使用完毕后，需调用OH_Print_ReleasePrinterInfo()释放查询结果所占内存，否则可能导致内存泄漏。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId 待查询的打印机ID，应为已连接的打印机列表中的打印机ID，不能为NULL。
 * @param printerInfo 用于存储打印机信息的 {@link Print_PrinterInfo} 指针的指针，不能为NULL。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要ohos.permission.PRINT权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER} printerId为NULL或printerInfo为NULL。
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER} 无法在已连接的打印机列表中找到该打印机。
 * @since 12
 */
Print_ErrorCode OH_Print_QueryPrinterInfo(const char *printerId, Print_PrinterInfo **printerInfo);

/**
 * @brief 此API用于释放打印机信息内存。传入的指针应来自OH_Print_QueryPrinterInfo()的查询结果。
 *
 * @param printerInfo 待释放的已查询打印机信息指针。
 * @since 12
 */
void OH_Print_ReleasePrinterInfo(Print_PrinterInfo *printerInfo);

/**
 * @brief 此API用于启动系统的打印机管理窗口。
 *
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE} 无法启动打印机管理窗口。
 * @since 12
 */
Print_ErrorCode OH_Print_LaunchPrinterManager();

/**
 * @brief 此API用于根据属性关键字列表查询对应的打印机属性值。在使用完毕后，需调用OH_Print_ReleasePrinterProperties()释放查询结果所占内存，否则可能会导致内存泄漏。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId 待查询的打印机ID，必须是已连接的打印机ID，不能为NULL。
 * @param propertyKeyList 待查询的属性关键字列表，不能为NULL且内部的字符串数组不能为NULL。
 * @param propertyList 查询到的打印机属性值列表，不能为NULL。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要ohos.permission.PRINT权限。
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER} 参数之一为NULL或关键字列表为空。
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER} 无法找到指定打印机的属性。
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE} 无法复制打印机属性。
 * @since 12
 */
Print_ErrorCode OH_Print_QueryPrinterProperties(const char *printerId, const Print_StringList *propertyKeyList,
    Print_PropertyList *propertyList);

/**
 * @brief 此API用于释放属性列表内存。传入的指针应来自OH_Print_QueryPrinterProperties()的查询结果。
 *
 * @param propertyList 待释放的已查询打印机属性值指针。
 * @since 12
 */
void OH_Print_ReleasePrinterProperties(Print_PropertyList *propertyList);

/**
 * @brief 此API用于根据属性键值对列表设置打印机属性。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId 待设置的打印机ID，必须是已连接的打印机列表中的打印机ID，不能为NULL。
 * @param propertyList 待设置的打印机属性值列表，不能为NULL且内部的属性数组不能为NULL。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要ohos.permission.PRINT权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 * @since 12
 */
Print_ErrorCode OH_Print_UpdatePrinterProperties(const char *printerId, const Print_PropertyList *propertyList);

/**
 * @brief 此API用于根据属性关键字列表将打印机属性恢复为默认设置。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId 待恢复的打印机ID，必须是已连接的打印机列表中的打印机ID，不能为NULL。
 * @param propertyKeyList 待恢复的属性关键字列表，不能为NULL且内部的字符串数组不能为NULL。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要ohos.permission.PRINT权限。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 * @since 12
 */
Print_ErrorCode OH_Print_RestorePrinterProperties(const char *printerId, const Print_StringList *propertyKeyList);

/**
 * @brief 此API用于启动系统打印应用，适用于需要用户在打印前通过系统打印应用选择打印机和设置打印参数（如份数、双面、色彩等）的场景。
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printJobName 此打印任务的名称。
 * @param printDocCallback 打印文档状态回调。
 * @param context 调用方应用的上下文指针，传入NULL表示不需要传递额外数据。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要ohos.permission.PRINT权限。
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
 * @brief 打印任务状态回调。与Print_OnJobStateChanged（使用uint32_t表示状态，起始版本13）相比，本回调使用OH_Print_JobState枚举表示任务状态，语义更清晰、类型更安全。
 *
 * @param jobId 打印任务的ID。
 * @param state 当前打印任务的状态。
 * @since 24
 */
typedef void(*OH_Print_OnJobStateChanged)(const char *jobId, OH_Print_JobState state);

/**
 * @brief 此API用于下发打印任务，并附带任务状态变更回调功能，适合需要监听打印任务执行状态（如成功、失败、取消等）的场景。调用此API前，待使用的打印机应在已连接的打印机列表中；如无需监听任务状态变化，
 * 可使用OH_Print_StartPrintJob。
 *
 * @permission ohos.permission.PRINT
 * @param printJob 指向指定打印任务信息的 {@link Print_PrintJob} 实例的指针，不能为NULL，其中引用的打印机需已通过OH_Print_ConnectPrinter连接。
 * @param jobStateChangedCb 打印任务状态回调，用于监听printJob参数指定的打印任务的状态变更，不能为NULL。
 * @return 返回 {@link PRINT_ERROR_NONE} 表示执行成功。
 *     <br>{@link PRINT_ERROR_NO_PERMISSION} 需要 {@link ohos.permission.PRINT} 权限。
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER} jobStateChangedCb为NULL。
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE} 无法复制回调函数。
 *     <br>{@link PRINT_ERROR_RPC_FAILURE} 无法连接到打印服务。
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE} 打印服务中创建打印任务结构体失败。
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER} 无法找到指定打印机的属性。
 *     <br>{@link PRINT_ERROR_INVALID_PRINT_JOB} printJob为NULL或内部参数不合法。
 * @since 24
 */
Print_ErrorCode OH_Print_StartPrintWithJobStateCallback(const Print_PrintJob *printJob,
                                                        OH_Print_OnJobStateChanged jobStateChangedCb);

#ifdef __cplusplus
}
#endif

#endif // OH_PRINT_H
/** @} */