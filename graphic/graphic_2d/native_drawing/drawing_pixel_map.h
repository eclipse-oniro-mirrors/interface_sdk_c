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
 * @file drawing_pixel_map.h
 *
 * @brief This file declares the functions related to the pixel map in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_PIXEL_MAP_H
#define C_INCLUDE_DRAWING_PIXEL_MAP_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines a pixel map defined by the image framework.
 *
 * @since 12
 * @version 1.0
 */
typedef struct NativePixelMap_ NativePixelMap_;

/**
 * @brief Defines a pixel map defined by the image framework.
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_PixelmapNative OH_PixelmapNative;

/**
 * @brief Obtains the pixel map defined by this module from a pixel map defined by the image framework.
 *
 * @param nativePixelMap Pointer to a {@link NativePixelMap_} object, which is the pixel map defined by the image
 * framework.
 * @return Returns the pointer to an {@link OH_Drawing_PixelMap} object, which is the pixel map defined by this module.
 * If NULL is returned, the creation fails. The possible failure cause is that **NativePixelMap_** is NULL.
 * @since 12
 * @version 1.0
 */
OH_Drawing_PixelMap* OH_Drawing_PixelMapGetFromNativePixelMap(NativePixelMap_* nativePixelMap);

/**
 * @brief Obtains the pixel map defined by this module from a pixel map defined by the image framework.
 *
 * @param pixelmapNative Pointer to a {@link OH_PixelmapNative} object, which is the pixel map defined by the image
 * framework.
 * @return Returns the pointer to an {@link OH_Drawing_PixelMap} object, which is the pixel map defined by this module.
 * If NULL is returned, the creation fails. The possible failure cause is that **OH_PixelmapNative** is NULL.
 * @since 12
 * @version 1.0
 */
OH_Drawing_PixelMap* OH_Drawing_PixelMapGetFromOhPixelMapNative(OH_PixelmapNative* pixelmapNative);

/**
 * @brief Removes the relationship between a pixel map defined by this module and a pixel map defined by the image
 * framework. The relationship is established by calling  {@link OH_Drawing_PixelMapGetFromNativePixelMap}  or
 * {@link OH_Drawing_PixelMapGetFromOhPixelMapNative}
 * .
 *
 * @param pixelMap Pointer to an {@link OH_Drawing_PixelMap} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PixelMapDissolve(OH_Drawing_PixelMap* pixelMap);

#ifdef __cplusplus
}
#endif
/** @} */
#endif