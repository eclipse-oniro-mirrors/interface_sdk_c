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
 * @brief InputMethod provides functions to use input methods and develop input methods.
 *
 * @since 12
 */

/**
 * @file inputmethod_text_editor_proxy_capi.h
 *
 * @brief Provides a set of methods that enable self‑drawn input boxes implemented by an app to receive notifications
 * and requests from the input method app. This module uses a callback mechanism to implement bidirectional
 * communication between the input method app and self‑drawn input box.
 *
 * @include <inputmethod/inputmethod_text_editor_proxy_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_TEXT_EDITOR_PROXY_CAPI_H
#define OHOS_INPUTMETHOD_TEXT_EDITOR_PROXY_CAPI_H
#include <stddef.h>

#include "inputmethod_private_command_capi.h"
#include "inputmethod_text_config_capi.h"
#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief Represents the proxy class for the input method text editor. It handles the interaction between the input
 * method app and the text editor, provides methods for receiving input method requests and notifications, and is
 * suitable for scenarios requiring bidirectional communication between the input method and the editor. This struct is
 * an opaque type. You cannot directly access its internal members and can only operate on it through the functions
 * provided by this module.
 *
 * @since 12
 */
typedef struct InputMethod_TextEditorProxy InputMethod_TextEditorProxy;

/**
 * @brief Callback triggered when the input method obtains the input box configuration. You need to implement this
 * function and set the configuration information of the edit box (input type, Enter key type, cursor information, etc.)
 * for the **config** parameter in the function. The input method framework adjusts the keyboard layout and input
 * behavior accordingly.
 * <br>Usage scenarios: When the input method app needs to obtain the configuration information of the edit box, the
 * system automatically invokes this callback. This callback is one of the core callbacks for interaction between the
 * input method and the editor, and must be implemented.
 * <br>Use effect: After the callback returns, the input method framework reads the configuration information in **
 * config** and adjusts the keyboard behavior accordingly. The memory of the **config** parameter is released after the
 * callback returns and cannot be accessed again.
 * <br>Preconditions: This callback must be set to **TextEditorProxy** through
 * {@link OH_TextEditorProxy_SetGetTextConfigFunc}, and registration must be completed through
 * {@link OH_InputMethodController_Attach}. The execution thread of this callback is determined by the thread that
 * calls **Attach**, and is not affected by {@link OH_TextEditorProxy_SetCallbackInMainThread}.
 *
 * @param textEditorProxy Input pointer to the {@link InputMethod_TextEditorProxy} instance for the current callback.
 *     It identifies the proxy object that triggers the callback.
 * @param config Output pointer to the {@link InputMethod_TextConfig} instance. In the function implementation, set its
 *     configuration properties (input type, Enter key type, cursor information, etc.) for the input box configuration.
 *     This pointer is valid only during callback execution. After the callback returns, the memory will be released
 *     and must not be accessed again. You must complete all configuration operations inside the callback and must not
 *     continue to use this pointer outside the callback.
 * @since 12
 */
typedef void (*OH_TextEditorProxy_GetTextConfigFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_TextConfig *config);
/**
 * @brief Callback triggered when the input method app inserts text. You need to implement this function to insert the
 * text content specified by the **text** parameter at the cursor position of the edit box.
 * <br>Usage scenarios: When the input method app inserts text into the edit box (for example, when the user selects a
 * candidate word or enters a character), the system automatically invokes this callback. This callback is one of the
 * core callbacks for interaction between the input method and the editor, and must be implemented.
 * <br>Use effect: After the callback is executed, the edit box should insert the specified text at the cursor position
 * and update the text content and cursor position.
 * <br>Preconditions: This callback must be set to **TextEditorProxy** through
 * {@link OH_TextEditorProxy_SetInsertTextFunc}, and registration must be completed through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @param text Input pointer to the text content to be inserted, encoded in UTF-16. This pointer is valid only during
 *     callback execution. After the callback returns, the memory is released and must not be accessed again. You
 *     should complete the necessary data copy or processing inside the callback.
 * @param length Input parameter, indicating the number of characters to insert (unit: number of char16_t characters).
 *     Value range: greater than 0.
 * @since 12
 */
typedef void (*OH_TextEditorProxy_InsertTextFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, const char16_t *text, size_t length);
/**
 * @brief Callback triggered when the input method deletes the text to the right of the cursor. You need to implement
 * this function to delete the specified number of characters to the right from the cursor position.
 * <br>Usage scenarios: This callback is automatically invoked when the input method app requests to delete the text to
 * the right of the cursor (for example, when the user performs a forward delete operation in the input method).
 * <br>Use effect: After the callback execution, the edit box should delete the specified number of characters to the
 * right from the cursor position and update the text content and cursor position.
 * <br>Preconditions: This callback must be set for **TextEditorProxy** through
 * {@link OH_TextEditorProxy_SetDeleteForwardFunc} and registered through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @param length Input parameter, indicating the number of characters to delete (unit: character count). Value range:
 *     greater than 0. Value principle: if **length** exceeds the length of the existing text to the right of the
 *     cursor, delete runs to the end of the text; otherwise, the specified number of characters are deleted.
 * @since 12
 */
typedef void (*OH_TextEditorProxy_DeleteForwardFunc)(InputMethod_TextEditorProxy *textEditorProxy, int32_t length);
/**
 * @brief Callback triggered when the input method deletes the text to the left of the cursor. You need to implement
 * this function to delete the specified number of characters to the left from the cursor position.
 * <br>Usage scenarios: When the input method app requests to delete text to the left of the cursor (for example, when
 * the user performs a backspace deletion in the input method), the system automatically invokes this callback.
 * <br>Use effect: After the callback is executed, the edit box should delete the specified number of characters to the
 * left of the cursor position and update the text content and cursor position.
 * <br>Preconditions: This callback must be set to **TextEditorProxy** via
 * {@link OH_TextEditorProxy_SetDeleteBackwardFunc} and registered through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @param length Input parameter, indicating the number of characters to delete (unit: number of characters). Value
 *     range: greater than 0. Value principle: if **length** exceeds the length of the existing text to the left of the
 *     cursor, delete runs to the beginning of the text; otherwise, the specified number of characters are deleted.
 * @since 12
 */
typedef void (*OH_TextEditorProxy_DeleteBackwardFunc)(InputMethod_TextEditorProxy *textEditorProxy, int32_t length);
/**
 * @brief Callback triggered when the input method reports the keyboard status. You need to implement this function to
 * update the edit box's awareness of the keyboard status based on the **keyboardStatus** parameter.
 * <br>Usage scenarios: When the keyboard status of the input method app changes (shown or hidden), the system
 * automatically invokes this callback to notify the edit box of the current keyboard status.
 * <br>Use effect: After the callback is executed, the edit box should update its awareness of keyboard visibility
 * accordingly, for example, adjusting the avoidance strategy or UI layout.
 * <br>Preconditions: This callback must be set to **TextEditorProxy** via
 * {@link OH_TextEditorProxy_SetSendKeyboardStatusFunc} and registered through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @param keyboardStatus Input parameter, indicating the keyboard status. Value range:
 *     {@link InputMethod_KeyboardStatus} enum values (**IME_KEYBOARD_STATUS_NONE=0**, **IME_KEYBOARD_STATUS_HIDE=1**,
 *     and **IME_KEYBOARD_STATUS_SHOW=2**). Use effect: when set to **IME_KEYBOARD_STATUS_SHOW**, it indicates that the
 *     keyboard is shown; when set to **IME_KEYBOARD_STATUS_HIDE**, it indicates that the keyboard is hidden.
 * @since 12
 */
typedef void (*OH_TextEditorProxy_SendKeyboardStatusFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_KeyboardStatus keyboardStatus);
/**
 * @brief Callback triggered when the input method sends the Enter key. You need to implement this function to perform
 * the corresponding Enter key action based on the **enterKeyType** parameter.
 * <br>Usage scenarios: When the input method app notifies the edit box of an Enter key event, the system automatically
 * invokes this callback.
 * <br>Use effect: After the callback is executed, the edit box should perform the corresponding Enter key behavior (
 * such as Search, Send, Done, etc.).
 * <br>Preconditions: This callback must be set to the **TextEditorProxy** through
 * {@link OH_TextEditorProxy_SetSendEnterKeyFunc} and registered through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @param enterKeyType Input parameter, indicating the Enter key type. Value range: {@link InputMethod_EnterKeyType}
 *     enum values. Use effect: different types correspond to different Enter key behaviors, for example, **
 *     IME_ENTER_KEY_GO** indicates **"Go"** and **IME_ENTER_KEY_SEARCH** indicates **"Search"**.
 * @since 12
 */
typedef void (*OH_TextEditorProxy_SendEnterKeyFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_EnterKeyType enterKeyType);
/**
 * @brief Callback triggered when the input method moves the cursor. You need to implement this function to move the
 * cursor position in the edit box based on the **direction** parameter.
 * <br>Usage scenarios: When the input method app requests to move the cursor, the system automatically invokes this
 * callback.
 * <br>Use effect: After the callback is executed, the edit box should move the cursor position accordingly and update
 * the cursor display.
 * <br>Preconditions: This callback must be set to the **TextEditorProxy** through
 * {@link OH_TextEditorProxy_SetMoveCursorFunc} and registered through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @param direction Input parameter, indicating the cursor movement direction. Value range:
 *     {@link InputMethod_Direction} enum values. Use effect: different directions correspond to different cursor
 *     movement behaviors, for example, **IME_DIRECTION_UP** indicates moving up, **IME_DIRECTION_DOWN** indicates
 *     moving down, **IME_DIRECTION_LEFT** indicates moving left, and **IME_DIRECTION_RIGHT** indicates moving right.
 * @since 12
 */
typedef void (*OH_TextEditorProxy_MoveCursorFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_Direction direction);
/**
 * @brief Callback triggered when the input method requests text selection. You need to implement this function to
 * select the specified range of text in the edit box based on the **start** and **end** parameters.
 * <br>Usage scenarios: When the input method app requests to select a range of text in the text box, the system
 * automatically invokes this callback.
 * <br>Use effect: After the callback is executed, the edit box should select the text from **start** to **end** and
 * update the selection state and UI display.
 * <br>Preconditions: This callback must be set to **TextEditorProxy** through
 * {@link OH_TextEditorProxy_SetHandleSetSelectionFunc} and registered through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @param start Input parameter, indicating the start position of the selected text (unit: character offset, counted
 *     from 0). Value principle: **start** must be greater than or equal to 0 and less than or equal to **end**.
 * @param end Input parameter, indicating the end position of the selected text (unit: character offset, counted from 0)
 *     . Value principle: **end** must be greater than or equal to **start** and less than the total text length.
 * @since 12
 */
typedef void (*OH_TextEditorProxy_HandleSetSelectionFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, int32_t start, int32_t end);
/**
 * @brief Callback triggered when the input method sends an extended editing operation. You need to implement this
 * function to perform the corresponding extended editing operation based on the action parameter.
 * <br>Usage scenarios: When the input method app requests an extended editing operation (such as cut, copy, or select
 * all), the system automatically invokes this callback.
 * <br>Use effect: After the callback is executed, the edit box should perform the corresponding extended editing
 * operation accordingly.
 * <br>Preconditions: This callback must be set to the **TextEditorProxy** through
 * {@link OH_TextEditorProxy_SetHandleExtendActionFunc} and registered through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @param action Input parameter, extended editing operation. Value range: {@link InputMethod_ExtendAction} enum values.
 *     Use effect: Different actions correspond to different editing behaviors. For example, **
 *     IME_EXTEND_ACTION_SELECT_ALL** indicates select all, **IME_EXTEND_ACTION_CUT** indicates cut, and **
 *     IME_EXTEND_ACTION_COPY** indicates copy.
 * @since 12
 */
typedef void (*OH_TextEditorProxy_HandleExtendActionFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_ExtendAction action);
/**
 * @brief Callback triggered when the input method obtains the text to the left of the cursor. You must implement this
 * function to write the specified number of characters to the left of the cursor into the **text** parameter and write
 * the actual number of characters into the **length** parameter.
 * <br>Usage scenarios: When the input method app needs to obtain the text to the left of the cursor (for example, for
 * predictive input or context analysis), the system automatically invokes this callback.
 * <br>Use effect: After the callback returns, the input method app reads the data in **text** and **length** for
 * context analysis.
 * <br>Preconditions: This callback must be set to **TextEditorProxy** through
 * {@link OH_TextEditorProxy_SetGetLeftTextOfCursorFunc} and registered through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @param number Input parameter, number of characters to obtain (unit: character count). Value range: greater than 0.
 *     Value principle: if **number** exceeds the length of existing text to the left of the cursor, all text to the
 *     left should be returned.
 * @param text Output pointer, text content of the specified length to the left of the cursor, which needs to be
 *     assigned in the function implementation. UTF-16 encoding is used. This pointer is valid only during callback
 *     execution. After the callback returns, the memory is released and must not be accessed again. You must complete
 *     the assignment inside the callback.
 * @param length Output pointer, used to return the actual number of characters obtained (unit: number of char16_t
 *     characters). The memory is allocated by the caller (input method framework), and you must assign a value to *
 *     length inside the callback.
 * @since 12
 */
typedef void (*OH_TextEditorProxy_GetLeftTextOfCursorFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, int32_t number, char16_t text[], size_t *length);
/**
 * @brief Callback triggered when the input method obtains the text to the right of the cursor. You must implement this
 * function to write the specified number of characters to the right of the cursor into the text parameter and write
 * the actual number of characters into the length parameter.
 * <br>Usage scenarios: When the input method app needs to obtain the text to the right of the cursor, the system
 * automatically invokes this callback.
 * <br>Use effect: After the callback returns, the input method app reads the data in **text** and **length** for
 * context analysis.
 * <br>Preconditions: This callback must be set to **TextEditorProxy** via
 * {@link OH_TextEditorProxy_SetGetRightTextOfCursorFunc} and registered through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @param number Input parameter, number of characters to obtain (unit: number of characters). Value range: greater
 *     than 0. Value principle: if number exceeds the length of the remaining text to the right of the cursor, all text
 *     on the right should be returned.
 * @param text Output pointer, text content of the specified length to the right of the cursor, which needs to be
 *     assigned in the function implementation. UTF-16 encoding is used. This pointer is valid only during callback
 *     execution. After the callback returns, the memory will be released and must not be accessed again.
 * @param length Output pointer, used to return the number of characters actually obtained (unit: number of char16_t
 *     characters). The memory is allocated by the caller, and you need to assign a value to *length inside the
 *     callback.
 * @since 12
 */
typedef void (*OH_TextEditorProxy_GetRightTextOfCursorFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, int32_t number, char16_t text[], size_t *length);
/**
 * @brief Callback triggered when the input method obtains the text index of the input box where the cursor is located.
 * You need to implement this function and return the character index position of the cursor in the text of the edit
 * box.
 * <br>Usage scenarios: When the input method app needs to obtain the precise position of the cursor in the text, the
 * system automatically calls this callback.
 * <br>Use effect: After the callback returns, the input method app reads the returned index value to locate the
 * context.
 * <br>Preconditions: This callback must be set to **TextEditorProxy** via
 * {@link OH_TextEditorProxy_SetGetTextIndexAtCursorFunc} and registered through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @return Returns the character index position of the cursor in the text content, with the index starting from 0 (unit:
 *     character offset). Value range: greater than or equal to 0 and less than the total text length.
 * @since 12
 */
typedef int32_t (*OH_TextEditorProxy_GetTextIndexAtCursorFunc)(InputMethod_TextEditorProxy *textEditorProxy);
/**
 * @brief Callback triggered when the input method app sends private data commands. You must implement this function to
 * process the private command data sent by the input method app.
 * <br>Usage scenarios: When the input method app sends a private command to the edit box through
 * {@link OH_InputMethodProxy_SendPrivateCommand}, the system automatically invokes this callback.
 * <br>Use effect: After the callback returns, the input method app determines whether the command was processed
 * successfully based on the return value.
 * <br>Preconditions: This callback must be set to **TextEditorProxy** through
 * {@link OH_TextEditorProxy_SetReceivePrivateCommandFunc} and registered through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @param privateCommand Input pointer, array of private data commands. This pointer is valid only during callback
 *     execution. After the callback returns, the memory will be released and must not be accessed again. You should
 *     complete the necessary data copy or processing inside the callback and must not continue using this pointer
 *     outside the callback.
 * @param size input parameter, number of elements in the private data command array. Value range: greater than 0 and
 *     no more than 5.
 * @return Returns the processing result of the private data command.
 *     <br>**0**: indicates success.
 *     <br>A non-zero value: indicates failure.
 * @since 12
 */
typedef int32_t (*OH_TextEditorProxy_ReceivePrivateCommandFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, InputMethod_PrivateCommand *privateCommand[], size_t size);
/**
 * @brief Callback triggered when the input method sets preview text. Preview text is the candidate text display
 * feature of the input method, typically shown when the user enters pinyin or input codes before the Chinese
 * characters are determined. This function is responsible for setting the preview text and its cursor position. It is
 * used together with {@link OH_TextEditorProxy_FinishTextPreviewFunc}: first call **SetPreviewTextFunc** to set the
 * preview text content, and when the user selects a candidate word or cancels the input, call **FinishTextPreviewFunc**
 * to end the preview.
 * <br>Usage scenarios: When the input method app needs to display candidate text (such as preview text during Pinyin
 * input), the system automatically invokes this callback.
 * <br>Use effect: After the callback is executed, the edit box should display the text content in preview text style
 * within the range from **start** to **end**, and return the result to the input method.
 * <br>Preconditions: This callback must be set to **TextEditorProxy** through
 * {@link OH_TextEditorProxy_SetSetPreviewTextFunc} and registered through **Attach**. The edit box must enable preview
 * text support in **TextConfig** (**supported**=**true**).
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @param text Input pointer, the text content requested to be set as the preview text style, encoded in UTF-16. This
 *     pointer is valid only during callback execution. After the callback returns, the memory will be released and
 *     must not be accessed again. You should complete the necessary data copy within the callback.
 * @param length Input parameter, the number of characters in the preview text (unit: number of char16_t characters).
 * @param start Input parameter, the starting cursor position of the preview text (unit: character offset, relative to
 *     the beginning of the text). Value rule: **start** should be greater than or equal to 0 and less than or equal to
 *     **end**.
 * @param end Input parameter, the ending cursor position of the preview text (unit: character offset, relative to the
 *     beginning of the text). Value rule: **end** should be greater than or equal to **start** and less than the total
 *     text length.
 * @return Returns the processing result.
 *     <br>**0**: indicates success.
 *     <br>A non-zero value: indicates failure.
 * @since 12
 */
typedef int32_t (*OH_TextEditorProxy_SetPreviewTextFunc)(
    InputMethod_TextEditorProxy *textEditorProxy, const char16_t text[], size_t length, int32_t start, int32_t end);
/**
 * @brief Callback triggered when the input method finishes preview text. This function is used to clear the preview
 * text state, and is typically invoked when the user selects a candidate word (confirms input) or cancels input. It is
 * used together with {@link OH_TextEditorProxy_SetPreviewTextFunc}.
 * <br>Usage scenarios: When the input method app needs to end the preview text state, the system automatically invokes
 * this callback.
 * <br>Use effect: After callback execution, the edit box should clear the preview text display state and restore
 * normal text display.
 * <br>Preconditions: This callback must be set to **TextEditorProxy** through
 * {@link OH_TextEditorProxy_SetFinishTextPreviewFunc} and registered through **Attach**.
 *
 * @param textEditorProxy Input pointer to the **TextEditorProxy** instance for the current callback.
 * @since 12
 */
typedef void (*OH_TextEditorProxy_FinishTextPreviewFunc)(InputMethod_TextEditorProxy *textEditorProxy);

/**
 * @brief Creates a new {@link InputMethod_TextEditorProxy} instance. After creation, register callbacks through the **
 * Set*Func** APIs, and then complete attachment and registration through {@link OH_InputMethodController_Attach}.
 * <br>Usage scenarios: Call this function when an app needs to create a text editor proxy object to receive input
 * method requests and notifications.
 * <br>Use effect: If the creation succeeds, a new **TextEditorProxy** instance pointer is returned, and callbacks can
 * be registered through the **Set*Func** APIs afterward.
 * <br>Lifecycle management: The returned object must be destroyed through {@link OH_TextEditorProxy_Destroy}. **Create*
 * * and **Destroy** must be used in pairs. Failure to destroy it will cause memory leaks. The same instance can be
 * destroyed only once.
 *
 * @return If the creation is successful, returns a pointer to the newly created {@link InputMethod_TextEditorProxy}
 *     instance.
 *     <br>If the creation fails, returns **NULL**. A possible cause of failure is insufficient memory. When **
 *     NULL** is returned, check the system memory status. After use, the returned pointer must be destroyed by
 *     {@link OH_TextEditorProxy_Destroy}, and the pointer should be set to **NULL** after destruction to avoid misuse.
 * @since 12
 */
InputMethod_TextEditorProxy *OH_TextEditorProxy_Create(void);
/**
 * @brief Destroys an {@link InputMethod_TextEditorProxy} instance. After destruction, the proxy pointer can no longer
 * be used. It is recommended that you set the pointer to **NULL** to avoid misuse.
 * <br>Usage scenarios: Call this function to release resources when the app no longer needs the **TextEditorProxy**
 * object (for example, after **Detach** is called or when the app exits).
 * <br>Use effect: The proxy object is released and its internal resources are reclaimed. After that, no function can
 * be called through the proxy pointer.
 * <br>Lifecycle management: Used in pairs with {@link OH_TextEditorProxy_Create}. The object returned by **Create**
 * must eventually be released through **Destroy**. The same instance can be destroyed only once and cannot be
 * destroyed repeatedly. If proxy is null, the function does nothing.
 *
 * @param proxy Input pointer to the {@link InputMethod_TextEditorProxy} instance to be destroyed. If **NULL** is
 *     passed in, the function does nothing and does not cause a crash. After destruction, this pointer becomes invalid.
 *     It is recommended that you set it to **NULL**.
 * @since 12
 */
void OH_TextEditorProxy_Destroy(InputMethod_TextEditorProxy *proxy);
/**
 * @brief Sets the {@link OH_TextEditorProxy_GetTextConfigFunc} function to {@link InputMethod_TextEditorProxy}. This
 * setting must be completed before **Attach** is called. Callbacks set after **Attach** will not be invoked by the
 * input method.
 * <br>Usage scenarios: Call this function when the app needs to register the **GetTextConfigFunc** callback to respond
 * to the input method's request for configuration.
 * <br>Use effect: After the setting succeeds, the **GetTextConfigFunc** callback is registered to **TextEditorProxy**.
 * After **Attach** is called, this callback is automatically triggered when the input method requests configuration.
 * <br>Preconditions: **proxy** must be created through {@link OH_TextEditorProxy_Create} first.
 *
 * @param proxy Input pointer to the {@link InputMethod_TextEditorProxy} instance to be set. It cannot be **NULL**. If *
 *     *NULL** is passed in, **IME_ERR_NULL_POINTER** is returned.
 * @param getTextConfigFunc Input parameter, indicating the {@link OH_TextEditorProxy_GetTextConfigFunc} callback to be
 *     set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetGetTextConfigFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetTextConfigFunc getTextConfigFunc);
/**
 * @brief Sets the {@link OH_TextEditorProxy_InsertTextFunc} function to {@link InputMethod_TextEditorProxy}. This
 * setting must be completed before **Attach**.
 * <br>Usage scenarios: Call this function when the app needs to register the **InsertTextFunc** callback to respond to
 * the input method's request to insert text.
 * <br>Use effect: After the setting succeeds, the **InsertTextFunc** callback is registered to **TextEditorProxy**.
 * After **Attach** is called, this callback is automatically triggered when the input method requests to insert text.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param insertTextFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetInsertTextFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_InsertTextFunc insertTextFunc);
/**
 * @brief Sets the {@link OH_TextEditorProxy_DeleteForwardFunc} function to {@link InputMethod_TextEditorProxy}. This
 * setting must be completed before **Attach**.
 * <br>Usage scenarios: Call this function when the app needs to register the **DeleteForwardFunc** callback to respond
 * to the input method's request to delete text to the right of the cursor.
 * <br>Use effect: After the setting succeeds, the **DeleteForwardFunc** callback is registered to **TextEditorProxy**.
 * After **Attach** is called, this callback is automatically triggered when the input method requests to delete text
 * to the right of the cursor.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param deleteForwardFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetDeleteForwardFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_DeleteForwardFunc deleteForwardFunc);
/**
 * @brief Sets the {@link OH_TextEditorProxy_DeleteBackwardFunc} function for {@link InputMethod_TextEditorProxy}. This
 * setting must be completed before **Attach**.
 * <br>Usage scenarios: Call this function when the app needs to register the **DeleteBackwardFunc** callback to
 * respond to the input method's request to delete text to the left of the cursor.
 * <br>Use effect: After the setting succeeds, the **DeleteBackwardFunc** callback is registered with **TextEditorProxy*
 * *. After **Attach** is called, this callback is automatically triggered when the input method requests deletion of
 * text to the left of the cursor.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param deleteBackwardFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetDeleteBackwardFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_DeleteBackwardFunc deleteBackwardFunc);
/**
 * @brief Sets the {@link OH_TextEditorProxy_SendKeyboardStatusFunc} function for {@link InputMethod_TextEditorProxy}.
 * This setting must be completed before **Attach**.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param sendKeyboardStatusFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetSendKeyboardStatusFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_SendKeyboardStatusFunc sendKeyboardStatusFunc);
/**
 * @brief Sets the {@link OH_TextEditorProxy_SendEnterKeyFunc} function for {@link InputMethod_TextEditorProxy}. This
 * setting must be completed before **Attach**.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param sendEnterKeyFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetSendEnterKeyFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_SendEnterKeyFunc sendEnterKeyFunc);
/**
 * @brief Sets the function {@link OH_TextEditorProxy_MoveCursorFunc} for {@link InputMethod_TextEditorProxy}. This
 * setting must be completed before **Attach**.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param moveCursorFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetMoveCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_MoveCursorFunc moveCursorFunc);
/**
 * @brief Sets the function {@link OH_TextEditorProxy_HandleSetSelectionFunc} into {@link InputMethod_TextEditorProxy}.
 * This setting must be completed before **Attach**.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param handleSetSelectionFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetHandleSetSelectionFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_HandleSetSelectionFunc handleSetSelectionFunc);
/**
 * @brief Sets the function {@link OH_TextEditorProxy_HandleExtendActionFunc} into {@link InputMethod_TextEditorProxy}.
 * This setting must be completed before **Attach**.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param handleExtendActionFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetHandleExtendActionFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_HandleExtendActionFunc handleExtendActionFunc);
/**
 * @brief Sets the function {@link OH_TextEditorProxy_GetLeftTextOfCursorFunc} into {@link InputMethod_TextEditorProxy}.
 * This setting must be completed before **Attach**.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param getLeftTextOfCursorFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetGetLeftTextOfCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetLeftTextOfCursorFunc getLeftTextOfCursorFunc);
/**
 * @brief Sets the function {@link OH_TextEditorProxy_GetRightTextOfCursorFunc} into
 * {@link InputMethod_TextEditorProxy}. This setting must be completed before **Attach**.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param getRightTextOfCursorFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetGetRightTextOfCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetRightTextOfCursorFunc getRightTextOfCursorFunc);
/**
 * @brief Sets the {@link OH_TextEditorProxy_GetTextIndexAtCursorFunc} function for {@link InputMethod_TextEditorProxy}.
 * This setting must be completed before **Attach**.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param getTextIndexAtCursorFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetGetTextIndexAtCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetTextIndexAtCursorFunc getTextIndexAtCursorFunc);
/**
 * @brief Sets the {@link OH_TextEditorProxy_ReceivePrivateCommandFunc} function for
 * {@link InputMethod_TextEditorProxy}. This setting must be completed before **Attach**.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param receivePrivateCommandFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetReceivePrivateCommandFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_ReceivePrivateCommandFunc receivePrivateCommandFunc);
/**
 * @brief Sets the {@link OH_TextEditorProxy_SetPreviewTextFunc} function for {@link InputMethod_TextEditorProxy}. This
 * setting must be completed before **Attach**.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param setPreviewTextFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetSetPreviewTextFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_SetPreviewTextFunc setPreviewTextFunc);
/**
 * @brief Sets the {@link OH_TextEditorProxy_FinishTextPreviewFunc} function for {@link InputMethod_TextEditorProxy}.
 * This setting must be completed before **Attach**.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be set. It cannot be **NULL**.
 * @param finishTextPreviewFunc Input parameter, callback to be set to the **proxy**. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetFinishTextPreviewFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_FinishTextPreviewFunc finishTextPreviewFunc);

/**
 * @brief Obtains the {@link OH_TextEditorProxy_GetTextConfigFunc} function from {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param getTextConfigFunc Output pointer, indicating the function pointer obtained from the **proxy**. The memory is
 *     allocated by the caller. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetGetTextConfigFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetTextConfigFunc *getTextConfigFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_InsertTextFunc} function from {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param insertTextFunc Output pointer, indicating the function pointer obtained from the **proxy**. The memory is
 *     allocated by the caller. It cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetInsertTextFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_InsertTextFunc *insertTextFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_DeleteForwardFunc} function from {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param deleteForwardFunc Output pointer, indicating the function pointer obtained from the **proxy**. It cannot be **
 *     NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetDeleteForwardFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_DeleteForwardFunc *deleteForwardFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_DeleteBackwardFunc} function from {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param deleteBackwardFunc Output pointer, indicating the function pointer obtained from the **proxy**. It cannot be *
 *     *NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetDeleteBackwardFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_DeleteBackwardFunc *deleteBackwardFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_SendKeyboardStatusFunc} function from
 * {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param sendKeyboardStatusFunc Output pointer, indicating the function pointer obtained from the **proxy**. It cannot
 *     be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetSendKeyboardStatusFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_SendKeyboardStatusFunc *sendKeyboardStatusFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_SendEnterKeyFunc} function from {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param sendEnterKeyFunc Output pointer, indicating the function pointer obtained from the **proxy**. It cannot be **
 *     NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetSendEnterKeyFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_SendEnterKeyFunc *sendEnterKeyFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_MoveCursorFunc} function from {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param moveCursorFunc Output pointer, indicating the function pointer obtained from the **proxy**. It cannot be **
 *     NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetMoveCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_MoveCursorFunc *moveCursorFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_HandleSetSelectionFunc} function from
 * {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param handleSetSelectionFunc Output pointer, indicating the function pointer obtained from the **proxy**. It cannot
 *     be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetHandleSetSelectionFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_HandleSetSelectionFunc *handleSetSelectionFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_HandleExtendActionFunc} function from
 * {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param handleExtendActionFunc Output pointer, indicating the function pointer obtained from the **proxy**. It cannot
 *     be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetHandleExtendActionFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_HandleExtendActionFunc *handleExtendActionFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_GetLeftTextOfCursorFunc} function from
 * {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param getLeftTextOfCursorFunc Output pointer, indicating the function pointer obtained from the **proxy**. It
 *     cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetGetLeftTextOfCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetLeftTextOfCursorFunc *getLeftTextOfCursorFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_GetRightTextOfCursorFunc} function from
 * {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param getRightTextOfCursorFunc Output pointer, indicating the function pointer obtained from the **proxy**. It
 *     cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetGetRightTextOfCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetRightTextOfCursorFunc *getRightTextOfCursorFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_GetTextIndexAtCursorFunc} function from
 * {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param getTextIndexAtCursorFunc Output pointer, indicating the function pointer obtained from the **proxy**. It
 *     cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetGetTextIndexAtCursorFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_GetTextIndexAtCursorFunc *getTextIndexAtCursorFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_ReceivePrivateCommandFunc} function from
 * {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param receivePrivateCommandFunc Output pointer, indicating the function pointer obtained from the **proxy**. It
 *     cannot be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetReceivePrivateCommandFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_ReceivePrivateCommandFunc *receivePrivateCommandFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_SetPreviewTextFunc} function from {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param setPreviewTextFunc Output pointer, indicating the function pointer obtained from the **proxy**. It cannot be *
 *     *NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetSetPreviewTextFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_SetPreviewTextFunc *setPreviewTextFunc);
/**
 * @brief Obtains the {@link OH_TextEditorProxy_FinishTextPreviewFunc} function from
 * {@link InputMethod_TextEditorProxy}.
 *
 * @param proxy Input pointer to the **TextEditorProxy** instance to be read. It cannot be **NULL**.
 * @param finishTextPreviewFunc Output pointer, indicating the function pointer obtained from the **proxy**. It cannot
 *     be **NULL**.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextEditorProxy_GetFinishTextPreviewFunc(
    InputMethod_TextEditorProxy *proxy, OH_TextEditorProxy_FinishTextPreviewFunc *finishTextPreviewFunc);

/**
 * @brief Configures the execution thread (main thread/IPC thread) for the callbacks of **InputMethod_TextEditorProxy**.
 * This API only controls all callbacks in **InputMethod_TextEditorProxy** except
 * {@link OH_TextEditorProxy_GetTextConfigFunc}. The execution thread of {@link OH_TextEditorProxy_GetTextConfigFunc}
 * is determined by the thread that calls {@link OH_InputMethodController_Attach}, and is not affected by this API. To
 * ensure that **GetTextConfigFunc** also executes on the main thread, make sure that **Attach** is called on the main
 * thread.
 * <br>Usage scenarios: When an app needs to avoid multi-thread concurrency issues, it can switch callbacks to the main
 * thread for execution. When an app requires faster callback response, it can keep callbacks executing on the IPC
 * thread.
 * <br>Use effect: When this API is set to **true**, all callbacks except **GetTextConfigFunc** will be executed on the
 * main thread, avoiding multi-thread concurrency, but time-consuming operations should be avoided inside callbacks.
 * When this API is set to **false**, callbacks are executed on the IPC thread, providing faster response but
 * potentially introducing concurrency issues.
 * <br>Preconditions: The **proxy** must be created through {@link OH_TextEditorProxy_Create} first. It is recommended
 * that you call this API to configure the thread policy before **Attach** is called.
 *
 * @param proxy Input pointer to the **InputMethod_TextEditorProxy** instance to be read. It cannot be **NULL**. If **
 *     NULL** is passed in, **IME_ERR_NULL_POINTER** is returned.
 * @param isCallbackInMainThread Input parameter, thread execution policy. Value range: **true** or **false**. Value
 *     principle: When the value is **true**, the callback is switched to the main thread for execution (used to avoid
 *     multi-thread concurrency issues). Avoid performing time-consuming operations in the callback to prevent main
 *     thread blocking. When the value is **false**, the callback is executed on the IPC thread (multi-thread
 *     concurrency may occur), with faster response.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK}: Success.
 *     <br>{@link IME_ERR_NULL_POINTER}: Returned when **proxy** is **NULL**.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 22
 */
InputMethod_ErrorCode OH_TextEditorProxy_SetCallbackInMainThread(
    InputMethod_TextEditorProxy *proxy, bool isCallbackInMainThread);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_TEXT_EDITOR_PROXY_CAP_H
