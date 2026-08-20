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
 * @brief Declares the C APIs for network traffic filtering and redirection. This header file provides APIs for
 * creating and destroying a packet controller, registering packet callbacks, adding and deleting filtering rules,
 * creating and destroying a traffic redirector, and adding and deleting redirection rules.
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
 * @param redirector Output parameter, which is the redirection handle when the operation is successful.
 * @return {@link OH_TRAFFICFILTER_OK}: Success.
 *     <br>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Missing permissions.
 *     <br>{@link OH_TRAFFICFILTER_ERROR_GROUP_ID_IN_USE}: The **group_id** exists.
 *     <br>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: Parameter error.
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
 * @param redirector Handle of **OH_TrafficFilter_Redirector**.
 * @return {@link OH_TRAFFICFILTER_OK}: Success.
 *     <br>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Missing permissions.
 *     <br>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: The **redirector** value is **NULL**.
 *     <br>{@link OH_TRAFFICFILTER_ERROR_NOT_FOUND}: The specified redirector handle is not found.
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
 * @brief Clears all redirection rules.
 *
 * @param redirector Handle of **OH_TrafficFilter_Redirector**.
 * @return {@link OH_TRAFFICFILTER_OK}: Success.
 *     <br>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Missing permissions.
 *     <br>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: The **redirector** value is NULL.
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_ClearRedirectRule(OH_TrafficFilter_Redirector* redirector);

/**
 * @brief Queries the process information based on network connection. This function queries the process that starts
 * the connection using the five-tuple connection information, including the source IP address, destination IP address,
 * source port number, destination port number, and protocol type.
 *
 * @param connection_info Input connection information.
 * @param process_info Output process information.
 * @return {@link OH_TRAFFICFILTER_OK}: Success.
 *     <br>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED}: Missing permissions.
 *     <br>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}: Invalid input parameter.
 *     <br>{@link OH_TRAFFICFILTER_ERROR_NOT_FOUND}: Process not found.
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_QueryProcess(
    const OH_TrafficFilter_ConnectionInfo* connection_info,
    OH_TrafficFilter_ProcessInfo* process_info
);

#ifdef __cplusplus
}
#endif

#endif /* NET_TRAFFICFILTER_H */
/** @} */
