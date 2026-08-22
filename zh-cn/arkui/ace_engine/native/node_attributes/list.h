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
 * @file list.h
 *
 * @brief 定义List组件相关的枚举和接口。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_LIST_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_LIST_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义List组件子组件的主轴尺寸信息。
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
 * @brief 定义{@link ListItemGroup}组件区域，默认值为ARKUI_LIST_ITEM_GROUP_AREA_OUTSIDE。
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
 * @brief 创建ListChildrenMainSize接口设置的配置项。使用结束后需调用{@link OH_ArkUI_ListChildrenMainSizeOption_Dispose}释放资源。
 *
 * @return ListChildrenMainSize配置项实例。
 * @since 12
 */
ArkUI_ListChildrenMainSize* OH_ArkUI_ListChildrenMainSizeOption_Create();

/**
 * @brief 销毁由{@link OH_ArkUI_ListChildrenMainSizeOption_Create}创建的ListChildrenMainSize实例。销毁后不得继续访问该实例。
 *
 * @param option 要销毁的ListChildrenMainSize实例。
 * @since 12
 */
void OH_ArkUI_ListChildrenMainSizeOption_Dispose(ArkUI_ListChildrenMainSize* option);

/**
 * @brief 设置{@link List}组件列表项在主轴方向的默认尺寸。主轴方向为纵向时表示高度，为横向时表示宽度。
 *
 * @param option ListChildrenMainSize实例。为空指针时返回ARKUI_ERROR_CODE_PARAM_INVALID。
 * @param defaultMainSize 列表项在主轴方向的默认尺寸值，单位为vp，取值范围为大于等于0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_ListChildrenMainSizeOption_SetDefaultMainSize(
    ArkUI_ListChildrenMainSize* option, float defaultMainSize);
/**
 * @brief 获取{@link List}组件的列表项在主轴方向的默认尺寸。主轴方向为纵向时表示高度，为横向时表示宽度。
 *
 * @param option ListChildrenMainSize实例。
 * @return 列表项在主轴方向的默认尺寸值，默认为0，单位为{@link vp}，option为空指针时返回-1。
 * @since 12
 */
float OH_ArkUI_ListChildrenMainSizeOption_GetDefaultMainSize(ArkUI_ListChildrenMainSize* option);

/**
 * @brief 调整{@link List}组件子项主轴尺寸数组的长度。扩大数组时，新增元素的初始值为-1。
 *
 * @param option ListChildrenMainSize实例。为空指针时不执行操作。
 * @param totalSize 目标数组长度，取值范围为大于0。传入小于等于0的值时不执行操作。
 * @since 12
 */
void OH_ArkUI_ListChildrenMainSizeOption_Resize(ArkUI_ListChildrenMainSize* option, int32_t totalSize);

/**
 * @brief 从指定索引位置开始删除deleteCount个{@link List}组件子项主轴尺寸数组元素，并在该位置插入addCount个初始值为-1的元素。deleteCount超出剩余元素个数时，删除至数组末尾。
 *
 * @param option ListChildrenMainSize实例。为空指针时返回ARKUI_ERROR_CODE_PARAM_INVALID。
 * @param index 操作起始索引位置，取值范围为0至数组当前长度减1。
 * @param deleteCount 从起始位置开始删除的元素数量，取值范围为大于等于0。数量超出剩余元素个数时删除至数组末尾。
 * @param addCount 从起始位置开始新增的元素数量，取值范围为大于等于0。新增元素的初始值为-1。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_ListChildrenMainSizeOption_Splice(
    ArkUI_ListChildrenMainSize* option, int32_t index, int32_t deleteCount, int32_t addCount);

/**
 * @brief 更新{@link List}组件子项主轴尺寸数组中指定索引位置的尺寸。主轴方向为纵向时表示高度，为横向时表示宽度。
 *
 * @param option ListChildrenMainSize实例。为空指针时返回ARKUI_ERROR_CODE_PARAM_INVALID。
 * @param index 目标元素的数组索引位置，取值范围为0至数组当前长度减1。
 * @param mainSize 要设置的主轴尺寸值，单位为vp，取值范围为大于等于0。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 12
 */
int32_t OH_ArkUI_ListChildrenMainSizeOption_UpdateSize(
    ArkUI_ListChildrenMainSize* option, int32_t index, float mainSize);
/**
 * @brief 获取{@link List}组件子项主轴尺寸数组中指定索引位置的尺寸。主轴方向为纵向时表示高度，为横向时表示宽度。
 *
 * @param option ListChildrenMainSize实例。
 * @param index 目标元素的数组索引位置，取值范围为0至数组当前长度减1。
 * @return 数组指定位置的主轴尺寸值，单位为vp。option为空指针或index超出数组范围时返回-1。
 * @since 12
 */
float OH_ArkUI_ListChildrenMainSizeOption_GetMainSize(ArkUI_ListChildrenMainSize* option, int32_t index);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_LIST_H

/** @} */