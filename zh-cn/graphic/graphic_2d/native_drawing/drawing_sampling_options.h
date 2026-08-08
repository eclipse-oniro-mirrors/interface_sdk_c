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
 * @brief 文件中定义了与采样选项相关的功能函数，用于创建、拷贝和销毁采样选项对象，
 * 以及指定图像采样时的过滤模式和纹理采样时的多级渐远纹理模式。
 * <br>本模块为单线程模型策略，需要调用方自行管理线程安全和上下文状态的切换。
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
     * 邻近过滤模式，采用最近邻采样，使用距离采样点最近的像素值。适合对性能要求高、对画面平滑度要求不高的场景。
     */
    FILTER_MODE_NEAREST,
    /**
     * 线性过滤模式，采用线性插值采样，在相邻像素之间进行插值计算。适合对画面平滑度和质量要求较高的场景。
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
     * 忽略多级渐远纹理级别。适合不使用多级渐远纹理的场景。
     */
    MIPMAP_MODE_NONE,
    /**
     * 邻近多级渐远纹理级别采样。适合性能优先的场景。
     */
    MIPMAP_MODE_NEAREST,
    /**
     * 两个邻近多级渐远纹理级别之间，线性插值采样。适合对画质要求较高的场景。
     */
    MIPMAP_MODE_LINEAR,
} OH_Drawing_MipmapMode;

/**
 * @brief 创建一个采样选项对象。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>mipmapMode不在枚举范围内时返回OH_DRAWING_ERROR_PARAMETER_OUT_OF_RANGE。
 * <br>使用完毕后，必须调用{@link OH_Drawing_SamplingOptionsDestroy}销毁采样选项对象并释放内存，避免内存泄漏。
 *
 * @param filterMode 过滤采样模式。
 * @param mipmapMode 多级渐远纹理采样模式。
 * @return 函数会返回一个指针，指针指向创建的采样选项对象{@link OH_Drawing_SamplingOptions}。如果返回NULL，
 * 表示创建失败；可能的原因是可用内存不足，或者是mipmapMode不在枚举范围内。
 * @since 12
 * @version 1.0
 */
OH_Drawing_SamplingOptions* OH_Drawing_SamplingOptionsCreate(OH_Drawing_FilterMode filterMode,
    OH_Drawing_MipmapMode mipmapMode);

/**
 * @brief 创建一个采样选项对象副本{@link OH_Drawing_SamplingOptions}，用于拷贝一个已有采样选项对象。
 * <br>本接口会产生错误码，可以通过{@link OH_Drawing_ErrorCodeGet}查看错误码的取值。
 * <br>samplingOptions为NULL时返回OH_DRAWING_ERROR_INVALID_PARAMETER。
 * <br>拷贝对象为独立的新对象，使用完毕后，必须调用{@link OH_Drawing_SamplingOptionsDestroy}销毁副本对象并释放内存，
 * 避免内存泄漏。
 *
 * @param samplingOptions 指向采样选项对象OH_Drawing_SamplingOptions的指针。
 * @return 函数会返回一个指针，指针指向创建的采样选项拷贝对象{@link OH_Drawing_SamplingOptions}。如果返回NULL，表示创建失败；
 * 可能的原因是可用内存不足，或者是samplingOptions为NULL。
 * @since 20
 * @version 1.0
 */
OH_Drawing_SamplingOptions* OH_Drawing_SamplingOptionsCopy(OH_Drawing_SamplingOptions* samplingOptions);

/**
 * @brief 销毁采样选项对象，并回收该对象占用的内存。
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