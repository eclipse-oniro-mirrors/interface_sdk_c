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
 * @brief Provides UI control capabilities of ArkUI on the native side for in-app intelligent
 * agents and UI automation, enabling the injection of control commands into specified UI nodes.
 *
 * @since 26.1.0
 */

/**
 * @file ui_event_injection.h
 *
 * @brief Declares the APIs used by in-app intelligent agents and UI automation to inject control
 * commands into specified UI nodes.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @include <arkui/ui_event_injection.h>
 * @library libace_ndk.z.so
 * @kit ArkUI
 * @since 26.1.0
 */

#ifndef ARKUI_NATIVE_UI_EVENT_INJECTION_H
#define ARKUI_NATIVE_UI_EVENT_INJECTION_H

#include <stdint.h>
#include <stddef.h>

#include "common_type.h"
#include "error_code.h"
#include "ui_json_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the result codes of UI event injection.
 *
 * This enumeration is shared by all injection APIs, including relaxed interaction injection
 * (non-precise) and precise component-targeted injection. A nonzero result code indicates an
 * execution failure, and its specific value conveys the failure reason.
 *
 * @since 26.1.0
 */
typedef enum {
    /**
     * @brief The injected command was executed successfully.
     *
     * @since 26.1.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_EVENT_INJECTION_RESULT_SUCCESS = 0,
    /**
     * @brief No component or target could be found to respond to the injected command.
     *
     * For example, the click coordinates do not hit any component, or the target required by the
     * execution mode cannot be located.
     *
     * @since 26.1.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_EVENT_INJECTION_RESULT_TARGET_NOT_FOUND = 1,
    /**
     * @brief The command cannot be executed in the current UI context.
     *
     * The command is structurally valid, but its type or execution mode is not supported by the
     * current UI state.
     *
     * @since 26.1.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_EVENT_INJECTION_RESULT_COMMAND_NOT_SUPPORTED = 2,
    /**
     * @brief The injected command was interrupted by a user operation.
     *
     * @since 26.1.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_EVENT_INJECTION_RESULT_INTERRUPTED_BY_USER = 3,
} OH_ArkUI_NativeModule_UIEventInjection_ResultCode;

/**
 * @brief Callback for injection completion.
 *
 * Reports the results of command dispatch and immediate component handling, without waiting for
 * deferred effects or rendering. Each accepted request receives exactly one callback on the originating
 * UI thread after the injection function returns. Callbacks on different UI threads are not globally serialized.
 *
 * @param result [in] Result code of the injection execution. For details, see
 *     {@link OH_ArkUI_NativeModule_UIEventInjection_ResultCode}.
 * @param userData [in] Custom user data pointer supplied during injection. NULL if NULL was supplied.
 *        The framework stores only the pointer value for delivery to this callback. It does not
 *        access the pointed-to data, copy or free that data, or take ownership of it. After the
 *        request is accepted, the caller must keep non-NULL data valid until the callback returns.
 * @since 26.1.0
 */
typedef void (*OH_ArkUI_NativeModule_UIEventInjectionCallback)(
    OH_ArkUI_NativeModule_UIEventInjection_ResultCode result, void *userData);

/**
 * @brief Injects a control command into a target UI node asynchronously.
 *
 * This API provides no cancellation operation or fixed completion timeout. Completion depends on
 * UI-thread task processing. A caller-side wait timeout does not cancel an accepted request.
 * Instance destruction does not cancel completion callbacks for accepted requests.
 *
 * @param uiContext [in] Pointer to a UI instance. Must not be NULL. The caller
 *        must be on the UI thread of this instance; a detected thread violation
 *        triggers a fatal abort. The uniqueId must resolve to a node within this instance.
 *        The pointer must remain valid throughout this function call.
 * @param uniqueId [in] Unique ID of the target node. The framework resolves this ID
 *        to the corresponding node within the uiContext instance.
 * @param command [in] Command data. Must not be NULL. The data is carried by an
 *        {@link OH_ArkUI_NativeModule_UIJsonWrapper} object created with
 *        {@link OH_ArkUI_NativeModule_UIJsonWrapperCreate}. The payload's top-level structure is:
 *        {"schemaVersion": 1, "cmd": {"type": "<command type>", "action_info": { ... }}}
 *        For supported command types, action_info field constraints, and examples, see the API development guide.
 *        The JSON data is internally copied before the function returns;
 *        if the caller owns command, it may release it with
 *        {@link OH_ArkUI_NativeModule_UIJsonWrapperDestroy} after this function returns.
 * @param callback [in] Completion callback. Must not be NULL. After the request is accepted,
 *        it must remain callable until it returns, even if the caller's wait times out.
 * @param userData [in] Custom user data pointer passed to the callback. Can be NULL.
 *        The data is managed by the caller. After acceptance, non-NULL data must remain valid
 *        until the callback returns, even if the caller's wait times out.
 * @return A value of 0 means the request was accepted; its execution result is reported by callback.
 *     A nonzero value means the request was rejected without command execution or callback.
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the request is accepted.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if command or callback is NULL,
 *     the command data is invalid, or command submission failed.</li>
 *     <li>{@link ARKUI_ERROR_CODE_NODE_NOT_FOUND} if uniqueId does not resolve to a node within the uiContext
 *     instance.</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if uiContext is NULL, or the
 *     corresponding UI instance is being destroyed or is invalid.</li>
 *     <li>{@link ARKUI_ERROR_CODE_COMMAND_UNFINISHED} if a previous command still restricts
 *     acceptance of subsequent requests in this process. Once a command is accepted, other valid
 *     requests in the same process return this error. The restriction is lifted before the framework
 *     invokes the completion callback. The callback may submit another command subject to the
 *     parameter and UI-thread requirements. Rejected requests may be retried after the restriction
 *     is lifted; acceptance remains subject to other requests in the process.</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIEventInjectCompositeCommand(
    ArkUI_ContextHandle uiContext,
    uint32_t uniqueId,
    const OH_ArkUI_NativeModule_UIJsonWrapper *command,
    OH_ArkUI_NativeModule_UIEventInjectionCallback callback,
    void *userData);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_UI_EVENT_INJECTION_H
/** @} */
