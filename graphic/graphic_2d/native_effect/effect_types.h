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
 * @brief Provides APIs for obtaining effect filter and information.
 *
 * @since 12
 */

/**
 * @file effect_types.h
 *
 * @brief This file declares the data types of the image effect filter.
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
 * @brief Defines a struct for a filter used to generate a filter PixelMap.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Filter OH_Filter;

/**
 * @brief Defines a pixel map defined by the image framework.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_PixelmapNative OH_PixelmapNative;

/**
 * @brief Describes a matrix used to create an effect filter.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Filter_ColorMatrix {
    /** Custom color matrix. The value is a 5 x 4 array. */
    float val[20];
} OH_Filter_ColorMatrix;

/**
 * @brief Enumerates the status codes that may be used by the effect filter.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /** Operation successful. */
    EFFECT_SUCCESS = 0,
    /** Invalid parameter. */
    EFFECT_BAD_PARAMETER = 401,
    /** Unsupported operation. */
    EFFECT_UNSUPPORTED_OPERATION = 7600201,
    /** Unknown error. */
    EFFECT_UNKNOWN_ERROR = 7600901,
} EffectErrorCode;

/**
 * @brief Enumerates the tile modes of the shader effect.
 *
 * @since 14
 */
typedef enum {
    /** Replicates the edge color if the shader effect draws outside of its original boundary. */
    CLAMP = 0,
    /** Repeats the shader effect in both horizontal and vertical directions. */
    REPEAT,
    /** Repeats the shader effect in both horizontal and vertical directions, alternating mirror images. */
    MIRROR,
    /** Renders the shader effect only within the original boundary. */
    DECAL,
} EffectTileMode;

#ifdef __cplusplus
}
#endif

/** @} */
#endif