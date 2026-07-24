/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "native_type.h"
#include "ui_input_event.h"

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
 * @brief Enumerates ArkUI component types that can be created on the native side.
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
    /** Button. */
    ARKUI_NODE_BUTTON = 9,
    /** Progress indicator. */
    ARKUI_NODE_PROGRESS = 10,
    /** Check box. */
    ARKUI_NODE_CHECKBOX = 11,
    /** XComponent. */
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
    /** Radio */
    ARKUI_NODE_RADIO = 18,
    /** Image animator. */
    ARKUI_NODE_IMAGE_ANIMATOR = 19,
    /** XComponent of type TEXTURE.
     *  @since 18
     */
    ARKUI_NODE_XCOMPONENT_TEXTURE,
    /** Check box group.
     *  @since 15
     */
    ARKUI_NODE_CHECKBOX_GROUP = 21,
    /**
     * 文本编辑器。
     * @since 24
     */
    ARKUI_NODE_TEXT_EDITOR = 22,
    /** Stack container. */
    ARKUI_NODE_STACK = MAX_NODE_SCOPE_NUM,
    /** Swiper. */
    ARKUI_NODE_SWIPER,
    /** Scrolling container. */
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
    /** Custom span. */
    ARKUI_NODE_CUSTOM_SPAN,
    /**
     * EmbeddedComponent.
     * @since 20
     */
    ARKUI_NODE_EMBEDDED_COMPONENT,
    /**
     * 组件类型未定义。在反色接口中代表全部组件类型。
     * @since 20
     */
    ARKUI_NODE_UNDEFINED,
    /**
     * Picker container.
     * @since 23
     */
    ARKUI_NODE_PICKER = 1018,
} ArkUI_NodeType;

/**
 * @brief Defines the general input parameter structure of the {@link setAttribute} function. The property
 * setting interfaces can utilize the member variables within it to store data of specific parameter types.
 *
 * @since 12
 */
typedef struct {
    /** A number array, used to store parameters of the number array type. */
    const ArkUI_NumberValue* value;
    /** The size of the number array, used together with the variable value, indicating the length of the value array. */
    int32_t size;
    /** String type, used to store parameters of the string type. */
    const char* string;
    /** Object type, used to store parameters of the object type. */
    void* object;
} ArkUI_AttributeItem;

/**
 * @brief 定义ArkUI在Native侧可以设置的属性样式集合。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief Defines the width attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: width, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: width, in vp.\n
     *
     */
    NODE_WIDTH = 0,
    /**
     * @brief Defines the height attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: height, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: height, in vp.\n
     *
     */
    NODE_HEIGHT,
    /**
     * @brief 背景色属性，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].u32</b>：背景色数值，0xargb格式，形如 `0xFFFF0000` 表示红色。
     * <br>**返回：**
     * <br><b>.value[0].u32</b>：背景色数值，0xargb格式，形如 `0xFFFF0000` 表示红色。
     *
     */
    NODE_BACKGROUND_COLOR,
    /**
     * @brief 背景色图片属性，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.string</b>：图片地址。API version 22及之前版本，支持网络图片资源地址、本地图片资源地址、Base64和{@link PixelMap}资源，不支持{@link svg}图片、
     * gif和webp等类型的动图。从API version 23开始，新增支持webp和gif类型的动图，显示动图第一帧，不支持其他类型的动图。
     * <br><b>.value[0]?.i32</b>：可选值，repeat参数，参数类型{@link ArkUI_ImageRepeat}，默认值为ARKUI_IMAGE_REPEAT_NONE。
     * <br><b>.object</b>：PixelMap图片数据，参数类型为{@link ArkUI_DrawableDescriptor}。`.object`参数和`.string`参数二选一，不可同时设置。
     * <br>**返回：**
     * <br><b>.string</b>：图片地址。API version 22及之前版本，支持网络图片资源地址、本地图片资源地址、Base64和PixelMap资源，不支持svg图片、gif和webp等类型的动图。从API
     * version 23开始，新增支持webp和gif类型的动图，显示动图第一帧，不支持其他类型的动图。
     * <br><b>.value[0].i32</b>：repeat参数，参数类型{@link ArkUI_ImageRepeat}。
     * <br><b>.object</b>：PixelMap图片数据，参数类型为{@link ArkUI_DrawableDescriptor}。
     *
     */
    NODE_BACKGROUND_IMAGE,
    /**
     * @brief Defines the padding attribute, which can be set, reset, and obtained as required through APIs.
     *
     * There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:\n
     * 1: Specify the same padding for the four directions. \n
     * .value[0].f32: padding, in vp.\n
     * 2: Specify different paddings for different directions. \n
     * .value[0].f32: top padding, in vp.\n
     * .value[1].f32: right padding, in vp.\n
     * .value[2].f32: bottom padding, in vp.\n
     * .value[3].f32: left padding, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: top padding, in vp.\n
     * .value[1].f32: right padding, in vp.\n
     * .value[2].f32: bottom padding, in vp.\n
     * .value[3].f32: left padding, in vp.\n
     *
     */
    NODE_PADDING,
    /**
     * @brief Defines the component ID attribute, which can be set, reset, and obtained as required through APIs.
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
     * @brief 设置组件是否可交互，支持属性设置，属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：false表示不可交互，true表示可交互。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：0表示不可交互，1表示可交互。
     *
     */
    NODE_ENABLED,
    /**
     * @brief Defines the margin attribute, which can be set, reset, and obtained as required through APIs.
     *
     * There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:\n
     * 1: Specify the same margin for the four directions. \n
     * .value[0].f32: margin, in vp.\n
     * 2: Specify different margins for different directions. \n
     * .value[0].f32: top margin, in vp.\n
     * .value[1].f32: right margin, in vp.\n
     * .value[2].f32: bottom margin, in vp.\n
     * .value[3].f32: left margin, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: top margin, in vp.\n
     * .value[1].f32: right margin, in vp.\n
     * .value[2].f32: bottom margin, in vp.\n
     * .value[3].f32: left margin, in vp.\n
     *
     */
    NODE_MARGIN,
    /**
     * @brief Defines the translate attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: distance to translate along the x-axis, in vp. The default value is <b>0</b>.\n
     * .value[1].f32: distance to translate along the y-axis, in vp. The default value is <b>0</b>.\n
     * .value[2].f32: distance to translate along the z-axis, in vp. The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: distance to translate along the x-axis, in vp.\n
     * .value[1].f32: distance to translate along the y-axis, in vp.\n
     * .value[2].f32: distance to translate along the z-axis, in vp. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_TRANSLATE,
    /**
     * @brief Defines the scale attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: scale factor along the x-axis. The default value is <b>1</b>.\n
     * .value[1].f32: scale factor along the y-axis. The default value is <b>1</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: scale factor along the x-axis.\n
     * .value[1].f32: scale factor along the y-axis. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_SCALE,
    /**
     * @brief Defines the rotate attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: X coordinate of the rotation axis vector. The default value is <b>0</b>.\n
     * .value[1].f32: Y coordinate of the rotation axis vector. The default value is <b>0</b>.\n
     * .value[2].f32: Z coordinate of the rotation axis vector. The default value is <b>0</b>.\n
     * .value[3].f32: rotation angle. The default value is <b>0</b>.\n
     * .value[4].f32: line of sight, that is, the distance from the viewpoint to the z=0 plane, in vp.
     * The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X coordinate of the rotation axis vector.\n
     * .value[1].f32: Y coordinate of the rotation axis vector.\n
     * .value[2].f32: Z coordinate of the rotation axis vector.\n
     * .value[3].f32: rotation angle.\n
     * .value[4].f32: line of sight, that is, the distance from the viewpoint to the z=0 plane, in vp. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_ROTATE,
    /**
     * @brief Sets the brightness attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: brightness value. The default value is <b>1.0</b>, and the recommended value range is [0, 2]. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: brightness value. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_BRIGHTNESS,
    /**
     * @brief Sets the saturation attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute: \n
     * .value[0].f32: saturation value. The default value is <b>1.0</b>, and the recommended value range is [0, 50). \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}: \n
     * .value[0].f32: saturation value. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_SATURATION,
    /**
     * @brief Sets the blur attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute: \n
     * .value[0].f32: blur radius. A larger value indicates a higher blur degree. If the value is <b>0</b>,
     * the component is not blurred. The unit is vp. The default value is <b>0.0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: blur radius. The larger the fuzzy radius, the more blurred the image. If the value is <b>0</b>,
     * the image is not blurred. The unit is vp. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_BLUR,
    /**
     * @brief Sets the gradient attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: start angle of the linear gradient. This attribute takes effect only when
     * {@link ArkUI_LinearGradientDirection} is set to <b>ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM</b>.
     * A positive value indicates a clockwise rotation from the origin, (0, 0). The default value is <b>180</b>. \n
     * .value[1].i32: direction of the linear gradient. When it is set, the <b>angle</b> attribute does not take effect.
     * The parameter type is {@link ArkUI_LinearGradientDirection}: \n
     * .value[2].i32: whether the colors are repeated. The default value is <b>false</b>. \n
     * .object: array of color stops, each of which consists of a color and its stop position.
     * Invalid colors are automatically skipped. \n
     * colors: colors of the color stops. \n
     * stops: stop positions of the color stops. \n
     * size: number of colors. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}: \n
     * .value[0].f32: start angle of the linear gradient. \n
     * .value[1].i32: direction of the linear gradient. It does not take effect when <b>angle</b> is set. \n
     * .value[2].i32: whether the colors are repeated. \n
     * .object: array of color stops, each of which consists of a color and its stop position.
     * Invalid colors are automatically skipped. \n
     * colors: colors of the color stops. \n
     * stops: stop positions of the color stops. \n
     * size: number of colors. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_LINEAR_GRADIENT,
    /**
     * @brief Sets the alignment attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: alignment mode. The data type is {@link ArkUI_Alignment}.
     * The default value is <b>ARKUI_ALIGNMENT_CENTER</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: alignment mode. The data type is {@link ArkUI_Alignment}. \n
     *
     */
    NODE_ALIGNMENT,
    /**
     * @brief Defines the opacity attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: opacity value. The value ranges from 0 to 1. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: opacity value. The value ranges from 0 to 1. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_OPACITY,
    /**
     * @brief Defines the border width attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * 1: .value[0].f32: width of the four borders. \n
     * 2: .value[0].f32: width of the top border. \n
     * .value[1].f32: width of the right border. \n
     * .value[2].f32: width of the bottom border. \n
     * .value[3].f32: width of the left border. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: width of the top border. \n
     * .value[1].f32: width of the right border. \n
     * .value[2].f32: width of the bottom border. \n
     * .value[3].f32: width of the left border. \n
     *
     */
    NODE_BORDER_WIDTH,
    /**
     * @brief Defines the border corner radius attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * 1: .value[0].f32: radius of the four corners. \n
     * 2: .value[0].f32: radius of the upper left corner. \n
     * .value[1].f32: radius of the upper right corner. \n
     * .value[2].f32: radius of the lower left corner. \n
     * .value[3].f32: radius of the lower right corner. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: radius of the upper left corner. \n
     * .value[1].f32: radius of the upper right corner. \n
     * .value[2].f32: radius of the lower left corner. \n
     * .value[3].f32: radius of the lower right corner. \n
     *
     */
    NODE_BORDER_RADIUS,
    /**
     * @brief Defines the border color attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * 1: .value[0].u32: color of the four borders, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * 2: .value[0].u32: color of the top border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * .value[1].u32: color of the right border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * .value[2].u32: color of the lower border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * .value[3].u32: color of the left border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the top border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * .value[1].u32: color of the right border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * .value[2].u32: color of the lower border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     * .value[3].u32: color of the left border, in 0xARGB format, for example, <b>0xFFFF11FF</b>. \n
     *
     */
    NODE_BORDER_COLOR,
    /**
     * @brief Defines the border line style attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * 1: .value[0].i32: line style of the four borders. The parameter type is {@link ArkUI_BorderStyle}.
     * The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>. \n
     * 2: .value[0].i32: line style of the top border. The parameter type is {@link ArkUI_BorderStyle}.
     * The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>. \n
     * .value[1].i32: line style of the right border. The parameter type is {@link ArkUI_BorderStyle}.
     * The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>. \n
     * .value[2].i32: line style of the bottom border. The parameter type is {@link ArkUI_BorderStyle}.
     * The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>. \n
     * .value[3].i32: line style of the left border. The parameter type is {@link ArkUI_BorderStyle}.
     * The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: line style of the top border. \n
     * .value[1].i32: line style of the right border. \n
     * .value[2].i32: line style of the bottom border. \n
     * .value[3].i32: line style of the left border. \n
     *
     */
    NODE_BORDER_STYLE,
    /**
     * @brief 组件的堆叠顺序属性，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：堆叠顺序数值。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：堆叠顺序数值。
     *
     */
    NODE_Z_INDEX,
    /**
     * @brief 组件是否可见属性，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：控制当前组件显示或隐藏，参数类型{@link ArkUI_Visibility}，默认值为ARKUI_VISIBILITY_VISIBLE。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：控制当前组件显示或隐藏，参数类型{@link ArkUI_Visibility}，默认值为ARKUI_VISIBILITY_VISIBLE。
     *
     */
    NODE_VISIBILITY,
    /**
     * @brief Defines the clipping and masking attribute, which can be set, reset, and obtained as required through
     * APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to clip the component based on the parent container bounds.
     * The value <b>1</b> means to clip the component, and <b>0</b> means the opposite. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to clip the component based on the parent container bounds.
     * The value <b>1</b> means to clip the component, and <b>0</b> means the opposite. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_CLIP,
    /**
     * @brief Defines the clipping region on the component.
     * This attribute can be set and obtained as required through APIs.
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
     * It takes effect when only the .object parameter is passed, ArkUI_RenderNodeClipOption type is rectangle, and .size must be equal to 1.
     * 2. Circle:\n
     * .value[0].i32: type of shape. The parameter type is {@link ArkUI_ClipType}.
     * The value is <b>ARKUI_CLIP_TYPE_CIRCLE</b> for the circle shape.\n
     * .value[1].f32: width of the circle.\n
     * .value[2].f32: height of the circle.\n
     * ?.object: clipOption of the circle. The parameter type is {@link ArkUI_RenderNodeClipOption} type.
     * It takes effect when only the .object parameter is passed, ArkUI_RenderNodeClipOption type is circle, and .size must be equal to 1.
     * 3.Ellipse:\n
     * .value[0].i32: type of shape. The parameter type is {@link ArkUI_ClipType}.
     * The value is <b>ARKUI_CLIP_TYPE_ELLIPSE</b> for the ellipse shape.\n
     * .value[1].f32: width of the ellipse.\n
     * .value[2].f32: height of the ellipse.\n
     * ?.object: clipOption of the ellipse. The parameter type is {@link ArkUI_RenderNodeClipOption} type.
     * It takes effect when only the .object parameter is passed, ArkUI_RenderNodeClipOption type is ellipse, and .size must be equal to 1.
     * 4. Path:\n
     * .value[0].i32: type of shape. The parameter type is {@link ArkUI_ClipType}.
     * The value is <b>ARKUI_CLIP_TYPE_PATH</b> for the path shape.\n
     * .value[1].f32: width of the path.\n
     * .value[2].f32: height of the path.\n
     * .string: command for drawing the path.\n
     * ?.object: clipOption of the path. The parameter type is {@link ArkUI_RenderNodeClipOption} type.
     * It takes effect when only the .object parameter is passed, ArkUI_RenderNodeClipOption type is path, and .size must be equal to 1.
     * Format of the return value {@link ArkUI_AttributeItem}, which supports four types of shapes: \n
     * 1. Rectangle:\n
     * .value[0].i32: type of shape. The parameter type is {@link ArkUI_ClipType}.
     * The value is <b>ARKUI_CLIP_TYPE_RECTANGLE</b> for the rectangle shape. \n
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
     * @ingroup Visual [视效属性]
     */
    NODE_CLIP_SHAPE,
    /**
     * @brief Defines the transform attribute, which can be used to translate, rotate, and scale images.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0...15].f32: 16 floating-point numbers. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0...15].f32: 16 floating-point numbers. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_TRANSFORM,
    /**
     * @brief 触摸测试类型，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：控制当前组件的触摸测试类型，参数类型{@link ArkUI_HitTestMode}，默认值为ARKUI_HIT_TEST_MODE_DEFAULT。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：控制当前组件的触摸测试类型，参数类型{@link ArkUI_HitTestMode}，默认值为ARKUI_HIT_TEST_MODE_DEFAULT。
     *
     */
    NODE_HIT_TEST_BEHAVIOR,
    /**
     * @brief Defines the offset attribute, which specifies the offset of the component's upper left corner relative
     * to the parent container's. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: X coordinate. \n
     * .value[1].f32: Y coordinate. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X coordinate. \n
     * .value[1].f32: Y coordinate. \n
     *
     */
    NODE_POSITION,
    /**
     * @brief Defines the shadow attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: shadow effect. The parameter type is {@link ArkUI_ShadowStyle}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: shadow effect. The parameter type is {@link ArkUI_ShadowStyle}. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_SHADOW,
    /**
     * @brief Defines the custom shadow effect. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.f32: blur radius of the shadow, in vp.\n
     * .value[1]?.i32: whether to enable the coloring strategy. The value <b>1</b> means to enable the coloring
     * strategy, and <b>0</b> (default value) means the opposite.\n
     * .value[2]?.f32: offset of the shadow along the x-axis, in px.\n
     * .value[3]?.f32: offset of the shadow along the y-axis, in px.\n
     * .value[4]?.i32: shadow type {@link ArkUI_ShadowType}. The default value is <b>ARKUI_SHADOW_TYPE_COLOR</b>.\n
     * .value[5]?.u32: shadow color, in 0xARGB format. For example, 0xFFFF0000 indicates red.\n
     * .value[6]?.u32: whether to fill the shadow. The value <b>1</b> means to fill the shadow, and <b>0</b>
     * means the opposite.\n
     *
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: blur radius of the shadow, in vp.\n
     * .value[1].i32: whether to enable the coloring strategy. \n
     * .value[2].f32: offset of the shadow along the x-axis, in px.\n
     * .value[3].f32: offset of the shadow along the y-axis, in px.\n
     * .value[4].i32: shadow type {@link ArkUI_ShadowType}. The default value is <b>ARKUI_SHADOW_TYPE_COLOR</b>.\n
     * .value[5].u32: shadow color, in 0xARGB format. For example, 0xFFFF0000 indicates red.\n
     * .value[6].u32: whether to fill the shadow. The value <b>1</b> means to fill the shadow, and <b>0</b>
     * means the opposite.\n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_CUSTOM_SHADOW,
    /**
     * @brief 背景图片的宽高属性，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].f32</b>：图片的宽度值，取值范围`[0,+∞)`，单位为vp。
     * <br><b>.value[1].f32</b>：图片的高度值，取值范围`[0,+∞)`，单位为vp。
     * <br>**返回：**
     * <br><b>.value[0].f32</b>：图片的宽度值，单位为vp。
     * <br><b>.value[1].f32</b>：图片的高度值，单位为vp。
     *
     */
    NODE_BACKGROUND_IMAGE_SIZE,
    /**
     * @brief 背景图片的宽高样式属性，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：背景图片的宽高样式，取{@link ArkUI_ImageSize}枚举值。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：背景图片的宽高样式，取{@link ArkUI_ImageSize}枚举值。
     *
     */
    NODE_BACKGROUND_IMAGE_SIZE_WITH_STYLE,
    /**
     * @brief Defines the background blur attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: blue type. The value is an enum of {@link ArkUI_BlurStyle}. \n
     * .value[1]?.i32: color mode. The value is an enum of {@link ArkUI_ColorMode}. \n
     * .value[2]?.i32: adaptive color mode. The value is an enum of {@link ArkUI_AdaptiveColor}. \n
     * .value[3]?.f32: blur degree. The value range is [0.0, 1.0]. \n
     * .value[4]?.f32: start boundary of grayscale blur. \n
     * .value[5]?.f32: end boundary of grayscale blur. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: blue type. The value is an enum of {@link ArkUI_BlurStyle}. \n
     * .value[1].i32: color mode. The value is an enum of {@link ArkUI_ColorMode}. \n
     * .value[2].i32: adaptive color mode. The value is an enum of {@link ArkUI_AdaptiveColor}. \n
     * .value[3].f32: blur degree. The value range is [0.0, 1.0]. \n
     * .value[4].f32: start boundary of grayscale blur. \n
     * .value[5].f32: end boundary of grayscale blur. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_BACKGROUND_BLUR_STYLE,
    /**
     * @brief Defines the transform center attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.f32: X coordinate of the center point, in vp.\n
     * .value[1]?.f32: Y coordinate of the center point, in vp.\n
     * .value[2]?.f32: Z coordinate of the center point, in vp.\n
     * .value[3]?.f32 : X coordinate of the center point, expressed in a number that represents a percentage.
     * For example, 0.2 indicates 20%. This attribute overwrites value[0].f32. The default value is <b>0.5f</b>. \n
     * .value[4]?.f32 : Y coordinate of the center point, expressed in a number that represents a percentage.
     * For example, 0.2 indicates 20%. This attribute overwrites value[1].f32. The default value is <b>0.5f</b>. \n
     * .value[5]?.f32 : Z coordinate of the center point, expressed in a number that represents a percentage.
     * For example, 0.2 indicates 20%. This attribute overwrites value[2].f32. The default value is <b>0.0f</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X coordinate of the center point, in vp.\n
     * .value[1].f32: Y coordinate of the center point, in vp.\n
     * .value[2].f32: Z coordinate of the center point, in vp.\n
     * Note: If the coordinate is expressed in a number that represents a percentage, the attribute obtaining API
     * returns the calculated value in vp.
     *
     * @ingroup Visual [视效属性]
     */
    NODE_TRANSFORM_CENTER,
    /**
     * @brief Defines the transition opacity attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: opacity values of the start and end points.\n
     * .value[1].i32: animation duration, in milliseconds.\n
     * .value[2].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n
     * .value[3]?.i32: animation delay duration, in milliseconds.\n
     * .value[4]?.i32: number of times that the animation is played.\n
     * .value[5]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}.\n
     * .value[6]?.f32: animation playback speed.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: opacity values of the start and end points.\n
     * .value[1].i32: animation duration, in milliseconds.\n
     * .value[2].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n
     * .value[3].i32: animation delay duration, in milliseconds. \n
     * .value[4].i32: number of times that the animation is played. \n
     * .value[5].i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * .value[6].f32: animation playback speed. \n
     *
     * @ingroup Animate [动效属性]
     */
    NODE_OPACITY_TRANSITION,
    /**
     * @brief Defines the transition rotation attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: X-component of the rotation vector. \n
     * .value[1].f32: Y-component of the rotation vector. \n
     * .value[2].f32: Z-component of the rotation vector \n
     * .value[3].f32: angle. \n
     * .value[4].f32: line of sight. The default value is <b>0.0f</b>. \n
     * .value[5].i32: animation duration, in milliseconds. \n
     * .value[6].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n \n
     * .value[7]?.i32: animation delay duration, in milliseconds. \n
     * .value[8]?.i32: number of times that the animation is played. \n
     * .value[9]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * .value[10]?.f32: animation playback speed. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X-component of the rotation vector. \n
     * .value[1].f32: Y-component of the rotation vector. \n
     * .value[2].f32: Z-component of the rotation vector \n
     * .value[3].f32: angle. \n
     * .value[4].f32: line of sight. \n
     * .value[5].i32: animation duration, in milliseconds. \n
     * .value[6].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n \n
     * .value[7].i32: animation delay duration, in milliseconds. \n
     * .value[8].i32: number of times that the animation is played. \n
     * .value[9].i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * .value[10].f32: animation playback speed. \n
     *
     * @ingroup Animate [动效属性]
     */
    NODE_ROTATE_TRANSITION,
    /**
     * @brief Defines the transition scaling attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: scale factor along the x-axis. \n
     * .value[1].f32: scale factor along the y-axis. \n
     * .value[2].f32: scale factor along the z-axis. \n
     * .value[3].i32: animation duration, in milliseconds. \n
     * .value[4].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n \n
     * .value[5]?.i32: animation delay duration, in milliseconds. \n
     * .value[6]?.i32: number of times that the animation is played. \n
     * .value[7]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * .value[8]?.f32: animation playback speed. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: scale factor along the x-axis. \n
     * .value[1].f32: scale factor along the y-axis. \n
     * .value[2].f32: scale factor along the z-axis. \n
     * .value[3].i32: animation duration, in milliseconds. \n
     * .value[4].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n \n
     * .value[5].i32: animation delay duration, in milliseconds. \n
     * .value[6].i32: number of times that the animation is played. \n
     * .value[7].i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * .value[8].f32: animation playback speed. \n
     *
     * @ingroup Animate [动效属性]
     */
    NODE_SCALE_TRANSITION,
    /**
     * @brief Defines the transition translation attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * value[0].f32: translation distance along the x-axis, in vp.\n
     * value[1].f32: translation distance along the y-axis, in vp.\n
     * value[2].f32: translation distance along the z-axis, in vp.\n
     * value[3].i32: animation duration, in milliseconds. \n
     * value[4].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n \n
     * value[5]?.i32: animation delay duration, in milliseconds. \n
     * value[6]?.i32: number of times that the animation is played. \n
     * value[7]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * value[8]?.f32: animation playback speed. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].f32: translation distance along the x-axis, in vp.\n
     * value[1].f32: translation distance along the y-axis, in vp.\n
     * value[2].f32: translation distance along the z-axis, in vp.\n
     * value[3].i32: animation duration, in milliseconds. \n
     * value[4].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n \n
     * value[5].i32: animation delay duration, in milliseconds. \n
     * value[6].i32: number of times that the animation is played. \n
     * value[7].i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * value[8].f32: animation playback speed. \n
     *
     * @ingroup Animate [动效属性]
     */
    NODE_TRANSLATE_TRANSITION,
    /**
     * @brief Defines the slide-in and slide-out of the component from the screen edge during transition.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The parameter type is {@link ArkUI_TransitionEdge}. \n
     * .value[1].i32: animation duration, in milliseconds.\n
     * .value[2].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n
     * .value[3]?.i32: animation delay duration, in milliseconds.\n
     * .value[4]?.i32: number of times that the animation is played.\n
     * .value[5]?.i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}.\n
     * .value[6]?.f32: animation playback speed.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The parameter type is {@link ArkUI_TransitionEdge}. \n
     * .value[1].i32: animation duration, in milliseconds.\n
     * .value[2].i32: animation curve type. The value is an enum of {@link ArkUI_AnimationCurve}.\n
     * .value[3].i32: animation delay duration, in milliseconds. \n
     * .value[4].i32: number of times that the animation is played. \n
     * .value[5].i32: animation playback mode. The value is an enum of {@link ArkUI_AnimationPlayMode}. \n
     * .value[6].f32: animation playback speed. \n
     *
     * @ingroup Animate [动效属性]
     */
    NODE_MOVE_TRANSITION,

    /**
     * @brief 获焦属性，支持属性设置，属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：参数类型为1表示可获焦，为0表示不可获焦。默认为不可获焦。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：参数类型为1表示可获焦，为0表示不可获焦。
     *
     */
    NODE_FOCUSABLE,

    /**
     * @brief 默认焦点属性，支持属性设置，属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：参数值为1表示是默认焦点，为0表示不是默认焦点。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：参数值为1表示是默认焦点，为0表示不是默认焦点。
     *
     */
    NODE_DEFAULT_FOCUS,

    /**
     * @brief 触摸热区属性，支持属性设置，属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**说明：**
     * <br>设置时data数据大小无数量限制，均可以设置成功，但仅支持获取到前20个。
     * <br>**参数：**
     * <br><b>.data[0].f32</b>：触摸点相对于组件左上角的x轴坐标，单位为vp。
     * <br><b>.data[1].f32</b>：触摸点相对于组件左上角的y轴坐标，单位为vp。
     * <br><b>.data[2].f32</b>：触摸热区的宽度，单位为百分比。
     * <br><b>.data[3].f32</b>：触摸热区的高度，单位为百分比。
     * <br><b>.data[4...].f32</b>：可以设置多个手势响应区域，顺序和上述一致。
     * <br>**返回：**
     * <br><b>.data[0].f32</b>：触摸点相对于组件左上角的x轴坐标，单位为vp。
     * <br><b>.data[1].f32</b>：触摸点相对于组件左上角的y轴坐标，单位为vp。
     * <br><b>.data[2].f32</b>：触摸热区的宽度，单位为百分比。
     * <br><b>.data[3].f32</b>：触摸热区的高度，单位为百分比。
     * <br><b>.data[4...].f32</b>：可以设置多个手势响应区域，顺序和上述一致。
     *
     */
    NODE_RESPONSE_REGION,

    /**
     * @brief 定义遮罩属性，支持属性设置，属性重置和属性获取。开发者可以通过如下.string或.object设置浮层内容，.string有更高的优先级。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.string</b>：遮罩文本。
     * <br><b>.value[0]?.i32</b>：可选值，浮层相对于组件的位置，参数类型{@link ArkUI_Alignment}，默认值为ARKUI_ALIGNMENT_TOP_START。
     * <br><b>.value[1]?.f32</b>：可选值，浮层基于自身左上角的偏移量X，单位为vp，默认值为0vp。
     * <br><b>.value[2]?.f32</b>：可选值，浮层基于自身左上角的偏移量Y，单位为vp，默认值为0vp。
     * <br><b>.value[3]?.i32</b>：可选值，浮层的布局方向，参数类型{@link ArkUI_Direction}，默认值为ARKUI_DIRECTION_LTR。
     * <br>在大部分场景下，这个参数都应该被设置成Auto，这个模式允许系统自动处理布局方向，如果在某些场景下需要保持特定的方向，设置这个属性为LTR（Left-to-Right）或者RTL（Right-to-Left）。
     * 从API version 21开始支持。
     * <br><b>.object</b>：用于overlay的节点树，参数类型为{@link ArkUI_NodeHandle}，默认值为nullptr。从API version 21开始支持。
     * <br>**返回：**
     * <br><b>.string</b>：遮罩文本。
     * <br><b>.value[0].i32</b>：浮层相对于组件的位置，参数类型{@link ArkUI_Alignment}，默认值为ARKUI_ALIGNMENT_TOP_START。
     * <br><b>.value[1].f32</b>：浮层基于自身左上角的偏移量X，单位为vp。
     * <br><b>.value[2].f32</b>：浮层基于自身左上角的偏移量Y，单位为vp。
     * <br><b>.value[3].i32</b>：浮层的布局方向，参数类型{@link ArkUI_Direction}，默认值为ARKUI_DIRECTION_LTR。从API version 21开始支持。
     * <br><b>.object</b>：用于overlay的节点树，参数类型为{@link ArkUI_NodeHandle}。从API version 21开始支持。
     *
     */
    NODE_OVERLAY,
    /**
     * @brief Defines the sweep gradient effect.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.f32: X coordinate of the sweep gradient center relative to the upper left corner of the component.\n
     * .value[1]?.f32: Y coordinate of the sweep gradient center relative to the upper left corner of the component.\n
     * .value[2]?.f32: start point of the sweep gradient. The default value is <b>0</b>. \n
     * .value[3]?.f32: end point of the sweep gradient. The default value is <b>0</b>. \n
     * .value[4]?.f32: rotation angle of the sweep gradient. The default value is <b>0</b>. \n
     * .value[5]?.i32: whether the colors are repeated. The value <b>1</b> means that the colors are repeated,
     * and <b>0</b> means the opposite.\n
     * .object: array of color stops, each of which consists of a color and its stop position. Invalid colors are
     * automatically skipped.\n
     * colors: colors of the color stops. \n
     * stops: stop positions of the color stops. \n
     * size: number of colors. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X coordinate of the sweep gradient center relative to the upper left corner of the component. \n
     * .value[1].f32: Y coordinate of the sweep gradient center relative to the upper left corner of the component. \n
     * .value[2].f32: start point of the sweep gradient. The default value is <b>0</b>. \n
     * .value[3].f32: end point of the sweep gradient. The default value is <b>0</b>. \n
     * .value[4].f32: rotation angle of the sweep gradient. The default value is <b>0</b>. \n
     * .value[5].i32: whether the colors are repeated. The value <b>1</b> means that the colors are repeated,
     * and <b>0</b> means the opposite.\n
     * .object: array of color stops, each of which consists of a color and its stop position. Invalid colors are
     * automatically skipped.\n
     * colors: colors of the color stops. \n
     * stops: stop positions of the color stops. \n
     * size: number of colors. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_SWEEP_GRADIENT,
    /**
     * @brief Defines the radial gradient effect.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute: \n
     * .value[0]?.f32: X coordinate of the radial gradient center relative to the upper left corner of the component. \n
     * .value[1]?.f32: Y coordinate of the radial gradient center relative to the upper left corner of the component. \n
     * .value[2]?.f32: radius of the radial gradient. The default value is <b>0</b>. \n
     * .value[3]?.i32: whether the colors are repeated. The value <b>1</b> means that the colors are repeated,
     * and <b>0</b> means the opposite. \n
     * .object: array of color stops, each of which consists of a color and its stop position. Invalid colors are
     * automatically skipped. \n
     * colors: colors of the color stops. \n
     * stops: stop positions of the color stops. \n
     * size: number of colors. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X coordinate of the radial gradient center relative to the upper left corner of the component. \n
     * .value[1].f32: Y coordinate of the radial gradient center relative to the upper left corner of the component. \n
     * .value[2].f32: radius of the radial gradient. The default value is <b>0</b>. \n
     * .value[3].i32: whether the colors are repeated. The value <b>1</b> means that the colors are repeated,
     * and <b>0</b> means the opposite.\n
     * .object: array of color stops, each of which consists of a color and its stop position. Invalid colors are
     * automatically skipped. \n
     * colors: colors of the color stops. \n
     * stops: stop positions of the color stops. \n
     * size: number of colors. \n
     *
     * @ingroup Visual [视效属性]
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
     * @ingroup Visual [视效属性]
     */
    NODE_MASK,
    /**
     * @brief Blends the component's background with the content of the component's child node.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: blend mode. The parameter type is {@link ArkUI_BlendMode}. The default value is
     * <b>ARKUI_BLEND_MODE_NONE</b>. \n
     * .value[1].?i32: how the specified blend mode is applied. The parameter type is {@link ArkUI_BlendApplyType}.
     * The default value is <b>BLEND_APPLY_TYPE_FAST</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: blend mode. The parameter type is {@link ArkUI_BlendMode}. The default value is
     * <b>ARKUI_BLEND_MODE_NONE</b>. \n
     * .value[1].i32: how the specified blend mode is applied. The parameter type is {@link ArkUI_BlendApplyType}.
     * The default value is <b>BLEND_APPLY_TYPE_FAST</b>. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_BLEND_MODE,
    /**
     * @brief Sets the direction of the main axis.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: direction of the main axis.\n
     * The parameter type is {@link ArkUI_Direction}. The default value is <b>ARKUI_DIRECTION_AUTO</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: direction of the main axis.\n
     * The parameter type is {@link ArkUI_Direction}. The default value is <b>ARKUI_DIRECTION_AUTO</b>. \n
     *
     */
    NODE_DIRECTION,
    /**
     * @brief Defines the size constraints.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: minimum width, in vp.\n
     * .value[1].f32: maximum width, in vp.\n
     * .value[2].f32: minimum height, in vp.\n
     * .value[3].f32: maximum height, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: minimum width, in vp.\n
     * .value[1].f32: maximum width, in vp.\n
     * .value[2].f32: minimum height, in vp.\n
     * .value[3].f32: maximum height, in vp.\n
     *
     */
    NODE_CONSTRAINT_SIZE,
    /**
     * @brief Defines the grayscale effect.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: grayscale conversion ratio. The value ranges from 0 to 1.
     * For example, 0.5 indicates a 50% grayscale conversion ratio. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: grayscale conversion ratio. The value ranges from 0 to 1.\n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_GRAY_SCALE,
    /**
     * @brief Inverts the image.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: image inversion ratio. The value ranges from 0 to 1.
     * For example, 0.5 indicates a 50% image inversion ratio.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: image inversion ratio. The value ranges from 0 to 1.\n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_INVERT,
    /**
     * @brief Defines the sepia conversion ratio.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: sepia conversion ratio. The value ranges from 0 to 1.
     * For example, 0.5 indicates that a 50% sepia conversion ratio.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: sepia conversion ratio. The value ranges from 0 to 1.\n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_SEPIA,
    /**
     * @brief Defines the contrast attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: contrast. If the value is <b>1</b>, the source image is displayed.
     * A larger value indicates a higher contrast. Value range: [0, 10).\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: contrast. Value range: [0, 10).\n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_CONTRAST,
    /**
     * @brief Defines the foreground color attribute, which can be set, reset, and obtained as required through APIs.
     *
     * There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:\n
     * 1: .value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red.\n
     * 2: .value[0].i32: color enum {@link ArkUI_ColoringStrategy}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color value, in 0xARGB format.\n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_FOREGROUND_COLOR,

    /**
     * @brief Defines the offset of the component's child relative to the component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32 : offset along the x-axis, in vp. \n
     * .value[1].f32 : offset along the y-axis, in vp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32 : offset along the x-axis, in vp. \n
     * .value[1].f32 : offset along the y-axis, in vp. \n
     *
     */
    NODE_OFFSET,
    /**
     * @brief Sets the anchor for locating the component's child.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: X coordinate of the anchor, in vp.\n
     * .value[1].f32: Y coordinate of the anchor, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: X coordinate of the anchor, in vp.\n
     * .value[1].f32: Y coordinate of the anchor, in vp.\n
     *
     */
    NODE_MARK_ANCHOR,

    /**
     * @brief 背景图在组件中显示位置，即相对于组件左上角的坐标，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].f32</b>：x轴位置，单位为px。
     * <br><b>.value[1].f32</b>：y轴位置，单位为px。
     * <br><b>.value[2]?.i32</b>：可选值，对齐方式，参数类型{@link ArkUI_Alignment}，默认值为ARKUI_ALIGNMENT_TOP_START。该参数从API version
     * 21开始支持。
     * <br><b>.value[3]?.i32</b>：可选值，布局方向，参数类型{@link ArkUI_Direction}，默认值为ARKUI_DIRECTION_AUTO。多数场景下建议设置为AUTO，
     * 由系统自动处理布局方向；若需要固定方向，可设置为LTR或RTL。该参数从API version 21开始支持。
     * <br>**返回：**
     * <br><b>.value[0].f32</b>：x轴位置，单位为px。
     * <br><b>.value[1].f32</b>：y轴位置，单位为px。
     * <br><b>.value[2].i32</b>：对齐方式，参数类型{@link ArkUI_Alignment}。该返回值从API version 21开始支持。
     * <br><b>.value[3].i32</b>：布局方向，参数类型{@link ArkUI_Direction}。该返回值从API version 21开始支持。
     *
     */
    NODE_BACKGROUND_IMAGE_POSITION,
    /**
     * @brief Sets the alignment rules in the relative container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: Use the {@link ArkUI_AlignmentRuleOption} object as the component’s alignment rule. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: Use the {@link ArkUI_AlignmentRuleOption} object as the component’s alignment rule. \n
     *
     */
    NODE_ALIGN_RULES,
    /**
     * @brief Sets the alignment mode of the child components along the cross axis of the parent container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: alignment mode of the child components along the cross axis of the parent container.\n
     * The parameter type is {@link ArkUI_ItemAlignment}. The default value is <b>ARKUI_ITEM_ALIGNMENT_AUTO</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: alignment mode of the child components along the cross axis of the parent container.\n
     * The parameter type is {@link ArkUI_ItemAlignment}. The default value is <b>ARKUI_ITEM_ALIGNMENT_AUTO</b>. \n
     *
     */
    NODE_ALIGN_SELF,
    /**
     * @brief Sets the percentage of the parent container's remaining space that is allocated to the component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: percentage of the parent container's remaining space that is allocated to the component. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: percentage of the parent container's remaining space that is allocated to the component. \n
     *
     */
    NODE_FLEX_GROW,
    /**
     * @brief Sets the percentage of the parent container's shrink size that is allocated to the component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: percentage of the parent container's shrink size that is allocated to the component. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: percentage of the parent container's shrink size that is allocated to the component. \n
     *
     */
    NODE_FLEX_SHRINK,
    /**
     * @brief Sets the base size of the component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: percentage of the parent container's remaining space that is allocated to the component. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: percentage of the parent container's remaining space that is allocated to the component. \n
     *
     */
    NODE_FLEX_BASIS,
    /**
     * @brief Sets the accessibility group. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: Accessibility group. The value <b>1</b> means that the component and all its child components
     * form an entire selectable component.
     * In this case, the accessibility service will no longer be available for the content of its child components.
     * The value is <b>1</b> or <b>0</b>.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: Accessibility group. The value <b>1</b> means that the component and all its child components
     * form an entire selectable component.
     * In this case, the accessibility service will no longer be available for the content of its child components.
     * The value is <b>1</b> or <b>0</b>.
     *
     */
    NODE_ACCESSIBILITY_GROUP,

    /**
     * @brief Sets the accessibility text. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: accessibility text.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: accessibility text.
     *
     */
    NODE_ACCESSIBILITY_TEXT,

    /**
     * @brief Sets the accessibility service model. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: accessibility service model. The parameter type is {@link ArkUI_AccessibilityMode}.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: accessibility service model. The parameter type is {@link ArkUI_AccessibilityMode}.
     *
     */
    NODE_ACCESSIBILITY_MODE,

    /**
     * @brief Sets the accessibility description.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: accessibility description.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: accessibility description.
     *
     */
    NODE_ACCESSIBILITY_DESCRIPTION,

    /**
     * @brief 组件获取焦点属性，支持属性设置，属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**说明：**
     * <br>设置参数为0时，当前层级页面获焦组件失焦，焦点转移到根容器上。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：参数值为1表示组件获焦，为0表示组件失焦。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：参数值为1表示组件获焦，为0表示组件失焦。
     *
     */
    NODE_FOCUS_STATUS,
    /**
     * @brief Defines the aspect ratio attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: aspect ratio of the component, in width/height format. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: aspect ratio of the component, in width/height format. \n
     *
     */
    NODE_ASPECT_RATIO,
    /**
     * @brief Defines the weight of the component within its row, column, or flex container for proportional
     * distribution of available space within the container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: weight of the component along the main axis. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: weight of the component along the main axis. \n
     *
     */
    NODE_LAYOUT_WEIGHT,
    /**
     * @brief Sets the display priority for the component in the row, column, or flex  (single-line) container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: display priority of the component in the container. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: display priority of the component in the container. \n
     *
     */
    NODE_DISPLAY_PRIORITY,
    /**
     * @brief Sets the thickness of an element's outline.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: thickness of the left outline. \n
     * .value[1].f32: thickness of the top outline. \n
     * .value[2].f32: thickness of the right outline. \n
     * .value[3].f32: thickness of the bottom outline. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: thickness of the left outline. \n
     * .value[1].f32: thickness of the top outline. \n
     * .value[2].f32: thickness of the right outline. \n
     * .value[3].f32: thickness of the bottom outline. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_OUTLINE_WIDTH,
    /**
     * @brief Defines the width attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: width, in percentage.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: width, in percentage.\n
     *
     */
    NODE_WIDTH_PERCENT,
    /**
     * @brief Defines the height attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: height, in percentage.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: height, in percentage.\n
     *
     */
    NODE_HEIGHT_PERCENT,
    /**
     * @brief Defines the padding attribute, which can be set, reset, and obtained as required through APIs.
     *
     * There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:\n
     * 1: Specify the same padding for the four directions. \n
     * .value[0].f32: padding, in percentage.\n
     * 2: Specify different paddings for different directions. \n
     * .value[0].f32: top padding, in percentage.\n
     * .value[1].f32: right padding, in percentage.\n
     * .value[2].f32: bottom padding, in percentage.\n
     * .value[3].f32: left padding, in percentage.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: top padding, in percentage.\n
     * .value[1].f32: right padding, in percentage.\n
     * .value[2].f32: bottom padding, in percentage.\n
     * .value[3].f32: left padding, in percentage.\n
     *
     */
    NODE_PADDING_PERCENT,
    /**
     * @brief Defines the margin attribute, which can be set, reset, and obtained as required through APIs.
     *
     * There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:\n
     * 1: Specify the same margin for the four directions. \n
     * .value[0].f32: margin, in percentage.\n
     * 2: Specify different margins for different directions. \n
     * .value[0].f32: top margin, in percentage.\n
     * .value[1].f32: right margin, in percentage.\n
     * .value[2].f32: bottom margin, in percentage.\n
     * .value[3].f32: left margin, in percentage.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: top margin, in percentage.\n
     * .value[1].f32: right margin, in percentage.\n
     * .value[2].f32: bottom margin, in percentage.\n
     * .value[3].f32: left margin, in percentage.\n
     *
     */
    NODE_MARGIN_PERCENT,

    /**
      * @brief The implicit shared element transition within the component supports attribute setting,
      * attribute reset, and attribute acquisition interfaces.
      *
      * Attribute setting method parameter {@link ArkUI_AttributeItem} format: \n
      * .value[0]?.i32: The parameter type is 1 or 0. 2 components that share element bindings,
      * Whether to continue to participate in the shared element animation when the appearance element is not deleted,
      * the default is false, and the original position will remain unchanged if not involved. \n
      * .string is used to set the binding relationship. Set the id to "" to
      * clear the binding relationship to avoid participating in sharing behavior. \n
      * The id can be changed and the binding relationship re-established.
      * The same ID can only be bound to two components and they are in/out roles of different types.
      * Multiple components cannot be bound to the same id. \n
      *\n
      * Attribute acquisition method return value {@link ArkUI_AttributeItem} format: \n
      * .value[0].i32: The parameter type is 1 or 0. 2 components that share element bindings,
      * Whether to continue to participate in the shared element animation when the appearance element is not deleted,
      * the default is not false, if not involved, the original position will remain unchanged. \n
      * .string is used to set the binding relationship. Set the id to "" to
      * clear the binding relationship to avoid participating in sharing behavior. \n
      * The id can be changed and the binding relationship re-established.
      * The same ID can only be bound to two components and they are in/out roles of different types.
      * Multiple components cannot be bound to the same id. \n
      *
      * @ingroup Animate [动效属性]
      */
    NODE_GEOMETRY_TRANSITION,

    /**
      * @brief specifies the parameters of the chain formed by this component as the chain head,
      * and supports attribute setting, attribute reset and attribute acquisition interfaces.
      *
      * Only takes effect when the parent container is RelativeContainer
      *
      * Attribute setting method parameter {@link ArkUI_AttributeItem} format: \n
      * .value[0].i32: The direction of the chain. Enum {@link ArkUI_Axis}. \n
      * .value[1].i32: Chain style. Enum {@link ArkUI_RelativeLayoutChainStyle}. \n
      *\n
      * .value[0].i32: The direction of the chain. Enum {@link ArkUI_Axis}. \n
      * .value[1].i32: Chain style. Enum {@link ArkUI_RelativeLayoutChainStyle}. \n
      */
    NODE_RELATIVE_LAYOUT_CHAIN_MODE,

    /**
     * @brief Set the component content filling method in the process of width and height animation,
     * support property setting, property reset, property acquisition interface.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32 Content filling mode {@link ArkUI_RenderFit}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32 Content filling mode {@link ArkUI_RenderFit}.\n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_RENDER_FIT,

    /**
     * @brief External stroke color properties, support property setting,
     * property reset and property acquisition interface.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * 1: .value[0].u32: Set the border color of the four sides uniformly, using 0xargb, such as 0xFFFF11FF. \n
     * 2: .value[0].u32: Set the top border color, represented by 0xargb, such as 0xFFFF11FF. \n
     * .value[1].u32: Set the right border color, represented by 0xargb, such as 0xFFFF11FF. \n
     * .value[2].u32: Set the lower side box color, denoted by 0xargb, such as 0xFFFF11FF. \n
     * .value[3].u32: Set the left border color, denoted by 0xargb, such as 0xFFFF11FF. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: Set the top border color, represented by 0xargb, such as 0xFFFF11FF. \n
     * .value[1].u32: Set the right border color, represented by 0xargb, such as 0xFFFF11FF. \n
     * .value[2].u32: Set the lower side box color, denoted by 0xargb, such as 0xFFFF11FF. \n
     * .value[3].u32: Set the left border color, denoted by 0xargb, such as 0xFFFF11FF. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_OUTLINE_COLOR,

    /**
     * @brief Set the height and width dimensions, support property setting,
     * property reset and property acquisition interface.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: Width value, unit is vp;\n
     * .value[1].f32: Height value, unit is vp;\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: Width value, unit is vp;\n
     * .value[1].f32: Height value, unit is vp;\n
     *
     */
    NODE_SIZE,

    /**
     * @brief Set whether the current component and child component are
     * rendered off the screen first and then fused with the parent control,
     * supporting property setting, property reset and property acquisition.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The parameter type is 1 or 0.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The parameter type is 1 or 0.
     *
     * @ingroup Visual [视效属性]
     */
    NODE_RENDER_GROUP,

    /**
     * @brief Add color overlay effect to components, support property setting,
     * property reset and property acquisition interface.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: The color of the overlay is represented by 0xargb, such as 0xFFFF11FF. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: The color of the overlay is represented by 0xargb, such as 0xFFFF11FF. \n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_COLOR_BLEND,

    /**
     * @brief Provide content ambiguity capability for the current component,
     * support property setting, property reset, property acquisition interface.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32 Represents the content blurring style, and uses the {@link ArkUI_BlurStyle} enumeration value.\n
     * .value[1]?.i32 Represents the dark and light mode used by the content blur effect,\n
     * with the {@link ArkUI_ThemeColorMode} enumeration value.\n
     * .value[2]?.i32 The color extraction mode used to represent the content blur effect takes\n
     * the {@link ArkUI_AdaptiveColor} enumeration value.\n
     * .value[3]?.f32: blur degree. The value range is [0.0, 1.0]. \n
     * .value[4]?.f32 It is a gray-level fuzzy parameter. The value range is [0,127].\n
     * .value[5]?.f32 It is a gray-level fuzzy parameter. The value range is [0,127].\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32 Represents the content blurring style, and uses the {@link ArkUI_BlurStyle} enumeration value.\n
     * .value[1].i32 Represents the dark and light mode used by the content blur effect,\n
     * with the {@link ArkUI_ThemeColorMode} enumeration value.\n
     * .value[2].i32 The color extraction mode used to represent the content blur effect takes\n
     * the {@link ArkUI_AdaptiveColor} enumeration value.\n
     * .value[3].f32: blur degree. The value range is [0.0, 1.0]. \n
     * .value[4].f32 It is a gray-level fuzzy parameter. The value range is [0,127].\n
     * .value[5].f32 It is a gray-level fuzzy parameter. The value range is [0,127].\n
     *
     * @ingroup Visual [视效属性]
     */
    NODE_FOREGROUND_BLUR_STYLE,

    /**
     * @brief Defines the component size and position for layout.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: X coordinate of the component, in px. \n
     * .value[1].i32: Y coordinate of the component, in px. \n
     * .value[2].i32: width of the component, in px. \n
     * .value[3].i32: height of the component, in px. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: X coordinate of the component, in px. \n
     * .value[1].i32: Y coordinate of the component, in px. \n
     * .value[2].i32: width of the component, in px. \n
     * .value[3].i32: height of the component, in px. \n
     *
     */
    NODE_LAYOUT_RECT,

    /**
     * @brief 设置当前组件是否支持点击获焦能力，支持属性设置，属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：参数值为1表示支持点击获焦，为0表示不支持点击获焦。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：参数值为1表示支持点击获焦，为0表示不支持点击获焦。
     *
     */
    NODE_FOCUS_ON_TOUCH,

    /**
     * @brief Defines the border width attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * 1: .value[0].f32: width of the four borders, in percentage. \n
     * 2: .value[0].f32: width of the top border, in percentage. \n
     * .value[1].f32: width of the right border, in percentage. \n
     * .value[2].f32: width of the bottom border, in percentage. \n
     * .value[3].f32: width of the left border, in percentage. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: width of the top border, in percentage. \n
     * .value[1].f32: width of the right border, in percentage. \n
     * .value[2].f32: width of the bottom border, in percentage. \n
     * .value[3].f32: width of the left border, in percentage. \n
     *
     */
    NODE_BORDER_WIDTH_PERCENT = 85,
    /**
     * @brief Defines the border corner radius attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * 1: .value[0].f32: radius of the four corners, in percentage. \n
     * 2: .value[0].f32: radius of the upper left corner, in percentage. \n
     * .value[1].f32: radius of the upper right corner, in percentage. \n
     * .value[2].f32: radius of the lower left corner, in percentage. \n
     * .value[3].f32: radius of the lower right corner, in percentage. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: radius of the upper left corner, in percentage. \n
     * .value[1].f32: radius of the upper right corner, in percentage. \n
     * .value[2].f32: radius of the lower left corner, in percentage. \n
     * .value[3].f32: radius of the lower right corner, in percentage. \n
     *
     */
    NODE_BORDER_RADIUS_PERCENT = 86,

    /**
     * @brief Accessible ID, which can be obtained as required through APIs.
     *
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32：Accessible ID。\n
     *
     */
    NODE_ACCESSIBILITY_ID = 87,

    /**
     * @brief Define accessible actions, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32：accessible action types，and uses the {@link ArkUI_AccessibilityActionType} enumeration value.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32：accessible action types，and uses the {@link ArkUI_AccessibilityActionType} enumeration value.\n
     *
     */
    NODE_ACCESSIBILITY_ACTIONS = 88,

    /**
     * @brief Define accessible role, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32：accessible role type，and uses the {@link ArkUI_NodeType} enumeration value.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32：accessible role type，and uses the {@link ArkUI_NodeType} enumeration value.\n
     *
     */
    NODE_ACCESSIBILITY_ROLE = 89,

    /**
     * @brief Define accessible state, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object：the parameter type is {@link ArkUI_AccessibilityState}.\n
     * \n
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object：the parameter type is {@link ArkUI_AccessibilityState}.\n
     *
     */
    NODE_ACCESSIBILITY_STATE = 90,

    /**
     * @brief Define accessible value, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object：the parameter type is {@link ArkUI_AccessibilityValue}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object：the parameter type is {@link ArkUI_AccessibilityValue}.\n
     *
     */
    NODE_ACCESSIBILITY_VALUE = 91,
    /**
     * @brief defines control components to extend their security zones,
     * supporting property setting, property reset, and property fetching.
     *
     * Attribute setting method {@link ArkUI_AttributeItem} Parameter format: \n
     * .value[0]? .u32: Set of extended security zone enumerated values {@link ArkUI_SafeAreaType},
     * For example, ARKUI_SAFE_AREA_TYPE_SYSTEM | ARKUI_SAFE_AREA_TYPE_CUTOUT; \n
     * .value[1]? .u32: set of directional enum values for extended security zones {@link ArkUI_SafeAreaEdge}; \n
     * For example: ARKUI_SAFE_AREA_EDGE_TOP | ARKUI_SAFE_AREA_EDGE_BOTTOM; \n
     * \n
     * Attribute fetch method return value {@link ArkUI_AttributeItem} format: \n
     *.value[0].u32: extends the security zone. \n. \n
     *.value[1].u32: indicates the direction to extend the security zone. \n. \n
     *
     */
    NODE_EXPAND_SAFE_AREA = 92,

    /**
     * @brief Defines the visible area ratio (visible area/total area of the component) threshold for invoking the
     * visible area change event of the component. Format of the {@link ArkUI_AttributeItem} parameter for setting the
     * attribute:
     * <br>.value[...].f32: threshold array. The value ranges from 0 to 1.
     * <br>.object: The parameter type is {@link ArkUI_VisibleAreaEventOptions}.
     * <br>Format of the return value {@link ArkUI_AttributeItem}:
     * <br>.value[...].f32: threshold array.
     * <br>.object: The return type is {@link ArkUI_VisibleAreaEventOptions}.
     *
     * @since 12
     */
    NODE_VISIBLE_AREA_CHANGE_RATIO = 93,

    /**
     * @brief Sets the transition effect when the component is inserted or deleted.
     * This attribute can be set, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: transition effect. The parameter type is {@link ArkUI_TransitionEffect}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: transition effect. The parameter type is {@link ArkUI_TransitionEffect}. \n
     *
     * @ingroup Animate [动效属性]
     */
    NODE_TRANSITION = 94,

    /**
     * @brief Defines the component ID.
     * This attribute can be obtained through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for obtaining the attribute:\n
     * .value[0].i32: component ID. \n
     *
     * @deprecated since 20
     * @useinstead OH_ArkUI_NodeUtils_GetNodeUniqueId
     */
    NODE_UNIQUE_ID = 95,

    /**
     * @brief 设置当前组件系统焦点框样式。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].f32</b>：焦点框相对组件边缘的距离。正数代表外侧，负数代表内侧。不支持百分比。
     * <br><b>.value[1].f32</b>：焦点框宽度。不支持负数和百分比。
     * <br><b>.value[2].u32</b>：焦点框颜色。
     *
     */
    NODE_FOCUS_BOX = 96,

    /**
     * @brief 组件所绑定的点击手势移动距离限制，支持属性设置。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].f32</b>：表示识别点击手势时允许手指在该范围内移动，单位为vp。
     *
     */
    NODE_CLICK_DISTANCE = 97,

    /**
     * @brief 控制焦点是否能停在当前组件，支持属性设置，属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：参数值为1表示焦点能停在当前组件，为0表示焦点不能停在当前组件。默认值为0。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：参数值为1表示焦点停在当前组件，为0表示焦点未停在当前组件。
     *
     * @since 14
     */
    NODE_TAB_STOP = 98,
    
    /**
     * @brief Defines the backdrop blur attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32：backdrop blur radius, in px. The value range is [0, +∞).\n
     * .value[1]?.f32：grayscale blur settings that control the brightness of the black color.\n
     * The value range is [0, 127].\n
     * .value[2]?.f32：grayscale blur settings that control the darkness of the white color.\n
     * The value range is [0, 127].\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32：backdrop blur radius, in px. The value range is [0, +∞).\n
     * .value[1].f32：grayscale blur settings that control the brightness of the black color.\n
     * The value range is [0, 127].\n
     * .value[2].f32：grayscale blur settings that control the darkness of the white color.\n
     * The value range is [0, 127].\n
     *
     * @ingroup Visual [视效属性]
     * @since 15
     */
    NODE_BACKDROP_BLUR = 99,

    /**
     * @brief Defines the background image resizable attribute, which can be set, reset,
     * and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: width of the left edge. The unit is vp. \n
     * .value[1].f32: width of the top edge. The unit is vp. \n
     * .value[2].f32: width of the right edge. The unit is vp. \n
     * .value[3].f32: width of the bottom edge. The unit is vp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: width of the left edge. The unit is vp. \n
     * .value[1].f32: width of the top edge. The unit is vp. \n
     * .value[2].f32: width of the right edge. The unit is vp. \n
     * .value[3].f32: width of the bottom edge. The unit is vp. \n
     *
     * @since 19
     */
    NODE_BACKGROUND_IMAGE_RESIZABLE_WITH_SLICE = 100,

    /**
     * @brief 设置下一个走焦节点。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：走焦类型，定义在{@link ArkUI_FocusMove}。
     * <br><b>.object</b>：下一个焦点。参数类型为{@link ArkUI_NodeHandle}。
     *
     * @since 18
     */
    NODE_NEXT_FOCUS = 101,

    /**
     * @brief 设置可见区域变化监听的参数。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**说明：**
     * <br>非实时回调，实际回调与预期间隔可能存在差别。两次可见区域回调的时间间隔不小于预期更新间隔。当开发者设置的预期间隔过小时，由系统负载决定实际回调间隔时间。当前接口的可见区域回调阈值默认包含0。例如，开发者设置回调阈值为[
     * 0.5]，实际生效的阈值为[0.0, 0.5]。
     * <br>**参数：**
     * <br><b>.object</b>：参数类型为{@link ArkUI_VisibleAreaEventOptions}。
     * <br>**返回：**
     * <br><b>.object</b>：参数类型为{@link ArkUI_VisibleAreaEventOptions}。
     *
     * @since 17
     */
    NODE_VISIBLE_AREA_APPROXIMATE_CHANGE_RATIO = 102,

    /**
     * @brief Defines the translate attribute, which supports for percentile translation input, and can be set, reset,
     * and obtained as required through APIs.\n
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
     * @ingroup Visual [视效属性]
     * @since 20
     */
    NODE_TRANSLATE_WITH_PERCENT = 103,

    /**
     * @brief Sets component rotation with multi-axis angle control. This attribute can be set, reset,
     * and obtained as required through APIs.
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
     * @ingroup Visual [视效属性]
     * @since 20
     */
    NODE_ROTATE_ANGLE = 104,

    /**
     * @brief Defines the width attribute with param type LayoutPolicy, which can be set, reset, and obtained
     * as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: the LayoutPolicy that the width of the component follows.\n
     * The parameter type is {@link ArkUI_LayoutPolicy}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: the LayoutPolicy that the width of the component follows.\n
     * The parameter type is {@link ArkUI_LayoutPolicy}. \n
     *
     * @since 21
     */
    NODE_WIDTH_LAYOUTPOLICY = 105,

    /**
     * @brief Defines the height attribute with param type LayoutPolicy, which can be set, reset, and obtained
     * as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: the LayoutPolicy that the height of the component follows.\n
     * The parameter type is {@link ArkUI_LayoutPolicy}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: the LayoutPolicy that the height of the component follows.\n
     * The parameter type is {@link ArkUI_LayoutPolicy}. \n
     *
     * @since 21
     */
    NODE_HEIGHT_LAYOUTPOLICY = 106,

    /**
     * @brief Defines the position attribute in param type Edges, which specifies the position of the component
     * by the distance relative to the parent container's four edges. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object indicates struct of edges for position. The parameter type is {@link ArkUI_PositionEdges}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object indicates struct of edges for position. The parameter type is {@link ArkUI_PositionEdges}. \n
     *
     * @since 21
     */
    NODE_POSITION_EDGES = 107,

    /**
     * @brief Set whether the component enables the ability to invert colors.
     * This attribute can be set , and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The parameter type is 1 or 0.\n
     *
     * @since 21
     */
    NODE_ALLOW_FORCE_DARK = 108,

    /**
     * @brief Defines the pixelRound attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object indicates struct of policy for pixelRound. The parameter type is {@link ArkUI_PixelRoundPolicy}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object indicates struct of policy for pixelRound. The parameter type is {@link ArkUI_PixelRoundPolicy}. \n
     *
     * @since 21
     */
    NODE_PIXEL_ROUND = 109,

    /**
     * @brief 设置组件是否启用默认点击音效。此功能仅在TV上生效，在其他设备上启用默认点击音效也不会播放音效。是否能够发音依赖设备声音相关的设置，如静音模式下不会播放音效。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：参数取值为1或0，1表示启用默认点击音效，0表示禁用默认点击音效，默认值为1。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：表示此节点是否启用了默认的点击音效。参数取值为1或0，1表示启用默认点击音效，0表示禁用默认点击音效。
     *
     * @since 24
     */
    NODE_ENABLE_CLICK_SOUND_EFFECT = 110,

    /**
     * @brief Defines the motion path attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute: \n
     * .object indicates a pointer to the ArkUI_MotionPathOptions. The parameter type is
     * {@link ArkUI_MotionPathOptions}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}: \n
     * .object indicates a pointer to the ArkUI_MotionPathOptions. The parameter type is
     * {@link ArkUI_MotionPathOptions}. \n
     *
     * @ingroup Animate [动效属性]
     * @since 23
     */
    NODE_MOTION_PATH = 111,

    /**
     * @brief 定义组件被悬停时的效果。该属性可根据需要通过API进行设置、重置和获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：组件在悬停状态下的悬停效果。参数类型为{@link ArkUI_HoverEffect}。默认值为ARKUI_HOVER_EFFECT_AUTO。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：组件在悬停状态下的悬停效果。参数类型为{@link ArkUI_HoverEffect}。
     *
     * @since 23
     */
    NODE_HOVER_EFFECT = 112,

    /**
     * @brief 将容器设置为具有特定标识符的焦点组，支持属性设置、属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.string</b>：焦点作用域标识符。
     * <br><b>.value[0].i32</b>：该作用域是否为焦点组，默认值为0。取值范围为1或0。1表示设置为焦点组，0表示组件未被设置为焦点组。
     * <br><b>.value[1].i32</b>：箭头键是否可以将焦点从焦点组内部移至外部，仅当isGroup为true时有效，默认值为1。取值范围为1或0。1表示箭头键可以将焦点从焦点组内部移至外部，
     * 0表示箭头键无法将焦点从焦点组内部移至外部。
     * <br>**返回：**
     * <br><b>.string</b>：焦点作用域标识符。
     * <br><b>.value[0].i32</b>：该作用域是否为焦点组，默认值为0。取值范围为1或0。1表示设置为焦点组，0表示组件未被设置为焦点组。
     * <br><b>.value[1].i32</b>：箭头键是否可以将焦点从焦点组内部移至外部，仅当isGroup为true时有效，默认值为1。取值范围为1或0。1表示箭头键可以将焦点从焦点组内部移至外部，
     * 0表示箭头键无法将焦点从焦点组内部移至外部。
     *
     * @since 23
     */
    NODE_FOCUS_SCOPE_ID = 113,

    /**
     * @brief 设置组件在特定焦点作用域内的焦点优先级，支持属性设置、属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.string</b>：焦点作用域标识符。
     * <br><b>.value[0].i32</b>：焦点作用域内获焦优先级。参数类型为{@link ArkUI_FocusPriority}。默认值为ARKUI_FOCUS_PRIORITY_AUTO。
     * <br>**返回：**
     * <br><b>.string</b>：焦点作用域标识符。
     * <br><b>.value[0].i32</b>：焦点作用域优先级。参数类型为{@link ArkUI_FocusPriority}。
     *
     * @since 23
     */
    NODE_FOCUS_SCOPE_PRIORITY = 114,

    /**
     * @brief 设置点击事件的距离阈值，支持属性设置、属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].f32</b>：点击事件移动阈值。取值范围(0, +∞)。默认值为+∞，单位vp。
     * <br>**返回：**
     * <br><b>.value[0].f32</b>：点击事件移动阈值。
     *
     * @since 23
     */
    NODE_ON_CLICK_EVENT_DISTANCE_THRESHOLD = 115,

    /**
     * @brief 设置组件事件的响应区域，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**说明：**
     * <br>设置时data数据大小无数量限制，均可以设置成功，但仅支持获取到20个。获取到的data数组顺序与设置顺序可能存在差异。
     * <br>**参数：**
     * <br><b>.data[0].i32</b>：适用于此响应区域的事件工具类型。参数类型为{@link ArkUI_ResponseRegionSupportedTool}。默认值：
     * ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_ALL。
     * <br><b>.data[1].f32</b>：触摸点相对于组件左上角的x轴坐标，默认值：0.0，单位为vp。
     * <br><b>.data[2].f32</b>：触摸点相对于组件左上角的y轴坐标，默认值：0.0，单位为vp。
     * <br><b>.data[3].f32</b>：触摸热区的宽度，默认值：100.0，单位为百分比。
     * <br><b>.data[4].f32</b>：触摸热区的高度，默认值：100.0，单位为百分比。
     * <br><b>.data[5...].f32</b>：可以设置多个手势响应区域，顺序和上述一致。
     * <br>**返回：**
     * <br><b>.data[0].i32</b>：适用于此响应区域的事件工具类型。参数类型为{@link ArkUI_ResponseRegionSupportedTool}。默认值：
     * ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_ALL。
     * <br><b>.data[1].f32</b>：触摸点相对于组件左上角的x轴坐标，默认值：0.0，单位为vp。
     * <br><b>.data[2].f32</b>：触摸点相对于组件左上角的y轴坐标，默认值：0.0，单位为vp。
     * <br><b>.data[3].f32</b>：触摸热区的宽度，默认值：100.0，单位为百分比。
     * <br><b>.data[4].f32</b>：触摸热区的高度，默认值：100.0，单位为百分比。
     * <br><b>.data[5...].f32</b>：可以设置多个手势响应区域，顺序和上述一致。
     *
     * @since 23
     */
    NODE_RESPONSE_REGION_LIST = 116,

    /**
     * @brief 定义独占事件属性，该属性可根据需要通过API进行设置、重置和获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br><b>.value[0].i32</b>：取值范围为1或0。1表示设置组件独占，0表示组件未设置独占属性。
     * <br>**返回：**
     * <br><b>.value[0].i32</b>：取值范围为1或0。1表示设置组件独占，0表示组件未设置独占属性。
     *
     * @since 23
     */
    NODE_MONOPOLIZE_EVENTS = 117,

    /**
     * @brief Sets the weight of the component in a chain, which is used to re-lay out components that form the chain.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: Horizontal ChainWeight.\n
     * .value[1].f32: Vertical ChainWeight.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: Horizontal ChainWeight.\n
     * .value[1].f32: Vertical ChainWeight.\n
     *
     * @since 23
     */
    NODE_CHAIN_WEIGHT = 118,

    /**
     * @brief Expands the layout safe area of a component.,
     * supporting property setting, property reset, and property fetching.
     *
     * Attribute setting method {@link ArkUI_AttributeItem} Parameter format: \n
     * .value[0].u32: The region type to expand the component's layout safe area into. The default value is LayoutSafeAreaType.SYSTEM. {@link ArkUI_LayoutSafeAreaType},
     * For example, ARKUI_LAYOUT_SAFE_AREA_TYPE_SYSTEM; \n
     * .value[1].u32: The set of edges for which to ignore layout safe area. The default value is LayoutSafeAreaEdge.ALL. {@link ArkUI_LayoutSafeAreaEdge}; \n
     * For example: ARKUI_LAYOUT_SAFE_AREA_EDGE_TOP | ARKUI_LAYOUT_SAFE_AREA_EDGE_START; \n
     * \n
     * Attribute fetch method return value {@link ArkUI_AttributeItem} format: \n
     *.value[0].u32: The region type to expand the component's layout safe area into. \n
     *.value[1].u32: The set of edges for which to ignore layout safe area. \n
     *
     * @since 23
     */
    NODE_IGNORE_LAYOUT_SAFE_AREA = 119,

    /**
     * @brief Defines the length of dash when BorderStyle is dashed, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: The length of dash on the top border. \n
     * .value[1].f32: The length of dash on the right border. \n
     * .value[2].f32: The length of dash on the bottom border. \n
     * .value[3].f32: The length of dash on the left border. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: The length of dash on the top border. \n
     * .value[1].f32: The length of dash on the right border. \n
     * .value[2].f32: The length of dash on the bottom border. \n
     * .value[3].f32: The length of dash on the left border. \n
     *
     * @since 23
     */
    NODE_DASH_WIDTH = 120,

    /**
     * @brief Defines the gap of dash when BorderStyle is dashed, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: The gap of dash on the top border. \n
     * .value[1].f32: The gap of dash on the right border. \n
     * .value[2].f32: The gap of dash on the bottom border. \n
     * .value[3].f32: The gap of dash on the left border. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: The gap of dash on the top border. \n  
     * .value[1].f32: The gap of dash on the right border. \n
     * .value[2].f32: The gap of dash on the bottom border. \n
     * .value[3].f32: The gap of dash on the left border. \n
     *
     * @since 23
     */
    NODE_DASH_GAP = 121,

    /**
     * @brief Defines the align rules of child component in Stack container, which can be set, reset, and obtained as required through APIs.\n
     * The default value is <b>ARKUI_LOCALIZED_ALIGNMENT_CENTER</b>. \n
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: LocalizedAlignment mode. The data type is {@link ArkUI_LocalizedAlignment}.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: LocalizedAlignment mode. The data type is {@link ArkUI_LocalizedAlignment}. \n
     *
     * @since 23
     */
    NODE_LAYOUT_GRAVITY = 122,

    /**
     * @brief Defines the render types for drawing rounded corners when the radius of the border rounded corners is set, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: Render types for drawing rounded corners. The data type is {@link ArkUI_RenderStrategy}.
     * The default value is <b>ARKUI_RENDERSTRATEGY_FAST</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: Render types for drawing rounded corners. The data type is {@link ArkUI_RenderStrategy}. \n
     *
     * @since 23
     */
    NODE_BORDER_RADIUS_TYPE = 123,
    
    /**
     * @brief Defines the inspector label attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: inspector label.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: inspector label.\n
     * \n
     * @since 26.0.0
     */
    NODE_INSPECTOR_LABEL = 126,

    /**
     * @brief Defines the next accessibility focus id of current component for accessibility processing to find the next focus component. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: accessibility next focus ID.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: accessibility next focus ID.
     * \n
     * @since 26.0.0
     */
    NODE_ACCESSIBILITY_NEXT_FOCUS_ID = 124,

    /**
     * @brief Sets the accessibility default focus flag for accessibility services to find the default focus component. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: Accessibility default focus. The value <b>1</b> means that the component is defined as default focus in accessibility services.\n
     * The value is <b>1</b> or <b>0</b>.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: Accessibility default focus. The value <b>1</b> means that the component is defined as default focus in accessibility services.\n
     * The value is <b>1</b> or <b>0</b>.
     * \n
     * @since 26.0.0
     */
    NODE_ACCESSIBILITY_DEFAULT_FOCUS = 125,

    /**
     * @brief Defines the system material attribute, which can be set, reset, and obtained as required through APIs.
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
     * @ingroup Visual [视效属性]
     * @since 26.0.0
     */
    NODE_SYSTEM_MATERIAL = 127,

    /**
     * @brief Text组件设置文本内容属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：表示文本内容。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：表示文本内容。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT,
    /**
     * @brief 组件字体颜色属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：字体颜色数值，0xargb格式，形如 0xFFFF0000 表示红色。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：字体颜色数值，0xargb格式。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_FONT_COLOR,
    /**
     * @brief 组件字体大小属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：字体大小数值，单位为fp。取值范围：[0, +∞)。传入负数时参数不生效。默认值：16fp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：字体大小数值，单位为fp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_FONT_SIZE,
    /**
     * @brief 组件字体样式属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：字体样式，具体枚举值请参考{@link ArkUI_FontStyle}。默认值为ARKUI_FONT_STYLE_NORMAL。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：字体样式{@link ArkUI_FontStyle}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_FONT_STYLE,
    /**
     * @brief 组件字体粗细属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：字体粗细样式{@link ArkUI_FontWeight}。取值越大字体越粗。默认值为ARKUI_FONT_WEIGHT_NORMAL。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：字体粗细样式{@link ArkUI_FontWeight}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_FONT_WEIGHT,
    /**
     * @brief 文本行高属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：表示行高值，单位为fp。取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：表示行高值，单位为fp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_LINE_HEIGHT,
    /**
     * @brief Defines the text decoration style and color.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: text decoration type {@link ArkUI_TextDecorationType}.
     * The default value is <b>ARKUI_TEXT_DECORATION_TYPE_NONE</b>.\n
     * .value[1]?.u32: text decoration color, in 0xARGB format. For example, 0xFFFF0000 indicates red. Optional.\n
     * .value[2]?.i32: text decoration style {@link ArkUI_TextDecorationStyle}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: text decoration type {@link ArkUI_TextDecorationType}.\n
     * .value[1].u32: text decoration color, in 0xARGB format. \n
     * .value[2].i32: text decoration style {@link ArkUI_TextDecorationStyle}. \n
     *
     */
    /**
     * @brief 文本装饰线样式及其颜色属性，支持属性设置、属性重置和属性获取接口。适用于添加文本装饰效果，如下划线表示链接、删除线表示已删除内容、或上划线表示强调。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本装饰线类型，具体枚举值请参考{@link ArkUI_TextDecorationType}。默认值为ARKUI_TEXT_DECORATION_TYPE_NONE，无装饰线。</li>
     * <li>.value[1]?.u32：可选值，装饰线颜色，0xargb格式，形如 0xFFFF0000 表示红色。默认值：0xFF000000，表示黑色。</li>
     * <li>.value[2]?.i32：文本装饰线样式，具体枚举值请参考{@link ArkUI_TextDecorationStyle}。默认值为ARKUI_TEXT_DECORATION_STYLE_SOLID，实线装饰线。</li>
     * <li>.value[3]?.f32：可选值，文本装饰线粗细比例，默认值：1.0，取值范围：[0, +∞)。传入负数时参数不生效。该参数从API version 22开始支持。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本装饰线类型{@link ArkUI_TextDecorationType}。</li>
     * <li>.value[1].u32：装饰线颜色，0xargb格式。</li>
     * <li>.value[2].i32：文本装饰线样式{@link ArkUI_TextDecorationStyle}。</li>
     * <li>.value[3].f32：文本装饰线粗细比例。该返回值从API version 22开始支持。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_DECORATION,
    /**
     * @brief 文本大小写属性，支持属性设置、属性重置和属性获取接口。适用于控制文本显示格式，如显示标题时自动大写、或格式化用户输入为统一大小写。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本大小写类型，具体枚举值请参考{@link ArkUI_TextCase}。默认值为ARKUI_TEXT_CASE_NORMAL，表示保持原样。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本大小写类型{@link ArkUI_TextCase}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_CASE,
    /**
     * @brief 文本字符间距属性，支持属性设置、属性重置和属性获取接口。适用于调整文本排版效果，如设置标题字符间距以增强视觉效果、或调整特殊文本样式的排版美观度。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：表示字符间距值，单位为fp。取值范围：(-∞, +∞)。当取值为负值时，文字会被压缩。负值过小时会将组件内容区大小压缩为0，导致内容无法显示。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：表示字符间距值，单位为fp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_LETTER_SPACING,
    /**
     * @brief 文本最大行数属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示最大行数，取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示最大行数。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_MAX_LINES,
    /**
     * @brief 文本水平对齐方式，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本水平对齐方式，具体枚举值请参考{@link ArkUI_TextAlignment}。默认值为ARKUI_TEXT_ALIGNMENT_START，表示水平对齐首部。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本水平对齐方式，取{@link ArkUI_TextAlignment}枚举值。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_ALIGN,
    /**
     * @brief 文本超长时的显示方式属性，支持属性设置、属性重置和属性获取接口。适用于处理文本内容超出显示区域的场景，如单行标题显示时使用省略号、或卡片内容截断显示等。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本超长时的显示方式，具体枚举值请参考{@link ArkUI_TextOverflow}。默认值为ARKUI_TEXT_OVERFLOW_NONE，表示文本超长时不裁剪显示。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本超长时的显示方式{@link ArkUI_TextOverflow}。</li>
     * </ul>
     *
     * 说明：支持此属性的{@link ArkUI_NodeType}为：ARKUI_NODE_TEXT、ARKUI_NODE_TEXT_INPUT、ARKUI_NODE_TEXT_AREA。\n
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_OVERFLOW,
    /**
     * @brief Text字体列表属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：字体字符串，多个字体用英文逗号(,)分隔。不传入时使用系统默认字体。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：字体字符串，多个字体用英文逗号(,)分隔。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_FONT_FAMILY,
    /**
     * @brief 文本复制粘贴属性，支持属性设置、属性重置和属性获取接口。适用于控制文本复制粘贴行为，如密码输入框禁止复制、或敏感信息保护。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：复制粘贴方式，具体枚举值请参考{@link ArkUI_CopyOptions}。默认值为ARKUI_COPY_OPTIONS_NONE，表示不支持复制。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：复制粘贴方式{@link ArkUI_CopyOptions}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_COPY_OPTION,
    /**
     * @brief 文本基线的偏移量属性，支持属性设置、属性重置和属性获取接口。适用于调整文本基线位置，如显示上下标时调整偏移量、或图文混排时实现文本与图片的精确对齐。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：偏移量数值，单位为fp。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：偏移量数值，单位为fp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_BASELINE_OFFSET,
    /**
     * @brief 文字阴影效果属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：阴影模糊半径，单位为vp。取值范围：[0, +∞)。默认值为0，表示无模糊效果。</li>
     * <li>.value[1].i32：阴影类型，具体枚举值请参考{@link ArkUI_ShadowType}。默认值为ARKUI_SHADOW_TYPE_COLOR，表示颜色阴影。</li>
     * <li>.value[2].u32：阴影颜色，0xargb格式，形如 0xFFFF0000 表示红色。</li>
     * <li>.value[3].f32：阴影X轴偏移量，单位为vp。</li>
     * <li>.value[4].f32：阴影Y轴偏移量，单位为vp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：阴影模糊半径，单位为vp。</li>
     * <li>.value[1].i32：阴影类型{@link ArkUI_ShadowType}。</li>
     * <li>.value[2].u32：阴影颜色，0xargb格式。</li>
     * <li>.value[3].f32：阴影X轴偏移量，单位为vp。</li>
     * <li>.value[4].f32：阴影Y轴偏移量，单位为vp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_TEXT_SHADOW,
    /**
     * @brief Text最小显示字号，支持属性设置、属性重置和属性获取。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：文本最小显示字号，单位为fp。取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：文本最小显示字号，单位为fp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_MIN_FONT_SIZE,

    /**
     * @brief Text最大显示字号，支持属性设置、属性重置和属性获取。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：文本最大显示字号，单位为fp。取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：文本最大显示字号，单位为fp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_MAX_FONT_SIZE,

    /**
     * @brief Text样式，支持属性设置、属性重置和属性获取。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string?：可选值：字体列表，多个字体使用','进行分隔。不传入时使用系统默认字体。</li>
     * <li>.value[0].f32：文本尺寸，单位为fp。取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * <li>.value[1]?.i32：可选值，文本的字体粗细，具体枚举值请参考{@link ArkUI_FontWeight}。取值越大字体越粗。默认值为ARKUI_FONT_WEIGHT_NORMAL。</li>
     * <li>.value[2]?.i32：可选值，字体样式，具体枚举值请参考{@link ArkUI_FontStyle}。默认值为ARKUI_FONT_STYLE_NORMAL。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：字体列表，使用多个字体，使用','进行分割。</li>
     * <li>.value[0].f32：文本尺寸，单位为fp。取值范围：[0, +∞)。</li>
     * <li>.value[1].i32：文本的字体粗细，具体枚举值请参考{@link ArkUI_FontWeight}。默认值为ARKUI_FONT_WEIGHT_NORMAL。</li>
     * <li>.value[2].i32：字体样式，具体枚举值请参考{@link ArkUI_FontStyle}。默认值为ARKUI_FONT_STYLE_NORMAL。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_FONT,

    /**
     * @brief Text自适应高度的方式，支持属性设置、属性重置和属性获取。适用于文本内容动态变化的场景，如优先按最大行数限制高度、或优先按最小字号确保文本可读性等。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：参数类型，具体枚举值请参考{@link ArkUI_TextHeightAdaptivePolicy}。默认值为ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST，表示以MaxLines优先。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：获取的文本自适应高度方式的枚举值，参数类型{@link ArkUI_TextHeightAdaptivePolicy}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_HEIGHT_ADAPTIVE_POLICY,
    /**
     * @brief 文本首行缩进属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：表示首行缩进值，入参单位为fp，返回值单位为vp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：表示首行缩进值，入参单位为fp，返回值单位为vp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_INDENT,
    /**
     * @brief 文本断行规则属性，支持属性设置、属性重置和属性获取接口。适用于控制文本换行方式， \n
     * 如英文单词完整断行、或中文任意字符断行等不同排版需求。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：参数类型，具体枚举值请参考{@link ArkUI_WordBreak}。默认值为ARKUI_WORD_BREAK_BREAK_WORD，对于Non-CJK的文本可在任意2个字符间断行，
     * 一行文本中有断行破发点（如空白符）时，优先按破发点换行。对于CJK的文本，换行效果与NORMAL效果保持一致。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：获取的文本断行规则枚举值，参数类型{@link ArkUI_WordBreak}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_WORD_BREAK,
    /**
     * @brief 设置文本省略位置，支持属性设置、属性重置和属性获取接口。适用于控制文本省略号显示位置，如尾部省略适合常规文本、头部省略适合路径显示、中间省略适合长标题等。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：参数类型，具体枚举值请参考{@link ArkUI_EllipsisMode}。默认值为ARKUI_ELLIPSIS_MODE_END，表示省略行末内容。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：获取的文本省略位置枚举值，参数类型{@link ArkUI_EllipsisMode}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_ELLIPSIS_MODE,
    /**
     * @brief 文本行间距属性，支持属性设置、属性重置和属性获取接口。适用于调整多行文本的间距，如优化阅读体验、或实现特定的排版风格效果。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：表示行间距值，单位为fp。取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：表示行间距值，单位为fp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_LINE_SPACING,
    /**
     * @brief 设置文本特性效果。NODE_FONT_FEATURE是OpenType字体的高级排版能力，如支持连字、数字等宽等特性，一般用在自定义字体中，其能力需要字体本身支持。支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：符合文本特性格式的字符串，格式为normal | <feature-tag-value>。 \n
     * <feature-tag-value>的格式为：string [ <integer> | on | off ]。 \n
     * <feature-tag-value>的个数可以有多个，中间用','隔开，例如，使用等宽数字的输入格式为：ss01 on。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：表示文本特性的内容，多个文本特性之间使用逗号分隔。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_FONT_FEATURE,
    /**
     * @brief 设置是否使能文本实体识别，识别的实体类型可通过NODE_TEXT_ENABLE_DATA_DETECTOR_CONFIG属性配置。
     * 适用于识别文本中的特定实体类型（如电话号码、邮箱地址、网址链接等），实现点击跳转、智能交互等功能。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：使能文本识别，1表示文本可实体识别，0表示不可识别。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：使能文本识别。1表示文本可实体识别，0表示不可识别。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_ENABLE_DATA_DETECTOR,
    /**
     * @brief 设置文本识别配置。适用于自定义需要识别的实体类型（如电话号码、邮箱地址、网址链接等），实现精准的文本智能识别和交互功能。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0...].i32：实体类型数组，参数类型{@link ArkUI_TextDataDetectorType}。数组中可包含电话号码、URL、邮箱等实体类型，
     * 具体取值请参考枚举定义。本参数仅在NODE_TEXT_ENABLE_DATA_DETECTOR设置为1（开启文本实体识别）时生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0...].i32：实体类型数组，参数类型{@link ArkUI_TextDataDetectorType}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_ENABLE_DATA_DETECTOR_CONFIG,
    /**
     * @brief 文本选中时的背景色属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：颜色数值，0xargb格式，形如 0xFFFF0000 表示红色。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：颜色数值，0xargb格式。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_SELECTED_BACKGROUND_COLOR,

    /**
     * @brief Text组件使用格式化字符串对象设置文本内容属性，支持属性设置、属性重置和属性获取接口。
     *        配置自定义{@link OH_Drawing_Typography}对象到Text组件，会跳过文本控件的布局测算阶段。注意事项：\n
     *        1. 需要保证OH_ArkUI_StyledString对象、OH_Drawing_Typography对象的生命周期跟随Text组件生命周期，
     *        Text组件析构时重置OH_ArkUI_StyledString对象，否则会导致应用出现空指针崩溃。\n
     *        2. 保证OH_Drawing_TypographyLayout方法调用时序在Text组件的布局测算之前。\n
     *        3. 释放OH_ArkUI_StyledString对象、OH_Drawing_Typography对象时，需要同步调用Text组件的reset方法，否则会导致应用出现空指针崩溃。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：表示 ArkUI_StyledString 格式化字符串数据，参数类型为{@link ArkUI_StyledString}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：表示 ArkUI_StyledString 格式化字符串数据，参数类型为{@link ArkUI_StyledString}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_CONTENT_WITH_STYLED_STRING,

    /**
     * @brief Text组件设置文本纵向居中显示。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本是否纵向居中显示，默认值：0。\n
     * 1表示文本是纵向居中显示，0表示文本不是纵向居中显示。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本是否纵向居中显示。1表示文本纵向居中显示，0表示文本不纵向居中显示。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_HALF_LEADING = 1029,

    /**
     * @brief 组件字体粗细属性，支持属性设置、属性重置和属性获取接口。
     * 通过此接口设置的粗细属性不会跟随系统字体粗细变化。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：字体粗细样式{@link ArkUI_FontWeight}。取值越大字体越粗，默认值为ARKUI_FONT_WEIGHT_NORMAL。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：字体粗细样式{@link ArkUI_FontWeight}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 15
     *
     */
    NODE_IMMUTABLE_FONT_WEIGHT = 1030,

    /**
     * @brief Defines the text line count attribute, which can only be obtained as required through APIs.
     *
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: line count of the node.
     *
     * @since 20
     */
    NODE_TEXT_LINE_COUNT = 1031,
 
    /**
     * @brief 设置文本排版时是否优化每行结尾的空格，支持属性设置、属性重置和属性获取接口。适用于优化文本排版效果，如去除结尾多余空格以实现更好的文本对齐。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：设置文本排版时是否优化每行结尾的空格，默认值：0。\n
     * 1表示设置文本排版时优化每行结尾的空格，0表示不优化。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本排版时是否优化每行结尾的空格。1表示已开启优化，0表示未开启优化。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 20
     *
     */
    NODE_TEXT_OPTIMIZE_TRAILING_SPACE = 1032,

    /**
     * @brief 设置文本线性渐变效果，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：线性渐变的起始角度，单位为deg。当direction属性设置为ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM时，angle属性生效； \n
     * 否则，以direction属性为主要布局方式。0点方向顺时针旋转为正向角度，默认值：180。</li>
     * <li>.value[1].i32：线性渐变的方向{@link ArkUI_LinearGradientDirection}。设置除ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM之外的线性渐变方向后，angle不生效。 \n
     * 默认值：ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_BOTTOM。</li>
     * <li>.value[2].i32：是否为渐变的颜色重复着色，0表示不重复着色，1表示重复着色。默认值：0。</li>
     * <li>.object：参数类型为{@link ArkUI_ColorStop}。指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过。</li>
     * <li>colors：渐变色颜色数组，数组元素为0xargb格式，形如0xFFFF0000表示红色。</li>
     * <li>stops：stops表示指定颜色所处位置的数组，数组元素取值范围为[0,1.0]，0表示需要设置渐变色的容器的开始处，1.0表示容器的结尾处。 \n
     * 想要实现多个颜色渐变效果时，数组元素建议递增设置，如后一个数组元素比前一个数组元素小的话，按照等于前一个数组元素的值处理。</li>
     * <li>size：颜色个数，若小于colors数组长度则仅生效前size个颜色，不建议设置大于colors数组长度或小于等于0的值以及异常值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：线性渐变的起始角度。当为ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM时，angle为设置值，其他情况均为默认值0。</li>
     * <li>.value[1].i32：线性渐变的方向{@link ArkUI_LinearGradientDirection}。</li>
     * <li>.value[2].i32：为渐变的颜色重复着色，0表示不重复着色，1表示重复着色。默认值：0。</li>
     * <li>.object：参数类型为{@link ArkUI_ColorStop}。指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过。</li>
     * <li>colors：渐变色颜色数组，数组元素为0xargb格式，形如0xFFFF0000表示红色。</li>
     * <li>stops：stops表示指定颜色所处位置的数组，数组元素取值范围为[0,1.0]，0表示需要设置渐变色的容器的开始处，1.0表示容器的结尾处。</li>
     * <li>size：生效后渐变色的颜色个数。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 20
     *
     */
    NODE_TEXT_LINEAR_GRADIENT = 1033,

    /**
     * @brief 设置文本径向渐变效果，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0]?.f32：为径向渐变的中心点，即相对于当前文本框左上角的X轴坐标，单位为vp。默认值：0。</li>
     * <li>.value[1]?.f32：为径向渐变的中心点，即相对于当前文本框左上角的Y轴坐标，单位为vp。文本框左上角的坐标为[0,0]。默认值：0。</li>
     * <li>.value[2]?.f32：径向渐变的半径，默认值0。取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * <li>.value[3]?.i32：是否为渐变的颜色重复着色，0表示不重复着色，1表示重复着色。默认值：0。</li>
     * <li>.object：参数类型为{@link ArkUI_ColorStop}。指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过。 \n
     * colors：渐变色颜色数组，数组元素为0xargb格式，形如0xFFFF0000表示红色。 \n
     * stops：stops表示指定颜色所处位置的数组，数组元素取值范围为[0,1.0]，0表示需要设置渐变色的容器的开始处，1.0表示容器的结尾处。 \n
     * 想要实现多个颜色渐变效果时，数组元素建议递增设置，如后一个数组元素比前一个数组元素小的话，按照等于前一个数组元素的值处理。 \n
     * size：颜色个数，若小于colors数组长度则仅生效前size个颜色，不建议设置大于colors数组长度或小于等于0的值以及异常值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0]?.f32：为径向渐变的中心点，即相对于当前文本框左上角的X轴坐标，单位为vp。</li>
     * <li>.value[1]?.f32：为径向渐变的中心点，即相对于当前文本框左上角的Y轴坐标，单位为vp。文本框左上角的坐标为[0,0]。</li>
     * <li>.value[2]?.f32：径向渐变的半径，单位为vp。默认值0。</li>
     * <li>.value[3]?.i32：为渐变的颜色重复着色，0表示不重复着色，1表示重复着色。默认值：0。</li>
     * <li>.object：参数类型为{@link ArkUI_ColorStop}。指定某百分比位置处的渐变色颜色，设置非法颜色直接跳过。 \n
     * colors：渐变色颜色数组，数组元素为0xargb格式，形如0xFFFF0000表示红色。 \n
     * stops：stops表示指定颜色所处位置的数组，数组元素取值范围为[0,1.0]，0表示需要设置渐变色的容器的开始处，1.0表示容器的结尾处。 \n
     * size：生效后渐变色的颜色个数。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 20
     *
     */
    NODE_TEXT_RADIAL_GRADIENT = 1034,

    /**
     * @brief 设置文本内容垂直对齐方式，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本内容垂直对齐方式{@link ArkUI_TextVerticalAlignment}，默认值：ARKUI_TEXT_VERTICAL_ALIGNMENT_BASELINE。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本内容垂直对齐方式{@link ArkUI_TextVerticalAlignment}。</li>
     * </ul>
     *
     * 说明：支持此属性的{@link ArkUI_NodeType}为：ARKUI_NODE_TEXT。\n
     *
     * @ingroup Text Display[文本显示]
     * @since 20
     *
     */
    NODE_TEXT_VERTICAL_ALIGN = 1035,

    /**
     * @brief 设置文本内容区垂直对齐方式，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本内容垂直对齐方式{@link ArkUI_TextContentAlign}，默认值：ARKUI_TEXT_CONTENT_ALIGN_CENTER。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本内容垂直对齐方式{@link ArkUI_TextContentAlign}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 21
     *
     */
    NODE_TEXT_CONTENT_ALIGN = 1036,

    /**
     * @brief 文本最小行数属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本最小行数，取值范围：正整数。传入0或负数时参数不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本最小行数，取值范围：正整数。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 22
     *
     */
    NODE_TEXT_MIN_LINES = 1037,

    /**
     * @brief 开启选中词的文本实体识别，用于在用户选中文本时识别其中的特定类型数据（如电话号码、邮箱、网址等）。
     * 适用于用户选中文本后进行智能识别，如识别选中词的语义类型、实现智能搜索推荐或上下文分析等功能。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：开启选中词文本识别，1表示开启识别，0表示关闭识别。默认值：1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启选中词文本识别。1表示已开启识别，0表示已关闭识别。</li>
     * </ul>
     *
     * @since 22
     *
     */
    NODE_TEXT_ENABLE_SELECTED_DATA_DETECTOR = 1038,

    /**
     * @group {ArkUI_NodeAttributeType (文本显示类组件相关属性)}[capi-native-node-h-node-attributetype-text]
     * @brief 设置文本最小行高，支持属性设置、属性重置和属性获取接口。适用于限制文本行高的最小值，如确保文本可读性、或防止行高过小导致文字重叠显示。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：文本最小行高，默认值：0。单位为fp。取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：文本最小行高。单位为fp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 22
     *
     */
    NODE_TEXT_MIN_LINE_HEIGHT = 1040,

    /**
     * @brief 设置文本最大行高，支持属性设置、属性重置和属性获取接口。适用于限制文本行高的最大值，如控制文本布局紧凑度、或防止行高过大导致显示空间浪费。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：文本最大行高，默认值：0，表示最大行高不受限制。单位为fp。取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：文本最大行高。单位为fp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 22
     *
     */
    NODE_TEXT_MAX_LINE_HEIGHT = 1041,

    /**
     * @brief 设置倍数行高模式的倍数值，支持属性设置、属性重置和属性获取接口。适用于相对字号设置行高，如实现动态排版、或字号变化时自动调整行高。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：倍数行高模式的倍数值，默认值：0，表示使用默认行高高度。取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：倍数行高模式的倍数值。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 22
     *
     */
    NODE_TEXT_LINE_HEIGHT_MULTIPLE = 1042,

    /**
     * @brief 文本布局管理器，支持属性获取接口。适用于获取文本布局信息，如查询文本行数、字符位置、测量文本尺寸等。
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：文本布局管理器对象，参数类型为{@link ArkUI_TextLayoutManager}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 22
     */
    NODE_TEXT_LAYOUT_MANAGER = 1043,

    /**
     * @brief 文本菜单扩展项，支持属性设置接口。适用于扩展文本编辑菜单，如添加自定义操作项、或扩展复制粘贴等功能。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：文本菜单扩展项配置数据，参数类型为{@link ArkUI_TextEditMenuOptions}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 22
     */
    NODE_TEXT_EDIT_MENU_OPTIONS = 1044,

    /**
     * @brief 自定义文本选择菜单，支持属性设置接口。适用于定制文本选择菜单，如添加特定操作按钮、或定制菜单UI风格。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：自定义文本选择菜单配置数据，参数类型为{@link ArkUI_TextSelectionMenuOptions}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 22
     */
    NODE_TEXT_BIND_SELECTION_MENU = 1045,

    /**
     * @brief 设置文本选择区域，设置后选中区域将被高亮显示，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本选择的起始位置。取值范围：[0, 文本长度]，必须是有效的文本索引。</li>
     * <li>.value[1].i32：文本选择的结束位置。取值范围：[0, 文本长度]，必须是有效的文本索引。</li>
     * <li>.object：选择选项。参数类型为{@link ArkUI_SelectionOptions}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本选择的起始位置。</li>
     * <li>.value[1].i32：文本选择的结束位置。</li>
     * <li>.object：选择选项。参数类型为{@link ArkUI_SelectionOptions}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 23
     *
     */
    NODE_TEXT_TEXT_SELECTION = 1046,

    /**
     * @brief 设置Text文本排版时是否使能孤字优化，设置后通过更高效地处理孤立字符（段落尾行首字符）来改善文本布局。
     * 使能后，它会调整换行点以尽可能避免孤立字符。孤字优化特性需在{@link ArkUI_WordBreak}属性为非ARKUI_WORD_BREAK_BREAK_ALL时生效。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否使能孤字优化，1表示使能，0表示不使能。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否使能孤字优化。1表示已使能孤字优化，0表示未使能孤字优化。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 26.0.0
     *
     */
 	  NODE_TEXT_ORPHAN_CHAR_OPTIMIZATION = 1047,

    /**
     * @brief 文本行首标点压缩开关，支持属性设置、属性重置和属性获取接口。适用于中文排版场景，压缩行首标点以提升排版美观度和阅读体验。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否打开行首标点压缩开关。\n
     * 1表示开启行首标点压缩，0表示关闭行首标点压缩。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否打开行首标点压缩开关。1表示已开启行首标点压缩，0表示已关闭行首标点压缩。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 23
     *
     */
    NODE_TEXT_COMPRESS_LEADING_PUNCTUATION = 1048,

    /**
     * @brief 设置是否在首行和尾行增加间距以避免文字截断。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：设置是否在首行和尾行增加间距以避免文字截断。\n
     * 1表示开启增加间距，0表示关闭增加间距。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否在首行和尾行增加间距。1表示增加间距，0表示不增加间距。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 23
     *
     */
    NODE_TEXT_INCLUDE_FONT_PADDING = 1049,

    /**
     * @brief 针对多行文字叠加，支持行高基于文字实际高度自适应。此接口仅当行高小于文字实际高度时生效。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：支持行高基于文字实际高度自适应。\n
     * 1表示开启自适应，0表示关闭自适应。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启行高基于文字实际高度自适应。1表示开启自适应，0表示关闭自适应。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 23
     *
     */
    NODE_TEXT_FALLBACK_LINE_SPACING = 1050,

    /**
     * @brief 文本跑马灯模式配置项，支持属性设置、属性重置和属性获取接口。适用于长文本滚动显示场景，如通知提醒、标题滚动显示等。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：文本跑马灯模式配置，参数类型为{@link ArkUI_TextMarqueeOptions}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：文本跑马灯模式配置，参数类型为{@link ArkUI_TextMarqueeOptions}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 23
     *
     */
    NODE_TEXT_MARQUEE_OPTIONS = 1051,

    /**
     * @brief 文本排版方向。适用于支持不同语言的排版需求，如阿拉伯语、希伯来语等从右向左（RTL）的语言显示。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本的排版方向，取{@link ArkUI_TextDirection}枚举值。默认值为ARKUI_TEXT_DIRECTION_DEFAULT，表示文本排版方向遵循组件布局。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本的排版方向，对应取值及含义请参考{@link ArkUI_TextDirection}枚举值。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 23
     *
     */
    NODE_TEXT_DIRECTION = 1052,

    /**
     * @brief Used to set the selected drag preview style.
     * 
     * Format of the {@link Arkui_AttributeItem} parameter for setting the attribute:\n
     * .object: selected drag preview style configuration.\n
     * The parameter type is {@link Arkui_SelectedDragPreviewStyle}.\n
     * \n
     * Format of the return value {@link Arkui_AttributeItem}:\n
     * .object: selected drag preview style configuration.\n
     * The parameter type is {@link Arkui_SelectedDragPreviewStyle}.\n
     * 
     * @since 23
     */
    NODE_TEXT_SELECTED_DRAG_PREVIEW_STYLE = 1053,

    /**
     * @brief 设置文本的控制器。适用于管理文本编辑行为，如控制文本显示、管理格式化字符串等。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：文本的控制器，参数类型为{@link OH_ArkUI_TextController}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 26.0.0
     */
    NODE_TEXT_CONTROLLER = 1054,

    /**
     * @brief 文本内容属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string 表示span的文本内容。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string 表示span的文本内容。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_SPAN_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SPAN,
    /**
     * @brief 文本背景色属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：表示文本背景颜色，0xargb格式，形如0xFFFF0000表示红色。</li>
     * <li>.value[1].f32：文本背景圆角半径，单位为vp。取值范围：[0, +∞)。传入负数时参数不生效。支持两种设置方式： \n
     * 1）仅设置.value[1].f32，未设置.value[2].f32~.value[4].f32时，表示四个方向的圆角半径统一设置； \n
     * 2）设置了.value[2].f32~.value[4].f32中任意项时，.value[1].f32仅表示左上角圆角半径。</li>
     * <li>.value[2].f32：设置右上角圆角半径，单位为vp。取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * <li>.value[3].f32：设置左下角圆角半径，单位为vp。取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * <li>.value[4].f32：设置右下角圆角半径，单位为vp。取值范围：[0, +∞)。传入负数时参数不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：文本背景颜色，0xargb格式。</li>
     * <li>.value[1].f32：左上角圆角半径，单位为vp。</li>
     * <li>.value[2].f32：右上角圆角半径，单位为vp。</li>
     * <li>.value[3].f32：左下角圆角半径，单位为vp。</li>
     * <li>.value[4].f32：右下角圆角半径，单位为vp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_SPAN_TEXT_BACKGROUND_STYLE,
    /**
     * @brief 文本基线的偏移量属性，支持属性设置、属性重置和属性获取接口。适用于调整Span文本的基线位置，如显示上下标、或实现特殊排版效果。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：偏移量数值，单位为fp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：偏移量数值，单位为fp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_SPAN_BASELINE_OFFSET,
    /**
     * @brief 定义文本样式属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string?：字体列表，多个字体使用`,`进行分割。可选。</li>
     * <li>.value[0].f32：文本尺寸，单位为fp。取值范围：[0, +∞)。</li>
     * <li>.value[1]?.i32：文本的字体粗细。可选。取值为`[100, 900]`，默认为`400`。取值越大，字体越粗。</li>
     * <li>.value[2]?.i32：字体样式。可选。参数类型为{@link ArkUI_FontStyle}。默认值为`ARKUI_FONT_STYLE_NORMAL`。</li>
     * <li>.object?：字体配置。可选，不设置时使用系统默认配置。参数类型为{@link OH_ArkUI_FontConfigs}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：字体列表，多个字体使用`,`进行分割。</li>
     * <li>.value[0].f32：文本尺寸，单位为fp。取值范围：[0, +∞)。</li>
     * <li>.value[1].i32：文本的字体粗细，无单位。取值越大，字体越粗。</li>
     * <li>.value[2].i32：字体样式。参数类型为{@link ArkUI_FontStyle}。</li>
     * <li>.object：字体配置。参数类型为{@link OH_ArkUI_FontConfigs}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 24
     *
     */
    NODE_SPAN_FONT = 2003,

    /**
     * @brief 定义文本字体粗细属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本的字体粗细。取值为`[100, 900]`，默认为`400`。取值越大，字体越粗。超出范围时按默认值400处理。</li>
     * <li>.object?：可选，文本字体粗细配置，不设置时使用默认字体粗细配置。参数类型为{@link OH_ArkUI_FontWeightConfigs}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本字体粗细，无单位。取值越大，字体越粗。</li>
     * <li>.object：文本字体粗细配置。参数类型为{@link OH_ArkUI_FontWeightConfigs}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 24
     *
     */
    NODE_SPAN_FONT_WEIGHT = 2004,
    /**
     * @brief imageSpan组件图片地址属性，支持属性设置、属性重置和属性获取接口。
>>>>>>> 4256a9f0 (8分文档回刷)
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：表示imageSpan的图片地址。</li>
     * <li>.object：表示 PixelMap 图片数据，参数类型为{@link ArkUI_DrawableDescriptor}。\n
     * .object参数和.string参数二选一，不可同时设置。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：表示imageSpan的图片地址。</li>
     * <li>.object：表示 PixelMap 图片数据，参数类型为{@link ArkUI_DrawableDescriptor}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_IMAGE_SPAN_SRC = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE_SPAN,
    /**
     * @brief 图片基于文本的对齐方式属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示图片基于文本的对齐方式，取{@link ArkUI_ImageSpanAlignment}枚举值。默认值为ARKUI_IMAGE_SPAN_ALIGNMENT_BOTTOM，图片下边沿与文本下边沿对齐。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示图片基于文本的对齐方式，取{@link ArkUI_ImageSpanAlignment}枚举值。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_IMAGE_SPAN_VERTICAL_ALIGNMENT,
    /**
     * @brief imageSpan组件占位图地址属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：表示imageSpan组件占位图地址（不支持gif类型图源）。</li>
     * <li>.object：表示 PixelMap 图片数据，参数类型为{@link ArkUI_DrawableDescriptor}；\n
     * .object参数和.string参数二选一，不可同时设置。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：表示imageSpan组件占位图地址。</li>
     * <li>.object：表示 PixelMap 图片数据，参数类型为{@link ArkUI_DrawableDescriptor}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_IMAGE_SPAN_ALT,
    /**
     * @brief imageSpan组件的基线偏移量属性，支持属性设置、属性重置和属性获取接口。偏移量数值为正数时向上偏移，负数时向下偏移，默认值0，单位为fp。 \n
     * 适用于图文混排时调整图片与文本的相对位置，实现精确的排版对齐效果。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：偏移量数值，单位为fp。取值范围：(-∞, +∞)。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：偏移量数值，单位为fp。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 13
     *
     */
    NODE_IMAGE_SPAN_BASELINE_OFFSET = 3003,

    /**
     * @brief 图片滤镜效果属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 ~ .value[19].f32：表示5x4颜色滤镜矩阵数组，共20个浮点数元素，按行优先顺序排列。矩阵前4列分别对应红（R）、绿（G）、蓝（B）、透明度（A）通道的颜色变换系数，第5列为各通道的偏移量。用于对图片进行颜色变换处理，如亮度、对比度、色调调整等。</li>
     * <li>.size：表示滤镜数组大小为5x4。</li>
     * <li>.object：颜色滤波器指针，参数类型为{@link OH_Drawing_ColorFilter}。\n
     * .object和.size参数只能二选一，不可同时设置。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 ~ .value[19].f32：表示滤镜矩阵数组。</li>
     * <li>.size：表示滤镜数组大小为5x4。</li>
     * <li>.object：颜色滤波器指针，参数类型为{@link OH_Drawing_ColorFilter}。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 22
     *
     */
    NODE_IMAGE_SPAN_COLOR_FILTER = 3004,
    /**
     * @brief 通过启用SVG新解析能力开关设置SVG解析功能支持的范围，支持属性设置、属性重置和属性获取接口。ImageSpan组件创建后，不支持动态修改该属性的值。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用SVG新解析能力开关。1表示支持SVG解析新能力；0表示保持原有SVG解析能力。\n
     * 默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用SVG新解析能力开关。1表示支持SVG解析新能力，0表示保持原有SVG解析能力。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 22
     *
     */
    NODE_IMAGE_SPAN_SUPPORT_SVG2 = 3005,
    /**
     * @brief Defines the image source of the <Image> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: image source.\n
     * .object: The parameter type is {@link ArkUI_DrawableDescriptor}. Either .string or .object must be set.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: image source.\n
     * .object: The parameter type is {@link ArkUI_DrawableDescriptor}.\n
     *
     */
    NODE_IMAGE_SRC = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE,
    /**
     * @brief Defines how the image is resized to fit its container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: how the image is resized to fit its container. The value is an enum of {@link ArkUI_ObjectFit}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: how the image is resized to fit its container. The value is an enum of {@link ArkUI_ObjectFit}. \n
     *
     */
    NODE_IMAGE_OBJECT_FIT,
    /**
     * @brief Defines the interpolation effect of the image.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: interpolation effect of the image. The value is an enum of {@link ArkUI_ImageInterpolation}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: interpolation effect of the image. The value is an enum of {@link ArkUI_ImageInterpolation}. \n
     *
     */
    NODE_IMAGE_INTERPOLATION,
    /**
     * @brief Defines how the image is repeated.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: how the image is repeated. The value is an enum of {@link ArkUI_ImageRepeat}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: how the image is repeated. The value is an enum of {@link ArkUI_ImageRepeat}. \n
     *
     */
    NODE_IMAGE_OBJECT_REPEAT,
    /**
     * @brief Defines the color filter of the image.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32 to .value[19].f32: filter matrix array. \n
     * .size: 5 x 4 filter array size. \n
     * .object: the pointer to OH_Drawing_ColorFilter. Either .value or .object is set. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32 to .value[19].f32: filter matrix array. \n
     * .size: 5 x 4 filter array size. \n
     * .object: the pointer to OH_Drawing_ColorFilter. \n
     *
     */
    NODE_IMAGE_COLOR_FILTER,
    /**
     * @brief Defines the auto resize attribute, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32 : whether to resize the image source. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32 : whether to resize the image source. \n
     *
     */
    NODE_IMAGE_AUTO_RESIZE,
    /**
     * @brief Defines the placeholder image source.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: placeholder image source. \n
     * .object: The parameter type is {@link ArkUI_DrawableDescriptor}. Either .string or .object must be set.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: placeholder image source. \n
     * .object: The parameter type is {@link ArkUI_DrawableDescriptor}.\n
     *
     */
    NODE_IMAGE_ALT,
    /**
     * @brief Defines whether the image is draggable.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the image is draggable. The value <b>true</b> means that the image is draggable. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the image is draggable. \n
     *
     */
    NODE_IMAGE_DRAGGABLE,
    /**
     * @brief Defines the image rendering mode. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The parameter type is {@link ArkUI_ImageRenderMode}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The parameter type is {@link ArkUI_ImageRenderMode}. \n
     *
     */
    NODE_IMAGE_RENDER_MODE,
    /**
     * @brief Defines whether the image display size follows the image source size.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: wheter to follow, true means to follow.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: wheter to follow, true means to follow.\n
     *
     */
    NODE_IMAGE_FIT_ORIGINAL_SIZE,
    /**
     * @brief Defines the fill color of the swiper.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: fill color, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: fill color, in 0xARGB format. \n
     *
     */
    NODE_IMAGE_FILL_COLOR,
    /**
     * @brief Resize the image when stretching it with array or a lattice object.
     * The parameter types for setting and getting should be the same.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: width of the left edge. The unit is vp. \n
     * .value[1].f32: width of the top edge. The unit is vp. \n
     * .value[2].f32: width of the right edge. The unit is vp. \n
     * .value[3].f32: width of the bottom edge. The unit is vp. \n
     * .object: The parameter type is {@link OH_Drawing_Lattice},add since api 24.\n
     * 
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: width of the left edge. The unit is vp. \n
     * .value[1].f32: width of the top edge. The unit is vp. \n
     * .value[2].f32: width of the right edge. The unit is vp. \n
     * .value[3].f32: width of the bottom edge. The unit is vp. \n
     * .object: The parameter type is {@link OH_Drawing_Lattice},add since api 24.\n
     *
     */
    NODE_IMAGE_RESIZABLE,
    /**
     * @brief Defines the synchronous image loading attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to load the image synchronously. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to load the image synchronously. \n
     *
     * @since 20
     */
    NODE_IMAGE_SYNC_LOAD = 4012,
    /**
     * @brief Defines the image decoding size attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: width of the image decoding, in px.\n
     * .value[1].i32: height of the image decoding, in px.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: width of the image decoding, in px.\n
     * .value[1].i32: height of the image decoding, in px.\n
     *
     * @since 21
     */
    NODE_IMAGE_SOURCE_SIZE = 4013,
    /**
     * @brief Support the implementation of affine image transformations using floating-point numbers.
     * This attribute can be set, reset, and obtained as required through APIs.
     * The parameter types for setting and getting should be the same.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0...15].f32: 16 floating-point numbers.\n
     * 
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0...15].f32: 16 floating-point numbers.\n
     *
     * @since 21
     */
    NODE_IMAGE_IMAGE_MATRIX = 4014,
    /**
     * @brief Defines the image follow text direction attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to follows the text direction.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to follows the text direction.\n
     *
     * @since 21
     */
    NODE_IMAGE_MATCH_TEXT_DIRECTION = 4015,
    /**
     * @brief Defines the image copy attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: copy option {@link ArkUI_CopyOptions}. The default value is <b>ARKUI_COPY_OPTIONS_NONE</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: copy option {@link ArkUI_CopyOptions.\n
     *
     * @since 21
     */
    NODE_IMAGE_COPY_OPTION = 4016,
    /**
     * @brief Defines the image AI analysis enable attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to enable AI analysis for the image.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to enable AI analysis for the image.\n
     *
     * @since 21
     */
    NODE_IMAGE_ENABLE_ANALYZER = 4017,
    /**
     * @brief Defines the image dynamic display range attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: dynamic range mode {@link ArkUI_DynamicRangeMode}.
     * The default value is <b>ARKUI_DYNAMIC_RANGE_MODE_STANDARD</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: dynamic range mode {@link ArkUI_DynamicRangeMode.\n
     *
     * @since 21
     */
    NODE_IMAGE_DYNAMIC_RANGE_MODE = 4018,
    /**
     * @brief Defines the image dynamic display brightness attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: hdr brightness. value range [0, 1]\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: hdr brightness. value range [0, 1]\n
     *
     * @since 21
     */
    NODE_IMAGE_HDR_BRIGHTNESS = 4019,
    /**
     * @brief Defines the image display direction attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: orientation {@link ArkUI_Orientation}.
     * The default value is <b>ARKUI_ORIENTATION_UP</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: orientation {@link ArkUI_Orientation.\n
     *
     * @since 21
     */
    NODE_IMAGE_ORIENTATION = 4020,
    /**
     * @brief Set the range of SVG parsing capabilities supported through enable switch.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: enable switch.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: enable switch.\n
     *
     * @since 21
     */
    NODE_IMAGE_SUPPORT_SVG2 = 4021, 
    /**
     * @brief Set the animation effect for the image content transformation.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: The parameter type is {@link ArkUI_ContentTransitionEffect}.\n
     * 
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: The parameter type is {@link ArkUI_ContentTransitionEffect}.\n
     *
     * @since 21
     */
    NODE_IMAGE_CONTENT_TRANSITION = 4022,
    /**
     * @brief Defines the placeholder image during loading process.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: placeholder image source. \n
     * .object: The parameter type is {@link ArkUI_DrawableDescriptor}. Either .string or .object must be set.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: placeholder image source. \n
     * .object: The parameter type is {@link ArkUI_DrawableDescriptor}.\n
     *
     * @since 22
     */
    NODE_IMAGE_ALT_PLACEHOLDER = 4023,
    /**
     * @brief Defines the placeholder image when loading fails.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: placeholder image source. \n
     * .object: The parameter type is {@link ArkUI_DrawableDescriptor}. Either .string or .object must be set.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: placeholder image source. \n
     * .object: The parameter type is {@link ArkUI_DrawableDescriptor}.\n
     *
     * @since 22
     */
    NODE_IMAGE_ALT_ERROR = 4024,
    /**
     * @brief Configure image edge anti-aliasing via an enable switch.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: enable switch,the default value is false.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: enable switch.\n
     *
     * @since 23
     */
    NODE_IMAGE_ANTIALIASED = 4025,
    /**
     * @brief Defines the color of the component when it is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: background color, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: background color, in 0xARGB format. \n
     *
     */
    NODE_TOGGLE_SELECTED_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TOGGLE,
    /**
     * @brief Defines the color of the circular slider for the component of the switch type.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color of the circular slider, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the circular slider, in 0xARGB format. \n
     *
     */
    NODE_TOGGLE_SWITCH_POINT_COLOR,
    /**
     * @brief Defines the toggle switch value. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to enable the toggle. The value <b>true</b> means to enable the toggle. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to enable the toggle. \n
     *
     */
    NODE_TOGGLE_VALUE,

    /**
     * @brief Defines the color of the component when it is deselected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     *.value[0].u32: background color, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: background color, in 0xARGB format. \n
     *
     */
    NODE_TOGGLE_UNSELECTED_COLOR,

    /**
     * @brief 加载进度条前景色属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：前景颜色数值，0xargb格式，形如 0xFFFF0000 表示红色。默认值：跟随主题。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：前景颜色数值，0xargb格式。</li>
     * </ul>
     *
     * @ingroup Information Display[信息展示]
     */
    NODE_LOADING_PROGRESS_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LOADING_PROGRESS,
    /**
     * @brief LoadingProgress动画显示属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：1时不显示动画，1时显示动画。默认值为1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：1时不显示动画，1时显示动画。</li>
     * </ul>
     *
     * @ingroup Information Display[信息展示]
     */
    NODE_LOADING_PROGRESS_ENABLE_LOADING,

    /**
     * @brief 单行文本输入框的默认提示文本内容属性，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：默认提示文本的内容。当需要在输入框显示提示信息引导用户输入时设置此属性，例如"请输入用户名"、"请输入密码"等。不设置时输入框无提示文本。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：默认提示文本的内容。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_PLACEHOLDER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,
    /**
     * @brief 单行文本输入框的默认文本内容属性，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：输入框的默认文本内容，用于设置输入框初始显示的文本。当需要在输入框中预置文本时设置此属性，例如表单默认值、编辑初始内容等。不设置时输入框为空。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：默认文本的内容。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_TEXT,
    /**
     * @brief Defines the caret color attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: caret color, in 0xARGB format. For example, 0xFFFF0000 indicates red.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: caret color, in 0xARGB format. \n
     *
     */
    NODE_TEXT_INPUT_CARET_COLOR,
    /**
     * @brief 光标风格属性，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：光标宽度数值，单位为vp。取值范围：[0, +∞)。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：光标宽度数值，单位为vp。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_CARET_STYLE,
    /**
     * @brief 单行文本输入框下划线属性，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示不展示下划线，1表示展示下划线。默认值0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示不展示下划线，1表示展示下划线。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_SHOW_UNDERLINE,
    /**
     * @brief 输入框支持的最大文本数属性，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：最大文本数，无单位。取值范围：[0, +∞)。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：最大文本数，无单位。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_MAX_LENGTH,
    /**
     * @brief 回车键类型属性，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：回车键类型，具体枚举值请参考{@link ArkUI_EnterKeyType}。默认值ARKUI_ENTER_KEY_TYPE_DONE，显示为完成样式。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：回车键类型枚举{@link ArkUI_EnterKeyType}，用于确定输入框回车键的显示样式。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ENTER_KEY_TYPE,
    /**
     * @brief Defines the placeholder text color.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color value, in 0xARGB format. \n
     *
     */
    NODE_TEXT_INPUT_PLACEHOLDER_COLOR,
    /**
     * @brief 无输入时默认提示文本的字体配置（包括大小、字重、样式、字体列表）属性，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0]?.f32：可选字体大小数值，默认值16.0，单位为fp。取值范围：[0, +∞)。传入负数时不生效。</li>
     * <li>.value[1]?.i32：可选字体样式，具体枚举值请参考{@link ArkUI_FontStyle}。默认值为ARKUI_FONT_STYLE_NORMAL，表示标准字体样式。</li>
     * <li>.value[2]?.i32：可选字体粗细样式，具体枚举值请参考{@link ArkUI_FontWeight}。默认值ARKUI_FONT_WEIGHT_NORMAL，表示正常字体粗细。</li>
     * <li>?.string：字体族内容，多个字体族之间使用逗号分隔，形如“字重；字体族1，字体族2”。不传入时使用系统默认字体族。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：字体大小数值，单位为fp。</li>
     * <li>.value[1].i32：字体样式{@link ArkUI_FontStyle}。</li>
     * <li>.value[2].i32：字体粗细样式{@link ArkUI_FontWeight}。</li>
     * <li>.string：字体族内容，多个字体族之间使用逗号分隔。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_PLACEHOLDER_FONT,
    /**
     * @brief 聚焦时是否绑定输入法属性，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示聚焦不拉起输入法，1表示拉起，默认值为1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示聚焦不拉起输入法，1表示拉起。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS,
    /**
     * @brief 输入框的类型属性，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：输入框类型，具体枚举值请参考{@link ArkUI_TextInputType}。默认值为ARKUI_TEXTINPUT_TYPE_NORMAL，表示基本输入模式。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：输入框类型枚举{@link ArkUI_TextInputType}，用于确定输入框的输入内容和键盘样式。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_TYPE,
    /**
     * @brief Defines the background color of the selected text.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color value, in 0xARGB format. \n
     *
     */
    NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR,
    /**
     * @brief 密码输入模式时是否显示末尾图标属性，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示不显示图标，1表示显示图标，默认值为0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示不显示图标，1表示显示图标。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_SHOW_PASSWORD_ICON,
    /**
     * @brief 控制单行文本输入框编辑态属性，支持属性设置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示退出编辑态，1表示维持现状。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示退出编辑态，1表示维持现状。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_EDITING,
    /**
     * @brief 单行文本右侧清除按钮样式属性，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：按钮样式{@link ArkUI_CancelButtonStyle}，默认值为ARKUI_CANCELBUTTON_STYLE_INPUT，表示清除按钮输入样式。</li>
     * <li>.value[1]?.f32：图标大小数值，单位为vp。取值范围：[0, +∞)。传入负数时不生效。不传入时使用系统默认图标大小。</li>
     * <li>.value[2]?.u32：按钮图标颜色数值，0xargb格式，形如 0xFFFF0000 表示红色。不传入时使用系统默认图标颜色。</li>
     * <li>?.string：按钮图标地址，入参内容为图片本地地址，例如 /pages/icon.png。不传入时使用系统默认清除图标。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：按钮样式{@link ArkUI_CancelButtonStyle}。</li>
     * <li>.value[1].f32：图标大小数值，单位为vp。</li>
     * <li>.value[2].u32：按钮图标颜色数值，0xargb格式。</li>
     * <li>.string：按钮图标地址。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_CANCEL_BUTTON,
    /**
     * @brief 组件在获焦状态下，设置文本选中并高亮的区域，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：选中文本的起始位置，取值范围[0, 文本长度]，需小于终止位置才生效。</li>
     * <li>.value[1].i32：选中文本的终止位置，取值范围[0, 文本长度]。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：选中文本的起始位置。</li>
     * <li>.value[1].i32：选中文本的终止位置。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_TEXT_SELECTION,
    /**
     * @brief 开启下划线时，支持配置下划线颜色。
     *
     * 需先设置NODE_TEXT_INPUT_SHOW_UNDERLINE属性为1以开启下划线后，本属性设置才生效。主题配置的默认下划线颜色为0x33182431，表示深灰色，不透明度为20%。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：typing下划线颜色，必填，表示键入时的下划线颜色，0xargb类型。</li>
     * <li>.value[1].u32：normal下划线颜色，必填，表示非特殊状态时下划线颜色，0xargb类型。</li>
     * <li>.value[2].u32：error下划线颜色，必填，表示错误时下划线颜色，0xargb类型。</li>
     * <li>.value[3].u32：disable下划线颜色，必填，表示禁用时下划线颜色，0xargb类型。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：typing下划线颜色，表示键入时的下划线颜色，0xargb类型。</li>
     * <li>.value[1].u32：normal下划线颜色，表示非特殊状态时下划线颜色，0xargb类型。</li>
     * <li>.value[2].u32：error下划线颜色，表示错误时下划线颜色，0xargb类型。</li>
     * <li>.value[3].u32：disable下划线颜色，表示禁用时下划线颜色，0xargb类型。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_UNDERLINE_COLOR,
    /**
     * @brief 设置是否启用自动填充。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用自动填充，默认值1。\n
     * 0表示不启用，1表示启用。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用自动填充。1表示启用，0表示不启用。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ENABLE_AUTO_FILL,
    /**
     * @brief 自动填充类型。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：参数类型{@link ArkUI_TextInputContentType}，用于自动填充场景指定内容类型。具体枚举值及适用场景请参考{@link ArkUI_TextInputContentType}枚举说明。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：自动填充内容类型枚举{@link ArkUI_TextInputContentType}，用于确定自动填充的内容类型。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_CONTENT_TYPE,
    /**
     * @brief 定义生成密码的规则。在触发自动填充时，所设置的密码规则会透传给密码保险箱，用于新密码的生成。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：定义生成密码的规则，用于在触发自动填充时透传给密码保险箱以控制新密码的生成。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：定义生成密码的规则。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_PASSWORD_RULES,
    /**
     * @brief 设置当初始状态，是否全选文本。不支持内联模式。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否全选文本，默认值：0。\n
     * 1表示会全选文本，0表示不会全选文本。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否全选文本。1表示会全选文本，0表示不会全选文本。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_SELECT_ALL,
    /**
     * @brief 通过正则表达式设置输入过滤器。匹配表达式的输入允许显示，不匹配的输入将被过滤。
     * 单字符输入场景仅支持单字符匹配，多字符输入场景支持字符串匹配，例如粘贴。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：正则表达式，用于过滤用户输入内容。匹配表达式的输入允许显示，不匹配的输入将被过滤。当需要限制用户只能输入特定格式的字符时设置此属性，例如"^[a-zA-Z]+$"表示只允许字母，"^[0-9]+$"表示只允许数字。不设置时允许所有字符输入。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：正则表达式。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_INPUT_FILTER,
    /**
     * @brief 设置输入框为默认风格或内联输入风格。内联输入风格是一种无边框的嵌入式输入样式，输入框直接融入页面内容中。
     * 内联输入风格只支持输入框类型的枚举{@link ArkUI_TextInputType}设置为ARKUI_TEXTINPUT_TYPE_NORMAL。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：参数类型{@link ArkUI_TextInputStyle}。内联输入风格只支持输入框类型{@link ArkUI_TextInputType}设置为ARKUI_TEXTINPUT_TYPE_NORMAL。默认值为ARKUI_TEXTINPUT_STYLE_DEFAULT。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：输入框样式枚举{@link ArkUI_TextInputStyle}，用于确定输入框的显示样式。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_STYLE,
    /**
     * @brief 设置或获取光标所在位置信息。设置输入光标的位置。返回当前光标所在位置信息。
     * 在当前帧更新光标位置同时调用该接口，该接口不生效。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：从字符串开始到光标所在位置的字符长度，取值范围[0, 文本长度]。超出范围时自动修正为边界值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：光标所在位置的索引值。</li>
     * <li>.value[1].f32：光标相对输入框的x坐标值，单位为px。</li>
     * <li>.value[2].f32：光标相对输入框的y坐标值，单位为px。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_CARET_OFFSET,
    /**
     * @brief 获取已编辑文本内容区域相对组件的位置和大小。
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：水平方向横坐标，单位为px。</li>
     * <li>.value[1].f32：竖直方向纵坐标，单位为px。</li>
     * <li>.value[2].f32：内容宽度大小，单位为px。</li>
     * <li>.value[3].f32：内容高度大小，单位为px。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_CONTENT_RECT,
    /**
     * @brief Obtains the number of lines of the edited text.
     * 
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: number of lines of the edited text. \n
     *
     */
    NODE_TEXT_INPUT_CONTENT_LINE_COUNT,
    /**
     * @brief 设置长按、双击输入框或者右键输入框时，是否不弹出文本选择菜单，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：长按、双击输入框或者右键输入框时，是否不弹出文本选择菜单。默认值0。\n
     * 设置为1时，单击输入框光标、长按输入框、双击输入框、三击输入框或者右键输入框，隐藏系统文本选择菜单。\n
     * 设置为0时，显示系统文本选择菜单。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：长按、双击输入框或者右键输入框时，是否不弹出文本选择菜单。1表示不弹出菜单，0表示弹出菜单。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_SELECTION_MENU_HIDDEN,
    /**
     * @brief 设置输入框在submit状态下，触发回车键是否失焦。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：触发回车键后是否失焦。默认值1。\n
     * 0表示不失焦，1表示失焦。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：触发回车键后是否失焦。1表示失焦，0表示不失焦。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_BLUR_ON_SUBMIT,
    /**
     * @brief 设置自定义键盘。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：自定义键盘，参数类型{@link ArkUI_NodeHandle}。</li>
     * <li>.value[0]?.i32：设置自定义键盘是否支持避让功能，默认值0。\n
     * 1表示支持避让，0表示不支持避让。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：自定义键盘，参数类型{@link ArkUI_NodeHandle}。</li>
     * <li>.value[0].i32：设置自定义键盘是否支持避让功能。0表示不支持避让，1表示支持避让。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_CUSTOM_KEYBOARD,
    /**
     * @brief 文本断行规则属性，仅在内联输入风格编辑态生效，支持属性设置，属性重置，属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：参数类型{@link ArkUI_WordBreak}。仅在内联输入风格编辑态生效。默认值ARKUI_WORD_BREAK_BREAK_WORD。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本断行规则枚举{@link ArkUI_WordBreak}，用于确定文本的断行方式。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_WORD_BREAK,

    /**
     * @brief 设置输入框获取焦点时是否弹出键盘，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否弹出键盘。默认值1。\n
     * 0表示获取焦点时不弹出键盘，1表示获取焦点时弹出键盘。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否弹出键盘。1表示弹出键盘，0表示不弹出键盘。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_SHOW_KEYBOARD_ON_FOCUS,

    /**
     * @brief 设置该属性后，通过该属性计算TextInput组件的高度。
     * 例如：设置numberOfLines为3时，组件将默认显示足够容纳3行文本内容的高度。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：设置行数，取值范围[1, +∞)，用于通过该属性计算TextInput组件的高度。例如：设置为3时，组件将默认显示足够容纳3行文本内容的高度。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：设置numberOfLines的值。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_NUMBER_OF_LINES,

    /**
     * @brief Sets the letter spacing of the <b>TextInput</b> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: letter spacing. The default unit is fp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: letter spacing. The default unit is fp. \n
     *
     * @since 15
     */
    NODE_TEXT_INPUT_LETTER_SPACING = 7032,

    /**
     * @brief 设置TextInput组件是否开启输入预上屏。
     * 接口支持设置，重置以及获取该属性。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：设置是否开启输入预上屏。默认值1。\n
     * 0表示不开启输入预上屏，1表示开启输入预上屏。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：获取是否开启输入预上屏。0表示不开启输入预上屏，1表示开启输入预上屏。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 15
     *
     */
    NODE_TEXT_INPUT_ENABLE_PREVIEW_TEXT = 7033,

    /**
     * @brief 设置文本将行间距平分至行的顶部与底部。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：设置文本是否将行间距平分至行的顶部与底部。默认值0。\n
     * 1表示将行间距平分至行的顶部与底部，0表示不平分。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本行间距是否平分至行的顶部与底部。1表示平分，0表示不平分。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 18
     *
     */
    NODE_TEXT_INPUT_HALF_LEADING = 7034,

    /**
     * @brief 设置输入框拉起的键盘样式。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：键盘样式，参数类型{@link ArkUI_KeyboardAppearance}。具体枚举值请参考ArkUI_KeyboardAppearance枚举说明。默认值ARKUI_KEYBOARD_APPEARANCE_NONE_IMMERSIVE，不使用沉浸式样式。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：键盘样式，参数类型{@link ArkUI_KeyboardAppearance}。具体枚举值请参考ArkUI_KeyboardAppearance枚举说明。默认值ARKUI_KEYBOARD_APPEARANCE_NONE_IMMERSIVE。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 15
     *
     */
    NODE_TEXT_INPUT_KEYBOARD_APPEARANCE = 7035,

    /**
     * @brief 设置是否启用自动填充动效。仅当输入框类型{@link ArkUI_TextInputType}设置为ARKUI_TEXTINPUT_TYPE_PASSWORD、ARKUI_TEXTINPUT_TYPE_NUMBER_PASSWORD或ARKUI_TEXTINPUT_TYPE_NEW_PASSWORD时，该动效才生效。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用自动填充动效。启用之后，仅输入框类型的枚举{@link ArkUI_TextInputType}设置为ARKUI_TEXTINPUT_TYPE_PASSWORD、ARKUI_TEXTINPUT_TYPE_NUMBER_PASSWORD或ARKUI_TEXTINPUT_TYPE_NEW_PASSWORD的输入框在进行自动填充时动效可生效。1表示启用，0表示不启用。默认值1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用自动填充动效。0表示不启用，1表示启用。启用之后，仅输入框类型的枚举{@link ArkUI_TextInputType}设置为ARKUI_TEXTINPUT_TYPE_PASSWORD、ARKUI_TEXTINPUT_TYPE_NUMBER_PASSWORD或ARKUI_TEXTINPUT_TYPE_NEW_PASSWORD的输入框在进行自动填充时动效可生效。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 20
     *
     */
    NODE_TEXT_INPUT_ENABLE_FILL_ANIMATION = 7036,

    /**
     * @brief 设置输入框文本的高度，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本的高度，单位fp。默认值是自适应字体大小。不传入该参数时，文本的高度设置为5fp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本的高度，单位fp。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 20
     *
     */
    NODE_TEXT_INPUT_LINE_HEIGHT = 7037,

    /**
     * @brief Enables selected data detector.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: Enable selected text recognition, default value true.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: Whether selected text recognition is enabled.\n
     *
     * @since 22
     */
    NODE_TEXT_INPUT_ENABLE_SELECTED_DATA_DETECTOR = 7038,

    /**
     * @brief 设置输入的字符数超过阈值时是否显示计数器并设置计数器样式，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启计数器。值为1表示开启计数器，值为0表示不开启计数器。</li>
     * <li>.value[1]?.f32：可输入字符数占最大字符限制的百分比值，超过此值时显示计数器，取值范围[1, 100]，小数时向下取整，若超出取值范围，则接口属性设置不生效。默认值-1，即始终显示计数器。</li>
     * <li>.value[2]?.i32：输入字符超出限制时高亮边框，1表示高亮边框，0表示不高亮边框。默认值1。</li>
     * <li>.object：计数器配置，配置属性为文本输入框未达到最大字符数时计数器的颜色以及超出最大字符数时计数器的颜色。参数类型为 {@link ArkUI_ShowCounterConfig}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启计数器。0表示不开启计数器，1表示开启计数器。</li>
     * <li>.value[1].f32：可输入字符数占最大字符限制的百分比值，超过此值时显示计数器，取值范围[1, 100]。</li>
     * <li>.value[2].i32：输入字符超出限制时高亮边框。0表示不高亮边框，1表示高亮边框。</li>
     * <li>.object：计数器配置，配置属性为文本输入框未达到最大字符数时计数器的颜色以及超出最大字符数时计数器的颜色。参数类型为 {@link ArkUI_ShowCounterConfig}。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 22
     *
     */
    NODE_TEXT_INPUT_SHOW_COUNTER = 7040,

    /**
     * @brief Used to set or get the text content base controller.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n 
     * .object: the text content base controller. The parameter type is {@link ArkUI_TextContentBaseController}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: the text content base controller. The parameter type is {@link ArkUI_TextContentBaseController}.\n
     * 
     * @since 23
     */
    NODE_TEXT_INPUT_TEXT_CONTENT_CONTROLLER_BASE = 7041,

    /**
     * @brief Defines the ellipsis position.
     * This attribute can be set, reset, and obtained as required through APIs.
     * 
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The parameter type is {@link ArkUI_EllipsisMode}, the default value
     * is ARKUI_ELLIPSIS_MODE_END. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The parameter type is {@link ArkUI_EllipsisMode}. \n
     *
     * @since 24
     */
    NODE_TEXT_INPUT_ELLIPSIS_MODE = 7042,

    /**
     * @brief 设置TextInput文本排版时是否使能孤字优化。使能后通过更高效地处理孤立字符（段落尾行首字符）来改善文本布局，调整换行点以尽可能避免孤立字符。
     * 注意：该特性需在{@link ArkUI_WordBreak}属性为非ARKUI_WORD_BREAK_BREAK_ALL时生效。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否使能孤字优化。该特性需在{@link ArkUI_WordBreak}属性为非ARKUI_WORD_BREAK_BREAK_ALL时生效。1表示使能，0表示不使能。默认值0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否使能孤字优化。0表示不使能，1表示使能。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     *
     */
 	  NODE_TEXT_INPUT_ORPHAN_CHAR_OPTIMIZATION = 7043,

    /**
     * @brief 设置输入字符行首标点压缩开关，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否打开行首标点压缩开关。1表示开启行首标点压缩，0表示关闭行首标点压缩。默认值0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否打开行首标点压缩开关。0表示关闭行首标点压缩，1表示开启行首标点压缩。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 23
     *
     */
    NODE_TEXT_INPUT_COMPRESS_LEADING_PUNCTUATION = 7044,

    /**
     * @brief 设置单行输入框内文字是否在首行顶部和尾行底部增加间距以避免文字截断。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：设置输入框内文字是否在首行顶部和尾行底部增加间距以避免文字截断。1表示开启增加间距，0表示关闭增加间距。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否在首行顶部和尾行底部增加间距。0表示不增加间距，1表示增加间距。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 23
     *
     */
    NODE_TEXT_INPUT_INCLUDE_FONT_PADDING = 7045,

    /**
     * @brief 针对多行文本显示场景，支持行高基于文字实际高度自适应。此接口仅当行高小于文字实际高度时生效。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：支持行高基于文字实际高度自适应。此接口仅当行高小于文字实际高度时生效。1表示开启自适应，0表示关闭自适应。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启行高基于文字实际高度自适应。0表示关闭自适应，1表示开启自适应。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 23
     *
     */
    NODE_TEXT_INPUT_FALLBACK_LINE_SPACING = 7046,

    /**
     * @brief Writing direction of the text.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: writing direction of the text. The value is an enum of {@link ArkUI_TextDirection}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: writing direction the text. The value is an enum of {@link ArkUI_TextDirection}. \n
     *
     * @since 23
     */
    NODE_TEXT_INPUT_DIRECTION = 7047,

    /**
     * @brief 用于设置文本输入框内文本选中状态下的拖拽预览样式。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：文本选中状态下的拖拽预览样式。参数类型为{@link ArkUI_SelectedDragPreviewStyle}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：文本选中状态下的拖拽预览样式。参数类型为{@link ArkUI_SelectedDragPreviewStyle}。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 23
     */
    NODE_TEXT_INPUT_SELECTED_DRAG_PREVIEW_STYLE = 7048,

    /**
     * @brief Defines the textinput textOverflow attribute.
     * which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: display mode when the text is too long {@link ArkUI_TextOverflow}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: display mode when the text is too long {@link ArkUI_TextOverflow}. \n
     *
     * @since 24  
     */
    NODE_TEXT_INPUT_TEXT_OVERFLOW = 7049,

    /**
     * @brief 定义单行输入框的文本装饰线样式与颜色，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：装饰样式配置项，为可选参数。参数类型为{@link OH_ArkUI_DecorationStyleOptions}。不传入时不添加装饰线。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：装饰样式配置项。参数类型为{@link OH_ArkUI_DecorationStyleOptions}。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     *
     */
    NODE_TEXT_INPUT_DECORATION = 7050,

    /**
     * @brief 设置文本输入框内文本线性渐变效果，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：线性渐变的起始角度，单位为deg。当线性渐变的方向为{@link ArkUI_LinearGradientDirection}的ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM时，线性渐变的起始角度属性生效，否则按线性渐变的方向属性为主要布局方式。取值范围为(-∞,+∞)，0点方向顺时针旋转为正向角度，当超过360时，是按照360取余处理，默认值：180。</li>
     * <li>.value[1].i32：线性渐变的方向，取值为{@link ArkUI_LinearGradientDirection}枚举。设置除ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM之外的方向后，起始角度不生效。默认值：ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_BOTTOM。</li>
     * <li>.value[2].i32：渐变的颜色是否重复着色，0表示不重复着色，1表示重复着色。默认值：0。</li>
     * <li>.object：指定位置处的渐变色颜色，参数类型为{@link ArkUI_ColorStop}。
     * - colors：渐变色颜色数组，元素为0xargb格式，形如0xFFFF0000表示红色。
     * - stops：指定颜色所处位置的数组，取值范围[0,1.0]，0表示容器开始处，1.0表示结尾处。建议递增设置。
     * - size：颜色个数，若小于colors数组长度则仅生效前size个颜色。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：线性渐变的起始角度，单位为deg。当线性渐变的方向为{@link ArkUI_LinearGradientDirection}的ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM时，线性渐变的起始角度为设置值，其他情况均为默认值0。</li>
     * <li>.value[1].i32：线性渐变的方向。对应取值及含义请参考{@link ArkUI_LinearGradientDirection}。</li>
     * <li>.value[2].i32：渐变的颜色是否重复着色，0表示不重复着色，1表示重复着色。默认值：0。</li>
     * <li>.object：指定位置处的渐变色颜色。参数类型为{@link ArkUI_ColorStop}。
     *  colors：渐变色颜色数组，数组元素为0xargb格式，形如0xFFFF0000表示红色。
     *  stops：stops表示指定颜色所处位置的数组，数组元素取值范围为[0,1.0]，0表示需要设置渐变色的容器的开始处，1.0表示容器的结尾处。
     *  size：生效后渐变色的颜色个数。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     *
     */
    NODE_TEXT_INPUT_LINEAR_GRADIENT = 7051,

    /**
     * @brief 设置文本输入框的文本径向渐变效果，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0]?.f32：径向渐变的中心点X轴坐标，即相对于当前文本输入框左上角的X轴坐标，单位为vp。默认值为文本输入框宽度的一半。</li>
     * <li>.value[1]?.f32：径向渐变的中心点Y轴坐标，即相对于当前文本输入框左上角的Y轴坐标，单位为vp。默认值为文本输入框高度的一半。</li>
     * <li>.value[2]?.f32：径向渐变的半径，单位为vp。取值范围[0, +∞)，默认值0。传入负数时不生效。</li>
     * <li>.value[3]?.i32：渐变的颜色是否重复着色，0表示不重复着色，1表示重复着色。默认值：0。</li>
     * <li>.object：指定位置处的渐变色颜色。参数类型为{@link ArkUI_ColorStop}。
     *  colors：渐变色数组，元素为0xargb格式，形如0xFFFF0000表示红色。
     *  stops：指定颜色所处位置的数组，取值范围[0,1.0]，0表示容器开始处，1.0表示结尾处。建议递增设置，若后一元素小于前一元素，则按等于前一元素的值处理。
     *  size：颜色个数，若小于colors数组长度则仅生效前size个颜色，不建议设置异常值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0]?.f32：径向渐变的中心点X轴坐标，即相对于当前文本输入框左上角的X轴坐标，单位为vp。</li>
     * <li>.value[1]?.f32：径向渐变的中心点Y轴坐标，即相对于当前文本输入框左上角的Y轴坐标，单位为vp。</li>
     * <li>.value[2]?.f32：径向渐变的半径，单位为vp，默认值0。</li>
     * <li>.value[3]?.i32：渐变的颜色是否重复着色，0表示不重复着色，1表示重复着色。默认值：0。</li>
     * <li>.object：指定位置处的渐变色颜色。参数类型为{@link ArkUI_ColorStop}。
     *  colors：渐变色颜色数组，数组元素为0xargb格式，形如0xFFFF0000表示红色。
     *  stops：stops表示指定颜色所处位置的数组，数组元素取值范围为[0,1.0]，0表示需要设置渐变色的容器的开始处，1.0表示容器的结尾处。
     *  size：生效后渐变色的颜色个数。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     *
     */
    NODE_TEXT_INPUT_RADIAL_GRADIENT = 7052,

    /**
     * @brief Defines the default placeholder text for the multi-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: default placeholder text. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: default placeholder text. \n
     *
     */
    NODE_TEXT_AREA_PLACEHOLDER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_AREA,
    /**
     * @brief Defines the default text content for the multi-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: default text content. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: default text content. \n
     *
     */
    NODE_TEXT_AREA_TEXT,
    /**
     * @brief Defines the maximum number of characters in the text input.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: maximum number of characters in the text input. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: maximum number of characters in the text input. \n
     *
     */
    NODE_TEXT_AREA_MAX_LENGTH,
    /**
     * @brief Defines the placeholder text color.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color value, in 0xARGB format. \n
     *
     */
    NODE_TEXT_AREA_PLACEHOLDER_COLOR,
    /**
     * @brief Defines the placeholder text font.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.f32: font size, in fp. Optional. The default value is <b>16.0</b>.\n
     * .value[1]?.i32: font style {@link ArkUI_FontStyle}. Optional. The default value is <b>ARKUI_FONT_STYLE_NORMAL</b>.\n
     * .value[2]?.i32: font weight {@link ArkUI_FontWeight}. Optional. The default value is <b>ARKUI_FONT_WEIGHT_NORMAL</b>.\n
     * ?.string: font family. Multiple font families are separated by commas (,). For example, "font weight; font family 1, font family 2". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: font size, in fp.\n
     * .value[1].i32: font style {@link ArkUI_FontStyle}.\n
     * .value[2].i32: font weight {@link ArkUI_FontWeight}.\n
     * .string: font family. Multiple font families are separated by commas (,). \n
     *
     */
    NODE_TEXT_AREA_PLACEHOLDER_FONT,
    /**
     * @brief Defines the caret color attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: background color, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: background color, in 0xARGB format. \n
     *
     */
    NODE_TEXT_AREA_CARET_COLOR,
    /**
     * @brief 控制多行文本输入框编辑态属性，支持属性设置，属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示退出编辑态，1表示维持现状。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示退出编辑态，1表示维持现状。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_EDITING,
    /**
     * @brief Defines the text box type. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: text box type {@link ArkUI_TextAreaType}.
     * The default value is <b>ARKUI_TEXTAREA_TYPE_NORMAL</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: text box type {@link ArkUI_TextAreaType}. \n
     *
     */
    NODE_TEXT_AREA_TYPE,
    /**
     * @brief 设置输入的字符数超过阈值时是否显示计数器并设置计数器样式，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启计数器。值为1时为开启。默认值0。</li>
     * <li>.value[1]?.f32：可输入字符数占最大字符限制的百分比值，超过此值时显示计数器，取值范围[1, 100]，小数时向下取整，若超出取值范围，则接口属性设置不生效。默认值-1，即始终显示计数器。</li>
     * <li>.value[2]?.i32：输入字符超出限制时是否高亮边框。1表示高亮边框，0表示不高亮边框。默认值1。</li>
     * <li>.object：计数器配置，配置属性为文本输入框未达到最大字符数时计数器的颜色以及超出最大字符数时计数器的颜色。参数类型为 {@link ArkUI_ShowCounterConfig}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启计数器。0表示不开启计数器，1表示开启计数器。</li>
     * <li>.value[1].f32：可输入字符数占最大字符限制的百分比值，超过此值时显示计数器，取值范围[1, 100]。</li>
     * <li>.value[2].i32：输入字符超出限制时是否高亮边框。0表示不高亮边框，1表示高亮边框。</li>
     * <li>.object：计数器配置，配置属性为文本输入框未达到最大字符数时计数器的颜色以及超出最大字符数时计数器的颜色。参数类型为 {@link ArkUI_ShowCounterConfig}。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_SHOW_COUNTER,
    /**
     * @brief 设置长按、双击输入框或者右键输入框时，是否不弹出文本选择菜单，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：长按、双击输入框或者右键输入框时，是否不弹出文本选择菜单。\n
     * 设置为1时，单击输入框光标、长按输入框、双击输入框、三击输入框或者右键输入框，隐藏系统文本选择菜单。\n
     * 设置为0时，显示系统文本选择菜单。\n
     * 默认值0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：长按、双击输入框或者右键输入框时，是否不弹出文本选择菜单。0表示显示系统文本选择菜单，1表示隐藏系统文本选择菜单。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_SELECTION_MENU_HIDDEN,
    /**
     * @brief 设置多行输入框在submit状态下，触发回车键是否失焦。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：触发回车键后是否失焦。\n
     * 0表示触发回车键后不失焦，1表示触发回车键后失焦。\n
     * 默认值0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：触发回车键后是否失焦。0表示触发回车键后不失焦，1表示触发回车键后失焦。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_BLUR_ON_SUBMIT,
    /**
     * @brief 通过正则表达式设置输入过滤器。匹配表达式的输入允许显示，不匹配的输入将被过滤。
     * 单字符输入场景仅支持单字符匹配，多字符输入场景支持字符串匹配，例如粘贴。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：正则表达式，用于过滤用户输入内容。匹配表达式的输入允许显示，不匹配的输入将被过滤。当需要限制用户只能输入特定格式的字符时设置此属性，例如"^[a-zA-Z]+$"表示只允许字母，"^[0-9]+$"表示只允许数字。不设置时允许所有字符输入。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：正则表达式。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_INPUT_FILTER,
    /**
     * @brief Defines the background color of the selected text.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color value, in 0xARGB format. For example, 0xFFFF0000 indicates red. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color value, in 0xARGB format. \n
     *
     */
    NODE_TEXT_AREA_SELECTED_BACKGROUND_COLOR,
    /**
     * @brief Defines the type of the Enter key.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: type of the Enter key{@link ArkUI_EnterKeyType}. The default value is <b>ARKUI_ENTER_KEY_TYPE_DONE</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: type of the Enter key{@link ArkUI_EnterKeyType}. \n
     *
     */
    NODE_TEXT_AREA_ENTER_KEY_TYPE,
    /**
     * @brief 设置TextArea通过点击以外的方式获焦时，是否绑定输入法，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示聚焦不拉起输入法，1表示拉起。默认值为1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示聚焦不拉起输入法，1表示拉起。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_ENABLE_KEYBOARD_ON_FOCUS,
    /**
     * @brief 设置或获取光标所在位置信息。设置输入光标的位置。返回当前光标所在位置信息。
     * 在当前帧更新光标位置同时调用该接口，该接口不生效。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：从字符串开始到光标所在位置的字符长度，取值范围[0, 文本长度]。超出范围时自动修正为边界值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：光标所在位置的索引值。</li>
     * <li>.value[1].f32：光标相对输入框的x坐标位值，单位为px。</li>
     * <li>.value[2].f32：光标相对输入框的y坐标位值，单位为px。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_CARET_OFFSET,
    /**
     * @brief 获取已编辑文本内容区域相对组件的位置和大小。
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：水平方向横坐标，单位为px。</li>
     * <li>.value[1].f32：竖直方向纵坐标，单位为px。</li>
     * <li>.value[2].f32：内容宽度大小，单位为px。</li>
     * <li>.value[3].f32：内容高度大小，单位为px。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_CONTENT_RECT,
    /**
     * @brief Obtains the number of lines of the edited text.
     * 
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: number of lines of the edited text. \n
     *
     */
    NODE_TEXT_AREA_CONTENT_LINE_COUNT,
    /**
     * @brief 组件在获焦状态下，调用该接口设置文本选择区域并高亮显示，且只有在selectionStart小于selectionEnd时，文字才会被选取、高亮显示。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：选中文本的起始位置，取值范围[0, 文本长度]，需小于终止位置才生效。</li>
     * <li>.value[1].i32：选中文本的终止位置，取值范围[0, 文本长度]。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：选中文本的起始位置。</li>
     * <li>.value[1].i32：选中文本的终止位置。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_TEXT_SELECTION,
    /**
     * @brief 设置是否启用自动填充。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用自动填充。\n
     * 1表示启用，0表示不启用。\n
     * 默认值1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用自动填充。1表示已启用，0表示未启用。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_ENABLE_AUTO_FILL,
    /**
     * @brief 自动填充类型。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：参数类型{@link ArkUI_TextInputContentType}。用于指定自动填充的内容类型，以便系统提供更准确的自动填充建议。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：参数类型{@link ArkUI_TextInputContentType}。用于指定自动填充的内容类型，以便系统提供更准确的自动填充建议。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_CONTENT_TYPE,

    /**
     * @brief 设置输入框获取焦点时是否弹出键盘，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：获取焦点时是否弹出键盘。\n
     * 1表示弹出键盘，0表示不弹出键盘。\n
     * 默认值1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：获取焦点时是否弹出键盘。1表示弹出键盘，0表示不弹出键盘。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_SHOW_KEYBOARD_ON_FOCUS,

    /**
     * @brief 设置该属性后，通过该属性计算TextArea组件的高度。
     * 例如：设置numberOfLines为3时，组件将默认显示足够容纳3行文本内容的高度。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：设置行数，取值范围[1, +∞)。用于通过该属性计算TextArea组件的高度。例如：设置为3时，组件将默认显示足够容纳3行文本内容的高度。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：设置numberOfLines的值。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_NUMBER_OF_LINES,

    /**
     * @brief Sets the letter spacing of the <b>TextArea</b> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: letter spacing. The default unit is fp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: letter spacing. The default unit is fp. \n
     *
     * @since 15
     */
    NODE_TEXT_AREA_LETTER_SPACING = 8023,
    /**
     * @brief 设置TextArea组件是否开启输入预上屏。
     * 接口支持设置，重置以及获取该属性。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：设置是否开启输入预上屏。\n
     * 0表示不开启输入预上屏，1表示开启输入预上屏。\n
     * 默认值1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启输入预上屏。1表示已开启，0表示未开启。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 15
     *
     */
    NODE_TEXT_AREA_ENABLE_PREVIEW_TEXT = 8024,

    /**
     * @brief 设置文本是否将行间距平分至行的顶部与底部。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：设置文本是否将行间距平分至行的顶部与底部。\n
     * 1表示将行间距平分至行的顶部与底部，0表示不平分。\n
     * 默认值0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本行间距是否平分至行的顶部与底部。1表示平分，0表示不平分。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 18
     *
     */
    NODE_TEXT_AREA_HALF_LEADING = 8025,

    /**
     * @brief Set the keyboard style of textArea
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32：keyboard style，the parameter type is {@link ArkUI_KeyboardAppearanceType}。\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}：\n
     * .value[0].i32：keyboard style，the parameter type is {@link ArkUI_KeyboardAppearanceType}。\n
     *
     * @since 15
     */
    NODE_TEXT_AREA_KEYBOARD_APPEARANCE = 8026,

    /**
     * @brief 设置输入框内联模式编辑态时文本可显示的最大行数，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：内联输入风格编辑态时文本可显示的最大行数。取值范围[1, +∞)。\n
     * 内联模式下，默认值是3，非内联模式下，默认值是+∞，不限制最大行数。\n
     * 不传入该参数时，使用默认值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：最大行数。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 20
     *
     */
    NODE_TEXT_AREA_MAX_LINES = 8027,

    /**
     * @brief 设置输入框文本的行间距，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本的行间距，取值范围[0, +∞)，单位为fp。默认值是0。超出范围时自动修正为边界值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本的行间距，单位fp。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 20
     *
     */
    NODE_TEXT_AREA_LINE_SPACING = 8028,

    /**
     * @brief 设置节点的最小行数。支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：最小行数，取值范围[1, +∞)。传入0或负数时参数不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：最小行数，取值范围[1, +∞)。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 20
     *
     */
    NODE_TEXT_AREA_MIN_LINES = 8029,
 
    /**
     * @brief 设置支持滚动时节点的最大行数。支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：支持滚动时的最大行数。取值范围[1, +∞)。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：支持滚动时的最大行数。取值范围[1, +∞)。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 20
     *
     */
    NODE_TEXT_AREA_MAX_LINES_WITH_SCROLL = 8030,

    /**
     * @brief 设置输入框文本的高度，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本的高度。默认值是自适应字体大小，单位fp。不传入该参数时，文本的高度设置为5fp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本的高度，单位fp。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 20
     *
     */
    NODE_TEXT_AREA_LINE_HEIGHT = 8031,

    /**
     * @brief Define bar state of the text area.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: bar state of the text area, specified using the {@link ArkUI_BarState} enum.
     * The default value is <b>ARKUI_BAR_STATE_AUTO</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: bar state of the text area, specified using the {@link ArkUI_BarState} enum. \n
     *
     * @since 22
     */
     NODE_TEXT_AREA_BAR_STATE = 8032,

    /**
     * @brief Enables selected data detector.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: Enable selected text recognition, default value true.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: Whether selected text recognition is enabled.\n
     *
     * @since 22
     */
    NODE_TEXT_AREA_ENABLE_SELECTED_DATA_DETECTOR = 8033,

    /**
     * @brief Defines the color of the scrollbar. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .data[0].u32: color of the scroll bar thumb, in 0xARGB format. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .data[0].u32: color of the scroll bar thumb, in 0xARGB format. \n
     *
     * @since 22
     */
     NODE_TEXT_AREA_SCROLL_BAR_COLOR = 8035,

    /**
     * @brief 设置文本输入框的自定义键盘。支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：自定义键盘，参数类型{@link ArkUI_NodeHandle}。</li>
     * <li>.value[0]?.i32：设置自定义键盘是否支持避让功能，\n
     * 1表示支持避让，0表示不支持避让。\n
     * 默认值为0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：自定义键盘，参数类型{@link ArkUI_NodeHandle}。</li>
     * <li>.value[0].i32：设置自定义键盘是否支持避让功能。0表示不支持避让，1表示支持避让。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 22
     *
     */
    NODE_TEXT_AREA_CUSTOM_KEYBOARD = 8036,

    /**
     * @brief Used to set or get the text content base controller.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n 
     * .object: the text content base controller. The parameter type is {@link ArkUI_TextContentBaseController}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: the text content base controller. The parameter type is {@link ArkUI_TextContentBaseController}.\n
     *
     * @since 23
     */
    NODE_TEXT_AREA_TEXT_CONTENT_CONTROLLER_BASE = 8037,

    /**
     * @brief Defines the ellipsis position.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The parameter type is {@link ArkUI_EllipsisMode}, the default value
     * is ARKUI_ELLIPSIS_MODE_END. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The parameter type is {@link ArkUI_EllipsisMode}. \n
     *
     * @since 24
     */
    NODE_TEXT_AREA_ELLIPSIS_MODE = 8038,

    /**
     * @brief 设置TextArea文本排版时是否使能孤字优化。使能后通过更高效地处理孤立字符（段落尾行首字符）来改善文本布局，调整换行点以尽可能避免孤立字符。
     * 注意：该特性需在{@link ArkUI_WordBreak}属性为非ARKUI_WORD_BREAK_BREAK_ALL时生效。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否使能孤字优化。该特性需在{@link ArkUI_WordBreak}属性为非ARKUI_WORD_BREAK_BREAK_ALL时生效。1表示使能，0表示不使能。默认值0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否使能孤字优化。0表示不使能，1表示使能。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     *
     */
    NODE_TEXT_AREA_ORPHAN_CHAR_OPTIMIZATION = 8039,

    /**
     * @brief 设置输入字符行首标点压缩开关，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否打开行首标点压缩开关。\n
     * 1表示开启行首标点压缩，0表示关闭行首标点压缩。默认值0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否打开行首标点压缩开关。0表示关闭行首标点压缩，1表示开启行首标点压缩。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 23
     *
     */
    NODE_TEXT_AREA_COMPRESS_LEADING_PUNCTUATION = 8040,

    /**
     * @brief 设置多行输入框内文字是否在首行顶部和尾行底部增加间距以避免文字截断。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：设置输入框内文字是否在首行顶部和尾行底部增加间距以避免文字截断。1表示开启增加间距，0表示关闭增加间距。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否在首行顶部和尾行底部增加间距。0表示不增加间距，1表示增加间距。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 23
     *
     */
    NODE_TEXT_AREA_INCLUDE_FONT_PADDING = 8041,

    /**
     * @brief 针对多行文本显示场景，支持行高基于文字实际高度自适应。此接口仅当行高小于文字实际高度时生效。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：支持行高基于文字实际高度自适应。此接口仅当行高小于文字实际高度时生效。1表示开启自适应，0表示关闭自适应。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启行高基于文字实际高度自适应。0表示关闭自适应，1表示开启自适应。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 23
     *
     */
    NODE_TEXT_AREA_FALLBACK_LINE_SPACING = 8042,

    /**
     * @brief 设置多行输入框在文本宽度超过输入框内容区宽度时是否启用水平滚动。默认值为0，文本会被输入框自动换行。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用水平滚动。1表示启用水平滚动，0表示不启用水平滚动。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用水平滚动。1表示启用水平滚动，0表示不启用水平滚动。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 24
     *
     */
    NODE_TEXT_AREA_HORIZONTAL_SCROLLING = 8043,

    /**
     * @brief Writing direction of the text.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: writing direction of the text. The value is an enum of {@link ArkUI_TextDirection}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: writing direction the text. The value is an enum of {@link ArkUI_TextDirection}. \n
     *
     * @since 23
     */
    NODE_TEXT_AREA_DIRECTION = 8044,

    /**
     * @brief Used to set the selected drag preview style.
     *
     * Format of the {@link Arkui_AttributeItem} parameter for setting the attribute:\n
     * .object: selected drag preview style configuration. 
     * The parameter type is {@link Arkui_SelectedDragPreviewStyle}.\n
     * \n
     * Format of the return value {@link Arkui_AttributeItem}:\n
     * .object: selected drag preview style configuration. 
     * The parameter type is {@link Arkui_SelectedDragPreviewStyle}.\n
     *
     * @since 23
     */
    NODE_TEXT_AREA_SELECTED_DRAG_PREVIEW_STYLE = 8045,

    /**
     * @brief Defines the textarea textOverflow attribute.
     * which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: display mode when the text is too long {@link ArkUI_TextOverflow}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: display mode when the text is too long {@link ArkUI_TextOverflow}. \n
     * 
     * @since 24
     */
    NODE_TEXT_AREA_TEXT_OVERFLOW = 8046,
    /**
     * @brief Defines the text decoration style and color for multi-line text box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * ?.object: Optional. The decoration style options. The parameter type is {@link OH_ArkUI_DecorationStyleOptions}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: The decoration style options. The parameter type is {@link OH_ArkUI_DecorationStyleOptions}.\n
     *
     * @since 26.0.0
     */
    NODE_TEXT_AREA_DECORATION = 8047,

    /**
     * @brief 设置多行文本输入框的文本线性渐变效果，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：线性渐变的起始角度，单位为deg。当线性渐变的方向为{@link ArkUI_LinearGradientDirection}的ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM时，线性渐变的起始角度属性生效，否则按线性渐变的方向属性为主要布局方式。取值范围为(-∞,+∞)，0点方向顺时针旋转为正向角度，当超过360时，是按照360取余处理，默认值：180。</li>
     * <li>.value[1].i32：线性渐变的方向，取值为{@link ArkUI_LinearGradientDirection}枚举。设置除ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM之外的方向后，起始角度不生效。默认值：ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_BOTTOM。</li>
     * <li>.value[2].i32：渐变的颜色是否重复着色，0表示不重复着色，1表示重复着色。默认值：0。</li>
     * <li>.object：指定位置处的渐变色颜色，参数类型为{@link ArkUI_ColorStop}。\n
     * - colors：渐变色颜色数组，元素为0xargb格式，形如0xFFFF0000表示红色。\n
     * - stops：指定颜色所处位置的数组，取值范围[0,1.0]，0表示容器开始处，1.0表示结尾处。建议递增设置。\n
     * - size：颜色个数，若小于colors数组长度则仅生效前size个颜色。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：线性渐变的起始角度，单位为deg。当线性渐变的方向为{@link ArkUI_LinearGradientDirection}的ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM时，线性渐变的起始角度为设置值，其他情况均为默认值0。</li>
     * <li>.value[1].i32：线性渐变的方向。对应取值及含义请参考{@link ArkUI_LinearGradientDirection}。</li>
     * <li>.value[2].i32：渐变的颜色是否重复着色，0表示不重复着色，1表示重复着色。默认值：0。</li>
     * <li>.object：指定位置处的渐变色颜色。参数类型为{@link ArkUI_ColorStop}。\n
     *  colors：渐变色颜色数组，数组元素为0xargb格式，形如0xFFFF0000表示红色。\n
     *  stops：stops表示指定颜色所处位置的数组，数组元素取值范围为[0,1.0]，0表示需要设置渐变色的容器的开始处，1.0表示容器的结尾处。\n
     *  size：生效后渐变色的颜色个数。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     *
     */
    NODE_TEXT_AREA_LINEAR_GRADIENT = 8048,

    /**
     * @brief 设置多行文本输入框的文本径向渐变效果，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0]?.f32：径向渐变的中心点X轴坐标，即相对于当前多行文本输入框左上角的X轴坐标，单位为vp。默认值为多行文本输入框宽度的一半。</li>
     * <li>.value[1]?.f32：径向渐变的中心点Y轴坐标，即相对于当前多行文本输入框左上角的Y轴坐标，单位为vp。默认值为多行文本输入框高度的一半。</li>
     * <li>.value[2]?.f32：径向渐变的半径，单位为vp。取值范围[0, +∞)，默认值0。传入负数时不生效。</li>
     * <li>.value[3]?.i32：渐变的颜色是否重复着色，0表示不重复着色，1表示重复着色。默认值：0。</li>
     * <li>.object：指定位置处的渐变色颜色。参数类型为{@link ArkUI_ColorStop}。\n
     *  colors：渐变色数组，元素为0xargb格式，形如0xFFFF0000表示红色。\n
     *  stops：指定颜色所处位置的数组，取值范围[0,1.0]，0表示容器开始处，1.0表示结尾处。建议递增设置，若后一元素小于前一元素，则按等于前一元素的值处理。\n
     *  size：颜色个数，若小于colors数组长度则仅生效前size个颜色，不建议设置异常值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0]?.f32：径向渐变的中心点X轴坐标，即相对于当前多行文本输入框左上角的X轴坐标，单位为vp。</li>
     * <li>.value[1]?.f32：径向渐变的中心点Y轴坐标，即相对于当前多行文本输入框左上角的Y轴坐标，单位为vp。</li>
     * <li>.value[2]?.f32：径向渐变的半径，单位为vp，默认值0。</li>
     * <li>.value[3]?.i32：渐变的颜色是否重复着色，0表示不重复着色，1表示重复着色。默认值：0。</li>
     * <li>.object：指定位置处的渐变色颜色。参数类型为{@link ArkUI_ColorStop}。\n
     *  colors：渐变色颜色数组，数组元素为0xargb格式，形如0xFFFF0000表示红色。\n
     *  stops：stops表示指定颜色所处位置的数组，数组元素取值范围为[0,1.0]，0表示需要设置渐变色的容器的开始处，1.0表示容器的结尾处。\n
     *  size：生效后渐变色的颜色个数。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     *
     */
    NODE_TEXT_AREA_RADIAL_GRADIENT = 8049,

    /**
     * @brief Defines the button text content. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: default text content. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: default text content. \n
     *
     */
    NODE_BUTTON_LABEL = MAX_NODE_SCOPE_NUM * ARKUI_NODE_BUTTON,

    /**
     * @brief Sets the button type. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: button type. The parameter type is {@link ArkUI_ButtonType}.
     * The default value is <b>ARKUI_BUTTON_TYPE_CAPSULE</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: button type. The parameter type is {@link ArkUI_ButtonType}.
     * The default value is <b>ARKUI_BUTTON_TYPE_CAPSULE</b>. \n
     *
     */
    NODE_BUTTON_TYPE,

    /**
    * @brief Defines the minimum font scale attribute, which can be set, reset, and obtained as required through APIs.
    *
    * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
    * .value[0].f32: minimum font scale, in fp.
    * \n
    * Format of the return value {@link ArkUI_AttributeItem}:\n
    * .value[0].f32: minimum font scale, in fp.
    *
    * @since 18
    */
    NODE_BUTTON_MIN_FONT_SCALE,

    /**
    * @brief Defines the maximum font scale attribute, which can be set, reset, and obtained as required through APIs.
    *
    * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
    * .value[0].f32: maximum font scale, in fp.
    * \n
    * Format of the return value {@link ArkUI_AttributeItem}:\n
    * .value[0].f32: maximum font scale, in fp.
    *
    * @since 18
    */
    NODE_BUTTON_MAX_FONT_SCALE,

    /**
     * @brief 进度条的当前进度值属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：进度条当前值，取值范围为[0, total]，默认值为0。超出范围时自动修正至有效范围边界值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：进度条当前值，取值范围为[0, total]，默认值为0。</li>
     * </ul>
     *
     * @ingroup Information Display[信息展示]
     */
    NODE_PROGRESS_VALUE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_PROGRESS,
    /**
     * @brief 进度条的总长属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：进度条总长，取值范围为(0, +∞)，默认值为100，需大于0。传入小于等于0的值时不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：进度条总长，取值范围为(0, +∞)，默认值为100。</li>
     * </ul>
     *
     * @ingroup Information Display[信息展示]
     */
    NODE_PROGRESS_TOTAL,
    /**
     * @brief 进度条显示进度值的颜色属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：颜色数值，0xargb格式，形如 0xFFFF0000 表示红色。默认值：跟随主题。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：颜色数值，0xargb格式。</li>
     * </ul>
     *
     * @ingroup Information Display[信息展示]
     */
    NODE_PROGRESS_COLOR,
    /**
     * @brief 进度条的类型属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：进度条类型，具体枚举值及含义参见{@link ArkUI_ProgressType}。默认值为ARKUI_PROGRESS_TYPE_LINEAR。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：进度条类型。</li>
     * </ul>
     *
     * @ingroup Information Display[信息展示]
     */
    NODE_PROGRESS_TYPE,
    /**
     * @brief 线性进度条样式设置，支持属性设置、属性重置和属性获取接口，如果进度条类型不是线性样式则不生效，需先通过NODE_PROGRESS_TYPE将进度条类型设置为ARKUI_PROGRESS_TYPE_LINEAR。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：使用{@link ArkUI_ProgressLinearStyleOption}对象设置组件样式。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：返回{@link ArkUI_ProgressLinearStyleOption}对象，包含线性进度条的样式信息。</li>
     * </ul>
     *
     * @ingroup Information Display[信息展示]
     * @since 15
     */
    NODE_PROGRESS_LINEAR_STYLE,

    /**
     * @brief Defines whether the check box is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the check box is selected.
     * The value <b>1</b> means that the check box is selected, and <b>0</b> means the opposite. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The value <b>1</b> means that the check box is selected, and <b>0</b> means the opposite. \n
     * 
     */
    NODE_CHECKBOX_SELECT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CHECKBOX,

    /**
     * @brief Defines the color of the check box when it is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color of the check box when it is selected, in 0xARGB format, for example, <b>0xFF1122FF</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the check box when it is selected, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     *
     */
    NODE_CHECKBOX_SELECT_COLOR,

    /**
     * @brief Defines the border color of the check box when it is not selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     * 
     */
    NODE_CHECKBOX_UNSELECT_COLOR,

    /**
     * @brief Defines the internal icon style of the check box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.\n
     * .value[1]?.f32: size of the internal mark, in vp. Optional.\n
     * .value[2]?.f32: stroke width of the internal mark, in vp. Optional. The default value is <b>2</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.\n
     * .value[1].f32: size of the internal mark, in vp. \n
     * .value[2].f32: stroke width of the internal mark, in vp. The default value is <b>2</b>. \n
     *
     */
    NODE_CHECKBOX_MARK,

    /**
     * @brief Defines the shape of the check box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: component shape. The parameter type is {@link ArkUI_CheckboxShape}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: component shape. The parameter type is {@link ArkUI_CheckboxShape}.
     *
     */
    NODE_CHECKBOX_SHAPE,

    /**
     * @brief Defines the name of the checkbox.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: component name. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: component name. \n
     *
     * @since 15
     */
    NODE_CHECKBOX_NAME,

    /**
     * @brief Defines the name of the checkbox.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: component name. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: component name. \n
     *
     * @since 15
     */
    NODE_CHECKBOX_GROUP,

    /**
     * @brief Defines the ID of the <b><XComponent></b> component.
     * This attribute can be set and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: component ID. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: component ID. \n
     *
     */
    NODE_XCOMPONENT_ID = MAX_NODE_SCOPE_NUM * ARKUI_NODE_XCOMPONENT,
    /**
     * @brief Specifies the type of the <b>XComponent</b> component. This attribute is read-only. \n
     * The type of the <b>XComponent</b> component must be explicitly set during creation using {@link ARKUI_NODE_XCOMPONENT} or {@link ARKUI_NODE_XCOMPONENT_TEXTURE}, and cannot be modified afterward. \n
     * Attempting to change the type through {@link setAttribute} will cause rendering exceptions.
     *
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: type {@link ArkUI_XComponentType}. \n
     *
     */
    NODE_XCOMPONENT_TYPE,
    /**
     * @brief Specifies the size of the <b>XComponent</b> component. This attribute is read-only. \n
     * Attempting to modify the size through {@link setAttribute} will have no effect.
     *
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: width, in px. \n
     * .value[1].u32: height, in px. \n
     *
     */
    NODE_XCOMPONENT_SURFACE_SIZE,
    /**
     * @brief Defines the rectangle information of surface created by the <b><XComponent></b> component.
     * This attribute can be set and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The horizontal offset of the surface relative to XComponent, in pixels. \n
     * .value[1].i32: The vertical offset of the surface relative to XComponent, in pixels. \n
     * .value[2].i32: The width of the surface created by XComponent, in pixels. \n
     * .value[3].i32: The height of the surface created by XComponent, in pixels. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The horizontal offset of the surface relative to XComponent, in pixels. \n
     * .value[1].i32: The vertical offset of the surface relative to XComponent, in pixels. \n
     * .value[2].i32: The width of the surface created by XComponent, in pixels. \n
     * .value[3].i32: The height of the surface created by XComponent, in pixels. \n
     * @since 18
     */
    NODE_XCOMPONENT_SURFACE_RECT,
    /**
     * @brief Defines whether to enable the AI analyzer for the <b><XComponent></b> component.
     * This attribute can be set and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * value[0].i32: The parameter type is 1 or 0.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].i32: The parameter type is 1 or 0.
     * @since 18
     */
    NODE_XCOMPONENT_ENABLE_ANALYZER,

    /**
     * @brief Defines whether to display the lunar calendar in the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to display the lunar calendar in the date picker. The default value is <b>false</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to display the lunar calendar in the date picker.
     *
     */
    NODE_DATE_PICKER_LUNAR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_DATE_PICKER,
    /**
     * @brief Defines the start date of the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: date. The default value is <b>"1970-1-1"</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: date. \n
     *
     */
    NODE_DATE_PICKER_START,
    /**
     * @brief Defines the end date of the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: date. The default value is <b>"2100-12-31"</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: date. \n
     *
     */
    NODE_DATE_PICKER_END,
    /**
     * @brief Defines the selected date of the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: date. The default value is <b>"2024-01-22"</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: date.
     *
     */
    NODE_DATE_PICKER_SELECTED,
    /**
     * @brief Defines the font color, font size, and font weight for the top and bottom items in the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     *
     */
    NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE,
    /**
     * @brief Defines the font color, font size, and font weight of all items except the top, bottom, and selected
     * items in the date picker. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     *
     */
    NODE_DATE_PICKER_TEXT_STYLE,
    /**
     * @brief Defines the font color, font size, and font weight of the selected item in the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     *
     */
    NODE_DATE_PICKER_SELECTED_TEXT_STYLE,
    /**
     * @brief Defines the mode of the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * value[0].i32: the mode. The value is and enum of {@link ArkUI_DatePickerMode}.\n.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].i32: the mode. The value is and enum of {@link ArkUI_DatePickerMode}.\n.
     *
     * @since 18
     */
    NODE_DATE_PICKER_MODE = 13007,
    /**
     * @brief Defines whether haptic feedback.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to feedback. The value <b>true</b> means to feedback, and
     * <b>false</b> means the opposite.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].i32: whether to feedback.\n
     *
     * @since 18
     */
    NODE_DATE_PICKER_ENABLE_HAPTIC_FEEDBACK = 13008,
    /**
     * @brief Defines whether to support scroll looping for the date picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to support scroll looping. The value <b>true</b> means to support scroll looping, and
     * <b>false</b> means the opposite.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].i32: The value <b>1</b> means to support scroll looping, and <b>0</b> means the opposite. \n
     *
     * @since 20
     */
     NODE_DATE_PICKER_CAN_LOOP = 13009,
    /**
     * @brief Defines the time of the selected item. in the timer picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: time. The default value is the current system time. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: time.
     *
     */

    NODE_TIME_PICKER_SELECTED = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TIME_PICKER,
    /**
     * @brief Defines whether the display time is in 24-hour format.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the display time is in 24-hour format. The default value is <b>false</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the display time is in 24-hour format.
     *
     */
    NODE_TIME_PICKER_USE_MILITARY_TIME,
    /**
     * @brief Defines the font color, font size, and font weight for the top and bottom items in the time picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     *
     */
    NODE_TIME_PICKER_DISAPPEAR_TEXT_STYLE,
    /**
     * @brief Defines the font color, font size, and font weight of all items except the top, bottom, and selected items
     * in the time picker. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     *
     */
    NODE_TIME_PICKER_TEXT_STYLE,
    /**
     * @brief Defines the font color, font size, and font weight of the selected item in the time picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     *
     */
    NODE_TIME_PICKER_SELECTED_TEXT_STYLE,
    /**
     * @brief Defines the start time of the time picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: time. The default value is <b>"00:00:00"</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: time. The default value is <b>"00:00:00"</b>.\n
     *
     * @since 18
     */
    NODE_TIME_PICKER_START = 14005,
    /**
     * @brief Defines the end time of the time picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: time. The default value is <b>"23:59:59"</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: time. The default value is <b>"23:59:59"</b>.\n
     *
     * @since 18
     */
    NODE_TIME_PICKER_END = 14006,
    /**
     * @brief Defines whether the AM/PM option is cascaded with the time in 12-hour mode.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to enable cascade. The default value is <b>false</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to enable cascade.\n
     *
     * @since 18
     */
    NODE_TIME_PICKER_ENABLE_CASCADE = 14007,

    /**
     * @brief Defines the data selection range of the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: type of the text picker {@link ArkUI_TextPickerRangeType}.
     * The default value is <b>ARKUI_TEXTPICKER_RANGETYPE_SINGLE</b>. \n
     * ?.string: string input, whose format varies by picker type.\n
     * 1: single-column picker. The input format is a group of strings separated by semicolons (;).\n
     * 2: multi-column picker. Multiple pairs of plain text strings are supported. The pairs are separated by
     * semicolons (;), and strings within each pair are separated by commas (,). \n
     * ?.object: Object input, whose format varies by picker type.\n
     * 1: single-column picker with image support. The input structure is {@link ARKUI_TextPickerRangeContent}.\n
     * 2: multi-column interconnected picker. The input structure is {@link ARKUI_TextPickerCascadeRangeContent}.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: type of the text picker {@link ArkUI_TextPickerRangeType}.\n
     * ?.string: string output, whose format varies by picker type.\n
     * 1: single-column picker. The output format is a group of strings separated by semicolons (;).\n
     * 2: multi-column picker. Multiple pairs of plain text strings are supported. The pairs are separated by
     * semicolons (;), and strings within each pair are separated by commas (,). \n
     * ?.string: Object output, whose format varies by picker type.\n
     * 1: single-column picker with image support. The output structure is {@link ARKUI_TextPickerRangeContent}.\n
     * 2: multi-column interconnected picker. The output structure is {@link ARKUI_TextPickerCascadeRangeContent}.\n
     *
     */
    NODE_TEXT_PICKER_OPTION_RANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_PICKER,
    /**
     * @brief Defines the index of the default selected item in the data selection range of the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: index. If there are multiple index values, add them one by one. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: index. If there are multiple index values, add them one by one.\n
     *
     */
    NODE_TEXT_PICKER_OPTION_SELECTED,
    /**
     * @brief Defines the value of the default selected item in the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: value of the selected item. If there are multiple values, add them one by one and
     * separate them with semicolons (;). \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: value of the selected item. If there are multiple values, add them one by one and
     * separate them with semicolons (;).\n
     *
     */
    NODE_TEXT_PICKER_OPTION_VALUE,
    /**
     * @brief Defines the font color, font size, and font weight for the top and bottom items in the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     *
     */
    NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE,
    /**
     * @brief Defines the font color, font size, and font weight for all items except the top, bottom, and selected
     * items in the text picker. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     *
     */
    NODE_TEXT_PICKER_TEXT_STYLE,
    /**
     * @brief Defines the font color, font size, and font weight for the selected item in the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: array of five parameters of the string type, separated by semicolons (;).\n
     * Parameter 1: font color, in #ARGB format.\n
     * Parameter 2: font size, in fp. The value is a number.\n
     * Parameter 3: font weight. Available options are ("bold", "normal", "bolder", "lighter", "medium", "regular").\n.
     * Parameter 4: fonts, separated by commas (,).\n
     * Parameter 5: font style. Available options are ("normal", "italic").\n
     * Example: "#ff182431;14;normal;Arial,HarmonyOS Sans;normal". \n
     *
     */
    NODE_TEXT_PICKER_SELECTED_TEXT_STYLE,
    /**
     * @brief Defines the index of the default selected item in the data selection range of the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0...].i32: index of the default item in the data selection range.
     *
     */
    NODE_TEXT_PICKER_SELECTED_INDEX,
    /**
     * @brief Defines whether to support scroll looping for the text picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to support scroll looping. The value <b>true</b> means to support scroll looping, and
     * <b>false</b> means the opposite.\n \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].i32: The value <b>1</b> means to support scroll looping, and <b>0</b> means the opposite. \n
     *
     */
    NODE_TEXT_PICKER_CAN_LOOP,
    /**
     * @brief Defines the height of each item in the picker. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: item height, in vp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].f32: item height, in vp. \n
     *
     */
    NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT,
    /**
     * @brief Defines whether haptic feedback.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to feedback. The value <b>true</b> means to feedback, and
     * <b>false</b> means the opposite.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].i32: whether to feedback.\n
     *
     * @since 18
     */
    NODE_TEXT_PICKER_ENABLE_HAPTIC_FEEDBACK = 15010,
    /**
     * @brief Defines the background color and border radius of the selected items.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: background color, in 0xARGB format, for example, <b>0xFF1122FF</b>. \n
     * 1: .value[1].f32: radius of the four corners. \n
     * 2: .value[1].f32: radius of the upper left corner. \n
     * .value[2].f32: radius of the upper right corner. \n
     * .value[3].f32: radius of the lower left corner. \n
     * .value[4].f32: radius of the lower right corner. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: background color, in 0xARGB format, for example, <b>0xFF1122FF</b>. \n     *
     * .value[1].f32: radius of the upper left corner. \n
     * .value[2].f32: radius of the upper right corner. \n
     * .value[3].f32: radius of the lower left corner. \n
     * .value[4].f32: radius of the lower right corner. \n
     *
     * @since 20
     */
    NODE_TEXT_PICKER_SELECTED_BACKGROUND_STYLE = 15011,
    /**
     * @brief Defines the style of the background in the selected state of the calendar picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: style of the background in the selected state of the calendar picker.
     * The value range is [0, +∞). If the value is <b>0</b>, the background is a rectangle with square corners.
     If the value is in the 0–16 range, the background is a rectangle with rounded corners. If the value is equal to
     * or greater than 16, the background is a circle. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: style of the background in the selected state of the calendar picker. The value range is [0, +∞).
     * If the value is <b>0</b>, the background is a rectangle with square corners.
     If the value is in the 0–16 range, the background is a rectangle with rounded corners. If the value is equal to or
     * greater than 16, the background is a circle. \n
     *
     */
    NODE_CALENDAR_PICKER_HINT_RADIUS = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CALENDAR_PICKER,
    /**
     * @brief Defines the date of the selected item in the calendar picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: year of the selected date. \n
     * .value[1].u32: month of the selected date. \n
     * .value[2].u32: day of the selected date. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: year of the selected date. \n
     * .value[1].u32: month of the selected date. \n
     * .value[2].u32: day of the selected date. \n
     *
     */
    NODE_CALENDAR_PICKER_SELECTED_DATE,
    /**
     * @brief Defines how the calendar picker is aligned with the entry component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: alignment mode. The parameter type is {@link ArkUI_CalendarAlignment}. \n
     * .value[1]?.f32: offset of the picker relative to the entry component along the x-axis after alignment based on
     * the specified alignment mode. \n
     * .value[2]?.f32: offset of the picker relative to the entry component along the y-axis after alignment based on
     * the specified alignment mode. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: alignment mode. The parameter type is {@link ArkUI_CalendarAlignment}. \n
     * .value[1]?.f32: offset of the picker relative to the entry component along the x-axis after alignment based on
     * the specified alignment mode. \n
     * .value[2]?.f32: offset of the picker relative to the entry component along the y-axis after alignment based on
     * the specified alignment mode. \n
     *
     */
    NODE_CALENDAR_PICKER_EDGE_ALIGNMENT,
    /**
     * @brief Defines the font color, font size, and font weight in the entry area of the calendar picker.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.u32: font color of the entry area. \n
     * .value[1]?.f32: font size of the entry area, in fp. \n
     * .value[2]?.i32: font weight of the entry area. The parameter type is {@link ArkUI_FontWeight}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: font color of the entry area. \n
     * .value[1].f32: font size of the entry area, in fp. \n
     * .value[2].i32: font weight of the entry area. The parameter type is {@link ArkUI_FontWeight}. \n
     *
     */
    NODE_CALENDAR_PICKER_TEXT_STYLE,
    /**
     * @brief Defines the start date of the calendar picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: date. The value like <b>"1970-1-1"</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: date. \n
     *
     * @since 18
     */
    NODE_CALENDAR_PICKER_START = 16004,
    /**
     * @brief Defines the end date of the calendar picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: date. The value like <b>"2100-12-31"</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: date. \n
     *
     * @since 18
     */
    NODE_CALENDAR_PICKER_END = 16005,
    /**
     * @brief Defines the color of the slider. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color of the slider, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the slider, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     *
     */
    NODE_SLIDER_BLOCK_COLOR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SLIDER,

    /**
     * @brief Defines the background color of the slider. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: background color, in 0xARGB format, for example, <b>0xFF1122FF</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: background color, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     *
     */
    NODE_SLIDER_TRACK_COLOR,

    /**
     * @brief Defines the color of the selected part of the slider track. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color of the selected part of the slider track, in 0xARGB format, for example, <b>0xFF1122FF</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the selected part of the slider track, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     *
     */
    NODE_SLIDER_SELECTED_COLOR,

    /**
     * @brief Sets whether to display the stepping value. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to display the stepping value. The value <b>1</b> means to display the stepping value,
     * and <b>0</b> (default value) means the opposite. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to display the stepping value. The value <b>1</b> means to display the stepping value,
     * and <b>0</b> (default value) means the opposite. \n
     *
     */
    NODE_SLIDER_SHOW_STEPS,

    /**
     * @brief Defines the slider shape, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: shape. The parameter type is {@link ArkUI_SliderBlockStyle}. \n
     * .string?: depending on the shape. Optional. \n
     * ARKUI_SLIDER_BLOCK_STYLE_IMAGE: image resource of the slider. Example: /pages/common/icon.png. \n
     * ARKUI_SLIDER_BLOCK_STYLE_SHAPE: custom shape of the slider. \n
     * There are five types:\n
     * 1. Rectangle:\n
     * .value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_RECTANGLE</b> for the rectangle shape.\n
     * .value[2].f32: width of the rectangle.\n
     * .value[3].f32: height of the rectangle.\n
     * .value[4].f32: width of the rounded corner of the rectangle.\n
     * .value[5].f32: height of the rounded corner of the rectangle.\n
     * 2. Circle:\n
     * .value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_CIRCLE</b> for the circle shape.\n
     * .value[2].f32: width of the circle.\n
     * .value[3].f32: height of the circle.\n
     * 3.Ellipse:\n
     * .value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_ELLIPSE</b> for the ellipse shape.\n
     * .value[2].f32: width of the ellipse.\n
     * .value[3].f32: height of the ellipse;\n
     * 4. Path:\n
     * .value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_PATH</b> for the path shape.\n
     * .value[2].f32: width of the path.\n
     * .value[3].f32: height of the path.\n
     * .string: command for drawing the path.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: shape. The parameter type is {@link ArkUI_SliderBlockStyle}. \n
     * .string?: depending on the shape. Optional. \n
     * ARKUI_SLIDER_BLOCK_STYLE_IMAGE: image resource of the slider. Example: /pages/common/icon.png. \n
     * ARKUI_SLIDER_BLOCK_STYLE_SHAPE: custom shape of the slider. \n
      * There are five types:\n
     * 1. Rectangle:\n
     * .value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_RECTANGLE</b> for the rectangle shape.\n
     * .value[2].f32: width of the rectangle.\n
     * .value[3].f32: height of the rectangle.\n
     * .value[4].f32: width of the rounded corner of the rectangle.\n
     * .value[5].f32: height of the rounded corner of the rectangle.\n
     * 2. Circle:\n
     * .value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_CIRCLE</b> for the circle shape.\n
     * .value[2].f32: width of the circle.\n
     * .value[3].f32: height of the circle.\n
     * 3.Ellipse:\n
     * .value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_ELLIPSE</b> for the ellipse shape.\n
     * .value[2].f32: width of the ellipse.\n
     * .value[3].f32: height of the ellipse;\n
     * 4. Path:\n
     * .value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_PATH</b> for the path shape.\n
     * .value[2].f32: width of the path.\n
     * .value[3].f32: height of the path.\n
     * .string: command for drawing the path.\n
     *
     */
    NODE_SLIDER_BLOCK_STYLE,

    /**
     * @brief Defines the current value of the slider. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: current value. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: current value.
     *
     */
    NODE_SLIDER_VALUE,

    /**
     * @brief Defines the minimum value of the slider. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: minimum value. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: minimum value.
     *
     */
    NODE_SLIDER_MIN_VALUE,

    /**
     * @brief Defines the maximum value of the slider. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: maximum value. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: maximum value.
     *
     */
    NODE_SLIDER_MAX_VALUE,

    /**
     * @brief Defines the step of the slider. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: step. The value range is [0.01, 100]. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: step. The value range is [0.01, 100].
     *
     */
    NODE_SLIDER_STEP,

    /**
     * @brief Defines whether the slider moves horizontally or vertically. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the slider moves horizontally or vertically.
     * The parameter type is {@link ArkUI_SliderDirection}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the slider moves horizontally or vertically.
     *
     */
    NODE_SLIDER_DIRECTION,

    /**
     * @brief Defines whether the slider values are reversed. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the slider values are reversed. The value <b>1</b> means that the slider values are
     * reversed, and <b>0</b> means the opposite. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the slider values are reversed. The value <b>1</b> means that the slider values are
     * reversed, and <b>0</b> means the opposite.
     *
     */
    NODE_SLIDER_REVERSE,

    /**
     * @brief Defines the style of the slider thumb and track. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: style of the slider thumb and track. The parameter type is {@link ArkUI_SliderStyle}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: style of the slider thumb and track. The parameter type is {@link ArkUI_SliderStyle}.
     *
     */
    NODE_SLIDER_STYLE,

    /**
     * @brief Sets the track thickness of the slider.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: track thickness of the slider, in vp. The default value is 4.0 vp when <b>NODE_SLIDER_STYLE</b>
     * is set to <b>ARKUI_SLIDER_STYLE_OUT_SET</b> and 20.0 vp when <b>NODE_SLIDER_STYLE</b> is set to
     * <b>ARKUI_SLIDER_STYLE_IN_SET</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: track thickness of the slider, in vp. \n
     *
     */
    NODE_SLIDER_TRACK_THICKNESS,

    /**
     * @brief Defines whether haptic feedback.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to feedback. The value <b>true</b> means to feedback, and
     * <b>false</b> means the opposite.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].i32: whether to feedback.\n
     * When enabling haptic feedback, you need to add "ohos.permission.VIBRATE" in the
     * requestPermissions field of the module.json5 file to enable vibration permission.\n
     *
     * @since 18
     */
    NODE_SLIDER_ENABLE_HAPTIC_FEEDBACK = 17013,

    /**
     * @brief Sets a custom component on the leading side of the Slider component.
     *
     * Attribute setting method {@link ArkUI_AttributeItem} parameter format:\n
     * .object: Parameter type {@link ArkUI_NodeHandle}.
     *
     * The prefix component will be placed at the start position of the Slider，
     * typically on the left side in LTR layouts.
	 *
	 * @since 20
     */
    NODE_SLIDER_PREFIX,

    /**
     * @brief Sets a custom component on the trailing side of the Slider component.
     *
     * Attribute setting method {@link link ArkUI_AttributeItem} parameter format:\n
     * .object: Parameter type {@link ArkUI_NodeHandle}.
     *
     * The suffix component will be placed at the end position of the Slider,
     * typically on the right side in LTR layouts.
	 *
	 * @since 20
     */
    NODE_SLIDER_SUFFIX,

    /**
     * @brief Defines the color of the slider block. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: array of color stops, each of which consists of a color and its stop position.
     * The parameter type is {@link ArkUI_ColorStop}. Invalid colors are automatically skipped. \n \n
     * colors: colors of the color stops. \n
     * stops: stop positions of the color stops. \n
     * size: number of colors. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: array of color stops, each of which consists of a color and its stop position.
     * The parameter type is {@link ArkUI_ColorStop}. Invalid colors are automatically skipped. \n \n
     * colors: colors of the color stops. \n
     * stops: stop positions of the color stops. \n
     * size: number of colors. \n
     *
     * @since 21
     */
    NODE_SLIDER_BLOCK_LINEAR_GRADIENT_COLOR,

    /**
     * @brief Defines the background color of the slider. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: array of color stops, each of which consists of a color and its stop position.
     * The parameter type is {@link ArkUI_ColorStop}. Invalid colors are automatically skipped. \n \n
     * colors: colors of the color stops. \n
     * stops: stop positions of the color stops. \n
     * size: number of colors. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: array of color stops, each of which consists of a color and its stop position.
     * The parameter type is {@link ArkUI_ColorStop}. Invalid colors are automatically skipped. \n \n
     * colors: colors of the color stops. \n
     * stops: stop positions of the color stops. \n
     * size: number of colors. \n
     *
     * @since 21
     */
    NODE_SLIDER_TRACK_LINEAR_GRADIENT_COLOR,

    /**
     * @brief Defines the color of the selected part of the slider track. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: array of color stops, each of which consists of a color and its stop position.
     * The parameter type is {@link ArkUI_ColorStop}. Invalid colors are automatically skipped. \n \n
     * colors: colors of the color stops. \n
     * stops: stop positions of the color stops. \n
     * size: number of colors. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: array of color stops, each of which consists of a color and its stop position.
     * The parameter type is {@link ArkUI_ColorStop}. Invalid colors are automatically skipped. \n \n
     * colors: colors of the color stops. \n
     * stops: stop positions of the color stops. \n
     * size: number of colors. \n
     *
     * @since 21
     */
    NODE_SLIDER_SELECTED_LINEAR_GRADIENT_COLOR,

    /**
     * @brief Set the selection status of an option button. Attribute setting,
     * attribute resetting, and attribute obtaining are supported.
     * Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:\n
     * .value[0].i32: check status of an option button. The default value is false.
     * Attribute obtaining method return value {@Link ArkUI_AttributeItem} format:\n
     * .value[0].i32: selection status of an option button.
     */
    NODE_RADIO_CHECKED = MAX_NODE_SCOPE_NUM * ARKUI_NODE_RADIO,
    /**
     * @brief Set the styles of the selected and deselected states of the option button.
     * The attribute setting, attribute resetting, and attribute obtaining are supported.
     * Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:\n
     * .value[0]?. u32: color of the mother board in enabled state. \n
     * The type is 0xARGB, and the default value is 0xFF007DFF. \n
     * .value[1]?. u32: stroke color in the close state. The type is 0xARGB, \n
     * and the default value is 0xFF182431. \n
     * .value[2]?. u32: color of the internal round pie in the enabled state. \n
     * The type is 0xARGB, and the default value is 0xFFFFFFFF. \n
     * Attribute obtaining method return value {@Link ArkUI_AttributeItem} format:\n
     * .value[0]. u32: color of the mother board in enabled state. \n
     * The type is 0xARGB, and the default value is 0xFF007DFF. \n
     * .value[1]. u32: stroke color in the close state. The type is 0xARGB, \n
     * and the default value is 0xFF182431. \n
     * .value[2]. u32: color of the internal round pie in the enabled state. \n
     * The type is 0xARGB, and the default value is 0xFFFFFFF. \n
     */
    NODE_RADIO_STYLE,
    /**
     * @brief Sets the value of the current radio.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:\n
     * .string: radio value.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: radio value.\n
     *
     */
    NODE_RADIO_VALUE,
    /**
     * @brief Set the group name of the current Radio group, only one radio of the same group can be selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:\n
     * .string: name of the group to which the current option box belongs.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: name of the group to which the current option box belongs.\n
     *
     */
    NODE_RADIO_GROUP,

    /**
     * @brief Set the image frames for the image animator. Dynamic updates is not supported.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:\n
     * .size: number of the images.\n
     * .object: array of the images, the type is {@ArkUI_ImageAnimatorFrameInfo} array.\n
     * \n
     * Attribute obtaining method return value {@Link ArkUI_AttributeItem} format:\n
     * .size: number of the images.\n
     * .object: array of the images, the type is {@ArkUI_ImageAnimatorFrameInfo} array.\n
     *
    */
    NODE_IMAGE_ANIMATOR_IMAGES = ARKUI_NODE_IMAGE_ANIMATOR * MAX_NODE_SCOPE_NUM,
    /**
     * @brief Set the playback status of the animation for the image animator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:\n
     * .value[0].i32: the playback status of the animation, the type is {@link ArkUI_AnimationStatus},
     * and the default value is ARKUI_ANIMATION_STATUS_INITIAL.
     *
     * Attribute obtaining method return value {@Link ArkUI_AttributeItem} format:\n
     * .value[0].i32: the playback status of the animation, the type is {@link ArkUI_AnimationStatus}.\n
     *
    */
    NODE_IMAGE_ANIMATOR_STATE = 19001,
    /**
     * @brief Set the playback duration for the image animator. When the duration is 0, no image is played.
     * The value change takes effect only at the beginning of the next cycle.
     * When a separate duration is set in images, the setting of this attribute is invalid.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:\n
     * .value[0].i32: the playback duration, the unit is ms and the default value is 1000.\n
     *
     * Attribute obtaining method return value {@Link ArkUI_AttributeItem} format:\n
     * .value[0].i32: the playback duration, the unit is ms.\n
     *
    */
    NODE_IMAGE_ANIMATOR_DURATION = 19002,
    /**
     * @brief Set the playback direction for the image animator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:\n
     * .value[0].i32: the playback direction. 0 indicates that images are played from the first one to the last one,
     * and 1 indicates that images are played from the last one to the first one.\n
     *
     * Attribute obtaining method return value {@Link ArkUI_AttributeItem} format:\n
     * .value[0].i32: the playback direction. 0 indicates that images are played from the first one to the last one,
     * and 1 indicates that images are played from the last one to the first one.\n
     *
    */
    NODE_IMAGE_ANIMATOR_REVERSE = 19003,
    /**
     * @brief Set whether the image size is the same as the component size.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:\n
     * .value[0].i32: whether the image size is the same as the component size.
     * 1 indicates the image size is the same as the component size.
     * In this case, the width, height, top, and left attributes of the image are invalid.
     * 0 indicates the image size is customized.
     * The width, height, top, and left attributes of each image must be set separately.
     *
     * Attribute obtaining method return value {@Link ArkUI_AttributeItem} format:\n
     * .value[0].i32: whether the image size is the same as the component size.
     * 1 indicates the image size is the same as the component size.
     * 0 indicates the image size is customized.
     *
    */
    NODE_IMAGE_ANIMATOR_FIXED_SIZE = 19004,
    /**
     * @brief Set the status before and after execution of the animation in the current playback direction.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:\n
     * .value[0].i32: the status before and after execution of the animation in the current playback direction,
     * the type is {ArkUI_AnimationFillMode} and the default value is ARKUI_ANIMATION_FILL_MODE_FORWARDS.\n
     *
     * Attribute obtaining method return value {@Link ArkUI_AttributeItem} format:\n
     * .value[0].i32: the status before and after execution of the animation in the current playback direction,
     * the type is {ArkUI_AnimationFillMode}.
     *
    */
    NODE_IMAGE_ANIMATOR_FILL_MODE = 19005,
    /**
     * @brief Set the number of times that the animation is played.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:\n
     * .value[0].i32: the number of times that the animation is played.\n
     *
     * Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:\n
     * .value[0].i32: the number of times that the animation is played.\n
     *
    */
    NODE_IMAGE_ANIMATOR_ITERATION = 19006,

    /**
     * @brief Defines the name of the checkboxgroup.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: component name. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: component name. \n
     * 
     * @since 15
     */
    NODE_CHECKBOX_GROUP_NAME  = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CHECKBOX_GROUP,

    /**
     * @brief Defines whether the checkboxgroup is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the checkboxgroup is selected.
     * The value <b>1</b> means that the checkboxgroup is selected, and <b>0</b> means the opposite. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The value <b>1</b> means that the checkboxgroup is selected, and <b>0</b> means the opposite. \n
     * 
     * @since 15
     */
    NODE_CHECKBOX_GROUP_SELECT_ALL,

    /**
     * @brief Defines the color of the checkboxgroup when it is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color of the checkboxgroup when it is selected, in 0xARGB format,
     * for example, <b>0xFF1122FF</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the checkboxgroup when it is selected, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     *
     * @since 15
     */
    NODE_CHECKBOX_GROUP_SELECTED_COLOR,
    /**
     * @brief Defines the border color of the checkboxgroup when it is not selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.
     * 
     * @since 15
     */
    NODE_CHECKBOX_GROUP_UNSELECTED_COLOR,

    /**
     * @brief Defines the internal icon style of the checkboxgroup.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.\n
     * .value[1]?.f32: size of the internal mark, in vp. Optional.\n
     * .value[2]?.f32: stroke width of the internal mark, in vp. Optional. The default value is <b>2</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.\n
     * .value[1].f32: size of the internal mark, in vp. \n
     * .value[2].f32: stroke width of the internal mark, in vp. The default value is <b>2</b>. \n
     *
     * @since 15
     */
    NODE_CHECKBOX_GROUP_MARK,

    /**
     * @brief Defines the shape of the checkboxgroup.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: component shape. The parameter type is {@link ArkUI_CheckboxShape}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: component shape. The parameter type is {@link ArkUI_CheckboxShape}.
     *
     * @since 15
     */
    NODE_CHECKBOX_GROUP_SHAPE,

    /**
     * @brief TextEditor组件回车键类型，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：回车键类型，参数类型{@link ArkUI_EnterKeyType}，默认值为ARKUI_ENTER_KEY_TYPE_NEW_LINE。
     * <br>**返回：**
     * <br>.value[0].i32：回车键类型，参数类型{@link ArkUI_EnterKeyType}。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_ENTER_KEY_TYPE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_EDITOR,

    /**
     * @brief TextEditor组件光标颜色，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].u32：光标颜色，采用0xARGB格式，例如0xFFFF0000表示红色。默认跟随系统主题。
     * <br>**返回：**
     * <br>.value[0].u32：光标颜色，采用0xARGB格式，例如0xFFFF0000表示红色。默认跟随系统主题。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_CARET_COLOR,

    /**
     * @brief TextEditor组件滚动条颜色，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.data[0].u32：滚动条颜色，采用0xARGB格式，例如0xFFFF0000表示红色。默认跟随系统主题。
     * <br>**返回：**
     * <br>.data[0].u32：滚动条颜色，采用0xARGB格式，例如0xFFFF0000表示红色。默认跟随系统主题。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_SCROLL_BAR_COLOR,

    /**
     * @brief TextEditor组件滚动条显示模式，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：滚动条显示模式，参数类型{@link ArkUI_BarState}，默认值为ARKUI_BAR_STATE_AUTO。
     * <br>**返回：**
     * <br>.value[0].i32：滚动条显示模式，参数类型{@link ArkUI_BarState}。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_BAR_STATE,

    /**
     * @brief TextEditor组件文本实体识别功能开关，启用后，文本中的电话号码、邮箱、链接等实体将被自动识别并标记为可交互内容。
     * 配合NODE_TEXT_EDITOR_DATA_DETECTOR_CONFIG属性可自定义识别类型和交互行为。支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：是否启用文本实体识别功能，0表示禁用，1表示启用，默认值为0。推荐在需要自动识别并高亮文本中实体信息的场景下设置此属性。
     * <br>**返回：**
     * <br>.value[0].i32：是否启用了文本实体识别功能，0表示禁用，1表示启用。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_ENABLE_DATA_DETECTOR,

    /**
     * @brief TextEditor组件文本实体识别配置，设置后，可配置识别类型、实体显示样式，并可选择是否开启长按预览功能。配合NODE_TEXT_EDITOR_ENABLE_DATA_DETECTOR属性使用，
     * 支持属性设置和属性重置。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.object：文本实体识别配置，设置后可指定需要识别的文本实体类型（如电话号码、邮箱、链接等）及识别后的交互行为。仅在启用文本实体识别功能(
     * NODE_TEXT_EDITOR_ENABLE_DATA_DETECTOR设置为1)后传入此参数以自定义识别类型，不传入时使用系统默认识别配置。参数类型{@link ArkUI_TextDataDetectorConfig}。
     * 
     * @since 24
     */
    NODE_TEXT_EDITOR_DATA_DETECTOR_CONFIG,

    /**
     * @brief TextEditor组件扩展菜单选项，支持属性设置和属性重置。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.object：扩展菜单选项，设置后可自定义默认菜单项的行为，或添加自定义选项内容。参数类型{@link ArkUI_TextEditMenuOptions}。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_EDIT_MENU_OPTIONS,

    /**
     * @brief TextEditor组件无输入时的提示文本选项，支持属性设置和属性重置。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.object：无输入时的提示文本选项，参数类型{@link ArkUI_TextEditorPlaceholderOptions}。不传入时，编辑器无输入状态下不显示提示文本。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_PLACEHOLDER,

    /**
     * @brief TextEditor组件属性字符串控制器，支持属性设置。设置后，可通过该控制器管理TextEditor中的内容、光标、选区、输入样式及编辑状态。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.object：属性字符串控制器，参数类型{@link ArkUI_TextEditorStyledStringController}。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_STYLED_STRING_CONTROLLER,

    /**
     * @brief TextEditor组件预上屏功能开关，启用后，组件内显示输入法输入过程中的拼音、笔画字符。支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：是否启用预上屏功能，0表示禁用，1表示启用，默认值为1。
     * <br>**返回：**
     * <br>.value[0].i32：是否启用预上屏功能，0表示禁用，1表示启用。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_ENABLE_PREVIEW_TEXT,

    /**
     * @brief TextEditor组件TextLayoutManager获取，获取后，可通过布局管理器查询文本的布局信息，如行数、行高和内容偏移等。支持属性获取。
     * <br>作为属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**返回：**
     * <br>.object：布局管理器，可通过该管理器查询文本的布局信息。参数类型{@link ArkUI_TextLayoutManager}。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_LAYOUT_MANAGER,

    /**
      * @brief TextEditor组件文本选择识别AI菜单开关，支持属性设置、属性重置和属性获取。启用后，用户选中特殊文本实体时将弹出AI识别菜单，提供基于选中文本内容的智能识别和操作选项。
      * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
      * <br>**参数：**
      * <br>.value[0].i32：是否启用文本选择识别的AI菜单，0表示禁用，1表示启用，默认值为1。
      * <br>**返回：**
      * <br>.value[0].i32：是否启用了文本选择识别的AI菜单，0表示禁用，1表示启用。
      *
      * @since 24
      */
    NODE_TEXT_EDITOR_ENABLE_SELECTED_DATA_DETECTOR,

    /**
     * @brief TextEditor组件选中内容背景颜色，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.data[0].u32：选中内容的背景颜色，采用0xARGB格式，例如0xFFFF0000表示红色。默认跟随系统主题。
     * <br>**返回：**
     * <br>.data[0].u32：选中内容的背景颜色，采用0xARGB格式，例如0xFFFF0000表示红色。默认跟随系统主题。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_SELECTED_BACKGROUND_COLOR,

    /**
     * @brief TextEditor组件非点击获焦时拉起输入法开关，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：非点击获焦时是否拉起输入法，0表示不拉起，1表示拉起，默认值为1。
     * <br>**返回：**
     * <br>.value[0].i32：非点击获焦时是否拉起输入法，0表示不拉起，1表示拉起。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_ENABLE_KEYBOARD_ON_FOCUS,

    /**
     * @brief TextEditor组件最大字符数，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：文本编辑器允许输入的最大长度，取值范围为[0, +∞)，超出此限制后将阻止继续输入文本。设置为0、负数或未设置该属性时不限制输入长度。
     * <br>**返回：**
     * <br>.value[0].i32：文本编辑器允许输入的最大长度。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_MAX_LENGTH,

    /**
     * @brief TextEditor组件内容最大行数，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：文本编辑器最大行数限制，取值范围[0, +∞)。取值为0时按无穷大处理；设置为0、负数或未设置该属性时不限制行数。建议在需要固定显示高度的场景下设置该参数。
     * <br>**返回：**
     * <br>.value[0].i32：文本编辑器最大行数限制。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_MAX_LINES,

    /**
     * @brief TextEditor组件触觉反馈开关，启用后，在文本拖选等交互操作时将产生触觉反馈震动响应，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：是否在文本编辑器中启用触觉反馈，0表示不启用，1表示启用，默认值为1。
     * <br>**返回：**
     * <br>.value[0].i32：是否启用了触觉反馈，0表示不启用，1表示启用。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_ENABLE_HAPTIC_FEEDBACK,

    /**
     * @brief TextEditor组件复制选项，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：复制选项，参数类型{@link ArkUI_CopyOptions}，默认值为ARKUI_COPY_OPTIONS_LOCAL_DEVICE。
     * <br>**返回：**
     * <br>.value[0].i32：复制选项，参数类型{@link ArkUI_CopyOptions}。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_COPY_OPTIONS,

    /**
    * @brief TextEditor组件键盘外观，支持属性设置、属性重置和属性获取。
    * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
    * <br>**参数：**
    * <br>.value[0].i32：键盘外观，参数类型{@link ArkUI_KeyboardAppearance}，默认值为ARKUI_KEYBOARD_APPEARANCE_NONE_IMMERSIVE。
    * <br>**返回：**
    * <br>.value[0].i32：文本编辑器当前设置的键盘外观类型，参数类型{@link ArkUI_KeyboardAppearance}。
    *
    * @since 24
    */
    NODE_TEXT_EDITOR_KEYBOARD_APPEARANCE,

    /**
     * @brief TextEditor组件是否阻止返回键事件向上层传播，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：是否阻止返回事件传播，0表示不阻止，1表示阻止，默认值为0。推荐在编辑器有未保存内容或需要拦截返回键防止意外退出的场景设置为1。
     * <br>**返回：**
     * <br>.value[0].i32：是否阻止返回事件传播，0表示不阻止，1表示阻止。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_STOP_BACK_PRESS,

    /**
     * @brief TextEditor组件中西文自动间距开关，支持属性设置、属性重置和属性获取。适用于包含中英文混排内容的编辑场景，启用后可在中文与西文之间自动添加间距，改善混排文本的阅读体验。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：是否启用中西文自动间距，0表示不启用，1表示启用，默认值为0。推荐在包含中英文混排内容的编辑场景设置为1，以改善混排文本的阅读体验。
     * <br>**返回：**
     * <br>.value[0].i32：是否启用中西文自动间距，0表示不启用，1表示启用。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_ENABLE_AUTO_SPACING,

    /**
     * @brief TextEditor组件自定义键盘。当需要替换系统默认键盘时传入此参数（如数字键盘、表情键盘等特殊输入布局），不传入时使用系统默认键盘。支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.object：自定义键盘，参数类型{@link ArkUI_NodeHandle}。
     * <br>.value[0]?.i32：设置自定义键盘是否支持内容避让功能，即键盘弹出时页面内容自动调整位置以避免被键盘遮挡，0表示不支持，1表示支持，默认值为0。
     * <br>**返回：**
     * <br>.object：自定义键盘，参数类型{@link ArkUI_NodeHandle}。
     * <br>.value[0].i32：自定义键盘是否支持内容避让功能，即键盘弹出时页面内容自动调整位置以避免被键盘遮挡，0表示不支持，1表示支持。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_CUSTOM_KEYBOARD,

    /**
     * @brief TextEditor组件自定义文本选择菜单绑定，支持属性设置和属性重置。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.object：自定义选择菜单，不传入时使用系统默认文本选择菜单。参数类型{@link ArkUI_TextEditorSelectionMenuOptions}。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_BIND_SELECTION_MENU,

    /**
     * @brief TextEditor组件首行尾行防截断间距开关，启用后，在首行和尾行增加间距以避免文字截断，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：是否添加首行尾行防截断间距，0表示不添加，1表示添加，默认值为0。
     * <br>**返回：**
     * <br>.value[0].i32：是否添加首行尾行防截断间距，0表示不添加，1表示添加。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_INCLUDE_FONT_PADDING,

    /**
     * @brief TextEditor组件行高自适应开关，在多行文字叠加时，行高可以基于文字实际高度自适应，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：行高是否自适应，0表示不自适应，1表示自适应，默认值为0。
     * <br>**返回：**
     * <br>.value[0].i32：行高是否自适应，0表示不自适应，1表示自适应。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_FALLBACK_LINE_SPACING,

    /**
     * @brief TextEditor组件行首标点符号压缩开关，启用后，行首的标点符号将缩减占位宽度，调整文本排版对齐效果，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：是否启用行首标点符号压缩，0表示不启用，1表示启用，默认值为0。
     * <br>**返回：**
     * <br>.value[0].i32：是否启用行首标点符号压缩，0表示不启用，1表示启用。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_COMPRESS_LEADING_PUNCTUATION,

    /**
     * @brief TextEditor组件选中拖拽预览样式，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.object：选中拖拽预览样式配置，参数类型{@link ArkUI_SelectedDragPreviewStyle}。当需要自定义选中文本拖拽时的预览效果时传入此参数，不传入时使用系统默认拖拽预览样式。
     * <br>**返回：**
     * <br>.object：选中拖拽预览样式配置，参数类型{@link ArkUI_SelectedDragPreviewStyle}。
     * 
     * @since 24
     */
    NODE_TEXT_EDITOR_SELECTED_DRAG_PREVIEW_STYLE,

    /**
     * @brief TextEditor组件单行模式开关，支持属性设置、属性重置和属性获取。启用单行模式后，NODE_TEXT_EDITOR_MAX_LINES属性设置的最大行数将不再生效。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：是否启用单行模式，0表示不启用，1表示启用，默认值为0。
     * <br>**返回：**
     * <br>.value[0].i32：是否启用单行模式，0表示不启用，1表示启用。
     * 
     * @since 24
     */
    NODE_TEXT_EDITOR_SINGLE_LINE,

    /**
     * @brief TextEditor组件孤字优化开关，支持属性设置、属性重置和属性获取。启用后会调整换行点以尽可能避免孤字。
     * 仅在[ArkUI_WordBreak](capi-text-common-h.md#arkui_wordbreak)属性为非ARKUI_WORD_BREAK_BREAK_ALL时生效。
     * <br>作为属性设置方法参数、属性获取方法返回值[ArkUI_AttributeItem](capi-arkui-nativemodule-arkui-attributeitem.md)格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：是否启用孤字优化，0表示不启用，1表示启用。默认值为0。
     * <br>**返回：**
     * <br>.value[0].i32：是否启用孤字优化，0表示不启用，1表示启用。
     *
     * @since 26.0.0
     */
     NODE_TEXT_EDITOR_ORPHAN_CHAR_OPTIMIZATION,

    /**
     * @brief 设置TextEditor组件在文本宽度超过内容区宽度时是否启用水平滚动，支持属性设置、属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：是否启用水平滚动，0表示不启用水平滚动，1表示启用水平滚动。默认值为0。
     * <br>**返回：**
     * <br>.value[0].i32：是否启用水平滚动，0表示不启用水平滚动，1表示启用水平滚动。
     *
     * @since 26.0.0
     */
    NODE_TEXT_EDITOR_HORIZONTAL_SCROLLING,

    /**
     * @brief 设置TextEditor组件是否启用行尾标点符号悬挂，支持属性设置、属性重置和属性获取。
     * <br>启用后，行尾单个标点符号超出排版宽度而不换行，避免行尾标点符号换行至下一行行首，从而改善文本排版效果。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.value[0].i32：是否启用行尾标点符号悬挂，0表示不启用标点符号悬挂，1表示启用标点符号悬挂。默认值为0。
     * <br>**返回：**
     * <br>.value[0].i32：是否启用行尾标点符号悬挂，0表示不启用行尾标点符号悬挂，1表示启用行尾标点符号悬挂。
     *
     * @since 26.0.0
     */
    NODE_TEXT_EDITOR_PUNCTUATION_OVERFLOW,

    /**
     * @brief Defines the alignment mode of the child components in the container. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: alignment mode. The data type is {@link ArkUI_Alignment}.
     * The default value is <b>ARKUI_ALIGNMENT_CENTER</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: alignment mode. The data type is {@link ArkUI_Alignment}. \n
     *
     */
    NODE_STACK_ALIGN_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_STACK,

    /**
     * @brief Defines the scrollbar status. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: scrollbar status. The parameter type is {@link ArkUI_ScrollBarDisplayMode}. The default value is
     * <b>ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO</b> for the <b>List</b>, <b>Grid</b>, and <b>Scroll</b> components, and
     * <b>ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF</b> for the <b>WaterFlow</b> component. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: scrollbar status. The parameter type is {@link ArkUI_ScrollBarDisplayMode}. \n
     *
     */
    NODE_SCROLL_BAR_DISPLAY_MODE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,
    /**
     * @brief Defines the width of the scrollbar. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: width of the scrollbar, in vp. The default value is <b>4</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: width of the scrollbar, in vp. \n
     *
     */
    NODE_SCROLL_BAR_WIDTH,
    /**
     * @brief Defines the color of the scrollbar. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .data[0].u32: color of the scrollbar, in 0xARGB format. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .data[0].u32: color of the scrollbar, in 0xARGB format. \n
     *
     */
    NODE_SCROLL_BAR_COLOR,
    /**
     * @brief Defines the scroll direction. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: scroll direction. The parameter type is {@link ArkUI_ScrollDirection}.
     * The default value is <b>ARKUI_SCROLL_DIRECTION_VERTICAL</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: scroll direction. The parameter type is {@link ArkUI_ScrollDirection}. \n
     *
     */
    NODE_SCROLL_SCROLL_DIRECTION,
    /**
     * @brief Defines the effect used at the edges of the component when the boundary of the scrollable content is
     * reached. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: effect used at the edges of the component when the boundary of the scrollable content is reached.
     * The parameter type is {@link ArkUI_EdgeEffect}. The default value is <b>ARKUI_EDGE_EFFECT_NONE</b>.\n
     * .value[1]?.i32: whether to enable the scroll effect when the component content size is smaller than the
     * component itself. Optional. The value <b>1</b> means to enable the scroll effect, and <b>0</b> means the
     * opposite. The default value for the List/Grid/WaterFlow component is <b>0</b>, and the default value for the
     * Scroll component is <b>1</b>. \n
     * .value[2]?.i32: direction in which the effect takes effect. The parameter type is {@link ArkUI_EffectEdge}.
     * The default value is <b>ARKUI_EFFECT_EDGE_START | ARKUI_EFFECT_EDGE_END</b>. This parameter is supported since
     * API version 16. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: effect used at the edges of the component when the boundary of the scrollable content is reached.
     * The parameter type is {@link ArkUI_EdgeEffect}. \n
     * .value[1].i32: whether to enable the scroll effect when the component content size is smaller than the component
     * itself. Optional. The value <b>1</b> means to enable the scroll effect, and <b>0</b> means the opposite. \n
     * .value[2].i32: edge for which the effect takes effect when the boundary of the scrollable content is reached.
     * The parameter type is {@link ArkUI_EffectEdge}. This parameter is supported since API version 16. \n
     *
     */
    NODE_SCROLL_EDGE_EFFECT,
    /**
     * @brief Defines whether to support scroll gestures. When this attribute is set to <b>false</b>, scrolling by
     * finger or mouse is not supported, but the scroll controller API is not affected.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to support scroll gestures. The default value is <b>true</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to support scroll gestures. \n
     *
     */
    NODE_SCROLL_ENABLE_SCROLL_INTERACTION,
    /**
     * @brief Defines the friction coefficient. It applies only to gestures in the scrolling area, and it affects only
     * indirectly the scroll chaining during the inertial scrolling process.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: friction coefficient. The default value is <b>0.6</b> for non-wearable devices and <b>0.9</b>
     * for wearable devices. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: friction coefficient.
     *
     */
    NODE_SCROLL_FRICTION,
    /**
     * @brief Defines the scroll snapping mode. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: alignment mode for the scroll snap position. The parameter type is {@link ArkUI_ScrollSnapAlign}.
     * The default value is <b>ARKUI_SCROLL_SNAP_ALIGN_NONE</b>.\n
     * .value[1].i32: whether to enable the snap to start feature. When scroll snapping is defined for the
     * <b><Scroll></b> component, setting this attribute to <b>false</b> enables the component to scroll between the
     * start edge and the first snap point. The default value is <b>true</b>. It is valid only when there are multiple
     * snap points.\n
     * .value[2].i32: Whether to enable the snap to end feature. When scroll snapping is defined for the
     * <b><Scroll></b> component, setting this attribute to <b>false</b> enables the component to scroll between the
     * end edge and the last snap point. The default value is <b>true</b>. It is valid only when there are multiple
     * snap points.\n
     * .value[3...].f32: snap points for the <b><Scroll></b> component. Each snap point defines the offset from an
     * edge to which the <b><Scroll></b> component can scroll.  \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: alignment mode for the scroll snap position. The parameter type is {@link ArkUI_ScrollSnapAlign}.\n
     * .value[1].i32: whether to enable the snap to start feature. When scroll snapping is defined for the
     * <b><Scroll></b> component, setting this attribute to <b>false</b> enables the component to scroll between the
     * start edge and the first snap point.\n
     * .value[2].i32: Whether to enable the snap to end feature. When scroll snapping is defined for the
     * <b><Scroll></b> component, setting this attribute to <b>false</b> enables the component to scroll between the
     * end edge and the last snap point.\n
     * .value[3...].f32: snap points for the <b><Scroll></b> component. Each snap point defines the offset from an edge
     * to which the <b><Scroll></b> component can scroll. \n
     *
     */
    NODE_SCROLL_SNAP,

    /**
     * @brief Defines the nested scrolling options. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: nested scrolling option when the component scrolls forward.
     * The parameter type is {@link ArkUI_ScrollNestedMode}. \n
     * .value[1].i32: nested scrolling option when the component scrolls backward.
     * The parameter type is {@link ArkUI_ScrollNestedMode}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: nested scrolling option when the component scrolls forward.
     * The parameter type is {@link ArkUI_ScrollNestedMode}. \n
     * .value[1].i32: nested scrolling option when the component scrolls backward.
     * The parameter type is {@link ArkUI_ScrollNestedMode}.
     *
     */
    NODE_SCROLL_NESTED_SCROLL,
    /**
     * @brief Defines the specified position to scroll to. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: horizontal scrolling offset, in vp. \n
     * .value[1].f32: vertical scrolling offset, in vp. \n
     * .value[2]?.i32: scrolling duration, in milliseconds. Optional. \n
     * .value[3]?.i32: scrolling curve. Optional. The parameter type is {@link ArkUI_AnimationCurve}.
     *                 The default value is <b>ARKUI_CURVE_EASE</b>. \n
     * .value[4]?.i32: whether to enable the default spring animation. Optional.
     *                 The default value <b>0</b> means not to enable the default spring animation. \n
     * .value[5]?.i32: whether to convert the scroll animation to an overshoot animation when the boundary is reached.
     *                 Optional. \n
     * .value[6]?.i32: whether the component can stop at an overscrolled position.
     *                 This parameter is supported since API version 20. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: horizontal scrolling offset, in vp. \n
     * .value[1].f32: vertical scrolling offset, in vp. \n
     *
     */
    NODE_SCROLL_OFFSET,

    /**
     * @brief Defines the edge position to scroll to. This attribute can be set and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: edge position to scroll to. The parameter type is {@link ArkUI_ScrollEdge}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the container at the edge position. The value <b>-1</b> means that the container is not
     * at the edge position. If the container is at the edge position, the parameter type is {@link ArkUI_ScrollEdge}.
     *
     */
    NODE_SCROLL_EDGE,

    /**
     * @brief Defines whether to enable the swipe-to-turn-pages feature. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * If both <b>enablePaging</b> and <b>scrollSnap</b> are set, <b>scrollSnap</b> takes effect, but
     * <b>enablePaging</b> does not. \n
     * \n
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to enable the swipe-to-turn-pages feature. The default value is <b>false</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to enable the swipe-to-turn-pages feature. \n
     *
     */
    NODE_SCROLL_ENABLE_PAGING,

    /**
     * @brief Scroll to the next or previous page.
     * 
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32 Indicates whether to scroll to next page. Value 0 indicates scroll to next page and value 1
     * indicates scroll to previous page. \n
     * .value[1]?.i32 Indicates whether to enable animation. Value 1 indicates enable and 0 indicates disable. \n
     *
     */
    NODE_SCROLL_PAGE,

    /**
     * @brief Scroll a specified distance.
     * List/Scroll/WaterFlow support since API version 12, Grid support since API version 26.0.0.
     * 
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32：Horizontal scrolling distance in vp; \n
     * .value[1].f32: Vertical scrolling distance in vp; \n
     *
     */
    NODE_SCROLL_BY,

    /**
     * @brief Performs inertial scrolling based on the initial velocity passed in.
     * 
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: Initial velocity of inertial scrolling. Unit: vp/s. If the value specified is 0, it is
     * considered as invalid, and the scrolling for this instance will not take effect. If the value is positive,
     * the scroll will move downward; if the value is negative, the scroll will move upward. \n
     *
     * @since 13
     */
    NODE_SCROLL_FLING,

    /**
    * @brief Sets the fading effect for the edges of scrollable components.
    *
    * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:
    * .value[0].i32: whether to enable the fading effect on edges. The value 0 means to disable the fading effect,
    * and 1 means to enable it.
    * .value[1]?.f32: length of the fading effect on edges, in vp. Default value: 32.
    *
    * Format of the return value {@link ArkUI_AttributeItem}:
    * .value[0].i32: whether the fading effect on edges is enabled. The value 0 means that the fading effect is
    * disabled, and 1 means that it is enabled.
    * .value[1].f32: length of the fading effect on edges, in vp.
    *
    * @since 14
    */
    NODE_SCROLL_FADING_EDGE,

    /**
     * @brief Obtains the total size of all child components when fully expanded in the scrollable component.
     *
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: total width of all child components when fully expanded in the scrollable component.
     *                The default unit is vp. \n
     * .value[1].f32: total height of all child components when fully expanded in the scrollable component.
     *                The default unit is vp. \n
     * When <b>NODE_PADDING</b>, <b>NODE_MARGIN</b>, or <b>NODE_BORDER_WIDTH</b> is set, the values are rounded to the
     * nearest pixel when being converted from vp to px.
     * The returned values are calculated based on these rounded pixel values. \n
     *
     * @since 14
     */
    NODE_SCROLL_SIZE,

    /**
     * @brief Sets the offset from the start of the scrollable components content.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: offset from the start of the content, in vp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: offset from the start of the content, in vp. \n
     *
     * @since 15
     */
    NODE_SCROLL_CONTENT_START_OFFSET,

    /**
     * @brief Sets the offset from the end of the scrollable components content.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: offset from the end of the content, in vp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: offset from the end of the content, in vp. \n
     *
     * @since 15
     */
    NODE_SCROLL_CONTENT_END_OFFSET,

    /**
     * @brief Defines the maximum starting fling speed of the scrollable when the fling animation starts.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute: \n
     * .value[0].f32: maximum starting fling speed, Unit: vp/s \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}: \n
     * .value[0].f32: maximum starting fling speed, Unit: vp/s \n
     *
     * @since 18
     */
    NODE_SCROLL_FLING_SPEED_LIMIT = 1002019,

    /**
     * @brief Defines the clip mode of the scrollable.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute: \n
     * .value[0].i32: clip content mode. The parameter type is {@link ArkUI_ContentClipMode}. The default value is
     * <b>ARKUI_CONTENT_CLIP_MODE_BOUNDARY</b> for the <b>Grid</b> and <b>Scroll</b> components, and
     * <b>ARKUI_CONTENT_CLIP_MODE_CONTENT_ONLY</b> for the <b>List</b> and <b>WaterFlow</b> components. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}: \n
     * .value[0].i32: clip content mode, The parameter type is {@link ArkUI_ContentClipMode}. \n
     *
     * @since 18
     */
    NODE_SCROLL_CLIP_CONTENT = 1002020,

    /**
     * @brief Defines whether the scrollable scrolls back to top when status bar is clicked.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute: \n
     * .value[0].i32: whether the scrollable scrolls back to top when status bar is clicked.
     * The value <b>1</b> means to scroll back to top, and <b>0</b> means the opposite. The default value is <b>0</b>
     * for API versions earlier than 18. For API version 18 and later, the default value is <b>0</b> for the
     * horizontal scroll direction and <b>1</b> for the vertical scroll direction. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}: \n
     * .value[0].i32: whether the scrollable scrolls back to top when status bar is clicked. \n
     *
     * @since 15
     */
    NODE_SCROLL_BACK_TO_TOP = 1002021,

    /**
     * @brief Defines the margin of the scrollbar.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: start margin of the scrollbar, in vp. The default value is <b>0</b>. \n
     * .value[1].f32: end margin of the scrollbar, in vp. The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: start margin of the scrollbar, in vp. \n
     * .value[1].f32: end margin of the scrollbar, in vp. \n
     *
     * @since 20
     */
    NODE_SCROLL_BAR_MARGIN = 1002022,

    /**
     * @brief Sets the maximum zoom scale for scrollable content.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: maximum zoom scale to set. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: current maximum zoom scale. \n
     *
     * @since 20
     */
    NODE_SCROLL_MAX_ZOOM_SCALE = 1002023,

    /**
     * @brief Sets the minimum zoom scale for scrollable content.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: minimum zoom scale to set. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: current minimum zoom scale. \n
     *
     * @since 20
     */
    NODE_SCROLL_MIN_ZOOM_SCALE = 1002024,

    /**
     * @brief Sets the zoom scale for scrollable content.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: zoom scale to set. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: current zoom scale. \n
     *
     * @since 20
     */
    NODE_SCROLL_ZOOM_SCALE = 1002025,

    /**
     * @brief Sets whether to enable the zoom bounce effect when the scaling exceeds the limits.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to enable the zoom bounce effect when the scaling exceeds the limits.
     * The value <b>1</b> means to enable the effect, and <b>0</b> means the opposite. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to enable the zoom bounce effect when the scaling exceeds the limits.
     * The value <b>1</b> means to enable the effect, and <b>0</b> means the opposite. \n
     *
     * @since 20
     */
    NODE_SCROLL_ENABLE_BOUNCES_ZOOM = 1002026,

    /**
     * @brief Sets whether dragging scrolling with the left mouse button pressed is supported.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether dragging scrolling with the left mouse button pressed is supported. <b>0</b>: no; <b>1</b>: yes. Default value: <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether dragging scrolling with the left mouse button pressed is supported. <b>0</b>: no; <b>1</b>: yes. \n
     *
     * @since 26.0.0
     */
    NODE_SCROLL_ENABLE_SCROLL_WITH_MOUSE = 1002027,

    /**
     * @brief Sets whether to automatically adjust the margin of the scrollbar to avoid the component's <b>NODE_PADDING</b>, <b>NODE_SCROLL_CONTENT_START_OFFSET</b>, and <b>NODE_SCROLL_CONTENT_END_OFFSET</b> areas.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute\n
     * .value[0].i32: whether to automatically adjust the margin of the scrollbar. <b>0</b>: yes; <b>1</b>: no. Default value: <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to automatically adjust the margin of the scrollbar. <b>0</b>: yes; <b>1</b>: no. \n
     *
     * @since 26.0.0
     */
    NODE_SCROLL_AUTO_ADJUST_MARGIN = 1002028,

    /**
     * @brief Sets the direction in which the list items are arranged.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: direction in which the list items are arranged. The parameter type is {@link ArkUI_Axis}.
     * The default value is <b>ARKUI_AXIS_VERTICAL</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: direction in which the list items are arranged. The parameter type is {@link ArkUI_Axis}. \n
     *
     */
    NODE_LIST_DIRECTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST,
    /**
     * @brief Defines whether to pin the header to the top or the footer to the bottom in the <b><ListItemGroup></b>
     * component. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to pin the header to the top or the footer to the bottom in the <b><ListItemGroup></b>
     * component. It is used together with the <b><ListItemGroup></b> component. The parameter type is
     * {@link ArkUI_StickyStyle}. The default value is <b>ARKUI_STICKY_STYLE_NONE</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to pin the header to the top or the footer to the bottom in the <b><ListItemGroup></b>
     * component. It is used together with the <b><ListItemGroup></b> component. The parameter type is
     * {@link ArkUI_StickyStyle}.
     *
     */
    NODE_LIST_STICKY,
    /**
     * @brief Defines the spacing between list items. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: spacing between list items along the main axis. The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: spacing between list items along the main axis. \n
     *
     */
    NODE_LIST_SPACE,
    /**
    * @brief Defines the list adapter. The attribute can be set, reset, and obtained as required through APIs.
    *
    * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
    * .object: {@link ArkUI_NodeAdapter} object as the adapter. \n
    */
    NODE_LIST_NODE_ADAPTER,

    /**
     * @brief list组件Adapter缓存数量，支持属性设置，属性重置和属性获取接口。 
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：配合List组件Adapter使用，设置adapter中的缓存数量\n
     * .value[1]?.i32：是否显示缓存节点，0：不显示，1：显示，默认值：0。该参数从API version 15开始支持。 \n
     * .value[2]?.i32：设置List最大缓存数量，默认值与第一个参数相同。该参数从API version 22开始支持。 \n
     * \n
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：adapter中的缓存数量。\n
     *  .value[1].i32：是否显示缓存节点，0：不显示，1：显示。该参数从API version 15开始支持。 \n
     * .value[2].i32：List最大缓存数量。该参数从API version 22开始支持。 \n
     *
     */
    NODE_LIST_CACHED_COUNT,

    /**
     * @brief Scroll to the specified index.
     * 
     * When activating the smooth animation, all items passed through will be loaded and layout calculated, which can
     * lead to performance issues when loading a large number of items.\n
     * \n
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32：The index value of the target element to be slid to in the current container.\n
     * .value[1]?.i32：Set whether there is an action when sliding to the index value of a list item in the list, where
     * 1 indicates an action and 0 indicates no action. Default value: 0.\n
     * .value[2]?.i32：Specify the alignment of the sliding element with the current container,The parameter type is
     * {@link ArkUI_ScrollAlignment}, default value is ARKUI_SCROLL_ALIGNMENT_START. \n
     * .value[3]?.f32: extra offset, in vp. The default value is <b>0</b>.
     * This parameter is supported since API version 15. \n
     *
     */
    NODE_LIST_SCROLL_TO_INDEX,
    /**
     * @brief Sets the alignment mode of list items along the cross axis when the cross-axis width of the list is
     * greater than the cross-axis width of list items multiplied by the value of lanes.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: alignment mode of list items along the cross axis.
     * The parameter type is {@link ArkUI_ListItemAlignment}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: alignment mode of list items along the cross axis.
     * The parameter type is {@link ArkUI_ListItemAlignment}. \n
    */
    NODE_LIST_ALIGN_LIST_ITEM,

    /**
     * @brief Set the default spindle size for the List subcomponent.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: The parameter format is {@ ArkUI-ListChildrenMainSize} \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: The parameter format is {@ ArkUI-ListChildrenMainSize} \n
     */
    NODE_LIST_CHILDREN_MAIN_SIZE = 1003007,

    /**
     * @brief Set the index value of the item displayed at the start of the viewport
     * when the current List is first loaded.This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: index value of the item displayed at
     * the start of the viewport when the current List is loaded for the first time. Default value: 0.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: index value of the item displayed at
     * the start of the viewport when the current List is loaded for the first time. Default value: 0.\n
     */
    NODE_LIST_INITIAL_INDEX = 1003008,
    /**
     * @brief sets the ListItem splitter style. By default, there is no splitter.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Attribute setting method parameter {@link ArkUI_AttributeItem} Format: \n
     *.value[0].u32: divider color, type 0xargb; \n
     *.value[1].f32: dividing line width; \n
     *.value[2].f32: the distance between the divider and the beginning of the side of the list, unit vp; \n
     *.value[3].f32: the distance between the divider and the end of the side of the list (unit: vp). \n
     * \n
     * Attribute fetch method return value {@link ArkUI_AttributeItem} format: \n
     *.value[0].u32: divider color, type 0xargb; \n
     *.value[1].f32: dividing line width; \n
     *.value[2].f32: the distance between the divider and the beginning of the side of the list, unit vp; \n
     *.value[3].f32: the distance between the divider and the end of the side of the list (unit: vp). \n
     *
     */
    NODE_LIST_DIVIDER = 1003009,

    /**
     * @brief Scrolls to the item with the specified index in the specified list item group.
     *
     * When <b>smooth</b> is set to <b>true</b>, all passed items are loaded and counted in layout calculation.
     * This may result in performance issues if a large number of items are involved. \n
     * \n
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: index of the target list item group in the current list. \n
     *.value[1].i32: index of the target list item in the list item group. \n
     * .value[2]?.i32: whether to enable the smooth animation for scrolling to the item with the specified index.
     * The value <b>1</b> means to enable the animation, and <b>0</b> means the opposite.
     * The default value is <b>0</b>. \n
     * .value[3]?.i32: how the item to scroll to is aligned with the container. The parameter type is
     * {@link ArkUI_ScrollAlignment}. The default value is <b>ARKUI_SCROLL_ALIGNMENT_START</b>. \n
     *
     * @since 15
     */
    NODE_LIST_SCROLL_TO_INDEX_IN_GROUP = 1003010,

    /**
     * @brief Sets the number of lanes in the list.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: number of lanes in the list. If the maximum and minimum lane widths are set, setting the number
     * of lanes will not take effect. \n
     * .value[1]?.f32: minimum lane width, in vp. \n
     * .value[2]?.f32: maximum column width, in vp. \n
     * .value[3]?.f32: lane spacing, in vp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: number of lanes in the list. \n
     * .value[1].f32: minimum lane width, in vp. \n
     * .value[2].f32: maximum column width, in vp. \n
     * .value[3].f32: lane spacing, in vp. \n \n
     *
     * @since 15
     */
    NODE_LIST_LANES = 1003011,

    /**
     * @brief Sets the list snap alignment mode.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: alignment mode for the list snap position. The parameter type is {@link ArkUI_ScrollSnapAlign}.
     * The default value is <b>ARKUI_SCROLL_SNAP_ALIGN_NONE</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     *.value[0].i32: alignment mode for the list snap position. The parameter type is {@link ArkUI_ScrollSnapAlign}.\n
     *
     * @since 15
     */
    NODE_LIST_SCROLL_SNAP_ALIGN = 1003012,

    /**
     * @brief Sets whether to maintain the visible content's position when data is inserted or deleted outside the
     * display area of the <b>List</b> component.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to maintain the visible content's position when data is inserted or deleted outside the
     * display area of the <b>List</b> component. The value <b>0</b> means not to maintain the visible content's
     * position, and <b>1</b> means the opposite. The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to maintain the visible content's position when data is inserted or deleted outside the
     * display area of the <b>List</b> component. The value <b>0</b> means not to maintain the visible content's
     * position, and <b>1</b> means the opposite. The default value is <b>0</b>. \n
     *
     * @since 15
     */
    NODE_LIST_MAINTAIN_VISIBLE_CONTENT_POSITION = 1003013,

    /**
     * @brief Sets whether the <b>List</b> component starts layout from the end.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the <b>List</b> component starts layout from the end. The value <b>0</b> means layout
     * starts from the top, and <b>1</b> means layout starts from the end. The default value is <b>0</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the <b>List</b> component starts layout from the end. The value <b>0</b> means layout
     * starts from the top, and <b>1</b> means layout starts from the end. The default value is <b>0</b>. \n
     *
     * @since 19
     */
    NODE_LIST_STACK_FROM_END = 1003014,
    
    /**
     * @brief Defines the focus wrap mode for the <b>List</b> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: focus wrap mode of the <b>List</b> component.
     *                The parameter type is {@link ArkUI_FocusWrapMode}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: focus wrap mode of the <b>List</b> component.
     *                The parameter type is {@link ArkUI_FocusWrapMode}. \n
     *
     * @since 20
     */
    NODE_LIST_FOCUS_WRAP_MODE = 1003015,

    /**
     * @brief Defines whether the <b>List</b> component loads child nodes synchronously.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the <b>List</b> component synchronously loads child nodes.
     * The value <b>0</b> means loading by frames, and <b>1</b> means synchronous loading. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the <b>List</b> component synchronously loads child nodes.
     * The value <b>0</b> means loading by frames, and <b>1</b> means synchronous loading. \n
     *
     * @since 20
     */
    NODE_LIST_SYNC_LOAD = 1003016,

    /**
     * @brief Defines the scroll snap animation speed for the <b>List</b> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     *.value[0].i32: scroll snap animation speed for the <b>List</b> component.
     * The parameter type is {@link ArkUI_ScrollSnapAnimationSpeed}.
     * Default value: <b>ARKUI_SCROLL_SNAP_ANIMATION_NORMAL</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     *.value[0].i32: scroll snap animation speed for the <b>List</b> component.
     * The parameter type is {@link ArkUI_ScrollSnapAnimationSpeed}. \n
     *
     * @since 22
     */
    NODE_LIST_SCROLL_SNAP_ANIMATION_SPEED = 1003017,

    /**
     * @brief List组件的响应式列数布局策略，支持属性设置，属性重置和属性获取接口。 
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：

     * .value[0].i32：在不同断点规格下的列数，数据类型{@link ArkUI_ItemFillPolicy}；

     * .value[1]?.f32：列间距，单位vp，默认值：0

     * 

     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：

     * .value[0].i32：在不同断点规格下的列数，数据类型{@link ArkUI_ItemFillPolicy}；

     * .value[1].f32：列间距，单位vp。

     *
     * @since 22
     */
    NODE_LIST_LANES_ITEMFILLPOLICY = 1003018,

    /**
     * @brief <b>List</b>容器是否支持懒加载空分支渲染。
     * 该属性可以通过API根据需要设置、重置和获取。在懒加载模式下启用时，
     * <b>List</b>中的空分支（没有内容的项）将被渲染并设置为宽度0和高度0。
     * 这可能会影响整体布局和滚动行为。这通常用于数据源可能存在间隙或需要维护特定布局位置的场景。
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：懒加载模式下是否支持空分支渲染。
     * <b>0</b>：禁用空分支支持。空分支不会被渲染。<b>1</b>：启用空分支支持。
     * 空分支将被渲染为占位符项。默认值：<b>0</b>.\n
     * \n
     * 属性获取{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].i32：是否启用空分支渲染。<b>0</b>：关闭。<b>1</b>：启用。\n
     *
     * @since 23
     */
    NODE_LIST_SUPPORT_EMPTY_BRANCH_IN_LAZY_LOADING = 1003019,

    /**
     * @brief 设置List组件的返回键行为。支持属性设置、重置、获取接口。
     *
     * {@link ArkUI_AttributeItem}设置属性的参数格式如下：
     * .value[0].i32：单击后退按钮时是否折叠滚动菜单。0：不支持，1：支持。默认值：1。
     *
     * {@link ArkUI_AttributeItem}获取属性的参数格式如下：
     * .value[0].i32：单击返回按钮时是否收起划出菜单。0：不支持，1：支持。
     *
     * @since 26.0.0
     */
    NODE_LIST_BACK_PRESS_BEHAVIOR = 1003020,

    /**
     * @brief List组件是否使能编辑模式。设置为1（可编辑）时，默认显示复选框，
     * 且在编辑模式内支持单指滑动多选。
     * 编辑模式状态变更时，会触发{@link NODE_LIST_ON_EDIT_MODE_CHANGE}事件回调。
     * 状态变更途径有两种：
     * 1. 直接设置本属性。
     * 2. 在{@link NODE_LIST_EDIT_MODE_OPTIONS}启用双指滑动多选且注册了
     * {@link NODE_LIST_ON_EDIT_MODE_CHANGE}回调时，通过双指滑动手势触发。
     * 支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：List组件是否使能编辑模式。0：不可编辑，1：可以编辑。默认值：0
     *
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：List组件是否使能编辑模式。0：不可编辑，1：可以编辑。
     *
     * @since 26.0.0
     */
    NODE_LIST_ENABLE_EDIT_MODE = 1003021,

    /**
     * @brief List组件编辑模式选项配置。
     * 支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：List组件是否使用默认多选样式， 使用默认多选样式时，List进入编辑模式后会显示复选框。
     * 0：不使用默认样式，1：使用默认样式。默认值：1
     * .value[1].i32：List组件是否启用双指滑动多选，该参数在注册{@link NODE_LIST_ON_EDIT_MODE_CHANGE}事件回调后生效。
     * 0：使用双指划动手势不能让List组件进入编辑模式，但通过其他方式进入编辑模式后，编辑模式内的单指滑动多选不受影响。
     * 1：使用双指划动手势能让List组件从非编辑模式进入编辑模式并执行划动多选。默认值：1
     *
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：List组件是否使用默认多选样式。0：不使用默认样式，1：使用默认样式。
     * .value[1].i32：List组件是否启用双指滑动多选。0：不启用，1：启用。
     *
     * @since 26.0.0
     */
    NODE_LIST_EDIT_MODE_OPTIONS = 1003022,

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
    * @brief Swiper组件适配器，支持属性设置，属性重置和属性获取接口。适用场景：当Swiper需要动态加载或复用子组件时使用适配器，如数据量较大的列表轮播、无限循环轮播等场景。
    *
    * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
    * .object：使用{@link ArkUI_NodeAdapter}对象作为适配器。建议配合NODE_SWIPER_CACHED_COUNT使用以提升性能。\n
    * \n
    * 属性获取方法返回值{@link ArkUI_AttributeItem}格式： \n
    * .object：返回值格式为{@link ArkUI_NodeAdapter}。 \n
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

    /**
     * @brief: Set the delineation component of the ListItem, supporting property settings, property resets, and
     * property acquisition interfaces.
     *
     * Attribute setting method parameter {@link ArkUI_AttributeItem} format: \n
     * .object: Construct using the {@link ArkUI_ListitemSwipeActionOption} object. \n
     * \n
     * The return value of the attribute acquisition method {@link ArkUI_AttributeItem} format: \n
     * .object: Construct using the {@link ArkUI_ListitemSwipeActionOption} object. \n
     *
     */
    NODE_LIST_ITEM_SWIPE_ACTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST_ITEM,

    /**
     * @brief Defines the header of the list item group.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: {@link ArkUI_NodeHandle} object to be used as the header of the list item group. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: {@link ArkUI_NodeHandle} object to be used as the header of the list item group. \n
     *
     */
    NODE_LIST_ITEM_GROUP_SET_HEADER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST_ITEM_GROUP,
    /**
     * @brief Defines the footer of the list item group. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: {@link ArkUI_NodeHandle} object to be used as the footer of the list item group. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: {@link ArkUI_NodeHandle} object to be used as the footer of the list item group. \n
     *
     */
    NODE_LIST_ITEM_GROUP_SET_FOOTER,
    /**
     * @brief Defines the style of the divider for the list items. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: color of the divider, in 0xARGB format.\n
     * .value[1].f32: stroke width of the divider, in vp.\n
     * .value[2].f32: distance between the divider and the start of the list, in vp.\n
     * .value[3].f32: distance between the divider and the end of the list, in vp.\n \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: color of the divider, in 0xARGB format.\n
     * .value[1].f32: stroke width of the divider, in vp.\n
     * .value[2].f32: distance between the divider and the start of the list, in vp.\n
     * .value[3].f32: distance between the divider and the end of the list, in vp.\n \n
     *
     */
    NODE_LIST_ITEM_GROUP_SET_DIVIDER,

    /**
     * @brief Set the default spindle size for the ListItem Group subcomponent.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: The parameter format is {@ ArkUI-ListChildrenMainSize} \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: The parameter format is {@ ArkUI-ListChildrenMainSize} \n
     */
    NODE_LIST_ITEM_GROUP_CHILDREN_MAIN_SIZE = 1005003,

    /**
    * @brief Defines the list item group adapter.
    * This attribute can be set, reset, and obtained as required through APIs.
    *
    * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
    * .object: {@link ArkUI_NodeAdapter} object as the adapter. \n
    * \n
    * Format of the return value {@link ArkUI_AttributeItem}:\n
    * .object: {@link ArkUI_NodeAdapter} object. \n
    *
    * @since 15
    */
    NODE_LIST_ITEM_GROUP_NODE_ADAPTER = 1005004,

    /**
     * @brief Defines the horizontal alignment mode of child components in the column.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: horizontal alignment mode of child components.
     * The parameter type is {@link ArkUI_HorizontalAlignment}.\n
     * Default value: <b>ARKUI_HORIZONTAL_ALIGNMENT_CENTER</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: horizontal alignment mode of child components.
     * The parameter type is {@link ArkUI_HorizontalAlignment}. \n
     *
     */
    NODE_COLUMN_ALIGN_ITEMS = MAX_NODE_SCOPE_NUM * ARKUI_NODE_COLUMN,
    /**
     * @brief Defines the vertical alignment mode of child components in the column.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: vertical alignment mode of child components. The parameter type is {@link ArkUI_FlexAlignment}.\n
     * Default value: <b>ARKUI_FLEX_ALIGNMENT_START</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: vertical alignment mode of child components. The parameter type is {@link ArkUI_FlexAlignment}. \n
     *
     */
    NODE_COLUMN_JUSTIFY_CONTENT,

    /**
     * @brief Defines Row constructor options or Column constructor options used for settting the spacing of child components, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: The space of child components, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: The space of child components, in vp.\n
     *
     * @since 23
     */
    NODE_LINEAR_LAYOUT_SPACE,

    /**
     * @brief Defines whether the arrangement of child components along the main axis in a Column or Row is reversed, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The value that determines whether the arrangement of child components along the main axis is reversed.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The value that determines whether the arrangement of child components along the main axis is reversed.\n
     *
     * @since 23
     */
    NODE_LINEAR_LAYOUT_REVERSE,

    /**
     * @brief Defines the vertical alignment mode of child components in the row.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: vertical alignment mode of child components.
     * The parameter type is {@link ArkUI_VerticalAlignment}.\n
     * Default value: <b>ARKUI_VERTICAL_ALIGNMENT_CENTER</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: vertical alignment mode of child components.
     * The parameter type is {@link ArkUI_VerticalAlignment}. \n
     *
     */
    NODE_ROW_ALIGN_ITEMS = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ROW,
    /**
     * @brief Defines the horizontal alignment mode of child components in the row.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: horizontal alignment mode of child components.
     * The parameter type is {@link ArkUI_FlexAlignment}.\n
     * Default value: <b>ARKUI_FLEX_ALIGNMENT_START</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: horizontal alignment mode of child components.
     * The parameter type is {@link ArkUI_FlexAlignment}. \n
     *
     */
    NODE_ROW_JUSTIFY_CONTENT,

    /**
     * @brief Defines the flex attribute. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0]?.i32: direction in which flex items are arranged. The parameter type is {@link ArkUI_FlexDirection}.
     * The default value is <b>ARKUI_FLEX_DIRECTION_ROW</b>.\n
     * .value[1]?.i32: how the flex items are wrapped. The parameter type is {@link ArkUI_FlexWrap}.
     * The default value is <b>ARKUI_FLEX_WRAP_NO_WRAP</b>.\n
     * .value[2]?.i32: alignment mode along the main axis. The parameter type is {@link ArkUI_FlexAlignment}.
     * The default value is <b>ARKUI_FLEX_ALIGNMENT_START</b>.\n
     * .value[3]?.i32: alignment mode along the cross axis. The parameter type is {@link ArkUI_ItemAlignment}.
     * The default value is <b>ARKUI_ITEM_ALIGNMENT_START</b>.\n
     * .value[4]?.i32: alignment mode along the cross axis for multi-line content. The parameter type is
     * {@link ArkUI_FlexAlignment}. The default value is <b>ARKUI_FLEX_ALIGNMENT_START</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: direction in which flex items are arranged. \n
     * .value[1].i32: how the flex items are wrapped. \n
     * .value[2].i32: alignment mode along the main axis. \n
     * .value[3].i32: alignment mode along the cross axis. \n
     * .value[4].i32: alignment mode along the cross axis for multi-line content.\n
     *
     */
    NODE_FLEX_OPTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_FLEX,

    /**
     * @brief Defines Row constructor options used for settting the spacing of child components, which can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: Space on the main axis of the flex container., in vp.\n
     * .value[1].f32: Space on the cross axis of a flex container., in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: Space on the main axis of the flex container., in vp.\n
     * .value[1].f32: Space on the cross axis of a flex container., in vp.\n
     *
     * @since 23
     */
    NODE_FLEX_SPACE,

    /**
     * @brief Sets whether the component is being refreshed.
     * This attribute can be set and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The parameter type is 1 or 0.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: The parameter type is 1 or 0.
     *
     */
    NODE_REFRESH_REFRESHING = MAX_NODE_SCOPE_NUM * ARKUI_NODE_REFRESH,
    /**
     * @brief Sets the custom content in the pull-down area.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: The parameter type is {@Link ArkUI_NodeHandle}.
     *
     */
    NODE_REFRESH_CONTENT,
    /**
     * @brief Set the pull-down hand coefficient.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32：Pull-down hand coefficient, valid value between 0 and 1.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32：Pull-down hand coefficient, valid value between 0 and 1.
     *
     */
    NODE_REFRESH_PULL_DOWN_RATIO = 1009002,
    /**
     * @brief Sets the pull-down offset that initiates a refresh.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: pull-down offset, in vp. The default value is <b>64vp</b>.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: pull-down offset, in vp. The default value is <b>64vp</b>.
     *
     */
    NODE_REFRESH_OFFSET = 1009003,
    /**
     * @brief Sets whether to initiate a refresh when the pull-down distance exceeds the value of <b>refreshOffset</b>.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to initiate a refresh. The value <b>true</b> means to initiate a refresh, and
     * <b>false</b> means the opposite.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether to initiate a refresh. The value <b>1</b> means to initiate a refresh, and
     * <b>0</b> means the opposite.
     *
     */
    NODE_REFRESH_PULL_TO_REFRESH = 1009004,
    /**
     * @brief Sets the maximum pull-down distance for refreshing.
     * This attribute can be set, reset, and obtained through the API as required.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: maximum pull-down distance, in vp.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: maximum pull-down distance, in vp.
     *
     * @since 20
     */
    NODE_REFRESH_MAX_PULL_DOWN_DISTANCE = 1009005,
    /**
     * @brief  设置上划是否取消刷新。支持属性设置，属性重置和属性获取。
     *
     *  属性设置方法{@link ArkUI_AttributeItem}的参数格式：\n
     *  .value[0].i32：上划是否取消刷新。0为上划不取消刷新，1为上划取消刷新。默认值：1。
     *  \n
     *  属性获取方法返回值{@link ArkUI_AttributeItem}的格式：\n
     *  .value[0].i32：上划是否取消刷新。0为上划不取消刷新，1为上划取消刷新。
     *
     * @since 23
     */
    NODE_REFRESH_PULL_UP_TO_CANCEL_REFRESH = 1009006,

    /**
     * @brief Defines the main axis direction of the <b><WaterFlow></b> component layout.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: main axis direction. The parameter type is {@Link ArkUI_FlexDirection}.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: main axis direction. The parameter type is {@Link ArkUI_FlexDirection}.
     *
     */
    NODE_WATER_FLOW_LAYOUT_DIRECTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_WATER_FLOW,

    /**
     * @brief Sets the number of columns in the water flow layout. If this parameter is not set, one column is used
     * by default. This attribute can be set, reset, and obtained as required through APIs.
     * For example, <b>'1fr 1fr 2fr'</b> indicates three columns, with the first column taking up 1/4 of the parent
     * component's full width, the second column 1/4, and the third column 2/4.
     * You can use <b>columnsTemplate('repeat(auto-fill,track-size)')</b> to automatically calculate the number of
     * columns based on the specified column width <b>track-size</b>.
     * <b>repeat</b> and <b>auto-fill</b> are keywords. The units for <b>track-size</b> can be px, vp (default), %,
     * or a valid number.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: number of columns in the layout.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: number of columns in the layout.\n
     *
     */
    NODE_WATER_FLOW_COLUMN_TEMPLATE,

    /**
     * @brief Sets the number of rows in the water flow layout. If this parameter is not set, one row is used
     * by default. This attribute can be set, reset, and obtained as required through APIs.
     * For example, <b>'1fr 1fr 2fr'</b> indicates three rows, with the first row taking up 1/4 of the parent
     * component's full height, the second row 1/4, and the third row 2/4.
     * You can use <b>rowsTemplate('repeat(auto-fill,track-size)')</b> to automatically calculate the number of rows
     * based on the specified row height <b>track-size</b>.
     * <b>repeat</b> and <b>auto-fill</b> are keywords. The units for <b>track-size</b> can be px, vp (default), %,
     * or a valid number.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: number of rows in the layout. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: number of rows in the layout. \n
     *
     */
    NODE_WATER_FLOW_ROW_TEMPLATE,

    /**
     * @brief Sets the gap between columns.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: gap between columns, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: gap between columns, in vp.\n
     *
     */
    NODE_WATER_FLOW_COLUMN_GAP,

    /**
     * @brief Sets the gap between rows.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: gap between lines, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: gap between lines, in vp.\n
     *
     */
    NODE_WATER_FLOW_ROW_GAP,

    /**
     * @brief Defines the water flow section configuration.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: An index calculated from 0 is converted to an integer,
     * indicating that you want to start changing the position of the group.
     * .object: {@ArkUI_WaterFlowSectionOption} object.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .object: {@ArkUI_WaterFlowSectionOption} object.\n
     *
     */
    NODE_WATER_FLOW_SECTION_OPTION,

    /**
    * @brief Defines the water flow adapter. The attribute can be set, reset, and obtained as required through APIs.
    *
    * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
    * .object: {@link ArkUI_NodeAdapter} object as the adapter. \n
    */
    NODE_WATER_FLOW_NODE_ADAPTER,

    /**
    * @brief Sets the number of cached items in the water flow adapter.
    * This attribute can be set, reset, and obtained as required through APIs.
    *
    * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
    * value[0].i32：number of cached items in the water flow adapter. \n
    * .value[1]?.i32：whether to the cached items will be displayed, 0: not displayed, 1: displayed, default value: 0.
    * This parameter is supported since API version 16. \n
    * \n
    * Format of the return value {@link ArkUI_AttributeItem}:\n
    * .value[0].i32: number of cached items in the water flow adapter. \n
    * .value[1].i32: whether to the cached items will be displayed, 0: not displayed, 1: displayed, default value: 0.
    * This parameter is supported since API version 16. \n
    */
    NODE_WATER_FLOW_CACHED_COUNT,

    /**
     * @brief Set the custom display component at the end of the waterfall flow component.
     *
     * Attribute setting method {@link ArkUI_AttributeItem} parameter format: \n
     * .object: Parameter type {@link ArkUI_NodeHandle}.
     *
     */
    NODE_WATER_FLOW_FOOTER,

    /**
     * @brief Scroll to the specified index.
     *
     * When activating the smooth animation, all items passed through will be loaded and layout calculated, which can
     * lead to performance issues when loading a large number of items.\n
     * \n
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: The index value of the target element to be slid to in the current container.\n
     * .value[1].i32: Set whether there is an action when sliding to the index value of a list item in the list, where
     * 1 indicates an action and 0 indicates no action. This parameter is optional, default value is 0.\n
     * .value[2].i32: Specify the alignment of the sliding element with the current container, The parameter type is
     * {@link ArkUI_ScrollAlignment}. This parameter is optional, default value is </b>ARKUI_SCROLL_ALIGNMENT_START</b>. \n
     * .value[3].f32: Extra offset after scrolling to a specified index, in vp. This parameter is optional, the default
     * value is <b>0</b>.
     * If value[3] is positive, it will offset further towards the bottom.
     * If value[3] is negative, it will offset further towards the top.
     * This parameter is supported since API version 23. \n
     *
     */
    NODE_WATER_FLOW_SCROLL_TO_INDEX,

    /**
     * @brief Defines the size constraints to apply to water flow items.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: minimum width, in vp.\n
     * .value[1].f32: maximum width, in vp.\n
     * .value[2].f32: minimum height, in vp.\n
     * .value[3].f32: maximum height, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: minimum width, in vp.\n
     * .value[1].f32: maximum width, in vp.\n
     * .value[2].f32: minimum height, in vp.\n
     * .value[3].f32: maximum height, in vp.\n
     *
     */
    NODE_WATER_FLOW_ITEM_CONSTRAINT_SIZE,

    /**
     * @brief Defines the layout mode of the <b><WaterFlow></b> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: waterflow layout mode. The parameter type is {@Link ArkUI_WaterFlowLayoutMode}.
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: waterflow layout mode. The parameter type is {@Link ArkUI_WaterFlowLayoutMode}.
     * @since 18
     */
    NODE_WATER_FLOW_LAYOUT_MODE,

    /**
     * @brief Defines whether the <b>WaterFlow</b> component loads child nodes synchronously.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the <b>WaterFlow</b> component synchronously loads child nodes.
     * The value <b>0</b> means loading by frames, and <b>1</b> means synchronous loading. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the <b>WaterFlow</b> component synchronously loads child nodes.
     * The value <b>0</b> means loading by frames, and <b>1</b> means synchronous loading. \n
     *
     * @since 20
     */
    NODE_WATER_FLOW_SYNC_LOAD = 1010012,

    /**
     * @brief Specifies the responsive column layout policy for the <b>WaterFlow</b> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: number of columns at different breakpoint specifications.
     * The data type is {@link ArkUI_ItemFillPolicy}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: number of columns at different breakpoint specifications.
     * The data type is {@link ArkUI_ItemFillPolicy}. \n
     *
     * @since 22
     */
    NODE_WATER_FLOW_COLUMN_TEMPLATE_ITEMFILLPOLICY = 1010013,

    /**
     * @brief Specifies whether to support empty branch rendering in lazy loading mode for the <b>WaterFlow</b> container.
     * This attribute can be set, reset, and obtained as required through APIs. When enabled in lazy loading mode, 
     * empty branches (items without content) in the <b>WaterFlow</b> will be rendered and set to width 0 and height 0, 
     * which may affect the overall layout and scrolling behavior. This is typically used in scenarios where the
     * data source may have gaps or when maintaining specific layout positions is required.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to support empty branch rendering in lazy loading mode.
     * <b>0</b>: Disable empty branch support. Empty branches will not be rendered. <b>1</b>: Enable empty branch support. 
     * Empty branches will be rendered as placeholder items. Default value: <b>0</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether empty branch rendering is enabled. <b>0</b>: Disabled. <b>1</b>: Enabled.\n
     *
     * @since 26.0.0
     */
    NODE_WATER_FLOW_SUPPORT_EMPTY_BRANCH_IN_LAZY_LOADING = 1010014,

    /**
     * @brief Set the auxiliary line in the RelativeContaine container, supporting property setting,
     * property reset and property acquisition interfaces.
     *
     * Attribute setting method parameter {@link ArkUI_AttributeItem} format: \n
     * .object: Auxiliary lines within the RelativeContaine container: \n
     *\n
     * Attribute acquisition method return value {@link ArkUI_AttributeItem} format: \n
     * .object: Auxiliary lines within the RelativeContaine container: \n
     *
     */
    NODE_RELATIVE_CONTAINER_GUIDE_LINE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_RELATIVE_CONTAINER,

    /**
     * @brief Sets the barrier within the RelativeContaine container and supports property setting,
     * property reset and property acquisition interfaces.
     *
     * Attribute setting method parameter {@link ArkUI_AttributeItem} format: \n
     * .object: Auxiliary lines within the RelativeContaine container: \n
     *\n
     * Attribute acquisition method return value {@link ArkUI_AttributeItem} format: \n
     * .object: Barrier within the RelativeContaine container: \n
     *
     */
    NODE_RELATIVE_CONTAINER_BARRIER,

    /**
     * @brief Sets the number of columns in the grid layout. If this parameter is not set, one column is used
     * by default. This attribute can be set, reset, and obtained as required through APIs.
     * For example, <b>'1fr 1fr 2fr'</b> indicates three columns, with the first column taking up 1/4 of the parent
     * component's full width, the second column 1/4, and the third column 2/4.
     * You can use <b>columnsTemplate('repeat(auto-fill,track-size)')</b> to automatically calculate the number of
     * columns based on the specified column width <b>track-size</b>.
     * <b>repeat</b> and <b>auto-fill</b> are keywords. The units for <b>track-size</b> can be px, vp (default), %,
     * or a valid number.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: number of columns in the layout.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: number of columns in the layout.\n
     *
     */
    NODE_GRID_COLUMN_TEMPLATE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_GRID,

    /**
     * @brief Sets the number of rows in the grid layout. If this parameter is not set, one row is used
     * by default. This attribute can be set, reset, and obtained as required through APIs.
     * For example, <b>'1fr 1fr 2fr'</b> indicates three rows, with the first row taking up 1/4 of the parent
     * component's full height, the second row 1/4, and the third row 2/4.
     * You can use <b>rowsTemplate('repeat(auto-fill,track-size)')</b> to automatically calculate the number of rows
     * based on the specified row height <b>track-size</b>.
     * <b>repeat</b> and <b>auto-fill</b> are keywords. The units for <b>track-size</b> can be px, vp (default), %,
     * or a valid number.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: number of rows in the layout. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: number of rows in the layout. \n
     *
     */
    NODE_GRID_ROW_TEMPLATE,

    /**
     * @brief Sets the gap between columns. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: gap between columns, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: gap between columns, in vp.\n
     *
     */
    NODE_GRID_COLUMN_GAP,

    /**
     * @brief Sets the gap between rows. This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].f32: gap between lines, in vp.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].f32: gap between lines, in vp.\n
     *
     */
    NODE_GRID_ROW_GAP,

    /**
    * @brief Defines the grid adapter. The attribute can be set, reset, and obtained as required through APIs.
    *
    * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
    * .object: {@link ArkUI_NodeAdapter} object as the adapter. \n
    */
    NODE_GRID_NODE_ADAPTER,

    /**
     * @brief 设置网格适配器中缓存项的数量。
     * 该属性可以通过API根据需要设置、重置和获取。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：网格适配器中缓存的项数。\n
     * .value[1].i32：是否显示缓存节点。0表示不显示，1表示显示。
     * 可选参数，默认值为0。此参数从API版本26.0.0开始支持。\n
     * \n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].i32：网格适配器中缓存的项数。\n
     * .value[1].i32：是否显示缓存节点。0表示不显示，1表示显示。
     * 此参数从API版本26.0.0开始支持。\n
     */
    NODE_GRID_CACHED_COUNT,

    /**
     * @brief Defines the focus wrap mode for the <b>Grid</b> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: focus wrap mode of the <b>Grid</b> component.
     *                The parameter type is {@link ArkUI_FocusWrapMode}. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: focus wrap mode of the <b>Grid</b> component.
     *                The parameter type is {@link ArkUI_FocusWrapMode}. \n
     *
     * @since 20
     */
    NODE_GRID_FOCUS_WRAP_MODE = 1013006,

    /**
     * @brief Defines whether the <b>Grid</b> component loads child nodes synchronously.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether the <b>Grid</b> component synchronously loads child nodes.
     * The value <b>0</b> means loading by frames, and <b>1</b> means synchronous loading. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: whether the <b>Grid</b> component synchronously loads child nodes.
     * The value <b>0</b> means loading by frames, and <b>1</b> means synchronous loading. \n
     *
     * @since 20
     */
    NODE_GRID_SYNC_LOAD = 1013007,

    /**
     * @brief 设置Grid中GridItem的对齐方式，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：Grid中GridItem的对齐方式，参数类型{@link ArkUI_GridItemAlignment}。默认值：GRID_ITEM_ALIGNMENT_DEFAULT。

     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：Grid中GridItem的对齐方式，参数类型{@link ArkUI_GridItemAlignment}。

     *
     * @since 22
     */
    NODE_GRID_ALIGN_ITEMS = 1013008,

    /**
     * @brief 设置Grid布局选项，支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法{@link ArkUI_AttributeItem}参数格式：
     * .object：参数格式为{@link ArkUI_GridLayoutOptions}。
     *
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：
     * .object：返回值格式为{@link ArkUI_GridLayoutOptions}。
     *
     * @since 22
     */
    NODE_GRID_LAYOUT_OPTIONS = 1013009,

    /**
     * @brief Grid组件的响应式列数布局策略，支持属性设置，属性重置和属性获取接口。
     *
     *  属性设置方法参数{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：在不同断点规格下的列数，数据类型{@link ArkUI_ItemFillPolicy}；
     *
     *  属性获取方法返回值{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：在不同断点规格下的列数，数据类型{@link ArkUI_ItemFillPolicy}；
     *
     * @since 22
     */
    NODE_GRID_COLUMN_TEMPLATE_ITEMFILLPOLICY = 1013010,

    /**
     * @brief Grid组件是否进入编辑模式，进入编辑模式可以通过NODE_GRID_ON_ITEM_DRAG_START事件拖拽GridItem。支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：Grid组件是否进入编辑模式。0：不可编辑，1：可以编辑。默认值：0
     *
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：Grid组件是否进入编辑模式。0：不可编辑，1：可以编辑。
     *
     * @since 23
     */
    NODE_GRID_EDIT_MODE = 1013011,

    /**
     * @brief Grid组件是否启用GridItem拖拽动画。支持属性设置，属性重置和属性获取接口。
     * 仅在滚动模式下（只设置rowsTemplate、columnsTemplate其中一个）支持动画。
     * 仅在大小规则的Grid中支持拖拽动画，跨行或跨列场景不支持。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：Grid组件是否启用GridItem拖拽动画。0：不启用，1：启用。默认值：0
     *
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：Grid组件是否启用GridItem拖拽动画。0：不启用，1：启用。
     *
     * @since 23
     */
    NODE_GRID_DRAG_ANIMATION = 1013012,

    /**
     * @brief 指定是否在<b>Grid</b>容器中启用基于鼠标的多选。这个属性可以通过API根据需要设置、重置和获取。
     * 启用后在Grid范围内鼠标框选会触发GridItem的NODE_GRID_ITEM_EVENT_ON_SELECT事件。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：是否启用鼠标多选。
     * <b>0</b>：关闭鼠标多选功能。<b>1</b>：启用基于鼠标的多选。默认值：
     * <b>0</b>.\n \n返回值{@link ArkUI_AttributeItem}格式：\n .value[0].i32是否启用
     * 基于鼠标的多选。<b>0</b>：关闭鼠标多选功能。<b>1</b>：启用基于鼠标的
     * 多选.\n
     *
     * @since 23
     */
    NODE_GRID_MULTI_SELECTABLE = 1013013,

    /**
     * @brief 滑动到指定index。
     *
     * 开启动效时，会对经过的所有子组件进行加载和布局计算，当大量加载子组件时会导致性能问题。\n
     * \n
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：要滑动到的目标元素在当前容器中的索引值。\n
     * .value[1].i32：设置滑动到目标元素时是否有动效，1表示有动效，0表示没有动效。该参数是可选的，默认值：0。\n
     * .value[2].i32：指定滑动到的目标元素与当前容器的对齐方式，参数类型{@link ArkUI_ScrollAlignment}, 该参数是可选的，默认值：ARKUI_SCROLL_ALIGNMENT_AUTO。\n
     * .value[3].f32：滑动到目标元素后的额外偏移量，该参数是可选的，默认值：0，单位：vp。如果值为正数，则向底部额外偏移；如果值为负数，则向顶部额外偏移。\n
     *
     * @since 23
     */
    NODE_GRID_SCROLL_TO_INDEX = 1013014,

    /**
     * @brief <b>Grid</b>容器是否支持懒加载空分支渲染。
     * 该属性可以通过API根据需要设置、重置和获取。在懒加载模式下启用时，
     * <b>Grid</b>中的空分支（没有内容的项）将被渲染并设置为宽度0和高度0。
     * 这可能会影响整体布局和滚动行为。这通常用于数据源可能存在间隙或需要维护特定布局位置的场景。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：懒加载模式下是否支持空分支渲染。
     * <b>0</b>：禁用空分支支持。空分支不会被渲染。<b>1</b>：启用空分支支持。
     * 空分支将被渲染为占位符项。默认值：<b>0</b>.\n
     * \n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].i32：是否启用空分支渲染。<b>0</b>：关闭。<b>1</b>：启用。\n
     *
     * @since 23
     */
    NODE_GRID_SUPPORT_EMPTY_BRANCH_IN_LAZY_LOADING = 1013015,

    /**
     * @brief Grid组件是否使能编辑模式。设置为1（可编辑）时，默认显示复选框，
     * 且在编辑模式内支持单指滑动多选。
     * 该属性为编辑模式的主开关，其他编辑相关属性（如{@link NODE_GRID_EDIT_MODE_OPTIONS}）
     * 仅在本属性为1时生效。
     * 编辑模式状态变更时，会触发{@link NODE_GRID_ON_EDIT_MODE_CHANGE}事件回调。
     * 状态变更途径有两种：
     * 1. 直接设置本属性。
     * 2. 在{@link NODE_GRID_EDIT_MODE_OPTIONS}启用双指滑动多选且注册了
     * {@link NODE_GRID_ON_EDIT_MODE_CHANGE}回调时，通过双指滑动手势触发。
     * 支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：Grid组件是否使能编辑模式。0：不可编辑，1：可以编辑。默认值：0
     *
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：Grid组件是否使能编辑模式。0：不可编辑，1：可以编辑。
     *
     * @since 26.0.0
     */
    NODE_GRID_ENABLE_EDIT_MODE = 1013016,

    /**
     * @brief Grid组件编辑模式选项配置。
     * 支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：Grid组件是否使用默认多选样式， 使用默认多选样式时，Grid进入编辑模式后会显示复选框。
     * 0：不使用默认样式，1：使用默认样式。默认值：1
     * .value[1].i32：Grid组件是否启用双指滑动多选，该参数在注册{@link NODE_GRID_ON_EDIT_MODE_CHANGE}事件回调后生效。
     * 0：使用双指划动手势不能让Grid组件进入编辑模式，但通过其他方式进入编辑模式后，编辑模式内的单指滑动多选不受影响。
     * 1：使用双指划动手势能让Grid组件从非编辑模式进入编辑模式并执行划动多选。默认值：1
     *
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：Grid组件是否使用默认多选样式。0：不使用默认样式，1：使用默认样式。
     * .value[1].i32：Grid组件是否启用双指滑动多选。0：不启用，1：启用。
     *
     * @since 26.0.0
     */
    NODE_GRID_EDIT_MODE_OPTIONS = 1013017,

    /**
     * @brief Sets the style of the <b>GridItem</b> component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute: \n
     * .value[0].i32: style of the <b>GridItem</b> component, specified using {@link ArkUI_GridItemStyle}. \n
     * The default value is <b>GRID_ITEM_STYLE_NONE</b>. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].i32: style of the <b>GridItem</b> component, specified using {@link ArkUI_GridItemStyle}. \n
     *
     * @since 22
     */
    NODE_GRID_ITEM_STYLE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_GRID_ITEM,

    /**
     * @brief 设置GridItem是否可以被鼠标框选。支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：GridItem是否可以被鼠标框选。0：不可以，1：可以。默认值：1
     *
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：
     * .value[0].i32：GridItem是否可以被鼠标框选。0：不可以，1：可以。

     *
     * @since 23
     */
    NODE_GRID_ITEM_SELECTABLE = 1014001,

    /**
     * @brief 设置GridItem选中状态。支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：

     * .value[0].i32：GridItem选中状态。0：未选中，1：已选中。默认值：0

     * 

     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：

     * .value[0].i32：GridItem选中状态。0：未选中，1：已选中。

     *
     * @since 23
     */
    NODE_GRID_ITEM_SELECTED = 1014002,

    /**
    * @brief Defines the column width of the text picker.
    * This attribute can be set, reset, and obtained as required through APIs.
    *
    * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
    * .value[0].f32: percentage of total width. The default value is that all colulmns are equal width.\n
    * .value[1]?.f32: percentage of total width. The default value is that all colulmns are equal width.\n
    * .value[2]?.f32: percentage of total width. The default value is that all colulmns are equal width.\n
    * ...\n
    * .value[n]?.f32: percentage of total width. The default value is that all colulmns are equal width.\n
    * \n
    * Format of the return value {@link ArkUI_AttributeItem}:\n
    * value[0].f32: percentage of total width.\n
    * value[1].f32: percentage of total width.\n
    * value[2].f32: percentage of total width.\n
    * ...\n
    * value[n].f32: percentage of total width.\n
    *
    * @since 18
    */
    NODE_TEXT_PICKER_COLUMN_WIDTHS = 15009,
    /**
     * @brief Defines the disabled date range of the calendar picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .string: A string of dates. The `1st start date`,`1st end date`,`2nd start date`,`2nd end date`,
     * ...,`nth start date`,`nth end date` of the disabled date range.\n
     *  Example: 1910-01-01,1910-12-31,2020-01-01,2020-12-31\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .string: A string of dates.\n
     *
     * @since 19
     */
    NODE_CALENDAR_PICKER_DISABLED_DATE_RANGE = 16006,

    /**
     * @brief Defines whether the calendar picker marks today.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * value[0].i32: whether the calendar picker marks today. The default value is <b>false</b>.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].i32: whether the calendar picker marks today.\n
     *
     * @since 19
     */
    NODE_CALENDAR_PICKER_MARK_TODAY = 16007,

    /**
     * @brief Defines the want used to start EmbeddedAbility.
     * This attribute can be set as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: The want of EmbeddedComponent, with parameter type {@AbilityBase_Want}.
     * The default value is <b>nullptr</b>.\n
     *
     * @since 20
     */
    NODE_EMBEDDED_COMPONENT_WANT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_EMBEDDED_COMPONENT,

    /**
     * @brief Set onError and onTerminated callbacks for EMBEDDED_COMPONENT.
     * This attribute can be set as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .object: The option for EmbeddedComponent, with parameter type {@ArkUI_EmbeddedComponentOption}.\n
     *
     * @since 20
     */
    NODE_EMBEDDED_COMPONENT_OPTION,

    /**
     * @brief Defines the index of the default selected item in the data selection range of the picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].u32: index. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * .value[0].u32: index. \n
     *
     * @since 23
     */
    NODE_PICKER_OPTION_SELECTED_INDEX = MAX_NODE_SCOPE_NUM * ARKUI_NODE_PICKER,
    /**
     * @brief Defines whether haptic feedback.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to feedback. The value <b>true</b> means to feedback, and
     * <b>false</b> means the opposite.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].i32: whether to feedback.\n
     *
     * @since 23
     */
    NODE_PICKER_ENABLE_HAPTIC_FEEDBACK = 1018001,
    /**
     * @brief Defines whether to support scroll looping for the picker.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:\n
     * .value[0].i32: whether to support scroll looping. The value <b>true</b> means to support scroll looping, and
     * <b>false</b> means the opposite.\n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}:\n
     * value[0].i32: The value <b>1</b> means to support scroll looping, and <b>0</b> means the opposite. \n
     *
     * @since 23
     */
    NODE_PICKER_CAN_LOOP = 1018002,
    /**
     * @brief Sets the type and parameters of the selection indicator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Attribute setting method parameter {@link ArkUI_AttributeItem} Format: \n
     * .object: Parameter type {@link ArkUI_PickerIndicatorStyle}.
     * \n
     * Attribute fetch method return value {@link ArkUI_AttributeItem} format: \n
     * .object: Parameter type {@link ArkUI_PickerIndicatorStyle}.
     *
     * @since 23
     */
    NODE_PICKER_SELECTION_INDICATOR = 1018003,

    /**
     * @brief Sets the total number of visible items.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute: \n
     * .value[0].i32: number of visible items. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}: \n
     * .value[0].i32: number of visible items. \n
     *
     * @since 26.0.0
     */
    NODE_PICKER_DISPLAYED_ITEM_COUNT = 1018004,

    /**
     * @brief Sets the height of each item.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute: \n
     * .value[0].f32: the height of each item, in vp. \n
     * \n
     * Format of the return value {@link ArkUI_AttributeItem}: \n
     * .value[0].f32: the height of each item, in vp. \n
     *
     * @since 26.0.0
     */
    NODE_PICKER_ITEM_HEIGHT = 1018005,
} ArkUI_NodeAttributeType;

/**
 * @brief Define component event max args size.
 *
 * @since 12
 */
#define MAX_COMPONENT_EVENT_ARG_NUM 12
/**
 * @brief Defines the parameter type of the component callback event.
 *
 * @since 12
 */
typedef struct {
    /** Data array object. */
    ArkUI_NumberValue data[MAX_COMPONENT_EVENT_ARG_NUM];
} ArkUI_NodeComponentEvent;

/**
 * @brief Defines the string type parameter used by the component callback event.
 *
 * @since 12
 */
typedef struct {
    /** String. */
    const char* pStr;
} ArkUI_StringAsyncEvent;

/**
 * @brief Defines a hybrid data structure for component events.
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
 * @brief 定义TextEditor组件文本内容变化事件的结构体。
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
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is {@link ArkUI_UIInputEvent}.
     */
    NODE_TOUCH_EVENT = 0,

    /**
     * @brief Defines the mount event.
     *
     * This event is triggered when the component is mounted and displayed. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     */
    NODE_EVENT_ON_APPEAR,
    /**
     * @brief Defines the unmount event.
     *
     * This event is triggered when the component is unmounted and hidden. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     */
    NODE_EVENT_ON_DISAPPEAR,

    /**
     * @brief Defines the area change event.
     *
     * This event is triggered when the component's size, position, or any other attribute that may
     * affect its display area changes. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     *  {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains 12 parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: original width of the target element, in vp.
     * The value type is number. \n
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: original height of the target element, in vp.
     * The value type is number. \n
     * <b>ArkUI_NodeComponentEvent.data[2].f32</b>: original X coordinate of the target element's upper left corner
     * relative to the parent element's, in vp. The value type is number. \n
     * <b>ArkUI_NodeComponentEvent.data[3].f32</b>: original Y coordinate of the target element's upper left corner
     * relative to the parent element's, in vp. The value type is number. \n
     * <b>ArkUI_NodeComponentEvent.data[4].f32</b>: original X coordinate of the target element's upper left corner
     * relative to the page's, in vp. The value type is number. \n
     * <b>ArkUI_NodeComponentEvent.data[5].f32</b>: original Y coordinate of the target element's upper left corner
     * relative to the page's, in vp. The value type is number. \n
     * <b>ArkUI_NodeComponentEvent.data[6].f32</b>: new width of the target element, in vp. The value is a number. \n
     * <b>ArkUI_NodeComponentEvent.data[7].f32</b>: new height of the target element, in vp. The value is a number. \n
     * <b>ArkUI_NodeComponentEvent.data[8].f32</b>: new X coordinate of the target element's upper left corner relative
     * to the parent element's, in vp. The value type is number. \n
     * <b>ArkUI_NodeComponentEvent.data[9].f32</b>: new Y coordinate of the target element's upper left corner relative
     * to the parent element's, in vp. The value type is number. \n
     * <b>ArkUI_NodeComponentEvent.data[10].f32</b>: new X coordinate of the target element's upper left corner relative
     * to the page's, in vp. The value type is number. \n
     * <b>ArkUI_NodeComponentEvent.data[11].f32</b>: new Y coordinate of the target element's upper left corner relative
     * to the page's, in vp. The value type is number. \n
     */
    NODE_EVENT_ON_AREA_CHANGE,
    /**
     * @brief Defines the focus event.
     *
     * This event is triggered when the component obtains the focus. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     */
    NODE_ON_FOCUS,
    /**
     * @brief Defines the blur event.
     *
     * This event is triggered when the component loses the focus. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     */
    NODE_ON_BLUR,
    /**
     * @brief Defines the click event.
     *
     * This event is triggered when the component is clicked. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains 12 parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: X coordinate of the click relative to the upper left corner of the
     * clicked component's original area, in vp. \n
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: Y coordinate of the click relative to the upper left corner of the
     * clicked component's original area, in vp. \n
     * <b>ArkUI_NodeComponentEvent.data[2].f32</b>: event timestamp. It is the interval between the time when the event
     * is triggered and the time when the system starts, in microseconds. \n
     * <b>ArkUI_NodeComponentEvent.data[3].i32</b>: event input device. The value <b>1</b> indicates the mouse,
     * <b>2</b> indicates the touchscreen, and <b>4</b> indicates the key. \n
     * <b>ArkUI_NodeComponentEvent.data[4].f32</b>: X coordinate of the click relative to the upper left corner of the
     * application window, in vp. \n
     * <b>ArkUI_NodeComponentEvent.data[5].f32</b>: Y coordinate of the click relative to the upper left corner of the
     * application window, in vp. \n
     * <b>ArkUI_NodeComponentEvent.data[6].f32</b>: X coordinate of the click relative to the upper left corner of the
     * application screen, in vp. \n
     * <b>ArkUI_NodeComponentEvent.data[7].f32</b>: Y coordinate of the click relative to the upper left corner of the
     * application screen, in vp. \n
     */
    NODE_ON_CLICK,
    /**
     * @brief Defines event interception.
     *
     * This event is triggered when the component is touched. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}. \n
     */
    NODE_ON_TOUCH_INTERCEPT,
    /**
     * @brief Defines the visible area change event.
     *
     * This event is triggered when the ratio of the component's visible area to its total area is greater than or less
     * than the threshold.
     * Before registering this event, you must set <b>NODE_VISIBLE_AREA_CHANGE_RATIO</b>. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: how the ratio of the component's visible area to its total area
     * changes compared to the previous one. The value <b>1</b> indicates an increase, and <b>0</b> indicates a
     * decrease. \n
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: ratio of the component's visible area to its total area when this
     * callback is invoked. \n
     */
    NODE_EVENT_ON_VISIBLE_AREA_CHANGE,
    /**
     * @brief Defines the event triggered when the mouse pointer is moved over or away from the component.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: whether the mouse pointer is hovered over the component.
     * The value <b>1</b> indicates that the mouse pointer is hovered over the component, and <b>0</b> indicates that
     * the mouse pointer is moved away from the component. \n
     */
    NODE_ON_HOVER,
    /**
     * @brief Defines the click event.
     *
     * This event is triggered when the component is clicked by a mouse device button or when the mouse pointer moves
     * within the component. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}. \n
     */
    NODE_ON_MOUSE,
    /**
     * @brief Defines the attach event.
     *
     * This event is triggered when the component is attached. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     */
    NODE_EVENT_ON_ATTACH,
    /**
     * @brief Defines the detach event.
     *
     * This event is triggered when the component is detached. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     */
    NODE_EVENT_ON_DETACH,

    /**
     * @brief Defines the accessibility action event.
     *
     * This event is triggered when The accessibility operation type has been set and
     * corresponding operations have been carried out. \n
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
     * This event is triggered when a drag operation is about to start on a draggable item. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: corresponds to {@link ArkUI_PreDragStatus}. \n
     */
    NODE_ON_PRE_DRAG = 14,
    /**
     * @brief Called when the user starts to drag an ite
     *
     * A drag operation is recognized only when the dragged item is moved far enough. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     */
    NODE_ON_DRAG_START = 15,
    /**
     * @brief Called when a dragged item enters the boundaries of the current component.
     *
     * The current component refers to the component that listens for this event. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     */
    NODE_ON_DRAG_ENTER = 16,
    /**
     * @brief Called  when a dragged item moves in the current component.
     *
     * The current component refers to the component that listens for this event. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     */
    NODE_ON_DRAG_MOVE = 17,
    /**
     * @brief Called when a dragged item leaves the boundaries of the current component.
     *
     * The current component refers to the component that listens for this event. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     */
    NODE_ON_DRAG_LEAVE = 18,
    /**
     * @brief Called when a dragged item is dropped on the current component.
     * The component can obtain the drag data for processing through the callback.
     *
     * The current component refers to the component that listens for this event. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     */
    NODE_ON_DROP = 19,
    /**
     * @brief Called when a drag operation ends.
     * The drag source can obtain the drag result by registering this callback.
     *
     * A drag operation ends when the dragged item is released.
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     */
    NODE_ON_DRAG_END = 20,
    /**
     * @brief Defines the event triggered when a key event occurs.
     *
     * The callback can be triggered during interactions with a focused window using an external keyboard or other input
     * device. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * 
     * @since 14
     */
    NODE_ON_KEY_EVENT = 21,
    /**
     * @brief Defines the event triggered before the input method responds to the key action.
     *
     * If the return value of this callback is <b>true</b>, it is considered that the key event has been consumed, and
     * subsequent event callbacks (<b>keyboardShortcut</b>, input method events, <b>onKeyEvent</b>) will be intercepted
     * and no longer triggered.
     * The callback can be triggered during interactions with a focused window using an external keyboard or other input
     * device. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * 
     * @since 14
     */
    NODE_ON_KEY_PRE_IME = 22,
    /**
     * @brief Defines the event triggered when the bound component receives a focus axis event after gaining focus.
     *
     * The event callback is triggered by interactions with a joystick and a focused component. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}. \n
     * 
     * @since 15
     */
    NODE_ON_FOCUS_AXIS = 23,

    /**
     * @brief Dispatch key event on the component node.
     *
     * When the component node receives a key event, this callback will be triggered instead of dispatching event to its
     * children. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
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
     * @since 17
     */
    NODE_ON_AXIS = 25,

    /**
     * @brief Defines the event triggered when the bound component is clicked.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}.  \n
     *
     * @since 18
     */
    NODE_ON_CLICK_EVENT = 26,

    /**
     * @brief 定义鼠标指针移至组件上方或远离组件时触发的事件。 \n
     * 当鼠标指针移到组件上方或远离组件时触发该事件。 \n
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合类型为{@link ArkUI_UIInputEvent}。 \n
     *
     * @since 17
     */
    NODE_ON_HOVER_EVENT = 27,

    /**
     * @brief Sets the callback for the NODE_EVENT_ON_VISIBLE_AREA_CHANGE event, which limits the callback interval.
     *
     * The callback is triggered when the ratio of the component's visible area to its total area is greater than or
     * less than the threshold. Before registering the callback, you must configure the threshold and update interval
     * using <b>NODE_VISIBLE_AREA_APPROXIMATE_CHANGE_RATIO</b>. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: how the ratio of the component's visible area to its total area
     * changes compared to the previous one. The value <b>1</b> indicates an increase, and <b>0</b> indicates
     * a decrease. \n
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: ratio of the component's visible area to its total area
     * when this callback is invoked. \n
     *
     * @since 17
     */
    NODE_VISIBLE_AREA_APPROXIMATE_CHANGE_EVENT = 28,

    /**
     * @brief Defines the hover event.
     * 
     * The event is triggered when the pointer is hovered by a pen device.
     * within the component. \n
     * When the event callback occurs, the {@link ArkUI_NodeEvent} object can be obtained from the
     * {@link ArkUI_UIInputEvent} object. \n
     * @since 15
    */
    NODE_ON_HOVER_MOVE = 29,

    /**
     * @brief Defines the size change event.
     *
     * The event will be triggered when the component size changes.
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. 
     * {@link ArkUI_NodeComponentEvent} contains four parameters:
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: the width of the old rectangle.
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: the height of the old rectangle.
     * <b>ArkUI_NodeComponentEvent.data[2].f32</b>: the width of the new rectangle.
     * <b>ArkUI_NodeComponentEvent.data[3].f32</b>: the height of the new rectangle.
     * @since 21
     */
    NODE_ON_SIZE_CHANGE = 30,

    /**
     * @brief Defines the coasting axis event.
     *
     * The event is triggered when user swipes with two fingers on the touchpad, the system constructs
     * sliding events based on the speed at the moment the fingers are lifted, according to a certain
     * decay curve. You can listen for such events to handle the flick effect immediately after the
     * regular axis events. \n
     * When the event callback occurs, the {@link ArkUI_UIInputEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object through {@link OH_ArkUI_NodeEvent_GetInputEvent}.
     * And the {@link ArkUI_CoastingAxisEvent} object can be obtained from the {@link ArkUI_UIInputEvent}
     * object through {@link OH_ArkUI_UIInputEvent_GetCoastingAxisEvent}. \n
     *
     * @since 22
     */
    NODE_ON_COASTING_AXIS_EVENT = 31,

    /**
     * @brief Defines the pre-touch test of sub component in touch events. Called to specify how to perform the touch test on the children of this component.
     * 
     * The event is triggered when the component is touched. \n
     * When the event callback occurs, the {@link ArkUI_NodeEvent} object can be obtained from the
     * {@link ArkUI_TouchTestInfo} object. \n
     * @since 22
    */
    NODE_ON_CHILD_TOUCH_TEST = 32,

    /**
     * @brief Defines the crown event.
     * This event is triggered when the crown is rotated. \n
     * When the event callback occurs, the {@link ArkUI_UIInputEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     * @since 24
    */
    NODE_ON_DIGITAL_CROWN = 33,

    /**
     * @brief Defines the event is triggered when the <b>ARKUI_NODE_CUSTOM</b> content is scrolled.
     * 
     * The event is triggered when the component's content is scrolled. \n
     * When the event callback occurs, the {@link ArkUI_NodeEvent} object can be obtained from the
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameters:\n
     * ArkUI_NodeComponentEvent.data[0].i32: id of scrolling child component. \n
     * ArkUI_NodeComponentEvent.data[1].f32: offset of the frame scrolling, measured in px. \n
     * @since 24
    */
    NODE_ON_CUSTOM_OVERFLOW_SCROLL = 34,

    /**
     * @brief Defines the event is triggered when the <b>ARKUI_NODE_STACK</b> content is scrolled.
     * 
     * The event is triggered when the component's content is scrolled. \n
     * When the event callback occurs, the {@link ArkUI_NodeEvent} object can be obtained from the
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameters:\n
     * ArkUI_NodeComponentEvent.data[0].i32: id of scrolling child component. \n
     * ArkUI_NodeComponentEvent.data[1].f32: offset of the frame scrolling, measured in px. \n
     * @since 24
    */
    NODE_ON_STACK_OVERFLOW_SCROLL = 35,

    /**
     * @brief Defines the event triggered when the component is focused and need to decide whether softkeyboard is needed.
     *
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
     * {@link ArkUI_StringAsyncEvent}contains 1 parameter\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>：Indicates the result of text recognition, in Json format.\n
     *
     */
    NODE_TEXT_ON_DETECT_RESULT_UPDATE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT,
    /**
     * @brief Defines the long press event for span.
     *
     * The event is triggered when the span is long pressed.
     * When the event callback occurs, the {@link ArkUI_NodeEvent} object can be obtained from the
     * {@link ArkUI_UIInputEvent} object. \n
     * @since 20
     */
    NODE_TEXT_SPAN_ON_LONG_PRESS = 1001,
    /**
     * @brief 定义文本选择位置改变时触发的事件。
     * \n
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合体类型为
     * {@link ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}包含两个参数：\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：文本选择区域的起始位置。\n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>：文本选择区域的结束位置。
     *
     * @since 26.0.0
     */
    NODE_TEXT_ON_TEXT_SELECTION_CHANGE = 1002,

    /**
     * @brief Defines the event triggered when the copy button on the pasteboard, which displays when the text box
     * is long pressed, is clicked.
     * \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: text that is copied.
     *
     * @since 26.0.0
     */
    NODE_TEXT_ON_COPY = 1003,

    /**
     * @brief Defines the event triggered before copying text.
     * \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: text that is copied.
     * @return Whether the copy is allowed. \n
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * value.i32 at index 0 in the return value indicates whether the copy is allowed.
     * <b>0</b>: not allowed. <b>1</b>: allowed. \n
     *
     * @since 26.0.0
     */
    NODE_TEXT_ON_WILL_COPY = 1004,

    /**
     * @brief Defines the image loading success event.
     *
     * This event is triggered when an image is successfully loaded or decoded. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains nine parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: loading status. The value <b>0</b> indicates that the image is
     * loaded successfully, and the value <b>1</b> indicates that the image is decoded successfully. \n
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: width of the image, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[2].f32</b>: height of the image, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[3].f32</b>: width of the component, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[4].f32</b>: height of the component, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[5].f32</b>: offset of the rendered content relative to the component on the
     * x-axis, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[6].f32</b>: offset of the rendered content relative to the component on the
     * y-axis, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[7].f32</b>: actual rendered width of the image, in px. \n
     * <b>ArkUI_NodeComponentEvent.data[8].f32</b>: actual rendered height of the image, in px. \n
     */
    NODE_IMAGE_ON_COMPLETE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE,
    /**
     * @brief Defines the image loading failure event.
     *
     * This event is triggered when an error occurs during image loading. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>error code:\n
     * 401: The image could not be obtained because the image path is invalid. \n
     * 103101: The image format is not supported. \n
     */
    NODE_IMAGE_ON_ERROR,
    /**
     * @brief Defines the SVG animation playback completion event.
     *
     * This event is triggered when the animation playback in the loaded SVG image is complete. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     */
    NODE_IMAGE_ON_SVG_PLAY_FINISH,
    /**
     * @brief Defines image download process event.
     *
     * This event is triggered when downloading webpage images from page components.\n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0].u32</b>: the num of bytes downloaded. \n
     * <b>ArkUI_NodeComponentEvent.data[1].u32</b>: the total number of bytes to download. \n
     */
    NODE_IMAGE_ON_DOWNLOAD_PROGRESS,
    /**
     * @brief Defines the event triggered when the toggle status changes.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter: \n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: toggle status. <b>1</b>: on; <b>0</b>: off.
     *
     */
    NODE_TOGGLE_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TOGGLE,
    /**
     * @brief Defines the event triggered when the text input content changes.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: text input.
     *
     */
    NODE_TEXT_INPUT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,
    /**
     * @brief Defines the event triggered when the Enter key of the text input method is pressed.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: Enter key type of the input method.
     *
     */
    NODE_TEXT_INPUT_ON_SUBMIT,
    /**
     * @brief Defines the event triggered when the cut button on the pasteboard, which displays when the text box
     * is long pressed, is clicked.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: text that is cut.
     *
     */
    NODE_TEXT_INPUT_ON_CUT,
    /**
     * @brief Defines the event triggered when the paste button on the pasteboard, which displays when the text box
     * is long pressed, is clicked.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: text that is pasted
     * \n
     * Since 26.0.0, the callback can return whether the paste is allowed.\n
     * @return Whether the paste is allowed. \n
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * value.i32 at index 0 in the return value indicates whether the paste is allowed. \n
     * <b>0</b>: not allowed. <b>1</b>: allowed. \n
     *
     */
    NODE_TEXT_INPUT_ON_PASTE,
    /**
     * @brief Defines the event triggered when the text selection position changes.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: start position of the text selection area. \n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: end position of the text selection area. \n
     *
     */
    NODE_TEXT_INPUT_ON_TEXT_SELECTION_CHANGE,

    /**
     * @brief Defines the event triggered when the input status changes.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: <b>true</b> indicates that text input is in progress. \n
     *
     */
    NODE_TEXT_INPUT_ON_EDIT_CHANGE,

    /**
      * @brief textInput This event is triggered when the input content changes.
      *
      * Conditions for triggering this event: When the input content changes. \n
      * When the event callback occurs, the union type in the event parameter
      * {@link ArkUI_NodeEvent} object is {@link ArkUI_NodeComponentEvent}. \n
      * {@link ArkUI_NodeComponentEvent} contains 2 parameters:\n
      * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: Indicates the width of the text. \n
      * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: Indicates the height of the text. \n
      *
      */
    NODE_TEXT_INPUT_ON_CONTENT_SIZE_CHANGE,

    /**
     * @brief Defines the event triggered when matching with the regular expression specified by
     * <b>NODE_TEXT_INPUT_INPUT_FILTER</b> fails.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: content that is filtered out when regular expression matching fails. \n
     *
     */
    NODE_TEXT_INPUT_ON_INPUT_FILTER_ERROR,

    /**
     * @brief This callback is triggered when the text content is scrolled.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: Indicates the horizontal offset of the text in the content area. \n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: Indicates the vertical coordinate offset of \n
     * the text in the content area. \n
     *
     */
    NODE_TEXT_INPUT_ON_CONTENT_SCROLL,

    /**
     * @brief 定义在将要输入时，触发回调的枚举值。
     *
     * 事件回调发生时，事件参数为{@link ArkUI_NodeEvent}。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetNumberValue}获取到index为0的value.f32：插入的值的位置信息。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetStringValue}获取到index为0的buffer字符串：插入的值。
     * @return 在返回true时，表示正常插入，返回false时，表示不插入。
     * 可通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}设置返回值。\n
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ON_WILL_INSERT = 7009,

    /**
     * @brief 定义在输入完成时，触发回调的枚举值。
     *
     * 事件回调发生时，事件参数为{@link ArkUI_NodeEvent}。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetNumberValue}获取到index为0的value.f32：插入的值的位置信息。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetStringValue}获取到index为0的buffer字符串：插入的值。
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ON_DID_INSERT = 7010,

    /**
     * @brief 定义在将要删除时，触发回调的枚举值。
     *
     * 事件回调发生时，事件参数为{@link ArkUI_NodeEvent}。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetNumberValue}获取到index为0的value.f32：删除的值的位置信息。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetNumberValue}获取到index为1的value.i32：删除值的方向，0为向后删除，1为向前删除。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetStringValue}获取到index为0的buffer字符串：删除的值。
     * @return 在返回true时，表示正常插入，返回false时，表示不插入。\n
     * 可通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}设置返回值。\n
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ON_WILL_DELETE = 7011,

    /**
     * @brief 定义在删除完成时，触发回调的枚举值。
     *
     * 事件回调发生时，事件参数为{@link ArkUI_NodeEvent}。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetNumberValue}获取到index为0的value.f32：删除的值的位置信息。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetNumberValue}获取到index为1的value.i32：删除值的方向，0为向后删除，1为向前删除。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetStringValue}获取到index为0的buffer字符串：删除的值。
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ON_DID_DELETE = 7012,

    /**
     * @brief Defines the event triggered when content (including preview text) changes in the <b>TextInput</b>
     * component.
     *
     * When the event callback occurs, the union type {@link ArkUI_NodeEvent} is {@link ArkUI_TextChangeEvent}. \n
     * {@link ArkUI_TextChangeEvent} contains the following parameters: \n
     * <b>ArkUI_TextChangeEvent.pStr</b>: content in the <b>TextInput</b> component.
     * <b>ArkUI_TextChangeEvent.pExtendStr</b>: content of the preview text in the <b>TextInput</b> component.
     * <b>ArkUI_TextChangeEvent.number</b>: start position of the preview text in the <b>TextInput</b> component.
     *
     * @since 15
     */
    NODE_TEXT_INPUT_ON_CHANGE_WITH_PREVIEW_TEXT = 7013,

    /**
     * @brief Defines the event triggered before content changes
     *
     * When the event callback occurs, the union type {@link ArkUI_NodeEvent} is {@link ArkUI_TextChangeEvent}. \n
     * {@link ArkUI_TextChangeEvent} contains the following parameters: \n
     * <b>ArkUI_TextChangeEvent.pStr</b>: content in the <b>TextInput</b> component.
     * <b>ArkUI_TextChangeEvent.pExtendStr</b>: content of the preview text in the <b>TextInput</b> component.
     * <b>ArkUI_TextChangeEvent.number</b>: start position of the preview text in the <b>TextInput</b> component.
     * 
     * @since 20
     */
    NODE_TEXT_INPUT_ON_WILL_CHANGE = 7014,

    /**
     * @brief Defines the event triggered when the copy button on the pasteboard, which displays when text is
     * selected, is clicked.
     * \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: text that is copied.
     *
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_ON_COPY = 7015,

    /**
     * @brief Defines the event triggered before copying text.
     * \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: text that is copied.
     * @return Whether the copy is allowed. \n
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * value.i32 at index 0 in the return value indicates whether the copy is allowed.
     * <b>0</b>: not allowed. <b>1</b>: allowed. \n
     *
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_ON_WILL_COPY = 7016,

    /**
     * @brief Defines the event triggered before cutting text.
     * \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: text that is cut.
     * @return Whether the cut is allowed. \n
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * value.i32 at index 0 in the return value indicates whether the cut is allowed.
     * <b>0</b>: not allowed. <b>1</b>: allowed. \n
     *
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_ON_WILL_CUT = 7017,

    /**
     * @brief Defines the event triggered when the input in the text box changes.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: text entered.
     *
     */
    NODE_TEXT_AREA_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_AREA,
    /**
     * @brief Defines the event triggered when the paste button on the pasteboard, which displays when the text box is
     * long pressed, is clicked.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: text that is pasted
     * \n
     * Since 26.0.0, the callback can return whether the paste is allowed.\n
     * @return Whether the paste is allowed. \n
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * value.i32 at index 0 in the return value indicates whether the paste is allowed. \n
     * <b>0</b>: not allowed. <b>1</b>: allowed. \n
     *
     */
    NODE_TEXT_AREA_ON_PASTE,
    /**
     * @brief Defines the event triggered when the text selection position changes.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: start position of the text selection area. \n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: end position of the text selection area. \n
     *
     */
    NODE_TEXT_AREA_ON_TEXT_SELECTION_CHANGE,
    /**
     * @brief Defines the event triggered when matching with the regular expression specified by
     * <b>NODE_TEXT_AREA_INPUT_FILTER</b> fails.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: content that is filtered out when regular expression matching fails. \n
     *
     */
    NODE_TEXT_AREA_ON_INPUT_FILTER_ERROR,
    /**
     * @brief This callback is triggered when the text content is scrolled.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: Indicates the horizontal offset of the text in the content area. \n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: Indicates the vertical coordinate offset of \n
     * the text in the content area. \n
     *
     */
    NODE_TEXT_AREA_ON_CONTENT_SCROLL,

    /**
     * @brief Defines the event triggered when the input status changes.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is \n
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: <b>true</b> indicates that text input is in progress. \n
     *
     */
    NODE_TEXT_AREA_ON_EDIT_CHANGE,

    /**
     * @brief Defines the event triggered when the Enter key on the keyboard is pressed for the multi-line text box.
     *
     * This event is not triggered when <b>keyType</b> is <b>ARKUI_ENTER_KEY_TYPE_NEW_LINE</b>. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is \n
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: type of the Enter key.
     *
     */
    NODE_TEXT_AREA_ON_SUBMIT,

    /**
      * @brief textArea This event is triggered when the input content changes.
      *
      * Conditions for triggering this event: When the input content changes. \n
      * When the event callback occurs, the union type in the event parameter {@link ArkUI_NodeEvent} object is \n
      * {@link ArkUI_NodeComponentEvent}.\n
      * {@link ArkUI_NodeComponentEvent} contains 2 parameters:\n
      * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: Indicates the width of the text. \n
      * <b>ArkUI_NodeComponentEvent.data[1].f32</b>: Indicates the height of the text. \n
      *
      */
    NODE_TEXT_AREA_ON_CONTENT_SIZE_CHANGE,

    /**
     * @brief 定义在将要输入时，触发回调的枚举值。
     *
     * 事件回调发生时，事件参数为{@link ArkUI_NodeEvent}。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetNumberValue}获取到index为0的value.f32：插入的值的位置信息。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetStringValue}获取到index为0的buffer字符串：插入的值。
     * @return 在返回true时，表示正常插入，返回false时，表示不插入。
     * 可通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}设置返回值。\n
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_ON_WILL_INSERT = 8008,

    /**
     * @brief 定义在输入完成时，触发回调的枚举值。
     *
     * 事件回调发生时，事件参数为{@link ArkUI_NodeEvent}。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetNumberValue}获取到index为0的value.f32：插入的值的位置信息。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetStringValue}获取到index为0的buffer字符串：插入的值。
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_ON_DID_INSERT = 8009,

    /**
     * @brief 定义在将要删除时，触发回调的枚举值。
     *
     * 事件回调发生时，事件参数为{@link ArkUI_NodeEvent}。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetNumberValue}获取到index为0的value.f32：删除的值的位置信息。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetNumberValue}获取到index为1的value.i32：删除值的方向，0为向后删除，1为向前删除。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetStringValue}获取到index为0的buffer字符串：删除的值。
     * @return 在返回true时，表示正常插入，返回false时，表示不插入。\n
     * 可通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}设置返回值。\n
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_ON_WILL_DELETE = 8010,

    /**
     * @brief Defines the event triggered when text is deleted.
     *
     * The event parameter is {@link ArkUI_NodeEvent}. \n
     * value.f32: position of the text deleted, with the index of <b>0</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>. \n
     * value.i32: direction for deleting the text, with the index of <b>1</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetNumberValue</b>. The value <b>0</b> indicates backward-delete, and <b>1</b> indicates
     * forward-delete. \n
     * buffer: string value of the text, with the index of <b>0</b>; obtained using
     * <b>OH_ArkUI_NodeEvent_GetStringValue</b>.
     */
    NODE_TEXT_AREA_ON_DID_DELETE = 8011,

    /**
     * @brief Defines the event triggered when content (including preview text) changes in the <b>TextArea</b>
     * component.
     *
     * When the event callback occurs, the union type {@link ArkUI_NodeEvent} is {@link ArkUI_TextChangeEvent}. \n
     * {@link ArkUI_TextChangeEvent} contains the following parameters: \n
     * <b>ArkUI_TextChangeEvent.pStr</b>: content in the <b>TextArea</b> component.
     * <b>ArkUI_TextChangeEvent.pExtendStr</b>: content of the preview text in the <b>TextArea</b> component.
     * <b>ArkUI_TextChangeEvent.number</b>: start position of the preview text in the <b>TextArea</b> component.
     *
     * @since 15
     */
    NODE_TEXT_AREA_ON_CHANGE_WITH_PREVIEW_TEXT = 8012,

    /**
     * @brief Defines the event triggered before content changes.
     *
     * When the event callback occurs, the union type {@link ArkUI_NodeEvent} is {@link ArkUI_TextChangeEvent}. \n
     * {@link ArkUI_TextChangeEvent} contains the following parameters: \n
     * <b>ArkUI_TextChangeEvent.pStr</b>: content in the <b>TextArea</b> component.
     * <b>ArkUI_TextChangeEvent.pExtendStr</b>: content of the preview text in the <b>TextArea</b> component.
     * <b>ArkUI_TextChangeEvent.number</b>: start position of the preview text in the <b>TextArea</b> component.
     *
     * @since 20
     */
    NODE_TEXT_AREA_ON_WILL_CHANGE = 8013,

    /**
     * @brief 定义长按输入框文本弹出菜单后点击复制按钮触发的事件。
     * \n
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合类型为
     * {@link ArkUI_StringAsyncEvent}。\n
     * {@link ArkUI_StringAsyncEvent}包含一个参数：\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>：复制的文本。
     *
     * @since 26.0.0
     */
    NODE_TEXT_AREA_ON_COPY = 8014,

    /**
     * @brief Defines the event triggered before copying text.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: text that is copied.
     * @return Whether the copy is allowed. \n
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * value.i32 at index 0 in the return value indicates whether the copy is allowed.
     * <b>0</b>: not allowed. <b>1</b>: allowed. \n
     *
     * @since 26.0.0
     */
    NODE_TEXT_AREA_ON_WILL_COPY = 8015,

    /**
     * @brief 定义长按输入框文本弹出菜单后点击剪切按钮触发的事件。
     * \n
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合类型为
     * {@link ArkUI_StringAsyncEvent}。\n
     * {@link ArkUI_StringAsyncEvent}包含一个参数：\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>：剪切后的文本。
     *
     * @since 26.0.0
     */
    NODE_TEXT_AREA_ON_CUT = 8016,

    /**
     * @brief Defines the event triggered before cutting text.
     * \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_StringAsyncEvent}. \n
     * {@link ArkUI_StringAsyncEvent} contains one parameter:\n
     * <b>ArkUI_StringAsyncEvent.pStr</b>: text that is cut.
     * @return Whether the cut is allowed. \n
     * You can set the return value using <b>OH_ArkUI_NodeEvent_SetReturnNumberValue</b>. \n
     * value.i32 at index 0 in the return value indicates whether the cut is allowed.
     * <b>0</b>: not allowed. <b>1</b>: allowed. \n
     *
     * @since 26.0.0
     */
    NODE_TEXT_AREA_ON_WILL_CUT = 8017,

    /**
     * @brief Defines the event triggered when the selected status of the <b>ARKUI_NODE_CHECKBOX</b> component changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b><b>1</b>: selected; <b>0</b>: not selected.\n
     */
    NODE_CHECKBOX_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CHECKBOX,

    /**
     * @brief Defines the event triggered when a date is selected in the <b>ARKUI_NODE_DATE_PICKER</b> component.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains three parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: year of the selected date. \n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: month of the selected date. Value range: [0-11]. \n
     * <b>ArkUI_NodeComponentEvent.data[2].i32</b>: day of the selected date. \n
     */
    NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_DATE_PICKER,

    /**
     * @brief Defines the event triggered when a time is selected in the <b>ARKUI_NODE_TIME_PICKER</b> component.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: hour of the selected time. Value range: [0-23]. \n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: minute of the selected time. Value range: [0-59]. \n
     */
    NODE_TIME_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TIME_PICKER,

    /**
     * @brief Defines the event triggered when an item is selected in the <b>ARKUI_NODE_TEXT_PICKER</b> component.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0...11].i32</b>: value of the selected item. \n
     */
    NODE_TEXT_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_PICKER,

    /**
     * @brief Defines the event triggered when an item is selected and scrolling has stopped in the
     * <b>ARKUI_NODE_TEXT_PICKER</b> component.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0...11].i32</b>: value of the selected item. \n
     *
     * @since 14
     */
    NODE_TEXT_PICKER_EVENT_ON_SCROLL_STOP = 15001,

    /**
     * @brief Defines the event triggered when a date is selected in the <b>NODE_CALENDAR_PICKER</b>.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * <b>ArkUI_NodeComponent.data[0].u32</b>: year of the selected date. \n
     * <b>ArkUI_NodeComponent.data[1].u32</b>: month of the selected date. \n
     * <b>ArkUI_NodeComponent.data[2].u32</b>: day of the selected date. \n
     */
    NODE_CALENDAR_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CALENDAR_PICKER,

    /**
     * @brief Defines the event triggered when the <b>ARKUI_NODE_SLIDER</b> component is dragged or clicked.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains two parameters:\n
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: current slider value. \n
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>: state triggered by the event.\n
     */
    NODE_SLIDER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SLIDER,

    /**
     * @brief Defines the event callback function triggered when an object is dragged or clicked by ARKUI_NODE_RADIO.
     * When the event callback occurs, the union type in the {@Link ArkUI_NodeEvent} object is \n
     * {@Link ArkUI_NodeComponentEvent}. \n
     * {@Link ArkUI_NodeComponentEvent} contains one parameter:\n
     * ArkUI_NodeComponentEvent.data[0].i32: option button status. \n
     */
    NODE_RADIO_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_RADIO,

    /**
     * @brief Defines the event callback function triggered when the animation starts to play.
     *
     * When the event callback occurs, the union type in the {@Link ArkUI_NodeEvent} object is \n
     * {@Link ArkUI_NodeComponentEvent}. \n
     * {@Link ArkUI_NodeComponentEvent} contains no parameter:\n
     *
    */
    NODE_IMAGE_ANIMATOR_EVENT_ON_START = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE_ANIMATOR,
    /**
     * @brief Defines the event callback function triggered when the animation playback is paused.
     *
     * When the event callback occurs, the union type in the {@Link ArkUI_NodeEvent} object is \n
     * {@Link ArkUI_NodeComponentEvent}. \n
     * {@Link ArkUI_NodeComponentEvent} contains no parameter:\n
     *
    */
    NODE_IMAGE_ANIMATOR_EVENT_ON_PAUSE = 19001,
    /**
     * @brief Defines the event callback function triggered when the animation playback is repeated.
     *
     * When the event callback occurs, the union type in the {@Link ArkUI_NodeEvent} object is \n
     * {@Link ArkUI_NodeComponentEvent}. \n
     * {@Link ArkUI_NodeComponentEvent} contains no parameter:\n
     *
    */
    NODE_IMAGE_ANIMATOR_EVENT_ON_REPEAT = 19002,
    /**
     * @brief Defines the event callback function when the animation playback returns to the initial state.
     *
     * When the event callback occurs, the union type in the {@Link ArkUI_NodeEvent} object is \n
     * {@Link ArkUI_NodeComponentEvent}. \n
     * {@Link ArkUI_NodeComponentEvent} contains no parameter:\n
     *
    */
    NODE_IMAGE_ANIMATOR_EVENT_ON_CANCEL = 19003,
    /**
     * @brief Defines the event callback function triggered when the animation playback is complete or stopped.
     *
     * When the event callback occurs, the union type in the {@Link ArkUI_NodeEvent} object is \n
     * {@Link ArkUI_NodeComponentEvent}. \n
     * {@Link ArkUI_NodeComponentEvent} contains no parameter:\n
     *
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
     * Status:
     * 0: All checkboxes are selected.
     * 1: Some checkboxes are selected.
     * 2: No checkboxes are selected. \n
     *
     * @since 15
     */
    NODE_CHECKBOX_GROUP_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CHECKBOX_GROUP,

    /**
     * @brief 定义TextEditor组件中选区或光标位置发生变化时触发的事件。
     * <br>事件回调触发时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * <br>{@link ArkUI_NodeComponentEvent}包含两个参数：
     * <br><b>ArkUI_NodeComponentEvent.data[0].i32</b>：选区起始索引。
     * <br><b>ArkUI_NodeComponentEvent.data[1].i32</b>：选区结束索引。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_SELECTION_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_EDITOR,

    /**
     * @brief 定义TextEditor组件首次初始化完成时触发的事件。
     * <br>事件回调触发时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_READY,

    /**
     * @brief 定义TextEditor组件执行粘贴时触发的事件。
     *
     * 系统会根据回调函数返回值判断是否拦截组件的默认行为。 \n
     * 可通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}设置返回值。 \n
     * 返回值中索引为0的value.i32表示是否拦截组件的默认行为。 \n
     * 0：不拦截。1：拦截。 \n
     *
     * @ingroup Text Editor[富文本]
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_PASTE,

    /**
     * @brief 定义TextEditor组件编辑状态发生变化时触发的事件。
     * <br>事件回调触发时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * <br>{@link ArkUI_NodeComponentEvent}包含一个参数：
     * <br><b>ArkUI_NodeComponentEvent.data[0].i32</b>：组件的编辑状态。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_EDITING_CHANGE,

    /**
     * @brief 定义TextEditor组件输入法的回车键被按下时触发的事件。
     * <br>事件回调触发时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * <br>{@link ArkUI_NodeComponentEvent}包含一个参数：
     * <br><b>ArkUI_NodeComponentEvent.data[0].i32</b>：输入法的回车键类型{@link ArkUI_EnterKeyType}。
     * 
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_SUBMIT,

    /**
     * @brief 定义TextEditor组件执行剪切时触发的事件。
     *
     * 系统会根据回调函数返回值判断是否拦截组件的默认行为。 \n
     * 可通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}设置返回值。 \n
     * 返回值中索引为0的value.i32表示是否拦截组件的默认行为。 \n
     * 0：不拦截。1：拦截。 \n
     *
     * @ingroup Text Editor[富文本]
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_CUT,

    /**
     * @brief 定义TextEditor组件执行复制时触发的事件。
     *
     * 系统会根据回调函数返回值判断是否拦截组件的默认行为。 \n
     * 可通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}设置返回值。 \n
     * 返回值中索引为0的value.i32表示是否拦截组件的默认行为。 \n
     * 0：不拦截。1：拦截。 \n
     *
     * @ingroup Text Editor[富文本]
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_COPY,

    /**
     * @brief 定义TextEditor组件在内容将要改变时触发的事件。
     * <br>在任何导致文本内容发生变化的操作生效之前会触发该回调，开发者可根据回调事件中的信息决定是否拦截本次内容变更。
     * <br>当事件回调发生时，可以通过{@link OH_ArkUI_NodeEvent_GetTextEditorOnWillChangeEvent}从{@link ArkUI_NodeEvent}对象中获得
     * {@link OH_ArkUI_TextEditorChangeEvent}对象。
     * <br>使用OH_ArkUI_TextEditorChangeEvent_XXX系列接口可以从该对象中获取更多信息。
     * <br>系统会根据回调函数返回值判断当前内容是否允许被更改。
     * <br>可通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}设置返回值。
     * <br>返回值中索引为0的value.i32表示当前内容是否允许被更改。<b>0</b>：不允许更改。<b>1</b>：允许更改。
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_WILL_CHANGE,

    /**
     * @brief 定义TextEditor组件在内容改变时触发的事件。
     * <br>事件回调触发时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * <br>{@link ArkUI_NodeComponentEvent}包含四个参数：
     * <br><b>ArkUI_NodeComponentEvent.data[0].i32</b>：文本变化前将要被替换的文本范围的起始索引。
     * <br><b>ArkUI_NodeComponentEvent.data[1].i32</b>：文本变化前将要被替换的文本范围的结束索引。
     * <br><b>ArkUI_NodeComponentEvent.data[2].i32</b>：文本变化后新增内容的文本范围的起始索引。
     * <br><b>ArkUI_NodeComponentEvent.data[3].i32</b>：文本变化后新增内容的文本范围的结束索引。
     *
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_DID_CHANGE,

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
     * <br>**ArkUI_NodeComponentEvent.data[3].i32**: current scroll source. The parameter type is
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
     * @brief Event triggered when the scrollable container starts scrolling. The **List**, **Scroll**, and **WaterFlow**
     * components support this event since API version 12, and the **Grid** component supports this event since API
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
     * @brief Defines the event triggered when scrolling of the <b>ARKUI_NODE_SCROLL</b> component stops.
     *
     * Notes for triggering the event:\n
     * 1. This event is triggered when scrolling is stopped by the <b>ARKUI_NODE_SCROLL</b> component or other input
     * settings, such as keyboard and mouse operations. \n
     * 2. This event is triggered when the controller API is called, accompanied by a transition animation. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters. \n
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
     * @brief 定义当用户即将释放可滚动容器组件上的拖动时的回调
     *
     * @since 20
     */
    NODE_SCROLL_EVENT_ON_WILL_STOP_DRAGGING,

    /**
     * @brief 定义Scroll组件缩放开始回调。
     * 触发该事件的条件：Scroll组件缩放开始时触发。
     * 定义Scroll组件缩放回调。
     * 触发该事件的条件：Scroll组件缩放每帧完成时触发。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含1个参数: 
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>: 当前缩放比例。
     *
     * @since 20
     */
    NODE_SCROLL_EVENT_ON_DID_ZOOM,

    /**
     * @brief 定义Scroll组件缩放开始回调。
     * 触发该事件的条件：Scroll组件缩放开始时触发。 

     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。 

     * {@link ArkUI_NodeComponentEvent}中不包含参数。

     *
     * @since 20
     */
    NODE_SCROLL_EVENT_ON_ZOOM_START,

    /**
     * @brief 定义Scroll组件缩放停止回调。
     *
     * 触发该事件的条件：Scroll组件缩放停止时触发。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中不包含参数。
     *
     * @since 20
     */
    NODE_SCROLL_EVENT_ON_ZOOM_STOP,

    /**
     * @brief Defines the callback for when the scrollable will start dragging.
     *
     * This event is triggered when the scrollable will start dragging. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains no parameters: \n
     * @since 21
     */
    NODE_SCROLL_EVENT_ON_WILL_START_DRAGGING = 1002013,

    /**
     * @brief Defines the callback for when the scrollable did end dragging.
     *
     * This event is triggered when the scrollable did end dragging. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter: \n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: whether start fling animation. \n
     *
     * @since 21
     */
    NODE_SCROLL_EVENT_ON_DID_STOP_DRAGGING = 1002014,

    /**
     * @brief Defines the callback for when the scrollable will start fling.
     *
     * This event is triggered when the scrollable will start fling. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains no parameters: \n
     * @since 21
     */
    NODE_SCROLL_EVENT_ON_WILL_START_FLING = 1002015,

    /**
     * @brief Defines the callback for when the scrollable did end fling.
     *
     * This event is triggered when the scrollable did end fling. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains no parameters: \n
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
     * <br>**ArkUI_NodeComponentEvent.data[2].i32**: current scroll source. The parameter type is
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
     * @brief 定义ARKUI_NODE_LIST当前显示内容发生改变的时候触发事件枚举值。
     *
     * 触发该事件的条件 ：
     * 列表初始化时会触发一次，List显示区域内第一个子组件的索引值或最后一个子组件的索引值有变化时会触发。
     * 计算触发条件时，每一个ListItem、ListItemGroup中的header或footer都算一个子组件。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含6个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：List显示区域内第一个子组件的索引值。
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>：List显示区域起始端在ListItemGroup中的区域。类型为{@link ArkUI_ListItemGroupArea}。
     * <b>ArkUI_NodeComponentEvent.data[2].i32</b>：List显示区域起始端在ListItemGroup中的ListItem索引号，
     *   如果List显示区域起始端不在ListItem上，该值为-1。
     * <b>ArkUI_NodeComponentEvent.data[3].i32</b>：List显示区域内最后一个子组件的索引值。
     * <b>ArkUI_NodeComponentEvent.data[4].i32</b>：List显示区域末尾端在ListItemGroup中的区域。类型为{@link ArkUI_ListItemGroupArea}。
     * <b>ArkUI_NodeComponentEvent.data[5].i32</b>：List显示区域末尾端在ListItemGroup中的ListItem索引号，
     *   如果List显示区域末尾端不在ListItem上，该值为-1。
     *
     * @since 15
     */
    NODE_LIST_ON_SCROLL_VISIBLE_CONTENT_CHANGE,

    /**
     * @brief 定义List组件编辑模式状态变更事件枚举值。
     *
     * 触发该事件的条件 ：
     * 1. 设置NODE_LIST_ENABLE_EDIT_MODE属性改变编辑模式状态。
     * 2. 当NODE_LIST_EDIT_MODE_OPTIONS开启双指滑动多选时，双指滑动触发多选状态变更。
     * 注册该事件回调是双指滑动进入多选状态的必要条件。如未注册该回调，双指滑动将不会进入多选状态。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含1个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：编辑模式状态。0：非编辑模式。1：编辑模式。
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
     * @brief Defines the event triggered when the refresh state of the <b>ARKUI_NODE_REFRESH</b> object changes.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>: refresh state. \n
     */
    NODE_REFRESH_STATE_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_REFRESH,
    /**
     * @brief 定义ARKUI_NODE_REFRESH进入刷新状态时触发该事件。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中不包含参数：
     */
    NODE_REFRESH_ON_REFRESH,

    /**
     * @brief 定义ARKUI_NODE_REFRESH下拉距离发生变化时触发该事件。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含1个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>：下拉距离。
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
     * @brief 定义ARKUI_NODE_WATER_FLOW组件的滑动时触发事件枚举值。
     *
     * 触发该事件的条件 ：
     * 1. 滚动组件触发滚动时触发，支持键鼠操作等其他触发滚动的输入设置。
     * 2. 通过滚动控制器API接口调用。
     * 3. 越界回弹。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含2个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>：每帧滚动的偏移量，内容向上滚动时偏移量为正，向下滚动时偏移量为负。
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>：当前滑动状态。
     */
    NODE_WATER_FLOW_ON_DID_SCROLL,
    /**
     * @brief Defines the enumerated values of the event triggered,
     * when the subcomponent of the start position or end position displayed in the current waterfall changes.
     * Condition for triggering the event: \n
     * This event is triggered when the index value of the \n
     * first or last subcomponent in the waterfall display area changes. \n
     * When the event callback occurs, the union type in the {@Link ArkUI_NodeEvent} object is \n
     * {@Link ArkUI_NodeComponentEvent}. \n
     * {@Link ArkUI_NodeComponentEvent} contains two parameters: \n
     * ArkUI_NodeComponentEvent.data[0].i32: The index value of the \n
     * start position of the currently displayed WaterFlow. \n
     * ArkUI_NodeComponentEvent.data[1].i32: The index value of \n
     * the end position of the currently displayed waterfall. \n
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
     * @brief 定义ARKUI_NODE_GRID组件的滑动前触发事件枚举值。
     *
     * 触发该事件的条件 ：
     * 1. 滚动组件触发滚动时触发，支持键鼠操作等其他触发滚动的输入设置。
     * 2. 通过滚动控制器API接口调用。
     * 3. 越界回弹。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含3个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>：
     * 每帧滚动的偏移量，Grid内容向上滚动时偏移量为正，向下滚动时偏移量为负。
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>：当前滑动状态，参数类型{@link ArkUI_ScrollState}。
     * <b>ArkUI_NodeComponentEvent.data[2].i32</b>：当前滚动的来源，参数类型{@link ArkUI_ScrollSource}。
     * @return 不返回或返回一个number，用于设置滚动组件实际的滚动距离。
     *
     * @since 22
     */
    NODE_GRID_ON_WILL_SCROLL = 1013001,

    /**
     * @brief 定义ARKUI_NODE_GRID组件的滑动时触发事件枚举值。
     *
     * 触发该事件的条件 ：
     * 1. 滚动组件触发滚动时触发，支持键鼠操作等其他触发滚动的输入设置。
     * 2. 通过滚动控制器API接口调用。
     * 3. 越界回弹。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含2个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>：
     * 每帧滚动的偏移量，Grid内容向上滚动时偏移量为正，向下滚动时偏移量为负。
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>：当前滑动状态。
     *
     * @since 22
     */
    NODE_GRID_ON_DID_SCROLL = 1013002,

    /**
     * @brief 定义ARKUI_NODE_GRID组件每帧布局结束时触发用于设置滚动条的位置及长度的事件枚举值。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}。
     * 通过OH_ArkUI_NodeEvent_GetNumberValue获取到index为0的value.i32：当前显示的网格起始位置的索引值。
     * 通过OH_ArkUI_NodeEvent_GetNumberValue获取到index为1的value.f32：当前显示的网格起始位置元素相对网格显示起始位置的偏移，单位vp。
     * @return 滚动条位置和长度。
     * 可通过OH_ArkUI_NodeEvent_SetReturnNumberValue设置返回值。
     * 返回值中index为0的value.f32表示Grid内容相对显示区域的总偏移，单位px。
     * 返回值中index为1的value.f32表示Grid内容总长度，单位px。
     *
     * @since 22
     */
    NODE_GRID_ON_SCROLL_BAR_UPDATE = 1013003,
    /**
     * @brief 定义ARKUI_NODE_GRID组件拖拽子组件开始事件枚举值。
     *
     * 触发该事件的条件：
     * 1. 设置NODE_GRID_EDIT_MODE为1。
     * 2. 在Grid子组件上长按并拖动产生足够位移距离时触发。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}。
     * 通过OH_ArkUI_NodeEvent_GetNumberValue获取到index为0的value.f32：当前拖拽点相对Grid组件的x坐标，单位vp。
     * 通过OH_ArkUI_NodeEvent_GetNumberValue获取到index为1的value.f32：当前拖拽点相对Grid组件的y坐标，单位vp。
     * 通过OH_ArkUI_NodeEvent_GetNumberValue获取到index为2的value.i32：被拖拽子组件在Grid组件中的索引值。
     *
     * @return 是否发起拖拽。
     * 可通过OH_ArkUI_NodeEvent_SetReturnNumberValue设置返回值。
     * 返回值中index为0的value.i32表示是否可以拖拽，0表示不可以拖拽，1表示可以拖拽。
     *
     * @since 23
     */
    NODE_GRID_ON_ITEM_DRAG_START = 1013004,

    /**
     * @brief 定义拖拽子组件进入当前Grid组件范围事件枚举值。
     *
     * 触发该事件的条件：
     * 通过NODE_GRID_ON_ITEM_DRAG_START事件成功拖拽的子组件进入当前Grid组件范围。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含2个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>：当前拖拽点相对Grid组件的x坐标，单位vp。
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>：当前拖拽点相对Grid组件的y坐标，单位vp。
     *
     * @since 23
     */
    NODE_GRID_ON_ITEM_DRAG_ENTER = 1013005,

    /**
     * @brief 定义拖拽子组件在当前Grid组件范围内移动事件枚举值。
     *
     * 触发该事件的条件：
     * 通过NODE_GRID_ON_ITEM_DRAG_START事件成功拖拽的子组件在当前Grid组件范围内移动。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含4个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>：当前拖拽点相对Grid组件的x坐标，单位vp。
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>：当前拖拽点相对Grid组件的y坐标，单位vp。
     * <b>ArkUI_NodeComponentEvent.data[2].i32</b>：被拖拽子组件在被拖拽Grid组件中的索引值。
     * <b>ArkUI_NodeComponentEvent.data[3].i32</b>：被拖拽子组件当前位置在当前Grid组件中的索引值。
     *
     * @since 23
     */
    NODE_GRID_ON_ITEM_DRAG_MOVE = 1013006,

    /**
     * @brief 定义拖拽子组件离开当前Grid组件范围事件枚举值。
     *
     * 触发该事件的条件：
     * 通过NODE_GRID_ON_ITEM_DRAG_START事件成功拖拽的子组件离开当前Grid组件范围。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含3个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>：当前拖拽点相对Grid组件的x坐标，单位vp。
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>：当前拖拽点相对Grid组件的y坐标，单位vp。
     * <b>ArkUI_NodeComponentEvent.data[2].i32</b>：被拖拽子组件在被拖拽Grid组件中的索引值。
     *
     * @since 23
     */
    NODE_GRID_ON_ITEM_DRAG_LEAVE = 1013007,

    /**
     * @brief 定义松手释放拖拽子组件事件枚举值。
     *
     * 触发该事件的条件：
     * 松手释放通过NODE_GRID_ON_ITEM_DRAG_START事件成功拖拽的子组件。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含5个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>：当前拖拽点相对Grid组件的x坐标，单位vp。
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>：当前拖拽点相对Grid组件的y坐标，单位vp。
     * <b>ArkUI_NodeComponentEvent.data[2].i32</b>：被拖拽子组件在被拖拽Grid中的索引值。
     * <b>ArkUI_NodeComponentEvent.data[3].i32</b>：被拖拽子组件当前位置在当前Grid组件中的索引值。
     * <b>ArkUI_NodeComponentEvent.data[4].i32</b>：被拖拽子组件是否成功释放，1表示释放位置在Grid组件范围内，0表示释放位置在Grid组件范围外。
     *
     * @since 23
     */
    NODE_GRID_ON_ITEM_DROP = 1013008,

    /**
     * @brief 定义Grid组件编辑模式状态变更事件枚举值。
     *
     * 触发该事件的条件 ：
     * 1. 设置NODE_GRID_ENABLE_EDIT_MODE属性改变编辑模式状态。
     * 2. 当NODE_GRID_EDIT_MODE_OPTIONS开启双指滑动多选时，双指滑动触发多选状态变更。
     * 注册该事件回调是双指滑动进入多选状态的必要条件。如未注册该回调，双指滑动将不会进入多选状态。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含1个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：编辑模式状态。0：非编辑模式。1：编辑模式。
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
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <b>ArkUI_NodeComponentEvent.data[0...11].i32</b>: value of the selected item. \n
     *
     * @since 23
     */
    NODE_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_PICKER,
     /**
      * @brief Defines the event triggered when an item is selected and scrolling has stopped in the
      * <b>ARKUI_NODE_PICKER</b> component.
      *
      * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
      * {@link ArkUI_NodeComponentEvent}. \n
      * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
      * <b>ArkUI_NodeComponentEvent.data[0...11].i32</b>: value of the selected item. \n
      *
      * @since 23
      */
    NODE_PICKER_EVENT_ON_SCROLL_STOP = 1018001,
} ArkUI_NodeEventType;

/**
 * @brief Defines the common structure type of a component event.
 *
 * @since 12
 */
typedef struct ArkUI_NodeEvent ArkUI_NodeEvent;

/**
 * @brief Obtains the type of a component event.
 *
 * @param event Indicates the pointer to the component event.
 * @return Returns the type of the component event.
 * @since 12
 */
ArkUI_NodeEventType OH_ArkUI_NodeEvent_GetEventType(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the custom ID of a component event.
 *
 * The event ID is passed in as a parameter when the {@link registerNodeEvent} function is called and can be applied
 * to the dispatch logic of the same event entry function {@link registerNodeEventReceiver}.
 *
 * @param event Indicates the pointer to the component event.
 * @return Returns the custom ID of the component event.
 * @since 12
 */
int32_t OH_ArkUI_NodeEvent_GetTargetId(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the component object that triggers a component event.
 *
 * @param event Indicates the pointer to the component event.
 * @return Returns the component object that triggers the component event.
 * @since 12
 */
ArkUI_NodeHandle OH_ArkUI_NodeEvent_GetNodeHandle(ArkUI_NodeEvent* event);

/**
 * @brief 获取组件事件中的输入事件（如触碰事件）数据。
 *
 * @param event 组件事件指针。
 * @return ArkUI_UIInputEvent 输入事件数据指针。
 * @since 12
 */
ArkUI_UIInputEvent* OH_ArkUI_NodeEvent_GetInputEvent(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the numerical data in a component event.
 *
 * @param event Indicates the pointer to the component event.
 * @return Returns the pointer to the numerical data.
 * @since 12
 */
ArkUI_NodeComponentEvent* OH_ArkUI_NodeEvent_GetNodeComponentEvent(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the string data in a component event.
 * 
 * @param event Indicates the pointer to the component event.
 * @return Returns the pointer to the string data.
 * @since 12
 */
ArkUI_StringAsyncEvent* OH_ArkUI_NodeEvent_GetStringAsyncEvent(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the ArkUI_TextChangeEvent data from a component event.
 *
 * @param event Pointer to a component event. It cannot be null.
 * @return Returns the pointer to the <b>ArkUI_TextChangeEvent</b> object.
 * @since 15
 */
ArkUI_TextChangeEvent* OH_ArkUI_NodeEvent_GetTextChangeEvent(ArkUI_NodeEvent* event);

/**
 * @brief Obtains the custom data in a component event.
 *
 * This parameter is passed in {@link registerNodeEvent} and can be applied to the service logic when the event
 * is triggered.
 *
 * @param event Indicates the pointer to the component event.
 * @return Returns the pointer to the custom data.
 * @since 12
 */
void* OH_ArkUI_NodeEvent_GetUserData(ArkUI_NodeEvent* event);

/**
 * @brief 获取组件回调事件的数字类型参数。
 *
 * @param event 组件事件指针。
 * @param index 返回值索引。
 * @param value 具体返回值。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE} 组件事件中参数长度超限。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID} 组件事件中不存在该数据。
 * @since 12
 */
int32_t OH_ArkUI_NodeEvent_GetNumberValue(ArkUI_NodeEvent* event, int32_t index, ArkUI_NumberValue* value);

/**
 * @brief 获取组件回调事件的字符串类型参数，字符串数据仅在事件回调过程中有效，需要在事件回调外使用建议进行额外拷贝处理。
 *
 * @param event 组件事件指针。
 * @param index 返回值索引。
 * @param string 字符串数组的指针。
 * @param stringSize 字符串数组的长度。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE} 组件事件中参数长度超限。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID} 组件事件中不存在该数据。
 * @since 12
 */
int32_t OH_ArkUI_NodeEvent_GetStringValue(ArkUI_NodeEvent* event, int32_t index, char** string, int32_t* stringSize);

/**
 * @brief 设置组件回调事件的返回值。
 *
 * @param event 组件事件指针。
 * @param value 事件数字类型数组。
 * @param size 数组长度。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID} 组件事件中不存在该数据。
 * @since 12
 */
int32_t OH_ArkUI_NodeEvent_SetReturnNumberValue(ArkUI_NodeEvent* event, ArkUI_NumberValue* value, int32_t size);

/**
 * @brief 获取组件事件中的触摸测试信息。
 *
 * @param {pointer} nodeEvent Indicates the pointer to an <b>ArkUI_NodeEvent</b> object.
 * @return 返回指向{@link ArkUI_TouchTestInfo}对象的指针。若传入的参数无效或并非触摸测试信息，则返回null。
 * @since 22
 */
ArkUI_TouchTestInfo* OH_ArkUI_NodeEvent_GetTouchTestInfo(ArkUI_NodeEvent* nodeEvent);

/**
 * @brief 获取组件事件中的TextEditor组件文本内容变化数据。
 *
 * @param event 指向{@link ArkUI_NodeEvent}组件事件对象的指针。
 * @return 指向{@link OH_ArkUI_TextEditorChangeEvent}数据对象的指针。
 *     <br>若传入的参数无效或并非TextEditor组件文本内容变化事件信息，则返回<b>null</b>。
 * @since 24
 */
OH_ArkUI_TextEditorChangeEvent* OH_ArkUI_NodeEvent_GetTextEditorOnWillChangeEvent(ArkUI_NodeEvent* event);

/**
 * @brief Defines the dirty area flag passed in the <b>::markDirty</b> API.
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
 * @brief Defines the custom component event type.
 *
 * @since 12
 */
typedef enum {
    /** Measure type. */
    ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE = 1 << 0,
    /** Layout type. */
    ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT = 1 << 1,
    /** Draw type. */
    ARKUI_NODE_CUSTOM_EVENT_ON_DRAW = 1 << 2,
    /** Foreground type. */
    ARKUI_NODE_CUSTOM_EVENT_ON_FOREGROUND_DRAW = 1 << 3,
    /** Overlay type. */
    ARKUI_NODE_CUSTOM_EVENT_ON_OVERLAY_DRAW = 1 << 4,
    /**
     * Draw front type.
     * @since 20
     */
    ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_FRONT = 1 << 5,
    /**
     * Draw behind type.
     * @since 20
     */
    ARKUI_NODE_CUSTOM_EVENT_ON_DRAW_BEHIND = 1 << 6,
} ArkUI_NodeCustomEventType;

/**
 * @brief Defines the general structure of a custom component event.
 *
 * @since 12
 */
typedef struct ArkUI_NodeCustomEvent ArkUI_NodeCustomEvent;

/**
 * @brief Defines the component adapter, which is used for lazy loading of elements of scrollable components.
 *
 * @since 12
 */
typedef struct ArkUI_NodeAdapter* ArkUI_NodeAdapterHandle;

/**
 * @brief Defines the component adapter event.
 *
 * @since 12
 */
typedef struct ArkUI_NodeAdapterEvent ArkUI_NodeAdapterEvent;

/**
 * @brief Enumerates component adapter events.
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
* @brief Destroys a component adapter.
*
* @param handle Indicates the target component adapter.
* @since 12
*/
void OH_ArkUI_NodeAdapter_Dispose(ArkUI_NodeAdapterHandle handle);

/**
* @brief 设置Adapter中的元素总数。
*
* @param handle 组件适配器对象。
* @param size 元素数量。
* @return 错误码。 \n
*         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
*         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
* @since 12
*/
int32_t OH_ArkUI_NodeAdapter_SetTotalNodeCount(ArkUI_NodeAdapterHandle handle, uint32_t size);

/**
* @brief Obtains the total number of elements in the specified adapter.
*
* @param handle Indicates the target component adapter.
* @return Returns the total number of elements in the adapter.
* @since 12
*/
uint32_t OH_ArkUI_NodeAdapter_GetTotalNodeCount(ArkUI_NodeAdapterHandle handle);

/**
* @brief 注册Adapter相关回调事件。在相关回调事件不需要之后，需要执行{@link OH_ArkUI_NodeAdapter_UnregisterEventReceiver}接口注销相关回调事件。
*
* @param handle 组件适配器对象。
* @param userData 自定义数据。
* @param receiver 事件接收回调。
* @return 错误码。 \n
*         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
*         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
* @since 12
*/
int32_t OH_ArkUI_NodeAdapter_RegisterEventReceiver(
ArkUI_NodeAdapterHandle handle, void* userData, void (*receiver)(ArkUI_NodeAdapterEvent* event));

/**
* @brief Deregisters an event callback for the adapter.
*
* @param handle Indicates the target component adapter.
* @since 12
*/
void OH_ArkUI_NodeAdapter_UnregisterEventReceiver(ArkUI_NodeAdapterHandle handle);

/**
* @brief 通知Adapter进行全量元素变化。
*
* @param handle 组件适配器对象。
* @return 错误码。 \n
*         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
*         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
* @since 12
*/
int32_t OH_ArkUI_NodeAdapter_ReloadAllItems(ArkUI_NodeAdapterHandle handle);

/**
* @brief 通知Adapter进行局部元素变化。
*
* @param handle 组件适配器对象。
* @param startPosition 元素变化起始位置。
* @param itemCount 元素变化数量。
* @return 错误码。 \n
*         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
*         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
*         {@link ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR} NodeAdapter需要添加监听器。
* @since 12
*/
int32_t OH_ArkUI_NodeAdapter_ReloadItem(
ArkUI_NodeAdapterHandle handle, uint32_t startPosition, uint32_t itemCount);

/**
* @brief 通知Adapter进行局部元素删除。
*
* @param handle 组件适配器对象。
* @param startPosition 元素删除起始位置。
* @param itemCount 元素删除数量。
* @return 错误码。 \n
*         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
*         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
*         {@link ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR} NodeAdapter需要添加监听器。
* @since 12
*/
int32_t OH_ArkUI_NodeAdapter_RemoveItem(
ArkUI_NodeAdapterHandle handle, uint32_t startPosition, uint32_t itemCount);

/**
* @brief 通知Adapter进行局部元素插入。
*
* @param handle 组件适配器对象。
* @param startPosition 元素插入起始位置。
* @param itemCount 元素插入数量。
* @return 错误码。 \n
*         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
*         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
*         {@link ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR} NodeAdapter需要添加监听器。
* @since 12
*/
int32_t OH_ArkUI_NodeAdapter_InsertItem(
ArkUI_NodeAdapterHandle handle, uint32_t startPosition, uint32_t itemCount);

/**
* @brief 通知Adapter进行局部元素移位。
*
* @param handle 组件适配器对象。
* @param from 元素移位起始位置。
* @param to 元素移位结束位置。
* @return 错误码。 \n
*         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
*         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
*         {@link ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR} NodeAdapter需要添加监听器。
* @since 12
*/
int32_t OH_ArkUI_NodeAdapter_MoveItem(ArkUI_NodeAdapterHandle handle, uint32_t from, uint32_t to);

/**
* @brief 获取存储在Adapter中的所有元素。
*
* 接口调用会返回元素的数组对象指针，该指针指向的内存数据需要开发者手动释放。
*
* @param handle 组件适配器对象。
* @param items 适配器内节点数组。
* @param size 元素数量。
* @return 错误码。 \n
*         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
*         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
*         {@link ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR} NodeAdapter需要添加监听器。
* @since 12
*/
int32_t OH_ArkUI_NodeAdapter_GetAllItems(ArkUI_NodeAdapterHandle handle, ArkUI_NodeHandle** items, uint32_t* size);

/**
* @brief Obtains the custom data passed in during registration of the specified event.
*
* @param event Indicates the target adapter event.
* @since 12
*/
void* OH_ArkUI_NodeAdapterEvent_GetUserData(ArkUI_NodeAdapterEvent* event);

/**
* @brief Obtains the event type.
*
* @param event Indicates the target adapter event.
* @return Returns the event type.
* @since 12
*/
ArkUI_NodeAdapterEventType OH_ArkUI_NodeAdapterEvent_GetType(ArkUI_NodeAdapterEvent* event);

/**
* @brief Obtains the element to be removed for the event to be destroyed.
*
* @param event Indicates the target adapter event.
* @return Returns the element to be removed.
* @since 12
*/
ArkUI_NodeHandle OH_ArkUI_NodeAdapterEvent_GetRemovedNode(ArkUI_NodeAdapterEvent* event);

/**
* @brief Obtains the index of the element to be operated for the specified adapter event.
*
* @param event Indicates the target adapter event.
* @return Returns the index of the element.
* @since 12
*/
uint32_t OH_ArkUI_NodeAdapterEvent_GetItemIndex(ArkUI_NodeAdapterEvent* event);

/**
* @brief Obtains the scrollable container node that uses the specified adapter.
*
* @param event Indicates the target adapter event.
* @return Returns the scrollable container node that uses the specified adapter.
* @since 12
*/
ArkUI_NodeHandle OH_ArkUI_NodeAdapterEvent_GetHostNode(ArkUI_NodeAdapterEvent* event);

/**
* @brief 设置需要新增到Adapter中的组件。
*
* @param event 适配器事件对象。
* @param node 待添加的组件。
* @return 错误码。 \n
*         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
*         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
* @since 12
*/
int32_t OH_ArkUI_NodeAdapterEvent_SetItem(ArkUI_NodeAdapterEvent* event, ArkUI_NodeHandle node);

/**
* @brief 设置生成的组件标识。
*
* @param event 适配器事件对象。
* @param id 设置返回的组件标识。
* @return 错误码。 \n
*         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
*         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
* @since 12
*/
int32_t OH_ArkUI_NodeAdapterEvent_SetNodeId(ArkUI_NodeAdapterEvent* event, int32_t id);

/**
 * @brief Declares a collection of native node APIs provided by ArkUI.
 *
 * The APIs related to the native node must be called in the main thread.
 *
 * @version 1
 * @since 12
 */
typedef struct {
    /**
     * @brief Struct version.
     *
     * @since 12
     */
    int32_t version;

    /**
     * @brief Creates a component based on {@link ArkUI_NodeType} and returns the pointer to the created component.
     *
     * @param type Indicates the type of component to create.
     * @return Returns the pointer to the created component. If the component fails to be created, NULL is returned.
     * @since 12
     */
    ArkUI_NodeHandle (*createNode)(ArkUI_NodeType type);

    /**
     * @brief Destroys the component to which the specified pointer points.
     *
     * @param node Indicates the pointer.
     * @since 12
     */
    void (*disposeNode)(ArkUI_NodeHandle node);

    /**
     * @brief Adds a component to a parent node.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *         Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the following operations are not allowed on
     *             BuilderNode generated nodes: setting or resetting attributes, setting events, or adding or editing subnodes.
     *         Returns {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} if the child node has already been adopted. Add since api 22.
     * @since 12
     */
    int32_t (*addChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief Removes a component from its parent node.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *         Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the following operations are not allowed
     * on BuilderNode generated nodes:
     *         setting or resetting attributes, setting events, or adding or editing subnodes.
     * @since 12
     */
    int32_t (*removeChild)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child);

    /**
     * @brief Inserts a component to a parent node after the specified <b>sibling</b> node.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @param sibling Indicates the pointer to the sibling node after which the target node is to be inserted.
     * If the value is null, the node is inserted at the start of the parent node.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *         Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the following operations are not allowed on BuilderNode generated
     *             nodes: setting or resetting attributes, setting events, or adding or editing subnodes.
     *         Returns {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} if the child node has already been adopted. Add since api 22.
     * @since 12
     */
    int32_t (*insertChildAfter)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, ArkUI_NodeHandle sibling);

    /**
     * @brief Inserts a component to a parent node before the specified <b>sibling</b> node.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @param sibling Indicates the pointer to the sibling node before which the target node is to be inserted.
     * If the value is null, the node is inserted at the end of the parent node.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *         Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the following operations are not allowed on BuilderNode generated
     *             nodes: setting or resetting attributes, setting events, or adding or editing subnodes.
     *         Returns {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} if the child node has already been adopted. Add since api 22.
     * @since 12
     */
    int32_t (*insertChildBefore)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, ArkUI_NodeHandle sibling);

    /**
     * @brief Inserts a component to the specified position in a parent node.
     *
     * @param parent Indicates the pointer to the parent node.
     * @param child Indicates the pointer to the child node.
     * @param position Indicates the position to which the target child node is to be inserted. If the value is a
     * negative number or invalid, the node is inserted at the end of the parent node.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *         Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the following operations are not allowed on BuilderNode generated
     *             nodes: setting or resetting attributes, setting events, or adding or editing subnodes.
     *         Returns {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} if the child node has already been adopted. Add since api 22.
     * @since 12
     */
    int32_t (*insertChildAt)(ArkUI_NodeHandle parent, ArkUI_NodeHandle child, int32_t position);

    /**
     * @brief Sets the attribute of a node.
     *
     * @param node Indicates the node whose attribute needs to be set.
     * @param attribute Indicates the type of attribute to set.
     * @param value Indicates the attribute value.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *         Returns {@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} if the dynamic implementation library
     *         of the native API was not found.
     *         Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the following operations are not allowed
     *         on BuilderNode generated nodes:
     *         setting or resetting attributes, setting events, or adding or editing subnodes.
     * @since 12
     */
    int32_t (*setAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, const ArkUI_AttributeItem* item);

    /**
     * @brief Obtains an attribute.
     *
     * The pointer returned by this API is an internal buffer pointer of the ArkUI framework. As such, you do not need
     * to call <b>delete</b> to release the memory. However, the pointer must be used before this API is called next
     * time. Otherwise, the pointer may be overwritten by other values.
     * @param node Indicates the node whose attribute needs to be obtained.
     * @param attribute Indicates the type of attribute to obtain.
     * @return Returns the attribute value. If the operation fails, a null pointer is returned.
     * @since 12
     */
    const ArkUI_AttributeItem* (*getAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

    /**
     * @brief Resets an attribute.
     *
     * @param node Indicates the node whose attribute needs to be reset.
     * @param attribute Indicates the type of attribute to reset.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *         Returns {@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} if the dynamic implementation library
     *         of the native API was not found.
     *         Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the following operations are not allowed
     *         on BuilderNode generated nodes:
     *         setting or resetting attributes, setting events, or adding or editing subnodes.
     * @since 12
     */
    int32_t (*resetAttribute)(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute);

    /**
     * @brief Registers an event for the specified node.
     *
     * When the component is being displayed, this API must be called in the main thread.
     *
     * @param node Indicates the target node.
     * @param eventType Indicates the type of event to register.
     * @param targetId Indicates the custom event ID, which is passed in the callback of {@link ArkUI_NodeEvent}
     * when the event is triggered.
     * @param userData Indicates the custom event parameter, which is passed in the callback of {@link ArkUI_NodeEvent}
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *         Returns {@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} if the dynamic implementation library
     *         of the native API was not found.
     *         Returns {@link ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED} if the following operations are not allowed
     *         on BuilderNode generated nodes:
     *         setting or resetting attributes, setting events, or adding or editing subnodes.
     * @since 12
     */
    int32_t (*registerNodeEvent)(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType,
        int32_t targetId, void* userData);

    /**
     * @brief Unregisters an event for the specified node.
     *
     * When the component is being displayed, this API must be called in the main thread.
     *
     * @param node Indicates the target node.
     * @param eventType Indicates the type of event to unregister.
     * @since 12
     */
    void (*unregisterNodeEvent)(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType);

    /**
     * @brief Registers an event receiver.
     *
     * The ArkUI framework collects component events generated during the process and calls back the events through
     * the registered event receiver. \n
     * A new call to this API will overwrite the previously registered event receiver. \n
     * Do not directly save the <b>ArkUI_NodeEvent</b> object pointer. The data will be destroyed after the
     * callback is complete. \n
     * To bind with a component instance, you can use the <b>addNodeEventReceiver</b> function. \n
     *
     * @param eventReceiver Indicates the event receiver to register.
     * @since 12
     */
    void (*registerNodeEventReceiver)(void (*eventReceiver)(ArkUI_NodeEvent* event));

    /**
     * @brief Unregisters the event receiver.
     *
     * @since 12
     */
    void (*unregisterNodeEventReceiver)();

    /**
     * @brief Forcibly marks the current node that needs to be measured, laid out, or rendered again.
     *
     * Regarding updates to system attributes, the ArkUI framework automatically marks the dirty area and performs
     * measuring, layout, or rendering again. In this case, you do not need to call this API.
     * @param node Indicates the node for which you want to mark as dirty area.
     * @param dirtyFlag Indicates type of dirty area.
     * @since 12
     */
    void (*markDirty)(ArkUI_NodeHandle node, ArkUI_NodeDirtyFlag dirtyFlag);

    /**
     * @brief Obtains the number of subnodes.
     *
     * @param node Indicates the target node.
     * @return the number of subnodes. If not, returns 0.
     * @since 12
     */
    uint32_t (*getTotalChildCount)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains a subnode.
     *
     * @param node Indicates the target node.
     * @param position Indicates the position of the subnode.
     * @return Returns the pointer to the subnode if the subnode exists; returns <b>NULL</b> otherwise.
     * @since 12
     */
    ArkUI_NodeHandle (*getChildAt)(ArkUI_NodeHandle node, int32_t position);

    /**
     * @brief Obtains the first subnode.
     *
     * @param node Indicates the target node.
     * @return Returns the pointer to the subnode if the subnode exists; returns <b>NULL</b> otherwise.
     * @since 12
     */
    ArkUI_NodeHandle (*getFirstChild)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains the last subnode.
     *
     * @param node Indicates the target node.
     * @return Returns the pointer to the subnode if the subnode exists; returns <b>NULL</b> otherwise.
     * @since 12
     */
    ArkUI_NodeHandle (*getLastChild)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains the previous sibling node.
     *
     * @param node Indicates the target node.
     * @return Returns the pointer to the subnode if the subnode exists; returns <b>NULL</b> otherwise.
     * @since 12
     */
    ArkUI_NodeHandle (*getPreviousSibling)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains the next sibling node.
     *
     * @param node Indicates the target node.
     * @return Returns the pointer to the subnode if the subnode exists; returns <b>NULL</b> otherwise.
     * @since 12
     */
    ArkUI_NodeHandle (*getNextSibling)(ArkUI_NodeHandle node);

    /**
     * @brief Registers a custom event for a node. When the event is triggered, the value is returned through the entry
     * point function registered by <b>registerNodeCustomEventReceiver</b>.
     *
     * @param node Indicates the target node.
     * @param eventType Indicates the type of event to register.
     * @param targetId Indicates the custom event ID, which is passed in the callback of {@link ArkUI_NodeCustomEvent}
     * when the event is triggered.
     * @param userData Indicates the custom event parameter, which is passed in the callback of
     * {@link ArkUI_NodeCustomEvent} when the event is triggered.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     *         Returns {@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} if the dynamic implementation library
     *         of the native API was not found.
     * @since 12
     */
    int32_t (*registerNodeCustomEvent)(
        ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType, int32_t targetId, void* userData);

    /**
     * @brief Unregisters a custom event for a node.
     *
     * @param node Indicates the target node.
     * @param eventType Indicates the type of event to unregister.
     * @since 12
     */
    void (*unregisterNodeCustomEvent)(ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType);

    /**
     * @brief Registers a unified entry point function for custom node event callbacks.
     *
     * The ArkUI framework collects custom component events generated during the process and calls back the events
     * through the registered <b>registerNodeCustomEventReceiver</b>. \n
     * A new call to this API will overwrite the previously registered event receiver.
     * Do not directly save the <b>ArkUI_NodeCustomEvent</b> object pointer.
     * The data will be destroyed after the callback is complete. \n
     * To bind with a component instance, you can use the <b>addNodeCustomEventReceiver</b> function. \n
     *
     * @param eventReceiver Indicates the event receiver to register.
     * @since 12
     */
    void (*registerNodeCustomEventReceiver)(void (*eventReceiver)(ArkUI_NodeCustomEvent* event));

    /**
     * @brief Unregisters the unified entry point function for custom node event callbacks.
     *
     * @since 12
     */
    void (*unregisterNodeCustomEventReceiver)();

    /**
     * @brief Sets the width and height for a component after the measurement.
     *
     * @param node Indicates the target node.
     * @param width Indicates the width.
     * @param height Indicates the height.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*setMeasuredSize)(ArkUI_NodeHandle node, int32_t width, int32_t height);

    /**
     * @brief Sets the position for a component.
     *
     * @param node Indicates the target node.
     * @param positionX Indicates the X coordinate.
     * @param positionY Indicates the Y coordinate.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*setLayoutPosition)(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY);

    /**
     * @brief Obtains the width and height of a component after measurement.
     *
     * @param node Indicates the target node.
     * @return Returns the width and height of the component.
     * @since 12
     */
    ArkUI_IntSize (*getMeasuredSize)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains the position of a component after the layout is complete.
     *
     * @param node Indicates the target node.
     * @return Returns the position of the component.
     * @since 12
     */
    ArkUI_IntOffset (*getLayoutPosition)(ArkUI_NodeHandle node);

    /**
     * @brief Measures a node. You can use the <b>getMeasuredSize</b> API to obtain the size after the measurement.
     *
     * @param node Indicates the target node.
     * @param Constraint Indicates the size constraint.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*measureNode)(ArkUI_NodeHandle node, ArkUI_LayoutConstraint* Constraint);

    /**
     * @brief Lays outs a component and passes the expected position of the component relative to its parent component.
     *
     * When the component is being displayed, this API must be called in the main thread.
     *
     * @param node Indicates the target node.
     * @param positionX Indicates the X coordinate.
     * @param positionY Indicates the Y coordinate.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*layoutNode)(ArkUI_NodeHandle node, int32_t positionX, int32_t positionY);

    /**
     * @brief Adds a component event callback function to a component to receive component events generated
     * by the component.
     *
     * Unlike the global registration function <b>registerNodeEventReceiver</b>, this API allows multiple event
     * receivers to be added to the same component. \n
     * The callback added by this API is triggered before the global callback registered by
     * <b>registerNodeEventReceiver</b>. \n
     * Do not directly save the <b>ArkUI_NodeEvent</b> object pointer.
     * The data will be destroyed after the callback is complete. \n
     *
     * @param node Indicates the component for which you want to add the event callback function.
     * @param eventReceiver Indicates the component event callback function to add.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*addNodeEventReceiver)(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeEvent* event));

    /**
     * @brief Removes the registered component event callback function from a component.
     *
     * @param node Indicates the component from which you want to remove the event callback function.
     * @param eventReceiver Indicates the component event callback function to remove.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*removeNodeEventReceiver)(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeEvent* event));

    /**
     * @brief Adds a custom event callback function to a component to receive custom events
     * (such as layout and drawing events) generated by the component.
     *
     * Unlike the global registration function <b>registerNodeCustomEventReceiver</b>, this API allows
     * multiple event receivers to be added to the same component. \n
     * The callback added by this API is triggered before the global callback registered by
     * <b>registerNodeCustomEventReceiver</b>. \n
     * Do not directly save the <b>ArkUI_NodeCustomEvent</b> object pointer.
     * The data will be destroyed after the callback is complete. \n
     *
     * @param node Indicates the component for which you want to add the custom event callback function.
     * @param eventReceiver Indicates the custom event callback function to add.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*addNodeCustomEventReceiver)(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeCustomEvent* event));

    /**
     * @brief Removes a registered custom event callback function from a component.
     *
     * @param node Indicates the component from which you want to remove the custom event callback function.
     * @param eventReceiver Indicates the custom event callback function to remove.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*removeNodeCustomEventReceiver)(ArkUI_NodeHandle node,
        void (*eventReceiver)(ArkUI_NodeCustomEvent* event));

    /**
     * @brief Saves custom data on the specified component.
     *
     * @param node Indicates the component on which the custom data will be saved.
     * @param userData Indicates the custom data to be saved.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*setUserData)(ArkUI_NodeHandle node, void* userData);

    /**
     * @brief Obtains the custom data saved on the specified component.
     *
     * @param node Indicates the target component.
     * @return Returns the custom data.
     * @since 12
     */
    void* (*getUserData)(ArkUI_NodeHandle node);

    /**
     * @brief Sets the unit for a component.
     *
     * @param node Indicates the component for which you want to set the unit.
     * @param unit Indicates the unit, which is an enumerated value of {@link ArkUI_LengthMetricUnit}.
     * The default value is <b>ARKUI_LENGTH_METRIC_UNIT_DEFAULT</b>.
     * @return Returns the error code.
     *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*setLengthMetricUnit)(ArkUI_NodeHandle node, ArkUI_LengthMetricUnit unit);

    /**
      * @brief Get the parent node.
      *
      * @param node target node object.
      * @return Returns the pointer of the component, if not return NULL
      * @since 12
      */
    ArkUI_NodeHandle (*getParent)(ArkUI_NodeHandle node);

    /**
    * @brief Uninstall all child nodes from the parent component.
    *
    * @param parent target node object.
    * @return Returns the error code.
    *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
    *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
    * @since 12
    */
    int32_t (*removeAllChildren)(ArkUI_NodeHandle parent);
} ArkUI_NativeNodeAPI_1;

/**
* @brief Obtains the size constraint for measurement through a custom component event.
*
* @param event Indicates the pointer to the custom component event.
* @return Returns the pointer to the size constraint.
* @since 12
*/
ArkUI_LayoutConstraint* OH_ArkUI_NodeCustomEvent_GetLayoutConstraintInMeasure(ArkUI_NodeCustomEvent* event);

/**
* @brief Obtains the expected position of a component relative to its parent component in the layout phase through a
* custom component event.
*
* @param event Indicates the pointer to the custom component event.
* @return Returns the expected position relative to the parent component.
* @since 12
*/
ArkUI_IntOffset OH_ArkUI_NodeCustomEvent_GetPositionInLayout(ArkUI_NodeCustomEvent* event);

/**
* @brief Obtains the drawing context through a custom component event.
*
* @param event Indicates the pointer to the custom component event.
* @return Returns the drawing context.
* @since 12
*/
ArkUI_DrawContext* OH_ArkUI_NodeCustomEvent_GetDrawContextInDraw(ArkUI_NodeCustomEvent* event);

/**
* @brief Obtains the ID of a custom component event.
*
* @param event Indicates the pointer to the custom component event.
* @return Returns the ID of the custom component event.
* @since 12
*/
int32_t OH_ArkUI_NodeCustomEvent_GetEventTargetId(ArkUI_NodeCustomEvent* event);

/**
* @brief Obtains custom event parameters through a custom component event.
*
* @param event Indicates the pointer to the custom component event.
* @return Returns the custom event parameters.
* @since 12
*/
void* OH_ArkUI_NodeCustomEvent_GetUserData(ArkUI_NodeCustomEvent* event);

/**
* @brief Obtains a component object through a custom component event.
*
* @param event Indicates the pointer to the custom component event.
* @return Returns the component object.
* @since 12
*/
ArkUI_NodeHandle OH_ArkUI_NodeCustomEvent_GetNodeHandle(ArkUI_NodeCustomEvent* event);

/**
* @brief Obtains the event type through a custom component event.
*
* @param event Indicates the pointer to the custom component event.
* @return Returns the type of the custom component event.
* @since 12
*/
ArkUI_NodeCustomEventType OH_ArkUI_NodeCustomEvent_GetEventType(ArkUI_NodeCustomEvent* event);

/**
* @brief Obtains the measurement information of a custom span through a custom component event.
*
* @param event Indicates the pointer to the custom component event.
* @param info Indicates the measurement information to be obtained.
* @return Returns the result code.
*         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
*         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
*         <br> Possible causes: Parameter verification failed, the parameter should not be nullptr.
* @since 12
*/
int32_t OH_ArkUI_NodeCustomEvent_GetCustomSpanMeasureInfo(
    ArkUI_NodeCustomEvent* event, ArkUI_CustomSpanMeasureInfo* info);

/**
* @brief Sets the measurement metrics of a custom span through a custom component event.
*
* @param event Indicates the pointer to the custom component event.
* @param metrics Indicates the measurement metrics to set.
* @return Returns the result code.
*         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
*         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
*         <br> Possible causes: Parameter verification failed, the parameter should not be nullptr.
* @since 12
*/
int32_t OH_ArkUI_NodeCustomEvent_SetCustomSpanMetrics(
    ArkUI_NodeCustomEvent* event, ArkUI_CustomSpanMetrics* metrics);

/**
* @brief Obtains the drawing information of a custom span through a custom component event.
*
* @param event Indicates the pointer to the custom component event.
* @param info Indicates the drawing information to obtain.
* @return Returns the result code.
*         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
*         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
*         <br> Possible causes: Parameter verification failed, the parameter should not be nullptr.
* @since 12
*/
int32_t OH_ArkUI_NodeCustomEvent_GetCustomSpanDrawInfo(
    ArkUI_NodeCustomEvent* event, ArkUI_CustomSpanDrawInfo* info);

/**
 * @brief Defines the node content event type.
 * 
 * @since 12
 */
typedef enum {
    /** Defines the attach event. */
    NODE_CONTENT_EVENT_ON_ATTACH_TO_WINDOW = 0,
    /** Defines the detach event. */
    NODE_CONTENT_EVENT_ON_DETACH_FROM_WINDOW = 1,
} ArkUI_NodeContentEventType;

/**
 * @brief Enumerates the inspector error codes.
 * @since 15
 */
typedef enum {
    /**
     * @error Success.
     */
    ARKUI_INSPECTOR_NATIVE_RESULT_SUCCESSFUL = 0,
    /**
     * @error Invalid parameter.
     */
    ARKUI_INSPECTOR_NATIVE_RESULT_BAD_PARAMETER = -1,
} ArkUI_InspectorErrorCode;

/**
 * @brief Defines the general structure of a node content event.
 * @since 12
 */
typedef struct ArkUI_NodeContentEvent ArkUI_NodeContentEvent;

/**
 * @brief Defines the callback function of a node content event.
 * @since 12
 */
typedef void (*ArkUI_NodeContentCallback)(ArkUI_NodeContentEvent* event);

/**
 * @brief 注册NodeContent事件函数。
 *
 * @param content 需要注册事件的NodeContent对象。
 * @param callback 事件触发时需要执行的函数回调。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_NodeContent_RegisterCallback(ArkUI_NodeContentHandle content, ArkUI_NodeContentCallback callback);

/**
 * @brief Obtains the type of a node content event.
 *
 * @param event Indicates the pointer to the node content event.
 * @return Returns the type of the node content event.
 * @since 12
 */
ArkUI_NodeContentEventType OH_ArkUI_NodeContentEvent_GetEventType(ArkUI_NodeContentEvent* event);

/**
 * @brief Obtains the node content object that triggers a node content event.
 *
 * @param event Indicates the pointer to the node content event.
 * @return Returns the node content object that triggers the node content event.
 * @since 12
 */
ArkUI_NodeContentHandle OH_ArkUI_NodeContentEvent_GetNodeContentHandle(ArkUI_NodeContentEvent* event);

/**
 * @brief Saves custom data on the specified node content.
 *
 * @param content Indicates the node content on which the custom data will be saved.
 * @param userData Indicates the custom data to be saved.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeContent_SetUserData(ArkUI_NodeContentHandle content, void* userData);

/**
 * @brief Obtains the custom data saved on the specified node content.
 *
 * @param content Indicates the target node content.
 * @return Returns the custom data.
 * @since 12
 */
void* OH_ArkUI_NodeContent_GetUserData(ArkUI_NodeContentHandle content);

/**
 * @brief 将一个ArkUI组件节点添加到对应的NodeContent对象下。
 *
 * @param content 需要被添加节点的NodeContent对象。
 * @param node 需要被添加的节点。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} 子节点已经被接纳。从API version 22开始支持。
 * @since 12
 */
int32_t OH_ArkUI_NodeContent_AddNode(ArkUI_NodeContentHandle content, ArkUI_NodeHandle node);

/**
 * @brief 删除NodeContent对象下的一个ArkUI组件节点。
 *
 * @param content 需要被删除节点的NodeContent对象。
 * @param node 需要被删除的节点。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_NodeContent_RemoveNode(ArkUI_NodeContentHandle content, ArkUI_NodeHandle node);

/**
 * @brief 将一个ArkUI组件节点插入到对应的NodeContent对象的特定位置下。
 *
 * @param content 需要被插入节点的NodeContent对象。
 * @param node 需要被插入的节点。
 * @param position 需要被插入的位置。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} 子节点已经被接纳。从API version 22开始支持。
 * @since 12
 */
int32_t OH_ArkUI_NodeContent_InsertNode(ArkUI_NodeContentHandle content, ArkUI_NodeHandle node, int32_t position);

/**
 * @brief 获取组件布局区域的大小。
 * 布局区域大小不包含图形变化属性，如缩放。
 *
 * @param node ArkUI_NodeHandle指针。
 * @param size 组件handle的绘制区域尺寸，单位：px。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutSize(ArkUI_NodeHandle node, ArkUI_IntSize* size);

/**
 * @brief 获取组件布局区域相对父组件的位置。
 * 布局区域相对位置不包含图形变化属性，如平移。
 *
 * @param node ArkUI_NodeHandle指针。
 * @param localOffset 组件handle相对父组件的偏移值，单位：px。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutPosition(ArkUI_NodeHandle node, ArkUI_IntOffset* localOffset);

/**
 * @brief 获取组件布局区域相对窗口的位置。
 * 布局区域相对位置不包含图形变化属性，如平移。
 *
 * @param node ArkUI_NodeHandle指针。
 * @param globalOffset 组件handle相对窗口的偏移值，单位：px。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInWindow(ArkUI_NodeHandle node, ArkUI_IntOffset* globalOffset);

/**
 * @brief 获取组件布局区域相对屏幕的位置。
 * 布局区域相对位置不包含图形变化属性，如平移。
 *
 * @param node ArkUI_NodeHandle指针。
 * @param screenOffset 组件handle相对屏幕的偏移值，单位：px。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInScreen(ArkUI_NodeHandle node, ArkUI_IntOffset* screenOffset);

/**
 * @brief 获取组件相对于全局屏幕的偏移。
 * 布局区域相对位置不包含图形变化属性，如平移。
 *
 * @param node ArkUI_NodeHandle指针。
 * @param offset 组件handle相对屏幕的偏移值，单位：px。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 20
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInGlobalDisplay(ArkUI_NodeHandle node, ArkUI_IntOffset* offset);

/**
 * @brief Obtain the position of the component in the window, including the properties of graphic translation changes.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param translateOffset The cumulative offset value of the component handle itself,
 * parent components, and ancestor nodes, in px.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetPositionWithTranslateInWindow(ArkUI_NodeHandle node, ArkUI_IntOffset* translateOffset);

/**
 * @brief Obtain the position of the component on the screen, including the attributes of graphic translation changes.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param translateOffset The cumulative offset value of the component handle itself,
 * parent components, and ancestor nodes, in px.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetPositionWithTranslateInScreen(ArkUI_NodeHandle node, ArkUI_IntOffset* translateOffset);

/**
 * @brief Add the custom property of the component. This interface only works on the main thread.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param name The name of the custom property. Passing null pointers is not allowed.
 * @param value The value of the custom property. Passing null pointers is not allowed.
 * @since 13
 */
void OH_ArkUI_NodeUtils_AddCustomProperty(ArkUI_NodeHandle node, const char* name, const char* value);

/**
 * @brief Remove the custom property of the component.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param name The name of the custom property.
 * @since 13
 */
void OH_ArkUI_NodeUtils_RemoveCustomProperty(ArkUI_NodeHandle node, const char* name);

/**
 * @brief Get the value of the custom property of the component.
 *
 * @param node ArkUI-NodeHandle pointer.
 * @param name The name of the custom attribute.
 * @param handle The structure of the custom attribute corresponding to the key parameter name obtained.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 14
 */
int32_t OH_ArkUI_NodeUtils_GetCustomProperty(ArkUI_NodeHandle node, const char* name, ArkUI_CustomProperty** handle);

/**
 * @brief Get the parent node to obtain the component nodes created by ArkTs.
 *
 * @param node Target node object.
 * @return Return the pointer of the component.
 * @since 14
 */
ArkUI_NodeHandle OH_ArkUI_NodeUtils_GetParentInPageTree(ArkUI_NodeHandle node);

/**
 * @brief Retrieve all active child nodes of a node. Span will not be counted in the children.
 *
 * @param head Pass in the node that needs to be obtained.
 * @param handle The structure corresponding to the sub node information of the head node.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 14
 */
int32_t OH_ArkUI_NodeUtils_GetActiveChildrenInfo(ArkUI_NodeHandle head, ArkUI_ActiveChildrenInfo** handle);

/**
 * @brief Retrieve the root node of the current page.
 *
 * @param node Target node object.
 * @return Return the pointer of the component.
 * @since 14
 */
ArkUI_NodeHandle OH_ArkUI_NodeUtils_GetCurrentPageRootNode(ArkUI_NodeHandle node);

/**
 * @brief Retrieve whether the component is labeled by C-API.
 *
 * @param node Target node object.
 * @return Return whether the node is a Tag created by C-API,
 *         true represents created by C-API, false represents not created by C-API.
 * @since 14
 */
bool OH_ArkUI_NodeUtils_IsCreatedByNDK(ArkUI_NodeHandle node);

/**
 * @brief Get the type of node.
 *
 * @param node Target node object.
 * @return Return the type of the node.
 *         For specific open types, refer to {@link ArkUI_NodeType}. For unopened nodes, return -1.
 * @since 14
 */
int32_t OH_ArkUI_NodeUtils_GetNodeType(ArkUI_NodeHandle node);

/**
 * @brief Get info of the window to which the node belongs.
 *
 * @param node Target node object.
 * @param info Window info. Use {@link OH_ArkUI_HostWindowInfo_Destroy} to release memory.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 *         {@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} The node is not mounted.
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetWindowInfo(ArkUI_NodeHandle node, ArkUI_HostWindowInfo** info);
 
/**
 * @brief 获取目标节点在树上的第一个子节点的下标。
 *
 * @param node 目标节点的指针。
 * @param index 子节点的下标值。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetFirstChildIndexWithoutExpand(ArkUI_NodeHandle node, uint32_t* index);

/**
 * @brief 获取目标节点在树上的最后一个子节点的下标。
 *
 * @param node 目标节点的指针。
 * @param index 子节点的下标值。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetLastChildIndexWithoutExpand(ArkUI_NodeHandle node, uint32_t* index);

/**
 * @brief 用不同的展开模式获取对应下标的子节点。
 *
 * @param node 目标节点的指针。
 * @param position 对应子节点的下标。
 * @param subnode 获取子节点的指针。
 * @param expandMode 节点遍历展开方式。 {@link ArkUI_ExpandMode}。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetChildWithExpandMode(ArkUI_NodeHandle node, int32_t position,
    ArkUI_NodeHandle* subnode, uint32_t expandMode);

/**
 * @brief 收起展开状态下的ListItem。
 *
 * @param node 需要注册事件的节点对象。
 * @param userData 自定义事件参数，当事件触发时在回调参数中携带回来。
 * @param onFinish 在收起动画完成后触发的回调。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
 *         {@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} 组件不支持该事件。
 * @since 12
 */
int32_t OH_ArkUI_List_CloseAllSwipeActions(ArkUI_NodeHandle node, void* userData, void (*onFinish)(void* userData));

/**
* @brief Obtain the UIContext pointer to the page where the node is located.
*
* @param node The node.
* @return The UIContext pointer.
*         If a null pointer is returned, it may be because the node is empty.
* @since 12
*/
ArkUI_ContextHandle OH_ArkUI_GetContextByNode(ArkUI_NodeHandle node);

/**
* @brief The event called when the system color mode changes.
*        Only one system color change callback can be registered for the same component.
*
* @param node Indicates the target node.
* @param userData Indicates the custom data to be saved.
* @param onColorModeChange Callback Events.
* @return Error code.
*         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
*         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
* @since 12
*/
int32_t OH_ArkUI_RegisterSystemColorModeChangeEvent(ArkUI_NodeHandle node,
    void* userData, void (*onColorModeChange)(ArkUI_SystemColorMode colorMode, void* userData));

/**
* @brief Unregister the event callback when the system color mode changes.
*
* @param node Indicates the target node.
* @since 12
*/
void OH_ArkUI_UnregisterSystemColorModeChangeEvent(ArkUI_NodeHandle node);

/**
* @brief The event called when the system font style changes.
*        Only one system font change callback can be registered for the same component.
*
* @param node Indicates the target node.
* @param userData Indicates the custom data to be saved.
* @param onFontStyleChange Callback Events.
* @return Error code.
*         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
*         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
* @since 12
*/
int32_t OH_ArkUI_RegisterSystemFontStyleChangeEvent(ArkUI_NodeHandle node,
    void* userData, void (*onFontStyleChange)(ArkUI_SystemFontStyleEvent* event, void* userData));

/**
* @brief Unregister the event callback when the system font style changes.
*
* @param node Indicates the target node.
* @since 12
*/
void OH_ArkUI_UnregisterSystemFontStyleChangeEvent(ArkUI_NodeHandle node);

/**
 * @brief Retrieve the font size value for system font change events.
 *
 * @param event Indicates a pointer to the current system font change event.
 * @return Updated system font size scaling factor. Default value: 1.0.
 * @since 12
 */
float OH_ArkUI_SystemFontStyleEvent_GetFontSizeScale(const ArkUI_SystemFontStyleEvent* event);

/**
 * @brief Retrieve the font thickness values for system font change events.
 *
 * @param event Indicates a pointer to the current system font change event.
 * @return The updated system font thickness scaling factor. Default value: 1.0.
 * @since 12
 */
float OH_ArkUI_SystemFontStyleEvent_GetFontWeightScale(const ArkUI_SystemFontStyleEvent* event);

/**
 * @brief Get the node handle by id.
 *
 * @param id The id of the target node handle.
 * @param node The handle of target node handle.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetAttachedNodeHandleById(const char* id, ArkUI_NodeHandle* node);

/**
 * @brief 将节点移动到目标父节点下，作为子节点。
 *
 * @param node 待移动的节点对象。
 * @param target_parent 目标父节点指针。
 * @param index 转移后的节点下标，如果下标值为非法值，则添加在目标父节点的最后一位。
 * @return 错误码。
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *         {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。
 *         {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} 子节点已经被接纳。从API version 22开始支持。
 * @since 18
 */
int32_t OH_ArkUI_NodeUtils_MoveTo(ArkUI_NodeHandle node, ArkUI_NodeHandle target_parent, int32_t index);

/**
 * @brief 在当前帧触发节点属性更新。
 * 
 * 当前节点的属性在构建阶段后被修改，这些改动不会立即生效，而是延迟到下一帧统一处理。
 * 此功能强制当前帧内即时节点更新，确保同步应用渲染效果。
 *
 * @param node 待更新的节点对象。
 * @return  错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_InvalidateAttributes(ArkUI_NodeHandle node);

/**
 * @brief 设置目标节点跨语言设置属性的能力。
 *
 * @param node 目标节点的指针。
 * @param option 跨语言配置项 {@link ArkUI_CrossLanguageOption}。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_SetCrossLanguageOption(ArkUI_NodeHandle node, ArkUI_CrossLanguageOption* option);

/**
 * @brief 获取目标节点跨语言设置属性的配置项。
 *
 * @param node 目标节点的指针。
 * @param option 跨语言配置项 {@link ArkUI_CrossLanguageOption}。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetCrossLanguageOption(ArkUI_NodeHandle node, ArkUI_CrossLanguageOption* option);

/**
 * @brief Registers a callback for node when layout is completed.
 *
 * @param node Indicates the target node.
 * @param userData Indicates the custom data used in onLayoutCompleted callback function.
 * @param onLayoutCompleted Indicates the function when layout completed is callback.
 * @return error code
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter is incorrect.
 * @since 15
 */
int32_t OH_ArkUI_RegisterLayoutCallbackOnNodeHandle(ArkUI_NodeHandle node,
    void* userData, void (*onLayoutCompleted)(void* userData));


/**
 * @brief Registers a callback for node when draw is completed.
 *
 * @param node Indicates the target node.
 * @param userData Indicates the custom data used in onDrawCompleted callback function.
 * @param onDrawCompleted Indicates the function when draw completed is callback.
 * @return error code
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter is incorrect.
 * @since 15
 */
int32_t OH_ArkUI_RegisterDrawCallbackOnNodeHandle(ArkUI_NodeHandle node,
    void* userData, void (*onDrawCompleted)(void* userData));
    
/**
 * @brief Unregisters the layout completed callback for node.
 *
 * @param node Indicates the target node.
 * @return error code
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter is incorrect.
 * @since 15
 */
int32_t OH_ArkUI_UnregisterLayoutCallbackOnNodeHandle(ArkUI_NodeHandle node);

/**
 * @brief Unregisters the draw completed callback for node.
 *
 * @param node Indicates the target node.
 * @return error code
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter is incorrect.
 * @since 15
 */
int32_t OH_ArkUI_UnregisterDrawCallbackOnNodeHandle(ArkUI_NodeHandle node);

/**
 * @brief Get the snapshot pixelmap for the given node synchronously, will get error if the node is not on the
 * tree or is not rendered yet.
 * Note: the pixelmap should be released through OH_PixelmapNative_Release when it's not used any more.
 *
 * @param node Indicates the target node.
 * @param snapshotOptions the given configuration for taking snapshot, can be null for using default.
 * @param pixelmap Pixelmap pointer created by system, it's the out result.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INTERNAL_ERROR} if the snapshot taking failed will null pixelmap returned.
 *         Returns {@link ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT} if the snapshot taking is timeout.
 * @since 15
 */
/**
 * @brief Obtains a snapshot of a given component. If the node is not in the component tree or has not been rendered,
 * the snapshot operation will fail. When the <b>Pixelmap</b> object created is no longer in use, it should be released
 * by calling {@link OH_PixelmapNative_Release}.
 *
 * @param node Target node.
 * @param snapshotOptions Snapshot settings. If the value is null, the default settings are used.
 *         Snapshot settings include scaling, color space, and dynamic range configuration.
 *         Scaling: floating-point value greater than 0.
 *         Color space: <b>3</b> (DISPLAY_P3), <b>4</b> (SRGB), <b>27</b> (DISPLAY_BT2020_SRGB).
 *         Dynamic range: {@link ArkUI_DynamicRangeMode}.
 * @param pixelmap Pointer to the <b>Pixelmap</b> object created by the system.
 * @return Result code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INTERNAL_ERROR} if the snapshot fails, returning a null pointer.
 *         Returns {@link ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT} if the snapshot operation times out.
 *         Returns {@link ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_MODE_NOT_SUPPORTED} if the provided color space or
 *         dynamic range mode is not supported.
 *         Returns {@link ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_AUTO_NOT_SUPPORTED} if the isAuto parameter of the color
 *         space or dynamic range mode is set to true for offscreen node snapshot.
 * @since 23
 */
int32_t OH_ArkUI_GetNodeSnapshot(ArkUI_NodeHandle node, ArkUI_SnapshotOptions* snapshotOptions,
    OH_PixelmapNative** pixelmap);

/**
 * @brief Query the size limitation of the component snapshot.
 *
 * @param maxWidth Maximum width limit of the component snapshot, in px.
 * @param maxHeight Maximum height limit of the component snapshot, in px.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Invalid function parameter.
 * @since 26.0.0
 */
int32_t OH_ArkUI_GetNodeSnapshotSizeLimitation(int32_t* maxWidth, int32_t* maxHeight);

/**
 * @brief 获取目标节点相对于父节点的偏移值，单位：px。
 *
 * @param node 目标节点。
 * @param globalOffset 目标节点相对父节点的偏移值，单位：px。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetPositionToParent(ArkUI_NodeHandle node, ArkUI_IntOffset* globalOffset);

/**
 * @brief 设置组件支持的多态样式状态。为了更高效地处理，需传入所关注的状态值及对应的状态处理函数，当关注的状态发生时，处理函数会被执行。
 *        可在回调中根据当前状态调整UI样式。当在同一个节点上多次调用该方法时，将以最后一次传入的状态及处理函数为准。
 *        有些类型的组件节点，系统内部已有对某些状态的默认处理。例如，Button组件默认具备对PRESSED状态的样式变化，当在此类组件上使用此方法自定义状态处理时，
 *        会先应用系统默认样式变化，再执行自定义的样式处理，最终效果为两者叠加。
 *        可以通过指定excludeInner为true来禁用系统内部的默认样式效果，但这通常取决于系统内部实现规范是否允许。当调用该函数时，传入的statesChangeHandler函数会立即执行一次，
 *        且无需特意注册对NORMAL状态的监听，只要注册了非NORMAL状态，当状态从任意状态变化回NORMAL时，系统都会进行回调，以便应用进行样式复原。
 *
 * @param node 目标节点。
 * @param uiStates 目标节点需要处理的目标UI状态。
 *        所有目标UI状态的组合结果可以通过“|”操作来计算。例如：targetUIStates = ArkUI_UIState::PRESSED | ArkUI_UIState::FOCUSED。
 * @param statesChangeHandler UI状态改变处理函数。
 *        返回当前UI状态，该值是所有当前状态枚举值“|”计算的结果，可以通过执行“&”操作来确定状态。例如：if (currentStates & ArkUI_UIState::PRESSED == ArkUI_UIState::PRESSED)。
 *        但是，对于正常状态检查，应直接使用等号。例如：if (currentStates == ArkUI_UIState::NORMAL)
 * @param excludeInner 禁止内部默认状态样式的标志。​​true​​表示禁用系统内部的默认样式，false表示不禁用。
 * @param userData onDrawCompleted回调函数中使用的自定义数据。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_AddSupportedUIStates(ArkUI_NodeHandle node, int32_t uiStates,
    void (statesChangeHandler)(int32_t currentStates, void* userData), bool excludeInner, void* userData);

/**
 * @brief 删除注册的状态处理。当通过OH_ArkUI_AddSupportedUIStates注册的状态都被删除时，所注册的stateChangeHandler也不会再被执行。
 *
 * @param node 目标节点。
 * @param uiStates 节点需要删除的目标UI状态。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_RemoveSupportedUIStates(ArkUI_NodeHandle node, int32_t uiStates);

/**
 * @brief Run a custom function inside the UIContext scope.
 *
 * @param uiContext Indicates the pointer to a UI instance.
 * @param userData Indicates the pointer to the custom data.
 * @param callback The custom function.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if the CAPI init error.
 *         Returns {@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if the uiContext is invalid.
 *         Returns {@link ARKUI_ERROR_CODE_CALLBACK_INVALID} if the callback function is invalid.
 * @since 20
 */
int32_t OH_ArkUI_RunTaskInScope(ArkUI_ContextHandle uiContext, void* userData, void(*callback)(void* userData));

/**
 * @brief Get the node handle by uniqueId.
 *
 * @param uniqueId The uniqueId of the target node handle.
 * @param node The handle of target node handle.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 *         {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if the CAPI init error.
 * @since 20
 */
int32_t OH_ArkUI_NodeUtils_GetNodeHandleByUniqueId(const uint32_t uniqueId, ArkUI_NodeHandle* node);

/**
 * @brief Get the uniqueId of the target node handle.
 *
 * @param node The ArkUI-NodeHandle pointer.
 * @param uniqueId The uniqueId of the target node handle, default value is -1.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 *         {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if the CAPI init error.
 * @since 20
 */
int32_t OH_ArkUI_NodeUtils_GetNodeUniqueId(ArkUI_NodeHandle node, int32_t* uniqueId);

/**
 * @brief 获取节点是否处于渲染状态，如果一个节点的对应RenderNode在渲染树上，则处于渲染状态。
 *
 * @param node ArkUI节点指针。
 * @param isInRenderState 节点是否处于渲染状态。true：处于渲染状态；false：不处于渲染状态。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 方法参数错误。 \n
 *         {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_IsInRenderState(ArkUI_NodeHandle node, bool* isInRenderState);

/**
 * @brief 当前节点接纳目标节点为附属节点。被接纳的节点不能已有父节点。
 * 调用该接口实际上不会将其添加为子节点，而是仅允许其接收对应子节点的生命周期回调。
 *
 * @param node ArkUI_NodeHandle指针，指定待接纳节点的父节点。
 * @param child ArkUI_NodeHandle指针，指定待被接纳的子节点。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_HAS_PARENT} 被接纳的节点已有父节点。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_CAN_NOT_BE_ADOPTED} 节点无法被接纳为附属节点。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_CAN_NOT_ADOPT_TO} 节点无法接纳其它附属节点。
 * @since 22
 */
int32_t OH_ArkUI_NativeModule_AdoptChild(ArkUI_NodeHandle node, ArkUI_NodeHandle child);

/**
 * @brief 移除被接纳的目标附属节点。
 *
 * @param node ArkUI_NodeHandle指针，父节点。
 * @param child ArkUI_NodeHandle指针，将要被移除的子节点。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_IS_NOT_IN_ADOPTED_CHILDREN} 节点不是被目标节点接纳的附属节点。
 * @since 22
 */
int32_t OH_ArkUI_NativeModule_RemoveAdoptedChild(ArkUI_NodeHandle node, ArkUI_NodeHandle child);

/**
 * @brief 为组件和实例设置反色算法。详细介绍请参考：[利用反色能力快速适配深色模式](../../ui/ui-dark-light-color-adaptation.md#利用反色能力快速适配深色模式)。
 *
 * @param uiContext UI实例对象指针。 \n
 *         如果该值为null，则该功能适用于整个应用进程。
 * @param forceDark 是否使用反色能力。取值为true：组件使用反色能力，取值为false：组件不使用反色能力。
 * @param nodeType 指定使用反色能力生效组件范围。 \n
 *         ARKUI_NODE_UNDEFINED代表对所有组件类型生效。
 * @param colorInvertFunc 开发者自定义反色算法函数。 \n
 *         如果该值为nullptr，则对组件使用系统默认反色算法，即三原色取反。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。 \n
 *         {@link ARKUI_ERROR_CODE_FORCE_DARK_CONFIG_INVALID} 反色能力入参错误。
 * @since 20
 */
int32_t OH_ArkUI_SetForceDarkConfig(ArkUI_ContextHandle uiContext, bool forceDark, ArkUI_NodeType nodeType,
    uint32_t (*colorInvertFunc)(uint32_t color));

/**
 * @brief 注册目标节点的基础事件回调。
 *
 * 当前支持的事件类型如下: 参考{@link ArkUI_NodeEventType}中的NODE_ON_CLICK_EVENT、NODE_TOUCH_EVENT、NODE_EVENT_ON_APPEAR、
 * NODE_EVENT_ON_DISAPPEAR、NODE_ON_KEY_EVENT、NODE_ON_FOCUS、NODE_ON_BLUR、NODE_ON_HOVER、NODE_ON_MOUSE、NODE_ON_SIZE_CHANGE。
 *
 * @param node 目标节点。
 * @param eventType 事件类型。
 * @param userData 开发者自定义的数据指针，以便在回调函数中处理自定义数据，需确保自定义函数执行时数据有效。
 * @param callback 开发者自定义的回调函数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_NODE_UNSUPPORTED_EVENT_TYPE} 暂不支持该事件类型。
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_RegisterCommonEvent(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType,
    void* userData, void (*callback)(ArkUI_NodeEvent* event));

/**
 * @brief 注销目标节点的基础事件回调。
 *        当前支持的事件类型请参考{@link OH_ArkUI_NativeModule_RegisterCommonEvent}。
 *
 * @param node 目标节点。
 * @param eventType 事件类型。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_UNSUPPORTED_EVENT_TYPE} 暂不支持该事件类型。
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_UnregisterCommonEvent(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType);

/**
 * @brief 注册限制回调间隔的可见区域变化的基础事件回调。
 *
 * @param node 目标节点。
 * @param ratios 阈值数组，表示组件的可见区域。
 * @param size 阈值数组的大小。
 * @param expectedUpdateInterval 开发人员预期的计算间隔。
 * @param userData 开发者自定义的数据指针，以便在回调函数中处理自定义数据，需确保自定义函数执行时数据有效。
 * @param callback 开发者自定义的回调函数。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_RegisterCommonVisibleAreaApproximateChangeEvent(ArkUI_NodeHandle node, float* ratios,
    int32_t size, float expectedUpdateInterval, void* userData, void (*callback)(ArkUI_NodeEvent* event));

/**
 * @brief 注销限制回调间隔的可见区域变化的基础事件回调。
 *
 * @param node 目标节点。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_UnregisterCommonVisibleAreaApproximateChangeEvent(ArkUI_NodeHandle node);

/**
 * @brief 将点的坐标从指定节点的坐标系转换至当前窗口的坐标系。节点的坐标系考虑节点本身的变换，例如，节点A的变换效果为向左平移100，会使得其坐标系中的点的坐标也向左平移100。
 *
 * @param currentNode 指定节点。
 * @param localPosition 点在指定节点坐标系中的坐标，单位：px。
 * @param windowPosition 指向接收转换后坐标（位于当前窗口坐标系中，单位：px）的指针。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} 节点未挂载到节点树上。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_ConvertPositionToWindow(ArkUI_NodeHandle currentNode, ArkUI_IntOffset localPosition, ArkUI_IntOffset* windowPosition);

/**
 * @brief 将点的坐标从当前窗口的坐标系转换至目标节点的坐标系。节点的坐标系考虑节点本身的变换，例如，节点A的变换效果为向左平移100，会使得其坐标系中的点的坐标也向左平移100。
 *
 * @param targetNode 目标节点。
 * @param windowPosition 点在当前窗口坐标系中的坐标，单位：px。
 * @param localPosition 指向接收转换后坐标（位于目标节点坐标系中，单位：px）的指针。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。 \n
 *         {@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} 节点未挂载到节点树上。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_ConvertPositionFromWindow(ArkUI_NodeHandle targetNode, ArkUI_IntOffset windowPosition, ArkUI_IntOffset* localPosition);

/**
 * @brief 停止指定的Swiper节点正在执行的翻页动画。
 *
 * @param node 指定的节点。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。 \n
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 22
 */
int32_t OH_ArkUI_Swiper_FinishAnimation(ArkUI_NodeHandle node);

/**
 * @brief Post UI task to background threads.
 *
 * @param context UIContext pointer of the page where the UI task located.
 * @param asyncUITaskData Parameter of asyncUITask and onFinish.
 * @param asyncUITask Function executed by a background thread.
 * @param onFinish Function executed by UI thread after async UI task is executed.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if context or asyncUITask is nullptr.
 * @since 22
 */
int32_t OH_ArkUI_PostAsyncUITask(ArkUI_ContextHandle context, void* asyncUITaskData,
    void (*asyncUITask)(void* asyncUITaskData), void (*onFinish)(void* asyncUITaskData));

/**
 * @brief Post UI task to UI thread.
 *
 * @param context UIContext pointer of the page where the UI task located.
 * @param taskData Parameter of task.
 * @param task Function executed by UI thread.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if context or task is nullptr.
 * @since 22
 */
int32_t OH_ArkUI_PostUITask(ArkUI_ContextHandle context, void* taskData, void (*task)(void* taskData));

/**
 * @brief 设置菜单栏的可见性。
 *
 * @param uiContext ArkUI上下文句柄，指定的ArkUI容器上下文。
 * @param visible 菜单栏是否可见。true表示菜单栏可见，false表示菜单栏不可见。
 * @return 错误码。 \n
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 操作成功。 \n
 *         {@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} 实例异常（uiContext为空指针、无法通过uiContext获取容器、uiContext不属于原子化服务）。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_AtomicServiceMenuBarSetVisible(ArkUI_ContextHandle uiContext, bool visible);

/**
 * @brief Registers a callback for listening for component dimension and area changes.
 *
 * This function can be called for a valid {@link ArkUI_NodeHandle} node at any time. \n
 * The newly registered callback will replace the previously registered callback for this event and will take effect from the next frame. \n
 * 
 * When the callback is no longer needed, call {@link OH_ArkUI_NativeModule_UnregisterCommonAreaApproximateChangeEvent} to unregister it. \n
 * Otherwise, the callback will be automatically unregistered when the node is released.
 *
 * @param node Pointer to {@link ArkUI_NodeHandle}.
 * @param expectedUpdateInterval Expected calculation interval, in milliseconds.
 * @param userData Pointer to custom data.
 * @param callback Event callback.
 * @return Result code. \n
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful. \n
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs. \n
 * @since 26.0.0
 */
int32_t OH_ArkUI_NativeModule_RegisterCommonAreaApproximateChangeEvent(ArkUI_NodeHandle node,
    float expectedUpdateInterval, void* userData, void (*callback)(ArkUI_NodeEvent* event));

/**
 * @brief Unregisters the callback bound to the dimensions and area changes of a component.
 *
 * @param node Pointer to {@link ArkUI_NodeHandle}.
 * @return Result code. \n
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful. \n
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs. \n
 * @since 26.0.0
 */
int32_t OH_ArkUI_NativeModule_UnregisterCommonAreaApproximateChangeEvent(ArkUI_NodeHandle node);

/**
 * @brief Post UI task to UI thread and wait until UI task finished.
 *
 * @param context UIContext pointer of the page where the UI task located.
 * @param taskData Parameter of task.
 * @param task Function executed by UI thread.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if context or task is nullptr.
 * @since 22
 */
int32_t OH_ArkUI_PostUITaskAndWait(ArkUI_ContextHandle context, void* taskData, void (*task)(void* taskData));

/**
 * @brief Start a fake drag of the Swiper node.
 * Call OH_ArkUI_Swiper_FakeDragBy to simulate the drag motion. Call OH_ArkUI_Swiper_StopFakeDrag to complete the
 * fake drag. A fake drag can be interrupted by a real drag. If you need to ignore touch events and other user input
 * during a fake drag, use NODE_SWIPER_DISABLE_SWIPE.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param isSuccessful If the fake drag started successfully, return true.
 *     If the Swiper is not ready to start the fake drag, or a real or fake drag is already in progress, return false.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_StartFakeDrag(ArkUI_NodeHandle node, bool* isSuccessful);

/**
 * @brief Fake drag by an offset of the Swiper node.
 * The OH_ArkUI_Swiper_StartFakeDrag must be called first.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param offset The offset that needs to be scrolled. The unit is vp.
 * @param isConsumedOffset If not in a fake drag progress, or no offset is consumed, return false.
 *     If any offset is consumed, return true.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_FakeDragBy(ArkUI_NodeHandle node, float offset, bool* isConsumedOffset);

/**
 * @brief Stop a fake drag of the Swiper node.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param isSuccessful If the fake drag stopped successfully, return true.
 *     If the Swiper is not ready to stop the fake drag, or no fake drag is in progress, return false.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_StopFakeDrag(ArkUI_NodeHandle node, bool* isSuccessful);

/**
 * @brief Get the fake drag state of the Swiper node.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param isFakeDragging If a fake drag is in progress return true, otherwise return false
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_IsFakeDragging(ArkUI_NodeHandle node, bool* isFakeDragging);

/**
 * @brief Show the previous page of the Swiper node.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_ShowPrevious(ArkUI_NodeHandle node);

/**
 * @brief Show the next page of the Swiper node.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_ShowNext(ArkUI_NodeHandle node);

/**
 * @brief Get the root node handle of the corresponding page of the Context.
 *
 * @param context A UIContext pointer.
 * @param rootNode The handle of target root node handle. If the context's corresponding
 *     page has no root node, the pointed-to value will be set to null.
 * @return Error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if the CAPI init error.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if the uiContext is invalid.
 * @since 24
 */
int32_t OH_ArkUI_NativeModule_GetPageRootNodeHandleByContext(
    ArkUI_ContextHandle context, ArkUI_NodeHandle* rootNode);

/**
 * @brief Obtains the <b>ArkUI_GestureCollectInterceptInfo</b> object from a specified <b>ArkUI_NodeEvent</b> object.
 *
 * @param nodeEvent Pointer to the <b>ArkUI_NodeEvent</b> object.
 * @return Returns the pointer to the <b>ArkUI_GestureCollectInterceptInfo</b> object.
 *         It is valid only during callback and does not need to be released.
 *         Returns <b>null</b> if the input parameter is invalid or the
 *         information is not gesture collection interception information.
 * @since 26.0.0
 */
ArkUI_GestureCollectInterceptInfo* OH_ArkUI_NodeEvent_GetGestureCollectInterceptInfo(ArkUI_NodeEvent* nodeEvent);

/**
 * @brief Set the subnode mounting policy of the target node.
 *
 * @param node the target node handle.
 * @param policy the policy to set. Valid values correspond to {@link OH_ArkUI_NodeMountPolicy}.
 * @return Error code.
 *     <ul><li>{@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *     </li><li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 *     </li><li>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if CAPI init error.</li></ul>
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_SetChildMountPolicy(ArkUI_NodeHandle node, OH_ArkUI_NodeMountPolicy policy);

/**
 * @brief Get the current child mount policy of the specified node.
 *
 * @param node the target node handle.
 * @param policy the pointer to receive child mounting policy of the target node.
 * @return Error code.
 *     <ul><li>{@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *     </li><li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 *     </li><li>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if CAPI init error.</li></ul>
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_GetChildMountPolicy(ArkUI_NodeHandle node, OH_ArkUI_NodeMountPolicy* policy);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_NODE_H
/** @} */
