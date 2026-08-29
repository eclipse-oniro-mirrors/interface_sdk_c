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
 * @file inputmethod_cursor_info_capi.h
 *
 * @brief Provides methods for creating, destroying, reading, and writing cursor information objects.
 *
 * @include <inputmethod/inputmethod_cursor_info_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_CURSOR_INFO_CAPI_H
#define OHOS_INPUTMETHOD_CURSOR_INFO_CAPI_H
#include "inputmethod_types_capi.h"
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
/**
 * @brief Represents the cursor information, including the coordinates, width, and height of the cursor.
 *
 *
 * @since 12
 */
typedef struct InputMethod_CursorInfo InputMethod_CursorInfo;

/**
 * @brief Create a new {@link InputMethod_CursorInfo} instance.
 *
 * @param left Absolute value of the distance between the cursor's leftmost point and the left edge of the physical
 * screen, in px.
 * @param top Absolute value of the distance between the cursor's top point and the top edge of the physical screen,
 * in px.
 * @param width The width of the cursor.in px.
 * @param height The height of the cursor.in px.
 * @return If the creation succeeds, a pointer to the newly created {@link InputMethod_CursorInfo}
 * instance is returned. If the creation fails, NULL is returned, possible cause is insufficient memory.
 * @since 12
 */
InputMethod_CursorInfo *OH_CursorInfo_Create(double left, double top, double width, double height);

/**
 * @brief Destroy a {@link InputMethod_CursorInfo} instance.
 *
 * @param cursorInfo Represents a pointer to an {@link InputMethod_CursorInfo} instance which will be destroyed.
 * @since 12
 */
void OH_CursorInfo_Destroy(InputMethod_CursorInfo *cursorInfo);

/**
 * @brief Set cursor info.
 *
 * @param cursorInfo Represents a pointer to an {@link InputMethod_CursorInfo} instance.
 * @param left Absolute value of the distance between the cursor's leftmost point and the left edge of the physical
 *  screen, in px.
 * @param top Absolute value of the distance between the cursor's top point and the top edge of the physical screen,
 *  in px.
 * @param width The width of the cursor.in px.
 * @param height The height of the cursor.in px.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK} - success.
 *     <br>{@link IME_ERR_NULL_POINTER} - unexpected null pointer.
 *     <br>Specific error codes can be referenced {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_CursorInfo_SetRect(
    InputMethod_CursorInfo *cursorInfo, double left, double top, double width, double height);

/**
 * @brief Get cursor info.
 *
 * @param cursorInfo Represents a pointer to an {@link InputMethod_CursorInfo} instance.
 * @param left Absolute value of the distance between the cursor's leftmost point and the left edge of the physical
 *  screen, in px.
 * @param top Absolute value of the distance between the cursor's top point and the top edge of the physical screen,
 *  in px.
 * @param width The width of the cursor.in px.
 * @param height The height of the cursor.in px.
 * @return Returns a specific error code.
 *     <br>{@link IME_ERR_OK} - success.
 *     <br>{@link IME_ERR_NULL_POINTER} - unexpected null pointer.
 *     <br>Specific error codes can be referenced {@link InputMethod_ErrorCode}.
 * @since 12
 */
InputMethod_ErrorCode OH_CursorInfo_GetRect(
    InputMethod_CursorInfo *cursorInfo, double *left, double *top, double *width, double *height);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_CURSOR_INFO_CAPI_H