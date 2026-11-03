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
 * @addtogroup USBSerialDDK
 * @{
 *
 * @brief Provides USB SERIAL DDK types and declares the macros, enumerated variables, and
 * data structures required by the USB SERIAL DDK APIs.
 *
 * @since 18
 */

/**
 * @file usb_serial_types.h
 *
 * @brief Provides the enumeration types and structures used in USB Serial DDK APIs. It is used for USB serial port
 * driver development, simplifying operations such as parameter configuration, return code processing, and flow control
 * for serial port devices, and improving driver development efficiency.
 *
 * @include <usb_serial/usb_serial_types.h>
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
 * @brief Defines the data structures for the USB serial port device (opaque), which is used to indicate the USB serial
 * port device. You can obtain this structure instance by calling the {@link OH_UsbSerial_Open} API.
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
     * No access permission. Ensure that the required permissions are declared in the **module.json5** file of the app.
     */
    USB_SERIAL_DDK_NO_PERM = 201,
    /**
     * Invalid parameter. Ensure that the input parameter value is within the valid range. For details, see the
     * parameter description of the related API.
     */
    USB_SERIAL_DDK_INVALID_PARAMETER = 401,
    /**
     * Operation success.
     */
    USB_SERIAL_DDK_SUCCESS = 31600000,
    /**
     * Invalid operation. For example, an invalid device handle is used. Ensure that the device is properly opened.
     */
    USB_SERIAL_DDK_INVALID_OPERATION = 31600001,
    /**
     * Initialization error. Initialize the DDK service first.
     */
    USB_SERIAL_DDK_INIT_ERROR = 31600002,
    /**
     * Service error. Check whether the DDK service status and API calling logic are normal.
     */
    USB_SERIAL_DDK_SERVICE_ERROR = 31600003,
    /**
     * Memory-related errors, such as insufficient memory, memory data replication failure, or memory request failure.
     * You are advised to optimize memory parameters and release unnecessary resources in a timely manner.
     */
    USB_SERIAL_DDK_MEMORY_ERROR = 31600004,
    /**
     * I/O error. Check whether the device connection is normal, whether the transmission cable is intact, and whether
     * the device is working properly.
     */
    USB_SERIAL_DDK_IO_ERROR = 31600005,
    /**
     * Device not found. Check the parameters and device connection status.
     */
    USB_SERIAL_DDK_DEVICE_NOT_FOUND = 31600006
} UsbSerial_DdkRetCode;

/**
 * @brief Defines the USB serial port parameters for the USB Serial DDK, which are used for configuring the
 * communication parameters of the USB-to-serial device. The parameter configuration must be consistent with that of
 * the target communication device. Otherwise, the communication may fail. It is commonly used in scenarios where
 * communication with devices through the USB serial port is required, such as industrial control devices, debugging
 * tools, and sensor data collection.
 *
 * @since 18
 */
typedef struct UsbSerial_Params {
    /**
     * Baud rate, unit: baud.
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
     * Parity setting (0: no parity; 1: odd parity; 2: even parity).
     */
    uint8_t parity;
} __attribute__((aligned(8))) UsbSerial_Params;

/**
 * @brief Defines the flow control mode for the USB Serial DDK. When using the USB serial port for data transfer, you
 * need to select a proper flow control mode based on the communication scenario. For example, in high-speed and large-
 * volume data transmission scenarios, hardware flow control is recommended to avoid data loss. In low-speed or
 * scenarios that do not require high real-time performance, software flow control can be used. In short-range and
 * reliable point-to-point communication scenarios, no flow control can be selected.
 *
 * @since 18
 */
typedef enum {
    /**
     * No flow control. This mode is applicable to low-speed data transfer or scenarios where flow control is not
     * required. However, data loss may occur.
     */
    USB_SERIAL_NO_FLOW_CONTROL = 0,
    /**
     * Software flow control. XON/XOFF control is applicable to devices that do not support hardware flow control.
     */
    USB_SERIAL_SOFTWARE_FLOW_CONTROL = 1,
    /**
     * Hardware flow control. RTS/CTS signal lines are used, which are applicable to high-speed data transfer and
     * provide high reliability.
     */
    USB_SERIAL_HARDWARE_FLOW_CONTROL = 2
} UsbSerial_FlowControl;

/**
 * @brief Defines the enums of the parity parameter used by the USB Serial DDK. When configuring the USB serial port
 * communication parameters, you need to select a proper parity mode based on the reliability requirements of data
 * transmission. For example, in industrial control scenarios that require high data integrity, it is recommended that
 * odd or even parity be used to detect transfer errors. In environments with high noise interference, parity can help
 * recognize error data. In short-range and reliable communication scenarios, no parity can be selected to improve
 * transfer efficiency.
 *
 * @since 18
 */
typedef enum {
    /**
     * No parity. In short-range and reliable communication scenarios, no parity can be selected to improve transfer
     * efficiency.
     */
    USB_SERIAL_PARITY_NONE = 0,
    /**
     * Odd parity. This mode is applicable to scenarios that require high data integrity.
     */
    USB_SERIAL_PARITY_ODD = 1,
    /**
     * Even parity. This mode is applicable to scenarios that require high data integrity.
     */
    USB_SERIAL_PARITY_EVEN = 2
} UsbSerial_Parity;

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // DDK_USB_SERIAL_TYPES_H
/** @} */