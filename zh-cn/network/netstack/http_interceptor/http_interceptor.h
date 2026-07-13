/*
 * Copyright (C) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup netstack
 * @{
 *
 * @brief 定义HTTP全局拦截器模块的接口。
 *
 * @since 24
 */

/**
 * @file http_interceptor.h
 * @brief 定义HTTP全局拦截器模块的接口，分为只读拦截器与可修改拦截器两类。通过全局只读拦截器，开发者可以监控应用内部通过所支持的系统网络组件发起的所有HTTP请求，实现日志记录功能，也可以在全局可修改拦截器中添加自定义逻辑，
 * 修改应用内部通过所支持的系统网络组件发起的HTTP请求的请求头、响应头、响应体。
 *
 * @library libhttp_interceptor.so
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetStack
 * @since 24
 */

#ifndef HTTP_INTERCEPTOR_H
#define HTTP_INTERCEPTOR_H

#include "http_interceptor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 添加一个HTTP全局只读拦截器。
 *
 * @param interceptor 待添加的拦截器，指向OH_Http_Interceptor结构体的指针。
 * @return 返回值为0表示执行成功；返回值为201表示权限被拒绝；返回值为401表示参数错误。
 * @permission ohos.permission.INTERNET
 * @note The interceptor remains active until it is explicitly removed by the developer.
 *     you must call {@link OH_Http_RemoveInterceptor} to release a specific interceptor
 *     or {@link OH_Http_RemoveAllInterceptors} to release a group of interceptors.
 * @since 24
 */
int32_t OH_Http_AddReadOnlyInterceptor(struct OH_Http_Interceptor *interceptor);

/**
 * @brief 添加一个HTTP全局可修改拦截器。
 *
 * @param interceptor 待添加的拦截器，指向OH_Http_Interceptor结构体的指针。
 * @return 返回值为0表示执行成功；返回值为201表示权限被拒绝；返回值为401表示参数错误。
 * @permission ohos.permission.INTERNET
 * @note The interceptor remains active until it is explicitly removed by the developer.
 *     you must call {@link OH_Http_RemoveInterceptor} to release a specific interceptor
 *     or {@link OH_Http_RemoveAllInterceptors} to release a group of interceptors.
 * @since 26.0.0
 */
int32_t OH_Http_AddWritableInterceptor(struct OH_Http_Interceptor *interceptor);

/**
 * @brief 删除指定的HTTP全局拦截器。
 *
 * @param interceptor 待删除的拦截器，指向OH_Http_Interceptor结构体的指针。
 * @return 返回值为0表示执行成功；返回值为201表示权限被拒绝；返回值为401表示参数错误。
 * @permission ohos.permission.INTERNET
 * @since 24
 */
int32_t OH_Http_RemoveInterceptor(struct OH_Http_Interceptor *interceptor);

/**
 * @brief 删除指定组ID的所有HTTP拦截器。
 *
 * @param groupId 拦截器组ID。
 * @return 返回值为0表示执行成功；返回值为201表示权限被拒绝；返回值为401表示参数错误。
 * @permission ohos.permission.INTERNET
 * @note The groupId is allocated and managed by the application itself when creating
 *     interceptors. If multiple modules within the application need to use interceptors,
 *     the application must properly allocate and manage groupId to avoid conflicts.
 *     Conflicts in groupId between internal modules may lead to accidental deletion
 *     of interceptors when calling this function.
 * @since 24
 */
int32_t OH_Http_RemoveAllInterceptors(int32_t groupId);

/**
 * @brief 启用指定组ID的所有HTTP拦截器。
 *
 * @param groupId http global interceptor group id
 * @return {@link OH_HTTP_RESULT_OK} 0 -if the operation is successful.
 *     {@link OH_HTTP_PERMISSION_DENIED} 201 -if permission is denied.
 * @permission ohos.permission.INTERNET
 * @since 24
 */
int32_t OH_Http_StartAllInterceptors(int32_t groupId);

/**
 * @brief 停用指定组ID的所有HTTP拦截器。
 *
 * @param groupId http global interceptor group id
 * @return {@link OH_HTTP_RESULT_OK} 0 -if the operation is successful.
 *     {@link OH_HTTP_PERMISSION_DENIED} 201 -if permission is denied.
 * @permission ohos.permission.INTERNET
 * @since 24
 */
int32_t OH_Http_StopAllInterceptors(int32_t groupId);

#ifdef __cplusplus
}
#endif
#endif // HTTP_INTERCEPTOR_H

/** @} */