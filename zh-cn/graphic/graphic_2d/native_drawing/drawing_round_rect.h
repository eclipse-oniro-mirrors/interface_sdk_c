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
 * @file drawing_round_rect.h
 *
 * @brief This file declares the functions related to the rounded rectangle in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_ROUND_RECT_H
#define C_INCLUDE_DRAWING_ROUND_RECT_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于描述圆角位置的枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 左上角圆角位置。
     */
    CORNER_POS_TOP_LEFT,
    /**
     * 右上角圆角位置。
     */
    CORNER_POS_TOP_RIGHT,
    /**
     * 右下角圆角位置。
     */
    CORNER_POS_BOTTOM_RIGHT,
    /**
     * 左下角圆角位置。
     */
    CORNER_POS_BOTTOM_LEFT,
} OH_Drawing_CornerPos;

/**
 * @brief 用于创建一个圆角矩形对象。本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * rect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param rect 指向矩形对象的指针。
 * @param xRad X轴上的圆角半径，小于或等于0时无效。
 * @param yRad Y轴上的圆角半径，小于或等于0时无效。
 * @return 函数会返回一个指针，指针指向创建的圆角矩形对象。
 * @since 11
 * @version 1.0
 */
OH_Drawing_RoundRect* OH_Drawing_RoundRectCreate(const OH_Drawing_Rect* rect, float xRad, float yRad);

/**
 * @brief 用于创建圆角矩形的拷贝。
 *
 * @param roundRect 指向用于拷贝的圆角矩形对象{@link OH_Drawing_RoundRect}的指针。
 * @return 函数会返回一个指针，指针指向创建的新圆角矩形对象。
 * @since 20
 * @version 1.0
 */
OH_Drawing_RoundRect* OH_Drawing_RoundRectCopy(const OH_Drawing_RoundRect* roundRect);

/**
 * @brief 用于设置圆角矩形中指定圆角位置的圆角半径。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * roundRect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param roundRect 指向圆角矩形对象的指针。
 * @param pos 圆角位置的枚举，支持类型可见{@link OH_Drawing_CornerPos}。
 * @param radii 圆角半径结构体OH_Drawing_Corner_Radii，其中包含x轴方向和y轴方向上的半径，半径小于等于0时无效。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_RoundRectSetCorner(OH_Drawing_RoundRect* roundRect,
    OH_Drawing_CornerPos pos, OH_Drawing_Corner_Radii radii);

/**
 * @brief 用于获取圆角矩形中指定圆角位置的圆角半径。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * roundRect为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param roundRect 指向圆角矩形对象的指针。
 * @param pos 圆角位置的枚举，支持类型可见{@link OH_Drawing_CornerPos}。
 * @return 返回指定圆角位置的圆角半径结构体OH_Drawing_Corner_Radii，其中包含x轴方向和y轴方向上的半径。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Corner_Radii OH_Drawing_RoundRectGetCorner(OH_Drawing_RoundRect* roundRect, OH_Drawing_CornerPos pos);

/**
 * @brief 用于销毁圆角矩形对象并回收该对象占用的内存。
 *
 * @param roundRect 指向圆角矩形对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_RoundRectDestroy(OH_Drawing_RoundRect* roundRect);

/**
 * @brief 用于将圆角矩形沿x轴方向和y轴方向平移指定距离。
 *
 * @param roundRect 指向圆角矩形对象{@link OH_Drawing_Point2D}的指针。
 * @param dx x轴方向偏移量。
 * @param dy y轴方向偏移量。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数roundRect为空。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_RoundRectOffset(OH_Drawing_RoundRect* roundRect, float dx, float dy);
#ifdef __cplusplus
}
#endif
/** @} */
#endif