/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup AVScreenCapture
 * @{
 *
 * @brief Provides APIs of request capability for Screen Capture.
 * @since 10
 */
/**
 * @file native_avscreen_capture.h
 *
 * @brief The file declares the APIs used to create an OH_AVScreenCapture instance.
 * 
 * @library libnative_avscreen_capture.so
 * @syscap SystemCapability.Multimedia.Media.AVScreenCapture
 * @kit MediaKit
 * @since 10
 */

#ifndef NATIVE_AVSCREEN_CAPTURE_H
#define NATIVE_AVSCREEN_CAPTURE_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "native_avscreen_capture_errors.h"
#include "native_avscreen_capture_base.h"
#include "native_window/external_window.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an OH_AVScreenCapture instance.
 * You can release the instance by calling {@link OH_AVScreenCapture_Release}.
 * 
 * @return Pointer to the OH_AVScreenCapture instance.
 * @since 10
 */
struct OH_AVScreenCapture *OH_AVScreenCapture_Create(void);

/**
 * @brief Initializes parameters related to an {@link OH_AVScreenCapture} instance, including audio sampling parameters
 * for external capture using microphones (optional), audio sampling parameters for internal capture, and video
 * resolution parameters.
 * In the scenario where screen recording files are stored, the application must ensure that the video encoding
 * parameters, video sampling parameters, audio encoding parameters, audio sampling parameters for internal capture,
 * and audio sampling parameters for external capture using microphones (optional) are valid.
 * In the scenario where screen capture streams are generated, the application must ensure that either audio sampling
 * parameters for internal capture or video sampling parameters are valid, or both are valid, and audio sampling
 * parameters for external capture using microphones are valid (optional).
 * The members of the struct variables are not initialized during initialization. Therefore, the application must
 * correctly set the parameters based on the use scenario. You are advised to set all memory bytes of the
 * OH_AVScreenCaptureConfig struct variables to **0**, and then set valid parameters based on the screen capture
 * scenario.
 * If both **audioSampleRate** and **audioChannels** in the {@link OH_AudioCaptureInfo} struct are **0**, the
 * OH_AVScreenCapture instance ignores the corresponding audio parameters and does not collect the audio data.
 * If both **videoFrameWidth** and **videoFrameHeight** in the {@link OH_VideoCaptureInfo} struct are **0**, the
 * OH_AVScreenCapture instance ignores the corresponding video parameters and does not collect the screen data.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param config Parameters related to screen capture initialization.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The configuration fails to be
 * initialized.
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_Init(struct OH_AVScreenCapture *capture,
    OH_AVScreenCaptureConfig config);

/**
 * @brief Starts screen capture and collects original streams.
 * After this function is called, the callback {@link OH_AVScreenCapture_OnBufferAvailable} can be used to check whether streams are generated, and the callback {@link OH_AVScreenCapture_OnStateChange}
 * can be used to check the startup status.
 * The application can obtain the original streams of screen capture by calling {@link OH_AVScreenCapture_AcquireAudioBuffer}
 * and {@link OH_AVScreenCapture_AcquireVideoBuffer}.
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_UNSUPPORT} (available since API version 20): The device does not support the operation.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The privacy permission fails to be
 * enabled or screen capture fails to start.
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StartScreenCapture(struct OH_AVScreenCapture *capture);

/**
 * @brief Stops screen capture. This function is used in pair with {@link OH_AVScreenCapture_StartScreenCapture}. After
 * calling this function, the application stops screen capture or screen share and releases the microphone.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. Screen capture fails to stop.
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StopScreenCapture(struct OH_AVScreenCapture *capture);

/**
 * @brief Starts screen recording, with recordings saved in files.
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_UNSUPPORT} (available since API version 20): The device does not support the operation.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The privacy permission fails to be
 * enabled or screen capture fails to start.
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StartScreenRecording(struct OH_AVScreenCapture *capture);

/**
 * @brief Stops screen recording. This function is used in pair with {@link OH_AVScreenCapture_StartScreenRecording}.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. Screen capture fails to stop.
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StopScreenRecording(struct OH_AVScreenCapture *capture);

/**
 * @brief Obtains an audio buffer. When calling this function, the application must allocate the memory of the
 * corresponding struct size to the audio buffer.
 * Starting from API version 12, you are advised to use {@link OH_AVScreenCapture_OnBufferAvailable} instead.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param audiobuffer Pointer to the struct for storing the audio buffer. This struct is used to obtain the information
 * about the audio buffer and the timestamp of the buffer.
 * @param type Type of the audio buffer, which is used to distinguish external streams recorded by the microphone from
 * internal streams played by the system.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** or **audiobuffer** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_NO_MEMORY}: The audio buffer fails to be allocated due to insufficient memory.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The privacy permission fails to be
 * enabled or the audio buffer fails to be obtained.
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_AcquireAudioBuffer(struct OH_AVScreenCapture *capture,
    OH_AudioBuffer **audiobuffer, OH_AudioCaptureSourceType type);

/**
 * @brief Obtains a video buffer. The application can call this function to obtain information such as the video buffer
 * and timestamp.
 * When a video buffer is no longer needed, call **OH_AVScreenCapture_ReleaseVideoBuffer** to release it.
 * Starting from API version 12, you are advised to use {@link OH_AVScreenCapture_OnBufferAvailable} instead.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param fence Pointer to parameters for synchronization display.
 * @param timestamp Pointer to the timestamp of the video frame, in nanosecond.
 * @param region Pointer to the coordinates related to video display.
 * @return OH_NativeBuffer object if the operation is successful. The application can call the APIs provided by the
 * OH_NativeBuffer object to obtain information such as the video buffer and resolution.
 * @since 10
 */
OH_NativeBuffer* OH_AVScreenCapture_AcquireVideoBuffer(struct OH_AVScreenCapture *capture,
    int32_t *fence, int64_t *timestamp, struct OH_Rect *region);

/**
 * @brief Releases an audio buffer. When an audio buffer is no longer needed, call this function to release it.
 * Starting from API version 12, you are advised to use {@link OH_AVScreenCapture_OnBufferAvailable} instead.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param type Type of the audio buffer, which is used to distinguish external streams recorded by the microphone from
 * internal streams played by the system.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The data callback has been set or the
 * audio buffer fails to be released.
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ReleaseAudioBuffer(struct OH_AVScreenCapture *capture,
    OH_AudioCaptureSourceType type);

/**
 * @brief Releases a video buffer. When a video buffer is no longer needed, call this function to release it.
 * Starting from API version 12, you are advised to use {@link OH_AVScreenCapture_OnBufferAvailable} instead.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The data callback has been set or the
 * vedio buffer fails to be released.
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ReleaseVideoBuffer(struct OH_AVScreenCapture *capture);

/**
 * @brief Sets a callback to listen for available video buffers and audio buffers and errors that occur during the
 * function calling.
 * Starting from API version 12, you are advised to use {@link OH_AVScreenCapture_SetErrorCallback} and {@link OH_AVScreenCapture_SetDataCallback}
 * instead.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param callback OH_AVScreenCaptureCallback struct, which stores related callback function pointers.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** or **callback** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The callback fails to be set.
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetCallback(struct OH_AVScreenCapture *capture,
    struct OH_AVScreenCaptureCallback callback);

/**
 * @brief Releases an OH_AVScreenCapture instance. This function is used in pair with {@link OH_AVScreenCapture_Create}.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The OH_AVScreenCapture instance fails to
 * be released.
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_Release(struct OH_AVScreenCapture *capture);

/**
 * @brief Enables or disables the microphone.
 * When **isMicrophone** is set to **true**, the microphone is enabled, and the original PCM data of the microphone can
 * be obtained by calling {@link OH_AVScreenCapture_StartScreenCapture} and {@link OH_AVScreenCapture_AcquireAudioBuffer}.
 * When **isMicrophone** is set to **false**, the obtained audio data is silent data.
 * By default, the microphone is enabled.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param isMicrophone Whether to enable the microphone.
 * **true** to enable, **false** to disable.
 * The default value is **true**.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The microphone fails to be enabled or
 * disabled.
 * @since 10
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetMicrophoneEnabled(struct OH_AVScreenCapture *capture,
    bool isMicrophone);

/**
 * @brief Sets a state change callback. This function must be called before screen capture starts.
 * The callback is triggered when the state changes during the running of an OH_AVScreenCapture instance.
 * A privacy dialog box is displayed to ask for user consent before screen capture starts. After a successful call to
 * this function, the following scenarios are possible:
 * 1. If the user agrees, the screen capture startup process starts. If screen capture starts successfully, the state
 * change callback is triggered to report the {@link OH_AVScreenCaptureStateCode}.OH_SCREEN_CAPTURE_STATE_STARTED status to notify the application of the startup success, with a screen capture notification displayed. If screen capture fails to start, the state change callback is triggered to report the failure information (for example, {@link OH_AVScreenCaptureStateCode}.
 * OH_SCREEN_CAPTURE_STATE_MIC_UNAVAILABLE if the microphone is unavailable), or the error processing callback {@link OH_AVScreenCapture_OnError}
 * is triggered to report the error information.
 * 2. If the user disagrees, the screen capture startup process stops. The state change callback is triggered to report
 * the {@link OH_AVScreenCaptureStateCode}.OH_SCREEN_CAPTURE_STATE_CANCELED status to notify the application of the
 * startup failure due to user rejection.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param callback State change callback.
 * @param userData Pointer to the user-defined data. The data is returned as an input parameter when the state change
 * callback is triggered.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** or **callback** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_NO_MEMORY}: The memory fails to be allocated due to insufficient memory.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The state callback fails to be set.
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetStateCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnStateChange callback, void *userData);

/**
 * @brief Sets a data processing callback. This function must be called before screen capture starts.
 * The callback is triggered when an audio buffer or a video buffer becomes available during the running of an
 * OH_AVScreenCapture instance.
 * The application needs to process microphone audio, internal audio, and video data based on the data type in the
 * callback. After the callback is triggered, the buffer is no longer valid.
 * A successful call to this function leads to the following scenarios:
 * 1. The callbacks {@link OH_AVScreenCaptureOnAudioBufferAvailable} and {@link OH_AVScreenCaptureOnVideoBufferAvailable}
 * set by calling {@link OH_AVScreenCapture_SetCallback} will no longer be triggered, even when an audio buffer or a
 * video buffer becomes available.
 * 2. A failure message is returned for a call to any of the following functions: {@link OH_AVScreenCapture_AcquireAudioBuffer},
 * {@link OH_AVScreenCapture_ReleaseAudioBuffer}, {@link OH_AVScreenCapture_AcquireVideoBuffer}, and {@link OH_AVScreenCapture_ReleaseVideoBuffer}.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param callback Data processing callback.
 * @param userData Pointer to the user-defined data. The data is returned as an input parameter when the data
 * processing callback is triggered.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** or **callback** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_NO_MEMORY}: The memory fails to be allocated due to insufficient memory.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The data callback fails to be set.
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetDataCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnBufferAvailable callback, void *userData);

/**
 * @brief Sets an error processing callback. This function must be called before screen capture starts.
 * The callback is triggered when an error occurs during the running of an OH_AVScreenCapture instance.
 * After a successful call to this function, the callback {@link OH_AVScreenCaptureOnError} set by calling {@link OH_AVScreenCapture_SetCallback}
 * will no longer be triggered, even when an error occurs in the OH_AVScreenCapture instance.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param callback Error processing callback.
 * @param userData Pointer to the user-defined data. The data is returned as an input parameter when the error
 * processing callback is triggered.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** or **callback** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_NO_MEMORY}: The memory fails to be allocated due to insufficient memory.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The error callback fails to be set.
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetErrorCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnError callback, void *userData);

/**
 * @brief Sets the callback for screen capture content changes. This function must be called before screen capture
 * starts.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param callback Pointer to the callback method instance for the screen capture content change event.
 * @param userData Pointer to the user-defined data. The data is returned as an input parameter when the error
 * processing callback is triggered.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** or **callback** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The screen capture callback fails to be
 * set.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetCaptureContentChangedCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnCaptureContentChanged callback, void *userData);

/**
 * @brief Starts screen capture in surface mode.
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance.
 * @param window Pointer to an OHNativeWindow instance.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture**, input parameter **window**, or **
 * windowSurface** pointed to by **window** is nullptr.
 * **AV_SCREEN_CAPTURE_ERR_UNSUPPORT** (available since API version 20): The device does not support the operation.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The privacy permission fails to be
 * enabled or screen capture with a surface fails to start.
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StartScreenCaptureWithSurface(struct OH_AVScreenCapture *capture,
    OHNativeWindow *window);

/**
 * @brief Sets whether the captured screen data should rotate.
 * When **canvasRotation** is set to **true**, rotation is enabled and the captured screen data remains upright.
 * The default value is **false**.
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param canvasRotation whether to rotate the canvas
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * **AV_SCREEN_CAPTURE_ERR_UNSUPPORT** (available since API version 20): The device does not support the operation.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. Canvas rotation fails to be set for
 * screen capture.
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetCanvasRotation(struct OH_AVScreenCapture *capture,
    bool canvasRotation);

/**
 * @brief Creates a content filter.
 * 
 * @return OH_AVScreenCapture_ContentFilter instance if the operation is successful; nullptr otherwise.
 * @since 12
 */
struct OH_AVScreenCapture_ContentFilter *OH_AVScreenCapture_CreateContentFilter(void);

/**
 * @brief Releases a content filter.
 * 
 * @param filter Pointer to the OH_AVScreenCapture_ContentFilter instance.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **filter** is nullptr.
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ReleaseContentFilter(struct OH_AVScreenCapture_ContentFilter *filter);

/**
 * @brief Adds audio content to a content filter.
 * 
 * @param filter Pointer to the OH_AVScreenCapture_ContentFilter instance.
 * @param content Pointer to the OH_AVScreenCaptureFilterableAudioContent instance.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **filter** is nullptr or the input parameter **content**
 * is invalid.
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ContentFilter_AddAudioContent(
    struct OH_AVScreenCapture_ContentFilter *filter, OH_AVScreenCaptureFilterableAudioContent content);

/**
 * @brief Sets a content filter for an OH_AVScreenCapture instance.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param filter Pointer to the OH_AVScreenCapture_ContentFilter instance.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** or **filter** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_UNSUPPORT}: The operation is not supported. For streams, the AudioCapturer API must be
 * called for the operation to take effect during the start.
 * For captured files, the Recorder API must be called for the operation to take effect during the start.
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ExcludeContent(struct OH_AVScreenCapture *capture,
    struct OH_AVScreenCapture_ContentFilter *filter);

/**
 * @brief Adds a list of window IDs to a ContentFilter instance.
 * 
 * @param filter Pointer to the OH_AVScreenCapture_ContentFilter instance.
 * @param windowIDs Pointer to the window IDs.
 * @param windowCount Length of the window ID list.
 * @return **AV_SCREEN_CAPTURE_ERR_OK** if the operation is successful; a specific error code if the operation fails.
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ContentFilter_AddWindowContent(
    struct OH_AVScreenCapture_ContentFilter *filter, int32_t *windowIDs, int32_t windowCount);

/**
 * @brief Adjusts the screen resolution.
 * This function is used to set the resolution of screen capture data. **width** indicates the screen width and **
 * height** indicates the screen height.
 * Currently, this function supports only the scenario of capturing streams, but not the scenario of storing captured
 * files. In addition, the caller of this function and the video data consumer must ensure that they support resolution
 * changes of the received video data.
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param width Video frame width of avscreeencapture, in px.
 * @param height Video frame height of avscreeencapture, in px.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * **AV_SCREEN_CAPTURE_ERR_UNSUPPORT** (available since API version 20): The device does not support the operation.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed.
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ResizeCanvas(struct OH_AVScreenCapture *capture,
    int32_t width, int32_t height);

/**
 * @brief Exempts privacy windows during screen capture.
 * Currently, all the IDs of the subwindows and main windows to skip must be passed in.
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param windowIDs Pointer of windowID list
 * @param windowCount length of windowID list
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * **AV_SCREEN_CAPTURE_ERR_UNSUPPORT** (available since API version 20): The device does not support the operation.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed.
 * @since 12
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SkipPrivacyMode(struct OH_AVScreenCapture *capture,
    int32_t *windowIDs, int32_t windowCount);

/**
 * @brief Sets the maximum frame rate for screen capture.
 * This function must be called after screen capture starts.
 *   
 * The maximum frame rate that can be configured is subject to the device's limitations and is ultimately governed by
 * the capabilities of the underlying system.
 * Although there is no limit on the maximum value of the input parameter, the maximum frame rate supported is 60 FPS.
 * If the input parameter value exceeds 60 FPS, 60 FPS is used. If the value does not exceed the upper limit, the
 * passed value is used.
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param frameRate max frame rate of video, in fps.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr, or the input parameter **
 * frameRate** is not supported.
 * **AV_SCREEN_CAPTURE_ERR_UNSUPPORT** (available since API version 20): The device does not support the operation.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed.
 * @since 14
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetMaxVideoFrameRate(struct OH_AVScreenCapture *capture,
    int32_t frameRate);

/**
 * @brief Sets whether to show the cursor.
 * 
 * @param capture Pointer to an OH_AVScreenCapture instance
 * @param showCursor The switch of the cursor
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * **AV_SCREEN_CAPTURE_ERR_UNSUPPORT** (available since API version 20): The device does not support the operation.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The cursor setting fails.
 * @since 15
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ShowCursor(struct OH_AVScreenCapture *capture,
    bool showCursor);

/**
 * @brief Sets or updates the capture area.
 * This function can be called before or after screen capture starts. The coordinates and dimensions provided must be
 * non-negative, and the capture area must not span multiple screens. If setting the area fails, the previously set
 * area is used for capturing.
 * 
 * @param capture capture Pointer to an OH_AVScreenCapture instance
 * @param displayId Indicates the screen index for setting area recording
 * @param area Pointer to an object describing the location and size of the region
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is a nullptr, the input **displayId** does
 * not exist, or the input **area** is abnormal.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetCaptureArea(struct OH_AVScreenCapture *capture, uint64_t displayId, OH_Rect* area);

/**
 * @brief Sets the highlight style for the screen capture area.
 * 
 * @param capture Pointer to OH_AVScreenCapture which want to set highlight style.
 * @param config the highlight parameters are to be set for this screen capture.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr or **config** is invalid.
 * @since 22
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetCaptureAreaHighlight(struct OH_AVScreenCapture *capture,
    OH_AVScreenCaptureHighlightConfig config);

/**
 * @brief Registers a callback to handle user selection results on the manual confirmation UI. This callback must be
 * invoked before screen capture starts.
 * 
 * @param capture Pointer to OH_AVScreenCapture which want to handle user selection info
 * @param callback user selection callback function, see {@link OH_AVScreenCapture_OnUserSelected}
 * @param userData The control block pointer passed by the application is carried to the application when it is
 * returned
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetSelectionCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnUserSelected callback, void *userData);

/**
 * @brief Obtains the screen capture object type selected by the user on the confirmation UI. This function is used in
 * the {@link OH_AVScreenCapture_OnUserSelected} callback. The **selection** pointer is destroyed after the callback is
 * complete.
 * 
 * @param selection Pointer to an OH_AVScreenCapture_UserSelectionInfo instance
 * @param type The capture object type selected by the user,
 * 0: represents the screen, 1: represents the window, 2: represents the app.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **selection** is nullptr.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_GetCaptureTypeSelected(OH_AVScreenCapture_UserSelectionInfo *selection, int32_t* type);

/**
 * @brief Obtains the display ID of the screen selected by the user for capture. This function is used in the {@link OH_AVScreenCapture_OnUserSelected}
 * callback. The **selection** pointer is destroyed after the callback is complete.
 * 
 * @param selection Pointer to an OH_AVScreenCapture_UserSelectionInfo instance
 * @param displayId Returns the screen ID value selected by the user
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **selection** is nullptr.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_GetDisplayIdSelected(OH_AVScreenCapture_UserSelectionInfo *selection, uint64_t* displayId);

/**
 * @brief Creates a screen capture strategy.
 * 
 * @return OH_AVScreenCapture_CaptureStrategy instance if the operation is successful; nullptr otherwise.
 * @since 20
 */
OH_AVScreenCapture_CaptureStrategy* OH_AVScreenCapture_CreateCaptureStrategy(void);

/**
 * @brief Releases a screen capture strategy.
 * 
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **strategy** is nullptr.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ReleaseCaptureStrategy(OH_AVScreenCapture_CaptureStrategy* strategy);

/**
 * @brief Sets a screen capture strategy for an OH_AVScreenCapture instance.
 * This function must be called before screen capture starts.
 * 
 * @param capture Pointer to an OH_AVScreenCapture which need to be setted.
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy which want to
 * set.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** or **strategy** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_STATE}: This function is called after screen capture starts.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetCaptureStrategy( 
	struct OH_AVScreenCapture *capture, OH_AVScreenCapture_CaptureStrategy *strategy);

/**
 * @brief Sets whether to keep screen capture during a cellular call.
 * When **value** is set to **true** and screen capture is active during a cellular call, for privacy reasons, the
 * voices of both parties (local microphone and remote speaker) are not captured. Other system sounds are captured
 * normally. After the call ends, the screen capture framework resumes microphone recording. If the screen capture
 * application is running in the background when the call ends, microphone recording fails to start because the audio
 * module does not allow background applications to activate microphone recording.
 * 
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @param value The default value is false, which means that screen recording is not allowed during cellular
 * calls.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **strategy** is nullptr.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForKeepCaptureDuringCall( 
    OH_AVScreenCapture_CaptureStrategy *strategy, bool value);

/**
 * @brief Set the fill mode for screen capture when a privacy window exists
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @param value 
 *         If set to 0, it means that when there is a privacy window interface, the output screen image is completely black. 
 *         If set to 1, it means that when there is a privacy window interface, only the privacy window area of the output screen becomes black, 
 *         and other values returns an error.
 * @return Function result code.
 *         {@link AV_SCREEN_CAPTURE_ERR_OK} if the execution is successful.
 *         {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL} strategy is nullptr or  value is invalid.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForPrivacyMaskMode( 
    OH_AVScreenCapture_CaptureStrategy *strategy, int32_t value);

/**
 * @brief Sets whether to enable B-frame encoding for a CaptureStrategy instance to reduce the size of the recorded
 * file.
 * For details about the restrictions on B-frame video encoding, see {@link Constraints in B-Frame Video Encoding}. If
 * the current environment does not meet the restrictions, B-frames will be skipped during screen capture, and no error
 * will be returned.
 * 
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @param value The default value is false, which means B frames  encoding are disabled.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **strategy** is nullptr.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForBFramesEncoding( 
    OH_AVScreenCapture_CaptureStrategy *strategy, bool value );

/**
 * @brief Sets the automatic rotation following configuration for screen capture. If the value is set to **true**, the
 * screen capture follows the rotation, and the virtual screen size is automatically adjusted after a rotation to
 * ensure the output image matches the new orientation.
 * After this setting, there is no need to manually call {@link OH_AVScreenCapture_ResizeCanvas} after rotation
 * notifications.
 * 
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @param value The default value is False, which means that the width and height of the VirtualDisplay
 * remain the initial settings. If set to True, it means that the width and height of the VirtualDisplay rotates
 * with the rotation of the screen..
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **strategy** is nullptr.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForCanvasFollowRotation( 
    OH_AVScreenCapture_CaptureStrategy *strategy, bool value);

/**
 * @brief Sets whether to display the screen capture picker.
 * 
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @param value
 * If set to false, it means that the APP don't need to pop up the Picker after screen capture starts;
 * If set to True, the Picker will pop up uniformly after screen capture starts;
 * If not set, it means using the system recommended behavior.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **strategy** is nullptr or **value** is invalid.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForPickerPopUp( 
    OH_AVScreenCapture_CaptureStrategy *strategy, bool value);

/**
 * @brief Sets the fill mode of the captured image in the target region.
 * 
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance
 * @param mode Value of the captured image fill mode
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **strategy** is nullptr.
 * @since 20
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForFillMode( 
    OH_AVScreenCapture_CaptureStrategy *strategy, OH_AVScreenCapture_FillMode mode);


/**
 * @brief Sets a callback function for obtaining the display ID.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param callback Callback function for returning the display ID.
 * @param userData Pointer to the user-defined data. The data is returned as an input parameter when the state change
 * callback is triggered.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** or **callback** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_NO_MEMORY}: The memory fails to be allocated due to insufficient memory.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_STATE}: The callback must be called before the **start** function.
 * @since 15
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetDisplayCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnDisplaySelected callback, void *userData);


/**
 * @brief Hides the specified window in the picker. This function is called before the picker is displayed. It is to
 * filter and hide a window.
 * 
 * @details Filters specified windows before displaying the system-level picker.
 * Excluded windows will not appear in the selection list.
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param excludedWindowIDs Array of IDs of the windows to be hidden (existing windows).
 * @param windowCount Size of the array.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr or **excludedWindowIDs** is
 * invalid.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed.
 * @since 22
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ExcludePickerWindows(struct OH_AVScreenCapture *capture,
    const int32_t *excludedWindowIDs, uint32_t windowCount);

/**
 * @brief Sets the display mode of the picker. You can define the content type displayed in the picker. The mode change
 * takes effect when {@link OH_AVScreenCapture_PresentPicker} is called next time.
 * 
 * @details Defines the content type displayed in the system-level picker.
 * Mode changes take effect upon the next call to function PresentPicker.
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param pickerMode Display mode of the picker. For details, see **OH_CapturePickerMode**.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr or **pickerMode** is invalid.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed.
 * @since 22
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetPickerMode(struct OH_AVScreenCapture *capture,
    OH_CapturePickerMode pickerMode);

/**
 * @brief Displays the picker once more after the screen capture starts, allowing for dynamic updates to the recording
 * source, such as changing the window or screen being captured. The ongoing capture process remains uninterrupted
 * while updating the recording source.
 * Following the dynamic update of the recording source through the picker, the capture can proceed with the newly
 * selected source.
 * 
 * @details Activates system visual picker with two usage scenarios:
 * 1. Initial capture configuration: Select source before starting capture
 * 2. Dynamic source switching: Change capture target during active capture
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is nullptr.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed.
 * @since 22
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_PresentPicker(struct OH_AVScreenCapture *capture);

/**
 * @brief Obtains the multi-screen recording capability information and determines whether the selected screens support
 * joint recording.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param displayIds Pointer to the array of display IDs selected by the user.
 * @param count Number of display IDs selected by the user.
 * @param capability Pointer to the **OH_MultiDisplayCapability** instance.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **capture** is a null pointer.
 * {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed, and data fails to be obtained.
 * @since 24
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_GetMultiDisplayCaptureCapability(
    struct OH_AVScreenCapture *capture, 
    uint64_t *displayIds, 
    size_t count,  
    OH_MultiDisplayCapability *capability);

/**
 * @brief Obtains the list of display IDs selected by the user for recording on the picker page. This function is used
 * in the {@link OH_AVScreenCapture_OnUserSelected} callback. The **selection** pointer is destroyed after the callback
 * is complete.
 * 
 * @param selection Pointer to the OH_AVScreenCapture_UserSelectionInfo instance.
 * @param displayIds Double pointer to the array of display IDs selected by the user. The memory of the **displayIds**
 * parameter is managed by **OH_AVScreenCapture_UserSelectionInfo** and does not need to be manually released.
 * @param count Pointer to the number of display IDs selected by the user.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input parameter **selection** is a null pointer.
 * @since 24
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_GetMultiDisplayIdsSelected(
    OH_AVScreenCapture_UserSelectionInfo *selection, 
    uint64_t **displayIds, 
    size_t *count);

/**
 * @brief Sets a privacy protection callback so that the application can respond to privacy protection events generated
 * during screen capture. This API must be called before screen capture starts.
 * 
 * @param capture Pointer to the OH_AVScreenCapture instance.
 * @param callback Privacy protection callback function.
 * @param userData Pointer to the user-defined data. The data is returned as an input parameter when the state change
 * callback is triggered.
 * @return {@link AV_SCREEN_CAPTURE_ERR_OK}: The operation is successful.
 * {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: The input screen capture instance or callback is a null pointer.
 * @since 24
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_SetPrivacyProtectCallback(struct OH_AVScreenCapture *capture,
    OH_AVScreenCapture_OnPrivacyProtect callback, void *userData);

/**
 * @brief Allow to pause screen capture
 * @param strategy Pointer to an OH_AVScreenCapture_CaptureStrategy instance.
 * @param value The default value is false, which means that screen recording is not allowed to pause
 * @return Function result code.
 *         {@link AV_SCREEN_CAPTURE_ERR_OK}: the execution is successful.
 *         {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: strategy value is nullptr.
 * @since 26.0.0
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_StrategyForPause(OH_AVScreenCapture_CaptureStrategy *strategy,
    bool value);

/**
 * @brief Pause screen capture
 * @param capture Initialized screen capture instance.
 * @return Function result code.
 *         {@link AV_SCREEN_CAPTURE_ERR_OK}: the execution is successful.
 *         {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: capture value is nullptr.
 *         {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 * @since 26.0.0
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_PauseScreenCapture(struct OH_AVScreenCapture *capture);

/**
 * @brief Resume screen capture
 * @param capture Initialized screen capture instance.
 * @return Function result code.
 *         {@link AV_SCREEN_CAPTURE_ERR_OK}: the execution is successful.
 *         {@link AV_SCREEN_CAPTURE_ERR_INVALID_VAL}: capture value is nullptr.
 *         {@link AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 * @since 26.0.0
 */
OH_AVSCREEN_CAPTURE_ErrCode OH_AVScreenCapture_ResumeScreenCapture(struct OH_AVScreenCapture *capture);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSCREEN_CAPTURE_H
/** @} */
