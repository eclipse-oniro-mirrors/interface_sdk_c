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
 * @brief Defines the struct and enum of **AVMediaSource**.
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
 * @brief Defines a struct for the HTTP header.
 *  
 * @since 23
 */
typedef struct OH_AVHttpHeader OH_AVHttpHeader;

/**
 * @brief Defines a struct for the media source.
 *  
 * @since 23
 */
typedef struct OH_AVMediaSource OH_AVMediaSource;

/**
 * @brief Defines a load request object for the media resource, through which the application obtains the location of
 * the requested resource.
 *  
 * @since 23
 */
typedef struct OH_AVMediaSourceLoadingRequest OH_AVMediaSourceLoadingRequest;

/**
 * @brief Declares the media source loader type, which is implemented by the application.
 * 
 * @since 23
 */
typedef struct OH_AVMediaSourceLoader OH_AVMediaSourceLoader;

/**
 * @brief Enumerates the error codes of network loading requests.
 *  
 * @since 23
 */
typedef enum AVLoadingRequestError {
    /**
     * The resource is successfully downloaded.
     */
    AV_LOADING_ERROR_SUCCESS = 0,

    /**
     * The resource is not ready and cannot be accessed.
     */
    AV_LOADING_ERROR_NOT_READY = 1,

    /**
     * The resource URL does not exist.
     */
    AV_LOADING_ERROR_NO_RESOURCE = 2,

    /**
     * The UUID of the resource handle is invalid.
     */
    AV_LOADING_ERROR_INVALID_HANDLE = 3,

    /**
     * The client does not have the permission to request the resource.
     */
    AV_LOADING_ERROR_ACCESS_DENIED = 4,

    /**
     * The access times out.
     */
    AV_LOADING_ERROR_ACCESS_TIMEOUT = 5,

    /**
     * The authorization failed.
     */
    AV_LOADING_ERROR_AUTHORIZE_FAILED = 6,
} AVLoadingRequestError;

/**
 * @brief Creates an HTTP header instance.
 * 
 * @return Pointer to the **OH_AVHttpHeader** instance if the operation is successful; null pointer if the operation
 * fails.
 * @since 23
 */
OH_AVHttpHeader *OH_AVHttpHeader_Create(void);

/**
 * @brief Releases an HTTP header instance.
 * 
 * @param header Pointer to the **OH_AVHttpHeader** instance.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The header is a null pointer or the instance fails to be destroyed.
 * @since 23
 */
OH_AVErrCode OH_AVHttpHeader_Destroy(OH_AVHttpHeader *header);

/**
 * @brief Obtains the number of records in an HTTP header instance.
 * 
 * @param header Pointer to the **OH_AVHttpHeader** instance.
 * @param count Pointer to the number of records in the header instance.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The header is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVHttpHeader_GetCount(OH_AVHttpHeader *header, uint32_t *count);

/**
 * @brief Adds a key-value pair record to an HTTP header instance.
 * 
 * @param header Pointer to the **OH_AVHttpHeader** instance.
 * @param key Pointer to the key name of the record.
 * @param value Pointer to the value of the record.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: Any parameter is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVHttpHeader_AddRecord(OH_AVHttpHeader *header, const char *key, const char *value);

/**
 * @brief Obtains a key-value pair record in an HTTP header instance by index.
 * 
 * @param header Pointer to the **OH_AVHttpHeader** instance.
 * @param index Position of the record in the header.
 * @param key Double pointer to the key name of the record.
 * @param value Double pointer to the value of the record.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The header is a null pointer or the index is out of range.
 * @since 23
 */
OH_AVErrCode OH_AVHttpHeader_GetRecord(OH_AVHttpHeader *header, uint32_t index, const char **key, const char **value);

/**
 * @brief Creates a media source using a URL.
 * 
 * @param url Pointer to the URL of the media source. The following streaming media formats are supported: HLS, HTTP-
 * FLV, DASH, and HTTPS.
 * @param header Pointer to the HTTP header attached to the network request.
 * @return Pointer to the **OH_AVMediaSource** instance if the operation is successful; null pointer if the operation
 * fails.
 * @since 23
 */
OH_AVMediaSource *OH_AVMediaSource_CreateWithUrl(const char *url, OH_AVHttpHeader *header);

/**
 * @brief Creates a media source using **OH_AVDataSource**.
 * 
 * @param dataSource Pointer to **OH_AVDataSource**.
 * @return Pointer to the **OH_AVMediaSource** instance if the operation is successful; null pointer if the operation
 * fails.
 * @since 23
 */
OH_AVMediaSource *OH_AVMediaSource_CreateWithDataSource(OH_AVDataSource *dataSource);

/**
 * @brief Creates a media source using a file descriptor.
 * 
 * @param fd FD of a media source file.
 * @param offset Offset of the file to be read.
 * @param size File size, in bytes
 * @return Pointer to the **OH_AVMediaSource** instance if the operation is successful; null pointer if the operation
 * fails.
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
 * @brief Releases a media source instance.
 * 
 * @param source Pointer to the **OH_AVMediaSource** instance.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The **source** is a null pointer or fails to be released.
 * @since 23
 */
OH_AVErrCode OH_AVMediaSource_Destroy(OH_AVMediaSource *source);

/**
 * @brief Sets the MIME type to process extended media sources.
 * 
 * @param source Pointer to the **OH_AVMediaSource** instance.
 * @param mimetype Pointer to the MIME type ({@link AV_MimeTypes}) of the media source.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The **source** or **mimetype** is a null pointer.
 * {@link AV_ERR_UNSUPPORTED_FORMAT}: The **mimetype** is not supported.
 * @since 23
 */
OH_AVErrCode OH_AVMediaSource_SetMimeType(OH_AVMediaSource *source, const char *mimetype);

/**
 * @brief Obtains the URL of a request.
 * 
 * @param request Pointer to the **OH_AVMediaSourceLoadingRequest** instance.
 * @param url Double pointer to the URL for output.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The **request** is a null pointer or the URL does not exist.
 * @since 23
 */
OH_AVErrCode OH_AVMediaSourceLoadingRequest_GetUrl(OH_AVMediaSourceLoadingRequest *request, const char **url);

/**
 * @brief Obtains the HTTP header of a request.
 * 
 * @param request Pointer to the **OH_AVMediaSourceLoadingRequest** instance.
 * @param header Double pointer to the HTTP header used for the HTTP request.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The **request** is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVMediaSourceLoadingRequest_GetHttpHeader(OH_AVMediaSourceLoadingRequest *request,
    OH_AVHttpHeader **header);

/**
 * @brief Sends request data to the AVPlayer.
 * 
 * @param request Pointer to the request for opening a resource.
 * @param uuid ID of the resource handle.
 * @param offset Offset of the current media data relative to the start of the resource.
 * @param data Pointer to the media data sent to the player.
 * @param dataSize Length of the data sent to the player.
 * @return Number of bytes accepted by the current read operation. If the return value is less than 0, the operation
 * fails.
 * The value **-2** indicates that the player no longer needs the current data, and the client should stop the current
 * read process.
 * The value **-3** indicates that the player's buffer is full, and the client should wait for the next read.
 * @since 23
 */
int32_t OH_AVMediaSourceLoadingRequest_RespondData(
    OH_AVMediaSourceLoadingRequest *request, int64_t uuid, int64_t offset, const uint8_t *data, uint64_t dataSize);

/**
 * @brief Sends the response header to the AVPlayer. This API must be called before {@link OH_AVMediaSourceLoadingRequest_RespondData}
 * is called for the first time.
 * 
 * @param request Pointer to the request for opening a resource.
 * @param uuid ID of the resource handle.
 * @param header Pointer to the header information in the HTTP response.
 * The application can intersect the header field with the supported fields at the bottom layer and then pass the
 * intersection result to the AVPlayer, or directly pass all the corresponding header information.
 * @param redirectUrl Pointer to the redirection URL contained in the HTTP response (if any).
 * @since 23
 */
void OH_AVMediaSourceLoadingRequest_RespondHeader(
    OH_AVMediaSourceLoadingRequest *request, int64_t uuid, OH_AVHttpHeader *header, const char *redirectUrl);

/**
 * @brief Notifies the player of the current request status. After pushing all data of a single resource, the
 * application should send the **LOADING_ERROR_SUCCESS** state to notify the player that the resource push is complete.
 * 
 * @param request Pointer to the request for opening a resource.
 * @param uuid ID of the resource handle.
 * @param error Audio playback is in the error state.
 * @since 23
 */
void OH_AVMediaSourceLoadingRequest_FinishLoading(
    OH_AVMediaSourceLoadingRequest *request, int64_t uuid, AVLoadingRequestError error);

/**
 * @brief Creates an **OH_AVMediaSourceLoader** instance. If the operation is successful, the **OH_AVMediaSourceLoader**
 *  pointer is returned. If the operation fails, a null pointer is returned.
 * 
 * @return OH_AVMediaSourceLoader pointer if success, else return NULL.
 * @since 23
 */
OH_AVMediaSourceLoader *OH_AVMediaSourceLoader_Create(void);

/**
 * @brief Releases an **OH_AVMediaSourceLoader** instance.
 * 
 * @param loader Pointer to the **OH_AVMediaSourceLoader** instance to be released.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The **loader** is a null pointer or fails to be released.
 * @since 23
 */
OH_AVErrCode OH_AVMediaSourceLoader_Destroy(OH_AVMediaSourceLoader *loader);

/**
 * @brief Sets a source loader for the media source instance.
 * 
 * @param source Pointer to the **OH_AVMediaSource** that requires a network proxy.
 * @param loader Pointer to the **OH_AVMediaSourceLoader** instance.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The **source** or **loader** is a null pointer, or the operation fails.
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
 * @brief Defines the **SourceReadCallback** function called by the server. The client should record the read request
 * and push data using the {@link OH_AVMediaSourceLoadingRequest_RespondData} and {@link OH_AVMediaSourceLoadingRequest_RespondHeader}
 * methods of the request object when there is sufficient data. The client must return immediately after the request
 * is processed.
 * 
 * @param uuid ID of the resource handle.
 * @param requestedOffset Offset of the current media data relative to the start of the resource.
 * @param requestedLength Length of the requested data. The value **-1** indicates that the end of the resource has
 * been reached. In this case, call the {@link OH_AVMediaSourceLoadingRequest_FinishLoading} method to notify the
 * player that the push is complete.
 * @param userData The data set by user in OH_AVMediaSourceLoader_SetSourceReadCallback
 * @since 23
 */
typedef void (*OH_AVMediaSourceLoaderOnSourceReadCallback)(int64_t uuid, int64_t requestedOffset,
    int64_t requestedLength, void *userData);

/**
 * @brief Defines the **SourceCloseCallback** function called by the server. The client should release related
 * resources and return immediately after the request is processed.
 * 
 * @param uuid ID of the resource handle.
 * @param userData The data set by user in OH_AVMediaSourceLoader_SetSourceCloseCallback
 * @since 23
 */
typedef void (*OH_AVMediaSourceLoaderOnSourceClosedCallback)(int64_t uuid, void *userData);

/**
 * @brief Sets the open callback function for **OH_AVMediaSourceLoader**.
 * 
 * @param loader Pointer to the **OH_AVMediaSourceLoader** instance for which the callback function is to be set.
 * @param callback Open callback function to be set.
 * @param userData Pointer to the user-defined data used in the callback function.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The **loader** is a null pointer or the operation fails.
 * @since 23
 */
OH_AVErrCode OH_AVMediaSourceLoader_SetSourceOpenCallback(OH_AVMediaSourceLoader *loader,
    OH_AVMediaSourceLoaderOnSourceOpenedCallback callback, void *userData);

/**
 * @brief Sets the read callback function for **OH_AVMediaSourceLoader**.
 * 
 * @param loader Pointer to the **OH_AVMediaSourceLoader** instance for which the callback function is to be set.
 * @param callback Read callback function to be set.
 * @param userData Pointer to the user-defined data used in the callback function.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The **loader** is a null pointer or the operation fails.
 * @since 23
 */
OH_AVErrCode OH_AVMediaSourceLoader_SetSourceReadCallback(OH_AVMediaSourceLoader *loader,
    OH_AVMediaSourceLoaderOnSourceReadCallback callback, void *userData);

/**
 * @brief Sets the close callback function for **OH_AVMediaSourceLoader**.
 * 
 * @param loader Pointer to the **OH_AVMediaSourceLoader** instance for which the callback function is to be set.
 * @param callback Close callback function to be set.
 * @param userData Pointer to the user-defined data used in the callback function.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The **loader** is a null pointer or the operation fails.
 * @since 23
 */
OH_AVErrCode OH_AVMediaSourceLoader_SetSourceCloseCallback(OH_AVMediaSourceLoader *loader,
    OH_AVMediaSourceLoaderOnSourceClosedCallback callback, void *userData);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMEDIA_SOURCE_H
/** @} */
