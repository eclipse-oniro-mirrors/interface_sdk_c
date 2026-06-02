/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
 * @file drawing_canvas.h
 *
 * @brief This file declares the functions related to the canvas in the drawing module.
 * By default, the canvas has a black brush with anti-aliasing enabled and without any other style. This brush takes
 * effect only when no brush or pen is proactively set in the canvas.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_H
#define C_INCLUDE_DRAWING_H

#include "drawing_error_code.h"
#include "drawing_types.h"
#include "drawing_sampling_options.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the constraint types of the source rectangle.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * The source rectangle must be completely contained in the image.
     */
    STRICT_SRC_RECT_CONSTRAINT,
    /**
     * The source rectangle can be partly outside the image.
     */
    FAST_SRC_RECT_CONSTRAINT,
} OH_Drawing_SrcRectConstraint;

/**
 * @brief Creates an **OH_Drawing_Canvas** object.
 *
 * @return Returns the pointer to the **OH_Drawing_Canvas** object created.
 * @since 8
 * @version 1.0
 */
OH_Drawing_Canvas* OH_Drawing_CanvasCreate(void);

/**
 * @brief Binds a pixel map to a canvas so that the content drawn on the canvas is output to the pixel map. (This
 * process is called CPU rendering.) A canvas bound to a pixel map is a non-recording canvas.
 * You should unbind the pixel map object by calling {@link OH_Drawing_PixelMapDissolve} after the canvas object is
 * destroyed.
 *
 * @param pixelMap Pointer to the {@link OH_Drawing_PixelMap} object.
 * @return Pointer to the created canvas object {@link OH_Drawing_Canvas}. If the returned object is NULL, the creation
 * fails due to insufficient memory or an empty pixel map object.
 * @since 20
 * @version 1.0
 */
OH_Drawing_Canvas* OH_Drawing_CanvasCreateWithPixelMap(OH_Drawing_PixelMap* pixelMap);

/**
 * @brief Destroys an **OH_Drawing_Canvas** object and reclaims the memory occupied by the object.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasDestroy(OH_Drawing_Canvas* canvas);

/**
 * @brief Binds a bitmap to a canvas so that the content drawn on the canvas is output to the bitmap. (This process is
 * called CPU rendering.) A canvas bound to a bitmap is a non-recording canvas.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **bitmap** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param bitmap Pointer to an **OH_Drawing_Bitmap** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasBind(OH_Drawing_Canvas* canvas, OH_Drawing_Bitmap* bitmap);

/**
 * @brief Attaches a pen to a canvas so that the canvas can use the style and color of the pen to outline a shape. If
 * the pen effect changes after this function is called, you must call the function again to use the new effect in the
 * subsequent drawing.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **pen** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param pen Pointer to an **OH_Drawing_Pen** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasAttachPen(OH_Drawing_Canvas* canvas, const OH_Drawing_Pen* pen);

/**
 * @brief Detaches the pen from a canvas so that the canvas can no longer use the style and color of the pen to outline
 * a shape.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasDetachPen(OH_Drawing_Canvas* canvas);

/**
 * @brief Attaches a brush to a canvas so that the canvas can use the style and color of the brush to fill in a shape.
 * If the brush effect changes after this function is called, you must call the function again to use the new effect in
 * the subsequent drawing.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasAttachBrush(OH_Drawing_Canvas* canvas, const OH_Drawing_Brush* brush);

/**
 * @brief Detaches the brush from a canvas so that the canvas can no longer use the previously set brush to fill in a
 * shape.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasDetachBrush(OH_Drawing_Canvas* canvas);

/**
 * @brief Saves the current canvas status (canvas matrix) to the top of the stack. This function works with
 * {@link OH_Drawing_CanvasRestore}.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasSave(OH_Drawing_Canvas* canvas);

/**
 * @brief Saves the matrix and cropping region, and allocates a bitmap for subsequent drawing. If you call
 * {@link OH_Drawing_CanvasRestore}, changes made to the matrix and clipping region are discarded,
 * and the bitmap is drawn.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object, which is used to limit the layer size. A null pointer
 * means no limit.
 * @param brush Pointer to an {@link OH_Drawing_Brush} object. The alpha value, filter effect, and blend mode of the
 * brush are applied when the bitmap is drawn. If NULL is passed in, no effect is applied.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasSaveLayer(OH_Drawing_Canvas* canvas, const OH_Drawing_Rect* rect, const OH_Drawing_Brush* brush);

/**
 * @brief Restores the canvas status (canvas matrix) saved on the top of the stack.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasRestore(OH_Drawing_Canvas* canvas);

/**
 * @brief Obtains the number of canvas statuses (canvas matrices) saved in the stack.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @return Returns a 32-bit value that describes the number of canvas statuses (canvas matrices). The initial number is
 * **1**.
 * @since 11
 * @version 1.0
 */
uint32_t OH_Drawing_CanvasGetSaveCount(OH_Drawing_Canvas* canvas);

/**
 * @brief Restores to a given number of canvas statuses (canvas matrices).
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param saveCount Number of canvas statuses (canvas matrices). If the value is less than or equal to 1, the canvas is
 * restored to the initial state. If the value is greater than the number of canvas statuses that have been saved, no
 * operation is performed.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasRestoreToCount(OH_Drawing_Canvas* canvas, uint32_t saveCount);

/**
 * @brief Draws a line segment.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param x1 X coordinate of the start point of the line segment.
 * @param y1 Y coordinate of the start point of the line segment.
 * @param x2 X coordinate of the end point of the line segment.
 * @param y2 Y coordinate of the end point of the line segment.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasDrawLine(OH_Drawing_Canvas* canvas, float x1, float y1, float x2, float y2);

/**
 * @brief Draws a path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param path Pointer to an **OH_Drawing_Path** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasDrawPath(OH_Drawing_Canvas* canvas, const OH_Drawing_Path* path);

/**
 * @brief Draws a PixelMap based on a mesh, where mesh vertices are evenly distributed across the PixelMap. (This API
 * works with brushes but not pens.)
 *
 * @param cCanvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param pixelMap Pointer to the {@link OH_Drawing_PixelMap} object.
 * @param meshWidth Number of columns in the mesh. The value is an integer greater than 0.
 * @param meshHeight Number of rows in the mesh. The value is an integer greater than 0.
 * @param vertices Pointer to the mesh vertex array.
 * @param verticesSize Size of the mesh vertex array. The value must be ((meshWidth + 1) * (meshHeight + 1) +
 * vertoffset) * 2.
 * @param vertOffset Number of vertices to skip before drawing. The value is an integer greater than or equal to 0.
 * @param colors Pointer to the mesh color array, which can be null.
 * @param colorsSize Size of the mesh color array. If the array exists, the size must be (meshWidth + 1) * (meshHeight +
 * 1) + colorOffset.
 * @param colorOffset Number of colors to skip before drawing. The value is an integer greater than or equal to 0.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if any of the parameters, such as **cCanvas**, **pixelMap**, and **vertices*
 * *, is empty or the input parameter does not meet the value rule.
 * @since 23
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawPixelMapMesh(OH_Drawing_Canvas* cCanvas, OH_Drawing_PixelMap* pixelMap,
    uint32_t meshWidth, uint32_t meshHeight, const float* vertices, uint32_t verticesSize, uint32_t vertOffset,
    const uint32_t* colors, uint32_t colorsSize, uint32_t colorOffset);

/**
 * @brief Splits a pixel map into nine sections using two horizontal and two vertical lines: four edge sections, four
 * corner sections, and a central section.
 * If the four corner sections are smaller than the target rectangle, they will be drawn in the target rectangle
 * without scaling. Otherwise, they will be scaled to fit the target rectangle.
 * Any remaining space will be filled by stretching or compressing the other five sections to cover the entire target
 * rectangle.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param pixelMap Pointer to the {@link OH_Drawing_PixelMap} object.
 * @param center Pointer to the {@link OH_Drawing_Rect} object, which indicates the central rectangle splitting the
 * pixel map. It divides the image into nine sections by extending its four edges.
 * @param dst Pointer to the {@link OH_Drawing_Rect} object, which indicates the target region on the canvas.
 * @param mode Enumeration of filter modes.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **canvas**, **pixelMap**, or **dst** is NULL.
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawPixelMapNine(OH_Drawing_Canvas* canvas, OH_Drawing_PixelMap* pixelMap,
    const OH_Drawing_Rect* center, const OH_Drawing_Rect* dst, OH_Drawing_FilterMode mode);

/**
 * @brief Draws a portion of a pixel map onto a specified area of the canvas.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If one of **canvas**, **pixelMap**, or **dst** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param pixelMap Pointer to the {@link OH_Drawing_PixelMap} object.
 * @param src Pointer to a rectangle on the pixel map. If NULL is passed in, it refers to the entire pixel map.
 * @param dst Pointer to a rectangle on the canvas.
 * @param samplingOptions Pointer to the {@link OH_Drawing_SamplingOptions} object. A null pointer means that the
 * default sampling options are used.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawPixelMapRect(OH_Drawing_Canvas* canvas, OH_Drawing_PixelMap* pixelMap,
    const OH_Drawing_Rect* src, const OH_Drawing_Rect* dst, const OH_Drawing_SamplingOptions* samplingOptions);

/**
 * @brief Draws a portion of a pixel map onto a specified area of the canvas.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param pixelMap Pointer to the {@link OH_Drawing_PixelMap} object.
 * @param src Pointer to a rectangle on the pixel map. If NULL is passed in, it refers to the entire pixel map.
 * @param dst Pointer to a rectangle on the canvas.
 * @param samplingOptions Pointer to the {@link OH_Drawing_SamplingOptions} object. A null pointer means that the
 * default sampling options are used.
 * @param constraint Constraint type. For details about the available options, see {@link OH_Drawing_SrcRectConstraint}.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **canvas**, **pixelMap**, or **dst** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawPixelMapRectConstraint(OH_Drawing_Canvas* canvas,
    OH_Drawing_PixelMap* pixelMap, const OH_Drawing_Rect* src, const OH_Drawing_Rect* dst,
    const OH_Drawing_SamplingOptions* samplingOptions, OH_Drawing_SrcRectConstraint constraint);

/**
 * @brief Draws a background filled with a brush.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **brush** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param brush Pointer to an **OH_Drawing_Brush** object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawBackground(OH_Drawing_Canvas* canvas, const OH_Drawing_Brush* brush);

/**
 * @brief Draws a region.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **region** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param region Pointer to an **OH_Drawing_Region** object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawRegion(OH_Drawing_Canvas* canvas, const OH_Drawing_Region* region);

/**
 * @brief Enumerates the modes of drawing multiple points. The modes include discrete points, line segments, and open
 * polygons.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Draws each point separately.
     */
    POINT_MODE_POINTS,
    /**
     * Draws every two points as a line segment.
     */
    POINT_MODE_LINES,
     /**
     * Draws an array of points as an open polygon.
     */
    POINT_MODE_POLYGON,
} OH_Drawing_PointMode;

/**
 * @brief Draws a point.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param point Pointer to the {@link OH_Drawing_Point2D} object.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **canvas** or **point** is NULL.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawPoint(OH_Drawing_Canvas* canvas, const OH_Drawing_Point2D* point);

/**
 * @brief Draws multiple points. You can draw a single point, a line segment, or an open polygon.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **point2D** is NULL, or **count** is **0**, **OH_DRAWING_ERROR_INVALID_PARAMETER** is
 * returned. If **mode** is not within the enumerated range, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param mode Mode for drawing multiple points. For details, see {@link OH_Drawing_PointMode}.
 * @param count Number of vertices, that is, the number of vertices in the vertex array.
 * @param point2D Pointer to an array holding the vertices.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawPoints(OH_Drawing_Canvas* canvas, OH_Drawing_PointMode mode,
    uint32_t count, const OH_Drawing_Point2D* point2D);

/**
 * @brief Draws a bitmap. A bitmap, also referred to as a dot matrix image, a pixel map image, or a grid image,
 * includes single points called pixels (image elements).
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **bitmap** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param bitmap Pointer to an **OH_Drawing_Bitmap** object.
 * @param left X coordinate of the upper left corner of the bitmap.
 * @param top Y coordinate of the upper left corner of the bitmap.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawBitmap(OH_Drawing_Canvas* canvas, const OH_Drawing_Bitmap* bitmap, float left, float top);

/**
 * @brief Draws a portion of a bitmap onto a specified area of the canvas.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If one of **canvas**, **bitmap**, or **dst** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param bitmap Pointer to the {@link OH_Drawing_Bitmap} object.
 * @param src Pointer to a rectangle on the bitmap. If NULL is passed in, it refers to the entire bitmap.
 * @param dst Pointer to a rectangle on the canvas.
 * @param samplingOptions Pointer to the {@link OH_Drawing_SamplingOptions} object. A null pointer means that the
 * default sampling options are used.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawBitmapRect(OH_Drawing_Canvas* canvas, const OH_Drawing_Bitmap* bitmap,
    const OH_Drawing_Rect* src, const OH_Drawing_Rect* dst, const OH_Drawing_SamplingOptions* samplingOptions);

/**
 * @brief Draws a rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **OH_Drawing_Rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawRect(OH_Drawing_Canvas* canvas, const OH_Drawing_Rect* rect);

/**
 * @brief Draws a circle. This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}. If
 * either **canvas** or **point** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **radius** is less than or equal to 0, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param point Pointer to an **OH_Drawing_Point** object, which indicates the center of the circle.
 * @param radius Radius of the circle. The value is invalid if it is less than or equal to 0.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawCircle(OH_Drawing_Canvas* canvas, const OH_Drawing_Point* point, float radius);

/**
 * @brief Fills the entire canvas with the specified color and blend mode.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param color Color, represented by a 32-bit (ARGB) variable.
 * @param blendMode Blend mode.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **canvas** is NULL.
 * **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** if **blendMode** is not set to one of the enumerated values.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawColor(OH_Drawing_Canvas* canvas, uint32_t color,
    OH_Drawing_BlendMode blendMode);

/**
 * @brief Draws an oval. This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}. If
 * either **canvas** or **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawOval(OH_Drawing_Canvas* canvas, const OH_Drawing_Rect* rect);

/**
 * @brief Draws an arc. If the absolute value of the sweep angle exceeds 360 degrees, an ellipse is drawn.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @param startAngle Start angle. When the degree is 0, the start point is located at the right end of the oval. A
 * positive number indicates that the start point is placed clockwise, and a negative number indicates that the start
 * point is placed counterclockwise.
 * @param sweepAngle Angle to sweep, in degrees. A positive number indicates a clockwise sweep, and a negative value
 * indicates a counterclockwise swipe. The valid range is from -360 degrees to 360 degrees. If the absolute value of
 * the sweep angle exceeds 360 degrees, an ellipse is drawn.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawArc(OH_Drawing_Canvas* canvas,
    const OH_Drawing_Rect* rect, float startAngle, float sweepAngle);

/**
 * @brief Draws an arc. It enables you to define the start angle, sweep angle, and whether the arc's endpoints should
 * connect to its center.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @param startAngle Start angle, in degrees. The value is a floating point number. When the degree is 0, the start
 * point is located at the right end of the oval. A positive number indicates that the start point is placed clockwise,
 * and a negative number indicates that the start point is placed counterclockwise.
 * @param sweepAngle Angle to sweep, in degrees. The value is a floating point number. A positive number indicates a
 * clockwise sweep, and a negative value indicates a counterclockwise swipe. The swipe angle can exceed 360 degrees,
 * and a complete ellipse is drawn.
 * @param useCenter Whether the start point and end point of the arc are connected to its center. The value **true**
 * means that they are connected to the center; the value **false** means the opposite.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **canvas** or **rect** is NULL.
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawArcWithCenter(OH_Drawing_Canvas* canvas, const OH_Drawing_Rect* rect,
    float startAngle, float sweepAngle, bool useCenter);

/**
 * @brief Draws a rounded rectangle. This API may return an error code. For details, call
 * {@link OH_Drawing_ErrorCodeGet}. If either **canvas** or **roundRect** is NULL,
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param roundRect Pointer to an **OH_Drawing_RoundRect** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawRoundRect(OH_Drawing_Canvas* canvas, const OH_Drawing_RoundRect* roundRect);

/**
 * @brief Draws two nested rounded rectangles. The outer rectangle boundary must contain the inner rectangle boundary.
 * Otherwise, there is no drawing effect.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param outer Pointer to the {@link OH_Drawing_RoundRect} object, indicating the outer rounded rectangle.
 * @param inner Pointer to the {@link OH_Drawing_RoundRect} object, indicating the inner rounded rectangle.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **canvas**, **outer**, or **inner** is NULL.
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawNestedRoundRect(OH_Drawing_Canvas* canvas, const OH_Drawing_RoundRect* outer,
    const OH_Drawing_RoundRect* inner);

/**
 * @brief Draws a single character. If the typeface of the current font does not support the character to draw, the
 * system typeface is used to draw the character.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param str Pointer to the single character to draw. A string can be passed in, but only the first character in the
 * string is parsed and drawn in UTF-8 encoding.
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param x X coordinate of the left point of the character baseline.
 * @param y Y coordinate of the left point of the character baseline.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if at least one of the parameters **canvas**, **str**, or **font** is NULL,
 * or the length of **str** is **0**.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawSingleCharacter(OH_Drawing_Canvas* canvas, const char* str,
    const OH_Drawing_Font* font, float x, float y);

/**
 * @brief Draws a single character with font features. If the typeface of the current font does not support the
 * character to draw, the system typeface is used to draw the character.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param str Pointer to the single character to draw. A string can be passed in, but only the first character in the
 * string is parsed and drawn in UTF-8 encoding.
 * @param font Pointer to the {@link OH_Drawing_Font} object.
 * @param x X coordinate of the left point of the character baseline.
 * @param y Y coordinate of the left point of the character baseline.
 * @param fontFeatures Pointer to the {@link OH_Drawing_FontFeatures} object. If no font feature is set, the preset
 * font feature in the TrueType fonts (TTF) file is used.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if at least one of the parameters **canvas**, **str**, **font**, or **
 * fontFeatures** is NULL, or the length of **str** is **0**.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawSingleCharacterWithFeatures(OH_Drawing_Canvas* canvas, const char* str,
    const OH_Drawing_Font* font, float x, float y, OH_Drawing_FontFeatures* fontFeatures);

/**
 * @brief Draws a text blob. If the typeface used to construct **OH_Drawing_TextBlob** does not support a character,
 * that character will not be drawn.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **textBlob** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param textBlob Pointer to an **OH_Drawing_TextBlob** object.
 * @param x X coordinate of the left point of the text baseline.
 * @param y Y coordinate of the left point of the text baseline.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawTextBlob(OH_Drawing_Canvas* canvas, const OH_Drawing_TextBlob* textBlob, float x, float y);

/**
 * @brief Enumerates the canvas clipping modes.
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * Clips a specified area. That is, the difference set is obtained.
     */
    DIFFERENCE,
    /**
     * Retains a specified area. That is, the intersection is obtained.
     */
    INTERSECT,
} OH_Drawing_CanvasClipOp;

/**
 * @brief Clips a rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **clipOp** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @param clipOp Clip mode. For details about the available options, see {@link OH_Drawing_CanvasClipOp}.
 * @param doAntiAlias Whether to enable anti-aliasing. The value **true** means to enable anti-aliasing, and **false**
 * means the opposite.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasClipRect(OH_Drawing_Canvas* canvas, const OH_Drawing_Rect* rect,
    OH_Drawing_CanvasClipOp clipOp, bool doAntiAlias);

/**
 * @brief Clips a rounded rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **roundRect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **clipOp** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param roundRect Pointer to an **OH_Drawing_RoundRect** object.
 * @param clipOp Clip mode. For details about the available options, see {@link OH_Drawing_CanvasClipOp}.
 * @param doAntiAlias Whether to perform anti-aliasing. The value **true** means to perform anti-aliasing, and **false**
 * means the opposite.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasClipRoundRect(OH_Drawing_Canvas* canvas, const OH_Drawing_RoundRect* roundRect,
    OH_Drawing_CanvasClipOp clipOp, bool doAntiAlias);

/**
 * @brief Clips a path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **clipOp** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param path Pointer to an **OH_Drawing_Path** object.
 * @param clipOp Clip mode. For details about the available options, see {@link OH_Drawing_CanvasClipOp}.
 * @param doAntiAlias Whether to enable anti-aliasing. The value **true** means to enable anti-aliasing, and **false**
 * means the opposite.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasClipPath(OH_Drawing_Canvas* canvas, const OH_Drawing_Path* path,
    OH_Drawing_CanvasClipOp clipOp, bool doAntiAlias);

/**
 * @brief Clips a rectangle.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @param clipOp Clip mode. For details about the available options, see {@link OH_Drawing_CanvasClipOp}.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **canvas** or **region** is NULL.
 * **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** if **clipOp** is not set to one of the enumerated values.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasClipRegion(OH_Drawing_Canvas* canvas, const OH_Drawing_Region* region,
    OH_Drawing_CanvasClipOp clipOp);

/**
 * @brief Rotates a canvas by a given angle. A positive value indicates a clockwise rotation, and a negative value
 * indicates a counterclockwise rotation.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param degrees Rotation angle.
 * @param px X coordinate of the rotation point.
 * @param py Y coordinate of the rotation point.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasRotate(OH_Drawing_Canvas* canvas, float degrees, float px, float py);

/**
 * @brief Translates a canvas by a given distance.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param dx Distance to translate on the X axis.
 * @param dy Distance to translate on the Y axis.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasTranslate(OH_Drawing_Canvas* canvas, float dx, float dy);

/**
 * @brief Scales a canvas.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param sx Scale ratio on the X axis.
 * @param sy Scale ratio on the Y axis.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasScale(OH_Drawing_Canvas* canvas, float sx, float sy);

/**
 * @brief Skews a canvas. This function premultiplies the current canvas matrix by a skew transformation matrix and
 * applies the resulting matrix to the canvas. The skew transformation matrix is as follows:
 * |1 sx 0|
 * |sy 1 0|
 * |0  0 1|
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param sx Amount of tilt on the X axis. A positive number tilts the drawing rightwards along the positive direction
 * of the Y axis, and a negative number tilts the drawing leftwards along the positive direction of the Y axis.
 * @param sy Amount of tilt on the Y axis. A positive number tilts the drawing downwards along the positive direction
 * of the X axis, and a negative number tilts the drawing upwards along the positive direction of the X axis.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasSkew(OH_Drawing_Canvas* canvas, float sx, float sy);

/**
 * @brief Obtains the canvas width.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @return Returns the width.
 * @since 12
 * @version 1.0
 */
int32_t OH_Drawing_CanvasGetWidth(OH_Drawing_Canvas* canvas);

/**
 * @brief Obtains the canvas height.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @return Returns the height.
 * @since 12
 * @version 1.0
 */
int32_t OH_Drawing_CanvasGetHeight(OH_Drawing_Canvas* canvas);

/**
 * @brief Obtains the bounds of the cropping region of the canvas. This function cannot be used for a canvas of the
 * recording type.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object. You can call {@link OH_Drawing_RectCreate} to create a
 * rectangle object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasGetLocalClipBounds(OH_Drawing_Canvas* canvas, OH_Drawing_Rect* rect);

/**
 * @brief Obtains the 3x3 matrix of a canvas.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object. You can call {@link OH_Drawing_MatrixCreate} to
 * create a matrix object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasGetTotalMatrix(OH_Drawing_Canvas* canvas, OH_Drawing_Matrix* matrix);

/**
 * @brief Preconcats the existing matrix of the canvas with the passed-in matrix. The drawing operation triggered
 * before this API is called is not affected.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasConcatMatrix(OH_Drawing_Canvas* canvas, OH_Drawing_Matrix* matrix);

/**
 * @brief Enumerates the shadow flags.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * There is no shadow flag.
     */
    SHADOW_FLAGS_NONE,
    /**
     * The occluding object is transparent.
     */
    SHADOW_FLAGS_TRANSPARENT_OCCLUDER,
    /**
     * No analysis on the shadows is required.
     */
    SHADOW_FLAGS_GEOMETRIC_ONLY,
    /**
     * All the preceding shadow flags are used.
     */
    SHADOW_FLAGS_ALL,
} OH_Drawing_CanvasShadowFlags;

/**
 * @brief Draws a spot shadow and uses a given path to outline the ambient shadow.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **flag** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param path Pointer to the {@link OH_Drawing_Path} object, which is used to generate shadows.
 * @param planeParams Z-axis offset of an occluder relative to the canvas, based on its x and y coordinates.
 * @param devLightPos Position of the light relative to the canvas.
 * @param lightRadius Radius of the light source. The value must be greater than or equal to 0.
 * @param ambientColor Ambient shadow color, which is represented by a 32-bit (ARGB) variable.
 * @param spotColor Point shadow color, which is represented by a 32-bit (ARGB) variable.
 * @param flag Enumeration of shadow flags.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawShadow(OH_Drawing_Canvas* canvas, OH_Drawing_Path* path, OH_Drawing_Point3D planeParams,
    OH_Drawing_Point3D devLightPos, float lightRadius, uint32_t ambientColor, uint32_t spotColor,
    OH_Drawing_CanvasShadowFlags flag);

/**
 * @brief Clears a canvas by using a given color.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param color Color, which is a 32-bit (ARGB) variable.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasClear(OH_Drawing_Canvas* canvas, uint32_t color);

/**
 * @brief Sets the matrix status for a canvas.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object. You can call {@link OH_Drawing_MatrixCreate} to
 * create a matrix object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasSetMatrix(OH_Drawing_Canvas* canvas, OH_Drawing_Matrix* matrix);

/**
 * @brief Resets the matrix of this canvas to an identity matrix.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **canvas** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasResetMatrix(OH_Drawing_Canvas* canvas);

/**
 * @brief Reset the clip status.
 *
 * @param canvas Indicates the pointer to an <b>OH_Drawing_Canvas</b> object.
 * @return Returns the error code.
 *         Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 *         Returns {@link OH_DRAWING_ERROR_INVALID_PARAMETER} if canvas is nullptr.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasResetClip(OH_Drawing_Canvas* canvas);

/**
 * @brief Draws a portion of an image onto a specified area of the canvas. The area selected by the source rectangle is
 * scaled and translated to the destination rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If one of **canvas**, **image**, **src**, or **dst** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param image Pointer to the {@link OH_Drawing_Image} object.
 * @param src Pointer to the {@link OH_Drawing_Rect} object.
 * @param dst Pointer to the {@link OH_Drawing_Rect} object.
 * @param samplingOptions Pointer to the {@link OH_Drawing_SamplingOptions} object. A null pointer means that the
 * default sampling options are used.
 * @param srcRectConstraint Constraint type. For details about the available options, see
 * {@link OH_Drawing_SrcRectConstraint}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawImageRectWithSrc(OH_Drawing_Canvas* canvas, const OH_Drawing_Image* image,
    const OH_Drawing_Rect* src, const OH_Drawing_Rect* dst, const OH_Drawing_SamplingOptions* samplingOptions,
    OH_Drawing_SrcRectConstraint srcRectConstraint);

/**
 * @brief Draws an image onto a specified area of the canvas.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If one of **canvas**, **image**, or **dst** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param image Pointer to the {@link OH_Drawing_Image} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @param samplingOptions Pointer to the {@link OH_Drawing_SamplingOptions} object. A null pointer means that the
 * default sampling options are used.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawImageRect(OH_Drawing_Canvas* canvas, OH_Drawing_Image* image,
    OH_Drawing_Rect* rect, OH_Drawing_SamplingOptions* samplingOptions);

/**
 * @brief Enumerates the modes of interpreting the geometry of a given vertex.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Draws a triangle list. Specifically, a list of isolated triangles are drawn using every three vertices. If the
     * number of vertices is not a multiple of 3, the extra vertices will be ignored.
     */
    VERTEX_MODE_TRIANGLES,
    /**
     * Draws a triangle strip. Specifically, the first triangle is drawn between the first 3 vertices, and all
     * subsequent triangles use the previous 2 vertices plus the next additional vertex.
     */
    VERTEX_MODE_TRIANGLES_STRIP,
    /**
     * Draws a triangle fan. A triangle fan is similar to a triangle strip, except that all the triangles share one
     * vertex (the first vertex).
     */
    VERTEX_MODE_TRIANGLE_FAN,
} OH_Drawing_VertexMode;

/**
 * @brief Draws a triangular grid described by a vertex array.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **positions** is NULL, **vertexCount** is less than 3, or **indexCount** is less than 3 but
 * not 0, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If either **vertexMmode** or **mode** is not set to one of the enumerated values, **
 * OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param canvas Pointer to an **OH_Drawing_Canvas** object.
 * @param vertexMmode Mode for drawing vertices. For details about the available options, see
 * {@link OH_Drawing_VertexMode}.
 * @param vertexCount Number of elements in the vertex array. The value must be greater than or equal to 3.
 * @param positions Pointer to the array that holds the position of every vertex. The array cannot be null and its
 * length must be equal to the value of **vertexCount**.
 * @param texs Pointer to the array that holds the texture space coordinate corresponding to each vertex. The array can
 * be null. If the array is not null, its length must be equal to the value of **vertexCount**.
 * @param colors Pointer to the array that holds the color corresponding to each vertex. It is used for interpolation
 * in a triangle. The array can be null. If the array is not null, its length must be equal to the value of **
 * vertexCount**.
 * @param indexCount Number of indices. The value can be 0 or a value greater than or equal to 3.
 * @param indices Pointer to the array that holds the index of each vertex. The array can be null. If the array is not
 * null, its length must be equal to the value of **indexCount**.
 * @param mode Enumeration of blend modes. For details about the available options, see {@link OH_Drawing_BlendMode}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawVertices(OH_Drawing_Canvas* canvas, OH_Drawing_VertexMode vertexMmode,
    int32_t vertexCount, const OH_Drawing_Point2D* positions, const OH_Drawing_Point2D* texs,
    const uint32_t* colors, int32_t indexCount, const uint16_t* indices, OH_Drawing_BlendMode mode);

/**
 * @brief Copies pixel data from a canvas to a specified address. This function cannot be used for a canvas of the
 * recording type.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If one of **canvas**, **imageInfo**, or **dstPixels** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param imageInfo Pointer to the {@link OH_Drawing_Image_Info} object.
 * @param dstPixels Pointer to the start address for storing the pixel data.
 * @param dstRowBytes Number of bytes in each row of pixels. The value is invalid if it is less than or equal to 0.
 * @param srcX X offset of the pixels on the canvas, in px.
 * @param srcY Y offset of the pixels on the canvas, in px.
 * @return Returns **true** if the pixel data is copied to the start address of the storage; returns **false**
 * otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_CanvasReadPixels(OH_Drawing_Canvas* canvas, OH_Drawing_Image_Info* imageInfo,
    void* dstPixels, uint32_t dstRowBytes, int32_t srcX, int32_t srcY);

/**
 * @brief Copies pixel data from a canvas to an image. This function cannot be used for a canvas of the recording type.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **canvas** or **bitmap** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param bitmap Pointer to the {@link OH_Drawing_Bitmap} object.
 * @param srcX X offset of the pixels on the canvas, in px.
 * @param srcY Y offset of the pixels on the canvas, in px.
 * @return Returns **true** if the pixel data is copied to the image; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_CanvasReadPixelsToBitmap(OH_Drawing_Canvas* canvas,
    OH_Drawing_Bitmap* bitmap, int32_t srcX, int32_t srcY);

/**
 * @brief Checks whether the region that can be drawn is empty after clipping.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param isClipEmpty Pointer to the variable that specifies whether the region is empty. The value **true** means that
 * the region is empty, and **false** means the opposite.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **canvas** or **isClipEmpty** is NULL.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasIsClipEmpty(OH_Drawing_Canvas* canvas, bool* isClipEmpty);

/**
 * @brief Obtains the image information of a canvas.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param imageInfo Pointer to the {@link OH_Drawing_Image_Info} object.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **canvas** or **imageInfo** is NULL.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasGetImageInfo(OH_Drawing_Canvas* canvas, OH_Drawing_Image_Info* imageInfo);

/**
 * @brief Draws an **OH_Drawing_RecordCmd** object.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object. Only the canvas of the recording type is supported.
 * @param recordCmd Pointer to the {@link OH_Drawing_RecordCmd} object.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **canvas** or **recordCmd** is NULL.
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawRecordCmd(OH_Drawing_Canvas* canvas, OH_Drawing_RecordCmd* recordCmd);

/**
 * @brief Draws an **OH_Drawing_RecordCmd** object. This API supports nesting.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object. Only the canvas of the recording type is supported.
 * @param recordCmd Pointer to the {@link OH_Drawing_RecordCmd} object.
 * @return Operation code.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **canvas** or **recordCmd** is NULL.
 * @since 19
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawRecordCmdNesting(OH_Drawing_Canvas* canvas, OH_Drawing_RecordCmd* recordCmd);

/**
 * @brief Checks whether the path is not intersecting with the canvas area. The canvas area includes its boundaries.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param quickReject Pointer to the check result. The value **true** means that the path is not intersecting with the
 * canvas area, and **false** means the opposite.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **canvas**, **path**, or **quickReject** is NULL.
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasQuickRejectPath(OH_Drawing_Canvas* canvas, const OH_Drawing_Path* path,
    bool* quickReject);

/**
 * @brief Checks whether the rectangle is not intersecting with the canvas area. The canvas area includes its
 * boundaries.
 *
 * @param canvas Pointer to the {@link OH_Drawing_Canvas} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @param quickReject Pointer to the check result. The value **true** means that the rectangle is not intersecting with
 * the canvas area, and **false** means the opposite.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **canvas**, **rect**, or **quickReject** is NULL.
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasQuickRejectRect(OH_Drawing_Canvas* canvas, const OH_Drawing_Rect* rect,
    bool* quickReject);

/**
 * @brief Checks if the current layer that drawn into the device is opaque.
 *
 * @param canvas Indicates the pointer to an <b>OH_Drawing_Canvas</b> object.
 * @param isOpaque Indicates if the canvas is opaque.
 * @return Returns the error code.
 *         Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 *         Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if canvas or isOpaque is nullptr.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasIsOpaque(const OH_Drawing_Canvas* canvas, bool* isOpaque);

#ifdef __cplusplus
}
#endif
/** @} */
#endif