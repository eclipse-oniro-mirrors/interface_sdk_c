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
 * @file water_flow.h
 *
 * @brief 定义WaterFlow组件相关的枚举和接口。
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
 * @brief 外边距属性，定义组件边界与父容器或相邻组件之间的空白区域，影响组件在布局中的实际占用空间和位置。
 *
 * @since 12
 */
typedef struct {
    /** 上外边距，单位为vp。 */
    float top;

    /**
     * 右外边距，单位为vp。
     */
    float right;

    /**
     * 下外边距，单位为vp。
     */
    float bottom;

    /**
     * 左外边距，单位为vp。
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
 * @brief 定义{@link WaterFlow}组件布局模式枚举值。
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
 * @brief 创建{@link FlowItem}分组配置信息，初始数组长度为1。使用结束后需调用{@link OH_ArkUI_WaterFlowSectionOption_Dispose}释放资源。
 *
 * @return {@link FlowItem}分组配置信息。
 * @since 12
 */
ArkUI_WaterFlowSectionOption* OH_ArkUI_WaterFlowSectionOption_Create();

/**
 * @brief 销毁由{@link OH_ArkUI_WaterFlowSectionOption_Create}创建的{@link FlowItem}分组配置信息。销毁后不得继续访问该指针。
 *
 * @param option 要销毁的{@link FlowItem}分组配置信息。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_Dispose(ArkUI_WaterFlowSectionOption* option);

/**
 * @brief 设置FlowItem分组配置信息数组长度。扩容时保留原有配置，并在数组末尾新增分组配置；缩容时保留新长度范围内的配置，删除其余配置。
 *
 * @param option FlowItem分组配置信息。
 * @param size 数组长度，取值范围为大于等于0。传入负数时不执行操作。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetSize(ArkUI_WaterFlowSectionOption* option, int32_t size);

/**
 * @brief 获取{@link FlowItem}分组配置信息数组长度。
 *
 * @param option FlowItem分组配置信息。
 * @return 数组长度。option为空指针时返回-1。
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetSize(ArkUI_WaterFlowSectionOption* option);

/**
 * @brief 设置分组中{@link FlowItem}数量。
 *
 * @param option {@link FlowItem}分组配置信息。
 * @param index 分组配置信息数组索引值，取值范围为大于等于0。超出当前数组长度时，数组自动扩展至index + 1。
 * @param itemCount 分组中{@link FlowItem}数量，取值范围为大于等于0。传入负数时不执行操作。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetItemCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t itemCount);

/**
 * @brief 通过{@link FlowItem}分组配置信息获取对应索引下的{@link FlowItem}数量。
 *
 * @param option {@link FlowItem}分组配置信息。
 * @param index 分组配置信息数组索引值，取值范围为0至数组长度减1。
 * @return 分组中FlowItem数量。index大于等于数组长度时返回0，option为空指针时返回-1。
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetItemCount(ArkUI_WaterFlowSectionOption* option, int32_t index);
/**
 * @brief 为分组配置信息数组中索引为index的分组注册用于提供{@link FlowItem}主轴尺寸的回调。WaterFlow布局该分组内的FlowItem时，
 * 将当前FlowItem在WaterFlow中的索引作为itemIndex传入回调，并将回调返回值作为该FlowItem的主轴尺寸。主轴尺寸在纵向布局时为高度，在横向布局时为宽度。如需在回调中使用自定义数据，可使用
 * {@link OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndexWithUserData}。
 *
 * @param option {@link FlowItem}分组配置信息。
 * @param index 要注册回调的分组配置信息数组索引值，取值范围为0至数组长度减1。
 * @param callback 主轴尺寸回调。itemIndex为当前{@link FlowItem}在WaterFlow中的索引；开发者通过返回值提供该FlowItem的主轴尺寸，单位：vp，返回负数时按0处理。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndex(
    ArkUI_WaterFlowSectionOption* option, int32_t index, float (*callback)(int32_t itemIndex));

/**
 * @brief 为分组配置信息数组中索引为index的分组注册用于提供{@link FlowItem}主轴尺寸的回调，同时保存传入的userData。WaterFlow布局该分组内的FlowItem时，
 * 将当前FlowItem在WaterFlow中的索引和userData分别作为回调的第一个、第二个参数传入。userData仅用于向回调传递附加数据，FlowItem的主轴尺寸由回调返回值提供。主轴尺寸在纵向布局时为高度，
 * 在横向布局时为宽度。
 *
 * @param option {@link FlowItem}分组配置信息。
 * @param index 要注册回调的分组配置信息数组索引值，取值范围为0至数组长度减1。
 * @param userData 传递给回调的附加数据指针，不直接表示FlowItem的主轴尺寸。WaterFlow布局时，将该参数作为回调的第二个参数传入。该指针由调用方管理，需在回调可能触发期间保持有效。
 * @param callback 主轴尺寸回调。itemIndex为当前{@link FlowItem}在WaterFlow中的索引；userData为传入接口的用户自定义数据；
 *     开发者通过返回值提供该FlowItem的主轴尺寸，单位：vp，返回负数时按0处理。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndexWithUserData(
    ArkUI_WaterFlowSectionOption* option, int32_t index, void* userData,
    float (*callback)(int32_t itemIndex, void* userData));

/**
 * @brief 设置布局栅格，纵向布局时为列数，横向布局时为行数。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值，取值范围为大于等于0。超出当前数组长度时，数组自动扩展至index + 1。
 * @param crossCount 布局栅格数量，纵向布局时为列数，横向布局时为行数。传入小于等于0的值时按1处理。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetCrossCount(
    ArkUI_WaterFlowSectionOption* option, int32_t index, int32_t crossCount);

/**
 * @brief 通过{@link FlowItem}分组配置信息获取对应索引下的布局栅格数。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值，取值范围为0至数组长度减1。
 * @return 布局栅格数量。index大于等于数组长度时返回0，option为空指针时返回-1。
 * @since 12
 */
int32_t OH_ArkUI_WaterFlowSectionOption_GetCrossCount(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief 设置分组的列间距。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值，取值范围为大于等于0。超出当前数组长度时，数组自动扩展至index + 1。
 * @param columnGap 列间距。单位：vp。传入负数时按0处理。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float columnGap);

/**
 * @brief 通过FlowItem分组配置信息获取对应索引下的分组的列间距。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值，取值范围为0至数组长度减1。
 * @return 列间距。单位：vp。
 * @since 12
 */
float OH_ArkUI_WaterFlowSectionOption_GetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief 设置指定分组的行间距。
 *
 * @param option FlowItem分组配置信息。
 * @param index 分组配置信息数组索引值，取值范围为大于等于0。超出当前数组长度时，数组自动扩展至index + 1。
 * @param rowGap 行间距。单位：vp。传入负数时按0处理。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index, float rowGap);

/**
 * @brief 通过{@link FlowItem}分组配置信息获取对应索引下的分组的行间距。
 *
 * @param option {@link FlowItem}分组配置信息。
 * @param index 分组配置信息数组索引值，取值范围为0至数组长度减1。
 * @return 行间距。单位：vp。
 * @since 12
 */
float OH_ArkUI_WaterFlowSectionOption_GetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
 * @brief 设置分组的外边距。
 *
 * @param option {@link FlowItem}分组配置信息。
 * @param index 分组配置信息数组索引值，取值范围为大于等于0。超出当前数组长度时，数组自动扩展至index + 1。
 * @param marginTop {@link FlowItem}上外边距。单位：vp。
 * @param marginRight {@link FlowItem}右外边距。单位：vp。
 * @param marginBottom {@link FlowItem}下外边距。单位：vp。
 * @param marginLeft {@link FlowItem}左外边距。单位：vp。
 * @since 12
 */
void OH_ArkUI_WaterFlowSectionOption_SetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index, float marginTop,
    float marginRight, float marginBottom, float marginLeft);

/**
 * @brief 通过{@link FlowItem}分组配置信息获取对应索引下的分组的外边距。
 *
 * @param option {@link FlowItem}分组配置信息。
 * @param index 分组配置信息数组索引值，取值范围为0至数组长度减1。
 * @return 外边距。单位：vp。
 * @since 12
 */
ArkUI_Margin OH_ArkUI_WaterFlowSectionOption_GetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_WATER_FLOW_WATER_FLOW_H

/** @} */