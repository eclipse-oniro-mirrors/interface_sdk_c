/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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
 * @file drawing_path.h
 *
 * @brief This file declares the functions related to the path in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_PATH_H
#define C_INCLUDE_DRAWING_PATH_H

#include "drawing_error_code.h"
#include "drawing_types.h"
#include "drawing_path_iterator.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the directions of a closed contour.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Adds a closed contour clockwise.
     */
    PATH_DIRECTION_CW,
    /**
     * Adds a closed contour counterclockwise.
     */
    PATH_DIRECTION_CCW,
} OH_Drawing_PathDirection;

/**
 * @brief Enumerates the fill types of a path.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * For any point within the drawing area, a ray is cast in an arbitrary direction. The count starts at 0 for all
     * intersections between this ray and the path.<br>Each clockwise intersection—where the path crosses the ray from
     * left to right—results in the count being incremented by 1, while each counterclockwise intersection—where the
     * path crosses the ray from right to left—causes the count to be decremented by 1. A point is deemed inside the
     * path and needs to be colored if the final count is non-zero; if the count is 0, the point remains uncolored.
     */
    PATH_FILL_TYPE_WINDING,
    /**
     * For any point in the drawing area, a ray is cast in an arbitrary direction. If the number of intersections
     * between this ray and the path is odd, the point is deemed inside the path and needs to be colored; if the number
     * is even, it remains uncolored.
     */
    PATH_FILL_TYPE_EVEN_ODD,
    /**
     * Same as **PATH_FILL_TYPE_WINDING**, but draws outside of the path, rather than inside.
     */
    PATH_FILL_TYPE_INVERSE_WINDING,
    /**
     * Same as **PATH_FILL_TYPE_EVEN_ODD**, but draws outside of the path, rather than inside.
     */
    PATH_FILL_TYPE_INVERSE_EVEN_ODD,
} OH_Drawing_PathFillType;

/**
 * @brief Enumerates the path adding modes.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Adds a path in append mode.
     */
    PATH_ADD_MODE_APPEND,
    /**
     * Adds a line segment to close the path if the previous path is not closed.
     */
    PATH_ADD_MODE_EXTEND,
} OH_Drawing_PathAddMode;

/**
 * @brief Enumerates the operation modes available for a path.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Difference operation.
     */
    PATH_OP_MODE_DIFFERENCE,
    /**
     * Intersection operation.
     */
    PATH_OP_MODE_INTERSECT,
    /**
     * Union operation.
     */
    PATH_OP_MODE_UNION,
    /**
     * XOR operation.
     */
    PATH_OP_MODE_XOR,
    /**
     * Reverse difference operation.
     */
    PATH_OP_MODE_REVERSE_DIFFERENCE,
} OH_Drawing_PathOpMode;

/**
 * @brief Enumerates the types of matrix information obtained during path measurement.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Matrix corresponding to the position information.
     */
    GET_POSITION_MATRIX,
    /**
     * Matrix corresponding to the tangent information.
     */
    GET_TANGENT_MATRIX,
    /**
     * Matrix corresponding to the position and tangent information.
     */
    GET_POSITION_AND_TANGENT_MATRIX,
} OH_Drawing_PathMeasureMatrixFlags;

/**
 * @brief Creates an **OH_Drawing_Path** object.
 *
 * @return Returns the pointer to the **OH_Drawing_Path** object created.
 * @since 8
 * @version 1.0
 */
OH_Drawing_Path* OH_Drawing_PathCreate(void);

/**
 * @brief Creates a copy of the {@link OH_Drawing_Path} object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @return Pointer to the copy of the {@link OH_Drawing_Path} object.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Path* OH_Drawing_PathCopy(OH_Drawing_Path* path);

/**
 * @brief Destroys an **OH_Drawing_Path** object and reclaims the memory occupied by the object.
 *
 * @param path Pointer to an **OH_Drawing_Path** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathDestroy(OH_Drawing_Path* path);

/**
 * @brief Sets a path object as the current path object.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param other Pointer to the {@link OH_Drawing_Path} object to be set.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **path** or **other** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathSetPath(OH_Drawing_Path* path, OH_Drawing_Path* other);

/**
 * @brief Checks whether a path object is empty.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param isEmpty Whether the path object is empty. **true** means empty; **false** otherwise. It as an output
 * parameter.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **path** or **isEmpty** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathIsEmpty(OH_Drawing_Path* path, bool* isEmpty);

/**
 * @brief Checks whether a path object forms a rectangle.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object, which is used as an output parameter and can be null.
 * @param isRect Whether a path forms a rectangle. **true** means yes; **false** otherwise. It as an output parameter.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **path** or **isRect** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathIsRect(OH_Drawing_Path* path, OH_Drawing_Rect* rect, bool* isRect);

/**
 * @brief Sets the start point of this path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to an **OH_Drawing_Path** object.
 * @param x X coordinate of the start point.
 * @param y Y coordinate of the start point.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathMoveTo(OH_Drawing_Path* path, float x, float y);

/**
 * @brief Draws a line segment from the last point of this path to the target point. If the path is empty, the start
 * point (0, 0) is used.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to an **OH_Drawing_Path** object.
 * @param x X coordinate of the target point.
 * @param y Y coordinate of the target point.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathLineTo(OH_Drawing_Path* path, float x, float y);

/**
 * @brief Draws an arc to a path. This is done by using angle arc mode. In this mode, a rectangle is specified first,
 * and then a start angle and scanning degree are specified. The inscribed ellipse of the rectangle will be used to
 * intercept the arc.
 * The arc is a portion of the ellipse defined by the start angle and the sweep angle. If the path is empty, a line
 * segment from the last point of the path to the start point of the arc is also added.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to an **OH_Drawing_Path** object.
 * @param x1 X coordinate of the upper left corner of the rectangle.
 * @param y1 Y coordinate of the upper left corner of the rectangle.
 * @param x2 X coordinate of the lower right corner of the rectangle.
 * @param y2 Y coordinate of the lower right corner of the rectangle.
 * @param startDeg Start angle. The start direction (0°) of the angle is the positive direction of the X axis.
 * @param sweepDeg Angle to sweep, in degrees. A positive number indicates a clockwise sweep, and a negative value
 * indicates a counterclockwise swipe. The actual swipe degree is the modulo operation result of the input parameter by
 * 360.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathArcTo(OH_Drawing_Path* path,
    float x1, float y1, float x2, float y2, float startDeg, float sweepDeg);

/**
 * @brief Draws a quadratic Bezier curve from the last point of a path to the target point. If the path is empty, the
 * start point (0, 0) is used.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to an **OH_Drawing_Path** object.
 * @param ctrlX X coordinate of the control point.
 * @param ctrlY Y coordinate of the control point.
 * @param endX X coordinate of the target point.
 * @param endY Y coordinate of the target point.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathQuadTo(OH_Drawing_Path* path, float ctrlX, float ctrlY, float endX, float endY);

/**
 * @brief Draws a conic curve from the last point of a path to the target point. If the path is empty, the start point (
 * 0, 0) is used.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param ctrlX X coordinate of the control point.
 * @param ctrlY Y coordinate of the control point.
 * @param endX X coordinate of the target point.
 * @param endY Y coordinate of the target point.
 * @param weight Weight of the curve, which determines its shape. The larger the value, the closer of the curve to the
 * control point.
 * If the value is less than or equal to **0**, the result is equivalent to a line segment from the start point to the
 * end point, which is added by calling {@link OH_Drawing_PathLineTo}.
 * If the value is **1**, the result is equivalent to {@link OH_Drawing_PathQuadTo}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathConicTo(OH_Drawing_Path* path, float ctrlX, float ctrlY, float endX, float endY, float weight);

/**
 * @brief Draws a cubic Bezier curve from the last point of this path to the target point. If the path is empty, the
 * start point (0, 0) is used.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to an **OH_Drawing_Path** object.
 * @param ctrlX1 X coordinate of the first control point.
 * @param ctrlY1 Y coordinate of the first control point.
 * @param ctrlX2 X coordinate of the second control point.
 * @param ctrlY2 Y coordinate of the second control point.
 * @param endX X coordinate of the target point.
 * @param endY Y coordinate of the target point.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathCubicTo(
    OH_Drawing_Path* path, float ctrlX1, float ctrlY1, float ctrlX2, float ctrlY2, float endX, float endY);

/**
 * @brief Sets the start position relative to the last point of a path. If the path is empty, the start point (0, 0) is
 * used.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param x X-axis offset relative to the end point of a path. A positive number indicates an offset in the positive
 * direction of the X axis, and a negative number indicates an offset in the negative direction of the X axis.
 * @param y Y-axis offset relative to the end point of a path. A positive number indicates an offset in the positive
 * direction of the Y axis, and a negative number indicates an offset in the negative direction of the Y axis.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathRMoveTo(OH_Drawing_Path* path, float x, float y);

/**
 * @brief Draws a line segment from the last point of this path to a point relative to the last point. If the path is
 * empty, the start point (0, 0) is used.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param x X offset relative to the last point, which is used to specify the X coordinate of the target point.
 * @param y Y offset relative to the last point, which is used to specify the X coordinate of the target point.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathRLineTo(OH_Drawing_Path* path, float x, float y);

/**
 * @brief Draws a quadratic Bezier curve from the last point of this path to a point relative to the last point. If the
 * path is empty, the start point (0, 0) is used.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param ctrlX X offset relative to the last point, which is used to specify the X coordinate of the control point.
 * @param ctrlY Y offset relative to the last point, which is used to specify the Y coordinate of the control point.
 * @param endX X offset relative to the last point, which is used to specify the X coordinate of the target point.
 * @param endY Y offset relative to the last point, which is used to specify the Y coordinate of the target point.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathRQuadTo(OH_Drawing_Path* path, float ctrlX, float ctrlY, float endX, float endY);

/**
 * @brief Draws a conic curve from the last point of a path to a point relative to the last point. If the path is empty,
 * the start point (0, 0) is used.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param ctrlX X offset relative to the last point, which is used to specify the X coordinate of the control point.
 * @param ctrlY Y offset relative to the last point, which is used to specify the Y coordinate of the control point.
 * @param endX X offset relative to the last point, which is used to specify the X coordinate of the target point.
 * @param endY Y offset relative to the last point, which is used to specify the Y coordinate of the target point.
 * @param weight Weight of the curve, which determines its shape. The larger the value, the closer of the curve to the
 * control point.
 * If the value is less than or equal to **0**, the result is equivalent to a line segment from the start point to the
 * end point, which is added by calling {@link OH_Drawing_PathRLineTo}.
 * If the value is **1**, the result is equivalent to {@link OH_Drawing_PathRQuadTo}.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathRConicTo(OH_Drawing_Path* path, float ctrlX, float ctrlY, float endX, float endY, float weight);

/**
 * @brief Draws a cubic Bezier curve from the last point of a path to a point relative to the last point. If the path
 * is empty, the start point (0, 0) is used.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param ctrlX1 X offset relative to the last point, which is used to specify the X coordinate of the first control
 * point.
 * @param ctrlY1 Y offset relative to the last point, which is used to specify the Y coordinate of the first control
 * point.
 * @param ctrlX2 X offset relative to the last point, which is used to specify the X coordinate of the second control
 * point.
 * @param ctrlY2 Y offset relative to the last point, which is used to specify the Y coordinate of the second control
 * point.
 * @param endX X offset relative to the last point, which is used to specify the X coordinate of the target point.
 * @param endY Y offset relative to the last point, which is used to specify the Y coordinate of the target point.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathRCubicTo(OH_Drawing_Path* path, float ctrlX1, float ctrlY1, float ctrlX2, float ctrlY2,
    float endX, float endY);

/**
 * @brief Adds a rectangle to a path in the specified direction. The start point is the upper left corner of the
 * rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **pathDirection** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param left X coordinate of the upper left corner of the rectangle.
 * @param top Y coordinate of the upper left corner of the rectangle.
 * @param right X coordinate of the lower right corner of the rectangle.
 * @param bottom Y coordinate of the lower right corner of the rectangle.
 * @param pathDirection {@link OH_Drawing_PathDirection} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddRect(OH_Drawing_Path* path, float left, float top, float right, float bottom,
    OH_Drawing_PathDirection pathDirection);

/**
 * @brief Adds a rectangle contour to a path in the specified direction.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **pathDirection** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @param pathDirection Indicates the path direction.
 * @param start Start point, indicating the corner of the rectangle from which the path is drawn. The value **0** means
 * the upper left corner, **1** means the upper right corner, **2** means the lower right corner, and **3** means the
 * lower left corner.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddRectWithInitialCorner(OH_Drawing_Path* path, const OH_Drawing_Rect* rect,
    OH_Drawing_PathDirection pathDirection, uint32_t start);

/**
 * @brief Adds a rounded rectangle to a path in the specified direction. When the path direction is clockwise, the
 * start point is at the intersection of the rounded rectangle's left boundary and its lower left corner. When the path
 * direction is counterclockwise, the start point is at the intersection point between the left boundary and the upper
 * left corner.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **roundRect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **pathDirection** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param roundRect Pointer to the {@link OH_Drawing_RoundRect} object.
 * @param pathDirection {@link OH_Drawing_PathDirection} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddRoundRect(OH_Drawing_Path* path,
    const OH_Drawing_RoundRect* roundRect, OH_Drawing_PathDirection pathDirection);

/**
 * @brief Adds an oval to a path. **OH_Drawing_Rect** specifies the outer tangent rectangle of the oval, and **
 * OH_Drawing_PathDirection** specifies whether the drawing is clockwise or counterclockwise.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **pathDirection** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @param start Start point of the oval.
 * @param pathDirection {@link OH_Drawing_PathDirection} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddOvalWithInitialPoint(OH_Drawing_Path* path, const OH_Drawing_Rect* rect,
    uint32_t start, OH_Drawing_PathDirection pathDirection);

/**
 * @brief Adds an oval to a path in the specified direction.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **pathDirection** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @param pathDirection {@link OH_Drawing_PathDirection} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddOval(OH_Drawing_Path* path,
    const OH_Drawing_Rect* rect, OH_Drawing_PathDirection pathDirection);

/**
 * @brief Adds an arc to a path as the start of a new contour. The arc added is part of the inscribed ellipse of the
 * rectangle, from the start angle through the sweep angle. If the sweep angle is less than or equal to -360°, or if
 * the sweep angle is greater than or equal to 360°, and start angle modulo 90 is nearly zero, an oval instead of an
 * ellipse is added.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @param startAngle Start angle of the arc, in degrees.
 * @param sweepAngle Angle to sweep, in degrees. A positive number indicates a clockwise sweep, and a negative value
 * indicates a counterclockwise swipe. The actual swipe degree is the modulo operation result of the input parameter by
 * 360.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddArc(OH_Drawing_Path* path, const OH_Drawing_Rect* rect, float startAngle, float sweepAngle);

/**
 * @brief Transforms the points in a **src** path by a matrix and adds the new one to the current path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **src** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the existing {@link OH_Drawing_Path} object.
 * @param src Pointer to the source {@link OH_Drawing_Path} object.
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object. A null pointer means an identity matrix.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddPath(OH_Drawing_Path* path, const OH_Drawing_Path* src, const OH_Drawing_Matrix* matrix);

/**
 * @brief Transforms the points in a **src** path by a matrix and adds the new one to the current path with the
 * specified adding mode.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **src** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **pathAddMode** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param path Pointer to the existing {@link OH_Drawing_Path} object.
 * @param src Pointer to the source {@link OH_Drawing_Path} object.
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object. A null pointer means an identity matrix.
 * @param pathAddMode {@link OH_Drawing_PathAddMode} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddPathWithMatrixAndMode(OH_Drawing_Path* path, const OH_Drawing_Path* src,
    const OH_Drawing_Matrix* matrix, OH_Drawing_PathAddMode pathAddMode);

/**
 * @brief Adds a **src** path to the current path with the specified adding mode.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **src** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **pathAddMode** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param path Pointer to the existing {@link OH_Drawing_Path} object.
 * @param src Pointer to the source {@link OH_Drawing_Path} object.
 * @param pathAddMode {@link OH_Drawing_PathAddMode} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddPathWithMode(OH_Drawing_Path* path,
    const OH_Drawing_Path* src, OH_Drawing_PathAddMode pathAddMode);

/**
 * @brief Translates a **src** path by an offset and adds the new one to the current path with the specified adding
 * mode.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **src** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **pathAddMode** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param path Pointer to the existing {@link OH_Drawing_Path} object.
 * @param src Pointer to the source {@link OH_Drawing_Path} object.
 * @param dx X offset.
 * @param dy Y offset.
 * @param pathAddMode {@link OH_Drawing_PathAddMode} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddPathWithOffsetAndMode(OH_Drawing_Path* path, const OH_Drawing_Path* src, float dx, float dy,
    OH_Drawing_PathAddMode pathAddMode);

/**
 * @brief Adds a polygon to a path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **points** is NULL or **count** is **0**, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the existing {@link OH_Drawing_Path} object.
 * @param points Pointer to an array that holds the vertex coordinates of the polygon.
 * @param count Size of the array.
 * @param isClosed Whether the path is closed. The value **true** means that the path is closed, and **false** means
 * the opposite.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddPolygon(OH_Drawing_Path* path, const OH_Drawing_Point2D* points, uint32_t count, bool isClosed);

/**
 * @brief Adds a circle to a path in the specified direction.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **radius** is less than or equal to 0, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 * If **pathDirection** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param x X coordinate of the circle center.
 * @param y Y coordinate of the circle center.
 * @param radius Radius of the circle.
 * @param pathDirection {@link OH_Drawing_PathDirection} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddCircle(OH_Drawing_Path* path,
    float x, float y, float radius, OH_Drawing_PathDirection pathDirection);

/**
 * @brief Parses the path represented by an SVG string.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **str** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param str Pointer to the SVG string.
 * @return Returns whether the SVG string is successfully parsed. **true** means successful; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PathBuildFromSvgString(OH_Drawing_Path* path, const char* str);

/**
 * @brief Convert path to an SVG string.
 *
 * @param path Indicates the pointer to an <b>OH_Drawing_Path</b> object.
 * @param str Indicates the SVG string. API users are responsible for allocating and freeing memory.
 * @param strSize Indicates the SVG string memory size in bytes.
 * @return Returns the error code.
 *         Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 *         Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if path or strSize is nullptr.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathConvertToSvgString(const OH_Drawing_Path* path, char* str, size_t* strSize);

/**
 * @brief Get path point data.
 *
 * @param path Indicates the pointer to an <b>OH_Drawing_Path</b> object.
 * @param points Indicates the path point array.
 * @param count Indicates the size of point array.
 * @return Returns the error code.
 *         Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 *         Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if path or count is nullptr.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathGetPointData(
    const OH_Drawing_Path* path, OH_Drawing_Point2D* points, uint32_t* count);

/**
 * @brief Get path verb data.
 *
 * @param path Indicates the pointer to an <b>OH_Drawing_Path</b> object.
 * @param verbs Indicates the path verb array.
 * @param count Indicates the size of verb array.
 * @return Returns the error code.
 *         Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 *         Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if path or count is nullptr.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathGetVerbData(const OH_Drawing_Path* path, OH_Drawing_PathIteratorVerb* verbs,
    uint32_t* count);

/**
 * @brief Get path conic weight data.
 *
 * @param path Indicates the pointer to an <b>OH_Drawing_Path</b> object.
 * @param conicWeights Indicates the path conic weight array.
 * @param count Indicates the size of conic weight array.
 * @return Returns the error code.
 *         Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 *         Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if path or count is nullptr.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathGetConicWeightData(
    const OH_Drawing_Path* path, float* conicWeights, uint32_t* count);

/**
 * @brief Checks whether a coordinate point is included in this path. For details, see {@link OH_Drawing_PathFillType}.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param x Coordinate point on the X axis.
 * @param y Coordinate point on the Y axis.
 * @return Returns **true** if the coordinate point is included in the path; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PathContains(OH_Drawing_Path* path, float x, float y);

/**
 * @brief Transforms the points in a path by matrix.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathTransform(OH_Drawing_Path* path, const OH_Drawing_Matrix* matrix);

/**
 * @brief Transforms the points in a path by matrix, and uses the new one to replace the **dst** path. If **dst** is
 * NULL, the **src** path is replaced.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **src** or **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param src Pointer to the {@link OH_Drawing_Path} object.
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param dst Pointer to the target {@link OH_Drawing_Path} object.
 * @param applyPerspectiveClip Whether to apply perspective cropping to the new path. The value **true** means to apply
 * perspective cropping, and **false** means the opposite.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathTransformWithPerspectiveClip(OH_Drawing_Path* src, const OH_Drawing_Matrix* matrix,
    OH_Drawing_Path* dst, bool applyPerspectiveClip);

/**
 * @brief Sets the fill type of a path. The fill type determines how "inside" of the path is drawn.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **pathFillType** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is
 * returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param pathFillType {@link OH_Drawing_PathFillType} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathSetFillType(OH_Drawing_Path* path, OH_Drawing_PathFillType pathFillType);

/**
 * @brief Obtains the fill type of a path.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param pathFillType Pointer to the {@link OH_Drawing_PathFillType} object.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **path** or **pathFillType** is NULL.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathGetFillType(OH_Drawing_Path* path, OH_Drawing_PathFillType* pathFillType);

/**
 * @brief Obtains the length of a path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param forceClosed Whether the path is measured as a closed path. **true** means that the path is forcibly
 * considered as a closed path; **false** means that the path is measured depending on whether it is a closed path.
 * @return Returns the length of the path.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_PathGetLength(OH_Drawing_Path* path, bool forceClosed);

/**
 * @brief Obtains the minimum bounds that enclose a path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathGetBounds(OH_Drawing_Path* path, OH_Drawing_Rect* rect);

/**
 * @brief Draws a line segment from the current point to the start point of this path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathClose(OH_Drawing_Path* path);

/**
 * @brief Translates a path by an offset along the X axis and Y axis and adds the new one to the **dst** path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the existing {@link OH_Drawing_Path} object.
 * @param dst Pointer to a destination path, which is an {@link OH_Drawing_Path} object. If NULL is passed in, the
 * result is stored in the current path.
 * @param dx X offset.
 * @param dy Y offset.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathOffset(OH_Drawing_Path* path, OH_Drawing_Path* dst, float dx, float dy);

/**
 * @brief Resets the path data.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to an **OH_Drawing_Path** object.
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathReset(OH_Drawing_Path* path);

/**
 * @brief Checks whether a path is closed.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **path** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param forceClosed Whether the path is measured as a closed path. The value **true** means that the path is
 * considered closed during measurement, and **false** means that the path is measured based on the actual closed
 * status.
 * @return Returns **true** if the path is closed; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PathIsClosed(OH_Drawing_Path* path, bool forceClosed);

/**
 * @brief Obtains the coordinates and tangent at a distance from the start point of this path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **path**, **position**, or **tangent** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param forceClosed Whether the path is measured as a closed path. The value **true** means that the path is
 * considered closed during measurement, and **false** means that the path is measured based on the actual closed
 * status.
 * @param distance Distance from the start point. If the distance is less than 0, it is considered as 0. If the
 * distance is greater than the path length, it is considered as the path length.
 * @param position Pointer to the coordinates.
 * @param tangent Pointer to the tangent, where **tangent.x** and **tangent.y** represent the cosine and sine of the
 * tangent of the point, respectively.
 * @return Returns whether the measurement is successful. **true** means successful; **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PathGetPositionTangent(OH_Drawing_Path* path, bool forceClosed,
    float distance, OH_Drawing_Point2D* position, OH_Drawing_Point2D* tangent);

/**
 * @brief Extracts a segment of a path and appends it to a destination path.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param forceClosed Whether the path is measured as a closed path. The value **true** means that the path is
 * considered closed during measurement, and **false** means that the path is measured based on the actual closed
 * status.
 * @param start Distance from the start point of the path to the start point of the segment. If it is less than 0, it
 * defaults to 0. If it is greater than or equal to **stop**, the extraction fails.
 * @param stop Distance from the start point of the path to the end point of the segment. If it is less than or equal
 * to **start**, the extraction fails. If it is greater than the path length, it defaults to the path length.
 * @param startWithMoveTo Whether to execute {@link OH_Drawing_PathMoveTo} in the destination path to move to its start
 * point. The value **true** means to move to the start point, and **false** means the opposite.
 * @param dst Pointer to a destination path, which is an {@link OH_Drawing_Path} object. If the extraction succeeds,
 * the segment is appended to the path. If the extraction fails, nothing changes.
 * @param result Pointer to the extraction result. The value **true** means that the extraction is successful, and **
 * false** means the opposite. It as an output parameter.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if at least one of the **path**, **dst**, and **result** parameters is a null
 * pointer.
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathGetSegment(OH_Drawing_Path* path, bool forceClosed,
    float start, float stop, bool startWithMoveTo, OH_Drawing_Path* dst, bool* result);

/**
 * @brief Combines two paths based on the specified operation mode.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **srcPath** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **op** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param path Pointer to an {@link OH_Drawing_Path} object, in which the resulting path is saved.
 * @param other Pointer to the {@link OH_Drawing_Path} object.
 * @param op Operation mode of the path. For details about the available options, see {@link OH_Drawing_PathOpMode}.
 * @return Returns **true** if the resulting path is not empty; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PathOp(OH_Drawing_Path* path, const OH_Drawing_Path* other, OH_Drawing_PathOpMode op);

/**
 * @brief Obtains a transformation matrix at a distance from the start point of this path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **path** or **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **flag** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param forceClosed Whether the path is measured as a closed path. The value **true** means that the path is
 * considered closed during measurement, and **false** means that the path is measured based on the actual closed
 * status.
 * @param distance Distance from the start point. If the distance is less than 0, it is considered as 0. If the
 * distance is greater than the path length, it is considered as the path length.
 * @param matrix Pointer to the transformation matrix.
 * @param flag Type of the matrix information. For details about the available options, see
 * {@link OH_Drawing_PathMeasureMatrixFlags}
 * .
 * @return Returns **true** if the transformation matrix is obtained successfully; returns **false** otherwise. The
 * possible failure cause is that **path** is NULL or the path length is 0.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PathGetMatrix(OH_Drawing_Path* path, bool forceClosed,
    float distance, OH_Drawing_Matrix* matrix, OH_Drawing_PathMeasureMatrixFlags flag);

/**
 * @brief Converts the existing path into an approximate path consisting of consecutive line segments.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param acceptableError Acceptable error of each line segment on the path. The value cannot be less than 0.
 * 1. Avoid setting **acceptableError** to **0** as it heavily divides the curve path, significantly impacting
 * performance and memory usage.
 * 2. Setting a high **acceptableError** simplifies the path greatly by keeping only essential points, potentially
 * distorting the original shape.
 * 3. When you set a high **acceptableError** for curves such as ellipses, the fitting process often simplifies them to
 * polygons by keeping just the start and end points of their Bezier curve segments.
 * @param vals An array of approximate points of the path.
 * Each point consists of three values, indicating:
 * 1. Length ratio of the point to the start point of the path.
 * 2. X coordinate of the point.
 * 3. Y coordinate of the point.
 * @param count Size of the returned array, which is at least 6. The size of the point array after fitting is returned
 * if **vals** is a null pointer.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **path** or **count** is a null pointer.
 * **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** if **acceptableError** is less than 0.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathApproximate(OH_Drawing_Path* path, float acceptableError, float* vals,
    uint32_t* count);

/**
 * @brief Interpolates between the existing path and another path based on the given weight and stores the result in
 * the target path object.
 * Interpolation is achievable if the two paths have the same number of points. The target path is created based on the
 * structure of the existing path.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param other Pointer to the {@link OH_Drawing_Path} object of the other path used for interpolation.
 * @param weight Interpolation weight. The value range is [0, 1].
 * @param success Whether the interpolation is successful. **true** means yes; **false** otherwise. It as an output
 * parameter.
 * @param interpolatedPath Pointer to the {@link OH_Drawing_Path} object used to store the interpolation result.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **path**, **other**, **success**, or **interpolatedPath** is a null
 * pointer.
 * **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** if **weight** is not in the range of [0, 1].
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathInterpolate(OH_Drawing_Path* path, OH_Drawing_Path* other,
    float weight, bool* success, OH_Drawing_Path* interpolatedPath);

/**
 * @brief Checks whether the existing path and another path (**other**) are compatible for interpolation in terms of
 * structure and operation sequence.
 * If the paths contain conic operations, the weight values of the operations must be the same.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param other Pointer to the {@link OH_Drawing_Path} object.
 * @param result Checks whether a path is compatible with another path. It is used as an output parameter.
 * **true** if the paths are compatible, **false** otherwise.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **path**, **other**, or **result** is a null pointer.
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathIsInterpolate(OH_Drawing_Path* path, OH_Drawing_Path* other, bool* result);

/**
 * @brief Gets the last point of the path.
 *
 * @param path Indicates the pointer to an <b>OH_Drawing_Path</b> object.
 * @param point Indicates the pointer to an <b>OH_Drawing_Point2D</b> object to store the last point.
 * @return Returns the error code.
 *         Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 *         Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if path or point is nullptr, or the path is empty.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathGetLastPoint(OH_Drawing_Path* path, OH_Drawing_Point2D* point);

/**
 * @brief Checks whether the fill type of the path is the inverse type.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param isInverse Whether the fill type is the inverse type. It is used as an output parameter. **true** if the fill
 * type is the inverse type; **false** otherwise.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **path** or **isInverse** is a null pointer.
 * @since 23
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathIsInverseFillType(const OH_Drawing_Path* path, bool* isInverse);

/**
 * @brief Toggles the fill type of the path to the inverse type.
 *
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **path** is a null pointer.
 * @since 23
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathToggleInverseFillType(OH_Drawing_Path* path);

/**
 * @brief Checks if two paths are equal.
 *
 * @param path Indicates the pointer to an <b>OH_Drawing_Path</b> object.
 * @param other Indicates the pointer to another <b>OH_Drawing_Path</b> object to compare.
 * @param equal Indicates whether the two paths are equal.
 * @return Returns the error code.
 *         Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 *         Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if path or other is nullptr, or equal is nullptr.
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathIsEqual(OH_Drawing_Path* path, OH_Drawing_Path* other, bool* equal);

#ifdef __cplusplus
}
#endif
/** @} */
#endif