/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @brief Provides the layout-related types for the native module.
 *
 * @since 12
 */

/**
 * @file layout.h
 *
 * @brief Defines the layout-related types for the native module.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_LAYOUT_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_LAYOUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief 指定设置在相对容器中子组件的对齐规则。
  *
  * @since 12
  */
typedef struct ArkUI_AlignmentRuleOption ArkUI_AlignmentRuleOption;

/**
  * @brief Guideline参数，用于定义Guideline（RelativeContainer容器内的辅助线）的id、方向和位置。
  *
  * @since 12
  */
typedef struct ArkUI_GuidelineOption ArkUI_GuidelineOption;

/**
  * @brief barrier选项，用于定义barrier的id、方向和生成时所依赖的组件。
  *
  * @since 12
  */
typedef struct ArkUI_BarrierOption ArkUI_BarrierOption;

/**
 * @brief 定义组件的像素取整策略结构体。
 *
 * @since 21
 */
typedef struct ArkUI_PixelRoundPolicy ArkUI_PixelRoundPolicy;

/**
 * @brief 定义布局对齐枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 顶部起始，该值为默认值。 */
    ARKUI_ALIGNMENT_TOP_START = 0,
    /** 顶部居中。 */
    ARKUI_ALIGNMENT_TOP,
    /** 顶部尾端。 */
    ARKUI_ALIGNMENT_TOP_END,
    /** 起始端纵向居中。 */
    ARKUI_ALIGNMENT_START,
    /** 横向和纵向居中。 */
    ARKUI_ALIGNMENT_CENTER,
    /** 尾端纵向居中。 */
    ARKUI_ALIGNMENT_END,
    /** 底部起始端。 */
    ARKUI_ALIGNMENT_BOTTOM_START,
    /** 底部横向居中。 */
    ARKUI_ALIGNMENT_BOTTOM,
    /** 底部尾端。 */
    ARKUI_ALIGNMENT_BOTTOM_END,
} ArkUI_Alignment;

/**
 * @brief 设置子组件在父容器交叉轴的对齐格式枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 使用Flex容器中默认配置，该值为默认值。 */
    ARKUI_ITEM_ALIGNMENT_AUTO = 0,
    /** 元素在Flex容器中，交叉轴方向首部对齐。 */
    ARKUI_ITEM_ALIGNMENT_START,
    /** 元素在Flex容器中，交叉轴方向居中对齐。 */
    ARKUI_ITEM_ALIGNMENT_CENTER,
    /** 元素在Flex容器中，交叉轴方向底部对齐。 */
    ARKUI_ITEM_ALIGNMENT_END,
    /** 元素在Flex容器中，交叉轴方向拉伸填充。 */
    ARKUI_ITEM_ALIGNMENT_STRETCH,
    /** 元素在Flex容器中，交叉轴方向文本基线对齐。 */
    ARKUI_ITEM_ALIGNMENT_BASELINE,
} ArkUI_ItemAlignment;

/**
 * @brief 定义垂直方向对齐方式。
 *
 * @since 12
 */
typedef enum {
    /** 主轴方向首端对齐，该值为默认值。 */
    ARKUI_FLEX_ALIGNMENT_START = 1,
    /** 主轴方向中心对齐。 */
    ARKUI_FLEX_ALIGNMENT_CENTER = 2,
    /** 主轴方向尾部对齐。 */
    ARKUI_FLEX_ALIGNMENT_END = 3,
    /** Flex主轴方向均匀分配弹性元素，相邻元素之间距离相同，第一个元素行首对齐，最后的元素行尾对齐。 */
    ARKUI_FLEX_ALIGNMENT_SPACE_BETWEEN = 6,
    /** Flex主轴方向均匀分配弹性元素，相邻元素之间距离相同，第一个元素到行首的距离是相邻元素间距离的一半。 */
    ARKUI_FLEX_ALIGNMENT_SPACE_AROUND = 7,
    /** Flex主轴方向均匀分配弹性元素，相邻元素之间距离、第一个元素到行首的距离和最后的元素到行尾的距离均相等。 */
    ARKUI_FLEX_ALIGNMENT_SPACE_EVENLY = 8,
} ArkUI_FlexAlignment;

/**
 * @brief 定义Flex容器的主轴方向。
 *
 * @since 12
 */
typedef enum {
    /** 主轴与行方向一致，该值为默认值。 */
    ARKUI_FLEX_DIRECTION_ROW = 0,
    /** 主轴与列方向一致。 */
    ARKUI_FLEX_DIRECTION_COLUMN,
    /** 主轴与行方向相反。 */
    ARKUI_FLEX_DIRECTION_ROW_REVERSE,
    /** 主轴与列方向相反。 */
    ARKUI_FLEX_DIRECTION_COLUMN_REVERSE,
} ArkUI_FlexDirection;

/**
 * @brief 定义Flex行列布局模式。
 *
 * @since 12
 */
typedef enum {
    /** 单行/单列布局，子项不能超出容器，该值为默认值。 */
    ARKUI_FLEX_WRAP_NO_WRAP = 0,
    /** 多行/多列布局，子项允许超出容器。 */
    ARKUI_FLEX_WRAP_WRAP,
    /** 反向多行/多列布局，子项允许超出容器。 */
    ARKUI_FLEX_WRAP_WRAP_REVERSE,
} ArkUI_FlexWrap;


/**
 * @brief 设置容器元素内主轴方向上的布局枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 元素从左到右布局，该值为默认值。 */
    ARKUI_DIRECTION_LTR = 0,
    /** 元素从右到左布局。 */
    ARKUI_DIRECTION_RTL,
    /** 使用系统布局方向。 */
    ARKUI_DIRECTION_AUTO = 3,
} ArkUI_Direction;

/**
 * @brief 定义方向或List组件排列方向枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 竖直方向，或者仅支持竖直方向滚动，该值为默认值。 */
    ARKUI_AXIS_VERTICAL = 0,
    /** 水平方向，或者仅支持水平方向滚动。 */
    ARKUI_AXIS_HORIZONTAL,
} ArkUI_Axis;

/**
 * @brief 定义垂直对齐方式。
 *
 * @since 12
 */
typedef enum {
    /** 顶部对齐。 */
    ARKUI_VERTICAL_ALIGNMENT_TOP = 0,
    /** 居中对齐，默认对齐方式。 */
    ARKUI_VERTICAL_ALIGNMENT_CENTER,
    /** 底部对齐。 */
    ARKUI_VERTICAL_ALIGNMENT_BOTTOM,
} ArkUI_VerticalAlignment;

/**
 * @brief 定义语言方向对齐方式。
 *
 * @since 12
 */
typedef enum {
    /** 按照语言方向起始端对齐。 */
    ARKUI_HORIZONTAL_ALIGNMENT_START = 0,
    /** 居中对齐，默认对齐方式。 */
    ARKUI_HORIZONTAL_ALIGNMENT_CENTER,
    /** 按照语言方向末端对齐。 */
    ARKUI_HORIZONTAL_ALIGNMENT_END,
} ArkUI_HorizontalAlignment;

/**
  * @brief 定义屏障线的方向。
  *
  * @since 12
  */
typedef enum {
    /** 屏障在其所有referencedId的最左侧。 */
    ARKUI_BARRIER_DIRECTION_START = 0,
    /** 屏障在其所有referencedId的最右侧。 */
    ARKUI_BARRIER_DIRECTION_END,
    /** 屏障在其所有referencedId的最上方。 */
    ARKUI_BARRIER_DIRECTION_TOP,
    /** 屏障在其所有referencedId的最下方。 */
    ARKUI_BARRIER_DIRECTION_BOTTOM
} ArkUI_BarrierDirection;

/**
  * @brief 定义链的风格。
  *
  * @since 12
  */
typedef enum {
    /** 组件在约束锚点间均匀分布，该值为默认值。 */
    ARKUI_RELATIVE_LAYOUT_CHAIN_STYLE_SPREAD = 0,
    /** 除首尾2个子组件的其他组件在约束锚点间均匀分布。 */
    ARKUI_RELATIVE_LAYOUT_CHAIN_STYLE_SPREAD_INSIDE,
    /** 链内子组件无间隙。 */
    ARKUI_RELATIVE_LAYOUT_CHAIN_STYLE_PACKED,
} ArkUI_RelativeLayoutChainStyle;

/**
 * @brief 创建RelativeContainer容器内的辅助线信息。
 *
 * @param size 辅助线数量。
 * @return 辅助线信息。
 * @since 12
 */
ArkUI_GuidelineOption* OH_ArkUI_GuidelineOption_Create(int32_t size);

/**
 * @brief 销毁辅助线信息。
 *
 * @param guideline 辅助线信息。
 * @since 12
 */
void OH_ArkUI_GuidelineOption_Dispose(ArkUI_GuidelineOption* guideline);

/**
 * @brief 设置辅助线的Id。
 *
 * @param guideline 辅助线信息。
 * @param value id，必须是唯一的并且不可与容器内组件重名。
 * @param index 辅助线索引值。
 * @since 12
 */
void OH_ArkUI_GuidelineOption_SetId(ArkUI_GuidelineOption* guideline, const char* value, int32_t index);

/**
 * @brief 设置辅助线的方向。
 *
 * @param guideline 辅助线信息。
 * @param value 方向。
 * @param index 辅助线索引值。
 * @since 12
 */
void OH_ArkUI_GuidelineOption_SetDirection(ArkUI_GuidelineOption* guideline, ArkUI_Axis value, int32_t index);

/**
 * @brief 设置距离容器左侧或者顶部的距离。
 *
 * @param guideline 辅助线信息。
 * @param value 距离容器左侧或者顶部的距离。
 * @param index 辅助线索引值。
 * @since 12
 */
void OH_ArkUI_GuidelineOption_SetPositionStart(ArkUI_GuidelineOption* guideline, float value, int32_t index);

/**
 * @brief 设置距离容器右侧或者底部的距离。
 *
 * @param guideline 辅助线信息。
 * @param value 距离容器右侧或者底部的距离。
 * @param index 辅助线索引值。
 * @since 12
 */
void OH_ArkUI_GuidelineOption_SetPositionEnd(ArkUI_GuidelineOption* guideline, float value, int32_t index);

/**
 * @brief 获取辅助线的Id。
 *
 * @param guideline 辅助线信息。
 * @param index 辅助线索引值。
 * @return Id。
 * @since 12
 */
const char* OH_ArkUI_GuidelineOption_GetId(ArkUI_GuidelineOption* guideline, int32_t index);

/**
 * @brief 获取辅助线的方向。
 *
 * @param guideline 辅助线信息。
 * @param index 辅助线索引值。
 * @return 方向。
 * @since 12
 */
ArkUI_Axis OH_ArkUI_GuidelineOption_GetDirection(ArkUI_GuidelineOption* guideline, int32_t index);

/**
 * @brief 获取辅助线距离容器左侧或者顶部的距离。
 *
 * @param guideline 辅助线信息。
 * @param index 辅助线索引值。
 * @return 辅助线距离容器左侧或者顶部的距离。单位为vp。
 * @since 12
 */
float OH_ArkUI_GuidelineOption_GetPositionStart(ArkUI_GuidelineOption* guideline, int32_t index);

/**
 * @brief 获取辅助线距离容器右侧或者底部的距离。
 *
 * @param guideline 辅助线信息。
 * @param index 辅助线索引值。
 * @return 辅助线距离容器右侧或者底部的距离。单位为vp。
 * @since 12
 */
float OH_ArkUI_GuidelineOption_GetPositionEnd(ArkUI_GuidelineOption* guideline, int32_t index);

/**
 * @brief 创建RelativeContainer容器内的屏障信息。
 *
 * @param size 屏障数量。
 * @return 屏障信息。
 * @since 12
 */
ArkUI_BarrierOption* OH_ArkUI_BarrierOption_Create(int32_t size);

/**
 * @brief 销毁屏障信息。
 *
 * @param barrierStyle 屏障信息。
 * @since 12
 */
void OH_ArkUI_BarrierOption_Dispose(ArkUI_BarrierOption* barrierStyle);

/**
 * @brief 设置屏障的Id。
 *
 * @param barrierStyle 屏障信息。
 * @param value id，必须是唯一的并且不可与容器内组件重名。
 * @param index 屏障索引值。
 * @since 12
 */
void OH_ArkUI_BarrierOption_SetId(ArkUI_BarrierOption* barrierStyle, const char* value, int32_t index);

/**
 * @brief 设置屏障的方向。
 *
 * @param barrierStyle 屏障信息。
 * @param value 方向。
 * @param index 屏障索引值。
 * @since 12
 */
void OH_ArkUI_BarrierOption_SetDirection(
    ArkUI_BarrierOption* barrierStyle, ArkUI_BarrierDirection value, int32_t index);

/**
 * @brief 设置屏障的依赖的组件。
 *
 * @param barrierStyle 屏障信息。
 * @param value 依赖的组件的Id。
 * @param index 屏障索引值。
 * @since 12
 */
void OH_ArkUI_BarrierOption_SetReferencedId(ArkUI_BarrierOption* barrierStyle, const char* value, int32_t index);

/**
 * @brief 获取屏障的Id。
 *
 * @param barrierStyle 屏障信息。
 * @param index 屏障索引值。
 * @return 屏障的Id。
 * @since 12
 */
const char* OH_ArkUI_BarrierOption_GetId(ArkUI_BarrierOption* barrierStyle, int32_t index);

/**
 * @brief 获取屏障的方向。
 *
 * @param barrierStyle 屏障信息。
 * @param index 屏障索引值。
 * @return 屏障的方向。
 * @since 12
 */
ArkUI_BarrierDirection OH_ArkUI_BarrierOption_GetDirection(ArkUI_BarrierOption* barrierStyle, int32_t index);

/**
 * @brief 获取屏障的依赖的组件。
 *
 * @param barrierStyle 屏障信息。
 * @param index 屏障索引值。
 * @param referencedIndex 依赖的组件Id索引值。
 * @return 屏障的依赖的组件。
 * @since 12
 */
const char* OH_ArkUI_BarrierOption_GetReferencedId(
    ArkUI_BarrierOption* barrierStyle, int32_t index, int32_t referencedIndex);

/**
 * @brief 获取屏障的依赖的组件的个数。
 *
 * @param barrierStyle 屏障信息。
 * @param index 屏障索引值。
 * @return 屏障的依赖的组件的个数。
 * @since 12
 */
int32_t OH_ArkUI_BarrierOption_GetReferencedIdSize(ArkUI_BarrierOption* barrierStyle, int32_t index);

/**
 * @brief 创建相对容器中子组件的对齐规则信息。
 *
 * @return 对齐规则信息。
 * @since 12
 */
ArkUI_AlignmentRuleOption* OH_ArkUI_AlignmentRuleOption_Create();


/**
 * @brief 销毁相对容器中子组件的对齐规则信息。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_Dispose(ArkUI_AlignmentRuleOption* option);

/**
 * @brief 设置相对布局的左对齐方式。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @param id 左对齐锚点的组件的id值。
 * @param alignment 相对于锚点组件的对齐方式。
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetStart(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_HorizontalAlignment alignment);

/**
 * @brief 设置相对布局的右对齐方式。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @param id 右对齐锚点的组件的id值。
 * @param alignment 相对于锚点组件的对齐方式。
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetEnd(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_HorizontalAlignment alignment);

/**
* @brief 设置相对布局的横向居中对齐方式。
*
* @param option 相对容器中子组件的对齐规则信息。
* @param id 横向居中锚点的组件的id值。
* @param alignment 相对于锚点组件的对齐方式。
* @since 12
*/
void OH_ArkUI_AlignmentRuleOption_SetCenterHorizontal(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_HorizontalAlignment alignment);

/**
 * @brief 设置相对布局的顶部对齐方式。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @param id 顶部对齐锚点的组件的id值。
 * @param alignment 相对于锚点组件的对齐方式。
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetTop(ArkUI_AlignmentRuleOption* option, const char* id,
    ArkUI_VerticalAlignment alignment);

/**
 * @brief 设置相对布局的底部对齐方式。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @param id 底部对齐锚点的组件的id值。
 * @param alignment 相对于锚点组件的对齐方式。
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetBottom(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_VerticalAlignment alignment);

/**
* @brief 设置相对布局的纵向居中对齐方式。
*
* @param option 相对容器中子组件的对齐规则信息。
* @param id 纵向居中锚点的组件的id值。
* @param alignment 相对于锚点组件的对齐方式。
* @since 12
*/
void OH_ArkUI_AlignmentRuleOption_SetCenterVertical(
    ArkUI_AlignmentRuleOption* option, const char* id, ArkUI_VerticalAlignment alignment);

/**
 * @brief 设置组件在锚点约束下的水平方向上偏移参数。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @param horizontal 水平方向上的bias值。
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetBiasHorizontal(ArkUI_AlignmentRuleOption* option, float horizontal);

/**
 * @brief 设置组件在锚点约束下的垂直方向上偏移参数。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @param vertical 垂直方向上的bias值。
 * @since 12
 */
void OH_ArkUI_AlignmentRuleOption_SetBiasVertical(ArkUI_AlignmentRuleOption* option, float vertical);

/**
 * @brief 获取左对齐参数的Id。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @return 锚点的组件的id值。
 * @since 12
 */
const char* OH_ArkUI_AlignmentRuleOption_GetStartId(ArkUI_AlignmentRuleOption* option);

/**
* @brief 获取左对齐参数的对齐方式。
*
* @param option 相对容器中子组件的对齐规则信息。
* @return 参数的对齐方式。
* @since 12
*/
ArkUI_HorizontalAlignment OH_ArkUI_AlignmentRuleOption_GetStartAlignment(ArkUI_AlignmentRuleOption* option);

/**
 * @brief 获取右对齐参数。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @return 右对齐参数id。
 * @since 12
 */
const char* OH_ArkUI_AlignmentRuleOption_GetEndId(ArkUI_AlignmentRuleOption* option);

/**
* @brief 获取右对齐参数。
*
* @param option 相对容器中子组件的对齐规则信息。
* @return 右对齐参数的对齐方式。
* @since 12
*/
ArkUI_HorizontalAlignment OH_ArkUI_AlignmentRuleOption_GetEndAlignment(ArkUI_AlignmentRuleOption* option);

/**
* @brief 获取横向居中对齐方式的参数。
*
* @param option 相对容器中子组件的对齐规则信息。
* @return 横向居中对齐方式的参数的id。
* @since 12
*/
const char* OH_ArkUI_AlignmentRuleOption_GetCenterIdHorizontal(ArkUI_AlignmentRuleOption* option);

/**
* @brief 获取横向居中对齐方式的参数。
*
* @param option 相对容器中子组件的对齐规则信息。
* @return 横向居中对齐方式的参数的对齐方式。
* @since 12
*/
ArkUI_HorizontalAlignment OH_ArkUI_AlignmentRuleOption_GetCenterAlignmentHorizontal(ArkUI_AlignmentRuleOption* option);

/**
 * @brief 获取顶部对齐的参数。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @return 顶部对齐的参数id。
 * @since 12
 */
const char* OH_ArkUI_AlignmentRuleOption_GetTopId(ArkUI_AlignmentRuleOption* option);

/**
* @brief 获取顶部对齐的参数。
*
* @param option 相对容器中子组件的对齐规则信息。
* @return 顶部对齐的参数的对齐方式。
* @since 12
*/
ArkUI_VerticalAlignment OH_ArkUI_AlignmentRuleOption_GetTopAlignment(ArkUI_AlignmentRuleOption* option);

/**
 * @brief 获取底部对齐的参数。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @return 底部对齐的参数的id。
 * @since 12
 */
const char* OH_ArkUI_AlignmentRuleOption_GetBottomId(ArkUI_AlignmentRuleOption* option);

/**
* @brief 获取底部对齐的参数。
*
* @param option 相对容器中子组件的对齐规则信息。
* @return 底部对齐的参数的对齐方式。
* @since 12
*/
ArkUI_VerticalAlignment OH_ArkUI_AlignmentRuleOption_GetBottomAlignment(ArkUI_AlignmentRuleOption* option);

/**
* @brief 获取纵向居中对齐方式的参数。
*
* @param option 相对容器中子组件的对齐规则信息。
* @return 纵向居中对齐方式的参数的id。
* @since 12
*/
const char* OH_ArkUI_AlignmentRuleOption_GetCenterIdVertical(ArkUI_AlignmentRuleOption* option);

/**
* @brief 获取纵向居中对齐方式的参数。
*
* @param option 相对容器中子组件的对齐规则信息。
* @return 纵向居中对齐方式的参数的对齐方式。
* @since 12
*/
ArkUI_VerticalAlignment OH_ArkUI_AlignmentRuleOption_GetCenterAlignmentVertical(ArkUI_AlignmentRuleOption* option);

/**
 * @brief 获取水平方向上的bias值。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @return 水平方向上的bias值。
 * @since 12
 */
float OH_ArkUI_AlignmentRuleOption_GetBiasHorizontal(ArkUI_AlignmentRuleOption* option);

/**
 * @brief 获取垂直方向上的bias值。
 *
 * @param option 相对容器中子组件的对齐规则信息。
 * @return 垂直方向上的bias值。
 * @since 12
 */
float OH_ArkUI_AlignmentRuleOption_GetBiasVertical(ArkUI_AlignmentRuleOption* option);

/**
 * @brief 定义扩展安全区域的方向的枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 上方区域，该值为默认值。 */
    ARKUI_SAFE_AREA_EDGE_TOP = 1,
    /** 下方区域。 */
    ARKUI_SAFE_AREA_EDGE_BOTTOM = 1 << 1,
    /** 前部区域。 */
    ARKUI_SAFE_AREA_EDGE_START = 1 << 2,
    /** 尾部区域。 */
    ARKUI_SAFE_AREA_EDGE_END = 1 << 3,
} ArkUI_SafeAreaEdge;

/**
 * @brief 定义扩展安全区域的枚举值。
 *
 * @since 23
 */
typedef enum {
    /** 系统默认非安全区域，包括状态栏、导航栏。 */
    ARKUI_LAYOUT_SAFE_AREA_TYPE_SYSTEM = 1,
} ArkUI_LayoutSafeAreaType;

/**
 * @brief 定义扩展安全区域的方向的枚举值。
 *
 * @since 23
 */
typedef enum {
    /** 上方区域。 */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_TOP = 1,
    /** 下方区域。 */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_BOTTOM = 1 << 1,
    /** 前部区域。 */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_START = 1 << 2,
    /** 尾部区域。 */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_END = 1 << 3,
    /** 垂直区域。 */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_VERTICAL = ARKUI_LAYOUT_SAFE_AREA_EDGE_TOP | ARKUI_LAYOUT_SAFE_AREA_EDGE_BOTTOM,
    /** 水平区域。 */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_HORIZONTAL = ARKUI_LAYOUT_SAFE_AREA_EDGE_START | ARKUI_LAYOUT_SAFE_AREA_EDGE_END,
    /** 全部区域。 */
    ARKUI_LAYOUT_SAFE_AREA_EDGE_ALL = ARKUI_LAYOUT_SAFE_AREA_EDGE_VERTICAL | ARKUI_LAYOUT_SAFE_AREA_EDGE_HORIZONTAL,
} ArkUI_LayoutSafeAreaEdge;

/**
 * @brief 定义Stack容器中子组件的对齐规则。
 *
 * @since 23
 */
typedef enum {
    /** 顶部起始。 */
    ARKUI_LOCALIZED_ALIGNMENT_TOP_START = 0,
    /** 顶部居中。 */
    ARKUI_LOCALIZED_ALIGNMENT_TOP,
    /** 顶部尾端。 */
    ARKUI_LOCALIZED_ALIGNMENT_TOP_END,
    /** 起始端纵向居中。 */
    ARKUI_LOCALIZED_ALIGNMENT_START,
    /** 横向和纵向居中。 */
    ARKUI_LOCALIZED_ALIGNMENT_CENTER,
    /** 尾端纵向居中。 */
    ARKUI_LOCALIZED_ALIGNMENT_END,
    /** 底部起始端。 */
    ARKUI_LOCALIZED_ALIGNMENT_BOTTOM_START,
    /** 底部横向居中。 */
    ARKUI_LOCALIZED_ALIGNMENT_BOTTOM,
    /** 底部尾端。 */
    ARKUI_LOCALIZED_ALIGNMENT_BOTTOM_END,
} ArkUI_LocalizedAlignment;

/**
 * @brief 布局策略枚举。
 *
 * @since 21
 */
typedef enum {
    /** 组件自适应父组件布局。 */
    ARKUI_LAYOUTPOLICY_MATCHPARENT = 0,
    /** 组件自适应子组件（内容），且其大小受父组件内容区大小约束。 */
    ARKUI_LAYOUTPOLICY_WRAPCONTENT,
    /** 组件自适应子组件（内容），且其大小不受父组件内容区大小约束。 */
    ARKUI_LAYOUTPOLICY_FIXATIDEALSIZE,
} ArkUI_LayoutPolicy;

/**
 * @brief 定义像素取整计算策略枚举。
 *
 * @since 21
 */
typedef enum {
    /** 非取整计算。 */
    ARKUI_PIXELROUNDCALCPOLICY_NOFORCEROUND = 0,
    /** 向上取整计算。 */
    ARKUI_PIXELROUNDCALCPOLICY_FORCECEIL,
    /** 向下取整计算。 */
    ARKUI_PIXELROUNDCALCPOLICY_FORCEFLOOR,
} ArkUI_PixelRoundCalcPolicy;

/**
 * @brief 相对容器内容区边界的位置参数。
 *
 * @since 21
 */
typedef struct ArkUI_PositionEdges ArkUI_PositionEdges;

/**
 * @brief 创建PositionEdges属性对象。
 *
 * @return 指向PositionEdges对象的指针。
 * @since 21
 */
ArkUI_PositionEdges* OH_ArkUI_PositionEdges_Create();

/**
 * @brief 深拷贝PositionEdges属性对象。
 *
 * @param edges 指向PositionEdges对象的指针。
 * @return 指向新PositionEdges对象的指针。
 * @since 21
 */
ArkUI_PositionEdges* OH_ArkUI_PositionEdges_Copy(const ArkUI_PositionEdges* edges);

/**
 * @brief 销毁PositionEdges属性对象。
 *
 * @param edges 指向PositionEdges对象的指针。
 * @since 21
 */
void OH_ArkUI_PositionEdges_Dispose(ArkUI_PositionEdges* edges);

/**
 * @brief 设置PositionEdges属性对象的上方向值。
 *
 * @param edges 指向PositionEdges对象的指针。
 * @param value PositionEdges对应方向的值，单位vp。
 * @since 21
 */
void OH_ArkUI_PositionEdges_SetTop(ArkUI_PositionEdges* edges, float value);

/**
 * @brief 获取PositionEdges属性对象的上方向值。
 *
 * @param edges 指向PositionEdges对象的指针。
 * @param value PositionEdges对应方向的值，单位vp。
 * @return 返回错误码。
 *      返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 表示操作成功。
 *      返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 表示参数无效。
 * @since 21
 */
int32_t OH_ArkUI_PositionEdges_GetTop(ArkUI_PositionEdges* edges, float* value);

/**
 * @brief 设置PositionEdges属性对象的左方向值。
 *
 * @param edges 指向PositionEdges对象的指针。
 * @param value PositionEdges对应方向的值，单位vp。
 * @since 21
 */
void OH_ArkUI_PositionEdges_SetLeft(ArkUI_PositionEdges* edges, float value);

/**
 * @brief 获取PositionEdges属性对象的左方向值。
 *
 * @param edges 指向PositionEdges对象的指针。
 * @param value PositionEdges对应方向的值，单位vp。
 * @return 返回错误码。
 *      返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 表示操作成功。
 *      返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 表示参数无效。
 * @since 21
 */
int32_t OH_ArkUI_PositionEdges_GetLeft(ArkUI_PositionEdges* edges, float* value);

/**
 * @brief 设置PositionEdges属性对象的下方向值。
 *
 * @param edges 指向PositionEdges对象的指针。
 * @param value PositionEdges对应方向的值，单位vp。
 * @since 21
 */
void OH_ArkUI_PositionEdges_SetBottom(ArkUI_PositionEdges* edges, float value);

/**
 * @brief 获取PositionEdges属性对象的下方向值。
 *
 * @param edges 指向PositionEdges对象的指针。
 * @param value PositionEdges对应方向的值，单位vp。
 * @return 返回错误码。
 *      返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 表示操作成功。
 *      返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 表示参数无效。
 * @since 21
 */
int32_t OH_ArkUI_PositionEdges_GetBottom(ArkUI_PositionEdges* edges, float* value);

/**
 * @brief 设置PositionEdges属性对象的右方向值。
 *
 * @param edges 指向PositionEdges对象的指针。
 * @param value PositionEdges对应方向的值，单位vp。
 * @since 21
 */
void OH_ArkUI_PositionEdges_SetRight(ArkUI_PositionEdges* edges, float value);

/**
 * @brief 获取PositionEdges属性对象的右方向值。
 *
 * @param edges 指向PositionEdges对象的指针。
 * @param value PositionEdges对应方向的值，单位vp。
 * @return 返回错误码。
 *      返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 表示操作成功。
 *      返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 表示参数无效。
 * @since 21
 */
int32_t OH_ArkUI_PositionEdges_GetRight(ArkUI_PositionEdges* edges, float* value);

/**
 * @brief 创建PixelRoundPolicy属性对象。
 *
 * @return 指向PixelRoundPolicy对象的指针。
 * @since 21
 */
ArkUI_PixelRoundPolicy* OH_ArkUI_PixelRoundPolicy_Create();

/**
 * @brief 释放PixelRoundPolicy属性对象。
 *
 * @param policy 指向要释放的PixelRoundPolicy对象的指针。
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_Dispose(ArkUI_PixelRoundPolicy* policy);

/**
 * @brief 设置PixelRoundPolicy属性对象的上部方向值。
 *
 * @param policy 指向PixelRoundPolicy对象的指针。
 * @param value PixelRoundPolicy对应方向的取整策略。
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_SetTop(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy value);

/**
 * @brief 获取PixelRoundPolicy属性对象的上部方向值。
 *
 * @param policy 指向PixelRoundPolicy对象的指针。
 * @param value PixelRoundPolicy对应方向的取整策略。
 * @return 返回错误码。
 *      返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 表示操作成功。
 *      返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 表示参数无效。
 * @since 21
 */
int32_t OH_ArkUI_PixelRoundPolicy_GetTop(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy* value);

/**
 * @brief 设置PixelRoundPolicy属性对象的前部方向值。
 *
 * @param policy 指向PixelRoundPolicy对象的指针。
 * @param value PixelRoundPolicy对应方向的取整策略。
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_SetStart(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy value);

/**
 * @brief 获取PixelRoundPolicy属性对象的前部方向值。
 *
 * @param policy 指向PixelRoundPolicy对象的指针。
 * @param value PixelRoundPolicy对应方向的取整策略。
 * @return 返回错误码。
 *      返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 表示操作成功。
 *      返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 表示参数无效。
 * @since 21
 */
int32_t OH_ArkUI_PixelRoundPolicy_GetStart(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy* value);

/**
 * @brief 设置PixelRoundPolicy属性对象的下部方向值。
 *
 * @param policy 指向PixelRoundPolicy对象的指针。
 * @param value PixelRoundPolicy对应方向的取整策略。
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_SetBottom(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy value);

/**
 * @brief 获取PixelRoundPolicy属性对象的下部方向值。
 *
 * @param policy 指向PixelRoundPolicy对象的指针。
 * @param value PixelRoundPolicy对应方向的取整策略。
 * @return 返回错误码。
 *      返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 表示操作成功。
 *      返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 表示参数无效。
 * @since 21
 */
int32_t OH_ArkUI_PixelRoundPolicy_GetBottom(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy* value);

/**
 * @brief 设置PixelRoundPolicy属性对象的尾部方向值。
 *
 * @param policy 指向PixelRoundPolicy对象的指针。
 * @param value PixelRoundPolicy对应方向的取整策略。
 * @since 21
 */
void OH_ArkUI_PixelRoundPolicy_SetEnd(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy value);

/**
 * @brief 获取PixelRoundPolicy属性对象的尾部方向值。
 *
 * @param policy 指向PixelRoundPolicy对象的指针。
 * @param value PixelRoundPolicy对应方向的取整策略。
 * @return 返回错误码。
 *      返回 {@link ARKUI_ERROR_CODE_NO_ERROR} 表示操作成功。
 *      返回 {@link ARKUI_ERROR_CODE_PARAM_INVALID} 表示参数无效。
 * @since 21
 */
int32_t OH_ArkUI_PixelRoundPolicy_GetEnd(ArkUI_PixelRoundPolicy* policy, ArkUI_PixelRoundCalcPolicy* value);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_LAYOUT_H
/** @} */
