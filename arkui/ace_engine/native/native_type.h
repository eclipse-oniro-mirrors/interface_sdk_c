/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file native_type.h
 *
 * @brief Defines the common types for the native module.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_TYPE_H
#define ARKUI_NATIVE_TYPE_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#include "drawable_descriptor.h"
#include "node_attributes/embedded_component.h"
#include "node_attributes/xcomponent.h"

#include "node_attributes/common_attributes.h"
#include "node_attributes/navigation_router/navigation_router.h"
#include "node_attributes/swiper/swiper.h"
#include "node_attributes/image_animator.h"
#include "node_attributes/image.h"
#include "node_attributes/picker.h"
#include "node_attributes/text_common.h"
#include "node_attributes/text.h"
#include "node_attributes/text_input.h"
#include "node_attributes/text_area.h"
#include "node_attributes/rich_editor.h"
#include "node_attributes/image_span.h"
#include "node_attributes/custom_span.h"
#include "node_attributes/progress.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the ArkUI native component object.
 *
 * @since 12
 */
struct ArkUI_Node;

/**
 * @brief Defines the pointer type of the ArkUI node content
 *
 * @since 12
 */
typedef struct ArkUI_NodeContent* ArkUI_NodeContentHandle;

/**
 * @brief Defines the custom dialog box controller of ArkUI on the native side.
 *
 * @since 12
 */
struct ArkUI_NativeDialog;

/**
 * @brief Sets the size constraints of a component during component layout.
 *
 * @since 12
 */
typedef struct ArkUI_LayoutConstraint ArkUI_LayoutConstraint;

/**
 * @brief Defines the structure of the component drawing context.
 *
 * @since 12
 */
typedef struct ArkUI_DrawContext ArkUI_DrawContext;

/**
 * @brief Defines the pointer to the ArkUI native component object.
 *
 * @since 12
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

/**
 * @brief Defines the pointer to the custom dialog box controller of ArkUI on the native side.
 *
 * @since 12
 */
typedef struct ArkUI_NativeDialog* ArkUI_NativeDialogHandle;

/**
 * @brief Defines information about gesture collection interception.
 *
 * @since 26.0.0
 */
typedef struct ArkUI_GestureCollectInterceptInfo ArkUI_GestureCollectInterceptInfo;

/**
 * @brief Defines the return value structure for the <b>onGetIrregularSizeByIndex</b> callback
 * in <b>Grid</b> layout options.
 *
 * @since 22
 */
typedef struct {
    /** Number of rows occupied by the <b>GridItem</b> component. */
    uint32_t rowSpan;
    /** Number of columns occupied by the <b>GridItem</b> component. */
    uint32_t columnSpan;
} ArkUI_GridItemSize;

/**
 * @brief Defines the return value structure for the <b>onGetRectByIndex</b> callback in <b>Grid</b> layout options.
 *
 * @since 22
 */
typedef struct {
    /** Starting row position of the <b>GridItem</b> component. */
    uint32_t rowStart;
    /** Starting column position of the <b>GridItem</b> component. */
    uint32_t columnStart;
    /** Number of rows occupied by the <b>GridItem</b> component. */
    uint32_t rowSpan;
    /** Number of columns occupied by the <b>GridItem</b> component. */
    uint32_t columnSpan;
} ArkUI_GridItemRect;

/**
 * @brief Defines the <b>Grid</b> layout options.
 *
 * @since 22
 */
typedef struct ArkUI_GridLayoutOptions ArkUI_GridLayoutOptions;

/**
 * @brief Defines the water flow section configuration.
 *
 * @since 12
 */
typedef struct ArkUI_WaterFlowSectionOption ArkUI_WaterFlowSectionOption;

/**
 * @brief Define the configuration information of the Item within the ListitemSwipeActionOption method.
 *
 * @since 12
 */
typedef struct ArkUI_ListItemSwipeActionItem ArkUI_ListItemSwipeActionItem;

/**
 * @brief Define the configuration information for the ListitemSwipeActionOption method.
 *
 * @since 12
 */
typedef struct ArkUI_ListItemSwipeActionOption ArkUI_ListItemSwipeActionOption;

/**
 * @brief Defines the ArkUI native context object.
 *
 * @since 12
 */
struct ArkUI_Context;

/**
  * @brief Defines the pointer to the context instance object pointer definition of ArkUI on the native side.
  *
  * @since 12
  */
typedef struct ArkUI_Context* ArkUI_ContextHandle;

/**
  * @brief specifies the alignment rules for subcomponents set in relative containers.
  *
  * @since 12
  */
typedef struct ArkUI_AlignmentRuleOption ArkUI_AlignmentRuleOption;

/**
  * @brief guideLine parameters, used to define the id, direction and position of the guideline.
  *
  * @since 12
  */
typedef struct ArkUI_GuidelineOption ArkUI_GuidelineOption;

/**
  * @brief barrier parameter, used to define the id,
  * direction and components of the barrier that it depends on when generating it.
  *
  * @since 12
  */
typedef struct ArkUI_BarrierOption ArkUI_BarrierOption;

/**
 * @brief Define the ChildrenMainSize class information for a List.
 *
 * @since 12
*/
typedef struct ArkUI_ListChildrenMainSize ArkUI_ListChildrenMainSize;

/**
 * @brief Defines the accessibility state for the component.
 *
 * @since 12
 */
typedef struct ArkUI_AccessibilityState ArkUI_AccessibilityState;

/**
 * @brief Defines the accessibility value for the component.
 *
 * @since 12
 */
typedef struct ArkUI_AccessibilityValue ArkUI_AccessibilityValue;

/**
 * @brief Define the information of the Custom Property class for custom properties.
 *
 * @since 14
 */
typedef struct ArkUI_CustomProperty ArkUI_CustomProperty;

/**
 * @brief Define the information of the HostWindowInfo class for window properties.
 *
 * @since 15
 */
typedef struct ArkUI_HostWindowInfo ArkUI_HostWindowInfo;

/**
 * @brief Define ActiveChildenInfo class information.
 *
 * @since 14
 */
typedef struct ArkUI_ActiveChildrenInfo ArkUI_ActiveChildrenInfo;

/**
 * @brief The cross-language option.
 *
 * @since 15
 */
typedef struct ArkUI_CrossLanguageOption ArkUI_CrossLanguageOption;

/**
 * @brief Define the Edges describing the position of a component by distances to the container's four edges.
 *
 * @since 21
 */
typedef struct ArkUI_PositionEdges ArkUI_PositionEdges;

/**
 * @brief Defines the PixelRound policy of a component's four edges.
 *
 * @since 21
 */
typedef struct ArkUI_PixelRoundPolicy ArkUI_PixelRoundPolicy;

/**
 * @brief Defines the selected drag preview style configuration.
 * @since 23
 */
typedef struct ArkUI_SelectedDragPreviewStyle ArkUI_SelectedDragPreviewStyle;

/**
 * @brief Defines the event callback type.
 *
 * @since 12
 */
typedef struct {
    /** Custom type, data of a user-defined type that is passed as a parameter during callbacks. */
    void* userData;
    /** Event callback. */
    void (*callback)(void* userData);
} ArkUI_ContextCallback;
/**
 * @brief Provides the number types of ArkUI in the native code.
 *
 * @since 12
 */
typedef union {
    /** Floating-point type, used to store a floating-point value. */
    float f32;
    /** Signed integer, used to store a signed integer value. */
    int32_t i32;
    /** Unsigned integer, used to store an unsigned integer value. */
    uint32_t u32;
} ArkUI_NumberValue;

/**
 * @brief Enumerates the alignment modes.
 *
 * @since 12
 */
typedef enum {
    /** Top start. */
    ARKUI_ALIGNMENT_TOP_START = 0,
    /** Top center. */
    ARKUI_ALIGNMENT_TOP,
    /** Top end. */
    ARKUI_ALIGNMENT_TOP_END,
    /** Vertically centered start. */
    ARKUI_ALIGNMENT_START,
    /** Horizontally and vertically centered. */
    ARKUI_ALIGNMENT_CENTER,
    /** Vertically centered end. */
    ARKUI_ALIGNMENT_END,
    /** Bottom start. */
    ARKUI_ALIGNMENT_BOTTOM_START,
    /** Horizontally centered on the bottom. */
    ARKUI_ALIGNMENT_BOTTOM,
    /** Bottom end. */
    ARKUI_ALIGNMENT_BOTTOM_END,
} ArkUI_Alignment;

/**
 * @brief Enumerates the text copy and paste modes.
 *
 * @since 12
 */
typedef enum {
    /** Copy is not allowed. */
    ARKUI_COPY_OPTIONS_NONE = 0,
    /** Intra-application copy is allowed. */
    ARKUI_COPY_OPTIONS_IN_APP,
    /** Intra-device copy is allowed. */
    ARKUI_COPY_OPTIONS_LOCAL_DEVICE,
    /** Cross-device copy is allowed. */
    ARKUI_COPY_OPTIONS_CROSS_DEVICE,
} ArkUI_CopyOptions;

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
 * @brief Enumerates the focus wrap mode of components.
 *
 * @since 20
 */
typedef enum {
    /** Default mode, where focus does not wrap when arrow keys are used. */
    ARKUI_FOCUS_WRAP_MODE_DEFAULT = 0,
    /** Focus wraps automatically when arrow keys are used. */
    ARKUI_FOCUS_WRAP_WITH_ARROW = 1,
} ArkUI_FocusWrapMode;

/**
 * @brief Specifies the number of columns for different responsive breakpoint specifications.
 *
 * @since 22
 */
typedef enum {
    /** No responsive breakpoint configuration. */
    ARKUI_ITEMFILLPOLICY_NONE = -1,
    /**
     * Default responsive layout:
     * <b>List</b> or <b>Swiper</b> component: 1 column (SM or smaller), 2 columns (MD), 3 columns (LG or larger).
     * <b>Grid</b> or <b>WaterFlow</b> component: 2 columns (SM or smaller), 3 columns (MD), 5 columns (LG or larger).
     */
    ARKUI_ITEMFILLPOLICY_DEFAULT = 0,
    /** 1 column (SM or smaller), 2 columns (MD), 3 columns (LG or larger). */
    ARKUI_ITEMFILLPOLICY_SM1MD2LG3 = 1,
    /** 2 columns (SM or smaller), 3 columns (MD), 5 columns (LG or larger). */
    ARKUI_ITEMFILLPOLICY_SM2MD3LG5 = 2,
} ArkUI_ItemFillPolicy;

/**
 * @brief Enumerates the grid item alignment modes.
 *
 * @since 22
 */
typedef enum {
    /** Use the default alignment mode of the grid. */
    GRID_ITEM_ALIGNMENT_DEFAULT = 0,
    /** Set the height of all grid items in a row to match the height of the tallest item in that row. */
    GRID_ITEM_ALIGNMENT_STRETCH = 1,
} ArkUI_GridItemAlignment;

/**
 * @brief Enumerates styles of grid items.
 *
 * @since 22
 */
typedef enum {
    /** No style. */
    GRID_ITEM_STYLE_NONE = 0,
    /** Hover or press style. */
    GRID_ITEM_STYLE_PLAIN = 1,
} ArkUI_GridItemStyle;

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
 * @brief Enumerates the scroll directions for the <b><List></b> component.
 *
 * @since 12
 */
typedef enum {
    /** Only vertical scrolling is supported. */
    ARKUI_AXIS_VERTICAL = 0,
    /** Only horizontal scrolling is supported. */
    ARKUI_AXIS_HORIZONTAL,
} ArkUI_Axis;

/**
 * @brief Enumerates the modes for pinning the header to the top or the footer to the bottom.
 *
 * @since 12
 */
typedef enum {
    /** In the list item group, the header is not pinned to the top, and the footer is not pinned to the bottom. */
    ARKUI_STICKY_STYLE_NONE = 0,
    /** In the list item group, the header is pinned to the top, and the footer is not pinned to the bottom. */
    ARKUI_STICKY_STYLE_HEADER = 1,
    /** In the list item group, the footer is pinned to the bottom, and the header is not pinned to the top. */
    ARKUI_STICKY_STYLE_FOOTER = 2,
    /** In the list item group, the footer is pinned to the bottom, and the header is pinned to the top. */
    ARKUI_STICKY_STYLE_BOTH = 3,
} ArkUI_StickyStyle;

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
 * @brief Enumerates the layout modes of the WaterFlow component.
 *
 * @since 18
 */
typedef enum {
    /** Layout items from top to viewport. */
    ARKUI_WATER_FLOW_LAYOUT_MODE_ALWAYS_TOP_DOWN = 0,
    /** Layout items in viewport. */
    ARKUI_WATER_FLOW_LAYOUT_MODE_SLIDING_WINDOW,
} ArkUI_WaterFlowLayoutMode;

/**
 * @brief Enumerates the border styles.
 *
 * @since 12
 */
typedef enum {
    /** Solid border. */
    ARKUI_BORDER_STYLE_SOLID = 0,
    /** Dashed border. */
    ARKUI_BORDER_STYLE_DASHED,
    /** Dotted border. */
    ARKUI_BORDER_STYLE_DOTTED,
} ArkUI_BorderStyle;

/**
 * @brief Enumerates the accessibility modes.
 *
 * @since 12
 */
typedef enum {
    /** Whether the component can be identified by the accessibility service is dependent on the component. */
    ARKUI_ACCESSIBILITY_MODE_AUTO = 0,
    /** The component can be identified by the accessibility service. */
    ARKUI_ACCESSIBILITY_MODE_ENABLED,
    /** The component cannot be identified by the accessibility service. */
    ARKUI_ACCESSIBILITY_MODE_DISABLED,
    /** The component and all its child components cannot be identified by the accessibility service. */
    ARKUI_ACCESSIBILITY_MODE_DISABLED_FOR_DESCENDANTS,
} ArkUI_AccessibilityMode;

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
 * @brief Enumerates the types of the slider in the block direction.
 *
 * @since 12
 */
typedef enum {
    /** Round slider. */
    ARKUI_SLIDER_BLOCK_STYLE_DEFAULT = 0,
    /** Slider with an image background. */
    ARKUI_SLIDER_BLOCK_STYLE_IMAGE,
    /** Slider in a custom shape. */
    ARKUI_SLIDER_BLOCK_STYLE_SHAPE,
} ArkUI_SliderBlockStyle;

/**
 * @brief Enumerates the scroll directions of the slider.
 *
 * @since 12
 */
typedef enum {
    /** Vertical direction. */
    ARKUI_SLIDER_DIRECTION_VERTICAL = 0,
    /** Horizontal direction. */
    ARKUI_SLIDER_DIRECTION_HORIZONTAL,
} ArkUI_SliderDirection;

/**
 * @brief Enumerates the slider styles.
 *
 * @since 12
 */
typedef enum {
    /** The slider is on the slider track. */
    ARKUI_SLIDER_STYLE_OUT_SET = 0,
    /** The slider is in the slider track. */
    ARKUI_SLIDER_STYLE_IN_SET,
    /** No slider. */
    ARKUI_SLIDER_STYLE_NONE,
} ArkUI_SliderStyle;

/**
 * @brief Enumerates the shapes of the check box
 *
 * @since 12
 */
typedef enum {
    /** Circle. */
    ArkUI_CHECKBOX_SHAPE_CIRCLE = 0,
    /** Rounded square. */
    ArkUI_CHECKBOX_SHAPE_ROUNDED_SQUARE,
} ArkUI_CheckboxShape;

/**
 * @brief Enumerates the adaptive color modes.
 *
 * @since 12
 */
typedef enum {
    /** Adaptive color mode is not used. */
    ARKUI_ADAPTIVE_COLOR_DEFAULT = 0,
    /** Adaptive color mode is used. */
    ARKUI_ADAPTIVE_COLOR_AVERAGE,
} ArkUI_AdaptiveColor;

/**
 * @brief Enumerates the color modes.
 *
 * @since 12
 */
typedef enum {
    /** Following the system color mode. */
    ARKUI_COLOR_MODE_SYSTEM = 0,
    /** Light color mode. */
    ARKUI_COLOR_MODE_LIGHT,
    /** Dark color mode. */
    ARKUI_COLOR_MODE_DARK,
} ArkUI_ColorMode;

/**
 * @brief Enumerates the system color modes.
 *
 * @since 12
 */
typedef enum {
    /** Light color mode. */
    ARKUI_SYSTEM_COLOR_MODE_LIGHT = 0,
    /** Dark color mode. */
    ARKUI_SYSTEM_COLOR_MODE_DARK,
} ArkUI_SystemColorMode;



/**
 * @brief Enumerates the vertical alignment modes.
 *
 * @since 12
 */
typedef enum {
    /** Top aligned. */
    ARKUI_VERTICAL_ALIGNMENT_TOP = 0,
    /** Center aligned. This is the default alignment mode. */
    ARKUI_VERTICAL_ALIGNMENT_CENTER,
    /** Bottom aligned. */
    ARKUI_VERTICAL_ALIGNMENT_BOTTOM,
} ArkUI_VerticalAlignment;

/**
 * @brief Enumerates the alignment mode in the horizontal direction.
 *
 * @since 12
 */
typedef enum {
    /** Aligned with the start edge in the same direction as the language in use. */
    ARKUI_HORIZONTAL_ALIGNMENT_START = 0,
    /** Center aligned. This is the default alignment mode. */
    ARKUI_HORIZONTAL_ALIGNMENT_CENTER,
    /** Aligned with the end edge in the same direction as the language in use. */
    ARKUI_HORIZONTAL_ALIGNMENT_END,
} ArkUI_HorizontalAlignment;

/**
 * @brief Enumerates the modes in which components are laid out along the main axis of the container.
 *
 * @since 12
 */
typedef enum {
    /** Components are arranged from left to right. */
    ARKUI_DIRECTION_LTR = 0,
    /** Components are arranged from right to left. */
    ARKUI_DIRECTION_RTL,
    /** The default layout direction is used. */
    ARKUI_DIRECTION_AUTO = 3,
} ArkUI_Direction;

/**
 * @brief Enumerates the modes in which components are laid out along the cross axis of the container.
 *
 * @since 12
 */
typedef enum {
    /** The default configuration in the container is used. */
    ARKUI_ITEM_ALIGNMENT_AUTO = 0,
    /** The items in the container are aligned with the cross-start edge. */
    ARKUI_ITEM_ALIGNMENT_START,
    /** The items in the container are centered along the cross axis. */
    ARKUI_ITEM_ALIGNMENT_CENTER,
    /** The items in the container are aligned with the cross-end edge. */
    ARKUI_ITEM_ALIGNMENT_END,
    /** The items in the container are stretched and padded along the cross axis. */
    ARKUI_ITEM_ALIGNMENT_STRETCH,
    /** The items in the container are aligned in such a manner that their text baselines are aligned along the
     *  cross axis. */
    ARKUI_ITEM_ALIGNMENT_BASELINE,
} ArkUI_ItemAlignment;


/**
 * @brief Enumerates the vertical alignment modes.
 *
 * @since 12
 */
typedef enum {
    /** The child components are aligned with the start edge of the main axis. */
    ARKUI_FLEX_ALIGNMENT_START = 1,
    /** The child components are aligned in the center of the main axis. */
    ARKUI_FLEX_ALIGNMENT_CENTER = 2,
    /** The child components are aligned with the end edge of the main axis. */
    ARKUI_FLEX_ALIGNMENT_END = 3,
    /** The child components are evenly distributed along the main axis. The space between any two adjacent components
     *  is the same. The first component is aligned with the main-start, and the last component is aligned with
     *  the main-end. */
    ARKUI_FLEX_ALIGNMENT_SPACE_BETWEEN = 6,
    /** The child components are evenly distributed along the main axis. The space between any two adjacent components
     *  is the same. The space between the first component and main-start, and that between the last component and
     *  cross-main are both half the size of the space between two adjacent components. */
    ARKUI_FLEX_ALIGNMENT_SPACE_AROUND = 7,
    /** The child components are evenly distributed along the main axis. The space between the first component
     *  and main-start, the space between the last component and main-end, and the space between any two adjacent
     *  components are the same. */
    ARKUI_FLEX_ALIGNMENT_SPACE_EVENLY = 8,
} ArkUI_FlexAlignment;

/**
 * @brief Enumerates the directions of the main axis in the flex container.
 *
 * @since 12
 */
typedef enum {
    /** The child components are arranged in the same direction as the main axis runs along the rows. */
    ARKUI_FLEX_DIRECTION_ROW = 0,
    /** The child components are arranged in the same direction as the main axis runs down the columns. */
    ARKUI_FLEX_DIRECTION_COLUMN,
    /** The child components are arranged opposite to the <b>ROW</b> direction. */
    ARKUI_FLEX_DIRECTION_ROW_REVERSE,
    /** The child components are arranged opposite to the <b>COLUMN</b> direction. */
    ARKUI_FLEX_DIRECTION_COLUMN_REVERSE,
} ArkUI_FlexDirection;

/**
 * @brief Defines whether the flex container has a single line or multiple lines.
 *
 * @since 12
 */
typedef enum {
    /** The child components in the flex container are arranged in a single line, and they cannot overflow. */
    ARKUI_FLEX_WRAP_NO_WRAP = 0,
    /** The child components in the flex container are arranged in multiple lines, and they may overflow. */
    ARKUI_FLEX_WRAP_WRAP,
    /** The child components in the flex container are reversely arranged in multiple lines, and they may overflow. */
    ARKUI_FLEX_WRAP_WRAP_REVERSE,
} ArkUI_FlexWrap;

/**
 * @brief Defines the gradient color stop structure.
 *
 * @since 12
 */
typedef struct {
    /** Color array. */
    const uint32_t* colors;
    /** Position array. */
    float* stops;
    /** Length array. */
    int size;
} ArkUI_ColorStop;

/**
 * @brief Defines a mask area.
 *
 * @since 12
 */
typedef struct {
    /** X coordinate of the mask area. */
    float x;
    /** Y coordinate of the mask area. */
    float y;
    /** Width of the mask area. */
    float width;
    /** Height of the mask area. */
    float height;
} ArkUI_Rect;

/**
 * @brief Describes the width and height of a component.
 *
 * @since 12
 */
typedef struct {
    /** Width, in px. */
    int32_t width;
    /** Height, in px. */
    int32_t height;
} ArkUI_IntSize;

/**
 * @brief Describes the position of a component.
 *
 * @since 12
 */
typedef struct {
    /** Horizontal coordinate, in px. */
    int32_t x;
    /** Vertical coordinate, in px. */
    int32_t y;
} ArkUI_IntOffset;


/**
 * @brief Enumerates the alignment modes of items along the cross axis.
  *
 * @since 12
 */
typedef enum {
    /** The list items are packed toward the start edge of the list container along the cross axis. */
    ARKUI_LIST_ITEM_ALIGNMENT_START = 0,
    /** The list items are centered in the list container along the cross axis. */
    ARKUI_LIST_ITEM_ALIGNMENT_CENTER,
    /** The list items are packed toward the end edge of the list container along the cross axis. */
    ARKUI_LIST_ITEM_ALIGNMENT_END,
} ArkUI_ListItemAlignment;

/**
  * @brief defines the direction of the barrier line.
  *
  * @since 12
  */
typedef enum {
    /** The barrier is the leftmost of all its referencedIds. */
    ARKUI_BARRIER_DIRECTION_START = 0,
    /** The barrier is on the rightmost side of all its referencedIds. */
    ARKUI_BARRIER_DIRECTION_END,
    /** The barrier is at the top of all its referencedIds. */
    ARKUI_BARRIER_DIRECTION_TOP,
    /** The barrier is at the bottom of all its referencedIds. */
    ARKUI_BARRIER_DIRECTION_BOTTOM
} ArkUI_BarrierDirection;

/**
  * @brief defines the style of the chain.
  *
  * @since 12
  */
typedef enum {
    /** Components are evenly distributed among constraint anchor points. */
    ARKUI_RELATIVE_LAYOUT_CHAIN_STYLE_SPREAD = 0,
    /** Except for the first and last two sub-components,
      * other components are evenly distributed between the constraint anchor points. */
    ARKUI_RELATIVE_LAYOUT_CHAIN_STYLE_SPREAD_INSIDE,
    /** No gaps in subcomponents within the chain. */
    ARKUI_RELATIVE_LAYOUT_CHAIN_STYLE_PACKED,
} ArkUI_RelativeLayoutChainStyle;

/**
 * @brief Describes the margins of a component.
 *
 * @since 12
 */
typedef struct {
    /** Top margin, in vp. */
    float top;
    /** Right margin, in vp. */
    float right;
    /** Bottom margin, in vp. */
    float bottom;
    /** Left margin, in vp. */
    float left;
} ArkUI_Margin;

/**
 * @brief Enumerates the component units.
 *
 * @since 12
 */
typedef enum {
    /** Default, which is fp for fonts and vp for non-fonts. */
    ARKUI_LENGTH_METRIC_UNIT_DEFAULT = -1,
    /** px. */
    ARKUI_LENGTH_METRIC_UNIT_PX = 0,
    /** vp. */
    ARKUI_LENGTH_METRIC_UNIT_VP,
    /** fp. */
    ARKUI_LENGTH_METRIC_UNIT_FP
} ArkUI_LengthMetricUnit;


/**
 * @brief Enumerates the button types.
 *
 * @since 12
 */
typedef enum {
    /** Normal button (without rounded corners by default). */
    ARKUI_BUTTON_TYPE_NORMAL = 0,
    /** Capsule-type button (the round corner is half of the height by default). */
    ARKUI_BUTTON_TYPE_CAPSULE,
    /** Circle button. */
    ARKUI_BUTTON_TYPE_CIRCLE,
    /**
     * Rounded rectangle button.
     * @since 19
     */
    ARKUI_BUTTON_ROUNDED_RECTANGLE = 8
} ArkUI_ButtonType;

/**
 * @brief Define the pattern of element arrangement in the main axis direction of the Swiper component.
 *
 * @since 12
 */
typedef enum {
    /** In the folded state, when the ListItem slides in the opposite direction to the main axis,
     * the operation item is hidden.*/
    ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_COLLAPSED = 0,
    /** In the folded state, when the ListItem slides in the opposite direction to the spindle,
     * the operation item is displayed.*/
    ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_EXPANDED,
    /** Long distance state, the state of deleting a ListItem after it enters the long distance deletion area.*/
    ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_ACTIONING,
} ArkUI_ListItemSwipeActionState;

/**
 * @brief Define the explicit and implicit mode of the SwipeAction method for the Listitem component.
 *
 * @since 12
 */
typedef enum {
    /** The ListItem can continue to be scratched after the distance exceeds the size of the scratched component.*/
    ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_SPRING = 0,
    /** The sliding distance of the ListItem cannot exceed the size of the scratched component.*/
    ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_NONE,
} ArkUI_ListItemSwipeEdgeEffect;

/**
 * @brief Define error code enumeration values.
 *
 * @since 12
 */
typedef enum {
    /** @error No errors. */
    ARKUI_ERROR_CODE_NO_ERROR = 0,
    /** @error Parameter error. */
    ARKUI_ERROR_CODE_PARAM_INVALID = 401,
    /**
     * @error CAPI init error.
     * @since 18
     */
    ARKUI_ERROR_CODE_CAPI_INIT_ERROR = 500,
    /**
     * @error Internal error occurs, such as failure occurs because of the internal environment error,
     * or operation failed because of the internal execution failed.
     * @since 15
     */
    ARKUI_ERROR_CODE_INTERNAL_ERROR = 100001,
    /**
     * @error The XComponent is in invalid state.
     * @since 19
     */
    ARKUI_ERROR_CODE_XCOMPONENT_STATE_INVALID = 103501,
    /** @error The component does not support specific properties or events. */
    ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED = 106102,
    /** @error The corresponding operation does not support nodes created by ArkTS. */
    ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED = 106103,
    /** @error The lazy loading adapter is not bound to the component. */
    ARKUI_ERROR_CODE_ADAPTER_NOT_BOUND = 106104,
    /** @error The adapter already exists. */
    ARKUI_ERROR_CODE_ADAPTER_EXIST = 106105,
    /** @error The corresponding node already has a child node and cannot add an adapter. */
    ARKUI_ERROR_CODE_CHILD_NODE_EXIST = 106106,
    /** The parameter length in the parameter event exceeds the limit. */
    ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE = 106107,
    /** The data does not exist in the component event. */
    ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID = 106108,
    /** The component event does not support return values. */
    ARKUI_ERROR_CODE_NODE_EVENT_NO_RETURN = 106109,
    /**
     * @error The event type is not supported by the node.
     * @since 21
     */
    ARKUI_ERROR_CODE_NODE_UNSUPPORTED_EVENT_TYPE = 106110,
    /** The index value is invalid. */
    ARKUI_ERROR_CODE_NODE_INDEX_INVALID = 106200,
    /**  Failed to query route navigation information. */
    ARKUI_ERROR_CODE_GET_INFO_FAILED = 106201,
    /** The buffer size is not large enough. */
    ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR = 106202,
    /**
     * @error The node is not on main tree.
     * @since 15
     */
    ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE = 106203,
    /**
     * @error The node is running on invalid thread.
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_ON_INVALID_THREAD = 106204,
    /**
     * @error Force dark config is invalid.
     * @since 20
     */
    ARKUI_ERROR_CODE_FORCE_DARK_CONFIG_INVALID = 106205,
    /**
     * @error The node has already been adopted.
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_IS_ADOPTED = 106206,
    /**
     * @error This node already has a parent node.
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_HAS_PARENT = 106207,
    /**
     * @error The node cannot be adopted.
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_CAN_NOT_BE_ADOPTED = 106208,
    /**
     * @error The node cannot adopt children.
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_CAN_NOT_ADOPT_TO = 106209,
    /**
     * @error This child node is not adopted by the parent node.
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_IS_NOT_IN_ADOPTED_CHILDREN = 106210,
    /**
     * @error The node type is not custom node.
     * @since 20
     */
    ARKUI_ERROR_CODE_NOT_CUSTOM_NODE = 106401,
    /**
     * @error Node already has children.
     * @since 20
     */
    ARKUI_ERROR_CODE_CHILD_EXISTED = 106402,
    /**
     * @error RenderNode parent is existed.
     * @since 20
     */
    ARKUI_ERROR_CODE_RENDER_PARENT_EXISTED = 106403,
    /**
     * @error RenderNode child is not exist.
     * @since 20
     */
    ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST = 106404,
    /**
     * @error Param is out of range.
     * @since 20
     */
    ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE = 106405,
    /**
     * @error The RenderNode is obtained from a FrameNode.
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE = 106406,
    /**
     * @error The RenderNode is obtained from a FrameNode,
     * and its corresponding FrameNode is no longer in the adopted state.
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE = 106407,
    /**
     * @error The node is not adopted.
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_NOT_ADOPTED_NODE = 106408,
    /**
     * @error The node requesting focus is not focusable.
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE = 150001,
    /**
     * @error The node requesting focus has unfocusable ancestor.
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE_ANCESTOR = 150002,
    /**
     * @error The node requesting focus does not exists.
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT = 150003,
    /**
     * @error The snapshot taking is timeout.
     * @since 15
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT = 160002,
    /**
     * @error The provided color space or dynamic range mode is not supported. For details about the error codes,
     * see [Snapshot Error Codes](../apis-arkui/errorcode-snapshot.md).
     * @since 23
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_MODE_NOT_SUPPORTED = 160003,
    /**
     * @error The isAuto parameter of the color space or dynamic range mode is set to true for offscreen node snapshot.
     * For details about the error codes, see [Snapshot Error Codes](../apis-arkui/errorcode-snapshot.md).
     * @since 23
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_AUTO_NOT_SUPPORTED = 160004,
    /** The component is not a scroll container. */
    ARKUI_ERROR_CODE_NON_SCROLLABLE_CONTAINER = 180001,
    /** The buffer is not large enough. */
    ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH = 180002,
    /**
     * @error The event is not a clone event.
     * @since 15
     */
    ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT = 180003,
    /**
     * @error The component status is abnormal.
     * @since 15
     */
    ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL = 180004,
    /**
     * @error No component hit to respond to the event.
     * @since 15
     */
    ARKUI_ERROR_CODE_POST_CLONED_NO_COMPONENT_HIT_TO_RESPOND_TO_THE_EVENT = 180005,
    /**
     * @error Input event type not supported.
     * @since 20
     */
    ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED = 180006,
    /**
     * @error invalid styled string.
     * @since 14
     */
    ARKUI_ERROR_CODE_INVALID_STYLED_STRING = 180101,
    /**
     * @error The gesture recognizer type is not supported.
     * @since 18
     */
    ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED = 180102,
    /**
     * @error The uiContext is invalid.
     * @since 18
     */
    ARKUI_ERROR_CODE_UI_CONTEXT_INVALID = 190001,
    /**
     * @error The callback function is invalid.
     * @since 18
     */
    ARKUI_ERROR_CODE_CALLBACK_INVALID = 190002,
    /**
     * @error operation is not allowed for current drag drop pharse.
     * @since 19
     */
    ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED = 190004,
    /**
     * @error Parameter error.
     * @since 21
     */
    ARKUI_ERROR_CODE_PARAM_ERROR = 100023,
} ArkUI_ErrorCode;

/**
 * @brief Defines the state type for the accessibility checkbox.
 *
 * @since 12
 */
typedef enum {
    /** The Checkbox unchecked. */
    ARKUI_ACCESSIBILITY_UNCHECKED = 0,
    /** The Checkbox checked. */
    ARKUI_ACCESSIBILITY_CHECKED,
} ArkUI_AccessibilityCheckedState;

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

/**
 * @brief Define accessible action types.
 *
 * @since 12
 */
typedef enum {
    /** click action. */
    ARKUI_ACCESSIBILITY_ACTION_CLICK = 1 << 0,
    /** long click action. */
    ARKUI_ACCESSIBILITY_ACTION_LONG_CLICK = 1 << 1,
    /** cut action. */
    ARKUI_ACCESSIBILITY_ACTION_CUT = 1 << 2,
    /** copy action. */
    ARKUI_ACCESSIBILITY_ACTION_COPY = 1 << 3,
    /** paste action. */
    ARKUI_ACCESSIBILITY_ACTION_PASTE = 1 << 4,
} ArkUI_AccessibilityActionType;

/**
 * @brief defines the enumerated value of the extended security zone.
 *
 * @since 12
 */
typedef enum {
    /** The default security zone includes the status bar and navigation bar. */
    ARKUI_SAFE_AREA_TYPE_SYSTEM = 1,
    /** Non-secure areas of the device, such as bangs or hole holes. */
    ARKUI_SAFE_AREA_TYPE_CUTOUT = 1 << 1,
    /** Soft keyboard area. */
    ARKUI_SAFE_AREA_TYPE_KEYBOARD = 1 << 2,
} ArkUI_SafeAreaType;

/**
 * @brief Define an enum for the areas of the <b>ListItemGroup</b> component.
 *
 * @since 15
 */
typedef enum {
    /** Outside the area of the <b>ListItemGroup</b> component. */
    ARKUI_LIST_ITEM_GROUP_AREA_OUTSIDE = 0,
    /** Area when the <b>ListItemGroup</b> component does not have the header, footer, or list item. */
    ARKUI_LIST_ITEM_SWIPE_AREA_NONE,
    /** List item area of the <b>ListItemGroup</b> component. */
    ARKUI_LIST_ITEM_SWIPE_AREA_ITEM,
    /** Header area of the <b>ListItemGroup</b> component. */
    ARKUI_LIST_ITEM_SWIPE_AREA_HEADER,
    /** Footer area of the <b>ListItemGroup</b> component. */
    ARKUI_LIST_ITEM_SWIPE_AREA_FOOTER,
} ArkUI_ListItemGroupArea;

/**
 * @brief defines the enumerated value of the direction of the extended security zone.
 *
 * @since 12
 */
typedef enum {
    /** Upper area. */
    ARKUI_SAFE_AREA_EDGE_TOP = 1,
    /** Lower area. */
    ARKUI_SAFE_AREA_EDGE_BOTTOM = 1 << 1,
    /** Front area. */
    ARKUI_SAFE_AREA_EDGE_START = 1 << 2,
    /** Tail area. */
    ARKUI_SAFE_AREA_EDGE_END = 1 << 3,
} ArkUI_SafeAreaEdge;

/**
 * @brief defines the enumerated value of the customDialog's keyboard avoid mode.
 *
 * @since 15
 */
typedef enum {
    /** Defines avoid keyboard when keyboard shows. */
    ARKUI_KEYBOARD_AVOID_MODE_DEFAULT = 0,
    /** Defines not avoid keyboard when keyboard shows. */
    ARKUI_KEYBOARD_AVOID_MODE_NONE,
} ArkUI_KeyboardAvoidMode;

/**
 * @brief defines the enumerated value of area in hover mode.
 *
 * @since 15
 */
typedef enum {
    /** Layout top half screen when the phone in hover mode. */
    ARKUI_HOVER_MODE_AREA_TYPE_TOP = 0,
    /** Layout bottom half screen when the phone in hover mode. */
    ARKUI_HOVER_MODE_AREA_TYPE_BOTTOM,
} ArkUI_HoverModeAreaType;

/**
 * @brief Enumerates the expand modes.
 *
 * @since 15
 */
typedef enum {
    /** Not expand. */
    ARKUI_NOT_EXPAND = 0,
    /** Expand. */
    ARKUI_EXPAND = 1,
    /** Lazy expand. Expand the children of node if needed. */
    ARKUI_LAZY_EXPAND = 2,
} ArkUI_ExpandMode;

/**
 * @brief Enumerates the edge direction.
 *
 * @since 20
 */
typedef enum {
    /** Set all edge direction. */
    ARKUI_EDGE_DIRECTION_ALL = 0,
    /** Set left edge direction. */
    ARKUI_EDGE_DIRECTION_LEFT,
    /** Set right edge direction. */
    ARKUI_EDGE_DIRECTION_RIGHT,
    /** Set top edge direction. */
    ARKUI_EDGE_DIRECTION_TOP,
    /** Set bottom edge direction. */
    ARKUI_EDGE_DIRECTION_BOTTOM,
} ArkUI_EdgeDirection;
 
/**
 * @brief Enumerates the corner direction.
 *
 * @since 20
 */
typedef enum {
    /** Set all corner direction. */
    ARKUI_CORNER_DIRECTION_ALL = 0,
    /** Set top left corner direction. */
    ARKUI_CORNER_DIRECTION_TOP_LEFT,
    /** Set top right corner direction. */
    ARKUI_CORNER_DIRECTION_TOP_RIGHT,
    /** Set bottom left corner direction. */
    ARKUI_CORNER_DIRECTION_BOTTOM_LEFT,
    /** Set bottom right corner direction. */
    ARKUI_CORNER_DIRECTION_BOTTOM_RIGHT,
} ArkUI_CornerDirection;

/**
 * @brief Enumerates the PixelRoundPolicy.
 *
 * @since 21
 */
typedef enum {
    /** No Force round the component boundary coordinates to integer pixel. */
    ARKUI_PIXELROUNDCALCPOLICY_NOFORCEROUND = 0,
    /** Force ceil the component boundary coordinates to integer pixel. */
    ARKUI_PIXELROUNDCALCPOLICY_FORCECEIL,
    /** Force floor the component boundary coordinates to integer pixel. */
    ARKUI_PIXELROUNDCALCPOLICY_FORCEFLOOR,
} ArkUI_PixelRoundCalcPolicy;

/**
 * @brief Menu pop-up strategy.
 *
 * @since 23
 */
typedef enum {
    /** Determine whether to pop up the menu according to the underlying default logic. */
    ARKUI_MENU_POLICY_DEFAULT = 0,
    /** Never pop up the menu. */
    ARKUI_MENU_POLICY_HIDE = 1,
    /** Always pop up the menu. */
    ARKUI_MENU_POLICY_SHOW = 2,
} ArkUI_MenuPolicy;

/**
 * @brief Define the direction to expand the swipe action.
 *
 * @since 21
 */
typedef enum {
    /**
     * When the List direction is vertical, it indicates the left in LTR mode and right in RTL mode.
     * When the List direction is horizontal, it indicates the top.
     */
    ARKUI_LIST_ITEM_SWIPE_ACTION_DIRECTION_START = 0,
    /**
     * When the List direction is vertical, it indicates the right in LTR mode and left in RTL mode.
     * When the List direction is horizontal, it indicates the bottom.
     */
    ARKUI_LIST_ITEM_SWIPE_ACTION_DIRECTION_END = 1,
} ArkUI_ListItemSwipeActionDirection;

/**
 * @brief Define the types for expanding the safe area in layout.
 *
 * @since 23
 */
typedef enum {
    /** Default non-safe area of the system, including the status bar and navigation bar. */
    ARKUI_LAYOUT_SAFE_AREA_TYPE_SYSTEM = 1,
} ArkUI_LayoutSafeAreaType;
/**
 * @brief Define the edges for expanding the safe area in layout.
 *
 * @since 23
 */
typedef enum {
    /** Top edge of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_TOP = 1,
    /** Bottom edge of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_BOTTOM = 1 << 1,
    /** Start edge of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_START = 1 << 2,
    /** End edge of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_END = 1 << 3,
    /** Vertical edge of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_VERTICAL = ARKUI_LAYOUT_SAFE_AREA_EDGE_TOP | ARKUI_LAYOUT_SAFE_AREA_EDGE_BOTTOM,
    /** Horizontal edge of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_HORIZONTAL = ARKUI_LAYOUT_SAFE_AREA_EDGE_START | ARKUI_LAYOUT_SAFE_AREA_EDGE_END,
    /** All edges of the safe area. */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_ALL = ARKUI_LAYOUT_SAFE_AREA_EDGE_VERTICAL | ARKUI_LAYOUT_SAFE_AREA_EDGE_HORIZONTAL,
} ArkUI_LayoutSafeAreaEdge;

/**
 * @brief Enumerates the localizedAlignment modes.
 *
 * @since 23
 */
typedef enum {
    /** Top start. */
    ARKUI_LOCALIZED_ALIGNMENT_TOP_START = 0,
    /** Top center. */
    ARKUI_LOCALIZED_ALIGNMENT_TOP,
    /** Top end. */
    ARKUI_LOCALIZED_ALIGNMENT_TOP_END,
    /** Vertically centered start. */
    ARKUI_LOCALIZED_ALIGNMENT_START,
    /** Horizontally and vertically centered. */
    ARKUI_LOCALIZED_ALIGNMENT_CENTER,
    /** Vertically centered end. */
    ARKUI_LOCALIZED_ALIGNMENT_END,
    /** Bottom start. */
    ARKUI_LOCALIZED_ALIGNMENT_BOTTOM_START,
    /** Horizontally centered on the bottom. */
    ARKUI_LOCALIZED_ALIGNMENT_BOTTOM,
    /** Bottom end. */
    ARKUI_LOCALIZED_ALIGNMENT_BOTTOM_END,
} ArkUI_LocalizedAlignment;
/**
 * @brief Enumerates the graphics rendering strategy.
 *
 * @since 23
 */
typedef enum {
    /** The current component and its child components will be drawn directly onto the screen canvas. */
    ARKUI_RENDERSTRATEGY_FAST = 0,
    /**
    * The current component and its child components will first be drawn onto an off-screen canvas,
    *     then undergo some graphic rendering operations, and finally be drawn onto the main canvas.
    */
    ARKUI_RENDERSTRATEGY_OFFSCREEN,
} ArkUI_RenderStrategy;

/**
 * @brief Enumerates the LayoutPolicy.
 *
 * @since 21
 */
typedef enum {
    /** The component fills its parent, which means its size is as large as its parent */
    ARKUI_LAYOUTPOLICY_MATCHPARENT = 0,
    /**
     * The component fills its content, which means its size is as large as its children but it is constrained
     * by its parent.
     */
    ARKUI_LAYOUTPOLICY_WRAPCONTENT,
    /** The component fills its content which means its size is as large as its children. */
    ARKUI_LAYOUTPOLICY_FIXATIDEALSIZE,
} ArkUI_LayoutPolicy;

/**
 * @brief Defines parameter used by the system font style callback event.
 *
 * @since 12
 */
typedef struct ArkUI_SystemFontStyleEvent ArkUI_SystemFontStyleEvent;

#include "native_type_visual.h"

/**
 * @brief Defines the options for selection operation.
 *
 * @since 23
 */
typedef struct ArkUI_SelectionOptions ArkUI_SelectionOptions;

/**
* @brief Creates a size constraint.
*
* @since 12
*/
ArkUI_LayoutConstraint* OH_ArkUI_LayoutConstraint_Create();

/**
* @brief Creates a deep copy of a size constraint.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the pointer to the new size constraint.
* @since 12
*/
ArkUI_LayoutConstraint* OH_ArkUI_LayoutConstraint_Copy(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Destroys the pointer to a size constraint.
*
* @param Constraint Indicates the pointer to the size constraint.
* @since 12
*/
void* OH_ArkUI_LayoutConstraint_Dispose(ArkUI_LayoutConstraint* Constraint);

/**
* @brief Obtains the maximum width for a size constraint, in px.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the maximum width.
* @since 12
*/
int32_t OH_ArkUI_LayoutConstraint_GetMaxWidth(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Obtains the minimum width for a size constraint, in px.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the minimum width.
* @since 12
*/
int32_t OH_ArkUI_LayoutConstraint_GetMinWidth(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Obtains the maximum height for a size constraint, in px.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the maximum height.
* @since 12
*/
int32_t OH_ArkUI_LayoutConstraint_GetMaxHeight(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Obtains the minimum height for a size constraint, in px.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the minimum height.
* @since 12
*/
int32_t OH_ArkUI_LayoutConstraint_GetMinHeight(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Obtains the width percentage reference for a size constraint, in px.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the width percentage reference.
* @since 12
*/
int32_t OH_ArkUI_LayoutConstraint_GetPercentReferenceWidth(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Obtains the height percentage reference for a size constraint, in px.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the height percentage reference.
* @since 12
*/
int32_t OH_ArkUI_LayoutConstraint_GetPercentReferenceHeight(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Sets the maximum width.
*
* @param Constraint Indicates the pointer to the size constraint.
* @param value Indicates the maximum width, in px.
* @since 12
*/
void OH_ArkUI_LayoutConstraint_SetMaxWidth(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
* @brief Sets the minimum width.
*
* @param Constraint Indicates the pointer to the size constraint.
* @param value Indicates the minimum width, in px.
* @since 12
*/
void OH_ArkUI_LayoutConstraint_SetMinWidth(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
* @brief Sets the maximum height.
*
* @param Constraint Indicates the pointer to the size constraint.
* @param value Indicates the maximum height, in px.
* @since 12
*/
void OH_ArkUI_LayoutConstraint_SetMaxHeight(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
* @brief Sets the minimum height.
*
* @param Constraint Indicates the pointer to the size constraint.
* @param value Indicates the minimum height, in px.
* @since 12
*/
void OH_ArkUI_LayoutConstraint_SetMinHeight(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
* @brief Sets the width percentage reference.
*
* @param Constraint Indicates the pointer to the size constraint.
* @param value Indicates the width percentage reference, in px.
* @since 12
*/
void OH_ArkUI_LayoutConstraint_SetPercentReferenceWidth(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
* @brief Sets the height percentage reference.
*
* @param Constraint Indicates the pointer to the size constraint.
* @param value Indicates the height percentage reference, in px.
* @since 12
*/
void OH_ArkUI_LayoutConstraint_SetPercentReferenceHeight(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
* @brief Obtains the pointer to a canvas for drawing, which can be converted into the <b>OH_Drawing_Canvas</b> pointer
* in the <b>Drawing</b> module.
*
* @param context Indicates the pointer to the drawing context.
* @return Returns the pointer to the canvas for drawing.
* @since 12
*/
void* OH_ArkUI_DrawContext_GetCanvas(ArkUI_DrawContext* context);

/**
* @brief Obtains the size of a drawing area.
*
* @param context Indicates the pointer to the drawing context.
* @return Returns the size of the drawing area.
* @since 12
*/
ArkUI_IntSize OH_ArkUI_DrawContext_GetSize(ArkUI_DrawContext* context);

/**
 * @brief Creates <b>Grid</b> layout options.
 *
 * @return <b>Grid</b> layout options created.
 * @since 22
 */
ArkUI_GridLayoutOptions* OH_ArkUI_GridLayoutOptions_Create();

/**
 * @brief Disposes of <b>Grid</b> layout options.
 *
 * @param option <b>Grid</b> layout options.
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_Dispose(ArkUI_GridLayoutOptions* option);

/**
 * @brief Sets the irregular grid item index array for the grid layout.
 *
 * @param option <b>Grid</b> layout options.
 * @param irregularIndexes Array of irregular grid item indexes.
 * @param size Size of the index array.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         If an error code is returned, it may be due to a failure in parameter validation;
 *         the parameter must not be null.
 * @since 22
 */
int32_t OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(
    ArkUI_GridLayoutOptions* option, uint32_t* irregularIndexes, int32_t size);

/**
 * @brief Obtains the irregular grid item index array for the grid layout.
 * When <b>OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback</b> is not set,
 * the grid item specified in <b>irregularIndexes</b> occupies an entire row of the grid that scrolls vertically or
 * an entire column of the grid that scrolls horizontally.
 *
 * @param option <b>Grid</b> layout options.
 * @param irregularIndexes Array of irregular grid item indexes.
 * @param size Size of the index array.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the provided buffer size is insufficient.
 *         If an error code is returned, it may be due to a failure in parameter validation;
 *         the parameter must not be null.
 * @since 22
 */
int32_t OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(
    ArkUI_GridLayoutOptions* option, uint32_t* irregularIndexes, int32_t* size);

/**
 * @brief Registers a callback to obtain the row and column span for the grid item at the specified index.
 *
 * @param option <b>Grid</b> layout options.
 * @param userData Indicates the custom data.
 * @param callback Callback that returns the row and column span for the grid item at the specified index.
 *        itemIndex: grid item index, which must be within the range set by
 *        {@link OH_ArkUI_GridLayoutOptions_SetIrregularIndexes}.
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback(
    ArkUI_GridLayoutOptions* option, void* userData, ArkUI_GridItemSize (*callback)(int32_t itemIndex, void* userData));

/**
 * @brief Registers a callback to obtain the starting row, starting column, row span,
 * and column span for the grid item at the specified index.
 *
 * @param option <b>Grid</b> layout options.
 * @param userData Indicates the custom data.
 * @param callback Callback that returns the starting row, starting column, row span,
 *        and column span for the grid item at the specified index.
 *        itemIndex: grid item index.
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback(
    ArkUI_GridLayoutOptions* option, void* userData, ArkUI_GridItemRect (*callback)(int32_t itemIndex, void* userData));

/**
* @brief Creates water flow section configuration.
*
* @return Returns the water flow section configuration.
* @since 12
*/
ArkUI_WaterFlowSectionOption* OH_ArkUI_WaterFlowSectionOption_Create();

/**
* @brief Destroys the pointer to a water flow section configuration.
*
* @param option Indicates the pointer to a water flow section configuration.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_Dispose(ArkUI_WaterFlowSectionOption* option);

/**
* @brief Sets the FlowItem block configuration information array length.
*
* @param option FlowItem Indicates the packet configuration.
* @param size Array Length.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_SetSize(ArkUI_WaterFlowSectionOption* option, int32_t size);

/**
* @brief Gets the FlowItem grouping configuration information array length.
*
* @param option FlowItem Indicates the packet configuration.
* @return Array size. If -1 is returned, the return fails.
*         The possible cause of the failure is that the option parameter is abnormal, such as a null pointer.
* @since 12
*/
int32_t OH_ArkUI_WaterFlowSectionOption_GetSize(ArkUI_WaterFlowSectionOption* option);

/**
* @brief Sets the number of items in a water flow section.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @param itemCount Indicates the number of items in the water flow section.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_SetItemCount(ArkUI_WaterFlowSectionOption* option,
    int32_t index, int32_t itemCount);

/**
* @brief Obtains the number of items in the water flow section that matches the specified index.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @return Returns the number of items in the water flow section.
* @since 12
*/
int32_t OH_ArkUI_WaterFlowSectionOption_GetItemCount(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
* @brief The FlowItem grouping configuration information getsthe spindle size of
* the specified Item based on flowItemIndex.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @param callback Gets the spindle size of the specified Item based on index.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndex(ArkUI_WaterFlowSectionOption* option,
    int32_t index, float(*callback)(int32_t itemIndex));

/**
* @brief The FlowItem grouping configuration information getsthe spindle size of
* the specified Item based on flowItemIndex.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @param userData FlowItem Custom data.
* @param callback Gets the spindle size of the specified Item based on index.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndexWithUserData(
    ArkUI_WaterFlowSectionOption* option, int32_t index, void* userData,
    float (*callback)(int32_t itemIndex, void* userData));

/**
* @brief Sets the number of columns (in a vertical layout) or rows (in a horizontal layout) of a water flow.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @param crossCount Indicates the number of columns or rows, depending on the layout direction.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_SetCrossCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t crossCount);

/**
* @brief Obtains the number of columns (in a vertical layout) or rows (in a horizontal layout) in the water flow section
* that matches the specified index.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @return Returns the number of columns or rows.
* @since 12
*/
int32_t OH_ArkUI_WaterFlowSectionOption_GetCrossCount(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
* @brief Sets the gap between columns in the specified water flow section.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @param columnGap Indicates the gap between columns to set.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_SetColumnGap(ArkUI_WaterFlowSectionOption* option,
    int32_t index, float columnGap);

/**
* @brief Obtains the gap between columns in the water flow section that matches the specified index.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @return Returns the gap between columns.
* @since 12
*/
float OH_ArkUI_WaterFlowSectionOption_GetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
* @brief Sets the gap between rows in the specified water flow section.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @param rowGap Indicates the gap between rows to set.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_SetRowGap(ArkUI_WaterFlowSectionOption* option,
    int32_t index, float rowGap);

/**
* @brief Obtains the gap between rows in the water flow section that matches the specified index.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @return Returns the gap between rows.
* @since 12
*/
float OH_ArkUI_WaterFlowSectionOption_GetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
* @brief Sets the margins for the specified water flow section.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @param marginTop Indicates the top margin of the water flow section.
* @param marginRight Indicates the right margin of the water flow section.
* @param marginBottom Indicates the bottom margin of the water flow section.
* @param marginLeft Indicates the left margin of the water flow section.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_SetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index,
    float marginTop, float marginRight, float marginBottom, float marginLeft);

/**
* @brief Obtains the margins of the water flow section that matches the specified index.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @return Returns the margins.
* @since 12
*/
ArkUI_Margin OH_ArkUI_WaterFlowSectionOption_GetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief Sets the font weight of total count in the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @param fontWeight font weight {@link ArkUI_FontWeight}. The default value is <b>ARKUI_FONT_WEIGHT_NORMAL</b>.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetFontWeight(ArkUI_SwiperDigitIndicator *indicator, ArkUI_FontWeight fontWeight);

/**
 * @brief Gets the font weight of total count in the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @return font weight {@link ArkUI_FontWeight}.
 * @since 19
 */
ArkUI_FontWeight OH_ArkUI_SwiperDigitIndicator_GetFontWeight(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the font weight of selected index in the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @param selectedFontWeight font weight {@link ArkUI_FontWeight}. The default value is <b>ARKUI_FONT_WEIGHT_NORMAL</b>.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetSelectedFontWeight(
    ArkUI_SwiperDigitIndicator *indicator, ArkUI_FontWeight selectedFontWeight);

/**
 * @brief Gets the font weight of selected index in the digital indicator.
 *
 * @param indicator The pointer to the digital indicator.
 * @return font weight {@link ArkUI_FontWeight}.
 * @since 19
 */
ArkUI_FontWeight OH_ArkUI_SwiperDigitIndicator_GetSelectedFontWeight(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Create auxiliary line information in the RelativeContaine container.
 *
 * @param size The number of auxiliary lines.
 * @return auxiliary line information.
 * @since 12
 */
ArkUI_GuidelineOption* OH_ArkUI_GuidelineOption_Create(int32_t size);

/**
 * @brief Destroy auxiliary line information.
 *
 * @param guideline auxiliary line information.
 * @since 12
 */
void OH_ArkUI_GuidelineOption_Dispose(ArkUI_GuidelineOption* guideline);

/**
 * @brief Set the Id of the auxiliary line.
 *
 * @param guideline auxiliary line information.
 * @param value id, must be unique and cannot have the same name as the component in the container.
 * @param index auxiliary line index value.
 * @since 12
 */
void OH_ArkUI_GuidelineOption_SetId(ArkUI_GuidelineOption* guideline, const char* value, int32_t index);

/**
 * @brief Set the direction of the auxiliary line.
 *
 * @param guideline auxiliary line information.
 * @param value direction.
 * @param index auxiliary line index value.
 * @since 12
 */
void OH_ArkUI_GuidelineOption_SetDirection(ArkUI_GuidelineOption* guideline, ArkUI_Axis value, int32_t index);

/**
 * @brief Set the distance from the left or top of the container.
 *
 * @param guideline auxiliary line information.
 * @param value The distance from the left or top of the container.
 * @param index auxiliary line index value.
 * @since 12
 */
void OH_ArkUI_GuidelineOption_SetPositionStart(ArkUI_GuidelineOption* guideline, float value, int32_t index);

/**
 * @brief Set the distance from the right or bottom of the container.
 *
 * @param guideline auxiliary line information.
 * @param value The distance from the right side or bottom of the container.
 * @param index auxiliary line index value.
 * @since 12
 */
void OH_ArkUI_GuidelineOption_SetPositionEnd(ArkUI_GuidelineOption* guideline, float value, int32_t index);

/**
 * @brief Get the Id of the auxiliary line.
 *
 * @param guideline auxiliary line information.
 * @param index auxiliary line index value.
 * @return Id.
 * @since 12
 */
const char* OH_ArkUI_GuidelineOption_GetId(ArkUI_GuidelineOption* guideline, int32_t index);

/**
 * @brief Get the direction of the auxiliary line.
 *
 * @param guideline auxiliary line information.
 * @param index auxiliary line index value.
 * @return direction.
 * @since 12
 */
ArkUI_Axis OH_ArkUI_GuidelineOption_GetDirection(ArkUI_GuidelineOption* guideline, int32_t index);

/**
 * @brief Get the distance from the left or top of the container.
 *
 * @param guideline auxiliary line information.
 * @param index auxiliary line index value.
 * @return The distance from the left or top of the container.
 * @since 12
 */
float OH_ArkUI_GuidelineOption_GetPositionStart(ArkUI_GuidelineOption* guideline, int32_t index);

/**
 * @brief Get the distance from the right side or bottom of the container.
 *
 * @param guideline auxiliary line information.
 * @param index auxiliary line index value.
 * @return The distance from the right side or bottom of the container.
 * @since 12
 */
float OH_ArkUI_GuidelineOption_GetPositionEnd(ArkUI_GuidelineOption* guideline, int32_t index);

/**
 * @brief creates barrier information within the RelativeContaine container.
 *
 * @param size Number of barriers.
 * @return barrier information.
 * @since 12
 */
ArkUI_BarrierOption* OH_ArkUI_BarrierOption_Create(int32_t size);

/**
 * @brief Destroy barrier information.
 *
 * @param barrierStyle barrier information.
 * @since 12
 */
void OH_ArkUI_BarrierOption_Dispose(ArkUI_BarrierOption* barrierStyle);

/**
 * @brief Set the Id of the barrier.
 *
 * @param barrierStyle barrier information.
 * @param value id, must be unique and cannot have the same name as the component in the container.
 * @param index Barrier index value.
 * @since 12
 */
void OH_ArkUI_BarrierOption_SetId(ArkUI_BarrierOption* barrierStyle, const char* value, int32_t index);

/**
 * @brief Set the direction of the barrier.
 *
 * @param barrierStyle barrier information.
 * @param value direction.
 * @param index Barrier index value.
 * @since 12
 */
void OH_ArkUI_BarrierOption_SetDirection(
    ArkUI_BarrierOption* barrierStyle, ArkUI_BarrierDirection value, int32_t index);

/**
 * @brief Sets the dependent component of the barrier.
 *
 * @param barrierStyle barrier information.
 * @param value The ID of the dependent component.
 * @param index Barrier index value.
 * @since 12
 */
void OH_ArkUI_BarrierOption_SetReferencedId(ArkUI_BarrierOption* barrierStyle, const char* value, int32_t index);

/**
 * @brief Get the Id of the barrier.
 *
 * @param barrierStyle auxiliary line information.
 * @param index auxiliary line index value.
 * @return The Id of the barrier.
 * @since 12
 */
const char* OH_ArkUI_BarrierOption_GetId(ArkUI_BarrierOption* barrierStyle, int32_t index);

/**
 * @brief Gets the direction of the barrier.
 *
 * @param barrierStyle auxiliary line information.
 * @param index auxiliary line index value.
 * @return The direction of the barrier.
 * @since 12
 */
ArkUI_BarrierDirection OH_ArkUI_BarrierOption_GetDirection(ArkUI_BarrierOption* barrierStyle, int32_t index);

/**
 * @brief Get the dependent components of the barrier.
 *
 * @param barrierStyle auxiliary line information.
 * @param index auxiliary line index value.
 * @param referencedIndex dependent component Id index value.
 * @return The barrier's dependent components.
 * @since 12
 */
const char* OH_ArkUI_BarrierOption_GetReferencedId(
    ArkUI_BarrierOption* barrierStyle, int32_t index, int32_t referencedIndex);

/**
 * @brief Gets the number of dependent components of the barrier.
 *
 * @param barrierStyle auxiliary line information.
 * @param index auxiliary line index value.
 * @return The number of dependent components of the barrier.
 * @since 12
 */
int32_t OH_ArkUI_BarrierOption_GetReferencedIdSize(ArkUI_BarrierOption* barrierStyle, int32_t index);

/**
 * @brief Set the types and parameters related to content transition effects.
 *
 * @since 21
 */
typedef struct ArkUI_ContentTransitionEffect ArkUI_ContentTransitionEffect;

/**
 * @brief creates content switching animation effects.
 *
 * @param type content transition type: 0-identity, 1-opacity.
 * @return content transition effect.
 * @since 21
 */
ArkUI_ContentTransitionEffect* OH_ArkUI_ContentTransitionEffect_Create(int32_t type);

/**
 * @brief creates alignment rule information for subcomponents in relative containers.
 *
 * @return Alignment rule information.
 * @since 12
 */
ArkUI_AlignmentRuleOption* OH_ArkUI_AlignmentRuleOption_Create();

/**
 * @brief Destroys the alignment rule information of subcomponents in relative containers.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_Dispose(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Set the start alignment parameter.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @param id The id value of the anchor component.
 * @param alignment Alignment relative to the anchor component.
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetStart(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_HorizontalAlignment alignment);

/**
 * @brief Set the end alignment parameter.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @param id The id value of the anchor component.
 * @param alignment Alignment relative to the anchor component.
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetEnd(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_HorizontalAlignment alignment);

/**
* @brief Set the parameters for horizontal center alignment.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @param id The id value of the anchor component.
* @param alignment Alignment relative to anchor component
* @since 12
*/
void OH_ArkUI_AlignmentRuleOption_SetCenterHorizontal(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_HorizontalAlignment alignment);

/**
 * @brief Set the parameters for top alignment.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @param id The id value of the anchor component.
 * @param alignment Alignment relative to anchor component
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetTop(ArkUI_AlignmentRuleOption* option, const char* id,
    ArkUI_VerticalAlignment alignment);

/**
 * @brief Set the bottom alignment parameters.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @param id The id value of the anchor component.
 * @param alignment Alignment relative to anchor component
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetBottom(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_VerticalAlignment alignment);

/**
* @brief Set the parameters for vertical center alignment.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @param id The id value of the anchor component.
* @param alignment Alignment relative to the anchor component.
* @since 12
*/
void OH_ArkUI_AlignmentRuleOption_SetCenterVertical(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_VerticalAlignment alignment);

/**
 * @brief Sets the horizontal offset parameter of the component under the anchor point constraint.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @param horizontal bias value in the horizontal direction.
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetBiasHorizontal(ArkUI_AlignmentRuleOption* option, float horizontal);

/**
 * @brief Set the vertical offset parameter of the component under the anchor point constraint.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @param vertical bias value in the vertical direction.
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetBiasVertical(ArkUI_AlignmentRuleOption* option, float vertical);

/**
 * @brief Get the Id of the start-aligned parameter.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @return The id value of the anchor component.
 * @since 12
 */
const char* OH_ArkUI_AlignmentRuleOption_GetStartId(ArkUI_AlignmentRuleOption* option);

/**
* @brief Gets the alignment of the start-aligned parameter.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The alignment of the parameters.
* @since 12
*/
ArkUI_HorizontalAlignment OH_ArkUI_AlignmentRuleOption_GetStartAlignment(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Get the end alignment parameter.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @return End-aligned parameter id.
 * @since 12
 */
const char* OH_ArkUI_AlignmentRuleOption_GetEndId(ArkUI_AlignmentRuleOption* option);

/**
* @brief Get the end alignment parameter.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The alignment of the end-aligned parameter.
* @since 12
*/
ArkUI_HorizontalAlignment OH_ArkUI_AlignmentRuleOption_GetEndAlignment(ArkUI_AlignmentRuleOption* option);

/**
* @brief Gets the parameters of horizontal center alignment.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The id of the parameter of horizontal center alignment.
* @since 12
*/
const char* OH_ArkUI_AlignmentRuleOption_GetCenterIdHorizontal(ArkUI_AlignmentRuleOption* option);

/**
* @brief Gets the parameters of horizontal center alignment.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The alignment of the horizontally centered alignment parameter.
* @since 12
*/
ArkUI_HorizontalAlignment OH_ArkUI_AlignmentRuleOption_GetCenterAlignmentHorizontal(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Get the top-aligned parameters.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @return Top aligned parameter id.
 * @since 12
 */
const char* OH_ArkUI_AlignmentRuleOption_GetTopId(ArkUI_AlignmentRuleOption* option);

/**
* @brief Get the top-aligned parameters.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The alignment of the top-aligned parameter.
* @since 12
*/
ArkUI_VerticalAlignment OH_ArkUI_AlignmentRuleOption_GetTopAlignment(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Get the bottom alignment parameters.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @return The id of the bottom-aligned parameter.
 * @since 12
 */
const char* OH_ArkUI_AlignmentRuleOption_GetBottomId(ArkUI_AlignmentRuleOption* option);

/**
* @brief Get the bottom alignment parameters.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The alignment of the bottom-aligned parameter.
* @since 12
*/
ArkUI_VerticalAlignment OH_ArkUI_AlignmentRuleOption_GetBottomAlignment(ArkUI_AlignmentRuleOption* option);

/**
* @brief Gets the parameters of vertical center alignment.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The id of the vertical center alignment parameter.
* @since 12
*/
const char* OH_ArkUI_AlignmentRuleOption_GetCenterIdVertical(ArkUI_AlignmentRuleOption* option);

/**
* @brief Gets the parameters of vertical center alignment.
*
* @param option Alignment rule information of subcomponents in the relative container.
* @return The alignment of the vertical center alignment parameter.
* @since 12
*/
ArkUI_VerticalAlignment OH_ArkUI_AlignmentRuleOption_GetCenterAlignmentVertical(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Get the bias value in the horizontal direction.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @return The bias value in the horizontal direction.
 * @since 12
 */
float OH_ArkUI_AlignmentRuleOption_GetBiasHorizontal(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Get the bias value in the vertical direction.
 *
 * @param option Alignment rule information of subcomponents in the relative container.
 * @return bias value in vertical direction.
 * @since 12
*/
float OH_ArkUI_AlignmentRuleOption_GetBiasVertical(ArkUI_AlignmentRuleOption* option);

/**
 * @brief Create a configuration item for the ListitemSwipeActionItem interface settings.
 *
 * @return List Item SwipeActionItem configuration item instance. If the object returns a null pointer,
 *         it indicates creation failure, and the reason for the failure may be that the address space is full.
 * @since 12
*/
ArkUI_ListItemSwipeActionItem* OH_ArkUI_ListItemSwipeActionItem_Create();

/**
* @brief Destroy the ListitemSwipeActionItem instance.
*
* @param item List Item SwipeActionItem instance to be destroyed.
* @since 12
*/
void OH_ArkUI_ListItemSwipeActionItem_Dispose(ArkUI_ListItemSwipeActionItem* item);

/**
* @brief Set the layout content of ListItem SwipeActionItem.
*
* @param item List Item SwipeActionItem instance.
* @param node Layout information.
* @since 12
*/
void OH_ArkUI_ListItemSwipeActionItem_SetContent(ArkUI_ListItemSwipeActionItem* item, ArkUI_NodeHandle node);

/**
* @brief Set the threshold for long-distance sliding deletion distance of components.
*
* @param item List Item SwipeActionItem instance.
* @param distance Component long-distance sliding deletion distance threshold.
* @since 12
*/
void OH_ArkUI_ListItemSwipeActionItem_SetActionAreaDistance(ArkUI_ListItemSwipeActionItem* item, float distance);

/**
* @brief Obtain the threshold for long-distance sliding deletion distance of components.
*
* @param item List Item SwipeActionItem instance.
* @return Component long-distance sliding deletion distance threshold. If -1.0f is returned, the return fails.
*         The possible cause of the failure is that the item parameter is abnormal, such as a null pointer.
* @since 12
*/
float OH_ArkUI_ListItemSwipeActionItem_GetActionAreaDistance(ArkUI_ListItemSwipeActionItem* item);

/**
* @brief Set the event to be called when a sliding entry enters the deletion area.
*
* @param item List Item SwipeActionItem instance.
* @param callback Callback Events.
* @since 12
*/
void OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionArea(ArkUI_ListItemSwipeActionItem* item, void (*callback)());

/**
 * @brief Set the event triggered when a sliding entry enters the deletion area.
 *
 * @param item List Item SwipeActionItem instance.
 * @param userData User defined data.
 * @param callback Callback Events.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionAreaWithUserData(ArkUI_ListItemSwipeActionItem* item,
    void* userData, void (*callback)(void* userData));

/**
* @brief Set the event to be called when a component enters the long-range deletion area and deletes a ListItem.
*
* @param item List Item SwipeActionItem instance.
* @param callback Callback Events.
* @since 12
*/
void OH_ArkUI_ListItemSwipeActionItem_SetOnAction(ArkUI_ListItemSwipeActionItem* item, void (*callback)());

/**
 * @brief Set the event triggered when a component enters the long-range deletion area and deletes a ListItem.
 *
 * @param item List Item SwipeActionItem instance.
 * @param userData User defined data.
 * @param callback Callback Events.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnActionWithUserData(ArkUI_ListItemSwipeActionItem* item,
    void* userData, void (*callback)(void* userData));

/**
* @brief Set the event to be called when a sliding entry exits the deletion area.
*
* @param item List Item SwipeActionItem instance.
* @param callback Callback Events.
* @since 12
*/
void OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionArea(ArkUI_ListItemSwipeActionItem* item, void (*callback)());

/**
 * @brief Set the event triggered when a sliding entry exits the deletion area.
 *
 * @param item List Item SwipeActionItem instance.
 * @param userData User defined data.
 * @param callback Callback Events.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionAreaWithUserData(ArkUI_ListItemSwipeActionItem* item,
    void* userData, void (*callback)(void* userData));

/**
* @brief Set the event triggered when the sliding state of a list item changes.
*
* @param item List Item SwipeActionItem instance.
* @param callback Callback Events.
*        swipeActionState The changed state.
* @since 12
*/
void OH_ArkUI_ListItemSwipeActionItem_SetOnStateChange(ArkUI_ListItemSwipeActionItem* item,
    void (*callback)(ArkUI_ListItemSwipeActionState swipeActionState));

/**
 * @brief Set the event triggered when the sliding state of a list item changes.
 *
 * @param item List Item SwipeActionItem instance.
 * @param userData User defined data.
 * @param callback Callback Events.
 *        swipeActionState The changed state.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnStateChangeWithUserData(ArkUI_ListItemSwipeActionItem* item,
    void* userData, void (*callback)(ArkUI_ListItemSwipeActionState swipeActionState, void* userData));

/**
 * @brief Create a configuration item for the ListitemSwipeActionOption interface settings.
 *
 * @return List Item SwipeActionOption configuration item instance.If the object returns a null pointer,
 *         it indicates a creation failure, and the reason for the failure may be that the address space is full.
 * @since 12
*/
ArkUI_ListItemSwipeActionOption* OH_ArkUI_ListItemSwipeActionOption_Create();

/**
* @brief Destroy the ListitemSwipeActionOption instance.
*
* @param option List Item SwipeActionOption instance to be destroyed.
* @since 12
*/
void OH_ArkUI_ListItemSwipeActionOption_Dispose(ArkUI_ListItemSwipeActionOption* option);

/**
* @brief Set the layout content on the left (vertical layout) or top (horizontal layout)
* of the ListItem SwipeActionItem.
*
* @param option List Item SwipeActionItem instance.
* @param item Layout information.
* @since 12
*/
void OH_ArkUI_ListItemSwipeActionOption_SetStart(ArkUI_ListItemSwipeActionOption* option,
    ArkUI_ListItemSwipeActionItem* item);

/**
* @brief Set the layout content on the right (vertical layout) or bottom (horizontal layout)
* of the ListItem SwipeActionItem.
*
* @param option List Item SwipeActionItem instance.
* @param item Layout information.
* @since 12
*/
void OH_ArkUI_ListItemSwipeActionOption_SetEnd(ArkUI_ListItemSwipeActionOption* option,
    ArkUI_ListItemSwipeActionItem* item);

/**
* @brief Set the sliding effect.
*
* @param option List Item SwipeActionItem instance.
* @param edgeEffect Sliding effect.
* @since 12
*/
void OH_ArkUI_ListItemSwipeActionOption_SetEdgeEffect(ArkUI_ListItemSwipeActionOption* option,
    ArkUI_ListItemSwipeEdgeEffect edgeEffect);

/**
* @brief Get the sliding effect.
*
* @param option List Item SwipeActionItem instance.
* @return Sliding effect. The default return value is 0. If -1 is returned, the return fails.
*         The possible cause of the failure is that the option parameter is abnormal, such as a null pointer.
* @since 12
*/
int32_t OH_ArkUI_ListItemSwipeActionOption_GetEdgeEffect(ArkUI_ListItemSwipeActionOption* option);

/**
* @brief The event called when the sliding operation offset changes.
*
* @param option List Item SwipeActionItem instance.
* @param callback Callback Events.
*        offset Slide offset.
* @since 12
*/
void OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChange(ArkUI_ListItemSwipeActionOption* option,
    void (*callback)(float offset));

/**
 * @brief Set the event triggered when the sliding operation offset changes.
 *
 * @param option List Item SwipeActionItem instance.
 * @param userData User defined data.
 * @param callback Callback Events.
 *        offset Slide offset.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChangeWithUserData(ArkUI_ListItemSwipeActionOption* option,
    void* userData, void (*callback)(float offset, void* userData));

/**
 * @brief Create configuration items for the ListChildrenMainSize interface settings.
 *
 * @return ListChildrenMainSize configuration item instance.If the object returns a null pointer,
 *         it indicates a creation failure, and the reason for the failure may be that the address space is full.
 * @since 12
*/
ArkUI_ListChildrenMainSize* OH_ArkUI_ListChildrenMainSizeOption_Create();

/**
* @brief Destroy the ListChildrenMainSize instance.
*
* @param option The ListChildrenMainSize instance to be destroyed.
* @since 12
*/
void OH_ArkUI_ListChildrenMainSizeOption_Dispose(ArkUI_ListChildrenMainSize* option);

/**
 * @brief Set the default size of ChildrenMainSizeOption for the List component.
 *
 * @param option ListChildrenMainSize instance.
 * @param defaultMainSize The default size of the ListItem under the List, measured in vp.
 * @return 0 represents success. If defaultMainSize is less than 0 or option is a null pointer, return 401.
 * @since 12
*/
int32_t OH_ArkUI_ListChildrenMainSizeOption_SetDefaultMainSize(ArkUI_ListChildrenMainSize* option,
    float defaultMainSize);

/**
 * @brief Get the default size of ChildrenMainSizeOption for the List component.
 *
 * @param option ListChildrenMainSize instance.
 * @return The default size of the ListItem under the List is 0, measured in vp.
 *         When the option is a null pointer, it returns -1.
 * @since 12
*/
float OH_ArkUI_ListChildrenMainSizeOption_GetDefaultMainSize(ArkUI_ListChildrenMainSize* option);

/**
 * @brief Reset the array size of ChildrenMainSizeOption for the List component.
 *
 * @param option ListChildrenMainSize instance.
 * @param totalSize Array size.
 * @since 12
*/
void OH_ArkUI_ListChildrenMainSizeOption_Resize(ArkUI_ListChildrenMainSize* option, int32_t totalSize);

/**
 * @brief Resize the ChildrenMainSizeOption array operation on the List component.
 *
 * @param option ListChildrenMainSize instance.
 * @param index To modify the starting position of the MainSize array.
 * @param deleteCount The number of MainSize arrays to be deleted starting from index.
 * @param addCount The number of MainSize arrays to be added starting from index.
 * @return 0 represents success. If the function parameter is abnormal, return 401.
 * @since 12
*/
int32_t OH_ArkUI_ListChildrenMainSizeOption_Splice(ArkUI_ListChildrenMainSize* option, int32_t index,
    int32_t deleteCount, int32_t addCount);

/**
 * @brief Update the value of the ChildrenMainSizeOption array in the List component.
 *
 * @param option ListChildrenMainSize instance.
 * @param index To modify the starting position of the MainSize array.
 * @param mainSize The actual modified value.
 * @return 0 represents success. If the function parameter is abnormal, return 401.
 * @since 12
*/
int32_t OH_ArkUI_ListChildrenMainSizeOption_UpdateSize(ArkUI_ListChildrenMainSize* option,
    int32_t index, float mainSize);

/**
 * @brief Get the value of the ChildrenMainSizeOption array for the List component.
 *
 * @param option ListChildrenMainSize instance.
 * @param index The index position of the value to be obtained.
 * @return The value of the specific position of the array. If the function parameter is abnormal, return -1.
 * @since 12
*/
float OH_ArkUI_ListChildrenMainSizeOption_GetMainSize(ArkUI_ListChildrenMainSize* option, int32_t index);

/**
 * @brief Create accessibility state.
 *
 * @return Returns the pointer to the accessibility state object.
 * If a null pointer is returned, the object fails to be created. The possible cause is that the address space is full.
 * @since 12
*/
ArkUI_AccessibilityState* OH_ArkUI_AccessibilityState_Create(void);

/**
* @brief Dispose accessibility state.
*
* @param state accessibility state object.
* @since 12
*/
void OH_ArkUI_AccessibilityState_Dispose(ArkUI_AccessibilityState* state);

/**
 * @brief Set accessibility state disabled.
 *
 * @param state accessibility state object.
 * @param isDisabled accessibility state disabled, Value 1 indicates disabled and 0 indicates enbled.
 * @since 12
*/
void OH_ArkUI_AccessibilityState_SetDisabled(ArkUI_AccessibilityState* state, int32_t isDisabled);

/**
 * @brief Get accessibility state disabled.
 *
 * @param state accessibility state object.
 * @return accessibility state disabled, Value 1 indicates disabled and 0 indicates enbled. The default value is 0.
 *         If the function parameter is abnormal, return the default value.
 * @since 12
*/
int32_t OH_ArkUI_AccessibilityState_IsDisabled(ArkUI_AccessibilityState* state);

/**
 * @brief Set accessibility state selected.
 *
 * @param state accessibility state object.
 * @param isSelected accessibility state selected, Value 1 indicates selected, and 0 indicates not selected.
 *        The default value is 0.
 * @since 12
*/
void OH_ArkUI_AccessibilityState_SetSelected(ArkUI_AccessibilityState* state, int32_t isSelected);

/**
 * @brief Get accessibility state selected.
 *
 * @param state accessibility state object.
 * @return accessibility state selected, Value 1 indicates selected, and 0 indicates not selected.
 *         The default value is 0.
 *         If the function parameter is abnormal, return the default value.
 * @since 12
*/
int32_t OH_ArkUI_AccessibilityState_IsSelected(ArkUI_AccessibilityState* state);

/**
 * @brief Set accessibility checked state.
 *
 * @param state accessibility state object.
 * @param checkedState checked state, and uses the {@link ArkUI_AccessibilityCheckedState} enumeration value,
 *        The default value is ARKUI_ACCESSIBILITY_UNCHECKED.
 * @since 12
*/
void OH_ArkUI_AccessibilityState_SetCheckedState(ArkUI_AccessibilityState* state, int32_t checkedState);

/**
 * @brief Get accessibility checked state.
 *
 * @param state accessibility state object.
 * @return checked state, and uses the {@link ArkUI_AccessibilityCheckedState} enumeration value,
 *         The default value is ARKUI_ACCESSIBILITY_UNCHECKED.
 *         If the function parameter is abnormal, return the default value.
 * @since 12
*/
int32_t OH_ArkUI_AccessibilityState_GetCheckedState(ArkUI_AccessibilityState* state);

/**
 * @brief Create accessibility value.
 *
 * @return Returns the pointer to the accessibility state object.
 * If a null pointer is returned, the object fails to be created. The possible cause is that the address space is full.
 * @since 12
*/
ArkUI_AccessibilityValue* OH_ArkUI_AccessibilityValue_Create(void);

/**
* @brief Dispose accessibility value.
*
* @param value accessibility value object.
* @since 12
*/
void OH_ArkUI_AccessibilityValue_Dispose(ArkUI_AccessibilityValue* value);

/**
 * @brief Set accessibility minimum value.
 *
 * @param value accessibility value object.
 * @param min minimum value based on range components, The default value is -1.
 * @since 12
*/
void OH_ArkUI_AccessibilityValue_SetMin(ArkUI_AccessibilityValue* value, int32_t min);

/**
 * @brief Get accessibility minimum value.
 *
 * @param value accessibility value object.
 * @return minimum value based on range components, The default value is -1.
 *         If the function parameter is abnormal, return -1.
 * @since 12
*/
int32_t OH_ArkUI_AccessibilityValue_GetMin(ArkUI_AccessibilityValue* value);

/**
 * @brief Set accessibility minimum value.
 *
 * @param value accessibility value object.
 * @param max maximum value based on range components, The default value is -1.
 * @since 12
*/
void OH_ArkUI_AccessibilityValue_SetMax(ArkUI_AccessibilityValue* value, int32_t max);

/**
 * @brief Get accessibility minimum value.
 *
 * @param value accessibility value object.
 * @return maximum value based on range components, The default value is -1.
 *         If the function parameter is abnormal, return -1.
 * @since 12
*/
int32_t OH_ArkUI_AccessibilityValue_GetMax(ArkUI_AccessibilityValue* value);

/**
 * @brief Set accessibility current value.
 *
 * @param value accessibility value object.
 * @param current value based on range components, The default value is -1.
 * @since 12
*/
void OH_ArkUI_AccessibilityValue_SetCurrent(ArkUI_AccessibilityValue* value, int32_t current);

/**
 * @brief Get accessibility current value.
 *
 * @param value accessibility value object.
 * @return current value based on range components, The default value is -1.
 *         If the function parameter is abnormal, return -1.
 * @since 12
*/
int32_t OH_ArkUI_AccessibilityValue_GetCurrent(ArkUI_AccessibilityValue* value);

/**
 * @brief Set accessibility minimum value.
 *
 * @param value accessibility value object.
 * @param rangeMin minimum value based on range components, The default value is -1.
 * @since 18
*/
void OH_ArkUI_AccessibilityValue_SetRangeMin(ArkUI_AccessibilityValue* value, int32_t rangeMin);

/**
 * @brief Get accessibility minimum value.
 *
 * @param value accessibility value object.
 * @return minimum value based on range components, The default value is -1.
 *         If the function parameter is abnormal, return -1.
 * @since 18
*/
int32_t OH_ArkUI_AccessibilityValue_GetRangeMin(ArkUI_AccessibilityValue* value);

/**
 * @brief Set accessibility maximum value.
 *
 * @param value accessibility value object.
 * @param rangeMax maximum value based on range components, The default value is -1.
 * @since 18
*/
void OH_ArkUI_AccessibilityValue_SetRangeMax(ArkUI_AccessibilityValue* value, int32_t rangeMax);

/**
 * @brief Get accessibility maximum value.
 *
 * @param value accessibility value object.
 * @return maximum value based on range components, The default value is -1.
 *         If the function parameter is abnormal, return -1.
 * @since 18
*/
int32_t OH_ArkUI_AccessibilityValue_GetRangeMax(ArkUI_AccessibilityValue* value);

/**
 * @brief Set accessibility current value.
 *
 * @param value accessibility value object.
 * @param rangeCurrent value based on range components, The default value is -1.
 * @since 18
*/
void OH_ArkUI_AccessibilityValue_SetRangeCurrent(ArkUI_AccessibilityValue* value, int32_t rangeCurrent);

/**
 * @brief Get accessibility current value.
 *
 * @param value accessibility value object.
 * @return current value based on range components, The default value is -1.
 *         If the function parameter is abnormal, return -1.
 * @since 18
*/
int32_t OH_ArkUI_AccessibilityValue_GetRangeCurrent(ArkUI_AccessibilityValue* value);

/**
 * @brief Set accessibility text value.
 *
 * @param value accessibility value object.
 * @param text The textual description information of the component, which defaults to an empty string.
 * @since 12
*/
void OH_ArkUI_AccessibilityValue_SetText(ArkUI_AccessibilityValue* value, const char* text);

/**
 * @brief Get accessibility text value.
 *
 * @param value accessibility value object.
 * @return The textual description information of the component, which defaults to an empty string;
 *         If the function parameter is abnormal, return null.
 * @since 12
*/
const char* OH_ArkUI_AccessibilityValue_GetText(ArkUI_AccessibilityValue* value);

/**
 * @brief Destroy the instance of Customs Property.
 *
 * @param handle The instance of Customs Property to be destroyed.
 * @since 14
 */
void OH_ArkUI_CustomProperty_Destroy(ArkUI_CustomProperty* handle);

/**
 * @brief Get custom attribute value information.
 *
 * @param handle Custom attribute object pointer.
 * @return Customize the value information within the attribute structure.
 * @since 14
 */
const char* OH_ArkUI_CustomProperty_GetStringValue(ArkUI_CustomProperty* handle);

/**
 * @brief Get window name from HostWindowInfo.
 *
 * @param info HostWindowInfo object pointer.
 * @return Window name in HostWindowInfo.
 * @since 15
 */
const char* OH_ArkUI_HostWindowInfo_GetName(ArkUI_HostWindowInfo* info);

/**
 * @brief Destroy the instance of HostWindowInfo.
 *
 * @param info Instance of HostWindowInfo to be destroyed.
 * @since 15
 */
void OH_ArkUI_HostWindowInfo_Destroy(ArkUI_HostWindowInfo* info);

/**
 * @brief Destroy ActiveChildenInfo instance.
 *
 * @param handle ActiveChild instance to be destroyed.
 * @since 14
 */
void OH_ArkUI_ActiveChildrenInfo_Destroy(ArkUI_ActiveChildrenInfo* handle);

/**
 * @brief Retrieve the child nodes of ActiveChildenInfo with the structure index.
 *
 * @param handle The ActiveChildenInfo instance for obtaining information.
 * @param index The index of child nodes.
 * @return The child node pointer corresponding to the index. Return nullptr in case of exception.
 * @since 14
 */
ArkUI_NodeHandle OH_ArkUI_ActiveChildrenInfo_GetNodeByIndex(ArkUI_ActiveChildrenInfo* handle, int32_t index);

/**
 * @brief Retrieve the number of nodes within the structure of ActiveChildenInfo.
 *
 * @param handle The ActiveChildenInfo instance for obtaining information.
 * @return Number of child nodes. Default value: 0.
 * @since 14
 */
int32_t OH_ArkUI_ActiveChildrenInfo_GetCount(ArkUI_ActiveChildrenInfo* handle);

/**
 * @brief Create a cross-language option instance.
 *
 * @return Returns a cross-language option instance. If the result is a null pointer, it may be out of memory.
 * @since 15
 */
ArkUI_CrossLanguageOption* OH_ArkUI_CrossLanguageOption_Create(void);

/**
 * @brief Destroy the cross-language option instance.
 *
 * @param option The cross-language option instance.
 * @since 15
 */
void OH_ArkUI_CrossLanguageOption_Destroy(ArkUI_CrossLanguageOption* option);

/**
 * @brief Enable the attribute setting in the cross-language option.
 *
 * @param option The cross-language option.
 * @param enabled The attribute setting in the cross-language option.
 * Default value: false.
 * @since 15
 */
void OH_ArkUI_CrossLanguageOption_SetAttributeSettingStatus(ArkUI_CrossLanguageOption* option, bool enabled);

/**
 * @brief Get the attribute setting enable of the cross-language option.
 *
 * @param option The cross-language option.
 * @return The attribute setting enable of the cross-language option.
 * @since 15
 */
bool OH_ArkUI_CrossLanguageOption_GetAttributeSettingStatus(ArkUI_CrossLanguageOption* option);


/**
 * @brief Expand the swipe action.
 *
 * @param node List Item node.
 * @param direction expand direction of swipeAction.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} success.
 *         {@link ARKUI_ERROR_CODE_PARAM_ERROR} The component type of the node is incorrect.
 *         {@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} The node not mounted to component tree.
 * @since 21
 */
int32_t OH_ArkUI_ListItemSwipeAction_Expand(ArkUI_NodeHandle node, ArkUI_ListItemSwipeActionDirection direction);

/**
 * @brief Collapse the swipe action.
 *
 * @param node List Item node.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} success.
 *         {@link ARKUI_ERROR_CODE_PARAM_ERROR} The component type of the node is incorrect.
 *         {@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} The node not mounted to component tree.
 * @since 21
 */
int32_t OH_ArkUI_ListItemSwipeAction_Collapse(ArkUI_NodeHandle node);

/**
 * @brief Create an edge object for position attribute.
 *
 * @return A pointer to the edge object.
 * @since 21
 */
ArkUI_PositionEdges* OH_ArkUI_PositionEdges_Create();

/**
 * @brief Creates a deep copy of an edge object for position attribute.
 *
 * @param edges A pointer to an edge object.
 * @return A pointer to the new edge object.
 * @since 21
 */
ArkUI_PositionEdges* OH_ArkUI_PositionEdges_Copy(const ArkUI_PositionEdges* edges);

/**
 * @brief Dispose an edge object for position attribute.
 *
 * @param edges Pointer to the edge object to be disposed.
 * @since 21
 */
void OH_ArkUI_PositionEdges_Dispose(ArkUI_PositionEdges* edges);

/**
 * @brief Sets the top edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of top edge to the corresponding edge of parent container, in vp.
 * @since 21
 */
void OH_ArkUI_PositionEdges_SetTop(ArkUI_PositionEdges* edges, float value);

/**
 * @brief Gets the top edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of top edge to the corresponding edge of parent container, in vp.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PositionEdges_GetTop(ArkUI_PositionEdges* edges, float* value);

/**
 * @brief Sets the left edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of left edge to the corresponding edge of parent container, in vp.
 * @since 21
 */
void OH_ArkUI_PositionEdges_SetLeft(ArkUI_PositionEdges* edges, float value);

/**
 * @brief Gets the left edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of left edge to the corresponding edge of parent container, in vp.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PositionEdges_GetLeft(ArkUI_PositionEdges* edges, float* value);

/**
 * @brief Sets the bottom edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of bottom edge to the corresponding edge of parent container, in vp.
 * @since 21
 */
void OH_ArkUI_PositionEdges_SetBottom(ArkUI_PositionEdges* edges, float value);

/**
 * @brief Gets the bottom edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of bottom edge to the corresponding edge of parent container, in vp.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PositionEdges_GetBottom(ArkUI_PositionEdges* edges, float* value);

/**
 * @brief Sets the right edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of right edge to the corresponding edge of parent container, in vp.
 * @since 21
 */
void OH_ArkUI_PositionEdges_SetRight(ArkUI_PositionEdges* edges, float value);

/**
 * @brief Gets the right edge of an edge object for position attribute.
 *
 * @param edges Pointer to the edge object.
 * @param value The distance of right edge to the corresponding edge of parent container, in vp.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PositionEdges_GetRight(ArkUI_PositionEdges* edges, float* value);

/**
 * @brief Create a policy object for PixelRound attribute.
 *
 * @return A pointer to the policy object.
 * @since 21
 */
ArkUI_PixelRoundPolicy* OH_ArkUI_PixelRoundPolicy_Create();

/**
 * @brief Dispose a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object to be disposed.
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_Dispose(ArkUI_PixelRoundPolicy* policy);

/**
 * @brief Sets the top edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of top edge.
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_SetTop(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy value);

/**
 * @brief Gets the top edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of top edge.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PixelRoundPolicy_GetTop(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy* value);

/**
 * @brief Sets the start edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of start edge.
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_SetStart(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy value);

/**
 * @brief Gets the start edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of start edge.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PixelRoundPolicy_GetStart(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy* value);

/**
 * @brief Sets the bottom edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of bottom edge.
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_SetBottom(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy value);

/**
 * @brief Gets the bottom edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of bottom edge.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PixelRoundPolicy_GetBottom(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy* value);

/**
 * @brief Sets the end edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of end edge.
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_SetEnd(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy value);

/**
 * @brief Gets the end edge of a policy object for PixelRound attribute.
 *
 * @param policy Pointer to the policy object.
 * @param value The CalcPolicy of end edge.
 * @return Returns the result code.
 *      Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *      Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the parameter is invalid.
 * @since 21
 */
int32_t OH_ArkUI_PixelRoundPolicy_GetEnd(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy* value);

/**
 * @brief Set text menu item title.
 *
 * @param item The text menu item.
 * @param content The name of the text menu item, which defaults to an empty string. The string will copy to framework.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_SetContent(ArkUI_TextMenuItem* item, const char* content);

/**
 * @brief Get text menu item title.
 *
 * @param item The text menu item object.
 * @param buffer The buffer of the text menu content, memory space needs to be allocated by the developer.
 * @param bufferSize The name of the text menu item, which defaults to an empty string;
 * @param writeLength Indicates the string length actually written to the buffer
 *                    when returning {@link ARKUI_ERROR_CODE_NO_ERROR}.
 *                    Indicates the minimum buffer size that can accommodate the target
 *                    when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 *
 * @return The error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the node, buffer or writeLength is null.
 *         {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_GetContent(const ArkUI_TextMenuItem* item, char* buffer, int32_t bufferSize,
    int32_t* writeLength);

/**
 * @brief Set text menu item icon.
 *
 * @param item The text menu item.
 * @param icon The text menu item icon resource, which defaults to an empty string. The string will copy to framework.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_SetIcon(ArkUI_TextMenuItem* item, const char* icon);

/**
 * @brief Get text menu item icon.
 *
 * @param item The text menu item object
 * @param buffer The buffer of the text menu content, memory space needs to be allocated by the developer.
 * @param bufferSize The icon of the text menu item, which defaults to an empty string;
 * @param writeLength Indicates the string length actually written to the buffer
 *                    when returning {@link ARKUI_ERROR_CODE_NO_ERROR}.
 *                    Indicates the minimum buffer size that can accommodate the target
 *                    when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 *
 * @return The error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the node, buffer or writeLength is null.
 *         {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_GetIcon(const ArkUI_TextMenuItem* item, char* buffer, int32_t bufferSize,
    int32_t* writeLength);

/**
 * @brief Set text menu item label info for keyboard shortcut.
 *
 * @param item The text menu item.
 * @param labelInfo The text menu item shortcut displays, which defaults to an empty string.
 *      The string will copy to framework.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_SetLabelInfo(ArkUI_TextMenuItem* item, const char* labelInfo);

/**
 * @brief Get text menu item label info for keyboard shortcut..
 *
 * @param item The text menu item object
 * @param buffer The buffer of the text menu content, memory space needs to be allocated by the developer.
 * @param bufferSize The shortcuts of the text menu item, which defaults to an empty string;
 * @param writeLength Indicates the string length actually written to the buffer
 *                    when returning {@link ARKUI_ERROR_CODE_NO_ERROR}.
 *                    Indicates the minimum buffer size that can accommodate the target
 *                    when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 *
 * @return The error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the node, buffer or writeLength is null.
 *         {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_GetLabelInfo(const ArkUI_TextMenuItem* item, char* buffer, int32_t bufferSize,
    int32_t* writeLength);

/**
 * @brief Set text menu item id.
 *
 * @param item The text menu item.
 * @param id The text menu id.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_SetId(ArkUI_TextMenuItem* item, int32_t id);

/**
 * @brief Get text menu item id.
 *
 * @param item The text menu item object
 * @param id The text menu item id;
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
*/
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_GetId(const ArkUI_TextMenuItem* item, int32_t* id);

/**
 * @brief Get the size of text menu items.
 *
 * @param items The text menu items.
 * @param size The size of text menu items.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
*/
ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_GetSize(ArkUI_TextMenuItemArray* items, int32_t* size);

/**
 * @brief Get text menu item at index.
 *
 * @param items The text menu items.
 * @param index The index of text menu items.
 * @param item The text menu item at index of array.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_GetItem(ArkUI_TextMenuItemArray* items, int32_t index,
    ArkUI_TextMenuItem** item);

/**
 * @brief Insert text menu item at index.
 *
 * @param items The text menu items.
 * @param item The text menu item at index of array. The item will copy by framework.
 * @param index The index of text menu items.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_Insert(ArkUI_TextMenuItemArray* items, ArkUI_TextMenuItem* item,
    int32_t index);

/**
 * @brief Erase text menu item at index.
 *
 * @param items The text menu items.
 * @param index The index of text menu items.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_Erase(ArkUI_TextMenuItemArray* items, int32_t index);

/**
 * @brief Clear all the items.
 *
 * @param items The text menu items.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_Clear(ArkUI_TextMenuItemArray* items);

/**
 * @brief Set the event to be called when text menu create.
 *
 * @param editMenuOptions Pointer to the ArkUI_TextEditMenuOptions object.
 * @param userData The user data.
 * @param cb The create callback function.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextEditMenuOptions_RegisterOnCreateMenuCallback(
    ArkUI_TextEditMenuOptions* editMenuOptions, void* userData, ArkUI_TextCreateMenuCallback cb);
/**
 * @brief Set the event to be called when menu prepare.
 *
 * @param editMenuOptions Pointer to the ArkUI_TextEditMenuOptions object.
 * @param userData The user data.
 * @param cb The prepare callback function.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextEditMenuOptions_RegisterOnPrepareMenuCallback(
    ArkUI_TextEditMenuOptions* editMenuOptions, void* userData, ArkUI_TextPrepareMenuCallback cb);

/**
 * @brief Set the event to be called when menu item click.
 *
 * @param editMenuOptions Pointer to the ArkUI_TextEditMenuOptions object.
 * @param userData The user data.
 * @param cb The menu item click callback function.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextEditMenuOptions_RegisterOnMenuItemClickCallback(
    ArkUI_TextEditMenuOptions* editMenuOptions, void* userData, ArkUI_TextMenuItemClickCallback cb);

/**
* @brief Enumerates raw input event types.
*
* @since 26.0.0
*/
typedef enum {
    /**
     * Touch event.
     *
     * @since 26.0.0
     */
    ARKUI_RAW_INPUT_EVENT_TYPE_TOUCH = 0,
    /**
     * Mouse event.
     *
     * @since 26.0.0
     */
    ARKUI_RAW_INPUT_EVENT_TYPE_MOUSE = 1,
} ArkUI_RawInputEventType;

/**
 * @brief Sets the recognition types of a configuration object for selected text recognition.
 *
 * @param selectionMenuOptions Pointer to the ArkUI_TextSelectionMenuOptions object.
 * @param textSpanType The span type of {@link ArkUI_TextSpanType}.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_SetSpanType(ArkUI_TextSelectionMenuOptions* selectionMenuOptions,
    ArkUI_TextSpanType textSpanType);
/**
 * @brief Gets the span type select menu options.
 *
 * @param selectionMenuOptions Pointer to the ArkUI_TextSelectionMenuOptions object.
 * @param spanType the text span type {@link ArkUI_TextSpanType}.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_GetSpanType(ArkUI_TextSelectionMenuOptions* selectionMenuOptions,
    ArkUI_TextSpanType* spanType);

/**
 * @brief Set custom text menu node of text.
 *
 * @param selectionMenuOptions Pointer to the ArkUI_TextSelectionMenuOptions object.
 * @param node The custom menu node.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_SetContentNode(ArkUI_TextSelectionMenuOptions* selectionMenuOptions,
    ArkUI_NodeHandle node);
/**
 * @brief Get custom text menu node of text.
 *
 * @param selectionMenuOptions Pointer to the ArkUI_TextSelectionMenuOptions object.
 * @param node The custom menu node.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_GetContentNode(ArkUI_TextSelectionMenuOptions* selectionMenuOptions,
    ArkUI_NodeHandle* node);

/**
 * @brief Sets the recognition types of a configuration object for selected text recognition.
 *
 * @param selectionMenuOptions Pointer to the ArkUI_TextSelectionMenuOptions object.
 * @param responseType The response type of {@link ArkUI_TextResponseType}.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_SetResponseType(ArkUI_TextSelectionMenuOptions* selectionMenuOptions,
    ArkUI_TextResponseType responseType);
/**
 * @brief Gets the response type select menu options.
 *
 * @param selectionMenuOptions Pointer to the ArkUI_TextSelectionMenuOptions object.
 * @param responseType The text response type {@link ArkUI_TextResponseType}.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_GetResponseType(ArkUI_TextSelectionMenuOptions* selectionMenuOptions,
    ArkUI_TextResponseType* responseType);

/**
 * @brief Set the event to be called when selection menu show.
 *
 * @param selectionMenuOptions Pointer to the ArkUI_TextSelectionMenuOptions object.
 * @param userData The user data.
 * @param callback The callback function of menu show.
 *     start The start offset of the selected content.
 *     end The end offset of the selected content.
 *     userData The user data.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_RegisterOnMenuShowCallback(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, void* userData,
    void (*callback)(int32_t start, int32_t end, void* userData));
/**
 * @brief Set the event to be called when selection menu hide.
 *
 * @param selectionMenuOptions Pointer to the ArkUI_TextSelectionMenuOptions object.
 * @param userData The user data.
 * @param callback The callback function of menu hide.
 *     start The start offset of the selected content.
 *     end The end offset of the selected content.
 *     userData The user data.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_RegisterOnMenuHideCallback(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, void* userData,
    void (*callback)(int32_t start, int32_t end, void* userData));

/**
 * @brief Create selection options.
 *
 * @return A pointer to the selection options object.
 * @since 23
 */
ArkUI_SelectionOptions* OH_ArkUI_SelectionOptions_Create();

/**
 * @brief Dispose selection options object.
 *
 * @param {ArkUI_SelectionOptions*} options Pointer to the selection options object. to be disposed.
 * @since 23
 */
void OH_ArkUI_SelectionOptions_Dispose(ArkUI_SelectionOptions* options);

/**
 * @brief Sets the menu policy for selection options.
 *
 * @param {ArkUI_SelectionOptions*} options Pointer to the selection options.
 * @param {ArkUI_MenuPolicy} menuPolicy The menu policy.
 * @since 23
 */
void OH_ArkUI_SelectionOptions_SetMenuPolicy(
    ArkUI_SelectionOptions* options, ArkUI_MenuPolicy menuPolicy);

/**
 * @brief Gets the menu policy of selection options.
 *
 * @param {ArkUI_SelectionOptions*} options Pointer to the selection options object.
 * @return Returns the menu policy.
 * @since 23
 */
ArkUI_MenuPolicy OH_ArkUI_SelectionOptions_GetMenuPolicy(ArkUI_SelectionOptions* options);

/**
 * @brief Create a configuration object for selected drag preview style.
 * @return A pointer to the configuration object.
 * @since 23
 */
ArkUI_SelectedDragPreviewStyle* OH_ArkUI_SelectedDragPreviewStyle_Create();

/**
 * @brief Dispose a configuration object for selected drag preview style.
 * @param config Pointer to the configuration object to be disposed.
 * @since 23
 */
void OH_ArkUI_SelectedDragPreviewStyle_Dispose(ArkUI_SelectedDragPreviewStyle* config);

/**
 * @brief Sets the color of background for selected drag preview style.
 * @param config Pointer to the configuration object to be modified.
 * @param color Background color.
 * @since 23
 */
void OH_ArkUI_SelectedDragPreviewStyle_SetColor(
    ArkUI_SelectedDragPreviewStyle* config, uint32_t color);

/**
 * @brief Gets the color of background for selected drag preview style.
 * @param config Pointer to the configuration object.
 * @return Returns the background color.
 * @since 23
 */
uint32_t OH_ArkUI_SelectedDragPreviewStyle_GetColor(
    ArkUI_SelectedDragPreviewStyle* config);

/**
 * @brief Sets the decoration type of the decorative line style.
 *
 * @param options Pointer to the {@link OH_ArkUI_DecorationStyleOptions} object.
 * @param type Decoration type ({@link ArkUI_TextDecorationType}).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyleOptions_SetTextDecorationType(OH_ArkUI_DecorationStyleOptions* options,
    ArkUI_TextDecorationType type);

/**
 * @brief Obtains the decoration type of the decorative line style.
 *
 * @param options Pointer to the {@link OH_ArkUI_DecorationStyleOptions} object.
 * @param type Pointer to the decoration type ({@link ArkUI_TextDecorationType}).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyleOptions_GetTextDecorationType(OH_ArkUI_DecorationStyleOptions* options,
    ArkUI_TextDecorationType* type);

/**
 * @brief Sets the color of the decorative line.
 *
 * @param options Pointer to the {@link OH_ArkUI_DecorationStyleOptions} object.
 * @param color Color of the decorative line, in 0xARGB format.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyleOptions_SetColor(OH_ArkUI_DecorationStyleOptions* options, uint32_t color);

/**
 * @brief Obtains the color of the decorative line.
 *
 * @param options Pointer to the {@link OH_ArkUI_DecorationStyleOptions} object.
 * @param color Pointer to the color of the decorative line, in 0xARGB format.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyleOptions_GetColor(OH_ArkUI_DecorationStyleOptions* options, uint32_t* color);

/**
 * @brief Sets the style of the decorative line.
 *
 * @param options Pointer to the {@link OH_ArkUI_DecorationStyleOptions} object.
 * @param style Style of the decorative line ({@link ArkUI_TextDecorationStyle}).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyleOptions_SetTextDecorationStyle(OH_ArkUI_DecorationStyleOptions* options,
    ArkUI_TextDecorationStyle style);

/**
 * @brief Obtains the style of the decorative line.
 *
 * @param options Pointer to the {@link OH_ArkUI_DecorationStyleOptions} object.
 * @param style Pointer to the style of the decorative line ({@link ArkUI_TextDecorationStyle}).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyleOptions_GetTextDecorationStyle(OH_ArkUI_DecorationStyleOptions* options,
    ArkUI_TextDecorationStyle* style);

/**
 * @brief Sets the scale factor of the decorative line thickness.
 *
 * @param options Pointer to the {@link OH_ArkUI_DecorationStyleOptions} object.
 * @param thicknessScale Scale factor of the decorative line thickness. The value range is [0, +∞).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyleOptions_SetThicknessScale(
    OH_ArkUI_DecorationStyleOptions* options, float thicknessScale);

/**
 * @brief Obtains the scale factor of the decorative line thickness.
 *
 * @param options Pointer to the {@link OH_ArkUI_DecorationStyleOptions} object.
 * @param thicknessScale Pointer to the scale factor of the decorative line thickness.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyleOptions_GetThicknessScale(OH_ArkUI_DecorationStyleOptions* options,
    float* thicknessScale);

/**
 * @brief Sets the types of the text entity recognition configuration.
 *
 * @param config Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.
 * @param types Pointer to the types of the text entity recognition configuration. The value is an enumerated value of {
 * @link ArkUI_TextDataDetectorType}.
 * @param length Type quantity.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextDataDetectorConfig_SetTypes(
    OH_ArkUI_TextDataDetectorConfig* config, const ArkUI_TextDataDetectorType* types, int32_t length);

/**
 * @brief Obtains the types of the text entity recognition configuration.
 *
 * @param config Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.
 * @param buffer Pointer to the buffer of the type array.
 * @param bufferSize Maximum number of types that can be written to the buffer reserved for the types.
 * @param writeLength Pointer to the number of types that are actually written to the buffer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the value of **bufferSize** is less than that of **
 *     writeLength**.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextDataDetectorConfig_GetTypes(OH_ArkUI_TextDataDetectorConfig* config,
    ArkUI_TextDataDetectorType* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Sets the callback for text entity recognition result updates.
 *
 * @param config Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.
 * @param userData Pointer to the user data.
 * @param callback detect result update callback.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextDataDetectorConfig_RegisterOnDetectResultUpdateCallback(
    OH_ArkUI_TextDataDetectorConfig* config, void* userData,
    void (*callback)(const char* result, int32_t length, void* userData));

/**
 * @brief Sets the color of the recognized content.
 *
 * @param config Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.
 * @param color Color of the recognized content, in 0xARGB format.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextDataDetectorConfig_SetColor(OH_ArkUI_TextDataDetectorConfig* config, uint32_t color);

/**
 * @brief Obtains the color of the recognized content.
 *
 * @param config Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.
 * @param color Pointer to the color of the recognized content, in 0xARGB format.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextDataDetectorConfig_GetColor(OH_ArkUI_TextDataDetectorConfig* config, uint32_t* color);

/**
 * @brief Sets the decoration style of the recognized content.
 *
 * @param config Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.
 * @param decoration Pointer to the decoration style of the recognized content. The value is an enumerated value of
 *     {@link OH_ArkUI_DecorationStyleOptions}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextDataDetectorConfig_SetDecorationStyleOptions(
    OH_ArkUI_TextDataDetectorConfig* config, OH_ArkUI_DecorationStyleOptions* decoration);

/**
 * @brief Obtains the decoration style of the recognized content.
 *
 * @param config Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.
 * @param decoration Pointer to the decoration style of the recognized content. The value is an enumerated value of
 *     {@link OH_ArkUI_DecorationStyleOptions}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextDataDetectorConfig_GetDecorationStyleOptions(
    OH_ArkUI_TextDataDetectorConfig* config, OH_ArkUI_DecorationStyleOptions* decoration);

/**
 * @brief Sets whether to display the preview menu when the recognized content is long-pressed.
 *
 * @param config Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.
 * @param enablePreviewMenu Whether to display the preview menu when the recognized content is long-pressed. **true**
 *     means to display the preview menu, and **false** means the opposite. The default value is **false**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextDataDetectorConfig_SetEnablePreviewMenu(
    OH_ArkUI_TextDataDetectorConfig* config, bool enablePreviewMenu);

/**
 * @brief Obtains whether the preview menu is displayed when the recognized content is long-pressed.
 *
 * @param config Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.
 * @param enablePreviewMenu Pointer to the **enablePreviewMenu** parameter indicating whether the preview menu is
 *     displayed when the recognized content is long-pressed. **true** means that the preview menu is displayed, and **
 *     false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextDataDetectorConfig_GetEnablePreviewMenu(
    OH_ArkUI_TextDataDetectorConfig* config, bool* enablePreviewMenu);

/**
 * @brief Set the StyledString of the text.
 *
 * @param controller the controller of the text.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object, which will be set to Text.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_TextController_SetStyledString(
    OH_ArkUI_TextController* controller, ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Sets the text for the placeholder text options used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @param value Pointer to the placeholder text.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_SetValue(
    OH_ArkUI_TextEditorPlaceholderOptions* options, const char* value);

/**
 * @brief Obtains the text for the placeholder text options used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @param buffer Pointer to the buffer for storing the placeholder text in the memory. You need to allocate the memory.
 * @param bufferSize Maximum number of characters that can be written to the buffer.
 * @param writeLength Pointer to the number of characters that are actually written to the buffer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the value of **bufferSize** is less than that of **
 *     writeLength**.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_GetValue(
    OH_ArkUI_TextEditorPlaceholderOptions* options, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Sets the font size for the placeholder text options used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @param fontSize Font size, in fp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_SetFontSize(
    OH_ArkUI_TextEditorPlaceholderOptions* options, float fontSize);

/**
 * @brief Obtains the font size for the placeholder text options used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @param fontSize Pointer to the font size, in fp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_GetFontSize(
    OH_ArkUI_TextEditorPlaceholderOptions* options, float* fontSize);

/**
 * @brief Sets the font weight for the placeholder text options used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @param fontWeight Font weight. The value is an integer multiple of 100 within the [100, 900] range, for example, **
 *     100** or **900**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_SetFontWeight(
    OH_ArkUI_TextEditorPlaceholderOptions* options, uint32_t fontWeight);

/**
 * @brief Obtains the font weight for the placeholder text options used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @param fontWeight Pointer to the font weight. The value is an integer multiple of 100 within the [100, 900] range,
 *     for example, **100** or **900**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_GetFontWeight(
    OH_ArkUI_TextEditorPlaceholderOptions* options, uint32_t* fontWeight);

/**
 * @brief Sets the font family for the placeholder text options used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @param fontFamily Pointer to the font family, containing the font names to be set. Different font names are
 *     separated by commas (,).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_SetFontFamily(
    OH_ArkUI_TextEditorPlaceholderOptions* options, const char* fontFamily);

/**
 * @brief Obtains the font family for the placeholder text options used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @param buffer Pointer to the buffer for storing the font family in the memory. You need to allocate the memory.
 * @param bufferSize Maximum number of characters that can be written to the buffer.
 * @param writeLength Pointer to the number of characters that are actually written to the buffer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the value of **bufferSize** is less than that of **
 *     writeLength**.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_GetFontFamily(
    OH_ArkUI_TextEditorPlaceholderOptions* options, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Sets the font style for the placeholder text options used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @param fontStyle Font style. The value is an enumerated value of {@link ArkUI_FontStyle}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_SetFontStyle(
    OH_ArkUI_TextEditorPlaceholderOptions* options, ArkUI_FontStyle fontStyle);

/**
 * @brief Obtains the font style for the placeholder text options used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @param fontStyle Pointer to the font style. The value is an enumerated value of {@link ArkUI_FontStyle}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_GetFontStyle(
    OH_ArkUI_TextEditorPlaceholderOptions* options, ArkUI_FontStyle* fontStyle);

/**
 * @brief Sets the font color for the placeholder text options used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @param fontColor Font color, in 0xARGB format.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_SetFontColor(
    OH_ArkUI_TextEditorPlaceholderOptions* options, uint32_t fontColor);

/**
 * @brief Obtains the font color for the placeholder text options used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @param fontColor Pointer to the font color, in 0xARGB format.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorPlaceholderOptions_GetFontColor(OH_ArkUI_TextEditorPlaceholderOptions* options,
    uint32_t* fontColor);

/**
 * @brief Sets the caret offset using the styled string controller.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param caretOffset Caret offset.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_SetCaretOffset(
    OH_ArkUI_TextEditorStyledStringController* controller, int32_t caretOffset);

/**
 * @brief Obtains the caret offset using the styled string controller.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param caretOffset Pointer to the caret offset.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_GetCaretOffset(
    OH_ArkUI_TextEditorStyledStringController* controller, int32_t* caretOffset);

/**
 * @brief Sets the selected area using the styled string controller.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param start Start position of the selected area.
 * @param end End position of the selected area.
 * @param menuPolicy Policy for displaying the menu in the selected area. The value is an enumerated value of
 *     {@link ArkUI_MenuPolicy}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_SetSelection(
    OH_ArkUI_TextEditorStyledStringController* controller, uint32_t start, uint32_t end, ArkUI_MenuPolicy menuPolicy);

/**
 * @brief Obtains the editing status of the text editor using the styled string controller.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param isEditing Pointer to the **isEditing** parameter indicating whether the text editor is in the editing state. *
 *     *true** means that the text editor is in the editing state, and **false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_IsEditing(
    OH_ArkUI_TextEditorStyledStringController* controller, bool* isEditing);

/**
 * @brief Exits the editing status of the text editor using the styled string controller.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_StopEditing(
    OH_ArkUI_TextEditorStyledStringController* controller);

/**
 * @brief Obtains the preview text using the styled string controller.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param offset Pointer to the preview text offset.
 * @param buffer Pointer to the buffer for storing the preview text in the memory. You need to allocate the memory.
 * @param bufferSize Maximum number of characters that can be written to the buffer.
 * @param writeLength Pointer to the number of characters that are actually written to the buffer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_GetPreviewText(
    OH_ArkUI_TextEditorStyledStringController* controller, uint32_t* offset, char* buffer,
    int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Obtains the caret-selected rectangle using the styled string controller.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param rect Pointer to the caret-selected rectangle information. The value is an enumerated value of
 *     {@link ArkUI_Rect}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_GetCaretRect(
    OH_ArkUI_TextEditorStyledStringController* controller, ArkUI_Rect* rect);

/**
 * @brief Deletes characters using the styled string controller. If no content is selected, one character before the
 * current caret position is deleted. If content is selected, the selected content is deleted.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_DeleteBackward(
    OH_ArkUI_TextEditorStyledStringController* controller);

/**
 * @brief Sets the text alignment mode in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param align Text alignment mode. The value is an enumerated value of {@link ArkUI_TextAlignment}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetTextAlign(
    OH_ArkUI_TextEditorParagraphStyle* style, ArkUI_TextAlignment align);

/**
 * @brief Obtains the text alignment mode in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param align Pointer to the text alignment mode. The value is an enumerated value of {@link ArkUI_TextAlignment}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetTextAlign(
    OH_ArkUI_TextEditorParagraphStyle* style, ArkUI_TextAlignment* align);

/**
 * @brief Sets the PixelMap for paragraph indentation in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param pixelmap Pointer to the PixelMap for paragraph indentation.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetLeadingMarginPixelMap(
    OH_ArkUI_TextEditorParagraphStyle* style, struct OH_PixelmapNative* pixelmap);

/**
 * @brief Obtains the PixelMap for paragraph indentation in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param pixelmap Double pointer to the PixelMap for paragraph indentation.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetLeadingMarginPixelMap(
    OH_ArkUI_TextEditorParagraphStyle* style, struct OH_PixelmapNative** pixelmap);

/**
 * @brief Sets the width for paragraph indentation in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param width Width for paragraph indentation, in vp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetLeadingMarginWidth(OH_ArkUI_TextEditorParagraphStyle* style,
    uint32_t width);

/**
 * @brief Obtains the width for paragraph indentation in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param width Pointer to the width for paragraph indentation, in vp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetLeadingMarginWidth(OH_ArkUI_TextEditorParagraphStyle* style,
    uint32_t* width);

/**
 * @brief Sets the height for paragraph indentation in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param height Height for paragraph indentation, in vp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetLeadingMarginHeight(OH_ArkUI_TextEditorParagraphStyle* style,
    uint32_t height);

/**
 * @brief Obtains the height for paragraph indentation in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param height Pointer to the height for paragraph indentation, in vp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetLeadingMarginHeight(OH_ArkUI_TextEditorParagraphStyle* style,
    uint32_t* height);

/**
 * @brief Sets the word breaking mode in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param wordBreak Word breaking mode. The value is an enumerated value of {@link ArkUI_WordBreak}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetWordBreak(OH_ArkUI_TextEditorParagraphStyle* style,
    ArkUI_WordBreak wordBreak);

/**
 * @brief Obtains the word breaking mode in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param wordBreak Pointer to the word breaking mode. The value is an enumerated value of {@link ArkUI_WordBreak}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetWordBreak(OH_ArkUI_TextEditorParagraphStyle* style,
    ArkUI_WordBreak* wordBreak);

/**
 * @brief Sets the line breaking strategy in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param lineBreakStrategy Line breaking strategy. The value is an enumerated value of
 *     {@link OH_ArkUI_LineBreakStrategy}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetLineBreakStrategy(OH_ArkUI_TextEditorParagraphStyle* style,
    OH_ArkUI_LineBreakStrategy lineBreakStrategy);

/**
 * @brief Obtains the line breaking strategy in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param lineBreakStrategy Pointer to the line breaking strategy. The value is an enumerated value of
 *     {@link OH_ArkUI_LineBreakStrategy}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetLineBreakStrategy(OH_ArkUI_TextEditorParagraphStyle* style,
    OH_ArkUI_LineBreakStrategy* lineBreakStrategy);

/**
 * @brief Sets the paragraph spacing in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param paragraphSpacing Paragraph spacing, in vp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetParagraphSpacing(OH_ArkUI_TextEditorParagraphStyle* style,
    uint32_t paragraphSpacing);

/**
 * @brief Obtains the paragraph spacing in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param paragraphSpacing Pointer to the paragraph spacing, in vp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetParagraphSpacing(OH_ArkUI_TextEditorParagraphStyle* style,
    uint32_t* paragraphSpacing);

/**
 * @brief Sets the text vertical alignment mode in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param verticalAlignment Text vertical alignment mode. The value is an enumerated value of
 *     {@link ArkUI_TextVerticalAlignment}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetTextVerticalAlign(OH_ArkUI_TextEditorParagraphStyle* style,
    ArkUI_TextVerticalAlignment verticalAlignment);

/**
 * @brief Obtains the text vertical alignment mode in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param verticalAlignment Text vertical alignment mode. The value is an enumerated value of
 *     {@link ArkUI_TextVerticalAlignment}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetTextVerticalAlign(OH_ArkUI_TextEditorParagraphStyle* style,
    ArkUI_TextVerticalAlignment* verticalAlignment);

/**
 * @brief Sets the text direction in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param textDirection Text direction. The value is an enumerated value of {@link ArkUI_TextDirection}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_SetTextDirection(OH_ArkUI_TextEditorParagraphStyle* style,
    ArkUI_TextDirection textDirection);

/**
 * @brief Obtains the text direction in the paragraph style.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @param textDirection Pointer to the text direction. The value is an enumerated value of {@link ArkUI_TextDirection}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorParagraphStyle_GetTextDirection(OH_ArkUI_TextEditorParagraphStyle* style,
    ArkUI_TextDirection* textDirection);

/**
 * @brief Sets the typing paragraph style using the styled string controller.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param style Pointer to the typing paragraph style.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_SetTypingParagraphStyle(
    OH_ArkUI_TextEditorStyledStringController* controller, OH_ArkUI_TextEditorParagraphStyle* style);

/**
 * @brief Sets the font color of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param color Font color, in 0xARGB format.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetFontColor(OH_ArkUI_TextEditorTextStyle* style, uint32_t color);

/**
 * @brief Obtains the font color of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param color Pointer to the font color, in 0xARGB format.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetFontColor(OH_ArkUI_TextEditorTextStyle* style, uint32_t* color);

/**
 * @brief Sets the font size of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param size Font size, in fp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetFontSize(OH_ArkUI_TextEditorTextStyle* style, float size);

/**
 * @brief Obtains the font size of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param size Pointer to the font size, in fp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetFontSize(OH_ArkUI_TextEditorTextStyle* style, float* size);

/**
 * @brief Sets the font style of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param fontStyle Font style. The value is an enumerated value of {@link ArkUI_FontStyle}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetFontStyle(OH_ArkUI_TextEditorTextStyle* style,
    ArkUI_FontStyle fontStyle);

/**
 * @brief Obtains the font style of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param fontStyle Pointer to the font style. The value is an enumerated value of {@link ArkUI_FontStyle}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetFontStyle(OH_ArkUI_TextEditorTextStyle* style,
    ArkUI_FontStyle* fontStyle);

/**
 * @brief Sets the font weight of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param fontWeight Font weight. The value is an integer multiple of 100 within the [100, 900] range, for example, **
 *     100** or **900**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetFontWeight(OH_ArkUI_TextEditorTextStyle* style, uint32_t fontWeight);

/**
 * @brief Obtains the font weight of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param fontWeight Pointer to the font weight. The value is an integer multiple of 100 within the [100, 900] range,
 *     for example, **100** or **900**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetFontWeight(OH_ArkUI_TextEditorTextStyle* style, uint32_t* fontWeight);

/**
 * @brief Sets the font family of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param fontFamily Pointer to the font family, containing the font names to be set. Different font names are
 *     separated by commas (,).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetFontFamily(OH_ArkUI_TextEditorTextStyle* style, const char* fontFamily);

/**
 * @brief Obtains the font family of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param buffer Pointer to the buffer for storing the font family in the memory. You need to allocate the memory.
 * @param bufferSize Maximum number of characters that can be written to the buffer.
 * @param writeLength Pointer to the number of characters that are actually written to the buffer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetFontFamily(OH_ArkUI_TextEditorTextStyle* style,
    char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Sets the text decoration options of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param options Pointer to the {@link OH_ArkUI_DecorationStyleOptions} object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetDecoration(OH_ArkUI_TextEditorTextStyle* style,
    OH_ArkUI_DecorationStyleOptions* options);

/**
 * @brief Obtains the text decoration options of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param options Pointer to the {@link OH_ArkUI_DecorationStyleOptions} object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetDecoration(OH_ArkUI_TextEditorTextStyle* style,
    OH_ArkUI_DecorationStyleOptions* options);

/**
 * @brief Sets the text shadow options of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param options Double pointer to the text shadow options.
 * @param length Length of the text shadow options.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetTextShadows(OH_ArkUI_TextEditorTextStyle* style,
    const OH_ArkUI_ShadowOptions** options, int32_t length);

/**
 * @brief Obtains the text shadow options of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param shadowOptions Double pointer to the text shadow options.
 * @param shadowOptionsSize Size of the shadow option buffer.
 * @param writeLength Pointer to the number of actual text shadow options in the text style.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetTextShadows(OH_ArkUI_TextEditorTextStyle* style,
    OH_ArkUI_ShadowOptions** shadowOptions, uint32_t shadowOptionsSize, uint32_t* writeLength);

/**
 * @brief Sets the line height of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param lineHeight Line height.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetLineHeight(OH_ArkUI_TextEditorTextStyle* style, int32_t lineHeight);

/**
 * @brief Obtains the line height of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param lineHeight Pointer to the line height.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetLineHeight(OH_ArkUI_TextEditorTextStyle* style, int32_t* lineHeight);

/**
 * @brief Sets the letter spacing of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param letterSpacing Letter spacing.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetLetterSpacing(OH_ArkUI_TextEditorTextStyle* style,
    int32_t letterSpacing);

/**
 * @brief Obtains the letter spacing of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param letterSpacing Pointer to the letter spacing.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetLetterSpacing(OH_ArkUI_TextEditorTextStyle* style,
    int32_t* letterSpacing);

/**
 * @brief Sets the font feature of the text style, such as monospaced digits.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param fontFeature Pointer to the font features, containing font features to be set. Multiple features are separated
 *     by commas (,).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetFontFeature(OH_ArkUI_TextEditorTextStyle* style,
    const char* fontFeature);

/**
 * @brief Obtains the font feature of the text style, such as monospaced digits.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param buffer Pointer to the buffer for storing the font features in the memory. You need to allocate the memory.
 * @param bufferSize Maximum number of characters that can be written to the buffer.
 * @param writeLength Pointer to the number of characters that are actually written to the buffer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetFontFeature(OH_ArkUI_TextEditorTextStyle* style, char* buffer,
    int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Sets whether to evenly distribute the line spacing to the top and bottom of each line in the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param halfLeading Whether to enable half leading.
 *     <br>**true** means to enable, and **false** means the opposite. The default value is **false**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetHalfLeading(OH_ArkUI_TextEditorTextStyle* style, bool halfLeading);

/**
 * @brief Obtains whether the line spacing is evenly distributed to the top and bottom of each line in the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param halfLeading Pointer to the **halfLeading** parameter indicating whether to enable half leading.
 *     <br>**true** means to enable, and **false** means the opposite. The default value is **false**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetHalfLeading(OH_ArkUI_TextEditorTextStyle* style, bool* halfLeading);

/**
 * @brief Sets the text background color of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param color Text background color, in 0xARGB format.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetTextBackgroundColor(OH_ArkUI_TextEditorTextStyle* style,
    uint32_t color);

/**
 * @brief Obtains the text background color of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param color Pointer to the text background color, in 0xARGB format.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetTextBackgroundColor(OH_ArkUI_TextEditorTextStyle* style,
    uint32_t* color);

/**
 * @brief Sets the radius of the rounded corner of the text background of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param topLeft Radius of the rounded corner in the upper left corner of the text background. The unit is vp.
 * @param topRight Radius of the rounded corner in the upper right corner of the text background. The unit is vp.
 * @param bottomLeft Radius of the rounded corner in the lower left corner of the text background. The unit is vp.
 * @param bottomRight Radius of the rounded corner in the lower right corner of the text background. The unit is vp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetTextBackgroundRadius(OH_ArkUI_TextEditorTextStyle* style, float topLeft,
    float topRight, float bottomLeft, float bottomRight);

/**
 * @brief Obtains the radius of the rounded corner of the text background of the text style.
 *
 * @param style Pointer to the text style of the **TextEditor** component.
 * @param topLeft Pointer to the radius of the rounded corner in the upper left corner of the text background. The unit
 *     is vp.
 * @param topRight Pointer to the radius of the rounded corner in the upper right corner of the text background. The
 *     unit is vp.
 * @param bottomLeft Pointer to the radius of the rounded corner in the lower left corner of the text background. The
 *     unit is vp.
 * @param bottomRight Pointer to the radius of the rounded corner in the lower right corner of the text background. The
 *     unit is vp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetTextBackgroundRadius(OH_ArkUI_TextEditorTextStyle* style,
    float* topLeft, float* topRight, float* bottomLeft, float* bottomRight);

/**
 * @brief Sets the typing style using the styled string controller.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param style Pointer to the typing style.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_SetTypingStyle(
    OH_ArkUI_TextEditorStyledStringController* controller, OH_ArkUI_TextEditorTextStyle* style);

/**
 * @brief Obtains the typing style using the styled string controller.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param style Pointer to the typing style.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_GetTypingStyle(
    OH_ArkUI_TextEditorStyledStringController* controller, OH_ArkUI_TextEditorTextStyle* style);

/**
 * @brief Sets the span type of the text selection menu in the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param textEditorSpanType Span type. The value is an enumerated value of {@link OH_ArkUI_TextEditorSpanType}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_SetSpanType(
    OH_ArkUI_TextEditorSelectionMenuOptions* options, OH_ArkUI_TextEditorSpanType textEditorSpanType);

/**
 * @brief Obtains the span type of the text selection menu in the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param textEditorSpanType Pointer to the span type. The value is an enumerated value of
 *     {@link OH_ArkUI_TextEditorSpanType}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_GetSpanType(
    OH_ArkUI_TextEditorSelectionMenuOptions* options, OH_ArkUI_TextEditorSpanType* textEditorSpanType);

/**
 * @brief Sets the content node of the text selection menu in the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param node Content node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_SetContentNode(OH_ArkUI_TextEditorSelectionMenuOptions* options,
    ArkUI_NodeHandle node);

/**
 * @brief Obtains the content node of the text selection menu in the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param node Pointer to the content node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_GetContentNode(OH_ArkUI_TextEditorSelectionMenuOptions* options,
    ArkUI_NodeHandle* node);

/**
 * @brief Sets the response type of the text selection menu in the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param responseType Response type. The value is an enumerated value of {@link OH_ArkUI_TextEditorResponseType}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_SetResponseType(
    OH_ArkUI_TextEditorSelectionMenuOptions* options, OH_ArkUI_TextEditorResponseType responseType);

/**
 * @brief Obtains the response type of the text selection menu in the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param responseType Pointer to the response type. The value is an enumerated value of
 *     {@link OH_ArkUI_TextEditorResponseType}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_GetResponseType(
    OH_ArkUI_TextEditorSelectionMenuOptions* options, OH_ArkUI_TextEditorResponseType* responseType);

/**
 * @brief Sets the type of the text selection menu in the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param menuType Menu type. The value is an enumerated value of {@link OH_ArkUI_TextMenuType}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_SetMenuType(OH_ArkUI_TextEditorSelectionMenuOptions* options,
    OH_ArkUI_TextMenuType menuType);

/**
 * @brief Obtains the type of the text selection menu in the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param menuType Pointer to the menu type. The value is an enumerated value of {@link OH_ArkUI_TextMenuType}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_GetMenuType(OH_ArkUI_TextEditorSelectionMenuOptions* options,
    OH_ArkUI_TextMenuType* menuType);

/**
 * @brief Sets the callback triggered when the text selection menu is displayed.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param userData Pointer to the user data.
 * @param callback The callback function of menu show.
 *     start The start offset of the selected content.
 *     end The end offset of the selected content.
 *     callbackUserData The user data.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_RegisterOnMenuShowCallback(
    OH_ArkUI_TextEditorSelectionMenuOptions* options, void* userData,
    void (*callback)(int32_t start, int32_t end, void* callbackUserData));

/**
 * @brief Sets the callback triggered when the text selection menu is hidden.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param userData Pointer to the user data.
 * @param callback The callback function of menu hide.
 *     start The start offset of the selected content.
 *     end The end offset of the selected content.
 *     userData The user data.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_RegisterOnMenuHideCallback(
    OH_ArkUI_TextEditorSelectionMenuOptions* options, void* userData,
    void (*callback)(int32_t start, int32_t end, void* callbackUserData));

/**
 * @brief Sets the callback triggered when the text selection menu appears.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param userData Pointer to the user data.
 * @param callback The callback function of menu appear.
 *     start The start offset of the selected content.
 *     end The end offset of the selected content.
 *     userData The user data.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_RegisterOnMenuAppearCallback(
    OH_ArkUI_TextEditorSelectionMenuOptions* options, void* userData,
    void (*callback)(int32_t start, int32_t end, void* callbackUserData));

/**
 * @brief Sets the callback triggered when the text selection menu disappears.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param userData Pointer to the user data.
 * @param callback The callback function of menu disappear.
 *     userData The user data.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_RegisterOnMenuDisappearCallback(
    OH_ArkUI_TextEditorSelectionMenuOptions* options, void* userData, void (*callback)(void* callbackUserData));

/**
 * @brief Sets the haptic feedback mode of the text selection menu in the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param mode Haptic feedback mode. The value is an enumerated value of {@link OH_ArkUI_HapticFeedbackMode}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_SetHapticFeedbackMode(
    OH_ArkUI_TextEditorSelectionMenuOptions* options, OH_ArkUI_HapticFeedbackMode mode);

/**
 * @brief Obtains the haptic feedback mode of the text selection menu in the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @param mode Pointer to the haptic feedback mode. The value is an enumerated value of
 *     {@link OH_ArkUI_HapticFeedbackMode}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorSelectionMenuOptions_GetHapticFeedbackMode(
    OH_ArkUI_TextEditorSelectionMenuOptions* options, OH_ArkUI_HapticFeedbackMode* mode);

/**
 * @brief Closes the text selection menu of the styled string controller in the text editor.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_CloseSelectionMenu(
    OH_ArkUI_TextEditorStyledStringController* controller);

/**
 * @brief Obtains the selected area using the styled string controller.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param start Pointer to the start position of the selected area.
 * @param end Pointer to the end position of the selected area.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_GetSelection(
    const OH_ArkUI_TextEditorStyledStringController* controller, uint32_t* start, uint32_t* end);

/**
 * @brief Sets the styled string displayed using the styled string controller.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_SetStyledString(
    const OH_ArkUI_TextEditorStyledStringController* controller, const ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Obtains the styled string displayed using the styled string controller.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_GetStyledString(
    const OH_ArkUI_TextEditorStyledStringController* controller, ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Sets the placeholder text in the styled string style using the styled string controller.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_SetStyledPlaceholder(
    const OH_ArkUI_TextEditorStyledStringController* controller, const ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Scroll the text editor component to make the specified content visible.
 *
 * @param controller <b>TextEditor</b> styled string controller.
 * @param start The start offset of the content to be made visible.
 * @param end The end offset of the content to be made visible
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_ScrollToVisible(
    const OH_ArkUI_TextEditorStyledStringController* controller, int32_t start, int32_t end);

/**
* @brief Set the parameters of background style.
*
* @param style The ArkUI_PickerIndicatorStyle instance.
* @param background The parameters of background style.
* @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if success.
*         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} The parameters set need to be consistent with
*         the type of the created instance. If they are not consistent, this error code will be returned.
*         This interface only takes effect when the type is "background".
* @since 23
*/
ArkUI_ErrorCode OH_ArkUI_PickerIndicatorStyle_ConfigureBackground(ArkUI_PickerIndicatorStyle* style,
    ArkUI_PickerIndicatorBackground* background);

/**
* @brief Set the parameters of divider style.
*
* @param style The ArkUI_PickerIndicatorStyle instance.
* @param divider The parameters of divider style.
* @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if success.
*         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} The parameters set need to be consistent with
*         the type of the created instance. If they are not consistent, this error code will be returned.
*         This interface only takes effect when the type is "divider".
* @since 23
*/
ArkUI_ErrorCode OH_ArkUI_PickerIndicatorStyle_ConfigureDivider(ArkUI_PickerIndicatorStyle* style,
    ArkUI_PickerIndicatorDivider* divider);

/**
 * @brief Enumerates the tree operating status for the cross-language option.
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * Undefined, the initial value of the node tree operating status. Nodes in this status do not support cross-language node tree operations.
     *
     * @since 26.0.0
     */
    OH_ARKUI_TREE_OPERATING_STATUS_UNDEFINED = 0,
    /**
     * Enable, which means that when the option is applied to the node, the node's tree operating status will be enabled.
     *
     * @since 26.0.0
     */
    OH_ARKUI_TREE_OPERATING_STATUS_ENABLE = 1,
    /**
     * Disable, which means that when the option is applied to the node, the node's tree operating status will be disabled.
     *
     * @since 26.0.0
     */
    OH_ARKUI_TREE_OPERATING_STATUS_DISABLE = 2,
} OH_ArkUI_CrossLanguageOperatingStatus;

/**
 * @brief Sets the tree operating status for the cross-language option.
 *
 * @param option The cross-language option.
 * @param status The tree operating status to be set for the cross-language option.
 * Default value: OH_ARKUI_TREE_OPERATING_STATUS_UNDEFINED.
 * @since 26.0.0
 */
void OH_ArkUI_CrossLanguageOption_SetTreeOperatingStatus(ArkUI_CrossLanguageOption* option, OH_ArkUI_CrossLanguageOperatingStatus status);

/**
 * @brief Gets the tree operating status of the cross-language option.
 *
 * @param option The cross-language option.
 * @return Return the tree operating status of the cross-language option.
 * @since 26.0.0
 */
OH_ArkUI_CrossLanguageOperatingStatus OH_ArkUI_CrossLanguageOption_GetTreeOperatingStatus(ArkUI_CrossLanguageOption* option);

/**
 * @brief Defines linear gradient options.
 *
 * @since 26.0.0
 */
typedef struct OH_ArkUI_LinearGradientOptions OH_ArkUI_LinearGradientOptions;

/**
 * @brief Defines radial gradient options.
 *
 * @since 26.0.0
 */
typedef struct OH_ArkUI_RadialGradientOptions OH_ArkUI_RadialGradientOptions;

/**
 * @brief Creates a linear gradient options object.
 * The returned object must be released by calling <b>OH_ArkUI_LinearGradientOptions_Destroy</b>.
 *
 * @return Pointer to the <b>OH_ArkUI_LinearGradientOptions</b> object.
 * @since 26.0.0
 */
OH_ArkUI_LinearGradientOptions* OH_ArkUI_LinearGradientOptions_Create();

/**
 * @brief Destroys a linear gradient options object.
 *
 * @param options Pointer to the <b>OH_ArkUI_LinearGradientOptions</b> object.
 * @since 26.0.0
 */
void OH_ArkUI_LinearGradientOptions_Destroy(OH_ArkUI_LinearGradientOptions* options);

/**
 * @brief Sets angle of linear gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_LinearGradientOptions</b> object.
 * @param angle Start angle of linear gradient.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_SetAngle(OH_ArkUI_LinearGradientOptions* options, float angle);

/**
 * @brief Gets angle of linear gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_LinearGradientOptions</b> object.
 * @param angle Pointer to the start angle of linear gradient.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_GetAngle(const OH_ArkUI_LinearGradientOptions* options, float* angle);

/**
 * @brief Sets direction of linear gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_LinearGradientOptions</b> object.
 * @param direction Direction of linear gradient.
 * The parameter type is {@link ArkUI_LinearGradientDirection}.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_SetDirection(OH_ArkUI_LinearGradientOptions* options,
    ArkUI_LinearGradientDirection direction);

/**
 * @brief Gets direction of linear gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_LinearGradientOptions</b> object.
 * @param direction Pointer to the direction of linear gradient.
 * The parameter type is {@link ArkUI_LinearGradientDirection}.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_GetDirection(const OH_ArkUI_LinearGradientOptions* options,
    ArkUI_LinearGradientDirection* direction);

/**
 * @brief Sets whether colors are repeated in linear gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_LinearGradientOptions</b> object.
 * @param repeating Whether colors are repeated.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_SetRepeating(OH_ArkUI_LinearGradientOptions* options, bool repeating);

/**
 * @brief Gets whether colors are repeated in linear gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_LinearGradientOptions</b> object.
 * @param repeating Pointer to whether colors are repeated.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_GetRepeating(
    const OH_ArkUI_LinearGradientOptions* options, bool* repeating);

/**
 * @brief Sets color stops of linear gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_LinearGradientOptions</b> object.
 * @param colors Pointer to the color array.
 * @param stops Pointer to the stop array.
 * @param colorsAndStopsSize Number of elements in colors and stops.
 *                           The number of elements in colors and stops must be the same.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_SetColorStop(
    OH_ArkUI_LinearGradientOptions* options, const uint32_t* colors, const float* stops, int32_t colorsAndStopsSize);

/**
 * @brief Gets color stops of linear gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_LinearGradientOptions</b> object.
 * @param colors Buffer pointer to the color array.
 * @param stops Buffer pointer to the stop array.
 * @param colorsAndStopsSize Buffer size reserved for color stops by developer.
 *                           The number of elements in colors and stops must be the same.
 *                           It should be larger than writeLength,
 *                           otherwise the operation will return ARKUI_ERROR_CODE_PARAM_INVALID.
 * @param writeLength Number of color stops actually written.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_GetColorStop(
    const OH_ArkUI_LinearGradientOptions* options, uint32_t* colors, float* stops, int32_t colorsAndStopsSize,
    int32_t* writeLength);

/**
 * @brief Creates a radial gradient options object.
 * The returned object must be released by calling <b>OH_ArkUI_RadialGradientOptions_Destroy</b>.
 *
 * @return Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @since 26.0.0
 */
OH_ArkUI_RadialGradientOptions* OH_ArkUI_RadialGradientOptions_Create();

/**
 * @brief Destroys a radial gradient options object.
 *
 * @param options Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @since 26.0.0
 */
void OH_ArkUI_RadialGradientOptions_Destroy(OH_ArkUI_RadialGradientOptions* options);

/**
 * @brief Sets centerX of radial gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @param centerX X-coordinate of center point.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_SetCenterX(OH_ArkUI_RadialGradientOptions* options, float centerX);

/**
 * @brief Gets centerX of radial gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @param centerX Pointer to the X-coordinate of center point.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_GetCenterX(
    const OH_ArkUI_RadialGradientOptions* options, float* centerX);

/**
 * @brief Sets centerY of radial gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @param centerY Y-coordinate of center point.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_SetCenterY(OH_ArkUI_RadialGradientOptions* options, float centerY);

/**
 * @brief Gets centerY of radial gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @param centerY Pointer to the Y-coordinate of center point.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_GetCenterY(
    const OH_ArkUI_RadialGradientOptions* options, float* centerY);

/**
 * @brief Sets radius of radial gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @param radius Radius of radial gradient.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_SetRadius(OH_ArkUI_RadialGradientOptions* options, float radius);

/**
 * @brief Gets radius of radial gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @param radius Pointer to the radius of radial gradient.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_GetRadius(
    const OH_ArkUI_RadialGradientOptions* options, float* radius);

/**
 * @brief Sets whether colors are repeated in radial gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @param repeating Whether colors are repeated.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_SetRepeating(OH_ArkUI_RadialGradientOptions* options, bool repeating);

/**
 * @brief Gets whether colors are repeated in radial gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @param repeating Pointer to whether colors are repeated.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_GetRepeating(
    const OH_ArkUI_RadialGradientOptions* options, bool* repeating);

/**
 * @brief Sets color stops of radial gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @param colors Pointer to the color array.
 * @param stops Pointer to the stop array.
 * @param colorsAndStopsSize Number of elements in colors and stops.
 *                           The number of elements in colors and stops must be the same.
 * @return Returns the result code.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_SetColorStop(
    OH_ArkUI_RadialGradientOptions* options, const uint32_t* colors, const float* stops, int32_t colorsAndStopsSize);

/**
 * @brief Gets color stops of radial gradient options.
 *
 * @param options Pointer to the <b>OH_ArkUI_RadialGradientOptions</b> object.
 * @param colors Buffer pointer to the color array.
 * @param stops Buffer pointer to the stop array.
 * @param colorsAndStopsSize Buffer size reserved for color stops by developer.
 *                           The number of elements in colors and stops must be the same.
 *                           It should be larger than writeLength,
 *             otherwise the operation will return ARKUI_ERROR_CODE_PARAM_INVALID.
 * @param writeLength Number of color stops actually written.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_GetColorStop(
    const OH_ArkUI_RadialGradientOptions* options, uint32_t* colors, float* stops, int32_t colorsAndStopsSize,
    int32_t* writeLength);

/**
 * @brief Enumeration of the policy for mounting child node to the target node.
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * If you want to mount a RenderNode as a child node, that RenderNode must be the only child.
     *
     * @since 26.0.0
     */
    OH_ARKUI_NODE_MOUNT_POLICY_SINGLE_IF_RENDER_NODE = 0,
    /**
     * Multiple child nodes of type Node or RenderNode allowed.
     *
     * @since 26.0.0
     */
    OH_ARKUI_NODE_MOUNT_POLICY_MIXED = 1,
} OH_ArkUI_NodeMountPolicy;
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_TYPE_H
/** @} */
