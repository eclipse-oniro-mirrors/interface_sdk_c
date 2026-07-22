/*
 * Copyright (c) 2026-2026 Huawei Device Co., Ltd.
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
 * @addtogroup ContentEmbed
 * @{
 *
 * @brief The ContentEmbed module provides the Object Editor (OE) framework and technologies to support document
 * embedding and collaborative editing between applications.
 * An embedded document (OE document for short) implemented by using the OE technology may be presented as a thumbnail
 * or a snapshot on a client UI, or may be serialized into a segment of binary data in a standard format and stored in
 * a memory or a file (referred to as an OE format file).
 * @since 24
 */

/**
 * @file content_embed_proxy.h
 *
 * @brief Provides the client application with the API for querying the OE Extension information registered by the
 * server application, the data structures for interacting with the server OE Extension object, and the related
 * operation APIs.
 *
 * @library libcontent_embed_ndk.so
 * @kit ContentEmbedKit
 * @syscap SystemCapability.ContentEmbed.ObjectEditor
 * @since 24
 */

#ifndef OHOS_CONTENT_EMBED_PROXY_H
#define OHOS_CONTENT_EMBED_PROXY_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <multimedia/image_framework/image/pixelmap_native.h>
#include "content_embed_common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Defines the maximum number of characters allowed in the name field in {@link ContentEmbed_Format}.
 *
 * @since 24
 */
#define MAX_NAME_LENGTH (1 * 1024)

/**
 * @brief Defines the maximum number of characters allowed in the description field in {@link ContentEmbed_Format}.
 *
 * @since 24
 */
#define MAX_DESCRIPTION_LENGTH (1 * 1024)

/**
 * @brief Declares the ContentEmbed_Info structure. Use {@link OH_ContentEmbed_GetContentEmbedInfo} to query the
 * OE document information registered by all server-side applications for the current session.
 * Then, use {@link OH_ContentEmbed_GetFormatCountFromInfo} to obtain the count of {@link ContentEmbed_Format}
 * instances in the current query result, and use {@link OH_ContentEmbed_GetFormatFromInfo} to retrieve the
 * instance object at the specified index.
 *
 * @since 24
 */
typedef struct ContentEmbed_Info ContentEmbed_Info;

/**
 * @brief Declares the ContentEmbed_Info structure. which contains OE document information registered by server-side
 * applications for the OE Extension. Specifically, you can use {@link OH_ContentEmbed_GetOEidFromFormat} to
 * obtain the OEID, {@link OH_ContentEmbed_GetNameAndDescriptionFromFormat} to get the name and description,
 * {@link OH_ContentEmbed_GetIconFromFormat} to retrieve the icon, and
 * {@link OH_ContentEmbed_GetFileNameExtensionsFromFormat} to obtain the list of file extensions.
 *
 * @since 24
 */
typedef struct ContentEmbed_Format ContentEmbed_Format;

/**
 * @brief Creates an {@link ContentEmbed_Info} instance.
 * <br>You can destroy the instance by calling {@link OH_ContentEmbed_DestroyContentEmbedInfo} to avoid memory leaks.
 *
 * @param info Output parameter. This pointer points to the newly created {@link ContentEmbed_Info} object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyContentEmbedInfo {info}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_CreateContentEmbedInfo(ContentEmbed_Info **info);

/**
 * @brief Destroys a {@link ContentEmbed_Info} instance.
 *
 * @param info Pointer to the {@link ContentEmbed_Info} object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_DestroyContentEmbedInfo(ContentEmbed_Info *info);

/**
 * @brief Obtains a {@link ContentEmbed_Info} instance based on the region settings.
 *
 * @permission ohos.permission.CONNECT_OBJECTEDITOR_EXTENSION
 * @param locale Locale ID, which consists of the language, script, and country/region, for example, **zh-Hans-
 *     CN**. If the locale is empty, the system locale setting is used by default.
 * @param info Output parameter. This pointer points to the ContentEmbed_Info object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_PERMISSION_DENIED} - Permission verification failed.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL} - The system service is abnormal.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetContentEmbedInfo(const char *locale, ContentEmbed_Info *info);

/**
 * @brief Obtains the number of {@link ContentEmbed_Format} instances in the {@link ContentEmbed_Info} instance.
 *
 * @param info Pointer to the {@link ContentEmbed_Info} object.
 * @param count Output parameter. Number of stored {@link ContentEmbed_Format} instances.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetFormatCountFromInfo(const ContentEmbed_Info *info, uint32_t *count);

/**
 * @brief Obtains the {@link ContentEmbed_Format} instance at the specified index from the {@link ContentEmbed_Info}
 * instance.
 *
 * @param info Pointer to the {@link ContentEmbed_Info} object.
 * @param index Represents the index of the internal array within the {@link ContentEmbed_Info} instance.
 * @param format Output parameter. Upon successful retrieval, returns a pointer to the {@link ContentEmbed_Format}
 *        instance at the specified index in info.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - Operations are successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameters.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetFormatFromInfo(const ContentEmbed_Info *info, uint32_t index,
                                                         ContentEmbed_Format **format);

/**
 * @brief Creates a {@link ContentEmbed_Format} instance.
 * <br>You can destroy the instance using {@link OH_ContentEmbed_DestroyContentEmbedFormat} to avoid memory leaks.
 *
 * @param format Output parameter. This pointer points to the newly created {@link ContentEmbed_Format} object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - Operations are successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameters.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyContentEmbedFormat {format}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_CreateContentEmbedFormat(ContentEmbed_Format **format);

/**
 * @brief Destroys an {@link ContentEmbed_Format} instance.
 *
 * @param format Pointer to the {@link ContentEmbed_Format} object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_DestroyContentEmbedFormat(ContentEmbed_Format *format);

/**
 * @brief Obtains an {@link ContentEmbed_Format} instance based on the OEID and region settings.
 *
 * @permission ohos.permission.CONNECT_OBJECTEDITOR_EXTENSION
 * @param oeid Unique identifier string of the document format.
 * @param locale Locale ID, which consists of the language, script, and country/region, for example, **zh-Hans-
 *     CN**. If the locale is empty, the system locale setting is used by default.
 * @param format Output parameter. The pointer points to the {@link ContentEmbed_Format} object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_PERMISSION_DENIED} - Permission verification failed.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL} - The system service is abnormal.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetContentEmbedFormatByOEidAndLocale(const char *oeid,
                                                                            const char *locale,
                                                                            ContentEmbed_Format *format);

/**
 * @brief Obtains the OEID of the {@link ContentEmbed_Format} instance.
 *
 * @param format Pointer to the {@link ContentEmbed_Format} object.
 * @param oeid Output parameter. Character array for storing the identifier string of the OEID. The recommended array
 *     length is {@link MAX_OEID_LENGTH}.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetOEidFromFormat(const ContentEmbed_Format *format, char *oeid);

/**
 * @brief Obtains the localized display name and description from a {@link ContentEmbed_Format} instance.
 *
 * @param format Pointer to the {@link ContentEmbed_Format} object.
 * @param name Output parameter. Character array for storing the name. The recommended array length is
 *     {@link MAX_NAME_LENGTH}.
 * @param description Output parameter. Character array for storing the description. The recommended array length is
 *     {@link MAX_DESCRIPTION_LENGTH}.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetNameAndDescriptionFromFormat(const ContentEmbed_Format *format,
                                                                       char *name, char *description);

/**
 * @brief Obtains the icon of a {@link ContentEmbed_Format} instance.
 *
 * @param format Pointer to the {@link ContentEmbed_Format} object.
 * @param icon Output parameter. Pointer to the {@link OH_PixelmapNative} instance that stores the icon.
 *     <br>You need to call {@link OH_PixelmapNative_Destroy} to destroy the instance to avoid memory leaks.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - Operations are successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_GetIconFromFormat(const ContentEmbed_Format *format, OH_PixelmapNative **icon);

/**
 * @brief Obtains the list of file name extensions of a {@link ContentEmbed_Format} instance.
 *
 * @param format Pointer to the {@link ContentEmbed_Format} object.
 * @param count Output parameter. Stores the number of returned file name extensions.
 * @return Pointer to the array of strings that indicate the file name extensions.
 * @since 24
 */
char** OH_ContentEmbed_GetFileNameExtensionsFromFormat(const ContentEmbed_Format *format, unsigned int *count);

/**
 * @brief Declares the ContentEmbed_ExtensionProxy structure. Points to the program object (client-side OE object for
 * short) for embedding and editing the client-side encapsulated and encapsulation documents of the OE.
 *
 * @since 24
 */
typedef struct ContentEmbed_ExtensionProxy ContentEmbed_ExtensionProxy;

/**
 * @brief Declares the structure type of an OE document. Encapsulates the metadata, content, and storage structure of
 * the embedded document.
 *
 * @since 24
 */
typedef struct ContentEmbed_Document ContentEmbed_Document;

/**
 * @brief Declares the ContentEmbed_Capability structure.
 *
 * @since 24
 */
typedef struct ContentEmbed_Capability ContentEmbed_Capability;

/**
 * @brief Creates a {@link ContentEmbed_ExtensionProxy} instance.
 * <br>You can destroy the instance using {@link OH_ContentEmbed_DestroyExtensionProxy} to avoid memory leaks.
 *
 * @param document Pointer to an OE document instance.
 * @param proxy Output parameter. This pointer points to the newly created {@link ContentEmbed_ExtensionProxy} object.
 * @param contextPtr Pointer to the context instance, which is used to transfer the application context information.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - The operation is not supported because the application is in the DLP sandbox.
 *     </li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyExtensionProxy {proxy}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_CreateExtensionProxy(ContentEmbed_Document *document,
                                                            ContentEmbed_ExtensionProxy **proxy,
                                                            void *contextPtr);

/**
 * @brief Destroys a {@link ContentEmbed_ExtensionProxy} instance.
 *
 * @param proxy Pointer to the {@link ContentEmbed_ExtensionProxy} object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_DestroyExtensionProxy(ContentEmbed_ExtensionProxy *proxy);

/**
 * @brief Callback function type for notifying the client when the OE document is updated.
 * <br>You need to implement this function and register it with the client's OE object through
 * {@link OH_ContentEmbed_Proxy_RegisterOnUpdateFunc}.
 *
 * @param proxy Represents a pointer to an
 *     {@link ContentEmbed_ExtensionProxy} instance which will be set in.
 * @since 24
 */
typedef void (*OH_ContentEmbed_ClientCallbackOnUpdateFunc)(
    ContentEmbed_ExtensionProxy *proxy);

/**
 * @brief Callback function type for notifying the client when an error occurs in the OE document.
 * <br>You need to implement this function and register it with the client's OE object through
 * {@link OH_ContentEmbed_Proxy_RegisterOnErrorFunc}.
 *
 * @param proxy Represents a pointer to an
 *     {@link ContentEmbed_ExtensionProxy} instance which will be set in.
 * @param error Error code. For details, see {@link ContentEmbed_ErrorCode}.
 * @since 24
 */
typedef void (*OH_ContentEmbed_ClientCallbackOnErrorFunc)(
    ContentEmbed_ExtensionProxy *proxy, ContentEmbed_ErrorCode error);

/**
 * @brief Callback function type for notifying the client when the OE document editing is complete.
 * <br>You need to implement this function and register it with the client's OE object through
 * {@link OH_ContentEmbed_Proxy_RegisterOnEditingFinishedFunc}.
 *
 * @param proxy Represents a pointer to an
 *     {@link ContentEmbed_ExtensionProxy} instance which will be set in.
 * @param dataModified Indicates whether the OE document data has been modified. The value true indicates that the OE
 *     document has been modified, and false indicates that the OE document has not been modified.
 * @since 24
 */
typedef void (*OH_ContentEmbed_ClientCallbackOnEditingFinishedFunc)(
    ContentEmbed_ExtensionProxy *proxy, bool dataModified);

/**
 * @brief Callback function type when the OE Extension stops.
 * <br>You need to implement this function and register it with the client's OE object through
 * {@link OH_ContentEmbed_Proxy_RegisterOnExtensionStoppedFunc}.
 *
 * @param proxy Represents a pointer to an
 *     {@link ContentEmbed_ExtensionProxy} instance which will be set in.
 * @since 24
 */
typedef void (*OH_ContentEmbed_ClientCallbackOnExtensionStoppedFunc)(
    ContentEmbed_ExtensionProxy *proxy);

/**
 * @brief Registers the callback function for updating an {@link ContentEmbed_ExtensionProxy} document with the client.
 *
 * @param proxy Pointer to the {@link ContentEmbed_ExtensionProxy} object.
 * @param onUpdateFunc {@link OH_ContentEmbed_ClientCallbackOnUpdateFunc} callback function to be registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_RegisterOnUpdateFunc(
    ContentEmbed_ExtensionProxy *proxy, OH_ContentEmbed_ClientCallbackOnUpdateFunc onUpdateFunc);

/**
 * @brief Registers the callback function for triggering an error when an error occurs in the document of the client's
 * object.
 *
 * @param proxy Pointer to the {@link ContentEmbed_ExtensionProxy} object.
 * @param onErrorFunc {@link OH_ContentEmbed_ClientCallbackOnErrorFunc} callback function to be registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_RegisterOnErrorFunc(
    ContentEmbed_ExtensionProxy *proxy, OH_ContentEmbed_ClientCallbackOnErrorFunc onErrorFunc);

/**
 * @brief Registers the callback function for the client to be invoked when an {@link ContentEmbed_ExtensionProxy}
 * document is edited.
 *
 * @param proxy Pointer to the {@link ContentEmbed_ExtensionProxy} object.
 * @param onEditingFinishedFunc {@link OH_ContentEmbed_ClientCallbackOnEditingFinishedFunc} callback function to be
 *     registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_RegisterOnEditingFinishedFunc(
    ContentEmbed_ExtensionProxy *proxy, OH_ContentEmbed_ClientCallbackOnEditingFinishedFunc onEditingFinishedFunc);

/**
 * @brief Registers the callback function for stopping the OE Extension to the client's OE object.
 *
 * @param proxy Pointer to the {@link ContentEmbed_ExtensionProxy} object.
 * @param onExtensionStoppedFunc {@link OH_ContentEmbed_ClientCallbackOnExtensionStoppedFunc} callback function to be
 *     registered.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_RegisterOnExtensionStoppedFunc(
    ContentEmbed_ExtensionProxy *proxy, OH_ContentEmbed_ClientCallbackOnExtensionStoppedFunc onExtensionStoppedFunc);

/**
 * @brief Connects to the server-side OE Extension and establishes a communication channel with the OE Extension.
 *
 * @permission ohos.permission.CONNECT_OBJECTEDITOR_EXTENSION
 * @param proxy Pointer to the {@link ContentEmbed_ExtensionProxy} object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_PERMISSION_DENIED} - Permission verification failed.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED} - Necessary client callbacks are not registered.</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL} - The system service is abnormal.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - The operation is not supported because the application is in the DLP sandbox.
 *     </li>
 *     <li>{@link CE_ERR_CONNECT_LIMIT_EXCEED} - The number of connected OE Extensions exceeds the upper limit.</li>
 *     <li>{@link CE_ERR_FILE_NOT_GRANT} - The file is not granted.</li>
 *     <li>{@link CE_ERR_DISK_FULL} - The disk is full.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_StartWork(ContentEmbed_ExtensionProxy *proxy);

/**
 * @brief Disconnects the communication channel with the OE Extension.
 *
 * @permission ohos.permission.CONNECT_OBJECTEDITOR_EXTENSION
 * @param proxy Pointer to the {@link ContentEmbed_ExtensionProxy} object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_PERMISSION_DENIED} - Permission verification failed.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_SYSTEM_ABNORMAL} - The system service is abnormal.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_StopWork(ContentEmbed_ExtensionProxy *proxy);

/**
 * @brief Obtains the snapshot image of the current OE document from the client OE object for
 * preview or thumbnail display.
 *
 * @param proxy Pointer to the {@link ContentEmbed_ExtensionProxy} object.
 * @param snapshot Output parameter. Pointer to the {@link OH_PixelmapNative} instance that stores the document
 *     snapshot.
 *     <br>You need to call {@link OH_PixelmapNative_Destroy} to destroy the instance to avoid memory leaks.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_EXTENSION_ERROR} - An error occurs in the OE Extension.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *     <li>{@link CE_ERR_EXTENSION_NOT_SUPPORT} - The OE Extension does not support this capability.</li>
 *         </ul>
 * @since 24
 * @release OH_PixelmapNative_Destroy {snapshot}
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_GetSnapshot(ContentEmbed_ExtensionProxy *proxy,
                                                         OH_PixelmapNative **snapshot);

/**
 * @brief Requests the OE Extension instance to enter the edit mode from the client's OE object.
 *
 * @param proxy Pointer to the {@link ContentEmbed_ExtensionProxy} object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_EXTENSION_ERROR} - An error occurs in the OE Extension.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *     <li>{@link CE_ERR_EXTENSION_NOT_SUPPORT} - The OE Extension does not support this capability.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_DoEdit(ContentEmbed_ExtensionProxy *proxy);

/**
 * @brief Queries the current editing state and modification state of the OE document by the server-side OE Extension
 * instance.
 *
 * @param proxy Pointer to the {@link ContentEmbed_ExtensionProxy} object.
 * @param isEditing Output parameter. Indicates whether the content embedded document is being edited. true: being
 *     edited; false: not being edited.
 * @param isModified Output parameter. Indicates whether the content embedded in the document has been modified. The
 *     value true indicates that the password has been changed, and the value false indicates that the password has not
 *     been changed.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - Operations are successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_EXTENSION_ERROR} - An error occurred in the OE Extension.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_GetEditStatus(ContentEmbed_ExtensionProxy *proxy,
                                                           bool *isEditing, bool *isModified);

/**
 * @brief Obtains the capabilities of the server-side OE Extension instance. The capabilities are returned in the form
 * of bit masks. For details about the meaning of each bit, see {@link ContentEmbed_CapabilityCode}.
 *
 * @param proxy Pointer to the {@link ContentEmbed_ExtensionProxy} object.
 * @param bitmask Output parameter. Indicates the capabilities of the server-side OE Extension instance, which are
 *     composed of the values in {@link ContentEmbed_CapabilityCode}.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_EXTENSION_ERROR} - An error occurs in the OE Extension.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_GetCapability(ContentEmbed_ExtensionProxy *proxy,
                                                           uint32_t *bitmask);

/**
 * @brief Obtains the associated OE document object from the client's OE object.
 * <br>The OE document object is created in {@link OH_ContentEmbed_CreateDocumentByOEid},
 * {@link OH_ContentEmbed_CreateDocumentByFile}, or {@link OH_ContentEmbed_LoadDocumentFromFile} mode.
 * <br>When the OE document is no longer needed, call {@link OH_ContentEmbed_DestroyDocument} to destroy it.
 *
 * @param proxy Pointer to the {@link ContentEmbed_ExtensionProxy} object.
 * @param ceDocument Output parameter. Pointer to the pointer that stores the OE document instance.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyDocument {ceDocument}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Proxy_GetDocument(ContentEmbed_ExtensionProxy *proxy,
                                                         ContentEmbed_Document **ceDocument);

#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_CONTENT_EMBED_PROXY_H
