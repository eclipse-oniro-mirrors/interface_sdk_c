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
 * @brief ArkUI ListItem related types and functions on the native side.
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
 * @brief Define the configuration information of the Item within the ListitemSwipeActionOption method.
 *
 * @since 12
 */
typedef struct ArkUI_ListItemSwipeActionItem ArkUI_ListItemSwipeActionItem;

/**
 * @brief Define the configuration information for the ListitemSwipeActionOption method.
 *
 * @since 12
 */
typedef struct ArkUI_ListItemSwipeActionOption ArkUI_ListItemSwipeActionOption;

/**
 * @brief Define the pattern of element arrangement in the main axis direction of the Swiper component.
 *
 * @since 12
 */
typedef enum {
    /** In the folded state, when the ListItem slides in the opposite direction to the main axis,
     * the operation item is hidden.*/
    ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_COLLAPSED = 0,
    /** In the folded state, when the ListItem slides in the opposite direction to the spindle,
     * the operation item is displayed.*/
    ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_EXPANDED,
    /** Long distance state, the state of deleting a ListItem after it enters the long distance deletion area.*/
    ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_ACTIONING,
} ArkUI_ListItemSwipeActionState;

/**
 * @brief Define the explicit and implicit mode of the SwipeAction method for the Listitem component.
 *
 * @since 12
 */
typedef enum {
    /** The ListItem can continue to be scratched after the distance exceeds the size of the scratched component.*/
    ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_SPRING = 0,
    /** The sliding distance of the ListItem cannot exceed the size of the scratched component.*/
    ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_NONE,
} ArkUI_ListItemSwipeEdgeEffect;

/**
 * @brief Define the direction to expand the swipe action.
 *
 * @since 21
 */
typedef enum {
    /**
     * When the List direction is vertical, it indicates the left in LTR mode and right in RTL mode.
     * When the List direction is horizontal, it indicates the top.
     */
    ARKUI_LIST_ITEM_SWIPE_ACTION_DIRECTION_START = 0,
    /**
     * When the List direction is vertical, it indicates the right in LTR mode and left in RTL mode.
     * When the List direction is horizontal, it indicates the bottom.
     */
    ARKUI_LIST_ITEM_SWIPE_ACTION_DIRECTION_END = 1,
} ArkUI_ListItemSwipeActionDirection;

/**
 * @brief Create a configuration item for the ListitemSwipeActionItem interface settings.
 *
 * @return List Item SwipeActionItem configuration item instance. If the object returns a null pointer,
 *         it indicates creation failure, and the reason for the failure may be that the address space is full.
 * @since 12
 */
ArkUI_ListItemSwipeActionItem* OH_ArkUI_ListItemSwipeActionItem_Create();

/**
 * @brief Destroy the ListitemSwipeActionItem instance.
 *
 * @param item List Item SwipeActionItem instance to be destroyed.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_Dispose(ArkUI_ListItemSwipeActionItem* item);

/**
 * @brief Set the layout content of ListItem SwipeActionItem.
 *
 * @param item List Item SwipeActionItem instance.
 * @param node Layout information.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetContent(ArkUI_ListItemSwipeActionItem* item, ArkUI_NodeHandle node);

/**
 * @brief Set the threshold for long-distance sliding deletion distance of components.
 *
 * @param item List Item SwipeActionItem instance.
 * @param distance Component long-distance sliding deletion distance threshold.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetActionAreaDistance(ArkUI_ListItemSwipeActionItem* item, float distance);

/**
 * @brief Obtain the threshold for long-distance sliding deletion distance of components.
 *
 * @param item List Item SwipeActionItem instance.
 * @return Component long-distance sliding deletion distance threshold. If -1.0f is returned, the return fails.
 *         The possible cause of the failure is that the item parameter is abnormal, such as a null pointer.
 * @since 12
 */
float OH_ArkUI_ListItemSwipeActionItem_GetActionAreaDistance(ArkUI_ListItemSwipeActionItem* item);

/**
 * @brief Set the event to be called when a sliding entry enters the deletion area.
 *
 * @param item List Item SwipeActionItem instance.
 * @param callback Callback Events.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionArea(ArkUI_ListItemSwipeActionItem* item, void (*callback)());

/**
 * @brief Set the event triggered when a sliding entry enters the deletion area.
 *
 * @param item List Item SwipeActionItem instance.
 * @param userData User defined data.
 * @param callback Callback Events.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionAreaWithUserData(
    ArkUI_ListItemSwipeActionItem* item, void* userData, void (*callback)(void* userData));

/**
 * @brief Set the event to be called when a component enters the long-range deletion area and deletes a ListItem.
 *
 * @param item List Item SwipeActionItem instance.
 * @param callback Callback Events.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnAction(ArkUI_ListItemSwipeActionItem* item, void (*callback)());

/**
 * @brief Set the event triggered when a component enters the long-range deletion area and deletes a ListItem.
 *
 * @param item List Item SwipeActionItem instance.
 * @param userData User defined data.
 * @param callback Callback Events.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnActionWithUserData(
    ArkUI_ListItemSwipeActionItem* item, void* userData, void (*callback)(void* userData));

/**
 * @brief Set the event to be called when a sliding entry exits the deletion area.
 *
 * @param item List Item SwipeActionItem instance.
 * @param callback Callback Events.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionArea(ArkUI_ListItemSwipeActionItem* item, void (*callback)());

/**
 * @brief Set the event triggered when a sliding entry exits the deletion area.
 *
 * @param item List Item SwipeActionItem instance.
 * @param userData User defined data.
 * @param callback Callback Events.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionAreaWithUserData(
    ArkUI_ListItemSwipeActionItem* item, void* userData, void (*callback)(void* userData));

/**
 * @brief Set the event triggered when the sliding state of a list item changes.
 *
 * @param item List Item SwipeActionItem instance.
 * @param callback Callback Events.
 *        swipeActionState The changed state.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnStateChange(
    ArkUI_ListItemSwipeActionItem* item, void (*callback)(ArkUI_ListItemSwipeActionState swipeActionState));

/**
 * @brief Set the event triggered when the sliding state of a list item changes.
 *
 * @param item List Item SwipeActionItem instance.
 * @param userData User defined data.
 * @param callback Callback Events.
 *        swipeActionState The changed state.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnStateChangeWithUserData(ArkUI_ListItemSwipeActionItem* item, void* userData,
    void (*callback)(ArkUI_ListItemSwipeActionState swipeActionState, void* userData));

/**
 * @brief Create a configuration item for the ListitemSwipeActionOption interface settings.
 *
 * @return List Item SwipeActionOption configuration item instance.If the object returns a null pointer,
 *         it indicates a creation failure, and the reason for the failure may be that the address space is full.
 * @since 12
 */
ArkUI_ListItemSwipeActionOption* OH_ArkUI_ListItemSwipeActionOption_Create();

/**
 * @brief Destroy the ListitemSwipeActionOption instance.
 *
 * @param option List Item SwipeActionOption instance to be destroyed.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_Dispose(ArkUI_ListItemSwipeActionOption* option);

/**
 * @brief Set the layout content on the left (vertical layout) or top (horizontal layout)
 * of the ListItem SwipeActionItem.
 *
 * @param option List Item SwipeActionItem instance.
 * @param item Layout information.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetStart(
    ArkUI_ListItemSwipeActionOption* option, ArkUI_ListItemSwipeActionItem* item);

/**
 * @brief Set the layout content on the right (vertical layout) or bottom (horizontal layout)
 * of the ListItem SwipeActionItem.
 *
 * @param option List Item SwipeActionItem instance.
 * @param item Layout information.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetEnd(
    ArkUI_ListItemSwipeActionOption* option, ArkUI_ListItemSwipeActionItem* item);

/**
 * @brief Set the sliding effect.
 *
 * @param option List Item SwipeActionItem instance.
 * @param edgeEffect Sliding effect.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetEdgeEffect(
    ArkUI_ListItemSwipeActionOption* option, ArkUI_ListItemSwipeEdgeEffect edgeEffect);

/**
 * @brief Get the sliding effect.
 *
 * @param option List Item SwipeActionItem instance.
 * @return Sliding effect. The default return value is 0. If -1 is returned, the return fails.
 *         The possible cause of the failure is that the option parameter is abnormal, such as a null pointer.
 * @since 12
 */
int32_t OH_ArkUI_ListItemSwipeActionOption_GetEdgeEffect(ArkUI_ListItemSwipeActionOption* option);

/**
 * @brief The event called when the sliding operation offset changes.
 *
 * @param option List Item SwipeActionItem instance.
 * @param callback Callback Events.
 *        offset Slide offset.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChange(
    ArkUI_ListItemSwipeActionOption* option, void (*callback)(float offset));

/**
 * @brief Set the event triggered when the sliding operation offset changes.
 *
 * @param option List Item SwipeActionItem instance.
 * @param userData User defined data.
 * @param callback Callback Events.
 *        offset Slide offset.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChangeWithUserData(
    ArkUI_ListItemSwipeActionOption* option, void* userData, void (*callback)(float offset, void* userData));

/**
 * @brief Expand the swipe action.
 *
 * @param node List Item node.
 * @param direction expand direction of swipeAction.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} success.
 *         {@link ARKUI_ERROR_CODE_PARAM_ERROR} The component type of the node is incorrect.
 *         {@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} The node not mounted to component tree.
 * @since 21
 */
int32_t OH_ArkUI_ListItemSwipeAction_Expand(ArkUI_NodeHandle node, ArkUI_ListItemSwipeActionDirection direction);

/**
 * @brief Collapse the swipe action.
 *
 * @param node List Item node.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} success.
 *         {@link ARKUI_ERROR_CODE_PARAM_ERROR} The component type of the node is incorrect.
 *         {@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} The node not mounted to component tree.
 * @since 21
 */
int32_t OH_ArkUI_ListItemSwipeAction_Collapse(ArkUI_NodeHandle node);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_ITEM_H
/** @} */
