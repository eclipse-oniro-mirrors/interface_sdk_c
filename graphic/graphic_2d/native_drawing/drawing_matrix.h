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
 * @file drawing_matrix.h
 *
 * @brief This file declares the functions related to the matrix in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_MATRIX_H
#define C_INCLUDE_DRAWING_MATRIX_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an **OH_Drawing_Matrix** object.
 *
 * @return Returns the pointer to the <b>OH_Drawing_Matrix</b> object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_Matrix* OH_Drawing_MatrixCreate(void);

/**
 * @brief Creates a copy of a matrix object.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object to be copied.
 * @return Returns the pointer to the <b>OH_Drawing_Matrix</b> object created.
 * @since 20
 * @version 1.0
 */
OH_Drawing_Matrix* OH_Drawing_MatrixCopy(const OH_Drawing_Matrix* matrix);

/**
 * @brief Creates an **OH_Drawing_Matrix** with the rotation attribute.
 * The matrix is obtained by rotating an identity matrix by a given degree around the rotation point (x, y).
 *
 * @param deg Angle to rotate, in degrees. A positive value indicates a clockwise rotation, and a negative value
 * indicates a counterclockwise rotation.
 * @param x Coordinate point on the X axis.
 * @param y Coordinate point on the Y axis.
 * @return Returns the pointer to the <b>OH_Drawing_Matrix</b> object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Matrix* OH_Drawing_MatrixCreateRotation(float deg, float x, float y);

/**
 * @brief Creates an **OH_Drawing_Matrix** with the scale attribute.
 * The matrix is obtained by scaling an identity matrix with the factor (sx, sy) at the rotation point (px, py).
 *
 * @param sx Scale factor on the X axis. If a negative number is passed in, the matrix is mirrored around y = px before
 * being scaled. The value is a floating point number.
 * @param sy Scale factor on the Y axis. If a negative number is passed in, the matrix is mirrored around x = py before
 * being scaled. The value is a floating point number.
 * @param px Coordinate point on the X axis.
 * @param py Coordinate point on the Y axis.
 * @return Returns the pointer to the <b>OH_Drawing_Matrix</b> object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Matrix* OH_Drawing_MatrixCreateScale(float sx, float sy, float px, float py);

/**
 * @brief Creates an **OH_Drawing_Matrix** with the translation attribute.
 * The matrix is obtained by translating the identity matrix by the distance (dx, dy).
 *
 * @param dx Distance to translate on the X axis. A positive number indicates a translation towards the positive
 * direction of the X axis, and a negative number indicates a translation towards the negative direction of the X axis.
 * The value is a floating point number.
 * @param dy Distance to translate on the Y axis. A positive number indicates a translation towards the positive
 * direction of the Y axis, and a negative number indicates a translation towards the negative direction of the Y axis.
 * The value is a floating point number.
 * @return Returns the pointer to the <b>OH_Drawing_Matrix</b> object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Matrix* OH_Drawing_MatrixCreateTranslation(float dx, float dy);

/**
 * @brief Sets matrix parameters for an **OH_Drawing_Matrix** object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **OH_Drawing_Matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to an **OH_Drawing_Matrix** object.
 * @param scaleX Scale factor on the X axis.
 * @param skewX Skew factor on the X axis.
 * @param transX Translation coefficient on the X axis.
 * @param skewY Skew factor on the Y axis.
 * @param scaleY Scale factor on the Y axis.
 * @param transY Translation coefficient on the Y axis.
 * @param persp0 Perspective coefficient of the X axis.
 * @param persp1 Perspective coefficient of the Y axis.
 * @param persp2 Perspective scale coefficient.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_MatrixSetMatrix(OH_Drawing_Matrix* matrix, float scaleX, float skewX, float transX,
    float skewY, float scaleY, float transY, float persp0, float persp1, float persp2);

/**
 * @brief Defines an enum for the matrix scaling modes.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Scales the source rectangle both horizontally and vertically to exactly match the destination rectangle.
     */
    SCALE_TO_FIT_FILL,
    /**
     * Scales the source rectangle and aligns it to the left and top edges of the destination rectangle.
     */
    SCALE_TO_FIT_START,
    /**
     * Scales the source rectangle and aligns it to the center of the destination rectangle.
     */
    SCALE_TO_FIT_CENTER,
    /**
     * Scales the source rectangle and aligns it to the right and bottom edges of the destination rectangle.
     */
    SCALE_TO_FIT_END,
} OH_Drawing_ScaleToFit;

/**
 * @brief Scales a matrix to map a source rectangle to a destination rectangle.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **matrix**, **src**, and **dst** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param src Pointer to the {@link OH_Drawing_Rect} object of the mapping source.
 * @param dst Pointer to the {@link OH_Drawing_Rect} object of the mapping destination.
 * @param stf Scaling mode. For details about the available options, see {@link OH_Drawing_ScaleToFit}.
 * @return Returns true if dst is empty, and sets matrix to:
 * | 0 0 0 |
 * | 0 0 0 |
 * | 0 0 1 |
 *
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_MatrixSetRectToRect(OH_Drawing_Matrix* matrix, const OH_Drawing_Rect* src,
    const OH_Drawing_Rect* dst, OH_Drawing_ScaleToFit stf);

/**
 * @brief Premultiplies this matrix by a matrix that is derived from an identity matrix after it has been rotated by a
 * given degree around the rotation point (px, py).
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param degree Angle to rotate, in degrees. A positive value indicates a clockwise rotation, and a negative value
 * indicates a counterclockwise rotation.
 * @param px X coordinate of the rotation point.
 * @param py Y coordinate of the rotation point.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixPreRotate(OH_Drawing_Matrix* matrix, float degree, float px, float py);

/**
 * @brief Premultiplies a matrix by an identity matrix that scales with the factor (sx, sy) at the scale point (px, py).
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param sx Scale factor on the X axis. If a negative number is passed in, the matrix is mirrored around y = px before
 * being scaled. The value is a floating point number.
 * @param sy Scale factor on the Y axis. If a negative number is passed in, the matrix is mirrored around x = py before
 * being scaled. The value is a floating point number.
 * @param px X coordinate of the scale point.
 * @param py Y coordinate of the scale point.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixPreScale(OH_Drawing_Matrix* matrix, float sx, float sy, float px, float py);

/**
 * @brief Premultiplies this matrix by a matrix that is derived from an identity matrix after it has been translated by
 * a given distance (dx, dy).
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param dx Horizontal distance to translate. A positive number indicates a translation towards the positive direction
 * of the X axis, and a negative number indicates a translation towards the negative direction of the X axis. The value
 * is a floating point number.
 * @param dy Vertical distance to translate. A positive number indicates a translation towards the positive direction
 * of the Y axis, and a negative number indicates a translation towards the negative direction of the Y axis. The value
 * is a floating point number.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixPreTranslate(OH_Drawing_Matrix* matrix, float dx, float dy);

/**
 * @brief Post multiplies this matrix by a matrix that is derived from an identity matrix after it has been rotated by
 * a given degree around the rotation point (px, py).
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param degree Angle to rotate, in degrees. A positive value indicates a clockwise rotation, and a negative value
 * indicates a counterclockwise rotation.
 * @param px X coordinate of the rotation point.
 * @param py Y coordinate of the rotation point.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixPostRotate(OH_Drawing_Matrix* matrix, float degree, float px, float py);

/**
 * @brief Post multiplies a matrix by an identity matrix that scales with the factor (sx, sy) at the scale point (px,
 * py).
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param sx Scale factor on the X axis. If a negative number is passed in, the matrix is mirrored around y = px before
 * being scaled. The value is a floating point number.
 * @param sy Scale factor on the Y axis. If a negative number is passed in, the matrix is mirrored around x = py before
 * being scaled. The value is a floating point number.
 * @param px X coordinate of the scale point.
 * @param py Y coordinate of the scale point.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixPostScale(OH_Drawing_Matrix* matrix, float sx, float sy, float px, float py);

/**
 * @brief Post multiplies this matrix by a matrix that is derived from an identity matrix after it has been translated
 * by a given distance (dx, dy).
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param dx Horizontal distance to translate. A positive number indicates a translation towards the positive direction
 * of the X axis, and a negative number indicates a translation towards the negative direction of the X axis. The value
 * is a floating point number.
 * @param dy Vertical distance to translate. A positive number indicates a translation towards the positive direction
 * of the Y axis, and a negative number indicates a translation towards the negative direction of the Y axis. The value
 * is a floating point number.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixPostTranslate(OH_Drawing_Matrix* matrix, float dx, float dy);

/**
 * @brief Resets a matrix to an identity matrix.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixReset(OH_Drawing_Matrix* matrix);

/**
 * @brief Multiplies two matrices to produce a new matrix.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **total**, **a**, and **b** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param total Pointer to the {@link OH_Drawing_Matrix} object.
 * @param a Pointer to {@link OH_Drawing_Matrix} object a.
 * @param b Pointer to {@link OH_Drawing_Matrix} object b.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixConcat(OH_Drawing_Matrix* total, const OH_Drawing_Matrix* a,
    const OH_Drawing_Matrix* b);

/**
 * @brief Obtains all element values of a matrix.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param value Array used to store the obtained element values.
 * @return Returns the error code.
 * Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 * Returns {@link OH_DRAWING_ERROR_INVALID_PARAMETER} if matrix or value is nullptr.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_MatrixGetAll(OH_Drawing_Matrix* matrix, float value[9]);

/**
 * @brief Left-multiplies matrix a by matrix b.
 *
 * @param a Pointer to the {@link OH_Drawing_Matrix} object.
 * @param b Pointer to the {@link OH_Drawing_Matrix} object.
 * @return Returns the error code.
 * Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 * Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if a or b is nullptr.
 * @since 22
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_MatrixPreConcat(OH_Drawing_Matrix* a, OH_Drawing_Matrix* b);

/**
 * @brief Obtains a matrix value of a given index, which ranges from 0 to 8.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **index** is less than 0 or greater than 8, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param index Index, which ranges from 0 to 8.
 * @return Returns value corresponding to index.Returns 0 if out of range.
 * @since 12
 * @version 1.0
 */
float OH_Drawing_MatrixGetValue(OH_Drawing_Matrix* matrix, int index);

/**
 * @brief Sets this matrix as an identity matrix and rotates it by a given degree around the rotation point (px, py).
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param degree Angle to rotate, in degrees. A positive value indicates a clockwise rotation, and a negative value
 * indicates a counterclockwise rotation.
 * @param px Coordinate point on the X axis.
 * @param py Coordinate point on the Y axis.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixRotate(OH_Drawing_Matrix* matrix, float degree, float px, float py);

/**
 * @brief Sets a matrix as an identity matrix and translates it by a given distance (dx, dy).
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param dx Distance to translate on the X axis. A positive number indicates a translation towards the positive
 * direction of the X axis, and a negative number indicates a translation towards the negative direction of the X axis.
 * The value is a floating point number.
 * @param dy Distance to translate on the Y axis. A positive number indicates a translation towards the positive
 * direction of the Y axis, and a negative number indicates a translation towards the negative direction of the Y axis.
 * The value is a floating point number.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixTranslate(OH_Drawing_Matrix* matrix, float dx, float dy);

/**
 * @brief Sets a matrix as an identity matrix and scales it with the factor (sx, sy) at the rotation point (px, py).
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param sx Scale factor on the X axis. If a negative number is passed in, the matrix is mirrored around y = px before
 * being scaled. The value is a floating point number.
 * @param sy Scale factor on the Y axis. If a negative number is passed in, the matrix is mirrored around x = py before
 * being scaled. The value is a floating point number.
 * @param px Coordinate point on the X axis.
 * @param py Coordinate point on the Y axis.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixScale(OH_Drawing_Matrix* matrix, float sx, float sy, float px, float py);

/**
 * @brief Inverts a matrix and returns the result.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **matrix** or **inverse** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param inverse Pointer to the inverse {@link OH_Drawing_Matrix} object. You can call {@link OH_Drawing_MatrixCreate}
 * to create an inverse matrix object.
 * @return Returns true if the matrix is not nullptr and can be inverted;
 * returns false if the matrix is nullptr or cannot be inverted.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_MatrixInvert(OH_Drawing_Matrix* matrix, OH_Drawing_Matrix* inverse);

/**
 * @brief Generates a transformation matrix by setting source points and destination points.
 * Both the number of source points and that of destination points must be in the range [0, 4]. This API may return an
 * error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **count** is less than 0 or greater than 4, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param src Array of source points. If NULL is passed in, **count** must be 0.
 * @param dst Array of destination points. The number of destination points must be the same as that of source points.
 * If NULL is passed in, **count** must be 0.
 * @param count Number of source points or destination points. If 0 is passed in, the matrix is set to an identity
 * matrix.
 * @return Returns true if matrix is constructed successfully.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_MatrixSetPolyToPoly(OH_Drawing_Matrix* matrix, const OH_Drawing_Point2D* src,
    const OH_Drawing_Point2D* dst, uint32_t count);

/**
 * @brief Maps a source point array to a destination point array by means of matrix transformation.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **matrix**, **src**, and **dst** is NULL or **count** is less than or equal to 0, **
 * OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param src Array of source points.
 * @param dst Array of destination points. The number of destination points must be the same as that of source points.
 * @param count Number of source points or destination points.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_MatrixMapPoints(const OH_Drawing_Matrix* matrix, const OH_Drawing_Point2D* src,
    OH_Drawing_Point2D* dst, int count);

/**
 * @brief Maps a rectangle to the smallest rectangle that can enclose the vertices to which the four source vertices
 * are mapped by means of matrix transformation.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If any of **matrix**, **src**, and **dst** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param src Source rectangle.
 * @param dst Destination rectangle.
 * @return Returns true if the mapped src is equal to the dst; returns false is not equal.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_MatrixMapRect(const OH_Drawing_Matrix* matrix, const OH_Drawing_Rect* src, OH_Drawing_Rect* dst);

/**
 * @brief Checks whether two **OH_Drawing_Matrix** objects are equal.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **matrix** or **other** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to one {@link OH_Drawing_Matrix} object.
 * @param other Pointer to the other {@link OH_Drawing_Matrix} object.
 * @return Returns true if the two matrices are equal; returns false if not equal.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_MatrixIsEqual(OH_Drawing_Matrix* matrix, OH_Drawing_Matrix* other);

/**
 * @brief Checks whether an **OH_Drawing_Matrix** object is an identity matrix.
 * An identity matrix is as follows: | 1 0 0 || 0 1 0 || 0 0 1 |. This API may return an error code. For details, see
 * {@link OH_Drawing_ErrorCodeGet}
 * .
 * If **matrix** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @return Returns true if matrix is identity; returns false if not identity.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_MatrixIsIdentity(OH_Drawing_Matrix* matrix);

/**
 * @brief Checks whether the existing matrix is an affine matrix, which includes transformations such as translation,
 * rotation, and scaling.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param isAffine Whether the existing matrix is an affine matrix. It is used as an output parameter. **true** means
 * yes; **false** otherwise.
 * @return Returns the error code.
 * Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 * Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if matrix or isAffine is nullptr.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_MatrixIsAffine(const OH_Drawing_Matrix* matrix, bool* isAffine);

/**
 * @brief Left multiplies the current matrix by a matrix constructed based on (px, py) and (kx, ky).
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param kx Tilt on the X axis.
 * @param ky Tilt on the Y axis.
 * @param px X-coordinate of the tilt center.
 * @param py Y-coordinate of the tilt center.
 * @return Returns the error code.
 * Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 * Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if matrix is nullptr.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_MatrixPreSkew(OH_Drawing_Matrix* matrix, float kx, float ky, float px, float py);

/**
 * @brief Checks whether the rectangle remains rectangular after being mapped by the current matrix. This condition is
 * met when the matrix is an identity matrix or contains only affine transformations such as translation, scaling, and
 * rotation by 90 degrees.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param isRectStaysRect Whether a rectangle stays a rectangle after being mapped by a matrix. It is used as an output
 * parameter.
 * **true** means yes; **false** otherwise.
 * @return Returns the error code.
 * Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 * Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if matrix or isRectStaysRect is nullptr.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_MatrixRectStaysRect(const OH_Drawing_Matrix* matrix, bool* isRectStaysRect);

/**
 * @brief Sets the matrix to rotate around the rotation center (px, py) with the specified sine and cosine values.
 *
 * @param matrix Pointer to the {@link OH_Drawing_Matrix} object.
 * @param sinValue Sine value of the rotation angle.
 * @param cosValue Cosine value of the rotation angle.
 * @param px X-axis coordinate of the rotation center.
 * @param py Y-axis coordinate of the rotation center.
 * @return Returns the error code.
 * Returns {@link OH_DRAWING_SUCCESS} if the operation is successful.
 * Returns {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER} if matrix is nullptr.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_MatrixSetSinCos(OH_Drawing_Matrix* matrix, float sinValue, float cosValue,
    float px, float py);

/**
 * @brief Destroys an **OH_Drawing_Matrix** object and reclaims the memory occupied by the object.
 *
 * @param matrix Pointer to an **OH_Drawing_Matrix** object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_MatrixDestroy(OH_Drawing_Matrix* matrix);

#ifdef __cplusplus
}
#endif
/** @} */
#endif