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
 * @brief 内容嵌入（ContentEmbed）模块提供对象编辑（Object Editor，简称OE）功能框架与技术，支持应用间文档的嵌入与协同编辑。
 * 通过OE技术实现的被嵌入文档（简称OE文档），在客户端界面中可能呈现为缩略图或者快照（Snapshot），
 * 也可能以标准格式序列化为一段二进制数据保存在内存或者某个文件（称为OE格式文件）中。
 *
 * @syscap SystemCapability.ContentEmbed.ObjectEditor
 * @since 24
 */

/**
 * @file content_embed_document.h
 *
 * @brief 提供OE技术实现的被嵌入文档（简称OE文档）相关数据结构及对应操作接口。
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
 * @brief 表示支持文件路径的最大长度。
 *
 * @since 24
 */
#define MAX_PATH_LENGTH (4 * 1024)

/**
 * @brief 声明OE文档结构体类型。封装了被嵌入文档的元数据、内容和存储结构。
 *
 * @since 24
 */
typedef struct ContentEmbed_Document ContentEmbed_Document;

/**
 * @brief 声明OE文档Storage结构体类型。类似于文件系统中的目录，Storage对象的父对象必须是另一个Storage对象或根Storage对象。
 *
 * @since 24
 */
typedef struct ContentEmbed_Storage ContentEmbed_Storage;

/**
 * @brief 声明OE文档存储元素的结构体类型。通过{@link OH_ContentEmbed_StorageElement_GetName}获取名称、
 * {@link OH_ContentEmbed_StorageElement_GetCTime}获取创建时间和{@link OH_ContentEmbed_StorageElement_GetMTime}获取修改
 * 时间。可以通过{@link OH_ContentEmbed_StorageElement_IsStorage}判断当前是否是{@link ContentEmbed_Storage}的封装对象，
 * {@link OH_ContentEmbed_StorageElement_IsStream}判断当前是否是{@link ContentEmbed_Stream}的封装对象。
 *
 * @since 24
 */
typedef struct ContentEmbed_StorageElement ContentEmbed_StorageElement;

/**
 * @brief 声明ContentEmbed_StorageElements结构体类型。通过{@link OH_ContentEmbed_Storage_GetElements}获取某个
 * {@link ContentEmbed_Storage}对象下所有的{@link ContentEmbed_Storage}和{@link ContentEmbed_Stream}对象集合，每个对象封装
 * 成{@link ContentEmbed_StorageElement}结构体。可以通过{@link OH_ContentEmbed_StorageElements_GetCount}获取当前查询元素
 * 的数量，{@link OH_ContentEmbed_StorageElements_GetElement}获取指定索引位置的{@link ContentEmbed_StorageElement}实例对象。
 *
 * @since 24
 */
typedef struct ContentEmbed_StorageElements ContentEmbed_StorageElements;

/**
 * @brief 声明OE文档Stream结构体类型。类似于文件系统中的文件，可对其进行读取或写入，且Stream对象只能存在于Storage对象中。
 *
 * @since 24
 */
typedef struct ContentEmbed_Stream ContentEmbed_Stream;

/**
 * @brief 使用提供的标识符OEID创建一个新的{@link ContentEmbed_Document}实例。
 * <br>开发者可通过{@link OH_ContentEmbed_DestroyDocument}销毁实例，以避免内存泄漏。
 *
 * @param oeid 用于唯一表示OE文档的标识符OEID，建议数组长度为{@link MAX_OEID_LENGTH}。
 * @param document 输出参数。该指针指向新创建的OE文档对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyDocument {document}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_CreateDocumentByOEid(
    const char *oeid, ContentEmbed_Document **document);

/**
 * @brief 从源文件创建一个新的{@link ContentEmbed_Document}实例。
 * <br>开发者可通过{@link OH_ContentEmbed_DestroyDocument}销毁实例，以避免内存泄漏。
 *
 * @param srcFilePath 源文件路径。
 * @param length 源文件路径字符串的长度，不包括终止符。
 * @param isLinking 是否以链接方式创建OE文档。true表示以链接方式创建OE文档，当服务端编辑OE文档时，源文件也会被修改；
 *                  <br>false表示以嵌入方式创建OE文档，当客户端请求服务端编辑OE文档时，会先拷贝一份临时文件到客户端应用沙箱目录。
 * @param document 输出参数。该指针指向新创建的OE文档对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *     <li>{@link CE_ERR_INVALID_LINKING_PATH}：表示链接文件在应用沙箱中，无法创建链接。</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyDocument {document}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_CreateDocumentByFile(
    const char *srcFilePath, size_t length, bool isLinking, ContentEmbed_Document **document);

/**
 * @brief 通过已存在的OE格式文件加载{@link ContentEmbed_Document}实例。
 * <br>开发者可通过{@link OH_ContentEmbed_DestroyDocument}销毁实例，以避免内存泄漏。
 *
 * @param srcFilePath 源文件路径，指向要加载的OE格式文件。
 * @param length 源文件路径字符串的长度，不包括终止符。
 * @param document 输出参数。该指针指向新创建的OE文档对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyDocument {document}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_LoadDocumentFromFile(
    const char *srcFilePath, size_t length, ContentEmbed_Document **document);

/**
 * @brief 从OE文档对象的指定偏移位置读取原始二进制数据到缓冲区。
 *
 * @param buffer 输出参数。用于存储从OE文档读取的数据的缓冲区。
 * @param length 缓冲区的大小，单位为字节。
 * @param document 指向OE文档对象指针。
 * @param offset 从OE文档开始读取的字节偏移位置，从0开始。
 * @param readSize 输出参数。实际读取的数据长度，单位为字节。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED}：表示OE格式文件目录相关操作失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Document_Read(
    uint8_t *buffer, size_t length, ContentEmbed_Document *document, size_t offset, size_t *readSize);

/**
 * @brief 从OE文档对象获取标识符OEID。
 *
 * @param document 指向OE文档对象指针。
 * @param oeid 输出参数。用于存储OEID值的字符数组。建议数组长度为{@link MAX_OEID_LENGTH}。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Document_GetOEid(
    const ContentEmbed_Document *document, char *oeid);

/**
 * @brief OE文档是否以链接方式创建。
 *
 * @param document 指向OE文档对象指针。
 * @param isLinking 输出参数。true表示以链接方式创建OE文档；false表示嵌入方式创建OE文档。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Document_IsLinking(
    const ContentEmbed_Document *document, bool *isLinking);

/**
 * @brief 从OE文档中获取客户端沙箱目录下存储的被嵌入源文件路径。
 *
 * @param document 指向OE文档对象指针。
 * @param nativeFilePath 输出参数。用于存储源文件路径的字符数组。建议数组长度为{@link MAX_PATH_LENGTH}。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Document_GetNativeFilePath(
    const ContentEmbed_Document *document, char *nativeFilePath);

/**
 * @brief 从OE文档对象获取根{@link ContentEmbed_Storage}对象。
 * <br>开发者可通过{@link OH_ContentEmbed_DestroyStorage}销毁实例，以避免内存泄漏。
 *
 * @param document 指向OE文档对象指针。
 * @param storage 输出参数。调用成功后，该指针指向OE文档根Storage对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyStorage {storage}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Document_GetRootStorage(
    ContentEmbed_Document *document, ContentEmbed_Storage **storage);

/**
 * @brief 将OE文档中数据落盘至OE格式文件。
 *
 * @param document 指向OE文档对象指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_FILE_OPERATION_FAILED}：表示文件操作失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Document_Flush(const ContentEmbed_Document *document);

/**
 * @brief 根据OE文档父Storage对象和名称创建子{@link ContentEmbed_Storage}对象。
 * <br>开发者可通过{@link OH_ContentEmbed_DestroyStorage}销毁实例，以避免内存泄漏。
 *
 * @param parentStorage 指向OE文档父Storage对象指针。
 *                      <br>当需要从父Storage对象删除指定的子Storage对象时，可以调用{@link OH_ContentEmbed_Storage_DeleteEntry}。
 *                      <br>当需要从父Storage对象删除所有的子Storage对象时，可以调用{@link OH_ContentEmbed_Storage_DeleteAllEntry}。
 * @param name 要创建的子Storage的名称。该参数不能为空字符串，名称长度应不超过31个字符且不能包含非法字符，如：'/'、'\\'、':'和'!'。
 * @param childStorage 输出参数。调用成功后，该指针指向新创建的OE文档子Storage对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败，可能是parentStorage无效或名称无效。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针，可能是childStorage创建失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED}：表示存储操作失败，可能是磁盘空间不足。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyStorage {childStorage}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_CreateStorage(
    const ContentEmbed_Storage *parentStorage, const char *name, ContentEmbed_Storage **childStorage);

/**
 * @brief 从OE文档父Storage对象和名称获取子{@link ContentEmbed_Storage}对象。
 * <br>开发者可通过{@link OH_ContentEmbed_DestroyStorage}销毁实例，以避免内存泄漏。
 *
 * @param parentStorage 指向OE文档父Storage对象指针。
 * @param name 要获取的子Storage的名称。该参数不能为空字符串，名称长度应不超过31个字符且不能包含非法字符，如：'/'、'\\'、':'和'!'。
 * @param childStorage 输出参数。调用成功后，该指针指向找到的OE文档子Storage对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED}：表示OE格式文件目录相关操作失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyStorage {childStorage}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_GetStorage(
    const ContentEmbed_Storage *parentStorage, const char *name, ContentEmbed_Storage **childStorage);

/**
 * @brief 在OE文档父Storage对象和名称创建{@link ContentEmbed_Stream}对象。
 * <br>开发者可通过{@link OH_ContentEmbed_DestroyStream}销毁实例，以避免内存泄漏。
 *
 * @param parentStorage 指向OE文档父Storage对象指针。
 *                      <br>当需要从父Storage对象删除指定的子Stream对象时，可以调用{@link OH_ContentEmbed_Storage_DeleteEntry}。
 *                      <br>当需要从父Storage对象删除所有的子Stream对象时，可以调用{@link OH_ContentEmbed_Storage_DeleteAllEntry}。
 * @param name 要创建的Stream的名称，用于标识和查找该Stream。该参数不能为空字符串，名称长度应不超过31个字符且不能包含非法字符，如：'/'、'\\'、':'和'!'。
 * @param childStream 输出参数。调用成功后，该指针指向新创建的OE文档Stream对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED}：表示OE格式文件目录相关操作失败。</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED}：表示OE格式文件流操作失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyStream {childStream}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_CreateStream(
    ContentEmbed_Storage *parentStorage, const char *name, ContentEmbed_Stream **childStream);

/**
 * @brief 从OE文档父Storage对象和名称获取子{@link ContentEmbed_Stream}对象。
 * <br>开发者可通过{@link OH_ContentEmbed_DestroyStream}销毁实例，以避免内存泄漏。
 *
 * @param parentStorage 指向OE文档父Storage对象指针。
 * @param name 要获取的OE文档Stream对象的名称。该参数不能为空字符串，名称长度应不超过31个字符且不能包含非法字符，如：'/'、'\\'、':'和'!'。
 * @param childStream 输出参数。调用成功后，该指针指向找到的OE文档Stream对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED}：表示OE格式文件目录相关操作失败。</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED}：表示OE格式文件流操作失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @release OH_ContentEmbed_DestroyStream {childStream}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_GetStream(
    ContentEmbed_Storage *parentStorage, const char *name, ContentEmbed_Stream **childStream);

/**
 * @brief 从OE文档父Storage对象删除指定名称的子Storage对象或子Stream对象。
 *
 * @param parentStorage 指向OE文档父Storage对象指针。
 * @param name 要删除的子Storage对象或子Stream对象的名称。该参数不能为空字符串，名称长度应不超过31个字符且不能包含非法字符，如：'/'、'\\'、':'和'!'。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED}：表示OE格式文件目录相关操作失败。</li>
 *     <li>{@link CE_ERR_FILE_OPERATION_FAILED}：表示OE格式文件操作失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_DeleteEntry(
    ContentEmbed_Storage *parentStorage, const char *name);

/**
 * @brief 从OE文档Storage对象删除所有条目，包括子Storage对象和子Stream对象。
 *
 * @param storage 指向OE文档Storage对象指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED}：表示OE格式文件目录相关操作失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_DeleteAllEntry(ContentEmbed_Storage *storage);

/**
 * @brief 销毁OE文档{@link ContentEmbed_Storage}对象实例并回收内存。
 *
 * @param storage 指向OE文档Storage对象指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_DestroyStorage(ContentEmbed_Storage *storage);

/**
 * @brief 从OE文档Stream对象的当前位置读取指定长度的数据到缓冲区。读取成功后，Stream对象的偏移量会按实际读取的字节数递增。
 *
 * @param stream 指向OE文档Stream对象指针。
 * @param buffer 输出参数。指向存储读取数据的缓冲区的指针。函数内部将分配内存，调用者需要负责释放。
 * @param length 要读取的数据的最大字节数。
 * @param num 输出参数。实际读取的数据项数量，单位为字节。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED}：表示流操作失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Stream_Read(
    ContentEmbed_Stream *stream, unsigned char **buffer, size_t length, size_t *num);

/**
 * @brief 将指定长度的数据从缓冲区写入OE文档Stream对象的当前位置。写入成功后，Stream对象的偏移量会按实际写入的字节数递增。
 *
 * @param stream 指向OE文档Stream对象指针。
 * @param data 输入参数。指向要写入数据的缓冲区的指针。
 * @param length 要写入的数据的字节数。
 * @param num 输出参数。实际写入的数据项数量，单位为字节。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED}：表示流操作失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Stream_Write(
    ContentEmbed_Stream *stream, const unsigned char *data, size_t length, size_t *num);

/**
 * @brief 将OE文档Stream对象的当前读取位置设置为指定的偏移量。
 *
 * @param stream 指向OE文档Stream对象指针。
 * @param position 要设置的Stream对象相对起始位置的偏移量，单位为字节，从0开始。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED}：表示OE格式文件流相关操作失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Stream_Seek(ContentEmbed_Stream *stream, size_t position);

/**
 * @brief 获取OE文档Stream对象的当前位置偏移量。
 *
 * @param stream 指向OE文档Stream对象指针。
 * @param position 输出参数。存储Stream对象相对起始位置的偏移量，单位为字节，从0开始。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED}：表示OE格式文件流相关操作失败。</li>
 *     <li>{@link CE_ERR_FILE_OPERATION_FAILED}：表示文件操作失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Stream_GetPosition(ContentEmbed_Stream *stream, size_t *position);

/**
 * @brief 获取OE文档Stream对象的总大小，单位为字节。
 *
 * @param stream 指向OE文档Stream对象指针。
 * @param size 输出参数。存储OE文档Stream对象的总字节大小。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_STREAM_OPERATION_FAILED}：表示OE格式文件流相关操作失败。</li>
 *     <li>{@link CE_ERR_FILE_OPERATION_FAILED}：表示文件操作失败。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Stream_GetSize(ContentEmbed_Stream *stream, size_t *size);

/**
 * @brief 销毁OE文档{@link ContentEmbed_Stream}对象实例并回收内存。
 *
 * @param stream 指向OE文档Stream对象指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_DestroyStream(ContentEmbed_Stream *stream);

/**
 * @brief 销毁{@link ContentEmbed_Document}对象实例并回收内存。
 *
 * @param document 指向OE文档对象指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_DestroyDocument(ContentEmbed_Document *document);

/**
 * @brief 获取OE文档Storage对象的标识符OEID。
 *
 * @param storage 指向OE文档Storage对象指针。
 * @param oeid 输出参数。用于存储标识符OEID的字符数组，建议数组长度为{@link MAX_OEID_LENGTH}。
 * @param oeidSize OEID数组的长度，单位为字节。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED}：表示OE格式文件目录相关操作失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_GetOEid(ContentEmbed_Storage *storage,
    char *oeid, size_t oeidSize);

/**
 * @brief 设置OE文档Storage对象的标识符OEID。
 *
 * @param storage 指向OE文档Storage对象指针。
 * @param oeid 要设置的标识符OEID的字符数组，建议数组长度为{@link MAX_OEID_LENGTH}。
 * @param oeidSize OEID数组的长度，单位为字节。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED}：表示OE格式文件目录相关操作失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_SetOEid(ContentEmbed_Storage *storage,
    char *oeid, size_t oeidSize);

/**
 * @brief 创建并初始化{@link ContentEmbed_StorageElements}实例。
 * <br>开发者可通过{@link OH_ContentEmbed_StorageElements_Destroy}销毁实例，以避免内存泄漏。
 *
 * @param storageElements 输出参数。调用成功后，该指针将指向{@link ContentEmbed_StorageElements}实例。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @release OH_ContentEmbed_StorageElements_Destroy {storageElements}
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElements_Create(ContentEmbed_StorageElements **storageElements);

/**
 * @brief 销毁{@link ContentEmbed_StorageElements}实例并回收其占用的内存。
 *
 * @param storageElements 指向{@link ContentEmbed_StorageElements}实例指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElements_Destroy(ContentEmbed_StorageElements *storageElements);

/**
 * @brief 获取OE文档Storage对象中的元素列表。
 *
 * @param storage 指向OE文档Storage对象指针。
 * @param storageElements 存储OE文档Storage对象中的元素列表。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED}：表示OE格式文件目录相关操作失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_Storage_GetElements(const ContentEmbed_Storage *storage,
    ContentEmbed_StorageElements *storageElements);

/**
 * @brief 获取{@link ContentEmbed_StorageElements}实例的元素数量。
 *
 * @param storageElements 指向{@link ContentEmbed_StorageElements}实例指针。
 * @param count 输出参数。存储元素集合中的元素数量。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElements_GetCount(const ContentEmbed_StorageElements *storageElements,
    size_t *count);

/**
 * @brief 获取{@link ContentEmbed_StorageElements}实例的指定索引位置的元素。
 *
 * @param storageElements 指向{@link ContentEmbed_StorageElements}实例指针。
 * @param index 要获取的元素的索引位置，从0开始计数。
 * @param storageElement 输出参数。获取成功后，返回指向storageElements中索引为index的{@link ContentEmbed_StorageElement}
 *        实例的指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElements_GetElement(const ContentEmbed_StorageElements *storageElements,
    size_t index, ContentEmbed_StorageElement **storageElement);

/**
 * @brief 获取{@link ContentEmbed_StorageElement}实例的名称。
 *
 * @param storageElement 指向{@link ContentEmbed_StorageElement}实例指针。
 * @param name 输出参数。用于存储元素名称字符串。
 * @param nameSize 表示name缓冲区的大小，单位为字节。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElement_GetName(const ContentEmbed_StorageElement *storageElement,
    char *name, size_t nameSize);

/**
 * @brief 获取{@link ContentEmbed_StorageElement}实例的创建时间戳，单位为毫秒。
 *
 * @param element 指向{@link ContentEmbed_StorageElement}实例指针。
 * @param ctime 输出参数。指向元素的创建时间戳，单位为毫秒。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElement_GetCTime(
    const ContentEmbed_StorageElement *element, uint64_t *ctime);

/**
 * @brief 获取{@link ContentEmbed_StorageElement}实例的最后修改时间戳，单位为毫秒。
 *
 * @param element 指向{@link ContentEmbed_StorageElement}实例指针。
 * @param mtime 输出参数。指向元素的最后修改时间戳，单位为毫秒。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElement_GetMTime(
    const ContentEmbed_StorageElement *element, uint64_t *mtime);

/**
 * @brief 检查{@link ContentEmbed_StorageElement}实例是否为OE文档Storage对象。
 *
 * @param storageElement 指向{@link ContentEmbed_StorageElement}实例指针。
 * @param isStorage 输出参数。true表示是OE文档Storage对象；false表示不是OE文档Storage对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElement_IsStorage(const ContentEmbed_StorageElement *storageElement,
    bool *isStorage);

/**
 * @brief 检查{@link ContentEmbed_StorageElement}实例是否为OE文档Stream对象。
 *
 * @param element 指向{@link ContentEmbed_StorageElement}实例指针。
 * @param isStream 输出参数。true表示是OE文档Stream对象；false表示不是OE文档Stream对象。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
 *         </ul>
 * @since 24
 */
ContentEmbed_ErrorCode OH_ContentEmbed_StorageElement_IsStream(
    const ContentEmbed_StorageElement *element, bool *isStream);

/**
 * @brief 将源OE文档Storage对象中的所有子Storage对象和Stream对象复制到目标OE文档Storage对象。
 *
 * @param srcStorage 指向源OE文档Storage对象指针。
 * @param destStorage 指向目标OE文档Storage对象指针。
 * @return <ul>
 *     <li>{@link CE_ERR_OK}：表示操作成功。</li>
 *     <li>{@link CE_ERR_PARAM_INVALID}：表示参数检查失败。</li>
 *     <li>{@link CE_ERR_NULL_POINTER}：表示返回空指针。</li>
 *     <li>{@link CE_ERR_STORAGE_OPERATION_FAILED}：表示存储操作失败。</li>
 *     <li>{@link CE_ERR_DEVICE_NOT_SUPPORTED}：表示设备不支持。</li>
 *     <li>{@link CE_ERR_IN_DLP_SANDBOX}：表示应用在DLP沙箱中，不支持此操作。</li>
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