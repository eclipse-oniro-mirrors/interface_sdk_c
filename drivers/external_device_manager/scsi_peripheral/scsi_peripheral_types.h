/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup ScsiPeripheralDDK
 * @{
 *
 * @brief Provides ScsiPeripheral DDK types and declares macros, enumerations, and data structures used by the
 * ScsiPeripheral DDK.
 * @since 18
 */

/**
 * @file scsi_peripheral_types.h
 *
 * @brief Provides the enum variables, structures, and macros used in the SCSI Peripheral DDK APIs.
 * 
 * @kit DriverDevelopmentKit
 * @library libscsi.z.so
 * @syscap SystemCapability.Driver.SCSI.Extension
 * @since 18
 */

#ifndef SCSI_PERIPHERAL_TYPES_H
#define SCSI_PERIPHERAL_TYPES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief The min length of descriptor format sense data: 8.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MIN_DESCRIPTOR_FORMAT_SENSE 8

/**
 * @brief The min length of fixed format sense data: 18.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MIN_FIXED_FORMAT_SENSE 18

/**
 * @brief SCSI Peripheral DDK error codes.
 * 
 * @since 18
 */
typedef enum {
    /**
     * Permission denied.
     */
    SCSIPERIPHERAL_DDK_NO_PERM = 201,
    /**
     * Invalid parameter.
     */
    SCSIPERIPHERAL_DDK_INVALID_PARAMETER = 401,
    /**
     * Operation success.
     */
    SCSIPERIPHERAL_DDK_SUCCESS = 31700000,
    /**
     * Memory-related errors, such as insufficient memory, memory data replication failure, or memory request failure.
     */
    SCSIPERIPHERAL_DDK_MEMORY_ERROR = 31700001,
    /**
     * Invalid operation.
     */
    SCSIPERIPHERAL_DDK_INVALID_OPERATION = 31700002,
    /**
     * Device input/output operation failed.
     */
    SCSIPERIPHERAL_DDK_IO_ERROR = 31700003,
    /**
     * Transfer timeout.
     */
    SCSIPERIPHERAL_DDK_TIMEOUT = 31700004,
    /**
     * DDK initialization error, or DDK uninitialized.
     */
    SCSIPERIPHERAL_DDK_INIT_ERROR = 31700005,
    /**
     * Communication with the SCSI Peripheral DDK failed.
     */
    SCSIPERIPHERAL_DDK_SERVICE_ERROR = 31700006,
    /**
     * Device not found.
     */
    SCSIPERIPHERAL_DDK_DEVICE_NOT_FOUND = 31700007,
} ScsiPeripheral_DdkErrCode;

/**
 * @brief Enumerates the SCSI status codes used for the response.
 * 
 * @since 18
 */
typedef enum {
    /**
     * Normal state.
     */
    SCSIPERIPHERAL_STATUS_GOOD = 0x00,
    /**
     * Status check required.
     */
    SCSIPERIPHERAL_STATUS_CHECK_CONDITION_NEEDED = 0x02,
    /**
     * Conditions met.
     */
    SCSIPERIPHERAL_STATUS_CONDITION_MET = 0x04,
    /**
     * Occupying.
     */
    SCSIPERIPHERAL_STATUS_BUSY = 0x08,
    /**
     * Resource reservation conflict.
     */
    SCSIPERIPHERAL_STATUS_RESERVATION_CONFLICT = 0x18,
    /**
     * Task set already full.
     */
    SCSIPERIPHERAL_STATUS_TASK_SET_FULL = 0x28,
    /**
     * ACA activity status.
     */
    SCSIPERIPHERAL_STATUS_ACA_ACTIVE = 0x30,
    /**
     * Task aborted.
     */
    SCSIPERIPHERAL_STATUS_TASK_ABORTED = 0x40,
} ScsiPeripheral_Status;

/**
 * @brief Opaque SCSI device structure.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_Device ScsiPeripheral_Device;

/**
 * @brief Represents the device memory mapping created by calling **OH_ScsiPeripheral_CreateDeviceMemMap**. The buffer
 * that uses the device memory mapping can provide better performance.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_DeviceMemMap {
    /**
     * Buffer address.
     */
    uint8_t * const address;
    /**
     * Buffer size.
     */
    const size_t size;
    /**
     * Offset of the used buffer. The default value is **0**, indicating that there is no offset and the buffer starts
     * from the specified address.
     */
    uint32_t offset;
    /**
     * Length of the used buffer. By default, the value is equal to the size of the buffer, indicating that the entire
     * buffer is used.
     */
    uint32_t bufferLength;
    /**
     * Length of the transferred data.
     */
    uint32_t transferredLength;
} ScsiPeripheral_DeviceMemMap;

/**
 * @brief Defines the read/write operation request.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_IORequest {
    /**
     * Start address of a logical block.
     */
    uint32_t lbAddress;
    /**
     * Number of consecutive logical blocks to be operated.
     */
    uint16_t transferLength;
    /**
     * **Control** field used to specify control information.
     */
    uint8_t control;
    /**
     * First byte of the CDB.
     */
    uint8_t byte1;
    /**
     * Sixth byte of the CDB.
     */
    uint8_t byte6;
    /**
     * Buffer for data transmission.
     */
    ScsiPeripheral_DeviceMemMap *data;
    /**
     * Timeout duration, in ms.
     */
    uint32_t timeout;
} ScsiPeripheral_IORequest;

/**
 * @brief The max length of command descriptor block: 16.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MAX_CMD_DESC_BLOCK_LEN 16

/**
 * @brief Defines the request structure.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_Request {
    /** Command descriptor block. */
    uint8_t commandDescriptorBlock[SCSIPERIPHERAL_MAX_CMD_DESC_BLOCK_LEN];
    /**
     * Length of the command descriptor block.
     */
    uint8_t cdbLength;
    /**
     * Data transfer direction: **–1** indicates no data transfer, **–2** indicates data transfer (write) from the host
     * to the device, **–3** indicates data transfer (read) from the device to the host, and **–4** indicates
     * bidirectional data transfer.
     */
    int8_t dataTransferDirection;
    /**
     * Buffer for data transmission.
     */
    ScsiPeripheral_DeviceMemMap *data;
    /**
     * Timeout duration, in ms.
     */
    uint32_t timeout;
} ScsiPeripheral_Request;

/**
 * @brief The max length of sense data: 252.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MAX_SENSE_DATA_LEN 252

/**
 * @brief Defines the response structure.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_Response {
    /** Sense data. */
    uint8_t senseData[SCSIPERIPHERAL_MAX_SENSE_DATA_LEN];
    /**
     * Status when the call is complete, for example, **Good** or **Busy**.
     */
    ScsiPeripheral_Status status;
    /**
     * Masked status, which is used in SCSI Generic (SG) interfaces of Linux to store the processed SCSI status for
     * easy access by applications.
     */
    uint8_t maskedStatus;
    /**
     * Message status.
     */
    uint8_t msgStatus;
    /**
     * Number of bytes that are actually written to the sense buffer.
     */
    uint8_t sbLenWr;
    /**
     * Host adapter status, for example, success (0x00), connection failure (0x01), busy bus (0x02), or timeout (0x03).
     */
    uint16_t hostStatus;
    /**
     * Driver status, for example, success (0x00) or busy device or resource (0x01).
     */
    uint16_t driverStatus;
    /**
     * Length deviation of the actually transmitted data, that is, the number of bytes that are not transmitted.
     */
    int32_t resId;
    /**
     * Command execution duration, in ms.
     */
    uint32_t duration;
} ScsiPeripheral_Response;

/**
 * @brief Defines the request structure of the **test unit ready** command.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_TestUnitReadyRequest {
    /**
     * **Control** field used to specify control information.
     */
    uint8_t control;
    /**
     * Timeout duration, in ms.
     */
    uint32_t timeout;
} ScsiPeripheral_TestUnitReadyRequest;

/**
 * @brief Defines the request structure of the **inquiry** command.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_InquiryRequest {
    /**
     * **Page code** field. Set this field if you want to obtain certain types of device information. When an
     * **Inquiry** command with a specific page code is run, the device returns details related to the page code.
     * If the page code is set to **0x00**, it indicates that the standard inquiry data rather than the data of
     * specific pages is requested.
     */
    uint8_t pageCode;
    /**
     * **Allocation length** field used to specify the size of the buffer prepared by the request initiator (usually
     * the host) for the response data.
     */
    uint16_t allocationLength;
    /**
     * **Control** field used to specify control information.
     */
    uint8_t control;
    /**
     * First byte of the CDB.
     */
    uint8_t byte1;
    /**
     * Timeout duration, in ms.
     */
    uint32_t timeout;
} ScsiPeripheral_InquiryRequest;

/**
 * @brief The length of vendor identification: 8.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_VENDOR_ID_LEN 8

/**
 * @brief The length of product identification: 16.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_PRODUCT_ID_LEN 16

/**
 * @brief The length of product revision: 4.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_PRODUCT_REV_LEN 4

/**
 * @brief Defines the SCSI inquiry data.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_InquiryInfo {
    /**
     * Device type.
     */
    uint8_t deviceType;
    /** Vendor identification. */
    char idVendor[SCSIPERIPHERAL_VENDOR_ID_LEN + 1];
    /** Product identification. */
    char idProduct[SCSIPERIPHERAL_PRODUCT_ID_LEN + 1];
    /** Product revision. */
    char revProduct[SCSIPERIPHERAL_PRODUCT_REV_LEN + 1];
    /**
     * Inquiry data.
     */
    ScsiPeripheral_DeviceMemMap *data;
} ScsiPeripheral_InquiryInfo;

/**
 * @brief Request structure of the **read capacity** command.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_ReadCapacityRequest {
    /**
     * Address of the logical unit.
     */
    uint32_t lbAddress;
    /**
     * **Control** field used to specify control information.
     */
    uint8_t control;
    /**
     * Eighth byte of the CDB.
     */
    uint8_t byte8;
    /**
     * Timeout duration, in ms.
     */
    uint32_t timeout;
} ScsiPeripheral_ReadCapacityRequest;

/**
 * @brief Defines the SCSI read capacity.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_CapacityInfo {
    /**
     * Address of the logical unit.
     */
    uint32_t lbAddress;
    /**
     * Length of a single logical unit, in bytes.
     */
    uint32_t lbLength;
} ScsiPeripheral_CapacityInfo;

/**
 * @brief Defines the request structure of the **Request Sense** command.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_RequestSenseRequest {
    /**
     * **Allocation length** field used to specify the size of the buffer prepared by the request initiator (usually
     * the host) for the response data.
     */
    uint8_t allocationLength;
    /**
     * **Control** field used to specify control information.
     */
    uint8_t control;
    /**
     * First byte of the CDB.
     */
    uint8_t byte1;
    /**
     * Timeout duration, in ms.
     */
    uint32_t timeout;
} ScsiPeripheral_RequestSenseRequest;

/**
 * @brief Defines the basic information about the sense data.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_BasicSenseInfo {
    /**
     * Response code.
     */
    uint8_t responseCode;
    /**
     * Information validity flag.
     */
    bool valid;
    /**
     * **Information** field.
     */
    uint64_t information;
    /**
     * **Command-specific information** field.
     */
    uint64_t commandSpecific;
    /**
     * Flag of the **Sense key specific** field.
     */
    bool sksv;
    /**
     * **Sense key specific** field.
     */
    uint32_t senseKeySpecific;
} ScsiPeripheral_BasicSenseInfo;

/**
 * @brief Defines the request structure of the **verify** command.
 * 
 * @since 18
 */
typedef struct ScsiPeripheral_VerifyRequest {
    /**
     * Start address of a logical block.
     */
    uint32_t lbAddress;
    /**
     * Number of consecutive logical blocks.
     */
    uint16_t verificationLength;
    /**
     * **Control** field used to specify control information.
     */
    uint8_t control;
    /**
     * First byte of the CDB.
     */
    uint8_t byte1;
    /**
     * Sixth byte of the CDB.
     */
    uint8_t byte6;
    /**
     * Timeout duration, in ms.
     */
    uint32_t timeout;
} ScsiPeripheral_VerifyRequest;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // SCSI_PERIPHERAL_TYPES_H
/** @} */
