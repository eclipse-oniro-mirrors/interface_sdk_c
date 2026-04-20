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
 * @since 11
 * @version 1.0
 */
/**
 * @file drawing_shader_effect.h
 *
 * @brief This file declares the functions related to the shader effect in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_SHADER_EFFECT_H
#define C_INCLUDE_DRAWING_SHADER_EFFECT_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 着色器效果平铺模式的枚举。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 如果着色器效果超出其原始边界，则复制边缘颜色。
     */
    CLAMP,
    /**
     * 在水平和垂直方向上重复着色器效果图像。
     */
    REPEAT,
    /**
     * 水平和垂直重复着色器效果图像，交替镜像。
     */
    MIRROR,
    /**
     * 只在原始区域内绘制，其他地方返回透明黑色。
     */
    DECAL,
} OH_Drawing_TileMode;

/**
 * @brief 创建具有单一颜色的着色器。
 *
 * @param color 表示着色器的ARGB格式颜色，该参数为32位无符号整数。
 * @return 函数会返回一个指针，指针指向创建的着色器对象{@link OH_Drawing_ShaderEffect}。如果对象返回NULL，表示创建失败；可能的原因是可用内存为空。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateColorShader(const uint32_t color);

/**
 * @brief 创建着色器，在两个指定点之间生成线性渐变。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * startPt、endPt、colors任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * tileMode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param startPt 表示渐变的起点。
 * @param endPt 表示渐变的终点。
 * @param colors 表示在两个点之间分布的颜色。
 * @param pos 表示colors中每个对应颜色的相对位置，数组长度需和colors保持一致。如果pos为NULL，颜色均匀分布在起点和终点之间。
 * @param size 表示颜色数组的长度（即元素个数），范围为[0, 256]，长度为0时，表示无渐变效果。
 * @param tileMode 着色器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @return 返回创建的着色器对象的指针。
 * @since 11
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateLinearGradient(const OH_Drawing_Point* startPt,
    const OH_Drawing_Point* endPt, const uint32_t* colors,
    const float* pos, uint32_t size, OH_Drawing_TileMode tileMode);

/**
 * @brief 创建着色器，在两个指定点之间生成线性渐变。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * startPt、endPt、colors任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * tileMode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param startPt 表示渐变的起点。
 * @param endPt 表示渐变的终点。
 * @param colors 表示在两个点之间分布的颜色。
 * @param pos 表示colors中每个对应颜色的相对位置，数组长度需和colors保持一致。如果pos为NULL，颜色均匀分布在起点和终点之间。
 * @param size 表示颜色数组的长度（即元素个数），范围为[0, 256]，长度为0时，表示无渐变效果。
 * @param tileMode 着色器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @param matrix 表示作用于着色器上的矩阵变换，如果matrix是NULL, 默认是一个单位矩阵。
 * @return 函数会返回一个指针，指针指向创建的着色器对象{@link OH_Drawing_ShaderEffect}。如果对象返回NULL，表示创建失败；可能的原因是可用内存为空，或者是startPt、endPt、
 * colors至少一个为NULL。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateLinearGradientWithLocalMatrix(
    const OH_Drawing_Point2D* startPt, const OH_Drawing_Point2D* endPt, const uint32_t* colors, const float* pos,
    uint32_t size, OH_Drawing_TileMode tileMode, const OH_Drawing_Matrix* matrix);

/**
 * @brief 创建着色器，在给定圆心和半径的情况下生成径向渐变。
 * 从起点到终点颜色从内到外进行圆形渐变（从中间向外拉）被称为径向渐变。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * centerPt、colors任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * tileMode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param centerPt 表示渐变的圆心。
 * @param radius 表示渐变的半径，需为非负数。
 * @param colors 表示在径向上分布的颜色。
 * @param pos 表示colors中每个对应颜色的相对位置，数组长度需和colors保持一致。如果pos为NULL，颜色均匀分布在径向上。
 * @param size 表示颜色数组的长度（即元素个数），范围为[0, 256]，长度为0时，表示无渐变效果。
 * @param tileMode 着色器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @return 返回创建的着色器对象的指针。
 * @since 11
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateRadialGradient(const OH_Drawing_Point* centerPt, float radius,
    const uint32_t* colors, const float* pos, uint32_t size, OH_Drawing_TileMode tileMode);

/**
 * @brief 创建着色器，在给定圆心和半径的情况下生成径向渐变。
 * 从起点到终点颜色从内到外进行圆形渐变（从中间向外拉）被称为径向渐变。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * centerPt、colors任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * tileMode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param centerPt 表示渐变的圆心。
 * @param radius 表示渐变的半径。
 * @param colors 表示在径向上分布的颜色。
 * @param pos 表示colors中每个对应颜色的相对位置，数组长度需和colors保持一致。如果pos为NULL，颜色均匀分布在径向上。
 * @param size 表示颜色数组的长度（即元素个数），范围为[0, 256]，长度为0时，表示无渐变效果。
 * @param tileMode 着色器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @param matrix 表示作用于着色器上的矩阵变换，如果matrix是NULL, 默认是一个单位矩阵。
 * @return 函数会返回一个指针，指针指向创建的着色器对象{@link OH_Drawing_ShaderEffect}。如果对象返回NULL，表示创建失败；可能的原因是可用内存为空，或者是centerPt、
 * colors至少一个为NULL。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateRadialGradientWithLocalMatrix(
    const OH_Drawing_Point2D* centerPt, float radius, const uint32_t* colors, const float* pos, uint32_t size,
    OH_Drawing_TileMode tileMode, const OH_Drawing_Matrix* matrix);

/**
 * @brief 创建着色器，在给定中心的情况下结合矩阵变换生成扇形渐变。
 * 颜色从0°到360°渐变被称为扇形渐变。
 *
 * @param centerPt 表示渐变的圆心。
 * @param colors 表示在两个点之间分布的颜色。
 * @param pos 表示colors中每个对应颜色的相对位置，数组长度需和colors保持一致。如果pos为NULL，颜色均匀分布在0°和360°之间。
 * @param size 表示颜色数组的长度（即元素个数），范围为[0, 256]，长度为0时，表示无渐变效果。
 * @param tileMode 着色器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @param matrix 表示作用于着色器上的矩阵变换，如果matrix是NULL, 默认是一个单位矩阵。
 * @return 函数会返回一个指针，指针指向创建的着色器对象{@link OH_Drawing_ShaderEffect}。
 * 存在以下任意一种情况时，会返回空指针：1.可用内存为空；2.centerPt、colors任意为空；3.tileMode超出枚举范围。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateSweepGradientWithLocalMatrix(
    const OH_Drawing_Point* centerPt, const uint32_t* colors, const float* pos, uint32_t size,
    OH_Drawing_TileMode tileMode, const OH_Drawing_Matrix* matrix);

/**
 * @brief 创建着色器，在给定中心的情况下生成扇形渐变。
 * 颜色从0°到360°渐变被称为扇形渐变。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * centerPt、colors任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * tileMode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param centerPt 表示渐变的圆心。
 * @param colors 表示在两个点之间分布的颜色。
 * @param pos 表示colors中每个对应颜色的相对位置，数组长度需和colors保持一致。如果pos为NULL，颜色均匀分布在0°和360°之间。
 * @param size 表示颜色数组的长度（即元素个数），范围为[0, 256]，长度为0时，表示无渐变效果。
 * @param tileMode 着色器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @return 函数会返回一个指针，指针指向创建的着色器对象{@link OH_Drawing_ShaderEffect}。
 * 存在以下任意一种情况时，会返回空指针：1.可用内存为空；2.centerPt、colors任意为空；3.tileMode超出枚举范围。
 * @since 11
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateSweepGradient(const OH_Drawing_Point* centerPt,
    const uint32_t* colors, const float* pos, uint32_t size, OH_Drawing_TileMode tileMode);

/**
 * @brief 创建图像着色器。此接口不建议用于录制类型的画布，会影响性能。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * image、samplingOptions任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * tileX、tileY任意一个不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param image 指向图片对象{@link OH_Drawing_Image}的指针。
 * @param tileX 水平方向着色器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @param tileY 垂直方向着色器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @param samplingOptions 指向采样选项对象{@link OH_Drawing_SamplingOptions}的指针。
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。如果矩阵指针为空，默认传入单位矩阵。
 * @return 函数会返回一个指针，指针指向创建的着色器对象{@link OH_Drawing_ShaderEffect}。
 * 存在以下任意一种情况时，会返回空指针：1.可用内存为空；2.image、samplingOptions任意为空；3.tileX、tileY超出枚举范围。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateImageShader(OH_Drawing_Image* image,
    OH_Drawing_TileMode tileX, OH_Drawing_TileMode tileY, const OH_Drawing_SamplingOptions* samplingOptions,
    const OH_Drawing_Matrix* matrix);

/**
 * @brief 创建像素图着色器。
 *
 * @param pixelMap 指向像素图{@link OH_Drawing_PixelMap}的指针。
 * @param tileX 水平方向着色器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @param tileY 垂直方向着色器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @param samplingOptions 指向采样选项对象{@link OH_Drawing_SamplingOptions}的指针。
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。如果矩阵指针为空，默认传入单位矩阵。
 * @return 返回创建的着色器对象的指针。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreatePixelMapShader(OH_Drawing_PixelMap* pixelMap,
    OH_Drawing_TileMode tileX, OH_Drawing_TileMode tileY, const OH_Drawing_SamplingOptions* samplingOptions,
    const OH_Drawing_Matrix* matrix);

/**
 * @brief 创建着色器，在给定两个圆之间生成渐变。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * startPt、endPt、colors任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * tileMode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param startPt 表示渐变的起点圆心。
 * @param startRadius 表示渐变的起点半径，需为非负数。
 * @param endPt 表示渐变的终点圆心。
 * @param endRadius 表示渐变的终点半径，需为非负数。
 * @param colors 表示在两个圆之间分布的颜色。
 * @param pos 表示colors中每个对应颜色的相对位置，数组长度需和colors保持一致。如果pos为NULL，颜色均匀分布在两个圆之间。
 * @param size 表示颜色数组的长度（即元素个数），范围为[0, 256]，长度为0时，表示无渐变效果。
 * @param tileMode 着色器效果平铺模式类型，支持可选的具体模式可见{@link OH_Drawing_TileMode}枚举。
 * @param matrix 表示作用于着色器上的矩阵变换，如果matrix是NULL, 默认是一个单位矩阵。
 * @return 函数会返回一个指针，指针指向创建的着色器对象{@link OH_Drawing_ShaderEffect}。如果对象返回NULL，表示创建失败；可能的原因是：1.可用内存为空；2.startPt、endPt、
 * colors任意为空；3.tileMode超出枚举范围。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateTwoPointConicalGradient(const OH_Drawing_Point2D* startPt,
    float startRadius, const OH_Drawing_Point2D* endPt, float endRadius, const uint32_t* colors, const float* pos,
    uint32_t size, OH_Drawing_TileMode tileMode, const OH_Drawing_Matrix* matrix);

/**
 * @brief 按照指定的混合模式对两个着色器进行叠加，生成一个新的着色器。
 *
 * @param dst 在混合模式中作为目标色的着色器。
 * @param src 在混合模式中作为源色的着色器。
 * @param mode 混合模式{@link OH_Drawing_BlendMode}。
 * @return 函数会返回一个指针，指针指向创建的着色器对象{@link OH_Drawing_ShaderEffect}。
 * 当可用内存为空，或者是dst、src任意一个为空，或mode超出枚举范围时，结果返回NULL，表示创建失败。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ShaderEffect* OH_Drawing_ShaderEffectCreateCompose(OH_Drawing_ShaderEffect* dst,
    OH_Drawing_ShaderEffect* src, OH_Drawing_BlendMode mode);

/**
 * @brief 销毁着色器对象，并收回该对象占用的内存。
 *
 * @param shaderEffect 表示指向着色器对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_ShaderEffectDestroy(OH_Drawing_ShaderEffect* shaderEffect);

#ifdef __cplusplus
}
#endif
/** @} */
#endif