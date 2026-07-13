/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup netstack
 * @{
 *
 * @brief 定义HTTP请求模块的接口。
 *
 * @syscap SystemCapability.Communication.NetStack
 * @since 20
 */

/**
 * @file net_http.h
 * @brief 定义HTTP请求模块的接口。
 *
 * @library libnet_http.so
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetStack
 * @since 20
 */

#ifndef NET_HTTP_H
#define NET_HTTP_H

#include <stdint.h>
#include <string.h>

#include "net_http_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建HTTP请求或者响应的头。
 *
 * @return Http_Headers 返回HTTP请求或者响应的头，指向Http_Headers。
 * @syscap SystemCapability.Communication.NetStack
 * @since 20
 */
Http_Headers *OH_Http_CreateHeaders(void);

/**
 * @brief 销毁HTTP请求或者响应的头。
 *
 * @param headers 要被销毁的HTTP请求或响应的头，是通过OH_Http_CreateHeaders生成的数据。
 * @syscap SystemCapability.Communication.NetStack
 * @since 20
 */
void OH_Http_DestroyHeaders(Http_Headers **headers);

/**
 * @brief 设置HTTP请求或者响应的头的键值对。
 *
 * @param headers 指向要设置的Http_Headers的指针。
 * @param name 键值。
 * @param value 键值对应的值。
 * @return uint32_t 0 - 成功。 401 - 参数错误。 2300027 - 内存不足。
 * @syscap SystemCapability.Communication.NetStack
 * @since 20
 */
uint32_t OH_Http_SetHeaderValue(struct Http_Headers *headers, const char *name, const char *value);

/**
 * @brief 通过键获取请求或响应头的值。
 *
 * @param headers 指向要获取值的Http_Headers的指针。
 * @param name 键值。
 * @return Http_HeaderValue 指向获取的Http_HeaderValue的指针。
 * @syscap SystemCapability.Communication.NetStack
 * @since 20
 */
Http_HeaderValue *OH_Http_GetHeaderValue(Http_Headers *headers, const char *name);

/**
 * @brief 获取请求或响应头的所有键值对。
 *
 * @param headers 指向要获取值的Http_Headers的指针。
 * @return Http_HeaderEntry 指向获取的Http_HeaderEntry的指针。
 * @syscap SystemCapability.Communication.NetStack
 * @since 20
 */
Http_HeaderEntry *OH_Http_GetHeaderEntries(Http_Headers *headers);

/**
 * @brief 销毁OH_Http_GetHeaderEntries中获取的所有键值对。
 *
 * @param headerEntry 指向要销毁的Http_HeaderEntry的指针，是通过OH_Http_GetHeaderEntries获取的数据。
 * @syscap SystemCapability.Communication.NetStack
 * @since 20
 */
void OH_Http_DestroyHeaderEntries(Http_HeaderEntry **headerEntry);

/**
 * @brief 创建HTTP请求。
 *
 * @param url 请求URL。
 * @return 返回创建的请求，指向Http_Request的指针。
 * @syscap SystemCapability.Communication.NetStack
 * @since 20
 */
Http_Request *OH_Http_CreateRequest(const char *url);

/**
 * @brief 发起HTTP请求。
 *
 * @param request 发送的请求，指向Http_Request的指针。
 * @param callback 请求的响应，指向Http_ResponseCallback。
 * @param handler 监听不同HTTP事件的回调函数，指向Http_EventsHandler。
 * @return 请求发起成功返回0，非0表示请求发起失败，错误码的具体描述，可以参考Http_ErrCode。
 *     <br>在Http_ResponseCallback中也会携带errCode信息，表示请求发起成功，但是因为一些原因，和服务器的交互异常，具体异常原因，同步参考Http_ErrCode。
 * @permission ohos.permission.INTERNET
 * @syscap SystemCapability.Communication.NetStack
 * @since 20
 */
int OH_Http_Request(Http_Request *request, Http_ResponseCallback callback, Http_EventsHandler handler);

/**
 * @brief 中断HTTP请求。
 *
 * @param request 要中断的请求，指向Http_Request的指针，参考{@link Http_Request}。
 * @syscap SystemCapability.Communication.NetStack
 * @since 20
 */
void OH_Http_Destroy(struct Http_Request **request);

#ifdef __cplusplus
}
#endif
#endif // NET_HTTP_H

/** @} */