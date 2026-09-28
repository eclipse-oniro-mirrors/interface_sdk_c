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
 * @brief Defines enumerations and APIs related to **WaterFlow**.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_WATER_FLOW_WATER_FLOW_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_WATER_FLOW_WATER_FLOW_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Describes the margins of a component, which is used to define the blank area between the component boundary
 * and its parent container or adjacent components, affecting the actually occupied space and position of the component
 * in the layout.
 *
 * @since 12
 */
typedef struct {
    /**
     * Top margin, in vp.
     */
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
 * @brief Creates a {@link water flow} section configuration, with an initial array length of 1. Call
 * {@link OH_ArkUI_WaterFlowSectionOption_Dispose} to release resources after the use.
 *
 * @return Pointer to the {@link FlowItem} section configuration.
 * @since 12
 */
ArkUI_WaterFlowSectionOption* OH_ArkUI_WaterFlowSectionOption_Create();

/**
 * @brief Disposes of the pointer to a {@link water flow} section configuration created by
 * {@link OH_ArkUI_WaterFlowSectionOption_Create}. The pointer must not be accessed after being disposed of.
 *
 * @param option Pointer to the {@link water flow} section configuration to dispose of.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_Dispose(ArkUI_WaterFlowSectionOption* option);

/**
 * @brief Sets the array length of a water flow section configuration. For scaling-out, the original configuration is
 * retained and a new group configuration is added at the end of the array. When scaling-in, the configuration within
 * the new length range is retained and the rest are deleted.
 *
 * @param option Pointer to a water flow section configuration.
 * @param size Array length. The value range is greater than or equal to 0. No operation is performed when a negative
 *     number is passed in.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetSize(ArkUI_WaterFlowSectionOption* option, int32_t size);

/**
 * @brief Obtains the length of the {@link FlowItem} section configuration array.
 *
 * @param option Pointer to a water flow section configuration.
 * @return Array length. **-1** is returned if **option** is a null pointer.
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetSize(ArkUI_WaterFlowSectionOption* option);

/**
 * @brief Sets the number of {@link water flow items} in the section.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the section configuration array. The value range is greater than or equal to 0. When the value
 *     exceeds the current array length, the array is automatically expanded to **index** + 1.
 * @param itemCount Number of {@link flow items} in the section. The value range is greater than or equal to 0. No
 *     operation is performed when a negative number is passed in.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetItemCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t itemCount);

/**
 * @brief Obtains the number of {@link water flow items} at the corresponding index based on the {@link FlowItem}
 * section configuration.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the section configuration array. The value ranges from 0 to the array length minus 1.
 * @return Number of flow items in the section. **0** is returned if the value of **index** is greater than or equal to
 *     the array length, and **-1** if **option** is a null pointer.
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetItemCount(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief Registers a callback for the section at the specified index in the section configuration array to provide the
 * main axis size of {@link FlowItem}. When **WaterFlow** lays out **FlowItem** in this section, the index of the
 * current **FlowItem** in **WaterFlow** is passed to the callback as **itemIndex**, and the callback return value is
 * used as the main axis size of the **FlowItem**. The main axis size is the height in vertical layout and the width in
 * horizontal layout. To use custom data in the callback, use
 * {@link OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndexWithUserData}.
 *
 * @param option Pointer to the {@link water flow} section configuration.
 * @param index Index of the section configuration array for which the callback is to be registered. The value range is
 *     0 to the array length minus 1.
 * @param callback Callback used to return the result. **itemIndex** indicates the index of {@link FlowItem}.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndex(
    ArkUI_WaterFlowSectionOption* option, int32_t index, float (*callback)(int32_t itemIndex));

/**
 * @brief Registers a callback for the section at the specified index in the section configuration array to provide the
 * main axis size of {@link FlowItem} and saves the passed **userData**. When **WaterFlow** lays out **FlowItem** in
 * this section, the index of the current **FlowItem** in **WaterFlow** and **userData** are passed to the callback as
 * the first and second parameters, respectively. **userData** is only used to pass additional data to the callback,
 * and the main axis size of the **FlowItem** is provided by the callback return value. The main axis size is the
 * height in vertical layout and the width in horizontal layout.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the group configuration array for which the callback is to be registered. The value ranges
 *     from 0 to the array length minus 1.
 * @param userData Pointer to the additional data passed to the callback. It does not directly represent the main axis
 *     size of the **FlowItem**. During **WaterFlow** layout, this parameter is passed as the second parameter of the
 *     callback. This pointer is managed by the caller and must remain valid while the callback may be triggered.
 * @param callback Callback used to return the result. **itemIndex**: index of the {@link water flow item}; **userData**
 *     : user-defined data.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndexWithUserData(
    ArkUI_WaterFlowSectionOption* option, int32_t index, void* userData,
    float (*callback)(int32_t itemIndex, void* userData));

/**
 * @brief Sets the number of columns (in a vertical layout) or rows (in a horizontal layout) of a water flow section.
 *
 * @param option Pointer to a water flow section configuration.
 * @param index Index of the section configuration array. The value range is greater than or equal to 0. When the value
 *     exceeds the current array length, the array is automatically expanded to **index** + 1.
 * @param crossCount Number of layout grids. In vertical layout, it indicates the number of columns; in horizontal
 *     layout, it indicates the number of rows. A value less than or equal to 0 is treated as **1**.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetCrossCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t crossCount);

/**
 * @brief Obtains the number of layout grids at the corresponding index based on the {@link FlowItem} section
 * configuration.
 *
 * @param option Pointer to a water flow section configuration.
 * @param index Index of the section configuration array. The value range is from 0 to the array length minus 1.
 * @return Number of layout grid columns. **0** is returned if the value of **index** is greater than or equal to the
 *     array length, and **-1** if **option** is a null pointer.
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetCrossCount(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief Sets the gap between columns in the specified water flow section.
 *
 * @param option Pointer to a water flow section configuration.
 * @param index Index of the section configuration array. The value range is greater than or equal to 0. When the value
 *     exceeds the current array length, the array is automatically expanded to **index** + 1.
 * @param columnGap Gap between columns. Unit: vp. If a negative number is passed in, it is treated as 0.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float columnGap);

/**
 * @brief Obtains the gap between columns in the water flow section that matches the specified index.
 *
 * @param option Pointer to a water flow section configuration.
 * @param index Index of the section configuration array. The value ranges from 0 to the array length minus 1.
 * @return Gap between columns. The unit is vp.
 * @since 12
 */
float OH_ArkUI_WaterFlowSectionOption_GetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief Sets the row spacing for the specified group.
 *
 * @param option Pointer to a water flow section configuration.
 * @param index Index of the section configuration array. The value range is greater than or equal to 0. When the value
 *     exceeds the current array length, the array is automatically expanded to **index** + 1.
 * @param rowGap Gap between rows. Unit: vp. If a negative number is passed in, it is treated as **0**.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float rowGap);

/**
 * @brief Obtains the gap between rows in the section at the corresponding index based on the {@link FlowItem} section
 * configuration.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the section configuration array. The value range is 0 to the array length minus 1.
 * @return Gap between rows. The unit is vp.
 * @since 12
 */
float OH_ArkUI_WaterFlowSectionOption_GetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief Sets the margins for the specified water flow section.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the section configuration array. The value range is greater than or equal to 0. When the value
 *     exceeds the current array length, the array is automatically expanded to **index** + 1.
 * @param marginTop Top margin of {@link FlowItem}. Unit: vp.
 * @param marginRight Right margin of {@link FlowItem}. Unit: vp.
 * @param marginBottom Bottom margin of {@link FlowItem}. Unit: vp.
 * @param marginLeft Left margin of {@link FlowItem}. Unit: vp.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index, float marginTop,
    float marginRight, float marginBottom, float marginLeft);

/**
 * @brief Obtains the margins of the section at the corresponding index based on the {@link FlowItem} section
 * configuration.
 *
 * @param option Pointer to the {@link FlowItem} section configuration.
 * @param index Index of the section configuration array. The value ranges from 0 to the array length minus 1.
 * @return Margin. The unit is vp.
 * @since 12
 */
ArkUI_Margin OH_ArkUI_WaterFlowSectionOption_GetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_WATER_FLOW_WATER_FLOW_H
/** @} */
