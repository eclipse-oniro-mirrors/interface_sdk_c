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
 * @file node_list.h
 *
 * @brief Provides shared list-related type and function definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUIKit
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_LIST_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_LIST_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Define the ChildrenMainSize class information for a List.
 *
 * @since 12
 */
typedef struct ArkUI_ListChildrenMainSize ArkUI_ListChildrenMainSize;

/**
 * @brief Enumerates the alignment modes of items along the cross axis.
 *
 * @since 12
 */
typedef enum {
    /** The list items are packed toward the start edge of the list container along the cross axis. */
    ARKUI_LIST_ITEM_ALIGNMENT_START = 0,
    /** The list items are centered in the list container along the cross axis. */
    ARKUI_LIST_ITEM_ALIGNMENT_CENTER,
    /** The list items are packed toward the end edge of the list container along the cross axis. */
    ARKUI_LIST_ITEM_ALIGNMENT_END,
} ArkUI_ListItemAlignment;

/**
 * @brief Enumerates the modes for pinning the header to the top or the footer to the bottom.
 *
 * @since 12
 */
typedef enum {
    /** In the list item group, the header is not pinned to the top, and the footer is not pinned to the bottom. */
    ARKUI_STICKY_STYLE_NONE = 0,
    /** In the list item group, the header is pinned to the top, and the footer is not pinned to the bottom. */
    ARKUI_STICKY_STYLE_HEADER = 1,
    /** In the list item group, the footer is pinned to the bottom, and the header is not pinned to the top. */
    ARKUI_STICKY_STYLE_FOOTER = 2,
    /** In the list item group, the footer is pinned to the bottom, and the header is pinned to the top. */
    ARKUI_STICKY_STYLE_BOTH = 3,
} ArkUI_StickyStyle;

/**
 * @brief Define an enum for the areas of the <b>ListItemGroup</b> component.
 *
 * @since 15
 */
typedef enum {
    /** Outside the area of the <b>ListItemGroup</b> component. */
    ARKUI_LIST_ITEM_GROUP_AREA_OUTSIDE = 0,
    /** Area when the <b>ListItemGroup</b> component does not have the header, footer, or list item. */
    ARKUI_LIST_ITEM_SWIPE_AREA_NONE,
    /** List item area of the <b>ListItemGroup</b> component. */
    ARKUI_LIST_ITEM_SWIPE_AREA_ITEM,
    /** Header area of the <b>ListItemGroup</b> component. */
    ARKUI_LIST_ITEM_SWIPE_AREA_HEADER,
    /** Footer area of the <b>ListItemGroup</b> component. */
    ARKUI_LIST_ITEM_SWIPE_AREA_FOOTER,
} ArkUI_ListItemGroupArea;

/**
 * @brief Create configuration items for the ListChildrenMainSize interface settings.
 *
 * @return ListChildrenMainSize configuration item instance.If the object returns a null pointer,
 *         it indicates a creation failure, and the reason for the failure may be that the address space is full.
 * @since 12
 */
ArkUI_ListChildrenMainSize* OH_ArkUI_ListChildrenMainSizeOption_Create();

/**
 * @brief Destroy the ListChildrenMainSize instance.
 *
 * @param option The ListChildrenMainSize instance to be destroyed.
 * @since 12
 */
void OH_ArkUI_ListChildrenMainSizeOption_Dispose(ArkUI_ListChildrenMainSize* option);

/**
 * @brief Set the default size of ChildrenMainSizeOption for the List component.
 *
 * @param option ListChildrenMainSize instance.
 * @param defaultMainSize The default size of the ListItem under the List, measured in vp.
 * @return 0 represents success. If defaultMainSize is less than 0 or option is a null pointer, return 401.
 * @since 12
 */
int32_t OH_ArkUI_ListChildrenMainSizeOption_SetDefaultMainSize(
    ArkUI_ListChildrenMainSize* option, float defaultMainSize);

/**
 * @brief Get the default size of ChildrenMainSizeOption for the List component.
 *
 * @param option ListChildrenMainSize instance.
 * @return The default size of the ListItem under the List is 0, measured in vp.
 *         When the option is a null pointer, it returns -1.
 * @since 12
 */
float OH_ArkUI_ListChildrenMainSizeOption_GetDefaultMainSize(ArkUI_ListChildrenMainSize* option);

/**
 * @brief Reset the array size of ChildrenMainSizeOption for the List component.
 *
 * @param option ListChildrenMainSize instance.
 * @param totalSize Array size.
 * @since 12
 */
void OH_ArkUI_ListChildrenMainSizeOption_Resize(ArkUI_ListChildrenMainSize* option, int32_t totalSize);

/**
 * @brief Resize the ChildrenMainSizeOption array operation on the List component.
 *
 * @param option ListChildrenMainSize instance.
 * @param index To modify the starting position of the MainSize array.
 * @param deleteCount The number of MainSize arrays to be deleted starting from index.
 * @param addCount The number of MainSize arrays to be added starting from index.
 * @return 0 represents success. If the function parameter is abnormal, return 401.
 * @since 12
 */
int32_t OH_ArkUI_ListChildrenMainSizeOption_Splice(
    ArkUI_ListChildrenMainSize* option, int32_t index, int32_t deleteCount, int32_t addCount);

/**
 * @brief Update the value of the ChildrenMainSizeOption array in the List component.
 *
 * @param option ListChildrenMainSize instance.
 * @param index To modify the starting position of the MainSize array.
 * @param mainSize The actual modified value.
 * @return 0 represents success. If the function parameter is abnormal, return 401.
 * @since 12
 */
int32_t OH_ArkUI_ListChildrenMainSizeOption_UpdateSize(
    ArkUI_ListChildrenMainSize* option, int32_t index, float mainSize);

/**
 * @brief Get the value of the ChildrenMainSizeOption array for the List component.
 *
 * @param option ListChildrenMainSize instance.
 * @param index The index position of the value to be obtained.
 * @return The value of the specific position of the array. If the function parameter is abnormal, return -1.
 * @since 12
 */
float OH_ArkUI_ListChildrenMainSizeOption_GetMainSize(ArkUI_ListChildrenMainSize* option, int32_t index);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_LIST_H
/** @} */
