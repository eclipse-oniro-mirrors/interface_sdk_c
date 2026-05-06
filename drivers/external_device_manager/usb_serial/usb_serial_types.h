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
 * @brief Provides the enum variables, structures, and macros used in USB Serial DDK APIs.
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
 * @brief Defines the data structures (opaque) for the USB serial port device.
 *
 * @since 18
 */
typedef struct UsbSerial_Device UsbSerial_Device;

/**
 * @brief Defines the return codes used by the USB Serial DDK.
 *
 * @since 18
 */
typedef enum {
    /**
     * No access permission.
     */
    USB_SERIAL_DDK_NO_PERM = 201,
    /**
     * Invalid parameter.
     */
    USB_SERIAL_DDK_INVALID_PARAMETER = 401,
    /**
     * Operation success.
     */
    USB_SERIAL_DDK_SUCCESS = 31600000,
    /**
     * Invalid operation.
     */
    USB_SERIAL_DDK_INVALID_OPERATION = 31600001,
    /**
     * Initialization error.
     */
    USB_SERIAL_DDK_INIT_ERROR = 31600002,
    /**
     * Service error.
     */
    USB_SERIAL_DDK_SERVICE_ERROR = 31600003,
    /**
     * Memory-related errors, such as insufficient memory, memory data replication failure,
     * or memory application fault.
     */
    USB_SERIAL_DDK_MEMORY_ERROR = 31600004,
    /**
     * I/O error.
     */
    USB_SERIAL_DDK_IO_ERROR = 31600005,
    /**
     * Device not found.
     */
    USB_SERIAL_DDK_DEVICE_NOT_FOUND = 31600006,
} UsbSerial_DdkRetCode;

/**
 * @brief Defines the USB serial port parameters for the USB Serial DDK.
 *
 * @since 18
 */
typedef struct UsbSerial_Params {
    /**
     * Baud rate, in bauds.
     */
    uint32_t baudRate;
    /**
     * Number of data bits.
     */
    uint8_t nDataBits;
    /**
     * Number of stop bits.
     */
    uint8_t nStopBits;
    /**
     * Parity parameter setting. **0**: no parity; **1**: odd parity; **2**: even parity.
     */
    uint8_t parity;
} __attribute__((aligned(8))) UsbSerial_Params;

/**
 * @brief Defines the flow control mode for the USB Serial DDK.
 *
 * @since 18
 */
typedef enum {
    /**
     * No flow control.
     */
    USB_SERIAL_NO_FLOW_CONTROL = 0,
    /**
     * Software flow control.
     */
    USB_SERIAL_SOFTWARE_FLOW_CONTROL = 1,
    /**
     * Hardware flow control.
     */
    USB_SERIAL_HARDWARE_FLOW_CONTROL = 2,
} UsbSerial_FlowControl;

/**
 * @brief Defines the enums of the parity parameter used by the USB Serial DDK.
 *
 * @since 18
 */
typedef enum {
    /**
     * No parity.
     */
    USB_SERIAL_PARITY_NONE = 0,
    /**
     * Odd parity.
     */
    USB_SERIAL_PARITY_ODD = 1,
    /**
     * Even parity.
     */
    USB_SERIAL_PARITY_EVEN = 2,
} UsbSerial_Parity;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // DDK_USB_SERIAL_TYPES_H
/** @} */
