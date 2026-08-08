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
 * @brief 文件中定义了与坐标点相关的功能函数，支持创建、获取、设置、取反、偏移及销毁坐标点对象等操作，
 * 便于在2D图形绘制中对坐标点进行管理与变换。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
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
 * @brief 创建一个坐标点对象。当此坐标点对象不再需要时，必须调用{@link OH_Drawing_PointDestroy}销毁并回收内存。
 *
 * @param x 表示坐标点的x轴坐标，单位为物理像素px。
 * @param y 表示坐标点的y轴坐标，单位为物理像素px。
 * @return 函数返回指向创建的坐标点对象的指针。
 * @since 11
 * @version 1.0
 */
OH_Drawing_Point* OH_Drawing_PointCreate(float x, float y);

/**
 * @brief 获取坐标点的x轴坐标值。
 *
 * @param point 指向坐标点对象{@link OH_Drawing_Point}的指针。
 * @param x 输出参数，用于接收坐标点的x轴坐标值，单位为物理像素px。
 * @return 函数返回执行错误码。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数point或者x为空。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PointGetX(const OH_Drawing_Point* point, float* x);

/**
 * @brief 获取坐标点的y轴坐标值。
 *
 * @param point 指向坐标点对象{@link OH_Drawing_Point}的指针。
 * @param y 输出参数，用于接收坐标点的y轴坐标值，单位为物理像素px。
 * @return 函数返回执行错误码。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数point或者y为空。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PointGetY(const OH_Drawing_Point* point, float* y);

/**
 * @brief 设置坐标点的x轴和y轴坐标。
 *
 * @param point 指向坐标点对象{@link OH_Drawing_Point}的指针。
 * @param x 表示坐标点的x轴坐标，单位为物理像素px。
 * @param y 表示坐标点的y轴坐标，单位为物理像素px。
 * @return 函数返回执行错误码。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数point为空。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PointSet(OH_Drawing_Point* point, float x, float y);

/**
 * @brief 对坐标点的x轴和y轴坐标取反。
 *
 * @param point 指向坐标点对象{@link OH_Drawing_Point}的指针。
 * @return 函数返回执行错误码。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数point为空。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PointNegate(OH_Drawing_Point* point);

/**
 * @brief 将坐标点沿x轴和y轴方向偏移指定距离。
 *
 * @param point 指向坐标点对象{@link OH_Drawing_Point}的指针。
 * @param dx 表示在x轴上的偏移量，单位为物理像素px。正数表示往x轴正方向平移，负数表示往x轴负方向平移。
 * @param dy 表示在y轴上的偏移量，单位为物理像素px。正数表示往y轴正方向平移，负数表示往y轴负方向平移。
 * @return 函数返回执行错误码。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示参数point为空。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PointOffset(OH_Drawing_Point* point, float dx, float dy);

/**
 * @brief 销毁坐标点对象并回收该对象占用的内存。需在{@link OH_Drawing_PointCreate}创建对象后且该对象不再使用时调用。
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