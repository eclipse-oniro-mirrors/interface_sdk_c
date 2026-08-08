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
 * @brief 声明与矩形网格对象相关的函数。矩形网格（Lattice）用于将图像划分为固定区域和可缩放区域，
 * 解决图像缩放时关键区域变形的问题，保持关键区域清晰不变形的同时实现其余区域的灵活缩放。
 * 固定区域在目标网格足够大时以原始大小绘制，目标网格太小时按比例缩小以适应目标网格，其余区域缩放以适应剩余空间。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
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
 * @brief 定义填充网格的矩形类型的枚举，决定对应网格单元格的渲染方式。
 *
 * @since 23
 */
typedef enum {
    /**
     * @brief 将图像绘制到矩形网格中。
     *
     * @since 23
     */
    DEFAULT,
    /**
     * @brief 将矩形网格设置为透明的。
     *
     * @since 23
     */
    TRANSPARENT,
    /**
     * @brief 将矩形网格对象中fColors数组的颜色绘制到矩形网格中。
     *
     * @since 23
     */
    FIXED_COLOR,
} OH_Drawing_LatticeRectType;

/**
 * @brief 用于销毁由{@link OH_Drawing_LatticeCreate()}创建的矩形网格对象并回收该对象占用的内存。
 * 与{@link OH_Drawing_LatticeCreate()}配对使用。
 *
 * @param lattice 指向由{@link OH_Drawing_LatticeCreate()}创建的矩形网格对象{@link OH_Drawing_Lattice}的指针。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示lattice是空指针。
 * @since 23
 */
OH_Drawing_ErrorCode OH_Drawing_LatticeDestroy(OH_Drawing_Lattice* lattice);

/**
 * @brief 创建矩形网格对象。将图像划分为矩形网格，同时处于偶数列（列索引为偶数，即第0、2、
 * 4…列）和偶数行（行索引为偶数，即第0、2、4…行）上的网格是固定的，如果目标网格足够大，
 * 则这些固定网格以其原始大小进行绘制。
 * 如果目标网格太小，无法容纳这些固定网格，则所有固定网格都会按比例缩小以适应目标网格。其余网格将进行缩放，
 * 以适应剩余的空间。
 *
 * @param xDivs 用于划分图像的X坐标值数组，数组元素需为整数，单位为物理像素px，且不能为空指针。
 * @param yDivs 用于划分图像的Y坐标值数组，数组元素需为整数，单位为物理像素px，且不能为空指针。
 * @param xCount X坐标值数组的大小。取值范围为[0, 5]。
 * @param yCount Y坐标值数组的大小。取值范围为[0, 5]。
 * @param bounds 要绘制的原始边界矩形。当需要指定不同于原始图像的绘制边界时传入此参数，
 * 不传入（空指针）时默认使用原始图像矩形大小。矩形坐标值应为整数，单位为物理像素px，非整数值将被向下取整。
 * @param rectTypes 填充网格的矩形类型数组，枚举值必须在有效范围内。如果rectTypes为空指针，表示不指定填充类型，
 * 所有网格区域默认按DEFAULT方式绘制图像，rectTypeCount必须为0。
 * @param rectTypeCount rectTypes数组的大小。如果rectTypes不是空指针，数组大小必须等于`(xCount + 1)*(yCount + 1)`。
 *     <br>如果rectTypes是空指针，数组大小必须等于0。
 * @param colors 填充网格的颜色数组，颜色值为ARGB格式（0xAARRGGBB）。当rectTypes中包含FIXED_COLOR时，
 * colors中对应位置的颜色会被绘制到对应矩形网格中，且colors不能为空指针。
 *     当rectTypes不包含FIXED_COLOR且colors为空指针时，默认不使用自定义颜色填充网格。
 * @param colorCount colors数组的大小。如果colors不是空指针，数组大小必须等于`(xCount + 1)*(yCount + 1)`。
 *     <br>如果colors是空指针，数组大小必须等于0。
 * @param lattice 指向矩形网格对象{@link OH_Drawing_Lattice}的二级指针，作为出参，返回给调用者，且不能为空指针。
 * @return 函数返回执行结果。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，有以下可能原因：
 *     <br>- xDivs或yDivs是空指针nullptr；
 *     <br>- rectTypes不是空指针，且rectTypeCount不等于`(xCount + 1)*(yCount + 1)`。
 *     <br>- colors不是空指针，且colorCount不等于`(xCount + 1)*(yCount + 1)`。
 *     <br>- rectTypes是空指针，且rectTypeCount不等于0。
 *     <br>- colors是空指针，且colorCount不等于0。
 *     <br>- lattice是空指针。
 *     <br>返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE，表示rectTypes中的枚举值超过枚举范围。
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