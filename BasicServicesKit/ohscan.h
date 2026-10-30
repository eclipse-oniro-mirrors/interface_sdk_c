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
 * @brief Declares APIs for discovering and connecting to scanners, scanning images, obtaining the image scanning
 * progress, and setting scanner parameters. This module can be used to integrate scanner-related operations into an
 * app.
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
 * @brief Enumerates the error codes.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Operation successful.
     */
    SCAN_ERROR_NONE = 0,

    /**
     * Permission verification failed. Request the required permissions.
     */
    SCAN_ERROR_NO_PERMISSION = 201,

    /**
     * Invalid parameter. For example, the pointer or string is null. Check whether the input parameter is valid.
     */
    SCAN_ERROR_INVALID_PARAMETER = 401,

    /**
     * A generic internal error occurred. Try again later.
     */
    SCAN_ERROR_GENERIC_FAILURE = 24300101,

    /**
     * RPC communication error. Check the scanning service status and try again.
     */
    SCAN_ERROR_RPC_FAILURE = 24300102,

    /**
     * An error occurred during scanning. Try again later.
     */
    SCAN_ERROR_SERVER_FAILURE = 24300103,

    /**
     * The operation is not supported. Check whether the current scanner supports this operation.
     */
    SCAN_ERROR_UNSUPPORTED = 24300104,

    /**
     * The operation has been canceled. Start scanning again.
     */
    SCAN_ERROR_CANCELED = 24300105,

    /**
     * The scanner is busy. Try again later.
     */
    SCAN_ERROR_DEVICE_BUSY = 24300106,

    /**
     * Invalid data (for example, no device is available when the scanner is started). Check the scanner connection
     * status.
     */
    SCAN_ERROR_INVALID = 24300107,

    /**
     * Paper jammed at the paper feeder. Remove the jammed paper and try again.
     */
    SCAN_ERROR_JAMMED = 24300108,

    /**
     * Out of paper. Place paper in the feeder and try again.
     */
    SCAN_ERROR_NO_DOCS = 24300109,

    /**
     * The scanner cover is open. Close the cover and try again.
     */
    SCAN_ERROR_COVER_OPEN = 24300110,

    /**
     * Scanner I/O error. Check the scanner connection and try again.
     */
    SCAN_ERROR_IO_ERROR = 24300111,

    /**
     * Insufficient memory. Release resources and try again.
     */
    SCAN_ERROR_NO_MEMORY = 24300112
} Scan_ErrorCode;

/**
 * @brief Represents the scanner device information, including the scanner ID, manufacturer, model, discovery mode, and
 * serial number. It is used to obtain device details during the scanner discovery process. You can obtain this struct
 * using the scanner discovery API to select the target scanner for scanning. For details about the design logic of the
 * related module, see {@link OH_Scan}.
 *
 * @since 12
 */
typedef struct {
    /**
     * Scanner ID.
     */
    const char *scannerId;
    /**
     * Scanner manufacturer.
     */
    const char *manufacturer;
    /**
     * Scanner model.
     */
    const char *model;
    /**
     * Scanner discovery mode, indicating how the scanner is discovered by the system. The value **TCP** indicates that
     * the scanner is discovered over the network, and the value **USB** indicates that the scanner is discovered
     * through the USB connection.
     */
    const char *discoverMode;
    /**
     * Scanner serial number.
     */
    const char *serialNumber;
} Scan_ScannerDevice;

/**
 * @brief Defines the progress of scanning a picture by the scanner. This struct contains the **progress**, **fd** (
 * file descriptor), and **isFinal** (whether the picture is the last one to be scanned) attributes. It can be used to
 * track the picture scanning status in real time and obtain the scanning result file in an app. For details about the
 * implementation mechanism, see {@link OH_Scan}.
 *
 * @since 12
 */
typedef struct {
    /**
     * Picture scanning progress, in percentage. The value range is [0, 100]. The value **0** indicates that the
     * scanning starts, and the value **100** indicates that the scanning is complete.
     */
    int32_t progress;
    /**
     * File descriptor of the scanned picture, which is used to read the image data transmitted by the scanner. **fd**
     * is valid only when the value of **progress** is **100**.
     */
    int32_t fd;
    /**
     * Whether the picture is the last one to be scanned. The value **true** indicates that the picture is the last one
     * to be scanned, and **false** indicates that the picture is not the last one. **isFinal** is valid only when
     * the value of **progress** is **100**.
     */
    bool isFinal;
} Scan_PictureScanProgress;

/**
 * @brief Defines the configurable parameters of a scanner. You can configure the title, description, value range, and
 * number of options for each parameter. Each option includes the **titles**, **descriptions**, and **ranges** fields,
 * which are stored as parallel arrays. The **optionCount** field indicates the total number of options. You can use
 * the index i (which must be within the range of [0, **optionCount**)) to access **titles[i]**, **descriptions[i]**,
 * and **ranges[i]** simultaneously to obtain the complete information about option i. Ensure that the array lengths of
 * **titles**, **descriptions**, and **ranges** are the same and equal to the value of **optionCount**. Otherwise, the
 * complete information about the options may not be obtained correctly.
 *
 * @since 12
 */
typedef struct {
    /**
     * Option titles.
     */
    char **titles;
    /**
     * Option descriptions.
     */
    char **descriptions;
    /**
     * Ranges of options.
     */
    char **ranges;
    /**
     * Number of options.
     */
    int32_t optionCount;
} Scan_ScannerOptions;

/**
 * @brief Callback for scanner discovery, which is registered using {@link OH_Scan_StartScannerDiscovery}.
 *
 * @param devices List of all discovered scanners. The memory pointed to by the **devices** pointer will be released
 *     when the callback ends.
 * @param deviceCount Number of scanners discovered.
 * @since 12
 */
typedef void (*Scan_ScannerDiscoveryCallback)(Scan_ScannerDevice** devices, int32_t deviceCount);

/**
 * @brief Initiates the scan service, initializes the scan client, and connects the client to the scan service. Call
 * this API to initialize the scan service before calling other scan APIs. After using the service, call
 * {@link OH_Scan_Exit} to release resources.
 *
 * @permission {@code ohos.permission.PRINT}
 * @return {@link SCAN_ERROR_NONE}: The operation is successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: The permission is denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: An error occurs during the scanning.
 * @since 12
 */
int32_t OH_Scan_Init();

/**
 * @brief Starts scanner discovery and registers a callback used to process the discovered scanners. Call
 * {@link OH_Scan_Exit} to unregister the callback.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param callback {@link Scan_ScannerDiscoveryCallback} for the scanner discovery event. The value cannot be null.
 * @return {@link SCAN_ERROR_NONE}: The operation is successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: The permission is denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: An error occurs during the scanning.
 * @since 12
 */
int32_t OH_Scan_StartScannerDiscovery(Scan_ScannerDiscoveryCallback callback);

/**
 * @brief Opens a scanner. After using the scanner, call {@link OH_Scan_CloseScanner} to close it.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId ID of the scanner to connect. The value must be the ID of a valid scanner that has been discovered.
 * @return {@link SCAN_ERROR_NONE}: The operation is successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: The permission is denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: An error occurs during the scanning.
 *     <br>{@link SCAN_ERROR_DEVICE_BUSY}: The scanner is busy.
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER}: The input parameter is invalid.
 *     <br>{@link SCAN_ERROR_IO_ERROR}: An error occurs during the communication with the scanner.
 *     <br>{@link SCAN_ERROR_NO_MEMORY}: The memory is insufficient.
 * @since 12
 */
int32_t OH_Scan_OpenScanner(const char* scannerId);

/**
 * @brief Closes a connected scanner. Generally, this API is called to disconnect the scanner after it is used.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId ID of the scanner to disconnect. The value must be the ID of a valid scanner that has been
 *     connected.
 * @return {@link SCAN_ERROR_NONE}: The operation is successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: The permission is denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: An error occurs during the scanning.
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER}: The input parameter is invalid.
 * @since 12
 */
int32_t OH_Scan_CloseScanner(const char* scannerId);

/**
 * @brief Obtains scanner settings. The memory to which the returned struct pointer points is automatically released
 * when {@link OH_Scan_Exit} is called. Only one copy of each scanner model is stored in the memory.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId ID of the scanner whose parameters are to be obtained. The value must be the ID of a valid scanner
 *     that has been connected.
 * @param errorCode The value cannot be null. Pointer to the error code. If the operation is successful,
 *     {@link SCAN_ERROR_NONE} is returned; otherwise, a specific error code is returned. For details, see
 *     {@link Scan_ErrorCode}.
 * @return Pointer to the scanner parameter struct when the operation is successful, which can be used to obtain and
 *     set scanner parameters. **NULL** is returned when the operation fails.
 * @since 12
 */
Scan_ScannerOptions* OH_Scan_GetScannerParameter(const char* scannerId, int32_t* errorCode);

/**
 * @brief Sets the option parameters of the scanner. The input options and values are obtained from
 * {@link OH_Scan_GetScannerParameter}.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId ID of the scanner whose options are to be set. The value must be the ID of a valid scanner that has
 *     been connected.
 * @param option ID of the option to be set. The value is obtained from {@link Scan_ScannerOptions}. The value ranges
 *     from 0 to **optionCount** – 1.
 * @param value Pointer to the option value to be set. The valid value is obtained from **ranges** of
 *     {@link Scan_ScannerOptions}.
 * @return {@link SCAN_ERROR_NONE}: The operation is successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: The permission is denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: An error occurs during the scanning.
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER}: The input parameter is invalid.
 * @since 12
 */
int32_t OH_Scan_SetScannerParameter(const char* scannerId, const int32_t option, const char* value);

/**
 * @brief Starts a scanning task of the scanner. After the scanning service is successfully initialized and parameters
 * have been set after the scanner is connected, you can call this API to start scanning. During scanning, you can call
 * {@link OH_Scan_GetPictureScanProgress} to obtain the scanning progress and call {@link OH_Scan_CancelScan} to cancel
 * the scanning.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId ID of the scanner whose scanning task is to be started. The scanner must be a valid scanner that
 *     has been connected.
 * @param batchMode Whether to start the scanner in batch processing mode. **true** indicates that the batch processing
 *     mode is enabled, and the scanner can continuously scan multiple pages of documents (usually through the paper
 *     feeder). **false** indicates that the batch processing mode is disabled, and only a single page is scanned.
 * @return {@link SCAN_ERROR_NONE}: The operation is successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: The permission is denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: An error occurs during the scanning.
 *     <br>{@link SCAN_ERROR_JAMMED}: paper jammed in the feeder.
 *     <br>{@link SCAN_ERROR_NO_DOCS}: out of paper.
 *     <br>{@link SCAN_ERROR_COVER_OPEN}: scanner cover open.
 *     <br>{@link SCAN_ERROR_IO_ERROR}: An error occurs during the communication with the scanner.
 *     <br>{@link SCAN_ERROR_NO_MEMORY}: The memory is insufficient.
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER}: The input parameter is invalid.
 *     <br>{@link SCAN_ERROR_DEVICE_BUSY}: The scanner is busy. Try again later.
 * @since 12
 */
int32_t OH_Scan_StartScan(const char* scannerId, bool batchMode);

/**
 * @brief Cancels an ongoing scanning task of the scanner.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId ID of the scanner whose scanning task is to be canceled. The scanner must be a valid scanner that
 *     has been connected.
 * @return {@link SCAN_ERROR_NONE}: The operation is successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: The permission is denied.
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER}: The input parameter is invalid.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: An error occurs during the scanning.
 * @since 12
 */
int32_t OH_Scan_CancelScan(const char* scannerId);

/**
 * @brief Obtains the progress of scanning a picture by the scanner.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId ID of the scanner whose image scanning progress is to be queried. The scanner must be a valid
 *     scanner that has been connected.
 * @param prog {@link Scan_PictureScanProgress} of the scanned image. A non-null value must be passed. The scanning
 *     progress will be written into the struct pointed to by the **prog** pointer.
 * @return {@link SCAN_ERROR_NONE}: The scanner has successfully queried the image scan progress.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: The permission is denied.
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER}: The input parameter is invalid.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: An error occurs during the scanning.
 *     <br>{@link SCAN_ERROR_JAMMED}: paper jammed in the feeder.
 *     <br>{@link SCAN_ERROR_NO_DOCS}: out of paper.
 *     <br>{@link SCAN_ERROR_COVER_OPEN}: scanner cover open.
 *     <br>{@link SCAN_ERROR_IO_ERROR}: An error occurs during the communication with the scanner.
 *     <br>{@link SCAN_ERROR_NO_MEMORY}: The memory is insufficient.
 *     <br>{@link SCAN_ERROR_DEVICE_BUSY}: The scanner is busy. Try again later.
 * @since 12
 */
int32_t OH_Scan_GetPictureScanProgress(const char* scannerId, Scan_PictureScanProgress* prog);

/**
 * @brief Exits the scan service, releases the memory of the scan framework, and deregisters the scanner discovery
 * callback. After the scan service exits, other scan APIs cannot be called.
 *
 * @permission {@code ohos.permission.PRINT}
 * @return {@link SCAN_ERROR_NONE}: The operation is successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: The permission is denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: An error occurs during the scanning.
 * @since 12
 */
int32_t OH_Scan_Exit();

#ifdef __cplusplus
}
#endif
#endif  // OH_SCAN_H

/** @} */