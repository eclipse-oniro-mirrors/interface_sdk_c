/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
 * @addtogroup Drawing
 * @{
 *
 * @brief Provides functions such as 2D graphics rendering, text drawing, and image display.
 *
 * @since 12
 * @version 1.0
 */
/**
 * @file drawing_sampling_options.h
 *
 * @brief This file declares the functions related to sampling in the drawing module. It is used for image or texture
 * sampling.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_SAMPLING_OPTIONS_H
#define C_INCLUDE_DRAWING_SAMPLING_OPTIONS_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines an enum for the filter modes.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Nearest filter mode.
     */
    FILTER_MODE_NEAREST,
    /**
     * Linear filter mode.
     */
    FILTER_MODE_LINEAR,
} OH_Drawing_FilterMode;

/**
 * @brief Defines an enum for the mipmap modes.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Mipmap level ignored.
     */
    MIPMAP_MODE_NONE,
    /**
     * Nearest sampling from two adjacent mipmap levels.
     */
    MIPMAP_MODE_NEAREST,
    /**
     * Linear interpolation sampling between two adjacent mipmap levels.
     */
    MIPMAP_MODE_LINEAR,
} OH_Drawing_MipmapMode;

/**
 * @brief Creates an **OH_Drawing_SamplingOptions** object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **mipmapMode** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param filterMode Filter sampling mode.
 * @param mipmapMode Mipmap mode.
 * @return Returns a pointer to the created {@link OH_Drawing_SamplingOptions} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_SamplingOptions* OH_Drawing_SamplingOptionsCreate(OH_Drawing_FilterMode filterMode,
    OH_Drawing_MipmapMode mipmapMode);

/**
 * @brief Creates a copy of an {@link OH_Drawing_SamplingOptions} object.
 *
 * @param samplingOptions Pointer to the {@link OH_Drawing_SamplingOptions} object.
 * @return Returns a pointer to the created {@link OH_Drawing_SamplingOptions} object copy. If NULL is returned, the
 * creation fails. The possible failure cause is that no memory is available or **samplingOptions** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_SamplingOptions* OH_Drawing_SamplingOptionsCopy(OH_Drawing_SamplingOptions* samplingOptions);

/**
 * @brief Destroys an **OH_Drawing_SamplingOptions** object and reclaims the memory occupied by the object.
 *
 * @param samplingOptions Pointer to the {@link OH_Drawing_SamplingOptions} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SamplingOptionsDestroy(OH_Drawing_SamplingOptions* samplingOptions);

#ifdef __cplusplus
}
#endif
/** @} */
#endif