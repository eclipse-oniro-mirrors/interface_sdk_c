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
 * @brief Provides ScsiPeripheral DDK types and declares macros, enumerations, and data structures used by the
 * ScsiPeripheral DDK.
 * @since 18
 */

/**
 * @file scsi_peripheral_types.h
 *
 * @brief 提供在SCSI Peripheral DDK（驱动开发工具包）API中使用的枚举变量、结构体和宏。
 *
 * @kit DriverDevelopmentKit
 * @library libscsi.z.so
 * @syscap SystemCapability.Driver.SCSI.Extension
 * @since 18
 */

#ifndef SCSI_PERIPHERAL_TYPES_H
#define SCSI_PERIPHERAL_TYPES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief 描述符格式感应数据的最小长度。
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MIN_DESCRIPTOR_FORMAT_SENSE 8

/**
 * @brief 固定格式感应数据的最小长度。
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MIN_FIXED_FORMAT_SENSE 18

/**
 * @brief SCSI Peripheral DDK错误码。
 *
 * @since 18
 */
typedef enum {
    /**
     * 没有权限。
     */
    SCSIPERIPHERAL_DDK_NO_PERM = 201,
    /**
     * 非法参数。
     */
    SCSIPERIPHERAL_DDK_INVALID_PARAMETER = 401,
    /**
     * 操作成功。
     */
    SCSIPERIPHERAL_DDK_SUCCESS = 31700000,
    /**
     * 与内存相关的错误，例如，内存不足、内存数据复制失败或内存申请失败。
     */
    SCSIPERIPHERAL_DDK_MEMORY_ERROR = 31700001,
    /**
     * 非法操作。
     */
    SCSIPERIPHERAL_DDK_INVALID_OPERATION = 31700002,
    /**
     * 设备输入/输出操作失败。
     */
    SCSIPERIPHERAL_DDK_IO_ERROR = 31700003,
    /**
     * 传输超时。
     */
    SCSIPERIPHERAL_DDK_TIMEOUT = 31700004,
    /**
     * DDK初始化错误，或者DDK未初始化。
     */
    SCSIPERIPHERAL_DDK_INIT_ERROR = 31700005,
    /**
     * 与SCSI Peripheral DDK服务的通信失败。
     */
    SCSIPERIPHERAL_DDK_SERVICE_ERROR = 31700006,
    /**
     * 设备未找到。
     */
    SCSIPERIPHERAL_DDK_DEVICE_NOT_FOUND = 31700007,
} ScsiPeripheral_DdkErrCode;

/**
 * @brief 定义用于响应的SCSI状态。
 *
 * @since 18
 */
typedef enum {
    /**
     * 正常状态。
     */
    SCSIPERIPHERAL_STATUS_GOOD = 0x00,
    /**
     * 需要状态检查。
     */
    SCSIPERIPHERAL_STATUS_CHECK_CONDITION_NEEDED = 0x02,
    /**
     * 条件满足。
     */
    SCSIPERIPHERAL_STATUS_CONDITION_MET = 0x04,
    /**
     * 占用中。
     */
    SCSIPERIPHERAL_STATUS_BUSY = 0x08,
    /**
     * 资源保留冲突。
     */
    SCSIPERIPHERAL_STATUS_RESERVATION_CONFLICT = 0x18,
    /**
     * 任务集已满。
     */
    SCSIPERIPHERAL_STATUS_TASK_SET_FULL = 0x28,
    /**
     * ACA活动状态。
     */
    SCSIPERIPHERAL_STATUS_ACA_ACTIVE = 0x30,
    /**
     * 任务已终止。
     */
    SCSIPERIPHERAL_STATUS_TASK_ABORTED = 0x40,
} ScsiPeripheral_Status;

/**
 * @brief 不透明的SCSI设备结构体。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_Device ScsiPeripheral_Device;

/**
 * @brief 通过调用{@link OH_ScsiPeripheral_CreateDeviceMemMap}创建的设备内存映射。使用该设备内存映射的缓冲区可以提供更好的性能。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_DeviceMemMap {
    /**
     * 缓冲区地址。
     */
    uint8_t * const address;
    /**
     * 缓冲区大小。
     */
    const size_t size;
    /**
     * 已使用缓冲区的偏移量。默认值为0，表示没有偏移，缓冲区从指定地址开始。
     */
    uint32_t offset;
    /**
     * 已使用缓冲区的长度。默认情况下，该值等于缓冲区的大小，表示整个缓冲区都被使用。
     */
    uint32_t bufferLength;
    /**
     * 已传输数据的长度。
     */
    uint32_t transferredLength;
} ScsiPeripheral_DeviceMemMap;

/**
 * @brief 读/写操作的请求参数。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_IORequest {
    /**
     * 逻辑块起始地址。
     */
    uint32_t lbAddress;
    /**
     * 需要操作的连续逻辑块的数量。
     */
    uint16_t transferLength;
    /**
     * Control字段，用于指定一些控制信息。
     */
    uint8_t control;
    /**
     * CDB的第一个字节。
     */
    uint8_t byte1;
    /**
     * CDB的第六个字节。
     */
    uint8_t byte6;
    /**
     * 数据传输的缓冲区。
     */
    ScsiPeripheral_DeviceMemMap *data;
    /**
     * 超时时间（单位：毫秒）。
     */
    uint32_t timeout;
} ScsiPeripheral_IORequest;

/**
 * @brief 命令描述块的最大长度。
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MAX_CMD_DESC_BLOCK_LEN 16

/**
 * @brief 请求参数结构体。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_Request {
    /**
     * 命令描述符块。
     */
    uint8_t commandDescriptorBlock[SCSIPERIPHERAL_MAX_CMD_DESC_BLOCK_LEN];
    /**
     * 命令描述符块的长度。
     */
    uint8_t cdbLength;
    /**
     * 数据传输方向：-1为无数据传输的命令，-2为从主机到设备的数据传输(写)，-3为从设备到主机的数据传输(读)，-4为双向数据传输。
     */
    int8_t dataTransferDirection;
    /**
     * 数据传输的缓冲区。
     */
    ScsiPeripheral_DeviceMemMap *data;
    /**
     * 超时时间（单位：毫秒）。
     */
    uint32_t timeout;
} ScsiPeripheral_Request;

/**
 * @brief 感应数据的最大长度。
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MAX_SENSE_DATA_LEN 252

/**
 * @brief 响应参数结构体。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_Response {
    /**
     * sense data（SCSI设备返回给主机的信息，用于报告设备的状态、错误信息以及诊断信息）。
     */
    uint8_t senseData[SCSIPERIPHERAL_MAX_SENSE_DATA_LEN];
    /**
     * 调用完成时的状态，例如良好（Good）、忙（Busy）。
     */
    ScsiPeripheral_Status status;
    /**
     * 在Linux的SCSI通用接口（SG）中，masked_status 字段用于存储经过处理后的SCSI状态，以便应用程序可以更方便地读取和解析。
     */
    uint8_t maskedStatus;
    /**
     * 消息状态。
     */
    uint8_t msgStatus;
    /**
     * 指的是实际写入到 Sense Buffer（感应缓冲区）的字节数。
     */
    uint8_t sbLenWr;
    /**
     * 主机适配器状态。 例如：成功(0x00)、无法连接(0x01)、总线忙(0x02)、超时(0x03)。
     */
    uint16_t hostStatus;
    /**
     * 驱动状态。 例如：成功（0x00）、设备或资源忙(0x01)。
     */
    uint16_t driverStatus;
    /**
     * 实际传输的数据长度差值，即未传输的字节数。
     */
    int32_t resId;
    /**
     * 执行命令消耗的时间 (单位：毫秒)。
     */
    uint32_t duration;
} ScsiPeripheral_Response;

/**
 * @brief 命令（test unit ready）的请求结构体。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_TestUnitReadyRequest {
    /**
     * Control字段，用于指定一些控制信息。
     */
    uint8_t control;
    /**
     * 超时时间（单位：毫秒）。
     */
    uint32_t timeout;
} ScsiPeripheral_TestUnitReadyRequest;

/**
 * @brief SCSI命令（inquiry）的请求结构体。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_InquiryRequest {
    /**
     * Page code字段。获取设备的某些特定类型的信息时使用。当发出带有特定页面代码的 Inquiry 命令时，设备会返回与该页面代码相关的详细信息。如果 page code 设置为 0x00，则表示请求的是标准的
     * Inquiry 数据，而非特定页面的数据。
     */
    uint8_t pageCode;
    /**
     * Allocation length字段，指定了请求方向发起者（通常是主机）为响应数据准备的缓冲区大小。
     */
    uint16_t allocationLength;
    /**
     * Control字段，用于指定一些控制信息。
     */
    uint8_t control;
    /**
     * CDB的第一个字节。
     */
    uint8_t byte1;
    /**
     * 超时时间（单位：毫秒）。
     */
    uint32_t timeout;
} ScsiPeripheral_InquiryRequest;

/**
 * @brief 厂商标识符的长度。
 *
 * @since 18
 */
#define SCSIPERIPHERAL_VENDOR_ID_LEN 8

/**
 * @brief 产品标识符的长度。
 *
 * @since 18
 */
#define SCSIPERIPHERAL_PRODUCT_ID_LEN 16

/**
 * @brief 产品修订版本号的长度。
 *
 * @since 18
 */
#define SCSIPERIPHERAL_PRODUCT_REV_LEN 4

/**
 * @brief SCSI inquiry 数据。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_InquiryInfo {
    /**
     * 设备类型。
     */
    uint8_t deviceType;
    /**
     * 制造商 id。
     */
    char idVendor[SCSIPERIPHERAL_VENDOR_ID_LEN + 1];
    /**
     * 产品 id。
     */
    char idProduct[SCSIPERIPHERAL_PRODUCT_ID_LEN + 1];
    /**
     * 产品版本。
     */
    char revProduct[SCSIPERIPHERAL_PRODUCT_REV_LEN + 1];
    /**
     * 所有的查询数据。
     */
    ScsiPeripheral_DeviceMemMap *data;
} ScsiPeripheral_InquiryInfo;

/**
 * @brief SCSI命令（read capacity）的请求结构体。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_ReadCapacityRequest {
    /**
     * 逻辑单元地址。
     */
    uint32_t lbAddress;
    /**
     * Control字段，用于指定一些控制信息。
     */
    uint8_t control;
    /**
     * CDB的第八个字节。
     */
    uint8_t byte8;
    /**
     * 超时时间（单位：毫秒）。
     */
    uint32_t timeout;
} ScsiPeripheral_ReadCapacityRequest;

/**
 * @brief SCSI read capacity 数据。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_CapacityInfo {
    /**
     * 返回的逻辑单元地址。
     */
    uint32_t lbAddress;
    /**
     * 单个逻辑单元长度，单位：字节。
     */
    uint32_t lbLength;
} ScsiPeripheral_CapacityInfo;

/**
 * @brief SCSI命令（Request Sense）的请求结构体。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_RequestSenseRequest {
    /**
     * Allocation length字段，指定了请求方向发起者（通常是主机）为响应数据准备的缓冲区大小。
     */
    uint8_t allocationLength;
    /**
     * Control字段，用于指定一些控制信息。
     */
    uint8_t control;
    /**
     * CDB的第一个字节。
     */
    uint8_t byte1;
    /**
     * 超时时间（单位：毫秒）。
     */
    uint32_t timeout;
} ScsiPeripheral_RequestSenseRequest;

/**
 * @brief sense data的基本信息。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_BasicSenseInfo {
    /**
     * 响应码。
     */
    uint8_t responseCode;
    /**
     * 信息有效标志位。
     */
    bool valid;
    /**
     * Information字段。
     */
    uint64_t information;
    /**
     * Command-specific information字段。
     */
    uint64_t commandSpecific;
    /**
     * Sense key specific字段的标志位。
     */
    bool sksv;
    /**
     * Sense key specific字段。
     */
    uint32_t senseKeySpecific;
} ScsiPeripheral_BasicSenseInfo;

/**
 * @brief SCSI命令（verify）的请求结构体。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_VerifyRequest {
    /**
     * 起始逻辑块地址。
     */
    uint32_t lbAddress;
    /**
     * 连续校验逻辑块的个数。
     */
    uint16_t verificationLength;
    /**
     * Control字段，用于指定一些控制信息。
     */
    uint8_t control;
    /**
     * CDB的第一个字节。
     */
    uint8_t byte1;
    /**
     * CDB的第六个字节。
     */
    uint8_t byte6;
    /**
     * 超时时间（单位：毫秒）。
     */
    uint32_t timeout;
} ScsiPeripheral_VerifyRequest;
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // SCSI_PERIPHERAL_TYPES_H
/** @} */
