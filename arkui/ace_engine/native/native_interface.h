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
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file native_interface.h
 *
 * @brief Provides a unified entry for the native module APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_INTERFACE_H
#define ARKUI_NATIVE_INTERFACE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the native API type of any version.
 *
 * @since 12
 */
typedef struct {
    /**
     * @brief Defines the version information of the native API set.
     *
     * Unlike the NDK version, the version field of the NativeNode API indicates the version of its own structure.
     */
    int32_t version;
} ArkUI_AnyNativeAPI;

/**
 * @brief Defines the native API types.
 *
 * @since 12
 */
typedef enum {
    /** API related to UI components. */
    ARKUI_NATIVE_NODE,
    /** API related to dialog boxes. */
    ARKUI_NATIVE_DIALOG,
    /** API related to gestures. */
    ARKUI_NATIVE_GESTURE,
} ArkUI_NativeAPIVariantKind;

/**
 * @brief Defines the version information supported by the ARKUI_NATIVE_NODE type.
 *
 * @since 12
 */
typedef enum {
    /** The ARKUI_NATIVE_NODE type supports the structure {@link ArkUI_NativeNodeAPI_1} of version 1. */
    ARKUI_NATIVE_NODE_VERSION_1 = 1,
} ArkUI_NativeNodeAPIVersion;

/**
 * @brief Obtains the native API set of a specified version.
 *
 * @param type Indicates the type of the native API set provided by ArkUI, for example,
 *        <b>ARKUI_NATIVE_NODE</b> and <b>ARKUI_NATIVE_GESTURE</b>.
 * @param version Indicates the version of the native API structure, which is obtained through the suffix
 *        defined in the structure. For the <b>ARKUI_NATIVE_NODE</b> structure, the version is 1,
 *        For the <b>ARKUI_NATIVE_GESTURE</b> structure, the version is 1
 * @return Returns the pointer to the native API abstract object that carries the version.
 * @code {.cpp}
 * #include<arkui/native_interface.h>
 * #include<arkui/native_node.h>
 *
 * auto anyNativeAPI = OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_NODE, 1);
 * if (anyNativeAPI->version == 1) {
 *     auto basicNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(anyNativeAPI);
 * }
 * auto anyGestureAPI = OH_ArkUI_GetNativeAPI(ARKUI_NATIVE_GESTURE, 1);
 * if (anyNativeAPI->version == 1) {
 *     auto basicGestureApi = reinterpret_cast<ArkUI_NativeGestureAPI_1*>(anyGestureAPI);
 * }
 * @endcode
 * @deprecated This API is deprecated since API version 12.
 * You are advised to use {@link OH_ArkUI_QueryModuleInterface} instead.
 * @since 12
 */
ArkUI_AnyNativeAPI* OH_ArkUI_GetNativeAPI(ArkUI_NativeAPIVariantKind type, int32_t version);

/**
 * @brief Obtains the native module API set of a specified version.
 *
 * @param type Indicates the type of the native API set provided by ArkUI, for example, <b>ARKUI_NATIVE_NODE</b> and
 *        <b>ARKUI_NATIVE_GESTURE</b>.
 * @param version Indicates the version of the native API structure, which is obtained through the version enum
 *        supported by the structure, for example, For the <b>ARKUI_NATIVE_NODE</b> structure, the version is 1,
 *        For the <b>ARKUI_NATIVE_GESTURE</b> structure, the version is 1
 * @return Returns the pointer to the native API abstract object that carries the version.
 * @code {.cpp}
 * #include<arkui/native_interface.h>
 * #include<arkui/native_node.h>
 *
 * auto anyNativeAPI = OH_ArkUI_QueryModuleInterface(ARKUI_NATIVE_NODE, 1);
 * if (anyNativeAPI->version == 1) {
 *     auto nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(anyNativeAPI);
 * }
 * auto anyGestureAPI = OH_ArkUI_QueryModuleInterface(ARKUI_NATIVE_GESTURE, 1);
 * if (anyNativeAPI->version == 1) {
 *     auto basicGestureApi = reinterpret_cast<ArkUI_NativeGestureAPI_1*>(anyGestureAPI);
 * }
 * @endcode
 *
 * @since 12
 */
ArkUI_AnyNativeAPI* OH_ArkUI_QueryModuleInterface(ArkUI_NativeAPIVariantKind type, int32_t version);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_INTERFACE_H
/** @} */
