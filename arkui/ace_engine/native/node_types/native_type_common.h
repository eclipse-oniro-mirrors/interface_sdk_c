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
 * @file native_type_common.h
 *
 * @brief Defines the common property and method types for the native module.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_TYPE_COMMON_H
#define ARKUI_NATIVE_TYPE_COMMON_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Enumerates the hit test modes.
*
* @since 12
*/
typedef enum {
    /**
* Both the node and its child node respond to the hit test of a touch event, but its sibling node is blocked from
* the hit test. The node itself and its child nodes respond to the hit test, but block the hit test of sibling
* nodes. It does not affect the hit test of ancestor nodes.
*/
    ARKUI_HIT_TEST_MODE_DEFAULT = 0,
    /**
* The node itself responds to the hit test and blocks the hit test of child nodes, sibling nodes, and ancestor
* nodes.
*/
    ARKUI_HIT_TEST_MODE_BLOCK,
    /**
* Both the node itself and its child nodes respond to the hit test and do not block the hit test of sibling nodes
* and ancestor nodes.
*/
    ARKUI_HIT_TEST_MODE_TRANSPARENT,
    /**
* The node itself does not respond to the hit test and does not block the hit test of child nodes, sibling nodes,
* and ancestor nodes.
*/
    ARKUI_HIT_TEST_MODE_NONE,
    /**
* The node itself and its child nodes respond to the hit test, preventing all sibling nodes and parent nodes with
* lower priority from participating in the hit test.
* @since 20
*/
    ARKUI_HIT_TEST_MODE_BLOCK_HIERARCHY,
    /**
* The node itself does not respond to the hit test, and all its descendants (children, grandchildren, and more)
* also do not respond to the hit test. It does not affect the hit test of ancestor nodes.
* @since 20
*/
    ARKUI_HIT_TEST_MODE_BLOCK_DESCENDANTS
} ArkUI_HitTestMode;

/**
* @brief Enumerates the visibility values.
*
* @since 12
*/
typedef enum {
    /** The component is visible. */
    ARKUI_VISIBILITY_VISIBLE = 0,
    /** The component is hidden, and a placeholder is used for it in the layout. */
    ARKUI_VISIBILITY_HIDDEN,
    /** The component is hidden. It is not involved in the layout, and no placeholder is used for it. */
    ARKUI_VISIBILITY_NONE
} ArkUI_Visibility;

/**
* @brief Enumerates the hover effects when a component is hovered over.
*
* @since 23
*/
typedef enum {
    /** Default effect. */
    ARKUI_HOVER_EFFECT_AUTO = 0,
    /** Zoom effect. */
    ARKUI_HOVER_EFFECT_SCALE,
    /** Highlight effect. */
    ARKUI_HOVER_EFFECT_HIGHLIGHT,
    /** No effect. */
    ARKUI_HOVER_EFFECT_NONE
} ArkUI_HoverEffect;

/**
* @brief Enumerates the priority levels for focus management within the application. These levels determine the
* sequence in which UI components receive focus during user interaction.
*
* @since 23
*/
typedef enum {
    /** Default priority. */
    ARKUI_FOCUS_PRIORITY_AUTO = 0,
    /** Priority that indicates the component is prioritized in the container. */
    ARKUI_FOCUS_PRIORITY_PRIOR = 2000,
    /** Priority of a previously focused node in the container. */
    ARKUI_FOCUS_PRIORITY_PREVIOUS = 3000
} ArkUI_FocusPriority;

/**
* @brief Enumerates the UI states of a component, used for handling state-specific styles.
*
* @since 20
*/
typedef enum {
    /** Normal state. */
    UI_STATE_NORMAL = 0,
    /** Pressed state. */
    UI_STATE_PRESSED = 1 << 0,
    /** Focused state. */
    UI_STATE_FOCUSED = 1 << 1,
    /** Disabled state. */
    UI_STATE_DISABLED = 1 << 2,
    /**
* Selected state. This state is supported only by specific component types: **Checkbox**, **Radio**, **Toggle**, **
* List**, **Grid**, and **MenuItem**.
*/
    UI_STATE_SELECTED = 1 << 3,
    /**
* The hovered state.
* @since 26.0.0
*/
    UI_STATE_HOVERED = 1 << 4
} ArkUI_UIState;

/**
* @brief Enumerates the focus movement directions.
*
* @since 18
*/
typedef enum {
    /** Move focus forward. */
    ARKUI_FOCUS_MOVE_FORWARD = 0,
    /** Move focus backward. */
    ARKUI_FOCUS_MOVE_BACKWARD,
    /** Move focus up. */
    ARKUI_FOCUS_MOVE_UP,
    /** Move focus down. */
    ARKUI_FOCUS_MOVE_DOWN,
    /** Move focus left. */
    ARKUI_FOCUS_MOVE_LEFT,
    /** Move focus right. */
    ARKUI_FOCUS_MOVE_RIGHT
} ArkUI_FocusMove;

/**
* @brief Enumerates the input tool types supported for response region configuration.
*
* @since 23
*/
typedef enum {
    /** All. */
    ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_ALL = 0,
    /** Finger. */
    ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_FINGER = 1,
    /** Stylus. */
    ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_PEN = 2,
    /** Mouse. */
    ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_MOUSE = 3
} ArkUI_ResponseRegionSupportedTool;

/**
* @brief Defines snapshot options.
*
* @since 15
*/
typedef struct ArkUI_SnapshotOptions ArkUI_SnapshotOptions;

/**
* @brief Creates a snapshot option object, which must be released using {@link OH_ArkUI_DestroySnapshotOptions()} when
* no longer in use.
*
* @return Pointer to the created snapshot option object. If a null pointer is returned, creation failed, possibly due
*     to insufficient memory.
* @since 15
*/
ArkUI_SnapshotOptions* OH_ArkUI_CreateSnapshotOptions();

/**
* @brief Destroys a snapshot option object.
*
* @param snapshotOptions Pointer to the screenshot option.
* @since 15
*/
void OH_ArkUI_DestroySnapshotOptions(ArkUI_SnapshotOptions* snapshotOptions);

/**
* @brief Sets the scale property in the snapshot options.
*
* @param snapshotOptions Pointer to the screenshot option.
* @param scale Scale factor.
* @return Result code.
*     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
*     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
*     <br>A possible cause is that mandatory parameters are left unspecified.
* @since 15
*/
int32_t OH_ArkUI_SnapshotOptions_SetScale(ArkUI_SnapshotOptions* snapshotOptions, float scale);

/**
* @brief Sets the color space in the screenshot options.
*
* @param snapshotOptions Pointer to the screenshot option.
* @param colorSpace Color space used for screenshot.
*     <br>If the target component's color space is known, specify it through **colorSpace** and set **isAuto** to **
*     false** to achieve optimal snapshot quality.
*     <br>The supported values are as follows: **3** (RGB color gamut of type Display P3), **4** (RGB color gamut of
*     type sRGB), and **27** (RGB color gamut of type BT.2020).
*     <br>Default value: **4**
*     <br>This parameter takes effect only when **isAuto** is set to **false**.
* @param isAuto Whether the system automatically determines the color space to be used.
*     <br>**true**: The system automatically determines the color space to be used. If the color space used by the
*     component is uncertain, you are advised to set **isAuto** to **true** so that the system can automatically
*     determine the color space to be used.
*     <br>**false**: The color space type set through the **colorSpace** field is used for screenshot.
*     <br>Default value: **false**.
* @return Result code.
*     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
*     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
* @since 23
*/
int32_t OH_ArkUI_SnapshotOptions_SetColorMode(ArkUI_SnapshotOptions* snapshotOptions, int32_t colorSpace, bool isAuto);

/**
* @brief Sets the dynamic range mode in the screenshot options.
*
* @param snapshotOptions Pointer to the screenshot option.
* @param dynamicRangeMode Dynamic range mode used for screenshot.
*     <br>If the dynamic range mode used for screenshot is known, you can specify the dynamic range mode using the **
*     dynamicRangeMode** field and set **isAuto** to **false** to achieve the expected snapshot effect.
*     <br>The value can be one of the enumerated values of {@link ArkUI_DynamicRangeMode}.
*     <br>Default value: **ARKUI_DYNAMIC_RANGE_MODE_STANDARD**
*     <br>This parameter takes effect only when **isAuto** is set to **false**.
* @param isAuto Whether the system automatically determines the dynamic range mode to be used.
*     <br>**true**: whether the system automatically determines the dynamic range mode to be used. If the dynamic
*     range mode used by the component is uncertain, you are advised to set **isAuto** to **true** so that the system
*     can automatically determine the dynamic range mode to be used.
*     <br>**false**: The dynamic range mode set by the **dynamicRangeMode** field is used for screenshot.
*     <br>Default value: **false**.
* @return Result code.
*     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
*     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
* @since 23
*/
int32_t OH_ArkUI_SnapshotOptions_SetDynamicRangeMode(
    ArkUI_SnapshotOptions* snapshotOptions, int32_t dynamicRangeMode, bool isAuto);

/**
* @brief Defines the parameters for visible area change events.
*
* @since 17
*/
typedef struct ArkUI_VisibleAreaEventOptions ArkUI_VisibleAreaEventOptions;

/**
* @brief Creates an instance of the parameters for visible area change events.
*
* @return Pointer to the instance of the parameters for visible area change events.
* @since 17
*/
ArkUI_VisibleAreaEventOptions* OH_ArkUI_VisibleAreaEventOptions_Create();

/**
* @brief Disposes of the instance of the parameters for visible area change events.
*
* @param option Pointer to the instance of visible area change event parameters to be destroyed.
* @since 17
*/
void OH_ArkUI_VisibleAreaEventOptions_Dispose(ArkUI_VisibleAreaEventOptions* option);

/**
* @brief Sets the threshold ratios for visible area changes.
*
* @param option Pointer to the instance of visible area change event parameters.
* @param value Pointer to the array of threshold ratios. Each element represents a ratio of the component's visible
*     area (that is, the area of the component that is visible on screen; only the area within the parent component is
*     counted) to the component's total area. The value range of the threshold is [0.0, 1.0]. If the threshold set
*     exceeds this range, the value **0.0** or **1.0** will be used.
* @param size Size of the array of threshold ratios.
* @return Result code.
*     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
*     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
*     <br>A possible cause is that mandatory parameters are left unspecified.
* @since 17
*/
int32_t OH_ArkUI_VisibleAreaEventOptions_SetRatios(ArkUI_VisibleAreaEventOptions* option, float* value, int32_t size);

/**
* @brief Sets the expected update interval for visible area changes.
*
* @param option Pointer to the instance of visible area change event parameters.
* @param value Expected update interval, in ms.  Default value: **1000**.
* @return Result code.
*     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
*     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
*     <br>A possible cause is that mandatory parameters are left unspecified.
* @since 17
*/
int32_t OH_ArkUI_VisibleAreaEventOptions_SetExpectedUpdateInterval(
    ArkUI_VisibleAreaEventOptions *option, int32_t value);

/**
* @brief Sets the visible area calculation mode.
*
* @param option Pointer to the instance of visible area change event parameters.
* @param measureFromViewport Visible area calculation mode.
*     <br>**true**: The calculation takes the parent component's **NODE_CLIP** attribute into account. If the parent
*     component's **NODE_CLIP** attribute is **false**: Child components can render beyond the parent component's
*     bounds, and the out-of-bounds area is counted as part of the visible area. If the parent component's **NODE_CLIP*
*     * attribute is **true**: Child components are clipped to the parent component's bounds, and the out-of-bounds
*     area is treated as invisible. **false**: The area beyond the parent component's bounds is directly treated as
*     invisible, ignoring the parent component's **NODE_CLIP** attribute.
*     <br>Default value: **false**.
* @return Result code.
*     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
*     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
*     <br>A possible cause is that mandatory parameters are left unspecified.
* @since 22
*/
int32_t OH_ArkUI_VisibleAreaEventOptions_SetMeasureFromViewport(
    ArkUI_VisibleAreaEventOptions* option, bool measureFromViewport);

/**
* @brief Obtains the threshold ratios for visible area changes.
*
* @param option Pointer to the instance of visible area change event parameters.
* @param value Pointer to the array of threshold ratios.
* @param size Pointer to the size of the array of threshold ratios.
* @return Result code.
*     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
*     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
*     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the buffer size is insufficient.
*     <br>A possible cause is that mandatory parameters are left unspecified.
* @since 17
*/
int32_t OH_ArkUI_VisibleAreaEventOptions_GetRatios(ArkUI_VisibleAreaEventOptions* option, float* value, int32_t* size);

/**
* @brief Obtains the expected update interval for visible area changes.
*
* @param option Pointer to the instance of visible area change event parameters.
* @return Expected update interval, in ms.  Default value: **1000**.
* @since 17
*/
int32_t OH_ArkUI_VisibleAreaEventOptions_GetExpectedUpdateInterval(ArkUI_VisibleAreaEventOptions* option);

/**
* @brief Obtains the visible area calculation mode.
*
* @param option Pointer to the instance of visible area change event parameters.
* @return Visible area calculation mode.
*     <br>**true**: The calculation takes the parent component's **NODE_CLIP** attribute into account. If the parent
*     component's **NODE_CLIP** attribute is **false**: Child components can render beyond the parent component's
*     bounds, and the out-of-bounds area is counted as part of the visible area. If the parent component's **NODE_CLIP*
*     * attribute is **true**: Child components are clipped to the parent component's bounds, and the out-of-bounds
*     area is treated as invisible. **false**: The area beyond the parent component's bounds is directly treated as
*     invisible, ignoring the parent component's **NODE_CLIP** attribute.
*     <br>Default value: **false**.
* @since 22
*/
bool OH_ArkUI_VisibleAreaEventOptions_GetMeasureFromViewport(ArkUI_VisibleAreaEventOptions* option);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_TYPE_COMMON_H
/** @} */