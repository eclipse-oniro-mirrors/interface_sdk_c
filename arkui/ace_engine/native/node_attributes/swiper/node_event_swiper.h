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
 * @brief Defines a set of swiper event enum.
 *
 * @since 12
 */

/**
 * @file swiper_event_enum.h
 *
 * @brief Defines a set of swiper event enum.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_SWIPER_EVENT_ENUM_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_SWIPER_EVENT_ENUM_H

#ifdef ARKUI_NODE_EVENT_ENUM_EXPANDING
/**
 * @brief Defines the event triggered when the index of the currently displayed element of this
 * <b>ARKUI_NODE_SWIPER</b> instance changes.
 *
 * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
 * {@link ArkUI_NodeComponentEvent}. \n
 * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
 * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: index of the currently displayed element. \n
 */
NODE_SWIPER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SWIPER,

/**
 * @brief Defines the event triggered when the switching animation of this <b>ARKUI_NODE_SWIPER</b> instance starts.
 *
 * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
 * {@link ArkUI_NodeComponentEvent}. \n
 * {@link ArkUI_NodeComponentEvent} contains five parameters: \n
 * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: index of the currently displayed element. \n
 * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: index of the target element to switch to. \n
 * <b>ArkUI_NodeComponentEvent.data[2].f32</b>: offset of the currently displayed element relative to the
 * start position of the swiper along the main axis. \n
 * <b>ArkUI_NodeComponentEvent.data[3].f32</b>: offset of the target element relative to the start position
 * of the swiper along the main axis. \n
 * <b>ArkUI_NodeComponentEvent.data[4].f32</b>: hands-off velocity. \n
 */
NODE_SWIPER_EVENT_ON_ANIMATION_START,

/**
 * @brief Defines the event triggered when the switching animation of this <b>ARKUI_NODE_SWIPER</b> instance ends.
 *
 * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
 * {@link ArkUI_NodeComponentEvent}. \n
 * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
 * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: index of the currently displayed element. \n
 * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: offset of the currently displayed element relative to the
 * start position of the swiper along the main axis. \n
 */
NODE_SWIPER_EVENT_ON_ANIMATION_END,

/**
 * @brief Defines the event triggered on a frame-by-frame basis when the page is turned by a swipe in this
 * <b>ARKUI_NODE_SWIPER</b> instance.
 *
 * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
 * {@link ArkUI_NodeComponentEvent}. \n
 * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
 * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: index of the currently displayed element. \n
 * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: offset of the currently displayed element relative to the
 * start position of the swiper along the main axis. \n
 */
NODE_SWIPER_EVENT_ON_GESTURE_SWIPE,

/**
 * @brief Define the <b>ARKUI_NODE_SWIPER</b> to listen for Swiper page slide events.
 * Instruction: \n
 * 1. If the {@link ArkUI_SwiperDisplayModeType} attribute is set to \n
 * ARKUI_SWIPER_DISPLAY_MODE_AUTO_LINEAR, the interface does not take effect. \n
 * 2, circular scenario, set prevMargin and nextMargin attributes, \n
 * so that Swiper front and back end display the same page, the interface does not take effect. \n
 * 3. During page sliding, the ContentDidScrollCallback callback is \n
 * triggered frame-by-frame for all pages in the window. \n
 * For example, when there are two pages in the window with subscripts 0 and 1, \n
 * callbacks with index values 0 and 1 are triggered twice per frame. \n
 * 4, set the swipeByGroup parameter of the displayCount property to \n
 * true if at least one page in the same group is in the window, \n
 * A callback is triggered for all pages in the group. \n
 * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
 * {@link ArkUI_NodeComponentEvent}. \n
 * {@link ArkUI_NodeComponentEvent} contains four parameters:\n
 * <b>ArkUI_NodeComponentEvent.data[0].i32</b> : indicates the index of the Swiper component, \n
 * which is consistent with the index change in the onChange event. \n
 * <b>ArkUI_NodeComponentEvent.data[1].i32</b> : The index of a page in the window. \n
 * <b>ArkUI_NodeComponentEvent.data[2].f32</b> : The proportion of page movement relative to \n
 * the start position of the Swiper spindle (selectedIndex corresponds to the start position of the page). \n
 * <b>ArkUI_NodeComponentEvent.data[3].f32</b> : The length of the page in the axis direction. \n
 */
NODE_SWIPER_EVENT_ON_CONTENT_DID_SCROLL,

/**
 * @brief Defines the event triggered when the selected index of the <b>ARKUI_NODE_SWIPER</b> changed.
 *
 * This event is triggered under the following scenarios: \n
 * 1. When the page switching animation starts after the user lifts their finger after swiping and the swipe meets
 * the threshold for page turning. \n
 * 2. When the page is changed programmatically using either <b>NODE_SWIPER_INDEX</b> or
 * <b>NODE_SWIPER_SWIPE_TO_INDEX</b>. \n
 * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
 * {@link ArkUI_NodeComponentEvent}. \n
 * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
 * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: index of the currently selected element. \n
 *
 * @since 18
 */
NODE_SWIPER_EVENT_ON_SELECTED = 1001005,

/**
 * @brief Defines the event triggered when the selected index of the <b>ARKUI_NODE_SWIPER</b> changed.
 *
 * This event is triggered under the following scenarios: \n
 * 1. When the page switching animation starts after the user lifts their finger after swiping and the swipe meets
 * the threshold for page turning. \n
 * 2. When the page is changed programmatically using either <b>NODE_SWIPER_INDEX</b> or
 * <b>NODE_SWIPER_SWIPE_TO_INDEX</b>. \n
 * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
 * {@link ArkUI_NodeComponentEvent}. \n
 * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
 * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: the index of the element becomes unselected. \n
 *
 * @since 18
 */
NODE_SWIPER_EVENT_ON_UNSELECTED = 1001006,

/**
 * @brief Defines the event triggered when content in the swiper component will scroll.
 * Instructions: Before page scrolling, the </b>ContentWillScrollCallback</b> callback is invoked. \n \n
 * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
 * {@link ArkUI_NodeComponentEvent}. \n
 * {@link ArkUI_NodeComponentEvent} contains three parameters:\n
 * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: the index value of the current child page. \n
 * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: the index value of the child page that will display. \n
 * <b>ArkUI_NodeComponentEvent.data[2].f32</b>: the sliding offset of each frame.
 * Positive numbers indicating slide backward(e.g. from index=1 to index=0), negative numbers indicating
 * slide forward(e.g. from index=0 to index=1). \n
 *
 * @since 15
 */
NODE_SWIPER_EVENT_ON_CONTENT_WILL_SCROLL = 1001007,

/**
 * @brief Defines the <b>ARKUI_NODE_SWIPER</b> scroll state change event.
 * This event is triggered when the scroll state of the <b>Swiper</b> component changes during user dragging,
 * during the animation phase after the user lifts their finger, or upon stopping of scrolling.
 * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
 * {@link ArkUI_NodeComponentEvent}. \n
 * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
 * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: current scroll state. The parameter type is
 * {@link ArkUI_ScrollState}. \n
 *
 * @since 20
 */
NODE_SWIPER_EVENT_ON_SCROLL_STATE_CHANGED = 1001008,
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_SWIPER_SWIPER_EVENT_ENUM_H
/** @} */