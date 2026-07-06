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
 * @addtogroup AVImageGenerator
 * @{
 *
 * @brief Provides APIs for generating an image at a specific time from a video resource.
 *
 * @syscap SystemCapability.Multimedia.Media.AVImageGenerator
 * @since 18
 */
/**
 * @file avimage_generator.h
 *
 * @brief The file declares the AVImageGenerator APIs. You can use the APIs to extract video frames at given time
 * points from videos.
 * 
 * @kit MediaKit
 * @library libavimage_generator.so
 * @since 18
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVIMAGE_GENERATOR_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVIMAGE_GENERATOR_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "native_averrors.h"
#include "avimage_generator_base.h"
#include "multimedia/image_framework/image/pixelmap_native.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The OH_AVImageGenerator struct describes the type used for generating video frames at specified timestamps.
 * 
 * @since 18
 */
typedef struct OH_AVImageGenerator OH_AVImageGenerator;

/**
 * @brief Creates an OH_AVImageGenerator instance, which is used to generate video frames at given time points.
 * 
 * @return Returns a pointer to an OH_AVImageGenerator instance for success, nullptr for failure.
 * Possible failure causes: HstEngineFactory failed to CreateAVMetadataHelperEngine.
 * @since 18
 */
OH_AVImageGenerator* OH_AVImageGenerator_Create(void);

/**
 * @brief Sets a data source based on the media file descriptor.
 * 
 * @param generator Pointer to the OH_AVImageGenerator instance.
 * @param fd File descriptor of the media source.
 * @param offset Offset of the media source in the file descriptor.
 * @param size Size of the media source.
 * @return Function result code.
 * {@link AV_ERR_OK}: the execution is successful.
 * {@link AV_ERR_INVALID_VAL}: input generator is nullptr or input param is invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: operation not allowed.
 * {@link AV_ERR_NO_MEMORY}: internal memory allocation failed.
 * @since 18
 */
OH_AVErrCode OH_AVImageGenerator_SetFDSource(OH_AVImageGenerator* generator,
    int32_t fd, int64_t offset, int64_t size);

/**
 * @brief Extracts a video frame at a given time from a video.
 * 
 * @param generator Pointer to the OH_AVImageGenerator instance.
 * @param timeUs Time point of the video frame to be extracted in the video, in μs.
 * @param options Mappings between the given time points and video frames.
 * @param pixelMap Double pointer to the video frame object obtained.
 * @return Function result code.
 * {@link AV_ERR_OK}: the execution is successful.
 * {@link AV_ERR_INVALID_VAL}: input generator is nullptr or input param is invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: operation not allowed.
 * {@link AV_ERR_UNSUPPORTED_FORMAT}: format is unsupported.
 * {@link AV_ERR_NO_MEMORY}: internal memory allocation failed.
 * @since 18
 */
OH_AVErrCode OH_AVImageGenerator_FetchFrameByTime(OH_AVImageGenerator* generator,
    int64_t timeUs, OH_AVImageGenerator_QueryOptions options, OH_PixelmapNative** pixelMap);

/**
 * @brief Releases the resources used by the OH_AVImageGenerator instance and destroys the instance.
 * 
 * @param generator Pointer to the OH_AVImageGenerator instance.
 * @return Function result code.
 * {@link AV_ERR_OK}: the execution is successful.
 * {@link AV_ERR_INVALID_VAL}: input generator is nullptr or input param is invalid.
 * @since 18
 */
OH_AVErrCode OH_AVImageGenerator_Release(OH_AVImageGenerator* generator);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVIMAGE_GENERATOR_H
/** @} */
