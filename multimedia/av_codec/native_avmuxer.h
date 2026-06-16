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

/**
 * @addtogroup AVMuxer
 * @{
 *
 * @brief The AVMuxer module provides functions for audio and video muxer.
 *
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @since 10
 */

/**
 * @file native_avmuxer.h
 *
 * @brief The file declares the native APIs used for audio and video multiplexing.
 *
 * @kit AVCodecKit
 * @library libnative_media_avmuxer.so
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @since 10
 */

#ifndef NATIVE_AVMUXER_H
#define NATIVE_AVMUXER_H

#include <stdint.h>
#include <stdio.h>
#include "native_avcodec_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct describes a native object for the muxer interface.
 *
 * @since 10
 */
typedef struct OH_AVMuxer OH_AVMuxer;

/**
 * @brief Creates an OH_AVMuxer instance by using the file descriptor and container format.
 *
 * @param fd File descriptor (FD). You must open the file in read/write mode (O_RDWR) and close the file after
 *     using it.
 * @param format Format of the multiplexed output file.
 * @return Pointer to the **OH_AVMuxer** instance created. You must call {@link OH_AVMuxer_Destroy} to destroy the
 *     instance when it is no longer needed.
 * @since 10
 */
OH_AVMuxer *OH_AVMuxer_Create(int32_t fd, OH_AVOutputFormat format);

/**
 * @brief Sets the rotation angle (clockwise), which must be 0, 90, 180, or 270, of an output video. This function must
 * be called before {@link OH_AVMuxer_Start}.
 *
 * @param muxer Pointer to an OH_AVMuxer instance.
 * @param rotation Angle to set. The value must be 0, 90, 180, or 270.
 * @return **AV_ERR_OK**: The operation is successful.
 *     <br>**AV_ERR_INVALID_VAL**: The muxer pointer is null or the value of **rotation** is invalid.
 *     <br>**AV_ERR_OPERATE_NOT_PERMIT**: The function is called out of sequence.
 * @since 10
 */
OH_AVErrCode OH_AVMuxer_SetRotation(OH_AVMuxer *muxer, int32_t rotation);

/**
 * @brief Set format to the muxer.
 *
 * @syscap SystemCapability.Multimedia.Media.Muxer
 * @param muxer Pointer to an OH_AVMuxer instance
 * @param format OH_AVFormat handle pointer contain format
 * @return Returns AV_ERR_OK if the execution is successful
 *         {@link AV_ERR_INVALID_VAL}, the muxer or format is invalid
 *         {@link AV_ERR_OPERATE_NOT_PERMIT}, not permit to call the interface, it was called in invalid state
 * @since 14
 */
OH_AVErrCode OH_AVMuxer_SetFormat(OH_AVMuxer *muxer, OH_AVFormat *format);

/**
 * @brief Adds an audio or video track to a muxer. Each time this function is called, an audio or video track is added
 * to the muxer. This function must be called before {@link OH_AVMuxer_Start}.
 *
 * @param muxer Pointer to an OH_AVMuxer instance.
 * @param trackIndex Pointer to the index of the media track. The index will be used in the
 *     {@link OH_AVMuxer_WriteSample} function. If the media track is added, the index value is greater than or equal
 *     to 0; otherwise, the value is less than 0.
 * @param trackFormat Pointer to an OH_AVFormat instance.
 * @return **AV_ERR_OK**: The operation is successful.
 *     <br>**AV_ERR_INVALID_VAL**: The muxer pointer is null, or the track index or track format is invalid.
 *     <br>**AV_ERR_OPERATE_NOT_PERMIT**: The function is called out of sequence.
 *     <br>**AV_ERR_UNSUPPORT**: The MIME type is not supported.
 *     <br>**AV_ERR_NO_MEMORY**: Memory allocation fails.
 *     <br>**AV_ERR_UNKNOWN**: An unknown error occurs.
 * @since 10
 */
OH_AVErrCode OH_AVMuxer_AddTrack(OH_AVMuxer *muxer, int32_t *trackIndex, OH_AVFormat *trackFormat);

/**
 * @brief Starts a muxer. This function must be called after {@link OH_AVMuxer_AddTrack} and before
 * {@link OH_AVMuxer_WriteSample}.
 *
 * @param muxer Pointer to an OH_AVMuxer instance.
 * @return **AV_ERR_OK**: The operation is successful.
 *     <br>**AV_ERR_INVALID_VAL**: The muxer pointer is null.
 *     <br>**AV_ERR_OPERATE_NOT_PERMIT**: The function is called out of sequence.
 *     <br>**AV_ERR_UNKNOWN**: An unknown error occurs.
 * @since 10
 */
OH_AVErrCode OH_AVMuxer_Start(OH_AVMuxer *muxer);

/**
 * @brief Writes a sample to a muxer. This function must be called after {@link OH_AVMuxer_Start} and before
 * {@link OH_AVMuxer_Stop}. The caller must write the sample to the correct audio or video track based on the timing in
 * **info**.
 *
 * @param muxer Pointer to an OH_AVMuxer instance.
 * @param trackIndex Index of the audio or video track corresponding to the data.
 * @param sample Pointer to the data obtained after encoding or demultiplexing.
 * @param info Sample description.
 * @return **AV_ERR_OK**: The operation is successful.
 *     <br>**AV_ERR_INVALID_VAL**: The muxer pointer is null, or the track index, sample, or info is invalid.
 *     <br>**AV_ERR_OPERATE_NOT_PERMIT**: The function is called out of sequence.
 *     <br>**AV_ERR_NO_MEMORY**: Memory allocation fails.
 *     <br>**AV_ERR_UNKNOWN**: An unknown error occurs.
 * @deprecated since 11
 * @useinstead OH_AVMuxer_WriteSampleBuffer
 * @since 10
 */
OH_AVErrCode OH_AVMuxer_WriteSample(OH_AVMuxer *muxer, uint32_t trackIndex,
    OH_AVMemory *sample, OH_AVCodecBufferAttr info);

/**
 * @brief Writes a sample to a muxer. This function must be called after {@link OH_AVMuxer_Start} and before
 * {@link OH_AVMuxer_Stop}. The caller must write the sample to the correct audio or video track based on the timing in
 * **sample**.
 *
 * @param muxer Pointer to an OH_AVMuxer instance.
 * @param trackIndex Index of the audio or video track corresponding to the data.
 * @param sample Pointer to the data and properties obtained after encoding or demultiplexing.
 * @return **AV_ERR_OK**: The operation is successful.
 *     <br>**AV_ERR_INVALID_VAL**: The muxer pointer is null, or the track index or sample is invalid.
 *     <br>**AV_ERR_OPERATE_NOT_PERMIT**: The function is called out of sequence.
 *     <br>**AV_ERR_NO_MEMORY**: Memory allocation fails.
 *     <br>**AV_ERR_UNKNOWN**: An unknown error occurs.
 * @since 11
 */
OH_AVErrCode OH_AVMuxer_WriteSampleBuffer(OH_AVMuxer *muxer, uint32_t trackIndex,
    const OH_AVBuffer *sample);

/**
 * @brief Stops a muxer. Once the muxer is stopped, it cannot be restarted.
 *
 * @param muxer Pointer to an OH_AVMuxer instance.
 * @return **AV_ERR_OK**: The operation is successful.
 *     <br>**AV_ERR_INVALID_VAL**: The muxer pointer is null.
 *     <br>**AV_ERR_OPERATE_NOT_PERMIT**: The function is called out of sequence.
 * @since 10
 */
OH_AVErrCode OH_AVMuxer_Stop(OH_AVMuxer *muxer);

/**
 * @brief Clears internal resources and destroys an OH_AVMuxer instance.
 *
 * @param muxer Pointer to an OH_AVMuxer instance.
 * @return **AV_ERR_OK**: The operation is successful.
 *     <br>**AV_ERR_INVALID_VAL**: The muxer pointer is null.
 * @since 10
 */
OH_AVErrCode OH_AVMuxer_Destroy(OH_AVMuxer *muxer);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVMUXER_H
/** @} */