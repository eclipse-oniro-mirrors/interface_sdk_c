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
 * @brief 声明与绘图模块中的图像滤波器对象相关的函数。支持创建模糊、颜色变换、偏移、基于着色器等多种图像滤波器效果，
 * 并支持销毁滤波器对象，适用于图像处理和视觉特效增强的场景。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
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
 * @brief 创建具有模糊效果的图像滤波器。使用本函数创建的图像滤波器对象，
 * 在使用完毕后必须调用{@link OH_Drawing_ImageFilterDestroy}进行销毁，否则会导致内存泄漏。
 *
 * @param sigmaX 表示沿x轴方向上高斯模糊的标准差，单位为px。传入小于等于0的值时不生效。
 * @param sigmaY 表示沿y轴方向上高斯模糊的标准差，单位为px。传入小于等于0的值时不生效。
 * @param tileMode 用于控制图像滤波器效果在图像边界处的平铺方式。
 * @param imageFilter 表示将要和当前图像滤波器叠加的输入滤波器，如果为NULL，表示直接将当前图像滤波器作用于原始图像。
 * @return 函数会返回一个指针，指针指向创建的图像滤波器对象{@link OH_Drawing_ImageFilter}。如果返回NULL，表示创建失败；
 * 可能的原因是可用内存不足。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateBlur(float sigmaX, float sigmaY, OH_Drawing_TileMode tileMode,
    OH_Drawing_ImageFilter* imageFilter);

/**
 * @brief 创建具有模糊效果的图像滤波器。
 * <br>支持传入裁剪矩形，用于限制模糊效果仅在图像的指定矩形区域内生效。使用本函数创建的图像滤波器对象，
 * 在使用完毕后必须调用{@link OH_Drawing_ImageFilterDestroy}进行销毁，否则会导致内存泄漏。
 *
 * @param sigmaX 表示沿x轴方向上高斯模糊的标准差，单位为px。必须大于0.0，传入小于等于0的值时不生效。
 * @param sigmaY 表示沿y轴方向上高斯模糊的标准差，单位为px。必须大于0.0，传入小于等于0的值时不生效。
 * @param tileMode 用于控制图像滤波器效果在图像边界处的平铺方式。
 * @param input 表示将要和当前图像滤波器叠加的输入滤波器，如果为NULL，表示直接将当前图像滤波器作用于原始图像。
 * @param rect 表示裁剪的矩形区域，如果为NULL，表示直接将模糊效果作用于整个图像。
 * @return 函数会返回一个指针，指针指向创建的图像滤波器对象{@link OH_Drawing_ImageFilter}。如果返回NULL，表示创建失败；
 * 可能的原因是可用内存不足。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateBlurWithCrop(float sigmaX, float sigmaY,
    OH_Drawing_TileMode tileMode, OH_Drawing_ImageFilter* input, const OH_Drawing_Rect* rect);

/**
 * @brief 创建具有颜色变换效果的图像滤波器。本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * colorFilter为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；可用内存不足导致内存分配失败时也会产生错误码。
 * 请检查并确保传入的colorFilter为有效的颜色滤波器对象指针。
 * 使用本函数创建的图像滤波器对象，在使用完毕后必须调用{@link OH_Drawing_ImageFilterDestroy}进行销毁，
 * 否则会导致内存泄漏。
 *
 * @param colorFilter 指向具有颜色变换效果的颜色滤波器对象{@link OH_Drawing_ColorFilter}。如果为NULL，
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 * @param imageFilter 表示将要和当前图像滤波器叠加的输入滤波器，如果为NULL，表示直接将当前图像滤波器作用于原始图像。
 * @return 函数会返回一个指针，指针指向创建的图像滤波器对象{@link OH_Drawing_ImageFilter}。如果返回NULL，表示创建失败；
 * 可能的原因是可用内存不足，或者是colorFilter为NULL。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateFromColorFilter(OH_Drawing_ColorFilter* colorFilter,
    OH_Drawing_ImageFilter* imageFilter);

/**
 * @brief 创建一个偏移滤波器，将输入的滤波器按照指定向量进行平移。适用于创建阴影偏移效果或位移动画等场景。
 * 使用本函数创建的图像滤波器对象，在使用完毕后必须调用
 * {@link OH_Drawing_ImageFilterDestroy}进行销毁，否则会导致内存泄漏。
 *
 * @param x 表示沿x轴方向的平移距离。
 * @param y 表示沿y轴方向的平移距离。
 * @param imageFilter 需要进行平移的滤波器，如果为NULL，则将无滤波效果的绘制结果进行平移。
 * @return 函数会返回一个指针，指针指向创建的图像滤波器对象{@link OH_Drawing_ImageFilter}。如果返回NULL，表示创建失败；
 * 可能的原因是可用内存不足。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateOffset(float x, float y, OH_Drawing_ImageFilter* imageFilter);

/**
 * @brief 基于着色器创建一个图像滤波器。使用本函数创建的图像滤波器对象，
 * 在使用完毕后必须调用{@link OH_Drawing_ImageFilterDestroy}进行销毁，否则会导致内存泄漏。
 *
 * @param shaderEffect 表示要应用于图像的着色器效果。
 * @return 函数会返回一个指针，指针指向创建的图像滤波器对象{@link OH_Drawing_ImageFilter}。如果返回NULL，表示创建失败；
 * 可能的原因是可用内存不足，或者是shaderEffect为NULL。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ImageFilter* OH_Drawing_ImageFilterCreateFromShaderEffect(OH_Drawing_ShaderEffect* shaderEffect);

/**
 * @brief 销毁图像滤波器对象并回收该对象占用的内存。
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