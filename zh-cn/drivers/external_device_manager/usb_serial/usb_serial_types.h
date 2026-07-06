/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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
 * @addtogroup USBSerialDDK
 * @{
 *
 * @brief Provides USB SERIAL DDK types and declares the macros, enumerated variables, and\n
 * data structures required by the USB SERIAL DDK APIs.
 *
 * @since 18
 */

/**
 * @file usb_serial_types.h
 *
 * @brief 提供USB Serial DDK中的枚举变量、结构体定义与宏定义。
 *
 * @kit DriverDevelopmentKit
 * @library libusb_serial_ndk.z.so
 * @syscap SystemCapability.Driver.UsbSerial.Extension
 * @since 18
 */

#ifndef DDK_USB_SERIAL_TYPES_H
#define DDK_USB_SERIAL_TYPES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief USB串口设备数据结构（不透明）。
 *
 * @since 18
 */
typedef struct UsbSerial_Device UsbSerial_Device;

/**
 * @brief 定义USB Serial DDK使用的返回码。
 *
 * @since 18
 */
typedef enum {
    /**
     * 权限被拒绝。
     */
    USB_SERIAL_DDK_NO_PERM = 201,
    /**
     * 无效参数。
     */
    USB_SERIAL_DDK_INVALID_PARAMETER = 401,
    /**
     * 操作成功。
     */
    USB_SERIAL_DDK_SUCCESS = 31600000,
    /**
     * 无效操作。
     */
    USB_SERIAL_DDK_INVALID_OPERATION = 31600001,
    /**
     * 初始化失败。
     */
    USB_SERIAL_DDK_INIT_ERROR = 31600002,
    /**
     * 服务错误。
     */
    USB_SERIAL_DDK_SERVICE_ERROR = 31600003,
    /**
     * 内存相关错误，例如内存不足、内存数据复制失败或内存应用程序故障。
     */
    USB_SERIAL_DDK_MEMORY_ERROR = 31600004,
    /**
     * I/O 错误。
     */
    USB_SERIAL_DDK_IO_ERROR = 31600005,
    /**
     * 未找到设备。
     */
    USB_SERIAL_DDK_DEVICE_NOT_FOUND = 31600006,
} UsbSerial_DdkRetCode;

/**
 * @brief 定义USB Serial DDK使用的USB串口参数。
 *
 * @since 18
 */
typedef struct UsbSerial_Params {
    /**
     * 波特率，单位为波特。
     */
    uint32_t baudRate;
    /**
     * 数据位比特数。
     */
    uint8_t nDataBits;
    /**
     * 停止位比特数。
     */
    uint8_t nStopBits;
    /**
     * 校验参数设置（0：无校验；1：奇校验；2：偶校验；）。
     */
    uint8_t parity;
} __attribute__((aligned(8))) UsbSerial_Params;

/**
 * @brief 定义USB Serial DDK中的流量控制。
 *
 * @since 18
 */
typedef enum {
    /**
     * 无流量控制。
     */
    USB_SERIAL_NO_FLOW_CONTROL = 0,
    /**
     * 软件流控。
     */
    USB_SERIAL_SOFTWARE_FLOW_CONTROL = 1,
    /**
     * 硬件流控。
     */
    USB_SERIAL_HARDWARE_FLOW_CONTROL = 2,
} UsbSerial_FlowControl;

/**
 * @brief 定义USB Serial DDK使用的校验参数枚举。
 *
 * @since 18
 */
typedef enum {
    /**
     * 无校验。
     */
    USB_SERIAL_PARITY_NONE = 0,
    /**
     * 奇校验。
     */
    USB_SERIAL_PARITY_ODD = 1,
    /**
     * 偶校验。
     */
    USB_SERIAL_PARITY_EVEN = 2,
} UsbSerial_Parity;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // DDK_USB_SERIAL_TYPES_H
/** @} */