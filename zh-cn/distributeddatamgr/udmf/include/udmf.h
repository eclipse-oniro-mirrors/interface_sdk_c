/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup UDMF
 * @{
 *
 * @brief The Unified Data Management Framework(UDMF) aims to define various standards
 * for data across applications, devices, and platforms, providing a unified OpenHarmony
 * data language and standardized data access and reading paths.
 *
 * @since 12
 */
/**
 * @file udmf.h
 *
 * @brief 提供访问统一数据管理框架数据的接口、数据结构、枚举类型。当参数类型为char*时，字符串必须以空字符（'\0'）结尾。
 * 
 * @kit ArkData
 * @library libudmf.so
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */

#ifndef UDMF_H
#define UDMF_H

#include <inttypes.h>
#include <stdbool.h>
#include "uds.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The key minimum memory space size of Unified Data.
 *
 * @since 12
 */
#define UDMF_KEY_BUFFER_LEN (512)

/**
 * @brief 描述UDMF数据通路枚举类型。
 * 
 * @since 12
 */
typedef enum Udmf_Intention {
    /**
     * @brief 拖拽数据通路。
     * 
     */
    UDMF_INTENTION_DRAG,
    /**
     * @brief 剪贴板数据通路。
     * 
     */
    UDMF_INTENTION_PASTEBOARD,
    /**
     * @brief 公共数据通路。
     * 
     * @since 20
     */
    UDMF_INTENTION_DATA_HUB,
    /**
     * @brief 系统分享数据通路。
     * 
     * @since 20
     */
    UDMF_INTENTION_SYSTEM_SHARE,
    /**
     * @brief Picker数据通路。
     * 
     * @since 20
     */
    UDMF_INTENTION_PICKER,
    /**
     * @brief 菜单数据通路。
     * 
     * @since 20
     */
    UDMF_INTENTION_MENU,
} Udmf_Intention;

/**
 * @brief UDMF支持的设备内使用范围类型枚举。
 * 
 * @since 12
 */
typedef enum Udmf_ShareOption {
    /**
     * @brief 表示不合法的使用范围类型。
     * 
     */
    SHARE_OPTIONS_INVALID,
    /**
     * @brief 表示允许在本设备同应用内使用。
     * 
     */
    SHARE_OPTIONS_IN_APP,
    /**
     * @brief 表示允许在本设备内跨应用使用。
     * 
     */
    SHARE_OPTIONS_CROSS_APP
} Udmf_ShareOption;

/**
 * @brief 定义文件拷贝冲突时的选项。
 * 
 * @since 15
 */
typedef enum Udmf_FileConflictOptions {
    /**
     * @brief 目标路径存在同文件名时覆盖。若不配置策略，默认使用该策略。
     * 
     */
    UDMF_OVERWRITE = 0,
    /**
     * @brief 目标路径存在同文件名时跳过。
     * 
     */
    UDMF_SKIP = 1,
} Udmf_FileConflictOptions;

/**
 * @brief 定义进度条指示选项，可选择是否采用系统默认进度显示。
 * 
 * @since 15
*/
typedef enum Udmf_ProgressIndicator {
    /**
     * @brief 不采用系统默认进度显示。
     * 
    */
    UDMF_NONE = 0,
    /**
     * @brief 采用系统默认进度显示，500ms内获取数据完成将不会拉起默认进度条。
     * 
    */
    UDMF_DEFAULT = 1
} Udmf_ProgressIndicator;

/**
 * @brief 定义数据的可见性等级。
 * 
 * @since 20
 */
typedef enum Udmf_Visibility {
    /**
     * @brief 可见性等级，所有应用可见。
     * 
     */
    UDMF_ALL,

    /**
     * @brief 可见性等级，仅数据提供者可见。
     * 
     */
    UDMF_OWN_PROCESS
} Udmf_Visibility;

/**
 * @brief 定义统一数据对象数据结构。
 * 
 * @since 12
 */
typedef struct OH_UdmfData OH_UdmfData;

/**
 * @brief 定义统一数据对象中记录数据的数据结构，称为数据记录。
 * 
 * @since 12
 */
typedef struct OH_UdmfRecord OH_UdmfRecord;

/**
 * @brief 定义统一数据对象中的数据提供者。
 * 
 * @since 13
 */
typedef struct OH_UdmfRecordProvider OH_UdmfRecordProvider;

/**
 * @brief 定义统一数据对象中数据记录的属性结构。
 * 
 * @since 12
 */
typedef struct OH_UdmfProperty OH_UdmfProperty;

/**
 * @brief 定义进度信息的数据结构。
 * 
 * @since 15
*/
typedef struct OH_Udmf_ProgressInfo OH_Udmf_ProgressInfo;

/**
 * @brief 定义异步获取UDMF数据的请求参数。
 * 
 * @since 15
*/
typedef struct OH_UdmfGetDataParams OH_UdmfGetDataParams;

/**
 * @brief 定义获取进度信息和数据的监听回调函数。
 * 使用时需要判断数据是否返回空指针。只有当进度达到100%时，才会返回数据。
 * 
 * @param progressInfo 进度信息，作为出参使用。
 * @param data 返回的统一数据对象，作为出参使用。
 * @since 15
*/
typedef void (*OH_Udmf_DataProgressListener)(OH_Udmf_ProgressInfo* progressInfo, OH_UdmfData* data);

/**
 * @brief 数据操作选项，定义数据操作的可选参数。
 * 
 * @since 20
 */
typedef struct OH_UdmfOptions OH_UdmfOptions;

/**
 * @brief 表示数据加载参数结构体。
 * 
 * @since 20
 */
typedef struct OH_UdmfDataLoadParams OH_UdmfDataLoadParams;

/**
 * @brief 表示数据加载信息结构体。
 * 
 * @since 20
 */
typedef struct OH_UdmfDataLoadInfo OH_UdmfDataLoadInfo;

/**
 * @brief 表示用于加载数据的回调函数。
 * 
 * @param acceptableInfo 表示接收端可接收的数据类型和数量信息。
 * @return 返回待加载的数据。
 * @since 20
 */
typedef OH_UdmfData* (*OH_Udmf_DataLoadHandler)(OH_UdmfDataLoadInfo* acceptableInfo);

/**
 * @brief 创建统一数据对象{@link OH_UdmfData}指针及实例对象。当不再需要使用指针时，请使用{@link OH_UdmfData_Destroy}销毁实例对象，否则会导致内存泄漏。
 * 
 * @return 执行成功则返回一个指向统一数据对象{@link OH_UdmfData}实例对象的指针，否则返回nullptr。
 * @see OH_UdmfData.
 * @since 12
 */
OH_UdmfData* OH_UdmfData_Create();

/**
 * @brief 销毁统一数据对象{@link OH_UdmfData}指针指向的实例对象。
 * 
 * @param pThis 表示指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @see OH_UdmfData.
 * @since 12
 */
void OH_UdmfData_Destroy(OH_UdmfData* pThis);

/**
 * @brief 添加一个数据记录{@link OH_UdmfRecord}到统一数据对象{@link OH_UdmfData}中。
 * 
 * @param pThis 表示指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @param record 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfData Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfData_AddRecord(OH_UdmfData* pThis, OH_UdmfRecord* record);

/**
 * @brief 检查统一数据对象{@link OH_UdmfData}中是否存在指定类型。
 * 
 * @param pThis 表示指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @param type 表示指定类型的字符串指针。
 * @return 返回查找类型的状态。返回false表示不存在指定类型，返回true表示存在指定类型。
 * @see OH_UdmfData.
 * @since 12
 */
bool OH_UdmfData_HasType(OH_UdmfData* pThis, const char* type);

/**
 * @brief 获取统一数据对象{@link OH_UdmfData}中包含的所有类型结果集。
 * 
 * @param pThis 表示指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @param count 该参数是输出参数，结果集中的类型数量会写入该变量。
 * @return 执行成功时返回统一数据对象的类型结果集，否则返回nullptr。
 * @see OH_UdmfData.
 * @since 12
 */
char** OH_UdmfData_GetTypes(OH_UdmfData* pThis, unsigned int* count);

/**
 * @brief 获取统一数据对象{@link OH_UdmfData}中包含的所有记录结果集。
 * 
 * @param pThis 表示指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @param count 该参数是输出参数，结果集中的记录数量会写入该变量。
 * @return 执行成功时返回统一数据记录{@link OH_UdmfRecord}结果集，否则返回nullptr。
 * @see OH_UdmfData OH_UdmfRecord.
 * @since 12
 */
OH_UdmfRecord** OH_UdmfData_GetRecords(OH_UdmfData* pThis, unsigned int* count);

/**
 * @brief 定义用于释放上下文的回调函数，统一数据提供者对象销毁时触发。
 * 
 * @param context 要释放的上下文指针。
 * @since 13
 */
typedef void (*UdmfData_Finalize)(void* context);

/**
 * @brief 创建一个统一数据提供者{@link OH_UdmfRecordProvider}指针及实例对象。当不再需要使用指针时，请使用{@link OH_UdmfRecordProvider_Destroy}销毁实例对象，
 * 否则会导致内存泄漏。
 * 
 * @return 执行成功时返回一个指向统一数据提供者{@link OH_UdmfRecordProvider}实例对象的指针，否则返回nullptr。
 * @see OH_UdmfRecordProvider.
 * @since 13
 */
OH_UdmfRecordProvider* OH_UdmfRecordProvider_Create();

/**
 * @brief 销毁统一数据提供者{@link OH_UdmfRecordProvider}指针指向的实例对象。
 * 
 * @param provider 表示指向统一数据提供者对象{@link OH_UdmfRecordProvider}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecordProvider Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfRecordProvider_Destroy(OH_UdmfRecordProvider* provider);

/**
 * @brief 定义用于按类型获取数据的回调函数。当从OH_UdmfRecord中获取数据时，会触发此回调函数，得到的数据就是这个回调函数返回的数据。
 * 
 * @param context 用{@link OH_UdmfRecordProvider_SetData}设置的上下文指针。
 * @param type 要获取的数据类型。详细类型信息见{@link udmf_meta.h}。
 * @return 需要返回一个标准化数据。
 * @since 13
 */
typedef void* (*OH_UdmfRecordProvider_GetData)(void* context, const char* type);

/**
 * @brief 设置统一数据提供者的数据提供回调函数。
 * 
 * @param provider 指向统一数据提供者{@link OH_UdmfRecordProvider}实例对象的指针。
 * @param context 上下文指针，将作为第一个参数传入{@link OH_UdmfRecordProvider_GetData}。
 * @param callback 获取数据的回调函数。详见：{@link OH_UdmfRecordProvider_GetData}。
 * @param finalize 可选的回调函数，用于统一数据提供者销毁时释放上下文数据。若传入nullptr则不执行释放操作，开发者需要自行管理上下文数据的生命周期。详见：{@link UdmfData_Finalize}。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecordProvider OH_UdmfRecordProvider_GetData UdmfData_Finalize Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfRecordProvider_SetData(OH_UdmfRecordProvider* provider, void* context,
    const OH_UdmfRecordProvider_GetData callback, const UdmfData_Finalize finalize);

/**
 * @brief 创建统一数据记录{@link OH_UdmfRecord}指针及实例对象。当不再需要使用指针时，请使用{@link OH_UdmfRecord_Destroy}销毁实例对象，否则会导致内存泄漏。
 * 
 * @return 执行成功则返回一个指向统一数据记录{@link OH_UdmfRecord}实例对象的指针，否则返回nullptr。
 * @see OH_UdmfRecord.
 * @since 12
 */
OH_UdmfRecord* OH_UdmfRecord_Create();

/**
 * @brief 销毁统一数据记录{@link OH_UdmfRecord}指针指向的实例对象。
 * 
 * @param pThis 表示指向统一数据对象{@link OH_UdmfRecord}实例的指针。
 * @see OH_UdmfRecord.
 * @since 12
 */
void OH_UdmfRecord_Destroy(OH_UdmfRecord* pThis);

/**
 * @brief 添加用户自定义的通用数据至统一数据记录{@link OH_UdmfRecord}中。对于已定义UDS的类型（比如PlainText、Link、Pixelmap等）不可使用该接口。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param typeId 表示数据类型标识，为和系统定义的类型进行区分，建议以'ApplicationDefined'开头。
 * @param entry 表示用户自定义数据。
 * @param count 表示用户自定义数据的大小。数据大小不超过4KB，否则返回错误码UDMF_E_INVALID_PARAM。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_AddGeneralEntry(OH_UdmfRecord* pThis, const char* typeId, unsigned char* entry, unsigned int count);

/**
 * @brief 增加纯文本类型{@link OH_UdsPlainText}数据至统一数据记录{@link OH_UdmfRecord}中。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param plainText 表示指向纯文本类型{@link OH_UdsPlainText}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsPlainText Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_AddPlainText(OH_UdmfRecord* pThis, OH_UdsPlainText* plainText);

/**
 * @brief 增加超链接类型{@link OH_UdsHyperlink}数据至统一数据记录{@link OH_UdmfRecord}中。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param hyperlink 表示指向超链接类型{@link OH_UdsHyperlink}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsHyperlink Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_AddHyperlink(OH_UdmfRecord* pThis, OH_UdsHyperlink* hyperlink);

/**
 * @brief 增加超文本标记语言类型{@link OH_UdsHtml}数据至统一数据记录{@link OH_UdmfRecord}中。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param html 表示指向超文本标记语言类型{@link OH_UdsHtml}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsHtml Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_AddHtml(OH_UdmfRecord* pThis, OH_UdsHtml* html);

/**
 * @brief 增加桌面图标类型{@link OH_UdsAppItem}数据至统一数据记录{@link OH_UdmfRecord}中。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param appItem 表示指向桌面图标类型{@link OH_UdsAppItem}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsAppItem Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_AddAppItem(OH_UdmfRecord* pThis, OH_UdsAppItem* appItem);

/**
 * @brief 增加文件Uri类型{@link OH_UdsFileUri}数据至统一数据记录{@link OH_UdmfRecord}中。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param fileUri 表示指向文件Uri类型{@link OH_UdsFileUri}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsFileUri Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfRecord_AddFileUri(OH_UdmfRecord* pThis, OH_UdsFileUri* fileUri);

/**
 * @brief 增加像素图片类型{@link OH_UdsPixelMap}数据至统一数据记录{@link OH_UdmfRecord}中。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param pixelMap 表示指向像素图片类型{@link OH_UdsPixelMap}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsPixelMap Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfRecord_AddPixelMap(OH_UdmfRecord* pThis, OH_UdsPixelMap* pixelMap);

/**
 * @brief 增加一个ArrayBuffer类型{@link OH_UdsArrayBuffer}的数据至统一数据记录{@link OH_UdmfRecord}中。
 * 
 * @param record 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param type 表示自定义的ArrayBuffer数据的数据类型标识，不可与已有的数据类型标识重复。
 * @param buffer 表示指向ArrayBuffer类型{@link OH_UdsArrayBuffer}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsArrayBuffer Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfRecord_AddArrayBuffer(OH_UdmfRecord* record, const char* type, OH_UdsArrayBuffer* buffer);

/**
 * @brief 增加一个内容卡片类型{@link OH_UdsContentForm}的数据至统一数据记录{@link OH_UdmfRecord}中。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param contentForm 表示指向内容卡片类型{@link OH_UdsContentForm}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsContentForm Udmf_ErrCode.
 * @since 14
 */
int OH_UdmfRecord_AddContentForm(OH_UdmfRecord* pThis, OH_UdsContentForm* contentForm);

/**
 * @brief 获取统一数据记录{@link OH_UdmfRecord}中所有类型的结果集。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param count 该参数是输出参数，结果集中的类型数量会写入该变量。
 * @return 执行成功时返回类型列表，否则返回nullptr。
 * @see OH_UdmfRecord.
 * @since 12
 */
char** OH_UdmfRecord_GetTypes(OH_UdmfRecord* pThis, unsigned int* count);

/**
 * @brief 获取统一数据记录{@link OH_UdmfRecord}中的特定类型的数据结果集。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param typeId 表示数据类型标识。
 * @param entry 该参数是输出参数，结果集中数据的具体信息会写入该变量。
 * @param count 该参数是输出参数，结果集中的数据长度会写入该变量。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 * 若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_GetGeneralEntry(OH_UdmfRecord* pThis, const char* typeId,
    unsigned char** entry, unsigned int* count);

/**
 * @brief 从统一数据记录{@link OH_UdmfRecord}中获取纯文本类型{@link OH_UdsPlainText}数据。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param plainText 该参数是输出参数，表示指向纯文本类型{@link OH_UdsPlainText}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 * 若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsPlainText Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_GetPlainText(OH_UdmfRecord* pThis, OH_UdsPlainText* plainText);

/**
 * @brief 从统一数据记录{@link OH_UdmfRecord}中获取超链接类型{@link OH_UdsHyperlink}数据。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param hyperlink 该参数是输出参数，表示指向超链接类型{@link OH_UdsHyperlink}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 * 若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsHyperlink Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_GetHyperlink(OH_UdmfRecord* pThis, OH_UdsHyperlink* hyperlink);

/**
 * @brief 从统一数据记录{@link OH_UdmfRecord}中获取超文本标记语言类型{@link OH_UdsHtml}数据。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param html 该参数是输出参数，表示指向超文本标记语言类型{@link OH_UdsHtml}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 * 若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsHtml Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_GetHtml(OH_UdmfRecord* pThis, OH_UdsHtml* html);

/**
 * @brief 从统一数据记录{@link OH_UdmfRecord}中获取桌面图标类型{@link OH_UdsAppItem}数据。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param appItem 该参数是输出参数，表示指向桌面图标类型{@link OH_UdsAppItem}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 * 若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsAppItem Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_GetAppItem(OH_UdmfRecord* pThis, OH_UdsAppItem* appItem);

/**
 * @brief 从统一数据记录{@link OH_UdmfRecord}中获取文件Uri类型{@link OH_UdsFileUri}数据。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param fileUri 该参数是输出参数，表示指向文件Uri类型{@link OH_UdsFileUri}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsFileUri Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfRecord_GetFileUri(OH_UdmfRecord* pThis, OH_UdsFileUri* fileUri);

/**
 * @brief 从统一数据记录{@link OH_UdmfRecord}中获取像素图片类型{@link OH_UdsPixelMap}数据。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param pixelMap 该参数是输出参数，表示指向像素图片类型{@link OH_UdsPixelMap}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsPixelMap Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfRecord_GetPixelMap(OH_UdmfRecord* pThis, OH_UdsPixelMap* pixelMap);

/**
 * @brief 将指定类型的统一数据提供者{@link OH_UdmfRecordProvider}设置至统一数据记录{@link OH_UdmfRecord}中。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param types 表示一组指定的要提供的数据类型。
 * @param count 表示指定的数据类型的数量。
 * @param provider 表示指向统一数据提供者对象{@link OH_UdmfRecordProvider}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdmfRecordProvider Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfRecord_SetProvider(OH_UdmfRecord* pThis, const char* const* types, unsigned int count,
    OH_UdmfRecordProvider* provider);

/**
 * @brief 从统一数据记录{@link OH_UdmfRecord}中获取ArrayBuffer类型{@link OH_UdsArrayBuffer}数据。
 * 
 * @param record 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param type 表示要获取的ArrayBuffer类型数据的数据类型标识。
 * @param buffer 该参数是输出参数，表示指向ArrayBuffer类型{@link OH_UdsArrayBuffer}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsArrayBuffer Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfRecord_GetArrayBuffer(OH_UdmfRecord* record, const char* type, OH_UdsArrayBuffer* buffer);

/**
 * @brief 从统一数据记录{@link OH_UdmfRecord}中获取内容卡片类型{@link OH_UdsContentForm}数据。
 * 
 * @param pThis 表示指向统一数据记录{@link OH_UdmfRecord}实例的指针。
 * @param contentForm 该参数是输出参数，表示指向内容卡片类型{@link OH_UdsContentForm}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfRecord OH_UdsContentForm Udmf_ErrCode.
 * @since 14
 */
int OH_UdmfRecord_GetContentForm(OH_UdmfRecord* pThis, OH_UdsContentForm* contentForm);

/**
 * @brief 从统一数据对象{@link OH_UdmfData}中获取第一个纯文本类型{@link OH_UdsPlainText}数据。
 * 
 * @param data 表示指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @param plainText 该参数是输出参数，表示指向纯文本类型{@link OH_UdsPlainText}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfData OH_UdsPlainText Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfData_GetPrimaryPlainText(OH_UdmfData* data, OH_UdsPlainText* plainText);

/**
 * @brief 从统一数据对象{@link OH_UdmfData}中获取第一个超文本标记语言类型{@link OH_UdsHtml}数据。
 * 
 * @param data 表示指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @param html 该参数是输出参数，表示指向超文本标记语言类型{@link OH_UdsHtml}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfData OH_UdsHtml Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfData_GetPrimaryHtml(OH_UdmfData* data, OH_UdsHtml* html);

/**
 * @brief 获取统一数据对象{@link OH_UdmfData}中包含的所有记录数量。
 * 
 * @param data 表示指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @return 返回统一数据记录{@link OH_UdmfRecord}的数量。
 * @see OH_UdmfData.
 * @since 13
 */
int OH_UdmfData_GetRecordCount(OH_UdmfData* data);

/**
 * @brief 获取统一数据对象{@link OH_UdmfData}中指定位置的数据记录。
 * 
 * @param data 表示指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @param index 表示要获取的统一数据记录{@link OH_UdmfRecord}在统一数据对象
 * {@link OH_UdmfData}中的索引。取值范围：[0, recordCount-1]，其中0表示第一个数据记录的索引，recordCount-1表示最后一个数据记录的索引，recordCount可通过
 * {@link OH_UdmfData_GetRecordCount}获取。若index超出有效范围，返回nullptr。
 * @return 执行成功时返回统一数据记录{@link OH_UdmfRecord}实例对象的指针，否则返回nullptr。
 * @see OH_UdmfData.
 * @since 13
 */
OH_UdmfRecord* OH_UdmfData_GetRecord(OH_UdmfData* data, unsigned int index);

/**
 * @brief 检查统一数据对象{@link OH_UdmfData}是否是来自本端设备的数据。
 * 
 * @param data 表示指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @return 返回数据是否是来自本端设备。返回true表示来自本端设备，返回false表示来自远端设备。
 * @see OH_UdmfData.
 * @since 13
 */
bool OH_UdmfData_IsLocal(OH_UdmfData* data);

/**
 * @brief 创建统一数据对象中数据记录属性{@link OH_UdmfProperty}指针及实例对象。当不再需要使用指针时，请使用{@link OH_UdmfProperty_Destroy}销毁实例对象，否则会导致内存泄漏。
 * 
 * @param unifiedData 表示指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @return 执行成功则返回一个指向属性{@link OH_UdmfProperty}实例对象的指针，否则返回nullptr。
 * @see OH_UdmfData OH_UdmfProperty.
 * @since 12
 */
OH_UdmfProperty* OH_UdmfProperty_Create(OH_UdmfData* unifiedData);

/**
 * @brief 销毁数据属性{@link OH_UdmfProperty}指针指向的实例对象。
 * 
 * @param pThis 表示指向数据属性{@link OH_UdmfProperty}实例的指针。
 * @see OH_UdmfProperty.
 * @since 12
 */
void OH_UdmfProperty_Destroy(OH_UdmfProperty* pThis);

/**
 * @brief 从数据属性{@link OH_UdmfProperty}中获取用户自定义标签值。
 * 
 * @param pThis 表示指向数据属性{@link OH_UdmfProperty}实例的指针。
 * @return 执行成功时返回自定义标签值的字符串指针，否则返回nullptr。
 * @see OH_UdmfProperty.
 * @since 12
 */
const char* OH_UdmfProperty_GetTag(OH_UdmfProperty* pThis);

/**
 * @brief 从数据属性{@link OH_UdmfProperty}中获取时间戳。
 * 
 * @param pThis 表示指向数据属性{@link OH_UdmfProperty}实例的指针。
 * @return 返回时间戳值。
 * @see OH_UdmfProperty
 * @since 12
 */
int64_t OH_UdmfProperty_GetTimestamp(OH_UdmfProperty* pThis);

/**
 * @brief 从数据属性{@link OH_UdmfProperty}中获取设备内适用范围属性。
 * 
 * @param pThis 表示指向数据属性{@link OH_UdmfProperty}实例的指针。
 * @return 返回设备内适用范围属性{@link Udmf_ShareOption}值。
 * @see OH_UdmfProperty Udmf_ShareOption
 * @since 12
 */
Udmf_ShareOption OH_UdmfProperty_GetShareOption(OH_UdmfProperty* pThis);

/**
 * @brief 从数据属性{@link OH_UdmfProperty}中获取自定义的附加整型参数。
 * 
 * @param pThis 表示指向数据属性{@link OH_UdmfProperty}实例的指针。
 * @param key 表示键值对的键。
 * @param defaultValue 用于用户自行设置获取值失败时的默认值。
 * @return 执行成功返回指定的键关联的整型值，否则返回用户设置的默认值defaultValue。
 * @see OH_UdmfProperty.
 * @since 12
 */
int OH_UdmfProperty_GetExtrasIntParam(OH_UdmfProperty* pThis,
    const char* key, int defaultValue);

/**
 * @brief 从数据属性{@link OH_UdmfProperty}中获取自定义的附加字符串参数。
 * 
 * @param pThis 表示指向数据属性{@link OH_UdmfProperty}实例的指针。
 * @param key 表示键值对的键。
 * @return 执行成功时返回指定的键关联的字符串值的指针，否则返回nullptr。
 * @see OH_UdmfProperty
 * @since 12
 */
const char* OH_UdmfProperty_GetExtrasStringParam(OH_UdmfProperty* pThis, const char* key);

/**
 * @brief 设置数据属性{@link OH_UdmfProperty}的自定义标签值。
 * 
 * @param pThis 表示指向数据属性{@link OH_UdmfProperty}实例的指针。
 * @param tag 表示自定义标签值。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfProperty Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfProperty_SetTag(OH_UdmfProperty* pThis, const char* tag);

/**
 * @brief 设置数据属性{@link OH_UdmfProperty}的设备内适用范围{@link Udmf_ShareOption}参数。
 * 
 * @param pThis 表示指向数据属性{@link OH_UdmfProperty}实例的指针。
 * @param option 表示设备内适用范围{@link Udmf_ShareOption}参数。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfProperty Udmf_ShareOption Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfProperty_SetShareOption(OH_UdmfProperty* pThis, Udmf_ShareOption option);

/**
 * @brief 设置数据属性{@link OH_UdmfProperty}的附加整型参数。
 * 
 * @param pThis 表示指向数据属性{@link OH_UdmfProperty}实例的指针。
 * @param key 表示键值对的键。
 * @param param 表示键值对的值。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfProperty Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfProperty_SetExtrasIntParam(OH_UdmfProperty* pThis, const char* key, int param);

/**
 * @brief 设置数据属性{@link OH_UdmfProperty}的附加整型参数。
 * 
 * @param pThis 表示指向数据属性{@link OH_UdmfProperty}实例的指针。
 * @param key 表示键值对的键。
 * @param param 表示键值对的值。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfProperty Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfProperty_SetExtrasStringParam(OH_UdmfProperty* pThis,
    const char* key, const char* param);

/**
 * @brief 在{@link OH_UdmfProperty}中设置权限，对{@link OH_UdmfData}生效。
 * 
 * @param pThis 表示指向{@link OH_UdmfProperty}实例的指针。
 * 说明：此授权策略仅在拖拽场景下生效，其他场景不生效。
 * @param authPolicy 表示拖拽场景下的URI授权策略，默认值READ+WRITE+PERSIST，只对单次数据生效，优先级较低。具体策略见{@link Udmf_AuthPermission}。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfProperty Udmf_ErrCode
 * @since 26.0.0
 */
int OH_UdmfProperty_SetAuthPermission(OH_UdmfProperty* pThis, uint32_t authPolicy);

/**
 * @brief 创建指向{@link OH_UdmfOptions}实例的指针。当不再需要使用指针时，请使用{@link OH_UdmfOptions_Destroy}销毁实例对象，否则会导致内存泄漏。
 * 
 * @return 执行成功则返回一个指向数据操作选项{@link OH_UdmfOptions}实例的指针，否则返回nullptr。
 * @see OH_UdmfOptions.
 * @since 20
 */
OH_UdmfOptions* OH_UdmfOptions_Create();

/**
 * @brief 销毁指向{@link OH_UdmfOptions}实例的指针。
 * 
 * @param pThis 指向数据操作选项{@link OH_UdmfOptions}实例的指针。
 * @see OH_UdmfOptions.
 * @since 20
 */
void OH_UdmfOptions_Destroy(OH_UdmfOptions* pThis);

/**
 * @brief 从数据操作选项{@link OH_UdmfOptions}实例中获取数据的唯一标识符信息。
 * 
 * @param pThis 指向数据操作选项{@link OH_UdmfOptions}实例的指针。
 * @return 输入有效入参时返回字符串指针，否则返回nullptr。
 * @see OH_UdmfOptions
 * @since 20
 */
const char* OH_UdmfOptions_GetKey(OH_UdmfOptions* pThis);

/**
 * @brief 设置数据操作选项{@link OH_UdmfOptions}实例中的数据的唯一标识符内容参数。
 * 
 * @param pThis 指向数据操作选项{@link OH_UdmfOptions}实例的指针。
 * @param key 数据的唯一标识符的新字符串值。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfOptions Udmf_ErrCode
 * @since 20
 */
int OH_UdmfOptions_SetKey(OH_UdmfOptions* pThis, const char* key);

/**
 * @brief 从数据操作选项{@link OH_UdmfOptions}实例中获取数据通路信息。
 * 
 * @param pThis 指向数据操作选项{@link OH_UdmfOptions}实例的指针。
 * @return 返回{@link Udmf_Intention}的值。
 * @see OH_UdmfOptions Udmf_Intention
 * @since 20
 */
Udmf_Intention OH_UdmfOptions_GetIntention(OH_UdmfOptions* pThis);

/**
 * @brief 设置数据操作选项{@link OH_UdmfOptions}实例中的数据通路内容参数。
 * 
 * @param pThis 指向数据操作选项{@link OH_UdmfOptions}实例的指针。
 * @param intention 数据通路类型参数。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfOptions Udmf_Intention Udmf_ErrCode.
 * @since 20
 */
int OH_UdmfOptions_SetIntention(OH_UdmfOptions* pThis, Udmf_Intention intention);

/**
 * @brief 重置数据操作选项{@link OH_UdmfOptions}实例为空。
 * 
 * @param pThis 指向数据操作选项{@link OH_UdmfOptions}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfOptions Udmf_ErrCode.
 * @since 20
 */
int OH_UdmfOptions_Reset(OH_UdmfOptions* pThis);

/**
 * @brief 从数据操作选项{@link OH_UdmfOptions}实例中获取数据可见性等级。
 * 
 * @param pThis 指向数据操作选项{@link OH_UdmfOptions}实例的指针。
 * @return 返回数据可见性等级{@link Udmf_Visibility}的值。
 * @see OH_UdmfOptions Udmf_Visibility
 * @since 20
 */
Udmf_Visibility OH_UdmfOptions_GetVisibility(OH_UdmfOptions* pThis);

/**
 * @brief 设置数据操作选项{@link OH_UdmfOptions}实例中的数据可见性等级。
 * 
 * @param pThis 指向数据操作选项{@link OH_UdmfOptions}实例的指针。
 * @param visibility 数据可见性等级{@link Udmf_Visibility}参数。
 * @return 返回执行结果。请参阅错误码定义{@link Udmf_ErrCode}。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 * @see OH_UdmfOptions Udmf_Visibility Udmf_ErrCode.
 * @since 20
 */
int OH_UdmfOptions_SetVisibility(OH_UdmfOptions* pThis, Udmf_Visibility visibility);

/**
 * @brief 从统一数据管理框架数据库中获取统一数据对象{@link OH_UdmfData}数据。
 * 
 * @param key 表示数据库存储的唯一标识符。
 * @param intention 表示数据通路类型{@link Udmf_Intention}。
 * @param unifiedData 该参数是输出参数，获取到的统一数据对象{@link OH_UdmfData}会写入该变量。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 * 若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfProperty Udmf_Intention Udmf_ErrCode.
 * @since 12
 */
int OH_Udmf_GetUnifiedData(const char* key, Udmf_Intention intention, OH_UdmfData* unifiedData);

/**
 * @brief 通过数据通路类型从统一数据管理框架数据库中获取统一数据对象{@link OH_UdmfData}数据。
 * 
 * @param options 指向数据操作选项{@link OH_UdmfOptions}实例的指针。
 * @param dataArray 该参数是输出参数，表示统一数据对象{@link OH_UdmfData}列表。
 * 需要使用{@link OH_UDMF_GetDataElementAt}函数通过下标访问每个元素。
 * 此指针需要使用{@link OH_Udmf_DestroyDataArray}函数释放。
 * @param dataSize 该参数是输出参数，表示获取到的统一数据对象个数。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 * 若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfData Udmf_Intention Udmf_ErrCode.
 * @since 20
 */
int OH_Udmf_GetUnifiedDataByOptions(OH_UdmfOptions* options, OH_UdmfData** dataArray, unsigned int* dataSize);

/**
 * @brief 从统一数据管理框架数据库中写入统一数据对象{@link OH_UdmfData}数据。
 * 
 * @param intention 表示数据通路类型{@link Udmf_Intention}。
 * @param unifiedData 表示统一数据对象{@link OH_UdmfData}数据。
 * @param key 表示成功将数据设置到数据库后对应数据的唯一标识符。
 * @param keyLen 表示唯一标识符参数的空间大小，内存大小不小于512字节。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 * 若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfProperty Udmf_Intention Udmf_ErrCode.
 * @since 12
 */
int OH_Udmf_SetUnifiedData(Udmf_Intention intention, OH_UdmfData* unifiedData,
    char* key, unsigned int keyLen);

/**
 * @brief 从统一数据管理框架数据库中写入统一数据对象{@link OH_UdmfData}数据。
 * 
 * @param options 指向数据操作选项{@link OH_UdmfOptions}实例的指针。
 * @param unifiedData 指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @param key 成功将数据设置到数据库后对应数据的唯一标识符，内存大小不小于{@link UDMF_KEY_BUFFER_LEN}。
 * @param keyLen 唯一标识符参数的空间大小。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 * 若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfOptions OH_UdmfData Udmf_ErrCode.
 * @since 20
 */
int OH_Udmf_SetUnifiedDataByOptions(OH_UdmfOptions* options, OH_UdmfData *unifiedData, char *key, unsigned int keyLen);

/**
 * @brief 对统一数据管理框架数据库中的统一数据对象{@link OH_UdmfData}数据进行数据更改。
 * 
 * @param options 指向数据操作选项{@link OH_UdmfOptions}实例的指针。
 * @param unifiedData 指向统一数据对象{@link OH_UdmfData}实例的指针。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 * 若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfOptions OH_UdmfData Udmf_ErrCode.
 * @since 20
 */
int OH_Udmf_UpdateUnifiedData(OH_UdmfOptions* options, OH_UdmfData* unifiedData);

/**
 * @brief 删除统一数据管理框架数据库中的统一数据对象{@link OH_UdmfData}数据。
 * 
 * @param options 指向数据操作选项{@link OH_UdmfOptions}实例的指针。
 * @param dataArray 该参数是输出参数，统一数据对象{@link OH_UdmfData}列表，需要使用{@link OH_UDMF_GetDataElementAt}函数通过下标访问每个元素。此指针需要使用
 * {@link OH_Udmf_DestroyDataArray}函数释放。
 * @param dataSize 该参数是输出参数，表示获取到的统一数据对象个数。
 * @return 返回执行的状态代码。
 * 若返回UDMF_E_OK，表示执行成功。
 * 若返回UDMF_E_INVALID_PARAM，表示传入了无效参数。
 * 若返回UDMF_ERR，表示内部数据错误。可能的原因是服务故障或者内存不足等。具体请参阅错误码定义{@link Udmf_ErrCode}。
 * @see OH_UdmfData Udmf_Intention Udmf_ErrCode.
 * @since 20
 */
int OH_Udmf_DeleteUnifiedData(OH_UdmfOptions* options, OH_UdmfData** dataArray, unsigned int* dataSize);



/**
 * @brief 从统一数据对象{@link OH_UdmfData}数组中获取指定下标的统一数据对象数据。
 * 
 * @param dataArray 指向统一数据对象{@link OH_UdmfData}的指针数组。
 * 只接受从{@link OH_Udmf_GetUnifiedDataByOptions}和{@link OH_Udmf_DeleteUnifiedData}接口中获得的指针数组。
 * @param index 表示要获取到的统一数据对象的下标。请确保该值不超出数组范围，否则会出现数组越界。
 * @return 执行成功则返回一个指向统一数据对象{@link OH_UdmfData}实例对象的指针，如果输入数组为空，则返回空。
 * @see OH_UdmfData
 * @since 22
 */
OH_UdmfData* OH_UDMF_GetDataElementAt(OH_UdmfData** dataArray, unsigned int index);

/**
 * @brief 销毁数据数组内存。
 * 
 * @param dataArray 指向统一数据对象{@link OH_UdmfData}的指针列表。
 * @param dataSize 列表中的数据大小。
 * @see OH_UdmfData
 * @since 20
 */
void OH_Udmf_DestroyDataArray(OH_UdmfData** dataArray, unsigned int dataSize);

/**
 * @brief 从进度信息{@link OH_Udmf_ProgressInfo}中获取进度百分比数据。
 * 
 * @param progressInfo 表示进度信息{@link OH_Udmf_ProgressInfo}。
 * @return 返回进度百分比数据。
 * @see OH_Udmf_ProgressInfo
 * @since 15
 */
int OH_UdmfProgressInfo_GetProgress(OH_Udmf_ProgressInfo* progressInfo);

/**
 * @brief 从进度信息{@link OH_Udmf_ProgressInfo}中获取状态信息。
 * 
 * @param progressInfo 表示进度信息{@link OH_Udmf_ProgressInfo}。
 * @return 返回状态信息。
 * @see OH_Udmf_ProgressInfo Udmf_ListenerStatus
 * @since 15
 */
int OH_UdmfProgressInfo_GetStatus(OH_Udmf_ProgressInfo* progressInfo);

/**
 * @brief 创建异步获取UDMF数据的请求参数{@link OH_UdmfGetDataParams}指针及实例对象。
 * 当不再需要使用指针时，请使用{@link OH_UdmfGetDataParams_Destroy}销毁实例对象，否则会导致内存泄漏。
 * 
 * @return 执行成功则返回一个指向属性{@link OH_UdmfGetDataParams}实例对象的指针，否则返回nullptr。
 * @see OH_UdmfGetDataParams
 * @since 15
 */
OH_UdmfGetDataParams* OH_UdmfGetDataParams_Create();

/**
 * @brief 销毁异步请求参数{@link OH_UdmfGetDataParams}指针指向的实例对象。
 * 
 * @param pThis 表示指向异步请求参数{@link OH_UdmfGetDataParams}实例的指针。
 * @see OH_UdmfGetDataParams
 * @since 15
 */
void OH_UdmfGetDataParams_Destroy(OH_UdmfGetDataParams* pThis);

/**
 * @brief 设置异步请求参数{@link OH_UdmfGetDataParams}中的目标路径。
 * 若设置了目标路径，会将文件类型的数据进行拷贝到指定路径。回调中获取到的文件类型数据会被替换为目标路径的URI。
 * 若不设置目标路径，则不会执行拷贝文件操作。回调中获取到的文件类型数据为源端路径URI。
 * 若应用涉及复杂文件处理策略，或需要将文件拷贝在多个路径下时，建议不设置此参数，由应用自行完成文件拷贝相关处理。
 * 
 * @param params 表示指向异步请求参数{@link OH_UdmfGetDataParams}实例的指针。
 * @param destUri 表示目标路径地址。
 * @see OH_UdmfGetDataParams
 * @since 15
 */
void OH_UdmfGetDataParams_SetDestUri(OH_UdmfGetDataParams* params, const char* destUri);

/**
 * @brief 设置异步请求参数{@link OH_UdmfGetDataParams}中的文件冲突选项。
 * 
 * @param params 表示指向异步请求参数{@link OH_UdmfGetDataParams}实例的指针。
 * @param options 表示文件拷贝冲突时的选项。
 * @see OH_UdmfGetDataParams Udmf_FileConflictOptions
 * @since 15
 */
void OH_UdmfGetDataParams_SetFileConflictOptions(OH_UdmfGetDataParams* params, const Udmf_FileConflictOptions options);

/**
 * @brief 设置异步请求参数{@link OH_UdmfGetDataParams}中的进度条指示选项。
 * 
 * @param params 表示指向异步请求参数{@link OH_UdmfGetDataParams}实例的指针。
 * @param progressIndicator 表示是否使用默认进度条选项。
 * @see OH_UdmfGetDataParams Udmf_ProgressIndicator
 * @since 15
 */
void OH_UdmfGetDataParams_SetProgressIndicator(OH_UdmfGetDataParams* params,
    const Udmf_ProgressIndicator progressIndicator);

/**
 * @brief 设置异步请求参数{@link OH_UdmfGetDataParams}中的监听回调函数。
 * 
 * @param params 表示指向异步请求参数{@link OH_UdmfGetDataParams}实例的指针。
 * @param dataProgressListener 用户自定义的监听回调函数，可用于获取进度信息和数据。
 * @see OH_UdmfGetDataParams OH_Udmf_DataProgressListener
 * @since 15
 */
void OH_UdmfGetDataParams_SetDataProgressListener(OH_UdmfGetDataParams* params,
    const OH_Udmf_DataProgressListener dataProgressListener);

/**
 * @brief 设置异步请求参数{@link OH_UdmfGetDataParams}中可接收的数据描述信息。
 * 
 * @param params 表示指向{@link OH_UdmfGetDataParams}实例的指针。
 * @param acceptableInfo 表示指向{@link OH_UdmfDataLoadInfo}实例的指针。
 * @see OH_UdmfGetDataParams OH_UdmfDataLoadInfo
 * @since 20
 */
void OH_UdmfGetDataParams_SetAcceptableInfo(OH_UdmfGetDataParams* params, OH_UdmfDataLoadInfo* acceptableInfo);

/**
 * @brief 创建指向数据加载参数{@link OH_UdmfDataLoadParams}实例的指针。
 * 当不再需要使用指针时，请使用{@link OH_UdmfDataLoadParams_Destroy}销毁实例对象，否则会导致内存泄漏。
 * 
 * @return 如果创建成功，返回一个指向数据加载参数{@link OH_UdmfDataLoadParams}实例的指针；否则返回nullptr。
 * @see OH_UdmfDataLoadParams
 * @since 20
 */
OH_UdmfDataLoadParams* OH_UdmfDataLoadParams_Create();

/**
 * @brief 销毁数据加载参数{@link OH_UdmfDataLoadParams}指针指向的实例对象。
 * 
 * @param pThis 表示指向数据加载参数{@link OH_UdmfDataLoadParams}实例的指针。
 * @see OH_UdmfDataLoadParams
 * @since 20
 */
void OH_UdmfDataLoadParams_Destroy(OH_UdmfDataLoadParams* pThis);

/**
 * @brief 设置数据加载参数{@link OH_UdmfDataLoadParams}中的数据加载处理函数。
 * 
 * @param params 表示指向数据加载参数{@link OH_UdmfDataLoadParams}实例的指针。
 * @param dataLoadHandler 表示用户定义的数据加载处理函数。
 * @see OH_UdmfDataLoadParams OH_Udmf_DataLoadHandler
 * @since 20
 */
void OH_UdmfDataLoadParams_SetLoadHandler(OH_UdmfDataLoadParams* params, const OH_Udmf_DataLoadHandler dataLoadHandler);

/**
 * @brief 设置数据加载参数{@link OH_UdmfDataLoadParams}中的数据加载信息。
 * 
 * @param params 表示指向数据加载参数{@link OH_UdmfDataLoadParams}实例的指针。
 * @param dataLoadInfo 表示指向数据加载信息{@link OH_UdmfDataLoadInfo}实例的指针。
 * @see OH_UdmfDataLoadParams OH_UdmfDataLoadInfo
 * @since 20
 */
void OH_UdmfDataLoadParams_SetDataLoadInfo(OH_UdmfDataLoadParams* params, OH_UdmfDataLoadInfo* dataLoadInfo);

/**
 * @brief 创建指向数据加载信息{@link OH_UdmfDataLoadInfo}实例的指针。
 * 当不再需要使用指针时，请使用{@link OH_UdmfDataLoadInfo_Destroy}销毁实例对象，否则会导致内存泄漏。
 * 
 * @return 如果创建成功，返回一个指向数据加载信息{@link OH_UdmfDataLoadInfo}实例的指针；否则返回nullptr。
 * @see OH_UdmfDataLoadInfo
 * @since 20
 */
OH_UdmfDataLoadInfo* OH_UdmfDataLoadInfo_Create();

/**
 * @brief 销毁数据加载信息{@link OH_UdmfDataLoadInfo}指针指向的实例对象。
 * 
 * @param dataLoadInfo 表示指向数据加载信息{@link OH_UdmfDataLoadInfo}实例的指针。
 * @see OH_UdmfDataLoadInfo
 * @since 20
 */
void OH_UdmfDataLoadInfo_Destroy(OH_UdmfDataLoadInfo* dataLoadInfo);

/**
 * @brief 从数据加载信息{@link OH_UdmfDataLoadInfo}中获取数据类型列表。
 * 
 * @param dataLoadInfo 表示指向数据加载信息{@link OH_UdmfDataLoadInfo}实例的指针。
 * @param count 返回的数据类型数量。
 * @return 返回数据类型的字符串数组。
 * @see OH_UdmfDataLoadInfo
 * @since 20
 */
char** OH_UdmfDataLoadInfo_GetTypes(OH_UdmfDataLoadInfo* dataLoadInfo, unsigned int* count);

/**
 * @brief 设置数据加载信息{@link OH_UdmfDataLoadInfo}中的数据类型。
 * 
 * @param dataLoadInfo 表示指向数据加载信息{@link OH_UdmfDataLoadInfo}实例的指针。
 * @param type 表示数据类型的字符串。
 * @see OH_UdmfDataLoadInfo
 * @since 20
 */
void OH_UdmfDataLoadInfo_SetType(OH_UdmfDataLoadInfo* dataLoadInfo, const char* type);

/**
 * @brief 获取数据加载信息{@link OH_UdmfDataLoadInfo}中的记录数量。
 * 
 * @param dataLoadInfo 表示指向数据加载信息{@link OH_UdmfDataLoadInfo}实例的指针。
 * @return 返回记录的数量。
 * @see OH_UdmfDataLoadInfo
 * @since 20
 */
int OH_UdmfDataLoadInfo_GetRecordCount(OH_UdmfDataLoadInfo* dataLoadInfo);

/**
 * @brief 设置数据加载信息{@link OH_UdmfDataLoadInfo}中的记录数量。
 * 
 * @param dataLoadInfo 表示指向数据加载信息{@link OH_UdmfDataLoadInfo}实例的指针。
 * @param recordCount 表示记录的数量。
 * @see OH_UdmfDataLoadInfo
 * @since 20
 */
void OH_UdmfDataLoadInfo_SetRecordCount(OH_UdmfDataLoadInfo* dataLoadInfo, unsigned int recordCount);

#ifdef __cplusplus
};
#endif

/** @} */
#endif
