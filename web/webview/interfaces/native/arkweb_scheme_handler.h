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
 * @brief The `arkweb_scheme_handler.h` file is a complete C API header file in ArkWeb for intercepting and customizing
 * network requests. This module defines **ArkWeb_SchemeHandler** for registering custom scheme interceptors,
 * **ArkWeb_ResourceHandler** for sending custom responses, **ArkWeb_Response** for building HTTP responses,
 * **ArkWeb_ResourceRequest** for inspecting request details, as well as **ArkWeb_HttpBodyStream** for reading upload
 * data and **ArkWeb_RequestHeaderList** for accessing request headers. This API works with the
 * **ArkWeb_NativeAPIVariantKind** system and is registered through **OH_ArkWeb_SetSchemeHandler** or
 * **OH_ArkWebServiceWorker_SetSchemeHandler**. Developers can implement custom protocol resource loading and responses,
 * suitable for scenarios such as local resource replacement, encrypted data transmission, and offline caching. By
 * intercepting and customizing network requests, it helps developers address special business requirements that
 * standard protocols cannot fulfill, enhancing app security and data control capabilities while optimizing network
 * resource loading efficiency.
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
 * @brief Enumerates the custom scheme options.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef enum ArkWeb_CustomSchemeOption {
    OH_ARKWEB_SCHEME_OPTION_NONE = 0,

    /**
     * The scheme is processed as a standard scheme. The standard schemes need to comply with the URL normalization and
     * parsing rules defined in Section 3.1 of RFC 1738, which can be found in the http://www.ietf.org/rfc/rfc1738.txt.
     */
    ARKWEB_SCHEME_OPTION_STANDARD = 1 << 0,

    /**
     * The scheme is processed using the same security rule as the file URL.
     */
    ARKWEB_SCHEME_OPTION_LOCAL = 1 << 1,

    /**
     * The request of the scheme can be initiated only by the page that is loaded using the same scheme.
     */
    ARKWEB_SCHEME_OPTION_DISPLAY_ISOLATED = 1 << 2,

    /**
     * The scheme is processed using the same security rule as the HTTPS URL.
     */
    ARKWEB_SCHEME_OPTION_SECURE = 1 << 3,

    /**
     * The scheme can send CORS requests. In most cases, this value should be set when **ARKWEB_SCHEME_OPTION_STANDARD**
     * is set.
     */
    ARKWEB_SCHEME_OPTION_CORS_ENABLED = 1 << 4,

    /**
     * The scheme can bypass the Content Security Policy (CSP) check. In most cases, this value should not be set
     * when ARKWEB_SCHEME_OPTION_STANDARD is set.
     */
    ARKWEB_SCHEME_OPTION_CSP_BYPASSING = 1 << 5,

    /**
     * The FETCH API request of the scheme can be initiated.
     */
    ARKWEB_SCHEME_OPTION_FETCH_ENABLED = 1 << 6,

    /**
     * The JS resources of the scheme support code cache generation.
     */
    ARKWEB_SCHEME_OPTION_CODE_CACHE_ENABLED = 1 << 7
} ArkWeb_CustomSchemeOption;

/**
 * @brief Enumerates the resource types of the request. The resource types match the corresponding items of
 * **ResourceType** in Chromium and should not be renumbered.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef enum ArkWeb_ResourceType {
    /**
     * Main frame.
     */
    MAIN_FRAME = 0,

    /**
     * Frame or iframe.
     */
    SUB_FRAME = 1,

    /**
     * Cascading Style Sheets (CSS).
     */
    STYLE_SHEET = 2,

    /**
     * External script.
     */
    SCRIPT = 3,

    /**
     * Image (JPG, GIF, PNG, or other format).
     */
    IMAGE = 4,

    /**
     * Font.
     */
    FONT_RESOURCE = 5,

    /**
     * Other sub-resource. If the type is unknown, the default type is used.
     */
    SUB_RESOURCE = 6,

    /**
     * The **Object** (or **embed**) tag of the plug-in, or the resource requested by the plug-in.
     */
    OBJECT = 7,

    /**
     * Media resource.
     */
    MEDIA = 8,

    /**
     * Main resource of the dedicated worker thread.
     */
    WORKER = 9,

    /**
     * Main resource of a shared worker thread.
     */
    SHARED_WORKER = 10,

    /**
     * Explicit prefetch request.
     */
    PREFETCH = 11,

    /**
     * Website icon.
     */
    FAVICON = 12,

    /**
     * XMLHttpRequest.
     */
    XHR = 13,

    /**
     * Ping request for <a ping>/sendBeacon.
     */
    PING = 14,

    /**
     * Main resource of a service worker.
     */
    SERVICE_WORKER = 15,

    /**
     * Report of Content Security Policy violation.
     */
    CSP_REPORT = 16,

    /**
     * Resource requested by the plug-in.
     */
    PLUGIN_RESOURCE = 17,

    /**
     * Main frame redirection request that triggers service worker preloading.
     */
    NAVIGATION_PRELOAD_MAIN_FRAME = 19,

    /**
     * Subframe redirection request that triggers service worker preloading.
     */
    NAVIGATION_PRELOAD_SUB_FRAME = 20
} ArkWeb_ResourceType;

/**
 * @brief ArkWeb_SchemeHandler is a struct used to register custom scheme (protocol) interceptors. It defines two
 * function pointers: the onRequestStart callback for request start and the onRequestStop callback for request stop.
 * With this struct, network requests of a specified scheme in the Web component can be intercepted, which is
 * applicable to scenarios such as resource localization, data simulation, request filtering, and protocol extension:
 * in onRequestStart, whether to intercept is determined and custom data is returned; in onRequestStop, resource
 * cleanup is performed; and onRequestStart and onRequestStop are called sequentially in the order of the request
 * lifecycle. This struct works with ArkWeb_ResourceHandler and ArkWeb_Response to implement a complete request
 * interception and custom response process. The call sequence is: ArkWeb_SchemeHandler intercepts the request →
 * ArkWeb_ResourceHandler processes the resource → ArkWeb_Response returns the response.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef struct ArkWeb_SchemeHandler_ ArkWeb_SchemeHandler;

/**
 * @brief The ArkWeb_ResourceHandler struct is a resource handler for processing intercepted scheme requests. After
 * ArkWeb_SchemeHandler intercepts a request of a specified scheme, this struct can be used to return custom response
 * data to the Web component, including the response status code, response headers, and response body. This struct is
 * passed as a parameter in the onRequestStart callback, through which developers can implement fully custom responses
 * to intercepted requests.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef struct ArkWeb_ResourceHandler_ ArkWeb_ResourceHandler;

/**
 * @brief Defines an **ArkWeb_Response** for the intercepted request.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef struct ArkWeb_Response_ ArkWeb_Response;

/**
 * @brief ArkWeb_ResourceRequest is a struct that contains detailed information about an intercepted scheme request,
 * including the request URL, HTTP method, request headers, and other metadata. This struct is passed as a parameter in
 * the onRequestStart callback of ArkWeb_SchemeHandler and is applicable to scenarios such as custom protocol handling
 * and resource interception. It helps developers implement features like cross-origin request control and local
 * resource mapping, thereby enhancing security and performance. Developers can use it to obtain complete information
 * about the intercepted request and decide whether to intercept it and how to construct a custom response.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef struct ArkWeb_ResourceRequest_ ArkWeb_ResourceRequest;

/**
 * @brief ArkWeb_RequestHeaderList is an HTTP request header list struct used to represent and manage a collection of
 * key-value pairs of HTTP request headers in the ArkWeb NDK. This struct contains a request header array (headers) and
 * the array length (headerCount), where headers is a pointer array of ArkWeb_RequestHeader and headerCount indicates
 * the number of elements in the array. This struct is used together with ArkWeb_ResourceRequest and other structs to
 * provide the capability of reading and setting network request headers for Web components. Use cases: processing HTTP
 * request headers in a custom protocol handler, modifying request headers in a network request interceptor, adding
 * authentication headers in API authentication scenarios, and configuring request headers in scenarios such as cache
 * control and content negotiation.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef struct ArkWeb_RequestHeaderList_ ArkWeb_RequestHeaderList;

/**
 * @brief Defines the uploaded data of the request. You can use the **OH_ArkWebHttpBodyStream_** API to read the
 * uploaded data.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef struct ArkWeb_HttpBodyStream_ ArkWeb_HttpBodyStream;

/**
 * @brief The error info for setting response error details.
 *
 * @since 26.1.0
 */
typedef struct ArkWeb_ErrorInfo_ ArkWeb_ErrorInfo;

/**
 * @brief Called when a request starts. This callback is used on the IO thread. It intercepts and handles network
 * requests of a specified scheme at the start of the request. Developers can use this callback to implement custom
 * protocol handling, local resource replacement, encrypted data transmission, and other features.
 *
 * @param schemeHandler **ArkWeb_SchemeHandler**.
 * @param resourceRequest Object used to obtain the request information.
 * @param resourceHandler **ArkWeb_ResourceHandler** of the request. If **intercept** is set to **false**, this
 *     parameter should not be used.
 * @param intercept Whether to intercept the request. If the value is **true**, the request will be intercepted.
 *     Otherwise, the request will not be intercepted.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef void (*ArkWeb_OnRequestStart)(const ArkWeb_SchemeHandler* schemeHandler,
                                      ArkWeb_ResourceRequest* resourceRequest,
                                      const ArkWeb_ResourceHandler* resourceHandler,
                                      bool* intercept);

/**
 * @brief Called when the request stops. This callback is used on the IO thread. It is used to perform resource cleanup,
 * status updates, or logging when the request completes. You should use **OH_ArkWebResourceRequest_Destroy** to
 * destroy the **resourceRequest** and use **OH_ArkWebResourceHandler_Destroy** to destroy the
 * **ArkWeb_ResourceHandler** received in **ArkWeb_OnRequestStart**.
 *
 * @param schemeHandler **ArkWeb_SchemeHandler**.
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @since 12
 */
typedef void (*ArkWeb_OnRequestStop)(const ArkWeb_SchemeHandler* schemeHandler,
                                     const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief Called when the **OH_ArkWebHttpBodyStream_Read** read operation is complete. This callback runs on the ArkWeb
 * worker thread.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @param buffer Buffer for receiving data.
 * @param bytesRead Number of bytes read. If bytesRead is greater than 0, the buffer has been filled with bytesRead
 *     bytes of data. The developer can read data from the buffer. If the return value of OH_ArkWebHttpBodyStream_IsEof
 *     is false, the developer can continue to read the remaining data.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef void (*ArkWeb_HttpBodyStreamReadCallback)(const ArkWeb_HttpBodyStream* httpBodyStream,
                                                  uint8_t* buffer,
                                                  int bytesRead);

/**
 * @brief Called when the **OH_ArkWebHttpBodyStream_AsyncRead** read operation is complete. This callback runs on the
 * ArkWeb worker thread.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @param buffer Pointer to the buffer for receiving data.
 * @param bytesRead Byte count representing the result of the asynchronous read operation. If bytesRead is greater than
 *     0, the buffer has been filled with bytesRead bytes of data. The developer can read data from the buffer. If
 *     OH_ArkWebHttpBodyStream_IsEof returns false, the developer can continue reading the remaining data.
 * @since 20
 */
typedef void (*ArkWeb_HttpBodyStreamAsyncReadCallback)(const ArkWeb_HttpBodyStream *httpBodyStream,
                                                       uint8_t *buffer,
                                                       int bytesRead);

/**
 * @brief Called when **ArkWeb_HttpBodyStream** initialization is complete.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @param result Operation result. If the operation is successful, **ARKWEB_NET_OK** is returned. Otherwise, see
 *     {@link arkweb_net_error_list.h}.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
typedef void (*ArkWeb_HttpBodyStreamInitCallback)(const ArkWeb_HttpBodyStream* httpBodyStream, ArkWeb_NetError result);

/**
 * @brief Destroys an **ArkWeb_RequestHeaderList** object.
 *
 * @param requestHeaderList The **ArkWeb_RequestHeaderList** to be destroyed.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebRequestHeaderList_Destroy(ArkWeb_RequestHeaderList* requestHeaderList);

/**
 * @brief Obtains the size of a request header list.
 *
 * @param requestHeaderList Request header list.
 * @return Size of the request header. If **requestHeaderList** is invalid, the value is **-1**.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebRequestHeaderList_GetSize(const ArkWeb_RequestHeaderList* requestHeaderList);

/**
 * @brief Obtains a specified request header.
 *
 * @param requestHeaderList Request header list.
 * @param index Index of the request header. The value ranges from [0, size-1], where size is the size of the request
 *     header list. The behavior is undefined when the value is out of range.
 * @param key Key of the request header. You should use the **OH_ArkWeb_ReleaseString** function to release this string.
 * @param value Value of the request header. You should use the **OH_ArkWeb_ReleaseString** function to release this
 *     string.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebRequestHeaderList_GetHeader(const ArkWeb_RequestHeaderList* requestHeaderList,
                                          int32_t index,
                                          char** key,
                                          char** value);

/**
 * @brief Sets user data to the **ArkWeb_ResourceRequest** object. It is used to pass context information between
 * different request callbacks or store request-associated state, which can later be retrieved through
 * {@link OH_ArkWebResourceRequest_GetUserData()}.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @param userData User data to be set.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceRequest_SetUserData(ArkWeb_ResourceRequest* resourceRequest, void* userData);

/**
 * @brief Obtains user data from **ArkWeb_ResourceRequest**.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @return Pointer to the user data. This pointer is set by the developer through
 *     {@link OH_ArkWebResourceRequest_SetUserData} and can be used to pass custom context information in the callback.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void* OH_ArkWebResourceRequest_GetUserData(const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief Obtains the method of a request.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @param method HTTP request method. This function allocates memory for the **method** string. You should use
 *     **OH_ArkWeb_ReleaseString** to release the string.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_GetMethod(const ArkWeb_ResourceRequest* resourceRequest, char** method);

/**
 * @brief Obtains the URL of a request.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @param url URL of a request. This function allocates memory for the **url** string. You should release the string
 *     using **OH_ArkWeb_ReleaseString**.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_GetUrl(const ArkWeb_ResourceRequest* resourceRequest, char** url);

/**
 * @brief Creates an **ArkWeb_HttpBodyStream** to read the uploaded data of the request.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @param httpBodyStream Uploaded data of the request. This function allocates memory for **httpBodyStream**. You
 *     should use **OH_ArkWebResourceRequest_DestroyHttpBodyStream** to release **httpBodyStream**.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_GetHttpBodyStream(const ArkWeb_ResourceRequest* resourceRequest,
                                                ArkWeb_HttpBodyStream** httpBodyStream);

/**
 * @brief Destroys an **ArkWeb_HttpBodyStream** object.
 *
 * @param httpBodyStream The **httpBodyStream** to be destroyed.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_DestroyHttpBodyStream(ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief Obtains the resource type of a request.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @return Resource type of the request. If resourceRequest is invalid, the value is **-1**, indicating that the
 *     request object is null or invalid. For other values, see {@link ArkWeb_ResourceType}.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceRequest_GetResourceType(const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief Obtains the URL of the frame that triggers this request.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @param frameUrl URL of the frame that triggers the request. This function allocates memory for the URL string. You
 *     should release the string using **OH_ArkWeb_ReleaseString**.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_GetFrameUrl(const ArkWeb_ResourceRequest* resourceRequest, char** frameUrl);

/**
 * @brief Sets user data to the **ArkWeb_HttpBodyStream** object.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @param userData User data to be set.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebHttpBodyStream_SetUserData(ArkWeb_HttpBodyStream* httpBodyStream, void* userData);

/**
 * @brief Obtains user data from **ArkWeb_HttpBodyStream**.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @return Pointer to the user data. This pointer is set by the developer through OH_ArkWebHttpBodyStream_SetUserData
 *     and can be used to pass custom context information in the callback.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void* OH_ArkWebHttpBodyStream_GetUserData(const ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief Sets a callback for **OH_ArkWebHttpBodyStream_Read**. The result of **OH_ArkWebHttpBodyStream_Read** is
 * notified to the caller through **readCallback**,
 * <br>which will run in the same thread as **OH_ArkWebHttpBodyStream_Read**.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @param readCallback Callback of **OH_ArkWebHttpBodyStream_Read**.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebHttpBodyStream_SetReadCallback(ArkWeb_HttpBodyStream* httpBodyStream,
                                                ArkWeb_HttpBodyStreamReadCallback readCallback);

/**
 * @brief Sets a callback for **OH_ArkWebHttpBodyStream_AsyncRead**. The result of **OH_ArkWebHttpBodyStream_AsyncRead**
 * is notified to the caller through **readCallback**, which runs in the ArkWeb worker thread.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @param readCallback Callback of **OH_ArkWebHttpBodyStream_AsyncRead**.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @since 20
 */
int32_t OH_ArkWebHttpBodyStream_SetAsyncReadCallback(ArkWeb_HttpBodyStream* httpBodyStream,
                                                     ArkWeb_HttpBodyStreamAsyncReadCallback readCallback);

/**
 * @brief Initializes **ArkWeb_HttpBodyStream**. This function establishes the internal data structures and connections
 * of **httpBodyStream** in preparation for subsequent read operations. During initialization, it allocates necessary
 * resources and establishes a communication mechanism with the worker thread. This function must be called before any
 * other function; otherwise, other operations will not execute properly. This API needs to be called on the IO thread
 * to ensure thread safety and correct initialization order.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @param initCallback Callback of the initialization.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebHttpBodyStream_Init(ArkWeb_HttpBodyStream* httpBodyStream,
                                     ArkWeb_HttpBodyStreamInitCallback initCallback);

/**
 * @brief Reads the upload data of a request into the buffer. This function uses an asynchronous read mechanism,
 * submitting the read task to the worker thread for execution and returning the result through a callback. The buffer
 * size must be greater than or equal to **bufLen** to accommodate the data to be read. Data is read from the worker
 * thread into the buffer, so the buffer should not be used in other threads before the callback returns, to avoid
 * concurrency issues. After the read operation completes, the caller is notified through the previously set callback,
 * which returns the actual number of bytes read.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @param buffer Buffer for receiving data. The buffer size must be greater than bufLen.
 * @param bufLen Number of bytes to read. The value must be a positive integer. The behavior is undefined if a negative
 *     number is passed.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebHttpBodyStream_Read(const ArkWeb_HttpBodyStream* httpBodyStream, uint8_t* buffer, int bufLen);

/**
 * @brief Exports the uploaded data of a request to the buffer. The buffer size must be greater than **bufLen**. The
 * data from the worker thread is exported to the buffer. Therefore, before the callback returns the data, the buffer
 * should not be used in other threads to avoid concurrency problems.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @param buffer Buffer that receives data.
 * @param bufLen Number of bytes to read.
 * @since 20
 */
void OH_ArkWebHttpBodyStream_AsyncRead(const ArkWeb_HttpBodyStream* httpBodyStream, uint8_t* buffer, int bufLen);

/**
 * @brief Obtains the size of **httpBodyStream**. When data is chunked or **httpBodyStream** is invalid, **0** is
 * always returned.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @return Size of **httpBodyStream**.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
uint64_t OH_ArkWebHttpBodyStream_GetSize(const ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief Obtains the position of **httpBodyStream**.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @return Current read position of httpBodyStream. The value is **0** if httpBodyStream is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
uint64_t OH_ArkWebHttpBodyStream_GetPosition(const ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief Determines whether **httpBodyStream** is chunked.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @return Returns **true** if chunked transfer is used; returns **false** otherwise.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWebHttpBodyStream_IsChunked(const ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief Determines whether all data in **httpBodyStream** has been read. **true** is returned if all data in
 * **httpBodyStream** has been read. **false** is returned before the chunked **httpBodyStream** is read for the first
 * time.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @return **true** is returned if all data has been read. Otherwise, **false** is returned.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWebHttpBodyStream_IsEof(const ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief Determines whether all the uploaded data in **httpBodyStream** is in memory and all read requests are
 * synchronized successfully. If yes, **true** is returned. **false** is returned if the data is chunked.
 *
 * @param httpBodyStream **ArkWeb_HttpBodyStream**.
 * @return **true** is returned if all the uploaded data is stored in the memory. Otherwise, **false** is returned.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWebHttpBodyStream_IsInMemory(const ArkWeb_HttpBodyStream* httpBodyStream);

/**
 * @brief Destroys an **ArkWeb_ResourceRequest** object.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceRequest_Destroy(const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief Obtains the referrer of a request.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @param referrer Referrer of the request. This function allocates memory for the referrer string. The caller must
 *     release the string using OH_ArkWeb_ReleaseString.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_GetReferrer(const ArkWeb_ResourceRequest* resourceRequest, char** referrer);

/**
 * @brief Obtains the request header list **ArkWeb_RequestHeaderList** of the request. This function allocates memory
 * for **requestHeaderList**, and the caller must use **OH_ArkWebRequestHeaderList_Destroy** to release
 * **requestHeaderList**.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @param requestHeaderList List of request headers.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResourceRequest_GetRequestHeaders(const ArkWeb_ResourceRequest* resourceRequest,
                                                ArkWeb_RequestHeaderList** requestHeaderList);

/**
 * @brief Determines whether a request is redirected.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @return Whether this is a redirect. The value **true** indicates it is a redirect, and **false** indicates it is not.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWebResourceRequest_IsRedirect(const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief Determines whether a request is from main frame.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @return true if this is from the main frame; false otherwise.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWebResourceRequest_IsMainFrame(const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief Determines whether a request is triggered by a user gesture.
 *
 * @param resourceRequest **ArkWeb_ResourceRequest**.
 * @return true if triggered by a user gesture; false otherwise.
 * @since 12
 */
bool OH_ArkWebResourceRequest_HasGesture(const ArkWeb_ResourceRequest* resourceRequest);

/**
 * @brief Registers a custom scheme with **ArkWeb**. This function should not be called for built-in HTTP, HTTPS, FILE,
 * FTP, ABOUT, and DATA protocols. This function should be called on the main thread before kernel initialization.
 *
 * @param scheme Scheme to be registered, which must comply with RFC 3986.
 * @param option Configuration (behavior) of the scheme. The value is obtained from the
 *     {@link ArkWeb_CustomSchemeOption} enum.
 * @return Result code. Returns 0 if successful; returns 17100100 if an unknown error occurs, in which case check the
 *     call timing and parameter configuration; returns 17100101 if the parameter is invalid; returns 17100102 if the
 *     scheme configuration fails to be registered, in which case register before creating ArkWeb.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWeb_RegisterCustomSchemes(const char* scheme, int32_t option);

/**
 * @brief Sets an **ArkWeb_SchemeHandler** for a specified scheme to intercept requests of the scheme type triggered by
 * **ServiceWorker**. **SchemeHandler** should be set after **BrowserContext** is created.
 * <br>You can use **WebviewController.initializeWebEngine** to initialize **BrowserContext** without creating the
 * **Web** component.
 *
 * @param scheme Scheme to be intercepted, which must comply with RFC 3986.
 * @param schemeHandler **ArkWeb_SchemeHandler** of the scheme. Only requests triggered by **ServiceWorker** are
 *     notified through this **schemeHandler**.
 * @return **true** is returned if the **SchemeHandler** is successfully set for the specified scheme. Otherwise,
 *     **false** is returned.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWebServiceWorker_SetSchemeHandler(const char* scheme, ArkWeb_SchemeHandler* schemeHandler);

/**
 * @brief Sets an **ArkWeb_SchemeHandler** to intercept requests of a specified scheme type. **SchemeHandler** should
 * be set after **BrowserContext** is created.
 * <br>You can use **WebviewController.initializeWebEngine** to initialize **BrowserContext** without creating the
 * **Web** component.
 *
 * @param scheme Scheme to be intercepted.
 * @param webTag Tag name of the Web component, used to identify a unique component. The developer must ensure the
 *     uniqueness of the name. The recommended length does not exceed 256 characters.
 * @param schemeHandler **ArkWeb_SchemeHandler** of the scheme. Only requests triggered from the specified web are
 *     notified through this **SchemeHandler**.
 * @return **true** is returned if the **SchemeHandler** is successfully set for the specified scheme. Otherwise,
 *     **false** is returned.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
bool OH_ArkWeb_SetSchemeHandler(const char* scheme, const char* webTag, ArkWeb_SchemeHandler* schemeHandler);

/**
 * @brief Clears the **SchemeHandler** registered for **ServiceWorker**.
 *
 * @return **0** is returned if the operation is successful.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebServiceWorker_ClearSchemeHandlers();

/**
 * @brief Clears the **SchemeHandler** registered for the specified **Web** component.
 *
 * @param webTag Tag that uniquely identifies a **Web** component. Ensure that it is unique.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWeb_ClearSchemeHandlers(const char* webTag);

/**
 * @brief Creates an **ArkWeb_SchemeHandler** object.
 *
 * @param schemeHandler Created ArkWeb_SchemeHandler. Destroy it using {@link OH_ArkWeb_DestroySchemeHandler} when it
 *     is no longer needed.
 * @since 12
 */
void OH_ArkWeb_CreateSchemeHandler(ArkWeb_SchemeHandler** schemeHandler);

/**
 * @brief Destroys an **ArkWeb_SchemeHandler** object.
 *
 * @param schemeHandler The **ArkWeb_SchemeHandler** to be destroyed.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWeb_DestroySchemeHandler(ArkWeb_SchemeHandler* schemeHandler);

/**
 * @brief Sets user data to the **ArkWeb_SchemeHandler** object.
 *
 * @param schemeHandler **ArkWeb_SchemeHandler**.
 * @param userData User data to be set.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebSchemeHandler_SetUserData(ArkWeb_SchemeHandler* schemeHandler, void* userData);

/**
 * @brief Obtains the user data from **ArkWeb_SchemeHandler**.
 *
 * @param schemeHandler **ArkWeb_SchemeHandler**.
 * @return Pointer to user data. This pointer is set by the developer through OH_ArkWebSchemeHandler_SetUserData and
 *     can be used to pass custom context information in callbacks.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void* OH_ArkWebSchemeHandler_GetUserData(const ArkWeb_SchemeHandler* schemeHandler);

/**
 * @brief Sets an **OnRequestStart** callback for **SchemeHandler**.
 *
 * @param schemeHandler **SchemeHandler** of the scheme.
 * @param onRequestStart The callback function **OnRequestStart**.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebSchemeHandler_SetOnRequestStart(ArkWeb_SchemeHandler* schemeHandler,
                                                 ArkWeb_OnRequestStart onRequestStart);

/**
 * @brief Sets an **OnRequestStop** callback for **SchemeHandler**.
 *
 * @param schemeHandler **SchemeHandler** of the scheme.
 * @param onRequestStop The callback function **OnRequestStop**.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebSchemeHandler_SetOnRequestStop(ArkWeb_SchemeHandler* schemeHandler,
                                                ArkWeb_OnRequestStop onRequestStop);

/**
 * @brief Creates an **ArkWeb_Response** object for the intercepted request.
 *
 * @param response A created **ArkWeb_Response**. Use **OH_ArkWeb_DestroyResponse** to destroy it when it is not
 *     required.
 * @since 12
 */
void OH_ArkWeb_CreateResponse(ArkWeb_Response** response);

/**
 * @brief Destroys an **ArkWeb_Response** object.
 *
 * @param response The **ArkWeb_Response** to be destroyed.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWeb_DestroyResponse(ArkWeb_Response* response);

/**
 * @brief Sets the resolved URL after redirection or HSTS changes. After setting, a navigation is triggered. It is used
 * to implement URL redirection in custom responses, such as URL normalization, domain redirection, and HTTP-to-HTTPS
 * upgrade.
 *
 * @param response **ArkWeb_Response**.
 * @param url Parsed URL.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResponse_SetUrl(ArkWeb_Response* response, const char* url);

/**
 * @brief Obtains the parsed URL that has been redirected or changed due to HSTS.
 *
 * @param response **ArkWeb_Response**.
 * @param url Parsed URL. This function allocates memory for the URL string. The caller must release the string using
 *     OH_ArkWeb_ReleaseString.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResponse_GetUrl(const ArkWeb_Response* response, char** url);

/**
 * @brief Sets an error code for the **ArkWeb_Response** object. It is used together with **DidFailWithError** to
 * inform the client of the specific reason for the request failure through the error code, such as permission errors
 * or resource not found.
 *
 * @param response **ArkWeb_Response**.
 * @param errorCode Error code of the failed request.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResponse_SetError(ArkWeb_Response* response, ArkWeb_NetError errorCode);

/**
 * @brief Obtains the error code of **ArkWeb_Response**.
 *
 * @param response **ArkWeb_Response**.
 * @return Error code of **ArkWeb_Response**.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
ArkWeb_NetError OH_ArkWebResponse_GetError(const ArkWeb_Response* response);

/**
 * @brief Sets an HTTP status code for **ArkWeb_Response**.
 *
 * @param response **ArkWeb_Response**.
 * @param status HTTP status code of the response. The value ranges from 100 to 599 and must comply with HTTP standard
 *     status code specifications (informational 100-199, success 200-299, redirection 300-399, client error 400-499,
 *     server error 500-599). The behavior is undefined when the value is out of range.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResponse_SetStatus(ArkWeb_Response* response, int status);

/**
 * @brief Obtains the HTTP status code of **ArkWeb_Response**.
 *
 * @param response **ArkWeb_Response**.
 * @return HTTP status code of **ArkWeb_Response**. If **ArkWeb_Response** is invalid, the value is **-1**.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int OH_ArkWebResponse_GetStatus(const ArkWeb_Response* response);

/**
 * @brief Sets a status text for **ArkWeb_Response**.
 *
 * @param response **ArkWeb_Response**.
 * @param statusText Status text of the response. Setting the status text provides a more detailed description for the
 *     HTTP status code. For example, status code 200 can correspond to "OK", status code 404 can correspond to "Not
 *     Found", etc., helping the client better understand the request result.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResponse_SetStatusText(ArkWeb_Response* response, const char* statusText);

/**
 * @brief Obtains the status text of **ArkWeb_Response**.
 *
 * @param response **ArkWeb_Response**.
 * @param statusText Status text of **ArkWeb_Response**. This function allocates memory for the **statusText** string.
 *     You need to release the string using **OH_ArkWeb_ReleaseString**.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResponse_GetStatusText(const ArkWeb_Response* response, char** statusText);

/**
 * @brief Sets a mime type for **ArkWeb_Response**.
 *
 * @param response **ArkWeb_Response**.
 * @param mimeType Media type of the response. Setting the media type tells the client the type of the response content,
 *     for example, text/html indicates an HTML document, application/json indicates JSON data, image/png indicates a
 *     PNG image, etc. The browser selects an appropriate rendering mode based on the media type.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResponse_SetMimeType(ArkWeb_Response* response, const char* mimeType);

/**
 * @brief Obtains the mime type of **ArkWeb_Response**.
 *
 * @param response **ArkWeb_Response**.
 * @param mimeType Mime type of **ArkWeb_Response**. This function allocates memory for the **mimeType** string. You
 *     need to release the string using **OH_ArkWeb_ReleaseString**.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResponse_GetMimeType(const ArkWeb_Response* response, char** mimeType);

/**
 * @brief Sets a character set for **ArkWeb_Response**.
 *
 * @param response **ArkWeb_Response**.
 * @param charset Character set of the response. Setting the character set tells the client the character encoding used
 *     for the response content. For example, UTF-8 indicates that UTF-8 encoding is used, GBK indicates that GBK
 *     encoding is used, and so on. The browser correctly parses and displays the text content based on the character
 *     set.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResponse_SetCharset(ArkWeb_Response* response, const char* charset);

/**
 * @brief Obtains the character set of **ArkWeb_Response**.
 *
 * @param response **ArkWeb_Response**.
 * @param charset Character set of **ArkWeb_Response**. This function allocates memory for the **charset** string. You
 *     need to release the string using **OH_ArkWeb_ReleaseString**.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResponse_GetCharset(const ArkWeb_Response* response, char** charset);

/**
 * @brief Sets a header for **ArkWeb_Response**.
 *
 * @param response **ArkWeb_Response**.
 * @param name Name of the header. Specifies the name of the HTTP response header to set, for example, Content-Type,
 *     Content-Length, or Cache-Control. Different headers affect how the browser processes the response.
 * @param value Value of the header. Specifies the value of the HTTP response header, for example, text/html for
 *     Content-Type or no-cache for Cache-Control. The actual effect depends on the combination of the header name and
 *     value.
 * @param overwrite Whether to overwrite the existing header. The value **true** means to overwrite the existing header,
 *     and **false** means the opposite.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @since 12
 */
int32_t OH_ArkWebResponse_SetHeaderByName(ArkWeb_Response* response,
                                          const char* name,
                                          const char* value,
                                          bool overwrite);

/**
 * @brief Obtains the header from **ArkWeb_Response**.
 *
 * @param response **ArkWeb_Response**.
 * @param name Name of the header.
 * @param value Value of the header. This function allocates memory for the **value **string. You need to release the
 *     string using **OH_ArkWeb_ReleaseString**.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWebResponse_GetHeaderByName(const ArkWeb_Response* response, const char* name, char** value);

/**
 * @brief Destroys an **ArkWeb_ResourceHandler** object.
 *
 * @param resourceHandler **ArkWeb_ResourceHandler**.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceHandler_Destroy(const ArkWeb_ResourceHandler* resourceHandler);

/**
 * @brief Passes the constructed response header to the intercepted request. Called when intercepting a request and
 * preparing to return a custom response, it is used to set response header information such as the HTTP response
 * status code, media type, and character set.
 *
 * @param resourceHandler **ArkWeb_ResourceHandler** of the request.
 * @param response **ArkWeb_Response** of the intercepted request.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceHandler_DidReceiveResponse(const ArkWeb_ResourceHandler* resourceHandler,
                                                    const ArkWeb_Response* response);

/**
 * @brief Passes the constructed response body to the intercepted request. Called after setting the response header, it
 * is used to send response data. It can be called multiple times for chunked transfer of data. After the transfer is
 * complete, **OH_ArkWebResourceHandler_DidFinish** must be called to notify the end of the request.
 *
 * @param resourceHandler **ArkWeb_ResourceHandler** of the request.
 * @param buffer Buffer data to be sent.
 * @param bufLen Size of the buffer, in bytes.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceHandler_DidReceiveData(const ArkWeb_ResourceHandler* resourceHandler,
                                                const uint8_t* buffer,
                                                int64_t bufLen);

/**
 * @brief Notifies the ArkWeb kernel that the intercepted request is complete and no more data is available. This
 * function sends a completion signal to the kernel, which will end the processing of the request and clean up related
 * internal resources. After calling this function, no other processing functions can be called for this request. If an
 * error occurs during the request, use **OH_ArkWebResourceHandler_DidFailWithError** to notify the kernel.
 *
 * @param resourceHandler **ArkWeb_ResourceHandler** of the request.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceHandler_DidFinish(const ArkWeb_ResourceHandler* resourceHandler);

/**
 * @brief Notifies the ArkWeb kernel that the intercepted request should fail. Called in scenarios such as permission
 * verification failure, resource not found, or network errors, it is used to mark the request as failed and inform the
 * client of the specific failure reason through an error code.
 *
 * @param resourceHandler Handler for intercepted URL requests. You can use **ArkWeb_ResourceHandler** to send custom
 *     request headers and bodies.
 * @param errorCode Error code of the request. For details, see {@link arkweb_net_error_list.h}.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
int32_t OH_ArkWebResourceHandler_DidFailWithError(const ArkWeb_ResourceHandler* resourceHandler,
                                                  ArkWeb_NetError errorCode);

/**
 * @brief Notifies the ArkWeb kernel that the intercepted request fails. Compared with the
 * {@link OH_ArkWebResourceHandler_DidFailWithError} API, the **completeIfNoResponse** parameter is added. With this
 * parameter set to **true**, if {@link OH_ArkWebResourceHandler_DidReceiveResponse} has not been called, a response is
 * automatically generated to complete the network request and the network error code is **-104**. With this parameter
 * set to **false**, the system waits for the application to call {@link OH_ArkWebResourceHandler_DidReceiveResponse}
 * and pass the response.
 *
 * @param resourceHandler Handler for intercepted URL requests. You can use **ArkWeb_ResourceHandler** to send custom
 *     request headers and bodies.
 * @param errorCode Error code of the request. For details, see {@link arkweb_net_error_list.h}.
 * @param completeIfNoResponse Whether the network request is complete when
 *     {@link OH_ArkWebResourceHandler_DidFailWithErrorV2} is called if
 *     {@link OH_ArkWebResourceHandler_DidReceiveResponse} is not called before. If the value is **true** and
 *     {@link OH_ArkWebResourceHandler_DidReceiveResponse} is not called before, a response is automatically generated
 *     to complete the network request, and the network error code is **-104**. If the value is **false**, the system
 *     waits for the application to call {@link OH_ArkWebResourceHandler_DidReceiveResponse} and pass the response.
 * @return **0** is returned when the operation is successful; **17100101** is returned when the parameter is invalid.
 * @since 20
 */
int32_t OH_ArkWebResourceHandler_DidFailWithErrorV2(const ArkWeb_ResourceHandler* resourceHandler,
                                                    ArkWeb_NetError errorCode,
                                                    bool completeIfNoResponse);

/**
 * @brief Creates an ArkWeb_ErrorInfo object.
 * @param errorInfo The created ArkWeb_ErrorInfo object. If errorInfo is nullptr, this function does nothing.
 *                  If the creation succeeds, *errorInfo points to the newly created object, which must be destroyed
 *                  using {@link OH_ArkWeb_DestroyErrorInfo} when no longer needed.
 *                  If the creation fails, *errorInfo is set to NULL.
 * @since 26.1.0
 */
void OH_ArkWeb_CreateErrorInfo(ArkWeb_ErrorInfo** errorInfo);

/**
 * @brief Destroys the ArkWeb_ErrorInfo.
 * @param errorInfo The ArkWeb_ErrorInfo to be destroyed.
 *
 * @since 26.1.0
 */
void OH_ArkWeb_DestroyErrorInfo(ArkWeb_ErrorInfo* errorInfo);

/**
 * @brief Sets whether to automatically generate a response if no response has been received.
 * @param errorInfo The ArkWeb_ErrorInfo.
 * @param completeIfNoResponse If true, a response will be automatically constructed when no response has been
 *                             received.
 * @return {@link ARKWEB_NET_OK} 0 - Success.
 *         {@link ARKWEB_INVALID_PARAM} 17100101 - Invalid param, errorInfo is nullptr.
 *
 * @since 26.1.0
 */
int32_t OH_ArkWebErrorInfo_SetCompleteIfNoResponse(ArkWeb_ErrorInfo* errorInfo, bool completeIfNoResponse);

/**
 * @brief Gets whether to automatically generate a response if no response has been received.
 * @param errorInfo The ArkWeb_ErrorInfo.
 * @return Returns true if automatically generating a response when no response has been received is enabled,
 *         returns false otherwise.
 *
 * @since 26.1.0
 */
bool OH_ArkWebErrorInfo_GetCompleteIfNoResponse(const ArkWeb_ErrorInfo* errorInfo);

/**
 * @brief Sets the custom error code for ArkWeb_ErrorInfo.
 * @param errorInfo The ArkWeb_ErrorInfo.
 * @param errorCode The custom error code, the web engine will pass the custom error code directly to the application
 *                  through onErrorReceive.
 * @return {@link ARKWEB_NET_OK} 0 - Success.
 *         {@link ARKWEB_INVALID_PARAM} 17100101 - Invalid param, errorInfo is nullptr.
 *
 * @since 26.1.0
 */
int32_t OH_ArkWebErrorInfo_SetCustomErrorCode(ArkWeb_ErrorInfo* errorInfo, int32_t errorCode);

/**
 * @brief Gets the custom error code from the ArkWeb_ErrorInfo.
 * @param errorInfo The ArkWeb_ErrorInfo.
 * @return The custom error code.
 *
 * @since 26.1.0
 */
int32_t OH_ArkWebErrorInfo_GetCustomErrorCode(const ArkWeb_ErrorInfo* errorInfo);

/**
 * @brief Sets the error code for ArkWeb_ErrorInfo.
 * @param errorInfo The ArkWeb_ErrorInfo.
 * @param errorCode The error code for this request. Refer to arkweb_net_error_list.h.
 * @return {@link ARKWEB_NET_OK} 0 - Success.
 *         {@link ARKWEB_INVALID_PARAM} 17100101 - Invalid param, errorInfo is nullptr.
 *
 * @since 26.1.0
 */
int32_t OH_ArkWebErrorInfo_SetErrorCode(ArkWeb_ErrorInfo* errorInfo, ArkWeb_NetError errorCode);

/**
 * @brief Gets the error code from the ArkWeb_ErrorInfo. Refer to arkweb_net_error_list.h.
 * @param errorInfo The ArkWeb_ErrorInfo.
 * @return The error code.
 *
 * @since 26.1.0
 */
ArkWeb_NetError OH_ArkWebErrorInfo_GetErrorCode(const ArkWeb_ErrorInfo* errorInfo);

/**
 * @brief Sets the error info for the ArkWeb_Response.
 *
 * @param response The ArkWeb_Response.
 * @param errorInfo The ArkWeb_ErrorInfo to set. Ownership is not transferred; the caller must keep errorInfo
 *                  valid until {@link ArkWeb_OnRequestStop} is triggered.
 * @return {@link ARKWEB_NET_OK} 0 - Success.
 *         {@link ARKWEB_INVALID_PARAM} 17100101 - Invalid param, response or errorInfo is nullptr.
 *
 * @since 26.1.0
 */
int32_t OH_ArkWebResponse_SetErrorInfo(ArkWeb_Response* response, ArkWeb_ErrorInfo* errorInfo);

/**
 * @brief Gets the error info from the ArkWeb_Response.
 *
 * @param response The ArkWeb_Response.
 * @return The pointer to the ArkWeb_ErrorInfo if set; NULL otherwise.
 *
 * @since 26.1.0
 */
ArkWeb_ErrorInfo* OH_ArkWebResponse_GetErrorInfo(const ArkWeb_Response* response);

/**
 * @brief Notify the web engine that this request should fail with error info.
 * @param resourceHandler The ArkWeb_ResourceHandler for the request.
 * @param errorInfo The error info for this request.
 * @return {@link ARKWEB_NET_OK} 0 - Success.
 *         {@link ARKWEB_INVALID_PARAM} 17100101 - Invalid param, resourceHandler or errorInfo is nullptr.
 *
 * @since 26.1.0
 */
int32_t OH_ArkWebResourceHandler_DidFailWithErrorInfo(
    const ArkWeb_ResourceHandler* resourceHandler,
    const ArkWeb_ErrorInfo* errorInfo);

/**
 * @brief Releases the string created by NDK APIs.
 *
 * @param string String to be released.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWeb_ReleaseString(char* string);

/**
 * @brief Releases the byte array created by NDK APIs.
 *
 * @param byteArray Byte array to be released.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
void OH_ArkWeb_ReleaseByteArray(uint8_t* byteArray);


#ifdef __cplusplus
};
#endif
#endif // ARKWEB_SCHEME_HANDLER_H
/** @} */
