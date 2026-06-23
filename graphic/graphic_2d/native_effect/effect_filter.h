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
 * @param pixelmap Pointer to the PixelMap.
 * @param filter Double pointer to the filter created.
 * @return Returns a status code. For details, see {@link EffectErrorCode}.
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_CreateEffect(OH_PixelmapNative* pixelmap, OH_Filter** filter);

/**
 * @brief Releases an **OH_Filter** object.
 *
 * @param filter Pointer to the filter.
 * @return Returns a status code. For details, see {@link EffectErrorCode}.
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Release(OH_Filter* filter);

/**
 * @brief Creates the frosted glass effect and adds it to a filter.
 *
 * @param filter Pointer to the filter.
 * @param radius Blur radius of the frosted glass effect, in px.
 * @return Returns a status code. For details, see {@link EffectErrorCode}.
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Blur(OH_Filter* filter, float radius);

/**
 * @brief Creates the frosted glass effect and adds it to a filter. It supports the tiling mode of the shader effect.
 *
 * @param filter Pointer to the filter.
 * @param radius Blur radius of the frosted glass effect, in px.
 * @param tileMode Tile mode of the shader effect. For details about the available options, see {@link EffectTileMode}.
 * @return Returns a status code. For details, see {@link EffectErrorCode}.
 * If the operation is successful, **EFFECT_SUCCESS** is returned.
 * If a parameter is invalid, **EFFECT_BAD_PARAMETER** is returned.
 * @since 14
 */
EffectErrorCode OH_Filter_BlurWithTileMode(OH_Filter* filter, float radius, EffectTileMode tileMode);

/**
 * @brief Creates the brightening effect and adds it to a filter.
 *
 * @param filter Pointer to the filter.
 * @param brightness Brightness value of the brightening effect, ranging from 0 to 1. When the value is 0, the image
 * brightness remains unchanged. When the value is 1, the image becomes fully brightened.
 * @return Returns a status code. For details, see {@link EffectErrorCode}.
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Brighten(OH_Filter* filter, float brightness);

/**
 * @brief Creates the grayscale effect and adds it to a filter.
 *
 * @param filter Pointer to the filter.
 * @return Returns a status code. For details, see {@link EffectErrorCode}.
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_GrayScale(OH_Filter* filter);

/**
 * @brief Creates the inverted color effect and adds it to a filter.
 *
 * @param filter Pointer to the filter.
 * @return Returns a status code. For details, see {@link EffectErrorCode}.
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_Invert(OH_Filter* filter);

/**
 * @brief Creates a custom effect through a matrix and adds it to a filter.
 *
 * @param filter Pointer to the filter.
 * @param matrix Custom {@link OH_Filter_ColorMatrix} used to create the filter.
 * @return Returns a status code. For details, see {@link EffectErrorCode}.
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_SetColorMatrix(OH_Filter* filter, OH_Filter_ColorMatrix* matrix);

/**
 * @brief Obtains the PixelMap with the filter effect.
 *
 * @param filter Pointer to the filter.
 * @param pixelmap Double pointer to the PixelMap obtained.
 * @return Returns a status code. For details, see {@link EffectErrorCode}.
 * @since 12
 * @version 1.0
 */
EffectErrorCode OH_Filter_GetEffectPixelMap(OH_Filter* filter, OH_PixelmapNative** pixelmap);

#ifdef __cplusplus
}
#endif

/** @} */
#endif