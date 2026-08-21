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
 * @brief 声明网络流量过滤与重定向功能的C接口。
 *
 * @since 26.0.0
 */
 
/**
 * @file net_trafficfilter.h
 * @brief 声明网络流量过滤与重定向功能的C接口。该头文件提供创建和销毁报文控制器、注册报文回调、添加和清除过滤规则，以及创建和销毁流量重定向器、添加和清除重定向规则的接口。
 * <br>适用于需要在系统层面对网络数据包进行拦截、过滤和重定向的应用场景。
 *
 * @library libnet_trafficfilter.so
 * @kit NetworkKit
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @syscap SystemCapability.Communication.NetManager.NetFirewall
 * @since 26.0.0
 */
 
#ifndef NET_TRAFFICFILTER_H
#define NET_TRAFFICFILTER_H
 
#include "net_trafficfilter_type.h"
 
#ifdef __cplusplus
extern "C" {
#endif
 
/**
 * @brief 创建流量重定向实例，用于将TCP流量重定向到代理服务器。资源管理：必须调用{@link OH_TrafficFilter_DestroyRedirector}释放资源。如果该函数失败，不会返回有效的重定向器。
 *
 * @param group_id 重定向链标识符。这是应用内的逻辑分组ID。同一应用内的多个重定向器可以使用不同的group_id。不同应用的相同group_id会自动隔离。有效范围为[
 *     {@link OH_TRAFFICFILTER_MIN_GROUP_ID}, {@link OH_TRAFFICFILTER_MAX_GROUP_ID}]，包含两个边界。如果group_id超出此范围，该函数返回
 *     {@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}。
 * @param priority 优先级。决定不同group_id链之间的执行顺序，数值越小越先执行。注意：重定向器优先级高于报文过滤器优先级。有效范围为[{@link OH_TRAFFICFILTER_MIN_PRIORITY},
 *     {@link OH_TRAFFICFILTER_MAX_PRIORITY}]，包含两个边界。如果priority超出此范围，该函数返回{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM}。
 * @param redirector 出参，成功时为重定向句柄。
 * @return {@link OH_TRAFFICFILTER_OK} - 成功。
 *     <br>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} - 缺少权限。
 *     <br>{@link OH_TRAFFICFILTER_ERROR_GROUP_ID_IN_USE} - group_id已存在。
 *     <br>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} - 参数错误。
 * @release TrafficFilter/OH_TrafficFilter_DestroyRedirector {redirector}
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_CreateRedirector(
    uint32_t group_id,
    uint32_t priority,
    OH_TrafficFilter_Redirector** redirector
);
 
/**
 * @brief 销毁重定向实例并释放相关资源（包括规则），调用后句柄将失效。
 *
 * @param redirector OH_TrafficFilter_Redirector句柄。
 * @return {@link OH_TRAFFICFILTER_OK} - 成功。
 *     <br>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} - 缺少权限。
 *     <br>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} - redirector为NULL。
 *     <br>{@link OH_TRAFFICFILTER_ERROR_NOT_FOUND} - 未找到指定的重定向器句柄。
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_DestroyRedirector(OH_TrafficFilter_Redirector* redirector);
 
/**
 * @brief 添加重定向规则
 * 添加TCP流量重定向规则，将匹配的流量重定向到指定的代理服务器
 * 要清除重定向规则，需要调用{@link OH_TrafficFilter_ClearRedirectRule}。
 *
 * @param redirector OH_TrafficFilter_Redirector句柄
 * @param rule 重定向规则。不能为NULL。
 * @return <ul><li>{@link OH_TRAFFICFILTER_OK} - 成功。</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} - 缺少权限。</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} - redirector或rule为NULL。</li>
 *     <li>{@link OH_TRAFFICFILTER_ERROR_TOO_MANY_RULES} - 规则数量过多。</li></ul>
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_AddRedirectRule(
    OH_TrafficFilter_Redirector* redirector,
    const OH_TrafficFilter_RedirectRule* rule
);
 
/**
 * @brief 清除所有重定向规则。
 *
 * @param redirector OH_TrafficFilter_Redirector句柄。
 * @return {@link OH_TRAFFICFILTER_OK} - 成功。
 *     <br>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} - 缺少权限。
 *     <br>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} - redirector为NULL。
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_ClearRedirectRule(OH_TrafficFilter_Redirector* redirector);
 
/**
 * @brief 根据网络连接信息查询对应的进程信息。通过源IP、目的IP、源端口、目的端口和协议类型组成的五元组连接信息，查询发起该连接的进程信息。
 *
 * @param connection_info 输入的连接信息。
 * @param process_info 输出的进程信息。
 * @return {@link OH_TRAFFICFILTER_OK} - 成功。
 *     <br>{@link OH_TRAFFICFILTER_ERROR_PERMISSION_DENIED} - 缺少权限。
 *     <br>{@link OH_TRAFFICFILTER_ERROR_INVALID_PARAM} - 输入参数无效。
 *     <br>{@link OH_TRAFFICFILTER_ERROR_NOT_FOUND} - 未找到进程。
 * @permission ohos.permission.kernel.TRAFFIC_FILTER
 * @since 26.0.0
 */
int32_t OH_TrafficFilter_QueryProcess(
    const OH_TrafficFilter_ConnectionInfo* connection_info,
    OH_TrafficFilter_ProcessInfo* process_info
);
 
#ifdef __cplusplus
}
#endif
 
#endif /* NET_TRAFFICFILTER_H */
/** @} */