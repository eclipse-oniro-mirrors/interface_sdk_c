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
 * @brief Provides APIs for obtaining effect filter and information.
 * @syscap SystemCapability.Multimedia.Image.Core
 * @since 12
 */

/**
 * @file effect_types.h
 *
 * @brief This file declares the data types of the image effect filter.
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
 * @brief 滤镜结构体，用来生成滤镜位图。
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
 * @brief 定义一个用来创建滤镜效果的矩阵。
 *
 * @since 12
 * @version 1.0
 */
typedef struct OH_Filter_ColorMatrix {
    /** 自定义颜色矩阵，值为 5 x 4 的数组 */
    float val[20];
} OH_Filter_ColorMatrix;

/**
 * @brief 定义滤镜效果的状态码。
 *
 * @since 12
 * @version 1.0
 */
typedef enum {
    /** 成功。 */
    EFFECT_SUCCESS = 0,
    /** 无效的参数。 */
    EFFECT_BAD_PARAMETER = 401,
    /** 不支持的操作。 */
    EFFECT_UNSUPPORTED_OPERATION = 7600201,
    /** 未知错误。 */
    EFFECT_UNKNOWN_ERROR = 7600901
} EffectErrorCode;

/**
 * @brief 定义着色器效果平铺模式的枚举。
 *
 * @since 14
 */
typedef enum {
    /** 如果着色器效果超出其原始边界，剩余区域使用着色器的边缘颜色填充。 */
    CLAMP = 0,
    /** 在水平和垂直方向上重复着色器效果。 */
    REPEAT,
    /** 在水平和垂直方向上重复着色器效果，交替镜像图像，以便相邻图像始终接合。 */
    MIRROR,
    /** 仅在其原始边界内渲染着色器效果。 */
    DECAL
} EffectTileMode;

#ifdef __cplusplus
}
#endif

/** @} */
#endif