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
 * @brief AVRecorder enables media recording and supports configuration of recording parameters and real-time status
 * callback. It is suitable for scenarios where audio and video need to be recorded and saved as files, such as video
 * call recording and voice notes.<br>
 * You can refer to the corresponding development guide and samples based on your development requirements.<br>
 * - [Using AVRecorder to Record Audio (C/C++)](../../../media/media/using-ndk-avrecorder-for-audio-recording.md)<br>
 * - [Using AVRecorder to Record Videos (C/C++)](../../../media/media/using-ndk-avrecorder-for-video-recording.md)<br>
 *
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 * @}
 */
/**
 * @file avrecorder.h
 *
 * @brief Defines the AVRecorder APIs. AVRecorder enables media recording and supports audio and video data collection
 * and recording, complete status management and callback listening, flexible encoder selection, and parameter
 * configuration. It is suitable for scenarios where audio and video need to be recorded and saved as files.
 * 
 * @include <multimedia/player_framework/avrecorder.h>
 * @library libavrecorder.so
 * @kit MediaKit
 * @since 18
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_H

#include <stdbool.h>
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
 * AVRECORDER_IDLE state. After using the AVRecorder instance, you must call
 * [OH_AVRecorder_Release]{@link OH_AVRecorder_Release} to release resources to prevent resource leaks.
 * 
 * @return Pointer to the **OH_AVRecorder** instance created if the operation is successful; **nullptr** otherwise. If
 *     the operation is successful, this parameter is used in the subsequent recording operations such as **Prepare**,
 *     **Start**, and **Pause**.
 * @since 18
*/
OH_AVRecorder *OH_AVRecorder_Create(void);

/**
 * @brief Sets AVRecorder parameters to prepare for recording. This function must be called after
 * [OH_AVRecorder_Create]{@link OH_AVRecorder_Create} and before [OH_AVRecorder_Start]{@link OH_AVRecorder_Start}. After
 * this function is successfully called, the AVRecorder transitions to the **AVRECORDER_PREPARED** state.<br>If
 * video-related parameters are not set, only audio is recorded. Similarly, if audio-related parameters are not set,
 * only video is recorded.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @param config [in] Pointer to the **OH_AVRecorder_Config** instance, which is used to configure parameters of the
 *     audio and video to be recorded, including the encoding format, sampling rate, and resolution. If video-related
 *     parameters are not set, only audio is recorded. If audio-related parameters are not set, only video is recorded.
 *     The value cannot be **nullptr**. Otherwise, **AV_ERR_INVALID_VAL** is returned.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** or **config** is **nullptr** or the preparation
 *         fails.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Prepare(OH_AVRecorder *recorder, OH_AVRecorder_Config *config);

/**
 * @brief Obtains the AVRecorder configuration. This function must be called after
 * [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare}. Typical use scenarios include checking whether the
 * configuration parameters are correct before recording starts and displaying the current recording settings on the UI.
 * <br>**config** must be set to **nullptr**. The framework layer allocates and releases the memory in a unified manner
 * to avoid leaks or double freeing.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @param config [out] Pointer to the pointer to the **OH_AVRecorder_Config** instance, which is used to obtain the
 *     current recording parameter configuration. **config** must be set to **nullptr**. The framework layer allocates
 *     and releases the memory in a unified manner to avoid leaks or double freeing. After the call is successful,
 *     **config** points to the configuration instance allocated by the framework layer.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or **config** is not nullptr.
 *     {@link AV_ERR_NO_MEMORY}: The memory fails to be allocated due to insufficient memory. Release resources and try
 *         again.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_GetAVRecorderConfig(OH_AVRecorder *recorder, OH_AVRecorder_Config **config);

/**
 * @brief Obtains an input surface. This function must be called after
 * [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} and before [OH_AVRecorder_Start]{@link OH_AVRecorder_Start}.<br>
 * **window** must be set to nullptr. The framework layer allocates and releases the memory in a unified manner to avoid
 * issues with memory management, such as leaks or double freeing.<br>The caller obtains the **surfaceBuffer** from this
 * surface and fills in data of the video to be recorded.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @param window [out] Pointer to the pointer to the **OHNativeWindow** instance, which is used to obtain the input
 *     surface. **window** must be set to **nullptr**. The framework layer allocates and releases the memory in a
 *     unified manner to avoid leaks or double freeing. After the call is successful, **window** points to the
 *     **OHNativeWindow** instance allocated by the framework layer. The caller can obtain the surface from this
 *     instance and fill in video data. If **window** is not **nullptr**, the error **AV_ERR_INVALID_VAL** is returned.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or **window** is not nullptr.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_GetInputSurface(OH_AVRecorder *recorder, OHNativeWindow **window);

/**
 * @brief Updates the video rotation angle. Typical use scenarios include adjusting the video orientation when the
 * device is switched between landscape and portrait modes, and setting the video rotation angle based on the camera
 * image capture direction. This function must be called after [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} and
 * before [OH_AVRecorder_Start]{@link OH_AVRecorder_Start}.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @param rotation [in] Video rotation angle, in degrees (°). The options are as follows: **0°**: no rotation,
 *     applicable to recording in the normal orientation; **90°**: rotation by 90°, applicable to adjusting the video
 *     orientation when the device is switched to the landscape mode clockwise; **180°**: rotation by 180°, applicable
 *     to recording in the inverted direction; **270°**: rotation by 270°, applicable to adjusting the video direction
 *     when the device is switched to the landscape mode counterclockwise. The value must be one of the preceding
 *     values. If another angle is passed, **AV_ERR_INVALID_VAL** is returned.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr, **rotation** is invalid, or the video
 *         rotation angle update fails.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_UpdateRotation(OH_AVRecorder *recorder, int32_t rotation);

/**
 * @brief Starts recording. This function must be called after [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} is
 * called. After this function is successfully called, the AVRecorder transitions to the **AVRECORDER_STARTED** state.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or recording fails to start.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Start(OH_AVRecorder *recorder);

/**
 * @brief Pauses recording. This function must be called after [OH_AVRecorder_Start]{@link OH_AVRecorder_Start} is
 * called. After this function is successfully called, the AVRecorder transitions to the **AVRECORDER_PAUSED** state.
 * <br>Then, you can call [OH_AVRecorder_Resume]{@link OH_AVRecorder_Resume} to resume recording, and the AVRecorder
 * transitions the AVRECORDER_STARTED state again.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or recording fails to pause.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Pause(OH_AVRecorder *recorder);

/**
 * @brief Resumes recording. This function must be called after [OH_AVRecorder_Pause]{@link OH_AVRecorder_Pause} is
 * called. After this function is successfully called, the AVRecorder transitions to the **AVRECORDER_STARTED** state.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or recording fails to resume.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Resume(OH_AVRecorder *recorder);

/**
 * @brief Stops recording. This function must be called after [OH_AVRecorder_Start]{@link OH_AVRecorder_Start} is
 * called. After this function is successfully called, the AVRecorder transitions to the **AVRECORDER_STOPPED** state.
 * <br>For audio-only recording, you can call [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} again for
 * re-recording.<br>For video-only recording or audio and video recording, you can call
 * [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} and
 * [OH_AVRecorder_GetInputSurface]{@link OH_AVRecorder_GetInputSurface} again for re-recording.<br>When
 * [OH_AVRecorder_FileGenerationMode]{@link OH_AVRecorder_FileGenerationMode} is used during media file creation, the
 * [OH_MediaAsset]{@link OH_MediaAsset} object is called back to the app through
 * [OH_AVRecorder_SetUriCallback]{@link OH_AVRecorder_SetUriCallback} after the **stop** operation is complete.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or recording fails to stop.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Stop(OH_AVRecorder *recorder);

/**
 * @brief Resets the recording state. This function must be called when the AVRecorder is not in the AVRECORDER_RELEASED
 * state. After this function is successfully called, the AVRecorder transitions to the AVRECORDER_IDLE state. Typical
 * use scenarios include reconfiguring parameters for a new round of recording after the previous recording is complete,
 * and resetting the AVRecorder to the initial state and starting recording again after an error occurs during
 * recording.<br>For audio-only recording, you can call [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} again for
 * re-recording.<br>For video-only recording or audio and video recording, you can call
 * [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} and
 * [OH_AVRecorder_GetInputSurface]{@link OH_AVRecorder_GetInputSurface} again for re-recording.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or recording fails to reset.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Reset(OH_AVRecorder *recorder);

/**
 * @brief Releases recording resources. This function must be called when the AVRecorder is not in the
 * **AVRECORDER_RELEASED** state. After this function is successfully called, the AVRecorder transitions to the
 * **AVRECORDER_RELEASED** state.<br>After this function is called, the recorder memory is released. The app layer must
 * explicitly set the recorder pointer to **nullptr** to avoid access to wild pointers. After the resources are
 * released, you can no longer perform any operation on the **OH_AVRecorder** instance.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or recording fails to release.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Release(OH_AVRecorder *recorder);

/**
 * @brief Obtains information about the available encoders of the AVRecorder. This API must be called when the
 * AVRecorder is not in the **AVRECORDER_RELEASED** or **AVRECORDER_ERROR** state. Typical use scenarios include
 * querying the encoders supported by the device when the app is started, selecting a proper encoding format based on
 * the available encoders, and displaying the list of available encoders on the encoder selection screen.<br>**info**
 * must be set to **nullptr**. The framework layer allocates and releases the memory in a unified manner to avoid leaks
 * or double freeing.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @param info [out] Pointer to the **OH_AVRecorder_EncoderInfo** instance, which is used to obtain the array of
 *     available encoder information. **info** must be set to **nullptr**. The framework layer allocates and releases
 *     the memory in a unified manner to avoid leaks or double freeing. After the call is successful, **info** points to
 *     the encoder information array allocated by the framework layer.
 * @param length [out] Number of elements in the array of available encoders. This is an output parameter. The value
 *     cannot be **nullptr**. After the call is successful, the value of **length** indicates the number of encoder
 *     information elements in the **info** array. This parameter is used together with the **info** parameter.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr or **info** is not nullptr.
 *     {@link AV_ERR_NO_MEMORY}: The memory fails to be allocated due to insufficient memory. Release resources and try
 *         again.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_GetAvailableEncoder(OH_AVRecorder *recorder, OH_AVRecorder_EncoderInfo **info,
    int32_t *length);

/**
 * @brief Sets a state change callback so that the application can respond to state change events generated by the
 * AVRecorder. This function must be called before [OH_AVRecorder_Start]{@link OH_AVRecorder_Start}.<br>An app can set
 * only one state change callback. If the app set multiple callbacks, the last one set will take effect.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @param callback [in] State callback function, which is used to receive AVRecorder state change events. This callback
 *     is triggered when the AVRecorder state changes, for example, when recording starts, pauses, or stops. The value
 *     must be a valid function pointer and cannot be **nullptr**.
 * @param userData [in] Pointer to the custom data, which is passed to the callback function when the state change
 *     callback function is triggered and can be used by the app layer. If custom data does not need to be passed, pass
 *     **nullptr**.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** or **callback** is nullptr.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_SetStateCallback(
    OH_AVRecorder *recorder, OH_AVRecorder_OnStateChange callback, void *userData);

/**
 * @brief Sets an error callback so that the application can respond to error events generated by the AVRecorder. This
 * function must be called before [OH_AVRecorder_Start]{@link OH_AVRecorder_Start}.<br>An app can set only one error
 * callback. If the app set multiple callbacks, the last one set will take effect.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @param callback [in] Error callback, which is used to receive AVRecorder error events. This callback is triggered
 *     when an error occurs during recording, for example, when the encoder is abnormal or the file fails to be written.
 *     The value must be a valid function pointer and cannot be **nullptr**.
 * @param userData [in] Pointer to the custom data, which is passed to the callback function when the error callback
 *     function is triggered and can be used by the app layer. If custom data does not need to be passed, pass
 *     **nullptr**.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** or **callback** is nullptr.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_SetErrorCallback(OH_AVRecorder *recorder, OH_AVRecorder_OnError callback, void *userData);

/**
 * @brief Sets a URI callback. When [OH_AVRecorder_FileGenerationMode]{@link OH_AVRecorder_FileGenerationMode} is used
 * during media file creation, this callback is triggered after the [OH_AVRecorder_Stop]{@link OH_AVRecorder_Stop}
 * operation is complete, and the [OH_MediaAsset]{@link OH_MediaAsset} object is called back to the app. Typical use
 * scenarios include obtaining the URI of the output file for file sharing or display after the recording is complete,
 * and updating the file list in the app based on the URI. This function must be called before
 * [OH_AVRecorder_Start]{@link OH_AVRecorder_Start}.<br>An app can set only one URI callback. If the app set multiple
 * callbacks, the last one set will take effect.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @param callback [in] URI callback used to receive the resource file created by the system. This callback is triggered
 *     only after the recording is complete. You need to set **FileGenerationMode** to the mode where the system creates
 *     media files in the recording configuration. The value must be a valid function pointer and cannot be **nullptr**.
 * @param userData [in] Pointer to the custom data, which is passed to the callback function when the URI callback
 *     function is triggered and can be used by the app layer. If custom data does not need to be passed, pass
 *     **nullptr**.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** or **callback** is nullptr.
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_SetUriCallback(OH_AVRecorder *recorder, OH_AVRecorder_OnUri callback, void *userData);

/**
 * @brief Sets whether to enable the mute interruption mode. This mode controls the behavior when the audio stream is
 * interrupted. The value **true** indicates that the recording is muted when the audio stream is interrupted. The value
 * **false** indicates that the recording stops when the audio stream is interrupted. The default value is **false**.
 * Typical use scenarios: In scenarios where continuous recording is required, such as conference recording, enable the
 * mute interruption mode to ensure that the recording remains muted when an incoming call interrupts the recording,
 * preventing loss of subsequent content. In normal recording scenarios, disable the mute interruption mode so that the
 * recording stops directly when interrupted, saving storage space. This function must be called before
 * [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare}.
 * 
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @param muteWhenInterrupted [in] Whether to enable the mute interruption mode. The value **true** indicates that the
 *     mute interruption mode is enabled. When the audio stream is interrupted, the recording is muted. The value
 *     **false** indicates that the mute interruption mode is disabled. When the audio stream is interrupted, the
 *     recording stops. The default value is **false**.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** is nullptr.
 *     {@link AV_ERR_INVALID_STATE}: This function cannot be called in the current state. It must be called before
 *         [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare}.
 * @since 20
 */
OH_AVErrCode OH_AVRecorder_SetWillMuteWhenInterrupted(OH_AVRecorder *recorder, bool muteWhenInterrupted);

/**
 * @brief Obtains the maximum amplitude of the current audio capturer. Typical use scenarios include real-time display
 * of the volume level during audio recording, audio waveform display, and checking whether the recording is muted. The
 * return value is the maximum amplitude between the last two calls. For example, if the maximum amplitude is obtained
 * once at 1s and then the API is called again at 2s, the return value is the maximum amplitude between 1s and 2s. This
 * function must be called after [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} and before
 * [OH_AVRecorder_Stop]{@link OH_AVRecorder_Stop}.
 *
 * @param recorder [in] Pointer to the OH_AVRecorder instance.
 * @param amplitude [out] Maximum audio amplitude obtained, indicating the maximum amplitude of the audio signal between
 *     the last two calls. This is an output parameter. The value cannot be **nullptr**. Otherwise,
 *     **AV_ERR_INVALID_VAL** is returned.
 * @return Function result code.
 *     {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** or **amplitude** is **nullptr**.
 *     {@link AV_ERR_INVALID_STATE}: This function cannot be called in the current state. It must be called after
 *         [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} and before
 *         [OH_AVRecorder_Stop]{@link OH_AVRecorder_Stop}.
 *     {@link AV_ERR_NO_MEMORY}: Insufficient memory. Release resources and try again.
 *     {@link AV_ERR_UNKNOWN}: This is an unknown error. Check the log for details.
 * @since 26.0.0
 */
OH_AVErrCode OH_AVRecorder_GetAudioCapturerMaxAmplitude(OH_AVRecorder *recorder, int32_t* amplitude);

/**
 * @brief Sets the metadata information to record. Typical use scenarios include adding custom metadata such as author
 * information, copyright information, geographical location, and recording time to recorded video or audio files. If
 * the **metadata** parameter contains the same key as that in **config.metadata.customInfo** (see
 * [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} and [OH_AVRecorder_Config]{@link OH_AVRecorder_Config}), the
 * value of the former will overwrite that of the latter. This function must be called after
 * [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} and before [OH_AVRecorder_Stop]{@link OH_AVRecorder_Stop}.
 *
 * @param recorder [in] Pointer to an OH_AVRecorder instance
 * @param metadata [in] Metadata embedded into the recorded media file. The value cannot be **nullptr**. Otherwise,
 *     **AV_ERR_INVALID_VAL** is returned. The value is a string key-value pair. The key must start with
 *     **com.openharmony**. If not, the key-value pair will be ignored. The value contains a maximum of 256 bytes. If
 *     the value is out of range, **AV_ERR_INVALID_VAL** is returned.
 * @return Function result code.
 *     {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The input parameter **recorder** or **metadata** is **nullptr**, or the value length
 *         in **metadata** exceeds 256 bytes.
 *     {@link AV_ERR_INVALID_STATE}: This function cannot be called in the current state. It must be called after
 *         [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} and before
 *         [OH_AVRecorder_Stop]{@link OH_AVRecorder_Stop}.
 *     {@link AV_ERR_NO_MEMORY}: Insufficient memory. Release resources and try again.
 *     {@link AV_ERR_UNKNOWN}: This is an unknown error. Check the log for details.
 * @since 26.0.0
 */
OH_AVErrCode OH_AVRecorder_SetMetadata(OH_AVRecorder *recorder, const OH_AVFormat *metadata);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_H
