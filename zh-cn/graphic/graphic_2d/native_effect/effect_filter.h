/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup effectKit
 * @{
 *
 * @brief 提供处理图像的基础能力，支持亮度调节、模糊化、灰度转换等效果。
 * 适用于需要在应用内快速实现图像滤镜效果的场景，如图像编辑、照片美化和相机滤镜等，
 * 开发者无需关注底层算法实现即可快速完成图像效果处理功能，降低开发复杂度。
 *
 * @since 12
 */

/**
 * @file effect_filter.h
 *
 * @brief 声明滤镜效果的接口。支持创建和管理多种滤镜效果，包括毛玻璃模糊、亮度调节、灰度转换、颜色反转等，
 * 支持通过自定义矩阵实现丰富的图像处理效果，适用于图像编辑、照片美化、视觉特效等场景。
 *
 * 必须成对调用{@link OH_Filter_CreateEffect}和{@link OH_Filter_Release}，确保资源正确释放。
 * 本文件接口均不支持多线程调用。
 *
 * @kit ArkGraphics2D
 * @library libnative_effect.so
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 12
 */

#ifndef C_INCLUDE_EFFECT_FILTER_H
#define C_INCLUDE_EFFECT_FILTER_H

#include "effect_types.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建一个OH_Filter对象，对图像应用各种滤镜效果（如模糊、提亮或灰度等），
 * 适用于图像编辑、相册应用和视频处理等场景。
 *
 * @param pixelmap [in] 作为滤镜效果处理源图像的位图对象。不能为NULL。
 * @param filter [out] 用来接收滤镜的二级指针。不能为NULL。
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} 操作成功则返回EFFECT_SUCCESS。</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} 当pixelmap或filter为空指针时，返回EFFECT_BAD_PARAMETER。</li>
 *         </ul>
 * @release effect_filter/OH_Filter_Release {filter}
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_CreateEffect(OH_PixelmapNative* pixelmap, OH_Filter** filter);

/**
 * @brief 释放OH_Filter对象。
 *
 * @param filter [in] 被释放的对象指针。不能为NULL。
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} 操作成功则返回EFFECT_SUCCESS。</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} 当filter为空指针时，返回EFFECT_BAD_PARAMETER。</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Release(OH_Filter* filter);

/**
 * @brief 创建一个毛玻璃滤镜效果，并添加到滤镜效果链中。
 *
 * @param filter [in] 滤镜指针，需要通过OH_Filter_CreateEffect创建并添加滤镜效果。不能为NULL。
 * @param radius [in] 毛玻璃效果的模糊半径，取值范围为[0, +∞)，单位为像素。
 *     值为0时不产生模糊效果；值越大，模糊效果越强；值越小，模糊效果越弱。
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} 操作成功则返回EFFECT_SUCCESS。</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} 当filter为空指针或radius小于0时，返回EFFECT_BAD_PARAMETER。</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Blur(OH_Filter* filter, float radius);

/**
 * @brief 创建一个毛玻璃滤镜效果，并添加到滤镜效果链中，支持选择着色器效果平铺模式。
 *
 * @param filter [in] 滤镜指针，需要通过OH_Filter_CreateEffect创建并添加滤镜效果。不能为NULL。
 * @param radius [in] 毛玻璃效果的模糊半径，取值范围为[0, +∞)，单位为像素。
 *     参数值为0时不产生模糊效果。值越大模糊效果越强。
 * @param tileMode [in] 着色器效果平铺模式，不同模式决定图像边缘区域的不同处理方式，
 *     支持可选的具体模式可见{@link EffectTileMode}枚举。
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} 操作成功则返回EFFECT_SUCCESS。</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} 当filter为空指针或radius小于0时，返回EFFECT_BAD_PARAMETER。</li>
 *         </ul>
 * @since 14
 */
EffectErrorCode OH_Filter_BlurWithTileMode(OH_Filter* filter, float radius, EffectTileMode tileMode);

/**
 * @brief 创建一个提亮效果，并添加到滤镜效果链中。
 *
 * @param filter [in] 滤镜指针，需要通过OH_Filter_CreateEffect创建并添加滤镜效果。不能为NULL。
 * @param brightness [in] 提亮效果的亮度值，取值范围为[0, 1]。取值为0时图像保持不变，取值为1时图像全白。
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} 操作成功则返回EFFECT_SUCCESS。</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} 当filter为空指针或
 *         brightness超出[0,1]时，返回EFFECT_BAD_PARAMETER。</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Brighten(OH_Filter* filter, float brightness);

/**
 * @brief 创建一个灰度效果，并添加到滤镜效果链中。
 *
 * @param filter [in] 滤镜指针，需要通过OH_Filter_CreateEffect创建并添加滤镜效果。不能为NULL。
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} 操作成功则返回EFFECT_SUCCESS。</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} 当filter为空指针时，返回EFFECT_BAD_PARAMETER。</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_GrayScale(OH_Filter* filter);

/**
 * @brief 创建一个反色效果，并添加到滤镜效果链中。
 *
 * @param filter [in] 滤镜指针，需要通过OH_Filter_CreateEffect创建并添加滤镜效果。不能为NULL。
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} 操作成功则返回EFFECT_SUCCESS。</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} 当filter为空指针时，返回EFFECT_BAD_PARAMETER。</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Invert(OH_Filter* filter);

/**
 * @brief 通过矩阵创建一个自定义的效果，并添加到滤镜效果链中，
 * 适用于需要实现特定的颜色变换效果（如色彩校正、色调调整或色温调节等）的场景。
 *
 * @param filter [in] 滤镜指针，需要通过OH_Filter_CreateEffect创建并添加滤镜效果。不能为NULL。
 * @param matrix [in] 用来创建滤镜的自定义矩阵{@link OH_Filter_ColorMatrix}。不能为NULL。
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} 操作成功则返回EFFECT_SUCCESS。</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} 当filter或matrix为空指针时，返回EFFECT_BAD_PARAMETER。</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_SetColorMatrix(OH_Filter* filter, OH_Filter_ColorMatrix* matrix);

/**
 * @brief 获取滤镜生成的位图。
 *
 * @param filter [in] 用来创建位图的滤镜指针，需要通过OH_Filter_CreateEffect创建并添加滤镜效果。不能为NULL。
 * @param pixelmap [out] 用来接收位图的二级指针。不能为NULL。
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} 操作成功则返回EFFECT_SUCCESS。</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} 当filter或pixelmap为空指针时，返回EFFECT_BAD_PARAMETER。</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_GetEffectPixelMap(OH_Filter* filter, OH_PixelmapNative** pixelmap);

#ifdef __cplusplus
}
#endif

/** @} */
#endif