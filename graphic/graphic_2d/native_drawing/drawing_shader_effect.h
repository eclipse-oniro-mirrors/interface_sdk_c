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
 * @since 11
 * @version 1.0
 */
/**
 * @file drawing_shader_effect.h
 *
 * @brief This file declares the functions related to the shader effect in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_SHADER_EFFECT_H
#define C_INCLUDE_DRAWING_SHADER_EFFECT_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines an enum for the tile modes of the shader effect.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * Replicates the edge color if the shader effect draws outside of its original boundary.
     */
    CLAMP,
    /**
     * Repeats the shader effect's image in both horizontal and vertical directions.
     */
    REPEAT,
    /**
     * Repeats the shader effect's image in both horizontal and vertical directions, alternating mirror images.
     */
    MIRROR,
    /**
     * Renders the shader effect's image only within the original boundary, and returns transparent black elsewhere.
     */
    DECAL,
} OH_Drawing_TileMode;

/**
 * @brief Creates an **OH_Drawing_ShaderEffect** object with a single color.
 *
 * @param color Color in the ARGB format. The value is a 32-bit unsigned integer.
 * @return Returns the pointer to the {@link OH_Drawing_ShaderEffect} object created. If NULL is returned, the creation
 * fails. The possible failure cause is that no memory is available.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateColorShader(const uint32_t color);

/**
 * @brief Creates a **ShaderEffect** object that generates a linear gradient between two points.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **startPt**, **endPt**, and **colors** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **tileMode** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param startPt Start point.
 * @param endPt End point.
 * @param colors Colors to distribute between the two points.
 * @param pos Relative position of each color in the color array. The array length must be the same as that of **colors*
 * *. If **pos** is NULL, colors are evenly distributed between the start point and end point.
 * @param size Number of colors and positions (if **pos** is not NULL).
 * @param tileMode Tile mode of the shader effect. For details about the available options, see
 * {@link OH_Drawing_TileMode}
 * .
 * @return Returns the pointer to the **OH_Drawing_ShaderEffect** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateLinearGradient(const OH_Drawing_Point* startPt,
    const OH_Drawing_Point* endPt, const uint32_t* colors,
    const float* pos, uint32_t size, OH_Drawing_TileMode tileMode);

/**
 * @brief Creates a **ShaderEffect** object that generates a linear gradient between two points.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **startPt**, **endPt**, and **colors** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **tileMode** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param startPt Start point.
 * @param endPt End point.
 * @param colors Colors to distribute between the two points.
 * @param pos Relative position of each color in the color array. The array length must be the same as that of **colors*
 * *. If **pos** is NULL, colors are evenly distributed between the start point and end point.
 * @param size Number of colors and positions (if **pos** is not NULL).
 * @param tileMode Tile mode of the shader effect. For details about the available options, see
 * {@link OH_Drawing_TileMode}
 * .
 * @param matrix Matrix applied on the shader effect. If **matrix** is NULL, an identity matrix is applied by default.
 * @return Returns the pointer to the {@link OH_Drawing_ShaderEffect} object created. If NULL is returned, the creation
 * fails. The possible failure cause is that no memory is available or at least one of the parameters **startPt**, **
 * endPt**, and **colors** is NULL.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateLinearGradientWithLocalMatrix(
    const OH_Drawing_Point2D* startPt, const OH_Drawing_Point2D* endPt, const uint32_t* colors, const float* pos,
    uint32_t size, OH_Drawing_TileMode tileMode, const OH_Drawing_Matrix* matrix);

/**
 * @brief Creates an **OH_Drawing_ShaderEffect** object that generates a radial gradient based on the center and radius
 * of a circle.
 * The radial gradient transitions colors from the center to the ending shape in a radial manner.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **centerPt** or **colors** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **tileMode** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param centerPt Center of the circle.
 * @param radius Radius of the gradient. The value should be a non-negative number.
 * @param colors Colors to distribute in the radial direction.
 * @param pos Relative position of each color in the color array. The array length must be the same as that of **colors*
 * *. If **pos** is NULL, colors are evenly distributed in the radial direction.
 * @param size Number of colors and positions (if **pos** is not NULL).
 * @param tileMode Tile mode of the shader effect. For details about the available options, see
 * {@link OH_Drawing_TileMode}
 * .
 * @return Returns the pointer to the **OH_Drawing_ShaderEffect** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateRadialGradient(const OH_Drawing_Point* centerPt, float radius,
    const uint32_t* colors, const float* pos, uint32_t size, OH_Drawing_TileMode tileMode);

/**
 * @brief Creates an **OH_Drawing_ShaderEffect** object that generates a radial gradient based on the center and radius
 * of a circle.
 * The radial gradient transitions colors from the center to the ending shape in a radial manner.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **centerPt** or **colors** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **tileMode** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param centerPt Center of the circle.
 * @param radius Radius of the gradient.
 * @param colors Colors to distribute in the radial direction.
 * @param pos Relative position of each color in the color array. The array length must be the same as that of **colors*
 * *. If **pos** is NULL, colors are evenly distributed in the radial direction.
 * @param size Number of colors and positions (if **pos** is not NULL).
 * @param tileMode Tile mode of the shader effect. For details about the available options, see
 * {@link OH_Drawing_TileMode}
 * .
 * @param matrix Matrix applied on the shader effect. If **matrix** is NULL, an identity matrix is applied by default.
 * @return Returns the pointer to the {@link OH_Drawing_ShaderEffect} object created. If NULL is returned, the creation
 * fails. The possible failure cause is that no memory is available or at least one of the parameters **centerPt** and *
 * *colors** is NULL.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateRadialGradientWithLocalMatrix(
    const OH_Drawing_Point2D* centerPt, float radius, const uint32_t* colors, const float* pos, uint32_t size,
    OH_Drawing_TileMode tileMode, const OH_Drawing_Matrix* matrix);

/**
 * @brief Creates an **OH_Drawing_ShaderEffect** object that generates a sweep gradient based on the matrix
 * transformation at the given center.
 * A sweep gradient paints a gradient in a sweeping arc ranging from 0° to 360°.
 *
 * @param centerPt Center of the circle.
 * @param colors Colors to distribute between the two points.
 * @param pos Relative position of each color in the color array. The array length must be the same as that of **colors*
 * *. If **pos** is NULL, colors are evenly distributed between the start angle (0°) and end angle (360°).
 * @param size Number of colors and positions (if **pos** is not NULL).
 * @param tileMode Tile mode of the shader effect. For details about the available options, see
 * {@link OH_Drawing_TileMode}
 * .
 * @param matrix Matrix applied on the shader effect. If **matrix** is NULL, an identity matrix is applied by default.
 * @return Returns the pointer to the {@link OH_Drawing_ShaderEffect} object created.
 * A null pointer is returned if any of the following conditions is met:
 * - The available memory is empty.
 * - **centerPt** or **colors** is NULL.
 * - The value of **tileMode** is out of the enumerated value range.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateSweepGradientWithLocalMatrix(
    const OH_Drawing_Point* centerPt, const uint32_t* colors, const float* pos, uint32_t size,
    OH_Drawing_TileMode tileMode, const OH_Drawing_Matrix* matrix);

/**
 * @brief Creates an **OH_Drawing_ShaderEffect** object that generates a sweep gradient based on the center.
 * A sweep gradient paints a gradient in a sweeping arc ranging from 0° to 360°.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **centerPt** or **colors** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **tileMode** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param centerPt Center of the circle.
 * @param colors Colors to distribute between the two points.
 * @param pos Relative position of each color in the color array. The array length must be the same as that of **colors*
 * *. If **pos** is NULL, colors are evenly distributed between the start angle (0°) and end angle (360°).
 * @param size Number of colors and positions (if **pos** is not NULL).
 * @param tileMode Tile mode of the shader effect. For details about the available options, see
 * {@link OH_Drawing_TileMode}
 * .
 * @return Returns the pointer to the {@link OH_Drawing_ShaderEffect} object created.
 * A null pointer is returned if any of the following conditions is met:
 * - The available memory is empty.
 * - **centerPt** or **colors** is NULL.
 * - The value of **tileMode** is out of the enumerated value range.
 * @since 11
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateSweepGradient(const OH_Drawing_Point* centerPt,
    const uint32_t* colors, const float* pos, uint32_t size, OH_Drawing_TileMode tileMode);

/**
 * @brief Creates an **OH_Drawing_ShaderEffect** object for an image shader. You are advised not to use the function
 * for the canvas of the capture type because it affects the performance.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **image** or **samplingOptions** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If either **tileX** or **tileY** is not set to one of the enumerated values, **
 * OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param image Pointer to the {@link OH_Drawing_Image} object.
 * @param tileX Tile mode of the shader effect in the horizontal direction. For details about the available options,
 * see {@link OH_Drawing_TileMode}.
 * @param tileY Tile mode of the shader effect in the vertical direction. For details about the available options, see
 * {@link OH_Drawing_TileMode}
 * .
 * @param samplingOptions Pointer to the {@link OH_Drawing_SamplingOptions} object.
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object. If the pointer array is empty, the identity matrix is
 * passed in.
 * @return Returns the pointer to the {@link OH_Drawing_ShaderEffect} object created.
 * A null pointer is returned if any of the following conditions is met:
 * - The available memory is empty.
 * - **image** or **samplingOptions** is NULL.
 * - The value of **tileX** or **tileY** is out of the enumerated value range.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateImageShader(OH_Drawing_Image* image,
    OH_Drawing_TileMode tileX, OH_Drawing_TileMode tileY, const OH_Drawing_SamplingOptions* samplingOptions,
    const OH_Drawing_Matrix* matrix);

/**
 * @brief Creates a PixelMap shader object.
 *
 * @param pixelMap Pointer to the {@link OH_Drawing_PixelMap} object.
 * @param tileX Tile mode of the shader effect in the horizontal direction. For details about the available options,
 * see {@link OH_Drawing_TileMode}.
 * @param tileY Tile mode of the shader effect in the vertical direction. For details about the available options, see
 * {@link OH_Drawing_TileMode}
 * .
 * @param samplingOptions Pointer to the {@link OH_Drawing_SamplingOptions} object.
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object. If the pointer array is empty, the identity matrix is
 * passed in.
 * @return Returns the pointer to the **OH_Drawing_ShaderEffect** object created.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreatePixelMapShader(OH_Drawing_PixelMap* pixelMap,
    OH_Drawing_TileMode tileX, OH_Drawing_TileMode tileY, const OH_Drawing_SamplingOptions* samplingOptions,
    const OH_Drawing_Matrix* matrix);

/**
 * @brief Creates an **OH_Drawing_ShaderEffect** object that generates a gradient between two given circles.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **startPt**, **endPt**, and **colors** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **tileMode** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param startPt Pointer to the center of the start circle.
 * @param startRadius Start radius of the gradient. The value should be a non-negative number.
 * @param endPt Pointer to the center of the end circle.
 * @param endRadius End radius of the gradient. The value should be a non-negative number.
 * @param colors Colors to distribute between the two circles.
 * @param pos Relative position of each color in the color array. The array length must be the same as that of **colors*
 * *. If **pos** is NULL, colors are evenly distributed between the two circles.
 * @param size Number of colors and positions (if **pos** is not NULL).
 * @param tileMode Tile mode of the shader effect. For details about the available options, see
 * {@link OH_Drawing_TileMode}
 * .
 * @param matrix Matrix applied on the shader effect. If **matrix** is NULL, an identity matrix is applied by default.
 * @return Returns the pointer to the {@link OH_Drawing_ShaderEffect} object created. If the returned pointer is NULL,
 * the creation fails. The possible causes are as follows:
 * - The available memory is empty.
 * - **startPt**, **endPt**, or **colors** is NULL.
 * - The value of **tileMode** is out of the enumerated value range.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateTwoPointConicalGradient(const OH_Drawing_Point2D* startPt,
    float startRadius, const OH_Drawing_Point2D* endPt, float endRadius, const uint32_t* colors, const float* pos,
    uint32_t size, OH_Drawing_TileMode tileMode, const OH_Drawing_Matrix* matrix);

/**
 * @brief Creates a shader by blending two existing shaders in a certain way.
 *
 * @param dst Shader that serves as the destination color in blend mode.
 * @param src Shader that serves as the source color in blend mode.
 * @param mode Blend mode.
 * @return Returns the pointer to the {@link OH_Drawing_ShaderEffect} object created.
 * If the returned pointer is NULL, the creation fails. The possible causes are as follows:
 * - The available memory is empty.
 * - **dst** or **src** is NULL.
 * - The value of **mode** is out of the enumerated value range.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateCompose(OH_Drawing_ShaderEffect* dst,
    OH_Drawing_ShaderEffect* src, OH_Drawing_BlendMode mode);

/**
 * @brief Destroys an **OH_Drawing_ShaderEffect** object and reclaims the memory occupied by the object.
 *
 * @param shaderEffect Pointer to an **OH_Drawing_ShaderEffect** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_ShaderEffectDestroy(OH_Drawing_ShaderEffect* shaderEffect);

#ifdef __cplusplus
}
#endif
/** @} */
#endif