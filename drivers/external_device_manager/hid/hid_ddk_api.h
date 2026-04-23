/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup HidDdk
 * @{
 *
 * @brief Provides HID DDK interfaces, including creating a device, sending an event, and destroying a device.
 *
 * @syscap SystemCapability.Driver.HID.Extension
 * @since 11
 * @version 1.0
 */

/**
 * @file hid_ddk_api.h
 *
 * @brief Declares the HID DDK functions for accessing an input device from the host.
 *
 * @kit DriverDevelopmentKit
 * @library libhid.z.so
 * @syscap SystemCapability.Driver.HID.Extension
 * File to include: <hid/hid_ddk_api.h>
 * @since 11
 * @version 1.0
 */

#ifndef HID_DDK_API_H
#define HID_DDK_API_H

#include <stdint.h>
#include "hid_ddk_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Creates a device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param hidDevice Pointer to the basic information about the device to create, including the device name, vendor ID,
 *     and product ID.
 * @param hidEventProperties Pointer to the event properties related to the device to create, including the event type,
 *     key event properties, absolute coordinate event properties, and relative coordinate event properties.
 * @return deviceID (a non-negative number) if the API call is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_OPERATION}: The hid_ddk service connection fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. The input **hidDevice** is a
 *     null pointer.
 *     2. The input **hidEventProperties** is a null pointer. 3. The length of **properties** exceeds 7 characters.
 *     4. The length of **hidEventTypes** exceeds 5 characters.
 *     5. The length of **hidKeys** exceeds 100 characters. 6. The length of **hidAbs** exceeds 26 characters. 7. The
 *     length of **hidRelBits** exceeds 13 characters. 8. The length of **hidMiscellaneous** exceeds 6 characters.
 *     {@link HID_DDK_FAILURE}: The number of devices reaches the maximum value 200.
 * @since 11
 * @version 1.0
 */
int32_t OH_Hid_CreateDevice(Hid_Device *hidDevice, Hid_EventProperties *hidEventProperties);

/**
 * @brief Sends an event list to a device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param deviceId Device ID.
 * @param items List of the events to send. The event information includes the event type (**Hid_EventType**), code
 *     (**Hid_SynEvent**, **Hid_KeyCode**, **Hid_AbsAxes**, **Hid_RelAxes**, or **Hid_MscEvent**),
 *     and value (depending on the actual device input).
 * @param length Length of the event list (number of events to be sent at a time).
 * @return {@link HID_DDK_SUCCESS}: The API call is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_OPERATION}: The hid_ddk service connection fails or the caller is not the device creator.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. The device ID is less than 0.
 *     2. The length of the input parameter **length** exceeds 7 characters. 3. The input parameter **items** is a null
 *     pointer.
 *     {@link HID_DDK_NULL_PTR}: The input device is a null pointer.
 * @since 11
 * @version 1.0
 */
int32_t OH_Hid_EmitEvent(int32_t deviceId, const Hid_EmitItem items[], uint16_t length);

/**
 * @brief Destroys a device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param deviceId Device ID.
 * @return {@link HID_DDK_SUCCESS}: The API call is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_OPERATION}: The hid_ddk service connection fails or the caller is not the device creator.
 *     {@link HID_DDK_FAILURE}: The corresponding device does not exist.
 * @since 11
 * @version 1.0
 */
int32_t OH_Hid_DestroyDevice(int32_t deviceId);

/**
 * @brief Initializes an HID DDK.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INIT_ERROR}: The DDK initialization fails.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 * @since 18
 */
int32_t OH_Hid_Init(void);

/**
 * @brief Releases an HID DDK.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 * @since 18
 */
int32_t OH_Hid_Release(void);

/**
 * @brief Opens the device specified by **deviceId** and **interfaceIndex**.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param deviceId Device ID.
 * @param interfaceIndex Interface index for the API of the HID device.
 * @param dev Device operation handle.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 *     {@link HID_DDK_MEMORY_ERROR}: Memory allocation for the device fails.
 *     {@link HID_DDK_IO_ERROR}: The I/O operation fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The **dev** parameter or ***dev** is null.
 *     {@link HID_DDK_DEVICE_NOT_FOUND}: No device is found based on **deviceId** and **interfaceIndex**.
 * @since 18
 */
int32_t OH_Hid_Open(uint64_t deviceId, uint8_t interfaceIndex, Hid_DeviceHandle **dev);

/**
 * @brief Closes an HID device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 *     {@link HID_DDK_IO_ERROR}: The I/O operation fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The **dev** parameter or ***dev** is null.
 * @since 18
 */
int32_t OH_Hid_Close(Hid_DeviceHandle **dev);

/**
 * @brief Writes a report to an HID device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle.
 * @param data Data to be written.
 * @param length Length of the data to be written. The maximum value is {@link HID_MAX_REPORT_BUFFER_SIZE}. Otherwise,
 *     the parameter verification fails.
 * @param bytesWritten Number of written bytes.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     2. **data** is null. 3. The value of **length** is **0**; 4. The value of **length**
 *     exceeds {@link HID_MAX_REPORT_BUFFER_SIZE}. 5. **bytesWritten** is null.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 *     {@link HID_DDK_IO_ERROR}: The I/O operation fails.
 * @since 18
*/
int32_t OH_Hid_Write(Hid_DeviceHandle *dev, uint8_t *data, uint32_t length, uint32_t *bytesWritten);

/**
 * @brief Reads a report from the HID device within the specified timeout interval.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle.
 * @param data Buffer for storing the read data.
 * @param bufSize Size of the buffer for storing the read data. The maximum size is {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     Otherwise, the parameter verification fails.
 * @param timeout Timeout interval, in ms. The value **-1** indicates block waiting.
 * @param bytesRead Number of bytes to read.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     2. **data** is null. 3. The value of **bufSize** is **0**. 4. The value of **bufSize**
 *     exceeds {@link HID_MAX_REPORT_BUFFER_SIZE}. 5. **bytesRead** is null.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 *     {@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     {@link HID_DDK_IO_ERROR}: The I/O operation fails.
 *     {@link HID_DDK_TIMEOUT}: The read operation times out.
 * @since 18
*/
int32_t OH_Hid_ReadTimeout(Hid_DeviceHandle *dev, uint8_t *data, uint32_t bufSize, int timeout, uint32_t *bytesRead);

/**
 * @brief Reads a report from the HID device. The blocking mode (that is, blocking remains active until
 * data can be read) is used by default. You can call {@link OH_Hid_SetNonBlocking} to change the mode.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle.
 * @param data Buffer for storing the read data.
 * @param bufSize Size of the buffer for storing the read data. The maximum size is {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     Otherwise, the parameter verification fails.
 * @param bytesRead Number of bytes to read.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     2. **data** is null. 3. The value of **bufSize** is **0**. 4. The value of **bufSize**
 *     exceeds {@link HID_MAX_REPORT_BUFFER_SIZE}. 5. **bytesRead** is null.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 *     {@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     {@link HID_DDK_IO_ERROR}: The I/O operation fails.
 *     {@link HID_DDK_TIMEOUT}: The read operation times out.
 * @since 18
*/
int32_t OH_Hid_Read(Hid_DeviceHandle *dev, uint8_t *data, uint32_t bufSize, uint32_t *bytesRead);

/**
 * @brief Sets the device read mode to non-blocking mode.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle.
 * @param nonBlock Whether to enable the non-blocking mode for reading data. - **1**: The non-blocking mode is enabled.
 *     When {@link OH_Hid_Read} is called, if the device has readable data, {@link HID_DDK_SUCCESS} is returned; if the
 *     device has no readable data, {@link HID_DDK_TIMEOUT} is returned. - **0**: The non-blocking mode is disabled.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     2. The value of **nonBlock** is not **1** or **0**.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 * @since 18
*/
int32_t OH_Hid_SetNonBlocking(Hid_DeviceHandle *dev, int nonBlock);

/**
 * @brief Obtains the original device information.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle.
 * @param rawDevInfo Original device information, including the vendor ID, product ID, and bus type.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     2. **rawDevInfo** is null.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 *     {@link HID_DDK_IO_ERROR}: The I/O operation fails.
 *     {@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
*/
int32_t OH_Hid_GetRawInfo(Hid_DeviceHandle *dev, Hid_RawDevInfo *rawDevInfo);

/**
 * @brief Obtains the original device name.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle.
 * @param data Buffer for storing the read data.
 * @param bufSize Size of the buffer for storing the read data. The maximum size is {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     Otherwise, the parameter verification fails.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     2. **data** is null. 3. The value of **bufSize** is **0**.
 *     4. The value of **bufSize** exceeds {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 *     {@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     {@link HID_DDK_IO_ERROR}: The I/O operation fails.
 *     {@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
*/
int32_t OH_Hid_GetRawName(Hid_DeviceHandle *dev, char *data, uint32_t bufSize);

/**
 * @brief Obtains the physical address of the HID device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle.
 * @param data Buffer for storing the read data.
 * @param bufSize Size of the buffer for storing the read data. The maximum size is {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     Otherwise, the parameter verification fails.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     2. **data** is null. 3. The value of **bufSize** is **0**.
 *     4. The value of **bufSize** exceeds {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 *     {@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     {@link HID_DDK_IO_ERROR}: The I/O operation fails.
 *     {@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
*/
int32_t OH_Hid_GetPhysicalAddress(Hid_DeviceHandle *dev, char *data, uint32_t bufSize);

/**
 * @brief Obtains the original unique identifier of a device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle.
 * @param data Buffer for storing the read data.
 * @param bufSize Size of the buffer for storing the read data. The maximum size is {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     Otherwise, the parameter verification fails.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     2. **data** is null. 3. The value of **bufSize** is **0**.
 *     4. The value of **bufSize** exceeds {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 *     {@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     {@link HID_DDK_IO_ERROR}: The I/O operation fails.
 *     {@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
*/
int32_t OH_Hid_GetRawUniqueId(Hid_DeviceHandle *dev, uint8_t *data, uint32_t bufSize);

/**
 * @brief Sends a report to the HID device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle.
 * @param reportType Report type.
 * @param data Data to be sent.
 * @param length Length of the data to be sent, in bytes. The maximum value is {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     Otherwise, the parameter verification fails.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     2. **data** is null. 3. The value of **length** is **0**;
 *     4. The value of **length** exceeds {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 *     {@link HID_DDK_IO_ERROR}: The I/O operation fails.
 *     {@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
*/
int32_t OH_Hid_SendReport(Hid_DeviceHandle *dev, Hid_ReportType reportType, const uint8_t *data, uint32_t length);

/**
 * @brief Obtains a report from the HID device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle.
 * @param reportType Report type.
 * @param data Buffer for storing the read data.
 * @param bufSize Size of the buffer for storing the read data. The maximum size is {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     Otherwise, the parameter verification fails.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     2. **data** is null. 3. The value of **bufSize** is **0**.
 *     4. The value of **bufSize** exceeds {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 *     {@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     {@link HID_DDK_IO_ERROR}: The I/O operation fails.
 *     {@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
*/
int32_t OH_Hid_GetReport(Hid_DeviceHandle *dev, Hid_ReportType reportType, uint8_t *data, uint32_t bufSize);

/**
 * @brief Obtains the report descriptor of the HID device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle.
 * @param buf Buffer for storing descriptors.
 * @param bufSize Size of the buffer, in bytes. The maximum value is {@link HID_MAX_REPORT_BUFFER_SIZE}. Otherwise, the
 *     parameter verification fails.
 * @param bytesRead Number of bytes to read.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     {@link HID_DDK_NO_PERM}: The permission verification fails.
 *     {@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     2. **buf** is null. 3. The value of **bufSize** is **0**. 4. The value of **bufSize**
 *     exceeds {@link HID_MAX_REPORT_BUFFER_SIZE}. 5. **bytesRead** is null.
 *     {@link HID_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails.
 *     {@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     {@link HID_DDK_IO_ERROR}: The I/O operation fails.
 *     {@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
*/
int32_t OH_Hid_GetReportDescriptor(Hid_DeviceHandle *dev, uint8_t *buf, uint32_t bufSize, uint32_t *bytesRead);
/** @} */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // HID_DDK_API_H
