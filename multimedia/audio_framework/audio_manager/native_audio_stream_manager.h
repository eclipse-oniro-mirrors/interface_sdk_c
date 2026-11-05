/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @syscap SystemCapability.Multimedia.Audio.Core
 *
 * @since 19
 */

/**
 * @file native_audio_stream_manager.h
 *
 * @brief Declare audio stream manager related interfaces.
 *
 * This file interface is used for the creation of audioStreamManager
 * as well as the audio stream settings and management.
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 19
 */

#ifndef NATIVE_AUDIO_STREAM_MANAGER_H
#define NATIVE_AUDIO_STREAM_MANAGER_H

#include <stdbool.h>
#include "native_audio_common.h"
#include "native_audiostream_base.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Declare the audio stream manager.
 * Audio stream manager provides many functions about audio streams, like monitoring audio streams status,
 * getting different stream types supported information and so on.
 *
 * @since 19
 */
typedef struct OH_AudioStreamManager OH_AudioStreamManager;

/**
 * @brief Fetch the audio streammanager handle, which is a singleton.
 *
 * @param streamManager output parameter to get the {@link #OH_AudioStreamManager}.
 * @return
 *         {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *         {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} if system state error
 * @since 19
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioStreamManager(OH_AudioStreamManager **streamManager);

/**
 * @brief Gets the mode of direct playback available for a given audio format with current active device.
 *
 * @param audioStreamManager the {@link OH_AudioStreamManager} handle provided by
 * {@link OH_AudioManager_GetAudioStreamManager}.
 * @param streamInfo the {@link OH_AudioStreamInfo}.
 * @param usage the {@link OH_AudioStream_Usage}.
 * @param directPlaybackMode the {@link OH_AudioStream_DirectPlaybackMode} pointer to a variable which receives the
 * result.
 * @return Function result code:
 *         {@link AUDIOCOMMON_RESULT_SUCCESS} If the execution is successful.
 *         {@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}:
 *                                                        1.The param of audioStreamManager is nullptr;
 *                                                        2.The param of streamInfo is nullptr;
 *                                                        3.The param of usage invalid;
 *                                                        4.The param of directPlaybackMode is nullptr.
 * @since 19
 */
OH_AudioCommon_Result OH_AudioStreamManager_GetDirectPlaybackSupport(
    OH_AudioStreamManager *audioStreamManager, OH_AudioStreamInfo *streamInfo,
    OH_AudioStream_Usage usage, OH_AudioStream_DirectPlaybackMode *directPlaybackMode);

/**
 * @brief Query whether acoustic echo canceler is supported by input source.
 *
 * @param streamManager The {@link OH_AudioStreamManager} handle provided
 * by {@link OH_AudioManager_GetAudioStreamManager}.
 * @param sourceType Related source type.
 * @param supported Pointer to get the result.
 * @return Function result code:
 *     {@link AUDIOCOMMON_RESULT_SUCCESS} If the execution is successful.
 *     {@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}:
 *                                                    1.The input param streamManager is nullptr;
 *                                                    2.Source type is invalid.
 *                                                    3.The input param supported is nullptr.
 * @since 20
 */

OH_AudioCommon_Result OH_AudioStreamManager_IsAcousticEchoCancelerSupported(
    OH_AudioStreamManager *streamManager,
    OH_AudioStream_SourceType sourceType,
    bool *supported);

/**
 * @brief Return if fast playback is supported for the specific audio stream info and usage type
 *     in current device situation.
 *
 * @param streamManager {@link OH_AudioStreamManager} handle
 *     provided by {@link OH_AudioManager_GetAudioStreamManager}.
 * @param streamInfo reference of stream info structure to describe basic audio format.
 * @param usage stream usage type used to decide the audio device and pipe type selection result.
 * @return {@code true} if fast playback is supported in this situation.
 * @since 20
 */
bool OH_AudioStreamManager_IsFastPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage);

/**
 * @brief Return if fast recording is supported for the specific audio stream info and source type
 *     in current device situation.
 *
 * @param streamManager {@link OH_AudioStreamManager} handle
 *     provided by {@link OH_AudioManager_GetAudioStreamManager}.
 * @param streamInfo reference of stream info structure to describe basic audio format.
 * @param source stream source type used to decide the audio device and pipe type selection result.
 * @return {@code true} if fast recording is supported in this situation.
 * @since 20
 */
bool OH_AudioStreamManager_IsFastRecordingSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_SourceType source);

/**
 * @brief This API is used to query whether the current device supports ultra-low latency playback in
 * specific audio stream information and application scenarios.
 * @param streamManager [in] Handle of the audio stream manager. Obtain the handle through
 *     {@link OH_AudioManager_GetAudioStreamManager}.
 * @param streamInfo [in] Pointer to audio stream information.
 * @param usage [in] Audio stream usage scenario.
 * @param supported [out] indicates the variable indicating whether the ultra-low latency playback result is
 *     supported. Only if the function returns
 * {@link AUDIOCOMMON_RESULT_SUCCESS}: This parameter is valid. The value true indicates that this parameter is
 * supported, and the value false indicates that this parameter is not supported.
 * @return<ul>
 * <li>AUDIOCOMMON_RESULT_SUCCESS: The query is successful. </li>
 * <li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM: streamManager, streamInfo, supported parameter null pointer
 * or usage parameter is invalid. </li>
 * <li>AUDIOCOMMON_RESULT_ERROR_SERVICE_DIED: The audio service process exits unexpectedly. </li>
 * </ul>
 * @since 26.1.0
 */
OH_AudioCommon_Result OH_AudioStreamManager_IsUltraFastPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage,
    bool *supported);

/**
 * @brief This API is used to query whether the current device supports ultra-low latency recording in
 * specific audio stream information and application scenarios.
 * @param streamManager [in] Handle of the audio stream manager. Obtain the handle through
 *     {@link OH_AudioManager_GetAudioStreamManager}.
 * @param streamInfo [in] Pointer to audio stream information.
 * @param source [in] Audio stream usage scenario.
 * @param supported [out] indicates whether to receive the result of ultra-low-latency recording. Only if the
 *     function returns
 * {@link AUDIOCOMMON_RESULT_SUCCESS}: This parameter is valid. The value true indicates that this parameter is
 * supported, and the value false indicates that this parameter is not supported.
 * @return<ul>
 * <li>AUDIOCOMMON_RESULT_SUCCESS: The query is successful. </li>
 * <li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM: streamManager, streamInfo, supported parameter null pointer
The * or source parameter is invalid. </li>
 * <li>AUDIOCOMMON_RESULT_ERROR_SERVICE_DIED: The audio service process exits unexpectedly. </li>
 * </ul>
 * @since 26.1.0
 */
OH_AudioCommon_Result OH_AudioStreamManager_IsUltraFastRecordingSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_SourceType source,
    bool *supported);

/**
 * @brief Return if the system recording enables intelligent noise reduction for current device.
 *
 * @param streamManager {@link OH_AudioStreamManager} handle
 *     provided by {@link OH_AudioManager_GetAudioStreamManager}.
 * @param source stream source type used to decide the audio device and pipe type selection result.
 * @return {@code true} if the system recording enables intelligent noise reduction for current device.
 * @since 21
 */
bool OH_AudioStreamManager_IsIntelligentNoiseReductionEnabledForCurrentDevice(
    OH_AudioStreamManager *streamManager, OH_AudioStream_SourceType source);

/**
 * @brief Returns if multichannel playback is supported for the specific audio stream info and usage type
 *     in current device situation.
 *
 * @param streamManager {@link OH_AudioStreamManager} handle
 *     provided by {@link OH_AudioManager_GetAudioStreamManager}.
 * @param streamInfo reference of stream info structure to describe basic audio format.
 * @param usage stream usage type used to decide the audio device and pipe type selection result.
 * @return True if multichannel playback is supported in this situation.
 * @since 26.0.0
 */
bool OH_AudioStreamManager_IsMultichannelPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage);

/**
 * @brief Returns if direct playback is supported for the specific audio stream info and usage type
 *     in current device situation.
 *
 * @param streamManager {@link OH_AudioStreamManager} handle
 *     provided by {@link OH_AudioManager_GetAudioStreamManager}.
 * @param streamInfo reference of stream info structure to describe basic audio format.
 * @param usage stream usage type used to decide the audio device and pipe type selection result.
 * @return True if direct playback is supported in this situation.
 * @since 26.0.0
 */
bool OH_AudioStreamManager_IsDirectPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage);

/**
 * @brief Returns if offload playback is supported for the specific audio stream info and usage type
 *     in current device situation.
 *
 * @param streamManager {@link OH_AudioStreamManager} handle
 *     provided by {@link OH_AudioManager_GetAudioStreamManager}.
 * @param streamInfo reference of stream info structure to describe basic audio format.
 * @param usage stream usage type used to decide the audio device and pipe type selection result.
 * @return True if offload playback is supported in this situation.
 * @since 26.0.0
 */
bool OH_AudioStreamManager_IsOffloadPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_STREAM_MANAGER_H
/** @} */
