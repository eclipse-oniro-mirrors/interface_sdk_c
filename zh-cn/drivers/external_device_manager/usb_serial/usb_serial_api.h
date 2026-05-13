/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @brief 初始化USB Serial DDK。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 初始化DDK失败。
 * @since 18
 */
int32_t OH_UsbSerial_Init(void);

/**
 * @brief 释放USB Serial DDK。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR} DDK服务通信失败。
 * @since 18
 */
int32_t OH_UsbSerial_Release(void);

/**
 * @brief 通过deviceId和interfaceIndex打开USB串口设备。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param deviceId 设备ID，代表要操作的设备。
 * @param interfaceIndex 接口索引，对应USB协议中的{@link bInterfaceNumber}。
 * @param dev 设备句柄。
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER} 参数检查失败。可能原因为：dev为空指针或*dev为空指针。
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR} DDK服务通信失败。
 *     {@link USB_SERIAL_DDK_MEMORY_ERROR} 内存不足。
 *     {@link USB_SERIAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link USB_SERIAL_DDK_DEVICE_NOT_FOUND} 找不到设备或接口。
 * @since 18
 */
int32_t OH_UsbSerial_Open(uint64_t deviceId, uint8_t interfaceIndex, UsbSerial_Device **dev);

/**
 * @brief 关闭USB串口设备。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev 设备句柄。
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER} 参数检查失败。可能原因：dev为空指针或*dev为空指针。
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR} DDK服务通信失败。
 *     {@link USB_SERIAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION} 无效操作。
 * @since 18
 */
int32_t OH_UsbSerial_Close(UsbSerial_Device **dev);

*/
int32_t OH_UsbSerial_Close(UsbSerial_Device **dev);

/**
 * @brief 从USB串口设备读入数据到缓冲区。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev 设备句柄。
 * @param buff 保存从USB串口设备读取数据的缓冲区。
 * @param bufferSize 缓冲区的大小。
 * @param bytesRead 实际读取的字节数，如果设置了阻塞模式，则实际读取到的数据等于bufferSize后才会返回，
 *     详见{@link OH_UsbSerial_SetTimeout}。
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER} 参数检查失败。可能原因：1. dev为空指针;
 *     2. buff为空指针; 3. bufferSize等于0; 4. bytesRead为空指针。
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR} DDK服务通信失败。
 *     {@link USB_SERIAL_DDK_MEMORY_ERROR} buff地址无效。
 *     {@link USB_SERIAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION} 无效操作。
 * @since 18
 */
int32_t OH_UsbSerial_Read(UsbSerial_Device *dev, uint8_t *buff, uint32_t bufferSize, uint32_t *bytesRead);

/**
 * @brief 将buff中的数据写入USB串口设备。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev 设备句柄。
 * @param buff 写入USB串口设备数据的缓冲区。
 * @param bufferSize 缓冲区的大小。
 * @param bytesWritten 实际写入的字节数。
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER} 参数检查失败。可能原因：1. dev为空指针;
 *     2. buff为空指针; 3. bufferSize等于0; 4. bytesWritten为空指针。
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR} DDK服务通信失败。
 *     {@link USB_SERIAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION} 无效操作。
 * @since 18
 */
int32_t OH_UsbSerial_Write(UsbSerial_Device *dev, uint8_t *buff, uint32_t bufferSize, uint32_t *bytesWritten);

*/
int32_t OH_UsbSerial_Write(UsbSerial_Device *dev, uint8_t *buff, uint32_t bufferSize, uint32_t *bytesWritten);

/**
 * @brief 设置USB串口设备的波特率。如果USB串口设备的参数为默认值（数据位为8，停止位为1，数据传输无校验），则只需要调用该接口设置波特率。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev 设备句柄。
 * @param baudRate USB串口设备的波特率。
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER}参数检查失败。可能原因：dev为空指针。
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR} DDK服务通信失败。
 *     {@link USB_SERIAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION} 无效操作。
 * @since 18
 */
int32_t OH_UsbSerial_SetBaudRate(UsbSerial_Device *dev, uint32_t baudRate);

*/
int32_t OH_UsbSerial_SetBaudRate(UsbSerial_Device *dev, uint32_t baudRate);

/**
 * @brief 设置USB串口设备的参数。如果USB串口设备的参数不为默认值（数据位默认为8，停止位默认为1，数据传输默认无校验），则需要调用该接口进行参数设置。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev 设备句柄。
 * @param params 待设置的USB串口设备参数，详见{@link UsbSerial_Params}。
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER} 参数检查失败。可能原因：1. dev为空指针;
 *     2. params为空指针。
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR} DDK服务通信失败。
 *     {@link USB_SERIAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION} 无效操作。
 * @since 18
 */
int32_t OH_UsbSerial_SetParams(UsbSerial_Device *dev, UsbSerial_Params *params);

* @since 18
 */
int32_t OH_UsbSerial_SetParams(UsbSerial_Device *dev, UsbSerial_Params *params);

/**
 * @brief 设置读取USB串口设备上报数据的超时时间（毫秒）。在不调用此函数的情况下，超时值默认为0，表示不管是否读取到数据都立即返回。如果需要等待一定的时间或者必须读取到数据，则调用该接口。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev 设备句柄。
 * @param timeout 读取USB串口设备的超时时间，其取值范围为：- (0, 25500]：以毫秒为单位的时间值，将其四舍五入为最接近的100毫秒后，作为实际的超时时间。例如，输入12321，实际生效的超时时间为12300。
 *     - 0：表示立即返回数据，不等待。- -1：表示以阻塞方式读取数据，即读取数据时，只有读到指定长度的数据后才返回，详见{@link OH_UsbSerial_Read}。
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER} 参数检查失败。可能原因：1. dev为空指针;
 *     2. timeout < -1 or timeout > 25500.
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR} DDK服务通信失败。
 *     {@link USB_SERIAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION} 无效操作。
 * @since 18
 */
int32_t OH_UsbSerial_SetTimeout(UsbSerial_Device *dev, int timeout);

* @since 18
 */
int32_t OH_UsbSerial_SetTimeout(UsbSerial_Device *dev, int timeout);

/**
 * @brief 设置流控参数。USB串口设备通信中的流控用于管理数据传输的速率，以确保发送方不会发送超过接收方处理能力的数据量。
 * 如果USB串口设备实现了流控处理，则需要调用此接口。如果不调用此接口，默认为无流控。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev 设备句柄。
 * @param flowControl 流控方式，详见{@link UsbSerial_FlowControl}。
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER} 参数检查失败。可能原因：dev为空指针。
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR} DDK服务通信失败。
 *     {@link USB_SERIAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION} 无效操作。
 * @since 18
 */
int32_t OH_UsbSerial_SetFlowControl(UsbSerial_Device *dev, UsbSerial_FlowControl flowControl);

link USB_SERIAL_DDK_INVALID_OPERATION;

invalid operation;

/**
 * @brief 刷新输入缓冲区，缓冲区中的数据会被立刻清空。在和USB串口设备通信过程中，特别是在调试阶段，有时会遇到乱序的数据包或者其他异常情况。
 * 调用该接口可以帮助清理这些异常状况，使通信恢复正常。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev 设备句柄。
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER} 参数检查失败。可能原因：dev为空指针。
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR} DDK服务通信失败。
 *     {@link USB_SERIAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION} 无效操作。
 * @since 18
 */
int32_t OH_UsbSerial_FlushInput(UsbSerial_Device *dev);

/**
 * @brief 写入完成后清空输入和输出缓冲区。在向USB串口设备发送数据时，可能会有大量数据缓冲在内核中等待发送。如果应用程序关闭文件描述符或者退出之前没有等待这些数据被实际发送出去，那么部分数据可能会丢失。
 * 调用该接口可以确保所有的数据都被发送完毕再继续执行后续操作。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev 设备句柄。
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER} 参数检查失败。可能原因：dev为空指针。
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR} DDK服务通信失败。
 *     {@link USB_SERIAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION} 无效操作。
 * @since 18
 */
int32_t OH_UsbSerial_Flush(UsbSerial_Device *dev);

/**
 * @brief 刷新输出缓冲区，缓冲区中的数据会被立刻清空。在和USB串口设备通信过程中，特别是在调试阶段，有时会遇到乱序的数据包或者其他异常情况。
 * 调用该接口可以帮助清理这些异常状况，使通信恢复正常。
 *
 * @permission ohos.permission.ACCESS_DDK_USB_SERIAL
 * @param dev 设备句柄。
 * @return {@link USB_SERIAL_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_SERIAL_DDK_NO_PERM} 权限校验失败。
 *     {@link USB_SERIAL_DDK_INVALID_PARAMETER} 参数检查失败。可能原因：dev为空指针。
 *     {@link USB_SERIAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link USB_SERIAL_DDK_SERVICE_ERROR} DDK服务通信失败。
 *     {@link USB_SERIAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link USB_SERIAL_DDK_INVALID_OPERATION} 无效操作。
 * @since 18
 */
int32_t OH_UsbSerial_FlushOutput(UsbSerial_Device *dev);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // DDK_USB_SERIAL_API_H

/** @} */