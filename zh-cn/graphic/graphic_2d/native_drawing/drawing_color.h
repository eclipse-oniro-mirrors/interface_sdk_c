/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
 * @file drawing_color.h
 *
 * @brief This file declares the functions related to the color in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_COLOR_H
#define C_INCLUDE_DRAWING_COLOR_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于将4个变量（分别描述透明度、红色、绿色和蓝色）转化为一个描述颜色的32位（ARGB）变量。
 *
 * @param alpha 描述透明度的变量, 变量范围是0x00~0xFF。
 * @param red 描述红色的变量, 变量范围是0x00~0xFF。
 * @param green 描述绿色的变量, 变量范围是0x00~0xFF。
 * @param blue 描述蓝色的变量, 变量范围是0x00~0xFF。
 * @return 函数返回一个描述颜色的32位（ARGB）变量。
 * @since 8
 * @version 1.0
 */
uint32_t OH_Drawing_ColorSetArgb(uint32_t alpha, uint32_t red, uint32_t green, uint32_t blue);

#ifdef __cplusplus
}
#endif
/** @} */
#endif