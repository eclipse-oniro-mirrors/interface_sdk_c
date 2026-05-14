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
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 26.0.0
 */

/**
 * @file native_audio_debugging_manager.h
 *
 * @brief Declare audio debugging manager related interfaces.
 *
 * This file interfaces are used for the creation of AudioDebuggingManager.
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 26.0.0
 */

#ifndef NATIVE_AUDIO_DEBUGGING_MANAGER_H
#define NATIVE_AUDIO_DEBUGGING_MANAGER_H

#include "native_audio_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Declare the audio debugging manager.
 *     Audio debugging manager provides many functions for developer
 *     to get the information about audio system runtime info.
 *
 * @since 26.0.0
 */
typedef struct OH_AudioDebuggingManager OH_AudioDebuggingManager;
typedef struct OH_AudioRendererStruct OH_AudioRenderer;
typedef struct OH_AudioCapturerStruct OH_AudioCapturer;
typedef struct OH_AudioLoopbackStruct OH_AudioLoopback;
typedef struct OH_AudioSessionStruct OH_AudioSession;


/**
 * @brief Fetch the audio debugging manager handle, which is a singleton.
 *
 * @param debugManager output parameter to get {@link #OH_AudioDebuggingManager}.
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}
 *         1.The param of debugManager is nullptr;
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioDebuggingManager(OH_AudioDebuggingManager **debugManager);

/**
 * @brief Print Single App Audio Runtime Snapshot
 *
 * @param debugManager {@link OH_AudioDebuggingManager} handle provided by
 *     {@link OH_AudioManager_GetAudioDebuggingManager}.
 * @param fd is a file handle, indicates the location where the snapshot information is stored.
 *     If the fd is less than 0, the snapshot information is stored in the pipeline log.
 *     Otherwise, the snapshot is stored in the file pointed to by the fd handle.
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintAppInfo(OH_AudioDebuggingManager *debugManager, int32_t fd);

/**
 * @brief Print AudioRenderer Runtime Snapshot
 *
 * @param debugManager {@link OH_AudioDebuggingManager} handle provided by
 *     {@link OH_AudioManager_GetAudioDebuggingManager}.
 * @param renderer is a pointer. Pointer to the AudioRenderer whose runtime snapshot needs to be displayed.
 * @param fd is a file handle, indicates the location where the snapshot information is stored.
 *     If the fd is less than 0, the snapshot information is stored in the pipeline log.
 *     Otherwise, the snapshot is stored in the file pointed to by the fd handle.
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} invalid param
 *     {@link #AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE} renderer is in illegal state
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintRendererInfo(
    OH_AudioDebuggingManager *debugManager, OH_AudioRenderer *renderer, int32_t fd);

/**
 * @brief Print AudioCapturer Runtime Snapshot
 *
 * @param debugManager {@link OH_AudioDebuggingManager} handle provided by
 *     {@link OH_AudioManager_GetAudioDebuggingManager}.
 * @param capturer is a pointer. Pointer to the AudioCapturer whose runtime snapshot needs to be displayed.
 * @param fd is a file handle, indicates the location where the snapshot information is stored.
 *     If the fd is less than 0, the snapshot information is stored in the pipeline log.
 *     Otherwise, the snapshot is stored in the file pointed to by the fd handle.
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} invalid param
 *     {@link #AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE} capturer is in illegal state
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintCapturerInfo(
    OH_AudioDebuggingManager *debugManager, OH_AudioCapturer *capturer, int32_t fd);

/**
 * @brief Print AudioLoopback Runtime Snapshot
 *
 * @param debugManager {@link OH_AudioDebuggingManager} handle provided by
 *     {@link OH_AudioManager_GetAudioDebuggingManager}.
 * @param loopback is a pointer. Pointer to the AudioLoopback whose runtime snapshot needs to be displayed.
 * @param fd is a file handle, indicates the location where the snapshot information is stored.
 *     If the fd is less than 0, the snapshot information is stored in the pipeline log.
 *     Otherwise, the snapshot is stored in the file pointed to by the fd handle.
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} invalid param
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintLoopbackInfo(
    OH_AudioDebuggingManager *debugManager, OH_AudioLoopback *loopback, int32_t fd);

/**
 * @brief Print AudioSession Runtime Snapshot
 *
 * @param debugManager {@link OH_AudioDebuggingManager} handle provided by
 *     {@link OH_AudioManager_GetAudioDebuggingManager}.
 * @param session is a pointer. Pointer to the AudioSession whose runtime snapshot needs to be displayed.
 * @param fd is a file handle, indicates the location where the snapshot information is stored.
 *     If the fd is less than 0, the snapshot information is stored in the pipeline log.
 *     Otherwise, the snapshot is stored in the file pointed to by the fd handle.
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} invalid param
 *     {@link #AUDIOCOMMON_RESULT_ERROR_UNSUPPORTED} currently unsupported
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintSessionInfo(
    OH_AudioDebuggingManager *debugManager, OH_AudioSession *session, int32_t fd);



#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_DEBUGGING_MANAGER_H
/** @} */
