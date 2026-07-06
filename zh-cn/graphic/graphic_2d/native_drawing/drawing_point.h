/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @file drawing_point.h
 *
 * @brief This file declares the functions related to the coordinate point in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_POINT_H
#define C_INCLUDE_DRAWING_POINT_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 用于创建一个坐标点对象。
 *
 * @param x X轴坐标。
 * @param y Y轴坐标。
 * @return 函数会返回一个指针，指针指向创建的坐标点对象。
 * @since 11
 * @version 1.0
 */
OH_Drawing_Point* OH_Drawing_PointCreate(float x, float y);

/**
 * @brief 用于获取点的x轴坐标。
 *
 * @param point 指向坐标点对象{@link OH_Drawing_Point}的指针。
 * @param x 表示点的x轴坐标。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数point或者x为空。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PointGetX(const OH_Drawing_Point* point, float* x);

/**
 * @brief 用于获取点的y轴坐标。
 *
 * @param point 指向坐标点对象{@link OH_Drawing_Point}的指针。
 * @param y 表示点的y轴坐标。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数point或者y为空。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PointGetY(const OH_Drawing_Point* point, float* y);

/**
 * @brief 用于设置点的x轴和y轴坐标。
 *
 * @param point 指向坐标点对象{@link OH_Drawing_Point}的指针。
 * @param x 表示点的x轴坐标。
 * @param y 表示点的y轴坐标。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数point为空。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PointSet(OH_Drawing_Point* point, float x, float y);

/**
 * @brief 对point对象的坐标取反。
 *
 * @param point 需要被操作的point对象指针。
 * @return 返回错误码。
 *  操作成功时，返回 {@link OH_DRAWING_SUCCESS}.
 *  Point对象指针为空时，返回 {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER}
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PointNegate(OH_Drawing_Point* point);

/**
 * @brief 对point对象的坐标分别偏移dx、dy。
 *
 * @param point 表示被操作的point对象指针。
 * @param dx 表示x轴方向的偏移量，单位为像素。
 * @param dy 表示y轴方向的偏移量，单位为像素。
 * @return 返回错误码。
 *  操作成功时，返回{@link OH_DRAWING_SUCCESS}.
 *  Point对象指针为空时，返回 {@link OH_DRAWING_ERROR_INCORRECT_PARAMETER}
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PointOffset(OH_Drawing_Point* point, float dx, float dy);

/**
 * @brief 用于销毁坐标点对象并回收该对象占有的内存。
 *
 * @param point 指向坐标点对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_PointDestroy(OH_Drawing_Point* point);

#ifdef __cplusplus
}
#endif
/** @} */
#endif