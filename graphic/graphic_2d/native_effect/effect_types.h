/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup effectKit
 * @{
 *
 * @brief Provides basic image processing capabilities, including brightness adjustment, blurring, and grayscale conversion of the current image. It is suitable for scenarios where image filter effects need to be quickly implemented within an app, such as image editing, photo beautification, and camera filters. This helps developers quickly implement image effect processing without focusing on the underlying algorithm implementation, reducing development complexity.
 *
 * @since 12
 */

/**
 * @file effect_types.h
 *
 * @brief Declares the data types for filter effects, used to define the matrices, status codes, and tile modes for filter effects, and supports scenarios such as creating custom filter effects and processing image shader tiling.
 * @kit ArkGraphics2D
 * @library libnative_effect.so
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 12
 */

#ifndef C_INCLUDE_EFFECT_TYPES_H
#define C_INCLUDE_EFFECT_TYPES_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines a filter struct used with EffectKit module APIs to implement filter effect processing.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Filter OH_Filter;

/**
 * @brief Declares a pixel map object defined by the image framework.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_PixelmapNative OH_PixelmapNative;

/**
 * @brief Defines a 4x5 matrix for creating a filter effect, with elements of floating-point numbers.
 *
 * @since 12
 * @version 1.0
 */
struct OH_Filter_ColorMatrix {
    /** Custom color matrix used to implement image color transformation effects. The array contains 20 float elements,
     *  stored in row-major order, forming a 4x5 matrix.
     *  The first 4 columns correspond to the transformation coefficients of the R, G, B, and A channels,
     *  and the 5th column is the constant offset value. It is recommended that the element values be within [-1, 1].
     *  Values outside this range may cause color values to overflow or produce unexpected effects.
     */
    float val[20];
};

/**
 * @brief Enumerates the status codes of the filter effect.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /** The operation is successful. */
    EFFECT_SUCCESS = 0,
    /** Invalid parameter. Check the parameter type and range. */
    EFFECT_BAD_PARAMETER = 401,
    /** The operation is not supported. Check the API usage. */
    EFFECT_UNSUPPORTED_OPERATION = 7600201,
    /** An unidentified error occurred. Possible causes include abnormal system resources or improper API calling. Check the API call parameters and system resource status first. */
    EFFECT_UNKNOWN_ERROR = 7600901,
} EffectErrorCode;

/**
 * @brief Enumerates the tile modes of the shader effect.
 *
 * @since 14
 */
typedef enum {
    /** Clamp mode. If the shader effect exceeds its original bounds, the remaining area is filled with the edge color of the shader. Applicable to scenarios requiring a smooth transition to a solid color background. */
    CLAMP = 0,
    /** Repeat mode. Repeats the shader effect in both horizontal and vertical directions. Applicable to scenarios requiring seamless tiled textures, such as background pattern filling. */
    REPEAT,
    /** Mirror mode. Repeats the shader effect in both horizontal and vertical directions, alternating mirrored images so that adjacent images always join seamlessly. Applicable to scenarios requiring continuity while avoiding abrupt repeating edges, such as gradient backgrounds. */
    MIRROR,
    /** Decal mode. Renders the shader effect only within its original bounds. Applicable to scenarios requiring precise control over shader boundaries, where areas outside the bounds remain transparent or retain the original content. */
    DECAL,
} EffectTileMode;

#ifdef __cplusplus
}
#endif

/** @} */
#endif