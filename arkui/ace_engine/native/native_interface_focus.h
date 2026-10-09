/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @brief Provides focus capabilities of ArkUI on the native side, such as focus transfer operaions.
 *
 * @since 15
 */

/**
 * @file native_interface_focus.h
 *
 * @brief Declares APIs for focus management, mainly used for actively transferring focus, clearing focus, managing
 * the default focus transfer behavior, controlling the focus activation state, and setting the key event processing
 * mode. It is applicable to scenarios such as page switching and keyboard navigation that require unified management
 * of the focus state and focus transfer behavior, helping improve the predictability of focus control and the
 * interaction experience.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 15
 */

#ifndef ARKUI_NATIVE_INTERFACE_FOCUS_H
#define ARKUI_NATIVE_INTERFACE_FOCUS_H

#include "napi/native_api.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the processing modes of key events.
 *
 * @since 15
 */
typedef enum {
    /**
     * Key events are used for focus navigation.
     */
    ARKUI_KEY_PROCESSING_MODE_FOCUS_NAVIGATION = 0,
    /**
     * Key events are passed up to ancestor components.
     */
    ARKUI_KEY_PROCESSING_MODE_FOCUS_ANCESTOR_EVENT,
} ArkUI_KeyProcessingMode;

/**
 * @brief Requests focus for a specific node. This is applicable when focus needs to be proactively moved to a
 * specified component, for example, setting the default focus after page initialization or navigating focus through
 * a keyboard or remote control. Before calling this API, ensure that the node exists and is focusable, and that its
 * ancestor nodes are also focusable; otherwise, the corresponding error code is returned.
 *
 * @param node Target node for which focus is requested.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the request is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE} if the node cannot gain focus.
 *     <br>Returns {@link ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE_ANCESTOR} if the ancestor node cannot gain focus.
 *     <br>Returns {@link ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT} if the node does not exist.
 * @since 15
 */
ArkUI_ErrorCode OH_ArkUI_FocusRequest(ArkUI_NodeHandle node);

/**
 * @brief Clears the current focus, after which the focus returns to the root container node. This is applicable when
 * exiting the current focus interaction or when the page focus state needs to be reset.
 *
 * @param uiContext Pointer to the UI instance object whose focus needs to be cleared.
 * @since 15
 */
void OH_ArkUI_FocusClear(ArkUI_ContextHandle uiContext);

/**
 * @brief Sets the focus activation state of the current page, so that the focused node displays the focus frame.
 * This is applicable when the focus position needs to be displayed in non-touch interactions such as keyboard and
 * remote control. Default configuration: the focus activation state is disabled by default. Note:
 * **OH_ArkUI_FocusActivate** only controls the focus activation state (that is, the display and hiding of the focus
 * frame) and does not affect the logical ownership of the focus. To actually move the focus to the root container
 * node, use **OH_ArkUI_FocusClear**.
 *
 * @param uiContext Pointer to the UI instance for which the focus active state is to be set.
 * @param isActive Whether to enter or exit the focus activation state. The value **true** means to enter the focus
 *     activation state, and **false** means to exit the focus activation state.
 * @param isAutoInactive Whether to automatically exit the focus active state on touch or mouse down events. This
 *     parameter takes effect only when **isActive** is set to **true**. **true**: Automatically exit the focus active
 *     state. **false**: Maintain the current state until the **OH_ArkUI_FocusActivate** API is called.
 * @since 15
 */
void OH_ArkUI_FocusActivate(ArkUI_ContextHandle uiContext, bool isActive, bool isAutoInactive);

/**
 * @brief Sets whether the focus is automatically transferred when the page is switched.
 *
 * @param uiContext UI instance object pointer.
 * @param autoTransfer Whether to transfer focus when the page is switched. The value **true** means to automatically
 *     transfer focus to the new page when the page is switched, and **false** means not to transfer focus.
 * @since 15
 */
void OH_ArkUI_FocusSetAutoTransfer(ArkUI_ContextHandle uiContext, bool autoTransfer);


/**
 * @brief Sets the processing mode of key events. This is applicable when a priority policy needs to be selected
 * between focus navigation and key event processing of ancestor components. Default configuration: the default key
 * event processing priority is **ARKUI_KEY_PROCESSING_MODE_FOCUS_NAVIGATION**, that is, key events are used to move
 * the focus.
 *
 * @param uiContext Pointer to the UI instance object for which the key event processing mode is to be set.
 * @param mode Key event processing mode. Value selection: **ARKUI_KEY_PROCESSING_MODE_FOCUS_NAVIGATION(0)** is used
 *     for focus navigation, and **ARKUI_KEY_PROCESSING_MODE_FOCUS_ANCESTOR_EVENT(1)** is used for passing key events
 *     upward to the ancestor component.
 * @since 15
*/
void OH_ArkUI_FocusSetKeyProcessingMode(ArkUI_ContextHandle uiContext, ArkUI_KeyProcessingMode mode);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_INTERFACE_FOCUS_H
/** @} */
