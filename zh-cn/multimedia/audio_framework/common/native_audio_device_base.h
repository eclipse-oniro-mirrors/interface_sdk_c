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
 * @brief 定义音频设备参数的类型以及获取每个设备参数的接口。
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
     * @brief 带话筒的耳机。
     *
     */
    AUDIO_DEVICE_TYPE_WIRED_HEADSET = 3,

    /**
     * @brief 无话筒的耳机。
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
 * @brief 声明音频设备描述符。该实例用于获取更多音频设备详细信息属性。
 *
 * @since 12
 */
typedef struct OH_AudioDeviceDescriptor OH_AudioDeviceDescriptor;

/**
 * @brief 声明音频设备描述符数组。
 *
 * @since 12
 */
typedef struct OH_AudioDeviceDescriptorArray {
    /**
     * @brief 音频设备描述符数组大小。
     *
     */
    uint32_t size;

    /**
     * @brief 音频设备描述符数组。
     *
     */
    OH_AudioDeviceDescriptor **descriptors;
} OH_AudioDeviceDescriptorArray;

/**
 * @brief 声明音频设备的堵塞状态。默认情况下，音频设备被视为未堵塞。
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
 * @param audioDeviceDescriptor 音频设备描述符。通过 {@link OH_AudioRoutingManager_GetDevices} 或者
 *     {@link OH_AudioRoutingManager_OnDeviceChangedCallback}获取。
 * @param deviceRole 设备角色指针。将设置设备角色值的变量，指向{@link OH_AudioDevice_Role}。
 * @return AUDIOCOMMON_RESULT_SUCCESS或AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceRole(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    OH_AudioDevice_Role *deviceRole);

/**
 * @brief 查询目标音频设备描述符的设备类型。
 *
 * @param audioDeviceDescriptor 音频设备描述符。通过 {@link OH_AudioRoutingManager_GetDevices} 或者
 *     {@link OH_AudioRoutingManager_OnDeviceChangedCallback}获取。
 * @param deviceType 设备类型指针。将设置设备类型值的变量，指向{@link OH_AudioDevice_Type}。
 * @return AUDIOCOMMON_RESULT_SUCCESS或AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceType(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    OH_AudioDevice_Type *deviceType);

/**
 * @brief 查询目标音频设备描述符的设备id。
 *
 * @param audioDeviceDescriptor 音频设备描述符。通过 {@link OH_AudioRoutingManager_GetDevices} 或者
 *     {@link OH_AudioRoutingManager_OnDeviceChangedCallback}获取。
 * @param id 设备id指针，将设置设备角色值的变量。
 * @return AUDIOCOMMON_RESULT_SUCCESS 或 AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceId(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    uint32_t *id);

/**
 * @brief 查询目标音频设备描述符的设备名称。
 *
 * @param audioDeviceDescriptor 音频设备描述符。通过 {@link OH_AudioRoutingManager_GetDevices} 或者
 *     {@link OH_AudioRoutingManager_OnDeviceChangedCallback}获取。
 * @param name 设备名称指针，将设置设备名称值的变量。
 *     <br>不要单独释放音频设备名称指针，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，以便在不再使用时释放所有DeviceDescriptor数组。
 * @return AUDIOCOMMON_RESULT_SUCCESS或AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceName(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    char **name);

/**
 * @brief 查询目标音频设备描述符的设备地址。
 *
 * @param audioDeviceDescriptor 音频设备描述符。通过 {@link OH_AudioRoutingManager_GetDevices} 或者
 *     {@link OH_AudioRoutingManager_OnDeviceChangedCallback}获取。
 * @param address 设备MAC地址指针，将设置设备MAC地址值的变量。
 *     <br>不要单独释放音频设备MAC地址指针，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，以便在不再使用时释放所有DeviceDescriptor数组。
 * @return AUDIOCOMMON_RESULT_SUCCESS或AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceAddress(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    char **address);

/**
 * @brief 查询目标音频设备描述符的采样率数组。
 *
 * @param audioDeviceDescriptor 音频设备描述符。通过 {@link OH_AudioRoutingManager_GetDevices} 或者
 *     {@link OH_AudioRoutingManager_OnDeviceChangedCallback}获取。
 * @param sampleRates 设置采样率数组值的数组指针变量。
 *     <br>不要单独释放音频设备采样率指针，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，以便在不再使用时释放所有DeviceDescriptor数组。
 * @param size 设置采样率大小值的指针变量。
 * @return AUDIOCOMMON_RESULT_SUCCESS或AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceSampleRates(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    uint32_t **sampleRates, uint32_t *size);

/**
 * @brief 查询目标音频设备描述符的设备通道计数数组。
 *
 * @param audioDeviceDescriptor 音频设备描述符。通过 {@link OH_AudioRoutingManager_GetDevices} 或者
 *     {@link OH_AudioRoutingManager_OnDeviceChangedCallback}获取。
 * @param channelCounts 数组指针变量，该变量将设置通道计数数组值。
 *     <br>不要单独释放音频设备通道数指针，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，以便在不再使用时释放所有DeviceDescriptor数组。
 * @param size 设置通道计数大小值的指针变量。
 * @return AUDIOCOMMON_RESULT_SUCCESS或AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceChannelCounts(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    uint32_t **channelCounts, uint32_t *size);

/**
 * @brief 查询目标音频设备描述符的显示名称。
 *
 * @param audioDeviceDescriptor 音频设备描述符。通过 {@link OH_AudioRoutingManager_GetDevices} 或者
 *     {@link OH_AudioRoutingManager_OnDeviceChangedCallback}获取。
 * @param displayName 设置显示名称值的指针变量。
 *     <br>不要单独释放音频设备显示名称指针，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，以便在不再使用时释放所有DeviceDescriptor数组。
 * @return AUDIOCOMMON_RESULT_SUCCESS或AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceDisplayName(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    char **displayName);

/**
 * @brief 查询目标音频设备描述符的编码类型数组。
 *
 * @param audioDeviceDescriptor 音频设备描述符。通过 {@link OH_AudioRoutingManager_GetDevices} 或者
 *     {@link OH_AudioRoutingManager_OnDeviceChangedCallback}获取。
 * @param encodingTypes 音频设备编码类型，指向{@link OH_AudioStream_EncodingType}。
 *     <br>不要单独释放音频设备编码类型指针，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，以便在不再使用时释放所有DeviceDescriptor数组。
 * @param size 设置编码类型大小值的指针变量。
 * @return AUDIOCOMMON_RESULT_SUCCESS或AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioDeviceDescriptor_GetDeviceEncodingTypes(OH_AudioDeviceDescriptor *audioDeviceDescriptor,
    OH_AudioStream_EncodingType **encodingTypes, uint32_t *size);
#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_DEVICE_BASE_H
/** @} */