/*
* Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @file inputmethod_inputmethod_proxy_capi.h
 *
 * @brief Provides methods for using the input method, allowing requests and notifications to be sent to the input
 * method application.
 *
 * @include <inputmethod/inputmethod_inputmethod_proxy_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_INPUTMETHOD_PROXY_CAPI_H
#define OHOS_INPUTMETHOD_INPUTMETHOD_PROXY_CAPI_H
#include <stddef.h>

#include "inputmethod_types_capi.h"
#include "inputmethod_attach_options_capi.h"
#include "inputmethod_cursor_info_capi.h"
#include "inputmethod_private_command_capi.h"
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
/**
 * @brief Provides an interaction proxy object between the app and the input method service. The app can call relevant
 * APIs of the input method service and receive event callbacks from the input method service through this object. This
 * struct is an opaque type. Its internal members shall not be accessed directly. Operations can only be performed
 * through the function interfaces provided by this module.
 *
 * @since 12
 */
typedef struct InputMethod_InputMethodProxy InputMethod_InputMethodProxy;

/**
 * @brief Displays the keyboard. After this function is called, the system requests the input method application to
 * display the soft keyboard interface for text input. <br> <br>Application scenario: This function is invoked when an
 * application needs to actively start the keyboard for text input. For example, the keyboard needs to be displayed
 * after the edit box is focused. <br> <br> Effect after use: After the interface is successfully invoked, the soft
 * keyboard interface is displayed. If the interface fails to be invoked, an error code is returned. You need to rectify
 * the fault based on the error code. <br> <br>Prerequisites: You must invoke
 * [OH_InputMethodController_Attach](capi-inputmethod-controller-capi-h. md#oh_inputmethodcontroller_attach) to obtain
 * the inputMethodProxy instance and the instance is in the Attached state. <br> <br>Life cycle management: The
 * inputMethodProxy is created by the
 * [OH_InputMethodController_Attach](capi-inputmethod-controller-capi-h. md#oh_inputmethodcontroller_attach) and cannot
 * be manually destroyed. After [OH_InputMethodController_Detach](capi-inputmethod-controller-capi-h.
 * md#oh_inputmethodcontroller_detach) is called to unbind the inputMethodProxy, the inputMethodProxy becomes invalid.
 * If this function is called again, the error code IME_ERR_DETAACHE is returned. <br><br>Invoking sequence:
 * OH_InputMethodController_Attach → OH_InputMethodProxy_ShowKeyboard → OH_InputMethodProxy_HideKeyboard →
 * OH_InputMethodController_Detach <br> <br> Thread security: This function is not thread-safe. You are not advised to
 * operate the same inputMethodProxy object at the same time in a multi-thread environment. If multiple threads are
 * required, lock the object. The Controller and InputMethodProxy operations must be performed in serial mode.
 * Concurrent or callback reentrant C interface session operations are rejected before affecting the current session and
 * IME_ERR_IMCLIENT is returned. This protection does not represent a general thread-safe guarantee for native layer,
 * ArkTS, or server-side operations.
 * @param inputMethodProxy [in] Input pointer to the {@link InputMethod_InputMethodProxy} instance. The value of
 *     inputMethodProxy is obtained by invoking
 *     [OH_InputMethodController_Attach](capi-inputmethod-controller-capi-h.md#oh_inputmethodcontroller_attach). The
 *     pointer cannot be null. If the pointer is null, the error code IME_ERR_NULL_POINTER is returned. After Detach,
 *     the pointer becomes invalid and cannot be used to invoke any functions related to InputMethodProxy.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - indicates success and the keyboard has requested display. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - inputMethodProxy does not match the current proxy. </li>
 *     <li>{@link IME_ERR_IMCLIENT} - Input method client error, which may be an internal exception of the client. </li>
 *     <li>{@link IME_ERR_IMMS} - Input method service error. The possible cause is that the input method management
 *     service is unavailable. </li>
 *     <li>{@link IME_ERR_DETACHED} - Unbound input method, indicating that Detach has been invoked and can be used only
 *     after re-attaching. </li>
 *     <li>{@link IME_ERR_EDITABLE}: The text box is in the non-editing state. The binding relationship may still be
 *     valid. </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer. The inputMethodProxy is NULL. </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodProxy_ShowKeyboard(InputMethod_InputMethodProxy *inputMethodProxy);
/**
 * @brief Displays the text box.
 *
 * @param inputMethodProxy [in] Input pointer to the {@link InputMethod_InputMethodProxy} instance. The value of
 *     inputMethodProxy is obtained by invoking
 *     [OH_InputMethodController_Attach](capi-inputmethod-controller-capi-h.md#oh_inputmethodcontroller_attach). The
 *     pointer cannot be null. If the pointer is null, the error code IME_ERR_NULL_POINTER is returned. The pointer
 *     becomes invalid after the Detach operation.
 * @param options [in] Input pointer to the {@link InputMethod_AttachOptions} instance, which is used to obtain
 *     configuration options. The pointer cannot be null. If the pointer is null, the error code IME_ERR_NULL_POINTER is
 *     returned. In this interface, you only need to pay attention to the {@link InputMethod_RequestKeyboardReason}
 *     attribute, which indicates the reason for requesting keyboard input. The ShowKeyboard attribute in AttachOptions
 *     is always true in this interface. options must be a valid AttachOptions handle; An unregistered or invalid value
 *     object handle returns IME_ERR_PARAMCHECK.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - indicates success. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - inputMethodProxy does not match the current proxy, or the options handle is not
 *     registered or invalid. </li>
 *     <li>{@link IME_ERR_IMCLIENT} - Input method client error. </li>
 *     <li>{@link IME_ERR_IMMS} - Input method service error. </li>
 *     <li>{@link IME_ERR_DETACHED}: The input method is not bound. The detached input method needs to be re-attached.
 *     </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer. The value of inputMethodProxy or options is NULL.
 *     </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 15
 */
InputMethod_ErrorCode OH_InputMethodProxy_ShowTextInput(
    InputMethod_InputMethodProxy *inputMethodProxy, InputMethod_AttachOptions *options);
/**
 * @brief Hides the keyboard.
 *
 * @param inputMethodProxy [in] Input pointer to the {@link InputMethod_InputMethodProxy} instance. The value of
 *     inputMethodProxy is obtained by invoking
 *     [OH_InputMethodController_Attach](capi-inputmethod-controller-capi-h.md#oh_inputmethodcontroller_attach). The
 *     pointer cannot be null. If the pointer is null, the error code IME_ERR_NULL_POINTER is returned. The pointer
 *     becomes invalid after the Detach operation.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - indicates success. The keyboard has requested to be hidden. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - inputMethodProxy does not match the current proxy. </li>
 *     <li>{@link IME_ERR_IMCLIENT} - Input method client error. </li>
 *     <li>{@link IME_ERR_IMMS} - Input method service error. </li>
 *     <li>{@link IME_ERR_DETACHED}: The input method is not bound. The detached input method needs to be re-attached.
 *     </li>
 *     <li>{@link IME_ERR_EDITABLE}: The text box is in the non-editing state. The binding relationship may still be
 *     valid. </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer. </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodProxy_HideKeyboard(InputMethod_InputMethodProxy *inputMethodProxy);

/**
 * @brief Notifies the input method application of the change in the selected text area, including the change of text
 * content, cursor position, or the selected text.
 *
 * @param inputMethodProxy [in] Input pointer to the {@link InputMethod_InputMethodProxy} instance. The value of
 *     inputMethodProxy is obtained by invoking
 *     [OH_InputMethodController_Attach](capi-inputmethod-controller-capi-h.md#oh_inputmethodcontroller_attach). The
 *     pointer cannot be null. If the pointer is null, the error code IME_ERR_NULL_POINTER is returned. The pointer
 *     becomes invalid after the Detach operation.
 * @param text [in] Pointer to the input text, which is encoded using UTF-16. Memory is allocated by the caller, and
 *     the function reads only this data. The pointer cannot be NULL. The maximum length is 8 KB.(8192 char16_t
 *     characters, corresponding to 16384 bytes) If this limit is exceeded, IME_ERR_PARAMCHECK is returned.
 * @param length [in] Input parameter, number of characters in the text parameter(unit: char16_t). Value range: 0 to
 *     8192. If the number exceeds 8192, the IME_ERR_PARAMCHECK error code is returned.
 * @param start [in] Input parameter, which indicates the start position of the selected text.(Unit: character
 *     offset, counting from 0) Value range: greater than or equal to 0 and less than or equal to end. Rule: The value
 *     of start must be smaller than or equal to that of end, and the length of text cannot exceed the actual length.
 * @param end [in] Input parameter, which indicates the end position of the selected text.(Unit: character offset,
 *     counting from 0) Value range: greater than or equal to the actual length of start and less than or equal to the
 *     actual length of text. Rule: When no text is selected, start is the same as end, indicating the cursor position.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - indicates success. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - Parameter error. The possible cause is that the length exceeds 8 KB or the
 *     start/end range is invalid. Check whether the parameter value is within the valid range. </li>
 *     <li>{@link IME_ERR_IMCLIENT} - Input method client error. </li>
 *     <li>{@link IME_ERR_IMMS} - Input method service error. </li>
 *     <li>{@link IME_ERR_DETACHED}: The input method is not bound. The detached input method needs to be re-attached.
 *     </li>
 *     <li>{@link IME_ERR_EDITABLE}: The text box is in the non-editing state. The binding relationship may still be
 *     valid. </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer, inputMethodProxy is NULL. </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodProxy_NotifySelectionChange(
    InputMethod_InputMethodProxy *inputMethodProxy, char16_t text[], size_t length, int start, int end);

/**
 * @brief Notifies the change of the text box configuration.
 *
 * @param inputMethodProxy [in] Input pointer to the {@link InputMethod_InputMethodProxy} instance. The value of
 *     inputMethodProxy is obtained by invoking
 *     [OH_InputMethodController_Attach](capi-inputmethod-controller-capi-h.md#oh_inputmethodcontroller_attach). The
 *     pointer cannot be null. If the pointer is null, the error code IME_ERR_NULL_POINTER is returned. The pointer
 *     becomes invalid after the Detach operation.
 * @param enterKey [in] Enter the input parameter. Value range: {@link InputMethod_EnterKeyType} Enumerated value,
 *     such as IME_ENTER_KEY_UNSPECIFIED, IME_ENTER_KEY_GO, and IME_ENTER_KEY_SEARCH. Effect after use: The input method
 *     will adjust the display label and function of the Enter key accordingly.
 * @param textType [in] Input parameter, text box type. Value range: {@link InputMethod_TextInputType} Enumerated
 *     value, such as IME_TEXT_INPUT_TYPE_UNSPECIFIED, IME_TEXT_INPUT_TYPE_TEXT, and IME_TEXT_INPUT_TYPE_NUMBER. Effect
 *     after use: The input method will switch the keyboard layout(such as the numeric keypad, text keyboard, etc.)
 *     accordingly.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - indicates success. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - Parameter error. The possible cause is that the value of enterKey or textType is
 *     invalid. Check whether the enumerated value is within the valid range. </li>
 *     <li>{@link IME_ERR_IMCLIENT} - Input method client error. </li>
 *     <li>{@link IME_ERR_IMMS} - Input method service error. </li>
 *     <li>{@link IME_ERR_DETACHED}: The input method is not bound. The detached input method needs to be re-attached.
 *     </li>
 *     <li>{@link IME_ERR_EDITABLE}: The text box is in the non-editing state. The binding relationship may still be
 *     valid. </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer. </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodProxy_NotifyConfigurationChange(InputMethod_InputMethodProxy *inputMethodProxy,
    InputMethod_EnterKeyType enterKey, InputMethod_TextInputType textType);

/**
 * @brief Notifies the cursor position change. When the cursor position in the edit box changes, this interface is used
 * to notify the input method application of the new cursor information. In this way, the input method can adjust the
 * position of the candidate word window based on the cursor position. <br> <br>Application scenario: This function is
 * invoked when the cursor moves in the edit box, for example, when a user clicks a different position in the edit box
 * or the code actively moves the cursor. <br> <br> Effect after use: After the call is successful, the input method
 * application receives the new cursor information and adjusts the positioning of the candidate word window accordingly.
 * If the interface fails to be invoked, the corresponding error code is returned. <br> <br>Prerequisites: You must
 * invoke [OH_InputMethodController_Attach](capi-inputmethod-controller-capi-h. md#oh_inputmethodcontroller_attach) to
 * obtain the inputMethodProxy instance. The cursorInfo must be a valid CursorInfo handle created with
 * {@link OH_CursorInfo_Create}, or a still valid child object borrow view returned by TextConfig, and the relevant
 * properties have been set. <br> <br>Life cycle management: The inputMethodProxy is created and output by the attach
 * process and cannot be manually destroyed. The inputMethodProxy becomes invalid after the detach process. The
 * cursorInfo created independently is managed by the caller. After using the cursorInfo, call
 * {@link OH_CursorInfo_Destroy} to destroy the cursorInfo. Sub-object views of TextConfig are borrowed only and cannot
 * be destroyed or used after they expire. <br> <br> Thread-safe: This function is not thread-safe. You are not advised
 * to operate the same inputMethodProxy object in a multi-thread environment.
 * @param inputMethodProxy [in] Input pointer to the {@link InputMethod_InputMethodProxy} instance. inputMethodProxy
 *     is obtained by calling {@link OH_InputMethodController_Attach}. The pointer cannot be null. If the pointer is
 *     null, the error code IME_ERR_NULL_POINTER is returned. The pointer becomes invalid after the Detach operation.
 * @param cursorInfo [in] Input pointer to the {@link InputMethod_CursorInfo} instance, indicating cursor
 *     information. The pointer cannot be null. If the pointer is null, the error code IME_ERR_NULL_POINTER is returned.
 *     cursorInfo must be a valid CursorInfo handle or a TextConfig sub-object borrowing view; An unregistered or
 *     invalid value object handle returns IME_ERR_PARAMCHECK. The function reads only its internal data and does not
 *     modify or release it. The object created independently through {@link OH_CursorInfo_Create} is released by the
 *     caller through {@link OH_CursorInfo_Destroy} after using it. The borrowed view cannot be destroyed.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - indicates success. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - Parameter error. The possible cause is that the internal data of cursorInfo is
 *     invalid, or the handle is not registered or invalid. Check the cursor information parameter. </li>
 *     <li>{@link IME_ERR_IMCLIENT} - Input method client error. </li>
 *     <li>{@link IME_ERR_IMMS} - Input method service error. </li>
 *     <li>{@link IME_ERR_DETACHED}: The input method is not bound. The detached input method needs to be re-attached.
 *     </li>
 *     <li>{@link IME_ERR_EDITABLE}: The text box is in the non-editing state. The binding relationship may still be
 *     valid. </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer. inputMethodProxy or cursorInfo is NULL. </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodProxy_NotifyCursorUpdate(
    InputMethod_InputMethodProxy *inputMethodProxy, InputMethod_CursorInfo *cursorInfo);

/**
 * @brief Send a private data command. An application uses this interface to send customized private command data to an
 * input method application to implement a private communication protocol between the application and the input method.
 * <br> <br>Application scenario: This function is invoked when an application needs to transfer customized private
 * data(such as service-specific instructions and configuration parameters) to an input method application. This
 * function is applicable to the scenario where a private communication protocol is used between the application and the
 * input method. <br> <br> Effect: After the invoking is successful, the input method application receives the private
 * command data through the [OH_TextEditorProxy_ReceivePrivateCommandFunc](capi-inputmethod-text-editor-proxy-capi-h.
 *     md#oh_texteditorproxy_receiveprivatecommandfunc)
 * callback. If the interface fails to be invoked, the corresponding error code is returned. <br> <br>Prerequisites: You
 * must invoke [OH_InputMethodController_Attach](capi-inputmethod-controller-capi-h. md#oh_inputmethodcontroller_attach)
 * to obtain the inputMethodProxy instance and the instance is in the Attached state. <br> <br>Life cycle management:
 * The inputMethodProxy is created and output by the attach process and cannot be manually destroyed. The
 * inputMethodProxy becomes invalid after the detach process. Self-owned objects in the privateCommand array are managed
 * by the caller. After using the privateCommand array, you need to call {@link OH_PrivateCommand_Destroy} to destroy
 * them one by one. Borrowed objects provided by the callback cannot be destroyed or retained after the callback ends.
 * <br> <br>Performance suggestion: The privateCommand array contains a maximum of five command objects(the maximum size
 * is 5). If the number of command objects exceeds the limit, IME_ERR_PARAMCHECK is returned. The maximum size of a
 * single command object is 32 KB. If the maximum size is exceeded, data transfer may fail. <br> <br> Thread-safe: This
 * function is not thread-safe. You are not advised to operate the same inputMethodProxy object in a multi-thread
 * environment.
 * @param inputMethodProxy [in] Input pointer to the {@link InputMethod_InputMethodProxy} instance. The value of
 *     inputMethodProxy is obtained by invoking
 *     [OH_InputMethodController_Attach](capi-inputmethod-controller-capi-h.md#oh_inputmethodcontroller_attach). The
 *     pointer cannot be null. If the pointer is null, the error code IME_ERR_NULL_POINTER is returned. The pointer
 *     becomes invalid after the Detach operation.
 * @param privateCommand [in] Input pointer, private command array. Each element must be a valid self-owned command
 *     object or a borrowed command object provided by the callback, pointing to the InputMethod_PrivateCommand
 *     instance. An unregistered or invalid value object handle returns IME_ERR_PARAMCHECK. Own objects are created and
 *     memory is allocated by the caller, and functions only read data. The pointer cannot be NULL. The maximum size of
 *     a single command object is 32 KB(including the total size of the key and value). If the size exceeds 32 KB, the
 *     transmission may fail. The maximum length of the array is 5(that is, the maximum length of the size parameter is
 *     5).
 * @param size [in] Input parameter, indicating the number of elements in the private command array. Value range: 0
 *     to 5. If the value exceeds 5, the IME_ERR_PARAMCHECK error code is returned.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - indicates success and the private command has been sent. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - Parameter error. The possible causes are as follows: size exceeds 5,
 *     privateCommand is NULL, or a single command exceeds 32 KB,
 *     or the object handle in the array is not registered or invalid. Check the parameter value. </li>
 *     <li>{@link IME_ERR_IMCLIENT} - Input method client error. </li>
 *     <li>{@link IME_ERR_IMMS} - Input method service error. </li>
 *     <li>{@link IME_ERR_DETACHED}: The input method is not bound. The detached input method needs to be re-attached.
 *     </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer, inputMethodProxy or privateCommand is NULL. </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodProxy_SendPrivateCommand(
    InputMethod_InputMethodProxy *inputMethodProxy, InputMethod_PrivateCommand *privateCommand[], size_t size);

/**
 * @brief Request system input capability.
 *
 * @param inputMethodProxy [in] indicates the pointer to the {@link InputMethod_InputMethodProxy} instance.
 * The value of inputMethodProxy is obtained from {@link OH_InputMethodController_Attach}.
 * @param type [out] indicates the input capability type. {@link OH_InputMethod_InputCapabilityType}
 * @returnReturns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - Success.</li>
 *     <li>{@link IME_ERR_PARAMCHECK} - Parameter verification failed.</li>
 *     <li>{@link IME_ERR_IMMS} - Input method management service error.</li>
 *     <li>{@link IME_ERR_DETAACHE} - The input method client is disconnected.</li>
 *     <li>{@link OH_INPUT METHOD_ERR_NOT_DEFAULT_IME} - The current input method is not the default input method configured
 *     in the system.</li>
 *     <li>{@link OH_INPUT METHOD_ERR_INPUT_CAPABLE_TYPE_NOT_SUPPORTED} - The input capability type is not supported.</li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer.</li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}.</li>
 *     <ul>
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_InputMethodProxy_RequestSystemInputCapability(
    InputMethod_InputMethodProxy *inputMethodProxy, OH_InputMethod_InputCapabilityType type);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // INPUTMETHOD_INPUTMETHOD_PROXY_CAPI_H
