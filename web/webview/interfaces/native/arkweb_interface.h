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
 * @brief Provides a unified entry for the native ArkWeb.
 * @kit ArkWeb
 * @library libohweb.so
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */

#ifndef ARKWEB_INTERFACE_H
#define ARKWEB_INTERFACE_H

#include "arkweb_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the native API type of any size.
 *
 * @since 12
 */
typedef struct {
    /** Defines the size information of the native API set. */
    size_t size;
} ArkWeb_AnyNativeAPI;

/**
 * @brief Defines the native API set type.
 *
 * @since 12
 */
typedef enum {
    /** API type related to ArkWeb component. */
    ARKWEB_NATIVE_COMPONENT,
    /** API type related to ArkWeb controller. */
    ARKWEB_NATIVE_CONTROLLER,
    /** API type related to ArkWeb WebMessagePort. */
    ARKWEB_NATIVE_WEB_MESSAGE_PORT,
    /** API type related to ArkWeb WebMessage. */
    ARKWEB_NATIVE_WEB_MESSAGE,
    /** API type related to ArkWeb cookie manager. */
    ARKWEB_NATIVE_COOKIE_MANAGER,
    /**
     * @brief API type related to ArkWeb JavaScript value.
     *
     * @since 18
     */
    ARKWEB_NATIVE_JAVASCRIPT_VALUE,
} ArkWeb_NativeAPIVariantKind;

/**
 * @brief Obtains the native API set of a specified type.
 * @param type Indicates the type of the native API set provided by ArkWeb.
 * @return Return the pointer to the native API abstract object that carries the size.
 *         If the type is incorrect, a null pointer is returned.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
ArkWeb_AnyNativeAPI* OH_ArkWeb_GetNativeAPI(ArkWeb_NativeAPIVariantKind type);


/**
 * @brief Register a scrolling event callback.
 * @param webTag The name of the web component.
 * @param callback The ArkWeb scrolling callback.
 * @param userData The data set by user.
 * @return Returns whether the registration was successful, false indicates failure.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 18
 */
bool OH_ArkWeb_RegisterScrollCallback(
    const char* webTag, ArkWeb_OnScrollCallback callback, void* userData);

#ifdef __cplusplus
};
#endif
#endif // ARKWEB_INTERFACE_H
/** @} */