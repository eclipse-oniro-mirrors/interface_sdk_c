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
 * @file drawing_lattice.h
 *
 * @brief This file declares the functions related to the rectangular lattice object.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 23
 */

#ifndef C_INCLUDE_DRAWING_LATTICE_H
#define C_INCLUDE_DRAWING_LATTICE_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the types of rectangles used to fill the lattices. It is applicable only to rectangular lattice
 * objects.
 *
 * @since 23
 */
typedef enum {
    /**
     * Draws an image into the rectangular lattice.
     *
     * @since 23
     */
    DEFAULT,
    /**
     * Sets the rectangular lattice to be transparent.
     *
     * @since 23
     */
    TRANSPARENT,
    /**
     * Draws the colors from the **fColors** array of the rectangular lattice object into the lattice.
     *
     * @since 23
     */
    FIXED_COLOR,
} OH_Drawing_LatticeRectType;

/**
 * @brief Destroys an **OH_Drawing_Lattice** object and reclaims the memory occupied by the object.
 *
 * @param lattice Pointer to an {@link OH_Drawing_Lattice} object.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **OHDrawingLattice* lattice** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_LatticeDestroy(OH_Drawing_Lattice* lattice);

/**
 * @brief Divides the image into lattices. The lattices on both even columns and even rows are fixed, and they are
 * drawn at their original size if the target is large enough. If the target is too small to hold the fixed lattices,
 * all the fixed lattices are scaled down to fit the target, and the lattices that are not on even columns and even
 * rows are scaled to accommodate the remaining space.
 *
 * @param xDivs Array of X coordinates used to divide the image. The value is an integer.
 * @param yDivs Array of Y coordinates used to divide the image. The value is an integer.
 * @param xCount Size of the array that holds the X coordinates. The value range is [0, 5].
 * @param yCount Size of the array that holds the Y coordinates. The value range is [0, 5].
 * @param bounds The original bounding rectangle to be drawn, which defaults to the size of the original image
 * rectangle. The value must be an integer and is rounded down.
 * @param rectTypes Array of rectangle types used to fill the lattice.
 * @param rectTypeCount Size of the **rectTypes** array. If **rectTypes** is not a null pointer, the array size must be
 * **(xCount + 1)*(yCount + 1)**.
 * If **rectTypes** is a null pointer, the array size must be **0**.
 * @param colors Array of colors used to fill the lattice.
 * @param colorCount Size of the **colors** array. If **colors** is not a null pointer, the array size must be **(
 * xCount + 1)*(yCount + 1)**.
 * If **colors** is a null pointer, the array size must be **0**.
 * @param lattice Double pointer to an {@link OH_Drawing_Lattice} object, which serves as an output parameter returned
 * to the caller.
 * @return Execution result.
 * Returns **OH_DRAWING_SUCCESS** if the operation is successful.
 * Returns **OH_DRAWING_ERROR_INCORRECT_PARAMETER** for any of the following reasons:
 * - **xDivs** or **yDivs** is a null pointer.
 * - **rectTypes** is not a null pointer, and **rectTypeCount** is not equal to **(xCount + 1)*(yCount + 1)**.
 * - **colors** is not a null pointer, and **colorCount** is not equal to **(xCount + 1)*(yCount + 1)**.
 * - **rectTypes** is a null pointer, and **rectTypeCount** is not equal to **0**.
 * - **colors** is a null pointer, and **colorCount** is not equal to **0**.
 * Returns **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE**, indicating that the enumeration value in **rectTypes** exceeds
 * the valid enumeration range.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_LatticeCreate(const int* xDivs, const int* yDivs, uint32_t xCount, uint32_t yCount,
    const OH_Drawing_Rect* bounds, const OH_Drawing_LatticeRectType* rectTypes, uint32_t rectTypeCount,
    const uint32_t* colors, uint32_t colorCount, OH_Drawing_Lattice** lattice);

#ifdef __cplusplus
}
#endif
#endif // C_INCLUDE_DRAWING_LATTICE_H

/** @} */