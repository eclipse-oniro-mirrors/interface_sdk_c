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
 * @file drawing_color_space.h
 *
 * @brief 声明与绘图模块中的颜色空间对象相关的函数。颜色空间用于定义颜色的解释和映射方式，
 * 确保图像在不同显示设备上的一致性呈现。本文件提供创建标准颜色空间（sRGB）和线性颜色空间（sRGB Linear）的函数，
 * 以及销毁颜色空间对象并回收内存的函数，用于图像渲染和色彩管理等场景。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_COLOR_SPACE_H
#define C_INCLUDE_DRAWING_COLOR_SPACE_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建一个标准sRGB颜色空间。适用于需要将颜色值按照sRGB标准进行解释和渲染的场景。
 * 创建的颜色空间对象使用完毕后必须调用{@link OH_Drawing_ColorSpaceDestroy}销毁并释放内存，
 * 否则会导致内存泄漏。
 *
 * @return 返回一个指向创建的颜色空间对象{@link OH_Drawing_ColorSpace}的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ColorSpace* OH_Drawing_ColorSpaceCreateSrgb(void);

/**
 * @brief 创建一个Gamma值为1.0的线性颜色空间。与OH_Drawing_ColorSpaceCreateSrgb创建的标准sRGB颜色空间不同，
 * 线性颜色空间适用于需要进行线性颜色计算（如混合、光照等）的场景。
 * 创建的颜色空间对象使用完毕后必须调用{@link OH_Drawing_ColorSpaceDestroy}销毁并释放内存，否则会导致内存泄漏。
 *
 * @return 返回一个指向创建的颜色空间对象{@link OH_Drawing_ColorSpace}的指针。
 * @since 12
 * @version 1.0
 */
OH_Drawing_ColorSpace* OH_Drawing_ColorSpaceCreateSrgbLinear(void);

/**
 * @brief 销毁颜色空间对象，并回收该对象占用的内存。
 *
 * @param colorSpace 指向待销毁的颜色空间对象{@link OH_Drawing_ColorSpace}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_ColorSpaceDestroy(OH_Drawing_ColorSpace* colorSpace);

#ifdef __cplusplus
}
#endif
/** @} */
#endif