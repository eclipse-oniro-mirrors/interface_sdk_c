/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @brief Provides USB DDK types and declares the macros, enumerated variables, and
 * data structures required by the USB DDK APIs.
 *
 * @syscap SystemCapability.Driver.USB.Extension
 * @since 10
 * @version 1.0
 */

/**
 * @file usb_ddk_types.h
 *
 * @brief 提供USB DDK中的枚举变量、结构体定义与宏定义。
 *
 * @kit DriverDevelopmentKit
 * @library libusb_ndk.z.so
 * @syscap SystemCapability.Driver.USB.Extension
 * @since 10
 * @version 1.0
 */

#ifndef USB_DDK_TYPES_H
#define USB_DDK_TYPES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief 控制传输setup包，对应USB协议中的Setup Data。
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbControlRequestSetup {
    /**
     * 请求类型。
     */
    uint8_t bmRequestType;
    /**
     * 具体的请求。
     */
    uint8_t bRequest;
    /**
     * 具体的请求不同，其代表的含义不一样。
     */
    uint16_t wValue;
    /**
     * 具体的请求不同，其代表的含义不一样，通常用来传递索引或者偏移量。
     */
    uint16_t wIndex;
    /**
     * 如果有数据阶段的传输，其代表传输的字节个数。
     */
    uint16_t wLength;
} __attribute__((aligned(8))) UsbControlRequestSetup;

/**
 * @brief 标准设备描述符，对应USB协议中Standard Device Descriptor。
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbDeviceDescriptor {
    /**
     * 该描述符的大小，单位为字节。
     */
    uint8_t bLength;
    /**
     * 描述符类型。
     */
    uint8_t bDescriptorType;
    /**
     * USB协议版本号。
     */
    uint16_t bcdUSB;
    /**
     * 由USB标准化组织（USB-IF）分配的设备类代码。
     */
    uint8_t bDeviceClass;
    /**
     * 由USB标准化组织（USB-IF）分配的子类代码，其值由bDeviceClass的值限定。
     */
    uint8_t bDeviceSubClass;
    /**
     * 由USB标准化组织（USB-IF）分配的协议代码，其值由bDeviceClass和bDeviceSubClass的值限定。
     */
    uint8_t bDeviceProtocol;
    /**
     * 端点零的最大包大小，只有8，16，32，64是合法的。
     */
    uint8_t bMaxPacketSize0;
    /**
     * 由USB标准化组织（USB-IF）分配的厂商编号。
     */
    uint16_t idVendor;
    /**
     * 由厂商分配的产品编号。
     */
    uint16_t idProduct;
    /**
     * 设备版本编号。
     */
    uint16_t bcdDevice;
    /**
     * 描述厂商的字符串描述符的索引。
     */
    uint8_t iManufacturer;
    /**
     * 描述产品的字符串描述符的索引。
     */
    uint8_t iProduct;
    /**
     * 描述设备序列号的字符串描述符的索引。
     */
    uint8_t iSerialNumber;
    /**
     * 配置数量。
     */
    uint8_t bNumConfigurations;
} __attribute__((aligned(8))) UsbDeviceDescriptor;

/**
 * @brief 标准配置描述符，对应USB协议中Standard Configuration Descriptor。
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbConfigDescriptor {
    /**
     * 该描述符的大小，单位为字节。
     */
    uint8_t bLength;
    /**
     * 描述符类型。
     */
    uint8_t bDescriptorType;
    /**
     * 该配置描述符的总长度，包含配置、接口、端点和特定于类或供应商的描述符。
     */
    uint16_t wTotalLength;
    /**
     * 该配置所支持的接口数量。
     */
    uint8_t bNumInterfaces;
    /**
     * 设置配置所需要的参数，用来选择当前配置。
     */
    uint8_t bConfigurationValue;
    /**
     * 描述该配置的字符串描述符的索引。
     */
    uint8_t iConfiguration;
    /**
     * 配置属性，包含供电模式，远程唤醒等配置。
     */
    uint8_t bmAttributes;
    /**
     * 总线供电的USB设备的最大功耗，以2mA为单位。
     */
    uint8_t bMaxPower;
} __attribute__((packed)) UsbConfigDescriptor;

/**
 * @brief 标准接口描述符，对应USB协议中Standard Interface Descriptor。
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbInterfaceDescriptor {
    /**
     * 该描述符的大小，单位为字节。
     */
    uint8_t bLength;
    /**
     * 描述符类型。
     */
    uint8_t bDescriptorType;
    /**
     * 接口编号。
     */
    uint8_t bInterfaceNumber;
    /**
     * 用来选择该接口的备用配置的值。
     */
    uint8_t bAlternateSetting;
    /**
     * 该接口所使用的端点数量（不包括端点零）。
     */
    uint8_t bNumEndpoints;
    /**
     * 由USB标准化组织（USB-IF）分配的设备类代码。
     */
    uint8_t bInterfaceClass;
    /**
     * 由USB标准化组织（USB-IF）分配的子类代码，其值由bInterfaceClass的值限定。
     */
    uint8_t bInterfaceSubClass;
    /**
     * 由USB标准化组织（USB-IF）分配的协议代码，其值由bInterfaceClass和bInterfaceSubClass的值限定。
     */
    uint8_t bInterfaceProtocol;
    /**
     * 描述该接口的字符串描述符的索引。
     */
    uint8_t iInterface;
} __attribute__((packed)) UsbInterfaceDescriptor;

/**
 * @brief 标准端点描述符，对应USB协议中Standard Endpoint Descriptor。
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbEndpointDescriptor {
    /**
     * 该描述符的大小，单位为字节。
     */
    uint8_t bLength;
    /**
     * 描述符类型。
     */
    uint8_t bDescriptorType;
    /**
     * 端点地址，包含端点编号以及端点方向。
     */
    uint8_t bEndpointAddress;
    /**
     * 端点属性，包括传输类型、同步类型、使用类型。
     */
    uint8_t bmAttributes;
    /**
     * 该端点所能承载的最大包的大小。
     */
    uint16_t wMaxPacketSize;
    /**
     * 数据传输轮询端点的时间间隔。
     */
    uint8_t bInterval;
    /**
     * 用于音频类设备，同步反馈的速率。
     */
    uint8_t bRefresh;
    /**
     * 用于音频类设备，同步端点的地址。
     */
    uint8_t bSynchAddress;
} __attribute__((packed)) UsbEndpointDescriptor;

/**
 * @brief 端点描述符。
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbDdkEndpointDescriptor {
    /**
     * 标准端点描述符。
     */
    struct UsbEndpointDescriptor endpointDescriptor;
    /**
     * 未做解析的描述符，包含特定于类或供应商的描述符。
     */
    const uint8_t *extra;
    /**
     * 未做解析的描述符长度。
     */
    uint32_t extraLength;
} UsbDdkEndpointDescriptor;

/**
 * @brief 接口描述符。
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbDdkInterfaceDescriptor {
    /**
     * 标准接口描述符。
     */
    struct UsbInterfaceDescriptor interfaceDescriptor;
    /**
     * 该接口所包含的端点描述符。
     */
    struct UsbDdkEndpointDescriptor *endPoint;
    /**
     * 未做解析的描述符，包含特定于类或供应商的描述符。
     */
    const uint8_t *extra;
    /**
     * 未做解析的描述符长度。
     */
    uint32_t extraLength;
} UsbDdkInterfaceDescriptor;

/**
 * @brief USB接口，是特定接口下备用设置的集合。
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbDdkInterface {
    /**
     * 接口的备用设置数量。
     */
    uint8_t numAltsetting;
    /**
     * 接口的备用设置。
     */
    struct UsbDdkInterfaceDescriptor *altsetting;
} UsbDdkInterface;

/**
 * @brief 配置描述符。
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbDdkConfigDescriptor {
    /**
     * 标准配置描述符。
     */
    struct UsbConfigDescriptor configDescriptor;
    /**
     * 该配置所包含的接口。
     */
    struct UsbDdkInterface *interface;
    /**
     * 未做解析的描述符，包含特定于类或供应商的描述符。
     */
    const uint8_t *extra;
    /**
     * 未做解析的描述符长度。
     */
    uint32_t extraLength;
} UsbDdkConfigDescriptor;

/**
 * @brief 请求管道。
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbRequestPipe {
    /**
     * 接口操作句柄。
     */
    uint64_t interfaceHandle;
    /**
     * 超时时间，单位是毫秒。
     */
    uint32_t timeout;
    /**
     * 要通信的端点的地址。
     */
    uint8_t endpoint;
} __attribute__((aligned(8))) UsbRequestPipe;

/**
 * @brief 设备内存映射，通过{@link OH_Usb_CreateDeviceMemMap}创建设备内存映射，使用内存映射后的缓冲区，可提升数据传输性能。
 *
 * @since 10
 * @version 1.0
 */
typedef struct UsbDeviceMemMap {
    /**
     * 映射后的缓冲区地址。
     */
    uint8_t * const address;
    /**
     * 缓冲区大小。
     */
    const size_t size;
    /**
     * 所使用的缓冲区的偏移量，默认为0，表示没有偏移，从映射后的缓冲区地址address开始。
     */
    uint32_t offset;
    /**
     * 所使用的缓冲区的长度，默认等于缓冲区大小 size，表示使用全部的缓冲区。
     */
    uint32_t bufferLength;
    /**
     * 实际传输的数据的长度。
     */
    uint32_t transferedLength;
} UsbDeviceMemMap;

/**
 * @brief USB DDK 错误码定义。
 *
 * @since 10
 * @version 1.0
 */
typedef enum {
    /**
     * 操作成功。
     */
    USB_DDK_SUCCESS = 0,
    /**
     * 操作失败。
     * @deprecated since 16
     */
    USB_DDK_FAILED = -1,
    /**
     * 没有权限。
     * @since 14
     */
    USB_DDK_NO_PERM = 201,
    /**
     * 非法参数，在API version 16之前值为-2。
     */
    USB_DDK_INVALID_PARAMETER = 401,
    /**
     * 内存相关的错误，包括：内存不足、内存数据拷贝失败、内存申请失败等，在API version 16之前值为-3。
     */
    USB_DDK_MEMORY_ERROR = 27400001,
    /**
     * 空指针异常。
     * @deprecated since 16
     */
    USB_DDK_NULL_PTR = -5,
    /**
     * 设备忙。
     * @deprecated since 16
     */
    USB_DDK_DEVICE_BUSY = -6,
    /**
     * 非法操作，在API version 16之前值为-4。
     */
    USB_DDK_INVALID_OPERATION = 27400002,
    /**
     * 设备I/O操作失败。
     * @since 14
     */
    USB_DDK_IO_FAILED = 27400003,
    /**
     * 传输超时，在API version 16之前值为-7。
     */
    USB_DDK_TIMEOUT = 27400004,
} UsbDdkErrCode;

/**
 * @brief 设备ID清单，用于存放{@link OH_Usb_GetDevices}接口获取到的设备ID列表和设备数量。
 *
 * @since 18
 */
typedef struct Usb_DeviceArray {
    /**
     * 开发者申请好的设备ID数组首地址，申请的数组大小建议一般不超过128，以避免过度占用内存。
     */
    uint64_t* deviceIds;
    /**
     * 实际返回的设备数量，根据数量遍历deviceIds获得设备ID。当该值为0时，表示不存在USB设备。
     */
    uint32_t num;
} Usb_DeviceArray;

/**
 * @brief 非根集线器列表，用于存放{@link OH_Usb_GetNonRootHubs}接口获取到的非根集线器设备ID列表和数量。
 *
 * @since 26.0.0
 */
typedef struct Usb_NonRootHubArray {

    /**
     * 开发者申请好的非根集线器设备ID数组首地址，申请的数组大小建议一般不超过128，以避免过度占用内存。非根USB集线器设备ID由总线号左移32位加上设备地址构造而成。
     * @since 26.0.0
     */
    uint64_t* nonRootHubIds;

    /**
     * 实际返回的非根集线器数量，根据数量遍历nonRootHubIds获得非根集线器设备ID。当该值为0时，表示不存在非根集线器设备。
     * @since 26.0.0
     */
    uint32_t num;
} Usb_NonRootHubArray;
#ifdef __cplusplus
}
/** @} */
#endif /* __cplusplus */
#endif // USB_DDK_TYPES_H