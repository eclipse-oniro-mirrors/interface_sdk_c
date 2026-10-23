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
 * @brief Defines **Picker** node types for **NativeNode** APIs, which support various picker components including the
 * date picker and text picker. It is applicable to scenarios requiring scroll‑selection implementation at the native
 * layer. It provides rich style configuration and data‑linkage capabilities for you to flexibly construct diverse
 * selection interactions.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @include <arkui/node_attributes/picker.h>
 * @library libace_ndk.z.so
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
 * @brief Enumerates the column display modes of the date picker.
 *
 * @since 18
 */
typedef enum {
    /**
     * A mode that displays the date in months, days of month, and years.
     *
     * @since 18
     */
    ARKUI_DATEPICKER_MODE_DATE = 0,
    /**
     * A mode that displays the date in months and years.
     *
     * @since 18
     */
    ARKUI_DATEPICKER_YEAR_AND_MONTH = 1,
    /**
     * A mode that displays the date in months and days of the month.
     *
     * @since 18
     */
    ARKUI_DATEPICKER_MONTH_AND_DAY = 2
} ArkUI_DatePickerMode;

/**
 * @brief Enumerates the types of the text picker.
 *
 * @since 12
 */
typedef enum {
    /**
     * Single-column text picker.
     *
     * @since 12
     */
    ARKUI_TEXTPICKER_RANGETYPE_SINGLE = 0,
    /**
     * Multi-column text picker.
     *
     * @since 12
     */
    ARKUI_TEXTPICKER_RANGETYPE_MULTI = 1,
    /**
     * Single-column text picker with image resources.
     *
     * @since 12
     */
    ARKUI_TEXTPICKER_RANGETYPE_RANGE_CONTENT = 2,
    /**
     * Interconnected multi-column text picker.
     *
     * @since 12
     */
    ARKUI_TEXTPICKER_RANGETYPE_CASCADE_RANGE_CONTENT = 3
} ArkUI_TextPickerRangeType;

/**
 * @brief Defines the image resource supported by a single-column text picker. This struct is used to display both
 * images and text in the **TextPicker** component, and is suitable for scenarios where icons and text combinations
 * need to be displayed in a single-column text picker. It supports custom icon paths and text content. Each item can
 * be set with an independent icon and text, or only one of them, helping you implement flexible image-text picker
 * configurations.
 *
 * @since 12
 */
typedef struct {
    /**
     * Pointer to the icon path, which is a C string ending with `\0`. The value can be **NULL**. When not set through
     * an API, the parameter remains at the default value `nullptr`; when set to `nullptr` through
     * {@link OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex}, the setting does not take effect (the API ignores
     * it). An empty string `""` is valid and indicates that no icon is displayed. A specific path is used to display a
     * custom icon (chosen when an icon hint is required), an empty string is used to explicitly display no icon (
     * chosen when only text is displayed), and **NULL** is the default value (you should set it to a specific value or
     * an empty string through the **Set** method; retaining **NULL** is not recommended). The path format is an in-
     * application resource path, for example, `"/common/hello.png"`, consistent with {@link TextPickerRangeContent} of
     * ArkTS. URIs are also supported. The image format is not specifically restricted. Images are loaded through **
     * ImageSourceInfo**, and the supported formats are consistent with those of the {@link Image} component (such as
     * PNG, JPG, and WebP). The display size is fixed at 24 vp × 24 vp and cannot be configured through this struct. No
     * upper limit on the file size is specified in the source code.
     * @since 12
     */
    const char* icon;
    /**
     * Pointer to the text content, which is a C string ending with `\0`. The value can be **NULL**, and the default
     * value is `nullptr`; when `nullptr` is passed through {@link OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex},
     *  the setting does not take effect. An empty string `""` is valid and indicates that no text is displayed.
     * Specific text content is used to display a hint (chosen when a text description is required), an empty string is
     * used to explicitly display no text (chosen when only an icon is displayed), and **NULL** is the default value (
     * you should set it to a specific value or an empty string through the **Set** method; retaining **NULL** is not
     * recommended). If the parameter is not set through the **Set** method, an empty string is displayed by default,
     * consistent with the ArkTS documentation.
     * @since 12
     */
    const char* text;
} ARKUI_TextPickerRangeContent;

/**
 * @brief Defines a multi-column text cascade picker, which describes the hierarchical data structure of the multi-
 * column text cascade picker. This struct forms a tree structure through children members to support multi-level
 * cascade selection. It is suitable for scenarios that require displaying hierarchical data such as province/city/
 * district and year/month/day, and can simplify the development of the multi-level text cascade picker.
 *
 * @since 12
 */
typedef struct {
    /**
     * Pointer to the text content, which is a C string ending with `\0`. The value can be **NULL**, and the default
     * value is `nullptr`; when `nullptr` is passed through {@link OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex},
     *  the setting does not take effect. An empty string `""` is valid and indicates that no text is displayed.
     * Specific text content is used to display a hint (chosen when a text description is required), an empty string is
     * used to explicitly display no text (chosen when only an icon is displayed), and **NULL** is the default value (
     * you should set it to a specific value or an empty string through the **Set** method; retaining **NULL** is not
     * recommended). If the parameter is not set through the **Set** method, an empty string is displayed by default,
     * consistent with the ArkTS documentation.
     * @since 12
     */
    const char* text;
    /**
     * Pointer to the child-level cascade data array, which points to the cascaded data array of the next level. When
     * this option is selected at the current level, the array content corresponding to children is displayed as the
     * options of the next level. Set it to **NULL** when there is no child-level data. The array pointer passed must
     * remain valid during the use of the picker, and the caller is responsible for managing the array memory.
     * @since 12
     */
    const ARKUI_TextPickerRangeContent* children;
    /**
     * Number of elements in the children array, that is, the number of options at the current level. The value must be
     * greater than or equal to 0 and must be consistent with the actual number of elements in the children array
     * passed. When **children** is **NULL**, set this parameter to **0**. A parameter error exception is thrown when a
     * negative number or an inconsistent value is passed in.
     * @since 12
     */
    int32_t size;
} ARKUI_TextPickerCascadeRangeContent;

/**
 * @brief Enumerates the alignment modes between the calendar picker and the entry component.
 *
 * @since 12
 */
typedef enum {
    /**
     * Left aligned.
     *
     * @since 12
     */
    ARKUI_CALENDAR_ALIGNMENT_START = 0,
    /**
     * Center aligned.
     *
     * @since 12
     */
    ARKUI_CALENDAR_ALIGNMENT_CENTER = 1,
    /**
     * Right aligned.
     *
     * @since 12
     */
    ARKUI_CALENDAR_ALIGNMENT_END = 2
} ArkUI_CalendarAlignment;

/**
 * @brief Enumerates the indicator types of the selected item.
 *
 * @since 23
 */
typedef enum {
    /**
     * background.
     *
     * @since 23
     */
    ARKUI_PICKER_INDICATOR_BACKGROUND = 0,
    /**
     * divider.
     *
     * @since 23
     */
    ARKUI_PICKER_INDICATOR_DIVIDER = 1
} ArkUI_PickerIndicatorType;

/**
 * @brief Defines the style parameter of the background-style indicator of the selected item. The background-style
 * indicator highlights the selected item with a background color and rounded corners, including the background color
 * and corner radius of the selected item.<br>Usage scenarios:
 *
 * @since 23
 */
typedef struct {
    /**
     * Background color of the selected item.<br>Default value: **0** (fully transparent, with an ARGB value of
     * 0x00000000, meaning the background is invisible).<br>Format requirement: 0xAARRGGBB format, where the first byte
     * is the alpha channel (**00** indicates fully transparent and **FF** indicates fully opaque), and the second to
     * fourth bytes are the red, green, and blue channels, respectively, for example, **0xFF1122FF**.
     * @since 23
     */
    uint32_t backgroundColor;
    /**
     * Radius of the upper left corner.<br>Default value: **0**<br>Unit: vp<br>Value range: Use the smaller of the
     * width and height of the selected item as **x**. The maximum value does not exceed half of **x**. If the value is
     * less than 0, the style parameter of the background-style indicator of the selected item fails to be set. If the
     * value is greater than the maximum value, the maximum value is used.
     * @since 23
     */
    float topLeftRadius;
    /**
     * Radius of the upper right corner.<br>Default value: **0**<br>Unit: vp<br>Value range: Use the smaller of the
     * width and height of the selected item as **x**. The maximum value does not exceed half of **x**. If the value is
     * less than 0, the style parameter of the background-style indicator of the selected item fails to be set. If the
     * value is greater than the maximum value, the maximum value is used.
     * @since 23
     */
    float topRightRadius;
    /**
     * Radius of the lower left corner.<br>Default value: **0**<br>Unit: vp<br>Value range: Use the smaller of the
     * width and height of the selected item as **x**. The maximum value does not exceed half of **x**. If the value is
     * less than 0, the style parameter of the background-style indicator of the selected item fails to be set. If the
     * value is greater than the maximum value, the maximum value is used.
     * @since 23
     */
    float bottomLeftRadius;
    /**
     * Radius of the lower right corner.<br>Default value: **0**<br>Unit: vp<br>Value range: Use the smaller of the
     * width and height of the selected item as **x**. The maximum value does not exceed half of **x**. If the value is
     * less than 0, the style parameter of the background-style indicator of the selected item fails to be set. If the
     * value is greater than the maximum value, the maximum value is used.
     * @since 23
     */
    float bottomRightRadius;
} ArkUI_PickerIndicatorBackground;

/**
 * @brief Defines the style parameter of the divider-style indicator. This struct supports customizing the stroke width
 * of the divider, color of the divider, and distance between the divider and the container edges. It applies to
 * scenarios where the appearance of the **Picker** control's divider needs to be beautified. You can configure this
 * struct to achieve personalized divider effects, improving the aesthetics of the UI and the user experience.
 *
 * @since 23
 */
typedef struct {
    /**
     * Stroke width of the divider.<br>Default value: **0**<br>Unit: vp<br>Value range: [0, Half the height of the
     * selected item (that is, 20 vp)].<br>Setting the style parameter for the divider-style indicator fails when **
     * strokeWidth** is less than 0. If **strokeWidth** exceeds half the height of the selected item, **0** is used.
     * Percentages are not supported.
     * @since 23
     */
    float strokeWidth;
    /**
     * Color of the divider.<br>Default value: **0** (indicating a fully transparent color, so the divider is invisible)
     * <br>Format requirement: 0xARGB format, for example, **0xFF1122FF**. If no color is set, the default value is
     * used.
     * @since 23
     */
    uint32_t dividerColor;
    /**
     * Distance between the divider and the start edge of the **Picker** container.<br>Default value: **0**<br>Unit: vp<
     * br>Value range: The sum of **startMargin** and **endMargin** must not exceed the width of the **Picker**
     * container.<br>Setting the style parameter for the divider-style indicator fails when the value less than 0 is
     * set. If the sum of **startMargin** and **endMargin** exceeds the container width, the default value **0** is
     * used. Percentages are not supported.
     * @since 23
     */
    float startMargin;
    /**
     * Distance between the divider and the end edge of the **Picker** container.<br>Default value: **0**<br>Unit: vp<
     * br>Value range: The sum of **startMargin** and **endMargin** must not exceed the width of the **Picker**
     * container.<br>Setting the style parameter for the divider-style indicator fails when the value less than 0 is
     * set. If the sum of **startMargin** and **endMargin** exceeds the container width, the default value **0** is
     * used. Percentages are not supported.
     * @since 23
     */
    float endMargin;
} ArkUI_PickerIndicatorDivider;

/**
 * @brief Defines the style of the selected item indicator. It contains attribute configurations such as the indicator
 * color and size, used to enhance the visual effect of the selected item in the **Picker** component and improve the
 * user interaction experience.
 *
 * @since 23
 */
typedef struct ArkUI_PickerIndicatorStyle ArkUI_PickerIndicatorStyle;

/**
 * @brief Defines the option content array of a text picker. This struct is used to configure the option list of a text
 * picker, setting the icon and text content of each option by index. It applies to scenarios such as date selection,
 * time selection, and list selection that require displaying multiple options for users to select by scrolling.
 *
 * @since 19
 */
typedef struct ArkUI_TextPickerRangeContentArray ArkUI_TextPickerRangeContentArray;

/**
 * @brief Defines an option array of a multi-column text cascade picker. This struct is used to configure the
 * hierarchical data of a multi-column text cascade picker, that is, configure the text and child-level data of each
 * column's options through indexes. It is applicable to scenarios that require multi-column data cascade, such as
 * province-city-district cascade and product category selection.
 *
 * @since 19
 */
typedef struct ArkUI_TextCascadePickerRangeContentArray ArkUI_TextCascadePickerRangeContentArray;

/**
 * @brief Creates an **ArkUI_TextPickerRangeContentArray** array object, which is used to construct the data list of
 * a single-column sliding data picker, commonly seen in scenarios such as date selection, time selection, and list
 * selection. After creation, you must call **OH_ArkUI_TextPickerRangeContentArray_Destroy** to release resources
 * after use; otherwise, a memory leak occurs.
 *
 * @param length Length of the **ArkUI_TextPickerRangeContentArray** array. The value must be greater than 0. A null
 *     pointer is returned if a non-positive integer is passed in or creation fails.
 * @return Pointer to the **ArkUI_TextPickerRangeContentArray** array object (the array length is specified by the **
 *     length** parameter). If a null pointer is returned, the creation fails.
 * @release OH_ArkUI_TextPickerRangeContentArray_Destroy {return}
 * @since 19
 */
ArkUI_TextPickerRangeContentArray* OH_ArkUI_TextPickerRangeContentArray_Create(int32_t length);

/**
 * @brief Sets the icon data at the specified position of the **ArkUI_TextPickerRangeContentArray** array, which is
 * used to set options with icons in a single-column text picker, commonly seen in scenarios such as mixed text-and-
 * image lists and option lists with icon hints.
 *
 * @param handle Pointer to the **ArkUI_TextPickerRangeContentArray** array, which must first be created through **
 *     OH_ArkUI_TextPickerRangeContentArray_Create**.
 * @param icon Pointer to the icon path, which supports a relative path or an absolute path. A relative path is
 *     relative to the application resource directory. The path must point to a valid icon resource file.
 * @param index Array index, with a value range of [0, Array length - 1], starting from 0. The value is not effective
 *     when out of range.
 *     If an icon was already set at <b>index</b>, the previous buffer is released before assigning the new value.
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(
    ArkUI_TextPickerRangeContentArray* handle, char* icon, int32_t index);

/**
 * @brief Sets the text data at the specified position of the **ArkUI_TextPickerRangeContentArray** array, which is
 * used to set the text content in a data picker. This is an essential step for constructing picker options. This API
 * is commonly used in scenarios such as setting date text in a date picker, setting city names in a city picker, and
 * setting category names in a product category picker.
 *
 * @param handle Pointer to the **ArkUI_TextPickerRangeContentArray** array, which must first be created through **
 *     OH_ArkUI_TextPickerRangeContentArray_Create**.
 * @param text Pointer to the text content.
 * @param index Array index, with a value range of [0, Array length - 1], starting from 0. The value is not effective
 *     when out of range.
 *     If text was already set at <b>index</b>, the previous buffer is released before assigning the new value.
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(
    ArkUI_TextPickerRangeContentArray* handle, char* text, int32_t index);

/**
 * @brief Destroys the **ArkUI_TextPickerRangeContentArray** array object. This API must be used in pair with **
 * OH_ArkUI_TextPickerRangeContentArray_Create** to release the created array object resources.
 *
 * @param handle Pointer to the **ArkUI_TextPickerRangeContentArray** array.
 *     After this call, <b>handle</b> must not be used. Do not pass pointers that were not returned by
 *     {@link OH_ArkUI_TextPickerRangeContentArray_Create}.
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_Destroy(ArkUI_TextPickerRangeContentArray* handle);

/**
 * @brief Creates an **ArkUI_TextCascadePickerRangeContentArray** array object, which is used to construct a
 * multi-column cascade data picker, commonly seen in scenarios such as year-month-day linkage selection and
 * province-city-district three-level linkage selection. After creation, you must call
 * **OH_ArkUI_TextCascadePickerRangeContentArray_Destroy** to release resources after use; otherwise, a memory
 * leak occurs.
 *
 * @param length Length of the **ArkUI_TextCascadePickerRangeContentArray** array. The value must be greater than 0.
 * @return Pointer to the **ArkUI_TextCascadePickerRangeContentArray** array object (the array length is specified by
 *     the **length** parameter). If a null pointer is returned, the creation fails.
 * @release OH_ArkUI_TextCascadePickerRangeContentArray_Destroy {return}
 * @since 19
 */
ArkUI_TextCascadePickerRangeContentArray* OH_ArkUI_TextCascadePickerRangeContentArray_Create(int32_t length);

/**
 * @brief Sets the text data at the specified position of the **ArkUI_TextCascadePickerRangeContentArray** array,
 * which is used to set the text content of a multi-column cascade picker. This API is commonly used in scenarios
 * such as setting province names in a province-city-district three-level cascade picker, setting years in a
 * year-month-day cascade picker, and setting brand names in a brand-vehicle model cascade picker.
 *
 * @param handle Pointer to the  **ArkUI_TextCascadePickerRangeContentArray** array, which must first be created
 *     through **OH_ArkUI_TextCascadePickerRangeContentArray_Create**.
 * @param text Pointer to the text content.
 * @param index Array index, with a value range of [0, Array length - 1], starting from 0. The value is not effective
 *     when out of range.
 *     If text was already set at <b>index</b>, the previous buffer is released before assigning the new value.
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
    ArkUI_TextCascadePickerRangeContentArray* handle, char* text, int32_t index);

/**
 * @brief Sets the child data at the specified position of the **ArkUI_TextCascadePickerRangeContentArray** array,
 * which is used to set the child-level data of a multi-column cascade picker to implement the linkage effect. This API
 * is commonly used in scenarios such as setting the city-level data corresponding to a province in a province-city-
 * district three-level cascade picker, setting the date data corresponding to a month in a year-month-day cascade
 * picker, and setting the model list corresponding to a brand in a brand-vehicle model cascade picker.
 *
 * @param handle Pointer to the  **ArkUI_TextCascadePickerRangeContentArray** array, which must first be created
 *     through **OH_ArkUI_TextCascadePickerRangeContentArray_Create**.
 * @param child Pointer to the child data list at the specified position of the cascade picker, which must first be
 *     created through **OH_ArkUI_TextCascadePickerRangeContentArray_Create**.
 * @param index Array index, with a value range of [0, Array length - 1], starting from 0. The value is not effective
 *     when out of range.
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(
    ArkUI_TextCascadePickerRangeContentArray* handle, ArkUI_TextCascadePickerRangeContentArray* child, int32_t index);

/**
 * @brief Destroys the **ArkUI_TextCascadePickerRangeContentArray** array object. This API must be used in pair with **
 * OH_ArkUI_TextCascadePickerRangeContentArray_Create** to release the created array object resources.
 *
 * @param handle Pointer to the  **ArkUI_TextCascadePickerRangeContentArray** array.
 *     After this call, <b>handle</b> must not be used. Do not pass pointers that were not returned by
 *     {@link OH_ArkUI_TextCascadePickerRangeContentArray_Create}.
 *     Do not call {@link OH_ArkUI_TextCascadePickerRangeContentArray_Destroy} on a <b>child</b> while
 *     it is still stored in a parent's {@code children}.
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(ArkUI_TextCascadePickerRangeContentArray* handle);

/**
 * @brief Creates a style instance of the selected item indicator, which is used to highlight the option currently
 * selected by the user and improve the user interaction experience. After creation, you must call **
 * OH_ArkUI_PickerIndicatorStyle_Dispose** to release resources after use; otherwise, a memory leak occurs.
 *
 * @param type Type of the selected item indicator in the picker.
 * @return Pointer to the **ArkUI_PickerIndicatorStyle** instance. If a null pointer is returned, the creation fails.
 *     The failure may be caused by a full address space or an unsupported type.
 * @since 23
 */
ArkUI_PickerIndicatorStyle* OH_ArkUI_PickerIndicatorStyle_Create(ArkUI_PickerIndicatorType type);

/**
 * @brief Disposes of the style instance of the selected item indicator. This API must be used in pair with **
 * OH_ArkUI_PickerIndicatorStyle_Create** to release the created style instance resources.
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