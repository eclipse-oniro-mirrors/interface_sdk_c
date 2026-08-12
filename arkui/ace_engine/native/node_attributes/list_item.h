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
 * @brief Enumerates the swipe action states of a {@link ListItem}. The default value is **
 * ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_COLLAPSED**.
 *
 * @since 12
 */
typedef enum {
    /**
     * Collapsed state. When the list item slides in the direction opposite to the main axis, the operation item is
     * hidden.
     */
    ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_COLLAPSED = 0,

    /**
     * Expanded state. When the list item slides in the direction opposite to the main axis, the operation item is
     * displayed.
     */
    ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_EXPANDED,

    /**
     * Actioning state. This state is triggered when the list item enters the long-distance deletion area and is
     * deleted.
     */
    ARKUI_LIST_ITEM_SWIPE_ACTION_STATE_ACTIONING,
} ArkUI_ListItemSwipeActionState;

/**
 * @brief Enumerates the edge effects of the swipe action for the {@link ListItem} component. The default value is **
 * ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_SPRING**.
 *
 * @since 12
 */
typedef enum {
    /**
     * The list item can continue to slide after the sliding distance exceeds the size of the operation item.
     */
    ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_SPRING = 0,

    /**
     * The sliding distance of the list item cannot exceed the size of the operation item.
     */
    ARKUI_LIST_ITEM_SWIPE_EDGE_EFFECT_NONE,
} ArkUI_ListItemSwipeEdgeEffect;

/**
 * @brief Enumerates the directions to expand the swipe action of a {@link ListItem}.
 *
 * @since 21
 */
typedef enum {
    /**
     * When the list direction is vertical, it indicates the left in LTR mode and right in RTL mode. When the list
     * direction is horizontal, it indicates the top.
     */
    ARKUI_LIST_ITEM_SWIPE_ACTION_DIRECTION_START = 0,

    /**
     * When the list direction is vertical, it indicates the right in LTR mode and left in RTL mode. When the list
     * direction is horizontal, it indicates the bottom.
     */
    ARKUI_LIST_ITEM_SWIPE_ACTION_DIRECTION_END = 1,
} ArkUI_ListItemSwipeActionDirection;

/**
 * @brief Creates a **ListItemSwipeActionItem** instance.
 *
 * @return Pointer to the created **ListItemSwipeActionItem** instance. If a null pointer is returned, it indicates a
 * creation failure. The possible cause is that the address space is full.
 * @since 12
 */
ArkUI_ListItemSwipeActionItem* OH_ArkUI_ListItemSwipeActionItem_Create();

/**
 * @brief Disposes of a **ListItemSwipeActionItem** instance.
 *
 * @param item Pointer to the **ListItemSwipeActionItem** instance to dispose of.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_Dispose(ArkUI_ListItemSwipeActionItem* item);

/**
 * @brief Sets the layout content of the **ListItemSwipeActionItem**.
 *
 * @param item Pointer to the **ListItemSwipeActionItem** instance.
 * @param node Layout information.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetContent(ArkUI_ListItemSwipeActionItem* item, ArkUI_NodeHandle node);

/**
 * @brief Sets the threshold for the long-distance sliding deletion distance of the component.
 *
 * @param item Pointer to the **ListItemSwipeActionItem** instance.
 * @param distance Threshold for the long-distance sliding deletion distance of the component.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetActionAreaDistance(ArkUI_ListItemSwipeActionItem* item, float distance);

/**
 * @brief Obtains the threshold for the long-distance sliding deletion distance of the component.
 *
 * @param item Pointer to the **ListItemSwipeActionItem** instance.
 * @return Threshold for the long-distance sliding deletion distance of the component. If **-1.0f** is returned, the
 * operation fails. The possible cause is that the **item** parameter is abnormal, such as a null pointer.
 * @since 12
 */
float OH_ArkUI_ListItemSwipeActionItem_GetActionAreaDistance(ArkUI_ListItemSwipeActionItem* item);

/**
 * @brief Sets the event to be called when a sliding entry enters the deletion area.
 *
 * @param item Pointer to the **ListItemSwipeActionItem** instance.
 * @param callback Callback event.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionArea(ArkUI_ListItemSwipeActionItem* item, void (*callback)());

/**
 * @brief Sets the event triggered when a sliding entry enters the deletion area, with user data.
 *
 * @param item Pointer to the **ListItemSwipeActionItem** instance.
 * @param userData User-defined data.
 * @param callback Callback event.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionAreaWithUserData(
    ArkUI_ListItemSwipeActionItem* item, void* userData, void (*callback)(void* userData));

/**
 * @brief Sets the event to be called when a component enters the long-range deletion area and deletes a
 * {@link ListItem}.
 *
 * @param item Pointer to the **ListItemSwipeActionItem** instance.
 * @param callback Callback event.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnAction(ArkUI_ListItemSwipeActionItem* item, void (*callback)());

/**
 * @brief Sets the event triggered when a component enters the long-range deletion area and deletes a
 * {@link ListItem}, with user data.
 *
 * @param item Pointer to the **ListItemSwipeActionItem** instance.
 * @param userData User-defined data.
 * @param callback Callback event.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnActionWithUserData(
    ArkUI_ListItemSwipeActionItem* item, void* userData, void (*callback)(void* userData));

/**
 * @brief Sets the event to be called when a sliding entry exits the deletion area.
 *
 * @param item Pointer to the **ListItemSwipeActionItem** instance.
 * @param callback Callback event.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionArea(ArkUI_ListItemSwipeActionItem* item, void (*callback)());

/**
 * @brief Sets the event triggered when a sliding entry exits the deletion area, with user data.
 *
 * @param item Pointer to the **ListItemSwipeActionItem** instance.
 * @param userData User-defined data.
 * @param callback Callback event.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionAreaWithUserData(
    ArkUI_ListItemSwipeActionItem* item, void* userData, void (*callback)(void* userData));

/**
 * @brief Sets the event triggered when the sliding state of a {@link ListItem} changes.
 *
 * @param item Pointer to the **ListItemSwipeActionItem** instance.
 * @param callback Callback event.
 *        **swipeActionState** The changed state.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnStateChange(
    ArkUI_ListItemSwipeActionItem* item, void (*callback)(ArkUI_ListItemSwipeActionState swipeActionState));

/**
 * @brief Sets the event triggered when the sliding state of a {@link ListItem} changes, with user data.
 *
 * @param item Pointer to the **ListItemSwipeActionItem** instance.
 * @param userData User-defined data.
 * @param callback Callback event.
 *        **swipeActionState** The changed state.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionItem_SetOnStateChangeWithUserData(ArkUI_ListItemSwipeActionItem* item, void* userData,
    void (*callback)(ArkUI_ListItemSwipeActionState swipeActionState, void* userData));

/**
 * @brief Creates a **ListItemSwipeActionOption** instance.
 *
 * @return Pointer to the created **ListItemSwipeActionOption** instance. If a null pointer is returned, it indicates a
 * creation failure. The possible cause is that the address space is full.
 * @since 12
 */
ArkUI_ListItemSwipeActionOption* OH_ArkUI_ListItemSwipeActionOption_Create();

/**
 * @brief Disposes of a **ListItemSwipeActionOption** instance.
 *
 * @param option Pointer to the **ListItemSwipeActionOption** instance to dispose of.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_Dispose(ArkUI_ListItemSwipeActionOption* option);

/**
 * @brief Sets the layout content on the left (vertical layout) or top (horizontal layout) of the
 * **ListItemSwipeActionItem**.
 *
 * @param option Pointer to the **ListItemSwipeActionOption** instance.
 * @param item Layout information.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetStart(
    ArkUI_ListItemSwipeActionOption* option, ArkUI_ListItemSwipeActionItem* item);

/**
 * @brief Sets the layout content on the right (vertical layout) or bottom (horizontal layout) of the
 * **ListItemSwipeActionItem**.
 *
 * @param option Pointer to the **ListItemSwipeActionOption** instance.
 * @param item Layout information.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetEnd(
    ArkUI_ListItemSwipeActionOption* option, ArkUI_ListItemSwipeActionItem* item);

/**
 * @brief Sets the sliding effect.
 *
 * @param option Pointer to the **ListItemSwipeActionOption** instance.
 * @param edgeEffect Sliding effect.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetEdgeEffect(
    ArkUI_ListItemSwipeActionOption* option, ArkUI_ListItemSwipeEdgeEffect edgeEffect);

/**
 * @brief Obtains the sliding effect.
 *
 * @param option Pointer to the **ListItemSwipeActionOption** instance.
 * @return Sliding effect. The default return value is **0**. If **-1** is returned, the operation fails. The possible
 * cause is that the **option** parameter is abnormal, such as a null pointer.
 * @since 12
 */
int32_t OH_ArkUI_ListItemSwipeActionOption_GetEdgeEffect(ArkUI_ListItemSwipeActionOption* option);

/**
 * @brief Sets the event called when the sliding operation offset changes.
 *
 * @param option Pointer to the **ListItemSwipeActionOption** instance.
 * @param callback Callback event.
 *        **offset** Slide offset.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChange(
    ArkUI_ListItemSwipeActionOption* option, void (*callback)(float offset));

/**
 * @brief Sets the event triggered when the sliding operation offset changes, with user data.
 *
 * @param option Pointer to the **ListItemSwipeActionOption** instance.
 * @param userData User-defined data.
 * @param callback Callback event.
 *        **offset** Slide offset.
 * @since 12
 */
void OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChangeWithUserData(
    ArkUI_ListItemSwipeActionOption* option, void* userData, void (*callback)(float offset, void* userData));

/**
 * @brief Expands the swipe action.
 *
 * @param node List item node.
 * @param direction Direction to expand the swipe action.
 * @return Result code.
 *     <ul>
 *     <li><br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li><br>Returns {@link ARKUI_ERROR_CODE_PARAM_ERROR} if the component type of the node is incorrect.</li>
 *     <li><br>Returns {@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} if the node is not mounted to the component
 *     tree.</li>
 *     </ul>
 * @since 21
 */
int32_t OH_ArkUI_ListItemSwipeAction_Expand(ArkUI_NodeHandle node, ArkUI_ListItemSwipeActionDirection direction);

/**
 * @brief Collapses the swipe action.
 *
 * @param node List item node.
 * @return Result code.
 *     <ul>
 *     <li><br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li><br>Returns {@link ARKUI_ERROR_CODE_PARAM_ERROR} if the component type of the node is incorrect.</li>
 *     <li><br>Returns {@link ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE} if the node is not mounted to the component
 *     tree.</li>
 *     </ul>
 * @since 21
 */
int32_t OH_ArkUI_ListItemSwipeAction_Collapse(ArkUI_NodeHandle node);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_LIST_ITEM_H
/** @} */
