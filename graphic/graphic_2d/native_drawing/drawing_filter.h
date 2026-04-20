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
 * @file drawing_filter.h
 *
 * @brief This file declares the functions related to the filter in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_FILTER_H
#define C_INCLUDE_DRAWING_FILTER_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an **OH_Drawing_Filter** object.
 *
 * @return Returns the pointer to the <b>OH_Drawing_Filter</b> object created.
 * @since 11
 * @version 1.0
 */
OH_Drawing_Filter* OH_Drawing_FilterCreate(void);

/**
 * @brief Sets an **OH_Drawing_ImageFilter** object for an **OH_Drawing_Filter** object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **filter** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param filter Pointer to an {@link OH_Drawing_Filter} object.
 * @param imageFilter Pointer to an {@link OH_Drawing_ImageFilter} object. If NULL is passed in, the image filter
 * effect of the object will be cleared.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FilterSetImageFilter(OH_Drawing_Filter* filter, OH_Drawing_ImageFilter* imageFilter);

/**
 * @brief Sets an **OH_Drawing_MaskFilter** object for an **OH_Drawing_Filter** object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **filter** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param filter Pointer to an {@link OH_Drawing_Filter} object.
 * @param maskFilter Pointer to an {@link OH_Drawing_ColorFilter} object. If NULL is passed in, the mask filter effect
 * of the object will be cleared.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_FilterSetMaskFilter(OH_Drawing_Filter* filter, OH_Drawing_MaskFilter* maskFilter);

/**
 * @brief Sets an **OH_Drawing_ColorFilter** object for an **OH_Drawing_Filter** object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **filter** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param filter Pointer to an {@link OH_Drawing_Filter} object.
 * @param colorFilter Pointer to an {@link OH_Drawing_ColorFilter} object. If NULL is passed in, the color filter
 * effect of the object will be cleared.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_FilterSetColorFilter(OH_Drawing_Filter* filter, OH_Drawing_ColorFilter* colorFilter);

/**
 * @brief Obtains an **OH_Drawing_ColorFilter** object from an **OH_Drawing_Filter** object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If either **filter** or **colorFilter** is NULL, **OH_DRAWING_ERROR_INVALID_PARAMETER** is returned.
 *
 * @param filter Pointer to an {@link OH_Drawing_Filter} object.
 * @param colorFilter Pointer to an {@link OH_Drawing_ColorFilter} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FilterGetColorFilter(OH_Drawing_Filter* filter, OH_Drawing_ColorFilter* colorFilter);

/**
 * @brief Destroys an **OH_Drawing_Filter** object and reclaims the memory occupied by the object.
 *
 * @param filter Pointer to an {@link OH_Drawing_Filter} object.
 * @since 11
 * @version 1.0
 */
void OH_Drawing_FilterDestroy(OH_Drawing_Filter* filter);

#ifdef __cplusplus
}
#endif
/** @} */
#endif