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
 * @brief Provides USB Serial Driver Development Kit (USB Serial DDK) APIs, including the enum types and data structs
 * used by USB Serial DDK APIs. Serial port communication is often used in industrial scenarios and some legacy devices,
 * such as card issuers and ID card readers. By using the USB Serial DDK, you can develop USB serial port peripherals
 * extension drivers.
 *
 * @since 18
 */

/**
 * @file usb_serial_api.h
 *
 * @brief Declares the USB Serial DDK APIs used by the host to access the serial port device. It provides the
 * capabilities of reading data from and writing data to serial ports and configuring parameters. This API is
 * applicable to scenarios where serial port devices need to be accessed through the USB port, such as industrial
 * control and embedded device communication.
 *
 * @include <usb_serial/usb_serial_api.h>
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
 * @brief Initializes the USB Serial DDK. This API must be called before any other USB Serial DDK APIs. It establishes
 * communication with the DDK service and loads necessary driver resources. After using the DDK, call
 * {@link OH_UsbSerial_Release} to release it to avoid resource leaks.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: The DDK initialization fails.
 * @since 18
 */
int32_t OH_UsbSerial_Init(void);

/**
 * @brief Releases the USB Serial DDK. This function must be used together with {@link OH_UsbSerial_Init}. After the
 * DDK is released, other USB Serial DDK methods cannot be called.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: DDK is not initialized or has been released. Call
 *     {@link OH_UsbSerial_Init} to initialize the DDK first.
 *     <br>{@link USB_SERIAL_DDK_SERVICE_ERROR}: DDK service fails to be executed. Check the device status.
 * @since 18
 */
int32_t OH_UsbSerial_Release(void);

/**
 * @brief Opens the USB serial port device based on the specified **deviceId** and **interfaceIndex**. This API
 * establishes a connection with the specified USB serial port device and returns the device handle for follow-up
 * procedures. After using the device, call {@link OH_UsbSerial_Close} to close the device. Otherwise, device resources
 * may not be correctly released.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param deviceId ID of the device to be operated, which can be obtained by calling {@link OH_Usb_GetDevices}.
 * @param interfaceIndex Interface index, which corresponds to **bInterfaceNumber** in the USB protocol.
 * @param dev Device handle, which is an output parameter used to return the handle of the opened USB serial port
 *     device. After the handle is used, call {@link OH_UsbSerial_Close} to release it.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. The possible cause is that
 *     **dev** or ***dev** is null. Check the parameter validity.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized. Call {@link OH_UsbSerial_Init} to initialize
 *     the DDK first.
 *     <br>{@link USB_SERIAL_DDK_SERVICE_ERROR}: DDK service fails to be executed. Check the parameters and device
 *     status.
 *     <br>{@link USB_SERIAL_DDK_MEMORY_ERROR}: The memory is insufficient.
 *     <br>{@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs. Check the device specifications and parameters.
 *     <br>{@link USB_SERIAL_DDK_DEVICE_NOT_FOUND}: The device or interface is not found.
 * @since 18
 */
int32_t OH_UsbSerial_Open(uint64_t deviceId, uint8_t interfaceIndex, UsbSerial_Device **dev);

/**
 * @brief Closes the USB serial port device. This API releases the resources occupied by the device and must be used
 * together with {@link OH_UsbSerial_Open}.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle, which is an input and output parameter. After the device is closed, this pointer is set to
 *     null.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. The possible cause is that
 *     **dev** or ***dev** is null. Check the parameter validity.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized. Call {@link OH_UsbSerial_Init} to initialize
 *     the DDK first.
 *     <br>{@link USB_SERIAL_DDK_SERVICE_ERROR}: DDK service fails to be executed. Check the parameters and device
 *     status.
 *     <br>{@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs. Check the device specifications and parameters.
 *     <br>{@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid. Ensure that the device is properly
 *     started.
 * @since 18
 */
int32_t OH_UsbSerial_Close(UsbSerial_Device **dev);

/**
 * @brief Reads data from the USB serial port device to the buffer.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle, which must be opened and obtained by calling {@link OH_UsbSerial_Open}.
 * @param buff Buffer for reading data from the USB serial port device. The buffer must be allocated by the caller and
 *     its capacity must be greater than or equal to **bufferSize**.
 * @param bufferSize Buffer size.
 * @param bytesRead Number of bytes that are actually read. If the block mode is set, the number of bytes that are
 *     actually read is returned only when it is equal to the value of **bufferSize**. If a timeout interval is set,
 *     the return value may be less than **bufferSize**.
 *     <br>For details, see {@link OH_UsbSerial_SetTimeout}.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible causes: 1. **dev** is a
 *     null pointer. 2. **buff** is a null pointer. 3. **bufferSize** is **0**. 4. **bytesRead** is a null pointer.
 *     Check the parameter validity.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized. Call {@link OH_UsbSerial_Init} to initialize
 *     the DDK first.
 *     <br>{@link USB_SERIAL_DDK_SERVICE_ERROR}: DDK service fails to be executed. Check the parameters and device
 *     status.
 *     <br>{@link USB_SERIAL_DDK_MEMORY_ERROR}: The buffer address is invalid.
 *     <br>{@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs. Check the device specifications and parameters.
 *     <br>{@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid. Ensure that the device is properly
 *     started.
 * @since 18
 */
int32_t OH_UsbSerial_Read(UsbSerial_Device *dev, uint8_t *buff, uint32_t bufferSize, uint32_t *bytesRead);

/**
 * @brief Writes the data in the buffer to the USB serial port device.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle, which must be opened and obtained by calling {@link OH_UsbSerial_Open}.
 * @param buff Buffer whose data is written to the USB serial port device. The buffer must be allocated by the caller
 *     and its size must be greater than or equal to **bufferSize**.
 * @param bufferSize Buffer size.
 * @param bytesWritten Number of bytes that are actually written. This parameter is valid only when the API returns a
 *     success message, and the value may be less than **bufferSize**.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible causes: 1. **dev** is a
 *     null pointer. 2. **buff** is a null pointer. 3. **bufferSize** is **0**. 4. **bytesWritten** is a null pointer.
 *     Check the parameter validity.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized. Call {@link OH_UsbSerial_Init} to initialize
 *     the DDK first.
 *     <br>{@link USB_SERIAL_DDK_SERVICE_ERROR}: DDK service fails to be executed. Check the parameters and device
 *     status.
 *     <br>{@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs. Check the device specifications and parameters.
 *     <br>{@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid. Ensure that the device is properly
 *     started.
 * @since 18
 */
int32_t OH_UsbSerial_Write(UsbSerial_Device *dev, uint8_t *buff, uint32_t bufferSize, uint32_t *bytesWritten);

/**
 * @brief Sets the baud rate for a USB serial port device. If the parameters of the USB serial port device are set to
 * the default values (the data bit is **8**, the stop bit is **1**, and parity is disabled for data transfer), you
 * only need to call this API to set the baud rate.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle, which must be opened and obtained by calling {@link OH_UsbSerial_Open}.
 * @param baudRate Baud rate of the USB serial port device, in bit/s.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible cause: The input
 *     **dev** is a null pointer. Check the parameter validity.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized. Call {@link OH_UsbSerial_Init} to initialize
 *     the DDK first.
 *     <br>{@link USB_SERIAL_DDK_SERVICE_ERROR}: DDK service fails to be executed. Check the parameters and device
 *     status.
 *     <br>{@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs. Check the device specifications and parameters.
 *     <br>{@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid. Ensure that the device is properly
 *     started.
 * @since 18
 */
int32_t OH_UsbSerial_SetBaudRate(UsbSerial_Device *dev, uint32_t baudRate);

/**
 * @brief Sets the parameters of the USB serial port device. If the parameters of the USB serial port device are not
 * set to the default values (the data bit is **8**, the stop bit is **1**, and parity is disabled for data transfer),
 * you only need to call this API to set the related parameters.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle, which must be opened and obtained by calling {@link OH_UsbSerial_Open}.
 * @param params USB serial port device parameters. For details, see {@link UsbSerial_Params}.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible causes: 1. **dev** is a
 *     null pointer.
 *     <br>2. **params** is a null pointer. Check the parameter validity.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized. Call {@link OH_UsbSerial_Init} to initialize
 *     the DDK first.
 *     <br>{@link USB_SERIAL_DDK_SERVICE_ERROR}: DDK service fails to be executed. Check the parameters and device
 *     status.
 *     <br>{@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs. Check the device specifications and parameters.
 *     <br>{@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid. Ensure that the device is properly
 *     started.
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
 * @param dev Device handle, which must be opened and obtained by calling {@link OH_UsbSerial_Open}.
 * @param timeout Timeout interval for reading data from a USB serial port device. If the value range is (0, 25500] in
 *     milliseconds, the value is rounded off to the nearest 100 milliseconds and used as the actual timeout interval.
 *     For example, if the input value is **12321**, the effective timeout interval is 12300 milliseconds. If the value
 *     is **0**, data is returned immediately without waiting. If the value is **-1**, data is read in blocking mode.
 *     That is, data is returned only after the data of the specified length is read. For details, see
 *     {@link OH_UsbSerial_Read}. The value **0** is recommended in polling scenarios, the value range (0, 25500] is
 *     recommended when timeout control is required, and the value **-1** is recommended when all integer data must be
 *     read.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible causes: 1. **dev** is a
 *     null pointer.
 *     <br>2. **timeout** is less than **-1** or greater than **25500**. Check the parameter validity and timeout
 *     interval.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized. Call {@link OH_UsbSerial_Init} to initialize
 *     the DDK first.
 *     <br>{@link USB_SERIAL_DDK_SERVICE_ERROR}: DDK service fails to be executed. Check the parameters and device
 *     status.
 *     <br>{@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs. Check the device specifications and parameters.
 *     <br>{@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid. Ensure that the device is properly
 *     started.
 * @since 18
 */
int32_t OH_UsbSerial_SetTimeout(UsbSerial_Device *dev, int timeout);

/**
 * @brief Sets flow control parameters. Flow control is used to manage the data transfer rate during communication with
 * the USB serial port device to ensure that the sender does not send data that exceeds the processing capability of
 * the receiver. If flow control is required, call this API to set flow control parameters. If this API is not called,
 * flow control is disabled by default.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle, which must be opened and obtained by calling {@link OH_UsbSerial_Open}.
 * @param flowControl Flow control mode. For details, see {@link UsbSerial_FlowControl}.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible cause: The input
 *     **dev** is a null pointer. Check the parameter validity.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized. Call {@link OH_UsbSerial_Init} to initialize
 *     the DDK first.
 *     <br>{@link USB_SERIAL_DDK_SERVICE_ERROR}: DDK service fails to be executed. Check the parameters and device
 *     status.
 *     <br>{@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs. Check the device specifications and parameters.
 *     <br>{@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid. Ensure that the device is properly
 *     started.
 * @since 18
 */
int32_t OH_UsbSerial_SetFlowControl(UsbSerial_Device *dev, UsbSerial_FlowControl flowControl);

/**
 * @brief Flushes the input and output buffers. The system waits until all data in the output buffer is sent. If a
 * large amount of data is to be transmitted to the USB serial port device, the data may be buffered in the kernel for
 * transmission. If the app closes the device or exits before all data is sent out, some data may be lost. You can call
 * this API to ensure that all data is sent before subsequent operations are performed.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle, which must be opened and obtained by calling {@link OH_UsbSerial_Open}.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible cause: The input
 *     **dev** is a null pointer. Check the parameter validity.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized. Call {@link OH_UsbSerial_Init} to initialize
 *     the DDK first.
 *     <br>{@link USB_SERIAL_DDK_SERVICE_ERROR}: DDK service fails to be executed. Check the parameters and device
 *     status.
 *     <br>{@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs. Check the device specifications and parameters.
 *     <br>{@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid. Ensure that the device is properly
 *     started.
 * @since 18
 */
int32_t OH_UsbSerial_Flush(UsbSerial_Device *dev);

/**
 * @brief Flushes the input buffer. The data in the buffer is flushed immediately. During the communication with the
 * USB serial port device, especially in the debugging phase, disordered data packets or other exceptions may occur. In
 * this case, you can call this API to clear errors at the receive end to restore the communication. This API does not
 * affect the data to be sent in the output buffer.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle, which must be opened and obtained by calling {@link OH_UsbSerial_Open}.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible cause: The input
 *     **dev** is a null pointer. Check the parameter validity.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized. Call {@link OH_UsbSerial_Init} to initialize
 *     the DDK first.
 *     <br>{@link USB_SERIAL_DDK_SERVICE_ERROR}: DDK service fails to be executed. Check the parameters and device
 *     status.
 *     <br>{@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs. Check the device specifications and parameters.
 *     <br>{@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid. Ensure that the device is properly
 *     started.
 * @since 18
 */
int32_t OH_UsbSerial_FlushInput(UsbSerial_Device *dev);

/**
 * @brief Flushes the output buffer. The data in the buffer is flushed immediately. During the communication with the
 * USB serial port device, especially in the debugging phase, disordered data packets or other exceptions may occur.
 * You can call this API to clear errors at the transmit end to restore the communication. This API does not affect the
 * received data in the input buffer.
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev Device handle, which must be opened and obtained by calling {@link OH_UsbSerial_Open}.
 * @return {@link USB_SERIAL_DDK_SUCCESS}: The operation is successful.
 *     <br>{@link USB_SERIAL_DDK_NO_PERM}: The permission verification fails. Check whether you have obtained the
 *     **ohos.permission.ACCESS_DDK_USB_SERIAL** permission.
 *     <br>{@link USB_SERIAL_DDK_INVALID_PARAMETER}: The parameter verification fails. Possible cause: The input
 *     **dev** is a null pointer. Check the parameter validity.
 *     <br>{@link USB_SERIAL_DDK_INIT_ERROR}: The DDK is not initialized. Call {@link OH_UsbSerial_Init} to initialize
 *     the DDK first.
 *     <br>{@link USB_SERIAL_DDK_SERVICE_ERROR}: DDK service fails to be executed. Check the parameters and device
 *     status.
 *     <br>{@link USB_SERIAL_DDK_IO_ERROR}: An I/O exception occurs. Check the device specifications and parameters.
 *     <br>{@link USB_SERIAL_DDK_INVALID_OPERATION}: The operation is invalid. Ensure that the device is properly
 *     started.
 * @since 18
 */
int32_t OH_UsbSerial_FlushOutput(UsbSerial_Device *dev);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // DDK_USB_SERIAL_API_H
/** @} */