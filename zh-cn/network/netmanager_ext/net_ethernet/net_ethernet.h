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
 * @file net_ethernet.h
 * @brief 为以太网网卡模块提供C接口。
 *
 * @library libnet_ethernet.so
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetManager.Ethernet
 * @since 26.0.0
 */

#ifndef NET_ETHERNET_H
#define NET_ETHERNET_H

#include <stdint.h>
#include <string.h>

#include "net_ethernet_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取以太网网卡MAC地址列表。
 *
 * @permission ohos.permission.GET_ETHERNET_LOCAL_MAC
 * @param macAddrList 以太网网卡MAC地址列表。
 * @return 0 - 成功。 201 - 缺少权限。
 *     <br>2200001 - 参数错误。 2200002 - 无法连接到服务。
 *     <br>2201005 - 设备信息不存在。
 * @syscap SystemCapability.Communication.NetManager.Ethernet
 * @since 26.0.0
 */
int32_t OH_Ethernet_GetMacAddress(Ethernet_MacAddrInfoList *macAddrList);

/**
 * @brief 获取以太网网卡IP地址列表。
 *
 * @permission ohos.permission.GET_NETWORK_INFO
 * @param netAddrList 以太网网卡IP地址列表。
 * @return 0 - 成功。 201 - 缺少权限。
 *     <br>2200001 - 参数错误。 2200002 - 无法连接到服务。
 *     <br>2201005 - 设备信息不存在。
 * @syscap SystemCapability.Communication.NetManager.Ethernet
 * @since 26.0.0
 */
int32_t OH_Ethernet_GetNetAddress(Ethernet_NetAddrList *netAddrList);

#ifdef __cplusplus
}
#endif
#endif // NET_ETHERNET_H

/** @} */