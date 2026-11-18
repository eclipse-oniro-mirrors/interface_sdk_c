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
 * @brief Text box avoidance information structure, which describes the position and height of the text box on the
 *     physical screen. The input method framework calculates the avoidance area based on positionY and height in
 *     TextAvoidInfo. When the soft keyboard pops up, the edit box can automatically move up or adjust the layout. This
 *     ensures that the input area is not blocked by the keyboard and the input content can be viewed and operated by
 *     users. <br> <br>Use: Serves as a parameter carrier for the edit box to avoid the keyboard area and transmits the
 *     vertical position and height information of the edit box to the input method framework. Input method framework
 *     based on positionY (Y coordinate at the top of the edit box. The value must be greater than or equal to 0.) and
 *     height (height of the edit box. The value must be a valid height value greater than 0.) Determine the complete
 *     vertical range (positionY to positionY+height) of the edit box on the screen, compare it with the screen area
 *     occupied by the keyboard, and calculate whether to avoid and the offset. <br> <br>Application scenario: After the
 *     edit box is bound to the input method service (through OH_InputMethodController_Attach), the edit box client
 *     transfers TextAvoidInfo to the input method framework through InputMethod_TextConfig. When the keyboard pops up,
 *     the input method framework reads the avoidance information, determines whether the edit box is in the keyboard
 *     block area, and triggers the corresponding avoidance adjustment. This structure can also be read by the input
 *     method application to understand the screen position of the edit box to optimize the keyboard layout. <br> <br>
 *     Related functions: <br> | Function | Description | | --- | --- | |
 *     [OH_TextAvoidInfo_Create](capi-inputmethod-text-avoid-info-capi-h.md#oh_textavoidinfo_create) | Creating an
 *     InputMethod_TextAvoidInfo Instance | |
 *     [OH_TextAvoidInfo_Destroy](capi-inputmethod-text-avoid-info-capi-h.md#oh_textavoidinfo_destroy) | Destroying an
 *     InputMethod_TextAvoidInfo Instance | |
 *     [OH_TextAvoidInfo_SetPositionY](capi-inputmethod-text-avoid-info-capi-h. md#oh_textavoidinfo_setpositiony) |
 *     Setting the Y Coordinate Value | |
 *     [OH_TextAvoidInfo_SetHeight](capi-inputmethod-text-avoid-info-capi-h.md#oh_textavoidinfo_setheight) | Setting the
 *     Height Value | |
 *     [OH_TextAvoidInfo_GetPositionY](capi-inputmethod-text-avoid-info-capi-h. md#oh_textavoidinfo_getpositiony) |
 *     Obtaining the Y Coordinate Value | |
 *     [OH_TextAvoidInfo_GetHeight](capi-inputmethod-text-avoid-info-capi-h.md#oh_textavoidinfo_getheight) | Obtaining
 *     the Height Value | |
 *     [OH_TextConfig_GetTextAvoidInfo](capi-inputmethod-text-config-capi-h. md#oh_textconfig_gettextavoidinfo) |
 *     Obtains TextAvoidInfo from TextConfig | <br> <br> Related structures: <br> | Structure | Description | | --- |
 *     --- | | [InputMethod_TextConfig](capi-inputmethod-inputmethod-textconfig.md) | Text box configuration structure.
 *     TextAvoidInfo is contained as its sub-attribute. | <br> <br> Handle and ownership: Only valid handles created by
 *     this API or borrowed handles provided by the framework can be used. Only independently created objects can be
 *     destroyed. The object provided by the callback and the child object view of TextConfig are borrowed objects. The
 *     provider returns IME_ERR_PARAMCHECK for an unregistered or invalid handle. The null parameter still returns an
 *     error according to the original rule. <br>Protection boundary: Life cycle check does not guarantee the thread
 *     safety of object members, nor does it identify all invalid addresses after address reuse. After the object is
 *     destroyed, the pointer should be null. The callback object must not be retained after the callback ends.
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
 * @brief Destroy a {@link InputMethod_TextAvoidInfo} instance to release the memory resources occupied by the instance.
 * <br> <br> Usage scenario: When the TextAvoidInfo instance is no longer used, this function is called to destroy the
 * instance. It must be called after the Create function returns successfully and the instance is no longer referenced
 * by any other object. <br> <br>Lifecycle management: OH_TextAvoidInfo_Create and OH_TextAvoidInfo_Destroy must be used
 * together. Each instance created by Create must have a corresponding Destroy call. Otherwise, memory leakage occurs.
 * After Destroy is called, the original pointer becomes invalid and cannot be used any more. <br> <br>Prerequisites:
 * The info parameter must be a non-null pointer returned by OH_TextAvoidInfo_Create. <br>Only independently created
 * objects are owned by the caller. The TextConfig interface returns a borrowed view and cannot be transferred to this
 * interface. A request to destroy a borrowed view is rejected and the TextConfig to which it belongs is not released.
 * The original pointer cannot be used after it is destroyed. <br> <br> Effect: The memory pointed to by info is
 * released, and the info pointer becomes invalid. Any subsequent access to a destroyed pointer is an undefined
 * behavior.
 * @param info Pointer to the {@link InputMethod_TextAvoidInfo} instance to be destroyed.
 * @since 12
 */
void OH_TextAvoidInfo_Destroy(InputMethod_TextAvoidInfo *info);
/**
 * @brief Sets the Y coordinate in {@link InputMethod_TextAvoidInfo}. The Y coordinate indicates the absolute distance
 * between the vertex of the text box and the upper side of the physical screen. <br> <br>Application scenario: When the
 * position of the edit box changes(for example, the window moves or the layout is adjusted), the Y coordinate in the
 * avoidance information needs to be updated so that the input method framework can recalculate the avoidance area based
 * on the latest position. <br> <br> Prerequisites: The info parameter must be a non-null pointer returned by
 * OH_TextAvoidInfo_Create successfully, or a valid borrowed view returned by TextConfig.
 * @param info Pointer to the {@link InputMethod_TextAvoidInfo} instance whose value is to be set.
 * @param positionY Y coordinate, that is, the absolute value of the distance between the text box's top vertex and the
 *     top edge of the physical screen, in px.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - indicates success. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - The object handle is not registered or invalid. </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer. The info parameter is NULL. </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_SetPositionY(InputMethod_TextAvoidInfo *info, double positionY);
/**
 * @brief Sets the height value in {@link InputMethod_TextAvoidInfo}. The height value represents the vertical pixel
 * size of the edit box on the screen. <br> <br>Application scenario: When the height of the edit box changes(for
 * example, the layout is adjusted or the window is zoomed), the height value in the avoidance information needs to be
 * updated so that the input method framework can recalculate the avoidance area based on the latest height. The
 * calculation of the avoidance area depends on the combination of positionY and height to ensure that the edit box is
 * not blocked when the keyboard is displayed. <br> <br> Prerequisites: The info parameter must be a non-null pointer
 * returned by OH_TextAvoidInfo_Create successfully, or a valid borrowed view returned by TextConfig.
 * @param info Pointer to the {@link InputMethod_TextAvoidInfo} instance whose value is to be set.
 * @param height Height, in px.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK} - indicates success. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - The object handle is not registered or invalid. </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer. The info parameter is NULL. </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_SetHeight(InputMethod_TextAvoidInfo *info, double height);
/**
 * @brief Obtain the Y coordinate value from {@link InputMethod_TextAvoidInfo}. The Y coordinate is the absolute value
 * of the distance between the vertex of the text box and the upper side of the physical screen. <br> <br>Application
 * scenario: When processing the avoidance logic, the input method application needs to obtain the Y coordinate value of
 * the edit box to determine the vertical position of the edit box on the screen and determine whether to adjust the
 * position or layout of the edit box. <br> <br> Prerequisites: The info parameter must be a non-null pointer returned
 * by OH_TextAvoidInfo_Create successfully, or a valid borrowed view returned by TextConfig. The output parameter
 * positionY must be a non-null pointer of the double type, and the memory is allocated by the caller.
 * @param info Pointer to the {@link InputMethod_TextAvoidInfo} instance whose value is to be obtained.
 * @param positionY Y coordinate, that is, the absolute value of the distance between the text box's top vertex and the
 *     top edge of the physical screen, in px.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK}: indicates that the operation is successful and the Y coordinate value has been written to
 *     the memory to which the positionY pointer points. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - The object handle is not registered or invalid. </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer. The info or positionY parameter is NULL. </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_GetPositionY(InputMethod_TextAvoidInfo *info, double *positionY);
/**
 * @brief Obtains the height value from {@link InputMethod_TextAvoidInfo}. The height value represents the vertical
 * pixel size of the edit box on the screen. <br> <br>Application scenario: When processing the avoidance logic, the
 * input method application needs to obtain the height of the edit box and determine the complete vertical range(from
 * positionY to positionY+height) of the edit box on the screen based on the Y coordinate value. In this way, you can
 * determine whether the edit box is blocked by the keyboard. <br> <br> Prerequisites: The info parameter must be a
 * non-null pointer returned by OH_TextAvoidInfo_Create successfully, or a valid borrowed view returned by TextConfig.
 * The output parameter height must be a non-null pointer of the double type, and the memory is allocated by the caller.
 * @param info Pointer to the {@link InputMethod_TextAvoidInfo} instance whose value is to be obtained.
 * @param height Height of the text box, in px.
 * @return Returns a specific error code.
 *     <ul>
 *     <li>{@link IME_ERR_OK}: indicates that the operation is successful and the height value has been written to the
 *     memory to which the height pointer points. </li>
 *     <li>{@link IME_ERR_PARAMCHECK} - The object handle is not registered or invalid. </li>
 *     <li>{@link IME_ERR_NULL_POINTER} - Unexpected null pointer. The info or height parameter is NULL. </li>
 *     <li>For details about the error code, see {@link InputMethod_ErrorCode}. </li>
 *     </ul>
 * @since 12
 */
InputMethod_ErrorCode OH_TextAvoidInfo_GetHeight(InputMethod_TextAvoidInfo *info, double *height);
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_TEXT_AVOID_INFO_CAPI_H
