/**
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

#include "common_type.h"
#include "error_code.h"

#include "drawable_descriptor.h"
#include "native_type_visual.h"
#include "node_attributes/slider.h"
#include "node_attributes/checkbox.h"
#include "node_attributes/button.h"
#include "node_attributes/embedded_component.h"
#include "node_attributes/xcomponent.h"

#include "node_attributes/common_attributes.h"
#include "node_attributes/grid.h"
#include "node_attributes/list.h"
#include "node_attributes/list_item.h"
#include "node_attributes/scroll.h"
#include "node_attributes/water_flow.h"
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
#include "node_attributes/layout.h"

#include "node_attributes/navigation_router.h"
#include "node_attributes/swiper.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines a custom dialog controller object for ArkUI on the native side, which is used to create and
 * manage custom dialog boxes at the native layer, supporting features such as display, dismissal, and attribute
 * configuration of dialog boxes. It is applicable to scenarios where the lifecycle of ArkUI dialog boxes needs to be
 * controlled through C/C++ code. For specific control APIs, see {@link ArkUI_NativeDialogAPI_1},
 * {@link ArkUI_NativeDialogAPI_2}, and {@link ArkUI_NativeDialogAPI_3}.
 *
 * @since 12
 */
struct ArkUI_NativeDialog;

/**
 * @brief Defines the pointer to the custom dialog box controller object of ArkUI on the native side, which is
 * used to identify and operate a custom dialog box instance.
 *
 * @since 12
 */
typedef struct ArkUI_NativeDialog* ArkUI_NativeDialogHandle;

/**
 * @brief Defines gesture collection interception information. During gesture collection in the touch test, this
 * struct is used to provide the gesture and touch recognizers in the response chain to the interception callback,
 * and carries the gesture collection intervention result set by the callback. For details about the related APIs for
 * gesture collection interception, see {@link native_gesture.h}.
 *
 * @since 26.0.0
 */
typedef struct ArkUI_GestureCollectInterceptInfo ArkUI_GestureCollectInterceptInfo;

/**
 * @brief Defines a component accessibility state, describing the selected, checked, disabled, and other states of
 * the component. It is applicable to scenarios where the accessibility service reads data and interacts with the
 * component, helping users obtain the current state of the component.
 *
 * @since 12
 */
typedef struct ArkUI_AccessibilityState ArkUI_AccessibilityState;

/**
 * @brief Defines a component accessibility value, describing the accessibility state of the component, such as
 * the minimum, maximum, and current values of a range-type component, as well as text descriptions. It is applicable
 * to scenarios where the current state information of a component needs to be provided to the accessibility service.
 *
 * @since 12
 */
typedef struct ArkUI_AccessibilityValue ArkUI_AccessibilityValue;

/**
 * @brief Defines custom property information, which is used to represent the custom property of a component.
 * You can use related APIs to add, remove, and obtain custom properties for ArkUI components, and obtain the
 * string values of custom properties.
 *
 * @since 14
 */
typedef struct ArkUI_CustomProperty ArkUI_CustomProperty;

/**
 * @brief Defines host window information.
 *
 * @since 15
 */
typedef struct ArkUI_HostWindowInfo ArkUI_HostWindowInfo;

/**
 * @brief Defines active child node information of the current node. You can query the number of active child nodes,
 * obtain child nodes by subscript, and release resources after use.
 *
 * @since 14
 */
typedef struct ArkUI_ActiveChildrenInfo ArkUI_ActiveChildrenInfo;

/**
 * @brief Defines a cross-language configuration option, which is used to configure the cross-language access
 * capability of a target node, for example, whether cross-language attribute modification is allowed. Since API
 * version 26.0.0, you can also configure cross-language operation status of a node tree.
 *
 * @since 15
 */
typedef struct ArkUI_CrossLanguageOption ArkUI_CrossLanguageOption;

/**
 * @brief Defines the text drag preview style in the selected state. It is applicable to scenarios where the preview
 * effect in selected state needs to be displayed during text dragging, improving user interaction experience.
 * @since 23
 */
typedef struct ArkUI_SelectedDragPreviewStyle ArkUI_SelectedDragPreviewStyle;

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
 * @brief Enumerates the focus wrap mode of components. The default value is **ARKUI_FOCUS_WRAP_MODE_DEFAULT** for the
 * **Grid** and **List** components.
 *
 * @since 20
 */
typedef enum {
    /** Default mode, where focus does not wrap when arrow keys are used. */
    ARKUI_FOCUS_WRAP_MODE_DEFAULT = 0,
    /** Auto mode, where focus wraps automatically when arrow keys are used. */
    ARKUI_FOCUS_WRAP_WITH_ARROW = 1,
} ArkUI_FocusWrapMode;

/**
 * @brief Enumerates column count policies for different responsive breakpoints.
 *
 * @since 22
 */
typedef enum {
    /** No responsive breakpoint policy is set. */
    ARKUI_ITEMFILLPOLICY_NONE = -1,
    /**
     * **List** or **Swiper** component: 1 column (SM or smaller), 2 columns (MD), 3 columns (LG or larger).<br>
     * **Grid** or **WaterFlow** component: 2 columns (SM or smaller), 3 columns (MD), 5 columns (LG or larger).
     */
    ARKUI_ITEMFILLPOLICY_DEFAULT = 0,
    /** 1 column (SM or smaller), 2 columns (MD), 3 columns (LG or larger). */
    ARKUI_ITEMFILLPOLICY_SM1MD2LG3 = 1,
    /** 2 columns (SM or smaller), 3 columns (MD), 5 columns (LG or larger). */
    ARKUI_ITEMFILLPOLICY_SM2MD3LG5 = 2,
} ArkUI_ItemFillPolicy;

/**
 * @brief Enumerates crown sensitivity levels.
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * Low sensitivity.
     *
     * @since 26.0.0
     */
    ARKUI_CROWN_SENSITIVITY_LOW = 0,
    /**
     * Medium sensitivity.
     *
     * @since 26.0.0
     */
    ARKUI_CROWN_SENSITIVITY_MEDIUM = 1,
    /**
     * High sensitivity.
     *
     * @since 26.0.0
     */
    ARKUI_CROWN_SENSITIVITY_HIGH = 2,
} ArkUI_CrownSensitivity;

/**
 * @brief Enumerates the border styles.
 *
 * @since 12
 */
typedef enum {
    /** Solid border. This is the default value. */
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
    /** The mode is automatically set to enabled or disabled based on the component. */
    ARKUI_ACCESSIBILITY_MODE_AUTO = 0,
    /** The component can be identified by the accessibility service. */
    ARKUI_ACCESSIBILITY_MODE_ENABLED,
    /** The component cannot be identified by the accessibility service. */
    ARKUI_ACCESSIBILITY_MODE_DISABLED,
    /** The component and all its child components cannot be identified by the accessibility service. */
    ARKUI_ACCESSIBILITY_MODE_DISABLED_FOR_DESCENDANTS,
} ArkUI_AccessibilityMode;

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
    /** Light mode. */
    ARKUI_SYSTEM_COLOR_MODE_LIGHT = 0,
    /** Dark mode. */
    ARKUI_SYSTEM_COLOR_MODE_DARK,
} ArkUI_SystemColorMode;

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
 * @brief Enumerates the component units.
 *
 * @since 12
 */
typedef enum {
    /** Default, which is fp for fonts and vp for non-fonts. */
    ARKUI_LENGTH_METRIC_UNIT_DEFAULT = -1,
    /** The unit is px. */
    ARKUI_LENGTH_METRIC_UNIT_PX = 0,
    /** The unit is vp. */
    ARKUI_LENGTH_METRIC_UNIT_VP,
    /** The unit is fp. */
    ARKUI_LENGTH_METRIC_UNIT_FP
} ArkUI_LengthMetricUnit;

/**
 * @brief Enumerates the accessibility check box states.
 *
 * @since 12
 */
typedef enum {
    /** The check box is not selected. */
    ARKUI_ACCESSIBILITY_UNCHECKED = 0,
    /** The check box is selected. */
    ARKUI_ACCESSIBILITY_CHECKED,
} ArkUI_AccessibilityCheckedState;

/**
 * @brief Enumerates the accessibility action types.
 *
 * @since 12
 */
typedef enum {
    /** Tapping. */
    ARKUI_ACCESSIBILITY_ACTION_CLICK = 1 << 0,
    /** Long press. */
    ARKUI_ACCESSIBILITY_ACTION_LONG_CLICK = 1 << 1,
    /** Cut. */
    ARKUI_ACCESSIBILITY_ACTION_CUT = 1 << 2,
    /** Copy. */
    ARKUI_ACCESSIBILITY_ACTION_COPY = 1 << 3,
    /** Paste. */
    ARKUI_ACCESSIBILITY_ACTION_PASTE = 1 << 4,
} ArkUI_AccessibilityActionType;

/**
 * @brief Enumerates the types of expanded safe areas.
 *
 * @since 12
 */
typedef enum {
    /** Default non-safe area of the system, including the status bar and navigation bar. This is the default value. */
    ARKUI_SAFE_AREA_TYPE_SYSTEM = 1,
    /** Non-safe area of the device, for example, the notch area. */
    ARKUI_SAFE_AREA_TYPE_CUTOUT = 1 << 1,
    /** Soft keyboard area. */
    ARKUI_SAFE_AREA_TYPE_KEYBOARD = 1 << 2,
} ArkUI_SafeAreaType;

/**
 * @brief Enumerates the soft keyboard avoidance modes.
 *
 * @since 15
 */
typedef enum {
    /** Automatically avoids the soft keyboard and compresses the height when reaching the maximum limit. */
    ARKUI_KEYBOARD_AVOID_MODE_DEFAULT = 0,
    /** The layout is not adjusted to avoid the keyboard. */
    ARKUI_KEYBOARD_AVOID_MODE_NONE,
} ArkUI_KeyboardAvoidMode;

/**
 * @brief Enumerates the types of display areas for the hover mode.
 *
 * @since 15
 */
typedef enum {
    /** Upper half screen. */
    ARKUI_HOVER_MODE_AREA_TYPE_TOP = 0,
    /** Lower half screen. */
    ARKUI_HOVER_MODE_AREA_TYPE_BOTTOM,
} ArkUI_HoverModeAreaType;

/**
 * @brief Enumerates the expansion mode of child nodes.
 *
 * @since 15
 */
typedef enum {
    /**
     * Child nodes are not expanded.
     */
    ARKUI_NOT_EXPAND = 0,
    /**
     * Child nodes are expanded immediately upon rendering.
     */
    ARKUI_EXPAND = 1,
    /**
     * Lazy expansion, indicating that child nodes are only expanded when needed. For details about the node expansion
     * conditions, see {@link LazyForEach: Lazy Data Loading}.
     */
    ARKUI_LAZY_EXPAND = 2,
} ArkUI_ExpandMode;

/**
 * @brief Enumerates rectangle edge directions.
 *
 * @since 20
 */
typedef enum {
    /** All four edges. */
    ARKUI_EDGE_DIRECTION_ALL = 0,
    /** Left edge. */
    ARKUI_EDGE_DIRECTION_LEFT,
    /** Right edge. */
    ARKUI_EDGE_DIRECTION_RIGHT,
    /** Top edge. */
    ARKUI_EDGE_DIRECTION_TOP,
    /** Bottom edge. */
    ARKUI_EDGE_DIRECTION_BOTTOM,
} ArkUI_EdgeDirection;

/**
 * @brief Enumerates corner directions.
 *
 * @since 20
 */
typedef enum {
    /**
     * All four corners.
     */
    ARKUI_CORNER_DIRECTION_ALL = 0,
    /**
     * Upper left corner.
     */
    ARKUI_CORNER_DIRECTION_TOP_LEFT,
    /**
     * Upper right corner.
     */
    ARKUI_CORNER_DIRECTION_TOP_RIGHT,
    /**
     * Lower left corner.
     */
    ARKUI_CORNER_DIRECTION_BOTTOM_LEFT,
    /**
     * Lower right corner.
     */
    ARKUI_CORNER_DIRECTION_BOTTOM_RIGHT,
} ArkUI_CornerDirection;

/**
 * @brief Enumerates menu display policies.
 *
 * @since 23
 */
typedef enum {
    /** Whether the menu is displayed depends on the underlying default logic. */
    ARKUI_MENU_POLICY_DEFAULT = 0,
    /** The menu is not popped up. */
    ARKUI_MENU_POLICY_HIDE = 1,
    /** The menu is popped up. */
    ARKUI_MENU_POLICY_SHOW = 2,
} ArkUI_MenuPolicy;

/**
 * @brief Enumerates strategies for drawing rounded corners.
 *
 * @since 23
 */
typedef enum {
    /** Online drawing mode. */
    ARKUI_RENDERSTRATEGY_FAST = 0,
    /** Off-screen drawing mode. */
    ARKUI_RENDERSTRATEGY_OFFSCREEN,
} ArkUI_RenderStrategy;

/**
 * @brief Defines a system font style change event, which is used to pass the event information to the registered
 * system font style change callback when the system font size or weight changes.
 *
 * @since 12
 */
typedef struct ArkUI_SystemFontStyleEvent ArkUI_SystemFontStyleEvent;

/**
 * @brief Defines the options for the selection operation in ArkUI. It is applicable to scenarios where selection
 * interaction is required within an application, providing you with the capability to customize selection behavior.
 *
 * @since 23
 */
typedef struct ArkUI_SelectionOptions ArkUI_SelectionOptions;

/**
 * @brief Creates layout constraints. After the created layout constraint pointer is used, call
 * {@link OH_ArkUI_LayoutConstraint_Dispose} to release it. If the pointer is not released, memory leakage may occur.
 *
 * @return Pointer to the created layout constraint.
 * @since 12
 */
ArkUI_LayoutConstraint* OH_ArkUI_LayoutConstraint_Create();

/**
 * @brief Performs a deep copy of a layout constraint. The new layout constraint pointer returned by the deep copy is
 * independent of the original pointer. You need to call {@link OH_ArkUI_LayoutConstraint_Dispose} to release them
 * separately after use.
 *
 * @param Constraint Pointer to the layout constraint.
 * @return Pointer to the new layout constraint.
 * @since 12
 */
ArkUI_LayoutConstraint* OH_ArkUI_LayoutConstraint_Copy(const ArkUI_LayoutConstraint* Constraint);

/**
 * @brief Disposes of a layout constraint pointer. This API must be used together with
 * {@link OH_ArkUI_LayoutConstraint_Create} or {@link OH_ArkUI_LayoutConstraint_Copy}. Each layout constraint pointer
 * can be destroyed only once. After being destroyed, the pointer should not be used anymore.
 *
 * @param Constraint Pointer to the layout constraint.
 * @since 12
 */
void* OH_ArkUI_LayoutConstraint_Dispose(ArkUI_LayoutConstraint* Constraint);

/**
 * @brief Obtains the maximum width using a layout constraint.
 *
 * @param Constraint Pointer to the layout constraint.
 * @return Maximum width, in px.
 * @since 12
 */
int32_t OH_ArkUI_LayoutConstraint_GetMaxWidth(const ArkUI_LayoutConstraint* Constraint);

/**
 * @brief Obtains the minimum width using a layout constraint.
 *
 * @param Constraint Pointer to the layout constraint.
 * @return Minimum width, in px.
 * @since 12
 */
int32_t OH_ArkUI_LayoutConstraint_GetMinWidth(const ArkUI_LayoutConstraint* Constraint);

/**
 * @brief Obtains the maximum height using a layout constraint.
 *
 * @param Constraint Pointer to the layout constraint.
 * @return Maximum height, in px.
 * @since 12
 */
int32_t OH_ArkUI_LayoutConstraint_GetMaxHeight(const ArkUI_LayoutConstraint* Constraint);

/**
 * @brief Obtains the minimum height using a layout constraint.
 *
 * @param Constraint Pointer to the layout constraint.
 * @return Minimum height, in px.
 * @since 12
 */
int32_t OH_ArkUI_LayoutConstraint_GetMinHeight(const ArkUI_LayoutConstraint* Constraint);

/**
 * @brief Obtains the width percentage reference using a layout constraint.
 *
 * @param Constraint Pointer to the layout constraint.
 * @return Width percentage reference.
 * @since 12
 */
int32_t OH_ArkUI_LayoutConstraint_GetPercentReferenceWidth(const ArkUI_LayoutConstraint* Constraint);

/**
 * @brief Obtains the height percentage reference using a layout constraint.
 *
 * @param Constraint Pointer to the layout constraint.
 * @return Height percentage reference.
 * @since 12
 */
int32_t OH_ArkUI_LayoutConstraint_GetPercentReferenceHeight(const ArkUI_LayoutConstraint* Constraint);

/**
 * @brief Sets the maximum width.
 *
 * @param Constraint Pointer to the layout constraint.
 * @param value Maximum width, in px. The value range is [0, +∞).
 * @since 12
 */
void OH_ArkUI_LayoutConstraint_SetMaxWidth(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
 * @brief Sets the minimum width.
 *
 * @param Constraint Pointer to the layout constraint.
 * @param value Minimum width, in px. The value range is [0, +∞).
 * @since 12
 */
void OH_ArkUI_LayoutConstraint_SetMinWidth(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
 * @brief Sets the maximum height.
 *
 * @param Constraint Pointer to the layout constraint.
 * @param value Maximum height, in px. The value range is [0, +∞).
 * @since 12
 */
void OH_ArkUI_LayoutConstraint_SetMaxHeight(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
 * @brief Sets the minimum height.
 *
 * @param Constraint Pointer to the layout constraint.
 * @param value Minimum height, in px. The value range is [0, +∞).
 * @since 12
 */
void OH_ArkUI_LayoutConstraint_SetMinHeight(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
 * @brief Sets the width percentage reference.
 *
 * @param Constraint Pointer to the layout constraint.
 * @param value Width percentage reference. The value range is [0, +∞).
 * @since 12
 */
void OH_ArkUI_LayoutConstraint_SetPercentReferenceWidth(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
 * @brief Sets the height percentage reference.
 *
 * @param Constraint Pointer to the layout constraint.
 * @param value Height percentage reference. The value range is [0, +∞).
 * @since 12
 */
void OH_ArkUI_LayoutConstraint_SetPercentReferenceHeight(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
 * @brief Obtains the pointer to the canvas for drawing, which can be converted into the {@link OH_Drawing_Canvas}
 * pointer of the graphics library for drawing.
 *
 * @param context Pointer to the drawing context.
 * @return Pointer to the canvas for drawing.
 * @since 12
 */
void* OH_ArkUI_DrawContext_GetCanvas(ArkUI_DrawContext* context);

/**
 * @brief Obtains the size of a drawing area.
 *
 * @param context Pointer to the drawing context.
 * @return Size of the drawing area.
 * @since 12
 */
ArkUI_IntSize OH_ArkUI_DrawContext_GetSize(ArkUI_DrawContext* context);

/**
 * @brief Sets the font weight of the digit-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator.
 * @param fontWeight Font weight. The value is an enumerated value of {@link ArkUI_FontWeight}.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetFontWeight(ArkUI_SwiperDigitIndicator *indicator, ArkUI_FontWeight fontWeight);

/**
 * @brief Obtains the font weight of the digit-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator.
 * @return Font weight. The value is an enumerated value of {@link ArkUI_FontWeight}.
 * @since 19
 */
ArkUI_FontWeight OH_ArkUI_SwiperDigitIndicator_GetFontWeight(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Sets the font weight of the selected digit-style navigation indicator for the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator.
 * @param selectedFontWeight Font weight. The value is an enumerated value of {@link ArkUI_FontWeight}.
 * @since 19
 */
void OH_ArkUI_SwiperDigitIndicator_SetSelectedFontWeight(
    ArkUI_SwiperDigitIndicator *indicator, ArkUI_FontWeight selectedFontWeight);

/**
 * @brief Obtains the font weight of the selected digit-style navigation indicator of the **Swiper** component.
 *
 * @param indicator Pointer to the digit-style navigation indicator.
 * @return Font weight. The value is an enumerated value of {@link ArkUI_FontWeight}.
 * @since 19
 */
ArkUI_FontWeight OH_ArkUI_SwiperDigitIndicator_GetSelectedFontWeight(ArkUI_SwiperDigitIndicator* indicator);

/**
 * @brief Defines the content transition effect.
 *
 * @since 21
 */
typedef struct ArkUI_ContentTransitionEffect ArkUI_ContentTransitionEffect;

/**
 * @brief Creates a **ContentTransitionEffect** attribute object.
 *
 * @param type Transition animation type. **0**: No transition animation. **1**: Fade-in and fade-out transition
 *     animation.
 * @return Pointer to the **ContentTransitionEffect** object.
 * @since 21
 */
ArkUI_ContentTransitionEffect* OH_ArkUI_ContentTransitionEffect_Create(int32_t type);

/**
 * @brief Creates an accessibility state.
 *
 * @return Pointer to the created accessibility state object. If a null pointer is returned, the creation fails. A
 *     possible cause is that the application address space is full.
 * @since 12
 */
ArkUI_AccessibilityState* OH_ArkUI_AccessibilityState_Create(void);

/**
 * @brief Disposes of the pointer to an accessibility state.
 *
 * @param state Pointer to the created accessibility state object.
 * @since 12
 */
void OH_ArkUI_AccessibilityState_Dispose(ArkUI_AccessibilityState* state);

/**
 * @brief Sets whether an accessibility state is disabled.
 *
 * @param state Pointer to the created accessibility state object.
 * @param isDisabled Whether the accessibility state is disabled. The value **1** means that the accessibility state is
 *     disabled, and **0** means the opposite. The default value is **0**.
 * @since 12
 */
void OH_ArkUI_AccessibilityState_SetDisabled(ArkUI_AccessibilityState* state, int32_t isDisabled);

/**
 * @brief Obtains whether an accessibility state is disabled.
 *
 * @param state Pointer to the created accessibility state object.
 * @return Whether the accessibility state is disabled. The value **1** means that the accessibility state is disabled,
 *     and **0** means the opposite. The default value is **0**.<br>
 *     If the value of **state** is null, the default value is returned.
 * @since 12
 */
int32_t OH_ArkUI_AccessibilityState_IsDisabled(ArkUI_AccessibilityState* state);

/**
 * @brief Sets whether an accessibility state is selected.
 *
 * @param state Pointer to the created accessibility state object.
 * @param isSelected Whether the accessibility state is selected. The value **1** means that the accessibility state is
 *     selected, and **0** means the opposite. The default value is **0**.
 * @since 12
 */
void OH_ArkUI_AccessibilityState_SetSelected(ArkUI_AccessibilityState* state, int32_t isSelected);

/**
 * @brief Obtains whether an accessibility state is selected.
 *
 * @param state Pointer to the created accessibility state object.
 * @return Whether the accessibility state is selected. The value **1** means that the accessibility state is selected,
 *     and **0** means the opposite. The default value is **0**.<br>
 *     If the value of **state** is null, the default value is returned.
 * @since 12
 */
int32_t OH_ArkUI_AccessibilityState_IsSelected(ArkUI_AccessibilityState* state);

/**
 * @brief Sets the check box state of an accessibility state.
 *
 * @param state Pointer to the created accessibility state object.
 * @param checkedState Check box status. The parameter type is {@link ArkUI_AccessibilityCheckedState}. The default
 *     value is **ARKUI_ACCESSIBILITY_UNCHECKED**.
 * @since 12
 */
void OH_ArkUI_AccessibilityState_SetCheckedState(ArkUI_AccessibilityState* state, int32_t checkedState);

/**
 * @brief Obtains the check box state of an accessibility state.
 *
 * @param state Pointer to the created accessibility state object.
 * @return Check box status. The parameter type is {@link ArkUI_AccessibilityCheckedState}. The default value is
 *     **ARKUI_ACCESSIBILITY_UNCHECKED**.<br>
 *     If a parameter error occurs, the default value is returned.
 * @since 12
 */
int32_t OH_ArkUI_AccessibilityState_GetCheckedState(ArkUI_AccessibilityState* state);

/**
 * @brief Creates an **AccessibilityValue** instance.
 *
 * @return Pointer to the created **AccessibilityValue** instance.
 * @since 12
 */
ArkUI_AccessibilityValue* OH_ArkUI_AccessibilityValue_Create(void);

/**
 * @brief Disposes of the pointer to an **AccessibilityValue** instance.
 *
 * @param value Pointer to the created **AccessibilityValue** instance.
 * @since 12
 */
void OH_ArkUI_AccessibilityValue_Dispose(ArkUI_AccessibilityValue* value);

/**
 * @brief Sets the minimum accessibility value.
 *
 * @param value Pointer to the created **AccessibilityValue** instance.
 * @param min Minimum value for the range-based component. The default value is **-1**.
 * @since 12
 */
void OH_ArkUI_AccessibilityValue_SetMin(ArkUI_AccessibilityValue* value, int32_t min);

/**
 * @brief Obtains the minimum accessibility value.
 *
 * @param value Pointer to the created **AccessibilityValue** instance.
 * @return Minimum value for the range-based component. The default value is **-1**.<br>
 *     If a parameter error occurs, **-1** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AccessibilityValue_GetMin(ArkUI_AccessibilityValue* value);

/**
 * @brief Sets the maximum accessibility value.
 *
 * @param value Pointer to the created **AccessibilityValue** instance.
 * @param max Maximum value for the range-based component. The default value is **-1**.
 * @since 12
 */
void OH_ArkUI_AccessibilityValue_SetMax(ArkUI_AccessibilityValue* value, int32_t max);

/**
 * @brief Obtains the maximum accessibility value.
 *
 * @param value Pointer to the created **AccessibilityValue** instance.
 * @return Maximum value for the range-based component. The default value is **-1**.<br>
 *     If a parameter error occurs, **-1** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AccessibilityValue_GetMax(ArkUI_AccessibilityValue* value);

/**
 * @brief Sets the current accessibility value.
 *
 * @param value Pointer to the created **AccessibilityValue** instance.
 * @param current Current value for the range-based component. The default value is **-1**.
 * @since 12
 */
void OH_ArkUI_AccessibilityValue_SetCurrent(ArkUI_AccessibilityValue* value, int32_t current);

/**
 * @brief Obtains the current accessibility value.
 *
 * @param value Pointer to the created **AccessibilityValue** instance.
 * @return Current value for the range-based component. The default value is **-1**.<br>
 *     If a parameter error occurs, **-1** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AccessibilityValue_GetCurrent(ArkUI_AccessibilityValue* value);

/**
 * @brief Sets the minimum value for accessibility information of the range-based component.
 *
 * @param value Pointer to the accessibility information object of the range-based component for which you want to set
 *     the minimum value.
 * @param rangeMin Minimum value for the range-based component. The default value is **-1**.
 * @since 18
 */
void OH_ArkUI_AccessibilityValue_SetRangeMin(ArkUI_AccessibilityValue* value, int32_t rangeMin);

/**
 * @brief Obtains the minimum value for accessibility information of the range-based component.
 *
 * @param value Pointer to the accessibility information object of the range-based component for which you want to
 *     obtain the minimum value.
 * @return Minimum value for the range-based component. The default value is **-1**.<br>
 *     If a parameter error occurs, **-1** is returned.
 * @since 18
 */
int32_t OH_ArkUI_AccessibilityValue_GetRangeMin(ArkUI_AccessibilityValue* value);

/**
 * @brief Sets the maximum value for accessibility information of the range-based component.
 *
 * @param value Pointer to the accessibility information object of the range-based component for which you want to set
 *     the maximum value.
 * @param rangeMax Maximum value for the range-based component. The default value is **-1**.
 * @since 18
 */
void OH_ArkUI_AccessibilityValue_SetRangeMax(ArkUI_AccessibilityValue* value, int32_t rangeMax);

/**
 * @brief Obtains the maximum value for accessibility information of the range-based component.
 *
 * @param value Pointer to the accessibility information object of the range-based component for which you want to
 *     obtain the minimum value.
 * @return Maximum value for the range-based component. The default value is **-1**.<br>
 *     If a parameter error occurs, **-1** is returned.
 * @since 18
 */
int32_t OH_ArkUI_AccessibilityValue_GetRangeMax(ArkUI_AccessibilityValue* value);

/**
 * @brief Sets the current value for accessibility information of the range-based component.
 *
 * @param value Pointer to the accessibility information object of the range-based component for which you want to set
 *     the current value.
 * @param rangeCurrent Current value for the range-based component. The default value is **-1**.
 * @since 18
 */
void OH_ArkUI_AccessibilityValue_SetRangeCurrent(ArkUI_AccessibilityValue* value, int32_t rangeCurrent);

/**
 * @brief Obtains the current value for accessibility information of the range-based component.
 *
 * @param value Pointer to the accessibility information object of the range-based component for which you want to
 *     obtain the current value.
 * @return Current value for the range-based component. The default value is **-1**.<br>
 *     If a parameter error occurs, **-1** is returned.
 * @since 18
 */
int32_t OH_ArkUI_AccessibilityValue_GetRangeCurrent(ArkUI_AccessibilityValue* value);

/**
 * @brief Sets the text description of an **AccessibilityValue** instance.
 *
 * @param value Pointer to the created **AccessibilityValue** instance.
 * @param text Pointer to the text description. The default value is an empty string.
 * @since 12
 */
void OH_ArkUI_AccessibilityValue_SetText(ArkUI_AccessibilityValue* value, const char* text);

/**
 * @brief Obtains the text description of an **AccessibilityValue** instance.
 *
 * @param value Pointer to the created **AccessibilityValue** instance.
 * @return Pointer to the text description. The default value is an empty string.<br>
 *     If a parameter error occurs, a null pointer is returned.
 * @since 12
 */
const char* OH_ArkUI_AccessibilityValue_GetText(ArkUI_AccessibilityValue* value);

/**
 * @brief Destroys an {@link ArkUI_CustomProperty} instance.
 *
 * @param handle Pointer to the instance to be destroyed.
 * @since 14
 */
void OH_ArkUI_CustomProperty_Destroy(ArkUI_CustomProperty* handle);

/**
 * @brief Obtains the value of a custom property object.
 *
 * @param handle Pointer to the custom property object.
 * @return Pointer to the value of a custom property object.
 * @since 14
 */
const char* OH_ArkUI_CustomProperty_GetStringValue(ArkUI_CustomProperty* handle);

/**
 * @brief Obtains the window name in an {@link ArkUI_HostWindowInfo} object.
 *
 * @param info Pointer to the **HostWindowInfo** object.
 * @return Pointer to the window name in the {@link ArkUI_HostWindowInfo} object.
 * @since 15
 */
const char* OH_ArkUI_HostWindowInfo_GetName(ArkUI_HostWindowInfo* info);

/**
 * @brief Destroys an {@link ArkUI_HostWindowInfo} object.
 *
 * @param info Pointer to the {@link ArkUI_HostWindowInfo} object to be destroyed.
 * @since 15
 */
void OH_ArkUI_HostWindowInfo_Destroy(ArkUI_HostWindowInfo* info);

/**
 * @brief Destroys the {@link ArkUI_ActiveChildrenInfo} instance and releases the resources allocated when obtaining
 * information about active child nodes.
 *
 * @param handle Pointer to the {@link ArkUI_ActiveChildrenInfo} instance to be destroyed.
 * @since 14
 */
void OH_ArkUI_ActiveChildrenInfo_Destroy(ArkUI_ActiveChildrenInfo* handle);

/**
 * @brief Obtains the child node whose subscript is index in the {@link ArkUI_ActiveChildrenInfo} struct. This API is
 * applicable to traversing active child nodes by subscript.
 *
 * @param handle Pointer to the {@link ArkUI_ActiveChildrenInfo} instance from which the information is to be obtained.
 * @param index Index of the target child node.
 * @return Handle to the child node at the specified index, or **nullptr** if an error occurs.
 * @since 14
 */
ArkUI_NodeHandle OH_ArkUI_ActiveChildrenInfo_GetNodeByIndex(ArkUI_ActiveChildrenInfo* handle, int32_t index);

/**
 * @brief Obtains the number of child nodes in an {@link ArkUI_ActiveChildrenInfo} struct. This API is applicable to
 * determining the number of child nodes before traversing active child nodes.
 *
 * @param handle Pointer to the {@link ArkUI_ActiveChildrenInfo} instance from which the information is to be obtained.
 * @return Number of child nodes. The default value is **0**.
 * @since 14
 */
int32_t OH_ArkUI_ActiveChildrenInfo_GetCount(ArkUI_ActiveChildrenInfo* handle);

/**
 * @brief Creates an instance of the cross-language configuration option.
 *
 * @return Pointer to the {@link ArkUI_CrossLanguageOption} instance created. If a null pointer is returned,
 *         creation failed, possibly due to insufficient memory.
 * @since 15
 */
ArkUI_CrossLanguageOption* OH_ArkUI_CrossLanguageOption_Create(void);

/**
 * @brief Destroys an instance of the cross-language configuration option.
 *
 * @param option Pointer to the cross-language configuration option instance to be destroyed.
 * @since 15
 */
void OH_ArkUI_CrossLanguageOption_Destroy(ArkUI_CrossLanguageOption* option);

/**
 * @brief Sets whether cross-language attribute setting is allowed in the configuration option.
 *
 * @param option Pointer to the cross-language configuration option instance.
 * @param enabled Whether cross-language attribute setting is allowed. **true** means that cross-language attribute
 *     setting is allowed, and **false** means the opposite. The default value is **false**.
 * @since 15
 */
void OH_ArkUI_CrossLanguageOption_SetAttributeSettingStatus(ArkUI_CrossLanguageOption* option, bool enabled);

/**
 * @brief Checks whether cross-language attribute setting is allowed in the configuration option.
 *
 * @param option Pointer to the cross-language configuration option instance.
 * @return Whether cross-language attribute setting is allowed. **true** means that cross-language attribute setting is
 *     allowed, and **false** means the opposite.
 * @since 15
 */
bool OH_ArkUI_CrossLanguageOption_GetAttributeSettingStatus(ArkUI_CrossLanguageOption* option);

/**
 * @brief Sets the title of a text menu item.
 *
 * @param item Pointer to the **ArkUI_TextMenuItem** object.
 * @param content Pointer to the title of a text menu item. The default value is an empty string.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_SetContent(ArkUI_TextMenuItem* item, const char* content);

/**
 * @brief Obtains the title of a text menu item.
 *
 * @param item Pointer to the **ArkUI_TextMenuItem** object.
 * @param buffer Pointer to the buffer. You can create it and allocate memory to store the title information of the
 *     text menu item.
 * @param bufferSize Buffer size.
 * @param writeLength Pointer to the length of the data actually written to the buffer if
 *     {@link ARKUI_ERROR_CODE_NO_ERROR} is returned.<br>
 *     Pointer to the minimum length required for writing the entire string to the buffer if
 *     {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the buffer size is insufficient.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_GetContent(const ArkUI_TextMenuItem* item, char* buffer, int32_t bufferSize,
    int32_t* writeLength);

/**
 * @brief Sets the icon path of a text menu item.
 *
 * @param item Pointer to the **ArkUI_TextMenuItem** object.
 * @param icon Pointer to the icon path of the text menu item. The default value is an empty string.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_SetIcon(ArkUI_TextMenuItem* item, const char* icon);

/**
 * @brief Obtains the icon path of a text menu item.
 *
 * @param item Pointer to the **ArkUI_TextMenuItem** object.
 * @param buffer Pointer to the buffer. You can create it and allocate memory to store the icon path of the text menu
 *     item.
 * @param bufferSize Buffer size.
 * @param writeLength Pointer to the length of the data actually written to the buffer if
 *     {@link ARKUI_ERROR_CODE_NO_ERROR} is returned.<br>
 *     Pointer to the minimum length required for writing the entire string to the buffer if
 *     {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the buffer size is insufficient.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_GetIcon(const ArkUI_TextMenuItem* item, char* buffer, int32_t bufferSize,
    int32_t* writeLength);

/**
 * @brief Sets the shortcut hint for a text menu item, for example, the shortcut hint for the **Copy** menu item can be
 * set to **Ctrl+C**.
 *
 * @param item Pointer to the **ArkUI_TextMenuItem** object.
 * @param labelInfo Pointer to the shortcut hint of a text menu item. The default value is an empty string.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_SetLabelInfo(ArkUI_TextMenuItem* item, const char* labelInfo);

/**
 * @brief Obtains the shortcut hint for a text menu item, for example, the shortcut hint for the **Copy** menu item is
 * typically **Ctrl+C**.
 *
 * @param item Pointer to the **ArkUI_TextMenuItem** object.
 * @param buffer Pointer to the buffer. You can create it and allocate memory to store the shortcut hint of the text
 *     menu item.
 * @param bufferSize Buffer size.
 * @param writeLength Pointer to the length of the data actually written to the buffer if
 *     {@link ARKUI_ERROR_CODE_NO_ERROR} is returned.<br>
 *     Pointer to the minimum length required for writing the entire string to the buffer if
 *     {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the buffer size is insufficient.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_GetLabelInfo(const ArkUI_TextMenuItem* item, char* buffer, int32_t bufferSize,
    int32_t* writeLength);

/**
 * @brief Sets the ID of a text menu item.
 *
 * @param item Pointer to the **ArkUI_TextMenuItem** object.
 * @param id ID of a text menu item.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_SetId(ArkUI_TextMenuItem* item, int32_t id);

/**
 * @brief Obtains the ID of a text menu item.
 *
 * @param item Pointer to the **ArkUI_TextMenuItem** object.
 * @param id Pointer to the ID of a text menu item.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItem_GetId(const ArkUI_TextMenuItem* item, int32_t* id);

/**
 * @brief Obtains the size of the text menu item array.
 *
 * @param items Pointer to the **ArkUI_TextMenuItemArray** object.
 * @param size Pointer to the size of the text menu item array.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_GetSize(ArkUI_TextMenuItemArray* items, int32_t* size);

/**
 * @brief Obtains the text menu item at a specified index from the text menu item array.
 *
 * @param items Pointer to the **ArkUI_TextMenuItemArray** object.
 * @param index Index position.
 * @param item Double pointer to the **ArkUI_TextMenuItem** object.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_GetItem(ArkUI_TextMenuItemArray* items, int32_t index,
    ArkUI_TextMenuItem** item);

/**
 * @brief Inserts a text menu item at a specified index into the text menu item array.
 *
 * @param items Pointer to the **ArkUI_TextMenuItemArray** object.
 * @param item Pointer to the **ArkUI_TextMenuItem** object.
 * @param index Index position of the text menu item to be inserted.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_Insert(ArkUI_TextMenuItemArray* items, ArkUI_TextMenuItem* item,
    int32_t index);

/**
 * @brief Deletes the text menu item at a specified index from the text menu item array.
 *
 * @param items Pointer to the **ArkUI_TextMenuItemArray** object.
 * @param index Index of the text menu item to be deleted.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_Erase(ArkUI_TextMenuItemArray* items, int32_t index);

/**
 * @brief Clears all text menu items in the text menu item array.
 *
 * @param items Pointer to the **ArkUI_TextMenuItemArray** object.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextMenuItemArray_Clear(ArkUI_TextMenuItemArray* items);

/**
 * @brief Registers the callback for creating text menus.
 *
 * @param editMenuOptions Pointer to the **ArkUI_TextEditMenuOptions** object.
 * @param userData Pointer to the user-defined data.
 * @param cb Callback for creating text menus.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextEditMenuOptions_RegisterOnCreateMenuCallback(
    ArkUI_TextEditMenuOptions* editMenuOptions, void* userData, ArkUI_TextCreateMenuCallback cb);
/**
 * @brief Registers the callback for preparing text menus.
 *
 * @param editMenuOptions Pointer to the **ArkUI_TextEditMenuOptions** object.
 * @param userData Pointer to the user-defined data.
 * @param cb Callback for preparing text menus.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextEditMenuOptions_RegisterOnPrepareMenuCallback(
    ArkUI_TextEditMenuOptions* editMenuOptions, void* userData, ArkUI_TextPrepareMenuCallback cb);

/**
 * @brief Registers the callback for text menu item clicks.
 *
 * @param editMenuOptions Pointer to the **ArkUI_TextEditMenuOptions** object.
 * @param userData Pointer to the user-defined data.
 * @param cb Callback for text menu item clicks.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextEditMenuOptions_RegisterOnMenuItemClickCallback(
    ArkUI_TextEditMenuOptions* editMenuOptions, void* userData, ArkUI_TextMenuItemClickCallback cb);

/**
 * @brief Sets the text recognition type of a custom text selection menu.
 *
 * @param selectionMenuOptions Pointer to the **ArkUI_TextSelectionMenuOptions** object.
 * @param textSpanType Recognition type of a custom text selection menu.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_SetSpanType(ArkUI_TextSelectionMenuOptions* selectionMenuOptions,
    ArkUI_TextSpanType textSpanType);
/**
 * @brief Obtains the text recognition type of a custom text selection menu.
 *
 * @param selectionMenuOptions Pointer to the **ArkUI_TextSelectionMenuOptions** object.
 * @param spanType Pointer to the recognition type of a custom text selection menu.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_GetSpanType(ArkUI_TextSelectionMenuOptions* selectionMenuOptions,
    ArkUI_TextSpanType* spanType);

/**
 * @brief Sets the content node of a custom text selection menu.
 *
 * @param selectionMenuOptions Pointer to the **ArkUI_TextSelectionMenuOptions** object.
 * @param node Content node of the custom text selection menu.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_SetContentNode(ArkUI_TextSelectionMenuOptions* selectionMenuOptions,
    ArkUI_NodeHandle node);
/**
 * @brief Obtains the content node of a custom text selection menu.
 *
 * @param selectionMenuOptions Pointer to the **ArkUI_TextSelectionMenuOptions** object.
 * @param node Pointer to the content node of the custom text selection menu.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_GetContentNode(ArkUI_TextSelectionMenuOptions* selectionMenuOptions,
    ArkUI_NodeHandle* node);

/**
 * @brief Sets the response type of a custom text selection menu.
 *
 * @param selectionMenuOptions Pointer to the **ArkUI_TextSelectionMenuOptions** object.
 * @param responseType Response type of the custom text selection menu.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_SetResponseType(ArkUI_TextSelectionMenuOptions* selectionMenuOptions,
    ArkUI_TextResponseType responseType);
/**
 * @brief Obtains the response type of a custom text selection menu.
 *
 * @param selectionMenuOptions Pointer to the **ArkUI_TextSelectionMenuOptions** object.
 * @param responseType Pointer to the response type of the custom text selection menu.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_GetResponseType(ArkUI_TextSelectionMenuOptions* selectionMenuOptions,
    ArkUI_TextResponseType* responseType);

/**
 * @brief Registers the callback for the event of showing a custom text selection menu.
 *
 * @param selectionMenuOptions Pointer to the **ArkUI_TextSelectionMenuOptions** object.
 * @param userData Pointer to the user-defined data, which can be any value. After the setting, the value is returned
 *     through the callback.
 * @param callback Callback for the event of showing a custom text selection menu.<br>
 *     **start**: start position of the selected text.<br>
 *     **end**: end position of the selected text.<br>
 *     **userData**: user-defined data, which corresponds to the input parameter **userData** of the
 *     **OH_ArkUI_TextSelectionMenuOptions_RegisterOnMenuShowCallback** API.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_RegisterOnMenuShowCallback(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, void* userData,
    void (*callback)(int32_t start, int32_t end, void* userData));
/**
 * @brief Registers the callback for the event of hiding a custom text selection menu.
 *
 * @param selectionMenuOptions Pointer to the **ArkUI_TextSelectionMenuOptions** object.
 * @param userData Pointer to the user-defined data, which can be any value. After the setting, the value is returned
 *     through the callback.
 * @param callback Callback for the event of hiding a custom text selection menu.<br>
 *     **start**: start position of the selected text.<br>
 *     **end**: end position of the selected text.<br>
 *     **userData**: user-defined data, which corresponds to the input parameter **userData** of the
 *     **OH_ArkUI_TextSelectionMenuOptions_RegisterOnMenuHideCallback** API.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TextSelectionMenuOptions_RegisterOnMenuHideCallback(
    ArkUI_TextSelectionMenuOptions* selectionMenuOptions, void* userData,
    void (*callback)(int32_t start, int32_t end, void* userData));

/**
 * @brief Creates a selection option.
 *
 * @return Pointer to the selection option.
 * @since 23
 */
ArkUI_SelectionOptions* OH_ArkUI_SelectionOptions_Create();

/**
 * @brief Releases a selection option object.
 *
 * @param options Pointer to the selection option to be released.
 * @since 23
 */
void OH_ArkUI_SelectionOptions_Dispose(ArkUI_SelectionOptions* options);

/**
 * @brief Sets the menu pop-up policy for selection options.
 *
 * @param options Pointer to the selection option.
 * @param menuPolicy Menu display policy.
 * @since 23
 */
void OH_ArkUI_SelectionOptions_SetMenuPolicy(
    ArkUI_SelectionOptions* options, ArkUI_MenuPolicy menuPolicy);

/**
 * @brief Obtains the menu pop-up policy for selection options.
 *
 * @param options Pointer to the selection option.
 * @return Menu display policy.
 * @since 23
 */
ArkUI_MenuPolicy OH_ArkUI_SelectionOptions_GetMenuPolicy(ArkUI_SelectionOptions* options);

/**
 * @brief Creates a preview style shown when dragging selected text.
 * @return Pointer to the **ArkUI_SelectedDragPreviewStyle** object.
 * @since 23
 */
ArkUI_SelectedDragPreviewStyle* OH_ArkUI_SelectedDragPreviewStyle_Create();

/**
 * @brief Destroys the preview style shown when dragging selected text.
 * @param config Pointer to the **ArkUI_SelectedDragPreviewStyle** object.
 * @since 23
 */
void OH_ArkUI_SelectedDragPreviewStyle_Dispose(ArkUI_SelectedDragPreviewStyle* config);

/**
 * @brief Sets the background color of the preview style shown when dragging selected text.
 * @param config Pointer to the **ArkUI_SelectedDragPreviewStyle** object.
 * @param color Background color of the preview style shown when dragging selected text, in RGBA format.
 * @since 23
 */
void OH_ArkUI_SelectedDragPreviewStyle_SetColor(
    ArkUI_SelectedDragPreviewStyle* config, uint32_t color);

/**
 * @brief Obtains the background color of the preview style shown when dragging selected text.
 * @param config Pointer to the **ArkUI_SelectedDragPreviewStyle** object.
 * @return Background color of the preview style shown when dragging selected text, in RGBA format.
 * @since 23
 */
uint32_t OH_ArkUI_SelectedDragPreviewStyle_GetColor(
    ArkUI_SelectedDragPreviewStyle* config);

/**
 * @brief Sets the decoration type of the decorative line style.
 *
 * @param options Pointer to the {@link OH_ArkUI_DecorationStyleOptions} object.
 * @param type Decoration type, specified using {@link ArkUI_TextDecorationType}.
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
 * @param type Pointer to the decoration type, specified using {@link ArkUI_TextDecorationType}.
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
 * @param style Decorative line style, specified using {@link ArkUI_TextDecorationStyle}.
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
 * @param style Pointer to the decorative line style, specified using {@link ArkUI_TextDecorationStyle}.
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
 * @param types Type of the text entity recognition configuration. The value is an enumerated value of
 *     {@link ArkUI_TextDataDetectorType}.
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
 * @param callback Pointer to the callback when the recognition result is updated. **result** indicates the recognized
 *     text entity content. **length** indicates the end position of the selected text. **userData** indicates the
 *     user-defined data, which corresponds to the input parameter **userData** of the
 *     **OH_ArkUI_TextDataDetectorConfig_RegisterOnDetectResultUpdateCallback** API.
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
 * @param decoration Pointer to the decoration style of the recognized content.
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
 * @param decoration Pointer to the decoration style of the recognized content.
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
 * @brief Sets a styled string for the text component.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextController} object.
 * @param descriptor Pointer to the {@link ArkUI_StyledString_Descriptor} object.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
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
 * @param fontWeight Font weight. The value is an enumerated value of {@link ArkUI_FontWeight}. The default
 *     value is **ARKUI_FONT_WEIGHT_W400**.
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
 * @param fontWeight Pointer to the font weight. The value is an enumerated value of {@link ArkUI_FontWeight}.
 *     The default value is **ARKUI_FONT_WEIGHT_W400**.
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
 * @param isEditing Pointer to the **isEditing** parameter indicating whether the text editor is in the editing
 *     state. **true** means that the text editor is in the editing state, and **false** means the opposite.
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
 * @param fontWeight Font weight. The value is an enumerated value of {@link ArkUI_FontWeight}. The default
 *     value is **ARKUI_FONT_WEIGHT_W400**.
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
 * @param fontWeight Pointer to the font weight. The value is an enumerated value of {@link ArkUI_FontWeight}.
 *     The default value is **ARKUI_FONT_WEIGHT_W400**.
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
 * @param halfLeading Pointer to the **halfLeading** parameter indicating whether half leading is enabled.
 *     <br>**true** means half leading is enabled, and **false** means the opposite. The default value is **false**.
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
 * @brief Sets the text background border width of the text style.
 *
 * @param style [in] Pointer to the text style of the **TextEditor** component.
 * @param borderWidth [in] Text background border width, in vp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetTextBackgroundBorderWidth(
    OH_ArkUI_TextEditorTextStyle* style, float borderWidth);

/**
 * @brief Obtains the text background border width of the text style.
 *
 * @param style [in] Pointer to the text style of the **TextEditor** component.
 * @param borderWidth [out] Pointer to the text background border width, in vp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetTextBackgroundBorderWidth(
    OH_ArkUI_TextEditorTextStyle* style, float* borderWidth);

/**
 * @brief Sets the text background border color of the text style.
 *
 * @param style [in] Pointer to the text style of the **TextEditor** component.
 * @param borderColor [in] Text background border color, in 0xARGB format.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_SetTextBackgroundBorderColor(
    OH_ArkUI_TextEditorTextStyle* style, uint32_t borderColor);

/**
 * @brief Obtains the text background border color of the text style.
 *
 * @param style [in] Pointer to the text style of the **TextEditor** component.
 * @param borderColor [out] Pointer to the text background border color, in 0xARGB format.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorTextStyle_GetTextBackgroundBorderColor(
    OH_ArkUI_TextEditorTextStyle* style, uint32_t* borderColor);

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
 * @param callback Pointer to the callback when the menu is displayed. **start** indicates the start offset of the
 *     selected content. **end** indicates the end offset of the selected content. **callbackUserData** indicates the
 *     user data.
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
 * @param callback Pointer to the callback when the menu is hidden. **start** indicates the start offset of the
 *     selected content. **end** indicates the end offset of the selected content. **callbackUserData** indicates the
 *     user data.
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
 * @param callback Pointer to the callback when the menu appears. **start** indicates the start offset of the
 *     selected content. **end** indicates the end offset of the selected content. **callbackUserData** indicates the
 *     user data.
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
 * @param callback Pointer to the callback when the menu disappears. **callbackUserData** indicates the user data.
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
 * @brief Scrolls the content within the range from the specified start index to the end index to the visible
 * area using the styled string controller.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @param start Start index.<br>
 *     The start index must be less than or equal to the end index. Otherwise, the API call is invalid. The value
 *     range is [0, Total length of the content in the **TextEditor** component]. If the start index is less than 0,
 *     0 is used. If the start index is greater than the total length, the total length is used.
 * @param end End index.<br>
 *     The end index must be greater than or equal to the start index. Otherwise, the API call is invalid. The value
 *     range is [0, Total length of the content in the **TextEditor** component]. If the end index is less than 0,
 *     0 is used. If the end index is greater than the total length, the total length is used.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorStyledStringController_ScrollToVisible(
    const OH_ArkUI_TextEditorStyledStringController* controller, int32_t start, int32_t end);

/**
 * @brief Sets the background style. This API takes effect only when the type of the selected item indicator
 * is {@link ARKUI_PICKER_INDICATOR_BACKGROUND}.
 *
 * @param style Pointer to the {@link ArkUI_PickerIndicatorStyle} instance.
 * @param background Pointer to the background.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_PickerIndicatorStyle_ConfigureBackground(ArkUI_PickerIndicatorStyle* style,
    ArkUI_PickerIndicatorBackground* background);

/**
 * @brief Sets the divider style. This API takes effect only when the type of the selected item indicator
 * is {@link ARKUI_PICKER_INDICATOR_DIVIDER}.
 *
 * @param style Pointer to the {@link ArkUI_PickerIndicatorStyle} instance.
 * @param divider Pointer to the divider style.
 * @return Return result.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_PickerIndicatorStyle_ConfigureDivider(ArkUI_PickerIndicatorStyle* style,
    ArkUI_PickerIndicatorDivider* divider);

/**
 * @brief Enumerates the node tree operation states of cross-language configuration options.
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * Undefined, which is the initial value of the node tree operation state. Nodes in this state do not support
     * cross-language node tree operations.
     * @since 26.0.0
     */
    OH_ARKUI_TREE_OPERATING_STATUS_UNDEFINED = 0,
    /**
     * Enabled, which indicates that when the configuration option is applied to a node, the node tree operation state
     * of the node will be enabled.
     *
     * @since 26.0.0
     */
    OH_ARKUI_TREE_OPERATING_STATUS_ENABLE = 1,
    /**
     * Disabled, which indicates that when the configuration option is applied to a node, the node tree operation state
     * of the node will be disabled.
     *
     * @since 26.0.0
     */
    OH_ARKUI_TREE_OPERATING_STATUS_DISABLE = 2,
} OH_ArkUI_CrossLanguageOperatingStatus;

/**
 * @brief Sets the node tree operation state of a cross-language configuration option.
 *
 * @param option Pointer to the cross-language configuration option instance.
 * @param status Node tree operation state to be set. Default value: **OH_ARKUI_TREE_OPERATING_STATUS_UNDEFINED**.
 * @since 26.0.0
 */
void OH_ArkUI_CrossLanguageOption_SetTreeOperatingStatus(ArkUI_CrossLanguageOption* option,
    OH_ArkUI_CrossLanguageOperatingStatus status);

/**
 * @brief Obtains the node tree operation state of a cross-language configuration option.
 *
 * @param option Pointer to the cross-language configuration option instance.
 * @return Node tree operation state of a cross-language configuration option.
 * @since 26.0.0
 */
OH_ArkUI_CrossLanguageOperatingStatus OH_ArkUI_CrossLanguageOption_GetTreeOperatingStatus(
    ArkUI_CrossLanguageOption* option);

/**
 * @brief Defines linear gradient options, which are used to describe the linear color gradient configuration of UI
 * components. You can set the gradient direction, angle, and color to implement flexible linear gradient effects,
 * improving the visual presentation capability of the UI. This is applicable to scenarios where a linear gradient
 * style needs to be applied to components.
 *
 * @since 26.0.0
 */
typedef struct OH_ArkUI_LinearGradientOptions OH_ArkUI_LinearGradientOptions;

/**
 * @brief Defines radial gradient options, which are applicable to scenarios where a radial gradient effect needs to
 * be implemented in UI components. This helps you enrich the visual hierarchy of the UI.
 *
 * @since 26.0.0
 */
typedef struct OH_ArkUI_RadialGradientOptions OH_ArkUI_RadialGradientOptions;

/**
 * @brief Creates an object for linear gradient effect options.
 *
 * @return Pointer to the {@link OH_ArkUI_LinearGradientOptions} object.
 * @since 26.0.0
 */
OH_ArkUI_LinearGradientOptions* OH_ArkUI_LinearGradientOptions_Create();

/**
 * @brief Destroys the object for linear gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_LinearGradientOptions} object.
 * @since 26.0.0
 */
void OH_ArkUI_LinearGradientOptions_Destroy(OH_ArkUI_LinearGradientOptions* options);

/**
 * @brief Sets the angle in linear gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_LinearGradientOptions} object.
 * @param angle Angle in linear gradient effect options.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_SetAngle(OH_ArkUI_LinearGradientOptions* options, float angle);

/**
 * @brief Obtains the angle in linear gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_LinearGradientOptions} object.
 * @param angle Pointer to the angle in linear gradient effect options.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_GetAngle(const OH_ArkUI_LinearGradientOptions* options, float* angle);

/**
 * @brief Sets the direction in linear gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_LinearGradientOptions} object.
 * @param direction Direction in linear gradient effect options.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_SetDirection(OH_ArkUI_LinearGradientOptions* options,
    ArkUI_LinearGradientDirection direction);

/**
 * @brief Obtains the direction in linear gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_LinearGradientOptions} object.
 * @param direction Pointer to the direction in linear gradient effect options.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_GetDirection(const OH_ArkUI_LinearGradientOptions* options,
    ArkUI_LinearGradientDirection* direction);

/**
 * @brief Sets whether the color is repeated in linear gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_LinearGradientOptions} object.
 * @param repeating Whether the color is repeated in linear gradient options. The value **false** indicates that the
 *     color is not repeated, and the value **true** indicates that the color is repeated. The default value is
 *     **false**.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_SetRepeating(OH_ArkUI_LinearGradientOptions* options, bool repeating);

/**
 * @brief Obtains whether the color is repeated in linear gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_LinearGradientOptions} object.
 * @param repeating Pointer to the **repeating** parameter indicating whether the color is repeated in linear gradient
 *     effect options.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_GetRepeating(
    const OH_ArkUI_LinearGradientOptions* options, bool* repeating);

/**
 * @brief Sets the color stop in linear gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_LinearGradientOptions} object.
 * @param colors Pointer to the color array.
 * @param stops Pointer to the color stop array.
 * @param colorsAndStopsSize Number of elements in the color and color stop arrays. The number of elements in the
 *     color array must be the same as that in the color stop array.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_SetColorStop(
    OH_ArkUI_LinearGradientOptions* options, const uint32_t* colors, const float* stops, int32_t colorsAndStopsSize);

/**
 * @brief Obtains the color stop in linear gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_LinearGradientOptions} object.
 * @param colors Pointer to the color array.
 * @param stops Pointer to the color stop array.
 * @param colorsAndStopsSize Number of elements in the color and color stop arrays. The number of elements in the
 *     color array must be the same as that in the color stop array.
 * @param writeLength Pointer to the number of colors and color stops that are actually written.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_LinearGradientOptions_GetColorStop(
    const OH_ArkUI_LinearGradientOptions* options, uint32_t* colors, float* stops, int32_t colorsAndStopsSize,
    int32_t* writeLength);

/**
 * @brief Creates an object for radial gradient effect options.
 *
 * @return Pointer to the {@link OH_ArkUI_RadialGradientOptions} object.
 * @since 26.0.0
 */
OH_ArkUI_RadialGradientOptions* OH_ArkUI_RadialGradientOptions_Create();

/**
 * @brief Destroys the object for radial gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_RadialGradientOptions} object.
 * @since 26.0.0
 */
void OH_ArkUI_RadialGradientOptions_Destroy(OH_ArkUI_RadialGradientOptions* options);

/**
 * @brief Sets the X coordinate of the center point in radial gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_RadialGradientOptions} object.
 * @param centerX X coordinate of the center point in radial gradient effect options.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_SetCenterX(OH_ArkUI_RadialGradientOptions* options, float centerX);

/**
 * @brief Obtains the X coordinate of the center point in radial gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_RadialGradientOptions} object.
 * @param centerX Pointer to the X coordinate of the center point in radial gradient effect options.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_GetCenterX(
    const OH_ArkUI_RadialGradientOptions* options, float* centerX);

/**
 * @brief Sets the Y coordinate of the center point in radial gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_RadialGradientOptions} object.
 * @param centerY Y coordinate of the center point in radial gradient effect options.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_SetCenterY(OH_ArkUI_RadialGradientOptions* options, float centerY);

/**
 * @brief Obtains the Y coordinate of the center point in radial gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_RadialGradientOptions} object.
 * @param centerY Pointer to the Y coordinate of the center point in radial gradient effect options.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_GetCenterY(
    const OH_ArkUI_RadialGradientOptions* options, float* centerY);

/**
 * @brief Sets the radius in radial gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_RadialGradientOptions} object.
 * @param radius Radius in radial gradient effect options.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_SetRadius(OH_ArkUI_RadialGradientOptions* options, float radius);

/**
 * @brief Obtains the radius in radial gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_RadialGradientOptions} object.
 * @param radius Pointer to the radius in radial gradient effect options.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_GetRadius(
    const OH_ArkUI_RadialGradientOptions* options, float* radius);

/**
 * @brief Sets whether the color is repeated in radial gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_RadialGradientOptions} object.
 * @param repeating Whether the color is repeated in radial gradient options. The value **false** indicates that the
 *     color is not repeated, and the value **true** indicates that the color is repeated. The default value is
 *     **false**.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_SetRepeating(OH_ArkUI_RadialGradientOptions* options, bool repeating);

/**
 * @brief Obtains whether the color is repeated in radial gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_RadialGradientOptions} object.
 * @param repeating Pointer to the **repeating** parameter indicating whether the color is repeated in radial gradient
 *     effect options.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_GetRepeating(
    const OH_ArkUI_RadialGradientOptions* options, bool* repeating);

/**
 * @brief Sets the color stop in radial gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_RadialGradientOptions} object.
 * @param colors Pointer to the color array.
 * @param stops Pointer to the color stop array.
 * @param colorsAndStopsSize Number of elements in the color and color stop arrays. The number of elements in the
 *     color array must be the same as that in the color stop array.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_SetColorStop(
    OH_ArkUI_RadialGradientOptions* options, const uint32_t* colors, const float* stops, int32_t colorsAndStopsSize);

/**
 * @brief Obtains the color stop in radial gradient effect options.
 *
 * @param options Pointer to the {@link OH_ArkUI_RadialGradientOptions} object.
 * @param colors Pointer to the buffer of the color array.
 * @param stops Pointer to the color stop array.
 * @param colorsAndStopsSize Number of elements in the color and color stop arrays. The number of elements in the
 *     color array must be the same as that in the color stop array.
 * @param writeLength Pointer to the number of color stops that are actually written.
 * @return Result code.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.<br>
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_RadialGradientOptions_GetColorStop(
    const OH_ArkUI_RadialGradientOptions* options, uint32_t* colors, float* stops, int32_t colorsAndStopsSize,
    int32_t* writeLength);

/**
 * @brief Enumerates the child node mounting policy types.
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * If a RenderNode needs to be mounted as a child node, this RenderNode must be the only child node.
     *
     * @since 26.0.0
     */
    OH_ARKUI_NODE_MOUNT_POLICY_SINGLE_IF_RENDER_NODE = 0,
    /**
     * Multiple typeNodes and RenderNodes can be mounted at the same time.
     *
     * @since 26.0.0
     */
    OH_ARKUI_NODE_MOUNT_POLICY_MIXED = 1,
} OH_ArkUI_NodeMountPolicy;

/**
 * @brief Enumerates arc directions.
 *
 * @since 26.0.1
 */
typedef enum {
    /**
     * 3 o'clock direction.
     *
     * @since 26.0.1
     */
    OH_ARKUI_ARCDIRECTION_THREE_CLOCK_DIRECTION = 0,
    /**
     * 6 o'clock direction.
     *
     * @since 26.0.1
     */
    OH_ARKUI_ARCDIRECTION_SIX_CLOCK_DIRECTION = 1,
    /**
     * 9 o'clock direction.
     *
     * @since 26.0.1
     */
    OH_ARKUI_ARCDIRECTION_NINE_CLOCK_DIRECTION = 2
} OH_ArkUI_ArcDirection;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_TYPE_H
/** @} */
