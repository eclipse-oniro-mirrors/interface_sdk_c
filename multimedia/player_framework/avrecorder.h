/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
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
 * @addtogroup AVRecorder
 * @{
 *
 * @brief Provides APIs of request capability for Recorder.
 *
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 * @}
 */
/**
 * @file avrecorder.h
 *
 * @brief The file declares the AVRecorder APIs. Applications can use the APIs to record media data.
 * 
 * @kit MediaKit
 * @library libavrecorder.so
 * @since 18
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_H

#include <stdint.h>
#include <stdio.h>
#include "avrecorder_base.h"
#include "native_averrors.h"
#include "native_window/external_window.h"
#include "native_avformat.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an AVRecorder instance. After this function is successfully called, the AVRecorder transitions to the
 * AVRECORDER_IDLE state.
 * 
 * @return Pointer to the OH_AVRecorder instance created if the operation is successful; nullptr otherwise.
 * @since 18
*/
OH_AVRecorder *OH_AVRecorder_Create(void);

/**
 * @brief Sets AVRecorder parameters to prepare for recording. This function must be called after {@link OH_AVRecorder_Create}
 * is successfully triggered. After this function is successfully called, the AVRecorder transitions to the
 * AVRECORDER_PREPARED state.
 * To record only audio, you do not need to set video parameters. Similarly, to record only video, you do not need to
 * set audio parameters.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param config Pointer to the OH_AVRecorder_Config instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or the preparation fails.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Prepare(OH_AVRecorder *recorder, OH_AVRecorder_Config *config);

/**
 * @brief Obtains the AVRecorder configuration. This function must be called after the recording preparation is
 * complete.
 * **config** must be set to nullptr. The framework layer allocates and releases the memory in a unified manner to
 * avoid issues with memory management, such as leaks or double freeing.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param config Pointer to the OH_AVRecorder_Config instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or **config** is not nullptr.
 * {@link AV_ERR_NO_MEMORY}: The memory fails to be allocated due to insufficient memory.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_GetAVRecorderConfig(OH_AVRecorder *recorder, OH_AVRecorder_Config **config);

/**
 * @brief Obtains an input surface. This function must be called after {@link OH_AVRecorder_Prepare} is successfully triggered and before {@link OH_AVRecorder_Start}
 * is called.
 * The caller obtains the **surfaceBuffer** from this surface and fills in the corresponding video data.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param window Pointer to the OHNativeWindow instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_GetInputSurface(OH_AVRecorder *recorder, OHNativeWindow **window);

/**
 * @brief Updates the video rotation angle. This function must be called after {@link OH_AVRecorder_Prepare} is successfully triggered and before {@link OH_AVRecorder_Start}
 * is called.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param rotation Video rotation angle, in degrees. The value must be an integer in the range [0, 90, 180, 270].
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr, **rotation** is invalid, or the update
 * operation fails.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_UpdateRotation(OH_AVRecorder *recorder, int32_t rotation);

/**
 * @brief Starts recording. This function must be called after {@link OH_AVRecorder_Prepare} is successfully triggered.
 * After this function is successfully called, the AVRecorder transitions to the AVRECORDER_STARTED state.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or recording fails to start.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Start(OH_AVRecorder *recorder);

/**
 * @brief Pauses recording. This function must be called after {@link OH_AVRecorder_Start} is successfully triggered
 * and the AVRecorder is in the AVRECORDER_STARTED state. After this function is successfully called, the AVRecorder
 * transitions to the AVRECORDER_PAUSED state.
 * Then, you can call {@link OH_AVRecorder_Resume} to resume recording, and the AVRecorder transitions the
 * AVRECORDER_STARTED state again.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or recording fails to pause.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Pause(OH_AVRecorder *recorder);

/**
 * @brief Resumes recording. This function must be called after {@link OH_AVRecorder_Pause} is successfully triggered
 * and the AVRecorder is in the AVRECORDER_PAUSED state. After this function is successfully called, the AVRecorder
 * transitions to the AVRECORDER_STARTED state.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or recording fails to resume.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Resume(OH_AVRecorder *recorder);

/**
 * @brief Stops recording. This function must be called after {@link OH_AVRecorder_Start} is successfully triggered.
 * After this function is successfully called, the AVRecorder transitions to the AVRECORDER_STOPPED state.
 * For audio-only recording, you can call {@link OH_AVRecorder_Prepare} again for re-recording.
 * For video-only recording or audio and video recording, you can call {@link OH_AVRecorder_Prepare} and {@link OH_AVRecorder_GetInputSurface}
 * again for re-recording.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or recording fails to stop.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Stop(OH_AVRecorder *recorder);

/**
 * @brief Resets the recording state. This function must be called when the AVRecorder is not in the
 * AVRECORDER_RELEASED state. After this function is successfully called, the AVRecorder transitions to the
 * AVRECORDER_IDLE state.
 * For audio-only recording, you can call {@link OH_AVRecorder_Prepare} again for re-recording.
 * For video-only recording or audio and video recording, you can call {@link OH_AVRecorder_Prepare} and {@link OH_AVRecorder_GetInputSurface}
 * again for re-recording.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or recording fails to reset.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Reset(OH_AVRecorder *recorder);

/**
 * @brief Releases recording resources. After this function is successfully called, the AVRecorder transitions to the
 * AVRECORDER_RELEASED state.
 * The recorder memory will be released. The application layer must explicitly set the recorder to nullptr to avoid
 * access to wild pointers. After the resources are released, you can no longer perform any operation on the
 * OH_AVRecorder instance.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or recording fails to release.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Release(OH_AVRecorder *recorder);

/**
 * @brief Obtains the available encoders and encoder information of the AVRecorder.
 * **info** must be set to nullptr. The framework layer allocates and releases the memory in a unified manner to avoid
 * issues with memory management, such as leaks or double freeing.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param info Pointer to the OH_AVRecorder_EncoderInfo instance.
 * @param length Pointer to the number of available encoders.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr.
 * {@link AV_ERR_NO_MEMORY}: The memory fails to be allocated due to insufficient memory.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_GetAvailableEncoder(OH_AVRecorder *recorder, OH_AVRecorder_EncoderInfo **info,
    int32_t *length);

/**
 * @brief Sets a state callback so that the application can respond to state change events generated by the AVRecorder.
 * This function must be called before {@link OH_AVRecorder_Start} is called.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param callback Status callback function.
 * @param userData Pointer to user-defined data.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** or **callback** is nullptr.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_SetStateCallback(
    OH_AVRecorder *recorder, OH_AVRecorder_OnStateChange callback, void *userData);

/**
 * @brief Sets an error callback so that the application can respond to error events generated by the AVRecorder. This
 * function must be called before {@link OH_AVRecorder_Start} is called.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param callback Error callback function.
 * @param userData Pointer to user-defined data.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** or **callback** is nullptr.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_SetErrorCallback(OH_AVRecorder *recorder, OH_AVRecorder_OnError callback, void *userData);

/**
 * @brief Sets a URI callback so that the application can respond to URI events generated by the AVRecorder. This
 * function must be called before {@link OH_AVRecorder_Start} is called.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param callback Callback used to return the result.
 * @param userData Pointer to user-defined data.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** or **callback** is nullptr.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_SetUriCallback(OH_AVRecorder *recorder, OH_AVRecorder_OnUri callback, void *userData);

/**
 * @brief Sets whether to enable the mute interruption mode.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param muteWhenInterrupted Sets whether to enable the mute interruption mode. The value **true** indicates that the
 * application remains muted instead of being interrupted when recording is required. The value **false** indicates
 * that the application stops recording instead of remain muted when the recording is interrupted.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** or **callback** is nullptr.
 * {@link AV_ERR_INVALID_STATE}: The function is called in an invalid state. It must be in the prepared state.
 * @since 20
 */
OH_AVErrCode OH_AVRecorder_SetWillMuteWhenInterrupted(OH_AVRecorder *recorder, bool muteWhenInterrupted);

/**
 * @brief Obtains the maximum amplitude of the current audio capturer.
 * The amplitude value is the max value from the last call to the current call.
 * For example, if you have obtained the maximum amplitude at 1s, and you call this API again at 2s,
 * then the return value is the maximum amplitude within the duration from 1s to 2s.
 *
 * This API can be called only after the **prepare()** API is called.
 * If this API is called after **stop()** is successfully called, an error is reported.
 *
 * @param recorder Pointer to an OH_AVRecorder instance
 * @param amplitude The max amplitude value of audio capturer
 * @return Function result code.
 *         {@link AV_ERR_OK}: the execution is successful.
 *         {@link AV_ERR_INVALID_VAL}: input recorder is nullptr or amplitude is nullptr.
 *         {@link AV_ERR_INVALID_STATE}: function called in invalid state.
 *         {@link AV_ERR_NO_MEMORY}: failed to malloc memory.
 *         {@link AV_ERR_UNKNOWN}: unknown error.
 *
 * @since 26.0.0
 */
OH_AVErrCode OH_AVRecorder_GetAudioCapturerMaxAmplitude(OH_AVRecorder *recorder, int32_t* amplitude);

/**
 * @brief Set metadata (key-value pairs) for the recording file of the recorder.
 * This metadata overwrites the value in config.metadata.customInfo (see {prepare()} and {OH_AVRecorder_Config})
 * if they have same key.
 * This API can be called only after the **prepare()** API is called, before stop recorder.
 *
 * @param recorder Pointer to an OH_AVRecorder instance
 * @param metadata The key-value pairs added to the the recording file.
 *                 The key string should start with "com.openharmony.",
 *                 the length of value can't be more than 256 bytes.
 * @return Function result code.
 *         {@link AV_ERR_OK}: the execution is successful.
 *         {@link AV_ERR_INVALID_VAL}: input recorder is nullptr or metadata is nullptr
 *                                     or the length of value exceed max length.
 *         {@link AV_ERR_INVALID_STATE}: function called in invalid state.
 *         {@link AV_ERR_NO_MEMORY}: failed to malloc memory.
 *         {@link AV_ERR_UNKNOWN}: unknown error.
 *
 * @since 26.0.0
 */
OH_AVErrCode OH_AVRecorder_SetMetadata(OH_AVRecorder *recorder, const OH_AVFormat *metadata);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_H
