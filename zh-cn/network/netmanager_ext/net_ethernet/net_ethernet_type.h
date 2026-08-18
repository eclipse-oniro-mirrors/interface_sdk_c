/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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
 * @addtogroup netmanager_ext
 * @{
 *
 * @brief 为以太网网卡模块提供C接口。
 *
 * @since 26.0.0
 */

/**
 * @file net_ethernet_type.h
 * @brief 为以太网网卡模块C接口定义数据结构。
 *
 * @library libnet_ethernet.so
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetManager.Ethernet
 * @since 26.0.0
 */

#ifndef NET_ETHERNET_TYPE_H
#define NET_ETHERNET_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @since 26.0.0
 */
#define ETHERNET_MAX_NET_SIZE 32
#define ETHERNET_MAX_STR_LEN 256

/**
 * @brief 以太网网卡MAC地址信息。
 *
 * @since 26.0.0
 */
typedef struct Ethernet_MacAddressInfo  {
    /**
     * 以太网网卡名称。
     * @since 26.0.0
     */
    char ifaceName[ETHERNET_MAX_STR_LEN];
    /**
     * 以太网网卡MAC地址。
     * @since 26.0.0
     */
    char macAddr[ETHERNET_MAX_STR_LEN];
} Ethernet_MacAddressInfo;

/**
 * @brief 以太网网卡MAC地址信息列表。
 *
 * @since 26.0.0
 */
typedef struct Ethernet_MacAddrInfoList  {
    /**
     * 以太网网卡MAC地址列表。
     * @since 26.0.0
     */
    Ethernet_MacAddressInfo macInfoList[ETHERNET_MAX_NET_SIZE];
    /**
     * macInfoList数组的实际大小。
     * @since 26.0.0
     */
    int32_t macInfoListSize;
} Ethernet_MacAddrInfoList;

/**
 * @brief 网络地址。
 *
 * @since 26.0.0
 */
typedef struct Ethernet_NetAddr {
    /**
     * 网络地址族。IPv4 = 1，IPv6 = 2。
     * @since 26.0.0
     */
    uint8_t family;
    /**
     * 前缀长度。
     * @since 26.0.0
     */
    uint8_t prefixlen;
    /**
     * 端口号。
     * @since 26.0.0
     */
    uint16_t port;
    /**
     * IP地址。
     * @since 26.0.0
     */
    char address[ETHERNET_MAX_STR_LEN];
} Ethernet_NetAddr;

/**
 * @brief 以太网网卡网络地址信息，包含以太网网卡名称及网络地址信息。
 *
 * @since 26.0.0
 */
typedef struct Ethernet_NetAddrInfo  {
    /**
     * 以太网网卡名称。
     * @since 26.0.0
     */
    char ifaceName[ETHERNET_MAX_STR_LEN];
    /**
     * 网络地址。
     * @since 26.0.0
     */
    Ethernet_NetAddr netAddrInfo[ETHERNET_MAX_NET_SIZE];
    /**
     * 网络地址数组的实际大小。
     * @since 26.0.0
     */
    int32_t netAddrInfoSize;
} Ethernet_NetAddrInfo;

/**
 * @brief 以太网网卡网络地址列表。
 *
 * @since 26.0.0
 */
typedef struct Ethernet_NetAddrList {
    /**
     * 以太网网络地址列表。
     * @since 26.0.0
     */
    Ethernet_NetAddrInfo netAddrList[ETHERNET_MAX_NET_SIZE];
    /**
     * netAddrList的实际大小。
     * @since 26.0.0
     */
    int32_t netAddrListSize;
} Ethernet_NetAddrList;

#ifdef __cplusplus
}
#endif
#endif // NET_HTTP_TYPE_H

/** @} */