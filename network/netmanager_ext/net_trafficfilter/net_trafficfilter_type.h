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
 * @brief Traffic filter and redirection subsystem - common types and error codes definition.
 *
 * @since 26.0.0
 */

/**
 * @file net_trafficfilter_type.h
 * @brief Declares the common types and error codes required for network traffic filtering and redirection. This header
 * file defines the match condition structs (such as IP addresses, ports, and interfaces) used in traffic filtering and
 * redirection, configuration structs (such as packet filter rules and redirection rules), and error codes returned by
 * operations.
 * <br>This header file is used to construct parameters and parse return values when APIs such as
 * {@link OH_TrafficFilter_CreateRedirector} are called.
 *
 * @library libnet_trafficfilter.so
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetManager.NetFirewall
 * @since 26.0.0
 */

#ifndef NET_TRAFFICFILTER_TYPE_H
#define NET_TRAFFICFILTER_TYPE_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Maximum length of the IP address byte array (compatible with both IPv4 and IPv6).
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_IP_ADDRLEN       16

/**
 * @brief Maximum number of IP addresses supported for multi–IP address matching.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_MAX_MULTI_IP_COUNT  16

/**
 * @brief Maximum number of ports supported for multi-port matching.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_MAX_MULTI_PORT_COUNT 64

/**
 * @brief NFQueue packet copy mode: copies only metadata.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_NFQUEUE_COPY_META   0

/**
 * @brief NFQueue packet copy mode: copies the entire packet.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_NFQUEUE_COPY_PACKET 0xFFFF

/**
 * @brief Default length of the copied NFQueue packet, in bytes. If the value is **0xFFFF**, the entire packet is
 * copied; if a smaller value, such as **128**, is used, only the packet header is copied.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_DEFAULT_COPY_LEN    0xFFFF

/**
 * @brief Default maximum length of the NFQueue queue (number of packets).
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_DEFAULT_QUEUE_MAXLEN  1024

/**
 * @brief NFQueue queue flag: FAIL-OPEN mode. When a user-mode process crashes, the kernel automatically allows packets
 * to pass to avoid network interruption.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_NFQUEUE_FLAG_FAIL_OPEN  0x1

/**
 * @brief Maximum length of MAC address string (XX:XX:XX:XX:XX:XX)
 * @since 26.1.0
 */
#define OH_TRAFFICFILTER_MAC_ADDRSTRLEN       18

/**
 * @brief Minimum priority.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_MIN_PRIORITY        1

/**
 * @brief Maximum priority.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_MAX_PRIORITY        10000

/**
 * @brief Minimum group ID value.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_MIN_GROUP_ID        1

/**
 * @brief Maximum group ID value.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_MAX_GROUP_ID        65535

/**
 * @brief Maximum length of the network interface name.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_IFNAMSIZ            32

/**
 * @brief Protocol constant: any protocol.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_PROTO_ANY           0
/**
 * @brief Protocol constant: TCP.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_PROTO_TCP           6
/**
 * @brief Protocol constant: UDP.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_PROTO_UDP           17
/**
 * @brief Protocol constant: ICMP.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_PROTO_ICMP          1
/**
 * @brief Protocol constant: ICMPv6.
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_PROTO_ICMPV6        58

/**
 * @brief Defines the error codes for traffic filtering and redirection.
 *
 * @since 26.0.0
 */
typedef enum OH_TrafficFilter_ErrCode {
    /**
     * @brief Operation succeeded.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_OK = 0,

    /**
     * @brief Base value for the error code.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_E_BASE = 29410000,

    /**
     * @brief Missing permissions.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED = 201,

    /**
     * @brief Parameter error (invalid priority, IP address, port, or group ID).
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_ERROR_INVALID_PARAM = (OH_TRAFFICFILTER_E_BASE + 101),

    /**
     * @brief Resource not found (rule, target, process, or group ID not found).
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_ERROR_NOT_FOUND = (OH_TRAFFICFILTER_E_BASE + 102),

    /**
     * @brief Too many rules.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_ERROR_TOO_MANY_RULES = (OH_TRAFFICFILTER_E_BASE + 103),

    /**
     * @brief Group ID already in use.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_ERROR_GROUP_ID_IN_USE = (OH_TRAFFICFILTER_E_BASE + 104),

    /**
     * @brief NFQueue error (initialization failed or no available queue).
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_ERROR_NFQUEUE_ERROR = (OH_TRAFFICFILTER_E_BASE + 105)
} OH_TrafficFilter_ErrCode;

/**
 * @brief Defines an IP match type.
 *
 * @since 26.0.0
 */
typedef enum OH_TrafficFilter_IPMatchType {
    /**
     * @brief Any IP address.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_MATCH_ANY = 0,
    /**
     * @brief Single IP address.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_MATCH_SINGLE,
    /**
     * @brief CIDR (for example, **192.168.1.0/24**, which matches all IP addresses in the subnet).
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_MATCH_CIDR,
    /**
     * @brief IP address range.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_MATCH_RANGE,
    /**
     * @brief Multiple IP addresses.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_MATCH_MULTI
} OH_TrafficFilter_IPMatchType;

/**
 * @brief Defines an IP address family.
 *
 * @since 26.0.0
 */
typedef enum OH_TrafficFilter_IPFamily {
    /**
     * @brief Unspecified IP address family.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_FAMILY_UNSPEC = 0,
    /**
     * @brief IPv4 address family.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_FAMILY_V4 = 1,
    /**
     * @brief IPv6 address family.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_FAMILY_V6 = 2
} OH_TrafficFilter_IPFamily;

/**
 * @brief Defines a port match type.
 *
 * @since 26.0.0
 */
typedef enum OH_TrafficFilter_PortMatchType {
    /**
     * @brief Any port.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_PORT_MATCH_ANY = 0,
    /**
     * @brief Single port.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_PORT_MATCH_SINGLE,
    /**
     * @brief Port range.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_PORT_MATCH_RANGE,
    /**
     * @brief Multiple ports.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_PORT_MATCH_MULTI
} OH_TrafficFilter_PortMatchType;

/**
 * @brief Enumerates the hook points, specifying where the rule takes effect in the network protocol stack. As packets
 * pass through the kernel network protocol stack, hook points are triggered at different stages, and the rule
 * intercepts packets at the corresponding hook points. For example, the INPUT chain processes packets entering the
 * local device, and the OUTPUT chain processes packets sent from the local device.
 *
 * @since 26.0.0
 */
typedef enum OH_TrafficFilter_HookPoint {
    /**
     * @brief INPUT chain that processes packets received by the local host.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_HOOK_INPUT = 0,
    /**
     * @brief OUTPUT chain that processes packets sent from the local host.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_HOOK_OUTPUT,
    /**
     * @brief FORWARD chain that processes packets forwarded by the local host.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_HOOK_FORWARD,
    /**
     * @brief PREROUTING chain that processes packets that have arrived at the NIC but not been routed.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_HOOK_PREROUTING,
    /**
     * @brief POSTROUTING chain that processes packets about to be sent from the NIC.
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_HOOK_POSTROUTING
} OH_TrafficFilter_HookPoint;

/**
 * @brief IP address in binary form, supports both IPv4 and IPv6
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPAddress {
    /**
     * @brief Address family, If not explicitly set, IPv4 is used by default.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPFamily family;
    /**
     * @brief IP address bytes.
     *
     * The bytes must be stored in network byte order.
     * For IPv4, {@link addr}[0] to {@link addr}[3] store the IPv4 address,
     * and {@link addr}[4] to {@link addr}[15] must be set to 0.
     * For IPv6, {@link addr}[0] to {@link addr}[15] store the IPv6 address.
     *
     * If the bytes do not match the address layout required by {@link family},
     * APIs using this structure return {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}.
     *
     * @since 26.0.0
     */
    uint8_t addr[OH_TRAFFICFILTER_IP_ADDRLEN];
} OH_TrafficFilter_IPAddress;

/**
 * @brief IP match value for CIDR match
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPCidr {
    /**
     * @brief Base IP address of the CIDR block
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress base;
    /**
     * @brief CIDR prefix length
     * @since 26.0.0
     */
    uint8_t prefixLen;
} OH_TrafficFilter_IPCidr;

/**
 * @brief IP match value for range match
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPRange {
    /**
     * @brief Start IP address of the range
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress start;
    /**
     * @brief End IP address of the range
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress end;
} OH_TrafficFilter_IPRange;

/**
 * @brief IP match value for multi-IP match
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPMulti {
    /**
     * @brief Number of IP addresses in the array
     * @since 26.0.0
     */
    uint32_t ipCount;
    /**
     * @brief IP address array
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress ips[OH_TRAFFICFILTER_MAX_MULTI_IP_COUNT];
} OH_TrafficFilter_IPMulti;

/**
 * @brief IP match condition
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPMatch {
    /**
     * @brief Match type
     * @since 26.0.0
     */
    OH_TrafficFilter_IPMatchType type;
    /**
     * @brief Whether to invert the match result
     * @since 26.0.0
     */
    bool invert;
    /**
     * @brief Match rule
     * @since 26.0.0
     */
    union {
        /**
         * @brief Single IP address, used when type is OH_TRAFFICFILTER_IP_MATCH_SINGLE
         * @since 26.0.0
         */
        OH_TrafficFilter_IPAddress single;
        /**
         * @brief CIDR match value, used when type is OH_TRAFFICFILTER_IP_MATCH_CIDR
         * @since 26.0.0
         */
        OH_TrafficFilter_IPCidr cidr;
        /**
         * @brief IP range match value, used when type is OH_TRAFFICFILTER_IP_MATCH_RANGE
         * @since 26.0.0
         */
        OH_TrafficFilter_IPRange range;
        /**
         * @brief Multi-IP match value, used when type is OH_TRAFFICFILTER_IP_MATCH_MULTI
         * @since 26.0.0
         */
        OH_TrafficFilter_IPMulti multi;
    } value;
} OH_TrafficFilter_IPMatch;

/**
 * @brief interface match condition
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_InterfaceMatch {
    /**
     * @brief Whether interface matching is enabled
     * @since 26.0.0
     */
    bool enabled;
    /**
     * @brief Whether to invert the match result
     * @since 26.0.0
     */
    bool invert;
    /**
     * @brief Whether the interface name is matched by prefix
     * @since 26.0.0
     */
    bool isPrefix;
    /**
     * @brief Interface name.
     *
     * The string must be encoded in UTF-8 and must be NUL-terminated.
     * The capacity of this buffer is {@link OH_TRAFFICFILTER_IFNAMSIZ} bytes,
     * including the terminating NUL character. Therefore, the maximum length
     * of the interface name is {@link OH_TRAFFICFILTER_IFNAMSIZ} - 1 bytes,
     * excluding the terminating NUL character.
     *
     * If {@link enabled} is true, this string must not be empty.
     * If the string is not NUL-terminated within {@link OH_TRAFFICFILTER_IFNAMSIZ}
     * bytes, or if its length exceeds {@link OH_TRAFFICFILTER_IFNAMSIZ} - 1 bytes,
     * APIs using this structure return {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}.
     *
     * If {@link enabled} is false, this field is ignored. It is recommended to set
     * this buffer to all zeros when interface matching is disabled.
     *
     * @since 26.0.0
     */
    char ifName[OH_TRAFFICFILTER_IFNAMSIZ];
} OH_TrafficFilter_InterfaceMatch;

/**
 * @brief Port match value for range match
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_PortRange {
    /**
     * @brief Start port of the range
     * @since 26.0.0
     */
    uint16_t startPort;
    /**
     * @brief End port of the range
     * @since 26.0.0
     */
    uint16_t endPort;
} OH_TrafficFilter_PortRange;

/**
 * @brief Port match value for multi-port match
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_PortMulti {
    /**
     * @brief Number of ports in the array
     * @since 26.0.0
     */
    uint32_t portCount;
    /**
     * @brief Port array
     * @since 26.0.0
     */
    uint16_t ports[OH_TRAFFICFILTER_MAX_MULTI_PORT_COUNT];
} OH_TrafficFilter_PortMulti;

/**
 * @brief Port match condition
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_PortMatch {
    /**
     * @brief Match type
     * @since 26.0.0
     */
    OH_TrafficFilter_PortMatchType type;
    /**
     * @brief Whether to invert the match result
     * @since 26.0.0
     */
    bool invert;
    /**
     * @brief Match rule
     * @since 26.0.0
     */
    union {
        /**
         * @brief Single port, used when type is OH_TRAFFICFILTER_PORT_MATCH_SINGLE
         * @since 26.0.0
         */
        uint16_t single;
        /**
         * @brief Port range match value, used when type is OH_TRAFFICFILTER_PORT_MATCH_RANGE
         * @since 26.0.0
         */
        OH_TrafficFilter_PortRange range;
        /**
         * @brief Multi-port match value, used when type is OH_TRAFFICFILTER_PORT_MATCH_MULTI
         * @since 26.0.0
         */
        OH_TrafficFilter_PortMulti multi;
    } value;
} OH_TrafficFilter_PortMatch;

/**
 * @brief Connection information structure
 *
 * Describes five-tuple connection information used to query process information.
 *
 * Initialization rule:
 * Before calling {@link OH_TrafficFilter_QueryProcess}, the caller must clear this structure
 * to zero, for example by using memset, and then set {@link size} to the actual size of the
 * structure allocated by the caller, usually sizeof(OH_TrafficFilter_ConnectionInfo).
 *
 * ABI compatibility rule:
 * The library uses {@link size} to determine which fields can be safely read.
 * If {@link size} is smaller than the minimum size required by the current API, the function
 * returns {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}. If {@link size} is larger than the
 * size known by the library, the extra fields are ignored. Newly added fields in future
 * versions should remain zero-initialized when not used.
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_ConnectionInfo {
    /**
     * @brief the actual size of the structure allocated by the caller.
     * @since 26.0.0
     */
    uint32_t size;
    /**
     * @brief Source IP address, supports IPv4 and IPv6.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress srcIp;
    /**
     * @brief Source port. 0 means any source port.
     * @since 26.0.0
     */
    uint16_t srcPort;
    /**
     * @brief Destination IP address, supports IPv4 and IPv6.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress dstIp;
    /**
     * @brief Destination port. 0 means any destination port.
     * @since 26.0.0
     */
    uint16_t dstPort;
    /**
     * @brief Protocol type.
     * Supported values:
     * - OH_TRAFFICFILTER_PROTO_TCP (6)
     * - OH_TRAFFICFILTER_PROTO_UDP (17)
     * @since 26.0.0
     */
    uint8_t protocol;
} OH_TrafficFilter_ConnectionInfo;

/**
 * @brief Process information structure.
 *
 * Stores process information returned by {@link OH_TrafficFilter_QueryProcess}.
 *
 * Initialization rule:
 * Before calling {@link OH_TrafficFilter_QueryProcess}, the caller must clear this structure
 * to zero, for example by using memset, and then set {@link size} to the actual size of the
 * structure allocated by the caller, usually sizeof(OH_TrafficFilter_ProcessInfo).
 *
 * ABI compatibility rule:
 * The library uses {@link size} to determine which output fields can be safely written.
 * Only fields fully covered by {@link size} are written by the library. If {@link size} is
 * smaller than the minimum size required to read the {@link size} field itself, the function
 * returns {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}. If {@link size} is larger than the
 * size known by the library, the extra fields are ignored.
 *
 * Output validity rule:
 * When {@link OH_TrafficFilter_QueryProcess} returns {@link OH_TRAFFICFILTER_OK}, fields
 * covered by {@link size} contain valid output values. When the function returns an error,
 * the caller must not rely on the values of output fields other than {@link size}.
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_ProcessInfo {
    /**
     * @brief the actual size of the structure allocated by the caller.
     * @since 26.0.0
     */
    uint32_t size;
    /**
     * @brief Process ID
     * @since 26.0.0
     */
    uint32_t pid;
    /**
     * @brief User ID
     * @since 26.0.0
     */
    uint32_t uid;
} OH_TrafficFilter_ProcessInfo;

/**
 * @brief Traffic redirector
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_Redirector OH_TrafficFilter_Redirector;

/**
 * @brief Traffic redirection rule.
 *
 * Defines a TCP traffic redirection rule to redirect matched traffic to the specified proxy server.
 *
 * Initialization rule:
 * Before calling {@link OH_TrafficFilter_AddRedirectRule}, the caller must clear this structure
 * to zero, for example by using memset, and then set {@link size} to the actual size of the
 * structure allocated by the caller, usually sizeof(OH_TrafficFilter_RedirectRule).
 *
 * ABI compatibility rule:
 * The library uses {@link size} to determine which fields can be safely read.
 * If {@link size} is smaller than the minimum size required by the current API, the function
 * returns {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}. If {@link size} is larger than the
 * size known by the library, the extra fields are ignored. Newly added fields in future
 * versions should remain zero-initialized when not used.
 *
 * Failure rule:
 * If {@link OH_TrafficFilter_AddRedirectRule} returns an error, the rule is not guaranteed
 * to be added or applied. The caller should check the return value before assuming that the
 * rule takes effect.
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_RedirectRule {
    /**
     * @brief the actual size of the structure allocated by the caller.
     * @since 26.0.0
     */
    uint32_t size;
    /**
     * @brief Priority (smaller number means higher priority, same rule as packet filter)
     * @since 26.0.0
     */
    uint32_t priority;
    /**
     * @brief Hook point (only PREROUTING and OUTPUT are supported)
     * @since 26.0.0
     */
    OH_TrafficFilter_HookPoint hookPoint;
    /**
     * @brief Protocol (fixed to TCP=6)
     * @since 26.0.0
     */
    uint8_t protocol;
    /**
     * @brief Source IP match condition
     * @since 26.0.0
     */
    OH_TrafficFilter_IPMatch srcIp;
    /**
     * @brief Source port match condition
     * @since 26.0.0
     */
    OH_TrafficFilter_PortMatch srcPort;
    /**
     * @brief Destination IP match condition
     * @since 26.0.0
     */
    OH_TrafficFilter_IPMatch dstIp;
    /**
     * @brief Destination port match condition
     * @since 26.0.0
     */
    OH_TrafficFilter_PortMatch dstPort;
    /**
     * @brief Incoming interface match condition
     * @since 26.0.0
     */
    OH_TrafficFilter_InterfaceMatch inInterface;
    /**
     * @brief Outgoing interface match condition
     * @since 26.0.0
     */
    OH_TrafficFilter_InterfaceMatch outInterface;
    /**
     * @brief Application UID range start (UINT32_MAX means any)
     * @since 26.0.0
     */
    uint32_t uidStart;
    /**
     * @brief Application UID range end (UINT32_MAX means any)
     * @since 26.0.0
     */
    uint32_t uidEnd;
    /**
     * @brief Proxy server IP address (supports IPv4 and IPv6)
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress proxyIp;
    /**
     * @brief Proxy server port
     * @since 26.0.0
     */
    uint16_t proxyPort;
} OH_TrafficFilter_RedirectRule;

/**
 * @brief Packet descriptor
 *
 * Contains five-tuple information and packet data
 * @since 26.1.0
 */
typedef struct OH_TrafficFilter_PacketDesc {
    /**
     * @brief Packet ID (assigned by kernel when packet arrives at netfilter)
     * @since 26.1.0
     */
    uint32_t packetId;
    /**
     * @brief Protocol type
     * @since 26.1.0
     */
    uint8_t protocol;
    /**
     * @brief Source IP address (supports IPv4 and IPv6)
     * @since 26.1.0
     */
    OH_TrafficFilter_IPAddress srcIp;
    /**
     * @brief Source port
     * @since 26.1.0
     */
    uint16_t srcPort;
    /**
     * @brief Destination IP address (supports IPv4 and IPv6)
     * @since 26.1.0
     */
    OH_TrafficFilter_IPAddress dstIp;
    /**
     * @brief Destination port
     * @since 26.1.0
     */
    uint16_t dstPort;
    /**
     * @brief Packet length
     * @since 26.1.0
     */
    uint32_t packetLen;
    /**
     * @brief Packet data pointer (user can modify, memory managed by system, valid only during callback)
     * @since 26.1.0
     */
    uint8_t* data;
    /**
     * @brief User data (used in callback)
     * @since 26.1.0
     */
    void* userData;
} OH_TrafficFilter_PacketDesc;

/**
 * @brief Packet decision type
 * @since 26.1.0
 */
typedef enum OH_TrafficFilter_PacketDecision {
    /**
     * @brief Accept packet
     * @since 26.1.0
     */
    OH_TRAFFICFILTER_DECISION_ACCEPT = 0,
    /**
     * @brief Drop packet
     * @since 26.1.0
     */
    OH_TRAFFICFILTER_DECISION_DROP
} OH_TrafficFilter_PacketDecision;

/**
 * @brief Packet callback function type
 *
 * @param packet Packet descriptor
 * @param userData User data
 * @return Packet decision (ACCEPT or DROP)
 * @since 26.1.0
 */
typedef OH_TrafficFilter_PacketDecision (*OH_TrafficFilter_PacketCallback)(
    const OH_TrafficFilter_PacketDesc* packet,
    void* userData
);

/**
 * @brief Packet copy mode enumeration
 * @since 26.1.0
 */
typedef enum OH_TrafficFilter_PacketCopyMode {
    /**
     * @brief Copy only metadata (no packet data)
     * @since 26.1.0
     */
    OH_TRAFFICFILTER_COPY_MODE_META = 0,
    /**
     * @brief Copy packet header only (specified by packetCopyLen)
     * @since 26.1.0
     */
    OH_TRAFFICFILTER_COPY_MODE_HEADER = 1,
    /**
     * @brief Copy entire packet
     * @since 26.1.0
     */
    OH_TRAFFICFILTER_COPY_MODE_FULL = 2,
    /**
     * @brief Copy packet with specified maximum length
     * @since 26.1.0
     */
    OH_TRAFFICFILTER_COPY_MODE_MAXLEN = 3
} OH_TrafficFilter_PacketCopyMode;

/**
 * @brief NFQueue configuration structure
 * - If `config` is **NULL**, the implementation applies the following default values:
 * - `packetCopyLen` = 0xFFFF (copy entire packet)
 * - `nfqueueMaxlen` = 0    (use system default, which is 1024)
 * - `nfqueueFlags`  = OH_TRAFFICFILTER_NFQUEUE_FLAG_FAIL_OPEN
 * - If `config` is **non-NULL**, the caller **must**:
 * 1. Zero-initialize the entire structure (e.g., `memset(&cfg, 0, sizeof(cfg))`).
 * 2. Set `size` = `sizeof(OH_TrafficFilter_Config)`.
 * 3. Set all other fields to valid values within the defined ranges (see below).
 * - **Failure** to follow this contract (e.g., incorrect `size`, out-of-range field values)
 * will cause the API to return `OH_TRAFFICFILTER_ERROR_INVALID_PARAM`.
 *
 * @note Failure to follow this initialization contract may lead to undefined behavior or binary incompatibility
 *     across versions.
 * @since 26.1.0
 */
typedef struct OH_TrafficFilter_Config {
    /**
     * @brief Must be set to `sizeof(OH_TrafficFilter_Config)` by the caller.
     * The caller is required to zero-initialize the structure first, then set this field.
     * The implementation uses this value to determine the valid data range for binary compatibility.
     * @since 26.1.0
     */
    uint32_t size;
    /**
     * @brief NFQueue packet copy mode, see OH_TrafficFilter_PacketCopyMode
     * @since 26.1.0
     */
    uint32_t packetCopyMode;
    /**
     * @brief NFQueue packet copy length in bytes, 0xFFFF means entire packet, smaller values copy only header
     * @since 26.1.0
     */
    uint32_t packetCopyLen;
    /**
     * @brief NFQueue maximum queue length (number of packets), 0 means system default (1024)
     * @since 26.1.0
     */
    uint32_t nfqueueMaxlen;
    /**
     * @brief NFQueue queue flags, see OH_TRAFFICFILTER_NFQUEUE_FLAG_* definitions
     * @since 26.1.0
     */
    uint32_t nfqueueFlags;
} OH_TrafficFilter_Config;

/**
 * @brief MAC address match condition
 *
 * Matches packets based on MAC address
 * Only source MAC is supported
 * @since 26.1.0
 */
typedef struct OH_TrafficFilter_MACMatch {
    /**
     * @brief Enable MAC address matching
     * @since 26.1.0
     */
    bool enable;
    /**
     * @brief Whether to invert the match result
     * @since 26.1.0
     */
    bool invert;
    /**
     * @brief Source MAC address in "XX:XX:XX:XX:XX:XX" format.
     * ASCII/UTF-8 encoded, must be null-terminated.
     * OH_TRAFFICFILTER_MAC_ADDRSTRLEN includes the null terminator;
     * maximum valid string length is 17 characters.
     * Invalid format will cause the rule-setting API to return OH_TRAFFICFILTER_ERROR_INVALID_PARAM.
     * @since 26.1.0
     */
    char srcMac[OH_TRAFFICFILTER_MAC_ADDRSTRLEN];
} OH_TrafficFilter_MACMatch;

/**
 * @brief TCP flags match condition
 *
 * Matches TCP packets based on TCP flag settings
 * @since 26.1.0
 */
typedef struct OH_TrafficFilter_TCPFlagsMatch {
    /**
     * @brief Enable TCP flags matching
     * @since 26.1.0
     */
    bool enable;
    /**
     * @brief Flag mask (which flags to check, use OH_TRAFFICFILTER_TCP_FLAG_* constants)
     * @since 26.1.0
     */
    uint8_t flagMask;
    /**
     * @brief Flag to compare (which flags must be set)
     * @since 26.1.0
     */
    uint8_t flagComp;
} OH_TrafficFilter_TCPFlagsMatch;

/**
 * @brief Connection tracking match condition
 *
 * Matches packets based on connection tracking states
 * @since 26.1.0
 */
typedef struct OH_TrafficFilter_ConntrackMatch {
    /**
     * @brief Enable conntrack matching
     * @since 26.1.0
     */
    bool enable;
    /**
     * @brief Connection states (use OH_TRAFFICFILTER_CT_STATE_* bitmap)
     * @since 26.1.0
     */
    uint8_t stateMask;
} OH_TrafficFilter_ConntrackMatch;

/**
 * @brief Packet filter rule
 *
 * Defines conditions for matching packets.
 * 1. **Initialization Contract (Caller Side)**:
 * - The caller must **zero-initialize** the entire structure (e.g., via `memset`) before use.
 * - The `size` field **must** be explicitly set to `sizeof(OH_TrafficFilter_FilterRule)`.
 * - If `size` is less than `sizeof(OH_TrafficFilter_FilterRule)`, the implementation will only read the stable
 * prefix fields up to `size`, ignoring subsequent bytes.
 *
 * 2. **Read Contract (Implementation Side)**:
 * - The implementation strictly determines the valid field range based on the `size` value.
 * - If `size` < `sizeof(OH_TrafficFilter_FilterRule)`, the implementation treats it as an older version and reads
 * only the prefix fields compatible with that size.
 * - If `size` is 0 or the pointer is NULL, the implementation must return an error.
 *
 * @note Failure to follow this initialization contract may lead to undefined behavior or binary incompatibility across
 *     versions.
 * @since 26.1.0
 */
typedef struct OH_TrafficFilter_FilterRule {
    /**
     * @brief Must be set to `sizeof(OH_TrafficFilter_FilterRule)` by the caller.
     * The caller is required to zero-initialize the structure first, then set this field.
     * The implementation uses this value to determine the valid data range for binary compatibility.
     * @since 26.1.0
     */
    uint32_t size;
    /**
     * @brief Priority (smaller number means higher priority)
     * @since 26.1.0
     */
    uint32_t priority;
    /**
     * @brief Hook point
     * @since 26.1.0
     */
    OH_TrafficFilter_HookPoint hookPoint;
    /**
     * @brief Protocol (0=any, 6=TCP, 17=UDP)
     * @since 26.1.0
     */
    uint8_t protocol;
    /**
     * @brief Source IP match condition
     * @since 26.1.0
     */
    OH_TrafficFilter_IPMatch srcIp;
    /**
     * @brief Source port match condition
     * @since 26.1.0
     */
    OH_TrafficFilter_PortMatch srcPort;
    /**
     * @brief Destination IP match condition
     * @since 26.1.0
     */
    OH_TrafficFilter_IPMatch dstIp;
    /**
     * @brief Destination port match condition
     * @since 26.1.0
     */
    OH_TrafficFilter_PortMatch dstPort;
    /**
     * @brief Incoming interface match condition
     * @since 26.1.0
     */
    OH_TrafficFilter_InterfaceMatch inInterface;
    /**
     * @brief Outgoing interface match condition
     * @since 26.1.0
     */
    OH_TrafficFilter_InterfaceMatch outInterface;
    /**
     * @brief Application UID range start (inclusive). Valid range: 0 to UINT32_MAX.
     * To match any UID, set both uidStart and uidEnd to UINT32_MAX.
     * If uidStart > uidEnd, the rule-setting API returns OH_TRAFFICFILTER_ERROR_INVALID_PARAM.
     * After zero-initialization, uidStart=0 and uidEnd=0, which matches UID 0 only.
     * @since 26.1.0
     */
    uint32_t uidStart;
    /**
     * @brief Application UID range end (inclusive). Valid range: 0 to UINT32_MAX.
     * See uidStart for usage details.
     * @since 26.1.0
     */
    uint32_t uidEnd;
    /**
     * @brief MAC address match condition (only source MAC)
     * @since 26.1.0
     */
    OH_TrafficFilter_MACMatch macMatch;
    /**
     * @brief TCP flags match condition (valid only for TCP protocol)
     * @since 26.1.0
     */
    OH_TrafficFilter_TCPFlagsMatch tcpFlagsMatch;
    /**
     * @brief Connection tracking match condition
     * @since 26.1.0
     */
    OH_TrafficFilter_ConntrackMatch conntrackMatch;
} OH_TrafficFilter_FilterRule;

/**
 * @brief Packet controller
 * @since 26.1.0
 */
typedef struct OH_TrafficFilter_PacketController OH_TrafficFilter_PacketController;

#ifdef __cplusplus
}
#endif

#endif /* NET_TRAFFICFILTER_TYPE_H */
/** @} */