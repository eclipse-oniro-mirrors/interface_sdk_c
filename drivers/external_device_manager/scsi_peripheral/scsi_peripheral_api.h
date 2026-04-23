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
 * @brief Provide ScsiPeripheral DDK interface, including initializing DDK, releasing DDK, opening devices, reading and
 * writing devices, etc.
 * @since 18
 */

/**
 * @file scsi_peripheral_api.h
 *
 * @brief Declares the SCSI Peripheral DDK APIs used by the host to access the SCSI device.
 * 
 * @kit DriverDevelopmentKit
 * @library libscsi.z.so
 * @syscap SystemCapability.Driver.SCSI.Extension
 * @since 18
 */

#ifndef SCSI_PERIPHERAL_API_H
#define SCSI_PERIPHERAL_API_H

#include <stdint.h>
#include "scsi_peripheral_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Initializes the SCSI Peripheral DDK.
 * 
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR}: The DDK initialization fails.
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR}: The communication with the DDK service fails.
 * @since 18
 */
int32_t OH_ScsiPeripheral_Init(void);

/**
 * @brief Releases the SCSI Peripheral DDK.
 * 
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR}: The communication with the DDK service fails.
 * @since 18
 */
int32_t OH_ScsiPeripheral_Release(void);

/**
 * @brief Opens the SCSI device specified by **deviceId** and **interfaceIndex**. The **deviceId** can be obtained by
 * shifting the bus number of the USB device left by 32 bits and then performing a bitwise OR operation with the device
 * address. **interfaceIndex** refers to the index of the USB interface to be opened.
 * 
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param deviceId Device ID.
 * @param interfaceIndex Interface index for the API of the SCSI device.
 * @param dev Device handle. For details, see {@link ScsiPeripheral_Device}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **dev** or ***dev** is null.
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR}: The communication with the DDK service fails.
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR}: The memory operation fails.
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR}: An I/O error occurs.
 *     {@link SCSIPERIPHERAL_DDK_DEVICE_NOT_FOUND}: No device is found based on the specified **deviceId** and
 *     **interfaceIndex**.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION}: The operation is not supported.
 * @since 18
 */
int32_t OH_ScsiPeripheral_Open(uint64_t deviceId, uint8_t interfaceIndex, ScsiPeripheral_Device **dev);

/**
 * @brief Closes the SCSI device.
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev Device handle. For details, see {@link ScsiPeripheral_Device}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **dev** or ***dev** is null.
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR}: The communication with the DDK service fails.
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR}: An I/O error occurs.
 * @since 18
 */
int32_t OH_ScsiPeripheral_Close(ScsiPeripheral_Device **dev);

/**
 * @brief Checks whether the logical unit is ready.
 * 
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev Device handle. For details, see {@link ScsiPeripheral_Device}.
 * @param request Request of the **test unit ready** command.
 *     For details, see {@link ScsiPeripheral_TestUnitReadyRequest}.
 * @param response Response returned by the **test unit ready** command.
 *     For details, see {@link ScsiPeripheral_Response}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **dev**, **request**, or **response** is null.
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR}: The communication with the DDK service fails.
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR}: The memory operation fails.
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR}: An I/O error occurs.
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT}: The transmission times out.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION}: The operation is not supported.
 * @since 18
 */
int32_t OH_ScsiPeripheral_TestUnitReady(ScsiPeripheral_Device *dev, ScsiPeripheral_TestUnitReadyRequest *request,
    ScsiPeripheral_Response *response);

/**
 * @brief Queries basic information about the SCSI device.
 * 
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev Device handle. For details, see {@link ScsiPeripheral_Device}.
 * @param request Request of the **inquiry** command. For details, see {@link ScsiPeripheral_InquiryRequest}.
 * @param inquiryInfo Query result returned by the **inquiry** command.
 *     For details, see {@link ScsiPeripheral_InquiryInfo}.
 * @param response Raw response returned by the inquiry command. For details, see {@link ScsiPeripheral_Response}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **dev**, **request**, **inquiryInfo**,
 *     **inquiryInfo->data**, or **response** is null.
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR}: The communication with the DDK service fails.
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR}: The memory operation fails.
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR}: An I/O error occurs.
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT}: The transmission times out.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION}: The operation is not supported.
 * @since 18
 */
int32_t OH_ScsiPeripheral_Inquiry(ScsiPeripheral_Device *dev, ScsiPeripheral_InquiryRequest *request,
    ScsiPeripheral_InquiryInfo *inquiryInfo, ScsiPeripheral_Response *response);

/**
 * @brief Obtains the capacity information about the SCSI device.
 * 
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev Device handle. For details, see {@link ScsiPeripheral_Device}.
 * @param request Request of the **read capacity** command.
 *     For details, see {@link ScsiPeripheral_ReadCapacityRequest}.
 * @param capacityInfo Capacity information returned by the **read capacity** command.
 *     For details, see {@link ScsiPeripheral_CapacityInfo}.
 * @param response Original response returned by the **read capacity** command.
 *     For details, see {@link ScsiPeripheral_Response}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **dev**, **request**, **capacityInfo**, or **response**
 *     is null.
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR}: The communication with the DDK service fails.
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR}: The memory operation fails.
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR}: An I/O error occurs.
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT}: The transmission times out.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION}: The operation is not supported.
 * @since 18
 */
int32_t OH_ScsiPeripheral_ReadCapacity10(ScsiPeripheral_Device *dev, ScsiPeripheral_ReadCapacityRequest *request,
    ScsiPeripheral_CapacityInfo *capacityInfo, ScsiPeripheral_Response *response);

/**
 * @brief Obtains sense data, that is, information returned by the SCSI device to the host to report the device status,
 * error information, and diagnosis information.
 * 
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev Device handle. For details, see {@link ScsiPeripheral_Device}.
 * @param request Request of the **Request Sense** command.
 *     For details, see {@link ScsiPeripheral_RequestSenseRequest}.
 * @param response Response returned by the **Request Sense** command.
 *     For details, see {@link ScsiPeripheral_Response}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **dev**, **request**, or **response** is null.
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR}: The communication with the DDK service fails.
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR}: The memory operation fails.
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR}: An I/O error occurs.
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT}: The transmission times out.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION}: The operation is not supported.
 * @since 18
 */
int32_t OH_ScsiPeripheral_RequestSense(ScsiPeripheral_Device *dev, ScsiPeripheral_RequestSenseRequest *request,
    ScsiPeripheral_Response *response);

/**
 * @brief Reads data from the specified logical block(s).
 * 
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev Device handle. For details, see {@link ScsiPeripheral_Device}.
 * @param request Request of the **read** command. For details, see {@link ScsiPeripheral_IORequest}.
 * @param response Response returned by the **read** command. For details, see {@link ScsiPeripheral_Response}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **dev**, **request**, **request->data**, or **response**
 *     is null.
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR}: The communication with the DDK service fails.
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR}: The memory operation fails.
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR}: An I/O error occurs.
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT}: The transmission times out.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION}: The operation is not supported.
 * @since 18
 */
int32_t OH_ScsiPeripheral_Read10(ScsiPeripheral_Device *dev, ScsiPeripheral_IORequest *request,
    ScsiPeripheral_Response *response);

/**
 * @brief Writes data to the specified logical block(s) of a device.
 * 
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev Device handle. For details, see {@link ScsiPeripheral_Device}.
 * @param request Request of the **write** command. For details, see {@link ScsiPeripheral_IORequest}.
 * @param response Response returned by the **write** command. For details, see {@link ScsiPeripheral_Response}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **dev**, **request**, **request->data**, or **response**
 *     is null.
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR}: The communication with the DDK service fails.
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR}: The memory operation fails.
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR}: An I/O error occurs.
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT}: The transmission times out.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION}: The operation is not supported.
 * @since 18
 */
int32_t OH_ScsiPeripheral_Write10(ScsiPeripheral_Device *dev, ScsiPeripheral_IORequest *request,
    ScsiPeripheral_Response *response);

/**
 * @brief Verifies the specified logical block(s).
 * 
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev Device handle. For details, see {@link ScsiPeripheral_Device}.
 * @param request Request of the **verify** command. For details, see {@link ScsiPeripheral_VerifyRequest}.
 * @param response Response returned by the **verify** command. For details, see {@link ScsiPeripheral_Response}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **dev**, **request**, or **response** is null.
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR}: The communication with the DDK service fails.
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR}: The memory operation fails.
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR}: An I/O error occurs.
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT}: The transmission times out.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION}: The operation is not supported.
 * @since 18
 */
int32_t OH_ScsiPeripheral_Verify10(ScsiPeripheral_Device *dev, ScsiPeripheral_VerifyRequest *request,
    ScsiPeripheral_Response *response);

/**
 * @brief Sends SCSI commands in CDB mode.
 * 
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev Device handle. For details, see {@link ScsiPeripheral_Device}.
 * @param request Request. For details, see {@link ScsiPeripheral_Request}.
 * @param response Response. For details, see {@link ScsiPeripheral_Response}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **dev**, **request**, **request->data**, or **response**
 *     is null, or **request->cdbLength** is 0.
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR}: The communication with the DDK service fails.
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR}: The memory operation fails.
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR}: An I/O error occurs.
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT}: The transmission times out.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION}: The operation is not supported.
 * @since 18
 */
int32_t OH_ScsiPeripheral_SendRequestByCdb(ScsiPeripheral_Device *dev, ScsiPeripheral_Request *request,
    ScsiPeripheral_Response *response);

/**
 * @brief Creates a buffer. To avoid resource leakage, use {@link OH_ScsiPeripheral_DestroyDeviceMemMap} to destroy a
 * buffer after use.
 * 
 * @param dev Device handle. For details, see {@link ScsiPeripheral_Device}.
 * @param size Buffer size.
 * @param devMmap Device memory mapping used to return the created buffer to the caller.
 *     For details, see {@link ScsiPeripheral_DeviceMemMap}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **dev**, **devMmap**, or ***devMmap** is null.
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR}: The memory operation fails.
 * @since 18
 */
int32_t OH_ScsiPeripheral_CreateDeviceMemMap(ScsiPeripheral_Device *dev, size_t size,
    ScsiPeripheral_DeviceMemMap **devMmap);

/**
 * @brief Destroys a buffer. To prevent resource leakage, destroy a buffer in time after use.
 * 
 * @param devMmap Buffer to be destroyed, which is created by calling {@link OH_ScsiPeripheral_CreateDeviceMemMap}.
 *     For details, see {@link ScsiPeripheral_DeviceMemMap}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **devMmap** is null.
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR}: The memory operation fails.
 * @since 18
 */
int32_t OH_ScsiPeripheral_DestroyDeviceMemMap(ScsiPeripheral_DeviceMemMap *devMmap);

/**
 * @brief Parses basic sense data, including the **Information**, **Command specific information**,
 * and **Sense key specific** fields.
 * 
 * @param senseData Sense data to be parsed.
 * @param senseDataLen Length of sense data.
 * @param senseInfo Basic sense data after parsing. For details, see {@link ScsiPeripheral_BasicSenseInfo}.
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS}: The API call is successful.
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER}: The input **senseData** is not a descriptor or is not of the fixed
 *     format, or **senseDataLen** is smaller than
 *     **SCSIPERIPHERAL_MIN_DESCRIPTOR_FORMAT_SENSE** or **SCSIPERIPHERAL_MIN_FIXED_FORMAT_SENSE**.
 * @since 18
 */
int32_t OH_ScsiPeripheral_ParseBasicSenseInfo(uint8_t *senseData, uint8_t senseDataLen,
    ScsiPeripheral_BasicSenseInfo *senseInfo);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // SCSI_PERIPHERAL_API_H
/** @} */
