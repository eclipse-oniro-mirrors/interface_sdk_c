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
 * @brief ArkUI Picker节点在Native侧的类型定义。
 *
 * @since 12
 */

/**
 * @file picker.h
 *
 * @brief 为NativeNode API提供Picker节点类型定义，支持日期选择器、文本选择器等多种类型的选择器组件，
 * 适用于需要在原生层实现滚动选择功能的场景，
 * 提供了丰富的样式配置和数据联动能力，帮助开发者灵活构建各类选择交互。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @include <arkui/picker.h>
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_PICKER_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_PICKER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义日期选择器列显示模式的枚举值。
 *
 * @since 18
 */
typedef enum {
    /** 默认值。日期列显示年、月、日三列。 */
    ARKUI_DATEPICKER_MODE_DATE = 0,
    /** 日期列显示年、月二列。 */
    ARKUI_DATEPICKER_YEAR_AND_MONTH = 1,
    /** 日期列显示月、日二列。 */
    ARKUI_DATEPICKER_MONTH_AND_DAY = 2,
} ArkUI_DatePickerMode;

/**
 * @brief 定义滑动选择文本选择器输入类型。
 *
 * @since 12
 */
typedef enum {
    /** 单列数据选择器。*/
    ARKUI_TEXTPICKER_RANGETYPE_SINGLE = 0,
    /** 多列数据选择器。*/
    ARKUI_TEXTPICKER_RANGETYPE_MULTI = 1,
    /** 支持图片资源的单列数据选择器。*/
    ARKUI_TEXTPICKER_RANGETYPE_RANGE_CONTENT = 2,
    /** 支持联动的多列数据选择器。*/
    ARKUI_TEXTPICKER_RANGETYPE_CASCADE_RANGE_CONTENT = 3,
} ArkUI_TextPickerRangeType;

/**
 * @brief 定义单列滑动数据选择器支持的图片资源结构体。该结构体用于在TextPicker组件中同时显示图片和文本内容，
 * 适用于需要在单列滑动选择器中展示图标和文本组合的场景。
 * 支持自定义图标路径和文本内容，每项可设置独立的图标和文本或仅设置其中之一，帮助开发者实现灵活的图文选择器配置。
 *
 * @note 每一项至少提供icon、text其中之一，可为仅icon、仅text或两者同时设置。\n
 * 当文本长度大于列宽时，text内容会被截断显示。\n
 * 建议使用{@link OH_ArkUI_TextPickerRangeContentArray_Create}创建数组后，通过
 * {@link OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex}和
 * {@link OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex}设置各位置数据，以确保数据结构正确性，
 * 不建议手动拼装原始结构体。如果手动拼装结构体或未使用Create方法初始化，可能导致数组对象未正确初始化、
 * 内存管理异常或类型不匹配等问题。\n
 * 在NODE_TEXT_PICKER_OPTION_RANGE中配合rangeType为ARKUI_TEXTPICKER_RANGETYPE_RANGE_CONTENT（取值为2）时使用本结构体。
 *
 * @since 12
 */
typedef struct {
    /** 图标路径。以\0结尾的C字符串。可为NULL。未通过API设置时，字段保持默认值nullptr；通过\n
        {@link OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex}设置为nullptr时不生效（API会忽略此设置）。\n
        空字符串""合法，表示不显示图标。具体路径用于显示自定义图标（当需要图标提示时选择），\n
        空字符串用于明确不显示图标（当仅显示文本时选择），NULL为默认值（应通过Set方法设置为具体值或空字符串，
        不建议保留NULL）。\n
        路径格式为应用内资源路径，例如"/common/hello.png"，与ArkTS TextPickerRangeContent一致；亦支持URI。\n
        图片格式未做专门限制，通过ImageSourceInfo加载，与Image组件支持的格式一致（如png、jpg、webp等）。\n
        显示尺寸固定为24vp × 24vp，不可通过本结构体配置。源码中未规定文件大小上限。 */
    const char* icon;
    /** 文本内容。以\0结尾的C字符串。可为NULL，默认为nullptr；通过\n
        {@link OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex}传入nullptr时不生效。\n
        空字符串""合法，表示不显示文本。具体文本内容用于显示提示信息（当需要文本说明时选择），\n
        空字符串用于明确不显示文本（当仅显示图标时选择），NULL为默认值（应通过Set方法设置为具体值或空字符串，
        不建议保留NULL）。\n
        若未通过Set方法设置，则默认显示为空字符串，与ArkTS文档一致。 */
    const char* text;
} ARKUI_TextPickerRangeContent;

/**
 * @brief 定义多列联动滑动数据选择器的结构体，用于描述多列联动选择器的层级数据结构。
 * 该结构体通过children成员形成树状结构，支持多级联动选择，适用于需要展示省市区、年月日等分级数据的场景，
 * 可简化多级联动选择器的开发。
 *
 * @since 12
 */
typedef struct {
    /** 要显示在多列联动滑动选择器中的文本内容，用于表示该选项的显示文本。默认值为NULL，可设置为空字符串表示无文本。
        取值原则请参见接口说明。\n
        说明：未设置文本时，建议将text设置为NULL。 */
    const char* text;
    /** 子级联动数据数组指针，指向下一级联动数据数组。当前级别选中该选项时，children对应数组内容会作为下一级显示的选项；
        无子级数据时设置为NULL。传入的数组指针需要在选择器使用期间保持有效，调用者负责管理数组内存。 */
    const ARKUI_TextPickerRangeContent* children;
    /** children数组的元素个数，即当前层级的选项数量。取值必须大于等于0，且需与实际传入的children数组元素个数一致；
        当children为NULL时应设置为0。传入负数或不一致时抛出参数错误异常。 */
    int32_t size;
} ARKUI_TextPickerCascadeRangeContent;

/**
 * @brief 日历选择器与入口组件对齐方式。
 *
 * @since 12
 */
typedef enum {
    /** 设置选择器与入口组件的对齐方式为左对齐。 */
    ARKUI_CALENDAR_ALIGNMENT_START = 0,
    /** 设置选择器与入口组件的对齐方式为居中对齐。 */
    ARKUI_CALENDAR_ALIGNMENT_CENTER = 1,
    /** 设置选择器与入口组件的对齐方式为右对齐。 */
    ARKUI_CALENDAR_ALIGNMENT_END = 2,
} ArkUI_CalendarAlignment;

/**
 * @brief 选择器的选中指示器类型。
 *
 * @since 23
 */
typedef enum {
    /** 背景样式。 */
    ARKUI_PICKER_INDICATOR_BACKGROUND = 0,
    /** 分割线样式。 */
    ARKUI_PICKER_INDICATOR_DIVIDER = 1,
} ArkUI_PickerIndicatorType;

/**
 * @brief 选择器指示器背景的样式参数。用于设置选择器指示器背景样式的参数结构体；
 * 指示器背景样式以背景色和圆角高亮显示选择器的选中项，包括选中项背景颜色和圆角半径。
 *
 * 使用场景：\n
 * - 在选择器（Picker）组件中为选中项设置自定义背景样式，如音乐播放器中的歌曲列表选中背景。\n
 * - 在日期选择器中突出显示当前选中的日期或时间，提升用户体验。\n
 * - 在选项列表中为选中项添加圆角背景，增强视觉层次感。
 *
 * @since 23
 */
typedef struct {
    /** 选中项背景的颜色。 \n
        默认值：0（完全透明，ARGB值为0x00000000，背景不可见）。 \n
        格式要求：0xAARRGGBB格式，第1个字节为透明度（00表示全透明，FF表示完全不透明），第2-4个字节分别为红、绿、蓝通道，
        例如0xFF1122FF。 */
    uint32_t backgroundColor;
    /** 左上角圆角半径。 \n
        默认值：0 \n
        单位：vp \n
        取值范围：取选中项的宽和高之中较小的边长为x，最大不超过x的一半。
        当取值小于0时，设置选择器指示器背景的样式参数失败；当取值大于最大值时，使用最大值。 */
    float topLeftRadius;
    /** 右上角圆角半径。 \n
        默认值：0 \n
        单位：vp \n
        取值范围：取选中项的宽和高之中较小的边长为x，最大不超过x的一半。
        当取值小于0时，设置选择器指示器背景的样式参数失败；当取值大于最大值时，使用最大值。 */
    float topRightRadius;
    /** 左下角圆角半径。 \n
        默认值：0 \n
        单位：vp \n
        取值范围：取选中项的宽和高之中较小的边长为x，最大不超过x的一半。
        当取值小于0时，设置选择器指示器背景的样式参数失败；当取值大于最大值时，使用最大值。 */
    float bottomLeftRadius;
    /** 右下角圆角半径。 \n
        默认值：0 \n
        单位：vp \n
        取值范围：取选中项的宽和高之中较小的边长为x，最大不超过x的一半。
        当取值小于0时，设置选择器指示器背景的样式参数失败；当取值大于最大值时，使用最大值。 */
    float bottomRightRadius;
} ArkUI_PickerIndicatorBackground;

/**
 * @brief 用于定义分割线样式指示器的样式参数，支持自定义分割线的线宽、颜色以及与容器侧边的距离，
 * 适用于需要美化Picker控件分割线外观的场景。开发者可通过配置该结构体实现个性化分割线效果，
 * 提升UI界面的美观度和用户体验。
 *
 * @since 23
 */
typedef struct {
    /** 分割线的线宽。 \n
        默认值：0 \n
        单位：vp \n
        取值范围：[0, 选中项高度的一半（即20vp）]。 \n
        小于0时设置失败，大于选中项高度的一半时使用默认值0。不支持百分比类型。 */
    float strokeWidth;
    /** 分割线的颜色。 \n
        默认值：0（表示全透明颜色，分割线不可见） \n
        格式要求：0xARGB格式，例如0xFF1122FF。未设置颜色时使用默认值。 */
    uint32_t dividerColor;
    /** 分割线与Picker容器侧边起始端的距离。 \n
        默认值：0 \n
        单位：vp \n
        取值范围：startMargin与endMargin之和不得超过Picker容器的宽度。 \n
        小于0时设置失败。startMargin与endMargin之和超过容器宽度时使用默认值0。不支持百分比类型。 */
    float startMargin;
    /** 分割线与Picker容器侧边结束端的距离。 \n
        默认值：0 \n
        单位：vp \n
        取值范围：startMargin与endMargin之和不得超过Picker容器的宽度。 \n
        小于0时设置失败。startMargin与endMargin之和超过容器宽度时使用默认值0。不支持百分比类型。 */
    float endMargin;
} ArkUI_PickerIndicatorDivider;

/**
 * @brief 选中项指示器的样式。包含指示器的颜色、大小等属性配置，用于增强Picker组件的选中项视觉效果，提升用户交互体验。
 *
 * @since 23
 */
typedef struct ArkUI_PickerIndicatorStyle ArkUI_PickerIndicatorStyle;

/**
 * @brief 定义文本选择器的选项内容数组。该结构体用于配置文本选择器的选项列表，通过索引设置每个选项的图标和文本内容，
 * 适用于日期选择、时间选择、列表选择等需要展示多个选项供用户滚动选择的场景。
 *
 * @since 19
 */
typedef struct ArkUI_TextPickerRangeContentArray ArkUI_TextPickerRangeContentArray;

/**
 * @brief 定义多列联动文本选择器的选项内容数组。该结构体用于配置多列联动选择器的层级数据，
 * 通过索引设置各列选项的文本及子级数据，适用于省市区联动、产品分类选择等需要多列数据联动的场景。
 *
 * @since 19
 */
typedef struct ArkUI_TextCascadePickerRangeContentArray ArkUI_TextCascadePickerRangeContentArray;

/**
 * @brief 创建{@link ArkUI_TextPickerRangeContentArray}数组的对象，用于构建单列滑动数据选择器的数据列表，
 * 常见于日期选择、时间选择、列表选择等场景。
 * 创建后必须在使用完毕后调用OH_ArkUI_TextPickerRangeContentArray_Destroy释放资源，否则会导致内存泄漏。
 *
 * @param length 指定ArkUI_TextPickerRangeContentArray数组的长度。取值必须大于0；传入非正整数或创建失败时返回空指针。
 * @return 返回指向ArkUI_TextPickerRangeContentArray数组对象的指针（数组长度由length参数指定）。如果返回空指针，
 * 表示创建失败。
 * @release OH_ArkUI_TextPickerRangeContentArray_Destroy {return}
 * @since 19
 */
ArkUI_TextPickerRangeContentArray* OH_ArkUI_TextPickerRangeContentArray_Create(int32_t length);

/**
 * @brief 设置ArkUI_TextPickerRangeContentArray数组指定位置的icon数据，用于在单列文本选择器中设置带图标的选项，
 * 常见于图文混排列表、带图标提示的选项列表等场景。
 *
 * @param handle 指向ArkUI_TextPickerRangeContentArray数组的指针，
 * 需先通过OH_ArkUI_TextPickerRangeContentArray_Create创建。
 * @param icon 图标路径，支持相对路径或绝对路径。相对路径相对于应用资源目录。路径必须指向有效的图标资源文件。
 * @param index 数组索引，取值范围为[0, 数组长度-1]，从0开始。超出范围时不生效。
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(
    ArkUI_TextPickerRangeContentArray* handle, char* icon, int32_t index);

/**
 * @brief 设置ArkUI_TextPickerRangeContentArray数组指定位置的text数据，用于在数据选择器中设置文本内容，
 * 是构建选择器选项的必备步骤。
 * 常见于日期选择器设置日期文本、城市选择器设置城市名称、产品分类选择器设置分类名称等场景。
 *
 * @param handle 指向ArkUI_TextPickerRangeContentArray数组的指针，
 * 需先通过OH_ArkUI_TextPickerRangeContentArray_Create创建。
 * @param text 文本内容。
 * @param index 数组索引，取值范围为[0, 数组长度-1]，从0开始。
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(
    ArkUI_TextPickerRangeContentArray* handle, char* text, int32_t index);

/**
 * @brief 销毁ArkUI_TextPickerRangeContentArray数组对象。
 * 此方法必须与OH_ArkUI_TextPickerRangeContentArray_Create配对使用，用于释放创建的数组对象资源。
 *
 * @param handle 指向ArkUI_TextPickerRangeContentArray数组的指针。
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_Destroy(ArkUI_TextPickerRangeContentArray* handle);

/**
 * @brief 创建{@link ArkUI_TextCascadePickerRangeContentArray}数组对象，用于构建多列联动数据选择器，
 * 常见于年月日联动选择、省市区三级联动选择等场景。
 * 创建后必须在使用完毕后调用OH_ArkUI_TextCascadePickerRangeContentArray_Destroy释放资源，否则会导致内存泄漏。
 *
 * @param length 指定ArkUI_TextCascadePickerRangeContentArray数组的长度。取值必须大于0。
 * @return 返回指向ArkUI_TextCascadePickerRangeContentArray数组对象的指针（数组长度由length参数指定）。如果返回空指针，
 * 表示创建失败。
 * @release OH_ArkUI_TextCascadePickerRangeContentArray_Destroy {return}
 * @since 19
 */
ArkUI_TextCascadePickerRangeContentArray* OH_ArkUI_TextCascadePickerRangeContentArray_Create(int32_t length);

/**
 * @brief 设置ArkUI_TextCascadePickerRangeContentArray数组指定位置的text数据，用于设置多列联动选择器的文本内容。
 * 常见于省市区三级联动选择器设置省份名称、年月日联动选择器设置年份、品牌车型联动选择器设置品牌名称等场景。
 *
 * @param handle 指向ArkUI_TextCascadePickerRangeContentArray数组的指针。
 * @param text 文本内容。
 * @param index 数组索引，取值范围为[0, 数组长度-1]，从0开始。
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
    ArkUI_TextCascadePickerRangeContentArray* handle, char* text, int32_t index);

/**
 * @brief 设置ArkUI_TextCascadePickerRangeContentArray数组指定位置的child数据，用于设置多列联动选择器的子级数据，
 * 实现联动效果。
 * 常见于省市区三级联动选择器设置省份对应的市级数据、年月日联动选择器设置月份对应的日期数据、
 * 品牌车型联动选择器设置品牌对应的车型列表等场景。
 *
 * @param handle 指向ArkUI_TextCascadePickerRangeContentArray数组的指针。
 * @param child 指向级联选择器指定位置子级数据列表的指针。
 * @param index 数组索引，取值范围为[0, 数组长度-1]，从0开始。
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(
    ArkUI_TextCascadePickerRangeContentArray* handle, ArkUI_TextCascadePickerRangeContentArray* child, int32_t index);

/**
 * @brief 销毁ArkUI_TextCascadePickerRangeContentArray数组对象。
 * 此方法必须与OH_ArkUI_TextCascadePickerRangeContentArray_Create配对使用，用于释放创建的数组对象资源。
 *
 * @param handle 指向ArkUI_TextCascadePickerRangeContentArray数组的指针。
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(ArkUI_TextCascadePickerRangeContentArray* handle);

/**
 * @brief 创建选中项指示器的样式实例，用于高亮显示用户当前选中的选项，提升用户交互体验。
 * 创建后必须在使用完毕后调用OH_ArkUI_PickerIndicatorStyle_Dispose释放资源，否则会导致内存泄漏。
 *
 * @param type 选择器选中项指示器类型。
 * @return {@link ArkUI_PickerIndicatorStyle}实例的指针。如果返回空指针，表示创建失败，
 * 失败原因可能是地址空间已满或类型不支持。
 * @since 23
 */
ArkUI_PickerIndicatorStyle* OH_ArkUI_PickerIndicatorStyle_Create(ArkUI_PickerIndicatorType type);

/**
 * @brief 销毁选中项指示器的样式实例。此方法必须与OH_ArkUI_PickerIndicatorStyle_Create配对使用，
 * 用于释放创建的样式实例资源。
 *
 * @param style 要销毁的{@link ArkUI_PickerIndicatorStyle}实例。
 * @since 23
 */
void OH_ArkUI_PickerIndicatorStyle_Dispose(ArkUI_PickerIndicatorStyle* style);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_PICKER_H
/** @} */
