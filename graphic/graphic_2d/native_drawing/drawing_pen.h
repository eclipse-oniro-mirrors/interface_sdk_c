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
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_pen.h
 *
 * @brief This file declares functions related to the pen in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_PEN_H
#define C_INCLUDE_DRAWING_PEN_H

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
 * @brief Creates an **OH_Drawing_Pen** object.
 *
 * @return Returns the pointer to the **OH_Drawing_Pen** object created.
 * @since 8
 * @version 1.0
 */
OH_Drawing_Pen* OH_Drawing_PenCreate(void);

/**
 * @brief Creates a copy of the {@link OH_Drawing_Pen} object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @return Returns the pointer to the {@link OH_Drawing_Pen} object created. If NULL is returned, the creation fails.
 * The possible failure cause is that no memory is available or **pen** is NULL.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Pen* OH_Drawing_PenCopy(OH_Drawing_Pen* pen);

/**
 * @brief Destroys an **OH_Drawing_Pen** object and reclaims the memory occupied by the object.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PenDestroy(OH_Drawing_Pen* pen);

/**
 * @brief Checks whether anti-aliasing is enabled for a pen. Anti-aliasing makes the pixels around the shape edges semi-
 * transparent.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @return Returns **true** if anti-aliasing is enabled; returns **false** otherwise.
 * @since 8
 * @version 1.0
 */
bool OH_Drawing_PenIsAntiAlias(const OH_Drawing_Pen* pen);

/**
 * @brief Enables or disables anti-aliasing for a pen. Anti-aliasing makes the pixels around the shape edges semi-
 * transparent.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @param antiAlias Whether to enable anti-aliasing. The value **true** means to enable anti-aliasing, and **false**
 * means the opposite.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PenSetAntiAlias(OH_Drawing_Pen* pen, bool antiAlias);

/**
 * @brief Obtains the color of a pen. The color is used by the pen to outline a shape.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @return Returns a 32-bit (ARGB) variable that describes the color.
 * @since 8
 * @version 1.0
 */
uint32_t OH_Drawing_PenGetColor(const OH_Drawing_Pen* pen);

/**
 * @brief Sets the color for a pen. The color is used by the pen to outline a shape.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @param color Color, which is a 32-bit (ARGB) variable.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PenSetColor(OH_Drawing_Pen* pen, uint32_t color);

/**
 * @brief Obtains the alpha value of a pen. This value is used by the alpha channel when the pen outlines a shape.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @return Returns an 8-bit variable that describes the alpha value.
 * @since 11
 * @version 1.0
 */
uint8_t OH_Drawing_PenGetAlpha(const OH_Drawing_Pen* pen);

/**
 * @brief Sets the alpha value for a pen. This value is used by the alpha channel when the pen outlines a shape.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @param alpha Alpha value, which is an 8-bit variable.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_PenSetAlpha(OH_Drawing_Pen* pen, uint8_t alpha);

/**
 * @brief Sets the color for a pen, which is used to outline a shape.
 * The color is in ARGB format represented by floating-point numbers. The color space is specified by
 * {@link OH_NativeColorSpaceManager}
 * .
 * If **colorSpaceManager** is a null pointer, the SRGB (standard red, green, and blue color space based on IEC 61966-2.
 * 1:1999) color space is used as the default value.
 *
 * @param pen Pointer to an {@link OH_Drawing_Pen} object.
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
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **pen** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PenSetColor4f(OH_Drawing_Pen* pen, float a, float r, float g, float b,
    OH_NativeColorSpaceManager* colorSpaceManager);

/**
 * @brief Obtains the alpha value of the pen color.
 *
 * @param pen Pointer to an {@link OH_Drawing_Pen} object.
 * @param a Alpha value of the pen color. The value is a floating-point number ranging from 0.0 to 1.0.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **pen** or **a** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PenGetAlphaFloat(OH_Drawing_Pen* pen, float* a);

/**
 * @brief Obtains the red component of the pen color.
 *
 * @param pen Pointer to an {@link OH_Drawing_Pen} object.
 * @param r Red component of the pen color. The value is a floating-point number ranging from 0.0 to 1.0.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **pen** or **r** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PenGetRedFloat(OH_Drawing_Pen* pen, float* r);

/**
 * @brief Obtains the green component of the pen color.
 *
 * @param pen Pointer to an {@link OH_Drawing_Pen} object.
 * @param g Green component of the pen color. The value is a floating-point number ranging from 0.0 to 1.0.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **pen** or **g** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PenGetGreenFloat(OH_Drawing_Pen* pen, float* g);

/**
 * @brief Obtains the blue component of the pen color.
 *
 * @param pen Pointer to an {@link OH_Drawing_Pen} object.
 * @param b Blue component of the pen color. The value is a floating-point number ranging from 0.0 to 1.0.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **pen** or **b** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PenGetBlueFloat(OH_Drawing_Pen* pen, float* b);

/**
 * @brief Obtains the thickness of a pen. This thickness determines the width of the outline of a shape.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @return Returns the thickness.
 * @since 8
 * @version 1.0
 */
float OH_Drawing_PenGetWidth(const OH_Drawing_Pen* pen);

/**
 * @brief Sets the thickness for a pen. This thickness determines the width of the outline of a shape.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @param width Thickness, which is a variable.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PenSetWidth(OH_Drawing_Pen* pen, float width);

/**
 * @brief Obtains the stroke miter limit of a polyline drawn by a pen. When the corner type is bevel, a beveled corner
 * is displayed if the miter limit is exceeded, and a mitered corner is displayed if the miter limit is not exceeded.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @return Returns the miter limit.
 * @since 8
 * @version 1.0
 */
float OH_Drawing_PenGetMiterLimit(const OH_Drawing_Pen* pen);

/**
 * @brief Sets the stroke miter limit for a polyline drawn by a pen. When the corner type is bevel, a beveled corner is
 * displayed if the miter limit is exceeded, and a mitered corner is displayed if the miter limit is not exceeded.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @param miter Stroke miter limit, which is a variable.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PenSetMiterLimit(OH_Drawing_Pen* pen, float miter);

/**
 * @brief Enumerates the line cap styles of a pen. The line cap style defines the style of both ends of a line segment
 * drawn by the pen.
 *
 * @since 8
 * @version 1.0
 */
typedef enum {
    /**
     * There is no cap style. Both ends of the line segment are cut off square.
     */
    LINE_FLAT_CAP,
    /**
     * Square cap style. Both ends have a square, the height of which is half of the width of the line segment, with
     * the same width.
     */
    LINE_SQUARE_CAP,
    /**
     * Round cap style. Both ends have a semicircle centered, the diameter of which is the same as the width of the
     * line segment.
     */
    LINE_ROUND_CAP
} OH_Drawing_PenLineCapStyle;

/**
 * @brief Obtains the line cap style of a pen.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @return Returns the line cap style.
 * @since 8
 * @version 1.0
 */
OH_Drawing_PenLineCapStyle OH_Drawing_PenGetCap(const OH_Drawing_Pen* pen);

/**
 * @brief Sets the line cap style for a pen.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **capStyle** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @param capStyle Line cap style, which is a variable.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PenSetCap(OH_Drawing_Pen* pen, OH_Drawing_PenLineCapStyle capStyle);

/**
 * @brief Enumerates the line join styles of a pen. The line join style defines the shape of the joints of a polyline
 * segment drawn by the pen.
 *
 * @since 8
 * @version 1.0
 */
typedef enum {
    /**
     * Mitered corner. If the angle of a polyline is small, its miter length may be inappropriate. In this case, you
     * need to use the miter limit to limit the miter length.
     */
    LINE_MITER_JOIN,
    /**
     * Round corner.
     */
    LINE_ROUND_JOIN,
    /**
     * Beveled corner.
     */
    LINE_BEVEL_JOIN
} OH_Drawing_PenLineJoinStyle;

/**
 * @brief Obtains the line join style of a pen.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @return Returns the line join style.
 * @since 8
 * @version 1.0
 */
OH_Drawing_PenLineJoinStyle OH_Drawing_PenGetJoin(const OH_Drawing_Pen* pen);

/**
 * @brief Sets the join style for this pen.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **joinStyle** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @param joinStyle Join style.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PenSetJoin(OH_Drawing_Pen* pen, OH_Drawing_PenLineJoinStyle joinStyle);

/**
 * @brief Sets the shader effect for this pen.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to the {@link OH_Drawing_Pen} object.
 * @param shaderEffect Pointer to an {@link OH_Drawing_ShaderEffect} object. If NULL is passed in, the shader effect
 * will be cleared.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_PenSetShaderEffect(OH_Drawing_Pen* pen, OH_Drawing_ShaderEffect* shaderEffect);

/**
 * @brief Sets the shadow layer for a pen. The shadow layer effect takes effect only when text is drawn.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to the {@link OH_Drawing_Pen} object.
 * @param shadowLayer Pointer to an {@link OH_Drawing_ShadowLayer} object. If NULL is passed in, the shadow layer
 * effect will be cleared.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PenSetShadowLayer(OH_Drawing_Pen* pen, OH_Drawing_ShadowLayer* shadowLayer);

/**
 * @brief Sets the path effect for this pen.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to the {@link OH_Drawing_Pen} object.
 * @param pathEffect Pointer to an {@link OH_Drawing_PathEffect} object. If NULL is passed in, the path effect will be
 * cleared.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PenSetPathEffect(OH_Drawing_Pen* pen, OH_Drawing_PathEffect* pathEffect);

/**
 * @brief Sets a filter for a pen.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to the {@link OH_Drawing_Pen} object.
 * @param filter Pointer to an {@link OH_Drawing_Filter} object. If NULL is passed in, the filter will be cleared.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_PenSetFilter(OH_Drawing_Pen* pen, OH_Drawing_Filter* filter);

/**
 * @brief Obtains the {@link OH_Drawing_Filter} object from the pen. The filter is a container that holds a mask filter
 * and color filter.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **pen** or **filter** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to the {@link OH_Drawing_Pen} object.
 * @param filter Pointer to an {@link OH_Drawing_Filter} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PenGetFilter(OH_Drawing_Pen* pen, OH_Drawing_Filter* filter);

/**
 * @brief Sets a blender for a pen. The blender implements the specified blend mode.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **blendMode** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param pen Pointer to the {@link OH_Drawing_Pen} object.
 * @param blendMode Enumeration of blend modes.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PenSetBlendMode(OH_Drawing_Pen* pen, OH_Drawing_BlendMode blendMode);

/**
 * @brief Obtains the source path outline drawn using this pen and represents it using a destination path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **pen**, **src**, and **dst** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to the {@link OH_Drawing_Pen} object.
 * @param src Pointer to the source {@link OH_Drawing_Path} object.
 * @param dst Pointer to the target {@link OH_Drawing_Path} object.
 * @param rect Pointer to an {@link OH_Drawing_Rect} object. NULL is recommended.
 * @param matrix Pointer to an {@link OH_Drawing_Matrix} object. NULL is recommended. The default value is an identity
 * matrix.
 * @return Returns **true** if the destination path is obtained; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PenGetFillPath(OH_Drawing_Pen* pen, const OH_Drawing_Path* src, OH_Drawing_Path* dst,
    const OH_Drawing_Rect* rect, const OH_Drawing_Matrix* matrix);

/**
 * @brief Resets a pen to the initial state.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param pen Pointer to the {@link OH_Drawing_Pen} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PenReset(OH_Drawing_Pen* pen);

#ifdef __cplusplus
}
#endif
/** @} */
#endif