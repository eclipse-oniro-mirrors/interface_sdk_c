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
 * @brief 定义填充网格的矩形类型的枚举。仅在矩形网格对象中使用。
 *
 * @since 23
 */
typedef enum {
    /**
     * 将图像绘制到矩形网格中。
     *
     * @since 23
     */
    DEFAULT,
    /**
     * 将矩形网格设置为透明的。
     *
     * @since 23
     */
    TRANSPARENT,
    /**
     * 将矩形网格对象中fColors数组的颜色绘制到矩形网格中。
     *
     * @since 23
     */
    FIXED_COLOR,
} OH_Drawing_LatticeRectType;

/**
 * @brief 用于销毁矩形网格对象并回收该对象占有的内存。
 *
 * @param lattice 指向矩形网格对象{@link OH_Drawing_Lattice}的指针。
 * @return 函数返回执行结果。
 * OH_DRAWING_SUCCESS，表示执行成功。
 * OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示lattice是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_LatticeDestroy(OH_Drawing_Lattice* lattice);

/**
 * @brief Divides the image into lattices. The lattices on both even columns and even rows are fixed, and they are
 * drawn at their original size if the target is large enough. If the target is too small to hold the fixed lattices,
 * all the fixed lattices are scaled down to fit the target, and the lattices that are not on even columns and even
 * rows are scaled to accommodate the remaining space.
 *
 * @param xDivs 用于划分图像的X坐标值数组。该参数为整数。
 * @param yDivs 用于划分图像的Y坐标值数组。该参数为整数。
 * @param xCount X坐标值数组的大小。取值范围为[0, 5]。
 * @param yCount Y坐标值数组的大小。取值范围为[0, 5]。
 * @param bounds 要绘制的原始边界矩形，默认为原始图像矩形大小。参数应为整数，向下取整。
 * @param rectTypes 填充网格的类型数组。
 * @param rectTypeCount rectTypes数组的大小。如果rectTypes不是空指针，数组大小必须等于`(xCount + 1)*(yCount + 1)`。
 * 如果rectTypes是空指针，数组大小必须等于0。
 * @param colors 填充网格的颜色数组。
 * @param colorCount colors数组的大小。 如果colors不是空指针，数组大小必须等于`(xCount + 1)*(yCount + 1)`。
 * 如果colors是空指针，数组大小必须等于0。
 * @param lattice 指向矩形网格对象{@link OH_Drawing_Lattice}的二级指针，作为出参，返回给调用者。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，有以下可能原因：
 * - xDivs或yDivs是空指针nullptr；
 * - rectTypes不是空指针，且rectTypeCount不等于`(xCount + 1)*(yCount + 1)`。
 * - colors不是空指针，且colorCount不等于`(xCount + 1)*(yCount + 1)`。
 * - rectTypes是空指针，且rectTypeCount不等于0。
 * - colors是空指针，且colorCount不等于0。
 * 返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE，表示rectTypes中的枚举值超过枚举范围。
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