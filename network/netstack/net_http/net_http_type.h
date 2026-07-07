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
 * @brief Provides C APIs for the Http client module.
 *
 * @since 20
 */

/**
 * @file net_http_type.h
 * @brief Defines the data structures for the C APIs of the HTTP request module.
 *
 * @library libnet_http.so
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetStack
 * @since 20
 */

#ifndef NET_HTTP_TYPE_H
#define NET_HTTP_TYPE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
#include <stddef.h>

/**
 * @brief Defines the maximum path length of an HTTP request.
 *
 * @since 20
 */
#define OHOS_HTTP_MAX_PATH_LEN 128

/**
 * @brief Defines the maximum string length of an HTTP request.
 *
 * @since 20
 */
#define OHOS_HTTP_MAX_STR_LEN 256

/**
 * @brief Defines the maximum number of DNS servers for an HTTP request.
 *
 * @since 20
 */
#define OHOS_HTTP_DNS_SERVER_NUM_MAX 3

/**
 * @brief Defines http error code.
 *
 * @since 20
 */
typedef enum Http_ErrCode {
    /** Operation success. */
    OH_HTTP_RESULT_OK = 0,
    /** @brief Parameter error. */
    OH_HTTP_PARAMETER_ERROR = 401,
    /** @brief Permission denied. */
    OH_HTTP_PERMISSION_DENIED = 201,
    /** @brief Error code base. */
    OH_HTTP_NETSTACK_E_BASE = 2300000,
    /** @brief Unsupported protocol. */
    OH_HTTP_UNSUPPORTED_PROTOCOL = (OH_HTTP_NETSTACK_E_BASE + 1),
    /** @brief Invalid URL format or missing URL. */
    OH_HTTP_INVALID_URL = (OH_HTTP_NETSTACK_E_BASE + 3),
    /** @brief Failed to resolve the proxy name. */
    OH_HTTP_RESOLVE_PROXY_FAILED = (OH_HTTP_NETSTACK_E_BASE + 5),
    /** @brief Failed to resolve the host name. */
    OH_HTTP_RESOLVE_HOST_FAILED = (OH_HTTP_NETSTACK_E_BASE + 6),
    /** @brief Failed to connect to the server. */
    OH_HTTP_CONNECT_SERVER_FAILED = (OH_HTTP_NETSTACK_E_BASE + 7),
    /** @brief Invalid server response. */
    OH_HTTP_INVALID_SERVER_RESPONSE = (OH_HTTP_NETSTACK_E_BASE + 8),
    /** @brief Access to the remote resource denied. */
    OH_HTTP_ACCESS_REMOTE_DENIED = (OH_HTTP_NETSTACK_E_BASE + 9),
    /** @brief Error in the HTTP2 framing layer. */
    OH_HTTP_HTTP2_FRAMING_ERROR = (OH_HTTP_NETSTACK_E_BASE + 16),
    /** @brief Transferred a partial file. */
    OH_HTTP_TRANSFER_PARTIAL_FILE = (OH_HTTP_NETSTACK_E_BASE + 18),
    /** @brief Failed to write the received data to the disk or application. */
    OH_HTTP_WRITE_DATA_FAILED = (OH_HTTP_NETSTACK_E_BASE + 23),
    /** @brief Upload failed. */
    OH_HTTP_UPLOAD_FAILED = (OH_HTTP_NETSTACK_E_BASE + 25),
    /** @brief Failed to open or read local data from the file or application. */
    OH_HTTP_OPEN_LOCAL_DATA_FAILED = (OH_HTTP_NETSTACK_E_BASE + 26),
    /** @brief Out of memory. */
    OH_HTTP_OUT_OF_MEMORY = (OH_HTTP_NETSTACK_E_BASE + 27),
    /** @brief Operation timeout. */
    OH_HTTP_OPERATION_TIMEOUT = (OH_HTTP_NETSTACK_E_BASE + 28),
    /** @brief The number of redirections reaches the maximum allowed. */
    OH_HTTP_TOO_MANY_REDIRECTIONS = (OH_HTTP_NETSTACK_E_BASE + 47),
    /** @brief The server returned nothing (no header or data). */
    OH_HTTP_SERVER_RETURNED_NOTHING = (OH_HTTP_NETSTACK_E_BASE + 52),
    /** @brief Failed to send data to the peer. */
    OH_HTTP_SEND_DATA_FAILED = (OH_HTTP_NETSTACK_E_BASE + 55),
    /** @brief Failed to receive data from the peer. */
    OH_HTTP_RECEIVE_DATA_FAILED = (OH_HTTP_NETSTACK_E_BASE + 56),
    /** @brief Local SSL certificate error. */
    OH_HTTP_SSL_CERTIFICATE_ERROR = (OH_HTTP_NETSTACK_E_BASE + 58),
    /** @brief The specified SSL cipher cannot be used. */
    OH_HTTP_SSL_CIPHER_USED_ERROR = (OH_HTTP_NETSTACK_E_BASE + 59),
    /** @brief Invalid SSL peer certificate or SSH remote key. */
    OH_HTTP_INVALID_SSL_PEER_CERT = (OH_HTTP_NETSTACK_E_BASE + 60),
    /** @brief Invalid HTTP encoding format. */
    OH_HTTP_INVALID_ENCODING_FORMAT = (OH_HTTP_NETSTACK_E_BASE + 61),
    /** @brief Maximum file size exceeded. */
    OH_HTTP_FILE_TOO_LARGE = (OH_HTTP_NETSTACK_E_BASE + 63),
    /** @brief Remote disk full. */
    OH_HTTP_REMOTE_DISK_FULL = (OH_HTTP_NETSTACK_E_BASE + 70),
    /** @brief Remote file already exists. */
    OH_HTTP_REMOTE_FILE_EXISTS = (OH_HTTP_NETSTACK_E_BASE + 73),
    /** @brief The SSL CA certificate does not exist or is inaccessible. */
    OH_HTTP_SSL_CA_NOT_EXIST = (OH_HTTP_NETSTACK_E_BASE + 77),
    /** @brief Remote file not found. */
    OH_HTTP_REMOTE_FILE_NOT_FOUND = (OH_HTTP_NETSTACK_E_BASE + 78),
    /**
     * @brief The request was intercepted by the HTTP global interceptor.
     * @since 26.0.0
     */
    OH_HTTP_REQUEST_INTERCEPTED = (OH_HTTP_NETSTACK_E_BASE + 996),
    /** @brief Authentication error. */
    OH_HTTP_AUTHENTICATION_ERROR = (OH_HTTP_NETSTACK_E_BASE + 94),
    /** @brief It is not allowed to access this domain. */
    OH_HTTP_ACCESS_DOMAIN_NOT_ALLOWED = (OH_HTTP_NETSTACK_E_BASE + 998),
    /** @brief Unknown error. */
    OH_HTTP_UNKNOWN_ERROR = (OH_HTTP_NETSTACK_E_BASE + 999)
} Http_ErrCode;

/**
 * @brief Defines http response code.
 *
 * @since 20
 */
typedef enum Http_ResponseCode {
    /** @brief The request was successful. */
    OH_HTTP_OK = 200,
    /** @brief Successfully requested and created a new resource. */
    OH_HTTP_CREATED = 201,
    /** @brief The request has been accepted but has not been processed completely. */
    OH_HTTP_ACCEPTED = 202,
    /** @brief Unauthorized information. The request was successful. */
    OH_HTTP_NON_AUTHORITATIVE_INFO = 203,
    /** @brief No content. The server successfully processed, but did not return content. */
    OH_HTTP_NO_CONTENT = 204,
    /** @brief Reset the content. */
    OH_HTTP_RESET = 205,
    /** @brief Partial content. The server successfully processed some GET requests. */
    OH_HTTP_PARTIAL = 206,
    /** @brief Multiple options. */
    OH_HTTP_MULTI_CHOICE = 300,
    /**
     * @brief Permanently move. The requested resource has been permanently moved to a new URI,
     * and the returned information will include the new URI. The browser will automatically redirect to the new URI.
     */
    OH_HTTP_MOVED_PERM = 301,
    /** @brief Temporary movement. */
    OH_HTTP_MOVED_TEMP = 302,
    /** @brief View other addresses. */
    OH_HTTP_SEE_OTHER = 303,
    /** @brief Not modified. */
    OH_HTTP_NOT_MODIFIED = 304,
    /** @brief Using proxies. */
    OH_HTTP_USE_PROXY = 305,
    /** @brief The server cannot understand the syntax error error requested by the client. */
    OH_HTTP_BAD_REQUEST = 400,
    /** @brief Request for user authentication. */
    OH_HTTP_UNAUTHORIZED = 401,
    /** @brief Reserved for future use. */
    OH_HTTP_PAYMENT_REQUIRED = 402,
    /** @brief The server understands the request from the requesting client, but refuses to execute it. */
    OH_HTTP_FORBIDDEN = 403,
    /** @brief The server was unable to find resources (web pages) based on the client's request. */
    OH_HTTP_NOT_FOUND = 404,
    /** @brief The method in the client request is prohibited. */
    OH_HTTP_BAD_METHOD = 405,
    /** @brief The server unabled to complete request based on the content characteristics requested by the client. */
    OH_HTTP_NOT_ACCEPTABLE = 406,
    /** @brief Request authentication of the proxy's identity. */
    OH_HTTP_PROXY_AUTH = 407,
    /** @brief The request took too long and timed out. */
    OH_HTTP_CLIENT_TIMEOUT = 408,
    /**
     * @brief The server may have returned this code when completing the client's PUT request,
     * as there was a conflict when the server was processing the request.
     */
    OH_HTTP_CONFLICT = 409,
    /** @brief The resource requested by the client no longer exists. */
    OH_HTTP_GONE = 410,
    /** @brief The server is unable to process request information sent by the client without Content Length. */
    OH_HTTP_LENGTH_REQUIRED = 411,
    /** @brief The prerequisite for requesting information from the client is incorrect. */
    OH_HTTP_PRECON_FAILED = 412,
    /** @brief The request was rejected because the requested entity was too large for the server to process. */
    OH_HTTP_ENTITY_TOO_LARGE = 413,
    /** @brief The requested URI is too long (usually a URL) and the server cannot process it. */
    OH_HTTP_REQUEST_TOO_LONG = 414,
    /** @brief The server is unable to process the requested format. */
    OH_HTTP_UNSUPPORTED_TYPE = 415,
    /** @brief Requested Range not satisfiable. */
    OH_HTTP_RANGE_NOT_MET = 416,
    /** @brief Internal server error, unable to complete the request. */
    OH_HTTP_INTERNAL_ERROR = 500,
    /** @brief The server does not support the requested functionality and cannot complete the request. */
    OH_HTTP_NOT_IMPLEMENTED = 501,
    /** @brief The server acting as a gateway or proxy received an invalid request from the remote server. */
    OH_HTTP_BAD_GATEWAY = 502,
    /** @brief Due to overload or system maintenance, the server is temporarily unable to process client requests. */
    OH_HTTP_UNAVAILABLE = 503,
    /** @brief The server acting as gateway did not obtain requests from the remote server in a timely manner. */
    OH_HTTP_GATEWAY_TIMEOUT = 504,
    /** @brief The version of the HTTP protocol requested by the server. */
    OH_HTTP_VERSION = 505
} Http_ResponseCode;

/**
 * @brief Defines the HTTP buffer structure.
 *
 * @since 20
 */
typedef struct Http_Buffer {
    /**
     * Buffer data.
     */
    const char *buffer;
    /**
     * Buffer length.
     */
    uint32_t length;
} Http_Buffer;

/**
 * @brief Defines the address Family.
 *
 * @since 20
 */
typedef enum Http_AddressFamilyType {
    /** Default, The system automatically selects the IPv4 or IPv6 address of the domain name. */
    HTTP_ADDRESS_FAMILY_DEFAULT = 0,
    /** IPv4, Selects the IPv4 address of the domain name. */
    HTTP_ADDRESS_FAMILY_ONLY_V4 = 1,
    /** IPv6, Selects the IPv4 address of the domain name. */
    HTTP_ADDRESS_FAMILY_ONLY_V6 = 2
} Http_AddressFamilyType;

/**
 * @brief Sets the HTTP request method to GET.
 * 
 * @since 20
 */
#define NET_HTTP_METHOD_GET "GET"

/**
 * @brief Sets the HTTP request method to HEAD.
 * 
 * @since 20
 */
#define NET_HTTPMETHOD_HEAD "HEAD"

/**
 * @brief Sets the HTTP request method to OPTIONS.
 * 
 * @since 20
 */
#define NET_HTTPMETHOD_OPTIONS "OPTIONS"

/**
 * @brief Sets the HTTP request method to TRACE.
 * 
 * @since 20
 */
#define NET_HTTPMETHOD_TRACE "TRACE"
/**
 * @brief Sets the HTTP request method to DELETE.
 *
 * @since 20
 */
#define NET_HTTPMETHOD_DELETE "DELETE"

/**
 * @brief Sets the HTTP request method to POST.
 * 
 * @since 20
 */
#define NET_HTTP_METHOD_POST "POST"

/**
 * @brief Sets the HTTP request method to PUT.
 * 
 * @since 20
 */
#define NET_HTTP_METHOD_PUT "PUT"

/**
 * @brief Sets the HTTP request method to CONNECT.
 * 
 * @since 20
 */
#define NET_HTTP_METHOD_PATCH "CONNECT"

/**
 * @brief Defines the HTTP version.
 *
 * @since 20
 */
typedef enum Http_HttpProtocol {
    /** Default choose by curl. */
    OH_HTTP_NONE = 0,
    /** HTTP 1.1 version. */
    OH_HTTP1_1,
    /** HTTP 2 version. */
    OH_HTTP2,
    /** HTTP 3 version. */
    OH_HTTP3
} Http_HttpProtocol;

/**
 * @brief Defines the Cert Type.
 *
 * @since 20
 */
typedef enum Http_CertType {
    /** PEM Cert Type. */
    OH_HTTP_PEM = 0,
    /** DER Cert Type. */
    OH_HTTP_DER = 1,
    /** P12 Cert Type. */
    OH_HTTP_P12 = 2
} Http_CertType;

/**
 * @brief Defines the header of an HTTP request or response.
 *
 * @since 20
 */
typedef struct Http_Headers Http_Headers;

/**
 * @brief Defines the type of a mapped value in a request or response header.
 *
 * @since 20
 */
typedef struct Http_HeaderValue {
    /**
     * Value of a key-value pair in the header.
     */
    char *value;
    /**
     * Pointer to Pointer to the next **Http_HeaderValue**.
     */
    struct Http_HeaderValue *next;
} Http_HeaderValue;

/**
 * @brief Defines all key-value pairs in the request or response header.
 *
 * @since 20
 */
typedef struct Http_HeaderEntry {
    /**
     * Key in the request or response header.
     */
    char *key;
    /**
     * Value of the key in the request or response header. For details, see {@link Http_HeaderValue}.
     */
    Http_HeaderValue *value;
    /**
     * Pointer to Pointer to the next **Http_HeaderEntry**.
     */
    struct Http_HeaderEntry *next;
} Http_HeaderEntry;

/**
 * @brief Defines the client certificate sent to a remote server, which will be used by the server to verify the
 * identity of the client.
 *
 * @since 20
 */
typedef struct Http_ClientCert {
    /**
     * Path of the certificate file.
     */
    char *certPath;
    /**
     * Certificate type. The default value is **PEM**. For details, see {@link Http_CertType}.
     */
    Http_CertType type;
    /**
     * Path of the certificate key file.
     */
    char *keyPath;
    /**
     * Password of the certificate key file.
     */
    char *keyPassword;
} Http_ClientCert;

/**
 * @brief Proxy type. Used to distinguish different proxy configurations.
 *
 * @since 20
 */
typedef enum Http_ProxyType {
    /** No proxy */
    HTTP_PROXY_NOT_USE,
    /** System proxy */
    HTTP_PROXY_SYSTEM,
    /** Use custom proxy */
    HTTP_PROXY_CUSTOM
} Http_ProxyType;

/**
 * @brief Defines the custom proxy configuration.
 *
 * @since 20
 */
typedef struct Http_CustomProxy {
    /**
     * Host name of the proxy server. If no port is explicitly set, the port number is defaulted to **1080**.
     */
    const char *host;
    int32_t port;
    const char *exclusionLists;
} Http_CustomProxy;

/**
 * @brief Defines the proxy configuration structure.
 *
 * @since 20
 */
typedef struct Http_Proxy {
    /**
     * Proxy configuration type. For details, see {@link Http_ProxyType}.
     */
    Http_ProxyType proxyType;
    /**
     * Custom proxy configuration. For details, see {@link Http_CustomProxy}.
     */
    Http_CustomProxy customProxy;
} Http_Proxy;

/**
 * @brief Defines the HTTP response timing information, which will be collected via {@link Http_Response}.
 *
 * @since 20
 */
typedef struct Http_PerformanceTiming {
    /**
     * Duration from the time when the request is initiated to the time when the DNS resolution is complete.
     */
    double dnsTiming;
    /**
     * Duration from the time when the request is initiated to the time when the TCP connection is complete.
     */
    double tcpTiming;
    /**
     * Duration from the time when the request is initiated to the time when the TLS connection is complete.
     */
    double tlsTiming;
    /**
     * Duration from the time when the request is initiated to the time when the first byte is sent.
     */
    double firstSendTiming;
    /**
     * Duration from the time when the request is initiated to the time when the first byte is received.
     */
    double firstReceiveTiming;
    /**
     * Duration from the time when the request is initiated to the time when the request is complete.
     */
    double totalFinishTiming;
    /**
     * Duration from the time when the request is initiated to the time when all redirection steps are complete.
     */
    double redirectTiming;
} Http_PerformanceTiming;

/**
 * @brief Defines the structure of HTTP requests.
 *
 * @since 20
 */
typedef struct Http_RequestOptions {
    /**
     * HTTP request method.
     */
    const char *method;
    /**
     * HTTP request priority.
     */
    uint32_t priority;
    /**
     * Pointer to the HTTP request header. For details, see {@link Http_Headers}.
     */
    Http_Headers *headers;
    /**
     * Read timeout duration.
     */
    uint32_t readTimeout;
    /**
     * Connection timeout duration.
     */
    uint32_t connectTimeout;
    /**
     * HTTP protocol. For details, see {@link Http_HttpProtocol}.
     */
    Http_HttpProtocol httpProtocol;
    /**
     * Pointer to the HTTP proxy configuration, which indicates whether to use a proxy. By default, proxy is not used.
     * For details, see {@link Http_Proxy}.
     */
    Http_Proxy *httpProxy;
    /**
     * Certificate path. If the CA certificate path is set, the system uses the CA certificate in the specified path.
     * Otherwise, the system uses the preset CA certificate.
     */
    const char *caPath;
    /**
     * Download start position. This field can be used only for the GET method.
     */
    int64_t resumeFrom;
    /**
     * Download end position. This field can be used only for the GET method.
     */
    int64_t resumeTo;
    /**
     * Pointer to the client certificate configuration. For details, see {@link Http_ClientCert}.
     */
    Http_ClientCert *clientCert;
    /**
     * HTTPS server for DNS resolution.
     */
    const char *dnsOverHttps;
    /**
     * IP address family. For details, see {@link Http_AddressFamilyType}.
     */
    Http_AddressFamilyType addressFamily;
} Http_RequestOptions;

/**
 * @brief Defines the structure of HTTP responses.
 *
 * @since 20
 */
typedef struct Http_Response {
    /**
     * HTTP response data. For details, see {@link Http_Buffer}.
     */
    Http_Buffer body;
    /**
     * HTTP response code. For details, see {@link Http_ResponseCode}.
     */
    Http_ResponseCode responseCode;
    /**
     * Pointer to the HTTP response header. For details, see {@link Http_Headers}.
     */
    Http_Headers *headers;
    /**
     * Pointer to the HTTP response cookies.
     */
    char *cookies;
    /**
     * Pointer to the HTTP response timing. For details, see {@link Http_PerformanceTiming}.
     */
    Http_PerformanceTiming *performanceTiming;
    /**
     * @brief Callback function for destroying an HTTP response.
     *
     * @param response Pointer to the HTTP response to be destroyed. For details, see {@link Http_Response}.
     * @since 20
     */
    void (*destroyResponse)(struct Http_Response **response);
} Http_Response;

/**
 * @brief Defines an HTTP request.
 *
 * @since 20
 */
typedef struct Http_Request {
    /**
     * ID of an HTTP request.
     */
    uint32_t requestId;
    /**
     * Pointer to the HTTP request URL.
     */
    char *url;
    /**
     * Pointer to the HTTP request configuration. For details, see {@link Http_RequestOptions}.
     */
    Http_RequestOptions *options;
} Http_Request;

/**
 * @brief Callback function that is invoked when response is received.
 *
 * @param response Http response struct, see {@link Http_Response}.
 * @param errCode Response error code.
 * @since 20
 */
typedef void (*Http_ResponseCallback)(struct Http_Response *response, uint32_t errCode);

/**
 * @brief Callback function that is invoked when a response body is received.
 *
 * @param data Response body.
 * @param length Length of response body.
 * @since 20
 */
typedef void (*Http_OnDataReceiveCallback)(const char *data, size_t length);

/**
 * @brief Callback function invoked during request/response data transmission.
 *
 * @param totalSize total size.
 * @param transferredSize transferred size.
 * @since 20
 */
typedef void (*Http_OnProgressCallback)(uint64_t totalSize, uint64_t transferredSize);

/**
 * @brief Callback called when header are received.
 *
 * @param headers Headers of the received requests, which points to the pointer of {@link Http_Headers}.
 * @since 20
 */
typedef void (*Http_OnHeaderReceiveCallback)(Http_Headers *headers);

/**
 * @brief Empty callback function for requested DataEnd or Canceled event callback.
 *
 * @since 20
 */
typedef void (*Http_OnVoidCallback)(void);

/**
 * @brief Defines the callback for various HTTP events.
 *
 * @since 20
 */
typedef struct Http_EventsHandler {
    /**
     * Callback invoked when a response body is received. For details, see {@link Http_OnDataReceiveCallback}.
     */
    Http_OnDataReceiveCallback onDataReceive;
    /**
     * Callback invoked when an upload is triggered. For details, see {@link Http_OnProgressCallback}.
     */
    Http_OnProgressCallback onUploadProgress;
    /**
     * Callback invoked when a download is triggered. For details, see {@link Http_OnProgressCallback}.
     */
    Http_OnProgressCallback onDownloadProgress;
    /**
     * Callback invoked when a header is received. For details, see {@link Http_OnHeaderReceiveCallback}.
     */
    Http_OnHeaderReceiveCallback onHeadersReceive;
    /**
     * Callback invoked when the transmission is complete. For details, see {@link Http_OnVoidCallback}.
     */
    Http_OnVoidCallback onDataEnd;
    /**
     * Callback invoked when the request is canceled. For details, see {@link Http_OnVoidCallback}.
     */
    Http_OnVoidCallback onCanceled;
} Http_EventsHandler;

#ifdef __cplusplus
}
#endif
#endif // NET_HTTP_TYPE_H

/** @} */

/** @} */