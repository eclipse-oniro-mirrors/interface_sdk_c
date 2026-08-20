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
#ifndef HID_DDK_API_H
#define HID_DDK_API_H

/**
 * @addtogroup HidDdk
 * @{
 *
 * @brief 提供HID DDK接口，包括创建设备、发送事件、销毁设备等功能，用于HID设备的驱动开发。
 *
 * @syscap SystemCapability.Driver.HID.Extension
 * @since 11
 * @version 1.0
 */

/**
 * @file hid_ddk_api.h
 *
 * @brief 声明主机侧访问输入设备的HID DDK（Driver Development Kit，驱动开发工具包）接口。该模块提供了创建、打开、读写HID设备的能力，支持设备管理和事件注入，
 * 支持两种使用模式：一是虚拟HID设备的创建与事件注入，适用于模拟键盘、鼠标、触摸屏输入等场景；二是真实HID设备的访问与通信，支持打开、读写设备报告以及获取设备信息，适用于与HID设备进行数据交互的场景。
 *
 * @include <hid/hid_ddk_api.h>
 * @library libhid.z.so
 * @kit DriverDevelopmentKit
 * @syscap SystemCapability.Driver.HID.Extension
 * @since 11
 * @version 1.0
 */

#include <stdint.h>
#include "hid_ddk_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建设备。适用于需要模拟虚拟HID输入设备的场景，如模拟键盘、鼠标等输入设备进行自动化测试。必须与{@link OH_Hid_DestroyDevice}成对使用。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param hidDevice 创建设备需要的基本信息，包括设备名、厂商ID、产品ID等。
 * @param hidEventProperties 创建的设备关注的事件，包括事件类型、按键事件属性、绝对坐标事件属性、相对坐标事件属性等。
 * @return deviceID（一个非负整数）成功创建设备的ID。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_OPERATION} 连接HID DDK服务失败。可能原因：DDK服务未初始化。请调用OH_Hid_Init完成初始化。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能的原因：1. 入参hidDevice为空指针；
 *     2. 入参hidEventProperties为空指针；3. properties的长度超过7；4. hidEventTypes的长度超过5；
 *     5. hidKeys的长度超过100；6. hidAbs的长度超过26；7.hidRelBits的长度超过13；
 *     8. hidMiscellaneous的长度超过6。
 *     {@link HID_DDK_FAILURE} 设备数量达到最大值200。
 * @since 11
 * @version 1.0
 */
int32_t OH_Hid_CreateDevice(Hid_Device *hidDevice, Hid_EventProperties *hidEventProperties);

/**
 * @brief 向指定设备发送事件列表，事件通过{@link OH_Hid_CreateDevice}创建的虚拟设备注入到系统中，系统将其作为真实输入事件进行处理。适用于模拟用户输入事件的场景，如模拟按键、鼠标移动、
 * 点击等操作进行自动化测试或远程控制。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param deviceId 设备ID，必须是当前调用者通过{@link OH_Hid_CreateDevice}创建的设备，取值为非负数。
 * @param items 发送的事件列表，事件包括类型（取值来源事件类型Hid_EventType）、编码（取值来源同步事件编码Hid_SynEvent、键值编码Hid_KeyCode、
 * 绝对坐标编码Hid_AbsAxes、相对坐标编码Hid_RelAxes、其他类型的输入事件编码Hid_MscEvent）、值（根据实际设备输入决定）。
 * 发送的事件将被注入到指定设备，模拟设备产生相应的输入行为
 * @param length 发送事件列表长度（一次发送事件个数），取值范围为[1, 7]。
 * @return {@link HID_DDK_SUCCESS} 调用接口成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_OPERATION} 连接HID DDK服务失败或者调用方不是设备的创建者。请确保调用了OH_Hid_Init完成初始化，且调用方是设备的创建者。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能的原因：1.设备ID小于0；2.入参length长度超过7；3.入参items为空指针。请检查参数有效性。
 *     {@link HID_DDK_NULL_PTR} 对应设备的注入为空。请确保使用OH_Hid_CreateDevice返回的有效设备ID，且设备未被销毁。
 * @since 11
 * @version 1.0
 */
int32_t OH_Hid_EmitEvent(int32_t deviceId, const Hid_EmitItem items[], uint16_t length);

/**
 * @brief 销毁设备。适用于不再需要使用虚拟HID设备时，释放系统资源的场景。必须与{@link OH_Hid_CreateDevice}成对使用，只能销毁由当前调用者创建的设备。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param deviceId 设备ID，必须是当前调用者创建的设备，取值为非负数。
 * @return {@link HID_DDK_SUCCESS} 调用接口成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_OPERATION} 连接HID DDK服务失败或者调用方不是设备的创建者。请确保调用了OH_Hid_Init完成初始化，且调用方是设备的创建者。
 *     {@link HID_DDK_NULL_PTR} 设备不存在。请确保使用OH_Hid_CreateDevice返回的有效设备ID，且设备未被销毁。
 * @since 11
 * @version 1.0
 */
int32_t OH_Hid_DestroyDevice(int32_t deviceId);

/**
 * @brief 初始化HID DDK。必须在使用其他所有HID DDK方法之前调用此方法。不再使用任何HID DDK功能时，必须调用{@link OH_Hid_Release}释放资源。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INIT_ERROR} 初始化DDK失败。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 * @since 18
 */
int32_t OH_Hid_Init(void);

/**
 * @brief 释放HID DDK。必须与{@link OH_Hid_Init}成对使用。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 * @since 18
 */
int32_t OH_Hid_Release(void);

/**
 * @brief 打开deviceId和interfaceIndex指定的设备。适用于需要与特定HID设备进行通信的场景，在使用完毕后调用{@link OH_Hid_Close}释放设备资源。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param deviceId 操作设备的ID，可通过{@link OH_Usb_GetDevices}查询获取。
 * @param interfaceIndex 接口索引，对应HID设备的接口。
 * @param dev 设备操作句柄，输出参数。接口执行成功后会被赋值，表示打开的HID设备。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 *     {@link HID_DDK_MEMORY_ERROR} dev内存申请失败。
 *     {@link HID_DDK_IO_ERROR} I/O操作失败。可能原因：设备状态异常、数据传输错误等。请检查设备状态和参数。
 *     {@link HID_DDK_INVALID_PARAMETER} dev为空或*dev为空。
 *     {@link HID_DDK_DEVICE_NOT_FOUND} 根据deviceId和interfaceIndex找不到设备。
 * @since 18
 */
int32_t OH_Hid_Open(uint64_t deviceId, uint8_t interfaceIndex, Hid_DeviceHandle **dev);

/**
 * @brief 关闭设备。必须与{@link OH_Hid_Open}成对使用，适用于不再需要与HID设备通信时，释放设备资源的场景。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev 设备操作句柄，须通过{@link OH_Hid_Open}打开并获取，接口调用成功后会释放资源并置空。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 *     {@link HID_DDK_IO_ERROR} I/O操作失败。可能原因：设备状态异常、数据传输错误等。请检查设备状态和参数。
 *     {@link HID_DDK_INVALID_PARAMETER} dev为空或*dev为空。
 * @since 18
 */
int32_t OH_Hid_Close(Hid_DeviceHandle **dev);

/**
 * @brief 向设备写入HID报告。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev 设备操作句柄，使用前须通过{@link OH_Hid_Open}打开并获取。
 * @param data 待写入的数据。
 * @param length 写入数据的字节长度，大于0且最大不超过{@link HID_MAX_REPORT_BUFFER_SIZE}，否则无法通过参数校验。
 * @param bytesWritten 实际写入的数据字节数。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能原因：1. dev为空；
 *     2. data为空；3. length为0；4. length超过{@link HID_MAX_REPORT_BUFFER_SIZE}；
 *     5. bytesWritten为空。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 *     {@link HID_DDK_IO_ERROR} I/O操作失败。可能原因：设备状态异常、数据传输错误等。请检查设备状态和参数。
 * @since 18
 */
int32_t OH_Hid_Write(Hid_DeviceHandle *dev, uint8_t *data, uint32_t length, uint32_t *bytesWritten);

/**
 * @brief 在指定的超时时间内从设备读取报告。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev 设备操作句柄，使用前须通过{@link OH_Hid_Open}打开并获取。
 * @param data 存放读取数据的缓冲区。
 * @param bufSize 存放读取数据的缓冲区大小，大于0且最大不超过{@link HID_MAX_REPORT_BUFFER_SIZE}，否则无法通过参数校验。
 * @param timeout 超时时间（毫秒），取值说明：大于0时，表示阻塞等待的毫秒数；等于0时表示立即返回；设置为-1时表示阻塞等待直至读出数据，不会返回超时。
 * @param bytesRead 读取的字节数。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能原因：1. dev为空；
 *     2. data为空；3. bufSize为0；4. bufSize超过{@link HID_MAX_REPORT_BUFFER_SIZE}；
 *     5. bytesRead为空。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 *     {@link HID_DDK_MEMORY_ERROR} 内存数据拷贝失败。
 *     {@link HID_DDK_IO_ERROR} I/O操作失败。可能原因：设备状态异常、数据传输错误等。请检查设备状态和参数。
 *     {@link HID_DDK_TIMEOUT} 读取超时。
 * @since 18
 */
int32_t OH_Hid_ReadTimeout(Hid_DeviceHandle *dev, uint8_t *data, uint32_t bufSize, int timeout, uint32_t *bytesRead);

/**
 * @brief 从设备读取报告，默认为阻塞模式（阻塞等待直到有数据可读取），可以调用{@link OH_Hid_SetNonBlocking}改变模式。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev 设备操作句柄，使用前须通过{@link OH_Hid_Open}打开并获取。
 * @param data 存放读取数据的缓冲区。
 * @param bufSize 存放读取数据的缓冲区大小，大于0且最大不超过{@link HID_MAX_REPORT_BUFFER_SIZE}，否则无法通过参数校验。
 * @param bytesRead 读取的字节数。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能原因：1. dev为空；
 *     2. data为空；3. bufSize为0；4. bufSize超过{@link HID_MAX_REPORT_BUFFER_SIZE}；
 *     5. bytesRead为空。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 *     {@link HID_DDK_MEMORY_ERROR} 内存数据拷贝失败。
 *     {@link HID_DDK_IO_ERROR} I/O操作失败。可能原因：设备状态异常、数据传输错误等。请检查设备状态和参数。
 *     {@link HID_DDK_TIMEOUT} 读取超时。
 * @since 18
 */
int32_t OH_Hid_Read(Hid_DeviceHandle *dev, uint8_t *data, uint32_t bufSize, uint32_t *bytesRead);

/**
 * @brief 设置设备读取模式为非阻塞。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev 设备操作句柄，使用前须通过{@link OH_Hid_Open}打开并获取。
 * @param nonBlock 是否启用非阻塞模式读取数据。1：启用非阻塞模式，调用{@link OH_Hid_Read}接口时，如果设备有可读的数据，读取并返回{@link HID_DDK_SUCCESS}，
 *     如果设备没有数据可读，则返回{@link HID_DDK_TIMEOUT}。0：禁用非阻塞模式，启用阻塞模式。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能原因：1. dev为空；
 *     2. nonBlock不是1或0。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 * @since 18
 */
int32_t OH_Hid_SetNonBlocking(Hid_DeviceHandle *dev, int nonBlock);

/**
 * @brief 获取设备原始信息。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev 设备操作句柄，使用前须通过{@link OH_Hid_Open}打开并获取。
 * @param rawDevInfo 设备原始信息，包含厂商ID、产品ID和总线类型。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能原因：1. dev为空；
 *     2. rawDevInfo为空。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 *     {@link HID_DDK_IO_ERROR} I/O操作失败。可能原因：设备状态异常、数据传输错误等。请检查设备状态和参数。
 *     {@link HID_DDK_INVALID_OPERATION} 不支持此操作。
 * @since 18
 */
int32_t OH_Hid_GetRawInfo(Hid_DeviceHandle *dev, Hid_RawDevInfo *rawDevInfo);

/**
 * @brief 获取设备原始名称。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev 设备操作句柄，使用前须通过{@link OH_Hid_Open}打开并获取。
 * @param data 存放读取数据的缓冲区。
 * @param bufSize 存放读取数据的缓冲区大小，大于0且最大不超过{@link HID_MAX_REPORT_BUFFER_SIZE}，否则无法通过参数校验。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能原因：1. dev为空；
 *     2. data为空；3. bufSize为0；4. bufSize超过{@link HID_MAX_REPORT_BUFFER_SIZE}。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 *     {@link HID_DDK_MEMORY_ERROR} 内存数据拷贝失败。
 *     {@link HID_DDK_IO_ERROR} I/O操作失败。可能原因：设备状态异常、数据传输错误等。请检查设备状态和参数。
 *     {@link HID_DDK_INVALID_OPERATION} 不支持此操作。
 * @since 18
 */
int32_t OH_Hid_GetRawName(Hid_DeviceHandle *dev, char *data, uint32_t bufSize);

/**
 * @brief 获取设备物理地址。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev 设备操作句柄，使用前须通过{@link OH_Hid_Open}打开并获取。
 * @param data 存放读取数据的缓冲区。
 * @param bufSize 存放读取数据的缓冲区大小，大于0且最大不超过{@link HID_MAX_REPORT_BUFFER_SIZE}，否则无法通过参数校验。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能原因：1. dev为空；
 *     2. data为空；3. bufSize为0；4. bufSize超过{@link HID_MAX_REPORT_BUFFER_SIZE}。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 *     {@link HID_DDK_MEMORY_ERROR} 内存数据拷贝失败。
 *     {@link HID_DDK_IO_ERROR} I/O操作失败。可能原因：设备状态异常、数据传输错误等。请检查设备状态和参数。
 *     {@link HID_DDK_INVALID_OPERATION} 不支持此操作。
 * @since 18
 */
int32_t OH_Hid_GetPhysicalAddress(Hid_DeviceHandle *dev, char *data, uint32_t bufSize);

/**
 * @brief 获取设备原始唯一标识符。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev 设备操作句柄，使用前须通过{@link OH_Hid_Open}打开并获取。
 * @param data 存放读取数据的缓冲区。
 * @param bufSize 存放读取数据的缓冲区大小，大于0且最大不超过{@link HID_MAX_REPORT_BUFFER_SIZE}，否则无法通过参数校验。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能原因：1. dev为空；
 *     2. data为空；3. bufSize为0；4. bufSize超过{@link HID_MAX_REPORT_BUFFER_SIZE}。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 *     {@link HID_DDK_MEMORY_ERROR} 内存数据拷贝失败。
 *     {@link HID_DDK_IO_ERROR} I/O操作失败。可能原因：设备状态异常、数据传输错误等。请检查设备状态和参数。
 *     {@link HID_DDK_INVALID_OPERATION} 不支持此操作。
 * @since 18
 */
int32_t OH_Hid_GetRawUniqueId(Hid_DeviceHandle *dev, uint8_t *data, uint32_t bufSize);

/**
 * @brief 向设备发送指定类型的HID报告。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev 设备操作句柄，使用前须通过{@link OH_Hid_Open}打开并获取。
 * @param reportType 报告类型，可指定为输入报告、输出报告或特性报告。
 * @param data 待发送的数据。
 * @param length 发送数据的字节长度，大于0且最大不超过 {@link HID_MAX_REPORT_BUFFER_SIZE}，否则无法通过参数校验。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能原因：1. dev为空；
 *     2. data为空；3. length为0；4. length超过{@link HID_MAX_REPORT_BUFFER_SIZE}。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 *     {@link HID_DDK_IO_ERROR} I/O操作失败。可能原因：设备状态异常、数据传输错误等。请检查设备状态和参数。
 *     {@link HID_DDK_INVALID_OPERATION} 不支持此操作。
 * @since 18
 */
int32_t OH_Hid_SendReport(Hid_DeviceHandle *dev, Hid_ReportType reportType, const uint8_t *data, uint32_t length);

/**
 * @brief 从设备获取指定类型的HID报告。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev 设备操作句柄，使用前须通过{@link OH_Hid_Open}打开并获取。
 * @param reportType 报告类型。
 * @param data 存放读取数据的缓冲区。
 * @param bufSize 存放读取数据的缓冲区大小，大于0且最大不超过{@link HID_MAX_REPORT_BUFFER_SIZE}，否则无法通过参数校验。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能原因：1. dev为空；
 *     2. data为空；3. bufSize为0；4. bufSize超过{@link HID_MAX_REPORT_BUFFER_SIZE}。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 *     {@link HID_DDK_MEMORY_ERROR} 内存数据拷贝失败。
 *     {@link HID_DDK_IO_ERROR} I/O操作失败。可能原因：设备状态异常、数据传输错误等。请检查设备状态和参数。
 *     {@link HID_DDK_INVALID_OPERATION} 不支持此操作。
 * @since 18
 */
int32_t OH_Hid_GetReport(Hid_DeviceHandle *dev, Hid_ReportType reportType, uint8_t *data, uint32_t bufSize);

/**
 * @brief 获取设备报告描述符。
 *
 * @permission ohos.permission.ACCESS_DDK_HID
 * @param dev 设备操作句柄，使用前须通过{@link OH_Hid_Open}打开并获取。
 * @param buf 存放描述符的缓冲区。
 * @param bufSize 缓冲区的字节大小，大于0且最大不超过{@link HID_MAX_REPORT_BUFFER_SIZE}，否则无法通过参数校验。
 * @param bytesRead 读取的字节数。
 * @return {@link HID_DDK_SUCCESS} 操作成功。
 *     {@link HID_DDK_NO_PERM} 权限校验失败。请确保应用已声明ohos.permission.ACCESS_DDK_HID权限。
 *     {@link HID_DDK_INVALID_PARAMETER} 参数校验失败。可能原因：1. dev为空；
 *     2. buf为空；3. bufSize为0；4. bufSize超过{@link HID_MAX_REPORT_BUFFER_SIZE}；
 *     5. bytesRead为空。
 *     {@link HID_DDK_INIT_ERROR} DDK未初始化，请确保已调用{@link OH_Hid_Init}完成初始化。
 *     {@link HID_DDK_SERVICE_ERROR} 与DDK服务通信失败。可能原因：服务内部错误。请检查当前操作和设备状态。
 *     {@link HID_DDK_MEMORY_ERROR} 内存数据拷贝失败。
 *     {@link HID_DDK_IO_ERROR} I/O操作失败。可能原因：设备状态异常、数据传输错误等。请检查设备状态和参数。
 *     {@link HID_DDK_INVALID_OPERATION} 不支持此操作。
 * @since 18
 */
int32_t OH_Hid_GetReportDescriptor(Hid_DeviceHandle *dev, uint8_t *buf, uint32_t bufSize, uint32_t *bytesRead);

#ifdef __cplusplus
}
#endif

#endif // HID_DDK_API_H
/** @} */
