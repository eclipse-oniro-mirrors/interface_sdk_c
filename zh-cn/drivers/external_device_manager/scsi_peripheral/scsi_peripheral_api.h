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
 * @addtogroup ScsiPeripheralDDK
 * @{
 *
 * @brief Provide ScsiPeripheral DDK interface, including initializing DDK, releasing DDK, opening devices, reading and
 * writing devices, etc.
 * @since 18
 */

/**
 * @file scsi_peripheral_api.h
 *
 * @brief 声明用于主机侧访问SCSI设备的SCSI Peripheral DDK接口。
 *
 * @kit DriverDevelopmentKit
 * @library libscsi.z.so
 * @syscap SystemCapability.Driver.SCSI.Extension
 * @since 18
 */

#ifndef SCSI_PERIPHERAL_API_H
#define SCSI_PERIPHERAL_API_H

#include <stdint.h>
#include "scsi_peripheral_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief 初始化SCSI Peripheral DDK。
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM} 权限校验失败。
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR} 初始化DDK失败。
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR} 与DDK服务通信失败。
 * @since 18
 */
int32_t OH_ScsiPeripheral_Init(void);

/**
 * @brief 释放SCSI Peripheral DDK。
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM} 权限校验失败。
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR} 与DDK服务通信失败。
 * @since 18
 */
int32_t OH_ScsiPeripheral_Release(void);

/**
 * @brief 打开deviceId和interfaceIndex指定的SCSI设备。其中，deviceId可以通过USB设备的总线编号左移32位后、同其设备地址进行或运算得到，
 * interfaceIndex为需要打开的USB接口的索引值。
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param deviceId 设备ID，代表要操作的设备。
 * @param interfaceIndex 接口索引，对应SCSI设备的接口。
 * @param dev 设备句柄，详情参见{@link ScsiPeripheral_Device}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM} 权限校验失败。
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} dev为空或*dev为空。
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR} 与DDK服务通信失败。
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR} 内存操作失败。
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR} DDK发生IO错误。
 *     {@link SCSIPERIPHERAL_DDK_DEVICE_NOT_FOUND} 通过deviceId和interfaceIndex找不到设备。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION} 不支持该操作。
 * @since 18
 */
int32_t OH_ScsiPeripheral_Open(uint64_t deviceId, uint8_t interfaceIndex, ScsiPeripheral_Device **dev);

/**
 * @brief 关闭SCSI设备。
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev 设备句柄，详情参见{@link ScsiPeripheral_Device}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM} 权限校验失败。
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} dev为空或*dev为空。
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR} 与DDK服务通信失败。
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR} DDK发生I/O错误。
 * @since 18
 */
int32_t OH_ScsiPeripheral_Close(ScsiPeripheral_Device **dev);

/**
 * @brief 检查逻辑单元是否已经准备好。
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev 设备句柄，详情参见{@link ScsiPeripheral_Device}。
 * @param request 逻辑单元检查命令（test unit ready）的请求信息，详情参见{@link ScsiPeripheral_TestUnitReadyRequest}。
 * @param response 逻辑单元检查命令（test unit ready）的响应信息，详情参见{@link ScsiPeripheral_Response}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM} 权限校验失败。
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} dev为空、request为空或者response为空。
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR} 与DDK服务通信失败。
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR} 内存操作失败。
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT} 传输超时。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION} 不支持该操作。
 * @since 18
 */
int32_t OH_ScsiPeripheral_TestUnitReady(ScsiPeripheral_Device *dev, ScsiPeripheral_TestUnitReadyRequest *request,
    ScsiPeripheral_Response *response);

/**
 * @brief 查询SCSI设备的基本信息。
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev 设备句柄，详情参见{@link ScsiPeripheral_Device}。
 * @param request inquiry命令的请求信息，详情参见{@link ScsiPeripheral_InquiryRequest}。
 * @param inquiryInfo inquiry命令返回的查询信息，详情参见{@link ScsiPeripheral_InquiryInfo}。
 * @param response inquiry命令返回的原始响应信息，详情参见{@link ScsiPeripheral_Response}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM} 权限校验失败。
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} dev为空、 request为空、inquiryInfo 为空、inquiryInfo->data或者response为空。
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR} 与DDK服务通信失败。
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR} 内存操作失败。
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT} 传输超时。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION} 不支持该操作。
 * @since 18
 */
int32_t OH_ScsiPeripheral_Inquiry(ScsiPeripheral_Device *dev, ScsiPeripheral_InquiryRequest *request,
    ScsiPeripheral_InquiryInfo *inquiryInfo, ScsiPeripheral_Response *response);

/**
 * @brief 获取SCSI设备的容量信息。
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev 设备句柄，详情参见{@link ScsiPeripheral_Device}。
 * @param request read capacity命令的请求信息，详情参见{@link ScsiPeripheral_ReadCapacityRequest}。
 * @param capacityInfo read capacity命令返回的容量信息，详情参见{@link ScsiPeripheral_CapacityInfo}。
 * @param response read capacity命令返回的原始响应信息，详情参见{@link ScsiPeripheral_Response}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM} 权限校验失败。
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} dev为空、 request为空、capacityInfo为空或者response为空。
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR} 与DDK服务通信失败。
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR} 内存操作失败。
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT} 传输超时。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION} 不支持该操作。
 * @since 18
 */
int32_t OH_ScsiPeripheral_ReadCapacity10(ScsiPeripheral_Device *dev, ScsiPeripheral_ReadCapacityRequest *request,
    ScsiPeripheral_CapacityInfo *capacityInfo, ScsiPeripheral_Response *response);

/**
 * @brief 获取sense data（SCSI设备返回给主机的信息，用于报告设备的状态、错误信息以及诊断信息）。
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev 设备句柄，详情参见{@link ScsiPeripheral_Device}。
 * @param request Request Sense命令的请求信息，详情参见{@link ScsiPeripheral_RequestSenseRequest}。
 * @param response Request Sense命令返回的响应信息，详情参见{@link ScsiPeripheral_Response}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM} 权限校验失败。
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} dev为空、 request为空或者response为空。
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR} 与DDK服务通信失败。
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR} 内存操作失败。
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT} 传输超时。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION} 不支持该操作。
 * @since 18
 */
int32_t OH_ScsiPeripheral_RequestSense(ScsiPeripheral_Device *dev, ScsiPeripheral_RequestSenseRequest *request,
    ScsiPeripheral_Response *response);

/**
 * @brief 从指定逻辑块读取数据。
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev 设备句柄，详情参见{@link ScsiPeripheral_Device}。
 * @param request read命令的请求信息，详情参见{@link ScsiPeripheral_IORequest}。
 * @param response read命令返回的响应信息，详情参见{@link ScsiPeripheral_Response}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM} 权限校验失败。
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} dev为空、 request为空、request->data或者response为空。
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR} 与DDK服务通信失败。
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR} 内存操作失败。
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT} 传输超时。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION} 不支持该操作。
 * @since 18
 */
int32_t OH_ScsiPeripheral_Read10(ScsiPeripheral_Device *dev, ScsiPeripheral_IORequest *request,
    ScsiPeripheral_Response *response);

/**
 * @brief 写数据到设备的指定逻辑块。
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev 设备句柄，详情参见{@link ScsiPeripheral_Device}。
 * @param request write命令的请求信息，详情参见{@link ScsiPeripheral_IORequest}。
 * @param response write命令返回的响应信息，详情参见{@link ScsiPeripheral_Response}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM} 权限校验失败。
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} dev为空、 request为空、request->data为空或者response为空。
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR} 与DDK服务通信失败。
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR} 内存操作失败。
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT} 传输超时。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION} 不支持该操作。
 * @since 18
 */
int32_t OH_ScsiPeripheral_Write10(ScsiPeripheral_Device *dev, ScsiPeripheral_IORequest *request,
    ScsiPeripheral_Response *response);

/**
 * @brief 校验指定逻辑块。
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev 设备句柄，详情参见{@link ScsiPeripheral_Device}。
 * @param request verify命令的请求信息，详情参见{@link ScsiPeripheral_VerifyRequest}。
 * @param response verify命令返回的响应信息，详情参见{@link ScsiPeripheral_Response}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM} 权限校验失败。
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} dev为空、request为空或者response为空。
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR} 与DDK服务通信失败。
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR} 内存操作失败。
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT} 传输超时。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION} 不支持该操作。
 * @since 18
 */
int32_t OH_ScsiPeripheral_Verify10(ScsiPeripheral_Device *dev, ScsiPeripheral_VerifyRequest *request,
    ScsiPeripheral_Response *response);

/**
 * @brief 以CDB（Command Descriptor Block）方式发送SCSI命令。
 *
 * @permission ohos.permission.ACCESS_DDK_SCSI_PERIPHERAL
 * @param dev 设备句柄，详情参见{@link ScsiPeripheral_Device}。
 * @param request 请求，详情参见{@link ScsiPeripheral_Request}。
 * @param response 响应，详情参见{@link ScsiPeripheral_Response}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_NO_PERM} 权限校验失败。
 *     {@link SCSIPERIPHERAL_DDK_INIT_ERROR} 未初始化DDK。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} dev为空、 request为空、request->data为
 *     空、request->cdbLength为0或者response为空。
 *     {@link SCSIPERIPHERAL_DDK_SERVICE_ERROR} 与DDK服务通信失败。
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR} 内存操作失败。
 *     {@link SCSIPERIPHERAL_DDK_IO_ERROR} DDK发生I/O错误。
 *     {@link SCSIPERIPHERAL_DDK_TIMEOUT} 传输超时。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_OPERATION} 不支持该操作。
 * @since 18
 */
int32_t OH_ScsiPeripheral_SendRequestByCdb(ScsiPeripheral_Device *dev, ScsiPeripheral_Request *request,
    ScsiPeripheral_Response *response);

/**
 * @brief 创建缓冲区。请在缓冲区使用完后，调用{@link OH_ScsiPeripheral_DestroyDeviceMemMap}销毁缓冲区，否则会造成资源泄漏。
 *
 * @param dev 设备句柄，详情参见{@link ScsiPeripheral_Device}。
 * @param size 缓冲区的大小。
 * @param devMmap 创建的缓冲区通过该参数返回给调用者，详情参见{@link ScsiPeripheral_DeviceMemMap}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} dev为空、devMmap为空或*devMmap为空。
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR} 内存操作失败。
 * @since 18
 */
int32_t OH_ScsiPeripheral_CreateDeviceMemMap(ScsiPeripheral_Device *dev, size_t size,
    ScsiPeripheral_DeviceMemMap **devMmap);

/**
 * @brief 销毁缓冲区。请在缓冲区使用完后及时销毁缓冲区，否则会造成资源泄漏。
 *
 * @param devMmap 待销毁的由{@link OH_ScsiPeripheral_CreateDeviceMemMap}创建的缓冲区，详情参见{@link ScsiPeripheral_DeviceMemMap}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} devMmap为空。
 *     {@link SCSIPERIPHERAL_DDK_MEMORY_ERROR} 内存操作失败。
 * @since 18
 */
int32_t OH_ScsiPeripheral_DestroyDeviceMemMap(ScsiPeripheral_DeviceMemMap *devMmap);

/**
 * @brief 解析基本的sense data，包括Information、Command specific information、Sense key specific字段。
 *
 * @param senseData 待解析的sense data。
 * @param senseDataLen sense data长度。
 * @param senseInfo 用于保存解析后的基本信息，详情参见{@link ScsiPeripheral_BasicSenseInfo}。
 * @return {@link SCSIPERIPHERAL_DDK_SUCCESS} 调用接口成功。
 *     {@link SCSIPERIPHERAL_DDK_INVALID_PARAMETER} senseData格式不是描述符或固定格式、
 *     senseDataLen小于{@link SCSIPERIPHERAL_MIN_DESCRIPTOR_FORMAT_SENSE}或者
 *     senseDataLen小于{@link SCSIPERIPHERAL_MIN_FIXED_FORMAT_SENSE}。
 * @since 18
 */
int32_t OH_ScsiPeripheral_ParseBasicSenseInfo(uint8_t *senseData, uint8_t senseDataLen,
    ScsiPeripheral_BasicSenseInfo *senseInfo);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // SCSI_PERIPHERAL_API_H
/** @} */
