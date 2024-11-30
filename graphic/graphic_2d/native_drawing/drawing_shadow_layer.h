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
 * @addtogroup Drawing
 * @{
 *
 * @brief Provides functions such as 2D graphics rendering, text drawing, and image display.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 *
 * @since 8
 * @version 1.0
 */

/**
 * @file drawing_shadow_layer.h
 *
 * @brief Declares functions related to the <b>ShadowLayer</b> object in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_SHADOW_LAYER_H
#define C_INCLUDE_DRAWING_SHADOW_LAYER_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an <b>OH_Drawing_ShadowLayer</b> object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param blurRadius Indicates the blur radius of the shadow.
 * @param x Indicates the offset point on x-axis.
 * @param y Indicates the offset point on y-axis.
 * @param color Indicates the shadow color.
 * @return Returns the pointer to the <b>OH_Drawing_ShadowLayer</b> object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShadowLayer* OH_Drawing_ShadowLayerCreate(float blurRadius, float x, float y, uint32_t color);

/**
 * @brief Destroys an <b>OH_Drawing_ShadowLayer</b> object and reclaims the memory occupied by the object.
 *
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @param shadowLayer Indicates the pointer to an <b>OH_Drawing_ShadowLayer</b> object.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ShadowLayerDestroy(OH_Drawing_ShadowLayer* shadowLayer);

#ifdef __cplusplus
}
#endif
/** @} */
#endif
