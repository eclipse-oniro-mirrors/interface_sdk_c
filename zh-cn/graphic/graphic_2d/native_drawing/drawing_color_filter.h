/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @file drawing_color_filter.h
 *
 * @brief This file declares the functions related to the color filter in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_COLOR_FILTER_H
#define C_INCLUDE_DRAWING_COLOR_FILTER_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建具有混合模式的颜色滤波器。
 *
 * @param color 表示颜色，是一个32位（ARGB）变量。
 * @param blendMode 表示混合模式。支持可选的混合模式具体可见{@link OH_Drawing_BlendMode}枚举。
 * @return 返回创建的颜色滤波器对象的指针。
 * @since 11
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateBlendMode(uint32_t color, OH_Drawing_BlendMode blendMode);

/**
 * @brief 将两个颜色滤波器合成一个新的颜色滤波器。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * outerColorFilter、innerColorFilter任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param outerColorFilter 指向颜色滤波器对象一的指针。
 * @param innerColorFilter 指向颜色滤波器对象二的指针。
 * @return 返回创建的颜色滤波器对象的指针。
 * @since 11
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateCompose(OH_Drawing_ColorFilter* outerColorFilter,
    OH_Drawing_ColorFilter* innerColorFilter);

/**
 * @brief 创建具有5x4颜色矩阵的颜色滤波器。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * matrix为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param matrix 表示矩阵，以长度为20的浮点数组表示。
 * @return 返回创建的颜色滤波器对象的指针。
 * @since 11
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateMatrix(const float matrix[20]);

/**
 * @brief 创建一个从线性颜色空间转换到SRGB颜色空间的颜色滤波器。
 *
 * @return 返回创建的颜色滤波器对象的指针。
 * @since 11
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateLinearToSrgbGamma(void);

/**
 * @brief 创建颜色滤波器将RGB颜色通道应用于SRGB的伽玛曲线。
 *
 * @return 返回创建的颜色滤波器对象的指针。
 * @since 11
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateSrgbGammaToLinear(void);

/**
 * @brief 创建一个颜色滤波器将其输入的亮度值乘以透明度通道，并将红色、绿色和蓝色通道设置为零。
 *
 * @return 返回创建的颜色滤波器对象的指针。
 * @since 11
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateLuma(void);

/**
 * @brief 创建一个光照颜色滤波器，此滤波器会将RGB通道的颜色值乘以一种颜色值并加上另一种颜色值，计算结果会被限制在0到255范围内。
 *
 * @param mulColor 用来乘法运算的颜色值。
 * @param addColor 用来加法运算的颜色值。
 * @return 返回创建的颜色滤波器对象的指针。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ColorFilter* OH_Drawing_ColorFilterCreateLighting(uint32_t mulColor, uint32_t addColor);

/**
 * @brief 销毁颜色滤波器对象，并回收该对象占用的内存。
 *
 * @param colorFilter 表示指向颜色滤波器对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_ColorFilterDestroy(OH_Drawing_ColorFilter* colorFilter);

#ifdef __cplusplus
}
#endif
/** @} */
#endif