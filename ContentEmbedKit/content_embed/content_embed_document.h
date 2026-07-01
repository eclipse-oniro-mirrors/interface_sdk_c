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
 * @file content_embed_document.h
 *
 * @brief Provides the data structures and corresponding operation APIs related to the embedded documents (OE documents)
 *  implemented using the OE technology.
 *
 * @library libcontent_embed_ndk.so
 * @kit ContentEmbedKit
 * @syscap SystemCapability.ContentEmbed.ObjectEditor
 * @since 24
 */

#ifndef OHOS_CONTENT_EMBED_DOCUMENT_H
#define OHOS_CONTENT_EMBED_DOCUMENT_H

#include <stdint.h>
#include <stdlib.h>
#include <cstdio>
#include "content_embed_common.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Indicates the maximum length of a file path.
 *
 * @since 24
 */
#define MAX_PATH_LENGTH (4 * 1024)

/**
 * @brief Declares the structure type of an OE document. Encapsulates the metadata, content, and storage structure of
 * the embedded document.
 *
 * @since 24
 */
typedef struct ContentEmbed_Document ContentEmbed_Document;

/**
 * @brief Declares the storage structure type of an OE document. Similar to a directory in a file system, the
 * parent object of a storage object must be another storage object or the root storage object.
 *
 * @since 24
 */
typedef struct ContentEmbed_Storage ContentEmbed_Storage;

/**
 * @brief Defines the structure type of a storage element in an OE document.
 * Use {@link OH_ContentEmbed_StorageElement_GetName} to get the name,
 * {@link OH_ContentEmbed_StorageElement_GetCTime} to get the creation time,
 * and {@link OH_ContentEmbed_StorageElement_GetMTime} to get the modification time.
 * Use {@link OH_ContentEmbed_StorageElement_IsStorage} to determine if the current object is an encapsulation
 * of {@link ContentEmbed_Storage}, and {@link OH_ContentEmbed_StorageElement_IsStream} to determine if it is an
 * encapsulation of {@link ContentEmbed_Stream}.
 *
 * @since 24
 */
typedef struct ContentEmbed_StorageElement ContentEmbed_StorageElement;

/**
 * @brief Declares the ContentEmbed_StorageElements structure.
 * Use {@link OH_ContentEmbed_Storage_GetElements} to retrieve the collection of all {@link ContentEmbed_Storage} and
 * {@link ContentEmbed_Stream} objects under a specific {@link ContentEmbed_Storage} object, with each object
 * encapsulated as a {@link ContentEmbed_StorageElement} struct.
 * Use {@link OH_ContentEmbed_StorageElements_GetCount} to get the number of elements in the current query,
 * and {@link OH_ContentEmbed_StorageElements_GetElement} to obtain the {@link ContentEmbed_StorageElement} instance
 * object at a specified index position.
 *
 * @since 24
 */
typedef struct ContentEmbed_StorageElements ContentEmbed_StorageElements;

/**
 * @brief Declares the stream structure type of an OE document. Similar to a file in the file system, a stream
 * can be read or written. A stream object can exist only in the storage object.
 *
 * @since 24
 */
typedef struct ContentEmbed_Stream ContentEmbed_Stream;

/**
 * @brief Creates a new {@link ContentEmbed_Document} instance using the provided identifier OEID.
 * <br>You can destroy the instance using {@link OH_ContentEmbed_DestroyDocument} to avoid memory leaks.
 *
 * @param oeid Identifier of the OE document, which is used to uniquely identify the OE document. It is recommended
 *     that the array length be {@link MAX_OEID_LENGTH}.
 * @param document Output parameter. This pointer points to the newly created OE document object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyDocument {document}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_CreateDocumentByOEid(
    const char *oeid, ContentEmbed_Document **document);

/**
 * @brief Creates a new {@link ContentEmbed_Document} instance from a source file.
 * <br>You can destroy the instance using {@link OH_ContentEmbed_DestroyDocument} to avoid memory leakage.
 *
 * @param srcFilePath Source file path.
 * @param length Length of the source file path string, excluding the terminator.
 * @param isLinking Whether to create an OE document in link mode. true: The OE document is created in link mode. When
 *     the server edits the OE document, the source file is also modified.
 *     <br>false: The OE document is created in embedded mode. When the server edits the OE document in response to a
 *     client request, a temporary file is copied to the sandbox directory of the client app.
 * @param document Output parameter. This pointer points to the newly created OE document object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - indicates that the operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - indicates that the parameter check fails.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - indicates that a null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - indicates that the device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *     <li>{@link CE_ERR_INVALID_LINKING_PATH} - indicates that the link file is in the app sandbox and the link
 *      cannot be created. </li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyDocument {document}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_CreateDocumentByFile(
    const char *srcFilePath, size_t length, bool isLinking, ContentEmbed_Document **document);

/**
 * @brief Loads an {@link ContentEmbed_Document} instance using an existing file in the OE format.
 * <br>You can destroy the instance using {@link OH_ContentEmbed_DestroyDocument} to avoid memory leaks.
 *
 * @param srcFilePath Source file path, which points to the file to be loaded in the OE format.
 * @param length Length of the source file path string, excluding the terminator.
 * @param document Output parameter. This pointer points to the newly created OE document object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyDocument {document}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_LoadDocumentFromFile(
    const char *srcFilePath, size_t length, ContentEmbed_Document **document);

/**
 * @brief Reads the original binary data from the specified offset position of the OE document object to the buffer.
 *
 * @param buffer Output parameter. Buffer for storing the data read from the OE document.
 * @param length Size of the buffer, in bytes.
 * @param document Pointer to the OE document object.
 * @param offset Offset position from which the data is read in the OE document, starting from 0.
 * @param readSize Output parameter. Length of the actually read data, in bytes.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED} - Operations related to the OE file directory failed.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Document_Read(
    uint8_t *buffer, size_t length, ContentEmbed_Document *document, size_t offset, size_t *readSize);

/**
 * @brief Obtains the identifier OEID from the OE document object.
 *
 * @param document Pointer to the OE document object.
 * @param oeid Output parameter. Character array for storing the OEID value. The recommended array length is
 *     {@link MAX_OEID_LENGTH}.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Document_GetOEid(
    const ContentEmbed_Document *document, char *oeid);

/**
 * @brief Checks whether an OE document is created in link mode.
 *
 * @param document Pointer to the OE document object.
 * @param isLinking Output parameter. true indicates that the OE document is created in link mode. false indicates that
 *     the OE document is created in embedded mode.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Document_IsLinking(
    const ContentEmbed_Document *document, bool *isLinking);

/**
 * @brief Obtains the embedded source file path stored in the client sandbox directory from the OE document.
 *
 * @param document Pointer to the OE document object.
 * @param nativeFilePath Output parameter. Character array for storing the source file path. It is recommended that the
 *     array length be {@link MAX_PATH_LENGTH}.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Document_GetNativeFilePath(
    const ContentEmbed_Document *document, char *nativeFilePath);

/**
 * @brief Obtains the root {@link ContentEmbed_Storage} object from an OE document object.
 * <br>You can destroy the instance using {@link OH_ContentEmbed_DestroyStorage} to avoid memory leaks.
 *
 * @param document Pointer to the {@link ContentEmbed_Document}t object.
 * @param storage Output parameter. After the API is successfully called, this pointer points to the root storage
 *     object of the OE document.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameters.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyStorage {storage}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Document_GetRootStorage(
    ContentEmbed_Document *document, ContentEmbed_Storage **storage);

/**
 * @brief Flushes data in an OE document to an OE format file.
 *
 * @param document Pointer to the OE document object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_FILE_OPERATION_FAILED} - Failed to perform the file operation.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Document_Flush(const ContentEmbed_Document *document);

/**
 * @brief Creates a child {@link ContentEmbed_Storage} object based on the parent storage object and name of the OE
 * document.
 * <br>You can destroy the instance using {@link OH_ContentEmbed_DestroyStorage} to avoid memory leaks.
 *
 * @param parentStorage Pointer to the parent storage object of the OE document.
 *     <br>To delete a specified child storage object from the parent storage object, call
 *     {@link OH_ContentEmbed_Storage_DeleteEntry}.
 *     <br>To delete all child storage objects from the parent storage object, call
 *     {@link OH_ContentEmbed_Storage_DeleteAllEntry}.
 * @param name Name of the child storage object to be created. The value cannot be an empty string. It can contain a
 *     maximum of 31 characters and cannot contain invalid characters, such as '/', '\', ':', and '!'.
 * @param childStorage Output parameter. After the function is successfully called, the pointer points to the newly
 *     created child storage object of the OE document.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails. The possible cause is that the parentStorage
 *      or name is invalid.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - The returned pointer is null. The possible cause is that the childStorage fails
 *      to be created.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED} - The storage operation fails. The possible cause is that the disk
 *     space is insufficient.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyStorage {childStorage}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_CreateStorage(
    const ContentEmbed_Storage *parentStorage, const char *name, ContentEmbed_Storage **childStorage);

/**
 * @brief Obtains the child {@link ContentEmbed_Storage} object from the parent Storage object and name of the OE
 * document.
 * <br>You can destroy the instance by calling {@link OH_ContentEmbed_DestroyStorage} to avoid memory leaks.
 *
 * @param parentStorage Pointer to the parent Storage object of the OE document.
 * @param name Name of the child Storage object to be obtained. The value cannot be an empty string. It can contain a
 *     maximum of 31 characters and cannot contain invalid characters such as '/', '\', ':', and '!'.
 * @param childStorage Output parameter. After the API is successfully called, the pointer points to the found child
 *     Storage object of the OE document.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - indicates that the operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - indicates that the parameter check fails.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - indicates that a null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - indicates that the device is not supported.</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED} - indicates that the operation related to the directory of the
 *     OE document fails.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyStorage {childStorage}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_GetStorage(
    const ContentEmbed_Storage *parentStorage, const char *name, ContentEmbed_Storage **childStorage);

/**
 * @brief Creates a {@link ContentEmbed_Stream} object for the parent storage object and name of an OE document.
 * <br>You can destroy the instance using {@link OH_ContentEmbed_DestroyStream} to avoid memory leaks.
 *
 * @param parentStorage Pointer to the parent storage object of an OE document.
 *     <br>You can call {@link OH_ContentEmbed_Storage_DeleteEntry} to delete a specified child stream object from the
 *     parent storage object.
 *     <br>You can call {@link OH_ContentEmbed_Storage_DeleteAllEntry} to delete all child stream objects from the
 *     parent storage object.
 * @param name Name of the stream to be created, which is used to identify and search for the stream. The value cannot
 *     be an empty string. It can contain a maximum of 31 characters and cannot contain invalid characters, such as '/',
 *     '\', ':', and '!'.
 * @param childStream Output parameter. After the call is successful, the pointer points to the newly created stream
 *     object of the OE document.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED} - Operations related to the directory of the OE document failed.</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED} - Operations related to the stream of the OE document failed.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyStream {childStream}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_CreateStream(
    ContentEmbed_Storage *parentStorage, const char *name, ContentEmbed_Stream **childStream);

/**
 * @brief Obtains the child {@link ContentEmbed_Stream} object from the parent storage object and name of the OE
 * document.
 * <br>You can destroy the instance using {@link OH_ContentEmbed_DestroyStream} to avoid memory leaks.
 *
 * @param parentStorage Pointer to the parent storage object of the OE document.
 * @param name Name of the stream object of the OE document to be obtained. The parameter cannot be an empty string.
 *     The name can contain a maximum of 31 characters and cannot contain invalid characters, such as '/', '\', ':',
 *     and '!'.
 * @param childStream Output parameter. After the call succeeds, the pointer points to the found stream object of the
 *     OE document.
  * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED} - Operations related to the directory of the OE document fail.</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED} - Operations related to the stream of the OE document fail.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyStream {childStream}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_GetStream(
    ContentEmbed_Storage *parentStorage, const char *name, ContentEmbed_Stream **childStream);

/**
 * @brief Deletes a child storage object or stream object with a specified name from the parent storage object of the
 * OE document.
 *
 * @param parentStorage Pointer to the parent storage object of the OE document.
 * @param name Name of the child storage object or stream object to be deleted. The parameter cannot be an empty string.
 *     The name can contain a maximum of 31 characters and cannot contain invalid characters, such as '/', '\', ':',
 *     and '!'.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED} - Operations related to the directory of the OE file failed.</li>
 *     <li>{@link CE_ERR_FILE_OPERATION_FAILED} - Operations on the OE file failed.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_DeleteEntry(
    ContentEmbed_Storage *parentStorage, const char *name);

/**
 * @brief Deletes all entries from the storage object of an OE document, including the sub-storage objects and
 * sub-stream objects.
 *
 * @param storage Pointer to the storage object of an OE document.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED} - Operations related to the directory of the OE file failed.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_DeleteAllEntry(ContentEmbed_Storage *storage);

/**
 * @brief Destroys the {@link ContentEmbed_Storage} object instance of an OE document and reclaims the memory.
 *
 * @param storage Pointer to the storage object of an OE document.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_DestroyStorage(ContentEmbed_Storage *storage);

/**
 * @brief Reads data of a specified length from the current position of the stream object of an OE document to
 * the buffer. After the data is successfully read, the offset of the stream object increases by the number of actually
 * read bytes.
 *
 * @param stream Pointer to the stream object of an OE document.
 * @param buffer Output parameter. Pointer to the buffer for storing the read data. The memory is allocated internally
 *     in the function. The caller needs to release the memory.
 * @param length Maximum number of bytes of data to be read.
 * @param num Output parameter. Number of actually read data items, in bytes.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED} - Failed to perform the stream operation.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Stream_Read(
    ContentEmbed_Stream *stream, unsigned char **buffer, size_t length, size_t *num);

/**
 * @brief Writes data of a specified length from the buffer to the current position of the stream object in the OE
 * document. After the data is successfully written, the offset of the stream object increases by the number of
 * actually written bytes.
 *
 * @param stream Pointer to the stream object in the OE document.
 * @param data Input parameter. Pointer to the buffer where data is to be written.
 * @param length Number of bytes of data to be written.
 * @param num Output parameter. Number of actually written data items, in bytes.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED} - The stream operation fails.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Stream_Write(
    ContentEmbed_Stream *stream, const unsigned char *data, size_t length, size_t *num);

/**
 * @brief Sets the current read location of the stream object in an OE document to the specified offset.
 *
 * @param stream Pointer to the stream object in an OE document.
 * @param position Offset of the stream object relative to the start position, in bytes. The value starts from 0.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED} - Failed to perform operations on the stream object in an OE document.
 *     </li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Stream_Seek(ContentEmbed_Stream *stream, size_t position);

/**
 * @brief Obtains the current position offset of the stream object in an OE document.
 *
 * @param stream Pointer to the stream object of the OE document.
 * @param position Output parameter. Offset of the stream object relative to the start position, in bytes. The value
 *     starts from 0.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED} - Operations related to the stream object of the OE document failed.
 *     </li>
 *     <li>{@link CE_ERR_FILE_OPERATION_FAILED} - The file operation failed.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Stream_GetPosition(ContentEmbed_Stream *stream, size_t *position);

/**
 * @brief Obtains the total size of the stream object of the OE document, in bytes.
 *
 * @param stream Pointer to the stream object of the OE document.
 * @param size Output parameter. Total size of the stream object of the OE document, in bytes.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED} - Operations related to the stream of the OE file failed.</li>
 *     <li>{@link CE_ERR_FILE_OPERATION_FAILED} - The file operation failed.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Stream_GetSize(ContentEmbed_Stream *stream, size_t *size);

/**
 * @brief Destroys the {@link ContentEmbed_Stream} object instance of an OE document and reclaims the memory.
 *
 * @param stream Pointer to the stream object of an OE document.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check failed.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_DestroyStream(ContentEmbed_Stream *stream);

/**
 * @brief Destroys the {@link ContentEmbed_Document} object instance and reclaims the memory.
 *
 * @param document Pointer to the OE document object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_DestroyDocument(ContentEmbed_Document *document);

/**
 * @brief Obtains the identifier (OEID) of the storage object of an OE document.
 *
 * @param storage Pointer to the storage object of an OE document.
 * @param oeid Output parameter. Character array for storing the identifier OEID. It is recommended that the array
 *     length be {@link MAX_OEID_LENGTH}.
 * @param oeidSize Length of the OEID array, in bytes.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED} - Operations related to the directory of the OE document fail.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_GetOEid(ContentEmbed_Storage *storage,
    char *oeid, size_t oeidSize);

/**
 * @brief Sets the identifier of the storage object in an OE document.
 *
 * @param storage Pointer to the storage object in an OE document.
 * @param oeid Character array of the identifier OEID to be set. It is recommended that the array length be
 *     {@link MAX_OEID_LENGTH}.
 * @param oeidSize Length of the OEID array, in bytes.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED} - Operations on the Storage object of the OE document failed.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_SetOEid(ContentEmbed_Storage *storage,
    char *oeid, size_t oeidSize);

/**
 * @brief Creates and initializes a {@link ContentEmbed_StorageElements} instance.
 * <br>You can destroy the instance using {@link OH_ContentEmbed_StorageElements_Destroy} to avoid memory leaks.
 *
 * @param storageElements Output parameter. After the call is successful, the pointer points to the
 *     {@link ContentEmbed_StorageElements} instance.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @release OH_ContentEmbed_StorageElements_Destroy {storageElements}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElements_Create(ContentEmbed_StorageElements **storageElements);

/**
 * @brief Destroys a {@link ContentEmbed_StorageElements} instance and reclaims the memory occupied by it.
 *
 * @param storageElements Pointer to the {@link ContentEmbed_StorageElements} instance.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElements_Destroy(ContentEmbed_StorageElements *storageElements);

/**
 * @brief Obtains the element list in the storage object of an OE document.
 *
 * @param storage Pointer to the storage object of an OE document.
 * @param storageElements Element list in the storage object of an OE document.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - indicates that the operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - indicates that the parameter check fails.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - indicates that a null pointer is returned.</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED} - Operations on the Storage object of the OE document failed.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - indicates that the device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 *     sandbox.
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_GetElements(const ContentEmbed_Storage *storage,
    ContentEmbed_StorageElements *storageElements);

/**
 * @brief Obtains the number of elements in a {@link ContentEmbed_StorageElements} instance.
 *
 * @param storageElements Pointer to the {@link ContentEmbed_StorageElements} instance.
 * @param count Output parameter. Number of elements in the element set.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - indicates that the operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - indicates that the parameter check fails.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElements_GetCount(const ContentEmbed_StorageElements *storageElements,
    size_t *count);

/**
 * @brief Obtains the element at the specified index position of the {@link ContentEmbed_StorageElements} instance.
 *
 * @param storageElements Pointer to the {@link ContentEmbed_StorageElements} instance.
 * @param index Index position of the element to be obtained, starting from 0.
 * @param storageElement Output parameter. Upon successful retrieval, returns a pointer to the
 *        {@link ContentEmbed_StorageElement} instance at the specified index in storageElements.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>.
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElements_GetElement(const ContentEmbed_StorageElements *storageElements,
    size_t index, ContentEmbed_StorageElement **storageElement);

/**
 * @brief Obtains the name of a {@link ContentEmbed_StorageElement} instance.
 *
 * @param storageElement Pointer to the {@link ContentEmbed_StorageElement} instance.
 * @param name Output parameter. Used to store the element name string.
 * @param nameSize Size of the name buffer, in bytes.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElement_GetName(const ContentEmbed_StorageElement *storageElement,
    char *name, size_t nameSize);

/**
 * @brief Obtains the creation timestamp of a {@link ContentEmbed_StorageElement} instance, in milliseconds.
 *
 * @param element Pointer to the {@link ContentEmbed_StorageElement} instance.
 * @param ctime Output parameter. Pointer to the creation timestamp of the element, in milliseconds.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - The returned pointer is null.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElement_GetCTime(
    const ContentEmbed_StorageElement *element, uint64_t *ctime);

/**
 * @brief Obtains the last modification timestamp of an {@link ContentEmbed_StorageElement} instance, in milliseconds.
 *
 * @param element Pointer to the {@link ContentEmbed_StorageElement} instance.
 * @param mtime Output parameter. Pointer to the last modification timestamp of the element, in milliseconds.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - The operation is successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElement_GetMTime(
    const ContentEmbed_StorageElement *element, uint64_t *mtime);

/**
 * @brief Checks whether the {@link ContentEmbed_StorageElement} instance is the storage object of an OE document.
 *
 * @param storageElement Pointer to the {@link ContentEmbed_StorageElement} instance.
 * @param isStorage Output parameter. The value true indicates that the instance is an OE document storage object, and
 *     the value false indicates that it is not.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - Operations are successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Failed to check the parameter.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElement_IsStorage(const ContentEmbed_StorageElement *storageElement,
    bool *isStorage);

/**
 * @brief Checks whether the {@link ContentEmbed_StorageElement} instance is an OE document stream object.
 *
 * @param element Pointer to the {@link ContentEmbed_StorageElement} instance.
 * @param isStream Output parameter. The value true indicates that the object is an OE document stream object, and the
 *     value false indicates that the object is not an OE document stream object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - Operations are successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - Parameter check failed.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElement_IsStream(
    const ContentEmbed_StorageElement *element, bool *isStream);

/**
 * @brief Copies all sub-storage objects and stream objects from the source OE document storage object to the target OE
 * document storage object.
 *
 * @param srcStorage Pointer to the source OE document storage object.
 * @param destStorage Pointer to the target OE document storage object.
 * @return <ul>
 *     <li>{@link CE_ERR_OK} - Operations are successful.</li>
 *     <li>{@link CE_ERR_PARAM_INVALID} - The parameter check fails.</li>
 *     <li>{@link CE_ERR_NULL_POINTER} - A null pointer is returned.</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED} - The storage operation fails.</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED} - The device is not supported.</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX} - This operation is not supported because the application is in
 *     the DLP sandbox.</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_CopyTo(ContentEmbed_Storage *srcStorage,
    ContentEmbed_Storage *destStorage);

#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_CONTENT_EMBED_DOCUMENT_H
