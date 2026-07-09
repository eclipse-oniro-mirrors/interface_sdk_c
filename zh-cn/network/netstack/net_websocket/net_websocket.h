/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#ifndef NET_WEBSOCKET_H
#define NET_WEBSOCKET_H

#include <signal.h>
#include <stdint.h>
#include <string.h>

/**
 * @addtogroup netstack
 * @{
 *
 * @brief 提供WebSocket客户端模块的接口。

 * @since 11
 * @version 1.0
 */

/**
 * @file net_websocket.h
 *
 * @brief 定义WebSocket客户端模块的接口。
 *
 * @library libnet_websocket.so
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */

#include "net_websocket_type.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief WebSocket客户端的构造函数。
 *
 * @param onOpen 客户端定义的建立连接消息的回调函数。
 * @param onMessage 客户端定义的接收消息的回调函数。
 * @param onError 客户端定义的错误消息的回调函数。
 * @param onclose 客户端定义的关闭消息的回调函数。
 * @return 成功返回客户端指针，失败返回为NULL。
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
struct WebSocket *OH_WebSocketClient_Constructor(WebSocket_OnOpenCallback onOpen, WebSocket_OnMessageCallback onMessage,
                                                 WebSocket_OnErrorCallback onError, WebSocket_OnCloseCallback onclose);
/**
 * @brief 将header头信息添加到client客户端request中。
 *
 * @param client 客户端指针。
 * @param header Header头信息。
 * @return 返回值为0表示执行成功，返回值不为0表示失败。返回值详细信息可以查看OH_Websocket_ErrCode。
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
int OH_WebSocketClient_AddHeader(struct WebSocket *client, struct WebSocket_Header header);
/**
 * @brief 客户端连接服务端。
 *
 * @param client 客户端指针。
 * @param url 客户端要连接到服务端的地址。
 * @param options 发起连接的可选参数。
 * @return 返回值为0表示执行成功，返回值不为0表示失败。返回值详细信息可以查看OH_Websocket_ErrCode。
 * @permission ohos.permission.INTERNET
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
int OH_WebSocketClient_Connect(struct WebSocket *client, const char *url, struct WebSocket_RequestOptions options);
/**
 * @brief 客户端向服务端发送数据。
 *
 * @param client 客户端。
 * @param data Data sent by the 客户端。
 * @param length Length of the data sent by the 客户端。
 * @return 返回值为0表示执行成功，返回值不为0表示失败。返回值详细信息可以查看OH_Websocket_ErrCode。
 * @permission ohos.permission.INTERNET
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
int OH_WebSocketClient_Send(struct WebSocket *client, char *data, size_t length);
/**
 * @brief Closes the connection on the 客户端。
 *
 * @param client 客户端。
 * @param options 发起关闭连接的可选参数。
 * @return 返回值为0表示执行成功，返回值不为0表示失败。返回值详细信息可以查看OH_Websocket_ErrCode。
 * @permission ohos.permission.INTERNET
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
int OH_WebSocketClient_Close(struct WebSocket *client, struct WebSocket_CloseOption options);
/**
 * @brief 释放WebSocket连接上下文和资源。使用方式如下：
 *
 * @param client 客户端。
 * @return 返回值为0表示执行成功，返回值不为0表示失败。返回值详细信息可以查看OH_Websocket_ErrCode。
 * @permission ohos.permission.INTERNET
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
int OH_WebSocketClient_Destroy(struct WebSocket *client);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // NET_WEBSOCKET_H