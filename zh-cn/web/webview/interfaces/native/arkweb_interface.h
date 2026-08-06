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
 * @file arkweb_interface.h
 *
 * @brief `arkweb_interface.h`是ArkWeb在Native侧（C/C++）的核心入口头文件：它定义了基础Native API类型{@link ArkWeb_AnyNativeAPI}与API类型枚举
 * {@link ArkWeb_NativeAPIVariantKind}，并提供{@link OH_ArkWeb_GetNativeAPI}接口用于按需获取Controller、Component、
 * CookieManager等具体Native API结构体，同时提供{@link OH_ArkWeb_RegisterScrollCallback}用于注册Web组件滚动事件回调；当开发者需要在Native代码中控制Web组件行为（
 * 如执行JavaScript、管理Cookie、监听组件生命周期或滚动事件）时，应首先通过本头文件获取对应的Native API，而页面渲染显示等能力仍需由ArkTS侧的Web组件提供。
 *
 * @kit ArkWeb
 * @library libohweb.so
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */

#ifndef ARKWEB_INTERFACE_H
#define ARKWEB_INTERFACE_H

#include "arkweb_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ArkWeb_AnyNativeAPI是ArkWeb Native API的基础结构体类型，用于统一表示通过{@link OH_ArkWeb_GetNativeAPI}接口获取到的各类Native API结构体指针。
 * 该结构体包含一个size_t类型的size成员，用于记录当前结构体的大小。
 *
 * @since 12
 */
typedef struct {
    /**
     * 结构体对应的大小。
     */
    size_t size;
} ArkWeb_AnyNativeAPI;

/**
 * @brief 定义Native API的类型枚举。
 *
 * @since 12
 */
typedef enum {
    /**
     * Component相关API类型。
     */
    ARKWEB_NATIVE_COMPONENT,
    /**
     * Controller相关API类型。
     */
    ARKWEB_NATIVE_CONTROLLER,
    /**
     * WebMessagePort相关API类型。
     */
    ARKWEB_NATIVE_WEB_MESSAGE_PORT,
    /**
     * WebMessage相关API类型。
     */
    ARKWEB_NATIVE_WEB_MESSAGE,
    /**
     * CookieManager相关API类型。
     */
    ARKWEB_NATIVE_COOKIE_MANAGER,
    /**
     * @brief API type related to ArkWeb JavaScript value.
     *
     * @since 18
     */
    ARKWEB_NATIVE_JAVASCRIPT_VALUE
} ArkWeb_NativeAPIVariantKind;

/**
 * @brief 根据传入的API类型，获取对应的Native API结构体。用于在Native代码中获取Controller以控制Web组件行为、获取CookieManager以管理Cookie、
 * 获取WebMessagePort以实现消息通信、获取JavaScriptValue以操作JavaScript对象等场景。
 *
 * @param type ArkWeb支持的Native API类型，不同API类型可能需要不同系统版本支持，详见枚举类型说明。
 *     <br>返回值使用说明：返回的指针由系统管理，无需开发者手动释放；多次调用相同参数可能返回同一指针；返回的Native API结构体在Web组件生命周期内有效；使用时请确保线程安全。
 * @return 根据传入的API类型，返回对应的Native API结构体指针，结构体第一个成员为当前结构体的大小，可用于访问Controller、Component、CookieManager等具体的Native API功能。
 *     若传入的API类型在当前系统版本不支持（如ARKWEB_NATIVE_JAVASCRIPT_VALUE在18以下版本不可用），则返回NULL。
 * @syscap SystemCapability.Web.Webview.Core
 * @since 12
 */
ArkWeb_AnyNativeAPI* OH_ArkWeb_GetNativeAPI(ArkWeb_NativeAPIVariantKind type);

/**
 * @brief 注册组件滚动时的回调函数。用于监测用户滚动行为以实现懒加载、检测滚动位置以实现回到顶部功能、记录用户浏览行为用于数据分析、实现滚动时的视觉特效等场景。
 *
 * @param webTag Web组件的名称。
 * @param callback 页面滚动时的回调函数。
 * @param userData 用户自定义的数据。
 * @return 如果回调设置成功，则返回true，否则返回false。
 * @since 18
 */
bool OH_ArkWeb_RegisterScrollCallback(
    const char* webTag, ArkWeb_OnScrollCallback callback, void* userData);

#ifdef __cplusplus
};
#endif
#endif // ARKWEB_INTERFACE_H
/** @} */