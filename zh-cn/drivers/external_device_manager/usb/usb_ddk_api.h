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
 * @brief 初始化USB DDK。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_INVALID_OPERATION} 连接 USB DDK 服务失败或内部错误。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_MEMORY_ERROR} 内存分配失败。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_Init(void);

/**
 * @brief 释放USB DDK。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @since 10
 * @version 1.0
 */
void OH_Usb_Release(void);

/**
 * @brief 释放USB DDK。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_INVALID_OPERATION} 连接 USB DDK 服务失败。
 * @since 18
 * @version 1.0
 */
int32_t OH_Usb_ReleaseResource(void);

/**
 * @brief 获取设备描述符。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId 设备ID，代表要获取描述符的设备。
 * @param desc 设备描述符，详细定义请参考{@link UsbDeviceDescriptor}。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_INVALID_OPERATION} 连接usb_ddk服务失败。
 *     {@link USB_DDK_INVALID_PARAMETER} 入参desc为空指针。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_GetDeviceDescriptor(uint64_t deviceId, struct UsbDeviceDescriptor *desc);

/**
 * @brief 释放配置描述符，请在描述符使用完后释放描述符，否则会造成内存泄漏。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param config 配置描述符，通过{@link OH_Usb_GetConfigDescriptor}获得的配置描述符。
 * @since 10
 * @version 1.0
 */
void OH_Usb_FreeConfigDescriptor(struct UsbDdkConfigDescriptor * const config);

/**
 * @brief 获取配置描述符。请在描述符使用完后使用{@link OH_Usb_FreeConfigDescriptor}释放描述符，否则会造成内存泄漏。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId 设备ID，代表要获取配置描述符的设备。
 * @param configIndex 配置id，对应USB协议配置描述符中的bConfigurationValue字段
 * @param config 配置描述符，包含USB协议中定义的标准配置描述符，以及与其关联的接口描述符和端点描述符。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败。
 *     {@link USB_DDK_INVALID_PARAMETER} 入参config为空指针。
 *     {@link USB_DDK_IO_FAILED} 数据I/O异常。
 *     {@link USB_DDK_MEMORY_ERROR} 内存分配失败。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_GetConfigDescriptor(
    uint64_t deviceId, uint8_t configIndex, struct UsbDdkConfigDescriptor ** const config);

configuration descriptor;

use <b>;

release;

a;

descriptor;

* @brief;

To avoid memory leakage;

OH_Usb_FreeConfigDescriptor</b>;

* to;

after;

/**
 * @brief 声明接口。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId 设备ID，代表要操作的设备。
 * @param interfaceIndex 接口索引，对应USB协议中的{@link bInterfaceNumber}。
 * @param interfaceHandle 接口操作句柄，接口声明成功后，该参数将会被赋值。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败。
 *     {@link USB_DDK_INVALID_PARAMETER} 入参interfaceHandle为空指针。
 *     {@link USB_DDK_MEMORY_ERROR} 内存超出限制。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_ClaimInterface(uint64_t deviceId, uint8_t interfaceIndex, uint64_t *interfaceHandle);

/**
 * @brief 释放接口。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle 接口操作句柄，代表要释放的接口。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败。
 *     {@link USB_DDK_INVALID_PARAMETER} 参数错误。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_ReleaseInterface(uint64_t interfaceHandle);

Releases;

the;

/**
 * @brief 激活接口的备用设置。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle 接口操作句柄，代表要操作的接口。
 * @param settingIndex 备用设置索引，对应USB协议中接口描述符的 bAlternateSetting字段。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败。
 *     {@link USB_DDK_INVALID_PARAMETER} 参数错误。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SelectInterfaceSetting(uint64_t interfaceHandle, uint8_t settingIndex);

/**
 * @brief 获取接口当前激活的备用设置。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle 接口操作句柄，代表要操作的接口。
 * @param settingIndex 备用设置索引，对应USB协议中接口描述符的 bAlternateSetting字段。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败。
 *     {@link USB_DDK_INVALID_PARAMETER} 入参settingIndex为空指针。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_GetCurrentInterfaceSetting(uint64_t interfaceHandle, uint8_t *settingIndex);

/**
 * @brief 发送控制读请求，该接口为同步接口。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle 接口操作句柄，代表要操作的接口。
 * @param setup 请求相关的参数，详细定义请参考{@link UsbControlRequestSetup}。
 * @param timeout 超时时间，单位为毫秒。
 * @param data 要传输的数据。
 * @param dataLen 表示data的数据长度，在函数返回后，表示实际读取到的数据的长度。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_FAILED} 权限校验失败。
 *     {@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败。
 *     {@link USB_DDK_INVALID_PARAMETER} 入参setup或者data或者dataLen为空指针，或者datalen小于读取到的数据长度。
 *     {@link USB_DDK_MEMORY_ERROR} 拷贝读取数据的内存失败。
 *     {@link USB_DDK_IO_FAILED} 数据I/O异常。
 *     {@link USB_DDK_TIMEOUT} 接口调用超时。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SendControlReadRequest(uint64_t interfaceHandle, const struct UsbControlRequestSetup *setup,
    uint32_t timeout, uint8_t *data, uint32_t *dataLen);

/**
 * @brief 发送控制写请求，该接口为同步接口。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle 接口操作句柄，代表要操作的接口。
 * @param setup 请求相关的参数，详细定义请参考{@link UsbControlRequestSetup}。
 * @param timeout 超时时间，单位为毫秒。
 * @param data 要传输的数据。
 * @param dataLen 表示data数据长度。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_FAILED} 权限校验失败。
 *     {@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败。
 *     {@link USB_DDK_INVALID_PARAMETER} 入参setup或者data为空指针。
 *     {@link USB_DDK_MEMORY_ERROR} 内存拷贝失败。
 *     {@link USB_DDK_IO_FAILED} 数据I/O异常。
 *     {@link USB_DDK_TIMEOUT} 接口调用超时。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SendControlWriteRequest(uint64_t interfaceHandle, const struct UsbControlRequestSetup *setup,
    uint32_t timeout, const uint8_t *data, uint32_t dataLen);

/**
 * @brief 执行一个 USB 控制传输。传输的方向根据设置包的 bmRequestType 字段进行推断。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceID 与该设备通信的 ID
 * @param setupPacket 控制传输请求中设置包的配置参数
 * @param data 一个足够大小的数据缓冲区，其大小根据 bmRequestType 中的方向位来确定（根据传输方向用于输入或输出）。
 * @param timeout 此函数应在未收到响应的情况下等待超时（以毫秒为单位）才能放弃。对于无限超时，请使用值 0。
 * @return 成功时的实际传输字节数。
 * {@link USB_DDK_NO_PERM} 权限认证失败。
 * {@link USB_DDK_INVALID_OPERATION} DDK 服务未初始化。请先调用 OH_Usb_Init 完成初始化过程。
 * {@link USB_DDK_INVALID_PARAMETER} setupPacket 或 data 参数无效。
 * {@link USB_DDK_TIMEOUT} 若控制传输超时。
 * {@link USB_DDK_IO_FAILED} 控制传输请求 IO 异常。
 * @since 26.0.0
 */
int32_t OH_Usb_ControlTransfer(uint64_t deviceID, const struct UsbControlRequestSetup *setupPacket, uint8_t *data,
    uint32_t timeout);

use;

/**
 * @brief 发送管道请求，该接口为同步接口。中断传输和批量传输都使用该接口发送请求。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param pipe 要传输数据的管道信息。
 * @param devMmap 数据缓冲区，可以通过{@link OH_Usb_CreateDeviceMemMap}获得。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败。
 *     {@link USB_DDK_INVALID_PARAMETER} 入参pipe为空指针或devMmap为空指针或devMmap的地址为空。
 *     {@link USB_DDK_MEMORY_ERROR} 读取数据的内存拷贝失败。
 *     {@link USB_DDK_IO_FAILED} 数据 IO 异常。
 *     {@link USB_DDK_TIMEOUT} 接口超时。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SendPipeRequest(const struct UsbRequestPipe *pipe, UsbDeviceMemMap *devMmap);

/**
 * @brief 基于共享内存发送管道请求，该接口为同步接口。中断传输和批量传输都使用该接口发送请求。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param pipe 要传输数据的管道信息。
 * @param ashmem 共享内存，可以通过{@link OH_DDK_CreateAshmem}获得。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败。
 *     {@link USB_DDK_INVALID_PARAMETER}入参pipe为空指针或ashmem为空指针或ashmem的地址为空。
 *     {@link USB_DDK_MEMORY_ERROR} 读取数据的内存拷贝失败。
 *     {@link USB_DDK_IO_FAILED} 数据 IO 异常。
 *     {@link USB_DDK_TIMEOUT} 接口超时。
 * @since 12
 */
int32_t OH_Usb_SendPipeRequestWithAshmem(const struct UsbRequestPipe *pipe, DDK_Ashmem *ashmem);

/**
 * @brief 销毁缓冲区。请在缓冲区使用完后及时销毁缓冲区，否则会造成资源泄漏。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param devMmap 销毁由{@link OH_Usb_CreateDeviceMemMap}创建的缓冲区。
 * @since 10
 * @version 1.0
 */
void OH_Usb_DestroyDeviceMemMap(UsbDeviceMemMap *devMmap);

/**
 * @brief 创建缓冲区。请在缓冲区使用完后，调用{@link OH_Usb_DestroyDeviceMemMap}销毁缓冲区，否则会造成资源泄漏。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId 设备ID，代表要创建缓冲区的设备。
 * @param size 缓冲区的大小。
 * @param devMmap 创建的缓冲区通过该参数返回给调用者。
 * @return {@link USB_DDK_SUCCESS}调用接口成功。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_INVALID_PARAMETER} 入参devMmap为空指针或*devMmap为空指针。
 *     {@link USB_DDK_MEMORY_ERROR} 内存映射失败或devMmap的内存分配失败。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_CreateDeviceMemMap(uint64_t deviceId, size_t size, UsbDeviceMemMap **devMmap);

/**
 * @brief 获取USB设备ID列表。请保证传入的指针参数是有效的，申请的设备ID数组的大小建议不超过128，以避免过度占用内存。在使用完结构体之后，需释放成员内存，否则会造成资源泄漏。获取到的USB设备ID，
 * 已通过驱动配置信息中的vid进行筛选过滤。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param devices 已申请好的设备内存地址，用于存放获取到的设备ID列表及数量。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败。
 *     {@link USB_DDK_INVALID_PARAMETER} 入参devices为空指针。
 * @since 18
 */
int32_t OH_Usb_GetDevices(struct Usb_DeviceArray *devices);

/**
 * @brief 查询并返回非根集线器列表。请保证传入的指针参数是有效的，申请的非根集线器ID数组的大小建议不超过128，以避免过度占用内存。在使用完结构体之后，需释放成员内存，否则会造成资源泄漏。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param nonRootHub 已申请好的非根集线器内存地址，用于存放查询到的非根集线器ID列表及数量。
 * @return {@link USB_DDK_SUCCESS} 查询操作成功。
 *     {@link USB_DDK_NO_PERM} 权限检查失败。
 *     {@link USB_DDK_INVALID_OPERATION} DDK服务未初始化，请先调用{@link OH_Usb_Init}完成初始化。
 *     {@link USB_DDK_INVALID_PARAMETER} 入参nonRootHub为空指针。
 * @since 26.0.0
 */
int32_t OH_Usb_GetNonRootHubs(struct Usb_NonRootHubArray *nonRootHub);