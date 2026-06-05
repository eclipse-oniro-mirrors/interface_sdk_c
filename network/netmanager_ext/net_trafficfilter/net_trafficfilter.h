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

#ifdef __cplusplus
}
#endif

#endif /* NET_TRAFFICFILTER_H */
/** @} */
