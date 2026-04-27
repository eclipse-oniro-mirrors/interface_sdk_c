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
 * @file drawing_round_rect.h
 *
 * @brief This file declares the functions related to the rounded rectangle in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_ROUND_RECT_H
#define C_INCLUDE_DRAWING_ROUND_RECT_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines an enum for the corner positions of a rounded rectangle.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Top left corner of the rounded rectangle.
     */
    CORNER_POS_TOP_LEFT,
    /**
     * Top right corner of the rounded rectangle.
     */
    CORNER_POS_TOP_RIGHT,
    /**
     * Bottom right corner of the rounded rectangle.
     */
    CORNER_POS_BOTTOM_RIGHT,
    /**
     * Bottom left corner of the rounded rectangle.
     */
    CORNER_POS_BOTTOM_LEFT,
} OH_Drawing_CornerPos;

/**
 * @brief Creates an **OH_Drawing_RoundRect** object. This API may return an error code. For details, call
 * {@link OH_Drawing_ErrorCodeGet}
 * .
 * If **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @param xRad Radius of the rounded corner on the X axis. A negative number is invalid.
 * @param yRad Radius of the rounded corner on the Y axis. A negative number is invalid.
 * @return Returns the pointer to the **OH_Drawing_RoundRect** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_RoundRect* OH_Drawing_RoundRectCreate(const OH_Drawing_Rect* rect, float xRad, float yRad);

/**
 * @brief Creates a copy of a rounded rectangle.
 *
 * @param roundRect Pointer to an {@link OH_Drawing_RoundRect} object.
 * @return Returns the pointer to the new **OH_Drawing_RoundRect** object created.
 * @since 20
 * @version 1.0
 */
OH_Drawing_RoundRect* OH_Drawing_RoundRectCopy(const OH_Drawing_RoundRect* roundRect);

/**
 * @brief Sets the radii of the specified rounded corner in this rounded rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **roundRect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param roundRect Pointer to an **OH_Drawing_RoundRect** object.
 * @param pos Position of the rounded corner. For details about the available options, see {@link OH_Drawing_CornerPos}.
 * @param radii OH_Drawing_Corner_Radii struct, including the radii on the X axis and Y axis. A radius less than or
 * equal to 0 is invalid.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RoundRectSetCorner(OH_Drawing_RoundRect* roundRect,
    OH_Drawing_CornerPos pos, OH_Drawing_Corner_Radii radii);

/**
 * @brief Obtains the radii of the specified rounded corner in a rounded rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **roundRect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param roundRect Pointer to an **OH_Drawing_RoundRect** object.
 * @param pos Position of the rounded corner. For details about the available options, see {@link OH_Drawing_CornerPos}.
 * @return Returns an OH_Drawing_Corner_Radii struct, including the radii on the X axis and Y axis.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Corner_Radii OH_Drawing_RoundRectGetCorner(OH_Drawing_RoundRect* roundRect, OH_Drawing_CornerPos pos);

/**
 * @brief Destroys an **OH_Drawing_RoundRect** object and reclaims the memory occupied by the object.
 *
 * @param roundRect Pointer to an **OH_Drawing_RoundRect** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_RoundRectDestroy(OH_Drawing_RoundRect* roundRect);

/**
 * @brief Translates a rounded rectangle by an offset along the X axis and Y axis.
 *
 * @param roundRect Pointer to an {@link OH_Drawing_Point2D} object.
 * @param dx X offset.
 * @param dy Y offset.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **roundRect** is NULL.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RoundRectOffset(OH_Drawing_RoundRect* roundRect, float dx, float dy);
#ifdef __cplusplus
}
#endif
/** @} */
#endif