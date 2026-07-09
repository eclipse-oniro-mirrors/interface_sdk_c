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
 * @brief 为网络管理数据网络连接模块提供C接口。
 *
 * @since 11
 * @version 1.0
 */

/**
 * @file net_connection.h
 *
 * @brief 为网络管理数据网络连接模块提供C接口。
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
 * @brief 查询是否有默认激活的数据网络。
 *
 * @param hasDefaultNet 是否有默认网络。
 * @return 0 - 成功。 201 - 缺少权限。
 *     <br>401 - 参数错误。 2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_HasDefaultNet(int32_t *hasDefaultNet);

/**
 * @brief 获取激活的默认的数据网络。
 *
 * @param netHandle 存放网络ID。
 * @return 0 - 成功。 201 - 缺少权限。
 *     <br>401 - 参数错误。 2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_GetDefaultNet(NetConn_NetHandle *netHandle);

/**
 * @brief 查询默认数据网络是否计流量。
 *
 * @param isMetered 是否激活。
 * @return 0 - 成功。 201 - 缺少权限。
 *     <br>401 - 参数错误。 2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_IsDefaultNetMetered(int32_t *isMetered);

/**
 * @brief 查询某个数据网络的链路信息。
 *
 * @param netHandle 存放网络ID。
 * @param prop 存放链路信息。
 * @return 0 - 成功。 201 - 缺少权限。
 *     <br>401 - 参数错误。 2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_GetConnectionProperties(NetConn_NetHandle *netHandle, NetConn_ConnectionProperties *prop);

/**
 * @brief 查询某个网络的能力集。
 *
 * @param netHandle 存放网络ID。
 * @param netCapabilities 存放能力集。
 * @return 0 - 成功。 201 - 缺少权限。
 *     <br>401 - 参数错误. 2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_GetNetCapabilities(NetConn_NetHandle *netHandle, NetConn_NetCapabilities *netCapabilities);

/**
 * @brief 查询默认的网络代理。
 *
 * @param httpProxy 存放代理配置信息。
 * @return 0 - 成功。 201 - 缺少权限。
 *     <br>401 - 参数错误. 2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_GetDefaultHttpProxy(NetConn_HttpProxy *httpProxy);

/**
 * @brief 通过netId获取DNS结果。
 *
 * @param host 所需查询的host名。
 * @param serv 服务名。
 * @param hint 指向addrinfo结构体的指针。
 * @param res 存放DNS查询结果，以链表形式返回。
 * @param netId DNS查询netId为0时，使用默认netId查询。
 * @return 0 - 成功。 201 - 缺少权限。
 *     <br>401 - 参数错误。 2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 * @permission ohos.permission.INTERNET
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_GetAddrInfo(char *host, char *serv, struct addrinfo *hint, struct addrinfo **res, int32_t netId);

/**
 * @brief 释放DNS结果。
 *
 * @param res DNS查询结果链表头。
 * @return 0 - 成功。 201 - 缺少权限。
 *     <br>401 - 参数错误。 2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 * @permission ohos.permission.INTERNET
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_FreeDnsResult(struct addrinfo *res);

/**
 * @brief 查询所有激活的数据网络。
 *
 * @param netHandleList 网络信息列表。
 * @return 0 - 成功。 201 - 缺少权限。
 *     <br>401 - 参数错误。 2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 11
 * @version 1.0
 */
int32_t OH_NetConn_GetAllNets(NetConn_NetHandleList *netHandleList);
/**
 * @brief 注册自定义DNS解析器。
 *
 * @param resolver 指向自定义DNS解析器的指针。
 * @return 0 - 成功。 401 - 参数错误。
 *     <br>2100002 - 无法连接到服务。  2100003 - 内部错误。
 * @syscap SystemCapability.Communication.NetManager.Core
 * @deprecated since 13
 * @useinstead OH_NetConn_RegisterDnsResolver
 * @since 11
 * @version 1.0
 */
int32_t OHOS_NetConn_RegisterDnsResolver(OH_NetConn_CustomDnsResolver resolver);

/**
 * @brief 取消注册自定义DNS解析器。
 *
 * @return 0 - 成功。
 *     <br>2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 * @syscap SystemCapability.Communication.NetManager.Core
 * @deprecated since 13
 * @useinstead OH_NetConn_UnregisterDnsResolver
 * @since 11
 * @version 1.0
 */
int32_t OHOS_NetConn_UnregisterDnsResolver(void);
/**
 * @brief 注册自定义DNS解析器。不再使用时，应调用 {@link OH_NetConn_UnregisterDnsResolver}注销自定义DNS解析器。
 * <br>建议使用{@link OH_NetConn_RegisterCustomDnsResolver}接口注册。当使用{@link OH_NetConn_RegisterCustomDnsResolver}时，需要使用
 * {@link OH_NetConn_UnregisterCustomDnsResolver}接口取消注册。
 *
 * @param resolver 指向自定义DNS解析器的指针。
 * @return 返回结果码。
 *     <br>NETMANAGER_EXT_SUCCESS 如果操作成功。
 *     <br>NETMANAGER_ERR_PARAMETER_ERROR 参数错误。请输入正确的参数。
 * @deprecated since 26.0.0
 * @useinstead OH_NetConn_RegisterCustomDnsResolver
 * @since 13
 * @version 1.0
 */
int32_t OH_NetConn_RegisterDnsResolver(OH_NetConn_CustomDnsResolver resolver);
/**
 * @brief 取消注册自定义DNS解析器。
 *
 * @return 0 - 成功。
 *     <br>2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 * @deprecated since 26.0.0
 * @useinstead OH_NetConn_UnregisterCustomDnsResolver
 * @since 13
 * @version 1.0
 */
int32_t OH_NetConn_UnregisterDnsResolver(void);
/**
 * @brief 注册自定义DNS解析器。注册后，系统DNS解析请求将优先回调该解析器，由开发者按需返回自定义解析结果；若未返回自定义结果，则继续使用系统默认DNS解析规则。
 * <br>同一时间全局仅支持一个自定义DNS解析器生效。如需更换解析器，应先调用{@link OH_NetConn_UnregisterCustomDnsResolver}注销已注册的解析器，再重新注册。
 * <br>作用范围：适用于系统DNS查询，以及应用通过系统网络库发起的DNS查询；不适用于应用自行实现的HTTPDNS解析、加密DNS解析（如 DoH/DoT）等非系统 DNS 通道的解析请求。不再使用时，应调用
 * {@link OH_NetConn_UnregisterCustomDnsResolver}注销自定义DNS解析器。
 *
 * @param resolver 指向自定义DNS解析器的指针。
 * @return 0 - 成功。
 *     <br>401 - 参数错误。
 *     <br>2101008 - 解析器已存在。
 * @stagemodelonly
 * @since 26.0.0
 */
int32_t OH_NetConn_RegisterCustomDnsResolver(OH_NetConn_CustomDnsResolver resolver);

/**
 * @brief 取消注册自定义DNS解析器。
 *
 * @return 0 - 成功。
 *     <br>2100003 - 内部错误。
 * @stagemodelonly
 * @since 26.0.0
 */
int32_t OH_NetConn_UnregisterCustomDnsResolver(void);

/**
 * @brief 将套接字绑定到特定的网络。
 *
 * @param socketFd 由用户构造的套接字。
 * @param netHandle 指针类型，指向包含网络ID的网络句柄。
 * @return 0 - 成功。
 *     <br>401 - 参数错误。
 *     <br>2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
int32_t OH_NetConn_BindSocket(int32_t socketFd, NetConn_NetHandle *netHandle);

/**
 * @brief 为当前应用设置http代理配置信息。
 *
 * @param httpProxy 需要设置的http代理配置信息。
 * @return 0 - 成功。
 *     <br>401 - 参数错误。
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
int32_t OH_NetConn_SetAppHttpProxy(NetConn_HttpProxy *httpProxy);

/**
 * @brief 注册监听应用http代理变化的回调。
 *
 * @param appHttpProxyChange 需要注册的监听回调。
 * @param callbackId 回调注册后生成的id, 关联已注册的回调。
 * @return 0 - 成功。
 *     <br>401 - 参数错误。
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
int32_t OH_NetConn_RegisterAppHttpProxyCallback(OH_NetConn_AppHttpProxyChange appHttpProxyChange, uint32_t *callbackId);

/**
 * @brief 注销监听应用http代理变化的回调。
 *
 * @param callbackId 需要被注销的回调所对应的id。
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
void OH_NetConn_UnregisterAppHttpProxyCallback(uint32_t callbackId);

/**
 * @brief 请求全局HTTP代理重新认证，并通过一次性回调报告结果。
 *
 * 该函数提交异步重新认证请求。返回值为0表示请求已被接受，不表示重新认证成功。
 * 最终结果通过回调报告。<br>
 *
 * 如果该函数返回0，回调最多会被调用一次。回调被调用后，将由系统自动释放。<br>
 *
 * 如果该函数返回非0值，回调不会被调用。<br>
 *
 * 回调可能在系统工作线程上调用。调用者必须确保回调实现是线程安全的并快速返回。<br>
 *
 * 调用者必须确保回调函数和userData在回调被调用之前保持有效。
 *
 * @permission ohos.permission.INTERNET
 * @param callback 用于接收重新认证结果的一次性回调，不能为NULL。
 * @param userContext 传递给回调的用户定义数据，可以为NULL。系统不会访问、复制或释放它。
 * @return <ul><li>0 - 成功。</li>
 *     <li>201 - 权限被拒。</li>
 *     <li>401 - 参数错误。</li></ul>
 * @since 26.0.0
 */
int32_t OH_NetConn_RefreshGlobalHttpProxyWithCallback(
    OH_NetConn_GlobalHttpProxyRefreshCallback callback,
    void *userContext);

/**
 * @brief 注册监听网络状态变化的回调。
 *
 * @param netSpecifier 网络特征集。
 * @param callback 注册的回调函数集合。
 * @param timeout 超时时间，单位为毫秒，为0时表示无限等待。
 * @param callbackId 出参，对应本次注册成功的回调。
 * @return 0 - 成功。
 *     <br>201 - 缺少权限。
 *     <br>401 - 参数错误。
 *     <br>2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 *     <br>2101008 - 回调已注册。
 *     <br>2101022 - 请求数超出了允许的最大值。
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
int32_t OH_NetConn_RegisterNetConnCallback(NetConn_NetSpecifier *specifier, NetConn_NetConnCallback *netConnCallback,
                                           uint32_t timeout, uint32_t *callbackId);

/**
 * @brief 注册监听默认网络状态变化的回调。
 *
 * @param callback 注册的回调函数集合。
 * @param callbackId 出参，对应本次注册成功的回调。
 * @return 0 - 成功。
 *     <br>201 - 缺少权限。
 *     <br>401 - 参数错误。
 *     <br>2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 *     <br>2101008 - 回调已注册。
 *     <br>2101022 - 请求数超出了允许的最大值。
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
int32_t OH_NetConn_RegisterDefaultNetConnCallback(NetConn_NetConnCallback *netConnCallback, uint32_t *callbackId);

/**
 * @brief 注销监听网络状态变化的回调。
 *
 * @param callBackId 需要被注销的回调对应ID。
 * @return 0 - 成功。
 *     <br>201 - 缺少权限。
 *     <br>401 - 参数错误。
 *     <br>2100002 - 无法连接到服务。
 *     <br>2100003 - 内部错误。
 *     <br>2101007 - 回调不存在。
 * @permission ohos.permission.GET_NETWORK_INFO
 * @syscap SystemCapability.Communication.NetManager.Core
 * @since 12
 * @version 1.0
 */
int32_t OH_NetConn_UnregisterNetConnCallback(uint32_t callBackId);
/**
 * @brief 设置当前PAC脚本（Proxy Auto-Configuration Script，代理自动配置脚本）的URL地址，比如：http://127.0.0.1:21998/PacProxyScript.pac。
 * 通过解析脚本地址可以获取代理信息。
 *
 * @param pacUrl 需要设置的PAC脚本地址。
 * @return 结果定义在 {@link NetConn_ErrorCode}。
 *     <br>{@link NETCONN_SUCCESS} 成功。
 *     <br>{@link NETCONN_PERMISSION_DENIED} 缺少权限。
 *     <br>{@link NETCONN_PARAMETER_ERROR} 参数错误。
 *     <br>{@link NETCONN_OPERATION_FAILED} 无法连接到服务。
 *     <br>{@link NETCONN_INTERNAL_ERROR} 内部错误。
 * @permission ohos.permission.SET_PAC_URL
 * @since 15
 */
NetConn_ErrorCode OH_NetConn_SetPacUrl(const char *pacUrl);

/**
 * @brief 获取系统级代理自动配置（PAC）脚本地址。
 *
 * @param pacUrl 获取的PAC脚本地址。
 * @return 结果定义在 {@link NetConn_ErrorCode}。
 *     <br>{@link NETCONN_SUCCESS} 成功。
 *     <br>{@link NETCONN_PARAMETER_ERROR} 参数错误。
 *     <br>{@link NETCONN_OPERATION_FAILED} 无法连接到服务。
 *     <br>{@link NETCONN_INTERNAL_ERROR} 内部错误。
 * @since 15
 */
NetConn_ErrorCode OH_NetConn_GetPacUrl(char *pacUrl);
/**
 * @brief 查询网络探测结果。若出现异常（例如断网），导致发送请求失败，则接口会立即返回，不再进行后续探测。本接口涉及网络操作，避免在主流程调用，否则可能导致UI卡顿。
 *
 * @param destination 需要探测的目标域名或者IP地址。对于域名，探测前会进行域名解析，将域名解析为目标IP，之后发起探测。域名解析时间不包含在duration指示的探测持续时间内。
 * @param duration 探测持续时间。单位：秒。探测间隔为1秒，因此可通过本字段控制探测次数。
 * @param probeResultInfo 丢包率和往返时间（RTT）。
 * @return 0 - 成功。
 *     <br>201 - 缺少权限。
 *     <br>401 - 参数错误。
 *     <br>2100003 - 内部错误。
 * @permission ohos.permission.INTERNET
 * @since 20
 */
int32_t OH_NetConn_QueryProbeResult(char *destination, int32_t duration, NetConn_ProbeResultInfo *probeResultInfo);
/**
 * @brief 查询网络跟踪路由。
 *
 * @param destination 目的地址。
 * @param option 路由参数选项。
 * @param traceRouteInfo 路由结果。需传入数组指针，数组大小代表路由跳数，默认30跳。若自定义跳数，则需保证数组大小与option字段中的maxJumpNumber数值保持一致。
 * @return 0 - 成功。
 *     <br>201 - 缺少权限。
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