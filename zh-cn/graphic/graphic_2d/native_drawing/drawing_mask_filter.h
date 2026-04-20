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
 * @file drawing_mask_filter.h
 *
 * @brief This file declares the functions related to the mask filter in the drawing module.
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
     * 内部实体，外部模糊。
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
 * @brief 创建具有模糊效果的蒙版滤波器。
 *
 * @param blurType 表示模糊类型。
 * @param sigma 表示要应用的高斯模糊的标准偏差。必须大于0。
 * @param respectCTM 表示模糊标准差值被CTM（当前变换矩阵）修改，默认为真。true表示模糊标准差值受CTM影响，false表示模糊标准差值固定，不受CTM影响。
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