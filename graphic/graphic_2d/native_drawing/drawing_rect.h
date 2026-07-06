/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
 * @file drawing_rect.h
 *
 * @brief This file declares the functions related to the rectangle in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_RECT_H
#define C_INCLUDE_DRAWING_RECT_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an **OH_Drawing_Rect** object, without sorting the coordinates passed in. This means that the
 * coordinates of the upper left corner of the rectangle can be greater than those of the lower right corner.
 *
 * @param left X coordinate of the upper left corner of the rectangle.
 * @param top Y coordinate of the upper left corner of the rectangle.
 * @param right X coordinate of the lower right corner of the rectangle.
 * @param bottom Y coordinate of the lower right corner of the rectangle.
 * @return Returns the pointer to the **OH_Drawing_Rect** object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_Rect* OH_Drawing_RectCreate(float left, float top, float right, float bottom);

/**
 * @brief Checks whether two rectangles intersect and if yes, sets **rect** to the area of intersection.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **rect** or **other** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @param other Pointer to an **OH_Drawing_Rect** object.
 * @return Returns **true** if they intersect (**rect** is set to the intersection area); returns **false** otherwise (*
 * *rect** remains unchanged).
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_RectIntersect(OH_Drawing_Rect* rect, const OH_Drawing_Rect* other);

/**
 * @brief Obtains the union of two rectangles.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **rect** or **other** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @param other Pointer to an **OH_Drawing_Rect** object.
 * @return Returns **true** if the union is obtained; returns **false** otherwise. The possible failure cause is that
 * at least one of the parameters **rect** and **other** is NULL or the size of the rectangle specified by **other** is
 * empty.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_RectJoin(OH_Drawing_Rect* rect, const OH_Drawing_Rect* other);

/**
 * @brief Sets the horizontal coordinate of the upper left corner of a rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @param left X coordinate of the upper left corner of the rectangle.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RectSetLeft(OH_Drawing_Rect* rect, float left);

/**
 * @brief Sets the vertical coordinate of the upper left corner of a rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @param top Y coordinate of the upper left corner of the rectangle.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RectSetTop(OH_Drawing_Rect* rect, float top);

/**
 * @brief Sets the horizontal coordinate of the lower right corner of a rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @param right X coordinate of the lower right corner of the rectangle.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RectSetRight(OH_Drawing_Rect* rect, float right);

/**
 * @brief Sets the vertical coordinate of the lower right corner of a rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @param bottom Y coordinate of the lower right corner of the rectangle.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RectSetBottom(OH_Drawing_Rect* rect, float bottom);

/**
 * @brief Obtains the X coordinate of the upper left corner of a rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @return X coordinate of the upper left corner of the rectangle.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_RectGetLeft(OH_Drawing_Rect* rect);

/**
 * @brief Obtains the Y coordinate of the upper left corner of a rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @return Y coordinate of the upper left corner of the rectangle.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_RectGetTop(OH_Drawing_Rect* rect);

/**
 * @brief Obtains the X coordinate of the lower right corner of a rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @return X coordinate of the lower right corner of the rectangle.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_RectGetRight(OH_Drawing_Rect* rect);

/**
 * @brief Obtains the Y coordinate of the lower right corner of a rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @return Y coordinate of the lower right corner of the rectangle.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_RectGetBottom(OH_Drawing_Rect* rect);

/**
 * @brief Obtains the height of a rectangle. The height is calculated by using the Y coordinate of the lower right
 * corner of the rectangle minus the Y coordinate of the upper left corner.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * @return Returns the height of the rectangle, in pixels.
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_RectGetHeight(OH_Drawing_Rect* rect);

/**
 * @brief Obtains the width of a rectangle. The width is calculated by using the X coordinate of the lower right corner
 * of the rectangle minus the X coordinate of the upper left corner.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @return Returns the weight of the rectangle, in pixels.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_RectGetWidth(OH_Drawing_Rect* rect);

/**
 * @brief Copies a source rectangle to create a new one.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **src** or **dst** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param src Pointer to a source rectangle, which is an **OH_Drawing_Rect** object.
 * @param dst Pointer to a destination rectangle, which is an **OH_Drawing_Rect** object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RectCopy(OH_Drawing_Rect* src, OH_Drawing_Rect* dst);

/**
 * @brief Destroys an **OH_Drawing_Rect** object and reclaims the memory occupied by the object.
 *
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_RectDestroy(OH_Drawing_Rect* rect);

/**
 * @brief Creates a rectangle array object to store multiple rectangle objects. Release this pointer by calling
 * {@link OH_Drawing_RectDestroyArray}
 * when this object is no longer needed.
 *
 * @param size Size of the rectangle array. The value cannot exceed 65536, which is the maximum number of glyph indices.
 * @return Returns the pointer to the {@link OH_Drawing_Array} object created. If the returned object pointer is null,
 * the creation fails.
 * Possible causes are that no memory is available or an input parameter is incorrect.
 * @since 18
 * @version 1.0
 */
OH_Drawing_Array* OH_Drawing_RectCreateArray(size_t size);

/**
 * @brief Obtains the size of an {@link OH_Drawing_Array} object.
 *
 * @param rectArray Pointer to an {@link OH_Drawing_Array} object.
 * @param pSize Pointer to the size_t type, which is used as an output parameter to store the size of the rectangle
 * array.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if either **rectArray** or **pSize** is NULL.
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RectGetArraySize(OH_Drawing_Array* rectArray, size_t* pSize);

/**
 * @brief Obtains the rectangle with the specified index in a rectangle array.
 *
 * @param rectArray Pointer to an {@link OH_Drawing_Array} object.
 * @param index Index of the rectangle array.
 * @param rect Double pointer to {@link OH_Drawing_Rect}, which is returned to the caller as an output parameter.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **rectArray** or **rect** is null or **index** is out of range.
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RectGetArrayElement(OH_Drawing_Array* rectArray, size_t index,
    OH_Drawing_Rect** rect);

/**
 * @brief Destroys an **OH_Drawing_Array** object and reclaims the memory occupied by the object.
 *
 * @param rectArray Pointer to an {@link OH_Drawing_Array} object.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INVALID_PARAMETER** if **rectArray** is NULL.
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RectDestroyArray(OH_Drawing_Array* rectArray);

/**
 * @brief Checks whether a rectangle completely contains another rectangle.
 *
 * @param rect Pointer to the {@link OH_Drawing_Rect} object. This rectangle is used to check whether another rectangle
 * (**other**) is contained.
 * @param other Pointer to the {@link OH_Drawing_Rect} object. This rectangle is used to check whether it is contained
 * by another rectangle (**rect**).
 * @param isContains Result of whether a rectangle completely contains another rectangle. It is used as an output
 * parameter. **true** indicates that **rect** completely contains **other**. **false** indicates that **rect** does
 * not completely contain **other**.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the **rect**, **other**, or **isContains** parameter is empty.
 * @since 22
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RectContains(OH_Drawing_Rect* rect, const OH_Drawing_Rect* other, bool* isContains);

/**
 * @brief Adds a specified value to the bounds of a rectangle.
 *
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @param left Value to be added to the left bound of the rectangle (X coordinate of the upper left corner of the
 * rectangle).
 * @param top Value to be added to the top bound of the rectangle (Y coordinate of the upper left corner of the
 * rectangle).
 * @param right Value to be added to the right bound of the rectangle (X coordinate of the lower right corner of the
 * rectangle).
 * @param bottom Value to be added to the bottom bound of the rectangle (Y coordinate of the lower right corner of the
 * rectangle).
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the **rect** parameter is empty.
 * @since 22
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RectInset(OH_Drawing_Rect* rect, float left, float top, float right, float bottom);

/**
 * @brief Checks whether a rectangle is empty.
 *
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @param isEmpty Whether a rectangle is empty. It is used as an output parameter. **true** means yes; **false**
 * otherwise.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **rect** or **isEmpty** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RectIsEmpty(const OH_Drawing_Rect* rect, bool* isEmpty);

/**
 * @brief Offsets a rectangle along the X axis and Y axis.
 *
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @param dx Offset on the X axis. A positive number indicates an offset towards the positive direction of the X axis,
 * and a negative number indicates an offset towards the negative direction of the X axis.
 * @param dy Offset on the Y axis. A positive number indicates an offset towards the positive direction of the Y axis,
 * and a negative number indicates an offset towards the negative direction of the Y axis.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **rect** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RectOffset(OH_Drawing_Rect* rect, float dx, float dy);

/**
 * @brief Offsets a rectangle to a specific position while keeping the width and height unchanged.
 *
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @param newLeft X coordinate of the upper left corner of the rectangle after the offset.
 * @param newTop Y coordinate of the upper left corner of the rectangle after the offset.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **rect** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RectOffsetTo(OH_Drawing_Rect* rect, float newLeft, float newTop);

/**
 * @brief Clears a rectangle (by setting the X and Y coordinates of the upper left corner and lower right corner to **0*
 * *).
 *
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **rect** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RectSetEmpty(OH_Drawing_Rect* rect);

/**
 * @brief Sorts the coordinates of a rectangle based on the actual position.
 *
 * @param rect Pointer to the {@link OH_Drawing_Rect} object.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **rect** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RectSort(OH_Drawing_Rect* rect);

/**
 * @brief Sets the current rectangle to the union of this rectangle and another rectangle.
 *
 * @param rect Pointer to this {@link OH_Drawing_Rect} object.
 * @param other Pointer to another {@link OH_Drawing_Rect} object.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **rect** or **other** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RectUnion(OH_Drawing_Rect* rect, const OH_Drawing_Rect* other);

#ifdef __cplusplus
}
#endif
/** @} */
#endif