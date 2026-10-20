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
 * @brief Provides the input method types.
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
     * @brief The keyboard status is none.
     */
    IME_KEYBOARD_STATUS_NONE = 0,
    /**
     * @brief The keyboard status is hide.
     */
    IME_KEYBOARD_STATUS_HIDE = 1,
    /**
     * @brief The keyboard status is show.
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
     * @brief The enter key type is UNSPECIFIED.
     */
    IME_ENTER_KEY_UNSPECIFIED = 0,
    /**
     * @brief The enter key type is NONE.
     */
    IME_ENTER_KEY_NONE = 1,
    /**
     * @brief The enter key type is GO.
     */
    IME_ENTER_KEY_GO = 2,
    /**
     * @brief The enter key type is SEARCH.
     */
    IME_ENTER_KEY_SEARCH = 3,
    /**
     * @brief The enter key type is SEND.
     */
    IME_ENTER_KEY_SEND = 4,
    /**
     * @brief The enter key type is NEXT.
     */
    IME_ENTER_KEY_NEXT = 5,
    /**
     * @brief The enter key type is DONE.
     */
    IME_ENTER_KEY_DONE = 6,
    /**
     * @brief The enter key type is PREVIOUS.
     */
    IME_ENTER_KEY_PREVIOUS = 7,
    /**
     * @brief The enter key type is NEWLINE.
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
     * @brief The direction is NONE.
     */
    IME_DIRECTION_NONE = 0,
    /**
     * @brief The direction is UP.
     */
    IME_DIRECTION_UP = 1,
    /**
     * @brief The direction is DOWN.
     */
    IME_DIRECTION_DOWN = 2,
    /**
     * @brief The direction is LEFT.
     */
    IME_DIRECTION_LEFT = 3,
    /**
     * @brief The direction is RIGHT.
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
     * @brief Select all text.
     */
    IME_EXTEND_ACTION_SELECT_ALL = 0,
    /**
     * @brief Cut selected text.
     */
    IME_EXTEND_ACTION_CUT = 3,
    /**
     * @brief Copy selected text.
     */
    IME_EXTEND_ACTION_COPY = 4,
    /**
     * @brief Paste from paste board.
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
     * @brief The text input type is NONE.
     */
    IME_TEXT_INPUT_TYPE_NONE = -1,
    /**
     * @brief The text input type is TEXT.
     */
    IME_TEXT_INPUT_TYPE_TEXT = 0,
    /**
     * @brief The text input type is MULTILINE.
     */
    IME_TEXT_INPUT_TYPE_MULTILINE = 1,
    /**
     * @brief The text input type is NUMBER.
     */
    IME_TEXT_INPUT_TYPE_NUMBER = 2,
    /**
     * @brief The text input type is PHONE.
     */
    IME_TEXT_INPUT_TYPE_PHONE = 3,
    /**
     * @brief The text input type is DATETIME.
     */
    IME_TEXT_INPUT_TYPE_DATETIME = 4,
    /**
     * @brief The text input type is EMAIL ADDRESS.
     */
    IME_TEXT_INPUT_TYPE_EMAIL_ADDRESS = 5,
    /**
     * @brief The text input type is URL.
     */
    IME_TEXT_INPUT_TYPE_URL = 6,
    /**
     * @brief The text input type is VISIBLE PASSWORD.
     */
    IME_TEXT_INPUT_TYPE_VISIBLE_PASSWORD = 7,
    /**
     * @brief The text input type is NUMBER PASSWORD.
     */
    IME_TEXT_INPUT_TYPE_NUMBER_PASSWORD = 8,
    /**
     * @brief The text input type is SCREEN LOCK PASSWORD.
     */
    IME_TEXT_INPUT_TYPE_SCREEN_LOCK_PASSWORD = 9,
    /**
     * @brief The text input type is USER NAME.
     */
    IME_TEXT_INPUT_TYPE_USER_NAME = 10,
    /**
     * @brief The text input type is NEW PASSWORD.
     */
    IME_TEXT_INPUT_TYPE_NEW_PASSWORD = 11,
    /**
     * @brief The text input type is NUMBER DECIMAL.
     */
    IME_TEXT_INPUT_TYPE_NUMBER_DECIMAL = 12,
    /**
     * @brief The text input type is ONE TIME CODE.
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
     * @brief Value type is NONE.
     */
    IME_COMMAND_VALUE_TYPE_NONE = 0,
    /**
     * @brief Value type is STRING.
     */
    IME_COMMAND_VALUE_TYPE_STRING = 1,
    /**
     * @brief Value type is BOOL.
     */
    IME_COMMAND_VALUE_TYPE_BOOL = 2,
    /**
     * @brief Value type is INT32.
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
     * @error The error code in the correct case.
     */
    IME_ERR_OK = 0,

    /**
     * @error The error code when error is undefined.
     */
    IME_ERR_UNDEFINED = 1,
    /**
     * @error The error code when parameter check failed.
     */
    IME_ERR_PARAMCHECK = 401,
    /**
     * @error The error code when the bundle manager error.
     */
    IME_ERR_PACKAGEMANAGER = 12800001,
    /**
     * @error The error code when input method engine error.
     */
    IME_ERR_IMENGINE = 12800002,
    /**
     * @error The error code when input method client error.
     */
    IME_ERR_IMCLIENT = 12800003,
    /**
     * @error The error code when configuration persistence error.
     *  This error code is reported when the configuration fails to be saved.
     */
    IME_ERR_CONFIG_PERSIST = 12800005,
    /**
     * @error The error code when input method controller error.
     */
    IME_ERR_CONTROLLER = 12800006,
    /**
     * @error The error code when input method setting error.
     */
    IME_ERR_SETTINGS = 12800007,
    /**
     * @error The error code when input method manager service error.
     */
    IME_ERR_IMMS = 12800008,
    /**
     * @error The error code when input method client detached.
     */
    IME_ERR_DETACHED = 12800009,
    /**
     * @error The error code when unexpected null pointer.
     */
    IME_ERR_NULL_POINTER = 12802000,
    /**
     * @error The error code when query failed.
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
     * @brief The request keyboard reason is NONE.
     */
    IME_REQUEST_REASON_NONE = 0,
    /**
     * @brief The request keyboard reason is MOUSE.
     */
    IME_REQUEST_REASON_MOUSE = 1,
    /**
     * @brief The request keyboard reason is TOUCH.
     */
    IME_REQUEST_REASON_TOUCH = 2,
    /**
     * @brief The request keyboard reason is OTHER.
     */
    IME_REQUEST_REASON_OTHER = 20
} InputMethod_RequestKeyboardReason;
#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_INPUTMETHOD_TYPES_CAPI_H