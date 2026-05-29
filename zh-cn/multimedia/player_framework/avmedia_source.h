/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @addtogroup avmedia_source
 * @{
 *
 * @brief Defines APIs for AVMediaSource.
 *
 * @since 23
 */
/**
 * @file avmedia_source.h
 *
 * @brief 定义AVMediaSource的结构体和枚举类型。
 * 
 * @syscap SystemCapability.Multimedia.Media.Core
 * @kit MediaKit
 * @library libavmedia_source.so
 * @since 23
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMEDIA_SOURCE_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMEDIA_SOURCE_H

#include <stdint.h>
#include <stdio.h>
#include "native_averrors.h"
#include "native_avcodec_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 声明HTTP头部类型。
 *  
 * @since 23
 */
typedef struct OH_AVHttpHeader OH_AVHttpHeader;

/**
 * @brief 声明媒体源类型。
 *  
 * @since 23
 */
typedef struct OH_AVMediaSource OH_AVMediaSource;

/**
 * @brief 加载请求对象，用于表示媒体资源的加载请求，应用通过该对象获取所请求资源的位置。
 *  
 * @since 23
 */
typedef struct OH_AVMediaSourceLoadingRequest OH_AVMediaSourceLoadingRequest;

/**
 * @brief 声明媒体数据加载器类型，该类型由应用程序实现。
 * 
 * @since 23
 */
typedef struct OH_AVMediaSourceLoader OH_AVMediaSourceLoader;

/**
 * @brief 网络加载请求的错误码枚举。
 *  
 * @since 23
 */
typedef enum AVLoadingRequestError {
    /**
     * 资源成功下载。
     */
    AV_LOADING_ERROR_SUCCESS = 0,

    /**
     * 资源未准备好，无法访问。
     */
    AV_LOADING_ERROR_NOT_READY = 1,

    /**
     * 资源URL不存在。
     */
    AV_LOADING_ERROR_NO_RESOURCE = 2,

    /**
     * 资源句柄的UUID无效。
     */
    AV_LOADING_ERROR_INVALID_HANDLE = 3,

    /**
     * 客户端无权请求该资源。
     */
    AV_LOADING_ERROR_ACCESS_DENIED = 4,

    /**
     * 访问超时。
     */
    AV_LOADING_ERROR_ACCESS_TIMEOUT = 5,

    /**
     * 授权失败。
     */
    AV_LOADING_ERROR_AUTHORIZE_FAILED = 6,
} AVLoadingRequestError;

/**
 * @brief 创建一个HTTP头部实例。
 * 
 * @return 成功时返回指向OH_AVHttpHeader实例的指针，失败时返回空指针。
 * @since 23
 */
OH_AVHttpHeader *OH_AVHttpHeader_Create(void);

/**
 * @brief 释放一个HTTP头部实例。
 * 
 * @param header 指向OH_AVHttpHeader实例的指针。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示header为空指针或实例销毁失败。
 * @since 23
 */
OH_AVErrCode OH_AVHttpHeader_Destroy(OH_AVHttpHeader *header);

/**
 * @brief 获取HTTP头部实例中的记录项数量。
 * 
 * @param header 指向OH_AVHttpHeader实例的指针。
 * @param count 用于输出头部实例中记录项的数量。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示header为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVHttpHeader_GetCount(OH_AVHttpHeader *header, uint32_t *count);

/**
 * @brief 向HTTP头部实例中添加一个键值对记录。
 * 
 * @param header 指向OH_AVHttpHeader实例的指针。
 * @param key 记录的键名。
 * @param value 记录的值。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示任一参数为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVHttpHeader_AddRecord(OH_AVHttpHeader *header, const char *key, const char *value);

/**
 * @brief 通过索引获取HTTP头部实例中的键值对记录。
 * 
 * @param header 指向OH_AVHttpHeader实例的指针。
 * @param index 记录在头部中的位置。
 * @param key 用于输出记录的键名。
 * @param value 用于输出记录的值。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示header为空指针或索引越界。
 * @since 23
 */
OH_AVErrCode OH_AVHttpHeader_GetRecord(OH_AVHttpHeader *header, uint32_t index, const char **key, const char **value);

/**
 * @brief 通过URL创建媒体源。
 * 
 * @param url 媒体源的URL。支持以下流媒体格式：HLS、HTTP-FLV、DASH和HTTPS。
 * @param header 附加到网络请求的HTTP头部。
 * @return 成功时返回指向OH_AVMediaSource实例的指针，失败时返回空指针。
 * @since 23
 */
OH_AVMediaSource *OH_AVMediaSource_CreateWithUrl(const char *url, OH_AVHttpHeader *header);

/**
 * @brief 通过OH_AVDataSource创建媒体源。
 * 
 * @param dataSource 指向OH_AVDataSource的指针。
 * @return 成功时返回指向OH_AVMediaSource实例的指针，失败时返回空指针。
 * @since 23
 */
OH_AVMediaSource *OH_AVMediaSource_CreateWithDataSource(OH_AVDataSource *dataSource);

/**
 * @brief 通过文件描述符（FileDescriptor）创建媒体源。
 * 
 * @param fd 数据源的文件描述符。
 * @param offset 开始读取的文件偏移量。
 * @param size 文件大小（以字节为单位）。
 * @return 成功时返回指向OH_AVMediaSource实例的指针，失败时返回空指针。
 * @details Possible failure causes:
 * 1. fd is invalid.
 * 2. offset is invalid.
 * 3. size error.
 * 4. resource is invalid.
 * 5. file format is not supported.
 * @since 23
 */
OH_AVMediaSource *OH_AVMediaSource_CreateWithFd(int32_t fd, int64_t offset, int64_t size);

/**
 * @brief 释放media source实例。
 * 
 * @param source 指向OH_AVMediaSource实例的指针。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示source为空指针或释放失败。
 * @since 23
 */
OH_AVErrCode OH_AVMediaSource_Destroy(OH_AVMediaSource *source);

/**
 * @brief 设置媒体MIME类型以处理扩展媒体源。
 * 
 * @param source 指向OH_AVMediaSource的指针。
 * @param mimetype 媒体源的MIME类型{@link AVMimeTypes}。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示source或mimetype为空指针。
 * AV_ERR_UNSUPPORTED_FORMAT：表示不支持该mimetype。
 * @since 23
 */
OH_AVErrCode OH_AVMediaSource_SetMimeType(OH_AVMediaSource *source, const char *mimetype);

/**
 * @brief 获取请求的URL。
 * 
 * @param request OH_AVMediaSourceLoadingRequest实例。
 * @param url 用于输出的URL字符串。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示request为空指针或不存在URL。
 * @since 23
 */
OH_AVErrCode OH_AVMediaSourceLoadingRequest_GetUrl(OH_AVMediaSourceLoadingRequest *request, const char **url);

/**
 * @brief 获取请求的HTTP头部。
 * 
 * @param request OH_AVMediaSourceLoadingRequest实例。
 * @param header 用于HTTP请求的HTTP头部。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示request为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVMediaSourceLoadingRequest_GetHttpHeader(OH_AVMediaSourceLoadingRequest *request,
    OH_AVHttpHeader **header);

/**
 * @brief 用于向AVPlayer发送请求数据的接口。
 * 
 * @param request 资源打开请求的参数。
 * @param uuid 资源句柄的ID。
 * @param offset 当前媒体数据相对于资源起始位置的偏移量。
 * @param data 发送给播放器的媒体数据。
 * @param dataSize 发送给播放器的数据长度。
 * @return 当前读取操作接受的字节数。返回值小于零表示失败；
 * -2 表示播放器不再需要当前数据，客户端应停止当前读取过程；
 * -3 表示播放器缓冲区已满，客户端应等待下一次读取。
 * @since 23
 */
int32_t OH_AVMediaSourceLoadingRequest_RespondData(
    OH_AVMediaSourceLoadingRequest *request, int64_t uuid, int64_t offset, const uint8_t *data, uint64_t dataSize);

/**
 * @brief 应用用于向AVPlayer发送响应头部的接口，必须在首次调用{@link OH_AVMediaSourceLoadingRequest_RespondData}之前调用。
 * 
 * @param request 资源打开请求的参数。
 * @param uuid 资源句柄的ID。
 * @param header HTTP响应中的头部信息。
 * 应用可将该头部字段与底层支持的字段进行交集处理后再传入，也可直接传入所有对应的头部信息。
 * @param redirectUrl HTTP响应中包含的重定向URL（如果存在）。
 * @since 23
 */
void OH_AVMediaSourceLoadingRequest_RespondHeader(
    OH_AVMediaSourceLoadingRequest *request, int64_t uuid, OH_AVHttpHeader *header, const char *redirectUrl);

/**
 * @brief 通知播放器当前请求的状态。在推送完单个资源的所有数据后，应用应发送LOADING_ERROR_SUCCESS状态，以通知播放器资源推送已完成。
 * 
 * @param request 资源打开请求的参数。
 * @param uuid 资源句柄的ID。
 * @param error 错误状态。
 * @since 23
 */
void OH_AVMediaSourceLoadingRequest_FinishLoading(
    OH_AVMediaSourceLoadingRequest *request, int64_t uuid, AVLoadingRequestError error);

/**
 * @brief 创建一个OH_AVMediaSourceLoader实例。成功时返回OH_AVMediaSourceLoader指针，失败时返回空指针。
 * 
 * @return OH_AVMediaSourceLoader pointer if success, else return NULL.
 * @since 23
 */
OH_AVMediaSourceLoader *OH_AVMediaSourceLoader_Create(void);

/**
 * @brief 释放OH_AVMediaSourceLoader实例。
 * 
 * @param loader 待释放的OH_AVMediaSourceLoader实例。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示loader为空指针或释放失败。
 * @since 23
 */
OH_AVErrCode OH_AVMediaSourceLoader_Destroy(OH_AVMediaSourceLoader *loader);

/**
 * @brief 为媒体源实例设置一个源加载器。
 * 
 * @param source 需要网络代理的OH_AVMediaSource。
 * @param loader OH_AVMediaSourceLoader实例。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示source或loader为空指针，或操作失败。
 * @since 23
 */
OH_AVErrCode OH_AVMediaSource_SetMediaSourceLoader(OH_AVMediaSource *source, OH_AVMediaSourceLoader *loader);

/**
 * @brief Defines the SourceOpenCallback function which is called by the service.
 * client should process the incoming request
 * and return the unique handle to the open resource.
 * The client must return the handle immediately after processing the request.
 * @param request Parameters for the resource open request,
 * including detailed information about the requested resource and the data push method.
 * @param userData The data set by user in OH_AVMediaSourceLoader_SetSourceOpenCallback
 * @return The handler of current resource open request, the handler for the request object is unique.
 *     A value greater than 0 means the request is successful.
 *     A value less than or equal to 0 means it fails.
 * @since 23
 */
typedef int64_t (*OH_AVMediaSourceLoaderOnSourceOpenedCallback)(OH_AVMediaSourceLoadingRequest *request,
    void *userData);

/**
 * @brief 定义由服务端调用的SourceReadCallback函数。客户端应记录读取请求，并在有足够数据时通过请求对象的{@link OH_AVMediaSourceLoadingRequest_RespondData}和{@link OH_AVMediaSourceLoadingRequest_RespondHeader}
 * 方法推送数据。客户端必须在处理完请求后立即返回。
 * 
 * @param uuid 资源句柄的ID。
 * @param requestedOffset 当前媒体数据相对于资源起始位置的偏移量。
 * @param requestedLength 当前请求的数据长度。-1 表示已到达资源末尾，需通过{@link OH_AVMediaSourceLoadingRequest_FinishLoading}方法通知播放器推送结束。
 * @param userData The data set by user in OH_AVMediaSourceLoader_SetSourceReadCallback
 * @since 23
 */
typedef void (*OH_AVMediaSourceLoaderOnSourceReadCallback)(int64_t uuid, int64_t requestedOffset,
    int64_t requestedLength, void *userData);

/**
 * @brief 定义由服务端调用的SourceCloseCallback函数。客户端应释放相关资源，并在处理完请求后立即返回。
 * 
 * @param uuid 资源句柄的ID。
 * @param userData The data set by user in OH_AVMediaSourceLoader_SetSourceCloseCallback
 * @since 23
 */
typedef void (*OH_AVMediaSourceLoaderOnSourceClosedCallback)(int64_t uuid, void *userData);

/**
 * @brief 为OH_AVMediaSourceLoader设置打开回调函数。
 * 
 * @param loader 要设置回调函数的OH_AVMediaSourceLoader实例。
 * @param callback 要设置的打开回调函数。
 * @param userData 回调函数中使用的用户自定义数据。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示loader为空指针或操作失败。
 * @since 23
 */
OH_AVErrCode OH_AVMediaSourceLoader_SetSourceOpenCallback(OH_AVMediaSourceLoader *loader,
    OH_AVMediaSourceLoaderOnSourceOpenedCallback callback, void *userData);

/**
 * @brief 为OH_AVMediaSourceLoader设置读取回调函数。
 * 
 * @param loader 要设置回调函数的OH_AVMediaSourceLoader实例。
 * @param callback 要设置的读取回调函数。
 * @param userData 回调函数中使用的用户自定义数据。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示loader为空指针或操作失败。
 * @since 23
 */
OH_AVErrCode OH_AVMediaSourceLoader_SetSourceReadCallback(OH_AVMediaSourceLoader *loader,
    OH_AVMediaSourceLoaderOnSourceReadCallback callback, void *userData);

/**
 * @brief 为OH_AVMediaSourceLoader设置关闭回调函数。
 * 
 * @param loader 要设置回调函数的OH_AVMediaSourceLoader实例。
 * @param callback 要设置的关闭回调函数。
 * @param userData 回调函数中使用的用户自定义数据。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示loader为空指针或操作失败。
 * @since 23
 */
OH_AVErrCode OH_AVMediaSourceLoader_SetSourceCloseCallback(OH_AVMediaSourceLoader *loader,
    OH_AVMediaSourceLoaderOnSourceClosedCallback callback, void *userData);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMEDIA_SOURCE_H
/** @} */
