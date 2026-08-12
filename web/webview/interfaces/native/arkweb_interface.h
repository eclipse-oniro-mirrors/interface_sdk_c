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
 * @addtogroup Web
 * @{
 *
 * @brief Provide the definition of the C interface for the native ArkWeb.
 * @since 12
 */
/**
 * @file arkweb_interface.h
 *
 * @brief `arkweb_interface.h` is the core entry header file of ArkWeb on the native side (C/C++): it defines the basic
 * Native API type {@link ArkWeb_AnyNativeAPI} and the API type enum {@link ArkWeb_NativeAPIVariantKind}, provides the
 *  {@link OH_ArkWeb_GetNativeAPI} interface for obtaining specific Native API structs such as Controller, Component,
 * and CookieManager on demand, and also provides {@link OH_ArkWeb_RegisterScrollCallback} for registering scroll event
 * callbacks of the Web component. When developers need to control Web component behavior in native code (such as
 * executing JavaScript, managing cookies, monitoring component lifecycle or scroll events), they should first obtain
 * the corresponding Native API through this header file, while capabilities such as page rendering and display still
 * need to be provided by the Web component on the ArkTS side.
 *
 * @kit ArkWeb
 * @library libohweb.so
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */

#ifndef ARKWEB_INTERFACE_H
#define ARKWEB_INTERFACE_H

#include <stdbool.h>

#include "arkweb_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ArkWeb_AnyNativeAPI is the basic struct type of ArkWeb Native API, used to uniformly represent pointers to
 * various Native API structs obtained through the {@link OH_ArkWeb_GetNativeAPI} API. This struct contains a size
 * member of the size_t type, which records the size of the current struct.
 *
 * @since 12
 */
typedef struct {
    /**
     * Size of the struct.
     */
    size_t size;
} ArkWeb_AnyNativeAPI;

/**
 * @brief Enumerates the native API types.
 *
 * @since 12
 */
typedef enum {
    /**
     * API type related to Component.
     */
    ARKWEB_NATIVE_COMPONENT,
    /**
     * API type related to Controller.
     */
    ARKWEB_NATIVE_CONTROLLER,
    /**
     * API type related to WebMessagePort.
     */
    ARKWEB_NATIVE_WEB_MESSAGE_PORT,
    /**
     * API type related to WebMessage.
     */
    ARKWEB_NATIVE_WEB_MESSAGE,
    /**
     * API type related to CookieManager.
     */
    ARKWEB_NATIVE_COOKIE_MANAGER,
    /**
     * @brief API type related to ArkWeb JavaScript value.
     *
     * @since 18
     */
    ARKWEB_NATIVE_JAVASCRIPT_VALUE
} ArkWeb_NativeAPIVariantKind;

/**
 * @brief Obtains the corresponding Native API struct based on the API type passed in. It is used in scenarios such as
 * obtaining a Controller in native code to control Web component behavior, obtaining a CookieManager to manage cookies,
 * obtaining a WebMessagePort for message communication, and obtaining a JavaScriptValue to operate JavaScript objects.
 *
 * @param type Type of Native API supported by ArkWeb. Different API types may require different system versions. For
 *     details, see the enum type description.
 *     <br>Note: The returned pointer is managed by the system and does not need to be manually released by the
 *     developer. Multiple calls with the same parameters may return the same pointer. The returned Native API struct
 *     is valid within the lifecycle of the Web component. Ensure thread safety when using it.
 * @return Returns the pointer to the corresponding Native API struct based on the passed-in API type. The first member
 *     of the struct is the size of the current struct. It can be used to access specific Native API functions such as
 *     Controller, Component, and CookieManager. <br> If the passed-in API type is not supported in the current system
 *     version (for example, ARKWEB_NATIVE_JAVASCRIPT_VALUE is unavailable in versions earlier than 18), NULL is
 *     returned.
 * @since 12
 */
ArkWeb_AnyNativeAPI* OH_ArkWeb_GetNativeAPI(ArkWeb_NativeAPIVariantKind type);

/**
 * @brief Registers a callback for the component scroll event. It is used in scenarios such as monitoring user scroll
 * behavior for lazy loading, detecting scroll position for back-to-top functionality, recording user browsing behavior
 * for data analysis, and implementing visual effects during scrolling.
 *
 * @param webTag Name of the **Web** component.
 * @param callback Callback used when a page is scrolled.
 * @param userData Pointer to user-defined data.
 * @return **true** is returned if the operation is successful; otherwise, **false** is returned.
 * @since 18
 */
bool OH_ArkWeb_RegisterScrollCallback(
    const char* webTag, ArkWeb_OnScrollCallback callback, void* userData);

#ifdef __cplusplus
};
#endif
#endif // ARKWEB_INTERFACE_H
/** @} */