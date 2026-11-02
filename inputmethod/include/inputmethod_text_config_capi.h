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
 * @file inputmethod_text_config_capi.h
 *
 * @brief Provides methods for creating, destroying, reading, and writing the text box configuration information
 * objects.
 *
 * @include <inputmethod/inputmethod_text_config_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_TEXT_CONFIG_CAPI_H
#define OHOS_INPUTMETHOD_TEXT_CONFIG_CAPI_H
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "inputmethod_cursor_info_capi.h"
#include "inputmethod_text_avoid_info_capi.h"
#include "inputmethod_types_capi.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief A struct that configures input behaviors of text boxes. It is used to pass core input rules to the input
 * method framework for input behavior adaptation.
 *
 * @since 12
 */
typedef struct InputMethod_TextConfig InputMethod_TextConfig;

/**
 * @brief Creates an {@link InputMethod_TextConfig} instance.
 *
 * @return If the operation is successful, a pointer to the created {@link InputMethod_TextConfig} instance is returned.
 *     <br>If the operation failed, **NULL** is returned, which may be caused by insufficient application address space.
 * @since 12
 */
InputMethod_TextConfig *OH_TextConfig_Create(void);
/**
 * @brief Destroys an {@link InputMethod_TextConfig} instance.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance to be destroyed.
 * @since 12
 */
void OH_TextConfig_Destroy(InputMethod_TextConfig *config);

/**
 * @brief Sets the text box type.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be set.
 * @param inputType Input type of the text box.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_SetInputType(InputMethod_TextConfig *config, InputMethod_TextInputType inputType);
/**
 * @brief Sets the Enter key type.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be set.
 * @param enterKeyType Enter key type.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_SetEnterKeyType(
    InputMethod_TextConfig *config, InputMethod_EnterKeyType enterKeyType);
/**
 * @brief Sets the text preview feature.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be set.
 * @param supported Whether text preview is supported. **true**: Text preview is supported. **false**: Text preview is
 *     not supported.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_SetPreviewTextSupport(InputMethod_TextConfig *config, bool supported);
/**
 * @brief Sets the selected text area.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be set.
 * @param start Start position of the selected text.
 * @param end End position of the selected text.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_SetSelection(InputMethod_TextConfig *config, int32_t start, int32_t end);
/**
 * @brief Sets the window ID.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be set.
 * @param windowId Window ID of the application bound to the input method.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_SetWindowId(InputMethod_TextConfig *config, int32_t windowId);

/**
 * @brief Sets the placeholder text.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be set.
 * @param placeholder Pointer to a UTF-16 encoded double-byte string. If a null pointer is passed, the placeholder text
 *     is an empty string.
 * @param length Number of elements in the memory to which **placeholder** points, including the null character of the
 *     double-byte string.1. If **length** is **0**, the placeholder text is an empty string.2. The maximum length of
 *     UTF-16 encoding is 255 characters (the null character of the string is not included in the count). If the length
 *     exceeds 255 characters, the extra characters will be truncated.
 * @return {@link InputMethod_ErrorCode}:
 *     <br>**IME_ERR_OK** = **0**: indicates success.
 *     <br>**IME_ERR_NULL_POINTER** = **12802000**: indicates an unexpected null pointer.
 * @since 20
 */
InputMethod_ErrorCode OH_TextConfig_SetPlaceholder(InputMethod_TextConfig *config, const char16_t *placeholder,
    size_t length);

/**
 * @brief Sets the ability name.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be set.
 * @param abilityName Pointer to a UTF-16 encoded double-byte string. If a null pointer is passed, the ability name is
 *     an empty string.
 * @param length Number of elements in the memory to which **abilityName** points, including the null character of the
 *     double-byte string.1. If **length** is **0**, the ability name is set to an empty string.2. The maximum length
 *     of UTF-16 encoding is 127 characters (the null character of the string is not included in the count). If the
 *     length exceeds 127 characters, the extra characters will be truncated.
 * @return {@link InputMethod_ErrorCode}:
 *     <br>**IME_ERR_OK** = **0**: indicates success.
 *     <br>**IME_ERR_NULL_POINTER** = **12802000**: indicates an unexpected null pointer.
 * @since 20
 */
InputMethod_ErrorCode OH_TextConfig_SetAbilityName(InputMethod_TextConfig *config, const char16_t *abilityName,
    size_t length);

/**
 * @brief Set whether the editor supports consuming key events into TextConfig.
 *
 * @param config Represents a pointer to an {@link InputMethod_TextConfig} instance which will be set.
 * @param consumeKeyEvents Indicates whether the editor supports consuming key events.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK} - success.
 *     <br>{@link IME_ERR_NULL_POINTER} - unexpected null pointer.
 *     <br>Specific error codes can be referenced {@link InputMethod_ErrorCode}.
 * @since 26.0.0
 */
InputMethod_ErrorCode OH_TextConfig_SetConsumeKeyEvents(InputMethod_TextConfig *config, bool consumeKeyEvents);

/**
 * @brief Obtains the text box type.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be obtained.
 * @param inputType Pointer to the {@link InputMethod_TextInputType} instance. Input type of the text box.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetInputType(InputMethod_TextConfig *config, InputMethod_TextInputType *inputType);
/**
 * @brief Obtains the Enter key type.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be obtained.
 * @param enterKeyType Pointer to the {@link InputMethod_EnterKeyType} instance. Enter key type of the text box.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetEnterKeyType(
    InputMethod_TextConfig *config, InputMethod_EnterKeyType *enterKeyType);
/**
 * @brief Obtains whether the text preview feature is supported.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be obtained.
 * @param supported Whether text preview is supported. **true**: Text preview is supported. **false**: Text preview is
 *     not supported.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_IsPreviewTextSupported(InputMethod_TextConfig *config, bool *supported);
/**
 * @brief Obtains the cursor information.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be obtained.
 * @param cursorInfo Cursor information.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetCursorInfo(InputMethod_TextConfig *config, InputMethod_CursorInfo **cursorInfo);

/**
 * @brief Obtains the avoidance information.
 *
 * @param config Text configuration information.
 * @param avoidInfo Text box avoidance information.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetTextAvoidInfo(
    InputMethod_TextConfig *config, InputMethod_TextAvoidInfo **avoidInfo);

/**
 * @brief Obtains the selected text area.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be obtained.
 * @param start Start position of the selected text.
 * @param end End position of the selected text.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetSelection(InputMethod_TextConfig *config, int32_t *start, int32_t *end);
/**
 * @brief Obtains the window ID.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be obtained.
 * @param windowId Window ID of the application bound to the input method.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextConfig_GetWindowId(InputMethod_TextConfig *config, int32_t *windowId);

/**
 * @brief Obtains the placeholder text.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be obtained.
 * @param placeholder Pointer to the placeholder text. The memory of this pointer is maintained by the caller.
 * @param length Pointer to the length of the placeholder text, in double bytes. The length includes the null character
 *     of the string.1. As an input parameter, **length** indicates the available length of the memory to which **
 *     placeholder** points. As an output parameter, it indicates the actual length of the placeholder text.2. If **
 *     placeholder** is a null pointer and **length** points to valid memory, **length** will be set to the actual
 *     length of the placeholder text, and an error will be thrown.3. If both **placeholder** and **length** point to
 *     valid memory, but the value of **length** is less than the actual length of the placeholder text, **length**
 *     will be set to the actual length of the placeholder text, and an error will be thrown.
 * @return {@link InputMethod_ErrorCode}:
 *     <br>**IME_ERR_OK** = **0**: indicates success.
 *     <br>**IME_ERR_PARAMCHECK** = **401**: indicates that parameter check failed.
 *     <br>**IME_ERR_NULL_POINTER** = **12802000**: indicates an unexpected null pointer.
 * @since 20
 */
InputMethod_ErrorCode OH_TextConfig_GetPlaceholder(InputMethod_TextConfig *config, char16_t *placeholder,
    size_t *length);

/**
 * @brief Obtains the ability name.
 *
 * @param config Pointer to the {@link InputMethod_TextConfig} instance whose value is to be obtained.
 * @param abilityName Pointer to the ability name. The memory of this pointer is maintained by the caller.
 * @param length Pointer to the length of the ability name, in double bytes. The length includes the null character of
 *     the string.1. As an input parameter, **length** indicates the available length of the memory to which **
 *     abilityName** points. As an output parameter, it indicates the actual length of the ability name.2. If **
 *     abilityName** is a null pointer and **length** points to valid memory, **length** will be set to the actual
 *     length of the ability name, and an error will be thrown.3. If both **abilityName** and **length** point to valid
 *     memory, but the value of **length** is less than the actual length of the ability name, **length** will be set
 *     to the actual length of the ability name, and an error will be thrown.
 * @return {@link InputMethod_ErrorCode}:
 *     <br>**IME_ERR_OK** = **0**: indicates success.
 *     <br>**IME_ERR_PARAMCHECK** = **401**: indicates that parameter check failed.
 *     <br>**IME_ERR_NULL_POINTER** = **12802000**: indicates an unexpected null pointer.
 * @since 20
 */
InputMethod_ErrorCode OH_TextConfig_GetAbilityName(InputMethod_TextConfig *config, char16_t *abilityName,
    size_t *length);

/**
 * @brief Get whether the editor supports consuming key events from TextConfig.
 *
 * @param config Represents a pointer to an {@link InputMethod_TextConfig} instance which will be get from.
 * @param consumeKeyEvents Indicates whether the editor supports consuming key events.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK} - success.
 *     <br>{@link IME_ERR_NULL_POINTER} - unexpected null pointer.
 *     <br>Specific error codes can be referenced {@link InputMethod_ErrorCode}.
 * @since 26.0.0
 */
InputMethod_ErrorCode OH_TextConfig_GetConsumeKeyEvents(InputMethod_TextConfig *config, bool *consumeKeyEvents);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_TEXT_CONFIG_CAPI_H
