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
 * @brief 提供ArkWeb Native API的核心入口，支持JavaScript执行与代理注入。
 * @since 11
 */
/**
 * @file native_interface_arkweb.h
 *
 * @brief native_interface_arkweb.h是ArkWeb Native API的核心入口头文件，定义了应用与ArkWeb引擎交互所需的枚举、结构体和NDK函数接口，涵盖JavaScript执行与代理注入、
 * Cookie管理、无白屏加载控制、内核版本选择等功能。该模块适用于需要通过Native方式与Web组件进行深度交互的场景，解决了ArkWeb组件的复杂能力（如JavaScript双向通信、Cookie持久化、内核版本切换）
 * 在ArkTS层无法直接调用的技术难题，为开发者提供了完整的底层控制能力，能够实现高性能、可定制的Web组件功能。
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
 * @brief 定义执行JavaScript代码后返回结果的回调函数的类型。
 *
 * @since 11
 */
typedef void (*NativeArkWeb_OnJavaScriptCallback)(const char*);

/**
 * @brief 定义注入对象的回调函数的类型。
 *
 * @since 11
 */
typedef char* (*NativeArkWeb_OnJavaScriptProxyCallback)(const char** argv, int32_t argc);

/**
 * @brief 定义Web组件可用时的回调函数的类型。
 *
 * @since 11
 */
typedef void (*NativeArkWeb_OnValidCallback)(const char*);

/**
 * @brief 定义Web组件销毁时的回调函数的类型。
 *
 * @since 11
 */
typedef void (*NativeArkWeb_OnDestroyCallback)(const char*);

/**
 * @brief 定义保存cookie的回调函数的类型。
 *
 * @param errorCode {@link ARKWEB_SUCCESS} 保存cookie成功。
 *     <br>{@link ARKWEB_COOKIE_SAVE_FAILED} 保存cookie失败。
 *     <br>{@link ARKWEB_COOKIE_MANAGER_INITIALIZE_FAILED} CookieManager初始化失败。
 * @since 20
 */
typedef void (*OH_ArkWeb_OnCookieSaveCallback)(ArkWeb_ErrorCode errorCode);

/**
 * @brief 定义在获取cookie操作完成时调用的回调函数类型。
 *
 * @param errorCode 获取cookie回调错误码。
 *     <br>{@link ARKWEB_SUCCESS} 获取cookie成功。
 *     <br>{@link ARKWEB_INVALID_URL} 无效的URL。
 *     <br>{@link ARKWEB_LIBRARY_OPEN_FAILURE} 打开动态链接库失败。
 *     <br>{@link ARKWEB_LIBRARY_SYMBOL_NOT_FOUND} 动态链接库中找不到所需的符号。
 * @param cookieValue 获取与URL对应的cookies。函数将为cookieValue分配内存，开发者必须通过{@link OH_ArkWeb_ReleaseString}释放该字符串。
 * @since 26.0.0
 */
typedef void (*OH_ArkWeb_OnCookieFetchCallback)(ArkWeb_ErrorCode errorCode, char* cookieValue);

/**
 * @brief 页面首屏加载预测信息，主要包括首屏相似度预测值、首屏加载耗时预测值、错误码，应用需根据此信息来决策是否启用无白屏加载插帧方案（该方案通过在页面加载过程中插入预渲染帧来减少白屏时间）。
 *
 * @since 20
 */
typedef struct {
    /**
     * 无白屏加载的错误码，取值为0表示无错误，非0值表示错误类型，见{@link ArkWeb_BlanklessErrorCode}定义。
     */
    ArkWeb_BlanklessErrorCode errCode;
    /**
     * 首屏相似度，根据历史加载首屏内容计算相似度，范围为[0, 1.0]，1.0表示完全一致，数值越接近1，相似度越高。该值存在滞后性，本地加载的相似度将在下次加载时才可反映。建议当相似度低于具体阈值（如0.33）时，
     * 应用不启用无白屏加载插帧方案。
     */
    double similarity;
    /**
     * 根据历史加载首屏耗时预测本次加载耗时，单位：ms，取值范围需大于0。
     */
    int32_t loadingTime;
} ArkWeb_BlanklessInfo;

/**
 * @brief ArkWeb内核版本，请参考{@link M114内核在OpenHarmony 6.0系统上的适配指导}，{@link M132内核在OpenHarmony 7.0系统上的适配指导}。
 *
 * @since 20
 */
typedef enum {
    /**
     * @brief 系统默认内核（可参考{@link 约束与限制}），OpenHarmony 6.0版本默认为M132，OpenHarmony 7.0版本默认为M144。
     *
     * @since 20
     */
    SYSTEM_DEFAULT = 0,

    /**
     * @brief OpenHarmony 6.0版本的遗留内核。开发者可选择此遗留内核，若系统版本上不存在此内核则设置无效，使用系统默认内核。
     *
     * @since 20
     */
    ARKWEB_M114 = 1,

    /**
     * @brief OpenHarmony 6.0版本的常青内核（OpenHarmony 7.0版本的遗留内核），M132为OpenHarmony 6.0版本的默认内核。若系统版本上不存在此内核则设置无效，使用系统默认内核。
     *
     * @since 20
     */
    ARKWEB_M132 = 2,

    /**
     * @brief OpenHarmony 7.0版本的常青内核，M144为OpenHarmony 7.0版本的默认内核。若系统版本上不存在此内核则设置无效，使用系统默认内核。
     *
     * @since 26.0.0
     */
    ARKWEB_M144 = 3,

    /**
     * @brief 系统的最新内核（常青内核）。开发者可选择在每个系统版本上都使用最新的内核。
     *
     * @since 23
     */
    ARKWEB_EVERGREEN = 99999
} ArkWebEngineVersion;

/**
 * @brief 在当前显示页面的环境下，加载并异步执行一段JavaScript代码。此函数应在主线程中调用。**使用场景**：需要在Native层动态修改页面内容、获取页面运行时信息、与页面JavaScript交互时使用，
 * 例如获取表单数据、执行自定义脚本等。
 *
 * @param webTag Web组件的名称。
 * @param jsCode 一段JavaScript的代码脚本。
 * @param callback 代码执行完后通知开发者结果的回调函数。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
void OH_NativeArkWeb_RunJavaScript(const char* webTag, const char* jsCode, NativeArkWeb_OnJavaScriptCallback callback);

/**
 * @brief 注册对象及函数名称列表，用于向Web页面注入Native对象，实现应用侧与前端页面的双向通信。用于Web页面调用Native功能、Native代码控制Web页面行为、混合应用中的跨层交互等场景。
 *
 * @param webTag Web组件的名称。
 * @param objName 注入对象的名称。
 * @param methodList 注入函数列表的名称。
 * @param callback 注入的回调函数。
 * @param size 注入的回调函数的个数。
 * @param needRefresh 是否需要刷新页面。true：刷新页面，false：不刷新页面。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
void OH_NativeArkWeb_RegisterJavaScriptProxy(const char* webTag, const char* objName, const char** methodList,
    NativeArkWeb_OnJavaScriptProxyCallback* callback, int32_t size, bool needRefresh);

/**
 * @brief 删除已注册的对象及其下的回调函数，用于清理不再需要的JavaScript注入对象。典型使用场景：页面销毁时清理注入对象、功能模块卸载时移除对应的Native接口、防止内存泄漏等场景。
 *
 * @param webTag Web组件的名称。
 * @param objName 注入对象的名称。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
void OH_NativeArkWeb_UnregisterJavaScriptProxy(const char* webTag, const char* objName);

/**
 * @brief 设置对象可注册时的回调函数。需要在JavaScript代理对象成功注册后执行特定逻辑时使用，例如注册成功后通知页面或记录日志。
 *
 * @param webTag Web组件的名称。
 * @param callback 对象可注册时的回调函数。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
void OH_NativeArkWeb_SetJavaScriptProxyValidCallback(const char* webTag, NativeArkWeb_OnValidCallback callback);

/**
 * @brief 获取已注册的对象可注册时的回调函数。
 *
 * @param webTag Web组件的名称。
 * @return 已注册的对象可注册时的回调函数。如果未设置由参数webTag指定的有效回调函数，则将返回空指针。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
NativeArkWeb_OnValidCallback OH_NativeArkWeb_GetJavaScriptProxyValidCallback(const char* webTag);

/**
 * @brief 设置Web组件销毁时的回调函数。典型使用场景：需要在Web组件销毁时释放资源、清理状态或执行收尾操作时使用，例如释放JavaScript代理对象、取消网络请求、关闭文件句柄等。
 *
 * @param webTag Web组件的名称。
 * @param callback Web组件销毁时的回调函数。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
void OH_NativeArkWeb_SetDestroyCallback(const char* webTag, NativeArkWeb_OnDestroyCallback callback);

/**
 * @brief 获取已注册的Web组件销毁时的回调函数。
 *
 * @param webTag Web组件的名称。
 * @return 返回已注册的Web组件销毁时的回调函数。如果未设置由参数webTag指定的销毁回调函数，则将返回空指针。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 11
 */
NativeArkWeb_OnDestroyCallback OH_NativeArkWeb_GetDestroyCallback(const char* webTag);

/**
 * @brief 加载数据或URL，此函数应在主线程中调用。典型使用场景：从网络或本地文件加载页面内容、动态生成HTML内容并显示、实现离线页面展示、自定义页面渲染等。
 *
 * @param webTag Web组件的名称。
 * @param data "Base64"或"URL"编码的字符串，不能为空。
 * @param mimeType 媒体类型，例如"text/html"，不能为空。
 * @param encoding 编码类型，例如"UTF-8"，不能为空。
 * @param baseUrl 指定的URL路径("http"/"https"/"data"协议)，由Web组件分配给window.origin。
 * @param historyUrl 历史URL，当它不为空时，可以通过历史记录来管理，实现前进和后退功能。
 * @return OH_NativeArkWeb_LoadData 错误码。
 *     <br>{@link ARKWEB_SUCCESS} 加载数据成功。
 *     <br>{@link ARKWEB_INVALID_PARAM} 必填参数未指定或参数类型不正确或参数校验失败。
 *     <br>{@link ARKWEB_INIT_ERROR} 初始化失败，根据传入的"webTag"找不到有效的Web组件。
 *     <br>{@link ARKWEB_LIBRARY_OPEN_FAILURE} 打开动态链接库失败。请检查库文件路径是否正确、库文件是否损坏、是否有足够的访问权限。
 *     <br>{@link ARKWEB_LIBRARY_SYMBOL_NOT_FOUND} 动态链接库中未找到所需的符号。
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
 * @brief 注册一个包含回调方法的 JavaScript 对象，这些方法可带有返回值。该对象将被注入到当前页面的所有frame中，包括所有的 iframe，并且可以通过在 ArkWeb_ProxyObjectWithResult
 * 中指定的名称进行访问。该对象只会在下一次加载或重新加载页面后在 JavaScript 中生效。这些方法将在 ArkWeb 的工作线程中执行。典型使用场景：可在工作线程中处理JavaScript调用并返回结果时使用。例如执行耗时计算、
 * 异步任务处理、复杂业务逻辑处理等场景，避免阻塞主线程。
 *
 * @param webTag Web组件名称。
 * @param proxyObject 注册的对象。
 * @param permission json格式字符串，默认值为空。该字符串用来配置JSBridge的权限限制，可以配置对象和方法级别。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 20
 */
void OH_NativeArkWeb_RegisterAsyncThreadJavaScriptProxy(const char* webTag,
    const ArkWeb_ProxyObjectWithResult* proxyObject, const char* permission);

/**
 * @brief 设置无白屏加载是否启用。本接口必须与OH_NativeArkWeb_GetBlanklessInfoWithKey接口配套使用。
 *
 * @permission ohos.permission.INTERNET and ohos.permission.GET_NETWORK_INFO
 * @param webTag Web组件名称。
 * @param key 唯一标识本页面的key值。必须与{@link OH_NativeArkWeb_GetBlanklessInfoWithKey}接口的key值相同。
 *     <br>合法取值范围：非空，长度不超过2048个字符。
 *     <br>非法值设置行为：返回错误码{@link ArkWeb_BlanklessErrorCode}，插帧不生效。
 * @param isStarted 是否启用插帧。true：启用插帧，当页面首屏相似度较高且需要减少白屏时间以提升加载体验时选择；false：不启用插帧，当页面跳变过大导致相似度较低或不需要优化加载体验时选择。
 *     <br>默认值：false。
 * @return 返回错误码，具体见{@link ArkWeb_BlanklessErrorCode}定义。
 * @since 20
 */
ArkWeb_BlanklessErrorCode OH_NativeArkWeb_SetBlanklessLoadingWithKey(const char* webTag,
                                                                     const char* key,
                                                                     bool isStarted);

/**
 * @brief 清除指定key值页面无白屏优化缓存，本接口只清除缓存。
 * <br>在小程序或Web应用场景中，当页面加载时内容变化显著，可能会出现一次明显的跳变。若对此跳变有所顾虑，可使用该接口清除页面缓存。
 *
 * @param key 清除Blankless优化方案页面的key值列表，key值为{@link OH_NativeArkWeb_GetBlanklessInfoWithKey}中指定过的。
 *     <br>合法取值范围：长度不超过2048，keys数组长度<=100。key和加载页面时输入给ArkWeb的相同。
 *     <br>非法值设置行为：key长度超过2048时该key不生效；长度超过100时，取前100个；当为NULL时，清除所有缓存。
 * @param size keys数组的大小。
 *     <br>合法取值范围：0~100。取值超过100时，keys数组取前100个。
 *     <br>非法值设置行为：取值大于100时，取前100个。
 * @since 20
 */
void OH_NativeArkWeb_ClearBlanklessLoadingCache(const char* key[], uint32_t size);

/**
 * @brief 获取页面首屏加载预测信息（详细说明见{@link ArkWeb_BlanklessInfo}），并开始本次加载过渡帧生成，应用根据此信息确定是否需要启用无白屏加载。必须与
 * {@link OH_NativeArkWeb_SetBlanklessLoadingWithKey}接口配套使用，并且必须在触发加载页面的接口之前调用。需在WebViewController与Web组件绑定后才能使用。
 *
 * @permission ohos.permission.INTERNET and ohos.permission.GET_NETWORK_INFO
 * @param webTag Web组件名称。
 * @param key 唯一标识本页面的key值。
 *     <br>合法取值范围：非空，长度不超过2048个字符。
 *     <br>设置非法值时不生效。
 * @return 页面首屏加载预测信息，主要包括首屏相似度预测值，首屏加载耗时预测值，应用需根据此信息来决策是否启用无白屏加载插帧。
 * @since 20
 */
ArkWeb_BlanklessInfo OH_NativeArkWeb_GetBlanklessInfoWithKey(const char* webTag, const char* key);

/**
 * @brief 设置无白屏加载方案的持久化缓存容量，返回实际生效值。默认缓存容量为30MB，最大值为100MB。当实际缓存超过容量时，将采用淘汰不常用的过渡帧的方式清理。典型使用场景：根据应用内存占用情况调整缓存大小、优化存储空间使用、
 * 平衡无白屏效果与系统资源消耗等。
 *
 * @param capacity 设置持久化缓存容量，单位MB，最大设置不超过100MB。
 *     <br>默认值：30MB。
 *     <br>合法取值范围：0~100，当设置为0时，无缓存空间，则功能全局不开启。
 *     <br>非法值处理行为：大于100时生效值为100。
 * @return 返回实际生效的容量值，单位为MB，范围0~100。
 *     <br>大于100时生效值为100。
 * @since 20
 */
uint32_t OH_NativeArkWeb_SetBlanklessLoadingCacheCapacity(uint32_t capacity);

/**
 * @brief 将当前可通过CookieManager API访问的所有cookie持久化到磁盘。如果要在非UI线程中使用此接口，则需要先使用{@link OH_ArkWeb_GetNativeAPI}
 * 初始化CookieManager接口。典型使用场景：可在应用退出或特定时机保存cookie状态时使用。例如保存用户登录状态、应用配置信息、会话数据等，确保应用重启后能够恢复之前的状态。
 *
 * @return OH_ArkWebCookieManager_SaveCookieSync 错误码。请检查磁盘空间是否充足、是否有写入权限、cookie数据格式是否正确。
 *     <br>{@link ARKWEB_SUCCESS} 保存cookie成功。
 *     <br>{@link ARKWEB_COOKIE_SAVE_FAILED} 保存cookie失败。
 *     <br>{@link ARKWEB_COOKIE_MANAGER_INITIALIZE_FAILED} CookieManager初始化失败。
 *     <br>{@link ARKWEB_COOKIE_MANAGER_NOT_INITIALIZED} 在非UI线程中，不允许在不初始化CookieManager接口的情况下调用该接口。请先使用
 *     {@link OH_ArkWeb_GetNativeAPI}初始化CookieManager接口。
 * @since 20
 */
ArkWeb_ErrorCode OH_ArkWebCookieManager_SaveCookieSync();

/**
 * @brief 将当前可通过CookieManager API访问的所有cookie持久化到磁盘。如果要在非UI线程中使用此接口，则需要先使用{@link OH_ArkWeb_GetNativeAPI}
 * 初始化CookieManager接口；在不初始化CookieManager接口的情况下，此接口将在UI线程上自动执行。典型使用场景：需要异步保存cookie状态时使用，例如在页面加载完成、用户操作完成后异步保存cookie，
 * 避免阻塞主线程。
 *
 * @param callback 保存cookie成功或失败后执行该回调。传入callback时使用回调方式异步接收操作结果，适用于需要异步通知保存结果的场景；不传入时根据具体实现可能有不同的行为。
 * @since 20
 */
void OH_ArkWebCookieManager_SaveCookieAsync(OH_ArkWeb_OnCookieSaveCallback callback);

/**
 * 设置ArkWeb内核版本。若系统不支持指定版本，则设置无效，使用系统默认内核（可参考{@link 约束与限制}）。需要根据应用兼容性需求选择特定内核版本时使用，例如应用依赖某些旧版本内核的特性，或需要在新版本系统上保持兼容性，
 * 可以指定使用特定的遗留内核版本。<br>该接口为全局静态方法，须在调用initializeWebEngine前执行，若已加载任何Web组件，则该设置无效。
 * @param { ArkWebEngineVersion } webEngineVersion - ArkWeb内核版本。
 *     详细说明见 {@link ArkWebEngineVersion}.
 * @since 20
 */
void OH_NativeArkWeb_SetActiveWebEngineVersion(ArkWebEngineVersion webEngineVersion);

/**
 * 获取当前使用的ArkWeb内核版本。
 * @return 返回由{@link ArkWebEngineVersion}枚举所定义的当前使用的ArkWeb内核版本。
 * @since 20
 */
ArkWebEngineVersion OH_NativeArkWeb_GetActiveWebEngineVersion();

/**
 * 设置是否延后初始化ArkWeb内核，不调用该方法时，默认不延后初始化ArkWeb内核。典型使用场景：应用启动时暂不需要使用Web功能，希望延迟内核初始化以节省启动资源；
 * 应用只需要使用CookieManager而暂时不需要Web组件渲染等。该接口为全局静态方法，须在使用ArkWeb组件和初始化ArkWeb内核前调用，否则该设置无效。
 * @param { bool } lazy - 是否延后初始化ArkWeb内核，true：延后，false：不延后。
 * @since 22
 */
void OH_NativeArkWeb_LazyInitializeWebEngineInCookieManager(bool lazy);

/**
 * 判断应用所使用ArkWeb内核是否是常青内核，即系统的最新内核。
 * @return 返回当前应用所使用内核是否为常青内核。true表示是常青内核，false表示不是常青内核。
 * @since 23
 */
bool OH_NativeArkWeb_IsActiveWebEngineEvergreen();

/**
 * @brief 获取指定URL对应的cookies。如果要在非UI线程中使用此接口，则需要先使用{@link OH_ArkWeb_GetNativeAPI}初始化CookieManager接口。
 *
 * @param url 指定cookie所属的URL。建议填写完整的URL。
 * @param incognito true表示获取隐私模式下webview的内存cookie, false表示获取非隐私模式下的cookie。
 * @param includeHttpOnly true表示标记为HTTP-Only属性的cookie也将包含在cookieValue中，false表示不包含。
 * @param includePartitionedCookies true表示第一方partitioned cookies也将包含在cookieValue中，false表示不包含。
 * @param cookieValue 获取与URL对应的cookie值。函数将为cookieValue分配内存，开发者必须通过{@link OH_ArkWeb_ReleaseString}释放该字符串。
 * @return 返回值错误码。
 *     <br>{@link ARKWEB_SUCCESS} 获取cookie成功。
 *     <br>{@link ARKWEB_INVALID_URL} 无效的URL。
 *     <br>{@link ARKWEB_INVALID_PARAM} 参数无效。
 *     <br>{@link ARKWEB_COOKIE_MANAGER_NOT_INITIALIZED} 在非UI线程中，不允许在不初始化CookieManager接口的情况下调用该接口。
 *     请先使用OH_ArkWeb_GetNativeAPI初始化CookieManager接口。
 *     <br>{@link ARKWEB_LIBRARY_OPEN_FAILURE} 打开动态链接库失败。
 *     <br>{@link ARKWEB_LIBRARY_SYMBOL_NOT_FOUND} 动态链接库中找不到所需的符号。
 * @since 26.0.0
 */
ArkWeb_ErrorCode OH_ArkWebCookieManager_FetchCookieSync(const char* url, bool incognito, bool includeHttpOnly,
    bool includePartitionedCookies, char** cookieValue);

/**
 * @brief 异步获取指定URL对应的cookies。在不初始化CookieManager接口的情况下，此接口将在UI线程上自动执行。
 *
 * @param url 指定cookie所属的URL。建议填写完整的URL。
 * @param incognito true表示获取隐私模式下webview的内存cookie, false表示获取非隐私模式下的cookie。
 * @param includeHttpOnly true表示标记为HTTP-Only属性的cookie也将包含在cookieValue中，false表示不包含。
 * @param includePartitionedCookies true表示第一方partitioned cookies也将包含在cookieValue中，false表示不包含。
 * @param callback 获取cookies完成后执行该回调。
 * @since 26.0.0
 */
void OH_ArkWebCookieManager_FetchCookieAsync(const char* url, bool incognito, bool includeHttpOnly,
    bool includePartitionedCookies, OH_ArkWeb_OnCookieFetchCallback callback);

#ifdef __cplusplus
};
#endif
#endif // NATIVE_INTERFACE_ARKWEB_H
/** @} */