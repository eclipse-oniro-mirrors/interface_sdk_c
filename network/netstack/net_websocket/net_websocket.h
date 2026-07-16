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
 * @brief Provides C APIs for the websocket client module.

 * @since 11
 * @version 1.0
 */

/**
 * @file net_websocket.h
 *
 * @brief Defines the APIs for the websocket client module.
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
 * @brief Constructor used to create a WebSocket client.
 *
 * @param onOpen Callback invoked when the WebSocket client receives an **open** message.
 * @param onMessage Callback invoked when the WebSocket client receives a **Message** message.
 * @param onError Callback invoked when the WebSocket client receives an **error** message.
 * @param onclose Callback invoked when the WebSocket client receives a **close** message.
 * @return Pointer to the WebSocket client if the operation is successful; **NULL** otherwise.
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
struct WebSocket *OH_WebSocketClient_Constructor(WebSocket_OnOpenCallback onOpen, WebSocket_OnMessageCallback onMessage,
                                                 WebSocket_OnErrorCallback onError, WebSocket_OnCloseCallback onclose);
/**
 * @brief Adds the header information to the client request.
 *
 * @param client Pointer to the WebSocket client.
 * @param header Header information.
 * @return **0** if the operation is successful; a non-0 value otherwise. For details about the return values, see **
 *     OH_Websocket_ErrCode**.
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
int OH_WebSocketClient_AddHeader(struct WebSocket *client, struct WebSocket_Header header);
/**
 * @brief Connects the WebSocket client to the server.
 *
 * @param client Pointer to the WebSocket client.
 * @param url IP address for the WebSocket client to connect to the server.
 * @param options Optional parameters for connection establishment.
 * @return **0** if the operation is successful; a non-0 value otherwise. For details about the return values, see **
 *     OH_Websocket_ErrCode**.
 * @permission ohos.permission.INTERNET
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
int OH_WebSocketClient_Connect(struct WebSocket *client, const char *url, struct WebSocket_RequestOptions options);
/**
 * @brief Sends data from the WebSocket client to the server.
 *
 * @param client WebSocket client.
 * @param data Data sent by the WebSocket client.
 * @param length Length of the data sent by the WebSocket client.
 * @return **0** if the operation is successful; a non-0 value otherwise. For details about the return values, see **
 *     OH_Websocket_ErrCode**.
 * @permission ohos.permission.INTERNET
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
int OH_WebSocketClient_Send(struct WebSocket *client, char *data, size_t length);
/**
 * @brief Closes the connection on the WebSocket client.
 *
 * @param client WebSocket client.
 * @param options Optional parameters for connection closure.
 * @return **0** if the operation is successful; a non-0 value otherwise. For details about the return values, see **
 *     OH_Websocket_ErrCode**.
 * @permission ohos.permission.INTERNET
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */
int OH_WebSocketClient_Close(struct WebSocket *client, struct WebSocket_CloseOption options);
/**
 * @brief Destroys the WebSocket client and releases the context and resources of the WebSocket connection. Usage:
 *
 * @param client WebSocket client.
 * @return **0** if the operation is successful; a non-0 value otherwise. For details about the return values, see **
 *     OH_Websocket_ErrCode**.
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