/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_image_filter.h
 *
 * @brief This file declares the functions related to the image filter in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_IMAGE_FILTER_H
#define C_INCLUDE_DRAWING_IMAGE_FILTER_H

#include "drawing_shader_effect.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an image filter with a given blur effect.
 *
 * @param sigmaX Standard deviation of the Gaussian blur to apply along the X axis. The value must be greater than 0.
 * @param sigmaY Standard deviation of the Gaussian blur to apply along the Y axis. The value must be greater than 0.
 * @param tileMode Tile mode of the shader effect. For details about the available options, see
 * {@link OH_Drawing_TileMode}
 * .
 * @param imageFilter Pointer to the filter to which the image filter will be applied. If NULL is passed in, the image
 * filter is directly applied to the original image.
 * @return Returns the pointer to the <b>OH_Drawing_ImageFilter</b> object created.
 * If nullptr is returned, the creation fails.
 * The possible cause of the failure is that the available memory is empty.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateBlur(float sigmaX, float sigmaY, OH_Drawing_TileMode tileMode,
    OH_Drawing_ImageFilter* imageFilter);

/**
 * @brief Creates an image filter with a given blur effect.
 *
 * @param sigmaX Standard deviation of the Gaussian blur to apply along the X axis. The value must be greater than 0.0.
 * @param sigmaY Standard deviation of the Gaussian blur to apply along the Y axis. The value must be greater than 0.0.
 * @param tileMode Tile mode of the shader effect. For details about the available options, see
 * {@link OH_Drawing_TileMode}
 * .
 * @param input Pointer to the filter to which the image filter will be applied. If NULL is passed in, the image filter
 * is directly applied to the original image.
 * @param rect Pointer to the rectangular region to be cropped. If NULL is passed in, the blur effect is directly
 * applied to the entire image.
 * @return Returns the pointer to the <b>OH_Drawing_ImageFilter</b> object created.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateBlurWithCrop(float sigmaX, float sigmaY,
    OH_Drawing_TileMode tileMode, OH_Drawing_ImageFilter* input, const OH_Drawing_Rect* rect);

/**
 * @brief Creates an **OH_Drawing_ImageFilter** object with a color filter effect. This API may return an error code.
 * For details, call {@link OH_Drawing_ErrorCodeGet}. If **colorFilter** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER**
 * is returned.
 *
 * @param colorFilter Pointer to an {@link OH_Drawing_ColorFilter} object.
 * @param imageFilter Pointer to the filter to which the image filter will be applied. If NULL is passed in, the image
 * filter is directly applied to the original image.
 * @return Returns the pointer to the <b>OH_Drawing_ImageFilter</b> object created.
 * If nullptr is returned, the creation fails.
 * The possible cause of the failure is that the available memory is empty or
 * a nullptr <b>OH_Drawing_ColorFilter</b> is passed.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateFromColorFilter(OH_Drawing_ColorFilter* colorFilter,
    OH_Drawing_ImageFilter* imageFilter);

/**
 * @brief Creates an offset filter to translate the input filter based on the specified vector.
 *
 * @param x Distance to translate on the X axis.
 * @param y Distance to translate on the Y axis.
 * @param imageFilter Filter to be translated. If NULL is passed in, the drawing result without the filtering effect is
 * translated.
 * @return Returns the pointer to the <b>OH_Drawing_ImageFilter</b> object created.
 * If nullptr is returned, the creation fails.
 * The possible cause of the failure is that the available memory is empty.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateOffset(float x, float y, OH_Drawing_ImageFilter* imageFilter);

/**
 * @brief Creates an **ImageFilter** object based on a shader.
 *
 * @param shaderEffect Shader effect to be applied to the image.
 * @return Returns the pointer to the <b>OH_Drawing_ImageFilter</b> object created.
 * If nullptr is returned, the creation fails.
 * The possible cause of the failure is that the available memory is empty or
 * a nullptr <b>OH_Drawing_ShaderEffect</b> is passed.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateFromShaderEffect(OH_Drawing_ShaderEffect* shaderEffect);

/**
 * @brief Destroys an **OH_Drawing_ImageFilter** object and reclaims the memory occupied by the object.
 *
 * @param imageFilter Pointer to an {@link OH_Drawing_ImageFilter} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ImageFilterDestroy(OH_Drawing_ImageFilter* imageFilter);

#ifdef __cplusplus
}
#endif
/** @} */
#endif