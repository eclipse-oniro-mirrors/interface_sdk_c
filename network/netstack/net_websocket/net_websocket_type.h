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
 * @brief Provides C APIs for the WebSocket client module.
 *
 * @since 11
 * @version 1.0
 */

/**
 * @file net_websocket_type.h
 * @brief Defines the data structure for the C APIs of the WebSocket client module.
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
 * @brief Defines the parameters for the connection closure received by the WebSocket client.
 *
 * @since 11
 * @version 1.0
 */
struct WebSocket_CloseResult {
    /**
     * Error code.
     */
    uint32_t code;
    /**
     * Error cause.
     */
    const char *reason;
};

/**
 * @brief Defines the parameters for the proactive connection closure initiated by the WebSocket client.
 *
 * @since 11
 * @version 1.0
 */
struct WebSocket_CloseOption {
    /**
     * Error code.
     */
    uint32_t code;
    /**
     * Error cause.
     */
    const char *reason;
};

/**
 * @brief Defines the parameters for the connection error received by the WebSocket client.
 *
 * @since 11
 * @version 1.0
 */
struct WebSocket_ErrorResult {
    /**
     * Error code.
     */
    uint32_t errorCode;
    /**
     * Error message.
     */
    const char *errorMessage;
};

/**
 * @brief Defines the parameters for the connection success received by the WebSocket client.
 *
 * @since 11
 * @version 1.0
 */
struct WebSocket_OpenResult {
    /**
     * Result code for successful WebSocket client connection.
     */
    uint32_t code;
    /**
     * Reason for successful WebSocket client connection.
     */
    const char *reason;
};

/**
 * @brief Callback invoked when the WebSocket client receives an **Open** message.
 *
 * @param client WebSocket client.
 * @param openResult Content of the **Open** message sent from the WebSocket server to client.
 * @since 11
 * @version 1.0
 */
typedef void (*WebSocket_OnOpenCallback)(struct WebSocket *client, WebSocket_OpenResult openResult);

/**
 * @brief Callback invoked when the WebSocket client receives a **Message** message.
 *
 * @param client WebSocket client.
 * @param data Data received by the WebSocket client.
 * @param length Length of the data received by the WebSocket client.
 * @since 11
 * @version 1.0
 */
typedef void (*WebSocket_OnMessageCallback)(struct WebSocket *client, char *data, uint32_t length);

/**
 * @brief Callback invoked when the WebSocket client receives an **Error** message.
 *
 * @param client WebSocket client.
 * @param errorResult Content of the **Error** message sent from the WebSocket server to client.
 * @since 11
 * @version 1.0
 */
typedef void (*WebSocket_OnErrorCallback)(struct WebSocket *client, WebSocket_ErrorResult errorResult);

/**
 * @brief Callback invoked when the WebSocket client receives a **Close** message.
 *
 * @param client WebSocket client.
 * @param closeResult Content of the **Close** message sent from the WebSocket server to client.
 * @since 11
 * @version 1.0
 */
typedef void (*WebSocket_OnCloseCallback)(struct WebSocket *client, WebSocket_CloseResult closeResult);

/**
 * @brief Defines the header linked list added to the WebSocket client.
 *
 * @since 11
 * @version 1.0
 */
struct WebSocket_Header {
    /**
     * Pointer to the field name of a header.
     */
    const char *fieldName;
    /**
     * Pointer to the field value of a header.
     */
    const char *fieldValue;
    /**
     * Next pointer of the header linked list.
     */
    struct WebSocket_Header *next;
};

/**
 * @brief Defines the parameters for the connection between the WebSocket client and server.
 *
 * @param headers Header information.
 * @since 11
 * @version 1.0
 */
struct WebSocket_RequestOptions {
    struct WebSocket_Header *headers;
};

/**
 * @brief Defines the parameters for the connection closure received by the WebSocket client.
 *
 * @since 11
 * @version 1.0
 */
struct WebSocket {
    /** Pointer to the callback invoked when the WebSocket client receives a connection message. */
    WebSocket_OnOpenCallback onOpen;
    /** Pointer to the callback invoked when the WebSocket client receives a message. */
    WebSocket_OnMessageCallback onMessage;
    /** Pointer to the callback invoked when the WebSocket client receives an error message. */
    WebSocket_OnErrorCallback onError;
    /** Pointer to the callback invoked when the WebSocket client receives a close message. */
    WebSocket_OnCloseCallback onClose;
    /** Options of the connection request. */
    WebSocket_RequestOptions requestOptions;
};

typedef enum WebSocket_ErrCode {
    /**
     * Operation successful.
     */
    WEBSOCKET_OK = 0,
    /**
     * @brief Base value of the error code.
     *
     */
    E_BASE = 1000,
    /**
     * @brief The WebSocket client is empty.
     *
     */
    WEBSOCKET_CLIENT_NULL = (E_BASE + 1),
    /**
     * @brief The WebSocket client is not created.
     *
     */
    WEBSOCKET_CLIENT_NOT_CREATED = (E_BASE + 2),
    /**
     * @brief An error occurred during WebSocket connection establishment.
     *
     */
    WEBSOCKET_CONNECTION_ERROR = (E_BASE + 3),
    /**
     * @brief An error occurred when parsing WebSocket connection parameters.
     *
     */
    WEBSOCKET_CONNECTION_PARSE_URL_ERROR = (E_BASE + 5),
    /**
     * @brief The memory is insufficient during WebSocket client connection establishment.
     *
     */
    WEBSOCKET_CONNECTION_NO_MEMORY = (E_BASE + 6),
    /**
     * @brief The WebSocket connection is closed by the peer end.
     *
     */
    WEBSOCKET_CONNECTION_CLOSED_BY_PEER = (E_BASE + 7),
    /**
     * @brief The WebSocket connection is disconnected.
     *
     */
    WEBSOCKET_DESTROYED = (E_BASE + 8),
    /**
     * @brief Incorrect protocol.
     *
     */
    WEBSOCKET_PROTOCOL_ERROR = (E_BASE + 9),
    /**
     * @brief The system memory is insufficient when the WebSocket client sends data.
     *
     */
    WEBSOCKET_SEND_NO_MEMORY = (E_BASE + 10),
    /**
     * @brief The sent data is empty.
     *
     */
    WEBSOCKET_SEND_DATA_NULL = (E_BASE + 11),
    /**
     * @brief The length of the sent data exceeds the limit.
     *
     */
    WEBSOCKET_DATA_LENGTH_EXCEEDED = (E_BASE + 12),
    /**
     * @brief The length of the sent data queue exceeds the limit.
     *
     */
    WEBSOCKET_QUEUE_LENGTH_EXCEEDED = (E_BASE + 13),
    /**
     * @brief The context of the WebSocket client is null.
     *
     */
    WEBSOCKET_NO_CLIENT_CONTEXT = (E_BASE + 14),
    /**
     * @brief The protocol header of the WebSocket client is empty.
     *
     */
    WEBSOCKET_NO_HEADER_CONTEXT = (E_BASE + 15),
    /**
     * @brief The protocol header of the WebSocket client exceeds the limit.
     *
     */
    WEBSOCKET_HEADER_EXCEEDED = (E_BASE + 16),
    /**
     * @brief The WebSocket client is not connected.
     *
     */
    WEBSOCKET_NO_CONNECTION = (E_BASE + 17),
    /**
     * @brief No WebSocket connection context is released.
     *
     */
    WEBSOCKET_NO_CONNECTION_CONTEXT = (E_BASE + 18)
} WebSocket_ErrCode;

#ifdef __cplusplus
}
#endif

/** @} */

#endif // NET_WEBSOCKET_TYPE_H