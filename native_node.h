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

#include <cstdint>

#include <cstdint>
#ifdef __cplusplus
#ifdef __cplusplus
extern "C" {
#endif
#endif
#define MAX_NODE_SCOPE_NUM 1000

/**
 * @brief Enumerates ArkUI component types that can be created on the native side.
 *
 * @since 12
 */
typedef enum {
    /** Custom node. */
    ARKUI_NODE_CUSTOM = 0,

/** 文本。 */
    ARKUI_NODE_TEXT = 1,

/** 文本段落。 */
    ARKUI_NODE_SPAN = 2,

/** 文本图片段落。 */
    ARKUI_NODE_IMAGE_SPAN = 3,

    /** Image. */
    ARKUI_NODE_IMAGE = 4,

    /** Toggle. */
    ARKUI_NODE_TOGGLE = 5,

/** 加载图标。 */
    ARKUI_NODE_LOADING_PROGRESS = 6,

/** 单行文本输入。 */
    ARKUI_NODE_TEXT_INPUT = 7,

/** 多行文本。 */
    ARKUI_NODE_TEXT_AREA = 8,

    /** Button. */
    ARKUI_NODE_BUTTON = 9,

    /** Progress indicator. */
    ARKUI_NODE_PROGRESS = 10,

    /** Check box. */
    ARKUI_NODE_CHECKBOX = 11,

    /** XComponent. */
    ARKUI_NODE_XCOMPONENT = 12,

/** 日期选择器组件。 */
    ARKUI_NODE_DATE_PICKER = 13,

/** 时间选择组件。 */
    ARKUI_NODE_TIME_PICKER = 14,

/** 滑动选择文本内容的组件。 */
    ARKUI_NODE_TEXT_PICKER = 15,

/** 日历选择器组件。*/
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

    /**
     * 弧形索引条组件
     * @since 26.1.0
     */
    ARKUI_NODE_ARC_ALPHABET_INDEXER = 23,

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


 * 自定义文本段落。
 * 不支持通用属性的设置和获取，支持获取和设置该类型组件节点信息的方法包括{@link OH_ArkUI_NodeCustomEvent_GetCustomSpanMeasureInfo}、{@link OH_ArkUI_NodeCustomEvent_SetCustomSpanMetrics}、{@link OH_ArkUI_NodeCustomEvent_GetCustomSpanDrawInfo}方法。
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
     * Picker容器，用于实现用户选择操作的组件。
     * @since 23
     */
    ARKUI_NODE_PICKER = 1018,

    /**
     * ArcList容器。
     * @since 26.0.0
     */
    ARKUI_NODE_ARC_LIST = 1019,

    /**
     * ArcListItem容器。
     * @since 26.0.0
     */
    ARKUI_NODE_ARC_LIST_ITEM = 1020,

    /**
     * ArcScrollBar容器。
     * @since 26.0.0
     */
    ARKUI_NODE_ARC_SCROLL_BAR = 1021,

    /**
     * 弧形滑块视图容器
     * @since 26.1.0
     */
    ARKUI_NODE_ARC_SWIPER = 1022
} ArkUI_NodeType;

/**
 * @brief 定义ArkUI在Native侧可以设置的属性样式集合。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief Defines the width attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: width, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: width, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_WIDTH = 0,

    /**
     * @brief Defines the height attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: height, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: height, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_HEIGHT,

    /**
     * @brief 背景色属性，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].u32</b>：背景色数值，0xargb格式，形如 `0xFFFF0000` 表示红色。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].u32</b>：背景色数值，0xargb格式，形如 `0xFFFF0000` 表示红色。</li>
     * </ul>
     *
     * @ingroup Background Display [背景显示]
     *
     */
    NODE_BACKGROUND_COLOR,

    /**
     * @brief 背景色图片属性，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.string</b>：图片地址。API version 22及之前版本，支持网络图片资源地址、本地图片资源地址、Base64和{@link PixelMap}资源，不支持{@link svg}图片、
     * gif和webp等类型的动图。从API version 23开始，新增支持webp和gif类型的动图，显示动图第一帧，不支持其他类型的动图。</li>
     * <li>.value[0]?.i32</b>：可选值，repeat参数，参数类型{@link ArkUI_ImageRepeat}，默认值为ARKUI_IMAGE_REPEAT_NONE。</li>
     * <li>.object</b>：PixelMap图片数据，参数类型为{@link ArkUI_DrawableDescriptor}。`.object`参数和`.string`参数二选一，不可同时设置。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.string</b>：图片地址。API version 22及之前版本，支持网络图片资源地址、本地图片资源地址、Base64和PixelMap资源，不支持svg图片、gif和webp等类型的动图。从API
     * version 23开始，新增支持webp和gif类型的动图，显示动图第一帧，不支持其他类型的动图。</li>
     * <li>.value[0].i32</b>：repeat参数，参数类型{@link ArkUI_ImageRepeat}。</li>
     * <li>.object</b>：PixelMap图片数据，参数类型为{@link ArkUI_DrawableDescriptor}。</li>
     * </ul>
     *
     * @ingroup Background Display [背景显示]
     *
     */
    NODE_BACKGROUND_IMAGE,

    /**
     * @brief Defines the padding attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:**
     * 1: Specify the same padding for the four directions.
     * <ul>
     * <li>.value[0].f32: padding, in vp.</li>
     * </ul>
     * 2: Specify different paddings for different directions.
     * <ul>
     * <li>.value[0].f32: top padding, in vp.</li>
     * <li>.value[1].f32: right padding, in vp.</li>
     * <li>.value[2].f32: bottom padding, in vp.</li>
     * <li>.value[3].f32: left padding, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: top padding, in vp.</li>
     * <li>.value[1].f32: right padding, in vp.</li>
     * <li>.value[2].f32: bottom padding, in vp.</li>
     * <li>.value[3].f32: left padding, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
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
     * **There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:**
     * 1. Specify the same margin for the four directions.
     * <ul>
     * <li>.value[0].f32: margin, in vp.</li>
     * </ul>
     * 2. Specify different margins for different directions.
     * <ul>
     * <li>.value[0].f32: top margin, in vp.</li>
     * <li>.value[1].f32: right margin, in vp.</li>
     * <li>.value[2].f32: bottom margin, in vp.</li>
     * <li>.value[3].f32: left margin, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: top margin, in vp.</li>
     * <li>.value[1].f32: right margin, in vp.</li>
     * <li>.value[2].f32: bottom margin, in vp.</li>
     * <li>.value[3].f32: left margin, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
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
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: alignment mode. The data type is {@link ArkUI_Alignment}. The default value is <b>ARKUI_ALIGNMENT_CENTER</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: alignment mode. The data type is {@link ArkUI_Alignment}.</li>
     * </ul>
     *
     * @ingroup Layout
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
     * **There are two formats of {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * 1. Specify the same border for the four directions.
     * <ul>
     * <li>.value[0].f32: width of the four borders.</li>
     * </ul>
     * 2. Specify different borders for different directions.
     * <ul>
     * <li>.value[0].f32: width of the top border.</li>
     * <li>.value[1].f32: width of the right border.</li>
     * <li>.value[2].f32: width of the bottom border.</li>
     * <li>.value[3].f32: width of the left border.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: width of the top border.</li>
     * <li>.value[1].f32: width of the right border.</li>
     * <li>.value[2].f32: width of the bottom border.</li>
     * <li>.value[3].f32: width of the left border.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_BORDER_WIDTH,

    /**
     * @brief Defines the border corner radius attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **There are two formats of {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * 1. Specify the same radius for the four directions.
     * <ul>
     * <li>.value[0].f32: radius of the four corners.</li>
     * </ul>
     * 2. Specify different radius for different directions.
     * <ul>
     * <li>.value[0].f32: radius of the upper left corner.</li>
     * <li>.value[1].f32: radius of the upper right corner.</li>
     * <li>.value[2].f32: radius of the lower left corner.</li>
     * <li>.value[3].f32: radius of the lower right corner.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: radius of the upper left corner.</li>
     * <li>.value[1].f32: radius of the upper right corner.</li>
     * <li>.value[2].f32: radius of the lower left corner.</li>
     * <li>.value[3].f32: radius of the lower right corner.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_BORDER_RADIUS,

    /**
     * @brief Defines the border color attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **There are two formats of {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * 1. Specify the same color of the four borders.
     * <ul>
     * <li>.value[0].u32: color of the four borders, in 0xARGB format, for example, <b>0xFFFF11FF</b>.</li>
     * </ul>
     * 2. Specify different colors of the four borders.
     * <ul>
     * <li>.value[0].u32: color of the top border, in 0xARGB format, for example, <b>0xFFFF11FF</b>.</li>
     * <li>.value[1].u32: color of the right border, in 0xARGB format, for example, <b>0xFFFF11FF</b>.</li>
     * <li>.value[2].u32: color of the lower border, in 0xARGB format, for example, <b>0xFFFF11FF</b>.</li>
     * <li>.value[3].u32: color of the left border, in 0xARGB format, for example, <b>0xFFFF11FF</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: color of the top border, in 0xARGB format, for example, <b>0xFFFF11FF</b>.</li>
     * <li>.value[1].u32: color of the right border, in 0xARGB format, for example, <b>0xFFFF11FF</b>.</li>
     * <li>.value[2].u32: color of the lower border, in 0xARGB format, for example, <b>0xFFFF11FF</b>.</li>
     * <li>.value[3].u32: color of the left border, in 0xARGB format, for example, <b>0xFFFF11FF</b>.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_BORDER_COLOR,

    /**
     * @brief Defines the border line style attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **There are two formats of {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * 1. Specify the same line style of the four borders.
     * <ul>
     * <li>.value[0].i32: line style of the four borders. The parameter type is {@link ArkUI_BorderStyle}. The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>.</li>
     * </ul>
     * 2. Specify different line styles of the four borders.
     * <ul>
     * <li>.value[0].i32: line style of the top border. The parameter type is {@link ArkUI_BorderStyle}. The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>.</li>
     * <li>.value[1].i32: line style of the right border. The parameter type is {@link ArkUI_BorderStyle}. The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>.</li>
     * <li>.value[2].i32: line style of the bottom border. The parameter type is {@link ArkUI_BorderStyle}. The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>.</li>
     * <li>.value[3].i32: line style of the left border. The parameter type is {@link ArkUI_BorderStyle}. The default value is <b>ARKUI_BORDER_STYLE_SOLID</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: line style of the top border.</li>
     * <li>.value[1].i32: line style of the right border.</li>
     * <li>.value[2].i32: line style of the bottom border.</li>
     * <li>.value[3].i32: line style of the left border.</li>
     * </ul>
     *
     * @ingroup Layout
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
     * **参数：**
     * <ul>
     * <li>.value[0].i32</b>：控制当前组件显示或隐藏，参数类型{@link ArkUI_Visibility}，默认值为ARKUI_VISIBILITY_VISIBLE。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].i32</b>：控制当前组件显示或隐藏，参数类型{@link ArkUI_Visibility}，默认值为ARKUI_VISIBILITY_VISIBLE。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
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
     * It takes effect when only the .object parameter is passed, ArkUI_RenderNodeClipOption type is path, and .size must be equal to 1.\n
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
     */
     * @ingroup Visual [视效属性]
     */
    NODE_CLIP_SHAPE,

    /**
     * @brief 矩阵变换功能，可对图形进行平移、旋转和缩放等，支持属性设置，属性重置和属性获取接口。
     * 属性设置方法参数{@link ArkUI_AttributeItem}格式：
     * .value[0...15].f32: 16个浮点数字。
     * 属性获取方法返回值{@link ArkUI_AttributeItem}格式：
     * .value[0...15].f32: 16个浮点数字。
     *
     * @ingroup Visual [视效属性]
     */
    NODE_TRANSFORM,

    /**
     * @brief 触摸测试类型，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].i32</b>：控制当前组件的触摸测试类型，参数类型{@link ArkUI_HitTestMode}，默认值为ARKUI_HIT_TEST_MODE_DEFAULT。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].i32</b>：控制当前组件的触摸测试类型，参数类型{@link ArkUI_HitTestMode}，默认值为ARKUI_HIT_TEST_MODE_DEFAULT。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     */
    NODE_HIT_TEST_BEHAVIOR,

    /**
     * @brief Defines the offset attribute, which specifies the offset of the component's upper left corner relative
     * to the parent container's. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: X coordinate.</li>
     * <li>.value[1].f32: Y coordinate.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: X coordinate.</li>
     * <li>.value[1].f32: Y coordinate.</li>
     * </ul>
     *
     * @ingroup Layout
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
     * **参数：**
     * <ul>
     * <li>.value[0].f32</b>：图片的宽度值，取值范围`[0,+∞)`，单位为vp。</li>
     * <li>.value[1].f32</b>：图片的高度值，取值范围`[0,+∞)`，单位为vp。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].f32</b>：图片的宽度值，单位为vp。</li>
     * <li>.value[1].f32</b>：图片的高度值，单位为vp。</li>
     * </ul>
     *
     * @ingroup Background Display [背景显示]
     *
     */
    NODE_BACKGROUND_IMAGE_SIZE,

    /**
     * @brief 背景图片的宽高样式属性，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].i32</b>：背景图片的宽高样式，取{@link ArkUI_ImageSize}枚举值。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].i32</b>：背景图片的宽高样式，取{@link ArkUI_ImageSize}枚举值。</li>
     * </ul>
     *
     * @ingroup Background Display [背景显示]
     *
     */
    NODE_BACKGROUND_IMAGE_SIZE_WITH_STYLE,

    /**
     * @brief Defines the background blur attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: blue type. The value is an enum of {@link ArkUI_BlurStyle}.</li>
     * <li>.value[1]?.i32: color mode. The value is an enum of {@link ArkUI_ColorMode}.</li>
     * <li>.value[2]?.i32: adaptive color mode. The value is an enum of {@link ArkUI_AdaptiveColor}.</li>
     * <li>.value[3]?.f32: blur degree. The value range is [0.0, 1.0].</li>
     * <li>.value[4]?.f32: start boundary of grayscale blur.</li>
     * <li>.value[5]?.f32: end boundary of grayscale blur.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: blue type. The value is an enum of {@link ArkUI_BlurStyle}.</li>
     * <li>.value[1].i32: color mode. The value is an enum of {@link ArkUI_ColorMode}.</li>
     * <li>.value[2].i32: adaptive color mode. The value is an enum of {@link ArkUI_AdaptiveColor}.</li>
     * <li>.value[3].f32: blur degree. The value range is [0.0, 1.0].</li>
     * <li>.value[4].f32: start boundary of grayscale blur.</li>
     * <li>.value[5].f32: end boundary of grayscale blur.</li>
     * </ul>
     *
     * @ingroup Background Display [背景显示]
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
     * **参数：**
     * <ul>
     * <li>.value[0].i32</b>：参数类型为1表示可获焦，为0表示不可获焦。默认为不可获焦。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].i32</b>：参数类型为1表示可获焦，为0表示不可获焦。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     */
    NODE_FOCUSABLE,

    /**
     * @brief 默认焦点属性，支持属性设置，属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].i32</b>：参数值为1表示是默认焦点，为0表示不是默认焦点。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].i32</b>：参数值为1表示是默认焦点，为0表示不是默认焦点。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     */
    NODE_DEFAULT_FOCUS,

    /**
     * @brief 触摸热区属性，支持属性设置，属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**说明：**
     * <br>设置时data数据大小无数量限制，均可以设置成功，但仅支持获取到前20个。
     * **参数：**
     * <ul>
     * <li>.data[0].f32</b>：触摸点相对于组件左上角的x轴坐标，单位为vp。</li>
     * <li>.data[1].f32</b>：触摸点相对于组件左上角的y轴坐标，单位为vp。</li>
     * <li>.data[2].f32</b>：触摸热区的宽度，单位为百分比。</li>
     * <li>.data[3].f32</b>：触摸热区的高度，单位为百分比。</li>
     * <li>.data[4...].f32</b>：可以设置多个手势响应区域，顺序和上述一致。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.data[0].f32</b>：触摸点相对于组件左上角的x轴坐标，单位为vp。</li>
     * <li>.data[1].f32</b>：触摸点相对于组件左上角的y轴坐标，单位为vp。</li>
     * <li>.data[2].f32</b>：触摸热区的宽度，单位为百分比。</li>
     * <li>.data[3].f32</b>：触摸热区的高度，单位为百分比。</li>
     * <li>.data[4...].f32</b>：可以设置多个手势响应区域，顺序和上述一致。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     */
    NODE_RESPONSE_REGION,

    /**
     * @brief 定义遮罩属性，支持属性设置，属性重置和属性获取。开发者可以通过如下.string或.object设置浮层内容，.string有更高的优先级。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.string</b>：遮罩文本。</li>
     * <li>.value[0]?.i32</b>：可选值，浮层相对于组件的位置，参数类型{@link ArkUI_Alignment}，默认值为ARKUI_ALIGNMENT_TOP_START。</li>
     * <li>.value[1]?.f32</b>：可选值，浮层基于自身左上角的偏移量X，单位为vp，默认值为0vp。</li>
     * <li>.value[2]?.f32</b>：可选值，浮层基于自身左上角的偏移量Y，单位为vp，默认值为0vp。</li>
     * <li>.value[3]?.i32</b>：可选值，浮层的布局方向，参数类型{@link ArkUI_Direction}，默认值为ARKUI_DIRECTION_LTR。
     * 在大部分场景下，这个参数都应该被设置成Auto，这个模式允许系统自动处理布局方向，如果在某些场景下需要保持特定的方向，设置这个属性为LTR（Left-to-Right）或者RTL（Right-to-Left）。
     * 从API version 21开始支持。</li>
     * <li>.object</b>：用于overlay的节点树，参数类型为{@link ArkUI_NodeHandle}，默认值为nullptr。从API version 21开始支持。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.string</b>：遮罩文本。</li>
     * <li>.value[0].i32</b>：浮层相对于组件的位置，参数类型{@link ArkUI_Alignment}，默认值为ARKUI_ALIGNMENT_TOP_START。</li>
     * <li>.value[1].f32</b>：浮层基于自身左上角的偏移量X，单位为vp。</li>
     * <li>.value[2].f32</b>：浮层基于自身左上角的偏移量Y，单位为vp。</li>
     * <li>.value[3].i32</b>：浮层的布局方向，参数类型{@link ArkUI_Direction}，默认值为ARKUI_DIRECTION_LTR。从API version 21开始支持。</li>
     * <li>.object</b>：用于overlay的节点树，参数类型为{@link ArkUI_NodeHandle}。从API version 21开始支持。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
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
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: direction of the main axis. The parameter type is {@link ArkUI_Direction}. The default value is <b>ARKUI_DIRECTION_AUTO</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: direction of the main axis. The parameter type is {@link ArkUI_Direction}. The default value is <b>ARKUI_DIRECTION_AUTO</b>.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_DIRECTION,

    /**
     * @brief Defines the size constraints.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: minimum width, in vp.</li>
     * <li>.value[1].f32: maximum width, in vp.</li>
     * <li>.value[2].f32: minimum height, in vp.</li>
     * <li>.value[3].f32: maximum height, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: minimum width, in vp.</li>
     * <li>.value[1].f32: maximum width, in vp.</li>
     * <li>.value[2].f32: minimum height, in vp.</li>
     * <li>.value[3].f32: maximum height, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
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
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32 : offset along the x-axis, in vp.</li>
     * <li>.value[1].f32 : offset along the y-axis, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32 : offset along the x-axis, in vp.</li>
     * <li>.value[1].f32 : offset along the y-axis, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_OFFSET,

    /**
     * @brief Sets the anchor for locating the component's child.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: X coordinate of the anchor, in vp.</li>
     * <li>.value[1].f32: Y coordinate of the anchor, in vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: X coordinate of the anchor, in vp.</li>
     * <li>.value[1].f32: Y coordinate of the anchor, in vp.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_MARK_ANCHOR,

    /**
     * @brief 背景图在组件中显示位置，即相对于组件左上角的坐标，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].f32</b>：x轴位置，单位为px。</li>
     * <li>.value[1].f32</b>：y轴位置，单位为px。</li>
     * <li>.value[2]?.i32</b>：可选值，对齐方式，参数类型{@link ArkUI_Alignment}，默认值为ARKUI_ALIGNMENT_TOP_START。该参数从API version
     * 21开始支持。</li>
     * <li>.value[3]?.i32</b>：可选值，布局方向，参数类型{@link ArkUI_Direction}，默认值为ARKUI_DIRECTION_AUTO。多数场景下建议设置为AUTO，
     * 由系统自动处理布局方向；若需要固定方向，可设置为LTR或RTL。该参数从API version 21开始支持。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].f32</b>：x轴位置，单位为px。</li>
     * <li>.value[1].f32</b>：y轴位置，单位为px。</li>
     * <li>.value[2].i32</b>：对齐方式，参数类型{@link ArkUI_Alignment}。该返回值从API version 21开始支持。</li>
     * <li>.value[3].i32</b>：布局方向，参数类型{@link ArkUI_Direction}。该返回值从API version 21开始支持。</li>
     * </ul>
     *
     * @ingroup Background Display [背景显示]
     *
     */
    NODE_BACKGROUND_IMAGE_POSITION,

    /**
     * @brief Sets the alignment rules in the relative container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: Use the {@link ArkUI_AlignmentRuleOption} object as the component’s alignment rule.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object: Use the {@link ArkUI_AlignmentRuleOption} object as the component’s alignment rule.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_ALIGN_RULES,

    /**
     * @brief Sets the alignment mode of the child components along the cross axis of the parent container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: alignment mode of the child components along the cross axis of the parent container. The parameter type is {@link ArkUI_ItemAlignment}. The default value is <b>ARKUI_ITEM_ALIGNMENT_AUTO</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: alignment mode of the child components along the cross axis of the parent container. The parameter type is {@link ArkUI_ItemAlignment}. The default value is <b>ARKUI_ITEM_ALIGNMENT_AUTO</b>.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_ALIGN_SELF,

    /**
     * @brief Sets the percentage of the parent container's remaining space that is allocated to the component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: percentage of the parent container's remaining space that is allocated to the component.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: percentage of the parent container's remaining space that is allocated to the component.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_FLEX_GROW,

    /**
     * @brief Sets the percentage of the parent container's shrink size that is allocated to the component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: percentage of the parent container's shrink size that is allocated to the component.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: percentage of the parent container's shrink size that is allocated to the component.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_FLEX_SHRINK,

    /**
     * @brief Sets the base size of the component.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: percentage of the parent container's remaining space that is allocated to the component.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: percentage of the parent container's remaining space that is allocated to the component.</li>
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
     * @brief 组件获取焦点属性，支持属性设置，属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**说明：**
     * <br>设置参数为0时，当前层级页面获焦组件失焦，焦点转移到根容器上。
     * **参数：**
     * <ul>
     * <li>.value[0].i32</b>：参数值为1表示组件获焦，为0表示组件失焦。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].i32</b>：参数值为1表示组件获焦，为0表示组件失焦。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     */
    NODE_FOCUS_STATUS,

    /**
     * @brief Defines the aspect ratio attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: aspect ratio of the component, in width/height format.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: aspect ratio of the component, in width/height format.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_ASPECT_RATIO,

    /**
     * @brief Defines the weight of the component within its row, column, or flex container for proportional
     * distribution of available space within the container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: weight of the component along the main axis.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: weight of the component along the main axis.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_LAYOUT_WEIGHT,

    /**
     * @brief Sets the display priority for the component in the row, column, or flex  (single-line) container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: display priority of the component in the container.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: display priority of the component in the container.</li>
     * </ul>
     *
     * @ingroup Layout
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
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: width, in percentage.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: width, in percentage.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_WIDTH_PERCENT,

    /**
     * @brief Defines the height attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: height, in percentage.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: height, in percentage.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_HEIGHT_PERCENT,

    /**
     * @brief Defines the padding attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:**
     * 1: Specify the same padding for the four directions.
     * <ul>
     * <li>.value[0].f32: padding, in percentage.</li>
     * </ul>
     * 2: Specify different paddings for different directions.
     * <ul>
     * <li>.value[0].f32: top padding, in percentage.</li>
     * <li>.value[1].f32: right padding, in percentage.</li>
     * <li>.value[2].f32: bottom padding, in percentage.</li>
     * <li>.value[3].f32: left padding, in percentage.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: top padding, in percentage.</li>
     * <li>.value[1].f32: right padding, in percentage.</li>
     * <li>.value[2].f32: bottom padding, in percentage.</li>
     * <li>.value[3].f32: left padding, in percentage.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_PADDING_PERCENT,

    /**
     * @brief Defines the margin attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **There are two formats of {@link ArkUI_AttributeItem} for setting the attribute value:**
     * 1: Specify the same margin for the four directions.
     * <ul>
     * <li>.value[0].f32: margin, in percentage.</li>
     * </ul>
     * 2: Specify different margins for different directions.
     * <ul>
     * <li>.value[0].f32: top margin, in percentage.</li>
     * <li>.value[1].f32: right margin, in percentage.</li>
     * <li>.value[2].f32: bottom margin, in percentage.</li>
     * <li>.value[3].f32: left margin, in percentage.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: top margin, in percentage.</li>
     * <li>.value[1].f32: right margin, in percentage.</li>
     * <li>.value[2].f32: bottom margin, in percentage.</li>
     * <li>.value[3].f32: left margin, in percentage.</li>
     * </ul>
     *
     * @ingroup Layout
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
     * **Attribute setting method parameter {@link ArkUI_AttributeItem} format:**
     * <ul>
     * <li>.value[0].i32: The direction of the chain. Enum {@link ArkUI_Axis}.</li>
     * <li>.value[1].i32: Chain style. Enum {@link ArkUI_RelativeLayoutChainStyle}.</li>
     * <li>.value[0].i32: The direction of the chain. Enum {@link ArkUI_Axis}.</li>
     * <li>.value[1].i32: Chain style. Enum {@link ArkUI_RelativeLayoutChainStyle}.</li>
     * </ul>
     *
     * @ingroup Layout
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
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: Width value, unit is vp.</li>
     * <li>.value[1].f32: Height value, unit is vp.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: Width value, unit is vp.</li>
     * <li>.value[1].f32: Height value, unit is vp.</li>
     * </ul>
     *
     * @ingroup Layout
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
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: X coordinate of the component, in px.</li>
     * <li>.value[1].i32: Y coordinate of the component, in px.</li>
     * <li>.value[2].i32: width of the component, in px.</li>
     * <li>.value[3].i32: height of the component, in px.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: X coordinate of the component, in px.</li>
     * <li>.value[1].i32: Y coordinate of the component, in px.</li>
     * <li>.value[2].i32: width of the component, in px.</li>
     * <li>.value[3].i32: height of the component, in px.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_LAYOUT_RECT,

    /**
     * @brief 设置当前组件是否支持点击获焦能力，支持属性设置，属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].i32：参数值为1表示支持点击获焦，为0表示不支持点击获焦。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].i32：参数值为1表示支持点击获焦，为0表示不支持点击获焦。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     */
    NODE_FOCUS_ON_TOUCH,

    /**
     * @brief Defines the border width attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * 1:
     * <ul>
     * <li>.value[0].f32: width of the four borders, in percentage.</li>
     * </ul>
     * 2:
     * <ul>
     * <li>.value[0].f32: width of the top border, in percentage.</li>
     * <li>.value[1].f32: width of the right border, in percentage.</li>
     * <li>.value[2].f32: width of the bottom border, in percentage.</li>
     * <li>.value[3].f32: width of the left border, in percentage.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: width of the top border, in percentage.</li>
     * <li>.value[1].f32: width of the right border, in percentage.</li>
     * <li>.value[2].f32: width of the bottom border, in percentage.</li>
     * <li>.value[3].f32: width of the left border, in percentage.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_BORDER_WIDTH_PERCENT = 85,

    /**
     * @brief Defines the border corner radius attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * 1:
     * <ul>
     * <li>.value[0].f32: radius of the four corners, in percentage.</li>
     * </ul>
     * 2:
     * <ul>
     * <li>.value[0].f32: radius of the upper left corner, in percentage.</li>
     * <li>.value[1].f32: radius of the upper right corner, in percentage.</li>
     * <li>.value[2].f32: radius of the lower left corner, in percentage.</li>
     * <li>.value[3].f32: radius of the lower right corner, in percentage.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: radius of the upper left corner, in percentage.</li>
     * <li>.value[1].f32: radius of the upper right corner, in percentage.</li>
     * <li>.value[2].f32: radius of the lower left corner, in percentage.</li>
     * <li>.value[3].f32: radius of the lower right corner, in percentage.</li>
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
     * @brief defines control components to extend their security zones,
     * supporting property setting, property reset, and property fetching.
     *
     * **Attribute setting method {@link ArkUI_AttributeItem} Parameter format:**
     * <ul>
     * <li>.value[0]? .u32: Set of extended security zone enumerated values {@link ArkUI_SafeAreaType}, For example, ARKUI_SAFE_AREA_TYPE_SYSTEM | ARKUI_SAFE_AREA_TYPE_CUTOUT.</li>
     * <li>.value[1]? .u32: set of directional enum values for extended security zones {@link ArkUI_SafeAreaEdge}; For example: ARKUI_SAFE_AREA_EDGE_TOP | ARKUI_SAFE_AREA_EDGE_BOTTOM.</li>
     * </ul>
     *
     * **Attribute fetch method return value {@link ArkUI_AttributeItem} format:**
     * <ul>
     * <li>.value[0].u32: extends the security zone. .</li>
     * <li>.value[1].u32: indicates the direction to extend the security zone. .</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_EXPAND_SAFE_AREA = 92,

    /**
     * @brief Defines the visible area ratio (visible area/total area of the component) threshold for invoking the
     * visible area change event of the component.
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the
     * attribute:**
     * <ul>
     * <li>.value[...].f32: threshold array. The value ranges from 0 to 1.</li>
     * <li>.object: The parameter type is {@link ArkUI_VisibleAreaEventOptions}.</li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[...].f32: threshold array.</li>
     * <li>.object: The return type is {@link ArkUI_VisibleAreaEventOptions}.</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
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
     * **参数：**
     * <ul>
     * <li>.value[0].f32</b>：焦点框相对组件边缘的距离。正数代表外侧，负数代表内侧。不支持百分比。</li>
     * <li>.value[1].f32</b>：焦点框宽度。不支持负数和百分比。</li>
     * <li>.value[2].u32</b>：焦点框颜色。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     */
    NODE_FOCUS_BOX = 96,

    /**
     * @brief 组件所绑定的点击手势移动距离限制，支持属性设置。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].f32</b>：表示识别点击手势时允许手指在该范围内移动，单位为vp。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     */
    NODE_CLICK_DISTANCE = 97,

    /**
     * @brief 控制焦点是否能停在当前组件，支持属性设置，属性重置和属性获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].i32</b>：参数值为1表示焦点能停在当前组件，为0表示焦点不能停在当前组件。默认值为0。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].i32</b>：参数值为1表示焦点停在当前组件，为0表示焦点未停在当前组件。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
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
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: width of the left edge. The unit is vp. </li>
     * <li>.value[1].f32: width of the top edge. The unit is vp. </li>
     * <li>.value[2].f32: width of the right edge. The unit is vp. </li>
     * <li>.value[3].f32: width of the bottom edge. The unit is vp.
     * </li>
     * </ul>
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: width of the left edge. The unit is vp. </li>
     * <li>.value[1].f32: width of the top edge. The unit is vp. </li>
     * <li>.value[2].f32: width of the right edge. The unit is vp. </li>
     * <li>.value[3].f32: width of the bottom edge. The unit is vp. </li>
     * </ul>
     *
     * @ingroup Background Display [背景显示]
     *
     * @since 19
     */
    NODE_BACKGROUND_IMAGE_RESIZABLE_WITH_SLICE = 100,

    /**
     * @brief 设置下一个走焦节点。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].i32</b>：走焦类型，定义在{@link ArkUI_FocusMove}。</li>
     * <li>.object</b>：下一个焦点。参数类型为{@link ArkUI_NodeHandle}。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
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
     * **参数：**
     * <ul>
     * <li>.object</b>：参数类型为{@link ArkUI_VisibleAreaEventOptions}。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.object</b>：参数类型为{@link ArkUI_VisibleAreaEventOptions}。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
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
     * @ingroup Layout
     * @since 21
     */
    NODE_WIDTH_LAYOUTPOLICY = 105,

    /**
     * @brief Defines the height attribute with param type LayoutPolicy, which can be set, reset, and obtained
     * as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: the LayoutPolicy that the height of the component follows. The parameter type is {@link ArkUI_LayoutPolicy}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: the LayoutPolicy that the height of the component follows. The parameter type is {@link ArkUI_LayoutPolicy}.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 21
     */
    NODE_HEIGHT_LAYOUTPOLICY = 106,

    /**
     * @brief Defines the position attribute in param type Edges, which specifies the position of the component
     * by the distance relative to the parent container's four edges. This attribute can be set, reset, and obtained as
     * required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object indicates struct of edges for position. The parameter type is {@link ArkUI_PositionEdges}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object indicates struct of edges for position. The parameter type is {@link ArkUI_PositionEdges}.</li>
     * </ul>
     *
     * @ingroup Layout
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
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object indicates struct of policy for pixelRound. The parameter type is {@link ArkUI_PixelRoundPolicy}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.object indicates struct of policy for pixelRound. The parameter type is {@link ArkUI_PixelRoundPolicy}.</li>
     * </ul>
     *
     * @ingroup Layout
     * @since 21
     */
    NODE_PIXEL_ROUND = 109,

    /**
     * @brief 设置组件是否启用默认点击音效。此功能仅在TV上生效，在其他设备上启用默认点击音效也不会播放音效。是否能够发音依赖设备声音相关的设置，如静音模式下不会播放音效。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].i32</b>：参数取值为1或0，1表示启用默认点击音效，0表示禁用默认点击音效，默认值为1。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].i32</b>：表示此节点是否启用了默认的点击音效。参数取值为1或0，1表示启用默认点击音效，0表示禁用默认点击音效。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     * @since 24
     */
    NODE_ENABLE_CLICK_SOUND_EFFECT = 110,

    /**
     * @brief 定义运动路径属性，可通过API根据需要设置、重置和获取该属性。
     * 设置属性时，参数{@link ArkUI_AttributeItem}的格式为：

     * .object 表示指向 ArkUI_MotionPathOptions 的指针。参数类型为
     * {@link ArkUI_MotionPathOptions}。

     * 

     * 返回值{@link ArkUI_AttributeItem}的格式为：

     * .object 表示指向 ArkUI_MotionPathOptions 的指针。参数类型为
     * {@link ArkUI_MotionPathOptions}。

     *
     * @ingroup Animate [动效属性]
     * @since 23
     */
    NODE_MOTION_PATH = 111,

    /**
     * @brief 定义组件被悬停时的效果。该属性可根据需要通过API进行设置、重置和获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].i32</b>：组件在悬停状态下的悬停效果。参数类型为{@link ArkUI_HoverEffect}。默认值为ARKUI_HOVER_EFFECT_AUTO。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].i32</b>：组件在悬停状态下的悬停效果。参数类型为{@link ArkUI_HoverEffect}。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     * @since 23
     */
    NODE_HOVER_EFFECT = 112,

    /**
     * @brief 将容器设置为具有特定标识符的焦点组，支持属性设置、属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.string</b>：焦点作用域标识符。</li>
     * <li>.value[0].i32</b>：该作用域是否为焦点组，默认值为0。取值范围为1或0。1表示设置为焦点组，0表示组件未被设置为焦点组。</li>
     * <li>.value[1].i32</b>：箭头键是否可以将焦点从焦点组内部移至外部，仅当isGroup为true时有效，默认值为1。取值范围为1或0。1表示箭头键可以将焦点从焦点组内部移至外部，
     * 0表示箭头键无法将焦点从焦点组内部移至外部。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.string</b>：焦点作用域标识符。</li>
     * <li>.value[0].i32</b>：该作用域是否为焦点组，默认值为0。取值范围为1或0。1表示设置为焦点组，0表示组件未被设置为焦点组。</li>
     * <li>.value[1].i32</b>：箭头键是否可以将焦点从焦点组内部移至外部，仅当isGroup为true时有效，默认值为1。取值范围为1或0。1表示箭头键可以将焦点从焦点组内部移至外部，
     * 0表示箭头键无法将焦点从焦点组内部移至外部。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     * @since 23
     */
    NODE_FOCUS_SCOPE_ID = 113,

    /**
     * @brief 设置组件在特定焦点作用域内的焦点优先级，支持属性设置、属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.string</b>：焦点作用域标识符。</li>
     * <li>.value[0].i32</b>：焦点作用域内获焦优先级。参数类型为{@link ArkUI_FocusPriority}。默认值为ARKUI_FOCUS_PRIORITY_AUTO。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.string</b>：焦点作用域标识符。</li>
     * <li>.value[0].i32</b>：焦点作用域优先级。参数类型为{@link ArkUI_FocusPriority}。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     * @since 23
     */
    NODE_FOCUS_SCOPE_PRIORITY = 114,

    /**
     * @brief 设置点击事件的距离阈值，支持属性设置、属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].f32</b>：点击事件移动阈值。取值范围(0, +∞)。默认值为+∞，单位vp。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].f32</b>：点击事件移动阈值。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     * @since 23
     */
    NODE_ON_CLICK_EVENT_DISTANCE_THRESHOLD = 115,

    /**
     * @brief 设置组件事件的响应区域，支持属性设置，属性重置和属性获取接口。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**说明：**
     * <br>设置时data数据大小无数量限制，均可以设置成功，但仅支持获取到20个。获取到的data数组顺序与设置顺序可能存在差异。
     * **参数：**
     * <ul>
     * <li>.data[0].i32</b>：适用于此响应区域的事件工具类型。参数类型为{@link ArkUI_ResponseRegionSupportedTool}。默认值：</li>
     * <li>ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_ALL。</li>
     * <li>.data[1].f32</b>：触摸点相对于组件左上角的x轴坐标，默认值：0.0，单位为vp。</li>
     * <li>.data[2].f32</b>：触摸点相对于组件左上角的y轴坐标，默认值：0.0，单位为vp。</li>
     * <li>.data[3].f32</b>：触摸热区的宽度，默认值：100.0，单位为百分比。</li>
     * <li>.data[4].f32</b>：触摸热区的高度，默认值：100.0，单位为百分比。</li>
     * <li>.data[5...].f32</b>：可以设置多个手势响应区域，顺序和上述一致。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.data[0].i32</b>：适用于此响应区域的事件工具类型。参数类型为{@link ArkUI_ResponseRegionSupportedTool}。默认值：</li>
     * <li>ARKUI_RESPONSE_REGIN_SUPPORTED_TOOL_ALL。</li>
     * <li>.data[1].f32</b>：触摸点相对于组件左上角的x轴坐标，默认值：0.0，单位为vp。</li>
     * <li>.data[2].f32</b>：触摸点相对于组件左上角的y轴坐标，默认值：0.0，单位为vp。</li>
     * <li>.data[3].f32</b>：触摸热区的宽度，默认值：100.0，单位为百分比。</li>
     * <li>.data[4].f32</b>：触摸热区的高度，默认值：100.0，单位为百分比。</li>
     * <li>.data[5...].f32</b>：可以设置多个手势响应区域，顺序和上述一致。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     * @since 23
     */
    NODE_RESPONSE_REGION_LIST = 116,

    /**
     * @brief 定义独占事件属性，该属性可根据需要通过API进行设置、重置和获取。
     * <br>作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * **参数：**
     * <ul>
     * <li>.value[0].i32</b>：取值范围为1或0。1表示设置组件独占，0表示组件未设置独占属性。</li>
     * </ul>
     * **返回：**
     * <ul>
     * <li>.value[0].i32</b>：取值范围为1或0。1表示设置组件独占，0表示组件未设置独占属性。</li>
     * </ul>
     *
     * @ingroup Interaction [交互属性]
     *
     * @since 23
     */
    NODE_MONOPOLIZE_EVENTS = 117,

    /**
     * @brief 设置组件在链条中的权重，用于重新布局构成链条的组件。
     * 该属性可以通过 API 根据需要进行设置、重置和获取。
     *
     * 用于设置该属性的 {@link ArkUI_AttributeItem} 参数格式为：
     *
     * .value[0].f32: 水平方向的 ChainWeight。
     *
     * .value[1].f32: 垂直方向的 ChainWeight。
     *
     *
     * 返回值 {@link ArkUI_AttributeItem} 的格式为：
     *
     * .value[0].f32: 水平方向的 ChainWeight。
     *
     * .value[1].f32: 垂直方向的 ChainWeight。
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_CHAIN_WEIGHT = 118,

    /**
     * @brief 扩展组件的布局安全区域，
     * 支持属性设置、属性重置和属性获取。
     *
     * 属性设置方法 {@link ArkUI_AttributeItem} 参数格式：
     * .value[0].u32: 要扩展组件布局安全区域的区域类型。默认值是 LayoutSafeAreaType.SYSTEM。{@link ArkUI_LayoutSafeAreaType}，
     * 例如，ARKUI_LAYOUT_SAFE_AREA_TYPE_SYSTEM；
     * .value[1].u32: 要忽略布局安全区域的边集。默认值是 LayoutSafeAreaEdge.ALL。{@link ArkUI_LayoutSafeAreaEdge}；
     * 例如：ARKUI_LAYOUT_SAFE_AREA_EDGE_TOP | ARKUI_LAYOUT_SAFE_AREA_EDGE_START；
     *
     * 属性获取方法返回值 {@link ArkUI_AttributeItem} 格式：
     * .value[0].u32: 要扩展组件布局安全区域的区域类型。
     * .value[1].u32: 要忽略布局安全区域的边集。
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_IGNORE_LAYOUT_SAFE_AREA = 119,

    /**
     * @brief 当 BorderStyle 为 dashed 时，定义虚线的长度，可以通过 API 根据需要进行设置、重置和获取。
     *
     * 设置属性的 {@link ArkUI_AttributeItem} 参数格式：
     * .value[0].f32: 顶部边的虚线长度。
     * .value[1].f32: 右侧边的虚线长度。
     * .value[2].f32: 底部边的虚线长度。
     * .value[3].f32: 左侧边的虚线长度。
     *
     * 返回值 {@link ArkUI_AttributeItem} 的格式：
     * .value[0].f32: 顶部边的虚线长度。
     * .value[1].f32: 右侧边的虚线长度。
     * .value[2].f32: 底部边的虚线长度。
     * .value[3].f32: 左侧边的虚线长度。
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_DASH_WIDTH = 120,

    /**
     * @brief 当 BorderStyle 为 dashed 时，定义虚线之间的间隔，可以通过 API 根据需要进行设置、重置和获取。
     *
     * 设置属性的 {@link ArkUI_AttributeItem} 参数格式：
     * .value[0].f32: 顶部边的虚线间隔。
     * .value[1].f32: 右侧边的虚线间隔。
     * .value[2].f32: 底部边的虚线间隔。
     * .value[3].f32: 左侧边的虚线间隔。
     *
     * 返回值 {@link ArkUI_AttributeItem} 的格式：
     * .value[0].f32: 顶部边的虚线间隔。
     * .value[1].f32: 右侧边的虚线间隔。
     * .value[2].f32: 底部边的虚线间隔。
     * .value[3].f32: 左侧边的虚线间隔。
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_DASH_GAP = 121,

    /**
     * @brief 定义 Stack 容器中子组件的对齐规则，可以通过 API 根据需要进行设置、重置和获取。
     *
     * 设置属性的 {@link ArkUI_AttributeItem} 参数格式：
     * .value[0].i32: 对齐（LocalizedAlignment）模式。数据类型为 {@link ArkUI_LocalizedAlignment}。
     * 默认值为 <b>ARKUI_LOCALIZED_ALIGNMENT_CENTER</b>。
     *
     * 返回值 {@link ArkUI_AttributeItem} 的格式：
     * .value[0].i32: 对齐（LocalizedAlignment）模式。数据类型为 {@link ArkUI_LocalizedAlignment}。
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_LAYOUT_GRAVITY = 122,

    /**
     * @brief 设置圆角渲染类型的API参数格式：
     *
     * .value[0].i32: 绘制圆角的渲染类型。数据类型为{@link ArkUI_RenderStrategy}。
     * 默认值为ARKUI_RENDERSTRATEGY_FAST。
     *
     * 返回值{@link ArkUI_AttributeItem}的格式：
     * .value[0].i32: 绘制圆角的渲染类型。数据类型为{@link ArkUI_RenderStrategy}。
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_BORDER_RADIUS_TYPE = 123,

    /**
     * @brief Defines the next accessibility focus id of current component for accessibility processing to find
     * the next focus component. This attribute can be set, reset, and obtained as required through APIs.
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
     * @brief Sets the accessibility default focus flag for accessibility services to find the default focus component.
     * This attribute can be set, reset, and obtained as required through APIs.
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
     * @brief 定义系统材质属性，可通过API设置、重置、获取。 
     * 只有支持systemMaterial的设备才能使用该属性。否则，在设置此属性时，则返回错误码{@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED}。
     * 通过{@link OH_ArkUI_NativeModule_GetSystemMaterialSupported}可以判断设备是否支持材质。
     * 材料视效在不同计算能力水平的设备上表现不同。
     * 级别由{@link ArkUI_MaterialLevel}定义，可以通过
     * {@链接OH_ArkUI_NativeModule_GetGlobalMaterialLevel}。
     * 在计算能力级别为ARKUI_MATERIAL_LEVEL_SMOOTH的设备上，它会影响属性，例如
     * 背景颜色，边框宽度，边框颜色，阴影。
     * 在计算能力等级为rkUI_MATERIAL_LEVEL_EXQUISITE或rkUI_MATERIAL_LEVEL_GENTLE的设备上，
     * 影响阴影属性，在系统材质层添加滤镜效果，可以产生效果
     * 类似于玻璃。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .object：系统材质对象。参数类型为{@link ArkUI_ImmersiveMaterialHandle}。\n
     * \n
     * 返回值{@link ArkUI_AttributeItem}格式：\n
     * .object：系统材质对象。参数类型为{@link ArkUI_ImmersiveMaterialHandle}。\n
     * 返回值的ArkUI_ImmersiveMaterialHandle对象是指向静态成员的指针，所以不要通过调用{@链接OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy}释放返回的对象。\n
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
     */
    NODE_IMMUTABLE_FONT_WEIGHT = 1030,

    /**
     * @brief 文本行数属性，支持属性获取接口。
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本行数。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
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
     * @since 22
     *
     * @ingroup Text Display[文本显示]
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
     * @ingroup Text Display
     * @since 22
     */
    NODE_TEXT_ENABLE_SELECTED_DATA_DETECTOR = 1038,

    /**
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
     * @since 22
     *
     * @ingroup Text Display[文本显示]
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
     * @since 22
     *
     * @ingroup Text Display[文本显示]
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
     * @since 22
     *
     * @ingroup Text Display[文本显示]
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
     */
    NODE_TEXT_FALLBACK_LINE_SPACING= 1050,

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
     */
    NODE_TEXT_DIRECTION = 1052,

    /**
     * @brief 用于设置文本选中状态下的拖拽预览样式。
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
     * @ingroup Text Display
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
     * @brief 设置Text组件是否启用行尾标点符号悬挂，支持属性设置、属性重置和属性获取。适用于中文排版场景，将行尾标点符号外挂显示以优化排版效果。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>

     * <li>.value[0].i32：是否启用行尾标点符号悬挂。\n
     * 1表示启用标点符号悬挂，0表示不启用标点符号悬挂。默认值为0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>

     * <li>.value[0].i32：是否启用行尾标点符号悬挂。\n
     * 1表示启用标点符号悬挂，0表示不启用标点符号悬挂。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 26.0.0
     */
    NODE_TEXT_PUNCTUATION_OVERFLOW = 1055,

    /**
     * @brief 定义文本块中每行的尾部缩进。适用于实现特殊排版效果，如诗歌排版、引用文本对齐等需要控制每行尾部空间。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>



     * <li>.value[i].f32：表示第i行文本的尾部缩进值，单位为vp。取值范围：[0, +∞)，传入负数时按默认值0处理。 \n
     * 当.size大小为1时，所有行共享相同的尾部缩进.value[0].f32；当.size大于1时，第i行使用.value[i].f32； \n
     * 当文本行数超过.size，则超出部分复用.value[.size - 1].f32。</li>
     * <li>.size：表示有效缩进值的数量，即 .value 数组中实际使用的元素个数。取值范围：正整数（大于0）。传入0或负数时参数不生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[i].f32：第i个尾部缩进值，单位为vp。</li>
     * <li>.size：表示有效缩进值的数量，即.value数组中实际使用的元素个数。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 26.0.0
     */
    NODE_TEXT_TAIL_INDENTS = 1056,

    /**
     * @brief 文本内容属性，支持属性设置、属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：表示span的文本内容。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：表示span的文本内容。</li>
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
     */
    NODE_SPAN_FONT_WEIGHT = 2004,

    /**
     * @brief imageSpan组件图片地址属性，支持属性设置、属性重置和属性获取接口。
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
     */
    NODE_IMAGE_SPAN_SUPPORT_SVG2 = 3005,

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
     * @brief Defines how the image is resized to fit its container.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: how the image is resized to fit its container. The value is an enum of
     * {@link ArkUI_ObjectFit}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: how the image is resized to fit its container. The value is an enum of
     * {@link ArkUI_ObjectFit}.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_OBJECT_FIT,

    /**
     * @brief Defines the interpolation effect of the image.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: interpolation effect of the image. The value is an enum of
     * {@link ArkUI_ImageInterpolation}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: interpolation effect of the image. The value is an enum of
     * {@link ArkUI_ImageInterpolation}.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_INTERPOLATION,

    /**
     * @brief Defines how the image is repeated.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: how the image is repeated. The value is an enum of {@link ArkUI_ImageRepeat}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: how the image is repeated. The value is an enum of {@link ArkUI_ImageRepeat}.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_OBJECT_REPEAT,

    /**
     * @brief Defines the color filter of the image.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32 to .value[19].f32: filter matrix array.</li>
     * <li>.size: 5 x 4 filter array size.</li>
     * <li>.object: the pointer to OH_Drawing_ColorFilter. Either .value or .object must be set.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32 to .value[19].f32: filter matrix array.</li>
     * <li>.size: 5 x 4 filter array size.</li>
     * <li>.object: the pointer to OH_Drawing_ColorFilter.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_COLOR_FILTER,

    /**
     * @brief Defines the auto resize attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to resize the image source.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to resize the image source.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_AUTO_RESIZE,

    /**
     * @brief Defines the placeholder image source.
     * This attribute can be set, reset, and obtained as required through APIs.
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
     * @ingroup Image
     */
    NODE_IMAGE_ALT,

    /**
     * @brief Defines whether the image is draggable.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the image is draggable. The value <b>true</b> means that the image is draggable.</li>
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
     * @brief Defines the image rendering mode. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: The parameter type is {@link ArkUI_ImageRenderMode}.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: The parameter type is {@link ArkUI_ImageRenderMode}.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_RENDER_MODE,

    /**
     * @brief Defines whether the image display size follows the image source size.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to follow the image source size. The value <b>true</b> means to follow.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to follow the image source size. The value <b>true</b> means to follow.</li>
     * </ul>
     *
     * @ingroup Image
     */
    NODE_IMAGE_FIT_ORIGINAL_SIZE,

    /**
     * @brief Defines the fill color of the image.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].u32: fill color, in 0xARGB format. For example, 0xFFFF0000 indicates red.</li>
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
     * @brief 图片拉伸时，支持通过设置边框大小或者使用矩阵方格对象调整其大小，1）设置边框大小可以设置left/top/right/bottom宽度，2）设置矩阵方格对象：该对象是通过图形侧的接口创建，并将对象地址传入。
     * 接口调用时需要保证设置和获取的参数类型是相同的。
     *
     * @ingroup Image
     */
    NODE_IMAGE_RESIZABLE,

    /**
     * @brief 定义Image是否同步加载 
     * 这个属性包含设置，重置，获取接口
     *
     * @ingroup Image
     * @since 20
     */
    NODE_IMAGE_SYNC_LOAD = 4012,

    /**
     * @brief 定义图片的解码尺寸属性。支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数ArkUI_AttributeItem格式：
     *
     * .value[0].i32 表示图片解码的宽，单位px。
     *
     * .value[1].i32 表示图片解码的高，单位px。
     *
     * 属性获取方法返回值ArkUI_AttributeItem格式：
     *
     * .value[0].i32 表示图片解码的宽，单位px。
     *
     * .value[1].i32 表示图片解码的高，单位px。
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_SOURCE_SIZE = 4013,

    /**
     * @brief 支持使用浮点数实现仿射图像变换。
     * 该属性可以通过API根据需要设置、重置和获取。
     * set和get的参数类型应该是相同的。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0....f32表示16个浮点数。\n
     *
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0....f32表示16个浮点数。\n
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_IMAGE_MATRIX = 4014,

    /**
     * @brief Defines the image follow text direction attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the image follows the text direction.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the image follows the text direction.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_MATCH_TEXT_DIRECTION = 4015,

    /**
     * @brief 定义图片复制粘贴属性。支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数ArkUI_AttributeItem格式：
     *
     * .value[0].i32：复制粘贴方式ArkUI_CopyOptions，默认值为ARKUI_COPY_OPTIONS_NONE；
     *
     * 属性获取方法返回值ArkUI_AttributeItem格式：
     *
     * .value[0].i32：复制粘贴方式ArkUI_CopyOptions。
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_COPY_OPTION = 4016,

    /**
     * @brief Defines the image AI analysis enable attribute.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable AI analysis for the image.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to enable AI analysis for the image.</li>
     * </ul>
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_ENABLE_ANALYZER = 4017,

    /**
     * @brief 定义图片显示动态范围属性。支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数ArkUI_AttributeItem格式：
     *
     * .value[0].i32：动态范围类型ArkUI_DynamicRangeMode，默认值为
     *
     * ARKUI_DYNAMIC_RANGE_MODE_STANDARD；
     *
     * 属性获取方法返回值ArkUI_AttributeItem格式：
     *
     * .value[0].i32：动态范围类型ArkUI_DynamicRangeMode。
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_DYNAMIC_RANGE_MODE = 4018,

    /**
     * @brief 定义图片显示动态范围的亮度属性。支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数ArkUI_AttributeItem格式：
     *
     * .value[0].f32：动态范围亮度，值的范围[0, 1]。
     *
     * 属性获取方法返回值ArkUI_AttributeItem格式：
     *
     * .value[0].f32：动态范围亮度，值的范围[0, 1]。
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_HDR_BRIGHTNESS = 4019,

    /**
     * @brief 定义图片显示方向属性。支持属性设置，属性重置和属性获取接口。
     *
     * 属性设置方法参数ArkUI_AttributeItem格式：
     *
     * .value[0].i32：动态范围类型ArkUI_Orientation，默认值为ARKUI_ORIENTATION_UP；
     *
     * 属性获取方法返回值ArkUI_AttributeItem格式：
     *
     * .value[0].i32：动态范围类型ArkUI_Orientation。
     *
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_ORIENTATION = 4020,

    /**
     * @brief Defines the range of SVG parsing capabilities supported through an enable switch.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: enable switch.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: enable switch.</li>
     * </ul>
     *
     * @ingroup Image
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
     * @ingroup Image
     * @since 21
     */
    NODE_IMAGE_CONTENT_TRANSITION = 4022,

    /**
     * @brief Defines the placeholder image during loading process.
     * This attribute can be set, reset, and obtained as required through APIs.
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
     * @ingroup Image
     * @since 22
     */
    NODE_IMAGE_ALT_PLACEHOLDER = 4023,

    /**
     * @brief Defines the placeholder image when loading fails.
     * This attribute can be set, reset, and obtained as required through APIs.
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
     * @ingroup Image
     * @since 22
     */
    NODE_IMAGE_ALT_ERROR = 4024,

    /**
     * @brief 通过开关配置图片边缘抗锯齿使能；true-开启抗锯齿，false-不开启，默认不开启抗锯齿。
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
     * @brief Defines the color of the circular slider for the component of the switch type.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: color of the circular slider, in 0xARGB format. For example, 0xFFFF0000 indicates red.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: color of the circular slider, in 0xARGB format.</li> \n
     * </ul>
     *
     * @ingroup Toggle
     */
    NODE_TOGGLE_SWITCH_POINT_COLOR,

    /**
     * @brief Defines the toggle switch value. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: whether to enable the toggle. The value <b>true</b> means to enable the toggle.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: whether to enable the toggle.</li> \n
     * </ul>
     *
     * @ingroup Toggle
     */
    NODE_TOGGLE_VALUE,

    /**
     * @brief Defines the color of the component when it is deselected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     *<li>.value[0].u32: background color, in 0xARGB format. For example, 0xFFFF0000 indicates red.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format.</li> \n
     * </ul>
     *
     * @ingroup Toggle
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
     * @brief 光标颜色属性，支持属性设置，属性重置和属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：光标颜色数值，0xargb格式，形如 0xFFFF0000 表示红色。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：光标颜色数值，0xargb格式。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     * @brief 无输入时默认提示文本的颜色属性，支持属性设置，属性重置和属性获取接口。


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
     * @ingroup Text Input[文本输入]
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
     * @brief 输入框文本选中时的背景色属性，支持属性设置，属性重置和属性获取接口。


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
     * @ingroup Text Input[文本输入]
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
     * @brief 获取已编辑文本内容的行数。
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：已编辑文本内容行数。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     * @brief 设置该属性后，通过该属性调整TextInput组件的字符间距。
     * 接口支持设置，重置以及获取该属性。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：设置letterSpacing的值，默认单位fp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：获取letterSpacing的值，默认单位fp。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     */
    NODE_TEXT_INPUT_LINE_HEIGHT = 7037,

    /**
     * @brief 开启选中词文本识别。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32: 开启选中词文本识别，true表示开启识别，false表示关闭识别。</li>
     * </ul>
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32: 是否开启选中词文本识别。</li>
     * </ul>
     *
     * @ingroup Text Input
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
     */
    NODE_TEXT_INPUT_SHOW_COUNTER = 7040,

    /**
     * @brief 用于设置或获取文本输入控制器。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：文本内容基础控制器。参数类型为{@link ArkUI_TextContentBaseController}。</li>

     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：文本内容基础控制器。参数类型为{@link ArkUI_TextContentBaseController}。</li>

     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 23
     */
    NODE_TEXT_INPUT_TEXT_CONTENT_CONTROLLER_BASE = 7041,

    /**
     * @brief 设置单行文本输入框中文本省略位置，支持属性设置，属性重置，属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>

     * <li>.value[0].i32：参数类型{@link ArkUI_EllipsisMode}。默认值为ARKUI_ELLIPSIS_MODE_END。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：参数类型{@link ArkUI_EllipsisMode}。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     */
    NODE_TEXT_INPUT_FALLBACK_LINE_SPACING= 7046,

    /**
     * @brief 单行输入框的文本排版方向。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本的排版方向，取{@link ArkUI_TextDirection}枚举值。默认值为ARKUI_TEXT_DIRECTION_DEFAULT。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本的排版方向，对应取值及含义请参考{@link ArkUI_TextDirection}枚举值。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     * @brief 单行文本输入框中文本超长时的显示方式属性，支持属性设置，属性重置，属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本超长时的显示方式{@link ArkUI_TextOverflow}。内联模式非编辑态下默认值为ARKUI_TEXT_OVERFLOW_ELLIPSIS，内联模式编辑态下默认值为ARKUI_TEXT_OVERFLOW_CLIP。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本超长时的显示方式{@link ArkUI_TextOverflow}。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     */
    NODE_TEXT_INPUT_RADIAL_GRADIENT = 7052,

    /**
     * @brief 设置TextInput组件是否启用行尾标点符号悬挂，支持属性设置，属性重置和属性获取。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用行尾标点符号悬挂。1表示启用标点符号悬挂，0表示不启用标点符号悬挂。默认值为0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用行尾标点符号悬挂。0表示不启用标点符号悬挂，1表示启用标点符号悬挂。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_PUNCTUATION_OVERFLOW = 7053,

    /**
     * @brief 多行文本输入框的默认提示文本内容属性，支持属性设置，属性重置和属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：默认提示文本的内容。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：默认提示文本的内容。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_PLACEHOLDER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_AREA,

    /**
     * @brief 多行文本输入框的默认文本内容属性，支持属性设置，属性重置和属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：默认文本的内容。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：默认文本的内容。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_TEXT,

    /**
     * @brief 输入框支持的最大文本数属性，支持属性设置，属性重置和属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：最大文本数的数字。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：最大文本数的数字。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_MAX_LENGTH,

    /**
     * @brief 无输入时默认提示文本的颜色属性，支持属性设置，属性重置和属性获取接口。


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
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_PLACEHOLDER_COLOR,

    /**
     * @brief 无输入时默认提示文本的字体配置（包括大小、字重、样式、字体列表）属性，支持属性设置，属性重置和属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0]?.f32：可选字体大小数值，默认值16.0，单位为fp。</li>

     * <li>.value[1]?.i32：可选字体样式{@link ArkUI_FontStyle}，默认值为ARKUI_FONT_STYLE_NORMAL。</li>

     * <li>.value[2]?.i32：可选字体粗细样式{@link ArkUI_FontWeight}，默认值为ARKUI_FONT_WEIGHT_NORMAL。</li>
     * <li>?.string：字体族内容，多个字体族之间使用逗号分隔，形如“字重；字体族1，字体族2”。</li>



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
    NODE_TEXT_AREA_PLACEHOLDER_FONT,

    /**
     * @brief 光标颜色属性，支持属性设置，属性重置和属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：光标颜色数值，0xargb格式，形如 0xFFFF0000 表示红色。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：光标颜色数值，0xargb格式。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     * @brief 输入框的类型属性，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：输入框类型枚举{@link ArkUI_TextAreaType}，默认值为ARKUI_TEXTAREA_TYPE_NORMAL。</li>

     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：输入框类型枚举{@link ArkUI_TextAreaType}。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     * @brief 输入框文本选中时的背景色属性，支持属性设置，属性重置和属性获取接口。


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
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_SELECTED_BACKGROUND_COLOR,

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
    NODE_TEXT_AREA_ENTER_KEY_TYPE,

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
     * @brief 获取已编辑文本内容的行数。
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：已编辑文本内容行数。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_CONTENT_LINE_COUNT,

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
    NODE_TEXT_AREA_TEXT_SELECTION,

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
    NODE_TEXT_AREA_ENABLE_AUTO_FILL,

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
    NODE_TEXT_AREA_CONTENT_TYPE,

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
     * @brief 设置该属性后，通过该属性调整TextArea组件的字符间距。
     * 接口支持设置，重置以及获取该属性。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：设置letterSpacing的值，默认单位fp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：获取letterSpacing的值，默认单位fp。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     */
    NODE_TEXT_AREA_HALF_LEADING = 8025,

    /**
     * @brief 设置输入框拉起的键盘样式。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：键盘样式，参数类型{@link ArkUI_KeyboardAppearance}。默认值ARKUI_KEYBOARD_APPEARANCE_NONE_IMMERSIVE。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：键盘样式，参数类型{@link ArkUI_KeyboardAppearance}。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     * @since 20
     *
     * @ingroup Text Input[文本输入]
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
     */
    NODE_TEXT_AREA_LINE_HEIGHT = 8031,

    /**
     * @brief 定义文本输入框滚动条状态。支持属性设置、属性重置和属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本控制滚动条状态。参数类型为{@link ArkUI_BarState}。默认值为ARKUI_BAR_STATE_AUTO。</li>


     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：文本控制滚动条状态。参数类型为{@link ArkUI_BarState}。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 22
     */
    NODE_TEXT_AREA_BAR_STATE = 8032,

    /**
     * @brief 开启选中词文本识别。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32: 开启选中词文本识别，true表示开启识别，false表示关闭识别。</li>
     * </ul>
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32: 是否开启选中词文本识别。</li>
     * </ul>
     *
     * @ingroup Text Input
     * @since 22
     */
    NODE_TEXT_AREA_ENABLE_SELECTED_DATA_DETECTOR = 8033,

    /**
     * @brief 设置输入框滚动条颜色，支持属性设置，属性重置和属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：滚动条颜色数值。0xargb类型。默认值：0x66182431，显示为灰色。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：滚动条颜色数值。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     */
    NODE_TEXT_AREA_CUSTOM_KEYBOARD = 8036,

    /**
     * @brief 用于设置或获取文本输入控制器。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：文本内容基础控制器。参数类型为{@link ArkUI_TextContentBaseController}。</li>

     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：文本内容基础控制器。参数类型为{@link ArkUI_TextContentBaseController}。</li>

     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 23
     */
    NODE_TEXT_AREA_TEXT_CONTENT_CONTROLLER_BASE = 8037,

    /**
     * @brief 设置单行文本输入框中文本省略位置，支持属性设置，属性重置，属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>

     * <li>.value[0].i32：参数类型{@link ArkUI_EllipsisMode}。默认值为ARKUI_ELLIPSIS_MODE_END。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：参数类型{@link ArkUI_EllipsisMode}。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     */
    NODE_TEXT_AREA_ORPHAN_CHAR_OPTIMIZATION = 8039,

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
     */
    NODE_TEXT_AREA_COMPRESS_LEADING_PUNCTUATION = 8040,

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
     */
    NODE_TEXT_AREA_FALLBACK_LINE_SPACING= 8042,

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
     */
    NODE_TEXT_AREA_HORIZONTAL_SCROLLING = 8043,

    /**
     * @brief 单行输入框的文本排版方向。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本的排版方向，取{@link ArkUI_TextDirection}枚举值。默认值为ARKUI_TEXT_DIRECTION_DEFAULT。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本的排版方向，对应取值及含义请参考{@link ArkUI_TextDirection}枚举值。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 23
     */
    NODE_TEXT_AREA_DIRECTION = 8044,

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
    NODE_TEXT_AREA_SELECTED_DRAG_PREVIEW_STYLE = 8045,

    /**
     * @brief 多行文本输入框中文本超长时的显示方式属性，支持属性设置，属性重置，属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本超长时的显示方式{@link ArkUI_TextOverflow}。默认值为ARKUI_TEXT_OVERFLOW_CLIP。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：表示文本超长时的显示方式{@link ArkUI_TextOverflow}。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 24
     */
    NODE_TEXT_AREA_TEXT_OVERFLOW = 8046,

    /**
     * @brief 定义多行输入框的文本装饰线样式与颜色，支持属性设置、属性重置和属性获取接口。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>

     * <li>.object：装饰样式配置项，为可选参数。参数类型为{@link OH_ArkUI_DecorationStyleOptions}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object：装饰样式配置项。参数类型为{@link OH_ArkUI_DecorationStyleOptions}。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     */
    NODE_TEXT_AREA_RADIAL_GRADIENT = 8049,

    /**
     * @brief 设置TextInput组件是否启用行尾标点符号悬挂，支持属性设置，属性重置和属性获取。


     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用行尾标点符号悬挂。1表示启用标点符号悬挂，0表示不启用标点符号悬挂。默认值为0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用行尾标点符号悬挂。0表示不启用标点符号悬挂，1表示启用标点符号悬挂。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     * @brief Sets the button type. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: button type. The parameter type is {@link ArkUI_ButtonType}.
     * The default value is <b>ARKUI_BUTTON_TYPE_CAPSULE</b>.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: button type. The parameter type is {@link ArkUI_ButtonType}.
     * The default value is <b>ARKUI_BUTTON_TYPE_CAPSULE</b>.</li> \n
     * </ul>
     *
     * @ingroup Button
     */
    NODE_BUTTON_TYPE,

    /**
     * @brief Defines the minimum font scale attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: minimum font scale, in fp.</li>
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: minimum font scale, in fp.</li>
     * </ul>
     *
     * @ingroup Button
     * @since 18
     */
    NODE_BUTTON_MIN_FONT_SCALE,

    /**
     * @brief Defines the maximum font scale attribute, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: maximum font scale, in fp.</li>
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: maximum font scale, in fp.</li>
     * </ul>
     *
     * @ingroup Button
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
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: whether the check box is selected.
     * The value <b>1</b> means that the check box is selected, and <b>0</b> means the opposite.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: The value <b>1</b> means that the check box is selected, and <b>0</b> means the opposite.</li> \n
     * </ul>
     *
     * @ingroup Checkbox
     */
    NODE_CHECKBOX_SELECT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CHECKBOX,

    /**
     * @brief Defines the color of the check box when it is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: color of the check box when it is selected, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: color of the check box when it is selected, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>
     * </ul>
     *
     * @ingroup Checkbox
     */
    NODE_CHECKBOX_SELECT_COLOR,

    /**
     * @brief Defines the border color of the check box when it is not selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>
     * </ul>
     *
     * @ingroup Checkbox
     */
    NODE_CHECKBOX_UNSELECT_COLOR,

    /**
     * @brief Defines the internal icon style of the check box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>\n
     * <li>.value[1]?.f32: size of the internal mark, in vp. Optional.</li>\n
     * <li>.value[2]?.f32: stroke width of the internal mark, in vp. Optional. The default value is <b>2</b>.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>\n
     * <li>.value[1].f32: size of the internal mark, in vp.</li> \n
     * <li>.value[2].f32: stroke width of the internal mark, in vp. The default value is <b>2</b>.</li> \n
     * </ul>
     *
     * @ingroup Checkbox
     */
    NODE_CHECKBOX_MARK,

    /**
     * @brief Defines the shape of the check box.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: component shape. The parameter type is {@link ArkUI_CheckboxShape}.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: component shape. The parameter type is {@link ArkUI_CheckboxShape}.</li>
     * </ul>
     *
     * @ingroup Checkbox
     */
    NODE_CHECKBOX_SHAPE,

    /**
     * @brief Defines the name of the checkbox.
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
     * @ingroup Checkbox
     * @since 15
     */
    NODE_CHECKBOX_NAME,

    /**
     * @brief Defines the name of the checkbox.
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
     * @brief Specifies the size of the <b>XComponent</b> component. This attribute is read-only.
     * Attempting to modify the size through {@link setAttribute} will have no effect.
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].u32: width, in px.</li>
     * <li>.value[1].u32: height, in px.</li>
     * </ul>
     *
     * @ingroup XComponent
     * @since 12
     */
    NODE_XCOMPONENT_SURFACE_SIZE,
    /**
     * @brief Defines the rectangle information of surface created by the <b><XComponent></b> component.
     * This attribute can be set and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: The horizontal offset of the surface relative to XComponent, in pixels.</li>
     * <li>.value[1].i32: The vertical offset of the surface relative to XComponent, in pixels.</li>
     * <li>.value[2].i32: The width of the surface created by XComponent, in pixels.</li>
     * <li>.value[3].i32: The height of the surface created by XComponent, in pixels.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: The horizontal offset of the surface relative to XComponent, in pixels.</li>
     * <li>.value[1].i32: The vertical offset of the surface relative to XComponent, in pixels.</li>
     * <li>.value[2].i32: The width of the surface created by XComponent, in pixels.</li>
     * <li>.value[3].i32: The height of the surface created by XComponent, in pixels.</li>
     * </ul>
     *
     * @ingroup XComponent
     * @since 18
     */
    NODE_XCOMPONENT_SURFACE_RECT,
    /**
     * @brief Defines whether to enable the AI analyzer for the <b><XComponent></b> component.
     * This attribute can be set and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>value[0].i32: The parameter type is 1 or 0.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>value[0].i32: The parameter type is 1 or 0.</li>
     * </ul>
     *
     * @ingroup XComponent
     * @since 18
     */
    NODE_XCOMPONENT_ENABLE_ANALYZER,

    /**
     * @brief 设置日期选择器组件的日期是否显示农历，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否显示农历，默认值0。0表示不展示农历，1表示展示农历。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否显示农历。返回0表示不展示农历，返回1表示展示农历。</li>
     * </ul>
     *
     *
     * @ingroup Datepicker[日期选择器]
     */
    NODE_DATE_PICKER_LUNAR = MAX_NODE_SCOPE_NUM * ARKUI_NODE_DATE_PICKER,

    /**
     * @brief 设置日期选择器组件选择器的起始日期，支持属性设置，属性重置和属性获取接口。设置的起始日期会限定日期选择的有效范围，超出范围的选中日期会自动调整。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：日期，默认值"1970-1-1"。格式：年-月-日，年份支持1或4位，月份和日期为1-2位数字。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：设置的起始日期，格式为年-月-日。</li>
     * </ul>
     *
     *
     * @ingroup Datepicker[日期选择器]
     */
    NODE_DATE_PICKER_START,

    /**
     * @brief 设置日期选择器组件选择器的结束日期，支持属性设置，属性重置和属性获取接口。设置的结束日期会限定日期选择的有效范围，超出范围的选中日期会自动调整。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：日期，默认值"2100-12-31"。格式：年-月-日，年份支持1或4位，月份和日期为1-2位数字。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：设置的结束日期，格式为年-月-日。</li>
     * </ul>
     *
     *
     * @ingroup Datepicker[日期选择器]
     */
    NODE_DATE_PICKER_END,

    /**
     * @brief 设置日期选择器组件选中项的日期，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：日期，默认值"2024-01-22"，未设置时使用默认值。格式：年-月-日，年份支持1或4位，月份和日期为1-2位数字。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：选中的日期，格式为年-月-日。</li>
     * </ul>
     *
     *
     * @ingroup Datepicker[日期选择器]
     */
    NODE_DATE_PICKER_SELECTED,

    /**
     * @brief 设置日期选择器组件的所有选项中最上和最下两个选项的文本颜色、字号、字体粗细，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1： 文本颜色，#ARGB类型。
     *  参数2： 文本大小，数字类型，单位fp。
     *  参数3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4： 文本字体列表，使用 ',' 进行分割。
     *  参数5： 文本样式，字符串枚举("normal", "italic")。
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。未设置时使用系统默认样式。
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1：文本颜色，#argb类型。
     *  参数2：文本大小，数字类型，单位fp。
     *  参数3：文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4：文本字体列表，使用 ',' 进行分割。
     *  参数5：文本样式，字符串枚举("normal", "italic")。
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal"。
     * </ul>
     *
     *
     * @ingroup Datepicker[日期选择器]
     */
    NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE,

    /**
     * @brief 设置日期选择器组件的所有选项中除了边缘项及选中项以外的文本颜色、字号、字体粗细，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1： 文本颜色，#argb类型。
     *  参数2： 文本大小，数字类型，单位fp。
     *  参数3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4： 文本字体列表，使用 ',' 进行分割。
     *  参数5： 文本样式，字符串枚举("normal", "italic")。
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。未设置时使用系统默认样式。
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1：文本颜色，#argb类型。
     *  参数2：文本大小，数字类型，单位fp。
     *  参数3：文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4：文本字体列表，使用 ',' 进行分割。
     *  参数5：文本样式，字符串枚举("normal", "italic")。
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal"。
     * </ul>
     *
     *
     * @ingroup Datepicker[日期选择器]
     */
    NODE_DATE_PICKER_TEXT_STYLE,

    /**
     * @brief 设置日期选择器组件的选中项的文本颜色、字号、字体粗细，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1： 文本颜色，#argb类型。
     *  参数2： 文本大小，数字类型，单位fp。
     *  参数3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4： 文本字体列表，使用 ',' 进行分割。
     *  参数5： 文本样式，字符串枚举("normal", "italic")。
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。未设置时使用系统默认样式。
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1：文本颜色，#argb类型。
     *  参数2：文本大小，数字类型，单位fp。
     *  参数3：文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4：文本字体列表，使用 ',' 进行分割。
     *  参数5：文本样式，字符串枚举("normal", "italic")。
     * 如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal"。
     * </ul>
     *
     *
     * @ingroup Datepicker[日期选择器]
     */
    NODE_DATE_PICKER_SELECTED_TEXT_STYLE,

    /**
     * @brief 设置要显示的日期选项列。DatePicker显示不同样式的日期列，支持属性设置，属性重置和属性获取接口。
     * 使用场景：根据应用需求选择合适的日期显示模式，如需要精确选择到日时使用年/月/日模式，只需要月份时使用年/月模式等。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：显示的日期列类型。参数类型{@link ArkUI_DatePickerMode}。默认值：完整的日期列（年、月、日）。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：当前设置的日期列类型枚举值，类型为{@link ArkUI_DatePickerMode}。</li>
     * </ul>
     *
     * @ingroup Datepicker[日期选择器]
     * @since 18
     */
    NODE_DATE_PICKER_MODE = 13007,

    /**
     * @brief 设置是否开启触控反馈。支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启触控反馈。1表示开启触控反馈，0表示不开启触控反馈。开启后，是否存在触控反馈取决于系统硬件支持情况。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启触控反馈。1表示开启触控反馈，0表示不开启触控反馈。</li>
     * </ul>
     *
     * @ingroup Datepicker[日期选择器]
     * @since 18
     */
    NODE_DATE_PICKER_ENABLE_HAPTIC_FEEDBACK = 13008,

    /**
     * @brief Picker组件可循环滚动属性，支持属性设置，属性重置和属性获取接口。
     * 使用场景：循环滚动适用于选项有限且希望提供快速选择体验的场景（如月份选择）；非循环滚动适用于选项有明确边界、需要限制用户选择范围的场景（如日期选择避免跨年混淆）。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否可循环。1表示可循环，0表示不可循环。默认值：1，设置异常值时使用默认值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示不可循环，1表示可循环。</li>
     * </ul>
     *
     * 说明：可循环情况下，年份随着月份的循环滚动进行联动加减，月份随着日的循环滚动进行联动加减。\n
     * 不可循环情况下，年/月/日到达本列的顶部或底部时，无法再进行滚动，年/月/日之间也无法再联动加减。
     *
     * @ingroup Datepicker[日期选择器]
     * @since 20
     */
    NODE_DATE_PICKER_CAN_LOOP = 13009,

    /**
     * @brief 设置时间选择器组件的选中项时间，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：时间。默认值：当前系统时间。设置格式：时:分或时-分（例：23:59或23-59）。返回格式：时,分,秒（例：23,59,0）。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：选中的时间。格式：时,分,秒，使用`,`分隔（例：23,59,0）。</li>
     * </ul>
     *
     * @ingroup Timepicker[时间选择器]
     */
    NODE_TIME_PICKER_SELECTED = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TIME_PICKER,

    /**
     * @brief 设置时间选择组件展示时间是否为24小时制，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否为24小时制，默认值：0。0表示展示时间为12小时制，1表示展示时间为24小时制。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否为24小时制。返回0表示展示时间为12小时制（对应false），返回1表示展示时间为24小时制（对应true）。</li>
     * </ul>
     *
     * @ingroup Timepicker[时间选择器]
     */
    NODE_TIME_PICKER_USE_MILITARY_TIME,

    /**
     * @brief 设置边缘项（以选中项为基准向上或向下的第二项）的文本样式，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1： 文本颜色，#argb类型。
     *  参数2： 文本大小，数字类型，单位fp。
     *  参数3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4： 文本字体列表，使用 ',' 进行分割。
     *  参数5： 文本样式，字符串枚举("normal", "italic")。
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。未设置时使用系统默认样式。
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1：文本颜色，#argb类型。
     *  参数2：文本大小，数字类型，单位fp。
     *  参数3：文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4：文本字体列表，使用 ',' 进行分割。
     *  参数5：文本样式，字符串枚举("normal", "italic")。
     * 如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal"。
     * </ul>
     *
     * @ingroup Timepicker[时间选择器]
     */
    NODE_TIME_PICKER_DISAPPEAR_TEXT_STYLE,

    /**
     * @brief 设置时间选择组件所有选项中除了边缘项及选中项以外的文本颜色、字号、字体粗细，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1： 文本颜色，#argb类型。
     *  参数2： 文本大小，数字类型，单位fp。
     *  参数3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4： 文本字体列表，使用 ',' 进行分割。
     *  参数5： 文本样式，字符串枚举("normal", "italic")。
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。未设置时使用系统默认样式。
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1：文本颜色，#argb类型。
     *  参数2：文本大小，数字类型，单位fp。
     *  参数3：文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4：文本字体列表，使用 ',' 进行分割。
     *  参数5：文本样式，字符串枚举("normal", "italic")。
     * 如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal"。
     * </ul>
     *
     * @ingroup Timepicker[时间选择器]
     */
    NODE_TIME_PICKER_TEXT_STYLE,

    /**
     * @brief 设置时间选择组件选中项的文本颜色、字号、字体粗细，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1： 文本颜色，#argb类型。
     *  参数2： 文本大小，数字类型，单位fp。
     *  参数3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4： 文本字体列表，使用 ',' 进行分割。
     *  参数5： 文本样式，字符串枚举("normal", "italic")。
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。未设置时使用系统默认样式。
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1：文本颜色，#argb类型。
     *  参数2：文本大小，数字类型，单位fp。
     *  参数3：文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4：文本字体列表，使用 ',' 进行分割。
     *  参数5：文本样式，字符串枚举("normal", "italic")。
     * 如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal"。
     * </ul>
     *
     * @ingroup Timepicker[时间选择器]
     */
    NODE_TIME_PICKER_SELECTED_TEXT_STYLE,

    /**
     * @brief 设置时间选择器组件的起始时间，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：时间。默认值："0:0"。设置时仅支持时:分，使用`:`或`-`分隔（例：12:59或12-59）。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：设置的起始时间。格式：时:分:秒（例：0:0:0）。</li>
     * </ul>
     *
     * @ingroup Timepicker[时间选择器]
     * @since 18
     */
    NODE_TIME_PICKER_START = 14005,

    /**
     * @brief 设置时间选择器组件的结束时间，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：时间。默认值："23:59"。设置时仅支持时:分，使用`:`或`-`分隔（例：23:59或23-59）。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：设置的结束时间。格式：时:分:秒（例：23:59:0）。</li>
     * </ul>
     *
     * @ingroup Timepicker[时间选择器]
     * @since 18
     */
    NODE_TIME_PICKER_END = 14006,

    /**
     * @brief 在设置12小时制时，上午和下午的标识会根据小时数自动切换，支持属性设置、重置和获取；在24小时制时，该参数不生效。
     * 使用场景：适用于需要提供友好的12小时制选择体验的场景，例如用户滚动选择小时时，上午/下午标识自动跟随变化，无需用户手动切换。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：在12小时制时，设置上午和下午的标识是否会根据小时数自动切换，默认值：0。0表示不自动切换，1表示自动切换。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：在12小时制时，上午和下午的标识是否会根据小时数自动切换。返回0表示不自动切换（对应false），返回1表示自动切换（对应true）。</li>
     * </ul>
     *
     * @ingroup Timepicker[时间选择器]
     * @since 18
     */
    NODE_TIME_PICKER_ENABLE_CASCADE = 14007,

    /**
     * @brief 设置滑动选择文本选择器的选择列表，支持属性设置，属性重置和属性获取接口。
     * 使用场景：单列选择器适用于单一类别选择（如省份、品牌），多列选择器适用于多个独立类别组合选择（如省-市），多列联动选择器适用于有层级关系的选择场景（如省-市-区，第二列根据第一列自动更新）。
     * 需先设置该参数后，才能使用 NODE_TEXT_PICKER_OPTION_SELECTED 和 NODE_TEXT_PICKER_SELECTED_INDEX 设置选中项。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：使用的选择器类型{@link ArkUI_TextPickerRangeType}，默认值为ARKUI_TEXTPICKER_RANGETYPE_SINGLE。
     * ARKUI_TEXTPICKER_RANGETYPE_SINGLE适用于单列选择，ARKUI_TEXTPICKER_RANGETYPE_MULTI适用于多列独立选择，
     * ARKUI_TEXTPICKER_RANGETYPE_RANGE_CONTENT适用于单列带图片选择，ARKUI_TEXTPICKER_RANGETYPE_CASCADE适用于多列联动选择。</li>
     * <li>?.string：针对不同选择器类型有如下输入范式：1：单列选择器，入参格式为用分号分隔的一组字符串；
     * 2：多列选择器，支持多对纯文本字符串对，多对之间使用分号分隔，每对内部使用逗号分隔。不传此参数时不设置选择列表。</li>
     * <li>?.object：针对不同选择器类型有如下输入范式：
     * 1：单列支持图片的选择器，输入结构体为{@link ARKUI_TextPickerRangeContentArray}；
     * 2：多列联动选择器，输入结构体为{@link ARKUI_TextCascadePickerRangeContentArray}。不传此参数时不设置选择列表。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：使用的选择器类型{@link ArkUI_TextPickerRangeType}。</li>
     * <li>?.string：针对不同选择器类型有如下输出范式：1：单列选择器，输出格式为用分号分隔的一组字符串；2：多列选择器，输出多对纯文本字符串对，多对之间使用分号分隔，每对内部使用逗号分隔。</li>
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     */
    NODE_TEXT_PICKER_OPTION_RANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_PICKER,

    /**
     * @brief 设置滑动选择文本内容的组件默认选中项在数组中的索引值，支持属性设置，属性重置和属性获取接口。需先通过 NODE_TEXT_PICKER_OPTION_RANGE 设置选项列表后才能使用该参数。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：默认选中项在选择器选项数组中的索引值，取值范围为[0, length-1]。超出范围时抛出异常。多列选择器时，如存在多个索引值则逐个添加。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：选中项在选择器选项数组中的索引值，如存在多个索引值则逐个添加。</li>
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     */
    NODE_TEXT_PICKER_OPTION_SELECTED,

    /**
     * @brief 设置滑动选择文本内容的组件默认选中项的值，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：选中项的值，如存在多个值则逐个添加，用分号分隔。默认值：空字符串，未设置时使用默认值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：选中项的值，如存在多个值则逐个添加，用分号分隔。</li>
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     */
    NODE_TEXT_PICKER_OPTION_VALUE,

    /**
     * @brief 设置滑动选择文本内容的组件所有选项中最上和最下两个选项的文本颜色、字号、字体粗细，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1： 文本颜色，#argb类型；
     *  参数2： 文本大小，数字类型，单位fp；
     *  参数3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")；
     *  参数4： 文本字体列表，使用 ',' 进行分割；
     *  参数5： 文本样式，字符串枚举("normal", "italic")；
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。未设置时使用系统默认样式。
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1：文本颜色，#argb类型。
     *  参数2：文本大小，数字类型，单位fp。
     *  参数3：文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4：文本字体列表，使用 ',' 进行分割。
     *  参数5：文本样式，字符串枚举("normal", "italic")。
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal"。
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     */
    NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE,

    /**
     * @brief 设置滑动选择文本内容的组件所有选项中除了最上、最下及选中项以外的文本颜色、字号、字体粗细，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1： 文本颜色，#argb类型。
     *  参数2： 文本大小，数字类型，单位fp。
     *  参数3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4： 文本字体列表，使用 ',' 进行分割。
     *  参数5： 文本样式，字符串枚举("normal", "italic")。
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。未设置时使用系统默认样式。
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1：文本颜色，#argb类型。
     *  参数2：文本大小，数字类型，单位fp。
     *  参数3：文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4：文本字体列表，使用 ',' 进行分割。
     *  参数5：文本样式，字符串枚举("normal", "italic")。
     * 如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal"。
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     */
    NODE_TEXT_PICKER_TEXT_STYLE,

    /**
     * @brief 设置滑动选择文本内容的组件选中项的文本颜色、字号、字体粗细，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1： 文本颜色，#argb类型；
     *  参数2： 文本大小，数字类型，单位fp；
     *  参数3： 文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")；
     *  参数4： 文本字体列表，使用 ',' 进行分割；
     *  参数5： 文本样式，字符串枚举("normal", "italic")；
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。未设置时使用系统默认样式。
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：参数5个，格式为字符串，以 ';' 分割：</li>
     *  参数1：文本颜色，#argb类型。
     *  参数2：文本大小，数字类型，单位fp。
     *  参数3：文本粗细，字符串枚举("bold", "normal", "bolder", "lighter", "medium", "regular")。
     *  参数4：文本字体列表，使用 ',' 进行分割。
     *  参数5：文本样式，字符串枚举("normal", "italic")。
     *  如 "#ff182431;14;normal;Arial,HarmonyOS Sans;normal" 。
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     */
    NODE_TEXT_PICKER_SELECTED_TEXT_STYLE,

    /**
     * @brief 设置滑动选择文本内容的组件默认选中项的索引数组，支持属性设置，属性重置和属性获取接口。
     * 需先通过 NODE_TEXT_PICKER_OPTION_RANGE 设置选项列表后才能使用该参数。设置选项列表后，如未通过本参数设置索引数组，则默认选中各列的第1项。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0...].i32：默认选中项在选择器选项数组中的索引值数组。用于多列选择器时设置每列的默认选中项索引。默认值：每列均为0。取值范围：每列索引值为[0, 对应列长度-1]，超出范围时抛出异常。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0...].i32：当前选中的索引值数组，用于多列选择器时表示每列的选中项索引。</li>
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     */
    NODE_TEXT_PICKER_SELECTED_INDEX,

    /**
     * @brief Picker组件可循环滚动属性，支持属性设置，属性重置和属性获取接口。
     * 使用场景：循环滚动适用于选项有限且希望提供快速选择体验的场景（如省份选择）；非循环滚动适用于选项有明确边界、需要限制用户选择范围的场景（如数量选择避免误操作）。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示不可循环，1表示可循环。默认值：1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：0表示不可循环，1表示可循环。</li>
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     */
    NODE_TEXT_PICKER_CAN_LOOP,

    /**
     * @brief 设置Picker组件各选择项的高度，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：当前设置的选项高度值，单位为vp。默认值：40.0vp，未设置时使用默认值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：当前设置的选项高度值，单位为vp。</li>
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     */
    NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT,

    /**
     * @brief 设置是否开启触控反馈。支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启触控反馈。1表示开启触控反馈，0表示不开启触控反馈。开启后，是否存在触控反馈取决于系统硬件支持情况。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否开启触控反馈。1表示开启触控反馈，0表示不开启触控反馈。</li>
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     * @since 18
     */
    NODE_TEXT_PICKER_ENABLE_HAPTIC_FEEDBACK = 15010,

    /**
     * @brief 设置选中项的背景颜色和边框圆角。支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：背景颜色，采用 0xARGB 格式。其中A表示透明度(0x00完全透明~0xFF完全不透明)，
     * RGB表示颜色值(0x000000~0xFFFFFF)，每个字节取值范围0x00~0xFF。例如，0xFF1122FF表示完全不透明的蓝色。</li>
     * <li>.value[1].f32：左上角的圆角半径，单位为VP。</li>
     * <li>.value[2].f32：右上角的圆角半径，单位为VP。</li>
     * <li>.value[3].f32：左下角的圆角半径，单位为VP。</li>
     * <li>.value[4].f32：右下角的圆角半径，单位为VP。</li>
     * </ul>
     * <p>默认值：背景颜色：0x0C182431；圆角半径：24.0。</p>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：背景颜色，采用 0xARGB 格式，例如，<b>0xFF1122FF</b>。</li>
     * <li>.value[1].f32：左上角的圆角半径，单位为VP。</li>
     * <li>.value[2].f32：右上角的圆角半径，单位为VP。</li>
     * <li>.value[3].f32：左下角的圆角半径，单位为VP。</li>
     * <li>.value[4].f32：右下角的圆角半径，单位为VP。</li>
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     * @since 20
     */
    NODE_TEXT_PICKER_SELECTED_BACKGROUND_STYLE = 15011,

    /**
     * @brief 设置日历选中态底板圆角半径的参数，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：日历选中态底板圆角半径，默认值：16.0，单位为vp，表示底板样式为圆形。
     * 当输入参数为0.0时表示底板样式为直角矩形；当输入参数为(0.0, 16.0)时，底板样式为圆角矩形；当输入参数为负数或大于16.0时，恢复成默认值16.0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：日历选中态底板圆角半径，默认值：16.0，单位为vp，表示底板样式为圆形。取值范围[0.0, 16.0]，其中取值为0.0表示底板样式为直角矩形。</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     */
    NODE_CALENDAR_PICKER_HINT_RADIUS = MAX_NODE_SCOPE_NUM * ARKUI_NODE_CALENDAR_PICKER,

    /**
     * @brief 设置日历选择选中日期的参数，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：选中的年。默认值：当前系统年份。传入无效值时使用默认值。</li>
     * <li>.value[1].u32：选中的月。默认值：当前系统月份。传入无效值时使用默认值。</li>
     * <li>.value[2].u32：选中的日。默认值：当前系统日期。传入无效值时使用默认值。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：选中的年。</li>
     * <li>.value[1].u32：选中的月。</li>
     * <li>.value[2].u32：选中的日。</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     */
    NODE_CALENDAR_PICKER_SELECTED_DATE,

    /**
     * @brief 设置日历选择器与入口组件的对齐方式，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：对齐方式类型，参数类型{@link ArkUI_CalendarAlignment}。用于设置日历选择器相对入口组件的对齐位置。</li>
     * <li>.value[1]?.f32：按照对齐方式对齐后，选择器相对入口组件的x轴方向相对偏移，单位为vp。默认值：0。</li>
     * <li>.value[2]?.f32：按照对齐方式对齐后，选择器相对入口组件的y轴方向相对偏移，单位为vp。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：对齐方式类型，参数类型{@link ArkUI_CalendarAlignment}。</li>
     * <li>.value[1].f32：按照对齐方式对齐后，选择器相对入口组件的x轴方向相对偏移。</li>
     * <li>.value[2].f32：按照对齐方式对齐后，选择器相对入口组件的y轴方向相对偏移。</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     */
    NODE_CALENDAR_PICKER_EDGE_ALIGNMENT,

    /**
     * @brief 设置日历选择器入口区的文本颜色、字号、字体粗细。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0]?.u32：入口区的文本颜色。未设置或执行resetAttribute后，使用系统主题
     * `calendar_picker_entry_font_color` 解析的值（具体色值随主题变化，可通过getAttribute获取）。</li>
     * <li>.value[1]?.f32：入口区的文本字号，单位为fp。未设置或执行resetAttribute后，使用系统主题
     * `calendar_picker_entry_font_size` 解析的值（具体数值随主题变化，可通过getAttribute获取）。</li>
     * <li>.value[2]?.i32：入口区的文本字体粗细，参数类型{@link ArkUI_FontWeight}。未设置或执行resetAttribute后，
     * 默认值为ARKUI_FONT_WEIGHT_NORMAL。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：入口区的文本颜色。</li>
     * <li>.value[1].f32：入口区的文本字号，单位为fp。</li>
     * <li>.value[2].i32：入口区的文本字体粗细，参数类型{@link ArkUI_FontWeight}。</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     */
    NODE_CALENDAR_PICKER_TEXT_STYLE,

    /**
     * @brief 设置日历选择器的开始日期，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：日期。格式：年-月-日，年份支持1或4位，月份和日期为1-2位数字，如"1970-1-1"、"2024-05-20"。默认值：1970-1-1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：设置的日历选择器开始日期，格式为年-月-日。</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     * @since 18
     */
    NODE_CALENDAR_PICKER_START = 16004,

    /**
     * @brief 设置日历选择器的结束日期，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：日期。格式：年-月-日，年份支持1或4位，月份和日期为1-2位数字，如"2100-12-31"、"2025-1-25"。默认值："2100-12-31"。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：设置的日历选择器结束日期，格式为年-月-日。</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     * @since 18
     */
    NODE_CALENDAR_PICKER_END = 16005,

    /**
     * @brief 设置日历选择器的禁用日期区间，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：禁用日期区间字符串。禁用日期区间："第一个区间开始日期,第一个区间结束日期,第二个区间开始日期,第二个区间结束日期,...,第n个区间开始日期,第n个区间结束日期"。
     * 设置的禁用日期区间格式："1910-01-01,1910-12-31,2020-01-01,2020-12-31"。默认值：空字符串，表示不设置禁用日期区间。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string：设置的禁用日期区间字符串，格式为"开始日期,结束日期,..."，如"1910-01-01,1910-12-31"。</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     * @since 19
     */
    NODE_CALENDAR_PICKER_DISABLED_DATE_RANGE = 16006,

    /**
     * @brief 设置日历选择器在系统当前日期时，是否保持高亮显示，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：日历选择器在系统当前日期时，是否保持高亮显示。返回0表示不保持高亮显示，返回1表示保持高亮显示。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：日历选择器在系统当前日期时，是否保持高亮显示。</li>
     * </ul>
     *
     * @ingroup Calendarpicker
     * @since 19
     */
    NODE_CALENDAR_PICKER_MARK_TODAY = 16007,

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
     * @brief Defines the background color of the slider. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: background color, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_TRACK_COLOR,

    /**
     * @brief Defines the color of the selected part of the slider track. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: color of the selected part of the slider track, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: color of the selected part of the slider track, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_SELECTED_COLOR,

    /**
     * @brief Sets whether to display the stepping value. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: whether to display the stepping value. The value <b>1</b> means to display the stepping value,
     * and <b>0</b> (default value) means the opposite.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: whether to display the stepping value. The value <b>1</b> means to display the stepping value,
     * and <b>0</b> (default value) means the opposite.</li> \n
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_SHOW_STEPS,

    /**
     * @brief Defines the slider shape, which can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: shape. The parameter type is {@link ArkUI_SliderBlockStyle}.</li> \n
     * <li>.string?: depending on the shape. Optional.</li> \n
     * <ul>
     * <li>ARKUI_SLIDER_BLOCK_STYLE_IMAGE: image resource of the slider. Example: /pages/common/icon.png.</li> \n
     * <li>ARKUI_SLIDER_BLOCK_STYLE_SHAPE: custom shape of the slider.</li> \n
     * </ul>
     * There are five types:\n
     * **1. Rectangle:**\n
     * <ul>
     * <li>.value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_RECTANGLE</b> for the rectangle shape.</li>\n
     * <li>.value[2].f32: width of the rectangle.</li>\n
     * <li>.value[3].f32: height of the rectangle.</li>\n
     * <li>.value[4].f32: width of the rounded corner of the rectangle.</li>\n
     * <li>.value[5].f32: height of the rounded corner of the rectangle.</li>\n
     * </ul>
     * **2. Circle:**\n
     * <ul>
     * <li>.value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_CIRCLE</b> for the circle shape.</li>\n
     * <li>.value[2].f32: width of the circle.</li>\n
     * <li>.value[3].f32: height of the circle.</li>\n
     * </ul>
     * **3.Ellipse:**\n
     * <ul>
     * <li>.value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_ELLIPSE</b> for the ellipse shape.</li>\n
     * <li>.value[2].f32: width of the ellipse.</li>\n
     * <li>.value[3].f32: height of the ellipse.</li>\n
     * </ul>
     * **4. Path:**\n
     * <ul>
     * <li>.value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_PATH</b> for the path shape.</li>\n
     * <li>.value[2].f32: width of the path.</li>\n
     * <li>.value[3].f32: height of the path.</li>\n
     * <li>.string: command for drawing the path.</li>\n
     * <ul>
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: shape. The parameter type is {@link ArkUI_SliderBlockStyle}.</li> \n
     * <li>.string?: depending on the shape. Optional.</li> \n
     * <ul>
     * <li>ARKUI_SLIDER_BLOCK_STYLE_IMAGE: image resource of the slider. Example: /pages/common/icon.png.</li> \n
     * <li>ARKUI_SLIDER_BLOCK_STYLE_SHAPE: custom shape of the slider.</li> \n
     * </ul>
     * There are five types:\n
     * **1. Rectangle:**\n
     * <ul>
     * <li>.value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_RECTANGLE</b> for the rectangle shape.</li>\n
     * <li>.value[2].f32: width of the rectangle.</li>\n
     * <li>.value[3].f32: height of the rectangle.</li>\n
     * <li>.value[4].f32: width of the rounded corner of the rectangle.</li>\n
     * <li>.value[5].f32: height of the rounded corner of the rectangle.</li>\n
     * </ul>
     * **2. Circle:**\n
     * <ul>
     * <li>.value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_CIRCLE</b> for the circle shape.</li>\n
     * <li>.value[2].f32: width of the circle.</li>\n
     * <li>.value[3].f32: height of the circle.</li>\n
     * </ul>
     * **3.Ellipse:**\n
     * <ul>
     * <li>.value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_ELLIPSE</b> for the ellipse shape.</li>\n
     * <li>.value[2].f32: width of the ellipse.</li>\n
     * <li>.value[3].f32: height of the ellipse.</li>\n
     * </ul>
     * **4. Path:**\n
     * <ul>
     * <li>.value[1].i32: type of shape. The parameter type is {@link ArkUI_ShapeType}.
     * The value is <b>ARKUI_SHAPE_TYPE_PATH</b> for the path shape.</li>\n
     * <li>.value[2].f32: width of the path.</li>\n
     * <li>.value[3].f32: height of the path.</li>\n
     * <li>.string: command for drawing the path.</li>\n
     * </ul>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_BLOCK_STYLE,

    /**
     * @brief Defines the current value of the slider. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: current value.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: current value.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_VALUE,

    /**
     * @brief Defines the minimum value of the slider. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: minimum value.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: minimum value.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_MIN_VALUE,

    /**
     * @brief Defines the maximum value of the slider. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: maximum value.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: maximum value.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_MAX_VALUE,

    /**
     * @brief Defines the step of the slider. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: step. The value range is [0.01, 100].</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: step. The value range is [0.01, 100].</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_STEP,

    /**
     * @brief Defines whether the slider moves horizontally or vertically. This attribute can be set, reset, and
     * obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: whether the slider moves horizontally or vertically.
     * The parameter type is {@link ArkUI_SliderDirection}.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: whether the slider moves horizontally or vertically.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_DIRECTION,

    /**
     * @brief Defines whether the slider values are reversed. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: whether the slider values are reversed. The value <b>1</b> means that the slider values are
     * reversed, and <b>0</b> means the opposite.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: whether the slider values are reversed. The value <b>1</b> means that the slider values are
     * reversed, and <b>0</b> means the opposite.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_REVERSE,

    /**
     * @brief Defines the style of the slider thumb and track. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: style of the slider thumb and track. The parameter type is {@link ArkUI_SliderStyle}.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: style of the slider thumb and track. The parameter type is {@link ArkUI_SliderStyle}.</li>
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_STYLE,

    /**
     * @brief Sets the track thickness of the slider.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].f32: track thickness of the slider, in vp. The default value is 4.0 vp when <b>NODE_SLIDER_STYLE</b>
     * is set to <b>ARKUI_SLIDER_STYLE_OUT_SET</b> and 20.0 vp when <b>NODE_SLIDER_STYLE</b> is set to
     * <b>ARKUI_SLIDER_STYLE_IN_SET</b>.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].f32: track thickness of the slider, in vp.</li> \n
     * </ul>
     *
     * @ingroup Slider
     */
    NODE_SLIDER_TRACK_THICKNESS,

    /**
     * @brief Defines whether haptic feedback.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: whether to feedback. The value <b>true</b> means to feedback, and
     * <b>false</b> means the opposite.</li>\n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>value[0].i32: whether to feedback.\n
     * When enabling haptic feedback, you need to add "ohos.permission.VIBRATE" in the
     * requestPermissions field of the module.json5 file to enable vibration permission.</li>\n
     * </ul>
     *
     * @ingroup Slider
     * @since 18
     */
    NODE_SLIDER_ENABLE_HAPTIC_FEEDBACK = 17013,

    /**
     * @brief Sets a custom component on the leading side of the Slider component.
     *
     * **Attribute setting method {@link ArkUI_AttributeItem} parameter format:**\n
     * <ul>
     * <li>.object: Parameter type {@link ArkUI_NodeHandle}.</li>
     * </ul>
     * The prefix component will be placed at the start position of the Slider，
     * typically on the left side in LTR layouts.
     *
     * @ingroup Slider
     * @since 20
     */
    NODE_SLIDER_PREFIX,

    /**
     * @brief Sets a custom component on the trailing side of the Slider component.
     *
     * **Attribute setting method {@link link ArkUI_AttributeItem} parameter format:**\n
     * <ul>
     * <li>.object: Parameter type {@link ArkUI_NodeHandle}.</li>
     * </ul>
     * The suffix component will be placed at the end position of the Slider,
     * typically on the right side in LTR layouts.
     *
     * @ingroup Slider
     * @since 20
     */
    NODE_SLIDER_SUFFIX,

    /**
     * @brief slider 滑块颜色设置，类型为渐变色
     *
     * @ingroup Slider
     * @since 21
     */
    NODE_SLIDER_BLOCK_LINEAR_GRADIENT_COLOR,

    /**
     * @brief slider 滑轨颜色设置，类型为渐变色
     *
     * @ingroup Slider
     * @since 21
     */
    NODE_SLIDER_TRACK_LINEAR_GRADIENT_COLOR,

    /**
     * @brief slider 选中段颜色设置，类型为渐变色
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
     * @brief Set the styles of the selected and deselected states of the option button.
     * The attribute setting, attribute resetting, and attribute obtaining are supported.
     * **Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:**\n
     * <ul>
     * <li>.value[0]?. u32: color of the mother board in enabled state. \n
     * The type is 0xARGB, and the default value is 0xFF007DFF.</li> \n
     * <li>.value[1]?. u32: stroke color in the close state. The type is 0xARGB, \n
     * and the default value is 0xFF182431.</li> \n
     * <li>.value[2]?. u32: color of the internal round pie in the enabled state. \n
     * The type is 0xARGB, and the default value is 0xFFFFFFFF.</li> \n
     * </ul>
     * **Attribute obtaining method return value {@Link ArkUI_AttributeItem} format:**\n
     * <ul>
     * <li>.value[0]. u32: color of the mother board in enabled state. \n
     * The type is 0xARGB, and the default value is 0xFF007DFF.</li> \n
     * <li>.value[1]. u32: stroke color in the close state. The type is 0xARGB, \n
     * and the default value is 0xFF182431.</li> \n
     * <li>.value[2]. u32: color of the internal round pie in the enabled state. \n
     * The type is 0xARGB, and the default value is 0xFFFFFFF.</li> \n
     * </ul>
     *
     * @ingroup Radio
     */
    NODE_RADIO_STYLE,
    /**
     * @brief Sets the value of the current radio.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:**\n
     * <ul>
     * <li>.string: radio value.</li>\n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.string: radio value.</li>\n
     * </ul>
     *
     * @ingroup Radio
     */
    NODE_RADIO_VALUE,
    /**
     * @brief Set the group name of the current Radio group, only one radio of the same group can be selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Attribute setting method {@Link ArkUI_AttributeItem} Parameter format:**\n
     * <ul>
     * <li>.string: name of the group to which the current option box belongs.</li>\n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.string: name of the group to which the current option box belongs.</li>\n
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
     * @brief Defines the playback status of the animation for the image animator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: playback status of the animation. The parameter type is
     * {@link ArkUI_AnimationStatus}. The default value is <b>ARKUI_ANIMATION_STATUS_INITIAL</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: playback status of the animation. The parameter type is {@link ArkUI_AnimationStatus}.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_STATE = 19001,

    /**
     * @brief Defines the playback duration for the image animator. When the duration is 0, no image is played.
     * The value change takes effect only at the beginning of the next cycle.
     * When a separate duration is set in images, the setting of this attribute is invalid.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: playback duration, in ms. The default value is 1000.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: playback duration, in ms.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_DURATION = 19002,

    /**
     * @brief Defines the playback direction for the image animator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: playback direction. <b>0</b> indicates that images are played from the first one to
     * the last one, and <b>1</b> indicates that images are played from the last one to the first one.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: playback direction. <b>0</b> indicates that images are played from the first one to
     * the last one, and <b>1</b> indicates that images are played from the last one to the first one.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_REVERSE = 19003,

    /**
     * @brief Defines whether the image size is the same as the component size.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether the image size is the same as the component size. <b>1</b> indicates that
     * the image size is the same as the component size. In this case, the width, height, top, and left
     * attributes of the image are invalid. <b>0</b> indicates that the image size is customized. The width,
     * height, top, and left attributes of each image must be set separately.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether the image size is the same as the component size. <b>1</b> indicates that
     * the image size is the same as the component size. <b>0</b> indicates that the image size is customized.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_FIXED_SIZE = 19004,

    /**
     * @brief Defines the status before and after execution of the animation in the current playback direction.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: status before and after execution of the animation in the current playback direction.
     * The parameter type is {@link ArkUI_AnimationFillMode}. The default value is
     * <b>ARKUI_ANIMATION_FILL_MODE_FORWARDS</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: status before and after execution of the animation in the current playback direction.
     * The parameter type is {@link ArkUI_AnimationFillMode}.</li>
     * </ul>
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_FILL_MODE = 19005,

    /**
     * @brief Defines the number of times that the animation is played.
     * This attribute can be set, reset, and obtained as required through APIs.
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
     * @brief Defines whether the checkboxgroup is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: whether the checkboxgroup is selected.
     * The value <b>1</b> means that the checkboxgroup is selected, and <b>0</b> means the opposite.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: The value <b>1</b> means that the checkboxgroup is selected, and <b>0</b> means the opposite.</li> \n
     * </ul>
     *
     * @ingroup CheckboxGroup
     * @since 15
     */
    NODE_CHECKBOX_GROUP_SELECT_ALL,

    /**
     * @brief Defines the color of the checkboxgroup when it is selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: color of the checkboxgroup when it is selected, in 0xARGB format,
     * for example, <b>0xFF1122FF</b>.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: color of the checkboxgroup when it is selected, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>
     * </ul>
     *
     * @ingroup CheckboxGroup
     * @since 15
     */
    NODE_CHECKBOX_GROUP_SELECTED_COLOR,
    /**
     * @brief Defines the border color of the checkboxgroup when it is not selected.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>
     * </ul>
     *
     * @ingroup CheckboxGroup
     * @since 15
     */
    NODE_CHECKBOX_GROUP_UNSELECTED_COLOR,

    /**
     * @brief Defines the internal icon style of the checkboxgroup.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>\n
     * <li>.value[1]?.f32: size of the internal mark, in vp. Optional.</li>\n
     * <li>.value[2]?.f32: stroke width of the internal mark, in vp. Optional. The default value is <b>2</b>.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].u32: border color, in 0xARGB format, for example, <b>0xFF1122FF</b>.</li>\n
     * <li>.value[1].f32: size of the internal mark, in vp.</li> \n
     * <li>.value[2].f32: stroke width of the internal mark, in vp. The default value is <b>2</b>.</li> \n
     * </ul>
     *
     * @ingroup CheckboxGroup
     * @since 15
     */
    NODE_CHECKBOX_GROUP_MARK,

    /**
     * @brief Defines the shape of the checkboxgroup.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**\n
     * <ul>
     * <li>.value[0].i32: component shape. The parameter type is {@link ArkUI_CheckboxShape}.</li> \n
     * </ul>
     * \n
     * **Format of the return value {@link ArkUI_AttributeItem}:**\n
     * <ul>
     * <li>.value[0].i32: component shape. The parameter type is {@link ArkUI_CheckboxShape}.</li>
     * </ul>
     *
     * @ingroup CheckboxGroup
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_DATA_DETECTOR_CONFIG,

    /**
     * @brief TextEditor组件扩展菜单选项，支持属性设置和属性重置。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。



     * <br>**参数：**
     * <br>.object：扩展菜单选项，设置后可自定义默认菜单项的行为，或添加自定义选项内容。参数类型{@link ArkUI_TextEditMenuOptions}。


     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_EDIT_MENU_OPTIONS,

    /**
     * @brief TextEditor组件无输入时的提示文本选项，支持属性设置和属性重置。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     * <br>**参数：**
     * <br>.object：无输入时的提示文本选项，参数类型{@link ArkUI_TextEditorPlaceholderOptions}。不传入时，编辑器无输入状态下不显示提示文本。







     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_PLACEHOLDER,

    /**
     * @brief TextEditor组件属性字符串控制器，支持属性设置。设置后，可通过该控制器管理TextEditor中的内容、光标、选区、输入样式及编辑状态。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。



     * <br>**参数：**
     * <br>.object：属性字符串控制器，参数类型{@link ArkUI_TextEditorStyledStringController}。

     *
     * @ingroup Text Editor
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
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ENABLE_PREVIEW_TEXT,

    /**
     * @brief TextEditor组件TextLayoutManager获取，获取后，可通过布局管理器查询文本的布局信息，如行数、行高和内容偏移等。支持属性获取。
     * <br>作为属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * <br>**返回：**
     * <br>.object：布局管理器，可通过该管理器查询文本的布局信息。参数类型{@link ArkUI_TextLayoutManager}。






     *
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_CUSTOM_KEYBOARD,

    /**
     * @brief TextEditor组件自定义文本选择菜单绑定，支持属性设置和属性重置。
     * <br>作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。



     * <br>**参数：**
     * <br>.object：自定义选择菜单，不传入时使用系统默认文本选择菜单。参数类型{@link ArkUI_TextEditorSelectionMenuOptions}。

     *
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
     * @since 26.0.0
     */
    NODE_TEXT_EDITOR_PUNCTUATION_OVERFLOW,

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
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_INDEXER_ARRAY = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_ALPHABET_INDEXER,

    /**
     * @brief 定义正常状态下的索引项文本颜色。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：文本的颜色，格式为0xARGB，默认值为0xFFFFFFFF。\n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].u32：文本的颜色，格式为0xARGB。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_INDEXER_COLOR,

    /**
     * @brief 定义选中状态下的索引项文本颜色。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：文本的颜色，格式为0xARGB，默认值为0xFFFFFFFF。\n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].u32：文本的颜色，格式为0xARGB。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_INDEXER_SELECTED_COLOR,

    /**
     * @brief 定义弹出窗口文本颜色。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：文本的颜色，格式为0xARGB，默认值为0xFFFFFFFF。\n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].u32：文本的颜色，格式为0xARGB。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_INDEXER_POPUP_COLOR,

    /**
     * @brief 定义选中状态下的索引项背景色。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：背景颜色，格式为0xARGB，默认值为0xFF1F71FF。\n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].u32：背景颜色，格式为0xARGB。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_INDEXER_SELECTED_BACKGROUND_COLOR,

    /**
     * @brief 定义弹出窗口背景色。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].u32：背景颜色，格式为0xARGB，默认值为0xD8404040。\n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].u32：背景颜色，格式为0xARGB。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_INDEXER_POPUP_BACKGROUND_COLOR,

    /**
     * @brief 定义是否使用弹窗。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：是否使用弹窗。值<b>0</b>表示不使用弹出窗口，\n
     * <b>1</b>表示使用弹出窗口。默认值为<b>0</b>。\n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].i32：是否使用弹窗。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_INDEXER_USE_POPUP,

    /**
     * @brief 定义所选索引的字体样式。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .string：字体系列。多个字体之间用逗号隔开。可选.\n
     * 默认值为<b>"HarmonyOS Sans"</b>。\n
     * .value[0].f32：字体大小，单位为fp。可选，默认为<b>13</b>。\n
     * .value[1].i32：字体粗细。可选，参数类型为{@link ArkUI_FontWeight}。\n
     * 默认值为<b>ARKUI_FONT_WEIGHT_W500</b>。\n
     * .value[2].i32：字体样式。可选，参数类型为{@link ArkUI_FontStyle}。\n
     * 默认值为<b>ARKUI_FONT_STYLE_NORMAL</b>。\n
     * 返回值{@link ArkUI_AttributeItem}格式：\n
     * .string：字体系列。多个字体之间用逗号隔开。\n
     * .value[0].f32：字体大小，单位为fp。\n
     * .value[1].i32：字体粗细。参数类型为{@link ArkUI_FontWeight}。\n
     * .value[2].i32：字体样式。参数类型为{@link ArkUI_FontStyle}。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_SELECTED_FONT,

    /**
     * @brief 定义弹出窗口的字体样式。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .string：字体系列。多个字体之间用逗号隔开。可选.\n
     * 默认值为<b>"HarmonyOS Sans"</b>。\n
     * .value[0].f32：字体大小，单位为fp。可选，默认为<b>19</b>。\n
     * .value[1].i32：字体粗细。可选，参数类型为{@link ArkUI_FontWeight}。\n
     * 默认值为<b>ARKUI_FONT_WEIGHT_W500</b>。\n
     * .value[2].i32：字体样式。可选，参数类型为{@link ArkUI_FontStyle}。\n
     * 默认值为<b>ARKUI_FONT_STYLE_NORMAL</b>。\n
     * 返回值{@link ArkUI_AttributeItem}格式：\n
     * .string：字体系列。多个字体之间用逗号隔开。\n
     * .value[0].f32：字体大小，单位为fp。\n
     * .value[1].i32：字体粗细。参数类型为{@link ArkUI_FontWeight}。\n
     * .value[2].i32：字体样式。参数类型为{@link ArkUI_FontStyle}。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_INDEXER_POPUP_FONT,

    /**
     * @brief 定义默认字体样式。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .string：字体系列。多个字体之间用逗号隔开。可选.\n
     * 默认值为<b>"HarmonyOS Sans"</b>。\n
     * .value[0].f32：字体大小，单位为fp。可选，默认为<b>13</b>。\n
     * .value[1].i32：字体粗细。可选，参数类型为{@link ArkUI_FontWeight}。\n
     * 默认值为<b>ARKUI_FONT_WEIGHT_W500</b>。\n
     * .value[2].i32：字体样式。可选，参数类型为{@link ArkUI_FontStyle}。\n
     * 默认值为<b>ARKUI_FONT_STYLE_NORMAL</b>。\n
     * 返回值{@link ArkUI_AttributeItem}格式：\n
     * .string：字体系列。多个字体之间用逗号隔开。\n
     * .value[0].f32：字体大小，单位为fp。\n
     * .value[1].i32：字体粗细。参数类型为{@link ArkUI_FontWeight}。\n
     * .value[2].i32：字体样式。参数类型为{@link ArkUI_FontStyle}。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_FONT,

    /**
     * @brief 定义字母索引栏字母区域大小。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].f32：字母区域为圆，设置圆的直径，单位为vp。\n
     * 默认值为<b>24</b>。\n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].f32：字母区域为圆，设置圆的直径，单位为vp。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_INDEXER_ITEM_SIZE,

    /**
     * @brief 定义选择的索引。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：选择的索引。默认值为<b>0</b>。\n
     * 返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：选择的索引。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_INDEXER_SELECTED,

    /**
     * @brief 定义当索引器栏不足以显示所有字符时，是否折叠字符。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：当索引器栏不足以显示所有字符时，是否折叠字符。\n
     * <b>1</b>表示自动折叠字符，<b>0</b>表示自动折叠字符。\n
     * 默认值为<b>1</b>。\n
     * 返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：当索引器栏不足以显示所有字符时，是否折叠字符。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_AUTO_COLLAPSE,

    /**
     * @brief 定义弹窗背景模糊样式。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：弹窗的模糊样式。取值为{@link ArkUI_BlurStyle}的枚举类型。\n
     * 默认值为<b>ARKUI_BLUR_STYLE_NONE</b>。\n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].i32：弹窗的模糊样式。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_ALPHABET_POPUP_BACKGROUND_BLUR_STYLE,

    /**
     * @brief Defines the alignment mode of the child components in the container. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: alignment mode. The data type is {@link ArkUI_Alignment}. The default value is <b>ARKUI_ALIGNMENT_CENTER</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: alignment mode. The data type is {@link ArkUI_Alignment}.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_STACK_ALIGN_CONTENT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_STACK,

    /**
     * @brief 设置滚动条状态，支持属性设置，属性重置和属性获取接口。List/Scroll/WaterFlow从API version 12开始支持，Grid从API version 22开始支持。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 滚动条状态，数据类型{@link ArkUI_ScrollBarDisplayMode}，
     * List、Grid、Scroll组件默认值为{@link ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO}，
     * WaterFlow组件默认值为{@link ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 滚动条状态，数据类型{@link ArkUI_ScrollBarDisplayMode}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_BAR_DISPLAY_MODE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_SCROLL,

    /**
     * @brief 设置滚动条的宽度，支持属性设置，属性重置和属性获取接口。List/Scroll/WaterFlow从API version 12开始支持，Grid从API version 22开始支持。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 滚动条宽度，单位vp，默认值4。 取值范围：[0, +∞)。设置为小于0的值时，按默认值处理，儿童智能表则恢复至默认值5vp。设置为0时，不显示滚动条。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 滚动条宽度，单位vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_BAR_WIDTH,

    /**
     * @brief 设置滚动条的颜色，支持属性设置，属性重置和属性获取接口。List/Scroll/WaterFlow从API version 12开始支持，Grid从API version 22开始支持。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.data[0].u32 滚动条颜色，0xargb类型。儿童智能表的默认值颜色：0xffffffff，表示白色（100%不透明度）。其他设备默认值：0x66182431，表示深蓝灰色（40%不透明度）。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.data[0].u32 滚动条颜色，0xargb类型。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_BAR_COLOR,

    /**
     * @brief 设置滚动方向，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 滚动方向，数据类型{@link ArkUI_ScrollDirection}，默认值{@link ARKUI_SCROLL_DIRECTION_VERTICAL}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 滚动方向，数据类型{@link ArkUI_ScrollDirection}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_SCROLL_DIRECTION,

    /**
     * @brief 设置边缘滑动效果，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 边缘滑动效果，参数类型{@link ArkUI_EdgeEffect}，Grid、Scroll、WaterFlow组件默认值为{@link ARKUI_EDGE_EFFECT_NONE}，
     * List组件默认值为{@link ARKUI_EDGE_EFFECT_SPRING}。</li>
     * <li>.value[1]?.i32 可选值，组件内容大小小于组件自身时，设置是否开启滑动效果，开启为1，关闭为0，List、Grid、WaterFlow组件默认值为0，Scroll组件默认值为1。</li>
     * <li>.value[2]?.i32 边缘效果生效的方向，参数类型{@link ArkUI_EffectEdge}，默认值{@link ARKUI_EFFECT_EDGE_START} | {@link ARKUI_EDGE_END}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 边缘滑动效果，参数类型{@link ArkUI_EdgeEffect}。</li>
     * <li>.value[1].i32 组件内容大小小于组件自身时，设置是否开启滑动效果，开启为1，关闭为0。</li>
     * <li>.value[2].i32 边缘效果生效的方向，参数类型{@link ArkUI_EffectEdge}。该参数从API version 18开始支持。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_EDGE_EFFECT,

    /**
     * @brief 设置是否支持滚动手势，当设置为0时，无法通过手指或者鼠标滚动，但不影响控制器的滚动接口。
     * List/Scroll/WaterFlow从API version 12开始支持，Grid从API version 22开始支持。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否支持滚动手势，默认值1。1：支持滚动手势，0：不支持滚动手势。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否支持滚动手势。1：支持滚动手势，0：不支持滚动手势。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_ENABLE_SCROLL_INTERACTION,

    /**
     * @brief 设置摩擦系数，手动滑动滚动区域时生效，只对惯性滚动过程有影响，对惯性滚动过程中的链式效果有间接影响。
     * List/Scroll/WaterFlow从API version 12开始支持，Grid从API version 22开始支持。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 摩擦系数，默认值：非可穿戴设备为0.6，可穿戴设备为0.9。取值范围：(0, +∞)，设置为小于等于0的值时，按默认值处理。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 摩擦系数。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_FRICTION,

    /**
     * @brief 设置Scroll组件的限位滚动模式，支持属性设置，属性重置和属性获取接口。如果同时设置了滑动翻页和限位滚动，则限位滚动优先生效，滑动翻页不生效。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Scroll组件限位滚动时的对齐方式，数据类型{@link ArkUI_ScrollSnapAlign}，默认值{@link ARKUI_SCROLL_SNAP_ALIGN_NONE}。
     * </li>
     * <li>.value[1].i32 在Scroll组件限位滚动模式下，该参数设置为1（true）后，不允许Scroll在开头和第一页间自由滑动，设置为0（false）后，允许Scroll在开头和第一页间自由滑动，
     * 默认值1（true）。该参数仅在限位点为2个及以上时生效。</li>
     * <li>.value[2].i32 在Scroll组件限位滚动模式下，该参数设置为1（true）后，不允许Scroll在最后一页和末尾间自由滑动，设置为0（false）后，允许Scroll在最后一页和末尾间自由滑动，
     * 默认值1（true）。该参数仅在限位点为2个及以上时生效。</li>
     * <li>.value[3...].f32 Scroll组件限位滚动时的限位点，限位点即为Scroll组件能滑动停靠的偏移量，单位：vp。可以1个或多个。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Scroll组件限位滚动时的对齐方式，数据类型{@link ArkUI_ScrollSnapAlign}。</li>
     * <li>.value[1].i32 在Scroll组件限位滚动模式下，该参数设置为1（true）后，不允许Scroll在开头和第一页间自由滑动，设置为0（false）后，允许Scroll在开头和第一页间自由滑动，
     * 默认值1（true）。该参数仅在限位点为2个及以上时生效。</li>
     * <li>.value[2].i32 在Scroll组件限位滚动模式下，该参数设置为1（true）后，不允许Scroll在最后一页和末尾间自由滑动，设置为0（false）后，允许Scroll在最后一页和末尾间自由滑动，
     * 默认值1（true）。该参数仅在限位点为2个及以上时生效。</li>
     * <li>.value[3...].f32 Scroll组件限位滚动时的限位点，限位点即为Scroll组件能滑动停靠的偏移量，单位：vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_SNAP,

    /**
     * @brief 设置嵌套滚动选项，支持属性设置，属性重置和属性获取。List/Scroll/WaterFlow从API version 12开始支持，Grid从API version 22开始支持。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 可滚动组件往末尾端滚动时的嵌套滚动，参数类型{@link ArkUI_ScrollNestedMode}。</li>
     * <li>.value[1].i32 可滚动组件往起始端滚动时的嵌套滚动，参数类型{@link ArkUI_ScrollNestedMode}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 可滚动组件往末尾端滚动时的嵌套滚动，参数类型{@link ArkUI_ScrollNestedMode}。</li>
     * <li>.value[1].i32 可滚动组件往起始端滚动时的嵌套滚动，参数类型{@link ArkUI_ScrollNestedMode}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_NESTED_SCROLL,

    /**
     * @brief 设置Scroll组件滑动到指定位置，支持属性设置，属性重置和属性获取。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 水平滑动偏移，单位为vp。取值范围：[0, +∞)，设置为小于0的值时按0处理。值为0时滚动到起始位置，值大于0时滚动到指定偏移位置。</li>
     * <li>.value[1].f32 垂直滑动偏移，单位为vp。取值范围：[0, +∞)，设置为小于0的值时按0处理。值为0时滚动到起始位置，值大于0时滚动到指定偏移位置。</li>
     * <li>.value[2]?.i32 可选值，滚动时长，单位为毫秒，默认值1000。滚动时长大于0或使能默认弹簧动效时，滚动带动画效果。</li>
     * <li>.value[3]?.i32 可选值，滚动曲线，参数类型{@link ArkUI_AnimationCurve}。默认值为{@link ARKUI_CURVE_EASE}。</li>
     * <li>.value[4]?.i32 可选值，是否使能默认弹簧动效，默认值为0不使能。</li>
     * <li>.value[5]?.i32 可选值，设置动画滚动到边界是否转换为越界回弹动画，默认值为0不转换越界回弹动画。</li>
     * <li>.value[6]?.i32 可选值，设置滚动是否可以停留在越界位置，默认值为0不停留在越界位置。该参数从API version 20开始支持。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 水平滑动偏移，单位为vp。</li>
     * <li>.value[1].f32 垂直滑动偏移，单位为vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_OFFSET,

    /**
     * @brief 设置Scroll组件滚动到容器边缘位置，支持属性设置和属性获取。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 容器边缘位置，参数类型{@link ArkUI_ScrollEdge}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 容器是否位于边缘。-1表示未处于边缘；处于边缘状态时，返回值为{@link ArkUI_ScrollEdge}枚举值，表示具体边缘位置。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_EDGE,

    /**
     * @brief 设置是否支持滑动翻页，支持属性设置，属性重置和属性获取接口。如果同时设置了滑动翻页enablePaging和限位滚动scrollSnap，则scrollSnap优先生效，enablePaging不生效。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否支持滑动翻页，默认值0。0：不支持滑动翻页，1：支持滑动翻页。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否支持滑动翻页。0：不支持滑动翻页，1：支持滑动翻页。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_ENABLE_PAGING,

    /**
     * @brief 滚动到下一页或者上一页。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 翻页方向。0表示向下翻页，1表示向上翻页。</li>
     * <li>.value[1]?.i32 是否开启翻页动画效果。1有动画，0无动画。默认值：0。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_PAGE,

    /**
     * @brief 滑动指定距离。从API version 12开始List/Scroll/WaterFlow组件支持滑动指定距离，从API版本26.0.0开始Grid组件支持滑动指定距离。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 水平方向滚动距离，单位：vp。</li>
     * <li>.value[1].f32 垂直方向滚动距离，单位：vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_SCROLL_BY,

    /**
     * @brief 滚动类组件按传入的初始速度进行惯性滚动。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 惯性滚动的初始速度，单位：vp/s。值设置为0，视为异常值，本次滚动不生效。如果值为正数，则向下滚动；如果值为负数，则向上滚动。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 13
     */
    NODE_SCROLL_FLING,

    /**
     * @brief 设置滚动类组件边缘渐隐效果。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否使能边缘渐隐效果。0表示关闭边缘效果，1表示开启边缘效果，默认值0。</li>
     * <li>.value[1]?.f32 边缘渐隐效果长度。单位：vp，默认值：32。 取值范围：值必须大于等于0。仅在开启边缘渐隐效果时生效。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否使能边缘渐隐效果。0表示关闭边缘效果，1表示开启边缘效果。</li>
     * <li>.value[1].f32 边缘渐隐效果长度。单位：vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 14
     */
    NODE_SCROLL_FADING_EDGE,

    /**
     * @brief 获取滚动类组件所有子组件全展开尺寸。
     * 作为属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 滚动类组件所有子组件全展开的宽度，默认单位为vp。</li>
     * <li>.value[1].f32 滚动类组件所有子组件全展开的高度，默认单位为vp。 设置NODE_PADDING、NODE_MARGIN或NODE_BORDER_WIDTH后，NODE_PADDING、
     * NODE_MARGIN或NODE_BORDER_WIDTH在单位vp转换成单位px时会进行像素取整，返回值根据取整后的值计算。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 14
     */
    NODE_SCROLL_SIZE,

    /**
     * @brief 设置滚动类组件内容起始端偏移量。List组件从API version 15开始支持，Grid/Scroll/WaterFlow从API version 22开始支持。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 内容起始端偏移量，单位vp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 内容起始端偏移量，单位vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 15
     */
    NODE_SCROLL_CONTENT_START_OFFSET,

    /**
     * @brief 设置滚动类组件内容末尾端偏移量。List组件从API version 15开始支持，Grid/Scroll/WaterFlow从API version 22开始支持。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 内容末尾端偏移量，单位vp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 内容末尾端偏移量，单位vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 15
     */
    NODE_SCROLL_CONTENT_END_OFFSET,

    /**
     * @brief 限制跟手滑动结束后，Fling动效开始时的最大初始速度。支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 Fling动效开始时的最大初始速度，单位：vp/s。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 Fling动效开始时的最大初始速度，单位：vp/s。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 18
     */
    NODE_SCROLL_FLING_SPEED_LIMIT = 1002019,

    /**
     * @brief 设置滚动容器的内容层裁剪区域。支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 内容裁剪模式，参数类型{@link ArkUI_ContentClipMode}。
     * Grid、Scroll组件默认值为{@link ARKUI_CONTENT_CLIP_MODE_BOUNDARY}，
     * List、WaterFlow组件默认值为{@link ARKUI_CONTENT_CLIP_MODE_CONTENT_ONLY}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 内容裁剪模式，参数类型{@link ArkUI_ContentClipMode}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 18
     */
    NODE_SCROLL_CLIP_CONTENT = 1002020,

    /**
     * @brief 设置滚动容器是否在点击状态栏时回到顶部。支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否回到顶部，1表示回到顶部，0表示保持当前位置不变，默认值：API version 18之前：0。API version 18及以后：滚动方向是水平方向时为0，是垂直方向时为1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否回到顶部。1表示回到顶部，0表示保持当前位置不变。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 15
     */
    NODE_SCROLL_BACK_TO_TOP = 1002021,

    /**
     * @brief 设置滚动条的边距，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 设置滚动条起始边距，儿童智能表默认值为42，其他设备默认值为0，单位：vp。</li>
     * <li>.value[1].f32 设置滚动条末尾边距，默认值为0，单位：vp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 滚动条起始边距，单位：vp。</li>
     * <li>.value[1].f32 滚动条末尾边距，单位：vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 20
     */
    NODE_SCROLL_BAR_MARGIN = 1002022,

    /**
     * @brief 设置滚动内容最大缩放比例。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 设置内容最大缩放比例。默认值：1 取值范围：(0, +∞)，小于或等于0时按默认值1处理。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 获取内容最大缩放比例。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 20
     */
    NODE_SCROLL_MAX_ZOOM_SCALE = 1002023,

    /**
     * @brief 设置滚动内容最小缩放比例。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 设置内容最小缩放比例，默认值：1 取值范围：(0, NODE_SCROLL_MAX_ZOOM_SCALE]，小于或等于0时按默认值1处理，
     * 大于NODE_SCROLL_MAX_ZOOM_SCALE时按NODE_SCROLL_MAX_ZOOM_SCALE处理。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 获取内容最小缩放比例。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 20
     */
    NODE_SCROLL_MIN_ZOOM_SCALE = 1002024,

    /**
     * @brief 设置滚动内容缩放比例。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 设置内容缩放比例，默认值：1 取值范围：(0, +∞)，小于或等于0时按默认值1处理。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 获取内容缩放比例。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 20
     */
    NODE_SCROLL_ZOOM_SCALE = 1002025,

    /**
     * @brief 设置是否支持过缩放回弹效果。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否支持过缩放回弹效果，0：不支持，1：支持。默认值：1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否支持过缩放回弹效果，0：不支持，1：支持。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 20
     */
    NODE_SCROLL_ENABLE_BOUNCES_ZOOM = 1002026,

    /**
     * @brief 设置是否支持鼠标左键按下拖动滚动，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否支持鼠标左键按下拖动滚动，0：不支持鼠标左键按下拖动滚动，1：支持鼠标左键按下拖动滚动。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否支持鼠标左键按下拖动滚动，0：不支持鼠标左键按下拖动滚动，1：支持鼠标左键按下拖动滚动。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_SCROLL_ENABLE_SCROLL_WITH_MOUSE = 1002027,

    /**
     * @brief 设置滚动条是否自动调整边距以避让组件NODE_PADDING、NODE_SCROLL_CONTENT_START_OFFSET或NODE_SCROLL_CONTENT_END_OFFSET的区域，支持属性设置，
     * 属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否自动调整边距，0：自动调整边距，1：不自动调整边距。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否自动调整边距，0：自动调整边距，1：不自动调整边距。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_SCROLL_AUTO_ADJUST_MARGIN = 1002028,

    /**
     * @brief 设置滚动条滑轨高度。支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 滚动条滑轨高度，单位：vp。默认值：自适应滚动组件高度。 取值范围：[0, +∞)。设置为小于0时使用默认值，儿童智能表则恢复至默认值37vp。设置为0时不显示滚动条。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 滚动条滑轨高度，单位：vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_SCROLL_BAR_HEIGHT = 1002029,

    /**
     * @brief 设置List组件排列方向。支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件排列方向，数据类型{@link ArkUI_Axis}，默认值ARKUI_AXIS_VERTICAL。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件排列方向，数据类型{@link ArkUI_Axis}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_DIRECTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST,

    /**
     * @brief 配合ListItemGroup组件使用，设置ListItemGroup中header和footer是否要吸顶或吸底，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 配合ListItemGroup组件使用，设置ListItemGroup中header和footer是否要吸顶或吸底。数据类型{@link ArkUI_StickyStyle}，
     * 默认值ARKUI_STICKY_STYLE_NONE。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 配合ListItemGroup组件使用，设置ListItemGroup中header和footer是否要吸顶或吸底。数据类型{@link ArkUI_StickyStyle}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_STICKY,

    /**
     * @brief 设置列表项间距，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 子组件主轴方向的间隔，单位vp，默认值0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 子组件主轴方向的间隔。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_SPACE,

    /**
     * @brief List组件适配器，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_NodeAdapter}对象作为适配器。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 返回值格式为{@link ArkUI_NodeAdapter}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_NODE_ADAPTER,

    /**
     * @brief List组件Adapter缓存数量，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 配合List组件Adapter使用，设置adapter中的缓存数量。</li>
     * <li>.value[1]?.i32 是否显示缓存节点，0：不显示，1：显示，默认值：0。该参数从API version 15开始支持。</li>
     * <li>.value[2]?.i32 设置List最大缓存数量，默认值与第一个参数相同。该参数从API version 22开始支持。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 adapter中的缓存数量。</li>
     * <li>.value[1].i32 是否显示缓存节点，0：不显示，1：显示。该参数从API version 15开始支持。</li>
     * <li>.value[2].i32 List最大缓存数量。该参数从API version 22开始支持。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_CACHED_COUNT,

    /**
     * @brief 滑动到指定index。开启平滑滚动动效时，会对经过的所有item进行加载和布局计算，当大量加载item时会导致性能问题。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 要滑动到的目标元素在当前容器中的索引值。传入-1时，指滑动到当前容器的最后一个元素。</li>
     * <li>.value[1]?.i32 设置滑动到列表项在列表中的索引值时是否有动效，1表示有动效，0表示没有动效。默认值：0。</li>
     * <li>.value[2]?.i32 指定滑动到的元素与当前容器的对齐方式，参数类型{@link ArkUI_ScrollAlignment}，默认值：{@link ARKUI_SCROLL_ALIGNMENT_START}。
     * </li>
     * <li>.value[3]?.f32 额外偏移量，默认值：0，单位：vp。正数表示向末尾端额外偏移，负数表示向起始端额外偏移。该参数从API version 15开始支持。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_SCROLL_TO_INDEX,

    /**
     * @brief 设置List交叉轴方向宽度大于ListItem交叉轴宽度乘以布局数量时，ListItem在List交叉轴方向的布局方式。List垂直滚动时，布局数量为列数；List水平滚动时，布局数量为行数。支持属性设置、
     * 属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 交叉轴方向的布局方式。参数类型{@link ArkUI_ListItemAlign}。默认值：ARKUI_LIST_ITEM_ALIGNMENT_START。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 交叉轴方向的布局方式。参数类型{@link ArkUI_ListItemAlign}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_ALIGN_LIST_ITEM,

    /**
     * @brief 设置List子组件默认主轴尺寸。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 参数格式为{@link ArkUI_ListChildrenMainSize}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 参数格式为{@link ArkUI_ListChildrenMainSize}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_CHILDREN_MAIN_SIZE = 1003007,

    /**
     * @brief 设置当前List初次加载时视口起始位置显示的item的索引值，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 当前List初次加载时视口起始位置显示的item的索引值。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 当前List初次加载时视口起始位置显示的item的索引值。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_INITIAL_INDEX = 1003008,

    /**
     * @brief 设置ListItem分割线样式，默认无分割线，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32 分割线颜色，0xargb类型，默认值为0x08000000。</li>
     * <li>.value[1].f32 分割线宽，默认值：0，单位vp。</li>
     * <li>.value[2].f32 分割线距离列表侧边起始端的距离，默认值：0，单位vp。</li>
     * <li>.value[3].f32 分割线距离列表侧边结束端的距离，默认值：0，单位vp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32 分割线颜色，0xargb类型。</li>
     * <li>.value[1].f32 分割线宽，单位vp。</li>
     * <li>.value[2].f32 分割线距离列表侧边起始端的距离，单位vp。</li>
     * <li>.value[3].f32 分割线距离列表侧边结束端的距离，单位vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_DIVIDER = 1003009,

    /**
     * @brief 滑动到指定ListItemGroup中指定index。开启smooth动效时，会对经过的所有item进行加载和布局计算，当大量加载item时会导致性能问题。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 要滑动到的目标ListItemGroup在当前List中的索引值。</li>
     * <li>.value[1].i32 要滑动到的目标ListItem在ListItemGroup中的索引值。</li>
     * <li>.value[2]?.i32 设置滑动到列表项在列表中的索引值时是否有动效，1表示有动效，0表示没有动效。默认值：0。</li>
     * <li>.value[3]?.i32 指定滑动到的元素与当前容器的对齐方式，参数类型{@link ArkUI_ScrollAlignment}。默认值：{@link ARKUI_SCROLL_ALIGNMENT_START}。
     * </li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 15
     */
    NODE_LIST_SCROLL_TO_INDEX_IN_GROUP = 1003010,

    /**
     * @brief 设置List列数（List垂直滚动时表示列数，水平滚动时表示行数），支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32 List布局列数或行数，List垂直滚动时表示列数，水平滚动时表示行数；如果同时设置了最小、最大列宽或行高，则设置列数或行数不生效；默认值：1，取值范围：[1, +∞)，
     * 设置异常值时使用默认值。</li>
     * <li>.value[1]?.f32 最小列宽或行高，单位vp，默认值：-1（未设置）。</li>
     * <li>.value[2]?.f32 最大列宽或行高，单位vp，默认值：-1（未设置）。</li>
     * <li>.value[3]?.f32 列间距或行间距，默认值：0，单位vp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32 当前List布局列数或行数，List垂直滚动时表示列数，水平滚动时表示行数。</li>
     * <li>.value[1].f32 最小列宽或行高，单位vp。</li>
     * <li>.value[2].f32 最大列宽或行高，单位vp。</li>
     * <li>.value[3].f32 列间距或行间距，单位vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 15
     */
    NODE_LIST_LANES = 1003011,

    /**
     * @brief 设置List限位对齐模式。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件限位滚动时的对齐方式，数据类型{@link ArkUI_ScrollSnapAlign}，默认值{@link ARKUI_SCROLL_SNAP_ALIGN_NONE}。
     * </li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件限位滚动时的对齐方式，数据类型{@link ArkUI_ScrollSnapAlign}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 15
     */
    NODE_LIST_SCROLL_SNAP_ALIGN = 1003012,

    /**
     * @brief 设置List显示区域外插入或删除数据是否保持可见内容位置不变。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List显示区域外插入或删除数据是否保持可见内容位置不变。0表示不保持可见内容位置，1表示保持可见内容位置，默认值为0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List显示区域外插入或删除数据是否保持可见内容位置不变。0表示不保持可见内容位置，1表示保持可见内容位置，默认值为0。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 15
     */
    NODE_LIST_MAINTAIN_VISIBLE_CONTENT_POSITION = 1003013,

    /**
     * @brief 设置List从末尾开始布局。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 设置List是否从末尾开始布局。0表示从顶部开始布局，1表示从末尾开始布局，默认值为0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 设置List是否从末尾开始布局。0表示从顶部开始布局，1表示从末尾开始布局，默认值为0。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 19
     */
    NODE_LIST_STACK_FROM_END = 1003014,

    /**
     * @brief List组件走焦换行模式，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件走焦换行模式，参数取值为{@link ArkUI_FocusWrapMode}下的枚举，默认值为ARKUI_FOCUS_WRAP_MODE_DEFAULT。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件走焦换行模式，参数类型{@link ArkUI_FocusWrapMode}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 20
     */
    NODE_LIST_FOCUS_WRAP_MODE = 1003015,

    /**
     * @brief List组件是否同步加载子节点，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件是否同步加载子节点。0：分帧加载，1：同步加载，默认值为1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件是否同步加载子节点。0：分帧加载，1：同步加载。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 20
     */
    NODE_LIST_SYNC_LOAD = 1003016,

    /**
     * @brief List组件限位滚动动画速度，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件限位滚动动画速度，数据类型{@link ArkUI_ScrollSnapAnimationSpeed}。默认值：
     * ARKUI_SCROLL_SNAP_ANIMATION_NORMAL。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件限位滚动动画速度，数据类型{@link ArkUI_ScrollSnapAnimationSpeed}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 22
     */
    NODE_LIST_SCROLL_SNAP_ANIMATION_SPEED = 1003017,

    /**
     * @brief List组件的响应式列数布局策略，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 在不同断点规格下的列数，数据类型{@link ArkUI_ItemFillPolicy}。</li>
     * <li>.value[1]?.f32 列间距，单位vp。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 在不同断点规格下的列数，数据类型{@link ArkUI_ItemFillPolicy}。</li>
     * <li>.value[1].f32 列间距，单位vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 22
     */
    NODE_LIST_LANES_ITEMFILLPOLICY = 1003018,

    /**
     * @brief 设置当前List组件是否支持在LazyForEach或Repeat中使用if/else渲染控制语法生成不包含任何子组件的空分支节点。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件是否支持空分支。0：不支持，1：支持。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件是否支持空分支。0：不支持，1：支持。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 23
     */
    NODE_LIST_SUPPORT_EMPTY_BRANCH_IN_LAZY_LOADING = 1003019,

    /**
     * @brief 设置List组件的系统返回键行为，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 系统返回键生效时是否收起ListItem的划出组件。0：不收起，1：收起。默认值：1</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 系统返回键生效时是否收起ListItem的划出组件。0：不收起，1：收起。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_LIST_BACK_PRESS_BEHAVIOR = 1003020,

    /**
     * @brief 设置List组件是否启用编辑模式。进入编辑模式后，默认显示复选框，并支持手指滑动多选。支持属性设置、属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件是否启用编辑模式。0：不启用，1：启用。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件是否启用编辑模式。0：未启用，1：已启用。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_LIST_ENABLE_EDIT_MODE = 1003021,

    /**
     * @brief 设置List组件的编辑模式选项，支持属性设置、属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件是否使用默认多选样式。0：不使用，1：使用。默认值：1。</li>
     * <li>.value[1].i32 List组件是否启用双指滑动多选。0：不启用，1：启用。默认值：1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 List组件是否使用默认多选样式。0：不使用，1：使用。</li>
     * <li>.value[1].i32 List组件是否启用双指滑动多选。0：未启用，1：已启用。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
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
     * @brief Defines whether to enable automatic playback for child component switching in the swiper.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable automatic playback for child component switching. The value <b>1</b>
     * means to enable automatic playback, and <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * <li>.value[1]?.i32: whether to stop automatic playback when the user touches the screen. The value <b>1</b> means
     * to stop automatic playback, and <b>0</b> means the opposite. The default value is <b>1</b>. This parameter is
     * supported since API version 16.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to enable automatic playback for child component switching. The value <b>1</b> means
     * to enable automatic playback, and <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * <li>.value[1].i32: whether to stop automatic playback when the user touches the screen. The value <b>1</b> means
     * to stop automatic playback, and <b>0</b> means the opposite. This parameter is supported since API version 16.
     * </li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_AUTO_PLAY,
    /**
     * @brief Defines whether to enable the navigation point indicator for the swiper. This attribute can be set,
     * reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to enable the navigation point indicator. The value <b>1</b> means to enable the
     * navigation point indicator, and <b>0</b> means the opposite. The default value is <b>1</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to enable the navigation point indicator. The value <b>1</b> means to enable the
     * navigation point indicator, and <b>0</b> means the opposite. The default value is <b>1</b>.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_SHOW_INDICATOR,
    /**
     * @brief Defines the interval for automatic playback. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: interval for automatic playback, in milliseconds.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: interval for automatic playback, in milliseconds.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_INTERVAL,
    /**
     * @brief Defines whether vertical swiping is used for the swiper. This attribute can be set, reset, and obtained
     * as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether vertical swiping is used. The value <b>1</b> means that vertical swiping is used, and
     * <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether vertical swiping is used. The value <b>1</b> means that vertical swiping is used, and
     * <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_VERTICAL,

    /**
     * @brief Defines the duration of the animation for switching child components. This attribute can be set, reset,
     * and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: duration of the animation for switching child components, in milliseconds. The default value
     * is <b>400</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: duration of the animation for switching child components, in milliseconds. The default value
     * is <b>400</b>.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_DURATION,

    /**
     * @brief Defines the animation curve for the swiper. This attribute can be set, reset, and obtained as required
     * through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: animation curve. The parameter type is {@link ArkUI_AnimationCurve}.
     * The default value is <b>ARKUI_CURVE_LINEAR</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: animation curve. The parameter type is {@link ArkUI_AnimationCurve}.
     * The default value is <b>ARKUI_CURVE_LINEAR</b>.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_CURVE,

    /**
     * @brief Defines the spacing between child components in the swiper.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: spacing between child components.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: spacing between child components.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_ITEM_SPACE,

    /**
     * @brief Defines the index of the child component currently displayed in the swiper.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: index value of the child component.</li>
     * <li>.value[1]?.i32: animation mode, the parameter type is {@link ArkUI_SwiperAnimationMode}.
     * The default value is ARKUI_SWIPER_NO_ANIMATION. This parameter is valid only for the current call.
     * This parameter is supported since API version 15.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: index value of the child component.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_INDEX,

    /**
     * @brief Defines the number of elements to display per page.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: number of elements to display per page.</li>
     * <li>.value[1]?.i32: whether to turn pages by group. The value <b>0</b> means to turn pages by child element,
     * and <b>1</b> means to turn pages by group. This parameter is supported since API version 19.</li>
     * <li>.string?: this parameter can only be set to 'auto'. When 'auto' is set, the value[] parameters are ignored.
     * This parameter is supported since API version 19.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: number of elements to display per page.</li>
     * <li>.value[1].i32: whether to turn pages by group. This parameter is supported since API version 19.</li>
     * <li>.string: 'auto' or empty string.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_DISPLAY_COUNT,

    /**
     * @brief Defines whether to disable the swipe feature.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to disable the swipe feature. The value <b>1</b> means to disable
     * the swipe feature, and <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to disable the swipe feature. The value <b>1</b> means to disable the swipe
     * feature, and <b>0</b> means the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_DISABLE_SWIPE,

    /**
     * @brief Defines whether to show the arrow when the mouse pointer hovers over the navigation point indicator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to show the arrow when the mouse pointer hovers over the navigation point indicator.
     * The parameter type is {@link ArkUI_SwiperArrow}.
     * The default value is <b>ARKUI_SWIPER_ARROW_HIDE</b>.</li>
     * <li>.?object: arrow style. The parameter type is {@link ArkUI_SwiperArrowStyle}.
     * This parameter is supported since API version 19.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to show the arrow when the mouse pointer hovers over the navigation point indicator.
     * The parameter type is {@link ArkUI_SwiperArrow}.
     * The default value is <b>ARKUI_SWIPER_ARROW_HIDE</b>.</li>
     * <li>.object: arrow style. The parameter type is {@link ArkUI_SwiperArrowStyle}.
     * This parameter is supported since API version 19.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_SHOW_DISPLAY_ARROW,

    /**
     * @brief Defines the effect used at the edges of the swiper when the boundary of the scrollable content is reached.
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
     * @since 12
     */
    NODE_SWIPER_EDGE_EFFECT_MODE,

    /**
     * @brief Defines the swiper adapter. The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.object: {@link ArkUI_NodeAdapter} object as the adapter.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_NODE_ADAPTER,

    /**
     * @brief Sets the number of cached items in the swiper adapter.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: number of cached items in the swiper adapter.</li>
     * <li>.value[1]?.i32: whether the cached items will be displayed.
     * The value <b>0</b> indicates that cached items will not be displayed,
     * and <b>1</b> indicates that cached items will be displayed. The default value is <b>0</b>.
     * This parameter is supported from API version 19.</li>
     * <li>.value[2]?.i32: whether the cachedCount is independent of group calculation.
     * The value <b>1</b> indicates that cachedCount is calculated by actual child component count,
     * and is independent of displayCount group calculation.
     * The value <b>0</b> indicates that, when NODE_SWIPER_DISPLAY_COUNT is enabled to turn pages by group,
     * cachedCount is calculated by group.The default value is <b>0</b>.
     * This parameter is supported from API version 24.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: number of cached items in the swiper adapter.</li>
     * <li>.value[1].i32: whether the cached items will be displayed. This parameter is supported from API version 19.
     * </li>
     * <li>.value[2].i32: whether the cachedCount is independent of group calculation.
     * This parameter is supported from API version 24.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_CACHED_COUNT,

    /**
     * @brief Defines the front margin of the wiper.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: the front margin. The unit is vp. The default value is <b>0.0</b></li>
     * <li>.value[1]?.i32: whether to ignore blanks, the default value is 0.
     * The value <b>1</b> means to ignore blank areas, and <b>0</b> means the opposite.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: the front margin, the unit is vp.</li>
     * <li>.value[1].i32: whether to ignore blank areas. The value <b>1</b> means to ignore blank areas, and <b>0</b>
     * means the opposite.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_PREV_MARGIN,

    /**
     * @brief Defines the back margin of the wiper.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: the back margin. The unit is vp. The default value is <b>0.0</b></li>
     * <li>.value[1]?.i32: whether to ignore blanks, the default value is 0.
     * The value <b>1</b> means to ignore blank areas, and <b>0</b> means the opposite.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: the back margin, the unit is vp.</li>
     * <li>.value[1].i32: whether to ignore blank areas. The value <b>1</b> means to ignore blank areas, and <b>0</b>
     * means the opposite.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_NEXT_MARGIN,

    /**
     * @brief Defines the navigation indicator type of the swiper.
     * The attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: navigation indicator type, the parameter type is {@link ArkUI_SwiperIndicatorType}.</li>
     * <li>.object: The parameter type is {@link ArkUI_SwiperIndicator} when the indicator type
     * is <b>ARKUI_SWIPER_INDICATOR_TYPE_DOT</b>. The parameter type is {@link ArkUI_SwiperDigitIndicator}
     * when the indicator type is <b>ARKUI_SWIPER_INDICATOR_TYPE_DIGIT</b>.
     * {@link ArkUI_SwiperDigitIndicator} is supported since API version 19.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: navigation indicator type, the parameter type is {@link ArkUI_SwiperIndicatorType}.</li>
     * <li>.object: The parameter type is {@link ArkUI_SwiperIndicator} when the indicator type
     * is <b>ARKUI_SWIPER_INDICATOR_TYPE_DOT</b>. The parameter type is {@link ArkUI_SwiperDigitIndicator}
     * when the indicator type is <b>ARKUI_SWIPER_INDICATOR_TYPE_DIGIT</b>.
     * {@link ArkUI_SwiperDigitIndicator} is supported since API version 19.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_INDICATOR,

    /**
     * @brief Set the nested scrolling mode for the Swiper component and parent component.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32：Nested scrolling patterns for Swiper components and parent components. The parameter type is
     * {@link ArkUI_SwiperNestedScrollMode}
     * The default value is <b>ARKUI_SWIPER_NESTED_SRCOLL_SELF_ONLY</b></li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32：Nested scrolling patterns for Swiper components and parent components. The parameter type is
     * {@link ArkUI_SwiperNestedScrollMode}</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_NESTED_SCROLL,

    /**
     * @brief Set the switcher component to flip to the specified page.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32：Specify the index value of the page in Swiper.</li>
     * <li>.value[1]?.i32：Set whether there is an animation effect when flipping to the specified page. 1 indicates
     * active effect, 0 indicates no active effect, default value is 0。</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_SWIPE_TO_INDEX,

    /**
     * @brief Set to disable component navigation point interaction function。
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32：Set to disable the interaction function of component navigation points. When set to true, it
     * indicates that the navigation points are interactive. The default value is true.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32：Set to disable component navigation point interaction.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
     */
    NODE_SWIPER_INDICATOR_INTERACTIVE,

    /**
     * @brief Sets the page flipping mode using the mouse wheel.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: page flipping mode using the mouse wheel. The parameter type is {@link ArkUI_PageFlipMode}.
     * </li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_PageFlipMode}:**
     * <ul>
     * <li>.value[0].i32: page flipping mode using the mouse wheel.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 15
     */
    NODE_SWIPER_PAGE_FLIP_MODE,

    /**
     * @brief Defines the minimum main axis size of child element for swiper to works out the display count.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].f32: minimum main axis size of the child element, Unit: vp.</li>
     * <li>.value[1]?.i32: whether to turn pages by group. The value <b>0</b> means to turn pages by child element,
     * and <b>1</b> means to turn pages by group. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].f32: minimum main axis size of the child element, Unit: vp.</li>
     * <li>.value[1].i32: whether to turn pages by group.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 19
     */
    NODE_SWIPER_AUTO_FILL,

    /**
     * @brief Sets whether to maintain the visible content's position when data is inserted or deleted outside
     * the display area of the <b>Swiper</b> component.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: whether to maintain the visible content's position when data is inserted or deleted outside
     * the display area of the <b>Swiper</b> component. The value <b>0</b> means not to maintain the visible content's
     * position, and <b>1</b> means the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: whether to maintain the visible content's position when data is inserted or deleted outside
     * the display area of the <b>Swiper</b> component. The value <b>0</b> means not to maintain the visible content's
     * position, and <b>1</b> means the opposite. The default value is <b>0</b>.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 20
     */
    NODE_SWIPER_MAINTAIN_VISIBLE_CONTENT_POSITION = 1001023,

    /**
     * @brief 指定<b>Swiper</b>组件的响应式列布局策略。
     * 该属性可以通过API根据需要设置、重置和获取。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：不同断点的列数。
     * 数据类型为{@link ArkUI_ItemFillPolicy}。\n
     * .value[1]？.i32：是否按分组分页。值<b>0</b>表示按单个子元素分页，
     * 和<b>1</b>表示按在视口中显示的子元素组进行分页。
     * 默认值为<b>0</b>。
     * \n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].i32：不同断点的列数。
     * 数据类型为{@link ArkUI_ItemFillPolicy}。\n
     * .value[1].i32：是否按分组分页。\n
     *
     * @ingroup Navigation Related Components
     * @since 22
     */
    NODE_SWIPER_ITEMFILLPOLICY = 1001024,

    /**
     * @brief: Set the delineation component of the ListItem, supporting property settings, property resets, and
     * property acquisition interfaces.
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
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_ITEM_SWIPE_ACTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST_ITEM,

    /**
     * @brief 设置 ListItemGroup 头部组件，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_NodeHandle}对象作为ListItemGroup头部组件。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_NodeHandle}对象作为ListItemGroup头部组件。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_ITEM_GROUP_SET_HEADER = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST_ITEM_GROUP,

    /**
     * @brief 设置 ListItemGroup 尾部组件，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_NodeHandle}对象作为ListItemGroup尾部组件。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_NodeHandle}对象作为ListItemGroup尾部组件。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_ITEM_GROUP_SET_FOOTER,

    /**
     * @brief 设置ListItem分割线样式，默认无分割线，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32 颜色，0xargb类型，默认值为0x08000000。</li>
     * <li>.value[1].f32 分割线宽，默认值：0，单位vp。</li>
     * <li>.value[2].f32 分割线距离列表侧边起始端的距离，默认值：0，单位vp。</li>
     * <li>.value[3].f32 分割线距离列表侧边结束端的距离，默认值：0，单位vp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32 颜色，0xargb类型。</li>
     * <li>.value[1].f32 分割线宽，单位vp。</li>
     * <li>.value[2].f32 分割线距离列表侧边起始端的距离，单位vp。</li>
     * <li>.value[3].f32 分割线距离列表侧边结束端的距离，单位vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_ITEM_GROUP_SET_DIVIDER,

    /**
     * @brief 设置ListItemGroup子组件默认主轴尺寸。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 参数格式为{@link ArkUI_ListChildrenMainSize}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 参数格式为{@link ArkUI_ListChildrenMainSize}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_LIST_ITEM_GROUP_CHILDREN_MAIN_SIZE = 1005003,

    /**
     * @brief ListItemGroup组件适配器，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_NodeAdapter}对象作为适配器。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 返回值格式为{@link ArkUI_NodeAdapter}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 15
     */
    NODE_LIST_ITEM_GROUP_NODE_ADAPTER = 1005004,

    /**
     * @brief Defines the horizontal alignment mode of child components in the column.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: horizontal alignment mode of child components. The parameter type is {@link ArkUI_HorizontalAlignment}. Default value: <b>ARKUI_HORIZONTAL_ALIGNMENT_CENTER</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: horizontal alignment mode of child components. The parameter type is {@link ArkUI_HorizontalAlignment}.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_COLUMN_ALIGN_ITEMS = MAX_NODE_SCOPE_NUM * ARKUI_NODE_COLUMN,

    /**
     * @brief Defines the vertical alignment mode of child components in the column.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: vertical alignment mode of child components. The parameter type is {@link ArkUI_FlexAlignment}. Default value: <b>ARKUI_FLEX_ALIGNMENT_START</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: vertical alignment mode of child components. The parameter type is {@link ArkUI_FlexAlignment}.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_COLUMN_JUSTIFY_CONTENT,

    /**
     * @brief 定义 Row 构造器选项或 Column 构造器选项，用于设置子组件的间距，可以通过 API 根据需要进行设置、重置和获取。
     *
     * 设置属性的 {@link ArkUI_AttributeItem} 参数格式：
     * .value[0].f32: 子组件的间距，单位为 vp。
     *
     * 返回值 {@link ArkUI_AttributeItem} 的格式：
     * .value[0].f32: 子组件的间距，单位为 vp。
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_LINEAR_LAYOUT_SPACE,

    /**
     * @brief 定义 Column 或 Row 中子组件沿主轴方向的排列是否反转，可以通过 API 根据需要进行设置、重置和获取。
     *
     * 设置属性的 {@link ArkUI_AttributeItem} 参数格式：
     * .value[0].i32: 确定子组件沿主轴方向排列是否反转的值。
     *
     * 返回值 {@link ArkUI_AttributeItem} 的格式：
     * .value[0].i32: 确定子组件沿主轴方向排列是否反转的值。
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_LINEAR_LAYOUT_REVERSE,

    /**
     * @brief Defines the vertical alignment mode of child components in the row.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: vertical alignment mode of child components. The parameter type is {@link ArkUI_VerticalAlignment}. Default value: <b>ARKUI_VERTICAL_ALIGNMENT_CENTER</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: vertical alignment mode of child components. The parameter type is {@link ArkUI_VerticalAlignment}.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_ROW_ALIGN_ITEMS = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ROW,

    /**
     * @brief Defines the horizontal alignment mode of child components in the row.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0].i32: horizontal alignment mode of child components. The parameter type is {@link ArkUI_FlexAlignment}. Default value: <b>ARKUI_FLEX_ALIGNMENT_START</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: horizontal alignment mode of child components. The parameter type is {@link ArkUI_FlexAlignment}.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_ROW_JUSTIFY_CONTENT,

    /**
     * @brief Defines the flex attribute. This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Format of the {@link ArkUI_AttributeItem} parameter for setting the attribute:**
     * <ul>
     * <li>.value[0]?.i32: direction in which flex items are arranged. The parameter type is {@link ArkUI_FlexDirection}. The default value is <b>ARKUI_FLEX_DIRECTION_ROW</b>.</li>
     * <li>.value[1]?.i32: how the flex items are wrapped. The parameter type is {@link ArkUI_FlexWrap}. The default value is <b>ARKUI_FLEX_WRAP_NO_WRAP</b>.</li>
     * <li>.value[2]?.i32: alignment mode along the main axis. The parameter type is {@link ArkUI_FlexAlignment}. The default value is <b>ARKUI_FLEX_ALIGNMENT_START</b>.</li>
     * <li>.value[3]?.i32: alignment mode along the cross axis. The parameter type is {@link ArkUI_ItemAlignment}. The default value is <b>ARKUI_ITEM_ALIGNMENT_START</b>.</li>
     * <li>.value[4]?.i32: alignment mode along the cross axis for multi-line content. The parameter type is {@link ArkUI_FlexAlignment}. The default value is <b>ARKUI_FLEX_ALIGNMENT_START</b>.</li>
     * </ul>
     *
     * **Format of the return value {@link ArkUI_AttributeItem}:**
     * <ul>
     * <li>.value[0].i32: direction in which flex items are arranged.</li>
     * <li>.value[1].i32: how the flex items are wrapped.</li>
     * <li>.value[2].i32: alignment mode along the main axis.</li>
     * <li>.value[3].i32: alignment mode along the cross axis.</li>
     * <li>.value[4].i32: alignment mode along the cross axis for multi-line content.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_FLEX_OPTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_FLEX,

    /**
     * @brief 定义 Flex 构造器选项，用于设置子组件的间距，可以通过 API 根据需要进行设置、重置和获取。
     *
     * 设置属性的 {@link ArkUI_AttributeItem} 参数格式：
     * .value[0].f32: flex 容器主轴上的间距，单位为 vp。
     * .value[1].f32: flex 容器交叉轴上的间距，单位为 vp。
     *
     * 返回值 {@link ArkUI_AttributeItem} 的格式：
     * .value[0].f32: flex 容器主轴上的间距，单位为 vp。
     * .value[1].f32: flex 容器交叉轴上的间距，单位为 vp。
     *
     * @ingroup Layout
     * @since 23
     */
    NODE_FLEX_SPACE,

    /**
     * @brief 设置组件是否正在刷新，支持属性设置，属性获取。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 参数值为1或者0，1表示正在刷新，0表示不在刷新。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 参数值为1或者0，1表示正在刷新，0表示不在刷新。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_REFRESH_REFRESHING = MAX_NODE_SCOPE_NUM * ARKUI_NODE_REFRESH,

    /**
     * @brief 设置下拉区域的自定义内容，支持属性设置和重置。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 参数类型{@link ArkUI_NodeHandle}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_REFRESH_CONTENT,

    /**
     * @brief 设置下拉跟手系数，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 下拉跟手系数，取值范围：[0, 1]。设置小于0或大于1的值时，属性设置失败。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 下拉跟手系数，取值范围：[0, 1]。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_REFRESH_PULL_DOWN_RATIO = 1009002,

    /**
     * @brief 设置触发刷新的下拉偏移量，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 下拉偏移量，单位vp， 默认值：64vp。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 下拉偏移量，单位vp， 默认值：64vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_REFRESH_OFFSET = 1009003,

    /**
     * @brief 设置当下拉距离超过refreshOffset时是否触发刷新，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否触发刷新。支持取值为0或1，其中1为触发刷新，0为不触发刷新。默认值：1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否触发刷新，1为触发刷新，0为不触发刷新。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_REFRESH_PULL_TO_REFRESH = 1009004,

    /**
     * @brief 设置刷新的最大下拉距离。支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 最大下拉距离，单位：vp。取值范围：[0, +∞)，设置小于0的值时按0处理。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 最大下拉距离，单位：vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 20
     */
    NODE_REFRESH_MAX_PULL_DOWN_DISTANCE = 1009005,

    /**
     * @brief 设置上划是否取消刷新。支持属性设置，属性重置和属性获取。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 上划是否取消刷新。支持取值为0或1，其中0为上划不取消刷新，1为上划取消刷新。默认值：1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 上划是否取消刷新。0为上划不取消刷新，1为上划取消刷新。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 23
     */
    NODE_REFRESH_PULL_UP_TO_CANCEL_REFRESH = 1009006,

    /**
     * @brief 定义瀑布流组件布局主轴方向，支持属性设置、重置和获取。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 主轴方向，参数类型{@link ArkUI_FlexDirection}。默认值{@link ARKUI_FLEX_DIRECTION_COLUMN}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 主轴方向，参数类型{@link ArkUI_FlexDirection}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_WATER_FLOW_LAYOUT_DIRECTION = MAX_NODE_SCOPE_NUM * ARKUI_NODE_WATER_FLOW,

    /**
     * @brief 设置当前瀑布流组件布局列的数量，不设置时默认1列，支持属性设置、重置和获取。例如，'1fr 1fr 2fr' 是将父组件分3列，将父组件允许的宽分为4等份，第1列占1份，第2列占1份，第3列占2份。
     * 可使用columnsTemplate('repeat(auto-fill,track-size)')根据给定的列宽track-size自动计算列数，其中repeat、auto-fill为关键字，
     * track-size为可设置的宽度，支持的单位包括px、vp、%或有效数字，默认单位为vp。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string 布局列的数量。默认值：'1fr'。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string 布局列的数量。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_WATER_FLOW_COLUMN_TEMPLATE,

    /**
     * @brief 设置当前瀑布流组件布局行的数量，不设置时默认1行，支持属性设置、重置和获取。例如，'1fr 1fr 2fr'是将父组件分3行，将父组件允许的高分为4等份，第1行占1份，第2行占1份，第3行占2份。
     * 可使用rowsTemplate('repeat(auto-fill,track-size)')根据给定的行高track-size自动计算行数，其中repeat、auto-fill为关键字，track-size为可设置的高度，
     * 支持的单位包括px、vp、%或有效数字，默认单位为vp。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string 布局行的数量。默认值：'1fr'。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string 布局行的数量。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_WATER_FLOW_ROW_TEMPLATE,

    /**
     * @brief 设置列与列的间距，支持属性设置、重置和获取。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 列与列的间距，默认值：0，单位vp。取值范围：[0, +∞)。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 列与列的间距，单位vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_WATER_FLOW_COLUMN_GAP,

    /**
     * @brief 设置行与行的间距，支持属性设置、重置和获取。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 行与行的间距，默认值：0，单位vp。取值范围：[0, +∞)。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 行与行的间距，单位vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_WATER_FLOW_ROW_GAP,

    /**
     * @brief 设置FlowItem分组配置信息，支持属性设置、重置和获取。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 从0开始计算的索引，会转换为整数，表示要开始改变分组的位置。</li>
     * <li>.object 参数格式为{@link ArkUI_WaterFlowSectionOption}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 返回值格式为{@link ArkUI_WaterFlowSectionOption}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_WATER_FLOW_SECTION_OPTION,

    /**
     * @brief WaterFlow组件适配器，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_NodeAdapter}对象作为适配器。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 返回值格式为{@link ArkUI_NodeAdapter}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_WATER_FLOW_NODE_ADAPTER,

    /**
     * @brief WaterFlow组件Adapter缓存数量，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 配合WaterFlow组件Adapter使用，设置adapter中的缓存数量。</li>
     * <li>.value[1]?.i32 是否显示缓存节点，0：不显示，1：显示，默认值：0。该参数从API version 16开始支持。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 adapter中的缓存数量。</li>
     * <li>.value[1].i32 是否显示缓存节点，0：不显示，1：显示。该参数从API version 16开始支持。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_WATER_FLOW_CACHED_COUNT,

    /**
     * @brief 设置瀑布流组件末尾的自定义显示组件。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 参数类型{@link ArkUI_NodeHandle}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_WATER_FLOW_FOOTER,

    /**
     * @brief 滑动到指定index。开启smooth动效时，会对经过的所有item进行加载和布局计算，当大量加载item时会导致性能问题。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 要滑动到的目标元素在当前容器中的索引值。</li>
     * <li>.value[1]?.i32 设置滑动到列表项在列表中的索引值时是否有动效，1表示有动效，0表示没有动效。默认值：0。</li>
     * <li>.value[2]?.i32 指定滑动到的元素与当前容器的对齐方式，参数类型{@link ArkUI_ScrollAlignment}。默认值为：{@link ARKUI_SCROLL_ALIGNMENT_START}
     * 。</li>
     * <li>.value[3]?.f32 滑动到目标元素后的额外偏移量，默认值：0，单位：vp。如果值为正数，则向底部额外偏移；如果值为负数，则向顶部额外偏移。该参数从API version 23开始支持。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_WATER_FLOW_SCROLL_TO_INDEX,

    /**
     * @brief 设置当前瀑布流子组件的约束尺寸属性，约束子组件尺寸范围，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 最小宽度，单位：vp。使用-1表示不设置。</li>
     * <li>.value[1].f32 最大宽度，单位：vp。使用-1表示不设置。</li>
     * <li>.value[2].f32 最小高度，单位：vp。使用-1表示不设置。</li>
     * <li>.value[3].f32 最大高度，单位：vp。使用-1表示不设置。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 最小宽度，单位：vp。使用-1表示不设置。</li>
     * <li>.value[1].f32 最大宽度，单位：vp。使用-1表示不设置。</li>
     * <li>.value[2].f32 最小高度，单位：vp。使用-1表示不设置。</li>
     * <li>.value[3].f32 最大高度，单位：vp。使用-1表示不设置。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_WATER_FLOW_ITEM_CONSTRAINT_SIZE,

    /**
     * @brief 定义瀑布流组件布局模式，支持属性设置、重置和获取。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 布局模式，参数类型{@link ArkUI_WaterFlowLayoutMode}，
     * 默认值：{@link ARKUI_WATER_FLOW_LAYOUT_MODE_ALWAYS_TOP_DOWN}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 布局模式，参数类型{@link ArkUI_WaterFlowLayoutMode}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 18
     */
    NODE_WATER_FLOW_LAYOUT_MODE,

    /**
     * @brief WaterFlow组件是否同步加载子节点，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 WaterFlow组件是否同步加载子节点。0：分帧加载，1：同步加载。默认值：1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 WaterFlow组件是否同步加载子节点。0：分帧加载，1：同步加载。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 20
     */
    NODE_WATER_FLOW_SYNC_LOAD = 1010012,

    /**
     * @brief WaterFlow组件的响应式列数布局策略，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 在不同断点规格下的列数，数据类型{@link ArkUI_ItemFillPolicy}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 在不同断点规格下的列数，数据类型{@link ArkUI_ItemFillPolicy}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 22
     */
    NODE_WATER_FLOW_COLUMN_TEMPLATE_ITEMFILLPOLICY = 1010013,

    /**
     * @brief 设置当前WaterFlow组件是否支持在LazyForEach或Repeat中使用if/else渲染控制语法生成不包含任何子组件的空分支节点。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     * > **说明：**
     * >
     * > 当通过{@link NODE_WATER_FLOW_SECTION_OPTION}设置了{@link ArkUI_WaterFlowSectionOption}分组，
     * > 或通过{@link NODE_WATER_FLOW_LAYOUT_MODE}设置为{@link ARKUI_WATER_FLOW_LAYOUT_MODE_SLIDING_WINDOW}
     * > 布局模式时，设置0或1时空分支后的FlowItem都会显示。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 WaterFlow组件是否支持空分支。0：不支持，1：支持。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 WaterFlow组件是否支持空分支。0：不支持，1：支持。</li>
     * </ul>
     *
     * 当通过{@link NODE_WATER_FLOW_SECTION_OPTION}设置了{@link ArkUI_WaterFlowSectionOption}分组，
     * 或通过{@link NODE_WATER_FLOW_LAYOUT_MODE}设置为{@link ARKUI_WATER_FLOW_LAYOUT_MODE_SLIDING_WINDOW}
     * 布局模式时，设置0或1时空分支后的FlowItem都会显示。
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_WATER_FLOW_SUPPORT_EMPTY_BRANCH_IN_LAZY_LOADING = 1010014,

    /**
     * @brief Set the auxiliary line in the RelativeContainer container, supporting property setting,
     * property reset and property acquisition interfaces.
     *
     * **Attribute setting method parameter {@link ArkUI_AttributeItem} format:**
     * <ul>
     * <li>.object: Auxiliary lines within the RelativeContainer container:.</li>
     * </ul>
     *
     * **Attribute acquisition method return value {@link ArkUI_AttributeItem} format:**
     * <ul>
     * <li>.object: Auxiliary lines within the RelativeContainer container:.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_RELATIVE_CONTAINER_GUIDE_LINE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_RELATIVE_CONTAINER,

    /**
     * @brief Sets the barrier within the RelativeContainer container and supports property setting,
     * property reset and property acquisition interfaces.
     *
     * **Attribute setting method parameter {@link ArkUI_AttributeItem} format:**
     * <ul>
     * <li>.object: Barrier within the RelativeContainer container:.</li>
     * </ul>
     *
     * **Attribute acquisition method return value {@link ArkUI_AttributeItem} format:**
     * <ul>
     * <li>.object: Barrier within the RelativeContainer container:.</li>
     * </ul>
     *
     * @ingroup Layout
     */
    NODE_RELATIVE_CONTAINER_BARRIER,

    /**
     * @brief 设置当前Grid组件布局列的数量，不设置时默认1列，支持属性设置、重置和获取。例如，'1fr 1fr 2fr' 是将父组件分3列，将父组件允许的宽分为4等份，第1列占1份，第2列占1份，第3列占2份。
     * 可使用columnsTemplate('repeat(auto-fill,track-size)')根据给定的列宽track-size自动计算列数，其中repeat、auto-fill为关键字，
     * track-size为可设置的宽度，支持的单位包括px、vp、%或有效数字，默认单位为vp。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string 布局列的数量。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string 布局列的数量。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_GRID_COLUMN_TEMPLATE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_GRID,

    /**
     * @brief 设置当前Grid布局行的数量或最小行高值，不设置时默认1行，支持属性设置、重置和获取。例如，'1fr 1fr 2fr'是将父组件分3行，将父组件允许的高分为4等份，第1行占1份，第2行占1份，第3行占2份。
     * 可使用rowsTemplate('repeat(auto-fill,track-size)')根据给定的行高track-size自动计算行数，其中repeat、auto-fill为关键字，track-size为可设置的高度，
     * 支持的单位包括px、vp、%或有效数字，默认单位为vp。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string 布局行的数量。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.string 布局行的数量。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_GRID_ROW_TEMPLATE,

    /**
     * @brief 设置列与列的间距，支持属性设置、重置和获取。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 列与列的间距，默认值：0，单位vp。取值范围：[0, +∞)。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 列与列的间距，单位vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_GRID_COLUMN_GAP,

    /**
     * @brief 设置行与行的间距，支持属性设置、重置和获取。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 行与行的间距，默认值：0，单位vp。取值范围：[0, +∞)。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 行与行的间距，单位vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_GRID_ROW_GAP,

    /**
     * @brief Grid组件适配器，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_NodeAdapter}对象作为适配器。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 返回值格式为{@link ArkUI_NodeAdapter}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_GRID_NODE_ADAPTER,

    /**
     * @brief Grid组件适配器缓存数量，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 配合Grid组件适配器使用，设置{@link ArkUI_NodeAdapter}的缓存数量。</li>
     * <li>.value[1].i32 是否显示缓存节点，0：不显示缓存节点，1：显示缓存节点。可选参数，默认值：0。从API版本26.0.0开始支持。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件适配器的缓存数量。</li>
     * <li>.value[1].i32 是否显示缓存节点，0：不显示，1：显示。该参数从API版本26.0.0开始支持。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
    NODE_GRID_CACHED_COUNT,

    /**
     * @brief Grid组件走焦换行模式，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件走焦换行模式，参数取值为{@link ArkUI_FocusWrapMode}下的枚举，默认值为ARKUI_FOCUS_WRAP_MODE_DEFAULT。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件走焦换行模式，参数类型{@link ArkUI_FocusWrapMode}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 20
     */
    NODE_GRID_FOCUS_WRAP_MODE = 1013006,

    /**
     * @brief Grid组件是否同步加载子节点，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否同步加载子节点。0：分帧加载，1：同步加载。默认值：1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否同步加载子节点。0：分帧加载，1：同步加载。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 20
     */
    NODE_GRID_SYNC_LOAD = 1013007,

    /**
     * @brief 设置Grid中GridItem的对齐方式，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid中GridItem的对齐方式，参数取值为{@link ArkUI_GridItemAlignment}下的枚举，
     * 默认值为ARKUI_GRID_ITEM_ALIGNMENT_DEFAULT。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid中GridItem的对齐方式，参数类型{@link ArkUI_GridItemAlignment}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 22
     */
    NODE_GRID_ALIGN_ITEMS = 1013008,

    /**
     * @brief 设置Grid布局选项，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 参数格式为{@link ArkUI_GridLayoutOptions}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 返回值格式为{@link ArkUI_GridLayoutOptions}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 22
     */
    NODE_GRID_LAYOUT_OPTIONS = 1013009,

    /**
     * @brief Grid组件的响应式列数布局策略，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 在不同断点规格下的列数，数据类型{@link ArkUI_ItemFillPolicy}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 在不同断点规格下的列数，数据类型{@link ArkUI_ItemFillPolicy}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 22
     */
    NODE_GRID_COLUMN_TEMPLATE_ITEMFILLPOLICY = 1013010,

    /**
     * @brief Grid组件是否进入编辑模式。进入编辑模式后，可以通过NODE_GRID_ON_ITEM_DRAG_START事件拖拽GridItem。支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否进入编辑模式。0：不可编辑，1：可以编辑。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否进入编辑模式。0：不可编辑，1：可以编辑。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 23
     */
    NODE_GRID_EDIT_MODE = 1013011,

    /**
     * @brief Grid组件是否启用GridItem拖拽动画。支持属性设置，属性重置和属性获取接口。
     * 仅在滚动模式下（只设置NODE_GRID_ROW_TEMPLATE、NODE_GRID_COLUMN_TEMPLATE其中一个）支持动画。
     * 仅在大小规则的Grid中支持拖拽动画，跨行或跨列场景不支持。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否启用GridItem拖拽动画。0：不启用，1：启用。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否启用GridItem拖拽动画。0：不启用，1：启用。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 23
     */
    NODE_GRID_DRAG_ANIMATION = 1013012,

    /**
     * @brief Grid组件是否启用鼠标框选。支持属性设置，属性重置和属性获取接口。
     * 启用后在Grid范围内鼠标框选会触发GridItem的[NODE_GRID_ITEM_ON_SELECT](./capi-native-node-h.md#arkui_nodeeventtype)事件。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否启用鼠标框选。0：不启用，1：启用。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否启用鼠标框选。0：不启用，1：启用。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 23
     */
    NODE_GRID_MULTI_SELECTABLE = 1013013,

    /**
     * @brief 滑动到指定index。
     * 开启动效时，会对经过的所有子组件进行加载和布局计算，当大量加载子组件时会导致性能问题。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 要滑动到的目标元素在当前容器中的索引值。</li>
     * <li>.value[1]?.i32 设置滑动到目标元素时是否有动效，1表示有动效，0表示没有动效。默认值：0。</li>
     * <li>.value[2]?.i32 指定滑动到的目标元素与当前容器的对齐方式，参数类型{@link ArkUI_ScrollAlignment}。默认值：ARKUI_SCROLL_ALIGNMENT_AUTO。</li>
     * <li>.value[3]?.f32 滑动到目标元素后的额外偏移量，默认值：0，单位：vp。如果值为正数，则向底部额外偏移；如果值为负数，则向顶部额外偏移。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 23
     */
    NODE_GRID_SCROLL_TO_INDEX = 1013014,

    /**
     * @brief 设置当前Grid组件是否支持在LazyForEach或Repeat中使用if/else渲染控制语法生成不包含任何子组件的空分支节点。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否支持空分支。0：不支持，1：支持。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否支持空分支。0：不支持，1：支持。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 23
     */
    NODE_GRID_SUPPORT_EMPTY_BRANCH_IN_LAZY_LOADING = 1013015,

    /**
     * @brief 设置Grid组件是否启用编辑模式。进入编辑模式后，默认显示复选框，并支持手指滑动多选。支持属性设置、属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否启用编辑模式。0：不启用，1：启用。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否启用编辑模式。0：未启用，1：已启用。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_GRID_ENABLE_EDIT_MODE = 1013016,

    /**
     * @brief 设置Grid组件的编辑模式选项，支持属性设置、属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否使用默认多选样式。0：不使用，1：使用。默认值：1。</li>
     * <li>.value[1].i32 Grid组件是否启用双指滑动多选。0：不启用，1：启用。默认值：1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 Grid组件是否使用默认多选样式。0：不使用，1：使用。</li>
     * <li>.value[1].i32 Grid组件是否启用双指滑动多选。0：未启用，1：已启用。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_GRID_EDIT_MODE_OPTIONS = 1013017,

    /**
     * @brief 设置GridItem样式，支持属性设置，属性重置和属性获取。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 GridItem样式，参数取值为{@link ArkUI_GridItemStyle}下的枚举，默认值为ARKUI_GRID_ITEM_STYLE_NONE。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 GridItem样式，参数类型{@link ArkUI_GridItemStyle}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 22
     */
    NODE_GRID_ITEM_STYLE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_GRID_ITEM,

    /**
     * @brief 设置GridItem是否可以被鼠标框选。支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 GridItem是否可以被鼠标框选。0：不可以，1：可以。默认值：1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 GridItem是否可以被鼠标框选。0：不可以，1：可以。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 23
     */
    NODE_GRID_ITEM_SELECTABLE = 1014001,

    /**
     * @brief 设置GridItem选中状态。支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 GridItem选中状态。0：未选中，1：已选中。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 GridItem选中状态。0：未选中，1：已选中。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 23
     */
    NODE_GRID_ITEM_SELECTED = 1014002,

    /**
     * @brief 设置每一个选择项列宽，支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：设置的第1个选择项列宽，为总宽度的百分比。默认情况下，所有选择项的列宽相等，默认值为不设置时各列均分。</li>
     * <li>.value[1]?.f32：设置的第2个选择项列宽，为总宽度的百分比。默认情况下，所有选择项的列宽相等。</li>
     * <li>.value[2]?.f32：设置的第3个选择项列宽，为总宽度的百分比。默认情况下，所有选择项的列宽相等。</li>
     * <li>...</li>
     * <li>.value[n]?.f32：设置的第n+1个选择项列宽，为总宽度的百分比。默认情况下，所有选择项的列宽相等。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：第1列宽度，总宽度的百分比。</li>
     * <li>.value[1].f32：第2列宽度，总宽度的百分比。</li>
     * <li>.value[2].f32：第3列宽度，总宽度的百分比。</li>
     * <li>...</li>
     * <li>.value[n].f32：第n+1列宽度，总宽度的百分比。</li>
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     * @since 18
     */
    NODE_TEXT_PICKER_COLUMN_WIDTHS = 15009,

    /**
     * @brief 定义用于启动EmbeddedAbility的目标。
     * 该属性可以通过API进行设置。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：
     * .object:EmbeddedComponent的对象，参数类型为{@ActivityBase_Want}。 默认值为<b>nullptr</b>.
     *  。
     *
     * @ingroup EmbeddedComponent
     * @since 20
     */
    NODE_EMBEDDED_COMPONENT_WANT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_EMBEDDED_COMPONENT,

    /**
     * @brief 设置EMBEDDED_COMPONENT的onError和onTermination回调。
     * 该属性可以通过API进行设置。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：
     * .object:EmbeddedComponent的选项，参数类型为{@ArkUI_EmbedComponentOption}。
     *
     * @ingroup EmbeddedComponent
     * @since 20
     */
    NODE_EMBEDDED_COMPONENT_OPTION,

    /**
     * @brief 定义选择器数据选择范围内默认选中项的索引。
     * 支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：索引值。默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].u32：选择器数据选择范围内当前选中项的索引。</li>
     * </ul>
     *
     * @ingroup Picker[容器滑动选择器]
     * @since 23
     */
    NODE_PICKER_OPTION_SELECTED_INDEX = MAX_NODE_SCOPE_NUM * ARKUI_NODE_PICKER,

    /**
     * @brief 定义是否启用触控反馈。支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用触控反馈。1表示启用反馈，0表示不启用。默认值：1。开启后，是否存在触控反馈取决于系统硬件支持情况。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否启用触控反馈。1表示启用反馈，0表示不启用。是否存在触控反馈取决于系统硬件支持情况。</li>
     * </ul>
     *
     * @ingroup Picker[容器滑动选择器]
     * @since 23
     */
    NODE_PICKER_ENABLE_HAPTIC_FEEDBACK = 1018001,

    /**
     * @brief 定义选择器是否支持滚动循环。支持属性设置，属性重置和属性获取接口。
     * 使用场景：循环滚动适用于选项有限且希望提供快速选择体验的场景（如性别选择）；非循环滚动适用于选项有明确边界、需要限制用户选择范围的场景。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否支持滚动循环。1表示支持滚动循环，0表示不支持。默认值：1。如果子组件的个数小于8个，无论设置为1还是0，都不会循环滚动。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：是否支持滚动循环。返回0表示不支持滚动循环，返回1表示支持滚动循环。</li>
     * </ul>
     *
     * @ingroup Picker[容器滑动选择器]
     * @since 23
     */
    NODE_PICKER_CAN_LOOP = 1018002,

    /**
     * @brief Sets the type and parameters of the selection indicator.
     * This attribute can be set, reset, and obtained as required through APIs.
     *
     * **Attribute setting method parameter {@link ArkUI_AttributeItem} Format:**
     * <ul>
     * <li>.object: Parameter type {@link ArkUI_Picker[容器滑动选择器]IndicatorStyle}.</li>
     * </ul>
     *
     * **Attribute fetch method return value {@link ArkUI_AttributeItem} format:**
     * <ul>
     * <li>.object: Parameter type {@link ArkUI_Picker[容器滑动选择器]IndicatorStyle}.</li>
     * </ul>
     *
     * @ingroup Picker[容器滑动选择器]
     * @since 23
     */
    NODE_PICKER_SELECTION_INDICATOR = 1018003,

    /**
     * @brief 设置Picker容器可见选项的数量，语义与ArkTS侧UIPickerComponent的displayedItemCount一致。
     * 未设置时，可见选项为7行。Picker为立体滚轮样式时，除选中项外的选项会按角度旋转，实际可视高度会小于选项行高；若增大可见行数或行高，请相应增大容器高度，详见UIPickerComponent。
     * 支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：可见选项数量。取值范围为<b>[2, 9]</b>内的整数。传入小数时按向下取整处理；
     * 传入偶数时，会规范为不小于该值的奇数（例如2变为3、8变为9）。不在取值范围内时使用默认值<b>7</b>。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32：当前Picker容器可见选项的数量，取值范围为[2, 9]内的整数。</li>
     * </ul>
     *
     * @since 26.0.0
     */
    NODE_PICKER_DISPLAYED_ITEM_COUNT = 1018004,

    /**
     * @brief 设置Picker容器每个选项的高度，语义与ArkTS侧UIPickerComponent的itemHeight一致。
     * 未设置时，每个选项高度为40vp。CAPI以vp为单位传入高度值。
     * 支持属性设置，属性重置和属性获取接口。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：选项高度，单位为vp。有效范围为<b>[40, 64]</b>。小于40vp或大于64vp时使用默认值<b>40</b>vp。不支持百分比。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32：当前选项高度，单位为vp。</li>
     * </ul>
     *
     * @since 26.0.0
     */
    NODE_PICKER_ITEM_HEIGHT = 1018005,

    /**
     * @brief 设置ArcList组件表冠灵敏度，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 表冠灵敏度类型，数据类型{@link ArkUI_CrownSensitivity}，默认值为{@link ARKUI_CROWN_SENSITIVITY_MEDIUM}。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 表冠灵敏度类型，数据类型{@link ArkUI_CrownSensitivity}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_DIGITAL_CROWN_SENSITIVITY = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_LIST,

    /**
     * @brief 设置ArcList子组件主轴方向的间隔，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 子组件主轴方向的间隔，单位为vp，默认值0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 子组件主轴方向的间隔，单位：vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_SPACE = 1019001,

    /**
     * @brief 设置ArcList组件缓存数量，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 缓存数量。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 缓存数量。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_CACHED_COUNT = 1019002,

    /**
     * @brief 滑动到指定索引值对应的列表项。开启动效时，会对经过的所有列表项进行加载和布局计算，当大量加载列表项时会导致性能问题。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 要滑动到的目标元素在当前容器中的索引值。传入-1时，指滑动到当前容器的最后一个元素。</li>
     * <li>.value[1]?.i32 设置滑动到指定索引值对应的列表项时是否有动效，1表示有动效，0表示没有动效。默认值：0。</li>
     * <li>.value[2]?.i32 指定滑动到的列表项与当前容器的对齐方式，参数类型{@link ArkUI_ScrollAlignment}，默认值：{@link ARKUI_SCROLL_ALIGNMENT_START}
     * 。</li>
     * <li>.value[3]?.f32 额外偏移量，默认值：0，单位：vp。正数表示向末尾端额外偏移，负数表示向起始端额外偏移。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_SCROLL_TO_INDEX = 1019003,

    /**
     * @brief 设置ArcList是否启用链式联动动效，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否启用链式联动动效，0：不启用，1：启用，默认值：0。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否启用链式联动动效。0：不启用，1：启用。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_CHAIN_ANIMATION = 1019004,

    /**
     * @brief 设置ArcList子组件默认主轴尺寸，支持属性设置和属性重置接口。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 参数格式为{@link ArkUI_ListChildrenMainSize}。
     * 定义ArcList的所有子项主轴尺寸信息的结构体。
     * 通过{@link OH_ArkUI_ListChildrenMainSizeOption_Create}接口来创建，
     * 并且可以使用{@link OH_ArkUI_ListChildrenMainSizeOption_Splice}方法
     * 对ArcList组件子项主轴尺寸数组进行大小调整。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_CHILDREN_MAIN_SIZE = 1019005,

    /**
     * @brief 设置ArcList头部组件，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_NodeHandle}对象作为ArcList头部组件。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_NodeHandle}对象作为ArcList头部组件。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_SET_HEADER = 1019006,

    /**
     * @brief 设置ArcList组件的滚动条状态，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 滚动条状态，数据类型{@link ArkUI_ScrollBarDisplayMode}，默认值为{@link ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO}。
     * </li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 滚动条状态，数据类型{@link ArkUI_ScrollBarDisplayMode}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_SCROLL_BAR = 1019007,

    /**
     * @brief 设置ArcList组件滚动条的颜色，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.data[0].u32 滚动条颜色，0xargb类型。默认值：0x66182431。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.data[0].u32 滚动条颜色，0xargb类型。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_SCROLL_BAR_COLOR = 1019008,

    /**
     * @brief 设置ArcList组件滚动条的宽度，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 滚动条宽度，单位vp，默认值4。 取值范围：[0, +∞)。设置为小于0的值时，按默认值处理。设置为0时，不显示滚动条。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 滚动条宽度，单位vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_SCROLL_BAR_WIDTH = 1019009,

    /**
     * @brief 设置ArcList是否支持滚动手势，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否支持滚动手势，默认值1。1：支持滚动手势，0：不支持滚动手势。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否支持滚动手势。1：支持滚动手势，0：不支持滚动手势。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_ENABLE_SCROLL_INTERACTION = 1019010,

    /**
     * @brief 设置ArcList边缘渐隐效果，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否使能边缘渐隐效果。0表示关闭边缘效果，1表示开启边缘效果。默认值：0。</li>
     * <li>.value[1]?.f32 边缘渐隐效果长度。单位：vp，默认值：32。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否使能边缘渐隐效果。0表示关闭边缘效果，1表示开启边缘效果。</li>
     * <li>.value[1].f32 边缘渐隐效果长度。单位：vp。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_FADING_EDGE = 1019011,

    /**
     * @brief 设置ArcList摩擦系数，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 摩擦系数，默认值：0.8。取值范围：(0, +∞)，设置为小于等于0的值时，按默认值处理。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 摩擦系数。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_FRICTION = 1019012,

    /**
     * @brief 设置ArcList限制Fling动效最大初始速度，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 Fling动效开始时的最大初始速度，单位：vp/s。默认值：9000。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].f32 Fling动效开始时的最大初始速度，单位：vp/s。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_FLING_SPEED_LIMIT = 1019013,

    /**
     * @brief 设置ArcListItem是否启用自动缩放，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否启用自动缩放，0：不启用，1：启用，默认值：1。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 是否启用自动缩放。0：不启用，1：启用。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_ITEM_AUTO_SCALE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_LIST_ITEM,

    /**
     * @brief 设置ArcListItem的划出组件，支持属性设置和属性重置接口。
     * 作为属性设置方法参数{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_ListItemSwipeActionOption}对象构造。
     * 定义ArcListItem的划出组件信息的结构体。
     * 通过{@link OH_ArkUI_ListItemSwipeActionOption_Create}接口来创建，
     * 并且可以使用{@link OH_ArkUI_ListItemSwipeActionOption_SetStart}方法
     * 设置ListItemSwipeActionItem左侧（垂直布局）或上方（横向布局）内容。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_LIST_ITEM_SWIPE_ACTION = 1020001,

    /**
     * @brief 设置ArcScrollBar绑定的可滚动组件，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_NodeHandle}对象作为滚动条绑定的可滚动组件。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.object 使用{@link ArkUI_NodeHandle}对象作为滚动条绑定的可滚动组件。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_SCROLL_BAR_BIND_SCROLLABLE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_SCROLL_BAR,

    /**
     * @brief 设置ArcScrollBar滚动条状态，支持属性设置，属性重置和属性获取接口。
     * 作为属性设置方法参数、属性获取方法返回值{@link ArkUI_AttributeItem}格式如下。
     *
     * **属性设置方法参数{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 滚动条状态，数据类型{@link ArkUI_ScrollBarDisplayMode}，默认值为ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO。</li>
     * </ul>
     *
     * **属性获取方法返回值{@link ArkUI_AttributeItem}格式：**
     * <ul>
     * <li>.value[0].i32 滚动条状态，数据类型{@link ArkUI_ScrollBarDisplayMode}。</li>
     * </ul>
     *
     * @ingroup Scrollable Container Component Attribute[滚动容器类组件相关属性]
     */
     * @since 26.0.0
     */
    NODE_ARC_SCROLL_BAR_DISPLAY_MODE = 1021001,

    /**
     * @brief 定义ArcSwiper当前显示的子组件的索引。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：子组件的索引值。默认值为<b>0</b>。\n
     * 返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：子组件的索引值。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_SWIPER_INDEX = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_SWIPER,

    /**
     * @brief 定义ArcSwiper的导航点类型。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：是否显示导航点。<b>1</b>表示显示导航点，\n
     * <b>0</b>表示相反的意思。默认值为<b>1</b>。\n
     * .value[1]？.i32：导航点的方向，参数类型为{@link OH_ArkUI_ArcDirection}。\n
     * 默认值为<b>OH_ARKUI_ARCDIRECTION_SIX_CLOCK_DIRECTION</b>。\n
     * .value[2]？.i32：未选中点的颜色，格式为0xARGB,\n
     * 默认值为<b>0xA9FFFFFF</b>。\n
     * .value[3]？.i32：选中点的颜色，格式为0xARGB，默认为<b>0xFF5EA1FF</b>。\n
     * .value[4]？.i32：长按后的背景颜色，格式为0xARGB,\n
     * 默认值为<b>0xFF5EA1FF</b>。\n
     * .?object：蒙版的渐变色。\n
     * 颜色断点数组，每个断点由一种颜色及其停止位置组成。\n
     * 参数类型为{@link ArkUI_ColorStop}。无效的颜色会被自动跳过。\n
     * colors：断点的颜色。\n
     * stop：断点的停止位置。\n
     * size：断点的个数。\n
     * 返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：是否显示导航点。\n
     * .value[1].i32：导航点的方向。\n
     * .value[2].i32：未选中点的颜色。\n
     * .value[3].i32：选中点的颜色。\n
     * .value[4].i32：长按后的背景颜色。\n
     * .object：蒙版的渐变色。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     *
     */
    NODE_ARC_SWIPER_INDICATOR,

    /**
     * @brief 定义动画时长。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：动画时长，单位为毫秒。默认值为<b>400</b>。\n
     * 返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：动画时长。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_SWIPER_DURATION,

    /**
     * @brief 定义是否垂直显示。
     * 可以通过API根据需要设置、重置和获取该属性。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：是否垂直显示。<b>1</b>表示垂直显示，\n
     * <b>0</b>表示相反的意思。默认值为<b>0</b>。\n
     * 返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：是否垂直显示。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_SWIPER_VERTICAL,

    /**
     * @brief 定义是否禁用滑动功能。
     * 该属性可以通过API根据需要设置、重置和获取。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：是否关闭滑动功能。值<b>1</b>表示禁用\n
     * 滑动功能，而<b>0</b>表示相反。默认值为<b>0</b>。\n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].i32：是否关闭滑动功能。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_SWIPER_DISABLE_SWIPE,

    /**
     * @brief 定义旋转表冠的灵敏度。
     * 该属性可以通过API根据需要设置、重置和获取。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：旋转表冠的灵敏度。参数类型为{@link ArkUI_CrownSensitivity}。\n
     * 默认值为<b>ARKUI_CROWN_SENSITIVITY_MEDIUM</b>。\n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].i32：旋转表冠的灵敏度。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_SWIPER_DIGITAL_CROWN_SENSITIVITY,

    /**
     * @brief 定义当到达可滚动内容的边界时，在ArcSwiper边缘使用的效果。
     * 该属性可以通过API根据需要设置、重置和获取。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：到达可滚动内容边界时，在滑动器边缘使用的效果。\n
     * 参数类型为{@link ArkUI_EdgeEffect}。\n
     * 默认值为<b>ARKUI_EDGE_EFFECT_SPRING</b>。\n
     * 返回值{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：到达可滚动内容边界时，在滑动器边缘使用的效果。\n
     * 参数类型为{@link ArkUI_EdgeEffect}。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_SWIPER_EFFECT_MODE,

    /**
     * @brief 定义是否禁用转场动画。
     * 该属性可以通过API根据需要设置、重置和获取。
     *
     * 设置属性{@link ArkUI_AttributeItem}格式：\n
     * .value[0].i32：是否禁用转场动画。值<b>1</b>表示禁用\n
     * 过渡动画，而<b>0</b>表示相反。默认值为<b>0</b>。\n
     * 返回值{@link ArkUI_AttributeItem}的格式为：\n
     * .value[0].i32：是否禁用转场动画。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_SWIPER_DISABLE_TRANSITION_ANIMATION
} ArkUI_NodeAttributeType;

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
     *
     * @ingroup Interaction Event [交互事件]
     */
    NODE_TOUCH_EVENT = 0,

    /**
     * @brief Defines the mount event.
     *
     * This event is triggered when the component is mounted and displayed. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Interaction Event [交互事件]
     */
    NODE_EVENT_ON_APPEAR,

    /**
     * @brief Defines the unmount event.
     *
     * This event is triggered when the component is unmounted and hidden. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Interaction Event [交互事件]
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
     * <li>ArkUI_NodeComponentEvent.data[6].f32</b>: new width of the target element, in vp. The value is a number.</li>
     * <li>ArkUI_NodeComponentEvent.data[7].f32</b>: new height of the target element, in vp. The value is a number.</li>
     * <li>ArkUI_NodeComponentEvent.data[8].f32</b>: new X coordinate of the target element's upper left corner relative
     * to the parent element's, in vp. The value type is number.</li>
     * <li>ArkUI_NodeComponentEvent.data[9].f32</b>: new Y coordinate of the target element's upper left corner relative
     * to the parent element's, in vp. The value type is number.</li>
     * <li>ArkUI_NodeComponentEvent.data[10].f32</b>: new X coordinate of the target element's upper left corner relative
     * to the page's, in vp. The value type is number.</li>
     * <li>ArkUI_NodeComponentEvent.data[11].f32</b>: new Y coordinate of the target element's upper left corner relative
     * to the page's, in vp. The value type is number.</li>
     * </ul>
     * @ingroup Interaction Event [交互事件]
     */
    NODE_EVENT_ON_AREA_CHANGE,

    /**
     * @brief Defines the focus event.
     *
     * This event is triggered when the component obtains the focus. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Interaction Event [交互事件]
     */
    NODE_ON_FOCUS,

    /**
     * @brief Defines the blur event.
     *
     * This event is triggered when the component loses the focus. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Interaction Event [交互事件]
     */
    NODE_ON_BLUR,

    /**
     * @brief Defines the click event.
     *
     * This event is triggered when the component is clicked. \n
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
     * @ingroup Interaction Event [交互事件]
     */
    NODE_ON_CLICK,

    /**
     * @brief Defines event interception.
     *
     * This event is triggered when the component is touched. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}. \n
     *
     * @ingroup Interaction Event [交互事件]
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
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32</b>: how the ratio of the component's visible area to its total area
     * changes compared to the previous one. The value <b>1</b> indicates an increase, and <b>0</b> indicates a
     * decrease.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32</b>: ratio of the component's visible area to its total area when this
     * callback is invoked.</li>
     * </ul>
     *
     * @ingroup Interaction Event [交互事件]
     */
    NODE_EVENT_ON_VISIBLE_AREA_CHANGE,

    /**
     * @brief Defines the event triggered when the mouse pointer is moved over or away from the component.
     *
      \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} contains one parameter:\n
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32</b>: whether the mouse pointer is hovered over the component.
     * The value <b>1</b> indicates that the mouse pointer is hovered over the component, and <b>0</b> indicates that
     * the mouse pointer is moved away from the component.</li>
     * </ul>
     *
     * @ingroup Interaction Event [交互事件]
     */
    NODE_ON_HOVER,

    /**
     * @brief Defines the click event.
     *
     * This event is triggered when the component is clicked by a mouse device button or when the mouse pointer moves
     * within the component. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}. \n
     *
     * @ingroup Interaction Event [交互事件]
     */
    NODE_ON_MOUSE,

    /**
     * @brief Defines the attach event.
     *
     * This event is triggered when the component is attached. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Interaction Event [交互事件]
     */
    NODE_EVENT_ON_ATTACH,

    /**
     * @brief Defines the detach event.
     *
     * This event is triggered when the component is detached. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup Interaction Event [交互事件]
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
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32</b>: corresponds to {@link ArkUI_PreDragStatus}.</li>
     * </ul>
     *
     * @ingroup Drag Event [拖拽事件]
     */
    NODE_ON_PRE_DRAG = 14,

    /**
     * @brief Called when the user starts to drag an ite
     *
     * A drag operation is recognized only when the dragged item is moved far enough. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Drag Event [拖拽事件]
     */
    NODE_ON_DRAG_START = 15,

    /**
     * @brief Called when a dragged item enters the boundaries of the current component.
     *
     * The current component refers to the component that listens for this event. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Drag Event [拖拽事件]
     */
    NODE_ON_DRAG_ENTER = 16,

    /**
     * @brief Called  when a dragged item moves in the current component.
     *
     * The current component refers to the component that listens for this event. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Drag Event [拖拽事件]
     */
    NODE_ON_DRAG_MOVE = 17,

    /**
     * @brief Called when a dragged item leaves the boundaries of the current component.
     *
     * The current component refers to the component that listens for this event. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Drag Event [拖拽事件]
     */
    NODE_ON_DRAG_LEAVE = 18,

    /**
     * @brief Called when a dragged item is dropped on the current component.
     * The component can obtain the drag data for processing through the callback.
     *
     * The current component refers to the component that listens for this event. \n
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Drag Event [拖拽事件]
     */
    NODE_ON_DROP = 19,

    /**
     * @brief Called when a drag operation ends.
     * The drag source can obtain the drag result by registering this callback.
     *
     * A drag operation ends when the dragged item is released.
     * When the event callback occurs, the {@link ArkUI_DragEvent} object can be obtained from the
     * {@link ArkUI_NodeEvent} object. \n
     *
     * @ingroup Drag Event [拖拽事件]
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
     * @ingroup Interaction Event [交互事件]
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
     * @ingroup Interaction Event [交互事件]
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
     * @ingroup Interaction Event [交互事件]
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
     * @ingroup Interaction Event [交互事件]
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
     * @ingroup Interaction Event [交互事件]
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
     * @ingroup Interaction Event [交互事件]
     *
     * @since 18
     */
    NODE_ON_CLICK_EVENT = 26,

    /**
     * @brief Defines the event triggered when the mouse pointer hovers over or moves away from a component.
     *
     * This event is triggered when the mouse pointer enters or leaves the component's bounding box. \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_UIInputEvent}. \n
     *
     * @ingroup Interaction Event [交互事件]
     *
     *@since 17
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
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32</b>: how the ratio of the component's visible area to its total area
     * changes compared to the previous one. The value <b>1</b> indicates an increase, and <b>0</b> indicates
     * a decrease.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32</b>: ratio of the component's visible area to its total area
     * when this callback is invoked.</li>
     * </ul>
     *
     * @ingroup Interaction Event [交互事件]
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
     *
     * @ingroup Interaction Event [交互事件]
     *
     * @since 15
     */
    NODE_ON_HOVER_MOVE = 29,

    /**
     * @brief 定义尺寸变化事件，当组件尺寸发生变化时会触发该事件。
     *
     * <br>事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * <br>{@link ArkUI_NodeComponentEvent}中包含四个参数：
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].f32：尺寸组件变化前的宽度。</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32：尺寸组件变化前的高度。</li>
     * <li>ArkUI_NodeComponentEvent.data[2].f32：尺寸组件变化后的宽度。</li>
     * <li>ArkUI_NodeComponentEvent.data[3].f32：尺寸组件变化后的高度。</li>
     * </ul>
     *
     * @ingroup Interaction Event [交互事件]
     *
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
     * @ingroup Interaction Event [交互事件]
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
     *
     * @ingroup Interaction Event [交互事件]
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
     * @ingroup Interaction Event [交互事件]
     *
     * @since 24
     */
    NODE_ON_DIGITAL_CROWN = 33,

    /**
     * @brief 当 <b>ARKUI_NODE_CUSTOM</b> 内容滚动时触发该事件。
     *
     * 当组件内容发生滚动时，该事件将被触发。  
     * 当事件回调发生时，可通过 {@link ArkUI_NodeComponentEvent} 获取 {@link ArkUI_NodeEvent} 对象。  
     * {@link ArkUI_NodeComponentEvent} 包含以下两个参数：
     *
     * - `ArkUI_NodeComponentEvent.data[0].i32`：正在滚动的子组件的 ID。  
     * - `ArkUI_NodeComponentEvent.data[1].f32`：滚动帧的偏移量，单位为像素（px）。
     * @since 24
     */
    NODE_ON_CUSTOM_OVERFLOW_SCROLL = 34,

    /**
     * @brief 当 <b>ARKUI_NODE_STACK</b> 内容滚动时触发该事件。
     *
     * 当组件内容发生滚动时，该事件将被触发。  
     * 当事件回调发生时，可通过 {@link ArkUI_NodeComponentEvent} 获取 {@link ArkUI_NodeEvent} 对象。  
     * {@link ArkUI_NodeComponentEvent} 包含以下两个参数：
     *
     * - `ArkUI_NodeComponentEvent.data[0].i32`：正在滚动的子组件的 ID。  
     * - `ArkUI_NodeComponentEvent.data[1].f32`：滚动帧的偏移量，单位为像素（px）。
     * @since 24
     */
    NODE_ON_STACK_OVERFLOW_SCROLL = 35,

    /**
     * @brief 定义组件获得焦点时需要判断是否需要软键盘时触发的事件。
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的union类型值为
     * {@link ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}不包含参数。
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
     * @ingroup Interaction Event [交互事件]
     *
     * @since 26.0.0
     */
    NODE_ON_GESTURE_COLLECT_INTERCEPT = 37,

    /**
     * @brief 文本设置TextDataDetectorConfig且识别成功时，触发onDetectResultUpdate回调。

     *
     * 触发该事件的条件：文本设置TextDataDetectorConfig且识别成功后。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n



     * **{@link ArkUI_StringAsyncEvent}中包含1个参数：**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：表示文本识别的结果，Json格式。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     */
    NODE_TEXT_ON_DETECT_RESULT_UPDATE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT,

    /**
     * @brief Span组件长按事件。
     *
     * 组件被长按时触发此回调。\n
     * 事件回调发生时，可从事件参数{@link ArkUI_NodeEvent}对象中获取{@link ArkUI_UIInputEvent}。\n
     * @ingroup Text Display[文本显示]
     * @since 20
     */
    NODE_TEXT_SPAN_ON_LONG_PRESS = 1001,

    /**
     * @brief 定义文本选择位置变化时触发的事件。
     *
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。 \n
     * **{@link ArkUI_NodeComponentEvent}包含两个参数：**





     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32：文本选择区域的起始位置。</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32：文本选择区域的结束位置。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 26.0.0
     */
    NODE_TEXT_ON_TEXT_SELECTION_CHANGE = 1002,

    /**
     * @brief 定义长按输入框时显示的剪贴板上的复制按钮被点击时触发的事件。
     *
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。 \n
     * **{@link ArkUI_StringAsyncEvent}包含一个参数：**






     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：复制的文本。</li>
     * </ul>
     *
     * @ingroup Text Display[文本显示]
     * @since 26.0.0
     */
    NODE_TEXT_ON_COPY = 1003,

    /**
     * @brief 定义复制文本前触发的事件。
     *
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。 \n
     * **{@link ArkUI_StringAsyncEvent}包含一个参数：**





     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：复制的文本。</li>
     * </ul>
     *
     * @return 是否允许复制。 \n

     * 可以通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}函数设置返回值。 \n
     * 返回值中索引为0的value.i32表示是否允许复制。
     * <b>0</b>：不允许复制；<b>1</b>：允许复制。 \n


     *
     * @ingroup Text Display[文本显示]
     * @since 26.0.0
     */
    NODE_TEXT_ON_WILL_COPY = 1004,

    /**
     * @brief 图片加载成功事件。
     *
     * 触发该事件的条件 ：图片数据加载成功和解码成功均触发该回调。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}中包含9个参数：\n















     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：表示加载状态，0表示数据加载成功，1表示解码成功。\n
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>：表示图片的宽度，单位px。\n
     * <b>ArkUI_NodeComponentEvent.data[2].f32</b>：表示图片的高度，单位px。\n
     * <b>ArkUI_NodeComponentEvent.data[3].f32</b>：表示当前组件的宽度，单位px。\n
     * <b>ArkUI_NodeComponentEvent.data[4].f32</b>：表示当前组件的高度，单位px。\n
     * <b>ArkUI_NodeComponentEvent.data[5].f32</b>：图片绘制区域相对组件X轴位置，单位px。\n
     * <b>ArkUI_NodeComponentEvent.data[6].f32</b>：图片绘制区域相对组件Y轴位置，单位px。\n
     * <b>ArkUI_NodeComponentEvent.data[7].f32</b>：图片绘制区域宽度，单位px。\n
     * <b>ArkUI_NodeComponentEvent.data[8].f32</b>：图片绘制区域高度，单位px。\n
     */
     * @ingroup Image
     */
    NODE_IMAGE_ON_COMPLETE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_IMAGE,

    /**
     * @brief 图片加载失败事件。
     *
     * 触发该事件的条件：图片加载异常时触发该回调。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n




     * {@link ArkUI_NodeComponentEvent}中包含1个参数：\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>错误码信息：\n
     * 401: 图片路径参数异常，无法获取到图片数据。\n
     * 103101: 图片格式不支持。\n


     */
     * @ingroup Image
     */
    NODE_IMAGE_ON_ERROR,

    /**
     * @brief SVG图片动效播放完成事件。
     *
     * 触发该事件的条件：带动效的SVG图片动画结束时触发。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}中不包含参数。




     */
     * @ingroup Image
     */
    NODE_IMAGE_ON_SVG_PLAY_FINISH,

    /**
     * @brief 定义图片下载过程中触发事件。
     *
     * 触发该事件的条件 ：页面组件下载网页图片时触发。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}中包含2个参数: \n





     * <b>ArkUI_NodeComponentEvent.data[0].u32</b>: 到目前为止已下载的字节数。 \n
     * <b>ArkUI_NodeComponentEvent.data[1].u32</b>: 要下载图片的总字节数。 \n
     */
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
     * @brief TextInput输入内容发生变化时触发该事件。
     *
     * 触发该事件的条件：输入内容发生变化时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n



     * **{@link ArkUI_StringAsyncEvent}中包含1个参数：**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：输入的文本内容。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_INPUT,

    /**
     * @brief TextInput按下输入法回车键触发该事件。
     *
     * 触发该事件的条件：按下输入法回车键。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n



     * **{@link ArkUI_NodeComponentEvent}中包含1个参数：**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32：输入法回车键类型。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ON_SUBMIT,

    /**
     * @brief 长按输入框内部区域弹出剪贴板后，点击剪切板剪切按钮，触发该回调。


     *
     * 触发该事件的条件：长按输入框内部区域弹出剪贴板后，点击剪切板剪切按钮。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n



     * **{@link ArkUI_StringAsyncEvent}中包含1个参数：**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：剪切的文本内容。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ON_CUT,

    /**
     * @brief 长按输入框内部区域弹出剪贴板后，点击剪切板粘贴按钮，触发该回调。


     *
     * 触发该事件的条件：长按输入框内部区域弹出剪贴板后，点击剪切板粘贴按钮。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n



     * **{@link ArkUI_StringAsyncEvent}中包含1个参数：**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：粘贴的文本内容。</li>
     * </ul>
     *
     * 从API版本26.0.0开始，回调函数可以返回是否允许粘贴。 \n
     * @return 是否允许粘贴。 \n


     * 可以通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}函数设置返回值。 \n
     * 返回值中索引为0的value.i32表示是否允许粘贴。 \n
     * <b>0</b>：不允许粘贴；<b>1</b>：允许粘贴。 \n


     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ON_PASTE,

    /**
     * @brief 文本选择的位置发生变化时，触发该回调。
     *
     * 触发该事件的条件：文本选择的位置发生变化时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * **{@link ArkUI_NodeComponentEvent}中包含2个参数：**





     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32：表示所选文本的起始位置。</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32：表示所选文本的结束位置。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ON_TEXT_SELECTION_CHANGE,

    /**
     * @brief 输入状态变化时，触发该回调。
     *
     * 触发该事件的条件：输入状态变化时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * **{@link ArkUI_NodeComponentEvent}中包含1个参数：**





     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32：true表示正在输入。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ON_EDIT_CHANGE,

    /**
     * @brief TextInput输入内容发生变化时触发该事件。
     *
     * 触发该事件的条件：输入内容发生变化时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * **{@link ArkUI_NodeComponentEvent}中包含2个参数：**



     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].f32：表示文本的宽度。</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32：表示文本的高度。</li>



     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ON_CONTENT_SIZE_CHANGE,

    /**
     * @brief 设置NODE_TEXT_INPUT_INPUT_FILTER，正则匹配失败时触发。
     *
     * 触发该事件的条件：正则匹配失败时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n
     * **{@link ArkUI_StringAsyncEvent}中包含1个参数：**




     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：表示正则匹配失败时，被过滤的内容。</li>


     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_INPUT_ON_INPUT_FILTER_ERROR,

    /**
     * @brief 文本内容滚动时，触发该回调。


     *
     * 触发该事件的条件：文本内容滚动时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * **{@link ArkUI_NodeComponentEvent}中包含2个参数：**



     * <ul>

     * <li>ArkUI_NodeComponentEvent.data[0].i32：表示文本在内容区的横坐标偏移。</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32：表示文本在内容区的纵坐标偏移。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     * @brief 定义TextInput组件在内容改变时（包含预上屏内容），触发回调的枚举值。


     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_TextChangeEvent}。\n
     * **{@link ArkUI_TextChangeEvent}包含参数：**
     * <ul>
     * <li>ArkUI_TextChangeEvent.pStr：TextInput的内容。</li>
     * <li>ArkUI_TextChangeEvent.pExtendStr：TextInput的预上屏内容。</li>
     * <li>ArkUI_TextChangeEvent.number：TextInput的预上屏起始位置。</li>

     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 15
     */
    NODE_TEXT_INPUT_ON_CHANGE_WITH_PREVIEW_TEXT = 7013,

    /**
     * @brief 定义TextInput组件在内容将要改变时（包含预上屏内容），触发回调的枚举值。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_TextChangeEvent}。\n
     * **{@link ArkUI_TextChangeEvent}包含参数：**
     * <ul>
     * <li>ArkUI_TextChangeEvent.pStr：TextInput的内容。</li>
     * <li>ArkUI_TextChangeEvent.pExtendStr：TextInput的预上屏内容。</li>
     * <li>ArkUI_TextChangeEvent.number：TextInput的预上屏起始位置。</li>

     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 20
     */
    NODE_TEXT_INPUT_ON_WILL_CHANGE = 7014,

    /**
     * @brief 定义当用户点击文本选择时显示的剪贴板上的复制按钮所触发的事件。


     * \n
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。 \n


     * **{@link ArkUI_StringAsyncEvent}包含一个参数：**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：复制的文本。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_ON_COPY = 7015,

    /**
     * @brief 定义复制文本前触发的事件。
     * \n
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。 \n


     * **{@link ArkUI_StringAsyncEvent}包含一个参数：**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：复制的文本。</li>
     * </ul>
     *
     * @return 是否允许复制。 \n

     * 可以通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}函数设置返回值。 \n
     * 返回值中索引为0的value.i32表示是否允许复制。
     * <b>0</b>：不允许复制；<b>1</b>：允许复制。 \n


     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_ON_WILL_COPY = 7016,

    /**
     * @brief 定义剪切文本前触发的事件。
     * \n
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。 \n


     * **{@link ArkUI_StringAsyncEvent}包含一个参数：**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：被剪切的文本。</li>
     * </ul>
     *
     * @return 是否允许剪切。 \n

     * 可以通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}函数设置返回值。 \n
     * 返回值中索引为0的value.i32表示是否允许剪切。
     * <b>0</b>：不允许剪切；<b>1</b>：允许剪切。 \n


     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     */
    NODE_TEXT_INPUT_ON_WILL_CUT = 7017,

    /**
     * @brief 输入内容发生变化时，触发该回调。
     *
     * 触发该事件的条件：输入内容发生变化时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n



     * **{@link ArkUI_StringAsyncEvent}中包含1个参数：**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：当前输入的文本内容。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_AREA,

    /**
     * @brief 长按输入框内部区域弹出剪贴板后，点击剪切板粘贴按钮，触发该回调。


     *
     * 触发该事件的条件：长按输入框内部区域弹出剪贴板后，点击剪切板粘贴按钮。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n



     * **{@link ArkUI_StringAsyncEvent}中包含1个参数：**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：粘贴的文本内容。</li>
     * </ul>
     *
     * 从API版本26.0.0开始，回调函数可以返回是否允许粘贴。\n
     * @return 是否允许粘贴。\n


     * 可以通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}函数设置返回值。\n
     * 返回值中索引为0的value.i32表示是否允许粘贴。\n
     * <b>0</b>：不允许；<b>1</b>：允许。\n


     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_ON_PASTE,

    /**
     * @brief 文本选择的位置发生变化时，触发该回调。
     *
     * 触发该事件的条件：文本选择的位置发生变化时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n



     * **{@link ArkUI_NodeComponentEvent}中包含2个参数：**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32：表示所选文本的起始位置。</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32：表示所选文本的结束位置。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_ON_TEXT_SELECTION_CHANGE,

    /**
     * @brief 设置NODE_TEXT_AREA_INPUT_FILTER，正则匹配失败时触发。
     *
     * 触发该事件的条件：正则匹配失败时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n
     * **{@link ArkUI_StringAsyncEvent}中包含1个参数：**




     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：表示正则匹配失败时，被过滤的内容。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_ON_INPUT_FILTER_ERROR,

    /**
     * @brief 文本内容滚动时，触发该回调。
     *
     * 触发该事件的条件：文本内容滚动时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * **{@link ArkUI_NodeComponentEvent}中包含2个参数：**




     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32：表示文本在内容区的横坐标偏移。</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32：表示文本在内容区的纵坐标偏移。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_ON_CONTENT_SCROLL,

    /**
     * @brief 输入状态变化时，触发该回调。


     *
     * 触发该事件的条件：输入状态变化时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n



     * **{@link ArkUI_NodeComponentEvent}中包含1个参数：**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32：true表示正在输入。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_ON_EDIT_CHANGE,

    /**
     * @brief TextArea按下输入法回车键触发该事件。
     *
     * 触发该事件的条件：按下输入法回车键。keyType为ARKUI_ENTER_KEY_TYPE_NEW_LINE时不触发\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * **{@link ArkUI_NodeComponentEvent}中包含1个参数：**




     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32：输入法回车键类型。</li>



     * </ul>
     *
     * @ingroup Text Input[文本输入]
     */
    NODE_TEXT_AREA_ON_SUBMIT,

    /**
     * @brief TextArea输入内容发生变化时触发该事件。
     *
     * 触发该事件的条件：输入内容发生变化时。\n
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。\n
     * **{@link ArkUI_NodeComponentEvent}中包含2个参数：**




     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].f32：表示文本的宽度。</li>
     * <li>ArkUI_NodeComponentEvent.data[1].f32：表示文本的高度。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
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
     * @brief 定义在删除完成时，触发回调的枚举值。
     *
     * 事件回调发生时，事件参数为{@link ArkUI_NodeEvent}。\n


     * 通过{@link OH_ArkUI_NodeEvent_GetNumberValue}获取到index为0的value.f32：删除的值的位置信息。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetNumberValue}获取到index为1的value.i32：删除值的方向，0为向后删除，1为向前删除。\n
     * 通过{@link OH_ArkUI_NodeEvent_GetStringValue}获取到index为0的buffer字符串：删除的值。
     * @ingroup Text Input[文本输入]






     */
    NODE_TEXT_AREA_ON_DID_DELETE = 8011,

    /**
     * @brief 定义TextArea组件在内容改变时（包含预上屏内容），触发回调的枚举值。


     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_TextChangeEvent}。\n
     * **{@link ArkUI_TextChangeEvent}包含参数：**
     * <ul>
     * <li>ArkUI_TextChangeEvent.pStr：TextArea的内容。</li>
     * <li>ArkUI_TextChangeEvent.pExtendStr：TextArea的预上屏内容。</li>
     * <li>ArkUI_TextChangeEvent.number：TextArea的预上屏起始位置。</li>

     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 15
     */
    NODE_TEXT_AREA_ON_CHANGE_WITH_PREVIEW_TEXT = 8012,

    /**
     * @brief 定义TextArea组件在内容将要改变时（包含预上屏内容），触发回调的枚举值。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_TextChangeEvent}。\n
     * **{@link ArkUI_TextChangeEvent}包含参数：**
     * <ul>
     * <li>ArkUI_TextChangeEvent.pStr：TextArea的内容。</li>
     * <li>ArkUI_TextChangeEvent.pExtendStr：TextArea的预上屏内容。</li>
     * <li>ArkUI_TextChangeEvent.number：TextArea的预上屏起始位置。</li>

     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 20
     */
    NODE_TEXT_AREA_ON_WILL_CHANGE = 8013,

    /**
     * @brief 定义长按输入框时显示的剪贴板上的复制按钮被点击时触发的事件。


     * \n
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。 \n


     * **{@link ArkUI_StringAsyncEvent}包含一个参数：**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：复制的文本。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     */
    NODE_TEXT_AREA_ON_COPY = 8014,

    /**
     * @brief 定义复制文本前触发的事件。
     * \n
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。\n
     * **{@link ArkUI_StringAsyncEvent}包含一个参数：**





     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：复制的文本。</li>
     * </ul>
     *
     * @return 是否允许复制。\n

     * 可以通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}函数设置返回值。\n
     * 返回值中索引为0的value.i32表示是否允许复制。
     * <b>0</b>：不允许复制；<b>1</b>：允许复制。\n


     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     */
    NODE_TEXT_AREA_ON_WILL_COPY = 8015,

    /**
     * @brief 定义点击剪贴板上的剪切按钮（长按文本框时显示）时触发的事件。


     * \n
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。 \n


     * **{@link ArkUI_StringAsyncEvent}包含一个参数：**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：被剪切的文本。</li>
     * </ul>
     *
     * @ingroup Text Input[文本输入]
     * @since 26.0.0
     */
    NODE_TEXT_AREA_ON_CUT = 8016,

    /**
     * @brief 定义剪切文本前触发的事件。
     * \n
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_StringAsyncEvent}。 \n


     * **{@link ArkUI_StringAsyncEvent}包含一个参数：**
     * <ul>
     * <li>ArkUI_StringAsyncEvent.pStr：被剪切的文本。</li>
     * </ul>
     *
     * @return 是否允许剪切。 \n

     * 可以通过{@link OH_ArkUI_NodeEvent_SetReturnNumberValue}函数设置返回值。 \n
     * 返回值中索引为0的value.i32表示是否允许剪切。
     * <b>0</b>：不允许剪切；<b>1</b>：允许剪切。 \n


     *
     * @ingroup Text Input[文本输入]
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
     * @brief 定义ARKUI_NODE_DATE_PICKER列表组件的滚动触摸事件枚举值。
     *
     * 触发该事件的条件：选择日期时触发该事件。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * **{@link ArkUI_NodeComponentEvent}包含3个参数：**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32：表示选中时间的年。</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32：表示选中时间的月，取值范围：[0-11]。</li>
     * <li>ArkUI_NodeComponentEvent.data[2].i32：表示选中时间的天。</li>
     * </ul>
     *
     * @ingroup Datepicker[日期选择器]
     */
    NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_DATE_PICKER,

    /**
     * @brief 定义ARKUI_NODE_TIME_PICKER列表组件的滚动触摸事件枚举值。
     *
     * 触发该事件的条件：选择时间时触发该事件。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * **{@link ArkUI_NodeComponentEvent}包含2个参数：**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32：表示选中时间的时，取值范围：[0-23]。</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32：表示选中时间的分，取值范围：[0-59]。</li>
     * </ul>
     *
     * @ingroup Timepicker[时间选择器]
     */
    NODE_TIME_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TIME_PICKER,

    /**
     * @brief 定义ARKUI_NODE_TEXT_PICKER列表组件的滚动触摸事件枚举值。
     *
     * 触发该事件的条件：选择文本时触发该事件。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * **{@link ArkUI_NodeComponentEvent}包含1个参数：**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0...11].i32：表示选中数据的维度。</li>
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     */
    NODE_TEXT_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_PICKER,

    /**
     * @brief 定义ARKUI_NODE_TEXT_PICKER列表组件的滚动触摸事件枚举值。
     *
     * 触发该事件的条件：滑动选择文本项停止时触发该事件。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * **{@link ArkUI_NodeComponentEvent}包含1个参数：**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0...11].i32：表示选中数据的维度。</li>
     * </ul>
     *
     * @ingroup Textpicker[滑动选择文本选择器]
     * @since 14
     */
    NODE_TEXT_PICKER_EVENT_ON_SCROLL_STOP = 15001,

    /**
     * @brief 定义NODE_CALENDAR_PICKER选中日期时触发的事件。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * **{@link ArkUI_NodeComponentEvent}包含3个参数：**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].u32：选中的年。</li>
     * <li>ArkUI_NodeComponentEvent.data[1].u32：选中的月。</li>
     * <li>ArkUI_NodeComponentEvent.data[2].u32：选中的日。</li>
     * </ul>
     *
     * @ingroup Calendarpicker[日历选择器]
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
     * @brief Defines the event triggered when the animation playback is paused.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_EVENT_ON_PAUSE = 19001,

    /**
     * @brief Defines the event triggered when the animation playback is repeated.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_EVENT_ON_REPEAT = 19002,

    /**
     * @brief Defines the event triggered when the animation playback returns to the initial state.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * {@link ArkUI_NodeComponentEvent} does not contain parameters.
     *
     * @ingroup ImageAnimator
     */
    NODE_IMAGE_ANIMATOR_EVENT_ON_CANCEL = 19003,

    /**
     * @brief Defines the event triggered when the animation playback is complete or stopped.
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
     * @brief 定义TextEditor组件中选区或光标位置发生变化时触发的事件。
     * <br>事件回调触发时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * <br>{@link ArkUI_NodeComponentEvent}包含两个参数：
     * <br><b>ArkUI_NodeComponentEvent.data[0].i32</b>：选区起始索引。
     * <br><b>ArkUI_NodeComponentEvent.data[1].i32</b>：选区结束索引。
     *
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_SELECTION_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_TEXT_EDITOR,

    /**
     * @brief 定义TextEditor组件首次初始化完成时触发的事件。
     * <br>事件回调触发时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     *
     * @ingroup Text Editor
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
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_EDITING_CHANGE,

    /**
     * @brief 定义TextEditor组件输入法的回车键被按下时触发的事件。
     * <br>事件回调触发时，{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * <br>{@link ArkUI_NodeComponentEvent}包含一个参数：
     * <br><b>ArkUI_NodeComponentEvent.data[0].i32</b>：输入法的回车键类型{@link ArkUI_EnterKeyType}。
     *
     * @ingroup Text Editor
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
     * @ingroup Text Editor
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
     * @ingroup Text Editor
     * @since 24
     */
    NODE_TEXT_EDITOR_ON_DID_CHANGE,

    /**
     * @brief 定义当前显示元素的索引时触发的事件
     * <b>ARKUI_NODE_ARC_ALPHABET_INDEXER</b>实例变更。
     *
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合类型为
     * {@链接ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}包含一个参数：\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：当前显示元素的索引。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
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
     * @brief Defines the event triggered when the switching animation of this <b>ARKUI_NODE_SWIPER</b> instance starts.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains five parameters:**
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
     * @brief Defines the event triggered when the switching animation of this <b>ARKUI_NODE_SWIPER</b> instance ends.
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
     * @since 12
     */
    NODE_SWIPER_EVENT_ON_ANIMATION_END,

    /**
     * @brief Defines the event triggered on a frame-by-frame basis when the page is turned by a swipe in this
     * <b>ARKUI_NODE_SWIPER</b> instance.
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
     * @since 12
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
     * **{@link ArkUI_NodeComponentEvent} contains four parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: indicates the index of the Swiper component,
     * which is consistent with the index change in the onChange event.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32: The index of a page in the window.</li>
     * <li>ArkUI_NodeComponentEvent.data[2].f32: The proportion of page movement relative to
     * the start position of the Swiper spindle (selectedIndex corresponds to the start position of the page).</li>
     * <li>ArkUI_NodeComponentEvent.data[3].f32: The length of the page in the axis direction.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 12
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
     * **{@link ArkUI_NodeComponentEvent} contains one parameter:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently selected element.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
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
     * **{@link ArkUI_NodeComponentEvent} contains one parameter:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: the index of the element becomes unselected.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 18
     */
    NODE_SWIPER_EVENT_ON_UNSELECTED = 1001006,

    /**
     * @brief Defines the event triggered when content in the swiper component will scroll.
     * Instructions: Before page scrolling, the </b>ContentWillScrollCallback</b> callback is invoked. \n \n
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains three parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: the index value of the current child page.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32: the index value of the child page that will display.</li>
     * <li>ArkUI_NodeComponentEvent.data[2].f32: the sliding offset of each frame.
     * Positive numbers indicating slide backward(e.g. from index=1 to index=0), negative numbers indicating
     * slide forward(e.g. from index=0 to index=1).</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 15
     */
    NODE_SWIPER_EVENT_ON_CONTENT_WILL_SCROLL = 1001007,

    /**
     * @brief Defines the <b>ARKUI_NODE_SWIPER</b> scroll state change event.
     * This event is triggered when the scroll state of the <b>Swiper</b> component changes during user dragging,
     * during the animation phase after the user lifts their finger, or upon stopping of scrolling.
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains one parameter:**
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
     * @brief      */
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
     * @brief 定义ListItem组件选中状态变化事件枚举值。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含1个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：选中状态。0：未选中。1：已选中。
     *
     * @since 26.0.0
     */
    NODE_LIST_ITEM_ON_SELECT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_LIST_ITEM,

    /**
     * @brief 定义ArcList组件有子组件划入或划出显示区域时触发事件枚举值。
     *
     * 触发该事件的条件 ：
     * 列表初始化时会触发一次，ArcList显示区域内第一个子组件的索引值或最后一个子组件的索引值有变化时会触发。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含3个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：ArcList显示区域内第一个子组件的索引值。
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>：ArcList显示区域内最后一个子组件的索引值。
     * <b>ArkUI_NodeComponentEvent.data[2].i32</b>：ArcList显示区域内中间位置子组件的索引值。
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_SCROLL_INDEX = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_LIST,

    /**
     * @brief 定义ArcList组件到达起始位置时触发回调。
     *
     * 触发该事件的条件：
     * 1. 组件到达起始位置时触发。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中不包含参数。
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_REACH_START = 1019001,

    /**
     * @brief 定义ArcList组件到达终止位置时触发回调。
     *
     * 触发该事件的条件：
     * 1. 组件到达终止位置时触发。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中不包含参数。
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_REACH_END = 1019002,

    /**
     * @brief 定义ArcList组件开始滚动时触发回调。
     *
     * 触发该事件的条件：
     * 1. 滚动组件开始滚动时触发。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中不包含参数。
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_SCROLL_START = 1019003,

    /**
     * @brief 定义ArcList组件停止滚动时触发回调。
     *
     * 触发该事件的条件：
     * 1. 滚动组件触发滚动后停止时触发。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中不包含参数。
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_SCROLL_STOP = 1019004,

    /**
     * @brief 定义ArcList组件滑动前触发事件枚举值。
     *
     * 触发该事件的条件：
     * 1. 滚动组件触发滚动时触发。
     * 2. 调用滚动控制器API接口。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含3个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>：本次滚动距离，内容向上滚动时偏移量为正，向下滚动时偏移量为负。单位：vp。
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>：当前滚动状态。参数类型为{@link ArkUI_ScrollState}。
     * <b>ArkUI_NodeComponentEvent.data[2].i32</b>：当前滚动的来源。参数类型为{@link ArkUI_ScrollSource}。
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_WILL_SCROLL = 1019005,

    /**
     * @brief 定义ArcList组件滑动时触发事件枚举值。
     *
     * 触发该事件的条件：
     * 1. 滚动组件触发滚动时触发。
     * 2. 调用滚动控制器API接口。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含2个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>：每帧滚动的距离，内容向上滚动时偏移量为正，向下滚动时偏移量为负。单位：vp。
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>：当前滚动状态。参数类型为{@link ArkUI_ScrollState}。
     *
     * @since 26.0.0
     */
    NODE_ARC_LIST_ON_DID_SCROLL = 1019006,

    /**
     * @brief 定义ARKUI_NODE_REFRESH刷新状态变更触发该事件。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含1个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：刷新状态。
     * 0：Inactive，默认未下拉状态。
     * 1：Drag，下拉中，下拉距离小于刷新距离。若此时松手，组件进入Inactive状态；若此时继续下拉使下拉距离超过刷新距离，组件进入OverDrag状态。
     * 2：OverDrag，下拉中，下拉距离超过刷新距离。若此时松手，组件进入Refresh状态；若此时上滑使下拉距离小于刷新距离，组件进入Drag状态。
     * 3：Refresh，下拉结束，回弹至刷新距离，进入刷新中状态。
     * 4：Done，刷新结束，返回初始状态（顶部）。
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
     * @brief 定义ARKUI_NODE_WATER_FLOW组件的滑动前触发事件枚举值。
     *
     * 触发该事件的条件 ：
     * 1. 滚动组件触发滚动时触发，支持键鼠操作等其他触发滚动的输入设置。
     * 2. 通过滚动控制器API接口调用。
     * 3. 越界回弹。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含3个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].f32</b>：每帧滚动的偏移量，内容向上滚动时偏移量为正，向下滚动时偏移量为负。
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>：当前滑动状态，参数类型{@link ArkUI_ScrollState}。
     * <b>ArkUI_NodeComponentEvent.data[2].i32</b>：当前滚动的来源，参数类型{@link ArkUI_ScrollSource}。
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
     * @brief 定义ARKUI_NODE_WATER_FLOW当前瀑布流显示的起始位置/终止位置的子组件发生变化时触发事件枚举值。
     *
     * 触发该事件的条件 ：
     * 瀑布流显示区域上第一个子组件/最后一个组件的索引值有变化就会触发。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含2个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：当前显示的WaterFlow起始位置的索引值。
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>：当前显示的瀑布流终止位置的索引值。
     */
    NODE_WATER_FLOW_ON_SCROLL_INDEX,

    /**
     * @brief 定义ARKUI_NODE_GRID有子组件滑入或滑出Grid显示区域时触发事件枚举值。
     *
     * 触发该事件的条件 ：
     * Grid初始化时会触发一次，Grid显示区域内第一个子组件的索引值或最后一个子组件的索引值有变化时会触发。
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含2个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：Grid显示区域内第一个子组件的索引值。
     * <b>ArkUI_NodeComponentEvent.data[1].i32</b>：Grid显示区域内最后一个子组件的索引值。
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
     * @brief 定义ARKUI_NODE_GRID_ITEM组件选中状态变化事件枚举值。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * {@link ArkUI_NodeComponentEvent}中包含1个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：0：未选中，1：已选中。
     *
     * @since 23
     */
    NODE_GRID_ITEM_ON_SELECT = MAX_NODE_SCOPE_NUM * ARKUI_NODE_GRID_ITEM,

    /**
     * @brief 定义Picker容器组件中选择某项时触发的事件。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * **{@link ArkUI_NodeComponentEvent}包含1个参数：**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32：选中项的值。</li>
     * </ul>
     *
     * @since 23
     */
    NODE_PICKER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_PICKER,

    /**
     * @brief 定义Picker容器组件中选择某项且滚动停止时触发的事件。
     *
     * 事件回调发生时，事件参数{@link ArkUI_NodeEvent}对象中的联合体类型为{@link ArkUI_NodeComponentEvent}。
     * **{@link ArkUI_NodeComponentEvent}包含1个参数：**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32：选中项的值。</li>
     * </ul>
     *
     * @since 23
     */
    NODE_PICKER_EVENT_ON_SCROLL_STOP = 1018001,

    /**
     * @brief 定义当前显示元素的索引时触发的事件
     * <b>ARKUI_NODE_ARC_SWIPER</b>实例变更。
     *
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合类型为
     * {@链接ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}包含一个参数：\n
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：当前显示元素的索引。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_SWIPER_EVENT_ON_CHANGE = MAX_NODE_SCOPE_NUM * ARKUI_NODE_ARC_SWIPER,

    /**
     * @brief Defines the event triggered when the switching animation of this <b>ARKUI_NODE_ARC_SWIPER</b> instance starts.
     *
     * When the event callback occurs, the union type in the {@link ArkUI_NodeEvent} object is
     * {@link ArkUI_NodeComponentEvent}. \n
     * **{@link ArkUI_NodeComponentEvent} contains five parameters:**
     * <ul>
     * <li>ArkUI_NodeComponentEvent.data[0].i32: index of the currently displayed element.</li>
     * <li>ArkUI_NodeComponentEvent.data[1].i32: index of the target element to switch to.</li>
     * <li>ArkUI_NodeComponentEvent.data[2].f32: offset of the currently displayed element relative to the
     * start position of the swiper along the main axis.</li>
     * <li>ArkUI_NodeComponentEvent.data[3].f32: offset of the target element relative to the start position
     * of the swiper along the main axis.</li>
     * <li>ArkUI_NodeComponentEvent.data[4].f32: hand-off velocity.</li>
     * </ul>
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_SWIPER_EVENT_ON_ANIMATION_START,

    /**
     * @brief 定义该<b>ARKUI_NODE_ARC_SWIPER</b>实例切换动画结束时触发的事件。
     *
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合类型为
     * {@链接ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}包含两个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：当前显示元素的索引。\n
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>：当前显示元素相对于元素的偏移量
     * 滑动器沿着主轴的起始位置。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_SWIPER_EVENT_ON_ANIMATION_END,

    /**
     * @brief 定义当页面被滑动翻页时，逐帧触发的事件
     * <b>ARKUI_NODE_ARC_SWIPER</b>实例。
     *
     * 当事件回调发生时，{@link ArkUI_NodeEvent}对象中的联合类型为
     * {@链接ArkUI_NodeComponentEvent}。\n
     * {@link ArkUI_NodeComponentEvent}包含两个参数：
     * <b>ArkUI_NodeComponentEvent.data[0].i32</b>：当前显示元素的索引。\n
     * <b>ArkUI_NodeComponentEvent.data[1].f32</b>：当前显示的元素相对于元素的偏移量
     * 滑动器沿着主轴的起始位置。\n
     *
     * @ingroup Navigation Related Components
     * @since 26.1.0
     */
    NODE_ARC_SWIPER_EVENT_ON_GESTURE_SWIPE
} ArkUI_NodeEventType;

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
 * @brief Obtains the numeric-type parameter of a component event.
 *
 * @param event Indicates the pointer to the component event.
 * @param index Indicates the index of the return value.
 * @param value Indicates the return value.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE} if the parameter length exceeds
 *         the limit.
 *         Returns {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID} if the data does not exist in the component event.
 * @since 12
 */
int32_t OH_ArkUI_NodeEvent_GetNumberValue(ArkUI_NodeEvent* event, int32_t index, ArkUI_NumberValue* value);

/**
 * @brief Obtains the string-type parameter of a component event. The string data is valid only during an event
 * callback. To use it outside an event callback, you are advised to copy the string data.
 *
 * @param event Indicates the pointer to the component event.
 * @param index Indicates the index of the return value.
 * @param string Indicates the pointer to the string array.
 * @param stringSize Indicates the length of the string array.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE} if the parameter length exceeds
 *         the limit.
 *         Returns {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID} if the data does not exist in the component event.
 * @since 12
 */
int32_t OH_ArkUI_NodeEvent_GetStringValue(ArkUI_NodeEvent* event, int32_t index, char** string, int32_t* stringSize);

/**
 * @brief Sets the return value for a component event.
 *
 * @param event Indicates the pointer to the component event.
 * @param value Indicates the numeric-type array.
 * @param size Indicates the array length.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_NODE_EVENT_NO_RETURN} if the component event does not support return values.
 *         Returns {@link ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID} if data does not exist in the component event.
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
 *         若传入的参数无效或并非TextEditor组件文本内容变化事件信息，则返回<b>null</b>。
 * @since 24
 */
OH_ArkUI_TextEditorChangeEvent* OH_ArkUI_NodeEvent_GetTextEditorOnWillChangeEvent(ArkUI_NodeEvent* event);

/**
 * @brief 从指定的<b>ArkUI_NodeEvent</b>对象中获取<b>ArkUI_GestureCollectInterceptInfo</b>对象。
 *
 * @param nodeEvent Pointer to the <b>ArkUI_NodeEvent</b> object.
 * @return 返回指向<b>ArkUI_GestureCollectInterceptInfo</b>对象的指针。
 * 如果传入的参数无效或不是手势收集拦截信息，则返回<b>null</b>。
 * @since 26.0.0
 */
ArkUI_GestureCollectInterceptInfo* OH_ArkUI_NodeEvent_GetGestureCollectInterceptInfo(ArkUI_NodeEvent* nodeEvent);

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
    NODE_NEED_RENDER
} ArkUI_NodeDirtyFlag;

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
    NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER = 5
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
 * @brief Sets the total number of elements in the specified adapter.
 *
 * @param handle Indicates the target component adapter.
 * @param size Indicates the number of elements.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
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
 * @brief Registers an event callback for the adapter.
 *
 * @param handle Indicates the target component adapter.
 * @param userData Indicates custom data.
 * @param receiver Indicates the event receiver callback.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
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
 * @brief Instructs the specified adapter to reload all elements.
 *
 * @param handle Indicates the target component adapter.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_ReloadAllItems(ArkUI_NodeAdapterHandle handle);

/**
 * @brief Instructs the specified adapter to reload certain elements.
 *
 * @param handle Indicates the target component adapter.
 * @param startPosition Indicates the start position of the elements to reload.
 * @param itemCount Indicates the number of the elements to reload.
 *  @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_ReloadItem(
ArkUI_NodeAdapterHandle handle, uint32_t startPosition, uint32_t itemCount);

/**
 * @brief Instructs the specified adapter to remove certain elements.
 *
 * @param handle Indicates the target component adapter.
 * @param startPosition Indicates the start position of the elements to remove.
 * @param itemCount Indicates the number of the elements to remove.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_RemoveItem(
ArkUI_NodeAdapterHandle handle, uint32_t startPosition, uint32_t itemCount);

/**
 * @brief Instructs the specified adapter to insert certain elements.
 *
 * @param handle Indicates the target component adapter.
 * @param startPosition Indicates the start position of the elements to insert.
 * @param itemCount Indicates the number of the elements to insert.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_InsertItem(
ArkUI_NodeAdapterHandle handle, uint32_t startPosition, uint32_t itemCount);

/**
 * @brief Instructs the specified adapter to move certain elements.
 *
 * @param handle Indicates the target component adapter.
 * @param from Indicates the start position of the elements to move.
 * @param to  Indicates the end position of the elements to move.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapter_MoveItem(ArkUI_NodeAdapterHandle handle, uint32_t from, uint32_t to);

/**
 * @brief Obtains all elements stored in the specified adapter.
 *
 * This API returns the pointer to the array of the elements. You need to manually release the memory data
 * to which the pointer points.
 *
 * @param handle Indicates the target component adapter.
 * @param items Indicates the pointer to the array of the elements in the adapter.
 * @param size Indicates the number of elements.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
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
 * @brief Sets the component to be added to the specified adapter.
 *
 * @param event Indicates the target adapter event.
 * @param node Indicates the component to be added.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapterEvent_SetItem(ArkUI_NodeAdapterEvent* event, ArkUI_NodeHandle node);

/**
 * @brief Sets the component ID to be generated.
 *
 * @param event Indicates the target adapter event.
 * @param id Indicates the component ID to set.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeAdapterEvent_SetNodeId(ArkUI_NodeAdapterEvent* event, int32_t id);

/**
 * @brief Provides a collection of native-side Node type APIs provided by ArkUI. APIs related to the Node module must
 * be called on the main thread.
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
     * @return Pointer to the created component. If the component fails to be created, **NULL** is returned. You need
     *     to manage the lifecycle of the returned component object pointer. Otherwise, issues such as Use After Free
     *     may cause process crashes or memory leaks.
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
     * @param position Inserting position. The value range is [-2147483648, 2147483647]. If the value is a negative
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
     * attributes set for a component contain the heap memory you apply for, ensure that the component is no longer used
     * before calling the corresponding release API. For example, **NODE_TEXT_CONTENT_WITH_STYLED_STRING** in
     * {@link ArkUI_NodeAttributeType}.
     *
     * @param node Node whose attribute needs to be set.
     * @param attribute Type of attribute to set.
     * @param value Indicates the attribute value.
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
     * @brief Registers an event for the specified node.
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
    int32_t (*registerNodeEvent)(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType, int32_t targetId, void* userData);

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
     * @brief Registers a unified entry point for event callbacks. The ArkUI framework collects component events
     * generated during processing and returns them through the registered **eventReceiver** API.
     * <br>Repeated calls will override the previously registered API. Do not directly save the pointer to the
     * {@link ArkUI_NodeEvent} object. The data will be destroyed after the callback is complete.
     * <br>To bind with a component instance, you can use the {@link addNodeEventReceiver} API.
     *
     * @param eventReceiver Indicates the event receiver to register.
     * @since 12
     */
    void (*registerNodeEventReceiver)(void (*eventReceiver)(ArkUI_NodeEvent* event));

    /**
     * @brief Unregisters the unified entry point for event callbacks.
     *
     * @since 12
     */
    void (*unregisterNodeEventReceiver)();

    /**
     * @brief Forcibly marks the current node for re-measurement, re-layout, or re-drawing. Regarding updates to system
     * attributes, the ArkUI framework automatically marks nodes and re-executes measurement, layout, or drawing; you
     * do not need to call this API actively.
     *
     * @param node Node object that needs to be marked for re-measurement, re-layout, or re-drawing.
     * @param dirtyFlag Type for re-measurement, re-layout, or re-drawing.
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
     * @brief Obtains a child node.
     *
     * @param node Target node.
     * @param position Position of the child node.
     * @return Pointer to the node, or **NULL** if the node is not found.
     * @since 12
     */
    ArkUI_NodeHandle (*getChildAt)(ArkUI_NodeHandle node, int32_t position);

    /**
     * @brief Obtains the first child node.
     *
     * @param node Target node.
     * @return Pointer to the node, or **NULL** if the node is not found.
     * @since 12
     */
    ArkUI_NodeHandle (*getFirstChild)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains the last child node.
     *
     * @param node Target node.
     * @return Pointer to the node, or **NULL** if the node is not found.
     * @since 12
     */
    ArkUI_NodeHandle (*getLastChild)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains the previous sibling node.
     *
     * @param node Target node.
     * @return Pointer to the node, or **NULL** if the node is not found.
     * @since 12
     */
    ArkUI_NodeHandle (*getPreviousSibling)(ArkUI_NodeHandle node);

    /**
     * @brief Obtains the next sibling node.
     *
     * @param node Target node.
     * @return Pointer to the node, or **NULL** if the node is not found.
     * @since 12
     */
    ArkUI_NodeHandle (*getNextSibling)(ArkUI_NodeHandle node);

    /**
     * @brief Registers a custom event for a node. Triggered events are returned through the custom event entry point
     * function registered using **registerNodeCustomEventReceiver**.
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
    int32_t (*registerNodeCustomEvent)( ArkUI_NodeHandle node, ArkUI_NodeCustomEventType eventType, int32_t targetId, void* userData);

    /**
     * @brief Unregisters a custom event for a node.
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
     * <br>Do not directly save the pointer to the {@link ArkUI_NodeCustomEvent} object. The data will be destroyed
     * after the callback is complete.
     * <br>To bind with a component instance, you can use the **addNodeCustomEventReceiver** function.
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
     * @brief Sets the width and height for a component after the measurement in the measurement callback function.
     *
     * @param node Target node.
     * @param width Width to set.
     * @param height Height to set.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*setMeasuredSize)(ArkUI_NodeHandle node, int32_t width, int32_t height);

    /**
     * @brief Sets the position of a component in the layout callback function. This API has a lower priority than
     * {@link NODE_POSITION} in **ArkUI_NodeAttributeType**.
     *
     * @param node Target node.
     * @param positionX X-coordinate.
     * @param positionY Y-coordinate.
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
     * @return Width and height of the component, wrapped in an **ArkUI_IntSize** structure.
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
     * @return Position of the component, wrapped in an **ArkUI_IntOffset** structure.
     * @since 12
     */
    ArkUI_IntOffset (*getLayoutPosition)(ArkUI_NodeHandle node);

    /**
     * @brief Measures a node. You can use the **getMeasuredSize** API to obtain the size after the measurement.
     *
     * @param node Target node.
     * @param Constraint Size constraint.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*measureNode)(ArkUI_NodeHandle node, ArkUI_LayoutConstraint* Constraint);

    /**
     * @brief Lays outs a node and specifies the expected position of the node relative to its parent node.
     *
     * @param node Target node.
     * @param positionX X-coordinate.
     * @param positionY Y-coordinate.
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
     * <br>The callback added by this function is triggered before the global callback registered by **
     * registerNodeEventReceiver**.
     * <br>Do not directly save the pointer to the {@link ArkUI_NodeEvent} object. The data will be destroyed after the
     * callback is complete.
     *
     * @param node Component for which you want to add the event callback function.
     * @param eventReceiver Indicates the component event callback function to add.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*addNodeEventReceiver)(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeEvent* event));

    /**
     * @brief Removes a registered component event callback function from a component.
     *
     * @param node Component for which you want to remove the event callback function.
     * @param eventReceiver Indicates the component event callback function to remove.
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
     * <br>The callback added by this function is triggered before the global callback registered by **
     * registerNodeCustomEventReceiver**.
     * <br>Do not directly save the pointer to the {@link ArkUI_NodeCustomEvent} object. The data will be destroyed
     * after the callback is complete.
     *
     * @param node Component for which you want to add the custom event callback function.
     * @param eventReceiver Indicates the custom event callback function to add.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*addNodeCustomEventReceiver)(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeCustomEvent* event));

    /**
     * @brief Removes a registered custom event callback function from a component.
     *
     * @param node Component for which you want to remove the custom event callback function.
     * @param eventReceiver Indicates the custom event callback function to remove.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 12
     */
    int32_t (*removeNodeCustomEventReceiver)(ArkUI_NodeHandle node, void (*eventReceiver)(ArkUI_NodeCustomEvent* event));

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
     * @return Custom data.
     * @since 12
     */
    void* (*getUserData)(ArkUI_NodeHandle node);

    /**
     * @brief Sets the unit of measurement for a component.
     *
     * @param node Component for which you want to set the unit.
     * @param unit Unit type {@link ArkUI_LengthMetricUnit}. The default value is **ARKUI_LENGTH_METRIC_UNIT_DEFAULT**.
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
     * @return Pointer to the node, or **NULL** if the node is not found.
     * @since 12
     */
    ArkUI_NodeHandle (*getParent)(ArkUI_NodeHandle node);

    /**
     * @brief Removes all child nodes from the parent component.
     *
     * @param parent Target node.
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
 * @brief 通过自定义组件事件获取自定义段落组件的测量信息。
 *
 * @param event 自定义组件事件。
 * @param info 需要获取的测量信息。
 * @return 错误码。 
 *         {@link ARKUI_ERROR_CODE_NO_ERROR}表示成功。
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID}表示函数参数异常。
 *         异常原因：传入参数验证失败，参数不能为空。
 * @since 12
 */
int32_t OH_ArkUI_NodeCustomEvent_GetCustomSpanMeasureInfo(
    ArkUI_NodeCustomEvent* event, ArkUI_CustomSpanMeasureInfo* info);

/**
 * @brief 通过自定义组件事件设置自定义段落的度量指标。
 *
 * @param event 自定义组件事件。
 * @param metrics 需要设置的度量指标信息。
 * @return 错误码。 
 *         {@link ARKUI_ERROR_CODE_NO_ERROR}表示成功。
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID}表示函数参数异常。
 *         异常原因：传入参数验证失败，参数不能为空。
 * @since 12
 */
int32_t OH_ArkUI_NodeCustomEvent_SetCustomSpanMetrics(
    ArkUI_NodeCustomEvent* event, ArkUI_CustomSpanMetrics* metrics);

/**
 * @brief 通过自定义组件事件获取自定义段落组件的绘制信息。
 *
 * @param event 自定义组件事件。
 * @param info 需要获取的绘制信息。
 * @return 错误码。 
 *         {@link ARKUI_ERROR_CODE_NO_ERROR}表示成功。
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID}表示函数参数异常。
 *         异常原因：传入参数验证失败，参数不能为空。
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
    NODE_CONTENT_EVENT_ON_DETACH_FROM_WINDOW = 1
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
    ARKUI_INSPECTOR_NATIVE_RESULT_BAD_PARAMETER = -1
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
 * @brief register a callback function to a node content.
 *
 * @param content Indicates the pointer to the node content instance.
 * @param callback Indicates the callback function.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
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
 * @brief 向节点内容中添加一个节点。
 *
 * @param content 指向节点内容实例的指针。
 * @param node 指向待添加节点的指针。
 * @return 返回错误码。
 *     操作成功时返回 {@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     参数错误时返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     节点已被收养时返回 {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED}。在API 23添加。
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
 * @brief 在节点内容的指定位置插入一个节点。
 *
 * @param content 指向节点内容实例的指针。
 * @param node 指向待插入节点的指针。
 * @param position 节点插入的位置下标。
 * @return 返回错误码。
 *     操作成功时返回 {@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     参数错误时返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     节点已被收养时返回 {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED}。在API 23添加。
 * @since 12
 */
int32_t OH_ArkUI_NodeContent_InsertNode(ArkUI_NodeContentHandle content, ArkUI_NodeHandle node, int32_t position);

/**
 * @brief Get the size of the component layout area.
 * The layout area size does not include graphic variation attributes such as scaling.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param size The drawing area size of the component handle, in px.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutSize(ArkUI_NodeHandle node, ArkUI_IntSize* size);

/**
 * @brief Obtain the position of the component layout area relative to the parent component.
 * The relative position of the layout area does not include graphic variation attributes, such as translation.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param localOffset The offset value of the component handle relative to the parent component, in px.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutPosition(ArkUI_NodeHandle node, ArkUI_IntOffset* localOffset);

/**
 * @brief Obtain the position of the component layout area relative to the window.
 * The relative position of the layout area does not include graphic variation attributes, such as translation.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param globalOffset The offset value of the component handle relative to the window, in px.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInWindow(ArkUI_NodeHandle node, ArkUI_IntOffset* globalOffset);

/**
 * @brief Obtain the position of the component layout area relative to the screen.
 * The relative position of the layout area does not include graphic variation attributes, such as translation.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @param screenOffset The offset value of the component handle relative to the screen, in px.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInScreen(ArkUI_NodeHandle node, ArkUI_IntOffset* screenOffset);

/**
 * @brief 获取组件相对于全局屏幕的偏移。
 *
 * @param node ArkUI_NodeHandle指针。
 * @param offset 组件handle相对屏幕的偏移值，单位：px。
 * @return 错误码。
 *          {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *          {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
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
 * @brief 设置组件的自定义属性。该接口仅在主线程生效。
 *
 * @param node ArkUI_NodeHandle指针。
 * @param name 自定义属性的名称。不允许传入空指针。
 * @param value 对应key参数名称的自定义属性的值。不允许传入空指针。
 * @since 13
 */
void OH_ArkUI_NodeUtils_AddCustomProperty(ArkUI_NodeHandle node, const char* name, const char* value);

/**
 * @brief 移除组件已设置的自定义属性。
 *
 * @param node ArkUI_NodeHandle指针。
 * @param name 自定义属性的名称。
 * @since 13
 */
void OH_ArkUI_NodeUtils_RemoveCustomProperty(ArkUI_NodeHandle node, const char* name);

/**
 * @brief 获取组件的自定义属性，并通过handle返回ArkUI_CustomProperty实例。
 *
 * @param node ArkUI_NodeHandle指针。
 * @param name 自定义属性的名称。
 * @param handle 获取的对应key参数名称的自定义属性的结构体。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 14
 */
int32_t OH_ArkUI_NodeUtils_GetCustomProperty(ArkUI_NodeHandle node, const char* name, ArkUI_CustomProperty** handle);

/**
 * @brief 获取父节点，可获取由ArkTs创建的组件节点。
 *
 * @param node 目标节点对象。
 * @return 组件的指针，如果没有返回NULL。
 * @since 14
 */
ArkUI_NodeHandle OH_ArkUI_NodeUtils_GetParentInPageTree(ArkUI_NodeHandle node);

/**
 * @brief 获取内部活跃状态为true的FrameNode子节点，并生成ArkUI_ActiveChildrenInfo实例。Span不会被计入子节点统计。获取成功后，可查询子节点数量并按下标读取子节点；实例使用完毕后必须调用OH_ArkUI_ActiveChildrenInfo_Destroy销毁。
 *
 * @param head 传入需要获取的节点。
 * @param handle 对应head节点子节点信息的结构体。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 14
 */
int32_t OH_ArkUI_NodeUtils_GetActiveChildrenInfo(ArkUI_NodeHandle head, ArkUI_ActiveChildrenInfo** handle);

/**
 * @brief 获取当前页面的根节点。
 *
 * @param node 目标节点对象。
 * @return 根节点的指针，如果没有返回NULL。
 * @since 14
 */
ArkUI_NodeHandle OH_ArkUI_NodeUtils_GetCurrentPageRootNode(ArkUI_NodeHandle node);

/**
 * @brief 获取组件是否由C-API创建的标签。
 *
 * @param node 目标节点对象。
 * @return 节点是否由C-API创建的Tag，true代表由C-API创建，false代表非C-API创建。
 * @since 14
 */
bool OH_ArkUI_NodeUtils_IsCreatedByNDK(ArkUI_NodeHandle node);

/**
 * @brief 获取节点的类型。
 *
 * @param node 目标节点对象。
 * @return 节点的类型，具体已开放类型参考{@link ArkUI_NodeType}，未开放结点返回-1。
 * @since 14
 */
int32_t OH_ArkUI_NodeUtils_GetNodeType(ArkUI_NodeHandle node);

/**
 * @brief 获取节点所属的窗口信息。
 *
 * @param node 目标节点对象。
 * @param info 窗口信息。使用{@link OH_ArkUI_HostWindowInfo_Destroy}释放内存。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} 节点未挂载到节点树上。
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetWindowInfo(ArkUI_NodeHandle node, ArkUI_HostWindowInfo** info);

/**
 * @brief 获取目标节点在树上的第一个子节点的下标。
 *
 * @param node 目标节点的指针。
 * @param index 子节点的下标值。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetFirstChildIndexWithoutExpand(ArkUI_NodeHandle node, uint32_t* index);

/**
 * @brief 获取目标节点在树上的最后一个子节点的下标。
 *
 * @param node 目标节点的指针。
 * @param index 子节点的下标值。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
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
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetChildWithExpandMode(ArkUI_NodeHandle node, int32_t position,
    ArkUI_NodeHandle* subnode, uint32_t expandMode);

/**
 * @brief Collapse the ListItem in its expanded state.
 *
 * @param node Node objects that need to be registered for events.
 * @param userData Custom event parameters are carried back in the callback parameter when the event is triggered.
 * @param onFinish The callback triggered after the completion of the folding animation.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 *         {@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} The component does not support this event.
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
 * @brief 将节点作为子节点移动到目标父节点下。
 *
 * @param node 待移动节点的指针
 * @param target_parent 目标父节点的指针
 * @param index 节点移动后所在位置的下标。若该值为负数或无效值，则节点将被移动到目标父节点的末尾。
 * @return 错误码。
 *     {@link ARKUI_ERROR_CODE_NO_ERROR} 表示操作成功。
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} 表示函数参数异常。
 *     {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} 表示CAPI初始化失败。
 *     {@link ARKUI_ERROR_CODE_NODE_IS_ADOPTED} 表示该节点已被收养。在API 23添加。
 * @since 18
 */
int32_t OH_ArkUI_NodeUtils_MoveTo(ArkUI_NodeHandle node, ArkUI_NodeHandle target_parent, int32_t index);

/**
 * @brief 设置目标节点的跨语言配置项。
 *
 * @param node  * @param option
 * @param option Pointer to the cross-language configuration option ({@link ArkUI_CrossLanguageOption}).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_SetCrossLanguageOption(ArkUI_NodeHandle node, ArkUI_CrossLanguageOption* option);

/**
 * @brief 获取目标节点的跨语言选项。
 *
 * @param node  * @param option
 * @param option Pointer to the cross-language configuration option ({@link ArkUI_CrossLanguageOption}).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
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
 * @brief 同步获取给定节点的快照像素图。如果该节点不在树中或者尚未渲染，则会返回错误。
 * 注意：当不再使用该像素图时，应通过 OH_PixelmapNative_Release 释放它。
 *
 * @param node 待截图的目标节点
 * @param snapshotOptions 用于截图的给定配置，可以为空以使用默认值。
 * @param pixelmap 截图结果位图
 * @return 返回结果码。
 * 如果操作成功，返回 {@link ARKUI_ERROR_CODE_NO_ERROR}。
 * 如果发生参数错误，返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * 如果截图失败，返回空像素图，返回结果码为 {@link ARKUI_ERROR_CODE_INTERNAL_ERROR}。
 * 如果截图超时，返回结果码为 {@link ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT}。
 * 如果截图选项中的色彩空间或动态范围模式不被支持，返回结果码为 {@link ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_MODE_NOT_SUPPORTED}。
 * 如果设置了 isAuto(true) 但不被支持，返回结果码为 {@link ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_AUTO_NOT_SUPPORTED}。
 * @since 15
 */
int32_t OH_ArkUI_GetNodeSnapshot(ArkUI_NodeHandle node, ArkUI_SnapshotOptions* snapshotOptions,
    OH_PixelmapNative** pixelmap);

/**
 * @brief 查询组件截图大小限制。
 *
 * @param maxWidth 组件截图的最大宽度限制，单位为PX。
 * @param maxHeight 组件截图最大高度限制，单位为PX。
 * @return 错误码。
 * 如果操作成功，则返回{@link RKUI_ERROR_CODE_NO_ERROR}。
 * {@link ARKUI_ERROR_CODE_PARAM_INVALID}参数错误。
 * @since 26.0.0
 */
int32_t OH_ArkUI_GetNodeSnapshotSizeLimitation(int32_t* maxWidth, int32_t* maxHeight);

/**
 * @brief 获取目标节点相对于父节点的偏移值，单位：px。
 *
 * @param node 目标节点。
 * @param globalOffset 目标节点相对父节点的偏移值，单位：px。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_NodeUtils_GetPositionToParent(ArkUI_NodeHandle node, ArkUI_IntOffset* globalOffset);

/**
 * @brief 在目标UI上下文中执行传入的自定义回调函数。示例请参考：{@link 在NDK中保证多实例场景功能正常}。
 *
 * @param uiContext 表示目标UI上下文的指针。
 * @param userData 开发者自定义数据指针，以便在回调函数中处理自定义数据，开发者需自行保证自定义函数被执行时的数据有效性。
 * @param callback 开发者自定义回调函数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。
 *     <br>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} UIContext对象无效。
 *     <br>{@link ARKUI_ERROR_CODE_CALLBACK_INVALID} 回调函数无效。
 * @since 20
 */
int32_t OH_ArkUI_RunTaskInScope(ArkUI_ContextHandle uiContext, void* userData, void(*callback)(void* userData));

/**
 * @brief 获取目标节点的uniqueId。
 *
 * @param node ArkUI节点指针。
 * @param uniqueId 目标节点的uniqueId。组件标识ID只读，且进程内唯一，若该节点存在，返回该节点的uniqueId值；否则返回-1。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 方法参数错误。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。
 * @since 20
 */
int32_t OH_ArkUI_NodeUtils_GetNodeUniqueId(ArkUI_NodeHandle node, int32_t* uniqueId);

/**
 * @brief 获取节点是否处于渲染状态，如果一个节点的对应{@link RenderNode}在渲染树上，则处于渲染状态。
 *
 * @param node ArkUI节点指针。
 * @param isInRenderState 节点是否处于渲染状态。true：处于渲染状态；false：不处于渲染状态。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 方法参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_IsInRenderState(ArkUI_NodeHandle node, bool* isInRenderState);

/**
 * @brief 当前节点接纳目标节点为附属节点。被接纳的节点不能已有父节点。调用该接口实际上不会将其添加为子节点，而是仅允许其接收对应子节点的生命周期回调。
 *
 * @param node ArkUI_NodeHandle指针，指定待接纳节点的父节点。
 * @param child ArkUI_NodeHandle指针，指定待被接纳的子节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。
 *     <br>{@link ARKUI_ERROR_CODE_NODE_HAS_PARENT} 被接纳的节点已有父节点。
 *     <br>{@link ARKUI_ERROR_CODE_NODE_CAN_NOT_BE_ADOPTED} 节点无法被接纳为附属节点。
 *     <br>{@link ARKUI_ERROR_CODE_NODE_CAN_NOT_ADOPT_TO} 节点无法接纳其它附属节点。
 * @since 22
 */
int32_t OH_ArkUI_NativeModule_AdoptChild(ArkUI_NodeHandle node, ArkUI_NodeHandle child);

/**
 * @brief 移除被接纳的目标附属节点。
 *
 * @param node ArkUI_NodeHandle指针，父节点。
 * @param child ArkUI_NodeHandle指针，将要被移除的子节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。
 *     <br>{@link ARKUI_ERROR_CODE_NODE_IS_NOT_IN_ADOPTED_CHILDREN} 节点不是被目标节点接纳的附属节点。
 * @since 22
 */
int32_t OH_ArkUI_NativeModule_RemoveAdoptedChild(ArkUI_NodeHandle node, ArkUI_NodeHandle child);

/**
 * @brief 获取指定实例的页面的根节点。
 *
 * @param context UI实例对象指针。
 * @param rootNode 目标根节点的句柄。如果上下文对应的页面没有根节点，则所指向的值将被设置为null。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。
 *     <br>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} 实例异常。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 24
 */
int32_t OH_ArkUI_NativeModule_GetPageRootNodeHandleByContext(ArkUI_ContextHandle context, ArkUI_NodeHandle* rootNode);

/**
 * @brief 将点的坐标从指定节点的坐标系转换至当前窗口的坐标系。节点的坐标系考虑节点本身的变换，例如，节点A的变换效果为向左平移100，会使得其坐标系中的点的坐标也向左平移100。
 *
 * [](docroot://reference/apis-arkui/figures/ConvertToWindow.png)
 *
 * 如上图所示，将指定节点坐标系中的坐标(x0, y0)转换成窗口坐标系的坐标，结果为(x1, y1)。
 *
 * @param currentNode 指定节点。
 * @param localPosition 点在指定节点坐标系中的坐标，单位：px。
 * @param windowPosition 指向接收转换后坐标（位于当前窗口坐标系中，单位：px）的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} 节点未挂载到节点树上。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_ConvertPositionToWindow(ArkUI_NodeHandle currentNode, ArkUI_IntOffset localPosition, ArkUI_IntOffset* windowPosition);

/**
 * @brief 将点的坐标从当前窗口的坐标系转换至目标节点的坐标系。节点的坐标系考虑节点本身的变换，例如，节点A的变换效果为向左平移100，会使得其坐标系中的点的坐标也向左平移100。
 *
 * [](docroot://reference/apis-arkui/figures/ConvertFromWindow.png)
 *
 * 如上图所示，将窗口坐标系中的坐标(x1, y1)转换成目标节点坐标系的坐标，结果为(x0, y0)。
 *
 * @param targetNode 目标节点。
 * @param windowPosition 点在当前窗口坐标系中的坐标，单位：px。
 * @param localPosition 指向接收转换后坐标（位于目标节点坐标系中，单位：px）的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} 节点未挂载到节点树上。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_ConvertPositionFromWindow(ArkUI_NodeHandle targetNode, ArkUI_IntOffset windowPosition, ArkUI_IntOffset* localPosition);

/**
 * @brief 通过uniqueId获取节点。
 *
 * @param uniqueId 目标节点的uniqueId。
 * @param node 目标节点的指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 方法参数错误。
 *     <br>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} CAPI初始化错误。
 * @since 20
 */
int32_t OH_ArkUI_NodeUtils_GetNodeHandleByUniqueId(const uint32_t uniqueId, ArkUI_NodeHandle* node);

/**
 * @brief Sets the inverse color algorithm for components and instances.
 *
 * @param uiContext Indicates the context in which the inverse color feature should take effect.
 *     If the value is null, the feature applies to the entire application process.
 * @param forceDark Indicates whether the inverse color feature is enabled.
 * @param nodeType Indicates the component type for which to enable the inverse color feature.
 *     If the value is ARKUI_NODE_UNDEFINED, enabling the feature for all components.
 * @param colorInvertFunc Indicates the user-defined inverse color algorithm.
 * @return Returns the error code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if CAPI init error.
 *         Returns {@link ARKUI_ERROR_CODE_FORCE_DARK_CONFIG_INVALID} if force dark config is invalid.
 * @since 20
 */
int32_t OH_ArkUI_SetForceDarkConfig(ArkUI_ContextHandle uiContext, bool forceDark, ArkUI_NodeType nodeType,
    uint32_t (*colorInvertFunc)(uint32_t color));

/**
 * @brief 设置组件支持的{@link 多态样式}状态。为了更高效地处理，需传入所关注的状态值及对应的状态处理函数，当关注的状态发生时，处理函数会被执行。可在回调中根据当前状态调整UI样式。当在同一个节点上多次调用该方法时，
 * 将以最后一次传入的状态及处理函数为准。有些类型的组件节点，系统内部已有对某些状态的默认处理。例如，Button组件默认具备对PRESSED状态的样式变化，当在此类组件上使用此方法自定义状态处理时，会先应用系统默认样式变化，
 * 再执行自定义的样式处理，最终效果为两者叠加。可以通过指定excludeInner为true来禁用系统内部的默认样式效果，但这通常取决于系统内部实现规范是否允许。当调用该函数时，
 * 传入的statesChangeHandler函数会立即执行一次，且无需特意注册对NORMAL状态的监听，只要注册了非NORMAL状态，当状态从任意状态变化回NORMAL时，系统都会进行回调，以便应用进行样式复原。
 *
 * @param node 目标节点。
 * @param uiStates 目标节点需要处理的目标UI状态。所有目标UI状态的组合结果可以通过“\|”操作来计算。例如：targetUIStates = ArkUI_UIState::PRESSED \|
 *     ArkUI_UIState::FOCUSED。
 * @param statesChangeHandler Handler for UI state changes.
 *     It rturns the current UI status. The value is the result of combining all current state enum values using the
 *     <b>|</b> operator. You can determine the state using the <b>&</b> operator.
 *     Example: <b>if (currentStates & ArkUI_UIState::PRESSED == ArkUI_UIState::PRESSED)</b>.
 *     However, for checking the normal state, use the equality operator directly.
 *     Example: <b>if (currentStates == ArkUI_UIState::NORMAL)</b>.
 * @param excludeInner 禁止内部默认状态样式的标志。​​true​​表示禁用系统内部的默认样式，false表示不禁用。
 * @param userData onDrawCompleted回调函数中使用的自定义数据。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_AddSupportedUIStates(ArkUI_NodeHandle node, int32_t uiStates,
    void (statesChangeHandler)(int32_t currentStates, void* userData), bool excludeInner, void* userData);

/**
 * @brief 删除注册的状态处理。当通过OH_ArkUI_AddSupportedUIStates注册的状态都被删除时，所注册的stateChangeHandler也不会再被执行。
 *
 * @param node 目标节点。
 * @param uiStates 节点需要删除的目标UI状态。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_RemoveSupportedUIStates(ArkUI_NodeHandle node, int32_t uiStates);

/**
 * @brief 将asyncUITask函数提交至ArkUI框架提供的非UI线程中执行，asyncUITask函数执行完毕后，在UI线程调用onFinish函数。
 * 适用于多线程创建UI组件的场景，开发者可使用此接口在非UI线程创建UI组件，随后在UI线程将创建完成的组件挂载至主树上。
 *
 * @param context UI实例对象指针。
 * @param asyncUITaskData 开发者自定义数据指针，作为asyncUITask和onFinish的入参。可以传入空指针。
 * @param asyncUITask 在非UI线程执行的函数。
 * @param onFinish asyncUITask执行完成后，在UI线程执行的函数。可以传入空指针。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} context对象无效或asyncUITask为空指针。
 * @since 22
 */
int32_t OH_ArkUI_PostAsyncUITask(ArkUI_ContextHandle context, void* asyncUITaskData,
    void (*asyncUITask)(void* asyncUITaskData), void (*onFinish)(void* asyncUITaskData));

/**
 * @brief 将task函数提交至UI线程中执行。
 *
 * @param context UI实例对象指针。
 * @param taskData 开发者自定义数据指针，作为task的入参。可以传入空指针。
 * @param task 在UI线程执行的函数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} context对象无效或task为空指针。
 * @since 22
 */
int32_t OH_ArkUI_PostUITask(ArkUI_ContextHandle context, void* taskData, void (*task)(void* taskData));
int32_t OH_ArkUI_PostUITaskAndWait(ArkUI_ContextHandle context, void* taskData, void (*task)(void* taskData));

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
 *
 * 当前支持的事件类型请参考{@link OH_ArkUI_NativeModule_RegisterCommonEvent}。
 *
 * @param node 目标节点。
 * @param eventType 事件类型。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 *     <br>{@link ARKUI_ERROR_CODE_NODE_UNSUPPORTED_EVENT_TYPE} 暂不支持该事件类型。
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_UnregisterCommonEvent(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType);

/**
 * @brief 在当前帧触发节点属性更新。当前节点的属性在构建阶段之后被修改，这些改动不会立即生效，而是会延迟到下一帧统一处理。此功能会强制当前帧内的即时节点更新，确保同步应用渲染效果。
 *
 * @param node 待更新的节点对象。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_InvalidateAttributes(ArkUI_NodeHandle node);

/**
 * @brief Stop the animation being executed by the Swiper node.
 *
 * @param node ArkUI_NodeHandle pointer.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 22
 */
int32_t OH_ArkUI_Swiper_FinishAnimation(ArkUI_NodeHandle node);

/**
 * @brief 设置menubar的可见性.
 *
 * @param uiContext ArkUI_ContextHandle. - 指定ArkUI实例的上下文。
 * @param visible 可见性。true表示可见，false表示不可见。
 * @return 返回状态码。
 *           Returns {@link ARKUI_ERROR_CODE_NO_ERROR} 参数设置成功。
 *  *         Returns {@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} UIContext对象无效。
 *                   比如1.uiContext为空指针。2.在当前UIContext无法关联ArkUI实例。
 *                   3.当前UIContext不属于元服务。
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_AtomicServiceMenuBarSetVisible(ArkUI_ContextHandle uiContext, bool visible);

/**
 * @brief 启动 Swiper 节点的模拟拖动操作。
 * 调用 OH_ArkUI_Swiper_FakeDragBy 来模拟拖动动作。调用 OH_ArkUI_Swiper_StopFakeDrag 来结束模拟拖动。模拟拖动操作可以被真实拖动操作打断。如果需要在模拟拖动期间忽略触摸事件和其他用户输入，请使用 NODE_SWIPER_DISABLE_SWIPE。
 *
 * @param node ArkUI_NodeHandle 指针。
 * @param isSuccessful 如果模拟拖拽操作成功启动，则返回 true。
 * 如果 Swiper 尚未准备好启动模拟拖拽操作，或者真实拖拽或模拟拖拽操作已在进行中，则返回 false。
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_StartFakeDrag(ArkUI_NodeHandle node, bool* isSuccessful);

/**
 * @brief 通过 Swiper 节点的偏移量来模拟拖动效果。
 * 必须先调用 OH_ArkUI_Swiper_StartFakeDrag 函数
 *
 * @param node ArkUI_NodeHandle 指针
 * @param offset 需要滚动的偏移量。单位是 vp。
 * @param isConsumedOffset 如果未处于模拟拖拽进度，或者未消耗任何偏移量，则返回 false。
 *
 * 如果消耗了任何偏移量，则返回 true
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_FakeDragBy(ArkUI_NodeHandle node, float offset, bool* isConsumedOffset);

/**
 * @brief 停止对 Swiper 节点的模拟拖动。
 *
 * @param node ArkUI_NodeHandle 指针
 * @param isSuccessful 如果模拟拖拽成功停止，则返回 true。
 *
 * 如果 Swiper 尚未准备好停止模拟拖拽，或者没有正在进行的模拟拖拽，则返回 false。
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_StopFakeDrag(ArkUI_NodeHandle node, bool* isSuccessful);

/**
 * @brief 获取 Swiper 节点的模拟拖拽状态。
 *
 * @param node ArkUI_NodeHandle 指针
 * @param isFakeDragging 如果正在进行模拟拖拽操作，则返回 true，否则返回 false
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_IsFakeDragging(ArkUI_NodeHandle node, bool* isFakeDragging);

/**
 * @brief 显示 Swiper 节点的上一页。
 *
 * @param node ArkUI_NodeHandle 指针
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_ShowPrevious(ArkUI_NodeHandle node);

/**
 * @brief 显示 Swiper 节点的下一页。
 *
 * @param node ArkUI_NodeHandle 指针
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 23
 */
int32_t OH_ArkUI_Swiper_ShowNext(ArkUI_NodeHandle node);

/**
 * @brief 注册限制回调间隔的可见区域变化的基础事件回调。
 *
 * @param node 目标节点。
 * @param ratios 阈值数组，表示组件的可见区域。
 * @param size 阈值数组的大小。
 * @param expectedUpdateInterval 开发人员预期的计算间隔。
 * @param userData 开发者自定义的数据指针，以便在回调函数中处理自定义数据，需确保自定义函数执行时数据有效。
 * @param callback 开发者自定义的回调函数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_RegisterCommonVisibleAreaApproximateChangeEvent(ArkUI_NodeHandle node, float* ratios,
    int32_t size, float expectedUpdateInterval, void* userData, void (*callback)(ArkUI_NodeEvent* event));

/**
 * @brief 注销限制回调间隔的可见区域变化的基础事件回调。
 *
 * @param node 目标节点。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 21
 */
int32_t OH_ArkUI_NativeModule_UnregisterCommonVisibleAreaApproximateChangeEvent(ArkUI_NodeHandle node);

/**
 * @brief 注册一个监听组件维度和区域变化的回调。
 * 该函数可以在任何时候为有效的{@link ArkUI_NodeHandle}节点调用。\n
 * 新注册的回调将替换先前为此事件注册的回调，并从下一帧开始生效。\n
 * 当不再需要回调时，调用{@link OH_ArkUI_NativeModule_UnregisterCommonAreaApproximateChangeEvent}将其注销。\n
 * 否则，当节点释放时，回调将自动取消注册。
 *
 * @param node 指向{@link ArkUI_NodeHandle}的指针。
 * @param expectedUpdateInterval 期望计算的时间间隔，单位为毫秒。
 * @param userData 自定义数据指针。
 * @param callback 事件回调。
 * @return 返回码。\n
 * 如果操作成功，则返回{@link RKUI_ERROR_CODE_NO_ERROR}。\n
 * 如果参数错误，则返回{@link RKUI_ERROR_CODE_PARAM_INVALID}。\n
 * @since 26.0.0
 */
int32_t OH_ArkUI_NativeModule_RegisterCommonAreaApproximateChangeEvent(ArkUI_NodeHandle node,
    float expectedUpdateInterval, void* userData, void (*callback)(ArkUI_NodeEvent* event));

/**
 * @brief 取消注册与组件的尺寸和面积变化绑定的回调。
 *
 * @param node 指向{@link ArkUI_NodeHandle}的指针。
 * @return 返回码。\n
 * 如果操作成功，则返回{@link RKUI_ERROR_CODE_NO_ERROR}。\n
 * 如果参数错误，则返回{@link RKUI_ERROR_CODE_PARAM_INVALID}。\n
 * @since 26.0.0
 */
int32_t OH_ArkUI_NativeModule_UnregisterCommonAreaApproximateChangeEvent(ArkUI_NodeHandle node);

/**
 * @brief 显示ArcSwiper节点的上一页。
 *
 * @param node ArkUI_NodeHandle指针。
 * @return 错误码。
 * {@link RKUI_ERROR_CODE_NO_ERROR}成功。
 * {@link RKUI_ERROR_CODE_PARAM_INVALID}函数参数异常。
 * @since 26.1.0
 */
int32_t OH_ArkUI_ArcSwiper_ShowPrevious(ArkUI_NodeHandle node);

/**
 * @brief 显示ArcSwiper节点的下一页。
 *
 * @param node ArkUI_NodeHandle指针。
 * @return 错误码。
 * {@link RKUI_ERROR_CODE_NO_ERROR}成功。
 * {@link RKUI_ERROR_CODE_PARAM_INVALID}函数参数异常。
 * @since 26.1.0
 */
int32_t OH_ArkUI_ArcSwiper_ShowNext(ArkUI_NodeHandle node);

/**
 * @brief 停止ArcSwiper节点执行的动画。
 *
 * @param node ArkUI_NodeHandle指针。
 * @return 错误码。
 * {@link RKUI_ERROR_CODE_NO_ERROR}成功。
 * {@link RKUI_ERROR_CODE_PARAM_INVALID}函数参数异常。
 * @since 26.1.0
 */
int32_t OH_ArkUI_ArcSwiper_FinishAnimation(ArkUI_NodeHandle node);

/**
 * @brief 设置目标节点的子节点挂载策略。
 *
 * @param node 目标节点句柄。
 * @param policy 要设置的策略。有效值对应{@link OH_ArkUI_NodeMountPolicy}：
 * @return 错误码。
 * {@link RKUI_ERROR_CODE_NO_ERROR}成功。
 * {@link RKUI_ERROR_CODE_PARAM_INVALID}函数参数异常。
 * 如果CAPI初始化错误，则返回{@link RKUI_ERROR_CODE_CAPI_INIT_ERROR}。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_SetChildMountPolicy(ArkUI_NodeHandle node, OH_ArkUI_NodeMountPolicy policy);

/**
 * @brief 获取指定节点的子节点装载策略。
 *
 * @param node 目标节点句柄。
 * @param policy 接收目标节点的子节点挂载策略的指针。
 * @return 错误码。
 * {@link RKUI_ERROR_CODE_NO_ERROR}成功。
 * {@link RKUI_ERROR_CODE_PARAM_INVALID}函数参数异常。
 * 如果CAPI初始化错误，则返回{@link RKUI_ERROR_CODE_CAPI_INIT_ERROR}。
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_GetChildMountPolicy(ArkUI_NodeHandle node, OH_ArkUI_NodeMountPolicy* policy);

#ifdef __cplusplus
};
#endif
#endif // ARKUI_NATIVE_NODE_H

/** @} */
