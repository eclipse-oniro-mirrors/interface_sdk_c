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
 * @brief Binds an application to the input method service.
 *
 * @param textEditorProxy Pointer to the {@link InputMethod_TextEditorProxy} instance. The caller needs to manage the **
 *     textEditorProxy** lifecycle. If the calling is successful, the caller cannot release **textEditorProxy** before
 *     the next binding or unbinding call.
 * @param options Pointer to the {@link InputMethod_AttachOptions} instance. This parameter is used to specify the
 *     options of attaching an input method.
 * @param inputMethodProxy Double pointer to the {@link InputMethod_InputMethodProxy} instance. The lifecycle lasts
 *     until the next binding or unbinding call.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_PARAMCHECK} - Parameter error.
 *     <br>{@link IME_ERR_IMCLIENT} - Client error in input method.
 *     <br>{@link IME_ERR_IMMS} - Input method service error.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_InputMethodController_Attach(InputMethod_TextEditorProxy *textEditorProxy,
    InputMethod_AttachOptions *options, InputMethod_InputMethodProxy **inputMethodProxy);

/**
 * @brief Binds an application to the input method service.
 *
 * @param context Pointer to the {@link ArkUI_Context} instance.
 * @param textEditorProxy Pointer to the {@link InputMethod_TextEditorProxy} instance. The caller needs to manage the **
 *     textEditorProxy** lifecycle. If the calling is successful, the caller cannot release **textEditorProxy** before
 *     the next binding or unbinding call.
 * @param options Pointer to the {@link InputMethod_AttachOptions} instance. This parameter is used to specify the
 *     options of attaching an input method.
 * @param inputMethodProxy Double pointer to the {@link InputMethod_InputMethodProxy} instance. The lifecycle lasts
 *     until the next binding or unbinding call.
 * @return An error code.
 *     <br>{@link IME_ERR_OK} - Success.
 *     <br>{@link IME_ERR_PARAMCHECK} - Parameter error.
 *     <br>{@link IME_ERR_IMCLIENT} - Client error in input method.
 *     <br>{@link IME_ERR_IMMS} - Input method service error.
 *     <br>{@link IME_ERR_NULL_POINTER} - An unexpected null pointer.
 *     <br>For details about the error codes, see {@link InputMethod_ErrorCode}.
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
 * @returnReturns a specific error code.
 * <ul>
 * <li>{@link IME_ERR_OK} - Success. </li>
 * <li>{@link IME_ERR_IMMS} - Input method management service error. </li>
 * <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer. </li>
 * <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 * </ul>
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_InputMethodController_GetCurrentInputMethod(
    char **bundleName, uint32_t *bundleNameLength, char **abilityName, uint32_t *abilityNameLength);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_CONTROLLER_CAPI_H
