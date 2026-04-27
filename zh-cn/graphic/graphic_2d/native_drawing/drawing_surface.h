/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
 * @file drawing_surface.h
 *
 * @brief This file declares the functions related to the surface in the drawing module, including creating, destroying,
 *  and using the surface.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_SURFACE_H
#define C_INCLUDE_DRAWING_SURFACE_H

#include "drawing_error_code.h"
#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 使用图形处理器上下文创建一个surface对象，用于管理画布绘制的内容。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * gpuContext为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param gpuContext 指向图形处理器上下文对象的指针{@link OH_Drawing_GpuContext}。
 * @param flag 用于控制内存分配是否计入缓存预算。true则计入高速缓存预算，false则不计入高速缓存预算。
 * @param imageInfo 图片信息{@link OH_Drawing_Image_Info}结构体。
 * @return 返回一个指针，指针指向创建的surface对象{@link OH_Drawing_Surface}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Surface* OH_Drawing_SurfaceCreateFromGpuContext(
    OH_Drawing_GpuContext* gpuContext, bool flag, OH_Drawing_Image_Info imageInfo);

/**
 * @brief 使用图形处理器上下文创建一个与屏幕窗口绑定的surface对象，用于管理画布绘制的内容。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * gpuContext或window为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 * imageInfo的宽高和window的宽高需保持一致。
 *
 * @param gpuContext 指向图形处理器上下文对象的指针{@link OH_Drawing_GpuContext}。
 * 该图形处理器上下文对象必须由{@link OH_Drawing_GpuContextCreate}创建，否则surface对象会创建失败。
 * @param imageInfo 图片信息{@link OH_Drawing_Image_Info}结构体。
 * @param window 指向屏幕窗口对象的指针。
 * @return 返回一个指针，指针指向创建的surface对象{@link OH_Drawing_Surface}。
 * @since 16
 * @version 1.0
 */
OH_Drawing_Surface* OH_Drawing_SurfaceCreateOnScreen(
    OH_Drawing_GpuContext* gpuContext, OH_Drawing_Image_Info imageInfo, void* window);

/**
 * @brief 通过surface对象获取画布对象。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * surface为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param surface 指向创建的surface对象的指针。
 * @return 返回一个指针，指针指向创建的画布对象{@link OH_Drawing_Canvas}。返回的指针不需要由调用者管理。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Canvas* OH_Drawing_SurfaceGetCanvas(OH_Drawing_Surface* surface);

/**
 * @brief 将surface对象上的画布绘制内容提交给GPU处理，完成绘制内容上屏显示。
 *
 * @param surface 指向创建的surface对象的指针{@link OH_Drawing_Surface}。该surface对象必须由{@link OH_Drawing_SurfaceCreateOnScreen}创建，
 * 否则该接口调用将没有任何效果。
 * @return 函数返回执行错误码。
 * 返回OH_DRAWING_SUCCESS，表示执行成功。
 * 返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数surface为空。
 * @since 16
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_SurfaceFlush(OH_Drawing_Surface* surface);

/**
 * @brief 销毁surface对象并回收该对象占用的内存。
 *
 * @param surface 指向创建的surface对象的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SurfaceDestroy(OH_Drawing_Surface* surface);

#ifdef __cplusplus
}
#endif
/** @} */
#endif