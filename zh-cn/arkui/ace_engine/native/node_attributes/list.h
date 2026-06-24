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
 * @brief 定义List的ChildrenMainSize类信息。
 *
 * @since 12
 */
typedef struct ArkUI_ListChildrenMainSize ArkUI_ListChildrenMainSize;
/**
 * @brief 交叉轴方向的布局方式，默认值为ARKUI_LIST_ITEM_ALIGNMENT_START。
 *
 * @since 12
 */
typedef enum {
    /**
     * The {@link list items} are packed toward the start edge of the **List** component along the cross axis.
     */
    ARKUI_LIST_ITEM_ALIGNMENT_START = 0,

    /** ListItem在List中，交叉轴方向居中对齐。*/
    ARKUI_LIST_ITEM_ALIGNMENT_CENTER,

    /** ListItem在List中，交叉轴方向尾部对齐。*/
    ARKUI_LIST_ITEM_ALIGNMENT_END
} ArkUI_ListItemAlignment;

/**
 * @brief 定义列表是否吸顶和吸底枚举值。
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
 * @brief 定义ListItemGroup组件区域，默认值为ARKUI_LIST_ITEM_GROUP_AREA_OUTSIDE。
 *
 * @since 15
 */
typedef enum {
    /** ListItemGroup区域外。 */
    ARKUI_LIST_ITEM_GROUP_AREA_OUTSIDE = 0,

    /**
     * Area without the {@link header}, {@link footer}, and {@link ListItem} in the **ListItemGroup** component.
     */
    ARKUI_LIST_ITEM_SWIPE_AREA_NONE,

    /** ListItemGroup的ListItem区域。 */
    ARKUI_LIST_ITEM_SWIPE_AREA_ITEM,

    /** ListItemGroup的header区域。 */
    ARKUI_LIST_ITEM_SWIPE_AREA_HEADER,

    /** ListItemGroup的footer区域。 */
    ARKUI_LIST_ITEM_SWIPE_AREA_FOOTER,
} ArkUI_ListItemGroupArea;

/**
 * @brief 创建ListChildrenMainSize实例。
 *
 * @return ListChildrenMainSize实例。
 * @since 12
 */
ArkUI_ListChildrenMainSize* OH_ArkUI_ListChildrenMainSizeOption_Create();

/**
 * @brief 销毁ListChildrenMainSize实例。
 *
 * @param option ListChildrenMainSize实例。
 * @since 12
 */
void OH_ArkUI_ListChildrenMainSizeOption_Dispose(ArkUI_ListChildrenMainSize* option);

/**
 * @brief 设置List组件主轴方向上的子组件默认大小。垂直方向表示高度，水平方向表示宽度。
 *
 * @param option ListChildrenMainSize实例。
 * @param defaultMainSize List 组件主轴方向上的子组件默认大小，单位为vp。
 * @return 错误码。
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_ListChildrenMainSizeOption_SetDefaultMainSize(
    ArkUI_ListChildrenMainSize* option, float defaultMainSize);
/**
 * @brief 获取List组件主轴方向上的子组件默认大小。垂直方向表示高度，水平方向表示宽度。
 *
 * @param option ListChildrenMainSize实例。
 * @return List 组件主轴方向上的子组件默认大小。默认值为0。单位为vp。如果option为null，返回-1。
 * @since 12
 */
float OH_ArkUI_ListChildrenMainSizeOption_GetDefaultMainSize(ArkUI_ListChildrenMainSize* option);

/**
 * @brief 调整List组件主轴方向上的子组件大小数组容量。
 *
 * @param option ListChildrenMainSize实例。
 * @param totalSize 目标数组的容量。
 * @since 12
 */
void OH_ArkUI_ListChildrenMainSizeOption_Resize(ArkUI_ListChildrenMainSize* option, int32_t totalSize);

/**
 * @brief 调整List组件主轴方向上的子组件大小数组。
 *
 * @param option ListChildrenMainSize实例。
 * @param index 起始索引。
 * @param deleteCount 从起始位置要删除的元素数量。
 * @param addCount 从起始位置要添加的元素数量。
 * @return 错误码。
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_ListChildrenMainSizeOption_Splice(
    ArkUI_ListChildrenMainSize* option, int32_t index, int32_t deleteCount, int32_t addCount);

/**
 * @brief 更新List组件主轴方向上子组件大小数组中指定索引的值。垂直方向表示高度，水平方向表示宽度。
 *
 * @param option ListChildrenMainSize实例。
 * @param index 目标元素的数组索引。
 * @param mainSize 主轴方向的大小，单位为vp。
 * @return 错误码。
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_ListChildrenMainSizeOption_UpdateSize(
    ArkUI_ListChildrenMainSize* option, int32_t index, float mainSize);
/**
 * @brief 获取List组件主轴方向上子组件大小数组中指定索引的值。垂直方向表示高度，水平方向表示宽度。
 *
 * @param option ListChildrenMainSize实例。
 * @param index 目标元素的数组索引。
 * @return 指定索引的值。如果发生参数错误，返回-1。
 * @since 12
 */
float OH_ArkUI_ListChildrenMainSizeOption_GetMainSize(ArkUI_ListChildrenMainSize* option, int32_t index);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_LIST_H

/** @} */