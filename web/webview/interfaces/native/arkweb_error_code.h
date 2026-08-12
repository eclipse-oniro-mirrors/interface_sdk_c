/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup Web
 * @{
 *
 * @brief Provides APIs for the ArkWeb errors.
 * @since 12
 */
/**
 * @file arkweb_error_code.h
 *
 * @brief Declares the exception error codes of ArkWeb NDK APIs, which are used to return specific error information
 * when ArkWeb-related API calls fail, helping developers quickly locate and resolve issues. These error codes cover
 * common exception scenarios such as initialization, parameter verification, URL processing, cookie management, and
 * library loading.
 *
 * @kit ArkWeb
 * @library libohweb.so
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
#ifndef ARKWEB_ERROR_CODE_H
#define ARKWEB_ERROR_CODE_H

/**
 * @brief Enumerates the error codes of ArkWeb NDK APIs.
 *
 * @since 12
 */
typedef enum ArkWeb_ErrorCode {
    /**
     * @error Operation successful.
     */
    ARKWEB_SUCCESS = 0,

    /**
     * @error Initialization failure. Check the system environment to ensure that the dependent libraries are installed,
     *        and retry initialization.
     */
    ARKWEB_INIT_ERROR = 17100001,

    /**
     * @error Unknown error. Collect logs and provide feedback.
     */
    ARKWEB_ERROR_UNKNOWN = 17100100,

    /**
     * @error Invalid parameter. Check whether the format, range, and type of the input parameter meet the
     *        API requirements.
     */
    ARKWEB_INVALID_PARAM = 17100101,

    /**
     * @error Failed to register the scheme. Register the scheme before creating the **Web** component.
     */
    ARKWEB_SCHEME_REGISTER_FAILED = 17100102,

    /**
     * @error Invalid URL. Check the URL format or protocol support.
     */
    ARKWEB_INVALID_URL = 17100103,

    /**
     * @error Invalid cookie value. Check the cookie format and validity.
     */
    ARKWEB_INVALID_COOKIE_VALUE = 17100104,

    /*
     * @brief Failed to open the library.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 15
     */
    ARKWEB_LIBRARY_OPEN_FAILURE = 17100105,

    /*
     * @brief The required symbol was not found in the library.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 15
     */
    ARKWEB_LIBRARY_SYMBOL_NOT_FOUND = 17100106,
    /**
     * @error CookieManager not initialized. Call the initialization API to complete the initialization
     *        of CookieManager.
     *
     * @since 20
     */
    ARKWEB_COOKIE_MANAGER_NOT_INITIALIZED = 17100107,
    /**
     * @error Failed to initialize CookieManager. Check the system capability and permission configuration.
     *
     * @since 20
     */
    ARKWEB_COOKIE_MANAGER_INITIALIZE_FAILED = 17100108,

    /**
     * @error Failed to save the cookie. Check whether the storage space is sufficient, whether the write permission is
     *     granted, and whether the cookie value meets the specifications.
     *
     * @since 20
     */
    ARKWEB_COOKIE_SAVE_FAILED = 17100109
} ArkWeb_ErrorCode;

/**
 * @brief Enumerates the error codes for the blankless loading.
 *
 * @since 20
 */

typedef enum ArkWeb_BlanklessErrorCode {
    /**
     * @error Operation successful.
     */
    ARKWEB_BLANKLESS_SUCCESS = 0,

    /**
     * @error Unknown error or internal status error.
     */
    ARKWEB_BLANKLESS_ERR_UNKNOWN = -1,

    /**
     * @error Invalid parameter.
     */
    ARKWEB_BLANKLESS_ERR_INVALID_ARGS = -2,

    /**
     * @error **WebViewController** is not bound to any component.
     */
    ARKWEB_BLANKLESS_ERR_CONTROLLER_NOT_INITED = -3,

    /**
     * @error The key value is not matched. The **OH_NativeArkWeb_SetBlanklessLoadingWithKey** and
     *     **OH_NativeArkWeb_GetBlanklessInfoWithKey** APIs must be used in pair and use the same key value.
     */
    ARKWEB_BLANKLESS_ERR_KEY_NOT_MATCH = -4,

    /**
     * @error When the similarity is low, the system will deem the scene change too abrupt and frame insertion through
     *     the **OH_NativeArkWeb_SetBlanklessLoadingWithKey** API will fail.
     */
    ARKWEB_BLANKLESS_ERR_SIGNIFICANT_CHANGE = -5,

    /**
     * @error This device does not support this feature.
     */
    ARKWEB_BLANKLESS_ERR_DEVICE_NOT_SUPPORT = 801
} ArkWeb_BlanklessErrorCode;

#endif // ARKWEB_ERROR_CODE_H
/** @} */
