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
 * @brief Declares APIs for focus management, mainly used for actively transferring focus, managing the default focus
 * transfer behavior, and controlling the focus activation state.
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
 * @brief Enumerates the key event processing priority modes.
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
 * @brief Requests focus for a specific node.
 *
 * @param node Node.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE} if the node cannot receive focus.
 *     <br>Returns {@link ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE_ANCESTOR} if the ancestor node cannot receive focus.
 *     <br>Returns {@link ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT} if the node does not exist.
 * @since 15
 */
ArkUI_ErrorCode OH_ArkUI_FocusRequest(ArkUI_NodeHandle node);

/**
 * @brief Clears the focus to the root container node.
 *
 * @param uiContext UI instance object pointer.
 * @since 15
 */
void OH_ArkUI_FocusClear(ArkUI_ContextHandle uiContext);

/**
 * @brief Sets the focus activation state for the current page. When activated, the focused node displays a focus box.
 *
 * @param uiContext UI instance object pointer.
 * @param isActive Whether to enter or exit the focus activation state. The value **true** means to enter the focus
 *     activation state, and **false** means to exit the focus activation state.
 * @param isAutoInactive Whether to automatically exit the focus active state on touch or mouse down events. **true**:
 *     Automatically exit the focus active state. **false**: Maintain the current state until the corresponding setting
 *     API is called.
 * @since 15
 */
void OH_ArkUI_FocusActivate(ArkUI_ContextHandle uiContext, bool isActive, bool isAutoInactive);

/**
 * @brief Configures the focus transfer behavior when pages are switched.
 *
 * @param uiContext UI instance object pointer.
 * @param autoTransfer Whether to automatically transfer focus when pages are switched. The value **true** means to
 *     automatically transfer focus when pages are switched, and **false** means the opposite.
 * @since 15
 */
void OH_ArkUI_FocusSetAutoTransfer(ArkUI_ContextHandle uiContext, bool autoTransfer);


/**
 * @brief Sets the mode for processing key events.
 *
 * @param uiContext UI instance object pointer.
 * @param mode Key event processing priority mode.
 * @since 15
*/
void OH_ArkUI_FocusSetKeyProcessingMode(ArkUI_ContextHandle uiContext, ArkUI_KeyProcessingMode mode);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_INTERFACE_FOCUS_H
/** @} */
