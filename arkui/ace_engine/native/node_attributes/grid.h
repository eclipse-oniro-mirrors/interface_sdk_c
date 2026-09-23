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
 * @brief ArkUI Grid related types and functions on the native side.
 *
 * @since 22
 */

/**
 * @file node_grid.h
 *
 * @brief Defines enumerations and APIs related to **Grid**.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 22
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_GRID_GRID_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_GRID_GRID_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the return value for the {@link OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback}
 * callback in **Grid** layout options, which is used to specify the row span and column span for an irregular grid
 * item at the specified index.
 *
 * @since 22
 */
typedef struct {
    /**
     * Number of rows occupied by a grid item, which is used to set the span of the grid item in the row direction.
     * Value range: [1, +∞). If set to **0**, the value **1** is used. In a horizontal grid layout, if the value
     * exceeds the actual number of rows, the actual number of rows is used.
     */
    uint32_t rowSpan;

    /**
     * Number of columns occupied by a grid item, which is used to set the span of the grid item in the column
     * direction. Value range: [1, +∞). If set to **0**, the value **1** is used. In a vertical grid layout, if the
     * value exceeds the actual number of columns, the actual number of columns is used.
     */
    uint32_t columnSpan;
} ArkUI_GridItemSize;

/**
 * @brief Defines the return value for the {@link OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback} callback
 * in **Grid** layout options, which is used to specify the start row, start column, row span, and column span for the
 * grid item in **Grid** at the specified index.
 *
 * @since 22
 */
typedef struct {
    /**
     * Start row of a grid item in **Grid**, which is counted from 0.
     */
    uint32_t rowStart;

    /**
     * Start column of a grid item in **Grid**, which is counted from 0.
     */
    uint32_t columnStart;

    /**
     * Number of rows occupied by a grid item, which is used to set the span of the grid item in the row direction.
     * Value range: [1, +∞). If set to **0**, the value **1** is used. In a horizontal grid layout, if the value
     * exceeds the actual number of rows, the actual number of rows is used.
     */
    uint32_t rowSpan;

    /**
     * Number of columns occupied by a grid item, which is used to set the span of the grid item in the column
     * direction. Value range: [1, +∞). If set to **0**, the value **1** is used. In a vertical grid layout, if the
     * value exceeds the actual number of columns, the actual number of columns is used.
     */
    uint32_t columnSpan;
} ArkUI_GridItemRect;

/**
 * @brief Defines grid layout options, which are used to set layout parameters for irregular grid items in a **Grid**
 * component, including the irregular item index and layout callback. An irregular grid item refers to a grid item that
 * spans rows and columns or has a different size in the grid layout.
 *
 * @since 22
 */
typedef struct ArkUI_GridLayoutOptions ArkUI_GridLayoutOptions;

/**
 * @brief Enumerates the alignment modes of the {@link GridItem} component.
 *
 * @since 22
 */
typedef enum {
    /**
     * Use the default alignment mode of the grid.
     */
    GRID_ITEM_ALIGNMENT_DEFAULT = 0,

    /**
     * Use the height of the tallest grid item in a row as the height for all other grid items in that row.
     */
    GRID_ITEM_ALIGNMENT_STRETCH = 1,
} ArkUI_GridItemAlignment;

/**
 * @brief Enumerates styles of grid items.
 *
 * @since 22
 */
typedef enum {
    /**
     * No style.
     */
    GRID_ITEM_STYLE_NONE = 0,

    /**
     * Hover or press style.
     */
    GRID_ITEM_STYLE_PLAIN = 1,
} ArkUI_GridItemStyle;

/**
 * @brief Creates **Grid** layout options. Call **OH_ArkUI_GridLayoutOptions_Dispose** to dispose of it after use.
 *
 * @return Pointer to the created **Grid** layout option array.
 * @since 22
 */
ArkUI_GridLayoutOptions* OH_ArkUI_GridLayoutOptions_Create();

/**
 * @brief Disposes of the **Grid** layout options to release resources.
 *
 * @param option Pointer to the **Grid** layout option array to dispose of.
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_Dispose(ArkUI_GridLayoutOptions* option);
/**
 * @brief Sets the irregular grid item index array for the grid layout.
 *
 * @param option Pointer to the **Grid** layout option array to set.
 * @param irregularIndexes Pointer to the array of irregular grid item indexes used to set the **Grid** layout options.
 * @param size Number of elements in the **irregularIndexes** array.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>A possible cause is that mandatory parameters are left unspecified.
 * @since 22
 */
int32_t OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(
    ArkUI_GridLayoutOptions* option, uint32_t* irregularIndexes, int32_t size);
/**
 * @brief Obtains the irregular grid item index array for the grid layout. When **
 * OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback** is not set, the grid item specified in this
 * parameter occupies an entire row of the grid that scrolls vertically or an entire column of the grid that scrolls
 * horizontally.
 *
 * @param option Pointer to the **Grid** layout option array to be obtained.
 * @param irregularIndexes Pointer to the buffer for receiving the irregular grid item index array.
 * @param size Pointer to the number of elements that the **irregularIndexes** buffer can hold. Pass the buffer
 *     capacity before calling, and it will be updated to the actual number of indexes actually written after a
 *     successful call.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the array size is insufficient.
 *     <br>A possible cause is that mandatory parameters are left unspecified.
 * @since 22
 */
int32_t OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(
    ArkUI_GridLayoutOptions* option, uint32_t* irregularIndexes, int32_t* size);

/**
 * @brief Registers a callback to obtain the row and column span for the grid item at the specified index.
 *
 * @param option Pointer to the **Grid** layout option array.
 * @param userData Pointer to the user-defined data.
 * @param callback Callback that returns the row and column span for the grid item at the specified index.
 *     itemIndex: grid item index, which must be within the range set by
 *     {@link OH_ArkUI_GridLayoutOptions_SetIrregularIndexes}.
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback(
    ArkUI_GridLayoutOptions* option, void* userData, ArkUI_GridItemSize (*callback)(int32_t itemIndex, void* userData));

/**
 * @brief Registers a callback to obtain the starting row, starting column, row span, and column span for the grid item
 * at the specified index.
 *
 * @param option Pointer to the **Grid** layout option array.
 * @param userData Pointer to the user-defined data.
 * @param callback Callback that returns the starting row, starting column, row span,
 *     and column span for the grid item at the specified index.
 *     itemIndex: grid item index.
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback(
    ArkUI_GridLayoutOptions* option, void* userData, ArkUI_GridItemRect (*callback)(int32_t itemIndex, void* userData));

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_GRID_GRID_H
/** @} */
