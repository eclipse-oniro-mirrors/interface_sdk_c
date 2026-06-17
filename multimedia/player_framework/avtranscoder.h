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
 * @addtogroup AVTranscoder
 * @{
 *
 * @brief Provides APIs of request capability for Transcoder.
 *
 * @syscap SystemCapability.Multimedia.Media.AVTranscoder
 * @since 20
 * @}
 */
/**
 * @file avtranscoder.h
 *
 * @brief The file declares the native APIs provided by the AVTranscoder. You can use the APIs to transcode a source
 * video file into a new video file.
 * 
 * @kit MediaKit
 * @library libavtranscoder.so
 * @since 20
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_AVTRANSCODER_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_AVTRANSCODER_H

#include <stdint.h>
#include <stdio.h>
#include "avtranscoder_base.h"
#include "native_avcodec_base.h"
#include "native_averrors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an instance of the transcoding configuration parameters.
 * 
 * @return Pointer to the OH_AVTranscoder_Config instance created. If the operation fails, nullptr is returned.
 * @since 20
 */
OH_AVTranscoder_Config *OH_AVTranscoderConfig_Create();

/**
 * @brief Releases the resources of the transcoding configuration parameters.
 * After a successful call, the instance specified by **config** is released and set to nullptr.
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance.
 * @return {@link AV_ERR_OK}: The release operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **config** is nullptr.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_Release(OH_AVTranscoder_Config* config);

/**
 * @brief Sets the file descriptor of the source video for transcoding.
 * This function must be called before {@link OH_AVTranscoder_Prepare}.
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance.
 * @param srcFd Source file descriptor.
 * @param srcOffset The offset into the file where the data to be read, in bytes.
 * @param length The length in bytes of the data to be read
 * @return {@link AV_ERR_OK}: The setting is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **config** is nullptr, or the parameters related to the source video
 * file are incorrect.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetSrcFD(
    OH_AVTranscoder_Config *config, int32_t srcFd, int64_t srcOffset, int64_t length);

/**
 * @brief Sets the file descriptor of the output video for transcoding.
 * This function must be called before {@link OH_AVTranscoder_Prepare}.
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param dstFd Destination file descriptor
 * @return {@link AV_ERR_OK}: The setting is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **config** is nullptr, or the output video file descriptor is invalid.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstFD(OH_AVTranscoder_Config *config, int32_t dstFd);

/**
 * @brief Sets the encoding format of the output video for transcoding.
 * Currently, only AVC and HEVC are supported. If the source video is in HEVC format, the default value is **HEVC**.
 * Otherwise, the default value is **AVC**.
 * This function must be called before {@link OH_AVTranscoder_Prepare}.
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param mimeType Destination video mime type. See native_avcodec_base.h
 * @return {@link AV_ERR_OK}: The setting is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **config** is nullptr, or the value of **mimeType** is not allowed.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstVideoType(OH_AVTranscoder_Config *config, const char *mimeType);

/**
 * @brief Sets the encoding format of the output audio for transcoding.
 * Currently, only AAC is supported. If this parameter is not set, AAC is used by default.
 * This function must be called before {@link OH_AVTranscoder_Prepare}.
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param mimeType Destination audio mime type. See native_avcodec_base.h
 * @return {@link AV_ERR_OK}: The setting is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **config** is nullptr, or the value of **mimeType** is not allowed.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstAudioType(OH_AVTranscoder_Config *config, const char *mimeType);

/**
 * @brief Sets the container format of the output video file for transcoding.
 * Currently, only MP4 is supported.
 * This function must be called before {@link OH_AVTranscoder_Prepare}.
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param mimeType Destination file type. See native_avcodec_base.h
 * @return {@link AV_ERR_OK}: The setting is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **config** is nullptr, or the value of **mimeType** is invalid.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstFileType(OH_AVTranscoder_Config *config, OH_AVOutputFormat mimeType);

/**
 * @brief Sets the bit rate of the output audio for transcoding.
 * This function must be called before {@link OH_AVTranscoder_Prepare}.
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param bitrate Destination audio bitrate, in bit/s.
 * @return {@link AV_ERR_OK}: The setting is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **config** is nullptr, or the value of **bitrate** is invalid.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstAudioBitrate(OH_AVTranscoder_Config *config, int32_t bitrate);

/**
 * @brief Sets the bit rate of the output video for transcoding.
 * This function must be called before {@link OH_AVTranscoder_Prepare}.
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param bitrate Destination video bitrate, in bit/s.
 * @return {@link AV_ERR_OK}: The setting is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **config** is nullptr, or the value of **bitrate** is invalid.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstVideoBitrate(OH_AVTranscoder_Config *config, int32_t bitrate);

/**
 * @brief Sets the resolution of the output video for transcoding, in px, where **width** is the width of the output
 * video frame and **height** is the height of the output video frame.
 * This function must be called before {@link OH_AVTranscoder_Prepare}.
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param width Destination for video width, in px.
 * @param height Destination for video height, in px.
 * @return {@link AV_ERR_OK}: The setting is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **config** is nullptr, or the value of **width** or **height** is
 * invalid.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_SetDstVideoResolution(OH_AVTranscoder_Config *config, int32_t width, int32_t height);

/**
 * @brief Creates an AVTranscoder instance.
 * 
 * @return Pointer to the OH_AVTranscoder instance created. If the operation fails, nullptr is returned.
 * @since 20
 */
OH_AVTranscoder *OH_AVTranscoder_Create(void);

/**
 * @brief Sets the parameters for video transcoding and prepares for transcoding.
 * This function must be called before {@link OH_AVTranscoder_Start}. Upon a successful call to this function, the
 * AVTranscoder enters the AVTRANSCODER_PREPARED state.
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @param config Pointer to an OH_AVTranscoder_Config instance,
 * see {@link OH_AVTranscoder_Config}
 * @return {@link AV_ERR_OK}: The video transcoding parameters are set successfully, and the AVTranscoder enters the
 * AVTRANSCODER_PREPARED state.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **transcoder** is nullptr, or the Prepare operation fails.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The Prepare operation is not allowed in the current state, or the format is not
 * supported.
 * **AV_ERR_IO**: An I/O access error occurs.
 * {@link AV_ERR_SERVICE_DIED}: The media service is stopped.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_Prepare(OH_AVTranscoder *transcoder, OH_AVTranscoder_Config *config);

/**
 * @brief Starts transcoding.
 * This function must be called after a successful call to {@link OH_AVTranscoder_Prepare}. Upon a successful call to
 * this function, the AVTranscoder enters the AVTRANSCODER_STARTED state.
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @return {@link AV_ERR_OK}: Transcoding starts successfully, and the AVTranscoder enters the AVTRANSCODER_STARTED state.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **transcoder** is nullptr, or the Start operation fails.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The Start operation is not allowed in the current state.
 * **AV_ERR_IO**: An I/O access error occurs.
 * {@link AV_ERR_SERVICE_DIED}: The media service is stopped.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_Start(OH_AVTranscoder *transcoder);

/**
 * @brief Pauses transcoding.
 * This function must be called when the AVTranscoder is in the AVTRANSCODER_STARTED state. Upon a successful call to
 * this function, the AVTranscoder enters the AVTRANSCODER_PAUSED state.
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @return {@link AV_ERR_OK}: Transcoding is paused successfully, and the AVTranscoder enters the AVTRANSCODER_PAUSED state.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **transcoder** is nullptr, or the Pause operation fails.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The Pause operation is not allowed in the current state.
 * **AV_ERR_IO**: An I/O access error occurs.
 * {@link AV_ERR_SERVICE_DIED}: The media service is stopped.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_Pause(OH_AVTranscoder *transcoder);

/**
 * @brief Resumes transcoding.
 * This function must be called when the AVTranscoder is in the AVTRANSCODER_PAUSED state. Upon a successful call to
 * this function, the AVTranscoder enters the AVTRANSCODER_STARTED state again.
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @return {@link AV_ERR_OK}: Transcoding is resumed successfully, and the AVTranscoder enters the AVTRANSCODER_STARTED
 * state.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **transcoder** is nullptr, or the Resume operation fails.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The Resume operation is not allowed in the current state.
 * **AV_ERR_IO**: An I/O access error occurs.
 * {@link AV_ERR_SERVICE_DIED}: The media service is stopped.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_Resume(OH_AVTranscoder *transcoder);

/**
 * @brief Cancels transcoding.
 * This function must be called when the AVTranscoder is in the AVTRANSCODER_STARTED or AVTRANSCODER_PAUSED state. Upon
 * a successful call to this function, the AVTranscoder enters the AVTRANSCODER_CANCELLED state.
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @return {@link AV_ERR_OK}: Transcoding is canceled successfully, and the AVTranscoder enters the AVTRANSCODER_CANCELLED
 * state.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **transcoder** is nullptr, or the Cancel operation fails.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The Cancel operation is not allowed in the current state.
 * **AV_ERR_IO**: An I/O access error occurs.
 * {@link AV_ERR_SERVICE_DIED}: The media service is stopped.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_Cancel(OH_AVTranscoder *transcoder);

/**
 * @brief Releases an AVTranscoder instance.
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @return AV_ERR_OK: The AVTranscoder instance is successfully released.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **transcoder** is nullptr, or the Release operation fails.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The Release operation is not allowed in the current state.
 * **AV_ERR_IO**: An I/O access error occurs.
 * {@link AV_ERR_SERVICE_DIED}: The media service is stopped.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_Release(OH_AVTranscoder *transcoder);

/**
 * @brief Registers a callback for transcoding state change events.
 * This callback is invoked when the state of the transcoding process changes.
 * An application can subscribe to only one transcoding state change event. When the application initiates multiple
 * subscriptions to this event, the last subscription is applied.
 * The callback must be registered before {@link OH_AVTranscoder_Prepare} is called.
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @param callback State callback function, see {@link OH_AVTranscoder_OnStateChange}
 * @param userData Pointer to user specific data
 * @return {@link AV_ERR_OK}: The registration is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **transcoder** or **callback** is nullptr.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_SetStateCallback(
    OH_AVTranscoder *transcoder, OH_AVTranscoder_OnStateChange callback, void *userData);

/**
 * @brief Registers a callback for transcoding error events.
 * This callback is invoked when an error occurs during the transcoding process.
 * If this event is reported, call {@link OH_AVTranscoder_Release} to exit the transcoding.
 * An application can subscribe to only one transcoding error event. When the application initiates multiple
 * subscriptions to this event, the last subscription is applied.
 * The callback must be registered before {@link OH_AVTranscoder_Prepare} is called.
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @param callback Error callback function, see {@link OH_AVTranscoder_OnError}
 * @param userData Pointer to user specific data
 * @return {@link AV_ERR_OK}: The registration is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **transcoder** or **callback** is nullptr.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_SetErrorCallback(
    OH_AVTranscoder *transcoder, OH_AVTranscoder_OnError callback, void *userData);

/**
 * @brief Registers a callback for transcoding progress update events.
 * This callback is invoked when the progress of the transcoding process is updated.
 * An application can subscribe to only one transcoding error event. When the application initiates multiple
 * subscriptions to this event, the last subscription is applied.
 * The callback must be registered before {@link OH_AVTranscoder_Prepare} is called.
 * 
 * @param transcoder Pointer to an OH_AVTranscoder instance
 * @param callback Uri callback function,
 * see {@link OH_AVTranscoder_OnProgressUpdate}
 * @param userData Pointer to user specific data
 * @return {@link AV_ERR_OK}: The registration is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **transcoder** or **callback** is nullptr.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoder_SetProgressUpdateCallback(
    OH_AVTranscoder *transcoder, OH_AVTranscoder_OnProgressUpdate callback, void *userData);

/**
 * @brief Enables B-frame encoding for the output video during transcoding.
 * For details about the constraints on B-frame video encoding, see {@link Constraints in B-Frame Video Encoding}.
 * If the current environment does not meet these constraints, B-frames will be skipped, and encoding will proceed as
 * if B-frame video encoding were not enabled.
 * 
 * @param config Pointer to an OH_AVTranscoder_Config instance
 * @param enabled Whether enable B Frame. If this function is not called, B Frame is disabled.
 * @return {@link AV_ERR_OK}: The setting is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **config** is nullptr.
 * @since 20
 */
OH_AVErrCode OH_AVTranscoderConfig_EnableBFrame(OH_AVTranscoder_Config *config, bool enabled);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_AVTRANSCODER_H

