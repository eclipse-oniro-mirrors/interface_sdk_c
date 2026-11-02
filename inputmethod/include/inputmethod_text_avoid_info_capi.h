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
 * @file inputmethod_text_avoid_info_capi.h
 *
 * @brief Provides methods for creating, destroying, reading, and writing the text box avoidance information objects.
 *
 * @include <inputmethod/inputmethod_text_avoid_info_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_TEXT_AVOID_INFO_CAPI_H
#define OHOS_INPUTMETHOD_TEXT_AVOID_INFO_CAPI_H
#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Information used by the input box to avoid the keyboard.
 *
 * @since 12
 */
typedef struct InputMethod_TextAvoidInfo InputMethod_TextAvoidInfo;

/**
 * @brief Creates an {@link InputMethod_TextAvoidInfo} instance.
 *
 * @param positionY Y coordinate of the text box, in px.
 * @param height Height of the text box, in px.
 * @return If the operation is successful, a pointer to the created {@link InputMethod_TextAvoidInfo} instance is
 *     returned.
 *     <br>If the operation failed, **NULL** is returned, which may be caused by insufficient application address space.
 * @since 12
 */
InputMethod_TextAvoidInfo *OH_TextAvoidInfo_Create(double positionY, double height);
/**
 * @brief Destroys an {@link InputMethod_TextAvoidInfo} instance.
 *
 * @param info Pointer to the {@link InputMethod_TextAvoidInfo} instance to be destroyed.
 * @since 12
 */
void OH_TextAvoidInfo_Destroy(InputMethod_TextAvoidInfo *info);
/**
 * @brief Sets the Y coordinate in {@link InputMethod_TextAvoidInfo}.
 *
 * @param info Pointer to the {@link InputMethod_TextAvoidInfo} instance whose value is to be set.
 * @param positionY Y coordinate, that is, the absolute value of the distance between the text box's top vertex and the
 *     top edge of the physical screen, in px.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_SetPositionY(InputMethod_TextAvoidInfo *info, double positionY);
/**
 * @brief Sets the height in {@link InputMethod_TextAvoidInfo}.
 *
 * @param info Pointer to the {@link InputMethod_TextAvoidInfo} instance whose value is to be set.
 * @param height Height, in px.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_SetHeight(InputMethod_TextAvoidInfo *info, double height);
/**
 * @brief Obtains the Y coordinate from {@link InputMethod_TextAvoidInfo}.
 *
 * @param info Pointer to the {@link InputMethod_TextAvoidInfo} instance whose value is to be obtained.
 * @param positionY Y coordinate, that is, the absolute value of the distance between the text box's top vertex and the
 *     top edge of the physical screen, in px.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_GetPositionY(InputMethod_TextAvoidInfo *info, double *positionY);
/**
 * @brief Obtains the height from {@link InputMethod_TextAvoidInfo}.
 *
 * @param info Pointer to the {@link InputMethod_TextAvoidInfo} instance whose value is to be obtained.
 * @param height Height of the text box, in px.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_GetHeight(InputMethod_TextAvoidInfo *info, double *height);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_TEXT_AVOID_INFO_CAPI_H
