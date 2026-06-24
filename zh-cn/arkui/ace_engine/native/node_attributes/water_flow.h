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
 * @brief 定义FlowItem分组配置信息。
 *
 * @since 12
 */
typedef struct ArkUI_WaterFlowSectionOption ArkUI_WaterFlowSectionOption;

/**
 * @brief 定义WaterFlow组件布局模式枚举值。
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
 * @brief 创建FlowItem分组配置信息。
 *
 * @return FlowItem分组配置信息。
 * @since 12
 */
ArkUI_WaterFlowSectionOption* OH_ArkUI_WaterFlowSectionOption_Create();

/**
 * @brief 销毁FlowItem分组配置信息指针。
 *
 * @param option FlowItem分组配置信息。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_Dispose(ArkUI_WaterFlowSectionOption* option);

/**
 * @brief 设置FlowItem分组配置信息数组长度。
 *
 * @param option FlowItem分组配置信息。
 * @param size 数组长度。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetSize(ArkUI_WaterFlowSectionOption* option, int32_t size);

/**
 * @brief 获取FlowItem分组配置信息数组长度。
 *
 * @param option FlowItem分组配置信息。
 * @return 数组长度。如果返回-1，则返回失败。失败的原因可能是option参数异常，如空指针。
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetSize(ArkUI_WaterFlowSectionOption* option);

/**
 * @brief 设置分组中FlowItem数量。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值。
 * @param itemCount 分组中FlowItem数量。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetItemCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t itemCount);

/**
 * @brief 通过FlowItem分组配置信息获取对应索引下的FlowItem数量。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值。
 * @return 分组中FlowItem数量。
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetItemCount(ArkUI_WaterFlowSectionOption* option, int32_t index);
/**
 * @brief 通过FlowItem分组配置信息根据flowItemIndex获取指定FlowItem的主轴大小。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值。
 * @param callback 根据index获取指定Item的主轴大小。
 *        flowItemIndex：FlowItem索引值。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndex(
    ArkUI_WaterFlowSectionOption* option, int32_t index, float (*callback)(int32_t itemIndex));

/**
 * @brief 通过FlowItem分组配置信息根据flowItemIndex获取指定Item的主轴大小。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值。
 * @param userData FlowItem自定义数据。
 * @param callback 根据index获取指定Item的主轴大小。
 *        itemIndex：FlowItem索引值。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndexWithUserData(
    ArkUI_WaterFlowSectionOption* option, int32_t index, void* userData,
    float (*callback)(int32_t itemIndex, void* userData));

/**
 * @brief 设置布局栅格，纵向布局时为列数，横向布局时为行数。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值。
 * @param crossCount 布局栅格数量。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetCrossCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t crossCount);

/**
 * @brief 通过FlowItem分组配置信息获取对应索引下的布局栅格数。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值。
 * @return 布局栅格数量。
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetCrossCount(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief 设置分组的列间距。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值。
 * @param columnGap 列间距。单位：vp。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float columnGap);

/**
 * @brief 通过FlowItem分组配置信息获取对应索引下的分组的列间距。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值。
 * @return 列间距。单位：vp。
 * @since 12
 */
float OH_ArkUI_WaterFlowSectionOption_GetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief 设置FlowItem分组的行间距。
 *
 * @param option FlowItem分组配置信息。
 * @param index FlowItem分组配置信息数组索引值。
 * @param rowGap 行间距。单位：vp。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float rowGap);

/**
 * @brief 通过FlowItem分组配置信息获取对应索引下的分组的行间距。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值。
 * @return 行间距。单位：vp。
 * @since 12
 */
float OH_ArkUI_WaterFlowSectionOption_GetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief 设置分组的外边距。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值。
 * @param marginTop FlowItem上外边距。
 * @param marginRight FlowItem右外边距。
 * @param marginBottom FlowItem下外边距。
 * @param marginLeft FlowItem左外边距。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index, float marginTop,
    float marginRight, float marginBottom, float marginLeft);

/**
 * @brief 通过FlowItem分组配置信息获取对应索引下的分组的外边距。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值。
 * @return 外边距。单位：vp。
 * @since 12
 */
ArkUI_Margin OH_ArkUI_WaterFlowSectionOption_GetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_WATER_FLOW_WATER_FLOW_H

/** @} */