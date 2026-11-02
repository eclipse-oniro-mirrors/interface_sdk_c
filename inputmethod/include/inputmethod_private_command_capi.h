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
 * @file inputmethod_private_command_capi.h
 *
 * @brief Provides methods for creating, destroying, reading, and writing private data objects.
 *
 * @include <inputmethod/inputmethod_private_command_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_PRIVATE_COMMAND_CAPI_H
#define OHOS_INPUTMETHOD_PRIVATE_COMMAND_CAPI_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief Represents the private data exchanged between the text box and the input method application.
 *
 * @since 12
 */
typedef struct InputMethod_PrivateCommand InputMethod_PrivateCommand;

/**
 * @brief Creates an {@link InputMethod_PrivateCommand} instance.
 *
 * @param key Key value of the private data.
 * @param keyLength Key length. The total size of all private data and keys in a single operation cannot exceed 32 KB.
 * @return If the operation is successful, a pointer to the created {@link InputMethod_PrivateCommand} instance is
 *     returned.
 *     <br>If the operation failed, **NULL** is returned, which may be caused by insufficient application address space.
 * @since 12
 */
InputMethod_PrivateCommand *OH_PrivateCommand_Create(char key[], size_t keyLength);
/**
 * @brief Destroys an {@link InputMethod_PrivateCommand} instance.
 *
 * @param command Pointer to the {@link InputMethod_PrivateCommand} instance to be destroyed.
 * @since 12
 */
void OH_PrivateCommand_Destroy(InputMethod_PrivateCommand *command);
/**
 * @brief Sets the key value for {@link InputMethod_PrivateCommand}.
 *
 * @param command Pointer to the {@link InputMethod_PrivateCommand} instance to be set.
 * @param key Key value.
 * @param keyLength Key length.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_SetKey(InputMethod_PrivateCommand *command, char key[], size_t keyLength);
/**
 * @brief Sets the value of the Boolean type for {@link InputMethod_PrivateCommand}.
 *
 * @param command Pointer to the {@link InputMethod_PrivateCommand} instance to be set.
 * @param value Boolean value.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_SetBoolValue(InputMethod_PrivateCommand *command, bool value);
/**
 * @brief Sets the value of the integer type for {@link InputMethod_PrivateCommand}.
 *
 * @param command Pointer to the {@link InputMethod_PrivateCommand} instance to be set.
 * @param value Value of the integer type.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_SetIntValue(InputMethod_PrivateCommand *command, int32_t value);
/**
 * @brief Sets the value of the string type for {@link InputMethod_PrivateCommand}.
 *
 * @param command Pointer to the {@link InputMethod_PrivateCommand} instance to be set.
 * @param value Value of the string type.
 * @param valueLength Value length.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_SetStrValue(
    InputMethod_PrivateCommand *command, char value[], size_t valueLength);

/**
 * @brief Obtains the key value from {@link InputMethod_PrivateCommand}.
 *
 * @param command Pointer to the {@link InputMethod_PrivateCommand} instance from which the key value is to be obtained.
 * @param key The lifespan of **key** is consistent with that of **command**. You are advised to copy instead of
 *     directly saving the key address or writing **key**.
 * @param keyLength Key length.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_GetKey(
    InputMethod_PrivateCommand *command, const char **key, size_t *keyLength);
/**
 * @brief Obtains the data type of value from {@link InputMethod_PrivateCommand}.
 *
 * @param command Pointer to the {@link InputMethod_PrivateCommand} instance from which the value is to be obtained.
 * @param type Pointer to the {@link InputMethod_CommandValueType} instance, used to indicate the data type of the
 *     value.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_GetValueType(
    InputMethod_PrivateCommand *command, InputMethod_CommandValueType *type);
/**
 * @brief Obtains the value of the Boolean type from {@link InputMethod_PrivateCommand}.
 *
 * @param command Pointer to the {@link InputMethod_PrivateCommand} instance from which the value is to be obtained.
 * @param value Boolean value.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>{@link IME_ERR_QUERY_FAILED} - Query failed as the command contains no Boolean value.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_GetBoolValue(InputMethod_PrivateCommand *command, bool *value);
/**
 * @brief Obtains the value of the integer type from {@link InputMethod_PrivateCommand}.
 *
 * @param command Pointer to the {@link InputMethod_PrivateCommand} instance from which the value is to be obtained.
 * @param value Value of the integer type.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>{@link IME_ERR_QUERY_FAILED} - Query failed because the command does not contain an integer value.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_GetIntValue(InputMethod_PrivateCommand *command, int32_t *value);
/**
 * @brief Obtains the value of the string type from {@link InputMethod_PrivateCommand}.
 *
 * @param command Pointer to the {@link InputMethod_PrivateCommand} instance from which the value is to be obtained.
 * @param value Value of the string type.
 * @param valueLength The lifespan of **value** is consistent with that of **command**. You are advised to copy instead
 *     of directly saving the value address or writing **value**.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>{@link IME_ERR_QUERY_FAILED} - Query failed because the command does not contain a string value.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_PrivateCommand_GetStrValue(
    InputMethod_PrivateCommand *command, const char **value, size_t *valueLength);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_PRIVATE_COMMAND_CAPI_H
