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
 * @addtogroup InputMethod
 * @{
 *
 * @brief InputMethod provides functions to use input methods.
 *
 * @since 12
 */

/**
 * @file inputmethod_controller_capi.h
 *
 * @brief Provides methods for binding and unbinding input methods.
 *
 * @include <inputmethod/inputmethod_controller_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_CONTROLLER_CAPI_H
#define OHOS_INPUTMETHOD_CONTROLLER_CAPI_H
#include <stdint.h>
#include <stdlib.h>

#include "inputmethod_text_editor_proxy_capi.h"
#include "inputmethod_inputmethod_proxy_capi.h"
#include "inputmethod_attach_options_capi.h"
#include "../arkui/drag_and_drop.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief Bind the application to the input method service to establish a bidirectional interaction channel between the
 * application and the input method. This interface must be invoked after TextEditorProxy and AttachOptions are created.
 * After the binding is successful, the application can send requests and notifications to the input method through the
 * returned InputMethodProxy. In addition, the input method can send notifications such as text insertion and deletion
 * to the application through the callback function registered in the TextEditorProxy. <br> <br>Prerequisites:<br>1. The
 * InputMethod_TextEditorProxy instance must be created through OH_TextEditorProxy_Create. The
 * OH_TextEditorProxy_SetXXXFunc function is used to register necessary callbacks(such as InsertTextFunc,
 * DeleteForwardFunc, and GetTextConfigFunc). <br>2. The InputMethod_AttachOptions instance must be created through
 * OH_AttachOptions_Create or OH_AttachOptions_CreateWithRequestKeyboardReason. <br>3. The callback function registered
 * in TextEditorProxy must be correctly implemented. Otherwise, the input method interaction is incomplete. <br> <br>
 * Pairing call: <br>- After calling OH_InputMethodController_Attach, you must call OH_InputMethodController_Detach to
 * unbind it after using it. <br>- If OH_InputMethodController_Detach is not invoked, input method resources may be
 * leaked. <br>- It is recommended that OH_InputMethodController_Detach be called in a timely manner when the
 * application exits or the input method is no longer required in the text box. <br><br>Invoking sequence: <br>1.
 * OH_TextEditorProxy_Create → Create TextEditorProxy <br>2. OH_TextEditorProxy_SetXXXFunc → Register callback function
 * <br>3. OH_AttachOptions_Create → Create AttachOptions <br>4. OH_InputMethodController_Attach → Bind Input Method(
 * return InputMethodProxy) <br>5. OH_InputMethodProxy_ShowKeyboard / NotifyCursorUpdate Use the input method function
 * <br>6. OH_InputMethodController_Detach → Unbind Input Method <br>7. OH_TextEditorProxy_Destroy /
 * OH_AttachOptions_Destroy → Destroy the created object <br> <br>Life cycle management: <br>- textEditorProxy: The
 * invoker manages the life cycle. If the OH_InputMethodController_Attach is successful, the textEditorProxy cannot be
 * released until the next OH_InputMethodController_Attach or OH_InputMethodController_Detach is completed. Otherwise,
 * invalid memory will be accessed during input method callback. <br>- options: The invoker manages the lifecycle. After
 * OH_InputMethodController_Attach is called, options can be destroyed by OH_AttachOptions_Destroy immediately because
 * the OH_InputMethodController_Attach procedure has read the configuration information in options. <br>-
 * inputMethodProxy: The OH_InputMethodController_Attach function allocates memory through dual pointer output
 * parameters. The caller must keep inputMethodProxy valid before OH_InputMethodController_Detach. After
 * OH_InputMethodController_Detach, this pointer cannot be used. <br> <br> Thread-safe: It is not thread-safe. It is
 * recommended that this interface be invoked in the main thread. The Controller and InputMethodProxy operations must be
 * performed in serial mode. Concurrent or callback reentrant C interface session operations are rejected before
 * affecting the current session and IME_ERR_IMCLIENT is returned. This protection does not represent a general
 * thread-safe guarantee for native layer, ArkTS, or server-side operations. <br>When a native session task fails to be
 * admitted or the waiting times out, IME_ERR_IMCLIENT is returned and the task is not executed.
 * @param textEditorProxy [in] Input pointer to the InputMethod_TextEditorProxy instance. <br>**Meaning/Function: *
 *     * serves as the channel carrier for an application to receive input method callback notifications. After the
 *     binding, the input method interacts with the application through the callback function registered in this object.
 *     <br>**Application scenario: * * Before binding an input method, the application needs to create the
 *     TextEditorProxy and register necessary callback functions. <br>**Effect after use: * * If
 *     OH_InputMethodController_Attach is successful, the input method sends a notification to the application through
 *     the callback function in this object. If the operation fails, the object is not affected and can be used.
 *     <br>**Prerequisites: * * It must be created through OH_TextEditorProxy_Create and registered callback through
 *     SetXXXFunc series functions. <br>**NULL pointer processing: * * cannot be NULL. If NULL is input,
 *     IME_ERR_NULL_POINTER is returned. <br>**Life cycle management: * * The caller manages the life cycle. If the
 *     attach is successful, the textEditorProxy cannot be released before the next OH_InputMethodController_Attach or
 *     OH_InputMethodController_Detach is complete. Otherwise, the released memory will be accessed during input method
 *     callback, resulting in undefined behavior. <br>**Responsibility of memory allocation: * * The memory is allocated
 *     by the caller through OH_TextEditorProxy_Create and released by OH_TextEditorProxy_Destroy.
 * @param options [in] Input pointer to the InputMethod_AttachOptions instance. <br>**Meaning/Function: * *
 *     Specifies the behavior configuration when the input method is bound, including whether to display the keyboard
 *     during binding and the reason for requesting the keyboard. <br>**Application scenario: * *Create and configure
 *     AttachOptions before binding to control the keyboard display behavior during binding. <br>**Effect: The **
 *     OH_InputMethodController_Attach function reads the configuration parameters in options to determine the binding
 *     behavior. <br>**Prerequisites: * * must be created through OH_AttachOptions_Create or
 *     OH_AttachOptions_CreateWithRequestKeyboardReason. options must be a valid AttachOptions handle; An unregistered
 *     or invalid value object handle returns IME_ERR_PARAMCHECK. <br>**NULL pointer processing: * * cannot be NULL. If
 *     NULL is input, IME_ERR_NULL_POINTER is returned. <br>**Life cycle management: After **
 *     OH_InputMethodController_Attach is complete, options can be destroyed immediately because configuration
 *     information has been read during binding. You are advised to call OH_AttachOptions_Destroy to release the memory
 *     after OH_InputMethodController_Attach is successful. <br>**Responsibility of memory allocation: * * The memory is
 *     allocated by the caller through the Create function and released by the OH_AttachOptions_Destroy function.
 * @param inputMethodProxy [out] Output double pointer, indicating the pointer to the InputMethod_InputMethodProxy
 *     pointer. <br>**Meaning/Function: * * InputMethodProxy instance returned after OH_InputMethodController_Attach is
 *     successfully received. This instance is an interaction channel for applications to actively send requests and
 *     notifications to the input method. <br>**Application scenario: After ** OH_InputMethodController_Attach is
 *     successful, the caller uses this pointer to obtain InputMethodProxy. This pointer is required when functions such
 *     as ShowKeyboard, HideKeyboard, and NotifyCursorUpdate are invoked. <br>**Effect: * *If
 *     OH_InputMethodController_Attach is successful, *inputMethodProxy is assigned as a valid InputMethodProxy pointer.
 *     If it fails, the value of *inputMethodProxy is uncertain and should not be used. <br>**Dual pointer description:
 *     * * This parameter is a double pointer(Pointer to Pointer). The OH_InputMethodController_Attach function
 *     internally allocates the memory of InputMethodProxy and outputs the memory to the caller through this double
 *     pointer. The caller must provide a valid pointer variable address, which cannot be null. <br>**NULL pointer
 *     processing: ** inputMethodProxy cannot be NULL. If NULL is input, IME_ERR_NULL_POINTER is returned. <br>**Memory
 *     management: **InputMethodProxy memory is allocated by the OH_InputMethodController_Attach function. Its life
 *     cycle is managed by the framework until OH_InputMethodController_Detach is completed. The caller cannot release
 *     this memory. After OH_InputMethodController_Detach, the memory pointed to by inputMethodProxy is released and
 *     cannot be used. <br>**Restriction on related parameters: * * This pointer is valid only when
 *     OH_InputMethodController_Attach returns IME_ERR_OK. After OH_InputMethodController_Detach, this pointer becomes
 *     invalid immediately and cannot be used any more. Otherwise, undefined behavior or crash may occur.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - indicates success. In this case, *inputMethodProxy is valid and can be used for
 *     subsequent interaction. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - Indicates that the parameter is incorrect. Check whether textEditorProxy,
 *     options, and inputMethodProxy are valid pointers. </li>
 *     <li>{@link IME_ERR_IMCLIENT} - Input method client error. The possible cause is that the input method service is
 *     not ready or the connection is abnormal. </li>
 *     <li>{@link IME_ERR_IMMS} - Input method service error. The system input method management service may be
 *     abnormal. </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer. Returns if textEditorProxy, options, or
 *     inputMethodProxy is NULL. </li>
 *     <li>** Error handling suggestion: * * If the return value is not IME_ERR_OK, check the parameter validity and try
 *     again. If IME_ERR_IMCLIENT or IME_ERR_IMMS is returned, the service is abnormal,
 *     It is recommended to try again later. </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodController_Attach(InputMethod_TextEditorProxy *textEditorProxy,
    InputMethod_AttachOptions *options, InputMethod_InputMethodProxy **inputMethodProxy);

/**
 * @brief Bind the application to the IME service and carry the UI context information. Applies to the scenario where an
 * input method needs to be associated with a specific UI page.(for example, in the multi-window scenario, specify the
 * page to which the page is bound.) Different from OH_InputMethodController_Attach, this function accepts an additional
 * ArkUI_ContextHandle parameter, which is used to specify the binding to a specific UI context in multi-window or
 * multi-page scenarios. Enables the input method service to accurately associate with the current active page. <br>
 * <br>Prerequisites:<br>1. The valid ArkUI_ContextHandle must be obtained by creating the UI context of the ArkUI
 * module. <br>2. The InputMethod_TextEditorProxy instance must be created through OH_TextEditorProxy_Create, and
 * necessary callbacks must be registered through OH_TextEditorProxy_SetXXXFunc series functions. <br>3. The
 * InputMethod_AttachOptions instance must be created using OH_AttachOptions_Create or
 * OH_AttachOptions_CreateWithRequestKeyboardReason. <br> <br> Pairing invoking: <br>- After
 * OH_InputMethodController_AttachWithUIContext is called, OH_InputMethodController_Detach must be called to unbind the
 * binding. <br>- If OH_InputMethodController_Detach is not invoked, input method resources may be leaked.
 * <br><br>Invoking sequence:<br>1. Obtain ArkUI_ContextHandle <br>2. OH_TextEditorProxy_Create →, create
 * TextEditorProxy <br>3. OH_TextEditorProxy_SetXXXFunc →, register the callback function <br>4. OH_AttachOptions_Create
 * →, create AttachOptions <br>5. OH_InputMethodController_AttachWithUIContext →, bind the input method(carrying the UI
 * context), and <br>6. OH_InputMethodProxy_ShowKeyboard / NotifyCursorUpdate. Use the input method function <br>7.
 * OH_InputMethodController_Detach → to unbind the input method.<br>8. Destroy the created object.<br> Life cycle
 * management: <br>- context: It is managed by the ArkUI module and must be valid during binding. <br>- textEditorProxy:
 * managed by the invoker. If the OH_InputMethodController_AttachWithUIContext is successful, it cannot be released
 * until the next OH_InputMethodController_AttachWithUIContext or OH_InputMethodController_Detach is complete. <br>-
 * options: The OH_InputMethodController_AttachWithUIContext can be destroyed immediately after it is complete. <br>-
 * inputMethodProxy: It is internally allocated by the AttachWithUIContext function and released after
 * OH_InputMethodController_Detach. <br> <br>Application scenario: This application scenario is applicable to
 * multi-window or multi-page application scenarios where the input method needs to be bound to a specific UI page. When
 * an application has multiple UI contexts(for example, multiple windows), this function ensures that the input method
 * is associated with the correct page and prevents the input method event from being sent to the wrong window. <br>
 * <br> Thread-safe: It is not thread-safe. It is recommended that this interface be invoked in the main thread.
 * <br>When a native session task fails to be admitted or the waiting times out, IME_ERR_IMCLIENT is returned and the
 * task is not executed.
 * @param context [in] Input pointer to the [ArkUI_Context](../apis-arkui/capi-arkui-nativemodule-arkui-context.md)
 *     instance. <br>**Meaning/Function: * * Specifies the UI context(page or window) to which the input method is bound
 *     so that the input method service can accurately associate with the current active page. <br>**Application
 *     scenario: * *In a multi-window or multi-page application, the input method needs to be bound to a specific UI
 *     context. <br>**Effect after use: * * Input method events are sent to the page associated with this context.
 *     <br>**Prerequisites: * * A valid ArkUI_ContextHandle must be obtained through the ArkUI module. <br>**NULL
 *     pointer processing: * * cannot be NULL. If NULL is input, IME_ERR_NULL_POINTER is returned. <br>**Life cycle
 *     management: * * The ArkUI_Context must be valid during binding. The corresponding UI context cannot be destroyed
 *     before OH_InputMethodController_Detach.
 * @param textEditorProxy [in] Input pointer to the InputMethod_TextEditorProxy instance. <br>**Meaning/Function: *
 *     * is the same as the textEditorProxy parameter in OH_InputMethodController_Attach. It is the channel carrier for
 *     applications to receive input method callback notifications. The application scenario, prerequisites, NULL
 *     pointer processing, and life cycle management are the same as those of the textEditorProxy parameter in
 *     OH_InputMethodController_Attach.
 * @param options [in] Input pointer to the InputMethod_AttachOptions instance. Meaning/Function: This parameter is
 *     the same as the options parameter in OH_InputMethodController_Attach. It specifies the behavior configuration
 *     during binding. The application scenario, prerequisites, NULL pointer processing, and life cycle management are
 *     the same as those of the options parameter in OH_InputMethodController_Attach. options must be a valid
 *     AttachOptions handle; An unregistered or invalid value object handle returns IME_ERR_PARAMCHECK.
 * @param inputMethodProxy [out] Output double pointer, indicating the pointer to the InputMethod_InputMethodProxy
 *     pointer. The meaning/function, application scenario, dual pointer description, NULL pointer processing, memory
 *     management, and related parameter restrictions are the same as those of inputMethodProxy in
 *     OH_InputMethodController_Attach.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - indicates success. In this case, *inputMethodProxy is valid and can be used for
 *     subsequent interaction. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - Indicates that the parameter is incorrect. Check whether context,
 *     textEditorProxy, options, and inputMethodProxy are valid.
 *     needle.</li>
 *     <li>{@link IME_ERR_IMCLIENT} - Input method client error. </li>
 *     <li>{@link IME_ERR_IMMS} - Input method service error. </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer. This parameter is returned when context,
 *     textEditorProxy, options, or inputMethodProxy is null.
 *     Back.</li>
 *     <li>** Error handling suggestion: * * If the return value is not IME_ERR_OK, check the parameter validity and try
 *     again. If IME_ERR_IMCLIENT or IME_ERR_IMMS is returned, the service is abnormal,
 *     It is recommended to try again later. </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 23
 */
InputMethod_ErrorCode OH_InputMethodController_AttachWithUIContext(ArkUI_ContextHandle context,
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_AttachOptions *options,
    InputMethod_InputMethodProxy **inputMethodProxy);

/**
 * @brief Unbinds an application from the input method service.
 *
 * @param inputMethodProxy Pointer to the {@link InputMethod_InputMethodProxy} instance obtained by calling
 *     {@link OH_InputMethodController_Attach}.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_IMCLIENT} - Client error in input method.
 *     <br>{@link IME_ERR_IMMS} - Input method service error.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodController_Detach(InputMethod_InputMethodProxy *inputMethodProxy);

/**
 * @brief Obtains the current input method.
 *
 * @param bundleName [out] This parameter is used as an output parameter and indicates the level-2 pointer that
 *     points to the obtained bundleName character string. The caller needs to use free() to release the call after
 *     using the caller,
 * Avoid memory leakage.
 * @param bundleNameLength [out] Pointer to the length of the obtained bundleName string. This parameter is used as
 *     an output parameter.
 * @param abilityName [out] This parameter is used as an output parameter and indicates the level-2 pointer to the
 *     obtained abilityName character string. The caller needs to use free() to release the call after using the caller,
 * Avoid memory leakage.
 * @param abilityNameLength [out] Pointer to the length of the obtained abilityName character string. This parameter
 *     is used as an output parameter.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - Success.</li>
 *     <li>{@link IME_ERR_IMMS} - Input method management service error.</li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer.</li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}.</li>
 *     </ul>
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_InputMethodController_GetCurrentInputMethod(
    char **bundleName, uint32_t *bundleNameLength, char **abilityName, uint32_t *abilityNameLength);

/**
 * @brief Sends text to the edit box that is currently in focus, bound to the input application, and in editing state.
 *
 * @permission ohos.permission.OPERATE_TEXT_ACROSS_APPLICATION or ohos.permission.CONTROL_DEVICE
 * @param text [in] Pointer to the injected text string. The value must be a NULL-terminated UTF-8 encoded string.
 *     The value cannot be nullptr. At least textLen bytes can be read. The buffer is managed by the caller and must
 *     remain valid at least until the function returns, after which it can be released.
 * @param textLen [in] Length of the injected text string, in bytes. The value range is [0, 512], excluding the end
 *     terminator.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - indicates success. The request is sent successfully. Do not confirm that the editing is
 *     complete. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - Parameter error. The text pointer is null or the textLen is invalid. </li>
 *     <li>{@link OH_INPUTMETHOD_ERR_PERMISSION_DENIED} - Permission verification failed. This error code is returned
 *     when the permission required for text injection is missing. Apply for the permission and try again. </li>
 *     <li>{@link OH_INPUTMETHOD_ERR_DEVICE_NOT_SUPPORTED} - Indicates that the device does not support this function.
 *     </li>
 *     <li>{@link IME_ERR_IMCLIENT} - Indicates that the input method client is incorrect. There may be no valid focus
 *     and bound target, or the target is invalid. </li>
 *     <li>{@link OH_INPUTMETHOD_ERR_EDITABLE} - indicates that the input method is not editable on the client. It may
 *     be a non-editable target client. </li>
 *     <li>{@link IME_ERR_IMMS} - Indicates that the input method service is incorrect. The server may be abnormal.
 *     </li>
 *     </ul>
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethodController_InjectText(const char *text, uint32_t textLen);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_CONTROLLER_CAPI_H