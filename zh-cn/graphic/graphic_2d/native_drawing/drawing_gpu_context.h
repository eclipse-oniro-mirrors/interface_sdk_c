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
 * @file drawing_gpu_context.h
 *
 * @brief 声明与绘图模块中的图形处理器上下文对象相关的函数，用于创建、配置和销毁图形处理器上下文对象，
 * 为绘图模块提供图形处理器加速渲染所需的上下文环境。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_GPU_CONTEXT_H
#define C_INCLUDE_DRAWING_GPU_CONTEXT_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义有关图形处理器上下文的选项。
 *
 * @since 12
 * @version 1.0
 * @deprecated since 18
 */
typedef struct {
    /**
     * 用于控制是否启用路径蒙版缓存，如果为true，则允许缓存路径蒙版纹理，如果为false，则不允许。
     */
    bool allowPathMaskCaching;
} OH_Drawing_GpuContextOptions;

/**
 * @brief 用于创建一个使用OpenGL作为后端接口的图形处理器上下文对象。创建的图形处理器上下文对象使用完毕后，
 * 需要调用{@link OH_Drawing_GpuContextDestroy}销毁并回收内存。
 *
 * @param gpuContextOptions 图形处理器上下文选项{@link OH_Drawing_GpuContextOptions}，
 * 用于配置所创建的图形处理器上下文对象。
 * @return 返回指向创建的图形处理器上下文对象{@link OH_Drawing_GpuContext}的指针。
 * @since 12
 * @version 1.0
 * @deprecated since 18
 * @useinstead OH_Drawing_GpuContextCreate
 */
OH_Drawing_GpuContext* OH_Drawing_GpuContextCreateFromGL(OH_Drawing_GpuContextOptions gpuContextOptions);

/**
 * @brief 用于创建一个图形处理器上下文对象，使用的后端类型取决于运行设备。创建的图形处理器上下文对象使用完毕后，
 * 需要调用{@link OH_Drawing_GpuContextDestroy}销毁并回收内存。
 *
 * @return 返回指向创建的图形处理器上下文对象{@link OH_Drawing_GpuContext}的指针。
 * @since 16
 * @version 1.0
 */
OH_Drawing_GpuContext* OH_Drawing_GpuContextCreate(void);

/**
 * @brief 用于销毁图形处理器上下文对象并回收该对象占用的内存。调用后该图形处理器上下文对象指针失效，
 * 不可再次使用或重复调用。
 *
 * @param gpuContext 指向图形处理器上下文对象的指针。调用后该指针失效，不可再次使用，否则可能导致未定义行为或程序崩溃。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_GpuContextDestroy(OH_Drawing_GpuContext* gpuContext);

#ifdef __cplusplus
}
#endif
/** @} */
#endif