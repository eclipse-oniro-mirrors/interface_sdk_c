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
 * file defines the matching condition structs for IP address, port, MAC address, interface, TCP flags, and connection
 * tracking used in traffic filtering and redirection, the configuration structs for packet filtering rules,
 * redirection rules, and NFQueue configuration, as well as the packet descriptor, packet processing decision, packet
 * copy mode, and error codes returned by operations.
 * <br>Applicable to constructing parameters and parsing return values when calling APIs such as
 * {@link OH_TrafficFilter_CreateRedirector} or {@link OH_TrafficFilter_CreatePacketController}.
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
 * @brief Maximum length of a MAC address string (in the XX:XX:XX:XX:XX:XX format).
 * @since 26.0.1
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
     * @brief Permission denied.
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
 * @brief Defines an IP address in binary form, supporting both IPv4 and IPv6.
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPAddress {
    /**
     * @brief Address family. If **OH_TRAFFICFILTER_IP_FAMILY_UNSPEC** is specified, IPv4 is used by default.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPFamily family;
    /**
     * @brief IP address bytes. The bytes must be stored in network byte order.
     * For IPv4, {@link addr}[0] to {@link addr}[3] store the IPv4 address, and {@link addr}[4] to {@link addr}[15] must
     * be set to **0**. For IPv6, {@link addr}[0] to {@link addr}[15] store the IPv6 address.
     * If the bytes do not match the address layout required by {@link family}, the interface that uses this struct
     * returns {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}.
     *
     * @since 26.0.0
     */
    uint8_t addr[OH_TRAFFICFILTER_IP_ADDRLEN];
} OH_TrafficFilter_IPAddress;

/**
 * @brief Defines the IP match value for Classless Inter-Domain Routing (CIDR) matching.
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPCidr {
    /**
     * @brief Base IP address of the CIDR block.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress base;
    /**
     * @brief CIDR prefix length, which indicates the number of leading 1 bits in the network mask (for example, **24**
     * indicates the subnet mask 255.255.255.0).
     * @since 26.0.0
     */
    uint8_t prefixLen;
} OH_TrafficFilter_IPCidr;

/**
 * @brief Defines the IP match value for range matching.
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPRange {
    /**
     * @brief Start IP address of the range.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress start;
    /**
     * @brief End IP address of the range.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress end;
} OH_TrafficFilter_IPRange;

/**
 * @brief Defines the IP match value for multi-IP matching.
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPMulti {
    /**
     * @brief Number of IP addresses in the array.
     * @since 26.0.0
     */
    uint32_t ipCount;
    /**
     * @brief Array of IP addresses.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress ips[OH_TRAFFICFILTER_MAX_MULTI_IP_COUNT];
} OH_TrafficFilter_IPMulti;

/**
 * @brief Defines the IP match condition.
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPMatch {
    /**
     * @brief Match type.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPMatchType type;
    /**
     * @brief Whether to invert the match result.
     * @since 26.0.0
     */
    bool invert;
    /**
     * @brief Match rule. ({@link OH_TrafficFilter_IPAddress} single, {@link OH_TrafficFilter_IPCidr} cidr,
     * {@link OH_TrafficFilter_IPRange} range, {@link OH_TrafficFilter_IPMulti} multi).
     *
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
 * @brief Defines the interface match condition.
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_InterfaceMatch {
    /**
     * @brief Whether to enable interface match.
     * The value **true** means to enable interface match,and **false** means not to enable interface match.
     *
     * @since 26.0.0
     */
    bool enabled;
    /**
     * @brief Whether to invert the match result.
     * The value **true** means to invert the match result, and **false** means not to invert the match result.
     * @since 26.0.0
     */
    bool invert;
    /**
     * @brief Whether to match the interface name by prefix.
     * The value **true** means to match by prefix, and **false** means not to match by prefix.
     *
     * @since 26.0.0
     */
    bool isPrefix;
    /**
     * @brief Interface name. The string must be UTF-8 encoded and NULL-terminated.
     * The buffer capacity is {@link OH_TRAFFICFILTER_IFNAMSIZ} bytes, including the terminating NULL character.
     * Therefore, the maximum length of the interface name is {@link OH_TRAFFICFILTER_IFNAMSIZ} - 1 bytes,
     * excluding the terminating NULL character. If {@link enabled} is **true**, the string cannot be empty.
     * If the string is not NULL-terminated within {@link OH_TRAFFICFILTER_IFNAMSIZ} bytes, or its length exceeds
     * {@link OH_TRAFFICFILTER_IFNAMSIZ} - 1 bytes, the API that uses this struct returns
     * {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}. If {@link enabled} is **false**, this field is ignored.
     * It is recommended to set the entire buffer to zero when interface match is disabled.
     *
     * @since 26.0.0
     */
    char ifName[OH_TRAFFICFILTER_IFNAMSIZ];
} OH_TrafficFilter_InterfaceMatch;

/**
 * @brief Defines the port matching value for range matching.
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_PortRange {
    /**
     * @brief Start port of the range.
     * @since 26.0.0
     */
    uint16_t startPort;
    /**
     * @brief End port of the range.
     * @since 26.0.0
     */
    uint16_t endPort;
} OH_TrafficFilter_PortRange;

/**
 * @brief Defines the port matching value for multi-port matching.
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_PortMulti {
    /**
     * @brief Number of ports in the array.
     * @since 26.0.0
     */
    uint32_t portCount;
    /**
     * @brief Port array.
     * @since 26.0.0
     */
    uint16_t ports[OH_TRAFFICFILTER_MAX_MULTI_PORT_COUNT];
} OH_TrafficFilter_PortMulti;

/**
 * @brief Defines the port match condition.
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_PortMatch {
    /**
     * @brief Match type.
     * @since 26.0.0
     */
    OH_TrafficFilter_PortMatchType type;
    /**
     * @brief Whether to invert the match result.
     * The value true means to invert the match result, and false means the opposite.
     *
     * @since 26.0.0
     */
    bool invert;
    /**
     * @brief Match rule.
     * (uint16_t single, {@link OH_TrafficFilter_PortRange} range, {@link OH_TrafficFilter_PortMulti} multi)
     *
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
 * @brief Defines the connection information struct.
 * It describes the five-tuple information of a network connection (source IP, destination IP, source port,
 * destination port, and protocol type), which is used to query the process that initiates the connection.
 * Initialization rule: Before calling {@link OH_TrafficFilter_QueryProcess}, the caller must clear this struct
 * to zero (for example, using **memset**), and then set {@link size} to the actual size of the struct allocated
 * by the caller, which is usually **sizeof(OH_TrafficFilter_ConnectionInfo)**.
 * Binary compatibility rule (ABI, that is, Application Binary Interface, which ensures that code compiled by old
 * and new versions can recognize each other's struct layout): The system determines which fields can be safely
 * read based on {@link size}. If {@link size} is smaller than the minimum size required by the current interface,
 * the interface returns {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}. If {@link size} is larger than the size known
 * to the system, the extra fields are ignored.
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_ConnectionInfo {
    /**
     * @brief Actual size of the struct allocated by the caller.
     * @since 26.0.0
     */
    uint32_t size;
    /**
     * @brief Source IP address, which supports IPv4 and IPv6.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress srcIp;
    /**
     * @brief Source port. 0 indicates any source port.
     * @since 26.0.0
     */
    uint16_t srcPort;
    /**
     * @brief Destination IP address, which supports IPv4 and IPv6.
     * It must be in the same address family as the source IP address.
     *
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress dstIp;
    /**
     * @brief Destination port. **0** indicates any destination port.
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
 * @brief Defines the process information struct.
 * Stores the process information returned by {@link OH_TrafficFilter_QueryProcess}.
 * Initialization rule: Before calling {@link OH_TrafficFilter_QueryProcess}, the caller must clear this struct to
 * zero (for example, using memset), and then set {@link size} to the actual size of the struct allocated by the caller,
 * which is usually **sizeof(OH_TrafficFilter_ProcessInfo)**.
 * Binary compatibility rule (ABI, that is, Application Binary Interface, which ensures that code compiled by old and
 * new versions can recognize each other's struct layout): The system uses {@link size} to determine which output fields
 * can be safely written. Only fields fully covered by {@link size} are written by the system.
 * If {@link size} is smaller than the minimum size required to read the {@link size} field itself,
 * the API returns {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}. If {@link size} is larger than the size known to
 * the system, the extra fields are ignored. Output validity rule: When {@link OH_TrafficFilter_QueryProcess}
 * returns {@link OH_TRAFFICFILTER_OK}, the fields covered by {@link size} contain valid output values.
 * When the API returns an error, the caller must not rely on the values of output fields other than {@link size}.
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_ProcessInfo {
    /**
     * @brief Actual size of the struct allocated by the caller.
     * @since 26.0.0
     */
    uint32_t size;
    /**
     * @brief Process ID.
     * @since 26.0.0
     */
    uint32_t pid;
    /**
     * @brief App UID.
     * @since 26.0.0
     */
    uint32_t uid;
} OH_TrafficFilter_ProcessInfo;

/**
 * @brief Defines a traffic redirector.
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_Redirector OH_TrafficFilter_Redirector;

/**
 * @brief Defines the traffic redirection rule. Defines a TCP traffic redirection rule to redirect matching traffic to
 * a specified proxy server. Initialization rule: Before calling {@link OH_TrafficFilter_AddRedirectRule},
 * the caller must clear this struct to zero (for example, using **memset**), and then set {@link size} to the actual
 * size of the struct allocated by the caller, usually **sizeof(OH_TrafficFilter_RedirectRule)**. Binary compatibility
 * rule (ABI, that is, application binary interface, which ensures that code compiled by old and new versions can
 * recognize each other's struct layout): The system determines which fields can be safely read based on {@link size}.
 * If {@link size} is smaller than the minimum size required by the current API, the API returns
 * {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}. If {@link size} is larger than the size known to the system,
 * the extra fields are ignored. Failure rule: If {@link OH_TrafficFilter_AddRedirectRule} returns an error, it is not
 * guaranteed that the rule has been added or taken effect. The caller should check the return value before assuming
 * that the rule has taken effect.
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_RedirectRule {
    /**
     * @brief Actual size of the struct allocated by the caller.
     * @since 26.0.0
     */
    uint32_t size;
    /**
     * @brief Priority. A smaller value indicates a higher priority. The rule is the same as that of the packet filter.
     * @since 26.0.0
     */
    uint32_t priority;
    /**
     * @brief Hook point, which specifies where the rule takes effect in the network protocol stack.
     * Only **PREROUTING** and **OUTPUT** are supported. For details, see {@link OH_TrafficFilter_HookPoint}.
     * @since 26.0.0
     */
    OH_TrafficFilter_HookPoint hookPoint;
    /**
     * @brief Protocol, fixed to TCP=6.
     * @since 26.0.0
     */
    uint8_t protocol;
    /**
     * @brief Source IP matching condition.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPMatch srcIp;
    /**
     * @brief Source port matching condition.
     * @since 26.0.0
     */
    OH_TrafficFilter_PortMatch srcPort;
    /**
     * @brief Destination IP matching condition.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPMatch dstIp;
    /**
     * @brief Destination port matching condition.
     * @since 26.0.0
     */
    OH_TrafficFilter_PortMatch dstPort;
    /**
     * @brief Inbound interface matching condition.
     * @since 26.0.0
     */
    OH_TrafficFilter_InterfaceMatch inInterface;
    /**
     * @brief Outbound interface matching condition.
     * @since 26.0.0
     */
    OH_TrafficFilter_InterfaceMatch outInterface;
    /**
     * @brief Start value of the app UID range. The value range is [0, UINT32_MAX], where **UINT32_MAX** indicates any
     * UID.
     * @since 26.0.0
     */
    uint32_t uidStart;
    /**
     * @brief End value of the app UID range. The value range is [0, UINT32_MAX], where **UINT32_MAX** indicates any
     * UID. Generally, this value must be greater than or equal to **uidStart** (the start value of the app UID range).
     * @since 26.0.0
     */
    uint32_t uidEnd;
    /**
     * @brief IP address of the proxy server. Both IPv4 and IPv6 are supported.
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress proxyIp;
    /**
     * @brief Port of the proxy server.
     * @since 26.0.0
     */
    uint16_t proxyPort;
} OH_TrafficFilter_RedirectRule;

/**
 * @brief Defines the packet descriptor.
 * @since 26.0.1
 */
typedef struct OH_TrafficFilter_PacketDesc {
    /**
     * @brief Packet ID (assigned by the kernel when the packet arrives at netfilter (Network Filter)).
     * @since 26.0.1
     */
    uint32_t packetId;
    /**
     * @brief Protocol type.
     * @since 26.0.1
     */
    uint8_t protocol;
    /**
     * @brief Source IP address (supports IPv4 and IPv6).
     * @since 26.0.1
     */
    OH_TrafficFilter_IPAddress srcIp;
    /**
     * @brief Source port.
     * @since 26.0.1
     */
    uint16_t srcPort;
    /**
     * @brief Destination IP address (supports IPv4 and IPv6).
     * @since 26.0.1
     */
    OH_TrafficFilter_IPAddress dstIp;
    /**
     * @brief Destination port.
     * @since 26.0.1
     */
    uint16_t dstPort;
    /**
     * @brief Packet length.
     * @since 26.0.1
     */
    uint32_t packetLen;
    /**
     * @brief Pointer to the packet data (modifiable by the user; the memory is managed by the system, and **it is
     * valid only during the callback. Do not access this pointer after the callback returns**).
     * @since 26.0.1
     */
    uint8_t* data;
    /**
     * @brief Pointer to the user data (used in the callback).
     * @since 26.0.1
     */
    void* userData;
} OH_TrafficFilter_PacketDesc;

/**
 * @brief Defines the configuration struct of an NFQueue (a packet queuing channel in the Netfilter framework).
 * Initialization rule: Before calling {@link OH_TrafficFilter_CreatePacketController}, the caller must clear this
 * struct to zero (for example, using **memset**), and then set {@link size} to the actual size of the struct allocated
 * by the caller, which is usually **sizeof(OH_TrafficFilter_Config)**.
 * Binary compatibility rule (ABI, that is, application binary interface, which ensures that code compiled by old
 * and new versions can recognize each other's struct layout): The system determines which fields can be safely read
 * based on {@link size}. If {@link size} is smaller than the minimum size required by the current API,
 * the API returns {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}. If {@link size} is larger than the size known to the
 * system, the extra fields are ignored.
 * @note Failure to follow this initialization contract may lead to undefined behavior or binary incompatibility
 *     across versions.
 * @since 26.0.1
 */
typedef struct OH_TrafficFilter_Config {
     /**
      * @brief Actual size of the struct allocated by the caller.
      * @since 26.0.1
      */
     uint32_t size;
     /**
      * @brief Packet copy mode. For details, see {@link OH_TrafficFilter_PacketCopyMode}. The default value is **2**.
      * @since 26.0.1
      */
     uint32_t packetCopyMode;
     /**
      * @brief Length (in bytes) of the packet copied by the NFQueue.
      * The value ranges from 0 to 0xFFFF. 0xFFFF means copying the entire packet,
      * and other values mean copying the packet header of the specified length. The default value is 0xFFFF.
      * @since 26.0.1
      */
     uint32_t packetCopyLen;
     /**
      * @brief Maximum queue length (number of packets) of the NFQueue.
      * **0** means using the system default value (1024).
      * @since 26.0.1
      */
     uint32_t nfqueueMaxlen;
     /**
      * @brief NFQueue queue flag.
      * For details, see {@link OH_TRAFFICFILTER_NFQUEUE_FLAG_FAIL_OPEN}. The default value is **0x1**.
      * @since 26.0.1
      */
     uint32_t nfqueueFlags;
} OH_TrafficFilter_Config;

/**
 * @brief Enumerates the packet processing decision types.
 * @since 26.0.1
 */
typedef enum OH_TrafficFilter_PacketDecision {
    /**
     * @brief Accepts the packet.
     * @since 26.0.1
     */
    OH_TRAFFICFILTER_DECISION_ACCEPT = 0,
    /**
     * @brief Drops the packet.
     * @since 26.0.1
     */
    OH_TRAFFICFILTER_DECISION_DROP
} OH_TrafficFilter_PacketDecision;

/**
 * @brief Packet callback function type
 *
 * @param packet Packet descriptor
 * @param userData User data
 * @return Packet decision (ACCEPT or DROP)
 * @since 26.0.1
 */
typedef OH_TrafficFilter_PacketDecision (*OH_TrafficFilter_PacketCallback)(
    const OH_TrafficFilter_PacketDesc* packet,
    void* userData
);

/**
 * @brief Enumerates the packet copy modes.
 * @since 26.0.1
 */
typedef enum OH_TrafficFilter_PacketCopyMode {
     /**
      * @brief Copies only the metadata (without copying the packet data).
      * @since 26.0.1
      */
     OH_TRAFFICFILTER_COPY_MODE_META = 0,
     /**
      * @brief Copies only the packet header (specified by **packetCopyLen**).
      * @since 26.0.1
      */
     OH_TRAFFICFILTER_COPY_MODE_HEADER = 1,
     /**
      * @brief Copies the entire packet.
      * @since 26.0.1
      */
     OH_TRAFFICFILTER_COPY_MODE_FULL = 2,
     /**
      * @brief Copies the packet of the specified maximum length.
      * @since 26.0.1
      */
     OH_TRAFFICFILTER_COPY_MODE_MAXLEN = 3
} OH_TrafficFilter_PacketCopyMode;

/**
 * @brief Defines the MAC address matching condition.
 * @since 26.0.1
 */
typedef struct OH_TrafficFilter_MACMatch {
    /**
     * @brief Whether to enable MAC address matching.
     * The value **true** means to enable MAC address matching, and **false** means the opposite.
     * @since 26.0.1
     */
    bool enable;
    /**
     * @brief Whether to invert the matching result.
     * The value **true** means to invert the matching result, and **false** means the opposite.
     * @since 26.0.1
     */
    bool invert;
    /**
     * @brief Source MAC address (in the XX:XX:XX:XX:XX:XX format).
     * @since 26.0.1
     */
    char srcMac[OH_TRAFFICFILTER_MAC_ADDRSTRLEN];
} OH_TrafficFilter_MACMatch;

/**
 * @brief Defines the TCP flag matching condition. It is valid only for the TCP protocol.
 * @since 26.0.1
 */
typedef struct OH_TrafficFilter_TCPFlagsMatch {
    /**
     * @brief Whether to enable TCP flag matching.
     * The value **true** means to enable TCP flag matching, and **false** means not to enable TCP flag matching.
     * @since 26.0.1
     */
    bool enable;
    /**
     * @brief Flag mask (specifies the flags to check).
     * @since 26.0.1
     */
    uint8_t flagMask;
    /**
     * @brief Flag comparison value (value to compare against the flags).
     * @since 26.0.1
     */
    uint8_t flagComp;
} OH_TrafficFilter_TCPFlagsMatch;

/**
 * @brief Defines the connection tracking match condition.
 * @since 26.0.1
 */
typedef struct OH_TrafficFilter_ConntrackMatch {
    /**
     * @brief Whether to enable connection tracking match. The value **true** means to enable connection tracking
     * match, and **false** means not to enable it.
     * @since 26.0.1
     */
    bool enable;
    /**
     * @brief Connection state.
     * @since 26.0.1
     */
    uint8_t stateMask;
} OH_TrafficFilter_ConntrackMatch;

/**
 * @brief Defines a packet filtering rule. The conditions within a single **OH_TrafficFilter_FilterRule** struct are
 * in a logical AND relationship, and multiple rules added to the same **OH_TrafficFilter_PacketController** are in a
 * logical OR relationship. Initialization rule: Before calling {@link OH_TrafficFilter_AddPacketRule}, the caller must
 * clear this struct to zero (for example, using **memset**), and then set {@link size} to the actual size of the struct
 * allocated by the caller, usually **sizeof(OH_TrafficFilter_FilterRule)**. Binary compatibility rule (ABI, that is,
 * application binary interface, which ensures that code compiled by old and new versions can recognize each
 * other's struct layout): The system determines which fields can be safely read based on {@link size}. If {@link size}
 * is smaller than the minimum size required by the current API, the API returns
 * {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}. If {@link size} is larger than the size known to the system,
 * the extra fields are ignored. Failure rule: If {@link OH_TrafficFilter_AddPacketRule} returns an error,
 * it is not guaranteed that the rule has been added or taken effect. The caller should check the return value
 * before assuming that the rule has taken effect.
 *
 * @note Failure to follow this initialization contract may lead to undefined behavior or binary incompatibility across
 *     versions.
 * @since 26.0.1
 */
typedef struct OH_TrafficFilter_FilterRule {
     /**
      * @brief Actual size of the struct allocated by the caller.
      * @since 26.0.1
      */
     uint32_t size;
     /**
      * @brief Priority. A smaller value indicates a higher priority.
      * @since 26.0.1
      */
     uint32_t priority;
     /**
      * @brief Hook point. Adds the rule to the chain of a different hook point.
      * @since 26.0.1
      */
     OH_TrafficFilter_HookPoint hookPoint;
     /**
      * @brief Protocol type. **0** indicates no restriction, **6** indicates TCP, and **17** indicates UDP.
      * @since 26.0.1
      */
     uint8_t protocol;
     /**
      * @brief Source IP matching condition.
      * @since 26.0.1
      */
     OH_TrafficFilter_IPMatch srcIp;
     /**
      * @brief Source port matching condition.
      * @since 26.0.1
      */
     OH_TrafficFilter_PortMatch srcPort;
     /**
      * @brief Destination IP matching condition.
      * @since 26.0.1
      */
     OH_TrafficFilter_IPMatch dstIp;
     /**
      * @brief Destination port matching condition.
      * @since 26.0.1
      */
     OH_TrafficFilter_PortMatch dstPort;
     /**
      * @brief Inbound interface matching condition.
      * @since 26.0.1
      */
     OH_TrafficFilter_InterfaceMatch inInterface;
     /**
      * @brief Outbound interface matching condition.
      * @since 26.0.1
      */
     OH_TrafficFilter_InterfaceMatch outInterface;
     /**
      * @brief Start value of the application UID range. **UINT32_MAX** indicates any value.
      * @since 26.0.1
      */
     uint32_t uidStart;
     /**
      * @brief End value of the application UID range. **UINT32_MAX** indicates any value.
      * @since 26.0.1
      */
     uint32_t uidEnd;
     /**
      * @brief MAC address matching condition. Applies to the source MAC address only.
      * @since 26.0.1
      */
     OH_TrafficFilter_MACMatch macMatch;
     /**
      * @brief TCP flag matching condition. Valid only for the TCP protocol.
      * @since 26.0.1
      */
     OH_TrafficFilter_TCPFlagsMatch tcpFlagsMatch;
     /**
      * @brief Connection tracking matching condition.
      * @since 26.0.1
      */
     OH_TrafficFilter_ConntrackMatch conntrackMatch;
} OH_TrafficFilter_FilterRule;

/**
 * @brief Defines the packet controller.
 * @since 26.0.1
 */
typedef struct OH_TrafficFilter_PacketController OH_TrafficFilter_PacketController;

#ifdef __cplusplus
}
#endif

#endif /* NET_TRAFFICFILTER_TYPE_H */
/** @} */