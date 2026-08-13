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
 * @brief Drawing模块提供包括2D图形渲染、文字绘制和图片显示等功能函数。
 * <br>本模块采用屏幕物理像素单位px。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file drawing_surface.h
 *
 * @brief 本文件定义了与surface相关的功能函数，包括surface的创建、销毁和使用等。surface对象用于管理画布绘制的内容，
 * 支持通过图形处理器上下文创建离屏surface和与屏幕窗口绑定的surface。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
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
 * @brief 使用图形处理器上下文创建离屏surface对象，用于管理画布绘制的内容。
 * 若需将绘制内容上屏显示（配合{@link OH_Drawing_SurfaceFlush}使用），请改用
 * {@link OH_Drawing_SurfaceCreateOnScreen}创建与屏幕窗口绑定的surface对象。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>gpuContext为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param gpuContext 指向图形处理器上下文对象{@link OH_Drawing_GpuContext}的指针。
 * @param flag 用于控制内存分配是否计入缓存预算。true则计入缓存预算，false则不计入缓存预算。
 * 缓存预算为图形处理器缓存可使用的内存上限，计入预算的内存分配会占用缓存额度。
 * 当需要将绘制内容纳入缓存管理以提升性能时，
 *     flag设置为true；当绘制内容为临时数据、不需要长期缓存时，flag设置为false。
 * @param imageInfo 图像信息{@link OH_Drawing_Image_Info}结构体，用于指定所创建surface的图像宽度、高度、
 * 颜色类型和透明度类型等属性。
 * @return 返回指向创建的surface对象{@link OH_Drawing_Surface}的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Surface* OH_Drawing_SurfaceCreateFromGpuContext(
    OH_Drawing_GpuContext* gpuContext, bool flag, OH_Drawing_Image_Info imageInfo);

/**
 * @brief 使用图形处理器上下文创建一个与屏幕窗口绑定的surface对象，用于管理画布绘制的内容。若不需要上屏显示，
 * 请改用{@link OH_Drawing_SurfaceCreateFromGpuContext}
 * 创建离屏surface对象。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>gpuContext或window为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 * <br>imageInfo的宽高和window的宽高需保持一致，否则对象创建失败。
 *
 * @param gpuContext 指向图形处理器上下文对象{@link OH_Drawing_GpuContext}的指针。
 * @param imageInfo 图像信息{@link OH_Drawing_Image_Info}结构体，用于指定所创建surface的图像宽度、高度、
 * 颜色类型和透明度类型等属性。
 * @param window 指向屏幕窗口对象（OHNativeWindow）的指针，实际应传入OHNativeWindow*类型。
 * @return 返回指向创建的surface对象{@link OH_Drawing_Surface}的指针。
 * @since 16
 * @version 1.0
 */
OH_Drawing_Surface* OH_Drawing_SurfaceCreateOnScreen(
    OH_Drawing_GpuContext* gpuContext, OH_Drawing_Image_Info imageInfo, void* window);

/**
 * @brief 通过surface对象获取画布对象。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>surface为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param surface 指向已创建的surface对象的指针{@link OH_Drawing_Surface}，用于从中获取画布对象。该surface对象可由
 *     {@link OH_Drawing_SurfaceCreateFromGpuContext}或{@link OH_Drawing_SurfaceCreateOnScreen}创建。
 * @return 返回指向获取的画布对象{@link OH_Drawing_Canvas}的指针。返回的指针不需要由调用者管理，
 * 其生命周期由对应的surface对象管理。调用
 *     {@link OH_Drawing_SurfaceDestroy}销毁surface对象后，不应再使用该画布对象。
 * @since 12
 * @version 1.0
 */
OH_Drawing_Canvas* OH_Drawing_SurfaceGetCanvas(OH_Drawing_Surface* surface);

/**
 * @brief 将surface对象上的画布绘制内容提交给图形处理器处理，完成绘制内容上屏显示。
 *
 * @param surface 指向创建的surface对象的指针{@link OH_Drawing_Surface}。该surface对象必须由{@link OH_Drawing_SurfaceCreateOnScreen}创建，
 *     否则该接口调用不会将绘制内容上屏显示。
 * @return 函数返回执行错误码。
 *     <br>返回OH_DRAWING_SUCCESS，表示执行成功。
 *     <br>返回OH_DRAWING_ERROR_INVALID_PARAMETER，表示参数surface为NULL。
 * @since 16
 * @version 1.0
 */
OH_Drawing_ErrorCode OH_Drawing_SurfaceFlush(OH_Drawing_Surface* surface);

/**
 * @brief 销毁surface对象并回收该对象占用的内存。调用本接口销毁surface对象后，
 * 通过{@link OH_Drawing_SurfaceGetCanvas}获取的画布对象不应再使用，其生命周期由surface对象管理。
 *
 * @param surface 指向待销毁的surface对象的指针{@link OH_Drawing_Surface}。该surface对象可由
 *     {@link OH_Drawing_SurfaceCreateFromGpuContext}或{@link OH_Drawing_SurfaceCreateOnScreen}创建，
 * 销毁后该指针不应再被使用。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SurfaceDestroy(OH_Drawing_Surface* surface);

#ifdef __cplusplus
}
#endif
/** @} */
#endif