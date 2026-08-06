/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup Web
 * @{
 *
 * @brief Provides APIs to intercept the request from ArkWeb.
 * @since 12
 */
/**
 * @file arkweb_scheme_handler.h
 *
 * @brief arkweb_scheme_handler.h是ArkWeb中用于拦截和自定义网络请求的完整C API头文件。该模块定义了注册自定义Scheme拦截器的ArkWeb_SchemeHandler、
 * 发送自定义响应的ArkWeb_ResourceHandler、构建HTTP响应的ArkWeb_Response、检查请求详情的ArkWeb_ResourceRequest，
 * 以及用于读取上传数据的ArkWeb_HttpBodyStream和访问请求头的ArkWeb_RequestHeaderList。该API配合ArkWeb_NativeAPIVariantKind系统使用，
 * 通过OH_ArkWeb_SetSchemeHandler或OH_ArkWebServiceWorker_SetSchemeHandler注册。开发者可以实现自定义协议的资源加载和响应，适用于本地资源替换、数据加密传输、离线缓存等场景，
 * 通过拦截和自定义网络请求，帮助开发者解决标准协议无法满足的特殊业务需求，提升应用的安全性和数据控制能力，优化网络资源加载效率。
 *
 * @kit ArkWeb
 * @library libohweb.so
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
#ifndef ARKWEB_SCHEME_HANDLER_H
#define ARKWEB_SCHEME_HANDLER_H

#include <stdbool.h>
#include "stdint.h"

#include "arkweb_error_code.h"
#include "arkweb_net_error_list.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief custom scheme的配置信息。
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef enum ArkWeb_CustomSchemeOption {
    OH_ARKWEB_SCHEME_OPTION_NONE = 0,

    /**
     * 如果设置了ARKWEB_SCHEME_OPTION_STANDARD，那么该scheme将被视为标准scheme来处理。
     */
    ARKWEB_SCHEME_OPTION_STANDARD = 1 << 0,

    /**
     * 如果设置了ARKWEB_SCHEME_OPTION_LOCAL，则将使用与“file” URL相同的安全规则来处理该scheme。
     */
    ARKWEB_SCHEME_OPTION_LOCAL = 1 << 1,

    /**
     * 如果设置了ARKWEB_SCHEME_OPTION_DISPLAY_ISOLATED，则该scheme的请求只能由使用相同scheme加载的页面中发起。
     */
    ARKWEB_SCHEME_OPTION_DISPLAY_ISOLATED = 1 << 2,

    /**
     * 如果设置了ARKWEB_SCHEME_OPTION_SECURE，则将使用与“https” URL相同的安全规则来处理该scheme。
     */
    ARKWEB_SCHEME_OPTION_SECURE = 1 << 3,

    /**
     * 如果设置了ARKWEB_SCHEME_OPTION_CORS_ENABLED，则该scheme可以发送CORS请求。在大多数情况下，当设置了ARKWEB_SCHEME_OPTION_STANDARD时，应该设置此值。
     */
    ARKWEB_SCHEME_OPTION_CORS_ENABLED = 1 << 4,

    /**
     * 如果设置了ARKWEB_SCHEME_OPTION_CSP_BYPASSING，则该scheme可以绕过内容安全策略（CSP）检查。
     */
    ARKWEB_SCHEME_OPTION_CSP_BYPASSING = 1 << 5,

    /**
     * 如果设置了ARKWEB_SCHEME_OPTION_FETCH_ENABLED，则可以发起该scheme的FETCH API请求。
     */
    ARKWEB_SCHEME_OPTION_FETCH_ENABLED = 1 << 6,

    /**
     * 如果设置了ARKWEB_SCHEME_OPTION_CODE_CACHE_ENABLED，则该scheme的js资源支持生成code cache。
     */
    ARKWEB_SCHEME_OPTION_CODE_CACHE_ENABLED = 1 << 7
} ArkWeb_CustomSchemeOption;

/**
 * @brief 请求的资源类型。这些常量与Chromium中的ResourceType的对应项相匹配，不应重新编号。
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef enum ArkWeb_ResourceType {
    /**
     * 顶层页面。
     */
    MAIN_FRAME = 0,

    /**
     * Frame或Iframe。
     */
    SUB_FRAME = 1,

    /**
     * CSS样式表。
     */
    STYLE_SHEET = 2,

    /**
     * 外部脚本。
     */
    SCRIPT = 3,

    /**
     * 图片（jpg/gif/png/以及其他）。
     */
    IMAGE = 4,

    /**
     * 字体。
     */
    FONT_RESOURCE = 5,

    /**
     * 其他子资源。如果实际类型未知，则是默认类型。
     */
    SUB_RESOURCE = 6,

    /**
     * 插件的Object（或embed）标签，或者插件请求的资源。
     */
    OBJECT = 7,

    /**
     * 媒体资源。
     */
    MEDIA = 8,

    /**
     * 专用工作线程的主资源。
     */
    WORKER = 9,

    /**
     * 共享工作线程的主资源。
     */
    SHARED_WORKER = 10,

    /**
     * 明确的预取请求。
     */
    PREFETCH = 11,

    /**
     * 网站图标。
     */
    FAVICON = 12,

    /** XMLHttpRequest. */
    XHR = 13,

    /**
     * /sendBeacon的Ping请求。
     */
    PING = 14,

    /**
     * service worker的主资源。
     */
    SERVICE_WORKER = 15,

    /**
     * 内容安全策略违规报告。
     */
    CSP_REPORT = 16,

    /**
     * 插件请求的资源。
     */
    PLUGIN_RESOURCE = 17,

    /**
     * 触发service worker预热的主frame跳转请求。
     */
    NAVIGATION_PRELOAD_MAIN_FRAME = 19,

    /**
     * 触发service worker预热的子frame跳转请求。
     */
    NAVIGATION_PRELOAD_SUB_FRAME = 20
} ArkWeb_ResourceType;

/**
 * @brief ArkWeb_SchemeHandler是用于注册自定义Scheme（协议）拦截器的结构体，定义了onRequestStart请求开始回调和onRequestStop请求停止回调两个函数指针。通过该结构体，
 * 开发者可以拦截Web组件中指定scheme的网络请求，适用于资源本地化、数据模拟、请求过滤、协议扩展等场景：在onRequestStart中判断是否拦截并返回自定义数据，在onRequestStop中执行资源清理，
 * onRequestStart和onRequestStop会按请求生命周期顺序依次调用。该结构体配合ArkWeb_ResourceHandler和ArkWeb_Response实现完整的请求拦截与自定义响应流程，调用顺序为：
 * ArkWeb_SchemeHandler拦截请求 → ArkWeb_ResourceHandler处理资源 → ArkWeb_Response返回响应。
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef struct ArkWeb_SchemeHandler_ ArkWeb_SchemeHandler;

/**
 * @brief ArkWeb_ResourceHandler是用于处理被拦截的Scheme请求的资源处理器结构体。在ArkWeb_SchemeHandler拦截到指定scheme的请求后，
 * 通过该结构体可以向Web组件返回自定义的响应数据，包括响应状态码、响应头、响应体等。该结构体在onRequestStart回调中作为参数传入，开发者通过它实现对被拦截请求的完全自定义响应。
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef struct ArkWeb_ResourceHandler_ ArkWeb_ResourceHandler;

/**
 * @brief ArkWeb_Response是用于构建自定义HTTP响应的结构体，定义了响应状态码、响应头、响应体等核心字段。该结构体配合ArkWeb_ResourceHandler使用，
 * 在Scheme请求拦截场景中为被拦截的请求提供完整的HTTP响应数据，实现自定义的资源返回能力。
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef struct ArkWeb_Response_ ArkWeb_Response;

/**
 * @brief ArkWeb_ResourceRequest是被拦截的Scheme请求的详细信息结构体，包含请求的URL、HTTP方法、请求头等元数据。
 * 该结构体在ArkWeb_SchemeHandler的onRequestStart回调中作为参数传入，适用于自定义协议处理、资源拦截等场景，帮助开发者实现跨域请求控制、本地资源映射等功能，从而增强安全性和性能。
 * 开发者通过它获取被拦截请求的完整信息，据此决定是否拦截以及如何构建自定义响应。
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef struct ArkWeb_ResourceRequest_ ArkWeb_ResourceRequest;

/**
 * @brief ArkWeb_RequestHeaderList是HTTP请求头列表结构体，用于在ArkWeb NDK中表示和管理HTTP请求头的键值对集合。该结构体包含请求头数组（headers）和数组长度（headerCount），
 * headers为ArkWeb_RequestHeader指针数组，headerCount表示数组元素个数。该结构体配合ArkWeb_ResourceRequest等结构体使用，提供对Web组件网络请求头的读取和设置能力。使用场景：
 * 在自定义协议处理器中处理HTTP请求头、在网络请求拦截器中修改请求头、在API鉴权场景中添加认证头、在缓存控制和内容协商等场景中配置请求头。
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef struct ArkWeb_RequestHeaderList_ ArkWeb_RequestHeaderList;

/**
 * @brief ArkWeb_HttpBodyStream是HTTP请求体流结构体，用于在自定义Scheme请求拦截场景中获取HTTP请求的body数据。当拦截到的POST等包含请求体的HTTP请求时，
 * 可通过该结构体读取请求体的原始字节流数据。该结构体通常与ArkWeb_ResourceRequest配合使用，在ArkWeb_SchemeHandler的回调中获取完整的请求信息。
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef struct ArkWeb_HttpBodyStream_ ArkWeb_HttpBodyStream;

/**
 * @brief OH_ArkWebResourceHandler_DidFailWithErrorInfo的错误信息；
 *
 * @since 26.1.0
 */
typedef struct ArkWeb_ErrorInfo_ ArkWeb_ErrorInfo;

/**
 * @brief 请求开始的回调，这将在IO线程上被调用。用于在请求开始时拦截和处理指定scheme的网络请求，开发者可通过此回调实现自定义协议处理、本地资源替换、数据加密传输等功能。
 *
 * @param schemeHandler ArkWeb_SchemeHandler。
 * @param resourceRequest 通过该对象获取请求的信息。
 * @param resourceHandler 请求的ArkWeb_ResourceHandler。如果intercept设置为false，则不应使用它。
 * @param intercept 如果为true，则会拦截请求；如果为false，则不会拦截。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef void (*ArkWeb_OnRequestStart)(const ArkWeb_SchemeHandler* schemeHandler,
                                      ArkWeb_ResourceRequest* resourceRequest,
                                      const ArkWeb_ResourceHandler* resourceHandler,
                                      bool* intercept);

/**
 * @brief 请求完成时的回调函数。这将在IO线程上被调用。用于在请求完成时进行资源清理、状态更新或日志记录等操作。
 * <br>应该使用OH_ArkWebResourceRequest_Destroy销毁resourceRequest，
 * 并使用OH_ArkWebResourceHandler_Destroy销毁在ArkWeb_OnRequestStart中接收到的ArkWeb_ResourceHandler。
 *
 * @param schemeHandler ArkWeb_SchemeHandler。
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @since 12
 */
typedef void (*ArkWeb_OnRequestStop)(const ArkWeb_SchemeHandler* schemeHandler,
                                     const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief 当OH_ArkWebHttpBodyStream_Read读取操作完成时的回调函数。该回调函数会在ArkWeb工作线程中运行。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @param buffer 接收数据的buffer。
 * @param bytesRead 读取的字节数。如果bytesRead大于0，则表示buffer已填充了bytesRead字节的数据。开发者可以从buffer中读取数据，
 *     如果OH_ArkWebHttpBodyStream_IsEof的返回值为false，则开发者可以继续读取剩余的数据。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef void (*ArkWeb_HttpBodyStreamReadCallback)(const ArkWeb_HttpBodyStream* httpBodyStream,
                                                  uint8_t* buffer,
                                                  int bytesRead);

/**
 * @brief 当OH_ArkWebHttpBodyStream_AsyncRead读取操作完成时的回调函数。该回调函数会在ArkWeb工作线程中运行。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @param buffer 接收数据的缓冲区。
 * @param bytesRead 标识异步读取操作执行结果的字节计数值。如果bytesRead大于0，则表示buffer已填充了bytesRead字节的数据。开发者可以从buffer中读取数据，
 *     如果OH_ArkWebHttpBodyStream_IsEof的返回值为false，则开发者可以继续读取剩余的数据。
 * @since 20
 */
typedef void (*ArkWeb_HttpBodyStreamAsyncReadCallback)(const ArkWeb_HttpBodyStream *httpBodyStream,
                                                       uint8_t *buffer,
                                                       int bytesRead);

/**
 * @brief ArkWeb_HttpBodyStream初始化操作完成时回调函数。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @param result 成功时返回ARKWEB_NET_OK，否则请参考{@link arkweb_net_error_list.h}。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef void (*ArkWeb_HttpBodyStreamInitCallback)(const ArkWeb_HttpBodyStream* httpBodyStream, ArkWeb_NetError result);

/**
 * @brief 销毁ArkWeb_RequestHeaderList对象。
 *
 * @param requestHeaderList 将被销毁的ArkWeb_RequestHeaderList。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebRequestHeaderList_Destroy(ArkWeb_RequestHeaderList* requestHeaderList);

/**
 * @brief 获取请求头列表的大小。
 *
 * @param requestHeaderList 请求头的列表。
 * @return 请求头的大小。如果requestHeaderList无效，则为-1。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebRequestHeaderList_GetSize(const ArkWeb_RequestHeaderList* requestHeaderList);

/**
 * @brief 获取指定的请求头。
 *
 * @param requestHeaderList 请求头列表。
 * @param index 请求头的索引。取值范围为[0, size-1]，其中size是请求头列表的大小。超出范围时行为未定义。
 * @param key 请求头的键（key）。调用者必须使用OH_ArkWeb_ReleaseString函数来释放这个字符串。
 * @param value 请求头的值（value）。调用者必须使用OH_ArkWeb_ReleaseString函数来释放这个字符串。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebRequestHeaderList_GetHeader(const ArkWeb_RequestHeaderList* requestHeaderList,
                                          int32_t index,
                                          char** key,
                                          char** value);

/**
 * @brief 将一个用户数据设置到ArkWeb_ResourceRequest对象中。用于在不同请求回调之间传递上下文信息或存储请求关联的状态，后续可通过
 * {@link OH_ArkWebResourceRequest_GetUserData()}获取。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @param userData 将要设置的用户数据。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceRequest_SetUserData(ArkWeb_ResourceRequest* resourceRequest, void* userData);

/**
 * @brief 从ArkWeb_ResourceRequest获取用户数据。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @return 指向用户数据的指针。该指针由开发者通过{@link OH_ArkWebResourceRequest_SetUserData}设置，可用于在回调中传递自定义上下文信息。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void* OH_ArkWebResourceRequest_GetUserData(const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief 获取请求的method。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @param method HTTP请求方法。此函数将为method字符串分配内存，调用者必须使用OH_ArkWeb_ReleaseString释放字符串。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_GetMethod(const ArkWeb_ResourceRequest* resourceRequest, char** method);

/**
 * @brief 获取请求的url。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @param url 请求的URL。此函数将为URL字符串分配内存，调用者必须通过OH_ArkWeb_ReleaseString释放该字符串。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_GetUrl(const ArkWeb_ResourceRequest* resourceRequest, char** url);

/**
 * @brief 创建一个ArkWeb_HttpBodyStream，用于读取请求的上传数据。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @param httpBodyStream 请求的上传数据。此函数将为httpBodyStream分配内存，
 *     调用者必须使用OH_ArkWebResourceRequest_DestroyHttpBodyStream释放httpBodyStream。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_GetHttpBodyStream(const ArkWeb_ResourceRequest* resourceRequest,
                                                ArkWeb_HttpBodyStream** httpBodyStream);

/**
 * @brief 销毁ArkWeb_HttpBodyStream对象。
 *
 * @param httpBodyStream 待销毁的httpBodyStream。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_DestroyHttpBodyStream(ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief 获取请求的资源类型。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @return 请求的资源类型。如果resourceRequest无效，则为-1，表示请求对象为空或已失效。其他值参考{@link ArkWeb_ResourceType}。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceRequest_GetResourceType(const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief 获取触发此请求的Frame的URL。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @param frameUrl 触发此请求的Frame的URL。此函数将为URL字符串分配内存，并且调用者必须通过OH_ArkWeb_ReleaseString来释放该字符串。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_GetFrameUrl(const ArkWeb_ResourceRequest* resourceRequest, char** frameUrl);

/**
 * @brief 将一个用户数据设置到ArkWeb_HttpBodyStream对象中。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @param userData 要设置的用户数据。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebHttpBodyStream_SetUserData(ArkWeb_HttpBodyStream* httpBodyStream, void* userData);

/**
 * @brief 从ArkWeb_HttpBodyStream获取用户数据。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @return 指向用户数据的指针。该指针由开发者通过OH_ArkWebHttpBodyStream_SetUserData设置，可用于在回调中传递自定义上下文信息。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void* OH_ArkWebHttpBodyStream_GetUserData(const ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief 为OH_ArkWebHttpBodyStream_Read设置回调函数。OH_ArkWebHttpBodyStream_Read的结果将通过readCallback通知给调用者。
 * <br>该回调函数将在与OH_ArkWebHttpBodyStream_Read相同的线程中运行。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @param readCallback OH_ArkWebHttpBodyStream_Read的回调函数。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebHttpBodyStream_SetReadCallback(ArkWeb_HttpBodyStream* httpBodyStream,
                                                ArkWeb_HttpBodyStreamReadCallback readCallback);

/**
 * @brief 为OH_ArkWebHttpBodyStream_AsyncRead设置回调函数。OH_ArkWebHttpBodyStream_AsyncRead的结果将通过readCallback通知给开发者。
 * <br>该回调函数会在ArkWeb工作线程中运行。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @param readCallback OH_ArkWebHttpBodyStream_AsyncRead的回调函数。
 * @return 返回0，表示成功；返回17100101，表示参数无效。
 * @since 20
 */
int32_t OH_ArkWebHttpBodyStream_SetAsyncReadCallback(ArkWeb_HttpBodyStream* httpBodyStream,
                                                     ArkWeb_HttpBodyStreamAsyncReadCallback readCallback);

/**
 * @brief 初始化ArkWeb_HttpBodyStream。该函数负责建立httpBodyStream的内部数据结构和连接，为后续的读取操作做准备。初始化过程中会分配必要的资源、建立与工作线程的通信机制。在调用任何其他函数之前，
 * 必须调用此函数，否则其他操作将无法正常执行。该接口需要在IO线程调用，以确保线程安全和正确的初始化顺序。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @param initCallback 初始化的回调函数。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebHttpBodyStream_Init(ArkWeb_HttpBodyStream* httpBodyStream,
                                     ArkWeb_HttpBodyStreamInitCallback initCallback);

/**
 * @brief 将请求的上传数据读取到buffer。该函数采用异步读取机制，将读取任务提交到工作线程执行，通过回调函数返回读取结果。buffer的大小必须大于或等于bufLen，以确保能够容纳读取的数据。
 * 我们将从工作线程读取数据到buffer，因此在回调函数返回之前，不应在其他线程中使用buffer，以避免并发问题。读取操作完成后，将通过之前设置的回调函数通知调用者，并返回实际读取的字节数。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @param buffer 接收数据的buffer。buffer的大小必须大于bufLen。
 * @param bufLen 要读取的字节数。取值范围必须为正整数，传入负数时行为未定义。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebHttpBodyStream_Read(const ArkWeb_HttpBodyStream* httpBodyStream, uint8_t* buffer, int bufLen);

/**
 * @brief 将请求的上传数据读取至buffer，buffer的大小必须超过bufLen。数据将由工作线程读取至buffer，因此在回调函数返回前，不应在其他线程中使用缓冲区，以避免并发问题。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @param buffer 接收数据的缓冲区。
 * @param bufLen 要读取的字节数。
 * @since 20
 */
void OH_ArkWebHttpBodyStream_AsyncRead(const ArkWeb_HttpBodyStream* httpBodyStream, uint8_t* buffer, int bufLen);

/**
 * @brief 获取httpBodyStream的大小。当数据以分块的形式传输或httpBodyStream无效时，始终返回0。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @return httpBodyStream的大小。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
uint64_t OH_ArkWebHttpBodyStream_GetSize(const ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief 获取httpBodyStream当前的读取位置。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @return httpBodyStream当前的读取位置。如果httpBodyStream无效，则返回0。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
uint64_t OH_ArkWebHttpBodyStream_GetPosition(const ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief 获取httpBodyStream是否采用分块传输。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @return 如果采用分块传输则返回true；否则返回false。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWebHttpBodyStream_IsChunked(const ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief 如果httpBodyStream中的所有数据都已被读取，则返回true。对于分块传输类型的httpBodyStream，在第一次读取尝试之前返回false。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @return 如果所有数据都已被读取则返回true；否则返回false。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWebHttpBodyStream_IsEof(const ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief 如果httpBodyStream中的上传数据完全在内存中，并且所有读取请求都将同步成功，则返回true。对于分块传输类型的数据，预期返回false。
 *
 * @param httpBodyStream ArkWeb_HttpBodyStream。
 * @return 如果上传数据完全在内存中则返回true；否则返回false。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWebHttpBodyStream_IsInMemory(const ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief 销毁ArkWeb_ResourceRequest对象。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceRequest_Destroy(const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief 获取请求的Referrer。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @param referrer 请求的Referrer。此函数将为referrer字符串分配内存，调用者必须使用OH_ArkWeb_ReleaseString释放该字符串。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_GetReferrer(const ArkWeb_ResourceRequest* resourceRequest, char** referrer);

/**
 * @brief 获取请求的请求头列表ArkWeb_RequestHeaderList。此函数将为requestHeaderList分配内存，
 * 调用者必须使用OH_ArkWebRequestHeaderList_Destroy释放requestHeaderList。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @param requestHeaderList 请求的请求头列表。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_GetRequestHeaders(const ArkWeb_ResourceRequest* resourceRequest,
                                                ArkWeb_RequestHeaderList** requestHeaderList);

/**
 * @brief 判断这是否是一个重定向请求。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @return 如果这是一个重定向，则返回true；如果不是重定向，则返回false。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWebResourceRequest_IsRedirect(const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief 判断这是否是主框架文档资源的请求。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @return 如果这是来自主框架，则返回true；如果不是来自主框架，则返回false。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWebResourceRequest_IsMainFrame(const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief 判断这是否是一个由用户手势触发的请求。
 *
 * @param resourceRequest ArkWeb_ResourceRequest。
 * @return 如果这是由用户手势触发的，则返回true；如果不是由用户手势触发的，则返回false。
 * @since 12
 */
bool OH_ArkWebResourceRequest_HasGesture(const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief 将custom scheme注册到ArkWeb。对于内置的HTTP、HTTPS、FILE、FTP、ABOUT和DATA协议，不应调用此函数。此函数应在主线程上调用并且需要在内核初始化之前调用。
 *
 * @param scheme 待注册的scheme，需符合RFC 3986规范。
 * @param option scheme的配置（行为），取值参考{@link ArkWeb_CustomSchemeOption}枚举。
 * @return 如果返回0，表示成功；返回17100100，表示未知错误，请检查调用时机和参数配置；返回17100101，表示参数无效；返回17100102，表示注册scheme的配置失败，应该在创建ArkWeb之前注册。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWeb_RegisterCustomSchemes(const char* scheme, int32_t option);

/**
 * @brief 为指定scheme设置一个ArkWeb_SchemeHandler以拦截ServiceWorker触发的该scheme类型的请求。应该在创建BrowserContext之后设置SchemeHandler。
 * <br>可以使用WebviewController.initializeWebEngine来初始化BrowserContext而无需创建ArkWeb。
 *
 * @param scheme 需要被拦截的scheme，需符合RFC 3986规范。
 * @param schemeHandler 该scheme的拦截器ArkWeb_SchemeHandler。只有通过ServiceWorker触发的请求才会通过这个schemeHandler进行通知。
 * @return 如果为指定scheme设置SchemeHandler成功，则返回true，否则返回false。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWebServiceWorker_SetSchemeHandler(const char* scheme, ArkWeb_SchemeHandler* schemeHandler);

/**
 * @brief 为指定scheme设置一个ArkWeb_SchemeHandler以拦截该scheme类型的请求。应该在创建BrowserContext之后设置SchemeHandler。
 * <br>可以使用WebviewController.initializeWebEngine来初始化BrowserContext而无需创建ArkWeb。
 *
 * @param scheme 需要被拦截的scheme。
 * @param webTag Web组件的标签名称，用于标识某个唯一组件，由开发者来保证名称唯一性。建议长度不超过256字符。
 * @param schemeHandler 该scheme的拦截器ArkWeb_SchemeHandler。只有从指定web触发的请求才会通过这个schemeHandler进行通知。
 * @return 如果为指定scheme设置SchemeHandler成功，则返回true，否则返回false。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWeb_SetSchemeHandler(const char* scheme, const char* webTag, ArkWeb_SchemeHandler* schemeHandler);

/**
 * @brief 清除为ServiceWorker注册的SchemeHandler。
 *
 * @return 如果返回0，表示成功。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebServiceWorker_ClearSchemeHandlers();

/**
 * @brief 清除为指定web注册的SchemeHandler。
 *
 * @param webTag Web组件的标签名称，用于标识某个唯一组件，由开发者来保证名称唯一性。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWeb_ClearSchemeHandlers(const char* webTag);

/**
 * @brief 创建一个ArkWeb_SchemeHandler对象。
 *
 * @param schemeHandler 返回创建的ArkWeb_SchemeHandler。在不需要时使用{@link OH_ArkWeb_DestroySchemeHandler}销毁它。
 * @since 12
 */
void OH_ArkWeb_CreateSchemeHandler(ArkWeb_SchemeHandler** schemeHandler);

/**
 * @brief 销毁一个ArkWeb_SchemeHandler对象。
 *
 * @param schemeHandler 待销毁的ArkWeb_SchemeHandler。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWeb_DestroySchemeHandler(ArkWeb_SchemeHandler* schemeHandler);

/**
 * @brief 将一个用户数据设置到ArkWeb_SchemeHandler对象中。
 *
 * @param schemeHandler ArkWeb_SchemeHandler。
 * @param userData 要设置的用户数据。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebSchemeHandler_SetUserData(ArkWeb_SchemeHandler* schemeHandler, void* userData);

/**
 * @brief 从ArkWeb_SchemeHandler获取用户数据。
 *
 * @param schemeHandler ArkWeb_SchemeHandler。
 * @return 指向用户数据的指针。该指针由开发者通过OH_ArkWebSchemeHandler_SetUserData设置，可用于在回调中传递自定义上下文信息。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void* OH_ArkWebSchemeHandler_GetUserData(const ArkWeb_SchemeHandler* schemeHandler);

/**
 * @brief 为SchemeHandler设置OnRequestStart回调。
 *
 * @param schemeHandler 该scheme的SchemeHandler。
 * @param onRequestStart OnRequestStart回调函数。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebSchemeHandler_SetOnRequestStart(ArkWeb_SchemeHandler* schemeHandler,
                                                 ArkWeb_OnRequestStart onRequestStart);

/**
 * @brief 为SchemeHandler设置OnRequestStop回调。
 *
 * @param schemeHandler 该scheme的SchemeHandler。
 * @param onRequestStop OnRequestStop回调函数。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebSchemeHandler_SetOnRequestStop(ArkWeb_SchemeHandler* schemeHandler,
                                                ArkWeb_OnRequestStop onRequestStop);

/**
 * @brief 为被拦截的请求创建一个ArkWeb_Response对象。
 *
 * @param response 返回创建的ArkWeb_Response。在不需要时使用OH_ArkWeb_DestroyResponse进行销毁。
 * @since 12
 */
void OH_ArkWeb_CreateResponse(ArkWeb_Response** response);

/**
 * @brief 销毁一个ArkWeb_Response对象。
 *
 * @param response 待销毁的ArkWeb_Response。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWeb_DestroyResponse(ArkWeb_Response* response);

/**
 * @brief 设置经过重定向或由于HSTS而改变后的解析URL，设置后会触发跳转。用于在自定义响应中实现URL重定向，如URL规范化、域名重定向、HTTP到HTTPS升级等场景。
 *
 * @param response ArkWeb_Response。
 * @param url 解析后的URL。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResponse_SetUrl(ArkWeb_Response* response, const char* url);

/**
 * @brief 获取经过重定向或由于HSTS而更改后的解析URL。
 *
 * @param response ArkWeb_Response。
 * @param url 解析后的URL。此函数将为URL字符串分配内存，调用方必须通过OH_ArkWeb_ReleaseString释放该字符串。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResponse_GetUrl(const ArkWeb_Response* response, char** url);

/**
 * @brief 给ArkWeb_Response对象设置一个错误码。用于与DidFailWithError配合使用，通过错误码告知客户端请求失败的具体原因，如权限错误、资源不存在等。
 *
 * @param response ArkWeb_Response。
 * @param errorCode 失败请求的错误码。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResponse_SetError(ArkWeb_Response* response, ArkWeb_NetError errorCode);

/**
 * @brief 获取ArkWeb_Response的错误码。
 *
 * @param response ArkWeb_Response。
 * @return ArkWeb_Response的错误码。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
ArkWeb_NetError OH_ArkWebResponse_GetError(const ArkWeb_Response* response);

/**
 * @brief 为ArkWeb_Response对象设置一个HTTP状态码。
 *
 * @param response ArkWeb_Response。
 * @param status 响应的HTTP状态码。取值范围为100-599，应符合HTTP标准状态码规范（信息100-199、成功200-299、重定向300-399、客户端错误400-499、服务器错误500-599）。
 *     超出范围时行为未定义。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResponse_SetStatus(ArkWeb_Response* response, int status);

/**
 * @brief 获取ArkWeb_Response的HTTP状态码。
 *
 * @param response ArkWeb_Response。
 * @return ArkWeb_Response的HTTP状态码。如果ArkWeb_Response无效，则为-1。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int OH_ArkWebResponse_GetStatus(const ArkWeb_Response* response);

/**
 * @brief 为ArkWeb_Response设置状态文本。
 *
 * @param response ArkWeb_Response。
 * @param statusText 响应的状态文本。设置状态文本会为HTTP状态码提供更详细的描述，例如：状态码200可以对应“OK”、状态码404可以对应“Not Found”等，帮助客户端更好地理解请求结果。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResponse_SetStatusText(ArkWeb_Response* response, const char* statusText);

/**
 * @brief 获取ArkWeb_Response的状态文本。
 *
 * @param response ArkWeb_Response。
 * @param statusText 返回ArkWeb_Response的状态文本。此函数将为statusText字符串分配内存，调用方必须通过OH_ArkWeb_ReleaseString释放该字符串。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResponse_GetStatusText(const ArkWeb_Response* response, char** statusText);

/**
 * @brief 为ArkWeb_Response设置媒体类型。
 *
 * @param response ArkWeb_Response。
 * @param mimeType 响应的媒体类型。设置媒体类型会告诉客户端响应内容的类型，例如：text/html表示HTML文档、application/json表示JSON数据、image/png表示PNG图片等，
 *     浏览器会根据媒体类型选择合适的渲染方式。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResponse_SetMimeType(ArkWeb_Response* response, const char* mimeType);

/**
 * @brief 获取ArkWeb_Response的媒体类型。
 *
 * @param response ArkWeb_Response。
 * @param mimeType 返回ArkWeb_Response的媒体类型。此函数将为mimeType字符串分配内存，调用方必须通过OH_ArkWeb_ReleaseString释放该字符串。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResponse_GetMimeType(const ArkWeb_Response* response, char** mimeType);

/**
 * @brief 为ArkWeb_Response设置字符集。
 *
 * @param response ArkWeb_Response。
 * @param charset 响应的字符集。设置字符集会告诉客户端响应内容使用的字符编码，例如：UTF-8表示使用UTF-8编码、GBK表示使用GBK编码等，浏览器会根据字符集正确解析和显示文本内容。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResponse_SetCharset(ArkWeb_Response* response, const char* charset);

/**
 * @brief 获取ArkWeb_Response的字符集。
 *
 * @param response ArkWeb_Response。
 * @param charset 返回ArkWeb_Response的字符集。此函数将为charset字符串分配内存，调用方必须通过OH_ArkWeb_ReleaseString释放字符串。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResponse_GetCharset(const ArkWeb_Response* response, char** charset);

/**
 * @brief 为ArkWeb_Response设置一个header。
 *
 * @param response ArkWeb_Response。
 * @param name header的名称。指定要设置的HTTP响应头名称，例如：Content-Type、Content-Length、Cache-Control等，不同的header会影响浏览器如何处理响应。
 * @param value header的值。指定HTTP响应头的值，例如：对于Content-Type可以设置为text/html、对于Cache-Control可以设置为no-cache等，
 *     实际效果取决于header的名称和值的组合。
 * @param overwrite 如果为true，将覆盖现有的header，否则不覆盖。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @since 12
 */
int32_t OH_ArkWebResponse_SetHeaderByName(ArkWeb_Response* response,
                                          const char* name,
                                          const char* value,
                                          bool overwrite);

/**
 * @brief 从ArkWeb_Response中获取header。
 *
 * @param response ArkWeb_Response。
 * @param name header的名称。
 * @param value 返回header的值。此函数将为value字符串分配内存，调用方必须通过OH_ArkWeb_ReleaseString释放该字符串。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResponse_GetHeaderByName(const ArkWeb_Response* response, const char* name, char** value);

/**
 * @brief 销毁一个ArkWeb_ResourceHandler对象。
 *
 * @param resourceHandler ArkWeb_ResourceHandler。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceHandler_Destroy(const ArkWeb_ResourceHandler* resourceHandler);

/**
 * @brief 将构造的响应头传递给被拦截的请求。在拦截请求并准备返回自定义响应时调用，用于设置HTTP响应状态码、媒体类型、字符集等响应头信息。
 *
 * @param resourceHandler 该请求的ArkWeb_ResourceHandler。
 * @param response 该拦截请求的ArkWeb_Response。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceHandler_DidReceiveResponse(const ArkWeb_ResourceHandler* resourceHandler,
                                                    const ArkWeb_Response* response);

/**
 * @brief 将构造的响应体传递给被拦截的请求。在设置响应头后调用，用于发送响应数据。可以多次调用来分块传输数据，在传输完成后需调用OH_ArkWebResourceHandler_DidFinish通知请求结束。
 *
 * @param resourceHandler 该请求的ArkWeb_ResourceHandler。
 * @param buffer 要发送的buffer数据。
 * @param bufLen buffer的大小，单位：字节。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceHandler_DidReceiveData(const ArkWeb_ResourceHandler* resourceHandler,
                                                const uint8_t* buffer,
                                                int64_t bufLen);

/**
 * @brief 通知ArkWeb内核被拦截的请求已经完成，并且没有更多的数据可用。该函数向内核发送完成信号，内核将结束该请求的处理，并清理相关的内部资源。调用此函数后，不能再对该请求调用其他处理函数。如果请求过程中发生错误，
 * 应使用OH_ArkWebResourceHandler_DidFailWithError通知内核。
 *
 * @param resourceHandler 该请求的ArkWeb_ResourceHandler。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceHandler_DidFinish(const ArkWeb_ResourceHandler* resourceHandler);

/**
 * @brief 通知ArkWeb内核，被拦截的请求应该失败。在权限验证失败、资源不存在、网络错误等场景下调用，用于标记请求失败并通过错误码告知客户端具体失败原因。
 *
 * @param resourceHandler 用于被拦截的URL请求。可以通过ArkWeb_ResourceHandler发送自定义请求头以及自定义请求体。
 * @param errorCode 该请求的错误码。请参考{@link arkweb_net_error_list.h}。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceHandler_DidFailWithError(const ArkWeb_ResourceHandler* resourceHandler,
                                                  ArkWeb_NetError errorCode);

/**
 * @brief 通知ArkWeb内核，被拦截的请求应该失败。对比{@link OH_ArkWebResourceHandler_DidFailWithError}接口，新增参数completeIfNoResponse，值为true时，
 * 若之前未调用过{@link OH_ArkWebResourceHandler_DidReceiveResponse}，则会自动生成一个response以完成此次网络请求，网络错误码为-104；值为false时，将等待应用调用
 * {@link OH_ArkWebResourceHandler_DidReceiveResponse}并传入response，不会直接完成此次网络请求。
 *
 * @param resourceHandler 用于被拦截的URL请求。可以通过ArkWeb_ResourceHandler发送自定义请求头以及自定义请求体。
 * @param errorCode 该请求的错误码。请参考{@link arkweb_net_error_list.h}。
 * @param completeIfNoResponse 若之前未调用过{@link OH_ArkWebResourceHandler_DidReceiveResponse}，调用
 *     {@link OH_ArkWebResourceHandler_DidFailWithErrorV2}时，此次网络请求是否完成；值为true时，若之前未调用过
 *     {@link OH_ArkWebResourceHandler_DidReceiveResponse}，则会自动生成一个response以完成此次网络请求，网络错误码为-104；值为false时，将等待应用调用
 *     {@link OH_ArkWebResourceHandler_DidReceiveResponse}并传入response，不会直接完成此次网络请求。
 * @return 如果返回0，表示成功；返回17100101，表示参数无效。
 * @since 20
 */
int32_t OH_ArkWebResourceHandler_DidFailWithErrorV2(const ArkWeb_ResourceHandler* resourceHandler,
                                                    ArkWeb_NetError errorCode,
                                                    bool completeIfNoResponse);

/**
 * @brief 创建一个ArkWeb_ErrorInfo对象。
 * @param errorInfo 返回创建的ArkWeb_ErrorInfo。
 * 如果errorInfo为空，则不做任何操作。
 * 如果创建成功，则*errorInfo指向新创建的对象。当不再需要时，必须使用OH_ArkWeb_DestroyErrorInfo进行销毁。
 * 如果创建失败，*errorInfo将被设置为NULL。
 * @since 26.1.0
 */
void OH_ArkWeb_CreateErrorInfo(ArkWeb_ErrorInfo** errorInfo);

/**
 * @brief 销毁ArkWeb_ErrorInfo。
 * @param errorInfo 要销毁的ArkWeb_ErrorInfo。
 *
 * @since 26.1.0
 */
void OH_ArkWeb_DestroyErrorInfo(ArkWeb_ErrorInfo* errorInfo);

/**
 * @brief 设置是否在未收到响应时自动生成响应。
 * @param errorInfo ArkWeb_ErrorInfo。
 * @param completeIfNoResponse 如果为true，将在尚未收到响应时构造响应。
 * @return {@link ARKWEB_NET_OK} 0 -成功。
 * {@link ARKWEB_INVALID_PARAM} 17100101 -参数无效，errorInfo为nullptr。
 *
 * @since 26.1.0
 */
int32_t OH_ArkWebErrorInfo_SetCompleteIfNoResponse(ArkWeb_ErrorInfo* errorInfo, bool completeIfNoResponse);

/**
 * @brief 获取是否在未收到响应时自动生成响应。
 * @param errorInfo ArkWeb_ErrorInfo。
 * @return 如果启用如果没有收到响应，则自动生成响应，则返回true，否则返回false。
 *
 * @since 26.1.0
 */
bool OH_ArkWebErrorInfo_GetCompleteIfNoResponse(const ArkWeb_ErrorInfo* errorInfo);

/**
 * @brief 设置自定义错误码。Web引擎将通过以下方式将自定义错误代码直接传递给应用程序
 * onErrorReceive.
 * @param errorInfo ArkWeb_ErrorInfo。
 * @param errorCode 自定义错误码。
 * @return {@link ARKWEB_NET_OK} 0 -成功。
 * {@link ARKWEB_INVALID_PARAM} 17100101 -参数无效，errorInfo为nullptr。
 *
 * @since 26.1.0
 */
int32_t OH_ArkWebErrorInfo_SetCustomErrorCode(ArkWeb_ErrorInfo* errorInfo, int32_t errorCode);

/**
 * @brief 获取之前设置的自定义错误码。
 * @param errorInfo ArkWeb_ErrorInfo。
 * @return 返回先前设置的自定义错误码。
 *
 * @since 26.1.0
 */
int32_t OH_ArkWebErrorInfo_GetCustomErrorCode(const ArkWeb_ErrorInfo* errorInfo);

/**
 * @brief 设置错误码。
 * @param errorInfo ArkWeb_ErrorInfo。
 * @param errorCode 此请求的错误代码。请参阅arkweb_net_error_list.h。
 * @return {@link ARKWEB_NET_OK} 0 -成功。
 * {@link ARKWEB_INVALID_PARAM} 17100101 -参数无效，errorInfo为nullptr。
 *
 * @since 26.1.0
 */
int32_t OH_ArkWebErrorInfo_SetErrorCode(ArkWeb_ErrorInfo* errorInfo, ArkWeb_NetError errorCode);

/**
 * @brief 获取之前设置的错误码。
 * @param errorInfo ArkWeb_ErrorInfo。
 * @return 返回之前设置的错误码。
 *
 * @since 26.1.0
 */
ArkWeb_NetError OH_ArkWebErrorInfo_GetErrorCode(const ArkWeb_ErrorInfo* errorInfo);

/**
 * @brief 将错误信息设置为ArkWebRespons。
 * @param response ArkWeb_Response。
 * @param errorInfo 响应的ArkWeb_ErrorInfo。
 * @return {@link ARKWEB_NET_OK} 0 -成功。
 * {@link ARKWEB_INVALID_PARAM} 17100101 -参数无效。
 *
 * @since 26.1.0
 */
int32_t OH_ArkWebResponse_SetErrorInfo(ArkWeb_Response* response, ArkWeb_ErrorInfo* errorInfo);

/**
 * @brief 获取先前设置的ArkWeb_ErrorInfo。
 *
 * @param response ArkWeb_Response对象。
 * @return 如果已设置ArkWeb_ErrorInfo，则返回指向ArkWeb_ErrorInfo的指针；否则返回NULL。
 *
 * @since 26.1.0
 */
ArkWeb_ErrorInfo* OH_ArkWebResponse_GetErrorInfo(const ArkWeb_Response* response);

/**
 * @brief 通知ArkWeb此请求应该失败。
 * @param resourceHandler 请求的ArkWeb_ResourceHandler。
 * @param errorInfo 此请求的错误信息。
 * @return 如果成功，则为0；否则，则为失败。请参阅arkweb_error_code.h。
 *
 * @since 26.1.0
 */
int32_t OH_ArkWebResourceHandler_DidFailWithErrorInfo(
    const ArkWeb_ResourceHandler* resourceHandler,
    const ArkWeb_ErrorInfo* errorInfo);

/**
 * @brief 释放由NDK接口创建的字符串。
 *
 * @param string 待释放的字符串。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWeb_ReleaseString(char* string);

/**
 * @brief 释放由NDK接口创建的字节数组。
 *
 * @param byteArray 待释放的字节数组。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWeb_ReleaseByteArray(uint8_t* byteArray);

#ifdef __cplusplus
};
#endif
#endif // ARKWEB_SCHEME_HANDLER_H
/** @} */