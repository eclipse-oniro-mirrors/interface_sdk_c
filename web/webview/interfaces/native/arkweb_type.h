/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @brief Provide the definition of the C interface for the native ArkWeb.
 * @since 12
 */
/**
 * @file arkweb_type.h
 *
 * @brief Defines the native common types of ArkWeb.
 *
 * @kit ArkWeb
 * @library libohweb.so
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */

#ifndef ARKWEB_TYPE_H
#define ARKWEB_TYPE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "arkweb_error_code.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ArkWeb_JavaScriptBridgeData is a struct that defines JavaScript bridge data, used to transfer JavaScript
 * bridge-related data between native code and web pages. This struct encapsulates the parameter data in bridge calls
 * and serves as the basic data unit in the JavaScript bridge subsystem, working in conjunction with the JavaScript
 * Proxy registration APIs in ArkWeb_ControllerAPI.
 *
 * @since 12
 */
typedef struct {
    /**
     * Pointer to the transmitted data. Supports String and ArrayBuffer types. Other types are JSON-serialized and
     * passed as String.
     */
    const uint8_t* buffer;
    /**
     * Length of the transmitted data. It is recommended to set this value appropriately based on the actual data size
     * and keep it consistent with the buffer size to avoid performance or data issues caused by excessively large or
     * small values.
     */
    size_t size;
} ArkWeb_JavaScriptBridgeData;

/**
 * @brief Enumerates the data types of post message.
 *
 * @since 12
 */
typedef enum ArkWeb_WebMessageType {
    /**
     * Error data.
     */
    ARKWEB_NONE = 0,
    /**
     * String data.
     */
    ARKWEB_STRING,
    /**
     * Byte stream data.
     */
    ARKWEB_BUFFER
} ArkWeb_WebMessageType;

/**
 * @brief Enumerates the JavaScript data types.
 *
 * @since 18
 */
typedef enum ArkWeb_JavaScriptValueType {
    /**
     * Error data.
     */
    ARKWEB_JAVASCRIPT_NONE = 0,
    /**
     * String data.
     */
    ARKWEB_JAVASCRIPT_STRING,
    /**
     * Boolean data type.
     */
    ARKWEB_JAVASCRIPT_BOOL
} ArkWeb_JavaScriptValueType;

/**
 * @brief ArkWeb_WebMessage is a web message struct used for cross-context message communication. It defines the basic
 * format and data carrying capability of messages. This struct serves as the fundamental data unit for web message
 * communication, supporting the transfer of strings and binary data between native code and web pages.
 *
 * @since 12
 */
typedef struct ArkWeb_WebMessage* ArkWeb_WebMessagePtr;

/**
 * @brief ArkWeb_JavaScriptValue is a struct used to encapsulate JavaScript values in native code. It provides basic
 * creation and manipulation capabilities for JavaScript values. This struct supports converting native data into a
 * JavaScript-recognizable format, addressing type safety and format compatibility issues in bidirectional data
 * transfer between native and JavaScript. As the fundamental data transfer type in JavaScript bridge communication, it
 * helps reduce manual conversion costs, improve bridge communication efficiency, and enhance maintainability.
 *
 * @since 18
 */
typedef struct ArkWeb_JavaScriptValue* ArkWeb_JavaScriptValuePtr;

/**
 * @brief Callback invoked when the injected JavaScript execution is complete. It is used to obtain the execution
 * result of JavaScript code in the Web component, for example, in scenarios where the native UI needs to be updated or
 * subsequent logic needs to be executed based on the data returned by JavaScript.
 *
 * @since 12
 */
typedef void (*ArkWeb_OnJavaScriptCallback)(
    const char* webTag, const ArkWeb_JavaScriptBridgeData* data, void* userData);

/**
 * @brief Callback invoked when a Proxy method is executed. Proxy methods are used for object interaction and custom
 * operations between the native side and the JavaScript side.
 *
 * @since 12
 */
typedef void (*ArkWeb_OnJavaScriptProxyCallback)(
    const char* webTag, const ArkWeb_JavaScriptBridgeData* dataArray, size_t arraySize, void* userData);

/**
 * @brief Callback invoked when a Proxy method is executed (with a return value). It is used to receive a notification
 * and return the execution result when JavaScript calls an injected Proxy method. This is suitable for implementing
 * bridge communication between JavaScript and native code, for example, intercepting JavaScript calls, executing
 * native logic, computing results, and returning the results to JavaScript.
 *
 * @param webTag Name of the **Web** component.
 * @param dataArray Pointer to data array.
 * @param arraySize Array size.
 * @param userData Pointer to user-defined data.
 * @since 18
 */
typedef ArkWeb_JavaScriptValuePtr (*ArkWeb_OnJavaScriptProxyCallbackWithResult)(
    const char* webTag, const ArkWeb_JavaScriptBridgeData* dataArray, size_t arraySize, void* userData);

/**
 * @brief Callback for receiving Web component event notifications. It is used to receive lifecycle event notifications
 * of the Web component, such as status change notifications in scenarios like page loading completion, page
 * destruction, and component visibility changes.
 *
 * @since 12
 */
typedef void (*ArkWeb_OnComponentCallback)(const char* webTag, void* userData);

/**
 * @brief Callback invoked when the Web component scrolls.
 *
 * @param webTag Name of the **Web** component.
 * @param userData Pointer to user-defined data.
 * @param x X-axis scroll offset. Unit: vp.
 * @param y Y-axis scroll offset. Unit: vp.
 * @since 18
 */
typedef void (*ArkWeb_OnScrollCallback)(const char* webTag, void* userData, double x, double y);

/**
 * @brief ArkWeb_WebMessagePort is a web message port struct that represents one of the two ports of a MessageChannel,
 * used to send and receive messages. This struct supports bidirectional message communication between native code and
 * web pages.
 *
 * @since 12
 */
typedef struct ArkWeb_WebMessagePort* ArkWeb_WebMessagePortPtr;

/**
 * @brief Called when a post message is sent from the HTML page.
 *
 * @param webTag Name of the **Web** component.
 * @param port Post message port.
 * @param message Post message data.
 * @param userData User-defined data.
 * @since 12
 */
typedef void (*ArkWeb_OnMessageEventHandler)(
    const char* webTag, const ArkWeb_WebMessagePortPtr port, const ArkWeb_WebMessagePtr message, void* userData);

/**
 * @brief The **ArkWeb_JavaScriptObject** struct is used to inject JavaScript code into a web page and obtain the
 * execution result. It is suitable for scenarios where a native app needs to actively call JavaScript functions in a
 * web page, read the web page state, or call web page APIs, simplifying the data interaction flow between the web and
 * native app. Developers can use this struct to specify the JavaScript script content and length to be injected,
 * register an execution completion callback, and pass custom context data through userData, thereby enabling data
 * interaction between the web and native app.
 *
 * @since 12
 */
typedef struct {
    /**
     * JavaScript code to be injected. The buffer length must be consistent with the **size** parameter.
     */
    const uint8_t* buffer;
    /**
     * Length of the JavaScript code, in bytes. Must be consistent with the actual length of **buffer**; otherwise, out-
     * of-bounds access or truncation may occur.
     */
    size_t size;
    /**
     * Callback invoked when JavaScript execution is complete. This is a callback function pointer. Passing **NULL**
     * indicates that no callback is needed.
     */
    ArkWeb_OnJavaScriptCallback callback;
    /**
     * Custom data to be carried in the callback.
     */
    void* userData;
} ArkWeb_JavaScriptObject;

/**
 * @brief ArkWeb_ProxyMethod is a struct that defines a JavaScript proxy method. It supports secure communication
 * between JavaScript and native code, and is suitable for scenarios where native capabilities need to be called from a
 * web page. This struct specifies the basic information of a native method that can be called from JavaScript,
 * consisting of three fields: the method name, the corresponding native callback pointer, and the custom data to carry.
 * Multiple ArkWeb_ProxyMethod instances can be combined into an ArkWeb_ProxyObject, which is injected into a web page
 * as an object, allowing web apps to conveniently access native device capabilities.
 *
 * @since 12
 */
typedef struct {
    /**
     * Pointer to the method name to be injected.
     */
    const char* methodName;
    /**
     * Callback triggered when JavaScript calls this method through a Proxy object, used to handle method calls from
     * JavaScript. The callback can access the parameters (dataArray) passed in from JavaScript and execute the
     * corresponding native logic.
     */
    ArkWeb_OnJavaScriptProxyCallback callback;
    /**
     * Custom data to be carried in the callback.
     */
    void* userData;
} ArkWeb_ProxyMethod;

/**
 * @brief ArkWeb_ProxyMethodWithResult is a JavaScript proxy method struct with a return value. It extends the
 * capabilities of ArkWeb_ProxyMethod and supports obtaining a return value after JavaScript calls a native method.
 * Based on the method name and callback function, this struct adds the return value processing capability, making it
 * suitable for scenarios where execution results need to be returned to the web frontend.
 *
 * @since 18
 */
typedef struct {
    /**
     * Pointer to the method name to be injected.
     */
    const char* methodName;
    /**
     * Callback invoked when JavaScript calls the native proxy method, used to process the method call and return the
     * execution result. This parameter must be a valid function pointer and cannot be NULL.
     */
    ArkWeb_OnJavaScriptProxyCallbackWithResult callback;
    /**
     * Custom data to be carried in the callback.
     */
    void* userData;
} ArkWeb_ProxyMethodWithResult;

/**
 * @brief ArkWeb_ProxyObject is a JavaScript proxy object struct injected into a web page. It organizes a group of
 * related ArkWeb_ProxyMethod methods into an object and exposes them to the web frontend as a whole. This struct
 * specifies the object name in JavaScript (objName), the method array (methodList), and the method count (size),
 * enabling a Native app to expose a structured API set to the web page. The proxy object associates ArkWeb_ProxyMethod
 * on the native side with method calls on the JavaScript side through a method mapping mechanism, supporting automatic
 * conversion of method parameters and return values.
 *
 * @since 12
 */
typedef struct {
    /**
     * Name of the injected object. The name must follow JavaScript identifier rules and cannot contain special
     * characters.
     */
    const char* objName;
    /**
     * Pointer to the method struct array of an object to be injected.
     */
    const ArkWeb_ProxyMethod* methodList;
    /**
     * Length of the method struct array. Must be consistent with the actual number of elements in the methodList array.
     */
    size_t size;
} ArkWeb_ProxyObject;

/**
 * @brief ArkWeb_ProxyObjectWithResult is a JavaScript proxy object struct with a return value, extending the
 * capabilities of ArkWeb_ProxyObject. This struct organizes multiple ArkWeb_ProxyMethodWithResult instances into an
 * object and injects it into a web page, allowing JavaScript to obtain a return value after calling Native methods. It
 * resolves the issue that ArkWeb_ProxyObject cannot return execution results, simplifying the development process and
 * improving development efficiency. It is suitable for API scenarios that require returning structured execution
 * results to the web frontend.
 *
 * @since 18
 */
typedef struct {
    /**
     * Name of the injected object. The name must follow JavaScript identifier rules and cannot contain special
     * characters.
     */
    const char* objName;
    /**
     * Array of method structs carried by the injected object. The array length is specified by the **size** parameter.
     * Each method in the array is registered to the web page, and JavaScript can call it in the format of "objectName.
     * methodName".
     */
    const ArkWeb_ProxyMethodWithResult* methodList;
    /**
     * Length of the method struct array. Must be consistent with the actual number of elements in the methodList array.
     */
    size_t size;
} ArkWeb_ProxyObjectWithResult;

/**
 * @brief ArkWeb_ControllerAPI is a native API struct related to the controller. This struct provides features such as
 * JavaScript injection, synchronous and asynchronous JavaScript proxy registration, proxy deletion, page refresh, Web
 * Message Port creation and management, and Frame URL query. It supports the coexistence of synchronous and
 * asynchronous proxies and unified management and control of WebView behavior. It is suitable for scenarios where
 * JavaScript needs to be injected and called from native code and bidirectional communication between native and pages
 * is required. It resolves JSBridge intercommunication and secure injection issues, improving development efficiency
 * and controllability. This is the primary interface for controlling WebView behavior from native code.<br>Controller-
 * related APIs must be called on the UI thread by calling the OH_ArkWeb_GetNativeAPI method. Before calling, you are
 * advised to use {@link ARKWEB_MEMBER_MISSING} to check the availability of the function pointer to avoid crashes
 * caused by mismatches between the SDK and the device ROM.
 *
 * @since 12
 */
typedef struct {
    /**
     * Size of the struct.
     */
    size_t size;
    /**
     * Injects a JavaScript script. This API must be called on the UI thread by calling the OH_ArkWeb_GetNativeAPI
     * method. This method injects a JavaScript script into the execution context of the **Web** component and executes
     * it after the page is loaded.
     */
    void (*runJavaScript)(const char* webTag, const ArkWeb_JavaScriptObject* javascriptObject);
    /**
     * Injects a JavaScript object into the window object and calls the synchronous methods of this object in the
     * window object. This method maps native objects to the JavaScript environment through a bridging mechanism to
     * implement bidirectional communication. Use Cases: for example, JS calls native capabilities to obtain device
     * information or execute native business logic. This API must be called on the UI thread by calling the
     * OH_ArkWeb_GetNativeAPI method. Compared with registerAsyncJavaScriptProxy, this method is suitable for scenarios
     * where a synchronous return value is required. If a synchronous return value is not needed or the operation is
     * time-consuming, you are advised to use registerAsyncJavaScriptProxy to avoid blocking the UI thread.
     */
    void (*registerJavaScriptProxy)(const char* webTag, const ArkWeb_ProxyObject* proxyObject);
    /**
     * Deletes the app-side JavaScript object with the specified name that is registered with the window through
     * registerJavaScriptProxy. This API must be called on the UI thread by calling the OH_ArkWeb_GetNativeAPI method.
     * This method unbinds the JavaScript object from the native object and releases related resources. Use Cases: for
     * example, cleaning up registered objects to avoid residue when a component is destroyed, a module is unloaded, or
     * services are switched.
     */
    void (*deleteJavaScriptRegister)(const char* webTag, const char* objName);
    /**
     * Refreshes the current web page. The page stack is cleared during the refresh, as a result, the current page
     * cannot be navigated forward or backward. This API must be called on the UI thread by calling the
     * OH_ArkWeb_GetNativeAPI method.
     */
    void (*refresh)(const char* webTag);
    /**
     * Injects a JavaScript object into the window object and calls the asynchronous methods of this object in the
     * window object. This API must be called on the UI thread by calling the OH_ArkWeb_GetNativeAPI method. This
     * method implements asynchronous calls through a message queue mechanism to avoid blocking the main thread.
     * Compared with registerJavaScriptProxy, this method is suitable for time-consuming operations or scenarios where
     * a synchronous return value is not needed. If a synchronous return value is needed, you are advised to use
     * registerJavaScriptProxy.
     */
    void (*registerAsyncJavaScriptProxy)(const char* webTag, const ArkWeb_ProxyObject* proxyObject);
    /**
     * @brief Creates a Post Message port. The Post Message port provides a bidirectional communication mechanism,
     * allowing the native layer and the web layer to securely exchange data messages. This API must be called on the
     * UI thread by calling the OH_ArkWeb_GetNativeAPI method. Use Cases: for example, implementing cross-context
     * message channels to support data transfer between iframes and the main page, and between Web and Worker.
     *
     * @param webTag Name of the **Web** component.
     * @param size Number of ports, which is an output parameter.
     */
    ArkWeb_WebMessagePortPtr* (*createWebMessagePorts)(const char* webTag, size_t* size);

    /**
     * @brief Destroys a port. This method closes the port connection, releases related system resources, and stops
     * message transmission. This API must be called on the UI thread by calling the OH_ArkWeb_GetNativeAPI method. Use
     * Cases: for example, releasing port resources to avoid leaks when communication ends or the component lifecycle
     * ends.
     *
     * @param ports Array of pointers to the Post Message port struct.
     * @param size Number of ports. Must be equal to the number of ports in the ports array.
     */
    void (*destroyWebMessagePorts)(ArkWeb_WebMessagePortPtr** ports, size_t size);

    /**
     * @brief Sends ports to the HTML main page. This method passes Post Message ports to the specified HTML page
     * through a message delivery mechanism to establish a cross-origin communication channel. This API must be called
     * on the UI thread by calling the OH_ArkWeb_GetNativeAPI method. Use Cases: for example, establishing a
     * bidirectional message channel between the main page and an iframe, or pushing messages across frames.
     *
     * @param webTag Name of the Web component. It must match the bound Web component; otherwise, ARKWEB_INIT_ERROR is
     *     returned.
     * @param name Name of the message sent to the HTML page.
     * @param size Number of ports.
     * @param url URL of the page that receives the message.
     * @return Result code.
     *     <br>{@link ARKWEB_SUCCESS}: success.
     *     <br>{@link ARKWEB_INVALID_PARAM}: invalid parameter.
     *     <br>{@link ARKWEB_INIT_ERROR}: initialization failed; no Web component bound to the webTag is found.
     */
    ArkWeb_ErrorCode (*postWebMessage)(
        const char* webTag, const char* name, ArkWeb_WebMessagePortPtr* webMessagePorts, size_t size, const char* url);

    /**
     * @brief Obtains the URL of the last frame that calls JavaScriptProxy. This method records the frame context of
     * the last JavaScript call through a frame stack tracing mechanism. It is called on the thread where
     * JavaScriptProxy is called. A JavaScript object is injected into the window object through
     * registerJavaScriptProxy or JavaScriptProxy. This API can obtain the URL of the frame that last called the
     * injected object. If the injected object has never been called, the return value is undefined. The correct URL
     * can be obtained only when this API is called inside the called function. You can obtain the URL inside the
     * function and save it. This API must be called on the UI thread by calling the OH_ArkWeb_GetNativeAPI method.
     *
     * @return URL of the last frame that calls **JavaScriptProxy**.
     * @since 14
     */
    const char* (*getLastJavascriptProxyCallingFrameUrl)();

    /**
     * @brief Injects a JavaScript object into the window object and calls the synchronous methods of this object in
     * the window object. The synchronous methods of this object can carry return values. This method implements
     * bidirectional data transfer and synchronous calls between JavaScript and native through a synchronous bridging
     * mechanism. Compared with registerJavaScriptProxy, this method adds a permission parameter for configuring
     * JSBridge permission restrictions, and is suitable for scenarios that require permission control or synchronous
     * return values. This API must be called on the UI thread by calling the OH_ArkWeb_GetNativeAPI method. Use Cases:
     * for example, business scenarios where synchronous return results are needed when JS calls native.
     *
     * @param webTag Name of the **Web** component.
     * @param proxyObject Pointer to the proxy object to be registered. The object is injected into the window object,
     *     and its synchronous methods can be called through JavaScript with returnable execution results.
     * @param permission Pointer to a JSON format string, which defaults to an empty string. This string is used to
     *     configure the permission restrictions of JSBridge at the object and method levels.
     * @since 18
     */
    void (*registerJavaScriptProxyEx)(const char* webTag, const ArkWeb_ProxyObjectWithResult* proxyObject,
        const char* permission);

    /**
     * @brief Injects a JavaScript object into the window object and calls the asynchronous methods of this object in
     * the window object. This API must be called on the UI thread by calling the OH_ArkWeb_GetNativeAPI method. This
     * method implements asynchronous calls through a message queue mechanism to avoid blocking the main thread.
     * Compared with registerAsyncJavaScriptProxy, this method adds a permission parameter for configuring JSBridge
     * permission restrictions, and is suitable for asynchronous operation scenarios that require permission control.
     *
     * @param webTag Name of the **Web** component.
     * @param proxyObject Object to be registered.
     * @param permission JSON format string, which defaults to an empty value. It is used to configure the permission
     *     restrictions of JSBridge at the object and method levels.
     * @since 18
     */
    void (*registerAsyncJavaScriptProxyEx)(const char* webTag, const ArkWeb_ProxyObject* proxyObject,
        const char* permission);
} ArkWeb_ControllerAPI;

/**
 * @brief ArkWeb_ComponentAPI is an API struct provided by ArkWeb on the native side for listening to Web component
 * lifecycle events. It inherits from the base native API type {@link ArkWeb_AnyNativeAPI}. Developers obtain this
 * struct by calling {@link OH_ArkWeb_GetNativeAPI} with the `ARKWEB_NATIVE_COMPONENT` type, and then register event
 * callbacks for Web component Controller attached, page load begin, page load end, and component destruction. This
 * struct is suitable for scenarios where you need to perceive key state changes of the Web component in native code (C/
 * C++), such as initializing native resources, synchronizing page load status, collecting analytics data, or releasing
 * associated resources upon component destruction. The related APIs must be called in the UI thread. Before calling a
 * specific member function, it is recommended to use the {@link ARKWEB_MEMBER_MISSING} macro to check whether the
 * function pointer exists.
 *
 * @since 12
 */
typedef struct {
    /**
     * Size of the struct.
     */
    size_t size;
    /**
     * Registers a callback listener for the Controller attached event. Note: This callback must be called in the UI
     * thread. Before calling, it is recommended to use the ARKWEB_MEMBER_MISSING macro to check whether the function
     * pointer exists.
     */
    void (*onControllerAttached)(const char* webTag, ArkWeb_OnComponentCallback callback, void* userData);
    /**
     * This callback is triggered when the web page starts loading. It is triggered only for the main frame, not for
     * iframe or frameset content loading. This callback must be called in the UI thread. Before calling, it is
     * recommended to use the ARKWEB_MEMBER_MISSING macro to check whether the function pointer exists.
     */
    void (*onPageBegin)(const char* webTag, ArkWeb_OnComponentCallback callback, void* userData);
    /**
     * This callback is triggered when the web page finishes loading. It is triggered only for the main frame, not for
     * iframe or frameset content loading. This callback must be called in the UI thread. Before calling, it is
     * recommended to use the ARKWEB_MEMBER_MISSING macro to check whether the function pointer exists.
     */
    void (*onPageEnd)(const char* webTag, ArkWeb_OnComponentCallback callback, void* userData);
    /**
     * Triggered when this **Web** component is destroyed.
     */
    void (*onDestroy)(const char* webTag, ArkWeb_OnComponentCallback callback, void* userData);
} ArkWeb_ComponentAPI;

/**
 * @brief ArkWeb_WebMessagePortAPI is a native API struct for web message ports. This struct provides functions such as
 * message port creation, closing, message sending, and message receiving callback registration. This API is a core
 * component of the postMessage bridge, supporting the establishment of persistent bidirectional communication channels
 * between native code and web pages. It is suitable for scenarios where data interaction between native apps and web
 * pages is required, solving cross-language communication challenges and improving app extensibility and development
 * efficiency.<br>Web message port related APIs must be called on the UI thread by using the OH_ArkWeb_GetNativeAPI
 * method. Before calling, you are advised to use {@link ARKWEB_MEMBER_MISSING} to check the availability of function
 * pointers, preventing crashes caused by mismatches between the SDK and the device ROM.
 *
 * @since 12
 */
typedef struct {
    /**
     * Size of the struct, in bytes.
     */
    size_t size;
    /**
     * @brief Sends a message to the HTML page. It is used when native code needs to pass data, instructions, or
     * configuration information to a web page, for example, form data synchronization and control command delivery.
     *
     * @param webMessagePort Pointer to the message port.
     * @param webTag Name of the Web component, used to identify the Web component to operate. It must be a unique
     *     identifier bound to the Web component. If no Web component bound to webTag is found, an initialization
     *     failure error is returned.
     * @param webMessage Message to send.
     * @return Result code.
     *     <br>{@link ARKWEB_SUCCESS}: execution successful.
     *     <br>{@link ARKWEB_INVALID_PARAM}: invalid parameter.
     *
     *     <br>**Possible causes:**
     *     <br>- webMessagePort or webMessage is null.
     *     <br>- The parameter type is incorrect.
     *
     *     <br>**Solutions:**
     *     <br>- Check whether the parameter is a null pointer.
     *     <br>- Verify that the parameter type meets the API requirements.
     *
     *     <br>{@link ARKWEB_INIT_ERROR}: initialization failed. No Web component bound to webTag is found.
     *
     *     <br>**Possible causes:**
     *     <br>- The Web component is not properly initialized.
     *     <br>- The webTag parameter does not match the actual Web component name.
     *
     *     <br>**Solutions:**
     *     <br>- Ensure that the Web component has been initialized.
     *     <br>- Check whether the webTag parameter matches the Web component name.
     */
    ArkWeb_ErrorCode (*postMessage)(
        const ArkWeb_WebMessagePortPtr webMessagePort, const char* webTag, const ArkWeb_WebMessagePtr webMessage);
    /**
     * @brief Closes a message port.
     *
     * @param webMessagePort Pointer to the message port.
     * @param webTag Name of the **Web** component.
     */
    void (*close)(const ArkWeb_WebMessagePortPtr webMessagePort, const char* webTag);
    /**
     * @brief Sets a callback for receiving HTML messages. It is used when messages, requests, or event notifications
     * from a web page need to be received and processed, for example, receiving user input and status update
     * notifications.
     *
     * @param webMessagePort Pointer to the message port.
     * @param webTag Name of the **Web** component.
     * @param messageEventHandler Callback used to handle messages.
     * @param userData User-defined data that is passed to the messageEventHandler callback when triggered. It can be
     *     used to carry context information or additional service data, and its lifecycle is managed by the app.
     */
    void (*setMessageEventHandler)(const ArkWeb_WebMessagePortPtr webMessagePort, const char* webTag,
        ArkWeb_OnMessageEventHandler messageEventHandler, void* userData);
} ArkWeb_WebMessagePortAPI;

/**
 * @brief ArkWeb_WebMessageAPI is a native API struct for Web messages. This struct provides functions for creating and
 * destroying messages, setting and obtaining message types, and managing message data buffers. This API is part of the
 * postMessage bridge, supporting bidirectional communication between Native code and HTML pages.<br>Web message APIs
 * must be called on the UI thread by calling the OH_ArkWeb_GetNativeAPI method. Before calling, you are advised to use
 * {@link ARKWEB_MEMBER_MISSING} to check the availability of function pointers, preventing crashes caused by a
 * mismatch between the SDK and device ROM.
 *
 * @since 12
 */
typedef struct {
    /**
     * Size of the struct.
     */
    size_t size;
    /**
     * @brief Creates a message. Used to create a message object to be sent before postMessage communication between
     * Native code and HTML pages. After calling createWebMessage(), you must call destroyWebMessage() to release the
     * message resources when they are no longer needed. Failure to call destroyWebMessage() will cause a message
     * resource leak, affecting system memory management.
     *
     * @return Pointer to the message struct.
     */
    ArkWeb_WebMessagePtr (*createWebMessage)();
    /**
     * @brief Destroys a message and releases the memory occupied by the message object. Must be used in pair with
     * createWebMessage(). Call this method to release resources after the message is no longer needed. After the call,
     * the webMessage pointer becomes invalid and should no longer be used.
     *
     * @param webMessage Pointer to the message to destroy.
     */
    void (*destroyWebMessage)(ArkWeb_WebMessagePtr* webMessage);
    /**
     *  @brief Sets the message type. @param webMessage Pointer to the message struct. @param type Message type.
     *
     * @param webMessage Pointer to the message struct.
     * @param type Message type.
     */
    void (*setType)(ArkWeb_WebMessagePtr webMessage, ArkWeb_WebMessageType type);
    /**
     * @brief Obtains the message type. Used to distinguish different types of communication messages, such as text
     * messages, JSON messages, and binary messages.
     *
     * @param webMessage Pointer to the message struct.
     * @return The type of ArkWeb_WebMessage.
     */
    ArkWeb_WebMessageType (*getType)(ArkWeb_WebMessagePtr webMessage);
    /**
     * @brief Sets data. Used to set the specific content of the message, supporting the transfer of text, JSON, or
     * binary data from Native code to HTML pages.
     *
     * @param webMessage Pointer to the message struct.
     * @param data Data pointer. The caller is responsible for memory management. The function does not release this
     *     memory internally, and data ownership is not transferred.
     * @param dataLength Data length.
     */
    void (*setData)(ArkWeb_WebMessagePtr webMessage, void* data, size_t dataLength);
    /**
     * @brief Obtains data. Used to obtain the specific content of the message, supporting the reception of text, JSON,
     * or binary data from HTML pages and processing them in Native code. setData() must be called first to set the
     * data before getData() can be called to obtain the data. If getData() is called without calling setData() first,
     * NULL is returned and dataLength is 0.
     *
     * @param webMessage Pointer to the message struct.
     * @param dataLength Data length, which is an output parameter.
     * @return Pointer to the message data. The data length is returned via the dataLength output parameter. The
     *     lifecycle of the returned pointer is bound to the message object. The pointer becomes invalid after the
     *     message is destroyed, and the caller should not free this memory.
     */
    void* (*getData)(ArkWeb_WebMessagePtr webMessage, size_t* dataLength);
} ArkWeb_WebMessageAPI;

/**
 * @brief ArkWeb_CookieManagerAPI is a Native API struct for cookie management. This struct provides capabilities such
 * as reading, setting, clearing, and synchronizing cookies. It is applicable to scenarios where user sessions need to
 * be managed and user preferences need to be tracked in the Web component, helping developers conveniently implement
 * data persistence and state synchronization.<br>CookieManager APIs must be obtained by calling the
 * OH_ArkWeb_GetNativeAPI method in the UI thread. Before calling, you are advised to use {@link ARKWEB_MEMBER_MISSING}
 * to check the availability of function pointers, so as to avoid crashes caused by mismatch between the SDK and the
 * device ROM.
 *
 * @since 12
 */
typedef struct {
    /**
     * Size of the struct.
     */
    size_t size;

    /**
     * @brief Obtains the cookie value of a specified URL. This method is used in scenarios such as user login state
     * maintenance, session management, and personalized configuration reading. This method must be called in the UI
     * thread. Before calling, you are advised to check the availability of the function pointer.
     *
     * @param url URL of the cookie to obtain. A complete URL is recommended.
     * @param incognito Whether to obtain the in-memory cookies of the Web component in privacy mode. The value true
     *     means to obtain cookies in privacy mode (automatically cleared after app exit), and false means to obtain
     *     cookies in non-privacy mode (persistent storage).
     * @param includeHttpOnly Whether to include cookies marked with the HTTP-Only attribute in cookieValue. The value
     *     true means to include them, and false means not to include them.
     *     **Note:** Reading HTTP-Only cookies must comply with security and compliance requirements.
     * @param cookieValue Output parameter, which is a pointer to the cookie value corresponding to the URL. The memory
     *     is allocated internally by the function, and the caller must release it after use. The return value is a
     *     string that contains all matching cookie items in the format of name=value, where name and value are the
     *     name and value of the cookie, respectively.
     * @return Result code.
     *     <br>{@link ARKWEB_SUCCESS}: success.
     *     <br>{@link ARKWEB_INVALID_URL}: invalid URL. Possible causes: incorrect URL format, empty URL, or non-
     *     compliant URL.
     *     <br>{@link ARKWEB_INVALID_PARAM}: invalid cookieValue parameter.
     */
    ArkWeb_ErrorCode (*fetchCookieSync)(const char* url, bool incognito, bool includeHttpOnly, char** cookieValue);

    /**
     * @brief Sets the cookie value of a specified URL. This method is used in scenarios such as saving user preference
     * settings, maintaining login state, and saving session information. This method must be called in the UI thread.
     * Before calling, you are advised to check the availability of the function pointer.
     *
     * @param url URL of the specified cookie. It must be a complete URL.
     * @param cookieValue Value of the cookie to set, in the format of name=value, where name and value are the name
     *     and value of the cookie, respectively.
     * @param incognito Whether to set the cookie for the corresponding URL in privacy mode. The value true means the
     *     cookie is set in privacy mode (automatically cleared after the app exits), and false means the cookie is set
     *     in non-privacy mode (persistent storage).
     * @param includeHttpOnly Whether to include or overwrite cookies marked with the HTTP-Only attribute. The value
     *     true means cookies marked with the HTTP-Only attribute can also be included in the result or overwritten,
     *     and false means only non-HTTP-Only cookies are processed.
     *     **Note:** Overwriting HTTP-Only cookies may affect security. Ensure that this meets your service security
     *     requirements.
     * @return Result code.
     *     <br>{@link ARKWEB_SUCCESS}: the cookie is set successfully.
     *     <br>{@link ARKWEB_INVALID_URL}: invalid URL. Possible causes: incorrect URL format, empty URL, or non-
     *     compliant URL.
     *     <br>{@link ARKWEB_INVALID_COOKIE_VALUE}: invalid cookieValue parameter.
     */
    ArkWeb_ErrorCode (*configCookieSync)(const char* url,
        const char* cookieValue, bool incognito, bool includeHttpOnly);

    /**
     * @brief Check whether cookies exist.
     *
     * @param incognito True indicates whether cookies exist in privacy mode,
     *                  and false indicates whether cookies exist in non-privacy mode.
     * @return True indicates that the cookie exists, and false indicates that the cookie does not exist.
     */
    bool (*existCookies)(bool incognito);

    /**
     * @brief Clears all cookies (including persistent cookies and session cookies). This method is used in scenarios
     * such as user logout, clearing privacy data, and resetting user state. If you only need to clear session cookies,
     * you are advised to use {@link clearSessionCookiesSync}. This method must be called in the UI thread. Before
     * calling, you are advised to check the availability of the function pointer.
     *
     * @param incognito Whether to clear all cookies in incognito mode. The value **true** means to clear all cookies
     *     in incognito mode, and **false** means the opposite.
     */
    void (*clearAllCookiesSync)(bool incognito);

    /**
     * @brief Clears all session cookies. This method is used in scenarios such as clearing temporary session data,
     * closing all sessions, and cleaning up session timeouts. This method must be called in the UI thread. Before
     * calling, you are advised to check the availability of the function pointer.
     *
     */
    void (*clearSessionCookiesSync)();
} ArkWeb_CookieManagerAPI;

    /**
     * @brief ArkWeb_JavaScriptValueAPI is a JavaScript-related Native API struct. This struct provides functions for
     * creating JavaScript values, supporting the conversion of Native data into a JavaScript-recognizable format and
     * returning it to HTML. This conversion mechanism parses and encapsulates the Native data buffer based on the
     * specified JavaScript value type to generate the corresponding JavaScript value object. It is applicable to
     * scenarios where data needs to be passed from the Native layer to the Web layer, enabling bidirectional data
     * interaction between Native and Web and improving app development flexibility.
     * <br>Call the OH_ArkWeb_GetNativeAPI method on the UI thread to obtain JavaScript-related APIs. Before calling,
     * you are advised to use {@link ARKWEB_MEMBER_MISSING} to check the availability of the function pointer,
     * to prevent crashes caused by mismatch between the SDK and device ROM.
     *
     * @since 18
     */
    typedef struct {
    /**
     * Size of the struct.
     */
    size_t size;

    /**
     * @brief Creates a JavaScript value to be returned to HTML. This function performs type conversion and
     * encapsulation on the data in the data buffer based on the specified type parameter to generate the corresponding
     * JavaScript value object. NULL is returned if the conversion fails. Before using this function, obtain the
     * JavaScript API through OH_ArkWeb_GetNativeAPI and check the availability of the function pointer.
     *
     * @param type Type of the JavaScript value.
     * @param data Pointer to the data buffer of the JavaScript value. The data must be provided in the type
     *     corresponding to **type**. The memory is managed by the caller and must remain valid until the function
     *     returns. For types that do not require data, **nullptr** can be passed.
     * @param dataLength Number of bytes pointed to by the data buffer of the JavaScript value. This value must match
     *     the length of the buffer pointed to by **data**. When **data** is **nullptr**, this value must be set
     *     to **0**.
     * @return Created JavaScript value. NULL is returned when the input parameter is invalid or memory allocation
     *     fails.
     */
    ArkWeb_JavaScriptValuePtr (*createJavaScriptValue)(ArkWeb_JavaScriptValueType type, void* data, size_t dataLength);
} ArkWeb_JavaScriptValueAPI;

/**
 * @brief Check whether the member variables of the current struct exist.
 *
 * @since 12
 */
#define ARKWEB_MEMBER_EXISTS(s, f) \
    ((intptr_t) & ((s)->f) - (intptr_t)(s) + sizeof((s)->f) <= *(size_t *)(s))

/**
 * @brief Return false if the struct member does not exist, otherwise true.
 *
 * @since 12
 */
#define ARKWEB_MEMBER_MISSING(s, f) (!ARKWEB_MEMBER_EXISTS(s, f) || !((s)->f))

#ifdef __cplusplus
}
#endif
#endif // ARKWEB_TYPE_H
/** @} */