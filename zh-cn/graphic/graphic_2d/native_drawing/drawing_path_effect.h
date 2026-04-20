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
 * @since 12
 * @version 1.0
 */
/**
 * @file drawing_path_effect.h
 *
 * @brief This file declares the functions related to the path effect in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_PATH_EFFECT_H
#define C_INCLUDE_DRAWING_PATH_EFFECT_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 路径效果的绘制样式枚举。
 *
 * @since 18
 * @version 1.0
 */
typedef enum {
    /**
     * 表示路径效果是平移效果。
     */
    DRAWING_PATH_DASH_STYLE_TRANSLATE,
    /**
     * 表示路径效果是旋转效果。
     */
    DRAWING_PATH_DASH_STYLE_ROTATE,
    /**
     * 表示路径效果是变形效果。
     */
    DRAWING_PATH_DASH_STYLE_MORPH,
} OH_Drawing_PathDashStyle;

/**
 * @brief 创建路径组合的路径效果对象。首先应用内部路径效果，然后应用外部路径效果。
 *
 * @param outer 表示组合路径效果中外部路径效果{@link OH_Drawing_PathEffect}的指针。
 * @param inner 表示组合路径效果中内部路径效果{@link OH_Drawing_PathEffect}的指针。
 * @return 函数返回一个指针，指针指向创建的路径效果对象{@link OH_Drawing_PathEffect}。
 * 如果返回nullptr，则创建失败，失败的原因可能是outer或者inner为nullptr。
 * @since 18
 * @version 1.0
 */
OH_Drawing_PathEffect* OH_Drawing_CreateComposePathEffect(OH_Drawing_PathEffect* outer, OH_Drawing_PathEffect* inner);

/**
 * @brief 创建一个将路径的夹角变成指定半径的圆角的路径效果对象。
 *
 * @param radius 表示圆角的半径，该值必须大于0时才生效。
 * @return 函数返回一个指针，指针指向创建的路径效果对象{@link OH_Drawing_PathEffect}。
 * 如果返回nullptr，则创建失败，失败的可能原因是radius小于等于0。
 * @since 18
 * @version 1.0
 */
OH_Drawing_PathEffect* OH_Drawing_CreateCornerPathEffect(float radius);

/**
 * @brief 创建一个虚线效果的路径效果对象。虚线效果由一组虚线开的间隔、虚线关的间隔数据决定。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * intervals为NULL或者count小于等于0时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param intervals 虚线间隔数组首地址，偶数项的值表示虚线开的间隔长度，奇数项的值表示虚线关的间隔长度，单位为像素。
 * @param count 虚线间隔数组元素的个数，必须为大于0的偶数。
 * @param phase 虚线间隔数组中偏移量。
 * @return 函数返回一个指针，指针指向创建的路径效果对象{@link OH_Drawing_PathEffect}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_PathEffect* OH_Drawing_CreateDashPathEffect(float* intervals, int count, float phase);

/**
 * @brief 创建一种将路径打散并且在路径上产生不规则分布的路径效果对象。
 *
 * @param segLength 表示路径中每进行一次打散操作的长度，该值大于0时有效果。
 * @param deviation 表示绘制时的末端点的最大移动偏离量。
 * @return 函数返回一个指针，指针指向创建的路径效果对象{@link OH_Drawing_PathEffect}。
 * @since 18
 * @version 1.0
 */
OH_Drawing_PathEffect* OH_Drawing_CreateDiscretePathEffect(float segLength, float deviation);

/**
 * @brief 创建一个虚线效果的路径效果对象。
 *
 * @param path 表示虚线样式的路径对象{@link OH_Drawing_Path}的指针。
 * @param advance 表示虚线段的步长。
 * @param phase 表示虚线段内图形在虚线步长范围内的偏移量。
 * @param type 表示虚线路径效果样式。
 * @return 函数返回一个指针，指针指向创建的路径效果对象{@link OH_Drawing_PathEffect}。
 * 如果返回nullptr，则创建失败，失败的可能原因是path为nullptr或者advance小于等于0。
 * @since 18
 * @version 1.0
 */
OH_Drawing_PathEffect* OH_Drawing_CreatePathDashEffect(const OH_Drawing_Path* path, float advance, float phase,
    OH_Drawing_PathDashStyle type);

/**
 * @brief 创建一个使用两种路径效果分别生效后叠加的路径效果对象。
 *
 * @param firstPathEffect 指向路径对象{@link OH_Drawing_PathEffect}的指针。
 * @param secondPathEffect 指向路径对象{@link OH_Drawing_PathEffect}的指针。
 * @return 函数返回一个指针，指针指向创建的路径效果对象{@link OH_Drawing_PathEffect}。
 * 如果返回nullptr，则创建失败，失败的可能原因是firstPathEffect或者secondPathEffect为nullptr。
 * @since 18
 * @version 1.0
 */
OH_Drawing_PathEffect* OH_Drawing_CreateSumPathEffect(OH_Drawing_PathEffect* firstPathEffect,
    OH_Drawing_PathEffect* secondPathEffect);

/**
 * @brief 销毁路径效果对象并回收该对象占有内存。
 *
 * @param pathEffect 指向路径效果对象{@link OH_Drawing_PathEffect}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathEffectDestroy(OH_Drawing_PathEffect* pathEffect);

#ifdef __cplusplus
}
#endif
/** @} */
#endif