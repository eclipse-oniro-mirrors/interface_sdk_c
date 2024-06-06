/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#ifndef NATIVE_AVCODEC_AUDIOCODEC_H
#define NATIVE_AVCODEC_AUDIOCODEC_H

#include <stdint.h>
#include <stdio.h>
#include "native_avcodec_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief MediaKeySession field.
 * @since 12
 * @version 1.0
 */
typedef struct MediaKeySession MediaKeySession;

/**
 * @brief Create an audio encoder or decoder instance from the mime type, which is recommended in most cases.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param mime mime type description string, refer to {@link AVCODEC_MIME_TYPE}
 * @param isEncoder true indicates the need to create an encoder, while false indicates the need to create a decoder.
 * @return Returns a Pointer to an OH_AVCodec instance
 * @since 11
 */
OH_AVCodec *OH_AudioCodec_CreateByMime(const char *mime, bool isEncoder);

/**
 * @brief Create an audio codec instance through the audio codec name.
 * The premise of using this interface is to know the exact name of the codec.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param name Audio codec name
 * @return Returns a Pointer to an OH_AVCodec instance
 * @since 11
 */
OH_AVCodec *OH_AudioCodec_CreateByName(const char *name);

/**
 * @brief Clear the internal resources of the codec and destroy the codec instance
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @return Returns AV_ERR_OK if the execution is successful,
 * otherwise returns a specific error code, refer to {@link OH_AVErrCode}
 * {@link AV_ERR_INVALID_VAL}, the codec is nullptr or invalid.
 * {@link AV_ERR_INVALID_STATE}, the interface was called in an invalid state.
 * {@link AV_ERR_NO_MEMORY}, inner resource has already released.
 * {@link AV_ERR_UNKNOWN}, internal error occurred, it is recommended to check the logs.
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_Destroy(OH_AVCodec *codec);

/**
 * @brief Set the asynchronous callback function so that your application
 * can respond to the events generated by the audio codec. This interface must be called before Prepare is called.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @param callback A collection of all callback functions, see {@link OH_AVCodecCallback}
 * @param userData User specific data
 * @return Returns AV_ERR_OK if the execution is successful,
 * otherwise returns a specific error code, refer to {@link OH_AVErrCode}
 * {@link AV_ERR_INVALID_VAL}, input parameter is empty or invalid.
 * {@link AV_ERR_INVALID_STATE}, the interface was called in an invalid state.
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_RegisterCallback(OH_AVCodec *codec, OH_AVCodecCallback callback, void *userData);

/**
 * @brief To configure the audio codec, typically, you need to configure the description information of the
 * audio track. This interface must be called before Prepare is called.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @param format A pointer to an OH_AVFormat giving a description of the audio track to be encoded or decoded
 * @return Returns AV_ERR_OK if the execution is successful,
 * otherwise returns a specific error code, refer to {@link OH_AVErrCode}
 * {@link AV_ERR_INVALID_VAL}, input parameter is empty or invalid.
 * {@link AV_ERR_INVALID_STATE}, the interface was called in an invalid state.
 * {@Link AV_ERR_OPERATE_NOT_PERMIT}, operation not permitted.
 * This could be due to an incorrect state or an unsupported operation.
 * {@link AV_ERR_UNKNOWN}, internal error occurred, it is recommended to check the logs.
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_Configure(OH_AVCodec *codec, const OH_AVFormat *format);

/**
 * @brief To prepare the internal resources of the codec, the Configure interface must be called
 * before calling this interface.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @return Returns AV_ERR_OK if the execution is successful,
 * otherwise returns a specific error code, refer to {@link OH_AVErrCode}
 * {@link AV_ERR_INVALID_VAL}, the codec is nullptr or invalid.
 * {@link AV_ERR_INVALID_STATE}, the interface was called in an invalid state.
 * {@Link AV_ERR_OPERATE_NOT_PERMIT}, operation not permitted.
 * This could be due to an incorrect state or an unsupported operation.
 * {@link AV_ERR_UNKNOWN}, internal error occurred, it is recommended to check the logs.
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_Prepare(OH_AVCodec *codec);

/**
 * @brief Start the codec, this interface must be called after the Prepare is successful.
 * After being successfully started, the codec will start reporting NeedInputData events.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @return Returns AV_ERR_OK if the execution is successful,
 * otherwise returns a specific error code, refer to {@link OH_AVErrCode}
 * {@link AV_ERR_INVALID_VAL}, the codec is nullptr or invalid.
 * {@link AV_ERR_INVALID_STATE}, the interface was called in an invalid state.
 * {@Link AV_ERR_OPERATE_NOT_PERMIT}, operation not permitted.
 * This could be due to an incorrect state or an unsupported operation.
 * {@link AV_ERR_UNKNOWN}, internal error occurred, it is recommended to check the logs.
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_Start(OH_AVCodec *codec);

/**
 * @brief Stop the codec. After stopping, you can re-enter the Started state through Start,
 * but it should be noted that need to re-enter if the codec has been input before
 * Codec-Specific-Data.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @return Returns AV_ERR_OK if the execution is successful,
 * otherwise returns a specific error code, refer to {@link OH_AVErrCode}
 * {@link AV_ERR_INVALID_VAL}, the codec is nullptr or invalid.
 * {@link AV_ERR_INVALID_STATE}, the interface was called in an invalid state.
 * {@Link AV_ERR_OPERATE_NOT_PERMIT}, operation not permitted.
 * This could be due to an incorrect state or an unsupported operation.
 * {@link AV_ERR_UNKNOWN}, internal error occurred, it is recommended to check the logs.
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_Stop(OH_AVCodec *codec);

/**
 * @brief Clear the input and output data buffered in the codec. After this interface is called, all the Buffer
 * indexes previously reported through the asynchronous callback will be invalidated, make sure not to access
 * the Buffers corresponding to these indexes.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @return Returns AV_ERR_OK if the execution is successful,
 * otherwise returns a specific error code, refer to {@link OH_AVErrCode}
 * {@link AV_ERR_INVALID_VAL}, the codec is nullptr or invalid.
 * {@link AV_ERR_INVALID_STATE}, the interface was called in an invalid state.
 * {@Link AV_ERR_OPERATE_NOT_PERMIT}, operation not permitted.
 * This could be due to an incorrect state or an unsupported operation.
 * {@link AV_ERR_UNKNOWN}, internal error occurred, it is recommended to check the logs.
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_Flush(OH_AVCodec *codec);

/**
 * @brief Reset the codec. To continue encoding or decoding, you need to call the Configure interface again to
 * configure the codec instance.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @return Returns AV_ERR_OK if the execution is successful,
 * otherwise returns a specific error code, refer to {@link OH_AVErrCode}
 * {@link AV_ERR_INVALID_VAL}, the codec is nullptr or invalid.
 * {@link AV_ERR_INVALID_STATE}, the interface was called in an invalid state.
 * @since 11
 */

OH_AVErrCode OH_AudioCodec_Reset(OH_AVCodec *codec);

/**
 * @brief Get the description information of the output data of the codec, refer to {@link OH_AVFormat} for details.
 * It should be noted that the life cycle of the OH_AVFormat instance pointed to by the return value * needs to
 * be manually released by calling {@link OH_AVFormat_Destroy}.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @return Returns the OH_AVFormat handle pointer, the life cycle is refreshed with the next GetOutputMediaDescription,
 * or destroyed with OH_AVCodec;
 * @since 11
 */
OH_AVFormat *OH_AudioCodec_GetOutputDescription(OH_AVCodec *codec);

/**
 * @brief Set dynamic parameters to the codec. Note: This interface can only be called after the codec is started.
 * At the same time, incorrect parameter settings may cause encoding or decoding failure.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @param format OH_AVFormat handle pointer
 * @return Returns AV_ERR_OK if the execution is successful,
 * otherwise returns a specific error code, refer to {@link OH_AVErrCode}
 * {@link AV_ERR_INVALID_VAL}, input parameter is empty or invalid.
 * {@link AV_ERR_INVALID_STATE}, the interface was called in an invalid state.
 * {@Link AV_ERR_OPERATE_NOT_PERMIT}, operation not permitted.
 * This could be due to an incorrect state or an unsupported operation.
 * {@link AV_ERR_UNKNOWN}, internal error occurred, it is recommended to check the logs.
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_SetParameter(OH_AVCodec *codec, const OH_AVFormat *format);

/**
 * @brief Submit the input buffer filled with data to the audio codec. The {@link OH_AVCodecOnNeedInputBuffer} callback
 * will report the available input buffer and the corresponding index value. Once the buffer with the specified index
 * is submitted to the audio codec, the buffer cannot be accessed again until the {@link OH_AVCodecOnNeedInputBuffer}
 * callback is received again reporting that the buffer with the same index is available. In addition, for some
 * codecs, it is required to input Codec-Specific-Data to the codec at the beginning to initialize the encoding or
 * decoding process of the codec.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @param index Enter the index value corresponding to the Buffer
 * @return Returns AV_ERR_OK if the execution is successful,
 * otherwise returns a specific error code, refer to {@link OH_AVErrCode}
 * {@link AV_ERR_INVALID_VAL}, input parameter is empty or invalid. Buffer index
 * should be given by {@link OH_AVCodecOnNeedInputBuffer}.
 * {@link AV_ERR_INVALID_STATE}, the interface was called in an invalid state.
 * {@Link AV_ERR_OPERATE_NOT_PERMIT}, operation not permitted.
 * This could be due to an incorrect state or an unsupported operation.
 * {@link AV_ERR_UNKNOWN}, internal error occurred, it is recommended to check the logs.
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_PushInputBuffer(OH_AVCodec *codec, uint32_t index);

/**
 * @brief Return the processed output Buffer to the codec.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @param index The index value corresponding to the output Buffer
 * @return Returns AV_ERR_OK if the execution is successful,
 * otherwise returns a specific error code, refer to {@link OH_AVErrCode}
 * {@link AV_ERR_INVALID_VAL}, input parameter is empty or invalid. Buffer index
 * should be given by {@link OH_AVCodecOnNewOutputBuffer}.
 * {@link AV_ERR_INVALID_STATE}, the interface was called in an invalid state.
 * {@Link AV_ERR_OPERATE_NOT_PERMIT}, operation not permitted.
 * This could be due to an incorrect state or an unsupported operation.
 * {@link AV_ERR_UNKNOWN}, internal error occurred, it is recommended to check the logs.
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_FreeOutputBuffer(OH_AVCodec *codec, uint32_t index);

/**
 * @brief Check whether the current codec instance is valid. It can be used fault recovery or app
 * switchback from the background
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @param isValid Output Parameter. A pointer to a boolean instance, it is true if the codec instance is valid,
 * false if the codec instance is invalid
 * @return Returns AV_ERR_OK if the execution is successful,
 * otherwise returns a specific error code, refer to {@link OH_AVErrCode}
 * {@link AV_ERR_INVALID_VAL}, input parameter is empty or invalid.
 * @since 11
 */
OH_AVErrCode OH_AudioCodec_IsValid(OH_AVCodec *codec, bool *isValid);

/**
 * @brief Set decryption info.
 * @syscap SystemCapability.Multimedia.Media.AudioCodec
 * @param codec Pointer to an OH_AVCodec instance
 * @param mediaKeySession A media key session instance with decryption function.
 * @param secureAudio Require secure decoder or not.
 * @return {@link AV_ERR_OK} 0 - Success
 *         {@link AV_ERR_INVALID_VAL} 3 - If the codec instance is nullptr or invalid,
 *         the mediaKeySession is nullptr or invalid.
 *         {@link AV_ERR_INVALID_STATE} 8 - If the codec service is invalid.
 * @since 12
 * @version 1.0
*/
OH_AVErrCode OH_AudioCodec_SetDecryptionConfig(OH_AVCodec *codec, MediaKeySession *mediaKeySession,
    bool secureAudio);
#ifdef __cplusplus
}
#endif
#endif // NATIVE_AVCODEC_AUDIOCODEC_H