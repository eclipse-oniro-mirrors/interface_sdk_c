/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
 * @file drawing_filter.h
 *
 * @brief This file declares the functions related to the filter in the drawing module.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 11
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_FILTER_H
#define C_INCLUDE_DRAWING_FILTER_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建一个滤波器对象。
 *
 * @return 返回创建的滤波器对象的指针。
 * @since 11
 * @version 1.0
 */
OH_Drawing_Filter* OH_Drawing_FilterCreate(void);

/**
 * @brief 为滤波器对象设置图像滤波器对象。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * filter为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param filter 指示指向滤波器对象{@link OH_Drawing_Filter}的指针。
 * @param imageFilter 指示指向图像滤波器{@link OH_Drawing_ImageFilter}对象的指针，为NULL表示清空滤波器对象中的图像滤波器效果。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FilterSetImageFilter(OH_Drawing_Filter* filter, OH_Drawing_ImageFilter* imageFilter);

/**
 * @brief 为滤波器对象设置蒙版滤波器对象。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * filter为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param filter 指示指向滤波器对象{@link OH_Drawing_Filter}的指针。
 * @param maskFilter 指示指向蒙版滤波器对象{@link OH_Drawing_MaskFilter}的指针，为NULL表示清空滤波器对象中的蒙版滤波器效果。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_FilterSetMaskFilter(OH_Drawing_Filter* filter, OH_Drawing_MaskFilter* maskFilter);

/**
 * @brief 为滤波器对象设置颜色滤波器对象。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * filter为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param filter 指示指向滤波器对象{@link OH_Drawing_Filter}的指针。
 * @param colorFilter 指示指向颜色滤波器对象{@link OH_Drawing_ColorFilter}的指针，为NULL表示清空滤波器对象中的颜色滤波器效果。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_FilterSetColorFilter(OH_Drawing_Filter* filter, OH_Drawing_ColorFilter* colorFilter);

/**
 * @brief 从滤波器对象获取颜色滤波器对象。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * filter、colorFilter任意一个为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 *
 * @param filter 指示指向滤波器对象{@link OH_Drawing_Filter}的指针。
 * @param colorFilter 指示指向颜色滤波器对象{@link OH_Drawing_ColorFilter}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_FilterGetColorFilter(OH_Drawing_Filter* filter, OH_Drawing_ColorFilter* colorFilter);

/**
 * @brief 销毁滤波器对象，并收回该对象占用的内存。
 *
 * @param filter 指示指向滤波器对象{@link OH_Drawing_Filter}的指针。
 * @since 11
 * @version 1.0
 */
void OH_Drawing_FilterDestroy(OH_Drawing_Filter* filter);

#ifdef __cplusplus
}
#endif
/** @} */
#endif