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
 * @brief Provide common types for audio accessory device C interface.
 *
 * @since 26.0.0
 */

/**
 * @file native_audio_accessory_common.h
 *
 * @brief Declare common types for external audio accessory device interfaces.
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
 * @brief 声明音频附件管理器。
 *
 * @since 26.0.0
 */
typedef struct OH_AudioAccessoryManager OH_AudioAccessoryManager;

/**
 * @brief 声明音频附件。
 *
 * @since 26.0.0
 */
typedef struct OH_AudioAccessory OH_AudioAccessory;

/**
 * @brief 声明音频附件输入流。
 *
 * @since 26.0.0
 */
typedef struct OH_AudioAccessoryInputStream OH_AudioAccessoryInputStream;

/**
 * @brief 枚举音频附件连接类型。
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief 蓝牙SPP（信号处理插件）连接。 */
     * @since 26.0.0
     */
    AUDIO_ACCESSORY_TYPE_BT_SPP = 1
} OH_AudioAccessoryType;

/**
 * @brief 定义音频附件基本信息。
 *
 * <b>Version Control:</b>调用方必须将structSize设置为sizeof(OH_AudioAccessoryInfo)
 * 在将此结构传递给框架之前。
 *
 * @since 26.0.0
 */
typedef struct {
    /**
     * @brief 此结构的大小（以字节为单位）。
     * 必须由调用者初始化（例如，info.structSize = sizeof(OH_AudioAccessoryInfo）)。
     * 框架使用它来确定使用的是哪个版本的结构。
     *
     * @since 26.0.0
     */
    uint32_t structSize;

    /**
     * @brief UX显示的附件名称，如“DJI Mic 2”。
     * 框架会对该字段执行深拷贝。
     *
     * @since 26.0.0
     */
    const char *accessoryName;

    /**
     * @brief 制造商名称，如“DJI”。
     * 框架会对该字段执行深拷贝。
     *
     * @since 26.0.0
     */
    const char *manufacturer;

    /**
     * @brief 型号，如“CP236”。
     * 框架会对该字段执行深拷贝。
     *
     * @since 26.0.0
     */
    const char *modelNumber;

    /**
     * @brief 配件的MAC地址，如“00:11:22:33:44:55”。
     * 框架会对该字段执行深拷贝。
     *
     * @since 26.0.0
     */
    const char *macAddress;

    /**
     * @brief 附件连接类型。
     *
     * @since 26.0.0
     */
    OH_AudioAccessoryType type;

    /**
     * @brief 配件是否为单向音频设备。
     * true：单向设备，false：双向设备。
     *
     * @since 26.0.0
     */
    bool isUnidirectional;
} OH_AudioAccessoryInfo;

/**
 * @brief 定义音频配件的降噪能力。
 *
 * @since 26.0.0
 */
typedef struct {
    /**
     * @brief 此结构的大小（以字节为单位）。
     * 必须由调用者初始化
     * （例如，info.structSize=sizeof(OH_AudioAccessoryNoiseReduceCapability）)。
     * 框架使用它来确定使用的是哪个版本的结构。
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
     * @brief 支持的降噪模式个数。
     *
     * @since 26.0.0
     */
    uint32_t supportedModeCount;

    /**
     * @brief 设备当前的降噪模式。
     * 这表示功能注册时的初始状态。
     *
     * @since 26.0.0
     */
    OH_AudioNoiseReductionMode currentMode;
} OH_AudioAccessoryNoiseReductionCapability;

/**
 * @brief 定义音频配件的能力。
 *
 * <b>Version Control:</b>调用方必须将structSize设置为sizeof(OH_AudioAccessoryCapability)。
 *
 * @since 26.0.0
 */
typedef struct {
    /**
     * @brief 此结构的大小（以字节为单位）。
     * 必须由调用者初始化（例如，caps.structSize=sizeof(OH_AudioAccessoryCapability）)。
     *
     * @since 26.0.0
     */
    uint32_t structSize;

    /**
     * @brief 支持的流配置数组。
     * 每个条目代表一个有效的采样速率组合，
     * 格式和通道数。
     * 框架执行此数组的深拷贝。
     *
     * @since 26.0.0
     */
    const OH_AudioStreamInfo *streamProperties;

    /**
     * @brief 支持的码流配置个数。
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