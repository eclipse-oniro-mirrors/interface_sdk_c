/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Defines a set of Swiper enum and interface.
 *
 * @since 12
 */

/**
 * @file swiper.h
 *
 * @brief 定义Swiper组件的枚举和接口。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义Swiper组件的导航指示器风格。
 *
 * @since 12
 */
typedef struct ArkUI_SwiperIndicator ArkUI_SwiperIndicator;

/**
 * @brief 定义Swiper组件的数字导航指示器风格。
 *
 * @since 19
 */
typedef struct ArkUI_SwiperDigitIndicator ArkUI_SwiperDigitIndicator;

/**
 * @brief 定义Swiper组件的导航箭头风格。
 *
 * @since 19
 */
typedef struct ArkUI_SwiperArrowStyle ArkUI_SwiperArrowStyle;

/**
 * @brief Swiper导航点箭头枚举值。
 *
 * @since 12
 */
typedef enum {
    /**
     * 不显示swiper中导航点箭头。
     * @since 12
     */
    ARKUI_SWIPER_ARROW_HIDE = 0,
    /**
     * 显示swiper中导航点箭头。
     * @since 12
     */
    ARKUI_SWIPER_ARROW_SHOW,
    /**
     * 在hover状态下显示swiper中导航点箭头。
     * @since 12
     */
    ARKUI_SWIPER_ARROW_SHOW_ON_HOVER
} ArkUI_SwiperArrow;

/**
 * @brief Swiper组件和父组件的嵌套滚动模式。
 *
 * @since 12
 */
typedef enum {
    /**
     * Swiper只自身滚动，不与父组件联动。
     * @since 12
     */
    ARKUI_SWIPER_NESTED_SRCOLL_SELF_ONLY = 0,
    /**
     * Swiper自身先滚动，自身滚动到边缘以后父组件滚动。父组件滚动到边缘以后，如果父组件有边缘效果，则父组件触发边缘效果，否则Swiper触发边缘效果。
     * @since 12
     */
    ARKUI_SWIPER_NESTED_SRCOLL_SELF_FIRST
} ArkUI_SwiperNestedScrollMode;

/**
 * @brief Swiper组件鼠标滚轮翻页模式。
 *
 * @since 15
 */
typedef enum {
    /**
     * 鼠标滚轮连续滚动时翻多页，根据鼠标事件上报次数确定。
     * @since 15
     */
    ARKUI_PAGE_FLIP_MODE_CONTINUOUS = 0,
    /**
     * 一次翻页动画结束前不响应其他鼠标滚轮事件。
     * @since 15
     */
    ARKUI_PAGE_FLIP_MODE_SINGLE
} ArkUI_PageFlipMode;

/**
 * @brief Swiper组件跳转到目标index的动画模式。
 *
 * @since 15
 */
typedef enum {
    /**
     * 无动画跳转到目标index。
     * @since 15
     */
    ARKUI_SWIPER_NO_ANIMATION = 0,
    /**
     * 做动画跳转到目标index。
     * @since 15
     */
    ARKUI_SWIPER_DEFAULT_ANIMATION = 1,
    /**
     * 先无动画跳转到目标附近再做动画跳转到目标index。
     * @since 15
     */
    ARKUI_SWIPER_FAST_ANIMATION = 2
} ArkUI_SwiperAnimationMode;

/**
 * @brief 定义Swiper组件的导航指示器类型。
 *
 * @since 12
 */
typedef enum {
    /**
     * 圆点指示器类型。
     * @since 12
     */
    ARKUI_SWIPER_INDICATOR_TYPE_DOT,
    /**
     * 数字指示器类型。
     * @since 12
     */
    ARKUI_SWIPER_INDICATOR_TYPE_DIGIT
} ArkUI_SwiperIndicatorType;

/**
 * @brief 创建Swiper组件的导航指示器。
 *
 * @param type 导航指示器的类型。
 * @return 导航指示器对象指针。
 * @since 12
 */
ArkUI_SwiperIndicator* OH_ArkUI_SwiperIndicator_Create(ArkUI_SwiperIndicatorType type);

/**
 * @brief 销毁Swiper组件的导航指示器指针。
 *
 * @param indicator 导航指示器对象指针。
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_Dispose(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置导航点距离Swiper组件左边的距离。
 *
 * @param indicator 导航指示器对象指针。
 * @param value 导航点距离Swiper组件左边的距离。默认值：0，单位：vp。
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetStartPosition(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief 获取导航点距离Swiper组件左边的距离。
 *
 * @param indicator 导航指示器对象指针。
 * @return 导航点距离Swiper组件左边的距离。单位：vp。
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetStartPosition(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置导航点距离Swiper组件顶部的距离。
 *
 * @param indicator 导航指示器对象指针。
 * @param value 导航点距离Swiper组件顶部的距离。默认值：0，单位：vp。
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetTopPosition(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief 获取导航点距离Swiper组件顶部的距离。
 *
 * @param indicator 导航指示器对象指针。
 * @return 导航点距离Swiper组件顶部的距离。单位：vp。
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetTopPosition(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置导航点距离Swiper组件右边的距离。
 *
 * @param indicator 导航指示器对象指针。
 * @param value 导航点距离Swiper组件右边的距离。默认值：0，单位：vp。
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetEndPosition(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief 获取导航点距离Swiper组件右边的距离。
 *
 * @param indicator 导航指示器对象指针。
 * @return 导航点距离Swiper组件右边的距离。单位：vp。
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetEndPosition(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置导航点距离Swiper组件底部的距离。
 *
 * @param indicator 导航指示器对象指针。
 * @param value 导航点距离Swiper组件底部的距离。默认值：0，单位：vp。
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetBottomPosition(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief 获取导航点距离Swiper组件底部的距离。
 *
 * @param indicator 导航指示器对象指针。
 * @return 导航点距离Swiper组件底部的距离。单位：vp。
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetBottomPosition(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置点指示器的点的宽度。
 *
 * @param indicator 导航指示器对象指针。
 * @param value 圆点导航指示器的宽。默认值：12，单位：vp。
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetItemWidth(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief 获取Swiper组件圆点导航指示器的宽。
 *
 * @param indicator 导航指示器对象指针。
 * @return 圆点导航指示器的宽。单位：vp。
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetItemWidth(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置Swiper组件圆点导航指示器的高。
 *
 * @param indicator 导航指示器对象指针。
 * @param value 圆点导航指示器的高。默认值：6，单位：vp。
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetItemHeight(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief 获取Swiper组件圆点导航指示器的高。
 *
 * @param indicator 导航指示器对象指针。
 * @return 圆点导航指示器的高。单位：vp。
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetItemHeight(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置被选中的Swiper组件圆点导航指示器的宽。
 *
 * @param indicator 导航指示器对象指针。
 * @param value 圆点导航指示器的宽。默认值：12，单位：vp。
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetSelectedItemWidth(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief 获取被选中Swiper组件圆点导航指示器的宽。
 *
 * @param indicator 导航指示器对象指针。
 * @return 圆点导航指示器的宽。单位：vp。
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetSelectedItemWidth(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置被选中的Swiper组件圆点导航指示器的高。
 *
 * @param indicator 导航指示器对象指针。
 * @param value 圆点导航指示器的高。默认值：6，单位：vp。
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetSelectedItemHeight(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief 获取被选中Swiper组件圆点导航指示器的高。
 *
 * @param indicator 导航指示器对象指针。
 * @return 圆点导航指示器的高。单位：vp。
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetSelectedItemHeight(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置是否显示Swiper组件圆点导航指示器的蒙版样式。
 *
 * @param indicator 导航指示器对象指针。
 * @param mask 是否显示蒙版样式，1表示显示，0表示不显示。
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetMask(ArkUI_SwiperIndicator* indicator, int32_t mask);

/**
 * @brief 获取是否显示Swiper组件圆点导航指示器的蒙版样式。
 *
 * @param indicator 导航指示器对象指针。
 * @return 1表示显示圆点导航指示器的蒙版样式，0表示不显示。
 * @since 12
 */
int32_t OH_ArkUI_SwiperIndicator_GetMask(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置Swiper组件圆点导航指示器的颜色。
 *
 * @param indicator 导航指示器对象指针。
 * @param color 颜色类型，0xargb格式，形如 0xFFFF0000表示红色。
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetColor(ArkUI_SwiperIndicator* indicator, uint32_t color);

/**
 * @brief 获取Swiper组件圆点导航指示器的颜色。
 *
 * @param indicator 导航指示器对象指针。
 * @return 颜色类型，0xargb格式，形如 0xFFFF0000表示红色。
 * @since 12
 */
uint32_t OH_ArkUI_SwiperIndicator_GetColor(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置被选中Swiper组件圆点导航指示器的颜色。
 *
 * @param indicator 导航指示器对象指针。
 * @param selectedColor 颜色类型，0xargb格式，形如 0xFFFF0000表示红色。
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetSelectedColor(ArkUI_SwiperIndicator* indicator, uint32_t selectedColor);

/**
 * @brief 获取被选中Swiper组件圆点导航指示器的颜色。
 *
 * @param indicator 导航指示器对象指针。
 * @return 颜色类型，0xargb格式，形如 0xFFFF0000表示红色。
 * @since 12
 */
uint32_t OH_ArkUI_SwiperIndicator_GetSelectedColor(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置圆点导航点指示器样式下，导航点显示个数的最大值。
 *
 * @param indicator 导航指示器对象指针。
 * @param maxDisplayCount 导航点显示个数最大值，有效取值范围[6, 9]。
 * @return 错误码。
 *          {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *          {@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果maxDisplayCount设置范围错误, 返回错误码。
 * @since 12
 */
int32_t OH_ArkUI_SwiperIndicator_SetMaxDisplayCount(ArkUI_SwiperIndicator* indicator, int32_t maxDisplayCount);

/**
 * @brief 获取圆点导航点指示器样式下，导航点显示个数的最大值。
 *
 * @param indicator 导航指示器对象指针。
 * @return 导航点显示个数最大值，有效取值范围[6, 9]。
 * @since 12
 */
int32_t OH_ArkUI_SwiperIndicator_GetMaxDisplayCount(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置OH_ArkUI_SwiperIndicator_SetBottomPosition是否忽略导航点大小。
 *
 * @param indicator 导航指示器对象指针。
 * @param ignoreSize 是否忽略导航点大小。1表示忽略导航点大小，0表示不忽略，默认值0。
 * @since 19
 */
void OH_ArkUI_SwiperIndicator_SetIgnoreSizeOfBottom(ArkUI_SwiperIndicator* indicator, int32_t ignoreSize);

/**
 * @brief 获取OH_ArkUI_SwiperIndicator_SetBottomPosition是否忽略导航点大小。
 *
 * @param indicator 导航指示器对象指针。
 * @return 是否忽略导航点大小。
 * @since 19
 */
int32_t OH_ArkUI_SwiperIndicator_GetIgnoreSizeOfBottom(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 设置导航点间距。
 *
 * @param indicator 导航指示器对象指针。
 * @param space 导航点间距。默认值：8，单位：vp。
 * @since 19
 */
void OH_ArkUI_SwiperIndicator_SetSpace(ArkUI_SwiperIndicator* indicator, float space);

/**
 * @brief Obtains 导航点间距。单位：vp。.
 *
 * @param indicator 导航指示器对象指针。
 * @return 导航点间距。单位：vp。
 * @since 19
 */
float OH_ArkUI_SwiperIndicator_GetSpace(ArkUI_SwiperIndicator* indicator);

/**
 * @brief 创建Swiper组件的数字导航指示器。
 *
 * @return 数字导航指示器对象指针。
 * @since 19
 */
ArkUI_SwiperDigitIndicator *OH_ArkUI_SwiperDigitIndicator_Create();

/**
 * @brief 设置数字导航指示器距离Swiper组件左边的距离，在从右至左显示的语言模式下，设置其距离Swiper组件右边的距离。
 *
 * @param indicator 数字导航指示器对象指针。
 * @param value 数字导航指示器距离Swiper组件左边的距离，在从右至左显示的语言模式下，其距离Swiper组件右边的距离。默认值：0，单位：vp。
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetStartPosition(ArkUI_SwiperDigitIndicator* indicator, float value);

/**
 * @brief 获取数字导航指示器距离Swiper组件左边的距离，在从右至左显示的语言模式下，获取其距离Swiper组件右边的距离。
 *
 * @param indicator 数字导航指示器对象指针。
 * @return 数字导航指示器距离Swiper组件左边的距离，在从右至左显示的语言模式下，其距离Swiper组件右边的距离。单位：vp。
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetStartPosition(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief 设置数字导航指示器距离Swiper组件顶部的距离。
 *
 * @param indicator 数字导航指示器对象指针。
 * @param value 数字导航指示器距离Swiper组件顶部的距离。默认值：0，单位：vp。
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetTopPosition(ArkUI_SwiperDigitIndicator* indicator, float value);

/**
 * @brief 获取数字导航指示器距离Swiper组件顶部的距离。
 *
 * @param indicator 数字导航指示器对象指针。
 * @return 数字导航指示器距离Swiper组件顶部的距离。单位：vp。
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetTopPosition(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief 设置数字导航指示器距离Swiper组件右边的距离，在从右至左显示的语言模式下，设置其距离Swiper组件左边的距离。
 *
 * @param indicator 数字导航指示器对象指针。
 * @param value 数字导航指示器距离Swiper组件右边的距离，在从右至左显示的语言模式下，其距离Swiper组件左边的距离。默认值：0，单位：vp。
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetEndPosition(ArkUI_SwiperDigitIndicator* indicator, float value);

/**
 * @brief 获取数字导航指示器距离Swiper组件右边的距离，在从右至左显示的语言模式下，获取其距离Swiper组件左边的距离。
 *
 * @param indicator 数字导航指示器对象指针。
 * @return 数字导航指示器距离Swiper组件右边的距离，在从右至左显示的语言模式下，其距离Swiper组件左边的距离。单位：vp。
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetEndPosition(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief 设置数字导航指示器距离Swiper组件底部的距离。
 *
 * @param indicator 数字导航指示器对象指针。
 * @param value 数字导航指示器距离Swiper组件底部的距离。默认值：0，单位：vp。
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetBottomPosition(ArkUI_SwiperDigitIndicator* indicator, float value);

/**
 * @brief 获取数字导航指示器距离Swiper组件底部的距离。
 *
 * @param indicator 数字导航指示器对象指针。
 * @return 数字导航指示器距离Swiper组件底部的距离。单位：vp。
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetBottomPosition(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief 设置Swiper组件数字导航指示器字体颜色。
 *
 * @param indicator 数字导航指示器对象指针。
 * @param color 颜色类型，0xargb格式，形如 0xFFFF0000表示红色。默认值：0xFF182431。
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetFontColor(ArkUI_SwiperDigitIndicator* indicator, uint32_t color);

/**
 * @brief 获取Swiper组件数字导航指示器字体颜色。
 *
 * @param indicator 数字导航指示器对象指针。
 * @return 颜色类型，0xargb格式，形如 0xFFFF0000表示红色。
 * @since 19
 */
uint32_t OH_ArkUI_SwiperDigitIndicator_GetFontColor(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief 设置被选中Swiper组件数字导航指示器字体颜色。
 *
 * @param indicator 数字导航指示器对象指针。
 * @param selectedColor 颜色类型，0xargb格式，形如 0xFFFF0000表示红色。默认值：0xFF182431。
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetSelectedFontColor(ArkUI_SwiperDigitIndicator* indicator, uint32_t selectedColor);

/**
 * @brief 获取被选中Swiper组件数字导航指示器字体颜色。
 *
 * @param indicator 数字导航指示器对象指针。
 * @return 颜色类型，0xargb格式，形如 0xFFFF0000表示红色。
 * @since 19
 */
uint32_t OH_ArkUI_SwiperDigitIndicator_GetSelectedFontColor(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief 设置Swiper组件数字导航指示器字体大小。
 *
 * @param indicator 数字导航指示器对象指针。
 * @param size 字体大小数值，单位为fp。
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetFontSize(ArkUI_SwiperDigitIndicator* indicator, float size);

/**
 * @brief 获取Swiper组件数字导航指示器字体大小。
 *
 * @param indicator 数字导航指示器对象指针。
 * @return 字体大小数值，单位为fp。
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetFontSize(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief 设置被选中Swiper组件数字导航指示器字体大小。
 *
 * @param indicator 数字导航指示器对象指针。
 * @param size 字体大小数值，单位为fp。
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetSelectedFontSize(ArkUI_SwiperDigitIndicator* indicator, float size);

/**
 * @brief 获取被选中Swiper组件数字导航指示器字体大小。
 *
 * @param indicator 数字导航指示器对象指针。
 * @return 字体大小数值，单位为fp。
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetSelectedFontSize(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief 销毁Swiper组件的数字导航指示器指针。
 *
 * @param indicator 数字导航指示器对象指针。
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_Destroy(ArkUI_SwiperDigitIndicator *indicator);

/**
 * @brief 设置OH_ArkUI_SwiperDigitIndicator_SetBottomPosition是否忽略导航点大小。
 *
 * @param indicator 导航指示器对象指针。
 * @param ignoreSize 是否忽略导航点大小。1表示忽略导航点大小，0表示不忽略，默认值0。
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetIgnoreSizeOfBottom(ArkUI_SwiperDigitIndicator* indicator, int32_t ignoreSize);

/**
 * @brief 获取OH_ArkUI_SwiperDigitIndicator_SetBottomPosition是否忽略导航点大小。
 *
 * @param indicator 导航指示器对象指针。
 * @return 是否忽略导航点大小。
 * @since 19
 */
int32_t OH_ArkUI_SwiperDigitIndicator_GetIgnoreSizeOfBottom(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief 创建Swiper组件的导航箭头。
 *
 * @return 导航箭头对象指针。
 * @since 19
 */
ArkUI_SwiperArrowStyle *OH_ArkUI_SwiperArrowStyle_Create();

/**
 * @brief 设置Swiper组件导航箭头底板是否显示。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @param showBackground 导航箭头底板是否显示，0：不显示，1：显示，默认值：0。
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetShowBackground(ArkUI_SwiperArrowStyle *arrowStyle, int32_t showBackground);

/**
 * @brief 获取Swiper组件导航箭头底板是否显示。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @return 导航箭头底板是否显示，0：不显示，1：显示。
 * @since 19
 */
int32_t OH_ArkUI_SwiperArrowStyle_GetShowBackground(ArkUI_SwiperArrowStyle* arrowStyle);

/**
 * @brief 设置Swiper组件导航箭头显示位置。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @param showSidebarMiddle 导航箭头显示位置，0：显示在导航指示器两侧，1：显示在Swiper组件两侧，默认值：0。
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetShowSidebarMiddle(ArkUI_SwiperArrowStyle* arrowStyle, int32_t showSidebarMiddle);

/**
 * @brief 获取Swiper组件导航箭头显示位置。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @return 导航箭头显示位置，0：显示在导航指示器两侧，1：显示在Swiper组件两侧。
 * @since 19
 */
int32_t OH_ArkUI_SwiperArrowStyle_GetShowSidebarMiddle(ArkUI_SwiperArrowStyle* arrowStyle);

/**
 * @brief 设置Swiper组件导航箭头底板大小。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @param backgroundSize 导航箭头底板大小，单位：vp。默认值：显示在导航指示器两侧24vp，显示在Swiper两侧32vp。
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetBackgroundSize(ArkUI_SwiperArrowStyle* arrowStyle, float backgroundSize);

/**
 * @brief 获取Swiper组件导航箭头底板大小。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @return 导航箭头底板大小，单位：vp。
 * @since 19
 */
float OH_ArkUI_SwiperArrowStyle_GetBackgroundSize(ArkUI_SwiperArrowStyle *arrowStyle);

/**
 * @brief 销毁Swiper组件的导航箭头指针。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_Destroy(ArkUI_SwiperArrowStyle *arrowStyle);

/**
 * @brief 设置Swiper组件导航箭头底板颜色。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @param backgroundColor 导航箭头底板颜色，0xargb格式，形如 0xFFFF0000表示红色。默认值：显示在导航指示器两侧为0x00000000，显示在Swiper两侧为0x19182431。
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetBackgroundColor(ArkUI_SwiperArrowStyle *arrowStyle, uint32_t backgroundColor);

/**
 * @brief 获取Swiper组件导航箭头底板颜色。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @return 导航箭头底板颜色，0xargb格式，形如 0xFFFF0000表示红色。
 * @since 19
 */
uint32_t OH_ArkUI_SwiperArrowStyle_GetBackgroundColor(ArkUI_SwiperArrowStyle* arrowStyle);

/**
 * @brief 设置Swiper组件导航箭头大小。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @param arrowSize 导航箭头大小，单位：vp。默认值：显示在导航指示器两侧18vp，显示在Swiper两侧24vp。
 * 显示导航箭头底板时，arrowSize固定为backgroundSize的3/4。
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetArrowSize(ArkUI_SwiperArrowStyle* arrowStyle, float arrowSize);

/**
 * @brief 获取Swiper组件导航箭头大小。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @return 导航箭头大小，单位：vp。
 * @since 19
 */
float OH_ArkUI_SwiperArrowStyle_GetArrowSize(ArkUI_SwiperArrowStyle* arrowStyle);

/**
 * @brief 设置Swiper组件导航箭头颜色。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @param arrowColor 导航箭头颜色，0xargb格式，形如 0xFFFF0000表示红色。
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetArrowColor(ArkUI_SwiperArrowStyle* arrowStyle, uint32_t arrowColor);

/**
 * @brief 获取Swiper组件导航箭头颜色。
 *
 * @param arrowStyle 导航箭头对象指针。
 * @return 导航箭头颜色，0xargb格式，形如 0xFFFF0000表示红色。
 * @since 19
 */
uint32_t OH_ArkUI_SwiperArrowStyle_GetArrowColor(ArkUI_SwiperArrowStyle* arrowStyle);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_H
/** @} */