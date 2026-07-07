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
 * @brief 提供HTTP客户端模块的C接口。
 *
 * @since 20
 */

/**
 * @file net_http_type.h
 * @brief 定义HTTP请求模块的C接口需要的数据结构。
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
 * @brief HTTP请求最长目录路径长度。
 *
 * @since 20
 */
#define OHOS_HTTP_MAX_PATH_LEN 128

/**
 * @brief HTTP请求最长字符串长度。
 *
 * @since 20
 */
#define OHOS_HTTP_MAX_STR_LEN 256

/**
 * @brief HTTP请求最多DNS服务器数量。
 *
 * @since 20
 */
#define OHOS_HTTP_DNS_SERVER_NUM_MAX 3

/**
 * @brief 定义HTTP请求的错误码。
 *
 * @since 20
 */
typedef enum Http_ErrCode {
    /**
     * 请求成功。
     */
    OH_HTTP_RESULT_OK = 0,
    /** @brief 参数错误。
* */
    OH_HTTP_PARAMETER_ERROR = 401,
    /** @brief 权限校验失败。
* */
    OH_HTTP_PERMISSION_DENIED = 201,
    /** @brief 基础错误码偏移。
* */
    OH_HTTP_NETSTACK_E_BASE = 2300000,
    /** @brief 不支持的协议。
* */
    OH_HTTP_UNSUPPORTED_PROTOCOL = (OH_HTTP_NETSTACK_E_BASE + 1),
    /** @brief URL格式错误。
* */
    OH_HTTP_INVALID_URL = (OH_HTTP_NETSTACK_E_BASE + 3),
    /** @brief 代理服务器域名解析失败。
* */
    OH_HTTP_RESOLVE_PROXY_FAILED = (OH_HTTP_NETSTACK_E_BASE + 5),
    /** @brief 域名解析失败。
* */
    OH_HTTP_RESOLVE_HOST_FAILED = (OH_HTTP_NETSTACK_E_BASE + 6),
    /** @brief 无法连接到服务器。
* */
    OH_HTTP_CONNECT_SERVER_FAILED = (OH_HTTP_NETSTACK_E_BASE + 7),
    /** @brief 服务器返回非法数据。
* */
    OH_HTTP_INVALID_SERVER_RESPONSE = (OH_HTTP_NETSTACK_E_BASE + 8),
    /** @brief 拒绝访问远程资源。
* */
    OH_HTTP_ACCESS_REMOTE_DENIED = (OH_HTTP_NETSTACK_E_BASE + 9),
    /** @brief HTTP2框架层出现错误。
* */
    OH_HTTP_HTTP2_FRAMING_ERROR = (OH_HTTP_NETSTACK_E_BASE + 16),
    /** @brief 传输了部分文件。
* */
    OH_HTTP_TRANSFER_PARTIAL_FILE = (OH_HTTP_NETSTACK_E_BASE + 18),
    /** @brief 无法将接收到的数据写入磁盘或应用程序。
* */
    OH_HTTP_WRITE_DATA_FAILED = (OH_HTTP_NETSTACK_E_BASE + 23),
    /** @brief 上传失败。
* */
    OH_HTTP_UPLOAD_FAILED = (OH_HTTP_NETSTACK_E_BASE + 25),
    /** @brief 无法打开或读取文件或应用程序中的本地数据。
* */
    OH_HTTP_OPEN_LOCAL_DATA_FAILED = (OH_HTTP_NETSTACK_E_BASE + 26),
    /** @brief 内存不足。
* */
    OH_HTTP_OUT_OF_MEMORY = (OH_HTTP_NETSTACK_E_BASE + 27),
    /** @brief 操作超时。
* */
    OH_HTTP_OPERATION_TIMEOUT = (OH_HTTP_NETSTACK_E_BASE + 28),
    /** @brief 重定向次数已达到允许的最大值。
* */
    OH_HTTP_TOO_MANY_REDIRECTIONS = (OH_HTTP_NETSTACK_E_BASE + 47),
    /** @brief 服务器没有返回任何内容（没有标头或数据）。
* */
    OH_HTTP_SERVER_RETURNED_NOTHING = (OH_HTTP_NETSTACK_E_BASE + 52),
    /** @brief 发送数据失败。
* */
    OH_HTTP_SEND_DATA_FAILED = (OH_HTTP_NETSTACK_E_BASE + 55),
    /** @brief 接收数据失败。
* */
    OH_HTTP_RECEIVE_DATA_FAILED = (OH_HTTP_NETSTACK_E_BASE + 56),
    /** @brief 本地SSL证书错误。
* */
    OH_HTTP_SSL_CERTIFICATE_ERROR = (OH_HTTP_NETSTACK_E_BASE + 58),
    /** @brief 指定的加密套件不可用。
* */
    OH_HTTP_SSL_CIPHER_USED_ERROR = (OH_HTTP_NETSTACK_E_BASE + 59),
    /** @brief SSL对等证书或SSH远程密钥无效。
* */
    OH_HTTP_INVALID_SSL_PEER_CERT = (OH_HTTP_NETSTACK_E_BASE + 60),
    /** @brief HTTP编码格式无效。
* */
    OH_HTTP_INVALID_ENCODING_FORMAT = (OH_HTTP_NETSTACK_E_BASE + 61),
    /** @brief 超出最大文件大小。
* */
    OH_HTTP_FILE_TOO_LARGE = (OH_HTTP_NETSTACK_E_BASE + 63),
    /** @brief 远端磁盘满。
* */
    OH_HTTP_REMOTE_DISK_FULL = (OH_HTTP_NETSTACK_E_BASE + 70),
    /** @brief 远端文件已存在。
* */
    OH_HTTP_REMOTE_FILE_EXISTS = (OH_HTTP_NETSTACK_E_BASE + 73),
    /** @brief SSL CA证书不存在或无法访问。
* */
    OH_HTTP_SSL_CA_NOT_EXIST = (OH_HTTP_NETSTACK_E_BASE + 77),
    /** @brief 远端文件未找到。
* */
    OH_HTTP_REMOTE_FILE_NOT_FOUND = (OH_HTTP_NETSTACK_E_BASE + 78),
    /**
     * @brief 请求已被 HTTP 全局拦截器拦截。
     * @since 26.0.0
     */
    OH_HTTP_REQUEST_INTERCEPTED = (OH_HTTP_NETSTACK_E_BASE + 996),
    /** @brief 身份验证错误。
* */
    OH_HTTP_AUTHENTICATION_ERROR = (OH_HTTP_NETSTACK_E_BASE + 94),
    /** @brief 不允许访问该域。
* */
    OH_HTTP_ACCESS_DOMAIN_NOT_ALLOWED = (OH_HTTP_NETSTACK_E_BASE + 998),
    /** @brief 未知错误。
* */
    OH_HTTP_UNKNOWN_ERROR = (OH_HTTP_NETSTACK_E_BASE + 999)
} Http_ErrCode;

/**
 * @brief 定义HTTP响应码。
 *
 * @since 20
 */
typedef enum Http_ResponseCode {
    /** @brief 请求成功。
* */
    OH_HTTP_OK = 200,
    /** @brief 成功请求并创建新资源。
* */
    OH_HTTP_CREATED = 201,
    /** @brief 请求已被接受但尚未完全处理。
* */
    OH_HTTP_ACCEPTED = 202,
    /** @brief 请求成功。但是有未授权信息。
* */
    OH_HTTP_NON_AUTHORITATIVE_INFO = 203,
    /** @brief 服务器处理成功，但未返回内容。
* */
    OH_HTTP_NO_CONTENT = 204,
    /** @brief 重置内容。
* */
    OH_HTTP_RESET = 205,
    /** @brief 服务器成功处理了部分GET请求。
* */
    OH_HTTP_PARTIAL = 206,
    /** @brief 多种选择。
* */
    OH_HTTP_MULTI_CHOICE = 300,
    /**
     * @brief 请求的资源已永久移动到新的URI，返回信息将包含新的URI。浏览器将自动重定向到新的URI。
     *
     */
    OH_HTTP_MOVED_PERM = 301,
    /** @brief 临时重定向。
* */
    OH_HTTP_MOVED_TEMP = 302,
    /** @brief 查看其他地址。请求的资源已移动到新的URL，客户端应使用GET方法访问该URL。
* */
    OH_HTTP_SEE_OTHER = 303,
    /** @brief 请求的资源没有修改。
* */
    OH_HTTP_NOT_MODIFIED = 304,
    /** @brief 请求资源需要使用代理访问。
* */
    OH_HTTP_USE_PROXY = 305,
    /** @brief 服务器无法理解客户端请求的语法错误。
* */
    OH_HTTP_BAD_REQUEST = 400,
    /** @brief 请求用户身份验证。
* */
    OH_HTTP_UNAUTHORIZED = 401,
    /** @brief 保留以供将来使用。
* */
    OH_HTTP_PAYMENT_REQUIRED = 402,
    /** @brief 服务器理解来自请求客户端的请求，但拒绝执行。
* */
    OH_HTTP_FORBIDDEN = 403,
    /** @brief 服务器无法根据客户端的请求找到资源。
* */
    OH_HTTP_NOT_FOUND = 404,
    /** @brief 客户端请求中的方法被禁止。
* */
    OH_HTTP_BAD_METHOD = 405,
    /** @brief 服务器无法根据客户端请求的内容特征完成请求。
* */
    OH_HTTP_NOT_ACCEPTABLE = 406,
    /** @brief 请求验证代理人的身份。
* */
    OH_HTTP_PROXY_AUTH = 407,
    /** @brief 请求耗时太长，超时。
* */
    OH_HTTP_CLIENT_TIMEOUT = 408,
    /**
     * @brief 服务器在完成客户端的PUT请求时可能返回此代码，因为服务器在处理请求时发生冲突。
     *
     */
    OH_HTTP_CONFLICT = 409,
    /** @brief 客户端请求的资源不再存在。
* */
    OH_HTTP_GONE = 410,
    /** @brief 服务器无法处理客户端发送的不带Content Length的请求信息。
* */
    OH_HTTP_LENGTH_REQUIRED = 411,
    /** @brief 向客户端请求信息的前提条件不正确。
* */
    OH_HTTP_PRECON_FAILED = 412,
    /** @brief 请求被拒绝，因为请求的实体太大，服务器无法处理。
* */
    OH_HTTP_ENTITY_TOO_LARGE = 413,
    /** @brief 请求的URI超过了服务器能够解析的长度，服务器无法处理。
* */
    OH_HTTP_REQUEST_TOO_LONG = 414,
    /** @brief 服务器无法处理请求的格式。
* */
    OH_HTTP_UNSUPPORTED_TYPE = 415,
    /** @brief 请求的范围无法满足。
* */
    OH_HTTP_RANGE_NOT_MET = 416,
    /** @brief 内部服务器错误，无法完成请求。
* */
    OH_HTTP_INTERNAL_ERROR = 500,
    /** @brief 服务器不支持请求的功能，无法完成请求。
* */
    OH_HTTP_NOT_IMPLEMENTED = 501,
    /** @brief 充当网关或代理的服务器从远程服务器收到无效请求。
* */
    OH_HTTP_BAD_GATEWAY = 502,
    /** @brief 由于超载或系统维护，服务器暂时无法处理客户端请求。
* */
    OH_HTTP_UNAVAILABLE = 503,
    /** @brief 作为网关的服务器没有及时从远程服务器获取请求。
* */
    OH_HTTP_GATEWAY_TIMEOUT = 504,
    /** @brief 服务器请求的HTTP协议版本。
* */
    OH_HTTP_VERSION = 505
} Http_ResponseCode;

/**
 * @brief HTTP缓存结构体。
 *
 * @since 20
 */
typedef struct Http_Buffer {
    /**
     * 缓存区数据。
     */
    const char *buffer;
    /**
     * 缓存区长度。
     */
    uint32_t length;
} Http_Buffer;

/**
 * @brief 定义解析目标域名时限定的地址类型。
 *
 * @since 20
 */
typedef enum Http_AddressFamilyType {
    /**
     * 默认值，系统将自行选择目标域名的IPv4地址或IPv6地址。
     */
    HTTP_ADDRESS_FAMILY_DEFAULT = 0,
    /**
     * 系统仅解析目标域名的IPv4地址，忽略IPv6地址。
     */
    HTTP_ADDRESS_FAMILY_ONLY_V4 = 1,
    /**
     * 系统仅解析目标域名的IPv6地址，忽略IPv4地址。
     */
    HTTP_ADDRESS_FAMILY_ONLY_V6 = 2
} Http_AddressFamilyType;

/**
 * @brief HTTP请求GET方法。
 * 
 * @since 20
 */
#define NET_HTTP_METHOD_GET "GET"

/**
 * @brief HTTP请求HEAD方法。
 * 
 * @since 20
 */
#define NET_HTTPMETHOD_HEAD "HEAD"

/**
 * @brief HTTP请求OPTIONS方法。
 * 
 * @since 20
 */
#define NET_HTTPMETHOD_OPTIONS "OPTIONS"

/**
 * @brief HTTP请求TRACE方法。
 * 
 * @since 20
 */
#define NET_HTTPMETHOD_TRACE "TRACE"
/**
 * @brief HTTP请求DELETE方法。
 *
 * @since 20
 */
#define NET_HTTPMETHOD_DELETE "DELETE"

/**
 * @brief HTTP请求POST方法。
 * 
 * @since 20
 */
#define NET_HTTP_METHOD_POST "POST"

/**
 * @brief HTTP请求PUT方法。
 * 
 * @since 20
 */
#define NET_HTTP_METHOD_PUT "PUT"

/**
 * @brief HTTP请求CONNECT方法。
 * 
 * @since 20
 */
#define NET_HTTP_METHOD_PATCH "CONNECT"

/**
 * @brief HTTP协议版本号枚举定义。
 *
 * @since 20
 */
typedef enum Http_HttpProtocol {
    /**
     * 遵循curl的协议版本选择。
     */
    OH_HTTP_NONE = 0,
    /**
     * HTTP1.1版本。
     */
    OH_HTTP1_1,
    /**
     * HTTP2版本。
     */
    OH_HTTP2,
    /**
     * HTTP3版本。
     */
    OH_HTTP3
} Http_HttpProtocol;

/**
 * @brief 证书类型枚举。
 *
 * @since 20
 */
typedef enum Http_CertType {
    /**
     * PEM证书类型。
     */
    OH_HTTP_PEM = 0,
    /**
     * DER证书类型。
     */
    OH_HTTP_DER = 1,
    /**
     * P12证书类型。
     */
    OH_HTTP_P12 = 2
} Http_CertType;

/**
 * @brief HTTP请求或者是响应中的标头。
 *
 * @since 20
 */
typedef struct Http_Headers Http_Headers;

/**
 * @brief 请求或者响应的标头映射的值类型。
 *
 * @since 20
 */
typedef struct Http_HeaderValue {
    /**
     * 标头键值对的值。
     */
    char *value;
    /**
     * 链式存储。指向下一个Http_HeaderValue。
     */
    struct Http_HeaderValue *next;
} Http_HeaderValue;

/**
 * @brief 请求或者响应的标头的所有键值对。
 *
 * @since 20
 */
typedef struct Http_HeaderEntry {
    /**
     * 请求或者响应的标头中的键。
     */
    char *key;
    /**
     * Value of the key in the request or response header. For details, see {@link Http_HeaderValue}.
     */
    Http_HeaderValue *value;
    /**
     * 链式存储。指向下一个Http_HeaderEntry。
     */
    struct Http_HeaderEntry *next;
} Http_HeaderEntry;

/**
 * @brief 发送到服务端的客户端证书配置，服务端将通过客户端证书校验客户端身份。
 *
 * @since 20
 */
typedef struct Http_ClientCert {
    /**
     * 证书路径。
     */
    char *certPath;
    /**
     * Certificate type. The default value is **PEM**. For details, see {@link Http_CertType}.
     */
    Http_CertType type;
    /**
     * 证书密钥的路径。
     */
    char *keyPath;
    /**
     * 证书密钥的密码。
     */
    char *keyPassword;
} Http_ClientCert;

/**
 * @brief 代理配置类型枚举定义。
 *
 * @since 20
 */
typedef enum Http_ProxyType {
    /**
     * 不使用代理。
     */
    HTTP_PROXY_NOT_USE,
    /**
     * 使用系统代理。
     */
    HTTP_PROXY_SYSTEM,
    /**
     * 使用用户自定义代理。
     */
    HTTP_PROXY_CUSTOM
} Http_ProxyType;

/**
 * @brief 用户自定义代理配置。
 *
 * @since 20
 */
typedef struct Http_CustomProxy {
    /**
     * 代理服务器主机名， 如果没有显式设置端口，端口将默认为1080。
     */
    const char *host;
    int32_t port;
    const char *exclusionLists;
} Http_CustomProxy;

/**
 * @brief 代理配置结构体。
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
 * @brief HTTP响应时间信息，会在{@link Http_Response}中收集。
 *
 * @since 20
 */
typedef struct Http_PerformanceTiming {
    /**
     * 从request请求到DNS解析完成的耗时，包含域名解析，TCP连接等流程耗时。
     */
    double dnsTiming;
    /**
     * 从request请求到TCP连接完成的耗时。
     */
    double tcpTiming;
    /**
     * 从request请求到TLS连接完成的耗时。
     */
    double tlsTiming;
    /**
     * 从request请求到开始发送第一个字节的耗时。
     */
    double firstSendTiming;
    /**
     * 从request请求到接收到第一个字节的耗时。
     */
    double firstReceiveTiming;
    /**
     * 从request请求到完成请求的耗时。
     */
    double totalFinishTiming;
    /**
     * 从request请求到完成所有重定向步骤的耗时。
     */
    double redirectTiming;
} Http_PerformanceTiming;

/**
 * @brief 定义HTTP请求配置的结构体。
 *
 * @since 20
 */
typedef struct Http_RequestOptions {
    /**
     * HTTP请求方法。
     */
    const char *method;
    /**
     * HTTP请求优先级。
     */
    uint32_t priority;
    /**
     * Pointer to the HTTP request header. For details, see {@link Http_Headers}.
     */
    Http_Headers *headers;
    /**
     * 读取超时时间。
     */
    uint32_t readTimeout;
    /**
     * 连接超时时间。
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
     * 证书路径，如果设置了此参数，系统将使用用户指定路径的CA证书（开发者需保证该路径下CA证书的可访问性），否则将使用系统预设CA证书。
     */
    const char *caPath;
    /**
     * 用于设置下载起始位置，该参数只能用于GET方法，不要用于其他。
     */
    int64_t resumeFrom;
    /**
     * 用于设置下载结束位置，该参数只能用于GET方法，不要用于其他。
     */
    int64_t resumeTo;
    /**
     * Pointer to the client certificate configuration. For details, see {@link Http_ClientCert}.
     */
    Http_ClientCert *clientCert;
    /**
     * 设置使用HTTPS协议的服务器进行DNS解析。
     */
    const char *dnsOverHttps;
    /**
     * IP address family. For details, see {@link Http_AddressFamilyType}.
     */
    Http_AddressFamilyType addressFamily;
} Http_RequestOptions;

/**
 * @brief 定义HTTP响应的结构体。
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
     * HTTP响应Cookies。
     */
    char *cookies;
    /**
     * Pointer to the HTTP response timing. For details, see {@link Http_PerformanceTiming}.
     */
    Http_PerformanceTiming *performanceTiming;
    /**
     * @brief 销毁HTTP响应的回调函数
     *
     * @param response 要销毁的HTTP响应，指向Http_Response的指针。
     * @since 20
     */
    void (*destroyResponse)(struct Http_Response **response);
} Http_Response;

/**
 * @brief HTTP请求结构体。
 *
 * @since 20
 */
typedef struct Http_Request {
    /**
     * HTTP请求的ID。
     */
    uint32_t requestId;
    /**
     * HTTP请求的URL。
     */
    char *url;
    /**
     * Pointer to the HTTP request configuration. For details, see {@link Http_RequestOptions}.
     */
    Http_RequestOptions *options;
} Http_Request;

/**
 * @brief 接收到HTTP响应的回调函数。
 *
 * @param response HTTP响应结构体，指向Http_Response的指针，参考{@link Http_Response}。
 * @param errCode 响应码。
 * @since 20
 */
typedef void (*Http_ResponseCallback)(struct Http_Response *response, uint32_t errCode);

/**
 * @brief 接收到数据的回调。
 *
 * @param data 响应体。
 * @param length 响应体的长度。
 * @since 20
 */
typedef void (*Http_OnDataReceiveCallback)(const char *data, size_t length);

/**
 * @brief 请求/响应数据传输过程中调用的回调函数。
 *
 * @param totalSize 数据总大小。
 * @param transferredSize 已传输的数据大小。
 * @since 20
 */
typedef void (*Http_OnProgressCallback)(uint64_t totalSize, uint64_t transferredSize);

/**
 * @brief 收到HTTP响应头的回调函数。
 *
 * @param headers 接收到的请求头，指向Http_Headers的指针，参考{@link Http_Headers}。
 * @since 20
 */
typedef void (*Http_OnHeaderReceiveCallback)(Http_Headers *headers);

/**
 * @brief 请求的DataEnd或Cancel事件回调的回调函数。
 *
 * @since 20
 */
typedef void (*Http_OnVoidCallback)(void);

/**
 * @brief 监听不同HTTP事件的回调函数。
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