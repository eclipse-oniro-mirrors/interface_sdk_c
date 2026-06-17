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
 * @file drawing_shadow_layer.h
 *
 * @brief This file declares the functions related to the shadow in the drawing module.
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
 * @brief Creates an **OH_Drawing_ShadowLayer** object.
 * This API may return an error code. For details, call {@link OH_Drawing_ErrorCodeGet}.
 * If **blurRadius** is less than or equal to 0, **OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE** is returned.
 *
 * @param blurRadius Radius of the shadow layer. The value must be greater than 0.
 * @param x Offset on the X axis.
 * @param y Offset on the Y axis.
 * @param color Color of the shadow.
 * @return Returns the pointer to the **OH_Drawing_ShadowLayer** object created.
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShadowLayer* OH_Drawing_ShadowLayerCreate(float blurRadius, float x, float y, uint32_t color);

/**
 * @brief Destroys an **OH_Drawing_ShadowLayer** object and reclaims the memory occupied by the object.
 *
 * @param shadowLayer Pointer to the shadow layer.
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ShadowLayerDestroy(OH_Drawing_ShadowLayer* shadowLayer);

#ifdef __cplusplus
}
#endif
/** @} */
#endif