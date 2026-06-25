/*
 * Copyright (C) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup TrafficFilter
 * @{
 *
 * @brief Defines the APIs for traffic filtering.
 *
 * @since 26.0.0
 */

/**
 * @file net_trafficfilter.h
 * @brief Defines the APIs for traffic filtering.
 *
 * @library libnet_trafficfilter.so
 * @kit NetworkKit
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @syscap SystemCapability.Communication.NetManager.NetFirewall
 * @since 26.0.0
 */

#ifndef NET_TRAFFICFILTER_H
#define NET_TRAFFICFILTER_H

#include "net_trafficfilter_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates a traffic redirection instance
 * Creates a traffic redirection instance for transparent TCP traffic redirection to proxy server
 * Resource Management: You must call {@link OH_TrafficFilter_DestroyRedirector} to release resources.
 * If this function fails, no valid redirector is returned.
 *
 * @param group_id Redirection chain identifier.
 *     This is the logical grouping ID within the application.
 *     Multiple redirectors within the same application can use different group_id.
 *     The same group_id from different applications will be automatically isolated.
 *     The valid range is [{@link OH_TRAFFICFILTER_MIN_GROUP_ID}, {@link OH_TRAFFICFILTER_MAX_GROUP_ID}],
 *     including both boundaries. If group_id is outside this range, this function returns
 *     {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}.
 * @param priority Priority.
 *     Determines execution order between different group_id chains. A smaller number executes first.
 *     Note: Redirector priority is higher than packet filter priority.
 *     The valid range is [{@link OH_TRAFFICFILTER_MIN_PRIORITY}, {@link OH_TRAFFICFILTER_MAX_PRIORITY}],
 *     including both boundaries. If priority is outside this range, this function returns
 *     {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}.
 *
 * @param redirector Output parameter, the redirection handle on success.
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} on success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} if permission is denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_GROUP_ID_IN_USE} when group_id already exists.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} if priority is invalid.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_NFQUEUE_ERROR} if NFQueue initialization fails.</li></ul>
 *
 * @release TrafficFilter/OH_TrafficFilter_DestroyRedirector {redirector}
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_CreateRedirector(
    uint32_t group_id,
    uint32_t priority,
    OH_TrafficFilter_Redirector** redirector
);

/**
 * @brief Destroys a traffic redirection instance.
 * Destroys the redirection instance and releases related resources, including rules.
 * The handle becomes invalid after this call.
 *
 * @param redirector OH_TrafficFilter_Redirector handle
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} on success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} if permission is denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} if redirector is NULL.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_NOT_FOUND} if the specified redirector handle is not found.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_DestroyRedirector(OH_TrafficFilter_Redirector* redirector);

/**
 * @brief Adds a redirection rule
 * Adds a TCP traffic redirection rule to redirect matched traffic to specified proxy server
 * To clear redirect rules, you need to call {@link OH_TrafficFilter_ClearRedirectRule}.
 *
 * @param redirector OH_TrafficFilter_Redirector handle
 * @param rule Redirection rule. Cannot be NULL.
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} on success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} if permission is denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} if redirector or rule is NULL.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_TOO_MANY_RULES} if too many rules added.</li></ul>

 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_AddRedirectRule(
    OH_TrafficFilter_Redirector* redirector,
    const OH_TrafficFilter_RedirectRule* rule
);

/**
 * @brief Clear all redirection rule
 *
 * @param redirector OH_TrafficFilter_Redirector handle
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} on success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} if permission is denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} if redirector is NULL.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_ClearRedirectRule(OH_TrafficFilter_Redirector* redirector);

/**
 * @brief Queries corresponding process information based on connection information
 *
 * Queries corresponding process information based on five-tuple information
 *
 * @param connection_info Input connection information
 * @param process_info Output process information
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} on success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} if permission is denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} if input parameters are invalid.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_NOT_FOUND} if process not found.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_QueryProcess(
    const OH_TrafficFilter_ConnectionInfo* connection_info,
    OH_TrafficFilter_ProcessInfo* process_info
);

/**
 * @brief Set packet filter rule
 * Add a packet filter rule to controller chain.
 * only packets matching the rule will be intercepted and sent to callback function.
 * @note Logical relationship:
 *     - Conditions within a single OH_TrafficFilter_FilterRule structure are combined with logical AND.
 *     - Multiple rules added to the same OH_TrafficFilter_PacketController are combined with logical OR.
 *     To clear filter rules, you need to call {@link OH_TrafficFilter_ClearPacketRule}.
 * @param controller [in] OH_TrafficFilter_PacketController handle
 * @param rule [in] Filter rule. Cannot be NULL.
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} on success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} if permission is denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} if controller or rule is NULL.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_TOO_MANY_RULES} if too many rules added.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.1.0
 */
int32_t OH_TrafficFilter_AddPacketRule(
    OH_TrafficFilter_PacketController* controller,
    const OH_TrafficFilter_FilterRule* rule
);

/**
 * @brief Clear packet filter rule
 * Clear all packet filter rules in controller.
 *
 * @param controller [in] OH_TrafficFilter_PacketController handle
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} on success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} if permission is denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} if controller is NULL.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.1.0
 */
int32_t OH_TrafficFilter_ClearPacketRule(OH_TrafficFilter_PacketController* controller);

/**
 * @brief Creates a packet controller instance.
 * Creates a packet controller for intercepting and filtering network packets
 * Resource Management: This instance occupies system resources.
 * You must call {@link OH_TrafficFilter_DestroyPacketController} to release resources.
 * If this function fails, no valid controller is returned.
 *
 * @param groupId [in] Filter chain identifier.
 *     This is the logical grouping ID within the application.
 *     Multiple controllers within the same application can use different group_id.
 *     The same group_id from different applications will be automatically isolated.
 * @param priority [in] Priority (determines execution order between different group_id chain,
 *     smaller number executes first)
 * @param config [in] Configuration parameters (can be NULL to use default configuration)
 * @param controller [out] Output parameter, <ul><li>the packet controller handle on success.</li></ul>
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} on success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} if permission is denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_GROUP_ID_IN_USE} when group_id already exists.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} if priority is invalid.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_NFQUEUE_ERROR} if NFQueue initialization fails.</li></ul>
 *
 * @release TrafficFilter/OH_TrafficFilter_DestroyPacketController {controller}
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.1.0
 */
int32_t OH_TrafficFilter_CreatePacketController(
    uint32_t groupId,
    uint32_t priority,
    const OH_TrafficFilter_Config* config,
    OH_TrafficFilter_PacketController** controller
);

/**
 * @brief Destroys a packet controller instance.
 * Destroys the controller and releases related resources, including rules and callbacks.
 * After calling this function, the handle is invalid. Do not use it again.
 *
 * @param controller [in] OH_TrafficFilter_PacketController handle
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} on success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} if permission is denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} if controller is NULL.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_NOT_FOUND} if the specified controller handle is not found.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.1.0
 */
int32_t OH_TrafficFilter_DestroyPacketController(OH_TrafficFilter_PacketController* controller);

/**
 * @brief Register a packet callback function.
 * Register a callback function to handle intercepted packets.
 * The callback will be triggered when packets match the filter rule.
 *
 * @note <strong>Callback Model:</strong>
 *     <ul>
 *     <li><strong>Single Slot Model:</strong> A single <code>controller</code> instance supports only one active
 *         callback at a time.</li>
 *     <li><strong>Repeated Registration:</strong> If called again with a non-NULL callback, the new callback
 *         <strong>replaces</strong> the previously registered one. The previous callback is immediately unregistered.
 *         No error is returned for repeated registration.</li>
 *     <li><strong>Unregister/Destroy Semantics:</strong>
 *       <ul>
 *         <li>Calling {@link OH_TrafficFilter_UnregisterPacketCallback} or destroying the <code>controller</code>
 *             immediately stops delivery of new packets to the callback.</li>
 *         <li><strong>No In-Flight Callbacks:</strong> Once unregistered or destroyed, the framework guarantees that
 *             no further callback invocations will occur for that registration, even if packet processing is in
 *             progress at the moment of unregistration.</li>
 *       </ul>
 *     </li>
 *     <li><strong>Callback Execution Constraints:</strong>
 *       <ul>
 *         <li><strong>User Data Lifetime:</strong> The <code>user_data</code> must remain valid from registration until
 *             after the callback is unregistered and all ongoing callback invocations have returned.</li>
 *         <li><strong>Thread Context:</strong> The callback may be invoked on any thread. Callers must ensure thread
 *             safety for shared resources.</li>
 *         <li><strong>Ordering and Concurrency:</strong> Callbacks are not guaranteed to be serialized or preserve
 *             packet order. Multiple callbacks may be invoked concurrently.</li>
 *         <li><strong>Reentrancy:</strong> The callback must not call any <code>OH_TrafficFilter_*</code> registration,
 *             unregistration, or controller destruction functions, as this may cause deadlock or undefined
 *             behavior.</li>
 *     </ul>
 *     </li>
 *     </ul>
 *
 * @param controller [in] OH_TrafficFilter_PacketController handle. Must not be NULL.
 * @param callback [in] Callback function pointer. Cannot be NULL.
 * @param userData [in] User data (will be passed back in callback).
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} on success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} if permission is denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} if controller or callback is NULL.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.1.0
 */
int32_t OH_TrafficFilter_RegisterPacketCallback(
    OH_TrafficFilter_PacketController* controller,
    OH_TrafficFilter_PacketCallback callback,
    void* userData
);

/**
 * @brief Unregister a packet callback function.
 * Unregister the current packet callback function.
 * After calling this, no more packets will be delivered to the callback.
 *
 * @param controller [in] OH_TrafficFilter_PacketController handle
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} on success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} if permission is denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} if controller is NULL.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.1.0
 */
int32_t OH_TrafficFilter_UnregisterPacketCallback(OH_TrafficFilter_PacketController* controller);

#ifdef __cplusplus
}
#endif

#endif /* NET_TRAFFICFILTER_H */
/** @} */
