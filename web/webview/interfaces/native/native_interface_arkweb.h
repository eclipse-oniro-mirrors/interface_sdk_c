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
 * @brief Provides APIs to use javascript proxy and run javascript code.
 * @since 11
 */
/**
 * @file native_interface_arkweb.h
 *
 * @brief native_interface_arkweb.h is the core entry header file of ArkWeb Native API. It defines the enums, structs,
 * and NDK function interfaces required for interaction between apps and the ArkWeb engine, covering features such as
 * JavaScript execution and proxy injection, cookie management, blankless loading control, and kernel version selection.
 *  This module is suitable for scenarios that require deep interaction with the **Web** component through native
 * methods. It addresses the technical challenge that complex capabilities of the ArkWeb component (such as JavaScript
 * bidirectional communication, cookie persistence, and kernel version switching) cannot be directly called at the
 * ArkTS layer, providing developers with complete low-level control to implement high-performance, customizable **Web**
 *  component features.
 *
 * @kit ArkWeb
 * @library libohweb.so
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
#ifndef NATIVE_INTERFACE_ARKWEB_H
#define NATIVE_INTERFACE_ARKWEB_H

#include <stdbool.h>
#include <stdint.h>

#include "arkweb_error_code.h"
#include "arkweb_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Called to return the result after the JavaScript code is executed.
 *
 * @since 11
 */
typedef void (*NativeArkWeb_OnJavaScriptCallback)(const char*);

/**
 * @brief Called when a JavaScript proxy is registered.
 *
 * @since 11
 */
typedef char* (*NativeArkWeb_OnJavaScriptProxyCallback)(const char** argv, int32_t argc);

/**
 * @brief Called when a **Web** component is valid.
 *
 * @since 11
 */
typedef void (*NativeArkWeb_OnValidCallback)(const char*);

/**
 * @brief Called when a **Web** component is destroyed.
 *
 * @since 11
 */
typedef void (*NativeArkWeb_OnDestroyCallback)(const char*);

/**
 * @brief Called when a cookie is saved.
 *
 * @param errorCode {@link ARKWEB_SUCCESS}: The cookie is successfully saved.
 *     <br>{@link ARKWEB_COOKIE_SAVE_FAILED}: Failed to save the cookie.
 *     <br>{@link ARKWEB_COOKIE_MANAGER_INITIALIZE_FAILED}: The **CookieManager** initialization failed.
 * @since 20
 */
typedef void (*OH_ArkWeb_OnCookieSaveCallback)(ArkWeb_ErrorCode errorCode);

/**
 * @brief Defines a pointer to the callback invoked when the cookie fetch operation is complete.
 *
 * @param errorCode Error code for the cookie fetch callback.
 *     <br>{@link ARKWEB_SUCCESS}: The cookie is fetched successfully.
 *     <br>{@link ARKWEB_INVALID_URL}: Invalid URL.
 *     <br>{@link ARKWEB_LIBRARY_OPEN_FAILURE}: Failed to open the dynamic link library.
 *     <br>{@link ARKWEB_LIBRARY_SYMBOL_NOT_FOUND}: The required symbol is not found in the dynamic link library.
 * @param cookieValue Cookies corresponding to the URL. The function allocates memory for cookieValue, and the
 *     developer must release the string using {@link OH_ArkWeb_ReleaseString}.
 * @since 26.0.0
 */
typedef void (*OH_ArkWeb_OnCookieFetchCallback)(ArkWeb_ErrorCode errorCode, char* cookieValue);

/**
 * @brief Describes the first-screen loading prediction information, including the predicted first-screen similarity
 * value, predicted first-screen loading time, and error code. The app uses this information to decide whether to
 * enable the blankless loading frame insertion solution, which reduces the blank screen time by inserting pre-rendered
 * frames during page loading.
 *
 * @since 20
 */
typedef struct {
    /**
     * Error code of the blankless loading. The value **0** indicates no error, and a non-zero value indicates the
     * error type. For details, see {@link ArkWeb_BlanklessErrorCode}.
     */
    ArkWeb_BlanklessErrorCode errCode;
    /**
     * Similarity of the first screen. The similarity is calculated based on the first screen content of historical
     * loads. The value ranges from [0, 1.0], where **1.0** indicates a complete match. The closer the value is to 1,
     * the higher the similarity. This value has a lagging nature, meaning the similarity of a local load will only be
     * reflected in the next load. It is recommended that the app does not enable the blankless loading frame insertion
     * solution when the similarity is below a specific threshold (for example, 0.33).
     */
    double similarity;
    /**
     * Predicted loading time of the current load based on the first screen loading time of historical loads, in ms.
     * The value must be greater than 0.
     */
    int32_t loadingTime;
} ArkWeb_BlanklessInfo;

/**
 * @brief For ArkWeb kernel versions, see {@link Adaptation Guide for the M114 Kernel on OpenHarmony 6.0} and
 * {@link Adaptation Guide for the M132 Kernel on OpenHarmony 7.0}.
 *
 * @since 20
 */
typedef enum {
    /**
     * @brief System default kernel (see {@link Constraints}). The default kernel is M132 for OpenHarmony 6.0 and M144
     * for OpenHarmony 7.0.
     *
     * @since 20
     */
    SYSTEM_DEFAULT = 0,

    /**
     * @brief Legacy kernel of OpenHarmony 6.0. Developers can select this legacy kernel. If this kernel does not exist
     * on the system version, the setting does not take effect and the system default kernel is used.
     *
     * @since 20
     */
    ARKWEB_M114 = 1,

    /**
     * @brief Evergreen kernel of OpenHarmony 6.0 (legacy kernel of OpenHarmony 7.0). M132 is the default kernel of
     * OpenHarmony 6.0. If this kernel does not exist on the system version, the setting does not take effect and the
     * system default kernel is used.
     *
     * @since 20
     */
    ARKWEB_M132 = 2,

    /**
     * @brief Evergreen kernel of OpenHarmony 7.0. M144 is the default kernel of OpenHarmony 7.0. If this kernel does
     * not exist on the system version, the setting does not take effect and the system default kernel is used.
     *
     * @since 26.0.0
     */
    ARKWEB_M144 = 3,

    /**
     * @brief Latest kernel of the system (evergreen kernel). Developers can select to use the latest kernel on each
     * system version.
     *
     * @since 23
     */
    ARKWEB_EVERGREEN = 99999
} ArkWebEngineVersion;

/**
 * @brief Loads and asynchronously executes a piece of JavaScript code in the context of the current page. This
 * function must be called in the main thread. **Use case**: Used when you need to dynamically modify page content,
 * obtain page runtime information, or interact with page JavaScript at the native layer, for example, obtaining form
 * data or executing custom scripts.
 *
 * @param webTag Name of the **Web** component.
 * @param jsCode A piece of JavaScript code script.
 * @param callback Callback for notifying the code execution result.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
void OH_NativeArkWeb_RunJavaScript(const char* webTag, const char* jsCode, NativeArkWeb_OnJavaScriptCallback callback);

/**
 * @brief Registers a list of object and function names, used to inject native objects into web pages and implement
 * bidirectional communication between the app side and the frontend page. This is used in scenarios such as web pages
 * calling native functions, native code controlling web page behavior, and cross-layer interaction in hybrid apps.
 *
 * @param webTag Name of the **Web** component.
 * @param objName Name of the registered object.
 * @param methodList Name of the registered method list.
 * @param callback Registered callback.
 * @param size Number of registered callbacks.
 * @param needRefresh Whether a page need to be refreshed. The value **true** indicates that the page needs to be
 *     refreshed, and **false** indicates the opposite.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
void OH_NativeArkWeb_RegisterJavaScriptProxy(const char* webTag, const char* objName, const char** methodList,
    NativeArkWeb_OnJavaScriptProxyCallback* callback, int32_t size, bool needRefresh);

/**
 * @brief Deletes a registered object and its callback functions, used to clean up JavaScript injection objects that
 * are no longer needed. Typical use cases: cleaning up injected objects when a page is destroyed, removing
 * corresponding native interfaces when a function module is unloaded, and preventing memory leaks.
 *
 * @param webTag Name of the **Web** component.
 * @param objName Name of the registered object.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
void OH_NativeArkWeb_UnregisterJavaScriptProxy(const char* webTag, const char* objName);

/**
 * @brief Sets the callback invoked when an object can be registered. Used when specific logic needs to be executed
 * after a JavaScript proxy object is successfully registered, for example, notifying the page or logging after
 * successful registration.
 *
 * @param webTag Name of the **Web** component.
 * @param callback Callback used when an object is valid.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
void OH_NativeArkWeb_SetJavaScriptProxyValidCallback(const char* webTag, NativeArkWeb_OnValidCallback callback);

/**
 * @brief Obtains the callback used when a registered object is valid.
 *
 * @param webTag Name of the **Web** component.
 * @return Callback used when a registered object is valid. If no valid callback function is set for the **webTag**
 *     parameter, a null pointer is returned.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
NativeArkWeb_OnValidCallback OH_NativeArkWeb_GetJavaScriptProxyValidCallback(const char* webTag);

/**
 * @brief Sets the callback invoked when the **Web** component is destroyed. Typical use cases: releasing resources,
 * cleaning up states, or performing finalization operations when the **Web** component is destroyed, for example,
 * releasing JavaScript proxy objects, canceling network requests, or closing file handles.
 *
 * @param webTag Name of the **Web** component.
 * @param callback Callback invoked when the Web component is destroyed.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
void OH_NativeArkWeb_SetDestroyCallback(const char* webTag, NativeArkWeb_OnDestroyCallback callback);

/**
 * @brief Obtains the registered callback invoked when the **Web** component is destroyed.
 *
 * @param webTag Name of the **Web** component.
 * @return Returns the registered callback for when the Web component is destroyed. If the destroy callback specified
 *     by the **webTag** parameter is not set, a null pointer is returned.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
NativeArkWeb_OnDestroyCallback OH_NativeArkWeb_GetDestroyCallback(const char* webTag);

/**
 * @brief Loads data or a URL. This function must be called in the main thread. Typical use cases: loading page content
 * from the network or local files, dynamically generating and displaying HTML content, implementing offline page
 * display, and custom page rendering.
 *
 * @param webTag Name of the **Web** component.
 * @param data String being base64 or URL encoded, which cannot be empty.
 * @param mimeType Media type, such as **text/html**, which cannot be empty.
 * @param encoding Encoding type, such as **UTF-8**, which cannot be empty.
 * @param baseUrl Specified URL path (using the "http", "https", or "data" protocol), assigned to window.origin by the
 *     Web component.
 * @param historyUrl Historical URL. If this parameter is not empty, it can be managed in historical records to
 *     implement backward and forward navigation.
 * @return Error codes of OH_NativeArkWeb_LoadData.
 *     <br>{@link ARKWEB_SUCCESS}: data loaded successfully.
 *     <br>{@link ARKWEB_INVALID_PARAM}: a required parameter is not specified, the parameter type is incorrect, or
 *     parameter verification fails.
 *     <br>{@link ARKWEB_INIT_ERROR}: initialization fails. No valid Web component is found based on the passed "webTag"
 *     .
 *     <br>{@link ARKWEB_LIBRARY_OPEN_FAILURE}: failed to open the dynamic link library. Check whether the library file
 *     path is correct, whether the library file is corrupted, and whether you have sufficient access permissions.
 *     <br>{@link ARKWEB_LIBRARY_SYMBOL_NOT_FOUND}: the required symbol is not found in the dynamic link library.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 15
 */
ArkWeb_ErrorCode OH_NativeArkWeb_LoadData(const char* webTag,
                                          const char* data,
                                          const char* mimeType,
                                          const char* encoding,
                                          const char* baseUrl,
                                          const char* historyUrl);

/**
 * @brief Registers a JavaScript object that contains callback methods with return values. The object is injected into
 * all frames of the current page, including all iframes, and can be accessed by the name specified in
 * ArkWeb_ProxyObjectWithResult. The object takes effect in JavaScript only after the next page load or reload. These
 * methods are executed in the worker thread of ArkWeb. Typical use cases: processing JavaScript calls and returning
 * results in the worker thread, for example, performing time-consuming computations, asynchronous task processing, and
 * complex business logic processing, to avoid blocking the main thread.
 *
 * @param webTag Name of the **Web** component.
 * @param proxyObject Object to be registered.
 * @param permission A JSON string used to configure the object and method levels of the JSBridge permission. This
 *     value is empty by default.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 20
 */
void OH_NativeArkWeb_RegisterAsyncThreadJavaScriptProxy(const char* webTag,
    const ArkWeb_ProxyObjectWithResult* proxyObject, const char* permission);

/**
 * @brief Sets whether blankless loading is enabled. This API must be used together with
 * OH_NativeArkWeb_GetBlanklessInfoWithKey.
 *
 * > **NOTE**
 * >
 * > - This API must be called after the page loading API is triggered. Other constraints are the same as those of
 * > {@link OH_NativeArkWeb_GetBlanklessInfoWithKey}.
 * > - The page must be loaded in the component that calls this set of APIs.
 * > - When the similarity is low, the system will deem the scene change too abrupt and frame insertion will fail.
 *
 * @permission ohos.permission.INTERNET and ohos.permission.GET_NETWORK_INFO
 * @param webTag Name of the **Web** component.
 * @param key Unique key that identifies this page. It must be the same as the key value of the
 *     {@link OH_NativeArkWeb_GetBlanklessInfoWithKey} API.
 *     <br>Valid value range: non-empty, with a maximum length of 2048 characters.
 *     <br>Behavior for invalid values: returns the error code {@link ArkWeb_BlanklessErrorCode}, and frame insertion
 *     does not take effect.
 * @param isStarted Whether to enable frame insertion. The value **true** means to enable frame insertion. Select this
 *     option when the first screen of the page has high similarity and the blank screen time needs to be reduced to
 *     improve the loading experience. The value **false** means to disable frame insertion. Select this option when
 *     the page transition is too large, resulting in low similarity, or when the loading experience does not need to
 *     be optimized.
 *     <br>Default value: **false**.
 * @return Enumerates the error codes. For details, see {@link ArkWeb_BlanklessErrorCode}.
 * @since 20
 */
ArkWeb_BlanklessErrorCode OH_NativeArkWeb_SetBlanklessLoadingWithKey(const char* webTag,
                                                                     const char* key,
                                                                     bool isStarted);

/**
 * @brief Clears the blankless loading cache of the page with a specified key value.
 * <br>In an applet or web application, when the content changes significantly during page loading, an obvious scene
 * change may occur. If you are concerned about this change, you can use this API to clear the page cache.
 *
 * @param key The list of key values of pages cached in the blankless loading solution. These key values are
 *     specified in OH_NativeArkWeb_GetBlanklessInfoWithKey.
 *
 *     The default value is the list of key values of all pages cached in the blankless loading solution.
 *
 *     The key length cannot exceed 2048 characters, and the number of keys must be less than or equal to 100. The
 *     URL is the same as that input to the Web component during page loading.
 *
 *     When the key length exceeds 2048 characters, the key does not take effect. When the number of keys exceeds
 *     100, the first 100 keys are used. If this parameter is set to NULL, the default value is used.
 * @param size Size of the keys array.
 *     <br>Valid value range: 0 to 100. If the value exceeds 100, the first 100 keys in the array are used.
 *     <br>Behavior for invalid values: if the value is greater than 100, the first 100 keys are used.
 * @since 20
 */
void OH_NativeArkWeb_ClearBlanklessLoadingCache(const char* key[], uint32_t size);

/**
 * @brief Obtains the first screen loading prediction information, and starts to generate the loading transition frame.
 * The application determines whether to enable blankless loading based on the information. For details, see {@link ArkWeb_BlanklessInfo}
 * . This API must be used together with the {@link OH_NativeArkWeb_SetBlanklessLoadingWithKey} API and must be called
 * before the page loading API is triggered and after **WebViewController** is bound to the **Web** component.
 *
 * > **NOTE**
 * >
 * > - The default size of the persistent cache capacity is 30 MB (about 30 pages). You can set the cache capacity by
 * > calling {@link OH_NativeArkWeb_SetBlanklessLoadingCacheCapacity}. For details, see the description of this API.
 * > When the maximum capacity is exceeded, the cache is updated based on the Least Recently Used (LRU) mechanism. The
 * > persistent cache data that has been stored for more than seven days is automatically cleared. After the cache is
 * > cleared, the optimization effect appears when the page is loaded for the third time.
 * > - If the value of **similarity** in {@link ArkWeb_BlanklessInfo} is extremely low, check whether the key value is
 * > correctly passed.
 * > - After this API is called, page loading snapshot detection and transition frame generation calculation are enabled
 * > , which generates certain resource overhead.
 * > - Blankless loading consumes resources, which depends on the resolution of the **Web** component. It is assumed
 * > that a width and a height of the resolution are respectively **w** and **h**. When a page is opened, the peak
 * > memory usage increases by about **12×w×h** B. After the page is opened, the memory is reclaimed, which does not
 * > affect the stable memory usage. When the size of the solid-state application cache is increased, the increased
 * > cache of each page is about **w×h/10** B and the cache is located in the application cache.
 *
 * @permission ohos.permission.INTERNET and ohos.permission.GET_NETWORK_INFO
 * @param webTag Name of the **Web** component.
 * @param key Key value that uniquely identifies the page.
 * The value cannot be empty and can contain a maximum of 2048 characters.
 * Invalid values do not take effect.
 * @return Prediction information about blankless loading, including the first screen similarity and first screen
 * loading duration. The application determines whether to enable blankless loading based on the prediction information.
 * @since 20
 */
ArkWeb_BlanklessInfo OH_NativeArkWeb_GetBlanklessInfoWithKey(const char* webTag, const char* key);

/**
 * @brief Sets the persistent cache capacity for the blankless loading solution and returns the actual effective value.
 * The default cache capacity is 30 MB, and the maximum value is 100 MB. When the actual cache exceeds the capacity,
 * infrequently used transition frames are evicted for cleanup. Typical use cases: adjusting the cache size based on
 * the app memory usage, optimizing storage space usage, and balancing the blankless effect with system resource
 * consumption.
 *
 * @param capacity Sets the persistent cache capacity, in MB. The maximum value cannot exceed 100 MB.
 *     <br>Default value: 30 MB.
 *     <br>Valid range: 0 to 100. When set to 0, there is no cache space and the feature is globally disabled.
 *     <br>Invalid value handling: When the value is greater than 100, the effective value is 100.
 * @return Effective capacity value, in MB, ranging from 0 to 100.
 *     <br>If the value is greater than 100, the effective value is 100.
 * @since 20
 */
uint32_t OH_NativeArkWeb_SetBlanklessLoadingCacheCapacity(uint32_t capacity);


/**
 * @brief Persists all cookies currently accessible through the CookieManager API to the disk. If this API is used in a
 * non-UI thread, you need to initialize the CookieManager API using {@link OH_ArkWeb_GetNativeAPI} first. Typical use
 * cases: saving cookie states when the app exits or at specific times, for example, saving user login states, app
 * configuration information, and session data, to ensure that the previous state can be restored after the app
 * restarts.
 *
 * @return Error codes of OH_ArkWebCookieManager_SaveCookieSync. Check whether the disk space is sufficient, whether
 *     write permission is available, and whether the cookie data format is correct.
 *     <br>{@link ARKWEB_SUCCESS}: the cookie is saved successfully.
 *     <br>{@link ARKWEB_COOKIE_SAVE_FAILED}: failed to save the cookie.
 *     <br>{@link ARKWEB_COOKIE_MANAGER_INITIALIZE_FAILED}: failed to initialize CookieManager.
 *     <br>{@link ARKWEB_COOKIE_MANAGER_NOT_INITIALIZED}: on a non-UI thread, calling this API without initializing the
 *     CookieManager API is not allowed. Use {@link OH_ArkWeb_GetNativeAPI} to initialize the CookieManager API first.
 * @since 20
 */
ArkWeb_ErrorCode OH_ArkWebCookieManager_SaveCookieSync();


/**
 * @brief Persists all cookies currently accessible through the CookieManager API to the disk. If this API is used in a
 * non-UI thread, you need to initialize the CookieManager API using {@link OH_ArkWeb_GetNativeAPI} first. Without
 * initializing the CookieManager API, this API is automatically executed on the UI thread. Typical use cases:
 * asynchronously saving cookie states, for example, saving cookies asynchronously after page loading is complete or
 * after a user operation, to avoid blocking the main thread.
 *
 * @param callback Callback invoked after the cookie is saved successfully or fails. When a callback is passed in, the
 *     operation result is received asynchronously using the callback, which is suitable for scenarios requiring
 *     asynchronous notification of the save result. When no callback is passed in, the behavior may vary depending on
 *     the specific implementation.
 * @since 20
 */
void OH_ArkWebCookieManager_SaveCookieAsync(OH_ArkWeb_OnCookieSaveCallback callback);

/**
 * Sets the ArkWeb kernel version. If the system does not support the specified version, the setting is invalid and the
 * system default kernel is used (see {@link Constraints}). Used when a specific kernel version needs to be selected
 * based on app compatibility requirements, for example, when an app depends on features of an older kernel version or
 * needs to maintain compatibility on a newer system version, a specific legacy kernel version can be specified.<br>
 * This API is a global static method and must be called before **initializeWebEngine** is called. If any **Web**
 * component has been loaded, the setting of this API is invalid.
 * @param { ArkWebEngineVersion } webEngineVersion - ArkWeb kernel version.
 *     For details, see {@link ArkWebEngineVersion}.
 * @since 20
 */
void OH_NativeArkWeb_SetActiveWebEngineVersion(ArkWebEngineVersion webEngineVersion);

/**
 * Obtains the current ArkWeb kernel version.
 *
 * @return The current ArkWeb kernel version defined by {@link ArkWebEngineVersion}.
 * @since 20
 */
ArkWebEngineVersion OH_NativeArkWeb_GetActiveWebEngineVersion();

/**
 * Sets whether to defer the initialization of the ArkWeb kernel. If this method is not called, the ArkWeb kernel is
 * not deferred for initialization by default. Typical use cases: the **Web** function is not needed immediately at app
 * startup, and you want to delay kernel initialization to save startup resources; the app only needs to use
 * CookieManager without **Web** component rendering for the time being. This API is a global static method and must be
 * called before using the **Web** component and initializing the ArkWeb kernel; otherwise, the setting is invalid.
 * @param { bool } lazy - Controls whether to delay the initialization of the web engine.
 * @since 22
 */
void OH_NativeArkWeb_LazyInitializeWebEngineInCookieManager(bool lazy);

/**
 * Checks whether the ArkWeb kernel used by the application is the evergreen kernel, that is, the latest kernel of the
 * system.
 * @return Whether the kernel used by the current app is the Evergreen kernel. The value **true** indicates it is the
 *     Evergreen kernel, and **false** indicates it is not.
 * @since 23
 */
bool OH_NativeArkWeb_IsActiveWebEngineEvergreen();

/**
 * @brief Obtains the cookies corresponding to the specified URL. If this API is used in a non-UI thread, you need to
 * initialize the CookieManager API using {@link OH_ArkWeb_GetNativeAPI} first.
 *
 * @param url URL to which the cookies belong. It is recommended to provide the complete URL.
 * @param incognito Whether to obtain the in-memory cookies of the webview in incognito mode. The value **true**
 *     indicates obtaining cookies in incognito mode, and **false** indicates obtaining cookies in non-incognito mode.
 * @param includeHttpOnly Whether to include cookies marked with the HTTP-Only attribute in cookieValue. The value
 *     **true** indicates that they are included, and **false** indicates that they are not.
 * @param includePartitionedCookies Whether to include first-party partitioned cookies in cookieValue. The value
 *     **true** indicates that they are included, and **false** indicates that they are not.
 * @param cookieValue Cookie value corresponding to the URL. The function allocates memory for cookieValue, and the
 *     developer must release the string using {@link OH_ArkWeb_ReleaseString}.
 * @return Result code.
 *     <br>{@link ARKWEB_SUCCESS}: The cookie is obtained successfully.
 *     <br>{@link ARKWEB_INVALID_URL}: Invalid URL.
 *     <br>{@link ARKWEB_INVALID_PARAM}: Invalid parameter.
 *     <br>{@link ARKWEB_COOKIE_MANAGER_NOT_INITIALIZED}: In a non-UI thread, calling this API without initializing the
 *     CookieManager API is not allowed. Initialize the CookieManager API using OH_ArkWeb_GetNativeAPI first.
 *     <br>{@link ARKWEB_LIBRARY_OPEN_FAILURE}: Failed to open the dynamic link library.
 *     <br>{@link ARKWEB_LIBRARY_SYMBOL_NOT_FOUND}: The required symbol is not found in the dynamic link library.
 * @since 26.0.0
 */
ArkWeb_ErrorCode OH_ArkWebCookieManager_FetchCookieSync(const char* url, bool incognito, bool includeHttpOnly,
    bool includePartitionedCookies, char** cookieValue);

/**
 * @brief Asynchronously obtains the cookies corresponding to the specified URL. Without initializing the CookieManager
 * API, this API is automatically executed on the UI thread.
 *
 * @param url URL to which the cookies belong. It is recommended to provide the complete URL.
 * @param incognito Whether to obtain the in-memory cookies of the webview in incognito mode. The value **true**
 *     indicates obtaining cookies in incognito mode, and **false** indicates obtaining cookies in non-incognito mode.
 * @param includeHttpOnly Whether to include cookies marked with the HTTP-Only attribute in cookieValue. The value
 *     **true** indicates that they are included, and **false** indicates that they are not.
 * @param includePartitionedCookies Whether to include first-party partitioned cookies in cookieValue. The value
 *     **true** indicates that they are included, and **false** indicates that they are not.
 * @param callback Callback invoked after the cookies are obtained.
 * @since 26.0.0
 */
void OH_ArkWebCookieManager_FetchCookieAsync(const char* url, bool incognito, bool includeHttpOnly,
    bool includePartitionedCookies, OH_ArkWeb_OnCookieFetchCallback callback);

#ifdef __cplusplus
};
#endif
#endif // NATIVE_INTERFACE_ARKWEB_H
/** @} */