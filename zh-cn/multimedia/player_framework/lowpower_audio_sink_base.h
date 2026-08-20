/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @addtogroup LowPowerAudioSink
 * @{
 *
 * @brief LowPowerAudioSink子模块提供低功耗音频输出的变量、属性和函数。
 *
 * @since 20
 */
/**
 * @file lowpower_audio_sink_base.h
 *
 * @brief 定义LowPowerAudioSink的结构体和枚举。
 * 
 * @library liblowpower_avsink.so
 * @kit MediaKit
 * @include <multimedia/player_framework/lowpower_audio_sink_base.h>
 * @syscap SystemCapability.Multimedia.Media.LowPowerAVSink
 * @since 20
 */

#ifndef NATIVE_LOWPOWER_AUDIO_SINK_BASE_H
#define NATIVE_LOWPOWER_AUDIO_SINK_BASE_H

#include <stdint.h>
#include "lowpower_avsink_base.h"
#include "ohaudio/native_audiostream_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief OH_LowPowerAudioSink是低功耗音频输出场景中使用的数据结构，开发者通过该结构体实现低功耗音频输出功能。
 * 
 * @since 20
 */
typedef struct OH_LowPowerAudioSink OH_LowPowerAudioSink;

/**
 * @brief 包含了OH_LowPowerAudioSink回调函数指针的集合。<br> 应用需注册此实例结构体到{@link OH_LowPowerAudioSink}实例中，并对回调上报的信息进行处理，
 * 保证LowPowerAudioSink的正常运行。
 * 
 * @since 20
 */
typedef struct OH_LowPowerAudioSinkCallback OH_LowPowerAudioSinkCallback;

/**
 * @brief LowPowerAudioSink发生错误时调用该方法。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param errorCode 发生错误时上报的错误码。请参考{@link OH_AVErrCode}
 * @param errorMsg 错误描述信息。
 * @param userData 用户自定义数据。
 * @since 20
 */
typedef void (*OH_LowPowerAudioSink_OnError)(
    OH_LowPowerAudioSink* sink,
    OH_AVErrCode errCode,
    const char* errorMsg,
    void* userData);

/**
 * @brief LowPowerAudioSink进度更新时调用该方法。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param currentPosition 返回服务当前播放的进度值。单位为毫秒。
 * @param userData 用户自定义数据。
 * @since 20
 */
typedef void (*OH_LowPowerAudioSink_OnPositionUpdated)(
    OH_LowPowerAudioSink* sink,
    int64_t currentPosition,
    void* userData);

/**
 * @brief LowPowerAudioSink需要数据时调用该方法。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param samples 即将写入的 AVSamplesBuffer实例。
 * @param userData 用户自定义数据。
 * @since 20
 */
typedef void (*OH_LowPowerAudioSink_OnDataNeeded)(
    OH_LowPowerAudioSink* sink,
    OH_AVSamplesBuffer* samples,
    void* userData);

/**
 * @brief LowPowerAudioSink音频焦点被打断时调用该方法
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param type 音频打断类型，请参考{@link OH_AudioInterrupt_ForceType}
 * @param hint 音频打断提示类型, 请参考{@link OH_AudioInterrupt_Hint}
 * @param userData 用户自定义数据。
 * @since 20
 */
typedef void (*OH_LowPowerAudioSink_OnInterrupted)(
    OH_LowPowerAudioSink* sink,
    OH_AudioInterrupt_ForceType type,
    OH_AudioInterrupt_Hint hint,
    void* userData);

/**
 * @brief LowPowerAudioSink设备切换时调用该方法。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param reason 输出设备发生变化的原因。
 * 请参考{@link OH_AudioStream_DeviceChangeReason}
 * @param userData 用户自定义数据。
 * @since 20
 */
typedef void (*OH_LowPowerAudioSink_OnDeviceChanged)(
    OH_LowPowerAudioSink* sink,
    OH_AudioStream_DeviceChangeReason reason,
    void* userData);

/**
 * @brief LowPowerAudioSink播放完成时调用该方法，包含在{@link OH_LowPowerAudioSinkCallback}中。
 * 
 * @param sink 指向OH_LowPowerAudioSink实例的指针。
 * @param userData 用户自定义数据。
 * @since 20
 */
typedef void (*OH_LowPowerAudioSink_OnEos)(OH_LowPowerAudioSink* sink, void* userData);

#ifdef __cplusplus
}
#endif
#endif // NATIVE_LOWPOWER_AUDIO_SINK_BASE_H

/** @} */
