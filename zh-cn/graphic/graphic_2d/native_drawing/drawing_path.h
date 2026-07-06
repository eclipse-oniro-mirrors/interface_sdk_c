/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_path.h
 *
 * @brief This file declares the functions related to the path in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_PATH_H
#define C_INCLUDE_DRAWING_PATH_H

#include "drawing_error_code.h"
#include "drawing_types.h"
#include "drawing_path_iterator.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 添加闭合轮廓方向枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 顺时针方向添加闭合轮廓。
     */
    PATH_DIRECTION_CW,
    /**
     * 逆时针方向添加闭合轮廓。
     */
    PATH_DIRECTION_CCW,
} OH_Drawing_PathDirection;

/**
 * @brief 定义路径的填充类型枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 绘制区域中的任意一点，向任意方向射出一条射线，对于射线和路径的所有交点，初始计数为0，<br>遇到每个顺时针的交点（路径从射线的左边向右穿过），计数加1，遇到每个逆时针的交点（路径从射线的右边向左穿过），计数减1，
     * 若最终的计数结果不为0，则认为这个点在路径内部，需要被涂色；若计数为0则不被涂色。
     */
    PATH_FILL_TYPE_WINDING,
    /**
     * 绘制区域中的任意一点，向任意方向射出一条射线，若这条射线和路径相交的次数是奇数，则这个点被认为在路径内部，需要被涂色；若是偶数则不被涂色。
     */
    PATH_FILL_TYPE_EVEN_ODD,
    /**
     * PATH_FILL_TYPE_WINDING 涂色规则取反。
     */
    PATH_FILL_TYPE_INVERSE_WINDING,
    /**
     * PATH_FILL_TYPE_EVEN_ODD 涂色规则取反。
     */
    PATH_FILL_TYPE_INVERSE_EVEN_ODD,
} OH_Drawing_PathFillType;

/**
 * @brief 用于指定路径添加模式的枚举类型。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 以追加的方式添加路径。
     */
    PATH_ADD_MODE_APPEND,
    /**
     * 如果之前的路径未闭合，则添加直线闭合路径。
     */
    PATH_ADD_MODE_EXTEND,
} OH_Drawing_PathAddMode;

/**
 * @brief 路径操作类型枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 差集操作。
     */
    PATH_OP_MODE_DIFFERENCE,
    /**
     * 交集操作。
     */
    PATH_OP_MODE_INTERSECT,
    /**
     * 并集操作。
     */
    PATH_OP_MODE_UNION,
    /**
     * 异或操作。
     */
    PATH_OP_MODE_XOR,
    /**
     * 反向差集操作。
     */
    PATH_OP_MODE_REVERSE_DIFFERENCE,
} OH_Drawing_PathOpMode;

/**
 * @brief 路径测量获取相应矩阵信息维度枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 获取位置信息对应的矩阵。
     */
    GET_POSITION_MATRIX,
    /**
     * 获取切线信息对应的矩阵。
     */
    GET_TANGENT_MATRIX,
    /**
     * 获取位置和切线信息对应的矩阵。
     */
    GET_POSITION_AND_TANGENT_MATRIX,
} OH_Drawing_PathMeasureMatrixFlags;

/**
 * @brief 用于创建一个路径对象。
 *
 * @return 函数会返回一个指针，指针指向创建的路径对象。
 * @since 8
 * @version 1.0
 */
OH_Drawing_Path* OH_Drawing_PathCreate(void);

/**
 * @brief 创建一个路径对象副本{@link OH_Drawing_Path}，用于拷贝一个已有路径对象。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @return 函数返回一个指针，指针指向创建的路径对象副本{@link OH_Drawing_Path}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Path* OH_Drawing_PathCopy(OH_Drawing_Path* path);

/**
 * @brief 用于销毁路径对象并回收该对象占有的内存。
 *
 * @param path 指向路径对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathDestroy(OH_Drawing_Path* path);

/**
 * @brief 将一个路径对象设置成当前的路径对象。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param other 用于设置的路径对象{@link OH_Drawing_Path}的指针。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数path或者other为空。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathSetPath(OH_Drawing_Path* path, OH_Drawing_Path* other);

/**
 * @brief 判断一个路径对象是否为空。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param isEmpty 表示路径对象是否为空。true表示路径对象为空，false表示路径对象不为空。作为出参使用。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数path或者isEmpty为空。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathIsEmpty(OH_Drawing_Path* path, bool* isEmpty);

/**
 * @brief 判断路径对象是否构成一个矩形。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针，作为出参使用，可以为空。
 * @param isRect 表示路径是否构成矩形。true表示构成矩形，false表示不构成矩形。作为出参使用。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数path或者isRect为空。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathIsRect(OH_Drawing_Path* path, OH_Drawing_Rect* rect, bool* isRect);

/**
 * @brief 用于设置自定义路径的起始点位置。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象的指针。
 * @param x 起始点的横坐标。
 * @param y 起始点的纵坐标。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathMoveTo(OH_Drawing_Path* path, float x, float y);

/**
 * @brief 用于添加一条从路径的最后点位置（若路径没有内容则默认为 (0, 0)）到目标点位置的线段。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象的指针。
 * @param x 目标点的横坐标。
 * @param y 目标点的纵坐标。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathLineTo(OH_Drawing_Path* path, float x, float y);

/**
 * @brief 用于给路径添加一段弧线，绘制弧线的方式为角度弧，该方式首先会指定一个矩形边框，
 * 矩形边框的内切椭圆将会被用来截取弧线，然后会指定一个起始角度和扫描度数，
 * 从起始角度扫描截取的椭圆周长一部分即为绘制的弧线。若路径有内容则会默认添加一条从路径的最后点位置到弧线起始点位置的线段。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象的指针。
 * @param x1 包围椭圆的矩形左上角点位置的横坐标。
 * @param y1 包围椭圆的矩形左上角点位置的纵坐标。
 * @param x2 包围椭圆的矩形右下角点位置的横坐标。
 * @param y2 包围椭圆的矩形右下角点位置的纵坐标。
 * @param startDeg 起始的角度。角度的起始方向（0°）为x轴正方向。
 * @param sweepDeg 扫描的度数，为正数时顺时针扫描，为负数时逆时针扫描。实际扫描的度数为该入参对360取模的结果。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathArcTo(OH_Drawing_Path* path,
    float x1, float y1, float x2, float y2, float startDeg, float sweepDeg);

/**
 * @brief 用于添加一条从路径最后点位置（若路径没有内容则默认为 (0, 0)）到目标点位置的二阶贝塞尔曲线。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象的指针。
 * @param ctrlX 控制点位置的横坐标。
 * @param ctrlY 控制点位置的纵坐标。
 * @param endX 目标点位置的横坐标。
 * @param endY 目标点位置的纵坐标。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathQuadTo(OH_Drawing_Path* path, float ctrlX, float ctrlY, float endX, float endY);

/**
 * @brief 在当前路径上添加一条路径终点（若路径没有内容则默认为 (0, 0)）到目标点位置的圆锥曲线段，其控制点为 (ctrlX, ctrlY)，结束点为 (endX, endY)。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param ctrlX 控制点位置的横坐标。
 * @param ctrlY 控制点位置的纵坐标。
 * @param endX 结束点位置的横坐标。
 * @param endY 结束点位置的纵坐标。
 * @param weight 表示曲线的权重，决定了曲线的形状，越大越接近控制点。
 * 若小于等于0则等同于使用{@link OH_Drawing_PathLineTo}添加一条到结束点的线段，
 * 若为1则等同于{@link OH_Drawing_PathQuadTo}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathConicTo(OH_Drawing_Path* path, float ctrlX, float ctrlY, float endX, float endY, float weight);

/**
 * @brief 用于添加一条从路径最后点位置（若路径没有内容则默认为 (0, 0)）到目标点位置的三阶贝塞尔圆滑曲线。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象的指针。
 * @param ctrlX1 第一个控制点位置的横坐标。
 * @param ctrlY1 第一个控制点位置的纵坐标。
 * @param ctrlX2 第二个控制点位置的横坐标。
 * @param ctrlY2 第二个控制点位置的纵坐标。
 * @param endX 目标点位置的横坐标。
 * @param endY 目标点位置的纵坐标。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathCubicTo(
    OH_Drawing_Path* path, float ctrlX1, float ctrlY1, float ctrlX2, float ctrlY2, float endX, float endY);

/**
 * @brief 用于设置一个相对于当前路径终点（若路径没有内容则默认为 (0, 0)）的路径起始点位置。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param x 相对于当前路径终点的x轴偏移量，正数往x轴正方向偏移，负数往x轴负方向偏移。
 * @param y 相对于当前路径终点的y轴偏移量，正数往y轴正方向偏移，负数往y轴负方向偏移。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathRMoveTo(OH_Drawing_Path* path, float x, float y);

/**
 * @brief 使用相对位置在当前路径上添加一条当前路径终点（若路径没有内容则默认为 (0, 0)）到目标点位置的线段。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param x 相对于当前路径终点的x轴偏移量，用于指定目标点的横坐标。
 * @param y 相对于当前路径终点的y轴偏移量，用于指定目标点的纵坐标。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathRLineTo(OH_Drawing_Path* path, float x, float y);

/**
 * @brief 使用相对位置在当前路径上添加一条当前路径终点（若路径没有内容则默认为 (0, 0)）到目标点位置的二阶贝塞尔曲线。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param ctrlX 相对于路径终点的x轴偏移量，用于指定控制点的横坐标。
 * @param ctrlY 相对于路径终点的y轴偏移量，用于指定控制点的纵坐标。
 * @param endX 相对于路径终点的x轴偏移量，用于指定目标点的横坐标。
 * @param endY 相对于路径终点的y轴偏移量，用于指定目标点的纵坐标。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathRQuadTo(OH_Drawing_Path* path, float ctrlX, float ctrlY, float endX, float endY);

/**
 * @brief 使用相对位置在当前路径上添加一条路径终点（若路径没有内容则默认为 (0, 0)）到目标点位置的圆锥曲线段。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param ctrlX 相对于路径终点的x轴偏移量，用于指定控制点的横坐标。
 * @param ctrlY 相对于路径终点的y轴偏移量，用于指定控制点的纵坐标。
 * @param endX 相对于路径终点的x轴偏移量，用于指定目标点的横坐标。
 * @param endY 相对于路径终点的y轴偏移量，用于指定目标点的纵坐标。
 * @param weight 表示曲线的权重，决定了曲线的形状，越大越接近控制点。
 * 若小于等于0则等同于使用{@link OH_Drawing_PathRLineTo}添加一条到结束点的线段，
 * 若为1则等同于{@link OH_Drawing_PathRQuadTo}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathRConicTo(OH_Drawing_Path* path, float ctrlX, float ctrlY, float endX, float endY, float weight);

/**
 * @brief 使用相对位置在当前路径上添加一条当前路径终点（若路径没有内容则默认为 (0, 0)）到目标点位置的三阶贝塞尔圆滑曲线。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param ctrlX1 相对于路径终点的x轴偏移量，用于指定第一个控制点的横坐标。
 * @param ctrlY1 相对于路径终点的y轴偏移量，用于指定第一个控制点的纵坐标。
 * @param ctrlX2 相对于路径终点的x轴偏移量，用于指定第二个控制点的横坐标。
 * @param ctrlY2 相对于路径终点的y轴偏移量，用于指定第二个控制点的纵坐标。
 * @param endX 相对于路径终点的x轴偏移量，用于指定目标点的横坐标。
 * @param endY 相对于路径终点的y轴偏移量，用于指定目标点的纵坐标。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathRCubicTo(OH_Drawing_Path* path, float ctrlX1, float ctrlY1, float ctrlX2, float ctrlY2,
    float endX, float endY);

/**
 * @brief 按指定方向，将矩形添加到路径中，添加的路径的起始点为矩形左上角。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * pathDirection不在枚举范围内返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param left 矩形左上角的x轴坐标。
 * @param top 矩形左上角的y轴坐标。
 * @param right 矩形右下角的x轴坐标。
 * @param bottom 矩形右下角的y轴坐标。
 * @param pathDirection 路径方向{@link OH_Drawing_PathDirection}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddRect(OH_Drawing_Path* path, float left, float top, float right, float bottom,
    OH_Drawing_PathDirection pathDirection);

/**
 * @brief 按指定方向，向路径添加矩形轮廓。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、rect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * pathDirection不在枚举范围内返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @param pathDirection Indicates the path direction.
 * @param start 起始点的位置，表示从矩形的哪个角开始绘制路径。0：左上角，1：右上角，2：右下角，3：左下角。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddRectWithInitialCorner(OH_Drawing_Path* path, const OH_Drawing_Rect* rect,
    OH_Drawing_PathDirection pathDirection, uint32_t start);

/**
 * @brief 按指定方向，向路径添加圆角矩形轮廓。路径添加方向为顺时针时，起始点位于圆角矩形左下方圆角与左边界的交点；路径添加方向为逆时针时，起始点位于圆角矩形左上方圆角与左边界的交点。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、roundRect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * pathDirection不在枚举范围内返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param roundRect 指向圆角矩形对象{@link OH_Drawing_RoundRect}的指针。
 * @param pathDirection 路径方向{@link OH_Drawing_PathDirection}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddRoundRect(OH_Drawing_Path* path,
    const OH_Drawing_RoundRect* roundRect, OH_Drawing_PathDirection pathDirection);

/**
 * @brief 将椭圆添加到路径中，其中矩形对象作为椭圆的外切矩形区域，绘制方向用来指定绘制时是顺时针或者逆时针方向。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、rect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * pathDirection不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @param start 表示椭圆初始点的索引。
 * @param pathDirection 表示绘制方向{@link OH_Drawing_PathDirection}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddOvalWithInitialPoint(OH_Drawing_Path* path, const OH_Drawing_Rect* rect,
    uint32_t start, OH_Drawing_PathDirection pathDirection);

/**
 * @brief 按指定方向，向路径添加椭圆。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、rect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * pathDirection不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @param pathDirection 路径方向{@link OH_Drawing_PathDirection}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddOval(OH_Drawing_Path* path,
    const OH_Drawing_Rect* rect, OH_Drawing_PathDirection pathDirection);

/**
 * @brief 将圆弧添加到路径中，作为新轮廓的起点。从起始角度到扫描角度添加弧，添加的弧是矩形内切椭圆的一部分，如果扫描角度<= -360°，或>= 360°，并且起始角度对90取模接近于0，则添加椭圆而不是弧。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、rect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @param startAngle 弧的起始角度，单位为度。
 * @param sweepAngle 扫描的度数，为正数时顺时针扫描，为负数时逆时针扫描。实际扫描的度数为该入参对360取模的结果。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddArc(OH_Drawing_Path* path, const OH_Drawing_Rect* rect, float startAngle, float sweepAngle);

/**
 * @brief 将源路径矩阵变换后，添加到当前路径中。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、src任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向当前路径对象{@link OH_Drawing_Path}的指针。
 * @param src 指向源路径对象{@link OH_Drawing_Path}的指针。
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针，为NULL时表示单位矩阵。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddPath(OH_Drawing_Path* path, const OH_Drawing_Path* src, const OH_Drawing_Matrix* matrix);

/**
 * @brief 将源路径矩阵变换后，以规定模式添加到当前路径中。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、src任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * pathAddMode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param path 指向当前路径对象{@link OH_Drawing_Path}的指针。
 * @param src 指向源路径对象{@link OH_Drawing_Path}的指针。
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针，为NULL表示单位矩阵。
 * @param pathAddMode 路径添加模式{@link OH_Drawing_PathAddMode}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddPathWithMatrixAndMode(OH_Drawing_Path* path, const OH_Drawing_Path* src,
    const OH_Drawing_Matrix* matrix, OH_Drawing_PathAddMode pathAddMode);

/**
 * @brief 将源路径以规定模式添加到当前路径中。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、src任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * pathAddMode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param path 指向当前路径对象{@link OH_Drawing_Path}的指针。
 * @param src 指向源路径对象{@link OH_Drawing_Path}的指针。
 * @param pathAddMode 路径添加模式{@link OH_Drawing_PathAddMode}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddPathWithMode(OH_Drawing_Path* path,
    const OH_Drawing_Path* src, OH_Drawing_PathAddMode pathAddMode);

/**
 * @brief 将源路径偏移后，以规定模式添加到当前路径中。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、src任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * pathAddMode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param path 指向当前路径对象{@link OH_Drawing_Path}的指针。
 * @param src 指向源路径对象{@link OH_Drawing_Path}的指针。
 * @param dx 添加到目标路径横坐标的偏移量。
 * @param dy 添加到目标路径纵坐标的偏移量。
 * @param pathAddMode 路径添加模式{@link OH_Drawing_PathAddMode}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddPathWithOffsetAndMode(OH_Drawing_Path* path, const OH_Drawing_Path* src, float dx, float dy,
    OH_Drawing_PathAddMode pathAddMode);

/**
 * @brief 向路径添加多边形。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、points任意一个为NULL或者count等于0时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向当前路径对象{@link OH_Drawing_Path}的指针。
 * @param points 表示多边形的顶点坐标数组。
 * @param count 表示多边形顶点坐标数组的大小。
 * @param isClosed 是否添加连接起始点和终止点的线，true表示添加，false表示不添加。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddPolygon(OH_Drawing_Path* path, const OH_Drawing_Point2D* points, uint32_t count, bool isClosed);

/**
 * @brief 按指定方向，向路径添加圆形。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * radius小于等于0时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE；
 * pathDirection不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param x 表示圆心的x轴坐标。
 * @param y 表示圆心的y轴坐标。
 * @param radius 表示圆形的半径。
 * @param pathDirection 路径方向{@link OH_Drawing_PathDirection}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathAddCircle(OH_Drawing_Path* path,
    float x, float y, float radius, OH_Drawing_PathDirection pathDirection);

/**
 * @brief 解析SVG字符串表示的路径。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、str任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param str 表示SVG字符串。
 * @return 函数返回解析SVG字符串是否成功。true表示成功，false表示不成功。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PathBuildFromSvgString(OH_Drawing_Path* path, const char* str);

/**
 * @brief 将路径转换为SVG字符串。
 *
 * @param path 指向OH_Drawing_Path对象的指针。
 * @param str SVG字符串。API用户负责分配和释放内存。
 * @param strSize SVG字符串内存大小，以字节为单位。
 * @return 返回错误码。如果操作成功，则返回OH_DRAWING_SUCCESS。
 * 如果path或strSize为nullptr，则返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathConvertToSvgString(const OH_Drawing_Path* path, char* str, size_t* strSize);

/**
 * @brief 获取路径点数据。
 *
 * @param path 指向OH_Drawing_Path对象的指针。
 * @param points 路径点数组。
 * @param count 点数组的大小。
 * @return 返回错误码。如果操作成功，则返回OH_DRAWING_SUCCESS。如果path或count为空，则返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathGetPointData(
    const OH_Drawing_Path* path, OH_Drawing_Point2D* points, uint32_t* count);

/**
 * @brief 获取路径动词数据。
 *
 * @param path 指向OH_Drawing_Path对象的指针。
 * @param verbs 路径动词数组。
 * @param count 动词数组的大小。
 * @return 返回错误码。如果操作成功，则返回OH_DRAWING_SUCCESS。如果path或count为空，则返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathGetVerbData(const OH_Drawing_Path* path, OH_Drawing_PathIteratorVerb* verbs,
    uint32_t* count);

/**
 * @brief 获取路径圆锥曲线权重数据。
 *
 * @param path 指向OH_Drawing_Path对象的指针。
 * @param conicWeights 路径圆锥曲线权重数组。
 * @param count 圆锥曲线权重数组的大小。
 * @return 返回错误码。如果操作成功，则返回OH_DRAWING_SUCCESS。如果path或count为空，则返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathGetConicWeightData(
    const OH_Drawing_Path* path, float* conicWeights, uint32_t* count);

/**
 * @brief 判断指定坐标点是否被路径包含，判定是否被路径包含的规则参考{@link OH_Drawing_PathFillType}。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param x x轴上坐标点。
 * @param y y轴上坐标点。
 * @return 函数返回true表示点在路径内，函数返回false表示点在路径外。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PathContains(OH_Drawing_Path* path, float x, float y);

/**
 * @brief 对路径进行矩阵变换。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、matrix任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathTransform(OH_Drawing_Path* path, const OH_Drawing_Matrix* matrix);

/**
 * @brief 对路径进行矩阵变换。用转换后的路径替换目标路径，如果目标路径为NULL，则替换源路径。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * src、matrix任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param src 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @param dst 指向目标路径对象{@link OH_Drawing_Path}的指针。
 * @param applyPerspectiveClip 表示变换路径是否应用透视裁剪。true表示应用透视裁剪，false表示不用透视裁剪。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathTransformWithPerspectiveClip(OH_Drawing_Path* src, const OH_Drawing_Matrix* matrix,
    OH_Drawing_Path* dst, bool applyPerspectiveClip);

/**
 * @brief 设置路径的填充类型，这个决定了路径内部区域的定义方式。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * pathFillType不在枚举范围内返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param pathFillType 路径填充规则{@link OH_Drawing_PathFillType}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathSetFillType(OH_Drawing_Path* path, OH_Drawing_PathFillType pathFillType);

/**
 * @brief 获取路径的填充类型。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param pathFillType 指向路径填充规则{@link OH_Drawing_PathFillType}的指针。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数path或者pathFillType为空。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathGetFillType(OH_Drawing_Path* path, OH_Drawing_PathFillType* pathFillType);

/**
 * @brief 获取当前路径的长度。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param forceClosed 表示是否按照闭合路径测量。true表示测量时路径会被强制视为已闭合，false表示会根据路径的实际闭合状态测量。
 * @return 函数返回当前路径的长度。
 * @since 12
 * @version 1.0
 */
float OH_Drawing_PathGetLength(OH_Drawing_Path* path, bool forceClosed);

/**
 * @brief 获取包含路径的最小边界框。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、rect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathGetBounds(OH_Drawing_Path* path, OH_Drawing_Rect* rect);

/**
 * @brief 用于闭合路径，会添加一条从路径起点位置到最后点位置的线段。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathClose(OH_Drawing_Path* path);

/**
 * @brief 将路径中的所有点沿着x轴和y轴方向偏移一定距离，并将结果存储到目标路径对象中。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向当前路径对象{@link OH_Drawing_Path}的指针。
 * @param dst 指向目标路径对象{@link OH_Drawing_Path}的指针，为NULL时会将结果存储到当前路径对象中。
 * @param dx x轴方向的偏移量。
 * @param dy y轴方向的偏移量。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_PathOffset(OH_Drawing_Path* path, OH_Drawing_Path* dst, float dx, float dy);

/**
 * @brief 用于重置自定义路径数据。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_PathReset(OH_Drawing_Path* path);

/**
 * @brief 获取路径是否闭合。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param forceClosed 表示是否按照闭合路径测量，true表示测量时路径会被强制视为已闭合，false表示会根据路径的实际闭合状态测量。
 * @return 返回路径是否闭合。true表示路径的测量结果为已闭合，false表示路径的测量结果为未闭合。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PathIsClosed(OH_Drawing_Path* path, bool forceClosed);

/**
 * @brief 获取距路径起始点指定距离的坐标点和切线值。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、position、tangent任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param forceClosed 表示是否按照闭合路径测量，true表示测量时路径会被强制视为已闭合，false表示会根据路径的实际闭合状态测量。
 * @param distance 表示距离起始点的距离，小于0时会被视为0处理，大于路径长度时会被视为路径长度处理。
 * @param position 表示距路径起始点指定距离的坐标点。
 * @param tangent 表示距路径起始点指定距离的切线值，tangent.x表示该点切线的余弦值，tangent.y表示该点切线的正弦值。
 * @return 返回测量是否成功。true表示成功，false表示失败。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PathGetPositionTangent(OH_Drawing_Path* path, bool forceClosed,
    float distance, OH_Drawing_Point2D* position, OH_Drawing_Point2D* tangent);

/**
 * @brief 截取路径的片段并追加到目标路径上。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param forceClosed 表示是否按照闭合路径测量，true表示测量时路径会被强制视为已闭合，false表示会根据路径的实际闭合状态测量。
 * @param start 表示与路径起始点的距离，距离路径起始点start距离的位置即为截取路径片段的起始点，小于0时会被视作0，大于等于stop时会截取失败。
 * @param stop 表示与路径起始点的距离，距离路径起始点stop距离的位置即为截取路径片段的终点，小于等于start时会截取失败，大于路径长度时会被视作路径长度。
 * @param startWithMoveTo 表示是否在目标路径执行{@link OH_Drawing_PathMoveTo}移动到截取路径片段的起始点位置。true表示执行，false表示不执行。
 * @param dst 指向目标路径对象{@link OH_Drawing_Path}的指针，截取成功时会将得到的路径片段追加到目标路径上，截取失败时不做改变。
 * @param result 返回是否成功截取路径片段的结果。true表示截取成功，false表示截取失败。作为出参使用。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数path、dst、result至少有一个为空指针。
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathGetSegment(OH_Drawing_Path* path, bool forceClosed,
    float start, float stop, bool startWithMoveTo, OH_Drawing_Path* dst, bool* result);

/**
 * @brief 将两个路径按照指定的路径操作类型合并。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、srcPath任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * op不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针，操作完成后的路径结果将会保存在此路径对象中。
 * @param other 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param op 路径操作枚举类型，支持可选的具体模式可见{@link OH_Drawing_PathOpMode}枚举。
 * @return 返回操作后的路径是否为空。true表示路径不为空，false表示路径为空。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PathOp(OH_Drawing_Path* path, const OH_Drawing_Path* other, OH_Drawing_PathOpMode op);

/**
 * @brief 获取距路径起始点指定距离的相应变换矩阵。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * path、matrix任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * flag不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param forceClosed 表示是否按照闭合路径测量，true表示测量时路径会被强制视为已闭合，false表示会根据路径的实际闭合状态测量。
 * @param distance 表示距离起始点的距离，小于0时会被视为0处理，大于路径长度时会被视为路径长度处理。
 * @param matrix 表示要获取的变换矩阵。
 * @param flag 矩阵信息维度枚举，支持可选的具体模式可见{@link OH_Drawing_PathMeasureMatrixFlags}枚举。
 * @return 返回获取变换矩阵是否成功。true表示获取成功，false表示获取失败，失败的原因可能是path为NULL或者长度为0。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_PathGetMatrix(OH_Drawing_Path* path, bool forceClosed,
    float distance, OH_Drawing_Matrix* matrix, OH_Drawing_PathMeasureMatrixFlags flag);

/**
 * @brief 将当前路径转化为由连续直线段构成的近似路径。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param acceptableError 表示路径上每条线段的可接受误差，不能小于0。
 * 1.当acceptableError为0时，曲线路径被极度细分，会严重影响性能和内存消耗，不建议设置误差值为0。
 * 2.当acceptableError特别大时，路径会极度简化，保留少量关键点，可能会丢失原有形状。
 * 3.对于椭圆等曲线，当acceptableError过大时，拟合结果通常只包含椭圆的分段贝塞尔曲线的起止点，椭圆形会被极度简化为多边形。
 * @param vals 返回包含路径近似点的数组。
 * 每个点由三个值组成，分别表示：
 * 1.该点所在的位置距离路径起点的长度比例值。
 * 2.点的x坐标。
 * 3.点的y坐标。
 * @param count 返回数组的大小，数组大小至少为6。vals为空指针时返回拟合后的点数数组的大小。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数path或者count为空指针。
 * 返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE，表示参数acceptableError小于0。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathApproximate(OH_Drawing_Path* path, float acceptableError, float* vals,
    uint32_t* count);

/**
 * @brief 按照给定权重在当前路径与另一条路径之间进行插值，并将结果存储到目标路径对象中。
 * 两条路径点数相同即可插值成功，目标路径按照当前路径的结构进行创建。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param other 指向用于插值的另一条路径对象{@link OH_Drawing_Path}的指针。
 * @param weight 表示插值权重，范围为[0, 1]。
 * @param success 表示插值是否成功。true表示插值成功，false表示插值失败。作为出参使用。
 * @param interpolatedPath 指向用于存储插值结果的路径对象{@link OH_Drawing_Path}的指针。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数path、other、success或者interpolatedPath为空指针。
 * 返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE，表示参数weight不在[0, 1]范围内。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathInterpolate(OH_Drawing_Path* path, OH_Drawing_Path* other,
    float weight, bool* success, OH_Drawing_Path* interpolatedPath);

/**
 * @brief 检查当前路径与另一条路径（other）在结构和操作顺序上是否完全一致，以确定两条路径是否兼容插值。
 * 若路径中包含圆锥曲线（Conic）操作，则对应操作的权重值也必须一致，才能视为兼容插值。
 *
 * @param path 指向另一条路径对象{@link OH_Drawing_Path}的指针。
 * @param other 指向另一条路径对象{@link OH_Drawing_Path}的指针。
 * @param result 表示当前路径与另一条路径是否兼容插值。作为出参使用。
 * 如果路径兼容，则返回true，否则返回false。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数path、other或者result为空指针。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathIsInterpolate(OH_Drawing_Path* path, OH_Drawing_Path* other, bool* result);

/**
 * @brief 获取路径的最后一个点。
 *
 * @param path 指向<b>OH_Drawing_Path</b>对象的指针。
 * @param point 指向<b>OH_Drawing_Point2D</b>对象的指针，用于存储最后一个点。
 * @return 返回错误码。
 * 如果操作成功，则返回{@link OH_DRAWING_SUCCESS}。
 * 如果路径或点为nullptr，或者路径为空，则返回{@link OH_DRAWING_ERROR_INCORRECT_PARAMETER}。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathGetLastPoint(OH_Drawing_Path* path, OH_Drawing_Point2D* point);

/**
 * @brief 检查路径的填充类型是否是取反类型。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param isInverse 表示填充类型是否是取反类型。作为出参使用。true表示填充类型是取反类型，false表示填充类型不是取反类型。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示path或isInverse是空指针。
 * @since 23
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathIsInverseFillType(const OH_Drawing_Path* path, bool* isInverse);

/**
 * @brief 切换路径的填充类型为取反类型。
 *
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示path是空指针。
 * @since 23
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathToggleInverseFillType(OH_Drawing_Path* path);

/**
 * @brief 检查两个路径是否相等。
 *
 * @param path 指向<b>OH_Drawing_Path</b>对象的指针。
 * @param other 指向另一个要比较的<b>OH_Drawing_Path</b>对象的指针。
 * @param equal 指示两个路径是否相等。
 * @return 返回错误码。
 * 如果操作成功，则返回{@link OH_DRAWING_SUCCESS}。
 * 如果path或other为nullptr，或equal为nullptr，则返回{@link OH_DRAWING_ERROR_INCORRECT_PARAMETER}。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_PathIsEqual(OH_Drawing_Path* path, OH_Drawing_Path* other, bool* equal);

#ifdef __cplusplus
}
#endif
/** @} */
#endif