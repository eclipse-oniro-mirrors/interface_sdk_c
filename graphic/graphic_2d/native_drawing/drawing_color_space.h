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
 * @brief Creates an sRGB color space.
 *
 * @return Returns a pointer to the {@link OH_Drawing_ColorSpace} object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ColorSpace* OH_Drawing_ColorSpaceCreateSrgb(void);

/**
 * @brief Creates an sRGB linear (Gamma 1.0) color space.
 *
 * @return Returns a pointer to the {@link OH_Drawing_ColorSpace} object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ColorSpace* OH_Drawing_ColorSpaceCreateSrgbLinear(void);

/**
 * @brief Destroys an **OH_Drawing_ColorSpace** object and reclaims the memory occupied by the object.
 *
 * @param colorSpace Pointer to an {@link OH_Drawing_ColorSpace} object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ColorSpaceDestroy(OH_Drawing_ColorSpace* colorSpace);

#ifdef __cplusplus
}
#endif
/** @} */
#endif