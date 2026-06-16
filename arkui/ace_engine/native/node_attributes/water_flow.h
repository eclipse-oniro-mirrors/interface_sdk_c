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
    /** Right margin, in vp. */
    float right;
    /** Bottom margin, in vp. */
    float bottom;
    /** Left margin, in vp. */
    float left;
} ArkUI_Margin;

/**
 * @brief Defines the water flow section configuration.
 *
 * @since 12
 */
typedef struct ArkUI_WaterFlowSectionOption ArkUI_WaterFlowSectionOption;

/**
 * @brief Enumerates the layout modes of the WaterFlow component.
 *
 * @since 18
 */
typedef enum {
    /** Layout items from top to viewport. */
    ARKUI_WATER_FLOW_LAYOUT_MODE_ALWAYS_TOP_DOWN = 0,
    /** Layout items in viewport. */
    ARKUI_WATER_FLOW_LAYOUT_MODE_SLIDING_WINDOW,
} ArkUI_WaterFlowLayoutMode;

/**
 * @brief Creates water flow section configuration.
 *
 * @return Returns the water flow section configuration.
 * @since 12
 */
ArkUI_WaterFlowSectionOption* OH_ArkUI_WaterFlowSectionOption_Create();

/**
 * @brief Destroys the pointer to a water flow section configuration.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_Dispose(ArkUI_WaterFlowSectionOption* option);

/**
 * @brief Sets the FlowItem block configuration information array length.
 *
 * @param option FlowItem Indicates the packet configuration.
 * @param size Array Length.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetSize(ArkUI_WaterFlowSectionOption* option, int32_t size);

/**
 * @brief Gets the FlowItem grouping configuration information array length.
 *
 * @param option FlowItem Indicates the packet configuration.
 * @return Array size. If -1 is returned, the return fails.
 *         The possible cause of the failure is that the option parameter is abnormal, such as a null pointer.
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetSize(ArkUI_WaterFlowSectionOption* option);

/**
 * @brief Sets the number of items in a water flow section.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @param index Indicates the index of the target water flow section.
 * @param itemCount Indicates the number of items in the water flow section.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetItemCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t itemCount);

/**
 * @brief Obtains the number of items in the water flow section that matches the
 * specified index.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @param index Indicates the index of the target water flow section.
 * @return Returns the number of items in the water flow section.
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetItemCount(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief The FlowItem grouping configuration information getsthe spindle size
 * of the specified Item based on flowItemIndex.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @param index Indicates the index of the target water flow section.
 * @param callback Gets the spindle size of the specified Item based on index.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndex(
    ArkUI_WaterFlowSectionOption* option, int32_t index, float (*callback)(int32_t itemIndex));

/**
 * @brief The FlowItem grouping configuration information getsthe spindle size
 * of the specified Item based on flowItemIndex.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @param index Indicates the index of the target water flow section.
 * @param userData FlowItem Custom data.
 * @param callback Gets the spindle size of the specified Item based on index.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndexWithUserData(
    ArkUI_WaterFlowSectionOption* option, int32_t index, void* userData,
    float (*callback)(int32_t itemIndex, void* userData));

/**
 * @brief Sets the number of columns (in a vertical layout) or rows (in a
 * horizontal layout) of a water flow.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @param index Indicates the index of the target water flow section.
 * @param crossCount Indicates the number of columns or rows, depending on the
 * layout direction.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetCrossCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t crossCount);

/**
 * @brief Obtains the number of columns (in a vertical layout) or rows (in a
 * horizontal layout) in the water flow section that matches the specified
 * index.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @param index Indicates the index of the target water flow section.
 * @return Returns the number of columns or rows.
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetCrossCount(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief Sets the gap between columns in the specified water flow section.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @param index Indicates the index of the target water flow section.
 * @param columnGap Indicates the gap between columns to set.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float columnGap);

/**
 * @brief Obtains the gap between columns in the water flow section that matches
 * the specified index.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @param index Indicates the index of the target water flow section.
 * @return Returns the gap between columns.
 * @since 12
 */
float OH_ArkUI_WaterFlowSectionOption_GetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief Sets the gap between rows in the specified water flow section.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @param index Indicates the index of the target water flow section.
 * @param rowGap Indicates the gap between rows to set.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float rowGap);

/**
 * @brief Obtains the gap between rows in the water flow section that matches
 * the specified index.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @param index Indicates the index of the target water flow section.
 * @return Returns the gap between rows.
 * @since 12
 */
float OH_ArkUI_WaterFlowSectionOption_GetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief Sets the margins for the specified water flow section.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @param index Indicates the index of the target water flow section.
 * @param marginTop Indicates the top margin of the water flow section.
 * @param marginRight Indicates the right margin of the water flow section.
 * @param marginBottom Indicates the bottom margin of the water flow section.
 * @param marginLeft Indicates the left margin of the water flow section.
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index, float marginTop,
    float marginRight, float marginBottom, float marginLeft);

/**
 * @brief Obtains the margins of the water flow section that matches the
 * specified index.
 *
 * @param option Indicates the pointer to a water flow section configuration.
 * @param index Indicates the index of the target water flow section.
 * @return Returns the margins.
 * @since 12
 */
ArkUI_Margin OH_ArkUI_WaterFlowSectionOption_GetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_WATER_FLOW_WATER_FLOW_H
/** @} */
