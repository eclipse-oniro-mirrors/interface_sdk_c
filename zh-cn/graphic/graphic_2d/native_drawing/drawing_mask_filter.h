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
 * @brief Drawing模块提供包括2D图形渲染、文字绘制和图片显示等功能函数。
 * <br>本模块采用屏幕物理像素单位px。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @since 11
 * @version 1.0
 */
/**
 * @file drawing_mask_filter.h
 *
 * @brief 声明与绘图模块中的对象相关的函数。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_MASK_FILTER_H
#define C_INCLUDE_DRAWING_MASK_FILTER_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 蒙版滤波器模糊操作类型的枚举。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 内外模糊。
     */
    NORMAL,
    /**
     * 内部实心，外部模糊。
     */
    SOLID,
    /**
     * 内部空白，外部模糊。
     */
    OUTER,
    /**
     * 内部模糊，外部空白。
     */
    INNER,
} OH_Drawing_BlurType;

/**
 * @brief 创建具有模糊效果的蒙版滤波器。常用于为图形、文本等绘制内容添加模糊视觉效果。创建的蒙版滤波器对象使用完毕后，
 * 必须调用{@link OH_Drawing_MaskFilterDestroy}销毁并释放内存。
 *
 * @param blurType 表示模糊类型，用于指定蒙版滤波器的模糊操作方式。
 * @param sigma 表示要应用的高斯模糊的标准差，单位为px。必须大于0。
 * @param respectCTM 表示模糊标准差值是否受CTM（当前变换矩阵）影响。传入true表示受CTM影响，传入false表示不受CTM影响，
 * 标准差值固定。
 * @return 返回创建的蒙版滤波器对象的指针。
 * @since 11
 * @version 1.0
 */
OH_Drawing_MaskFilter* OH_Drawing_MaskFilterCreateBlur(OH_Drawing_BlurType blurType, float sigma, bool respectCTM);

/**
 * @brief 销毁蒙版滤波器对象，并收回该对象占用的内存。
 *
 * @param maskFilter 表示指向蒙版滤波器对象的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_MaskFilterDestroy(OH_Drawing_MaskFilter* maskFilter);

#ifdef __cplusplus
}
#endif
/** @} */
#endif