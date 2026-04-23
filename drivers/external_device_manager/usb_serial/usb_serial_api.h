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
 * @file usb_serial_api.h
 *
 * @brief Declares the USB Serial DDK APIs used by the host to access the serial port device through the USB port.
 * 
 * @kit DriverDevelopmentKit
 * @library libusb_serial_ndk.z.so
 * @syscap SystemCapability.Driver.UsbSerial.Extension
 * @since 18
 */

#ifndef DDK_USB_SERIAL_API_H
#define DDK_USB_SERIAL_API_H

#include <stdint.h>
#include "usb_serial_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the USB Serial DDK.
 * 
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK initialization fails.
 * @since 18
 */
int32_t OH_UsbSerial_Init(void);

/**
 * @brief Releases the USB Serial DDK.
 * 
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR}: The DDK service communication fails.
 * @since 18
 */
int32_t OH_UsbSerial_Release(void);

/**
 * @brief Opens the USB serial port device based on the specified **deviceId** and **interfaceIndex**.
 * 
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param deviceId Device ID.
 * @param interfaceIndex Interface index, which corresponds to {@link bInterfaceNumber} in the USB protocol.
 * @param dev Device handle.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. The possible cause is that **dev**
 *     or ***dev** is null.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR}: The DDK service communication fails.
 *     {@link USB_SERIAL_DDK_MEMORY_ERROR}: The memory is insufficient.
 *     {@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs.
 *     {@link USB_SERIAL_DDK_DEVICE_NOT_FOUND}: The device or interface is not found.
 * @since 18
 */
int32_t OH_UsbSerial_Open(uint64_t deviceId, uint8_t interfaceIndex, UsbSerial_Device **dev);

/**
 * @brief Closes the USB serial port device.
 * 
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. The possible cause is that **dev**
 *     or ***dev** is null.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR}: The DDK service communication fails.
 *     {@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs.
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid.
 * @since 18
 */
int32_t OH_UsbSerial_Close(UsbSerial_Device **dev);

/**
 * @brief Reads data from the USB serial port device to the buffer.
 * 
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle.
 * @param buff Buffer for storing the data read from the USB serial port device.
 * @param bufferSize Buffer size.
 * @param bytesRead Number of bytes that are actually read. If the block mode is set, the number of bytes that are
 *     actually read is returned only when it is equal to the value of **bufferSize**.
 *     For details, see {@link OH_UsbSerial_SetTimeout}.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible causes: 1. **dev** is a
 *     null pointer.
 *     2. **buff** is a null pointer. 3. **bufferSize** is **0**. 4. **bytesRead** is a null pointer.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR}: The DDK service communication fails.
 *     {@link USB_SERIAL_DDK_MEMORY_ERROR}: The buffer address is invalid.
 *     {@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs.
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid.
 * @since 18
 */
int32_t OH_UsbSerial_Read(UsbSerial_Device *dev, uint8_t *buff, uint32_t bufferSize, uint32_t *bytesRead);

/**
 * @brief Writes the data in the buffer to the USB serial port device.
 * 
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle.
 * @param buff Buffer to which the data of the USB serial port device is written.
 * @param bufferSize Buffer size.
 * @param bytesWritten Number of bytes that are actually written.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible causes: 1. **dev** is a
 *     null pointer. 2. **buff** is a null pointer. 3. **bufferSize** is **0**. 4. **bytesWritten** is a null pointer.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR}: The DDK service communication fails.
 *     {@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs.
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid.
 * @since 18
 */
int32_t OH_UsbSerial_Write(UsbSerial_Device *dev, uint8_t *buff, uint32_t bufferSize, uint32_t *bytesWritten);

/**
 * @brief Sets the baud rate for a USB serial port device. If the parameters of the USB serial port device are set to
 * the default values (the data bit is **8**, the stop bit is **1**, and parity is disabled for data transfer), you
 * only need to call this API to set the baud rate.
 * 
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle.
 * @param baudRate Baud rate of the USB serial port device.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible cause: The input **dev** is
 *     a null pointer.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR}: The DDK service communication fails.
 *     {@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs.
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid.
 * @since 18
 */
int32_t OH_UsbSerial_SetBaudRate(UsbSerial_Device *dev, uint32_t baudRate);

/**
 * @brief Sets the parameters of the USB serial port device. If the parameters of the USB serial port device are not
 * set to the default values (the data bit is **8**, the stop bit is **1**, and parity is disabled for data transfer),
 * you only need to call this API to set the related parameters.
 * 
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle.
 * @param params USB serial port device parameters. For details, see {@link UsbSerial_Params}.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible causes: 1. **dev** is a
 *     null pointer.
 *     2. **params** is a null pointer.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR}: The DDK service communication fails.
 *     {@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs.
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid.
 * @since 18
 */
int32_t OH_UsbSerial_SetParams(UsbSerial_Device *dev, UsbSerial_Params *params);

/**
 * @brief Sets the timeout interval (ms) for reading data reported by a USB serial port device. If this function is not
 * called, the timeout value is **0** by default, indicating that data is returned immediately regardless of whether
 * data is read. If you need to wait for a certain period of time or data must be read, call this API to set the
 * timeout interval.
 * 
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle.
 * @param timeout Timeout interval for reading data from a USB serial port device, in milliseconds. The value range is
 *     - (0, 25500]. The value is rounded off to the nearest 100 milliseconds as the actual timeout interval. For
 *     example, if the value is set to **12321**, the effective timeout interval is **12300**. - **0**: Data is
 *     returned immediately. - **-1**: Data is read in block mode. That is, data is returned only after data of the
 *     specified length is read. For details, see {@link OH_UsbSerial_Read}.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible causes: 1. **dev** is a
 *     null pointer. 2.timeout < -1 or timeout > 25500.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR}: The DDK service communication fails.
 *     {@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs.
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid.
 * @since 18
 */
int32_t OH_UsbSerial_SetTimeout(UsbSerial_Device *dev, int timeout);

/**
 * @brief Sets flow control parameters. Flow control is used to manage the data transfer rate during communication with
 * the USB serial port device to ensure that the sender does not send data that exceeds the processing capability of
 * the receiver.
 * If flow control is required, call this API to set flow control parameters. If this API is not called, flow control
 * is not performed by default.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle.
 * @param flowControl Flow control mode. For details, see {@link UsbSerial_FlowControl}.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible cause: The input **dev** is
 *     a null pointer.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR}: The DDK service communication fails.
 *     {@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs.
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid.
 * @since 18
 */
int32_t OH_UsbSerial_SetFlowControl(UsbSerial_Device *dev, UsbSerial_FlowControl flowControl);

/**
 * @brief Flushes the input and output buffers after the write operation is complete. If a large amount of data is to
 * be transmitted to the USB serial port device, the data may be buffered in the kernel for transmission. If the
 * application closes the file descriptor or exits before the data is completely sent out, some data may be lost.
 * If the data is not sent out, some data may be lost. You can call this API to ensure that all data is sent before
 * subsequent operations are performed.
 * 
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible cause: The input **dev** is
 *     a null pointer.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR}: The DDK service communication fails.
 *     {@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs.
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid.
 * @since 18
 */
int32_t OH_UsbSerial_Flush(UsbSerial_Device *dev);

/**
 * @brief Flushes the input buffer. The data in the buffer is cleared immediately. During the communication with the
 * USB serial port device, especially in the debugging phase, disordered data packets or other exceptions may occur.
 * You can call this API to clear these exceptions to restore the communication.
 * 
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible cause: The input **dev** is
 *     a null pointer.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR}: The DDK service communication fails.
 *     {@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs.
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid.
 * @since 18
 */
int32_t OH_UsbSerial_FlushInput(UsbSerial_Device *dev);

/**
 * @brief Flushes the output buffer. The data in the buffer is cleared immediately. During the communication with the
 * USB serial port device, especially in the debugging phase, disordered data packets or other exceptions may occur.
 * You can call this API to clear these exceptions to restore the communication.
 * 
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     {@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails.
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible cause: The input **dev** is
 *     a null pointer.
 *     {@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized.
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR}: The DDK service communication fails.
 *     {@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs.
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid.
 * @since 18
 */
int32_t OH_UsbSerial_FlushOutput(UsbSerial_Device *dev);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // DDK_USB_SERIAL_API_H
/** @} */
