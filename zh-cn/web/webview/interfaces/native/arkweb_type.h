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
 * @brief 提供ArkWeb在Native侧的公共类型定义。
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
 * @brief ArkWeb_JavaScriptBridgeData是JavaScript桥接数据定义结构体，用于在Native代码和Web页面之间传递JavaScript桥接相关的数据。该结构体封装了桥接调用中的参数数据，
 * 是JavaScript桥接子系统中的基本数据单元，配合ArkWeb_ControllerAPI中的JavaScript Proxy注册接口使用。
 *
 * @since 12
 */
typedef struct {
    /**
     * 指向传输数据的指针。支持String和ArrayBuffer类型，其余类型会被json序列化后，以String类型传递。
     */
    const uint8_t* buffer;
    /**
     * 传输数据的长度。建议根据实际数据大小合理设置，与buffer的大小保持一致，避免过大或过小导致的性能或数据问题。
     */
    size_t size;
} ArkWeb_JavaScriptBridgeData;

/**
 * @brief Post Message数据类型。
 *
 * @since 12
 */
typedef enum ArkWeb_WebMessageType {
    /**
     * 错误数据。
     */
    ARKWEB_NONE = 0,
    /**
     * 字符串数据类型。
     */
    ARKWEB_STRING,
    /**
     * 字节流数据类型。
     */
    ARKWEB_BUFFER
} ArkWeb_WebMessageType;

/**
 * @brief JavaScript数据类型。
 *
 * @since 18
 */
typedef enum ArkWeb_JavaScriptValueType {
    /**
     * 错误数据。
     */
    ARKWEB_JAVASCRIPT_NONE = 0,
    /**
     * 字符串数据类型。
     */
    ARKWEB_JAVASCRIPT_STRING,
    /**
     * boolean数据类型。
     */
    ARKWEB_JAVASCRIPT_BOOL
} ArkWeb_JavaScriptValueType;

/**
 * @brief ArkWeb_WebMessage是用于跨上下文消息通信的Web消息结构体，定义了消息的基本格式和数据承载能力。该结构体是Web消息通信的基础数据单元，支持在Native代码和Web页面之间传递字符串和二进制数据。
 *
 * @since 12
 */
typedef struct ArkWeb_WebMessage* ArkWeb_WebMessagePtr;

/**
 * @brief ArkWeb_JavaScriptValue是用于在Native代码中封装JavaScript值的结构体，提供了JavaScript值的基本创建和操作能力。
 * 该结构体支持将Native数据转换为JavaScript可识别的格式，解决Native与JavaScript双向数据传递的类型安全与格式兼容问题，是JavaScript桥接通信中的数据传递基础类型，有助于减少手动转换成本、
 * 提升桥接通信效率并增强可维护性。
 *
 * @since 18
 */
typedef struct ArkWeb_JavaScriptValue* ArkWeb_JavaScriptValuePtr;

/**
 * @brief 注入的JavaScript执行完成的回调。用于获取JavaScript代码在Web组件中的执行结果，例如在需要根据JavaScript返回的数据更新原生UI或执行后续逻辑的场景中使用。
 *
 * @since 12
 */
typedef void (*ArkWeb_OnJavaScriptCallback)(
    const char* webTag, const ArkWeb_JavaScriptBridgeData* data, void* userData);

/**
 * @brief Proxy方法被执行的回调。Proxy方法用于Native侧与JavaScript侧的对象交互和自定义操作。
 *
 * @since 12
 */
typedef void (*ArkWeb_OnJavaScriptProxyCallback)(
    const char* webTag, const ArkWeb_JavaScriptBridgeData* dataArray, size_t arraySize, void* userData);

/**
 * @brief Proxy方法被执行的回调（有返回值）。用于在JavaScript调用注入的Proxy方法时接收通知并返回执行结果，适用于实现JavaScript与原生代码的桥接通信场景，例如拦截JavaScript调用、执行原生逻辑、
 * 计算结果并将结果返回给JavaScript。
 *
 * @param webTag Web组件名称。
 * @param dataArray 数组数据。
 * @param arraySize 数组大小。
 * @param userData 用户自定义的数据。
 * @since 18
 */
typedef ArkWeb_JavaScriptValuePtr (*ArkWeb_OnJavaScriptProxyCallbackWithResult)(
    const char* webTag, const ArkWeb_JavaScriptBridgeData* dataArray, size_t arraySize, void* userData);

/**
 * @brief 接收Web组件事件通知的回调。用于接收Web组件生命周期事件通知，例如页面加载完成、页面销毁、组件可见性变化等场景下的状态变更通知。
 *
 * @since 12
 */
typedef void (*ArkWeb_OnComponentCallback)(const char* webTag, void* userData);

/**
 * @brief Web组件滚动时的回调函数。
 *
 * @param webTag Web组件名称。
 * @param userData 用户自定义的数据。
 * @param x X轴滚动偏移。单位：vp。
 * @param y Y轴滚动偏移。单位：vp。
 * @since 18
 */
typedef void (*ArkWeb_OnScrollCallback)(const char* webTag, void* userData, double x, double y);

/**
 * @brief ArkWeb_WebMessagePort是Web消息端口结构体，表示MessageChannel的两个端口之一，用于发送和接收消息。该结构体支持在Native代码和Web页面之间进行双向消息通信。
 *
 * @since 12
 */
typedef struct ArkWeb_WebMessagePort* ArkWeb_WebMessagePortPtr;

/**
 * @brief 处理HTML发送过来的Post Message数据。
 *
 * @param webTag Web组件名称。
 * @param port Post Message端口。
 * @param message Post Message数据。
 * @param userData 用户自定义的数据。
 * @since 12
 */
typedef void (*ArkWeb_OnMessageEventHandler)(
    const char* webTag, const ArkWeb_WebMessagePortPtr port, const ArkWeb_WebMessagePtr message, void* userData);

/**
 * @brief Defines the javascript object.
 *
 * @since 12
 */
typedef struct {
    /**
     * 注入的JavaScript代码。该缓冲区长度需与size参数一致。
     */
    const uint8_t* buffer;
    /**
     * JavaScript代码长度。单位：字节。需与buffer的实际长度一致，否则可能导致越界或截断。
     */
    size_t size;
    /**
     * JavaScript执行完成的回调。回调函数指针，传入NULL表示不需要回调。
     */
    ArkWeb_OnJavaScriptCallback callback;
    /**
     * 需要在回调中携带的自定义数据。
     */
    void* userData;
} ArkWeb_JavaScriptObject;

/**
 * @brief ArkWeb_ProxyMethod是用于定义JavaScript代理方法的结构体，支持实现JavaScript与Native代码之间的安全通信，适用于需要从Web页面调用Native能力的场景。
 * 该结构体指定了一个可以从JavaScript调用的Native方法的基本信息，包含方法名称和对应的Native回调函数指针和需要携带的自定义数据三个字段。
 * 多个ArkWeb_ProxyMethod可以组合成ArkWeb_ProxyObject，以对象的形式整体注入到Web页面中，从而让Web应用能够方便地访问设备原生能力。
 *
 * @since 12
 */
typedef struct {
    /**
     * 注入的方法名。
     */
    const char* methodName;
    /**
     * JavaScript通过Proxy对象调用该方法时触发的回调函数，用于处理来自JavaScript的方法调用。回调函数中可以访问JavaScript传入的参数（dataArray）并执行相应的Native逻辑。
     */
    ArkWeb_OnJavaScriptProxyCallback callback;
    /**
     * 需要在回调中携带的自定义数据。
     */
    void* userData;
} ArkWeb_ProxyMethod;

/**
 * @brief ArkWeb_ProxyMethodWithResult是带返回值的JavaScript代理方法结构体，扩展了ArkWeb_ProxyMethod的能力，支持在JavaScript调用Native方法后获取返回值。
 * 该结构体在方法名称和回调函数的基础上，增加了返回值处理能力，适用于需要向Web前端返回执行结果的调用场景。
 *
 * @since 18
 */
typedef struct {
    /**
     * 注入的方法名。
     */
    const char* methodName;
    /**
     * JavaScript调用Native代理方法时执行的回调函数，用于处理方法调用并返回执行结果。该参数必须为有效的函数指针，不能为NULL。
     */
    ArkWeb_OnJavaScriptProxyCallbackWithResult callback;
    /**
     * 需要在回调中携带的自定义数据。
     */
    void* userData;
} ArkWeb_ProxyMethodWithResult;

/**
 * @brief ArkWeb_ProxyObject是注入到Web页面的JavaScript代理对象结构体，用于将一组相关的ArkWeb_ProxyMethod方法组织成对象整体暴露给Web前端。
 * 该结构体指定了对象在JavaScript中的名称（objName）、方法数组（methodList）和方法数量（size），使得Native应用可以向Web页面暴露结构化的API集合。
 * 代理对象通过方法映射机制将Native侧的ArkWeb_ProxyMethod与JavaScript侧的方法调用进行关联，支持方法参数和返回值的自动转换。
 *
 * @since 12
 */
typedef struct {
    /**
     * 注入的对象名，命名应遵循JavaScript标识符规则，不支持特殊字符。
     */
    const char* objName;
    /**
     * 注入的对象携带的方法结构体数组。
     */
    const ArkWeb_ProxyMethod* methodList;
    /**
     * 方法结构体数组的长度，必须与methodList数组的实际元素个数一致。
     */
    size_t size;
} ArkWeb_ProxyObject;

/**
 * @brief ArkWeb_ProxyObjectWithResult是带返回值的JavaScript代理对象结构体，扩展了ArkWeb_ProxyObject的能力。
 * 该结构体将多个ArkWeb_ProxyMethodWithResult组织成对象注入到Web页面中，支持JavaScript调用Native方法后获取返回值。解决了ArkWeb_ProxyObject无法返回执行结果的问题，
 * 简化了开发流程，提升了开发效率。适用于需要向Web前端返回结构化执行结果的API场景。
 *
 * @since 18
 */
typedef struct {
    /**
     * 注入的对象名，命名应遵循JavaScript标识符规则，不支持特殊字符。
     */
    const char* objName;
    /**
     * 注入的对象携带的方法结构体数组，数组长度由 size 参数指定。数组中的每个方法会被注册到Web页面中，JavaScript可通过“对象名.方法名”的方式进行调用。
     */
    const ArkWeb_ProxyMethodWithResult* methodList;
    /**
     * 方法结构体数组的长度，必须与methodList数组的实际元素个数一致。
     */
    size_t size;
} ArkWeb_ProxyObjectWithResult;

/**
 * @brief ArkWeb_ControllerAPI是Controller相关Native API结构体。该结构体提供了JavaScript注入、同步和异步JavaScript代理注册、代理删除、页面刷新、Web Message
 * Port创建和管理、Frame URL查询等功能，特点包括支持同步与异步代理并存、统一管理控制WebView行为。适用于需要从Native代码注入并调用JavaScript、实现Native与页面双向通信的场景，
 * 可解决JSBridge互通与安全注入问题，提升开发效率与可控性。这是从Native代码控制WebView行为的主要接口。<br>Controller相关接口需在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取，
 * 调用前建议通过{@link ARKWEB_MEMBER_MISSING}校验函数指针的可用性，避免SDK与设备ROM不匹配导致崩溃。
 *
 * @since 12
 */
typedef struct {
    /**
     * 结构体的大小。
     */
    size_t size;
    /**
     * 注入JavaScript脚本。需在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取该接口。该方法将JavaScript脚本注入到Web组件的执行上下文中，在页面加载完成后执行。
     */
    void (*runJavaScript)(const char* webTag, const ArkWeb_JavaScriptObject* javascriptObject);
    /**
     * 注入JavaScript对象到window对象中，并在window对象中调用该对象的同步方法。该方法通过桥接机制将Native对象映射到JavaScript环境，实现双向通信。使用场景：
     * 例如JS调用Native能力以获取设备信息、执行 Native 业务逻辑等。需在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取该接口。与registerAsyncJavaScriptProxy相比，
     * 此方法适用于需要同步获取返回值的场景。若不需要同步返回值或耗时操作，建议使用registerAsyncJavaScriptProxy以避免阻塞UI线程。
     */
    void (*registerJavaScriptProxy)(const char* webTag, const ArkWeb_ProxyObject* proxyObject);
    /**
     * 删除通过registerJavaScriptProxy注册到window上的指定name的应用侧JavaScript对象。需在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取该接口。
     * 该方法会解除JavaScript对象与Native对象的绑定，并释放相关资源。使用场景：例如组件销毁、模块卸载或切换业务时清理注册对象以避免残留。
     */
    void (*deleteJavaScriptRegister)(const char* webTag, const char* objName);
    /**
     * 刷新当前网页。刷新的同时会清理页面栈，导致当前页面无法前进后退。需在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取该接口。
     */
    void (*refresh)(const char* webTag);
    /**
     * 注入JavaScript对象到window对象中，并在window对象中调用该对象的异步方法。需在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取该接口。该方法通过消息队列机制实现异步调用，避免阻塞主线程。
     * 与registerJavaScriptProxy相比，此方法适用于耗时操作或不需要同步获取返回值的场景，若需要同步获取返回值，建议使用registerJavaScriptProxy。
     */
    void (*registerAsyncJavaScriptProxy)(const char* webTag, const ArkWeb_ProxyObject* proxyObject);
    /**
     * @brief 创建Post Message端口。Post Message端口提供双向通信机制，允许Native层与Web层安全地交换数据消息。需在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取该接口。
     * 使用场景：例如实现跨上下文消息通道，支持iframe与主页面、Web与Worker之间的数据传递。
     *
     * @param webTag Web组件名称。
     * @param size The quantity of message ports.
     */
    ArkWeb_WebMessagePortPtr* (*createWebMessagePorts)(const char* webTag, size_t* size);

    /**
     * @brief 销毁端口。该方法会关闭端口连接，释放相关系统资源，停止消息传输。需在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取该接口。使用场景：例如通信结束、组件生命周期结束时释放端口资源以避免泄漏。
     *
     * @param ports Post Message端口结构体指针数组。
     * @param size The quantity of message ports.
     */
    void (*destroyWebMessagePorts)(ArkWeb_WebMessagePortPtr** ports, size_t size);

    /**
     * @brief Post message ports to main frame.
     *
     * @param webTag The name of the web component.
     * @param name Name of the message to be sent.
     * @param size The quantity of message ports.
     * @param url Indicates the URI for receiving the message.
     * @return Post web message result code.
     *         {@link ARKWEB_SUCCESS} post web message success.
     *         {@link ARKWEB_INVALID_PARAM} the parameter verification fails.
     *         {@link ARKWEB_INIT_ERROR} no web associated with this webTag.
     */
    ArkWeb_ErrorCode (*postWebMessage)(
        const char* webTag, const char* name, ArkWeb_WebMessagePortPtr* webMessagePorts, size_t size, const char* url);

    /**
     * @brief 获取调用JavaScriptProxy最后一帧的url。该方法通过帧栈追踪机制，记录最后一次JavaScript调用的frame上下文。在JavaScriptProxy调用的线程上调用。
     * 通过registerJavaScriptProxy或者JavaScriptProxy注入JavaScript对象到window对象中。该接口可以获取最后一次调用注入对象frame的url，如果从未调用过注入对象，返回值未定义。
     * 在被调用函数内部获取url才能获取到正确值，可以在函数内部获取url后保存下来。需在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取该接口。
     *
     * @return 调用JavaScriptProxy最后一帧的url。
     * @since 14
     */
    const char* (*getLastJavascriptProxyCallingFrameUrl)();

    /**
     * @brief Register the JavaScript object and method list, the method is callback function that has a return value.
     *
     * @param webTag The name of the web component.
     * @param proxyObject The JavaScript object to register, the object has callback functions with return value.
     * @param permission The JSON string, which defaults to null, is used to configure the permission control for
     * JSBridge, allowing for the definition of URL whitelists at the object and method levels.
     *
     * @since 18
     */
    void (*registerJavaScriptProxyEx)(const char* webTag, const ArkWeb_ProxyObjectWithResult* proxyObject,
        const char* permission);

    /**
     * @brief Register the JavaScript object and async method list.
     *
     * @param webTag The name of the web component.
     * @param proxyObject The JavaScript object to register.
     * @param permission The JSON string, which defaults to null, is used to configure the permission control
     * for JSBridge, allowing for the definition of URL whitelists at the object and method levels.
     *
     * @since 18
     */
    void (*registerAsyncJavaScriptProxyEx)(const char* webTag, const ArkWeb_ProxyObject* proxyObject,
        const char* permission);
} ArkWeb_ControllerAPI;

/**
 * @brief ArkWeb_ComponentAPI是ArkWeb在Native侧提供的用于监听Web组件生命周期事件的API结构体，继承自基础Native API类型{@link ArkWeb_AnyNativeAPI}。
 * 开发者通过{@link OH_ArkWeb_GetNativeAPI}并指定`ARKWEB_NATIVE_COMPONENT`类型获取该结构体，进而注册Web组件的Controller绑定、页面开始加载、
 * 页面加载完成以及组件销毁等事件回调。该结构体适用于需要在Native代码（C/C++）中感知Web组件关键状态变化的场景，例如初始化Native资源、同步页面加载状态、统计埋点或在组件销毁时释放关联资源；相关接口需在UI线程中调用，
 * 并建议在调用具体成员函数前通过{@link ARKWEB_MEMBER_MISSING}宏校验函数指针是否存在。
 *
 * @since 12
 */
typedef struct {
    /**
     * 结构体的大小。
     */
    size_t size;
    /**
     * 注册Controller绑定事件的回调监听器。说明：该回调需在UI线程中调用，调用前建议通过ARKWEB_MEMBER_MISSING宏校验函数指针是否存在。
     */
    void (*onControllerAttached)(const char* webTag, ArkWeb_OnComponentCallback callback, void* userData);
    /**
     * 网页开始加载时触发该回调，该回调只在主frame触发，不会为iframe或frameset内容加载触发。该回调需在UI线程中调用，调用前建议通过ARKWEB_MEMBER_MISSING宏校验函数指针是否存在。
     */
    void (*onPageBegin)(const char* webTag, ArkWeb_OnComponentCallback callback, void* userData);
    /**
     * 网页加载完成时触发该回调，该回调只在主frame触发，不会为iframe或frameset内容加载触发。该回调需在UI线程中调用，调用前建议通过ARKWEB_MEMBER_MISSING宏校验函数指针是否存在。
     */
    void (*onPageEnd)(const char* webTag, ArkWeb_OnComponentCallback callback, void* userData);
    /**
     * 当前Web组件销毁时触发该回调。
     */
    void (*onDestroy)(const char* webTag, ArkWeb_OnComponentCallback callback, void* userData);
} ArkWeb_ComponentAPI;

/**
 * @brief ArkWeb_WebMessagePortAPI是Web消息端口相关Native API结构体。该结构体提供了消息端口的创建、关闭、消息发送和消息接收回调注册等功能。此API是postMessage桥接的核心组件，
 * 支持在Native代码和Web页面之间建立持久的双向通信通道。适用于需要在原生应用与Web页面之间进行数据交互的场景，解决了跨语言通信的难题，提升了应用的扩展能力和开发效率。<br>
 * Web消息端口相关接口需在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取，调用前建议通过{@link ARKWEB_MEMBER_MISSING}校验函数指针的可用性，避免SDK与设备ROM不匹配导致崩溃。
 *
 * @since 12
 */
typedef struct {
    /**
     * 结构体的大小（字节）。
     */
    size_t size;
    /**
     * @brief Post message to HTML.
     *
     * @param webMessagePort The ArkWeb_WebMessagePort.
     * @param webTag The name of the web component.
     * @param webMessage The ArkWeb_WebMessage to send.
     * @return Post message result code.
     *         {@link ARKWEB_SUCCESS} post message success.
     *         {@link ARKWEB_INVALID_PARAM} the parameter verification fails.
     *         {@link ARKWEB_INIT_ERROR} no web associated with this webTag.
     */
    ArkWeb_ErrorCode (*postMessage)(
        const ArkWeb_WebMessagePortPtr webMessagePort, const char* webTag, const ArkWeb_WebMessagePtr webMessage);
    /**
     * @brief 关闭消息端口。
     *
     * @param webMessagePort Post Message端口结构体指针。
     * @param webTag The name of the web component.
     */
    void (*close)(const ArkWeb_WebMessagePortPtr webMessagePort, const char* webTag);
    /**
     * @brief Set a callback to receive message from HTML.
     *
     * @param webMessagePort The ArkWeb_WebMessagePort.
     * @param webTag The name of the web component.
     * @param messageEventHandler The handler to receive message from HTML.
     * @param userData The data set by user.
     */
    void (*setMessageEventHandler)(const ArkWeb_WebMessagePortPtr webMessagePort, const char* webTag,
        ArkWeb_OnMessageEventHandler messageEventHandler, void* userData);
} ArkWeb_WebMessagePortAPI;

/**
 * @brief ArkWeb_WebMessageAPI是Web消息相关Native API结构体。该结构体提供了创建和销毁消息、设置和获取消息类型、管理消息数据缓冲区等函数。此API是postMessage桥接的一部分，
 * 支持Native代码与HTML页面之间的双向通信。<br>Web消息相关接口需在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取，调用前建议通过{@link ARKWEB_MEMBER_MISSING}
 * 校验函数指针的可用性，避免SDK与设备ROM不匹配导致崩溃。
 *
 * @since 12
 */
typedef struct {
    /**
     * 结构体的大小。
     */
    size_t size;
    /**
     *  @brief 创建消息。用于在Native代码与HTML页面之间进行postMessage通信前，创建待发送的消息对象。调用createWebMessage()后，必须在使用完毕后调用destroyWebMessage()
     * 释放消息资源，未调用destroyWebMessage()会导致消息资源泄漏，影响系统内存管理。
     *
     *  @return The created ArkWeb_WebMessage, destroy it through
     *  destroyWebMessage after it is no longer used.
     */
    ArkWeb_WebMessagePtr (*createWebMessage)();
    /**
     *  @brief 销毁消息，并释放消息对象占用的内存。必须与createWebMessage()成对使用，在使用完消息后调用此方法释放资源。调用后webMessage指针将变为无效，不应再被使用。
     *
     */
    void (*destroyWebMessage)(ArkWeb_WebMessagePtr* webMessage);
    /**
     *  @brief 设置消息类型。
     *
     */
    void (*setType)(ArkWeb_WebMessagePtr webMessage, ArkWeb_WebMessageType type);
    /**
     *  @brief 获取消息类型。用于区分不同类型的通信消息，如文本消息、JSON消息、二进制消息等。
     *
     */
    ArkWeb_WebMessageType (*getType)(ArkWeb_WebMessagePtr webMessage);
    /**
     *  @brief 设置数据。用于设置消息的具体内容，支持从Native代码向HTML页面传递文本、JSON或二进制数据。
     *
     */
    void (*setData)(ArkWeb_WebMessagePtr webMessage, void* data, size_t dataLength);
    /**
     *  @brief 获取数据。用于获取消息的具体内容，支持从HTML页面接收文本、JSON或二进制数据并在Native代码中处理。必须先调用setData()设置数据，然后才能调用getData()获取数据；
     * 如果未调用setData()就调用getData()，将返回NULL，且dataLength为0。
     *
     *  @param webMessage 消息结构体指针。
     *  @param dataLength 出参，数据长度。
     *  @return The data of ArkWeb_WebMessage.
     */
    void* (*getData)(ArkWeb_WebMessagePtr webMessage, size_t* dataLength);
} ArkWeb_WebMessageAPI;

/**
 * @brief ArkWeb_CookieManagerAPI是Cookie管理相关Native API结构体。该结构体提供了Cookie的读取、设置、清除和同步等操作能力，适用于需要在WebView组件中管理用户会话、
 * 跟踪用户首选项等场景，能够帮助开发者便捷地实现数据持久化和状态同步。<br>CookieManager相关接口需在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取，调用前建议通过
 * {@link ARKWEB_MEMBER_MISSING}校验函数指针的可用性，避免SDK与设备ROM不匹配导致崩溃。
 *
 * @since 12
 */
typedef struct {
    /**
     * 结构体的大小。
     */
    size_t size;

    /**
     * @brief Obtains the cookie value corresponding to a specified URL.
     *
     * @param url URL to which the cookie to be obtained belongs. A complete URL is recommended.
     * @param incognito True indicates that the memory cookies of the webview in privacy mode are obtained,
     *                  and false indicates that cookies in non-privacy mode are obtained.
     * @param includeHttpOnly If true HTTP-only cookies will also be included in the cookieValue.
     * @param cookieValue Get the cookie value corresponding to the URL.
     * @return Fetch cookie result code.
     *         {@link ARKWEB_SUCCESS} fetch cookie success.
     *         {@link ARKWEB_INVALID_URL} invalid url.
     *         {@link ARKWEB_INVALID_PARAM} cookieValue is nullptr.
     */
    ArkWeb_ErrorCode (*fetchCookieSync)(const char* url, bool incognito, bool includeHttpOnly, char** cookieValue);

    /**
     * @brief Sets the cookie value for a specified URL.
     *
     * @param url Specifies the URL to which the cookie belongs. A complete URL is recommended.
     * @param cookieValue The value of the cookie to be set.
     * @param incognito True indicates that cookies of the corresponding URL are set in privacy mode,
     *                  and false indicates that cookies of the corresponding URL are set in non-privacy mode.
     * @param includeHttpOnly If true, HTTP-only cookies can also be overwritten.
     * @return Config cookie result code.
     *         {@link ARKWEB_SUCCESS} config cookie success.
     *         {@link ARKWEB_INVALID_URL} invalid url.
     *         {@link ARKWEB_INVALID_COOKIE_VALUE} invalid cookie value.
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
     * @brief 清除所有cookies（包括持久化cookies和会话cookies）。用于用户退出登录、清除隐私数据、重置用户状态等场景。若仅需清除会话cookies，建议使用
     * {@link clearSessionCookiesSync}。该方法需在UI线程调用，调用前建议校验函数指针的可用性。
     *
     * @param incognito True indicates that all memory cookies of the webview are cleared in privacy mode,
     *                  and false indicates that persistent cookies in non-privacy mode are cleared.
     */
    void (*clearAllCookiesSync)(bool incognito);

    /**
     * @brief 清除所有会话cookies。用于清除临时会话数据、关闭所有会话、会话超时清理等场景。该方法需在UI线程调用，调用前建议校验函数指针的可用性。
     *
     */
    void (*clearSessionCookiesSync)();
} ArkWeb_CookieManagerAPI;

/**
 * @brief ArkWeb_JavaScriptValueAPI是JavaScript相关Native API结构体。该结构体提供了创建JavaScript值的函数，
 * 支持将Native数据转换为JavaScript可识别的格式并返回给HTML。该转换机制根据指定的JavaScript值类型对Native数据缓冲区进行解析和封装，生成对应的JavaScript值对象。
 * 适用于需要从Native层向Web层传递数据的应用场景，能够实现Native与Web之间的双向数据交互，提升应用开发灵活性。<br>在UI线程中调用OH_ArkWeb_GetNativeAPI方法获取JavaScript相关接口。
 * 调用前建议通过{@link ARKWEB_MEMBER_MISSING}校验函数指针的可用性，避免SDK与设备ROM不匹配导致崩溃。
 *
 * @since 18
 */
typedef struct {
    /**
     * 结构体的大小。
     */
    size_t size;

    /**
     * @brief 创建一个JavaScript值，用于返回给HTML。该函数根据指定的type参数对data缓冲区中的数据进行类型转换和封装，生成对应的JavaScript值对象，转换失败时返回NULL。
     * 使用前需通过OH_ArkWeb_GetNativeAPI获取JavaScript接口，并建议校验函数指针可用性。
     *
     * @param type JavaScript值的类型。
     * @param data JavaScript值的数据缓冲区。应按type对应的类型提供数据，内存由调用方管理并确保在返回前有效，对于无需数据的类型可传nullptr。
     * @param dataLength JavaScript值的数据缓冲区所指向的字节数。应与data所指向缓冲区长度一致，当data为nullptr时，该值应设为0。
     * @return ArkWeb_JavaScriptValuePtr created by ArkWeb, the memory of ArkWeb_JavaScriptValue
     * is managed by ArkWeb itself.
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