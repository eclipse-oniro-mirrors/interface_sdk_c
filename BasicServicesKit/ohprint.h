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
 * @brief Declares APIs for discovering and connecting to printers, printing files, and querying the list of added
 * printers and printer information. This module can be used to integrate the printing capability to an app, helping
 * developers conveniently manage the printing process, including printer discovery, connection, task delivery, and
 * status monitoring.
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
 * @brief Enumerates the error codes.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Operation successful.
     */
    PRINT_ERROR_NONE = 0,
    /**
     * Permission verification failed. Ensure that the corresponding permission has been declared in the app
     * configuration.
     */
    PRINT_ERROR_NO_PERMISSION = 201,
    /**
     * Invalid parameter. Check the type and value range of the passed parameter.
     */
    PRINT_ERROR_INVALID_PARAMETER = 401,
    /**
     * Generic internal error. Check the running status of the printing service and try again.
     */
    PRINT_ERROR_GENERIC_FAILURE = 24300001,
    /**
     * RPC communication error. Ensure that the printing service has been started and try again.
     */
    PRINT_ERROR_RPC_FAILURE = 24300002,
    /**
     * Server error. Check the running status of the printing service.
     */
    PRINT_ERROR_SERVER_FAILURE = 24300003,
    /**
     * Invalid extension. Ensure that a valid printing extension has been installed.
     */
    PRINT_ERROR_INVALID_EXTENSION = 24300004,
    /**
     * Invalid printer. Ensure that the printer is in the list of discovered or connected printers.
     */
    PRINT_ERROR_INVALID_PRINTER = 24300005,
    /**
     * Invalid print task. Ensure that the print task information is complete and the printer is connected.
     */
    PRINT_ERROR_INVALID_PRINT_JOB = 24300006,
    /**
     * Failure to read data from or write data to the file. Check the file path and access permission.
     */
    PRINT_ERROR_FILE_IO = 24300007,
    /**
     * Unknown error. Check the printing service status and try again. If the issue persists, contact technical support.
     */
    PRINT_ERROR_UNKNOWN = 24300255,
} Print_ErrorCode;

/**
 * @brief Enumerates the printer states.
 *
 * @since 12
 */
typedef enum {
    /**
     * The printer is idle.
     */
    PRINTER_IDLE,
    /**
     * The printer is busy.
     */
    PRINTER_BUSY,
    /**
     * The printer is unavailable.
     */
    PRINTER_UNAVAILABLE,
} Print_PrinterState;

/**
 * @brief Enumerates the printer discovery events.
 *
 * @since 12
 */
typedef enum {
    /**
     * Printer discovered.
     */
    PRINTER_DISCOVERED = 0,
    /**
     * Printer lost.
     */
    PRINTER_LOST = 1,
    /**
     * Printer connecting.
     */
    PRINTER_CONNECTING = 2,
    /**
     * Printer connected.
     */
    PRINTER_CONNECTED = 3,
} Print_DiscoveryEvent;

/**
 * @brief Enumerates the printer change events.
 *
 * @since 12
 */
typedef enum {
    /**
     * Printer added.
     */
    PRINTER_ADDED = 0,
    /**
     * Printer deleted.
     */
    PRINTER_DELETED = 1,
    /**
     * Printer changed.
     */
    PRINTER_STATE_CHANGED = 2,
    /**
     * Printer information changed.
     */
    PRINTER_INFO_CHANGED = 3,
} Print_PrinterEvent;

/**
 * @brief Represents a string list, which is used to transfer multiple strings in the print module. This struct uses
 * the **count** field to record the number of strings and the **list** field to point to the string array. It can be
 * used to transfer multiple strings in batches. For details about related APIs, see {@link OH_Print}.
 *
 * @since 12
 */
typedef struct {
    /**
     * String count, which indicates the number of elements in the **list** array.
     */
    uint32_t count;
    /**
     * Pointer to the string array. The number of elements in the array must be the same as the value of **count**.
     */
    char **list;
} Print_StringList;

/**
 * @brief Describes the printer properties in key-value pair format. You can use this struct to obtain or set printer
 * properties.
 *
 * @since 12
 */
typedef struct {
    /**
     * Property key, which identifies the type of a printer property. The value must be a valid property name defined
     * in the {@link OH_Print} module.
     */
    char *key;
    /**
     * Property value, which corresponds to the property key. The format and valid range of the value depend on the
     * corresponding property key.
     */
    char *value;
} Print_Property;

/**
 * @brief Defines a printer property list, which is used to store and manage printer properties. You can access and
 * operate printer properties in batches by using the property count and the pointer to the property array. **count**
 * indicates the number of properties, and **list** is a pointer to the property array. The two parameters together
 * indicate a complete set of printer properties, which is applicable to scenarios where multiple printer properties
 * need to be queried or set.
 *
 * @since 12
 */
typedef struct {
    /**
     * Number of properties. The value must be the same as the actual number of elements in the property array to which
     * **list** points.
     */
    uint32_t count;
    /**
     * Pointer to the property array, which is used to store printer properties. This parameter must be used together
     * with **count**. The array length is specified by **count**.
     */
    Print_Property *list;
} Print_PropertyList;

/**
 * @brief Represents the printing resolution, in dpi. This API can be used to control the fineness and quality of the
 * print output.
 *
 * @since 12
 */
typedef struct {
    uint32_t horizontalDpi;
    uint32_t verticalDpi;
} Print_Resolution;

/**
 * @brief Represents the margin information of a printed page. You can set the margins in the left, top, right, and
 * bottom directions to control the print content area. This API can be used to precisely control the distance between
 * the content and the paper edge during printing. Proper margin settings can prevent content overflow or clipping.
 *
 * @since 12
 */
typedef struct {
    /**
     * Left margin, in millimeters. The value must be greater than **0**.
     */
    uint32_t leftMargin;
    /**
     * Top margin, in millimeters. The value must be greater than **0**.
     */
    uint32_t topMargin;
    /**
     * Right margin, in millimeters. The value must be greater than **0**.
     */
    uint32_t rightMargin;
    /**
     * Bottom margin, in millimeters. The value must be greater than **0**.
     */
    uint32_t bottomMargin;
} Print_Margin;

/**
 * @brief Represents the paper size information in a print task, including key attributes such as the paper ID, name,
 * width, and height. This API can be used to specify or query paper specifications during printing configuration.
 *
 * @since 12
 */
typedef struct {
    /**
     * Unique ID of the paper size, which is used to distinguish different paper specifications.
     */
    char *id;
    /**
     * Name of the paper size, for example, **A4** or **Letter**.
     */
    char *name;
    /**
     * Paper width, in mils (1 mil = 1/1000 inch). The value must be greater than **0**.
     */
    uint32_t width;
    /**
     * Paper height, in mils (1 mil = 1/1000 inch). The value must be greater than **0**.
     */
    uint32_t height;
} Print_PageSize;

/**
 * @brief Enumerates the duplex modes.
 *
 * @since 12
 */
typedef enum {
    /**
     * Single-sided mode.
     */
    DUPLEX_MODE_ONE_SIDED = 0,
    /**
     * Duplex mode with flipping on long edge.
     */
    DUPLEX_MODE_TWO_SIDED_LONG_EDGE = 1,
    /**
     * Duplex mode with flipping on short edge.
     */
    DUPLEX_MODE_TWO_SIDED_SHORT_EDGE = 2,
} Print_DuplexMode;

/**
 * @brief Enumerates the color modes.
 *
 * @since 12
 */
typedef enum {
    /**
     * B/W mode.
     */
    COLOR_MODE_MONOCHROME = 0,
    /**
     * Color mode. The color mode is suitable for documents (such as images) that require color display. The monochrome
     * mode is suitable for printing plain text or drafts to save consumables. The automatic mode allows the system to
     * automatically select the color mode.
     */
    COLOR_MODE_COLOR = 1,
    /**
     * Auto mode.
     */
    COLOR_MODE_AUTO = 2,
} Print_ColorMode;

/**
 * @brief Enumerates the orientation modes.
 *
 * @since 12
 */
typedef enum {
    /**
     * Portrait mode.
     */
    ORIENTATION_MODE_PORTRAIT = 0,
    /**
     * Landscape mode.
     */
    ORIENTATION_MODE_LANDSCAPE = 1,
    /**
     * Reverse landscape mode.
     */
    ORIENTATION_MODE_REVERSE_LANDSCAPE = 2,
    /**
     * Reverse portrait mode.
     */
    ORIENTATION_MODE_REVERSE_PORTRAIT = 3,
    /**
     * Not specified.
     */
    ORIENTATION_MODE_NONE = 4,
} Print_OrientationMode;

/**
 * @brief Enumerates the print qualities.
 *
 * @since 12
 */
typedef enum {
    /**
     * Draft-quality mode.
     */
    PRINT_QUALITY_DRAFT = 3,
    /**
     * Normal-quality mode.
     */
    PRINT_QUALITY_NORMAL = 4,
    /**
     * High-quality mode.
     */
    PRINT_QUALITY_HIGH = 5
} Print_Quality;

/**
 * @brief Enumerates the MIME types.
 *
 * @since 12
 */
typedef enum {
    /**
     * application/octet-stream.
     */
    DOCUMENT_FORMAT_AUTO,
    /**
     * image/jpeg.
     */
    DOCUMENT_FORMAT_JPEG,
    /**
     * application/pdf.
     */
    DOCUMENT_FORMAT_PDF,
    /**
     * application/postscript.
     */
    DOCUMENT_FORMAT_POSTSCRIPT,
    /**
     * text/plain.
     */
    DOCUMENT_FORMAT_TEXT,
} Print_DocumentFormat;

/**
 * @brief Enumerates the print job adapter states.
 *
 * @since 13
 */
typedef enum {
    /**
     * Print job preview destroyed.
     */
    PRINT_DOC_ADAPTER_PREVIEW_ABILITY_DESTROY = 0,
    /**
     * Successful print job.
     */
    PRINT_DOC_ADAPTER_PRINT_TASK_SUCCEED = 1,
    /**
     * Print job failed.
     */
    PRINT_DOC_ADAPTER_PRINT_TASK_FAIL = 2,
    /**
     * Print job canceled.
     */
    PRINT_DOC_ADAPTER_PRINT_TASK_CANCEL = 3,
    /**
     * Print job blocked.
     */
    PRINT_DOC_ADAPTER_PRINT_TASK_BLOCK = 4,
    /**
     * Print job preview destroyed due to cancellation.
     */
    PRINT_DOC_ADAPTER_PREVIEW_ABILITY_DESTROY_FOR_CANCELED = 5,
    /**
     * Print job preview destroyed due to startup.
     */
    PRINT_DOC_ADAPTER_PREVIEW_ABILITY_DESTROY_FOR_STARTED = 6,
} Print_JobDocAdapterState;

/**
 * @brief Describes the printer capabilities, including the supported colors, duplex modes, paper sizes, media types,
 * print quality, paper sources, copies, resolution, print orientations, and advanced capabilities. This API can be
 * used to query or match printer capabilities, helping developers configure and adapt print tasks based on printer
 * capabilities.
 *
 * @since 12
 */
typedef struct {
    /**
     * Array of supported color modes. The array length is determined by **supportedColorModesCount**.
     */
    Print_ColorMode *supportedColorModes;
    /**
     * Number of supported color modes, which is the same as the actual number of elements in the
     * **supportedColorModes** array.
     */
    uint32_t supportedColorModesCount;
    /**
     * Array of supported duplex modes. The array length is determined by **supportedDuplexModesCount**.
     */
    Print_DuplexMode *supportedDuplexModes;
    /**
     * Number of supported duplex modes, which is the same as the actual number of elements in the
     * **supportedDuplexModes** array.
     */
    uint32_t supportedDuplexModesCount;
    /**
     * Array of supported paper sizes. The array length is determined by **supportedPageSizesCount**.
     */
    Print_PageSize *supportedPageSizes;
    /**
     * Number of supported paper sizes, which is the same as the actual number of elements in the **supportedPageSizes**
     * array.
     */
    uint32_t supportedPageSizesCount;
    /**
     * Supported print media types. The value is a string in JSON format and determined by the printer.
     */
    char *supportedMediaTypes;
    /**
     * Array of supported print quality options. The array length is determined by **supportedQualitiesCount**.
     */
    Print_Quality *supportedQualities;
    /**
     * Number of supported print quality options, which is the same as the actual number of elements in the 
     * **supportedQualities** array.
     */
    uint32_t supportedQualitiesCount;
    /**
     * Supported paper sources. The value is a string in JSON array format and determined by the printer.
     */
    char *supportedPaperSources;
    /**
     * Number of supported copies. The value is determined by the printer capability.
     */
    uint32_t supportedCopies;
    /**
     * Array of supported printer resolutions. The array length is determined by **supportedResolutionsCount**.
     */
    Print_Resolution *supportedResolutions;
    /**
     * Number of supported printer resolutions, which is the same as the actual number of elements in the 
     * **supportedResolutions** array.
     */
    uint32_t supportedResolutionsCount;
    /**
     * Array of supported print orientation modes. The array length is determined by **supportedOrientationsCount**.
     */
    Print_OrientationMode *supportedOrientations;
    /**
     * Number of supported print orientation modes, which is the same as the actual number of elements in the
     * **supportedOrientations** array.
     */
    uint32_t supportedOrientationsCount;
    /**
     * Advanced capability. The value is a string in JSON format. This parameter is used to describe printer features
     * other than those described above. The specific field names and values of the JSON object are determined by the
     * printer. You need to parse the JSON object based on the actual returned content.
     */
    char *advancedCapability;
} Print_PrinterCapability;

/**
 * @brief Enumerates default attributes of a printer, including the color mode, duplex mode, media type, paper size,
 * margin, paper source, print quality, copies, resolution, and orientation.
 *
 * @since 12
 */
typedef struct {
    /**
     * Default color mode, which indicates the color mode of the print output. The value is determined by the color
     * modes supported by the printer.
     */
    Print_ColorMode defaultColorMode;
    /**
     * Default duplex mode, which indicates whether printing is single-sided or double-sided. The value is determined
     * by the duplex modes supported by the printer.
     */
    Print_DuplexMode defaultDuplexMode;
    /**
     * Default media type, which indicates the type of media (such as ordinary paper or glossy paper) used for printing.
     *  The value is determined by the media types supported by the printer.
     */
    char *defaultMediaType;
    /**
     * Default paper size ID, which indicates the paper size ID (such as **A4** or **Letter**) used for printing. The
     * value is determined by the paper sizes supported by the printer.
     */
    char *defaultPageSizeId;
    /**
     * Default margin, which indicates the margin settings of the printed page. The value is determined by the margins
     * supported by the printer.
     */
    Print_Margin defaultMargin;
    /**
     * Default paper source, which indicates the paper source (such as automatic paper feeder or manual feeding) used
     * for printing. The value is determined by the paper sources supported by the printer.
     */
    char *defaultPaperSource;
    /**
     * Default print quality, which indicates the quality level of the print. The value is determined by the print
     * quality supported by the printer.
     */
    Print_Quality defaultPrintQuality;
    /**
     * Default number of copies. The value must be greater than or equal to 1.
     */
    uint32_t defaultCopies;
    /**
     * Default resolution, which indicates the resolution of the print. The value is determined by the resolutions
     * supported by the printer.
     */
    Print_Resolution defaultResolution;
    /**
     * Default print orientation, which indicates the orientation (such as portrait or landscape) of the print. The
     * value is determined by the print orientations supported by the printer.
     */
    Print_OrientationMode defaultOrientation;
    /**
     * Other default values in JSON format, which indicate additional default print attributes that are not listed in
     * the preceding member variables. The key-value pairs that can be set are determined by the extended capabilities
     * supported by the printer.
     */
    char *otherDefaultValues;
} Print_DefaultValue;

/**
 * @brief Represents the printer information, including the printer status, capabilities, default attributes, and
 * identification information (such as the printer ID, name, description, location, brand, model, and URI). This API
 * can be used by apps to obtain and display detailed printer information in printing scenarios, helping developers
 * select appropriate printers based on their capabilities and attributes. You can obtain the value by calling
 * {@link OH_Print_StartPrinterDiscovery} or {@link OH_Print_QueryPrinterInfo}.
 *
 * @since 12
 */
typedef struct {
    /**
     * Current running state of the printer.
     */
    Print_PrinterState printerState;
    /**
     * Capabilities supported by the printer, such as the paper sizes and color modes.
     */
    Print_PrinterCapability capability;
    /**
     * Default attributes of the printer, such as the default paper size and color mode.
     */
    Print_DefaultValue defaultValue;
    /**
     * Whether the printer is the default one. The value **true** indicates that the printer is the default one, and
     * the value **false** indicates the opposite.
     */
    bool isDefaultPrinter;
    /**
     * Printer ID, which specifies the target printer. You can obtain a valid printer ID by calling the related query
     * API, for example, {@link OH_Print_QueryPrinterList}.
     */
    char *printerId;
    /**
     * Printer name.
     */
    char *printerName;
    /**
     * Printer description.
     */
    char *description;
    /**
     * Printer location.
     */
    char *location;
    /**
     * Brand and model of the printer.
     */
    char *makeAndModel;
    /**
     * Printer URI, which is used to locate and access the printer. The value is in the format of **scheme://[user@]
     * host[:port]/resource**.
     */
    char *printerUri;
    /**
     * Details in JSON format.
     * <br>The supported keys are as follows:
     * <br>- **printerAlias**: printer alias, the value is of the string type.
     * This key is supported since API version 24.
     * <br>- **vendorId**: USB printer VID, the value is of the int type and within the range of [0, 65535].
     * This key is supported since API version 12.
     * <br>- **productId**: USB printer PID, the value is of the int type and within the range of [0, 65535].
     * This key is supported since API version 12.
     * <br>- **protocol**: array of protocols supported by the printer. The value is of the string type, and the options
     * include **ipp**, **ipps**, **lpd**, and **socket**. This key is supported since API version 24.
     * <br>- **ipp**: printer URI of the IPP protocol, the value is of the string type.
     * This key is supported since API version 24.
     * <br>- **ipps**: printer URI of the IPPS protocol, the value is of the string type.
     * This key is supported since API version 24.
     * <br>- **lpd**: printer URI of the LPD protocol, the value is of the string type.
     * This key is supported since API version 24.
     * <br>- **socket**: printer URI of the Socket protocol, the value is of the string type.
     * This key is supported since API version 24.
     */
    char *detailInfo;
} Print_PrinterInfo;

/**
 * @brief Represents a print job, which is used to configure the attributes of a print job, including the number of
 * copies, paper source, color mode, duplex mode, resolution, margin, orientation mode, print quality, document format,
 * and advanced options. You can initiate a print job by populating this struct and submitting it to the print module
 * API.
 *
 * @since 12
 */
typedef struct {
    /**
     * Task name, which identifies the print task and distinguishes it from other tasks.
     */
    char *jobName;
    /**
     * Array of file descriptors to be printed. This parameter must be used together with **fdListCount**. The value of
     * **fdListCount** must be equal to the number of elements in this array.
     */
    uint32_t *fdList;
    /**
     * Number of file descriptors to be printed. The value must be greater than or equal to 1, and must be the same as
     * the length of the **fdList** array.
     */
    uint32_t fdListCount;
    /**
     * Printer ID, which specifies the target printer. You can obtain a valid printer ID by calling the related query
     * API, for example, {@link OH_Print_QueryPrinterList}.
     */
    char *printerId;
    /**
     * Number of copies to print. The value must be greater than or equal to 1.
     */
    uint32_t copyNumber;
    /**
     * Paper source, which specifies the paper feeding mode. The available values depend on the paper source options
     * supported by the printer.
     */
    char *paperSource;
    /**
     * Media type, which specifies the type of the printing media, such as ordinary paper, glossy paper, and photo
     * paper. The available values depend on the media type options supported by the printer.
     */
    char *mediaType;
    /**
     * Paper size ID, which specifies the size of the paper to be printed, such as **ISO A4**, **Letter**, and **A3**.
     * The available values depend on the size options supported by the printer.
     */
    char *pageSizeId;
    /**
     * Color mode. The color mode is suitable for documents (such as images) that require color display. The monochrome
     * mode is suitable for printing plain text or drafts to save consumables. The automatic mode allows the system to
     * automatically select the color mode.
     */
    Print_ColorMode colorMode;
    /**
     * Duplex mode. The single-sided mode is suitable for single-sided printing. The long-edge flip mode is suitable
     * for documents that are turned vertically (such as books). The short-edge flip mode is suitable for documents
     * that are turned horizontally (such as calendars).
     */
    Print_DuplexMode duplexMode;
    /**
     * Print resolution, in dpi. A high resolution is suitable for printing fine content such as images, while a low
     * resolution is suitable for printing plain text or drafts to save on consumables and printing time.
     */
    Print_Resolution resolution;
    /**
     * Print margin, in millimeters. You are advised to set the margin based on the document type and the minimum
     * margin supported by the printer. If the margin is too small, the printed content may be cropped.
     */
    Print_Margin printMargin;
    /**
     * Whether to print without margins. The value **true** means to print without margins, and **false** means the
     * opposite.
     */
    bool borderless;
    /**
     * Orientation mode. The portrait mode is suitable for printing regular documents. The landscape mode is suitable
     * for printing wide content such as tables and charts. The reverse landscape mode is suitable for printing
     * horizontal content that requires mirroring. The reverse portrait mode is suitable for printing vertical content
     * that requires mirroring. If no mode is specified, the system automatically selects an orientation.
     */
    Print_OrientationMode orientationMode;
    /**
     * Print quality. The high-quality mode is suitable for final output or formal documents. The normal mode is
     * suitable for daily printing. The draft mode is suitable for quick preview to save consumables.
     */
    Print_Quality printQuality;
    /**
     * MIME media type of the document, for example, PDF (application/pdf) or JPEG (image/jpeg).
     */
    Print_DocumentFormat documentFormat;
    /**
     * @brief Advanced options in JSON format.
     * <br>The following keys are supported:
     * <br>- **isReverse**: Boolean type, indicating whether to print in reverse order.
     * <br>- **isCollate**: Boolean type, indicating whether to print copies one by one.
     * <br>- **printPages**: Integer type, indicating the actual number of pages to print. The value
     * must be greater than or equal to 1. Default value is 1.
     */
    char *advancedOptions;
} Print_PrintJob;

/**
 * @brief Represents the print range, which is used to specify the page range in a print task. You can use **startPage**
 * and **endPage** to specify consecutive pages, or use **pagesArray** and **pagesArrayLen** to specify an array of
 * non-consecutive pages to be printed.
 *
 * @since 13
 */
typedef struct {
    /**
     * Start page number for printing. The page number starts from 1. The value must be a valid page number in the
     * document and must be less than or equal to the value of **endPage**.
     */
    uint32_t startPage;
    /**
     * End page number for printing. The page number starts from 1. The value must be a valid page number in the
     * document and must be greater than or equal to the value of **startPage**.
     */
    uint32_t endPage;
    /**
     * Length of the page array. The value must be the same as the actual number of elements in the **pagesArray**
     * array. This parameter is valid only when **pagesArray** is not **NULL**.
     */
    uint32_t pagesArrayLen;
    /**
     * Page array. Each element in the array indicates a page to be printed. The page number starts from 1. The value
     * must be a valid page number in the document. The array length is determined by **pagesArrayLen**.
     */
    uint32_t *pagesArray;
} Print_Range;

/**
 * @brief Represents the print attributes to be configured in a print task, including the print range, paper size,
 * margin, number of copies, duplex mode, color mode, print orientation, and print options. This API can be used to
 * perform refined control over the print output.
 *
 * @since 13
 */
typedef struct {
    /**
     * Print range.
     */
    Print_Range pageRange;
    /**
     * Page size.
     */
    Print_PageSize pageSize;
    /**
     * Print margin, in millimeters. You are advised to set the margin based on the document type and the minimum
     * margin supported by the printer. If the margin is too small, the printed content may be cropped.
     */
    Print_Margin pageMargin;
    /**
     * Number of copies to print. The value must be greater than or equal to 1.
     */
    uint32_t copyNumber;
    /**
     * Duplex mode. The single-sided mode is suitable for single-sided printing. The long-edge flip mode is suitable
     * for documents that are turned vertically (such as books). The short-edge flip mode is suitable for documents
     * that are turned horizontally (such as calendars).
     */
    uint32_t duplexMode;
    /**
     * Color mode. The color mode is suitable for documents (such as images) that require color display. The monochrome
     * mode is suitable for printing plain text or drafts to save consumables. The automatic mode allows the system to
     * automatically select the color mode.
     */
    uint32_t colorMode;
    /**
     * Whether pages are printed in sequential order.<br>The value **true** indicates that pages are printed in
     * sequential order, and **false** indicates that pages are printed in reverse order.
     */
    bool isSequential;
    /**
     * Whether pages are printed in landscape mode.<br>The value **true** indicates that pages are printed in landscape
     * mode, and **false** indicates that pages are printed in portrait mode.
     */
    bool isLandscape;
    /**
     * Whether the printing has an option flag.<br>The value **true** indicates that the printing has an option flag (
     * the **options** field is valid), and **false** indicates the opposite (the **options** field is invalid).
     */
    bool hasOption;
    /** Printing options, which are used to pass additional printing configuration parameters. This parameter is valid
     * only when **hasOption** is set to **true**. The value can contain a maximum of 255 characters.
     */
    char options[256];
} Print_PrintAttributes;

/**
 * @brief Defines a callback used to return the file write-back result.
 *
 * @param jobId Pointer to the print job ID.
 * @param code File write-back result. **0**: The file is successfully created. **1**: The file fails to be created. 
 *     **2**: The file is successfully created but not rendered.
 * @since 13
 */
typedef void(*Print_WriteResultCallback)(const char *jobId, uint32_t code);

/**
 * @brief Defines a callback to be invoked when the file write-back starts.
 *
 * @param jobId Pointer to the print job ID.
 * @param fd File descriptor to write.
 * @param oldAttrs Pointer to the print attributes of the previous print job.
 * @param newAttrs Pointer to the print attributes of the current print job.
 * @param writeCallback Defines a callback used to return the file write-back result.
 * @since 13
 */
typedef void(*Print_OnStartLayoutWrite)(const char *jobId,
                                        uint32_t fd,
                                        const Print_PrintAttributes *oldAttrs,
                                        const Print_PrintAttributes *newAttrs,
                                        Print_WriteResultCallback writeCallback);

/**
 * @brief Defines a callback to be invoked when the print job state changes.
 *
 * @param jobId Pointer to the print job ID.
 * @param state Status of the current print task. For details about the values and meanings, see
 *     {@link OH_Print_JobState}.
 * @since 13
 */
typedef void(*Print_OnJobStateChanged)(const char *jobId, uint32_t state);

/**
 * @brief Represents a callback for the printed document. This API can be used by native apps written in C or C++ to
 * provide file generation and task status receiving capabilities for the print framework.
 *
 * @since 13
 */
typedef struct {
    /**
     * Callback invoked when the file write-back starts. When the file write-back starts, the system calls this
     * callback to instruct the app to write the content to be printed.
     */
    Print_OnStartLayoutWrite startLayoutWriteCb;
    /**
     * Callback invoked when the print job state changes. When the print job state changes, the system invokes this
     * callback to notify the app of the change.
     */
    Print_OnJobStateChanged jobStateChangedCb;
} Print_PrintDocCallback;

/**
 * @brief Defines a callback used to return the discovered printers.
 *
 * @param event Printer discovery event.
 * @param printerInfo Printer information when the discovery event occurs.
 * @since 12
 */
typedef void (*Print_PrinterDiscoveryCallback)(Print_DiscoveryEvent event, const Print_PrinterInfo *printerInfo);

/**
 * @brief Defines a callback to be invoked when a printer is changed.
 *
 * @param event Printer change event during the running of the print service.
 * @param printerInfo Printer information when the change event occurs.
 * @since 12
 */
typedef void (*Print_PrinterChangeCallback)(Print_PrinterEvent event, const Print_PrinterInfo *printerInfo);

/**
 * @brief Checks and starts the print service, initializes the print client, and connects it with the print service.
 * Before calling other print APIs, you must call this API to complete initialization. Otherwise, other APIs cannot
 * work properly because the connection to the print service is not established. After using the print service, call
 * **OH_Print_Release()** to terminate the connection and release the print client resources. Otherwise, the connection
 * to the print service will not be closed and the client resource leak may occur.
 *
 * @permission {@code ohos.permission.PRINT}
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The **ohos.permission.PRINT** permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: The print service fails to be connected.
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE}: The CUPS service fails to be started.
 * @since 12
 */
Print_ErrorCode OH_Print_Init();

/**
 * @brief Disconnects from the print service, unregister all registered callbacks, and releases the print client
 * resources.
 *
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>Currently, no other error codes will be returned.
 * @since 12
 */
Print_ErrorCode OH_Print_Release();

/**
 * @brief Starts printer discovery. During the discovery process, you can use **Print_PrinterDiscoveryCallback** to
 * notify printer discovery events and obtain the printer information from **Print_PrinterInfo**. After the discovery
 * is complete, you can call **OH_Print_StopPrinterDiscovery()** to stop the discovery process. Otherwise, the
 * discovery process will continue, consuming system resources.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param callback {@link Print_PrinterDiscoveryCallback} to be invoked when a printer is discovered.
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The **ohos.permission.PRINT** permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: The print service fails to be connected.
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE}: The print extension list fails to be obtained from the BMS.
 *     <br>{@link PRINT_ERROR_INVALID_EXTENSION}: No available print extension is found.
 * @since 12
 */
Print_ErrorCode OH_Print_StartPrinterDiscovery(Print_PrinterDiscoveryCallback callback);

/**
 * @brief Stops printer discovery.
 *
 * @permission {@code ohos.permission.PRINT}
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The **ohos.permission.PRINT** permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: The print service fails to be connected.
 * @since 12
 */
Print_ErrorCode OH_Print_StopPrinterDiscovery();

/**
 * @brief Connects to a printer by the printer ID.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId ID of the printer to connect to. The printer must be in the list of discovered printers. The value
 *     cannot be null.
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The **ohos.permission.PRINT** permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: The print service fails to be connected.
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER}: Printer does not exist in the list of discovered printers.
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE}: The printer extension cannot be found.
 * @since 12
 */
Print_ErrorCode OH_Print_ConnectPrinter(const char *printerId);

/**
 * @brief Starts a print job. Before calling this API, ensure that the printer to be used is in the list of connected
 * printers.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printJob Pointer to the {@link Print_PrintJob} instance. The value cannot be null. The referenced printer
 *     must have been connected using **OH_Print_ConnectPrinter**.
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The **ohos.permission.PRINT** permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: The print service fails to be connected.
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER}: Printer does not exist in the list of connected printers.
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE}: Failed to create a print job in the print service.
 *     <br>{@link PRINT_ERROR_INVALID_PRINT_JOB}: Failed to find the specified task in the task queue.
 * @since 12
 */
Print_ErrorCode OH_Print_StartPrintJob(const Print_PrintJob *printJob);

/**
 * @brief Registers a listener for printer changes. When you no longer need to listen for printer change events, call
 * **OH_Print_UnregisterPrinterChangeListener()** to unregister the listener. If the listener is not unregistered,
 * it may cause unnecessary calls and resource usage.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param callback Callback for printer changes, which is used to receive notifications of printer addition, deletion,
 *     status change, and information change during the running of the printing service. The value cannot be null.
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The **ohos.permission.PRINT** permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: The print service fails to be connected.
 * @since 12
 */
Print_ErrorCode OH_Print_RegisterPrinterChangeListener(Print_PrinterChangeCallback callback);

/**
 * @brief Unregisters this listener for printer changes.
 *
 * @permission {@code ohos.permission.PRINT}
 * @since 12
 */
void OH_Print_UnregisterPrinterChangeListener();

/**
 * @brief Queries the list of added printers. After using this API, call **OH_Print_ReleasePrinterList()** to release
 * the memory occupied by the query result. Otherwise, memory leak may occur.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerIdList Pointer to the {@link Print_StringList} instance that stores the queried printer ID list. The
 *     value cannot be null.
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The **ohos.permission.PRINT** permission is required.
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER}: **printerIdList** is null.
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER}: Failed to query any connected printers.
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE}: Failed to copy printer ID list.
 * @since 12
 */
Print_ErrorCode OH_Print_QueryPrinterList(Print_StringList *printerIdList);

/**
 * @brief Releases the memory used to store the printer list. The input pointer must come from the query result of
 * **OH_Print_QueryPrinterList()**.
 *
 * @param printerIdList Pointer to the queried printer ID list.
 * @since 12
 */
void OH_Print_ReleasePrinterList(Print_StringList *printerIdList);

/**
 * @brief Queries printer information by printer ID. After using this API, call **OH_Print_ReleasePrinterInfo()** to
 * release the memory occupied by the query result. Otherwise, memory leak may occur.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId ID of the printer to query. The printer must be in the list of connected printers. The value cannot
 *     be null.
 * @param printerInfo Double pointer to the {@link Print_PrinterInfo}. The value cannot be null.
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The **ohos.permission.PRINT** permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: The print service fails to be connected.
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER}: **printerId** or **printerInfo** is null.
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER}: Failed to find the specified printer in the list of connected printers.
 * @since 12
 */
Print_ErrorCode OH_Print_QueryPrinterInfo(const char *printerId, Print_PrinterInfo **printerInfo);

/**
 * @brief Releases the memory allocated for querying the printer information. The input pointer must come from the
 * query result of **OH_Print_QueryPrinterInfo()**.
 *
 * @param printerInfo Pointer to the queried printer information.
 * @since 12
 */
void OH_Print_ReleasePrinterInfo(Print_PrinterInfo *printerInfo);

/**
 * @brief Starts the printer management window of the system.
 *
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE}: Failed to start the printer management window.
 * @since 12
 */
Print_ErrorCode OH_Print_LaunchPrinterManager();

/**
 * @brief Queries the printer properties based on the list of property keys. After using this API, call
 * **OH_Print_ReleasePrinterProperties()** to release the memory occupied by the query result.
 * Otherwise, memory leak may occur.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId ID of the printer to query. The printer must be connected. The value cannot be null.
 * @param propertyKeyList List of property keys to query. The value cannot be null, and the internal string array
 *     cannot be null.
 * @param propertyList Pointer to the queried printer properties. The value cannot be null.
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The **ohos.permission.PRINT** permission is required.
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER}: One of the parameters is null or the key list is empty.
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER}: Failed to find properties of the specified printer.
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE}: Failed to copy printer properties.
 * @since 12
 */
Print_ErrorCode OH_Print_QueryPrinterProperties(const char *printerId, const Print_StringList *propertyKeyList,
    Print_PropertyList *propertyList);

/**
 * @brief Releases the memory used to store the property list. The input pointer must come from the query result of
 * **OH_Print_QueryPrinterProperties()**.
 *
 * @param propertyList Pointer to the queried printer properties.
 * @since 12
 */
void OH_Print_ReleasePrinterProperties(Print_PropertyList *propertyList);

/**
 * @brief Updates the printer properties based on the KV pairs.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId ID of the printer to set. The printer must be in the list of connected printers. The value cannot
 *     be null.
 * @param propertyList List of printer properties to set. The value cannot be null, and the internal property array
 *     cannot be null.
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The **ohos.permission.PRINT** permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: The print service fails to be connected.
 * @since 12
 */
Print_ErrorCode OH_Print_UpdatePrinterProperties(const char *printerId, const Print_PropertyList *propertyList);

/**
 * @brief Restores printer properties to the default settings based on the property key list.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId ID of the printer to be restored. The printer must be in the list of connected printers. The value
 *     cannot be null.
 * @param propertyKeyList List of property keys to be restored. The value cannot be null, and the internal string array
 *     cannot be null.
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The **ohos.permission.PRINT** permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: The print service fails to be connected.
 * @since 12
 */
Print_ErrorCode OH_Print_RestorePrinterProperties(const char *printerId, const Print_StringList *propertyKeyList);

/**
 * @brief Starts the system printing app. This API enables users to select a printer and set printing parameters (such
 * as the number of copies, double-sided printing, and color) using the system printing app before printing.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printJobName Pointer to the name of the print job.
 * @param printDocCallback Callback used to return the file state.
 * @param context Pointer to the context of the app that calls the API. If this parameter is set to null, no additional
 *     data needs to be passed.
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The **ohos.permission.PRINT** permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: The print service fails to be connected.
 * @since 13
 */
Print_ErrorCode OH_Print_StartPrintByNative(const char *printJobName,
                                            Print_PrintDocCallback printDocCallback,
                                            void *context);

/**
 * @brief Enumerates the print job states.
 *
 * @since 24
 */
typedef enum {
    /**
     * Successful print job.
     */
    OH_PRINT_JOB_SUCCEED = 0,
    /**
     * Print job failed.
     */
    OH_PRINT_JOB_FAIL = 1,
    /**
     * Print job canceled.
     */
    OH_PRINT_JOB_CANCEL = 2,
    /**
     * Print job blocked.
     */
    OH_PRINT_JOB_BLOCK = 3,
} OH_Print_JobState;

/**
 * @brief Defines a callback to be invoked when the print job state changes. Compared with **Print_OnJobStateChanged**
 * (which uses uint32_t to indicate the state and is available since API version 13), this callback uses the
 * **OH_Print_JobState** enumeration to indicate the job state, which is clearer in semantics and more secure in type.
 *
 * @param jobId Pointer to the print job ID.
 * @param state Print job state.
 * @since 24
 */
typedef void(*OH_Print_OnJobStateChanged)(const char *jobId, OH_Print_JobState state);

/**
 * @brief Starts a print job with the callback to be invoked when the print job state changes. This API can be used to
 * listen for the print job execution status, such as success, failure, and cancellation. Before calling this API,
 * ensure that the printer to be used is in the list of connected printers. If you do not need to listen for task
 * status changes, call **OH_Print_StartPrintJob**.
 *
 * @permission ohos.permission.PRINT
 * @param printJob Pointer to the {@link Print_PrintJob} instance. The value cannot be null. The referenced printer
 *     must have been connected using **OH_Print_ConnectPrinter**.
 * @param jobStateChangedCb Callback for the print task status, which is used to listen for status changes of the print
 *     task specified by **printJob**. The value cannot be null.
 * @return {@link PRINT_ERROR_NONE}: The operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The {@link ohos.permission.PRINT} permission is required.
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER}: **jobStateChangedCb** is null.
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE}: The callback function cannot be copied.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: The print service fails to be connected.
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE}: The print job struct fails to be created in the print service.
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER}: Failed to find properties of the specified printer.
 *     <br>{@link PRINT_ERROR_INVALID_PRINT_JOB}: **printJob** is null or internal parameters are invalid.
 * @since 24
 */
Print_ErrorCode OH_Print_StartPrintWithJobStateCallback(const Print_PrintJob *printJob,
                                                        OH_Print_OnJobStateChanged jobStateChangedCb);

#ifdef __cplusplus
}
#endif

#endif // OH_PRINT_H
/** @} */