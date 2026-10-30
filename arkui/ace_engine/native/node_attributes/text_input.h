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
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Defines a set of TextInput enum and interface.
 *
 * @since 12
 */

/**
 * @file text_input.h
 *
 * @brief Defines enumerations related to **TextInput**, which supports multiple input type configurations (including
 * text, numbers, passwords, emails, and phone numbers),  style customization of the clear button, auto-filling content
 * type settings, and input box style selection. It is applicable to scenarios requiring user interaction input, such
 * as login and registration, form filling, and search input, helping you quickly implement single-line text input that
 * meets service requirements.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @include <arkui/text_input.h>
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_INPUT_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_INPUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the input types of single-line text.
 *
 * @since 12
 */
typedef enum {
    /** Normal input type with no special restrictions. */
    ARKUI_TEXTINPUT_TYPE_NORMAL = 0,
    /** Numeric input type. */
    ARKUI_TEXTINPUT_TYPE_NUMBER = 2,
    /** Phone number input type.<br>It supports input of digits, spaces, +, -, *, #, (, ), with no length limit. */
    ARKUI_TEXTINPUT_TYPE_PHONE_NUMBER = 3,
    /** Email address input type.<br>It supports digits, letters, underscores, decimal points, !, #, $, %, &, ', *, +,
     * -, /, =, ?, ^, `, \{, \|, \}, ~, and @ (only one @ character allowed). The email address format must follow the
     * basic specification: the part before the @ character is the username, and the part after the @ character is the
     * domain name.
     */
    ARKUI_TEXTINPUT_TYPE_EMAIL = 5,
    /** Password input type.<br>By default, the input text is briefly displayed and then changed to dots. Since API
     * version 12, on PCs/2-in-1 devices, the input text is directly displayed as dots.<br>On TV devices, the eye icon
     * is hidden by default at the end of the input box. On other devices, the eye icon is shown by default at the end
     * of the input box.
     */
    ARKUI_TEXTINPUT_TYPE_PASSWORD = 7,
    /** Numeric password input type.<br>By default, the input text is briefly displayed and then changed to dots. Since
     * API version 12, on PCs/2-in-1 devices, the input text is directly displayed as dots.<br>On TV devices, the eye
     * icon is hidden by default at the end of the input box. On other devices, the eye icon is shown by default at the
     * end of the input box.
     */
    ARKUI_TEXTINPUT_TYPE_NUMBER_PASSWORD = 8,
    /** Lock screen password input type.<br>It supports input of digits, letters, underscores, spaces, and special
     * characters. The eye icon is shown at the end of the input box and the input text changes to dots by default.
     * Since API version 12, on wearables, the input text is directly displayed as dots. The password input type does
     * not support the underline style.
     */
    ARKUI_TEXTINPUT_TYPE_SCREEN_LOCK_PASSWORD = 9,
    /** Username input type with no special restrictions.<br>When Password Vault is enabled, usernames can be auto-saved
     * and auto-filled.
     */
    ARKUI_TEXTINPUT_TYPE_USER_NAME = 10,
    /** New password input type.<br>By default, the input text is briefly displayed and then changed to dots. Since API
     * version 12, on PCs/2-in-1 devices, the input text is directly displayed as dots.<br>On TV devices, the eye icon
     * is hidden by default at the end of the input box. On other devices, the eye icon is shown by default at the end
     * of the input box.
     */
    ARKUI_TEXTINPUT_TYPE_NEW_PASSWORD = 11,
    /** Number input type with a decimal point.<br>It supports digits and a decimal point (only one decimal point
     * allowed), and does not support negative numbers (including negative integers and negative decimals).
     */
    ARKUI_TEXTINPUT_TYPE_NUMBER_DECIMAL = 12,
    /**
     * Verification code input type with no special restrictions. In this type, the system input method is shown by
     * default when the component gains focus.
     * @since 20
     */
    ARKUI_TEXTINPUT_TYPE_ONE_TIME_CODE = 14
} ArkUI_TextInputType;

/**
 * @brief Enumerates the styles of the **Cancel** button.
 *
 * @since 12
 */
typedef enum {
    /** The Cancel button is always displayed. */
    ARKUI_CANCELBUTTON_STYLE_CONSTANT = 0,
    /** The Cancel button is always hidden. */
    ARKUI_CANCELBUTTON_STYLE_INVISIBLE,
    /** The Cancel button is displayed when there is text input. */
    ARKUI_CANCELBUTTON_STYLE_INPUT
} ArkUI_CancelButtonStyle;

/**
 * @brief Enumerates autofill types.
 *
 * @since 12
 */
typedef enum {
    /** Username. Password Vault, when enabled, can automatically save and fill in usernames. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_USER_NAME = 0,
    /** Password. Password Vault, when enabled, can automatically save and fill in passwords. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PASSWORD,
    /** New password. Password Vault, when enabled, can automatically generate a new password. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_NEW_PASSWORD,
    /** Full street address. The scenario-based autofill feature, when enabled, can automatically save and fill in full
     * street addresses.
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_FULL_STREET_ADDRESS,
    /** House number. The scenario-based autofill feature, when enabled, can automatically save and fill in house
     * numbers.
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_HOUSE_NUMBER,
    /** District and county. The scenario-based autofill feature, when enabled, can automatically save and fill in
     * districts and counties.
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_DISTRICT_ADDRESS,
    /** City. The scenario-based autofill feature, when enabled, can automatically save and fill in cities. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_CITY_ADDRESS,
    /** Province. The scenario-based autofill feature, when enabled, can automatically save and fill in provinces. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PROVINCE_ADDRESS,
    /** Country. The scenario-based autofill feature, when enabled, can automatically save and fill in countries. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_COUNTRY_ADDRESS,
    /** Full name. The scenario-based autofill feature, when enabled, can automatically save and fill in full names. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PERSON_FULL_NAME,
    /** Last name. The scenario-based autofill feature, when enabled, can automatically save and fill in last names. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PERSON_LAST_NAME,
    /** First name. The scenario-based autofill feature, when enabled, can automatically save and fill in first names.
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PERSON_FIRST_NAME,
    /** Phone number. The scenario-based autofill feature, when enabled, can automatically save and fill in phone
     *  numbers. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PHONE_NUMBER,
    /** Country code. The scenario-based autofill feature, when enabled, can automatically save and fill in country
     *  codes. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PHONE_COUNTRY_CODE,
    /** Phone number with country code. The scenario-based autofill feature, when enabled, can automatically save and
     *  fill in phone numbers with country codes. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_FULL_PHONE_NUMBER,
    /** Email address. The scenario-based autofill feature, when enabled, can automatically save and fill in email
     *  addresses. */
    ARKUI_TEXTINPUT_CONTENT_EMAIL_ADDRESS,
    /** Bank card number. The scenario-based autofill feature, when enabled, can automatically save and fill in bank
     *  card numbers. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_BANK_CARD_NUMBER,
    /** ID card number. The scenario-based autofill feature, when enabled, can automatically save and fill in ID card
     *  numbers. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ID_CARD_NUMBER,
    /** Nickname. The scenario-based autofill feature, when enabled, can automatically save and fill in nicknames. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_NICKNAME,
    /** Address information without street address. The scenario-based autofill feature, when enabled, can automatically
     *  save and fill in address information without street addresses. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_DETAIL_INFO_WITHOUT_STREET,
    /** Standard address. The scenario-based autofill feature, when enabled, can automatically save and fill in standard
     *  addresses. */
    ARKUI_TEXTINPUT_CONTENT_TYPE_FORMAT_ADDRESS,
    /**
     * Passport number. The scenario-based autofill feature, when enabled, can automatically save and fill in passport
     * numbers.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_PASSPORT_NUMBER,
    /**
     * Passport validity period. The scenario-based autofill feature, when enabled, can automatically save and fill in
     * passport validity periods.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_VALIDITY,
    /**
     * Passport place of issue. The scenario-based autofill feature, when enabled, can automatically save and fill in
     * the place of issue for passports.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ISSUE_AT,
    /**
     * Invoice title. The scenario-based autofill feature, when enabled, can automatically save and fill in invoice
     * titles.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ORGANIZATION,
    /**
     * Tax ID. The scenario-based autofill feature, when enabled, can automatically save and fill in tax IDs.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_TAX_ID,
    /**
     * Location. The scenario-based autofill feature, when enabled, can automatically save and fill in locations.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ADDRESS_CITY_AND_STATE,
    /**
     * Flight number. Currently not supported for automatic saving and auto-filling.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_FLIGHT_NUMBER,
    /**
     * Driver's license number. Currently not supported for automatic saving and auto-filling.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_LICENSE_NUMBER,
    /**
     * Driver's license file number. Currently not supported for automatic saving and auto-filling.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_LICENSE_FILE_NUMBER,
    /**
     *  License plate number. The scenario-based autofill feature, when enabled, can automatically save and fill in
     *  license plate numbers.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_LICENSE_PLATE,
    /**
     * Vehicle registration engine number. Currently not supported for automatic saving and auto-filling.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_ENGINE_NUMBER,
    /**
     * Chassis number. Auto-save and auto-fill are not yet supported.
     * @since 18
     */
    ARKUI_TEXTINPUT_CONTENT_TYPE_LICENSE_CHASSIS_NUMBER
} ArkUI_TextInputContentType;

/**
 * @brief Enumerates text input styles.
 *
 * @since 12
 */
typedef enum {
    /** Default style. The caret width is fixed at 1.5 vp, and the caret height is subject to the background height and
     *  font size of the selected text. */
    ARKUI_TEXTINPUT_STYLE_DEFAULT = 0,
    /** Inline input style. The background height of the selected text is the same as the height of the text box. */
    ARKUI_TEXTINPUT_STYLE_INLINE
} ArkUI_TextInputStyle;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_INPUT_H
/** @} */