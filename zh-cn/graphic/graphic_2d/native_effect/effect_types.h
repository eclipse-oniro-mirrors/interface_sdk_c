/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup effectKit
 *
 * @{
 *
 * @brief 提供处理图像的基础能力，支持亮度调节、模糊化、灰度转换等效果。
 * 适用于需要在应用内快速实现图像滤镜效果的场景，如图像编辑、照片美化和相机滤镜等，
 * 开发者无需关注底层算法实现即可快速完成图像效果处理功能，降低开发复杂度。
 *
 * @since 12
 */

/**
 * @file effect_types.h
 *
 * @brief 声明滤镜效果的数据类型，用于定义滤镜效果的矩阵、状态码和平铺模式等，
 * 支持创建自定义滤镜效果、处理图像着色器平铺等场景。
 *
 * @kit ArkGraphics2D
 * @library libnative_effect.so
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 12
 */

#ifndef C_INCLUDE_EFFECT_TYPES_H
#define C_INCLUDE_EFFECT_TYPES_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 滤镜结构体，用于配合effectKit模块相关接口实现滤镜效果处理。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Filter OH_Filter;

/**
 * @brief 声明由图像框架定义的像素图对象。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_PixelmapNative OH_PixelmapNative;

/**
 * @brief 定义用于创建滤镜效果的矩阵，矩阵维度为4x5，元素取值范围为浮点数。
 *
 * @since 12
 * @version 1.0
 */
struct OH_Filter_ColorMatrix {
    /**
     * 自定义颜色矩阵，用于实现图像颜色变换效果。数组包含20个float类型元素，
     * 按行优先顺序存储，组成4行5列矩阵。
     * 前4列对应R、G、B、A通道的变换系数，第5列为常量偏移值。建议元素取值为
     * [-1, 1]，超出此范围可能导致颜色值溢出或产生非预期效果。
     */
    float val[20];
};

/**
 * @brief 定义滤镜效果的状态码。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /** 操作成功完成。 */
    EFFECT_SUCCESS = 0,
    /** 参数错误，请检查参数类型和范围。 */
    EFFECT_BAD_PARAMETER = 401,
    /** 当前操作不被支持，请检查API使用方式。 */
    EFFECT_UNSUPPORTED_OPERATION = 7600201,
    /** 发生了未被明确识别的错误，可能原因包括系统资源异常、API调用方式不当等。
     *  建议先检查API调用参数和系统资源状态。 */
    EFFECT_UNKNOWN_ERROR = 7600901,
} EffectErrorCode;

/**
 * @brief 定义着色器效果平铺模式的枚举。
 *
 * @since 14
 */
typedef enum {
    /** 边缘拉伸模式，如果着色器效果超出其原始边界，剩余区域使用着色器的边缘颜色
     *  填充。适用于需要平滑过渡到纯色背景的场景。 */
    CLAMP = 0,
    /** 平铺重复模式，在水平和垂直方向上重复着色器效果。适用于需要无缝平铺纹理
     *  的场景，如背景图案填充。 */
    REPEAT,
    /** 镜像平铺模式，在水平和垂直方向上重复着色器效果，交替镜像图像，以便相邻
     *  图像始终接合。适用于需要连续但避免生硬重复边缘的场景，如渐变背景。 */
    MIRROR,
    /** 贴花模式，仅在其原始边界内渲染着色器效果。适用于需要精确控制着色器边界
     *  的场景，边界外保持透明或原有内容。 */
    DECAL,
} EffectTileMode;

#ifdef __cplusplus
}
#endif

/** @} */
#endif