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
 * @file inputmethod_types_capi.h
 *
 * @brief Defines the types related to the input method.
 *
 * @include <inputmethod/inputmethod_types_capi.h>
 * @library libohinputmethod.so
 * @kit IMEKit
 * @syscap SystemCapability.MiscServices.InputMethodFramework
 * @since 12
 * @version 1.0
 */
#ifndef OHOS_INPUTMETHOD_TYPES_CAPI_H
#define OHOS_INPUTMETHOD_TYPES_CAPI_H
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
/**
 * @brief Enumerates the keyboard status.
 *
 * @since 12
 */
typedef enum InputMethod_KeyboardStatus {
    /**
     * @brief NONE.
     *
     */
    IME_KEYBOARD_STATUS_NONE = 0,
    /**
     * @brief Invisible.
     *
     */
    IME_KEYBOARD_STATUS_HIDE = 1,
    /**
     * @brief Visible.
     *
     */
    IME_KEYBOARD_STATUS_SHOW = 2,
} InputMethod_KeyboardStatus;

/**
 * @brief Enumerates the Enter key types.
 *
 * @since 12
 */
typedef enum InputMethod_EnterKeyType {
    /**
     * @brief Unspecified.
     *
     */
    IME_ENTER_KEY_UNSPECIFIED = 0,
    /**
     * @brief NONE.
     *
     */
    IME_ENTER_KEY_NONE = 1,
    /**
     * @brief Go.
     *
     */
    IME_ENTER_KEY_GO = 2,
    /**
     * @brief Search.
     *
     */
    IME_ENTER_KEY_SEARCH = 3,
    /**
     * @brief Send.
     *
     */
    IME_ENTER_KEY_SEND = 4,
    /**
     * @brief Next.
     *
     */
    IME_ENTER_KEY_NEXT = 5,
    /**
     * @brief Done.
     *
     */
    IME_ENTER_KEY_DONE = 6,
    /**
     * @brief Previous.
     *
     */
    IME_ENTER_KEY_PREVIOUS = 7,
    /**
     * @brief Line break.
     *
     */
    IME_ENTER_KEY_NEWLINE = 8,
} InputMethod_EnterKeyType;

/**
 * @brief Enumerates the moving directions.
 *
 * @since 12
 */
typedef enum InputMethod_Direction {
    /**
     * @brief NONE.
     *
     */
    IME_DIRECTION_NONE = 0,
    /**
     * @brief Upward.
     *
     */
    IME_DIRECTION_UP = 1,
    /**
     * @brief Downward.
     *
     */
    IME_DIRECTION_DOWN = 2,
    /**
     * @brief Leftward.
     *
     */
    IME_DIRECTION_LEFT = 3,
    /**
     * @brief Rightward.
     *
     */
    IME_DIRECTION_RIGHT = 4,
} InputMethod_Direction;

/**
 * @brief Enumerates the types of the extended edit action on the text box.
 *
 * @since 12
 */
typedef enum InputMethod_ExtendAction {
    /**
     * @brief Select all.
     *
     */
    IME_EXTEND_ACTION_SELECT_ALL = 0,
    /**
     * @brief Cut.
     *
     */
    IME_EXTEND_ACTION_CUT = 3,
    /**
     * @brief Copy.
     *
     */
    IME_EXTEND_ACTION_COPY = 4,
    /**
     * @brief Paste.
     *
     */
    IME_EXTEND_ACTION_PASTE = 5,
} InputMethod_ExtendAction;

/**
 * @brief Enumerates the text input types.
 *
 * @since 12
 */
typedef enum InputMethod_TextInputType {
    /**
     * @brief NONE.
     *
     */
    IME_TEXT_INPUT_TYPE_NONE = -1,
    /**
     * @brief Text.
     *
     */
    IME_TEXT_INPUT_TYPE_TEXT = 0,
    /**
     * @brief Multi-line.
     *
     */
    IME_TEXT_INPUT_TYPE_MULTILINE = 1,
    /**
     * @brief Number.
     *
     */
    IME_TEXT_INPUT_TYPE_NUMBER = 2,
    /**
     * @brief Phone number.
     *
     */
    IME_TEXT_INPUT_TYPE_PHONE = 3,
    /**
     * @brief Date.
     *
     */
    IME_TEXT_INPUT_TYPE_DATETIME = 4,
    /**
     * @brief Email address.
     *
     */
    IME_TEXT_INPUT_TYPE_EMAIL_ADDRESS = 5,
    /**
     * @brief URL.
     *
     */
    IME_TEXT_INPUT_TYPE_URL = 6,
    /**
     * @brief Password.
     *
     */
    IME_TEXT_INPUT_TYPE_VISIBLE_PASSWORD = 7,
    /**
     * @brief Numeric password.
     *
     */
    IME_TEXT_INPUT_TYPE_NUMBER_PASSWORD = 8,
    /**
     * @brief Lock screen password.
     *
     */
    IME_TEXT_INPUT_TYPE_SCREEN_LOCK_PASSWORD = 9,
    /**
     * @brief Username.
     *
     */
    IME_TEXT_INPUT_TYPE_USER_NAME = 10,
    /**
     * @brief New password.
     *
     */
    IME_TEXT_INPUT_TYPE_NEW_PASSWORD = 11,
    /**
     * @brief Decimal number.
     *
     */
    IME_TEXT_INPUT_TYPE_NUMBER_DECIMAL = 12,
    /**
     * @brief Verification code.
     *
     * @since 20
     */
    IME_TEXT_INPUT_TYPE_ONE_TIME_CODE = 13,
} InputMethod_TextInputType;

/**
 * @brief Enumerates the private data types.
 *
 * @since 12
 */
typedef enum InputMethod_CommandValueType {
    /**
     * @brief NONE.
     *
     */
    IME_COMMAND_VALUE_TYPE_NONE = 0,
    /**
     * @brief String.
     *
     */
    IME_COMMAND_VALUE_TYPE_STRING = 1,
    /**
     * @brief Boolean.
     *
     */
    IME_COMMAND_VALUE_TYPE_BOOL = 2,
    /**
     * @brief 32-bit signed integer.
     *
     */
    IME_COMMAND_VALUE_TYPE_INT32 = 3,
} InputMethod_CommandValueType;

/**
 * @brief Enumerates the input method error codes.
 *
 * @since 12
 */
typedef enum InputMethod_ErrorCode {
    /**
     * @error Success.
     */
    IME_ERR_OK = 0,

    /**
     * @error Undefined error.
     */
    IME_ERR_UNDEFINED = 1,
    /**
     * @error Parameter check failed.
     */
    IME_ERR_PARAMCHECK = 401,
    /**
     * @error Package management error.
     */
    IME_ERR_PACKAGEMANAGER = 12800001,
    /**
     * @error Input method application error.
     */
    IME_ERR_IMENGINE = 12800002,
    /**
     * @error Text box client error.
     */
    IME_ERR_IMCLIENT = 12800003,
    /**
     * @error Configuration persistence failed. This error code is reported when the configuration fails to be saved.
     */
    IME_ERR_CONFIG_PERSIST = 12800005,
    /**
     * @error Input method controller error.
     */
    IME_ERR_CONTROLLER = 12800006,
    /**
     * @error Input method setter error.
     */
    IME_ERR_SETTINGS = 12800007,
    /**
     * @error Input method manager service error.
     */
    IME_ERR_IMMS = 12800008,
    /**
     * @error Text box unbound.
     */
    IME_ERR_DETACHED = 12800009,
    /**
     * @brief Error code when the current input method is not the default input method preset in the system.
     * @since 26.1.0
     */
    OH_INPUTMETHOD_ERR_NOT_DEFAULT_IME = 12800010,
    /**
     * @brief Error code when the input capability type is not supported.
     * @since 26.1.0
     */
    OH_INPUTMETHOD_ERR_INPUT_CAPABILITY_TYPE_NOT_SUPPORTED = 12800029,
    /**
     * @error Null pointer.
     */
    IME_ERR_NULL_POINTER = 12802000,
    /**
     * @error Query failed.
     */
    IME_ERR_QUERY_FAILED = 12802001,
} InputMethod_ErrorCode;

/**
 * @brief Enumerates the reasons for requesting the keyboard.
 *
 * @since 15
 */
typedef enum InputMethod_RequestKeyboardReason {
    /**
     * @brief No reason.
     *
     */
    IME_REQUEST_REASON_NONE = 0,
    /**
     * @brief Mouse operation.
     *
     */
    IME_REQUEST_REASON_MOUSE = 1,
    /**
     * @brief Touch operation.
     *
     */
    IME_REQUEST_REASON_TOUCH = 2,
    /**
     * @brief Other reasons.
     *
     */
    IME_REQUEST_REASON_OTHER = 20
} InputMethod_RequestKeyboardReason;

/**
 * @brief Pre-screen text underline style enumeration.
 *
 * @since 26.1.0
 */
typedef enum OH_InputMethod_UnderlineStyle {
    /**
     * @brief No underline.
     * @since 26.1.0
     */
    OH_INPUTMETHOD_UNDERLINE_STYLE_NONE = 0,
    /**
     * @brief Solid underline.
     * @since 26.1.0
     */
    OH_INPUTMETHOD_UNDERLINE_STYLE_SOLID = 1,
    /**
     * @brief Wavy lines underline.
     * @since 26.1.0
     */
    OH_INPUTMETHOD_UNDERLINE_STYLE_WAVY = 2,
    /**
     * @brief Dotted underline.
     * @since 26.1.0
     */
    OH_INPUTMETHOD_UNDERLINE_STYLE_DASHED = 3,
} OH_InputMethod_UnderlineStyle;

/**
 * @brief Input capability type enumeration.
 *
 * @since 26.1.0
 */
typedef enum OH_InputMethod_InputCapabilityType {
    /**
     * @brief Set Capability Type to Translation.
     * @since 26.1.0
     */
    OH_INPUTMETHOD_INPUT_CAPABILITY_TYPE_TRANSLATION = 0,
} OH_InputMethod_InputCapabilityType;

#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_TYPES_CAPI_H
