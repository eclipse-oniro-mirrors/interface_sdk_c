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
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_INTERFACE_H
#define ARKUI_NATIVE_INTERFACE_H

#include <stdint.h>

#include "error_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the types of native API collections.
 *
 * @since 12
 */
typedef enum {
    /** API related to UI components. For details, see the struct definition in <arkui/native_node.h>. */
    ARKUI_NATIVE_NODE,
    /** API related to dialog boxes. For details, see the struct definition in <arkui/native_dialog.h>. */
    ARKUI_NATIVE_DIALOG,
    /** API related to gestures. For details, see the struct definition in <arkui/native_gesture.h>. */
    ARKUI_NATIVE_GESTURE,
    /** API related to animations. For details, see the struct definition in <arkui/native_animate.h>.*/
    ARKUI_NATIVE_ANIMATE,
    /**
     * API related to multi-threaded UI components. For details, see the {@link struct} definition in
     * {@link native_node.h}.
     * @since 22
     */
    ARKUI_MULTI_THREAD_NATIVE_NODE
} ArkUI_NativeAPIVariantKind;

/**
 * @brief Defines the runtime check types for ArkUI C APIs.
 *
 * Each check type corresponds to a specific improper usage scenario of ArkUI C APIs,
 * used to detect misuse at runtime (such as cross-thread calls, accessing destroyed objects, etc.).
 * You can use {@link OH_ArkUI_NativeModule_SetRuntimeCheckMode} to independently configure
 * a runtime check mode for each check type. The behavior upon check failure is determined by
 * the configured runtime check mode. For available modes, see {@link OH_ArkUI_NativeModule_RuntimeCheckMode}.
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief UI thread check type: Some ArkUI C APIs must be called on the UI thread.
     * This type detects whether these APIs are called from a non-UI thread.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_TYPE_UI_THREAD = 0,
    /**
     * @brief Node disposed check type: Detects whether the ArkUI_NodeHandle passed to a C API
     * has already been disposed.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_TYPE_NODE_DISPOSED = 1,
    /**
     * @brief Checks for concurrent operations on the same Free component tree.
     *
     * This check applies to the multi-threaded UI component APIs obtained with
     * {@link ARKUI_MULTI_THREAD_NATIVE_NODE}. When enabled, a conflict prints diagnostic
     * information and a native stack trace, then immediately terminates the application.
     * Both LOG and CRASH modes terminate the application. Different component trees
     * can still be operated on in parallel.
     * Debug application builds default to CRASH, and release application builds default to DISABLED.
     * Even when this check is disabled, the application must serialize operations on the same Free tree.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_TYPE_MULTI_THREAD = 2
} OH_ArkUI_NativeModule_RuntimeCheckType;

/**
 * @brief Defines the runtime check modes for ArkUI C APIs.
 *
 * All runtime check types use the same set of modes (DISABLED, LOG, CRASH) defined in this enum
 * to determine the behavior upon check failure. That is, each check type can be independently
 * set to one of the following three modes. For
 * {@link OH_ARKUI_NATIVEMODULE_CHECK_TYPE_MULTI_THREAD}, any enabled mode terminates
 * the application when a conflict is detected.
 * The default mode depends on the application's build type:
 * For applications compiled in debug mode (Debug build in DevEco Studio, used for development
 * and debugging), the default is {@link OH_ARKUI_NATIVEMODULE_CHECK_MODE_CRASH}.
 * For applications compiled in release mode (Release build in DevEco Studio, used for production
 * release), the default is {@link OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED}.
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief Disables the specified runtime check. The C API behavior is the same as before the check was introduced.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED = 0,
    /**
     * @brief Prints diagnostic logs (check type, API name, cause, native stack trace) and continues the C API call.
     * For {@link OH_ARKUI_NATIVEMODULE_CHECK_TYPE_MULTI_THREAD}, this mode is treated as
     * {@link OH_ARKUI_NATIVEMODULE_CHECK_MODE_CRASH}.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG = 1,
    /**
     * @brief Prints diagnostic logs and immediately terminates the application.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CHECK_MODE_CRASH = 2
} OH_ArkUI_NativeModule_RuntimeCheckMode;
/**
 * @brief Initializes the C API environment and obtains the native module API collection of the specified type.
 *
 * @param type Type of the native API collection provided by ArkUI, for example, <b>ARKUI_NATIVE_NODE</b> or
 *     <b>ARKUI_NATIVE_GESTURE</b>.
 * @param structName Pointer to the name of a native API struct, which can be obtained by querying the struct
 *     definition in the corresponding header file, for example, <b>ArkUI_NativeNodeAPI_1</b> in <arkui/native_node.h>.
 * @return Pointer to the native API abstraction, which must be cast to the specific type for use.
 * @code {.cpp}
 * #include<arkui/native_interface.h>
 * #include<arkui/native_node.h>
 * #include<arkui/native_gesture.h>
 *
 * auto* anyNativeAPI = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1");
 * if (anyNativeAPI) {
 *     auto nativeNodeApi = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(anyNativeAPI);
 * }
 * auto anyGestureAPI = OH_ArkUI_QueryModuleInterface(ARKUI_NATIVE_GESTURE, "ArkUI_NativeGestureAPI_1");
 * if (anyNativeAPI) {
 *     auto basicGestureApi = reinterpret_cast<ArkUI_NativeGestureAPI_1*>(anyGestureAPI);
 * }
 * @endcode
 *
 * @since 12
 */
void* OH_ArkUI_QueryModuleInterfaceByName(ArkUI_NativeAPIVariantKind type, const char* structName);

/**
 * @brief Obtains the latest error information, including the error codes, API names, and error causes.
 * For details about the error code, see {@link ArkUI_ErrorCode}. When other APIs return an error code, the
 * corresponding error information is saved, and the currently stored error information can be obtained through
 * this API. The returned string is a thread-local global string created by the system, and its content must not be
 * modified. If any editing is required, create a copy of the string content. The information returned by this API
 * may change as versions evolve. It is used only for output to assist in analysis and troubleshooting, and must
 * not be used as a basis for logical judgment. The returned error information does not need to be released manually.
 *
 * @return Pointer to the latest error information, including the error codes, API names, and error causes.
 * @since 26.0.0
 */
const char* OH_ArkUI_NativeModule_GetErrorMessage();

/**
 * @brief Sets the process-level runtime check mode for ArkUI C APIs.
 *
 * This function configures the behavior of a specific runtime check type when misuse is detected.
 * The setting is process-level and remains in effect until the next successful call for the same
 * check type.
 *
 * <b>Thread requirement:</b> This function must be called on the UI thread.
 * Calling it from any other thread will immediately terminate the application without returning.
 * The thread check is performed before parameter validation.
 *
 * <b>Default behavior:</b> If this function is not called for a specific check type,
 * debug application builds default to {@link OH_ARKUI_NATIVEMODULE_CHECK_MODE_CRASH},
 * and release application builds default to {@link OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED}.
 *
 * @param checkType [in] Specifies the runtime check type to configure.
 *     The value is an enum value from {@link OH_ArkUI_NativeModule_RuntimeCheckType}.
 * @param mode [in] Specifies the runtime check mode.
 *     The value is an enum value from {@link OH_ArkUI_NativeModule_RuntimeCheckMode}.
 * @return Return value:
 *     <ul><li>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the setting is updated successfully.
 *     </li><li>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if checkType or mode is invalid.</li></ul>
 *     When an invalid parameter error is returned, the previous setting is retained.
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_SetRuntimeCheckMode(
    OH_ArkUI_NativeModule_RuntimeCheckType checkType, OH_ArkUI_NativeModule_RuntimeCheckMode mode);

/**
 * @brief Initializes the C API environment and obtains the corresponding struct pointer based on the struct type.
 *
 * It applies to the scenario where the native API set type and the API struct type have been determined, and a
 * specific native API struct pointer needs to be obtained to call ArkUI native C APIs. This macro function receives
 * the enumeration parameter <b>nativeAPIVariantKind</b> of the {@link ArkUI_NativeAPIVariantKind} type, the struct
 * type parameter <b>structType</b>, and the struct pointer variable <b>structPtr</b>. <b>structPtr</b> must match
 * <b>structType</b>. This macro function calls {@link OH_ArkUI_QueryModuleInterfaceByName} to initialize the C API
 * environment and obtain the abstract pointer of the native API, converts it to the <b>structType*</b> type, and
 * assigns it to <b>structPtr</b>.
 *
 * @code {.cpp}
 * #include<arkui/native_interface.h>
 * #include<arkui/native_node.h>
 *
 * ArkUI_NativeNodeAPI_1* nativeNodeApi = nullptr;
 * OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nativeNodeApi);
 * @endcode
 *
 * @since 12
 */
#define OH_ArkUI_GetModuleInterface(nativeAPIVariantKind, structType, structPtr)                     \
    do {                                                                                             \
        void* anyNativeAPI = OH_ArkUI_QueryModuleInterfaceByName(nativeAPIVariantKind, #structType); \
        if (anyNativeAPI) {                                                                          \
            structPtr = (structType*)(anyNativeAPI);                                                 \
        }                                                                                            \
    } while (0)

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_INTERFACE_H
/** @} */