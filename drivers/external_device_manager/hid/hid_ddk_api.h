/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
 */

/**
 * @file hid_ddk_api.h
 *
 * @brief Declares the HID DDK functions for accessing an input device from the host. DDK stands for Driver Development
 * Kit. This module provides APIs for creating, opening, reading data from, and writing data to HID devices, as well as
 * managing devices and injecting events. It supports two use modes. The first one is creating virtual HID devices and
 * injecting events, which is suitable for simulating keyboard, mouse, and touchscreen inputs. The second one is
 * accessing and communicating with real HID devices, which allows you to open, read, and write device reports and
 * obtain device information. The second mode is applicable to scenarios where data interaction with HID devices is
 * required.
 *
 * @include <hid/hid_ddk_api.h>
 * @kit DriverDevelopmentKit
 * @library libhid.z.so
 * @syscap SystemCapability.Driver.HID.Extension
 *     File to include: <hid/hid_ddk_api.h>
 * @since 11
 */

#ifndef HID_DDK_API_H
#define HID_DDK_API_H

#include <stdint.h>
#include "hid_ddk_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Creates a device. This function is applicable to scenarios where virtual HID input devices need to be
 * simulated, such as simulating input devices like keyboards and mouse devices for automated testing. This function
 * must be used in pairs with {@link OH_Hid_DestroyDevice}.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param hidDevice Pointer to the basic information about the device to create, including the device name, vendor ID,
 *     and product ID.
 * @param hidEventProperties Pointer to the event properties related to the device to create, including the event type,
 *     key event properties, absolute coordinate event properties, and relative coordinate event properties.
 * @return **deviceID**, indicating the ID of the device that is successfully created. The value must be a non-negative
 *     integer.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_OPERATION}: The HID DDK service connection fails. Possible cause: The DDK service is
 *     not initialized. Call **OH_Hid_Init** to complete the initialization.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. The input **hidDevice** is
 *     a null pointer.
 *     <br>2. The input **hidEventProperties** is a null pointer. 3. The length of **properties** exceeds 7 characters.
 *     4. The length of **hidEventTypes** exceeds 5 characters.
 *     <br>5. The length of **hidKeys** exceeds 100 characters. 6. The length of **hidAbs** exceeds 26 characters. 7.
 *     The length of **hidRelBits** exceeds 13 characters.
 *     <br>8. The length of **hidMiscellaneous** exceeds 6 characters.
 *     <br>{@link HID_DDK_FAILURE}: The number of devices reaches the maximum value 200.
 * @since 11
 * @version 1.0
 */
int32_t OH_Hid_CreateDevice(Hid_Device *hidDevice, Hid_EventProperties *hidEventProperties);

/**
 * @brief Sends an event list to a device. Events are injected into the system through the virtual device created by
 * {@link OH_Hid_CreateDevice}, and the system processes them as real input events. This function is applicable to
 * scenarios where user input events are simulated, such as simulating key presses, mouse movements, and clicks for
 * automated testing or remote control.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param deviceId Device ID, which must be the ID of the device created by the current caller using
 *     {@link OH_Hid_CreateDevice}. The value must be a non-negative integer.
 * @param items List of the events to send. The event information includes the event type (**Hid_EventType**), code
 *     (**Hid_SynEvent**, **Hid_KeyCode**, **Hid_AbsAxes**, **Hid_RelAxes**, or **Hid_MscEvent**),
 *     and value (depending on the actual device input). The sent events will be injected into the specified device
 *     to simulate the corresponding input behavior on the device.
 * @param length Length of the event list (number of events to be sent at a time). The value range is [1, 7].
 * @return {@link HID_DDK_SUCCESS}: The API call is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_OPERATION}: The HID DDK service connection fails or the caller is not the device
 *     creator. Ensure that **OH_Hid_Init** is called to complete the initialization and the caller is the device
 *     creator.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. The device ID is less than
 *     0. 2. The length of the input parameter **length** exceeds 7 characters. 3. The input parameter **items** is a
 *     null pointer. Check the parameter validity.
 *     <br>{@link HID_DDK_NULL_PTR}: The corresponding device does not exist. Ensure that a valid device ID returned by
 *     **OH_Hid_CreateDevice** is used and the device is not destroyed.
 * @since 11
 * @version 1.0
 */
int32_t OH_Hid_EmitEvent(int32_t deviceId, const Hid_EmitItem items[], uint16_t length);

/**
 * @brief Destroys a device. This function can be used to release system resources when the virtual HID device is no
 * longer required. This function must be used in pairs with {@link OH_Hid_CreateDevice}. Only the device created by
 * the current caller can be destroyed.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param deviceId Device ID, which must be the ID of the device created by the current caller. The value must be a non-
 *     negative integer.
 * @return {@link HID_DDK_SUCCESS}: The API call is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_OPERATION}: The HID DDK service connection fails or the caller is not the device
 *     creator. Ensure that **OH_Hid_Init** is called to complete the initialization and the caller is the device
 *     creator.
 *     <br>{@link HID_DDK_NULL_PTR}: The device does not exist. Ensure that a valid device ID returned by
 *     **OH_Hid_CreateDevice** is used and the device is not destroyed.
 * @since 11
 * @version 1.0
 */
int32_t OH_Hid_DestroyDevice(int32_t deviceId);

/**
 * @brief Initializes an HID DDK. This method must be called before all other HID DDK methods. When no HID DDK function
 * is used, you must call {@link OH_Hid_Release} to release resources.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INIT_ERROR}: The DDK initialization fails.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 * @since 18
 */
int32_t OH_Hid_Init(void);

/**
 * @brief Releases an HID DDK. This function must be used in pairs with {@link OH_Hid_Init}.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 * @since 18
 */
int32_t OH_Hid_Release(void);

/**
 * @brief Opens the device specified by **deviceId** and **interfaceIndex**. This function applies to scenarios where
 * communication with a specific HID device is required. After using the device, call {@link OH_Hid_Close} to release
 * the device resources.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param deviceId ID of the device to be operated, which can be obtained by calling {@link OH_Usb_GetDevices}.
 * @param interfaceIndex Interface index for the API of the HID device.
 * @param dev Device operation handle. This is an output parameter. After the API is called successfully, a value is
 *     assigned to this parameter, indicating the opened HID device.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 *     <br>{@link HID_DDK_MEMORY_ERROR}: Memory allocation for the device fails.
 *     <br>{@link HID_DDK_IO_ERROR}: The I/O operation fails. Possible causes: The device status is abnormal or a data
 *     transmission error occurs. Check the device status and parameters.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The **dev** parameter or ***dev** is null.
 *     <br>{@link HID_DDK_DEVICE_NOT_FOUND}: No device is found based on **deviceId** and **interfaceIndex**.
 * @since 18
 */
int32_t OH_Hid_Open(uint64_t deviceId, uint8_t interfaceIndex, Hid_DeviceHandle **dev);

/**
 * @brief Closes a device. This function must be used in pairs with {@link OH_Hid_Open}. It can be used to release
 * device resources when the communication with the HID device is no longer required.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle, which must be opened and obtained by calling {@link OH_Hid_Open}. After the API
 *     is called successfully, the resources are released and the handle is set to null.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 *     <br>{@link HID_DDK_IO_ERROR}: The I/O operation fails. Possible causes: The device status is abnormal or a data
 *     transmission error occurs. Check the device status and parameters.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The **dev** parameter or ***dev** is null.
 * @since 18
 */
int32_t OH_Hid_Close(Hid_DeviceHandle **dev);

/**
 * @brief Writes an HID report to the device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle, which must be opened and obtained by calling {@link OH_Hid_Open} before being
 *     used.
 * @param data Data to be written.
 * @param length Length of the data to be written, in bytes. Ensure that the value is greater than 0 and does not
 *     exceed {@link HID_MAX_REPORT_BUFFER_SIZE}. Otherwise, the parameter verification fails.
 * @param bytesWritten Number of written bytes.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     <br>2. **data** is null. 3. The value of **length** is **0**; 4. The value of **length** exceeds
 *     {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     <br>5. **bytesWritten** is null.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 *     <br>{@link HID_DDK_IO_ERROR}: The I/O operation fails. Possible causes: The device status is abnormal or a data
 *     transmission error occurs. Check the device status and parameters.
 * @since 18
 */
int32_t OH_Hid_Write(Hid_DeviceHandle *dev, uint8_t *data, uint32_t length, uint32_t *bytesWritten);

/**
 * @brief Reads a report from the device within the specified timeout interval.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle, which must be opened and obtained by calling {@link OH_Hid_Open} before being
 *     used.
 * @param data Buffer for storing the read data.
 * @param bufSize Size of the buffer for storing the read data. Ensure that the value is greater than 0 and does not
 *     exceed {@link HID_MAX_REPORT_BUFFER_SIZE}. Otherwise, the parameter verification fails.
 * @param timeout Timeout interval, in milliseconds. If the value is greater than 0, it indicates the number of
 *     milliseconds to wait before a timeout occurs. If the value is **0**, it indicates that the operation is
 *     performed immediately. If the value is **-1**, it indicates that the operation is blocked until the data is read
 *     and no timeout occurs.
 * @param bytesRead Number of bytes to read.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     <br>2. **data** is null. 3. The value of **bufSize** is **0**. 4. The value of **bufSize** exceeds
 *     {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     <br>5. **bytesRead** is null.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 *     <br>{@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     <br>{@link HID_DDK_IO_ERROR}: The I/O operation fails. Possible causes: The device status is abnormal or a data
 *     transmission error occurs. Check the device status and parameters.
 *     <br>{@link HID_DDK_TIMEOUT}: The read operation times out.
 * @since 18
 */
int32_t OH_Hid_ReadTimeout(Hid_DeviceHandle *dev, uint8_t *data, uint32_t bufSize, int timeout, uint32_t *bytesRead);

/**
 * @brief Reads a report from the device. The blocking mode (that is, blocking remains active until data can be read)
 * is used by default. You can call {@link OH_Hid_SetNonBlocking} to change the mode.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle, which must be opened and obtained by calling {@link OH_Hid_Open} before being
 *     used.
 * @param data Buffer for storing the read data.
 * @param bufSize Size of the buffer for storing the read data. Ensure that the value is greater than 0 and does not
 *     exceed {@link HID_MAX_REPORT_BUFFER_SIZE}. Otherwise, the parameter verification fails.
 * @param bytesRead Number of bytes to read.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     <br>2. **data** is null. 3. The value of **bufSize** is **0**. 4. The value of **bufSize** exceeds
 *     {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     <br>5. **bytesRead** is null.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 *     <br>{@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     <br>{@link HID_DDK_IO_ERROR}: The I/O operation fails. Possible causes: The device status is abnormal or a data
 *     transmission error occurs. Check the device status and parameters.
 *     <br>{@link HID_DDK_TIMEOUT}: The read operation times out.
 * @since 18
 */
int32_t OH_Hid_Read(Hid_DeviceHandle *dev, uint8_t *data, uint32_t bufSize, uint32_t *bytesRead);

/**
 * @brief Sets the device read mode to non-blocking mode.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle, which must be opened and obtained by calling {@link OH_Hid_Open} before being
 *     used.
 * @param nonBlock Whether to enable the non-blocking mode for reading data. **1**: The non-blocking mode is enabled.
 *     When {@link OH_Hid_Read} is called, if the device has readable data, {@link HID_DDK_SUCCESS} is returned;
 *     <br>if the device has no readable data, {@link HID_DDK_TIMEOUT} is returned. **0**: The non-blocking mode is
 *     disabled, and the blocking mode is enabled.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     <br>2. The value of **nonBlock** is not **1** or **0**.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 * @since 18
 */
int32_t OH_Hid_SetNonBlocking(Hid_DeviceHandle *dev, int nonBlock);

/**
 * @brief Obtains the original device information.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle, which must be opened and obtained by calling {@link OH_Hid_Open} before being
 *     used.
 * @param rawDevInfo Original device information, including the vendor ID, product ID, and bus type.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     <br>2. **rawDevInfo** is null.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 *     <br>{@link HID_DDK_IO_ERROR}: The I/O operation fails. Possible causes: The device status is abnormal or a data
 *     transmission error occurs. Check the device status and parameters.
 *     <br>{@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
 */
int32_t OH_Hid_GetRawInfo(Hid_DeviceHandle *dev, Hid_RawDevInfo *rawDevInfo);

/**
 * @brief Obtains the original device name.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle, which must be opened and obtained by calling {@link OH_Hid_Open} before being
 *     used.
 * @param data Buffer for storing the read data.
 * @param bufSize Size of the buffer for storing the read data. Ensure that the value is greater than 0 and does not
 *     exceed {@link HID_MAX_REPORT_BUFFER_SIZE}. Otherwise, the parameter verification fails.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     <br>2. **data** is null. 3. The value of **bufSize** is **0**. 4. The value of **bufSize** exceeds
 *     {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 *     <br>{@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     <br>{@link HID_DDK_IO_ERROR}: The I/O operation fails. Possible causes: The device status is abnormal or a data
 *     transmission error occurs. Check the device status and parameters.
 *     <br>{@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
 */
int32_t OH_Hid_GetRawName(Hid_DeviceHandle *dev, char *data, uint32_t bufSize);

/**
 * @brief Obtains the physical address of a device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle, which must be opened and obtained by calling {@link OH_Hid_Open} before being
 *     used.
 * @param data Buffer for storing the read data.
 * @param bufSize Size of the buffer for storing the read data. Ensure that the value is greater than 0 and does not
 *     exceed {@link HID_MAX_REPORT_BUFFER_SIZE}. Otherwise, the parameter verification fails.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     <br>2. **data** is null. 3. The value of **bufSize** is **0**. 4. The value of **bufSize** exceeds
 *     {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 *     <br>{@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     <br>{@link HID_DDK_IO_ERROR}: The I/O operation fails. Possible causes: The device status is abnormal or a data
 *     transmission error occurs. Check the device status and parameters.
 *     <br>{@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
 */
int32_t OH_Hid_GetPhysicalAddress(Hid_DeviceHandle *dev, char *data, uint32_t bufSize);

/**
 * @brief Obtains the original unique identifier of a device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle, which must be opened and obtained by calling {@link OH_Hid_Open} before being
 *     used.
 * @param data Buffer for storing the read data.
 * @param bufSize Size of the buffer for storing the read data. Ensure that the value is greater than 0 and does not
 *     exceed {@link HID_MAX_REPORT_BUFFER_SIZE}. Otherwise, the parameter verification fails.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     <br>2. **data** is null. 3. The value of **bufSize** is **0**. 4. The value of **bufSize** exceeds
 *     {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 *     <br>{@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     <br>{@link HID_DDK_IO_ERROR}: The I/O operation fails. Possible causes: The device status is abnormal or a data
 *     transmission error occurs. Check the device status and parameters.
 *     <br>{@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
 */
int32_t OH_Hid_GetRawUniqueId(Hid_DeviceHandle *dev, uint8_t *data, uint32_t bufSize);

/**
 * @brief Sends an HID report of a specified type to the device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle, which must be opened and obtained by calling {@link OH_Hid_Open} before being
 *     used.
 * @param reportType Report type, which can be an input report, output report, or feature report.
 * @param data Data to be sent.
 * @param length Length of the data to be sent, in bytes. Ensure that the value is greater than 0 and does not exceed
 *     {@link HID_MAX_REPORT_BUFFER_SIZE}. Otherwise, the parameter verification fails.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     <br>2. **data** is null. 3. The value of **length** is **0**; 4. The value of **length** exceeds
 *     {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 *     <br>{@link HID_DDK_IO_ERROR}: The I/O operation fails. Possible causes: The device status is abnormal or a data
 *     transmission error occurs. Check the device status and parameters.
 *     <br>{@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
 */
int32_t OH_Hid_SendReport(Hid_DeviceHandle *dev, Hid_ReportType reportType, const uint8_t *data, uint32_t length);

/**
 * @brief Obtains an HID report of a specified type from the device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle, which must be opened and obtained by calling {@link OH_Hid_Open} before being
 *     used.
 * @param reportType Report type.
 * @param data Buffer for storing the read data.
 * @param bufSize Size of the buffer for storing the read data. Ensure that the value is greater than 0 and does not
 *     exceed {@link HID_MAX_REPORT_BUFFER_SIZE}. Otherwise, the parameter verification fails.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     <br>2. **data** is null. 3. The value of **bufSize** is **0**. 4. The value of **bufSize** exceeds
 *     {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 *     <br>{@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     <br>{@link HID_DDK_IO_ERROR}: The I/O operation fails. Possible causes: The device status is abnormal or a data
 *     transmission error occurs. Check the device status and parameters.
 *     <br>{@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
 */
int32_t OH_Hid_GetReport(Hid_DeviceHandle *dev, Hid_ReportType reportType, uint8_t *data, uint32_t bufSize);

/**
 * @brief Obtains the report descriptor of the device.
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev Device operation handle, which must be opened and obtained by calling {@link OH_Hid_Open} before being
 *     used.
 * @param buf Buffer for storing descriptors.
 * @param bufSize Size of the buffer, in bytes. Ensure that the value is greater than 0 and does not exceed
 *     {@link HID_MAX_REPORT_BUFFER_SIZE}. Otherwise, the parameter verification fails.
 * @param bytesRead Number of bytes to read.
 * @return {@link HID_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link HID_DDK_NO_PERM}: The permission verification fails. Ensure that you have declared the
 *     **ohos.permission.ACCESS_DDK_HID** permission.
 *     <br>{@link HID_DDK_INVALID_PARAMETER}: The parameter check fails. Possible causes: 1. **dev** is null.
 *     <br>2. **buf** is null. 3. The value of **bufSize** is **0**. 4. The value of **bufSize** exceeds
 *     {@link HID_MAX_REPORT_BUFFER_SIZE}.
 *     <br>5. **bytesRead** is null.
 *     <br>{@link HID_DDK_INIT_ERROR}: DDK is not initialized. Ensure that you have called {@link OH_Hid_Init} to
 *     complete the initialization.
 *     <br>{@link HID_DDK_SERVICE_ERROR}: Communication with the DDK server fails. Possible cause: An internal service
 *     error occurs. Check the current operation and device status.
 *     <br>{@link HID_DDK_MEMORY_ERROR}: The memory data copy fails.
 *     <br>{@link HID_DDK_IO_ERROR}: The I/O operation fails. Possible causes: The device status is abnormal or a data
 *     transmission error occurs. Check the device status and parameters.
 *     <br>{@link HID_DDK_INVALID_OPERATION}: This operation is not supported.
 * @since 18
 */
int32_t OH_Hid_GetReportDescriptor(Hid_DeviceHandle *dev, uint8_t *buf, uint32_t bufSize, uint32_t *bytesRead);
/** @} */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // HID_DDK_API_H