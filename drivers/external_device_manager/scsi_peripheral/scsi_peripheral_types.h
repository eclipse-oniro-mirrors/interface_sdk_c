/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @brief The SCSI Peripheral DDK is a suite dedicated to SCSI device driver development at the application layer.
 * It provides APIs for initializing the DDK, releasing the DDK, enabling and disabling devices, and reading data
 * from and writing data to devices. It also declares the macros, enum variables, and data structures required for
 * SCSI device driver development. The use scenarios include storage device driver development and disk array
 * management.
 * 
 * @since 18
 */

/**
 * @file scsi_peripheral_types.h
 *
 * @brief Provides the enum variables, structures, and macros used in the SCSI Peripheral DDK APIs.
 *
 * @include <scsi_peripheral/scsi_peripheral_types.h>
 * @kit DriverDevelopmentKit
 * @library libscsi.z.so
 * @syscap SystemCapability.Driver.SCSI.Extension
 * @since 18
 */

#ifndef SCSI_PERIPHERAL_TYPES_H
#define SCSI_PERIPHERAL_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Defines the minimum length of the sense data in the descriptor format.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MIN_DESCRIPTOR_FORMAT_SENSE 8

/**
 * @brief Defines the minimum length of the sense data in the fixed format.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MIN_FIXED_FORMAT_SENSE 18

/**
 * @brief Enumerates the SCSI Peripheral DDK error codes.
 *
 * @since 18
 */
typedef enum {
    /**
     * Permission denied. Ensure that you have correctly declared the required permissions.
     */
    SCSIPERIPHERAL_DDK_NO_PERM = 201,
    /**
     * Invalid parameter. Check whether the parameters meet the requirements.
     */
    SCSIPERIPHERAL_DDK_INVALID_PARAMETER = 401,
    /**
     * Operation success.
     */
    SCSIPERIPHERAL_DDK_SUCCESS = 31700000,
    /**
     * Memory-related errors, such as insufficient memory, memory data replication failure, or memory request failure.
     * Check the memory status and related parameters.
     */
    SCSIPERIPHERAL_DDK_MEMORY_ERROR = 31700001,
    /**
     * Invalid operation. Check whether the operation logic is correct.
     */
    SCSIPERIPHERAL_DDK_INVALID_OPERATION = 31700002,
    /**
     * Device input/output operation failed. Check the transfer parameters and device specifications.
     */
    SCSIPERIPHERAL_DDK_IO_ERROR = 31700003,
    /**
     * Transfer timeout. Check the timeout parameters and device status.
     */
    SCSIPERIPHERAL_DDK_TIMEOUT = 31700004,
    /**
     * DDK initialization error, or DDK uninitialized. Initialize the DDK service first.
     */
    SCSIPERIPHERAL_DDK_INIT_ERROR = 31700005,
    /**
     * Communication with the SCSI Peripheral DDK failed. Check whether the DDK service is running properly.
     */
    SCSIPERIPHERAL_DDK_SERVICE_ERROR = 31700006,
    /**
     * Device not found. Ensure that the input device information is correct.
     */
    SCSIPERIPHERAL_DDK_DEVICE_NOT_FOUND = 31700007
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
    SCSIPERIPHERAL_STATUS_TASK_ABORTED = 0x40
} ScsiPeripheral_Status;

/**
 * @brief Defines the opaque SCSI device struct, which is used to represent the device handle that interacts with SCSI
 * peripherals.
 *
 * @since 18
 */
typedef struct ScsiPeripheral_Device ScsiPeripheral_Device;

/**
 * @brief Represents the device memory mapping created by calling {@link OH_ScsiPeripheral_CreateDeviceMemMap}. The
 * buffer that uses the device memory mapping can provide better performance.
 *
 * @since 18
 */
typedef struct ScsiPeripheral_DeviceMemMap {
    /**
     * Start address of the buffer mapped to the device memory, pointing to the mapped device memory space. This buffer
     * is used to store SCSI device data and provides high-performance memory access capabilities.
     */
    uint8_t * const address;
    /**
     * Buffer size, in bytes. The value must be greater than 0.
     */
    const size_t size;
    /**
     * Read/write start offset of the buffer, in bytes. The default value is **0**, indicating that there is no offset
     * and the buffer starts from the specified address. The value range is [0, **size**]. Set this parameter when you
     * need to start reading/writing data from a specific position in the buffer. Different offset values correspond to
     * different start positions for reading/writing.
     */
    uint32_t offset;
    /**
     * Length of the used buffer, in bytes. By default, the value is equal to the size of the buffer, indicating that
     * the entire buffer is used. Set this parameter when only a part of the buffer is used. The sum of **bufferLength**
     *  and **offset** must be less than or equal to the value of **size**.
     */
    uint32_t bufferLength;
    /**
     * Length of the transferred data, in bytes. The initial value is **0**, indicating that no data has been
     * transferred. This field is updated after SCSI data transfer is complete. It indicates the actual amount of data
     * transferred and can be used to monitor the transfer progress.
     */
    uint32_t transferredLength;
} ScsiPeripheral_DeviceMemMap;

/**
 * @brief Defines the read/write operation request. This struct defines the request parameters required for the SCSI
 * peripheral to perform read/write operations, including the start address of the logical block, transfer length, and
 * control information.
 *
 * @since 18
 */
typedef struct ScsiPeripheral_IORequest {
    /**
     * Start address of a logical block, which specifies the start position for read/write operations of the SCSI
     * peripheral.
     */
    uint32_t lbAddress;
    /**
     * Number of consecutive logical blocks to be operated. The value must be a positive integer and cannot exceed the
     * maximum number of logical blocks that can be transferred at a time.
     */
    uint16_t transferLength;
    /**
     * **Control** field, which specifies the control flags of a SCSI command, such as the priority and linked command.
     */
    uint8_t control;
    /**
     * First byte of the SCSI command descriptor block (CDB), which usually contains the operation code and operation
     * group information.
     */
    uint8_t byte1;
    /**
     * Sixth byte of the SCSI CDB, which contains different parameters or flag information based on the command type.
     */
    uint8_t byte6;
    /**
     * Buffer for data transmission.
     */
    ScsiPeripheral_DeviceMemMap *data;
    /**
     * Timeout interval, in milliseconds.
     */
    uint32_t timeout;
} ScsiPeripheral_IORequest;

/**
 * @brief Defines the maximum length of a CDB.
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
     * Timeout interval, in milliseconds.
     */
    uint32_t timeout;
} ScsiPeripheral_Request;

/**
 * @brief Defines the maximum length of the sense data.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MAX_SENSE_DATA_LEN 252

/**
 * @brief Defines the SCSI response parameters, including the status, error diagnosis data, and transfer result. It is
 * used to receive the response data from the SCSI device and determine whether the command is successful.
 *
 * @since 18
 */
typedef struct ScsiPeripheral_Response {
    /**
     * Sense data, which is the status, error, and diagnosis information returned by the SCSI device to the host.
     */
    uint8_t senseData[SCSIPERIPHERAL_MAX_SENSE_DATA_LEN];
    /**
     * Status when the call is complete. The options include **SCSIPERIPHERAL_STATUS_GOOD** (normal) and
     * **SCSIPERIPHERAL_STATUS_BUSY** (busy).
     */
    ScsiPeripheral_Status status;
    /**
     * In the SCSI generic driver, this field is used to store the masked SCSI status.
     */
    uint8_t maskedStatus;
    /**
     * Message status, indicating the message result after the SCSI command is executed.
     */
    uint8_t msgStatus;
    /**
     * Number of valid bytes actually written to the sense buffer, which is used to determine the length of valid data
     * in the **senseData** array. If the value is **0**, there is no sense data.
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
     * SCSI command execution duration, in ms.
     */
    uint32_t duration;
} ScsiPeripheral_Response;

/**
 * @brief Defines the SCSI command (**TEST UNIT READY**) request struct, which is usually used to check whether the
 * logical unit is ready. A logical unit is an I/O operation entity that can be independently addressed in a SCSI
 * device.
 *
 * @since 18
 */
typedef struct ScsiPeripheral_TestUnitReadyRequest {
    /**
     * **Control** field used to specify the control information of the SCSI command.
     */
    uint8_t control;
    /**
     * Timeout interval, in milliseconds.
     */
    uint32_t timeout;
} ScsiPeripheral_TestUnitReadyRequest;

/**
 * @brief Defines the SCSI command (**INQUIRY**) request struct, which is usually used to query basic device
 * information.
 *
 * @since 18
 */
typedef struct ScsiPeripheral_InquiryRequest {
    /**
     * **Page code** field. Set this field if you want to obtain certain types of device information. When an **Inquiry*
     * * command with a specific page code is run, the device returns details related to the page code. If the page
     * code is set to **0x00**, it indicates that the standard inquiry data rather than the data of specific pages is
     * requested.
     */
    uint8_t pageCode;
    /**
     * **Allocation length** field used to specify the size of the buffer prepared by the request initiator (usually
     * the host) for the response data, in bytes.
     */
    uint16_t allocationLength;
    /**
     * **Control** field used to specify the control information of the SCSI command.
     */
    uint8_t control;
    /**
     * First byte of the SCSI command descriptor block (CDB), which usually contains the operation code and operation
     * group information.
     */
    uint8_t byte1;
    /**
     * Timeout interval, in milliseconds.
     */
    uint32_t timeout;
} ScsiPeripheral_InquiryRequest;

/**
 * @brief Defines the length of a vendor ID.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_VENDOR_ID_LEN 8

/**
 * @brief Defines the length of a product ID.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_PRODUCT_ID_LEN 16

/**
 * @brief Defines the length of a product revision version.
 *
 * @since 18
 */
#define SCSIPERIPHERAL_PRODUCT_REV_LEN 4

/**
 * @brief Defines the SCSI **INQUIRY** data, which is used to store the query result of the **INQUIRY** command of SCSI
 * peripherals.
 *
 * @since 18
 */
typedef struct ScsiPeripheral_InquiryInfo {
    /**
     * Device type of the SCSI peripheral. For details about the type values, see the SCSI protocol.
     */
    uint8_t deviceType;
    /**
     * Vendor ID.
     */
    char idVendor[SCSIPERIPHERAL_VENDOR_ID_LEN + 1];
    /**
     * Product ID.
     */
    char idProduct[SCSIPERIPHERAL_PRODUCT_ID_LEN + 1];
    /**
     * Product version.
     */
    char revProduct[SCSIPERIPHERAL_PRODUCT_REV_LEN + 1];
    /**
     * Pointer to the device memory mapping, which is used to store the queried data.
     */
    ScsiPeripheral_DeviceMemMap *data;
} ScsiPeripheral_InquiryInfo;

/**
 * @brief Defines the SCSI command (**READ CAPACITY**) request struct, which is used to send a command for reading the
 * storage capacity. It helps obtain the logical block size and total number of blocks of a device.
 *
 * @since 18
 */
typedef struct ScsiPeripheral_ReadCapacityRequest {
    /**
     * Logical block address, which specifies the start position for reading the capacity. If the value is **0**, the
     * overall capacity of the device is obtained.
     */
    uint32_t lbAddress;
    /**
     * **Control** field used to specify the control information of the SCSI command.
     */
    uint8_t control;
    /**
     * Eighth byte of the command descriptor block (CDB).
     */
    uint8_t byte8;
    /**
     * Timeout interval, in milliseconds.
     */
    uint32_t timeout;
} ScsiPeripheral_ReadCapacityRequest;

/**
 * @brief Defines the SCSI **READ CAPACITY** struct. It is used to obtain the storage capacity of a device during SCSI
 * driver development. It supports operations such as partition management, available space check, and store resource
 * allocation.
 *
 * @since 18
 */
typedef struct ScsiPeripheral_CapacityInfo {
    /**
     * Logical block address, which specifies the start position for reading the capacity. If the value is **0**, the
     * overall capacity of the device is obtained.
     */
    uint32_t lbAddress;
    /**
     * Length of a single logical unit, in bytes. Size of each logical block, in bytes. The value is usually a standard
     * value such as **512**, **2048**, or **4096**, depending on the device type and formatting mode.
     */
    uint32_t lbLength;
} ScsiPeripheral_CapacityInfo;

/**
 * @brief Defines the SCSI **REQUEST SENSE** request struct. This command is usually used to obtain device error
 * information.
 *
 * @since 18
 */
typedef struct ScsiPeripheral_RequestSenseRequest {
    /**
     * **Allocation length** field used to specify the size of the buffer prepared by the request initiator (usually
     * the host) for the response data, in bytes.
     */
    uint8_t allocationLength;
    /**
     * **Control** field used to specify the control information of the SCSI command.
     */
    uint8_t control;
    /**
     * First byte of the SCSI command descriptor block (CDB), which usually contains the operation code and operation
     * group information.
     */
    uint8_t byte1;
    /**
     * Timeout interval, in milliseconds.
     */
    uint32_t timeout;
} ScsiPeripheral_RequestSenseRequest;

/**
 * @brief Defines the basic information struct of SCSI sense data, which is used to encapsulate the sense data returned
 * after a SCSI command is executed. This struct contains the response code, status flag, and various information
 * fields, which are used by the driver to obtain and analyze the error status and command execution result of the SCSI
 * device.
 *
 * @since 18
 */
typedef struct ScsiPeripheral_BasicSenseInfo {
    /**
     * Response code. It is automatically set by the driver layer when the sense data is received.
     */
    uint8_t responseCode;
    /**
     * Information validity flag. If the value is **true**, the **information** and **commandSpecific** fields are
     * valid. If the value is **false**, these fields should be ignored. Before using this flag, check it to avoid
     * reading invalid data.
     */
    bool valid;
    /**
     * **information** field. The value must comply with the SCSI protocol.
     */
    uint64_t information;
    /**
     * **commandSpecific** field. The value must comply with the SCSI protocol.
     */
    uint64_t commandSpecific;
    /**
     * Flag of the **senseKeySpecific** field. If the value is **true**, the **senseKeySpecific** field is valid and
     * contains sense key specific data. If the value is **false**, the **senseKeySpecific** field should be ignored.
     * Before using this flag, check it to avoid reading invalid data.
     */
    bool sksv;
    /**
     * **senseKeySpecific** field. The value must comply with the SCSI protocol.
     */
    uint32_t senseKeySpecific;
} ScsiPeripheral_BasicSenseInfo;

/**
 * @brief Defines the SCSI command (**VERIFY**) request struct, which is usually used to verify the data integrity of
 * logical blocks.
 *
 * @since 18
 */
typedef struct ScsiPeripheral_VerifyRequest {
    /**
     * Start address of logical blocks.
     */
    uint32_t lbAddress;
    /**
     * Number of consecutive logical blocks to be verified.
     */
    uint16_t verificationLength;
    /**
     * **Control** field used to specify the control information of the SCSI command.
     */
    uint8_t control;
    /**
     * First byte of the SCSI command descriptor block (CDB), which usually contains the operation code and operation
     * group information.
     */
    uint8_t byte1;
    /**
     * Sixth byte of the SCSI CDB, which contains different parameters or flag information based on the command type.
     */
    uint8_t byte6;
    /**
     * Timeout interval, in milliseconds.
     */
    uint32_t timeout;
} ScsiPeripheral_VerifyRequest;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // SCSI_PERIPHERAL_TYPES_H
/** @} */