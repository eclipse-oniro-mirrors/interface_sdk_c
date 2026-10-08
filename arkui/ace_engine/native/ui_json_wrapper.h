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
 * for in-app intelligent agents and UI automation. JSON is adopted as the mainstream structured
 * format for cross-language and cross-process consumption, as an alternative to a large set of
 * field accessors.
 *
 * @since 26.2.0
 */

/**
 * @file ui_json_wrapper.h
 *
 * @brief Declares the shared JSON data object for the UI perception and control APIs.
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
 * sensing) and to carry commands submitted by the application (UI control).
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
 * The provided string should contain a schemaVersion field. If it is absent, or the specified
 * version value is outside the supported range, it is treated as 1, as follows:
 * { "schemaVersion": 1, ... }
 *
 * Note: the data string passed to this function remains owned by the caller. Destroying the JSON
 * wrapper object returned by this API does not release the memory pointed to by data on the
 * caller's behalf.
 *
 * @param data [in] Pointer to the JSON string. It must not be null and must remain valid for the
 *     duration of the call. The callee does not retain it. An empty string is valid and corresponds
 *     to a size of 0.
 * @param size [in] Byte length (in bytes) of the JSON string, excluding the terminating null
 *     character. It must equal the actual length of data. If size is inconsistent with the actual
 *     string length, {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param outOwned [out] Receives the created object on success. The caller owns the returned object
 *     and must release it with {@link OH_ArkUI_NativeModule_UIJsonWrapperDestroy}. It must not be
 *     null, requires no initialization, and on failure is set to null.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter is invalid.</li>
 *         </ul>
 * @release ui_json_wrapper/OH_ArkUI_NativeModule_UIJsonWrapperDestroy {outOwned}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIJsonWrapperCreate(const char *data, uint32_t size,
    OH_ArkUI_NativeModule_UIJsonWrapper **outOwned);

/**
 * @brief Obtains the JSON string held by the object.
 *
 * The returned string is read-only and null-terminated. It points to memory owned by the JSON
 * object and remains valid until the object is destroyed. The caller must not modify or free the
 * returned string.
 *
 * @param json [in] The JSON data object. It must not be null.
 * @return The borrowed JSON string, or null if json is null.
 * @since 26.2.0
 */
const char *OH_ArkUI_NativeModule_UIJsonWrapperGetData(const OH_ArkUI_NativeModule_UIJsonWrapper *json);

/**
 * @brief Obtains the byte length of the JSON string.
 *
 * The returned length excludes the terminating null character. For an empty JSON string, zero is
 * returned.
 *
 * @param json [in] The JSON data object. It must not be null.
 * @return <ul>
 *     <li>The byte length of the JSON string, excluding the terminating null character.</li>
 *     <li>Returns 0 for an empty JSON string.</li>
 *     </ul>
 * @since 26.2.0
 */
uint32_t OH_ArkUI_NativeModule_UIJsonWrapperGetSize(const OH_ArkUI_NativeModule_UIJsonWrapper *json);

/**
 * @brief Destroys a JSON data object and releases its resources.
 *
 * Passing null has no effect. Any pointer returned by
 * {@link OH_ArkUI_NativeModule_UIJsonWrapper_GetData} becomes invalid after this call.
 *
 * Note: call this function only on a JSON wrapper object whose ownership you explicitly hold, for
 * example, a wrapper created with {@link OH_ArkUI_NativeModule_UIJsonWrapper_Create}, or a wrapper
 * whose ownership you have explicitly obtained through an ownership transfer function. Do not use
 * this function to release JSON wrapper objects that are constructed and handed out by the system,
 * for example, the object delivered through
 * {@link OH_ArkUI_NativeModule_UIInfoCollectionInteractionJsonCallback}.
 *
 * @param json [in] The JSON data object to destroy.
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