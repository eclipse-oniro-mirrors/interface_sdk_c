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
 * @brief 提供乐器数字接口MIDI（Musical Instrument Digital Interface）模块的C接口定义，用于MIDI设备管理和数据传输。
 * 支持MIDI设备的发现与连接、设备热插拔状态监控、端口能力的查询与开关、UMP（通用MIDI数据包）格式的数据收发等功能，
 * 适用于需要在应用中对接电子乐器、MIDI控制器等外设并进行MIDI数据交互的场景。
 *
 * @since 24
 */
/**
 * @file native_midi_base.h
 *
 * @brief 声明MIDI模块的基础数据结构，定义MIDI接口的基础类型、枚举、结构体和回调函数。MIDI模块提供标准化的MIDI数据通信能力，
 * 支持USB和BLE设备的连接与枚举，基于UMP格式兼容MIDI 1.0和MIDI 2.0协议，适用于音乐演奏数据传输、MIDI设备控制等需要
 * 与外部MIDI硬件交互的场景。
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
     * @error 操作成功。
     * @since 24
     */
    OH_MIDI_STATUS_OK = 0,

    /**
     * @error 无效参数（例如：空指针）。
     * @since 24
     */
    OH_MIDI_STATUS_GENERIC_INVALID_ARGUMENT = 35500001,

    /**
     * @error IPC通信失败。
     * @since 24
     */
    OH_MIDI_STATUS_GENERIC_IPC_FAILURE = 35500002,

    /**
     * @error 无效的客户端句柄。
     * @since 24
     */
    OH_MIDI_STATUS_INVALID_CLIENT = 35500003,

    /**
     * @error 无效的设备句柄。
     * @since 24
     */
    OH_MIDI_STATUS_INVALID_DEVICE_HANDLE = 35500004,

    /**
     * @error 无效的端口索引。
     * @since 24
     */
    OH_MIDI_STATUS_INVALID_PORT = 35500005,

    /**
     * @error 发送缓冲区暂时已满。表示共享内存缓冲区当前空间不足。<br> 当消息无法放入缓冲区时由非阻塞发送返回。建议等待约10ms后重试。
     * @since 24
     */
    OH_MIDI_STATUS_WOULD_BLOCK = 35500006,

    /**
     * @error 操作超时。
     * @since 24
     */
    OH_MIDI_STATUS_TIMEOUT = 35500007,

    /**
     * @error 客户端已达到允许打开的最大设备数量（16个）。<br> 要打开新设备，必须先关闭现有设备。
     * @since 24
     */
    OH_MIDI_STATUS_TOO_MANY_OPEN_DEVICES = 35500008,

    /**
     * @error 客户端已达到允许打开的最大端口数量（64个）。<br> 要打开新端口，必须先关闭现有端口。
     * @since 24
     */
    OH_MIDI_STATUS_TOO_MANY_OPEN_PORTS = 35500009,

    /**
     * @error 客户端已经打开此设备。同一设备在同一客户端中不允许重复打开。
     * @since 24
     */
    OH_MIDI_STATUS_DEVICE_ALREADY_OPEN = 35500010,

    /**
     * @error 客户端已经打开此端口。同一端口在同一客户端中不允许重复打开。
     * @since 24
     */
    OH_MIDI_STATUS_PORT_ALREADY_OPEN = 35500011,

    /**
     * @error 系统级（8个）或应用级（2个/UID）客户端数量已达上限。应用应等待或释放其他资源后重试。
     * @since 24
     */
    OH_MIDI_STATUS_TOO_MANY_CLIENTS = 35500012,

    /**
     * @error 权限被拒绝。当应用尝试在未获得所需权限（例如BLE设备的蓝牙权限）的情况下执行操作时返回。
     * @since 24
     */
    OH_MIDI_STATUS_PERMISSION_DENIED = 35500013,

    /**
     * @error MIDI系统服务已崩溃或断开连接。必须销毁并重新创建客户端。
     * @since 24
     */
    OH_MIDI_STATUS_SERVICE_DIED = 35500014,

    /**
     * @error 系统内部错误。表示发生了未预期的系统级错误。
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
 * @note SDK始终使用UMP（Universal MIDI Packet）格式进行数据传输，无论选择何种协议。
 * 此枚举定义连接的数据行为和语义，而不是数据结构。
 * MT（Message Type，消息类型）是UMP数据包的消息类型标识，不同MT值对应不同类型的MIDI消息。
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
     * @note 回退策略：如果请求此协议但硬件仅支持MIDI 1.0，
     * 服务将执行”尽力而为”的转换（例如将32位力度降级为7位，将Type 4转换回Type 2）。
     * 可能会丢失数据精度或某些消息类型（如Flex数据）被忽略。
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
     * @brief 时间戳，单位为ns。
     * 通过clock_gettime(CLOCK_MONOTONIC, &time)获取基准时间。值为0表示立即发送。
     *
     * @since 24
     */
    uint64_t timestamp;

    /**
     * @brief UMP数据包中的32位字（word）数量，而非字节数。取值取决于UMP消息类型。
     * 例如：Type 1消息（如UMP系统实时与公共消息）占1个字（32位），Type 4消息（如UMP MIDI 2.0通道声音消息）占2个字（64位）。
     *
     * @since 24
     */
    size_t length;

    /**
     * @brief 指向UMP数据的指针，包含UMP字（uint32_t）。
     * 原始字节流（MIDI 1.0）数据需先转换为UMP格式后再填充此字段。
     * 此指针必须指向4字节对齐的内存地址，以满足UMP规范对32位边界对齐的要求。
     *
     * @since 24
     */
    uint32_t *data;
} OH_MIDIEvent;

/**
 * @brief 设备信息结构体，用于存储MIDI设备的详细信息，包括设备唯一标识符、设备类型（如USB、BLE）、
 * 支持的MIDI协议、设备名称、厂商ID、产品ID及物理地址等。适用于在MIDI设备枚举、识别和连接管理等场景中，
 * 获取并传递设备的完整属性信息。
 *
 * @since 24
 */
typedef struct {
    /**
     * @brief MIDI设备的唯一标识符。
     *
     * @since 24
     */
    int64_t midiDeviceId;

    /**
     * @brief 设备类型（USB或BLE）。
     *
     * @since 24
     */
    OH_MIDIDeviceType deviceType;

    /**
     * @brief 设备原生支持的MIDI协议。
     *
     * - OH_MIDI_PROTOCOL_1_0：设备是传统设备或当前配置为MIDI 1.0。
     * - OH_MIDI_PROTOCOL_2_0：设备使用MIDI 2.0协议。
     * @note 应用可据此决定是否启用高分辨率UI控件。
     *
     * @since 24
     */
    OH_MIDIProtocol nativeProtocol;

    /**
     * @brief 设备名称。
     *
     * @since 24
     */
    char deviceName[256];

    /**
     * @brief 厂商ID。
     *
     * @since 24
     */
    uint64_t vendorId;

    /**
     * @brief 产品ID。
     *
     * @since 24
     */
    uint64_t productId;

    /**
     * @brief 设备物理地址，采用冒号分隔的十六进制MAC地址格式，例如"00:11:22:33:44:55"，仅BLE设备类型时有效。
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
     * @brief 端口在设备中的索引号。
     *
     * @since 24
     */
    uint32_t portIndex;

    /**
     * @brief 端口所属的MIDI设备ID。
     *
     * @since 24
     */
    int64_t deviceId;

    /**
     * @brief 端口方向（输入或输出）。
     *
     * @since 24
     */
    OH_MIDIPortDirection direction;

    /**
     * @brief 端口名称。
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
     * @brief 要打开的端口索引号。取值范围为0到设备实际端口数减1，具体有效索引需通过设备枚举接口获取。
     *
     * @since 24
     */
    uint32_t portIndex;

    /**
     * @brief 指定要使用的MIDI协议版本（MIDI 1.0或MIDI 2.0）。
     * 服务会根据此字段在应用和硬件之间转换数据。应用只需声明期望的协议版本，以下是协议版本与硬件不匹配时的系统处理行为：
     * 1. 在MIDI 2.0设备上请求OH_MIDI_PROTOCOL_1_0：（无损兼容）
     * 应用发送UMP Type 2（MIDI 1.0通道声音）消息，服务直接转发给设备，无数据损失。
     * 2. 在MIDI 1.0设备上请求OH_MIDI_PROTOCOL_2_0：（有损转换）
     * 应用发送UMP Type 4（MIDI 2.0通道声音）消息，服务将Type 4降级转换为Type 2（例如：截断力度值，丢弃逐音符数据），
     * 会丢失数据精度，MIDI 2.0新增且在MIDI 1.0中无法表达的消息（如Per-Note控制器消息）可能被丢弃。
     *
     * @since 24
     */
    OH_MIDIProtocol protocol;
} OH_MIDIPortDescriptor;

/**
 * @brief 声明MIDI客户端。OH_MIDIClient用于建立与MIDI服务的连接，是开发者进行MIDI数据收发和设备管理等操作的基础句柄，
 * 适用于音乐播放器、MIDI控制器接入、数字音乐创作等需要与MIDI设备通信的场景。
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
 * @param userData 调用{@link #OH_MIDIClient_Create}时传入的用户自定义数据指针。
 * @param action 设备变化操作（已连接/已断开）。
 * @param deviceInfo 变化设备的信息。
 *     <br>此对象仅在此回调范围内有效。如需持久化特定属性（如ID或名称），请对该设备信息进行复制。
 * @since 24
 */
typedef void (*OH_MIDICallback_OnDeviceChange)(
    void *userData, OH_MIDIDeviceChangeAction action, OH_MIDIDeviceInformation deviceInfo);

/**
 * @brief 处理客户端级别错误的回调。当MIDI服务发生关键错误（如服务崩溃）时调用。应用可能需要重新创建客户端。
 *
 * @param userData 调用{@link #OH_MIDIClient_Create}时传入的用户自定义数据指针。
 * @param code 错误状态码，指示错误原因。
 * @since 24
 */
typedef void (*OH_MIDICallback_OnError)(void *userData, OH_MIDIStatusCode code);

/**
 * @brief 接收MIDI数据的回调（批量处理）。
 *
 * @warning 内存安全与线程安全注意事项：
 * - 内存安全：events数组及其中所有数据指针是临时的，仅在此回调期间有效。
 * 在回调返回后访问这些指针会导致未定义行为（崩溃、内存损坏）。调用方必须复制任何需要保留的数据。
 * - 线程安全：此回调在高优先级系统线程上调用。不要执行阻塞操作、大量计算或I/O操作。
 *
 * @param userData 调用{@link #OH_MIDIDevice_OpenInputPort}时传入的用户自定义数据指针。
 * @param events 指向接收到的MIDI事件数组的指针。<br> events数组及其中所有数据指针仅在此回调范围内有效。
 *     如需保留数据，请先进行复制。
 * @param eventCount 数组中的事件数。
 * @since 24
 */
typedef void (*OH_MIDIDevice_OnReceived)(void *userData, const OH_MIDIEvent *events, size_t eventCount);

/**
 * @brief 异步打开BLE设备的结果回调。
 * 此回调在系统线程上调用，不要在此回调中执行阻塞操作、大量计算或I/O操作。
 *
 * @param userData 调用{@link #OH_MIDIClient_OpenBLEDevice}时传入的用户自定义数据指针。
 * @param opened 设备是否成功打开。
 *     <br>true表示设备成功打开，设备句柄有效；false表示设备打开失败，设备句柄为NULL。
 * @param device 已打开设备的句柄。
 *     如果opened为true，应用必须在不再需要时调用{@link #OH_MIDIClient_CloseDevice}关闭此句柄。
 *     如果opened为false，此参数为NULL。
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
 * @brief 客户端回调结构体，用于监听MIDI设备的热插拔事件和关键服务错误，包含设备热插拔和错误处理的回调函数指针，
 * 适用于需要在应用中实时感知MIDI设备状态变化并处理异常的场景。
 *
 * @since 24
 */
typedef struct {
    /**
     * @brief 处理设备热插拔事件的回调函数指针。
     *
     * @since 24
     */
    OH_MIDICallback_OnDeviceChange onDeviceChange;

    /**
     * @brief 处理服务运行过程中发生的关键错误的回调函数指针。
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