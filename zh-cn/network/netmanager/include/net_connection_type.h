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
 * @brief 为网络管理数据网络连接模块提供C接口数据结构。
 *
 * @since 11
 * @version 1.0
 */

/**
 * @file net_connection_type.h
 * @brief 定义网络管理数据网络连接模块的C接口数据结构。
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
 * @brief 网络能力集。
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
     * 非计量网络
     */
    NETCONN_NET_CAPABILITY_NOT_METERED = 11,
    /**
     * Internet.
     */
    NETCONN_NET_CAPABILITY_INTERNET = 12,
    /**
     * 非VPN
     */
    NETCONN_NET_CAPABILITY_NOT_VPN = 15,
    /**
     * 已验证
     */
    NETCONN_NET_CAPABILITY_VALIDATED = 16,
    /**
     * Portal.
     * @since 12
     */
    NETCONN_NET_CAPABILITY_PORTAL = 17,
    /**
     * 检测连通性中。
     * @since 12
     */
    NETCONN_NET_CAPABILITY_CHECKING_CONNECTIVITY = 31
} NetConn_NetCap;

/**
 * @brief 网络载体类型。
 *
 * @since 11
 * @version 1.0
 */
typedef enum NetConn_NetBearerType {
    /**
     * 蜂窝网络
     */
    NETCONN_BEARER_CELLULAR = 0,
    /**
     * Wi-Fi.
     */
    NETCONN_BEARER_WIFI = 1,
    /**
     * 蓝牙
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
 * @brief 网络连接返回值错误码。
 *
 * @since 15
 */
typedef enum NetConn_ErrorCode {
    /**
     * 成功
     */
    NETCONN_SUCCESS = 0,
    /**
     * 缺少权限
     */
    NETCONN_PERMISSION_DENIED = 201,
    /**
     * 参数错误
     */
    NETCONN_PARAMETER_ERROR = 401,
    /**
     * 无法连接到服务
     */
    NETCONN_OPERATION_FAILED = 2100002,
    /**
     * 内部错误。1. 内存异常, 比如内存不足或内存拷贝失败。2. 空指针, 比如访问已释放内存的指针。
     */
    NETCONN_INTERNAL_ERROR = 2100003
} NetConn_ErrorCode;

/**
 * @brief 枚举跟踪路由的数据包类型。
 *
 * @since 20
 */
typedef enum NetConn_PacketsType {
    /**
     * 互联网控制消息协议。
     */
    NETCONN_PACKETS_ICMP = 0,
    /**
     * 用户数据报协议。
     */
    NETCONN_PACKETS_UDP = 1
} NetConn_PacketsType;

/**
 * @brief 存放网络ID。
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_NetHandle {
    /**
     * 网络标识符。
     */
    int32_t netId;
} NetConn_NetHandle;

/**
 * @brief 网络能力集。
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_NetCapabilities {
    /**
     * 上行带宽。
     */
    uint32_t linkUpBandwidthKbps;
    /**
     * 下行带宽。
     */
    uint32_t linkDownBandwidthKbps;
    /**
     * 网络能力列表。
     */
    NetConn_NetCap netCaps[NETCONN_MAX_CAP_SIZE];
    /**
     * 网络能力列表的实际size。
     */
    int32_t netCapsSize;
    /**
     * 承载类型列表。
     */
    NetConn_NetBearerType bearerTypes[NETCONN_MAX_BEARER_TYPE_SIZE];
    /**
     * 承载类型列表的实际size
     */
    int32_t bearerTypesSize;
} NetConn_NetCapabilities;

/**
 * @brief 网络地址。
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_NetAddr {
    /**
     * 网络地址族。
     */
    uint8_t family;
    /**
     * 前缀长度。
     */
    uint8_t prefixlen;
    /**
     * 端口号。
     */
    uint8_t port;
    /**
     * 地址。
     */
    char address[NETCONN_MAX_STR_LEN];
} NetConn_NetAddr;

/**
 * @brief 路由配置信息。
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_Route {
    /**
     * 网络接口。
     */
    char iface[NETCONN_MAX_STR_LEN];
    /**
     * 目标地址
     */
    NetConn_NetAddr destination;
    /**
     * 网关地址
     */
    NetConn_NetAddr gateway;
    /**
     * 是否存在网关
     */
    int32_t hasGateway;
    /**
     * 是否是默认路由
     */
    int32_t isDefaultRoute;
} NetConn_Route;

/**
 * @brief 代理配置信息。
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
     * 排除列表的实际大小。
     */
    int32_t exclusionListSize;
    /**
     * 端口号。
     */
    uint16_t port;
} NetConn_HttpProxy;

/**
 * @brief 网络连接信息。
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_ConnectionProperties {
    /**
     * 网络接口名称。
     */
    char ifaceName[NETCONN_MAX_STR_LEN];
    /**
     * 网络连接的域名。
     */
    char domain[NETCONN_MAX_STR_LEN];
    /**
     * TCP缓冲区大小。
     */
    char tcpBufferSizes[NETCONN_MAX_STR_LEN];
    /** MTU */
    uint16_t mtu;
    /**
     * 地址列表。
     */
    NetConn_NetAddr netAddrList[NETCONN_MAX_ADDR_SIZE];
    /**
     * 地址列表的实际size。
     */
    int32_t netAddrListSize;
    /**
     * DNS列表。
     */
    NetConn_NetAddr dnsList[NETCONN_MAX_ADDR_SIZE];
    /**
     * DNS列表的实际size。
     */
    int32_t dnsListSize;
    /**
     * 路由列表。
     */
    NetConn_Route routeList[NETCONN_MAX_ROUTE_SIZE];
    /**
     * 路由列表的实际大小。
     */
    int32_t routeListSize;
    /**
     * HTTP代理信息。
     */
    NetConn_HttpProxy httpProxy;
} NetConn_ConnectionProperties;

/**
 * @brief 网络列表。
 *
 * @since 11
 * @version 1.0
 */
typedef struct NetConn_NetHandleList {
    /**
     * 网络句柄列表。
     */
    NetConn_NetHandle netHandles[NETCONN_MAX_NET_SIZE];
    /**
     * netHandleList的实际大小。
     */
    int32_t netHandleListSize;
} NetConn_NetHandleList;
/**
 * @brief 指向自定义DNS解析器的指针。
 *
 * @param host 要查询的主机名。
 * @param serv 服务名称。
 * @param hint 指向addrinfo结构的指针。
 * @param res 存储DNS查询结果并以链表形式返回。
 * @since 11
 * @version 1.0
 */
typedef int (*OH_NetConn_CustomDnsResolver)(const char *host, const char *serv,
    const struct addrinfo *hint, struct addrinfo **res);

/**
 * @brief 应用的http代理信息变化回调。
 *
 * @param proxy 变化的代理配置信息，可能是空指针。
 *
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_AppHttpProxyChange)(NetConn_HttpProxy *proxy);

/**
 * @brief 定义用于接收全局HTTP代理重新认证结果的一次性回调。
 *
 * 每次成功调用OH_NetConn_RefreshGlobalHttpProxyWithCallback时，该回调最多会被调用一次。
 *
 * @param result 重新认证结果。0表示成功，其他值表示失败。
 * @param proxy 当result为0时的全局HTTP代理信息。如果重新认证失败，proxy为NULL。<br>
 *     proxy对象由系统所有，仅在此次回调调用期间有效。调用者不能释放或修改它。
 *     如果调用者需要在回调返回后使用代理信息，必须进行深拷贝。
 * @param userContext 传递给OH_NetConn_RefreshGlobalHttpProxyWithCallback的用户定义数据。系统不会访问、复制或释放它。
 *
 * @since 26.0.0
 */
typedef void (*OH_NetConn_GlobalHttpProxyRefreshCallback)(
    int32_t result,
    const NetConn_HttpProxy *proxy,
    void *userContext);

/**
 * @brief 网络的特征集。
 *
 * @since 12
 * @version 1.0
 */
typedef struct NetConn_NetSpecifier {
    /**
     * 网络能力集。
     */
    NetConn_NetCapabilities caps;
    /**
     * 网络标识符。
     */
    char *bearerPrivateIdentifier;
} NetConn_NetSpecifier;
/**
 * @brief 网络可用回调。
 *
 * @param netHandle 网络句柄。
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_NetworkAvailable)(NetConn_NetHandle *netHandle);
/**
 * @brief 网络能力集变更回调。
 *
 * @param netHandle 网络句柄。
 * @param netCapabilities 网络能力集。
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_NetCapabilitiesChange)(NetConn_NetHandle *netHandle,
                                                 NetConn_NetCapabilities *netCapabilities);
/**
 * @brief 网络连接属性变更回调。
 *
 * @param netHandle 网络句柄。
 * @param connConnetionProperties 网络连接属性。
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_NetConnectionPropertiesChange)(NetConn_NetHandle *netHandle,
                                                         NetConn_ConnectionProperties *connConnetionProperties);
/**
 * @brief 网络断开回调。
 *
 * @param netHandle 网络句柄。
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_NetLost)(NetConn_NetHandle *netHandle);
/**
 * @brief 网络不可用回调，在指定的超时时间内网络未激活时触发该回调，如果未设置超时时间则不会触发该回调。
 *
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_NetUnavailable)(void);

/**
 * @brief 网络阻塞状态变更回调。
 *
 * @param netHandle 网络句柄。
 * @param blocked 指示网络是否将被阻塞的标志。true表示网络被阻塞，false表示网络未被阻塞。
 * @since 12
 * @version 1.0
 */
typedef void (*OH_NetConn_NetBlockStatusChange)(NetConn_NetHandle *netHandle, bool blocked);
/**
 * @brief 网络状态监听回调集合，所有回调事件需全部注册，无需关注的回调可以设为空实现。
 *
 * @since 12
 * @version 1.0
 */
typedef struct NetConn_NetConnCallback {
    /**
     * 网络可用回调。
     */
    OH_NetConn_NetworkAvailable onNetworkAvailable;
    /**
     * 网络能力集变更回调。
     */
    OH_NetConn_NetCapabilitiesChange onNetCapabilitiesChange;
    /**
     * 网络连接属性变更回调。
     */
    OH_NetConn_NetConnectionPropertiesChange onConnetionProperties;
    /**
     * 网络断开回调。
     */
    OH_NetConn_NetLost onNetLost;
    /**
     * 网络不可用回调, 在指定的超时时间内网络未激活时触发该回调，如果未设置超时时间则不会触发该回调。
     */
    OH_NetConn_NetUnavailable onNetUnavailable;
    /**
     * 网络阻塞状态变更回调。
     */
    OH_NetConn_NetBlockStatusChange onNetBlockStatusChange;
} NetConn_NetConnCallback;

/**
 * @brief 定义探测结果信息。
 *
 * @since 20
 */
typedef struct NetConn_ProbeResultInfo {
    /**
    * 丢包率，百分制，值100表示100%丢包；50表示50%丢包。
    */
    uint8_t lossRate;
    /**
     * Round-trip time in ms, including the maximum, minimum, average, and standard deviations.
     */
    uint32_t rtt[NETCONN_MAX_RTT_NUM];
} NetConn_ProbeResultInfo;

/**
 * @brief 定义网络跟踪路由选项。
 *
 * @since 20
 */
typedef struct NetConn_TraceRouteOption {
    /**
     * 探测结果最大跳数，需要和TraceRouteInfo设置一致，最大可设置30跳，默认为30跳。
     */
    uint8_t maxJumpNumber;
    /**
     * 探测包协议类型，默认为NETCONN_PACKETS_ICMP。
     */
    NetConn_PacketsType packetsType;
} NetConn_TraceRouteOption;

/**
 * @brief 定义跟踪路由信息。
 *
 * @since 20
 */
typedef struct NetConn_TraceRouteInfo {
    /**
    * 丢包率，百分制，值100表示100%丢包；50表示50%丢包。
    */
    uint8_t jumpNo;
    /**
    * 主机名或地址。
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