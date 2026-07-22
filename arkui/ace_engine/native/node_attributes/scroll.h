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
 * @file scroll.h
 *
 * @brief Provides shared scroll-related enum definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_SCROLL_SCROLL_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_SCROLL_SCROLL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the effects used at the edges of the component when the boundary of the scrollable content is
 * reached. The default value is **ARKUI_EDGE_EFFECT_NONE** for the **Grid**, **Scroll**, and **WaterFlow** components,
 * and **ARKUI_EDGE_EFFECT_SPRING** for the **List** component.
 *
 * @since 12
 */
typedef enum {
    /**
     * Spring effect. When at one of the edges, the component can move beyond the bounds based on the initial speed or
     * through touches, and produces a bounce effect when the user releases their finger.
     */
    ARKUI_EDGE_EFFECT_SPRING = 0,

    /**
     * Fade effect. When at one of the edges, the component produces a fade effect.
     */
    ARKUI_EDGE_EFFECT_FADE,

    /**
     * No effect when the component is at one of the edges.
     */
    ARKUI_EDGE_EFFECT_NONE,
} ArkUI_EdgeEffect;

/**
 * @brief Enumerates the text control scrollbar states.
 *
 * @since 22
 */
typedef enum {
    /**
     * Not displayed.
     */
    ARKUI_BAR_STATE_OFF = 0,

    /**
     * Displayed on demand (The scrollbar is displayed when being touched and disappears 2 seconds later.)
     */
    ARKUI_BAR_STATE_AUTO = 1,

    /**
     * Always displayed.
     */
    ARKUI_BAR_STATE_ON = 2,
} ArkUI_BarState;

/**
 * @brief Enumerates the edges for which the effect takes effect when the boundary of the scrollable content is reached.
 *
 * @since 18
 */
typedef enum {
    /**
     * Start edge.
     */
    ARKUI_EFFECT_EDGE_START = 1,

    /**
     * End edge.
     */
    ARKUI_EFFECT_EDGE_END = 2,
} ArkUI_EffectEdge;

/**
 * @brief Enumerates the scrolling directions of the {@link Scroll} component.
 *
 * @since 12
 */
typedef enum {
    /**
     * Vertical scrolling only.
     */
    ARKUI_SCROLL_DIRECTION_VERTICAL = 0,

    /**
     * Horizontal scrolling only.
     */
    ARKUI_SCROLL_DIRECTION_HORIZONTAL,

    /**
     * Scrolling disabled.
     */
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
    /**
     * No alignment mode.
     */
    ARKUI_SCROLL_SNAP_ALIGN_NONE = 0,

    /**
     * The first item in the view is aligned at the start of the list.
     */
    ARKUI_SCROLL_SNAP_ALIGN_START,

    /**
     * The middle items in the view are aligned in the center of the list.
     */
    ARKUI_SCROLL_SNAP_ALIGN_CENTER,

    /**
     * The last item in the view is aligned at the end of the list.
     */
    ARKUI_SCROLL_SNAP_ALIGN_END,
} ArkUI_ScrollSnapAlign;

/**
 * @brief Enumerates scroll snap animation speeds for list components.
 *
 * @since 22
 */
typedef enum {
    /**
     * Normal scroll snap animation speed.
     */
    ARKUI_SCROLL_SNAP_ANIMATION_NORMAL = 0,

    /**
     * Slow scroll snap animation speed.
     */
    ARKUI_SCROLL_SNAP_ANIMATION_SLOW = 1,
} ArkUI_ScrollSnapAnimationSpeed;

/**
 * @brief Enumerates the scrollbar display modes.
 *
 * @since 12
 */
typedef enum {
    /**
     * Not displayed.
     */
    ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF = 0,

    /**
     * Displayed when the screen is touched and hidden after 2s.
     */
    ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO,

    /**
     * Always displayed.
     */
    ARKUI_SCROLL_BAR_DISPLAY_MODE_ON,
} ArkUI_ScrollBarDisplayMode;

/**
 * @brief Enumerates the content clipping modes of scrollable components.
 *
 * @since 18
 */
typedef enum {
    /**
     * Clip to the content area only.
     */
    ARKUI_CONTENT_CLIP_MODE_CONTENT_ONLY = 0,

    /**
     * Clip to the component's boundary area.
     */
    ARKUI_CONTENT_CLIP_MODE_BOUNDARY,

    /**
     * Clip to the {@link safe area} configured for the component.
     */
    ARKUI_CONTENT_CLIP_MODE_SAFE_AREA,
} ArkUI_ContentClipMode;

/**
 * @brief Enumerates nested scrolling modes.
 *
 * @since 12
 */
typedef enum {
    /** The scrolling is contained within the component, and no scroll chaining occurs, that is, the parent component
     * does not scroll when the component scrolling reaches the boundary. */
    ARKUI_SCROLL_NESTED_MODE_SELF_ONLY = 0,

    /**
     * The component scrolls first, and when it hits the boundary, the parent component scrolls. When the parent
     * component hits the boundary, its edge effect is displayed. If no edge effect is specified for the parent
     * component, the edge effect of the child component is displayed instead.
     */
    ARKUI_SCROLL_NESTED_MODE_SELF_FIRST,

    /**
     * The parent component scrolls first, and when it hits the boundary, the component scrolls. When the component
     * hits the boundary, its edge effect is displayed. If no edge effect is specified for the component, the edge
     * effect of the parent component is displayed instead.
     */
    ARKUI_SCROLL_NESTED_MODE_PARENT_FIRST,
    /** The component and its parent component scroll at the same time. When both the component and its parent component
     *  hit the boundary, the edge effect of the component is displayed. If no edge effect is specified for the
     *  component, the edge effect of the parent component is displayed instead. */
    ARKUI_SCROLL_NESTED_MODE_PARALLEL,
} ArkUI_ScrollNestedMode;

/**
 * @brief Enumerates the edges to which the component scrolls.
 *
 * @since 12
 */
typedef enum {
    /**
     * Top edge in the vertical direction.
     */
    ARKUI_SCROLL_EDGE_TOP = 0,

    /**
     * Bottom edge in the vertical direction.
     */
    ARKUI_SCROLL_EDGE_BOTTOM,

    /**
     * Start position in the horizontal direction.
     */
    ARKUI_SCROLL_EDGE_START,

    /**
     * End position in the horizontal direction.
     */
    ARKUI_SCROLL_EDGE_END,
} ArkUI_ScrollEdge;

/**
 * @brief Defines how the list item to scroll to is aligned with the container.
 *
 * @since 12
 */
typedef enum {
    /**
     * The start edge of the list item is flush with the start edge of the container.
     */
    ARKUI_SCROLL_ALIGNMENT_START = 0,

    /**
     * The list item is centered along the main axis of the container.
     */
    ARKUI_SCROLL_ALIGNMENT_CENTER,

    /**
     * The end edge of the list item is flush with the end edge of the container.
     */
    ARKUI_SCROLL_ALIGNMENT_END,

    /**
     * The list item is automatically aligned. If the item is fully contained within the display area, no adjustment is
     * performed. Otherwise, the item is aligned so that its start or end edge is flush with the start or end edge of
     * the container, whichever requires a shorter scrolling distance.
     */
    ARKUI_SCROLL_ALIGNMENT_AUTO,
} ArkUI_ScrollAlignment;

/**
 * @brief Enumerates the scrolling states.
 *
 * @since 12
 */
typedef enum {
    /**
     * Idle. The container enters this state when an API in the controller is used to scroll the container or when the
     * scrollbar is dragged.
     */
    ARKUI_SCROLL_STATE_IDLE = 0,

    /**
     * Scrolling. The container enters this state when the user drags the container to scroll.
     */
    ARKUI_SCROLL_STATE_SCROLL,

    /**
     * Inertial scrolling. The container enters this state when inertial scrolling occurs or when the container bounces
     * back after being released from a fling.
     */
    ARKUI_SCROLL_STATE_FLING,
} ArkUI_ScrollState;

/**
 * @brief Enumerates scroll sources.
 *
 * @since 12
 */
typedef enum {
    /**
     * Finger dragging.
     */
    ARKUI_SCROLL_SOURCE_DRAG = 0,

    /**
     * Inertia scrolling after finger dragging.
     */
    ARKUI_SCROLL_SOURCE_FLING,

    /**
     * {@link EdgeEffect.Spring} for boundary crossing.
     */
    ARKUI_SCROLL_SOURCE_EDGE_EFFECT,

    /**
     * User input other than dragging, such as mouse wheel and keyboard events.
     */
    ARKUI_SCROLL_SOURCE_OTHER_USER_INPUT,

    /**
     * Scrollbar dragging.
     */
    ARKUI_SCROLL_SOURCE_SCROLL_BAR,

    /**
     * Inertial scrolling after scrollbar dragging.
     */
    ARKUI_SCROLL_SOURCE_SCROLL_BAR_FLING,

    /**
     * Scrolling by the scroll controller (without animation).
     */
    ARKUI_SCROLL_SOURCE_SCROLLER,

    /**
     * Scrolling by the scroll controller (with animation).
     */
    ARKUI_SCROLL_SOURCE_ANIMATION,
} ArkUI_ScrollSource;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_SCROLL_SCROLL_H
/** @} */
