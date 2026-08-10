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
 * @addtogroup OHAudio
 * @{
 *
 * @brief 提供音频模块C接口定义。
 *
 * @syscap SystemCapability.Multimedia.Audio.Core
 *
 * @since 26.0.0
 */

/**
 * @file native_audio_accessory_common.h
 *
 * @brief 声明外部音频配件设备接口的公共数据结构。\n
 *
 * 定义音频配件接口的公共类型。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 26.0.0
 */

#ifndef NATIVE_AUDIO_ACCESSORY_COMMON_H
#define NATIVE_AUDIO_ACCESSORY_COMMON_H

#include <stdbool.h>

#include "native_audio_common.h"
#include "native_audiostream_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 声明音频配件管理器。
 *
 * 用于管理音频配件相关功能。
 *
 * @since 26.0.0
 */
typedef struct OH_AudioAccessoryManager OH_AudioAccessoryManager;

/**
 * @brief 声明音频配件。
 *
 * 用于表示一个音频配件设备实例。
 *
 * @since 26.0.0
 */
typedef struct OH_AudioAccessory OH_AudioAccessory;

/**
 * @brief 声明音频配件输入流。
 *
 * 用于表示音频配件的输入音频流。
 *
 * @since 26.0.0
 */
typedef struct OH_AudioAccessoryInputStream OH_AudioAccessoryInputStream;

/**
 * @brief 枚举音频配件连接类型。
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief 蓝牙SPP（串行端口协议）连接。
     *
     * @since 26.0.0
     */
    AUDIO_ACCESSORY_TYPE_BT_SPP = 1,
} OH_AudioAccessoryType;

/**
 * @brief 定义音频配件的基本信息。\n
 *
 * <b>版本控制：</b>调用方在将此结构体传递给框架之前，必须将structSize设置为sizeof(OH_AudioAccessoryInfo)。
 *
 * @since 26.0.0
 */
typedef struct {
    /**
     * @brief 结构体大小，单位为字节。\n
     * 调用方必须初始化此字段（例如：info.structSize = sizeof(OH_AudioAccessoryInfo)）。
     * 框架通过此字段判断所使用的结构体版本。
     *
     * @since 26.0.0
     */
    uint32_t structSize;

    /**
     * @brief 配件名称，用于UX展示，如"DJI Mic 2"。\n
     * 框架会对此字段进行深拷贝。
     *
     * @since 26.0.0
     */
    const char *accessoryName;

    /**
     * @brief 制造商名称，如"DJI"。\n
     * 框架会对此字段进行深拷贝。
     *
     * @since 26.0.0
     */
    const char *manufacturer;

    /**
     * @brief 型号编号，如"CP236"。\n
     * 框架会对此字段进行深拷贝。
     *
     * @since 26.0.0
     */
    const char *modelNumber;

    /**
     * @brief 配件MAC地址，如"00:11:22:33:44:55"。\n
     * 框架会对此字段进行深拷贝。
     *
     * @since 26.0.0
     */
    const char *macAddress;

    /**
     * @brief 配件连接类型。
     *
     * @since 26.0.0
     */
    OH_AudioAccessoryType type;

    /**
     * @brief 标识配件是否为单向音频设备。\n
     * true：单向设备；false：双向设备。
     *
     * @since 26.0.0
     */
    bool isUnidirectional;
} OH_AudioAccessoryInfo;

/**
 * @brief 定义音频配件的降噪能力。\n
 *
 * @since 26.0.0
 */
typedef struct {
    /**
     * @brief 结构体大小，单位为字节。\n
     * 调用方必须初始化此字段（例如：info.structSize = sizeof(OH_AudioAccessoryNoiseReductionCapability)）。
     * 框架通过此字段判断所使用的结构体版本。
     *
     * @since 26.0.0
     */
    uint32_t structSize;
    /**
     * @brief 支持的降噪模式数组。
     *
     * @since 26.0.0
     */
    const OH_AudioNoiseReductionMode *supportedModes;

    /**
     * @brief 支持的降噪模式数量。
     *
     * @since 26.0.0
     */
    uint32_t supportedModeCount;

    /**
     * @brief 设备当前降噪模式。\n
     * 表示注册能力时的初始状态。
     *
     * @since 26.0.0
     */
    OH_AudioNoiseReductionMode currentMode;
} OH_AudioAccessoryNoiseReductionCapability;

/**
 * @brief 定义音频配件的能力。\n
 *
 * <b>版本控制：</b>调用方必须将structSize设置为sizeof(OH_AudioAccessoryCapabilities)。
 *
 * @since 26.0.0
 */
typedef struct {
    /**
     * @brief 结构体大小，单位为字节。\n
     * 调用方必须初始化此字段（例如：caps.structSize = sizeof(OH_AudioAccessoryCapabilities)）。
     *
     * @since 26.0.0
     */
    uint32_t structSize;

    /**
     * @brief 支持的音频流配置数组。\n
     * 每个条目表示采样率、采样格式和声道数的有效组合。
     * 框架会对此数组进行深拷贝。
     *
     * @since 26.0.0
     */
    const OH_AudioStreamInfo *streamProperties;

    /**
     * @brief 支持的音频流配置数量。
     *
     * @since 26.0.0
     */
    uint32_t streamPropertyCount;
} OH_AudioAccessoryCapabilities;

#ifdef __cplusplus
}
#endif

/** @} */
#endif // NATIVE_AUDIO_ACCESSORY_COMMON_H
