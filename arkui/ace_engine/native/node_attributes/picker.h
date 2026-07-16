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
 * @brief Defines **Picker** node types for **NativeNode** APIs.
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
 * @brief Defines the option content supported by the single-column text picker, including text and image resources.
 *
 * @since 12
 */
typedef struct {
    /**
     * Pointer to the image resource.
     * @since 12
     */
    const char* icon;
    /**
     * Pointer to the text information.
     * @since 12
     */
    const char* text;
} ARKUI_TextPickerRangeContent;

/**
 * @brief Defines a multi-column cascade picker.
 *
 * @since 12
 */
typedef struct {
    /**
     * Pointer to the text information.
     * @since 12
     */
    const char* text;
    /**
     * Cascade data.
     * @since 12
     */
    const ARKUI_TextPickerRangeContent* children;
    /**
     * Size of the cascade data array.
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
 * @brief Defines the style of the selected item indicator.
 *
 * @since 23
 */
typedef struct ArkUI_PickerIndicatorStyle ArkUI_PickerIndicatorStyle;

/**
 * @brief Defines the data list for the text picker.
 *
 * @since 19
 */
typedef struct ArkUI_TextPickerRangeContentArray ArkUI_TextPickerRangeContentArray;

/**
 * @brief Defines an array of multi-column cascade pickers.
 *
 * @since 19
 */
typedef struct ArkUI_TextCascadePickerRangeContentArray ArkUI_TextCascadePickerRangeContentArray;
/**
 * @brief Creates an object of the {@link TextPickerRangeContent} array.
 *
 * @param length Length of the **TextPickerRangeContent** array.
 * @return Pointer to an empty **TextPickerRangeContent** array.
 * @since 19
 */
ArkUI_TextPickerRangeContentArray* OH_ArkUI_TextPickerRangeContentArray_Create(int32_t length);
/**
 * @brief Configures the icon data at a specified position in the **TextPickerRangeContent** array.
 *
 * @param handle Pointer to the **TextPickerRangeContent** array.
 * @param icon Pointer to the icon path.
 * @param index Array index, starting from 0.
 * @note If an icon was already set at <b>index</b>, the previous buffer is released before assigning the new value.
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(
    ArkUI_TextPickerRangeContentArray* handle, char* icon, int32_t index);
/**
 * @brief Configures the text data at a specified position in the **TextPickerRangeContent** array.
 *
 * @param handle Pointer to the **TextPickerRangeContent** array.
 * @param text Pointer to the text content.
 * @param index Position in the array, starting from 0.
 * @note If text was already set at <b>index</b>, the previous buffer is released before assigning the new value.
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(
    ArkUI_TextPickerRangeContentArray* handle, char* text, int32_t index);
/**
 * @brief Destroys a **TextPickerRangeContent** array object.
 *
 * @param handle Pointer to the **TextPickerRangeContent** array.
 * @note After this call, <b>handle</b> must not be used. Do not pass pointers that were not returned by
 *     {@link OH_ArkUI_TextPickerRangeContentArray_Create}.
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_Destroy(ArkUI_TextPickerRangeContentArray* handle);
/**
 * @brief Creates an object of the {@link TextCascadePickerRangeContent} array.
 *
 * @param length Length of the **TextPickerRangeContent** array.
 * @return Pointer to an empty **TextCascadePickerRangeContent** array.
 * @since 19
 */
ArkUI_TextCascadePickerRangeContentArray* OH_ArkUI_TextCascadePickerRangeContentArray_Create(int32_t length);
/**
 * @brief Configures the text data at a specified position in the **TextCascadePickerRangeContent** array.
 *
 * @param handle Pointer to the **TextCascadePickerRangeContentHandle** instance.
 * @param text Pointer to the text content.
 * @param index Position in the array, starting from 0.
 * @note If text was already set at <b>index</b>, the previous buffer is released before assigning the new value.
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
    ArkUI_TextCascadePickerRangeContentArray* handle, char* text, int32_t index);
/**
 * @brief Configures the child data at a specified position in the **TextCascadePickerRangeContent** array.
 *
 * @param handle Pointer to the **TextCascadePickerRangeContentHandle** instance.
 * @param child Pointer to the child node array.
 * @param index Position in the array, starting from 0.
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(
    ArkUI_TextCascadePickerRangeContentArray* handle, ArkUI_TextCascadePickerRangeContentArray* child, int32_t index);
/**
 * @brief Destroys a **TextCascadePickerRangeContent** array object.
 *
 * @param handle Pointer to the **TextCascadePickerRangeContentHandle** instance.
 * @note After this call, <b>handle</b> must not be used. Do not pass pointers that were not returned by
 *     {@link OH_ArkUI_TextCascadePickerRangeContentArray_Create}.
 * @note Do not call {@link OH_ArkUI_TextCascadePickerRangeContentArray_Destroy} on a <b>child</b> while
 *     it is still stored in a parent's {@code children}.
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(ArkUI_TextCascadePickerRangeContentArray* handle);

/**
 * @brief Creates a style instance of the selected item indicator.
 *
 * @param type Type of the selected item indicator.
 * @return Pointer to the {@link ArkUI_PickerIndicatorStyle} instance. If a null pointer is returned, the creation
 *     fails. The possible cause is that the address space is full or the type is not supported.
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