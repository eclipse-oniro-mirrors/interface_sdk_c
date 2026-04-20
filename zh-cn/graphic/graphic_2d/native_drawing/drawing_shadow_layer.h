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
 * @brief 创建一个阴影层对象。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * blurRadius小于等于0时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param blurRadius 表示阴影的半径，必须大于零。
 * @param x 表示x轴上的偏移点。
 * @param y 表示y轴上的偏移点。
 * @param color 表示阴影的颜色。
 * @return 返回创建的阴影层对象的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ShadowLayer* OH_Drawing_ShadowLayerCreate(float blurRadius, float x, float y, uint32_t color);

/**
 * @brief 销毁阴影层对象，并收回该对象占用的内存。
 *
 * @param shadowLayer 表示指向阴影层对象的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ShadowLayerDestroy(OH_Drawing_ShadowLayer* shadowLayer);

#ifdef __cplusplus
}
#endif
/** @} */
#endif