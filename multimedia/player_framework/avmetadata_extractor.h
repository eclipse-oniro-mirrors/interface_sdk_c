/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup AVMetadataExtractor
 * @{
 *
 * @brief Provides APIs of metadata capability for Media Source.
 *
 * @syscap SystemCapability.Multimedia.Media.AVMetadataExtractor
 * @since 18
 */
/**
 * @file avmetadata_extractor.h
 *
 * @brief The file declares the AVMetadataExtractor APIs. You can use the APIs to obtain metadata from media assets.
 * 
 * @kit MediaKit
 * @library libavmetadata_extractor.so
 * @since 18
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "native_averrors.h"
#include "avmetadata_extractor_base.h"
#include "native_avcodec_base.h"
#include "native_avformat.h"
#include "multimedia/image_framework/image/pixelmap_native.h"
#include "avmedia_source.h"
#include "avmedia_base.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief The struct describes the OH_AVMetadataExtractor type.
 * 
 * @since 18
 */
typedef struct OH_AVMetadataExtractor OH_AVMetadataExtractor;

/**
 * @brief Obtains the track description of a specified index from the media source. This function must be used after
 * resources are set.
 * 
 * @param extractor Pointer to the **OH_AVMetadataExtractor** instance.
 * @param index Index of the track description to be obtained.
 * @return Returns a pointer to an OH_AVFormat instance containing track description for success, nullptr for failure.
 * Possible failure causes: extractor is nullptr, no source set, or format is unsupported.
 * Note: User need release OH_AVFormat by {@link OH_AVFormat_Destroy} after use.
 * @since 23
 */
OH_AVFormat *OH_AVMetadataExtractor_GetTrackDescription(OH_AVMetadataExtractor *extractor, uint32_t index);

/**
 * @brief Obtains custom metadata from the media source. This function must be used after resources are set.
 * 
 * @param extractor Pointer to the **OH_AVMetadataExtractor** instance.
 * @return Returns a pointer to an OH_AVFormat instance containing custom metadata for success, nullptr for failure.
 * Possible failure causes: extractor is nullptr, no source set, or custom info not found.
 * Note: User need release OH_AVFormat by {@link OH_AVFormat_Destroy} after use.
 * @since 23
 */
OH_AVFormat *OH_AVMetadataExtractor_GetCustomInfo(OH_AVMetadataExtractor *extractor);

/**
 * @brief Sets the media source for the extractor.
 * 
 * @param extractor Pointer to the **OH_AVMetadataExtractor** instance.
 * @param source Media source to be set.
 * @return Function result code.
 * {@link AV_ERR_OK}: the execution is successful.
 * {@link AV_ERR_INVALID_VAL}: input extractor is nullptr or input source is invalid.
 * @since 23
 */
OH_AVErrCode OH_AVMetadataExtractor_SetMediaSource(OH_AVMetadataExtractor *extractor, OH_AVMediaSource *source);

/**
 * @brief Creates an **OH_AVMetadataExtractor** instance.
 * 
 * @return Returns a pointer to an OH_AVMetadataExtractor instance for success, nullptr for failure
 * Possible failure causes: failed to HstEngineFactory::CreateAVMetadataHelperEngine.
 * @since 18
 */
OH_AVMetadataExtractor* OH_AVMetadataExtractor_Create(void);

/**
 * @brief Sets a data source based on the media file descriptor.
 * 
 * @param extractor Pointer to the **OH_AVMetadataExtractor** instance.
 * @param fd File descriptor of the media source.
 * @param offset Offset of the media source in the file descriptor.
 * @param size Size of the media source.
 * @return Function result code.
 * {@link AV_ERR_OK}: the execution is successful.
 * {@link AV_ERR_INVALID_VAL}: input extractor is nullptr or input param is invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: operation not allowed.
 * {@link AV_ERR_NO_MEMORY}: internal memory allocation failed.
 * @since 18
 */
OH_AVErrCode OH_AVMetadataExtractor_SetFDSource(OH_AVMetadataExtractor* extractor,
    int32_t fd, int64_t offset, int64_t size);

/**
 * @brief Obtains metadata from a media asset.
 * This function must be called after {@link OH_AVMetadataExtractor_SetFDSource}.
 * 
 * @param extractor Pointer to the **OH_AVMetadataExtractor** instance.
 * @param avMetadata Pointer to the **OH_AVFormat** instance, which contains the obtained metadata.
 * @return Function result code.
 * {@link AV_ERR_OK}: the execution is successful.
 * {@link AV_ERR_INVALID_VAL}: input extractor is nullptr or input param is invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: operation not allowed.
 * {@link AV_ERR_UNSUPPORTED_FORMAT}: format is unsupported.
 * {@link AV_ERR_NO_MEMORY}: internal memory allocation failed.
 * {@link AV_ERR_IO_CLEARTEXT_NOT_PERMITTED}: http cleartext traffic is not permitted. Add since api 23.
 * @since 18
 */
OH_AVErrCode OH_AVMetadataExtractor_FetchMetadata(OH_AVMetadataExtractor* extractor, OH_AVFormat* avMetadata);

/**
 * @brief Obtains the cover of an audio album.
 * This function must be called after {@link OH_AVMetadataExtractor_SetFDSource}.
 * 
 * @param extractor Pointer to the **OH_AVMetadataExtractor** instance.
 * @param pixelMap Double pointer to the album cover obtained.
 * @return Function result code.
 * {@link AV_ERR_OK}: the execution is successful.
 * {@link AV_ERR_INVALID_VAL}: input extractor is nullptr or input param is invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: operation not allowed.
 * {@link AV_ERR_UNSUPPORTED_FORMAT}: format is unsupported.
 * {@link AV_ERR_NO_MEMORY}: internal memory allocation failed.
 * @since 18
 */
OH_AVErrCode OH_AVMetadataExtractor_FetchAlbumCover(OH_AVMetadataExtractor* extractor, OH_PixelmapNative** pixelMap);

/**
 * @brief Extracts an image at a specified time point from the video source. This function must be used after resources
 * are set.
 * 
 * @param extractor Pointer to the **OH_AVMetadataExtractor** instance.
 * @param timeUs Time (in microseconds) at which an image is extracted from the video resource.
 * @param seekMode Seek mode that defines the relationship between the specified time and the key frame. For details,
 * see {@link OH_AVMedia_SeekMode}.
 * @param outputParam Output parameter of the image, for example, the height or width of the image. For details, see {@link OH_AVMetadataExtractor_OutputParam}.
 * If this parameter is a null pointer, the original size of the video is used. Note: You need to use {@link OH_PixelmapNative_Destroy}
 * to release the pixel map after using it.
 * @param pixelMap Used to receive images extracted from the video source. For details, see {@link OH_PixelmapNative}.
 * @return Function result code.
 * {@link AV_ERR_OK}: the execution is successful.
 * {@link AV_ERR_INVALID_VAL}: the input param is invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: operation not allowed.
 * {@link AV_ERR_UNSUPPORTED_FORMAT}: format is unsupported.
 * {@link AV_ERR_SERVICE_DIED}: the service died.
 * {@link AV_ERR_IO_CLEARTEXT_NOT_PERMITTED}: http cleartext traffic is not permitted.
 * @since 23
 */
OH_AVErrCode OH_AVMetadataExtractor_FetchFrameByTime(OH_AVMetadataExtractor *extractor, int64_t timeUs,
    OH_AVMedia_SeekMode seekMode, const OH_AVMetadataExtractor_OutputParam* outputParam,
    OH_PixelmapNative** pixelMap);

/**
 * @brief Defines a callback used to obtain the frames captured by **AVMetadataExtractor**. Note: **frameInfo** is
 * automatically released after the callback. However, you need to use {@link OH_PixelmapNative_Destroy} to release **
 * frameInfo.image** to avoid memory leaks.
 * 
 * @since 23
 */
typedef void (*OH_AVMetadataExtractor_OnFrameFetched)(OH_AVMetadataExtractor *extractor,
    const OH_AVMetadataExtractor_FrameInfo* frameInfo, OH_AVErrCode code, void *userData);

/**
 * @brief Extracts images at multiple specified time points from the video source asynchronously. This function must be
 * used after resources are set.
 * 
 * @param extractor Pointer to the **OH_AVMetadataExtractor** instance.
 * @param timesUs The times array expected to fetch picture from the video resource. The unit is microsecond(us).
 * @param timesUsSize Length of the time point array.
 * @param seekMode Seek mode that defines the relationship between the specified time and the key frame. For details,
 * see {@link OH_AVMedia_SeekMode}.
 * @param outputParam Output parameter of the image, for example, the height or width of the image. For details, see {@link OH_AVMetadataExtractor_OutputParam}.
 * If this parameter is a null pointer, the original video size is used for the obtained frame.
 * @param onFrameInfoCallback Callback function invoked after each frame is extracted or fails to be extracted.
 * @param userData Pointer to the user-defined data passed to the callback function.
 * @return Function result code.
 * {@link AV_ERR_OK} if the execution is successful.
 * {@link AV_ERR_INVALID_VAL}: the input param is invalid.
 * {@link AV_ERR_SERVICE_DIED}: the service died.
 * {@link AV_ERR_IO_CLEARTEXT_NOT_PERMITTED}: http cleartext traffic is not permitted.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: operation not allowed. Returned by onFrameInfoCallback.
 * {@link AV_ERR_UNSUPPORTED_FORMAT}: format is unsupported. Returned by onFrameInfoCallback.
 * {@link AV_ERR_TIMEOUT}: the execution is times out. Returned by onFrameInfoCallback.
 * @since 23
 */
OH_AVErrCode OH_AVMetadataExtractor_FetchFramesByTimes(OH_AVMetadataExtractor *extractor, int64_t timesUs[], uint16_t timesUsSize,
    OH_AVMedia_SeekMode seekMode, const OH_AVMetadataExtractor_OutputParam* outputParam,
    OH_AVMetadataExtractor_OnFrameFetched onFrameInfoCallback, void* userData);

/**
 * @brief Cancels all batch image obtaining operations initiated by {@link OH_AVMetadataExtractor_FetchFramesByTimes}. If this function is called, the pending fetch operation is canceled and the result is marked as canceled in the {@link OH_AVMetadataExtractor_OnFrameFetched}
 * callback.
 *  
 * @param extractor Pointer to the **OH_AVMetadataExtractor** instance.
 * @since 23
 */
void OH_AVMetadataExtractor_CancelAllFetchFrames(OH_AVMetadataExtractor *extractor);

/**
 * @brief Releases the resources used by the **OH_AVMetadataExtractor** instance and destroys the instance.
 * 
 * @param extractor Pointer to the **OH_AVMetadataExtractor** instance.
 * @return Function result code.
 * {@link AV_ERR_OK}: the execution is successful.
 * {@link AV_ERR_INVALID_VAL}: input extractor is nullptr or input param is invalid.
 * @since 18
 */
OH_AVErrCode OH_AVMetadataExtractor_Release(OH_AVMetadataExtractor* extractor);

/**
 * @brief Creates an **OH_AVMetadataExtractor_OutputParam** instance.
 * 
 * @return The new OH_AVMetadataExtractor_OutputParam instance.
 * @since 23
 */
OH_AVMetadataExtractor_OutputParam* OH_AVMetadataExtractor_OutputParam_Create();

/**
 * @brief Releases the **OH_AVMetadataExtractor_OutputParam** instance.
 * 
 * @param outputParam Pointer to the **OH_AVMetadataExtractor_OutputParam** instance.
 * @since 23
 */
void OH_AVMetadataExtractor_OutputParam_Destroy(OH_AVMetadataExtractor_OutputParam* outputParam);

/**
 * @brief Sets the expected output size of the **OH_AVMetadataExtractor_OutputParam** instance. If **width** or **
 * height** is less than 0, the original width or height is used. If **width** or **height** is 0, the aspect ratio is
 * maintained and the image is scaled proportionally. If both **width** and **height** are greater than 0, they are
 * used to scale the image.
 * 
 * @param outputParam Pointer to the **OH_AVMetadataExtractor_OutputParam** instance.
 * @param width Expected width of the output image, which can be scaled if necessary.
 * @param height Expected height of the output image, which can be scaled if necessary.
 * @return The return value is TRUE for success, FALSE for failure.
 * Possible failure causes: outputParam is nullptr.
 * @since 23
 */
bool OH_AVMetadataExtractor_OutputParam_SetSize(OH_AVMetadataExtractor_OutputParam* outputParam,
    int32_t width, int32_t height);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_H
/** @} */
