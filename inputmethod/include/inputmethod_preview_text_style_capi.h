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
 * @addtogroup InputMethod
 * @{
 *
 * @brief InputMethod provides functions to use input methods.
 *
 * @since 12
 */

/**
 * @file inputmethod_preview_text_style_capi.h
 *
 * @brief Provides methods for creating, destroying, and accessing the preview text style object.
 * PreviewTextStyle describes the underline style and color for preview text, used when the input method
 * sets preview text with style. Create/Destroy must be paired.
 * <br>
 * <br>Function: Creates and manages OH_InputMethod_PreviewTextStyle instances, describing the underline style
 * (none/solid/wavy/dashed) and color of preview text. The color format is 0xRRGGBB; the alpha channel (AA)
 * is invalid and will be ignored by the editor.
 * <br>
 * <br>Usage scenario: When the input method app sets preview text with style via the SetPreviewTextWithStyleFunc
 * callback, the system constructs a PreviewTextStyle object and passes it to the app, which reads the style
 * information via Get methods for rendering.
 * 
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @include <inputmethod/inputmethod_preview_text_style_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @since 26.1.0
 */
#ifndef OHOS_INPUTMETHOD_PREVIEW_TEXT_STYLE_CAPI_H
#define OHOS_INPUTMETHOD_PREVIEW_TEXT_STYLE_CAPI_H
#include <stdbool.h>
#include <stdint.h>
#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief OH_InputMethod_PreviewTextStyle is an opaque type of the pre-screen text style, and is used to describe the
 * underline style and color information of the pre-screen text.
 * The caller cannot directly access its internal members. The caller can perform operations only through the function
 * interfaces provided in this header file.
 * <br>
 * <br>Use: Provide style description for the pre-screen text with style for the input method. Contains the following
 * attributes:
 * <br>-underlineStyle: enumerated value. The value is {@link OH_InputMethod_UnderlineStyle}. The default value is
 * {@link OH_INPUTMETHOD_DOWNLINE_SPECIAL_NONE}.
 * <br>- UnderlineColor: The format is 0xRRGGBB. This parameter is valid only when hasUnderlineColor is set to true.
 * Transparency channel(AA) is invalid and will be
 * Ignored by the editor.
 * <br>- Indicates whether to explicitly set the color(hasUnderlineColor): false indicates that the theme color is
 * applied.
 * <br>
 * <br>Lifecycle Management:
 * <br>-Creation mode: The [OH_InputMethod_PreviewTextStyle_Create](#oh_inputmethod_previewtextstyle_create) function is
 * used to create a file. One is returned.
 * Pointer to the new OH_InputMethod_PreviewTextStyle instance. If the creation fails, NULL is returned. The possible
 * cause is that the memory is insufficient.
 * <br>- Destruction mode: Destroy by using the
 * [OH_InputMethod_PreviewTextStyle_Destroy](#oh_inputmethod_previewtextstyle_destroy) function.
 * Pointer to the instance to be destroyed. The pointer cannot be used after being destroyed. You are advised to set the
 * pointer to NULL to avoid misuse.
 * <br>-Pairing relationship: OH_InputMethod_PreviewTextStyle_Create and OH_InputMethod_PreviewTextStyle_Destroy must be
 * used in pairs.
 * The memory must be released through Destroy. Otherwise, memory leakage occurs.
 *
 * @since 26.1.0
 */
typedef struct OH_InputMethod_PreviewTextStyle OH_InputMethod_PreviewTextStyle;

/**
 * @brief Create a new {@link OH_InputMethod_PreviewTextStyle} instance. The default underline style is
 * {@link OH_INPUTMETHOD_DOWNLINE_SHOP_NONE}. The default underline color is 0, and hasUnderlineColor is false.
 * <br>
 * <br>Application scenario: This function is called when you need to construct a pre-screen text style object.
 * <br>
 * <br>Lifecycle management: The returned object must pass the
 * [OH_InputMethod_PreviewTextStyle_Destroy](#oh_inputmethod_previewtextstyle_destroy).
 * Destroy. Create and Destroy must be used in pairs. If the memory is not destroyed, a memory leak occurs.
 *
 * @return If the creation is successful, a pointer to the newly created {@link OH_InputMethod_PreviewTextStyle}
 *     instance is returned. If the creation fails, NULL is returned,
 * Possible failure causes are insufficient memory.
 * @since 26.1.0
 */
OH_InputMethod_PreviewTextStyle *OH_InputMethod_PreviewTextStyle_Create(void);

/**
 * @brief Destroy a {@link OH_InputMethod_PreviewTextStyle} instance. The style pointer cannot be used after being
 * destroyed. You are advised to set the pointer to NULL to avoid misuse.
 * <br>
 * <br>Application scenario: This function is invoked to release memory when the PreviewTextStyle instance is no longer
 * required.
 * <br>
 * <br>Life cycle management: When NULL is input, the function does not perform any processing and does not break down.
 *
 * @param style Input pointer to the {@link OH_InputMethod_PreviewTextStyle} instance to be destroyed. If NULL is
 *     input, the function does not perform any processing.
 * @since 26.1.0
 */
void OH_InputMethod_PreviewTextStyle_Destroy(OH_InputMethod_PreviewTextStyle *style);

/**
 * @brief Sets the underline style of the pre-screen text.
 *
 * @param style Input pointer to the {@link OH_InputMethod_PreviewTextStyle} instance to be set. Cannot be NULL.
 * @param underlineStyle Input parameter in the underline style. For details, see {@link OH_InputMethod_UnderlineStyle}.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK} - indicates success.
 *     <br>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer.
 *     <br>For details about the error code, see {@link InputMethod_ErrorCode}.
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_PreviewTextStyle_SetUnderlineStyle(
    OH_InputMethod_PreviewTextStyle *style, OH_InputMethod_UnderlineStyle underlineStyle);

/**
 * @brief Gets the underline style of the pre-screen text.
 *
 * @param style Input pointer to the {@link OH_InputMethod_PreviewTextStyle} instance to be read. Cannot be NULL.
 * @param underlineStyle Output pointer, which is used to return the underline style. Cannot be NULL.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK} - indicates success.
 *     <br>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer.
 *     <br>For details about the error code, see {@link InputMethod_ErrorCode}.
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_PreviewTextStyle_GetUnderlineStyle(
    OH_InputMethod_PreviewTextStyle *style, OH_InputMethod_UnderlineStyle *underlineStyle);

/**
 * @brief Sets the underline color of the pre-screen text. The color format is 0xRRGGBB. The transparency channel(AA) is
 * invalid and will be ignored by the editor.
 * When this function is called, the underline color is marked as explicitly specified; When
 * {@link OH_InputMethod_PreviewTextStyle_HasUnderlineColor} is called later, its hasUnderlineColor output parameter
 * will be true.
 *
 * @param style Input pointer to the {@link OH_InputMethod_PreviewTextStyle} instance to be set. Cannot be NULL.
 * @param underlineColor Input parameter, underlined, in the format of 0xRRGGBB.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK} - indicates success.
 *     <br>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer.
 *     <br>For details about the error code, see {@link InputMethod_ErrorCode}.
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_PreviewTextStyle_SetUnderlineColor(
    OH_InputMethod_PreviewTextStyle *style, uint32_t underlineColor);

/**
 * @brief Obtains the underline color of the pre-screen text.
 *
 * @param style Input pointer to the {@link OH_InputMethod_PreviewTextStyle} instance to be read. Cannot be NULL.
 * @param underlineColor Output pointer, which is used to return the underline color. The format is 0xRRGGBB. Cannot
 *     be NULL.
 * @returnReturns a specific error code.
 *     <br>{@link IME_ERR_OK} - indicates success.
 *     <br>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer.
 *     <br>For details about the error code, see {@link InputMethod_ErrorCode}.
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_PreviewTextStyle_GetUnderlineColor(
    OH_InputMethod_PreviewTextStyle *style, uint32_t *underlineColor);

/**
 * @brief Obtains whether the underline color is set from {@link OH_InputMethod_PreviewTextStyle}.
 *
 * The result is determined by whether {@link OH_InputMethod_PreviewTextStyle_SetUnderlineColor} has been invoked. If
 * hasUnderlineColor has been called, the output value is true. Otherwise, the output value is false.
 *
 * @param style Input pointer to the {@link OH_InputMethod_PreviewTextStyle} instance to be read. Cannot be NULL.
 * @param hasUnderlineColor Output pointer, which is used to return whether the underline color is set. Cannot be NULL.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK} - indicates success.
 *     <br>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer.
 *     <br>For details about the error code, see {@link InputMethod_ErrorCode}.
 * @since 26.1.0
 */
InputMethod_ErrorCode OH_InputMethod_PreviewTextStyle_HasUnderlineColor(
    OH_InputMethod_PreviewTextStyle *style, bool *hasUnderlineColor);

#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_PREVIEW_TEXT_STYLE_CAPI_H
