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
 * @syscap SystemCapability.Multimedia.Audio.Core
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file native_audio_manager.h
 *
 * @brief Declare audio manager related interfaces.
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 12
 * @version 1.0
 */
#ifndef NATIVE_AUDIO_MANAGER_H
#define NATIVE_AUDIO_MANAGER_H

#include "native_audio_common.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Declare the audio manager.
 * The handle of audio manager is used for audio management related functions.
 *
 * @since 12
 */
typedef struct OH_AudioManager OH_AudioManager;

/**
 * @brief Prototype for the audio scene change function that is passed to
 *     {@link OH_AudioManager_RegisterAudioSceneChangeCallback}.
 * 
 * @param userData userdata which is passed by register.
 * @param scene the latest audio scene.
 * @since 20
 */
typedef void (*OH_AudioManager_OnAudioSceneChangeCallback) (
    void *userData,
    OH_AudioScene scene
);

/**
 * @brief Get audio manager handle.
 *
 * @param audioManager the {@link OH_AudioManager} handle received from this function.
 * @return Function result code:
 *         {@link AUDIOCOMMON_RESULT_SUCCESS} If the execution is successful.
 *         {@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}:
 *                                                        1.The param of audioManager is nullptr;
 * @since 12
 */
OH_AudioCommon_Result OH_GetAudioManager(OH_AudioManager **audioManager);

/**
 * @brief Get audio scene.
 *
 * @param manager the {@link OH_AudioManager} handle received from {@link OH_GetAudioManager}.
 * @param scene the {@link OH_AudioScene} pointer to receive the result.
 * @return Function result code:
 *         {@link AUDIOCOMMON_RESULT_SUCCESS} If the execution is successful.
 *         {@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}:
 *                                                        1.The param of audioManager is nullptr;
 *                                                        2.The param of scene is nullptr.
 * @since 12
 */
OH_AudioCommon_Result OH_GetAudioScene(OH_AudioManager* manager, OH_AudioScene *scene);

/**
 * @brief Register callback to receive audio scene changed events.
 *
 * @param manager {@link OH_AudioManager} handle received from {@link OH_GetAudioManager}.
 * @param callback callback function which will be called when audio scene changed.
 * @param userData pointer to a data structure that will be passed to the callback functions.
 * @return
 *     {@link AUDIOCOMMON_RESULT_SUCCESS} if the execution is successful
 *     {@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}
 *                                                   1.param of manager is nullptr
 *                                                   2.param of callback is nullptr
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 20
 */
OH_AudioCommon_Result OH_AudioManager_RegisterAudioSceneChangeCallback(OH_AudioManager *manager,
    OH_AudioManager_OnAudioSceneChangeCallback callback, void *userData);

/**
 * @brief Unregister audio scene change callback.
 *
 * @param manager {@link OH_AudioManager} handle received from {@link OH_GetAudioManager}.
 * @param callback callback function which registered in {@link OH_AudioManager_RegisterAudioSceneChangeCallback}.
 * @return
 *     {@link AUDIOCOMMON_RESULT_SUCCESS} if the execution is successful
 *     {@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}
 *                                                   1.param of manager is nullptr
 *                                                   2.param of callback is nullptr
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 20
 */
OH_AudioCommon_Result OH_AudioManager_UnregisterAudioSceneChangeCallback(OH_AudioManager *manager,
    OH_AudioManager_OnAudioSceneChangeCallback callback);

/**
 * @brief Sets the loudness gain of current renderer. The default loudness gain is 0.0dB.
 *        The stream usage of the audio renderer must be {@link OH_AudioStream_Usage#AUDIOSTREAM_USAGE_MUSIC},
 *        {@link OH_AudioStream_Usage#AUDIOSTREAM_USAGE_MOVIE} or
 *        {@link OH_AudioStream_Usage#AUDIOSTREAM_USAGE_AUDIOBOOK}.
 *        The latency mode of the audio renderer must be
 *        {@link OH_AudioStream_LatencyMode#AUDIOSTREAM_LATENCY_MODE_NORMAL}.
 *        OH_AudioRenderer routing through the high-resolution playback path does not support this operation.
 *
 * @since 20
 *
 * @param renderer Reference created by OH_AudioStreamBuilder_GenerateRenderer()
 * @param loudnessGain loudness gain to set which changes from -90.0 to 24.0. It is expressed in dB.
 * @return Function result code:
 *         {@link AUDIOSTREAM_SUCCESS} If the execution is successful.
 *         {@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of renderer is nullptr;
 *                                                 2.The param of loudnessGain is invalid.
 *         {@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} This audio renderer is not supported to set loudness gain.
 *         {@link AUDIOSTREAM_ERROR_SYSTEM}:
 *                                          1.Crash or blocking occurs in system process.
 *                                          2.Other unexpected error from internal system.
 */
OH_AudioStream_Result OH_AudioRenderer_SetLoudnessGain(OH_AudioRenderer* renderer, float loudnessGain);

/**
 * Get the loudness gain of current renderer.
 *
 * @since 20
 *
 * @param renderer Reference created by OH_AudioStreamBuilder_GenerateRenderer()
 * @param loudnessGain Pointer to a variable to receive the loudness gain.
 * @return Function result code:
 *         {@link AUDIOSTREAM_SUCCESS} If the execution is successful.
 *         {@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of renderer is nullptr;
 *                                                 2.The param of loudnessGain is nullptr.
 *         {@link AUDIOSTREAM_ERROR_SYSTEM}:
 *                                          1.Crash or blocking occurs in system process.
 *                                          2.Other unexpected error from internal system.
 */
OH_AudioStream_Result OH_AudioRenderer_GetLoudnessGain(OH_AudioRenderer* renderer, float* loudnessGain);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_ROUTING_MANAGER_H
/** @} */