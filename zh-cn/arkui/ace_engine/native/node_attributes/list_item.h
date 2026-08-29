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
 * @brief ArkUI ListItem原生端相关的类型和函数。
 *
 * @since 12
 */

/**
 * @file list_item.h
 *
 * @brief Provides shared list item-related type and function definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_ITEM_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_ITEM_H

#include <stdint.h>

#include "../common_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the configuration information of an item in the **ListItemSwipeActionOption**.
 *
 * @since 12
 */
typedef struct ArkUI_ListItemSwipeActionItem ArkUI_ListItemSwipeActionItem;
/**
 * @brief Defines the configuration information of the **ListItemSwipeActionOption**.
 *
 * @since 12
 */
typedef struct ArkUI_ListItemSwipeActionOption ArkUI_ListItemSwipeActionOption;

/**
 * @brief 定义{@link ListItem}组件{@link swipeAction}方法的列表项滑动状态。侧滑操作在垂直列表中沿水平方向进行，在水平列表中沿垂直方向进行。
 * 默认值为ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_COLLAPSED。
 *
 * @since 12
 */
typedef enum {
    /** 收起状态，操作项处于隐藏状态。 */
    ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_COLLAPSED = 0,

    /** 展开状态，操作项处于显示状态。 */
    ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_EXPANDED,

    /** 长距离状态，表示ListItem进入长距删除区后处于删除操作中的状态。 */
    ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_ACTIONING,
} ArkUI_ListItemSwipeActionState;

/**
 * @brief 定义ListItem组件{@link swipeAction}方法的边缘滑动效果，默认值为ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_SPRING。其中，划出组件是指侧滑操作时展示的操作项内容。
 *
 * @since 12
 */
typedef enum {
/** ListItem滑动距离超过划出组件大小后可以继续滑动。 */
    ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_SPRING = 0,

/** ListItem滑动距离不能超过划出组件大小。 */
    ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_NONE,
} ArkUI_ListItemSwipeEdgeEffect;

/**
 * @brief ListItem划出菜单的展开方向。
 *
 * @since 21
 */
typedef enum {
    /** 当列表方向为垂直时，LTR模式下表示ListItem的左边，RTL模式下表示ListItem的右边。当列表方向为水平时，表示ListItem的上边。 */
    ARKUI_LIST_ITEM_SWIPE_ACTION_DIRECTION_START = 0,

    /** 当列表方向为垂直时，LTR模式下表示ListItem的右边，RTL模式下表示ListItem的左边。当列表方向为水平时，表示ListItem的下边。 */
    ARKUI_LIST_ITEM_SWIPE_ACTION_DIRECTION_END = 1,
} ArkUI_ListItemSwipeActionDirection;

/**
 * @brief 创建ListItem组件swipeAction方法设置的Item配置项。
 *
 * @return 指向已创建的**ListItemSwipeActionItem**实例的指针。如果返回空指针，则表示
 * 创建失败。可能的原因是地址空间已满。
 * @since 12
 */
ArkUI_ListItemSwipeActionItem* OH_ArkUI_ListItemSwipeActionItem_Create();

/**
 * @brief 销毁由OH_ArkUI_ListItemSwipeActionItem_Create创建的ListItemSwipeActionItem实例，使用完毕后需调用本接口释放，避免内存泄漏。
 *
 * @param item 要销毁的ListItemSwipeActionItem实例。
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_Dispose(ArkUI_ListItemSwipeActionItem* item);

/**
 * @brief 设置ListItemSwipeActionItem的布局内容。
 *
 * @param item ListItemSwipeActionItem实例。
 * @param node 侧滑操作项的内容节点。不设置时，侧滑操作项无可显示内容。
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetContent(ArkUI_ListItemSwipeActionItem* item, ArkUI_NodeHandle node);

/**
 * @brief 设置组件长距离滑动删除距离阈值，即列表项侧滑删除的触发距离。当划出组件被完全滑出后继续滑动，且该阈值取值大于0并小于ListItem在滑动方向上的尺寸减去划出组件在滑动方向上的尺寸时，
 * 继续滑动距离超过或等于该阈值后ListItem进入长距删除区。
 *
 * @param item ListItemSwipeActionItem实例。
 * @param distance 组件长距离滑动删除距离阈值，单位vp。默认值为56vp；取值小于等于0或大于等于ListItem在滑动方向上的尺寸减去划出组件在滑动方向上的尺寸时，不会形成长距删除区；
 *     进入长距删除区时会触发OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionArea或OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActi
 *     onAreaWithUserData设置的回调，
 *     退出长距删除区时会触发OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionArea或OH_ArkUI_ListItemSwipeActionItem_SetOnExitAction
 *     AreaWithUserData设置的回调。
 *     建议配合OH_ArkUI_ListItemSwipeActionItem_SetOnAction或OH_ArkUI_ListItemSwipeActionItem_SetOnActionWithUserData回调使用。
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetActionAreaDistance(ArkUI_ListItemSwipeActionItem* item, float distance);

/**
 * @brief 获取组件长距离滑动删除距离阈值。
 *
 * @param item ListItemSwipeActionItem实例。
 * @return 组件长距离滑动删除距离阈值，单位vp。未显式设置时返回默认值56vp，异常时返回值：-1.0f。
 * @since 12
 */
float OH_ArkUI_ListItemSwipeActionItem_GetActionAreaDistance(ArkUI_ListItemSwipeActionItem* item);

/**
 * @brief 设置滑动条目进入长距删除区时调用的事件。仅当长距删除距离阈值有效并形成长距删除区时触发。
 *
 * @param item ListItemSwipeActionItem实例。
 * @param callback Callback event.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionArea(ArkUI_ListItemSwipeActionItem* item, void (*callback)());

/**
 * @brief 设置滑动条目进入长距删除区时调用的事件，回调事件会传入用户自定义数据。仅当长距删除距离阈值有效并形成长距删除区时触发。
 *
 * @param item ListItemSwipeActionItem实例。
 * @param userData 用户自定义数据。
 * @param callback Callback event.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionAreaWithUserData(
    ArkUI_ListItemSwipeActionItem* item, void* userData, void (*callback)(void* userData));

/**
 * @brief 设置滑动条目进入长距删除区后抬手删除{@link ListItem}时调用的事件。仅在删除距离阈值处于有效取值范围（大于0且小于ListItem在滑动方向上的尺寸减去划出组件在滑动方向上的尺寸），
 * 且滑动后松手位置超过或等于该阈值时触发。
 *
 * @param item ListItemSwipeActionItem实例。
 * @param callback Callback event.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnAction(ArkUI_ListItemSwipeActionItem* item, void (*callback)());

/**
 * @brief 设置滑动条目进入长距删除区后抬手删除ListItem时调用的事件，回调事件会传入用户自定义数据。仅在删除距离阈值处于有效取值范围（大于0且小于ListItem在滑动方向上的尺寸减去划出组件在滑动方向上的尺寸），
 * 且滑动后松手位置超过或等于该阈值时触发。
 *
 * @param item ListItemSwipeActionItem实例。
 * @param userData 用户自定义数据。
 * @param callback Callback event.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnActionWithUserData(
    ArkUI_ListItemSwipeActionItem* item, void* userData, void (*callback)(void* userData));

/**
 * @brief 设置滑动条目退出长距删除区时调用的事件。仅当长距删除距离阈值有效并形成长距删除区时触发。
 *
 * @param item ListItemSwipeActionItem实例。
 * @param callback Callback event.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionArea(ArkUI_ListItemSwipeActionItem* item, void (*callback)());

/**
 * @brief 设置滑动条目退出长距删除区时调用的事件，回调事件会传入用户自定义数据。仅当长距删除距离阈值有效并形成长距删除区时触发。
 *
 * @param item ListItemSwipeActionItem实例。
 * @param userData 用户自定义数据。
 * @param callback Callback event.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionAreaWithUserData(
    ArkUI_ListItemSwipeActionItem* item, void* userData, void (*callback)(void* userData));

/**
 * @brief 设置列表项滑动状态变化时触发的事件。列表项滑动状态会在收起、展开和长距离状态之间切换，具体状态见{@link ArkUI_ListItemSwipeActionState}。
 *
 * @param item ListItemSwipeActionItem实例。
 * @param callback Callback event.
 *     **swipeActionState** The changed state.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnStateChange(
    ArkUI_ListItemSwipeActionItem* item, void (*callback)(ArkUI_ListItemSwipeActionState swipeActionState));

/**
 * @brief 设置列表项滑动状态变化时触发的事件，回调事件会传入用户自定义数据。列表项滑动状态会在收起、展开和长距离状态之间切换，具体状态见{@link ArkUI_ListItemSwipeActionState}。
 *
 * @param item ListItemSwipeActionItem实例。
 * @param userData 用户自定义数据。
 * @param callback Callback event.
 *     **swipeActionState** The changed state.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnStateChangeWithUserData(ArkUI_ListItemSwipeActionItem* item, void* userData,
    void (*callback)(ArkUI_ListItemSwipeActionState swipeActionState, void* userData));

/**
 * @brief 创建ListItem组件swipeAction方法设置的配置项。
 *
 * @return ListItemSwipeActionOption配置项实例，用于设置ListItem侧滑操作项在起始侧和结束侧的布局内容、边缘滑动效果及偏移量变化回调。
 * @since 12
 */
ArkUI_ListItemSwipeActionOption* OH_ArkUI_ListItemSwipeActionOption_Create();

/**
 * @brief 销毁由OH_ArkUI_ListItemSwipeActionOption_Create创建的ListItemSwipeActionOption实例，使用完毕后需调用本接口释放，避免内存泄漏。
 *
 * @param option 要销毁的ListItemSwipeActionOption实例。
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_Dispose(ArkUI_ListItemSwipeActionOption* option);

/**
 * @brief 设置ListItemSwipeActionItem的左侧（垂直布局）或上方（横向布局）布局内容，该布局内容可通过OH_ArkUI_ListItemSwipeAction_Expand接口以编程方式展开。
 *
 * @param option ListItemSwipeActionOption实例。
 * @param item 待设置到起始侧的ListItemSwipeActionItem实例。不设置时，ListItem起始侧不展示侧滑操作项。
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetStart(
    ArkUI_ListItemSwipeActionOption* option, ArkUI_ListItemSwipeActionItem* item);

/**
 * @brief 设置ListItemSwipeActionItem的右侧（垂直布局）或下方（横向布局）布局内容，该布局内容可通过OH_ArkUI_ListItemSwipeAction_Expand接口以编程方式展开。
 *
 * @param option ListItemSwipeActionOption实例。
 * @param item 待设置到结束侧的ListItemSwipeActionItem实例。不设置时，ListItem结束侧不展示侧滑操作项。
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetEnd(
    ArkUI_ListItemSwipeActionOption* option, ArkUI_ListItemSwipeActionItem* item);

/**
 * @brief 设置边缘滑动效果。需要允许滑动距离超过划出组件大小时，使用ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_SPRING；需要限制滑动距离不超过划出组件大小时，
 * 使用ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_NONE。
 *
 * @param option ListItemSwipeActionOption实例。
 * @param edgeEffect 边缘滑动效果。
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetEdgeEffect(
    ArkUI_ListItemSwipeActionOption* option, ArkUI_ListItemSwipeEdgeEffect edgeEffect);

/**
 * @brief 获取边缘滑动效果。
 *
 * @param option ListItemSwipeActionOption实例。
 * @return 边缘滑动效果。取值包括{@link ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_SPRING}（0）和
 *     {@link ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_NONE}（1），默认返回值为{@link ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_SPRING}，异常时返回-1。
 * @since 12
 */
int32_t OH_ArkUI_ListItemSwipeActionOption_GetEdgeEffect(ArkUI_ListItemSwipeActionOption* option);

/**
 * @brief 滑动操作偏移量更改时调用的事件。
 *
 * @param option ListItemSwipeActionOption实例。
 * @param callback Callback event.
 *     **offset** Slide offset.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChange(
    ArkUI_ListItemSwipeActionOption* option, void (*callback)(float offset));

/**
 * @brief 滑动操作偏移量更改时调用的事件，回调事件会传入用户自定义数据。
 *
 * @param option ListItemSwipeActionOption实例。
 * @param userData 用户自定义数据。
 * @param callback Callback event.
 *     **offset** Slide offset.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChangeWithUserData(
    ArkUI_ListItemSwipeActionOption* option, void* userData, void (*callback)(float offset, void* userData));

/**
 * @brief 展开指定ListItem的划出菜单（即侧滑操作时展示的操作项区域）。direction为ARKUI_LIST_ITEM_SWIPE_ACTION_DIRECTION_START时，
 * 展开通过OH_ArkUI_ListItemSwipeActionOption_SetStart设置的划出菜单；direction为ARKUI_LIST_ITEM_SWIPE_ACTION_DIRECTION_END时，
 * 展开通过OH_ArkUI_ListItemSwipeActionOption_SetEnd设置的划出菜单。展开后的划出菜单可通过OH_ArkUI_ListItemSwipeAction_Collapse接口收起。
 * 也可在应用响应用户点击"更多"等按钮后调用本接口，以编程方式展开划出菜单。
 *
 * @param node ListItem节点对象。
 * @param direction ListItem划出菜单的展开方向。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_ERROR} 传入的节点对象类型错误，请检查传入的节点是否为ListItem节点。
 *     <br>{@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} 传入的节点未挂载到组件树上，请先将节点挂载到组件树上再执行该操作。
 * @since 21
 */
int32_t OH_ArkUI_ListItemSwipeAction_Expand(ArkUI_NodeHandle node, ArkUI_ListItemSwipeActionDirection direction);

/**
 * @brief 收起由OH_ArkUI_ListItemSwipeAction_Expand展开的指定ListItem的划出菜单（即侧滑操作时展示的操作项区域），也可在用户完成划出菜单操作或切换其他列表项时以编程方式调用。
 *
 * @param node ListItem节点对象。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_ERROR} 传入的节点对象类型错误，请检查传入的节点是否为ListItem节点。
 *     <br>{@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} 传入的节点未挂载到组件树上，请先将节点挂载到组件树上再执行该操作。
 * @since 21
 */
int32_t OH_ArkUI_ListItemSwipeAction_Collapse(ArkUI_NodeHandle node);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_ITEM_H
/** @} */
