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
 * @brief Provides APIs for obtaining effect filter and information.
 *
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 12
 */

/**
 * @file effect_filter.h
 *
 * @brief This file declares the APIs of an image effect filter.
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
 * @brief 创建一个OH_Filter对象。
 *
 * @param pixelmap 创建滤镜的位图。
 * @param filter 用来接收滤镜的二级指针。
 * @return 返回结果参见状态码{@link EffectErrorCode}。
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_CreateEffect(OH_PixelmapNative* pixelmap, OH_Filter** filter);

/**
 * @brief 释放OH_Filter对象。
 *
 * @param filter 被释放的对象指针。
 * @return 返回结果参见状态码{@link EffectErrorCode}。
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Release(OH_Filter* filter);

/**
 * @brief 创建一个毛玻璃滤镜效果，然后添加到滤镜里面。
 *
 * @param filter 滤镜指针。
 * @param radius 毛玻璃效果的模糊半径，单位为像素。
 * @return 返回结果参见状态码{@link EffectErrorCode}。
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Blur(OH_Filter* filter, float radius);

/**
 * @brief 创建一个毛玻璃滤镜效果，然后添加到滤镜里面，支持着色器效果平铺模式选择。
 *
 * @param filter 滤镜指针。
 * @param radius 毛玻璃效果的模糊半径，单位为像素。
 * @param tileMode 着色器效果平铺模式，支持可选的具体模式可见{@link EffectTileMode}枚举。
 * @return 返回结果参见状态码{@link EffectErrorCode}。
 * 操作成功则返回EFFECT_SUCCESS。
 * 无效参数则返回EFFECT_BAD_PARAMETER。
 * @since 14
 */
EffectErrorCode OH_Filter_BlurWithTileMode(OH_Filter* filter, float radius, EffectTileMode tileMode);

/**
 * @brief 创建一个提亮效果并且添加到滤镜中。
 *
 * @param filter 滤镜指针。
 * @param brightness 提亮效果的亮度值，取值范围在0-1之间，取值为0时图像保持不变，取值为1时图像全白。
 * @return 返回结果参见状态码{@link EffectErrorCode}。
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Brighten(OH_Filter* filter, float brightness);

/**
 * @brief 创建一个灰度效果并且添加到滤镜中。
 *
 * @param filter 滤镜指针。
 * @return 返回结果参见状态码{@link EffectErrorCode}。
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_GrayScale(OH_Filter* filter);

/**
 * @brief 创建一个反色效果并且添加到滤镜中。
 *
 * @param filter 滤镜指针。
 * @return 返回结果参见状态码{@link EffectErrorCode}。
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Invert(OH_Filter* filter);

/**
 * @brief 通过矩阵创建一个自定义的效果并且添加到滤镜中。
 *
 * @param filter 滤镜指针。
 * @param matrix 用来创建滤镜的自定义矩阵{@link OH_Filter_ColorMatrix}。
 * @return 返回结果参见状态码{@link EffectErrorCode}。
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_SetColorMatrix(OH_Filter* filter, OH_Filter_ColorMatrix* matrix);

/**
 * @brief 获取滤镜生成的位图。
 *
 * @param filter 用来创建位图的滤镜指针。
 * @param pixelmap 用来接收位图的二级指针。
 * @return 返回结果参见状态码{@link EffectErrorCode}。
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_GetEffectPixelMap(OH_Filter* filter, OH_PixelmapNative** pixelmap);

#ifdef __cplusplus
}
#endif

/** @} */
#endif