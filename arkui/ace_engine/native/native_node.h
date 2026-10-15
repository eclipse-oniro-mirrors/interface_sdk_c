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
 * @file native_node.h
 *
 * @brief Provides type definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_H
#define ARKUI_NATIVE_NODE_H

#include "common_type.h"
#include "native_type.h"
#include "ui_input_event.h"

#include "node_attributes/custom_attributes.h"

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Define components max function size.
 *
 * @since 12
 */
#define MAX_NODE_SCOPE_NUM 1000

/**
 * @brief Enumerates the component types that can be created by ArkUI on the native side.
 *
 * @since 12
 */
typedef enum {
    /** Custom node. */
    ARKUI_NODE_CUSTOM = 0,
    /** Text. */
    ARKUI_NODE_TEXT = 1,
    /** Text span. */
    ARKUI_NODE_SPAN = 2,
    /** Image span. */
    ARKUI_NODE_IMAGE_SPAN = 3,
    /** Image. */
    ARKUI_NODE_IMAGE = 4,
    /** Toggle. */
    ARKUI_NODE_TOGGLE = 5,
    /** Loading icon. */
    ARKUI_NODE_LOADING_PROGRESS = 6,
    /** Single-line text input. */
    ARKUI_NODE_TEXT_INPUT = 7,
    /** Multi-line text input. */
    ARKUI_NODE_TEXT_AREA = 8,
    /** Icon. */
    ARKUI_NODE_BUTTON = 9,
    /** Progress indicator. */
    ARKUI_NODE_PROGRESS = 10,
    /** Check box. */
    ARKUI_NODE_CHECKBOX = 11,
    /** XComponent of the SURFACE type. */
    ARKUI_NODE_XCOMPONENT = 12,
    /** Date picker. */
    ARKUI_NODE_DATE_PICKER = 13,
    /** Time picker. */
    ARKUI_NODE_TIME_PICKER = 14,
    /** Text picker. */
    ARKUI_NODE_TEXT_PICKER = 15,
    /** Calendar picker. */
    ARKUI_NODE_CALENDAR_PICKER = 16,
    /** Slider. */
    ARKUI_NODE_SLIDER = 17,
    /** Radio button. */
    ARKUI_NODE_RADIO = 18,
    /** Frame animation component. */
    ARKUI_NODE_IMAGE_ANIMATOR = 19,
    /** XComponent of the TEXTURE type.
     *  @since 18
     */
    ARKUI_NODE_XCOMPONENT_TEXTURE,
    /** Check box group.
     *  @since 15
     */
    ARKUI_NODE_CHECKBOX_GROUP = 21,
    /**
     * Text editor.
     * @since 24
     */
    ARKUI_NODE_TEXT_EDITOR = 22,
    /**
     * Arc alphabet index component.
     * @since 26.0.1
     */
    ARKUI_NODE_ARC_ALPHABET_INDEXER = 23,
    /** Stack container. */
    ARKUI_NODE_STACK = MAX_NODE_SCOPE_NUM,
    /** Swiper. */
    ARKUI_NODE_SWIPER,
    /** Scrollable container. */
    ARKUI_NODE_SCROLL,
    /** List. */
    ARKUI_NODE_LIST,
    /** List item. */
    ARKUI_NODE_LIST_ITEM,
    /** List item group. */
    ARKUI_NODE_LIST_ITEM_GROUP,
    /** Column container. */
    ARKUI_NODE_COLUMN,
    /** Row container. */
    ARKUI_NODE_ROW,
    /** Flex container. */
    ARKUI_NODE_FLEX,
    /** Refresh component. */
    ARKUI_NODE_REFRESH,
    /** Water flow container. */
    ARKUI_NODE_WATER_FLOW,
    /** Water flow item. */
    ARKUI_NODE_FLOW_ITEM,
    /** Relative layout component. */
    ARKUI_NODE_RELATIVE_CONTAINER,
    /** Grid. */
    ARKUI_NODE_GRID,
    /** Grid item. */
    ARKUI_NODE_GRID_ITEM,
    /**
     * Custom span. Common attributes cannot be set or obtained. You can use
     * {@link OH_ArkUI_NodeCustomEvent_GetCustomSpanMeasureInfo},
     * {@link OH_ArkUI_NodeCustomEvent_SetCustomSpanMetrics}, and
     * {@link OH_ArkUI_NodeCustomEvent_GetCustomSpanDrawInfo} to obtain and set the node information of components of
     * this type. For details about the usage, see text_capi_sample.
     */
    ARKUI_NODE_CUSTOM_SPAN,
    /**
     * In-application embedded component.
     * @since 20
     */
    ARKUI_NODE_EMBEDDED_COMPONENT,
    /**
     * Undefined component type. It specifies all component types in the color inversion API.
     * @since 20
     */
    ARKUI_NODE_UNDEFINED,
    /**
     * **Picker** component, which is used to implement user selection operations.
     * @since 23
     */
    ARKUI_NODE_PICKER = 1018,
    /**
     * Arc list.
     * @since 26.0.0
     */
    ARKUI_NODE_ARC_LIST = 1019,
    /**
     * Arc list item.
     * @since 26.0.0
     */
    ARKUI_NODE_ARC_LIST_ITEM = 1020,
    /**
     * Arc scrollbar.
     * @since 26.0.0
     */
    ARKUI_NODE_ARC_SCROLL_BAR = 1021,
    /**
     * Arc swipe container.
     * @since 26.0.1
     */
    ARKUI_NODE_ARC_SWIPER = 1022,
} ArkUI_NodeType;

/**
 * @brief Enumerates the attribute types that can be set by ArkUI on the native side.
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief Width attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Width, in vp. Value range: [0, +∞). When an invalid value is set, the default value is used
     * for display or the component size is abnormal.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Width, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_WIDTH = 0,
    /**
     * @brief Height attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Height, in vp. Value range: [0, +∞). When an invalid value is set, the default value is
     * displayed or the component size is abnormal. </li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Height, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_HEIGHT,
    /**
     * @brief Background color attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format. The value range is from 0x00000000 to 0xFFFFFFFF. For
     * example, `0xFFFF0000` indicates red.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format. For example, **0xFFFF0000** indicates red.</li>
     * </ul>
     *
     * @ingroup Background Display
     *
     */
    NODE_BACKGROUND_COLOR,
    /**
     * @brief Background image attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: image address. In API version 22 and earlier versions, the value can be a network image resource
     * address, local image resource address, Base64 string, or {@link PixelMap} resource, but cannot be the address
     * of an animated image such as an {@link SVG}, GIF, or WebP image. In API version 23 and later versions,
     * animated images of the WebP and GIF types are supported. Only the first frame of the animated image is
     * displayed. Other types of animated images are not supported.</li>
     * <li>.value[0]?.i32: whether the image is repeated. This parameter is optional. The parameter type is
     * {@link ArkUI_ImageRepeat}. The default value is **ARKUI_IMAGE_REPEAT_NONE**.</li>
     * <li>.object: **PixelMap** object. The parameter type is {@link ArkUI_DrawableDescriptor}. Either **.object** or
     * **.string** must be set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: image address. In API version 22 and earlier versions, the value can be a network image resource
     * address, local image resource address, Base64 string, or PixelMap resource, but cannot be the address of an
     * animated image such as an SVG, GIF, or WebP image. In API version 23 and later versions, animated images of
     * the WebP and GIF types are supported. Only the first frame of the animated image is displayed. Other types of
     * animated images are not supported.</li>
     * <li>.value[0].i32: whether the image is repeated. The parameter type is {@link ArkUI_ImageRepeat}.</li>
     * <li>.object: **PixelMap** object. The parameter type is {@link ArkUI_DrawableDescriptor}.</li>
     * </ul>
     *
     * @ingroup Background Display
     *
     */
    NODE_BACKGROUND_IMAGE,
    /**
     * @brief Padding attribute, which can be set (through {@link setAttribute}), reset (through
     * {@link resetAttribute}), and obtained (through {@link getAttribute}) as required.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:**
     * 1: Specify the same padding for the four directions (top, bottom, left, and right).
     * <ul>
     * <li>.value[0].f32: Padding for the four directions (top, bottom, left, and right), in vp. Value range: [0, +∞).
     * When an invalid value is set, the default value **0vp** is used for display.</li>
     * </ul>
     * 2: Specify different padding values for the four directions (top, bottom, left, and right).
     * <ul>
     * <li>.value[0].f32: Top padding, in vp. The default value is **0vp**. Value range: [0, +∞). When an invalid value
     * is set, the default value **0vp** is used.</li>
     * <li>.value[1].f32: Right padding, in vp. The default value is **0vp**. Value range: [0, +∞). When an invalid
     * value is set, the default value **0vp** is used.</li>
     * <li>.value[2].f32: Bottom padding, in vp. The default value is **0vp**. Value range: [0, +∞). When an invalid
     * value is set, the default value **0vp** is used.</li>
     * <li>.value[3].f32: Left padding, in vp. The default value is **0vp**. Value range: [0, +∞). When an invalid value
     * is set, the default value **0vp** is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Top padding, in vp.</li>
     * <li>.value[1].f32: Right padding, in vp.</li>
     * <li>.value[2].f32: Bottom padding, in vp.</li>
     * <li>.value[3].f32: Left padding, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_PADDING,
    /**
     * @brief Component ID attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: component ID.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: component ID.\n
     *
     */
    NODE_ID,
    /**
     * @brief Interactivity attribute, which can be set, reset, and obtained as required through APIs.
     * <br>Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:
     * <br>.value[0].i32: Whether the component can interact with users. The value **1** indicates that the component
     * can interact with users, and **0** indicates the opposite. The default value is **1**. If the value is less
     * than 0, it does not take effect. If the value is greater than 1, the default value is used.
     * <br>Format of the return value {@link ArkUI_AttributeItem}:
     * <br>.value[0].i32: Whether the component can interact with users. The value **1** indicates that the component
     * can interact with users, and **0** indicates the opposite.
     *
     */
    NODE_ENABLED,
    /**
     * @brief Margin attribute, which can be set (through {@link setAttribute}), reset (through {@link resetAttribute}),
     * and obtained (through {@link getAttribute}) as required.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:**
     * 1: Specify the same margin for the four directions (top, bottom, left, and right).
     * <ul>
     * <li>.value[0].f32: Margin for the four directions (top, bottom, left, and right), in vp. Value range: [0, +∞).
     * When an invalid value is set, the default value **0vp** is used for display.</li>
     * </ul>
     * 2: Specify different margins for the four directions (top, bottom, left, and right).
     * <ul>
     * <li>.value[0].f32: Top margin, in vp. The default value is **0vp**. Value range: [0, +∞). When an invalid value
     * is set, the default value **0vp** is used for display.</li>
     * <li>.value[1].f32: Right margin, in vp. The default value is **0vp**. Value range: [0, +∞). When an invalid value
     * is set, the default value **0vp** is used for display.</li>
     * <li>.value[2].f32: Bottom margin, in vp. The default value is **0vp**. Value range: [0, +∞). When an invalid
     * value is set, the default value **0vp** is used for display.</li>
     * <li>.value[3].f32: Left margin, in vp. The default value is **0vp**. Value range: [0, +∞). When an invalid value
     * is set, the default value **0vp** is used for display.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Top margin, in vp.</li>
     * <li>.value[1].f32: Right margin, in vp.</li>
     * <li>.value[2].f32: Bottom margin, in vp.</li>
     * <li>.value[3].f32: Left margin, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_MARGIN,
    /**
     * @brief Translate attribute, which can be set, reset, and obtained as required through APIs.
     * This attribute is mutually exclusive with **NODE_TRANSLATE_WITH_PERCENT**. A component can use only one
     * translation attribute. If **NODE_TRANSLATE** and **NODE_TRANSLATE_WITH_PERCENT** are set simultaneously,
     * the value set by the latter overrides the former.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: distance to translate along the x-axis, in vp. The default value is **0**.\n
     * .value[1].f32: distance to translate along the y-axis, in vp. The default value is **0**.\n
     * .value[2].f32: distance to translate along the z-axis, in vp. The default value is **0**.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: distance to translate along the x-axis, in vp.\n
     * .value[1].f32: distance to translate along the y-axis, in vp.\n
     * .value[2].f32: distance to translate along the z-axis, in vp.\n
     *
     * @ingroup Visual
     */
    NODE_TRANSLATE,
    /**
     * @brief Scale attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: scale factor along the x-axis. The default value is **1**. When the value is **0**, the
     * component is invisible. When the value is negative, the component is flipped along the x-axis.\n
     * .value[1].f32: scale factor along the y-axis. The default value is **1**. When the value is **0**, the
     * component is invisible. When the value is negative, the component is flipped along the y-axis.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: scale factor along the x-axis.\n
     * .value[1].f32: scale factor along the y-axis.\n
     *
     * @ingroup Visual
     */
    NODE_SCALE,
    /**
     * @brief Rotate attribute, which can be set, reset, and obtained as required through APIs.
     * This attribute is mutually exclusive with **NODE_ROTATE_ANGLE**. A component can use only one rotation
     * attribute. If **NODE_ROTATE** and **NODE_ROTATE_ANGLE** are set simultaneously, the value set by the
     * latter overrides the former.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: X-coordinate of the rotation axis vector. The default value is **0**.\n
     * .value[1].f32: Y-coordinate of the rotation axis vector. The default value is **0**.\n
     * .value[2].f32: Z-coordinate of the rotation axis vector. The default value is **0**.\n
     * .value[3].f32: rotation angle, in degrees (°). The default value is **0**.\n
     * .value[4].f32: line of sight, that is, the distance from the viewpoint to the z=0 plane, in vp. The
     * default value is **0**.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X-coordinate of the rotation axis vector.\n
     * .value[1].f32: Y-coordinate of the rotation axis vector.\n
     * .value[2].f32: Z-coordinate of the rotation axis vector.\n
     * .value[3].f32: rotation angle, in degrees (°).\n
     * .value[4].f32: line of sight, that is, the distance from the viewpoint to the z=0 plane, in vp.\n
     *
     * @ingroup Visual
     */
    NODE_ROTATE,
    /**
     * @brief Brightness attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: brightness value. The default value is **1.0**, and the recommended value range is
     * [0, 2.0].\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: brightness value. **1.0** indicates the original brightness. Recommended value range:
     * [0, 2.0].\n
     *
     * @ingroup Visual
     */
    NODE_BRIGHTNESS,
    /**
     * @brief Saturation attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: saturation value. Default value: **1.0**. Recommended value range: [0, 50.0). If a negative
     * value is passed, the value **0** is used.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: saturation value. **1.0** indicates the original saturation. Recommended value range:
     * [0, 50.0).\n
     *
     * @ingroup Visual
     */
    NODE_SATURATION,
    /**
     * @brief Blur attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: blur radius. Value range: [0, +∞). A larger value indicates a higher blur degree. If the
     * value is **0**, the content is not blurred. If the value is less than 0, it is treated as 0 and no error
     * code is returned. The unit is vp. The default value is **0.0**.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: blur radius. A larger value indicates a higher blur degree. If the value is 0, the content
     * is not blurred. The unit is vp.\n
     *
     * @ingroup Visual
     */
    NODE_BLUR,
    /**
     * @brief Linear gradient attribute, which can be set, reset, and obtained as required through APIs.
     * This attribute is mutually exclusive with **NODE_SWEEP_GRADIENT** and **NODE_RADIAL_GRADIENT**. A component
     * can set only one gradient type. If multiple gradient attributes are set simultaneously, the gradient type
     * set later overrides the previously set gradient effect.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: start angle of the linear gradient, in degrees (°). The angle increases clockwise from the
     * 0 o'clock direction. The default value is **180**. When {@link ArkUI_LinearGradientDirection} is set to
     * **ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM**, the **angle** attribute takes effect; otherwise, the
     * **direction** attribute is used as the main layout mode.\n
     * .value[1].i32: direction of the linear gradient. The parameter type is
     * {@link ArkUI_LinearGradientDirection}. When it is set to a value other than
     * **ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM**, the **angle** attribute does not take effect.\n
     * .value[2].i32: whether the colors are repeated. The value **0** means that the colors are not repeated,
     * and **1** means the opposite. The default value is **0**.\n
     * .object: the parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of
     * which consists of a color and its stop position. Invalid colors are automatically skipped.\n
     * colors: colors of the color stops.\n
     * stops: stop positions of the color stops.\n
     * size: number of colors.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: start angle of the linear gradient, in degrees (°). The set value is used only when
     * **direction** is set to **ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM**. In other cases, the default value is
     * used.\n
     * .value[1].i32: direction of the linear gradient. The parameter type is
     * {@link ArkUI_LinearGradientDirection}.\n
     * .value[2].i32: whether the colors are repeated. The value **0** means that the colors are not repeated,
     * and **1** means the opposite.\n
     * .object: the parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of
     * which consists of a color and its stop position. Invalid colors are automatically skipped.\n
     * colors: colors of the color stops.\n
     * stops: stop positions of the color stops.\n
     * size: number of colors.\n
     *
     * @ingroup Visual
     */
    NODE_LINEAR_GRADIENT,
    /**
     * @brief Alignment attribute for component content in the element drawing area, which can be set (through
     * {@link setAttribute}), reset (through {@link resetAttribute}), and obtained (through {@link getAttribute}) as
     * required.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Alignment mode. The parameter type is {@link ArkUI_Alignment}. The default value is
     * **ARKUI_ALIGNMENT_CENTER**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Alignment mode. The parameter type is {@link ArkUI_Alignment}.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_ALIGNMENT,
    /**
     * @brief Opacity attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: opacity value. Default value: **1**. Value range: [0, 1].\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: opacity value. The value ranges from 0 to 1.\n
     *
     * @ingroup Visual
     */
    NODE_OPACITY,
    /**
     * @brief Border width attribute, which can be set (through {@link setAttribute}), reset (through
     * {@link resetAttribute}), and obtained (through {@link getAttribute}) as required.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **There are two formats of {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * 1: Specify the same width for the four borders.
     * <ul>
     * <li>.value[0].f32: Width for the four borders, in vp. Value range: [0, +∞). The default value is **0vp**.</li>
     * </ul>
     * 2: Specify different width values for the four borders.
     * <ul>
     * <li>.value[0].f32: Width of the top border, in vp. The default value is **0vp**. Value range: [0, +∞).</li>
     * <li>.value[1].f32: Width of the right border, in vp. The default value is **0vp**. Value range: [0, +∞).</li>
     * <li>.value[2].f32: Width of the bottom border, in vp. The default value is **0vp**. Value range: [0, +∞).</li>
     * <li>.value[3].f32: Width of the left border, in vp. The default value is **0vp**. Value range: [0, +∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Width of the top border, in vp.</li>
     * <li>.value[1].f32: Width of the right border, in vp.</li>
     * <li>.value[2].f32: Width of the bottom border, in vp.</li>
     * <li>.value[3].f32: Width of the left border, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_BORDER_WIDTH,
    /**
     * @brief Border corner radius attribute, which can be set (through {@link setAttribute}), reset (through
     * {@link resetAttribute}), and obtained (through {@link getAttribute}) as required.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **There are two formats of {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * 1. Specify the same corner radius for the four borders.
     * <ul>
     * <li>.value[0].f32: Corner radius for the four borders, in vp. Value range: [0, +∞). The default value is **0vp**
     * .</li>
     * </ul>
     * 2. Four parameters are passed, indicating respectively setting the border radius for each of the four corners.
     * <ul>
     * <li>.value[0].f32: Radius of the upper left corner, in vp. The default value is **0vp**. Value range: [0, +
     * ∞).</li>
     * <li>.value[1].f32: Radius of the upper right corner, in vp. The default value is **0vp**. Value range: [0, +
     * ∞).</li>
     * <li>.value[2].f32: Radius of the lower left corner, in vp. The default value is **0vp**. Value range: [0, +
     * ∞).</li>
     * <li>.value[3].f32: Radius of the lower right corner, in vp. The default value is **0vp**. Value range: [0, +
     * ∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Radius of the upper left corner, in vp.</li>
     * <li>.value[1].f32: Radius of the upper right corner, in vp.</li>
     * <li>.value[2].f32: Radius of the lower left corner, in vp.</li>
     * <li>.value[3].f32: Radius of the lower right corner, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_BORDER_RADIUS,
    /**
     * @brief Border color attribute, which can be set (through {@link setAttribute}), reset (through
     * {@link resetAttribute}), and obtained (through {@link getAttribute}) as required.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **There are two formats of {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * 1: Specify the same color for the four borders.
     * <ul>
     * <li>.value[0].u32: Color for the four borders, in 0xARGB format, for example, `0xFFFF11FF`.</li>
     * </ul>
     * 2: Specify different colors for the four borders.
     * <ul>
     * <li>.value[0].u32: Color of the top border, in 0xARGB format. The default value is `0xFF000000`.</li>
     * <li>.value[1].u32: Color of the right border, in 0xARGB format. The default value is `0xFF000000`.</li>
     * <li>.value[2].u32: Color of the bottom border, in 0xARGB format. The default value is `0xFF000000`.</li>
     * <li>.value[3].u32: Color of the left border, in 0xARGB format. The default value is `0xFF000000`.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: Color of the top border, in 0xARGB format, for example, `0xFFFF11FF`.</li>
     * <li>.value[1].u32: Color of the right border, in 0xARGB format, for example, `0xFFFF11FF`.</li>
     * <li>.value[2].u32: Color of the bottom border, in 0xARGB format, for example, `0xFFFF11FF`.</li>
     * <li>.value[3].u32: Color of the left border, in 0xARGB format, for example, `0xFFFF11FF`.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_BORDER_COLOR,
    /**
     * @brief Border line style attribute, which can be set (through {@link setAttribute}), reset (through
     * {@link resetAttribute}), and obtained (through {@link getAttribute}) as required.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **There are two formats of {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * 1: Specify the same line style for the four borders.
     * <ul>
     * <li>.value[0].i32: Line style for the four borders. The parameter type is {@link ArkUI_BorderStyle}. The default
     * value is **ARKUI_BORDER_STYLE_SOLID**.</li>
     * </ul>
     * 2: Specify different line styles for the four borders.
     * <ul>
     * <li>.value[0].i32: Line style of the top border. The parameter type is {@link ArkUI_BorderStyle}. The default
     * value is **ARKUI_BORDER_STYLE_SOLID**.</li>
     * <li>.value[1].i32: Line style of the right border. The parameter type is {@link ArkUI_BorderStyle}. The default
     * value is **ARKUI_BORDER_STYLE_SOLID**.</li>
     * <li>.value[2].i32: Line style of the bottom border. The parameter type is {@link ArkUI_BorderStyle}. The default
     * value is **ARKUI_BORDER_STYLE_SOLID**.</li>
     * <li>.value[3].i32: Line style of the left border. The parameter type is {@link ArkUI_BorderStyle}. The default
     * value is **ARKUI_BORDER_STYLE_SOLID**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Line style of the top border. The parameter type is {@link ArkUI_BorderStyle}.</li>
     * <li>.value[1].i32: Line style of the right border. The parameter type is {@link ArkUI_BorderStyle}.</li>
     * <li>.value[2].i32: Line style of the bottom border. The parameter type is {@link ArkUI_BorderStyle}.</li>
     * <li>.value[3].i32: Line style of the left border. The parameter type is {@link ArkUI_BorderStyle}.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_BORDER_STYLE,
    /**
     * @brief Z-index attribute for the stack sequence. This attribute can be set, reset, and obtained as required
     * through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: z-index value. A larger value indicates a higher component level. Default value: **0**.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: z-index value. The default value is **0**.\n
     *
     */
    NODE_Z_INDEX,
    /**
     * @brief Visibility attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to show or hide the component. The parameter type is {@link ArkUI_Visibility}.
     * The default value is **ARKUI_VISIBILITY_VISIBLE**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the component is shown or hidden. The parameter type is {@link ArkUI_Visibility}.
     * Default value: **ARKUI_VISIBILITY_VISIBLE**. The meaning of each enumerated value and its corresponding
     * number are as follows: **ARKUI_VISIBILITY_VISIBLE(0)** indicates visible, **ARKUI_VISIBILITY_HIDDEN(1)**
     * indicates hidden but occupying space, and **ARKUI_VISIBILITY_NONE(2)** indicates hidden and not occupying
     * space.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     */
    NODE_VISIBILITY,
    /**
     * @brief Clip attribute, which controls whether to clip the area of child components that extends beyond the
     * current component range. This attribute can be set, reset, and obtained as required through APIs.
     * This attribute is mutually exclusive with **NODE_CLIP_SHAPE**. A component can use only one clipping
     * attribute. **NODE_CLIP** provides simple boolean clipping, and **NODE_CLIP_SHAPE** provides clipping with a
     * specified shape. When both are set, the latter overrides the former.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to clip the area of child components that extends beyond the bounds of the parent
     * component. The value **0** indicates not to clip, and the value **1** indicates to clip. The default value
     * is **0**.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the area of child components that extends beyond the bounds of the parent component
     * is clipped. The value **0** indicates no clipping, and the value **1** indicates clipping.\n
     *
     * @ingroup Visual
     */
    NODE_CLIP,
    /**
     * @brief Clipping shape on the component. This attribute can be set, reset, and obtained as required
     * through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute,
     * which supports four types of shapes:\n
     * 1. Rectangle:\n
     * .value[0].i32: type of shape. The parameter type is {@link ArkUI_ClipType}.
     * The value is <b>ARKUI_CLIP_TYPE_RECTANGLE</b> for the rectangle shape. \n
     * .value[1].f32: width of the rectangle.\n
     * .value[2].f32: height of rectangle.\n
     * .value[3].f32: width of the rounded corner of the rectangle.\n
     * .value[4].f32: height of the rounded corner of the rectangle.\n
     * .value[5]?.f32: radius of the top left corner of the rectangular shape.\n
     * .value[6]?.f32: radius of the bottom left corner of the rectangular shape.\n
     * .value[7]?.f32: radius of the top right corner of the rectangular shape.\n
     * .value[8]?.f32: radius of the bottom right corner of the rectangular shape.\n
     * ?.object: clipOption of the rectangle. The parameter type is {@link ArkUI_RenderNodeClipOption} type.
     * It takes effect when only the .object parameter is passed, ArkUI_RenderNodeClipOption type is rectangle,
     * and .size must be equal to 1.
     * 2. Circle:\n
     * .value[0].i32: type of shape. The parameter type is {@link ArkUI_ClipType}.
     * The value is <b>ARKUI_CLIP_TYPE_CIRCLE</b> for the circle shape.\n
     * .value[1].f32: width of the circle.\n
     * .value[2].f32: height of the circle.\n
     * ?.object: clipOption of the circle. The parameter type is {@link ArkUI_RenderNodeClipOption} type.
     * It takes effect when only the .object parameter is passed, ArkUI_RenderNodeClipOption type is circle,
     * and .size must be equal to 1.
     * 3.Ellipse:\n
     * .value[0].i32: type of shape. The parameter type is {@link ArkUI_ClipType}.
     * The value is <b>ARKUI_CLIP_TYPE_ELLIPSE</b> for the ellipse shape.\n
     * .value[1].f32: width of the ellipse.\n
     * .value[2].f32: height of the ellipse.\n
     * ?.object: clipOption of the ellipse. The parameter type is {@link ArkUI_RenderNodeClipOption} type.
     * It takes effect when only the .object parameter is passed, ArkUI_RenderNodeClipOption type is ellipse,
     * and .size must be equal to 1.
     * 4. Path:\n
     * .value[0].i32: type of shape. The parameter type is {@link ArkUI_ClipType}.
     * The value is <b>ARKUI_CLIP_TYPE_PATH</b> for the path shape.\n
     * .value[1].f32: width of the path.\n
     * .value[2].f32: height of the path.\n
     * .string: command for drawing the path.\n
     * ?.object: clipOption of the path. The parameter type is {@link ArkUI_RenderNodeClipOption} type.
     * It takes effect when only the .object parameter is passed, ArkUI_RenderNodeClipOption type is path,
     * and .size must be equal to 1.\n
     * Format of the return value {@link ArkUI_AttributeItem}, which supports four types of shapes: \n
     * 1. Rectangle:\n
     * .value[0].i32: type of shape. The parameter type is {@link ArkUI_ClipType}.
     * The value is <b>ARKUI_CLIP_TYPE_RECTANGLE</b> for the rectangle shape.\n
     * .value[1].f32: width of the rectangle.\n
     * .value[2].f32: height of rectangle.\n
     * .value[3].f32: width of the rounded corner of the rectangle.\n
     * .value[4].f32: height of the rounded corner of the rectangle.\n
     * .value[5].f32: radius of the top left corner of the rectangular shape; \n
     * .value[6].f32: radius of the bottom left corner of the rectangular shape; \n
     * .value[7].f32: radius of the top right corner of the rectangular shape; \n
     * .value[8].f32: radius of the bottom right corner of the rectangular shape; \n
     * .value[9]?.f32: horizontal coordinate offset of the rectangle. \n
     * .value[10]?.f32: vertical coordinate offset of the rectangle. \n
     * 2. Circle:\n
     * .value[0].i32: type of shape. The parameter type is {@link ArkUI_ClipType}.
     * The value is <b>ARKUI_CLIP_TYPE_CIRCLE</b> for the circle shape.\n
     * .value[1].f32: width of the circle.\n
     * .value[2].f32: height of the circle.\n
     * .value[3]?.f32: horizontal coordinate offset of the circle.\n
     * .value[4]?.f32: vertical coordinate offset of the circle.\n
     * 3.Ellipse:\n
     * .value[0].i32: type of shape. The parameter type is {@link ArkUI_ClipType}.
     * The value is <b>ARKUI_CLIP_TYPE_ELLIPSE</b> for the ellipse shape.\n
     * .value[1].f32: width of the ellipse.\n
     * .value[2].f32: height of the ellipse.\n
     * .value[3]?.f32: horizontal coordinate offset of the ellipse.\n
     * .value[4]?.f32: vertical coordinate offset of the ellipse.\n
     * 4. Path:\n
     * .value[0].i32: type of shape. The parameter type is {@link ArkUI_ClipType}.
     * The value is <b>ARKUI_CLIP_TYPE_PATH</b> for the path shape.\n
     * .value[1].f32: width of the path.\n
     * .value[2].f32: height of the path.\n
     * .string: command for drawing the path.\n
     *
     * @ingroup Visual
     */
    NODE_CLIP_SHAPE,
    /**
     * @brief Transform attribute, which can be used to translate, rotate, and scale images. This attribute can be
     * set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0...15].f32: 16 floating-point numbers of a 4 x 4 transformation matrix, used to perform matrix
     * transformations such as translation, rotation, and scaling on images, arranged in row-major order. In this
     * case, the value of **size** in {@link ArkUI_AttributeItem} should not be **0**.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0...15].f32: 16 floating-point numbers of the 4 x 4 transformation matrix.\n
     *
     * @ingroup Visual
     */
    NODE_TRANSFORM,
    /**
     * @brief Hit test behavior attribute, which can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Hit test mode. The parameter type is {@link ArkUI_HitTestMode}. The default value is
     * **ARKUI_HIT_TEST_MODE_DEFAULT**.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Hit test mode. The parameter type is {@link ArkUI_HitTestMode}. The default value is
     * **ARKUI_HIT_TEST_MODE_DEFAULT**.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     */
    NODE_HIT_TEST_BEHAVIOR,
    /**
     * @brief Offset of the component's upper left corner relative to the parent container's. This attribute can be
     * set (through {@link setAttribute}), reset (through {@link resetAttribute}), and obtained (through
     * {@link getAttribute}) as required.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 2.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: X-coordinate, in vp. Value range: (-∞, +∞).</li>
     * <li>.value[1].f32: Y-coordinate, in vp. Value range: (-∞, +∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: X-coordinate, in vp.</li>
     * <li>.value[1].f32: Y-coordinate, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_POSITION,
    /**
     * @brief Shadow attribute, which can be set, reset, and obtained as required through APIs.
     * This attribute is mutually exclusive with **NODE_CUSTOM_SHADOW**. A component can use only one shadow
     * attribute. When both are set, the latter overrides the former. To use a predefined shadow style, use
     * **NODE_SHADOW**. To customize shadow parameters, use **NODE_CUSTOM_SHADOW**.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: shadow effect of the current component. The parameter type is {@link ArkUI_ShadowStyle}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: shadow effect of the current component. The parameter type is {@link ArkUI_ShadowStyle}.\n
     *
     * @ingroup Visual
     */
    NODE_SHADOW,
    /**
     * @brief Custom shadow effect. It is mutually exclusive with **NODE_SHADOW**. A component can use only one
     * shadow attribute. When both are set, the latter overrides the former. To use a predefined shadow style, use
     * **NODE_SHADOW**. To customize shadow parameters, use **NODE_CUSTOM_SHADOW**. This attribute can be set,
     * reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.f32: blur radius of the shadow. Value range: [0, +∞). Passing a negative value returns a
     * parameter verification failure. Unit: px. Default value: **0.0**.\n
     * .value[1]?.i32: whether to enable the coloring strategy. The value **1** means to enable the coloring
     * strategy (the color is automatically picked from around the component to adapt to the background), and
     * **0** means the opposite (a fixed color is used). The default value is **0**. Pass **1** when the shadow
     * color needs to automatically adapt to the surrounding background.\n
     * .value[2]?.f32: offset of the shadow along the x-axis, in px. Default value: **0.0**.\n
     * .value[3]?.f32: offset of the shadow along the y-axis, in px. Default value: **0.0**.\n
     * .value[4]?.i32: shadow type. The parameter type is {@link ArkUI_ShadowType}. The default value is
     * **ARKUI_SHADOW_TYPE_COLOR**.\n
     * .value[5]?.u32: it specifies the shadow color when the coloring strategy is disabled (**.value[1]** is set
     * to **0**), in 0xARGB format. For example, **0xFFFF0000** indicates red. If not passed, the default value
     * is **0xFF000000** (black). It specifies the coloring strategy when the coloring strategy is enabled
     * (**.value[1]** is set to **1**), and the parameter type is {@link ArkUI_ColorStrategy}.\n
     * .value[6]?.u32: whether to fill the shadow. The value **1** means to fill the shadow, and **0** means the
     * opposite.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: blur radius of the shadow, in px.\n
     * .value[1].i32: whether the coloring strategy is enabled. The value 1 indicates the coloring strategy is
     * enabled, and **0** indicates the opposite.\n
     * .value[2].f32: offset of the shadow along the x-axis, in px.\n
     * .value[3].f32: offset of the shadow along the y-axis, in px.\n
     * .value[4].i32: shadow type. The parameter type is {@link ArkUI_ShadowType}, and the default value is
     * **ARKUI_SHADOW_TYPE_COLOR**. The enumerated values include: **ARKUI_SHADOW_TYPE_COLOR** (color shadow) and
     * **ARKUI_SHADOW_TYPE_BLUR** (blur shadow).\n
     * .value[5].u32: shadow color, in 0xARGB format. For example, **0xFFFF0000** indicates red.\n
     * .value[6].u32: whether the shadow is filled. The value **1** means that the shadow is filled, and **0**
     * means the opposite.\n
     *
     * @ingroup Visual
     */
    NODE_CUSTOM_SHADOW,
    /**
     * @brief Background image size attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: width of the image. The value range is [0,+∞), and the unit is vp.</li>
     * <li>.value[1].f32: height of the image. The value range is [0,+∞), and the unit is vp.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: width of the image, in vp.</li>
     * <li>.value[1].f32: height of the image, in vp.</li>
     * </ul>
     *
     * @ingroup Background Display
     */
    NODE_BACKGROUND_IMAGE_SIZE,
    /**
     * @brief Background image size with style. This attribute can be set, reset, and obtained as required
     * through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: background image size with style. The value is an enumerated value of
     * {@link ArkUI_ImageSize}. Different enumerated values determine how the background image is scaled and
     * cropped, such as displaying at the original size, covering the component area while maintaining the aspect
     * ratio, or displaying completely while maintaining the aspect ratio.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: background image size with style. The value is an enumerated value of
     * {@link ArkUI_ImageSize}.</li>
     * </ul>
     *
     * @ingroup Background Display
     */
    NODE_BACKGROUND_IMAGE_SIZE_WITH_STYLE,
    /**
     * @brief Background blur attribute. The blur effect is applied between the background layer and the content
     * layer of the component. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: blur type. The value is an enumerated value of {@link ArkUI_BlurStyle}.</li>
     * <li>.value[1]?.i32: color mode. The value is an enumerated value of {@link ArkUI_ColorMode}. If not
     * specified, the default color mode of the system is used.</li>
     * <li>.value[2]?.i32: adaptive color mode. The value is an enumerated value of {@link ArkUI_AdaptiveColor}.
     * If not specified, the default adaptive color mode is used. Pass this parameter when a fixed color picking
     * mode is required.</li>
     * <li>.value[3]?.f32: blur degree. The value range is [0.0, 1.0]. **0.0** indicates no blur, and **1.0**
     * indicates the maximum blur effect. If not specified, the default value is **1.0**. Pass this parameter when
     * the content blur degree needs to be adjusted.</li>
     * <li>.value[4]?.f32: start boundary of grayscale blur, that is, the position to which black is brightened.
     * The valid value range is 0 to 127. A larger value produces a more obvious adjustment effect.</li>
     * <li>.value[5]?.f32: end boundary of grayscale blur, that is, the position to which white is darkened. The
     * valid value range is 0 to 127. A larger value produces a more obvious adjustment effect.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: blur type. The value is an enumerated value of {@link ArkUI_BlurStyle}.</li>
     * <li>.value[1].i32: color mode. The value is an enumerated value of {@link ArkUI_ColorMode}. The enumerated
     * values include: **ARKUI_COLOR_MODE_LIGHT** (light mode) and **ARKUI_COLOR_MODE_DARK** (dark mode).</li>
     * <li>.value[2].i32: adaptive color mode. The value is an enumerated value of
     * {@link ArkUI_AdaptiveColor}.</li>
     * <li>.value[3].f32: blur degree. The value range is [0.0, 1.0].</li>
     * <li>.value[4].f32: start boundary of grayscale blur.</li>
     * <li>.value[5].f32: end boundary of grayscale blur.</li>
     * </ul>
     *
     * @ingroup Background Display
     */
    NODE_BACKGROUND_BLUR_STYLE,
    /**
     * @brief Center point attribute for image transformation and transition, which affects the center point
     * behavior of transformation and transition attributes such as rotation
     * (**NODE_ROTATE** / **NODE_ROTATE_ANGLE** / **NODE_ROTATE_TRANSITION**), scaling
     * (**NODE_SCALE** / **NODE_SCALE_TRANSITION**), and translation
     * (**NODE_TRANSLATE** / **NODE_TRANSLATE_TRANSITION**). This attribute can be set, reset, and obtained as
     * required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     * Note: If the coordinate is expressed in a number that represents a percentage, the attribute obtaining API
     * returns the calculated value in vp.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.f32: X-coordinate of the center point, in vp. Default value: **0.0**.\n
     * .value[1]?.f32: Y-coordinate of the center point, in vp. Default value: **0.0**.\n
     * .value[2]?.f32: Z-coordinate of the center point, in vp. Default value: **0.0**.\n
     * .value[3]?.f32: X-coordinate of the center point, expressed in a number that represents a percentage. The
     * value range is [0, 1]. For example, **0.2** indicates 20%. This attribute overwrites **value[0].f32**. The
     * default value is **0.5f**. The error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned when the value
     * is out of range.\n
     * .value[4]?.f32: Y-coordinate of the center point, expressed in a number that represents a percentage. The
     * value range is [0, 1]. For example, **0.2** indicates 20%. This attribute overwrites **value[1].f32**. The
     * default value is **0.5f**. The error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned when the value
     * is out of range.\n
     * .value[5]?.f32: Z-coordinate of the center point, expressed in a number that represents a percentage. The
     * value range is [0, 1]. For example, **0.2** indicates 20%. This attribute overwrites **value[2].f32**. The
     * default value is **0.0f**. The error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned when the value
     * is out of range.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X-coordinate of the center point, in vp.\n
     * .value[1].f32: Y-coordinate of the center point, in vp.\n
     * .value[2].f32: Z-coordinate of the center point, in vp.\n     *
     * @ingroup Visual
     */
    NODE_TRANSFORM_CENTER,
    /**
     * @brief Transition opacity attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: opacity value at the end of the transition (that is, the end point). The transition changes
     * from the current opacity to this value.\n
     * .value[1].i32: animation duration, in ms. The value must be greater than 0.\n
     * .value[2].i32: animation curve type. The value is an enumerated value of
     * {@link ArkUI_AnimationCurve}.\n
     * .value[3]?.i32: animation delay duration, in ms. The default value is **0** (no delay) when this parameter
     * is not passed. Pass this parameter when the animation needs to wait for a period of time before starting.\n
     * .value[4]?.i32: number of times the animation is played. The default value is **1** (play once) when this
     * parameter is not passed. Pass this parameter when the animation needs to be played repeatedly.\n
     * .value[5]?.i32: animation playback mode. The value is an enumerated value of
     * {@link ArkUI_AnimationPlayMode}. The default value is **ARKUI_ANIMATION_PLAY_MODE_NORMAL**. Pass this
     * parameter when a special play mode such as reverse playback or loop playback is required.\n
     * .value[6]?.f32: animation playback speed. The default value is **1.0** (normal speed) when this parameter
     * is not passed. Pass this parameter when the animation needs to be played faster or slower. A value greater
     * than **1.0** indicates acceleration, and a value less than **1.0** indicates deceleration.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: opacity values of the start and end points. The value range is [0, 1]. Values beyond the
     * range are automatically corrected to the boundary values.\n
     * .value[1].i32: animation duration, in ms.\n
     * .value[2].i32: animation curve type. The value is an enumerated value of
     * {@link ArkUI_AnimationCurve}.\n
     * .value[3].i32: animation delay duration, in ms.\n
     * .value[4].i32: number of times the animation is played.\n
     * .value[5].i32: animation playback mode. The value is an enumerated value of
     * {@link ArkUI_AnimationPlayMode}.\n
     * .value[6].f32: animation playback speed.\n
     *
     * @ingroup Animate
     */
    NODE_OPACITY_TRANSITION,
    /**
     * @brief Transition rotation attribute, which takes effect only when a component is inserted or deleted. This
     * attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: X-component of the rotation vector.\n
     * .value[1].f32: Y-component of the rotation vector.\n
     * .value[2].f32: Z-component of the rotation vector.\n
     * .value[3].f32: angle, in degrees (°).\n
     * .value[4].f32: line of sight, that is, the distance from the viewpoint to the z=0 plane. Value range:
     * [0, +∞). A negative value is treated as **0**. Unit: vp. Default value: **0.0**.\n
     * .value[5].i32: animation duration, in ms.\n
     * .value[6].i32: animation curve type. The value is an enumerated value of
     * {@link ArkUI_AnimationCurve}.\n
     * .value[7]?.i32: animation delay duration, in ms. If not passed, the default value is **0** (no delay). Pass
     * this parameter when the animation needs to wait for a period of time before starting.\n
     * .value[8]?.i32: number of times the animation is played.\n
     * .value[9]?.i32: animation playback mode. The value is an enumerated value of
     * {@link ArkUI_AnimationPlayMode}. Default value: **ARKUI_ANIMATION_PLAY_MODE_NORMAL**.\n
     * .value[10]?.f32: animation playback speed.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X-component of the rotation vector.\n
     * .value[1].f32: Y-component of the rotation vector.\n
     * .value[2].f32: Z-component of the rotation vector.\n
     * .value[3].f32: angle, in degrees (°).\n
     * .value[4].f32: line of sight, in vp.\n
     * .value[5].i32: animation duration, in ms.\n
     * .value[6].i32: animation curve type. The value is an enumerated value of
     * {@link ArkUI_AnimationCurve}.\n
     * .value[7].i32: animation delay duration, in ms.\n
     * .value[8].i32: number of times the animation is played.\n
     * .value[9].i32: animation playback mode. The value is an enumerated value of
     * {@link ArkUI_AnimationPlayMode}.\n
     * .value[10].f32: animation playback speed.\n
     *
     * @ingroup Animate
     */
    NODE_ROTATE_TRANSITION,
    /**
     * @brief Transition scaling attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: scale factor along the x-axis. Default value: **1.0**.\n
     * .value[1].f32: scale factor along the y-axis. Default value: **1.0**.\n
     * .value[2].f32: scale factor along the z-axis. Default value: **1.0**.\n
     * .value[3].i32: animation duration, in ms.\n
     * .value[4].i32: animation curve type. The value is an enumerated value of
     * {@link ArkUI_AnimationCurve}.\n
     * .value[5]?.i32: animation delay duration, in ms. If not passed, the default value is **0** (no delay). Pass
     * this parameter when the animation needs to wait for a period of time before starting.\n
     * .value[6]?.i32: number of times the animation is played.\n
     * .value[7]?.i32: animation playback mode. The value is an enumerated value of
     * {@link ArkUI_AnimationPlayMode}. The default value is **ARKUI_ANIMATION_PLAY_MODE_NORMAL**.\n
     * .value[8]?.f32: animation playback speed.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: scale factor along the x-axis.\n
     * .value[1].f32: scale factor along the y-axis.\n
     * .value[2].f32: scale factor along the z-axis.\n
     * .value[3].i32: animation duration, in ms.\n
     * .value[4].i32: animation curve type. The value is an enumerated value of
     * {@link ArkUI_AnimationCurve}.\n
     * .value[5].i32: animation delay duration, in ms.\n
     * .value[6].i32: number of times the animation is played.\n
     * .value[7].i32: animation playback mode. The value is an enumerated value of
     * {@link ArkUI_AnimationPlayMode}.\n
     * .value[8].f32: animation playback speed.\n
     *
     * @ingroup Animate
     */
    NODE_SCALE_TRANSITION,
    /**
     * @brief Transition translation attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: translation distance along the x-axis, in vp. The default value is **0.0**.\n
     * .value[1].f32: translation distance along the y-axis, in vp. The default value is **0.0**.\n
     * .value[2].f32: translation distance along the z-axis, in vp. The default value is **0.0**.\n
     * .value[3].i32: animation duration, in ms.\n
     * .value[4].i32: animation curve type. The value is an enumerated value of
     * {@link ArkUI_AnimationCurve}.\n
     * .value[5]?.i32: animation delay duration, in ms. If not passed, the default value is **0** (no delay). Pass
     * this parameter when the animation needs to wait for a period of time before starting.\n
     * .value[6]?.i32: number of times the animation is played.\n
     * .value[7]?.i32: animation playback mode. The value is an enumerated value of
     * {@link ArkUI_AnimationPlayMode}. The default value is **ARKUI_ANIMATION_PLAY_MODE_NORMAL**.\n
     * .value[8]?.f32: animation playback speed.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: translation distance along the x-axis, in vp.\n
     * .value[1].f32: translation distance along the y-axis, in vp.\n
     * .value[2].f32: translation distance along the z-axis, in vp.\n
     * .value[3].i32: animation duration, in ms.\n
     * .value[4].i32: animation curve type. The value is an enumerated value of
     * {@link ArkUI_AnimationCurve}.\n
     * .value[5].i32: animation delay duration, in ms.\n
     * .value[6].i32: number of times the animation is played.\n
     * .value[7].i32: animation playback mode. The value is an enumerated value of
     * {@link ArkUI_AnimationPlayMode}.\n
     * .value[8].f32: animation playback speed.\n
     *
     * @ingroup Animate
     */
    NODE_TRANSLATE_TRANSITION,
    /**
     * @brief Slide-in and slide-out of the component from the screen edge during transition. This attribute can
     * be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: edge from which the component slides in and out during transition. The parameter type is
     * {@link ArkUI_TransitionEdge}. Different enumerated values determine from which edge of the screen the
     * component slides in and out.\n
     * .value[1].i32: animation duration, in ms.\n
     * .value[2].i32: animation curve type. The value is an enumerated value of
     * {@link ArkUI_AnimationCurve}.\n
     * .value[3]?.i32: animation delay duration, in ms. The default value is **0** (no delay) when this parameter
     * is not passed. Pass this parameter when the animation needs to wait for a period of time before starting.\n
     * .value[4]?.i32: number of times the animation is played.\n
     * .value[5]?.i32: animation playback mode. The value is an enumerated value of
     * {@link ArkUI_AnimationPlayMode}. The default value is **ARKUI_ANIMATION_PLAY_MODE_NORMAL**.\n
     * .value[6]?.f32: animation playback speed.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: transition edge. The parameter type is {@link ArkUI_TransitionEdge}.\n
     * .value[1].i32: animation duration, in ms.\n
     * .value[2].i32: animation curve type. The value is an enumerated value of
     * {@link ArkUI_AnimationCurve}.\n
     * .value[3].i32: animation delay duration, in ms.\n
     * .value[4].i32: number of times the animation is played.\n
     * .value[5].i32: animation playback mode. The value is an enumerated value of
     * {@link ArkUI_AnimationPlayMode}.\n
     * .value[6].f32: animation playback speed.\n
     *
     * @ingroup Animate
     */
    NODE_MOVE_TRANSITION,

    /**
     * @brief Focus attribute, which controls whether the component can gain focus. It is applicable to scenarios
     * such as keyboard navigation and accessibility assistance. This attribute can be set, reset, and obtained as
     * required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the component is focusable. The value **1** indicates that the component is
     * focusable, and **0** indicates the opposite. The default value is **0**.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the component is focusable. The value **1** indicates that the component is
     * focusable, and **0** indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     */
    NODE_FOCUSABLE,

    /**
     * @brief Default focus attribute, which can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the focus is the default one. The value **1** indicates that the target is the
     * default focus, and **0** indicates that it is not the default focus.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the focus is the default one. The value **1** indicates that the target is the
     * default focus, and **0** indicates that it is not the default focus.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     */
    NODE_DEFAULT_FOCUS,

    /**
     * @brief Touch target attribute, which can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.data[0].f32: X coordinate of the touch point relative to the upper left corner of the component, in vp.</li>
     * <li>.data[1].f32: Y coordinate of the touch point relative to the upper left corner of the component, in vp.</li>
     * <li>.data[2].f32: Width of the touch target, in percentage.</li>
     * <li>.data[3].f32: Height of the touch target, in percentage.</li>
     * <li>.data[4...].f32: Multiple touch targets that can be set. The sequence of the parameters is the same as the
     * preceding.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.data[0].f32: X coordinate of the touch point relative to the upper left corner of the component, in vp.</li>
     * <li>.data[1].f32: Y coordinate of the touch point relative to the upper left corner of the component, in vp.</li>
     * <li>.data[2].f32: Width of the touch target, in percentage.</li>
     * <li>.data[3].f32: Height of the touch target, in percentage.</li>
     * <li>.data[4...].f32: Multiple touch targets that can be set. The sequence of the parameters is the same as the
     * preceding.</li>
     * <li>Note: During configuration, the data array can contain any number of values (all will be accepted), but only
     * the first 20 values can be retrieved.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     */
    NODE_RESPONSE_REGION,

    /**
     * @brief Overlay attribute, which can be set, reset, and obtained as required through APIs. You can set the
     * overlay content through **.string** or **.object**, with **.string** having higher priority.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: Overlay text.</li>
     * <li>.value[0]?.i32: Position of the overlay relative to the component. This parameter is optional. The
     * parameter type is {@link ArkUI_Alignment}. The default value is **ARKUI_ALIGNMENT_TOP_START**.</li>
     * <li>.value[1]?.f32: Offset of the overlay relative to the upper left corner of itself on the x-axis, in vp.
     * This parameter is optional. The default value is **0** vp.</li>
     * <li>.value[2]?.f32: Offset of the overlay relative to the upper left corner of itself on the y-axis, in vp.
     * This parameter is optional. The default value is **0** vp.</li>
     * <li>.value[3]?.i32: Layout direction of the overlay. This parameter is optional. The parameter type is
     * {@link ArkUI_Direction}. The default value is **ARKUI_DIRECTION_LTR**.
     * In most scenarios, this parameter should be set to **Auto**, which allows the system to automatically handle
     * the layout direction. If specific directions need to be maintained in certain scenarios, set this parameter to **
     * LTR** (left-to-right) or **RTL** (right-to-left). It is supported since API version 21.</li>
     * <li>.object: Node tree used for overlay. The parameter type is {@link ArkUI_NodeHandle}. The default value is **
     * nullptr**. It is supported since API version 21.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: Overlay text.</li>
     * <li>.value[0].i32: Position of the overlay relative to the component. The parameter type is
     * {@link ArkUI_Alignment}. The default value is **ARKUI_ALIGNMENT_TOP_START**.</li>
     * <li>.value[1].f32: Offset of the overlay relative to the upper left corner of itself on the x-axis, in vp.</li>
     * <li>.value[2].f32: Offset of the overlay relative to the upper left corner of itself on the y-axis, in vp.</li>
     * <li>.value[3].i32: Layout direction of the overlay. The parameter type is {@link ArkUI_Direction}. The default
     * value is **ARKUI_DIRECTION_LTR**. It is supported since API version 21.</li>
     * <li>.object: Node tree used for overlay. The parameter type is {@link ArkUI_NodeHandle}. It is supported since
     * API version 21.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     */
    NODE_OVERLAY,
    /**
     * @brief Sweep gradient effect. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.f32: X-coordinate of the sweep gradient center relative to the upper left corner of the
     * component, in vp. Default value: 50% of the component width.\n
     * .value[1]?.f32: Y-coordinate of the sweep gradient center relative to the upper left corner of the
     * component, in vp. If not passed, the default value is the vertical center position of the component. Pass
     * this parameter when the gradient center needs to be offset to a specific position.\n
     * .value[2]?.f32: start point of the sweep gradient, in degrees (°). Default value: **0**.\n
     * .value[3]?.f32: end point of the sweep gradient, in degrees (°). Default value: **0**.\n
     * .value[4]?.f32: rotation angle of the sweep gradient, in degrees (°). Default value: **0**.\n
     * .value[5]?.i32: whether the colors are repeated. The value **0** means that the colors are not repeated,
     * and **1** means the opposite. If not passed, the default value is **0** (no repeat). Pass **1** when the
     * colors need to be filled cyclically and repeatedly.\n
     * .object: the parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of
     * which consists of a color and its stop position. Invalid colors are automatically skipped.\n
     * colors: colors of the color stops.\n
     * stops: stop positions of the color stops.\n
     * size: number of colors.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X-coordinate of the sweep gradient center relative to the upper left corner of the
     * component.\n
     * .value[1].f32: Y-coordinate of the sweep gradient center relative to the upper left corner of the
     * component.\n
     * .value[2].f32: start point of the sweep gradient, in degrees (°). Default value: **0**.\n
     * .value[3].f32: end point of the sweep gradient, in degrees (°). Default value: **0**.\n
     * .value[4].f32: rotation angle of the sweep gradient, in degrees (°). Default value: **0**.\n
     * .value[5].i32: whether the colors are repeated. The value **0** means that the colors are not repeated,
     * and **1** means the opposite.\n
     * .object: the parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of
     * which consists of a color and its stop position. Invalid colors are automatically skipped.\n
     * colors: colors of the color stops.\n
     * stops: stop positions of the color stops.\n
     * size: number of colors.\n
     *
     * @ingroup Visual
     */
    NODE_SWEEP_GRADIENT,
    /**
     * @brief Radial gradient effect. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.f32: X-coordinate of the radial gradient center relative to the upper left corner of the
     * current component.\n
     * .value[1]?.f32: Y-coordinate of the radial gradient center relative to the upper left corner of the
     * current component.\n
     * .value[2]?.f32: radius of the radial gradient. The value range is [0, +∞), and the default value is **0**.\n
     * .value[3]?.i32: whether the colors are repeated. The value **0** means that the colors are not repeated,
     * and **1** means the opposite. If this parameter is not passed, the default value is **0** (no repeat).\n
     * .object: the parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of
     * which consists of a color and its stop position. Invalid colors are automatically skipped.\n
     * colors: colors of the color stops.\n
     * stops: stop positions of the color stops.\n
     * size: number of colors.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X-coordinate of the radial gradient center relative to the upper left corner of the
     * component.\n
     * .value[1].f32: Y-coordinate of the radial gradient center relative to the upper left corner of the
     * component.\n
     * .value[2].f32: radius of the radial gradient. The default value is **0**.\n
     * .value[3].i32: whether the colors are repeated. The value **false (0)** means that the colors are not
     * repeated, and **true (1)** means the opposite.\n
     * .object: the parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of
     * which consists of a color and its stop position. Invalid colors are automatically skipped.\n
     * colors: colors of the color stops.\n
     * stops: stop positions of the color stops.\n
     * size: number of colors.\n
     *
     * @ingroup Visual
     */
    NODE_RADIAL_GRADIENT,
    /**
     * @brief Adds a mask of the specified shape to the component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute, which supports five types of
     * shapes:\n
     * 1. Rectangle:\n
     * .value[0].u32 fill color, in 0xARGB format. \n
     * .value[1].u32: stroke color, in 0xARGB format. \n
     * .value[2].f32: stroke width, in vp. \n
     * .value[3].i32: mask type. The parameter type is {@link ArkUI_MaskType}.
     * The value is <b>ARKUI_MASK_TYPE_RECTANGLE</b> for the rectangle shape.\n
     * .value[4].f32: width of the rectangle.\n
     * .value[5].f32: height of the rectangle.\n
     * .value[6].f32: width of the rounded corner of the rectangle.\n
     * .value[7].f32: height of the rounded corner of the rectangle.\n
     * .value[8]?.f32: radius of the top left corner of the rectangular shape.\n
     * .value[9]?.f32: radius of the bottom left corner of the rectangular shape.\n
     * .value[10]?.f32: radius of the top right corner of the rectangular shape.\n
     * .value[11]?.f32: radius of the bottom right corner of the rectangular shape.\n
     * 2. Circle:\n
     * .value[0].u32 fill color, in 0xARGB format. \n
     * .value[1].u32: stroke color, in 0xARGB format. \n
     * .value[2].f32: stroke width, in vp. \n
     * .value[3].i32: mask type. The parameter type is {@link ArkUI_MaskType}.
     * The value is <b>ARKUI_MASK_TYPE_CIRCLE</b> for the circle shape.\n
     * .value[4].f32: width of the circle.\n
     * .value[5].f32: height of the circle.\n
     * 3. Ellipse:\n
     * .value[0].u32 fill color, in 0xARGB format. \n
     * .value[1].u32: stroke color, in 0xARGB format. \n
     * .value[2].f32: stroke width, in vp. \n
     * .value[3].i32: mask type. The parameter type is {@link ArkUI_MaskType}.
     * The value is <b>ARKUI_MASK_TYPE_ELLIPSE</b> for the ellipse shape.\n
     * .value[4].f32: width of the ellipse.\n
     * .value[5].f32: height of the ellipse.\n
     * 4. Path:\n
     * .value[0].u32 fill color, in 0xARGB format. \n
     * .value[1].u32: stroke color, in 0xARGB format. \n
     * .value[2].f32: stroke width, in vp. \n
     * .value[3].i32: mask type. The parameter type is {@link ArkUI_MaskType}.
     * The value is <b>ARKUI_MASK_TYPE_PATH</b> for the path shape.\n
     * .value[4].f32: width of the path.\n
     * .value[5].f32: height of the path.\n
     * .string: command for drawing the path.\n
     * 5. Progress:\n
     * .value[0].i32: mask type. The parameter type is {@link ArkUI_MaskType}.
     * The value is <b>ARKUI_MASK_TYPE_PROGRESS</b> for the progress shape.\n
     * .value[1].f32: current value of the progress indicator.\n
     * .value[2].f32: maximum value of the progress indicator.\n
     * .value[3].u32: color of the progress indicator, in 0xARGB format.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}, which supports five types of shapes:\n
     * 1. Rectangle:\n
     * .value[0].u32 fill color, in 0xARGB format. \n
     * .value[1].u32: stroke color, in 0xARGB format. \n
     * .value[2].f32: stroke width, in vp. \n
     * .value[3].i32: mask type.\n
     * .value[4].f32: width of the rectangle.\n
     * .value[5].f32: height of the rectangle.\n
     * .value[6].f32: width of the rounded corner of the rectangle.\n
     * .value[7].f32: height of the rounded corner of the rectangle.\n
     * .value[8].f32: radius of the top left corner of the rectangular shape.\n
     * .value[9].f32: radius of the bottom left corner of the rectangular shape.\n
     * .value[10].f32: radius of the top right corner of the rectangular shape.\n
     * .value[11].f32: radius of the bottom right corner of the rectangular shape.\n
     * 2. Circle:\n
     * .value[0].u32 fill color, in 0xARGB format. \n
     * .value[1].u32: stroke color, in 0xARGB format. \n
     * .value[2].f32: stroke width, in vp. \n
     * .value[3].i32: mask type.\n
     * .value[4].f32: width of the circle.\n
     * .value[5].f32: height of the circle.\n
     * 3. Ellipse:\n
     * .value[0].u32 fill color, in 0xARGB format. \n
     * .value[1].u32: stroke color, in 0xARGB format. \n
     * .value[2].f32: stroke width, in vp. \n
     * .value[3].i32: mask type.\n
     * .value[4].f32: width of the ellipse.\n
     * .value[5].f32: height of the ellipse.\n
     * 4. Path:\n
     * .value[0].u32 fill color, in 0xARGB format. \n
     * .value[1].u32: stroke color, in 0xARGB format. \n
     * .value[2].f32: stroke width, in vp. \n
     * .value[3].i32: mask type.\n
     * .value[4].f32: width of the path.\n
     * .value[5].f32: height of the path.\n
     * .string: command for drawing the path.\n
     * 5. Progress:\n
     * .value[0].i32: mask type.\n
     * .value[1].f32: current value of the progress indicator.\n
     * .value[2].f32: maximum value of the progress indicator.\n
     * .value[3].u32: color of the progress indicator.\n
     *
     * @ingroup Visual
     */
    NODE_MASK,
    /**
     * @brief Blends the component's background with the content of the component's child node. It is used for
     * visual composition scenarios such as overlay transparency effects and color blending. This attribute can be
     * set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: blend mode of the current component. The parameter type is {@link ArkUI_BlendMode}. The
     * default value is **ARKUI_BLEND_MODE_NONE**.\n
     * .value[1]?.i32: how the specified blend mode is applied. The parameter type is
     * {@link ArkUI_BlendApplyType}. The default value is **BLEND_APPLY_TYPE_FAST**.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: blend mode of the current component. The parameter type is {@link ArkUI_BlendMode}. The
     * default value is **ARKUI_BLEND_MODE_NONE**.\n
     * .value[1].i32: how the specified blend mode is applied. The parameter type is
     * {@link ArkUI_BlendApplyType}. The default value is **BLEND_APPLY_TYPE_FAST**. The enumerated values include:
     * **BLEND_APPLY_TYPE_FAST** (fast implementation, non-offscreen) and **BLEND_APPLY_TYPE_OFFSCREEN**
     * (offscreen implementation).\n
     *
     * @ingroup Visual
     */
    NODE_BLEND_MODE,
    /**
     * @brief Direction of the main axis within the container element. This attribute can be set, reset, and obtained
     * as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Direction of the main axis, which is used to set the arrangement direction of child components
     * in the container. The parameter type is {@link ArkUI_Direction}. The default value is **ARKUI_DIRECTION_AUTO**
     * .</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Direction of the main axis. The parameter type is {@link ArkUI_Direction}.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_DIRECTION,
    /**
     * @brief Size constraint attribute, used to restricts the size range during component layout. This attribute can
     * be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Minimum width, in vp. Value range: [0, +∞). Default value: **0**.</li>
     * <li>.value[1].f32: Maximum width, in vp. Value range: [0, +∞). Default value: no limit.</li>
     * <li>.value[2].f32: Minimum height, in vp. Value range: [0, +∞). Default value: **0**.</li>
     * <li>.value[3].f32: Maximum height, in vp. Value range: [0, +∞). Default value: no limit.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Minimum width, in vp.</li>
     * <li>.value[1].f32: Maximum width, in vp.</li>
     * <li>.value[2].f32: Minimum height, in vp.</li>
     * <li>.value[3].f32: Maximum height, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_CONSTRAINT_SIZE,
    /**
     * @brief Grayscale effect. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: grayscale conversion ratio. The value ranges from 0 to 1. The default value is **0**. For
     * example, **0.5** indicates a 50% grayscale conversion ratio.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: grayscale conversion ratio. The value ranges from 0 to 1.\n
     *
     * @ingroup Visual
     */
    NODE_GRAY_SCALE,
    /**
     * @brief Image inversion ratio. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: image inversion ratio. The value ranges from 0 to 1. The default value is **0**. For
     * example, **0.5** indicates a 50% image inversion ratio.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: image inversion ratio. The value ranges from 0 to 1.\n
     *
     * @ingroup Visual
     */
    NODE_INVERT,
    /**
     * @brief Sepia conversion ratio. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: sepia conversion ratio. The value ranges from 0 to 1. The default value is **0**. For
     * example, **0.5** indicates a 50% sepia conversion ratio.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: sepia conversion ratio. The value ranges from 0 to 1.\n
     *
     * @ingroup Visual
     */
    NODE_SEPIA,
    /**
     * @brief Contrast attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: contrast. If the value is **1**, the source image is displayed. A larger value indicates a
     * higher contrast. The default value is **1**. The value range is [0, 10). If the value is out of range, the
     * error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: contrast. The value range is [0, 10).\n
     *
     * @ingroup Visual
     */
    NODE_CONTRAST,
    /**
     * @brief Foreground color attribute, which can be set and obtained as required through APIs. The reset API has
     * no effect on this attribute, because the foreground color is an attribute type that cannot automatically
     * restore its default value, and the reset operation does not change the foreground color that has been set.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color, in 0xAARRGGBB format. For example, **0xFFFF0000** indicates red. The default value is
     * **0xFF000000**.\n
     * .value[0].i32: coloring strategy. The value is an enumerated value of {@link ArkUI_ColorStrategy}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color, in 0xARGB format.\n
     *
     * @ingroup Visual
     */
    NODE_FOREGROUND_COLOR,

    /**
     * @brief Additional offset of a component's child element relative to the component itself. This attribute can
     * be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Offset along the x-axis, in vp. Value range: (-∞, +∞). Default value: **0**.</li>
     * <li>.value[1].f32: Offset along the y-axis, in vp. Value range: (-∞, +∞). Default value: **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: X-axis offset relative to the component itself, in vp.</li>
     * <li>.value[1].f32: Y-axis offset relative to the component itself, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_OFFSET,
    /**
     * @brief Anchor of a component's child element during locating. This attribute can be set, reset, and obtained
     * as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: X-coordinate of the anchor, in vp. Value range: (-∞, +∞). Default value: **0**.</li>
     * <li>.value[1].f32: Y-coordinate of the anchor, in vp. Value range: (-∞, +∞). Default value: **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: X-coordinate of the anchor in the component's coordinate system, in vp.</li>
     * <li>.value[1].f32: Y-coordinate of the anchor in the component's coordinate system, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_MARK_ANCHOR,

    /**
     * @brief Position of the background image in the component, that is, the coordinates relative to the
     * upper left corner of the component. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: position along the x-axis, in px.</li>
     * <li>.value[1].f32: position along the y-axis, in px.</li>
     * <li>.value[2]?.i32: alignment mode. This parameter is optional. The parameter type is
     * {@link ArkUI_Alignment}. The default value is **ARKUI_ALIGNMENT_TOP_START**. This parameter is supported
     * since API version 21.</li>
     * <li>.value[3]?.i32: layout direction. This parameter is optional. The parameter type is
     * {@link ArkUI_Direction}. The default value is **ARKUI_DIRECTION_AUTO**. In most scenarios, you are advised
     * to set this parameter to **AUTO**, so that the system automatically handles the layout direction. If a fixed
     * direction is required, set this parameter to **LTR** or **RTL**. This parameter is supported since API
     * version 21.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: position along the x-axis, in px.</li>
     * <li>.value[1].f32: position along the y-axis, in px.</li>
     * <li>.value[2].i32: alignment mode. The parameter type is {@link ArkUI_Alignment}. This return value is
     * supported since API version 21.</li>
     * <li>.value[3].i32: layout direction. The parameter type is {@link ArkUI_Direction}. This return value is
     * supported since API version 21.</li>
     * </ul>
     *
     * @ingroup Background Display
     */
    NODE_BACKGROUND_IMAGE_POSITION,
    /**
     * @brief Alignment rules of the child components in the relative container. This attribute can be set, reset,
     * and obtained as required through APIs. This attribute takes effect only when the parent container is a
     * RelativeContainer.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Alignment rules of the child components in the relative container. The parameter type is
     * {@link ArkUI_AlignmentRuleOption}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Alignment rules of the child components in the relative container. The parameter type is
     * {@link ArkUI_AlignmentRuleOption}.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_ALIGN_RULES,
    /**
     * @brief Alignment mode of the child component along the cross axis of the parent container. This attribute can
     * be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Alignment mode of the child component along the cross axis of the parent container, used to
     * change the position of the child component along the cross axis. The parameter type is
     * {@link ArkUI_ItemAlignment}. The default value is **ARKUI_ITEM_ALIGNMENT_AUTO**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Alignment mode of the child component along the cross axis of the parent container. The
     * parameter type is {@link ArkUI_ItemAlignment}.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_ALIGN_SELF,
    /**
     * @brief Percentage of the parent container's remaining space that is allocated to the component. This attribute
     * can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Percentage of the parent container's remaining space that is allocated to the component. Value
     * range: [0, +∞). Default value: **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Percentage of the parent container's remaining space that is allocated to the component.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_FLEX_GROW,
    /**
     * @brief Percentage of the parent container's shrink size that is allocated to the component. This attribute can
     * be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Percentage of the parent container's shrink size that is allocated to the current component.
     * Value range: [0, +∞). Default value: **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Percentage of the parent container's shrink size that is allocated to the current
     * component.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_FLEX_SHRINK,
    /**
     * @brief Base size of the component. This attribute can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Base size of the component on the main axis of the parent container, in vp. Value range: [0, +
     * ∞). Default value: **auto**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Base size of the component on the main axis of the parent container, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_FLEX_BASIS,
    /**
     * @brief Sets the accessibility group. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Accessibility group. The value <b>1</b> means that the component and all its child components
     * form an entire selectable component.</li>
     * <li>In this case, the accessibility service will no longer be available for the content of
     * its child components.</li>
     * <li>The value is <b>1</b> or <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Accessibility group. The value <b>1</b> means that the component and all its child components
     * form an entire selectable component.</li>
     * <li>In this case, the accessibility service will no longer be available for the content of
     * its child components.</li>
     * <li>The value is <b>1</b> or <b>0</b>.</li>
     * </ul>
     *
     * @ingroup Accessibility
     * @since 12
     */
    NODE_ACCESSIBILITY_GROUP,

    /**
     * @brief Sets the accessibility text. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: accessibility text.</li>
     * </ul>
     *
     * @ingroup Accessibility
     * @since 12
     */
    NODE_ACCESSIBILITY_TEXT,

    /**
     * @brief Sets the accessibility service model. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: accessibility service model. The parameter type is {@link ArkUI_AccessibilityMode}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: accessibility service model. The parameter type is {@link ArkUI_AccessibilityMode}.</li>
     * </ul>
     *
     * @ingroup Accessibility
     * @since 12
     */
    NODE_ACCESSIBILITY_MODE,

    /**
     * @brief Sets the accessibility description.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: accessibility description.</li>
     * </ul>
     *
     * @ingroup Accessibility
     * @since 12
     */
    NODE_ACCESSIBILITY_DESCRIPTION,

    /**
     * @brief Component focus status. This attribute can be set and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Component focus status. The value **1** indicates that the component gains focus and
     * **0** indicates that the component loses focus.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Component focus status. The value **1** indicates that the component gains focus and
     * **0** indicates that the component loses focus.</li>
     * <li>Note: Setting the parameter to **0** shifts focus from the currently focused component on the current
     * level of the page to the root container.</li>
     * </ul>
     *
     * @ingroup Interaction
     */
    NODE_FOCUS_STATUS,
    /**
     * @brief Aspect ratio attribute, which can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Aspect ratio of the component, in width/height format. Value range: (0, +∞). Default value: no
     * aspect ratio constraint is set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Aspect ratio of the component, in width/height format. After being set, the component adjusts
     * its size based on this ratio.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_ASPECT_RATIO,
    /**
     * @brief Weight of the component within the **Row**, **Column**, or **Flex** layout. This attribute can be set,
     * reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: Layout weight of the component along the main axis, which determines the allocation ratio of
     * the component in the remaining space. Value range: [0, +∞). Default value: **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: Layout weight of the component along the main axis, which determines the allocation ratio of
     * the component in the remaining space.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_LAYOUT_WEIGHT,
    /**
     * @brief Display priority of the component within the **Row**, **Column**, or **Flex** (single-line) layout in
     * the layout container. This attribute can be set, reset, and obtained as required through APIs.<br>
     * When the value of **displayPriority** is greater than 1, a larger value indicates a higher priority.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: Display priority of the component in the layout container. Value range: [0, +∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: Display priority of the component in the layout container. A larger value indicates a higher
     * priority. When space is insufficient, components with higher priority are displayed first.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_DISPLAY_PRIORITY,
    /**
     * @brief Outline width of an element, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: width of the left outline, in vp.\n
     * .value[1].f32: width of the top outline, in vp.\n
     * .value[2].f32: width of the right outline, in vp.\n
     * .value[3].f32: width of the bottom outline, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: width of the left outline, in vp.\n
     * .value[1].f32: width of the top outline, in vp.\n
     * .value[2].f32: width of the right outline, in vp.\n
     * .value[3].f32: width of the bottom outline, in vp.\n
     *
     * @ingroup Visual
     */
    NODE_OUTLINE_WIDTH,
    /**
     * @brief Width attribute, which can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Width, in percentage. Value range: (0, +∞). There is no default value. When not set, the size
     * is determined by the component layout, using the width required by the child component's own content. When an
     * invalid value is set, an error code is returned.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Width, in percentage.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_WIDTH_PERCENT,
    /**
     * @brief Height attribute, which can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Height, in percentage. Value range: (0, +∞). There is no default value. When not set, the size
     * is determined by the component layout, using the height required by the child component's own content. When an
     * invalid value is set, an error code is returned.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Height, in percentage.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_HEIGHT_PERCENT,
    /**
     * @brief Padding attribute, which can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:**
     * 1: Specify the same padding for the four directions (top, bottom, left, and right).
     * <ul>
     * <li>.value[0].f32: Padding for the four directions, in percentage. The default value is **0**. Value range: [0, +
     * ∞). When an invalid value is set, the default value is used for display.</li>
     * </ul>
     * 2: Specify different padding values for the four directions (top, bottom, left, and right).
     * <ul>
     * <li>.value[0].f32: Top padding, in percentage. Default value: **0**. Value range: [0, +∞). When an invalid value
     * is set, the default value is used for display.</li>
     * <li>.value[1].f32: Right padding, in percentage. Default value: **0**. Value range: [0, +∞). When an invalid
     * value is set, the default value is used for display.</li>
     * <li>.value[2].f32: Bottom padding, in percentage. Default value: **0**. Value range: [0, +∞). When an invalid
     * value is set, the default value is used for display.</li>
     * <li>.value[3].f32: Left padding, in percentage. Default value: **0**. Value range: [0, +∞). When an invalid value
     * is set, the default value is used for display.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Top padding, in percentage.</li>
     * <li>.value[1].f32: Right padding, in percentage.</li>
     * <li>.value[2].f32: Bottom padding, in percentage.</li>
     * <li>.value[3].f32: Left padding, in percentage.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_PADDING_PERCENT,
    /**
     * @brief Margin attribute, which can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:**
     * 1: Specify the same margin for the four directions (top, bottom, left, and right).
     * <ul>
     * <li>.value[0].f32: Margin for the four directions, in percentage. Default value: **0**. Value range: [0, +∞).
     * When an invalid value is set, the default value is used for display.</li>
     * </ul>
     * 2: Specify different margins for the four directions (top, bottom, left, and right).
     * <ul>
     * <li>.value[0].f32: Top margin, in percentage. Default value: **0**. Value range: [0, +∞). When an invalid value
     * is set, the default value is used for display.</li>
     * <li>.value[1].f32: Right margin, in percentage. Default value: **0**. Value range: [0, +∞). When an invalid value
     * is set, the default value is used for display.</li>
     * <li>.value[2].f32: Bottom margin, in percentage. Default value: **0**. Value range: [0, +∞). When an invalid
     * value is set, the default value is used for display.</li>
     * <li>.value[3].f32: Left margin, in percentage. Default value: **0**. Value range: [0, +∞). When an invalid value
     * is set, the default value is used for display.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Top margin, in percentage.</li>
     * <li>.value[1].f32: Right margin, in percentage.</li>
     * <li>.value[2].f32: Bottom margin, in percentage.</li>
     * <li>.value[3].f32: Left margin, in percentage.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_MARGIN_PERCENT,

    /**
     * @brief Implicit shared element transition within a component (the transition is automatically triggered
     * when the component is inserted or deleted). This attribute can be set, reset, and obtained as required
     * through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.i32: two components bound to the shared element. The value is **1** or **0**. By default, the
     * out component does not continue to participate in the shared element animation when not yet deleted, which
     * means that it stays in its original position.\n
     * .string: ID used to set up a binding relationship. If this attribute is set to an empty string **""**, the
     * binding relationship is cleared. The value can be dynamically changed to refresh the binding relationship.
     * One ID can be bound to only two components, which function as in and out components.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: two components bound to the shared element. The value is **1** or **0**. By default, the
     * out component does not continue to participate in the shared element animation when not yet deleted, which
     * means that it stays in its original position.\n
     * .string: ID used to set up a binding relationship. If this attribute is set to an empty string **""**, the
     * binding relationship is cleared. The value can be dynamically changed to refresh the binding relationship.
     * One ID can be bound to only two components, which function as in and out components.\n
     *
     * @ingroup Animate
     */
    NODE_GEOMETRY_TRANSITION,

    /**
     * @brief Parameters of the chain in which the component is the head, used to control the distribution of
     * multiple child components along the main axis or cross axis within a RelativeContainer. It is commonly used
     * to implement scenarios where multiple components are evenly distributed along the same direction and
     * maintain fixed spacing or alignment mode. This attribute can be set, reset, and obtained as required through
     * APIs. This attribute takes effect only when the parent container is a RelativeContainer.<br>
     * 
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Direction of the chain, used to set whether the chain is arranged horizontally or vertically.
     * The value is an enumerated value of {@link ArkUI_Axis}.</li>
     * <li>.value[1].i32: Style of the chain, used to set the distribution mode of components within the chain. The
     * value is an enumerated value of {@link ArkUI_RelativeLayoutChainStyle}.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Direction of the chain. The parameter type is {@link ArkUI_Axis}.</li>
     * <li>.value[1].i32: Style of the chain. The parameter type is {@link ArkUI_RelativeLayoutChainStyle}.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_RELATIVE_LAYOUT_CHAIN_MODE,

    /**
     * @brief How the final state of the component's content is rendered during its width and height animation
     * process. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: how the final state of the component's content is rendered. The value is an enumerated
     * value of {@link ArkUI_RenderFit}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: how the final state of the component's content is rendered. The value is an enumerated
     * value of {@link ArkUI_RenderFit}.\n
     *
     * @ingroup Visual
     */
    NODE_RENDER_FIT,

    /**
     * @brief Outline color attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color of the four outlines, in 0xARGB format, for example, **0xFFFF11FF**. This parameter
     * takes effect only when **.value[0]** is passed.\n
     * .value[0].u32: color of the top outline, in 0xARGB format, for example, **0xFFFF11FF**. This parameter
     * takes effect when the four values from **.value[0]** to **.value[3]** are passed.\n
     * .value[1].u32: color of the right outline, in 0xARGB format, for example, **0xFFFF11FF**.\n
     * .value[2].u32: color of the bottom outline, in 0xARGB format, for example, **0xFFFF11FF**.\n
     * .value[3].u32: color of the left outline, in 0xARGB format, for example, **0xFFFF11FF**.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the top outline, in 0xARGB format, for example, **0xFFFF11FF**.\n
     * .value[1].u32: color of the right outline, in 0xARGB format, for example, **0xFFFF11FF**.\n
     * .value[2].u32: color of the bottom outline, in 0xARGB format, for example, **0xFFFF11FF**.\n
     * .value[3].u32: color of the left outline, in 0xARGB format, for example, **0xFFFF11FF**.\n
     *
     * @ingroup Visual
     */
    NODE_OUTLINE_COLOR,

    /**
     * @brief Size attribute, which can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 2.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Width, in vp. Value range: [0, +∞).</li>
     * <li>.value[1].f32: Height, in vp. Value range: [0, +∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Width, in vp.</li>
     * <li>.value[1].f32: Height, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_SIZE,

    /**
     * @brief Whether the component and its child components are rendered off the screen and then drawn together
     * with its parent. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the component and its child components are rendered off the screen and then drawn
     * together with its parent. The value **1** means that the component and its child components are rendered off
     * the screen and then drawn together with its parent, and **0** means the opposite. The default value is **0**.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the component and its child components are rendered off the screen and then drawn
     * together with its parent. The value **1** means that the component and its child components are rendered off
     * the screen and then drawn together with its parent, and **0** means the opposite.\n
     *
     * @ingroup Visual
     */
    NODE_RENDER_GROUP,

    /**
     * @brief Applies a color blend effect to the component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color to blend with the component, in 0xARGB format. The default value is **0x00000000**.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color to blend with the component, in 0xARGB format, for example, **0xFFFF11FF**.\n
     *
     * @ingroup Visual
     */
    NODE_COLOR_BLEND,

    /**
     * @brief Applies a foreground blur style to the component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: foreground blur style. The value is an enumerated value of {@link ArkUI_BlurStyle}.\n
     * .value[1]?.i32: color mode used for the foreground blur. The value is an enumerated value of
     * {@link ArkUI_ColorMode}. If not passed, the default value is **ARKUI_COLOR_MODE_SYSTEM**.\n
     * .value[2]?.i32: adaptive color mode used for the foreground blur. The value is an enumerated value of
     * {@link ArkUI_AdaptiveColor}.\n
     * .value[3]?.f32: blur degree. The value range is [0.0, 1.0].\n
     * .value[4]?.f32: brightness of black in the grayscale blur. The value range is [0,127]. If not passed, the
     * default value is **0**.\n
     * .value[5]?.f32: degree of darkening the white color in the grayscale blur. The value range is [0,127]. If
     * not passed, the default value is **0**.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: foreground blur style. The value is an enumerated value of {@link ArkUI_BlurStyle}.\n
     * .value[1].i32: color mode used for the foreground blur. The value is an enumerated value of
     * {@link ArkUI_ColorMode}.\n
     * .value[2].i32: adaptive color mode used for the foreground blur. The value is an enumerated value of
     * {@link ArkUI_AdaptiveColor}.\n
     * .value[3].f32: blur degree. The value range is [0.0, 1.0].\n
     * .value[4].f32: brightness of black in the grayscale blur. The value range is [0,127].\n
     * .value[5].f32: degree of darkening the white color in the grayscale blur. The value range is [0,127].\n
     *
     * @ingroup Visual
     */
    NODE_FOREGROUND_BLUR_STYLE,

    /**
     * @brief Component size and position for layout. This attribute can be set, reset, and obtained as required
     * through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: X-coordinate of the component, in px. Value range: (-∞, +∞).</li>
     * <li>.value[1].i32: Y-coordinate of the component, in px. Value range: (-∞, +∞).</li>
     * <li>.value[2].i32: Width of the component, in px. Value range: [0, +∞).</li>
     * <li>.value[3].i32: Height of the component, in px. Value range: [0, +∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: X-coordinate of the component, in px.</li>
     * <li>.value[1].i32: Y-coordinate of the component, in px.</li>
     * <li>.value[2].i32: Width of the component, in px.</li>
     * <li>.value[3].i32: Height of the component, in px.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_LAYOUT_RECT,

    /**
     * @brief Whether the component is focusable on touch. This attribute can be set, reset, and obtained as required
     * through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the component is focusable on touch. The value **1** means that the component is
     * focusable on touch, and **0** means the opposite.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the component is focusable on touch. The value **1** means that the component is
     * focusable on touch, and **0** means the opposite.</li>
     * </ul>
     *
     * @ingroup Interaction
     */
    NODE_FOCUS_ON_TOUCH,

    /**
     * @brief Border width attribute, which can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * 1: Specify the same width for the four borders.
     * <ul>
     * <li>.value[0].f32: Width for the four borders, in percentage. Value range: [0, +∞). Default value: **0**.</li>
     * </ul>
     * 2: Specify different width values for the four borders.
     * <ul>
     * <li>.value[0].f32: Width of the top border, in percentage. Value range: [0, +∞). Default value: **0**.</li>
     * <li>.value[1].f32: Width of the right border, in percentage. Value range: [0, +∞). Default value: **0**.</li>
     * <li>.value[2].f32: Width of the bottom border, in percentage. Value range: [0, +∞). Default value: **0**.</li>
     * <li>.value[3].f32: Width of the left border, in percentage. Value range: [0, +∞). Default value: **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Width of the top border, in percentage.</li>
     * <li>.value[1].f32: Width of the right border, in percentage.</li>
     * <li>.value[2].f32: Width of the bottom border, in percentage.</li>
     * <li>.value[3].f32: Width of the left border, in percentage.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_BORDER_WIDTH_PERCENT = 85,
    /**
     * @brief Border corner radius attribute, which can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * 1. Specify the same corner radius for the four borders.
     * <ul>
     * <li>.value[0].f32: Corner radius for the four borders, in percentage. Value range: [0, +∞). Default value: **0**
     * .</li>
     * </ul>
     * 2. Specify different corner radii for the four borders.
     * <ul>
     * <li>.value[0].f32: Radius of the upper left corner, in percentage. Value range: [0, +∞). Default value: **0**
     * .</li>
     * <li>.value[1].f32: Radius of the upper right corner, in percentage. Value range: [0, +∞). Default value: **0**
     * .</li>
     * <li>.value[2].f32: Radius of the lower left corner, in percentage. Value range: [0, +∞). Default value: **0**
     * .</li>
     * <li>.value[3].f32: Radius of the lower right corner, in percentage. Value range: [0, +∞). Default value: **0**
     * .</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Radius of the upper left corner, in percentage.</li>
     * <li>.value[1].f32: Radius of the upper right corner, in percentage.</li>
     * <li>.value[2].f32: Radius of the lower left corner, in percentage.</li>
     * <li>.value[3].f32: Radius of the lower right corner, in percentage.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_BORDER_RADIUS_PERCENT = 86,

    /**
     * @brief Accessible ID, which can be obtained as required through APIs.
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Accessible ID.</li>
     * </ul>
     *
     * @ingroup Accessibility
     * @since 12
     */
    NODE_ACCESSIBILITY_ID = 87,

    /**
     * @brief Define accessible actions, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: accessible action types, and uses the {@link ArkUI_AccessibilityActionType}
     * enumeration value.</li>
     * </ul>
     *
     * @ingroup Accessibility
     * @since 12
     */
    NODE_ACCESSIBILITY_ACTIONS = 88,

    /**
     * @brief Define accessible role, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: accessible role type, and uses the {@link ArkUI_NodeType} enumeration value.</li>
     * </ul>
     *
     * @ingroup Accessibility
     * @since 12
     */
    NODE_ACCESSIBILITY_ROLE = 89,

    /**
     * @brief Define accessible state, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: the parameter type is {@link ArkUI_AccessibilityState}.</li>
     * </ul>
     *
     * @ingroup Accessibility
     * @since 12
     */
    NODE_ACCESSIBILITY_STATE = 90,

    /**
     * @brief Define accessible value, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: the parameter type is {@link ArkUI_AccessibilityValue}.</li>
     * </ul>
     *
     * @ingroup Accessibility
     * @since 12
     */
    NODE_ACCESSIBILITY_VALUE = 91,
    /**
     * @brief Safe area to be expanded to. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0]?.u32: Types of the expanded safe area, which are enumerated values of {@link ArkUI_SafeAreaType}.
     * Example: **ARKUI_SAFE_AREA_TYPE_SYSTEM | ARKUI_SAFE_AREA_TYPE_CUTOUT**.</li>
     * <li>.value[1]?.u32: Types of the expanded safe area edge, which are enumerated values of
     * {@link ArkUI_SafeAreaEdge}. Example: **ARKUI_SAFE_AREA_EDGE_TOP | ARKUI_SAFE_AREA_EDGE_BOTTOM**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: Types of the expanded safe area.</li>
     * <li>.value[1].u32: Edges for expanding the safe area.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_EXPAND_SAFE_AREA = 92,

    /**
     * @brief Visible area ratio (visible area/total area of the component) threshold for invoking the visible area
     * change event of the component.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[...].f32: Threshold array. The value ranges from 0 to 1.</li>
     * <li>.object: Parameters for visible area change events. The parameter type is
     * {@link ArkUI_VisibleAreaEventOptions}.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[...].f32: Threshold array.</li>
     * <li>.object: Parameters for visible area change events. The parameter type is
     * {@link ArkUI_VisibleAreaEventOptions}.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     * @since 12
     */
    NODE_VISIBLE_AREA_CHANGE_RATIO = 93,

    /**
     * @brief Transition effect when the component is inserted or deleted. This attribute can be set and obtained
     * as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: transition effect when the component is inserted or deleted. The parameter type is
     * {@link ArkUI_TransitionEffect}. Different **TransitionEffect** values determine the animation effect type
     * when a component appears and disappears.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: transition effect when the component is inserted or deleted. The parameter type is
     * {@link ArkUI_TransitionEffect}.\n
     *
     * @ingroup Animate
     */
    NODE_TRANSITION = 94,

    /**
     * @brief Component ID. This attribute can be obtained as required through APIs.
     * The component ID is read-only and unique in a process.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for obtaining the attribute:\n
     * .value[0].i32: component ID. \n
     *
     * @deprecated since 20
     * @useinstead OH_ArkUI_NodeUtils_GetNodeUniqueId
     */
    NODE_UNIQUE_ID = 95,

    /**
     * @brief Style of the system focus box for this component.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Distance of the focus box from the component's edge. A positive number indicates the
     * outside, and a negative number indicates the inside. The value cannot be in percentage.</li>
     * <li>.value[1].f32: Width of the focus box. Negative numbers and percentages are not supported.</li>
     * <li>.value[2].u32: Color of the focus box.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     */
    NODE_FOCUS_BOX = 96,

    /**
     * @brief Moving distance limit for the component-bound click gesture. This attribute can be set as
     * required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Distance threshold within which the finger is allowed to move when a click gesture is
     * recognized, in vp. The value range is [0, +∞). If the value is less than 0, the default value is used. The
     * default value is infinite. A smaller value is suitable for scenarios requiring high click precision, and a
     * larger value is suitable for scenarios requiring high click fault tolerance.</li>
     * </ul>
     *
     * @ingroup Interaction
     */
    NODE_CLICK_DISTANCE = 97,

    /**
     * @brief Whether the focus can be placed on the component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the focus can be placed on the current component. The value **1** means that the
     * focus can be placed on the current component, and **0** means the opposite. The default value is **0**.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the focus can be placed on the current component. The value **1** means that the
     * focus can be placed on the current component, and **0** means the opposite.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     * @since 14
     */
    NODE_TAB_STOP = 98,

    /**
     * @brief Background blur effect. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: background blur radius. The value range is [0, +∞). If the value is out of range, the
     * error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned. Unit: px. Default value: **0.0**.\n
     * .value[1]?.f32: brightness of black in the grayscale blur. The value range is [0, 127]. If this parameter
     * is not passed, the default value is **0**. Pass this parameter when the degree to which black areas are
     * brightened in the blur effect needs to be finely adjusted.\n
     * .value[2]?.f32: degree of darkening the white color in the grayscale blur. The value range is [0, 127].
     * If this parameter is not passed, the default value is **0**. Pass this parameter when the degree to which
     * white areas are darkened in the blur effect needs to be finely adjusted.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: background blur radius. The value range is [0, +∞). Unit: px.\n
     * .value[1].f32: brightness of black in the grayscale blur. The value range is [0, 127].\n
     * .value[2].f32: degree of darkening the white color in the grayscale blur. The value range is [0, 127].\n
     *
     * @ingroup Visual
     * @since 15
     */
    NODE_BACKDROP_BLUR = 99,

    /**
     * @brief Resizable attribute of a background image when it is stretched. This attribute can be set, reset,
     * and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: pixel value of the image that remains unchanged when the left side of the image is
     * stretched, in vp. Default value: **0**.</li>
     * <li>.value[1].f32: pixel value of the image that remains unchanged when the top side of the image is
     * stretched, in vp. Default value: **0**.</li>
     * <li>.value[2].f32: pixel value of the image that remains unchanged when the right side of the image is
     * stretched, in vp. Default value: **0**.</li>
     * <li>.value[3].f32: pixel value of the image that remains unchanged when the bottom side of the image is
     * stretched, in vp. Default value: **0**.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: pixel value of the image that remains unchanged when the left side of the image is
     * stretched, in vp.</li>
     * <li>.value[1].f32: pixel value of the image that remains unchanged when the top side of the image is
     * stretched, in vp.</li>
     * <li>.value[2].f32: pixel value of the image that remains unchanged when the right side of the image is
     * stretched, in vp.</li>
     * <li>.value[3].f32: pixel value of the image that remains unchanged when the bottom side of the image is
     * stretched, in vp.</li>
     * </ul>
     *
     * @ingroup Background Display
     *
     * @since 19
     */
    NODE_BACKGROUND_IMAGE_RESIZABLE_WITH_SLICE = 100,

    /**
     * @brief Next focus node.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Focus movement direction, as defined in {@link ArkUI_FocusMove}.</li>
     * <li>.object: Next focus node. The parameter type is {@link ArkUI_NodeHandle}.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     * @since 18
     */
    NODE_NEXT_FOCUS = 101,

    /**
     * @brief Threshold ratio for triggering a visible area change event.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Parameters for visible area change events. The parameter type is
     * {@link ArkUI_VisibleAreaEventOptions}.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Parameters for visible area change events. The parameter type is
     * {@link ArkUI_VisibleAreaEventOptions}.</li>
     * <li>Note: The visible area change callback is not a real-time callback. The actual callback interval may differ
     * from the expected interval due to system load and other factors. The interval between two visible area change
     * callbacks will not be less than the expected update interval. If the provided expected interval is too short,
     * the actual callback interval will be determined by the system load. By default, the interval threshold of the
     * visible area change callback includes 0. This means that, if the provided threshold is [0.5], the effective
     * threshold will be [0.0, 0.5].</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     * @since 17
     */
    NODE_VISIBLE_AREA_APPROXIMATE_CHANGE_RATIO = 102,

    /**
     * @brief Component translation, with support for percentage-based translation parameters. This attribute is
     * mutually exclusive with **NODE_TRANSLATE**. A component can use only one translation attribute. When both are
     * set, the latter overrides the former. This attribute can be set, reset, and obtained as required through APIs.\n
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: distance to translate along the x-axis. The default unit is percentage.
     * The unit is vp only if value[3] exists and value[3] is 0. The default value of value[0] is <b>0</b>.\n
     * .value[1].f32: distance to translate along the y-axis. The default unit is percentage.
     * The unit is vp only if value[4] exists and value[4] is 0. The default value of value[1] is <b>0</b>.\n
     * .value[2].f32: distance to translate along the z-axis, in vp. The default value is <b>0</b>.\n
     * .value[3]?.i32: Whether the translation distance along the x-axis is specified as a percentage.
     *  The value can be 0 or 1. When the value is 1, it is specified as a percentage.
     *  For example, value[0].f32=0.1 and value[3].i32=1 indicates a 10% shift in the x direction.
     *  The default value is <b>1</b>.\n
     * .value[4]?.i32: Whether the translation distance along the y-axis is specified as a percentage.
     *  The value can be 0 or 1. When the value is 1, it is specified as a percentage.
     *  For example, value[1].f32=0.1 and value[4].i32=1 indicates a 10% shift in the y direction.
     *  The default value is <b>1</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: distance to translate along the x-axis. The unit depends on value[3].\n
     * .value[1].f32: distance to translate along the y-axis. The unit depends on value[4].\n
     * .value[2].f32: distance to translate along the z-axis. The unit is vp.\n
     * .value[3].i32: Whether the unit of the X-axis translation distance is in percentage. When value[3].i32 is 0,
     *  the unit of the X-axis translation distance is vp; when value[3].i32 is 1, the unit of the X-axis translation
     *  distance is percentage;\n
     * .value[4].i32: Whether the unit of the Y-axis translation distance is in percentage. When value[4].i32 is 0,
     *  the unit of the Y-axis translation distance is vp; when value[4].i32 is 1, the unit of the Y-axis translation
     *  distance is percentage;\n
     *
     * @ingroup Visual
     * @since 20
     */
    NODE_TRANSLATE_WITH_PERCENT = 103,

    /**
     * @brief Component rotation with multi-axis angle control. This attribute can be reset and obtained as required
     * through APIs. It is mutually exclusive with **NODE_ROTATE**. A component can use only one rotation attribute.
     * When both are set, the latter overrides the former.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: x-axis rotation angle. The default value is <b>0</b>. \n
     * .value[1].f32: y-axis rotation angle. The default value is <b>0</b>. \n
     * .value[2].f32: z-axis rotation angle. The default value is <b>0</b>. \n
     * .value[3].f32: perspective distance from the viewpoint to the z=0 plane, in px. The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: x-axis rotation angle. The default value is <b>0</b>.
     * .value[1].f32: y-axis rotation angle. The default value is <b>0</b>. \n
     * .value[2].f32: z-axis rotation angle. The default value is <b>0</b>. \n
     * .value[3].f32: perspective distance from the viewpoint to the z=0 plane, in px. The default value is <b>0</b>. \n
     *
     * @ingroup Visual
     * @since 20
     */
    NODE_ROTATE_ANGLE = 104,

    /**
     * @brief Width layout policy of the component. This attribute can be set, reset, and obtained as required
     * through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Width layout policy of the component. The parameter type is {@link ArkUI_LayoutPolicy}.
     * Default value: **ARKUI_LAYOUT_POLICY_WRAP_CONTENT**. When an invalid value is set, the default value is used for
     * display.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Width layout policy of the component. The parameter type is {@link ArkUI_LayoutPolicy}.
     * Default value: **ARKUI_LAYOUT_POLICY_WRAP_CONTENT**. When an invalid value is set, the default value is
     * used.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 21
     */
    NODE_WIDTH_LAYOUTPOLICY = 105,

    /**
     * @brief Height layout policy of the component. This attribute can be set, reset, and obtained as required
     * through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Height layout policy of the component. The parameter type is {@link ArkUI_LayoutPolicy}.
     * Default value: **ARKUI_LAYOUT_POLICY_WRAP_CONTENT**. When an invalid value is set, the default value is used for
     * display.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Height layout policy of the component. The parameter type is {@link ArkUI_LayoutPolicy}.
     * Default value: **ARKUI_LAYOUT_POLICY_WRAP_CONTENT**. When an invalid value is set, the default value is used for
     * display.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 21
     */
    NODE_HEIGHT_LAYOUTPOLICY = 106,

    /**
     * @brief Position of the component relative to the edges of the container's content area. This attribute can be
     * set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Position of the component relative to the edges of the container's content area. The parameter type
     * is {@link ArkUI_PositionEdges}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Position of the component relative to the edges of the container's content area. The parameter type
     * is {@link ArkUI_PositionEdges}.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 21
     */
    NODE_POSITION_EDGES = 107,

    /**
     * @brief Whether to enable color inversion of a component. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: Whether to enable color inversion. The value 1 indicates to enable color inversion, and
     * **0** indicates the opposite.\n
     *
     * @since 21
     */
    NODE_ALLOW_FORCE_DARK = 108,

    /**
     * @brief Pixel rounding policy of the component, used to avoid issues such as visual aliasing when the component
     * is rendered at a scaled size or non-integer-pixel position. This attribute can be set, reset, and obtained as
     * required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Pixel rounding policy of the component. The parameter type is {@link ArkUI_PixelRoundPolicy}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Pixel rounding policy of the component. The parameter type is {@link ArkUI_PixelRoundPolicy}.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 21
     */
    NODE_PIXEL_ROUND = 109,

    /**
     * @brief Whether the component enables the default click sound effect. This enumerated value takes effect only on
     * TVs. If the default click sound effect is enabled on other devices, the sound effect is not played. Whether the
     * sound can be played depends on the sound settings of the device. For example, the sound effect is not played in
     * mute mode.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the component enables the default click sound effect. The value **1** indicates that
     * the default click sound effect is enabled, and the value **0** indicates the opposite. The default value is
     * **1**.
     * </li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the component enables the default click sound effect. The value **1** indicates that
     * the default click sound effect is enabled, and the value **0** indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     * @since 24
     */
    NODE_ENABLE_CLICK_SOUND_EFFECT = 110,

    /**
     * @brief Motion path of the component. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute: \n
     * .object indicates a pointer to the ArkUI_MotionPathOptions. The parameter type is
     * {@link ArkUI_MotionPathOptions}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}: \n
     * .object indicates a pointer to the ArkUI_MotionPathOptions. The parameter type is
     * {@link ArkUI_MotionPathOptions}. \n
     *
     * @ingroup Animate
     * @since 23
     */
    NODE_MOTION_PATH = 111,

    /**
     * @brief Hover effect applied when the component is hovered over. This attribute can be set, reset, and obtained
     * as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Hover effect applied when the component is hovered over. The parameter type is
     * {@link ArkUI_HoverEffect}. The default value is **ARKUI_HOVER_EFFECT_AUTO**.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Hover effect applied when the component is hovered over. The parameter type is
     * {@link ArkUI_HoverEffect}.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     * @since 23
     */
    NODE_HOVER_EFFECT = 112,

    /**
     * @brief Sets the container as a focus group with the specified identifier. This attribute can be set, reset, and
     * obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: Focus scope identifier.</li>
     * <li>.value[0].i32: Whether the scope is a focus group. The default value is **0**. The value can be **1** or **
     * 0**. The value **1** indicates that the component is set as a focus group, and the value **0** indicates that
     * the opposite.</li>
     * <li>.value[1].i32: Whether arrow keys can move focus from inside the focus group to outside. This setting only
     * takes effect when **isGroup** is **true**. The default value is **1**. The value can be **1** or **0**. The
     * value **1** indicates that arrow keys can move focus from inside the focus group to outside, and the value **0**
     * indicates the opposite.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: Focus scope identifier.</li>
     * <li>.value[0].i32: Whether the scope is a focus group. The default value is **0**. The value can be **1** or **
     * 0**. The value **1** indicates that the component is set as a focus group, and the value **0** indicates that
     * the opposite.</li>
     * <li>.value[1].i32: Whether arrow keys can move focus from inside the focus group to outside. This setting only
     * takes effect when **isGroup** is **true**. The default value is **1**. The value can be **1** or **0**. The
     * value **1** indicates that arrow keys can move focus from inside the focus group to outside, and the value **0**
     * indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     * @since 23
     */
    NODE_FOCUS_SCOPE_ID = 113,

    /**
     * @brief Component focus priority within a specific focus scope. This attribute can be set, reset, and obtained
     * as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: Focus scope identifier.</li>
     * <li>.value[0].i32: Focus priority within the focus scope. The parameter type is {@link ArkUI_FocusPriority}.
     * The default value is **ARKUI_FOCUS_PRIORITY_AUTO**.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: Focus scope identifier.</li>
     * <li>.value[0].i32: Focus priority within the focus scope. The parameter type is {@link ArkUI_FocusPriority}.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     * @since 23
     */
    NODE_FOCUS_SCOPE_PRIORITY = 114,

    /**
     * @brief Distance threshold for click events. This attribute can be set, reset, and obtained as required
     * through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Movement threshold for click events. If the value specified is less than or equal
     * to 0, it will be converted to the default value. The value range is (0, +∞). The default value is
     * **+∞**. The unit is vp.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Movement threshold for click events.</li>
     * <li>Note: If finger movement exceeds the preset distance limit, click event recognition will fail.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     * @since 23
     */
    NODE_ON_CLICK_EVENT_DISTANCE_THRESHOLD = 115,

    /**
     * @brief Component event response region. This attribute can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.data[0].i32: Event tool type for the response region. The parameter type is
     * {@link ArkUI_ResponseRegionSupportedTool}. The default value is **ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_ALL**.</li>
     * <li>.data[1].f32: X coordinate of the touch point relative to the upper left corner of the component, in vp.
     * The default value is **0.0**.</li>
     * <li>.data[2].f32: Y coordinate of the touch point relative to the upper left corner of the component, in vp.
     * The default value is **0.0**.</li>
     * <li>.data[3].f32: Width of the response region, in percentage. The default value is **100.0**.</li>
     * <li>.data[4].f32: Height of the response region, in percentage. The default value is **100.0**.</li>
     * <li>.data[5...].f32: Multiple response regions that can be set. The sequence of the parameters is the same as
     * the preceding.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.data[0].i32: Event tool type for the response region. The parameter type is
     * {@link ArkUI_ResponseRegionSupportedTool}. The default value is **ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_ALL**.</li>
     * <li>.data[1].f32: X coordinate of the touch point relative to the upper left corner of the component, in vp.
     * The default value is **0.0**.</li>
     * <li>.data[2].f32: Y coordinate of the touch point relative to the upper left corner of the component, in vp.
     * The default value is **0.0**.</li>
     * <li>.data[3].f32: Width of the response region, in percentage. The default value is **100.0**.</li>
     * <li>.data[4].f32: Height of the response region, in percentage. The default value is **100.0**.</li>
     * <li>.data[5...].f32: Multiple response regions that can be set. The sequence of the parameters is the same as
     * the preceding.</li>
     * <li>Note: During configuration, the data array can contain any number of values (all will be accepted), but only
     * 20 values can be retrieved. The order of the retrieved data array may be different from that of the
     * settings.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     * @since 23
     */
    NODE_RESPONSE_REGION_LIST = 116,

    /**
     * @brief Event monopolization attribute, which can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether event monopolization is set for the component. The value can be **1** or **0**. The
     * value **1** indicates that event monopolization is set for the component, and the value **0** indicates the
     * opposite.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether event monopolization is set for the component. The value can be **1** or **0**. The
     * value **1** indicates that event monopolization is set for the component, and the value **0** indicates the
     * opposite.</li>
     * </ul>
     *
     * @ingroup Interaction
     *
     * @since 23
     */
    NODE_MONOPOLIZE_EVENTS = 117,

    /**
     * @brief Layout location of components that have formed a chain when the parent component is a RelativeContainer.
     * This attribute is used to control the proportion of space occupied by each component in the chain along the
     * chain direction, commonly applied to scenarios where components in the same chain are allocated remaining
     * space by weight ratio. This attribute can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 2.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Layout weight of the component in the horizontal direction. Default value: **0**. A larger
     * weight value indicates a larger proportion of space the component occupies in the chain. Value range: [0, +∞).
     * When an invalid value is set, the default value is used for display.</li>
     * <li>.value[1].f32: Layout weight of the component in the vertical direction. Default value: **0**. A larger
     * weight value indicates a larger proportion of space the component occupies in the chain. Value range: [0, +∞).
     * When an invalid value is set, the default value is used for display.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Layout weight of the component in the horizontal direction. A larger weight value indicates a
     * larger proportion of space the component occupies in the chain.</li>
     * <li>.value[1].f32: Layout weight of the component in the vertical direction. A larger weight value indicates a
     * larger proportion of space the component occupies in the chain.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_CHAIN_WEIGHT = 118,

    /**
     * @brief Safe area to be ignored when expanding the layout of the component, allowing components to extend into
     * system UI areas such as the system status bar and navigation bar. This attribute is commonly used in scenarios
     * requiring full-screen display, such as immersive video playback, full-screen games, and image viewers. This
     * attribute can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 2.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: Type of the safe area. The parameter type is {@link ArkUI_LayoutSafeAreaType}. The default
     * value is **ARKUI_LAYOUT_SAFE_AREA_TYPE_SYSTEM**. If an invalid value is set, the default value is used.</li>
     * <li>.value[1].u32: Edges for expanding the safe area. The parameter type is {@link ArkUI_LayoutSafeAreaEdge}. The
     * default value is **ARKUI_LAYOUT_SAFE_AREA_EDGE_ALL**. Example:
     * **ARKUI_LAYOUT_SAFE_AREA_EDGE_TOP | ARKUI_LAYOUT_SAFE_AREA_EDGE_BOTTOM**. If an invalid value is set, the default
     * value is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: Type of the safe area. The parameter type is {@link ArkUI_LayoutSafeAreaType}.</li>
     * <li>.value[1].u32: Edges for expanding the safe area. The parameter type is {@link ArkUI_LayoutSafeAreaEdge}
     * .</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_IGNORE_LAYOUT_SAFE_AREA = 119,

    /**
     * @brief Length of the dashed line when the border style is set to dashed (**ArkUI_BorderStyle** is set to
     * **ARKUI_BORDER_STYLE_DASHED**). The default value is the border width value of the **NODE_BORDER_WIDTH**
     * attribute. This attribute takes effect only when the border style is dashed. This attribute can be set, reset,
     * and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Length of the dashed line on the top border, in vp. Value range: [0, +∞). Default value: the
     * border width value of the **NODE_BORDER_WIDTH** attribute. When an invalid value is set, the default dashed line
     * effect is displayed.</li>
     * <li>.value[1].f32: Length of the dashed line on the right border, in vp. Value range: [0, +∞). Default value: the
     * border width value of the **NODE_BORDER_WIDTH** attribute. When an invalid value is set, the default dashed line
     * effect is displayed.</li>
     * <li>.value[2].f32: Length of the dashed line on the bottom border, in vp. Value range: [0, +∞). Default value:
     * the border width value of the **NODE_BORDER_WIDTH** attribute. When an invalid value is set, the default dashed
     * line effect is displayed.</li>
     * <li>.value[3].f32: Length of the dashed line on the left border, in vp. Value range: [0, +∞). Default value: the
     * border width value of the **NODE_BORDER_WIDTH** attribute. When an invalid value is set, the default dashed line
     * effect is displayed.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Length of the dashed line on the top border, in vp.</li>
     * <li>.value[1].f32: Length of the dashed line on the right border, in vp.</li>
     * <li>.value[2].f32: Length of the dashed line on the bottom border, in vp.</li>
     * <li>.value[3].f32: Length of the dashed line on the left border, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_DASH_WIDTH = 120,

    /**
     * @brief Gap between dashes on the dashed line when the border style is set to dashed (**ArkUI_BorderStyle** is
     * set to **ARKUI_BORDER_STYLE_DASHED**). The default value is the border width value of the **NODE_BORDER_WIDTH**
     * attribute. This attribute takes effect only when the border style is dashed. This attribute can be set, reset,
     * and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     * **size** in the return value {@link ArkUI_AttributeItem} is invalid, and the actual returned **value** array
     * length is always 4.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Gap between dashes on the dash line of the top border, in vp. Value range: [0, +∞). Default
     * value: the border width value of the **NODE_BORDER_WIDTH** attribute. When an invalid value is set, the default
     * dashed line effect is displayed.</li>
     * <li>.value[1].f32: Gap between dashes on the dash line of the right border, in vp. Value range: [0, +∞). Default
     * value: the border width value of the **NODE_BORDER_WIDTH** attribute. When an invalid value is set, the default
     * dashed line effect is displayed.</li>
     * <li>.value[2].f32: Gap between dashes on the dash line of the bottom border, in vp. Value range: [0, +∞). Default
     * value: the border width value of the **NODE_BORDER_WIDTH** attribute. When an invalid value is set, the default
     * dashed line effect is displayed.</li>
     * <li>.value[3].f32: Gap between dashes on the dash line of the left border, in vp. Value range: [0, +∞). Default
     * value: the border width value of the **NODE_BORDER_WIDTH** attribute. When an invalid value is set, the default
     * dashed line effect is displayed.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Gap between dashes on the dash line of the top border, in vp.</li>
     * <li>.value[1].f32: Gap between dashes on the dash line of the right border, in vp.</li>
     * <li>.value[2].f32: Gap between dashes on the dash line of the bottom border, in vp.</li>
     * <li>.value[3].f32: Gap between dashes on the dash line of the left border, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_DASH_GAP = 121,

    /**
     * @brief Alignment rule of the child components in the **Stack** container. This attribute can be set, reset,
     * and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Alignment rule of the child components in the **Stack** container, determining the position of
     * child components in the **Stack** container. The parameter type is {@link ArkUI_LocalizedAlignment}. The default
     * value is **ARKUI_LOCALIZED_ALIGNMENT_CENTER**. When an invalid value is set, the default value is used for
     * display.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Alignment rule of the child components in the **Stack** container. The parameter type is
     * {@link ArkUI_LocalizedAlignment}.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_LAYOUT_GRAVITY = 122,

    /**
     * @brief Mode for drawing rounded corners of the component. This attribute can be set, reset, and obtained as
     * required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Mode for rendering rounded corners of the component, which affects the rendering effect and
     * performance of rounded corners. The parameter type is {@link ArkUI_RenderStrategy}. The default value is
     * **ARKUI_RENDERSTRATEGY_FAST**. In FAST mode, rounded corners are directly clipped, prioritizing rendering
     * performance. In OFFSCREEN mode, offscreen rendering is used to optimize the rounded corner effect, which may
     * affect performance. When an invalid value is set, the default value is used for display.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Mode for rendering rounded corners of the component. The parameter type is
     * {@link ArkUI_RenderStrategy}.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_BORDER_RADIUS_TYPE = 123,

    /**
     * @brief Inspector label, which helps you distinguish nodes of the same type to improve development, analysis,
     * and debugging efficiency. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: content of the inspector label. If a null pointer is passed, the local call is invalid. An empty
     * string is supported.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: content of the inspector label.\n
     * \n
     * @since 26.0.0
     */
    NODE_INSPECTOR_LABEL = 126,

    /**
     * @brief {@link NODE_ID} of the next focus component for accessibility of this component. After the node ID of
     * the component is set, the accessibility service searches for the component whose node ID is the same as that
     * of the next focus component on the current page. If no such component exists, the setting is invalid. This
     * attribute can be set, reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: accessibility next focus ID.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: accessibility next focus ID.</li>
     * </ul>
     *
     * @ingroup Accessibility
     * @since 26.0.0
     */
    NODE_ACCESSIBILITY_NEXT_FOCUS_ID = 124,

    /**
     * @brief Default focus flag for accessibility to find the default focus component. This attribute can be set,
     * reset, and obtained as required through APIs.<br>
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the return
     * value **ArkUI_AttributeItem** are as follows.<br>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Accessibility default focus. The value <b>1</b> means that the component is defined as
     * default focus in accessibility services.</li>
     * <li>The value is <b>1</b> or <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Accessibility default focus. The value <b>1</b> means that the component is defined
     * as default focus in accessibility services.</li>
     * <li>The value is <b>1</b> or <b>0</b>.</li>
     * </ul>
     *
     * @ingroup Accessibility
     * @since 26.0.0
     */
    NODE_ACCESSIBILITY_DEFAULT_FOCUS = 125,

    /**
     * @brief System material attribute, which can be set, reset, and obtained as required through APIs.
     * Only devices that support systemMaterial can use this attribute. Otherwise, when setting this attribute,
     * the error code {@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} will be returned.
     * Whether a device supports materials can be determined by calling
     * {@link OH_ArkUI_NativeModule_GetSystemMaterialSupported}.
     * The material effect behaves differently on devices with different level of computing powers.
     * The level is defined by {@link ArkUI_MaterialLevel}, which can be obtained by
     * {@link OH_ArkUI_NativeModule_GetGlobalMaterialLevel}.
     * On devices with the computing power level of ARKUI_MATERIAL_LEVEL_SMOOTH, it affects attributes such as the
     * backgroundColor, borderWidth, borderColor, shadow.
     * On devices with the computing power levels of ARKUI_MATERIAL_LEVEL_EXQUISITE or ARKUI_MATERIAL_LEVEL_GENTLE,
     * it affects shadow attribute and adds a filter effect at the system material layer, which can produce an effect
     * similar to glass.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: system material object. The parameter type is {@link ArkUI_ImmersiveMaterialHandle}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: system material object. The parameter type is {@link ArkUI_ImmersiveMaterialHandle}.\n
     * The ArkUI_ImmersiveMaterialHandle object of the return value is a pointer to static member, so do not release
     * the return object by calling {@link OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy}.\n
     *
     * @ingroup Visual
     * @since 26.0.0
     */
    NODE_SYSTEM_MATERIAL = 127,

    /**
     * @brief Defines the 3D transform attribute, which sets the 3D transformation matrix of the component.
     * When 3D transformation with the perspective effect is involved, the display effect of
     * {@link NODE_TRANSFORM} may be incorrect. In this case, this attribute is recommended.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0...15].f32: 16 floating-point numbers, indicating a 4x4 transformation matrix.
     * The array length must be <b>16</b>.</li>
     * <li>.object: pointer to an {@link ArkUI_Matrix4} object, indicating a 4x4 transformation matrix.
     * Either .value or .object is used to set the matrix. If both are set at the same time, .value takes priority.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0...15].f32: 16 floating-point numbers, indicating the current 3D transformation matrix.</li>
     * </ul>
     *
     * @ingroup Visual
     * @since 26.0.1
     */
    NODE_TRANSFORM_3D = 128,

    /**
     * @brief Defines the linear gradient blur attribute, which can be set, reset, and obtained
     * as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: linear gradient blur options object. The parameter type is
     * {@link OH_ArkUI_LinearGradientBlurOptions}*.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: linear gradient blur options object. The type is
     * {@link OH_ArkUI_LinearGradientBlurOptions}*. The object is an internal static object;
     * do not release it by calling {@link OH_ArkUI_NativeModule_LinearGradientBlurOptions_Destroy}.
     * When the attribute is not set or has been reset, the returned object contains default values
     * (blurRadius = 0, fractionStops = {0.0, 0.0, 0.0, 1.0}, direction =
     * {@link OH_ARKUI_LINEAR_GRADIENT_BLUR_DIRECTION_BOTTOM}).</li>
     * </ul>
     *
     * @ingroup Visual
     * @since 26.2.0
     */
    NODE_LINEAR_GRADIENT_BLUR = 129,

    /**
     * @brief Defines the text content attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: text content.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: text content.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT,
    /**
     * @brief Font color attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: font color, in 0xARGB format. For example, **0xFFFF0000** indicates red.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: font color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_FONT_COLOR,
    /**
     * @brief Font size attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: font size, in fp. Value range: [0, +∞). If a negative value is passed, the setting does
     * not take effect. Default value: **16fp**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: font size, in fp.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_FONT_SIZE,
    /**
     * @brief Font style attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: font style. The value is an enumerated value of {@link ArkUI_FontStyle}. The default
     * value is <b>ARKUI_FONT_STYLE_NORMAL</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: font style. The value is an enumerated value of {@link ArkUI_FontStyle}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_FONT_STYLE,
    /**
     * @brief Font weight attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: font weight. The value is an enumerated value of {@link ArkUI_FontWeight}. A larger
     * value indicates a bolder font. The default value is <b>ARKUI_FONT_WEIGHT_NORMAL</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: font weight. The value is an enumerated value of {@link ArkUI_FontWeight}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_FONT_WEIGHT,
    /**
     * @brief Text line height attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: line height, in fp. Value range: [0, +∞). If a negative value is passed, the setting
     * does not take effect.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: line height, in fp.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_LINE_HEIGHT,
    /**
     * @brief Text decorative line style and its color. This attribute can be set, reset, and obtained as required
     * through APIs. This attribute is suitable for adding text decoration effects, such as underlines for links,
     * strikethroughs for deleted content, or overlines for emphasis.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: text decorative line type. The value is an enumerated value of
     * {@link ArkUI_TextDecorationType}. Default value: <b>ARKUI_TEXT_DECORATION_TYPE_NONE</b>, indicating no
     * decorative line.</li>
     * <li>.value[1]?.u32: text decorative line color, in 0xARGB format. For example, **0xFFFF0000** indicates
     * red. This parameter is optional. Default value: <b>0xFF000000</b>, indicating black.</li>
     * <li>.value[2]?.i32: text decorative line style. The value is an enumerated value of
     * {@link ArkUI_TextDecorationStyle}. Default value: <b>ARKUI_TEXT_DECORATION_STYLE_SOLID</b>, indicating a
     * solid decorative line.</li>
     * <li>.value[3]?.f32: thickness of the text decorative line. This parameter is optional. The default value is
     * <b>1.0</b>. The value range is [0, +∞). If a negative value is passed, the setting does not take effect.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: text decorative line type. The value is an enumerated value of
     * {@link ArkUI_TextDecorationType}.</li>
     * <li>.value[1].u32: text decorative line color, in 0xARGB format.</li>
     * <li>.value[2].i32: text decorative line style. The value is an enumerated value of
     * {@link ArkUI_TextDecorationStyle}.</li>
     * <li>.value[3].f32: thickness of the text decorative line.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_DECORATION,
    /**
     * @brief Text case attribute, which can be set, reset, and obtained as required through APIs. This attribute is
     * suitable for controlling the text display format, such as automatically capitalizing titles or formatting
     * user input to a uniform case.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: text case. The parameter type is {@link ArkUI_TextCase}. The default value is
     * <b>ARKUI_TEXT_CASE_NORMAL</b>, which indicates that the original case is retained.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: text case. The parameter type is {@link ArkUI_TextCase}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_CASE,
    /**
     * @brief Letter spacing attribute, which can be set, reset, and obtained as required through APIs. This
     * attribute is suitable for adjusting text layout effects, such as setting title letter spacing to enhance
     * visual effects or adjusting the layout aesthetics of special text styles.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: letter spacing, in fp. Value range: (-∞, +∞). When the value is negative, the text is
     * compressed. If the negative value is too small, the component content area size is compressed to 0, causing
     * the content to be undisplayable.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: letter spacing, in fp.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_LETTER_SPACING,
    /**
     * @brief Maximum number of lines in the text. This attribute can be set, reset, and obtained as required through
     * APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: maximum number of lines. Value range: [0, +∞). If a negative value is passed, the setting
     * does not take effect.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: maximum number of lines.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_MAX_LINES,
    /**
     * @brief Horizontal alignment mode of the text. This attribute can be set, reset, and obtained as required
     * through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: horizontal alignment mode of the text. The value is an enumerated value of
     * {@link ArkUI_TextAlignment}. The default value is <b>ARKUI_TEXT_ALIGNMENT_START</b>, which indicates
     * alignment with the start edge.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: horizontal alignment mode of the text. The value is an enumerated value of
     * {@link ArkUI_TextAlignment}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_ALIGN,
    /**
     * @brief Text overflow attribute, which can be set, reset, and obtained as required through APIs. This attribute
     * is suitable for scenarios where text content exceeds the display area, such as using an ellipsis for a
     * single-line title or truncating card content.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: display mode when the text is too long. The value is an enumerated value of
     * {@link ArkUI_TextOverflow}. The default value is <b>ARKUI_TEXT_OVERFLOW_NONE</b>, which indicates the text is
     * displayed without clipping when it exceeds the limit.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: display mode when the text is too long. The value is an enumerated value of
     * {@link ArkUI_TextOverflow}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_OVERFLOW,
    /**
     * @brief Font family attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: font string. Multiple fonts are separated by commas (,). The system default font is used when
     * no value is passed.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: font string. Multiple fonts are separated by commas (,).</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_FONT_FAMILY,
    /**
     * @brief Copy option attribute, which can be set, reset, and obtained as required through APIs. This attribute
     * is suitable for controlling text copy and paste behavior, such as prohibiting copying in a password input
     * box or protecting sensitive information.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: copy options. The parameter type is {@link ArkUI_CopyOptions}. The default value is
     * <b>ARKUI_COPY_OPTIONS_NONE</b>, which indicates that copying is not supported.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: copy options. The parameter type is {@link ArkUI_CopyOptions}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_COPY_OPTION,
    /**
     * @brief Text baseline offset attribute, which can be set, reset, and obtained as required through APIs. This
     * attribute is suitable for adjusting the text baseline position, such as adjusting the offset when displaying
     * superscripts and subscripts, or achieving precise alignment between text and images in mixed layouts.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: baseline offset, in fp. Default value: <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: baseline offset, in fp.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_BASELINE_OFFSET,
    /**
     * @brief Text shadow attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: blur radius of the shadow, in vp. Value range: [0, +∞). The default value is <b>0</b>,
     * indicating no blur effect.</li>
     * <li>.value[1].i32: shadow type. The parameter type is {@link ArkUI_ShadowType}. The default value is
     * <b>ARKUI_SHADOW_TYPE_COLOR</b>, indicating a color shadow.</li>
     * <li>.value[2].u32: shadow color, in 0xARGB format. For example, **0xFFFF0000** indicates red.</li>
     * <li>.value[3].f32: offset of the shadow along the x-axis, in vp.</li>
     * <li>.value[4].f32: offset of the shadow along the y-axis, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: blur radius of the shadow, in vp.</li>
     * <li>.value[1].i32: shadow type. The parameter type is {@link ArkUI_ShadowType}.</li>
     * <li>.value[2].u32: shadow color, in 0xARGB format.</li>
     * <li>.value[3].f32: offset of the shadow along the x-axis, in vp.</li>
     * <li>.value[4].f32: offset of the shadow along the y-axis, in vp.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_TEXT_SHADOW,
    /**
     * @brief Minimum font size attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: minimum font size, in fp. Value range: [0, +∞). If a negative value is passed, the
     * setting does not take effect.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: minimum font size, in fp.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_MIN_FONT_SIZE,

    /**
     * @brief Maximum font size attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: maximum font size, in fp. Value range: [0, +∞). If a negative value is passed, the
     * setting does not take effect.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: maximum font size, in fp.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_MAX_FONT_SIZE,

    /**
     * @brief Text style attribute, which can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string?: font family. This parameter is optional. Use commas (,) to separate multiple fonts. The system
     * default font is used when this parameter is not passed.</li>
     * <li>.value[0].f32: text size, in fp. Value range: [0, +∞). If a negative value is passed, the setting does
     * not take effect.</li>
     * <li>.value[1]?.i32: font weight. This parameter is optional. The parameter type is {@link ArkUI_FontWeight}.
     * A larger value indicates a bolder font. Default value: <b>ARKUI_FONT_WEIGHT_NORMAL</b>.</li>
     * <li>.value[2]?.i32: font style. This parameter is optional. The parameter type is {@link ArkUI_FontStyle}.
     * Default value: <b>ARKUI_FONT_STYLE_NORMAL</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: font family. Use commas (,) to separate multiple fonts.</li>
     * <li>.value[0].f32: text size, in fp. Value range: [0, +∞).</li>
     * <li>.value[1].i32: font weight. The parameter type is {@link ArkUI_FontWeight}. Default value:
     * <b>ARKUI_FONT_WEIGHT_NORMAL</b>.</li>
     * <li>.value[2].i32: font style. The parameter type is {@link ArkUI_FontStyle}. Default value:
     * <b>ARKUI_FONT_STYLE_NORMAL</b>.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_FONT,

    /**
     * @brief How the adaptive height is determined for the text. This attribute can be set, reset, and obtained as
     * required through APIs. This attribute is suitable for scenarios where text content changes dynamically, such
     * as prioritizing the maximum line count to limit height or prioritizing the minimum font size to ensure text
     * readability.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: how the adaptive height is determined for the text. The parameter type is
     * {@link ArkUI_TextHeightAdaptivePolicy}. Default value:
     * <b>ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST</b>, indicating **MaxLines** takes precedence.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: how the adaptive height is determined for the text. The parameter type is
     * {@link ArkUI_TextHeightAdaptivePolicy}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_HEIGHT_ADAPTIVE_POLICY,
    /**
     * @brief Indentation of the first line. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: indentation of the first line. The input parameter unit is fp, and the return value unit
     * is vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: indentation of the first line. The input parameter unit is fp, and the return value unit
     * is vp.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_INDENT,
    /**
     * @brief Defines the line break rule. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: The parameter type is {@link ArkUI_WordBreak}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: The parameter type is {@link ArkUI_WordBreak}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_WORD_BREAK,
    /**
     * @brief Ellipsis position. This attribute can be set, reset, and obtained as required through APIs. This
     * attribute is suitable for controlling the display position of the text ellipsis, such as trailing ellipsis
     * for regular text, leading ellipsis for path display, and middle ellipsis for long titles.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: ellipsis position. The parameter type is {@link ArkUI_EllipsisMode}. The default value is
     * <b>ARKUI_ELLIPSIS_MODE_END</b>, indicating that content at the end of the line is ellipsized.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: ellipsis position. The parameter type is {@link ArkUI_EllipsisMode}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_ELLIPSIS_MODE,
    /**
     * @brief Defines the text line spacing attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: line spacing, in fp.</li>
     * <li>?.object: Optional. Pointer to {@link OH_ArkUI_NativeModule_LineSpacingOptions} object for line spacing
     * options. Available since API version 26.2.0.
     * Use {@link OH_ArkUI_NativeModule_LineSpacingOptions_Create} to create and
     * {@link OH_ArkUI_NativeModule_LineSpacingOptions_Destroy} to destroy the object.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: line spacing, in fp.</li>
     * <li>.object: pointer to {@link OH_ArkUI_NativeModule_LineSpacingOptions} object for line spacing options.
     * Available since API version 26.2.0.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 12
     */
    NODE_TEXT_LINE_SPACING,
    /**
     * @brief Font feature. **NODE_FONT_FEATURE** provides advanced typographic features in OpenType fonts. These
     * features such as ligatures and monospace are generally used in custom fonts and require support from the
     * respective fonts. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: string that describes the font feature settings. The value format is <b>normal |
     * &lt;feature-tag-value&gt;</b>. Syntax for <b>&lt;feature-tag-value&gt;</b> is <b>&lt;string&gt; [
     * &lt;integer&gt; | on | off]</b>. There can be multiple <b>&lt;feature-tag-value&gt;</b> values, separated by
     * commas (,). For example, for the monospace feature, you can pass in <b>ss01 on</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: font feature. Multiple font features are separated by commas (,).</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_FONT_FEATURE,
    /**
     * @brief Whether to enable text entity recognition. The recognized entity types can be configured through the
     * **NODE_TEXT_ENABLE_DATA_DETECTOR_CONFIG** attribute. This attribute is suitable for recognizing specific
     * entity types in text (such as phone numbers, email addresses, and URLs) to implement features like
     * tap-to-redirection and smart interaction.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable text entity recognition. The value <b>1</b> means to enable text entity
     * recognition, and <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether text entity recognition is enabled. The value <b>1</b> means that text entity
     * recognition is enabled, and <b>0</b> means the opposite.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_ENABLE_DATA_DETECTOR,
    /**
     * @brief Text recognition configuration. This attribute is suitable for customizing the entity types to be
     * recognized (such as phone numbers, email addresses, and URLs) to implement precise text smart recognition and
     * interaction features.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0...].i32: entity type array. The parameter type is {@link ArkUI_TextDataDetectorType}. The array
     * can contain entity types such as phone numbers, URLs, and email addresses. For specific values, refer to the
     * enumeration definition. This parameter takes effect only when **NODE_TEXT_ENABLE_DATA_DETECTOR** is set to
     * <b>1</b> (text entity recognition enabled).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0...].i32: entity type array. The parameter type is {@link ArkUI_TextDataDetectorType}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_ENABLE_DATA_DETECTOR_CONFIG,
    /**
     * @brief Defines the background color of the selected text.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: color value, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_SELECTED_BACKGROUND_COLOR,

    /**
     * @brief String to use in the styled string. This attribute can be set, reset, and obtained as required through
     * APIs. Configuring a custom {@link OH_Drawing_Typography} object for the **Text** component will skip the
     * layout measurement phase of the component. Note the following:
     * 1. Ensure that the lifecycles of the **OH_ArkUI_StyledString** object and **OH_Drawing_Typography** object
     * are aligned with the lifecycle of the **Text** component. Reset the **OH_ArkUI_StyledString** object when the
     * **Text** component is destroyed; otherwise, it may lead to null pointer crashes in the application.
     * 2. Ensure that the **OH_Drawing_TypographyLayout** API is called prior to the layout measurement of the
     * **Text** component.
     * 3. When the **OH_ArkUI_StyledString** and **OH_Drawing_Typography** objects are released, the **reset** API of
     * the **Text** component must be called synchronously; otherwise, it may cause null pointer crashes in the
     * application.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: string to use in the styled string. The parameter type is {@link ArkUI_StyledString}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: string to use in the styled string. The parameter type is {@link ArkUI_StyledString}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_CONTENT_WITH_STYLED_STRING,

    /**
     * @brief Whether to center text vertically in the **Text** component.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to center text vertically. The default value is **0**.
     * The value **1** means to center text vertically, and **0** means the opposite.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the text is vertically centered. The value **1** means the text is vertically
     * centered,
     * and **0** means the opposite.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_HALF_LEADING = 1029,

    /**
     * @brief Font weight attribute, which can be set, reset, and obtained as required through APIs. The font weight
     * specified by this API is not affected by any changes in the system font weight settings.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: font weight. The value is an enumerated value of {@link ArkUI_FontWeight}. A larger value
     * indicates a bolder font. The default value is <b>ARKUI_FONT_WEIGHT_NORMAL</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: font weight. The value is an enumerated value of {@link ArkUI_FontWeight}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 15
     */
    NODE_IMMUTABLE_FONT_WEIGHT = 1030,

    /**
     * @brief Number of lines in the text. This attribute can be obtained as required through APIs.
     * The format of the return value {@link ArkUI_AttributeItem} is as follows.
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: number of lines in the text.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 20
     */
    NODE_TEXT_LINE_COUNT = 1031,

    /**
     * @brief Whether to optimize the trailing spaces at the end of each line during text layout. This attribute can
     * be set, reset, and obtained as required through APIs. This attribute is suitable for optimizing text layout
     * effects, such as removing extra trailing spaces to achieve better text alignment.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to optimize the trailing spaces at the end of each line during text layout. The
     * default value is <b>0</b>.
     * The value <b>1</b> means to optimize trailing spaces at the end of each line during text layout, and <b>0</b>
     * means the opposite.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the trailing spaces at the end of each line are optimized during text layout. The
     * value <b>1</b> indicates the trailing spaces at the end of each line are optimized during text layout, and
     * <b>0</b> indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 20
     */
    NODE_TEXT_OPTIMIZE_TRAILING_SPACE = 1032,

    /**
     * @brief Linear gradient effect for text. This attribute can be set, reset, and obtained as required through
     * APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: start angle of the linear gradient. The setting takes effect only when <b>direction</b> is
     * set to <b>ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM</b>; otherwise, the <b>direction</b> attribute serves as the
     * primary layout method. A positive value indicates a clockwise rotation from the origin, (0, 0). The default
     * value is <b>180</b>.</li>
     * <li>.value[1].i32: direction of the linear gradient. The parameter type is
     * {@link ArkUI_LinearGradientDirection}. When a direction other than
     * <b>ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM</b> is set, the <b>angle</b> attribute is ignored. The default value
     * is <b>ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_BOTTOM</b>.</li>
     * <li>.value[2].i32: whether to repeat the colors. The value <b>1</b> means to repeat the gradient colors, and
     * <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * <li>.object: the parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of
     * which consists of a color and its stop position. Invalid colors are automatically skipped. colors: colors of
     * the color stops, in 0xARGB format. For example, **0xFFFF0000** indicates red. stops: stop positions of the
     * color stops. The value range is [0, 1.0]. <b>0</b> represents the start of the gradient container, and
     * <b>1.0</b> represents the end. To create a gradient with multiple color stops, you are advised to set the
     * array elements in ascending order. If a later element is smaller than a previous one, it will be treated as
     * equal to the previous value. size: number of colors. If the value is smaller than the length of the
     * <b>colors</b> array, only the first <b>size</b> colors take effect. Values greater than the <b>colors</b>
     * array length, values less than or equal to 0, or invalid values are not recommended.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: start angle of the linear gradient. The set value is used only when
     * <b>ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM</b> is used. In other cases, the default value <b>0</b> is used.</li>
     * <li>.value[1].i32: direction of the linear gradient. The parameter type is
     * {@link ArkUI_LinearGradientDirection}.</li>
     * <li>.value[2].i32: whether the colors are repeated. The value <b>0</b> means that the colors are not
     * repeated, and <b>1</b> means the opposite. The default value is <b>0</b>.</li>
     * <li>.object: the parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of
     * which consists of a color and its stop position. Invalid colors are automatically skipped. colors: colors of
     * the color stops, in 0xARGB format. For example, **0xFFFF0000** indicates red. stops: stop positions of the
     * color stops. The value range is [0, 1.0]. <b>0</b> represents the start of the gradient container, and
     * <b>1.0</b> represents the end. size: number of effective gradient colors.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 20
     */
    NODE_TEXT_LINEAR_GRADIENT = 1033,

    /**
     * @brief Radial gradient effect for text. This attribute can be set, reset, and obtained as required through
     * APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0]?.f32: X-coordinate of the radial gradient center relative to the upper left corner of the text
     * box, in vp. Default value: <b>0</b>.</li>
     * <li>.value[1]?.f32: Y-coordinate of the radial gradient center relative to the upper left corner of the text
     * box, in vp. The coordinates of the upper left corner of the text box are [0, 0]. Default value: <b>0</b>.</li>
     * <li>.value[2]?.f32: radius of the radial gradient. The default value is <b>0</b>. Value range: [0, +∞). If a
     * negative value is passed, the setting does not take effect.</li>
     * <li>.value[3]?.i32: whether to repeat the colors. The value <b>1</b> indicates to repeat the colors, and
     * <b>0</b> indicates the opposite. Default value: <b>0</b>.</li>
     * <li>.object: the parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of
     * which consists of a color and its stop position. Invalid colors are automatically skipped. colors: colors of
     * the color stops, in 0xARGB format. For example, **0xFFFF0000** indicates red. stops: stop positions of the
     * color stops. The value range is [0, 1.0]. <b>0</b> represents the start of the gradient container, and
     * <b>1.0</b> represents the end. To create a gradient with multiple color stops, you are advised to set the
     * array elements in ascending order. If a later element is smaller than a previous one, it will be treated as
     * equal to the previous value. size: number of colors. If the value is smaller than the length of the
     * <b>colors</b> array, only the first <b>size</b> colors take effect. Values greater than the <b>colors</b>
     * array length, values less than or equal to 0, or invalid values are not recommended.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0]?.f32: X-coordinate of the radial gradient center relative to the upper left corner of the text
     * box, in vp.</li>
     * <li>.value[1]?.f32: Y-coordinate of the radial gradient center relative to the upper left corner of the text
     * box, in vp. The coordinates of the upper left corner of the text box are [0, 0].</li>
     * <li>.value[2]?.f32: radius of the radial gradient, in vp. The default value is <b>0</b>.</li>
     * <li>.value[3]?.i32: whether the colors are repeated. The value <b>1</b> means that the colors are repeated,
     * and <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * <li>.object: the parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of
     * which consists of a color and its stop position. Invalid colors are automatically skipped. colors: colors of
     * the color stops, in 0xARGB format. For example, **0xFFFF0000** indicates red. stops: stop positions of the
     * color stops. The value range is [0, 1.0]. <b>0</b> represents the start of the gradient container, and
     * <b>1.0</b> represents the end. size: number of effective gradient colors.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 20
     */
    NODE_TEXT_RADIAL_GRADIENT = 1034,

    /**
     * @brief Vertical alignment mode of the text content. This attribute can be set, reset, and obtained as required
     * through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: vertical alignment mode of the text content. The parameter type is
     * {@link ArkUI_TextVerticalAlignment}. The default value is <b>ARKUI_TEXT_VERTICAL_ALIGNMENT_BASELINE</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: vertical alignment mode of the text content. The parameter type is
     * {@link ArkUI_TextVerticalAlignment}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 20
     */
    NODE_TEXT_VERTICAL_ALIGN = 1035,

    /**
     * @brief Vertical alignment mode of the text content area. This attribute can be set, reset, and obtained as
     * required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: vertical alignment mode of the text content area. The parameter type is
     * {@link ArkUI_TextContentAlign}. The default value is <b>ARKUI_TEXT_CONTENT_ALIGN_CENTER</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: vertical alignment mode of the text content area. The parameter type is
     * {@link ArkUI_TextContentAlign}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 21
     */
    NODE_TEXT_CONTENT_ALIGN = 1036,

    /**
     * @brief Minimum number of lines in the text. This attribute can be set, reset, and obtained as required through
     * APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: minimum number of lines in the text. Value range: positive integer. The setting does not
     * take effect when 0 or a negative value is passed.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: minimum number of lines in the text. Value range: positive integer.</li>
     * </ul>
     *
     * @since 22
     *
     * @ingroup Text Display
     */
    NODE_TEXT_MIN_LINES = 1037,

    /**
     * @brief Enables the selected data detector.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Enable selected text recognition, default value true.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether selected text recognition is enabled.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 22
     */
    NODE_TEXT_ENABLE_SELECTED_DATA_DETECTOR = 1038,

    /**
     * @brief Minimum line height. This attribute can be set, reset, and obtained as required through APIs. This
     * attribute is suitable for limiting the minimum text line height, such as ensuring text readability or
     * preventing overlapping text display caused by an excessively small line height.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: minimum line height of the text. Default value: <b>0</b>. Unit: fp. Value range: [0, +∞).
     * When a negative value is passed, the setting does not take effect.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: minimum line height of the text. The unit is fp.</li>
     * </ul>
     *
     * @since 22
     *
     * @ingroup Text Display
     */
    NODE_TEXT_MIN_LINE_HEIGHT = 1040,

    /**
     * @brief Maximum line height. This attribute can be set, reset, and obtained as required through APIs. This
     * attribute is suitable for limiting the maximum text line height, such as controlling the compactness of text
     * layout or preventing wasted display space caused by an excessively large line height.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: maximum line height of the text. Default value: <b>0</b>, which indicates that the maximum
     * line height is not limited. The unit is fp. Value range: [0, +∞). If a negative value is passed, the setting
     * does not take effect.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: maximum line height of the text. The unit is fp.</li>
     * </ul>
     *
     * @since 22
     *
     * @ingroup Text Display
     */
    NODE_TEXT_MAX_LINE_HEIGHT = 1041,

    /**
     * @brief Multiple value of the multiple line height mode. This attribute can be set, reset, and obtained as
     * required through APIs. This attribute is suitable for setting the line height relative to the font size,
     * such as implementing dynamic layout or automatically adjusting the line height when the font size changes.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: line height multiple value of text.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: line height multiple value of text.</li>
     * </ul>
     *
     * @since 22
     *
     * @ingroup Text Display
     */
    NODE_TEXT_LINE_HEIGHT_MULTIPLE = 1042,

    /**
     * @brief Text layout manager. This attribute can be obtained as required through APIs. This attribute is
     * suitable for obtaining text layout information, such as querying the number of text lines and character
     * positions, as well as measuring text sizes.
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: the layout manager of text. The parameter type is {@link ArkUI_TextLayoutManager}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 22
     */
    NODE_TEXT_LAYOUT_MANAGER = 1043,

    /**
     * @brief Extended options of the text menu. This attribute can be set as required through APIs. This
     * attribute is suitable for extending the text editing menu, such as adding custom action items or extending
     * copy and paste functions.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: the edit menu options of text. The parameter type is {@link ArkUI_TextEditMenuOptions}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 22
     */
    NODE_TEXT_EDIT_MENU_OPTIONS = 1044,

    /**
     * @brief Custom text selection menu. This attribute can be set as required through APIs. This attribute is
     * suitable for customizing the text selection menu, such as adding specific action buttons or customizing the
     * menu UI style.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: the custom selection menu of text.
     * The parameter type is {@link ArkUI_SelectionMenuOptions}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 22
     */
    NODE_TEXT_BIND_SELECTION_MENU = 1045,

    /**
     * @brief Text selection area, which will be highlighted, for the component that obtains focus. This attribute can
     * be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Start position of the text selection. Value range: [0, Text length]. The value must be a valid
     * text index.</li>
     * <li>.value[1].i32: End position of the text selection. Value range: [0,
     * Text length]. The value must be a valid text
     * index.</li>
     * <li>.object: Selection options. The parameter type is {@link ArkUI_SelectionOptions}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Start position of the text selection.</li>
     * <li>.value[1].i32: End position of the text selection.</li>
     * <li>.object: Selection options. The parameter type is {@link ArkUI_SelectionOptions}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 23
     */
    NODE_TEXT_TEXT_SELECTION = 1046,

    /**
     * @brief Whether to enable orphan character optimization for text layout in the **Text** component. When set,
     * the orphan character (the first character in the last line of a paragraph) is processed more efficiently to
     * improve the text layout. When enabled, it adjusts line break positions to avoid orphan characters as much
     * as possible. The orphan character optimization feature takes effect only when the {@link ArkUI_WordBreak}
     * attribute is not set to **ARKUI_WORD_BREAK_BREAK_ALL**.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32:  Whether enable the feature, true means enable this feature, false means disable. The default
     * value is false.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: The current state of this feature.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 26.0.0
     */
 	  NODE_TEXT_ORPHAN_CHAR_OPTIMIZATION = 1047,

    /**
     * @brief Whether to enable leading punctuation compression. This attribute can be set, reset, and obtained as
     * required through APIs. This attribute is suitable for Chinese layout scenarios, compressing leading
     * punctuations to improve layout aesthetics and reading experience.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32:  Whether enable the feature, true means enable this feature, false means disable. The default
     * value is false.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether compress punctuation at the beginning of line.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 23
     */
    NODE_TEXT_COMPRESS_LEADING_PUNCTUATION = 1048,

    /**
     * @brief Whether to add spacing to the first and last lines to avoid text truncation.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Enable include the font padding, true means enable this feature, false means disable. The
     * default value is false.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether include the font padding.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 23
     */
    NODE_TEXT_INCLUDE_FONT_PADDING = 1049,

    /**
     * @brief Whether the line height can be automatically adjusted based on the actual text height for multi-line
     * text overlay. This enumerated value takes effect only when the line height is smaller than the actual text
     * height.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32:  Whether enable the feature, true means enable this feature, false means disable. The default
     * value is false.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether fallback line spacing.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 23
     */
    NODE_TEXT_FALLBACK_LINE_SPACING = 1050,

    /**
     * @brief Configuration options of the text marquee mode. This attribute can be set, reset, and obtained as
     * required through APIs. This attribute is suitable for long text scrolling display scenarios, such as
     * notification reminders and scrolling title display.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: the marquee options of text. The parameter type is {@link ArkUI_TextMarqueeOptions}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: the marquee options of text. The parameter type is {@link ArkUI_TextMarqueeOptions}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 23
     */
    NODE_TEXT_MARQUEE_OPTIONS = 1051,

    /**
     * @brief Text layout direction. This attribute is suitable for supporting the layout requirements of
     * different languages, such as right-to-left (RTL) language display for Arabic and Hebrew.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: writing direction of the text. The value is an enum of {@link ArkUI_TextDirection}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: writing direction the text. The value is an enum of {@link ArkUI_TextDirection}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 23
     */
    NODE_TEXT_DIRECTION = 1052,

    /**
     * @brief Drag preview style when the text is selected.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: selected drag preview style configuration.
     * The parameter type is {@link ArkUI_SelectedDragPreviewStyle}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: selected drag preview style configuration.
     * The parameter type is {@link ArkUI_SelectedDragPreviewStyle}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 23
     */
    NODE_TEXT_SELECTED_DRAG_PREVIEW_STYLE = 1053,

    /**
     * @brief Text controller. This attribute is suitable for managing text editing behavior, such as controlling
     * text display and managing formatted strings.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: the controller of the text. The parameter type is {@link OH_ArkUI_TextController}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 26.0.0
     */
    NODE_TEXT_CONTROLLER = 1054,

    /**
     * @brief Whether to enable punctuation hanging at the end of a line for the Text component. This attribute
     * can be set, reset, and obtained as required through APIs. This attribute is suitable for Chinese layout
     * scenarios, displaying trailing punctuation outside the line to optimize the layout effect.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable punctuation overflow, the default value is false.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to enable punctuation overflow.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 26.0.0
     */
    NODE_TEXT_PUNCTUATION_OVERFLOW = 1055,

    /**
     * @brief Tail indentation of each line in a text block. This attribute is suitable for implementing special
     * layout effects, such as poetry layout and quoted text alignment, which require controlling the trailing
     * space of each line.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: tail indent value, in fp. When size is 1, all lines share the same tail indent.</li>
     * <li>.size: number of tail indent values. When size > 1, the i-th value specifies the tail indent for the i-th
     * line. If the number of text lines exceeds size, the last value is used for the remaining lines.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: first tail indent value, in fp.</li>
     * <li>.size: number of tail indent values.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 26.0.0
     */
    NODE_TEXT_TAIL_INDENTS = 1056,

    /**
     * @brief Sets the text stroke width.
     * <br>This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: text stroke width, in vp. The default value is <b>0</b>, indicating no stroke.
     * A value less than <b>0</b> indicates solid text; a value greater than <b>0</b> indicates outlined text.
     * Percentage values are not supported.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: text stroke width, in vp.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 26.2.0
     */
    NODE_TEXT_STROKE_WIDTH = 1057,

    /**
     * @brief Sets the text stroke color.
     * <br>This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: text stroke color, in 0xARGB format.
     * The default value is the text font color. Invalid values are treated as the default value.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: text stroke color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 26.2.0
     */
    NODE_TEXT_STROKE_COLOR = 1058,

    /**
     * @brief Sets the join style of the text stroke.
     * <br>This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: text stroke join style. The parameter type is {@link OH_ArkUI_StrokeJoinStyle}.
     * The default value is <b>OH_ARKUI_STROKE_JOIN_STYLE_MITER_JOIN</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: text stroke join style. The parameter type is {@link OH_ArkUI_StrokeJoinStyle}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 26.2.0
     */
    NODE_TEXT_STROKE_JOIN_STYLE = 1059,

    /**
     * @brief Defines the text content attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: content of the text span.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: content of the text span.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_SPAN_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SPAN,
    /**
     * @brief Text background style. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: color of the text background, in 0xARGB format, for example, <b>0xFFFF0000</b> indicating
     * red. The second parameter indicates the rounded corners of the text background. Two setting modes are available:
     * 1: .value[1].f32: radius of the four corners, in vp. 2: .value[1].f32: radius of the upper left corner, in
     * vp.</li>
     * <li>.value[2].f32: radius of the upper right corner, in vp.</li>
     * <li>.value[3].f32: radius of the lower left corner, in vp.</li>
     * <li>.value[4].f32: radius of the lower right corner, in vp.</li>
     * <li>.value[5]?.f32: border width of the text background, in vp. Optional. The default value is <b>0</b>.
     * This parameter is supported since API version 26.2.0.</li>
     * <li>.value[6]?.u32: border color of the text background, in 0xARGB format. Optional.
     * The default value is <b>0x00000000</b> (transparent). This parameter is supported since API version 26.2.0.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: color of the text background, in 0xARGB format.</li>
     * <li>.value[1].f32: radius of the upper left corner, in vp.</li>
     * <li>.value[2].f32: radius of the upper right corner, in vp.</li>
     * <li>.value[3].f32: radius of the lower left corner, in vp.</li>
     * <li>.value[4].f32: radius of the lower right corner, in vp.</li>
     * <li>.value[5].f32: border width of the text background, in vp.
     * This parameter is supported since API version 26.2.0.</li>
     * <li>.value[6].u32: border color of the text background, in 0xARGB format.
     * This parameter is supported since API version 26.2.0.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_SPAN_TEXT_BACKGROUND_STYLE,
    /**
     * @brief Text baseline offset attribute, which can be set, reset, and obtained as required through APIs.
     * This attribute is suitable for adjusting the baseline position of the text of the **Span** component, such
     * as displaying superscripts and subscripts or implementing special layout effects.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: baseline offset, in fp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: baseline offset, in fp.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_SPAN_BASELINE_OFFSET,
    /**
     * @brief Text style attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>?.string: font family. Optional. Use commas (,) to separate multiple fonts.</li>
     * <li>.value[0].f32: font size, in fp.</li>
     * <li>.value[1]?.i32: font weight. Optional.</li>
     * <li>.value[2]?.i32: font style. Optional. The parameter type is {@link ArkUI_FontStyle}.
     * The default value is <b>ARKUI_FONT_STYLE_NORMAL</b>.</li>
     * <li>?.object: Optional. The font configurations. The parameter type is {@link OH_ArkUI_FontConfigs}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: font family. Use commas (,) to separate multiple fonts.</li>
     * <li>.value[0].f32: font size, in fp.</li>
     * <li>.value[1].i32: font weight.</li>
     * <li>.value[2].i32: font style. The parameter type is {@link ArkUI_FontStyle}.
     * The default value is <b>ARKUI_FONT_STYLE_NORMAL</b>.</li>
     * <li>.object: the font configurations. The parameter type is {@link OH_ArkUI_FontConfigs}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 24
     */
    NODE_SPAN_FONT = 2003,

    /**
     * @brief Font weight attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: font weight. The default value is 400.</li>
     * <li>?.object: Optional. The font weight configurations.
     * The parameter type is {@link OH_ArkUI_FontWeightConfigs}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: font weight.</li>
     * <li>.object: the font weight configurations. The parameter type is {@link OH_ArkUI_FontWeightConfigs}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 24
     */
    NODE_SPAN_FONT_WEIGHT = 2004,
    /**
     * @brief Defines the image source of the image span.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: image address of the image span.</li>
     * <li>.object: The parameter type is {@link ArkUI_DrawableDescriptor}. Either .string or .object must be set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: image address of the image span.</li>
     * <li>.object: The parameter type is {@link ArkUI_DrawableDescriptor}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_IMAGE_SPAN_SRC = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE_SPAN,
    /**
     * @brief Alignment mode of the image with the text. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: alignment mode of the image with the text.
     * The value is an enum of {@link ArkUI_ImageSpanAlignment}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: alignment mode of the image with the text.
     * The value is an enum of {@link ArkUI_ImageSpanAlignment}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_IMAGE_SPAN_VERTICAL_ALIGNMENT,
    /**
     * @brief Placeholder image address for the image span. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: placeholder image source.</li>
     * <li>.object: The parameter type is {@link ArkUI_DrawableDescriptor}. Either .string or .object must be set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: placeholder image source.</li>
     * <li>.object: The parameter type is {@link ArkUI_DrawableDescriptor}.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_IMAGE_SPAN_ALT,
    /**
     * @brief Baseline offset attribute of the **ImageSpan** component. This attribute can be set, reset, and
     * obtained as required through APIs. A positive value means an upward offset, while a negative value means a
     * downward offset. The default value is **0**, and the unit is fp. This attribute is suitable for adjusting
     * the relative position between images and text in mixed layouts to achieve precise alignment effects.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: baseline offset, in fp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: baseline offset, in fp.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 13
     */
    NODE_IMAGE_SPAN_BASELINE_OFFSET = 3003,

    /**
     * @brief Color filter of the image. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32 to .value[19].f32: filter matrix array.</li>
     * <li>.size: 5 x 4 filter array size.</li>
     * <li>.object: the pointer to OH_Drawing_ColorFilter. Either .value or .object is set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32 to .value [19].f32: filter matrix array.</li>
     * <li>.size: 5 x 4 filter array size.</li>
     * <li>.object: the pointer to OH_Drawing_ColorFilter.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 22
     */
    NODE_IMAGE_SPAN_COLOR_FILTER = 3004,
    /**
     * @brief Whether to enable the new SVG parsing capability, which allows you to set the scope of SVG parsing
     * functionality support. This attribute can be set, reset, and obtained as required through APIs. After the
     * **ImageSpan** component is created, the value of this attribute cannot be dynamically changed.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether color fliter support svg. The default value is <b>false</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: enable switch.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 22
     */
    NODE_IMAGE_SPAN_SUPPORT_SVG2 = 3005,
    /**
     * @brief Resizes the image span when stretching it with array or a lattice object.
     * This attribute can be set, reset, and obtained as required through APIs.
     * The parameter types for setting and getting should be the same.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: width of the left edge, in vp.</li>
     * <li>.value[1].f32: width of the top edge, in vp.</li>
     * <li>.value[2].f32: width of the right edge, in vp.</li>
     * <li>.value[3].f32: width of the bottom edge, in vp.</li>
     * <li>.object: The parameter type is {@link OH_Drawing_Lattice}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: width of the left edge, in vp.</li>
     * <li>.value[1].f32: width of the top edge, in vp.</li>
     * <li>.value[2].f32: width of the right edge, in vp.</li>
     * <li>.value[3].f32: width of the bottom edge, in vp.</li>
     * <li>.object: The parameter type is {@link OH_Drawing_Lattice}.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 26.2.0
     */
    NODE_IMAGE_SPAN_RESIZABLE = 3006,
    /**
     * @brief Defines the image source of the <Image> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: image source.</li>
     * <li>.object: The parameter type is {@link ArkUI_DrawableDescriptor}. Either .string or .object must be set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: image source.</li>
     * <li>.object: The parameter type is {@link ArkUI_DrawableDescriptor}.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_SRC = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE,
    /**
     * @brief How the image is resized to fit its container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: image filling effect. The value is an enumerated value of
     * {@link ArkUI_ObjectFit}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: image filling effect. The value is an enumerated value of
     * {@link ArkUI_ObjectFit}.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_OBJECT_FIT,
    /**
     * @brief Interpolation effect of the image.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: interpolation effect. The value is an enumerated value of
     * {@link ArkUI_ImageInterpolation}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: interpolation effect. The value is an enumerated value of
     * {@link ArkUI_ImageInterpolation}.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_INTERPOLATION,
    /**
     * @brief How the image is repeated.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: image repetition style. The value is an enumerated value of
     * {@link ArkUI_ImageRepeat}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: image repetition style. The value is an enumerated value of
     * {@link ArkUI_ImageRepeat}.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_OBJECT_REPEAT,
    /**
     * @brief Color filter of the image.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32 to .value[19].f32: filter matrix array.</li>
     * <li>.size: 5 x 4 filter array size.</li>
     * <li>.object: color filter pointer. The parameter type is <b>OH_Drawing_ColorFilter</b>.
     * Either <b>.object</b> or <b>.size</b> must be set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32 to .value[19].f32: filter matrix array.</li>
     * <li>.size: 5 x 4 filter array size.</li>
     * <li>.object: color filter pointer. The parameter type is <b>OH_Drawing_ColorFilter</b>.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_COLOR_FILTER,
    /**
     * @brief Auto resize attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable auto resize. The default value is <b>false</b>. <b>true</b> to
     * enable; <b>false</b> otherwise.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether auto resize is enabled.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_AUTO_RESIZE,
    /**
     * @brief Placeholder image address attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: address of the placeholder image.</li>
     * <li>.object: <b>PixelMap</b> object. The parameter type is {@link ArkUI_DrawableDescriptor}.
     * Either <b>.object</b> or <b>.string</b> must be set. Network images are not supported.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: address of the placeholder image.</li>
     * <li>.object: <b>PixelMap</b> object. The parameter type is {@link ArkUI_DrawableDescriptor}.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_ALT,
    /**
     * @brief Whether the image is draggable.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the image is draggable. The value <b>true</b> means that the image is
     * draggable.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the image is draggable.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_DRAGGABLE,
    /**
     * @brief Image rendering mode. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: image rendering mode. The value is an enumerated value of
     * {@link ArkUI_ImageRenderMode}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: image rendering mode. The value is an enumerated value of
     * {@link ArkUI_ImageRenderMode}.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_RENDER_MODE,
    /**
     * @brief Whether the display size of an image follows the original size of the image source.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the display size of an image follows the original size of the image
     * source. The value <b>1</b> indicates that the display size of an image follows the original size
     * of the image source, and the value <b>0</b> indicates the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the display size of an image follows the original size of the image
     * source. The value <b>1</b> indicates that the display size of an image follows the original size
     * of the image source, and the value <b>0</b> indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_FIT_ORIGINAL_SIZE,
    /**
     * @brief Fill color to be superimposed on the image.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: fill color, in 0xARGB format. For example, <b>0xFFFF0000</b> indicates red.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: fill color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_FILL_COLOR,
    /**
     * @brief Resizable image options.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: fixed distance (unchanged during stretching) from the left edge of the image.
     * The unit is vp.</li>
     * <li>.value[1].f32: fixed distance (unchanged during stretching) from the top edge of the image.
     * The unit is vp.</li>
     * <li>.value[2].f32: fixed distance (unchanged during stretching) from the right edge of the image.
     * The unit is vp.</li>
     * <li>.value[3].f32: fixed distance (unchanged during stretching) from the bottom edge of the image.
     * The unit is vp. When this attribute is used together with <b>NODE_IMAGE_ANTIALIASED</b>, the
     * <b>NODE_IMAGE_ANTIALIASED</b> attribute setting does not take effect.</li>
     * <li>.object: The parameter type is {@link OH_Drawing_Lattice}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: fixed distance (unchanged during stretching) from the left edge of the image.
     * The unit is vp.</li>
     * <li>.value[1].f32: fixed distance (unchanged during stretching) from the top edge of the image.
     * The unit is vp.</li>
     * <li>.value[2].f32: fixed distance (unchanged during stretching) from the right edge of the image.
     * The unit is vp.</li>
     * <li>.value[3].f32: fixed distance (unchanged during stretching) from the bottom edge of the image.
     * The unit is vp.</li>
     * <li>.object: The parameter type is {@link OH_Drawing_Lattice}.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_RESIZABLE,
    /**
     * @brief Synchronous image loading attribute, which can be set, reset, and obtained as required through APIs.
     * The {@link NODE_IMAGE_ALT} placeholder image is always loaded asynchronously, and <b>syncLoad</b>
     * does not take effect on it.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to load the image synchronously. The default value is <b>false</b>.
     * <b>true</b>: Load the image synchronously. <b>false</b>: Load the image asynchronously.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the image is loaded synchronously.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 20
     */
    NODE_IMAGE_SYNC_LOAD = 4012,
    /**
     * @brief Decoding size of the image. This attribute works only when the target size is smaller than
     * the source size. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: width for image decoding, in px.</li>
     * <li>.value[1].i32: height for image decoding, in px. If the value of any parameter is less than or
     * equal to 0, the attribute setting fails and {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned,
     * indicating a parameter error.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: width for image decoding, in px.</li>
     * <li>.value[1].i32: height for image decoding, in px.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_SOURCE_SIZE = 4013,
    /**
     * @brief Transformation matrix of the image. This attribute can be set, reset, and obtained as
     * required through APIs. Affine image transformation can be implemented using floating-point numbers.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0...15].f32: 4 x 4 matrix represented by a floating-point array with a length of 16.
     * If the number of parameters is less than 16, the attribute setting fails, and
     * {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned. If the number of parameters exceeds 16, only
     * the first 16 data entries are used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0...15].f32: 4 x 4 matrix represented by a floating-point array with a length of 16.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_IMAGE_MATRIX = 4014,
    /**
     * @brief Whether the image follows the system language direction, displaying a mirrored effect in a
     * right-to-left (RTL) language environments. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the image follows the system language direction. The default value is
     * <b>false</b>. <b>true</b>: The image follows the system language direction. <b>false</b>: The image
     * does not follow the system language direction.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the image follows the system language direction. <b>true</b>: The image
     * follows the system language direction. <b>false</b>: The image does not follow the system language
     * direction.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_MATCH_TEXT_DIRECTION = 4015,
    /**
     * @brief Image copy mode. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: image copy mode, specified using the {@link ArkUI_CopyOptions} enum. The
     * default value is <b>ARKUI_COPY_OPTIONS_NONE</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: image copy mode, specified using the {@link ArkUI_CopyOptions} enum.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_COPY_OPTION = 4016,
    /**
     * @brief Whether to enable the AI analyzer, which supports subject recognition, text recognition,
     * and object lookup. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable the AI analyzer for images. The default value is
     * <b>false</b>. <b>true</b> to enable; <b>false</b> otherwise.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the AI analyzer is enabled for images. <b>true</b> indicates that the
     * AI analyzer is enabled; <b>false</b> otherwise.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_ENABLE_ANALYZER = 4017,
    /**
     * @brief Dynamic range attribute for image display, specifying the dynamic range mode for image
     * rendering (for example, SDR/HDR). This attribute can be set, reset, and obtained as required
     * through APIs. It is used to match the capabilities of the display device and ensure accurate
     * presentation of image brightness and colors.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: dynamic range mode, specified using {@link ArkUI_DynamicRangeMode}. The
     * default value is <b>ARKUI_DYNAMIC_RANGE_MODE_STANDARD</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: dynamic range mode, specified using {@link ArkUI_DynamicRangeMode}.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_DYNAMIC_RANGE_MODE = 4018,
    /**
     * @brief Brightness attribute of the image in HDR mode, used to control brightness parameters for
     * high dynamic range display. This attribute can be set, reset, and obtained as required through
     * APIs. It is used to ensure accurate presentation of details in the bright and dark areas of HDR
     * images.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: brightness value. The value range is [0, 1]. Values less than 0 or greater
     * than 1.0 are clamped to 1. <b>0</b>: The image is displayed at SDR brightness. <b>1</b>: The
     * image is displayed at the highest allowed HDR brightness.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: brightness value. The value range is [0, 1].</li>
     * </ul>
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_HDR_BRIGHTNESS = 4019,
    /**
     * @brief Display orientation of the image content. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: expected image content display orientation, specified using
     * {@link ArkUI_ImageRotateOrientation}. The default value is <b>ARKUI_ORIENTATION_UP</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: expected image content display orientation, specified using
     * {@link ArkUI_ImageRotateOrientation}.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_ORIENTATION = 4020,
    /**
     * @brief Whether to enable the new SVG parsing capability, which allows you to set the scope of SVG
     * parsing functionality support. This attribute can be set, reset, and obtained as required through
     * APIs. After the <b>Image</b> component is created, the value of this attribute cannot be
     * dynamically changed.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable the new SVG parsing capability.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the new SVG parsing capability is enabled.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_SUPPORT_SVG2 = 4021,
    /**
     * @brief Transition effect when the image changes. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: custom transition animation. The parameter type is
     * {@link ArkUI_ContentTransitionEffect}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: custom transition animation. The parameter type is
     * {@link ArkUI_ContentTransitionEffect}.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_CONTENT_TRANSITION = 4022,
    /**
     * @brief Placeholder image during the loading process. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: placeholder image address during the loading of the image component.</li>
     * <li>.object: <b>PixelMap</b> object. The parameter type is {@link ArkUI_DrawableDescriptor}.
     * Either <b>.object</b> or <b>.string</b> must be set. Network images are not supported.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: placeholder image address during the loading of the image component.</li>
     * <li>.object: <b>PixelMap</b> object. The parameter type is {@link ArkUI_DrawableDescriptor}.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 22
     */
    NODE_IMAGE_ALT_PLACEHOLDER = 4023,
    /**
     * @brief Placeholder image in the loading failure scenarios. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: placeholder image address in the loading failure scenarios.</li>
     * <li>.object: <b>PixelMap</b> object. The parameter type is {@link ArkUI_DrawableDescriptor}.
     * Either <b>.object</b> or <b>.string</b> must be set. Network images are not supported.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: placeholder image address in the loading failure scenarios.</li>
     * <li>.object: <b>PixelMap</b> object. The parameter type is {@link ArkUI_DrawableDescriptor}.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 22
     */
    NODE_IMAGE_ALT_ERROR = 4024,
    /**
     * @brief Whether to enable anti-aliasing for the edges of a bitmap image. This attribute can be
     * set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable anti-aliasing for the edges of a bitmap image. The default
     * value is <b>false</b>. <b>true</b> to enable; <b>false</b> otherwise. This attribute does not
     * take effect when used together with <b>NODE_IMAGE_RESIZABLE</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether anti-aliasing is enabled for the edges of a bitmap image. <b>true</b>
     * means enabled; <b>false</b> otherwise.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 23
     */
    NODE_IMAGE_ANTIALIASED = 4025,
    /**
     * @brief Defines the color of the component when it is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format. For example, 0xFFFF0000 indicates red.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format.</li> \n
     * </ul>
     *
     * @ingroup Toggle
     */
    NODE_TOGGLE_SELECTED_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TOGGLE,
    /**
     * @brief Color of the circular thumb for the component of the switch type.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: Color of the circular thumb, in 0xARGB format. For example,
     * **0xFFFF0000** indicates red.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: Color of the circular thumb, in 0xARGB format.</li> \n
     * </ul>
     *
     * @ingroup Toggle
     */
    NODE_TOGGLE_SWITCH_POINT_COLOR,
    /**
     * @brief Toggle value of the component of the switch type. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: Whether to enable the toggle. The value **true** means to enable the toggle.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: Whether the toggle is enabled.</li> \n
     * </ul>
     *
     * @ingroup Toggle
     */
    NODE_TOGGLE_VALUE,

    /**
     * @brief Color of the component when it is deselected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     *<li>.value[0].u32: Background color, in 0xARGB format. For example, **0xFFFF0000** indicates red.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: Background color, in 0xARGB format.</li> \n
     * </ul>
     *
     * @ingroup Toggle
     */
    NODE_TOGGLE_UNSELECTED_COLOR,

    /**
     * @brief Defines the foreground color of the loading progress bar.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: foreground color, in 0xARGB format. For example, 0xFFFF0000 indicates red.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: foreground color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Information Display
     */
    NODE_LOADING_PROGRESS_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LOADING_PROGRESS,
    /**
     * @brief Whether to show the loading animation for the **LoadingProgress** component. This attribute can be set,
     * reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to show the loading animation.
     * The value <b>true</b> means to show the loading animation, and <b>false</b> means the opposite.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: The value <b>1</b> means to show the loading animation, and <b>0</b> means the opposite.</li>
     * </ul>
     *
     * @ingroup Information Display
     */
    NODE_LOADING_PROGRESS_ENABLE_LOADING,

    /**
     * @brief Defines the default placeholder text of the single-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: default placeholder text.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: default placeholder text.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_PLACEHOLDER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,
    /**
     * @brief Default text of the single-line text box. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: Default text content,
     * used to set the text initially displayed in the input box. Set this parameter when
     * you need to preset text in the input box, for example, form default values, initial editing content,
     * etc. When not set, the input box is empty.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: Default text content.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_TEXT,
    /**
     * @brief Caret color attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: caret color, in 0xARGB format. For example, **0xFFFF0000** indicates red.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: Caret color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_CARET_COLOR,
    /**
     * @brief Caret style attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Caret width, in vp. Value range: [0, +∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Caret width, in vp.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_CARET_STYLE,
    /**
     * @brief Underline of the single-line text box. This attribute can be set, reset, and obtained as required through
     * APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to show an underline. **1** means to show an underline; **0** means the opposite.
     * Default
     * value: **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether an underline is shown. The value **1** means that an underline is shown, and **0**
     * means the
     * opposite.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_SHOW_UNDERLINE,
    /**
     * @brief Maximum number of characters in the text input. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: maximum number of characters in the text input, without a unit. Value range: [0, +∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: maximum number of characters in the text input, without a unit.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_MAX_LENGTH,
    /**
     * @brief Type of the **Enter** key. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: type of the **Enter** key. The value is an enumerated value of {@link ArkUI_EnterKeyType}.
     * The default value is <b>ARKUI_ENTER_KEY_TYPE_DONE</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: type of the **Enter** key. The value is an enumerated value of {@link ArkUI_EnterKeyType},
     * used to
     * determine the display style of the **Enter** key in the input box.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ENTER_KEY_TYPE,
    /**
     * @brief Default placeholder text color when there is no input. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: Color, in 0xARGB format. For example, **0xFFFF0000** indicates red.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: Color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_PLACEHOLDER_COLOR,
    /**
     * @brief Default placeholder text font (including the size, weight, style, and font family) when there is no input.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0]?.f32: Font size, in fp. This parameter is optional. The default value is **16.0**. Value range: [0,
     * +∞). When a negative value is passed, the setting does not take effect.</li>
     * <li>.value[1]?.i32: Font style. This parameter is optional. The value is an enumerated value of {@link
     * ArkUI_FontStyle}. Default value: **ARKUI_FONT_STYLE_NORMAL**, which indicates the normal font
     * style.</li>
     * <li>.value[2]?.i32: Font weight. This parameter is optional. The value is an enumerated value of {@link
     * ArkUI_FontWeight}. Default value: **ARKUI_FONT_WEIGHT_NORMAL**, which indicates the normal font
     * weight.</li>
     * <li>?.string: Font family. Multiple font families are separated by commas (,). For example, "font family 1,font
     * family 2". When not passed, the system default font family is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Font size, in fp.</li>
     * <li>.value[1].i32: Font style. The value is an enumerated value of {@link ArkUI_FontStyle}.</li>
     * <li>.value[2].i32: Font weight. The value is an enumerated value of {@link ArkUI_FontWeight}.</li>
     * <li>.string: Font family. Multiple font families are separated by commas (,).</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_PLACEHOLDER_FONT,
    /**
     * @brief Whether to enable the input method when the component obtains focus. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable the input method when the component obtains focus. The value **1** indicates
     * means to enable the input method, and <b>false</b> means the opposite.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the input method is enabled when the component obtains focus. The value **1** means
     * <b>0</b> means the opposite.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS,
    /**
     * @brief Text input type. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Text input type. The value is an enumerated value of {@link ArkUI_TextInputType}. The default
     * value is **ARKUI_TEXTINPUT_TYPE_NORMAL**, which indicates the basic input mode.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Text input type. The value is an enumerated value of {@link ArkUI_TextInputType}, used to
     * determine the input content and keyboard style of the input box.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_TYPE,
    /**
     * @brief Background color of the selected text. This attribute can be set, reset, and obtained as required
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: color, in 0xARGB format. For example, **0xFFFF0000** indicates red.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR,
    /**
     * @brief Whether to display the password icon at the end of the password text box. This attribute can be set,
     * reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to display the password icon. **1** means to display; **0** otherwise. Default value:
     * **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the password icon is displayed. The value **1** means that the password icon is
     * displayed, and **0** means the opposite.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_SHOW_PASSWORD_ICON,
    /**
     * @brief Editable state for the single-line text box. This attribute can be set and obtained as required through
     * APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to remain in the editable state. **1** means to remain in the editable state, and
     * **0**
     * means to exit the editable state.</li>
     * </ul>
     *
     * **Format of the {@link ArkUI_AttributeItem} for obtaining the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to remain in the editable state. **1** means to remain in the editable state, and
     * **0**
     * means to exit the editable state.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_EDITING,
    /**
     * @brief Style of the cancel button on the right of the single-line text box. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Button style. The value is an enumerated value of {@link ArkUI_CancelButtonStyle}. The default
     * value is **ARKUI_CANCELBUTTON_STYLE_INPUT**, which indicates the clear button input style.</li>
     * <li>.value[1]?.f32: Icon size, in vp. Value range: [0, +∞). When a negative value is passed, the setting does not
     * take effect. When not passed, the system default icon size is used.</li>
     * <li>.value[2]?.u32: Button icon color, in 0xARGB format, for example,
     * **0xFFFF0000** indicates red. When not passed,
     * the system default icon color is used.</li>
     * <li>?.string: Button icon address. The value is the local address of an image, for example,
     * /pages/icon.png. When
     * not passed, the system default clear icon is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Button style. The value is an enumerated value of {@link ArkUI_CancelButtonStyle}.</li>
     * <li>.value[1].f32: Button icon size, in vp.</li>
     * <li>.value[2].u32: Button icon color, in 0xARGB format.</li>
     * <li>.string: Button icon address.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_CANCEL_BUTTON,
    /**
     * @brief Text selection area. After set, the selected area will be highlighted. This attribute can be set,
     * reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: start position of the text selection.</li>
     * <li>.value[1].i32: end position of the text selection.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: start position of the text selection.</li>
     * <li>.value[1].i32: end position of the text selection.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_TEXT_SELECTION,
    /**
     * @brief Color of the underline when it is shown. This attribute takes effect only after
     * **NODE_TEXT_INPUT_SHOW_UNDERLINE** is set to **1** to show the underline. The default underline color configured
     * for the theme is **0x33182431**, which indicates dark gray with 20% opacity.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: Color of the underline applied to the text being typed in. This parameter is mandatory.
     * The value
     * is in 0xARGB format.</li>
     * <li>.value[1].u32: Color of the underline applied to the text in the normal state. This parameter is mandatory.
     * The
     * value is in 0xARGB format.</li>
     * <li>.value[2].u32: Color of the underline applied to the text when an error is detected.
     * This parameter is mandatory.
     * The value is in 0xARGB format.</li>
     * <li>.value[3].u32: Color of the underline applied to the text when it is disabled. This parameter is mandatory.
     * The
     * value is in 0xARGB format.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: Color of the underline applied to the text being typed in. The value is in 0xARGB format.</li>
     * <li>.value[1].u32: Color of the underline applied to the text in the normal state.
     * The value is in 0xARGB format.</li>
     * <li>.value[2].u32: Color of the underline applied to the text when an error is detected. The value is in 0xARGB
     * format.</li>
     * <li>.value[3].u32: Color of the underline applied to the text when it is disabled.
     * The value is in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_UNDERLINE_COLOR,
    /**
     * @brief Whether to enable autofill.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable autofill. The default value is **1**.
     * **1** indicates to enable, and **0** indicates the opposite.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether autofill is enabled. The value **1** means auto-fill is enabled, and **0** means the
     * opposite.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ENABLE_AUTO_FILL,
    /**
     * @brief Autofill type.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: autofill type. The parameter type is {@link ArkUI_TextInputContentType}, used to specify the
     * content type in autofill scenarios. For specific enumerated values and application scenarios, see
     * {@link ArkUI_TextInputContentType}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: autofill type. The parameter type is {@link ArkUI_TextInputContentType}, used to determine the
     * auto-filled content type.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_CONTENT_TYPE,
    /**
     * @brief Rules for generating passwords. When autofill is used, these rules are transparently transmitted to
     * Password Vault for generating a new password.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: rules for generating passwords, which are transparently passed to the password vault to control new
     * password generation when autofill is triggered.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: rules for generating passwords.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_PASSWORD_RULES,
    /**
     * @brief Whether to select all text in the initial state. This attribute is not available for the inline input
     * style.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to select all text. Default value: **0**. The value **1** means to select all text,
     * and **0** means the opposite.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether all text is selected. **1** means all text is selected, and **0** means the
     * opposite.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_SELECT_ALL,
    /**
     * @brief Regular expression for input filtering. Only inputs that comply with the regular expression can be
     * displayed. Other inputs are filtered out. For single-character input scenarios, only single-character matching is
     * supported; for multi-character input scenarios (such as pasting), string matching is supported.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: Regular expression,
     * used to filter user input. Input matching the expression is allowed to be displayed,
     * and input not matching is filtered out. Set this parameter when you need to restrict users to inputting
     * only characters in a specific format. For example, **"^[a-zA-Z]+$"** allows only letters, and
     * **"^[0-9]+$"** allows only digits. When not set, all characters are allowed.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: Regular expression.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_INPUT_FILTER,
    /**
     * @brief Text box style (default style or inline input style). The inline input style is a borderless embedded
     * input style where the input box blends directly into the page content. The inline input style is only available
     * when {@link ArkUI_TextInputType} is set to **ARKUI_TEXTINPUT_TYPE_NORMAL**.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Text box style. The parameter type is {@link ArkUI_TextInputStyle}.
     * The inline input style is only
     * available when {@link ArkUI_TextInputType} is set to **ARKUI_TEXTINPUT_TYPE_NORMAL**. The default
     * value is **ARKUI_TEXTINPUT_STYLE_DEFAULT**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Text box style. The parameter type is {@link ArkUI_TextInputStyle},
     * used to determine the display
     * style of the input box.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_STYLE,
    /**
     * @brief Caret position. Sets the position of the caret. Returns the position information of the caret. If this API
     * is called when the caret position is updated in the current frame, it will not take effect.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: length from the start of the string to the position where the caret is located. The value
     * range is [0, Text length]. If the value is out of range, it is automatically corrected to the boundary
     * value.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: index of the caret position.</li>
     * <li>.value[1].f32: X-coordinate of the caret relative to the input box, in px.</li>
     * <li>.value[2].f32: Y-coordinate of the caret relative to the input box, in px.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_CARET_OFFSET,
    /**
     * @brief Position of the edited text area relative to the component and its size.
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: X-coordinate, in px.</li>
     * <li>.value[1].f32: Y-coordinate, in px.</li>
     * <li>.value[2].f32: Content width, in px.</li>
     * <li>.value[3].f32: Content height, in px.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_CONTENT_RECT,
    /**
     * @brief Number of lines of the edited text.
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: number of lines of the edited text.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_CONTENT_LINE_COUNT,
    /**
     * @brief Whether to hide the text selection menu when the text box is long-pressed, double-tapped, or
     * right-clicked. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to hide the text selection menu when the text box is long-pressed, double-tapped, or
     * right-clicked. The default value is **0**.
     * **1**: The system text selection menu is hidden when a user clicks the text box cursor, long-presses the text
     * box,
     * double-taps the text box, triple-taps the text box, or right-clicks the text box.
     * **0**: The system text selection menu is displayed.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the text selection menu is hidden when the text box is long-pressed, double-tapped, or
     * right-clicked. The value **1** means the text selection menu is hidden, and **0** means the text
     * selection menu is displayed.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_SELECTION_MENU_HIDDEN,
    /**
     * @brief Whether the text box loses focus after the **Enter** key is pressed to submit information.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the text box loses focus after the **Enter** key is pressed to submit information. The
     * default value is **1**.
     * **1**: The text box loses focus. **0**: The text box does not lose focus.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the text box loses focus after the **Enter** key is pressed to submit information. The
     * value **1** indicates the text box loses focus, and **0** indicates the text box does not lose
     * focus.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_BLUR_ON_SUBMIT,
    /**
     * @brief Custom keyboard.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Custom keyboard. The parameter type is {@link ArkUI_NodeHandle}.</li>
     * <li>.value[0]?.i32: Whether the custom keyboard supports avoidance. The default value is **0**.
     * **1** to support; **0** otherwise.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Custom keyboard. The parameter type is {@link ArkUI_NodeHandle}.</li>
     * <li>.value[0].i32: Whether the custom keyboard supports avoidance. The value **1** indicates the custom keyboard
     * supports avoidance, **0** indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_CUSTOM_KEYBOARD,
    /**
     * @brief Defines the line break rule. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: The parameter type is {@link ArkUI_WordBreak}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: The parameter type is {@link ArkUI_WordBreak}.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_WORD_BREAK,

    /**
     * @brief Whether to show the keyboard when the text box obtains focus. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to show the keyboard. Default value: **1**.
     * **1** to show; **0** otherwise.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the keyboard is shown. The value **1** indicates the keyboard is shown, and 0
     * indicates
     * the opposite.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_SHOW_KEYBOARD_ON_FOCUS,

    /**
     * @brief Number of lines in the {@link TextInput} component, which can be used to work out the height of the
     * component. For example, if **numberOfLines** is set to **3**, the component displays three lines of text by
     * default.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Number of lines, with a value range of [1,
     * +∞). This parameter is used to calculate the height of
     * the **TextInput** component. For example, when set to 3, the component displays a height
     * sufficient to accommodate three lines of text content by default.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Number of lines.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_NUMBER_OF_LINES,

    /**
     * @brief Letter spacing of the {@link TextInput} component. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: letter spacing. The default unit is fp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: letter spacing. The default unit is fp.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 15
     */
    NODE_TEXT_INPUT_LETTER_SPACING = 7032,

    /**
     * @brief Whether to enable preview text for the {@link TextInput} component. This attribute can be set, reset, and
     * obtained as required through APIs. "Preview text" describes a temporary text staging state. The preview text
     * feature must be enabled in the input method. During text input, before a candidate word is confirmed, marked text
     * is displayed in the text box. For example, when entering Chinese characters via Pinyin, the Pinyin letters are
     * displayed in the input box before the candidate word is confirmed. This state is called preview.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable preview text. The default value is **1**.
     * **1** to enable; **0** otherwise.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether preview text is enabled. The value **1** indicates preview text is enabled, **0**
     * indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 15
     */
    NODE_TEXT_INPUT_ENABLE_PREVIEW_TEXT = 7033,

    /**
     * @brief Whether to enable half leading.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable half leading. The default value is <b>false</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to enable half leading.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 18
     */
    NODE_TEXT_INPUT_HALF_LEADING = 7034,

    /**
     * @brief Appearance of the keyboard when the text box is started.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: keyboard appearance. The parameter type is {@link ArkUI_KeyboardAppearanceType}. For specific
     * enumerated values, see **ArkUI_KeyboardAppearance**. The default value is
     * **ARKUI_KEYBOARD_APPEARANCE_NONE_IMMERSIVE**, which indicates no immersive style is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: keyboard appearance. The parameter type is {@link ArkUI_KeyboardAppearanceType}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 15
     */
    NODE_TEXT_INPUT_KEYBOARD_APPEARANCE = 7035,

    /**
     * @brief Whether to enable the autofill animation. This animation takes effect only when the input box type {@link
     * ArkUI_TextInputType} is set to **ARKUI_TEXTINPUT_TYPE_PASSWORD**, **ARKUI_TEXTINPUT_TYPE_NUMBER_PASSWORD**, or
     * **ARKUI_TEXTINPUT_TYPE_NEW_PASSWORD**.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable the autofill animation. When enabled, the animation takes effect during
     * auto-fill only for the input box whose {@link ArkUI_TextInputType} is set to **ARKUI_TEXTINPUT_TYPE_PASSWORD**,
     * **ARKUI_TEXTINPUT_TYPE_NUMBER_PASSWORD**, or **ARKUI_TEXTINPUT_TYPE_NEW_PASSWORD**. **1** to enable; **0**
     * otherwise. Default value: **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the autofill animation is enabled. The value **1** means enabled, and **0** means
     * disabled. When enabled, the animation takes effect during auto-fill only for the input box whose
     * {@link ArkUI_TextInputType} enumeration is set to **ARKUI_TEXTINPUT_TYPE_PASSWORD**,
     * **ARKUI_TEXTINPUT_TYPE_NUMBER_PASSWORD**, or **ARKUI_TEXTINPUT_TYPE_NEW_PASSWORD**.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 20
     */
    NODE_TEXT_INPUT_ENABLE_FILL_ANIMATION = 7036,

    /**
     * @brief Line height of text in the text box. This attribute can be set, reset, and obtained as required through
     * APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: text line height, in fp. The default value is adaptive to the font size.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: text line height, in fp. The default value is adaptive to the font size.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 20
     */
    NODE_TEXT_INPUT_LINE_HEIGHT = 7037,

    /**
     * @brief Whether to enable entity recognition for selected text. This attribute supports the recognition of entity
     * information such as phone numbers, email addresses, and URLs in the selected text, making it convenient for users
     * to quickly make calls, send emails, or open URLs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable entity recognition for selected text. **1** to enable; **0** otherwise. The
     * default value is **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether entity recognition for selected text is enabled. The value **1** indicates entity
     * recognition is enabled, and **0** indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 22
     */
    NODE_TEXT_INPUT_ENABLE_SELECTED_DATA_DETECTOR = 7038,

    /**
     * @brief Whether to show a counter and its style when the number of input characters exceeds a threshold. This
     * attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to show a counter. **1** to show; **0** otherwise.</li>
     * <li>.value[1]?.f32: Percentage of the number of characters that can be entered to the maximum number of
     * characters
     * allowed. When the percentage exceeds this value, the counter is shown. The value range is [1,
     * 100]. If the value is a decimal, it is rounded down. If the value is out of the range, the
     * attribute setting does not take effect. The default value is **-1**, meaning the counter is
     * always shown.</li>
     * <li>.value[2]?.i32: Whether to highlight the border when the number of entered characters exceeds the maximum.
     * **1**
     * means to highlight; **0** otherwise.</li>
     * <li>.object: Counter configuration. The configuration attributes are the color of the counter when the number of
     * characters entered in the text box does not reach the maximum and the color of the counter when the
     * number of characters entered in the text box exceeds the maximum. The parameter type is {@link
     * ArkUI_ShowCounterConfig}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the counter is shown. The value **1** means the counter is shown, and **0** means the
     * opposite.</li>
     * <li>.value[1].f32: Percentage of the number of characters that can be entered to the maximum number of characters
     * allowed. When the percentage exceeds this value, the counter is shown. The value range is [1,
     * 100].</li>
     * <li>.value[2].i32: Whether the border is highlighted when the number of entered characters exceeds the maximum.
     * **1**
     * indicates that the border is highlighted; **0** otherwise.</li>
     * <li>.object: Counter configuration. The configuration attributes are the color of the counter when the number of
     * characters entered in the text box does not reach the maximum and the color of the counter when the
     * number of characters entered in the text box exceeds the maximum. The parameter type is {@link
     * ArkUI_ShowCounterConfig}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 22
     */
    NODE_TEXT_INPUT_SHOW_COUNTER = 7040,

    /**
     * @brief Text input controller.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Basic controller for text. The parameter type is {@link ArkUI_TextContentBaseController}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Basic controller for text. The parameter type is {@link ArkUI_TextContentBaseController}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 23
     */
    NODE_TEXT_INPUT_TEXT_CONTENT_CONTROLLER_BASE = 7041,

    /**
     * @brief Text ellipsis mode of the single-line text box.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32:
     * The parameter type is {@link ArkUI_EllipsisMode}, the default value is ARKUI_ELLIPSIS_MODE_END.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: The parameter type is {@link ArkUI_EllipsisMode}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 24
     */
    NODE_TEXT_INPUT_ELLIPSIS_MODE = 7042,

    /**
     * @brief Whether to enable orphan character optimization for text layout in the **TextInput** component. When set,
     * the orphan character (the first character in the last line of a paragraph) is processed more efficiently to
     * improve the text layout. When enabled, it adjusts line break points to avoid orphan characters as much as
     * possible.<br>Note: The orphan character optimization feature takes effect only when the {@link ArkUI_WordBreak}
     * attribute is not set to **ARKUI_WORD_BREAK_BREAK_ALL**.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32:  Whether enable the feature, true means enable this feature, false means disable. The default
     * value is false.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: The current state of this feature.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
 	  NODE_TEXT_INPUT_ORPHAN_CHAR_OPTIMIZATION = 7043,

    /**
     * @brief Whether to enable leading punctuation compression of a text line.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32:  Whether enable the feature, true means enable this feature, false means disable. The default
     * value is false.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether compress punctuation at the beginning of line.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 23
     */
    NODE_TEXT_INPUT_COMPRESS_LEADING_PUNCTUATION = 7044,

    /**
     * @brief Whether to add spacing to the top of the first line and the bottom of the last line of text in a
     * single-line text box to avoid text truncation.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Enable include the font padding, true means enable this feature, false means disable. The
     * default value is false.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether include the font padding.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 23
     */
    NODE_TEXT_INPUT_INCLUDE_FONT_PADDING = 7045,

    /**
     * @brief Whether the line height can be automatically adjusted based on the actual text height for multi-line text
     * display. This enumerated value takes effect only when the line height is smaller than the actual text height.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32:  Whether enable the feature, true means enable this feature, false means disable. The default
     * value is false.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether fallback line spacing.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 23
     */
    NODE_TEXT_INPUT_FALLBACK_LINE_SPACING = 7046,

    /**
     * @brief Text layout direction of the single-line text box.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: writing direction of the text. The value is an enum of {@link ArkUI_TextDirection}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: writing direction the text. The value is an enum of {@link ArkUI_TextDirection}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 23
     */
    NODE_TEXT_INPUT_DIRECTION = 7047,

    /**
     * @brief Drag preview style when the text in the text box is selected.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: selected drag preview style configuration.
     * The parameter type is {@link ArkUI_SelectedDragPreviewStyle}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: selected drag preview style configuration.
     * The parameter type is {@link ArkUI_SelectedDragPreviewStyle}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 23
     */
    NODE_TEXT_INPUT_SELECTED_DRAG_PREVIEW_STYLE = 7048,

    /**
     * @brief Display mode when the text is too long in the single-line text box.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: display mode when the text is too long {@link ArkUI_TextOverflow}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: display mode when the text is too long {@link ArkUI_TextOverflow}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 24
     */
    NODE_TEXT_INPUT_TEXT_OVERFLOW = 7049,

    /**
     * @brief Text decorative line style and color of the single-line text box.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>?.object: Optional. The decoration style options.
     * The parameter type is {@link OH_ArkUI_DecorationStyleOptions}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: The decoration style options. The parameter type is {@link OH_ArkUI_DecorationStyleOptions}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_DECORATION = 7050,

    /**
     * @brief Linear gradient effect of the text in the text box.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: start angle of the linear gradient. The setting takes effect only when <b>direction</b> is
     * set to <b>ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM</b>. A positive value indicates a clockwise rotation from the
     * origin, (0, 0). The default value is <b>180</b>.</li>
     * <li>.value[1].i32: direction of the linear gradient. When a direction other than
     * <b>ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM</b> is set, the <b>angle</b> property is ignored.
     * The parameter type is {@link ArkUI_LinearGradientDirection}.</li>
     * <li>.value[2].i32: whether the colors are repeated. The default value is <b>false</b>.</li>
     * <li>.object: array of color stops, each of which consists of a color and its stop position.
     * The parameter type is {@link ArkUI_ColorStop}. Invalid colors are automatically skipped. colors: colors of the
     * color stops. stops: stop positions of the color stops. size: number of colors.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: start angle of the linear gradient. When <b>direction</b> is set to
     * <b>ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM</b>, <b>angle</b> at the set value; otherwise, it is at default
     * value.</li>
     * <li>.value[1].i32: direction of the linear gradient.</li>
     * <li>.value[2].i32: whether the colors are repeated.</li>
     * <li>.object: array of color stops, each of which consists of a color and its stop position.
     * The parameter type is {@link ArkUI_ColorStop}. Invalid colors are automatically skipped. colors: colors of the
     * color stops. stops: stop positions of the color stops. size: number of colors.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_LINEAR_GRADIENT = 7051,

    /**
     * @brief Radial gradient effect of the text in the text box.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0]?.f32: X-coordinate of the radial gradient center relative to the upper left corner of the
     * text.</li>
     * <li>.value[1]?.f32: Y-coordinate of the radial gradient center relative to the upper left corner of the
     * text.</li>
     * <li>.value[2]?.f32: radius of the radial gradient. The default value is <b>0</b>.</li>
     * <li>.value[3]?.i32: whether the colors are repeated. The value <b>1</b> means that the colors are repeated, and
     * <b>0</b> means the opposite.</li>
     * <li>.object: array of color stops, each of which consists of a color and its stop position.
     * The parameter type is {@link ArkUI_ColorStop}. Invalid colors are automatically skipped. colors: colors of the
     * color stops. stops: stop positions of the color stops. size: number of colors.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: X-coordinate of the radial gradient center relative to the upper left corner of the text.</li>
     * <li>.value[1].f32: Y-coordinate of the radial gradient center relative to the upper left corner of the text.</li>
     * <li>.value[2].f32: radius of the radial gradient. The default value is <b>0</b>.</li>
     * <li>.value[3].i32: whether the colors are repeated. The value <b>1</b> means that the colors are repeated, and
     * <b>0</b> means the opposite.</li>
     * <li>.object: array of color stops, each of which consists of a color and its stop position.
     * The parameter type is {@link ArkUI_ColorStop}. Invalid colors are automatically skipped. colors: colors of the
     * color stops. stops: stop positions of the color stops. size: number of colors.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_RADIAL_GRADIENT = 7052,

    /**
     * @brief Whether to enable punctuation hanging at the end of a line for the **TextInput** component.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable punctuation overflow, the default value is false.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to enable punctuation overflow.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_PUNCTUATION_OVERFLOW = 7053,

    /**
     * @brief Defines the default placeholder text for the multi-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: default placeholder text.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: default placeholder text.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_PLACEHOLDER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_AREA,
    /**
     * @brief Defines the default text content for the multi-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: default text content.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: default text content.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_TEXT,
    /**
     * @brief Maximum number of characters in the text input.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: maximum number of characters in the text input.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: maximum number of characters in the text input.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_MAX_LENGTH,
    /**
     * @brief Default placeholder text color when there is no input.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: color value, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_PLACEHOLDER_COLOR,
    /**
     * @brief Defines the placeholder text font.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0]?.f32: font size, in fp. Optional. The default value is <b>16.0</b>.</li>
     * <li>.value[1]?.i32: font style {@link ArkUI_FontStyle}. Optional. The default value is <b>ARKUI_FONT_STYLE_NORMAL</b>.</li>
     * <li>.value[2]?.i32: font weight {@link ArkUI_FontWeight}. Optional. The default value is <b>ARKUI_FONT_WEIGHT_NORMAL</b>.</li>
     * <li>?.string: font family. Multiple font families are separated by commas (,). For example, "font weight; font family 1, font family 2".</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: font size, in fp.</li>
     * <li>.value[1].i32: font style {@link ArkUI_FontStyle}.</li>
     * <li>.value[2].i32: font weight {@link ArkUI_FontWeight}.</li>
     * <li>.string: font family. Multiple font families are separated by commas (,).</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_PLACEHOLDER_FONT,
    /**
     * @brief Caret color attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format. For example, 0xFFFF0000 indicates red.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_CARET_COLOR,
    /**
     * @brief Editable state for the multi-line text box.
     *
     * This attribute can be set and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to remain in the editable state. The value <b>true</b> means to remain in the
     * editable state, and <b>false</b> means to exit the editable state.</li>
     * </ul>
     *
     * **Format of the {@link ArkUI_AttributeItem} for obtaining the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to remain in the editable state. The value <b>true</b> means to remain in the
     * editable state, and <b>false</b> means to exit the editable state.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_EDITING,
    /**
     * @brief Text area type. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: text box type {@link ArkUI_TextAreaType}.
     * The default value is <b>ARKUI_TEXTAREA_TYPE_NORMAL</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: text box type {@link ArkUI_TextAreaType}.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_TYPE,
    /**
     * @brief Whether to show a counter and its style when the number of input characters exceeds a threshold.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to show the counter. **1** to show; **0** otherwise. The default value is **0**.</li>
     * <li>.value[1]?.f32: Percentage of the number of characters that can be entered to the maximum number of
     * characters
     * allowed. When the percentage exceeds this value, the counter is shown. The value range is [1,
     * 100]. If the value is a decimal, it is rounded down. If the value is out of the range, the
     * attribute setting does not take effect. The default value is **-1**, which means the counter is
     * always shown.</li>
     * <li>.value[2]?.i32: Whether to highlight the border when the number of entered characters exceeds the maximum.
     * **1**
     * to highlight; **0** otherwise. The default value is **1**.</li>
     * <li>.object: Counter configuration. The configuration attributes are the color of the counter when the number of
     * characters entered in the text box does not reach the maximum and the color of the counter when the
     * number of characters entered in the text box exceeds the maximum. The parameter type is {@link
     * ArkUI_ShowCounterConfig}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the counter is shown. **1** indicates the counter is shown; **0** otherwise.</li>
     * <li>.value[1].f32: Percentage of the number of characters that can be entered to the maximum number of characters
     * allowed. When the percentage exceeds this value, the counter is shown. The value range is [1,
     * 100].</li>
     * <li>.value[2].i32: Whether the border is highlighted when the number of entered characters exceeds the maximum.
     * **1**
     * indicates that the border is highlighted, and **0** indicates the opposite.</li>
     * <li>.object: Counter configuration. The configuration attributes are the color of the counter when the number of
     * characters entered in the text box does not reach the maximum and the color of the counter when the
     * number of characters entered in the text box exceeds the maximum. The parameter type is {@link
     * ArkUI_ShowCounterConfig}.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_SHOW_COUNTER,
    /**
     * @brief Whether to hide the text selection menu when the text box is long-pressed, double-tapped, or
     * right-clicked.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to hide the text selection menu when the text box is long-pressed, double-click, or
     * right-clicked. The default value is <b>false</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the text selection menu is hidden when the text box is long-pressed, double-tapped,
     * right-clicked.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_SELECTION_MENU_HIDDEN,
    /**
     * @brief Sets whether the multi-line text box loses focus after the Enter key is pressed to submit information.
     * 
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the text box loses focus.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the text box loses focus.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_BLUR_ON_SUBMIT,
    /**
     * @brief Regular expression for input filtering.
     *
     * Only inputs that comply with the regular expression can be displayed. Other inputs are filtered out. For
     * single-character input scenarios, only single-character matching is supported; for multi-character input
     * scenarios (such as pasting), string matching is supported.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: regular expression.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: regular expression.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_INPUT_FILTER,
    /**
     * @brief Background color of the selected text.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: color value, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_SELECTED_BACKGROUND_COLOR,
    /**
     * @brief Defines the type of the Enter key.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: type of the Enter key{@link ArkUI_EnterKeyType}. The default value is <b>ARKUI_ENTER_KEY_TYPE_DONE</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: type of the Enter key{@link ArkUI_EnterKeyType}.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ENTER_KEY_TYPE,
    /**
     * @brief Whether to enable the input method when the **TextArea** component obtains focus in a way other than
     * clicking.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable the input method when the **TextArea** component obtains focus in a way
     * other
     * than clicking. **1** means to enable, and **0** to disable. Default value: **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the input method is enabled when the component obtains focus.
     * The value **1** means that
     * the input method is enabled when the component obtains focus, and **0** means the opposite.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ENABLE_KEYBOARD_ON_FOCUS,
    /**
     * @brief Caret position.
     *
     * Sets the position of the caret.
     *
     * Returns the position information of the caret. If this API is called when the caret position is updated in the
     * current frame, it will not take effect.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Length of characters from the beginning of the string to the position of the cursor.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Index value of the cursor position.</li>
     * <li>.value[1].f32: indicates the x-coordinate value of the cursor relative to the text box.</li>
     * <li>.value[2].f32: indicates the y-coordinate value of the cursor relative to the text box.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_CARET_OFFSET,
    /**
     * @brief Position of the edited text area relative to the component and its size.
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: X-coordinate, in px.</li>
     * <li>.value[1].f32: Y-coordinate, in px.</li>
     * <li>.value[2].f32: content width, in px.</li>
     * <li>.value[3].f32: content height.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_CONTENT_RECT,
    /**
     * @brief Number of lines of the edited text.
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: number of lines of the edited text.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_CONTENT_LINE_COUNT,
    /**
     * @brief Text selection range, which will be highlighted, when the component is focused.
     *
     * This enumerated value works only when the value of **selectionStart** is less than that of **selectionEnd**.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: start position of the text selection.</li>
     * <li>.value[1].i32: end position of the text selection.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: start position of the text selection.</li>
     * <li>.value[1].i32: end position of the text selection.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_TEXT_SELECTION,
    /**
     * @brief Whether to enable autofill.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable autofill.
     * **1** indicates to enable, and **0** indicates the opposite.
     * Default value: **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether autofill is enabled. **1** indicates enabled, and **0** indicates disabled.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ENABLE_AUTO_FILL,
    /**
     * @brief Autofill type.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Autofill type. The parameter type is {@link ArkUI_TextInputContentType}.
     * It is used to specify the
     * auto filled content type so that the system can provide more accurate autofill suggestions.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Autofill type. The parameter type is {@link ArkUI_TextInputContentType}.
     * It is used to specify the
     * auto filled content type so that the system can provide more accurate autofill suggestions.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_CONTENT_TYPE,

    /**
     * @brief Whether to show the keyboard when the text box obtains focus.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to pop up the keyboard.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether to pop up the keyboard.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_SHOW_KEYBOARD_ON_FOCUS,

    /**
     * @brief When this property is set, the height of the textArea component is calculated using this property.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: set the value of numberOfLines.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Set the value of numberOfLines.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_NUMBER_OF_LINES,

    /**
     * @brief Letter spacing of the **TextArea** component.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: letter spacing. The default unit is fp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: letter spacing. The default unit is fp.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 15
     */
    NODE_TEXT_AREA_LETTER_SPACING = 8023,
    /**
     * @brief Whether to enable preview text for the **TextArea** component.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * "Preview text" describes a temporary text staging state. The preview text feature must be enabled in the input
     * method. During text input, before a candidate word is confirmed, marked text is displayed in the text box. For
     * example, when entering Chinese characters via Pinyin, the Pinyin letters are displayed in the input box before
     * the candidate word is confirmed. This state is called preview.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable preview tex.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to enable preview tex.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 15
     */
    NODE_TEXT_AREA_ENABLE_PREVIEW_TEXT = 8024,

    /**
     * @brief Whether to enable half leading.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to center text vertically. The default value is <b>false</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to center text vertically.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 18
     */
    NODE_TEXT_AREA_HALF_LEADING = 8025,

    /**
     * @brief Set the keyboard style of textArea
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: keyboard style, the parameter type is {@link ArkUI_KeyboardAppearanceType}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: keyboard style, the parameter type is {@link ArkUI_KeyboardAppearanceType}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 15
     */
    NODE_TEXT_AREA_KEYBOARD_APPEARANCE = 8026,

    /**
     * @brief Maximum number of lines that can be displayed with the inline style in the editing state.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: max lines count.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: max lines count.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 20
     */
    NODE_TEXT_AREA_MAX_LINES = 8027,

    /**
     * @brief Line spacing of text in the text box.
     *
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: line spacing value.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: line spacing value.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 20
     */
    NODE_TEXT_AREA_LINE_SPACING = 8028,

    /**
     * @brief Minimum number of lines for the node. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Minimum number of lines. The value range is [1, +∞). The setting does not take effect
     * when 0 or a negative value is passed.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Minimum number of lines. The value range is [1, +∞).</li>
     * </ul>
     *
     * @since 20
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_MIN_LINES = 8029,

    /**
     * @brief Maximum number of lines for the node when scrolling is enabled.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Maximum number of lines when scrolling is enabled. Value range: [1, +∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Maximum number of lines when scrolling is enabled. Value range: [1, +∞).</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 20
     */
    NODE_TEXT_AREA_MAX_LINES_WITH_SCROLL = 8030,

    /**
     * @brief Line height of text in the text box. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Text line height, in fp. The default value is adaptive to the font size.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Text line height, in fp.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 20
     */
    NODE_TEXT_AREA_LINE_HEIGHT = 8031,

    /**
     * @brief Scrollbar status of the text input box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Scrollbar status of the text input box. The parameter type is {@link ArkUI_BarState}. The
     * default value is <b>ARKUI_BAR_STATE_AUTO</b>, which indicates the scrollbar is displayed as needed (displayed
     * upon touch and automatically disappears after 2 seconds).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Scrollbar status of the text input box. The parameter type is {@link ArkUI_BarState}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 22
     */
     NODE_TEXT_AREA_BAR_STATE = 8032,

    /**
     * @brief Whether to enable entity recognition for selected text, supporting the recognition of entity
     * information such as phone numbers, email addresses, and URLs in the selected text, making it convenient for
     * users to quickly make calls, send emails, or open URLs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable entity recognition for selected text. <b>1</b> to enable; <b>0</b>
     * otherwise. Default value: <b>1</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether entity recognition for selected text is enabled. <b>1</b> indicates enabled, and
     * <b>0</b> indicates disabled.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 22
     */
    NODE_TEXT_AREA_ENABLE_SELECTED_DATA_DETECTOR = 8033,

    /**
     * @brief Scrollbar color of the text box. This attribute can be set, reset, and obtained as required through
     * APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.data[0].u32: Scrollbar color, in 0xARGB format. Default value: <b>0x66182431</b>, indicating gray.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.data[0].u32: Scrollbar color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 22
     */
     NODE_TEXT_AREA_SCROLL_BAR_COLOR = 8035,

    /**
     * @brief Custom keyboard of the text box. This attribute can be set, reset, and obtained as required through
     * APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Custom keyboard. The parameter type is {@link ArkUI_NodeHandle}.</li>
     * <li>.value[0]?.i32: Whether the custom keyboard supports the avoidance feature. <b>1</b> indicates support
     * for avoidance, and <b>0</b> indicates the opposite. Default value: <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Custom keyboard. The parameter type is {@link ArkUI_NodeHandle}.</li>
     * <li>.value[0].i32: Whether the custom keyboard supports the avoidance feature. <b>1</b> indicates support
     * for avoidance, and <b>0</b> indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 22
     */
    NODE_TEXT_AREA_CUSTOM_KEYBOARD = 8036,

    /**
     * @brief Text area controller.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Basic controller of the text content.
     * The parameter type is {@link ArkUI_TextContentBaseController}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Basic controller of the text content.
     * The parameter type is {@link ArkUI_TextContentBaseController}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 23
     */
    NODE_TEXT_AREA_TEXT_CONTENT_CONTROLLER_BASE = 8037,

    /**
     * @brief Text ellipsis mode of the multi-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * This attribute has the following configuration dependencies:
     * <ul>
     * <li>This attribute takes effect only when <b>NODE_TEXT_AREA_TEXT_OVERFLOW</b> is set to
     * <b>ARKUI_TEXT_OVERFLOW_ELLIPSIS</b>.</li>
     * <li>When <b>TEXT_OVERFLOW</b> is set to <b>ARKUI_TEXT_OVERFLOW_CLIP</b>, the <b>ELLIPSIS_MODE</b> setting
     * does not take effect.</li>
     * <li>It is recommended to set <b>TEXT_OVERFLOW</b> to <b>ELLIPSIS</b> first, and then set
     * <b>ELLIPSIS_MODE</b> to a specified ellipsis position.</li>
     * </ul>
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Ellipsis mode. The parameter type {@link ArkUI_EllipsisMode}. For details about the
     * enumerated values, see the {@link ArkUI_EllipsisMode} description. The default value is
     * <b>ARKUI_ELLIPSIS_MODE_END</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Enum for text ellipsis position {@link ArkUI_EllipsisMode}, used to determine the
     * ellipsis position when text exceeds the limit.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 24
     */
    NODE_TEXT_AREA_ELLIPSIS_MODE = 8038,

    /**
     * @brief Whether to enable orphan character optimization for text layout in the <b>TextArea</b> component.
     * When set, the orphan character (the first character in the last line of a paragraph) is processed more
     * efficiently to improve the text layout. When enabled, it adjusts line break points to avoid orphan
     * characters as much as possible. The orphan character optimization feature takes effect only when the
     * {@link ArkUI_WordBreak} attribute is not set to <b>ARKUI_WORD_BREAK_BREAK_ALL</b>.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable orphan character optimization. This feature takes effect only when the
     * {@link ArkUI_WordBreak} attribute is not <b>ARKUI_WORD_BREAK_BREAK_ALL</b>. <b>1</b> to enable; <b>0</b>
     * otherwise. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether orphan character optimization is enabled. The value <b>1</b> means enabled, and
     * <b>0</b> means disabled.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_AREA_ORPHAN_CHAR_OPTIMIZATION = 8039,

    /**
     * @brief Whether to enable the feature of compressing punctuations at the beginning of a text line.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable leading punctuation compression. <b>1</b> indicates to enable, and
     * <b>0</b> indicates the opposite. Default value: <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether leading punctuation compression is enabled. <b>1</b> indicates enabled, and
     * <b>0</b> indicates disabled.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 23
     */
    NODE_TEXT_AREA_COMPRESS_LEADING_PUNCTUATION = 8040,

    /**
     * @brief Whether to add spacing to the first and last lines of text in a multi-line text box to avoid text
     * truncation.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to add spacing to the first and last lines of text in a text box to avoid text
     * truncation. <b>1</b> to add; <b>0</b> otherwise. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether spacing is added to the first and last lines of text in a text box. <b>1</b>
     * indicates spacing is added; <b>0</b> otherwise.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 23
     */
    NODE_TEXT_AREA_INCLUDE_FONT_PADDING = 8041,

    /**
     * @brief Whether the line height can be automatically adjusted based on the actual text height for multi-line
     * text display. This enumerated value takes effect only when the line height is smaller than the actual text
     * height.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the line height can be automatically adjusted based on the actual text height.
     * <b>1</b> to be adjusted; <b>0</b> otherwise. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the line height can be automatically adjusted based on the actual text height.
     * <b>1</b> means that the line height can be automatically adjusted; <b>0</b> otherwise.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 23
     */
    NODE_TEXT_AREA_FALLBACK_LINE_SPACING = 8042,

    /**
     * @brief Whether to enable horizontal scrolling for a multi-line text box when the text width exceeds the width
     * of the content area in the text box. The default value is <b>0</b>, meaning that the text will be
     * automatically wrapped by the text box.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable horizontal scrolling. <b>1</b> to enable; <b>0</b> otherwise. Default
     * value: <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether horizontal scrolling is enabled. <b>1</b> indicates enabled, and <b>0</b>
     * indicates disabled.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 24
     */
    NODE_TEXT_AREA_HORIZONTAL_SCROLLING = 8043,

    /**
     * @brief Text layout direction of the multi-line text box.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Text layout direction. The value is an enumerated value of
     * {@link ArkUI_TextDirection}. The default value is <b>ARKUI_TEXT_DIRECTION_DEFAULT</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Text layout direction. For details about the values and meanings, see the enumerated
     * values of {@link ArkUI_TextDirection}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 23
     */
    NODE_TEXT_AREA_DIRECTION = 8044,

    /**
     * @brief Drag preview style when the text in the multi-line text box is selected.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Drag preview style when the text is selected.
     * The parameter type is {@link ArkUI_SelectedDragPreviewStyle}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Drag preview style when the text is selected.
     * The parameter type is {@link ArkUI_SelectedDragPreviewStyle}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 23
     */
    NODE_TEXT_AREA_SELECTED_DRAG_PREVIEW_STYLE = 8045,

    /**
     * @brief Display mode when the text is too long in the multi-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Display mode when the text is too long. The value is an enumerated value of
     * {@link ArkUI_TextOverflow}. The default value is <b>ARKUI_TEXT_OVERFLOW_CLIP</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Display mode when the text is too long. The value is an enumerated value of
     * {@link ArkUI_TextOverflow}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 24
     */
    NODE_TEXT_AREA_TEXT_OVERFLOW = 8046,

    /**
     * @brief Text decorative line style and color of the multi-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>?.object: Decoration style options. This parameter is optional.
     * The parameter type is {@link OH_ArkUI_DecorationStyleOptions}. When not passed, no decoration line is
     * added.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Decoration style options. The parameter type is
     * {@link OH_ArkUI_DecorationStyleOptions}.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_AREA_DECORATION = 8047,

    /**
     * @brief Linear gradient effect of the text in the multi-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Start angle of the linear gradient, in degree. When the linear gradient direction is
     * <b>ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM</b> of {@link ArkUI_LinearGradientDirection}, the start angle of the
     * linear gradient takes effect. Otherwise, the linear gradient direction is used as the main layout mode. The
     * value range is (-∞,+∞). A positive value indicates a clockwise rotation from the origin (0, 0). When the
     * value exceeds 360, the remainder of 360 is used. The default value is <b>180</b>.</li>
     * <li>.value[1].i32: Direction of the linear gradient. The value is an enumerated value of
     * {@link ArkUI_LinearGradientDirection}. If the linear gradient direction is set to a value other than
     * <b>ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM</b> of {@link ArkUI_LinearGradientDirection}, the start angle of
     * the linear gradient does not take effect. Default value:
     * <b>ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_BOTTOM</b> of {@link ArkUI_LinearGradientDirection}.</li>
     * <li>.value[2].i32: Whether the gradient colors are repeated. The value <b>0</b> indicates that the gradient
     * colors are not repeated, and <b>1</b> indicates that the gradient colors are repeated. The default value is
     * <b>0</b>.</li>
     * <li>.object: Color stop. The parameter type is {@link ArkUI_ColorStop}.
     * <b>colors</b>: colors of the color stops, in 0xARGB format. For example, <b>0xFFFF0000</b> indicates red.
     * <b>stops</b>: stop positions of the color stops. The value range is [0, 1.0]. <b>0</b> represents the start
     * of the gradient container, and <b>1.0</b> represents the end. To create a gradient with multiple color stops,
     * you are advised to set the array elements in ascending order. If a later element is smaller than a previous
     * one, it will be treated as equal to the previous value.
     * <b>size</b>: number of colors. If the value is smaller than the length of the <b>colors</b> array, only the
     * first <b>size</b> colors take effect. Values greater than the <b>colors</b> array length, values less than or
     * equal to 0, or invalid values are not recommended.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Start angle of the linear gradient, in degree. When the direction of the linear gradient is
     * <b>ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM</b> of {@link ArkUI_LinearGradientDirection}, the start angle is
     * the set value. In other cases, the default value <b>0</b> is used.</li>
     * <li>.value[1].i32: Direction of the linear gradient. For details about the values and meanings, see
     * {@link ArkUI_LinearGradientDirection}.</li>
     * <li>.value[2].i32: Whether the gradient colors are repeated. The value <b>0</b> indicates that the gradient
     * colors are not repeated, and <b>1</b> indicates that the gradient colors are repeated. The default value is
     * <b>0</b>.</li>
     * <li>.object: Color stop. The parameter type is {@link ArkUI_ColorStop}.
     * <b>colors</b>: colors of the color stops, in 0xARGB format. For example, <b>0xFFFF0000</b> indicates red.
     * <b>stops</b>: stop positions of the color stops. The value range is [0, 1.0]. <b>0</b> represents the start
     * of the gradient container, and <b>1.0</b> represents the end.
     * <b>size</b>: number of effective gradient colors.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_AREA_LINEAR_GRADIENT = 8048,

    /**
     * @brief Radial gradient effect of the text in the multi-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0]?.f32: X-coordinate of the radial gradient center relative to the upper left corner of the
     * multi-line text box, in vp. The default value is half the width of the multi-line text input box.</li>
     * <li>.value[1]?.f32: Y-coordinate of the radial gradient center relative to the upper left corner of the
     * multi-line text box, in vp. The default value is half the height of the multi-line text input box.</li>
     * <li>.value[2]?.f32: Radius of the radial gradient. The value range is [0, +∞), and the default value is
     * <b>0</b>. If a negative value is passed, the setting does not take effect.</li>
     * <li>.value[3]?.i32: Whether the gradient colors are repeated. The value <b>0</b> indicates that the gradient
     * colors are not repeated, and <b>1</b> indicates that the gradient colors are repeated. The default value is
     * <b>0</b>.</li>
     * <li>.object: Color stop. The parameter type is {@link ArkUI_ColorStop}.
     * <b>colors</b>: colors of the color stops, in 0xARGB format. For example, <b>0xFFFF0000</b> indicates red.
     * <b>stops</b>: stop positions of the color stops. The value range is [0, 1.0]. <b>0</b> represents the start
     * of the gradient container, and <b>1.0</b> represents the end. To create a gradient with multiple color stops,
     * you are advised to set the array elements in ascending order. If a later element is smaller than a previous
     * one, it will be treated as equal to the previous value.
     * <b>size</b>: number of colors. If the value is smaller than the length of the <b>colors</b> array, only the
     * first <b>size</b> colors take effect. Values greater than the <b>colors</b> array length, values less than or
     * equal to 0, or invalid values are not recommended.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0]?.f32: X-coordinate of the radial gradient center relative to the upper left corner of the
     * multi-line text box, in vp.</li>
     * <li>.value[1]?.f32: Y-coordinate of the radial gradient center relative to the upper left corner of the
     * multi-line text box, in vp.</li>
     * <li>.value[2]?.f32: Radius of the radial gradient, in vp. Default value: <b>0</b>.</li>
     * <li>.value[3]?.i32: Whether the gradient colors are repeated. The value <b>0</b> indicates that the gradient
     * color is not repeated, and <b>1</b> indicates that the gradient color is repeated. The default value is
     * <b>0</b>.</li>
     * <li>.object: Color stop. The parameter type is {@link ArkUI_ColorStop}.
     * <b>colors</b>: colors of the color stops, in 0xARGB format. For example, <b>0xFFFF0000</b> indicates red.
     * <b>stops</b>: stop positions of the color stops. The value range is [0, 1.0]. <b>0</b> represents the start
     * of the gradient container, and <b>1.0</b> represents the end.
     * <b>size</b>: number of effective gradient colors.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_AREA_RADIAL_GRADIENT = 8049,

    /**
     * @brief Whether to enable punctuation hanging at the end of a line for the <b>TextArea</b> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable punctuation hanging at the end of a line. The value <b>1</b> means to
     * enable, and <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether punctuation hanging at the end of a line is enabled. <b>1</b> indicates enabled,
     * <b>0</b> indicates disabled.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_AREA_PUNCTUATION_OVERFLOW = 8050,

    /**
     * @brief Defines the button text content. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.string: default text content.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.string: default text content.</li> \n
     * </ul>
     *
     * @ingroup Button
     */
    NODE_BUTTON_LABEL = MAX_NODE_SCOPE_NUM * ARKUI_NODE_BUTTON,

    /**
     * @brief Button type. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: Button type. The parameter type is {@link ArkUI_ButtonType}.
     * The default value is **ARKUI_BUTTON_TYPE_CAPSULE**.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: Button type. The parameter type is {@link ArkUI_ButtonType}.
     * The default value is **ARKUI_BUTTON_TYPE_CAPSULE**.</li> \n
     * </ul>
     *
     * @ingroup Button
     */
    NODE_BUTTON_TYPE,

    /**
     * @brief Minimum font scale factor for the button. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: Minimum font scale factor for the button. The default unit is fp.</li>
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: Minimum font scale factor for the button. The default unit is fp.</li>
     * </ul>
     *
     * @ingroup Button
     * @since 18
     */
    NODE_BUTTON_MIN_FONT_SCALE,

    /**
     * @brief Maximum font scale factor for the button. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: Maximum font scale factor for the button. The default unit is fp.</li>
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: Maximum font scale factor for the button. The default unit is fp.</li>
     * </ul>
     *
     * @ingroup Button
     * @since 18
     */
    NODE_BUTTON_MAX_FONT_SCALE,

    /**
     * @brief Defines the current value of the progress indicator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: current value of the progress indicator.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: current value of the progress indicator.</li>
     * </ul>
     *
     * @ingroup Information Display
     */
    NODE_PROGRESS_VALUE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_PROGRESS,
    /**
     * @brief Total value of the progress indicator. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: total value of the progress indicator.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: total value of the progress indicator.</li>
     * </ul>
     *
     * @ingroup Information Display
     */
    NODE_PROGRESS_TOTAL,
    /**
     * @brief Color for the progress value on the progress indicator. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: color value, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Information Display
     */
    NODE_PROGRESS_COLOR,
    /**
     * @brief Type of the progress indicator. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: type of the progress indicator {@link ArkUI_ProgressType}.
     * The default value is <b>ARKUI_PROGRESS_TYPE_LINEAR</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: type of the progress indicator {@link ArkUI_ProgressType}.</li>
     * </ul>
     *
     * @ingroup Information Display
     */
    NODE_PROGRESS_TYPE,
    /**
     * @brief Linear progress indicator style. This attribute can be set, reset, and obtained as required through APIs.
     * It does not take effect if the progress indicator type is not linear. In this case, set the progress indicator
     * type to **ARKUI_PROGRESS_TYPE_LINEAR** through **NODE_PROGRESS_TYPE** first.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Use the {@link ArkUI_ProgressLinearStyleOption} object to set the style.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Use the {@link ArkUI_ProgressLinearStyleOption} object to get the style.</li>
     * </ul>
     *
     * @ingroup Information Display
     * @since 15
     */
    NODE_PROGRESS_LINEAR_STYLE,

    /**
     * @brief Defines whether the check box is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: whether the check box is selected.
     * The value <b>1</b> means that the check box is selected, and <b>0</b> means the opposite.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: The value <b>1</b> means that the check box is selected,
     * and <b>0</b> means the opposite.</li> \n
     * </ul>
     *
     * @ingroup Checkbox
     */
    NODE_CHECKBOX_SELECT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CHECKBOX,

    /**
     * @brief Color of the **CheckBox** component when it is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: Color of the check box when it is selected, in 0xARGB format, for example,
     * **0xFF1122FF**.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: Color of the check box when it is selected, in 0xARGB format, for example,
     * **0xFF1122FF**.</li>
     * </ul>
     *
     * @ingroup Checkbox
     */
    NODE_CHECKBOX_SELECT_COLOR,

    /**
     * @brief Border color of the **CheckBox** component when it is not selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: Border color, in 0xARGB format, for example, **0xFF1122FF**.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: Border color, in 0xARGB format, for example, **0xFF1122FF**.</li>
     * </ul>
     *
     * @ingroup Checkbox
     */
    NODE_CHECKBOX_UNSELECT_COLOR,

    /**
     * @brief Internal mark style of the **CheckBox** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: Border color, in 0xARGB format, for example, **0xFF1122FF**.</li>\n
     * <li>.value[1]?.f32: Size of the internal mark, in vp. This parameter is optional.</li>\n
     * <li>.value[2]?.f32: Stroke width of the internal mark,
     * in vp. This parameter is optional. The default value is **2**.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: Border color, in 0xARGB format, for example, **0xFF1122FF**.</li>\n
     * <li>.value[1].f32: Size of the internal mark, in vp.</li> \n
     * <li>.value[2].f32: Stroke width of the internal mark, in vp. The default value is **2**.</li> \n
     * </ul>
     *
     * @ingroup Checkbox
     */
    NODE_CHECKBOX_MARK,

    /**
     * @brief Shape of the **CheckBox** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: Component shape. The parameter type is {@link ArkUI_CheckboxShape}.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: Component shape. The parameter type is {@link ArkUI_CheckboxShape}.</li>
     * </ul>
     *
     * @ingroup Checkbox
     */
    NODE_CHECKBOX_SHAPE,

    /**
     * @brief Name of the **CheckBox** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.string: Component name.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.string: Component name.</li> \n
     * </ul>
     *
     * @ingroup Checkbox
     * @since 15
     */
    NODE_CHECKBOX_NAME,

    /**
     * @brief Name of the **CheckboxGroup** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.string: Component name.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.string: Component name.</li> \n
     * </ul>
     *
     * @ingroup Checkbox
     * @since 15
     */
    NODE_CHECKBOX_GROUP,

    /**
     * @brief Defines the ID of the <b><XComponent></b> component.
     * This attribute can be set and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: component ID.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: component ID.</li>
     * </ul>
     *
     * @ingroup XComponent
     * @since 12
     */
    NODE_XCOMPONENT_ID = MAX_NODE_SCOPE_NUM * ARKUI_NODE_XCOMPONENT,
    /**
     * @brief Specifies the type of the <b>XComponent</b> component. This attribute is read-only.
     * The type of the <b>XComponent</b> component must be explicitly set during creation
     * using{@link ARKUI_NODE_XCOMPONENT} or {@link ARKUI_NODE_XCOMPONENT_TEXTURE}, and cannot be modified afterward.
     * Attempting to change the type through {@link setAttribute} will cause rendering exceptions.
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: type {@link ArkUI_XComponentType}.</li>
     * </ul>
     *
     * @ingroup XComponent
     * @since 12
     */
    NODE_XCOMPONENT_TYPE,
    /**
     * @brief Size of the surface held by the **XComponent** component. This attribute can only be obtained
     * through APIs.
     * If you attempt to modify the size of the surface by using the {@link setAttribute} API, the setting
     * does not take effect.
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: Width, in px.</li>
     * <li>.value[1].u32: Height, in px.</li>
     * </ul>
     *
     * @ingroup XComponent
     * @since 12
     */
    NODE_XCOMPONENT_SURFACE_SIZE,
    /**
     * @brief Display area of the surface held by the **XComponent** component. This attribute can be set and
     * obtained through APIs. It applies to scenarios where a partial area within the **XComponent** component
     * needs to be specified for rendering, such as cropped video display and partial rendering in PiP mode.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: X-coordinate of the surface display area relative to the upper left corner of the
     * **XComponent** component, in px.</li>
     * <li>.value[1].i32: Y-coordinate of the surface display area relative to the upper left corner of the
     * **XComponent** component, in px.</li>
     * <li>.value[2].i32: Width of the surface display area, in px. The value must be a positive integer. The
     * setting does not take effect when 0 or a negative number is passed.</li>
     * <li>.value[3].i32: Height of the surface display area, in px. The value must be a positive integer. The
     * setting does not take effect when 0 or a negative number is passed.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: X-coordinate of the surface display area relative to the upper left corner of the
     * **XComponent** component, in px.</li>
     * <li>.value[1].i32: Y-coordinate of the surface display area relative to the upper left corner of the
     * **XComponent** component, in px.</li>
     * <li>.value[2].i32: Width of the surface display area, in px. The value must be a non-negative integer.</li>
     * <li>.value[3].i32: Height of the surface display area, in px.</li>
     * </ul>
     *
     * @ingroup XComponent
     * @since 18
     */
    NODE_XCOMPONENT_SURFACE_RECT,
    /**
     * @brief Whether to enable the image analyzer for the **XComponent** component. This attribute can be set
     * and obtained as required through APIs. When enabled, content recognition and analysis can be performed on
     * the image displayed in the component. It applies to scenarios such as real-time recognition in camera
     * preview and image content understanding.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable the image analyzer. `1` indicates enable the image analyzer, and `0`
     * indicates the opposite. The default value is `0`. Values other than 0 and 1 are treated as `0`.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the image analyzer is enabled. `1` indicates that the image analyzer is
     * supported, and `0` indicates the opposite.</li>
     * </ul>
     *
     * @ingroup XComponent
     * @since 18
     */
    NODE_XCOMPONENT_ENABLE_ANALYZER,

    /**
     * @brief Defines whether to display the lunar calendar in the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to display the lunar calendar in the date picker.
     * The default value is <b>false</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to display the lunar calendar in the date picker.</li>
     * </ul>
     *
     * @ingroup Datepicker
     */
    NODE_DATE_PICKER_LUNAR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_DATE_PICKER,
    /**
     * @brief Start date of the date picker. This attribute can be set, reset, and obtained as required through
     * APIs. The start date limits the valid range of date selection, and a selected date out of range is
     * automatically adjusted.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: date. The default value is <b>"1970-1-1"</b>. Format: <i>YYYY-MM-DD</i>, where <b>YYYY</b>
     * supports 1 or 4 digits, and <b>MM</b> and <b>DD</b> are 1-2 digit numbers.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: start date to set, in the format of <i>YYYY-MM-DD</i>.</li>
     * </ul>
     *
     * @ingroup Datepicker
     */
    NODE_DATE_PICKER_START,
    /**
     * @brief End date of the date picker. This attribute can be set, reset, and obtained as required through
     * APIs. The end date limits the valid range of date selection, and a selected date out of range is
     * automatically adjusted.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: date. The default value is <b>"2100-12-31"</b>. Format: <i>YYYY-MM-DD</i>, where <b>YYYY</b>
     * supports 1 or 4 digits, and <b>MM</b> and <b>DD</b> are 1-2 digit numbers.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: end date to set, in the format of <i>YYYY-MM-DD</i>.</li>
     * </ul>
     *
     * @ingroup Datepicker
     */
    NODE_DATE_PICKER_END,
    /**
     * @brief Date of the selected item in the date picker. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: date. The default value is <b>"2024-01-22"</b>. When not set, the default value is used.
     * Format: <i>YYYY-MM-DD</i>, where <b>YYYY</b> supports 1 or 4 digits, and <b>MM</b> and <b>DD</b> are
     * 1-2 digit numbers.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: selected date, in the format of <i>YYYY-MM-DD</i>.</li>
     * </ul>
     *
     * @ingroup Datepicker
     */
    NODE_DATE_PICKER_SELECTED,
    /**
     * @brief Text color, font size, and font weight for the top and bottom items in the date picker. This
     * attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>. When not set, the system default
     * style is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>.</li>
     * </ul>
     *
     * @ingroup Datepicker
     */
    NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE,
    /**
     * @brief Text color, font size, and font weight for all items except edge items and selected items in the
     * date picker. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>. When not set, the system default
     * style is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>.</li>
     * </ul>
     *
     * @ingroup Datepicker
     */
    NODE_DATE_PICKER_TEXT_STYLE,
    /**
     * @brief Text color, font size, and font weight of the selected item in the date picker. This attribute can
     * be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>. When not set, the system default
     * style is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>.</li>
     * </ul>
     *
     * @ingroup Datepicker
     */
    NODE_DATE_PICKER_SELECTED_TEXT_STYLE,
    /**
     * @brief Date column to be displayed. <b>DatePicker</b> displays different styles of date columns. This
     * attribute can be set, reset, and obtained as required through APIs.
     *
     * Use scenario: Select an appropriate date display mode based on application requirements. For example, use
     * the year/month/day mode when precise selection down to the day is required, and use the year/month mode
     * when only the month is required.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: type of the date column to be displayed. The parameter type is
     * {@link ArkUI_DatePickerMode}. Default value: the complete date columns (year, month, day).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: type of the date column to be displayed. The parameter type is
     * {@link ArkUI_DatePickerMode}.</li>
     * </ul>
     *
     * @ingroup Datepicker
     * @since 18
     */
    NODE_DATE_PICKER_MODE = 13007,
    /**
     * @brief Whether to enable haptic feedback. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable haptic feedback. The value <b>1</b> indicates to enable, and
     * <b>0</b> indicates the opposite. After enabled, whether haptic feedback exists depends on the hardware
     * support of the system.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether haptic feedback is enabled. The value <b>1</b> indicates haptic feedback is
     * enabled, and <b>0</b> indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Datepicker
     * @since 18
     */
    NODE_DATE_PICKER_ENABLE_HAPTIC_FEEDBACK = 13008,
    /**
     * @brief Whether to enable looping for the date picker. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * Use scenario: Looping is suitable for scenarios with limited options where a quick selection experience
     * is desired (such as month selection); non-looping is suitable for scenarios where options have clear
     * boundaries and the user selection range needs to be restricted (such as date selection to avoid confusion
     * across years).
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable looping. <b>1</b> to enable; <b>0</b> otherwise. The default value
     * is <b>1</b>. If an invalid value is provided, the default value is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether looping is enabled. The value <b>1</b> means that the looping is enabled, and
     * <b>0</b> means the opposite.<br>
     * Note: When looping is enabled, the year increments or decrements in linkage with the month's cycle, and
     * the month increments or decrements in linkage with the day's cycle.<br>
     * When looping is disabled, scrolling beyond the bounds of the year, month, or day columns is prevented,
     * and cross-column value synchronization (between year, month, and day) is also disabled.</li>
     * </ul>
     *
     * @ingroup Datepicker
     * @since 20
     */
     NODE_DATE_PICKER_CAN_LOOP = 13009,
    /**
     * @brief Defines the time of the selected item. in the timer picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: time. The default value is the current system time.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: time.</li>
     * </ul>
     *
     * @ingroup Timepicker
     */
    NODE_TIME_PICKER_SELECTED = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TIME_PICKER,
    /**
     * @brief Whether the display time of the time picker is in 24-hour format. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the display time is in 24-hour format. The default value is <b>0</b>. <b>1</b>:
     * The display time is in 24-hour format. <b>0</b>: The display time is in 12-hour format.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the display time is in 24-hour format. The value <b>1</b> indicates that the
     * time is displayed in the 24-hour format (corresponding to <b>true</b>), and <b>0</b> indicates that the
     * time is displayed in the 12-hour format (corresponding to <b>false</b>).</li>
     * </ul>
     *
     * @ingroup Timepicker
     */
    NODE_TIME_PICKER_USE_MILITARY_TIME,
    /**
     * @brief Text style for edge items (the second item above or below the selected item). This attribute can
     * be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>. When not set, the system default
     * style is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>.</li>
     * </ul>
     *
     * @ingroup Timepicker
     */
    NODE_TIME_PICKER_DISAPPEAR_TEXT_STYLE,
    /**
     * @brief Text color, font size, and font weight for all items except edge items and selected items in the
     * time picker. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>. When not set, the system default
     * style is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>.</li>
     * </ul>
     *
     * @ingroup Timepicker
     */
    NODE_TIME_PICKER_TEXT_STYLE,
    /**
     * @brief Text color, font size, and font weight of the selected item in the time picker. This attribute
     * can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>. When not set, the system default
     * style is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>.</li>
     * </ul>
     *
     * @ingroup Timepicker
     */
    NODE_TIME_PICKER_SELECTED_TEXT_STYLE,
    /**
     * @brief Start time of the timer picker. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: time. The default value is <b>"0:0"</b>. When set, only hours and minutes are supported,
     * separated by <b>:</b> or <b>-</b> (for example, 12:59 or 12-59).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: start time to set. Format: hour:minute:second (for example, 0:0:0).</li>
     * </ul>
     *
     * @ingroup Timepicker
     * @since 18
     */
    NODE_TIME_PICKER_START = 14005,
    /**
     * @brief End time of the timer picker. This attribute can be set, reset, and obtained as required through
     * APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: time. The default value is <b>"23:59"</b>. When set, only hours and minutes are supported,
     * separated by <b>:</b> or <b>-</b> (for example, 23:59 or 23-59).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: end time to set. Format: hour:minute:second (for example, 23:59:0).</li>
     * </ul>
     *
     * @ingroup Timepicker
     * @since 18
     */
    NODE_TIME_PICKER_END = 14006,
    /**
     * @brief Whether the AM/PM indicator automatically switches based on the hour in 12-hour format. This
     * attribute can be set, reset, and obtained as required through APIs. In the 24-hour format, this attribute
     * does not take effect.
     *
     * Use scenario: It is suitable for scenarios that require a friendly 12-hour format selection experience.
     * For example, when the user scrolls to select the hour, the AM/PM indicator changes automatically without
     * manual switching.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the AM/PM indicator automatically switches based on the hour in 12-hour
     * format. The default value is <b>0</b>. The value <b>1</b> means that the AM/PM indicator automatically
     * switches based on the hour in 12-hour format, and <b>0</b> means the opposite.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the AM/PM indicator automatically switches based on the hour in 12-hour
     * format. The value <b>1</b> means that the AM/PM indicator automatically switches (corresponding to
     * <b>true</b>), and the value <b>0</b> that the AM/PM indicator does not automatically switch
     * (corresponding to <b>false</b>).</li>
     * </ul>
     *
     * @ingroup Timepicker
     * @since 18
     */
    NODE_TIME_PICKER_ENABLE_CASCADE = 14007,

    /**
     * @brief Defines the data selection range of the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: type of the text picker {@link ArkUI_TextPickerRangeType}.
     * The default value is <b>ARKUI_TEXTPICKER_RANGETYPE_SINGLE</b>. </li>
     * <li>.string: string input, whose format varies by picker type.</li>
     * <li>1: single-column picker. The input format is a group of strings separated by semicolons (;).</li>
     * <li>2: multi-column picker. Multiple pairs of plain text strings are supported. The pairs are separated by
     * semicolons (;), and strings within each pair are separated by commas (,).</li>
     * <li>.object: Object input, whose format varies by picker type.</li>
     * <li>1: single-column picker with image support.
     * The input structure is {@link ARKUI_TextPickerRangeContent}.</li>
     * <li>2: multi-column interconnected picker.
     * The input structure is {@link ARKUI_TextPickerCascadeRangeContent}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: type of the text picker {@link ArkUI_TextPickerRangeType}.</li>
     * <li>.string: string output, whose format varies by picker type.</li>
     * <li>1: single-column picker. The output format is a group of strings separated by semicolons (;).</li>
     * <li>2: multi-column picker. Multiple pairs of plain text strings are supported. The pairs are separated by
     * semicolons (;), and strings within each pair are separated by commas (,).</li>
     * <li>.string: Object output, whose format varies by picker type.</li>
     * <li>1: single-column picker with image support.
     * The output structure is {@link ARKUI_TextPickerRangeContent}.</li>
     * <li>2: multi-column interconnected picker.
     * The output structure is {@link ARKUI_TextPickerCascadeRangeContent}.</li>
     * </ul>
     *
     * @ingroup Textpicker
     */
    NODE_TEXT_PICKER_OPTION_RANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_PICKER,
    /**
     * @brief Index of the default selected item in the data selection range of the text picker. This attribute
     * can be set, reset, and obtained as required through APIs. This attribute can be used only after the option
     * list is set through {@link NODE_TEXT_PICKER_OPTION_RANGE}.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: index of the default selected item in the picker option array. The value range is
     * [0, length - 1]. An exception is thrown if the value is out of range. For a multi-column picker, if
     * multiple index values exist, add them one by one. Default value: <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: index of the selected item in the picker option array. If multiple indexes exist, add
     * them one by one.</li>
     * </ul>
     *
     * @ingroup Textpicker
     */
    NODE_TEXT_PICKER_OPTION_SELECTED,
    /**
     * @brief Value of the default selected item in the text picker. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: value of the selected item. If multiple values exist, add them one by one, separated by
     * semicolons (;). Default value: empty string. When not set, use the default value.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: value of the selected item. If there are multiple values, add them one by one and separate
     * them with semicolons (;).</li>
     * </ul>
     *
     * @ingroup Textpicker
     */
    NODE_TEXT_PICKER_OPTION_VALUE,
    /**
     * @brief Text color, font size, and font weight for the top and bottom items in the text picker. This
     * attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>. When not set, the system default
     * style is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>.</li>
     * </ul>
     *
     * @ingroup Textpicker
     */
    NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE,
    /**
     * @brief Text color, font size, and font weight for all items except the top, bottom, and selected items in
     * the text picker. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>. When not set, the system default
     * style is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>.</li>
     * </ul>
     *
     * @ingroup Textpicker
     */
    NODE_TEXT_PICKER_TEXT_STYLE,
    /**
     * @brief Text color, font size, and font weight of the selected item in the text picker. This attribute can
     * be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>. When not set, the system default
     * style is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: five parameters of the string type, separated by semicolons (;):<br>
     * Parameter 1: text color, in #ARGB format.<br>
     * Parameter 2: font size, in fp. The value is a number.<br>
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium",
     * "regular").<br>
     * Parameter 4: fonts, separated by commas (,).<br>
     * Parameter 5: font style. Available options are ("normal", "italic").<br>
     * Example: <b>"#ff182431;14;normal;Arial,HarmonyOS Sans;normal"</b>.</li>
     * </ul>
     *
     * @ingroup Textpicker
     */
    NODE_TEXT_PICKER_SELECTED_TEXT_STYLE,
    /**
     * @brief Index of the default selected item in the data selection range of the text picker. This attribute
     * can be set, reset, and obtained as required through APIs. This attribute can be used only after the option
     * list is set through {@link NODE_TEXT_PICKER_OPTION_RANGE}. After the option list is set, if the index array
     * is not set through this attribute, the first item of each column is selected by default.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0...].i32: array of the indexes of the default selected items in the picker option array. When
     * used for a multi-column picker, it indicates the index of the default selected item in each column.
     * Default value: <b>0</b> for each column. Value range: the index of each column is in [0, length of the
     * corresponding column - 1]. An exception is thrown when the value is out of range.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0...].i32: array of the indexes of the currently selected items. When used for a multi-column
     * picker, it indicates the index of the selected item in each column.</li>
     * </ul>
     *
     * @ingroup Textpicker
     */
    NODE_TEXT_PICKER_SELECTED_INDEX,
    /**
     * @brief Whether to enable looping for the picker. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * Use scenario: Looping is suitable for scenarios with limited options where a quick selection experience
     * is desired (such as province selection). Non-looping is suitable for scenarios where options have clear
     * boundaries and the user selection range needs to be restricted (such as quantity selection to avoid
     * misoperation).
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable looping. <b>1</b> to enable; <b>0</b> otherwise. Default value:
     * <b>1</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether looping is enabled. The value <b>1</b> means that the looping is enabled, and
     * <b>0</b> means the opposite.</li>
     * </ul>
     *
     * @ingroup Textpicker
     */
    NODE_TEXT_PICKER_CAN_LOOP,
    /**
     * @brief Height of each item in the text picker. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: height of the currently set item, in vp. Default value: <b>40.0vp</b>. When not set,
     * the default value is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: height of the currently set item, in vp.</li>
     * </ul>
     *
     * @ingroup Textpicker
     */
    NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT,
    /**
     * @brief Whether to enable haptic feedback. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable haptic feedback. The value <b>1</b> indicates to enable, and
     * <b>0</b> indicates the opposite. When enabled, whether haptic feedback exists depends on the hardware
     * support of the system.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether haptic feedback is enabled. The value <b>1</b> indicates haptic feedback is
     * enabled, and <b>0</b> indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Textpicker
     * @since 18
     */
    NODE_TEXT_PICKER_ENABLE_HAPTIC_FEEDBACK = 15010,
    /**
     * @brief Background color and border radius of the selected item. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format. <b>A</b> indicates the opacity (0x00 fully
     * transparent to 0xFF fully opaque), and <b>RGB</b> indicates the color value (0x000000 to 0xFFFFFF). Each
     * byte ranges from 0x00 to 0xFF. For example, <b>0xFF1122FF</b> indicates a fully opaque blue.</li>
     * <li>.value[1].f32: radius of the upper left corner, in vp.</li>
     * <li>.value[2].f32: radius of the upper right corner, in vp.</li>
     * <li>.value[3].f32: radius of the lower left corner, in vp.</li>
     * <li>.value[4].f32: radius of the lower right corner, in vp.<br>
     * Default background color: 0x0C182431; default corner radius: 24.0.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>
     * <li>.value[1].f32: radius of the upper left corner, in vp.</li>
     * <li>.value[2].f32: radius of the upper right corner, in vp.</li>
     * <li>.value[3].f32: radius of the lower left corner, in vp.</li>
     * <li>.value[4].f32: radius of the lower right corner, in vp.</li>
     * </ul>
     *
     * @ingroup Textpicker
     * @since 20
     */
    NODE_TEXT_PICKER_SELECTED_BACKGROUND_STYLE = 15011,
    /**
     * @brief Defines the style of the background in the selected state of the calendar picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: style of the background in the selected state of the calendar picker.
     * The value range is [0, +∞). If the value is <b>0</b>, the background is a rectangle with square corners.
     If the value is in the 0–16 range, the background is a rectangle with rounded corners. If the value is equal to
     * or greater than 16, the background is a circle.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: style of the background in the selected state of the calendar picker.
     * The value range is [0, +∞). If the value is <b>0</b>, the background is a rectangle with square corners.
     * If the value is in the 0–16 range, the background is a rectangle with rounded corners.
     * If the value is equal to or greater than 16, the background is a circle.</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     */
    NODE_CALENDAR_PICKER_HINT_RADIUS = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CALENDAR_PICKER,
    /**
     * @brief Date of the selected item in the calendar picker. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: selected year. Default value: the current system year. The default value is used when
     * an invalid value is passed in.</li>
     * <li>.value[1].u32: selected month. Default value: the current system month. The default value is used
     * when an invalid value is passed in.</li>
     * <li>.value[2].u32: selected day. Default value: the current system date. The default value is used when
     * an invalid value is passed in.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: selected year.</li>
     * <li>.value[1].u32: selected month.</li>
     * <li>.value[2].u32: selected day.</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     */
    NODE_CALENDAR_PICKER_SELECTED_DATE,
    /**
     * @brief How the calendar picker is aligned with the entry component. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: alignment mode. The parameter type is {@link ArkUI_CalendarAlignment}. It is used to
     * set the alignment position of the calendar picker relative to the entry component.</li>
     * <li>.value[1]?.f32: offset of the picker relative to the entry component along the x-axis after alignment
     * based on the specified alignment mode, in vp. Default value: <b>0</b>.</li>
     * <li>.value[2]?.f32: offset of the picker relative to the entry component along the y-axis after alignment
     * based on the specified alignment mode, in vp. Default value: <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: alignment mode. The parameter type is {@link ArkUI_CalendarAlignment}.</li>
     * <li>.value[1].f32: offset of the picker relative to the entry component along the x-axis after alignment
     * based on the specified alignment mode, in vp.</li>
     * <li>.value[2].f32: offset of the picker relative to the entry component along the y-axis after alignment
     * based on the specified alignment mode, in vp.</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     */
    NODE_CALENDAR_PICKER_EDGE_ALIGNMENT,
    /**
     * @brief Text color, font size, and font weight in the entry area of the calendar picker.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0]?.u32: text color of the entry area. When not set or after <b>resetAttribute</b> is
     * executed, the value resolved by the system theme <b>calendar_picker_entry_font_color</b> is used (the
     * specific color value varies with the theme and can be obtained through <b>getAttribute</b>).</li>
     * <li>.value[1]?.f32: font size of the entry area, in fp. When not set or after <b>resetAttribute</b> is
     * executed, the value resolved by the system theme <b>calendar_picker_entry_font_size</b> is used (the
     * specific value varies with the theme and can be obtained through <b>getAttribute</b>).</li>
     * <li>.value[2]?.i32: font weight of the entry area. The parameter type is {@link ArkUI_FontWeight}. When
     * not set or after <b>resetAttribute</b> is executed, the default value is
     * <b>ARKUI_FONT_WEIGHT_NORMAL</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: text color of the entry area.</li>
     * <li>.value[1].f32: font size of the entry area, in fp.</li>
     * <li>.value[2].i32: font weight of the entry area. The parameter type is {@link ArkUI_FontWeight}.</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     */
    NODE_CALENDAR_PICKER_TEXT_STYLE,
    /**
     * @brief Start date of the calendar picker. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: date. The value format is "YYYY-MM-DD", where <b>YYYY</b> supports 1 or 4 digits, and
     * <b>MM</b> and <b>DD</b> are 1-2 digit numbers, for example, "1970-1-1" or "2024-05-20". Default value:
     * <b>1970-1-1</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: start date of the calendar picker to set, in the format of "YYYY-MM-DD".</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     * @since 18
     */
    NODE_CALENDAR_PICKER_START = 16004,
    /**
     * @brief End date of the calendar picker. This attribute can be set, reset, and obtained as required through
     * APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: date. The value format is "YYYY-MM-DD", where <b>YYYY</b> supports 1 or 4 digits, and
     * <b>MM</b> and <b>DD</b> are 1-2 digit numbers, for example, "2100-12-31" or "2025-1-25". Default value:
     * <b>"2100-12-31"</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: end date of the calendar picker to set, in the format of "YYYY-MM-DD".</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     * @since 18
     */
    NODE_CALENDAR_PICKER_END = 16005,
    /**
     * @brief Defines the color of the slider. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: color of the slider, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: color of the slider, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_BLOCK_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SLIDER,

    /**
     * @brief Background color of the slider track. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: Background color, in 0xARGB format, for example, **0xFF1122FF**.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: Background color, in 0xARGB format, for example, **0xFF1122FF**.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_TRACK_COLOR,

    /**
     * @brief Color of the selected part of the slider track. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: Color of the selected part of the slider track, in 0xARGB format, for example,
     * **0xFF1122FF**.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: Color of the selected part of the slider track, in 0xARGB format, for example,
     * **0xFF1122FF**.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_SELECTED_COLOR,

    /**
     * @brief Whether to display the step scale value. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: Whether to display the step scale value. The value **1** means to display the step scale
     * value,
     * and **0** means the opposite. The default value is **0**.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: Whether the step scale value is displayed. The value **1** means that the step scale value is
     * displayed, and **0** means the opposite. The default value is **0**.</li> \n
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_SHOW_STEPS,

    /**
     * @brief Shape of the slider thumb. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: Shape. The parameter type is {@link ArkUI_SliderBlockStyle}.</li> \n
     * <li>.string?: This parameter is optional,
     * and its value depends on the shape.<br>**ARKUI_SLIDER_BLOCK_STYLE_IMAGE**:
     * image resource of the slider thumb. Example: /pages/common/icon.png.<br>**ARKUI_SLIDER_BLOCK_STYLE_SHAPE**:
     * custom
     * shape of the slider thumb. In this case, the width and height values in the defined shape do not represent the
     * actual size of the thumb; they are scaled proportionally to ensure the thumb displays correctly.<br>There are
     * four
     * types. For the path type, **.string** indicates the command string for drawing the path.</li> \n
     * <li>.value[1].i32: Shape type. The parameter type is {@link ArkUI_ShapeType}. The value is
     * **ARKUI_SHAPE_TYPE_RECTANGLE** for the rectangle type, **ARKUI_SHAPE_TYPE_CIRCLE** for the circle type,
     * **ARKUI_SHAPE_TYPE_ELLIPSE** for the ellipse type, and **ARKUI_SHAPE_TYPE_PATH** for the path type.</li> \n
     * <li>.value[2].f32: Width of the rectangle, circle, ellipse, or path type.</li> \n
     * <li>.value[3].f32: Height of the rectangle, circle, ellipse, or path type.</li> \n
     * <li>.value[4].f32: Width of the rounded corner of the rectangle type.</li> \n
     * <li>.value[5].f32: Height of the rounded corner of the rectangle type.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: Shape. The parameter type is {@link ArkUI_SliderBlockStyle}.</li> \n
     * <li>.string?: This parameter is optional,
     * and its value depends on the shape.<br>**ARKUI_SLIDER_BLOCK_STYLE_IMAGE**:
     * image resource of the slider thumb. Example: /pages/common/icon.png.<br>**ARKUI_SLIDER_BLOCK_STYLE_SHAPE**:
     * custom
     * shape of the slider thumb.<br>There are four types. For the path type,
     * **.string** indicates the command string for
     * drawing the path.</li> \n
     * <li>.value[1].i32: Shape type. The parameter type is {@link ArkUI_ShapeType}. The value is
     * **ARKUI_SHAPE_TYPE_RECTANGLE** for the rectangle type, **ARKUI_SHAPE_TYPE_CIRCLE** for the circle type,
     * **ARKUI_SHAPE_TYPE_ELLIPSE** for the ellipse type, and **ARKUI_SHAPE_TYPE_PATH** for the path type.</li> \n
     * <li>.value[2].f32: Width of the rectangle, circle, ellipse, or path type.</li> \n
     * <li>.value[3].f32: Height of the rectangle, circle, ellipse, or path type.</li> \n
     * <li>.value[4].f32: Width of the rounded corner of the rectangle type.</li> \n
     * <li>.value[5].f32: Height of the rounded corner of the rectangle type.</li> \n
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_BLOCK_STYLE,

    /**
     * @brief Current value of the slider. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: Current value.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: Current value.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_VALUE,

    /**
     * @brief Minimum value of the slider. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: Minimum value.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: Minimum value.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_MIN_VALUE,

    /**
     * @brief Maximum value of the slider. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: Maximum value.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: Maximum value.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_MAX_VALUE,

    /**
     * @brief Step of the slider. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: Step. The value range is [0.01, 100].</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: Step. The value range is [0.01, 100].</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_STEP,

    /**
     * @brief Slider direction. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: Slider direction. The parameter type is {@link ArkUI_SliderDirection}.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: Slider direction. The parameter type is {@link ArkUI_SliderDirection}.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_DIRECTION,

    /**
     * @brief Whether the slider values are reversed. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: Whether the slider values are reversed. The value **1** means that the slider values are
     * reversed, and **0** means the opposite.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: Whether the slider values are reversed. The value **1** means that the slider values are
     * reversed, and **0** means the opposite.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_REVERSE,

    /**
     * @brief Style of the slider thumb and track. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: Slider style. The parameter type is {@link ArkUI_SliderStyle}.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: Slider style. The parameter type is {@link ArkUI_SliderStyle}.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_STYLE,

    /**
     * @brief Track thickness of the slider.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: Track thickness of the slider, in vp. The default value is 4.0 vp when **NODE_SLIDER_STYLE**
     * is set to **ARKUI_SLIDER_STYLE_OUT_SET** and 20.0 vp when **NODE_SLIDER_STYLE** is set to
     * **ARKUI_SLIDER_STYLE_IN_SET**.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: Track thickness of the slider, in vp.</li> \n
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_TRACK_THICKNESS,

    /**
     * @brief Whether to enable haptic feedback. This attribute can be set, reset, and obtained as required through
     * APIs.
     * To enable haptic feedback, you must add **"name": "ohos.permission.VIBRATE"** under **requestPermissions** in the
     * **module.json5** file of the project.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: Whether to enable haptic feedback. **true** to enable; **false** otherwise.
     * The default value is
     * **true**.</li>\n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: Whether haptic feedback is enabled.</li>\n
     * </ul>
     *
     * @ingroup Slider
     * @since 18
     */
    NODE_SLIDER_ENABLE_HAPTIC_FEEDBACK = 17013,

    /**
     * @brief Custom prefix component for the start edge of the slider.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.object: The parameter type is {@link ArkUI_NodeHandle}. The prefix component is typically placed on the left
     * in LTR layouts.</li>
     * </ul>
     *
     * @ingroup Slider
     * @since 20
     */
    NODE_SLIDER_PREFIX,

    /**
     * @brief Custom suffix component for the end edge of the slider.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.object: The parameter type is {@link ArkUI_NodeHandle}. The suffix component is typically placed on the
     * right
     * in LTR layouts.</li>
     * </ul>
     *
     * @ingroup Slider
     * @since 20
     */
    NODE_SLIDER_SUFFIX,

    /**
     * @brief Linear gradient color of the slider thumb. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.object: The parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of which
     * consists of a color and its stop position. Invalid colors are automatically skipped.<br>- **colors**: colors of
     * the color stops.<br>- **stops**: stop positions of the color stops.<br>- **size**: number of colors.</li> \n \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.object: The parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of which
     * consists of a color and its stop position. Invalid colors are automatically skipped.<br>- **colors**: colors of
     * the color stops.<br>- **stops**: stop positions of the color stops.<br>- **size**: number of colors.</li> \n \n
     * </ul>
     *
     * @ingroup Slider
     * @since 21
     */
    NODE_SLIDER_BLOCK_LINEAR_GRADIENT_COLOR,

    /**
     * @brief Linear gradient color of the slider track. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.object: The parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of which
     * consists of a color and its stop position. Invalid colors are automatically skipped.<br>- **colors**: colors of
     * the color stops.<br>- **stops**: stop positions of the color stops.<br>- **size**: number of colors.</li> \n \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.object: The parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of which
     * consists of a color and its stop position. Invalid colors are automatically skipped.<br>- **colors**: colors of
     * the color stops.<br>- **stops**: stop positions of the color stops.<br>- **size**: number of colors.</li> \n \n
     * </ul>
     *
     * @ingroup Slider
     * @since 21
     */
    NODE_SLIDER_TRACK_LINEAR_GRADIENT_COLOR,

    /**
     * @brief Linear gradient color of the selected part of the slider track. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.object: The parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of which
     * consists of a color and its stop position. Invalid colors are automatically skipped.<br>- **colors**: colors of
     * the color stops.<br>- **stops**: stop positions of the color stops.<br>- **size**: number of colors.</li> \n \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.object: The parameter type is {@link ArkUI_ColorStop}. It specifies an array of color stops, each of which
     * consists of a color and its stop position. Invalid colors are automatically skipped.<br>- **colors**: colors of
     * the color stops.<br>- **stops**: stop positions of the color stops.<br>- **size**: number of colors.</li> \n \n
     * </ul>
     *
     * @ingroup Slider
     * @since 21
     */
    NODE_SLIDER_SELECTED_LINEAR_GRADIENT_COLOR,

    /**
     * @brief Set the selection status of an option button. Attribute setting,
     * attribute resetting, and attribute obtaining are supported.
     * **Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:**\n
     * <ul>
     * <li>.value[0].i32: check status of an option button. The default value is false.</li>
     * </ul>
     * **Attribute obtaining method return value {@Link ArkUI_AttributeItem} format:**\n
     * <ul>
     * <li>.value[0].i32: selection status of an option button.</li>
     * </ul>
     *
     * @ingroup Radio
     */
    NODE_RADIO_CHECKED = MAX_NODE_SCOPE_NUM * ARKUI_NODE_RADIO,
    /**
     * @brief Style of the radio button in selected or deselected state. This attribute can be set, reset, and obtained
     * as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0]?.u32: Color of the background when the radio button is selected, in 0xARGB format. The default
     * value
     * is **0xFF007DFF**.</li> \n
     * <li>.value[1]?.u32: Color of the border when the radio button is deselected, in 0xARGB format. The default value
     * is **0xFF182431**.</li> \n
     * <li>.value[2]?.u32: Color of the indicator when the radio button is selected, in 0xARGB format. The default value
     * is **0xFFFFFFFF**.</li> \n
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: Color of the background when the radio button is selected, in 0xARGB format. The default value
     * is **0xFF007DFF**.</li> \n
     * <li>.value[1].u32: Color of the border when the radio button is deselected, in 0xARGB format. The default value
     * is **0xFF182431**.</li> \n
     * <li>.value[2].u32: Color of the indicator when the radio button is selected, in 0xARGB format. The default value
     * is **0xFFFFFFFF**.</li> \n
     * </ul>
     *
     * @ingroup Radio
     */
    NODE_RADIO_STYLE,
    /**
     * @brief Current value of the radio button. This attribute can be set, reset, and obtained as required through
     * APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.string: Current value of the radio button.</li>\n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.string: Current value of the radio button.</li>\n
     * </ul>
     *
     * @ingroup Radio
     */
    NODE_RADIO_VALUE,
    /**
     * @brief Name of the group to which the radio button belongs. Only one radio button in a given group can be
     * selected at a time. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.string: Name of the group to which the radio button belongs.</li>\n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.string: Name of the group to which the radio button belongs.</li>\n
     * </ul>
     *
     * @ingroup Radio
     */
    NODE_RADIO_GROUP,

    /**
     * @brief Defines the image frames for the image animator. Dynamic updates are not supported.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.size: number of images.</li>
     * <li>.object: array of images. The array element type is {@link ArkUI_ImageAnimatorFrameInfo}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.size: number of images.</li>
     * <li>.object: array of images. The array element type is {@link ArkUI_ImageAnimatorFrameInfo}.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_IMAGES = ARKUI_NODE_IMAGE_ANIMATOR * MAX_NODE_SCOPE_NUM,
    /**
     * @brief Playback status of the frame-by-frame animation. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: playback status of the frame-by-frame animation. The parameter type is
     * {@link ArkUI_AnimationStatus}. The default state is initial.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: playback status of the frame-by-frame animation. The parameter type is
     * {@link ArkUI_AnimationStatus}.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_STATE = 19001,
    /**
     * @brief Playback duration of the frame-by-frame animation. This attribute does not take effect
     * when a separate duration is set for any of the image frames. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: playback duration, in milliseconds. The default value is <b>1000</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: playback duration, in milliseconds. The default value is <b>1000</b>.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_DURATION = 19002,
    /**
     * @brief Playback direction of the frame-by-frame animation. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: playback direction. The value <b>0</b> indicates that images are played from
     * the first one to the last one, and <b>1</b> indicates that images are played from the last one to
     * the first one. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: playback direction. The value <b>0</b> indicates that images are played from
     * the first one to the last one, and <b>1</b> indicates that images are played from the last one to
     * the first one.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_REVERSE = 19003,
    /**
     * @brief Whether the image size is fixed at the component size. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the image size is fixed at the component size. The value <b>1</b>
     * indicates that the image size is fixed at the component size. The value <b>0</b> indicates that
     * the <b>width</b>, <b>height</b>, <b>top</b>, and <b>left</b> attributes of each image must be set
     * separately. The default value is <b>1</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the image size is fixed at the component size. The value <b>1</b>
     * indicates that the image size is fixed at the component size. The value <b>0</b> indicates that
     * the <b>width</b>, <b>height</b>, <b>top</b>, and <b>left</b> attributes of each image must be set
     * separately.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_FIXED_SIZE = 19004,
    /**
     * @brief Status before and after execution of the frame-by-frame animation in the current playback
     * direction. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: status before and after execution of the frame-by-frame animation in the
     * current playback direction. The parameter type is {@link ArkUI_AnimationFillMode}. The default
     * value is <b>ARKUI_ANIMATION_FILL_MODE_FORWARDS</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: status before and after execution of the frame-by-frame animation in the
     * current playback direction. The parameter type is {@link ArkUI_AnimationFillMode}.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_FILL_MODE = 19005,
    /**
     * @brief Number of times that the frame-by-frame animation is played. This attribute can be set,
     * reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: number of times that the animation is played.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: number of times that the animation is played.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_ITERATION = 19006,
    /**
     * @brief Defines the interpolation effect of the frame images, which mitigates aliasing during image scaling.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: interpolation effect of the frame images. The parameter type is
     * {@link ArkUI_ImageInterpolation}. The default value is <b>ARKUI_IMAGE_INTERPOLATION_LOW</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: interpolation effect of the frame images. The parameter type is
     * {@link ArkUI_ImageInterpolation}.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     * @since 26.0.1
     */
    NODE_IMAGE_ANIMATOR_INTERPOLATION = 19007,

    /**
     * @brief Defines the name of the checkboxgroup.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.string: component name.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.string: component name.</li> \n
     * </ul>
     *
     * @ingroup CheckboxGroup
     * @since 15
     */
    NODE_CHECKBOX_GROUP_NAME  = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CHECKBOX_GROUP,

    /**
     * @brief Whether to select all check boxes in the **CheckBoxGroup** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: Whether to select all check boxes in the **CheckBoxGroup** component. The value **1** means to
     * select all check boxes, and **0** means the opposite.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: Whether all check boxes are selected. The value **1** means that all check boxes are selected,
     * and **0** means the opposite.</li> \n
     * </ul>
     *
     * @ingroup CheckboxGroup
     * @since 15
     */
    NODE_CHECKBOX_GROUP_SELECT_ALL,

    /**
     * @brief Color for the selected state of the **CheckBoxGroup** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: Color of the selected state, in 0xARGB format, for example, **0xFF1122FF**.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: Color for the selected state of the **CheckBoxGroup** component, in 0xARGB format, for
     * example,
     * **0xFF1122FF**.</li>
     * </ul>
     *
     * @ingroup CheckboxGroup
     * @since 15
     */
    NODE_CHECKBOX_GROUP_SELECTED_COLOR,
    /**
     * @brief Border color for the unselected state of the **CheckBoxGroup** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: Border color, in 0xARGB format, for example, **0xFF1122FF**.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: Border color, in 0xARGB format, for example, **0xFF1122FF**.</li>
     * </ul>
     *
     * @ingroup CheckboxGroup
     * @since 15
     */
    NODE_CHECKBOX_GROUP_UNSELECTED_COLOR,

    /**
     * @brief Internal mark style of the **CheckBoxGroup** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: Border color, in 0xARGB format, for example, **0xFF1122FF**.</li>\n
     * <li>.value[1]?.f32: Size of the internal mark, in vp. This parameter is optional.</li>\n
     * <li>.value[2]?.f32: Stroke width of the internal mark,
     * in vp. This parameter is optional. The default value is **2**.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: Border color, in 0xARGB format, for example, **0xFF1122FF**.</li>\n
     * <li>.value[1]?.f32: Size of the internal mark, in vp. This parameter is optional.</li> \n
     * <li>.value[2]?.f32: Stroke width of the internal mark,
     * in vp. This parameter is optional. The default value is **2**.</li> \n
     * </ul>
     *
     * @ingroup CheckboxGroup
     * @since 15
     */
    NODE_CHECKBOX_GROUP_MARK,

    /**
     * @brief Shape of the **CheckBoxGroup** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: Component shape. The parameter type is {@link ArkUI_CheckboxShape}.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: Component shape. The parameter type is {@link ArkUI_CheckboxShape}.</li>
     * </ul>
     *
     * @ingroup CheckboxGroup
     * @since 15
     */
    NODE_CHECKBOX_GROUP_SHAPE,

    /**
     * @brief Type of the **Enter** key of the **TextEditor** component. This attribute can be set, reset, and obtained
     * as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Type of the **Enter** key.
     * The parameter type is {@link ArkUI_EnterKeyType}. The default value is **ARKUI_ENTER_KEY_TYPE_NEW_LINE**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Type of the **Enter** key. The parameter type is {@link ArkUI_EnterKeyType}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ENTER_KEY_TYPE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_EDITOR,

    /**
     * @brief Caret color of the **TextEditor** component. This attribute can be set, reset, and obtained as required
     * through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: Caret color, in 0xARGB format, for example, **0xFFFF0000** indicates red. The color follows
     * the system theme color by default.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: Caret color, in 0xARGB format, for example, **0xFFFF0000** indicates red. The color follows
     * the system theme color by default.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_CARET_COLOR,

    /**
     * @brief Scroll bar color of the **TextEditor** component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.data[0].u32: Scroll bar color, in 0xARGB format, for example, **0xFFFF0000** indicates red. The color
     * follows the system theme color by default.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.data[0].u32: Scroll bar color, in 0xARGB format, for example, **0xFFFF0000** indicates red. The color
     * follows the system theme color by default.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_SCROLL_BAR_COLOR,

    /**
     * @brief Scroll bar state of the **TextEditor** component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Scroll bar state. The parameter type is {@link ArkUI_BarState}. The default value is
     * **ARKUI_BAR_STATE_AUTO**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Scroll bar state. The parameter type is {@link ArkUI_BarState}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_BAR_STATE,

    /**
     * @brief Whether to enable text entity recognition for the **TextEditor** component. When enabled, entities such
     * as phone numbers, email addresses, and URLs in the text are automatically recognized and marked as interactive
     * content. Used together with the **NODE_TEXT_EDITOR_DATA_DETECTOR_CONFIG** attribute, the recognition types and
     * interaction behavior can be customized. This attribute can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable text entity recognition. The value **1** indicates to enable text entity
     * recognition, and **0** indicates the opposite. The default value is **0**. It is recommended to set this
     * attribute in scenarios where entity information in the text needs to be automatically recognized and
     * highlighted.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether text entity recognition is enabled. **1** indicates enabled, and **0** indicates
     * disabled.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ENABLE_DATA_DETECTOR,

    /**
     * @brief Text entity recognition configuration of the **TextEditor** component. When set, the recognition types
     * and entity display styles can be configured, and whether to enable the long-press preview feature can be
     * selected. This attribute is used together with the **NODE_TEXT_EDITOR_ENABLE_DATA_DETECTOR** attribute. This
     * attribute can be set and reset as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Text entity detection configuration. After it is set, you can specify the text entity types to
     * be recognized (such as phone numbers, email addresses, and URLs) and the interaction behavior after
     * recognition. This parameter is passed only after the text entity recognition feature is enabled
     * (**NODE_TEXT_EDITOR_ENABLE_DATA_DETECTOR** is set to **1**) to customize the recognition types. When not
     * passed, the system default recognition configuration is used. The parameter type is
     * {@link ArkUI_TextDataDetectorConfig}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_DATA_DETECTOR_CONFIG,

    /**
     * @brief Extended menu options for the **TextEditor** component. This attribute can be set and reset as required
     * through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Extended menu options. After being set, you can customize the behavior of the default menu items
     * or add custom option content. The parameter type is {@link ArkUI_TextEditMenuOptions}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_EDIT_MENU_OPTIONS,

    /**
     * @brief Placeholder options when there is no input for the **TextEditor** component. This attribute can be set
     * and reset as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Placeholder options when there is no input. The parameter type is
     * {@link ArkUI_TextEditorPlaceholderOptions}. When not passed, the editor does not display placeholder text
     * when there is no input.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_PLACEHOLDER,

    /**
     * @brief Styled string controller of the **TextEditor** component. This attribute can be set as required through
     * APIs. After it is set, the content, caret, selection, input style, and editing state in the **TextEditor**
     * component can be managed through the controller.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Styled string controller. The parameter type is {@link ArkUI_TextEditorStyledStringController}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_STYLED_STRING_CONTROLLER,

    /**
     * @brief Whether to enable preview text for the **TextEditor** component. When enabled, the pinyin and stroke
     * characters entered during the input method input process are displayed within the component. This attribute
     * can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable preview text. The value **1** indicates to enable preview text, and **0**
     * indicates the opposite. The default value is **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether preview text is enabled. The value **1** indicates preview text is enabled, and **0**
     * indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ENABLE_PREVIEW_TEXT,

    /**
     * @brief **TextLayoutManager** of the **TextEditor** component. After it is obtained, the layout information of
     * the text, such as the number of lines, line height, and content offset, can be queried through the layout
     * manager. This attribute can be obtained as required through APIs.
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Layout manager, through which the layout information of the text can be queried. The parameter
     * type is {@link ArkUI_TextLayoutManager}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_LAYOUT_MANAGER,

    /**
     * @brief Whether to enable the AI menu for text selection and recognition of the TextEditor component, used to
     * control whether the AI recognition menu is displayed when a special text entity is selected. This attribute
     * can be set, reset, and obtained as required through APIs. When enabled, intelligent recognition and operation
     * options can be provided based on the selected text content.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable the AI menu for text selection and recognition. The value **1** means to
     * enable, and **0** means the opposite. The default value is **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the AI menu is enabled for text selection and recognition. **0** indicates
     * disabled, and **1** indicates enabled.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ENABLE_SELECTED_DATA_DETECTOR,

    /**
     * @brief Background color of the selected content in the **TextEditor** component. This attribute can be set,
     * reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.data[0].u32: Background color of the selected content, in 0xARGB format, for example, **0xFFFF0000**
     * indicates red. The color follows the system theme color by default.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.data[0].u32: Background color of the selected content, in 0xARGB format, for example, **0xFFFF0000**
     * indicates red. The color follows the system theme color by default.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_SELECTED_BACKGROUND_COLOR,

    /**
     * @brief Whether to enable the input method when the focus is obtained in a way other than by clicking in the **
     * TextEditor** component. This attribute can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable the input method when the focus is obtained in a way other than clicking.
     * The value **1** means to enable, and **0** means the opposite. The default value is **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the input method is enabled when the focus is obtained in a way other than clicking.
     * The value **1** indicates the input method is enabled, and **0** indicates the input method is disabled.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ENABLE_KEYBOARD_ON_FOCUS,

    /**
     * @brief Maximum number of characters in the **TextEditor** component. This attribute can be set, reset, and
     * obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Maximum number of characters allowed to be entered in the text editor. The value range is
     * [0, +∞). Text input is blocked once this limit is exceeded. The input length is not limited when this
     * parameter is set to **0**, a negative number, or not set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Maximum number of characters allowed to be entered in the text editor.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_MAX_LENGTH,

    /**
     * @brief Maximum number of lines in the **TextEditor** component. This attribute can be set, reset, and obtained
     * as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Maximum number of lines in the text editor. The value range is (0, +∞). When set to 0, a
     * negative number, or not set, the default value **UINT32_MAX** is used, which means no limit on the number of
     * lines. It is recommended to set this parameter in scenarios where a fixed display height is required.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Maximum number of lines in the text editor.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_MAX_LINES,

    /**
     * @brief Whether to enable haptic feedback of the **TextEditor** component. When enabled, haptic feedback
     * vibration responses are generated during interactive operations such as text drag and selection. This
     * attribute can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable haptic feedback in the text editor. The value **1** means to enable, and
     * **0** means the opposite. The default value is **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether haptic feedback is enabled. The value **1** indicates haptic feedback is enabled, and
     * **0** indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ENABLE_HAPTIC_FEEDBACK,

    /**
     * @brief Copy options of the **TextEditor** component, which can be set, reset, and obtained as required through
     * APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Copy options. The parameter type is {@link ArkUI_CopyOptions}. The default value is
     * **ARKUI_COPY_OPTIONS_LOCAL_DEVICE**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Copy options. The parameter type is {@link ArkUI_CopyOptions}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_COPY_OPTIONS,

    /**
     * @brief Keyboard appearance of the **TextEditor** component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Keyboard appearance. The parameter type is {@link ArkUI_KeyboardAppearance}. The default
     * value is **ARKUI_KEYBOARD_APPEARANCE_NONE_IMMERSIVE**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Keyboard appearance currently set for the text editor. The parameter type is
     * {@link ArkUI_KeyboardAppearance}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_KEYBOARD_APPEARANCE,

    /**
     * @brief Whether the **TextEditor** component blocks the back key event from propagating to the upper layer. This
     * attribute can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to block the propagation of return events. The value **1** indicates to block, and
     * **0** indicates the opposite. The default value is **0**. It is recommended to set this to **1** when the
     * editor has unsaved content or when the back key needs to be intercepted to prevent accidental exit.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the propagation of return events is blocked. The value **1** indicates that the
     * propagation of return events is blocked, and **0** indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_STOP_BACK_PRESS,

    /**
     * @brief Whether to enable automatic spacing for Chinese and Western characters in the **TextEditor** component.
     * This attribute can be set, reset, and obtained as required through APIs. It is applicable to editing scenarios
     * with mixed Chinese and English content. When enabled, spacing is automatically added between Chinese and
     * Western characters to improve the reading experience of mixed text.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable automatic spacing between Chinese and English characters. The value **1**
     * indicates to enable, and **0** indicates the opposite. The default value is **0**. It is recommended to set
     * this parameter to **1** in editing scenarios with mixed Chinese and English content to improve the reading
     * experience of mixed text.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether automatic spacing is enabled between Chinese and English characters. The value **1**
     * indicates automatic spacing is enabled, and **0** indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ENABLE_AUTO_SPACING,

    /**
     * @brief Custom keyboard of the **TextEditor** component. Pass this attribute when the system default keyboard
     * needs to be replaced (for example, special input layouts such as a numeric keyboard or an emoji keyboard). When
     * not passed, the system default keyboard is used. This attribute can be set, reset, and obtained as required
     * through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Custom keyboard. The parameter type is {@link ArkUI_NodeHandle}.</li>
     * <li>.value[0]?.i32: Whether the custom keyboard supports content avoidance, that is, whether the page content
     * automatically adjusts its position to avoid being covered by the keyboard when the keyboard is displayed. The
     * value **0** indicates not supported, and **1** indicates supported. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Custom keyboard. The parameter type is {@link ArkUI_NodeHandle}.</li>
     * <li>.value[0].i32: Whether the custom keyboard supports content avoidance, that is, whether the page content
     * automatically adjusts its position to avoid being covered by the keyboard when the keyboard is displayed. The
     * value **0** indicates not supported, and **1** indicates supported.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_CUSTOM_KEYBOARD,

    /**
     * @brief Binds the custom text selection menu of the **TextEditor** component. This attribute can be set and reset
     * as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Custom text selection menu. When not passed, the system default text selection menu is used. The
     * parameter type is {@link ArkUI_TextEditorSelectionMenuOptions}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_BIND_SELECTION_MENU,

    /**
     * @brief Whether to enable the anti-truncation spacing for the first and last lines of the **TextEditor**
     * component. When enabled, spacing is added to the first and last lines to avoid text truncation. This attribute
     * can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to add spacing. The value **1** means to add spacing, and **0** means not to add
     * spacing. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether spacing is added. The value **1** means that spacing is added, and **0** means
     * spacing is not added.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_INCLUDE_FONT_PADDING,

    /**
     * @brief Whether to enable line height adaptation of the **TextEditor** component. When multiple lines of text
     * are overlaid, the line height can adapt based on the actual height of the text. This attribute can be set,
     * reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable line height adaptation. The value **1** means to enable, and **0** means
     * the opposite. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether line height adaptation is enabled. The value **1** means line height adaptation is
     * enabled, and **0** means the opposite.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_FALLBACK_LINE_SPACING,

    /**
     * @brief Whether to enable leading punctuation compression in the **TextEditor** component. When enabled, the
     * punctuation at the beginning of a line reduces its occupied width to adjust the text layout alignment. This
     * attribute can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable leading punctuation compression. The value **1** means to enable, and
     * **0** means the opposite. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether leading punctuation compression is enabled. The value **1** indicates that leading
     * punctuation compression is enabled, and **0** indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_COMPRESS_LEADING_PUNCTUATION,

    /**
     * @brief Selected drag preview style of the **TextEditor** component. This attribute can be set, reset, and
     * obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Selected drag preview style. The parameter type is {@link ArkUI_SelectedDragPreviewStyle}. Pass
     * this parameter when you need to customize the preview effect when dragging selected text. When not passed, the
     * system default drag preview style is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Selected drag preview style. The parameter type is {@link ArkUI_SelectedDragPreviewStyle}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_SELECTED_DRAG_PREVIEW_STYLE,

    /**
     * @brief Whether to enable the single-line mode of the **TextEditor** component. This attribute can be set,
     * reset, and obtained as required through APIs. When enabled, the maximum number of lines set by the
     * **NODE_TEXT_EDITOR_MAX_LINES** attribute no longer takes effect.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable the single-line mode. The value **1** means to enable, and **0** means
     * the opposite. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the single-line mode is enabled. The value **1** indicates that the single-line
     * mode is enabled, and **0** means the opposite.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_SINGLE_LINE,

    /**
     * @brief Whether to enable orphan character optimization during text layout in **TextEditor**. This attribute can
     * be set, reset, and obtained as required through APIs. When enabled, line break positions are adjusted to avoid
     * orphan characters as much as possible. It takes effect only when the {@link ArkUI_WordBreak} attribute is not
     * set to **ARKUI_WORD_BREAK_BREAK_ALL**.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable orphan character optimization. The value **1** indicates to enable, and
     * **0** indicates the opposite. The default value is **0**. This parameter takes effect only when the
     * {@link ArkUI_WordBreak} attribute is not set to **ARKUI_WORD_BREAK_BREAK_ALL**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether orphan character optimization is enabled. The value **0** indicates disabled, and
     * **1** indicates enabled.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.0.0
     */
     NODE_TEXT_EDITOR_ORPHAN_CHAR_OPTIMIZATION,

    /**
     * @brief Whether to enable horizontal scrolling for the **TextEditor** component when the text width exceeds the
     * content area width. This attribute can be set, reset, and obtained as required through APIs.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable horizontal scrolling. The value **1** means to enable, and **0** means the
     * opposite. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether horizontal scrolling is enabled. The value **1** means enabled, and **0** means the
     * opposite.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.0.0
     */
    NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING,

    /**
     * @brief Whether to enable punctuation hanging at the end of a line for the **TextEditor** component. This
     * attribute can be set, reset, and obtained as required through APIs.<br>When enabled, a single punctuation mark
     * at the end of a line overflows the layout width without wrapping, preventing the punctuation mark from wrapping
     * to the beginning of the next line and thereby improving the text layout effect.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable punctuation hanging at the end of a line. The value **1** indicates to
     * enable, and **0** indicates the opposite. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether punctuation hanging at the end of a line is enabled. The value **1** means
     * punctuation hanging is enabled, and **0** means the opposite.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.0.0
     */
    NODE_TEXT_EDITOR_PUNCTUATION_OVERFLOW,

    /**
     * @brief Defines the text editor type.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:
     * .value[0].i32: text editor type {@link OH_ArkUI_TextEditorType}.
     * The default value is <b>OH_ARKUI_TEXT_EDITOR_TYPE_NORMAL</b>.
     *
     * Format of the return value {@link ArkUI_AttributeItem}:
     * .value[0].i32: text editor type {@link OH_ArkUI_TextEditorType}.
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_TYPE = 22031,

    /**
     * @brief Defines whether to display the password icon at the end of the password text editor.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:
     * .value[0].i32: whether to display the password icon at the end of the password text editor.
     * The value <b>true</b> means to display the password icon, and <b>false</b> means the opposite.
     *
     * Format of the return value {@link ArkUI_AttributeItem}:
     * .value[0].i32: The value <b>1</b> means to display the password icon, and <b>0</b> means the opposite.
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_SHOW_PASSWORD_ICON = 22032,

    /**
     * @brief Defines the password icon of the text editor.
     * This attribute can be set and reset as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:
     * .value[0].string: show icon image source.
     * .value[1].string: hide icon image source.
     *
     * Format of the return value {@link ArkUI_AttributeItem}:
     * .value[0].string: show icon image source.
     * .value[1].string: hide icon image source.
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_PASSWORD_ICON = 22033,

    /**
     * @brief Whether to enable autofill. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable autofill. The value **1** means to enable, and **0** means the opposite.
     * The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether autofill is enabled. The value **1** means enabled, and **0** means disabled.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_ENABLE_AUTO_FILL = 22034,

    /**
     * @brief Autofill type. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: autofill type, used to specify the content type for autofill scenarios.
     * <br>The parameter type is {@link ArkUI_TextInputContentType}.
     * For details about the enum values and applicable scenarios, see {@link ArkUI_TextInputContentType}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: autofill type, used to determine the autofill content type.
     * The parameter type is {@link ArkUI_TextInputContentType}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_CONTENT_TYPE = 22035,

    /**
     * @brief Rules for generating passwords. When autofill is used, these rules are transparently transmitted to
     * Password Vault for generating a new password. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: rules for generating passwords, used to control new password generation by being transparently
     * transmitted to the Password Vault when autofill is triggered.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: rules for generating passwords.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_PASSWORD_RULES = 22036,

    /**
     * @brief Sets whether to enable the autofill animation. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable the autofill animation. The value **1** means to enable,
     * and **0** means the opposite. The default value is **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the autofill animation is enabled. The value **1** means enabled,
     * and **0** means disabled.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_ENABLE_FILL_ANIMATION = 22037,

    /**
     * @brief Sets whether to show the underline. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to show the underline. The value **1** means to show, and **0** means the opposite.
     * The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the underline is shown. The value **1** means shown, and **0** means not shown.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_SHOW_UNDERLINE = 22038,

    /**
     * @brief Sets the color of the underline. This attribute can be set, reset, and obtained as required through APIs.
     * This attribute takes effect only after NODE_TEXT_EDITOR_SHOW_UNDERLINE is set to **1**.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: color of the underline applied to the text being typed in.
     * The value is in 0xARGB format.</li>
     * <li>.value[1].u32: color of the underline applied to the text in the normal state.
     * The value is in 0xARGB format.</li>
     * <li>.value[2].u32: color of the underline applied to the text when an error is detected.
     * The value is in 0xARGB format.</li>
     * <li>.value[3].u32: color of the underline applied to the text when it is disabled.
     * The value is in 0xARGB format.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: color of the underline applied to the text being typed in.
     * The value is in 0xARGB format.</li>
     * <li>.value[1].u32: color of the underline applied to the text in the normal state.
     * The value is in 0xARGB format.</li>
     * <li>.value[2].u32: color of the underline applied to the text when an error is detected.
     * The value is in 0xARGB format.</li>
     * <li>.value[3].u32: color of the underline applied to the text when it is disabled.
     * The value is in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_UNDERLINE_COLOR = 22039,

    /**
     * @brief Sets the caret width. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: caret width, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: caret width, in vp.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_CARET_STYLE = 22040,

    /**
     * @brief Sets whether to select all text in the initial state. This attribute can be set, reset,
     * and obtained as required through APIs.
     * The full selection is triggered only when the component gains focus for the first time
     * and the layout is complete. It is not triggered when the window regains focus.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to select all text in the initial state. The value **1** means to enable,
     * and **0** means the opposite. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether to select all text in the initial state. The value **1** means to select all,
     * and **0** means the opposite.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_SELECT_ALL = 22041,

    /**
     * @brief Sets whether to blur on submit. This attribute can be set, reset, and obtained as required through APIs.
     * This attribute takes effect only when EnterKeyType is NEW_LINE and the Enter key is pressed.
     * When set to **1**, the keyboard is closed and the component loses focus without inserting a newline.
     * When set to **0**, a newline is inserted and the component retains focus.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to blur on submit. The value **1** means to enable, and **0** means the opposite.
     * The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether to blur on submit. The value **1** means to blur, and **0** means the opposite.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_BLUR_ON_SUBMIT = 22042,

    /**
     * @brief Gets the position and size of the editing content area. This attribute can only be obtained.
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: x offset of the editing content area.</li>
     * <li>.value[1].f32: y offset of the editing content area.</li>
     * <li>.value[2].f32: width of the editing content area.</li>
     * <li>.value[3].f32: height of the editing content area.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_CONTENT_RECT = 22043,

    /**
     * @brief Sets whether to hide the selection menu. This attribute can be set, reset,
     * and obtained as required through APIs.
     * When set to **1**, the selection menu is not displayed on long press, double-tap, or right-click,
     * but the selection handles are not affected.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to hide the selection menu. The value **1** means to hide,
     * and **0** means the opposite. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the selection menu is hidden. The value **1** means hidden,
     * and **0** means not hidden.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_SELECTION_MENU_HIDDEN = 22044,

    /**
     * @brief Sets whether to skip the preview state on long press and directly enter the editing state.
     * This attribute can be set, reset, and obtained as required through APIs.
     * When set to **1**, long press directly enters the editing state (keyboard pops up and cursor twinkles),
     * skipping the preview state. Double-tap behavior is not affected.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to skip the preview state on long press. The value **1** means to skip,
     * and **0** means the opposite. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether to skip the preview state on long press. The value **1** means to skip,
     * and **0** means the opposite.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_ENABLE_SKIP_PREVIEW_LONG_PRESS = 22045,

    /**
     * @brief Defines the style of the cancel button of the text editor.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: button style {@link ArkUI_CancelButtonStyle}.
     * The default value is <b>ARKUI_CANCELBUTTON_STYLE_INPUT</b>.</li>
     * <li>.value[1]?.f32: button icon size, in vp.</li>
     * <li>.value[2]?.u32: button icon color, in 0xARGB format. For example, 0xFFFF0000 indicates red.</li>
     * <li>?.string: button icon image source. The value is the local address of the image,
     * for example, /pages/icon.png.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: button style {@link ArkUI_CancelButtonStyle}.</li>
     * <li>.value[1].f32: icon size, in vp.</li>
     * <li>.value[2].u32: button icon color, in 0xARGB format.</li>
     * <li>.string: button icon image source.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_CANCEL_BUTTON = 22046,

    /**
     * @brief Defines the counter settings. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to show a character counter.
     * The value <b>true</b> means to show a character counter.</li>
     * <li>.value[1]?.f32: threshold percentage for displaying the character counter.
     * The character counter is displayed when the number of characters that have been entered
     * is greater than the maximum number of characters multiplied by the threshold percentage value.
     * The value range is 1 to 100. If the value is a decimal, it is rounded down.</li>
     * <li>.value[2]?.i32: whether to highlight the border when the number of entered characters
     * reaches the maximum.</li>
     * <li>.object: counter configuration. The parameter type is {@link ArkUI_ShowCounterConfig}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to show a character counter.</li>
     * <li>.value[1].f32: threshold percentage for displaying the character counter. The character counter is displayed
     * when the number of characters that have been entered is greater than the maximum number of characters multiplied
     * by the threshold percentage value. The value range is 1 to 100.</li>
     * <li>.value[2].i32: whether to highlight the border when the number of entered characters reaches the maximum.
     * The default value is <b>true</b>.</li>
     * <li>.object: counter configuration. The parameter type is {@link ArkUI_ShowCounterConfig}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_SHOW_COUNTER = 22047,

    /**
     * @brief Sets the input filter regex for the **TextEditor** component.
     * <br>This attribute can be set, reset, and obtained as required through APIs.
     * <br>This attribute is effective only in spanString mode (including both single-line and multi-line modes).
     * <br>When both inputFilter and maxLength are set, the filter priority is: inputFilter first, then maxLength.
     * <br>When the regex changes, existing content is silently re-filtered (consistent with TextInput behavior).
     * <br>Non-character content (ImageSpan/SymbolSpan/BuilderSpan) is treated as \uFFFC during regex matching.
     * <br>The format of {@link ArkUI_AttributeItem} for property setting method parameters and property getting method
     * return values is as follows.
     * <br>**Parameter:**
     * <br>.string: Regex expression string for input filtering.
     * Only characters matching the regex whitelist are allowed.
     * An empty string is equivalent to not setting the filter.
     * <br>**Return:**
     * <br>.string: The currently set input filter regex expression string.
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_INPUT_FILTER = 22048,

    /**
     * @brief Defines the index string array.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: array of the alphabet index. the type is string array.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: array of the alphabet index. the type is string array.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_INDEXER_ARRAY = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_ALPHABET_INDEXER,

    /**
     * @brief Defines the text color of the index item in the unselected state.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: text color, in 0xARGB format. The default value is <b>0xFFFFFFFF</b>, which indicates
     * white.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: text color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_INDEXER_COLOR,

    /**
     * @brief Defines the text color of the index item in the selected state.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: text color, in 0xARGB format. The default value is <b>0xFFFFFFFF</b>, which indicates
     * white.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: text color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_INDEXER_SELECTED_COLOR,

    /**
     * @brief Defines the text color of the popup.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: text color, in 0xARGB format. The default value is <b>0xFFFFFFFF</b>, which indicates
     * white.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: text color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_INDEXER_POPUP_COLOR,

    /**
     * @brief Defines the background color of the index item in the selected state.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format. The default value is <b>0xFF1F71FF</b>, which
     * indicates blue.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_INDEXER_SELECTED_BACKGROUND_COLOR,

    /**
     * @brief Defines the background color of the popup.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format. The default value is <b>0xD8404040</b>, which
     * indicates dark gray.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_INDEXER_POPUP_BACKGROUND_COLOR,

    /**
     * @brief Defines whether to use the popup.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to use the popup. The value <b>1</b> indicates to use the popup, and <b>0</b>
     * indicates the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the popup is used.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_INDEXER_USE_POPUP,

    /**
     * @brief Defines the font style of the selected index item.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: font family. Multiple fonts are separated by comma (,). This is an optional parameter.
     * The default value is <b>"HarmonyOS Sans"</b>.</li>
     * <li>.value[0].f32: font size, in fp. This is an optional parameter. The default value is <b>13</b>.</li>
     * <li>.value[1].i32: font weight. This is an optional parameter. The parameter type is
     * {@link ArkUI_FontWeight}. The default value is <b>ARKUI_FONT_WEIGHT_W500</b>.</li>
     * <li>.value[2].i32: font style. This is an optional parameter. The parameter type is
     * {@link ArkUI_FontStyle}. The default value is <b>ARKUI_FONT_STYLE_NORMAL</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: font family. Multiple fonts are separated by comma (,).</li>
     * <li>.value[0].f32: font size, in fp.</li>
     * <li>.value[1].i32: font weight. The parameter type is {@link ArkUI_FontWeight}.</li>
     * <li>.value[2].i32: font style. The parameter type is {@link ArkUI_FontStyle}.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_SELECTED_FONT,

    /**
     * @brief Defines the font style of the popup.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: font family. Multiple fonts are separated by comma (,). This is an optional parameter.
     * The default value is <b>"HarmonyOS Sans"</b>.</li>
     * <li>.value[0].f32: font size, in fp. This is an optional parameter. The default value is <b>19</b>.</li>
     * <li>.value[1].i32: font weight. This is an optional parameter. The parameter type is
     * {@link ArkUI_FontWeight}. The default value is <b>ARKUI_FONT_WEIGHT_W500</b>.</li>
     * <li>.value[2].i32: font style. This is an optional parameter. The parameter type is
     * {@link ArkUI_FontStyle}. The default value is <b>ARKUI_FONT_STYLE_NORMAL</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: font family. Multiple fonts are separated by comma (,).</li>
     * <li>.value[0].f32: font size, in fp.</li>
     * <li>.value[1].i32: font weight. The parameter type is {@link ArkUI_FontWeight}.</li>
     * <li>.value[2].i32: font style. The parameter type is {@link ArkUI_FontStyle}.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_INDEXER_POPUP_FONT,

    /**
     * @brief Defines the default font style of the index item.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: font family. Multiple fonts are separated by comma (,). This is an optional parameter.
     * The default value is <b>"HarmonyOS Sans"</b>.</li>
     * <li>.value[0].f32: font size, in fp. This is an optional parameter. The default value is <b>13</b>.</li>
     * <li>.value[1].i32: font weight. This is an optional parameter. The parameter type is
     * {@link ArkUI_FontWeight}. The default value is <b>ARKUI_FONT_WEIGHT_W500</b>.</li>
     * <li>.value[2].i32: font style. This is an optional parameter. The parameter type is
     * {@link ArkUI_FontStyle}. The default value is <b>ARKUI_FONT_STYLE_NORMAL</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: font family. Multiple fonts are separated by comma (,).</li>
     * <li>.value[0].f32: font size, in fp.</li>
     * <li>.value[1].i32: font weight. The parameter type is {@link ArkUI_FontWeight}.</li>
     * <li>.value[2].i32: font style. The parameter type is {@link ArkUI_FontStyle}.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_FONT,

    /**
     * @brief Defines the size of the letter area of the alphabet index bar.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: diameter of the circle when the letter area is circular, in vp.
     * The default value is <b>24</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: diameter of the circle when the letter area is circular, in vp.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_INDEXER_ITEM_SIZE,

    /**
     * @brief Defines the index of the selected item.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: index of the selected item. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: index of the selected item.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_INDEXER_SELECTED,

    /**
     * @brief Defines whether to collapse the characters when the space of the index bar is insufficient to display
     * all characters.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to collapse the characters when the space of the index bar is insufficient to
     * display all characters. The value <b>1</b> indicates to collapse the characters, and <b>0</b> indicates the
     * opposite. The default value is <b>1</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the characters are collapsed when the space of the index bar is insufficient to
     * display all characters.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_AUTO_COLLAPSE,

    /**
     * @brief Defines the background blur style of the popup.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: background blur style of the popup. The parameter type is {@link ArkUI_BlurStyle}.
     * The default value is <b>ARKUI_BLUR_STYLE_NONE</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: background blur style of the popup.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_POPUP_BACKGROUND_BLUR_STYLE,

    /**
     * @brief Defines the alignment mode of the child components in the container. This attribute can be set, reset,
     * and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Alignment mode. The parameter type is {@link ArkUI_Alignment}. The value options are as
     * follows: **TOP** (top alignment), **BOTTOM** (bottom alignment), **LEFT** (left alignment), **RIGHT** (right
     * alignment), **TOP_START** (top-left alignment), **TOP_END** (top-right alignment), **BOTTOM_START** (bottom-left
     * alignment), **BOTTOM_END** (bottom-right alignment), **CENTER** (center alignment), **START** (alignment with the
     * start edge), and **END** (alignment with the end edge). For the mapping between enumerated values and numbers,
     * see {@link ArkUI_Alignment}. Select the corresponding alignment mode when a child component needs to be aligned
     * at a specific position within the container. The default value is **ARKUI_ALIGNMENT_CENTER** (center alignment).
     * When an invalid value is set, the default value is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Alignment mode. The parameter type is {@link ArkUI_Alignment}. For details about the values
     * and their meanings, see the parameter description.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_STACK_ALIGN_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_STACK,

    /**
     * @brief Scrollbar display mode. This attribute can be set, reset, and obtained as required through APIs. {@link
     * List}, {@link Scroll}, and {@link WaterFlow} support this attribute since API version 12, and {@link Grid}
     * supports this attribute since API version 22.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: scrollbar status. The parameter type is {@link ArkUI_ScrollBarDisplayMode}. The default value
     * is <b>ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO</b> for the <b>List</b>, <b>Grid</b>, and <b>Scroll</b> components, and
     * <b>ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF</b> for the <b>WaterFlow</b> component.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: scrollbar status. The parameter type is {@link ArkUI_ScrollBarDisplayMode}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_BAR_DISPLAY_MODE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,
    /**
     * @brief Width of the scrollbar. This attribute can be set, reset, and obtained as required through APIs. {@link
     * List}, {@link Scroll}, and {@link WaterFlow} support this attribute since API version 12, and {@link Grid}
     * supports this attribute since API version 22.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: width of the scrollbar, in vp. The default value is <b>4</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: width of the scrollbar, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_BAR_WIDTH,
    /**
     * @brief Color of the scrollbar. This attribute can be set, reset, and obtained as required through APIs. {@link
     * List}, {@link Scroll}, and {@link WaterFlow} support this attribute since API version 12, and {@link Grid}
     * supports this attribute since API version 22.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.data[0].u32: color of the scrollbar, in 0xARGB format.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.data[0].u32: color of the scrollbar, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_BAR_COLOR,
    /**
     * @brief Scroll direction. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: scroll direction. The parameter type is {@link ArkUI_ScrollDirection}. The default value is
     * <b>ARKUI_SCROLL_DIRECTION_VERTICAL</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: scroll direction. The parameter type is {@link ArkUI_ScrollDirection}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_SCROLL_DIRECTION,
    /**
     * @brief Effect used at the edges of the component when the boundary of the scrollable content is reached. This
     * attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: effect used at the edges of the component when the boundary of the scrollable content is
     * reached. The parameter type is {@link ArkUI_EdgeEffect}. The default value is <b>ARKUI_EDGE_EFFECT_NONE</b>.</li>
     * <li>.value[1]?.i32: whether to enable the scroll effect when the component content size is smaller than the
     * component itself. Optional. The value <b>1</b> means to enable the scroll effect, and <b>0</b> means the
     * opposite. The default value for the List/Grid/WaterFlow component is <b>0</b>, and the default value for the
     * Scroll component is <b>1</b>.</li>
     * <li>.value[2]?.i32: direction in which the effect takes effect. The parameter type is {@link ArkUI_EffectEdge}.
     * The default value is <b>ARKUI_EFFECT_EDGE_START | ARKUI_EFFECT_EDGE_END</b>. This parameter is supported since
     * API version 16.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: effect used at the edges of the component when the boundary of the scrollable content is
     * reached. The parameter type is {@link ArkUI_EdgeEffect}.</li>
     * <li>.value[1].i32: whether to enable the scroll effect when the component content size is smaller than the
     * component itself. Optional. The value <b>1</b> means to enable the scroll effect, and <b>0</b> means the
     * opposite.</li>
     * <li>.value[2].i32: edge for which the effect takes effect when the boundary of the scrollable content is
     * reached. The parameter type is {@link ArkUI_EffectEdge}. This parameter is supported since API version 16.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_EDGE_EFFECT,
    /**
     * @brief Whether to support scroll gestures. When this attribute is set to **0**, scrolling by finger or mouse is
     * not supported, but the scrolling controller API is not affected.
     * <br>The **List**, **Scroll**, and **WaterFlow** components support this attribute since API version 12, and the
     * **Grid** component supports this attribute since API version 22.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to support scroll gestures. The default value is <b>true</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to support scroll gestures.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_ENABLE_SCROLL_INTERACTION,
    /**
     * @brief Friction coefficient. It applies only to gestures in the scrolling area, and it only indirectly affects
     * the scroll chaining during the inertial scrolling process.
     * <br>The **List**, **Scroll**, and **WaterFlow** components support this attribute since API version 12, and the
     * **Grid** component supports this attribute since API version 22.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: friction coefficient. The default value is <b>0.6</b> for non-wearable devices and <b>0.9</b>
     * for wearable devices.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: friction coefficient.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_FRICTION,
    /**
     * @brief Scroll snapping mode of the {@link Scroll} component. This attribute can be set, reset, and obtained as
     * required through APIs. If both swipe-to-turn-pages and scroll snapping are set, scroll snapping takes effect
     * first, and swipe-to-turn-pages does not take effect.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: alignment mode for the scroll snap position. The parameter type is
     * {@link ArkUI_ScrollSnapAlign}. The default value is <b>ARKUI_SCROLL_SNAP_ALIGN_NONE</b>.</li>
     * <li>.value[1].i32: whether to enable the snap to start feature. When scroll snapping is defined for the
     * <b><Scroll></b> component, setting this attribute to <b>false</b> enables the component to scroll between the
     * start edge and the first snap point. The default value is <b>true</b>. It is valid only when there are multiple
     * snap points.</li>
     * <li>.value[2].i32: Whether to enable the snap to end feature. When scroll snapping is defined for the
     * <b><Scroll></b> component, setting this attribute to <b>false</b> enables the component to scroll between the
     * end edge and the last snap point. The default value is <b>true</b>. It is valid only when there are multiple
     * snap points.</li>
     * <li>.value[3...].f32: snap points for the <b><Scroll></b> component. Each snap point defines the offset from an
     * edge to which the <b><Scroll></b> component can scroll.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: alignment mode for the scroll snap position. The parameter type is
     * {@link ArkUI_ScrollSnapAlign}.</li>
     * <li>.value[1].i32: whether to enable the snap to start feature. When scroll snapping is defined for the
     * <b><Scroll></b> component, setting this attribute to <b>false</b> enables the component to scroll between the
     * start edge and the first snap point.</li>
     * <li>.value[2].i32: Whether to enable the snap to end feature. When scroll snapping is defined for the
     * <b><Scroll></b> component, setting this attribute to <b>false</b> enables the component to scroll between the
     * end edge and the last snap point.</li>
     * <li>.value[3...].f32: snap points for the <b><Scroll></b> component. Each snap point defines the offset from an
     * edge to which the <b><Scroll></b> component can scroll.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_SNAP,

    /**
     * @brief Nested scrolling attribute, which can be set, reset, and obtained as required through APIs. The **List**,
     * **Scroll**, and **WaterFlow** components support this attribute since API version 12, and the **Grid** component
     * supports this attribute since API version 22.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: nested scrolling option when the component scrolls forward. The parameter type is
     * {@link ArkUI_ScrollNestedMode}.</li>
     * <li>.value[1].i32: nested scrolling option when the component scrolls backward. The parameter type is
     * {@link ArkUI_ScrollNestedMode}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: nested scrolling option when the component scrolls forward. The parameter type is
     * {@link ArkUI_ScrollNestedMode}.</li>
     * <li>.value[1].i32: nested scrolling option when the component scrolls backward. The parameter type is
     * {@link ArkUI_ScrollNestedMode}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_NESTED_SCROLL,
    /**
     * @brief Position to scroll to for the {@link Scroll} component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: horizontal scrolling offset, in vp.</li>
     * <li>.value[1].f32: vertical scrolling offset, in vp.</li>
     * <li>.value[2]?.i32: scrolling duration, in milliseconds. Optional.</li>
     * <li>.value[3]?.i32: scrolling curve. Optional. The parameter type is {@link ArkUI_AnimationCurve}. The default
     * value is <b>ARKUI_CURVE_EASE</b>.</li>
     * <li>.value[4]?.i32: whether to enable the default spring animation. Optional. The default value <b>0</b> means
     * not to enable the default spring animation.</li>
     * <li>.value[5]?.i32: whether to convert the scroll animation to an overshoot animation when the boundary is
     * reached. Optional.</li>
     * <li>.value[6]?.i32: whether the component can stop at an overscrolled position. This parameter is supported
     * since API version 20.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: horizontal scrolling offset, in vp.</li>
     * <li>.value[1].f32: vertical scrolling offset, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_OFFSET,

    /**
     * @brief Edge position to scroll to for the {@link Scroll} component. This attribute can be set and obtained as
     * required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: edge position to scroll to. The parameter type is {@link ArkUI_ScrollEdge}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the container at the edge position. The value <b>-1</b> means that the container is
     * not at the edge position. If the container is at the edge position, the parameter type is
     * {@link ArkUI_ScrollEdge}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_EDGE,

    /**
     * @brief Whether to enable the swipe-to-turn-pages feature. This attribute can be set, reset, and obtained as
     * required through APIs. If both {@link enablePaging} and {@link scrollSnap} are set, {@link scrollSnap} takes
     * effect preferentially, and {@link enablePaging} does not take effect.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable the swipe-to-turn-pages feature. The default value is <b>false</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to enable the swipe-to-turn-pages feature.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_ENABLE_PAGING,

    /**
     * @brief Scrolls to the next or previous page.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Indicates whether to scroll to next page. Value 0 indicates scroll to next page and value 1
     * indicates scroll to previous page.</li>
     * <li>.value[1]?.i32: Indicates whether to enable animation. Value 1 indicates enable and 0 indicates disable.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_PAGE,

    /**
     * @brief Scrolling distance. The **List**, **Scroll**, and **WaterFlow** components support this attribute since
     * API version 12. The **Grid** component supports this attribute since API version 26.0.0.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Horizontal scrolling distance in vp.</li>
     * <li>.value[1].f32: Vertical scrolling distance in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_SCROLL_BY,

    /**
     * @brief Performs inertial scrolling based on the initial velocity passed in.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Initial velocity of inertial scrolling. Unit: vp/s. If the value specified is 0, it is
     * considered as invalid, and the scrolling for this instance will not take effect. If the value is positive, the
     * scroll will move downward; if the value is negative, the scroll will move upward.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 13
     */
    NODE_SCROLL_FLING,

    /**
     * @brief Edge fade effect for the scrollable component.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable the fading effect on edges. The value 0 means to disable the fading effect,
     * and 1 means to enable it.</li>
     * <li>.value[1]?.f32: length of the fading effect on edges, in vp. Default value: 32.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the fading effect on edges is enabled. The value 0 means that the fading effect is
     * disabled, and 1 means that it is enabled.</li>
     * <li>.value[1].f32: length of the fading effect on edges, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 14
     */
    NODE_SCROLL_FADING_EDGE,

    /**
     * @brief Total size of all child components when fully expanded in the scrollable component.
     * <br>The format of the return value {@link ArkUI_AttributeItem} is as follows.
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: total width of all child components when fully expanded in the scrollable component. The
     * default unit is vp.</li>
     * <li>.value[1].f32: total height of all child components when fully expanded in the scrollable component. The
     * default unit is vp. When <b>NODE_PADDING</b>, <b>NODE_MARGIN</b>, or <b>NODE_BORDER_WIDTH</b> is set, the values
     * are rounded to the nearest pixel when being converted from vp to px. The returned values are calculated based on
     * these rounded pixel values.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 14
     */
    NODE_SCROLL_SIZE,

    /**
     * @brief Offset from the start of the content of the scrollable component. {@link List} supports this attribute
     * since API version 15, and {@link Grid}, {@link Scroll}, and {@link WaterFlow} support this attribute since API
     * version 22.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: offset from the start of the content, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: offset from the start of the content, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 15
     */
    NODE_SCROLL_CONTENT_START_OFFSET,

    /**
     * @brief Offset from the end of the content of the scrollable component. {@link List} supports this attribute since
     * API version 15, and {@link Grid}, {@link Scroll}, and {@link WaterFlow} support this attribute since API version
     * 22.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: offset from the end of the content, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: offset from the end of the content, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 15
     */
    NODE_SCROLL_CONTENT_END_OFFSET,

    /**
     * @brief Maximum initial velocity at the start of the fling animation that occurs after gesture-driven scrolling
     * ends. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: maximum starting fling speed, Unit: vp/s</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: maximum starting fling speed, Unit: vp/s</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 18
     */
    NODE_SCROLL_FLING_SPEED_LIMIT = 1002019,

    /**
     * @brief Content clipping area for the scrollable component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: clip content mode. The parameter type is {@link ArkUI_ContentClipMode}. The default value is
     * <b>ARKUI_CONTENT_CLIP_MODE_BOUNDARY</b> for the <b>Grid</b> and <b>Scroll</b> components, and
     * <b>ARKUI_CONTENT_CLIP_MODE_CONTENT_ONLY</b> for the <b>List</b> and <b>WaterFlow</b> components.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: clip content mode. The parameter type is {@link ArkUI_ContentClipMode}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 18
     */
    NODE_SCROLL_CLIP_CONTENT = 1002020,

    /**
     * @brief Whether to scroll back to the top when the status bar is clicked for the scrollable component. This
     * attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the scrollable scrolls back to top when status bar is clicked. The value <b>1</b>
     * means to scroll back to top, and <b>0</b> means the opposite. The default value is <b>0</b> for API versions
     * earlier than 18. For API version 18 and later, the default value is <b>0</b> for the horizontal scroll direction
     * and <b>1</b> for the vertical scroll direction.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the scrollable scrolls back to top when status bar is clicked.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 15
     */
    NODE_SCROLL_BACK_TO_TOP = 1002021,

    /**
     * @brief Margin of the scrollbar. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: start margin of the scrollbar, in vp. The default value is <b>0</b>.</li>
     * <li>.value[1].f32: end margin of the scrollbar, in vp. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: start margin of the scrollbar, in vp.</li>
     * <li>.value[1].f32: end margin of the scrollbar, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 20
     */
    NODE_SCROLL_BAR_MARGIN = 1002022,

    /**
     * @brief Maximum zoom scale for scrollable content.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: maximum zoom scale to set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: current maximum zoom scale.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 20
     */
    NODE_SCROLL_MAX_ZOOM_SCALE = 1002023,

    /**
     * @brief Minimum zoom scale for scrollable content.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: minimum zoom scale to set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: current minimum zoom scale.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 20
     */
    NODE_SCROLL_MIN_ZOOM_SCALE = 1002024,

    /**
     * @brief Zoom scale for scrollable content.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: zoom scale to set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: current zoom scale.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 20
     */
    NODE_SCROLL_ZOOM_SCALE = 1002025,

    /**
     * @brief Whether to enable the zoom bounce effect when the scaling exceeds the limits.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable the zoom bounce effect when the scaling exceeds the limits. The value
     * <b>1</b> means to enable the effect, and <b>0</b> means the opposite.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to enable the zoom bounce effect when the scaling exceeds the limits. The value
     * <b>1</b> means to enable the effect, and <b>0</b> means the opposite.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 20
     */
    NODE_SCROLL_ENABLE_BOUNCES_ZOOM = 1002026,

    /**
     * @brief Whether to support scroll using the left button on the mouse. This attribute can be set, reset, and
     * obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to support scrolling by pressing the left mouse button. 0: no; 1: yes.
     * For API versions earlier than 26.2.0, the default value is 0. For API versions 26.2.0 and later,
     * the default value is 1 when the scrollable component scrolls horizontally, 0 otherwise.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to support scrolling by pressing the left mouse button. 0: no; 1: yes.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_SCROLL_ENABLE_SCROLL_WITH_MOUSE = 1002027,

    /**
     * @brief Whether the scrollbar automatically adjusts its margin to avoid the area of the **NODE_PADDING**,
     * **NODE_SCROLL_CONTENT_START_OFFSET**, or **NODE_SCROLL_CONTENT_END_OFFSET** component. This attribute can be set,
     * reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to automatically adjust the margin of the scrollbar. <b>0</b>: yes; <b>1</b>: no.
     * Default value: <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to automatically adjust the margin of the scrollbar. <b>0</b>: yes; <b>1</b>: no.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_SCROLL_AUTO_ADJUST_MARGIN = 1002028,

    /**
     * @brief Scrollbar height. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: height of the scrollbar track, in vp. Default value: adaptive to the height of the scrollable
     * component. Value range: The value must be greater than or equal to 0. If set to a value less than 0, the default
     * value is used. If set to 0, the scrollbar is not displayed.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: height of the scrollbar track, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_SCROLL_BAR_HEIGHT = 1002029,

    /**
     * @brief Direction in which the {@link list} items are arranged. This attribute can be set, reset, and obtained as
     * required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: direction in which the list items are arranged. The parameter type is {@link ArkUI_Axis}. The
     * default value is <b>ARKUI_AXIS_VERTICAL</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: direction in which the list items are arranged. The parameter type is {@link ArkUI_Axis}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_DIRECTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST,
    /**
     * @brief Whether to pin the header to the top or the footer to the bottom in the {@link ListItemGroup} component.
     * It is used together with the **ListItemGroup** component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to pin the header to the top or the footer to the bottom in the
     * <b><ListItemGroup></b> component. It is used together with the <b><ListItemGroup></b> component. The parameter
     * type is {@link ArkUI_StickyStyle}. The default value is <b>ARKUI_STICKY_STYLE_NONE</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to pin the header to the top or the footer to the bottom in the
     * <b><ListItemGroup></b> component. It is used together with the <b><ListItemGroup></b> component. The parameter
     * type is {@link ArkUI_StickyStyle}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_STICKY,
    /**
     * @brief Spacing between list items. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: spacing between list items along the main axis. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: spacing between list items along the main axis.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_SPACE,
    /**
     * @brief Adapter of the **List** component. This attribute can be set, reset, and obtained as required through
     * APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeAdapter} object as the adapter.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_NODE_ADAPTER,

    /**
     * @brief Number of cached items in the adapter of the **List** component. This attribute can be set, reset, and
     * obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: number of cached items in the list adapter.</li>
     * <li>.value[1]?.i32: whether to show cached items. The value <b>0</b> means to hide cached items, and <b>1</b>
     * means to show cached items. The default value is <b>0</b>. This parameter is supported since API version 15.</li>
     * <li>.value[2]?.i32: maximum cache count. This parameter is supported since API version 22.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: number of cached items in the list adapter.</li>
     * <li>.value[1].i32: whether to show cached items. The value <b>0</b> means to hide cached items, and <b>1</b>
     * means to show cached items. This parameter is supported since API version 15.</li>
     * <li>.value[2].i32: maximum cache count. This parameter is supported since API version 22.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_CACHED_COUNT,

    /**
     * @brief Scrolls to the item with the specified index. When **smooth** is set to **true**, all passed items are
     * loaded and counted in layout calculation. This may result in performance issues if a large number of items are
     * involved.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: index value of the target element to be slid to in the current container.</li>
     * <li>.value[1]?.i32: whether there is an action when sliding to the index value of a list item in the list, where
     * 1 indicates an action and 0 indicates no action. Default value: 0.</li>
     * <li>.value[2]?.i32: alignment of the sliding element with the current container. The parameter type is
     * {@link ArkUI_ScrollAlignment}. The default value is <b>ARKUI_SCROLL_ALIGNMENT_START</b>.</li>
     * <li>.value[3]?.f32: extra offset, in vp. The default value is <b>0</b>. This parameter is supported since API
     * version 15.</li>
     * <li>.value[4]?.i32: fast scroll mode for scrolling to a specified index. The parameter type is
     * {@link OH_ArkUI_FastScrollMode}, and the default value is <b>OH_ARKUI_FAST_SCROLL_MODE_NONE</b>.
     * This parameter is valid only when .value[1]?.i32 is set to 1, and is supported since API version 26.2.0.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_SCROLL_TO_INDEX,
    /**
     * @brief Alignment mode of list items along the cross axis when the cross-axis width of the list is greater than
     * the cross-axis width of list items multiplied by the number of lanes. When the list scrolls vertically, the
     * number of lanes is the number of columns; when the list scrolls horizontally, the number of lanes is the number
     * of rows. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: alignment mode of list items along the cross axis. The parameter type is
     * {@link ArkUI_ListItemAlignment}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: alignment mode of list items along the cross axis. The parameter type is
     * {@link ArkUI_ListItemAlignment}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_ALIGN_LIST_ITEM,

    /**
     * @brief Default main axis size of the child component in **List**.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: The parameter format is {@link ArkUI_ListChildrenMainSize}</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: The parameter format is {@link ArkUI_ListChildrenMainSize}</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_CHILDREN_MAIN_SIZE = 1003007,

    /**
     * @brief Index of the item displayed at the beginning of the viewport when the current list is loaded for the first
     * time. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: index value of the item displayed at the start of the viewport when the current List is
     * loaded for the first time. Default value: 0.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: index value of the item displayed at the start of the viewport when the current List is
     * loaded for the first time. Default value: 0.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_INITIAL_INDEX = 1003008,
    /**
     * @brief Style of the divider for the list items. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: divider color, in 0xARGB format.</li>
     * <li>.value[1].f32: stroke width of the divider, in vp.</li>
     * <li>.value[2].f32: distance between the divider and the start of the list, in vp.</li>
     * <li>.value[3].f32: distance between the divider and the end of the list, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: divider color, in 0xARGB format.</li>
     * <li>.value[1].f32: stroke width of the divider, in vp.</li>
     * <li>.value[2].f32: distance between the divider and the start of the list, in vp.</li>
     * <li>.value[3].f32: distance between the divider and the end of the list, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_DIVIDER = 1003009,

    /**
     * @brief Scrolls to the item with the specified index in the specified {@link list item group}. When **smooth** is
     * set to **true**, all passed items are loaded and counted in layout calculation. This may result in performance
     * issues if a large number of items are involved.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: index of the target list item group in the current list.</li>
     * <li>.value[1].i32: index of the target list item in the list item group.</li>
     * <li>.value[2]?.i32: whether to enable the smooth animation for scrolling to the item with the specified index.
     * The value <b>1</b> means to enable the animation, and <b>0</b> means the opposite. The default value is
     * <b>0</b>.</li>
     * <li>.value[3]?.i32: how the item to scroll to is aligned with the container. The parameter type is
     * {@link ArkUI_ScrollAlignment}. The default value is <b>ARKUI_SCROLL_ALIGNMENT_START</b>.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 15
     */
    NODE_LIST_SCROLL_TO_INDEX_IN_GROUP = 1003010,

    /**
     * @brief Number of lanes in the list. (The number of columns is used when the list is scrolled vertically, and the
     * number of rows is used when the list is scrolled horizontally.) This attribute can be set, reset, and obtained as
     * required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: number of lanes in the list. If the maximum and minimum lane widths are set, setting the
     * number of lanes will not take effect.</li>
     * <li>.value[1]?.f32: minimum lane width, in vp.</li>
     * <li>.value[2]?.f32: maximum column width, in vp.</li>
     * <li>.value[3]?.f32: lane spacing, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: number of lanes in the list.</li>
     * <li>.value[1].f32: minimum lane width, in vp.</li>
     * <li>.value[2].f32: maximum column width, in vp.</li>
     * <li>.value[3].f32: lane spacing, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 15
     */
    NODE_LIST_LANES = 1003011,

    /**
     * @brief Alignment mode for scroll snapping in the **List** component.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Alignment mode for scroll snapping in the **List** component. The parameter type is
     * {@link ArkUI_ScrollSnapAlign}. The default value is {@link ARKUI_SCROLL_SNAP_ALIGN_NONE}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Alignment mode for scroll snapping in the **List** component. The parameter type is
     * {@link ArkUI_ScrollSnapAlign}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 15
     */
    NODE_LIST_SCROLL_SNAP_ALIGN = 1003012,

    /**
     * @brief Whether to maintain the visible content's position when data is inserted or deleted outside the display
     * area of the **List** component.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to maintain the visible content's position when data is inserted or deleted outside
     * the display area of the **List** component. The value **1** means to maintain the visible content's position,
     * and **0** means the opposite. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the visible content's position is maintained when data is inserted or deleted
     * outside the display area of the **List** component. The value **1** means that the visible content's position
     * is maintained, and **0** means the opposite. The default value is **0**.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 15
     */
    NODE_LIST_MAINTAIN_VISIBLE_CONTENT_POSITION = 1003013,

    /**
     * @brief Whether the **List** component starts layout from the end.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the **List** component starts layout from the end. The value **0** means layout
     * starts from the top, and **1** means layout starts from the end. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the **List** component starts layout from the end. The value **0** means layout
     * starts from the top, and **1** means layout starts from the end. The default value is **0**.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 19
     */
    NODE_LIST_STACK_FROM_END = 1003014,

    /**
     * @brief Focus wrap mode of the **List** component. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Focus wrap mode of the **List** component. The parameter type is
     * {@link ArkUI_FocusWrapMode}. The default value is **ARKUI_FOCUS_WRAP_MODE_DEFAULT**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Focus wrap mode of the **List** component. The parameter type is
     * {@link ArkUI_FocusWrapMode}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 20
     */
    NODE_LIST_FOCUS_WRAP_MODE = 1003015,

    /**
     * @brief Whether the **List** component loads child nodes synchronously. This attribute can be set, reset, and
     * obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the **List** component loads child nodes synchronously. **0**: frame-by-frame
     * loading. **1**: synchronous loading. The default value is **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the **List** component loads child nodes synchronously. **0**: frame-by-frame
     * loading. **1**: synchronous loading.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 20
     */
    NODE_LIST_SYNC_LOAD = 1003016,

    /**
     * @brief Scroll snap animation speed for the **List** component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Scroll snap animation speed for the **List** component. The parameter type is
     * {@link ArkUI_ScrollSnapAnimationSpeed}. The default value is **ARKUI_SCROLL_SNAP_ANIMATION_NORMAL**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Scroll snap animation speed for the **List** component. The parameter type is
     * {@link ArkUI_ScrollSnapAnimationSpeed}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 22
     */
    NODE_LIST_SCROLL_SNAP_ANIMATION_SPEED = 1003017,

    /**
     * @brief Responsive lane layout policy of the **List** component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Number of lanes at different breakpoint specifications. The parameter type is
     * {@link ArkUI_ItemFillPolicy}.</li>
     * <li>.value[1]?.f32: Lane spacing, in vp. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Number of lanes at different breakpoint specifications. The parameter type is
     * {@link ArkUI_ItemFillPolicy}.</li>
     * <li>.value[1].f32: Lane spacing, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 22
     */
    NODE_LIST_LANES_ITEMFILLPOLICY = 1003018,

    /**
     * @brief Whether the **List** component supports the generation of empty branch nodes that do not contain any child
     * components using the **if/else** rendering control syntax in **LazyForEach** or **Repeat**.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the **List** component supports the generation of empty branches. **0**: no;
     * **1**: yes. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the **List** component supports the generation of empty branches. **0**: no;
     * **1**: yes.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 23
     */
    NODE_LIST_SUPPORT_EMPTY_BRANCH_IN_LAZY_LOADING = 1003019,

    /**
     * @brief Behavior of the system back button for the **List** component. This attribute can be set, reset, and
     * obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to collapse the swipe-out component of **ListItem** when the system back button
     * takes effect. **0**: no; **1**: yes. The default value is **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the swipe-out component of **ListItem** is collapsed when the system back button
     * takes effect. **0**: no; **1**: yes.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_LIST_BACK_PRESS_BEHAVIOR = 1003020,

    /**
     * @brief Whether to enable the edit mode for the **List** component. After the edit mode is enabled, the check box
     * is displayed by default, and users can swipe with their fingers to select multiple items. This attribute can be
     * set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable the edit mode for the **List** component. **0**: disable; **1**: enable.
     * The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the edit mode is enabled for the **List** component. **0**: disabled; **1**:
     * enabled.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_LIST_ENABLE_EDIT_MODE = 1003021,

    /**
     * @brief Edit mode options of the **List** component. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to use the default multi-selection style for the **List** component. **0**: no;
     * **1**: yes. The default value is **1**.</li>
     * <li>.value[1].i32: Whether to enable two-finger swipe to select multiple items for the **List** component.
     * **0**: disable; **1**: enable. The default value is **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the default multi-selection style is used for the **List** component. **0**: no;
     * **1**: yes.</li>
     * <li>.value[1].i32: Whether two-finger swipe is enabled to select multiple items for the **List** component.
     * **0**: disabled; **1**: enabled.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_LIST_EDIT_MODE_OPTIONS = 1003022,

    /**
     * @brief Defines whether to enable loop playback for the swiper.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable loop playback. The value <b>1</b> means to enable loop playback, and
     * <b>0</b> means the opposite. The default value is <b>1</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to enable loop playback. The value <b>1</b> means to enable loop playback, and
     * <b>0</b> means the opposite. The default value is <b>1</b>.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_LOOP = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SWIPER,
    /**
     * @brief Defines whether to enable automatic playback for child component switching in the **Swiper** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable automatic playback for child component switching. The value <b>1</b>
     * means to enable automatic playback, and <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * <li>.value[1]?.i32: whether to stop automatic playback when the user touches the screen. The value <b>1</b>
     * means to stop automatic playback, and <b>0</b> means the opposite. The default value is <b>1</b>. This
     * parameter is supported since API version 16.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether automatic playback is enabled for child component switching. The value <b>1</b>
     * indicates automatic playback is enabled for child component switching, and <b>0</b> indicates the opposite.
     * </li>
     * <li>.value[1].i32: whether automatic playback is stopped when the user touches the screen. The value <b>1</b>
     * means
     *  that automatic playback is stopped, and <b>0</b> means the opposite. This parameter is supported since
     * API version 16.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_AUTO_PLAY,
    /**
     * @brief Defines whether to show the navigation indicator for the **Swiper** component. This attribute can be
     * set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to show the navigation indicator. The value <b>1</b> means to show the navigation
     * indicator, and <b>0</b> means the opposite. The default value is <b>1</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the navigation indicator is shown. The value <b>1</b> indicates the navigation
     * indicator is shown, and <b>0</b> indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_SHOW_INDICATOR,
    /**
     * @brief Defines the interval for automatic playback in the **Swiper** component. This attribute can be set,
     * reset, and obtained as required through APIs.
     * **NODE_SWIPER_AUTO_PLAY** must be set to <b>1</b> (enable auto-play) first for the time interval set by
     * this attribute to take effect.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: interval for automatic playback, in milliseconds. The value range is [0, +∞). The
     * default value is <b>3000</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: interval for automatic playback, in ms.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_INTERVAL,
    /**
     * @brief Defines whether to use vertical swiping for the **Swiper** component. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to use vertical swiping. The value <b>1</b> means to use vertical swiping, and
     * <b>0</b> means to use horizontal swiping. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether vertical swiping is used. The value <b>1</b> indicates vertical sliding is used,
     * and <b>0</b> indicates horizontal sliding is used.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_VERTICAL,

    /**
     * @brief Defines the duration of the animation for switching child components in the **Swiper** component. This
     * attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: duration of the animation for switching child components, in milliseconds. The value range
     * is [0, +∞). The default value is <b>400</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: duration of the animation for switching child components, in milliseconds.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_DURATION,

    /**
     * @brief Defines the animation curve for the **Swiper** component. This attribute can be set, reset, and obtained
     * as required through APIs. If this attribute is not set or reset, the animation curve is
     * {@link curvesInterpolatingSpring}(-1, 1, 328, 34). If an exception occurs (such as mismatching parameter type
     * or invalid parameter) when setting this attribute, the default value <b>ARKUI_CURVE_LINEAR</b> is used.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: animation curve. The parameter type is {@link ArkUI_AnimationCurve}.
     * The default value is <b>ARKUI_CURVE_LINEAR</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: animation curve. The parameter type is {@link ArkUI_AnimationCurve}.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_CURVE,

    /**
     * @brief Defines the spacing between child components in the **Swiper** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: spacing between child components, in vp. The value range is [0, +∞), and the default value
     * is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: spacing between child components, in vp.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_ITEM_SPACE,

    /**
     * @brief Defines the index of the child component currently displayed in the **Swiper** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: index of the child component. The value range is [0, Number of child components – 1].
     * The default value is <b>0</b>.</li>
     * <li>.value[1]?.i32: swipe animation mode. The parameter type is {@link ArkUI_SwiperAnimationMode}.
     * The default value is <b>ARKUI_SWIPER_ANIMATION_MODE_NONE</b>. It is effective only for this setting.
     * This parameter is supported since API version 15.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: index of the child component.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_INDEX,

    /**
     * @brief Defines the number of elements to display per page for the **Swiper** component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: number of elements to display per page. The value range is [1, +∞). The default value is
     * <b>1</b>.</li>
     * <li>.value[1]?.i32: whether to paginate by group. The value <b>0</b> means to paginate by elements, and
     * <b>1</b> means to paginate by groups of elements displayed within the viewport. The default value is <b>0</b>.
     * This parameter is supported since API version 19.</li>
     * <li>.string?: whether to enable auto-adaptation. This parameter accepts only the value <b>"auto"</b>. When
     * this parameter is set to <b>"auto"</b>, the **value[]** parameters are ignored. If this parameter is not set,
     * the **value[]** parameter is used.
     * This parameter is supported since API version 19.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: number of elements to display per page.</li>
     * <li>.value[1].i32: whether pagination by group is enabled. The value <b>0</b> indicates that pagination is
     * performed by elements, and <b>1</b> indicates that pagination is performed by groups of elements displayed
     * within the viewport. This parameter is supported since API version 19.</li>
     * <li>.string: the value <b>auto</b> indicates the number of elements to display after being automatically
     * adjusted. This parameter is supported since API version 19.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_DISPLAY_COUNT,

    /**
     * @brief Defines whether to disable the swipe-to-switch feature of the **Swiper** component. This attribute can
     * be set, reset, and obtained as required through APIs. For example, you can disable the swipe-to-switch feature
     * to allow page switching only through navigation arrows or indicators, or to prevent gesture sliding
     * interference.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to disable the swipe-to-switch feature. The value <b>1</b> means to disable the
     * feature, and <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the swipe-to-switch feature is disabled. The value <b>1</b> indicates the
     * swipe-to-switch feature is disabled, and <b>0</b> indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_DISABLE_SWIPE,

    /**
     * @brief Defines whether to show the arrow when the mouse pointer hovers over the navigation indicator in the
     * **Swiper** component. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to show the arrow when the mouse pointer hovers over the navigation indicator.
     * The parameter type is {@link ArkUI_SwiperArrow}.
     * The default value is <b>ARKUI_SWIPER_ARROW_HIDE</b>.</li>
     * <li>?.object: style of the arrow displayed when the mouse pointer hovers over the navigation indicator.
     * The parameter type is {@link ArkUI_SwiperArrowStyle}. If this parameter is not set, the default arrow style
     * is used.
     * This parameter is supported since API version 19.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the arrow is shown when the mouse pointer hovers over the navigation indicator.
     * The parameter type is {@link ArkUI_SwiperArrow}.</li>
     * <li>.object: style of the arrow displayed when the mouse pointer hovers over the navigation indicator.
     * The parameter type is {@link ArkUI_SwiperArrowStyle}. This parameter is supported since API version 19.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_SHOW_DISPLAY_ARROW,

    /**
     * @brief Defines the effect used at the edges of the **Swiper** component when the boundary of the scrollable
     * content is reached. This attribute can be set, reset, and obtained as required through APIs. When the
     * **Swiper** component has reached the first or last child component, the edge effect is triggered if the user
     * continues to slide.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: effect used at the edges of the component when the boundary of the scrollable content is
     * reached. The parameter type is {@link ArkUI_EdgeEffect}.
     * The default value is <b>ARKUI_EDGE_EFFECT_SPRING</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: effect used at the edges of the component when the boundary of the scrollable content is
     * reached. The parameter type is {@link ArkUI_EdgeEffect}.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_EDGE_EFFECT_MODE,

    /**
     * @brief Defines the adapter of the **Swiper** component. This attribute can be set, reset, and obtained as
     * required through APIs. The adapter is used when the **Swiper** component needs to dynamically load or reuse
     * child components, for example, list carousel with a large amount of data and carousel with an infinite loop.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeAdapter} object used as the adapter. You are advised to use this parameter
     * together with **NODE_SWIPER_CACHED_COUNT** to improve performance.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: adapter object. The parameter type is {@link ArkUI_NodeAdapter}, used to dynamically load or
     * reuse **Swiper** child components.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_NODE_ADAPTER,

    /**
     * @brief Defines the number of cached items in the adapter of the **Swiper** component. This attribute can be set,
     * reset, and obtained as required through APIs. This attribute is used to optimize the **Swiper** performance.
     * When the rendering of child components is complex or more pages need to be preloaded, you can increase the
     * number of cached items.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: number of cached items in the adapter of **Swiper**. The value range is [0, +∞). The
     * default value is <b>1</b>. You are advised to set this parameter based on the actual service scenario to avoid
     * high memory usage.</li>
     * <li>.value[1]?.i32: whether to show cached items. The value <b>0</b> means to hide cached items, and <b>1</b>
     * means to show cached items. The default value is <b>0</b>. This parameter is supported since API version 19.</li>
     * <li>.value[2]?.i32: whether the number of cached items is calculated by group. The value <b>0</b> indicates
     * that the number of cached items is calculated by group when **NODE_SWIPER_DISPLAY_COUNT** is set to pagination
     * by group. The value <b>1</b> indicates that the actual number of cached items is used. The default value is
     * <b>0</b>. This parameter is supported since API version 24.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: number of cached items in the adapter of **Swiper**.</li>
     * <li>.value[1].i32: whether cached items are shown. The value <b>0</b> means cached items are hidden, and
     * <b>1</b> means cached items are shown. This parameter is supported since API version 19.</li>
     * <li>.value[2].i32: whether the number of cached items is calculated by group. The value <b>0</b> means the
     * number of cached items is calculated by group, and <b>1</b> means the actual number of cached items is used.
     * This parameter is supported since API version 24.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_CACHED_COUNT,

    /**
     * @brief Defines the leading margin of the **Swiper** component.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: leading margin, in vp. The value range is [0, +∞). The default value is <b>0</b>.</li>
     * <li>.value[1]?.i32: whether to ignore blank areas. The value <b>1</b> indicates to ignore blank areas, and
     * <b>0</b> indicates the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: leading margin, in vp.</li>
     * <li>.value[1].i32: whether blank areas are ignored. The value <b>1</b> indicates blank areas are ignored,
     * and <b>0</b> indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_PREV_MARGIN,

    /**
     * @brief Defines the trailing margin of the **Swiper** component.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: trailing margin, in vp. The value range is [0, +∞). The default value is <b>0</b>.</li>
     * <li>.value[1]?.i32: whether to ignore blank areas. The value <b>1</b> indicates to ignore blank areas, and
     * <b>0</b> indicates the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: trailing margin, in vp.</li>
     * <li>.value[1].i32: whether blank areas are ignored. The value <b>1</b> indicates blank areas are ignored,
     * and <b>0</b> indicates the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_NEXT_MARGIN,

    /**
     * @brief Defines the navigation indicator type of the **Swiper** component.
     * The attribute can be set, reset, and obtained as required through APIs.
     * <b>ARKUI_SWIPER_INDICATOR_TYPE_DOT</b> is applicable to scenarios such as carousel images and ad slots.
     * <b>ARKUI_SWIPER_INDICATOR_TYPE_DIGIT</b> is applicable to scenarios where the current page number needs to be
     * displayed, such as readers and galleries.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: navigation indicator type. The parameter type is {@link ArkUI_SwiperIndicatorType}.
     * The default value is <b>ARKUI_SWIPER_INDICATOR_TYPE_DOT</b>.</li>
     * <li>.object: additional configuration for the navigation indicator, depending on the type. For
     * <b>ARKUI_SWIPER_INDICATOR_TYPE_DOT</b>, the parameter type is {@link ArkUI_SwiperIndicator}.
     * For <b>ARKUI_SWIPER_INDICATOR_TYPE_DIGIT</b>, the parameter type is {@link ArkUI_SwiperDigitIndicator}.
     * {@link ArkUI_SwiperDigitIndicator} is supported since API version 19.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: navigation indicator type. The parameter type is {@link ArkUI_SwiperIndicatorType}.</li>
     * <li>.object: additional configuration for the navigation indicator, depending on the type. For
     * <b>ARKUI_SWIPER_INDICATOR_TYPE_DOT</b>, the parameter type is {@link ArkUI_SwiperIndicator}.
     * For <b>ARKUI_SWIPER_INDICATOR_TYPE_DIGIT</b>, the parameter type is {@link ArkUI_SwiperDigitIndicator}.
     * {@link ArkUI_SwiperDigitIndicator} is supported since API version 19.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_INDICATOR,

    /**
     * @brief Defines the nested scrolling mode of the **Swiper** component and its parent component. This attribute
     * can be set, reset, and obtained as required through APIs. This attribute is used when **Swiper** is nested in
     * scrollable containers such as **ScrollView** and **List**, to coordinate scrolling behavior and avoid scrolling
     * conflicts.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: nested scrolling mode of the **Swiper** component and its parent component. The parameter
     * type is {@link ArkUI_SwiperNestedScrollMode}. It takes effect only when the **Swiper** component is nested in a
     * scrollable container. The default value is <b>ARKUI_SWIPER_NESTED_SCROLL_SELF_ONLY</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: nested scrolling mode. The parameter type is {@link ArkUI_SwiperNestedScrollMode}.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_NESTED_SCROLL,

    /**
     * @brief Sets the **Swiper** component to switch to the specified page. The format of the
     * {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows. This attribute cannot be reset
     * or obtained through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: index of the target page in the Swiper component. The value range is [0, Number of pages –
     * 1].</li>
     * <li>.value[1]?.i32: whether to use an animation when the target page is reached. The value <b>1</b> indicates
     * to use the animation, and <b>0</b> indicates the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_SWIPE_TO_INDEX,

    /**
     * @brief Defines whether the navigation indicator of a component is interactive.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the navigation indicator of a component is interactive. The value <b>1</b>
     * indicates that the navigation indicator is interactive, and <b>0</b> indicates the opposite. The default value
     * is <b>1</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the navigation indicator of a component is interactive. The value <b>1</b>
     * indicates that the navigation indicator is interactive, and <b>0</b> indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_INDICATOR_INTERACTIVE,

    /**
     * @brief Defines the page flipping mode using the mouse wheel. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: page flipping mode using the mouse wheel. The parameter type is {@link ArkUI_PageFlipMode}.
     * The default value is <b>ARKUI_PAGE_FLIP_MODE_CONTINUOUS</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: page flipping mode using the mouse wheel. The parameter type is
     * {@link ArkUI_PageFlipMode}.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 15
     */
    NODE_SWIPER_PAGE_FLIP_MODE,

    /**
     * @brief Configures the **Swiper** component to automatically adjust the number of elements displayed per page
     * based on the minimum width of the elements. This attribute can be set, reset, and obtained as required through
     * APIs. This attribute is applicable to responsive layout. It is used when the number of elements displayed per
     * page needs to be automatically adjusted based on the container width, such as in landscape mode or multi-device
     * adaptation scenarios.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: minimum width of the elements, in vp. The value range is (0, +∞).</li>
     * <li>.value[1]?.i32: whether to paginate by group. The value <b>0</b> means to paginate by elements, and
     * <b>1</b> means to paginate by groups of elements displayed within the viewport. The default value is <b>0</b>.
     * </li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: minimum width of the elements, in vp.</li>
     * <li>.value[1].i32: whether pagination by group is enabled. The value <b>0</b> indicates that pagination is
     * performed by elements, and <b>1</b> indicates that pagination is performed by groups of elements displayed
     * within the viewport.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 19
     */
    NODE_SWIPER_AUTO_FILL,

    /**
     * @brief Defines whether to maintain the visible content's position when a child component is inserted or
     * deleted outside the display area of the **Swiper** component. This attribute can be used to maintain the
     * content currently displayed when a child component is dynamically added or deleted in **Swiper**, for example,
     * in the chat record list and offering list.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to maintain the visible content's position when a child component is inserted or
     * deleted outside the display area of the **Swiper** component. The value <b>1</b> indicates to maintain the
     * visible content's position, and <b>0</b> indicates the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the visible content's position is maintained when a child component is inserted or
     * deleted outside the display area of the **Swiper** component. The value <b>1</b> indicates that the visible
     * content's position is maintained, and <b>0</b> indicates the opposite.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 20
     */
    NODE_SWIPER_MAINTAIN_VISIBLE_CONTENT_POSITION = 1001023,

    /**
     * @brief Defines the responsive layout policy of the **Swiper** component, used to automatically adjust the
     * number of child component columns displayed on a page based on different breakpoint specifications. This
     * attribute can be set, reset, and obtained as required through APIs. This attribute is used to adaptively
     * adjust the number of columns displayed on each page based on different screen sizes, such as in landscape mode
     * or multi-device adaptation scenarios.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: number of columns at different breakpoint specifications. The parameter type is
     * {@link ArkUI_ItemFillPolicy}.</li>
     * <li>.value[1]?.i32: whether to paginate by group. The value <b>0</b> means to paginate by elements, and
     * <b>1</b> means to paginate by groups of elements displayed within the viewport. The default value is <b>0</b>.
     * </li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: responsive layout policy. The parameter type is {@link ArkUI_ItemFillPolicy}.</li>
     * <li>.value[1].i32: whether pagination by group is enabled. The value <b>0</b> indicates that pagination is
     * performed by elements, and <b>1</b> indicates that pagination is performed by groups of elements displayed
     * within the viewport.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 22
     */
    NODE_SWIPER_ITEMFILLPOLICY = 1001024,

    /**
     * @brief Swipe-out component of **ListItem**. This attribute can be set, reset, and obtained as required through
     * APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Construct using the {@link ArkUI_ListitemSwipeActionOption} object.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Construct using the {@link ArkUI_ListitemSwipeActionOption} object.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_ITEM_SWIPE_ACTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST_ITEM,

    /**
     * @brief Header component of **ListItemGroup**. This attribute can be set, reset, and obtained as required through
     * APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeHandle} object to be used as the header of the list item group.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeHandle} object to be used as the header of the list item group.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_ITEM_GROUP_SET_HEADER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST_ITEM_GROUP,
    /**
     * @brief Footer component of **ListItemGroup**. This attribute can be set, reset, and obtained as required through
     * APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeHandle} object used as the footer component of **ListItemGroup**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeHandle} object used as the footer component of **ListItemGroup**.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_ITEM_GROUP_SET_FOOTER,
    /**
     * @brief Style of the divider for the list items. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: Color, in 0xARGB format. The default value is **0x08000000**.</li>
     * <li>.value[1].f32: Stroke width of the divider, in vp. The default value is **0**.</li>
     * <li>.value[2].f32: Distance between the divider and the start of the list, in vp. The default value is
     * **0**.</li>
     * <li>.value[3].f32: Distance between the divider and the end of the list, in vp. The default value is
     * **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: Color, in 0xARGB format.</li>
     * <li>.value[1].f32: Stroke width of the divider, in vp.</li>
     * <li>.value[2].f32: Distance between the divider and the start of the list, in vp.</li>
     * <li>.value[3].f32: Distance between the divider and the end of the list, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_ITEM_GROUP_SET_DIVIDER,

    /**
     * @brief Default main axis size of the **ListItemGroup** child components.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: The parameter type is {@link ArkUI_ListChildrenMainSize}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: The parameter type is {@link ArkUI_ListChildrenMainSize}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_LIST_ITEM_GROUP_CHILDREN_MAIN_SIZE = 1005003,

    /**
     * @brief Adapter of the {@link ListItemGroup} component. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeAdapter} object used as the adapter.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeAdapter} object.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 15
     */
    NODE_LIST_ITEM_GROUP_NODE_ADAPTER = 1005004,

    /**
     * @brief Defines the horizontal alignment mode of child components in the column.
     * This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Horizontal alignment mode of the child components. The parameter type is
     * {@link ArkUI_HorizontalAlignment}. The value options are as follows: **START** (alignment with the start edge),
     * CENTER (center alignment), and END (alignment with the end edge). For the mapping between enumerated values and
     * numbers, see {@link ArkUI_HorizontalAlignment}. Select the corresponding alignment mode when child components
     * need to be aligned at a specific horizontal position within a **Column** container. The default value is
     * **ARKUI_HORIZONTAL_ALIGNMENT_CENTER** (center alignment).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Horizontal alignment mode of the child components. The parameter type is
     * {@link ArkUI_HorizontalAlignment}. For details about the options and their meanings, see the parameter
     * description.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_COLUMN_ALIGN_ITEMS = MAX_NODE_SCOPE_NUM * ARKUI_NODE_COLUMN,
    /**
     * @brief Vertical alignment mode of child components in the Column component. This attribute can be set, reset,
     * and obtained as required through APIs. This attribute is used when the vertical alignment mode of child
     * components in a **Column** container needs to be controlled, such as top alignment, bottom alignment, center
     * alignment, or justified alignment. This addresses the issue where the default vertical alignment mode of child
     * components in a **Column** container does not meet requirements, providing flexible vertical alignment control
     * for child components to achieve diverse vertical layout effects.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Vertical alignment mode of the child components. The parameter type is
     * {@link ArkUI_FlexAlignment}. The value options are as follows: **START** (alignment with the start edge),
     * **CENTER** (center alignment), **END** (alignment with the end edge), **SPACE_BETWEEN** (justified alignment),
     * **SPACE_AROUND** (circular alignment), and **SPACE_EVENLY** (even alignment). For the mapping between enumerated
     * values and numbers, see the definition of {@link ArkUI_FlexAlignment}. Select the corresponding alignment mode
     * when a specific distribution of child elements in the **Column** container in the vertical direction is needed.
     * The default value is **ARKUI_FLEX_ALIGNMENT_START** (alignment with the start edge).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Vertical alignment mode of the child components. The parameter type is
     * {@link ArkUI_FlexAlignment}. For details about the values and their meanings, see the parameter description.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_COLUMN_JUSTIFY_CONTENT,

    /**
     * @brief Spacing between the child components of **Column** or **Row**. This attribute can be set, reset, and
     * obtained as required through APIs. This attribute is used when the spacing between child components in a
     * **Column** or **Row** container needs to be controlled, such as the spacing between card list items or between
     * buttons. This addresses the issue where the spacing between child components in a **Column** or **Row** container
     * needs to be uniformly controlled, providing a convenient way to set spacing between child components and
     * avoiding the need to set margins for each child component individually, thereby simplifying development.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Spacing between child components, in vp. Default value: **0**. Value range: `[0, +∞)`. Set
     * this parameter when spacing is needed between child components of a **Column** or **Row** container. Setting it
     * to **0** means no spacing. When an invalid value is set, the default value is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Spacing between child components, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_LINEAR_LAYOUT_SPACE,

    /**
     * @brief Whether the child components along the main axis in **Column** or **Row** are arranged reversely. This
     * attribute can be set, reset, and obtained through APIs. This attribute is used when the arrangement order of
     * child components in a **Column** or **Row** container needs to be reversed, such as a chat message list (with
     * the latest message at the bottom) or displaying list items in reverse order. This addresses the issue where
     * child components in a **Column** or **Row** container need to be arranged in reverse, enabling a reversed
     * arrangement effect without changing the data source order, thereby simplifying development logic.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the child components along the main axis are arranged reversely. Default value: **0**
     * (false). When the value is a non-zero integer, the child components are arranged in reverse order along the main
     * axis (applicable to right-to-left or bottom-to-top layout requirements). When the value is 0, the child
     * components are arranged in normal order along the main axis (applicable to general layout). Set this parameter to
     * a non-zero value when a reverse arrangement effect is needed (such as displaying a list in reverse order);
     * otherwise, set it to **0**. When an invalid value is set, the default value is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the child components along the main axis are arranged reversely. A non-zero value
     * indicates reverse arrangement, and **0** indicates normal order.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_LINEAR_LAYOUT_REVERSE,

    /**
     * @brief Defines the vertical alignment mode of child components in the row.
     * This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Vertical alignment mode of the child components. The parameter type is
     * {@link ArkUI_VerticalAlignment}. The value options are as follows: **TOP** (top alignment), **CENTER** (center
     * alignment), and **BOTTOM** (bottom alignment). For the mapping between enumerated values and numbers, see
     * {@link ArkUI_VerticalAlignment}. Select the corresponding alignment mode when the child component needs to be
     * aligned at a specific vertical position within the **Row** container. The default value is
     * **ARKUI_VERTICAL_ALIGNMENT_CENTER** (center alignment).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Vertical alignment mode of the child components. The parameter type is
     * {@link ArkUI_VerticalAlignment}. For details about the values and their meanings, see the parameter
     * description.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_ROW_ALIGN_ITEMS = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ROW,
    /**
     * @brief Horizontal alignment mode of child components in the **Row** component. This attribute can be set, reset,
     * and obtained as required through APIs. This attribute is used when the horizontal alignment mode of child
     * components in a **Row** container needs to be controlled, such as left alignment, right alignment, center
     * distribution, or justified alignment. This addresses the issue where the default horizontal alignment mode of
     * child components in a **Row** container does not meet requirements, providing flexible horizontal alignment
     * control for child components to achieve diverse horizontal layout effects.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Horizontal alignment mode of the child components. The parameter type is
     * {@link ArkUI_FlexAlignment}. The value options are as follows: **START** (alignment with the start edge),
     * **CENTER** (center alignment), **END** (alignment with the end edge), **SPACE_BETWEEN** (justified alignment),
     * **SPACE_AROUND** (circular alignment), and **SPACE_EVENLY** (even alignment). For the mapping between enumerated
     * values and numbers, see {@link ArkUI_FlexAlignment}. Select the corresponding alignment mode when child elements
     * need a specific distribution along the horizontal axis within a **Row** container. The default value is
     * **ARKUI_FLEX_ALIGNMENT_START** (start alignment).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Horizontal alignment mode of the child components. The parameter type is
     * {@link ArkUI_FlexAlignment}. For details about the values and their meanings, see the parameter description.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_ROW_JUSTIFY_CONTENT,

    /**
     * @brief Defines the flex attribute. This attribute can be set, reset, and obtained as required through APIs.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0]?.i32: Direction in which child components are arranged within the **Flex** container. The parameter
     * type is {@link ArkUI_FlexDirection}. The value options are as follows: **ROW** (horizontal, from left to right),
     * **ROW_REVERSE** (horizontal, from right to left), **COLUMN** (vertical, from top to bottom), and
     * **COLUMN_REVERSE** (vertical, from bottom to top). For details about the mapping between enumerated values and
     * numbers, see {@link ArkUI_FlexDirection}. Select **ROW** or **ROW_REVERSE** when a horizontal layout is
     * implemented, and **COLUMN** or **COLUMN_REVERSE** when a vertical layout is implemented. The default value is
     * **ARKUI_FLEX_DIRECTION_ROW** (horizontal, from left to right). When an invalid value is set, the default value is
     * used.</li>
     * <li>.value[1]?.i32: Wrapping rule. The parameter type is {@link ArkUI_FlexWrap}. The value options are as
     * follows: **NO_WRAP** (no wrapping; child elements are compressed when they exceed the container boundary),
     * **WRAP** (forward wrapping; child elements automatically wrap when they exceed the container boundary), and
     * **WRAP_REVERSE** (reverse wrapping; the wrapping direction is opposite to that of the forward wrapping). For
     * details about the mapping between enumerated values and numbers, see {@link ArkUI_FlexWrap}. Select **NO_WRAP**
     * when child elements need to be displayed in a single row or column, and **WRAP** or **WRAP_REVERSE** when
     * automatic wrapping is required. The default value is **ARKUI_FLEX_WRAP_NO_WRAP** (no wrapping). When an invalid
     * value is set, the default value is used.</li>
     * <li>.value[2]?.i32: Alignment mode along the main axis. The parameter type is {@link ArkUI_FlexAlignment}. The
     * value options are as follows: **START** (alignment with the start edge), **CENTER** (center alignment), **END**
     * (alignment with the end edge), **SPACE_BETWEEN** (justified alignment; equal spacing between elements),
     * **SPACE_AROUND** (circular alignment; equal spacing on both sides of each element), and **SPACE_EVENLY** (even
     * alignment; equal spacing between elements and on both ends). For details about the mapping between enumerated
     * values and numbers, see {@link ArkUI_FlexAlignment}. Select the corresponding alignment mode when a specific
     * distribution of child elements on the main axis is required. The default value is **ARKUI_FLEX_ALIGNMENT_START**
     * (alignment with the start edge). When an invalid value is set, the default value is used.</li>
     * <li>.value[3]?.i32: Alignment mode along the cross axis. The parameter type is {@link ArkUI_ItemAlignment}. The
     * value options are as follows: **START** (alignment with the start edge), **CENTER** (center alignment), **END**
     * (alignment with the end edge), **STRETCH** (stretch to fill), and **BASELINE** (baseline alignment). For details
     * about the mapping between enumerated values and numbers, see {@link ArkUI_ItemAlignment}. Select the
     * corresponding alignment mode when a specific alignment of child elements on the cross axis is required. The
     * default value is **ARKUI_ITEM_ALIGNMENT_START** (alignment with the start edge). When an invalid value is set,
     * the default value is used.</li>
     * <li>.value[4]?.i32: Alignment mode for multi-line content when there is extra space in the cross axis. The
     * parameter type is {@link ArkUI_FlexAlignment}. The value options are as follows: **START** (alignment with the
     * start edge), **CENTER** (center alignment), **END** (alignment with the end edge), **SPACE_BETWEEN** (justified
     * alignment; equal spacing between lines), **SPACE_AROUND** (circular alignment; equal spacing on both sides of
     * each line), and **SPACE_EVENLY** (even alignment; equal spacing between lines and on both ends). For details
     * about the mapping between enumerated values and numbers, see {@link ArkUI_FlexAlignment}. Select the
     * corresponding alignment mode when the **Flex** container requires wrapping and the distribution of multiple lines
     * on the cross axis needs to be controlled. The default value is **ARKUI_FLEX_ALIGNMENT_START** (alignment with the
     * start edge). When an invalid value is set, the default value is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Direction in which child components are arranged within the **Flex** container. The parameter
     * type is {@link ArkUI_FlexDirection}. For details about the values and their meanings, see the parameter
     * description.</li>
     * <li>.value[1].i32: Wrapping rule. The parameter type is {@link ArkUI_FlexWrap}. For details about the values and
     * their meanings, see the parameter description.</li>
     * <li>.value[2].i32: Alignment mode along the main axis. The parameter type is {@link ArkUI_FlexAlignment}. For
     * details about the values and their meanings, see the parameter description.</li>
     * <li>.value[3].i32: Alignment mode along the cross axis. The parameter type is {@link ArkUI_ItemAlignment}. For
     * details about the values and their meanings, see the parameter description.</li>
     * <li>.value[4].i32: Alignment mode for multi-line content when there is extra space in the cross axis. The
     * parameter type is {@link ArkUI_FlexAlignment}. For details about the values and their meanings, see the parameter
     * description.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_FLEX_OPTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_FLEX,

    /**
     * @brief Spacing between the child components within the **Flex** container. This attribute can be set, reset,
     * and obtained as required through APIs. This attribute is used when the spacing between child components along
     * the main axis and cross axis directions needs to be controlled separately in a **Flex** container, such as when
     * row spacing and column spacing in a grid layout need to be set independently. This addresses the issue where
     * child components in a **Flex** container require different spacing in the main axis and cross axis, providing
     * flexible bidirectional spacing control to achieve more refined layout effects and avoiding the need to set
     * margins for each child component individually.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Spacing between the child components along the main axis of the **Flex** container, in vp.
     * Default value: **0**. Value range: `[0, +∞)`. Set this parameter to add spacing between child elements along the
     * main axis within the **Flex** container. The value **0** indicates no spacing. When an invalid value is set, the
     * default value is used.</li>
     * <li>.value[1].f32: Spacing between the child components along the cross axis of the **Flex** container, in vp.
     * Default value: **0**. Value range: `[0, +∞)`. Set this parameter to add spacing between different rows along the
     * cross axis when the **Flex** container requires wrapping. The value **0** indicates no spacing. When an invalid
     * value is set, the default value is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Spacing between the child components along the main axis of the **Flex** container, in
     * vp.</li>
     * <li>.value[1].f32: Spacing between the child components along the cross axis of the **Flex** container, in
     * vp.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_FLEX_SPACE,

    /**
     * @brief Whether the component is being refreshed. This attribute can be set and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: The parameter type is 1 or 0.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: The parameter type is 1 or 0.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_REFRESH_REFRESHING = MAX_NODE_SCOPE_NUM * ARKUI_NODE_REFRESH,
    /**
     * @brief Custom content in the pull-down area. This attribute can be set and reset as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: The parameter type is {@link ArkUI_NodeHandle}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_REFRESH_CONTENT,
    /**
     * @brief Pull-down follow ratio. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Pull-down follow ratio. Value range: [0, 1]. If a value less than 0 or greater than 1 is
     * set, the attribute setting fails.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Pull-down follow ratio. Value range: [0, 1].</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_REFRESH_PULL_DOWN_RATIO = 1009002,
    /**
     * @brief Pull-down offset that triggers refresh. This attribute can be set, reset, and obtained as required through
     * APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Pull-down offset, in vp. The default value is **64**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Pull-down offset, in vp. The default value is **64**.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_REFRESH_OFFSET = 1009003,
    /**
     * @brief Whether to initiate a refresh when the pull-down distance exceeds the value of {@link refreshOffset}. This
     * attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to trigger a refresh. **1**: yes; **0**: no. The default value is **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether a refresh is triggered. The value **1** means a refresh is triggered, and **0**
     * means the opposite.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_REFRESH_PULL_TO_REFRESH = 1009004,
    /**
     * @brief Maximum pull-down distance for refreshing. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Maximum pull-down distance, in vp. Value range: [0, +∞). Values less than 0 are treated
     * as **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Maximum pull-down distance, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 20
     */
    NODE_REFRESH_MAX_PULL_DOWN_DISTANCE = 1009005,
    /**
     * @brief Whether to enable the pull-up-to-cancel gesture for refreshing operations. This attribute can be set,
     * reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether to enable the pull-up-to-cancel gesture for refreshing operations. **0**: disable;
     * **1**: enable. The default value is **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the pull-up-to-cancel gesture is enabled for refreshing operations. **0**: The
     * pull-up-to-cancel gesture is disabled; **1**: The pull-up-to-cancel gesture is enabled.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 23
     */
    NODE_REFRESH_PULL_UP_TO_CANCEL_REFRESH = 1009006,

    /**
     * @brief Main axis direction of the **WaterFlow** component layout. This attribute can be set, reset, and obtained
     * as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: main axis direction. The parameter type is {@link ArkUI_FlexDirection}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: main axis direction. The parameter type is {@link ArkUI_FlexDirection}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_WATER_FLOW_LAYOUT_DIRECTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_WATER_FLOW,

    /**
     * @brief Number of columns in the water flow layout. If this attribute is not set, one column is used by default.
     * This attribute can be set, reset, and obtained as required through APIs. For example, **'1fr 1fr 2fr'** indicates
     * three columns, with the first column taking up 1/4 of the parent component's full width, the second column 1/4,
     * and the third column 2/4. You can use {@link columnsTemplate}('repeat(auto-fill,track-size)') to automatically
     * calculate the number of columns based on the specified column width (using **track-size**). **repeat** and
     * **auto-fill** are keywords. The units for **track-size** can be px, vp (default), %, or a valid number.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: Number of columns in the layout. The default value is **'1fr'**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: Number of columns in the layout.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_WATER_FLOW_COLUMN_TEMPLATE,

    /**
     * @brief Number of rows in the water flow layout. If this attribute is not set, one row is used by default. This
     * attribute can be set, reset, and obtained as required through APIs. For example, **'1fr 1fr 2fr'** indicates
     * three rows, with the first row taking up 1/4 of the parent component's full height, the second row 1/4, and the
     * third row 2/4. You can use {@link rowsTemplate}('repeat(auto-fill,track-size)') to automatically calculate the
     * number of rows based on the specified row height (using **track-size**). **repeat** and **auto-fill** are
     * keywords. The units for **track-size** can be px, vp (default), %, or a valid number.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: Number of rows in the layout. The default value is **'1fr'**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: Number of rows in the layout.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_WATER_FLOW_ROW_TEMPLATE,

    /**
     * @brief Gap between columns. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Gap between columns, in vp. The default value is **0**. Value range: [0, +∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Gap between columns, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_WATER_FLOW_COLUMN_GAP,

    /**
     * @brief Gap between rows. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Gap between rows, in vp. The default value is **0**. Value range: [0, +∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Gap between rows, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_WATER_FLOW_ROW_GAP,

    /**
     * @brief Water flow section configuration. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Zero-based index at which the changing starts. The value is converted to an integer.</li>
     * <li>.object: The parameter format is {@link ArkUI_WaterFlowSectionOption}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: {@link ArkUI_WaterFlowSectionOption} object.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_WATER_FLOW_SECTION_OPTION,

    /**
     * @brief Adapter of the {@link WaterFlow} component. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeAdapter} object used as the adapter.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_WATER_FLOW_NODE_ADAPTER,

    /**
     * @brief Number of cached items in the adapter of the {@link WaterFlow} component. This attribute can be set,
     * reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Number of cached items in the **WaterFlow** component's adapter.</li>
     * <li>.value[1]?.i32: Whether to show cached items. The value **0** means to hide cached items, and **1** means
     * to show cached items. The default value is **0**. This parameter is supported since API version 16.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Number of cached items in the adapter.</li>
     * <li>.value[1].i32: Whether cached items are shown. The value **0** means that cached items are hidden, and
     * **1** means that cached items are shown. This parameter is supported since API version 16.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_WATER_FLOW_CACHED_COUNT,

    /**
     * @brief Custom footer for the **WaterFlow** component.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: The parameter type is {@link ArkUI_NodeHandle}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_WATER_FLOW_FOOTER,

    /**
     * @brief Scrolls to the item with the specified index. When **smooth** is set to **true**, all passed items are
     * loaded and counted in layout calculation. This may result in performance issues if a large number of items are
     * involved.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: The index value of the target element to be slid to in the current container.</li>
     * <li>.value[1].i32: Set whether there is an action when sliding to the index value of a list item in the list,
     * where 1 indicates an action and 0 indicates no action. This parameter is optional, default value is 0.</li>
     * <li>.value[2].i32: Specify the alignment of the sliding element with the current container. The parameter type
     * is {@link ArkUI_ScrollAlignment}. This parameter is optional, default value is
     * </b>ARKUI_SCROLL_ALIGNMENT_START</b>.</li>
     * <li>.value[3].f32: Extra offset after scrolling to a specified index, in vp. This parameter is optional, the
     * default value is <b>0</b>. If value[3] is positive, it will offset further towards the bottom. If value[3] is
     * negative, it will offset further towards the top. This parameter is supported since API version 23.</li>
     * <li>.value[4]?.i32: fast scroll mode for scrolling to a specified index. The parameter type is
     * {@link OH_ArkUI_FastScrollMode}, and the default value is <b>OH_ARKUI_FAST_SCROLL_MODE_NONE</b>.
     * This parameter is valid only when .value[1].i32 is set to 1, and is supported since API version 26.2.0.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_WATER_FLOW_SCROLL_TO_INDEX,

    /**
     * @brief Size constraints to apply to water flow items, constraining the size range of the child component. This
     * attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Minimum width. Unit: vp. The value **-1** indicates that the minimum width is not set.</li>
     * <li>.value[1].f32: Maximum width. Unit: vp. The value **-1** indicates that the maximum width is not set.</li>
     * <li>.value[2].f32: Minimum height. Unit: vp. The value **-1** indicates that the minimum height is not
     * set.</li>
     * <li>.value[3].f32: Maximum height. Unit: vp. The value **-1** indicates that the maximum height is not
     * set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Minimum width, in vp. The value **-1** indicates that the minimum width is not set.</li>
     * <li>.value[1].f32: Maximum width, in vp. The value **-1** indicates that the maximum width is not set.</li>
     * <li>.value[2].f32: Minimum height, in vp. The value **-1** indicates that the minimum height is not set.</li>
     * <li>.value[3].f32: Maximum height, in vp. The value **-1** indicates that the maximum height is not set.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_WATER_FLOW_ITEM_CONSTRAINT_SIZE,

    /**
     * @brief Layout mode for the **WaterFlow** component. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Layout mode. The parameter type is {@link ArkUI_WaterFlowLayoutMode}. The default value is
     * {@link ARKUI_WATER_FLOW_LAYOUT_MODE_ALWAYS_TOP_DOWN}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Layout mode. The parameter type is {@link ArkUI_WaterFlowLayoutMode}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 18
     */
    NODE_WATER_FLOW_LAYOUT_MODE,

    /**
     * @brief Whether the **WaterFlow** component loads child nodes synchronously. This attribute can be set, reset, and
     * obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the **WaterFlow** component loads child nodes synchronously. **0**: frame-by-frame
     * loading. **1**: synchronous loading. The default value is **1**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the **WaterFlow** component loads child nodes synchronously. **0**: frame-by-frame
     * loading. **1**: synchronous loading.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 20
     */
    NODE_WATER_FLOW_SYNC_LOAD = 1010012,

    /**
     * @brief Responsive column layout policy of the **WaterFlow** component. This attribute can be set, reset, and
     * obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Number of columns at different breakpoint specifications. The parameter type is
     * {@link ArkUI_ItemFillPolicy}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Number of columns at different breakpoint specifications. The parameter type is
     * {@link ArkUI_ItemFillPolicy}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 22
     */
    NODE_WATER_FLOW_COLUMN_TEMPLATE_ITEMFILLPOLICY = 1010013,

    /**
     * @brief Whether the **WaterFlow** component supports the generation of empty branch nodes that do not contain any
     * child components using the **if/else** rendering control syntax in **LazyForEach** or **Repeat**.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Whether the **WaterFlow** component supports the generation of empty branches. **0**: no;
     * **1**: yes. The default value is **0**.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Whether the **WaterFlow** component supports the generation of empty branches. **0**: no;
     * **1**: yes.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_WATER_FLOW_SUPPORT_EMPTY_BRANCH_IN_LAZY_LOADING = 1010014,

    /**
     * @brief Set the auxiliary line in the RelativeContainer container, supporting property setting,
     * property reset and property acquisition interfaces.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Guideline in the **RelativeContainer** component. The parameter type is
     * {@link ArkUI_GuidelineOption}. Set this parameter when a guideline needs to be defined in **RelativeContainer**
     * for locating child components relative to the guideline. No guideline is set when this parameter is not
     * passed.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Guideline in the **RelativeContainer** component. The parameter type is
     * {@link ArkUI_GuidelineOption}. If no guideline is set, **NULL** is returned.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_RELATIVE_CONTAINER_GUIDE_LINE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_RELATIVE_CONTAINER,

    /**
     * @brief Barrier in the **RelativeContainer** component. This attribute can be set, reset, and obtained as
     * required through APIs. This attribute is used when barriers need to be created in a **RelativeContainer**
     * container to constrain the positions of child components, such as ensuring that a component is always
     * positioned to the left or right of other components. This addresses the issue where dynamic constraint
     * boundaries need to be created based on the positions of other components in a **RelativeContainer** container,
     * providing barrier capabilities to implement more flexible relative layout constraints and meet complex UI
     * layout requirements.
     * The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Barrier in the **RelativeContainer** component. The parameter type is {@link ArkUI_BarrierOption}.
     * Set this parameter when a barrier needs to be defined in **RelativeContainer** to constrain the layout boundaries
     * of child components. No barrier is set when this parameter is not passed.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Barrier in the **RelativeContainer** component. The parameter type is {@link ArkUI_BarrierOption}.
     * When no barrier is set, **NULL** is returned.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_RELATIVE_CONTAINER_BARRIER,

    /**
     * @brief Number of columns in the **Grid** component. If this attribute is not set, one column is used by default.
     * This attribute can be set, reset, and obtained as required through APIs. For example, **'1fr 1fr 2fr'** indicates
     * three columns, with the first column taking up 1/4 of the parent component's full width, the second column 1/4,
     * and the third column 2/4. You can use {@link columnsTemplate}('repeat(auto-fill,track-size)') to automatically
     * calculate the number of columns based on the specified column width (using **track-size**). **repeat** and
     * **auto-fill** are keywords. The units for **track-size** can be px, vp (default), %, or a valid number.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: Number of columns in the layout.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: Number of columns in the layout.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_GRID_COLUMN_TEMPLATE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_GRID,

    /**
     * @brief Number of rows or the minimum row height in the **Grid** component. If this parameter is not set, one row
     * is used by default. This attribute can be set, reset, and obtained as required through APIs. For example, **'1fr
     * 1fr 2fr'** indicates three rows, with the first row taking up 1/4 of the parent component's full height, the
     * second row 1/4, and the third row 2/4. You can use {@link rowsTemplate}('repeat(auto-fill,track-size)') to
     * automatically calculate the number of rows based on the specified row height (using **track-size**). **repeat**
     * and **auto-fill** are keywords. The units for **track-size** can be px, vp (default), %, or a valid number.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: Number of rows in the layout.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: Number of rows in the layout.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_GRID_ROW_TEMPLATE,

    /**
     * @brief Gap between columns. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Gap between columns, in vp. The default value is **0**. Value range: [0, +∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Gap between columns, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_GRID_COLUMN_GAP,

    /**
     * @brief Gap between rows. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Gap between rows, in vp. The default value is **0**. Value range: [0, +∞).</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Gap between rows, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_GRID_ROW_GAP,

    /**
     * @brief Adapter of the {@link Grid} component. This attribute can be set, reset, and obtained as required through
     * APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeAdapter} object used as the adapter.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_GRID_NODE_ADAPTER,

    /**
     * @brief Number of cached items in the adapter of the {@link Grid} component. This attribute can be set, reset, and
     * obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: Number of cached items of {@link ArkUI_NodeAdapter}, which is used with the **Grid**
     * component.</li>
     * <li>.value[1].i32: Whether to show cached items. The value **0** means to hide cached items, and **1** means
     * to show cached items. This parameter is optional. The default value is **0**. This parameter is supported
     * since API version 26.0.0.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: Number of cached items in the **Grid** component adapter.</li>
     * <li>.value[1].i32: Whether cached items are shown. The value **0** means that cached items are hidden, and
     * **1** means that cached items are shown. This parameter is supported since API version 26.0.0.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     */
    NODE_GRID_CACHED_COUNT,

    /**
     * @brief Focus wrap mode of the {@link Grid} component. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: focus wrap mode of the <b>Grid</b> component. The parameter type is
     * {@link ArkUI_FocusWrapMode}. The default value is <b>ARKUI_FOCUS_WRAP_MODE_DEFAULT</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: focus wrap mode of the <b>Grid</b> component. The parameter type is
     * {@link ArkUI_FocusWrapMode}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 20
     */
    NODE_GRID_FOCUS_WRAP_MODE = 1013006,

    /**
     * @brief Whether the {@link Grid} component synchronously loads child nodes. This attribute can be set, reset, and
     * obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the <b>Grid</b> component loads child nodes synchronously. <b>0</b>: frame-by-frame
     * loading. <b>1</b>: synchronous loading. The default value is <b>1</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the <b>Grid</b> component loads child nodes synchronously. <b>0</b>: frame-by-frame
     * loading. <b>1</b>: synchronous loading.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 20
     */
    NODE_GRID_SYNC_LOAD = 1013007,

    /**
     * @brief Alignment mode of {@link GridItem} in **Grid**. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: alignment mode of <b>GridItem</b> in <b>Grid</b>. The parameter type is
     * {@link ArkUI_GridItemAlignment}. The default value is <b>ARKUI_GRID_ITEM_ALIGNMENT_DEFAULT</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: alignment mode of <b>GridItem</b> in <b>Grid</b>. The parameter type is
     * {@link ArkUI_GridItemAlignment}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 22
     */
    NODE_GRID_ALIGN_ITEMS = 1013008,

    /**
     * @brief Layout options of **Grid**. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: layout options of <b>Grid</b>. The parameter type is {@link ArkUI_GridLayoutOptions}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: {@link ArkUI_GridLayoutOptions} object.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 22
     */
    NODE_GRID_LAYOUT_OPTIONS = 1013009,

    /**
     * @brief Responsive column layout policy of the **Grid** component. This attribute can be set, reset, and obtained
     * as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: number of columns at different breakpoint specifications. The parameter type is
     * {@link ArkUI_ItemFillPolicy}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: number of columns at different breakpoint specifications. The parameter type is
     * {@link ArkUI_ItemFillPolicy}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 22
     */
    NODE_GRID_COLUMN_TEMPLATE_ITEMFILLPOLICY = 1013010,

    /**
     * @brief Whether the **Grid** component enters the editing mode. After the component enters the editing mode, you
     * can drag **GridItem** by using the **NODE_GRID_ON_ITEM_DRAG_START** event. This attribute can be set, reset, and
     * obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the <b>Grid</b> component enters the editing mode. <b>0</b>: The component does not
     * enter the editing mode. <b>1</b>: The component enters the editing mode. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the <b>Grid</b> component enters the editing mode. <b>0</b>: The component does not
     * enter the editing mode. <b>1</b>: The component enters the editing mode.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 23
     */
    NODE_GRID_EDIT_MODE = 1013011,

    /**
     * @brief Whether to enable the drag animation for **GridItem** in the **Grid** component. This attribute can be
     * set, reset, and obtained as required through APIs.
     * <br>The animation is supported only when the scrolling mode is used (only one of **NODE_GRID_ROW_TEMPLATE** and
     * **NODE_GRID_COLUMN_TEMPLATE** is set).
     * <br>Drag animations are only supported in grids with fixed size rules; scenarios involving spanning across rows
     * or columns are not supported.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable the drag animation for <b>GridItem</b> in the <b>Grid</b> component.
     * <b>0</b>: disable. <b>1</b>: enable. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the drag animation is enabled for <b>GridItem</b> in the <b>Grid</b> component.
     * <b>0</b>: disabled. <b>1</b>: enabled.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 23
     */
    NODE_GRID_DRAG_ANIMATION = 1013012,

    /**
     * @brief Whether to enable mouse-based multi-selection for the **Grid** component. This attribute can be set,
     * reset, and obtained as required through APIs.
     * <br>After enabled, mouse-based multi-selection within the grid will trigger the {@link NODE_GRID_ITEM_ON_SELECT}
     * event of the grid item.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable mouse-based multi-selection for the <b>Grid</b> component. <b>0</b>:
     * disable. <b>1</b>: enable. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether mouse-based multi-selection is enabled for the <b>Grid</b> component. <b>0</b>:
     * disabled. <b>1</b>: enabled.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 23
     */
    NODE_GRID_MULTI_SELECTABLE = 1013013,

    /**
     * @brief Scrolls to the item with the specified index.
     * <br>When the animation is enabled, all passed child components are loaded and counted in layout calculation. This
     * may result in performance issues if a large number of child components are involved.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: index value of the target element to be slid to in the current container.</li>
     * <li>.value[1].i32: whether there is an animation when sliding to the target element, where 1 indicates an
     * animation and 0 indicates no animation. This parameter is optional. Default value: <b>0</b>.</li>
     * <li>.value[2].i32: alignment of the target element with the current container. The parameter type is
     * {@link ArkUI_ScrollAlignment}. This parameter is optional. The default value is
     * <b>ARKUI_SCROLL_ALIGNMENT_AUTO</b>.</li>
     * <li>.value[3].f32: extra offset after scrolling to a specified index, in vp. This parameter is optional. The
     * default value is <b>0</b>. If value[3] is positive, it will offset further towards the bottom. If value[3] is
     * negative, it will offset further towards the top.</li>
     * <li>.value[4]?.i32: fast scroll mode for scrolling to a specified index. The parameter type is
     * {@link OH_ArkUI_FastScrollMode}, and the default value is <b>OH_ARKUI_FAST_SCROLL_MODE_NONE</b>.
     * This parameter is valid only when .value[1].i32 is set to 1, and is supported since API version 26.2.0.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 23
     */
    NODE_GRID_SCROLL_TO_INDEX = 1013014,

    /**
     * @brief Whether the **Grid** component supports the generation of empty branch nodes that do not contain any child
     * components using the **if/else** rendering control syntax in **LazyForEach** or **Repeat**.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the <b>Grid</b> component supports the generation of empty branches. <b>0</b>: no.
     * <b>1</b>: yes. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the <b>Grid</b> component supports the generation of empty branches. <b>0</b>: no.
     * <b>1</b>: yes.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 23
     */
    NODE_GRID_SUPPORT_EMPTY_BRANCH_IN_LAZY_LOADING = 1013015,

    /**
     * @brief Whether to enable the edit mode for the **Grid** component. After the edit mode is enabled, the check box
     * is displayed by default, and users can swipe with their fingers to select multiple items. This attribute can be
     * set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable the edit mode for the <b>Grid</b> component. <b>0</b>: disable.
     * <b>1</b>: enable. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the edit mode is enabled for the <b>Grid</b> component. <b>0</b>: disabled.
     * <b>1</b>: enabled.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_GRID_ENABLE_EDIT_MODE = 1013016,

    /**
     * @brief Edit mode options of the **Grid** component. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to use the default multi-selection style for the <b>Grid</b> component. <b>0</b>:
     * no. <b>1</b>: yes. The default value is <b>1</b>.</li>
     * <li>.value[1].i32: whether to enable two-finger swipe to select multiple items for the <b>Grid</b> component.
     * <b>0</b>: disable. <b>1</b>: enable. The default value is <b>1</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the default multi-selection style is used for the <b>Grid</b> component. <b>0</b>:
     * no. <b>1</b>: yes.</li>
     * <li>.value[1].i32: whether two-finger swipe is enabled to select multiple items for the <b>Grid</b> component.
     * <b>0</b>: disabled. <b>1</b>: enabled.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_GRID_EDIT_MODE_OPTIONS = 1013017,

    /**
     * @brief Style for **GridItem**. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: style of the <b>GridItem</b> component, specified using {@link ArkUI_GridItemStyle}. The
     * default value is <b>GRID_ITEM_STYLE_NONE</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: style of the <b>GridItem</b> component, specified using {@link ArkUI_GridItemStyle}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 22
     */
    NODE_GRID_ITEM_STYLE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_GRID_ITEM,

    /**
     * @brief Whether **GridItem** can be selected using mouse-based multi-selection. This attribute can be set, reset,
     * and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether <b>GridItem</b> can be selected using mouse-based multi-selection. <b>0</b>: not
     * selectable. <b>1</b>: selectable. The default value is <b>1</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether <b>GridItem</b> can be selected using mouse-based multi-selection. <b>0</b>: not
     * selectable. <b>1</b>: selectable.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 23
     */
    NODE_GRID_ITEM_SELECTABLE = 1014001,

    /**
     * @brief Selection status of **GridItem**. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: selection status of <b>GridItem</b>. <b>0</b>: not selected. <b>1</b>: selected. The
     * default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: selection status of <b>GridItem</b>. <b>0</b>: not selected. <b>1</b>: selected.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 23
     */
    NODE_GRID_ITEM_SELECTED = 1014002,

    /**
     * @brief Width of each column in the picker. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: width of the first column, specified as a percentage of the total width. By default,
     * all columns have equal widths. When not set, the columns are evenly divided.</li>
     * <li>.value[1]?.f32: width of the second column, specified as a percentage of the total width. By default,
     * all columns have equal widths.</li>
     * <li>.value[2]?.f32: width of the third column, specified as a percentage of the total width. By default,
     * all columns have equal widths.</li>
     * <li>...</li>
     * <li>.value[n]?.f32: width of the (n+1)-th column, specified as a percentage of the total width. By
     * default, all columns have equal widths.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: width of the first column, specified as a percentage of the total width.</li>
     * <li>.value[1].f32: width of the second column, specified as a percentage of the total width.</li>
     * <li>.value[2].f32: width of the third column, as a percentage of the total width.</li>
     * <li>...</li>
     * <li>.value[n].f32: width of the (n+1)-th column, specified as a percentage of the total width.</li>
     * </ul>
     *
     * @ingroup Textpicker
     * @since 18
     */
    NODE_TEXT_PICKER_COLUMN_WIDTHS = 15009,
    /**
     * @brief Disabled date ranges of the calendar picker. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.string: string representing the disabled date ranges. The format is "start_date,end_date" for each
     * range, with multiple ranges separated by commas (,).<br>
     * Format of the disabled date range: "1910-01-01,1910-12-31,2020-01-01,2020-12-31". Default value: empty
     * string, indicating that no disabled date range is set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.string: string representing the disabled date ranges. The format is "start_date,end_date" for each
     * range, with multiple ranges separated by commas (,), for example,
     * <b>"1910-01-01,1910-12-31"</b>.</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     * @since 19
     */
    NODE_CALENDAR_PICKER_DISABLED_DATE_RANGE = 16006,

    /**
     * @brief Whether to highlight the current system date in the calendar picker. This attribute can be set,
     * reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to highlight the current system date in the calendar picker. <b>1</b> to
     * highlight; <b>0</b> otherwise.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the current system date is highlighted in the calendar picker.</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     * @since 19
     */
    NODE_CALENDAR_PICKER_MARK_TODAY = 16007,

    /**
     * @brief Defines the want used to start EmbeddedUIExtensionAbility.
     * This attribute can be set as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: The want of EmbeddedComponent, with parameter type {@AbilityBase_Want}.</li>
     * <li>The default value is <b>nullptr</b>.</li>
     * </ul>
     *
     * @ingroup EmbeddedComponent
     * @since 20
     */
    NODE_EMBEDDED_COMPONENT_WANT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_EMBEDDED_COMPONENT,

    /**
     * @brief Runtime option of **EmbeddedComponent**, which is used to control the UI display behavior of the
     * EmbeddedAbility. This attribute can be set.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: List of options for **EmbeddedComponent**. The parameter type is
     * {@link ArkUI_EmbeddedComponentOption}. The default value is **nullptr**.</li>
     * </ul>
     *
     * @ingroup EmbeddedComponent
     * @since 20
     */
    NODE_EMBEDDED_COMPONENT_OPTION,

    /**
     * @brief Defines the index of the default selected item in the data selection range of the picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: index.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: index.</li>
     * </ul>
     *
     * @ingroup Picker
     * @since 23
     */
    NODE_PICKER_OPTION_SELECTED_INDEX = MAX_NODE_SCOPE_NUM * ARKUI_NODE_PICKER,
    /**
     * @brief Defines whether to enable haptic feedback. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable haptic feedback. <b>1</b> indicates to enable, and <b>0</b>
     * indicates opposite. Default value: <b>1</b>. When enabled, whether haptic feedback exists depends on the
     * hardware support of the system.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether haptic feedback is enabled. <b>1</b> indicates enabled, and <b>0</b> indicates
     * the opposite. Whether haptic feedback exists depends on the hardware support of the system.</li>
     * </ul>
     *
     * @ingroup Picker
     * @since 23
     */
    NODE_PICKER_ENABLE_HAPTIC_FEEDBACK = 1018001,
    /**
     * @brief Whether the picker supports looping. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Use scenario: Looping is suitable for scenarios with limited options where a quick selection experience
     * is desired (such as gender selection). Non-looping is suitable for scenarios where options have clear
     * boundaries and the user selection range needs to be restricted.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the picker supports looping. <b>1</b> to support; <b>0</b> otherwise. The
     * default value is <b>1</b>.<br>
     * If the number of child components is less than 8, looping will not occur regardless of whether the value
     * is <b>1</b> or <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the picker supports looping. <b>1</b> indicates that scrolling is supported;
     * <b>0</b> indicates that scrolling is not supported.</li>
     * </ul>
     *
     * @ingroup Picker
     * @since 23
     */
    NODE_PICKER_CAN_LOOP = 1018002,
    /**
     * @brief Picker indicator style. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: picker indicator style. The parameter type is {@link ArkUI_PickerIndicatorStyle}. Default
     * value:<br>
     * {<br>
     * type: PickerIndicatorType.BACKGROUND,<br>
     * borderRadius: {<br>
     * value:12,<br>
     * unit:LengthUnit.vp<br>
     * },<br>
     * backgroundColor: 'sys.color.comp_background_tertiary'<br>
     * }<br>
     * When not set, the default value is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: picker indicator style. The parameter type is {@link ArkUI_PickerIndicatorStyle}.</li>
     * </ul>
     *
     * @ingroup Picker
     * @since 23
     */
    NODE_PICKER_SELECTION_INDICATOR = 1018003,

    /**
     * @brief Crown sensitivity of the **ArcList** component, which can be set, reset, and obtained as required through
     * APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: digital crown sensitivity type. The parameter type is {@link ArkUI_CrownSensitivity}. Default
     * value: ARKUI_CROWN_SENSITIVITY_MEDIUM</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: digital crown sensitivity type. The parameter type is {@link ArkUI_CrownSensitivity}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_DIGITAL_CROWN_SENSITIVITY = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_LIST,

    /**
     * @brief Spacing between the **ArcList** child components in the main axis direction. This attribute can be set,
     * reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: spacing between the child components in the main axis direction, in vp. The default value
     * is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: spacing between the child components in the main axis direction, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_SPACE = 1019001,

    /**
     * @brief Number of cached items of the **ArcList** component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: number of cached items.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: number of cached items.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_CACHED_COUNT = 1019002,

    /**
     * @brief Scrolls to the list item corresponding to a specified index value. When the animation is enabled, all
     * passed list items are loaded and counted in layout calculation. This may result in performance issues if a large
     * number of list items are involved.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: index of the item to be scrolled to in the container. If the value is <b>-1</b>, the last
     * item in the container is scrolled to.</li>
     * <li>.value[1]?.i32: whether there is an animation effect when the list item corresponding to the specified
     * index value is scrolled to. The value <b>1</b> indicates there is an animation effect, and <b>0</b> indicates
     * the opposite. The default value is <b>0</b>.</li>
     * <li>.value[2]?.i32: how the list item to scroll to is aligned with the container. The parameter type is
     * {@link ArkUI_ScrollAlignment}. The default value is <b>ARKUI_SCROLL_ALIGNMENT_START</b>.</li>
     * <li>.value[3]?.f32: extra offset, in vp. The default value is <b>0</b>. A positive number indicates an extra
     * offset toward the end, and a negative number indicates an extra offset toward the start.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_SCROLL_TO_INDEX = 1019003,

    /**
     * @brief Whether to enable the chain animation effect for the **ArcList** component. This attribute can be set,
     * reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable the chain animation effect. The value <b>1</b> means to enable, and
     * <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the chain animation effect is enabled. The value <b>1</b> means the chain animation
     * effect is enabled, and <b>0</b> means the opposite.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_CHAIN_ANIMATION = 1019004,

    /**
     * @brief Default main axis size of the **ArcList** child component. The attribute can be set and reset through
     * APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: default main axis size of the <b>ArcList</b> child component. The parameter format is
     * {@link ArkUI_ListChildrenMainSize}. This parameter defines the main axis sizes of all child items in
     * <b>ArcList</b>.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_CHILDREN_MAIN_SIZE = 1019005,

    /**
     * @brief Header component of **ArcList**. This attribute can be set, reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeHandle} object used as the header component of <b>ArcList</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeHandle} object used as the header component of <b>ArcList</b>.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_SET_HEADER = 1019006,

    /**
     * @brief Scroll bar display mode of the **ArcList** component. This attribute can be set, reset, and obtained as
     * required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: scrollbar display mode. The parameter type is {@link ArkUI_ScrollBarDisplayMode}. The
     * default value is <b>ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: scrollbar display mode. The parameter type is {@link ArkUI_ScrollBarDisplayMode}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_SCROLL_BAR = 1019007,

    /**
     * @brief Scroll bar color of the **ArcList** component. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.data[0].u32: color of the scrollbar, in 0xARGB format. The default value is <b>0x66182431</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.data[0].u32: color of the scrollbar, in 0xARGB format.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_SCROLL_BAR_COLOR = 1019008,

    /**
     * @brief Scroll bar width of the **ArcList** component. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: width of the scrollbar, in vp. The default value is <b>4</b>. Value range: [0, +∞). If
     * set to a value less than 0, the default value is used. If set to <b>0</b>, the scrollbar is not displayed.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: width of the scrollbar, in vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_SCROLL_BAR_WIDTH = 1019009,

    /**
     * @brief Whether the **ArcList** component supports scroll gestures. This attribute can be set, reset, and obtained
     * as required through APIs. The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and
     * the format of the return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to support scroll gestures. The default value is <b>1</b>. The value <b>1</b> means
     * to support, and <b>0</b> means the opposite.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether scroll gestures are supported. The value <b>1</b> means scroll gestures are
     * supported, and <b>0</b> means the opposite.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_ENABLE_SCROLL_INTERACTION = 1019010,

    /**
     * @brief Edge fade effect of the **ArcList** component. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable the edge fade effect. <b>0</b>: Disable the edge fade effect. <b>1</b>:
     * Enable the edge fade effect. The default value is <b>0</b>.</li>
     * <li>.value[1]?.f32: length of the edge fade effect. The unit is vp. The default value is <b>32</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the edge fade effect is enabled. <b>0</b>: The edge fade effect is disabled.
     * <b>1</b>: The edge fade effect is enabled.</li>
     * <li>.value[1].f32: length of the edge fade effect. The unit is vp.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_FADING_EDGE = 1019011,

    /**
     * @brief Friction coefficient of the **ArcList** component, which can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: friction coefficient. The default value is <b>0.8</b>. Value range: (0, +∞). If this
     * parameter is set to a value less than or equal to 0, the default value is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: friction coefficient.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_FRICTION = 1019012,

    /**
     * @brief Maximum initial speed of the fling animation in the **ArcList** component. This attribute can be set,
     * reset, and obtained as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: maximum initial velocity at the start of the fling animation, in vp/s. The default value is
     * <b>9000</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: maximum initial velocity at the start of the fling animation, in vp/s.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_FLING_SPEED_LIMIT = 1019013,

    /**
     * @brief Whether to enable automatic scaling for **ArcListItem**. This attribute can be set, reset, and obtained as
     * required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable auto scale. Value 0 means not to enable, and value 1 means to enable.
     * Default value: 1.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to enable auto scale.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_ITEM_AUTO_SCALE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_LIST_ITEM,

    /**
     * @brief Swipe-out component of **ArcListItem**. This attribute can be set and reset as required through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute is as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: {@link ArkUI_ListItemSwipeActionOption} object. This parameter defines the swipe-out component
     * information of <b>ArcListItem</b>.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_LIST_ITEM_SWIPE_ACTION = 1020001,

    /**
     * @brief Scrollable component bound to **ArcScrollBar**. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: use {@link ArkUI_NodeHandle} object as the scrollable component bound by the scroll bar.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: use {@link ArkUI_NodeHandle} object as the scrollable component bound by the scroll bar.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_SCROLL_BAR_BIND_SCROLLABLE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_SCROLL_BAR,

    /**
     * @brief Scroll bar display mode of **ArcScrollBar**. This attribute can be set, reset, and obtained as required
     * through APIs.
     * <br>The format of the {@link ArkUI_AttributeItem} parameter for setting the attribute and the format of the
     * return value **ArkUI_AttributeItem** are as follows.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: scrollbar display mode. The parameter type is {@link ArkUI_ScrollBarDisplayMode}. The
     * default value is <b>ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: scrollbar display mode. The parameter type is {@link ArkUI_ScrollBarDisplayMode}.</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component
     * @since 26.0.0
     */
    NODE_ARC_SCROLL_BAR_DISPLAY_MODE = 1021001,

    /**
     * @brief Number of displayed items in the <b>Picker</b> container. The semantics is the same as that of
     * {@link displayedItemCount} in {@link UIPickerComponent} on the ArkTS side. If this attribute is not set,
     * the value <b>7</b> is used. When <b>Picker</b> is in a three-dimensional wheel style, all items except the
     * selected ones rotate at an angle, and the actual visible height is less than the item line height. To
     * increase the number of visible lines or the line height, increase the container height accordingly. For
     * details, see {@link UIPickerComponent}. This attribute can be set, reset, and obtained as required through
     * APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: number of displayed items. The value is an integer within the range of [2, 9]. If a
     * number with a decimal is passed, it is rounded down. If an even number is passed, it is rounded up to the
     * nearest odd number (for example, 2 becomes 3 and 8 becomes 9). If a number is not within the range, the
     * default value <b>7</b> is used.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: number of displayed items in the <b>Picker</b> container, which is an integer in the
     * range [2, 9].</li>
     * </ul>
     *
     * @since 26.0.0
     */
    NODE_PICKER_DISPLAYED_ITEM_COUNT = 1018004,

    /**
     * @brief Height of each item in the <b>Picker</b> container. The semantics is the same as that of
     * {@link itemHeight} in {@link UIPickerComponent} on the ArkTS side. If this attribute is not set, the
     * height of each item is 40 vp. C APIs pass the height value in vp. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: item height, in vp. The valid range is [40, 64]. If the value is less than 40 vp or
     * greater than 64 vp, the default value <b>40</b> vp is used. The value cannot be in percentage.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: item height, in vp.</li>
     * </ul>
     *
     * @since 26.0.0
     */
    NODE_PICKER_ITEM_HEIGHT = 1018005,

    /**
     * @brief Defines the index of the child component currently displayed in the ArcSwiper.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: index value of the child component. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: index value of the child component.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_SWIPER_INDEX = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_SWIPER,

    /**
     * @brief Defines the navigation dot indicator of the **ArcSwiper** component.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to display the navigation dot indicator. The value <b>1</b> indicates to display,
     * and <b>0</b> indicates the opposite. The default value is <b>1</b>.</li>
     * <li>.value[1].i32: direction of the **ArcSwiper** navigation dot indicator. The parameter type is
     * {@link OH_ArkUI_ArcDirection}. The default value is <b>OH_ARKUI_ARCDIRECTION_SIX_CLOCK_DIRECTION</b>. This is
     * an optional parameter.</li>
     * <li>.value[2].i32: color of the unselected dot, in 0xARGB format. The default value is <b>0xA9FFFFFF</b>,
     * which indicates white. This is an optional parameter.</li>
     * <li>.value[3].i32: color of the selected dot, in 0xARGB format. The default value is <b>0xFF5EA1FF</b>, which
     * indicates blue. This is an optional parameter.</li>
     * <li>.value[4].i32: background color of the **ArcSwiper** navigation dot indicator after a long press, in
     * 0xARGB format. The default value is <b>0xFF5EA1FF</b>, which indicates blue. This is an optional parameter.
     * </li>
     * <li>.object: gradient color of the mask. This is an optional parameter. In a color stop array, each color
     * stop consists of a color and its stop. The parameter type is {@link ArkUI_ColorStop}. Invalid colors are
     * automatically skipped. <b>colors</b>: color of the color stop. <b>stops</b>: stop of the color.
     * <b>size</b>: number of colors.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the navigation dot indicator is displayed.</li>
     * <li>.value[1].i32: direction of the **ArcSwiper** navigation dot indicator.</li>
     * <li>.value[2].u32: color of the unselected dot.</li>
     * <li>.value[3].u32: color of the selected dot.</li>
     * <li>.value[4].u32: background color of the **ArcSwiper** navigation dot indicator after a long press.</li>
     * <li>.object: gradient color of the mask.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     *
     */
    NODE_ARC_SWIPER_INDICATOR,

    /**
     * @brief Defines the animation duration for child component switching.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: animation duration for child component switching, in milliseconds. The value range is
     * [0, +∞). When not set, the default value is <b>400</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: animation duration for child component switching, in milliseconds.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_SWIPER_DURATION,

    /**
     * @brief Defines whether to use vertical swiping.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to use vertical swiping. The value <b>1</b> indicates to use vertical swiping,
     * and <b>0</b> indicates to use horizontal swiping. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether vertical swiping is used.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_SWIPER_VERTICAL,

    /**
     * @brief Whether to disable swiping. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to disable the swipe feature. The value <b>1</b> means to disable
     * the swipe feature, and <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to disable the swipe feature.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_SWIPER_DISABLE_SWIPE,

    /**
     * @brief Sensitivity of rotating the digital crown. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: the sensitivity of rotating crown. The parameter type is {@link ArkUI_CrownSensitivity}.
     * The default value is <b>ARKUI_CROWN_SENSITIVITY_MEDIUM</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: the sensitivity of rotating crown.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_SWIPER_DIGITAL_CROWN_SENSITIVITY,

    /**
     * @brief Edge swipe effect of the **ArcSwiper** component when swiping to the boundary of the scrollable content.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: effect used at the edges of the swiper when the boundary of the scrollable content is reached.
     * The parameter type is {@link ArkUI_EdgeEffect}.
     * The default value is <b>ARKUI_EDGE_EFFECT_SPRING</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: effect used at the edges of the swiper when the boundary of the scrollable content is reached.
     * The parameter type is {@link ArkUI_EdgeEffect}.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_SWIPER_EFFECT_MODE,

    /**
     * @brief Whether to disable the transition animation. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to disable the transition animation. The value <b>1</b> means to disable
     * the transition animation, and <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to disable the transition animation.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_SWIPER_DISABLE_TRANSITION_ANIMATION,
} ArkUI_NodeAttributeType;

/**
 * @brief Define component event max args size.
 *
 * @since 12
 */
#define MAX_COMPONENT_EVENT_ARG_NUM 12
/**
 * @brief Defines the parameter type of a component callback event, which is used to pass event-related data when the
 * component callback is triggered, so that the application can obtain the callback event parameters.
 *
 * @since 12
 */
typedef struct {
    /** Data array object. */
    ArkUI_NumberValue data[MAX_COMPONENT_EVENT_ARG_NUM];
} ArkUI_NodeComponentEvent;

/**
 * @brief Defines the type of string parameters used in component callback events. This struct is used to pass string
 * data in the asynchronous event callback of a component. It is applicable to scenarios where the component callback
 * event needs to carry text information.
 *
 * @since 12
 */
typedef struct {
    /** String. */
    const char* pStr;
} ArkUI_StringAsyncEvent;

/**
 * @brief Defines a text change event, which is used to listen to and handle text change events in text input
 * scenarios. This struct contains the text content, extended information, and numeric parameters. It allows you to
 * obtain text change data in real time, making it suitable for scenarios such as listening to text box content,
 * real-time search, and word count.
 *
 * @since 15
 */
typedef struct {
    /** String data */
    const char* pStr;
    /** Extended string data */
    const char* pExtendStr;
    /** Numeric data */
    int32_t number;
} ArkUI_TextChangeEvent;

/**
 * @brief Defines a text content change event of the **TextEditor** component.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorChangeEvent OH_ArkUI_TextEditorChangeEvent;

/**
 * @brief Enumerates the event types supported by the NativeNode component.
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief Defines the gesture event type.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}.
     *
     * @ingroup Interaction Event
     */
    NODE_TOUCH_EVENT = 0,

    /**
     * @brief Mount event. This event is triggered when the component is mounted and displayed. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Interaction Event
     */
    NODE_EVENT_ON_APPEAR,
    /**
     * @brief Unmount event. This event is triggered when the component is unmounted from the component tree and
     * disappears. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Interaction Event
     */
    NODE_EVENT_ON_DISAPPEAR,

    /**
     * @brief Component area change event. This event is triggered when the component area changes. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     *  {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains 12 parameters:\n
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].f32</b>: original width of the target element, in vp.
     * The value type is number.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32</b>: original height of the target element, in vp.
     * The value type is number.</li>
     * <li>ArkUI_NodeComponentEvent.data[2].f32</b>: original X coordinate of the target element's upper left corner
     * relative to the parent element's, in vp. The value type is number.</li>
     * <li>ArkUI_NodeComponentEvent.data[3].f32</b>: original Y coordinate of the target element's upper left corner
     * relative to the parent element's, in vp. The value type is number.</li>
     * <li>ArkUI_NodeComponentEvent.data[4].f32</b>: original X coordinate of the target element's upper left corner
     * relative to the page's, in vp. The value type is number.</li>
     * <li>ArkUI_NodeComponentEvent.data[5].f32</b>: original Y coordinate of the target element's upper left corner
     * relative to the page's, in vp. The value type is number.</li>
     * <li>ArkUI_NodeComponentEvent.data[6].f32</b>: new width of the target element, in vp.
     * The value is a number.</li>
     * <li>ArkUI_NodeComponentEvent.data[7].f32</b>: new height of the target element, in vp.
     * The value is a number.</li>
     * <li>ArkUI_NodeComponentEvent.data[8].f32</b>: new X coordinate of the target element's upper left corner
     * relative to the parent element's, in vp. The value type is number.</li>
     * <li>ArkUI_NodeComponentEvent.data[9].f32</b>: new Y coordinate of the target element's upper left corner
     * relative to the parent element's, in vp. The value type is number.</li>
     * <li>ArkUI_NodeComponentEvent.data[10].f32</b>: new X coordinate of the target element's upper left corner
     * relative to the page's, in vp. The value type is number.</li>
     * <li>ArkUI_NodeComponentEvent.data[11].f32</b>: new Y coordinate of the target element's upper left corner
     * relative to the page's, in vp. The value type is number.</li>
     * </ul>
     *
     * @ingroup Interaction Event
     */
    NODE_EVENT_ON_AREA_CHANGE,
    /**
     * @brief Event of obtaining focus. This event is triggered when the component obtains the focus. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Interaction Event
     */
    NODE_ON_FOCUS,
    /**
     * @brief Event of losing focus. This event is triggered when the component loses the focus. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Interaction Event
     */
    NODE_ON_BLUR,
    /**
     * @brief Click event. This event is triggered when the component is clicked. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains 12 parameters:\n
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].f32</b>: X coordinate of the click relative to the upper left corner of the
     * clicked component's original area, in vp.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32</b>: Y coordinate of the click relative to the upper left corner of the
     * clicked component's original area, in vp.</li>
     * <li>ArkUI_NodeComponentEvent.data[2].f32</b>: event timestamp. It is the interval between the time when the event
     * is triggered and the time when the system starts, in microseconds.</li>
     * <li>ArkUI_NodeComponentEvent.data[3].i32</b>: event input device. The value <b>1</b> indicates the mouse,
     * <li>2</b> indicates the touchscreen, and <b>4</b> indicates the key.</li>
     * <li>ArkUI_NodeComponentEvent.data[4].f32</b>: X coordinate of the click relative to the upper left corner of the
     * application window, in vp.</li>
     * <li>ArkUI_NodeComponentEvent.data[5].f32</b>: Y coordinate of the click relative to the upper left corner of the
     * application window, in vp.</li>
     * <li>ArkUI_NodeComponentEvent.data[6].f32</b>: X coordinate of the click relative to the upper left corner of the
     * application screen, in vp.</li>
     * <li>ArkUI_NodeComponentEvent.data[7].f32</b>: Y coordinate of the click relative to the upper left corner of the
     * application screen, in vp.</li>
     * </ul>
     *
     * @ingroup Interaction Event
     */
    NODE_ON_CLICK,
    /**
     * @brief Custom component event interception. This event is triggered when the component is touched. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}. \n
     *
     * @ingroup Interaction Event
     */
    NODE_ON_TOUCH_INTERCEPT,
    /**
     * @brief Visible area change event. This event is triggered when the ratio of the component's visible area to its
     * total area is greater than or less than the threshold. Before registering the event, you need to use
     * <b>NODE_VISIBLE_AREA_CHANGE_RATIO</b> to configure the threshold. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32</b>: how the ratio of the component's visible area to its total area
     * changes compared to the previous one. The value <b>1</b> indicates an increase, and <b>0</b> indicates a
     * decrease.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32</b>: ratio of the component's visible area to its total area when this
     * callback is invoked.</li>
     * </ul>
     *
     * @ingroup Interaction Event
     */
    NODE_EVENT_ON_VISIBLE_AREA_CHANGE,
    /**
     * @brief Event triggered when the mouse pointer moves over or away from the component. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32</b>: whether the mouse pointer is hovered over the component.
     * The value <b>1</b> indicates that the mouse pointer is hovered over the component, and <b>0</b> indicates that
     * the mouse pointer is moved away from the component.</li>
     * </ul>
     *
     * @ingroup Interaction Event
     */
    NODE_ON_HOVER,
    /**
     * @brief Mouse event. This event is triggered when the component is clicked by a mouse device button or when the
     * mouse pointer moves within the component. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}. \n
     *
     * @ingroup Interaction Event
     */
    NODE_ON_MOUSE,
    /**
     * @brief Attach event. This event is triggered when the component is attached to the component tree. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Interaction Event
     */
    NODE_EVENT_ON_ATTACH,
    /**
     * @brief Detach event. This event is triggered when the component is detached from the component tree. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Interaction Event
     */
    NODE_EVENT_ON_DETACH,

    /**
     * @brief Accessibility-supported action event. This event is triggered when an accessibility action is performed
     * after the corresponding accessibility action type is set. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].u32</b>: accessibility action type，the union type is
     * {@link ArkUI_AccessibilityActionType} \n
     *
     */
    NODE_ON_ACCESSIBILITY_ACTIONS = 13,

    /**
     * @brief Notifies the listener of the interaction state prior to a drop and drop operation.
     *
     * This event is triggered when a component is draggable and when a long press, lift, or drag initiation occurs. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32</b>: corresponds to {@link ArkUI_PreDragStatus}.</li>
     * </ul>
     *
     * @ingroup Drag Event
     */
    NODE_ON_PRE_DRAG = 14,
    /**
     * @brief Event triggered when the user starts to drag an item. A drag operation is recognized only when the
     * dragged item is moved far enough. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Drag Event
     */
    NODE_ON_DRAG_START = 15,
    /**
     * @brief Event triggered when a dragged item enters the boundaries of the current component.
     *
     * The current component refers to the component that listens for this event. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Drag Event
     */
    NODE_ON_DRAG_ENTER = 16,
    /**
     * @brief Event triggered when a dragged item moves in the current component.
     *
     * The current component refers to the component that listens for this event. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Drag Event
     */
    NODE_ON_DRAG_MOVE = 17,
    /**
     * @brief Event triggered when a dragged item leaves the boundaries of the current component.
     *
     * The current component refers to the component that listens for this event. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Drag Event
     */
    NODE_ON_DRAG_LEAVE = 18,
    /**
     * @brief Event triggered when a dragged item is dropped on the current component. The component can obtain the
     * drag data for processing through the callback.
     *
     * The current component refers to the component that listens for this event. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Drag Event
     */
    NODE_ON_DROP = 19,
    /**
     * @brief Event triggered when a drag operation ends. The drag source can obtain the drag result by registering
     * this callback.
     *
     * A drag operation ends when the dragged item is released.
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Drag Event
     */
    NODE_ON_DRAG_END = 20,
    /**
     * @brief Event triggered when a key event occurs. The callback can be triggered during interactions with a focused
     * window using an external keyboard or other input device. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     *
     * @ingroup Interaction Event
     *
     * @since 14
     */
    NODE_ON_KEY_EVENT = 21,
    /**
     * @brief Event triggered before the input method responds to the key action. If the return value of this callback
     * is <b>true</b>, the key event is considered consumed, and subsequent event callbacks (<b>keyboardShortcut</b>,
     * input method events, <b>onKeyEvent</b>) will be intercepted and no longer triggered. The callback can be
     * triggered during interactions with a focused window using an external keyboard or other input device. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     *
     * @ingroup Interaction Event
     *
     * @since 14
     */
    NODE_ON_KEY_PRE_IME = 22,
    /**
     * @brief Event triggered when the bound component receives a focus axis event after gaining focus. The event
     * callback is triggered by interactions with a joystick and a focused component. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}. \n
     *
     * @ingroup Interaction Event
     *
     * @since 15
     */
    NODE_ON_FOCUS_AXIS = 23,

    /**
     * @brief Component key event re-dispatch event. When a component node receives a key event, this callback is
     * triggered instead of dispatching the event to its child nodes. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     *
     * @ingroup Interaction Event
     *
     * @since 15
     */
    NODE_DISPATCH_KEY_EVENT = 24,

    /**
     * @brief Defines the event triggered when the bound component receives an axis event.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}. \n
     *
     * @ingroup Interaction Event
     *
     * @since 17
     */
    NODE_ON_AXIS = 25,

    /**
     * @brief Event triggered when the bound component is clicked. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}.  \n
     *
     * @ingroup Interaction Event
     *
     * @since 18
     */
    NODE_ON_CLICK_EVENT = 26,

    /**
     * @brief Event triggered when the mouse pointer moves over or away from the component. This event is triggered
     * when the mouse pointer enters or leaves the component's bounding box. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}. \n
     *
     * @ingroup Interaction Event
     *
     *@since 17
     */
    NODE_ON_HOVER_EVENT = 27,

    /**
     * @brief Sets the callback for the NODE_EVENT_ON_VISIBLE_AREA_CHANGE event, which limits the callback interval.
     *
     * The callback is triggered when the ratio of the component's visible area to its total area is greater than or
     * less than the threshold. Before registering the event, you need to use
     * <b>NODE_VISIBLE_AREA_APPROXIMATE_CHANGE_RATIO</b> to configure the threshold and update interval. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32</b>: how the ratio of the component's visible area to its total area
     * changes compared to the previous one. The value <b>1</b> indicates an increase, and <b>0</b> indicates
     * a decrease.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32</b>: ratio of the component's visible area to its total area
     * when this callback is invoked.</li>
     * </ul>
     *
     * @ingroup Interaction Event
     *
     * @since 17
     */
    NODE_VISIBLE_AREA_APPROXIMATE_CHANGE_EVENT = 28,

    /**
     * @brief Hover event. This event is triggered when the stylus pointer hovers over the component. \n
     * When the event callback occurs, the {@link ArkUI_NodeEvent} object can be obtained from the
     * {@link ArkUI_UIInputEvent} object. \n
     *
     * @ingroup Interaction Event
     *
     * @since 15
     */
    NODE_ON_HOVER_MOVE = 29,

    /**
     * @brief Size change event. This event is triggered when the component size changes.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * {@link ArkUI_NodeComponentEvent} contains four parameters:
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].f32</b>: width of the component before the size change.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32</b>: height of the component before the size change.</li>
     * <li>ArkUI_NodeComponentEvent.data[2].f32</b>: width of the component after the size change.</li>
     * <li>ArkUI_NodeComponentEvent.data[3].f32</b>: height of the component after the size change.</li>
     * </ul>
     *
     * @ingroup Interaction Event
     *
     * @since 21
     */
    NODE_ON_SIZE_CHANGE = 30,

    /**
     * @brief Coasting axis event. When a user slides two fingers on the touchpad for a certain distance and quickly
     * lifts the fingers, the system continuously constructs the event based on the speed at which the fingers are
     * lifted and a certain attenuation curve. You can listen to this type of events to handle the fling effect after
     * the normal scrolling axis event. \n
     * When the event callback occurs, the {@link ArkUI_UIInputEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object through {@link OH_ArkUI_NodeEvent_GetInputEvent}.
     * And the {@link ArkUI_CoastingAxisEvent} object can be obtained from the {@link ArkUI_UIInputEvent}
     * object through {@link OH_ArkUI_UIInputEvent_GetCoastingAxisEvent}. \n
     *
     * @ingroup Interaction Event
     *
     * @since 22
     */
    NODE_ON_COASTING_AXIS_EVENT = 31,

    /**
     * @brief Pre-touch test event of a child component. This event is called to specify how to perform a touch test on
     * the child component of the current component. This event is triggered when the component is touched. \n
     * When the event callback occurs, you can obtain the {@link ArkUI_TouchTestInfo} object from the
     * {@link ArkUI_NodeEvent} object by calling {@link OH_ArkUI_NodeEvent_GetTouchTestInfo}. \n
     *
     * @ingroup Interaction Event
     *
     * @since 22
     */
    NODE_ON_CHILD_TOUCH_TEST = 32,

    /**
     * @brief Defines the crown event.
     * This event is triggered when the crown is rotated. \n
     * When the event callback occurs, the {@link ArkUI_UIInputEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Interaction Event
     *
     * @since 24
     */
    NODE_ON_DIGITAL_CROWN = 33,

    /**
     * @brief Content scrolling event of the <b>ARKUI_NODE_CUSTOM</b> node. This event is triggered when the component
     * content is scrolled. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameters:\n
     * ArkUI_NodeComponentEvent.data[0].i32: id of scrolling child component. \n
     * ArkUI_NodeComponentEvent.data[1].f32: offset of the frame scrolling, measured in px. \n
     * @since 24
     */
    NODE_ON_CUSTOM_OVERFLOW_SCROLL = 34,

    /**
     * @brief Content scrolling event of the <b>ARKUI_NODE_STACK</b> node. This event is triggered when the component
     * content is scrolled. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameters:\n
     * ArkUI_NodeComponentEvent.data[0].i32: id of scrolling child component. \n
     * ArkUI_NodeComponentEvent.data[1].f32: offset of the frame scrolling, measured in px. \n
     * @since 24
     */
    NODE_ON_STACK_OVERFLOW_SCROLL = 35,

    /**
     * @brief Event for determining whether a keyboard is required. This event is triggered when the component gains
     * focus. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @return Whether softkeyboard is needed. \n
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * value.i32 at index 0 in the return value indicates whether softkeyboard is needed.
     * <b>0</b>: not needed. <b>1</b>: needed. \n
     * @since 24
     */
    NODE_ON_NEED_SOFTKEYBOARD = 36,

    /**
     * @brief This callback is invoked when the events and gestures on this node and
     * higher-priority nodes are collected. \n
     * This callback is used to intervene in the collection result of events and gestures. \n
     *
     * When the event callback occurs, the {@link ArkUI_GestureCollectInterceptInfo} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Interaction Event
     *
     * @since 26.0.0
     */
    NODE_ON_GESTURE_COLLECT_INTERCEPT = 37,

    /**
     * @brief Triggers onDetectResultUpdate callback
     * when the text is set to TextDataDetectorConfig and recognized successfully.
     *
     * Trigger this event when TextDataDetectorConfig is set and recognized successfully.\n
     * When the event callback occurs, the event parameter{@link ArkUI_NodeEvent}The union type in the object is
     * {@link ArkUI_StringAsyncEvent}.\n
     * **{@link ArkUI_StringAsyncEvent}contains 1 parameter**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr: Indicates the result of text recognition, in Json format.</li>
     * </ul>
     *
     * @ingroup Text Display
     */
    NODE_TEXT_ON_DETECT_RESULT_UPDATE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT,
    /**
     * @brief Long-press event for the span component. This callback is triggered when the component is long-pressed.
     * When the event callback occurs, the {@link ArkUI_NodeEvent} object can be obtained from the
     * {@link ArkUI_UIInputEvent} object. \n
     * @ingroup Text Display
     * @since 20
     */
    NODE_TEXT_SPAN_ON_LONG_PRESS = 1001,

    /**
     * @brief Event triggered when the text selection position changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].i32**: start position of the text selection range.</li>
     * <li>**ArkUI_NodeComponentEvent.data[1].i32**: end position of the text selection range.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 26.0.0
     */
    NODE_TEXT_ON_TEXT_SELECTION_CHANGE = 1002,

    /**
     * @brief Event triggered when the copy button on the clipboard, which displays when the text box is long
     * pressed, is clicked.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_StringAsyncEvent.pStr**: text to be copied.</li>
     * </ul>
     *
     * @ingroup Text Display
     * @since 26.0.0
     */
    NODE_TEXT_ON_COPY = 1003,

    /**
     * @brief Event triggered before text is copied.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_StringAsyncEvent.pStr**: text to be copied.</li>
     * </ul>
     *
     * @return You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     *     **value.i32** whose **index** is set to **0** indicates whether to intercept the default copying
     *     behavior of the component. \n
     *     **0**: intercept the default copying behavior of the component. **1**: not intercept the default
     *     copying behavior of the component. \n
     *
     * @ingroup Text Display
     * @since 26.0.0
     */
    NODE_TEXT_ON_WILL_COPY = 1004,

    /**
     * @brief Defines the image loading success event.
     *
     * This event is triggered when an image is successfully loaded or decoded. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains nine parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: loading status. The value <b>0</b> indicates that the image is
     * loaded successfully, and the value <b>1</b> indicates that the image is decoded successfully.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32: width of the image, in px.</li>
     * <li>ArkUI_NodeComponentEvent.data[2].f32: height of the image, in px.</li>
     * <li>ArkUI_NodeComponentEvent.data[3].f32: width of the component, in px.</li>
     * <li>ArkUI_NodeComponentEvent.data[4].f32: height of the component, in px.</li>
     * <li>ArkUI_NodeComponentEvent.data[5].f32: offset of the rendered content relative to the component on the
     * x-axis, in px.</li>
     * <li>ArkUI_NodeComponentEvent.data[6].f32: offset of the rendered content relative to the component on the
     * y-axis, in px.</li>
     * <li>ArkUI_NodeComponentEvent.data[7].f32: actual rendered width of the image, in px.</li>
     * <li>ArkUI_NodeComponentEvent.data[8].f32: actual rendered height of the image, in px.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_ON_COMPLETE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE,
    /**
     * @brief Image loading failure event.
     *
     * This event is triggered when an error occurs during image loading. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].i32**: result code.<br><b>401</b>: The image could not be obtained
     * because the image path is invalid.<br><b>103101</b>: The image format is not supported.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_ON_ERROR,
    /**
     * @brief SVG animation playback completion event.
     *
     * This event is triggered when the animation playback in the loaded SVG image is complete. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Image
     */
    NODE_IMAGE_ON_SVG_PLAY_FINISH,
    /**
     * @brief Event triggered during image download.
     *
     * This event is triggered when the page component downloads a web page image. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].u32**: number of bytes that have been downloaded.</li>
     * <li>**ArkUI_NodeComponentEvent.data[1].u32**: total number of bytes of the image to be downloaded.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_ON_DOWNLOAD_PROGRESS,
    /**
     * @brief Defines the event triggered when the toggle status changes.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains one parameter:** \n
     * <ul>
     * <li><b>ArkUI_NodeComponentEvent.data[0].i32</b>: toggle status. <b>1</b>: on; <b>0</b>: off.</li>
     * </ul>
     *
     * @ingroup Toggle
     */
    NODE_TOGGLE_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TOGGLE,
    /**
     * @brief Defines the event triggered when the text input content changes.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains one parameter:**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr: text input.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,
    /**
     * @brief Event triggered when the **Enter** key on the keyboard is pressed for the **TextInput** component.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].i32**: type of the **Enter** key.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_SUBMIT,
    /**
     * @brief Event triggered when the cut button on the clipboard, which displays when the text box is long
     * pressed, is clicked.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_StringAsyncEvent.pStr**: text to be cut.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_CUT,
    /**
     * @brief Defines the event triggered when the paste button on the pasteboard, which displays when the text box
     * is long pressed, is clicked.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains one parameter:**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr: text that is pasted.</li>
     * </ul>
     *
     * Since 26.0.0, the callback can return whether the paste is allowed.\n
     * @return Whether the paste is allowed. \n
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * value.i32 at index 0 in the return value indicates whether the paste is allowed. \n
     * <b>0</b>: not allowed. <b>1</b>: allowed. \n
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_PASTE,
    /**
     * @brief Event triggered when the text selection position changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].i32**: start position of the text selection range.</li>
     * <li>**ArkUI_NodeComponentEvent.data[1].i32**: end position of the text selection range.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_TEXT_SELECTION_CHANGE,

    /**
     * @brief Event triggered when the input state changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].i32**: **true** indicates that text input is in progress.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_EDIT_CHANGE,

    /**
     * @brief Event triggered when the text input content changes in the **TextInput** component.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].f32**: width of the text.</li>
     * <li>**ArkUI_NodeComponentEvent.data[1].f32**: height of the text.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_CONTENT_SIZE_CHANGE,

    /**
     * @brief Event triggered when matching with the regular expression specified by
     * **NODE_TEXT_INPUT_INPUT_FILTER** fails.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_StringAsyncEvent.pStr**: content that is filtered out when regular expression matching fails.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_INPUT_FILTER_ERROR,

    /**
     * @brief Event triggered when the text content is scrolled.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].i32**: offset in the x-coordinate of the text in the content area.</li>
     * <li>**ArkUI_NodeComponentEvent.data[1].i32**: offset in the y-coordinate of the text in the content area.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_CONTENT_SCROLL,

    /**
     * @brief Event triggered when text is about to be entered.
     *
     * When the event callback occurs, the event parameter is {@link ArkUI_NodeEvent}. \n
     * <ul>
     * <li>value.f32 at index 0: position of the text to be inserted; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>.</li>
     * <li>buffer at index 0: text to be inserted; obtained using <b>OH_ArkUI_NodeEvent_GetStringValue</b>.</li>
     * </ul>
     *
     * @return Returns <b>true</b> if the text is entered; returns <b>false</b> otherwise.
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_WILL_INSERT = 7009,

    /**
     * @brief Event triggered when input is completed.
     *
     * When the event callback occurs, the event parameter is {@link ArkUI_NodeEvent}. \n
     * <ul>
     * <li>value.f32 at index 0: position of the text inserted; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>.</li>
     * <li>buffer at index 0: inserted text; obtained using <b>OH_ArkUI_NodeEvent_GetStringValue</b>.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_DID_INSERT = 7010,

    /**
     * @brief Event triggered when text is about to be deleted.
     *
     * When the event callback occurs, the event parameter is {@link ArkUI_NodeEvent}. \n
     * <ul>
     * <li>value.f32 at index 0: position of the text to be deleted; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>.</li>
     * <li>value.i32: direction for deleting the text, with the index of <b>1</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>. The value <b>0</b> indicates backward-delete, and <b>1</b>
     * indicates forward-delete.</li>
     * <li>buffer at index 0: text to be deleted; obtained using <b>OH_ArkUI_NodeEvent_GetStringValue</b>.</li>
     * </ul>
     *
     * @return Returns <b>true</b> if the text is deleted; returns <b>false</b> otherwise. \n
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_WILL_DELETE = 7011,

    /**
     * @brief Event triggered when deletion is completed.
     *
     * When the event callback occurs, the event parameter is {@link ArkUI_NodeEvent}. \n
     * <ul>
     * <li>value.f32 at index 0: position of the text deleted; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>.</li>
     * <li>value.i32: direction for deleting the text, with the index of <b>1</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>. The value <b>0</b> indicates backward-delete, and <b>1</b>
     * indicates forward-delete.</li>
     * <li>buffer at index 0: deleted text; obtained using <b>OH_ArkUI_NodeEvent_GetStringValue</b>.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_INPUT_ON_DID_DELETE = 7012,

    /**
     * @brief Event triggered when content (including preview text) changes in the <b>TextInput</b> component.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_TextChangeEvent}. \n
     * **{@link ArkUI_TextChangeEvent} contains the following parameters:**
     * <ul>
     * <li>**ArkUI_TextChangeEvent.pStr**: content in the <b>TextInput</b> component.</li>
     * <li>**ArkUI_TextChangeEvent.pExtendStr**: content of the preview text in the <b>TextInput</b> component.</li>
     * <li>**ArkUI_TextChangeEvent.number**: start position of the preview text in the <b>TextInput</b> component.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 15
     */
    NODE_TEXT_INPUT_ON_CHANGE_WITH_PREVIEW_TEXT = 7013,

    /**
     * @brief Event triggered when content (including preview text) is about to change in the <b>TextInput</b>
     * component.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_TextChangeEvent}. \n
     * **{@link ArkUI_TextChangeEvent} contains the following parameters:**
     * <ul>
     * <li>**ArkUI_TextChangeEvent.pStr**: content in the <b>TextInput</b> component.</li>
     * <li>**ArkUI_TextChangeEvent.pExtendStr**: content of the preview text in the <b>TextInput</b> component.</li>
     * <li>**ArkUI_TextChangeEvent.number**: start position of the preview text in the <b>TextInput</b> component.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 20
     */
    NODE_TEXT_INPUT_ON_WILL_CHANGE = 7014,

    /**
     * @brief Event triggered when the copy button on the clipboard, which displays when the user clicks text
     * selection, is clicked.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_StringAsyncEvent.pStr**: text to be copied.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_ON_COPY = 7015,

    /**
     * @brief Event triggered before text is copied.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_StringAsyncEvent.pStr**: text to be copied.</li>
     * </ul>
     *
     * @return You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     *     **value.i32** whose **index** is set to **0** indicates whether to intercept the default copying
     *     behavior of the component. \n
     *     **0**: intercept the default copying behavior of the component. **1**: not intercept the default
     *     copying behavior of the component. \n
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_ON_WILL_COPY = 7016,

    /**
     * @brief Event triggered before text is cut.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_StringAsyncEvent.pStr**: text to be cut.</li>
     * </ul>
     *
     * @return You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     *     **value.i32** whose **index** is set to **0** indicates whether to intercept the default cutting
     *     behavior of the component. \n
     *     **0**: intercept the default cutting behavior of the component. **1**: not intercept the default cutting
     *     behavior of the component. \n
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_ON_WILL_CUT = 7017,

    /**
     * @brief Defines the event triggered when the input in the text box changes.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains one parameter:**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr: text entered.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_AREA,
    /**
     * @brief Defines the event triggered when the paste button on the pasteboard, which displays when the text box is
     * long pressed, is clicked.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains one parameter:**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr: text that is pasted.</li>
     * </ul>
     *
     * Since 26.0.0, the callback can return whether the paste is allowed.\n
     * @return Whether the paste is allowed. \n
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * value.i32 at index 0 in the return value indicates whether the paste is allowed. \n
     * <b>0</b>: not allowed. <b>1</b>: allowed. \n
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ON_PASTE,
    /**
     * @brief Event triggered when the text selection position changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].i32**: start position of the text selection range.</li>
     * <li>**ArkUI_NodeComponentEvent.data[1].i32**: end position of the text selection range.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ON_TEXT_SELECTION_CHANGE,
    /**
     * @brief Event triggered when matching with the regular expression specified by
     * **NODE_TEXT_AREA_INPUT_FILTER** fails.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_StringAsyncEvent.pStr**: content that is filtered out when regular expression matching fails.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ON_INPUT_FILTER_ERROR,
    /**
     * @brief Event triggered when the text content is scrolled.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].i32**: offset in the x-coordinate of the text in the content area.</li>
     * <li>**ArkUI_NodeComponentEvent.data[1].i32**: offset in the y-coordinate of the text in the content area.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ON_CONTENT_SCROLL,

    /**
     * @brief Event triggered when the input state changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].i32**: **true** indicates that text input is in progress.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ON_EDIT_CHANGE,

    /**
     * @brief Event triggered when the **Enter** key on the keyboard is pressed for the **TextArea** component. It
     * is not triggered when **keyType** is **ARKUI_ENTER_KEY_TYPE_NEW_LINE**.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameter:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].i32**: type of the **Enter** key.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ON_SUBMIT,

    /**
     * @brief Event triggered when the text input content changes in the **TextArea** component.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>**ArkUI_NodeComponentEvent.data[0].f32**: width of the text.</li>
     * <li>**ArkUI_NodeComponentEvent.data[1].f32**: height of the text.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ON_CONTENT_SIZE_CHANGE,

    /**
     * @brief Event triggered when text is about to be entered.
     *
     * When the event callback occurs, the event parameter is {@link ArkUI_NodeEvent}. \n
     * <ul>
     * <li>value.f32: position of the text to be inserted, with the index of <b>0</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>.</li>
     * <li>buffer: string value of the text to be inserted, with the index of <b>0</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetStringValue</b>.</li>
     * </ul>
     *
     * @return Returns <b>true</b> if the text is entered; returns <b>false</b> otherwise.
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ON_WILL_INSERT = 8008,

    /**
     * @brief Event triggered when input is completed.
     *
     * When the event callback occurs, the event parameter is {@link ArkUI_NodeEvent}. \n
     * <ul>
     * <li>value.f32: position of the text inserted, with the index of <b>0</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>.</li>
     * <li>buffer: string value of the inserted text, with the index of <b>0</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetStringValue</b>.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ON_DID_INSERT = 8009,

    /**
     * @brief Event triggered when text is about to be deleted.
     *
     * When the event callback occurs, the event parameter is {@link ArkUI_NodeEvent}. \n
     * <ul>
     * <li>value.f32: position of the text to be deleted, with the index of <b>0</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>.</li>
     * <li>value.i32: direction for deleting the text, with the index of <b>1</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>. The value <b>0</b> indicates backward-delete, and <b>1</b>
     * indicates forward-delete.</li>
     * <li>buffer: string value of the text to be deleted, with the index of <b>0</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetStringValue</b>.</li>
     * </ul>
     *
     * @return Returns <b>true</b> if the text is deleted; returns <b>false</b> otherwise. \n
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ON_WILL_DELETE = 8010,

    /**
     * @brief Event triggered when deletion is completed.
     *
     * When the event callback occurs, the event parameter is {@link ArkUI_NodeEvent}. \n
     * <ul>
     * <li>value.f32: position of the text deleted, with the index of <b>0</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>.</li>
     * <li>value.i32: direction for deleting the text, with the index of <b>1</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>. The value <b>0</b> indicates backward-delete, and <b>1</b>
     * indicates forward-delete.</li>
     * <li>buffer: string value of the deleted text, with the index of <b>0</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetStringValue</b>.</li>
     * </ul>
     *
     * @ingroup Text Input
     */
    NODE_TEXT_AREA_ON_DID_DELETE = 8011,

    /**
     * @brief Event triggered when content (including preview text) changes in the <b>TextArea</b> component.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_TextChangeEvent}. \n
     * **{@link ArkUI_TextChangeEvent} contains the following parameters:**
     * <ul>
     * <li>**ArkUI_TextChangeEvent.pStr**: content in the <b>TextArea</b> component.</li>
     * <li>**ArkUI_TextChangeEvent.pExtendStr**: content of the preview text in the <b>TextArea</b> component.</li>
     * <li>**ArkUI_TextChangeEvent.number**: start position of the preview text in the <b>TextArea</b> component.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 15
     */
    NODE_TEXT_AREA_ON_CHANGE_WITH_PREVIEW_TEXT = 8012,

    /**
     * @brief Event triggered when content (including preview text) is about to change in the <b>TextArea</b>
     * component.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_TextChangeEvent}. \n
     * **{@link ArkUI_TextChangeEvent} contains the following parameters:**
     * <ul>
     * <li>**ArkUI_TextChangeEvent.pStr**: content in the <b>TextArea</b> component.</li>
     * <li>**ArkUI_TextChangeEvent.pExtendStr**: content of the preview text in the <b>TextArea</b> component.</li>
     * <li>**ArkUI_TextChangeEvent.number**: start position of the preview text in the <b>TextArea</b> component.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 20
     */
    NODE_TEXT_AREA_ON_WILL_CHANGE = 8013,

    /**
     * @brief Event triggered when the copy button on the clipboard, which displays when the text box is long
     * pressed, is clicked.
     * \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains the following parameter:**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr: text to be copied.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_AREA_ON_COPY = 8014,

    /**
     * @brief Event triggered before text is copied.
     * \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains the following parameter:**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr: text to be copied.</li>
     * </ul>
     *
     * @return You can use {@link OH_ArkUI_NodeEvent_SetReturnNumberValue} to set the return value. \n
     *     **value.i32** whose **index** is set to **0** indicates whether to intercept the default copying behavior
     *     of the component. \n
     *     **0**: intercept the default copying behavior of the component. **1**: not intercept the default copying
     *     behavior of the component. \n
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_AREA_ON_WILL_COPY = 8015,

    /**
     * @brief Event triggered when the cut button on the clipboard, which displays when the internal area of the
     * text box is long pressed, is clicked.
     * \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains the following parameter:**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr: text to be cut.</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_AREA_ON_CUT = 8016,

    /**
     * @brief Event triggered before text is cut.
     * \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * **{@link ArkUI_StringAsyncEvent} contains the following parameter:**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr: text to be cut.</li>
     * </ul>
     *
     * @return You can use {@link OH_ArkUI_NodeEvent_SetReturnNumberValue} to set the return value. \n
     *     **value.i32** whose **index** is set to **0** indicates whether to intercept the default cutting behavior
     *     of the component. \n
     *     **0**: intercept the default cutting behavior of the component. **1**: not intercept the default cutting
     *     behavior of the component. \n
     *
     * @ingroup Text Input
     * @since 26.0.0
     */
    NODE_TEXT_AREA_ON_WILL_CUT = 8017,

    /**
     * @brief Defines the event triggered when the selected status of the <b>ARKUI_NODE_CHECKBOX</b> component changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b><b>1</b>: selected; <b>0</b>: not selected.\n
     *
     * @ingroup Checkbox
     */
    NODE_CHECKBOX_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CHECKBOX,

    /**
     * @brief Defines the event triggered when a date is selected in the <b>ARKUI_NODE_DATE_PICKER</b> component.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * {@link ArkUI_NodeComponentEvent} contains three parameters:
     * <ul>
     * <li><b>ArkUI_NodeComponentEvent.data[0].i32</b>: year of the selected date.</li>
     * <li><b>ArkUI_NodeComponentEvent.data[1].i32</b>: month of the selected date. Value range: [0-11].</li>
     * <li><b>ArkUI_NodeComponentEvent.data[2].i32</b>: day of the selected date.</li>
     * </ul>
     *
     * @ingroup Datepicker
     */
    NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_DATE_PICKER,

    /**
     * @brief Defines the event triggered when a time is selected in the <b>ARKUI_NODE_TIME_PICKER</b> component.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * {@link ArkUI_NodeComponentEvent} contains two parameters:
     * <ul>
     * <li><b>ArkUI_NodeComponentEvent.data[0].i32</b>: hour of the selected time. Value range: [0-23].</li>
     * <li><b>ArkUI_NodeComponentEvent.data[1].i32</b>: minute of the selected time. Value range: [0-59].</li>
     * </ul>
     *
     * @ingroup Timepicker
     */
    NODE_TIME_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TIME_PICKER,

    /**
     * @brief Defines the event triggered when an item is selected in the <b>ARKUI_NODE_TEXT_PICKER</b> component.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * {@link ArkUI_NodeComponentEvent} contains one parameter:
     * <ul>
     * <li><b>ArkUI_NodeComponentEvent.data[0...11].i32</b>: value of the selected item.</li>
     * </ul>
     *
     * @ingroup Textpicker
     */
    NODE_TEXT_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_PICKER,

    /**
     * @brief Event triggered when an item is selected in the <b>ARKUI_NODE_TEXT_PICKER</b> component. This event
     * is triggered when the user stops sliding to select a text item.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * {@link ArkUI_NodeComponentEvent} contains the following parameter:
     * <ul>
     * <li><b>ArkUI_NodeComponentEvent.data[0...11].i32</b>: value of the selected item.</li>
     * </ul>
     *
     * @ingroup Textpicker
     * @since 14
     */
    NODE_TEXT_PICKER_EVENT_ON_SCROLL_STOP = 15001,

    /**
     * @brief Defines the event triggered when a date is selected in the <b>NODE_CALENDAR_PICKER</b>.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <ul>
     * <li><b>ArkUI_NodeComponent.data[0].u32</b>: year of the selected date.</li>
     * <li><b>ArkUI_NodeComponent.data[1].u32</b>: month of the selected date.</li>
     * <li><b>ArkUI_NodeComponent.data[2].u32</b>: day of the selected date.</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     */
    NODE_CALENDAR_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CALENDAR_PICKER,

    /**
     * @brief Defines the event triggered when the <b>ARKUI_NODE_SLIDER</b> component is dragged or clicked.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains two parameters:**\n
     * <ul>
     * <li><b>ArkUI_NodeComponentEvent.data[0].f32</b>: current slider value.</li> \n
     * <li><b>ArkUI_NodeComponentEvent.data[1].i32</b>: state triggered by the event.</li>\n
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SLIDER,

    /**
     * @brief Defines the event callback function triggered when an object is dragged or clicked by ARKUI_NODE_RADIO.
     * When the event callback occurs, the union type in the {@Link ArkUI_NodeEvent} object is \n
     * {@Link ArkUI_NodeComponentEvent}. \n
     * **{@Link ArkUI_NodeComponentEvent} contains one parameter:**\n
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: option button status.</li> \n
     * </ul>
     *
     * @ingroup Radio
     */
    NODE_RADIO_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_RADIO,

    /**
     * @brief Defines the event triggered when the animation starts to play.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_EVENT_ON_START = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE_ANIMATOR,
    /**
     * @brief Event triggered when the frame-by-frame animation playback is paused.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_EVENT_ON_PAUSE = 19001,
    /**
     * @brief Event triggered when the frame-by-frame animation playback is repeated.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_EVENT_ON_REPEAT = 19002,
    /**
     * @brief Event triggered when the frame-by-frame animation playback returns to the initial state.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_EVENT_ON_CANCEL = 19003,
    /**
     * @brief Event triggered when the frame-by-frame animation playback is complete or stopped.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_EVENT_ON_FINISH = 19004,

    /**
     * @brief Defines the callback triggered when the selected status of the <b>ARKUI_NODE_CHECKBOX_GROOUP</b>
     * or checkbox changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * <b>ArkUI_StringAsyncEvent.pStr</b>
     * Name: The names of the selected checkboxes;
     * **Status:**
     * <ul>
     * <li>0: All checkboxes are selected.</li>
     * <li>1: Some checkboxes are selected.</li>
     * <li>2: No checkboxes are selected.</li> \n
     * </ul>
     *
     * @ingroup CheckboxGroup
     * @since 15
     */
    NODE_CHECKBOX_GROUP_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CHECKBOX_GROUP,

    /**
     * @brief Event triggered when the selection or cursor position in the **TextEditor** component changes.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: start index of the selection.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32: end index of the selection.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_SELECTION_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_EDITOR,

    /**
     * @brief Event triggered when the first initialization of the **TextEditor** component is complete.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_READY,

    /**
     * @brief Event triggered when the **TextEditor** component pastes content.
     * <br>The system determines whether to intercept the default behavior of the component based on the return value
     * of the callback function.
     * <br>You can use {@link OH_ArkUI_NodeEvent_SetReturnNumberValue} to set the return value.
     * <br>**value.i32**: whether to intercept the default behavior of the component, with the index of **0**.
     * <br>**0**: not intercept. **1**: intercept.
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_PASTE,

    /**
     * @brief Event triggered when the editing status of the **TextEditor** component changes.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * **{@link ArkUI_NodeComponentEvent} contains the following parameter:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: editing status of the component.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_EDITING_CHANGE,

    /**
     * @brief Event triggered when the **Enter** key on the keyboard is pressed for the **TextEditor** component.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * **{@link ArkUI_NodeComponentEvent} contains the following parameter:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: type of the Enter key, specified using {@link ArkUI_EnterKeyType}.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_SUBMIT,

    /**
     * @brief Event triggered when the **TextEditor** component cuts content.
     * <br>The system determines whether to intercept the default behavior of the component based on the return value
     * of the callback function.
     * <br>You can use {@link OH_ArkUI_NodeEvent_SetReturnNumberValue} to set the return value.
     * <br>**value.i32**: whether to intercept the default behavior of the component, with the index of **0**.
     * <br>**0**: not intercept. **1**: intercept.
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_CUT,

    /**
     * @brief Event triggered when the **TextEditor** component copies content.
     * <br>The system determines whether to intercept the default behavior of the component based on the return value
     * of the callback function.
     * <br>You can use {@link OH_ArkUI_NodeEvent_SetReturnNumberValue} to set the return value.
     * <br>**value.i32**: whether to intercept the default behavior of the component, with the index of **0**.
     * <br>**0**: not intercept. **1**: intercept.
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_COPY,

    /**
     * @brief Event triggered when the **TextEditor** component is about to change the content.
     * <br>This callback is triggered before any operation that causes a text content change takes effect. You can
     * determine whether to intercept the content change based on the information in the callback event.
     * <br>When the event callback occurs, you can obtain the {@link OH_ArkUI_TextEditorChangeEvent} object from the
     * {@link ArkUI_NodeEvent} object by calling {@link OH_ArkUI_NodeEvent_GetTextEditorOnWillChangeEvent}.
     * <br>Then, you can use the **OH_ArkUI_TextEditorChangeEvent_***XXX* series APIs to obtain more information from
     * this object.
     * <br>The system determines whether the current content can be changed based on the return value of the callback
     * function.
     * <br>You can use {@link OH_ArkUI_NodeEvent_SetReturnNumberValue} to set the return value.
     * <br>**value.i32** whose **index** is set to **0** indicates whether the current content can be changed. **0**:
     * The content cannot be changed. **1**: The content can be changed.
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_WILL_CHANGE,

    /**
     * @brief Event triggered when the **TextEditor** component changes the content.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: start index of the text range to be replaced before the text
     * changes.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32: end index of the text range to be replaced before the text
     * changes.</li>
     * <li>ArkUI_NodeComponentEvent.data[2].i32: start index of the text range of the new content after the text
     * changes.</li>
     * <li>ArkUI_NodeComponentEvent.data[3].i32: end index of the text range of the new content after the text
     * changes.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_DID_CHANGE,

    /**
     * @brief This event is triggered when the text content of TextEditor is scrolled.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * **{@link ArkUI_NodeComponentEvent} contains 2 parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].f32: Indicates the horizontal offset of the text in the content area.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32: Indicates the vertical offset of the text in the content area.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_ON_CONTENT_SCROLL = 22009,

    /**
     * @brief This event is triggered when the content size of TextEditor changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * **{@link ArkUI_NodeComponentEvent} contains 2 parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].f32: Indicates the width of the text.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32: Indicates the height of the text.</li>
     * </ul>
     *
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_ON_CONTENT_SIZE_CHANGE = 22010,

    /**
     * @brief Event triggered when input characters are rejected by the inputFilter regex
     * of the **TextEditor** component.
     * <br>This event is effective only in spanString mode.
     * <br>The event is triggered only when the onInputFilterError callback has been registered
     * and input characters are rejected by the inputFilter regex.
     * <br>When the event callback occurs, you can obtain the rejected characters from the
     * {@link ArkUI_NodeEvent} object by calling {@link OH_ArkUI_NodeEvent_GetStringAsyncEvent}.
     * <br>The **ArkUI_StringAsyncEvent.pStr** field contains the rejected characters as a UTF-8 string.
     * @ingroup Text Editor
     * @since 26.2.0
     */
    NODE_TEXT_EDITOR_ON_INPUT_FILTER_ERROR = 22011,

    /**
     * @brief Defines the event triggered when the index of the currently displayed element of this
     * <b>ARKUI_NODE_ARC_ALPHABET_INDEXER</b> instance changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains one parameter:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently displayed element.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_ALPHABET_INDEXER_EVENT_ON_SELECT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_ALPHABET_INDEXER,

    /**
     * @brief Defines the event triggered when the index of the currently displayed element of this
     * <b>ARKUI_NODE_SWIPER</b> instance changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains one parameter:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently displayed element.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SWIPER,

    /**
     * @brief Event triggered when the switching animation of this <b>ARKUI_NODE_SWIPER</b> instance starts.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently displayed element.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32: index of the target element to switch to.</li>
     * <li>ArkUI_NodeComponentEvent.data[2].f32: offset of the currently displayed element relative to the
     * start position of the swiper along the main axis.</li>
     * <li>ArkUI_NodeComponentEvent.data[3].f32: offset of the target element relative to the start position
     * of the swiper along the main axis.</li>
     * <li>ArkUI_NodeComponentEvent.data[4].f32: hands-off velocity.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_EVENT_ON_ANIMATION_START,

    /**
     * @brief Event triggered when the transition animation of <b>ARKUI_NODE_SWIPER</b> ends.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently displayed element.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32: offset of the currently displayed element relative to the
     * start position of the swiper along the main axis.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_EVENT_ON_ANIMATION_END,

    /**
     * @brief Event triggered on a frame-by-frame basis when the page is turned by a swipe.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently displayed element.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32: offset of the currently displayed element relative to the
     * start position of the swiper along the main axis.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_EVENT_ON_GESTURE_SWIPE,

    /**
     * @brief Event triggered when the Swiper page scrolls, which is listened by <b>ARKUI_NODE_SWIPER</b>.
     * Instructions: \n
     * 1. This API does not work when <b>NODE_SWIPER_DISPLAY_COUNT</b> is set to <b>'auto'</b>. \n
     * 2. This API does not work when <b>prevMargin</b> and <b>nextMargin</b> are set in such a way that the
     * <b>Swiper</b> frontend and backend display the same page during loop playback. \n
     * 3. During page scrolling, the <b>ContentDidScrollCallback</b> callback is invoked for all pages in the
     * viewport on a frame-by-frame basis. \n
     * For example, when there are two pages whose subscripts are 0 and 1 in the viewport, two callbacks whose
     * indexes are 0 and 1 are invoked in each frame. \n
     * 4. When the <b>swipeByGroup</b> parameter of the <b>displayCount</b> attribute is set to <b>true</b>, the
     * callback is invoked for all pages in a group if any page in the group is within the viewport. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the <b>Swiper</b> component, which is the same as the
     * index in the onChange event.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32: index of a page in the viewport.</li>
     * <li>ArkUI_NodeComponentEvent.data[2].f32: position of the page relative to the start position of the
     * <b>Swiper</b> component's main axis (start position of the page corresponding to <b>selectedIndex</b>).</li>
     * <li>ArkUI_NodeComponentEvent.data[3].f32: length of the page in the main axis direction.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_EVENT_ON_CONTENT_DID_SCROLL,

    /**
     * @brief Event triggered when the selection changes in the <b>ARKUI_NODE_SWIPER</b> component. This event is
     * triggered in the following scenarios: \n
     * 1. When the page switching animation starts after the user lifts their finger after swiping and the swipe
     * meets the threshold for page turning. \n
     * 2. When the page is changed programmatically using either <b>NODE_SWIPER_INDEX</b> or
     * <b>NODE_SWIPER_SWIPE_TO_INDEX</b>. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameter:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently selected element.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 18
     */
    NODE_SWIPER_EVENT_ON_SELECTED = 1001005,

    /**
     * @brief Event triggered when the selection changes in the <b>ARKUI_NODE_SWIPER</b> component. This event is
     * triggered when any of the following occurs: \n
     * 1. When the page switching animation starts after the user lifts their finger after swiping and the swipe
     * meets the threshold for page turning. \n
     * 2. When the page is changed using either <b>NODE_SWIPER_INDEX</b> or <b>NODE_SWIPER_SWIPE_TO_INDEX</b>. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameter:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the element that is about to be hidden.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 18
     */
    NODE_SWIPER_EVENT_ON_UNSELECTED = 1001006,

    /**
     * @brief Event for swipe behavior interception in the <b>ARKUI_NODE_SWIPER</b> component. Usage: The
     * <b>ContentWillScrollCallback</b> callback is triggered before a swipe operation. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently displayed element. The value of this
     * parameter is used as the result of the interception event. The value <b>0</b> indicates that interception
     * is performed; the value <b>1</b> indicates that interception is not performed.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32: index of the target element to switch to.</li>
     * <li>ArkUI_NodeComponentEvent.data[2].f32: swipe offset per frame. A positive value indicates swiping
     * backward (for example, from index=1 to index=0), and a negative value indicates swiping forward (for
     * example, from index=0 to index=1).</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 15
     */
    NODE_SWIPER_EVENT_ON_CONTENT_WILL_SCROLL = 1001007,

    /**
     * @brief <b>ARKUI_NODE_SWIPER</b> scroll state change event. This event is triggered under the following
     * scenarios: \n
     * The <b>Swiper</b> transitions between three scroll states: scrolling with the touch, animating after
     * release, and stopped.
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameter:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: current scroll state. The parameter type is
     * {@link ArkUI_ScrollState}.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 20
     */
    NODE_SWIPER_EVENT_ON_SCROLL_STATE_CHANGED = 1001008,

    /**
     * @brief Event triggered when scrolling occurs. This event is triggered under the following scenarios:
     * <br>1. Scrolling is started by the scrollable component (supports keyboard, mouse, and other input methods that
     * trigger scrolling).
     * <br>2. Scrolling is initiated by calling the controller API.
     * <br>3. The out-of-bounds bounce effect is active.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: horizontal scrolling offset.
     * <br>**ArkUI_NodeComponentEvent.data[1].f32**: vertical scrolling offset.
     *
     */
    NODE_SCROLL_EVENT_ON_SCROLL = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,

    /**
     * @brief Event triggered when the scrollable container starts scrolling in each frame. The **List**, **Scroll**,
     * and **WaterFlow** components support this event since API version 12, and the **Grid** component supports this
     * event since API version 22.
     * <br>This event is triggered under the following scenarios:
     * <br>1. This event is triggered when scrolling is started by the scrollable component (supports keyboard, mouse,
     * and other input methods that trigger scrolling).
     * <br>2. This event is not triggered when the controller API is called.
     * <br>3. This event is not triggered when the component bounces back out of bounds.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: amount to scroll by.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: current scroll state.
     * <br>**::ArkUI_NodeComponentEvent** contains one return value:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: The event handler can work out the amount by which the component
     * needs to scroll based on the real-world situation and return the result in this parameter.
     *
     */
    NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN,

    /**
     * @brief Event triggered when the scrollable container is about to scroll. This event is triggered under the
     * following scenarios:
     * <br>1. Scrolling is started by the scrollable component (supports keyboard, mouse, and other input methods that
     * trigger scrolling).
     * <br>2. Scrolling is initiated by calling the controller API.
     * <br>3. The out-of-bounds bounce effect is active.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: scroll offset of each frame, in vp. The offset is positive when
     * the content is scrolled left and negative when the content is scrolled right.
     * <br>**ArkUI_NodeComponentEvent.data[1].f32**: scroll offset of each frame, in vp. The offset is positive when
     * the content is scrolled up and negative when the content is scrolled down.
     * <br>**ArkUI_NodeComponentEvent.data[2].i32**: current scroll state. The parameter type is
     * {@link ArkUI_ScrollState}.
     * <br>**ArkUI_NodeComponentEvent.data[3].i32**: scroll source. The parameter type is
     * {@link ArkUI_ScrollSource}.
     *
     * @return Does not return or returns a number that sets the actual scroll distance of the scroll component.
     */
    NODE_SCROLL_EVENT_ON_WILL_SCROLL,
    /**
     * @brief Event triggered when the scrollable container scrolls. This event is triggered under the following
     * scenarios:
     * <br>1. Scrolling is started by the scrollable component (supports keyboard, mouse, and other input methods that
     * trigger scrolling).
     * <br>2. Scrolling is initiated by calling the controller API.
     * <br>3. The out-of-bounds bounce effect is active.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: scroll offset of each frame, in vp. The offset is positive when
     * the content is scrolled left and negative when the content is scrolled right.
     * <br>**ArkUI_NodeComponentEvent.data[1].f32**: scroll offset of each frame, in vp. The offset is positive when
     * the content is scrolled up and negative when the content is scrolled down.
     * <br>**ArkUI_NodeComponentEvent.data[2].i32**: current scroll state. The parameter type is
     * {@link ArkUI_ScrollState}.
     *
     */
    NODE_SCROLL_EVENT_ON_DID_SCROLL,
    /**
     * @brief Event triggered when the scrollable container starts scrolling. The **List**, **Scroll**, and **WaterFlow*
     * * components support this event since API version 12, and the **Grid** component supports this event since API
     * version 22.
     * <br>This event is triggered under the following scenarios:
     * <br>1. Scrolling is started by the scrollable component (supports keyboard, mouse, and other input methods that
     * trigger scrolling).
     * <br>2. The controller API is called to start the scrolling, accompanied by a transition animation.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     */
    NODE_SCROLL_EVENT_ON_SCROLL_START,

    /**
     * @brief Event triggered when the scrollable container stops scrolling. The **List**, **Scroll**, and **WaterFlow**
     * components support this event since API version 12, and the **Grid** component supports this event since API
     * version 22.
     * <br>This event is triggered under the following scenarios:
     * <br>1. Scrolling is stopped by the scrollable component (supports keyboard, mouse, and other input methods that
     * trigger scrolling).
     * <br>2. The controller API is called to stop the scrolling, accompanied by a transition animation.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     */
    NODE_SCROLL_EVENT_ON_SCROLL_STOP,

    /**
     * @brief Event triggered when the scrollable container reaches the scroll boundary. This event is triggered under
     * the following scenarios:
     * <br>1. Scrolling reaches the edge after being started by the scrollable component (supports keyboard, mouse, and
     * other input methods that trigger scrolling).
     * <br>2. Scrolling is initiated by calling the controller API.
     * <br>3. The out-of-bounds bounce effect is active.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameter:
     * <br>**ArkUI_NodeComponentEvent.data[0].i32**: edge (top, bottom, left, or right) that the scrolling reaches.
     *
     */
    NODE_SCROLL_EVENT_ON_SCROLL_EDGE,

    /**
     * @brief Event triggered when the scrollable component reaches the start edge.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     */
    NODE_SCROLL_EVENT_ON_REACH_START,

    /**
     * @brief Event triggered when the scrollable component reaches the end edge.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     */
    NODE_SCROLL_EVENT_ON_REACH_END,

    /**
     * @brief Event triggered when the user is about to release the drag on the scrollable component.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameter:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: speed at which the user releases the drag, in vp/s.
     *
     * @since 20
     */
    NODE_SCROLL_EVENT_ON_WILL_STOP_DRAGGING,

    /**
     * @brief **Scroll** component zoom event, triggered at the end of each frame during zooming.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameter:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: current zoom scale.
     *
     * @since 20
     */
    NODE_SCROLL_EVENT_ON_DID_ZOOM,

    /**
     * @brief **Scroll** component's zoom start event, triggered when zooming begins.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @since 20
     */
    NODE_SCROLL_EVENT_ON_ZOOM_START,

    /**
     * @brief {@link Scroll} component's zoom end event, triggered when zooming ends.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @since 20
     */
    NODE_SCROLL_EVENT_ON_ZOOM_STOP,

    /**
     * @brief Event triggered when the user is about to drag the scrollable component.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @since 21
     */
    NODE_SCROLL_EVENT_ON_WILL_START_DRAGGING = 1002013,

    /**
     * @brief Event triggered when the user ends dragging the scrollable component.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameter:
     * <br>**ArkUI_NodeComponentEvent.data[0].i32**: whether to trigger the sliding animation after the drag ends.
     *
     * @since 21
     */
    NODE_SCROLL_EVENT_ON_DID_STOP_DRAGGING = 1002014,

    /**
     * @brief Event triggered when the scrollable component's flinging animation is about to start.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @since 21
     */
    NODE_SCROLL_EVENT_ON_WILL_START_FLING = 1002015,

    /**
     * @brief Event triggered when the scrollable component's flinging animation ends.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @since 21
     */
    NODE_SCROLL_EVENT_ON_DID_STOP_FLING = 1002016,

    /**
     * @brief Event triggered when a child component of {@link ARKUI_NODE_LIST} enters or leaves the list display area.
     * This event is triggered in the following scenarios:
     * <br>This event is triggered once when the list is initialized and when the index of the first child component or
     * the last child component in the list display area changes.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].i32**: index of the first child component in the list display area.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: index of the last child component in the list display area.
     * <br>**ArkUI_NodeComponentEvent.data[2].i32**: index of the center child component in the list display area.
     *
     */
    NODE_LIST_ON_SCROLL_INDEX = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST,

    /**
     * @brief Event triggered when the {@link ARKUI_NODE_LIST} component is about to scroll. This event is triggered in
     * the following scenarios:
     * <br>1. Scrolling is started by the scrollable component (supports keyboard, mouse, and other input methods that
     * trigger scrolling).
     * <br>2. Scrolling is initiated by calling the controller API.
     * <br>3. The out-of-bounds bounce effect is active.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: scroll offset of each frame. The offset is positive when the list
     * is scrolled up and negative when the list is scrolled down.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: current scroll state. The parameter type is
     * {@link ArkUI_ScrollState}.
     * <br>**ArkUI_NodeComponentEvent.data[2].i32**: scroll source. The parameter type is
     * {@link ArkUI_ScrollSource}.
     *
     * @return Does not return or returns a number that sets the actual scroll distance of the scroll component. \n
     */
    NODE_LIST_ON_WILL_SCROLL,
    /**
     * @brief Event triggered when the {@link ARKUI_NODE_LIST} component scrolls. This event is triggered under the
     * following scenarios:
     * <br>1. Scrolling is started by the scrollable component (supports keyboard, mouse, and other input methods that
     * trigger scrolling).
     * <br>2. Scrolling is initiated by calling the controller API.
     * <br>3. The out-of-bounds bounce effect is active.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: scroll offset of each frame. The offset is positive when the list
     * is scrolled up and negative when the list is scrolled down.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: current scroll state.
     *
     */
    NODE_LIST_ON_DID_SCROLL,

    /**
     * @brief Event triggered when the currently displayed content of the **ARKUI_NODE_LIST** component changes. This
     * event is triggered under the following scenarios:
     * <br>This event is triggered once when the list is initialized and when the index of the first child component or
     * the last child component in the list display area changes. During trigger condition calculation, {@link header}
     * or {@link footer} in each {@link ListItem} and {@link ListItemGroup} is considered as a child component.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].i32**: index of the first child component in the list display area.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: area in the list item group where the list display area starts.
     * The type is {@link ArkUI_ListItemGroupArea}.
     * <br>**ArkUI_NodeComponentEvent.data[2].i32**: index of the list item at the start of the list display area in
     * the list item group. If the start of the list display area is not on a list item, the value is **-1**.
     * <br>**ArkUI_NodeComponentEvent.data[3].i32**: index of the last child component in the list display area.
     * <br>**ArkUI_NodeComponentEvent.data[4].i32**: area in the list item group where the list display area ends. The
     * type is {@link ArkUI_ListItemGroupArea}.
     * <br>**ArkUI_NodeComponentEvent.data[5].i32**: index of the list item at the end of the list display area in the
     * list item group. If the end of the list display area is not on a list item, the value is **-1**.
     *
     * @since 15
     */
    NODE_LIST_ON_SCROLL_VISIBLE_CONTENT_CHANGE,

    /**
     * @brief Edit mode status change event of the {@link List} component. This event is triggered in the following
     * scenarios:
     * <br>1. {@link NODE_LIST_ENABLE_EDIT_MODE} is set to change the edit mode status.
     * <br>2. {@link NODE_LIST_EDIT_MODE_OPTIONS} is set to enable two-finger swipe for multi-selection.
     * <br>Registering the event callback is the prerequisite for entering the multi-selection state through
     * two-finger swipe. If the event callback is not registered, two-finger swipe will not enter the
     * multi-selection state.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameter:
     * <br>**ArkUI_NodeComponentEvent.data[0].i32**: edit mode status. The value **0** indicates not to enter the
     * edit mode, and **1** indicates to enter edit mode.
     *
     * @since 26.0.0
     */
    NODE_LIST_ON_EDIT_MODE_CHANGE = 1003004,

    /**
     * @brief Defines the selected state change event of the <b>ListItem</b> component.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * {@link ArkUI_NodeComponentEvent} contains one parameter:
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: selected state. <b>0</b>: not selected. <b>1</b>: selected.
     *
     * @since 26.0.0
     */
    NODE_LIST_ITEM_ON_SELECT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST_ITEM,

    /**
     * @brief Defines the event triggered when a child component enters or leaves the ArcList display area.
     *
     * Conditions for triggering the event:\n
     * This event is triggered once when the list is initialized and when the index value of the first or last child
     * component in the ArcList display area changes.\n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.\n
     * {@link ArkUI_NodeComponentEvent} contains 3 parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: index value of the first child component in the ArcList display
     * area.\n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: index value of the last child component in the ArcList display
     * area.\n
     * <b>ArkUI_NodeComponentEvent.data[2].i32</b>: index value of the child component in the middle position of the
     * ArcList display area.\n
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_SCROLL_INDEX = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_LIST,

    /**
     * @brief Event triggered when the **ArcList** component reaches the start position.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_REACH_START = 1019001,

    /**
     * @brief Event triggered when the **ArcList** component reaches the end position.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_REACH_END = 1019002,

    /**
     * @brief Event triggered when the **ArcList** component starts scrolling.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_SCROLL_START = 1019003,

    /**
     * @brief Event triggered when the **ArcList** component stops scrolling.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_SCROLL_STOP = 1019004,

    /**
     * @brief Event triggered when the **ArcList** component is about to scroll. This event is triggered in the
     * following scenarios:
     * <br>1. The **ArcList** component is about to scroll.
     * <br>2. Scrolling is initiated by calling the controller API.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: distance of this scrolling, in vp. A positive value indicates
     * that the content scrolls upwards, and a negative value indicates that the content scrolls downwards.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: current scroll state. The data type is
     * {@link ArkUI_ScrollState}.
     * <br>**ArkUI_NodeComponentEvent.data[2].i32**: scroll source. The parameter type is
     * {@link ArkUI_ScrollSource}.
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_WILL_SCROLL = 1019005,

    /**
     * @brief Event triggered when the **ArcList** component scrolls. This event is triggered in the following
     * scenarios:
     * <br>1. The **ArcList** component scrolls.
     * <br>2. Scrolling is initiated by calling the controller API.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: scrolling distance of this frame, in vp. A positive value
     * indicates that the content scrolls upwards, and a negative value indicates that the content scrolls
     * downwards.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: current scroll state. The data type is
     * {@link ArkUI_ScrollState}.
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_DID_SCROLL = 1019006,

    /**
     * @brief Event triggered when the refresh state of the **ARKUI_NODE_REFRESH** object changes. When the event
     * callback occurs, the union type in the {@link ArkUI_NodeEvent} object is {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameter:
     * <br>**ArkUI_NodeComponentEvent.data[0].i32**: refresh state.
     * <br>**0** (Inactive): This is the default status, indicating that the user has not pulled down the list.
     * <br>**1** (Drag): The user is pulling down the list, and the distance between the current position and the top
     * of the list is less than the refresh distance. If the user releases the list at this time, the component enters
     * the **Inactive** state. If the user continues to pull down the list and the distance between the current
     * position and the top of the list exceeds the refresh distance, the component enters the **OverDrag** state.
     * <br>**2** (OverDrag): The user is pulling down the list, and the distance between the current position and the
     * top of the list exceeds the refresh distance. If the user releases the list at this time, the component enters
     * the **Refresh** state. If the user swipes upward and the pull-down distance is less than the refresh distance,
     * the component enters the **Drag** state.
     * <br>**3** (Refresh): The user has pulled down the list to the refresh distance, and the component enters the **
     * Refresh** state.
     * <br>**4** (Done): The refresh is complete, and the component returns to the initial state (the top of the list).
     *
     */
    NODE_REFRESH_STATE_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_REFRESH,
    /**
     * @brief Event triggered when the **ARKUI_NODE_REFRESH** object enters the refresh state. When the event callback
     * occurs, the union type in the {@link ArkUI_NodeEvent} object is {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     */
    NODE_REFRESH_ON_REFRESH,

    /**
     * @brief Event triggered when the pull-down distance of the **ARKUI_NODE_REFRESH** object changes. When the event
     * callback occurs, the union type in the {@link ArkUI_NodeEvent} object is {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameter:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: drop-down distance.
     *
     */
    NODE_REFRESH_ON_OFFSET_CHANGE,

    /**
     * @brief Event triggered when the **ARKUI_NODE_WATER_FLOW** component is about to scroll. This event is triggered
     * under the following scenarios:
     * <br>1. Scrolling is started by the scrollable component (supports keyboard, mouse, and other input methods that
     * trigger scrolling).
     * <br>2. Scrolling is initiated by calling the controller API.
     * <br>3. The out-of-bounds bounce effect is active.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: scroll offset of each frame. The offset is positive when the
     * content is scrolled up and negative when the content is scrolled down.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: current scroll state. The parameter type is
     * {@link ArkUI_ScrollState}.
     * <br>**ArkUI_NodeComponentEvent.data[2].i32**: current scroll source. The parameter type is
     * {@link ArkUI_ScrollSource}.
     *
     * @return Does not return or returns a number that sets the actual scroll distance of the scroll component. \n
     */
    NODE_ON_WILL_SCROLL = MAX_NODE_SCOPE_NUM * ARKUI_NODE_WATER_FLOW,
    /**
     * @brief Event triggered when the **ARKUI_NODE_WATER_FLOW** component scrolls. This event is triggered under the
     * following scenarios:
     * <br>1. Scrolling is started by the scrollable component (supports keyboard, mouse, and other input methods that
     * trigger scrolling).
     * <br>2. Scrolling is initiated by calling the controller API.
     * <br>3. The out-of-bounds bounce effect is active.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: scroll offset of each frame. The offset is positive when the
     * content is scrolled up and negative when the content is scrolled down.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: current scroll state.
     *
     */
    NODE_WATER_FLOW_ON_DID_SCROLL,
    /**
     * @brief Event triggered when the first or last item displayed in the water flow container changes in **
     * ARKUI_NODE_WATER_FLOW**. This event is triggered under the following scenario:
     * <br>This event is triggered when the index value of the first or last item in the water flow container changes.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].i32**: index of the first item of the water flow container.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: index of the last item of the water flow container.
     *
     */
    NODE_WATER_FLOW_ON_SCROLL_INDEX,

    /**
     * @brief Event triggered when a child component of **ARKUI_NODE_GRID** enters or leaves the grid display area.
     * This event is triggered under the following scenarios:
     * <br>This event is triggered once when the grid is initialized and when the index of the first child component or
     * the last child component in the grid display area changes.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].i32**: index of the first child component in the grid display area.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: index of the last child component in the grid display area.
     *
     * @since 22
     */
    NODE_GRID_ON_SCROLL_INDEX = MAX_NODE_SCOPE_NUM * ARKUI_NODE_GRID,

    /**
     * @brief Event triggered when the **ARKUI_NODE_GRID** component is about to scroll. This event is triggered under
     * the following scenarios:
     * <br>1. Scrolling is started by the scrollable component (supports keyboard, mouse, and other input methods that
     * trigger scrolling).
     * <br>2. Scrolling is initiated by calling the controller API.
     * <br>3. The out-of-bounds bounce effect is active.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: scroll offset of each frame. The offset is positive when the
     * content is scrolled up in the grid and negative when the content is scrolled down.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: current scroll state. The parameter type is
     * {@link ArkUI_ScrollState}.
     * <br>**ArkUI_NodeComponentEvent.data[2].i32**: scroll source. The parameter type is
     * {@link ArkUI_ScrollSource}.
     *
     * @return Returns one or no number to indicate the actual amount by which the scroll component scrolls.
     *
     * @since 22
     */
    NODE_GRID_ON_WILL_SCROLL = 1013001,

    /**
     * @brief Event triggered when the **ARKUI_NODE_GRID** component scrolls. This event is triggered under the
     * following scenarios:
     * <br>1. Scrolling is started by the scrollable component (supports keyboard, mouse, and other input methods that
     * trigger scrolling).
     * <br>2. Scrolling is initiated by calling the controller API.
     * <br>3. The out-of-bounds bounce effect is active.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: scroll offset of each frame. The offset is positive when the
     * content is scrolled up in the grid and negative when the content is scrolled down.
     * <br>**ArkUI_NodeComponentEvent.data[1].i32**: current scroll state. The parameter type is
     * {@link ArkUI_ScrollState}.
     *
     * @since 22
     */
    NODE_GRID_ON_DID_SCROLL = 1013002,

    /**
     * @brief Event triggered at the end of each frame layout of the **ARKUI_NODE_GRID** component, which is used to
     * set the position and length of the scrollbar.
     * <br>When the event callback occurs, the event parameter is {@link ArkUI_NodeEvent}. value.i32 at index 0: index
     * of the first item in the currently displayed grid; obtained using **OH_ArkUI_NodeEvent_GetNumberValue**.
     * <br>value.f32 at index 1: offset of the item at the starting position of the currently displayed grid relative
     * to the starting position of the grid display, in vp; obtained using **OH_ArkUI_NodeEvent_GetNumberValue**.
     *
     * @return Information about the scrollbar position and length. \n
     *     You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     *     value.f32 at index 0: total offset of the grid content relative to the display area, in px. \n
     *     value.f32 at index 1: total length of the grid content, in px. \n
     *
     * @since 22
     */
    NODE_GRID_ON_SCROLL_BAR_UPDATE = 1013003,
    /**
     * @brief **ARKUI_NODE_GRID** component's child drag start event.
     * <br>This event is triggered in the following scenarios:
     * <br>1. **NODE_GRID_EDIT_MODE** is set to **1**.
     * <br>2. A user long-presses and drags a **Grid** child component with sufficient displacement.
     * <br>When the event callback occurs, the event parameter is {@link ArkUI_NodeEvent}.
     * <br>value.f32 at index 0: x-coordinate of the current drag point relative to the **Grid** component, in vp;
     * obtained by calling **OH_ArkUI_NodeEvent_GetNumberValue**.
     * <br>value.f32 at index 1: y-coordinate of the current drag point relative to the **Grid** component, in vp;
     * obtained by calling **OH_ArkUI_NodeEvent_GetNumberValue**.
     * <br>value.i32 at index 2: index of the dragged child component in the **Grid** component; obtained by calling **
     * OH_ArkUI_NodeEvent_GetNumberValue**.
     * <br>You can set the return value using **OH_ArkUI_NodeEvent_SetReturnNumberValue**.
     * <br>value.i32 at index 0 in the return value indicates whether dragging is allowed. **0**: not allowed. **1**:
     * allowed.
     *
     * @return Whether the drag operation is allowed. \n
     *     You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     *     value.i32 at index 0 in the return value indicates whether dragging is allowed.
     *     <b>0</b>: not allowed. <b>1</b>: allowed. \n
     *
     * @since 23
     */
    NODE_GRID_ON_ITEM_DRAG_START = 1013004,

    /**
     * @brief Event triggered when a dragged child component enters this **Grid** component's area.
     * <br>This event is triggered in the following scenario:
     * <br>This event is triggered when a child component is successfully dragged by **NODE_GRID_ON_ITEM_DRAG_START**
     * into this **Grid** component's area.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: x-coordinate of the current drag point relative to the **Grid**
     * component, in vp.
     * <br>**ArkUI_NodeComponentEvent.data[1].f32**: y-coordinate of the current drag point relative to the **Grid**
     * component, in vp.
     *
     * @since 23
     */
    NODE_GRID_ON_ITEM_DRAG_ENTER = 1013005,

    /**
     * @brief Event triggered when a dragged child component moves within this **Grid** component's area.
     * <br>This event is triggered in the following scenario:
     * <br>This event is triggered when a child component is successfully dragged by **NODE_GRID_ON_ITEM_DRAG_START**
     * into this **Grid** component's area.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: x-coordinate of the current drag point relative to the **Grid**
     * component, in vp.
     * <br>**ArkUI_NodeComponentEvent.data[1].f32**: y-coordinate of the current drag point relative to the **Grid**
     * component, in vp.
     * <br>**ArkUI_NodeComponentEvent.data[2].i32**: index of the dragged child component in the source **Grid**
     * component.
     * <br>**ArkUI_NodeComponentEvent.data[3].i32**: index of the dragged child component in this **Grid** component.
     *
     * @since 23
     */
    NODE_GRID_ON_ITEM_DRAG_MOVE = 1013006,

    /**
     * @brief Event triggered when a dragged child component leaves this **Grid** component's area.
     * <br>This event is triggered in the following scenario:
     * <br>This event is triggered when a child component successfully dragged using **NODE_GRID_ON_ITEM_DRAG_START**
     * leaves this **Grid** component's area.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: x-coordinate of the current drag point relative to the **Grid**
     * component, in vp.
     * <br>**ArkUI_NodeComponentEvent.data[1].f32**: y-coordinate of the current drag point relative to the **Grid**
     * component, in vp.
     * <br>**ArkUI_NodeComponentEvent.data[2].i32**: index of the dragged child component in the source **Grid**
     * component.
     *
     * @since 23
     */
    NODE_GRID_ON_ITEM_DRAG_LEAVE = 1013007,

    /**
     * @brief Event triggered when a dragged child component is released.
     * <br>This event is triggered in the following scenario:
     * <br>This event is triggered when a child component successfully dragged using **NODE_GRID_ON_ITEM_DRAG_START**
     * is released.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameters:
     * <br>**ArkUI_NodeComponentEvent.data[0].f32**: x-coordinate of the current drag point relative to the **Grid**
     * component, in vp.
     * <br>**ArkUI_NodeComponentEvent.data[1].f32**: y-coordinate of the current drag point relative to the **Grid**
     * component, in vp.
     * <br>**ArkUI_NodeComponentEvent.data[2].i32**: index of the dragged child component in the source **Grid**
     * component.
     * <br>**ArkUI_NodeComponentEvent.data[3].i32**: index of the dragged child component in this **Grid** component.
     * <br>**ArkUI_NodeComponentEvent.data[4].i32**: whether the dragged child component is successfully released
     * within the **Grid** component's area. **1**: within the **Grid** component's area. **0**: outside the **Grid**
     * component's area.
     *
     * @since 23
     */
    NODE_GRID_ON_ITEM_DROP = 1013008,

    /**
     * @brief Edit mode status change event of the <b>Grid</b> component. This event is triggered in the
     * following scenarios:
     * 1. {@link NODE_GRID_ENABLE_EDIT_MODE} is set to change the edit mode status.
     * 2. {@link NODE_GRID_EDIT_MODE_OPTIONS} is set to enable two-finger swipe for multi-selection.
     * Registering the event callback is the prerequisite for entering the multi-selection state through
     * two-finger swipe. If the event callback is not registered, two-finger swipe will not enter the
     * multi-selection state.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * {@link ArkUI_NodeComponentEvent} contains the following parameter:
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: edit mode status. The value <b>0</b> indicates not to
     * enter the edit mode, and <b>1</b> indicates to enter edit mode.
     *
     * @since 26.0.0
     */
    NODE_GRID_ON_EDIT_MODE_CHANGE = 1013009,

    /**
     * @brief Selected state change event of the **ARKUI_NODE_GRID_ITEM** component.
     * <br>When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}.
     * <br>{@link ArkUI_NodeComponentEvent} contains the following parameter:
     * <br>**ArkUI_NodeComponentEvent.data[0].i32**: **0** (not selected) or **1** (selected).
     *
     * @since 23
     */
    NODE_GRID_ITEM_ON_SELECT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_GRID_ITEM,
    /**
     * @brief Defines the event triggered when an item is selected in the <b>ARKUI_NODE_PICKER</b> component.
     *
     * \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0...11].i32</b>: value of the selected item. \n
     *
     * @since 23
     */
    NODE_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_PICKER,
    /**
     * @brief Event triggered when an item is selected in the <b>Picker</b> container and the scrolling
     * stops.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains the following parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: value of the selected item. \n
     *
     * @since 23
     */
    NODE_PICKER_EVENT_ON_SCROLL_STOP = 1018001,

    /**
     * @brief Defines the event triggered when the index of the currently displayed element of this
     * <b>ARKUI_NODE_ARC_SWIPER</b> instance changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains one parameter:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently displayed element.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_SWIPER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_SWIPER,

    /**
     * @brief Triggered when the transition animation of the arc swipe container
     * (<b>ARKUI_NODE_ARC_SWIPER</b>) starts.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains the following parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently displayed element.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32: index of the target element to switch to.</li>
     * <li>ArkUI_NodeComponentEvent.data[2].f32: offset of the currently displayed element relative to the
     * start position of the <b>Swiper</b> component along the main axis.</li>
     * <li>ArkUI_NodeComponentEvent.data[3].f32: offset of the target element relative to the start
     * position of the <b>Swiper</b> component along the main axis.</li>
     * <li>ArkUI_NodeComponentEvent.data[4].f32: hands-off velocity.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_SWIPER_EVENT_ON_ANIMATION_START,

    /**
     * @brief Defines the event triggered when the switching animation of this <b>ARKUI_NODE_ARC_SWIPER</b> instance
     * ends.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains two parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently displayed element.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32: offset of the currently displayed element relative to the
     * start position of the swiper along the main axis.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_SWIPER_EVENT_ON_ANIMATION_END,

    /**
     * @brief Defines the event triggered on a frame-by-frame basis when the page is turned by a swipe in this
     * <b>ARKUI_NODE_ARC_SWIPER</b> instance.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains two parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently displayed element.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32: offset of the currently displayed element relative to the
     * start position of the swiper along the main axis.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.0.1
     */
    NODE_ARC_SWIPER_EVENT_ON_GESTURE_SWIPE,
} ArkUI_NodeEventType;

/**
 * @brief Obtains the type of a component event.
 *
 * @param event Pointer to the component event.
 * @return Type of the {@link ArkUI_NodeEventType} component event.
 * @since 12
 */
ArkUI_NodeEventType OH_ArkUI_NodeEvent_GetEventType(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the custom ID of a component event.
 *
 * The event ID is passed in as a parameter when the {@link registerNodeEvent} function is called and can be applied
 * to the dispatch logic of the same event entry point function {@link registerNodeEventReceiver}.
 *
 * @param event Pointer to the component event.
 * @return Custom ID of the component event.
 * @since 12
 */
int32_t OH_ArkUI_NodeEvent_GetTargetId(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the component object that triggers an event.
 *
 * @param event Pointer to the component event.
 * @return Component object that triggers the event.
 * @since 12
 */
ArkUI_NodeHandle OH_ArkUI_NodeEvent_GetNodeHandle(ArkUI_NodeEvent* event);

/**
 * @brief Obtains input event (for example, touch event) data for a component event.
 *
 * @param event Pointer to the component event.
 * @return Pointer to the input event data.
 * @since 12
 */
ArkUI_UIInputEvent* OH_ArkUI_NodeEvent_GetInputEvent(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the numerical data in a component event.
 *
 * @param event Pointer to the component event.
 * @return Pointer to the numerical data.
 * @since 12
 */
ArkUI_NodeComponentEvent* OH_ArkUI_NodeEvent_GetNodeComponentEvent(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the string data in a component event.
 *
 * @param event Pointer to the component event.
 * @return Pointer to the string data.
 * @since 12
 */
ArkUI_StringAsyncEvent* OH_ArkUI_NodeEvent_GetStringAsyncEvent(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the ArkUI_TextChangeEvent data from the specified component event.
 *
 * @param event Pointer to the component event. It cannot be null.
 * @return Pointer to the ArkUI_TextChangeEvent object.
 * @since 15
 */
ArkUI_TextChangeEvent* OH_ArkUI_NodeEvent_GetTextChangeEvent(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the custom data in a component event.
 *
 * This parameter is passed in {@link registerNodeEvent} and can be applied to the service logic when the event
 * is triggered.
 *
 * @param event Pointer to the component event.
 * @return Pointer to the custom data.
 * @since 12
 */
void* OH_ArkUI_NodeEvent_GetUserData(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the numeric-type parameter of a component event.
 *
 * @param event Pointer to the component event.
 * @param index Return value index.
 * @param value Pointer to the return value.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE} if the parameter index in the
 *         component event is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID} if the data requested by the caller does not
 *         exist in the component event.
 * @since 12
 */
int32_t OH_ArkUI_NodeEvent_GetNumberValue(ArkUI_NodeEvent* event, int32_t index, ArkUI_NumberValue* value);

/**
 * @brief Obtains the string-type parameter of a component event. The string data is valid only during an event
 * callback. To use it outside an event callback, you are advised to copy the string data.
 *
 * @param event Pointer to the component event.
 * @param index Return value index.
 * @param string Double pointer to the string array.
 * @param stringSize Pointer to the size of the string array.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE} if the parameter index in the
 *         component event is out of range.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID} if the data requested by the caller does not
 *         exist in the component event.
 * @since 12
 */
int32_t OH_ArkUI_NodeEvent_GetStringValue(ArkUI_NodeEvent* event, int32_t index, char** string, int32_t* stringSize);

/**
 * @brief Sets the return value for a component event.
 *
 * @param event Pointer to the component event.
 * @param value Pointer to the event numeric type array.
 * @param size Size of the array.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID} if the data requested by the caller does not
 *         exist in the component event.
 * @since 12
 */
int32_t OH_ArkUI_NodeEvent_SetReturnNumberValue(ArkUI_NodeEvent* event, ArkUI_NumberValue* value, int32_t size);

/**
 * @brief Obtains the touch test information in the component event.
 *
 * @param nodeEvent Pointer to the component event.
 * @return Pointer to the {@link ArkUI_TouchTestInfo} object. If the input parameter is invalid or is not touch test
 *     information, **null** is returned.
 * @since 22
 */
ArkUI_TouchTestInfo* OH_ArkUI_NodeEvent_GetTouchTestInfo(ArkUI_NodeEvent* nodeEvent);

/**
 * @brief Obtains the text content change data of the **TextEditor** component in the component event.
 *
 * @param event Pointer to the {@link ArkUI_NodeEvent} component event object.
 * @return Pointer to the {@link OH_ArkUI_TextEditorChangeEvent} data object.<br>         If the input parameter is
 *     invalid or is not the text content change event information of the **TextEditor** component, **null** is
 *     returned.
 * @since 24
 */
OH_ArkUI_TextEditorChangeEvent* OH_ArkUI_NodeEvent_GetTextEditorOnWillChangeEvent(ArkUI_NodeEvent* event);

/**
 * @brief Enumerates the flags passed to indicate the need to re-execute measurement, layout, or rendering when a
 * custom component calls the <b>::markDirty</b> API.
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief Remeasure.
     *
     * When this type of flag is specified, re-layout is triggered by default.
     */
    NODE_NEED_MEASURE = 1,

    /** Re-layout. */
    NODE_NEED_LAYOUT,
    /** Re-rendering. */
    NODE_NEED_RENDER,
} ArkUI_NodeDirtyFlag;

/**
 * @brief Defines a custom component event. This is a general struct type.
 * This struct is used to pass event information in the measurement, layout, and drawing event callbacks of a
 * custom component.
 *
 * @since 12
 */
typedef struct ArkUI_NodeCustomEvent ArkUI_NodeCustomEvent;

/**
 * @brief Defines the pointer to a component adapter object,
 * which is used for lazy loading of elements in scrollable components.
 * This is applicable to scenarios where a large amount of scrollable content needs to be loaded on demand.
 * It prevents all elements from being created at once, reducing memory usage and improving scrolling performance.
 *
 * @since 12
 */
typedef struct ArkUI_NodeAdapter* ArkUI_NodeAdapterHandle;

/**
 * @brief Defines a component adapter event object, used to pass information such as the event type, host node,
 * and data item index in the event callback of the node adapter.
 *
 * @since 12
 */
typedef struct ArkUI_NodeAdapterEvent ArkUI_NodeAdapterEvent;

/**
 * @brief Enumerates node adapter event types.
 *
 * @since 12
 */
typedef enum {
    /** This event occurs when the component is attached to the adapter. */
    NODE_ADAPTER_EVENT_WILL_ATTACH_TO_NODE = 1,
    /** This event occurs when the component is detached from the adapter. */
    NODE_ADAPTER_EVENT_WILL_DETACH_FROM_NODE = 2,
    /** This event occurs when the adapter obtains the unique ID of the new element to add. */
    NODE_ADAPTER_EVENT_ON_GET_NODE_ID = 3,
    /** This event occurs when the adapter obtains the content of the new element to add. */
    NODE_ADAPTER_EVENT_ON_ADD_NODE_TO_ADAPTER = 4,
    /** This event occurs when the adapter removes an element. */
    NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER = 5,
} ArkUI_NodeAdapterEventType;

/**
 * @brief Creates a component adapter.
 *
 * @since 12
 */
ArkUI_NodeAdapterHandle OH_ArkUI_NodeAdapter_Create();

/**
 * @brief Disposes of a component adapter.
 *
 * @param handle Component adapter object.
 * @since 12
 */
void OH_ArkUI_NodeAdapter_Dispose(ArkUI_NodeAdapterHandle handle);

/**
 * @brief Sets the total number of elements in the specified adapter.
 *
 * @param handle Component adapter object.
 * @param size Number of elements.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_SetTotalNodeCount(ArkUI_NodeAdapterHandle handle, uint32_t size);

/**
 * @brief Obtains the total number of elements in the specified adapter.
 *
 * @param handle Component adapter object.
 * @return Total number of elements in the adapter.
 * @since 12
 */
uint32_t OH_ArkUI_NodeAdapter_GetTotalNodeCount(ArkUI_NodeAdapterHandle handle);

/**
 * @brief Registers an event callback for the specified adapter. After the callback event is no longer needed, you
 * need to call {@link OH_ArkUI_NodeAdapter_UnregisterEventReceiver} to deregister it.
 *
 * @note In versions earlier than API version 26.0.0, if the event receiving callback processes the
 * {@link NODE_ADAPTER_EVENT_WILL_ATTACH_TO_NODE} event, this event will be triggered when the host node is attached to
 * the main tree. You can register an event listener after the **NodeAdapter** is bound to the host node and before the
 * host node is attached to the main tree. In this case, you will receive this event when the host node is attached to
 * the main tree.
 * In API version 26.0.0 and later, this event is triggered immediately when the **NodeAdapter** is bound to the host
 * node, instead of when the host node is attached to the main tree. In this case, the host node may not have been
 * attached to the main tree. If the node on which the callback logic depends has been mounted (for example, accessing
 * layout information or executing animation), you are advised to place the related logic in the **onAppear** callback
 * of the host node. Register an event listener before the **NodeAdapter** is bound to the host node. Otherwise, this
 * event may not be triggered.
 *
 * @param handle Component adapter object.
 * @param userData Pointer to the custom data.
 * @param receiver Event receiving callback.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_RegisterEventReceiver(
ArkUI_NodeAdapterHandle handle, void* userData, void (*receiver)(ArkUI_NodeAdapterEvent* event));

/**
 * @brief Unregisters an event callback for the specified adapter.
 *
 * @param handle Component adapter object.
 * @since 12
 */
void OH_ArkUI_NodeAdapter_UnregisterEventReceiver(ArkUI_NodeAdapterHandle handle);

/**
 * @brief Instructs the specified adapter to reload all elements.
 *
 * @param handle Component adapter object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_ReloadAllItems(ArkUI_NodeAdapterHandle handle);

/**
 * @brief Instructs the specified adapter to reload certain elements.
 *
 * @param handle Component adapter object.
 * @param startPosition Start position of an element change.
 * @param itemCount Number of changed elements.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR if the NodeAdapter requires a listener
 *         to be added.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_ReloadItem(
ArkUI_NodeAdapterHandle handle, uint32_t startPosition, uint32_t itemCount);

/**
 * @brief Instructs the specified adapter to remove certain elements.
 *
 * @param handle Component adapter object.
 * @param startPosition Start position for deleting an element.
 * @param itemCount Number of deleted elements.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR if the NodeAdapter requires a listener
 *         to be added.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_RemoveItem(
ArkUI_NodeAdapterHandle handle, uint32_t startPosition, uint32_t itemCount);

/**
 * @brief Instructs the specified adapter to insert certain elements.
 *
 * @param handle Component adapter object.
 * @param startPosition Start position for inserting an element.
 * @param itemCount Number of inserted elements.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR if the NodeAdapter requires a listener
 *         to be added.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_InsertItem(
ArkUI_NodeAdapterHandle handle, uint32_t startPosition, uint32_t itemCount);

/**
 * @brief Instructs the specified adapter to move certain elements.
 *
 * @param handle Component adapter object.
 * @param from Start position of the element shift.
 * @param to End position of the element shift.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR if the NodeAdapter requires a listener
 *         to be added.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_MoveItem(ArkUI_NodeAdapterHandle handle, uint32_t from, uint32_t to);

/**
 * @brief Obtains all elements stored in the specified adapter. When the API is called, the array object pointer of
 * the element is returned. You must release the memory data to which the pointer points.
 *
 * @param handle Component adapter object.
 * @param items Double pointer to the array of nodes in the adapter.
 * @param size Pointer to the number of elements.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR if the NodeAdapter requires a listener
 *         to be added.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_GetAllItems(ArkUI_NodeAdapterHandle handle, ArkUI_NodeHandle** items, uint32_t* size);

/**
 * @brief Obtains the custom data passed in during registration of the specified event.
 *
 * @param event Pointer to the adapter event object.
 * @return Pointer to the custom data.
 * @since 12
 */
void* OH_ArkUI_NodeAdapterEvent_GetUserData(ArkUI_NodeAdapterEvent* event);

/**
 * @brief Obtains the event type.
 *
 * @param event Pointer to the adapter event object.
 * @return Event type.
 * @since 12
 */
ArkUI_NodeAdapterEventType OH_ArkUI_NodeAdapterEvent_GetType(ArkUI_NodeAdapterEvent* event);

/**
 * @brief Obtains the element to be removed for the event to be destroyed.
 *
 * @param event Pointer to the adapter event object.
 * @return Element to be removed.
 * @since 12
 */
ArkUI_NodeHandle OH_ArkUI_NodeAdapterEvent_GetRemovedNode(ArkUI_NodeAdapterEvent* event);

/**
 * @brief Obtains the index of the element to be operated for the specified adapter event.
 *
 * @param event Pointer to the adapter event object.
 * @return Sequence number of an element.
 * @since 12
 */
uint32_t OH_ArkUI_NodeAdapterEvent_GetItemIndex(ArkUI_NodeAdapterEvent* event);

/**
 * @brief Obtains the scrollable container node that uses the specified adapter.
 *
 * @param event Pointer to the adapter event object.
 * @return Scrollable container node that uses the specified adapter.
 * @since 12
 */
ArkUI_NodeHandle OH_ArkUI_NodeAdapterEvent_GetHostNode(ArkUI_NodeAdapterEvent* event);

/**
 * @brief Sets the component to be added to the specified adapter.
 *
 * @param event Pointer to the adapter event object.
 * @param node Component to be added.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapterEvent_SetItem(ArkUI_NodeAdapterEvent* event, ArkUI_NodeHandle node);

/**
 * @brief Sets the component ID to be generated.
 *
 * @param event Pointer to the adapter event object.
 * @param id Component ID to be returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapterEvent_SetNodeId(ArkUI_NodeAdapterEvent* event, int32_t id);

/**
 * @brief Provides a collection of native-side APIs of the Node type provided by ArkUI, supporting capabilities such as
 * component node creation and destruction, node tree operations, attribute and event management, measurement, and
 * layout. It is suitable for scenarios where native APIs are used to build and operate ArkUI component nodes. APIs
 * related to the Node module must be called on the main thread.
 *
 * @version 1
 * @since 12
 */
typedef struct {
    /**
     * @brief Structure version, that is, the version number of the **ArkUI_NativeNodeAPI_1** structure. The version
     * number is provided by the system and does not need to be modified.
     *
     * @since 12
     */
    int32_t version;

    /**
     * @brief Creates a component based on {@link ArkUI_NodeType} and returns the pointer to the component object.
     *
     * @param type Type of the component to create.
     * @return Pointer to the created component object. If the component fails to be created, **NULL** is returned.
     *     When the component object is no longer needed, call {@link disposeNode} to destroy it. Improper lifecycle
     *     management may cause Use After Free, process crashes, or memory leak.
     * @since 12
     */
    ArkUI_NodeHandle (*createNode)(ArkUI_NodeType type);

    /**
     * @brief Disposes of the component to which the specified pointer points. When calling this API on a non-main
     * thread, special attention must be paid to the lifecycle of the component object to be destroyed. Improper
     * lifecycle management may cause the application to crash; therefore, it is not recommended to call this API on
     * non-main threads.
     *
     * @param node Pointer to a component object.
     * @since 12
     */
    void (*disposeNode)(ArkUI_NodeHandle node);

    /**
     * @brief Attaches a component to a parent node. This API is used for node operations, and you are advised to call
     * this API in the main thread.
     *
     * @param parent Pointer to the parent node.
     * @param child Pointer to the child node.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the operation is not supported for the node
     *     created in ArkTS.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} if the node has been adopted as an affiliated node.
     *     This specification is supported since API version 22.
     * @since 12
     */
    int32_t (*addChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief Removes a component from its parent node. This API is used for node operations, and you are advised to
     * call this API in the main thread.
     *
     * @param parent Pointer to the parent node.
     * @param child Pointer to the child node.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the operation is not supported for the node
     *     created in ArkTS.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ADAPTER_EXIST} if the NodeAdapter already exists.
     * @since 12
     */
    int32_t (*removeChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief Attaches a component to a parent node, with the position after the **sibling** node. This API is used for
     * node operations, and you are advised to call this API in the main thread.
     *
     * @param parent Pointer to the parent node.
     * @param child Pointer to the child node.
     * @param sibling Pointer to the sibling node after which the target node is to be inserted. If the value is null,
     *     the node is inserted at the end of the parent node.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the operation is not supported for the node
     *     created in ArkTS.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} if the node has been adopted as an affiliated node.
     *     This specification is supported since API version 22.
     * @since 12
     */
    int32_t (*insertChildAfter)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, ArkUI_NodeHandle sibling);

    /**
     * @brief Attaches a component to a parent node, with the position before the **sibling** node. This API is used
     * for node operations, and you are advised to call this API in the main thread.
     *
     * @param parent Pointer to the parent node.
     * @param child Pointer to the child node.
     * @param sibling Pointer to the sibling node before which the target node is to be inserted. If the value is null,
     *     the node is inserted at the end of the parent node.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the operation is not supported for the node
     *     created in ArkTS.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} if the node has been adopted as an affiliated node.
     *     This specification is supported since API version 22.
     * @since 12
     */
    int32_t (*insertChildBefore)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, ArkUI_NodeHandle sibling);

    /**
     * @brief Attaches a component to a parent node, with the position specified by **position**. This API is used for
     * node operations, and you are advised to call this API in the main thread.
     *
     * @param parent Pointer to the parent node.
     * @param child Pointer to the child node.
     * @param position Inserting position. The value range is [0, current child count]. If the value is a negative
     *     number or invalid, the component is inserted at the end of the parent node.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the operation is not supported for the node
     *     created in ArkTS.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} if the node has been adopted as an affiliated node.
     *     This specification is supported since API version 22.
     * @since 12
     */
    int32_t (*insertChildAt)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, int32_t position);

    /**
     * @brief Sets attributes. You are advised to call this API in the main thread. In actual service scenarios, if the
     * attributes set for a component contain the heap memory you apply for, ensure that the component no longer uses
     * the heap memory before calling the corresponding release API. For example,
     * **NODE_TEXT_CONTENT_WITH_STYLED_STRING** in {@link ArkUI_NodeAttributeType}.
     *
     * @param node Node whose attribute needs to be set.
     * @param attribute Type of attribute to set.
     * @param item Attribute value to set.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} if the attribute is not supported.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the operation is not supported for the node
     *     created in ArkTS.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ADAPTER_EXIST} if the NodeAdapter already exists.
     * @since 12
     */
    int32_t (*setAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const ArkUI_AttributeItem* item);

    /**
     * @brief Obtains attributes. The pointer returned by this API is an internal buffer pointer of the ArkUI framework.
     * As such, you do not need to call **delete** to free the memory. However, the pointer must be used before this
     * API is called next time. Otherwise, the pointer may be overwritten by other values.
     *
     * @param node Node whose attribute needs to be obtained.
     * @param attribute Type of the attribute to obtain.
     * @return Attribute value. If the operation fails, a null pointer is returned.
     * @since 12
     */
    const ArkUI_AttributeItem* (*getAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

    /**
     * @brief Resets attributes. You are advised to call this API in the main thread.
     *
     * @param node Node whose attribute needs to be reset.
     * @param attribute Type of the attribute to reset.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} if the attribute is not supported.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the operation is not supported for the node
     *     created in ArkTS.
     * @since 12
     */
    int32_t (*resetAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

    /**
     * @brief Registers an event for the specified node. After the event is triggered, it can be received through the
     * component-level callback added by {@link addNodeEventReceiver} or the global callback registered by
     * {@link registerNodeEventReceiver}. When the event is no longer needed, call {@link unregisterNodeEvent} to
     * unregister it.
     *
     * @param node Target node.
     * @param eventType Type of the event to register.
     * @param targetId Custom event ID, which is passed in the callback of {@link ArkUI_NodeEvent} when the event is
     *     triggered.
     * @param userData Custom event parameter, which is passed in the callback of {@link ArkUI_NodeEvent} when the
     *     event is triggered.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} if the event is not supported.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the operation is not supported for the node
     *     created in ArkTS.
     * @since 12
     */
    int32_t (*registerNodeEvent)(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType,
        int32_t targetId, void* userData);

    /**
     * @brief Unregisters an event for the specified node, which is previously registered through
     * {@link registerNodeEvent}. After unregistration, the event no longer triggers the corresponding callback.
     *
     * @param node Target node.
     * @param eventType Type of the event to unregister.
     * @since 12
     */
    void (*unregisterNodeEvent)(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType);

    /**
     * @brief Registers a unified entry point for event callbacks. The ArkUI framework collects component events
     * generated during processing and returns them through the registered **eventReceiver** API.
     * <br>Repeated calls will override the previously registered API.
     * <br>Avoid directly saving pointers to {@link ArkUI_NodeEvent} objects, as the data is destroyed after the
     * callback is complete.
     * <br>To bind with a component instance, you can use the {@link addNodeEventReceiver} API.
     * <br>When the global callback is no longer needed, call {@link unregisterNodeEventReceiver} to unregister it.
     *
     * @param eventReceiver Unified entry point for event callbacks to register.
     * @since 12
     */
    void (*registerNodeEventReceiver)(void (*eventReceiver)(ArkUI_NodeEvent* event));

    /**
     * @brief Unregisters the unified entry point for event callbacks, which is previously registered through
     * {@link registerNodeEventReceiver}. After unregistration, the global entry no longer receives component events.
     *
     * @since 12
     */
    void (*unregisterNodeEventReceiver)();

    /**
     * @brief Forcibly marks the current node for re-measurement, re-layout, or re-drawing. Regarding updates to system
     * attributes, the ArkUI framework automatically marks nodes and re-executes measurement, layout, or drawing; you
     * do not need to call this API actively. This API can be called to trigger the corresponding process when you
     * modify custom measurement, layout, or drawing data that the framework cannot automatically detect.
     *
     * @param node Node object that needs to be marked for re-measurement, re-layout, or re-drawing.
     * @param dirtyFlag Type of the process to be re-executed.
     * @since 12
     */
    void (*markDirty)(ArkUI_NodeHandle node, ArkUI_NodeDirtyFlag dirtyFlag);

    /**
     * @brief Obtains the number of child nodes.
     *
     * @param node Target node.
     * @return Number of child nodes. If there is no child node, **0** is returned.
     * @since 12
     */
    uint32_t (*getTotalChildCount)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains the child node at the specified index.
     *
     * @param node Target node.
     * @param position Zero-based index of the target node in the child node list. The value range is [0, Number of
     *     child nodes - 1). **NULL** is returned if the index is out of range.
     * @return Pointer to the child node at the specified index, or **NULL** if no child node exists at the position.
     * @since 12
     */
    ArkUI_NodeHandle (*getChildAt)(ArkUI_NodeHandle node, int32_t position);

    /**
     * @brief Obtains the first child node.
     *
     * @param node Target node.
     * @return Pointer to the first child node, or **NULL** if there is no child node.
     * @since 12
     */
    ArkUI_NodeHandle (*getFirstChild)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains the last child node.
     *
     * @param node Target node.
     * @return Pointer to the last child node, or **NULL** if there is no child node.
     * @since 12
     */
    ArkUI_NodeHandle (*getLastChild)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains the previous sibling node.
     *
     * @param node Target node.
     * @return Pointer to the previous sibling node, or **NULL** if no previous sibling node exists.
     * @since 12
     */
    ArkUI_NodeHandle (*getPreviousSibling)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains the next sibling node.
     *
     * @param node Target node.
     * @return Pointer to the next sibling node, or **NULL** if no next sibling node exists.
     * @since 12
     */
    ArkUI_NodeHandle (*getNextSibling)(ArkUI_NodeHandle node);

    /**
     * @brief Registers a custom event for a node. After the event is triggered, it can be received through the
     * component-level callback added by {@link addNodeCustomEventReceiver} or the global callback registered by
     * {@link registerNodeCustomEventReceiver}. When the event is no longer needed, call
     * {@link unregisterNodeCustomEvent} to unregister it.
     *
     * @param node Target node.
     * @param eventType Type of the event to register.
     * @param targetId Custom event ID, which is passed in the callback of {@link ArkUI_NodeCustomEvent} when the event
     *     is triggered.
     * @param userData Custom event parameter, which is passed in the callback of {@link ArkUI_NodeCustomEvent} when
     *     the event is triggered.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *     <br>Returns {@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} if the event is not supported.
     * @since 12
     */
    int32_t (*registerNodeCustomEvent)(
        ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType, int32_t targetId, void* userData);

    /**
     * @brief Unregisters a custom event for a node, which is previously registered through
     * {@link registerNodeCustomEvent}. After unregistration, the event no longer triggers the corresponding callback.
     *
     * @param node Target node.
     * @param eventType Type of the event to unregister.
     * @since 12
     */
    void (*unregisterNodeCustomEvent)(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType);

    /**
     * @brief Registers a unified entry point for custom node event callbacks. The ArkUI framework collects custom
     * component events generated during processing and returns them through the custom event entry point function
     * registered using **registerNodeCustomEventReceiver**.
     * <br>Repeated calls will override the previously registered API.
     * <br>Avoid directly saving pointers to {@link ArkUI_NodeCustomEvent} objects, as the data will be destroyed after
     * the callback is complete.
     * <br>To bind with a component instance, you can use the {@link addNodeCustomEventReceiver} API.
     * <br>When the global callback is no longer needed, call {@link unregisterNodeCustomEventReceiver} to unregister
     * it.
     *
     * @param eventReceiver Unified entry point for event callbacks to register.
     * @since 12
     */
    void (*registerNodeCustomEventReceiver)(void (*eventReceiver)(ArkUI_NodeCustomEvent* event));

    /**
     * @brief Unregisters the unified entry point function for custom node event callbacks, which is previously
     * registered through {@link registerNodeCustomEventReceiver}. After unregistration, the global entry no longer
     * receives custom component events.
     *
     * @since 12
     */
    void (*unregisterNodeCustomEventReceiver)();

    /**
     * @brief Sets the width and height of the component after measurement is complete in the measurement callback
     * function.
     *
     * @param node Target node.
     * @param width Width of the component after measurement, in px. If the value is less than 0, 0 is used.
     * @param height Height of the component after measurement, in px. If the value is less than 0, 0 is used.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*setMeasuredSize)(ArkUI_NodeHandle node, int32_t width, int32_t height);

    /**
     * @brief Sets the layout position of the component relative to its parent component in the layout callback
     * function. This API has a lower priority than {@link NODE_POSITION} in **ArkUI_NodeAttributeType**.
     *
     * @param node Target node.
     * @param positionX X-axis layout coordinate of the component relative to its parent component, in px.
     * @param positionY Y-axis layout coordinate of the component relative to its parent component, in px.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*setLayoutPosition)(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY);

    /**
     * @brief Obtains the width and height of a component after measurement.
     *
     * @param node Target node.
     * @return Width and height of the component, wrapped in an **ArkUI_IntSize** struct.
     * @since 12
     */
    ArkUI_IntSize (*getMeasuredSize)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains the offset of a node relative to its parent node after component layout is completed. The unit is
     * px. The offset is the result after the parent container lays out the node. Therefore, the **offset** attribute
     * that takes effect after the layout and the **position** attribute that does not participate in the layout do not
     * affect the offset value.
     *
     * @param node Target node.
     * @return Offset relative to the parent node after the component layout is complete, in px.
     * @since 12
     */
    ArkUI_IntOffset (*getLayoutPosition)(ArkUI_NodeHandle node);

    /**
     * @brief Measures a node. You can use the **getMeasuredSize** API to obtain the size after the measurement.
     *
     * @param node Target node.
     * @param Constraint Pointer to the size constraint used during measurement of the target component. The unit is px.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*measureNode)(ArkUI_NodeHandle node, ArkUI_LayoutConstraint* Constraint);

    /**
     * @brief Lays out a node and specifies the expected position of the node relative to its parent node.
     *
     * @param node Target node.
     * @param positionX Expected X-axis coordinate of the target component relative to its parent component, in px.
     * @param positionY Expected Y-axis coordinate of the target component relative to its parent component, in px.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*layoutNode)(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY);

    /**
     * @brief Adds a component event callback function to a component to receive component events generated by it.
     * Unlike the global registration function **registerNodeEventReceiver**, this API allows multiple event receivers
     * to be added to the same component.
     * <br>The callback added by this function is triggered before the global callback registered by
     * **registerNodeEventReceiver**.
     * <br>Avoid directly saving pointers to {@link ArkUI_NodeEvent} objects, as the data is destroyed after the
     * callback is complete.
     * <br>When the callback is no longer needed, call {@link removeNodeEventReceiver} to remove it.
     *
     * @param node Component for which you want to add the event callback function.
     * @param eventReceiver Event callback for the component.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*addNodeEventReceiver)(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeEvent* event));

    /**
     * @brief Removes the event callback function previously added to the component through
     * {@link addNodeEventReceiver}. After being removed, the callback no longer receives events generated by this
     * component.
     *
     * @param node Component for which you want to remove the event callback function.
     * @param eventReceiver Pointer to the component event callback function to be removed. It must be the same as the
     *     function pointer passed when {@link addNodeEventReceiver} is called.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*removeNodeEventReceiver)(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeEvent* event));

    /**
     * @brief Adds a custom event callback function to a component to receive custom events (such as layout and drawing
     * events) generated by it. Unlike the global registration function **registerNodeCustomEventReceiver**, this API
     * allows multiple event receivers to be added to the same component.
     * <br>The callback added by this function is triggered before the global callback registered by
     * **registerNodeCustomEventReceiver**.
     * <br>Avoid directly saving pointers to {@link ArkUI_NodeCustomEvent} objects, as the data is destroyed after the
     * callback is complete.
     * <br>When the callback is no longer needed, call {@link removeNodeCustomEventReceiver} to remove it.
     *
     * @param node Component for which you want to add the custom event callback function.
     * @param eventReceiver Custom event callback for the component.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*addNodeCustomEventReceiver)(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeCustomEvent* event));

    /**
     * @brief Removes the custom event callback function previously added to the component through
     * {@link addNodeCustomEventReceiver}. After removed, the callback no longer receives custom events generated by
     * this component.
     *
     * @param node Component for which you want to remove the custom event callback function.
     * @param eventReceiver Pointer to the custom component event callback to be removed. It must be the same as the
     *     function pointer passed when {@link addNodeCustomEventReceiver} is called.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*removeNodeCustomEventReceiver)(ArkUI_NodeHandle node,
        void (*eventReceiver)(ArkUI_NodeCustomEvent* event));

    /**
     * @brief Saves custom data on a component.
     *
     * @param node Component on which the custom data will be saved.
     * @param userData Custom data to be saved.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*setUserData)(ArkUI_NodeHandle node, void* userData);

    /**
     * @brief Obtains the custom data stored on a component.
     *
     * @param node Target component.
     * @return Pointer to the user-defined data previously saved on this component through {@link setUserData}.
     * @since 12
     */
    void* (*getUserData)(ArkUI_NodeHandle node);

    /**
     * @brief Sets the unit used when setting length-type attributes of a component through the native API of the Node
     * type. When the service needs to uniformly use px, vp, or fp to set length-type attributes of a component, this
     * API can be called to specify the unit.
     *
     * @param node Component for which you want to set the unit.
     * @param unit Unit type for component length attributes. The default value is
     *     **ARKUI_LENGTH_METRIC_UNIT_DEFAULT**. When the default value is used, the unit for font-related attributes is
     *     fp, and the unit for non-font attributes is vp.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*setLengthMetricUnit)(ArkUI_NodeHandle node, ArkUI_LengthMetricUnit unit);

    /**
     * @brief Obtains the parent node.
     *
     * @param node Target node.
     * @return Pointer to the parent node, or **NULL** if no parent node exists.
     * @since 12
     */
    ArkUI_NodeHandle (*getParent)(ArkUI_NodeHandle node);

    /**
     * @brief Removes all child nodes from the parent component.
     *
     * @param parent Pointer to the parent node.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*removeAllChildren)(ArkUI_NodeHandle parent);
} ArkUI_NativeNodeAPI_1;

/**
 * @brief Obtains the size constraint for measurement through a custom component event.
 *
 * @param event Pointer to the custom component event.
 * @return Pointer to the size constraint.
 * @since 12
 */
ArkUI_LayoutConstraint* OH_ArkUI_NodeCustomEvent_GetLayoutConstraintInMeasure(ArkUI_NodeCustomEvent* event);

/**
 * @brief Obtains the expected position of a component relative to its parent component in the layout phase through a
 * custom component event.
 *
 * @param event Pointer to the custom component event.
 * @return Expected position relative to the parent component.
 * @since 12
 */
ArkUI_IntOffset OH_ArkUI_NodeCustomEvent_GetPositionInLayout(ArkUI_NodeCustomEvent* event);

/**
 * @brief Obtains the drawing context through a custom component event.
 * You need to release the obtained drawing context in a timely manner after use.
 *
 * @param event Pointer to the custom component event.
 * @return Pointer to the drawing context.
 * @since 12
 */
ArkUI_DrawContext* OH_ArkUI_NodeCustomEvent_GetDrawContextInDraw(ArkUI_NodeCustomEvent* event);

/**
 * @brief Obtains the ID of a custom component event.
 *
 * @param event Pointer to the custom component event.
 * @return Custom event ID.
 * @since 12
 */
int32_t OH_ArkUI_NodeCustomEvent_GetEventTargetId(ArkUI_NodeCustomEvent* event);

/**
 * @brief Obtains a custom event parameter through a custom component event.
 *
 * @param event Pointer to the custom component event.
 * @return Pointer to the custom event parameter.
 * @since 12
 */
void* OH_ArkUI_NodeCustomEvent_GetUserData(ArkUI_NodeCustomEvent* event);

/**
 * @brief Obtains a component object through a custom component event.
 *
 * @param event Pointer to the custom component event.
 * @return Component object.
 * @since 12
 */
ArkUI_NodeHandle OH_ArkUI_NodeCustomEvent_GetNodeHandle(ArkUI_NodeCustomEvent* event);

/**
 * @brief Obtains the event type through a custom component event.
 *
 * @param event Pointer to the custom component event.
 * @return Type of the custom component event.
 * @since 12
 */
ArkUI_NodeCustomEventType OH_ArkUI_NodeCustomEvent_GetEventType(ArkUI_NodeCustomEvent* event);

/**
 * @brief Obtains the measurement information of a custom span through a custom component event.
 *
 * @param event Pointer to the custom component event.
 * @param info Pointer to the measurement information to be obtained.
 * @return Returns the result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         <br> A possible cause is that mandatory parameters are left unspecified.
 * @since 12
 */
int32_t OH_ArkUI_NodeCustomEvent_GetCustomSpanMeasureInfo(
    ArkUI_NodeCustomEvent* event, ArkUI_CustomSpanMeasureInfo* info);

/**
 * @brief Sets the measurement metrics of a custom span through a custom component event.
 *
 * @param event Pointer to the custom component event.
 * @param metrics Pointer to the measurement metrics to be set.
 * @return Returns the result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         <br> A possible cause is that mandatory parameters are left unspecified.
 * @since 12
 */
int32_t OH_ArkUI_NodeCustomEvent_SetCustomSpanMetrics(
    ArkUI_NodeCustomEvent* event, ArkUI_CustomSpanMetrics* metrics);

/**
 * @brief Obtains the drawing information of a custom span through a custom component event.
 *
 * @param event Pointer to the custom component event.
 * @param info Pointer to the drawing information to be obtained.
 * @return Returns the result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         <br> A possible cause is that mandatory parameters are left unspecified.
 * @since 12
 */
int32_t OH_ArkUI_NodeCustomEvent_GetCustomSpanDrawInfo(
    ArkUI_NodeCustomEvent* event, ArkUI_CustomSpanDrawInfo* info);

/**
 * @brief Enumerates the event types of NodeContent.
 *
 * @since 12
 */
typedef enum {
    /** Attach event. */
    NODE_CONTENT_EVENT_ON_ATTACH_TO_WINDOW = 0,
    /** Detach event. */
    NODE_CONTENT_EVENT_ON_DETACH_FROM_WINDOW = 1,
} ArkUI_NodeContentEventType;

/**
 * @brief Enumerates inspector error codes.
 * @since 15
 */
typedef enum {
    /**
     * @error Operation successful.
     */
    ARKUI_INSPECTOR_NATIVE_RESULT_SUCCESSFUL = 0,
    /**
     * @error Parameter error.
     */
    ARKUI_INSPECTOR_NATIVE_RESULT_BAD_PARAMETER = -1,
} ArkUI_InspectorErrorCode;

/**
 * @brief Defines a node content event. This is a general struct type.
 * It is used as the event parameter of the node content event callback to obtain the event type and the node content
 * object that triggers the event.
 * @since 12
 */
typedef struct ArkUI_NodeContentEvent ArkUI_NodeContentEvent;

/**
 * @brief Defines a callback for the **NodeContent** event.
 *
 * @param event Pointer to the **NodeContent** event.
 * @since 12
 */
typedef void (*ArkUI_NodeContentCallback)(ArkUI_NodeContentEvent* event);

/**
 * @brief Registers an event callback for **NodeContent**.
 *
 * @param content **NodeContent** object for which a callback needs to be registered.
 * @param callback Callback to be executed when the event is triggered.
 * @return Returns the error code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeContent_RegisterCallback(ArkUI_NodeContentHandle content, ArkUI_NodeContentCallback callback);

/**
 * @brief Obtains the type of the specified **NodeContent** event.
 *
 * @param event Pointer to the **NodeContent** event.
 * @return Type of the **NodeContent** event.
 * @since 12
 */
ArkUI_NodeContentEventType OH_ArkUI_NodeContentEvent_GetEventType(ArkUI_NodeContentEvent* event);

/**
 * @brief Obtains the object that triggers the specified **NodeContent** event.
 *
 * @param event Pointer to the **NodeContent** event.
 * @return **NodeContent** object that triggers the event.
 * @since 12
 */
ArkUI_NodeContentHandle OH_ArkUI_NodeContentEvent_GetNodeContentHandle(ArkUI_NodeContentEvent* event);

/**
 * @brief Saves custom data to the specified **NodeContent** object.
 *
 * @param content **NodeContent** object to which custom data needs to be saved.
 * @param userData Pointer to the custom data to be saved.
 * @return Returns the error code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeContent_SetUserData(ArkUI_NodeContentHandle content, void* userData);

/**
 * @brief Obtains the custom data saved on the specified **NodeContent** object.
 *
 * @param content **NodeContent** object on which custom data needs to be saved.
 * @return Pointer to the custom data.
 * @since 12
 */
void* OH_ArkUI_NodeContent_GetUserData(ArkUI_NodeContentHandle content);

/**
 * @brief Adds an ArkUI component node to the specified **NodeContent** object.
 *
 * @param content **NodeContent** object to which a node is to be added.
 * @param node Node to be added.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} if a child node has been accepted. This specification is
 *     supported since API version 22.
 * @since 12
 */
int32_t OH_ArkUI_NodeContent_AddNode(ArkUI_NodeContentHandle content, ArkUI_NodeHandle node);

/**
 * @brief Removes an ArkUI component node from the specified **NodeContent** object.
 *
 * @param content **NodeContent** object from which a node is to be removed.
 * @param node Node to be removed.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeContent_RemoveNode(ArkUI_NodeContentHandle content, ArkUI_NodeHandle node);

/**
 * @brief Inserts an ArkUI component node into a specific position of the specified **NodeContent** object.
 *
 * @param content **NodeContent** object into which a node is to be inserted.
 * @param node Node to be inserted.
 * @param position Position where a node is to be inserted.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} if a child node has been accepted. This specification is
 *     supported since API version 22.
 * @since 12
 */
int32_t OH_ArkUI_NodeContent_InsertNode(ArkUI_NodeContentHandle content, ArkUI_NodeHandle node, int32_t position);

/**
 * @brief Obtains the layout area size of the component. The size does not count in transformation attributes,
 * such as scale.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param size Pointer to the size of the component handle layout area, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutSize(ArkUI_NodeHandle node, ArkUI_IntSize* size);

/**
 * @brief Obtains the position of the component's layout area relative to its parent component. The relative position
 * does not count in transformation attributes, such as translate.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param localOffset Pointer to the offset of the component handle relative to the parent component, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutPosition(ArkUI_NodeHandle node, ArkUI_IntOffset* localOffset);

/**
 * @brief Obtains the position of the component's layout area relative to the window. The relative position does not
 * count in transformation attributes, such as translate.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param globalOffset Pointer to the offset of the component handle relative to the window, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInWindow(ArkUI_NodeHandle node, ArkUI_IntOffset* globalOffset);

/**
 * @brief Obtains the position of the component's layout area relative to the screen. The relative position does not
 * count in transformation attributes, such as translate.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param screenOffset Pointer to the offset of the component handle relative to the screen, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInScreen(ArkUI_NodeHandle node, ArkUI_IntOffset* screenOffset);

/**
 * @brief Obtains the offset of the specified component relative to the global display. The relative position does not
 * count in transformation attributes, such as translate.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param offset Pointer to the offset of the component handle relative to the screen, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 20
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInGlobalDisplay(ArkUI_NodeHandle node, ArkUI_IntOffset* offset);

/**
 * @brief Obtains the position of the component in the window, including the translate attribute.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param translateOffset Pointer to the accumulated offset of the component handle, its parent component, and its
 *     ancestor node, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetPositionWithTranslateInWindow(ArkUI_NodeHandle node, ArkUI_IntOffset* translateOffset);

/**
 * @brief Obtains the position of the component on the screen, including the translate attribute.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param translateOffset Pointer to the accumulated offset of the component handle, its parent component, and its
 *     ancestor node, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetPositionWithTranslateInScreen(ArkUI_NodeHandle node, ArkUI_IntOffset* translateOffset);

/**
 * @brief Sets a custom property for a component. This API takes effect only in the main thread.
 *
 * @param node **ArkUI_NodeHandle** pointer.
 * @param name Pointer to the name of the custom property. A null pointer is not allowed.
 * @param value Pointer to the value of the custom property corresponding to the key parameter name. A null pointer is
 *     not allowed.
 * @since 13
 */
void OH_ArkUI_NodeUtils_AddCustomProperty(ArkUI_NodeHandle node, const char* name, const char* value);

/**
 * @brief Removes a custom property that has been set for the specified component.
 *
 * @param node **ArkUI_NodeHandle** pointer.
 * @param name Pointer to the name of the custom property.
 * @since 13
 */
void OH_ArkUI_NodeUtils_RemoveCustomProperty(ArkUI_NodeHandle node, const char* name);

/**
 * @brief Obtains the custom property of a component and returns an **ArkUI_CustomProperty** instance through a handle.
 *
 * @param node **ArkUI_NodeHandle** pointer.
 * @param name Pointer to the name of the custom property.
 * @param handle Double pointer to the struct that receives the custom property corresponding to the key parameter name.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 14
 */
int32_t OH_ArkUI_NodeUtils_GetCustomProperty(ArkUI_NodeHandle node, const char* name, ArkUI_CustomProperty** handle);

/**
 * @brief Obtains the parent node, which can be a component node created with ArkTS.
 *
 * @param node Target node object.
 * @return Pointer to the component if the component exists; **NULL** otherwise.
 * @since 14
 */
ArkUI_NodeHandle OH_ArkUI_NodeUtils_GetParentInPageTree(ArkUI_NodeHandle node);

/**
 * @brief Obtains the FrameNode child node whose internal active state is **true** and generates an
 * {@link ArkUI_ActiveChildrenInfo} instance. Spans are not counted as child nodes.
 *
 * After the child node is obtained, you can call {@link OH_ArkUI_ActiveChildrenInfo_GetCount} to obtain the number of
 * child nodes and call {@link OH_ArkUI_ActiveChildrenInfo_GetNodeByIndex} to read the child nodes by index. After the
 * instance is used, you must call {@link OH_ArkUI_ActiveChildrenInfo_Destroy} to destroy it. In **LazyForEach**
 * scenarios, you are advised to use the {@link OH_ArkUI_NodeUtils_GetChildWithExpandMode} API for traversal.
 *
 * @param head Node for which to obtain the child nodes.
 * @param handle Double pointer to the struct containing information about the child nodes of the head node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 14
 */
int32_t OH_ArkUI_NodeUtils_GetActiveChildrenInfo(ArkUI_NodeHandle head, ArkUI_ActiveChildrenInfo** handle);

/**
 * @brief Obtains the root node of the current page.
 *
 * @param node Target node object.
 * @return Pointer to the root node if the node exists; **NULL** otherwise.
 * @since 14
 */
ArkUI_NodeHandle OH_ArkUI_NodeUtils_GetCurrentPageRootNode(ArkUI_NodeHandle node);

/**
 * @brief Checks whether the specified component is created with C APIs.
 *
 * @param node Target node object.
 * @return Whether the node is created with the C API. The value **true** means that the node is created with the C API,
 *      and **false** means the opposite.
 * @since 14
 */
bool OH_ArkUI_NodeUtils_IsCreatedByNDK(ArkUI_NodeHandle node);

/**
 * @brief Obtains the type of the specified node.
 *
 * @param node Target node object.
 * @return Type of the node. Returns **-1** if the type is not supported yet. For details about the available types,
 *     see {@link ArkUI_NodeType}.
 * @since 14
 */
int32_t OH_ArkUI_NodeUtils_GetNodeType(ArkUI_NodeHandle node);

/**
 * @brief Obtains the information about the window to which a node belongs.
 *
 * @param node Target node object.
 * @param info Double pointer to the window information object. The memory allocated for this object must be released
 *     using {@link OH_ArkUI_HostWindowInfo_Destroy}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if a C API initialization error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} if the node is not mounted to the node tree.
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetWindowInfo(ArkUI_NodeHandle node, ArkUI_HostWindowInfo** info);

/**
 * @brief Obtains the index of the first child node of the target node in the tree without expanding any nodes.
 *
 * @param node Pointer to the target node.
 * @param index Pointer to the index of the child node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetFirstChildIndexWithoutExpand(ArkUI_NodeHandle node, uint32_t* index);

/**
 * @brief Obtains the index of the last child node of the target node in the tree without expanding any nodes.
 *
 * @param node Pointer to the target node.
 * @param index Pointer to the index of the child node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetLastChildIndexWithoutExpand(ArkUI_NodeHandle node, uint32_t* index);

/**
 * @brief Obtains a child node at the specified index using different expansion modes.
 *
 * @param node Pointer to the target node.
 * @param position Index of the child node to obtain.
 * @param subnode Pointer to the obtained child node.
 * @param expandMode Expansion mode for node traversal. For details, see {@link ArkUI_ExpandMode}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetChildWithExpandMode(ArkUI_NodeHandle node, int32_t position,
    ArkUI_NodeHandle* subnode, uint32_t expandMode);

/**
 * @brief Collapses the list items in the expanded state.
 *
 * @param node Node object for which an event needs to be registered.
 * @param userData Pointer to the custom event parameter, which is passed in the callback when the event is triggered.
 * @param onFinish Pointer to the callback invoked when the collapse animation is complete.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} if the event is not supported.
 * @since 12
 */
int32_t OH_ArkUI_List_CloseAllSwipeActions(ArkUI_NodeHandle node, void* userData, void (*onFinish)(void* userData));

/**
 * @brief Obtains the pointer to the UI context object of the specified node.
 *
 * @param node Specified node.
 * @return Pointer to the UI context object.
 *         If a null pointer is returned, it may be because the node is empty.
 * @since 12
 */
ArkUI_ContextHandle OH_ArkUI_GetContextByNode(ArkUI_NodeHandle node);

/**
 * @brief Registers an event listener for system color mode changes. A single component can only register one callback
 *        for system color mode changes. For implementation examples, see Adding an Event Listener.
 *
 * @param node Specified node.
 * @param userData Pointer to the custom event parameter, which is passed in the callback when the event is triggered.
 * @param onColorModeChange Pointer to the callback to be executed when the event is triggered.
 *        {@link ArkUI_SystemColorMode} defines the system color mode (light/dark).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_RegisterSystemColorModeChangeEvent(ArkUI_NodeHandle node,
    void* userData, void (*onColorModeChange)(ArkUI_SystemColorMode colorMode, void* userData));

/**
 * @brief Unregisters the event listener for system color mode changes.
 *
 * @param node Specified node.
 * @since 12
 */
void OH_ArkUI_UnregisterSystemColorModeChangeEvent(ArkUI_NodeHandle node);

/**
 * @brief Registers an event listener for system font style changes. A single component can only register one callback
 *        for system font style changes.
 *
 * @param node Specified node.
 * @param userData Pointer to the custom event parameter, which is passed in the callback when the event is triggered.
 * @param onFontStyleChange Pointer to the callback to be executed when the event is triggered.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_RegisterSystemFontStyleChangeEvent(ArkUI_NodeHandle node,
    void* userData, void (*onFontStyleChange)(ArkUI_SystemFontStyleEvent* event, void* userData));

/**
 * @brief Unregisters the event listener for system font style changes.
 *
 * @param node Specified node.
 * @since 12
 */
void OH_ArkUI_UnregisterSystemFontStyleChangeEvent(ArkUI_NodeHandle node);

/**
 * @brief Obtains the font size in the system font style change event.
 *
 * @param event Pointer to the current system font style change event.
 * @return Font size scale after the change. Default value: **1.0**.
 * @since 12
 */
float OH_ArkUI_SystemFontStyleEvent_GetFontSizeScale(const ArkUI_SystemFontStyleEvent* event);

/**
 * @brief Obtains the font weight in the system font style change event.
 *
 * @param event Pointer to the current system font style change event.
 * @return Font weight scale after the change. Default value: **1.0**.
 * @since 12
 */
float OH_ArkUI_SystemFontStyleEvent_GetFontWeightScale(const ArkUI_SystemFontStyleEvent* event);

/**
 * @brief Obtains the target node based on the provided user ID.
 *
 * @param id ID of the target node.
 * @param node Pointer to the target node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetAttachedNodeHandleById(const char* id, ArkUI_NodeHandle* node);

/**
 * @brief Moves a node to a target parent node as a child.
 *
 * @param node Node to be moved.
 * @param target_parent Pointer to the target parent node.
 * @param index Index of the node after the movement. If the index is invalid, the node will be added to the end of the
 *     target parent node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if a C API initialization error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} if a child node has been accepted. This specification is
 *     supported since API version 22.
 * @since 18
 */
int32_t OH_ArkUI_NodeUtils_MoveTo(ArkUI_NodeHandle node, ArkUI_NodeHandle target_parent, int32_t index);

/**
 * @brief Triggers the node attribute update in this frame.
 *
 * If the attributes of the current node are modified after the build phase, these changes do not take effect
 * immediately but are deferred for batch processing in the next frame.
 *
 * This API forces immediate node updates within the current frame, ensuring that rendering effects are applied
 * synchronously.
 *
 * @param node Node whose attributes are to be updated.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_InvalidateAttributes(ArkUI_NodeHandle node);

/**
 * @brief Sets the cross-language option for the target node.
 *
 * @param node Pointer to the target node.
 * @param option Pointer to the cross-language configuration option ({@link ArkUI_CrossLanguageOption}).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_SetCrossLanguageOption(ArkUI_NodeHandle node, ArkUI_CrossLanguageOption* option);

/**
 * @brief Obtains the cross-language option of the target node.
 *
 * @param node Pointer to the target node.
 * @param option Pointer to the cross-language configuration option ({@link ArkUI_CrossLanguageOption}).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetCrossLanguageOption(ArkUI_NodeHandle node, ArkUI_CrossLanguageOption* option);

/**
 * @brief Registers a layout completion callback function for a specific node.
 *
 * @param node Target node for which the callback function is to be registered.
 * @param userData Pointer to the custom parameter passed to the callback function when it is invoked.
 * @param onLayoutCompleted Pointer to the callback function to be invoked when layout is completed.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_RegisterLayoutCallbackOnNodeHandle(ArkUI_NodeHandle node,
    void* userData, void (*onLayoutCompleted)(void* userData));


/**
 * @brief Registers a drawing completion callback function for a specific node.
 *
 * @param node Target node for which the callback function is to be registered.
 * @param userData Pointer to the custom parameter passed to the callback function when it is invoked.
 * @param onDrawCompleted Pointer to the callback function to be invoked when drawing is completed.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_RegisterDrawCallbackOnNodeHandle(ArkUI_NodeHandle node,
    void* userData, void (*onDrawCompleted)(void* userData));

/**
 * @brief Unregisters the layout completion callback function for a specific node.
 *
 * @param node Target node for which the callback function is to be unregistered.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_UnregisterLayoutCallbackOnNodeHandle(ArkUI_NodeHandle node);

/**
 * @brief Unregisters the drawing completion callback function for a specific node.
 *
 * @param node Target node for which the callback function is to be unregistered.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_UnregisterDrawCallbackOnNodeHandle(ArkUI_NodeHandle node);

/**
 * @brief Obtains a snapshot of a given component. If the node is not in the component tree or has not been rendered,
 * the snapshot operation will fail. When the PixelMap is no longer used, you should call
 * {@link OH_PixelmapNative_Release} to release it.
 *
 * @param node Target node to capture a snapshot.
 * @param snapshotOptions Pointer to the snapshot configuration. If the value is null, the default configuration is
 *         used.<br>The screenshot configuration includes the scaling attribute, color space, and dynamic range mode.
 *         The color space and dynamic range mode are supported since API version 23.<br>The scaling attribute value is
 *         a floating point number greater than 0. The default value is **1.0**.<br>The color space value can be **3**
 *         (RGB color gamut is of the Display P3 type), **4** (RGB color gamut is of the SRGB type), or **27** (RGB
 *         color gamut is of the Display BT2020 type). The default value is **4**.<br> The dynamic range mode value is
 *         specified using {@link ArkUI_DynamicRangeMode}. The default value is
 *         **ARKUI_DYNAMIC_RANGE_MODE_STANDARD**.
 * @param pixelmap Pointer to the Pixelmap created by the system.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_INTERNAL_ERROR} if the snapshot fails, returning a null pointer.
 *     <br>Returns {@link ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT} if the snapshot operation times out.
 *     <br>Returns {@link ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_MODE_NOT_SUPPORTED} if the color space or dynamic range
 *         mode set in the screenshot options is not supported.
 *     <br>Returns {@link ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_AUTO_NOT_SUPPORTED} if the **isAuto** parameter of the
 *         color space or dynamic range mode cannot be set to **true** for the offscreen node snapshot.
 * @since 15
 */
int32_t OH_ArkUI_GetNodeSnapshot(ArkUI_NodeHandle node, ArkUI_SnapshotOptions* snapshotOptions,
    OH_PixelmapNative** pixelmap);

/**
 * @brief Obtains the size limit of a component screenshot.
 *
 * @param maxWidth Pointer to the maximum width of a component screenshot, in px.
 * @param maxHeight Pointer to the maximum height of a component screenshot, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
int32_t OH_ArkUI_GetNodeSnapshotSizeLimitation(int32_t* maxWidth, int32_t* maxHeight);

/**
 * @brief Obtains the offset of the target node relative to its parent node, in px.
 *
 * @param node Target node.
 * @param globalOffset Pointer to the offset of the target node relative to its parent node, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetPositionToParent(ArkUI_NodeHandle node, ArkUI_IntOffset* globalOffset);

/**
 * @brief Adds the polymorphic style states supported by the component. To handle states efficiently, specify the
 * states of interest and their corresponding handlers. When a state of interest occurs, the handler will be executed.
 * You can adjust the UI style based on the current state within the callback. If this API is called multiple times on
 * the same node, the last set of states and handlers will take precedence. Some component types have default system
 * handling for certain states. For example, the **Button** component has a default style effect for the PRESSED state.
 * When custom state handling is implemented on such components, the default style effect will be applied first,
 * followed by the custom style changes, resulting in a combined effect. To disable the default style effects, set
 * **excludeInner** to **true**, if this is allowed by the system implementation. When this API is called, the provided
 * handler function will be executed immediately. There is no need to explicitly register a listener for the NORMAL
 * state. Once a non-NORMAL state is registered, the system will automatically notify your application when the state
 * changes back to NORMAL.
 *
 * @param node Target node.
 * @param uiStates Target UI states to be handled on the node. The combination of all target UI states can be
 *     calculated using the **\|** operator. Example: targetUIStates = ArkUI_UIState::PRESSED \| ArkUI_UIState::FOCUSED
 * @param statesChangeHandler Handler for UI state changes. It returns the current UI status. The value is the result
 *     of combining all current state enum values using the **\|** operator. You can determine the state using the
 *     **&** operator. Example: **if (currentStates & ArkUI_UIState::PRESSED == ArkUI_UIState::PRESSED)**. However, for
 *     checking the normal state, use the equality operator directly. Example:
 *     **if (currentStates == ArkUI_UIState::NORMAL)**.
 * @param excludeInner Whether to disable the default state styles. **true**: Disable the default state styles.
 *     **false**: Do not disable the default state styles.
 * @param userData Pointer to the custom data used in the **onDrawCompleted** callback.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_AddSupportedUIStates(ArkUI_NodeHandle node, int32_t uiStates,
    void (statesChangeHandler)(int32_t currentStates, void* userData), bool excludeInner, void* userData);

/**
 * @brief Removes registered UI states. When all states registered using **OH_ArkUI_AddSupportedUIStates** are removed,
 * the registered **stateChangeHandler** will no longer be executed.
 *
 * @param node Target node.
 * @param uiStates Target UI states to be removed.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_RemoveSupportedUIStates(ArkUI_NodeHandle node, int32_t uiStates);

/**
 * @brief Executes the specified callback in the target UI context. For the implementation example, see Ensuring
 * Multi-Instance Functionality in the NDK.
 *
 * @param uiContext Pointer to the target UI context.
 * @param userData Pointer to the user-defined data for processing custom data within the callback function. You are
 *     responsible for ensuring the validity of the data when the custom function is executed.
 * @param callback Pointer to the user-defined callback function.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if the **UIContext** object is invalid.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CALLBACK_INVALID} if the callback function is invalid.
 * @since 20
 */
int32_t OH_ArkUI_RunTaskInScope(ArkUI_ContextHandle uiContext, void* userData, void(*callback)(void* userData));

/**
 * @brief Obtain a node by its unique ID.
 *
 * @param uniqueId Unique ID of the target node.
 * @param node Pointer to the target node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_NodeUtils_GetNodeHandleByUniqueId(const uint32_t uniqueId, ArkUI_NodeHandle* node);

/**
 * @brief Obtains the unique ID of the target node.
 *
 * @param node ArkUI node pointer.
 * @param uniqueId Pointer to the unique ID of the target node. The component ID is read-only and unique in the process.
 *     If the node exists, the unique ID of the node is returned. Otherwise, **-1** is returned.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 20
 */
int32_t OH_ArkUI_NodeUtils_GetNodeUniqueId(ArkUI_NodeHandle node, int32_t* uniqueId);

/**
 * @brief Obtains whether a node is in the render state. If RenderNode of a node is in the render tree, the node is in
 * the render state.
 *
 * @param node ArkUI node pointer.
 * @param isInRenderState Pointer to the **isInRenderState** parameter indicating whether the node is in render state. *
 *     *true**: The node is in the render state. **false**: The node is not in the render state.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_IsInRenderState(ArkUI_NodeHandle node, bool* isInRenderState);

/**
 * @brief Adopts the target node as an affiliated node. The adopted node must not have an existing parent. This API is
 * not used to add a node as a child node. Instead, it only allows the node to receive lifecycle callbacks of the
 * corresponding child node.
 *
 * @param node **ArkUI_NodeHandle** pointer, which specifies the parent node of the node to be adopted.
 * @param child **ArkUI_NodeHandle** pointer, which specifies the child node to be adopted.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_HAS_PARENT} if the adopted node already has a parent node.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_CAN_NOT_BE_ADOPTED} if the node cannot be adopted as an affiliated node.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_CAN_NOT_ADOPT_TO} if the node cannot adopt other affiliated nodes.
 * @since 22
 */
int32_t OH_ArkUI_NativeModule_AdoptChild(ArkUI_NodeHandle node, ArkUI_NodeHandle child);

/**
 * @brief Removes a previously-adopted affiliated node.
 *
 * @param node **ArkUI_NodeHandle** pointer, which specifies the parent node.
 * @param child **ArkUI_NodeHandle** pointer, which specifies the child node to be removed.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_IS_NOT_IN_ADOPTED_CHILDREN} if the node is not an affiliated node
 *     adopted by the target node.
 * @since 22
 */
int32_t OH_ArkUI_NativeModule_RemoveAdoptedChild(ArkUI_NodeHandle node, ArkUI_NodeHandle child);

/**
 * @brief Sets the color inversion algorithm for the component and instance. For details, see Using Color Inversion for
 * Quick Dark Mode Adaptation.
 *
 * @param uiContext Pointer to the UI instance object.<br>  If the value is **null**, this function applies to the
 *     entire application process.
 * @param forceDark Whether to use the color inversion capability. **true** to use; **false** otherwise.
 * @param nodeType Component scope where the color inversion capability takes effect.<br>   **ARKUI_NODE_UNDEFINED**
 *     indicates that the setting takes effect for all component types.
 * @param colorInvertFunc Pointer to the custom color inversion algorithm function.<br> If the value is **nullptr**,
 *     the default color inversion algorithm is used for the component, that is, the three primary colors are inverted.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if a C API initialization error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_FORCE_DARK_CONFIG_INVALID} if the input parameter of the color inversion
 *         capability is incorrect.
 * @since 20
 */
int32_t OH_ArkUI_SetForceDarkConfig(ArkUI_ContextHandle uiContext, bool forceDark, ArkUI_NodeType nodeType,
    uint32_t (*colorInvertFunc)(uint32_t color));

/**
 * @brief Registers a basic event callback for the target node.
 *
 * Currently, the following event types are supported: **NODE_ON_CLICK_EVENT**, **NODE_TOUCH_EVENT**,
 * **NODE_EVENT_ON_APPEAR**, **NODE_EVENT_ON_DISAPPEAR**, **NODE_ON_KEY_EVENT**, **NODE_ON_FOCUS**, **NODE_ON_BLUR**,
 * **NODE_ON_HOVER**, **NODE_ON_MOUSE**, and **NODE_ON_SIZE_CHANGE**. For details, see
 * {@link ArkUI_NodeEventType}.
 *
 * @param node Target node.
 * @param eventType Event type.
 * @param userData Pointer to the user-defined data for processing custom data within the callback function. You are
 *     responsible for ensuring the validity of the data when the custom function is executed.
 * @param callback Pointer to the user-defined callback function.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_UNSUPPORTED_EVENT_TYPE} if the event type is not supported.
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_RegisterCommonEvent(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType,
    void* userData, void (*callback)(ArkUI_NodeEvent* event));

/**
 * @brief Unregisters the basic event callback for the target node.
 *
 * For details about the supported event types, see {@link OH_ArkUI_NativeModule_RegisterCommonEvent}.
 *
 * @param node Target node.
 * @param eventType Event type.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_UNSUPPORTED_EVENT_TYPE} if the event type is not supported.
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_UnregisterCommonEvent(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType);

/**
 * @brief Registers a basic event callback for visible area changes with a constrained callback interval.
 *
 * @param node Target node.
 * @param ratios Pointer to the array of threshold ratios, representing the visible area of the component.
 * @param size Size of the array of threshold ratios.
 * @param expectedUpdateInterval Expected calculation interval.
 * @param userData Pointer to the user-defined data for processing custom data within the callback function. You are
 *     responsible for ensuring the validity of the data when the custom function is executed.
 * @param callback Pointer to the user-defined callback function.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_RegisterCommonVisibleAreaApproximateChangeEvent(ArkUI_NodeHandle node, float* ratios,
    int32_t size, float expectedUpdateInterval, void* userData, void (*callback)(ArkUI_NodeEvent* event));

/**
 * @brief Unregisters the basic event callback for visible area changes with a constrained callback interval.
 *
 * @param node Target node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_UnregisterCommonVisibleAreaApproximateChangeEvent(ArkUI_NodeHandle node);

/**
 * @brief Converts the coordinates of a point from the coordinate system of a specified node to that of the current
 * window. For a coordinate system of a node, transformation of the node is considered. For example, if node A is
 * translated leftward by 100, the coordinates of the points in its coordinate system will also be translated leftward
 * by 100.
 *
 * [](docroot://reference/apis-arkui/figures/ConvertToWindow.png)
 *
 * As shown in the preceding figure, the coordinates (x0, y0) in the coordinate system of the specified node are
 * converted to the coordinates (x1, y1) in the coordinate system of the window.
 *
 * @param currentNode Specified node.
 * @param localPosition Coordinates of the point in the coordinate system of the specified node, in px.
 * @param windowPosition Pointer to the converted coordinates (in the current window coordinate system, in px).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} if the node is not mounted on the main component tree.
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_ConvertPositionToWindow(ArkUI_NodeHandle currentNode, ArkUI_IntOffset localPosition,
    ArkUI_IntOffset* windowPosition);

/**
 * @brief Converts the coordinates of a point from the current window's coordinate system to the target node's
 * coordinate system. For a coordinate system of a node, transformation of the node is considered. For example, if node
 * A is translated leftward by 100, the coordinates of the points in its coordinate system will also be translated
 * leftward by 100.
 *
 * [](docroot://reference/apis-arkui/figures/ConvertFromWindow.png)
 *
 * As shown in the preceding figure, the coordinates (x1, y1) in the window coordinate system are converted to the
 * coordinates (x0, y0) in the coordinate system of the target node.
 *
 * @param targetNode Target node.
 * @param windowPosition Coordinates of the point in the current window coordinate system, in px.
 * @param localPosition Pointer to the converted coordinates (in the coordinate system of the target node, in px).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} if the node is not mounted on the main component tree.
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_ConvertPositionFromWindow(ArkUI_NodeHandle targetNode, ArkUI_IntOffset windowPosition,
    ArkUI_IntOffset* localPosition);

/**
 * @brief Stops the page turning animation that is being executed on the specified **Swiper** node.
 *
 * @param node Specified node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
int32_t OH_ArkUI_Swiper_FinishAnimation(ArkUI_NodeHandle node);

/**
 * @brief Submits the **asyncUITask** function to a non-UI thread provided by the ArkUI framework for execution. After
 * **asyncUITask** finishes execution, the **onFinish** function is called in the UI thread.
 *
 * This is suitable for scenarios involving multi-threaded UI component creation. You can use this API to create UI
 * components in non-UI threads and then mount the created components to the main tree in the UI thread.
 *
 * @param context Pointer to the UI instance object.
 * @param asyncUITaskData Pointer to the user-defined data, which is passed as the input parameter of **asyncUITask**
 *     and **onFinish**. A null pointer is allowed.
 * @param asyncUITask Pointer to the function executed in the non-UI thread.
 * @param onFinish Pointer to the function executed on the UI thread after **asyncUITask** is completed. A null pointer
 *     is allowed.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the context object is invalid, or **asyncUITask** is a
 *     null pointer.
 * @since 22
 */
int32_t OH_ArkUI_PostAsyncUITask(ArkUI_ContextHandle context, void* asyncUITaskData,
    void (*asyncUITask)(void* asyncUITaskData), void (*onFinish)(void* asyncUITaskData));

/**
 * @brief Submits the **task** function to the UI thread for execution.
 *
 * This is suitable for scenarios involving multi-threaded UI component creation. When you create UI components in a
 * self-built thread, you can use this API to mount the created components to the main tree on the UI thread.
 *
 * @param context Pointer to the UI instance object.
 * @param taskData Pointer to the user-defined data, which is passed as the input parameter of **task**. A null pointer
 *     is allowed.
 * @param task Pointer to the function executed in the UI thread.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the context object is invalid, or **task** is a null
 *     pointer.
 * @since 22
 */
int32_t OH_ArkUI_PostUITask(ArkUI_ContextHandle context, void* taskData, void (*task)(void* taskData));

/**
 * @brief Sets the visibility of the menu bar.
 *
 * @param uiContext ArkUI context handle, which specifies the context of the ArkUI container.
 * @param visible Whether the menu bar is visible. The value **true** indicates that the menu bar is visible, and
 *     **false** indicates the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if an instance error occurs (for example, the
 *         **uiContext** pointer is null, the container cannot be obtained through **uiContext**, or **uiContext** does
 *         not belong to atomic services).
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_AtomicServiceMenuBarSetVisible(ArkUI_ContextHandle uiContext, bool visible);

/**
 * @brief Registers a callback for listening for component size and area changes. This API can be called for a valid
 * {@link ArkUI_NodeHandle} node at any time. The newly registered callback will replace the previously registered
 * callback for this event and take effect from the next frame. When the callback is no longer needed, use
 * {@link OH_ArkUI_NativeModule_UnregisterCommonAreaApproximateChangeEvent} to unregister it. Otherwise, the callback
 * will be automatically unregistered when the node is released.
 *
 * @param node {@link ArkUI_NodeHandle} pointer.
 * @param expectedUpdateInterval Interval at which the callback is triggered by the expected calculation area change,
 *     in ms.
 * @param userData Pointer to the custom data.
 * @param callback Pointer to the event callback.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
int32_t OH_ArkUI_NativeModule_RegisterCommonAreaApproximateChangeEvent(ArkUI_NodeHandle node,
    float expectedUpdateInterval, void* userData, void (*callback)(ArkUI_NodeEvent* event));

/**
 * @brief Unregisters the callback for listening for component size and area changes.
 *
 * @param node {@link ArkUI_NodeHandle} pointer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
int32_t OH_ArkUI_NativeModule_UnregisterCommonAreaApproximateChangeEvent(ArkUI_NodeHandle node);

/**
 * @brief Submits the **task** function to the UI thread for execution. The thread calling this API will block until
 * the **task** function completes execution. Calling this API from the UI thread is equivalent to synchronously
 * calling the **task** function.
 *
 * This is suitable for scenarios involving multi-threaded UI component creation. When you need to call functions that
 * are only supported on the UI thread during the multi-threaded component creation process, you can use this API to
 * return to the UI thread to call the function and then resume multi-threaded component creation after the call
 * completes.
 *
 * When the UI thread is under high load, non-UI threads calling this API may block for extended periods, affecting the
 * performance of multi-threaded UI component creation. Frequent use is not recommended.
 *
 * @param context Pointer to the UI instance object.
 * @param taskData Pointer to the user-defined data, which is passed as the input parameter of **task**. A null pointer
 *     is allowed.
 * @param task Pointer to the function executed in the UI thread.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the context object is invalid, or **task** is a null
 *     pointer.
 * @since 22
 */
int32_t OH_ArkUI_PostUITaskAndWait(ArkUI_ContextHandle context, void* taskData, void (*task)(void* taskData));

/**
 * @brief Starts a simulated drag on a **Swiper** node. {@link OH_ArkUI_Swiper_FakeDragBy} can be used to simulate a
 * drag action. {@link OH_ArkUI_Swiper_StopFakeDrag} can be used to stop the drag simulation.<br> A simulated drag can
 * be interrupted by a real drag. To ignore a drag event from a user during the simulated drag, use
 * {@link NODE_SWIPER_DISABLE_SWIPE}.
 *
 * @param node Specified node.
 * @param isSuccessful Pointer to the **isSuccessful** parameter indicating whether the simulated drag is successfully
 *     started. **true** is returned if the simulated drag is successfully started.<br> **false** is returned if
 *     **Swiper** is not ready to start the simulated drag or a real drag or simulated drag is in progress.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_StartFakeDrag(ArkUI_NodeHandle node, bool* isSuccessful);

/**
 * @brief Simulates the drag effect by setting the offset of a **Swiper** node. Before calling this API, you must call
 * {@link OH_ArkUI_Swiper_StartFakeDrag} to start the drag simulation.
 *
 * @param node Specified node.
 * @param offset Offset to be dragged, in vp.
 * @param isConsumedOffset Pointer to the **isConsumedOffset** parameter indicating whether to consume the offset to
 *     trigger dragging. **true** is returned if the offset is consumed to trigger dragging.<br> **false** is returned
 *     if the dragging is not in progress or no offset is consumed.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_FakeDragBy(ArkUI_NodeHandle node, float offset, bool* isConsumedOffset);

/**
 * @brief Stops the drag simulation on a **Swiper** node.
 *
 * @param node Specified node.
 * @param isSuccessful Pointer to the **isSuccessful** parameter indicating whether the simulated drag is successfully
 *     stopped. **true** is returned if the simulated drag is successfully stopped.<br> **false** is returned if
 *     **Swiper** is not ready to stop the simulated drag or no simulated drag is in progress.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_StopFakeDrag(ArkUI_NodeHandle node, bool* isSuccessful);

/**
 * @brief Obtains the drag simulation status on a **Swiper** node.
 *
 * @param node Specified node.
 * @param isFakeDragging Pointer to the **isFakeDragging** parameter indicating whether the simulated drag is in
 *     progress. **true** is returned if the simulated drag is in progress; **false** otherwise.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_IsFakeDragging(ArkUI_NodeHandle node, bool* isFakeDragging);

/**
 * @brief Displays the previous page of a **Swiper** node.
 *
 * @param node Specified node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_ShowPrevious(ArkUI_NodeHandle node);

/**
 * @brief Displays the next page of a **Swiper** node.
 *
 * @param node Specified node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_ShowNext(ArkUI_NodeHandle node);

/**
 * @brief Displays the previous page of the **ArcSwiper** node.
 *
 * @param node **ArkUI_NodeHandle** pointer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.1
 */
int32_t OH_ArkUI_ArcSwiper_ShowPrevious(ArkUI_NodeHandle node);

/**
 * @brief Displays the next page of the **ArcSwiper** node.
 *
 * @param node **ArkUI_NodeHandle** pointer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.1
 */
int32_t OH_ArkUI_ArcSwiper_ShowNext(ArkUI_NodeHandle node);

/**
 * @brief Finishes the animation being executed by the **ArcSwiper** node.
 *
 * @param node **ArkUI_NodeHandle** pointer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.1
 */
int32_t OH_ArkUI_ArcSwiper_FinishAnimation(ArkUI_NodeHandle node);

/**
 * @brief Obtains the root node of the page of a specified instance.
 *
 * @param context Pointer to the UI instance object.
 * @param rootNode Handle to the target root node. If the page corresponding to the context does not have a root node,
 *     this parameter is set to null.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if C API initialization failed.
 *     <br>Returns {@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if an instance error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
int32_t OH_ArkUI_NativeModule_GetPageRootNodeHandleByContext(ArkUI_ContextHandle context, ArkUI_NodeHandle* rootNode);

/**
 * @brief Obtains the **ArkUI_GestureCollectInterceptInfo** object from a specified **ArkUI_NodeEvent** object.
 *
 * @param nodeEvent Pointer to the **ArkUI_NodeEvent** object.
 * @return Pointer to the **ArkUI_GestureCollectInterceptInfo** object. This return value is valid only during the
 *     callback and does not need to be released.<br>**null** is returned if the input parameter is invalid or is not
 *     the gesture collection interception information.
 * @since 26.0.0
 */
ArkUI_GestureCollectInterceptInfo* OH_ArkUI_NodeEvent_GetGestureCollectInterceptInfo(ArkUI_NodeEvent* nodeEvent);

/**
 * @brief Sets the child node mounting policy for a target node.
 *
 * @param node Target node.
 * @param policy Mounting policy to be set.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if a C API initialization error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_SetChildMountPolicy(ArkUI_NodeHandle node, OH_ArkUI_NodeMountPolicy policy);

/**
 * @brief Obtains the current child node mounting policy of a target node. The default child node mounting policy of a
 * target node is OH_ARKUI_NODE_MOUNT_POLICY_SINGLE_IF_RENDER_NODE.
 *
 * @param node Target node.
 * @param policy Pointer to the child node mounting policy of the target node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if a C API initialization error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_GetChildMountPolicy(ArkUI_NodeHandle node, OH_ArkUI_NodeMountPolicy* policy);

/**
 * @brief Sets the UI Dvsync switch.
 *
 * When enabled, the system responds to Vsync requests more promptly and executes rendering tasks more frequently.
 * It is typically enabled at the start of an animation in a self-rendering framework and disabled when the animation
 * ends, to ensure smoother animation effects while preventing frequent Vsync requests from affecting other
 * functionalities. Calling this function on a non-UI thread will cause the application to exit.
 *
 * @param context [in] Pointer to an ArkUI_ContextHandle.
 * @param enable [in] Whether to enable Dvsync. The value true enables Dvsync, and false disables Dvsync.
 * @return Returns the result.
 *     <ul><li>{@link ARKUI_ERROR_CODE_NO_ERROR} The operation is successful.
 *     </li><li>{@link RKUI_ERROR_CODE_CAPI_INIT_ERROR} Failed to initialize the CAPI.
 *     </li><li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} The function parameter is invalid.</li></ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NodeUtils_SetUiDvsyncSwitch(ArkUI_ContextHandle context, bool enable);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_NODE_H
/** @} */
