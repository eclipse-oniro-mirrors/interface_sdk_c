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
 * @brief Provides basic image processing capabilities, including brightness adjustment, blurring, and grayscale conversion of the current image. It is suitable for scenarios where image filter effects need to be quickly implemented within an app, such as image editing, photo beautification, and camera filters. This helps developers quickly implement image effect processing without focusing on the underlying algorithm implementation, reducing development complexity.
 *
 * @since 12
 */

/**
 * @file effect_filter.h
 *
 * @brief Declares the APIs for filter effects. It supports creating and managing various filter effects, including frosted glass blur, brightness adjustment, grayscale conversion, and color inversion. It also supports implementing rich image processing effects through custom matrices, applicable to scenarios such as image editing, photo beautification, and visual effects.
 *
 * You must call {@link OH_Filter_CreateEffect} and {@link OH_Filter_Release} in pairs to ensure that resources are properly released.
 * None of the APIs in this file support multi-threaded calls.
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
 * @brief Creates an **OH_Filter** object to apply various filter effects (such as blur, brightening, or grayscale) to an image, applicable to scenarios such as image editing, album apps, and video processing.
 *
 * @param pixelmap [in] The pixelmap object used as the source image for filter effect processing. Cannot be NULL.
 * @param filter [out] Double pointer used to receive the filter. Cannot be NULL.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if pixelmap or filter is NULL.</li>
 *         </ul>
 * @release effect_filter/OH_Filter_Release {filter}
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_CreateEffect(OH_PixelmapNative* pixelmap, OH_Filter** filter);

/**
 * @brief Releases an **OH_Filter** object.
 *
 * @param filter [in] Pointer to the filter. Cannot be NULL.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter is NULL.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Release(OH_Filter* filter);

/**
 * @brief Creates a frosted glass filter effect and adds it to a filter effect chain.
 *
 * @param filter [in] Filter pointer, which needs to be created through OH_Filter_CreateEffect. Cannot be NULL.
 * @param radius [in] Blur radius of the frosted glass effect. Value range: [0, +∞), in pixels. A value of 0 produces no blur effect; larger values produce stronger blur effects.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter is a null pointer or radius is less than 0.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Blur(OH_Filter* filter, float radius);

/**
 * @brief Creates a frosted glass filter effect and adds it to a filter effect chain. It supports selecting the shader effect tile mode.
 *
 * @param filter [in] Filter pointer, which needs to be created through OH_Filter_CreateEffect. Cannot be NULL.
 * @param radius [in] Blur radius of the frosted glass effect. Value range: [0, +∞), in pixels. No blur effect is produced when the parameter value is 0. The larger the value, the stronger the blur effect.
 * @param tileMode [in] Shader effect tile mode. Different modes determine different processing methods for image edge areas. For details about the available options, see {@link EffectTileMode}.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter is a null pointer or radius is less than 0.</li>
 *         </ul>
 * @since 14
 */
EffectErrorCode OH_Filter_BlurWithTileMode(OH_Filter* filter, float radius, EffectTileMode tileMode);

/**
 * @brief Creates a brightening effect and adds it to a filter effect chain.
 *
 * @param filter [in] Filter pointer, which needs to be created through OH_Filter_CreateEffect. Cannot be NULL.
 * @param brightness [in] Brightness value of the brightening effect. Value range: [0, 1]. The image remains unchanged when the value is 0, and becomes completely white when the value is 1.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter is a null pointer or brightness is outside the value range [0, 1].</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Brighten(OH_Filter* filter, float brightness);

/**
 * @brief Creates a grayscale effect and adds it to a filter effect chain.
 *
 * @param filter [in] Filter pointer, which needs to be created through OH_Filter_CreateEffect. Cannot be NULL.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter is NULL.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_GrayScale(OH_Filter* filter);

/**
 * @brief Creates an inverted color effect and adds it to a filter effect chain.
 *
 * @param filter [in] Filter pointer, which needs to be created through OH_Filter_CreateEffect. Cannot be NULL.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter is NULL.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Invert(OH_Filter* filter);

/**
 * @brief Creates a custom effect through a matrix and adds it to a filter effect chain, applicable to scenarios that require specific color transformation effects (such as color correction, hue adjustment, or color temperature adjustment).
 *
 * @param filter [in] Filter pointer, which needs to be created through OH_Filter_CreateEffect. Cannot be NULL.
 * @param matrix [in] Custom matrix used to create the filter. Cannot be NULL.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter or matrix is NULL.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_SetColorMatrix(OH_Filter* filter, OH_Filter_ColorMatrix* matrix);

/**
 * @brief Obtains the bitmap generated by the filter.
 *
 * @param filter [in] Filter pointer used to create a bitmap, which needs to be created through OH_Filter_CreateEffect. Cannot be NULL.
 * @param pixelmap [out] Double pointer used to receive the PixelMap. Cannot be NULL.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter or pixelmap is NULL.</li>
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