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
 * @brief Provides picker type definitions of ArkUI on the native side.
 *
 * @since 12
 */

/**
 * @file picker.h
 *
 * @brief 为NativeNode API提供Picker节点类型定义。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
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
    /**
     * 默认值。日期列显示年、月、日三列。
     * @since 18
     */
    ARKUI_DATEPICKER_MODE_DATE = 0,
    /**
     * 日期列显示年、月二列。
     * @since 18
     */
    ARKUI_DATEPICKER_YEAR_AND_MONTH = 1,
    /**
     * 日期列显示月、日二列。
     * @since 18
     */
    ARKUI_DATEPICKER_MONTH_AND_DAY = 2
} ArkUI_DatePickerMode;

/**
 * @brief 定义滑动选择文本选择器输入类型。
 *
 * @since 12
 */
typedef enum {
    /**
     * 单列数据选择器。
     * @since 12
     */
    ARKUI_TEXTPICKER_RANGETYPE_SINGLE = 0,
    /**
     * 多列数据选择器。
     * @since 12
     */
    ARKUI_TEXTPICKER_RANGETYPE_MULTI = 1,
    /**
     * 支持图片资源的单列数据选择器。
     * @since 12
     */
    ARKUI_TEXTPICKER_RANGETYPE_RANGE_CONTENT = 2,
    /**
     * 支持联动的多列数据选择器。
     * @since 12
     */
    ARKUI_TEXTPICKER_RANGETYPE_CASCADE_RANGE_CONTENT = 3
} ArkUI_TextPickerRangeType;
/**
 * @brief 定义单列滑动数据选择器支持的选项内容结构体，包含文本和图片资源。
 *
 * @since 12
 */
typedef struct {
    /**
     * 图片资源。
     * @since 12
     */
    const char* icon;
    /**
     * 文本信息。
     * @since 12
     */
    const char* text;
} ARKUI_TextPickerRangeContent;

/**
 * @brief 定义多列联动滑动数据选择器的结构体。
 *
 * @since 12
 */
typedef struct {
    /**
     * 文本信息。
     * @since 12
     */
    const char* text;
    /**
     * 联动数据。
     * @since 12
     */
    const ARKUI_TextPickerRangeContent* children;
    /**
     * 联动数据数组大小。
     * @since 12
     */
    int32_t size;
} ARKUI_TextPickerCascadeRangeContent;

/**
 * @brief 日历选择器与入口组件之间的对齐模式类型。
 *
 * @since 12
 */
typedef enum {
    /**
     * 选择器和入口组件左对齐方式。
     * @since 12
     */
    ARKUI_CALENDAR_ALIGNMENT_START = 0,
    /**
     * 选择器和入口组件居中对齐方式。
     * @since 12
     */
    ARKUI_CALENDAR_ALIGNMENT_CENTER = 1,
    /**
     * 选择器和入口组件右对齐方式。
     * @since 12
     */
    ARKUI_CALENDAR_ALIGNMENT_END = 2
} ArkUI_CalendarAlignment;

/**
 * @brief 选择器的选中指示器类型。
 *
 * @since 23
 */
typedef enum {
    /**
     * 背景样式。
     *
     * @since 23
     */
    ARKUI_PICKER_INDICATOR_BACKGROUND = 0,
    /**
     * 分割线样式。
     *
     * @since 23
     */
    ARKUI_PICKER_INDICATOR_DIVIDER = 1
} ArkUI_PickerIndicatorType;
/**
 * @brief Defines the style parameter of the background-style indicator of the selected item.
 *
 * @since 23
 */
typedef struct {
    /**
     * Background color of the selected item.<br>Default value: **0**<br>Value range: 0xARGB format, for example, <b>
     * 0xFF1122FF</b>.
     * @since 23
     */
    uint32_t backgroundColor;
    /**
     * Radius of the upper left corner.<br>Default value: **0**<br>Unit: vp<br>Value range: no more than half of the
     * smaller value between the width and height of the selected item. If the value is less than 0, the style
     * parameter of the background-style indicator of the selected item fails to be set. If the value is greater than
     * the maximum value, the maximum value is used.
     * @since 23
     */
    float topLeftRadius;
    /**
     * Radius of the upper right corner.<br>Default value: **0**<br>Unit: vp<br>Value range: no more than half of the
     * smaller value between the width and height of the selected item. If the value is less than 0, the style
     * parameter of the background-style indicator of the selected item fails to be set. If the value is greater than
     * the maximum value, the maximum value is used.
     * @since 23
     */
    float topRightRadius;
    /**
     * Radius of the lower left corner.<br>Default value: **0**<br>Unit: vp<br>Value range: no more than half of the
     * smaller value between the width and height of the selected item. If the value is less than 0, the style
     * parameter of the background-style indicator of the selected item fails to be set. If the value is greater than
     * the maximum value, the maximum value is used.
     * @since 23
     */
    float bottomLeftRadius;
    /**
     * Radius of the lower right corner.<br>Default value: **0**<br>Unit: vp<br>Value range: no more than half of the
     * smaller value between the width and height of the selected item. If the value is less than 0, the style
     * parameter of the background-style indicator of the selected item fails to be set. If the value is greater than
     * the maximum value, the maximum value is used.
     * @since 23
     */
    float bottomRightRadius;
} ArkUI_PickerIndicatorBackground;
/**
 * @brief Defines the style parameter of the divider-style indicator.
 *
 * @since 23
 */
typedef struct {
    /**
     * Stroke width of the divider.<br>Default value: **0**<br>Unit: vp<br>Value range: [0, half the height of the
     * selected item (that is, 20 vp)]. Setting the style parameter for the divider-style indicator fails when **
     * strokeWidth** is less than **0**. If **strokeWidth** exceeds half the height of the selected item, 2.0 vp is
     * used. Percentages are not supported.
     * @since 23
     */
    float strokeWidth;
    /**
     * Color of the divider.<br>Default value: **0**<br>Value range: 0xARGB format, for example, <b>0xFF1122FF</b>.
     * @since 23
     */
    uint32_t dividerColor;
    /**
     * Distance between the divider and the start edge of the **Picker** container.<br>Default value: **0**<br>Unit: vp<
     * br>Value range: The sum of **startMargin** and **endMargin** must not exceed the width of the **Picker**
     * container. Setting the style parameter for the divider-style indicator fails when the value less than **0** is
     * set. If the sum of **startMargin** and **endMargin** exceeds the width of the **Picker** container, the default
     * value is used. Percentages are not supported.
     * @since 23
     */
    float startMargin;
    /**
     * Distance between the divider and the end edge of the **Picker** container.<br>Default value: **0**<br>Unit: vp<
     * br>Value range: The sum of **startMargin** and **endMargin** must not exceed the width of the **Picker**
     * container. Setting the style parameter for the divider-style indicator fails when the value less than **0** is
     * set. If the sum of **startMargin** and **endMargin** exceeds the width of the **Picker** container, the default
     * value is used. Percentages are not supported.
     * @since 23
     */
    float endMargin;
} ArkUI_PickerIndicatorDivider;

/**
 * @brief 选中项指示器的样式。
 *
 * @since 23
 */
typedef struct ArkUI_PickerIndicatorStyle ArkUI_PickerIndicatorStyle;

/**
 * @brief 定义文本选择器的数据选择列表。
 *
 * @since 19
 */
typedef struct ArkUI_TextPickerRangeContentArray ArkUI_TextPickerRangeContentArray;

/**
 * @brief 定义多列联动数据选择器的数组。
 *
 * @since 19
 */
typedef struct ArkUI_TextCascadePickerRangeContentArray ArkUI_TextCascadePickerRangeContentArray;
/**
 * @brief 创建{@link TextPickerRangeContent}数组的对象。
 *
 * @param length 指定TextPickerRangeContent数组的长度。
 * @return 返回指向TextPickerRangeContent空数组的指针。
 * @since 19
 */
ArkUI_TextPickerRangeContentArray* OH_ArkUI_TextPickerRangeContentArray_Create(int32_t length);
/**
 * @brief 设置TextPickerRangeContent数组指定位置的icon数据。
 *
 * @param handle 指向TextPickerRangeContent数组的指针。
 * @param icon 图标路径。
 * @param index 数组索引，从0开始。
 * @note If an icon was already set at <b>index</b>, the previous buffer is released before assigning the new value.
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(
    ArkUI_TextPickerRangeContentArray* handle, char* icon, int32_t index);
/**
 * @brief 设置TextPickerRangeContent数组指定位置的text数据。
 *
 * @param handle 指向TextPickerRangeContent数组的指针。
 * @param text 文本内容。
 * @param index 数组位置，从0开始。
 * @note If text was already set at <b>index</b>, the previous buffer is released before assigning the new value.
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(
    ArkUI_TextPickerRangeContentArray* handle, char* text, int32_t index);
/**
 * @brief 删除TextPickerRangeContent数组对象。
 *
 * @param handle 指向TextPickerRangeContent数组的指针。
 * @note After this call, <b>handle</b> must not be used. Do not pass pointers that were not returned by
 *     {@link OH_ArkUI_TextPickerRangeContentArray_Create}.
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_Destroy(ArkUI_TextPickerRangeContentArray* handle);
/**
 * @brief 创建{@link TextCascadePickerRangeContent}数组对象。
 *
 * @param length 指向TextPickerRangeContent数组的长度。
 * @return 返回指向TextCascadePickerRangeContent空数组的指针。
 * @since 19
 */
ArkUI_TextCascadePickerRangeContentArray* OH_ArkUI_TextCascadePickerRangeContentArray_Create(int32_t length);
/**
 * @brief 设置TextCascadePickerRangeContent数组指定位置的text数据。
 *
 * @param handle 指向TextCascadePickerRangeContentHandle的指针。
 * @param text 文本内容。
 * @param index 数组位置，从0开始。
 * @note If text was already set at <b>index</b>, the previous buffer is released before assigning the new value.
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
    ArkUI_TextCascadePickerRangeContentArray* handle, char* text, int32_t index);
/**
 * @brief 设置TextCascadePickerRangeContent数组指定位置的child数据。
 *
 * @param handle 指向TextCascadePickerRangeContentHandle的指针。
 * @param child 子节点数组指针。
 * @param index 数组位置，从0开始。
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(
    ArkUI_TextCascadePickerRangeContentArray* handle, ArkUI_TextCascadePickerRangeContentArray* child, int32_t index);
/**
 * @brief 删除TextCascadePickerRangeContent数组对象。
 *
 * @param handle 指向TextCascadePickerRangeContentHandle的指针。
 * @note After this call, <b>handle</b> must not be used. Do not pass pointers that were not returned by
 *     {@link OH_ArkUI_TextCascadePickerRangeContentArray_Create}.
 * @note Do not call {@link OH_ArkUI_TextCascadePickerRangeContentArray_Destroy} on a <b>child</b> while
 *     it is still stored in a parent's {@code children}.
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(ArkUI_TextCascadePickerRangeContentArray* handle);

/**
 * @brief 创建选中项指示器的样式实例。
 *
 * @param type 选择器选中项样式枚举类型。
 * @return {@link ArkUI_PickerIndicatorStyle}实例。如果返回空指针，表示创建失败，失败原因可能是地址空间已满或类型不支持。
 * @since 23
 */
ArkUI_PickerIndicatorStyle* OH_ArkUI_PickerIndicatorStyle_Create(ArkUI_PickerIndicatorType type);

/**
 * @brief Disposes of the style instance of the selected item indicator.
 *
 * @param style Pointer to the {@link ArkUI_PickerIndicatorStyle} instance to be disposed of.
 * @since 23
 */
void OH_ArkUI_PickerIndicatorStyle_Dispose(ArkUI_PickerIndicatorStyle* style);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_PICKER_H
/** @} */