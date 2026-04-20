/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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
 * @file drawing_brush.h
 *
 * @brief This file declares the functions related to the brush in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_BRUSH_H
#define C_INCLUDE_DRAWING_BRUSH_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Provides the declaration of an **OH_NativeColorSpaceManager** struct.
 *
 * @since 20
 */
typedef struct OH_NativeColorSpaceManager OH_NativeColorSpaceManager;

/**
 * @brief Creates an **OH_Drawing_Brush** object.
 *
 * @return Returns the pointer to the **OH_Drawing_Brush** object created.
 * @since 8
 * @version 1.0
 */
OH_Drawing_Brush* OH_Drawing_BrushCreate(void);

/**
 * @brief Copies an existing {@link OH_Drawing_Brush} object to create a new one.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @return Returns a pointer to the {@link OH_Drawing_Brush} object created. If NULL is returned, the creation fails.
 * The possible failure cause is that no memory is available or **brush** is NULL.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Brush* OH_Drawing_BrushCopy(OH_Drawing_Brush* brush);

/**
 * @brief Destroys an **OH_Drawing_Brush** object and reclaims the memory occupied by the object.
 *
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_BrushDestroy(OH_Drawing_Brush* brush);

/**
 * @brief Checks whether anti-aliasing is enabled for a brush. Anti-aliasing makes the pixels around the shape edges
 * semi-transparent.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @return Returns **true** if anti-aliasing is enabled; returns **false** otherwise.
 * @since 8
 * @version 1.0
 */
bool OH_Drawing_BrushIsAntiAlias(const OH_Drawing_Brush* brush);

/**
 * @brief Enables or disables anti-aliasing for a brush. Anti-aliasing makes the pixels around the shape edges semi-
 * transparent.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @param antiAlias Whether to enable anti-aliasing. The value **true** means to enable anti-aliasing, and **false**
 * means the opposite.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_BrushSetAntiAlias(OH_Drawing_Brush* brush, bool antiAlias);

/**
 * @brief Obtains the color of a brush. The color is used by the brush to fill in a shape.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @return Returns a 32-bit (ARGB) variable that describes the color.
 * @since 8
 * @version 1.0
 */
uint32_t OH_Drawing_BrushGetColor(const OH_Drawing_Brush* brush);

/**
 * @brief Sets the color for a brush. The color is used by the brush to fill in a shape.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @param color Color, which is a 32-bit (ARGB) variable.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_BrushSetColor(OH_Drawing_Brush* brush, uint32_t color);

/**
 * @brief Obtains the alpha value of a brush. This value is used by the alpha channel when the brush fills in a shape.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @return Returns an 8-bit variable that describes the alpha value.
 * @since 11
 * @version 1.0
 */
uint8_t OH_Drawing_BrushGetAlpha(const OH_Drawing_Brush* brush);

/**
 * @brief Sets the alpha value for a brush. This value is used by the alpha channel when the brush fills in a shape.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @param alpha Alpha value, which is an 8-bit variable.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_BrushSetAlpha(OH_Drawing_Brush* brush, uint8_t alpha);

/**
 * @brief Sets a color for this brush. The color will be used by the brush to fill in a shape.
 * The color is in ARGB format represented by floating-point numbers. The color space is specified by
 * {@link OH_NativeColorSpaceManager}.
 * If **colorSpaceManager** is a null pointer, the SRGB (standard red, green, and blue color space based on IEC 61966-2.
 * 1:1999) color space is used as the default value.
 *
 * @param brush Pointer to an {@link OH_Drawing_Brush} object.
 * @param a Alpha value of the color, which is a floating-point number ranging from 0.0 to 1.0. Values above 1.0
 * default to 1.0, while values below 0.0 default to 0.0.
 * @param r Red component of the color, which is a floating-point number ranging from 0.0 to 1.0. Values above 1.0
 * default to 1.0, while values below 0.0 default to 0.0.
 * @param g Green component of the color, which is a floating-point number ranging from 0.0 to 1.0. Values above 1.0
 * default to 1.0, while values below 0.0 default to 0.0.
 * @param b Blue component of the color, which is a floating-point number ranging from 0.0 to 1.0. Values above 1.0
 * default to 1.0, while values below 0.0 default to 0.0.
 * @param colorSpaceManager Pointer to an {@link OH_NativeColorSpaceManager} object.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **brush** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_BrushSetColor4f(OH_Drawing_Brush* brush, float a, float r, float g, float b,
    OH_NativeColorSpaceManager* colorSpaceManager);

/**
 * @brief Obtains the alpha value of the brush color.
 *
 * @param brush Pointer to an {@link OH_Drawing_Brush} object.
 * @param a Alpha value of the color. The value is a floating-point number ranging from 0.0 to 1.0.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **brush** or **a** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_BrushGetAlphaFloat(const OH_Drawing_Brush* brush, float* a);

/**
 * @brief Obtains the red component of the brush color.
 *
 * @param brush Pointer to an {@link OH_Drawing_Brush} object.
 * @param r Red component of the pen color. The value is a floating-point number ranging from 0.0 to 1.0.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **brush** or **r** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_BrushGetRedFloat(const OH_Drawing_Brush* brush, float* r);

/**
 * @brief Obtains the green component of the brush color.
 *
 * @param brush Pointer to an {@link OH_Drawing_Brush} object.
 * @param g Green component of the pen color. The value is a floating-point number ranging from 0.0 to 1.0.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **brush** or **g** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_BrushGetGreenFloat(const OH_Drawing_Brush* brush, float* g);

/**
 * @brief Obtains the blue component of the brush color.
 *
 * @param brush Pointer to an {@link OH_Drawing_Brush} object.
 * @param b Blue component of the pen color. The value is a floating-point number ranging from 0.0 to 1.0.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **brush** or **b** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_BrushGetBlueFloat(const OH_Drawing_Brush* brush, float* b);

/**
 * @brief Sets the shader effect for a brush.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @param shaderEffect Pointer to an **OH_Drawing_ShaderEffect** object. If NULL is passed in, the shader effect of the
 * brush will be cleared.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_BrushSetShaderEffect(OH_Drawing_Brush* brush, OH_Drawing_ShaderEffect* shaderEffect);

/**
 * @brief Sets the shadow layer for a brush. The shadow layer effect takes effect only when text is drawn.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @param shadowLayer Pointer to an **OH_Drawing_ShadowLayer** object. If NULL is passed in, the shadow layer effect of
 * the brush will be cleared.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_BrushSetShadowLayer(OH_Drawing_Brush* brush, OH_Drawing_ShadowLayer* shadowLayer);

/**
 * @brief Sets the filter {@link OH_Drawing_Filter} for a brush. The filter is a container that holds a mask filter and
 * color filter.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @param filter Pointer to an **OH_Drawing_Filter** object. If null is passed in, the filter will be cleared.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_BrushSetFilter(OH_Drawing_Brush* brush, OH_Drawing_Filter* filter);

/**
 * @brief Obtains the {@link OH_Drawing_Filter} object from the brush. The filter is a container that holds a mask
 * filter and color filter.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **brush** or **filter** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param brush Pointer to the {@link OH_Drawing_Brush} object.
 * @param filter Pointer to an {@link OH_Drawing_Filter} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_BrushGetFilter(OH_Drawing_Brush* brush, OH_Drawing_Filter* filter);

/**
 * @brief Sets a blender for a brush. The blender implements the specified blend mode.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **blendMode** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param brush Pointer to the {@link OH_Drawing_Brush} object.
 * @param blendMode Enumeration of blend modes.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_BrushSetBlendMode(OH_Drawing_Brush* brush, OH_Drawing_BlendMode blendMode);

/**
 * @brief Resets a brush to the initial state. All configured attributes are cleared.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param brush Pointer to the {@link OH_Drawing_Brush} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_BrushReset(OH_Drawing_Brush* brush);

#ifdef __cplusplus
}
#endif
/** @} */
#endif