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
 * @brief 声明由图像框架定义的像素图对象。
 *
 * @since 12
 * @version 1.0
 */
typedef struct NativePixelMap_ NativePixelMap_;

/**
 * @brief 声明由图像框架定义的像素图对象。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_PixelmapNative OH_PixelmapNative;

/**
 * @brief 从图像框架定义的像素图对象中获取本模块定义的像素图对象。对象使用完毕后，需调用{@link OH_Drawing_PixelMapDissolve}解除关系，否则会引发内存泄露问题。
 *
 * @param nativePixelMap 指向图像框架定义的像素图对象{@link NativePixelMap_}的指针。
 * @return 函数会返回一个指向本模块定义的像素图对象{@link OH_Drawing_PixelMap}的指针。如果对象返回NULL，表示创建失败；可能的原因是NativePixelMap_为NULL。
 * @since 12
 * @version 1.0
 */
OH_Drawing_PixelMap* OH_Drawing_PixelMapGetFromNativePixelMap(NativePixelMap_* nativePixelMap);

/**
 * @brief 从图像框架定义的像素图对象中获取本模块定义的像素图对象。对象使用完毕后，需调用{@link OH_Drawing_PixelMapDissolve}解除关系，否则会引发内存泄露问题。
 *
 * @param pixelmapNative 指向图像框架定义的像素图对象{@link OH_PixelmapNative}的指针。
 * @return 函数会返回一个指向本模块定义的像素图对象{@link OH_Drawing_PixelMap}的指针。如果对象返回NULL，表示创建失败；可能的原因是OH_PixelmapNative为NULL。
 * @since 12
 * @version 1.0
 */
OH_Drawing_PixelMap* OH_Drawing_PixelMapGetFromOhPixelMapNative(OH_PixelmapNative* pixelmapNative);

/**
 * @brief 解除本模块定义的像素图对象和图像框架定义的像素图对象之间的关系，该关系通过调用 {@link OH_Drawing_PixelMapGetFromNativePixelMap} 或
 * {@link OH_Drawing_PixelMapGetFromOhPixelMapNative}
 * 建立。
 *
 * @param pixelMap 指向像素图对象{@link OH_Drawing_PixelMap}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PixelMapDissolve(OH_Drawing_PixelMap* pixelMap);

#ifdef __cplusplus
}
#endif
/** @} */
#endif