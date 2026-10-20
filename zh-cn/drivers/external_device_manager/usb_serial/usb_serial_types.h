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
 * @brief 提供USB Serial DDK（USB串口驱动开发工具包）接口，包括枚举类型和USB Serial DDK API使用的数据结构。串口通信常见于工业用途及一些老旧设备，如：发卡机、身份证读卡器等。
 * 开发者通过使用USB Serial DDK，可以开发USB串口外设扩展驱动。
 *
 * @since 18
 */

/**
 * @file usb_serial_types.h
 *
 * @brief 提供USB Serial DDK中的枚举类型与结构体的定义，用于USB串口驱动开发，简化串口设备参数配置、返回码处理和流量控制等操作，提升驱动开发效率。
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
 * @brief USB串口设备数据结构（不透明），用于表示USB串口设备。开发者应通过{@link OH_UsbSerial_Open}接口函数获取此结构体实例。
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
     * 权限被拒绝。请确保应用在module.json5文件中声明了所需的权限。
     */
    USB_SERIAL_DDK_NO_PERM = 201,
    /**
     * 无效参数。请确保传入的参数值在有效范围内，参考相关接口的参数说明。
     */
    USB_SERIAL_DDK_INVALID_PARAMETER = 401,
    /**
     * 操作成功。
     */
    USB_SERIAL_DDK_SUCCESS = 31600000,
    /**
     * 无效操作，例如使用了无效的设备句柄。请检查确保设备处于正常打开的状态。
     */
    USB_SERIAL_DDK_INVALID_OPERATION = 31600001,
    /**
     * 初始化失败。请先初始化DDK服务。
     */
    USB_SERIAL_DDK_INIT_ERROR = 31600002,
    /**
     * 服务错误。请检查DDK服务状态和接口调用逻辑是否正常。
     */
    USB_SERIAL_DDK_SERVICE_ERROR = 31600003,
    /**
     * 内存相关错误，例如内存不足、内存数据复制失败或内存申请故障。建议优化内存参数，及时释放不再需要的资源。
     */
    USB_SERIAL_DDK_MEMORY_ERROR = 31600004,
    /**
     * I/O 错误。请检查设备连接是否正常、传输线是否完好、设备是否处于正常工作状态。
     */
    USB_SERIAL_DDK_IO_ERROR = 31600005,
    /**
     * 未找到设备。请检查参数和设备连接状态。
     */
    USB_SERIAL_DDK_DEVICE_NOT_FOUND = 31600006,
} UsbSerial_DdkRetCode;

/**
 * @brief 定义USB Serial DDK使用的USB串口参数，用于USB转串口设备的通信参数配置，需与目标通信设备的配置保持一致，否则可能无法正常通信。常见于工业控制设备、调试工具、
 * 传感器数据采集等需要通过USB串口与设备通信的场景。
 *
 * @since 18
 */
typedef struct UsbSerial_Params {
    /**
     * 波特率，单位：波特。
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
     * 校验参数设置（0：无校验；1：奇校验；2：偶校验）。
     */
    uint8_t parity;
} __attribute__((aligned(8))) UsbSerial_Params;

/**
 * @brief 定义USB Serial DDK中的流量控制。在使用USB串口进行数据传输时，需要根据通信场景选择合适的流量控制方式。例如，在高速大数据量传输场景下，建议使用硬件流控以避免数据丢失；在低速或对实时性要求不高的场景下，
 * 可使用软件流控；在短距离、可靠的点对点通信场景下，可选择无流控。
 *
 * @since 18
 */
typedef enum {
    /**
     * 无流量控制。适用于低速传输或无需流控的场景，但可能导致数据丢失。
     */
    USB_SERIAL_NO_FLOW_CONTROL = 0,
    /**
     * 软件流控。使用XON/XOFF字符控制，适用于不支持硬件流控的设备。
     */
    USB_SERIAL_SOFTWARE_FLOW_CONTROL = 1,
    /**
     * 硬件流控。使用RTS/CTS信号线，适用于高速数据传输，可靠性高。
     */
    USB_SERIAL_HARDWARE_FLOW_CONTROL = 2,
} UsbSerial_FlowControl;

/**
 * @brief 定义USB Serial DDK使用的校验参数枚举。在配置USB串口通信参数时，需要根据数据传输的可靠性要求选择合适的校验方式。例如，在对数据完整性要求较高的工业控制场景下，建议使用奇校验或偶校验来检测传输错误；
 * 在高噪声干扰环境下，校验可以帮助识别错误数据；在短距离、可靠的通信场景下，为提高传输效率，可选择无校验。
 *
 * @since 18
 */
typedef enum {
    /**
     * 无校验。在短距离、可靠的通信场景下，为提高传输效率，可选择无校验。
     */
    USB_SERIAL_PARITY_NONE = 0,
    /**
     * 奇校验。适用于对数据完整性要求较高的场景。
     */
    USB_SERIAL_PARITY_ODD = 1,
    /**
     * 偶校验。适用于对数据完整性要求较高的场景。
     */
    USB_SERIAL_PARITY_EVEN = 2,
} UsbSerial_Parity;

#ifdef __cplusplus
}
#endif
#endif // DDK_USB_SERIAL_TYPES_H
/** @} */

