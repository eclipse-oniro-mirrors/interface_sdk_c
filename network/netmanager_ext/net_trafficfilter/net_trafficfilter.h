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
 * @brief This module implements network traffic filtering and redirection. Traffic filtering intercepts network data
 * packets in the kernel network protocol stack of the system and allows or discards packets based on preset rules. It
 * applies to scenarios such as firewalls, parental controls, and application traffic management.
 * <br>Traffic redirection forwards TCP traffic that matches rules to a specified proxy server. It applies to
 * scenarios such as enterprise network auditing, content filtering proxies, and VPN transparent proxies.
 * <br>To use this module, first create a controller or redirector instance, then add filtering or redirection rules
 * to manage network traffic. After use, call the corresponding destroy API to release resources.
 *
 * @since 26.0.0
 */

/**
 * @file net_trafficfilter.h
 * @brief Declares the C APIs for network traffic filtering and redirection. This header file provides the APIs for
 * creating and destroying a packet controller, registering packet callbacks, adding and clearing filtering rules, as
 * well as creating and destroying a traffic redirector, and adding and clearing redirection rules.
 * <br>It is applicable to scenarios where network packets need to be intercepted, filtered, and redirected at the
 * system level.
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
 * @brief Creates a traffic redirection instance for redirecting TCP traffic to a proxy server.
 * {@link OH_TrafficFilter_DestroyRedirector} must be called to release resources. If this function fails, no valid
 * redirector is returned.
 *
 * @param group_id Redirection link ID, which is a logical group ID within an app. Different **group_id** values can be
 *     used for multiple redirectors within the same app. Redirectors with the same **group_id** in different apps are
 *     automatically isolated. The value range is [{@link OH_TRAFFICFILTER_MIN_GROUP_ID},
 *     {@link OH_TRAFFICFILTER_MAX_GROUP_ID}]. If the value is out of this range, the function returns
 *     {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}.
 * @param priority Priority, which determines the execution order among links with different **group_id** values. A
 *     smaller value indicates a higher priority. Note: The redirector priority is higher than the packet filter
 *     priority. The value range is [{@link OH_TRAFFICFILTER_MIN_PRIORITY}, {@link OH_TRAFFICFILTER_MAX_PRIORITY}]. If
 *     the value is out of range, the function returns {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}.
 * @param redirector Output parameter. On success, it is the double pointer to the redirector handle.
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK}: Success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Permission denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_GROUP_ID_IN_USE}: group_id already exists.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: Invalid parameter.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_NFQUEUE_ERROR}: NFQueue initialization failed.</li></ul>
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
 * @brief Destroys the redirection instance and releases related resources (including rules). The handle becomes
 * invalid after the function is called.
 *
 * @param redirector Pointer to the handle to **OH_TrafficFilter_Redirector**.
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK}: Success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Permission denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: The **redirector** value is **NULL**.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_NOT_FOUND}: The specified redirector handle is not found.</li></ul>
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_DestroyRedirector(OH_TrafficFilter_Redirector* redirector);

/**
 * @brief Adds a TCP traffic redirection rule to redirect matching traffic to the specified proxy server. To delete a
 * redirection rule, call {@link OH_TrafficFilter_ClearRedirectRule}.
 *
 * @param redirector Pointer to the handle to **OH_TrafficFilter_Redirector**.
 * @param rule Pointer to the redirection rule. Cannot be NULL.
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK}: Success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Permission denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: The **redirector** or **rule** value is **NULL**.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_TOO_MANY_RULES}: Too many rules added.</li></ul>
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_AddRedirectRule(
    OH_TrafficFilter_Redirector* redirector,
    const OH_TrafficFilter_RedirectRule* rule
);

/**
 * @brief Clears all redirection rules.
 *
 * @param redirector Pointer to the handle to **OH_TrafficFilter_Redirector**.
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK}: Success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Permission denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: The **redirector** value is NULL.</li></ul>
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_ClearRedirectRule(OH_TrafficFilter_Redirector* redirector);

/**
 * @brief Queries the process information based on network connection. This function queries the process that starts
 * the connection using the five-tuple connection information, including the source IP address, destination IP address,
 * source port number, destination port number, and protocol type.
 *
 * @param connection_info Pointer to the input connection information.
 * @param process_info Pointer to the output process information.
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK}: Success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Permission denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: Invalid parameter.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_NOT_FOUND}: Process not found.</li></ul>
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_QueryProcess(
    const OH_TrafficFilter_ConnectionInfo* connection_info,
    OH_TrafficFilter_ProcessInfo* process_info
);
/**
 * @brief Adds a packet filter rule. The conditions within a single {@link OH_TrafficFilter_FilterRule} struct are in
 * a logical AND relationship. Multiple rules added to the same {@link OH_TrafficFilter_PacketController} are in a
 * logical OR relationship. To clear the filter rules, call {@link OH_TrafficFilter_ClearPacketRule}.
 *
 * @param controller [in] Pointer to the handle to the **OH_TrafficFilter_PacketController**.
 * @param rule [in] Filter rule. Cannot be NULL.
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK}: Success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Permission denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: **controller** or **rule** is NULL.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_TOO_MANY_RULES}: More than 2000 rules are added.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.1
 */
int32_t OH_TrafficFilter_AddPacketRule(
    OH_TrafficFilter_PacketController* controller,
    const OH_TrafficFilter_FilterRule* rule
);

/**
 * @brief Clears packet filter rules (clears all packet filter rules added to the controller handle).
 *
 * @param controller [in] Pointer to the handle to **OH_TrafficFilter_PacketController**.
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK}: Success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Permission denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: **controller** is NULL.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.1
 */
int32_t OH_TrafficFilter_ClearPacketRule(OH_TrafficFilter_PacketController* controller);

/**
 * @brief Creates a packet controller instance.
 * Creates a packet controller for intercepting and filtering network packets
 * Resource Management: This instance occupies system resources.
 * You must call {@link OH_TrafficFilter_DestroyPacketController} to release resources.
 * If this function fails, no valid controller is returned.
 *
 * @param groupId [in] Filter chain identifier. This is the logical group ID within the application. Multiple
 *     controllers in the same application can use different groupIds. The same group ID of different applications is
 *     automatically isolated.
 * @param priority [in] Priority(Determine the execution sequence of different groupId chains. The smaller the
 *     value, the earlier the execution.)
 * @param config [in] Configuration parameters (can be NULL to use default configuration)
 * @param controller [out] Output parameter, <ul><li>the packet controller handle on success.</li></ul>
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} - succeeded.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} - Missing permission. </li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_GROUP_ID_IN_USE} - The groupId already exists. </li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} - The priority is invalid. </li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_NFQUEUE_ERROR} - NFQueue initialization failed. </li></ul>
 *
 * @release TrafficFilter/OH_TrafficFilter_DestroyPacketController {controller}
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.1
 */
int32_t OH_TrafficFilter_CreatePacketController(
    uint32_t groupId,
    uint32_t priority,
    const OH_TrafficFilter_Config* config,
    OH_TrafficFilter_PacketController** controller
);

/**
 * @brief Destroys a packet controller instance. Destroys the controller instance and releases related resources
 * (including rules). After the call, the handle becomes invalid.
 *
 * @param controller [in] Pointer to the **OH_TrafficFilter_PacketController** handle.
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK}: Success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Permission denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: **controller** is NULL.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_NOT_FOUND}: The specified controller handle is not found.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.1
 */
int32_t OH_TrafficFilter_DestroyPacketController(OH_TrafficFilter_PacketController* controller);
/**
 * @brief Registers a packet callback function. Registers a callback function to process intercepted packets. When a
 * packet matches a filter rule, the callback is triggered. To release the callback, call
 * {@link OH_TrafficFilter_UnregisterPacketCallback}.
 *
 * @param controller [in] Pointer to the handle to the **OH_TrafficFilter_PacketController**.
 * @param callback [in] Callback function pointer. Cannot be NULL.
 * @param userData [in] Pointer to the user data (returned in the callback).
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK}: Success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Permission denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: **controller** or **callback** is NULL.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.1
 */
int32_t OH_TrafficFilter_RegisterPacketCallback(
    OH_TrafficFilter_PacketController* controller,
    OH_TrafficFilter_PacketCallback callback,
    void* userData
);

/**
 * @brief Unregisters the packet callback function.
 *
 * @param controller [in] Pointer to the handle to the **OH_TrafficFilter_PacketController**.
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK}: Success.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Permission denied.</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: **controller** is NULL.</li></ul>
 *
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.1
 */
int32_t OH_TrafficFilter_UnregisterPacketCallback(OH_TrafficFilter_PacketController* controller);

#ifdef __cplusplus
}
#endif

#endif /* NET_TRAFFICFILTER_H */
/** @} */