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
 * @brief Defines the shared immutable JSON data object used by the UI perception and control APIs
 * for in-app intelligent agents and UI automation data collection scenarios. JSON is adopted as the
 * mainstream structured format for cross-language and cross-process consumption, as an alternative
 * to a large set of field accessors.
 *
 * @since 26.2.0
 */

/**
 * @file ui_json_wrapper.h
 *
 * @brief Declares the shared JSON data object for APIs such as UI perception and control.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @include <arkui/ui_json_wrapper.h>
 * @library libace_ndk.z.so
 * @kit ArkUI
 * @since 26.2.0
 */

#ifndef ARKUI_NATIVE_UI_JSON_WRAPPER_H
#define ARKUI_NATIVE_UI_JSON_WRAPPER_H

#include <stdint.h>

#include "error_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines an opaque, immutable JSON data object.
 *
 * The object holds a JSON string. It is used both to carry data delivered by the framework (UI
 * sensing) and to carry commands injected by the application (UI control).
 * The JSON object must contain a top-level schemaVersion field for version control and future
 * compatibility. This requirement applies both to JSON supplied by the application and to JSON
 * returned or delivered through callbacks by the framework, including results with no collected
 * content.
 *
 * @since 26.2.0
 */
typedef struct OH_ArkUI_NativeModule_UIJsonWrapper OH_ArkUI_NativeModule_UIJsonWrapper;

/**
 * @brief Creates a JSON data object from a caller-provided JSON string.
 *
 * The provided string is copied into the object. The caller owns the created object and must
 * release it with {@link OH_ArkUI_NativeModule_UIJsonWrapperDestroy} when it is no longer needed.
 *
 * The provided string must represent a valid JSON object with a top-level schemaVersion field.
 * If this field is missing or its value is outside the supported version range, this function
 * returns {@link ARKUI_ERROR_CODE_PARAM_INVALID}; no default version is used. For example:
 * { "schemaVersion": 1, ... }
 *
 * Note: the data string passed to this function remains owned by the caller. Destroying the JSON
 * wrapper object returned by this API does not release the memory pointed to by data on the
 * caller's behalf.
 *
 * @param data [in] Pointer to the JSON string. It must not be NULL and must remain valid for the
 *     duration of the call. The callee does not retain it. The string must contain a valid JSON
 *     object with a supported schemaVersion. An empty string is invalid.
 * @param size [in] Byte length (in bytes) of the JSON string, excluding the terminating '\0'
 *     character. It must equal the actual length of data. If size is inconsistent with the actual
 *     string length, {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param outOwned [out] Receives the created object on success. The caller owns the returned object
 *     and must release it with {@link OH_ArkUI_NativeModule_UIJsonWrapperDestroy}. It must not be
 *     NULL, requires no initialization, and on failure is set to NULL.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter is invalid, data is empty or
 *             does not represent a valid JSON object, or schemaVersion is missing or unsupported.</li>
 *         </ul>
 * @release ui_json_wrapper/OH_ArkUI_NativeModule_UIJsonWrapperDestroy {outOwned}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIJsonWrapperCreate(const char *data, uint32_t size,
    OH_ArkUI_NativeModule_UIJsonWrapper **outOwned);

/**
 * @brief Obtains the JSON string held by the object.
 *
 * The returned string is read-only and terminated by '\0'. It points to memory owned by the JSON
 * object and remains valid until the object is destroyed. The caller must not modify or free the
 * returned string. The JSON object contains a top-level schemaVersion field.
 *
 * @param json [in] The JSON data object. It must not be NULL.
 *     The object is borrowed and must remain valid for the entire call. The callee does not retain it.
 * @return The borrowed JSON string, or NULL if json is NULL.
 * @since 26.2.0
 */
const char *OH_ArkUI_NativeModule_UIJsonWrapperGetData(const OH_ArkUI_NativeModule_UIJsonWrapper *json);

/**
 * @brief Obtains the byte length of the JSON string.
 *
 * The returned length excludes the terminating '\0' character and includes the schemaVersion
 * field in the JSON string.
 *
 * @param json [in] The JSON data object. It must not be NULL.
 *     The object is borrowed and must remain valid for the entire call. The callee does not retain it.
 * @return <ul>
 *     <li>The byte length of the JSON string, excluding the terminating '\0' character.</li>
 *     <li>0 if json is NULL.</li>
 *     </ul>
 * @since 26.2.0
 */
uint32_t OH_ArkUI_NativeModule_UIJsonWrapperGetSize(const OH_ArkUI_NativeModule_UIJsonWrapper *json);

/**
 * @brief Destroys a JSON data object and releases its resources.
 *
 * Passing NULL has no effect. Any pointer returned by
 * {@link OH_ArkUI_NativeModule_UIJsonWrapperGetData} becomes invalid after this call.
 *
 * Note: call this function only on a JSON wrapper object whose ownership you explicitly hold, for
 * example, a wrapper created with {@link OH_ArkUI_NativeModule_UIJsonWrapperCreate}, or a wrapper
 * whose ownership you have explicitly obtained through an ownership transfer function. Do not use
 * this function to release JSON wrapper objects that are constructed and handed out by the system,
 * for example, the object delivered through
 * {@link OH_ArkUI_NativeModule_UIInfoCollectionInteractionJsonCallback}.
 *
 * @param json [in] The JSON data object to destroy. NULL is allowed and has no effect.
 * @since 26.2.0
 */
void OH_ArkUI_NativeModule_UIJsonWrapperDestroy(OH_ArkUI_NativeModule_UIJsonWrapper *json);

/**
 * @brief Enumerated type of the JSON output format.
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief Produces canonical JSON without unnecessary whitespace.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_JSON_COMPACT = 0,
    /**
     * @brief Generates JSON with double-space indentation and line breaks.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_JSON_PRETTY = 1
} OH_ArkUI_NativeModule_UIJsonFormat;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_UI_JSON_WRAPPER_H
/** @} */
