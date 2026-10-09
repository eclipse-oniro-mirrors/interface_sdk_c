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
 * @addtogroup OHMIDI
 * @{
 *
 * @brief Provides the definition of the C interface for the MIDI module.
 *
 * @since 24
 */
/**
 * @file native_midi_base.h
 *
 * @brief 声明MIDI模块的基础数据结构，定义MIDI接口的基础类型、枚举、结构体和回调函数。MIDI模块提供标准化的MIDI数据通信能力，支持USB和BLE设备的连接与枚举，基于UMP格式兼容MIDI 1.0和MIDI 2.
 * 0协议，适用于音乐演奏数据传输、MIDI设备控制等需要与外部MIDI硬件交互的场景。
 *
 * @library libohmidi.so
 * @syscap SystemCapability.Multimedia.Audio.MIDI
 * @kit AudioKit
 * @since 24
 */
#ifndef NATIVE_MIDI_BASE_H
#define NATIVE_MIDI_BASE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief MIDI状态码枚举。定义MIDI操作的状态码，用于表示操作成功或失败的原因。
 *
 * @since 24
 */
typedef enum {
    /**
     * @error Operation successful.
     *
     * @since 24
     */
    OH_MIDI_STATUS_OK = 0,

    /**
     * @error Invalid parameter (e.g., null pointer).
     *
     * @since 24
     */
    OH_MIDI_STATUS_GENERIC_INVALID_ARGUMENT = 35500001,

    /**
     * @error IPC communication failure.
     *
     * @since 24
     */
    OH_MIDI_STATUS_GENERIC_IPC_FAILURE = 35500002,

    /**
     * @error Invalid client handle.
     *
     * @since 24
     */
    OH_MIDI_STATUS_INVALID_CLIENT = 35500003,

    /**
     * @error Invalid device handle.
     *
     * @since 24
     */
    OH_MIDI_STATUS_INVALID_DEVICE_HANDLE = 35500004,

    /**
     * @error Invalid port index.
     *
     * @since 24
     */
    OH_MIDI_STATUS_INVALID_PORT = 35500005,

    /**
     * @error The send buffer is transiently full.
     * Indicates that the shared memory buffer currently lacks space.
     * Returned by non-blocking send when a message cannot fit in the buffer.
     * Retry the operation with a short delay (recommended: 10ms).
     *
     * @since 24
     */
    OH_MIDI_STATUS_WOULD_BLOCK = 35500006,

    /**
     * @error Operation can not be handled in a reasonable time.
     *
     * @since 24
     */
    OH_MIDI_STATUS_TIMEOUT = 35500007,

    /**
     * @error The client has reached the maximum number of open devices allowed.
     * To open a new device, the client must close an existing one first.
     *
     * @since 24
     */
    OH_MIDI_STATUS_TOO_MANY_OPEN_DEVICES = 35500008,

    /**
     * @error The client has reached the maximum number of open ports allowed.
     * To open a new port, the client must close an existing one first.
     *
     * @since 24
     */
    OH_MIDI_STATUS_TOO_MANY_OPEN_PORTS = 35500009,

    /**
     * @error The client has already opened this device.
     *
     * @since 24
     */
    OH_MIDI_STATUS_DEVICE_ALREADY_OPEN = 35500010,

    /**
     * @error The client has already opened this port.
     *
     * @since 24
     */
    OH_MIDI_STATUS_PORT_ALREADY_OPEN = 35500011,

    /**
     * @error The system-wide or per-application limit for MIDI clients has been reached.
     * The application should wait or release other resources before retrying.
     *
     * @since 24
     */
    OH_MIDI_STATUS_TOO_MANY_CLIENTS = 35500012,

    /**
     * @error Permission denied.
     * Returned when the application attempts to perform an operation
     * without the required permission (e.g., Bluetooth for BLE devices).
     *
     * @since 24
     */
    OH_MIDI_STATUS_PERMISSION_DENIED = 35500013,

    /**
     * @error The MIDI system service has died or disconnected.
     * The client must be destroyed and recreated.
     *
     * @since 24
     */
    OH_MIDI_STATUS_SERVICE_DIED = 35500014,

    /**
     * @error System-level errors such as insufficient memory or system service failure.
     *
     * @since 24
     */
    OH_MIDI_STATUS_SYSTEM_ERROR = 35500100
} OH_MIDIStatusCode;

/**
 * @brief 表示端口方向的枚举。定义MIDI端口的数据传输方向。
 *
 * @since 24
 */
typedef enum {
    /**
     * @brief 输入端口（设备->主机）。
     *
     * @since 24
     */
    OH_MIDI_PORT_DIRECTION_INPUT = 0,

    /**
     * @brief 输出端口（主机->设备）。
     *
     * @since 24
     */
    OH_MIDI_PORT_DIRECTION_OUTPUT = 1
} OH_MIDIPortDirection;

/**
 * @brief MIDI协议版本枚举，用于指定端口使用的MIDI协议行为。
 *
 * @note **CRITICAL**: The SDK always uses UMP (Universal MIDI Packet) format for data transfer,
 * regardless of the selected protocol. This enum defines the "Behavior" and "Semantics"
 * of the connection, not the data structure.
 *
 * @since 24
 */
typedef enum {
    /**
     * @brief 传统MIDI 1.0语义。
     * <br>在此协议下，MIDI系统服务期望接收以下UMP消息类型：
     * <br>- 严格遵循MIDI 1.0协议规范的UMP数据包。
     * <br>- MT 0x0：实用消息（例如时间戳）。
     * <br>- MT 0x1：系统实时和系统公共消息。
     * <br>- MT 0x2：MIDI 1.0通道声音消息（32位）。
     * <br>- MT 0x3：数据消息（64位），用于SysEx（7位载荷）。
     * <br>- 如果目标硬件是MIDI 1.0：服务将UMP转换回字节流（F0...F7）。
     * <br>- 如果目标硬件是MIDI 2.0：服务直接发送未经转换的UMP包（封装的MIDI 1.0）。
     *
     * @since 24
     */
    OH_MIDI_PROTOCOL_1_0 = 1,

    /**
     * @brief MIDI 2.0语义。
     * <br>在此协议下，MIDI系统服务期望接收以下UMP消息类型：
     * <br>- 利用MIDI 2.0功能特性的UMP数据包。
     * <br>- MT 0x4：MIDI 2.0通道声音消息（64位，高分辨率）。
     * <br>- MT 0x0：实用消息（时间戳）。
     * <br>- MT 0xD：Flex数据消息（128位，例如文本、歌词）。
     * <br>- MT 0xF：UMP流消息（128位，端点发现、功能块）。
     * <br>- MT 0x3 / MT 0x5：数据消息（64位或128位）。
     *
     * @note Fallback Policy: If this protocol is requested but the hardware only supports MIDI 1.0,
     * the service will perform "Best-Effort" translation (e.g., downscaling 32-bit velocity
     * to 7-bit, converting Type 4 back to Type 2). Some data precision or message types (like Flex Data)
     * may be lost or ignored.
     *
     * @since 24
     */
    OH_MIDI_PROTOCOL_2_0 = 2
} OH_MIDIProtocol;

/**
 * @brief MIDI设备类型枚举。定义MIDI设备的连接类型。
 *
 * @since 24
 */
typedef enum {
    /**
     * @brief USB MIDI设备。
     *
     * @since 24
     */
    OH_MIDI_DEVICE_TYPE_USB = 0,

    /**
     * @brief BLE（蓝牙低功耗）MIDI设备。
     *
     * @since 24
     */
    OH_MIDI_DEVICE_TYPE_BLE = 1
} OH_MIDIDeviceType;

/**
 * @brief 设备连接状态变化操作枚举。用于标识设备的连接和断开事件。
 *
 * @since 24
 */
typedef enum {
    /**
     * @brief 设备已连接。
     *
     * @since 24
     */
    OH_MIDI_DEVICE_CHANGE_ACTION_CONNECTED = 0,

    /**
     * @brief 设备已断开。
     *
     * @since 24
     */
    OH_MIDI_DEVICE_CHANGE_ACTION_DISCONNECTED = 1
} OH_MIDIDeviceChangeAction;

/**
 * @brief MIDI事件结构体（通用），用于以UMP（Universal MIDI Packet）格式承载和传输MIDI事件数据，适用于MIDI消息的接收、发送与处理场景（如音乐制作应用接收和处理MIDI控制器输入事件、
 * 数字音频工作站处理MIDI消息、音乐教育类应用中MIDI设备交互等）。原始字节流（MIDI 1.0）数据需要先转换为UMP格式后再填充此结构体。
 *
 * @since 24
 */
typedef struct {
    /**
     * @brief Timestamp in nanoseconds.
     * Base time obtained via clock_gettime(CLOCK_MONOTONIC, &time)
     * 0 indicates "send immediately".
     *
     * @since 24
     */
    uint64_t timestamp;

    /**
     * @brief Number of 32-bit words in the packet.
     * e.g., 1 for Type 2/4 (64-bit messages use 2 words)
     *
     * @since 24
     */
    size_t length;

    /**
     * @brief Pointer to UMP data (Must be 4-byte aligned).
     * This contains the raw UMP words (uint32_t).
     *
     * @since 24
     */
    uint32_t *data;
} OH_MIDIEvent;

/**
 * @brief 设备信息结构体，用于存储MIDI设备的详细信息，包括设备唯一标识符、设备类型（如USB、BLE）、支持的MIDI协议、设备名称、厂商ID、产品ID及物理地址等。适用于在MIDI设备枚举、识别和连接管理等场景中，
 * 获取并传递设备的完整属性信息。
 *
 * @since 24
 */
typedef struct {
    /**
     * @brief Unique identifier for the MIDI device.
     *
     * @since 24
     */
    int64_t midiDeviceId;

    /**
     * @brief Type of the device (USB, BLE, etc.).
     *
     * @since 24
     */
    OH_MIDIDeviceType deviceType;

    /**
     * @brief The native protocol supported by the hardware.
     *
     * - If OH_MIDI_PROTOCOL_1_0: The device is a legacy device or currently configured as such.
     * - If OH_MIDI_PROTOCOL_2_0: The device supports MIDI 2.0 features.
     * @note Applications can use this to decide whether to enable high-resolution UI controls.
     *
     * @since 24
     */
    OH_MIDIProtocol nativeProtocol;

    /**
     * @brief Device name.
     *
     * @since 24
     */
    char deviceName[256];

    /**
     * @brief Vendor ID.
     *
     * @since 24
     */
    uint64_t vendorId;

    /**
     * @brief Product ID.
     *
     * @since 24
     */
    uint64_t productId;

    /**
     * @brief Physical address (for BLE device).
     *
     * @since 24
     */
    char deviceAddress[64];
} OH_MIDIDeviceInformation;

/**
 * @brief 端口信息结构体。用于枚举和标识MIDI设备端口，包含可显示的端口名称、端口索引、所属设备ID及端口方向（输入或输出）等关键信息，便于开发者在MIDI应用中管理和操作各端口。
 *
 * @since 24
 */
typedef struct {
    /**
     * @brief The index of the port.
     *
     * @since 24
     */
    uint32_t portIndex;

    /**
     * @brief The ID of the device this port belongs to.
     *
     * @since 24
     */
    int64_t deviceId;

    /**
     * @brief Direction of the port (Input/Output).
     *
     * @since 24
     */
    OH_MIDIPortDirection direction;

    /**
     * @brief Name of the port.
     *
     * @since 24
     */
    char name[64];
} OH_MIDIPortInformation;

/**
 * @brief 端口描述符结构体，用于打开端口时指定端口索引和MIDI协议版本（MIDI 1.0或MIDI 2.0），由系统自动完成应用与硬件之间的协议适配与数据转换，适用于需要在不同MIDI协议版本间进行兼容通信的场景。
 *
 * @since 24
 */
typedef struct {
    /**
     * @brief The unique ID of the port within the device (index).
     *
     * @since 24
     */
    uint32_t portIndex;

    /**
     * @brief The requested protocol behavior for this session.
     *
     * This field dictates how the Service translates data between the app and the hardware.
     *
     * **Compatibility Behavior:**
     *
     * 1. **Request OH_MIDI_PROTOCOL_1_0 on a 2.0 Device**: (Safe)
     * - The service creates a virtual 1.0 view.
     * - App sends UMP Type 2 (MIDI 1.0 Channel Voice).
     * - Device receives UMP Type 2.
     * - Fully compatible.
     *
     * 2. **Request OH_MIDI_PROTOCOL_2_0 on a 1.0 Device**: (Lossy)
     * - The service creates a virtual 2.0 view.
     * - App sends UMP Type 4 (MIDI 2.0 Voice).
     * - Service **down-converts** Type 4 to Type 2 (e.g., clipping velocity, dropping per-note data).
     * - **Warning**: Data precision will be lost. Advanced messages may be dropped.
     *
     * @since 24
     */
    OH_MIDIProtocol protocol;
} OH_MIDIPortDescriptor;

/**
 * @brief 声明MIDI客户端。OH_MIDIClient用于建立与MIDI服务的连接，是开发者进行MIDI数据收发和设备管理等操作的基础句柄，适用于音乐播放器、MIDI控制器接入、数字音乐创作等需要与MIDI设备通信的场景。
 *
 * @since 24
 */
typedef struct OH_MIDIClientStruct OH_MIDIClient;

/**
 * @brief OH_MIDIDevice用于声明和表示MIDI设备，提供对MIDI设备的标识与引用能力，适用于需要在应用中对MIDI设备进行操作的场景。
 *
 * @since 24
 */
typedef struct OH_MIDIDeviceStruct OH_MIDIDevice;

/**
 * @brief 监控设备连接/断开连接的回调。
 *
 * @param userData The user context pointer passed to {@link #OH_MIDIClient_Create}.
 * @param action 设备变化操作（已连接/已断开）。
 * @param deviceInfo 变化设备的信息。
 *     <br>此对象仅在此回调范围内有效。如需持久化特定属性（如ID或名称），请对该设备信息进行复制。
 * @since 24
 */
typedef void (*OH_MIDICallback_OnDeviceChange)(
    void *userData, OH_MIDIDeviceChangeAction action, OH_MIDIDeviceInformation deviceInfo);

/**
 * @brief 接收MIDI数据的回调（批量处理）。
 *
 * @warning **CRITICAL: Memory Safety**
 * The events array and all data pointers within it
 * are **transient and ONLY valid during this callback**.
 * Accessing these pointers after the callback returns
 * causes **undefined behavior** (crashes, memory corruption).
 * You MUST copy any data you need to keep.
 *
 * @warning This callback is invoked on a high-priority system thread.
 * Do **not** perform blocking operations, heavy computation, or I/O.
 *
 * @param userData The user context pointer passed to {@link #OH_MIDIDevice_OpenInputPort}.
 * @param events Pointer to the array of MIDI events received.
 * @param eventCount 数组中的事件数。
 * @since 24
 */
typedef void (*OH_MIDIDevice_OnReceived)(void *userData, const OH_MIDIEvent *events, size_t eventCount);

/**
 * @brief 处理客户端级别错误的回调。当MIDI服务发生关键错误（如服务崩溃）时调用。应用可能需要重新创建客户端。
 *
 * @param userData The user context pointer passed to {@link #OH_MIDIClient_Create}.
 * @param code 错误状态码，指示错误原因。
 * @since 24
 */
typedef void (*OH_MIDICallback_OnError)(void *userData, OH_MIDIStatusCode code);

/**
 * @brief 异步打开BLE设备的结果回调。
 *
 * @param userData The user context pointer passed to {@link #OH_MIDIClient_OpenBLEDevice}.
 * @param opened 设备是否成功打开。
 *     <br>true表示设备成功打开，设备句柄有效；false表示设备打开失败，设备句柄为NULL。
 * @param device The handle of the opened device.
 *     If opened is true, the application MUST close this handle using
 *     {@link #OH_MIDIClient_CloseDevice} when it is no longer needed.
 *     If opened is false, this parameter is NULL.
 * @param info 已打开设备的信息。
 *     <br>如果opened为false，此参数的内容无效。
 *     <br>此对象仅在此回调范围内有效。如需持久化特定属性（如ID或名称），请对该设备信息进行复制。
 * @since 24
 */
typedef void (*OH_MIDIClient_OnDeviceOpened)(void *userData,
                                             bool opened,
                                             OH_MIDIDevice *device,
                                             OH_MIDIDeviceInformation info);

/**
 * @brief 客户端回调结构体，用于监听MIDI设备的热插拔事件和关键服务错误，包含设备热插拔和错误处理的回调函数指针，适用于需要在应用中实时感知MIDI设备状态变化并处理异常的场景。
 *
 * @since 24
 */
typedef struct {
    /**
     * @brief Handler for device hotplug events.
     *
     * @since 24
     */
    OH_MIDICallback_OnDeviceChange onDeviceChange;

    /**
     * @brief Handler for critical service errors.
     *
     * @since 24
     */
    OH_MIDICallback_OnError onError;
} OH_MIDICallbacks;

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_MIDI_BASE_H