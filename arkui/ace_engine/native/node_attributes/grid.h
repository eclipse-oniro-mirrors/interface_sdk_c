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
 * @brief Provides Grid-related type and function definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUIKit
 * @since 22
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_GRID_GRID_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_GRID_GRID_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the return value structure for the <b>onGetIrregularSizeByIndex</b> callback
 * in <b>Grid</b> layout options.
 *
 * @since 22
 */
typedef struct {
    /** Number of rows occupied by the <b>GridItem</b> component. */
    uint32_t rowSpan;
    /** Number of columns occupied by the <b>GridItem</b> component. */
    uint32_t columnSpan;
} ArkUI_GridItemSize;

/**
 * @brief Defines the return value structure for the <b>onGetRectByIndex</b> callback in <b>Grid</b> layout options.
 *
 * @since 22
 */
typedef struct {
    /** Starting row position of the <b>GridItem</b> component. */
    uint32_t rowStart;
    /** Starting column position of the <b>GridItem</b> component. */
    uint32_t columnStart;
    /** Number of rows occupied by the <b>GridItem</b> component. */
    uint32_t rowSpan;
    /** Number of columns occupied by the <b>GridItem</b> component. */
    uint32_t columnSpan;
} ArkUI_GridItemRect;

/**
 * @brief Defines the <b>Grid</b> layout options.
 *
 * @since 22
 */
typedef struct ArkUI_GridLayoutOptions ArkUI_GridLayoutOptions;

/**
 * @brief Enumerates the grid item alignment modes.
 *
 * @since 22
 */
typedef enum {
    /** Use the default alignment mode of the grid. */
    GRID_ITEM_ALIGNMENT_DEFAULT = 0,
    /** Set the height of all grid items in a row to match the height of the tallest item in that row. */
    GRID_ITEM_ALIGNMENT_STRETCH = 1,
} ArkUI_GridItemAlignment;

/**
 * @brief Enumerates styles of grid items.
 *
 * @since 22
 */
typedef enum {
    /** No style. */
    GRID_ITEM_STYLE_NONE = 0,
    /** Hover or press style. */
    GRID_ITEM_STYLE_PLAIN = 1,
} ArkUI_GridItemStyle;

/**
 * @brief Creates <b>Grid</b> layout options.
 *
 * @return <b>Grid</b> layout options created.
 * @since 22
 */
ArkUI_GridLayoutOptions* OH_ArkUI_GridLayoutOptions_Create();

/**
 * @brief Disposes of <b>Grid</b> layout options.
 *
 * @param option <b>Grid</b> layout options.
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_Dispose(ArkUI_GridLayoutOptions* option);

/**
 * @brief Sets the irregular grid item index array for the grid layout.
 *
 * @param option <b>Grid</b> layout options.
 * @param irregularIndexes Array of irregular grid item indexes.
 * @param size Size of the index array.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         If an error code is returned, it may be due to a failure in parameter validation;
 *         the parameter must not be null.
 * @since 22
 */
int32_t OH_ArkUI_GridLayoutOptions_SetIrregularIndexes(
    ArkUI_GridLayoutOptions* option, uint32_t* irregularIndexes, int32_t size);

/**
 * @brief Obtains the irregular grid item index array for the grid layout.
 * When <b>OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback</b> is not set,
 * the grid item specified in <b>irregularIndexes</b> occupies an entire row of the grid that scrolls vertically or
 * an entire column of the grid that scrolls horizontally.
 *
 * @param option <b>Grid</b> layout options.
 * @param irregularIndexes Array of irregular grid item indexes.
 * @param size Size of the index array.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the provided buffer size is insufficient.
 *         If an error code is returned, it may be due to a failure in parameter validation;
 *         the parameter must not be null.
 * @since 22
 */
int32_t OH_ArkUI_GridLayoutOptions_GetIrregularIndexes(
    ArkUI_GridLayoutOptions* option, uint32_t* irregularIndexes, int32_t* size);

/**
 * @brief Registers a callback to obtain the row and column span for the grid item at the specified index.
 *
 * @param option <b>Grid</b> layout options.
 * @param userData Indicates the custom data.
 * @param callback Callback that returns the row and column span for the grid item at the specified index.
 *        itemIndex: grid item index, which must be within the range set by
 *        {@link OH_ArkUI_GridLayoutOptions_SetIrregularIndexes}.
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_RegisterGetIrregularSizeByIndexCallback(
    ArkUI_GridLayoutOptions* option, void* userData, ArkUI_GridItemSize (*callback)(int32_t itemIndex, void* userData));

/**
 * @brief Registers a callback to obtain the starting row, starting column, row span,
 * and column span for the grid item at the specified index.
 *
 * @param option <b>Grid</b> layout options.
 * @param userData Indicates the custom data.
 * @param callback Callback that returns the starting row, starting column, row span,
 *        and column span for the grid item at the specified index.
 *        itemIndex: grid item index.
 * @since 22
 */
void OH_ArkUI_GridLayoutOptions_RegisterGetRectByIndexCallback(
    ArkUI_GridLayoutOptions* option, void* userData, ArkUI_GridItemRect (*callback)(int32_t itemIndex, void* userData));

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_GRID_GRID_H
/** @} */
