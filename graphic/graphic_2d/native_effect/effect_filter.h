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
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 12
 */

/**
 * @file effect_filter.h
 *
 * @brief This file declares the APIs of an image effect filter.
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
 * @brief Creates an **OH_Filter** object.
 *
 * @param pixelmap [in] Pointer to the PixelMap.
 * @param filter [out] Double pointer to the filter created.
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
 * @param filter [in] Pointer to the filter.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter is NULL.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Release(OH_Filter* filter);

/**
 * @brief Creates the frosted glass effect and adds it to a filter.
 *
 * @param filter [in] Pointer to the filter.
 * @param radius [in] Blur radius of the frosted glass effect, in px.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter is NULL.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Blur(OH_Filter* filter, float radius);

/**
 * @brief Creates the frosted glass effect and adds it to a filter. It supports the tiling mode of the shader effect.
 *
 * @param filter [in] Pointer to the filter.
 * @param radius [in] Blur radius of the frosted glass effect, in px.
 * @param tileMode [in] Tile mode of the shader effect. For details about the available options,
 *     see {@link EffectTileMode}.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter is NULL.</li>
 *         </ul>
 * @since 14
 */
EffectErrorCode OH_Filter_BlurWithTileMode(OH_Filter* filter, float radius, EffectTileMode tileMode);

/**
 * @brief Creates the brightening effect and adds it to a filter.
 *
 * @param filter [in] Pointer to the filter.
 * @param brightness [in] Brightness value of the brightening effect, ranging from 0 to 1.
 *     When the value is 0, the image brightness remains unchanged.
 *     When the value is 1, the image becomes fully brightened.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter is NULL.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Brighten(OH_Filter* filter, float brightness);

/**
 * @brief Creates the grayscale effect and adds it to a filter.
 *
 * @param filter [in] Pointer to the filter.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter is NULL.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_GrayScale(OH_Filter* filter);

/**
 * @brief Creates the inverted color effect and adds it to a filter.
 *
 * @param filter [in] Pointer to the filter.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter is NULL.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Invert(OH_Filter* filter);

/**
 * @brief Creates a custom effect through a matrix and adds it to a filter.
 *
 * @param filter [in] Pointer to the filter.
 * @param matrix [in] Custom {@link OH_Filter_ColorMatrix} used to create the filter.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter or matrix is NULL.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_SetColorMatrix(OH_Filter* filter, OH_Filter_ColorMatrix* matrix);

/**
 * @brief Obtains the PixelMap with the filter effect.
 *
 * @param filter [in] Pointer to the filter.
 * @param pixelmap [out] Double pointer to the PixelMap obtained.
 * @return <ul>
 *         <li>{@link EffectErrorCode#EFFECT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link EffectErrorCode#EFFECT_BAD_PARAMETER} if filter or pixelmap is NULL.</li>
 *         </ul>
 * @release pixelmap_native/OH_PixelmapNative_Release {pixelmap}
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_GetEffectPixelMap(OH_Filter* filter, OH_PixelmapNative** pixelmap);

#ifdef __cplusplus
}
#endif

/** @} */
#endif