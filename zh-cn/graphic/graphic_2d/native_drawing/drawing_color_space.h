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
 * @file drawing_color_space.h
 *
 * @brief This file declares the functions related to the color space in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_COLOR_SPACE_H
#define C_INCLUDE_DRAWING_COLOR_SPACE_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建一个标准颜色空间。
 *
 * @return 函数返回一个指针，指针指向创建的颜色空间对象{@link OH_Drawing_ColorSpace}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ColorSpace* OH_Drawing_ColorSpaceCreateSrgb(void);

/**
 * @brief 创建一个Gamma 1.0空间上的颜色空间。
 *
 * @return 函数返回一个指针，指针指向创建的颜色空间对象{@link OH_Drawing_ColorSpace}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ColorSpace* OH_Drawing_ColorSpaceCreateSrgbLinear(void);

/**
 * @brief 销毁颜色空间对象，并回收该对象占用的内存。
 *
 * @param colorSpace 指向颜色空间对象{@link OH_Drawing_ColorSpace}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ColorSpaceDestroy(OH_Drawing_ColorSpace* colorSpace);

#ifdef __cplusplus
}
#endif
/** @} */
#endif