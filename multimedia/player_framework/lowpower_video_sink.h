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
 * @addtogroup LowPowerVideoSink
 * @{
 *
 * @brief The LowPowerVideoSink sub module provides variables, properties, and functions
 * for lowpower video sink.
 *
 * @since 20
 */
/**
 * @file lowpower_video_sink.h
 *
 * @brief The file declares the native APIs provided by the LowPowerVideoSink. You can use the APIs to implement low-
 * power video playback.
 * 
 * @library liblowpower_avsink.so
 * @kit MediaKit
 * @syscap SystemCapability.Multimedia.Media.LowPowerAVSink
 * @since 20
 */

#ifndef NATIVE_LOWPOWER_VIDEO_SINK_H
#define NATIVE_LOWPOWER_VIDEO_SINK_H

#include <stdint.h>
#include "native_averrors.h"
#include "native_avformat.h"
#include "lowpower_avsink_base.h"
#include "lowpower_video_sink_base.h"
#include "lowpower_audio_sink_base.h"
#include "native_window/external_window.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an OH_LowPowerVideoSink instance.
 * 
 * @param mime mime type description string, refer to {@link AVCODEC_MIME_TYPE}
 * @return Pointer to the OH_LowPowerVideoSink instance created. If the operation fails, nullptr is returned.
 * @since 20
 */
OH_LowPowerVideoSink* OH_LowPowerVideoSink_CreateByMime(const char* mime);

/**
 * @brief Configures an OH_LowPowerVideoSink instance. This function must be called before {@link OH_LowPowerVideoSink_Prepare}.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param format A pointer to an OH_AVFormat to give the description of the video track to be decoded,
 * key of format refer to lowpower_avsink_base.h
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_UNSUPPORT}: The format is not supported.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Configure(OH_LowPowerVideoSink* sink, const OH_AVFormat* format);

/**
 * @brief Sets parameters for an OH_LowPowerVideoSink instance. The parameters can be dynamically set after {@link OH_LowPowerVideoSink_Prepare}.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param format pointer to an OH_AVFormat instance, key of format refer to lowpower_avsink_base.h
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_UNSUPPORT}: The format is not supported.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_SetParameter(OH_LowPowerVideoSink* sink, const OH_AVFormat* format);

/**
 * @brief Obtains the parameters of an OH_LowPowerVideoSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param format pointer to an OH_AVFormat instance, key of format refer to lowpower_avsink_base.h
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_GetParameter(OH_LowPowerVideoSink* sink, OH_AVFormat* format);

/**
 * @brief Sets the rendering window for an OH_LowPowerVideoSink instance. This function must be called before {@link OH_LowPowerVideoSink_Prepare}.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param surface A pointer to a OHNativeWindow instance, see {@link OHNativeWindow}
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_SetVideoSurface(OH_LowPowerVideoSink* sink, const OHNativeWindow* surface);

/**
 * @brief Prepares an OH_LowPowerVideoSink instance for decoding and rendering. This function must be called after {@link OH_LowPowerVideoSink_SetSyncAudioSink}.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_UNSUPPORT}: The format is not supported.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Prepare(OH_LowPowerVideoSink* sink);

/**
 * @brief Starts an OH_LowPowerVideoSink instance for decoding. This function must be called after {@link OH_LowPowerVideoSink_Prepare}
 * or if no video is playing, after {@link OH_LowPowerVideoSink_SetTargetStartFrame}.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_UNSUPPORT}: The format is not supported.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_StartDecoder(OH_LowPowerVideoSink* sink);

/**
 * @brief Renders the first frame decoded by an OH_LowPowerVideoSink instance. This function must be called after {@link OH_LowPowerVideoSink_StartDecoder}.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_RenderFirstFrame(OH_LowPowerVideoSink* sink);

/**
 * @brief Starts an OH_LowPowerVideoSink instance for rendering. This function must be called after {@link OH_LowPowerVideoSink_StartDecoder}.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_UNSUPPORT}: The format is not supported.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_StartRenderer(OH_LowPowerVideoSink* sink);

/**
 * @brief Pauses an OH_LowPowerVideoSink instance. This function must be called after {@link OH_LowPowerVideoSink_StartRenderer}
 * or {@link OH_LowPowerVideoSink_Resume}.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Pause(OH_LowPowerVideoSink* sink);

/**
 * @brief Resumes an OH_LowPowerVideoSink instance. This function must be called after{@link OH_LowPowerVideoSink_Pause}.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSinkinstance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Resume(OH_LowPowerVideoSink* sink);

/**
 * @brief Clears all input and output data from the decoders and render buffers of an OH_LowPowerVideoSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Flush(OH_LowPowerVideoSink* sink);

/**
 * @brief Stops an OH_LowPowerVideoSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Stop(OH_LowPowerVideoSink* sink);

/**
 * @brief Resets an OH_LowPowerVideoSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Reset(OH_LowPowerVideoSink* sink);

/**
 * @brief Clears internal resources of an OH_LowPowerVideoSink instance and destroys the instance. You only need to
 * call the function once.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_Destroy(OH_LowPowerVideoSink* sink);

/**
 * @brief Sets an OH_LowPowerAudioSink instance for audio-video synchronization in an OH_LowPowerVideoSink instance.
 * 
 * @param videoSink Pointer to an OH_LowPowerVideoSink instance
 * @param audioSink Pointer to an OH_LowPowerAudioSink instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_SetSyncAudioSink(
    OH_LowPowerVideoSink* videoSink, OH_LowPowerAudioSink* audioSink);

/**
 * @brief Sets the target rendering frame for an OH_LowPowerVideoSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param framePts target video frame pts, in microseconds
 * @param onTargetArrived OH_LowPowerVideoSink_OnTargetArrived func,
 * will be called once, refer to {@link OH_LowPowerVideoSink_OnTargetArrived}
 * @param timeoutMs if wait first frame over timeoutMs, onTargetArrived will be called directly,
 * in milliseconds.
 * @param userData User specific data
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_SetTargetStartFrame(
    OH_LowPowerVideoSink* sink,
    const int64_t framePts,
    OH_LowPowerVideoSink_OnTargetArrived onTargetArrived,
    const int64_t timeoutMs,
    void* userData);

/**
 * @brief Sets the playback speed for an OH_LowPowerVideoSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param speed Indicates the value of the playback rate.
 * The current version is valid in the range of 0.25-4.0
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_SetPlaybackSpeed(OH_LowPowerVideoSink* sink, const float speed);

/**
 * @brief Provides a buffer to an OH_LowPowerVideoSink instance for procesing.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param samples Pointer to an OH_AVSamplesBuffer instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_ReturnSamples(OH_LowPowerVideoSink* sink, OH_AVSamplesBuffer* samples);

/**
 * @brief Registers a callback for an OH_LowPowerVideoSink instance.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSink_RegisterCallback(OH_LowPowerVideoSink* sink, OH_LowPowerVideoSinkCallback* callback);

/**
 * @brief Creates an OH_LowPowerVideoSinkCallback instance.
 * 
 * @return Pointer to the OH_LowPowerVideoSinkCallback instance created. If the memory is insufficient, nullptr is
 * returned.
 * @since 20
 */
OH_LowPowerVideoSinkCallback* OH_LowPowerVideoSinkCallback_Create(void);

/**
 * @brief Destroys an OH_LowPowerVideoSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_Destroy(OH_LowPowerVideoSinkCallback* callback);

/**
 * @brief Sets a data needed listener for an OH_LowPowerVideoSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @param onDataNeeded OH_LowPowerVideoSink_OnDataNeeded function,
 * refer to {@link OH_LowPowerVideoSink_OnDataNeeded}
 * @param userData User specific data
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_SetDataNeededListener(
    OH_LowPowerVideoSinkCallback* callback, OH_LowPowerVideoSink_OnDataNeeded onDataNeeded,void* userData);

/**
 * @brief Sets an error listener for an OH_LowPowerVideoSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @param onError OH_LowPowerVideoSink_OnError function,
 * refer to {@link OH_LowPowerVideoSink_OnError}
 * @param userData User specific data
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_SetErrorListener(
    OH_LowPowerVideoSinkCallback* callback, OH_LowPowerVideoSink_OnError onError, void* userData);

/**
 * @brief Sets a render start listener for an OH_LowPowerVideoSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @param onRenderStarted OH_LowPowerVideoSink_OnRenderStarted function,
 * refer to {@link OH_LowPowerVideoSink_OnRenderStarted}
 * @param userData User specific data
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_SetRenderStartListener(
    OH_LowPowerVideoSinkCallback* callback, OH_LowPowerVideoSink_OnRenderStarted onRenderStarted, void* userData);

/**
 * @brief Sets a stream change listener for an OH_LowPowerVideoSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @param onStreamChanged OH_LowPowerVideoSink_OnStreamChanged function,
 * refer to {@link OH_LowPowerVideoSink_OnStreamChanged}
 * @param userData User specific data
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_SetStreamChangedListener(
    OH_LowPowerVideoSinkCallback* callback, OH_LowPowerVideoSink_OnStreamChanged onStreamChanged, void* userData);

/**
 * @brief Sets a first-frame ready listener for an OH_LowPowerVideoSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @param onFirstFrameDecoded OH_LowPowerVideoSink_OnFirstFrameDecoded
 * function,
 * refer to {@link OH_LowPowerVideoSink_OnFirstFrameDecoded}
 * @param userData User specific data
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_SetFirstFrameDecodedListener(
    OH_LowPowerVideoSinkCallback* callback,
    OH_LowPowerVideoSink_OnFirstFrameDecoded onFirstFrameDecoded,
    void* userData);

/**
 * @brief Sets an end-of-stream listener for an OH_LowPowerVideoSinkCallback instance.
 * 
 * @param callback Pointer to an OH_LowPowerVideoSinkCallback instance
 * @param onEos OH_LowPowerVideoSink_OnEos function,
 * refer to {@link OH_LowPowerVideoSink_OnEos}
 * @param userData User specific data
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 20
 */
OH_AVErrCode OH_LowPowerVideoSinkCallback_SetEosListener(OH_LowPowerVideoSinkCallback* callback,
    OH_LowPowerVideoSink_OnEos onEos, void* userData);

/**
 * @brief Obtains the Presentation Timestamp (PTS) of the video that is playing.
 * 
 * @param sink Pointer to an OH_LowPowerVideoSink instance.
 * @param pts Pointer to store the latest PTS value (in microseconds).
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VA}: An input parameter is nullptr or invalid.
 * {@link AV_ERR_SERVICE_DIED}: The media server is destroyed.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not supported.
 * @since 21
 */
OH_AVErrCode OH_LowPowerVideoSink_GetLatestPts(OH_LowPowerVideoSink *sink, int64_t *pts);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_LOWPOWER_VIDEO_SINK_H

/** @} */
