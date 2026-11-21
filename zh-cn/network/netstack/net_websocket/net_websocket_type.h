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

#ifndef NET_WEBSOCKET_TYPE_H
#define NET_WEBSOCKET_TYPE_H

/**
 * @addtogroup netstack
 * @{
 *
 * @brief 提供WebSocket客户端模块的C接口。
 *
 * @since 11
 * @version 1.0
 */

/**
 * @file net_websocket_type.h
 * @brief 定义WebSocket客户端模块的C接口需要的数据结构。
 *
 * @library libnet_websocket.so
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetStack
 * @since 11
 * @version 1.0
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief WebSocket客户端接收到服务端关闭的参数。
 *
 * @since 11
 * @version 1.0
 */
struct WebSocket_CloseResult {
    /**
     * 错误码。
     */
    uint32_t code;
    /**
     * 错误原因。
     */
    const char *reason;
};

/**
 * @brief WebSocket客户端主动关闭的参数。
 *
 * @since 11
 * @version 1.0
 */
struct WebSocket_CloseOption {
    /**
     * 错误值。
     */
    uint32_t code;
    /**
     * 错误原因。
     */
    const char *reason;
};

/**
 * @brief WebSocket客户端来自服务端连接错误的参数。
 *
 * @since 11
 * @version 1.0
 */
struct WebSocket_ErrorResult {
    /**
     * 错误值。
     */
    uint32_t errorCode;
    /**
     * 错误的消息。
     */
    const char *errorMessage;
};

/**
 * @brief WebSocket客户端来自服务端连接成功的参数。
 *
 * @since 11
 * @version 1.0
 */
struct WebSocket_OpenResult {
    /**
     * WebSocket客户端连接成功码。
     */
    uint32_t code;
    /**
     * WebSocket客户端连接成功原因。
     */
    const char *reason;
};

/**
 * @brief WebSocket客户端接收open消息的回调函数定义。
 * @param client WebSocket客户端。
 * @param openResult WebSocket客户端接收建立连接消息的内容。
 * @since 11
 * @version 1.0
 */
typedef void (*WebSocket_OnOpenCallback)(struct WebSocket *client, WebSocket_OpenResult openResult);

/**
 * @brief WebSocket客户端接收数据的回调函数定义。
 * @param client WebSocket客户端。
 * @param data WebSocket客户端接收的数据。
 * @param length WebSocket客户端接收数据的长度。
 * @since 11
 * @version 1.0
 */
typedef void (*WebSocket_OnMessageCallback)(struct WebSocket *client, char *data, uint32_t length);

/**
 * @brief WebSocket客户端接收error错误消息的回调函数定义。
 * @param client WebSocket客户端。
 * @param errorResult WebSocket客户端接收连接错误消息的内容。
 * @since 11
 * @version 1.0
 */
typedef void (*WebSocket_OnErrorCallback)(struct WebSocket *client, WebSocket_ErrorResult errorResult);

/**
 * @brief WebSocket客户端接收close消息的回调函数定义。
 * @param client WebSocket客户端。
 * @param closeResult WebSocket客户端接收的关闭消息内容。
 * @since 11
 * @version 1.0
 */
typedef void (*WebSocket_OnCloseCallback)(struct WebSocket *client, WebSocket_CloseResult closeResult);

/**
 * @brief WebSocket客户端增加header的链表节点。
 *
 * @since 11
 * @version 1.0
 */
struct WebSocket_Header {
    /**
     * header的字段名。
     */
    const char *fieldName;
    /**
     * header的字段内容。
     */
    const char *fieldValue;
    /**
     * header链表的next指针。
     */
    struct WebSocket_Header *next;
};

/**
 * @brief webSocket客户端和服务端建立连接的参数。
 *
 * @param headers 头信息。
 * @since 11
 * @version 1.0
 */
struct WebSocket_RequestOptions {
    /**
     * header头信息。
     */
    struct WebSocket_Header *headers;
};

/**
 * @brief WebSocket客户端结构体。
 *
 * @since 11
 * @version 1.0
 */
struct WebSocket {
    /**
     * 客户端接收连接消息的回调指针。
     */
    WebSocket_OnOpenCallback onOpen;
    /**
     * 客户端接收消息的回调指针。
     */
    WebSocket_OnMessageCallback onMessage;
    /**
     * 客户端接收错误消息的回调指针。
     */
    WebSocket_OnErrorCallback onError;
    /**
     * 客户端接收关闭消息的回调指针。
     */
    WebSocket_OnCloseCallback onClose;
    /**
     * 客户端建立连接请求内容。
     */
    WebSocket_RequestOptions requestOptions;
};

/**
 * @brief 定义WebSocket请求的错误码。
 *
 * @since 11
 * @version 1.0
 */
typedef enum WebSocket_ErrCode {
    /**
     * @brief 操作成功。
     */
    WEBSOCKET_OK = 0,

    /**
     * @brief 错误码基准值。
     */
    E_BASE = 1000,

    /**
     * @brief WebSocket客户端为空。
     */
    WEBSOCKET_CLIENT_NULL = (E_BASE + 1),

    /**
     * @brief WebSocket客户端未创建。
     */
    WEBSOCKET_CLIENT_NOT_CREATED = (E_BASE + 2),

    /**
     * @brief 建立WebSocket连接时发生错误。
     */
    WEBSOCKET_CONNECTION_ERROR = (E_BASE + 3),

    /**
     * @brief 解析WebSocket连接参数时出错。
     */
    WEBSOCKET_CONNECTION_PARSE_URL_ERROR = (E_BASE + 5),

    /**
     * @brief WebSocket客户端建立连接过程中内存不足。
     */
    WEBSOCKET_CONNECTION_NO_MEMORY = (E_BASE + 6),

    /**
     * @brief WebSocket连接被对端关闭。
     */
    WEBSOCKET_CONNECTION_CLOSED_BY_PEER = (E_BASE + 7),

    /**
     * @brief WebSocket连接断开。
     */
    WEBSOCKET_DESTROYED = (E_BASE + 8),

    /**
     * @brief 协议错误。
     */
    WEBSOCKET_PROTOCOL_ERROR = (E_BASE + 9),

    /**
     * @brief WebSocket客户端发送数据时系统内存不足。
     */
    WEBSOCKET_SEND_NO_MEMORY = (E_BASE + 10),

    /**
     * @brief 发送数据为空。
     */
    WEBSOCKET_SEND_DATA_NULL = (E_BASE + 11),

    /**
     * @brief 发送数据长度超出限制。
     */
    WEBSOCKET_DATA_LENGTH_EXCEEDED = (E_BASE + 12),

    /**
     * @brief 发送数据队列长度超出限制。
     */
    WEBSOCKET_QUEUE_LENGTH_EXCEEDED = (E_BASE + 13),

    /**
     * @brief WebSocket客户端的上下文为空。
     */
    WEBSOCKET_NO_CLIENT_CONTEXT = (E_BASE + 14),

    /**
     * @brief WebSocket客户端协议头为空。
     */
    WEBSOCKET_NO_HEADER_CONTEXT = (E_BASE + 15),

    /**
     * @brief WebSocket客户端协议头超出限制。
     */
    WEBSOCKET_HEADER_EXCEEDED = (E_BASE + 16),

    /**
     * @brief WebSocket客户端未连接。
     */
    WEBSOCKET_NO_CONNECTION = (E_BASE + 17),

    /**
     * @brief 释放WebSocket连接上下文时无相应上下文。
     */
    WEBSOCKET_NO_CONNECTION_CONTEXT = (E_BASE + 18)
} WebSocket_ErrCode;

#ifdef __cplusplus
}
#endif

/** @} */

#endif // NET_WEBSOCKET_TYPE_H