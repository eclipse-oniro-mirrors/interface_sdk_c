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
 * @brief Defines a set of Swiper enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_SWIPER_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_SWIPER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the navigation indicator style for the swiper.
 *
 * @since 12
 */
typedef struct ArkUI_SwiperIndicator ArkUI_SwiperIndicator;

/**
 * @brief Defines the digital indicator style for the swiper.
 *
 * @since 19
 */
typedef struct ArkUI_SwiperDigitIndicator ArkUI_SwiperDigitIndicator;

/**
 * @brief Defines the arrow style for the swiper.
 *
 * @since 19
 */
typedef struct ArkUI_SwiperArrowStyle ArkUI_SwiperArrowStyle;

/**
 * @brief Enumerates arrow styles of the navigation point indicator.
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
 * @brief Nested scrolling mode for Swiper components and parent components.
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
 * @brief Enumerates the page flipping modes using the mouse wheel for the <b>Swiper</b> component.
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
 * @brief Enumerates the animation modes for {@link NODE_SWIPER_INDEX}.
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
 * @brief Define the navigation indicator type of the swiper.
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
 * @brief Creates a navigation indicator.
 *
 * @param type Indicates the type of the indicator.
 * @return Returns the pointer to the new indicator.
 * @since 12
 */
ArkUI_SwiperIndicator* OH_ArkUI_SwiperIndicator_Create(ArkUI_SwiperIndicatorType type);

/**
 * @brief Destroys the pointer to the indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_Dispose(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the distance between the navigation point and the start of the swiper.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param value Indicates the distance between the navigation point and the start of the swiper.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetStartPosition(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief Obtains the distance between the navigation point and the start of the swiper.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns the distance between the navigation point and the start of the swiper.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetStartPosition(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the distance between the navigation point and the top of the swiper.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param value Indicates the distance between the navigation point and the top of the swiper.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetTopPosition(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief Obtains the distance between the navigation point and the top of the swiper.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns the distance between the navigation point and the top of the swiper.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetTopPosition(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the distance between the navigation point and the right of the swiper.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param value Indicates the distance between the navigation point and the right of the swiper.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetEndPosition(ArkUI_SwiperIndicator* indicator, float value);

/**
* @brief Obtains the distance between the navigation point and the end of the swiper.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns the distance between the navigation point and the end of the swiper.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetEndPosition(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the distance between the navigation point and the bottom of the swiper.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param value Indicates the distance between the navigation point and the bottom of the swiper.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetBottomPosition(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief Obtains the distance between the navigation point and the bottom of the swiper.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns the distance between the navigation point and the bottom of the swiper.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetBottomPosition(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the width of the dot for the dot indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param value Indicates the width of the dot for the dot indicator.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetItemWidth(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief Obtains the width of the dot for the dot indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns the width of the dot for the dot indicator.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetItemWidth(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the height of the dot for the dot indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param value Indicates the height of the dot for the dot indicator.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetItemHeight(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief  Obtains the height of the dot for the dot indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns the height of the dot for the dot indicator.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetItemHeight(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the width of the selected dot for the dot indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param value Indicates the width of the selected dot for the dot indicator.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetSelectedItemWidth(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief  Obtains the width of the selected dot for the dot indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns the width of the selected dot for the dot indicator.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetSelectedItemWidth(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the height of the selected dot for the dot indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param value Indicates the height of the selected dot for the dot indicator.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetSelectedItemHeight(ArkUI_SwiperIndicator* indicator, float value);

/**
 * @brief  Obtains the height of the selected dot for the dot indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns the height of the selected dot for the dot indicator.
 * @since 12
 */
float OH_ArkUI_SwiperIndicator_GetSelectedItemHeight(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets whether to display the mask style of the dot navigation indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param mask Whether to display the mask style. True means to display.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetMask(ArkUI_SwiperIndicator* indicator, int32_t mask);

/**
 * @brief Obtains whether to display the mask style of the dot navigation indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns whether to display the mask style. True means to display.
 * @since 12
 */
int32_t OH_ArkUI_SwiperIndicator_GetMask(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the color of the dot navigation indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param color the color of the dot navigation indicator, in 0xARGB format.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetColor(ArkUI_SwiperIndicator* indicator, uint32_t color);

/**
 * @brief Obtains the color of the dot navigation indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns the color of the dot navigation indicator, in 0xARGB format.
 * @since 12
 */
uint32_t OH_ArkUI_SwiperIndicator_GetColor(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the color of the selected dot for the navigation indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param selectedColor the color of the selected dot, in 0xARGB format.
 * @since 12
 */
void OH_ArkUI_SwiperIndicator_SetSelectedColor(ArkUI_SwiperIndicator* indicator, uint32_t selectedColor);

/**
 * @brief Obtains the color of the selected dot for the dot navigation indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns the color of the selected dot, in 0xARGB format.
 * @since 12
 */
uint32_t OH_ArkUI_SwiperIndicator_GetSelectedColor(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the number of maxDisplayCount for the dot navigation indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param maxDisplayCount the maxDisplayCount of the navigation dot, span is 6-9.
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} indicator is null or maxDisplayCount less then 6 or
 *         maxDisplayCount more then 9
 * @since 12
 */
int32_t OH_ArkUI_SwiperIndicator_SetMaxDisplayCount(ArkUI_SwiperIndicator* indicator, int32_t maxDisplayCount);

/**
 * @brief Obtains the number of maxDisplayCount for the dot navigation indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns the number of the maxDisplayCount, span is 6-9.
 *         0 - indicator is null
 * @since 12
 */
int32_t OH_ArkUI_SwiperIndicator_GetMaxDisplayCount(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets whether to ignore the size of the indicator for {@link OH_ArkUI_SwiperIndicator_SetBottomPosition}.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param ignoreSize Whether to ignore the size of the indicator. The value 1 means to ignore, and 0 means the opposite.
 *     The default value is 0.
 * @since 19
 */
void OH_ArkUI_SwiperIndicator_SetIgnoreSizeOfBottom(ArkUI_SwiperIndicator* indicator, int32_t ignoreSize);

/**
 * @brief Obtains whether to ignore the size of the indicator for {@link OH_ArkUI_SwiperIndicator_SetBottomPosition}.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return Returns whether to ignore the size of the indicator.
 * @since 19
 */
int32_t OH_ArkUI_SwiperIndicator_GetIgnoreSizeOfBottom(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Sets the space between the dots of the navigation indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @param space the space between the dots of the navigation indicator, the default value is 8vp.
 * @since 19
 */
void OH_ArkUI_SwiperIndicator_SetSpace(ArkUI_SwiperIndicator* indicator, float space);

/**
 * @brief Obtains the space between the dots of the navigation indicator.
 *
 * @param indicator Indicates the pointer to the indicator.
 * @return the space between the dots of the navigation indicator
 * @since 19
 */
float OH_ArkUI_SwiperIndicator_GetSpace(ArkUI_SwiperIndicator* indicator);

/**
 * @brief Creates a digital indicator.
 *
 * @return Returns the pointer to the new indicator.
 * @since 19
 */
ArkUI_SwiperDigitIndicator *OH_ArkUI_SwiperDigitIndicator_Create();

/**
 * @brief Sets the distance between the digital indicator and the start of the swiper.
 *
 * @param indicator The pointer to the digital indicator.
 * @param value Indicates the distance between the digital indicator and the start of the swiper.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetStartPosition(ArkUI_SwiperDigitIndicator* indicator, float value);

/**
 * @brief Gets the distance between the digital indicator and the start of the swiper.
 *
 * @param indicator The pointer to the digital indicator.
 * @return Returns the distance between the digital indicator and the start of the swiper.
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetStartPosition(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the distance between the digital indicator and the top of the swiper.
 *
 * @param indicator The pointer to the digital indicator.
 * @param value Indicates the distance between the digital indicator and the top of the swiper.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetTopPosition(ArkUI_SwiperDigitIndicator* indicator, float value);

/**
 * @brief Gets the distance between the digital indicator and the top of the swiper.
 *
 * @param indicator The pointer to the digital indicator.
 * @return Returns the distance between the digital indicator and the top of the swiper.
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetTopPosition(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the distance between the digital indicator and the end of the swiper.
 *
 * @param indicator The pointer to the digital indicator.
 * @param value Indicates the distance between the digital indicator and the end of the swiper.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetEndPosition(ArkUI_SwiperDigitIndicator* indicator, float value);

/**
 * @brief Gets the distance between the digital indicator and the end of the swiper.
 *
 * @param indicator The pointer to the digital indicator.
 * @return Returns the distance between the digital indicator and the end of the swiper.
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetEndPosition(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the distance between the digital indicator and the bottom of the swiper.
 *
 * @param indicator The pointer to the digital indicator.
 * @param value Returns the distance between the digital indicator and the bottom of the swiper.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetBottomPosition(ArkUI_SwiperDigitIndicator* indicator, float value);

/**
 * @brief Gets the distance between the digital indicator and the bottom of the swiper.
 *
 * @param indicator The pointer to the digital indicator.
 * @return Returns the distance between the digital indicator and the bottom of the swiper.
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetBottomPosition(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the font color of total count in the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @param color font color, in 0xARGB format. Default value: 0xFF182431.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetFontColor(ArkUI_SwiperDigitIndicator* indicator, uint32_t color);

/**
 * @brief Gets the font color of total count in the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @return font color, in 0xARGB format.
 * @since 19
 */
uint32_t OH_ArkUI_SwiperDigitIndicator_GetFontColor(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the font color of selected index in the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @param selectedColor font color, in 0xARGB format. Default value: 0xFF182431.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetSelectedFontColor(ArkUI_SwiperDigitIndicator* indicator, uint32_t selectedColor);

/**
 * @brief Gets the font color of selected index in the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @return font color, in 0xARGB format.
 * @since 19
 */
uint32_t OH_ArkUI_SwiperDigitIndicator_GetSelectedFontColor(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the font size of total count in the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @param size font size, in fp.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetFontSize(ArkUI_SwiperDigitIndicator* indicator, float size);

/**
 * @brief Gets the font size of total count in the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @return font size, in fp.
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetFontSize(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the font size of selected index in the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @param size font size, in fp.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetSelectedFontSize(ArkUI_SwiperDigitIndicator* indicator, float size);

/**
 * @brief Gets the font size of selected index in the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @return font size, in fp.
 * @since 19
 */
float OH_ArkUI_SwiperDigitIndicator_GetSelectedFontSize(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Destroys the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_Destroy(ArkUI_SwiperDigitIndicator *indicator);

/**
 * @brief Sets whether to ignore the size of the indicator for {@link OH_ArkUI_SwiperDigitIndicator_SetBottomPosition}.
 *
 * @param indicator The pointer to the digital indicator.
 * @param ignoreSize Whether to ignore the size of the indicator. The value 1 means to ignore, and 0 means the opposite.
 *     The default value is 0.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetIgnoreSizeOfBottom(ArkUI_SwiperDigitIndicator* indicator, int32_t ignoreSize);

/**
 * @brief Obtains whether to ignore the size of the indicator for
 * {@link OH_ArkUI_SwiperDigitIndicator_SetBottomPosition}.
 *
 * @param indicator The pointer to the digital indicator.
 * @return Returns whether to ignore the size of the indicator.
 * @since 19
 */
int32_t OH_ArkUI_SwiperDigitIndicator_GetIgnoreSizeOfBottom(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Creates a arrow style for swiper.
 *
 * @return Returns the pointer to the new arrow style.
 * @since 19
 */
ArkUI_SwiperArrowStyle *OH_ArkUI_SwiperArrowStyle_Create();

/**
 * @brief Sets whether to show the background for the arrow.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @param showBackground whether to show the background for the arrow.
 *        The value <b>1</b> means to show the background, and <b>0</b> means the opposite.
 *        The default value is <b>0</b>.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetShowBackground(ArkUI_SwiperArrowStyle *arrowStyle, int32_t showBackground);

/**
 * @brief Gets whether to show the background for the arrow.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @return whether to show the background for the arrow.
 *         The value <b>1</b> means to show the background, and <b>0</b> means the opposite.
 * @since 19
 */
int32_t OH_ArkUI_SwiperArrowStyle_GetShowBackground(ArkUI_SwiperArrowStyle* arrowStyle);

/**
 * @brief Sets the display position of the arrow.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @param showSidebarMiddle the display position of the arrow.
 *        The value <b>1</b> means to display on boths sides of the swiper,
 *        and <b>0</b> means display on boths sides of the swiper indicator.
 *        The default value is <b>0</b>.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetShowSidebarMiddle(ArkUI_SwiperArrowStyle* arrowStyle, int32_t showSidebarMiddle);

/**
 * @brief Gets the display position of the arrow.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @return the display position of the arrow. The value <b>1</b> means to display on boths sides of the swiper,
 *         and <b>0</b> means display on boths sides of the swiper indicator.
 * @since 19
 */
int32_t OH_ArkUI_SwiperArrowStyle_GetShowSidebarMiddle(ArkUI_SwiperArrowStyle* arrowStyle);

/**
 * @brief Sets the background size of the arrow.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @param backgroundSize the background size of the arrow. The unit is vp.
 *        The default value is <b>24</b> when the arrow displays on both sides of the swiper indicator.
 *        The default value is <b>32</b> when the arrow displays on both sides of the swiper.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetBackgroundSize(ArkUI_SwiperArrowStyle* arrowStyle, float backgroundSize);

/**
 * @brief Gets the background size of the arrow.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @return Returns the background size of the arrow. The unit is vp.
 * @since 19
 */
float OH_ArkUI_SwiperArrowStyle_GetBackgroundSize(ArkUI_SwiperArrowStyle *arrowStyle);

/**
 * @brief Destroys the arrow style.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_Destroy(ArkUI_SwiperArrowStyle *arrowStyle);

/**
 * @brief Sets the background color of the arrow.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @param backgroundColor the background color of the arrow, in 0xARGB format.
 *        The default value is <b>0x00000000</b> when the arrow displays on both sides of the swiper indicator.
 *        The default value is <b>0x19182431</b> when the arrow displays on both sides of the swiper.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetBackgroundColor(ArkUI_SwiperArrowStyle *arrowStyle, uint32_t backgroundColor);

/**
 * @brief Gets the background color of the arrow.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @return Returns the background color of the arrow, in 0xARGB format.
 * @since 19
 */
uint32_t OH_ArkUI_SwiperArrowStyle_GetBackgroundColor(ArkUI_SwiperArrowStyle* arrowStyle);

/**
 * @brief Sets the size of the arrow.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @param arrowSize the size of the arrow. The unit is vp.
 *        The default value is <b>18</b> when the arrow displays on both sides of the swiper indicator.
 *        The default value is <b>24</b> when the arrow displays on both sides of the swiper.
 *        The arrow size is fixed to 3/4 of the background size when the background is shown.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetArrowSize(ArkUI_SwiperArrowStyle* arrowStyle, float arrowSize);

/**
 * @brief Gets the size of the arrow.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @return the size of the arrow. The unit is vp.
 * @since 19
 */
float OH_ArkUI_SwiperArrowStyle_GetArrowSize(ArkUI_SwiperArrowStyle* arrowStyle);

/**
 * @brief Sets the color of the arrow.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @param arrowColor the color of the arrow, in 0xARGB format. The default value is <b>0x00182431</b>.
 * @since 19
 */
void OH_ArkUI_SwiperArrowStyle_SetArrowColor(ArkUI_SwiperArrowStyle* arrowStyle, uint32_t arrowColor);

/**
 * @brief Gets the color of the arrow.
 *
 * @param arrowStyle The pointer to the arrow style.
 * @return Returns the color of the arrow, in 0xARGB format.
 * @since 19
 */
uint32_t OH_ArkUI_SwiperArrowStyle_GetArrowColor(ArkUI_SwiperArrowStyle* arrowStyle);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_SWIPER_H
/** @} */