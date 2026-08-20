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
 * @addtogroup ScsiPeripheralDDK
 * @{
 *
 * @brief SCSI Peripheral DDK是为开发者提供专门用于开发SCSI设备驱动程序的套件，提供了初始化DDK、释放DDK、打开关闭设备、读写设备等接口，并声明了SCSI设备驱动的开发所需的宏、枚举变量和数据结构，
 * 使用场景包括存储设备驱动开发、磁盘阵列管理等。
 * @since 18
 */

/**
 * @file scsi_peripheral_types.h
 *
 * @brief 提供在SCSI Peripheral DDK（驱动开发工具包）API中使用的枚举变量、结构体和宏。
 *
 * @include <scsi_peripheral/scsi_peripheral_types.h>
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
#endif

/**
 * @brief 描述符格式感知数据的最小长度。
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MIN_DESCRIPTOR_FORMAT_SENSE 8

/**
 * @brief 固定格式感知数据的最小长度。
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
     * 没有权限。请确保应用已正确声明所需的权限。
     */
    SCSIPERIPHERAL_DDK_NO_PERM = 201,
    /**
     * 非法参数。请检查参数是否符合要求。
     */
    SCSIPERIPHERAL_DDK_INVALID_PARAMETER = 401,
    /**
     * 操作成功。
     */
    SCSIPERIPHERAL_DDK_SUCCESS = 31700000,
    /**
     * 与内存相关的错误，例如，内存不足、内存数据复制失败或内存申请失败。请检查内存状态和相关参数。
     */
    SCSIPERIPHERAL_DDK_MEMORY_ERROR = 31700001,
    /**
     * 非法操作。请检查操作逻辑是否正确。
     */
    SCSIPERIPHERAL_DDK_INVALID_OPERATION = 31700002,
    /**
     * 设备输入/输出操作失败。请检查传输参数和设备规格。
     */
    SCSIPERIPHERAL_DDK_IO_ERROR = 31700003,
    /**
     * 传输超时。请检查超时参数和设备状态。
     */
    SCSIPERIPHERAL_DDK_TIMEOUT = 31700004,
    /**
     * DDK初始化错误，或者DDK未初始化。请先初始化DDK服务。
     */
    SCSIPERIPHERAL_DDK_INIT_ERROR = 31700005,
    /**
     * 与SCSI Peripheral DDK服务的通信失败。请检查DDK服务是否正常运行。
     */
    SCSIPERIPHERAL_DDK_SERVICE_ERROR = 31700006,
    /**
     * 设备未找到。请确保传入的设备信息正确。
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
     * 任务已中止。
     */
    SCSIPERIPHERAL_STATUS_TASK_ABORTED = 0x40,
} ScsiPeripheral_Status;

/**
 * @brief 不透明的SCSI设备结构体，用于表示与SCSI外设交互的设备句柄。
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
     * 设备内存映射的缓冲区起始地址，指向映射的设备内存空间。该缓冲区用于存储SCSI设备数据，提供高性能的内存访问能力。
     */
    uint8_t * const address;
    /**
     * 缓冲区大小，单位：字节。取值原则：必须大于0。
     */
    const size_t size;
    /**
     * 缓冲区读写起始偏移量，单位：字节。默认值为0，表示没有偏移，缓冲区从指定地址开始。取值范围为[0, size]，当需要从缓冲区特定位置开始读写时设置此参数，不同的offset值对应不同的起始读写位置。
     */
    uint32_t offset;
    /**
     * 要使用的缓冲区长度，单位：字节。默认情况下，该值等于缓冲区的大小，表示整个缓冲区都被使用。当只使用缓冲区的一部分时设置此参数，bufferLength加offset的值应小于等于size。
     */
    uint32_t bufferLength;
    /**
     * 已传输数据的长度，单位：字节。初始值为0，表示尚未传输任何数据。该字段在SCSI数据传输完成后更新，表示实际传输的数据量，可用于监控传输进度。
     */
    uint32_t transferredLength;
} ScsiPeripheral_DeviceMemMap;

/**
 * @brief 读/写操作的请求参数。该结构体定义了SCSI外设进行读/写操作时所需的请求参数，包括逻辑块起始地址、传输长度、控制信息等。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_IORequest {
    /**
     * 逻辑块起始地址，用于指定SCSI外设读/写操作的起始逻辑块位置。
     */
    uint32_t lbAddress;
    /**
     * 需要操作的连续逻辑块的数量，必须是正整数且不超过设备单次传输的最大逻辑块数限制。
     */
    uint16_t transferLength;
    /**
     * Control字段，用于指定SCSI命令的控制标志，如优先级、链接命令等控制选项。
     */
    uint8_t control;
    /**
     * SCSI命令描述符块（CDB）的第一个字节，通常包含操作码和操作组信息。
     */
    uint8_t byte1;
    /**
     * SCSI命令描述符块（CDB）的第六个字节，根据命令类型包含不同的参数或标志信息。
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
 * @brief 命令描述符块的最大长度。
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MAX_CMD_DESC_BLOCK_LEN 16

/**
 * @brief SCSI请求参数结构体，用于构造与SCSI设备交互的请求参数，支持配置命令描述符块、数据缓冲区、超时时间等。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_Request {
    /**
     * 命令描述符块，应遵循SCSI命令规范，填充对应命令的标准描述符格式。
     */
    uint8_t commandDescriptorBlock[SCSIPERIPHERAL_MAX_CMD_DESC_BLOCK_LEN];
    /**
     * 命令描述符块的长度，应确保长度和实际命令匹配，最大不超过{@link SCSIPERIPHERAL_MAX_CMD_DESC_BLOCK_LEN}。
     */
    uint8_t cdbLength;
    /**
     * 数据传输方向：-1为无数据传输的命令，-2为从主机到设备的数据传输（写），-3为从设备到主机的数据传输（读），-4为双向数据传输。
     */
    int8_t dataTransferDirection;
    /**
     * 数据传输缓冲区的指针。
     */
    ScsiPeripheral_DeviceMemMap *data;
    /**
     * 超时时间（单位：毫秒）。
     */
    uint32_t timeout;
} ScsiPeripheral_Request;

/**
 * @brief 感知数据的最大长度。
 *
 * @since 18
 */
#define SCSIPERIPHERAL_MAX_SENSE_DATA_LEN 252

/**
 * @brief SCSI响应参数结构体，包含状态、错误诊断数据、传输结果等，用于接收SCSI设备响应数据、判断命令是否成功。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_Response {
    /**
     * Sense Data，SCSI设备返回给主机的状态、错误及诊断信息。
     */
    uint8_t senseData[SCSIPERIPHERAL_MAX_SENSE_DATA_LEN];
    /**
     * 调用完成时的状态。可能的值包括：SCSIPERIPHERAL_STATUS_GOOD（正常状态）、SCSIPERIPHERAL_STATUS_BUSY（占用中）等。
     */
    ScsiPeripheral_Status status;
    /**
     * 在SCSI通用驱动中，该字段用于存储经掩码处理后的SCSI状态。
     */
    uint8_t maskedStatus;
    /**
     * 消息状态，表示SCSI命令执行完成后的消息结果。
     */
    uint8_t msgStatus;
    /**
     * 实际写入到Sense Buffer（感知缓冲区）的有效字节数，用于确定senseData数组中有效数据的长度，若为0表示无Sense Data。
     */
    uint8_t sbLenWr;
    /**
     * 主机适配器状态。例如：成功（0x00）、无法连接（0x01）、总线忙（0x02）、超时（0x03）。
     */
    uint16_t hostStatus;
    /**
     * 驱动状态。例如：成功（0x00）、设备或资源忙（0x01）。
     */
    uint16_t driverStatus;
    /**
     * 实际传输的数据长度差值，即未传输的字节数。
     */
    int32_t resId;
    /**
     * 执行SCSI命令消耗的时间（单位：毫秒）。
     */
    uint32_t duration;
} ScsiPeripheral_Response;

/**
 * @brief SCSI命令（TEST UNIT READY）的请求结构体，通常用于确认逻辑单元是否就绪（逻辑单元是SCSI设备中可独立寻址的I/O操作实体）。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_TestUnitReadyRequest {
    /**
     * Control字段，用于指定SCSI命令的控制信息。
     */
    uint8_t control;
    /**
     * 超时时间（单位：毫秒）。
     */
    uint32_t timeout;
} ScsiPeripheral_TestUnitReadyRequest;

/**
 * @brief SCSI命令（INQUIRY）的请求结构体，通常用于查询设备的基本信息。
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
     * Allocation length字段，用于指定请求发起者（通常是主机）为响应数据准备的缓冲区大小。单位：字节。
     */
    uint16_t allocationLength;
    /**
     * Control字段，用于指定SCSI命令的控制标志，如优先级、链接命令等控制选项。
     */
    uint8_t control;
    /**
     * SCSI命令描述符块（CDB）的第一个字节，通常包含操作码和操作组信息。
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
 * @brief SCSI INQUIRY 数据，用于存储SCSI外设的INQUIRY命令查询结果。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_InquiryInfo {
    /**
     * SCSI外设的设备类型，具体类型值定义参见SCSI标准协议。
     */
    uint8_t deviceType;
    /**
     * 制造商 ID。
     */
    char idVendor[SCSIPERIPHERAL_VENDOR_ID_LEN + 1];
    /**
     * 产品 ID。
     */
    char idProduct[SCSIPERIPHERAL_PRODUCT_ID_LEN + 1];
    /**
     * 产品版本。
     */
    char revProduct[SCSIPERIPHERAL_PRODUCT_REV_LEN + 1];
    /**
     * 指向设备内存映射的指针，用于存储查询得到的数据。
     */
    ScsiPeripheral_DeviceMemMap *data;
} ScsiPeripheral_InquiryInfo;

/**
 * @brief SCSI命令（READ CAPACITY）的请求结构体，用于发送读取存储容量的命令，可帮助获取设备的逻辑块大小和总块数。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_ReadCapacityRequest {
    /**
     * 逻辑块地址，用于指定读取容量的起始逻辑块位置。取值为0时获取设备整体容量信息。
     */
    uint32_t lbAddress;
    /**
     * Control字段，用于指定SCSI命令的控制信息。
     */
    uint8_t control;
    /**
     * CDB（Command Descriptor Block，命令描述符块）的第八个字节。
     */
    uint8_t byte8;
    /**
     * 超时时间（单位：毫秒）。
     */
    uint32_t timeout;
} ScsiPeripheral_ReadCapacityRequest;

/**
 * @brief SCSI READ CAPACITY结构体。用于在开发SCSI设备驱动时获取设备的存储容量信息，支持进行分区管理、可用空间检查和存储资源分配等操作。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_CapacityInfo {
    /**
     * 返回的逻辑块地址，表示可寻址的最后一块逻辑块的编号，逻辑块总数为该值加1。
     */
    uint32_t lbAddress;
    /**
     * 单个逻辑块长度（单位：字节）。表示每个逻辑块的字节大小，通常为512、2048或4096等标准值，具体取决于设备类型和格式化方式。
     */
    uint32_t lbLength;
} ScsiPeripheral_CapacityInfo;

/**
 * @brief SCSI命令（REQUEST SENSE）的请求结构体，该命令通常用于获取设备的错误信息。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_RequestSenseRequest {
    /**
     * Allocation length字段，指定了请求发起者（通常是主机）为响应数据准备的缓冲区大小，单位：字节。
     */
    uint8_t allocationLength;
    /**
     * Control字段，用于指定SCSI命令的控制信息。
     */
    uint8_t control;
    /**
     * CDB（Command Descriptor Block，命令描述符块）的第一个字节。
     */
    uint8_t byte1;
    /**
     * 超时时间（单位：毫秒）。
     */
    uint32_t timeout;
} ScsiPeripheral_RequestSenseRequest;

/**
 * @brief SCSI Sense Data的基本信息结构体，用于封装SCSI命令执行后返回的sense数据。该结构体包含响应码、状态标志位以及各类信息字段，用于驱动程序获取和分析SCSI设备的错误状态和命令执行结果。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_BasicSenseInfo {
    /**
     * 响应码。由驱动层在收到Sense Data时自动设置。
     */
    uint8_t responseCode;
    /**
     * 信息有效标志位。为true时表示information和commandSpecific字段有效，为false时这些字段应被忽略。使用前应先检查此标志位以避免读取无效数据。
     */
    bool valid;
    /**
     * Information字段，取值遵循SCSI标准协议。
     */
    uint64_t information;
    /**
     * Command-specific information字段，取值遵循SCSI标准协议。
     */
    uint64_t commandSpecific;
    /**
     * Sense key specific字段的标志位。当为true时，表示senseKeySpecific字段有效，包含sense key specific data；为false时应忽略senseKeySpecific字段。
     * 使用前应先检查此标志位以避免读取无效数据。
     */
    bool sksv;
    /**
     * Sense key specific字段，取值遵循SCSI标准协议。
     */
    uint32_t senseKeySpecific;
} ScsiPeripheral_BasicSenseInfo;

/**
 * @brief SCSI命令（VERIFY）的请求结构体，该命令通常用于校验逻辑块的数据完整性。
 *
 * @since 18
 */
typedef struct ScsiPeripheral_VerifyRequest {
    /**
     * 起始逻辑块地址。
     */
    uint32_t lbAddress;
    /**
     * 要校验的连续逻辑块的数量。
     */
    uint16_t verificationLength;
    /**
     * Control字段，用于指定SCSI命令的控制信息。
     */
    uint8_t control;
    /**
     * CDB（Command Descriptor Block，命令描述符块）的第一个字节。
     */
    uint8_t byte1;
    /**
     * CDB（Command Descriptor Block，命令描述符块）的第六个字节。
     */
    uint8_t byte6;
    /**
     * 超时时间（单位：毫秒）。
     */
    uint32_t timeout;
} ScsiPeripheral_VerifyRequest;
#ifdef __cplusplus
}
#endif
#endif // SCSI_PERIPHERAL_TYPES_H
/** @} */

