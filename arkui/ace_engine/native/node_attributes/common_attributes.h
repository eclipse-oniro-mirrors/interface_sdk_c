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
 * @file common_attributes.h
 *
 * @brief Defines the types of common attributes and events of **NativeModule**, used to support the configuration
 * of common component attributes and event handling, making it easier for native developers to manage component
 * behavior in a unified manner.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_COMMON_ATTRIBUTES_H
#define ARKUI_COMMON_ATTRIBUTES_H

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
* Default hit test mode. The node itself and its child nodes respond to the hit test, but block the hit test of
* sibling nodes. It does not affect the hit test of ancestor nodes.
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
* Neither the node itself nor any of its descendant nodes responds to the hit test. It does not affect the hit test
* of ancestor nodes.
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
    /** Scale effect. */
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
* Selected state. This state is supported only by specific component types: **Checkbox**, **Radio**, **Toggle**,
* **List**, **Grid**, and **MenuItem**.
*/
    UI_STATE_SELECTED = 1 << 3,
    /**
* Hovered state.
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
* @brief Enumerates the types of raw input events.
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
 * @brief Defines snapshot options, used to configure the snapshot behavior when taking a snapshot of a
 * component. It applies to scenarios where the snapshot output effect needs to be controlled based on service
 * requirements.
 *
 * To use this struct, first call {@link OH_ArkUI_CreateSnapshotOptions} to create a snapshot options object, and
 * set the snapshot parameters through {@link OH_ArkUI_SnapshotOptions_SetScale},
 * {@link OH_ArkUI_SnapshotOptions_SetColorMode}, and {@link OH_ArkUI_SnapshotOptions_SetDynamicRangeMode}; then
 * pass the object as the **snapshotOptions** parameter to {@link OH_ArkUI_GetNodeSnapshot}. When the object is no
 * longer used, call {@link OH_ArkUI_DestroySnapshotOptions} to release resources.
 *
 * @since 15
 */
typedef struct ArkUI_SnapshotOptions ArkUI_SnapshotOptions;

/**
* @brief Creates a snapshot option object, which must be released using {@link OH_ArkUI_DestroySnapshotOptions()} when
* no longer in use.
*
 * @return Pointer to the created screenshot option object. If the API returns a null pointer, the creation fails,
 *     possibly because the address space is full.
 * @since 15
*/
ArkUI_SnapshotOptions* OH_ArkUI_CreateSnapshotOptions();

/**
 * @brief Destroys the screenshot option object created by {@link OH_ArkUI_CreateSnapshotOptions}.
 *
 * @param snapshotOptions Pointer to the screenshot option object to be destroyed, used to release the screenshot
 *     option object created by {@link OH_ArkUI_CreateSnapshotOptions}.
 * @since 15
 */
void OH_ArkUI_DestroySnapshotOptions(ArkUI_SnapshotOptions* snapshotOptions);

/**
 * @brief Set the scale attribute in screenshot options, which is used to control the scale factor of the generated
 * screenshot.
 *
 * @param snapshotOptions Pointer to the screenshot option object. Before using this parameter, create a valid
 *     screenshot option object through {@link OH_ArkUI_CreateSnapshotOptions} to set the scale attribute of the
 *     screenshot.
 * @param scale Scale factor of the screenshot. The value is a floating-point number greater than 0, and the default
 *     value is **1.0**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Possible causes: The **snapshotOptions** parameter is null, or the **scale** value does not match the API
 *     requirements. To solve this issue, pass a valid screenshot option object pointer and ensure that the value of
 *     **scale** is a floating-point number greater than 0.
 * @since 15
 */
int32_t OH_ArkUI_SnapshotOptions_SetScale(ArkUI_SnapshotOptions* snapshotOptions, float scale);

/**
 * @brief Sets the color space in the screenshot options.
 *
 * @param snapshotOptions Pointer to the screenshot option object. Before using this parameter, call
 *     {@link OH_ArkUI_CreateSnapshotOptions} to create a valid screenshot option object to set the color space of
 *     the screenshot.
 * @param colorSpace Color space used for the screenshot.
 *     <br>If you know the color space used by the component to be captured, you can specify it through the
 *     **colorSpace** parameter and set **isAuto** to **false** to achieve the expected screenshot effect.
 *     <br>The supported values are as follows: **3** (Display P3, suitable for scenarios where Display P3 content
 *     needs to be retained), **4** (SRGB, suitable for common display devices and compatibility-first scenarios),
 *     and **27** (DISPLAY BT2020, suitable for scenarios where the target device supports the BT2020 color gamut).
 *     <br>Default value: **4**
 *     <br>This parameter takes effect only when **isAuto** is set to **false**.
 * @param isAuto Whether the system automatically determines the color space to be used.
 *     <br>**true**: The system automatically determines the color space to be used. If the color space used by the
 *     component is uncertain, you are advised to set **isAuto** to **true** so that the system can automatically
 *     determine the color space to be used.
 *     <br>**false**: The color space type set through the **colorSpace** field is used for screenshot.
 *     <br>Default value: **false**
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Possible causes: The **snapshotOptions** parameter is null, or the **colorSpace** value is not supported.
 *     To solve this issue, pass a valid screenshot option object pointer and ensure that the **colorSpace** value is
 *     a supported color space.
 * @since 23
 */
int32_t OH_ArkUI_SnapshotOptions_SetColorMode(ArkUI_SnapshotOptions* snapshotOptions, int32_t colorSpace, bool isAuto);

/**
 * @brief Sets the dynamic range mode in the screenshot options.
 *
 * @param snapshotOptions Pointer to the screenshot option object. Before using this parameter, create a valid
 *     screenshot option object through {@link OH_ArkUI_CreateSnapshotOptions} to set the dynamic range mode of the
 *     screenshot.
 * @param dynamicRangeMode Dynamic range mode used for the screenshot.
 *     <br>If you know the dynamic range mode used by the screenshot object, you can specify it through the
 *     **dynamicRangeMode** parameter and set **isAuto** to **false** to achieve the expected screenshot effect.
 *     <br>The value can be an enumerated value of {@link ArkUI_DynamicRangeMode}:
 *     **ARKUI_DYNAMIC_RANGE_MODE_HIGH** applies to devices that support HDR display and HDR content,
 *     **ARKUI_DYNAMIC_RANGE_MODE_CONSTRAINT** applies to scenarios that require SDR compatibility, and
 *     **ARKUI_DYNAMIC_RANGE_MODE_STANDARD** applies to common display devices.
 *     <br>Default value: **ARKUI_DYNAMIC_RANGE_MODE_STANDARD**
 *     <br>This parameter takes effect only when **isAuto** is set to **false**.
 * @param isAuto Whether the system automatically determines the dynamic range mode to be used.
 *     <br>**true**: The system automatically determines the dynamic range mode to be used. If the dynamic range
 *     mode used by the component is uncertain, you are advised to set **isAuto** to **true** so that the system can
 *     automatically determine the dynamic range mode to be used.
 *     <br>**false**: The dynamic range mode set by the **dynamicRangeMode** field is used for screenshot.
 *     <br>Default value: **false**
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Possible causes: The **snapshotOptions** parameter is null, or the **dynamicRangeMode** value is not
 *     supported. To solve this issue, pass a valid screenshot option object pointer and ensure that
 *     **dynamicRangeMode** is set to a supported dynamic range mode.
 * @since 23
 */
int32_t OH_ArkUI_SnapshotOptions_SetDynamicRangeMode(
    ArkUI_SnapshotOptions* snapshotOptions, int32_t dynamicRangeMode, bool isAuto);

/**
 * @brief Defines the options for visible area change listening, including the threshold array, expected update
 * interval, and visible area calculation mode. This struct can be used to load or release resources based on the
 * visible ratio of a component, and is suitable for scenarios where you need to listen for visible area changes
 * of a component and trigger updates at specified thresholds.
 *
 * When using this struct, you need to first call {@link OH_ArkUI_VisibleAreaEventOptions_Create} to create an
 * **ArkUI_VisibleAreaEventOptions** parameter object. After the object is created, you can configure the
 * listening behavior through the following APIs:
 *
 * Use {@link OH_ArkUI_VisibleAreaEventOptions_SetRatios} to set a threshold array, which defines the threshold
 * conditions for triggering visible area changes.
 *
 * Use {@link OH_ArkUI_VisibleAreaEventOptions_SetExpectedUpdateInterval} to set an expected update interval,
 * which defines the minimum time interval between two visible area change notifications.
 *
 * Use {@link OH_ArkUI_VisibleAreaEventOptions_SetMeasureFromViewport} to set a calculation mode of a visible
 * area, which defines whether to calculate the visible ratio from the viewport area.
 *
 * To obtain the parameter values that have been set, you can:
 *
 * Use {@link OH_ArkUI_VisibleAreaEventOptions_GetRatios} to obtain the threshold array.
 *
 * Use {@link OH_ArkUI_VisibleAreaEventOptions_GetExpectedUpdateInterval} to obtain the expected update interval.
 *
 * Use {@link OH_ArkUI_VisibleAreaEventOptions_GetMeasureFromViewport} to obtain the visible area calculation
 * mode.
 *
 * When the **ArkUI_VisibleAreaEventOptions** object is no longer needed, call
 * {@link OH_ArkUI_VisibleAreaEventOptions_Dispose} to release resources.
 *
 * @since 17
 */
typedef struct ArkUI_VisibleAreaEventOptions ArkUI_VisibleAreaEventOptions;

/**
 * @brief Creates an instance of the parameters for visible area change events. This API is used in scenarios such
 * as list scrolling exposure statistics, lazy loading of images or videos, and triggering business logic when a
 * component enters or leaves the screen. After successful creation, you must first complete the related parameter
 * configuration such as the visible ratio threshold and update interval through related APIs, and then use the
 * parameter object to register the visible area change listener. The system calculates the component visible
 * ratio based on the configured parameters and triggers the corresponding listener event. After use, call
 * {@link OH_ArkUI_VisibleAreaEventOptions_Dispose} to release the parameter object. After **Dispose** is called,
 * the parameter object must not be used again.
 *
 * @return Pointer to the parameter object of the visible area change listener. If the API returns a null pointer,
 *     the creation fails.
 * @since 17
 */
ArkUI_VisibleAreaEventOptions* OH_ArkUI_VisibleAreaEventOptions_Create();

/**
 * @brief Disposes of the instance of the parameters for visible area change events. The parameter object must be
 * created by {@link OH_ArkUI_VisibleAreaEventOptions_Create}, and must not be used after **Dispose** is called.
 *
 * @param option Pointer to the parameter object to be disposed of.
 * @since 17
 */
void OH_ArkUI_VisibleAreaEventOptions_Dispose(ArkUI_VisibleAreaEventOptions* option);

/**
 * @brief Sets the threshold array used to determine the change in the visible ratio of a component. This API is
 * applicable to scenarios such as exposure statistics, staged loading of components, and controlling media
 * playback based on the visible ratio.
 *
 * @param option Pointer to the instance of visible area change event parameters. Before using this parameter,
 *     create a valid parameter instance through {@link OH_ArkUI_VisibleAreaEventOptions_Create}.
 * @param value Pointer to the threshold array. Each element represents the ratio of the visible area of the
 *     component to the area of the component itself. By default, only the area within the parent component is
 *     calculated. When **measureFromViewport** is set to **true** and **NODE_CLIP** of the parent component is
 *     set to **false**, the part of the component beyond the parent component area is also counted into the
 *     visible area. The value range of each threshold is [0.0, 1.0]: a value close to 0.0 is suitable for
 *     listening to the scenario where the component just enters the visible area, a value close to 0.5 is
 *     suitable for listening to the scenario where most of the component is visible, and a value close to 1.0 is
 *     suitable for listening to the scenario where the component is fully or almost fully visible. Select the
 *     threshold based on the service requirement for the visibility of the component. If the threshold you set
 *     exceeds this range, the actual value **0.0** or **1.0** is used.
 * @param size Number of elements in the threshold array, used to specify the number of thresholds passed by the
 *     **value** parameter. The value must be a non-negative integer and must be consistent with the actual
 *     number of threshold elements passed by the **value** parameter.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Possible causes: The **option** or **value** parameter is null, or the **size** value does not meet the
 *     API requirements. To solve this issue, pass a valid parameter pointer and ensure that the **size** value
 *     is valid.
 * @since 17
 */
int32_t OH_ArkUI_VisibleAreaEventOptions_SetRatios(ArkUI_VisibleAreaEventOptions* option, float* value, int32_t size);

/**
 * @brief Sets the expected update interval. This API is used to control the update frequency of the visible area
 * ratio. A smaller interval is suitable for scenarios that require timely awareness of visible area changes, but
 * increases computational overhead. A larger interval is suitable for scenarios that do not require high
 * real-time performance and need to reduce computational overhead.
 *
 * @param option Pointer to the instance of visible area change event parameters. Before using this parameter,
 *     create a valid parameter instance through {@link OH_ArkUI_VisibleAreaEventOptions_Create}.
 * @param value Expected update interval, in ms. This parameter is used to control the calculation frequency of
 *     the visible area ratio. The value must be a non-negative integer. The default value is 1000 ms, which is
 *     used when this parameter is not set.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Possible causes: The **option** parameter is null or the **value** parameter does not meet the API
 *     requirements. To solve this issue, pass a valid parameter instance and ensure that **value** is valid.
 * @since 17
 */
int32_t OH_ArkUI_VisibleAreaEventOptions_SetExpectedUpdateInterval(
    ArkUI_VisibleAreaEventOptions *option, int32_t value);

/**
 * @brief Sets the visible area calculation mode. In scenarios involving scrolling containers, clipping
 * containers, or allowing child components to extend beyond the parent component display, you can select the
 * calculation mode based on whether the actually visible portion within the viewport needs to be included in
 * exposure and visibility determination.
 *
 * @param option Pointer to the instance of visible area change event parameters. Before using this parameter,
 *     create a valid parameter instance through {@link OH_ArkUI_VisibleAreaEventOptions_Create}.
 * @param measureFromViewport Visible area calculation mode.
 *     <br>When **measureFromViewport** is set to **true**, the system considers the **NODE_CLIP** attribute of
 *     the parent component when calculating the visible area of a component: if **NODE_CLIP** of the parent
 *     component is set to **false**, the area of the component beyond the parent component is also counted into
 *     the visible area; if **NODE_CLIP** of the parent component is set to **true**, the area of the component
 *     beyond the parent component is clipped and not counted into the visible area. When
 *     **measureFromViewport** is set to **false**, the system does not consider the **NODE_CLIP** attribute and
 *     directly treats the part of the component beyond the parent component as the invisible area.
 *     <br>Default value: **false**
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Possible cause: The **option** parameter is null. To solve this issue, pass a valid instance of
 *     visible area change event parameters.
 * @since 22
 */
int32_t OH_ArkUI_VisibleAreaEventOptions_SetMeasureFromViewport(
    ArkUI_VisibleAreaEventOptions* option, bool measureFromViewport);

/**
 * @brief Obtains the threshold ratios for visible area changes.
 *
 * @param option Pointer to the instance of visible area change event parameters. Before using this parameter,
 *     create a valid parameter instance through {@link OH_ArkUI_VisibleAreaEventOptions_Create}.
 * @param value Pointer to the buffer used to receive the threshold array, where each element indicates the ratio
 *     of the visible area of the component to the area of the component itself, with a value range of
 *     [0.0, 1.0]. The array capacity is specified by the **size** parameter.
 * @param size Pointer to the size of the threshold array. Before the call, it is used to pass the capacity of
 *     the buffer specified by **value**. After the call succeeds, it is used to return the actual number of
 *     elements in the threshold array.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the array size is insufficient.
 *     <br>Possible causes: The **option**, **value**, or **size** parameter is null. To solve this issue, pass
 *     a valid parameter pointer and ensure that the buffer specified by **value** has sufficient capacity. If
 *     the capacity is insufficient, **ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR** is returned.
 * @since 17
 */
int32_t OH_ArkUI_VisibleAreaEventOptions_GetRatios(ArkUI_VisibleAreaEventOptions* option, float* value, int32_t* size);

/**
 * @brief Obtains the expected update interval for visible area changes.
 *
 * @param option Pointer to the instance of visible area change event parameters. Before using this parameter,
 *     create a valid parameter instance through {@link OH_ArkUI_VisibleAreaEventOptions_Create}.
 * @return Expected update interval, in ms. Default value: 1000 ms.
 * @since 17
 */
int32_t OH_ArkUI_VisibleAreaEventOptions_GetExpectedUpdateInterval(ArkUI_VisibleAreaEventOptions* option);

/**
 * @brief Obtains the visible area calculation mode.
 *
 * @param option Pointer to the instance of visible area change event parameters. Before using this parameter,
 *     create a valid parameter instance through {@link OH_ArkUI_VisibleAreaEventOptions_Create}.
 * @return Visible area calculation mode.
 *     <br>**true**: The calculation takes the parent component's **NODE_CLIP** attribute into account. If the parent
 *     component's **NODE_CLIP** attribute is **false**: Child components can render beyond the parent component's
 *     bounds, and the out-of-bounds area is counted as part of the visible area. If the parent component's
 *     **NODE_CLIP** attribute is **true**: Child components are clipped to the parent component's bounds, and the
 *     out-of-bounds area is treated as invisible. **false**: The area beyond the parent component's bounds is
 *     directly treated as invisible, ignoring the parent component's **NODE_CLIP** attribute.
 *     <br>Default value: **false**
 * @since 22
 */
bool OH_ArkUI_VisibleAreaEventOptions_GetMeasureFromViewport(ArkUI_VisibleAreaEventOptions* option);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_COMMON_ATTRIBUTES_H
/** @} */