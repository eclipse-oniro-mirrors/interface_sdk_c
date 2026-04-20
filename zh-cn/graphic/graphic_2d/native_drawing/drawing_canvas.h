/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
 * @file drawing_canvas.h
 *
 * @brief This file declares the functions related to the canvas in the drawing module.
 * By default, the canvas has a black brush with anti-aliasing enabled and without any other style. This brush takes
 * effect only when no brush or pen is proactively set in the canvas.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 8
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_H
#define C_INCLUDE_DRAWING_H

#include "drawing_error_code.h"
#include "drawing_types.h"
#include "drawing_sampling_options.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 源矩形区域约束类型枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 严格约束，源矩形区域必须完全包含在图像中。
     */
    STRICT_SRC_RECT_CONSTRAINT,
    /**
     * 快速约束，源矩形区域可以部分位于图像之外。
     */
    FAST_SRC_RECT_CONSTRAINT,
} OH_Drawing_SrcRectConstraint;

/**
 * @brief 用于创建一个画布对象。
 *
 * @return 函数会返回一个指针，指针指向创建的画布对象。
 * @since 8
 * @version 1.0
 */
OH_Drawing_Canvas* OH_Drawing_CanvasCreate(void);

/**
 * @brief 用于将一个像素图对象绑定到画布中，使得画布绘制的内容输出到像素图中（即CPU渲染）。绑定像素图对象后的画布为非录制类型画布。
 * 像素图对象应该在销毁画布对象之后调用{@link OH_Drawing_PixelMapDissolve}解除绑定。
 *
 * @param pixelMap 指向像素图{@link OH_Drawing_PixelMap}的指针。
 * @return 函数会返回一个指针，指针指向创建的画布对象{@link OH_Drawing_Canvas}，如果对象返回为NULL，则创建失败，原因可能是可用内存不足或者像素图对象为空。
 * @since 20
 * @version 1.0
 */
OH_Drawing_Canvas* OH_Drawing_CanvasCreateWithPixelMap(OH_Drawing_PixelMap* pixelMap);

/**
 * @brief 用于销毁画布对象并回收该对象占有的内存。
 *
 * @param canvas 指向画布对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasDestroy(OH_Drawing_Canvas* canvas);

/**
 * @brief 用于将一个位图对象绑定到画布中，使得画布绘制的内容输出到位图中（即CPU渲染）。绑定位图对象后的画布为非录制类型画布。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、bitmap任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param bitmap 指向位图对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasBind(OH_Drawing_Canvas* canvas, OH_Drawing_Bitmap* bitmap);

/**
 * @brief 用于设置画笔给画布，画布将会使用设置画笔的样式和颜色去绘制图形形状的轮廓。执行该方法后，若画笔的效果发生改变并且开发者希望该变化生效于接下来的绘制动作，需要再次执行该方法以确保变化生效。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、pen任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param pen 指向画笔对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasAttachPen(OH_Drawing_Canvas* canvas, const OH_Drawing_Pen* pen);

/**
 * @brief 用于去除掉画布中的画笔，使用后画布将不去绘制图形形状的轮廓。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasDetachPen(OH_Drawing_Canvas* canvas);

/**
 * @brief 用于设置画刷给画布，画布将会使用设置的画刷样式和颜色去填充绘制的图形形状。执行该方法后，若画刷的效果发生改变并且开发者希望该变化生效于接下来的绘制动作，需要再次执行该方法以确保变化生效。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、brush任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param brush 指向画刷对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasAttachBrush(OH_Drawing_Canvas* canvas, const OH_Drawing_Brush* brush);

/**
 * @brief 用于去除掉画布中的画刷，使用后画布将不使用此前设置的画刷去填充图形形状。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasDetachBrush(OH_Drawing_Canvas* canvas);

/**
 * @brief 用于保存当前画布的状态（画布矩阵）到一个栈顶。需要与恢复接口{@link OH_Drawing_CanvasRestore}配合使用。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasSave(OH_Drawing_Canvas* canvas);

/**
 * @brief 保存矩阵和裁剪区域，为后续绘制分配位图。调用恢复接口。
 * {@link OH_Drawing_CanvasRestore}将放弃对矩阵和剪切区域所做的更改，并绘制位图。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针，用于限制图层大小，为NULL表示无限制。
 * @param brush 指向画刷对象{@link OH_Drawing_Brush}的指针，绘制位图时会应用画刷对象的透明度，滤波器效果，混合模式，为NULL表示不应用任何效果。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasSaveLayer(OH_Drawing_Canvas* canvas, const OH_Drawing_Rect* rect, const OH_Drawing_Brush* brush);

/**
 * @brief 用于恢复保存在栈顶的画布状态（画布矩阵）。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasRestore(OH_Drawing_Canvas* canvas);

/**
 * @brief 用于获取栈中保存的画布状态（画布矩阵）的数量。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @return 函数会返回一个32位的值描述画布状态（画布矩阵）的数量，画布初始状态数量为1。
 * @since 11
 * @version 1.0
 */
uint32_t OH_Drawing_CanvasGetSaveCount(OH_Drawing_Canvas* canvas);

/**
 * @brief 用于恢复到指定数量的画布状态（画布矩阵）。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param saveCount 要恢复的画布状态深度。小于等于1时，恢复为初始状态；大于已保存的画布状态数量时，不执行任何操作。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasRestoreToCount(OH_Drawing_Canvas* canvas, uint32_t saveCount);

/**
 * @brief 用于画一条直线段。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param x1 线段起始点的横坐标。
 * @param y1 线段起始点的纵坐标。
 * @param x2 线段结束点的横坐标。
 * @param y2 线段结束点的纵坐标。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasDrawLine(OH_Drawing_Canvas* canvas, float x1, float y1, float x2, float y2);

/**
 * @brief 用于画一个自定义路径。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、path任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param path 指向路径对象的指针。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasDrawPath(OH_Drawing_Canvas* canvas, const OH_Drawing_Path* path);

/**
 * @brief 在网格上绘制像素图，网格均匀分布在像素图上。（只支持brush，使用pen没有绘制效果。）
 *
 * @param cCanvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param pixelMap 指向像素图{@link OH_Drawing_PixelMap}的指针。
 * @param meshWidth 网格的列数，取值为大于0的整数。
 * @param meshHeight 网格的行数，取值为大于0的整数。
 * @param vertices 指向网格顶点数组的指针。
 * @param verticesSize 网格顶点数组的大小，大小必须为((meshWidth + 1) * (meshHeight + 1) + vertoffset) * 2。
 * @param vertOffset 在绘图前需要跳过的顶点数，取值为大于等于0的整数。
 * @param colors 指向网格颜色数组的指针，可为nullptr。
 * @param colorsSize 网格颜色数组的大小，若存在则大小必须为(meshWidth + 1) * (meshHeight + 1) + colorOffset。
 * @param colorOffset 在绘图前需要跳过的颜色数，取值为大于等于0的整数。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INCORRECT_PARAMETER，表示出现cCanvas、pixelMap、vertices等参数为空或传参不符合取值规则的情况。
 * @since 23
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawPixelMapMesh(OH_Drawing_Canvas* cCanvas, OH_Drawing_PixelMap* pixelMap,
    uint32_t meshWidth, uint32_t meshHeight, const float* vertices, uint32_t verticesSize, uint32_t vertOffset,
    const uint32_t* colors, uint32_t colorsSize, uint32_t colorOffset);

/**
 * @brief 通过绘制两条水平线和两条垂直线将像素图分割成9个部分：四个边，四个角和中心。
 * 若角落的4个区域尺寸不超过目标矩形，则会在不缩放的情况下被绘制在目标矩形，反之则会按比例缩放绘制在目标矩形。
 * 如果还有剩余空间，剩下的5个区域会通过拉伸或压缩来绘制，以便能够完全覆盖目标矩形。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param pixelMap 指向像素图{@link OH_Drawing_PixelMap}的指针。
 * @param center 指向矩形对象{@link OH_Drawing_Rect}的指针，表示分割像素图的中心矩形。矩形四条边所在的直线将像素图分成了9个部分。
 * @param dst 指向矩形对象{@link OH_Drawing_Rect}的指针，表示画布上的目标区域。
 * @param mode 过滤模式枚举{@link OH_Drawing_FilterMode}。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas、pixelMap或dst为空。
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawPixelMapNine(OH_Drawing_Canvas* canvas, OH_Drawing_PixelMap* pixelMap,
    const OH_Drawing_Rect* center, const OH_Drawing_Rect* dst, OH_Drawing_FilterMode mode);

/**
 * @brief 用于将像素图的指定区域绘制到画布的指定区域。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、pixelMap、dst任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param pixelMap 指向像素图{@link OH_Drawing_PixelMap}的指针。
 * @param src 像素图指定矩形区域，为NULL将指定整个像素图区域。
 * @param dst 目标画布指定矩形区域。
 * @param samplingOptions 指向采样选项对象{@link OH_Drawing_SamplingOptions}的指针，为NULL将使用默认采样选项。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawPixelMapRect(OH_Drawing_Canvas* canvas, OH_Drawing_PixelMap* pixelMap,
    const OH_Drawing_Rect* src, const OH_Drawing_Rect* dst, const OH_Drawing_SamplingOptions* samplingOptions);

/**
 * @brief 用于将像素图的指定区域绘制到画布的指定区域。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param pixelMap 指向像素图{@link OH_Drawing_PixelMap}的指针。
 * @param src 像素图指定矩形区域，为NULL将指定整个像素图区域。
 * @param dst 目标画布指定矩形区域。
 * @param samplingOptions 指向采样选项对象{@link OH_Drawing_SamplingOptions}的指针，为NULL将使用默认采样选项。
 * @param constraint 约束类型，支持可选的具体类型可见{@link OH_Drawing_SrcRectConstraint}枚举。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas、pixelMap或dst为空。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawPixelMapRectConstraint(OH_Drawing_Canvas* canvas,
    OH_Drawing_PixelMap* pixelMap, const OH_Drawing_Rect* src, const OH_Drawing_Rect* dst,
    const OH_Drawing_SamplingOptions* samplingOptions, OH_Drawing_SrcRectConstraint constraint);

/**
 * @brief 用于画一个背景，此背景以画刷填充。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、brush任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param brush 指向画刷对象的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawBackground(OH_Drawing_Canvas* canvas, const OH_Drawing_Brush* brush);

/**
 * @brief 用于画一块区域。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、region任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param region 指向区域对象的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawRegion(OH_Drawing_Canvas* canvas, const OH_Drawing_Region* region);

/**
 * @brief 绘制多个点的方式枚举，方式分为离散点、直线或开放多边形。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 分别绘制每个点。
     */
    POINT_MODE_POINTS,
    /**
     * 将每两个点绘制为线段。
     */
    POINT_MODE_LINES,
     /**
     * 将点阵列绘制为开放多边形。
     */
    POINT_MODE_POLYGON,
} OH_Drawing_PointMode;

/**
 * @brief 用于画一个点。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param point 指向点对象{@link OH_Drawing_Point2D}的指针。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas或者point为空。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawPoint(OH_Drawing_Canvas* canvas, const OH_Drawing_Point2D* point);

/**
 * @brief 用于画多个点，绘制方式分为绘制单独的点、绘制成线段或绘制成开放多边形。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、point2D任意一个为NULL或者count等于0时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * mode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param canvas 指向画布对象的指针。
 * @param mode 绘制多个点的方式，支持方式参考{@link OH_Drawing_PointMode}。
 * @param count 点的数量，即点数组中点的个数。
 * @param point2D 指向多个点的数组。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawPoints(OH_Drawing_Canvas* canvas, OH_Drawing_PointMode mode,
    uint32_t count, const OH_Drawing_Point2D* point2D);

/**
 * @brief 用于画一个位图，位图又称为点阵图像、像素图或栅格图像，是由像素（图片元素）的单个点组成。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、bitmap任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param bitmap 指向位图对象的指针。
 * @param left 位图对象左上角的横坐标。
 * @param top 位图对象左上角的纵坐标。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawBitmap(OH_Drawing_Canvas* canvas, const OH_Drawing_Bitmap* bitmap, float left, float top);

/**
 * @brief 将位图的指定区域绘制到画布的指定区域。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、bitmap、dst任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param bitmap 指向位图对象{@link OH_Drawing_Bitmap}的指针。
 * @param src 源位图指定矩形区域，为NULL将指定整个源位图区域。
 * @param dst 目标画布指定矩形区域。
 * @param samplingOptions 指向采样选项对象{@link OH_Drawing_SamplingOptions}的指针，为NULL将使用默认采样选项。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawBitmapRect(OH_Drawing_Canvas* canvas, const OH_Drawing_Bitmap* bitmap,
    const OH_Drawing_Rect* src, const OH_Drawing_Rect* dst, const OH_Drawing_SamplingOptions* samplingOptions);

/**
 * @brief 用于画一个矩形。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、OH_Drawing_Rect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param rect 指向矩形对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawRect(OH_Drawing_Canvas* canvas, const OH_Drawing_Rect* rect);

/**
 * @brief 用于画一个圆形。本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。canvas、
 * point任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * radius小于等于0时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param canvas 指向画布对象的指针。
 * @param point 指向坐标点对象的指针，表示圆心。
 * @param radius 圆形的半径，小于等于0时无效。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawCircle(OH_Drawing_Canvas* canvas, const OH_Drawing_Point* point, float radius);

/**
 * @brief 用于使用指定的颜色及混合模式来填充整个画布。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param color 表示指定的颜色，用一个32位（ARGB）的变量表示。
 * @param blendMode 表示指定的混合模式。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas为空。
 * 返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE，表示blendMode不在枚举范围内。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawColor(OH_Drawing_Canvas* canvas, uint32_t color,
    OH_Drawing_BlendMode blendMode);

/**
 * @brief 用于画一个椭圆。本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。canvas、
 * rect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param rect 指向矩形对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawOval(OH_Drawing_Canvas* canvas, const OH_Drawing_Rect* rect);

/**
 * @brief 用于画一个弧。当扫描角度的绝对值大于360度时，本接口绘制的是一个椭圆。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、rect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param rect 指向矩形对象的指针。
 * @param startAngle 弧的起始角度，0度时起始点位于椭圆的右端点，正数时以顺时针方向放置起始点，负数时以逆时针方向放置起始点。
 * @param sweepAngle 弧的扫描角度，正数时顺时针扫描，负数时逆时针扫描。它的有效范围在-360度到360度之间，当绝对值大于360度时，该函数绘制的是一个椭圆。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawArc(OH_Drawing_Canvas* canvas,
    const OH_Drawing_Rect* rect, float startAngle, float sweepAngle);

/**
 * @brief 绘制一段圆弧。该方法允许指定圆弧的起始角度、扫描角度以及圆弧的起点和终点是否连接圆弧的中心点。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @param startAngle 弧的起始角度，单位为度，该参数为浮点数。0度时起始点位于椭圆的右端点，为正数时以顺时针方向放置起始点，为负数时以逆时针方向放置起始点。
 * @param sweepAngle 弧的扫描角度，单位为度，该参数为浮点数。为正数时顺时针扫描，为负数时逆时针扫描。扫描角度可以超过360度，将绘制一个完整的椭圆。
 * @param useCenter 表示绘制时弧形的起点和终点是否连接弧形的中心点。true表示连接，false表示不连接。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas或者rect为空。
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawArcWithCenter(OH_Drawing_Canvas* canvas, const OH_Drawing_Rect* rect,
    float startAngle, float sweepAngle, bool useCenter);

/**
 * @brief 用于画一个圆角矩形。本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。canvas、
 * roundRect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param roundRect 指向圆角矩形对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawRoundRect(OH_Drawing_Canvas* canvas, const OH_Drawing_RoundRect* roundRect);

/**
 * @brief 绘制两个嵌套的圆角矩形，外部矩形边界必须包含内部矩形边界，否则无绘制效果。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param outer 指向圆角矩形对象{@link OH_Drawing_RoundRect}的指针，表示外部圆角矩形边界。
 * @param inner 指向圆角矩形对象{@link OH_Drawing_RoundRect}的指针，表示内部圆角矩形边界。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas、outer或者inner为空。
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawNestedRoundRect(OH_Drawing_Canvas* canvas, const OH_Drawing_RoundRect* outer,
    const OH_Drawing_RoundRect* inner);

/**
 * @brief 用于绘制单个字符。当前字型中的字体不支持待绘制字符时，退化到使用系统字体绘制字符。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param str 待绘制的单个字符。可以传入字符串，但只会以UTF-8编码解析并绘制字符串中的首个字符。
 * @param font 指向字型对象{@link OH_Drawing_Font}的指针。
 * @param x 字符对象基线左端点（靠近字符左下角）的横坐标。
 * @param y 字符对象基线左端点（靠近字符左下角）的纵坐标。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas、str、font任意一个为NULL或者str的长度为0。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawSingleCharacter(OH_Drawing_Canvas* canvas, const char* str,
    const OH_Drawing_Font* font, float x, float y);

/**
 * @brief 绘制单个字符，字符带有字体特征。当前字型中的字体不支持待绘制字符时，退化到使用系统字体绘制字符。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param str 待绘制的单个字符。可以传入字符串，但只会以UTF-8编码解析并绘制字符串中的首个字符。
 * @param font 指向字型对象{@link OH_Drawing_Font}的指针。
 * @param x 字符对象基线左端点（靠近字符左下角）的横坐标。
 * @param y 字符对象基线左端点（靠近字符左下角）的纵坐标。
 * @param fontFeatures 指向字体特征容器对象{@link OH_Drawing_FontFeatures}的指针。容器中未加入任何字体特征时使用TTF(TrueType Font)文件中预设的字体特征。
 * @return 函数返回执行结果。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas、str、font或者fontFeatures任意一个为NULL或者str的长度为0。
 * @since 20
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawSingleCharacterWithFeatures(OH_Drawing_Canvas* canvas, const char* str,
    const OH_Drawing_Font* font, float x, float y, OH_Drawing_FontFeatures* fontFeatures);

/**
 * @brief 用于画一段文字。若构造OH_Drawing_TextBlob的字体不支持待绘制字符，则该部分字符无法绘制。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、textBlob任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param textBlob 指向文本对象的指针。
 * @param x 文本对象基线左端点（靠近文本左下角）的横坐标。
 * @param y 文本对象基线左端点（靠近文本左下角）的纵坐标。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasDrawTextBlob(OH_Drawing_Canvas* canvas, const OH_Drawing_TextBlob* textBlob, float x, float y);

/**
 * @brief 画布裁剪方式的枚举集合。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 将指定区域裁剪（取差集）。
     */
    DIFFERENCE,
    /**
     * 将指定区域保留（取交集）。
     */
    INTERSECT,
} OH_Drawing_CanvasClipOp;

/**
 * @brief 用于裁剪一个矩形。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、rect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * clipOp不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param canvas 指向画布对象的指针。
 * @param rect 指向矩形对象的指针。
 * @param clipOp 裁剪方式。支持可选的具体裁剪方式可见{@link OH_Drawing_CanvasClipOp}枚举。
 * @param doAntiAlias 值为true则做抗锯齿处理，值为false不做抗锯齿处理。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasClipRect(OH_Drawing_Canvas* canvas, const OH_Drawing_Rect* rect,
    OH_Drawing_CanvasClipOp clipOp, bool doAntiAlias);

/**
 * @brief 用于裁剪一个圆角矩形。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、roundRect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * clipOp不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param canvas 指向画布对象的指针。
 * @param roundRect 指向圆角矩形对象的指针。
 * @param clipOp 裁剪方式。支持可选的具体裁剪方式可见@{link OH_Drawing_CanvasClipOp}枚举。
 * @param doAntiAlias 表示是否需要做抗锯齿处理，值为true时为需要，为false时为不需要。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasClipRoundRect(OH_Drawing_Canvas* canvas, const OH_Drawing_RoundRect* roundRect,
    OH_Drawing_CanvasClipOp clipOp, bool doAntiAlias);

/**
 * @brief 用于裁剪一个自定义路径。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、path任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * clipOp不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param canvas 指向画布对象的指针。
 * @param path 指向路径对象的指针。
 * @param clipOp 裁剪方式。支持可选的具体裁剪方式可见@{link OH_Drawing_CanvasClipOp}枚举。
 * @param doAntiAlias 真为抗锯齿，假则不做抗锯齿处理。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasClipPath(OH_Drawing_Canvas* canvas, const OH_Drawing_Path* path,
    OH_Drawing_CanvasClipOp clipOp, bool doAntiAlias);

/**
 * @brief 用于裁剪一个区域。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param region 指向区域对象{@link OH_Drawing_Region}的指针。
 * @param clipOp 表示裁剪类型。支持可选的具体裁剪方式可见@{link OH_Drawing_CanvasClipOp}枚举。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas或者region为空。
 * 返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE，表示clipOp不在枚举范围内。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasClipRegion(OH_Drawing_Canvas* canvas, const OH_Drawing_Region* region,
    OH_Drawing_CanvasClipOp clipOp);

/**
 * @brief 用于画布旋转一定的角度，正数表示顺时针旋转，负数反之。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param degrees 旋转角度。
 * @param px 旋转中心的横坐标。
 * @param py 旋转中心的纵坐标。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasRotate(OH_Drawing_Canvas* canvas, float degrees, float px, float py);

/**
 * @brief 用于平移画布一段距离。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param dx x轴方向的移动距离。
 * @param dy y轴方向的移动距离。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasTranslate(OH_Drawing_Canvas* canvas, float dx, float dy);

/**
 * @brief 用于画布缩放。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param sx x轴方向的缩放比例。
 * @param sy y轴方向的缩放比例。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_CanvasScale(OH_Drawing_Canvas* canvas, float sx, float sy);

/**
 * @brief 用于画布倾斜变换。等同于将当前画布矩阵左乘（premultiply）倾斜变换矩阵，并应用到画布上。其中倾斜变换矩阵为：
 * |1 sx 0|
 * |sy 1 0|
 * |0  0 1|。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param sx 沿x轴的倾斜量。正值会使绘制沿y轴增量方向向右倾斜；负值会使绘制沿y轴增量方向向左倾斜。
 * @param sy 沿y轴的倾斜量。正值会使绘制沿x轴增量方向向下倾斜；负值会使绘制沿x轴增量方向向上倾斜。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasSkew(OH_Drawing_Canvas* canvas, float sx, float sy);

/**
 * @brief 获取画布宽度。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @return 返回画布宽度。
 * @since 12
 * @version 1.0
 */
int32_t OH_Drawing_CanvasGetWidth(OH_Drawing_Canvas* canvas);

/**
 * @brief 获取画布高度。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @return 返回画布高度。
 * @since 12
 * @version 1.0
 */
int32_t OH_Drawing_CanvasGetHeight(OH_Drawing_Canvas* canvas);

/**
 * @brief 获取画布裁剪区域的边界。该接口不可用于录制类型画布。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、rect任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针，开发者可调用{@link OH_Drawing_RectCreate}接口创建。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasGetLocalClipBounds(OH_Drawing_Canvas* canvas, OH_Drawing_Rect* rect);

/**
 * @brief 获取画布3x3矩阵。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、matrix任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针，开发者可调用{@link OH_Drawing_MatrixCreate}接口创建。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasGetTotalMatrix(OH_Drawing_Canvas* canvas, OH_Drawing_Matrix* matrix);

/**
 * @brief 画布现有矩阵左乘以传入矩阵，不影响该接口之前的绘制操作。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、matrix任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasConcatMatrix(OH_Drawing_Canvas* canvas, OH_Drawing_Matrix* matrix);

/**
 * @brief 阴影标志枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 无阴影标志。
     */
    SHADOW_FLAGS_NONE,
    /**
     * 遮挡物对象不透明标志。
     */
    SHADOW_FLAGS_TRANSPARENT_OCCLUDER,
    /**
     * 不分析阴影标志。
     */
    SHADOW_FLAGS_GEOMETRIC_ONLY,
    /**
     * 使能以上所有阴影标志。
     */
    SHADOW_FLAGS_ALL,
} OH_Drawing_CanvasShadowFlags;

/**
 * @brief 绘制射灯类型阴影，使用路径描述环境光阴影的轮廓。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、path任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER；
 * flag不在枚举范围内返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针，用于生成阴影。
 * @param planeParams 表示遮挡物相对于画布在Z轴上的偏移量，其值取决于x与y坐标。
 * @param devLightPos 光线相对于画布的位置。
 * @param lightRadius 光源半径，需大于或等于0。
 * @param ambientColor 环境阴影颜色，用一个32位（ARGB）的变量表示。
 * @param spotColor 点阴影颜色，用一个32位（ARGB）的变量表示。
 * @param flag 阴影标志枚举{@link OH_Drawing_CanvasShadowFlags}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawShadow(OH_Drawing_Canvas* canvas, OH_Drawing_Path* path, OH_Drawing_Point3D planeParams,
    OH_Drawing_Point3D devLightPos, float lightRadius, uint32_t ambientColor, uint32_t spotColor,
    OH_Drawing_CanvasShadowFlags flag);

/**
 * @brief 用于使用指定颜色去清空画布。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象的指针。
 * @param color 描述颜色的32位（ARGB）变量。
 * @since 8
 * @version 1.0
 */
void OH_Drawing_CanvasClear(OH_Drawing_Canvas* canvas, uint32_t color);

/**
 * @brief 设置画布的矩阵状态。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、matrix任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param matrix 指向矩阵对象{@link OH_Drawing_Matrix}的指针，开发者可调用{@link OH_Drawing_MatrixCreate}接口创建。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasSetMatrix(OH_Drawing_Canvas* canvas, OH_Drawing_Matrix* matrix);

/**
 * @brief 重置当前画布的矩阵为单位矩阵。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasResetMatrix(OH_Drawing_Canvas* canvas);

/**
 * @brief 重置剪辑状态。
 *
 * @param canvas 指向OH_Drawing_Canvas对象的指针。
 * @return 返回错误码。
 * 如果操作成功，则返回OH_DRAWING_SUCCESS。
 * 如果canvas为nullptr，则返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasResetClip(OH_Drawing_Canvas* canvas);

/**
 * @brief 将图片绘制到画布的指定区域上，源矩形选定的区域会缩放平移到目标矩形。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、image、src、dst任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param image 指向图片对象{@link OH_Drawing_Image}的指针。
 * @param src 指向目标矩形对象{@link OH_Drawing_Rect}的指针。
 * @param dst 指向目标矩形对象{@link OH_Drawing_Rect}的指针。
 * @param samplingOptions 指向采样选项对象{@link OH_Drawing_SamplingOptions}的指针，为NULL将使用默认采样选项。
 * @param srcRectConstraint 约束类型，支持可选的具体类型可见{@link OH_Drawing_SrcRectConstraint}枚举。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawImageRectWithSrc(OH_Drawing_Canvas* canvas, const OH_Drawing_Image* image,
    const OH_Drawing_Rect* src, const OH_Drawing_Rect* dst, const OH_Drawing_SamplingOptions* samplingOptions,
    OH_Drawing_SrcRectConstraint srcRectConstraint);

/**
 * @brief 将图片绘制到画布的指定区域上。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、image、dst任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param image 指向图片对象{@link OH_Drawing_Image}的指针。
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @param samplingOptions 指向采样选项对象{@link OH_Drawing_SamplingOptions}的指针，为NULL将使用默认采样选项。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawImageRect(OH_Drawing_Canvas* canvas, OH_Drawing_Image* image,
    OH_Drawing_Rect* rect, OH_Drawing_SamplingOptions* samplingOptions);

/**
 * @brief 用于指定如何解释给定顶点的几何形状的枚举类型。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 每三个顶点表示一个三角形，如果顶点数不是3的倍数，则多余的顶点会被忽略。
     */
    VERTEX_MODE_TRIANGLES,
    /**
     * 相邻三个顶点表示一个三角形，每个新的顶点将与前两个顶点组成一个新的三角形。
     */
    VERTEX_MODE_TRIANGLES_STRIP,
    /**
     * 第一个顶点作为中心点，后续的每个顶点都与前一个顶点和中心点组成一个三角形。
     */
    VERTEX_MODE_TRIANGLE_FAN,
} OH_Drawing_VertexMode;

/**
 * @brief 用于画顶点数组描述的三角网格。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas或positions为NULL、vertexCount值小于3、indexCount值小于3且不为0，存在以上任意一种情况时设置错误码为OH_DRAWING_ERROR_INVALID_PARAMETER；
 * vertexMmode、mode任意一个不在枚举范围内时设置错误码为OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param canvas 指向画布对象的指针。
 * @param vertexMmode 绘制顶点的连接方式，支持方式参考{@link OH_Drawing_VertexMode}。
 * @param vertexCount 顶点数组元素的数量，值必须大于等于3。
 * @param positions 描述顶点位置的数组指针，不能为空，其长度必须等于vertexCount。
 * @param texs 描述顶点对应纹理空间坐标的数组指针，可以为空，若不为空其长度必须等于vertexCount。
 * @param colors 描述顶点对应颜色的数组指针，用于在三角形中进行插值，可以为空，若不为空其长度必须等于vertexCount。
 * @param indexCount 索引的数量，可以为0，若不为0则值必须大于等于3。
 * @param indices 描述顶点对应索引的数组指针，可以为空，若不为空其长度必须等于indexCount。
 * @param mode 混合模式枚举，支持方式参考{@link OH_Drawing_BlendMode}。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_CanvasDrawVertices(OH_Drawing_Canvas* canvas, OH_Drawing_VertexMode vertexMmode,
    int32_t vertexCount, const OH_Drawing_Point2D* positions, const OH_Drawing_Point2D* texs,
    const uint32_t* colors, int32_t indexCount, const uint16_t* indices, OH_Drawing_BlendMode mode);

/**
 * @brief 从画布中拷贝像素数据到指定地址。该接口不可用于录制类型画布。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、imageInfo、dstPixels任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param imageInfo 指向图片信息{@link OH_Drawing_Image_Info}的指针。
 * @param dstPixels 目标像素存储首地址。
 * @param dstRowBytes 一行像素的大小，小于等于0时无效。
 * @param srcX 画布像素的x轴偏移量，单位为像素。
 * @param srcY 画布像素的y轴偏移量，单位为像素。
 * @return 函数返回true表示像素成功拷贝到目标像素存储首地址，函数返回false表示拷贝失败。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_CanvasReadPixels(OH_Drawing_Canvas* canvas, OH_Drawing_Image_Info* imageInfo,
    void* dstPixels, uint32_t dstRowBytes, int32_t srcX, int32_t srcY);

/**
 * @brief 从画布拷贝像素数据到位图中。该接口不可用于录制类型画布。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * canvas、bitmap任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param bitmap 指向位图对象{@link OH_Drawing_Bitmap}的指针。
 * @param srcX 画布像素的x轴偏移量，单位为像素。
 * @param srcY 画布像素的y轴偏移量，单位为像素。
 * @return 函数返回true表示像素成功拷贝到位图，函数返回false表示拷贝失败。
 * @since 12
 * @version 1.0
 */
bool OH_Drawing_CanvasReadPixelsToBitmap(OH_Drawing_Canvas* canvas,
    OH_Drawing_Bitmap* bitmap, int32_t srcX, int32_t srcY);

/**
 * @brief 用于判断裁剪后可绘制区域是否为空。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param isClipEmpty 表示裁剪后可绘制区域是否为空。true表示为空，false表示不为空。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas或者isClipEmpty为空。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasIsClipEmpty(OH_Drawing_Canvas* canvas, bool* isClipEmpty);

/**
 * @brief 用于获取画布的图像信息。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param imageInfo 指向图像信息对象{@link OH_Drawing_Image_Info}的指针。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas或者imageInfo为空。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasGetImageInfo(OH_Drawing_Canvas* canvas, OH_Drawing_Image_Info* imageInfo);

/**
 * @brief 用于绘制录制指令对象。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针，仅支持录制类型画布。
 * @param recordCmd 指向录制指令对象{@link OH_Drawing_RecordCmd}的指针。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas或者recordCmd为空。
 * @since 13
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawRecordCmd(OH_Drawing_Canvas* canvas, OH_Drawing_RecordCmd* recordCmd);

/**
 * @brief 用于绘制录制指令对象，支持嵌套。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针，仅支持录制类型画布。
 * @param recordCmd 指向录制指令对象{@link OH_Drawing_RecordCmd}的指针。
 * @return 函数返回执行操作码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas或者recordCmd为空。
 * @since 19
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasDrawRecordCmdNesting(OH_Drawing_Canvas* canvas, OH_Drawing_RecordCmd* recordCmd);

/**
 * @brief 判断路径与画布区域是否不相交。画布区域包含边界。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param path 指向路径对象{@link OH_Drawing_Path}的指针。
 * @param quickReject 表示路径与画布区域是否不相交，true表示路径与画布区域不相交，false表示路径与画布区域相交。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas、path或者quickReject为空。
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasQuickRejectPath(OH_Drawing_Canvas* canvas, const OH_Drawing_Path* path,
    bool* quickReject);

/**
 * @brief 判断矩形和画布区域是否不相交。画布区域包含边界。
 *
 * @param canvas 指向画布对象{@link OH_Drawing_Canvas}的指针。
 * @param rect 指向矩形对象{@link OH_Drawing_Rect}的指针。
 * @param quickReject 表示矩形与画布区域是否不相交，true表示矩形与画布区域不相交，false表示矩形与画布区域相交。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数canvas、rect或者quickReject为空。
 * @since 18
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasQuickRejectRect(OH_Drawing_Canvas* canvas, const OH_Drawing_Rect* rect,
    bool* quickReject);

/**
 * @brief 检查当前图层绘制设备是否是不透明的。
 *
 * @param canvas 指向 OH_Drawing_Canvas 对象的指针。
 * @param isOpaque 表示画布是否为不透明。
 * @return 返回错误码。
 * 如果操作成功，返回OH_DRAWING_SUCCESS。
 * 如果 canvas 或 isOpaque 为空，返回 OH_DRAWING_ERROR_INCORRECT_PARAMETER。
 * @since 26.0.0
 */
OH_Drawing_ErrorCode OH_Drawing_CanvasIsOpaque(const OH_Drawing_Canvas* canvas, bool* isOpaque);

#ifdef __cplusplus
}
#endif
/** @} */
#endif