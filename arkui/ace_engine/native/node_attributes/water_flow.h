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
 * @brief ArkUI WaterFlow related types and functions on the native side.
 *
 * @since 12
 */

/**
 * @file node_water_flow.h
 *
 * @brief Provides WaterFlow-related type and function definitions for
 * <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUIKit
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_WATER_FLOW_WATER_FLOW_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_WATER_FLOW_WATER_FLOW_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Describes the margins of a component.
 *
 * @since 12
 */
typedef struct {
    /** Top margin, in vp. */
    float top;

    /**
     * Right margin, in vp.
     */
    float right;

    /**
     * Bottom margin, in vp.
     */
    float bottom;

    /**
     * Left margin, in vp.
     */
    float left;
} ArkUI_Margin;

/**
 * @brief Defines the water flow section configuration.
 *
 * @since 12
 */
typedef struct ArkUI_WaterFlowSectionOption ArkUI_WaterFlowSectionOption;

/**
 * @brief Enumerates the layout modes of the {@link WaterFlow} component.
 *
 * @since 18
 */
typedef enum {
    /**
     * Layout from top to bottom. In scenarios where column switching occurs, the layout starts from the first
     * {@link water flow item} to the currently displayed {@link water flow item}.
     */
    ARKUI_WATER_FLOW_LAYOUT_MODE_ALWAYS_TOP_DOWN = 0,

    /**
     * Sliding window layout. In scenarios where column switching occurs, only the range of {@link water flow items}
     * currently on display is re-laid out. As the user scrolls down with their finger, {@link water flow items} that
     * enter the display range from above are subsequently laid out.
     */
    ARKUI_WATER_FLOW_LAYOUT_MODE_SLIDING_WINDOW
} ArkUI_WaterFlowLayoutMode;

/**
 * @brief Creates the {@link FlowItem} section configuration.
 *
 * @return Pointer to the {@link FlowItem} section configuration.
 * @since 12
 */
ArkUI_WaterFlowSectionOption* OH_ArkUI_WaterFlowSectionOption_Create();

/**
 * @brief Disposes of the pointer to the {@link FlowItem} section configuration.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_Dispose(ArkUI_WaterFlowSectionOption* option);

/**
 * @brief Sets the array length for a water flow section configuration.
 *
 * @param option Pointer to a water flow section configuration.
 * @param size Size of the array.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetSize(ArkUI_WaterFlowSectionOption* option, int32_t size);

/**
 * @brief Obtains the length of the {@link FlowItem} section configuration array.
 *
 * @param option Pointer to a water flow section configuration.
 * @return Size of the array. If **-1** is returned, an error code indicating failure is returned. The possible cause
 *     is that the **option** parameter is abnormal, for example, a null pointer.
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetSize(ArkUI_WaterFlowSectionOption* option);

/**
 * @brief Sets the number of {@link water flow items} in the section.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the target water flow section.
 * @param itemCount Number of {@link water flow items} in the section.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetItemCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t itemCount);

/**
 * @brief Obtains the number of {@link water flow items} at the corresponding index based on the {@link FlowItem}
 * section configuration.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the target water flow section.
 * @return Number of items in the water flow section.
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetItemCount(ArkUI_WaterFlowSectionOption* option, int32_t index);
/**
 * @brief Obtains the main axis size of a specified water flow item based on **itemIndex** in the {@link FlowItem}
 * section configuration. To use custom data in the callback, call
 * {@link OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndexWithUserData}.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the target water flow section.
 * @param callback Callback used to return the result. **itemIndex** indicates the index of {@link FlowItem}.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndex(
    ArkUI_WaterFlowSectionOption* option, int32_t index, float (*callback)(int32_t itemIndex));

/**
 * @brief Obtains the main axis size of a specified water flow item based on **itemIndex** in the {@link FlowItem}
 * section configuration. The difference between this API and
 * {@link OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndex} is that this API allows you to pass
 * custom data (**userData**) and receive the data in the callback function.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the target water flow section.
 * @param userData Pointer to user-defined data, which will be passed back to the user in the callback.
 * @param callback Callback used to return the result. **itemIndex**: index of the {@link water flow item}; **userData**
 *     : user-defined data.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndexWithUserData(
    ArkUI_WaterFlowSectionOption* option, int32_t index, void* userData,
    float (*callback)(int32_t itemIndex, void* userData));

/**
 * @brief Sets the number of columns (in a vertical layout) or rows (in a horizontal layout) of a water flow.
 *
 * @param option Pointer to a water flow section configuration.
 * @param index Index of the target water flow section.
 * @param crossCount Number of columns or rows, depending on the layout direction.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetCrossCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t crossCount);

/**
 * @brief Obtains the number of layout grids at the corresponding index based on the {@link FlowItem} section
 * configuration.
 *
 * @param option Pointer to a water flow section configuration.
 * @param index Index of the target water flow section.
 * @return Number of columns or rows, depending on the layout direction.
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetCrossCount(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief Sets the gap between columns in the specified water flow section.
 *
 * @param option Pointer to a water flow section configuration.
 * @param index Index of the target water flow section.
 * @param columnGap Gap between columns. Unit: vp.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float columnGap);

/**
 * @brief Obtains the gap between columns in the water flow section that matches the specified index.
 *
 * @param option Pointer to a water flow section configuration.
 * @param index Index of the target water flow section.
 * @return Gap between columns. Unit: vp.
 * @since 12
 */
float OH_ArkUI_WaterFlowSectionOption_GetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief Sets the gap between rows in the **FlowItem** section.
 *
 * @param option Pointer to a water flow section configuration.
 * @param index Index of the **FlowItem** section configuration array.
 * @param rowGap Gap between rows. Unit: vp.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float rowGap);

/**
 * @brief Obtains the gap between rows in the section at the corresponding index based on the {@link FlowItem} section
 * configuration.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the target water flow section.
 * @return Gap between rows. Unit: vp.
 * @since 12
 */
float OH_ArkUI_WaterFlowSectionOption_GetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief Sets the margins for the specified water flow section.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the target water flow section.
 * @param marginTop Top margin of {@link FlowItem}.
 * @param marginRight Right margin of {@link FlowItem}.
 * @param marginBottom Bottom margin of {@link FlowItem}.
 * @param marginLeft Left margin of {@link FlowItem}.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index, float marginTop,
    float marginRight, float marginBottom, float marginLeft);

/**
 * @brief Obtains the top margin of the section at the corresponding index based on the {@link FlowItem} section
 * configuration.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the target water flow section.
 * @return Margins. Unit: vp.
 * @since 12
 */
ArkUI_Margin OH_ArkUI_WaterFlowSectionOption_GetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_WATER_FLOW_WATER_FLOW_H
/** @} */
