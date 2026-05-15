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
 * @brief The LowPowerAudioSink sub module provides variables, properties, and functions
 * for lowpower audio sink.
 *
 * @since 20
 */
/**
 * @file lowpower_audio_sink.h
 *
 * @brief The file declares the native APIs provided by the OH_LowPowerAudioSink instance. You can use the APIs to
 * implement low-power audio playback.
 * 
 * @library liblowpower_avsink.so
 * @kit MediaKit
 * @syscap SystemCapability.Multimedia.Media.LowPowerAVSink
 * @since 20
 */

#ifndef NATIVE_LOWPOWER_AUDIO_SINK_H
#define NATIVE_LOWPOWER_AUDIO_SINK_H

#include <stdint.h>
#include <stdio.h>
#include "native_averrors.h"
#include "native_avformat.h"
#include "lowpower_audio_sink_base.h"
#include "ohaudio/native_audiostream_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an OH_LowPowerAudioSink instance.
 * 
 * @param mime mime type description string, refer to {@link AVCODEC_MIME_TYPE}
 * @return Pointer to the OH_LowPowerAudioSink instance created. If the operation fails, nullptr is returned.
 * @since 20
 */
OH_LowPowerAudioSink* OH_LowPowerAudioSink_CreateByMime(const char* mime);

/**
 * @brief Configures an OH_LowPowerAudioSink instance. This function must be called before {@link OH_LowPowerAudioSink_Prepare}.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @param format A pointer to an OH_AVFormat to give the description of the audio track to be decoded
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_UNSUPPORT}: The format is not supported.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Configure(OH_LowPowerAudioSink* sink, const OH_AVFormat* format);

/**
 * @brief Sets parameters for an OH_LowPowerAudioSink instance. The parameters can be dynamically set after {@link OH_LowPowerAudioSink_Prepare}.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @param format pointer to an OH_AVFormat instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_UNSUPPORT}: The format is not supported.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_SetParameter(OH_LowPowerAudioSink* sink, const OH_AVFormat* format);

/**
 * @brief Obtains the parameters of an OH_LowPowerAudioSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @param format pointer to an OH_AVFormat instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_GetParameter(OH_LowPowerAudioSink* sink, OH_AVFormat* format);

/**
 * @brief Prepares an OH_LowPowerAudioSink instance for decoding and rendering. This function must be called after {@link OH_LowPowerAudioSink_Configure}.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_UNSUPPORT}: The format is not supported.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Prepare(OH_LowPowerAudioSink* sink);

/**
 * @brief Starts an OH_LowPowerAudioSink instance. This function must be called after a successful call to {@link OH_LowPowerAudioSink_Prepare}.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_UNSUPPORT}: The format is not supported.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Start(OH_LowPowerAudioSink* sink);

/**
 * @brief Pauses an OH_LowPowerAudioSink instance. This function must be called after {@link OH_LowPowerAudioSink_Start}
 * or {@link OH_LowPowerAudioSink_Resume}.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Pause(OH_LowPowerAudioSink* sink);

/**
 * @brief Resumes an OH_LowPowerAudioSink instance. This function must be called after {@link OH_LowPowerAudioSink_Pause}.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Resume(OH_LowPowerAudioSink* sink);

/**
 * @brief Clears all input and output data from the decoders and render buffers of an OH_LowPowerAudioSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Flush(OH_LowPowerAudioSink* sink);

/**
 * @brief Stops an OH_LowPowerAudioSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Stop(OH_LowPowerAudioSink* sink);

/**
 * @brief Resets an OH_LowPowerAudioSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Reset(OH_LowPowerAudioSink* sink);

/**
 * @brief Clears internal resources of an OH_LowPowerAudioSink instance and destroys the instance. You only need to
 * call the function once.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_Destroy(OH_LowPowerAudioSink* sink);

/**
 * @brief Sets the rendering volume for an OH_LowPowerAudioSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @param volume Volume to set which changes from 0.0 to 1.0
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_SetVolume(OH_LowPowerAudioSink* sink, const float volume);

/**
 * @brief Sets the audio rendering speed for an OH_LowPowerAudioSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @param speed The playback speed value needs to be specified, the valid value is 0.25-4.0
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_SetPlaybackSpeed(OH_LowPowerAudioSink* sink, const float speed);

/**
 * @brief Provides a buffer to an OH_LowPowerAudioSink instance for procesing.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @param samples Pointer to an OH_AVSamplesBuffer instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_ReturnSamples(OH_LowPowerAudioSink* sink, OH_AVSamplesBuffer* samples);

/**
 * @brief Registers a callback for an OH_LowPowerAudioSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance
 * @param callback Pointer to an OH_LowPowerAudioSinkCallback instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSink_RegisterCallback(OH_LowPowerAudioSink* sink, OH_LowPowerAudioSinkCallback* callback);

/**
 * @brief Creates an OH_LowPowerAudioSinkCallback instance.
 * 
 * @return Pointer to the OH_LowPowerAudioSinkCallback instance created. If the memory is insufficient, nullptr is
 * returned.
 * @since 20
 */
OH_LowPowerAudioSinkCallback* OH_LowPowerAudioSinkCallback_Create(void);

/**
 * @brief Destroys an OH_LowPowerAudioSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerAudioSinkCallback instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_Destroy(OH_LowPowerAudioSinkCallback* callback);

/**
 * @brief Sets a progress update listener for an OH_LowPowerAudioSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerAudioSinkCallback instance
 * @param onPositionUpdated OH_LowPowerAudioSink_OnPositionUpdated function,
 * refer to {@link OH_LowPowerAudioSink_OnPositionUpdated}
 * @param userData Pointer to the data on which the caller depends when executing the callback.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_SetPositionUpdateListener(
    OH_LowPowerAudioSinkCallback* callback,
    OH_LowPowerAudioSink_OnPositionUpdated onPositionUpdated,
    void* userData);

/**
 * @brief Sets a data needed listener for an OH_LowPowerAudioSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerAudioSinkCallback instance
 * @param onDataNeeded OH_LowPowerAudioSink_OnDataNeeded function,
 * refer to {@link OH_LowPowerAudioSink_OnDataNeeded}
 * @param userData User specific data
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_SetDataNeededListener(
    OH_LowPowerAudioSinkCallback* callback,
    OH_LowPowerAudioSink_OnDataNeeded onDataNeeded,
    void* userData);

/**
 * @brief Sets an error listener for an OH_LowPowerAudioSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerAudioSinkCallback instance
 * @param onError OH_LowPowerAudioSink_OnError function,
 * refer to {@link OH_LowPowerAudioSink_OnError}
 * @param userData User specific data
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_SetErrorListener(
    OH_LowPowerAudioSinkCallback* callback,
    OH_LowPowerAudioSink_OnError onError,
    void* userData);

/**
 * @brief Sets an audio focus interruption listener for an OH_LowPowerAudioSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerAudioSinkCallback instance
 * @param onInterrupted OH_LowPowerAudioSink_OnInterrupted function,
 * refer to {@link OH_LowPowerAudioSink_OnInterrupted}
 * @param userData User specific data
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_SetInterruptListener(
    OH_LowPowerAudioSinkCallback* callback,
    OH_LowPowerAudioSink_OnInterrupted onInterrupted,
    void* userData);

/**
 * @brief Sets an audio device change listener for an OH_LowPowerAudioSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerAudioSink Callback instance
 * @param onDeviceChanged OH_LowPowerAudioSink_OnDeviceChanged function,
 * refer to {@link OH_LowPowerAudioSink_OnDeviceChanged}
 * @param userData User specific data
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_SetDeviceChangeListener(
    OH_LowPowerAudioSinkCallback* callback,
    OH_LowPowerAudioSink_OnDeviceChanged onDeviceChanged,
    void* userData);

/**
 * @brief Sets an end-of-stream listener for an OH_LowPowerAudioSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerAudioSinkCallback instance
 * @param onEos OH_LowPowerAudioSink_OnEos function,
 * refer to {@link OH_LowPowerAudioSink_OnEos}
 * @param userData User specific data
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerAudioSinkCallback_SetEosListener(
    OH_LowPowerAudioSinkCallback *callback,
    OH_LowPowerAudioSink_OnEos onEos,
    void* userData);

/**
 * @brief Sets the loudness gain for an OH_LowPowerAudioSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerAudioSink instance.
 * @param loudnessGain Loudness gain to set which changes from -90.0 to 24.0, expressing in dB.
 * The default loudness gain is 0.0dB.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * @since 21
 */
OH_AVErrCode OH_LowPowerAudioSink_SetLoudnessGain(OH_LowPowerAudioSink* sink, float loudnessGain);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_LOWPOWER_AUDIO_SINK_H

/** @} */
