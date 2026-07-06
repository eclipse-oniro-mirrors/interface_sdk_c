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
 * @brief Provides APIs for generating an image at the specific time from a video resource.
 *
 * @syscap SystemCapability.Multimedia.Media.AVImageGenerator
 * @since 18
 */
/**
 * @file avimage_generator_base.h
 *
 * @brief The file declares the enums used by the AVImageGenerator.
 * 
 * @kit MediaKit
 * @library libavimage_generator.so
 * @since 18
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVIMAGE_GENERATOR_BASE_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVIMAGE_GENERATOR_BASE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the mappings between time points and video frames.
 * 
 * @since 18
 */
typedef enum OH_AVImageGenerator_QueryOptions {
    /**
     * Extracts the key frame at or next to the specified time.
     */
    OH_AVIMAGE_GENERATOR_QUERY_NEXT_SYNC = 0,
    /**
     * Extracts the key frame at or prior to the specified time.
     */
    OH_AVIMAGE_GENERATOR_QUERY_PREVIOUS_SYNC = 1,
    /**
     * Extracts the key frame closest to the specified time.
     */
    OH_AVIMAGE_GENERATOR_QUERY_CLOSEST_SYNC = 2,
    /**
     * Extracts the frame (not necessarily a key frame) closest to the specified time.
     */
    OH_AVIMAGE_GENERATOR_QUERY_CLOSEST = 3,
} OH_AVImageGenerator_QueryOptions;

#ifdef __cplusplus
}
#endif
#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_BASE_H
/** @} */
