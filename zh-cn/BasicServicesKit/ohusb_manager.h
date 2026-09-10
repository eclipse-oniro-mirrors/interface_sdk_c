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
 * @addtogroup UsbManager
 * @{
 *
 * @brief Provides the C interface for the USB Manager module, enabling USB device
 * enumeration, connection, permission management, and pipe operations.
 *
 * @since 26.1.0
 */

/**
 * @file ohusb_manager.h
 *
 * @brief Declares the C APIs for USB device management.
 *
 * @library libohusb_manager.so
 * @kit BasicServicesKit
 * @syscap SystemCapability.USB.USBManager
 * @since 26.1.0
 */

#ifndef OHUSB_MANAGER_H
#define OHUSB_MANAGER_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 枚举USB管理器的错误码。
 *
 * @since 26.1.0
 */
typedef enum OH_UsbManager_ErrorCode {
    /**
     * 操作成功。
     *
     * @since 26.1.0
     */
    OH_USBMANAGER_SUCCESS = 0,

    /**
     * 权限被拒绝。
     *
     * @since 26.1.0
     */
    OH_USBMANAGER_ERROR_PERMISSION_DENIED = 14400001,

    /**
     * 服务异常。
     *
     * @since 26.1.0
     */
    OH_USBMANAGER_ERROR_SERVICE_EXCEPTION = 14400004,

    /**
     * 不存在该设备（可能已被断开连接）。
     *
     * @since 26.1.0
     */
    OH_USBMANAGER_ERROR_NO_DEVICE = 14400008,

    /**
     * 内存不足。
     *
     * @since 26.1.0
     */
    OH_USBMANAGER_ERROR_NO_MEMORY = 14400009,

    /**
     * 传输I/O错误。
     *
     * @since 26.1.0
     */
    OH_USBMANAGER_ERROR_IO_ERROR = 14400012,

    /**
     * 无效参数。对不可为空的参数传入了空指针。
     *
     * @since 26.1.0
     */
    OH_USBMANAGER_ERROR_INVALID_PARAMETER = 14400014
} OH_UsbManager_ErrorCode;

/**
 * @brief 枚举USB请求方向。
 *
 * @since 26.1.0
 */
typedef enum OH_UsbManager_RequestDirection {
    /**
     * 用于从主机向设备写入数据的请求。
     *
     * @since 26.1.0
     */
    OH_USBMANAGER_REQUEST_DIR_TO_DEVICE = 0,

    /**
     * 用于从设备向主机读取数据的请求。
     *
     * @since 26.1.0
     */
    OH_USBMANAGER_REQUEST_DIR_FROM_DEVICE = 0x80
} OH_UsbManager_RequestDirection;

/**
 * @brief 定义用于发送或接收数据的USB端点。端点从{@link OH_UsbManager_UsbInterface}获取。
 *
 * @since 26.1.0
 */
typedef struct OH_UsbManager_UsbEndpoint {
    /**
     * 端点地址。
     *
     * @since 26.1.0
     */
    uint8_t address;

    /**
     * 端点属性。
     *
     * @since 26.1.0
     */
    uint8_t attributes;

    /**
     * 端点数据传输间隔。对于中断端点，单位为毫秒。对于等时端点，
     * 单位取决于设备速度。
     *
     * @since 26.1.0
     */
    uint8_t interval;

    /**
     * 端点上数据包的最大大小。单位：字节。
     *
     * @since 26.1.0
     */
    uint16_t maxPacketSize;

    /**
     * 端点方向。
     *
     * @since 26.1.0
     */
    OH_UsbManager_RequestDirection direction;

    /**
     * 端点号。
     *
     * @since 26.1.0
     */
    uint8_t number;

    /**
     * 端点类型。
     *
     * @since 26.1.0
     */
    uint8_t type;

    /**
     * 端点所属接口的唯一标识。
     *
     * @since 26.1.0
     */
    uint8_t interfaceId;
} OH_UsbManager_UsbEndpoint;

/**
 * @brief 定义USB接口。一个{@link OH_UsbManager_UsbConfig}可以包含多个
 * OH_UsbManager_UsbInterface实例，每个实例提供特定功能。
 *
 * @since 26.1.0
 */
typedef struct OH_UsbManager_UsbInterface {
    /**
     * USB接口的唯一标识。
     *
     * @since 26.1.0
     */
    uint8_t id;

    /**
     * 接口协议。
     *
     * @since 26.1.0
     */
    uint8_t protocol;

    /**
     * 接口类。
     *
     * @since 26.1.0
     */
    uint8_t clazz;

    /**
     * 接口子类。
     *
     * @since 26.1.0
     */
    uint8_t subClass;

    /**
     * 此USB接口的交替设置编号，由USB接口描述符定义。值0表示
     * 默认的交替设置。
     *
     * @since 26.1.0
     */
    uint8_t alternateSetting;

    /**
     * 接口名称。
     *
     * @since 26.1.0
     */
    const char *name;

    /**
     * 属于该USB接口的端点。
     *
     * @since 26.1.0
     */
    OH_UsbManager_UsbEndpoint *endpoints;

    /**
     * 接口中的端点数量。
     *
     * @since 26.1.0
     */
    uint32_t endpointCount;
} OH_UsbManager_UsbInterface;

/**
 * @brief 定义USB配置。一个{@link OH_UsbManager_UsbDevice}可以包含多个
 * OH_UsbManager_UsbConfig实例。
 *
 * @since 26.1.0
 */
typedef struct OH_UsbManager_UsbConfig {
    /**
     * USB配置的唯一标识。
     *
     * @since 26.1.0
     */
    uint8_t id;

    /**
     * 配置属性。
     *
     * @since 26.1.0
     */
    uint8_t attributes;

    /**
     * 最大功耗。单位：mA。
     *
     * @since 26.1.0
     */
    uint8_t maxPower;

    /**
     * 配置名称，可以为空。
     *
     * @since 26.1.0
     */
    const char *name;

    /**
     * 是否支持远程唤醒。true表示支持远程唤醒；false表示不支持。
     *
     * @since 26.1.0
     */
    bool isRemoteWakeup;

    /**
     * 是否支持独立供电。true表示支持独立供电；false表示不支持。
     *
     * @since 26.1.0
     */
    bool isSelfPowered;

    /**
     * 支持的接口属性。
     *
     * @since 26.1.0
     */
    OH_UsbManager_UsbInterface *interfaces;

    /**
     * 配置中的接口数量。
     *
     * @since 26.1.0
     */
    uint32_t interfaceCount;
} OH_UsbManager_UsbConfig;

/**
 * @brief 定义USB设备的扁平化表示。
 *
 * @since 26.1.0
 */
typedef struct OH_UsbManager_UsbDevice {
    /**
     * USB设备的总线编号。
     *
     * @since 26.1.0
     */
    uint8_t busNum;

    /**
     * 设备在总线上的地址。
     *
     * @since 26.1.0
     */
    uint8_t devAddress;

    /**
     * 设备名称，格式为<总线编号>-<设备地址>。
     *
     * @since 26.1.0
     */
    const char *name;

    /**
     * 制造商名称。
     *
     * @since 26.1.0
     */
    const char *manufacturerName;

    /**
     * 产品名称。
     *
     * @since 26.1.0
     */
    const char *productName;

    /**
     * 设备版本。
     *
     * @since 26.1.0
     */
    const char *version;

    /**
     * 厂商ID。
     *
     * @since 26.1.0
     */
    uint16_t vendorId;

    /**
     * 产品ID。
     *
     * @since 26.1.0
     */
    uint16_t productId;

    /**
     * 设备类。
     *
     * @since 26.1.0
     */
    uint8_t clazz;

    /**
     * 设备子类。
     *
     * @since 26.1.0
     */
    uint8_t subClass;

    /**
     * 设备协议。
     *
     * @since 26.1.0
     */
    uint8_t protocol;

    /**
     * 设备配置描述符信息。
     *
     * @since 26.1.0
     */
    OH_UsbManager_UsbConfig *configs;

    /**
     * 设备中的配置数量。
     *
     * @since 26.1.0
     */
    uint32_t configCount;
} OH_UsbManager_UsbDevice;

/**
 * @brief 定义用于与已打开设备通信的USB设备管道。
 *
 * @since 26.1.0
 */
typedef struct OH_UsbManager_UsbPipe {
    /**
     * 所连接设备的总线编号。
     *
     * @since 26.1.0
     */
    uint8_t busNum;

    /**
     * 所连接设备的设备地址。
     *
     * @since 26.1.0
     */
    uint8_t devAddress;
} OH_UsbManager_UsbPipe;

/**
 * @brief 获取所有已连接USB设备的列表。调用者必须调用{@link OH_UsbManager_FreeUsbDeviceList}
 * 释放返回的数组。
 *
 * @param devices [out] 指向{@link OH_UsbManager_UsbDevice}数组的二级指针。成功时，
 *     函数会分配该数组及所有内部字符串缓冲区。调用者不得单独释放各个字段；
 *     请改用{@link OH_UsbManager_FreeUsbDeviceList}。不得为空。
 * @param deviceCount [out] 指向返回设备数量的指针。成功时，该值被设置为数组中的
 *     元素个数。为0表示当前没有设备。不得为空。
 * @return {@link OH_USBMANAGER_SUCCESS} 表示操作成功。
 *     <br>{@link OH_USBMANAGER_ERROR_SERVICE_EXCEPTION} 表示USB服务不可用。可能原因：USB服务故障，例如服务未运行或意外停止。
 *     <br>{@link OH_USBMANAGER_ERROR_NO_MEMORY} 表示设备数组或字符串的内存分配失败。可能原因：系统内存不足或连接的设备过多。处理建议：释放未使用的内存后重试。
 *     <br>{@link OH_USBMANAGER_ERROR_INVALID_PARAMETER} 表示devices或deviceCount为NULL。可能原因：未提供必需的参数。处理建议：传入有效的非空指针。
 * @release OH_UsbManager_FreeUsbDeviceList {devices}
 * @since 26.1.0
 */
OH_UsbManager_ErrorCode OH_UsbManager_GetUsbDeviceList(OH_UsbManager_UsbDevice **devices,
    uint32_t *deviceCount);

/**
 * @brief 释放之前由{@link OH_UsbManager_GetUsbDeviceList}返回的设备数组。
 *
 * 调用后该指针失效，不得再使用。传入null或数量为0是安全的空操作。
 *
 * @param devices [in] 指向由{@link OH_UsbManager_GetUsbDeviceList}返回的数组的指针。
 * @param deviceCount [in] 数组中的元素个数，由{@link OH_UsbManager_GetUsbDeviceList}
 *     返回。
 * @since 26.1.0
 */
void OH_UsbManager_FreeUsbDeviceList(OH_UsbManager_UsbDevice *devices, uint32_t deviceCount);

/**
 * @brief 连接USB设备并打开用于通信的管道。返回的管道必须通过调用
 * {@link OH_UsbManager_ClosePipe}关闭，以避免资源泄漏。
 *
 * 仅需要设备结构体中的busNum和devAddress字段；其他字段将被忽略。
 *
 * @param device [in] 指向要连接的{@link OH_UsbManager_UsbDevice}的指针。不得为空。
 * @param pipe [out] 指向{@link OH_UsbManager_UsbPipe}的指针，成功时用于接收
 *     句柄。不得为空。
 * @return {@link OH_USBMANAGER_SUCCESS} 表示连接成功。
 *     <br>{@link OH_USBMANAGER_ERROR_PERMISSION_DENIED} 表示应用缺少设备访问权限。
 *     可能原因：尚未请求访问权限、权限已被撤销，或用户拒绝了请求。
 *     处理建议：调用{@link OH_UsbManager_RequestPermission}请求访问权限。
 *     <br>{@link OH_USBMANAGER_ERROR_SERVICE_EXCEPTION} 表示USB服务打开设备失败。
 *     可能原因：USB服务故障（例如服务未运行或意外停止），或传入的device无效。
 *     处理建议：如果device无效，请先通过{@link OH_UsbManager_GetUsbDeviceList}
 *     获取有效的设备数据后重试。
 *     <br>{@link OH_USBMANAGER_ERROR_IO_ERROR} 表示无法打开设备（如已断开连接或发生I/O失败）。
 *     可能原因：设备已断开连接或USB总线发生I/O错误。
 *     处理建议：检查物理连接和设备状态后重试。
 *     <br>{@link OH_USBMANAGER_ERROR_INVALID_PARAMETER} 表示device或pipe为NULL。
 *     可能原因：未提供必需的参数。处理建议：传入有效的非空指针。
 * @since 26.1.0
 */
OH_UsbManager_ErrorCode OH_UsbManager_ConnectDevice(const OH_UsbManager_UsbDevice *device,
    OH_UsbManager_UsbPipe *pipe);

/**
 * @brief 检查应用是否有权限访问指定设备。
 *
 * @param deviceName [in] 设备名称，格式为<总线编号>-<设备地址>。不得为空。
 * @param result [out] 用于接收结果的指针。如果应用已被授予访问设备的权限
 *     则为true；如果权限未被授予或未被请求则为false。不得为空。
 * @return {@link OH_USBMANAGER_SUCCESS} 表示操作成功。
 *     <br>{@link OH_USBMANAGER_ERROR_SERVICE_EXCEPTION} 表示USB服务不可用。
 *     可能原因：USB服务故障（例如服务未运行或意外停止），或传入的deviceName无效。
 *     处理建议：如果deviceName无效，请先通过{@link OH_UsbManager_GetUsbDeviceList}
 *     获取有效的设备名称后重试。
 *     <br>{@link OH_USBMANAGER_ERROR_INVALID_PARAMETER} 表示deviceName或result为NULL。
 *     可能原因：未提供必需的参数。处理建议：传入有效的非空指针。
 * @since 26.1.0
 */
OH_UsbManager_ErrorCode OH_UsbManager_HasPermission(const char *deviceName, bool *result);

/**
 * @brief 定义用于返回{@link OH_UsbManager_RequestPermission}结果的
 * 回调类型。
 *
 * @param errorCode [out] 请求的错误码。{@link OH_USBMANAGER_SUCCESS}表示请求
 *     正常完成；其他值表示服务异常。
 * @param result [out] 如果权限被授予则为true；如果用户拒绝请求则为false。
 *     该参数仅在errorCode为{@link OH_USBMANAGER_SUCCESS}时有意义。
 * @param userContext [out] 从{@link OH_UsbManager_RequestPermission}透传的用户上下文。
 * @since 26.1.0
 */
typedef void (*OH_UsbManager_PermissionCallback)(OH_UsbManager_ErrorCode errorCode, bool result,
    void *userContext);

/**
 * @brief 异步请求访问指定USB设备的权限。这可能触发系统弹窗询问用户是否授权。
 * 函数立即返回，结果通过回调传递。
 *
 * @param deviceName [in] 设备名称，格式为<总线编号>-<设备地址>。不得为空。
 * @param callback [in] 请求完成时调用的{@link OH_UsbManager_PermissionCallback}。
 *     不得为空。
 * @param userContext [in] 传递给回调的用户上下文指针。可以为空。
 * @return {@link OH_USBMANAGER_SUCCESS} 表示请求成功发起。
 *     <br>{@link OH_USBMANAGER_ERROR_SERVICE_EXCEPTION} 表示服务启动请求失败。
 *     可能原因：USB服务故障（例如服务未运行或意外停止），或传入的deviceName无效。
 *     处理建议：如果deviceName无效，请先通过{@link OH_UsbManager_GetUsbDeviceList}
 *     获取有效的设备名称后重试。
 *     <br>{@link OH_USBMANAGER_ERROR_INVALID_PARAMETER} 表示deviceName或callback为NULL。
 *     可能原因：未提供必需的参数。处理建议：传入有效的非空指针。
 * @since 26.1.0
 */
OH_UsbManager_ErrorCode OH_UsbManager_RequestPermission(const char *deviceName,
    OH_UsbManager_PermissionCallback callback, void *userContext);

/**
 * @brief 获取已打开USB设备管道的文件描述符。该fd可用于基于ioctl的
 * 低层USB传输。
 *
 * @param pipe [in] 指向从{@link OH_UsbManager_ConnectDevice}获取的
 *     {@link OH_UsbManager_UsbPipe}的指针。不得为空。
 * @param fd [out] 用于在成功时接收文件描述符的指针。不得为空。
 * @return {@link OH_USBMANAGER_SUCCESS} 表示操作成功。
 *     <br>{@link OH_USBMANAGER_ERROR_PERMISSION_DENIED} 表示应用缺少设备访问权限。
 *     可能原因：尚未请求访问权限、权限已被撤销，或用户拒绝了请求。
 *     处理建议：调用{@link OH_UsbManager_RequestPermission}请求访问权限。
 *     <br>{@link OH_USBMANAGER_ERROR_SERVICE_EXCEPTION} 表示管道无效或服务失败。
 *     可能原因：USB服务故障，或管道并非通过{@link OH_UsbManager_ConnectDevice}获取、
 *     或管道已被关闭。处理建议：如果管道无效或已关闭，请通过
 *     {@link OH_UsbManager_ConnectDevice}获取有效的打开管道后重试。
 *     <br>{@link OH_USBMANAGER_ERROR_NO_DEVICE} 表示设备不存在或已断开连接。
 *     可能原因：设备已被拔出。处理建议：使用{@link OH_UsbManager_GetUsbDeviceList}
 *     重新枚举设备并重新连接。
 *     <br>{@link OH_USBMANAGER_ERROR_INVALID_PARAMETER} 表示pipe或fd为NULL。
 *     可能原因：未提供必需的参数。处理建议：传入有效的非空指针。
 * @since 26.1.0
 */
OH_UsbManager_ErrorCode OH_UsbManager_GetFileDescriptor(const OH_UsbManager_UsbPipe *pipe,
    int32_t *fd);

/**
 * @brief 关闭USB设备管道并释放底层资源。该管道必须从{@link OH_UsbManager_ConnectDevice}
 * 获取。
 *
 * @param pipe [in] 指向要关闭的、从{@link OH_UsbManager_ConnectDevice}获取的
 *     {@link OH_UsbManager_UsbPipe}的指针。不得为空。
 * @return {@link OH_USBMANAGER_SUCCESS} 表示管道关闭成功。
 *     <br>{@link OH_USBMANAGER_ERROR_PERMISSION_DENIED} 表示应用缺少设备访问权限。
 *     可能原因：尚未请求访问权限、权限已被撤销，或用户拒绝了请求。
 *     处理建议：调用{@link OH_UsbManager_RequestPermission}请求访问权限。
 *     <br>{@link OH_USBMANAGER_ERROR_SERVICE_EXCEPTION} 表示关闭操作失败。
 *     可能原因：USB服务故障，或管道无效或已被关闭。处理建议：如果管道无效或已关闭，
 *     请通过{@link OH_UsbManager_ConnectDevice}获取有效的打开管道后重试。
 *     <br>{@link OH_USBMANAGER_ERROR_INVALID_PARAMETER} 表示pipe为NULL。
 *     可能原因：未提供必需的参数。处理建议：传入有效的非空指针。
 * @since 26.1.0
 */
OH_UsbManager_ErrorCode OH_UsbManager_ClosePipe(const OH_UsbManager_UsbPipe *pipe);

#ifdef __cplusplus
}
#endif

#endif  // OHUSB_MANAGER_H

/** @} */