/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NATIVE_NET_CONN_API_H
#define NATIVE_NET_CONN_API_H

/**
 * @addtogroup NetConnection
 * @{
 *
 * @brief Provide C interface for the data network connection module of network management.
 *
 * @since 11
 * @version 1.0
 */

/**
 * @file net_connection.h
 *
 * @brief Provide C interface for the data network connection module of network management.
 *
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetManager.Core
 * @library libnet_connection.so
 * @since 11
 * @version 1.0
 */

#include <netdb.h>

#include "net_connection_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Checks whether a default activated data network is available.
 *
 * @param hasDefaultNet Whether there is a default network.
 * @return **0**: Success. **201**: Missing permissions.
 *     <br>**401**: Parameter error. **2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_HasDefaultNet(int32_t *hasDefaultNet);

/**
 * @brief Obtains the default activated data network.
 *
 * @param netHandle Network ID.
 * @return **0**: Success. **201**: Missing permissions.
 *     <br>**401**: Parameter error. **2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_GetDefaultNet(NetConn_NetHandle *netHandle);

/**
 * @brief Checks whether metering is enabled for the default data network.
 *
 * @param isMetered Whether metering is enabled.
 * @return **0**: Success. **201**: Missing permissions.
 *     <br>**401**: Parameter error. **2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_IsDefaultNetMetered(int32_t *isMetered);

/**
 * @brief Obtains the link information of a data network.
 *
 * @param netHandle Network ID.
 * @param prop Link information.
 * @return **0**: Success. **201**: Missing permissions.
 *     <br>**401**: Parameter error. **2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_GetConnectionProperties(NetConn_NetHandle *netHandle, NetConn_ConnectionProperties *prop);

/**
 * @brief Obtains the capabilities of a data network.
 *
 * @param netHandle Network ID.
 * @param netCapabilities Capability set.
 * @return **0**: Success. **201**: Missing permissions.
 *     <br>**401**: Parameter error. **2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_GetNetCapabilities(NetConn_NetHandle *netHandle, NetConn_NetCapabilities *netCapabilities);

/**
 * @brief Obtains the default network proxy.
 *
 * @param httpProxy Proxy configuration.
 * @return **0**: Success. **201**: Missing permissions.
 *     <br>**401**: Parameter error. **2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_GetDefaultHttpProxy(NetConn_HttpProxy *httpProxy);

/**
 * @brief Obtains the DNS result based on the specified **netId**.
 *
 * @param host Host name.
 * @param serv Service name.
 * @param hint Pointer to the addrinfo structure.
 * @param res DNS query result, which is in the format of linked lists.
 * @param netId If **netId** is set to **0**, the default **netid** is used for query.
 * @return **0**: Success. **201**: Missing permissions.
 *     <br>**401**: Parameter error. **2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 * @permission ohos.permission.INTERNET
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_GetAddrInfo(char *host, char *serv, struct addrinfo *hint, struct addrinfo **res, int32_t netId);

/**
 * @brief Releases the DNS query result.
 *
 * @param res Header of the DNS query result, which is in the format of linked lists.
 * @return **0**: Success. **201**: Missing permissions.
 *     <br>**401**: Parameter error. **2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 * @permission ohos.permission.INTERNET
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_FreeDnsResult(struct addrinfo *res);

/**
 * @brief Obtains all activated data networks.
 *
 * @param netHandleList Network information list.
 * @return **0**: Success. **201**: Missing permissions.
 *     <br>**401**: Parameter error. **2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_GetAllNets(NetConn_NetHandleList *netHandleList);
/**
 * @brief Registers a custom DNS resolver.
 *
 * @param resolver Pointer to the custom DNS resolver.
 * @return **0**: Success. **401**: Parameter error.
 *     <br>**2100002**: Service connection failure.  **2100003**: Internal error.
 * @syscap SystemCapability.Communication.NetManager.Core
 * @deprecated since 13
 * @useinstead OH_NetConn_RegisterDnsResolver
 * @since 11
 * @version 1.0
 */
int32_t OHOS_NetConn_RegisterDnsResolver(OH_NetConn_CustomDnsResolver resolver);

/**
 * @brief Unregisters a custom DNS resolver.
 *
 * @return **0**: Success.
 *     <br>**2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 * @syscap SystemCapability.Communication.NetManager.Core
 * @deprecated since 13
 * @useinstead OH_NetConn_UnregisterDnsResolver
 * @since 11
 * @version 1.0
 */
int32_t OHOS_NetConn_UnregisterDnsResolver(void);
/**
 * @brief Registers a custom DNS resolver.
 *
 * @param resolver Pointer to the custom DNS resolver.
 * @return Result code.
 *     <br>**NETMANAGER_EXT_SUCCESS**: Operation success.
 *     <br>**NETMANAGER_ERR_PARAMETER_ERROR**: Parameter error. Enter a correct parameter.
 * @deprecated since 26.0.0
 * @useinstead OH_NetConn_RegisterCustomDnsResolver
 * @since 13
 * @version 1.0
 */
int32_t OH_NetConn_RegisterDnsResolver(OH_NetConn_CustomDnsResolver resolver);
/**
 * @brief Unregisters a custom DNS resolver.
 *
 * @return **0**: Success.
 *     <br>**2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 * @deprecated since 26.0.0
 * @useinstead OH_NetConn_UnregisterCustomDnsResolver
 * @since 13
 * @version 1.0
 */
int32_t OH_NetConn_UnregisterDnsResolver(void);
/**
 * @brief Registers a custom DNS resolver to intercept and override DNS queries. Falls back to system DNS if no result is specified.
 *        Only a single resolver is allowed. You must unregister the existing one before registering a new one.
 *
 * @param resolver Pointer to the custom DNS resolver. If the resolver returns 0, skip system DNS; otherwise, fallback to system DNS.
 * @return 0 - Success.
 *         401 - Parameter error. Please enter a correct parameter.
 *         2101008 - Resolver already exists. use OH_NetConn_UnregisterCustomDnsResolver before registering a new one.
 * @stagemodelonly
 * @since 26.0.0
 */
int32_t OH_NetConn_RegisterCustomDnsResolver(OH_NetConn_CustomDnsResolver resolver);

/**
 * @brief Unregisters the custom DNS resolver.
 *
 * @return 0 - Success.
 *         2100003 - Internal error.
 * @stagemodelonly
 * @since 26.0.0
 */
int32_t OH_NetConn_UnregisterCustomDnsResolver(void);

/**
 * @brief Binds a socket to the specified network.
 *
 * @param socketFd Socket constructed by the user.
 * @param netHandle Pointer to the network handle containing the network ID.
 * @return **0**: Success.
 *     <br>**401**: Parameter error.
 *     <br>**2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
int32_t OH_NetConn_BindSocket(int32_t socketFd, NetConn_NetHandle *netHandle);

/**
 * @brief Sets an HTTP proxy for the current application.
 *
 * @param httpProxy HTTP proxy to set.
 * @return **0**: Success.
 *     <br>**401**: Parameter error.
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
int32_t OH_NetConn_SetAppHttpProxy(NetConn_HttpProxy *httpProxy);

/**
 * @brief Registers a callback for HTTP proxy changes of the application.
 *
 * @param appHttpProxyChange Callback to register.
 * @param callbackId ID of the registered callback.
 * @return **0**: Success.
 *     <br>**401**: Parameter error.
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
int32_t OH_NetConn_RegisterAppHttpProxyCallback(OH_NetConn_AppHttpProxyChange appHttpProxyChange, uint32_t *callbackId);

/**
 * @brief Unregisters the callback for HTTP proxy changes of the application.
 *
 * @param callbackId ID of the callback to unregister.
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
void OH_NetConn_UnregisterAppHttpProxyCallback(uint32_t callbackId);

/**
 * @brief Requests global HTTP proxy re-authentication and reports the result through a one-shot callback.
 *
 * This function submits an asynchronous re-authentication request. A return value of 0 indicates
 * that the request has been accepted. It does not indicate that re-authentication has succeeded.
 * The final result is reported through the callback.<br>
 *
 * If this function returns 0, the callback will be invoked at most once. After the callback is
 * invoked, it is automatically released by the system.<br>
 *
 * If this function returns a non-zero value, the callback will not be invoked.<br>
 *
 * The callback may be invoked on a system worker thread. The caller must ensure that the callback
 * implementation is thread-safe and returns quickly.<br>
 *
 * The caller must ensure that the callback function and userData remain valid until the callback
 * is invoked.
 *
 * @permission ohos.permission.INTERNET
 * @param callback The one-shot callback used to receive the re-authentication result. It must not be NULL.
 * @param userContext The user-defined data passed to the callback. It can be NULL. The system does
 *     not access, copy, or release it.
 * @return <ul><li>0 - Success.</li>
 *     <li>201 - Permission denied.</li>
 *     <li>401 - Parameter error.</li></ul>
 * @since 26.0.0
 */
int32_t OH_NetConn_RefreshGlobalHttpProxyWithCallback(
    OH_NetConn_GlobalHttpProxyRefreshCallback callback,
    void *userContext);

/**
 * @brief Registers a callback for network status changes.
 *
 * @param netSpecifier Network feature set.
 * @param callback Registered callbacks.
 * @param timeout Timeout duration, in milliseconds. The value **0** indicates infinite waiting.
 * @param callbackId Callback IDs.
 * @return **0**: Success.
 *     <br>**201**: Missing permissions.
 *     <br>**401**: Parameter error.
 *     <br>**2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 *     <br>**2101008**: Callback already registered.
 *     <br>**2101022**: Maximum number of requests exceeded.
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
int32_t OH_NetConn_RegisterNetConnCallback(NetConn_NetSpecifier *specifier, NetConn_NetConnCallback *netConnCallback,
                                           uint32_t timeout, uint32_t *callbackId);

/**
 * @brief Registers a callback for status changes of the default network.
 *
 * @param callback Registered callbacks.
 * @param callbackId Callback IDs.
 * @return **0**: Success.
 *     <br>**201**: Missing permissions.
 *     <br>**401**: Parameter error.
 *     <br>**2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 *     <br>**2101008**: Callback already registered.
 *     <br>**2101022**: Maximum number of requests exceeded.
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
int32_t OH_NetConn_RegisterDefaultNetConnCallback(NetConn_NetConnCallback *netConnCallback, uint32_t *callbackId);

/**
 * @brief Unregisters the callback for network status changes.
 *
 * @param callBackId ID of the callback to unregister.
 * @return **0**: Success.
 *     <br>**201**: Missing permissions.
 *     <br>**401**: Parameter error.
 *     <br>**2100002**: Service connection failure.
 *     <br>**2100003**: Internal error.
 *     <br>**2101007**: Callback not exist.
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
int32_t OH_NetConn_UnregisterNetConnCallback(uint32_t callBackId);
/**
 * @brief Sets the URL of the system-level Proxy Auto Config (PAC) script, for example, **http://127.0.0.1:21998/
 * PacProxyScript.pac**. You can obtain the proxy information by parsing the URL.
 *
 * @param pacUrl Address of the PAC script.
 * @return Result code defined in {@link NetConn_ErrorCode}.
 *     <br>{@link NETCONN_SUCCESS}: success.
 *     <br>{@link NETCONN_PERMISSION_DENIED}: permission denied.
 *     <br>{@link NETCONN_PARAMETER_ERROR}: parameter error.
 *     <br>{@link NETCONN_OPERATION_FAILED}: unable to connect to the service.
 *     <br>{@link NETCONN_INTERNAL_ERROR}: internal error.
 * @permission ohos.permission.SET_PAC_URL
 * @since 15
 */
NetConn_ErrorCode OH_NetConn_SetPacUrl(const char *pacUrl);

/**
 * @brief Obtains the URL of the system-level PAC script.
 *
 * @param pacUrl URL of the PAC script.
 * @return Result code defined in {@link NetConn_ErrorCode}.
 *     <br>{@link NETCONN_SUCCESS}: success.
 *     <br>{@link NETCONN_PARAMETER_ERROR}: parameter error.
 *     <br>{@link NETCONN_OPERATION_FAILED}: unable to connect to the service.
 *     <br>{@link NETCONN_INTERNAL_ERROR}: internal error.
 * @since 15
 */
NetConn_ErrorCode OH_NetConn_GetPacUrl(char *pacUrl);
/**
 * @brief Queries network probe results. If an exception (for example, network disconnection) occurs and the request
 * fails to be sent, the API immediately returns the result without performing subsequent detection. This API involves
 * network operations. Do not call it in the main process. Otherwise, the UI may freeze.
 *
 * @param destination Target domain name or IP address to be detected. For a domain name, the domain name is resolved
 *     to the target IP address before the detection, and then the detection is initiated. The domain name resolution
 *     time is not included in the probe duration indicated by duration.
 * @param duration Probe duration. in seconds. The detection interval is 1 second. Therefore, you can use this field to
 *     control the number of detections.
 * @param probeResultInfo Packet loss rate and round-trip time (RTT).
 * @return **0**: Success.
 *     <br>**201**: Missing permissions.
 *     <br>**401**: Parameter error.
 *     <br>**2100003**: Internal error.
 * @permission ohos.permission.INTERNET
 * @since 20
 */
int32_t OH_NetConn_QueryProbeResult(char *destination, int32_t duration, NetConn_ProbeResultInfo *probeResultInfo);
/**
 * @brief Queries network trace route information.
 *
 * @param destination Destination address.
 * @param option Route options.
 * @param traceRouteInfo Route result. An array pointer needs to be passed. The array size indicates the number of
 *     route hops, which is **30** by default. If you customize the number of hops, ensure that the array size is the
 *     same as the value of **maxJumpNumber** in the **option** field.
 * @return **0**: Success.
 *     <br>**201**: Missing permissions.
 * @permission ohos.permission.INTERNET and ohos.permission.LOCATION and ohos.permission.ACCESS_NET_TRACE_INFO
 * @since 20
 */
int32_t OH_NetConn_QueryTraceRoute(char *destination, NetConn_TraceRouteOption *option,
    NetConn_TraceRouteInfo *traceRouteInfo);

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* NATIVE_NET_CONN_API_H */