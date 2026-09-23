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
 * @brief Provides UI perception capabilities of ArkUI on the native side for in-app intelligent
 * agents and UI automation, enabling observation of user interaction events and hit nodes.
 *
 * @since 26.2.0
 */

/**
 * @file ui_info_collection.h
 *
 * @brief Declares the APIs used by in-app intelligent agents and UI automation to observe UI
 * interaction events and hit nodes.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @include <arkui/ui_info_collection.h>
 * @library libace_ndk.z.so
 * @kit ArkUI
 * @since 26.2.0
 */

#ifndef ARKUI_NATIVE_UI_INFO_COLLECTION_H
#define ARKUI_NATIVE_UI_INFO_COLLECTION_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multimedia/image_framework/image/pixelmap_native.h"

#include "common_type.h"
#include "error_code.h"
#include "ui_json_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the observable UI interaction event types.
 *
 * The values are bit flags. They are used to build the eventMask passed to
 * {@link OH_ArkUI_NativeModule_UIInfoCollection_RegisterInteractionObserver}.
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief No event.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_NONE = 0,
    /**
     * @brief Tap gesture.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_TAP = 1 << 0,
    /**
     * @brief Click.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_CLICK = 1 << 1,
    /**
     * @brief Long press gesture.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_LONG_PRESS = 1 << 2,
    /**
     * @brief Pan gesture.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_PAN = 1 << 3,
    /**
     * @brief Pinch gesture.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_PINCH = 1 << 4,
    /**
     * @brief Rotation gesture.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_ROTATION = 1 << 5,
    /**
     * @brief Swipe gesture.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_SWIPE = 1 << 6,
    /**
     * @brief Unified drag and drop.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_DRAG = 1 << 7,
    /**
     * @brief Raw touch down or up.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_TOUCH = 1 << 8
} OH_ArkUI_NativeModule_UIInfoCollection_InteractionEventType;

/**
 * @brief Callback type for receiving a sensed interaction event.
 *
 * The callback carries a borrowed {@link OH_ArkUI_NativeModule_UIJsonWrapper} object that holds the
 * event payload. The object is valid only within the callback invocation; the callback must not
 * retain or destroy it. All positional coordinates in the payload are relative to the screen
 * (display), in physical pixels (px). The payload's top-level structure is:
 *
 * { "schemaVersion": 1, "type": "<event type>", ... }
 *
 * The event-specific fields are as follows:
 * - Tap or click: id, point, count, fingers.
 * - Long press: id, point, actualDuration (milliseconds), action ("end").
 * - Pan: id, point, direction, action ("start" | "end" | "cancel").
 * - Pinch: id, point (array of [x, y]), fingers, action ("start" | "end" | "cancel"); scale is
 * present only on "end".
 * - Rotation: id, point (array of [x, y]), fingers, action ("start" | "end" | "cancel"); angle
 * (degrees) is present only on "end".
 * - Swipe: id, downPoint (array of [x, y]), upPoint (array of [x, y]), direction, speed,
 * actualSpeed.
 * - Drag: action ("start" | "end"); "start" carries id, point, hostName, actualDuration; "end"
 * carries point, dropResult ("success" | "fail"), id (target, present only on success), hostName.
 * - Touch: action ("down" | "up"), fingerId, point; "down" also carries id (hit node ID).
 *
 * @param json [in] Borrowed JSON object. Valid only during the callback invocation.
 * @param userData [in] Custom user data passed during registration. It can be null. The framework
 *     does not own, dereference, or free it.
 * @since 26.2.0
 */
typedef void (*OH_ArkUI_NativeModule_UIInfoCollectionInteractionJsonCallback)(
    const OH_ArkUI_NativeModule_UIJsonWrapper *json, void *userData);

/**
 * @brief Registers an observer for UI interaction events.
 *
 * The observer receives callbacks only for the event types included in eventMask. Multiple
 * observers can be registered for the same UI instance. Registering the same callback and userData
 * pair again creates an additional independent observer with a new registration ID.
 *
 * Remember to unregister the callback by {@link OH_ArkUI_NativeModule_UIInfoCollectionUnregisterInteractionObserver}
 * when it's not used anymore.
 *
 * @param uiContext [in] Pointer to a UI instance. It must not be null.
 * @param eventMask [in] Bitmask of {@link OH_ArkUI_NativeModule_UIInfoCollection_InteractionEventType}
 *     values to observe, combined with the bitwise OR operator. The supported bits are
 *     OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_TAP through
 *     OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_TOUCH. Bits outside this range are
 *     ignored. If no supported bit is set, {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param registerID [out] Receives the observer registration ID on success. It must not be null,
 *     requires no initialization, and on failure is set to 0.
 * @param callback [in] Callback invoked when a matching event occurs. It must not be null.
 * @param userData [in] Custom user data passed to the callback. It can be null. The framework does
 *     not take ownership of it; the caller must keep it valid until the observer is unregistered.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a required pointer is null or eventMask
 *             contains no supported bit.</li>
 *         <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if the UI context is invalid.</li>
 *         </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIInfoCollectionRegisterInteractionObserver(
    ArkUI_ContextHandle uiContext,
    uint32_t eventMask,
    uint32_t *registerID,
    OH_ArkUI_NativeModule_UIInfoCollectionInteractionJsonCallback callback,
    void *userData);

/**
 * @brief Unregisters an interaction observer.
 *
 * After this call completes, the associated callback is no longer invoked.
 *
 * This function is thread-safe, can be called from any thread, does not block the caller, and is
 * not async-signal-safe.
 *
 * @param registerID [in] Registration ID returned by a successful registration.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if the registration ID is invalid.</li>
 *         </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIInfoCollectionUnregisterInteractionObserver(uint32_t registerID);

/**
 * @brief Declare a UI tree collection request structure.
 *
 * @since 26.2.0
 */
typedef struct OH_ArkUI_NativeModule_UIAgentTreeRequest OH_ArkUI_NativeModule_UIAgentTreeRequest;

/**
 * @brief Enumeration of the collection type of the UI tree.
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief Collects the full UI tree, including invisible, transparent, off-screen, and blocked nodes.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_AGENT_TREE_FULL = 0,
    /**
     * @brief Collects the visible tree after visibility, clipping, off-screen, and occlusion filtering.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_AGENT_TREE_VISIBLE = 1
} OH_ArkUI_NativeModule_UIAgentTreeType;

/**
 * @brief Defines the callback invoked after an asynchronous JSON tree request completes.
 *
 * The callback is invoked exactly once on the UI thread for each accepted request. The callback receives ownership
 * of a non-null JSON object only when errorCode is ARKUI_ERROR_CODE_NO_ERROR. The caller must release the object
 * by calling OH_ArkUI_NativeModule_UIJsonWrapperDestroy.
 *
 * @param context [in] The UI context used to start the request.
 * @param requestId [in] The identifier assigned to the accepted request.
 * @param errorCode [in] The request result.
 * @param json [in] Immutable JSON result. If the request fails, the value is NULL. Otherwise, the control tree is in
 *     the JSON structure. This object needs to be released by the developer after being used.
 * @param userData [in] The caller-provided data passed to OH_ArkUI_NativeModule_UIAgentGetTreeJsonAsync.
 * @release ui_json_wrapper/OH_ArkUI_NativeModule_UIJsonWrapperDestroy {json}.
 * @since 26.2.0
 */
typedef void (*OH_ArkUI_NativeModule_UIAgentJsonCallback)(ArkUI_ContextHandle context, uint64_t requestId, 
    ArkUI_ErrorCode errorCode, OH_ArkUI_NativeModule_UIJsonWrapper *json, void *userData);

/**
 * @brief Create a UI tree collection request.
 * @param treeType [in] The tree type. The value must be a member of OH_ArkUI_NativeModule_UIAgentTreeType.
 * @param request [out] The output request object. The caller must release it by calling
 *     OH_ArkUI_NativeModule_UIAgentTreeRequestDestroy.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the request is created successfully.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if an input or output parameter is invalid.</li>
 *     <li>{@link ARKUI_ERROR_CODE_RESOURCE_EXHAUSTED} if allocation fails.</li>
 *     </ul>
 * @release OH_ArkUI_NativeModule_UIAgentTreeRequestDestroy {request}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestCreate(OH_ArkUI_NativeModule_UIAgentTreeType treeType,
    OH_ArkUI_NativeModule_UIAgentTreeRequest **request);

/**
 * @brief Destroys the UI tree collection request object.
 *
 * Passing NULL has no effect.
 * @param request [in] The request to destroy.
 * @since 26.2.0
 */
void OH_ArkUI_NativeModule_UIAgentTreeRequestDestroy(OH_ArkUI_NativeModule_UIAgentTreeRequest *request);

/**
 * @brief Sets whether pure layout nodes are filtered from the returned tree.
 *
 * Filtering is disabled by default. When enabled, retained descendants of a filtered node are attached to the
 * nearest retained ancestor while preserving their relative order.
 *
 * @param request [in] The request to configure.
 * @param enabled [in] Whether pure layout nodes are filtered.
 * @return <ul>
 *     <li> {@link ARKUI_ERROR_CODE_NO_ERROR} if the option is set successfully.</li>
 *     <li> {@link ARKUI_ERROR_CODE_PARAM_INVALID} if the request is NULL.</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetFilterPureLayoutNodes(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, bool enabled);

/**
 * @brief Sets whether fully occluded nodes are filtered from the returned tree.
 *
 * Filtering is disabled by default and can be enabled only for visible-tree
 * requests. Disabling this option does not disable visibility, clipping,
 * off-screen, or fully transparent node filtering.
 *
 * The occluder opacity threshold is configured separately by
 * {@link OH_ArkUI_NativeModule_UIAgentTreeRequestSetOcclusionOpacityThreshold}.
 * Changing this option does not change that threshold.
 *
 * @param request [in] The request to configure. It must not be NULL.
 * @param enabled [in] true to enable occlusion filtering; false to disable it.
 * @return <ul> 
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the option is set successfully.
 *         Setting false for a full-tree request also succeeds.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if request is NULL.</li>
 *     <li>{@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} if enabled
 *         is true for a full-tree request. The request remains unchanged.
 *         Use a visible-tree request to enable this option.</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetFilterOccludedNodes(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, bool enabled);

/**
 * @brief Sets the minimum final opacity for a node to participate as an occluder.
 *
 * The default value is 1.0. The option is supported only for visible-tree requests. A target node is removed only
 * when the union of qualifying occluder regions fully covers its effective visible region.
 *
 * This threshold will not work if the filter option is not enabled by
 * {@link OH_ArkUI_NativeModule_UIAgentTreeRequestSetFilterOccludedNodes}.
 *
 * @param request [in] UI tree collection request.
 * @param threshold [in] The opacity threshold in the range [0.0, 1.0].
 * @return <ul> 
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the threshold is set successfully.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if the request is NULL.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} if the threshold is outside the valid range.</li>
 *     <li>{@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} if the request is for a full tree.</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetOcclusionOpacityThreshold(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, float threshold);

/**
 * @brief Sets whether additional interaction information is collected.
 *
 * Collection is disabled by default. When enabled, the result includes
 * supported interaction information, such as whether a node is clickable,
 * focusable, or editable. This option does not register event observers
 * or change the interaction behavior of any node.
 *
 * Disabling this option does not remove fields included in the default
 * simplified result. Advanced property collection does not implicitly
 * enable this option or collect fields reserved for this option.
 *
 * @param request [in] The request to configure. It must not be NULL.
 * @param enabled [in] true to collect interaction information; false otherwise.
 * @return <ul> 
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the option is set successfully.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if request is NULL.</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetInteractionInfo(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, bool enabled);

/**
 * @brief Sets whether additional accessibility information is collected.
 *
 * Collection is disabled by default. When enabled, the result includes
 * supported accessibility information, such as accessibility content.
 * This option does not enable accessibility services or change node behavior.
 *
 * Disabling this option does not remove fields included in the default
 * simplified result. Advanced property collection does not implicitly
 * enable this option or collect fields reserved for this option.
 *
 * @param request [in] The request to configure. It must not be NULL.
 * @param enabled [in] true to collect accessibility information; false otherwise.
 * @return <ul> 
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the option is set successfully.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if request is NULL.</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetAccessibilityInfo(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, bool enabled);

/**
 * @brief Sets whether advanced visual properties are collected.
 *
 * Collection is disabled by default. When enabled, the result additionally
 * includes supported properties describing directly perceivable appearance,
 * such as visual styles and displayed states.
 *
 * Properties already included in the default simplified result are not
 * duplicated. Fields reserved for interaction or accessibility collection
 * are excluded from this property group, regardless of those options.
 * Internal diagnostic properties are never included.
 *
 * This option is independent of advanced functional property collection
 * and does not change which nodes are retained in the tree.
 *
 * @param request [in] The request to configure. It must not be NULL.
 * @param enabled [in] true to collect advanced visual properties; false otherwise.
 * @return <ul> 
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the option is set successfully.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if request is NULL.</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetCollectVisualProperties(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, bool enabled);

/**
 * @brief Sets whether advanced functional properties are collected.
 *
 * Collection is disabled by default. When enabled, the result additionally
 * includes supported properties describing developer-configured component
 * behavior and functional capabilities.
 *
 * Properties already included in the default simplified result are not
 * duplicated. Fields reserved for interaction or accessibility collection
 * are excluded from this property group, regardless of those options.
 * Internal diagnostic properties are never included.
 *
 * This option is independent of advanced visual property collection
 * and does not change which nodes are retained in the tree.
 *
 * @param request [in] The request to configure. It must not be NULL.
 * @param enabled [in] true to collect advanced functional properties; false otherwise.
 * @return <ul> 
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the option is set successfully.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if request is NULL.</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetCollectFunctionalProperties(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, bool enabled);

/**
 * @brief Collects a UI tree synchronously and returns it as JSON.
 *
 * This function must be called on the UI thread. The result contains at most 5000 nodes and must not exceed 5 MiB.
 * The size limit is measured using canonical compact JSON. If pretty output itself exceeds 5 MiB, the request also
 * fails. No partial JSON is returned.
 *
 * @param context [in] The UI context whose tree is collected.
 * @param request [in] The collection request.
 * @param format [in] The JSON output format.
 * @param json [out] The output immutable JSON object. The caller must release it by calling
 *     OH_ArkUI_NativeModule_UIJsonWrapperDestroy.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if collection succeeds.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter or format is invalid.</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if the context is invalid.</li>
 *     <li>{@link ARKUI_ERROR_CODE_NODE_ON_INVALID_THREAD} if called outside the UI thread.</li>
 *     <li>{@link ARKUI_ERROR_CODE_RESULT_TOO_LARGE} if a result limit is exceeded.</li>
 *     <li>{@link ARKUI_ERROR_CODE_RESOURCE_EXHAUSTED} if allocation fails.</li>
 *     <li>{@link ARKUI_ERROR_CODE_INTERNAL_ERROR} if another internal failure occurs.</li>
 *     </ul>
 * @release ui_json_wrapper/OH_ArkUI_NativeModule_UIJsonWrapperDestroy {json}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentGetTreeJson(ArkUI_ContextHandle context,
    const OH_ArkUI_NativeModule_UIAgentTreeRequest *request,
    OH_ArkUI_NativeModule_UIJsonFormat format,
    OH_ArkUI_NativeModule_UIJsonWrapper **json);

/**
 * @brief Initiate an asynchronous UI tree collection request. Receive the collection through asynchronous callback.
 * This function must be called on the UI thread. function copies the request and format before returning, so
 * The caller can destroy or reuse the request immediately after the call. Each accepted request is completed only once
 * On the UI thread.
 * @param context [in] The UI context whose tree is collected.
 * @param request [in] The collection request.
 * @param format [in] The JSON output format.
 * @param callback [in] The completion callback. On success, the callback receives ownership of the JSON object and must
 *     release it by calling OH_ArkUI_NativeModule_UIJsonWrapperDestroy.
 * @param userData [in] The caller-provided data passed to the callback.
 * @param requestId [out] The output identifier for the accepted request.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the request is accepted.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter or format is invalid.</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if the context is invalid.</li>
 *     <li>{@link ARKUI_ERROR_CODE_NODE_ON_INVALID_THREAD} if called outside the UI thread.</li>
 *     <li>{@link ARKUI_ERROR_CODE_COMMAND_UNFINISHED} if last request unfinished.</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentGetTreeJsonAsync(ArkUI_ContextHandle context,
    const OH_ArkUI_NativeModule_UIAgentTreeRequest *request,
    OH_ArkUI_NativeModule_UIJsonFormat format,
    OH_ArkUI_NativeModule_UIAgentJsonCallback callback, void *userData, uint64_t *requestId);

/**
 * @brief Synchronously collects the text on the current ArkUI page and outputs the text in JSON format. Each JSON item
 * contains an integer "id".
 * Recognize the control, the rectangular "rect" relative to the target window, and the text content
 * The string "content". After using the result, use OH_ArkUI_NativeModule_UIJsonWrapperDestroy to free up the result
 * memory.
 * The function must be called on the UI thread. The output format is as follows:
 * @param uiContext [in] Context of the target UI instance for text collection
 * @param pageText [out] output slot, initialized to NULL by the caller.
 *     A valid slot is set to NULL on failure; an empty page still returns a
 *     wrapper.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} on success.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if pageText is NULL.</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if uiContext is NULL or no longer valid.</li>
 *     <li>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if the native implementation is unavailable.</li>
 *     <li>{@link ARKUI_ERROR_CODE_INTERNAL_ERROR} if no current page exists, the JSON payload cannot be represented
 *     by uint32_t size, or collection/serialization fails.</li>
 *     </ul>
 * @release ui_json_wrapper/OH_ArkUI_NativeModule_UIJsonWrapperDestroy {pageText}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentGetPageText(
    ArkUI_ContextHandle uiContext, OH_ArkUI_NativeModule_UIJsonWrapper** pageText);

/**
 * @brief Declare the ArkUI content change event structure.
 * @since 26.2.0
 */
typedef struct OH_ArkUI_NativeModule_UIContentChangeEvent OH_ArkUI_NativeModule_UIContentChangeEvent;

/**
 * @brief UI Content Change Event Type Enumeration
 * @since 26.2.0
 */
typedef enum OH_ArkUI_NativeModule_UIContentChangeEventCategory {
    /**
     * @brief Page switch events, including Navigation, Router, Swiper, and Tabs switchover events.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_CATEGORY_PAGE = 1U << 0,
    /**
     * @brief Scroll events.
     *
     * @since 26.2.0
     */
     */
    OH_ARKUI_NATIVEMODULE_EVENT_CATEGORY_SCROLL = 1U << 1,
    /**
     * @brief Overlay events.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_CATEGORY_OVERLAY = 1U << 2,
    /**
     * @brief All supported event categories.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_CATEGORY_ALL = ~0U
} OH_ArkUI_NativeModule_UIContentChangeEventCategory;

/**
 * @brief UI Content Change Event Ignore Enumeration
 * @since 26.2.0
 */
typedef enum OH_ArkUI_NativeModule_UIContentChangeIgnoreType {
    /**
     * @brief Scroll by events.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CONTENTCHANGE_IGNORE_SCROLLBY = 1U << 0,
    /**
     * @brief Scroll to events.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CONTENTCHANGE_IGNORE_SCROLLTO = 1U << 1,
    /**
     * @brief Toast events.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CONTENTCHANGE_IGNORE_TOAST = 1U << 2
} OH_ArkUI_NativeModule_UIContentChangeIgnoreType;

/**
 * @brief Enumerates ArkUI state change event types.
 *
 * @since 26.2.0
 */
typedef enum OH_ArkUI_NativeModule_UIContentChangeEventType {
    /**
     * @brief Start of page change.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_PAGE_CHANGE_START = 0,
    /**
     * @brief End of page change
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_PAGE_CHANGE_END = 1,
    /**
     * @brief Start of scrolling events
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_SCROLL_START = 2,
    /**
     * @brief A scroll interaction and any following inertial scrolling have ended.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_SCROLL_END = 3,
    /**
     * @brief An overlay has finished appearing.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_OVERLAY_SHOW = 4,
    /**
     * @brief An overlay has finished disappearing.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_OVERLAY_HIDE = 5,
    /**
     * @brief A swiper interaction has started.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_SWIPER_START = 6,
    /**
     * @brief A swiper interaction has completed, including its transition animation if exists.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_SWIPER_END = 7,
    /**
     * @brief The Swiper switchover event returns to the start index.
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_SWIPER_CANCEL = 8,
    /**
     * @brief Tabs Start Event
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_TABS_START = 9,
    /**
     * @brief Tabs End Event
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_TABS_END = 10,
    /**
     * @brief Cancel the event after the Tabs switch starts. Rebound to the index after the start
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_TABS_CANCEL = 11
} OH_ArkUI_NativeModule_UIContentChangeEventType;

/**
 * @brief Defines the callback invoked for a registered ArkUI state change event.
 *
 * The callback runs on the user interface thread associated with the registered context. The event snapshot is
 * immutable and valid only until this callback returns. ArkUI borrows but does not access or release userData.
 *
 * @param event [in] Pointer to the immutable event snapshot.
 * @param userData [in] Pointer supplied when the callback was registered. The pointer can be NULL.
 * @since 26.2.0
 */
typedef void (*OH_ArkUI_NativeModule_UIContentChangeEventCallback)(
    const OH_ArkUI_NativeModule_UIContentChangeEvent* event, void* userData);

/**
 * @brief Registers to the selected ArkUI state change event categories for a user interface context.
 *
 * Each successful call creates an independent subscription. The returned ID is nonzero and unique within the
 * context. The callback is invoked synchronously on the context's user interface thread. ArkUI borrows uiContext
 * and userData and does not release either value. If the operation fails, subscriptionId is not modified.
 * This function must be called on the UI thread; calling it from a non-UI thread will abort the process.
 *
 * @param uiContext [in] User interface context to observe. The handle must remain valid for the subscription.
 * @param withStart [in] Whether to report start events. When set to true, start events (such as page change start and
 *     scroll start) are reported; when set to false, only end events are reported.
 * @param eventMask [in] Bitwise OR combination of {@link OH_ArkUI_NativeModule_UIContentChangeEventCategory} values.
 *     Must not be zero. The {@link OH_ARKUI_NATIVEMODULE_EVENT_CATEGORY_SCROLL} category does
 *     not differentiate between scroll sub-types. Set the corresponding
 *     {@link OH_ARKUI_NATIVEMODULE_CONTENTCHANGE_IGNORE_SCROLLTO} or
 *     {@link OH_ARKUI_NATIVEMODULE_CONTENTCHANGE_IGNORE_SCROLLBY} bit in ignoreMask to ignore those events.
 * @param ignoreMask [in] Bitwise OR combination of {@link OH_ArkUI_NativeModule_UIContentChangeIgnoreType} values.
 * @param userData [in] User-defined data passed to the callback. The pointer can be NULL and owned by the caller.
 * @param callback [in] Callback invoked for matching events. The callback must not be NULL.
 * @param subscriptionId [out] Pointer to the nonzero subscription ID written when the operation succeeds.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if uiContext is NULL or no longer active.</li>
 *     <li>{@link ARKUI_ERROR_CODE_CALLBACK_INVALID} if callback is NULL.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if eventMask or subscriptionId is invalid.</li>
 *     <li>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if the native C API is not initialized.</li></ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_RegisterUIContentChangeEvent(
    ArkUI_ContextHandle uiContext, bool withStart, uint32_t eventMask, uint32_t ignoreMask, void* userData, 
    OH_ArkUI_NativeModule_UIContentChangeEventCallback callback,
    uint64_t* subscriptionId);

/**
 * @brief Unregisters an active ArkUI state change event subscription from a user interface context.
 *
 * After this function returns successfully, no later event invokes the removed subscription. The caller can then
 * release its userData. Unsubscribing from a callback does not change the callback batch currently being dispatched.
 * This function must be called on the UI thread; calling it from a non-UI thread will abort the process.
 *
 * @param uiContext [in] User interface context that owns the subscription.
 * @param subscriptionId [in] Nonzero ID of an active subscription owned by uiContext.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} if uiContext is NULL or no longer active.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if subscriptionId is zero, unknown, already removed.</li>
 *     <li>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} if the native C API is not initialized.</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UnRegisterUIContentChangeEvent(
    ArkUI_ContextHandle uiContext, uint64_t subscriptionId);

/**
 * @brief Obtains the event type from an ArkUI state change event snapshot.
 *
 * @param event [in] Pointer to the event snapshot. The pointer is valid only while the callback is running.
 * @param type [out] Pointer to the event type written when the operation succeeds.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if event or type is NULL.</li></ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIContentChangeEventGetType(
    const OH_ArkUI_NativeModule_UIContentChangeEvent* event, OH_ArkUI_NativeModule_UIContentChangeEventType* type);

/**
 * @brief Obtains the monotonic timestamp of an ArkUI state change event snapshot.
 *
 * The timestamp is captured at the event completion point, is expressed in nanoseconds, and is not wall-clock time.
 *
 * @param event [in] Pointer to the event snapshot. The pointer is valid only while the callback is running.
 * @param nanoTimestamp [out] Pointer to the monotonic timestamp in nanoseconds written when the operation succeeds.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if event or nanoTimestamp is NULL.</li></ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIContentChangeEventGetTimestamp(
    const OH_ArkUI_NativeModule_UIContentChangeEvent* event, uint64_t* nanoTimestamp);

/**
 * @brief Obtains the user interface context associated with an ArkUI state change event snapshot.
 *
 * The returned handle is borrowed, and the caller must not release it or use it after the callback returns.
 *
 * @param event [in] Pointer to the event snapshot. The pointer is valid only while the callback is running.
 * @param uiContext [out] Pointer to the borrowed user interface context handle written when the operation succeeds.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if event or uiContext is NULL.</li></ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIContentChangeEventGetContext(
    const OH_ArkUI_NativeModule_UIContentChangeEvent* event, ArkUI_ContextHandle* uiContext);

/**
 * @brief Obtains the content change event details as a JSON wrapper from an ArkUI state change event snapshot.
 *
 * The JSON output includes the content change type, trigger node, target node, overlay type, and an optional
 * sub-tree dump depending on the event category:
 *
 * Page events identify the target page. Scroll events identify the scrolling node. Overlay events identify
 * overlay node and provide the overlay type (such as "dialog"). The trigger node is the node that initiated the
 * content change; it is available for overlay events and general start/end scenarios, and is NULL for page and
 * scroll events when no trigger node can be exposed. The operation succeeds and writes an empty JSON wrapper when
 * no target node can be exposed. The handles referenced in the JSON wrapper are borrowed and must not be released
 * or used after the callback returns.
 *
 * @param event [in] Pointer to the event snapshot. The pointer is valid only while the callback is running.
 * @param json [out] Pointer to the {@link OH_ArkUI_NativeModule_UIJsonWrapper} that receives the content change event
 *     details. The caller must not release the wrapper or use it after the callback returns.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if event or json is NULL.</li></ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIContentChangeEventGetContentChangeEventJson(
    const OH_ArkUI_NativeModule_UIContentChangeEvent* event, const OH_ArkUI_NativeModule_UIJsonWrapper** json);

/**
 * @brief ArkUI image acquisition result structure declaration
 * @since 26.2.0
 */
typedef struct OH_ArkUI_NativeModule_ImageCollection OH_ArkUI_NativeModule_ImageCollection;

/**
 * @brief Defines the callback used to return the result of collecting images of ArkUI nodes.
 *
 * The framework invokes this callback exactly once on the UI thread for each accepted request.
 * When <b>errorCode</b> is {@link ARKUI_ERROR_CODE_NO_ERROR}, the framework transfers ownership of the non-<b>null</b>
 * <b>collection</b> to the caller. When <b>errorCode</b> is {@link ARKUI_ERROR_CODE_INTERNAL_ERROR} or
 * {@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID}, <b>collection</b> is <b>null</b>.
 *
 * The framework returns <b>userData</b> unchanged without dereferencing,
 * copying, or releasing the object it points to. The caller must keep that
 * object valid until the callback has finished using it.
 *
 * @param errorCode [in] Indicates the overall request result.
 *     <ul<li>>{@link ARKUI_ERROR_CODE_NO_ERROR} indicates successful collection.</li>
 *     <li>{@link ARKUI_ERROR_CODE_INTERNAL_ERROR} indicates an internal collection failure.</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} context became invalid after the request was accepted.</li></ul>
 * @param collection [in] Indicates the result collection. The value is non-<b>null</b> for overall success and
 *     <b>null</b> for an overall error.
 * @param userData [in] Indicates the caller-defined context pointer. The value can be <b>null</b>.
 * @release OH_ArkUI_NativeModule_ImageCollection_Destroy {collection}
 * @since 26.2.0
 */
typedef void (*OH_ArkUI_NativeModule_ImageCollectionCallback)(ArkUI_ErrorCode errorCode,
    OH_ArkUI_NativeModule_ImageCollection* collection, void* userData);

/**
 * @brief Asynchronously collects images for specified ArkUI node IDs.
 *
 * The framework accepts from <b>0</b> to <b>20</b> unique node IDs in one
 * request and copies the <b>nodeIds</b> array before this function returns.
 * The framework accepts a request with <b>count</b> equal to <b>0</b> and
 * returns a non-<b>null</b> empty collection through the callback.
 *
 * Each accepted node ID has one result in the collection, including a result
 * for a node ID that cannot be found or whose image cannot be captured. An
 * <b>Image</b> node returns its complete source <b>PixelMap</b> when available
 * and otherwise falls back to capturing the rendered content within the node
 * bounds. A non-<b>Image</b> node uses the same node-bounds capture behavior.
 * A node does not need to be visible.
 *
 * If the ArkUI node corresponding to a requested node ID cannot be found, the
 * corresponding collection item reports
 * <b>ARKUI_ERROR_CODE_PARAM_INVALID</b>; the caller should check the node ID.
 * A capture timeout reports
 * <b>ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT</b>; the caller can retry the
 * request. Another internal capture failure reports
 * <b>ARKUI_ERROR_CODE_INTERNAL_ERROR</b> for that item; the caller can retry
 * the request after handling the failure. An item failure does not change the
 * overall successful request result.
 *
 * The caller can call this function from any thread. For each accepted
 * request, the framework invokes <b>callback</b> exactly once on the UI thread
 * associated with <b>context</b>. Concurrent requests are independent, and the
 * framework does not guarantee their callback order.
 *
 * @param context [in] Indicates the ArkUI context used to process the request.
 *     The parameter must not be <b>null</b>.
 * @param nodeIds [in] Indicates the first element of an array containing
 *     <b>count</b> unique ArkUI node IDs. The parameter must not be NULL.
 * @param count [in] Indicates the number of node IDs. The valid range is (0, 20]
 * @param callback [in] Indicates the callback used to receive the result. The
 *     parameter must not be <b>null</b>.
 * @param userData [in] Indicates the caller-defined context pointer passed
 *     unchanged to the callback. The value can be <b>null</b>.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the framework accepts the request. </li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if context or callback is null.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} count out of range of (0, 20].</li>
 *     <li>{@link ARKUI_ERROR_CODE_COMMAND_UNFINISHED} if the last request is unfinished.</li></ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_GetImagesByNodeIdAsync(ArkUI_ContextHandle context, const int32_t* nodeIds,
    uint32_t count, OH_ArkUI_NativeModule_ImageCollectionCallback callback, void* userData);

/**
 * @brief Consumes the result for a specified node ID.
 *
 * For a successful image result, this function transfers ownership of the
 * <b>PixelMap</b> to the caller. The caller must release it by calling
 * <b>OH_PixelmapNative_Destroy</b>. This function also consumes a failed image
 * result. In that case, it sets <b>*outPixelmap</b> to <b>null</b> and writes
 * the item error to <b>*outItemError</b>. Each node ID in a collection can be
 * consumed only once.
 *
 * Destroying the collection releases only <b>PixelMap</b> instances that the
 * caller has not taken and does not invalidate a transferred <b>PixelMap</b>.
 *
 * The caller must not call this function concurrently with another collection
 * API for the same collection.
 *
 * @param collection [in] Indicates the image collection whose item is consumed. The parameter must not be null.
 * @param nodeId [in] Indicates the ArkUI node ID of the item to consume.
 * @param outPixelmap [out] Indicates the output pointer that receives the transferred PixelMap. The parameter must not
 *     be null. For a failed item, the function sets outPixelmap to null.
 * @param outItemError [out] Indicates the output pointer to the result code for the item. The parameter must not be
 *     null. The function writes {@link ARKUI_ERROR_CODE_NO_ERROR} for a successful item,
 *     {@link ARKUI_ERROR_CODE_NODE_NOT_FOUND} if the ArkUI node corresponding to the requested node ID could not be
 *     found while collecting its image, {@link ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT} for a capture timeout, or
 *     {@link ARKUI_ERROR_CODE_INTERNAL_ERROR} for another capture failure, the caller can retry the request.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if this function consumes the item, including a failed image result.</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a required pointer is null, nodeId does not identify an item in
 *     collection, or the caller has already consumed that item. To resolve the error, provide all required pointers
 *     and use a nodeId that identifies an unconsumed item in collection.</li></ul>
 * @release multimedia/image_framework/image/OH_PixelmapNative_Destroy {outPixelmap}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImageCollectionTakeItemByNodeId(
    OH_ArkUI_NativeModule_ImageCollection* collection, int32_t nodeId,
    OH_PixelmapNative** outPixelmap, ArkUI_ErrorCode* outItemError);

/**
 * @brief Destroys an image collection and releases <b>PixelMap</b> instances that have not been consumed.
 *
 * The caller must destroy every non-<b>null</b> collection that a callback
 * returns, including an empty collection or a collection after the caller has
 * consumed all its items. This function does not release or invalidate
 * <b>PixelMap</b> instances that the caller obtained through
 * <b>OH_ArkUI_NativeModule_ImageCollectionTakeItemByNodeId</b>.
 *
 * The caller must not call this function concurrently with another collection
 * API for the same collection.
 *
 * @param collection [in] Indicates the image collection to destroy. The
 *     parameter can be <b>null</b>. If <b>collection</b> is <b>null</b>, this
 *     function does nothing.
 * @since 26.2.0
 */
void OH_ArkUI_NativeModule_ImageCollectionDestroy(OH_ArkUI_NativeModule_ImageCollection* collection);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_UI_INFO_COLLECTION_H
/** @} */