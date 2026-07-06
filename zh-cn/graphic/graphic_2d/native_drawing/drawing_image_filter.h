/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @file drawing_image_filter.h
 *
 * @brief This file declares the functions related to the image filter in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_IMAGE_FILTER_H
#define C_INCLUDE_DRAWING_IMAGE_FILTER_H

#include "drawing_shader_effect.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建具有模糊效果的图像滤波器。
 *
 * @param sigmaX 表示沿x轴方向上高斯模糊的标准差，必须大于0。
 * @param sigmaY 表示沿y轴方向上高斯模糊的标准差，必须大于0。
 * @param tileMode 图像滤波器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @param imageFilter 表示将要和当前图像滤波器叠加的输入滤波器, 如果为NULL，表示直接将当前图像滤波器作用于原始图像。
 * @return 函数会返回一个指针，指针指向创建的图像滤波器对象{@link OH_Drawing_ImageFilter}。如果对象返回NULL，表示创建失败；可能的原因是可用内存为空。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateBlur(float sigmaX, float sigmaY, OH_Drawing_TileMode tileMode,
    OH_Drawing_ImageFilter* imageFilter);

/**
 * @brief 创建具有模糊效果的图像滤波器。
 *
 * @param sigmaX 表示沿x轴方向上高斯模糊的标准差，必须大于0.0。
 * @param sigmaY 表示沿y轴方向上高斯模糊的标准差，必须大于0.0。
 * @param tileMode 图像滤波器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @param input 表示将要和当前图像滤波器叠加的输入滤波器, 如果为NULL，表示直接将当前图像滤波器作用于原始图像。
 * @param rect 表示裁剪的矩形区域，如果为NULL，表示直接将模糊效果作用于整个图像。
 * @return 函数会返回一个指针，指针指向创建的图像滤波器对象{@link OH_Drawing_ImageFilter}。如果对象返回NULL，表示创建失败；可能的原因是可用内存为空。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateBlurWithCrop(float sigmaX, float sigmaY,
    OH_Drawing_TileMode tileMode, OH_Drawing_ImageFilter* input, const OH_Drawing_Rect* rect);

/**
 * @brief 创建具有颜色变换效果的图像滤波器。本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * colorFilter为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param colorFilter 指向具有颜色变换效果的颜色滤波器对象{@link OH_Drawing_ColorFilter}。
 * @param imageFilter 表示将要和当前图像滤波器叠加的输入滤波器, 如果为NULL，表示直接将当前图像滤波器作用于原始图像。
 * @return 函数会返回一个指针，指针指向创建的图像滤波器对象{@link OH_Drawing_ImageFilter}。如果对象返回NULL，表示创建失败；可能的原因是可用内存为空，或者是colorFilter为NULL。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateFromColorFilter(OH_Drawing_ColorFilter* colorFilter,
    OH_Drawing_ImageFilter* imageFilter);

/**
 * @brief 创建一个偏移滤波器，将输入的滤波器按照指定向量进行平移。
 *
 * @param x 水平方向的平移距离。
 * @param y 竖直方向的平移距离。
 * @param imageFilter 需进行平移的滤波器，如果为空，则将无滤波效果的绘制结果进行平移。
 * @return 函数会返回一个指针，指针指向创建的图像滤波器对象{@link OH_Drawing_ImageFilter}。如果对象返回NULL，表示创建失败，可能原因为可用内存为空。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateOffset(float x, float y, OH_Drawing_ImageFilter* imageFilter);

/**
 * @brief 基于着色器创建一个图像滤波器。
 *
 * @param shaderEffect 表示要应用于图像的着色器效果。
 * @return 函数会返回一个指针，指针指向创建的图像滤波器对象{@link OH_Drawing_ImageFilter}。如果结果返回NULL，表示创建失败，可能原因为可用内存为空。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateFromShaderEffect(OH_Drawing_ShaderEffect* shaderEffect);

/**
 * @brief 销毁图像滤波器对象并回收该对象占有内存。
 *
 * @param imageFilter 指向图像滤波器对象{@link OH_Drawing_ImageFilter}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ImageFilterDestroy(OH_Drawing_ImageFilter* imageFilter);

#ifdef __cplusplus
}
#endif
/** @} */
#endif