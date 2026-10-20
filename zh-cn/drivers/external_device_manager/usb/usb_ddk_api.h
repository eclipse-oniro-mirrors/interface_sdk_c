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
 * @brief 提供USB DDK接口，包括主机侧打开和关闭接口、管道同步异步读写通信、控制传输、中断传输等，适用于需要与USB设备进行底层交互和数据通信的场景，帮助开发者实现高效的USB设备驱动开发。
 *
 * @syscap SystemCapability.Driver.USB.Extension
 * @since 10
 * @version 1.0
 */

/**
 * @file usb_ddk_api.h
 *
 * @brief 声明用于主机侧访问设备的USB DDK接口，提供USB设备管理、配置和数据传输等功能，帮助开发者实现与USB设备的底层交互和数据通信。
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
 * @brief 初始化USB DDK。必须在调用其他所有USB DDK方法之前调用此方法。请在使用完DDK后调用{@link OH_Usb_Release}或{@link OH_Usb_ReleaseResource}释放资源。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败或内部错误。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_MEMORY_ERROR} 内存分配失败，请检查内存大小和有效性。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_Init(void);

/**
 * @brief 释放USB DDK。在不再使用USB DDK功能时使用以正确释放资源，需在调用{@link OH_Usb_Init}完成初始化后使用。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @since 10
 * @version 1.0
 */
void OH_Usb_Release(void);

/**
 * @brief 释放USB DDK。在不再使用USB DDK功能时使用以正确释放资源，需在调用{@link OH_Usb_Init}完成初始化后使用。该接口返回一个整数值，可用于判断执行结果。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 * @since 18
 * @version 1.0
 */
int32_t OH_Usb_ReleaseResource(void);

/**
 * @brief 获取设备描述符，请确保传入的指针参数是有效的。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId 设备ID，可通过{@link OH_Usb_GetDevices}获取，代表要获取描述符的设备。
 * @param desc 输出参数，用于接收获取到的设备描述符，详细定义请参考{@link UsbDeviceDescriptor}。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 入参desc为空指针，请检查参数有效性。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_GetDeviceDescriptor(uint64_t deviceId, struct UsbDeviceDescriptor *desc);

/**
 * @brief 获取配置描述符。请在描述符使用完后调用{@link OH_Usb_FreeConfigDescriptor}释放描述符，否则会造成内存泄漏。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId 设备ID，可通过{@link OH_Usb_GetDevices}获取，代表要获取配置描述符的设备。
 * @param configIndex 配置索引，对应USB协议配置描述符中的bConfigurationValue字段。
 * @param config 输出参数，用于接收获取到的配置描述符，包含USB协议中定义的标准配置描述符，以及与其关联的接口描述符和端点描述符。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 入参config为空指针，请检查参数有效性。
 *     <br>{@link USB_DDK_IO_FAILED} 数据I/O异常，请检查参数和设备规格。
 *     <br>{@link USB_DDK_MEMORY_ERROR} 内存分配失败，请检查内存大小和有效性。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_GetConfigDescriptor(
    uint64_t deviceId, uint8_t configIndex, struct UsbDdkConfigDescriptor ** const config);

/**
 * @brief 释放配置描述符。使用完配置描述符后必须调用此接口释放，否则会造成内存泄漏。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param config 配置描述符，通过{@link OH_Usb_GetConfigDescriptor}获得的配置描述符。
 * @since 10
 * @version 1.0
 */
void OH_Usb_FreeConfigDescriptor(struct UsbDdkConfigDescriptor * const config);

/**
 * @brief 声明USB接口，申请USB接口的独占使用权。调用此方法声明接口后，在使用完毕后必须调用OH_Usb_ReleaseInterface释放接口，否则会导致接口资源无法释放。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId 设备ID，可通过{@link OH_Usb_GetDevices}获取，代表要操作的设备。
 * @param interfaceIndex 接口索引，对应USB协议中的bInterfaceNumber。
 * @param interfaceHandle 输出参数，用于接收声明的接口操作句柄（接口声明成功后，该参数将会被赋值）。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 入参interfaceHandle为空指针，请检查参数有效性。
 *     <br>{@link USB_DDK_MEMORY_ERROR} 内存超出限制，请检查内存大小和有效性。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_ClaimInterface(uint64_t deviceId, uint8_t interfaceIndex, uint64_t *interfaceHandle);

/**
 * @brief 释放USB接口，用于释放对USB设备接口的独占使用权。需要先调用{@link OH_Usb_ClaimInterface}声明接口获取interfaceHandle后，在使用完毕后才能调用此方法释放接口。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle 接口操作句柄，代表要释放的接口，需通过{@link OH_Usb_ClaimInterface}获取。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 参数错误，请检查参数有效性。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_ReleaseInterface(uint64_t interfaceHandle);

/**
 * @brief 激活USB接口的备用设置，在需要改变接口工作模式时调用。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle 接口操作句柄，代表要操作的接口，需通过{@link OH_Usb_ClaimInterface}获取。
 * @param settingIndex 备用设置索引，对应USB协议中接口描述符的 bAlternateSetting字段。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 参数错误，请检查参数有效性。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SelectInterfaceSetting(uint64_t interfaceHandle, uint8_t settingIndex);

/**
 * @brief 获取USB接口当前激活的备用设置。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle 接口操作句柄，代表要操作的接口，需通过{@link OH_Usb_ClaimInterface}获取。
 * @param settingIndex 输出参数，用于接收获取到的备用设置索引，对应USB协议中接口描述符的 bAlternateSetting字段。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 入参settingIndex为空指针，请检查参数有效性。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_GetCurrentInterfaceSetting(uint64_t interfaceHandle, uint8_t *settingIndex);

/**
 * @brief 发送控制读请求，该接口为同步接口。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle 接口操作句柄，代表要操作的接口，需通过{@link OH_Usb_ClaimInterface}获取。
 * @param setup 请求相关的参数，详细定义请参考{@link UsbControlRequestSetup}。
 * @param timeout 超时时间（单位：毫秒），表示未收到响应时等待的最大时间，设置为0表示无限制等待。
 * @param data 要读取的数据缓冲区，用于存放从设备读取到的数据。
 * @param dataLen 表示data的数据长度，取值应不小于setup包中wLength字段指定的数据长度。在函数返回后，表示实际读取到的数据的长度。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 入参setup或者data或者dataLen为空指针，或者dataLen小于读取到的数据长度。请确保指针参数有效，且dataLen足够大。
 *     <br>{@link USB_DDK_MEMORY_ERROR} 拷贝读取数据的内存失败，请检查内存大小和有效性。
 *     <br>{@link USB_DDK_IO_FAILED} 数据I/O异常，请检查参数和设备规格。
 *     <br>{@link USB_DDK_TIMEOUT} 接口调用超时，请检查传输参数和设备状态。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SendControlReadRequest(uint64_t interfaceHandle, const struct UsbControlRequestSetup *setup,
    uint32_t timeout, uint8_t *data, uint32_t *dataLen);

/**
 * @brief 发送控制写请求，该接口为同步接口。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param interfaceHandle 接口操作句柄，代表要操作的接口，需通过{@link OH_Usb_ClaimInterface}获取。
 * @param setup 请求相关的参数，详细定义请参考{@link UsbControlRequestSetup}。
 * @param timeout 超时时间（单位：毫秒），表示未收到响应时等待的最大时间，设置为0表示无限制等待。
 * @param data 要写入的数据缓冲区，指向要往设备发送的数据。
 * @param dataLen 表示data数据长度，取值应与setup包中的wLength字段一致，且最大不超过1024。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 入参setup或者data为空指针，请检查参数有效性。
 *     <br>{@link USB_DDK_MEMORY_ERROR} 内存拷贝失败，请检查内存大小和有效性。
 *     <br>{@link USB_DDK_IO_FAILED} 数据I/O异常，请检查参数和设备规格。
 *     <br>{@link USB_DDK_TIMEOUT} 接口调用超时，请检查传输参数和设备状态。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_SendControlWriteRequest(uint64_t interfaceHandle, const struct UsbControlRequestSetup *setup,
    uint32_t timeout, const uint8_t *data, uint32_t dataLen);

/**
 * @brief 发送管道请求，该接口为同步接口。中断传输和批量传输都使用该接口发送请求。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param pipe 要传输数据的管道信息。
 * @param devMmap 数据缓冲区，可以通过{@link OH_Usb_CreateDeviceMemMap}获得。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 入参pipe为空指针或devMmap为空指针或devMmap的地址为空，请检查参数有效性。
 *     <br>{@link USB_DDK_MEMORY_ERROR} 内存拷贝失败，请检查内存大小和有效性。
 *     <br>{@link USB_DDK_IO_FAILED} 数据I/O异常，请检查传输参数和设备状态。
 *     <br>{@link USB_DDK_TIMEOUT} 接口超时，请检查传输参数和设备状态。
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
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 入参pipe为空指针或ashmem为空指针或ashmem的地址为空，请检查参数有效性。
 *     <br>{@link USB_DDK_MEMORY_ERROR} 内存拷贝失败，请检查内存大小和有效性。
 *     <br>{@link USB_DDK_IO_FAILED} 数据I/O异常，请检查传输参数和设备状态。
 *     <br>{@link USB_DDK_TIMEOUT} 接口超时，请检查传输参数和设备状态。
 * @since 12
 */
int32_t OH_Usb_SendPipeRequestWithAshmem(const struct UsbRequestPipe *pipe, DDK_Ashmem *ashmem);

/**
 * @brief 创建缓冲区。请在缓冲区使用完后，调用{@link OH_Usb_DestroyDeviceMemMap}销毁缓冲区，否则会造成资源泄漏。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceId 设备ID，可通过{@link OH_Usb_GetDevices}获取，代表要创建缓冲区的设备。
 * @param size 缓冲区的大小（字节）。
 * @param devMmap 输出参数，创建的缓冲区指针通过该参数返回给调用者。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 入参devMmap为空指针或\*devMmap为空指针，请检查参数有效性。
 *     <br>{@link USB_DDK_MEMORY_ERROR} 内存映射失败或devMmap的内存分配失败，请检查内存大小和有效性。
 * @since 10
 * @version 1.0
 */
int32_t OH_Usb_CreateDeviceMemMap(uint64_t deviceId, size_t size, UsbDeviceMemMap **devMmap);

/**
 * @brief 销毁缓冲区。使用完缓冲区后必须调用此接口销毁，否则会造成资源泄漏。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param devMmap 销毁由{@link OH_Usb_CreateDeviceMemMap}创建的缓冲区。
 * @since 10
 * @version 1.0
 */
void OH_Usb_DestroyDeviceMemMap(UsbDeviceMemMap *devMmap);

/**
 * @brief 获取USB设备ID列表。请保证传入的指针参数是有效的，申请的设备ID数组的大小建议不超过128，以避免过度占用内存。在使用完结构体之后，需释放成员内存，否则会造成资源泄漏。获取到的USB设备ID，
 * 已通过驱动配置信息中的vid进行筛选过滤。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param devices 已申请好的设备内存地址，用于存放获取到的设备ID列表及数量。在使用完毕后，需释放成员内存，否则会造成资源泄漏。
 * @return {@link USB_DDK_SUCCESS} 调用接口成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 入参devices为空指针，请检查参数有效性。
 * @since 18
 */
int32_t OH_Usb_GetDevices(struct Usb_DeviceArray *devices);

/**
 * @brief 执行USB控制传输，该接口为同步接口。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param deviceID 设备ID，可通过{@link OH_Usb_GetDevices}获取，代表要进行通信的设备。
 * @param setupPacket 控制传输请求的setup包配置参数，包含了传输方向、传输数据长度等信息。
 * @param data 已申请好的缓冲区，用于存放输入或输出数据。缓冲区大小应与setup包中的wLength字段一致，且最大不超过1024，否则会被截断。
 * @param timeout 超时时间（单位：毫秒），在未收到响应时等待的最大时间。设置为0表示无限制等待。
 * @return 成功时返回实际传输的字节数（非负数）。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} setupPacket或data为空指针，请检查参数有效性。
 *     <br>{@link USB_DDK_TIMEOUT} 控制传输超时，请检查传输参数和设备状态。
 *     <br>{@link USB_DDK_IO_FAILED} 控制传输请求I/O异常，请检查参数和设备规格。
 * @since 26.0.0
 */
int32_t OH_Usb_ControlTransfer(uint64_t deviceID, const struct UsbControlRequestSetup *setupPacket,
    uint8_t *data, uint32_t timeout);

/**
 * @brief 查询并返回非根集线器列表。请保证传入的指针参数是有效的，申请的非根集线器ID数组的大小建议不超过128，以避免过度占用内存。在使用完结构体之后，需释放成员内存，否则会造成资源泄漏。
 *
 * @permission ohos.permission.ACCESS_DDK_USB
 * @param nonRootHub 已申请好的非根集线器内存地址，用于存放查询到的非根集线器ID列表及数量。在使用完毕后，需释放成员内存，否则会造成资源泄漏。
 * @return {@link USB_DDK_SUCCESS} 查询操作成功。
 *     <br>{@link USB_DDK_NO_PERM} 权限检查失败，请检查应用已获取了ohos.permission.ACCESS_DDK_USB权限。
 *     <br>{@link USB_DDK_INVALID_OPERATION} 连接USB DDK服务失败，请先调用{@link OH_Usb_Init}完成初始化。
 *     <br>{@link USB_DDK_INVALID_PARAMETER} 入参nonRootHub为空指针，请检查参数有效性。
 * @since 26.0.0
 */
int32_t OH_Usb_GetNonRootHubs(struct Usb_NonRootHubArray *nonRootHub);
/** @} */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // USB_DDK_API_H