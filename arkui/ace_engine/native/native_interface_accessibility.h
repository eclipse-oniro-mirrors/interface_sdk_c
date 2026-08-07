/**
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
 * @addtogroup ArkUI_Accessibility
 * @{
 *
 * @brief Describes the native capabilities supported by ArkUI Accessibility, such as querying accessibility nodes and
 * reporting accessibility events.
 *
 * @since 13
 */

/**
 * @file native_interface_accessibility.h
 *
 * @brief Declares the APIs for accessing Native Accessibility features.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 13
 */
#ifndef _NATIVE_INTERFACE_ACCESSIBILITY_H
#define _NATIVE_INTERFACE_ACCESSIBILITY_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#endif

#include "common_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Provides accessibility node information for accessibility services and assistive applications (such as screen
 * readers).
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityElementInfo ArkUI_AccessibilityElementInfo;

/**
 * @brief Describes the accessibility event information. After a component completes an action requested by an
 * accessibility service or application, it needs to send a success event to confirm the operation.
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityEventInfo ArkUI_AccessibilityEventInfo;

/**
 * @brief Defines a third-party operation provider to implement callback functions.
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityProvider ArkUI_AccessibilityProvider;

/**
 * @brief Sets the arguments of accessibility actions.
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityActionArguments ArkUI_AccessibilityActionArguments;

/**
 * @brief Enumerates accessibility action types.
 *
 * @since 13
 */
typedef enum {
    /**
     * Invalid value.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_INVALID = 0,
    /**
     * Triggers the component's click event handling.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLICK = 0x00000010,
    /**
     * Triggers the component's long-click event handling.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_LONG_CLICK = 0x00000020,
    /**
     * Requests accessibility focus for the component.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_GAIN_ACCESSIBILITY_FOCUS = 0x00000040,
    /**
     * Clears accessibility focus from the component.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CLEAR_ACCESSIBILITY_FOCUS = 0x00000080,
    /**
     * Initiates forward scrolling in scrollable containers.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_FORWARD = 0x00000100,
    /**
     * Initiates backward scrolling in scrollable containers.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SCROLL_BACKWARD = 0x00000200,
    /**
     * Copies the current text selection.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_COPY = 0x00000400,
    /**
     * Pastes content to the text component.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_PASTE = 0x00000800,
    /**
     * Cuts the current text selection to the pasteboard.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_CUT = 0x00001000,
    /**
     * Selects a range of text within an editable area in a text component. Selects a range of text within an editable
     * area by using **ArkUI_AccessibilityActionArguments** and setting **selectTextBegin** (indicates the start
     * position of the selection), **selectTextEnd** (indicates the end position of the selection), and **
     * selectTextInForWard** (**true** indicates to select text forward, and **false** indicates to select text
     * backward).
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SELECT_TEXT = 0x00002000,
    /**
     * Sets the text content of the text component.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SET_TEXT = 0x00004000,
    /**
     * Sets the cursor position where the text can be entered for the text component. This API is used together with **
     * ArkUI_AccessibilityActionArguments**.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_SET_CURSOR_POSITION = 0x00100000,
    /**
     * Support action for find next item in focus move operation.
     * @since 15
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_NEXT_HTML_ITEM = 0x02000000,
    /**
     * Support action for find previous item in focus move operation.
     * @since 15
     */
    ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_PREVIOUS_HTML_ITEM = 0x04000000
} ArkUI_Accessibility_ActionType;

/**
 * @brief Enumerates accessibility event types.
 *
 * @since 13
 */
typedef enum {
    /**
     * Invalid value.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_INVALID = 0,
    /**
     * Click event, sent after the UI component responds.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_CLICKED = 0x00000001,
    /**
     * Long-click event, sent after the UI component responds.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_LONG_CLICKED = 0x00000002,
    /**
     * Selection event, sent after the UI component responds.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_SELECTED = 0x00000004,
    /**
     * Text update event, sent when text is updated.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_TEXT_UPDATE = 0x00000010,
    /**
     * Page state update event, sent on page navigation, switching, resizing, or movement.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_PAGE_STATE_UPDATE = 0x00000020,
    /**
     * Page content update event, sent when the page content changes.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_PAGE_CONTENT_UPDATE = 0x00000800,
    /**
     * Scroll event, sent when scrolling occurs on scrollable components.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_SCROLLED = 0x000001000,
    /**
     * Accessibility focus event, sent after the UI component receives focus.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUSED = 0x00008000,
    /**
     * Accessibility focus cleared event, sent after the UI component loses focus.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ACCESSIBILITY_FOCUS_CLEARED = 0x00010000,
    /**
     * Event to actively requests focus for the specified node.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_REQUEST_ACCESSIBILITY_FOCUS = 0x02000000,
    /**
     * Page open event reported by the UI component.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_PAGE_OPEN = 0x20000000,
    /**
     * Page close event reported by the UI component.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_PAGE_CLOSE = 0x08000000,
    /**
     * Announcement event, indicating a request to proactively announce specified content.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_ANNOUNCE_FOR_ACCESSIBILITY = 0x10000000,
    /**
     * Focus update event, used in the focus update scenarios.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_EVENT_TYPE_FOCUS_NODE_UPDATE = 0x10000001
} ArkUI_AccessibilityEventType;

/**
 * @brief Defines an accessibility action.
 *
 * @since 13
 */
typedef struct {
    /**
     * Action type.
     * @since 13
     */
    ArkUI_Accessibility_ActionType actionType;
    /**
     * Action description.
     * @since 13
     */
    const char* description;
} ArkUI_AccessibleAction;

/**
 * @brief Provides the coordinate position where the node is located.
 *
 * @since 13
 */
typedef struct {
    /**
     * X-coordinate of the upper left corner.
     * @since 13
     */
    int32_t leftTopX;
    /**
     * Y-coordinate of the upper left corner.
     * @since 13
     */
    int32_t leftTopY;
    /**
     * X-coordinate of the lower right corner.
     * @since 13
     */
    int32_t rightBottomX;
    /**
     * Y-coordinate of the lower right corner.
     * @since 13
     */
    int32_t rightBottomY;
} ArkUI_AccessibleRect;

/**
 * @brief Sets and obtains the current value, maximum value, and minimum value of a specific component (such as
 * {@link Slider}, {@link Rating}, or {@link Progress}).
 *
 * @since 13
 */
typedef struct {
    /**
     * Minimum value of the component.
     * @since 13
     */
    double min;
    /**
     * Maximum value of the component.
     * @since 13
     */
    double max;
    /**
     * Current value of the component.
     * @since 13
     */
    double current;
} ArkUI_AccessibleRangeInfo;

/**
 * @brief Configures the grid layout attributes of a specific component (such as {@link List}, {@link Flex},
 * {@link Select}, or {@link Swiper}).
 *
 * @since 13
 */
typedef struct {
    /**
     * Number of rows of the component. The value is an integer greater than 0.
     * @since 13
     */
    int32_t rowCount;
    /**
     * Number of columns of the component. The value is an integer greater than 0.
     * @since 13
     */
    int32_t columnCount;
    /**
     * Selection mode. If the value is **0**, only a single row in the grid can be selected. If the value is not 0,
     * multiple rows can be selected.
     * @since 13
     */
    int32_t selectionMode;
} ArkUI_AccessibleGridInfo;

/**
 * @brief Configures the attributes of a specific component (such as {@link List}, {@link Flex}, {@link Select}, or
 * {@link Swiper}).
 *
 * @since 13
 */
typedef struct {
    /**
     * Whether the item is a heading. **true** for heading, **false** for non-heading.
     * @since 13
     */
    bool heading;
    /**
     * Whether the item is selected. **true** for selected, **false** for unselected.
     * @since 13
     */
    bool selected;
    /**
     * Row index of the item. The value is an integer greater than 0.
     * @since 13
     */
    int32_t columnIndex;
    /**
     * Column index of the item. The value is an integer greater than 0.
     * @since 13
     */
    int32_t rowIndex;
    /**
     * Number of rows that the item spans. The value is an integer greater than 0.
     * @since 13
     */
    int32_t columnSpan;
    /**
     * Number of columns that the item spans. The value is an integer greater than 0.
     * @since 13
     */
    int32_t rowSpan;
} ArkUI_AccessibleGridItemInfo;

/**
 * @brief Enumerates accessibility error codes.
 *
 * @since 13
 */
typedef enum {
    /**
     * The operation is successful.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL = 0,
    /**
     * The operation failed.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_RESULT_FAILED = -1,
    /**
     * Invalid parameter.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER = -2,
    /**
     * Insufficient memory.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_RESULT_OUT_OF_MEMORY = -3
} ArkUI_AcessbilityErrorCode;

/**
 * @brief Enumerates accessibility search modes.
 *
 * @since 13
 */
typedef enum {
    /**
     * Searches the current node.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CURRENT = 0,
    /**
     * Searches parent nodes.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_PREDECESSORS = 1 << 0,
    /**
     * Searches sibling nodes.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_SIBLINGS = 1 << 1,
    /**
     * Searches immediate child nodes.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CHILDREN = 1 << 2,
    /**
     * Searches all child nodes.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_RECURSIVE_CHILDREN = 1 << 3
} ArkUI_AccessibilitySearchMode;

/**
 * @brief Enumerates accessibility focus types.
 *
 * @since 13
 */
typedef enum {
    /**
     * Invalid value.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_FOCUS_TYPE_INVALID = -1,
    /**
     * Input focus type.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_FOCUS_TYPE_INPUT = 1 << 0,
    /**
     * Accessibility focus type.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_FOCUS_TYPE_ACCESSIBILITY = 1 << 1
} ArkUI_AccessibilityFocusType;

/**
 * @brief Enumerates accessibility focus movement directions.
 *
 * @since 13
 */
typedef enum {
    /**
     * Invalid value.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_INVALID = 0,
    /**
     * Moves focus up.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_UP = 0x00000001,
    /**
     * Moves focus down.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_DOWN = 0x00000002,
    /**
     * Moves focus left.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_LEFT = 0x00000004,
    /**
     * Moves focus right.
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_RIGHT = 0x00000008,
    /**
     * Moves focus to the next focusable node (relative to the reference node in query).
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_FORWARD = 0x00000010,
    /**
     * Moves focus to the previous focusable node (relative to the reference node in query).
     * @since 13
     */
    ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_BACKWARD = 0x00000020
} ArkUI_AccessibilityFocusMoveDirection;

/**
 * @brief Provides a **List** instance of encapsulated {@link ArkUI_AccessibilityElementInfo}.
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityElementInfoList ArkUI_AccessibilityElementInfoList;

/**
 * @brief Defines callback functions of a third-party operation {@link provider}. The functions that need to be
 * implemented by the third-party platform are registered with the system through
 * {@link OH_ArkUI_AccessibilityProviderRegisterCallback}.
 *
 * @since 13
 */
typedef struct ArkUI_AccessibilityProviderCallbacks {
    /**
     * @brief Finds node information for the specified node. Callback function implemented by the third-party platform
     * and registered with the system.
     *
     * @param elementId Unique ID of the accessibility element.
     * @param mode Accessibility search mode.
     * @param requestId Request ID.
     * @param elementList Accessibility element information list.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     * @since 13
     */
    int32_t (*findAccessibilityNodeInfosById)(int64_t elementId, ArkUI_AccessibilitySearchMode mode,
        int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    /**
     * @brief Finds the nodes that contain specific text content. Callback function implemented by the third-party
     * platform and registered with the system.
     *
     * @param elementId Unique ID of the accessibility element.
     * @param text Accessibility text.
     * @param requestId Request ID.
     * @param elementList Accessibility element information list.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     */
    int32_t (*findAccessibilityNodeInfosByText)(int64_t elementId, const char* text, int32_t requestId,
        ArkUI_AccessibilityElementInfoList* elementList);
    /**
     * @brief Finds the node that has obtained the focus based on the focus type and returns the element information of
     * the node. Callback function implemented by the third-party platform and registered with the system.
     *
     * @param elementId Unique ID of the accessibility element.
     * @param focusType Focus type.
     * @param requestId Request ID.
     * @param elementInfo Accessibility element information.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     */
    int32_t (*findFocusedAccessibilityNode)(int64_t elementId, ArkUI_AccessibilityFocusType focusType,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    /**
     * @brief Called to find the next focusable node based on the reference node mode and search direction.
     *
     * @param elementId Unique ID of the accessibility element.
     * @param direction Search direction.
     * @param requestId Request ID.
     * @param elementInfo Information about the found accessibility element.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     */
    int32_t (*findNextFocusAccessibilityNode)(
        int64_t elementId, ArkUI_AccessibilityFocusMoveDirection direction,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    /**
     * @brief Executes an accessibility action on the specified accessibility node.
     *
     * @param elementId Unique ID of the accessibility element.
     * @param action Action to execute.
     * @param actionArguments Indicates action arguments.
     * @param requestId Request ID.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     */
    int32_t (*executeAccessibilityAction)(int64_t elementId, ArkUI_Accessibility_ActionType action,
        ArkUI_AccessibilityActionArguments *actionArguments, int32_t requestId);
    /**
     * @brief Called to clear the focus state of the current focused node.
     *
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     */
    int32_t (*clearFocusedFocusAccessibilityNode)();
    /**
     * @brief Called to query the current cursor position of the specified node.
     *
     * @param elementId Unique ID of the accessibility element.
     * @param requestId Request ID.
     * @param index Index of the cursor position.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     */
    int32_t (*getAccessibilityNodeCursorPosition)(int64_t elementId, int32_t requestId, int32_t* index);
} ArkUI_AccessibilityProviderCallbacks;

/**
 * @brief Defines a struct for third-party accessibility provider callback functions, which third-party platforms need
 * to implement. These functions are registered with the system side through **
 * OH_ArkUI_AccessibilityProviderRegisterCallback**.
 *
 * @param provider Pointer to an **ArkUI_AccessibilityProvider** instance.
 * @param callbacks Pointer to an **ArkUI_AccessibilityProviderCallbacks** struct that contains the set of callback
 *     functions implemented by the third-party platform.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityProviderRegisterCallback(
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityProviderCallbacks* callbacks);

/**
 * @brief Defines callback functions of a third-party operation provider with instance ID.
 * These callback functions need to be implemented by the third-party platform and registered
 * with the system through {@link OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance}.
 *
 * @since 15
 */
typedef struct ArkUI_AccessibilityProviderCallbacksWithInstance {
    /**
     * @brief Finds node information for the specified node with instance ID.
     *
     * @param instanceId Unique ID of the third-party framework instance.
     * @param elementId Unique ID of the accessibility element.
     * @param mode Accessibility search mode.
     * @param requestId Request ID.
     * @param elementList Accessibility element information list.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     * @since 15
     */
    int32_t (*findAccessibilityNodeInfosById)(const char* instanceId, int64_t elementId,
        ArkUI_AccessibilitySearchMode mode, int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    /**
     * @brief Finds the nodes that contain specific text content with instance ID.
     *
     * @param instanceId Unique ID of the third-party framework instance.
     * @param elementId Unique ID of the accessibility element.
     * @param text Accessibility text.
     * @param requestId Request ID.
     * @param elementList Accessibility element information list.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     */
    int32_t (*findAccessibilityNodeInfosByText)(const char* instanceId, int64_t elementId, const char* text,
        int32_t requestId, ArkUI_AccessibilityElementInfoList* elementList);
    /**
     * @brief Finds the node that has obtained the focus based on the focus type with instance ID.
     *
     * @param instanceId Unique ID of the third-party framework instance.
     * @param elementId Unique ID of the accessibility element.
     * @param focusType Focus type.
     * @param requestId Request ID.
     * @param elementInfo Accessibility element information.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     */
    int32_t (*findFocusedAccessibilityNode)(const char* instanceId, int64_t elementId,
        ArkUI_AccessibilityFocusType focusType, int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    /**
     * @brief Finds the next focusable node based on the reference node with instance ID.
     *
     * @param instanceId Unique ID of the third-party framework instance.
     * @param elementId Unique ID of the accessibility element.
     * @param direction Search direction.
     * @param requestId Request ID.
     * @param elementInfo Information about the found accessibility element.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     */
    int32_t (*findNextFocusAccessibilityNode)(
        const char* instanceId, int64_t elementId, ArkUI_AccessibilityFocusMoveDirection direction,
        int32_t requestId, ArkUI_AccessibilityElementInfo* elementInfo);
    /**
     * @brief Executes an accessibility action on the specified accessibility node with instance ID.
     *
     * @param instanceId Unique ID of the third-party framework instance.
     * @param elementId Unique ID of the accessibility element.
     * @param action Action to execute.
     * @param actionArguments Indicates action arguments.
     * @param requestId Request ID.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     */
    int32_t (*executeAccessibilityAction)(const char* instanceId, int64_t elementId,
        ArkUI_Accessibility_ActionType action, ArkUI_AccessibilityActionArguments *actionArguments, int32_t requestId);
    /**
     * @brief Clears the focus state of the current focused node with instance ID.
     *
     * @param instanceId Unique ID of the third-party framework instance.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_FAILED} if the operation fails.
     */
    int32_t (*clearFocusedFocusAccessibilityNode)(const char* instanceId);
    /**
     * @brief Queries the current cursor position of the specified node with instance ID.
     *
     * @param instanceId Unique ID of the third-party framework instance.
     * @param elementId Unique ID of the accessibility element.
     * @param requestId Request ID.
     * @param index Index of the cursor position.
     * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
     *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
     */
    int32_t (*getAccessibilityNodeCursorPosition)(const char* instanceId, int64_t elementId,
        int32_t requestId, int32_t* index);
} ArkUI_AccessibilityProviderCallbacksWithInstance;

/**
 * @brief Registers callbacks with instance for the accessibility provider.
 *
 * @param instanceId Unique ID of the third-party framework instance.
 * @param provider Pointer to an {@link ArkUI_AccessibilityProvider} instance.
 * @param callbacks Pointer to an {@link ArkUI_AccessibilityProviderCallbacksWithInstance} struct that contains
 *     the set of callback functions implemented by the third-party platform.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_AccessibilityProviderRegisterCallbackWithInstance(const char* instanceId,
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityProviderCallbacksWithInstance* callbacks);

/**
 * @brief Proactively sends an event to notify the accessibility service.
 *
 * @param provider Handle to the third-party platform provider.
 * @param eventInfo Pointer to the accessibility event information.
 * @param callback Indicates the pointer to the callback that is called after the event is sent.
 * @since 13
 */
void OH_ArkUI_SendAccessibilityAsyncEvent(
    ArkUI_AccessibilityProvider* provider, ArkUI_AccessibilityEventInfo* eventInfo,
    void (*callback)(int32_t errorCode));

/**
 * @brief Adds an **ArkUI_AccessibilityElementInfo** member to the specified list and returns the **
 * ArkUI_AccessibilityElementInfo** struct.
 *
 * @param list **ArkUI_AccessibilityElementInfoList** struct to which the newly created **
 *     ArkUI_AccessibilityElementInfo** member is added and then returned to the function caller.
 * @return Pointer to the created **ArkUI_AccessibilityElementInfo** struct; returns **NULL** if creation fails.
 * @since 13
 */
ArkUI_AccessibilityElementInfo* OH_ArkUI_AddAndGetAccessibilityElementInfo(
    ArkUI_AccessibilityElementInfoList* list);

/**
 * @brief Sets the component ID for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to an **ArkUI_AccessibilityElementInfo** object.
 * @param elementId Unique ID of the accessibility element.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetElementId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t elementId);

/**
 * @brief Sets the parent ID for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param parentId Accessibility ID of the element's parent component.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetParentId(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t parentId);

/**
 * @brief Sets the component type for the **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param componentType Pointer to the component type of the element.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetComponentType(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* componentType);

/**
 * @brief Sets the component text content for the **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param contents Pointer to the text content recognized by accessibility services for the element.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetContents(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* contents);

/**
 * @brief Sets the hint text for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param hintText Pointer to the hint text. The default value is **""**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetHintText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hintText);

/**
 * @brief Sets the accessibility text for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param accessibilityText Pointer to the accessibility text. The default value is **""**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityText(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityText);

/**
 * @brief Sets the accessibility description for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param accessibilityDescription Pointer to the accessibility description. The default value is **""**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityDescription(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityDescription);

/**
 * @brief Sets the child node count and IDs for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param childCount Child node count. The default value is **0**.
 * @param childNodeIds Pointer to the array of child node IDs.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetChildNodeIds(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t childCount, int64_t* childNodeIds);

/**
 * @brief Sets the supported operations for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param operationCount Pointer to the number of actions supported by the component.
 * @param operationActions Pointer to the array of actions supported by the component.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetOperationActions(ArkUI_AccessibilityElementInfo* elementInfo,
    int32_t operationCount, ArkUI_AccessibleAction* operationActions);

/**
 * @brief Sets the screen coordinates for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param screenRect Pointer to the screen coordinates.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetScreenRect(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRect* screenRect);

/**
 * @brief Sets whether the **ArkUI_AccessibilityElementInfo** object is checkable.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param checkable Whether the object is checkable. **true**: checkable; **false**: not checkable. The default value is
 *     **false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetCheckable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checkable);

/**
 * @brief Sets whether the **ArkUI_AccessibilityElementInfo** object is checked.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param checked Whether the object is checked. **true**: checked; **false**: unchecked.
 * The default value is **false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetChecked(
    ArkUI_AccessibilityElementInfo* elementInfo, bool checked);

/**
 * @brief Sets whether the **ArkUI_AccessibilityElementInfo** object is focusable.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param focusable Whether the object is focusable. **true**: focusable; **false**: not focusable. The default value is
 *     **false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetFocusable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool focusable);

/**
 * @brief Sets whether the **ArkUI_AccessibilityElementInfo** object is focused.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param isFocused Whether the object is focused. **true**: focused; **false**: not focused. The default value is **
 *     false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isFocused);

/**
 * @brief Sets whether an **ArkUI_AccessibilityElementInfo** object is visible.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param isVisible Whether the element is visible. **true**: visible; **false**: not visible. The default value is **
 *     false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetVisible(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isVisible);

/**
 * @brief Sets whether the element is focused for accessibility purposes for an **ArkUI_AccessibilityElementInfo**
 * object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param accessibilityFocused Accessibility focus state. **true**: Accessibility focus is set. **false**: Accessibility
 *     focus is not set. The default value is **false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityFocused(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityFocused);

/**
 * @brief Sets whether the **ArkUI_AccessibilityElementInfo** object is selected.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param selected Whether the object is selected. **true**: selected; **false**: not selected. The default value is **
 *     false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetSelected(
    ArkUI_AccessibilityElementInfo* elementInfo, bool selected);

/**
 * @brief Sets whether the **ArkUI_AccessibilityElementInfo** object is clickable.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param clickable Whether the object is clickable. **true**: supported; **false**: not supported. The default value is
 *     **false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool clickable);

/**
 * @brief Sets whether the **ArkUI_AccessibilityElementInfo** object supports long-press gestures.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param longClickable Whether long-press gestures are supported. **true**: supported; **false**: not supported. The
 *     default value is **false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetLongClickable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool longClickable);

/**
 * @brief Sets whether the **ArkUI_AccessibilityElementInfo** object is enabled.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param isEnabled Whether the object is enabled. **true**: enabled; **false**: not enabled. The default value is **
 *     false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetEnabled(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isEnabled);

/**
 * @brief Sets whether the **ArkUI_AccessibilityElementInfo** object is a password.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param isPassword Whether the object is a password. **true**: The object is a password. **false**: The object is not
 *     a password. The default value is **false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetIsPassword(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isPassword);

/**
 * @brief Sets whether the **ArkUI_AccessibilityElementInfo** object is scrollable.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param scrollable Whether scrolling is supported. **true**: supported; **false**: not supported. The default value is
 *     **false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetScrollable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool scrollable);

/**
 * @brief Sets whether the **ArkUI_AccessibilityElementInfo** object is editable.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param editable Whether editing is supported. **true**: supported; **false**: not supported. The default value is **
 *     false**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetEditable(
    ArkUI_AccessibilityElementInfo* elementInfo, bool editable);

/**
 * @brief Sets the hint status for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param isHint Whether the object represents a hint. **true** if the object represents a hint, **false** otherwise.
 *     The **hintText** information is obtained only when the object is in the hint state.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetIsHint(
    ArkUI_AccessibilityElementInfo* elementInfo, bool isHint);

/**
 * @brief Sets the range information for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param rangeInfo Pointer to the current value, maximum value, and minimum value of the specific component.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetRangeInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleRangeInfo* rangeInfo);

/**
 * @brief Sets the grid information for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param gridInfo Pointer to the number of rows, number of columns, and selection mode of the specific component.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetGridInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridInfo* gridInfo);

/**
 * @brief Sets a single-item container within a grid container for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param gridItem Pointer to the attribute values for the specific component.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetGridItemInfo(
    ArkUI_AccessibilityElementInfo* elementInfo, ArkUI_AccessibleGridItemInfo* gridItem);

/**
 * @brief Sets the start position of the selected text for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param selectedTextStart Start position of the selected text. Applicable to text components.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetSelectedTextStart(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t selectedTextStart);

/**
 * @brief Sets the end position of the selected text for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param selectedTextEnd End position of the selected text. Applicable to text components.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetSelectedTextEnd(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t selectedTextEnd);

/**
 * @brief Sets the position information of the currently focused component for an **ArkUI_AccessibilityElementInfo**
 * object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param currentItemIndex Position information of the currently focused component.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetCurrentItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t currentItemIndex);

/**
 * @brief Sets the position information of the first element displayed on the current screen for an **
 * ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param startItemIndex Index of the first item displayed on the current screen. Applicable to components such as **
 *     List**, **Select**, **Swiper**, and **Tab_Bar**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetStartItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t startItemIndex);

/**
 * @brief Sets the position information of the last element displayed on the current screen for an **
 * ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param endItemIndex Index of the last item displayed on the current screen.
 * Applicable to components such as **List**, **Select**, **Swiper**, and **Tab_Bar**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetEndItemIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t endItemIndex);

/**
 * @brief Sets the total number of elements of a specific component for an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param itemCount Total count of items of the specific component.
 * Applicable to components such as **List**, **Select**, **Swiper**, and **Tab_Bar**.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetItemCount(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t itemCount);

/**
 * @brief Sets the scrolling pixel offset of the content area relative to the top coordinate of the element for an **
 * ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param offset Scrolling pixel offset of the content area relative to the top coordinate of the element for scrollable
 *     controls, such as {@link List} and {@link Grid}.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityOffset(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t offset);

/**
 * @brief Sets whether the **ArkUI_AccessibilityElementInfo** object should be treated as an accessibility group.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param accessibilityGroup Whether to enable accessibility group behavior for the object. **true**: enable; **false**:
 *     disable.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityGroup(
    ArkUI_AccessibilityElementInfo* elementInfo, bool accessibilityGroup);

/**
 * @brief Sets the accessibility level for the **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param accessibilityLevel Pointer to the accessibility level of the component, which is used to decide whether the
 *     component is recognized by accessibility services.
 *     <br>- **auto**: The system automatically determines the component's importance based on its attributes and
 *     decides whether to allow accessibility services to recognize it.
 *     <br>- **yes**: The component is important and allows recognition by accessibility services.
 *     <br>- **no**: The component is not important and prohibits recognition by accessibility services.
 *     <br>- **no-hide-descendants**: The component and its descendant nodes are not important, and prohibits
 *     recognition of the component and its descendants by accessibility services.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityLevel(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* accessibilityLevel);

/**
 * @brief Sets the z-order of the component for the **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param zIndex Z-order of the component, used to control the position of the component along the z-axis perpendicular
 *     to the screen. This parameter is required for {@link UiTest}.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetZIndex(
    ArkUI_AccessibilityElementInfo* elementInfo, int32_t zIndex);

/**
 * @brief Sets the opacity for the **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param opacity Opacity. The value ranges from 0 to 1, where **1** indicates opaque and **0** indicates completely
 *     transparent. This parameter is required for {@link UiTest}.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetAccessibilityOpacity(
    ArkUI_AccessibilityElementInfo* elementInfo, float opacity);

/**
 * @brief Sets the background color for the **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param backgroundColor Pointer to the background color. The value is in the **#ARGB** format. For example, the value
 *     for non-transparent white is **"#FFFFFFFF"**. This parameter is required for {@link UiTest}.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetBackgroundColor(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundColor);

/**
 * @brief Sets the background image for the **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param backgroundImage Pointer to the background image. This parameter is required for {@link UiTest}.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetBackgroundImage(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* backgroundImage);

/**
 * @brief Sets the blur value for the **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param blur Pointer to the blur value. This parameter is required for {@link UiTest}.
 * @return <ul>
 *         <li>{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.</li>
 *         <li>{@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetBlur(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* blur);

/**
 * @brief Sets the response logic and node blocking rules for the hit test for an **ArkUI_AccessibilityElementInfo**
 * object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @param hitTestBehavior Pointer to the hit test mode. For details about the value range, see {@link HitTestMode}.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetHitTestBehavior(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* hitTestBehavior);

/**
 * @brief Sets the component identifier for the accessibility node information of the **ArkUI_AccessibilityElementInfo**
 * object, which can be used to identify specific components in automated tests.
 *
 * @param elementInfo Pointer to the element information of an accessibility node.
 * @param identifier Pointer to the unique identifier of a component.
 *     <br>Ensure that the component identifier in the reported component tree is unique and the character string
 *     contains a maximum of 1024 characters. If the character string exceeds 1024 characters, it will be truncated.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 24
 */
int32_t OH_ArkUI_AccessibilityElementInfoSetComponentIdentifier(
    ArkUI_AccessibilityElementInfo* elementInfo, const char* identifier);

/**
 * @brief Creates an **ArkUI_AccessibilityElementInfo** object, which must be destroyed with **
 * OH_ArkUI_DestoryAccessibilityElementInfo**.
 *
 * @return Pointer to the **ArkUI_AccessibilityElementInfo** object.
 * @since 13
 * @version 1.0
 */
ArkUI_AccessibilityElementInfo* OH_ArkUI_CreateAccessibilityElementInfo(void);

/**
 * @brief Destroys an **ArkUI_AccessibilityElementInfo** object.
 *
 * @param elementInfo Pointer to the target **ArkUI_AccessibilityElementInfo** object.
 * @since 13
 * @version 1.0
 */
void OH_ArkUI_DestoryAccessibilityElementInfo(ArkUI_AccessibilityElementInfo* elementInfo);

/**
 * @brief Creates an **ArkUI_AccessibilityEventInfo** object, which must be destroyed with **
 * OH_ArkUI_DestoryAccessibilityEventInfo**.
 *
 * @return Pointer to the **ArkUI_AccessibilityEventInfo** object.
 * @since 13
 */
ArkUI_AccessibilityEventInfo* OH_ArkUI_CreateAccessibilityEventInfo(void);

/**
 * @brief Destroys an **ArkUI_AccessibilityEventInfo** object.
 *
 * @param eventInfo Pointer to the **ArkUI_AccessibilityEventInfo** object to destroy.
 * @since 13
 */
void OH_ArkUI_DestoryAccessibilityEventInfo(ArkUI_AccessibilityEventInfo* eventInfo);

/**
 * @brief Sets the event type for an **ArkUI_AccessibilityEventInfo** object.
 *
 * @param eventInfo Pointer to an **ArkUI_AccessibilityEventInfo** object.
 * @param eventType Event type.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityEventSetEventType(
    ArkUI_AccessibilityEventInfo* eventInfo,  ArkUI_AccessibilityEventType eventType);

/**
 * @brief Sets the content for auto-broadcasting for the **ArkUI_AccessibilityEventInfo** object.
 *
 * @param eventInfo Pointer to an **ArkUI_AccessibilityEventInfo** object.
 * @param textAnnouncedForAccessibility Pointer to the content for auto-broadcasting.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityEventSetTextAnnouncedForAccessibility(
    ArkUI_AccessibilityEventInfo* eventInfo,  const char* textAnnouncedForAccessibility);

/**
 * @brief Sets the focus request ID for an **ArkUI_AccessibilityEventInfo** object.
 *
 * @param eventInfo Pointer to an **ArkUI_AccessibilityEventInfo** object.
 * @param requestFocusId Focus request ID.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityEventSetRequestFocusId(
    ArkUI_AccessibilityEventInfo* eventInfo,  int32_t requestFocusId);

/**
 * @brief Sets the element information for an **ArkUI_AccessibilityEventInfo** object.
 *
 * @param eventInfo Pointer to an **ArkUI_AccessibilityEventInfo** object.
 * @param elementInfo Pointer to an **ArkUI_AccessibilityElementInfo** object.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_AccessibilityEventSetElementInfo(
    ArkUI_AccessibilityEventInfo* eventInfo,  ArkUI_AccessibilityElementInfo* elementInfo);

/**
 * @brief Obtains the value associated with a specified key in an **ArkUI_AccessibilityActionArguments** struct.
 *
 * @param arguments Pointer to an **ArkUI_AccessibilityActionArguments** object.
 * @param key Pointer to the key.
 * @param value Pointer to the value.
 * @return {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_SUCCESSFUL} if the operation is successful.
 *         {@link ARKUI_ACCESSIBILITY_NATIVE_RESULT_BAD_PARAMETER} if a parameter error occurs.
 * @since 13
 */
int32_t OH_ArkUI_FindAccessibilityActionArgumentByKey(
    ArkUI_AccessibilityActionArguments* arguments, const char* key, char** value);

/**
 * @brief Obtains the level-2 pointer variable of the pointer to the {@link ArkUI_AccessibilityProvider} object.
 *
 * @param node Pointer to an **ArkUI_NodeHandle** object.
 * @param provider Double pointer to an object of the **ArkUI_AccessibilityProvider** type. **provider** is used to
 *     register an accessibility callback function.
 * @return <ul>
 *         <li>Status code.</li>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         <li><br>Parameter error: 1. The input parameter **node** or **provider** is a null pointer.</li>
 *         <li><br>2. The **ArkUI_NodeHandle** type corresponding to **node** is not **ARKUI_NODE_CUSTOM**.</li>
 *         </ul>
 * @since 23
 */
int32_t OH_ArkUI_NativeModule_GetNativeAccessibilityProvider(
    ArkUI_NodeHandle* node, ArkUI_AccessibilityProvider** provider);
#ifdef __cplusplus
};
#endif
#endif // _NATIVE_INTERFACE_ACCESSIBILITY_H
/** @} */
