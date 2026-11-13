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
 * @addtogroup UsbDdk
 * @{
 *
 * @brief Provides USB DDK APIs to open and close USB interfaces, perform
 * non-isochronous and isochronous data transfer over USB pipes, and implement
 * control transfer and interrupt transfer. This module is applicable to scenarios
 * where underlying interaction and data communication with USB devices are required,
 * helping you efficiently develop USB device drivers.
 *
 * @syscap SystemCapability.Driver.USB.Extension
 * @since 10
 */

/**
 * @file usb_ddk_api.h
 *
 * @brief Declares the USB DDK APIs used by the host to access the device. These APIs provide functions such as USB
 * device management, configuration, and data transmission, helping developers implement underlying interaction and
 * data communication with the USB device.
 *
 * @include <usb/usb_ddk_api.h>
 * @kit DriverDevelopmentKit
 * @library libusb_ndk.z.so
 * @syscap SystemCapability.Driver.USB.Extension
 * @since 10
 */

#ifndef USB_DDK_API_H
#define USB_DDK_API_H

#include <stdint.h>

#include "ddk/ddk_types.h"
#include "usb_ddk_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Initializes the USB DDK. This method must be called before all other USB DDK methods. After using the DDK,
 * call {@link OH_Usb_Release} or {@link OH_Usb_ReleaseResource} to release resources.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails, or an internal error occurs.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_MEMORY_ERROR}: The memory allocation fails. Check the memory size and validity.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_Init(void);

/**
 * @brief Releases the USB DDK. This method is used to correctly release resources when the USB DDK is no longer used.
 * It can only be called after {@link OH_Usb_Init} is called to complete initialization.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @since 10
 * @version 1.0
 */
void OH_Usb_Release(void);

/**
 * @brief Releases the USB DDK. This method is used to correctly release resources when the USB DDK is no longer used.
 * It can only be called after {@link OH_Usb_Init} is called to complete initialization. This method returns an integer
 * value, which can be used to determine the execution result.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 * @since 18
 * @version 1.0
 */
int32_t OH_Usb_ReleaseResource(void);

/**
 * @brief Obtains the device descriptor. Ensure that the input pointer parameter is valid.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId Device ID, which can be obtained by calling {@link OH_Usb_GetDevices}. It identifies the device
 *     whose descriptor is to be obtained.
 * @param desc Output parameter, which is used to receive the device descriptor. For details, see
 *     {@link UsbDeviceDescriptor}.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: The input **desc** is a null pointer. Check the parameter validity.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_GetDeviceDescriptor(uint64_t deviceId, struct UsbDeviceDescriptor *desc);

/**
 * @brief Obtains the configuration descriptor. To prevent memory leak, use {@link OH_Usb_FreeConfigDescriptor()} to
 * release a descriptor after use.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId Device ID, which can be obtained by calling {@link OH_Usb_GetDevices}. It identifies the device
 *     whose configuration descriptor is to be obtained.
 * @param configIndex Configuration index, which corresponds to the **bConfigurationValue** field in the USB
 *     configuration descriptor.
 * @param config Output parameter, which is used to receive the configuration descriptor, including the standard
 *     configuration descriptor defined in the USB protocol and the associated interface descriptor and endpoint
 *     descriptor.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: The input **config** is a null pointer. Check the parameter validity.
 *     <br>{@link USB_DDK_IO_FAILED}: An I/O exception occurs. Check the parameters and device specifications.
 *     <br>{@link USB_DDK_MEMORY_ERROR}: The memory allocation fails. Check the memory size and validity.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_GetConfigDescriptor(
    uint64_t deviceId, uint8_t configIndex, struct UsbDdkConfigDescriptor ** const config);

/**
 * @brief Releases the configuration descriptor. To prevent memory leak, use this API to release the configuration
 * descriptor after use.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param config Configuration descriptor obtained by calling {@link OH_Usb_GetConfigDescriptor}.
 * @since 10
 * @version 1.0
 */
void OH_Usb_FreeConfigDescriptor(struct UsbDdkConfigDescriptor * const config);

/**
 * @brief Claims a USB interface exclusively. After calling this method, you must call {@link OH_Usb_ReleaseInterface}
 * to release the interface after use. Otherwise, the interface resources cannot be released.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId Device ID, which can be obtained by calling {@link OH_Usb_GetDevices}. It identifies the device to
 *     be operated.
 * @param interfaceIndex Interface index, which corresponds to **bInterfaceNumber** in the USB protocol.
 * @param interfaceHandle Output parameter, which is used to receive the declared interface operation handle. After the
 *     interface is claimed successfully, a value will be assigned to this parameter.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: The input **interfaceHandle** is a null pointer. Check the parameter
 *     validity.
 *     <br>{@link USB_DDK_MEMORY_ERROR}: The memory to be allocated exceeds the limit. Check the memory size and
 *     validity.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_ClaimInterface(uint64_t deviceId, uint8_t interfaceIndex, uint64_t *interfaceHandle);

/**
 * @brief Releases the USB interface that is claimed exclusively. Before calling this method, you must call
 * {@link OH_Usb_ClaimInterface} to claim the interface and obtain the interface handle.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle Interface operation handle, which needs to be obtained through {@link OH_Usb_ClaimInterface}.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: One or more parameters are invalid. Check the parameter validity.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_ReleaseInterface(uint64_t interfaceHandle);

/**
 * @brief Activates the alternate setting of a USB interface. Call this method when the interface working mode needs to
 * be changed.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle Interface operation handle, which needs to be obtained through {@link OH_Usb_ClaimInterface}.
 * @param settingIndex Alternate setting index, which corresponds to the **bAlternateSetting** field of the interface
 *     descriptor in the USB protocol.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: One or more parameters are invalid. Check the parameter validity.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SelectInterfaceSetting(uint64_t interfaceHandle, uint8_t settingIndex);

/**
 * @brief Obtains the activated alternate setting of a USB interface.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle Interface operation handle, which needs to be obtained through {@link OH_Usb_ClaimInterface}.
 * @param settingIndex Output parameter, which is used to receive the alternate setting index corresponding to the
 *     **bAlternateSetting** field of the interface descriptor in the USB protocol.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: The input **settingIndex** is a null pointer. Check the parameter
 *     validity.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_GetCurrentInterfaceSetting(uint64_t interfaceHandle, uint8_t *settingIndex);

/**
 * @brief Sends a control read transfer request. This API works in a synchronous manner.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle Interface operation handle, which needs to be obtained through {@link OH_Usb_ClaimInterface}.
 * @param setup Request parameters. For details, see {@link UsbControlRequestSetup}.
 * @param timeout Timeout interval, in milliseconds, which is the maximum waiting time before a response is received.
 *     The value **0** indicates that the waiting time is unlimited.
 * @param data Data buffer to be read, which is used to store the data read from the device.
 * @param dataLen Data length. The value must be greater than or equal to the data length specified by the **wLength**
 *     field in the setup data. The return value indicates the length of the actually read data.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: The input **setup**, **data**, or **dataLen** is a null pointer, or the
 *     value of **dataLen** is less than the length of the read data. Ensure that the pointer parameters are valid and
 *     the value of **dataLen** is large enough.
 *     <br>{@link USB_DDK_MEMORY_ERROR}: The attempt to copy the memory that stores the read data fails. Check the
 *     memory size and validity.
 *     <br>{@link USB_DDK_IO_FAILED}: An I/O exception occurs. Check the parameters and device specifications.
 *     <br>{@link USB_DDK_TIMEOUT}: The operation times out. Check the transmission parameters and device status.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SendControlReadRequest(uint64_t interfaceHandle, const struct UsbControlRequestSetup *setup,
    uint32_t timeout, uint8_t *data, uint32_t *dataLen);

/**
 * @brief Sends a control write transfer request. This API works in a synchronous manner.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle Interface operation handle, which needs to be obtained through {@link OH_Usb_ClaimInterface}.
 * @param setup Request parameters. For details, see {@link UsbControlRequestSetup}.
 * @param timeout Timeout interval, in milliseconds, which is the maximum waiting time before a response is received.
 *     The value **0** indicates that the waiting time is unlimited.
 * @param data Data buffer to be written, which points to the data to be sent to the device.
 * @param dataLen Data length. The value must be the same as that of the **wLength** field in the setup data and cannot
 *     exceed 1024 bytes.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: The input **setup** or **data** is a null pointer. Check the parameter
 *     validity.
 *     <br>{@link USB_DDK_MEMORY_ERROR}: The attempt to copy the memory that stores the read data fails. Check the
 *     memory size and validity.
 *     <br>{@link USB_DDK_IO_FAILED}: An I/O exception occurs. Check the parameters and device specifications.
 *     <br>{@link USB_DDK_TIMEOUT}: The operation times out. Check the transmission parameters and device status.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SendControlWriteRequest(uint64_t interfaceHandle, const struct UsbControlRequestSetup *setup,
    uint32_t timeout, const uint8_t *data, uint32_t dataLen);

/**
 * @brief Sends a pipe request. This API works in a synchronous manner. It applies to interrupt transfer and bulk
 * transfer.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param pipe Pipe used to transfer data.
 * @param devMmap Device memory map, which can be obtained by calling {@link OH_Usb_CreateDeviceMemMap}.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: The input **pipe** or **devMmap** is a null pointer, or the **devMmap**
 *     address is null. Check the parameter validity.
 *     <br>{@link USB_DDK_MEMORY_ERROR}: The attempt to copy the memory that stores the read data fails. Check the
 *     memory size and validity.
 *     <br>{@link USB_DDK_IO_FAILED}: An I/O exception occurs. Check the parameters and device specifications.
 *     <br>{@link USB_DDK_TIMEOUT}: The operation times out. Check the transmission parameters and device status.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SendPipeRequest(const struct UsbRequestPipe *pipe, UsbDeviceMemMap *devMmap);

/**
 * @brief Sends a pipe request based on the shared memory. This API returns the result synchronously. It applies to
 * interrupt transfer and bulk transfer.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param pipe Pipe used to transfer data.
 * @param ashmem Shared memory, which can be obtained through {@link OH_DDK_CreateAshmem}.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: The input **pipe** or **ashmem** is a null pointer, or the **ashmem**
 *     address is null. Check the parameter validity.
 *     <br>{@link USB_DDK_MEMORY_ERROR}: The attempt to copy the memory that stores the read data fails. Check the
 *     memory size and validity.
 *     <br>{@link USB_DDK_IO_FAILED}: An I/O exception occurs. Check the parameters and device specifications.
 *     <br>{@link USB_DDK_TIMEOUT}: The operation times out. Check the transmission parameters and device status.
 * @since 12
 */
int32_t OH_Usb_SendPipeRequestWithAshmem(const struct UsbRequestPipe *pipe, DDK_Ashmem *ashmem);

/**
 * @brief Creates a buffer. To prevent resource leaks, use {@link OH_Usb_DestroyDeviceMemMap} to destroy a buffer after
 * use.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId Device ID, which can be obtained by calling {@link OH_Usb_GetDevices}. It identifies the device for
 *     which a buffer is to be created.
 * @param size Buffer size, in bytes.
 * @param devMmap Output parameter, which is used to return the pointer to the created buffer to the caller.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: The input **devMmap** is a null pointer, or ***devMmap** is a null
 *     pointer. Check the parameter validity.
 *     <br>{@link USB_DDK_MEMORY_ERROR}: The memory mapping fails, or the memory allocation of **devMmap** fails. Check
 *     the memory size and validity.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_CreateDeviceMemMap(uint64_t deviceId, size_t size, UsbDeviceMemMap **devMmap);

/**
 * @brief Destroys a buffer. To prevent resource leaks, use this API to destroy a buffer after use.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param devMmap Destroys the buffer created by {@link OH_Usb_CreateDeviceMemMap}.
 * @since 10
 * @version 1.0
 */
void OH_Usb_DestroyDeviceMemMap(UsbDeviceMemMap *devMmap);

/**
 * @brief Obtains the USB device ID list. Ensure that the pointer parameters passed in are valid. To avoid excessive
 * memory usage, the size of the requested device ID array is recommended not to exceed 128. After using the struct,
 * release the memory of its members; otherwise, resource leaks may occur. Besides, make sure that the obtained USB
 * device ID has been filtered by **vid** in the driver configuration information.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param devices Device memory address, which is used to store the obtained device ID list and quantity. After using
 *     it, release the memory of its members; otherwise, resource leaks may occur.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: The input **devices** is a null pointer. Check the parameter validity.
 * @since 18
 */
int32_t OH_Usb_GetDevices(struct Usb_DeviceArray *devices);

/**
 * @brief Performs USB control transfer. This API returns the result synchronously.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceID Device ID, which can be obtained by calling {@link OH_Usb_GetDevices}. It identifies the device to
 *     be communicated with.
 * @param setupPacket Setup parameter that controls the transfer request, including the transfer direction and data
 *     length.
 * @param data Requested buffer for storing input or output data. The buffer size must be the same as the value of the
 *     **wLength** field in the setup packet and cannot exceed 1,024 bytes. Otherwise, the data will be truncated.
 * @param timeout Timeout interval, in milliseconds, which is the maximum waiting time before a response is received.
 *     The value **0** indicates that the waiting time is not limited.
 * @return Number of actually transferred bytes upon success (a non-negative number).
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: **setupPacket** or **data** is a null pointer. Check the parameter
 *     validity.
 *     <br>{@link USB_DDK_TIMEOUT}: Controls transfer timeout. Check the transmission parameters and device status.
 *     <br>{@link USB_DDK_IO_FAILED}: Controls transfer request I/O exceptions. Check the parameters and device
 *     specifications.
 * @since 26.0.0
 */
int32_t OH_Usb_ControlTransfer(uint64_t deviceID, const struct UsbControlRequestSetup *setupPacket, uint8_t *data,
    uint32_t timeout);

/**
 * @brief Queries and returns the non-root hub list. Ensure that the input pointer is valid. It is recommended that the
 * number of non-root hub IDs do not exceed 128 to prevent excessive memory usage. After using the struct, release the
 * memory of its members; otherwise, resource leaks may occur.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param nonRootHub Requested non-root hub memory address, which is used to store the queried non-root hub ID list and
 *     quantity. After using it, release the memory of its members; otherwise, resource leaks may occur.
 * @return {@link USB_DDK_SUCCESS}: The query is successful.
 *     <br>{@link USB_DDK_NO_PERM}: The permission check fails. Check whether the app has obtained the
 *     **ohos.permission.ACCESS_DDK_USB** permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails. Call {@link OH_Usb_Init} to
 *     complete initialization first.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}: The input **nonRootHub** is a null pointer. Check the parameter validity.
 * @since 26.0.0
 */
int32_t OH_Usb_GetNonRootHubs(struct Usb_NonRootHubArray *nonRootHub);

/**
 * @brief Creates a device memory buffer. To avoid resource leakage, call {@link OH_Usb_DestroyDeviceMemBuffer} to
 * destroy the buffer after the buffer has been used.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId [in] Device ID.
 * @param size [in] Buffer size, in bytes.
 * @param buffer [out] Data buffer, which is used to return the created buffer to the caller.
 * @return {@link USB_DDK_SUCCESS} The API is successfully called.
 *     <br>{@link USB_DDK_NO_PERM} Permission check failed. Check whether the app has obtained the
 *     ohos.permission.ACCESS_DDK_USB permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION} Failed to connect to the USB DDK service or the device driver is invalid. Call
 *     <br>{@link OH_Usb_Init} to complete initialization and check the device status corresponding to **deviceId**.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}The input parameter **buffer** is a null pointer. Check the parameter validity.
 *     <br>{@link USB_DDK_MEMORY_ERROR} Memory allocation failed. Check the memory size and validity.
 * @release OH_Usb_DestroyDeviceMemBuffer {buffer}
 * @since 26.1.0
 */
UsbDdkErrCode OH_Usb_CreateDeviceMemBuffer(uint64_t deviceId, uint32_t size, uint8_t **buffer);
 
/**
 * @brief Destroy the device memory buffer. To prevent resource leakage, destroy the buffer immediately after using the
 * buffer.
 *
 * @param buffer [in,out] Destroy the buffer created by {@link OH_Usb_CreateDeviceMemBuffer}.
 * @return {@link USB_DDK_SUCCESS} The API is successfully called.
 *     <br>{@link USB_DDK_INVALID_PARAMETER}The input parameter **buffer** or ***buffer** is null, or ***buffer** is
 *     invalid. Check the parameter validity.
 *     <br>{@link USB_DDK_MEMORY_ERROR} Failed to demap the memory. Please check the buffer and device status.
 * @since 26.1.0
 */
UsbDdkErrCode OH_Usb_DestroyDeviceMemBuffer(uint8_t **buffer);
 
/**
 * @brief Send a pipe write request. This interface operates in synchronous mode and is suitable for interrupt transfers
 * and bulk transfers.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param pipe [in] Pipe used to transfer data.
 * @param buffer [in] Data buffer, that is, the device memory-mapped buffer.
 * @param bufferSize [in] Buffer size, in bytes.
 * @param offset [in] Start position of the data in the buffer, in bytes.
 * @param writeLength [in] Length of the buffer to be used, indicating the length of the data written from the
 *     offset position, in bytes.
 * @param transferredLength [out] Output parameter, indicating the length of the actually transmitted data, in
 *     bytes. This parameter is valid only when the function returns 0.
 * @return {@link USB_DDK_SUCCESS} The API is successfully called.
 *     <br>{@link USB_DDK_NO_PERM} Permission check failed. Check whether the app has obtained the
 *     ohos.permission.ACCESS_DDK_USB permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION} Failed to connect to the USB DDK service. Call {@link OH_Usb_Init} to complete
 *     initialization.
 *     <br>{@link USB_DDK_INVALID_PARAMETER} Parameter verification failed. Check the parameter validity. Possible causes:
 *     1. **pipe**, **buffer**, or **transferredLength** is a null pointer.
 *     <br>2. **offset** is greater than **bufferSize** or the sum of **offset** and **writeLength** is greater than
 *     **bufferSize**. 3. The direction of the endpoint in **pipe** is incorrect.
 *     <br>{@link USB_DDK_MEMORY_ERROR} Failed to copy the memory for storing write data. Check the memory size and
 *     validity.
 *     <br>{@link USB_DDK_IO_FAILED} Data I/O error. Check parameters and device specifications.
 *     <br>{@link USB_DDK_TIMEOUT} Operation timed out. Check the transmission parameters and device status.
 * @since 26.1.0
 */
UsbDdkErrCode OH_Usb_WritePipe(const struct UsbRequestPipe *pipe, uint8_t *buffer, uint32_t bufferSize,
    uint32_t offset, uint32_t writeLength, uint32_t *transferredLength);
 
/**
 * @brief Send a pipe read request. This interface operates in synchronous mode and is suitable for interrupt transfers
 * and bulk transfers.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param pipe [in] Pipe used to transfer data.
 * @param buffer [in] Data buffer, that is, the device memory-mapped buffer.
 * @param bufferSize [in] Buffer size, in bytes.
 * @param offset [in] Start position of the data in the buffer, in bytes.
 * @param readLength [in] Length of the buffer to be used, indicating the length of the data read from the offset
 *     position, in bytes.
 * @param transferredLength [out] Output parameter, indicating the length of the actually transmitted data, in
 *     bytes. This parameter is valid only when the function returns 0.
 * @return {@link USB_DDK_SUCCESS} The API is successfully called.
 *     <br>{@link USB_DDK_NO_PERM} Permission check failed. Check whether the app has obtained the
 *     ohos.permission.ACCESS_DDK_USB permission.
 *     <br>{@link USB_DDK_INVALID_OPERATION} Failed to connect to the USB DDK service. Call {@link OH_Usb_Init} to complete
 *     initialization.
 *     <br>{@link USB_DDK_INVALID_PARAMETER} Parameter verification failed. Check the parameter validity. Possible causes:
 *     1. **pipe**, **buffer**, or **transferredLength** is a null pointer.
 *     <br>2. **offset** is greater than **bufferSize** or the sum of **offset** and **readLength** is greater than
 *     **bufferSize**. 3. The direction of the endpoint in **pipe** is incorrect.
 *     <br>{@link USB_DDK_MEMORY_ERROR} Failed to copy the memory for storing read data. Check the memory size and validity.
 *     <br>{@link USB_DDK_IO_FAILED} Data I/O error. Check parameters and device specifications.
 *     <br>{@link USB_DDK_TIMEOUT} Operation timed out. Check the transmission parameters and device status.
 * @since 26.1.0
 */
UsbDdkErrCode OH_Usb_ReadPipe(const struct UsbRequestPipe *pipe, uint8_t *buffer, uint32_t bufferSize,
    uint32_t offset, uint32_t readLength, uint32_t *transferredLength);
/** @} */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // USB_DDK_API_H