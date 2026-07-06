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
 * @addtogroup NativeColorSpaceManager
 * @{
 *
 * @brief 提供创建色彩空间及获取色彩空间相关属性的能力。
 *
 * @since 13
 * @version 1.0
 */

/**
 * @file native_color_space_manager.h
 *
 * @brief 定义创建和使用色彩空间的相关函数。
 *
 * @kit ArkGraphics2D
 * @library libnative_color_space_manager.so
 * @syscap SystemCapability.Graphic.Graphic2D.ColorManager.Core
 * @since 13
 * @version 1.0
 */

#ifndef C_INCLUDE_NATIVE_COLOR_SPACE_MANAGER_H_
#define C_INCLUDE_NATIVE_COLOR_SPACE_MANAGER_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 提供OH_NativeColorSpaceManager结构体声明。
 *
 * @since 13
 */
typedef struct OH_NativeColorSpaceManager OH_NativeColorSpaceManager;

/**
 * @brief Defines an enum for the color space names.
 *
 * @since 13
 */
typedef enum {
    /**
     * 表示未知的色彩空间。
     */
    NONE = 0,
    /**
     * 表示基于Adobe RGB的色彩空间。
     */
    ADOBE_RGB = 1,
    /**
     * 表示基于SMPTE RP 431-2-2007和IEC 61966-2.1：1999的色彩空间。
     */
    DCI_P3 = 2,
    /**
     * 表示基于SMPTE RP 431-2-2007和IEC 61966-2.1：1999的色彩空间。
     */
    DISPLAY_P3 = 3,
    /**
     * 表示基于IEC 61966-2.1：1999的标准红绿蓝（SRGB）色彩空间。
     */
    SRGB = 4,
    /**
     * 表示基于ITU-R BT.709的色彩空间。
     */
    BT709 = 6,
    /**
     * 表示基于ITU-R BT.601的色彩空间。
     */
    BT601_EBU = 7,
    /**
     * 表示基于ITU-R BT.601的色彩空间。
     */
    BT601_SMPTE_C = 8,
    /**
     * 表示基于ITU-R BT.2020的色彩空间。
     */
    BT2020_HLG = 9,
    /**
     * 表示基于ITU-R BT.2020的色彩空间。
     */
    BT2020_PQ = 10,
    /**
     * 表示色彩原色为P3_D65，传输特性为HLG，色彩范围为Full的色彩空间。
     */
    P3_HLG = 11,
    /**
     * 表示色彩原色为P3_D65，传输特性为PQ，色彩范围为Full的色彩空间。
     */
    P3_PQ = 12,
    /**
     * 表示色彩原色为ADOBE_RGB，传输特性为ADOBE_RGB，色彩范围为LIMIT的色彩空间。
     */
    ADOBE_RGB_LIMIT = 13,
    /**
     * 表示色彩原色为P3_D65，传输特性为SRGB，色彩范围为LIMIT的色彩空间。
     */
    DISPLAY_P3_LIMIT = 14,
    /**
     * 表示色彩原色为SRGB，传输特性为SRGB，色彩范围为LIMIT的色彩空间。
     */
    SRGB_LIMIT = 15,
    /**
     * 表示色彩原色为BT709，传输特性为BT709，色彩范围为LIMIT的色彩空间。
     */
    BT709_LIMIT = 16,
    /**
     * 表示色彩原色为BT601_P，传输特性为BT709，色彩范围为LIMIT的色彩空间。
     */
    BT601_EBU_LIMIT = 17,
    /**
     * 表示色彩原色为BT601_N，传输特性为BT709，色彩范围为LIMIT的色彩空间。
     */
    BT601_SMPTE_C_LIMIT = 18,
    /**
     * 表示色彩原色为BT2020，传输特性为HLG，色彩范围为LIMIT的色彩空间。
     */
    BT2020_HLG_LIMIT = 19,
    /**
     * 表示色彩原色为BT2020，传输特性为PQ，色彩范围为LIMIT的色彩空间。
     */
    BT2020_PQ_LIMIT = 20,
    /**
     * 表示色彩原色为P3_D65，传输特性为HLG，色彩范围为LIMIT的色彩空间。
     */
    P3_HLG_LIMIT = 21,
    /**
     * 表示色彩原色为P3_D65，传输特性为PQ，色彩范围为LIMIT的色彩空间。
     */
    P3_PQ_LIMIT = 22,
    /**
     * 表示色彩原色为P3_D65，传输特性为LINEAR的色彩空间。
     */
    LINEAR_P3 = 23,
    /**
     * 表示色彩原色为SRGB，传输特性为LINEAR的色彩空间。
     */
    LINEAR_SRGB = 24,
    /**
     * 表示色彩原色为BT709，传输特性为LINEAR的色彩空间。
     */
    LINEAR_BT709 = LINEAR_SRGB,
    /**
     * 表示色彩原色为BT2020，传输特性为LINEAR的色彩空间。
     */
    LINEAR_BT2020 = 25,
    /**
     * 表示色彩原色为SRGB，传输特性为SRGB，色彩范围为Full的色彩空间。
     */
    DISPLAY_SRGB = SRGB,
    /**
     * 表示色彩原色为P3_D65，传输特性为SRGB，色彩范围为Full的色彩空间。
     */
    DISPLAY_P3_SRGB = DISPLAY_P3,
    /**
     * 表示色彩原色为P3_D65，传输特性为HLG，色彩范围为Full的色彩空间。
     */
    DISPLAY_P3_HLG = P3_HLG,
    /**
     * 表示色彩原色为P3_D65，传输特性为PQ，色彩范围为Full的色彩空间。
     */
    DISPLAY_P3_PQ = P3_PQ,
    /**
     * 表示色彩原色为BT2020，传输特性为LOG，色彩范围为Full的色彩空间。
     * @since 26.0.0
     */
    BT2020_LOG_FULL = 27,
    /**
     * 表示色彩原色为BT2020，传输特性为LOG，色彩范围为LIMIT的色彩空间。
     * @since 26.0.0
     */
    BT2020_LOG_LIMIT = 28,
    /**
     * 表示自定义色彩空间。
     */
    CUSTOM = 5,
} ColorSpaceName;

/**
 * @brief 提供色彩原色结构体声明
 *
 * @since 13
 */
typedef struct {
    /**
     * 红色的x轴坐标值。
     */
    float rX;
    /**
     * 红色的y轴坐标值。
     */
    float rY;
    /**
     * 绿色的x轴坐标值。
     */
    float gX;
    /**
     * 绿色的y轴坐标值。
     */
    float gY;
    /**
     * 蓝色的x轴坐标值。
     */
    float bX;
    /**
     * 蓝色的y轴坐标值。
     */
    float bY;
    /**
     * 白点的x轴坐标值。
     */
    float wX;
    /**
     * 白点的y轴坐标值。
     */
    float wY;
} ColorSpacePrimaries;

/**
 * @brief 提供白点数组结构体，白点是在当前色域中表示白色的坐标。
 *
 * @since 13
 */
typedef struct {
    /** 表示白点坐标数组。 */
    float arr[2];
} WhitePointArray;

/**
 * @brief 通过colorSpaceName创建OH_NativeColorSpaceManager实例。\n
 * 每次调用此函数时，都会创建一个新的OH_NativeColorSpaceManager实例。
 *
 * @param colorSpaceName 表示创建OH_NativeColorSpaceManager的色彩空间名称。
 * @return 返回一个指向OH_NativeColorSpaceManager实例的指针。内存不足时，会导致创建OH_NativeColorSpaceManager实例失败。
 * @since 13
 * @version 1.0
 */
OH_NativeColorSpaceManager* OH_NativeColorSpaceManager_CreateFromName(ColorSpaceName colorSpaceName);

/**
 * @brief 通过原色和伽马值创建OH_NativeColorSpaceManager实例。\n
 * 每次调用此函数时，都会创建一个新的OH_NativeColorSpaceManager实例。
 *
 * @param primaries 表示创建OH_NativeColorSpaceManager的色彩原色。
 * @param gamma 表示创建OH_NativeColorSpaceManager的伽马值，伽马值为一个浮点数，用于校正亮度范围。\n
 * 伽马值通常为正值，负值会使弱光区域更亮，强光区域变暗，伽马值为0.0表示线性色彩空间。
 * @return 返回一个指向OH_NativeColorSpaceManager实例的指针。
 * 内存不足时，会导致创建OH_NativeColorSpaceManager实例失败。
 * @since 13
 * @version 1.0
 */
OH_NativeColorSpaceManager* OH_NativeColorSpaceManager_CreateFromPrimariesAndGamma(
    ColorSpacePrimaries primaries, float gamma);

/**
 * @brief 销毁OH_NativeColorSpaceManager实例。
 *
 * @param nativeColorSpaceManager 表示指向OH_NativeColorSpaceManager实例的指针。
 * @since 13
 * @version 1.0
 */
void OH_NativeColorSpaceManager_Destroy(OH_NativeColorSpaceManager* nativeColorSpaceManager);

/**
 * @brief 获取色彩空间名称。
 *
 * @param nativeColorSpaceManager 表示指向OH_NativeColorSpaceManager实例的指针。
 * @return 返回色彩空间枚举{@link ColorSpaceName}对应的值。其中，当返回值为0时，表示接口操作失败。
 * @since 13
 * @version 1.0
 */
int OH_NativeColorSpaceManager_GetColorSpaceName(
    OH_NativeColorSpaceManager* nativeColorSpaceManager);

/**
 * @brief 获取白点。
 *
 * @param nativeColorSpaceManager 表示指向OH_NativeColorSpaceManager实例的指针。
 * @return 返回值为float数组，返回值为<0.0, 0.0>表示接口操作失败，其余返回值表示操作成功。
 * @since 13
 * @version 1.0
 */
WhitePointArray OH_NativeColorSpaceManager_GetWhitePoint(
    OH_NativeColorSpaceManager* nativeColorSpaceManager);

/**
 * @brief 获取伽马值。
 *
 * @param nativeColorSpaceManager 表示指向OH_NativeColorSpaceManager实例的指针。
 * @return 返回值为float类型，返回值为0.0表示接口操作失败，其余返回值表示操作成功。
 * @since 13
 * @version 1.0
 */
float OH_NativeColorSpaceManager_GetGamma(OH_NativeColorSpaceManager* nativeColorSpaceManager);

#ifdef __cplusplus
}
#endif

/** @} */
#endif