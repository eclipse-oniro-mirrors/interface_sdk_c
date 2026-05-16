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
 * @brief Provides C APIs for the ethernet module.
 *
 * @since 26.0.0
 */

/**
 * @file net_ethernet_type.h
 * @brief Defines the data structure for the C APIs of the ethernet module.
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
 * @brief Defines the ethernet iface mac address info.
 *
 * @since 26.0.0
 */
typedef struct Ethernet_MacAddressInfo  {
    /**
     * The ethernet iface name.
     * @since 26.0.0
     */
    char ifaceName[ETHERNET_MAX_STR_LEN];
    /**
     * The character array of device Mac address.
     * @since 26.0.0
     */
    char macAddr[ETHERNET_MAX_STR_LEN];
} Ethernet_MacAddrInfo;

/**
 * @brief Defines the ethernet iface mac address info list.
 *
 * @since 26.0.0
 */
typedef struct Ethernet_MacAddrInfoList  {
    /**
     * The ethernet mac address list.
     * @since 26.0.0
     */
    Ethernet_MacAddressInfo macInfoList[ETHERNET_MAX_NET_SIZE];
    /**
     * The real size of the macInfoList.
     * @since 26.0.0
     */
    int32_t macInfoListSize;
} Ethernet_MacAddrInfoList;

/**
 * @brief Defines the ethernet network address list.
 *
 * @since 26.0.0
 */
typedef struct Ethernet_NetAddrList {
    /**
     * The ethernet network address list.
     * @since 26.0.0
     */
    Ethernet_NetAddrInfo netAddrList[ETHERNET_MAX_NET_SIZE];
    /**
     * The real size of the netAddrList.
     * @since 26.0.0
     */
    int32_t netAddrListSize;
} Ethernet_NetAddrList;

/**
 * @brief Defines the ethernet iface net address info.
 *
 * @since 26.0.0
 */
typedef struct Ethernet_NetAddrInfo  {
    /**
     * The ethernet iface name.
     * @since 26.0.0
     */
    char ifaceName[ETHERNET_MAX_STR_LEN];
    /**
     * The network address
     * @since 26.0.0
     */
    Ethernet_NetAddr netAddrInfo;
} Ethernet_NetAddrInfo;

/**
 * @brief Defines the network address.
 *
 * @since 26.0.0
 */
typedef struct Ethernet_NetAddr {
    /**
     * Network address family
     * @since 26.0.0
     */
    uint8_t family;
    /**
     * Prefix length
     * @since 26.0.0
     */
    uint8_t prefixlen;
    /**
     * Port number
     * @since 26.0.0
     */
    uint8_t port;
    /**
     * IP Address
     * @since 26.0.0
     */
    char address[ETHERNET_MAX_STR_LEN];
} Ethernet_NetAddr;

#ifdef __cplusplus
}
#endif
#endif // NET_HTTP_TYPE_H

/** @} */
