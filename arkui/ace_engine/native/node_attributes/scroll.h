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
 * @brief ArkUI Scroll related enums on the native side.
 *
 * @since 12
 */

/**
 * @file node_scroll.h
 *
 * @brief Provides shared scroll-related enum definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUIKit
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_SCROLL_SCROLL_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_SCROLL_SCROLL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the effects used at the edges of the component when the boundary of the scrollable content is
 * reached.
 *
 * @since 12
 */
typedef enum {
    /** Spring effect. When at one of the edges, the component can move beyond the bounds based on the initial
     *  speed or through touches, and produces a bounce effect when the user releases their finger. */
    ARKUI_EDGE_EFFECT_SPRING = 0,
    /** Fade effect. When at one of the edges, the component produces a fade effect. */
    ARKUI_EDGE_EFFECT_FADE,
    /** No effect after the scrollbar is moved to the edge. */
    ARKUI_EDGE_EFFECT_NONE,
} ArkUI_EdgeEffect;

/**
 * @brief Enumerates the status of the scroll bar.
 *
 * @since 22
 */
typedef enum {
    /** Not displayed. */
    ARKUI_BAR_STATE_OFF = 0,
    /** On-demand display. */
    ARKUI_BAR_STATE_AUTO = 1,
    /** Resident display. */
    ARKUI_BAR_STATE_ON = 2,
} ArkUI_BarState;

/**
 * @brief Enumerates the edges for which the effect takes effect when the boundary of the scrollable content is reached.
 *
 * @since 18
 */
typedef enum {
    /** Start edge. */
    ARKUI_EFFECT_EDGE_START = 1,
    /** End edge. */
    ARKUI_EFFECT_EDGE_END = 2,
} ArkUI_EffectEdge;

/**
 * @brief Enumerates the scroll directions for the <b><Scroll></b> component.
 *
 * @since 12
 */
typedef enum {
    /** Only vertical scrolling is supported. */
    ARKUI_SCROLL_DIRECTION_VERTICAL = 0,
    /** Only horizontal scrolling is supported. */
    ARKUI_SCROLL_DIRECTION_HORIZONTAL,
    /** Scrolling is not allowed. */
    ARKUI_SCROLL_DIRECTION_NONE = 3,
    /**
     * Free scrolling in both directions.
     *
     * @since 20
     */
    ARKUI_SCROLL_DIRECTION_FREE = 4,
} ArkUI_ScrollDirection;

/**
 * @brief Enumerates the alignment modes of list items when scrolling ends.
 *
 * @since 12
 */
typedef enum {
    /** No alignment. This is the default value. */
    ARKUI_SCROLL_SNAP_ALIGN_NONE = 0,
    /** The first item in the view is aligned at the start of the list. */
    ARKUI_SCROLL_SNAP_ALIGN_START,
    /** The middle items in the view are aligned in the center of the list. */
    ARKUI_SCROLL_SNAP_ALIGN_CENTER,
    /** The last item in the view is aligned at the end of the list. */
    ARKUI_SCROLL_SNAP_ALIGN_END,
} ArkUI_ScrollSnapAlign;

/**
 * @brief Enumerates the scroll snap animation speeds for lists.
 *
 * @since 22
 */
typedef enum {
    /** Normal scroll snap animation speed. */
    ARKUI_SCROLL_SNAP_ANIMATION_NORMAL = 0,
    /** Slow scroll snap animation speed. */
    ARKUI_SCROLL_SNAP_ANIMATION_SLOW = 1,
} ArkUI_ScrollSnapAnimationSpeed;

/**
 * @brief Enumerates the scrollbar display modes.
 *
 * @since 12
 */
typedef enum {
    /** Hide. */
    ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF = 0,
    /** Display on demand (displays when the screen is touched and disappears after 2s). */
    ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO,
    /** Always display. */
    ARKUI_SCROLL_BAR_DISPLAY_MODE_ON,
} ArkUI_ScrollBarDisplayMode;

/**
 * @brief Enumerates the content clipping modes of scrollable components.
 *
 * @since 18
 */
typedef enum {
    /** clip by content */
    ARKUI_CONTENT_CLIP_MODE_CONTENT_ONLY = 0,
    /** clip by boundary */
    ARKUI_CONTENT_CLIP_MODE_BOUNDARY,
    /** clip by safe area padding */
    ARKUI_CONTENT_CLIP_MODE_SAFE_AREA,
} ArkUI_ContentClipMode;

/**
 * @brief Defines nested scrolling options.
 *
 * @since 12
 */
typedef enum {
    /** The scrolling is contained within the component, and no scroll chaining occurs, that is, the parent component
     * does not scroll when the component scrolling reaches the boundary. */
    ARKUI_SCROLL_NESTED_MODE_SELF_ONLY = 0,
    /** The component scrolls first, and when it hits the boundary, the parent component scrolls.
     *  When the parent component hits the boundary, its edge effect is displayed. If no edge
     *  effect is specified for the parent component, the edge effect of the child component is displayed instead. */
    ARKUI_SCROLL_NESTED_MODE_SELF_FIRST,
    /** The parent component scrolls first, and when it hits the boundary, the component scrolls.
     *  When the component hits the boundary, its edge effect is displayed. If no edge effect is specified for the
     *  component, the edge effect of the parent component is displayed instead. */
    ARKUI_SCROLL_NESTED_MODE_PARENT_FIRST,
    /** The component and its parent component scroll at the same time. When both the component and its parent component
     *  hit the boundary, the edge effect of the component is displayed. If no edge effect is specified for the
     *  component, the edge effect of the parent component is displayed instead. */
    ARKUI_SCROLL_NESTED_MODE_PARALLEL,
} ArkUI_ScrollNestedMode;

/**
 * @brief Defines the edge to which the component scrolls.
 *
 * @since 12
 */
typedef enum {
    /** Top edge in the vertical direction. */
    ARKUI_SCROLL_EDGE_TOP = 0,
    /** Bottom edge in the vertical direction. */
    ARKUI_SCROLL_EDGE_BOTTOM,
    /** Start position in the horizontal direction. */
    ARKUI_SCROLL_EDGE_START,
    /** End position in the horizontal direction. */
    ARKUI_SCROLL_EDGE_END,
} ArkUI_ScrollEdge;

/**
 * @brief Alignment when scrolling to specific items.
 *
 * @since 12
 */
typedef enum {
    /** Align the head. Align the head of the specified item with the head of the container.*/
    ARKUI_SCROLL_ALIGNMENT_START = 0,
    /** Center alignment. Align the axis direction of the specified item to the center of the container.*/
    ARKUI_SCROLL_ALIGNMENT_CENTER,
    /** Tail alignment. Align the tail of the specified item with the tail of the container.*/
    ARKUI_SCROLL_ALIGNMENT_END,
    /** Automatic alignment. If the specified item is completely in the display area, no adjustments will be made.
     * Otherwise, according to the principle of the shortest sliding distance, align the head or tail of the specified
     * item with the container, so that the specified item is completely in the display area.*/
    ARKUI_SCROLL_ALIGNMENT_AUTO,
} ArkUI_ScrollAlignment;

/**
 * @brief Define the current scrolling state.
 *
 * @since 12
 */
typedef enum {
    /** Idle state. Trigger when using the method provided by the controller to control scrolling, and trigger when
     * dragging the scroll bar to scroll.*/
    ARKUI_SCROLL_STATE_IDLE = 0,
    /** Scroll state. Triggered when dragging the container with fingers to scroll.*/
    ARKUI_SCROLL_STATE_SCROLL,
    /** Inertial rolling state. Triggered when inertia rolling and bouncing back to the edge are performed after
     * releasing the hand quickly.*/
    ARKUI_SCROLL_STATE_FLING,
} ArkUI_ScrollState;

/**
 * @brief Define the rolling source enumeration value.
 *
 * @since 12
 */
typedef enum {
    /** Finger drag. */
    ARKUI_SCROLL_SOURCE_DRAG = 0,
    /** Inertial roll after finger drag. */
    ARKUI_SCROLL_SOURCE_FLING,
    /** Execute the EdgeEffect.Spring edge effect when crossing the boundary.*/
    ARKUI_SCROLL_SOURCE_EDGE_EFFECT,
    /** Other user input other than dragging, such as mouse wheel, keyboard events, etc.*/
    ARKUI_SCROLL_SOURCE_OTHER_USER_INPUT,
    /** Drag the scroll bar.*/
    ARKUI_SCROLL_SOURCE_SCROLL_BAR,
    /** Inertia scrolling after dragging the scroll bar.*/
    ARKUI_SCROLL_SOURCE_SCROLL_BAR_FLING,
    /** The scroll controller causes unanimated scrolling.*/
    ARKUI_SCROLL_SOURCE_SCROLLER,
    /** The scroll controller causes the scroll to drive the painting.*/
    ARKUI_SCROLL_SOURCE_ANIMATION,
} ArkUI_ScrollSource;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_SCROLL_SCROLL_H
/** @} */
