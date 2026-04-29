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
 * @addtogroup VideoEncoder
 * @{
 *
 * @brief The VideoEncoder module provides interfaces for video encoding.
 *
 * @since 9
 */
/**
 * @file native_avcodec_videoencoder.h
 *
 * @brief Declare the interface used for video encoding.
 *
 * @kit AVCodecKit
 * @library libnative_media_venc.so
 * @syscap SystemCapability.Multimedia.Media.VideoEncoder
 * @since 9
 */

#ifndef NATIVE_AVCODEC_VIDEOENCODER_H
#define NATIVE_AVCODEC_VIDEOENCODER_H
#include <stdint.h>
#include <stdio.h>
#include "native_avcodec_base.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the pointer to the function that is called when new input parameters are required for a frame with
 * the specified index.
 *
 * This callback can be used only in surface mode after it is registered by calling
 * OH_VideoEncoder_RegisterParameterCallback.
 *
 * In buffer mode, OH_AVBuffer can directly carry the encoding parameter associated with each frame. Currently, it can
 * manage parameters, including **QPMin**, **QPMax**, and reference frames for Long Term Reference (LTR), on a
 * per-frame basis.
 *
 * @param codec Pointer to a video encoder instance.
 * @param index Index of the frame to encode.
 * @param parameter Pointer to the encoding parameter
 * @param userData Pointer to the data on which the caller depends when executing the callback.
 * @since 12
 */
typedef void (*OH_VideoEncoder_OnNeedInputParameter)(OH_AVCodec *codec, uint32_t index, OH_AVFormat *parameter,
                                                     void *userData);

/**
 * @brief Creates a video encoder instance based on a MIME type. This function is recommended.
 *
 * @param mime Pointer to a string that describes the MIME type. For details, see {@link AVCODEC_MIME_TYPE}.
 * @return Pointer to the video encoder instance created.
 *     <br>If the encoder type is not supported or the memory is insufficient, NULL is returned.
 * @since 9
 */
OH_AVCodec *OH_VideoEncoder_CreateByMime(const char *mime);

/**
 * @brief Creates a video encoder instance based on an encoder name. To use this function, you must know the exact name
 * of the encoder. The encoder name can be obtained through capability query.
 *
 * For details, see [Obtaining Supported Codecs](docroot://media/avcodec/obtain-supported-codecs.md#creating-a-codec-with-the-specified-name).
 *
 * @param name Pointer to a video encoder name.
 * @return Pointer to the video encoder instance created.
 *     <br>If the encoder name is not supported or the memory is insufficient, NULL is returned.
 * @since 9
 */
OH_AVCodec *OH_VideoEncoder_CreateByName(const char *name);

/**
 * @brief Creates a primary video encoder with preprocessor.
 *
 * Creates a primary video encoder instance that supports:
 * 1. Preprocessing features (downsampling, cropping, drop frame)
 * 2. Creating a secondary encoder for one-input-dual-output encoding
 *
 * @param mime Mime type description string, refer to {@link AVCODEC_MIME_TYPE}.
 *             Cannot be NULL, must be a supported MIME type
 *             (e.g., {@link OH_AVCODEC_MIMETYPE_VIDEO_AVC}, {@link OH_AVCODEC_MIMETYPE_VIDEO_HEVC}).
 * @param codec Double pointer to an OH_AVCodec instance, used to receive the created encoder.
 *              Cannot be NULL. If creation is successful, the encoder needs to be released
 *              by calling {@link OH_VideoEncoder_Destroy}.
 *
 * @return Returns {@link AV_ERR_OK} if the execution is successful.
 *         For other error codes, refer to {@link OH_AVErrCode}.
 *         Returns {@link AV_ERR_INVALID_VAL} if:
 *         - mime is NULL.
 *         - codec is NULL.
 *         - mime type is not supported.
 *         Returns {@link AV_ERR_NO_MEMORY} if memory allocation fails.
 *
 * @since 26.0.0
 */
OH_AVErrCode OH_VideoEncoder_CreatePrimaryWithPreproc(const char *mime, OH_AVCodec **codec);

/**
 * @brief Creates a secondary video encoder from a primary video encoder.
 *
 * Creates a secondary video encoder instance from a primary encoder created by
 * {@link OH_VideoEncoder_CreatePrimaryWithPreproc}. The secondary encoder:
 * 1. Shares the input source with the primary encoder
 * 2. Can be configured with independent encoding parameters
 * 3. Can use different preprocessing parameters
 * 4. Can be started/stopped independently from the primary encoder
 * 5. The lifecycle of primary encoder must be longer than secondary encoder
 * 6. One primary encoder can only have one secondary encoder at the same time
 *
 * @param primary Pointer to a primary OH_AVCodec instance created by
 *                {@link OH_VideoEncoder_CreatePrimaryWithPreproc}. Cannot be NULL.
 * @param codec Double pointer to an OH_AVCodec instance, used to receive the created encoder.
 *              Cannot be NULL. If creation is successful, the encoder needs to be released
 *              by calling {@link OH_VideoEncoder_Destroy}.
 *
 * @return Returns {@link AV_ERR_OK} if the execution is successful.
 *         For other error codes, refer to {@link OH_AVErrCode}.
 *         Returns {@link AV_ERR_INVALID_VAL} if:
 *         - primary is NULL.
 *         - codec is NULL.
 *         - primary is not a valid primary encoder.
 *         Returns {@link AV_ERR_OPERATE_NOT_PERMIT} if primary encoder already has an existing secondary encoder.
 *         Returns {@link AV_ERR_NO_MEMORY} if memory allocation fails.
 *
 * @note Lifecycle management:
 *       - The lifecycle of primary encoder must be longer than secondary encoder.
 *       - Recommended destruction order: destroy secondary encoder first, then primary encoder.
 *       - If primary encoder is destroyed before secondary encoder, the system will automatically
 *         destroy the secondary encoder before releasing the primary encoder.
 *       - Both encoders must be destroyed by calling {@link OH_VideoEncoder_Destroy}.
 *       - One primary encoder can only have one secondary encoder at the same time.
 *         After the secondary encoder is destroyed, a new secondary encoder can be created
 *         from the same primary encoder again.
 *
 * @since 26.0.0
 */
OH_AVErrCode OH_VideoEncoder_CreateSecondaryFromPrimary(OH_AVCodec *primary, OH_AVCodec **codec);

/**
 * @brief Clears the internal resources of a video encoder and destroys the encoder instance. You only need to call the
 * function once.
 *
 * @param codec Pointer to a video encoder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance,
 *     for example, an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Destroy(OH_AVCodec *codec);

/**
 * @brief Sets an OH_AVCodecCallback callback so that your application can respond to events generated by a video
 * encoder. This function must be called prior to {@link OH_VideoEncoder_Prepare}.
 *
 * @param codec Pointer to a video encoder instance.
 * @param callback Callback function.
 * @param userData Pointer to the data on which the caller depends when executing the callback.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 * @deprecated since 11
 * @useinstead OH_VideoEncoder_RegisterCallback
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_SetCallback(OH_AVCodec *codec, OH_AVCodecAsyncCallback callback, void *userData);

/**
 * @brief Registers an OH_AVCodecCallback callback so that your application can respond to events generated by a video
 * encoder. This function must be called prior to {@link OH_VideoEncoder_Prepare}.
 *
 * @param codec Pointer to a video encoder instance.
 * @param callback Callback function.
 * @param userData Pointer to the data on which the caller depends when executing the callback.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 * @since 11
 */
OH_AVErrCode OH_VideoEncoder_RegisterCallback(OH_AVCodec *codec, OH_AVCodecCallback callback, void *userData);

/**
 * @brief Registers an input parameter callback so that your application can respond to events
 * generated by a video encoder. In surface encoding mode, this function must be called when frame parameters need to
 * be set,
 *
 * and it must be called before {@link OH_VideoEncoder_Configure}.
 *
 * @param codec Pointer to a video encoder instance.
 * @param onInputParameter Pointer to the input parameter callback.
 * @param userData Pointer to the data on which the caller depends when executing the callback.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: The function is not called prior to {@link OH_VideoEncoder_Prepare}.
 * @since 12
 */
OH_AVErrCode OH_VideoEncoder_RegisterParameterCallback(OH_AVCodec *codec,
                                                       OH_VideoEncoder_OnNeedInputParameter onInputParameter,
                                                       void *userData);

/**
 * @brief Configures encoding parameters for a video encoder. Typically, you need to configure the description
 * information about the video frames, such as the frame width, height, and pixel format.
 * This function must be called prior to {@link OH_VideoEncoder_Prepare}.
 *
 * This function is used to verify the validity of configuration parameters. Some invalid parameters are not forcibly
 * verified. The default values are used or discarded. Some invalid parameters are forcibly verified. The rules are as
 * follows:
 *
 * The value ranges of the following parameters can be obtained through
 * [Capability Query](docroot://media/avcodec/obtain-supported-codecs.md).
 * {@link OH_MD_KEY_I_FRAME_INTERVAL} does not support capability query currently.
 *
 * When attempting to set the {@link OH_MD_KEY_VIDEO_ENCODER_ENABLE_TEMPORAL_SCALABILITY} or
 * {@link OH_MD_KEY_VIDEO_ENCODER_LTR_FRAME_COUNT} parameter on an unsupported platform,
 * this API will not return an error; instead, it will follow its normal execution path.
 *
 * Parameter verification rules are as follows:
 * | Key     | Value Within the Range| Value Out of Range| No Value Configured|
 * | ------- | -------- | -------- | ------ |
 * | OH_MD_KEY_WIDTH  | AV_ERR_OK | AV_ERR_INVALID_VAL | AV_ERR_INVALID_VAL |
 * | OH_MD_KEY_HEIGHT | AV_ERR_OK | AV_ERR_INVALID_VAL | AV_ERR_INVALID_VAL |
 * | OH_MD_KEY_PIXEL_FORMAT {@link OH_AVPixelFormat}| AV_ERR_OK | AV_ERR_UNSUPPORT | AV_ERR_OK    |
 * | OH_MD_KEY_FRAME_RATE | AV_ERR_OK | AV_ERR_INVALID_VAL | AV_ERR_OK |
 * | OH_MD_KEY_PROFILE {@link OH_MD_KEY_PROFILE}   | AV_ERR_OK | AV_ERR_INVALID_VAL | AV_ERR_OK |
 * | OH_MD_KEY_I_FRAME_INTERVAL | AV_ERR_OK |  \\       | AV_ERR_OK |
 *
 * | OH_MD_KEY_<br>BITRATE | OH_MD_KEY_<br>QUALITY |OH_MD_KEY_<br>VIDEO_ENCODER_BITRATE_MODE|Return Value| Description|
 * | :-------- | :---------| :---------- | ---- | ---------- |
 * | \\      | \\      | \\           |  AV_ERR_OK    | The default value of the encoder is used.|
 * | Out of range| Out of range| Unsupported mode| AV_ERR_INVALID_VAL   | An error is reported for all abnormal values.|
 * | Normal value    | Normal value    | \\   | AV_ERR_INVALID_VAL   | The bit rate conflicts with the quality.  |
 * | Normal value    | \\      | \\           | AV_ERR_OK     | The default bit rate control mode is enabled.|
 * | Normal value    | \\      | BITRATE_MODE_VBR and BITRATE_MODE_CBR     | AV_ERR_OK     |    -     |
 * | Normal value    | \\      | BITRATE_MODE_CQ | AV_ERR_INVALID_VAL   | The bit rate conflicts with the CQ mode.  |
 * | \\      | Normal value    | \\           | AV_ERR_OK     | The CQ mode is enabled.|
 * | \\      | Normal value    | BITRATE_MODE_CQ           | AV_ERR_OK     |   -      |
 * | \\      | Normal value | BITRATE_MODE_VBR and BITRATE_MODE_CBR | AV_ERR_INVALID_VAL | The quality conflicts with the VBR or CBR mode.|
 * | \\      | \\   | BITRATE_MODE_VBR and BITRATE_MODE_CBR | AV_ERR_OK | The default bit rate of the encoder is used.|
 * | \\      | \\      | BITRATE_MODE_CQ           | AV_ERR_OK    | The default quality is used. |
 *
 * @param codec Pointer to a video encoder instance.
 * @param format Pointer to an OH_AVFormat instance, which provides the description information about the video track
 * to be encoded.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}:<br>1. The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>2. The format is not supported.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: The function is not called prior to {@link OH_VideoEncoder_Prepare}.
 *     <br>{@link AV_ERR_UNSUPPORT}: unsupported pixel format.
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Configure(OH_AVCodec *codec, OH_AVFormat *format);

/**
 * @brief Prepares internal resources for a video encoder. This function must be called after
 * {@link OH_VideoEncoder_Configure}.
 *
 * @param codec Pointer to a video encoder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal error occurs in the input encoder instance.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state.
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Prepare(OH_AVCodec *codec);

/**
 * @brief Starts a video encoder. This function should be called after a successful call of
 * {@link OH_VideoEncoder_Prepare}. After being started, the encoder starts to report the registered event.
 *
 * In surface mode, when there is a correct input on the surface, **OnNewOutputBuffer** is triggered each time a frame
 * is encoded.
 *
 * In buffer mode, the encoder immediately triggers the input callback. Each time the caller completes an input, the
 * encoder performs encoding. **OnNewOutputBuffer** is triggered each time a frame is encoded.
 *
 * @param codec Pointer to a video encoder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state..
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Start(OH_AVCodec *codec);

/**
 * @brief Stops a video encoder and releases the input and output buffers. After the video encoder is stopped, you can
 * call {@link OH_VideoEncoder_Start} to enter the running state again.
 *
 * @param codec Pointer to a video encoder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state.
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Stop(OH_AVCodec *codec);

/**
 * @brief Clears the input and output data and parameters, for example, H.264 PPS/SPS, cached in a video encoder.
 * This function invalidates the indexes of all buffers previously reported through the asynchronous callback.
 *
 * Therefore, before calling this function, ensure that the buffers with the specified indexes are no longer required.
 * This function cannot be called consecutively.
 *
 * @param codec Pointer to a video encoder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state.
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Flush(OH_AVCodec *codec);

/**
 * @brief Resets a video encoder. The encoder returns to the initial state. To continue encoding, you must call
 * {@link OH_VideoEncoder_Configure} to configure the encoder again.
 *
 * @param codec Pointer to a video encoder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_Reset(OH_AVCodec *codec);

/**
 * @brief Obtains the OH_AVFormat information about the output data of a video encoder.
 *
 * You must call {@link OH_AVFormat_Destroy} to release the OH_AVFormat instance in the return value.
 *
 * @param codec Pointer to a video encoder instance.
 * @return Pointer to an OH_AVFormat instance.
 *     <br>If the value of **codec** is nullptr or does not point to an encoder instance, NULL is returned.
 * @since 9
 */
OH_AVFormat *OH_VideoEncoder_GetOutputDescription(OH_AVCodec *codec);

/**
 * @brief Sets the encoder parameter when a video encoder is running.
 *
 * This function can be called only after the encoder is started. Incorrect parameter settings may cause encoding
 * failure.
 *
 * @param codec Pointer to a video encoder instance.
 * @param format Pointer to an OH_AVFormat instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}:<br>1. The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>2. The format is not supported.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state.
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_SetParameter(OH_AVCodec *codec, OH_AVFormat *format);

/**
 * @brief Obtains the input surface from a video encoder. This function must be called after **
 * OH_VideoEncoder_Configure** but before {@link OH_VideoEncoder_Prepare}.
 *
 * @param codec Pointer to a video encoder instance.
 * @param window Double pointer to an OHNativeWindow instance. The application manages the lifecycle of the window and
 *     calls {@link OH_NativeWindow_DestroyNativeWindow} to release the window when the lifecycle ends.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_GetSurface(OH_AVCodec *codec, OHNativeWindow **window);

/**
 * @brief Frees an output buffer of a video encoder.
 *
 * @param codec Pointer to a video encoder instance.
 * @param index Index of the output buffer. The value is provided by {@link OH_AVCodecOnNewOutputData}.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}:<br>1. The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>2. The index is invalid. This error does not affect the subsequent encoding process.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state.
 * @deprecated since 11
 * @useinstead OH_VideoEncoder_FreeOutputBuffer
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_FreeOutputData(OH_AVCodec *codec, uint32_t index);

/**
 * @brief Notifies a video encoder that input streams end. You are advised to use this function for notification. This
 * function is used only in surface mode. In buffer mode, OH_AVBuffer is used to carry the EOS information to notify
 * the end of the input stream.
 *
 * @param codec Pointer to a video encoder instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state.
 * @since 9
 */
OH_AVErrCode OH_VideoEncoder_NotifyEndOfStream(OH_AVCodec *codec);

/**
 * @brief Pushes the input buffer filled with data to a video encoder.
 *
 * @param codec Pointer to a video encoder instance.
 * @param index Index of the input buffer. The value is provided by {@link OH_AVCodecOnNeedInputData}.
 * @param attr Description of the data contained in the buffer.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}:<br>1. The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>2. The index is invalid. This error does not affect the subsequent encoding process.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state.
 * @deprecated since 11
 * @useinstead OH_VideoEncoder_PushInputBuffer
 * @since 10
 */
OH_AVErrCode OH_VideoEncoder_PushInputData(OH_AVCodec *codec, uint32_t index, OH_AVCodecBufferAttr attr);

/**
 * @brief Pushes the OH_AVBuffer corresponding to the index to a video encoder in buffer mode.
 *
 * @param codec Pointer to an OH_AVCodec instance
 * @param index Enter the index value corresponding to the Buffer
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: instance has already released.
 *     <br>{@link AV_ERR_INVALID_VAL}:<br>1. The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>2. The index is invalid. This error does not affect the subsequent encoding process.
 *     <br>{@link AV_ERR_UNKNOWN}: unknown error.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state.
 * @since 11
 */
OH_AVErrCode OH_VideoEncoder_PushInputBuffer(OH_AVCodec *codec, uint32_t index);

/**
 * @brief Pushes the parameter configured for a frame with the given index to a video encoder in surface mode.
 *
 * @param codec Pointer to a video encoder instance.
 * @param index Index of the input parameter buffer. The value is provided by {@link OH_AVCodecOnNeedInputBuffer}.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}:<br>1. The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>2. The index is invalid. This error does not affect the subsequent encoding process.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state.
 * @since 12
 */
OH_AVErrCode OH_VideoEncoder_PushInputParameter(OH_AVCodec *codec, uint32_t index);

/**
 * @brief Returns the processed OH_AVBuffer corresponding to the index to a video encoder. You need to call this
 * function to release the output buffer in a timely manner. Otherwise, the encoding process is blocked.
 *
 * For details, see step 13 in surface mode or step 11 in buffer mode in
 * [Video Encoding](docroot://media/avcodec/video-encoding.md#surface-mode).
 *
 * @param codec Pointer to a video encoder instance.
 * @param index Index of the output buffer. The value is provided by {@link OH_AVCodecOnNeedInputBuffer}.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: An internal exception occurs in the encoder instance, for example,
 *     an unexpected nullptr.
 *     <br>{@link AV_ERR_INVALID_VAL}:<br>1. The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>2. The index is invalid. This error does not affect the subsequent encoding process.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: operation not permitted.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state.
 * @since 11
 */
OH_AVErrCode OH_VideoEncoder_FreeOutputBuffer(OH_AVCodec *codec, uint32_t index);

/**
 * @brief Obtains the index of the next available input buffer.
 *
 * After calling this function, you must call {@link OH_VideoEncoder_GetInputBuffer} to obtain the buffer instance and
 * call {@link OH_VideoEncoder_PushInputBuffer} to pass the buffer instance to the encoder.
 *
 * Note that the preceding operations are supported only in synchronous mode.
 *
 * @param codec Pointer to a video encoder instance.
 * @param index Pointer to the index of the input buffer.
 * @param timeoutUs Timeout duration, in microseconds. A negative value means to wait infinitely. The value **0** means
 *  to return immediately. A positive value means to wait for the specified time before exiting.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: The encoder instance has been destroyed.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: This function is called in asynchronous mode.
 *     <br>{@link AV_ERR_TRY_AGAIN_LATER}: The query fails. Try again after a short interval.
 * @since 20
 */
OH_AVErrCode OH_VideoEncoder_QueryInputBuffer(struct OH_AVCodec *codec, uint32_t *index, int64_t timeoutUs);

/**
 * @brief Obtains the instance of the available input buffer.
 *
 * Note that this function works only in synchronous mode.
 *
 * @param codec Pointer to a video encoder instance.
 * @param index Index of the input buffer. It can be obtained by calling {@link OH_VideoEncoder_QueryInputBuffer}.
 * @return Pointer to the OH_AVBuffer instance created. If the operation fails, NULL is returned.
 * @since 20
 */
OH_AVBuffer *OH_VideoEncoder_GetInputBuffer(struct OH_AVCodec *codec, uint32_t index);

/**
 * @brief Obtains the index of the next available output buffer. Through the buffer instance obtained via
 * {@link OH_VideoEncoder_GetOutputBuffer}, you can return the processed output buffer to the encoder by calling
 * {@link OH_VideoEncoder_FreeOutputBuffer}.
 *
 * Note that the preceding operations are supported only in synchronous mode.
 *
 * @param codec Pointer to a video encoder instance.
 * @param index Pointer to the index of the output buffer.
 * @param timeoutUs Timeout duration, in microseconds. A negative value means to wait infinitely. The value **0** means
 *     to return immediately. A positive value means to wait for the specified time before exiting.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_NO_MEMORY}: The encoder instance has been destroyed.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 *     <br>{@link AV_ERR_UNKNOWN}: An unknown error occurs.
 *     <br>{@link AV_ERR_INVALID_STATE}: This API cannot be called in the current encoder state.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: This function is called in asynchronous mode.
 *     <br>{@link AV_ERR_STREAM_CHANGED}: The stream format has changed. You can call
 *     {@link OH_VideoEncoder_GetOutputDescription} to obtain the new stream information.
 *     <br>{@link AV_ERR_TRY_AGAIN_LATER}: The query fails. Try again after a short interval.
 * @since 20
 */
OH_AVErrCode OH_VideoEncoder_QueryOutputBuffer(struct OH_AVCodec *codec, uint32_t *index, int64_t timeoutUs);

/**
 * @brief Obtains the instance of the available output buffer.
 *
 * Note that this function works only in synchronous mode.
 *
 * @param codec Pointer to a video encoder instance.
 * @param index Index of the output buffer. It can be obtained by calling {@link OH_VideoEncoder_QueryOutputBuffer}.
 * @return Pointer to the OH_AVBuffer instance created. If the operation fails, NULL is returned.
 * @since 20
 */
OH_AVBuffer *OH_VideoEncoder_GetOutputBuffer(struct OH_AVCodec *codec, uint32_t index);

/**
 * @brief Obtains the description of the image received by a video encoder. This function must be called after 
 * {@link OH_VideoEncoder_Configure} is called.
 *
 * You must call {@link OH_AVFormat_Destroy} to release the OH_AVFormat instance in the return value.
 *
 * @param codec Pointer to a video encoder instance.
 * @return Pointer to an OH_AVFormat instance.
 *     <br>If the value of **codec** is nullptr or does not point to an encoder instance, NULL is returned.
 * @since 10
 */
OH_AVFormat *OH_VideoEncoder_GetInputDescription(OH_AVCodec *codec);

/**
 * @brief Checks whether the encoder service is valid when an encoder instance exists.
 *
 * @param codec Pointer to a video encoder instance.
 * @param isValid Pointer of the Boolean type. The value indicates the validity of the encoder service only when the
 *     function returns {@link AV_ERR_OK}. The value **true** means that the encoder service is valid,
 *     and **false** means the opposite. It is recommended that you initialize **isValid** to **false**.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **codec** is nullptr or does not point to an encoder instance.
 * @since 10
 */
OH_AVErrCode OH_VideoEncoder_IsValid(OH_AVCodec *codec, bool *isValid);

/**
 * @brief Enumerates the bit rate modes of a video encoder.
 *
 * @deprecated since 14
 * @useinstead OH_BitrateMode
 * @since 9
 */
typedef enum OH_VideoEncodeBitrateMode {
    /** constant bit rate mode.
     * @deprecated since 14
     * @useinstead BITRATE_MODE_CBR
     * @since 9
     */
    CBR = 0,
    /** variable bit rate mode.
     * @deprecated since 14
     * @useinstead BITRATE_MODE_VBR
     * @since 9
     */
    VBR = 1,
    /** constant quality mode.
     * @deprecated since 14
     * @useinstead BITRATE_MODE_CQ
     * @since 9
     */
    CQ = 2
} OH_VideoEncodeBitrateMode;
#ifdef __cplusplus
}
#endif
#endif // NATIVE_AVCODEC_VIDEOENCODER_H
/** @} */