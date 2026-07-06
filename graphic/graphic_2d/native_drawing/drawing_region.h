/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
 * @file drawing_region.h
 *
 * @brief This file declares the functions related to the region in the drawing module, including creating a region,
 * setting the boundary, and destroying a region.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_REGION_H
#define C_INCLUDE_DRAWING_REGION_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the operation modes available for a region.
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * Difference operation.
     */
    REGION_OP_MODE_DIFFERENCE,
    /**
     * Intersection operation.
     */
    REGION_OP_MODE_INTERSECT,
    /**
     * Union operation.
     */
    REGION_OP_MODE_UNION,
    /**
     * XOR operation.
     */
    REGION_OP_MODE_XOR,
    /**
     * Reverse difference operation.
     */
    REGION_OP_MODE_REVERSE_DIFFERENCE,
    /**
     * Replacement operation.
     */
    REGION_OP_MODE_REPLACE,
} OH_Drawing_RegionOpMode;

/**
 * @brief Creates an **OH_Drawing_Region** object for more accurate graphical control.
 *
 * @return Returns the pointer to the {@link OH_Drawing_Region} object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_Region* OH_Drawing_RegionCreate(void);

/**
 * @brief Creates a copy of a region object.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object to be copied.
 * @return Returns the pointer to the **OH_Drawing_Region** object created.
 * @since 20
 * @version 1.0
 */
OH_Drawing_Region* OH_Drawing_RegionCopy(const OH_Drawing_Region* region);

/**
 * @brief Checks whether a region contains the specified point.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **region** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @param x X coordinate of the point.
 * @param y Y coordinate of the point.
 * @return Returns **true** if the region contains the specified point; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_RegionContains(OH_Drawing_Region* region, int32_t x, int32_t y);

/**
 * @brief Combines two regions based on the specified operation mode.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **region** or **dst** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 * If **op** is not set to one of the enumerated values, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param region Pointer to an {@link OH_Drawing_Region} object, in which the resulting region is saved.
 * @param other Pointer to the {@link OH_Drawing_Region} object.
 * @param op Operation mode of the region. For details about the available options, see {@link OH_Drawing_RegionOpMode}.
 * @return Returns **true** if the resulting region is not empty; returns false otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_RegionOp(OH_Drawing_Region* region, const OH_Drawing_Region* other, OH_Drawing_RegionOpMode op);

/**
 * @brief Sets the boundary for an **OH_Drawing_Region** object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **region** or **rect** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @param rect Pointer to an **OH_Drawing_Rect** object.
 * @return Returns **true** if the setting is successful; returns **false** otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_RegionSetRect(OH_Drawing_Region* region, const OH_Drawing_Rect* rect);

/**
 * @brief Sets a region to the area described by the path.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **region**, **path**, or **clip** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @param path Pointer to the {@link OH_Drawing_Path} object.
 * @param clip Pointer to the {@link OH_Drawing_Region} object.
 * @return Returns **true** if the resulting region is not empty; returns false otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_RegionSetPath(OH_Drawing_Region* region, const OH_Drawing_Path* path, const OH_Drawing_Region* clip);

/**
 * @brief Destroys an **OH_Drawing_Region** object and reclaims the memory occupied by the object.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RegionDestroy(OH_Drawing_Region* region);

/**
 * @brief Sets the existing region to empty.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @return Returns one of the following result codes:
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if the **region** parameter is empty.
 * @since 22
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RegionEmpty(OH_Drawing_Region* region);

/**
 * @brief Sets the path as the boundary of the region. If the region is empty, the path is also empty.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @param path Pointer to the {@link OH_Drawing_Path} object. It is used as an output parameter.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **region** or **path** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionGetBoundaryPath(const OH_Drawing_Region* region, OH_Drawing_Path* path);

/**
 * @brief Obtains the smallest bounding rectangle that contains the region.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @param rect Pointer to the {@link OH_Drawing_Rect} object. It is used as an output parameter.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **region** or **rect** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionGetBounds(const OH_Drawing_Region* region, OH_Drawing_Rect* rect);

/**
 * @brief Checks whether the region contains two or more rectangles.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @param isComplex Whether this region contains multiple rectangles. It is used as an output parameter. **true** means
 * yes; **false** otherwise.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **region** or **isComplex** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionIsComplex(const OH_Drawing_Region* region, bool* isComplex);

/**
 * @brief Checks whether the region is empty.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @param isEmpty Whether the region is empty. It is used as an output parameter. **true** means yes; **false**
 * otherwise.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **region** or **isEmpty** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionIsEmpty(const OH_Drawing_Region* region, bool* isEmpty);

/**
 * @brief Checks whether the region the same as a rectangle.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @param isRect Whether the region the same as a rectangle. It is used as an output parameter. **true** means yes; **
 * false** otherwise.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **region** or **isRect** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionIsRect(const OH_Drawing_Region* region, bool* isRect);

/**
 * @brief Checks whether the region is the same as a single rectangle and contains the specified rectangle.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @param left X coordinate of the upper left corner of the specified rectangle.
 * @param top Y coordinate of the upper left corner of the specified rectangle.
 * @param right X coordinate of the lower right corner of the specified rectangle.
 * @param bottom Y coordinate of the lower right corner of the specified rectangle.
 * @param isContained Whether the region is the same as a single rectangle and contains the specified rectangle. It is
 * used as an output parameter.
 * **true** if the current region is the same as a single rectangle and contains the specified rectangle; **false**
 * otherwise.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **region** or **isContained** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionQuickContains(const OH_Drawing_Region* region,
    int32_t left, int32_t top, int32_t right, int32_t bottom, bool* isContained);

/**
 * @brief Checks whether the region is empty or does not intersect the specified rectangle.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @param left X coordinate of the upper left corner of the specified rectangle.
 * @param top Y coordinate of the upper left corner of the specified rectangle.
 * @param right X coordinate of the lower right corner of the specified rectangle.
 * @param bottom Y coordinate of the lower right corner of the specified rectangle.
 * @param isReject Whether the region is empty or whether the specified rectangle does not intersect with the region.
 * It is used as an output parameter.
 * **true** means yes; **false** otherwise.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **region** or **isReject** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionQuickReject(const OH_Drawing_Region* region,
    int32_t left, int32_t top, int32_t right, int32_t bottom, bool* isReject);

/**
 * @brief Translates the region by a specified distance on the X and Y axes. If the region is empty, no operation is
 * performed.
 *
 * @param region Pointer to the {@link OH_Drawing_Region} object.
 * @param dx Distance to be translated on the X axis, in pixels.
 * @param dy Distance to be translated on the Y axis, in pixels.
 * @return Execution result.
 * **OH_DRAWING_SUCCESS** if the operation is successful.
 * **OH_DRAWING_ERROR_INCORRECT_PARAMETER** if **region** is a null pointer.
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_RegionTranslate(OH_Drawing_Region* region, int32_t dx, int32_t dy);

#ifdef __cplusplus
}
#endif
/** @} */
#endif