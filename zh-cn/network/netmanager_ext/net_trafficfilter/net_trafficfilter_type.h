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
 * @brief 声明网络流量过滤与重定向功能所需的通用类型和错误码。
 *
 * @since 26.0.0
 */
 
/**
 * @file net_trafficfilter_type.h
 * @brief 声明网络流量过滤与重定向功能所需的通用类型和错误码。该头文件定义了流量过滤与重定向功能中使用的IP地址、端口、接口等匹配条件结构体，报文过滤规则、重定向规则等配置结构体，以及操作返回的错误码。
 * <br>适用于调用{@link OH_TrafficFilter_CreateRedirector}等接口时构造参数和解析返回值。
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
 * @brief IP地址字节数组最大长度（兼容IPv4和IPv6）。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_IP_ADDRLEN       16
 
/**
 * @brief 多IP匹配支持的最大IP数量。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_MAX_MULTI_IP_COUNT  16
 
/**
 * @brief 多端口匹配支持的最大端口数量。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_MAX_MULTI_PORT_COUNT 64
 
/**
 * @brief NFQueue报文拷贝模式：仅拷贝元数据。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_NFQUEUE_COPY_META   0
 
/**
 * @brief NFQueue报文拷贝模式：拷贝整个报文。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_NFQUEUE_COPY_PACKET 0xFFFF
 
/**
 * @brief 默认NFQueue报文拷贝长度（字节）。设置为0xFFFF表示拷贝整个报文，较小的值（如128）仅拷贝报文头。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_DEFAULT_COPY_LEN    0xFFFF
 
/**
 * @brief 默认NFQueue最大队列长度（报文数量）。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_DEFAULT_QUEUE_MAXLEN  1024
 
/**
 * @brief NFQueue队列标志：FAIL-OPEN模式。当用户态进程崩溃时，内核自动放行报文以避免网络中断。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_NFQUEUE_FLAG_FAIL_OPEN  0x1
 
/**
 * @brief 最小优先级值。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_MIN_PRIORITY        1
 
/**
 * @brief 最大优先级值。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_MAX_PRIORITY        10000
 
/**
 * @brief 最小Group ID值。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_MIN_GROUP_ID        1
 
/**
 * @brief 最大Group ID值。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_MAX_GROUP_ID        65535
 
/**
 * @brief 网络接口名称最大长度。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_IFNAMSIZ            32
 
/**
 * @brief 协议类型常量：任意协议。
 *
 * @since 26.0.0
 */
#define OH_TRAFFICFILTER_PROTO_ANY           0
#define OH_TRAFFICFILTER_PROTO_TCP           6
#define OH_TRAFFICFILTER_PROTO_UDP           17
#define OH_TRAFFICFILTER_PROTO_ICMP          1
#define OH_TRAFFICFILTER_PROTO_ICMPV6        58
 
/**
 * @brief 流量过滤与重定向错误码。
 *
 * @since 26.0.0
 */
typedef enum OH_TrafficFilter_ErrCode {
    /**
     * @brief 操作成功。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_OK = 0,
 
    /**
     * @brief 错误码基值。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_E_BASE = 29410000,
 
    /**
     * @brief 缺少权限。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED = 201,
 
    /**
     * @brief 参数错误（无效的优先级、IP地址、端口或Group ID）。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_ERROR_INVALID_PARAM = (OH_TRAFFICFILTER_E_BASE + 101),
 
    /**
     * @brief 资源未找到（规则、目标、进程或Group ID未找到）。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_ERROR_NOT_FOUND = (OH_TRAFFICFILTER_E_BASE + 102),
 
    /**
     * @brief 规则数量过多。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_ERROR_TOO_MANY_RULES = (OH_TRAFFICFILTER_E_BASE + 103),
 
    /**
     * @brief Group ID已被占用。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_ERROR_GROUP_ID_IN_USE = (OH_TRAFFICFILTER_E_BASE + 104),
 
    /**
     * @brief NFQueue错误（初始化失败或无可用队列）。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_ERROR_NFQUEUE_ERROR = (OH_TRAFFICFILTER_E_BASE + 105),
} OH_TrafficFilter_ErrCode;
 
/**
 * @brief IP匹配类型。
 *
 * @since 26.0.0
 */
typedef enum OH_TrafficFilter_IPMatchType {
    /**
     * @brief 任意IP。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_MATCH_ANY = 0,
    /**
     * @brief 单个IP。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_MATCH_SINGLE,
    /**
     * @brief CIDR格式（如192.168.1.0/24，表示匹配该子网内的所有IP）。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_MATCH_CIDR,
    /**
     * @brief IP范围。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_MATCH_RANGE,
    /**
     * @brief 多个IP。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_MATCH_MULTI
} OH_TrafficFilter_IPMatchType;
 
/**
 * @brief IP地址族。
 *
 * @since 26.0.0
 */
typedef enum OH_TrafficFilter_IPFamily {
    /**
     * @brief 未指定的IP地址族。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_FAMILY_UNSPEC = 0,
    /**
     * @brief IPv4地址族。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_FAMILY_V4 = 1,
    /**
     * @brief IPv6地址族。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_IP_FAMILY_V6 = 2
} OH_TrafficFilter_IPFamily;
 
/**
 * @brief 端口匹配类型。
 *
 * @since 26.0.0
 */
typedef enum OH_TrafficFilter_PortMatchType {
    /**
     * @brief 任意端口。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_PORT_MATCH_ANY = 0,
    /**
     * @brief 单个端口。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_PORT_MATCH_SINGLE,
    /**
     * @brief 端口范围。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_PORT_MATCH_RANGE,
    /**
     * @brief 多个端口。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_PORT_MATCH_MULTI
} OH_TrafficFilter_PortMatchType;
 
/**
 * @brief 钩子点类型，指定规则在网络协议栈中生效的位置。报文经过内核网络协议栈时会在不同阶段触发钩子点，规则在对应钩子点处对报文进行拦截。例如INPUT链处理进入本机的报文，OUTPUT链处理本机发出的报文。
 *
 * @since 26.0.0
 */
typedef enum OH_TrafficFilter_HookPoint {
    /**
     * @brief INPUT链，处理进入本机的报文。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_HOOK_INPUT = 0,
    /**
     * @brief OUTPUT链，处理本机发出的报文。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_HOOK_OUTPUT,
    /**
     * @brief FORWARD链，处理本机转发的报文。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_HOOK_FORWARD,
    /**
     * @brief PREROUTING链，处理刚到达网卡、尚未路由的报文。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_HOOK_PREROUTING,
    /**
     * @brief POSTROUTING链，处理即将从网卡发出的报文。
     *
     * @since 26.0.0
     */
    OH_TRAFFICFILTER_HOOK_POSTROUTING
} OH_TrafficFilter_HookPoint;
 
/**
 * @brief 二进制形式的IP地址，支持IPv4和IPv6。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPAddress {
    /**
     * @brief 地址族。若未显式设置，默认使用IPv4。
     * @since 26.0.0
     */
    OH_TrafficFilter_IPFamily family;
    /**
     * @brief IP地址字节。
     *
     * 字节必须以网络字节序存储。
     * 对于IPv4，{@link addr}[0]到{@link addr}[3]存储IPv4地址，
     * {@link addr}[4]到{@link addr}[15]必须设置为0。
     * 对于IPv6，{@link addr}[0]到{@link addr}[15]存储IPv6地址。
     *
     * 如果字节与{@link family}要求的地址布局不匹配，
     * 使用该结构体的接口将返回{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}。
     *
     * @since 26.0.0
     */
    uint8_t addr[OH_TRAFFICFILTER_IP_ADDRLEN];
} OH_TrafficFilter_IPAddress;
 
/**
 * @brief CIDR（Classless Inter-Domain Routing，无类别域间路由）匹配的IP匹配值。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPCidr {
    /**
     * @brief CIDR块的基IP地址。
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress base;
    /**
     * @brief CIDR前缀长度。
     * @since 26.0.0
     */
    uint8_t prefixLen;
} OH_TrafficFilter_IPCidr;
 
/**
 * @brief 范围匹配的IP匹配值。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPRange {
    /**
     * @brief 范围的起始IP地址。
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress start;
    /**
     * @brief 范围的结束IP地址。
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress end;
} OH_TrafficFilter_IPRange;
 
/**
 * @brief 多IP匹配的IP匹配值。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPMulti {
    /**
     * @brief 数组中的IP地址数量。
     * @since 26.0.0
     */
    uint32_t ipCount;
    /**
     * @brief IP地址数组
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress ips[OH_TRAFFICFILTER_MAX_MULTI_IP_COUNT];
} OH_TrafficFilter_IPMulti;
 
/**
 * @brief IP匹配条件。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_IPMatch {
    /**
     * @brief 匹配类型。
     * @since 26.0.0
     */
    OH_TrafficFilter_IPMatchType type;
    /**
     * @brief 是否反转匹配结果。
     * @since 26.0.0
     */
    bool invert;
    /**
     * @brief 匹配规则
     * @since 26.0.0
     */
    union {
        /**
         * @brief 单个IP地址，当type为OH_TRAFFICFILTER_IP_MATCH_SINGLE时使用
         * @since 26.0.0
         */
        OH_TrafficFilter_IPAddress single;
        /**
         * @brief CIDR匹配值，当type为OH_TRAFFICFILTER_IP_MATCH_CIDR时使用
         * @since 26.0.0
         */
        OH_TrafficFilter_IPCidr cidr;
        /**
         * @brief IP范围匹配值，当type为OH_TRAFFICFILTER_IP_MATCH_RANGE时使用
         * @since 26.0.0
         */
        OH_TrafficFilter_IPRange range;
        /**
         * @brief 多IP匹配值，当type为OH_TRAFFICFILTER_IP_MATCH_MULTI时使用
         * @since 26.0.0
         */
        OH_TrafficFilter_IPMulti multi;
    } value;
} OH_TrafficFilter_IPMatch;
 
/**
 * @brief 接口匹配条件。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_InterfaceMatch {
    /**
     * @brief 是否启用接口匹配。
     * @since 26.0.0
     */
    bool enabled;
    /**
     * @brief 是否反转匹配结果。
     * @since 26.0.0
     */
    bool invert;
    /**
     * @brief 是否按前缀匹配接口名称。
     * @since 26.0.0
     */
    bool isPrefix;
    /**
     * @brief 接口名称。
     *
     * 该字符串必须以UTF-8编码，且必须以NUL结尾。
     * 该缓冲区的容量为{@link OH_TRAFFICFILTER_IFNAMSIZ}字节，
     * 包含结尾的NUL字符。因此，接口名称的最大长度为
     * {@link OH_TRAFFICFILTER_IFNAMSIZ} - 1字节，
     * 不包含结尾的NUL字符。
     *
     * 如果{@link enabled}为true，该字符串不能为空。
     * 如果该字符串在{@link OH_TRAFFICFILTER_IFNAMSIZ}
     * 字节内没有以NUL结尾，或者其长度超过{@link OH_TRAFFICFILTER_IFNAMSIZ} - 1字节，
     * 使用该结构体的接口将返回{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}。
     *
     * 如果{@link enabled}为false，该字段将被忽略。建议在禁用接口匹配时
     * 将该缓冲区全部置零。
     *
     * @since 26.0.0
     */
    char ifName[OH_TRAFFICFILTER_IFNAMSIZ];
} OH_TrafficFilter_InterfaceMatch;
 
/**
 * @brief 范围匹配的端口匹配值。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_PortRange {
    /**
     * @brief 范围的起始端口。
     * @since 26.0.0
     */
    uint16_t startPort;
    /**
     * @brief 范围的结束端口。
     * @since 26.0.0
     */
    uint16_t endPort;
} OH_TrafficFilter_PortRange;
 
/**
 * @brief 多端口匹配的端口匹配值。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_PortMulti {
    /**
     * @brief 数组中的端口数量。
     * @since 26.0.0
     */
    uint32_t portCount;
    /**
     * @brief 端口数组
     * @since 26.0.0
     */
    uint16_t ports[OH_TRAFFICFILTER_MAX_MULTI_PORT_COUNT];
} OH_TrafficFilter_PortMulti;
 
/**
 * @brief 端口匹配条件。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_PortMatch {
    /**
     * @brief 匹配类型。
     * @since 26.0.0
     */
    OH_TrafficFilter_PortMatchType type;
    /**
     * @brief 是否反转匹配结果。
     * @since 26.0.0
     */
    bool invert;
    /**
     * @brief 匹配规则
     * @since 26.0.0
     */
    union {
        /**
         * @brief 单个端口，当type为OH_TRAFFICFILTER_PORT_MATCH_SINGLE时使用
         * @since 26.0.0
         */
        uint16_t single;
        /**
         * @brief 端口范围匹配值，当type为OH_TRAFFICFILTER_PORT_MATCH_RANGE时使用
         * @since 26.0.0
         */
        OH_TrafficFilter_PortRange range;
        /**
         * @brief 多端口匹配值，当type为OH_TRAFFICFILTER_PORT_MATCH_MULTI时使用
         * @since 26.0.0
         */
        OH_TrafficFilter_PortMulti multi;
    } value;
} OH_TrafficFilter_PortMatch;
 
/**
 * @brief 连接信息结构体。描述一条网络连接的五元组信息（源IP、目的IP、源端口、目的端口、协议类型），用于查询发起该连接的进程信息。<br>初始化规则：调用
 * {@link OH_TrafficFilter_QueryProcess}之前，调用者必须将该结构体清零（例如使用memset），然后将{@link size}设置为调用者分配的结构体实际大小，通常为sizeof(
 * OH_TrafficFilter_ConnectionInfo)。<br>二进制兼容规则（ABI，即应用程序二进制接口，保证新旧版本编译的代码能互相识别结构体布局）：系统通过{@link size}来确定哪些字段可以被安全读取。
 * 如果{@link size}小于当前接口所需的最小大小，接口将返回{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}。如果{@link size}大于系统已知的大小，多余的字段将被忽略。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_ConnectionInfo {
    /**
     * @brief 调用者分配的结构体实际大小。
     * @since 26.0.0
     */
    uint32_t size;
    /**
     * @brief 源IP地址，支持IPv4和IPv6。
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress srcIp;
    /**
     * @brief 源端口。0表示任意源端口。
     * @since 26.0.0
     */
    uint16_t srcPort;
    /**
     * @brief 目的IP地址，支持IPv4和IPv6。
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress dstIp;
    /**
     * @brief 目的端口。0表示任意目的端口。
     * @since 26.0.0
     */
    uint16_t dstPort;
    /**
     * @brief 协议类型。支持的取值：OH_TRAFFICFILTER_PROTO_TCP (6)、OH_TRAFFICFILTER_PROTO_UDP (17)。
     * @since 26.0.0
     */
    uint8_t protocol;
} OH_TrafficFilter_ConnectionInfo;
 
/**
 * @brief 进程信息结构体。存储{@link OH_TrafficFilter_QueryProcess}返回的进程信息。<br>初始化规则：调用{@link OH_TrafficFilter_QueryProcess}之前，
 * 调用者必须将该结构体清零（例如使用memset），然后将{@link size}设置为调用者分配的结构体实际大小，通常为sizeof(OH_TrafficFilter_ProcessInfo)。<br>二进制兼容规则（ABI，
 * 即应用程序二进制接口，保证新旧版本编译的代码能互相识别结构体布局）：系统通过{@link size}来确定哪些输出字段可以被安全写入。只有被{@link size}完全覆盖的字段才会被系统写入。如果{@link size}小于读取
 * {@link size}字段本身所需的最小大小，接口将返回{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}。如果{@link size}大于系统已知的大小，多余的字段将被忽略。<br>
 * 输出有效性规则：当{@link OH_TrafficFilter_QueryProcess}返回{@link OH_TRAFFICFILTER_OK}时，被{@link size}覆盖的字段包含有效的输出值。当接口返回错误时，
 * 调用者不应依赖{@link size}以外的输出字段的值。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_ProcessInfo {
    /**
     * @brief 调用者分配的结构体实际大小。
     * @since 26.0.0
     */
    uint32_t size;
    /**
     * @brief 进程ID。
     * @since 26.0.0
     */
    uint32_t pid;
    /**
     * @brief 用户ID。
     * @since 26.0.0
     */
    uint32_t uid;
} OH_TrafficFilter_ProcessInfo;
 
/**
 * @brief 流量重定向器。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_Redirector OH_TrafficFilter_Redirector;
 
/**
 * @brief 流量重定向规则。定义TCP流量重定向规则，将匹配的流量重定向到指定的代理服务器。<br>初始化规则：调用{@link OH_TrafficFilter_AddRedirectRule}之前，调用者必须将该结构体清零（
 * 例如使用memset），然后将{@link size}设置为调用者分配的结构体实际大小，通常为sizeof(OH_TrafficFilter_RedirectRule)。<br>二进制兼容规则（ABI，即应用程序二进制接口，
 * 保证新旧版本编译的代码能互相识别结构体布局）：系统通过{@link size}来确定哪些字段可以被安全读取。如果{@link size}小于当前接口所需的最小大小，接口将返回
 * {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}。如果{@link size}大于系统已知的大小，多余的字段将被忽略。<br>失败规则：如果
 * {@link OH_TrafficFilter_AddRedirectRule}返回错误，不保证规则已被添加或生效。调用者应在假设规则生效之前检查返回值。
 *
 * @since 26.0.0
 */
typedef struct OH_TrafficFilter_RedirectRule {
    /**
     * @brief 调用者分配的结构体实际大小。
     * @since 26.0.0
     */
    uint32_t size;
    /**
     * @brief 优先级（数值越小优先级越高，规则同报文过滤器）。
     * @since 26.0.0
     */
    uint32_t priority;
    /**
     * @brief 钩子点（仅支持PREROUTING和OUTPUT）。
     * @since 26.0.0
     */
    OH_TrafficFilter_HookPoint hookPoint;
    /**
     * @brief 协议（固定为TCP=6）。
     * @since 26.0.0
     */
    uint8_t protocol;
    /**
     * @brief 源IP匹配条件。
     * @since 26.0.0
     */
    OH_TrafficFilter_IPMatch srcIp;
    /**
     * @brief 源端口匹配条件。
     * @since 26.0.0
     */
    OH_TrafficFilter_PortMatch srcPort;
    /**
     * @brief 目的IP匹配条件。
     * @since 26.0.0
     */
    OH_TrafficFilter_IPMatch dstIp;
    /**
     * @brief 目的端口匹配条件。
     * @since 26.0.0
     */
    OH_TrafficFilter_PortMatch dstPort;
    /**
     * @brief 入接口匹配条件。
     * @since 26.0.0
     */
    OH_TrafficFilter_InterfaceMatch inInterface;
    /**
     * @brief 出接口匹配条件。
     * @since 26.0.0
     */
    OH_TrafficFilter_InterfaceMatch outInterface;
    /**
     * @brief 应用UID范围起始值（UINT32_MAX表示任意）。
     * @since 26.0.0
     */
    uint32_t uidStart;
    /**
     * @brief 应用UID范围结束值（UINT32_MAX表示任意）。
     * @since 26.0.0
     */
    uint32_t uidEnd;
    /**
     * @brief 代理服务器IP地址（支持IPv4和IPv6）。
     * @since 26.0.0
     */
    OH_TrafficFilter_IPAddress proxyIp;
    /**
     * @brief 代理服务器端口。
     * @since 26.0.0
     */
    uint16_t proxyPort;
} OH_TrafficFilter_RedirectRule;
 
#ifdef __cplusplus
}
#endif
 
#endif /* NET_TRAFFICFILTER_TYPE_H */
/** @} */