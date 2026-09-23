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
 * @brief ArkUI List related types and functions on the native side.
 *
 * @since 12
 */

/**
 * @file list.h
 *
 * @brief Defines enumerations and APIs related to **List**.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_LIST_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_LIST_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the size of the main axis of a child component of the **List** component.
 *
 * @since 12
 */
typedef struct ArkUI_ListChildrenMainSize ArkUI_ListChildrenMainSize;
/**
 * @brief Enumerates the alignment modes of items along the cross axis. The default value is **
 * ARKUI_LIST_ITEM_ALIGNMENT_START**.
 *
 * @since 12
 */
typedef enum {
    /**
     * The {@link list items} are packed toward the start edge of the **List** component along the cross axis.
     */
    ARKUI_LIST_ITEM_ALIGNMENT_START = 0,

    /**
     * The list items are centered in the **List** component along the cross axis.
     */
    ARKUI_LIST_ITEM_ALIGNMENT_CENTER,

    /**
     * The list items are packed toward the end edge of the **List** component along the cross axis.
     */
    ARKUI_LIST_ITEM_ALIGNMENT_END,
} ArkUI_ListItemAlignment;

/**
 * @brief Enumerates the modes for pinning the header to the top or the footer to the bottom.
 *
 * @since 12
 */
typedef enum {
    /**
     * {@link header} and {@link footer} of {@link ListItemGroup} are not pinned to the top and bottom, respectively.
     */
    ARKUI_STICKY_STYLE_NONE = 0,

    /**
     * {@link header} of {@link ListItemGroup} is pinned to the top, and {@link footer} is not pinned to the bottom.
     */
    ARKUI_STICKY_STYLE_HEADER = 1,

    /**
     * {@link header} of {@link ListItemGroup} is not pinned to the top, and {@link footer} is pinned to the bottom.
     */
    ARKUI_STICKY_STYLE_FOOTER = 2,

    /**
     * {@link header} of {@link ListItemGroup} is pinned to the top, and {@link footer} is pinned to the bottom.
     */
    ARKUI_STICKY_STYLE_BOTH = 3,
} ArkUI_StickyStyle;

/**
 * @brief Enumerates the areas in the {@link ListItemGroup} component. The default value is **
 * ARKUI_LIST_ITEM_GROUP_AREA_OUTSIDE**.
 *
 * @since 15
 */
typedef enum {
    /**
     * Outside the area of the **ListItemGroup** component.
     */
    ARKUI_LIST_ITEM_GROUP_AREA_OUTSIDE = 0,

    /**
     * Area without the {@link header}, {@link footer}, and {@link ListItem} in the **ListItemGroup** component.
     */
    ARKUI_LIST_ITEM_SWIPE_AREA_NONE,

    /**
     * List item area of the **ListItemGroup** component.
     */
    ARKUI_LIST_ITEM_SWIPE_AREA_ITEM,

    /**
     * Header area of the **ListItemGroup** component.
     */
    ARKUI_LIST_ITEM_SWIPE_AREA_HEADER,

    /**
     * Footer area of the **ListItemGroup** component.
     */
    ARKUI_LIST_ITEM_SWIPE_AREA_FOOTER,
} ArkUI_ListItemGroupArea;

/**
 * @brief Creates a **ListChildrenMainSize** instance. After use, call
 * {@link OH_ArkUI_ListChildrenMainSizeOption_Dispose} to release resources.
 *
 * @return Pointer to the **ListChildrenMainSize** instance.
 * @since 12
 */
ArkUI_ListChildrenMainSize* OH_ArkUI_ListChildrenMainSizeOption_Create();

/**
 * @brief Disposes of a **ListChildrenMainSize** instance created by {@link OH_ArkUI_ListChildrenMainSizeOption_Create}.
 * The instance cannot be accessed after disposal.
 *
 * @param option Pointer to the **ListChildrenMainSize** instance to dispose of.
 * @since 12
 */
void OH_ArkUI_ListChildrenMainSizeOption_Dispose(ArkUI_ListChildrenMainSize* option);

/**
 * @brief Sets the default size of the list item in the {@link List} component along the main axis. The vertical
 * direction indicates the height, and the horizontal direction indicates the width.
 *
 * @param option Pointer to the **ListChildrenMainSize** instance. **ARKUI_ERROR_CODE_PARAM_INVALID** is returned when
 *     the parameter is a null pointer.
 * @param defaultMainSize Default size of the list item along the main axis, in vp. The value must be greater than or
 *     equal to 0.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_ListChildrenMainSizeOption_SetDefaultMainSize(
    ArkUI_ListChildrenMainSize* option, float defaultMainSize);
/**
 * @brief Obtains the default size of the list item in the {@link List} component along the main axis. The vertical
 * direction indicates the height, and the horizontal direction indicates the width.
 *
 * @param option Pointer to the **ListChildrenMainSize** instance.
 * @return Default size of the list item along the main axis. The default value is **0**. The unit is {@link vp}. If **
 *     option** is a null pointer, **-1** is returned.
 * @since 12
 */
float OH_ArkUI_ListChildrenMainSizeOption_GetDefaultMainSize(ArkUI_ListChildrenMainSize* option);

/**
 * @brief Adjusts the length of the main axis size array of child items in the {@link List} component. When the array
 * is expanded, the initial value of new elements is **-1**.
 *
 * @param option Pointer to the **ListChildrenMainSize** instance. No operation is performed when the parameter is a
 *     null pointer.
 * @param totalSize Target array length. The value range is greater than 0. No operation is performed when a value less
 *     than or equal to 0 is passed in.
 * @since 12
 */
void OH_ArkUI_ListChildrenMainSizeOption_Resize(ArkUI_ListChildrenMainSize* option, int32_t totalSize);

/**
 * @brief Deletes **deleteCount** elements from the main axis size array of child items in the {@link List} component
 * starting from the specified index position, and inserts **addCount** elements with an initial value of **-1** at
 * that position. If the value of **deleteCount** exceeds the number of remaining elements, deletion proceeds to the
 * end of the array.
 *
 * @param option Pointer to the **ListChildrenMainSize** instance. **ARKUI_ERROR_CODE_PARAM_INVALID** is returned when
 *     the parameter is a null pointer.
 * @param index Start index of the operation. The value ranges from 0 to the current array length minus 1.
 * @param deleteCount Number of elements to delete starting from the start position. The value is greater than or equal
 *     to 0. If the number exceeds the remaining elements, deletion proceeds to the end of the array.
 * @param addCount Number of elements to add starting from the start position. The value is greater than or equal to 0.
 *     The initial value of new elements is **-1**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_ListChildrenMainSizeOption_Splice(
    ArkUI_ListChildrenMainSize* option, int32_t index, int32_t deleteCount, int32_t addCount);

/**
 * @brief Updates the size at the specified index in the child item size array of the {@link List} component along the
 * main axis. The vertical direction indicates the height, and the horizontal direction indicates the width.
 *
 * @param option Pointer to the **ListChildrenMainSize** instance. **ARKUI_ERROR_CODE_PARAM_INVALID** is returned when
 *     the parameter is a null pointer.
 * @param index Array index of the target element. The value ranges from 0 to the current array length minus 1.
 * @param mainSize Main axis size value to set, in vp. The value must be greater than or equal to 0.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_ListChildrenMainSizeOption_UpdateSize(
    ArkUI_ListChildrenMainSize* option, int32_t index, float mainSize);
/**
 * @brief Obtains the size at the specified index in the child item size array of the {@link List} component along the
 * main axis. The vertical direction indicates the height, and the horizontal direction indicates the width.
 *
 * @param option Pointer to the **ListChildrenMainSize** instance.
 * @param index Array index of the target element. The value ranges from 0 to the current array length minus 1.
 * @return Main axis size value at the specified index in the array, in vp. **-1** is returned if **option** is a null
 *     pointer or **index** is out of the array range.
 * @since 12
 */
float OH_ArkUI_ListChildrenMainSizeOption_GetMainSize(ArkUI_ListChildrenMainSize* option, int32_t index);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_LIST_H
/** @} */
