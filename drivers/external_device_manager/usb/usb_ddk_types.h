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
 * @file usb_ddk_types.h
 *
 * @brief Provides the enumeration types and structures used in USB DDK APIs, including core data structures such as
 * USB device description, control transfer, and request pipe, to facilitate driver development.
 *
 * @include <usb/usb_ddk_types.h>
 * @kit DriverDevelopmentKit
 * @library libusb_ndk.z.so
 * @syscap SystemCapability.Driver.USB.Extension
 * @since 10
 */

#ifndef USB_DDK_TYPES_H
#define USB_DDK_TYPES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief Setup data for control transfer. It corresponds to <b>Setup Data</b> in the USB protocol.
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbControlRequestSetup {
    /**
     * Request type.
     */
    uint8_t bmRequestType;
    /**
     * Specific request.
     */
    uint8_t bRequest;
    /**
     * Value corresponding to **wValue** in the USB protocol. Its meaning varies according to the request.
     */
    uint16_t wValue;
    /**
     * Index corresponding to **wIndex** in the USB protocol. It is usually used to pass the index or offset. Its
     * meaning varies according to the request.
     */
    uint16_t wIndex;
    /**
     * Data length corresponding to **wLength** in the USB protocol. If data is transferred, this field indicates the
     * number of transferred bytes.
     */
    uint16_t wLength;
} __attribute__((aligned(8))) UsbControlRequestSetup;

/**
 * @brief Defines standard device descriptors, which correspond to **Standard Device Descriptor** in the USB protocol.
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbDeviceDescriptor {
    /**
     * Size of the descriptor, in bytes.
     */
    uint8_t bLength;
    /**
     * Descriptor type.
     */
    uint8_t bDescriptorType;
    /**
     * Version of the USB protocol.
     */
    uint16_t bcdUSB;
    /**
     * Device class code allocated by the USB-IF.
     */
    uint8_t bDeviceClass;
    /**
     * Device subclass code allocated by the USB-IF. The value is limited by that of **bDeviceClass**.
     */
    uint8_t bDeviceSubClass;
    /**
     * Device protocol code allocated by the USB-IF. The value is limited by that of **bDeviceClass** and
     * **bDeviceSubClass**.
     */
    uint8_t bDeviceProtocol;
    /**
     * Maximum packet size of endpoint 0 (control endpoint). Only values 8, 16, 32, and 64 are valid.
     */
    uint8_t bMaxPacketSize0;
    /**
     * Vendor ID allocated by USB-IF.
     */
    uint16_t idVendor;
    /**
     * Product ID allocated by the vendor.
     */
    uint16_t idProduct;
    /**
     * Device version number.
     */
    uint16_t bcdDevice;
    /**
     * Index of the string descriptor that describes the vendor.
     */
    uint8_t iManufacturer;
    /**
     * Index of the string descriptor that describes the product.
     */
    uint8_t iProduct;
    /**
     * Index of the string descriptor that describes the device SN.
     */
    uint8_t iSerialNumber;
    /**
     * Configuration quantity.
     */
    uint8_t bNumConfigurations;
} __attribute__((aligned(8))) UsbDeviceDescriptor;

/**
 * @brief Defines standard configuration descriptors, which correspond to **Standard Configuration Descriptor** in the
 * USB protocol.
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbConfigDescriptor {
    /**
     * Size of this descriptor, in bytes.
     */
    uint8_t bLength;
    /**
     * Descriptor type.
     */
    uint8_t bDescriptorType;
    /**
     * Total length of the configuration descriptor, in bytes, including the configuration, interface, endpoint, and
     * class- or vendor-specific descriptors.
     */
    uint16_t wTotalLength;
    /**
     * Number of interfaces supported by the configuration.
     */
    uint8_t bNumInterfaces;
    /**
     * Configuration index, which is used to select the configuration.
     */
    uint8_t bConfigurationValue;
    /**
     * Index of the string descriptor that describes the configuration.
     */
    uint8_t iConfiguration;
    /**
     * Configuration attributes, including the power mode and remote wakeup.
     */
    uint8_t bmAttributes;
    /**
     * Maximum power consumption of the bus-powered USB device, in 2 mA.
     */
    uint8_t bMaxPower;
} __attribute__((packed)) UsbConfigDescriptor;

/**
 * @brief Defines standard interface descriptors, which correspond to **Standard Interface Descriptor** in the USB
 * protocol.
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbInterfaceDescriptor {
    /**
     * Size of this descriptor, in bytes.
     */
    uint8_t bLength;
    /**
     * Descriptor type.
     */
    uint8_t bDescriptorType;
    /**
     * Interface ID.
     */
    uint8_t bInterfaceNumber;
    /**
     * Value used to select the alternate setting of the interface.
     */
    uint8_t bAlternateSetting;
    /**
     * Number of endpoints (excluding endpoint 0) used by the interface.
     */
    uint8_t bNumEndpoints;
    /**
     * Interface class code allocated by the USB-IF.
     */
    uint8_t bInterfaceClass;
    /**
     * Interface subclass code allocated by the USB-IF. The value is limited by that of **bInterfaceClass**.
     */
    uint8_t bInterfaceSubClass;
    /**
     * Interface protocol code allocated by the USB-IF. The value is limited by that of **bInterfaceClass** and
     * **bInterfaceSubClass**.
     */
    uint8_t bInterfaceProtocol;
    /**
     * Index of the string descriptor that describes the interface.
     */
    uint8_t iInterface;
} __attribute__((packed)) UsbInterfaceDescriptor;

/**
 * @brief Defines standard endpoint descriptors, which correspond to **Standard Endpoint Descriptor** in the USB
 * protocol.
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbEndpointDescriptor {
    /**
     * Size of this descriptor, in bytes.
     */
    uint8_t bLength;
    /**
     * Descriptor type.
     */
    uint8_t bDescriptorType;
    /**
     * Endpoint address, including the endpoint number and endpoint direction.
     */
    uint8_t bEndpointAddress;
    /**
     * Endpoint attributes, including the transfer type, synchronization type, and usage type.
     */
    uint8_t bmAttributes;
    /**
     * Maximum packet size supported by an endpoint, in bytes.
     */
    uint16_t wMaxPacketSize;
    /**
     * Interval for polling endpoints for data transfer.
     */
    uint8_t bInterval;
    /**
     * Refresh rate for audio devices.
     */
    uint8_t bRefresh;
    /**
     * Endpoint synchronization address for audio devices.
     */
    uint8_t bSynchAddress;
} __attribute__((packed)) UsbEndpointDescriptor;

/**
 * @brief Defines endpoint descriptors, including standard endpoint descriptors and descriptors that are not parsed.
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbDdkEndpointDescriptor {
    /**
     * Standard endpoint descriptor.
     */
    struct UsbEndpointDescriptor endpointDescriptor;
    /**
     * Pointer to the unresolved descriptor, including class- or vendor-specific descriptors.
     */
    const uint8_t *extra;
    /**
     * Length of the unresolved descriptor.
     */
    uint32_t extraLength;
} UsbDdkEndpointDescriptor;

/**
 * @brief Defines interface descriptors, including standard interface descriptors and endpoint descriptors.
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbDdkInterfaceDescriptor {
    /**
     * Standard USB interface descriptor.
     */
    struct UsbInterfaceDescriptor interfaceDescriptor;
    /**
     * Endpoint descriptor contained in the interface. This parameter can be a null pointer, indicating that there is
     * no endpoint (excluding control endpoint 0).
     */
    struct UsbDdkEndpointDescriptor *endPoint;
    /**
     * Pointer to the unresolved descriptor, including class- or vendor-specific descriptors.
     */
    const uint8_t *extra;
    /**
     * Length of the unresolved descriptor.
     */
    uint32_t extraLength;
} UsbDdkInterfaceDescriptor;

/**
 * @brief Defines a USB DDK API, which is a collection of alternate settings for a particular USB interface.
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbDdkInterface {
    /**
     * Number of alternate settings of the USB interface.
     */
    uint8_t numAltsetting;
    /**
     * Pointer to the array of alternate settings of the USB interface. The length of the array is specified
     * by **numAltsetting**.
     */
    struct UsbDdkInterfaceDescriptor *altsetting;
} UsbDdkInterface;

/**
 * @brief Defines configuration descriptors, including standard configuration descriptors and interface descriptors.
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbDdkConfigDescriptor {
    /**
     * Standard configuration descriptor.
     */
    struct UsbConfigDescriptor configDescriptor;
    /**
     * Interfaces contained in the configuration.
     */
    struct UsbDdkInterface *interface;
    /**
     * Pointer to the unresolved descriptor, including class- or vendor-specific descriptors.
     */
    const uint8_t *extra;
    /**
     * Length of the unresolved descriptor.
     */
    uint32_t extraLength;
} UsbDdkConfigDescriptor;

/**
 * @brief Defines a request pipe, which is actually a USB data transfer request. It describes the basic configuration
 * parameters for USB data transfer, including the interface handle, endpoint address, and timeout interval. This API
 * applies to scenarios where USB data transfer is required.
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbRequestPipe {
    /**
     * Interface handle, which identifies an interface on the USB device. The handle is obtained by calling
     * {@link OH_Usb_ClaimInterface}.
     */
    uint64_t interfaceHandle;
    /**
     * Timeout interval, in milliseconds. The value **0** indicates that the operation is performed until it is
     * complete. A non-zero value indicates that the operation times out if it is not complete within the specified
     * milliseconds.
     */
    uint32_t timeout;
    /**
     * Endpoint address.
     */
    uint8_t endpoint;
} __attribute__((aligned(8))) UsbRequestPipe;

/**
 * @brief Defines the device memory map created by calling {@link OH_Usb_CreateDeviceMemMap}. A buffer using the device
 * memory map can provide better data transfer performance.
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbDeviceMemMap {
    /**
     * Buffer address.
     */
    uint8_t * const address;
    /**
     * Buffer size, in bytes. The value must be greater than 0.
     */
    const size_t size;
    /**
     * Offset of the used buffer. The default value is **0**, indicating that there is no offset. The offset is
     * calculated from the buffer address. The sum of **offset** and **bufferLength** must be less than or equal 
     * to **size**.
     */
    uint32_t offset;
    /**
     * Length of the used buffer. By default, the value is equal to the buffer size, indicating that the entire buffer
     * is used. The sum of **offset** and **bufferLength** must be less than or equal to **size**.
     */
    uint32_t bufferLength;
    /**
     * Length of the data actually transferred, in bytes.
     */
    uint32_t transferedLength;
} UsbDeviceMemMap;

/**
 * @brief Enumerates the USB DDK error code definitions.
 *
 * @since 10
 * @version 1.0
 */
typedef enum {
    /**
     * Operation succeeded.
     */
    USB_DDK_SUCCESS = 0,
    /**
     * Operation failed.
     * @deprecated since 16
     */
    USB_DDK_FAILED = -1,
    /**
     * No permission. Ensure that you have obtained the **ohos.permission.ACCESS_DDK_USB** permission.
     * @since 14
     */
    USB_DDK_NO_PERM = 201,
    /**
     * Invalid parameter. Check the validity of the input parameter, including whether the pointer is null and whether
     * the value range is valid. The value is **-2** in versions earlier than API version 16.
     */
    USB_DDK_INVALID_PARAMETER = 401,
    /**
     * Memory-related error, for example, insufficient memory, memory data copy failure, or memory application failure.
     * Check whether the available system memory is sufficient and whether the memory operation parameters are correct.
     * The value is **-3** in versions earlier than API version 16.
     */
    USB_DDK_MEMORY_ERROR = 27400001,
    /**
     * Null pointer error. For example, the input pointer parameter is null. Check whether the input pointer parameter
     * is valid.
     * @deprecated since 16
     */
    USB_DDK_NULL_PTR = -5,
    /**
     * The device is busy. For example, the device is performing other operations or the device resources are occupied.
     * Wait until the device is idle and try again, or release the occupied device resources.
     * @deprecated since 16
     */
    USB_DDK_DEVICE_BUSY = -6,
    /**
     * Invalid operation, for example, calling an API before the device is initialized or performing an operation when
     * the device is in an incorrect state. Check whether the DDK has been initialized and whether the API handle is
     * valid. The value is **-4** in versions earlier than API version 16.
     */
    USB_DDK_INVALID_OPERATION = 27400002,
    /**
     * Device I/O operation failure. Check whether the device connection is normal and whether the device supports the
     * operation.
     * @since 14
     */
    USB_DDK_IO_FAILED = 27400003,
    /**
     * Transfer timed out. Check whether the device response is normal or increase the timeout interval. The value
     * is **-7** in versions earlier than API version 16.
     */
    USB_DDK_TIMEOUT = 27400004
} UsbDdkErrCode;

/**
 * @brief Defines the device ID array, which is used to store the device IDs and device quantity obtained using
 * {@link OH_Usb_GetDevices}. After using the structure, you must release the memory allocated for the device ID array.
 * Otherwise, resource leaks may occur.
 *
 * @since 18
 */
typedef struct Usb_DeviceArray {
    /**
     * Pointer to the start address of the device ID array that you have applied for. To avoid excessive memory
     * consumption, it is recommended that the maximum size of the allocated array be 128.
     */
    uint64_t* deviceIds;
    /**
     * Device quantity. Device IDs are obtained by traversing **deviceIds** based on the value of this parameter. If
     * the value is **0**, there is no USB device.
     */
    uint32_t num;
} Usb_DeviceArray;

/**
 * @brief Defines the non-root hub array, which is used to store the non-root hub IDs and quantity obtained using
 * {@link OH_Usb_GetNonRootHubs}. After using the structure, you must release the memory allocated for the non-root hub
 * ID array. Otherwise, resource leaks may occur.
 *
 * @since 26.0.0
 */
typedef struct Usb_NonRootHubArray {
    /**
     * Start address of the non-root hub ID array. It is recommended that the number of non-root hub IDs not exceed 128
     * to prevent excessive memory usage. The device ID of a non-root USB hub is constructed by left-shifting its bus
     * number by 32 bits and adding it to its device address.
     */
    uint64_t* nonRootHubIds;

    /**
     * Number of returned non-root hubs. The system traverses **nonRootHubIds** to obtain the non-root hub ID based on
     * the number. If the value is **0**, no non-root hub exists.
     */
    uint32_t num;
} Usb_NonRootHubArray;
#ifdef __cplusplus
}
#endif /* __cplusplus */

/** @} */

#endif // USB_DDK_TYPES_H