/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef NATIVE_NET_CONN_TYPE_H
#define NATIVE_NET_CONN_TYPE_H

/**
 * @addtogroup NetConnection
 * @{
 *
 * @brief Provides the data structures for the C APIs of the network connection module for network management.
 *
 * @since 11
 * @version 1.0
 */

/**
 * @file net_connection_type.h
 * @brief Defines the data structures for the C APIs of the network connection module.
 *
 * @library libnet_connection.so
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <netdb.h>

#ifdef __cplusplus
extern "C" {
#endif
#define NETCONN_MAX_NET_SIZE 32
#define NETCONN_MAX_BEARER_TYPE_SIZE 32
#define NETCONN_MAX_CAP_SIZE 32
#define NETCONN_MAX_ADDR_SIZE 32
#define NETCONN_MAX_ROUTE_SIZE 64
#define NETCONN_MAX_EXCLUSION_SIZE 256
#define NETCONN_MAX_STR_LEN 256
#define NETCONN_MAX_RTT_NUM 4

/**
 * @brief Enumerates the network capabilities.
 *
 * @since 11
 * @version 1.0
 */
typedef enum NetConn_NetCap {
    /**
     * MMS.
     */
    NETCONN_NET_CAPABILITY_MMS = 0,
    /**
     * Non-metered network.
     */
    NETCONN_NET_CAPABILITY_NOT_METERED = 11,
    /**
     * Internet.
     */
    NETCONN_NET_CAPABILITY_INTERNET = 12,
    /**
     * Non-VPN.
     */
    NETCONN_NET_CAPABILITY_NOT_VPN = 15,
    /**
     * Verified.
     */
    NETCONN_NET_CAPABILITY_VALIDATED = 16,
    /**
     * Portal.
     * @since 12
     */
    NETCONN_NET_CAPABILITY_PORTAL = 17,
    /**
     * Connectivity check.
     * @since 12
     */
    NETCONN_NET_CAPABILITY_CHECKING_CONNECTIVITY = 31
} NetConn_NetCap;

/**
 * @brief Enumerates the network carrier types.
 *
 * @since 11
 * @version 1.0
 */
typedef enum NetConn_NetBearerType {
    /**
     * Cellular network.
     */
    NETCONN_BEARER_CELLULAR = 0,
    /**
     * Wi-Fi.
     */
    NETCONN_BEARER_WIFI = 1,
    /**
     * Bluetooth.
     * @since 12
     */
    NETCONN_BEARER_BLUETOOTH = 2,
    /**
     * Ethernet.
     */
    NETCONN_BEARER_ETHERNET = 3,
    /**
     * VPN.
     * @since 12
     */
    NETCONN_BEARER_VPN = 4
} NetConn_NetBearerType;

/**
 * @brief Enumerates network connection error codes.
 *
 * @since 15
 */
typedef enum NetConn_ErrorCode {
    /**
     * Success.
     */
    NETCONN_SUCCESS = 0,
    /**
     * Missing permissions.
     */
    NETCONN_PERMISSION_DENIED = 201,
    /**
     * Invalid parameter.
     */
    NETCONN_PARAMETER_ERROR = 401,
    /**
     * Service connection failure.
     */
    NETCONN_OPERATION_FAILED = 2100002,
    /**
     * Internal error.1. Memory-related error, for example, insufficient memory, memory data copy failure, or memory
     * request failure.2. Null pointer, for example, access to a released memory pointer.
     */
    NETCONN_INTERNAL_ERROR = 2100003
} NetConn_ErrorCode;

/**
 * @brief Enumerates trace route packet types.
 *
 * @since 20
 */
typedef enum NetConn_PacketsType {
    /**
     * Internet Control Message Protocol.
     */
    NETCONN_PACKETS_ICMP = 0,
    /**
     * User Datagram Protocol.
     */
    NETCONN_PACKETS_UDP = 1
} NetConn_PacketsType;

/**
 * @brief Defines network handles for network IDs.
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_NetHandle {
    /**
     * Network ID.
     */
    int32_t netId;
} NetConn_NetHandle;

/**
 * @brief Defines network capability sets.
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_NetCapabilities {
    /**
     * Uplink bandwidth.
     */
    uint32_t linkUpBandwidthKbps;
    /**
     * Downlink bandwidth.
     */
    uint32_t linkDownBandwidthKbps;
    /** Network capability list */
    NetConn_NetCap netCaps[NETCONN_MAX_CAP_SIZE];
    /**
     * Actual size of the network capability list.
     */
    int32_t netCapsSize;
    /** Bearer type list */
    NetConn_NetBearerType bearerTypes[NETCONN_MAX_BEARER_TYPE_SIZE];
    /**
     * Actual size of the bearer type list.
     */
    int32_t bearerTypesSize;
} NetConn_NetCapabilities;

/**
 * @brief Defines network addresses.
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_NetAddr {
    /**
     * Network address family.
     */
    uint8_t family;
    /**
     * Prefix length.
     */
    uint8_t prefixlen;
    /**
     * Port number.
     */
    uint8_t port;
    /** Address */
    char address[NETCONN_MAX_STR_LEN];
} NetConn_NetAddr;

/**
 * @brief Defines the route configuration.
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_Route {
    /** Network interface */
    char iface[NETCONN_MAX_STR_LEN];
    /**
     * Destination address.
     */
    NetConn_NetAddr destination;
    /**
     * Gateway IP address.
     */
    NetConn_NetAddr gateway;
    /**
     * Whether a gateway exists.
     */
    int32_t hasGateway;
    /**
     * Whether the default route is used.
     */
    int32_t isDefaultRoute;
} NetConn_Route;

/**
 * @brief Defines the proxy configuration.
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_HttpProxy {
    /** Host name */
    char host[NETCONN_MAX_STR_LEN];
    /** Exclusion list of proxy servers */
    char exclusionList[NETCONN_MAX_EXCLUSION_SIZE][NETCONN_MAX_STR_LEN];
    /**
     * Actual size of the exclusion list.
     */
    int32_t exclusionListSize;
    /**
     * Port number.
     */
    uint16_t port;
} NetConn_HttpProxy;

/**
 * @brief Defines the network connection properties.
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_ConnectionProperties {
    /** Network interface name */
    char ifaceName[NETCONN_MAX_STR_LEN];
    /** Domain name of the network connection */
    char domain[NETCONN_MAX_STR_LEN];
    /** TCP buffer size */
    char tcpBufferSizes[NETCONN_MAX_STR_LEN];
    /**
     * Maximum transmission unit.
     */
    uint16_t mtu;
    /** Address list */
    NetConn_NetAddr netAddrList[NETCONN_MAX_ADDR_SIZE];
    /**
     * Actual size of the address list.
     */
    int32_t netAddrListSize;
    /** DNS list */
    NetConn_NetAddr dnsList[NETCONN_MAX_ADDR_SIZE];
    /**
     * Actual size of the DNS list.
     */
    int32_t dnsListSize;
    /** Route list */
    NetConn_Route routeList[NETCONN_MAX_ROUTE_SIZE];
    /**
     * Actual size of the route list.
     */
    int32_t routeListSize;
    /**
     * HTTP proxy information.
     */
    NetConn_HttpProxy httpProxy;
} NetConn_ConnectionProperties;

/**
 * @brief Defines the network list.
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_NetHandleList {
    /** Network handle list */
    NetConn_NetHandle netHandles[NETCONN_MAX_NET_SIZE];
    /**
     * Actual size of the network handle list.
     */
    int32_t netHandleListSize;
} NetConn_NetHandleList;
/**
 * @brief Defines the pointer to the custom DNS resolver.
 *
 * @param host Host name.
 * @param serv Service name.
 * @param hint Pointer to the addrinfo structure.
 * @param res DNS query result, which is in the format of linked lists.
 * @since 11
 * @version 1.0
 */
typedef int (*OH_NetConn_CustomDnsResolver)(const char *host, const char *serv,
    const struct addrinfo *hint, struct addrinfo **res);

/**
 * @brief Callback for application http proxy information changed.
 *
 * @param proxy Changed proxy information, which can be a null pointer.
 *
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_AppHttpProxyChange)(NetConn_HttpProxy *proxy);

/**
 * @brief Defines the one-shot callback used to receive the global HTTP proxy re-authentication result.
 *
 * This callback is invoked at most once for each successful call to
 * OH_NetConn_RefreshGlobalHttpProxyWithCallback.
 *
 * @param result The re-authentication result. 0 indicates success. Other values indicate failure.
 * @param proxy The refreshed global HTTP proxy information when result is 0. If re-authentication
 *     fails, proxy is NULL.<br>
 *     The proxy object is owned by the system and is valid only during this callback
 *     invocation. The caller must not free or modify it. If the caller needs to use the
 *     proxy information after the callback returns, the caller must make a deep copy.
 * @param userContext The user-defined data passed to OH_NetConn_RefreshGlobalHttpProxyWithCallback. The system
 *     does not access, copy, or release it.
 *
 * @since 26.0.0
 */
typedef void (*OH_NetConn_GlobalHttpProxyRefreshCallback)(
    int32_t result,
    const NetConn_HttpProxy *proxy,
    void *userContext);

/**
 * @brief Defines network feature sets.
 *
 * @since 12
 * @version 1.0
 */
typedef struct NetConn_NetSpecifier {
    /**
     * Network capability set.
     */
    NetConn_NetCapabilities caps;
    /**
     * Network ID.
     */
    char *bearerPrivateIdentifier;
} NetConn_NetSpecifier;
/**
 * @brief Defines the callback invoked when the network is available.
 *
 * @param netHandle Network handle.
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_NetworkAvailable)(NetConn_NetHandle *netHandle);
/**
 * @brief Defines the callback invoked when the network capabilities change.
 *
 * @param netHandle Network handle.
 * @param netCapabilities Network capability set.
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_NetCapabilitiesChange)(NetConn_NetHandle *netHandle,
                                                 NetConn_NetCapabilities *netCapabilities);
/**
 * @brief Defines the callback invoked when network connection properties change.
 *
 * @param netHandle Network handle.
 * @param connConnetionProperties Network connection properties.
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_NetConnectionPropertiesChange)(NetConn_NetHandle *netHandle,
                                                         NetConn_ConnectionProperties *connConnetionProperties);
/**
 * @brief Defines the callback invoked when the network is disconnected.
 *
 * @param netHandle Network handle.
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_NetLost)(NetConn_NetHandle *netHandle);
/**
 * @brief Defines the callback invoked when the network is unavailable. This callback is triggered when the network is
 * not activated within the specified timeout interval. If the timeout interval is not set, this callback is not
 * triggered.
 *
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_NetUnavailable)(void);

/**
 * @brief Defines the callback invoked when the network blocking status changes.
 *
 * @param netHandle Network handle.
 * @param blocked Whether the network is blocked. The value true indicates that the network is blocked, and the value
 *     false indicates the opposite.
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_NetBlockStatusChange)(NetConn_NetHandle *netHandle, bool blocked);
/**
 * @brief Defines a struct for the network status listener callback collection. All callback events must be registered;
 * those not requiring attention can be set to empty.
 *
 * @since 12
 * @version 1.0
 */
typedef struct NetConn_NetConnCallback {
    /**
     * Callback invoked when the network is available.
     */
    OH_NetConn_NetworkAvailable onNetworkAvailable;
    /**
     * Callback invoked when the network capabilities change.
     */
    OH_NetConn_NetCapabilitiesChange onNetCapabilitiesChange;
    /**
     * Callback invoked when network connection properties change.
     */
    OH_NetConn_NetConnectionPropertiesChange onConnetionProperties;
    /**
     * Callback invoked when the network is disconnected.
     */
    OH_NetConn_NetLost onNetLost;
    /**
     * Callback invoked when the network is unavailable. This callback is triggered when the network is not activated
     * within the specified timeout interval. If the timeout interval is not set, this callback is not triggered.
     */
    OH_NetConn_NetUnavailable onNetUnavailable;
    /**
     * Callback invoked when the network blocking status changes.
     */
    OH_NetConn_NetBlockStatusChange onNetBlockStatusChange;
} NetConn_NetConnCallback;

/**
 * @brief Defines the probe result.
 *
 * @since 20
 */
typedef struct NetConn_ProbeResultInfo {
    /**
     * Packet loss rate, in percentage. The value **100** indicates 100% packet loss, and the value **50** indicates 50%
     * packet loss.
     */
    uint8_t lossRate;
    /**
     * Round-trip time in ms, including the maximum, minimum, average, and standard deviations.
     */
    uint32_t rtt[NETCONN_MAX_RTT_NUM];
} NetConn_ProbeResultInfo;

/**
 * @brief Defines the network trace route options.
 *
 * @since 20
 */
typedef struct NetConn_TraceRouteOption {
    /**
     * Maximum number of hops in the probe result. The value must be the same as that of **TraceRouteInfo**. The
     * maximum number of hops is 30, which is also the default value.
     */
    uint8_t maxJumpNumber;
    /**
     * Protocol type of the probe packet. The default value is **NETCONN_PACKETS_ICMP**.
     */
    NetConn_PacketsType packetsType;
} NetConn_TraceRouteOption;

/**
 * @brief Defines the trace route information.
 *
 * @since 20
 */
typedef struct NetConn_TraceRouteInfo {
    /**
     * Number of hops.
     */
    uint8_t jumpNo;
    /**
     * Host name or address.
     */
    char address[NETCONN_MAX_STR_LEN];
    /**
     * Round-trip time in ms, including the maximum, minimum, average, and standard deviations.
     */
    uint32_t rtt[NETCONN_MAX_RTT_NUM];
} NetConn_TraceRouteInfo;

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* NATIVE_NET_CONN_TYPE_H */