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
 * @brief Displays the keyboard.
 *
 * @param inputMethodProxy Pointer to the {@link InputMethod_InputMethodProxy} instance obtained by calling
 *     {@link OH_InputMethodController_Attach}.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_IMCLIENT} - Client error in input method.
 *     <br>{@link IME_ERR_IMMS} - Input method service error.
 *     <br>{@link IME_ERR_DETACHED} - Input method not bound.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodProxy_ShowKeyboard(InputMethod_InputMethodProxy *inputMethodProxy);
/**
 * @brief Displays the text box.
 *
 * @param inputMethodProxy Pointer to the {@link InputMethod_InputMethodProxy} instance obtained by calling
 *     {@link OH_InputMethodController_Attach}.
 * @param options Pointer to the {@link InputMethod_AttachOptions} instance, which is used to obtain the configuration
 *     options.
 *     <br>In this API, you only need to pay attention to {@link InputMethod_RequestKeyboardReason}, which indicates
 *     the reason for requesting the keyboard.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_IMCLIENT} - Client error in input method.
 *     <br>{@link IME_ERR_IMMS} - Input method service error.
 *     <br>{@link IME_ERR_DETACHED} - Input method not bound.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 15
 */
InputMethod_ErrorCode OH_InputMethodProxy_ShowTextInput(
    InputMethod_InputMethodProxy *inputMethodProxy, InputMethod_AttachOptions *options);
/**
 * @brief Hides the keyboard.
 *
 * @param inputMethodProxy Pointer to the {@link InputMethod_InputMethodProxy} instance obtained by calling
 *     {@link OH_InputMethodController_Attach}.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_IMCLIENT} - Client error in input method.
 *     <br>{@link IME_ERR_IMMS} - Input method service error.
 *     <br>{@link IME_ERR_DETACHED} - Input method not bound.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodProxy_HideKeyboard(InputMethod_InputMethodProxy *inputMethodProxy);

/**
 * @brief Notifies the input method application of the change in the selected text area, including the change of text
 * content, cursor position, or the selected text.
 *
 * @param inputMethodProxy Pointer to the {@link InputMethod_InputMethodProxy} instance obtained by calling
 *     {@link OH_InputMethodController_Attach}.
 * @param text Entire input text.
 * @param length Length of the **text** parameter. Maximum length: 8 KB.
 * @param start Start position of the selected text.
 * @param end End position of the selected text.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_PARAMCHECK} - Parameter error.
 *     <br>{@link IME_ERR_IMCLIENT} - Client error in input method.
 *     <br>{@link IME_ERR_IMMS} - Input method service error.
 *     <br>{@link IME_ERR_DETACHED} - Input method not bound.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodProxy_NotifySelectionChange(
    InputMethod_InputMethodProxy *inputMethodProxy, char16_t text[], size_t length, int start, int end);

/**
 * @brief Notifies the change of the text box configuration.
 *
 * @param inputMethodProxy Pointer to the {@link InputMethod_InputMethodProxy} instance obtained by calling
 *     {@link OH_InputMethodController_Attach}.
 * @param enterKey Enter key type.
 * @param textType Text box type.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_PARAMCHECK} - Parameter error.
 *     <br>{@link IME_ERR_IMCLIENT} - Client error in input method.
 *     <br>{@link IME_ERR_IMMS} - Input method service error.
 *     <br>{@link IME_ERR_DETACHED} - Input method not bound.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodProxy_NotifyConfigurationChange(InputMethod_InputMethodProxy *inputMethodProxy,
    InputMethod_EnterKeyType enterKey, InputMethod_TextInputType textType);

/**
 * @brief Notifies the cursor position change.
 *
 * @param inputMethodProxy Pointer to the {@link InputMethod_InputMethodProxy} instance obtained by calling
 *     {@link OH_InputMethodController_Attach}.
 * @param cursorInfo Pointer to the {@link InputMethod_CursorInfo} instance, indicating the cursor information.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_PARAMCHECK} - Parameter error.
 *     <br>{@link IME_ERR_IMCLIENT} - Client error in input method.
 *     <br>{@link IME_ERR_IMMS} - Input method service error.
 *     <br>{@link IME_ERR_DETACHED} - Input method not bound.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodProxy_NotifyCursorUpdate(
    InputMethod_InputMethodProxy *inputMethodProxy, InputMethod_CursorInfo *cursorInfo);

/**
 * @brief Sends a private data command.
 *
 * @param inputMethodProxy Pointer to the {@link InputMethod_InputMethodProxy} instance obtained by calling
 *     {@link OH_InputMethodController_Attach}.
 * @param privateCommand Private command that is defined in {@link InputMethod_PrivateCommand}. The maximum size is 32
 *     KB.
 * @param size Size of the private command array. The maximum size is 5.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_PARAMCHECK} - Parameter error.
 *     <br>{@link IME_ERR_IMCLIENT} - Client error in input method.
 *     <br>{@link IME_ERR_IMMS} - Input method service error.
 *     <br>{@link IME_ERR_DETACHED} - Input method not bound.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodProxy_SendPrivateCommand(
    InputMethod_InputMethodProxy *inputMethodProxy, InputMethod_PrivateCommand *privateCommand[], size_t size);

/**
 * @brief Request system input capability.
 *
 * @param inputMethodProxy [Input parameter] indicates the pointer to the {@link InputMethod_InputMethodProxy} instance.
 * The value of inputMethodProxy is obtained from {@link OH_InputMethodController_Attach}.
 * @param type [Input parameter] indicates the input capability type. {@link OH_InputMethod_InputCapabilityType}
 * @returnReturns a specific error code.
 * <br>{@link IME_ERR_OK} - Success.
 * <br>{@link IME_ERR_PARAMCHECK} - Parameter verification failed.
 * <br>{@link IME_ERR_IMMS} - Input method management service error.
 * <br>{@link IME_ERR_DETAACHE} - The input method client is disconnected.
 * <br>{@link OH_INPUT METHOD_ERR_NOT_DEFAULT_IME} - The current input method is not the default input method configured
 * in the system.
 * <br>{@link OH_INPUT METHOD_ERR_INPUT_CAPABLE_TYPE_NOT_SUPPORTED} - The input capability type is not supported.
 * <br>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer.
 * For details about the error code, see {@link InputMethod_ErrorCode}.
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_InputMethodProxy_RequestSystemInputCapability(
    InputMethod_InputMethodProxy *inputMethodProxy, OH_InputMethod_InputCapabilityType type);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // INPUTMETHOD_INPUTMETHOD_PROXY_CAPI_H
