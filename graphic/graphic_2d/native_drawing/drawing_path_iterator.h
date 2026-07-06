/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 */
/**
 * @file drawing_path_iterator.h
 *
 * @brief This file declares the functions related to the path operation iterator object.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 23
 */

#ifndef C_INCLUDE_DRAWING_PATH_ITERATOR_H
#define C_INCLUDE_DRAWING_PATH_ITERATOR_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the path operation types contained in an iterator. It is used to read path operation instructions.
 *
 * @since 23
 */
typedef enum {
    /**
     * Sets the start point of the path.
     */
    MOVE = 0,
    /**
     * Adds a line segment.
     */
    LINE = 1,
    /**
     * Adds a quadratic Bezier curve for smooth transitions.
     */
    QUAD = 2,
    /**
     * Adds a conic curve.
     */
    CONIC = 3,
    /**
     * Adds a cubic Bezier curve for smooth transitions.
     */
    CUBIC = 4,
    /**
     * Closes the path.
     */
    CLOSE = 5,
    /**
     * Completes the path configuration.
     */
    DONE = CLOSE + 1,
} OH_Drawing_PathIteratorVerb;

/**
 * @brief Creates an **OH_Drawing_PathIterator** object.
 *
 * @param path Pointer to an {@link OH_Drawing_Path} object.
 * @param pathIterator Double pointer to an {@link OH_Drawing_PathIterator} object, which serves as an output parameter.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **path** or **pathIterator** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorCreate(const OH_Drawing_Path* path, OH_Drawing_PathIterator** pathIterator);

/**
 * @brief Destroys an **OH_Drawing_PathIterator** object and reclaims the memory occupied by the object.
 *
 * @param pathIterator Pointer to an {@link OH_Drawing_PathIterator} object.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **pathIterator** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorDestroy(OH_Drawing_PathIterator* pathIterator);

/**
 * @brief Checks whether there is any next operation in the path operation iterator.
 *
 * @param pathIterator Pointer to an {@link OH_Drawing_PathIterator} object.
 * @param hasNext Whether there is a next operation in the path operation iterator, which serves as an output parameter.
 * A value of **true** means there is a next operation; **false** means the opposite.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **pathIterator** or **hasNext** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorHasNext(const OH_Drawing_PathIterator* pathIterator, bool* hasNext);

/**
 * @brief Retrieves the next operation in this path and moves the iterator to that operation.
 *
 * @param pathIterator Pointer to an {@link OH_Drawing_PathIterator} object.
 * @param points Array of coordinate points.
 * @param count Size of the coordinate point array.
 * @param offset Offset of the write position relative to the start point in the array. The value range is [0, count - 4].
 * @param verb Next operation of the current path, which serves as an output parameter.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **pathIterator**, **points**, or **verb** is a null pointer.
 * **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** if **count** is less than offset + 4.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorNext(OH_Drawing_PathIterator* pathIterator,
    OH_Drawing_Point2D* points, uint32_t count, uint32_t offset, OH_Drawing_PathIteratorVerb* verb);

/**
 * @brief Retrieves the next operation in this path, without moving the iterator.
 *
 * @param pathIterator Pointer to an {@link OH_Drawing_PathIterator} object.
 * @param verb Next operation of the current path, which serves as an output parameter.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **pathIterator** or **verb** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_PathIteratorPeek(const OH_Drawing_PathIterator* pathIterator,
    OH_Drawing_PathIteratorVerb* verb);

#ifdef __cplusplus
}
#endif
#endif // C_INCLUDE_DRAWING_PATH_ITERATOR_H

/** @} */