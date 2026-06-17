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
     * Permission verification failed.
     */
    PRINT_ERROR_NO_PERMISSION = 201,
    /**
     * Invalid parameter.
     */
    PRINT_ERROR_INVALID_PARAMETER = 401,
    /**
     * Internal error.
     */
    PRINT_ERROR_GENERIC_FAILURE = 24300001,
    /**
     * RPC communication error.
     */
    PRINT_ERROR_RPC_FAILURE = 24300002,
    /**
     * Server error.
     */
    PRINT_ERROR_SERVER_FAILURE = 24300003,
    /**
     * Invalid extension.
     */
    PRINT_ERROR_INVALID_EXTENSION = 24300004,
    /**
     * Invalid printer.
     */
    PRINT_ERROR_INVALID_PRINTER = 24300005,
    /**
     * Invalid print job.
     */
    PRINT_ERROR_INVALID_PRINT_JOB = 24300006,
    /**
     * File I/O error.
     */
    PRINT_ERROR_FILE_IO = 24300007,
    /**
     * Unknown error.
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
 * @brief Defines a struct for the string list.
 *
 * @since 12
 */
typedef struct {
    /**
     * Number of strings.
     */
    uint32_t count;
    /**
     * Double pointer to the string array.
     */
    char **list;
} Print_StringList;

/**
 * @brief Defines a struct for the printer property.
 *
 * @since 12
 */
typedef struct {
    /**
     * Property key.
     */
    char *key;
    /**
     * Property value.
     */
    char *value;
} Print_Property;

/**
 * @brief Defines a struct for the printer property list.
 *
 * @since 12
 */
typedef struct {
    /**
     * Number of properties.
     */
    uint32_t count;
    /**
     * Pointer to the property array.
     */
    Print_Property *list;
} Print_PropertyList;

/**
 * @brief Defines a struct for the printing resolution in dpi.
 *
 * @since 12
 */
typedef struct {
    uint32_t horizontalDpi;
    uint32_t verticalDpi;
} Print_Resolution;

/**
 * @brief Defines a struct for the page margin to print.
 *
 * @since 12
 */
typedef struct {
    /**
     * Left margin, in millimeters.
     */
    uint32_t leftMargin;
    /**
     * Top margin, in millimeters.
     */
    uint32_t topMargin;
    /**
     * Right margin, in millimeters.
     */
    uint32_t rightMargin;
    /**
     * Bottom margin, in millimeters.
     */
    uint32_t bottomMargin;
} Print_Margin;

/**
 * @brief Defines a struct for the page size.
 *
 * @since 12
 */
typedef struct {
    /**
     * Page ID.
     */
    char *id;
    /**
     * Page name.
     */
    char *name;
    /**
     * Page width, in millimeters.
     */
    uint32_t width;
    /**
     * Page height, in millimeters.
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
     * Color mode.
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
     * Draft.
     */
    PRINT_QUALITY_DRAFT = 3,
    /**
     * Normal quality.
     */
    PRINT_QUALITY_NORMAL = 4,
    /**
     * High quality.
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
 * @brief Defines a struct for the printer capabilities.
 *
 * @since 12
 */
typedef struct {
    /**
     * Array of supported color modes.
     */
    Print_ColorMode *supportedColorModes;
    /**
     * Number of supported color modes.
     */
    uint32_t supportedColorModesCount;
    /**
     * Array of supported duplex modes.
     */
    Print_DuplexMode *supportedDuplexModes;
    /**
     * Number of supported duplex modes.
     */
    uint32_t supportedDuplexModesCount;
    /**
     * Array of supported page sizes.
     */
    Print_PageSize *supportedPageSizes;
    /**
     * Number of supported page sizes.
     */
    uint32_t supportedPageSizesCount;
    /**
     * Array of supported print media types in JSON string format.
     */
    char *supportedMediaTypes;
    /**
     * Array of supported print qualities.
     */
    Print_Quality *supportedQualities;
    /**
     * Number of supported print qualities.
     */
    uint32_t supportedQualitiesCount;
    /**
     * Array of supported paper sources in JSON string format.
     */
    char *supportedPaperSources;
    /**
     * Supported number of copies.
     */
    uint32_t supportedCopies;
    /**
     * Array of supported printer resolutions.
     */
    Print_Resolution *supportedResolutions;
    /**
     * Supported number of printer resolutions.
     */
    uint32_t supportedResolutionsCount;
    /**
     * Array of supported orientations.
     */
    Print_OrientationMode *supportedOrientations;
    /**
     * Supported number of orientations.
     */
    uint32_t supportedOrientationsCount;
    /**
     * Advanced capabilities in JSON format.
     */
    char *advancedCapability;
} Print_PrinterCapability;

/**
 * @brief Defines a struct for the default property value.
 *
 * @since 12
 */
typedef struct {
    /**
     * Default color mode.
     */
    Print_ColorMode defaultColorMode;
    /**
     * Default duplex mode.
     */
    Print_DuplexMode defaultDuplexMode;
    /**
     * Default media type.
     */
    char *defaultMediaType;
    /**
     * Default page size ID.
     */
    char *defaultPageSizeId;
    /**
     * Default margin.
     */
    Print_Margin defaultMargin;
    /**
     * Default paper source.
     */
    char *defaultPaperSource;
    /**
     * Default print quality.
     */
    Print_Quality defaultPrintQuality;
    /**
     * Default number of copies.
     */
    uint32_t defaultCopies;
    /**
     * Default printer resolution.
     */
    Print_Resolution defaultResolution;
    /**
     * Default orientation.
     */
    Print_OrientationMode defaultOrientation;
    /**
     * Other default values in JSON format.
     */
    char *otherDefaultValues;
} Print_DefaultValue;

/**
 * @brief Defines a struct for the printer information.
 *
 * @since 12
 */
typedef struct {
    /**
     * Printer state.
     */
    Print_PrinterState printerState;
    /**
     * Printer capability.
     */
    Print_PrinterCapability capability;
    /**
     * Default property value of the printer.
     */
    Print_DefaultValue defaultValue;
    /**
     * Default printer.
     */
    bool isDefaultPrinter;
    /**
     * Printer ID.
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
     * Printer URI.
     */
    char *printerUri;
    /**
     * Details in JSON format.
     * <br>The supported keys are as follows:
     * <br>- **printerAlias**: string type, indicating the printer alias. **Since**: 24
     * <br>- **vendorId**: int type, indicating the USB vendor ID of the printer. **Since**: 12
     * <br>- **productId**: int type, indicating the USB product ID of the printer. **Since**: 12
     * <br>- **protocol**: string array, indicating the list of protocols detected for the printer. **Since**: 24
     * <br>- **ipp**: string type, indicating the printer URI for the detected IPP protocol. **Since**: 24
     * <br>- **ipps**: string type, indicating the printer URI for the detected IPPS protocol. **Since**: 24
     * <br>- **lpd**: string type, indicating the printer URI for the detected LPD protocol. **Since**: 24
     * <br>- **socket**: string type, indicating the printer URI for the detected Socket protocol. **Since**: 24
     */
    char *detailInfo;
} Print_PrinterInfo;

/**
 * @brief Defines a struct for the print job.
 *
 * @since 12
 */
typedef struct {
    /**
     * Job name.
     */
    char *jobName;
    /**
     * Array of file descriptors to be printed.
     */
    uint32_t *fdList;
    /**
     * Number of file descriptors to be printed.
     */
    uint32_t fdListCount;
    /**
     * Printer ID.
     */
    char *printerId;
    /**
     * Number of copies to print.
     */
    uint32_t copyNumber;
    /**
     * Paper source.
     */
    char *paperSource;
    /**
     * Media type.
     */
    char *mediaType;
    /**
     * Page size ID.
     */
    char *pageSizeId;
    /**
     * Color mode.
     */
    Print_ColorMode colorMode;
    /**
     * Duplex mode.
     */
    Print_DuplexMode duplexMode;
    /**
     * Print resolution, in dpi.
     */
    Print_Resolution resolution;
    /**
     * Page margin.
     */
    Print_Margin printMargin;
    /**
     * Whether to print without margins.
     */
    bool borderless;
    /**
     * Orientation mode.
     */
    Print_OrientationMode orientationMode;
    /**
     * Print quality.
     */
    Print_Quality printQuality;
    /**
     * Document format.
     */
    Print_DocumentFormat documentFormat;
    /**
     * Advanced options in JSON format.<br>The supported keys are as follows:<br>- **isReverse**: Boolean type,
     * indicating whether to print in reverse order.<br>- **isCollate**: Boolean type, indicating whether to print
     * copies one by one.
     */
    char *advancedOptions;
} Print_PrintJob;

/**
 * @brief Defines a struct for the page range to print.
 *
 * @since 13
 */
typedef struct {
    /**
     * Start page.
     */
    uint32_t startPage;
    /**
     * End page.
     */
    uint32_t endPage;
    /**
     * Length of the page array.
     */
    uint32_t pagesArrayLen;
    /**
     * Page array.
     */
    uint32_t *pagesArray;
} Print_Range;

/**
 * @brief Defines a struct for the print attributes.
 *
 * @since 13
 */
typedef struct {
    /**
     * Page range.
     */
    Print_Range pageRange;
    /**
     * Page size.
     */
    Print_PageSize pageSize;
    /**
     * Page margin.
     */
    Print_Margin pageMargin;
    /**
     * Number of copies to print.
     */
    uint32_t copyNumber;
    /**
     * Duplex mode.
     */
    uint32_t duplexMode;
    /**
     * Color mode.
     */
    uint32_t colorMode;
    /**
     * Whether pages are printed in sequential order.<br>The value **true** indicates that pages are printed in
     * sequential order, and **false** indicates the opposite.
     */
    bool isSequential;
    /**
     * Whether pages are printed in landscape mode.<br>The value **true** indicates that pages are printed in landscape
     * mode, and **false** indicates that pages are printed in portrait mode.
     */
    bool isLandscape;
    /**
     * Whether the printing has an option flag.<br>The value **true** indicates that the printing has an option flag,
     * and **false** indicates the opposite.
     */
    bool hasOption;
    /** Print options. */
    char options[256];
} Print_PrintAttributes;

/**
 * @brief Defines a callback used to return the file write-back result.
 *
 * @param jobId Pointer to the print job ID.
 * @param code File write-back result.
 * @since 13
 */
typedef void(*Print_WriteResultCallback)(const char *jobId, uint32_t code);

/**
 * @brief Defines a callback to be invoked when the file write-back starts.
 *
 * @param jobId Pointer to the print job ID.
 * @param fd File descriptor to write.
 * @param oldAttrs Pointer to the old attribute.
 * @param newAttrs Pointer to the new attribute.
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
 * @param state Print job state.
 * @since 13
 */
typedef void(*Print_OnJobStateChanged)(const char *jobId, uint32_t state);

/**
 * @brief Defines a struct for the print job state callback.
 *
 * @since 13
 */
typedef struct {
    /**
     * Callback to be invoked when the file write-back starts.
     */
    Print_OnStartLayoutWrite startLayoutWriteCb;
    /**
     * Callback to be invoked when the print job state changes.
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
 *
 * @permission {@code ohos.permission.PRINT}
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The ohos.permission.PRINT permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: Failed to connect to the print service.
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE}: Failed to start the CUPS service.
 * @since 12
 */
Print_ErrorCode OH_Print_Init();

/**
 * @brief Disconnects from the print service, dismisses the previous callback, and releases the print client resources.
 *
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>Currently, no other error codes will be returned.
 * @since 12
 */
Print_ErrorCode OH_Print_Release();

/**
 * @brief Starts printer discovery.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param callback {@link Print_PrinterDiscoveryCallback} to be invoked when a printer is discovered.
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The ohos.permission.PRINT permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: Failed to connect to the print service.
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE}: Failed to query the print extension list from the BMS.
 *     <br>{@link PRINT_ERROR_INVALID_EXTENSION}: No available print extension is found.
 * @since 12
 */
Print_ErrorCode OH_Print_StartPrinterDiscovery(Print_PrinterDiscoveryCallback callback);

/**
 * @brief Stops printer discovery.
 *
 * @permission {@code ohos.permission.PRINT}
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The ohos.permission.PRINT permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: Failed to connect to the print service.
 * @since 12
 */
Print_ErrorCode OH_Print_StopPrinterDiscovery();

/**
 * @brief Connects to a printer by the printer ID.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId Pointer to the ID of the printer to be connected.
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The ohos.permission.PRINT permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: Failed to connect to the print service.
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER}: Printer does not exist in the list of discovered printers.
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE}: Failed to find the printer extension.
 * @since 12
 */
Print_ErrorCode OH_Print_ConnectPrinter(const char *printerId);

/**
 * @brief Starts a print job.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printJob Pointer to the {@link Print_PrintJob} instance of the specified print job information.
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The ohos.permission.PRINT permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: Failed to connect to the print service.
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER}: Printer does not exist in the list of connected printers.
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE}: Failed to create a print job in the print service.
 *     <br>{@link PRINT_ERROR_INVALID_PRINT_JOB}: Failed to find the specified task in the task queue.
 * @since 12
 */
Print_ErrorCode OH_Print_StartPrintJob(const Print_PrintJob *printJob);

/**
 * @brief Registers a listener for printer changes.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param callback {@link Print_PrinterChangeCallback} to be registered.
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The ohos.permission.PRINT permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: Failed to connect to the print service.
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
 * @brief Queries the list of added printers.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerIdList Pointer to the {@link Print_StringList} instance that stores the queried printer ID list.
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The ohos.permission.PRINT permission is required.
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER}: printerIdList is null.
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER}: Failed to query any connected printers.
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE}: Failed to copy printer ID list.
 * @since 12
 */
Print_ErrorCode OH_Print_QueryPrinterList(Print_StringList *printerIdList);

/**
 * @brief Releases the memory used to query the printer list.
 *
 * @param printerIdList Pointer to the queried printer ID list.
 * @since 12
 */
void OH_Print_ReleasePrinterList(Print_StringList *printerIdList);

/**
 * @brief Queries printer information by printer ID.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId Pointer to the printer ID to be queried.
 * @param printerInfo Double pointer to the {@link Print_PrinterInfo}.
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The ohos.permission.PRINT permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: Failed to connect to the print service.
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER}: The printerId or printerInfo is null.
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER}: Failed to find the specified printer in the list of connected printers.
 * @since 12
 */
Print_ErrorCode OH_Print_QueryPrinterInfo(const char *printerId, Print_PrinterInfo **printerInfo);

/**
 * @brief Releases the memory used to query the printer information.
 *
 * @param printerInfo Pointer to the queried printer information.
 * @since 12
 */
void OH_Print_ReleasePrinterInfo(Print_PrinterInfo *printerInfo);

/**
 * @brief Starts the printer management window of the system.
 *
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE}: Failed to start the printer management window.
 * @since 12
 */
Print_ErrorCode OH_Print_LaunchPrinterManager();

/**
 * @brief Queries the printer properties based on the list of property keys.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId Pointer to the printer ID to be queried.
 * @param propertyKeyList Pointer to the list of property keys.
 * @param propertyList Pointer to the queried printer properties.
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The ohos.permission.PRINT permission is required.
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER}: One of the parameters is null or the key list is empty.
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER}: Failed to find properties of the specified printer.
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE}: Failed to copy printer properties.
 * @since 12
 */
Print_ErrorCode OH_Print_QueryPrinterProperties(const char *printerId, const Print_StringList *propertyKeyList,
    Print_PropertyList *propertyList);

/**
 * @brief Releases the memory used to query the printer properties.
 *
 * @param propertyList Pointer to the queried printer properties.
 * @since 12
 */
void OH_Print_ReleasePrinterProperties(Print_PropertyList *propertyList);

/**
 * @brief Updates the printer properties based on the KV pairs.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId Pointer to the printer ID.
 * @param propertyList Pointer to the list of printer properties to be updated.
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The ohos.permission.PRINT permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: Failed to connect to the print service.
 * @since 12
 */
Print_ErrorCode OH_Print_UpdatePrinterProperties(const char *printerId, const Print_PropertyList *propertyList);

/**
 * @brief Restores printer properties to the default settings based on the property key list.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printerId Pointer to the printer ID.
 * @param propertyKeyList Pointer to the property key list.
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The ohos.permission.PRINT permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: Failed to connect to the print service.
 * @since 12
 */
Print_ErrorCode OH_Print_RestorePrinterProperties(const char *printerId, const Print_StringList *propertyKeyList);

/**
 * @brief Starts the printing dialog box.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param printJobName Pointer to the name of the print job.
 * @param printDocCallback Callback used to return the file state.
 * @param context Pointer to the context of the caller.
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The ohos.permission.PRINT permission is required.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: Failed to connect to the print service.
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
 * @brief Defines a callback to be invoked when the print job state changes.
 *
 * @param jobId Pointer to the print job ID.
 * @param state Print job state.
 * @since 24
 */
typedef void(*OH_Print_OnJobStateChanged)(const char *jobId, OH_Print_JobState state);

/**
 * @brief Starts a print job with the callback to be invoked when the print job state changes.
 *
 * @permission ohos.permission.PRINT
 * @param printJob Pointer to the print job struct.
 * @param jobStateChangedCb Callback to be invoked when the print job state changes.
 * @return {@link PRINT_ERROR_NONE}: Operation is successful.
 *     <br>{@link PRINT_ERROR_NO_PERMISSION}: The {@link ohos.permission.PRINT} permission is required.
 *     <br>{@link PRINT_ERROR_INVALID_PARAMETER}: The jobStateChangedCb is null.
 *     <br>{@link PRINT_ERROR_GENERIC_FAILURE}: The callback function cannot be copied.
 *     <br>{@link PRINT_ERROR_RPC_FAILURE}: Failed to connect to the print service.
 *     <br>{@link PRINT_ERROR_SERVER_FAILURE}: The print job struct cannot be created in the print service.
 *     <br>{@link PRINT_ERROR_INVALID_PRINTER}: Failed to find the specified printer in the list of connected printers.
 *     <br>{@link PRINT_ERROR_INVALID_PRINT_JOB}: Print job cannot be found in the job queue.
 * @since 24
 */
Print_ErrorCode OH_Print_StartPrintWithJobStateCallback(const Print_PrintJob *printJob,
                                                        OH_Print_OnJobStateChanged jobStateChangedCb);

#ifdef __cplusplus
}
#endif

#endif // OH_PRINT_H
/** @} */