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
 * @addtogroup UDMF
 * @{
 *
 * @brief 统一数据管理框架旨在定义数据跨应用、跨设备以及跨平台过程中的各项标准，
 * 提供统一的OpenHarmony数据语言和标准化的数据接入与读取通路。
 *
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */
/**
 * @file uds.h
 *
 * @brief 提供标准化数据结构相关接口函数、结构体定义。当参数类型为char*时，字符串必须以空字符（'\0'）结尾，否则可能导致未定义行为或函数返回错误。
 *
 * @kit ArkData
 * @library libudmf.so
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 * @since 12
 */

#ifndef UDS_H
#define UDS_H

#include <stdbool.h>
#include <inttypes.h>
#include "multimedia/image_framework/image/pixelmap_native.h"

#ifdef __cplusplus

extern "C" {
#endif

/**
 * @brief 拖拽场景下的URI授权策略。
 *
 * > **说明：**
 * > 此授权策略仅在拖拽场景下生效，其他场景不生效。
 *
 * 支持不授权、读、写、持久化四种权限策略，可组合使用，仅以下组合生效：
 *
 * - 仅使用NONE：不做任何文件授权。
 * - 仅使用READ：仅做单次只读授权。
 * - 仅使用WRITE：做单次读、写授权（写授权包含读授权）。
 * - READ+WRITE：做单次读、写授权，与仅写授权等同。
 * - READ+PERSIST：做持久化读授权。
 * - WRITE+PERSIST：做持久化读写授权。
 * - READ+WRITE+PERSIST：做持久化读写授权。
 *
 * 拖拽授权策略应用规则（按优先级从高到低）：
 *
 * - 单个数据级别：FileUri、HTML两个UDS支持配置授权策略参数，仅对单个record单次生效，优先级最高。
 * - [OH_UdmfData](capi-udmf-oh-udmfdata.md)级别：[OH_UdmfProperty](capi-udmf-oh-udmfproperty.md)中提供的授权参数对单次
 * 拖拽有效。若某个数据中配置了授权策略，则优先按照该数据的配置进行，优先级次之。
 * - 默认级别：若单个数据和[OH_UdmfProperty](capi-udmf-oh-udmfproperty.md)均未配置授权策略，则按照拖拽默认逻辑进行代理授权。默认逻辑如下：
 *
 *    - FileUri类型数据：拖拽场景下默认授权为READ+WRITE+PERSIST（读+写+持久化授权）。
 *    - HTML类型数据：仅针对HTML文本中img标签下的uri做读授权。
 *
 * @since 26.0.0
 */
typedef enum Udmf_AuthPermission {
    /**
     * @brief 表示未授予任何权限。
     *
     * @since 26.0.0
     */
    UDMF_PERM_NONE = 0,
    /**
     * @brief 表示读取或查看数据的权限。
     *
     * @since 26.0.0
     */
    UDMF_PERM_READ = 1u << 0,
    /**
     * @brief 表示修改数据的权限（包含READ）。
     *
     * @since 26.0.0
     */
    UDMF_PERM_WRITE = 1u << 1,
    /**
     * @brief 表示持久化文件的权限。
     *
     * @since 26.0.0
     */
    UDMF_PERM_PERSIST = 1u << 2,
} Udmf_AuthPermission;

/**
 * @brief 描述纯文本类型数据的统一数据结构。
 *
 * @since 12
 */
typedef struct OH_UdsPlainText OH_UdsPlainText;

/**
 * @brief 描述超链接类型的统一数据结构。
 *
 * @since 12
 */
typedef struct OH_UdsHyperlink OH_UdsHyperlink;

/**
 * @brief 描述超文本标记语言类型的统一数据结构。
 *
 * @since 12
 */
typedef struct OH_UdsHtml OH_UdsHtml;

/**
 * @brief 描述桌面图标类型的统一数据结构。
 *
 * @since 12
 */
typedef struct OH_UdsAppItem OH_UdsAppItem;

/**
 * @brief 描述文件Uri类型的统一数据结构。
 *
 * @since 13
 */
typedef struct OH_UdsFileUri OH_UdsFileUri;

/**
 * @brief 描述虚拟文件或虚拟目录节点。
 *
 * @since 26.1.0
 */
typedef struct OH_UDMF_VirtualItem OH_UDMF_VirtualItem;

/**
 * @brief 描述虚拟文件入口及其数据回调。
 *
 * @since 26.1.0
 */
typedef struct OH_UDMF_VirtualFileInfo OH_UDMF_VirtualFileInfo;

/**
 * @brief 描述虚拟节点类型。
 *
 * @since 26.1.0
 */
typedef enum OH_UDMF_VirtualItemType {
    /**
     * @brief 虚拟文件。
     *
     * @since 26.1.0
     */
    OH_UDMF_VIRTUAL_ITEM_FILE = 0,
    /**
     * @brief 虚拟目录。
     *
     * @since 26.1.0
     */
    OH_UDMF_VIRTUAL_ITEM_DIRECTORY = 1,
} OH_UDMF_VirtualItemType;

/**
 * @brief 需要获取虚拟文件元数据时调用。
 *
 * 返回的节点必须由{@link OH_UDMF_CreateVirtualFileItem}创建，其所有权将转移给UDMF，回调返回后不得销毁该节点。
 *
 * @param context [in] 通过{@link OH_UDMF_CreateVirtualFileInfo}传入的用户上下文。
 * @param id [in] 请求的虚拟文件标识。
 * @return 成功时返回虚拟文件节点，失败时返回nullptr。
 * @since 26.1.0
 */
typedef OH_UDMF_VirtualItem* (*OH_UDMF_VirtualFileOnStat)(void* context, const char* id);

/**
 * @brief 需要读取虚拟文件数据时调用。
 *
 * 回调最多将<code>length</code>字节写入<code>data</code>，并通过<code>bytesRead</code>返回实际写入字节数。
 * 实际字节数可以小于<code>length</code>，也可以为零。
 *
 * @param context [in] 通过{@link OH_UDMF_CreateVirtualFileInfo}传入的用户上下文。
 * @param id [in] 请求的虚拟文件标识。
 * @param offset [in] 读取偏移量，单位为字节。
 * @param length [in] 最大读取长度。
 * @param data [out] UDMF提供的目标缓冲区，仅在回调执行期间有效。
 * @param bytesRead [out] 实际写入<code>data</code>的字节数。
 * @return 返回执行状态码。具体请参阅{@link Udmf_ErrCode}。
 *         <ul>
 *         <li>{@link UDMF_E_OK} 表示数据读取成功。</li>
 *         <li>{@link UDMF_E_INVALID_PARAM} 表示传入了无效参数。</li>
 *         <li>{@link UDMF_ERR} 表示发生内部错误，无法提供数据。</li>
 *         </ul>
 * @see Udmf_ErrCode
 * @since 26.1.0
 */
typedef int (*OH_UDMF_VirtualFileOnRead)(void* context, const char* id, int64_t offset, uint32_t length,
    uint8_t* data, uint32_t* bytesRead);

/**
 * @brief 取消虚拟文件操作时调用。
 *
 * @param context [in] 通过{@link OH_UDMF_CreateVirtualFileInfo}传入的用户上下文。
 * @param idList [in] 被取消的虚拟文件标识列表。
 *                   该数组及其中的字符串仅在回调执行期间有效。
 * @param count [in] <code>idList</code>中的标识数量。
 * @return 返回执行状态码。具体请参阅{@link Udmf_ErrCode}。
 *         <ul>
 *         <li>{@link UDMF_E_OK} 表示取消成功。</li>
 *         <li>{@link UDMF_E_INVALID_PARAM} 表示传入了无效参数。</li>
 *         <li>{@link UDMF_ERR} 表示发生内部错误，取消失败。</li>
 *         </ul>
 * @see Udmf_ErrCode
 * @since 26.1.0
 */
typedef int (*OH_UDMF_VirtualFileOnCancel)(void* context, const char* const *idList, uint32_t count);

/**
 * @brief 释放UDMF持有的用户上下文。
 *
 * 引用该上下文的全部虚拟文件对象释放后，此回调仅执行一次。回调可能在任意线程执行。
 *
 * @param context [in] 待释放的用户上下文。
 * @since 26.1.0
 */
typedef void (*OH_UDMF_VirtualFileFinalize)(void* context);

/**
 * @brief 描述用于提供虚拟文件元数据和内容的回调。
 *
 * <code>structSize</code>必须设置为<code>sizeof(OH_UDMF_VirtualFileCallbacks)</code>。
 * <code>onRead</code>为必选回调，<code>onStat</code>和<code>onCancel</code>为可选回调；所有文件必须预先声明大小。
 * 不需要取消通知时，将<code>onCancel</code>设置为nullptr。
 * 不同线程可能并发调用回调，回调不得无限期阻塞。
 *
 * @since 26.1.0
 */
typedef struct OH_UDMF_VirtualFileCallbacks {
    /**
     * @brief 结构体大小。
     *
     * @since 26.1.0
     */
    uint32_t structSize;
    /**
     * @brief 可选的元数据回调。
     *
     * @since 26.1.0
     */
    OH_UDMF_VirtualFileOnStat onStat;
    /**
     * @brief 必选的内容读取回调。
     *
     * @since 26.1.0
     */
    OH_UDMF_VirtualFileOnRead onRead;
    /**
     * @brief 可选的取消回调。为nullptr时，取消操作成功，不通知提供方。
     *
     * @since 26.1.0
     */
    OH_UDMF_VirtualFileOnCancel onCancel;
} OH_UDMF_VirtualFileCallbacks;

/**
 * @brief 描述像素图类型的统一数据结构。
 *
 * @since 13
 */
typedef struct OH_UdsPixelMap OH_UdsPixelMap;

/**
 * @brief 描述内容卡片类型的统一数据结构。
 *
 * @since 14
 */
typedef struct OH_UdsContentForm OH_UdsContentForm;

/**
 * @brief 描述ArrayBuffer类型的统一数据结构。
 *
 * @since 13
 */
typedef struct OH_UdsArrayBuffer OH_UdsArrayBuffer;

/**
 * @brief 描述字典类型的统一数据结构。
 *
 * @since 22
 */
typedef struct OH_UdsDetails OH_UdsDetails;

/**
 * @brief 创建纯文本类型{@link OH_UdsPlainText}指针及实例对象。当不再需要使用指针时，请使用{@link OH_UdsPlainText_Destroy}销毁实例对象，否则会导致内存泄漏。
 *
 * @return 执行成功则返回一个指向纯文本类型{@link OH_UdsPlainText}实例对象的指针，否则返回nullptr。
 * @see OH_UdsPlainText
 * @since 12
 */
OH_UdsPlainText* OH_UdsPlainText_Create();

/**
 * @brief 销毁纯文本类型数据{@link OH_UdsPlainText}指针指向的实例对象。
 *
 * @param pThis 表示指向{@link OH_UdsPlainText}实例的指针。
 * @see OH_UdsPlainText
 * @since 12
 */
void OH_UdsPlainText_Destroy(OH_UdsPlainText* pThis);

/**
 * @brief 从纯文本类型{@link OH_UdsPlainText}中获取类型ID。
 *
 * @param pThis 表示指向纯文本类型{@link OH_UdsPlainText}实例的指针。
 * @return 输入有效入参时返回类型ID的字符串指针，否则返回nullptr。
 * @see OH_UdsPlainText
 * @since 12
 */
const char* OH_UdsPlainText_GetType(OH_UdsPlainText* pThis);

/**
 * @brief 从纯文本类型{@link OH_UdsPlainText}中获取纯文本内容信息。
 *
 * @param pThis 表示指向纯文本类型{@link OH_UdsPlainText}实例的指针。
 * @return 输入有效入参时返回纯文本内容信息的字符串指针，否则返回nullptr。
 * @see OH_UdsPlainText
 * @since 12
 */
const char* OH_UdsPlainText_GetContent(OH_UdsPlainText* pThis);

/**
 * @brief 从纯文本类型{@link OH_UdsPlainText}中获取纯文本摘要信息。
 *
 * @param pThis 表示指向纯文本类型{@link OH_UdsPlainText}实例的指针。
 * @return 输入有效入参时返回纯文本摘要信息的字符串指针，否则返回nullptr。
 * @see OH_UdsPlainText
 * @since 12
 */
const char* OH_UdsPlainText_GetAbstract(OH_UdsPlainText* pThis);

/**
 * @brief 从纯文本类型{@link OH_UdsPlainText}中获取字典类型{@link OH_UdsDetails}实例的指针。
 *
 * @param pThis 表示指向纯文本类型{@link OH_UdsPlainText}实例的指针。
 * @param details 该参数是输出参数，表示指向字典类型{@link OH_UdsDetails}实例的指针，该指针不能为空。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsPlainText OH_UdsDetails Udmf_ErrCode
 * @since 22
 */
int OH_UdsPlainText_GetDetails(OH_UdsPlainText* pThis, OH_UdsDetails* details);

/**
 * @brief 设置纯文本类型{@link OH_UdsPlainText}中的纯文本内容参数。
 *
 * @param pThis 表示指向纯文本类型{@link OH_UdsPlainText}实例的指针。
 * @param content 表示纯文本内容参数。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsPlainText Udmf_ErrCode
 * @since 12
 */
int OH_UdsPlainText_SetContent(OH_UdsPlainText* pThis, const char* content);

/**
 * @brief 设置纯文本类型{@link OH_UdsPlainText}中的纯文本摘要参数。
 *
 * @param pThis 表示指向纯文本类型{@link OH_UdsPlainText}实例的指针。
 * @param abstract 表示纯文本摘要参数。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsPlainText Udmf_ErrCode
 * @since 12
 */
int OH_UdsPlainText_SetAbstract(OH_UdsPlainText* pThis, const char* abstract);

/**
 * @brief 设置纯文本类型{@link OH_UdsPlainText}中的字典类型{@link OH_UdsDetails}参数。
 *
 * @param pThis 表示指向纯文本类型{@link OH_UdsPlainText}实例的指针。
 * @param details 表示指向字典类型{@link OH_UdsDetails}实例的指针，该指针不能为空。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsPlainText OH_UdsDetails Udmf_ErrCode
 * @since 22
 */
int OH_UdsPlainText_SetDetails(OH_UdsPlainText* pThis, const OH_UdsDetails* details);

/**
 * @brief 创建超链接类型{@link OH_UdsHyperlink}指针及实例对象。当不再需要使用指针时，请使用{@link OH_UdsHyperlink_Destroy}销毁实例对象，否则会导致内存泄漏。
 *
 * @return 执行成功则返回一个指向超链接类型{@link OH_UdsHyperlink}实例对象的指针，否则返回nullptr。
 * @see OH_UdsHyperlink
 * @since 12
 */
OH_UdsHyperlink* OH_UdsHyperlink_Create();

/**
 * @brief 销毁超链接类型{@link OH_UdsHyperlink}指针指向的实例对象。
 *
 * @param pThis 表示指向超链接类型{@link OH_UdsHyperlink}实例的指针。
 * @see OH_UdsHyperlink
 * @since 12
 */
void OH_UdsHyperlink_Destroy(OH_UdsHyperlink* pThis);

/**
 * @brief 从超链接类型{@link OH_UdsHyperlink}中获取类型ID。
 *
 * @param pThis 表示指向超链接类型{@link OH_UdsHyperlink}实例的指针。
 * @return 输入有效入参时返回类型ID的字符串指针，否则返回nullptr。
 * @see OH_UdsHyperlink
 * @since 12
 */
const char* OH_UdsHyperlink_GetType(OH_UdsHyperlink* pThis);

/**
 * @brief 从超链接类型{@link OH_UdsHyperlink}中获取URL参数。
 *
 * @param pThis 表示指向超链接类型{@link OH_UdsHyperlink}实例的指针。
 * @return 输入有效入参时返回URL参数的字符串指针，否则返回nullptr。
 * @see OH_UdsHyperlink
 * @since 12
 */
const char* OH_UdsHyperlink_GetUrl(OH_UdsHyperlink* pThis);

/**
 * @brief 从超链接类型{@link OH_UdsHyperlink}中获取描述参数。
 *
 * @param pThis 表示指向超链接类型{@link OH_UdsHyperlink}实例的指针。
 * @return 输入有效入参时返回描述参数的字符串指针，否则返回nullptr。
 * @see OH_UdsHyperlink
 * @since 12
 */
const char* OH_UdsHyperlink_GetDescription(OH_UdsHyperlink* pThis);

/**
 * @brief 从超链接类型{@link OH_UdsHyperlink}中获取字典类型{@link OH_UdsDetails}实例的指针。
 *
 * @param pThis 表示指向超链接类型{@link OH_UdsHyperlink}实例的指针。
 * @param details 该参数是输出参数，表示指向字典类型{@link OH_UdsDetails}实例的指针，该指针不能为空。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsHyperlink OH_UdsDetails Udmf_ErrCode
 * @since 22
 */
int OH_UdsHyperlink_GetDetails(OH_UdsHyperlink* pThis, OH_UdsDetails* details);

/**
 * @brief 设置超链接类型{@link OH_UdsHyperlink}实例中URL参数。
 *
 * @param pThis 表示指向超链接类型{@link OH_UdsHyperlink}实例的指针。
 * @param url 表示URL参数。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsHyperlink Udmf_ErrCode
 * @since 12
 */
int OH_UdsHyperlink_SetUrl(OH_UdsHyperlink* pThis, const char* url);

/**
 * @brief 设置超链接类型{@link OH_UdsHyperlink}实例中描述参数。
 *
 * @param pThis 表示指向超链接类型{@link OH_UdsHyperlink}实例的指针。
 * @param description 表示描述信息。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsHyperlink Udmf_ErrCode
 * @since 12
 */
int OH_UdsHyperlink_SetDescription(OH_UdsHyperlink* pThis, const char* description);

/**
 * @brief 设置超链接类型{@link OH_UdsHyperlink}实例中的字典类型{@link OH_UdsDetails}参数。
 *
 * @param pThis 表示指向超链接类型{@link OH_UdsHyperlink}实例的指针。
 * @param details 表示指向字典类型{@link OH_UdsDetails}实例的指针，该指针不能为空。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @since 22
 * @see OH_UdsHyperlink OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsHyperlink_SetDetails(OH_UdsHyperlink* pThis, const OH_UdsDetails* details);

/**
 * @brief 创建超文本标记语言类型{@link OH_UdsHtml}指针及实例对象。当不再需要使用指针时，请使用{@link OH_UdsHtml_Destroy}销毁实例对象，否则会导致内存泄漏。
 *
 * @return 执行成功则返回一个指向超文本标记语言类型{@link OH_UdsHtml}实例对象的指针，否则返回nullptr。
 * @see OH_UdsHtml
 * @since 12
 */
OH_UdsHtml* OH_UdsHtml_Create();

/**
 * @brief 销毁超文本标记语言类型{@link OH_UdsHtml}指针指向的实例对象。
 *
 * @param pThis 表示指向超文本标记语言类型{@link OH_UdsHtml}实例的指针。
 * @see OH_UdsHtml
 * @since 12
 */
void OH_UdsHtml_Destroy(OH_UdsHtml* pThis);

/**
 * @brief 获取超文本标记语言类型{@link OH_UdsHtml}对象中类型ID。
 *
 * @param pThis 表示指向超文本标记语言类型{@link OH_UdsHtml}实例的指针。
 * @return 输入有效入参时返回类型ID的字符串指针，否则返回nullptr。
 * @see OH_UdsHtml
 * @since 12
 */
const char* OH_UdsHtml_GetType(OH_UdsHtml* pThis);

/**
 * @brief 获取超文本标记语言类型{@link OH_UdsHtml}对象中HTML格式内容参数。
 *
 * @param pThis 表示指向超文本标记语言类型{@link OH_UdsHtml}实例的指针。
 * @return 输入有效入参时返回HTML格式内容的字符串指针，否则返回nullptr。
 * @see OH_UdsHtml
 * @since 12
 */
const char* OH_UdsHtml_GetContent(OH_UdsHtml* pThis);

/**
 * @brief 获取超文本标记语言类型{@link OH_UdsHtml}对象中的纯文本内容参数。
 *
 * @param pThis 表示指向超文本标记语言类型{@link OH_UdsHtml}实例的指针。
 * @return 输入有效入参时返回纯文本内容的字符串指针，否则返回nullptr。
 * @see OH_UdsHtml
 * @since 12
 */
const char* OH_UdsHtml_GetPlainContent(OH_UdsHtml* pThis);

/**
 * @brief 从超文本标记语言类型{@link OH_UdsHtml}对象中获取字典类型{@link OH_UdsDetails}实例的指针。
 *
 * @param pThis 表示指向超文本标记语言类型{@link OH_UdsHtml}实例的指针。
 * @param details 该参数是输出参数，表示指向字典类型{@link OH_UdsDetails}实例的指针，该指针不能为空。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @since 22
 * @see OH_UdsHtml OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsHtml_GetDetails(OH_UdsHtml* pThis, OH_UdsDetails* details);

/**
 * @brief 设置超文本标记语言类型{@link OH_UdsHtml}中的HTML格式内容参数。
 *
 * @param pThis 表示指向超文本标记语言类型{@link OH_UdsHtml}实例的指针。
 * @param content 表示HTML格式内容参数。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsHtml Udmf_ErrCode
 * @since 12
 */
int OH_UdsHtml_SetContent(OH_UdsHtml* pThis, const char* content);

/**
 * @brief 设置超文本标记语言类型{@link OH_UdsHtml}中的纯文本内容参数。
 *
 * @param pThis 表示指向超文本标记语言类型{@link OH_UdsHtml}实例的指针。
 * @param plainContent 表示纯文本内容参数。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsHtml Udmf_ErrCode
 * @since 12
 */
int OH_UdsHtml_SetPlainContent(OH_UdsHtml* pThis, const char* plainContent);

/**
 * @brief 设置超文本标记语言类型{@link OH_UdsHtml}中的字典类型{@link OH_UdsDetails}参数。
 *
 * @param pThis 表示指向超文本标记语言类型{@link OH_UdsHtml}实例的指针。
 * @param details 表示指向字典类型{@link OH_UdsDetails}实例的指针，该指针不能为空。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @since 22
 * @see OH_UdsHtml OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsHtml_SetDetails(OH_UdsHtml* pThis, const OH_UdsDetails* details);

/**
 * @brief 给{@link OH_UdsHtml}设置授权策略。
 *
 * > **说明：**
 * > 此授权策略仅在拖拽场景下生效，其他场景不生效。
 *
 * @param pThis 表示指向{@link OH_UdsHtml}实例的指针。
 * @param authPolicy 表示拖拽场景下的URI授权策略，默认值为READ（仅读授权），仅在img标签等场景下生效。只针对单个record使用，优先级最高。具体策略见{@link Udmf_AuthPermission}。
 * @return 返回执行的状态代码。
 *     <br>返回UDMF_E_OK表示执行成功。
 *     <br>返回UDMF_E_INVALID_PARAM表示传入了无效参数。
 *     <br>具体请参见{@link Udmf_ErrCode}。
 * @since 26.0.0
 * @see OH_UdsHtml Udmf_ErrCode
 */
int OH_UdsHtml_SetAuthPolicy(OH_UdsHtml* pThis, uint32_t authPolicy);

/**
 * @brief 创建桌面图标类型{@link OH_UdsAppItem}指针及实例对象。当不再需要使用指针时，请使用{@link OH_UdsAppItem_Destroy}销毁实例对象，否则会导致内存泄漏。
 *
 * @return 执行成功则返回一个指向桌面图标类型{@link OH_UdsAppItem}实例对象的指针，否则返回nullptr。
 * @see OH_UdsAppItem
 * @since 12
 */
OH_UdsAppItem* OH_UdsAppItem_Create();

/**
 * @brief 销毁桌面图标类型{@link OH_UdsAppItem}指针指向的实例对象。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @see OH_UdsAppItem
 * @since 12
 */
void OH_UdsAppItem_Destroy(OH_UdsAppItem* pThis);

/**
 * @brief 从桌面图标类型{@link OH_UdsAppItem}实例获取类型ID。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @return 输入有效入参时返回类型ID的字符串指针，否则返回nullptr。
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetType(OH_UdsAppItem* pThis);

/**
 * @brief 从桌面图标类型{@link OH_UdsAppItem}实例中获取应用ID。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @return 输入有效入参时返回应用ID的字符串指针，否则返回nullptr。
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetId(OH_UdsAppItem* pThis);

/**
 * @brief 从桌面图标类型{@link OH_UdsAppItem}实例中获取应用名称。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @return 输入有效入参时返回应用名称的字符串指针，否则返回nullptr。
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetName(OH_UdsAppItem* pThis);

/**
 * @brief 从桌面图标类型{@link OH_UdsAppItem}实例中获取图片ID。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @return 输入有效入参时返回图片ID的字符串指针，否则返回nullptr。
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetIconId(OH_UdsAppItem* pThis);

/**
 * @brief 从桌面图标类型{@link OH_UdsAppItem}实例中获取标签ID。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @return 输入有效入参时返回标签ID的字符串指针，否则返回nullptr。
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetLabelId(OH_UdsAppItem* pThis);

/**
 * @brief 从桌面图标类型{@link OH_UdsAppItem}实例中获取bundle名称。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @return 输入有效入参时返回bundle名称的字符串指针，否则返回nullptr。
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetBundleName(OH_UdsAppItem* pThis);

/**
 * @brief 从桌面图标类型{@link OH_UdsAppItem}实例中获取ability名称。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @return 输入有效入参时返回ability名称的字符串指针，否则返回nullptr。
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetAbilityName(OH_UdsAppItem* pThis);

/**
 * @brief 从桌面图标类型{@link OH_UdsAppItem}实例中获取字典类型{@link OH_UdsDetails}实例的指针。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @param details 该参数是输出参数，表示指向字典类型{@link OH_UdsDetails}实例的指针，该指针不能为空。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @since 22
 * @see OH_UdsAppItem OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsAppItem_GetDetails(OH_UdsAppItem* pThis, OH_UdsDetails* details);

/**
 * @brief 设置桌面图标类型{@link OH_UdsAppItem}对象的应用ID。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @param appId 表示应用ID。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsAppItem Udmf_ErrCode
 * @since 12
 */
int OH_UdsAppItem_SetId(OH_UdsAppItem* pThis, const char* appId);

/**
 * @brief 设置桌面图标类型{@link OH_UdsAppItem}对象的应用名称。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @param appName 表示应用名称。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsAppItem Udmf_ErrCode
 * @since 12
 */
int OH_UdsAppItem_SetName(OH_UdsAppItem* pThis, const char* appName);

/**
 * @brief 设置桌面图标类型{@link OH_UdsAppItem}对象的图片ID。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @param appIconId 表示图片ID。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsAppItem Udmf_ErrCode
 * @since 12
 */
int OH_UdsAppItem_SetIconId(OH_UdsAppItem* pThis, const char* appIconId);

/**
 * @brief 设置桌面图标类型{@link OH_UdsAppItem}对象的标签ID。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @param appLabelId 表示标签ID。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsAppItem Udmf_ErrCode
 * @since 12
 */
int OH_UdsAppItem_SetLabelId(OH_UdsAppItem* pThis, const char* appLabelId);

/**
 * @brief 设置桌面图标类型{@link OH_UdsAppItem}对象的bundle名称。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @param bundleName 表示bundle名称。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsAppItem Udmf_ErrCode
 * @since 12
 */
int OH_UdsAppItem_SetBundleName(OH_UdsAppItem* pThis, const char* bundleName);

/**
 * @brief 设置桌面图标类型{@link OH_UdsAppItem}对象的ability名称。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @param abilityName 表示ability名称。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsAppItem Udmf_ErrCode
 * @since 12
 */
int OH_UdsAppItem_SetAbilityName(OH_UdsAppItem* pThis, const char* abilityName);

/**
 * @brief 设置桌面图标类型{@link OH_UdsAppItem}对象的字典类型{@link OH_UdsDetails}参数。
 *
 * @param pThis 表示指向桌面图标类型{@link OH_UdsAppItem}对象的指针。
 * @param details 表示指向字典类型{@link OH_UdsDetails}实例的指针，该指针不能为空。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsAppItem OH_UdsDetails Udmf_ErrCode
 * @since 22
 */
int OH_UdsAppItem_SetDetails(OH_UdsAppItem* pThis, const OH_UdsDetails* details);

/**
 * @brief 创建文件Uri类型{@link OH_UdsFileUri}的实例对象以及指向它的指针。当不再需要使用指针时，请使用{@link OH_UdsFileUri_Destroy}销毁实例对象，否则会导致内存泄漏。
 *
 * @return 执行成功则返回一个指向文件Uri类型{@link OH_UdsFileUri}实例对象的指针，否则返回nullptr。
 * @see OH_UdsFileUri
 * @since 13
 */
OH_UdsFileUri* OH_UdsFileUri_Create();

/**
 * @brief 销毁文件Uri类型{@link OH_UdsFileUri}的实例对象。
 *
 * @param pThis 表示指向文件Uri类型{@link OH_UdsFileUri}实例的指针。
 * @see OH_UdsFileUri
 * @since 13
 */
void OH_UdsFileUri_Destroy(OH_UdsFileUri* pThis);

/**
 * @brief 从文件Uri类型{@link OH_UdsFileUri}实例中获取类型ID。
 *
 * @param pThis 表示指向文件Uri类型{@link OH_UdsFileUri}实例的指针。
 * @return 输入有效入参时返回类型ID的字符串指针，否则返回nullptr。
 * @see OH_UdsFileUri
 * @since 13
 */
const char* OH_UdsFileUri_GetType(OH_UdsFileUri* pThis);

/**
 * @brief 从文件Uri类型{@link OH_UdsFileUri}实例中获取文件Uri。
 *
 * @param pThis 表示指向文件Uri类型{@link OH_UdsFileUri}实例的指针。
 * @return 输入有效入参时返回文件Uri的字符串指针，否则返回nullptr。
 * @see OH_UdsFileUri
 * @since 13
 */
const char* OH_UdsFileUri_GetFileUri(OH_UdsFileUri* pThis);

/**
 * @brief 从文件Uri类型{@link OH_UdsFileUri}实例中获取文件类型。
 *
 * @param pThis 表示指向文件Uri类型{@link OH_UdsFileUri}实例的指针。
 * @return 输入有效入参时返回文件类型的字符串指针，否则返回nullptr。
 * @see OH_UdsFileUri
 * @since 13
 */
const char* OH_UdsFileUri_GetFileType(OH_UdsFileUri* pThis);

/**
 * @brief 从文件Uri类型{@link OH_UdsFileUri}实例中获取字典类型{@link OH_UdsDetails}实例的指针。
 *
 * @param pThis 表示指向文件Uri类型{@link OH_UdsFileUri}实例的指针。
 * @param details 该参数是输出参数，表示指向字典类型{@link OH_UdsDetails}实例的指针，该指针不能为空。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @since 22
 * @see OH_UdsFileUri OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsFileUri_GetDetails(OH_UdsFileUri* pThis, OH_UdsDetails* details);

/**
 * @brief 设置文件Uri类型{@link OH_UdsFileUri}对象的Uri信息。
 *
 * @param pThis 表示指向文件Uri类型{@link OH_UdsFileUri}实例的指针。
 * @param fileUri 表示文件Uri。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsFileUri Udmf_ErrCode
 * @since 13
 */
int OH_UdsFileUri_SetFileUri(OH_UdsFileUri* pThis, const char* fileUri);

/**
 * @brief 设置文件Uri类型{@link OH_UdsFileUri}对象的文件类型。
 *
 * @param pThis 表示指向文件Uri类型{@link OH_UdsFileUri}实例的指针。
 * @param fileType 表示文件类型。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsFileUri Udmf_ErrCode
 * @since 13
 */
int OH_UdsFileUri_SetFileType(OH_UdsFileUri* pThis, const char* fileType);

/**
 * @brief 设置文件Uri类型{@link OH_UdsFileUri}对象的字典类型{@link OH_UdsDetails}参数。
 *
 * @param pThis 表示指向文件Uri类型{@link OH_UdsFileUri}实例的指针。
 * @param details 表示指向字典类型{@link OH_UdsDetails}实例的指针，该指针不能为空。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsFileUri OH_UdsDetails Udmf_ErrCode
 * @since 22
 */
int OH_UdsFileUri_SetDetails(OH_UdsFileUri* pThis, const OH_UdsDetails* details);

/**
 * @brief 给{@link OH_UdsFileUri}设置授权策略。
 *
 * > **说明：**
 * > 此授权策略仅在拖拽场景下生效，其他场景不生效。
 *
 * @param pThis 表示指向{@link OH_UdsFileUri}实例的指针。
 * @param authPolicy 表示拖拽场景下的URI授权策略，默认值为READ+WRITE+PERSIST（读+写+持久化授权），只针对单个record使用，优先级最高。具体策略见
 * {@link Udmf_AuthPermission}。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsFileUri Udmf_ErrCode
 * @since 26.0.0
 */
int OH_UdsFileUri_SetAuthPolicy(OH_UdsFileUri* pThis, uint32_t authPolicy);

/**
 * @brief 创建必须显式设置文件大小的虚拟文件节点。
 *
 * 将节点添加到目录或创建虚拟文件信息前，必须调用{@link OH_UDMF_SetVirtualFileSize}设置文件大小。
 * 大小为零表示空文件，未设置大小时不会通过其他方式推断文件大小。
 *
 * @param name [in] 文件名，不得包含路径分隔符。
 * @param id [in] 传递给虚拟文件回调的文件标识。
 * @param modifyTime [in] 文件修改时间。
 * @return 成功时返回创建的虚拟节点；参数无效或内存分配失败时返回nullptr。
 * @release uds/OH_UDMF_DestroyVirtualItem {return}
 * @since 26.1.0
 */
OH_UDMF_VirtualItem* OH_UDMF_CreateVirtualFileItem(const char* name, const char* id, int64_t modifyTime);

/**
 * @brief 创建虚拟目录节点。
 *
 * @param name [in] 目录名，不得包含路径分隔符。
 * @param modifyTime [in] 目录修改时间。
 * @return 成功时返回创建的虚拟节点；参数无效或内存分配失败时返回nullptr。
 * @release uds/OH_UDMF_DestroyVirtualItem {return}
 * @since 26.1.0
 */
OH_UDMF_VirtualItem* OH_UDMF_CreateVirtualDirectoryItem(const char* name, int64_t modifyTime);

/**
 * @brief 销毁虚拟节点。
 *
 * @param item [in] 待销毁的虚拟节点。
 * @since 26.1.0
 */
void OH_UDMF_DestroyVirtualItem(OH_UDMF_VirtualItem* item);

/**
 * @brief 设置虚拟文件节点的文件大小。
 *
 * @param item [in,out] 虚拟文件节点。
 * @param size [in] 文件大小，单位为字节。
 * @return 返回执行状态码。具体请参阅{@link Udmf_ErrCode}。
 *         <ul>
 *         <li>{@link UDMF_E_OK} 表示设置成功。</li>
 *         <li>{@link UDMF_E_INVALID_PARAM} 表示<code>item</code>无效、不是文件节点或<code>size</code>为负数。</li>
 *         </ul>
 * @see Udmf_ErrCode
 * @since 26.1.0
 */
int OH_UDMF_SetVirtualFileSize(OH_UDMF_VirtualItem* item, int64_t size);

/**
 * @brief 在构建过程中清除虚拟文件节点必须设置的文件大小。
 *
 * 清除后，必须再次通过{@link OH_UDMF_SetVirtualFileSize}设置非负文件大小，才能将节点添加到目录或用于创建
 * 虚拟文件信息；stat回调不能替代此步骤。
 *
 * @param item [in,out] 虚拟文件节点。
 * @return 返回执行状态码。具体请参阅{@link Udmf_ErrCode}。
 *         <ul>
 *         <li>{@link UDMF_E_OK} 表示清除成功。</li>
 *         <li>{@link UDMF_E_INVALID_PARAM} 表示<code>item</code>无效或不是文件节点。</li>
 *         </ul>
 * @see Udmf_ErrCode
 * @since 26.1.0
 */
int OH_UDMF_ClearVirtualFileSize(OH_UDMF_VirtualItem* item);

/**
 * @brief 向虚拟目录添加子节点。
 *
 * 此接口会复制<code>child</code>，调用方仍持有原节点的所有权。
 *
 * @param directory [in,out] 虚拟目录节点。
 * @param child [in] 待添加的子节点。
 * @return 返回执行状态码。具体请参阅{@link Udmf_ErrCode}。
 *         <ul>
 *         <li>{@link UDMF_E_OK} 表示添加成功。</li>
 *         <li>{@link UDMF_E_INVALID_PARAM} 表示节点无效、<code>directory</code>不是目录，或结果违反虚拟文件树约束。</li>
 *         </ul>
 * @see Udmf_ErrCode
 * @since 26.1.0
 */
int OH_UDMF_AddVirtualItemChild(OH_UDMF_VirtualItem* directory, const OH_UDMF_VirtualItem* child);

/**
 * @brief 创建虚拟文件信息。
 *
 * 此接口会复制节点树和回调表。<code>context</code>非nullptr时必须提供<code>finalize</code>。
 * 接口执行成功后，UDMF持有该上下文，直到最后一个引用释放。
 *
 * @param itemInfo [in] 虚拟根节点，树中的每个文件都必须显式设置非负文件大小。
 * @param callbacks [in] 虚拟文件回调。
 * @param context [in] 传递给各回调的用户上下文。
 * @param finalize [in] 用于释放<code>context</code>的回调。
 * @return 成功时返回创建的虚拟文件信息；节点或回调无效、内存分配失败时返回nullptr。
 * @release uds/OH_UDMF_DestroyVirtualFileInfo {return}
 * @since 26.1.0
 */
OH_UDMF_VirtualFileInfo* OH_UDMF_CreateVirtualFileInfo(const OH_UDMF_VirtualItem* itemInfo,
    const OH_UDMF_VirtualFileCallbacks* callbacks, void* context, OH_UDMF_VirtualFileFinalize finalize);

/**
 * @brief 销毁虚拟文件信息。
 *
 * 虚拟文件信息已附加到文件Uri或统一数据记录时，回调状态会保持有效，直到相关引用全部释放。
 *
 * @param info [in] 待销毁的虚拟文件信息。
 * @since 26.1.0
 */
void OH_UDMF_DestroyVirtualFileInfo(OH_UDMF_VirtualFileInfo* info);

/**
 * @brief 为文件Uri附加虚拟文件信息。
 *
 * @param fileUri [in,out] 待更新的文件Uri实例。
 * @param info [in] 待附加的虚拟文件信息。
 * @return 返回执行状态码。具体请参阅{@link Udmf_ErrCode}。
 *         <ul>
 *         <li>{@link UDMF_E_OK} 表示附加成功。</li>
 *         <li>{@link UDMF_E_INVALID_PARAM} 表示<code>fileUri</code>或<code>info</code>无效。</li>
 *         </ul>
 * @see Udmf_ErrCode
 * @since 26.1.0
 */
int OH_UDMF_SetFileUriVirtualEntry(OH_UdsFileUri* fileUri, const OH_UDMF_VirtualFileInfo* info);

/**
 * @brief 从文件Uri移除虚拟文件信息。
 *
 * @param fileUri [in,out] 待更新的文件Uri实例。
 * @return 返回执行状态码。具体请参阅{@link Udmf_ErrCode}。
 *         <ul>
 *         <li>{@link UDMF_E_OK} 表示移除成功。</li>
 *         <li>{@link UDMF_E_INVALID_PARAM} 表示<code>fileUri</code>无效。</li>
 *         </ul>
 * @see Udmf_ErrCode
 * @since 26.1.0
 */
int OH_UDMF_ClearFileUriVirtualEntry(OH_UdsFileUri* fileUri);

/**
 * @brief 创建像素图片类型{@link OH_UdsPixelMap}的实例对象以及指向它的指针。当不再需要使用指针时，请使用{@link OH_UdsPixelMap_Destroy}销毁实例对象，否则会导致内存泄漏。
 *
 * @return 执行成功则返回一个指向像素图片类型{@link OH_UdsPixelMap}实例对象的指针，否则返回nullptr。
 * @see OH_UdsPixelMap
 * @since 13
 */
OH_UdsPixelMap* OH_UdsPixelMap_Create();

/**
 * @brief 销毁像素图片类型{@link OH_UdsPixelMap}的实例对象。
 *
 * @param pThis 表示指向像素图片类型{@link OH_UdsPixelMap}实例的指针。
 * @see OH_UdsPixelMap
 * @since 13
 */
void OH_UdsPixelMap_Destroy(OH_UdsPixelMap* pThis);

/**
 * @brief 从像素图片类型{@link OH_UdsPixelMap}实例中获取类型ID。
 *
 * @param pThis 表示指向像素图片类型{@link OH_UdsPixelMap}实例的指针。
 * @return 输入有效入参时返回类型ID的字符串指针，否则返回nullptr。
 * @see OH_UdsPixelMap
 * @since 13
 */
const char* OH_UdsPixelMap_GetType(OH_UdsPixelMap* pThis);

/**
 * @brief 从像素图片类型{@link OH_UdsPixelMap}实例中获取像素图片{@link OH_PixelmapNative}实例的指针。
 *
 * @param pThis 表示指向像素图片类型{@link OH_UdsPixelMap}实例的指针。
 * @param pixelmapNative 该参数是输出参数，表示指向像素图片{@link OH_PixelmapNative}实例的指针。
 * @see OH_UdsPixelMap
 * @since 13
 */
void OH_UdsPixelMap_GetPixelMap(OH_UdsPixelMap* pThis, OH_PixelmapNative* pixelmapNative);

/**
 * @brief 从像素图片类型{@link OH_UdsPixelMap}实例中获取字典类型{@link OH_UdsDetails}实例的指针。
 *
 * @param pThis 表示指向像素图片类型{@link OH_UdsPixelMap}实例的指针。
 * @param details 该参数是输出参数，表示指向字典类型{@link OH_UdsDetails}实例的指针，该指针不能为空。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @since 22
 * @see OH_UdsPixelMap OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsPixelMap_GetDetails(OH_UdsPixelMap* pThis, OH_UdsDetails* details);

/**
 * @brief 设置像素图片类型{@link OH_UdsPixelMap}对象的像素图片内容。
 *
 * @param pThis 表示指向像素图片类型{@link OH_UdsPixelMap}实例的指针。
 * @param pixelmapNative 表示指向像素图片{@link OH_PixelmapNative}实例的指针。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsPixelMap Udmf_ErrCode
 * @since 13
 */
int OH_UdsPixelMap_SetPixelMap(OH_UdsPixelMap* pThis, OH_PixelmapNative* pixelmapNative);

/**
 * @brief 设置像素图片类型{@link OH_UdsPixelMap}对象的字典类型{@link OH_UdsDetails}参数。
 *
 * @param pThis 表示指向像素图片类型{@link OH_UdsPixelMap}实例的指针。
 * @param details 表示指向字典类型{@link OH_UdsDetails}实例的指针，该指针不能为空。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @since 22
 * @see OH_UdsPixelMap OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsPixelMap_SetDetails(OH_UdsPixelMap* pThis, const OH_UdsDetails* details);

/**
 * @brief 创建ArrayBuffer类型{@link OH_UdsArrayBuffer}的实例对象以及指向它的指针。当不再需要使用指针时，请使用{@link OH_UdsArrayBuffer_Destroy}销毁实例对象，
 * 否则会导致内存泄漏。
 *
 * @return 执行成功则返回一个指向ArrayBuffer类型{@link OH_UdsArrayBuffer}实例对象的指针，否则返回nullptr。
 * @see OH_UdsArrayBuffer
 * @since 13
 */
OH_UdsArrayBuffer* OH_UdsArrayBuffer_Create();

/**
 * @brief 销毁ArrayBuffer类型{@link OH_UdsArrayBuffer}的实例对象。
 *
 * @param buffer 表示指向ArrayBuffer类型{@link OH_UdsArrayBuffer}实例的指针。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsArrayBuffer Udmf_ErrCode
 * @since 13
 */
int OH_UdsArrayBuffer_Destroy(OH_UdsArrayBuffer* buffer);

/**
 * @brief 设置ArrayBuffer类型{@link OH_UdsArrayBuffer}对象的数据内容。
 *
 * @param buffer 表示指向ArrayBuffer类型{@link OH_UdsArrayBuffer}实例的指针。
 * @param data 表示用户自定义的ArrayBuffer数据。
 * @param len 表示用户自定义的ArrayBuffer数据的大小。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsArrayBuffer Udmf_ErrCode
 * @since 13
 */
int OH_UdsArrayBuffer_SetData(OH_UdsArrayBuffer* buffer, unsigned char* data, unsigned int len);

/**
 * @brief 从ArrayBuffer类型{@link OH_UdsArrayBuffer}实例中获取用户自定义的ArrayBuffer数据内容。
 *
 * @param buffer 表示指向ArrayBuffer类型{@link OH_UdsArrayBuffer}实例的指针。
 * @param data 该参数是输出参数，表示用户自定义的ArrayBuffer数据。
 * @param len 该参数是输出参数，表示用户自定义的ArrayBuffer数据的大小。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsArrayBuffer Udmf_ErrCode
 * @since 13
 */
int OH_UdsArrayBuffer_GetData(OH_UdsArrayBuffer* buffer, unsigned char** data, unsigned int* len);

/**
 * @brief 创建内容卡片类型{@link OH_UdsContentForm}指针及实例对象。当不再需要使用指针时，请使用{@link OH_UdsContentForm_Destroy}销毁实例对象，否则会导致内存泄漏。
 *
 * @return 执行成功则返回一个指向内容卡片类型{@link OH_UdsContentForm}实例对象的指针，否则返回nullptr。
 * @see OH_UdsContentForm
 * @since 14
 */
OH_UdsContentForm* OH_UdsContentForm_Create();

/**
 * @brief 销毁内容卡片类型数据{@link OH_UdsContentForm}指针指向的实例对象。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @see OH_UdsContentForm
 * @since 14
 */
void OH_UdsContentForm_Destroy(OH_UdsContentForm* pThis);

/**
 * @brief 从内容卡片类型{@link OH_UdsContentForm}中获取类型ID。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @return 输入有效入参时返回类型ID的字符串指针，否则返回nullptr。
 * @see OH_UdsContentForm
 * @since 14
 */
const char* OH_UdsContentForm_GetType(OH_UdsContentForm* pThis);

/**
 * @brief 从内容卡片类型{@link OH_UdsContentForm}中获取图片数据。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @param thumbData 该参数是输出参数，表示内容卡片中的图片二进制数据。
 * @param len 该参数是输出参数，表示内容卡片中的图片二进制数据的大小。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 *     <br>若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_GetThumbData(OH_UdsContentForm* pThis, unsigned char** thumbData, unsigned int* len);

/**
 * @brief 从内容卡片类型{@link OH_UdsContentForm}中获取描述信息。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @return 输入有效入参时返回描述信息的字符串指针，否则返回nullptr。
 * @see OH_UdsContentForm
 * @since 14
 */
const char* OH_UdsContentForm_GetDescription(OH_UdsContentForm* pThis);

/**
 * @brief 从内容卡片类型{@link OH_UdsContentForm}中获取标题信息。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @return 输入有效入参时返回标题信息的字符串指针，否则返回nullptr。
 * @see OH_UdsContentForm
 * @since 14
 */
const char* OH_UdsContentForm_GetTitle(OH_UdsContentForm* pThis);

/**
 * @brief 从内容卡片类型{@link OH_UdsContentForm}中获取应用图标数据。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @param appIcon 该参数是输出参数，表示内容卡片中的应用图标二进制数据。
 * @param len 该参数是输出参数，表示内容卡片中的应用图标二进制数据的大小。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 *     <br>若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_GetAppIcon(OH_UdsContentForm* pThis, unsigned char** appIcon, unsigned int* len);

/**
 * @brief 从内容卡片类型{@link OH_UdsContentForm}中获取应用名称信息。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @return 输入有效入参时返回应用名称信息的字符串指针，否则返回nullptr。
 * @see OH_UdsContentForm
 * @since 14
 */
const char* OH_UdsContentForm_GetAppName(OH_UdsContentForm* pThis);

/**
 * @brief 从内容卡片类型{@link OH_UdsContentForm}中获取超链接信息。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @return 输入有效入参时返回超链接的字符串指针，否则返回nullptr。
 * @see OH_UdsContentForm
 * @since 14
 */
const char* OH_UdsContentForm_GetLinkUri(OH_UdsContentForm* pThis);

/**
 * @brief 设置内容卡片类型{@link OH_UdsContentForm}中的图片数据。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @param thumbData 表示内容卡片中的图片二进制数据。
 * @param len 表示内容卡片中的图片二进制数据的大小。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_SetThumbData(OH_UdsContentForm* pThis, const unsigned char* thumbData, unsigned int len);

/**
 * @brief 设置内容卡片类型{@link OH_UdsContentForm}中的描述信息。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @param description 表示描述信息。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_SetDescription(OH_UdsContentForm* pThis, const char* description);

/**
 * @brief 设置内容卡片类型{@link OH_UdsContentForm}中的标题信息。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @param title 表示标题信息。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_SetTitle(OH_UdsContentForm* pThis, const char* title);

/**
 * @brief 设置内容卡片类型{@link OH_UdsContentForm}中的应用图标数据。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @param appIcon 表示内容卡片中的应用图标二进制数据。
 * @param len 表示内容卡片中的应用图标二进制数据的大小。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_SetAppIcon(OH_UdsContentForm* pThis, const unsigned char* appIcon, unsigned int len);

/**
 * @brief 设置内容卡片类型{@link OH_UdsContentForm}中的应用名称数据。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @param appName 表示内容卡片中的应用名称。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_SetAppName(OH_UdsContentForm* pThis, const char* appName);

/**
 * @brief 设置内容卡片类型{@link OH_UdsContentForm}中的超链接数据。
 *
 * @param pThis 表示指向{@link OH_UdsContentForm}实例的指针。
 * @param linkUri 表示内容卡片中的超链接。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_SetLinkUri(OH_UdsContentForm* pThis, const char* linkUri);

/**
 * @brief 创建字典类型{@link OH_UdsDetails}指针及实例对象。
 * <br>当不再需要使用指针时，请使用{@linkOH_UdsDetails_Destroy}销毁实例对象，否则会导致内存泄漏。
 *
 * @return 执行成功则返回一个指向字典类型{@link OH_UdsDetails}实例对象的指针，否则返回nullptr。
 * @since 22
 * @see OH_UdsDetails
 */
OH_UdsDetails* OH_UdsDetails_Create();

/**
 * @brief 销毁字典类型{@link OH_UdsDetails}指针指向的实例对象。
 *
 * @param pThis 表示指向字典类型{@link OH_UdsDetails}实例的指针。
 * @since 22
 * @see OH_UdsDetails
 */
void OH_UdsDetails_Destroy(OH_UdsDetails* pThis);

/**
 * @brief 检查字典类型{@link OH_UdsDetails}中是否存在指定键。
 *
 * @param pThis 表示指向字典类型{@link OH_UdsDetails}实例的指针。
 * @param key 表示字典类型中键值对的键。
 * @return 返回查找结果的状态。返回false表示不存在指定键，返回true表示存在指定键。
 * @see OH_UdsDetails
 * @since 22
 */
bool OH_UdsDetails_HasKey(const OH_UdsDetails* pThis, const char* key);

/**
 * @brief 删除字典类型{@link OH_UdsDetails}中指定键值对。
 *
 * @param pThis 表示指向字典类型{@link OH_UdsDetails}实例的指针。
 * @param key 表示字典类型中键值对的键。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @since 22
 * @see OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsDetails_Remove(OH_UdsDetails* pThis, const char* key);

/**
 * @brief 清除字典类型{@link OH_UdsDetails}中所有数据。
 *
 * @param pThis 表示指向字典类型{@link OH_UdsDetails}实例的指针。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @since 22
 * @see OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsDetails_Clear(OH_UdsDetails* pThis);

/**
 * @brief 向字典类型{@link OH_UdsDetails}中添加键值对数据。
 *
 * @param pThis 表示指向字典类型{@link OH_UdsDetails}实例的指针。
 * @param key 表示字典类型中键值对的键。
 * @param value [in] 表示字典类型中键值对的值。
 * @return 返回执行的状态代码。
 *     <br>若返回UDMF_E_OK，表示执行成功。
 *     <br>若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @since 22
 * @see OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsDetails_SetValue(OH_UdsDetails* pThis, const char* key, const char* value);

/**
 * @brief 获取字典类型{@link OH_UdsDetails}中指定的键对应的值。
 *
 * @param pThis 表示指向字典类型{@link OH_UdsDetails}实例的指针。
 * @param key 表示字典类型中键值对的键。
 * @return 当入参有效时返回指向字典类型中值的指针，否则返回nullptr。
 * @since 22
 * @see OH_UdsDetails
 */
const char* OH_UdsDetails_GetValue(const OH_UdsDetails* pThis, const char* key);

/**
 * @brief 获取字典类型{@link OH_UdsDetails}中所有键的结果集。
 *
 * @param pThis 表示指向字典类型{@link OH_UdsDetails}实例的指针。
 * @param count 该参数是输出参数，表示结果集的长度。
 * @return 执行成功时返回字典类型中键的结果集，否则返回nullptr。
 * <br>当使用{@link OH_UdsDetails_Destroy}销毁字典类型{@link OH_UdsDetails}指针指向的实例对象，该返回值也会被释放。
 * @since 22
 * @see OH_UdsDetails
 */
char** OH_UdsDetails_GetAllKeys(OH_UdsDetails* pThis, unsigned int* count);

#ifdef __cplusplus
};
#endif

/** @} */
#endif
