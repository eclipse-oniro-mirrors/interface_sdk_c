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
 * @file http_interceptor_type.h
 * @brief 为HTTP全局拦截器模块提供C接口的数据结构定义，包含拦截器的请求/响应头信息、HTTP请求/响应数据包结构、拦截器配置信息以及相关的枚举类型和函数指针。
 *
 * @library libhttp_interceptor.so
 * @kit NetworkKit
 * @syscap SystemCapability.Communication.NetStack
 * @since 24
 */

#ifndef HTTP_INTERCEPTOR_TYPE_H
#define HTTP_INTERCEPTOR_TYPE_H

#include <stdint.h>
#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif
#include "net_http_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义拦截器的请求/响应头信息。
 *
 * @since 24
 */
typedef struct OH_Http_Interceptor_Headers {
    /** 
     * @brief 拦截器请求/响应头信息。
     * 
     * @since 24
     */
    char *data;
    /** 
     * @brief 指向下一个头信息的指针。
     *     
     * @since 24
     */
    struct OH_Http_Interceptor_Headers *next;
} OH_Http_Interceptor_Headers;

/**
 * @brief 定义拦截器的HTTP请求数据包结构。
 *
 * @since 24
 */
typedef struct OH_Http_Interceptor_Request {
    /** 
     * @brief 请求URL，详情请参考{@link Http_Buffer}定义。
     * 
     * @since 24
     */
    Http_Buffer url;
    /** 
     * @brief 请求方法，详情请参考{@link Http_Buffer}定义。
     *
     * @since 24
     */
    Http_Buffer method;
    /** 
     * @brief HTTP请求头信息，详情请参考{@link OH_Http_Interceptor_Headers}定义。
     *
     * @since 24
     */
    OH_Http_Interceptor_Headers *headers;
    /** 
     * @brief 请求体内容，详情请参考{@link Http_Buffer}定义。
     * 
     * @since 24
     */
    Http_Buffer body;
} OH_Http_Interceptor_Request;

/**
 * @brief 定义拦截器的HTTP响应数据包结构。
 *
 * @since 24
 */
typedef struct OH_Http_Interceptor_Response {
    /** 
     * @brief 响应体内容，详情请参考{@link Http_Buffer}定义。
     *
     * @since 24
     */
    Http_Buffer body;
    /** 
     * @brief 响应状态码，详情请参考{@link Http_ResponseCode} 枚举定义。
     * 
     * @since 24
     */
    Http_ResponseCode responseCode;
    /** 
     * @brief HTTP响应头信息，详情请参考{@link OH_Http_Interceptor_Headers}定义。
     *
     * @since 24
     */
    OH_Http_Interceptor_Headers *headers;
    /** 
     * @brief 响应性能信息，详情请参考{@link Http_PerformanceTiming}定义。
     *
     * @since 24
     */
    Http_PerformanceTiming performanceTiming;
} OH_Http_Interceptor_Response;

/**
 * @brief 定义拦截器的执行阶段。
 *
 * @since 24
 */
typedef enum OH_Interceptor_Stage {
    /**
     * @brief 拦截器处理请求。
     * 
     * @since 24
     */
    OH_STAGE_REQUEST,
    /**
     * @brief 拦截器处理响应。
     * 
     * @since 24
     */
    OH_STAGE_RESPONSE
} OH_Interceptor_Stage;

/**
 * @brief 定义拦截器的类型。
 *
 * @since 24
 */
typedef enum OH_Interceptor_Type {
    /**
     * @brief 只读拦截器。
     * @since 24
     */
    OH_TYPE_READ_ONLY,
    /**
     * @brief 可修改拦截器。仅针对Network Kit HTTP请求生效。
     * @since 26.0.0
     */
    OH_TYPE_MODIFY_NETWORK_KIT
} OH_Interceptor_Type;

/**
 * @brief 定义拦截器的处理结果。
 *
 * @since 24
 */
typedef enum OH_Interceptor_Result {
    /**
     * @brief 继续处理。
     *
     * @since 24
     */
    OH_CONTINUE,
    /**
     * @brief 拦截处理。
     *
     * @since 24
     */
    OH_ABORT
} OH_Interceptor_Result;
/**
 * @brief 定义HTTP拦截器处理函数。
 *
 * @param request HTTP请求数据包指针（仅在请求阶段有效）。
 * @param response HTTP响应数据包指针（仅在响应阶段有效）。
 * @param isModified 标识拦截器是否修改了数据包。对OH_TYPE_READ_ONLY类型拦截器无效，可配置为nullptr。
 *     <br>- 0表示未对数据执行修改操作。
 *     <br>- 非0表示已对数据执行修改操作。
 * @return 拦截器处理结果。
 *     <br>- OH_CONTINUE：继续处理
 *     <br>- OH_ABORT：拦截处理
 * @since 24
 */
typedef OH_Interceptor_Result (*OH_Http_InterceptorHandler)(
    OH_Http_Interceptor_Request *request,
    OH_Http_Interceptor_Response *response,
    int32_t *isModified);

/**
 * @brief 定义HTTP全局拦截器的配置信息。
 *
 * @since 24
 */
typedef struct OH_Http_Interceptor {
    /** 
     * @brief 拦截器组ID。
     * 
     * @since 24
     */
    int32_t groupId;
    /** 
     * @brief 拦截器的执行阶段，详情请参考{@link OH_Interceptor_Stage} 枚举定义。
     * 
     * @since 24
     */
    OH_Interceptor_Stage stage;
    /** 
     * @brief 拦截器的类型，详情请参考{@link OH_Interceptor_Type} 枚举定义。
     * 
     * @since 24
     */
    OH_Interceptor_Type type;
    /** 
     * @brief 拦截器处理函数，详情请参考{@link OH_Http_InterceptorHandler} 函数指针定义。
     * 
     * @since 24
     */
    OH_Http_InterceptorHandler handler;
    /** 
     * @brief 拦截器的启用状态。0代表未启用，非0代表启用。
     * 
     * @since 24
     */
    int32_t enabled;
} OH_Http_Interceptor;

#ifdef __cplusplus
}
#endif
#endif // HTTP_INTERCEPTOR_TYPE_H

/** @} */