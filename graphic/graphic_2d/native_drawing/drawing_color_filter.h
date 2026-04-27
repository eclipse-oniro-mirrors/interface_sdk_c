/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @since 11
 * @version 1.0
 */
/**
 * @file drawing_color_filter.h
 *
 * @brief This file declares the functions related to the color filter in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_COLOR_FILTER_H
#define C_INCLUDE_DRAWING_COLOR_FILTER_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an **OH_Drawing_ColorFilter** object with a given blend mode.
 *
 * @param color Color, which is a 32-bit (ARGB) variable.
 * @param blendMode Blend mode. For details about the available options, see {@link OH_Drawing_BlendMode}.
 * @return Returns the pointer to the **OH_Drawing_ColorFilter** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateBlendMode(uint32_t color, OH_Drawing_BlendMode blendMode);

/**
 * @brief Creates an **OH_Drawing_ColorFilter** object by combining another two color filters.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **outerColorFilter** or **innerColorFilter** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param outerColorFilter Pointer to the first color filter.
 * @param innerColorFilter Pointer to the second color filter.
 * @return Returns the pointer to the **OH_Drawing_ColorFilter** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateCompose(OH_Drawing_ColorFilter* outerColorFilter,
    OH_Drawing_ColorFilter* innerColorFilter);

/**
 * @brief Creates an **OH_Drawing_ColorFilter** object with a given 5x4 color matrix.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Matrix, which is represented by a floating-point array with a length of 20.
 * @return Returns the pointer to the **OH_Drawing_ColorFilter** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateMatrix(const float matrix[20]);

/**
 * @brief Creates an **OH_Drawing_ColorFilter** object that applies the sRGB gamma curve to the RGB channels.
 *
 * @return Returns the pointer to the **OH_Drawing_ColorFilter** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateLinearToSrgbGamma(void);

/**
 * @brief Creates an **OH_Drawing_ColorFilter** object that applies the RGB channels to the sRGB gamma curve.
 *
 * @return Returns the pointer to the **OH_Drawing_ColorFilter** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateSrgbGammaToLinear(void);

/**
 * @brief Creates a **ColorFilter** object that multiplies the luma into the alpha channel and sets the RGB channels to
 * zero.
 *
 * @return Returns the pointer to the **OH_Drawing_ColorFilter** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateLuma(void);

/**
 * @brief Creates a lighting color filter. It multiplies the RGB channel values by one color and then adds another
 * color value. The final output stays between 0 and 255.
 *
 * @param mulColor Color value used for multiplication.
 * @param addColor Color value used for addition.
 * @return Returns the pointer to the **OH_Drawing_ColorFilter** object created.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateLighting(uint32_t mulColor, uint32_t addColor);

/**
 * @brief Destroys an **OH_Drawing_ColorFilter** object and reclaims the memory occupied by the object.
 *
 * @param colorFilter Pointer to an **OH_Drawing_ColorFilter** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_ColorFilterDestroy(OH_Drawing_ColorFilter* colorFilter);

#ifdef __cplusplus
}
#endif
/** @} */
#endif