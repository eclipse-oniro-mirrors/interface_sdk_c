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
 * @brief The LowPowerAudioSink sub module provides variables, properties,
 * and functions for lowpower audio sink.
 *
 * @since 20
 */
/**
 * @file lowpower_audio_sink_base.h
 *
 * @brief The file declares the structs and enums of the LowPowerAudioSink.
 * 
 * @library liblowpower_avsink.so
 * @kit MediaKit
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
 * @brief The struct describes the declaration for the LowPowerAudioSink.
 * 
 * @since 20
 */
typedef struct OH_LowPowerAudioSink OH_LowPowerAudioSink;

/**
 * @brief The struct contains a set of callback function pointers for the LowPowerAudioSink.
 * 
 * @since 20
 */
typedef struct OH_LowPowerAudioSinkCallback OH_LowPowerAudioSinkCallback;

/**
 * @brief Called when an error occurs in the LowPowerAudioSink.
 * 
 * @param sink OH_LowPowerAudioSink instance
 * @param errorCode Error code when an error occurs
 * @param errorMsg Error description information
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerAudioSink_OnError)(
    OH_LowPowerAudioSink* sink,
    OH_AVErrCode errCode,
    const char* errorMsg,
    void* userData);

/**
 * @brief Called when the playback position is updated in the LowPowerAudioSink.
 * 
 * @param sink OH_LowPowerAudioSink instance
 * @param currentPosition Returns the current playback progress value of the service, in milliseconds
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerAudioSink_OnPositionUpdated)(
    OH_LowPowerAudioSink* sink,
    int64_t currentPosition,
    void* userData);

/**
 * @brief Called when the LowPowerAudioSink needs more data.
 * 
 * @param sink OH_LowPowerAudioSink instance
 * @param samples OH_AVSamplesBuffer instance that will be written in
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerAudioSink_OnDataNeeded)(
    OH_LowPowerAudioSink* sink,
    OH_AVSamplesBuffer* samples,
    void* userData);

/**
 * @brief Called when the audio focus is interrupted in the LowPowerAudioSink.
 * 
 * @param sink OH_LowPowerAudioSink instance
 * @param type The audio interrupt type,
 * please refer to {@link OH_AudioInterrupt_ForceType}
 * @param hint The audio interrupt hint type, please refer to {@link OH_AudioInterrupt_Hint}
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerAudioSink_OnInterrupted)(
    OH_LowPowerAudioSink* sink,
    OH_AudioInterrupt_ForceType type,
    OH_AudioInterrupt_Hint hint,
    void* userData);

/**
 * @brief Called when the audio device changes in the LowPowerAudioSink.
 * 
 * @param sink OH_LowPowerAudioSink instance
 * @param reason Indicates that why does the output device changes,
 * please refer to {@link OH_AudioStream_DeviceChangeReason}
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerAudioSink_OnDeviceChanged)(
    OH_LowPowerAudioSink* sink,
    OH_AudioStream_DeviceChangeReason reason,
    void* userData);

/**
 * @brief Called when the playback is complete in the LowPowerAudioSink. This callback is included in {@link OH_LowPowerAudioSinkCallback}.
 * 
 * @param sink OH_LowPowerAudioSink instance
 * @param userData User specific data
 * @since 20
 */
typedef void (*OH_LowPowerAudioSink_OnEos)(OH_LowPowerAudioSink* sink, void* userData);

#ifdef __cplusplus
}
#endif
#endif // NATIVE_LOWPOWER_AUDIO_SINK_BASE_H

/** @} */
