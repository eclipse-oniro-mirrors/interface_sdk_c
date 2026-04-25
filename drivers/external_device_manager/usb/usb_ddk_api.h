/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
 * @brief Provides USB DDK APIs to open and close USB interfaces, perform non-isochronous and isochronous\n
 * data transfer over USB pipes, and implement control transfer and interrupt transfer, etc.
 *
 * @syscap SystemCapability.Driver.USB.Extension
 * @since 10
 * @version 1.0
 */

/**
 * @file usb_ddk_api.h
 *
 * @brief Declares the USB DDK APIs used by the USB host to access USB devices.
 *
 * @kit DriverDevelopmentKit
 * @library libusb_ndk.z.so
 * @syscap SystemCapability.Driver.USB.Extension
 * @since 10
 * @version 1.0
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
 * @brief Initializes the USB DDK.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails, or an internal error occurs.
 *     {@link USB_DDK_NO_PERM}: The permission check fails.
 *     {@link USB_DDK_MEMORY_ERROR}: The memory allocation fails.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_Init(void);

/**
 * @brief Releases the USB DDK.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @since 10
 * @version 1.0
 */
void OH_Usb_Release(void);

/**
 * @brief Releases the USB DDK.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_NO_PERM}: The permission check fails.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails.
 * @since 18
 * @version 1.0
 */
int32_t OH_Usb_ReleaseResource(void);

/**
 * @brief Obtains the device descriptor.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId Device ID.
 * @param desc Device descriptor. For details, see {@link UsbDeviceDescriptor}.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_NO_PERM}: The permission check fails.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails.
 *     {@link USB_DDK_INVALID_PARAMETER}: The input **desc** is a null pointer.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_GetDeviceDescriptor(uint64_t deviceId, struct UsbDeviceDescriptor *desc);

/**
 * @brief Obtains the configuration descriptor. To avoid memory leakage, use {@link OH_Usb_FreeConfigDescriptor} to
 * release a descriptor after use.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId Device ID.
 * @param configIndex Configuration index, which corresponds to the **bConfigurationValue** field in the USB
 *     configuration descriptor.
 * @param config Configuration descriptor, which includes the standard configuration descriptor defined in the USB
 *     protocol and the associated interface descriptor and endpoint descriptor.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_NO_PERM}: The permission check fails.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails.
 *     {@link USB_DDK_INVALID_PARAMETER}: The input **config** is a null pointer.
 *     {@link USB_DDK_IO_FAILED}: An I/O exception occurs.
 *     {@link USB_DDK_MEMORY_ERROR}: The memory allocation fails.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_GetConfigDescriptor(
    uint64_t deviceId, uint8_t configIndex, struct UsbDdkConfigDescriptor ** const config);

/**
 * @brief Releases a configuration descriptor after use to prevent memory leakage.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param config Configuration descriptor, which is obtained by calling {@link OH_Usb_GetConfigDescriptor}.
 * @since 10
 * @version 1.0
 */
void OH_Usb_FreeConfigDescriptor(struct UsbDdkConfigDescriptor * const config);

/**
 * @brief Claims a USB interface.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId Device ID.
 * @param interfaceIndex Interface index, which corresponds to {@link bInterfaceNumber} in the USB protocol.
 * @param interfaceHandle Interface operation handle. After the interface is claimed successfully, a value will be
 *     assigned to this parameter.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_NO_PERM}: The permission check fails.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails.
 *     {@link USB_DDK_INVALID_PARAMETER}: The input **interfaceHandle** is a null pointer.
 *     {@link USB_DDK_MEMORY_ERROR}: The memory to be allocated exceeds the limit.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_ClaimInterface(uint64_t deviceId, uint8_t interfaceIndex, uint64_t *interfaceHandle);

/**
 * @brief Releases a USB interface.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle Interface operation handle.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_NO_PERM}: The permission check fails.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails.
 *     {@link USB_DDK_INVALID_PARAMETER}: One or more parameters are invalid.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_ReleaseInterface(uint64_t interfaceHandle);

/**
 * @brief Activates the alternate setting of a USB interface.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle Interface operation handle.
 * @param settingIndex Alternate setting index, which corresponds to the **bAlternateSetting** field of the interface
 *     descriptor in the USB protocol.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_NO_PERM}: The permission check fails.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails.
 *     {@link USB_DDK_INVALID_PARAMETER}: One or more parameters are invalid.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SelectInterfaceSetting(uint64_t interfaceHandle, uint8_t settingIndex);

/**
 * @brief Obtains the activated alternate setting of a USB interface.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle Interface operation handle.
 * @param settingIndex Alternate setting index, which corresponds to the **bAlternateSetting** field of the interface
 *     descriptor in the USB protocol.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_NO_PERM}: The permission check fails.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails.
 *     {@link USB_DDK_INVALID_PARAMETER}: The input **settingIndex** is a null pointer.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_GetCurrentInterfaceSetting(uint64_t interfaceHandle, uint8_t *settingIndex);

/**
 * @brief Sends a control read transfer request. This API works in a synchronous manner.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle Interface operation handle.
 * @param setup Request parameters. For details, see {@link UsbControlRequestSetup}.
 * @param timeout Timeout duration, in ms.
 * @param data Data to transfer.
 * @param dataLen Data length. The return value indicates the length of the actually read data.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_FAILED}: The permission check fails.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails.
 *     {@link USB_DDK_INVALID_PARAMETER}: The input **setup**, **data**, or **dataLen** is a null pointer, or the value
 *     of **datalen** is less than the length of the read data.
 *     {@link USB_DDK_MEMORY_ERROR}: The attempt to copy the memory that stores the read data fails.
 *     {@link USB_DDK_IO_FAILED}: An I/O exception occurs.
 *     {@link USB_DDK_TIMEOUT}: The operation times out.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SendControlReadRequest(uint64_t interfaceHandle, const struct UsbControlRequestSetup *setup,
    uint32_t timeout, uint8_t *data, uint32_t *dataLen);

/**
 * @brief Sends a control write transfer request. This API works in a synchronous manner.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle Interface operation handle.
 * @param setup Request parameters. For details, see {@link UsbControlRequestSetup}.
 * @param timeout Timeout duration, in ms.
 * @param data Data to transfer.
 * @param dataLen Data length.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_FAILED}: The permission check fails.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails.
 *     {@link USB_DDK_INVALID_PARAMETER}: The input **setup** or **data** is a null pointer.
 *     {@link USB_DDK_MEMORY_ERROR}: The attempt to copy the memory that stores the read data fails.
 *     {@link USB_DDK_IO_FAILED}: An I/O exception occurs.
 *     {@link USB_DDK_TIMEOUT}: The operation times out.
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
 * @param devMmap Data buffer, which can be obtained by calling {@link OH_Usb_CreateDeviceMemMap}.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_NO_PERM}: The permission check fails.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails.
 *     {@link USB_DDK_INVALID_PARAMETER}: The input **pipe** or **devMmap** is a null pointer, or the **devMmap**
 *     address is null.
 *     {@link USB_DDK_MEMORY_ERROR}: The attempt to copy the memory that stores the read data fails.
 *     {@link USB_DDK_IO_FAILED}: An I/O exception occurs.
 *     {@link USB_DDK_TIMEOUT}: The operation times out.
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
 *     {@link USB_DDK_NO_PERM}: The permission check fails.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails.
 *     {@link USB_DDK_INVALID_PARAMETER}: The input **pipe** or **ashmem** is a null pointer, or the **ashmem** address
 *     is null.
 *     {@link USB_DDK_MEMORY_ERROR}: The attempt to copy the memory that stores the read data fails.
 *     {@link USB_DDK_IO_FAILED}: An I/O exception occurs.
 *     {@link USB_DDK_TIMEOUT}: The operation times out.
 * @since 12
 */
int32_t OH_Usb_SendPipeRequestWithAshmem(const struct UsbRequestPipe *pipe, DDK_Ashmem *ashmem);

/**
 * @brief Creates a buffer. To avoid resource leakage, use {@link OH_Usb_DestroyDeviceMemMap} to destroy a buffer after
 * use.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId Device ID.
 * @param size Buffer size.
 * @param devMmap Data memory map, through which the created buffer is returned to the caller.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_NO_PERM}: The permission check fails.
 *     {@link USB_DDK_INVALID_PARAMETER}: The input parameter **devMmap** or ***devMmap** is a null pointer.
 *     {@link USB_DDK_MEMORY_ERROR}: The memory mapping fails, or the memory allocation of **devMmap** fails.
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_CreateDeviceMemMap(uint64_t deviceId, size_t size, UsbDeviceMemMap **devMmap);

/**
 * @brief Destroys a buffer. To prevent resource leakage, destroy a buffer in time after use.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param devMmap Destroys the buffer created by calling {@link OH_Usb_CreateDeviceMemMap}.
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
 * @param devices Device memory address, which is used to store the obtained device ID list and quantity.
 * @return {@link USB_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_DDK_NO_PERM}: The permission check fails.
 *     {@link USB_DDK_INVALID_OPERATION}: The USB DDK service connection fails.
 *     {@link USB_DDK_INVALID_PARAMETER}: The input **devices** is a null pointer.
 * @since 18
 */
int32_t OH_Usb_GetDevices(struct Usb_DeviceArray *devices);

/**
 * @brief Performs a USB control transfer. This API works in a synchronous manner.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceID An ID for the device to communicate with
 * @param setupPacket Configuration parameters for the setup packet in control transfer requests
 * @param data A suitably-sized data buffer for either input or output based on the direction bits
 *     within bmRequestType.
 * @param timeout Timeout (in milliseconds) that this function should wait before giving up due to no response being
 *     received. For an unlimited timeout, use value 0.
 * @return on success, the number of bytes actually transferred.
 *     {@link USB_DDK_NO_PERM} Permission authentication failed.
 *     {@link USB_DDK_INVALID_OPERATION} DDK Service not initialized. Please invoke {@link OH_Usb_Init} to complete the
 *     initialization process first.
 *     {@link USB_DDK_INVALID_PARAMETER} The setupPacket or data parameters are invalid.
 *     {@link USB_DDK_TIMEOUT} The control transfer timed out.
 *     {@link USB_DDK_IO_FAILED} Control transfer request I/O exception.
 * @since 26.0.0
 */
int32_t OH_Usb_ControlTransfer(uint64_t deviceID, const struct UsbControlRequestSetup *setupPacket, uint8_t *data,
    uint32_t timeout);

/**
 * @brief Queries and returns the list of non-root hubs. Ensure that the pointer parameters passed in are valid. To
 * avoid excessive memory usage, the size of the requested non-root hub ID array is recommended not to exceed 128.
 * After using the struct, release the memory of its members; otherwise, resource leaks may occur.
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param nonRootHub Returns the list of queried non-root hubs.
 * @return {@link USB_DDK_SUCCESS} Query operation successful.
 *     {@link USB_DDK_NO_PERM} Permission authentication failed.
 *     {@link USB_DDK_INVALID_OPERATION} DDK Service not initialized. Please invoke {@link OH_Usb_Init} to complete the
 *     initialization process first.
 *     {@link USB_DDK_INVALID_PARAMETER} The parameter nonRootHub is null.
 * @since 26.0.0
 */
int32_t OH_Usb_GetNonRootHubs(struct Usb_NonRootHubArray *nonRootHub);
/** @} */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // USB_DDK_API_H