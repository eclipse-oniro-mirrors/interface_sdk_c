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
 * @brief Defines the enumerations and APIs of the **Swiper** component for implementing scenarios such as carousel
 * display and content navigation. It supports custom navigation indicators (dot/number types), navigation arrow styles,
 *  nested scrolling modes, mouse wheel page-turning modes, and animation modes, helping users quickly build carousel
 * interaction experiences.
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
 * @brief Defines the navigation indicator style of the **Swiper** component, which is used to display the current
 * position and switching state in scenarios such as carousels. It supports custom configuration of attributes such as
 * the indicator size, color, and spacing, which improves the user's awareness of the current browsing position and
 * enhances the user interaction experience. It is applicable to various application scenarios such as displaying
 * carousel images, ad slots, and content navigation.
 *
 * @since 12
 */
typedef struct ArkUI_SwiperIndicator ArkUI_SwiperIndicator;

/**
 * @brief Defines the style of the digit navigation indicator for the **Swiper** component, which is used to display
 * the current position and total number of pages in digits.
 *
 * @since 19
 */
typedef struct ArkUI_SwiperDigitIndicator ArkUI_SwiperDigitIndicator;

/**
 * @brief Defines the navigation arrow style of the **Swiper** component, which implements page-turning guidance by
 * configuring attributes such as the arrow position, size, and color.
 *
 * @since 19
 */
typedef struct ArkUI_SwiperArrowStyle ArkUI_SwiperArrowStyle;

/**
 * @brief Enumerates arrow styles of the navigation indicator of the **Swiper** component.
 *
 * @since 12
 */
typedef enum {
    /**
     * The arrow is not displayed for the navigation point indicator.
     * @since 12
     */
    ARKUI_SWIPER_ARROW_HIDE = 0,
    /**
     * The arrow is displayed for the navigation point indicator.
     * @since 12
     */
    ARKUI_SWIPER_ARROW_SHOW,
    /**
     * The arrow is displayed only when the mouse pointer hovers over the navigation point indicator.
     * @since 12
     */
    ARKUI_SWIPER_ARROW_SHOW_ON_HOVER
} ArkUI_SwiperArrow;

/**
 * @brief Enumerates the nested scrolling modes of the **Swiper** component and its parent container.
 *
 * @since 12
 */
typedef enum {
    /**
     * Swiper only scrolls on its own and is not linked to its parent component.
     * @since 12
     */
    ARKUI_SWIPER_NESTED_SRCOLL_SELF_ONLY = 0,
    /**
     * The Swiper itself scrolls first, and the parent component scrolls after it reaches the edge. After the parent
     * component scrolls to the edge, if the parent component has an edge effect, the parent component triggers
     * the edge effect; otherwise, the Swiper triggers the edge effect.
     * @since 12
     */
    ARKUI_SWIPER_NESTED_SRCOLL_SELF_FIRST
} ArkUI_SwiperNestedScrollMode;

/**
 * @brief Enumerates the page flipping modes using the mouse wheel for the **Swiper** component.
 *
 * @since 15
 */
typedef enum {
    /**
     * When the mouse wheel is scrolled continuously, multiple pages are flipped, which is determined by the number of
     *  times that mouse events are reported.
     * @since 15
     */
    ARKUI_PAGE_FLIP_MODE_CONTINUOUS = 0,
    /**
     * The system does not respond to other mouse wheel events until the page flipping animation ends.
     * @since 15
     */
    ARKUI_PAGE_FLIP_MODE_SINGLE
} ArkUI_PageFlipMode;

/**
 * @brief Enumerates the animation modes for the **Swiper** component when jumping to the page with the specified index.
 *
 * @since 15
 */
typedef enum {
    /**
     * Jump to target index without animation.
     * @since 15
     */
    ARKUI_SWIPER_NO_ANIMATION = 0,
    /**
     * Scroll to target index with animation.
     * @since 15
     */
    ARKUI_SWIPER_DEFAULT_ANIMATION = 1,
    /**
     * Jump to some index near the target index without animation, then scroll to target index with animation.
     * @since 15
     */
    ARKUI_SWIPER_FAST_ANIMATION = 2
} ArkUI_SwiperAnimationMode;

/**
 * @brief Enumerates the navigation indicator types of the **Swiper** component.
 *
 * @since 12
 */
typedef enum {
    /**
     * dot type.
     * @since 12
     */
    ARKUI_SWIPER_INDICATOR_TYPE_DOT,
    /**
     * digit type.
     * @since 12
     */
    ARKUI_SWIPER_INDICATOR_TYPE_DIGIT
} ArkUI_SwiperIndicatorType;

/**
 * @brief Creates a navigation indicator for the **Swiper** component. After calling this API, you must call **
 * OH_ArkUI_SwiperIndicator_Dispose** to dispose of the navigation indicator object pointer to release resources after
 * use, so as to avoid memory leaks.
 *
 * @param type Type of the navigation indicator. {@link ARKUI_SWIPER_INDICATOR_TYPE_DOT} indicates a dot-style
 *     indicator, which applies to general carousel scenarios. {@link ARKUI_SWIPER_INDICATOR_TYPE_DIGIT} indicates a
 *     digit-style indicator, which applies to navigation scenarios that require precise display of the current page
 *     number and total page count (such as content navigation and step guidance).
 * @return Pointer to the navigation indicator object.
 * @since 12
 */
ArkUI_SwiperIndicator* OH_ArkUI_SwiperIndicator_Create(ArkUI_SwiperIndicatorType type);

/**
 * @brief Disposes of the pointer to the navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_Dispose(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the distance between a navigation indicator and the left edge of the **Swiper** component. In the
 * language mode displayed from right to left, use this API to set its distance from the right side of the **Swiper**
 * component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param value Distance between the navigation indicator and the left edge of the **Swiper** component. In the
 *     language mode displayed from right to left, it indicates the distance from the right side of the **Swiper**
 *     component. Default value: **0**. Unit: vp.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetStartPosition(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief Obtains the distance between the navigation indicator and the left edge of the **Swiper** component. In the
 * language mode displayed from right to left, use this API to obtain its distance from the right side of the **Swiper**
 * component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Distance between the navigation indicator and the left edge of the **Swiper** component. The unit is vp.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetStartPosition(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the distance between a navigation indicator and the top edge of the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param value Distance between the navigation indicator and the top edge of the **Swiper** component. Default value: *
 *     *0**, in vp.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetTopPosition(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief Obtains the distance between the navigation indicator and the top edge of the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Distance between the navigation indicator and the top edge of the **Swiper** component. The unit is vp.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetTopPosition(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the distance between the navigation indicator and the right edge of the **Swiper** component. In the
 * language mode displayed from right to left, use this API to set its distance from the left side of the **Swiper**
 * component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param value Distance between the navigation indicator and the right edge of the **Swiper** component. In the
 *     language mode displayed from right to left, it indicates the distance from the left side of the **Swiper**
 *     component. Default value: **0**. Unit: vp.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetEndPosition(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief Obtains the distance from the navigation indicator to the right edge of the **Swiper** component. In the
 * language mode displayed from right to left, use this API to obtain its distance to the left side of the **Swiper**
 * component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Distance between the navigation indicator and the right edge of the **Swiper** component. The unit is vp.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetEndPosition(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the distance between a navigation indicator and the bottom edge of the **Swiper** component. You can use
 * {@link OH_ArkUI_SwiperIndicator_SetIgnoreSizeOfBottom} to set whether to ignore the navigation indicator size.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param value Distance between the navigation indicator and the bottom edge of the **Swiper** component, in vp.
 *     Default value: **0**. When {@link OH_ArkUI_SwiperIndicator_SetIgnoreSizeOfBottom} is set to **1**, the
 *     navigation indicator size is ignored when the distance from the bottom edge is calculated.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetBottomPosition(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief Obtains the distance between the navigation indicator and the bottom edge of the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Distance between the navigation indicator and the bottom edge of the **Swiper** component. The unit is vp.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetBottomPosition(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the width of a dot-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param value Width of the dot-style navigation indicator. Default value: **12**, in vp.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetItemWidth(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief Obtains the width of the dot-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Width of the dot-style navigation indicator. The unit is vp.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetItemWidth(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the height of a dot-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param value Height of the dot-style navigation indicator. Default value: **6**, in vp.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetItemHeight(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief Obtains the height of the dot-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Height of the dot-style navigation indicator. The unit is vp.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetItemHeight(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the width of a selected dot-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param value Width of the dot-style navigation indicator. Default value: **12**, in vp.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetSelectedItemWidth(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief Obtains the width of the selected dot-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Width of the selected dot-style navigation indicator. Unit: vp.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetSelectedItemWidth(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the height of a selected dot-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param value Height of the dot-style navigation indicator. Default value: **6**, in vp.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetSelectedItemHeight(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief Obtains the height of the selected dot-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Height of the selected dot-style navigation indicator. Unit: vp.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetSelectedItemHeight(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets whether to enable the mask for a dot-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param mask Whether to enable the mask. The value **1** means to enable, and **0** means the opposite. Default value:
 *      **0**.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetMask(ArkUI_SwiperIndicator* indicator, int32_t mask);

/**
 * @brief Obtains whether the mask is enabled for the dot-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Whether the mask is enabled. The value **1** indicates that the mask is enabled, and **0** indicates the
 *     opposite.
 * @since 12
 */
int32_t OH_ArkUI_SwiperIndicator_GetMask(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the color of a dot-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param color Color, in 0xARGB format. For example, **0xFFFF0000** indicates red.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetColor(ArkUI_SwiperIndicator* indicator, uint32_t color);

/**
 * @brief Obtains the color of the dot-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Color, in 0xARGB format. For example, **0xFFFF0000** indicates red.
 * @since 12
 */
uint32_t OH_ArkUI_SwiperIndicator_GetColor(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the color of a selected dot-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param selectedColor Color, in 0xARGB format. For example, **0xFFFF0000** indicates red.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetSelectedColor(ArkUI_SwiperIndicator* indicator, uint32_t selectedColor);

/**
 * @brief Obtains the color of the selected dot-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Color, in 0xARGB format. For example, **0xFFFF0000** indicates red.
 * @since 12
 */
uint32_t OH_ArkUI_SwiperIndicator_GetSelectedColor(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the maximum number of dots for a dot-style navigation indicator.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param maxDisplayCount Maximum number of dots displayed. The valid value range is [6, 9], and the default value is **
 *     6**. A smaller value (for example, 6 to 7) arranges the dots more compactly, which is suitable for scenarios
 *     with fewer pages and limited interface space. A larger value (for example, 8 to 9) provides wider spacing
 *     between the dots and clearer position indication, which is suitable for scenarios with more pages or when
 *     clearer position awareness is required.
 * @return Error code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the value range of **maxDisplayCount** is incorrect.
 * @since 12
 */
int32_t OH_ArkUI_SwiperIndicator_SetMaxDisplayCount(ArkUI_SwiperIndicator* indicator, int32_t maxDisplayCount);

/**
 * @brief Obtains the maximum number of dots for the dot-style navigation indicator.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Maximum number of dots. Value range: [6, 9].
 * @since 12
 */
int32_t OH_ArkUI_SwiperIndicator_GetMaxDisplayCount(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets whether the **OH_ArkUI_SwiperIndicator_SetBottomPosition** API ignores the navigation indicator size.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param ignoreSize Whether to ignore the navigation indicator size. The value **1** indicates to ignore the
 *     navigation indicator size, in which case the bottom distance calculation of
 *     {@link OH_ArkUI_SwiperIndicator_SetBottomPosition} will ignore the navigation indicator size; the value **0**
 *     indicates not to ignore. The default value is **0**.
 * @since 19
 */
void OH_ArkUI_SwiperIndicator_SetIgnoreSizeOfBottom(ArkUI_SwiperIndicator* indicator, int32_t ignoreSize);

/**
 * @brief Obtains whether the **OH_ArkUI_SwiperIndicator_SetBottomPosition** API ignores the navigation indicator size.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Whether the indicator size is ignored.
 * @since 19
 */
int32_t OH_ArkUI_SwiperIndicator_GetIgnoreSizeOfBottom(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the spacing between navigation indicators.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param space Spacing between navigation indicators. Default value: **8**, in vp.
 * @since 19
 */
void OH_ArkUI_SwiperIndicator_SetSpace(ArkUI_SwiperIndicator* indicator, float space);

/**
 * @brief Obtains the spacing between navigation indicators.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @return Spacing between navigation indicators. The unit is vp.
 * @since 19
 */
float OH_ArkUI_SwiperIndicator_GetSpace(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Creates a digit-style navigation indicator for the **Swiper** component.
 *
 * @return Pointer to the digit-style navigation indicator object.
 * @since 19
 */
ArkUI_SwiperDigitIndicator *OH_ArkUI_SwiperDigitIndicator_Create();

/**
 * @brief Sets the start position of a digit-style navigation indicator for the **Swiper** component. This determines
 * the distance from the left edge of the **Swiper** component. For right-to-left scripts, this determines the distance
 * from the right edge of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @param value Distance from the left edge of the **Swiper** component. For right-to-left scripts, this indicates the
 *     distance from the right edge. Default value: **0**, in vp.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetStartPosition(ArkUI_SwiperDigitIndicator* indicator, float value);

/**
 * @brief Obtains the start position of the digit-style navigation indicator for the **Swiper** component. This
 * indicates the distance from the left edge of the **Swiper** component. For right-to-left scripts, this indicates the
 * distance from the right edge of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @return Distance from the left edge of the **Swiper** component. For right-to-left scripts, this indicates the
 *     distance from the right edge. The unit is vp.
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetStartPosition(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the distance from a digit-style navigation indicator to the top edge of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @param value Distance from the digit-style navigation indicator to the top of the **Swiper** component. Default
 *     value: **0**, in vp.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetTopPosition(ArkUI_SwiperDigitIndicator* indicator, float value);

/**
 * @brief Obtains the distance from the digit-style navigation indicator to the top edge of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @return Distance from the digit-style navigation indicator to the top of the **Swiper** component. The unit is vp.
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetTopPosition(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the end position of a digit-style navigation indicator for the **Swiper** component. This determines the
 * distance from the right edge of the **Swiper** component. For right-to-left scripts, this determines the distance
 * from the left edge of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @param value Distance from the right edge of the **Swiper** component. For right-to-left scripts, this indicates the
 *     distance from the left edge. Default value: **0**, in vp.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetEndPosition(ArkUI_SwiperDigitIndicator* indicator, float value);

/**
 * @brief Obtains the end position of the digit-style navigation indicator for the **Swiper** component. This indicates
 * the distance from the right edge of the **Swiper** component. For right-to-left scripts, this indicates the distance
 * from the left edge of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @return Distance from the right edge of the **Swiper** component. For right-to-left scripts, this indicates the
 *     distance from the left edge. The unit is vp.
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetEndPosition(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the distance from a digit-style navigation indicator to the bottom edge of the **Swiper** component. You
 * can use {@link OH_ArkUI_SwiperDigitIndicator_SetIgnoreSizeOfBottom} to set whether to ignore the navigation
 * indicator size.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @param value Distance from the digit-style navigation indicator to the bottom of the **Swiper** component. Default
 *     value: **0**, in vp. When {@link OH_ArkUI_SwiperDigitIndicator_SetIgnoreSizeOfBottom} is set to **1**, the
 *     navigation indicator size is ignored when the distance from the bottom is calculated.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetBottomPosition(ArkUI_SwiperDigitIndicator* indicator, float value);

/**
 * @brief Obtains the distance from the digit-style navigation indicator to the bottom edge of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @return Distance from the digit-style navigation indicator to the bottom of the **Swiper** component. The unit is vp.
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetBottomPosition(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the font color of a digit-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @param color Color, in 0xARGB format. For example, **0xFFFF0000** indicates red. Default value: **0xFF182431**.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetFontColor(ArkUI_SwiperDigitIndicator* indicator, uint32_t color);

/**
 * @brief Obtains the font color of the digit-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @return Color, in 0xARGB format. For example, **0xFFFF0000** indicates red.
 * @since 19
 */
uint32_t OH_ArkUI_SwiperDigitIndicator_GetFontColor(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the font color of a selected digit-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @param selectedColor Font color of the selected digit-style navigation indicator, in 0xARGB format, for example, **
 *     0xFFFF0000** indicates red.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetSelectedFontColor(ArkUI_SwiperDigitIndicator* indicator, uint32_t selectedColor);

/**
 * @brief Obtains the font color of the selected digit-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @return Color, in 0xARGB format. For example, **0xFFFF0000** indicates red.
 * @since 19
 */
uint32_t OH_ArkUI_SwiperDigitIndicator_GetSelectedFontColor(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the font size of a digit-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @param size Font size, in fp.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetFontSize(ArkUI_SwiperDigitIndicator* indicator, float size);

/**
 * @brief Obtains the font size of the digit-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @return Font size, in fp.
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetFontSize(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the font size of a selected digit-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @param size Font size, in fp.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetSelectedFontSize(ArkUI_SwiperDigitIndicator* indicator, float size);

/**
 * @brief Obtains the font size of the selected digit-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @return Font size, in fp.
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetSelectedFontSize(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Destroys the pointer to the digit-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_Destroy(ArkUI_SwiperDigitIndicator *indicator);

/**
 * @brief Sets whether the **OH_ArkUI_SwiperDigitIndicator_SetBottomPosition** API ignores the navigation indicator
 * size.
 *
 * @param indicator Pointer to the navigation indicator object.
 * @param ignoreSize Whether to ignore the navigation indicator size. The value **1** indicates to ignore the
 *     navigation indicator size, in which case the bottom distance calculation of
 *     {@link OH_ArkUI_SwiperDigitIndicator_SetBottomPosition} will ignore the navigation indicator size; **0**
 *     indicates not to ignore. The default value is **0**.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetIgnoreSizeOfBottom(ArkUI_SwiperDigitIndicator* indicator, int32_t ignoreSize);

/**
 * @brief Obtains whether the **OH_ArkUI_SwiperDigitIndicator_SetBottomPosition** API ignores the navigation indicator
 * size.
 *
 * @param indicator Pointer to the digit-style navigation indicator object.
 * @return Whether the navigation indicator size is ignored. The value **1** indicates the navigation indicator size is
 *     ignored, and **0** indicates the opposite.
 * @since 19
 */
int32_t OH_ArkUI_SwiperDigitIndicator_GetIgnoreSizeOfBottom(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Creates a navigation arrow for the **Swiper** component. After calling this API, you must call **
 * OH_ArkUI_SwiperArrowStyle_Destroy** to destroy the navigation arrow object pointer to release resources after use,
 * so as to avoid memory leaks.
 *
 * @return Pointer to the navigation arrow object.
 * @since 19
 */
ArkUI_SwiperArrowStyle *OH_ArkUI_SwiperArrowStyle_Create();

/**
 * @brief Sets whether to display the background of a navigation arrow for the **Swiper** component. After the
 * background display is enabled, the value of **arrowSize** will be fixed to 3/4 of the value of **backgroundSize**.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @param showBackground Whether to show the background of the navigation arrow. The value **1** means to show the
 *     background, and **0** means the opposite. The default value is **0**.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetShowBackground(ArkUI_SwiperArrowStyle *arrowStyle, int32_t showBackground);

/**
 * @brief Obtains whether the background of the navigation arrow is displayed for the **Swiper** component.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @return Whether the background of the navigation arrow is displayed. The value **1** means that the background is
 *     displayed, and **0** means the opposite.
 * @since 19
 */
int32_t OH_ArkUI_SwiperArrowStyle_GetShowBackground(ArkUI_SwiperArrowStyle* arrowStyle);

/**
 * @brief Sets the position of a navigation arrow for the **Swiper** component. The mode on both sides of the
 * navigation indicator is suitable for scenarios where navigation areas are used for centralized interaction, and the
 * mode on both sides of the **Swiper** component is suitable for scenarios where pages need to be turned quickly
 * within a large area.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @param showSidebarMiddle Position where the navigation arrow is displayed. The value **0** indicates that the
 *     navigation arrow is displayed on both sides of the navigation indicator, and **1** indicates that the navigation
 *     arrow is displayed on both sides of the **Swiper** component. The default value is **0**.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetShowSidebarMiddle(ArkUI_SwiperArrowStyle* arrowStyle, int32_t showSidebarMiddle);

/**
 * @brief Obtains the position of the navigation arrow for the **Swiper** component.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @return Position where the navigation arrow is displayed. The value **0** indicates that the navigation arrow is
 *     displayed on both sides of the navigation indicator, and **1** indicates that the navigation arrow is displayed
 *     on both sides of the **Swiper** component.
 * @since 19
 */
int32_t OH_ArkUI_SwiperArrowStyle_GetShowSidebarMiddle(ArkUI_SwiperArrowStyle* arrowStyle);

/**
 * @brief Sets the background size for a navigation arrow of the **Swiper** component. When the navigation arrow
 * background is displayed (set through {@link OH_ArkUI_SwiperArrowStyle_SetShowBackground}), the value of **arrowSize**
 * will be fixed to 3/4 of the value of **backgroundSize**.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @param backgroundSize Background size of the navigation arrow, in vp. Default value: 24 vp on both sides of the
 *     navigation indicator, and 32 vp on both sides of the **Swiper** component. When the background display is
 *     enabled through {@link OH_ArkUI_SwiperArrowStyle_SetShowBackground}, the value of **arrowSize** will be fixed to
 *     3/4 of the value of **backgroundSize**.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetBackgroundSize(ArkUI_SwiperArrowStyle* arrowStyle, float backgroundSize);

/**
 * @brief Obtains the background size of the navigation arrow of the **Swiper** component.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @return Background size of the navigation arrow, in vp.
 * @since 19
 */
float OH_ArkUI_SwiperArrowStyle_GetBackgroundSize(ArkUI_SwiperArrowStyle *arrowStyle);

/**
 * @brief Destroys the navigation arrow pointer of the **Swiper** component.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_Destroy(ArkUI_SwiperArrowStyle *arrowStyle);

/**
 * @brief Sets the background color for a navigation arrow of the **Swiper** component.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @param backgroundColor Background color of the navigation arrow, in 0xARGB format. For example, **0xFFFF0000**
 *     indicates red. Default value: **0x00000000** when displayed on both sides of the navigation indicator and **
 *     0x19182431** when displayed on both sides of the **Swiper** component.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetBackgroundColor(ArkUI_SwiperArrowStyle *arrowStyle, uint32_t backgroundColor);

/**
 * @brief Obtains the background color of the navigation arrow of the **Swiper** component.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @return Background color of the navigation arrow, in 0xARGB format. For example, **0xFFFF0000** indicates red.
 * @since 19
 */
uint32_t OH_ArkUI_SwiperArrowStyle_GetBackgroundColor(ArkUI_SwiperArrowStyle* arrowStyle);

/**
 * @brief Sets the size for a navigation arrow of the **Swiper** component. When the navigation arrow background is
 * displayed (set through **OH_ArkUI_SwiperArrowStyle_SetShowBackground**), the value of **arrowSize** is fixed to 3/4
 * of the value of **backgroundSize**, and setting **arrowSize** in this case does not take effect.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @param arrowSize Size of the navigation arrow, in vp. Default value: 18 vp when displayed on both sides of the
 *     navigation indicator and 24 vp when displayed on both sides of the **Swiper** component. When the navigation
 *     arrow background is displayed, the value of **arrowSize** is fixed at 3/4 of the value of **backgroundSize**.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetArrowSize(ArkUI_SwiperArrowStyle* arrowStyle, float arrowSize);

/**
 * @brief Obtains the size of the navigation arrow of the **Swiper** component.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @return Size of the navigation arrow, in vp.
 * @since 19
 */
float OH_ArkUI_SwiperArrowStyle_GetArrowSize(ArkUI_SwiperArrowStyle* arrowStyle);

/**
 * @brief Sets the color for a navigation arrow of the **Swiper** component.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @param arrowColor Color of the navigation arrow, in 0xARGB format. For example, **0xFFFF0000** indicates red.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetArrowColor(ArkUI_SwiperArrowStyle* arrowStyle, uint32_t arrowColor);

/**
 * @brief Obtains the color of the navigation arrow of the **Swiper** component.
 *
 * @param arrowStyle Pointer to the navigation arrow object.
 * @return Color of the navigation arrow, in 0xARGB format. For example, **0xFFFF0000** indicates red.
 * @since 19
 */
uint32_t OH_ArkUI_SwiperArrowStyle_GetArrowColor(ArkUI_SwiperArrowStyle* arrowStyle);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_H
/** @} */