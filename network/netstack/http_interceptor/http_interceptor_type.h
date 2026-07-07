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
 * @brief Defines the APIs for http global interceptor.
 *
 * @since 24
 */

/**
 * @file http_interceptor_type.h
 * @brief Defines the data structures for the C APIs of the global HTTP interceptor module, including the interceptor
 * request/response header information, HTTP request/response data packet structure, interceptor configuration
 * information, and related enum types and function pointers.
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
 * @brief Defines a struct for the request/response header information of the interceptor.
 *
 * @since 24
 */
typedef struct OH_Http_Interceptor_Headers {
    /** 
     * @brief Pointer to the request/response header information of the interceptor.
     * 
     * @since 24
     */
    char *data;
    /** 
     * @brief Pointer to the next header information.
     *     
     * @since 24
     */
    struct OH_Http_Interceptor_Headers *next;
} OH_Http_Interceptor_Headers;

/**
 * @brief Defines a struct for the HTTP request data packet of the interceptor.
 *
 * @since 24
 */
typedef struct OH_Http_Interceptor_Request {
    /** 
     * @brief Request URL. For details, see {@link Http_Buffer}.
     * 
     * @since 24
     */
    Http_Buffer url;
    /** 
     * @brief Request method. For details, see {@link Http_Buffer}.
     *
     * @since 24
     */
    Http_Buffer method;
    /** 
     * @brief HTTP request header. For details, see {@link OH_Http_Interceptor_Headers}.
     *
     * @since 24
     */
    OH_Http_Interceptor_Headers *headers;
    /** 
     * @brief Request body. For details, see {@link Http_Buffer}.
     * 
     * @since 24
     */
    Http_Buffer body;
} OH_Http_Interceptor_Request;

/**
 * @brief Defines a struct for the HTTP response data packet of the interceptor.
 *
 * @since 24
 */
typedef struct OH_Http_Interceptor_Response {
    /** 
     * @brief Response body. For details, see {@link Http_Buffer}.
     *
     * @since 24
     */
    Http_Buffer body;
    /** 
     * @brief Response status code. For details, see {@link Http_ResponseCode}.
     * 
     * @since 24
     */
    Http_ResponseCode responseCode;
    /** 
     * @brief HTTP response header. For details, see {@link OH_Http_Interceptor_Headers}.
     *
     * @since 24
     */
    OH_Http_Interceptor_Headers *headers;
    /** 
     * @brief Response performance information. For details, see {@link Http_PerformanceTiming}.
     *
     * @since 24
     */
    Http_PerformanceTiming performanceTiming;
} OH_Http_Interceptor_Response;

/**
 * @brief Defines an enum for the interceptor stages.
 *
 * @since 24
 */
typedef enum OH_Interceptor_Stage {
    /**
     * @brief The interceptor processes the request.
     * 
     * @since 24
     */
    OH_STAGE_REQUEST,
    /**
     * @brief The interceptor processes the response.
     * 
     * @since 24
     */
    OH_STAGE_RESPONSE
} OH_Interceptor_Stage;

/**
 * @brief Defines an enum for the interceptor types.
 *
 * @since 24
 */
typedef enum OH_Interceptor_Type {
    /**
     * @brief Read-only interceptor.
     *
     * @since 24
     */
    OH_TYPE_READ_ONLY,
    /**
     * @brief interceptor will modify the packet from Network Kit
     * @since 26.0.0
     */
    OH_TYPE_MODIFY_NETWORK_KIT
} OH_Interceptor_Type;

/**
 * @brief Defines an enum for the interceptor results.
 *
 * @since 24
 */
typedef enum OH_Interceptor_Result {
    /**
     * @brief The processing continues.
     * 
     * @since 24
     */
    OH_CONTINUE,
    /**
     * @brief The processing is aborted.
     * 
     * @since 24
     */
    OH_ABORT
} OH_Interceptor_Result;
/**
 * @brief Defines the HTTP interceptor handler function.
 *
 * @param request Pointer to the HTTP request data packet (valid only in the request stage).
 * @param response Pointer to the HTTP response data packet (valid only in the response stage).
 * @param isModified Output parameter, which indicates whether the interceptor has modified the data packet. This
 *     parameter is invalid for the interceptor of the **OH_TYPE_READ_ONLY** type.
 * @return Interceptor processing result. - **OH_CONTINUE**: The processing continues. - **OH_ABORT**: The processing
 *     is aborted.
 * @since 24
 */
typedef OH_Interceptor_Result (*OH_Http_InterceptorHandler)(
    OH_Http_Interceptor_Request *request,
    OH_Http_Interceptor_Response *response,
    int32_t *isModified);

/**
 * @brief Defines a struct for the configuration information of the global HTTP interceptor.
 *
 * @since 24
 */
typedef struct OH_Http_Interceptor {
    /** 
     * @brief Interceptor group ID.
     * 
     * @since 24
     */
    int32_t groupId;
    /** 
     * @brief Execution stage of the interceptor. For details, see {@link OH_Interceptor_Stage}.
     * 
     * @since 24
     */
    OH_Interceptor_Stage stage;
    /** 
     * @brief Interceptor type. For details, see {@link OH_Interceptor_Type}.
     * 
     * @since 24
     */
    OH_Interceptor_Type type;
    /** 
     * @brief Interceptor handler. For details, see {@link OH_Http_InterceptorHandler}.
     * 
     * @since 24
     */
    OH_Http_InterceptorHandler handler;
    /** 
     * @brief Enabling status of the interceptor. The value **0** indicates that the interceptor is disabled, and a non-
     * zero value indicates the opposite.
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

/** @} */