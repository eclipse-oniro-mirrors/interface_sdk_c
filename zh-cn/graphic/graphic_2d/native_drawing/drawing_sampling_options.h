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
 * @since 12
 * @version 1.0
 */
/**
 * @file drawing_sampling_options.h
 *
 * @brief This file declares the functions related to sampling in the drawing module. It is used for image or texture
 * sampling.
 *
 * @kit ArkGraphics2D
 * @library libnative_drawing.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeDrawing
 * @since 12
 * @version 1.0
 */

#ifndef C_INCLUDE_DRAWING_SAMPLING_OPTIONS_H
#define C_INCLUDE_DRAWING_SAMPLING_OPTIONS_H

#include "drawing_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 过滤模式枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 邻近过滤模式。
     */
    FILTER_MODE_NEAREST,
    /**
     * 线性过滤模式。
     */
    FILTER_MODE_LINEAR,
} OH_Drawing_FilterMode;

/**
 * @brief 多级渐远纹理模式枚举。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 忽略多级渐远纹理级别。
     */
    MIPMAP_MODE_NONE,
    /**
     * 邻近多级渐远级别采样。
     */
    MIPMAP_MODE_NEAREST,
    /**
     * 两个邻近多级渐远纹理之间，线性插值采样。
     */
    MIPMAP_MODE_LINEAR,
} OH_Drawing_MipmapMode;

/**
 * @brief 创建一个采样选项对象。
 * 本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * mipmapMode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 *
 * @param filterMode 过滤采样模式{@link OH_Drawing_FilterMode}。
 * @param mipmapMode 多级渐远纹理采样模式{@link OH_Drawing_MipmapMode}。
 * @return 函数会返回一个指针，指针指向创建的采样选项对象{@link OH_Drawing_SamplingOptions}。
 * @since 12
 * @version 1.0
 */
OH_Drawing_SamplingOptions* OH_Drawing_SamplingOptionsCreate(OH_Drawing_FilterMode filterMode,
    OH_Drawing_MipmapMode mipmapMode);

/**
 * @brief 创建一个采样选项对象副本{@link OH_Drawing_SamplingOptions}，用于拷贝一个已有采样选项对象。
 *
 * @param samplingOptions 指向采样选项对象{@link OH_Drawing_SamplingOptions}的指针。
 * @return 函数会返回一个指针，指针指向创建的采样选项对象副本{@link OH_Drawing_SamplingOptions}。如果对象返回NULL，表示创建失败；可能的原因是可用内存为空，
 * 或者是samplingOptions为NULL。
 * @since 20
 * @version 1.0
 */
OH_Drawing_SamplingOptions* OH_Drawing_SamplingOptionsCopy(OH_Drawing_SamplingOptions* samplingOptions);

/**
 * @brief 销毁采样选项对象并回收该对象占有内存。
 *
 * @param samplingOptions 指向采样选项对象{@link OH_Drawing_SamplingOptions}的指针。
 * @since 12
 * @version 1.0
 */
void OH_Drawing_SamplingOptionsDestroy(OH_Drawing_SamplingOptions* samplingOptions);

#ifdef __cplusplus
}
#endif
/** @} */
#endif