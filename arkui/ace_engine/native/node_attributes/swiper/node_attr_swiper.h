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
 * @brief Defines a set of swiper attribute enum.
 *
 * @since 12
 */

/**
 * @file swiper_event_enum.h
 *
 * @brief Defines a set of swiper attribute enum.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_SWIPER_ATTR_ENUM_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_SWIPER_ATTR_ENUM_H

#ifdef ARKUI_NODE_ATTRIBUTE_ENUM_EXPANDING
/**
 * @brief Defines whether to enable loop playback for the swiper.
 * This attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: whether to enable loop playback. The value <b>1</b> means to enable loop playback, and <b>0</b>
 * means the opposite. The default value is <b>1/b>. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: whether to enable loop playback. The value <b>1</b> means to enable loop playback, and <b>0</b>
 * means the opposite. The default value is <b>1</b>. \n
 *
 */
NODE_SWIPER_LOOP = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SWIPER,
/**
 * @brief Defines whether to enable automatic playback for child component switching in the swiper.
 * This attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: whether to enable automatic playback for child component switching. The value <b>1</b>
 * means to enable automatic playback, and <b>0</b> means the opposite. The default value is <b>0</b>. \n
 * \n
 * .value[1]?.i32: whether to stop automatic playback when the user touches the screen. The value <b>1</b> means
 * to stop automatic playback, and <b>0</b> means the opposite. The default value is <b>1</b>. This parameter is
 * supported since API version 16. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: whether to enable automatic playback for child component switching. The value <b>1</b> means
 * to enable automatic playback, and <b>0</b> means the opposite. The default value is <b>0</b>. \n
 * .value[1].i32: whether to stop automatic playback when the user touches the screen. The value <b>1</b> means to
 * stop automatic playback, and <b>0</b> means the opposite. This parameter is supported since API version 16. \n
 *
 */
NODE_SWIPER_AUTO_PLAY,
/**
 * @brief Defines whether to enable the navigation point indicator for the swiper. This attribute can be set,
 * reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: whether to enable the navigation point indicator. The value <b>1</b> means to enable the
 * navigation point indicator, and <b>0</b> means the opposite. The default value is <b>1</b>. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: whether to enable the navigation point indicator. The value <b>1</b> means to enable the
 * navigation point indicator, and <b>0</b> means the opposite. The default value is <b>1</b>. \n
 *
 */
NODE_SWIPER_SHOW_INDICATOR,
/**
 * @brief Defines the interval for automatic playback. This attribute can be set, reset, and obtained as required
 * through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].f32: interval for automatic playback, in milliseconds. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].f32: interval for automatic playback, in milliseconds. \n
 *
 */
NODE_SWIPER_INTERVAL,
/**
 * @brief Defines whether vertical swiping is used for the swiper. This attribute can be set, reset, and obtained
 * as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: whether vertical swiping is used. The value <b>1</b> means that vertical swiping is used, and
 * <b>0</b> means the opposite. The default value is <b>0</b>. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: whether vertical swiping is used. The value <b>1</b> means that vertical swiping is used, and
 * <b>0</b> means the opposite. The default value is <b>0</b>. \n
 *
 */
NODE_SWIPER_VERTICAL,

/**
 * @brief Defines the duration of the animation for switching child components. This attribute can be set, reset,
 * and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].f32: duration of the animation for switching child components, in milliseconds. The default value is
 * <b>400</b>. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].f32: duration of the animation for switching child components, in milliseconds. The default value is
 * <b>400</b>. \n
 *
 */
NODE_SWIPER_DURATION,

/**
 * @brief Defines the animation curve for the swiper. This attribute can be set, reset, and obtained as required
 * through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: animation curve. The parameter type is {@link ArkUI_AnimationCurve}.
 * The default value is <b>ARKUI_CURVE_LINEAR</b>. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: animation curve. The parameter type is {@link ArkUI_AnimationCurve}.
 * The default value is <b>ARKUI_CURVE_LINEAR</b>. \n
 *
 */
NODE_SWIPER_CURVE,

/**
 * @brief Defines the spacing between child components in the swiper.
 * This attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].f32: spacing between child components. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].f32: spacing between child components. \n
 *
 */
NODE_SWIPER_ITEM_SPACE,

/**
 * @brief Defines the index of the child component currently displayed in the swiper.
 * This attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: index value of the child component. \n
 * .value[1]?.i32: animation mode, the parameter type is {@link ArkUI_SwiperAnimationMode}. \n
 * The default value is ARKUI_SWIPER_NO_ANIMATION. This parameter is valid only for the current call. \n
 * This parameter is supported since API version 15. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: index value of the child component. \n
 *
 */
NODE_SWIPER_INDEX,

/**
 * @brief Defines the number of elements to display per page.
 * This attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: number of elements to display per page. \n
 * .value[1]?.i32: whether to turn pages by group. The value <b>0</b> means to turn pages by child element,
 * and <b>1</b> means to turn pages by group. This parameter is supported since API version 19. \n
 * .string?: this parameter can only be set to 'auto'. When 'auto' is set, the value[] parameters are ignored.
 * This parameter is supported since API version 19. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: number of elements to display per page. \n
 * .value[1].i32: whether to turn pages by group. This parameter is supported since API version 19. \n
 * .string: 'auto' or empty string.
 *
 */
NODE_SWIPER_DISPLAY_COUNT,

/**
 * @brief Defines whether to disable the swipe feature.
 * This attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: whether to disable the swipe feature. The value <b>1</b> means to disable
 * the swipe feature, and <b>0</b> means the opposite. The default value is <b>0</b>. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: whether to disable the swipe feature. The value <b>1</b> means to disable the swipe
 * feature, and <b>0</b> means the opposite. The default value is <b>0</b>. \n
 *
 */
NODE_SWIPER_DISABLE_SWIPE,

/**
 * @brief Defines whether to show the arrow when the mouse pointer hovers over the navigation point indicator.
 * This attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: whether to show the arrow when the mouse pointer hovers over the navigation point indicator.
 * The parameter type is {@link ArkUI_SwiperArrow}.\n
 * The default value is <b>ARKUI_SWIPER_ARROW_HIDE</b>. \n
 * .?object: arrow style. The parameter type is {@link ArkUI_SwiperArrowStyle}. \n
 * This parameter is supported since API version 19. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: whether to show the arrow when the mouse pointer hovers over the navigation point indicator.
 * The parameter type is {@link ArkUI_SwiperArrow}.\n
 * The default value is <b>ARKUI_SWIPER_ARROW_HIDE</b>. \n
 * .object: arrow style. The parameter type is {@link ArkUI_SwiperArrowStyle}. \n
 * This parameter is supported since API version 19. \n
 *
 */
NODE_SWIPER_SHOW_DISPLAY_ARROW,

/**
 * @brief Defines the effect used at the edges of the swiper when the boundary of the scrollable content is reached.
 * This attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: effect used at the edges of the swiper when the boundary of the scrollable content is reached.
 * The parameter type is {@link ArkUI_EdgeEffect}.\n
 * The default value is <b>ARKUI_EDGE_EFFECT_SPRING</b>. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: effect used at the edges of the swiper when the boundary of the scrollable content is reached.
 * The parameter type is {@link ArkUI_EdgeEffect}. \n
 *
 */
NODE_SWIPER_EDGE_EFFECT_MODE,

/**
 * @brief Defines the swiper adapter. The attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .object: {@link ArkUI_NodeAdapter} object as the adapter. \n
 */
NODE_SWIPER_NODE_ADAPTER,

/**
 * @brief Sets the number of cached items in the swiper adapter.
 * This attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: number of cached items in the swiper adapter. \n
 * .value[1]?.i32: whether the cached items will be displayed. \n
 * The value <b>0</b> indicates that cached items will not be displayed, \n
 * and <b>1</b> indicates that cached items will be displayed. The default value is <b>0</b>. \n
 * This parameter is supported from API version 19. \n
 * .value[2]?.i32: whether the cachedCount is independent of group calculation. \n
 * The value <b>1</b> indicates that cachedCount is calculated by actual child component count,\n
 * and is independent of displayCount group calculation.\n
 * The value <b>0</b> indicates that, when NODE_SWIPER_DISPLAY_COUNT is enabled to turn pages by group,\n
 * cachedCount is calculated by group.The default value is <b>0</b>. \n
 * This parameter is supported from API version 24. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: number of cached items in the swiper adapter. \n
 * .value[1].i32: whether the cached items will be displayed. This parameter is supported from API version 19. \n
 * .value[2].i32: whether the cachedCount is independent of group calculation. This parameter is supported from API version 24. \n
 */
NODE_SWIPER_CACHED_COUNT,

/**
 * @brief Defines the front margin of the wiper.
 * The attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].f32: the front margin. The unit is vp. The default value is <b>0.0</b>\n
 * .value[1]?.i32: whether to ignore blanks, the default value is 0.
 * The value <b>1</b> means to ignore blank areas, and <b>0</b> means the opposite. \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].f32: the front margin, the unit is vp. \n
 * .value[1].i32: whether to ignore blank areas. The value <b>1</b> means to ignore blank areas, and <b>0</b> means
 * the opposite. \n
 */
NODE_SWIPER_PREV_MARGIN,

/**
 * @brief Defines the back margin of the wiper.
 * The attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].f32: the back margin. The unit is vp. The default value is <b>0.0</b>\n
 * .value[1]?.i32: whether to ignore blanks, the default value is 0.
 * The value <b>1</b> means to ignore blank areas, and <b>0</b> means the opposite. \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].f32: the back margin, the unit is vp. \n
 * .value[1].i32: whether to ignore blank areas. The value <b>1</b> means to ignore blank areas, and <b>0</b> means
 * the opposite. \n
 */
NODE_SWIPER_NEXT_MARGIN,

/**
 * @brief Defines the navigation indicator type of the swiper.
 * The attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: navigation indicator type, the parameter type is {@link ArkUI_SwiperIndicatorType}.\n
 * .object: The parameter type is {@link ArkUI_SwiperIndicator} when the indicator type \n
 * is <b>ARKUI_SWIPER_INDICATOR_TYPE_DOT</b>. The parameter type is {@link ArkUI_SwiperDigitIndicator}
 * when the indicator type is <b>ARKUI_SWIPER_INDICATOR_TYPE_DIGIT</b>. \n
 * {@link ArkUI_SwiperDigitIndicator} is supported since API version 19. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: navigation indicator type, the parameter type is {@link ArkUI_SwiperIndicatorType}.\n
 * .object: The parameter type is {@link ArkUI_SwiperIndicator} when the indicator type \n
 * is <b>ARKUI_SWIPER_INDICATOR_TYPE_DOT</b>. The parameter type is {@link ArkUI_SwiperDigitIndicator}
 * when the indicator type is <b>ARKUI_SWIPER_INDICATOR_TYPE_DIGIT</b>. \n
 * {@link ArkUI_SwiperDigitIndicator} is supported since API version 19. \n
 *
 */
NODE_SWIPER_INDICATOR,

/**
 * @brief Set the nested scrolling mode for the Swiper component and parent component.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32：Nested scrolling patterns for Swiper components and parent components. The parameter type is
 * {@link ArkUI_SwiperNestedScrollMode} \n
 * The default value is <b>ARKUI_SWIPER_NESTED_SRCOLL_SELF_ONLY<b> \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32：Nested scrolling patterns for Swiper components and parent components. The parameter type is
 * {@link ArkUI_SwiperNestedScrollMode} \n
 */
NODE_SWIPER_NESTED_SCROLL,

/**
 * @brief Set the switcher component to flip to the specified page.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32：Specify the index value of the page in Swiper.\n
 * .value[1]?.i32：Set whether there is an animation effect when flipping to the specified page. 1 indicates active
 * effect, 0 indicates no active effect, default value is 0。\n
 */
NODE_SWIPER_SWIPE_TO_INDEX,

/**
 * @brief Set to disable component navigation point interaction function。
 *
 * Property setting method parameter {@link ArkUI-AttributeItem} format: \n
 * .value[0].i32：Set to disable the interaction function of component navigation points. When set to true, it
 * indicates that the navigation points are interactive. The default value is true. \n
 * The return value of the attribute acquisition method is in the format of {@ link ArkUI-AttributeItem}： \n
 * .value[0].i32：Set to disable component navigation point interaction. \n
 */
NODE_SWIPER_INDICATOR_INTERACTIVE,

/**
 * @brief Sets the page flipping mode using the mouse wheel.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: page flipping mode using the mouse wheel. The parameter type is {@link ArkUI_PageFlipMode}. \n
 * \n
 * Format of the return value {@link ArkUI_PageFlipMode}:\n
 * .value[0].i32: page flipping mode using the mouse wheel. \n
 *
 * @since 15
 */
NODE_SWIPER_PAGE_FLIP_MODE,

/**
 * @brief Defines the minimum main axis size of child element for swiper to works out the display count.
 * This attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].f32: minimum main axis size of the child element, Unit: vp. \n
 * .value[1]?.i32: whether to turn pages by group. The value <b>0</b> means to turn pages by child element,
 * and <b>1</b> means to turn pages by group. The default value is <b>0</b>. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].f32: minimum main axis size of the child element, Unit: vp. \n
 * .value[1].i32: whether to turn pages by group. \n
 *
 * @since 19
 */
NODE_SWIPER_AUTO_FILL,

/**
 * @brief Sets whether to maintain the visible content's position when data is inserted or deleted outside
 * the display area of the <b>Swiper</b> component.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
 * .value[0].i32: whether to maintain the visible content's position when data is inserted or deleted outside
 * the display area of the <b>Swiper</b> component. The value <b>0</b> means not to maintain the visible content's
 * position, and <b>1</b> means the opposite. The default value is <b>0</b>. \n
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}:\n
 * .value[0].i32: whether to maintain the visible content's position when data is inserted or deleted outside
 * the display area of the <b>Swiper</b> component. The value <b>0</b> means not to maintain the visible content's
 * position, and <b>1</b> means the opposite. The default value is <b>0</b>. \n
 *
 * @since 20
 */
NODE_SWIPER_MAINTAIN_VISIBLE_CONTENT_POSITION = 1001023,

/**
 * @brief Specifies the responsive column layout policy for the <b>Swiper</b> component.
 * This attribute can be set, reset, and obtained as required through APIs.
 *
 * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute: \n
 * .value[0].i32: number of columns at different breakpoint specifications.
 * The data type is {@link ArkUI_ItemFillPolicy}. \n
 * .value[1]?.i32: whether to paginate by group. The value <b>0</b> means to paginate by individual child elements,
 * and <b>1</b> means to paginate by groups of child elements displayed within the viewport.
 * The default value is <b>0</b>.
 * \n
 * Format of the return value {@link ArkUI_AttributeItem}: \n
 * .value[0].i32: number of columns at different breakpoint specifications.
 * The data type is {@link ArkUI_ItemFillPolicy}. \n
 * .value[1].i32: whether to paginate by group. \n
 *
 * @since 22
 */
NODE_SWIPER_ITEMFILLPOLICY = 1001024,
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_SWIPER_ATTR_ENUM_H
/** @} */