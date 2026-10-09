/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup OHAudio
 * @{
 *
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file native_audio_device_base.h
 *
 * @brief 本文件提供音频设备管理模块所依赖的基础枚举和结构体定义，包括音频设备类型、音频设备描述结构体以及从设备描述结构体查询具体设备参数的接口。
 * <br>该模块为音频设备管理提供基础数据结构和查询能力，支持获取音频设备的角色、类型、ID、名称、地址、采样率、声道数、编码类型等信息，适用于需要查询和管理音频设备属性的场景。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 12
 * @version 1.0
 */

#ifndef NATIVE_AUDIO_DEVICE_BASE_H
#define NATIVE_AUDIO_DEVICE_BASE_H

#include "native_audiostream_base.h"
#include "native_audio_common.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义音频设备更改类型。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 设备连接。
     *
     */
    AUDIO_DEVICE_CHANGE_TYPE_CONNECT = 0,

    /**
     * @brief 设备断开。
     *
     */
    AUDIO_DEVICE_CHANGE_TYPE_DISCONNECT = 1
} OH_AudioDevice_ChangeType;

/**
 * @brief 定义音频设备角色。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 输入设备。
     *
     */
    AUDIO_DEVICE_ROLE_INPUT = 1,

    /**
     * @brief 输出设备。
     *
     */
    AUDIO_DEVICE_ROLE_OUTPUT = 2
} OH_AudioDevice_Role;

/**
 * @brief 定义音频设备类型。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 无效设备。
     *
     */
    AUDIO_DEVICE_TYPE_INVALID = 0,

    /**
     * @brief 内置听筒。
     *
     */
    AUDIO_DEVICE_TYPE_EARPIECE = 1,

    /**
     * @brief 内置扬声器。
     *
     */
    AUDIO_DEVICE_TYPE_SPEAKER = 2,

    /**
     * @brief 带话筒的有线耳机。
     *
     */
    AUDIO_DEVICE_TYPE_WIRED_HEADSET = 3,

    /**
     * @brief 无话筒的有线耳机。
     *
     */
    AUDIO_DEVICE_TYPE_WIRED_HEADPHONES = 4,

    /**
     * @brief 使用面向同步连接链路（SCO）的蓝牙设备。
     *
     */
    AUDIO_DEVICE_TYPE_BLUETOOTH_SCO = 7,

    /**
     * @brief 使用高级音频分布模式（A2DP）的蓝牙设备。
     *
     */
    AUDIO_DEVICE_TYPE_BLUETOOTH_A2DP = 8,

    /**
     * @brief 内置麦克风。
     *
     */
    AUDIO_DEVICE_TYPE_MIC = 15,

    /**
     * @brief USB音频耳机。
     *
     */
    AUDIO_DEVICE_TYPE_USB_HEADSET = 22,

    /**
     * @brief 显示端口（DisplayPort）设备。
     *
     */
    AUDIO_DEVICE_TYPE_DISPLAY_PORT = 23,

    /**
     * @brief 音频被系统应用投送到其他远程的设备。
     *
     */
    AUDIO_DEVICE_TYPE_REMOTE_CAST = 24,

    /**
     * @brief USB设备（不包含USB耳机）。
     *
     * @since 18
     */
    AUDIO_DEVICE_TYPE_USB_DEVICE = 25,

    /**
     * @brief 附件设备，如遥控器上的麦克风。
     *
     * @since 19
     */
    AUDIO_DEVICE_TYPE_ACCESSORY = 26,

    /**
     * @brief HDMI设备（例如HDMI、ARC、eARC等）。
     *
     * @since 19
     */
    AUDIO_DEVICE_TYPE_HDMI = 27,

    /**
     * @brief 有线数字设备（例如S/PDIF等）。
     *
     * @since 19
     */
    AUDIO_DEVICE_TYPE_LINE_DIGITAL = 28,

    /**
     * @brief 助听器设备。
     *
     * @since 20
     */
    AUDIO_DEVICE_TYPE_HEARING_AID = 30,

    /**
     * @brief 星闪设备。
     *
     * @since 20
     */
    AUDIO_DEVICE_TYPE_NEARLINK = 31,

    /**
     * @brief 默认设备类型。
     *
     */
    AUDIO_DEVICE_TYPE_DEFAULT = 1000
} OH_AudioDevice_Type;

/**
 * @brief 定义音频设备标志。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 无设备。
     *
     */
    AUDIO_DEVICE_FLAG_NONE = 0,

    /**
     * @brief 输出设备。
     *
     */
    AUDIO_DEVICE_FLAG_OUTPUT = 1,

    /**
     * @brief 输入设备。
     *
     */
    AUDIO_DEVICE_FLAG_INPUT = 2,

    /**
     * @brief 所有设备。
     *
     */
    AUDIO_DEVICE_FLAG_ALL = 3
} OH_AudioDevice_Flag;

/**
 * @brief 定义可获取的设备种类。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 媒体输出设备。
     *
     * @since 12
     */
    AUDIO_DEVICE_USAGE_MEDIA_OUTPUT = 1,

    /**
     * @brief 媒体输入设备。
     *
     * @since 12
     */
    AUDIO_DEVICE_USAGE_MEDIA_INPUT = 2,

    /**
     * @brief 所有媒体设备。
     *
     * @since 12
     */
    AUDIO_DEVICE_USAGE_MEDIA_ALL = 3,

    /**
     * @brief 通话输出设备。
     *
     * @since 12
     */
    AUDIO_DEVICE_USAGE_CALL_OUTPUT = 4,

    /**
     * @brief 通话输入设备。
     *
     * @since 12
     */
    AUDIO_DEVICE_USAGE_CALL_INPUT = 8,

    /**
     * @brief 所有通话设备。
     *
     * @since 12
     */
    AUDIO_DEVICE_USAGE_CALL_ALL = 12
} OH_AudioDevice_Usage;

/**
 * @brief 声明音频设备描述结构体，该结构体用于查询音频设备详细信息。
 *
 * @since 12
 */
typedef struct OH_AudioDeviceDescriptor OH_AudioDeviceDescriptor;

/**
 * @brief 声明音频设备描述符数组的结构体，该结构体表示一组音频设备描述符，通过每个描述符可查询设备详细信息。
 *
 * @since 12
 */
typedef struct OH_AudioDeviceDescriptorArray {
    /**
     * @brief 音频设备描述符数组元素个数。
     *
     */
    uint32_t size;

    /**
     * @brief 指向音频设备描述符数组的指针。
     *
     */
    OH_AudioDeviceDescriptor **descriptors;
} OH_AudioDeviceDescriptorArray;

/**
 * @brief 定义音频设备的堵塞状态，主要用于表示内置麦克风的堵塞。默认情况下，音频设备是未堵塞状态。
 *
 * @since 13
 */
typedef enum {
    /**
     * @brief 音频设备未被堵塞。
     *
     * @since 13
     */
    AUDIO_DEVICE_UNBLOCKED = 0,

    /**
     * @brief 音频设备被堵塞。
     *
     * @since 13
     */
    AUDIO_DEVICE_BLOCKED = 1
} OH_AudioDevice_BlockStatus;

/**
 * @brief 查询目标音频设备描述符的设备角色。
 *
 * @param audioDeviceDescriptor [in] 音频设备描述符。可通过 {@link OH_AudioRoutingManager} 的设备查询或监听接口获取。
 * @param deviceRole [out] 获取设备角色的指针。
 * @return <ul>
 *     <br><li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *     <br><li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数 audioDeviceDescriptor 或 deviceRole 为空指针。</li>
 *     <br></ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceRole(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    OH_AudioDevice_Role *deviceRole);

/**
 * @brief 查询目标音频设备描述符的设备类型。
 *
 * @param audioDeviceDescriptor [in] 音频设备描述符。可通过 {@link OH_AudioRoutingManager} 的设备查询或监听接口获取。
 * @param deviceType [out] 获取设备类型的指针。
 * @return <ul>
 *     <br><li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *     <br><li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数 audioDeviceDescriptor 或 deviceType 为空指针。</li>
 *     <br></ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceType(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    OH_AudioDevice_Type *deviceType);

/**
 * @brief 查询目标音频设备描述符的设备ID。
 *
 * @param audioDeviceDescriptor [in] 音频设备描述符。可通过 {@link OH_AudioRoutingManager} 的设备查询或监听接口获取。
 * @param id [out] 获取设备ID的指针。
 * @return <ul>
 *     <br><li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *     <br><li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数 audioDeviceDescriptor 或 id 为空指针。</li>
 *     <br></ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceId(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    uint32_t *id);

/**
 * @brief 查询目标音频设备描述符的设备名称。
 *
 * @param audioDeviceDescriptor [in] 音频设备描述符。可通过 {@link OH_AudioRoutingManager} 的设备查询或监听接口获取。
 * @param name [out] 获取设备名称字符串的指针。
 *     <br>不要单独释放此指针指向的内存，而是调用 {@link OH_AudioRoutingManager_ReleaseDevices} 在不使用时释放所有内存。
 * @return <ul>
 *     <br><li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *     <br><li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数 audioDeviceDescriptor 或 name 为空指针。</li>
 *     <br></ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceName(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    char **name);

/**
 * @brief 查询目标音频设备描述符的设备地址。
 *
 * @param audioDeviceDescriptor [in] 音频设备描述符。可通过 {@link OH_AudioRoutingManager} 的设备查询或监听接口获取。
 * @param address [out] 获取设备地址字符串的指针。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，在不使用时释放所有内存。
 * @return <ul>
 *     <br><li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *     <br><li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数 audioDeviceDescriptor 或 address 为空指针。</li>
 *     <br></ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceAddress(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    char **address);

/**
 * @brief 查询目标音频设备描述符的支持采样率数组。
 *
 * @param audioDeviceDescriptor [in] 音频设备描述符。可通过 {@link OH_AudioRoutingManager} 的设备查询或监听接口获取。
 * @param sampleRates [out] 获取采样率数组的指针，单位为Hz。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，在不使用时释放所有内存。
 * @param size [out] 获取采样率数组长度的指针。
 * @return <ul>
 *     <br><li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *     <br><li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数 audioDeviceDescriptor、sampleRates 或 size 为空指针。</li>
 *     <br></ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceSampleRates(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    uint32_t **sampleRates, uint32_t *size);

/**
 * @brief 查询目标音频设备描述符的支持声道数数组。
 *
 * @param audioDeviceDescriptor [in] 音频设备描述符。可通过 {@link OH_AudioRoutingManager} 的设备查询或监听接口获取。
 * @param channelCounts [out] 获取声道数数组的指针。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices} 在不使用时释放所有内存。
 * @param size [out] 获取声道数数组长度的指针。
 * @return <ul>
 *     <br><li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *     <br><li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数 audioDeviceDescriptor、channelCounts 或 size 为空指针。</li>
 *     <br></ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceChannelCounts(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    uint32_t **channelCounts, uint32_t *size);

/**
 * @brief 查询目标音频设备描述符的显示名称。
 * <br>此名称为目标音频设备所属产品设备的名称，如扬声器所属手机的设备名称。主要用于分布式音频场景下设备选择列表的显示。
 *
 * @param audioDeviceDescriptor [in] 音频设备描述符。可通过 {@link OH_AudioRoutingManager} 的设备查询或监听接口获取。
 * @param displayName [out] 获取显示名称值字符串的指针。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，在不使用时释放所有内存。
 * @return <ul>
 *     <br><li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *     <br><li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数 audioDeviceDescriptor 或 displayName 为空指针。</li>
 *     <br></ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceDisplayName(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    char **displayName);

/**
 * @brief 查询目标音频设备描述符的支持编码类型数组。
 *
 * @param audioDeviceDescriptor [in] 音频设备描述符。可通过 {@link OH_AudioRoutingManager} 的设备查询或监听接口获取。
 * @param encodingTypes [out] 获取音频编码类型数组的指针。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，在不使用时释放所有内存。
 * @param size [out] 获取编码类型大小值的指针变量。
 * @return <ul>
 *     <br><li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *     <br><li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数 audioDeviceDescriptor、encodingTypes 或 size 为空指针。</li>
 *     <br></ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceEncodingTypes(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    OH_AudioStream_EncodingType **encodingTypes, uint32_t *size);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_DEVICE_BASE_H
/** @} */