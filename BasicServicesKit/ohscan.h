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
 * @brief Declares APIs for discovering and connecting to scanners, scanning pictures, querying the scan progress, and
 * setting parameters for scanning.
 *
 * @library libohscan.so
 * @kit BasicServicesKit
 * @syscap SystemCapability.Print.PrintFramework
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
     * Permission verification failed.
     */
    SCAN_ERROR_NO_PERMISSION = 201,

    /**
     * Invalid parameter. For example, the pointer or string is null.
     */
    SCAN_ERROR_INVALID_PARAMETER = 401,

    /**
     * Internal error.
     */
    SCAN_ERROR_GENERIC_FAILURE = 24300101,

    /**
     * RPC communication error.
     */
    SCAN_ERROR_RPC_FAILURE = 24300102,

    /**
     * Server error.
     */
    SCAN_ERROR_SERVER_FAILURE = 24300103,

    /**
     * Unsupported operation.
     */
    SCAN_ERROR_UNSUPPORTED = 24300104,

    /**
     * Operation canceled.
     */
    SCAN_ERROR_CANCELED = 24300105,

    /**
     * Device busy.
     */
    SCAN_ERROR_DEVICE_BUSY = 24300106,

    /**
     * Invalid data (for example, no device is available when the scanner is started).
     */
    SCAN_ERROR_INVALID = 24300107,

    /**
     * Paper jam in feeder.
     */
    SCAN_ERROR_JAMMED = 24300108,

    /**
     * Out of paper.
     */
    SCAN_ERROR_NO_DOCS = 24300109,

    /**
     * Scanner cover open.
     */
    SCAN_ERROR_COVER_OPEN = 24300110,

    /**
     * Scanner I/O error.
     */
    SCAN_ERROR_IO_ERROR = 24300111,

    /**
     * Insufficient memory.
     */
    SCAN_ERROR_NO_MEMORY = 24300112
} Scan_ErrorCode;

/**
 * @brief Defines scanner information.
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
     * Discovery mode of the scanner.
     */
    const char *discoverMode;
    /**
     * Scanner serial number.
     */
    const char *serialNumber;
} Scan_ScannerDevice;

/**
 * @brief Defines the progress of scanning a picture by the scanner.
 *
 * @since 12
 */
typedef struct {
    /**
     * Picture scanning progress, in percentage. The value ranges from 0 to 100.
     */
    int32_t progress;
    /**
     * Scanner file handle.
     */
    int32_t fd;
    /**
     * Whether the picture is the last one to be scanned. The value **true** indicates that the picture is the last one
     * to be scanned, and **false** indicates the opposite.
     */
    bool isFinal;
} Scan_PictureScanProgress;

/**
 * @brief Defines all parameter options of a scanner.
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
     * Number of configurable parameter options.
     */
    int32_t optionCount;
} Scan_ScannerOptions;

/**
 * @brief Discovers scanners. The memory pointed to by the pointer registered via {@link OH_Scan_StartScannerDiscovery}
 * will be released when the callback function ends.
 *
 * @param devices Double pointer to the list of all discovered scanners.
 * @param deviceCount Number of scanners discovered.
 * @since 12
 */
typedef void (*Scan_ScannerDiscoveryCallback)(Scan_ScannerDevice** devices, int32_t deviceCount);

/**
 * @brief Initiates the scan service, initializes the scan client, and connects the client to the scan service.
 *
 * @permission {@code ohos.permission.PRINT}
 * @return {@link SCAN_ERROR_NONE}: operation successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: permission denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: server error.
 * @since 12
 */
int32_t OH_Scan_Init();

/**
 * @brief Starts scanner discovery and registers a callback used to process the discovered scanners.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param callback {@link Scan_ScannerDiscoveryCallback} used to discover scanners.
 * @return {@link SCAN_ERROR_NONE}: operation successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: permission denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: server error.
 * @since 12
 */
int32_t OH_Scan_StartScannerDiscovery(Scan_ScannerDiscoveryCallback callback);

/**
 * @brief Opens a scanner.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId Pointer to the scanner ID.
 * @return {@link SCAN_ERROR_NONE}: operation successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: permission denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: server error.
 *     <br>{@link SCAN_ERROR_DEVICE_BUSY}: device busy.
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER}: invalid parameter.
 *     <br>{@link SCAN_ERROR_IO_ERROR}: scanner I/O error.
 *     <br>{@link SCAN_ERROR_NO_MEMORY}: insufficient memory.
 * @since 12
 */
int32_t OH_Scan_OpenScanner(const char* scannerId);

/**
 * @brief Closes a connected scanner.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId Pointer to the scanner ID.
 * @return {@link SCAN_ERROR_NONE}: operation successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: permission denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: server error.
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER}: invalid parameter.
 * @since 12
 */
int32_t OH_Scan_CloseScanner(const char* scannerId);

/**
 * @brief Obtains the scanner setting options. The memory to which the returned struct pointer points is automatically
 * released when {@link OH_Scan_Exit} is called. Only one copy of each scanner model is stored in the memory.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId Pointer to the scanner ID.
 * @param errorCode Pointer to the error code. If the operation is successful, {@link SCAN_ERROR_NONE} is returned;
 *     otherwise, a specific error code is returned. For details, see {@link Scan_ErrorCode}.
 * @return Pointer to an {@link Scan_ScannerOptions} instance, or NULL if it fails to create.
 * @since 12
 */
Scan_ScannerOptions* OH_Scan_GetScannerParameter(const char* scannerId, int32_t* errorCode);

/**
 * @brief Sets the option parameters of a scanner. The option values are obtained through the
 * {@link OH_Scan_GetScannerParameter} API.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId Pointer to the scanner ID.
 * @param option ID of the option to be set. The value, obtained from {@link Scan_ScannerOptions}, ranges from 0 to
 *     *optionCount* – 1.
 * @param value Pointer to the option value to be set. The valid value is obtained from **ranges** of
 *     {@link Scan_ScannerOptions}.
 * @return {@link SCAN_ERROR_NONE}: operation successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: permission denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: server error.
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER}: invalid parameter.
 * @since 12
 */
int32_t OH_Scan_SetScannerParameter(const char* scannerId, const int32_t option, const char* value);

/**
 * @brief Starts scanning.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId Pointer to the scanner ID.
 * @param batchMode Whether to start the scanner in batch processing mode.
 * @return {@link SCAN_ERROR_NONE}: operation successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: permission denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: server error.
 *     <br>{@link SCAN_ERROR_JAMMED}: paper jam in feeder.
 *     <br>{@link SCAN_ERROR_NO_DOCS}: out of paper.
 *     <br>{@link SCAN_ERROR_COVER_OPEN}: scanner cover open.
 *     <br>{@link SCAN_ERROR_IO_ERROR}: scanner I/O error.
 *     <br>{@link SCAN_ERROR_NO_MEMORY}: insufficient memory.
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER}: invalid parameter.
 *     <br>{@link SCAN_ERROR_DEVICE_BUSY}: device busy.
 * @since 12
 */
int32_t OH_Scan_StartScan(const char* scannerId, bool batchMode);

/**
 * @brief Cancels scanning.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId Pointer to the scanner ID.
 * @return {@link SCAN_ERROR_NONE}: operation successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: permission denied.
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER}: invalid parameter.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: server error.
 * @since 12
 */
int32_t OH_Scan_CancelScan(const char* scannerId);

/**
 * @brief Obtains the progress of scanning a picture by the scanner. A non-null value must be passed. The scan progress
 * will be written into the struct pointed to by the pointer.
 *
 * @permission {@code ohos.permission.PRINT}
 * @param scannerId Pointer to the scanner ID.
 * @param prog Pointer to {@link Scan_PictureScanProgress}. The value cannot be empty.
 * @return {@link SCAN_ERROR_NONE}: operation successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: permission denied.
 *     <br>{@link SCAN_ERROR_INVALID_PARAMETER}: invalid parameter.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: server error.
 *     <br>{@link SCAN_ERROR_JAMMED}: paper jam in feeder.
 *     <br>{@link SCAN_ERROR_NO_DOCS}: out of paper.
 *     <br>{@link SCAN_ERROR_COVER_OPEN}: scanner cover open.
 *     <br>{@link SCAN_ERROR_IO_ERROR}: scanner I/O error.
 *     <br>{@link SCAN_ERROR_NO_MEMORY}: insufficient memory.
 *     <br>{@link SCAN_ERROR_DEVICE_BUSY}: device busy.
 * @since 12
 */
int32_t OH_Scan_GetPictureScanProgress(const char* scannerId, Scan_PictureScanProgress* prog);

/**
 * @brief Exits the scan service, releases the memory of the scan framework, and deregisters the scanner discovery
 * callback.
 *
 * @permission {@code ohos.permission.PRINT}
 * @return {@link SCAN_ERROR_NONE}: operation successful.
 *     <br>{@link SCAN_ERROR_NO_PERMISSION}: permission denied.
 *     <br>{@link SCAN_ERROR_RPC_FAILURE}: RPC communication error.
 *     <br>{@link SCAN_ERROR_SERVER_FAILURE}: server error.
 * @since 12
 */
int32_t OH_Scan_Exit();

#ifdef __cplusplus
}
#endif
#endif  // OH_SCAN_H

/** @} */