/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup RDB
 * @{
 *
 * @brief 分布式数据管理（Distributed Data Manager，data）支持单设备的各种结构化数据的持久化，以及端云间的同步、共享功能。
 * 分布式数据管理定义了一系列数据类型，可以对数据进行增删改查。
 *
 * @since 10
 */

/**
 * @file relational_store.h
 *
 * @include database/rdb/relational_store.h
 * @brief 提供管理关系数据库（RDB）方法的接口，未标注支持向量数据库的接口仅支持关系型数据库。
 *
 * @kit ArkData
 * @library libnative_rdb_ndk.z.so
 * @syscap SystemCapability.DistributedDataManager.RelationalStore.Core
 * @since 10
 */
#ifndef RELATIONAL_STORE_ZH_CN_H
#define RELATIONAL_STORE_ZH_CN_H

#include "database/rdb/oh_cursor.h"
#include "database/rdb/oh_predicates.h"
#include "database/rdb/oh_rdb_crypto_param.h"
#include "database/rdb/oh_rdb_transaction.h"
#include "database/rdb/oh_rdb_types.h"
#include "database/rdb/oh_value_object.h"
#include "database/rdb/oh_values_bucket.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 数据库的安全级别枚举。
 *
 * @since 10
 */
typedef enum OH_Rdb_SecurityLevel {
    /**
     * @brief S1: 表示数据库的安全级别为低级别。当数据泄露时会产生较低影响。
     *
     */
    S1 = 1,
    /**
     * @brief S2: 表示数据库的安全级别为中级别。当数据泄露时会产生较大影响。
     *
     */
    S2,
    /**
     * @brief S3: 表示数据库的安全级别为高级别。当数据泄露时会产生重大影响。
     *
     */
    S3,
    /**
     * @brief S4: 表示数据库的安全级别为关键级别。当数据泄露时会产生严重影响。
     *
     */
    S4
} OH_Rdb_SecurityLevel;

/**
 * @brief 描述数据库的安全区域等级。
 *
 * @since 11
 */
typedef enum Rdb_SecurityArea {
    /**
     * @brief 安全区域等级为1。
     *
     */
    RDB_SECURITY_AREA_EL1 = 1,
    /**
     * @brief 安全区域等级为2。
     *
     */
    RDB_SECURITY_AREA_EL2,
    /**
     * @brief 安全区域等级为3。
     *
     */
    RDB_SECURITY_AREA_EL3,
    /**
     * @brief 安全区域等级为4。
     *
     */
    RDB_SECURITY_AREA_EL4,

    /**
     * @brief 安全区域等级为5。
     *
     * @since 12
     */
    RDB_SECURITY_AREA_EL5,
} Rdb_SecurityArea;

/**
 * @brief 管理关系型数据库配置。
 * @since 10
 */
#pragma pack(1)
typedef struct {
    /**
     * 该结构体的大小。
     */
    int selfSize;
    /**
     * 数据库文件路径，包含数据库名称在内的全路径长度不超过1024个字符。不能为空。
     */
    const char *dataBaseDir;
    /**
     * 数据库名称，不能为空且不能包含路径分隔符/。
     */
    const char *storeName;
    /**
     * 应用包名，不能为空。
     */
    const char *bundleName;
    /**
     * 应用模块名，不能为空。
     */
    const char *moduleName;
    /**
     * 指定数据库是否加密。true表示加密，false表示不加密。
     */
    bool isEncrypt;
    /**
     * 数据库安全级别{@link OH_Rdb_SecurityLevel}。
     */
    int securityLevel;
    /**
     * 数据库安全区域等级{@link Rdb_SecurityArea}。
     * @since 11
     */
    int area;
} OH_Rdb_Config;
#pragma pack()

/**
 * @brief 表示数据库实例。
 *
 * @since 10
 */
typedef struct {
    /**
     * OH_Rdb_Store结构体的唯一标识符。
     */
    int64_t id;
} OH_Rdb_Store;

/**
 * @brief 管理关系数据库配置，与{@link OH_Rdb_Config}的区别是该结构体成员变量不对外暴露，使用一系列方法配置该结构体的属性，支持向量数据库。
 *
 * @since 14
 */
typedef struct OH_Rdb_ConfigV2 OH_Rdb_ConfigV2;

/**
 * @brief 描述数据库的内核类型。
 *
 * @since 14
 */
typedef enum Rdb_DBType {
    /**
     * @brief 表示使用sqlite作为数据库内核。
     *
     * @since 14
     */
    RDB_SQLITE = 1,
    /**
     * @brief 表示使用凯莱数据库作为数据库内核。
     *
     * @since 14
     */
    RDB_CAYLEY = 2,
    /**
     * @brief 表示内核类型枚举值允许取值的最大值，这是一个非法值。
     *
     * @since 14
     */
    DBTYPE_BUTT = 64,
} Rdb_DBType;

/**
 * @brief 描述数据库的分词器类型。
 *
 * @since 17
 */
typedef enum Rdb_Tokenizer {
    /**
     * @brief 表示不使用分词器。
     *
	 * @since 17
     */
    RDB_NONE_TOKENIZER = 1,
    /**
     * @brief 表示使用ICU分词器。
     *
	 * @since 17
     */
    RDB_ICU_TOKENIZER = 2,
    /**
     * @brief 表示使用CUSTOM分词器。
     *
	 * @since 18
     */
    RDB_CUSTOM_TOKENIZER = 3,
} Rdb_Tokenizer;

/**
 * @brief 创建一个{@link OH_Rdb_ConfigV2}实例，并返回指向该实例的指针。
 *
 * @return 返回一个指向{@link OH_Rdb_ConfigV2}实例的指针。
 *     <br>使用完成后，必须通过{@link OH_Rdb_DestroyConfig}接口释放内存。
 * @see OH_Rdb_ConfigV2
 * @since 14
 */
OH_Rdb_ConfigV2 *OH_Rdb_CreateConfig();

/**
 * @brief 销毁由{@link OH_Rdb_CreateConfig}创建的{@link OH_Rdb_ConfigV2}对象。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 14
 */
int OH_Rdb_DestroyConfig(OH_Rdb_ConfigV2 *config);

/**
 * @brief 给指定的数据库文件配置{@link OH_Rdb_ConfigV2}，设置数据库文件路径。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置。
 * @param databaseDir 表示数据库文件路径，不能为空，包含数据库名称在内的全路径长度不超过1024个字符。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 14
 */
int OH_Rdb_SetDatabaseDir(OH_Rdb_ConfigV2 *config, const char *databaseDir);

/**
 * @brief 给指定的数据库文件配置{@link OH_Rdb_ConfigV2}，设置数据库名称。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置。
 * @param storeName 表示数据库名称，不能为空且不能包含路径分隔符/。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 14
 */
int OH_Rdb_SetStoreName(OH_Rdb_ConfigV2 *config, const char *storeName);

/**
 * @brief 给指定的数据库文件配置{@link OH_Rdb_ConfigV2}，设置应用包名。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置。
 * @param bundleName 表示数据库应用包名，不能为空。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 14
 */
int OH_Rdb_SetBundleName(OH_Rdb_ConfigV2 *config, const char *bundleName);

/**
 * @brief 给指定的数据库文件配置{@link OH_Rdb_ConfigV2}，设置应用模块名。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置。
 * @param moduleName 表示数据库应用模块名，不能为空。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 14
 */
int OH_Rdb_SetModuleName(OH_Rdb_ConfigV2 *config, const char *moduleName);

/**
 * @brief 给指定的数据库文件配置{@link OH_Rdb_ConfigV2}，设置数据库是否加密。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置。
 * @param isEncrypted 表示数据库是否加密。true表示加密，false表示不加密。数据库创建完成后，此参数不允许直接修改。如需变更数据库加密状态，请调用{@link OH_Rdb_RekeyEx}接口进行更新操作。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 14
 */
int OH_Rdb_SetEncrypted(OH_Rdb_ConfigV2 *config, bool isEncrypted);

/**
 * @brief 给指定的数据库文件配置{@link OH_Rdb_ConfigV2}，设置数据库安全级别{@link OH_Rdb_SecurityLevel}。
 * <br>创建数据库时必须调用该方法，否则数据库文件无法创建成功，调用{@link OH_Rdb_CreateOrOpen}接口时将返回错误码RDB_E_INVALID_ARGS。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置。
 * @param securityLevel 表示数据库安全级别{@link OH_Rdb_SecurityLevel}。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 14
 */
int OH_Rdb_SetSecurityLevel(OH_Rdb_ConfigV2 *config, int securityLevel);

/**
 * @brief 给指定的数据库文件配置{@link OH_Rdb_ConfigV2}，设置数据库安全区域等级{@link Rdb_SecurityArea}。
 * <br>创建数据库时必须调用该方法，否则数据库文件无法创建成功，调用{@link OH_Rdb_CreateOrOpen}接口时将返回错误码RDB_E_INVALID_ARGS。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置。
 * @param area 表示数据库安全区域等级{@link Rdb_SecurityArea}。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 14
 */
int OH_Rdb_SetArea(OH_Rdb_ConfigV2 *config, int area);

/**
 * @brief 给指定的数据库文件配置{@link OH_Rdb_ConfigV2}，设置数据库类型{@link Rdb_DBType}。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置。
 * @param dbType 表示数据库的数据库类型{@link Rdb_DBType}。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。
 *     <br>RDB_E_NOT_SUPPORTED 表示不支持当前操作。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 14
 */
int OH_Rdb_SetDbType(OH_Rdb_ConfigV2 *config, int dbType);

/**
 * @brief 设置数据库的自定义目录。
 *
 * @param config 表示此关系型数据库相关的数据库配置{@link OH_Rdb_ConfigV2}的指针。
 * @param customDir 表示数据库的自定义目录，目录长度不能超过128字节。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
 */
int OH_Rdb_SetCustomDir(OH_Rdb_ConfigV2 *config, const char *customDir);

/**
 * @brief 设置关系型数据库是否为只读模式。
 *
 * @param config 表示此关系型数据库相关的数据库配置{@link OH_Rdb_ConfigV2}的指针。
 * @param readOnly 表示关系型数据库存储是否为只读模式，true表示设置为只读模式，false表示设置为读写模式。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
 */
int OH_Rdb_SetReadOnly(OH_Rdb_ConfigV2 *config, bool readOnly);

/**
 * @brief 设置具有特定功能（如全文检索）的动态库。
 *
 * @param config 表示此关系型数据库相关的数据库配置{@link OH_Rdb_ConfigV2}的指针。
 * @param plugins 表示动态库的名称数组。
 * @param length 表示插件数组的大小，最大值为16。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
 */
int OH_Rdb_SetPlugins(OH_Rdb_ConfigV2 *config, const char **plugins, int32_t length);

/**
 * @brief 设置自定义加密参数。
 *
 * @param config 表示此关系型数据库相关的数据库配置{@link OH_Rdb_ConfigV2}的指针。
 * @param cryptoParam 表示自定义加密参数。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
 */
int OH_Rdb_SetCryptoParam(OH_Rdb_ConfigV2 *config, const OH_Rdb_CryptoParam *cryptoParam);

/**
 * @brief 给指定的数据库文件配置设置分词器类型。
 *
 * @param config 指向此RDB存储相关的数据库配置的指针。
 * @param tokenizer 表示数据库的分词器类型。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。
 *     <br>RDB_E_NOT_SUPPORTED 表示不支持当前操作。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 17
 */
int OH_Rdb_SetTokenizer(OH_Rdb_ConfigV2 *config, Rdb_Tokenizer tokenizer);

/**
 * @brief 指定数据库是否需要持久化。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}实例的指针。
 *     <br>指示与此RDB存储相关的数据库的配置。
 * @param isPersistent 指示数据库是否需要持久化。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 18
 */
int OH_Rdb_SetPersistent(OH_Rdb_ConfigV2 *config, bool isPersistent);

/**
 * @brief 开启或关闭基于语义索引的知识加工。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}实例的指针。
 * @param enableSemanticIndex 开启或关闭基于语义索引的知识加工能力标志。
 *     <br>true表示开启。false表示关闭。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 20
 */
int OH_Rdb_SetSemanticIndex(OH_Rdb_ConfigV2 *config, bool enableSemanticIndex);

/**
 * @brief 判断当前平台是否支持传入的分词器。
 *
 * @param tokenizer 要校验是否支持的分词器。
 * @param isSupported 校验结果的指针，作为出参使用。true表示当前平台支持当前校验的分词器，false表示当前平台不支持当前校验的分词器。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 18
 */
int OH_Rdb_IsTokenizerSupported(Rdb_Tokenizer tokenizer, bool *isSupported);

/**
 * @brief 获得支持的数据库类型{@link Rdb_DBType}。
 *
 * @param typeCount 表示支持的数据库类型的数组的长度，作为出参使用。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @since 14
 */
const int *OH_Rdb_GetSupportedDbType(int *typeCount);

/**
 * @brief 创建{@link OH_VObject}实例。
 *
 * @return 创建成功则返回一个指向{@link OH_VObject}结构体实例的指针，否则返回NULL。
 * @see OH_VObject.
 * @since 10
 */
OH_VObject *OH_Rdb_CreateValueObject();

/**
 * @brief 创建{@link OH_VBucket}实例。
 *
 * @return 创建成功则返回一个指向{@link OH_VBucket}结构体实例的指针，否则返回NULL。
 * @see OH_VBucket.
 * @since 10
 */
OH_VBucket *OH_Rdb_CreateValuesBucket();

/**
 * @brief 创建{@link OH_Predicates}实例。
 *
 * @param table 表示数据库表名。
 * @return 创建成功则返回一个指向{@link OH_Predicates}结构体实例的指针，否则返回NULL。
 * @see OH_Predicates.
 * @since 10
 */
OH_Predicates *OH_Rdb_CreatePredicates(const char *table);

/**
 * @brief 获得一个相关的{@link OH_Rdb_Store}实例，操作关系型数据库。
 *
 * @param config 指向{@link OH_Rdb_Config}实例的指针，与此RDB存储相关的数据库配置。
 * @param errCode 表示函数执行状态，作为出参使用。
 * @return 创建成功则返回一个指向{@link OH_Rdb_Store}结构体实例的指针，否则返回NULL。
 *     <br>RDB_OK表示成功。
 *     <br>RDB_E_INVALID_ARGS表示无效参数。
 * @see OH_Rdb_Config, OH_Rdb_Store.
 * @since 10
 */
OH_Rdb_Store *OH_Rdb_GetOrOpen(const OH_Rdb_Config *config, int *errCode);

/**
 * @brief 使用指定的数据库文件配置{@link OH_Rdb_ConfigV2}，获得一个对应的{@link OH_Rdb_Store}实例，用来操作关系型数据库。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置。
 * @param errCode 表示函数执行状态，作为出参使用。
 * @return 创建成功则返回一个指向{@link OH_Rdb_Store}结构体实例的指针，否则返回NULL。
 *     <br>RDB_OK表示成功。
 *     <br>RDB_E_INVALID_ARGS表示无效参数。
 * @see OH_Rdb_ConfigV2, OH_Rdb_Store.
 * @since 14
 */
OH_Rdb_Store *OH_Rdb_CreateOrOpen(const OH_Rdb_ConfigV2 *config, int *errCode);

/**
 * @brief 销毁{@link OH_Rdb_Store}对象，并回收该对象占用的内存。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store, OH_Rdb_ErrCode.
 * @since 10
 */
int OH_Rdb_CloseStore(OH_Rdb_Store *store);

/**
 * @brief 使用指定的数据库文件配置删除数据库。
 *
 * @param config 表示数据库的配置。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_ErrCode.
 * @since 10
 */
int OH_Rdb_DeleteStore(const OH_Rdb_Config *config);

/**
 * @brief 使用指定的数据库文件配置{@link OH_Rdb_ConfigV2}删除数据库。
 * <br>当使用向量数据库时，在调用接口前，应当确保向量数据库已经打开的OH_Rdb_Store和OH_Cursor均已成功关闭。
 *
 * @param config 表示数据库的配置。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_ErrCode.
 * @since 14
 */
int OH_Rdb_DeleteStoreV2(const OH_Rdb_ConfigV2 *config);

/**
 * @brief 向目标表中插入一行数据。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param table 表示指定的目标表名。
 * @param valuesBucket 表示要插入到表中的数据行{@link OH_VBucket}。
 * @return 如果插入成功，返回rowID，否则返回的结果小于0。
 *     <br>RDB_ERR表示插入失败。
 *     <br>RDB_E_INVALID_ARGS表示无效参数。
 * @see OH_Rdb_Store, OH_VBucket, OH_Rdb_ErrCode.
 * @since 10
 */
int OH_Rdb_Insert(OH_Rdb_Store *store, const char *table, OH_VBucket *valuesBucket);

/**
 * @brief 向目标表中插入一行数据，并支持冲突解决。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param table 表示目标表的名称。
 * @param row 表示要插入到表中的数据。
 * @param resolution 表示发生冲突时的解决策略。
 * @param rowId 表示插入成功后返回的行号。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示执行成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示输入参数无效。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已关闭。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL文件大小超过默认限制。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库已损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误：违反约束导致操作中止。
 * @since 20
 */
int OH_Rdb_InsertWithConflictResolution(OH_Rdb_Store *store, const char *table, OH_VBucket *row,
    Rdb_ConflictResolution resolution, int64_t *rowId);

/**
 * @brief 将一批数据插入到目标表中。
 * <br>单次插入参数的最大数量限制为32766，超出上限会返回RDB_E_INVALID_ARGS错误码。参数数量计算方式为插入数据条数乘以插入数据的所有字段的并集大小。
 * <br>例如：插入数据的所有字段的并集大小为10，则最多可以插入3276条数据（3276*10=32760）。
 * <br>请确保在调用接口时遵守此限制，以避免因参数数量过多而导致错误。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param table 表示要插入数据的目标表名。
 * @param rows 表示要插入到表中的一组数据。
 * @param resolution 表示发生冲突时的解决策略。
 * @param changes 输出参数，表示插入成功的次数。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已经关闭。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL日志文件大小超过默认值。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误码：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误码：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误码：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误码：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误码：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误码：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误码：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误码：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误码：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误码：SQLite约束。
 * @since 18
 */
int OH_Rdb_BatchInsert(OH_Rdb_Store *store, const char *table,
    const OH_Data_VBuckets *rows, Rdb_ConflictResolution resolution, int64_t *changes);

/**
 * @brief 根据指定的条件更新数据库中的数据。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param valuesBucket 表示要更新到表中的数据行{@link OH_VBucket}。
 * @param predicates 指向{@link OH_Predicates}实例的指针，指定更新条件。
 * @return 如果更新成功，返回更新的行数，否则返回的结果小于0。
 *     <br>RDB_ERR表示更新失败。
 *     <br>RDB_E_INVALID_ARGS表示无效参数。
 * @see OH_Rdb_Store, OH_Bucket, OH_Predicates, OH_Rdb_ErrCode.
 * @since 10
 */
int OH_Rdb_Update(OH_Rdb_Store *store, OH_VBucket *valuesBucket, OH_Predicates *predicates);

/**
 * @brief 根据指定条件更新数据库中的数据，并支持冲突解决。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param row 表示要更新到表中的数据行。
 * @param predicates 指向{@link OH_Predicates}实例的指针，指定更新条件。
 * @param resolution 表示发生冲突时的解决策略。
 * @param changes 输出参数，表示成功更新的行数。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示执行成功。
 *     <br>返回RDB_E_ERROR 表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示输入参数无效。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已关闭。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL文件大小超过默认限制。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库已损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误：违反约束导致操作中止。
 * @since 20
 */
int OH_Rdb_UpdateWithConflictResolution(OH_Rdb_Store *store, OH_VBucket *row, OH_Predicates *predicates,
    Rdb_ConflictResolution resolution, int64_t *changes);

/**
 * @brief 根据指定的条件删除数据库中的数据。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param predicates 指向{@link OH_Predicates}实例的指针，指定删除条件。
 * @return 如果删除成功，返回删除的行数；如果失败，则返回的结果小于0。
 *     <br>RDB_ERR表示删除失败。
 *     <br>RDB_E_INVALID_ARGS表示无效参数。
 * @see OH_Rdb_Store, OH_Predicates, OH_Rdb_ErrCode.
 * @since 10
 */
int OH_Rdb_Delete(OH_Rdb_Store *store, OH_Predicates *predicates);

/**
 * @brief 根据指定条件查询数据库中的数据。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param predicates 指向{@link OH_Predicates}实例的指针，指定查询条件。
 * @param columnNames 表示要查询的列。如果值为空，则查询应用于所有列。
 * @param length 该参数为输入参数，表示开发者传入的columnNames数组的长度。若length大于columnNames数组的实际长度，则会访问越界。
 * @return 如果查询成功则返回一个指向{@link OH_Cursor}结构体实例的指针，否则返回NULL。
 * @see OH_Rdb_Store, OH_Predicates, OH_Cursor.
 * @since 10
 */
OH_Cursor *OH_Rdb_Query(OH_Rdb_Store *store, OH_Predicates *predicates, const char *const *columnNames, int length);

/**
 * @brief 根据指定条件查询数据库中的数据，不计算行数。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param predicates 指向{@link OH_Predicates}实例的指针，指定查询条件。
 * @param columns 表示要查询的列。如果值为空数组，则查询适用于所有列。
 * @param length 该参数为输入参数，表示开发者传入的columns数组的长度。若length大于columns数组的实际长度，则会访问越界。
 * @return 如果查询成功则返回一个指向{@link OH_Cursor}结构体实例的指针。如果获取store失败或结果集为空，则返回nullptr。
 * @see OH_Rdb_Store, OH_Predicates, OH_Cursor.
 * @since 23
 */
OH_Cursor *OH_Rdb_QueryWithoutRowCount(OH_Rdb_Store *store, OH_Predicates *predicates,
    const char *const columns[], int length);

/**
 * @brief 执行有返回值的SQL语句，不计算行数，支持向量数据库。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param sql 要执行的SQL语句。
 * @param args 指向{@link OH_Data_Values}实例的指针。SQL语句完整时，args可填写为nullptr。
 * @return 如果查询成功则返回一个指向{@link OH_Cursor}结构体实例的指针。如果SQL语句无效或内存分配失败，则返回nullptr。
 * @see OH_Rdb_Store.
 * @since 23
 */
OH_Cursor *OH_Rdb_QuerySqlWithoutRowCount(OH_Rdb_Store *store, const char *sql, const OH_Data_Values *args);

/**
 * @brief 执行无返回值的SQL语句。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param sql 指定要执行的SQL语句。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @since 10
 */
int OH_Rdb_Execute(OH_Rdb_Store *store, const char *sql);

/**
 * @brief 执行有返回值的SQL语句，支持向量数据库。
 * <br>不支持开头包含注释的语句。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param sql 指定要执行的SQL语句。
 * @param args 可选参数，指向{@link OH_Data_Values}实例的指针。
 * @param result 执行成功时指向{@link OH_Data_Value}实例的指针，作为出参使用。使用完成后，必须通过{@link OH_Value_Destroy}接口释放内存。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已经关闭。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL日志文件大小超过默认值。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误码：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误码：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误码：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误码：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误码：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误码：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误码：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误码：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误码：数据类型不匹配。
 * @see OH_Value_Destroy.
 * @since 18
 */
int OH_Rdb_ExecuteV2(OH_Rdb_Store *store, const char *sql, const OH_Data_Values *args, OH_Data_Value **result);

/**
 * @brief 使用指定的事务ID执行无返回值的SQL语句，仅支持向量数据库。
 * <br>不支持开头包含注释的语句。
 *
 * @param store 表示一个指向{@link OH_Rdb_Store} 实例的指针。
 * @param trxId 调用{@link OH_Rdb_BeginTransWithTrxId}获得的事务ID，当设置为0时，表示不启用事务。
 * @param sql 指定要执行的SQL语句。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK表示成功。
 *     <br>RDB_E_INVALID_ARGS表示无效参数，可能情况如下：
 *     <br>传入参数为空指针。
 *     <br>当前事务ID不是调用{@link OH_Rdb_BeginTransWithTrxId}获得的。
 *     <br>当前事务ID已经调用{@link OH_Rdb_CommitByTrxId}提交。
 *     <br>当前事务ID已经调用{@link OH_Rdb_RollBackByTrxId}回滚。
 *     <br>当store或者sql为NULL时。
 *     <br>RDB_E_NOT_SUPPORTED表示不支持当前操作。
 * @see OH_Rdb_Store.
 * @since 14
 */
int OH_Rdb_ExecuteByTrxId(OH_Rdb_Store *store, int64_t trxId, const char *sql);

/**
 * @brief 根据指定SQL语句查询数据库中的数据，支持向量数据库。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param sql 指定要执行的SQL语句。
 * @return 如果查询成功则返回一个指向{@link OH_Cursor}结构体实例的指针，否则返回NULL。
 * @see OH_Rdb_Store.
 * @since 10
 */
OH_Cursor *OH_Rdb_ExecuteQuery(OH_Rdb_Store *store, const char *sql);

/**
 * @brief 根据指定SQL语句查询数据库中的数据，支持向量数据库。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param sql 指定要执行的SQL语句。
 * @param args 可选参数，指向{@link OH_Data_Values}实例的指针。
 * @return 如果查询成功则返回一个指向{@link OH_Cursor}结构体实例的指针，使用完成后及时释放{@link OH_Cursor}。
 *     <br>如果SQL语句无效或内存分配失败，则返回NULL。
 * @see OH_Rdb_Store.
 * @since 18
 */
OH_Cursor *OH_Rdb_ExecuteQueryV2(OH_Rdb_Store *store, const char *sql, const OH_Data_Values *args);

/**
 * @brief 在开始执行SQL语句之前，开始事务。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @since 10
 */
int OH_Rdb_BeginTransaction(OH_Rdb_Store *store);

/**
 * @brief 回滚已经执行的SQL语句。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @since 10
 */
int OH_Rdb_RollBack(OH_Rdb_Store *store);

/**
 * @brief 提交已执行的SQL语句。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @since 10
 */
int OH_Rdb_Commit(OH_Rdb_Store *store);

/**
 * @brief 在开始执行SQL语句之前，开始事务，并获得该事务的ID，仅支持向量数据库。
 *
 * @param store 表示一个指向{@link OH_Rdb_Store}实例的指针。
 * @param trxId 事务ID，作为出参使用。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。
 *     <br>RDB_E_NOT_SUPPORTED 表示不支持当前操作。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @since 14
 */
int OH_Rdb_BeginTransWithTrxId(OH_Rdb_Store *store, int64_t *trxId);

/**
 * @brief 使用指定的事务ID，回滚已经执行的SQL语句，仅支持向量数据库。
 *
 * @param store 表示一个指向{@link OH_Rdb_Store}实例的指针。
 * @param trxId 表示需要回滚的事务的ID。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK表示成功。
 *     <br>RDB_E_INVALID_ARGS表示无效参数，可能情况如下：
 *     <br>传入参数为空指针。
 *     <br>当前事务ID不是调用{@link OH_Rdb_BeginTransWithTrxId}获得的。
 *     <br>当前事务ID已经调用{@link OH_Rdb_CommitByTrxId}提交。
 *     <br>当前事务ID已经调用{@link OH_Rdb_RollBackByTrxId}回滚。
 *     <br>RDB_E_NOT_SUPPORTED表示不支持当前操作。
 * @see OH_Rdb_Store.
 * @since 14
 */
int OH_Rdb_RollBackByTrxId(OH_Rdb_Store *store, int64_t trxId);

/**
 * @brief 使用指定的事务ID，提交已经执行的SQL语句，仅支持向量数据库。
 *
 * @param store 表示一个指向{@link OH_Rdb_Store}实例的指针。
 * @param trxId 表示需要提交的事务的ID。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS表示无效参数，可能情况如下：
 *     <br>传入参数为空指针。
 *     <br>当前事务ID不是调用{@link OH_Rdb_BeginTransWithTrxId}获得的。
 *     <br>当前事务ID已经调用{@link OH_Rdb_CommitByTrxId}提交。
 *     <br>当前事务ID已经调用{@link OH_Rdb_RollBackByTrxId}回滚。
 *     <br>RDB_E_NOT_SUPPORTED表示不支持当前操作。
 * @see OH_Rdb_Store.
 * @since 14
 */
int OH_Rdb_CommitByTrxId(OH_Rdb_Store *store, int64_t trxId);

/**
 * @brief 以指定路径备份数据库，支持向量数据库。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param databasePath 指定数据库的备份文件路径。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @since 10
 */
int OH_Rdb_Backup(OH_Rdb_Store *store, const char *databasePath);

/**
 * @brief 从指定的数据库备份文件恢复数据库，支持向量数据库。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param databasePath 指定数据库的备份文件路径。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @since 10
 */
int OH_Rdb_Restore(OH_Rdb_Store *store, const char *databasePath);

/**
 * @brief 获取数据库版本。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param version 表示版本号，作为出参使用。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @since 10
 */
int OH_Rdb_GetVersion(OH_Rdb_Store *store, int *version);

/**
 * @brief 设置数据库版本。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param version 表示版本号。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @since 10
 */
int OH_Rdb_SetVersion(OH_Rdb_Store *store, int version);

/**
 * @brief 描述表的分布式类型的枚举。
 *
 * @since 11
 */
typedef enum Rdb_DistributedType {
    /**
     * @brief 表示在设备和云端之间分布式的数据库表。
     *
     */
    RDB_DISTRIBUTED_CLOUD
} Rdb_DistributedType;

/**
 * @brief 描述{@link Rdb_DistributedConfig}的版本。
 *
 * @since 11
 */
#define DISTRIBUTED_CONFIG_VERSION 1
/**
 * @brief 记录表的分布式配置信息。
 *
 * @since 11
 */
typedef struct Rdb_DistributedConfig {
    /**
     * 表示Rdb_DistributedConfig结构的版本。
     */
    int version;
    /**
     * 表示该表是否支持端云自动同步。为true时，支持系统自动触发端云同步；为false时不支持系统自动触发端云同步，需要调用{@link OH_Rdb_CloudSync}接口触发端云同步。
     */
    bool isAutoSync;
} Rdb_DistributedConfig;

/**
 * @brief 设置分布式数据库表。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param tables 表示要设置的表名。
 * @param count 要设置的分布式数据库表的数量。
 * @param type 表的分布式类型{@link Rdb_DistributedType}。
 * @param config 表的分布式配置信息{@link Rdb_DistributedConfig}。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @see Rdb_DistributedConfig.
 * @since 11
 */
int OH_Rdb_SetDistributedTables(OH_Rdb_Store *store, const char *tables[], uint32_t count, Rdb_DistributedType type,
    const Rdb_DistributedConfig *config);

/**
 * @brief 获取数据库表中数据的最后修改时间。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param tableName 要查找的分布式数据库表表名。
 * @param columnName 指定要查询的数据库表的列名。
 * @param values 指定要查询的行的主键。如果数据库表无主键，参数columnName需传入"rowid"，此时values为要查询的数据库表的行号。
 * @return 如果操作成功则返回一个指向{@link OH_Cursor}结构体实例的指针，否则返回NULL。
 * @see OH_Rdb_Store.
 * @see OH_VObject.
 * @see OH_Cursor.
 * @since 11
 */
OH_Cursor *OH_Rdb_FindModifyTime(OH_Rdb_Store *store, const char *tableName, const char *columnName,
    OH_VObject *values);

/**
 * @brief 描述数据变更类型。
 *
 * @since 11
 */
typedef enum Rdb_ChangeType {
    /**
     * @brief 表示是数据发生变更。
     *
     */
    RDB_DATA_CHANGE,
    /**
     * @brief 表示是资产附件发生了变更。
     *
     */
    RDB_ASSET_CHANGE
} Rdb_ChangeType;

/**
 * @brief 描述发生变化的行的主键或者行号。
 *
 * @since 11
 */
typedef struct Rdb_KeyInfo {
    /**
     * 表示发生变化的主键或者行号的数量。
     */
    int count;

    /**
     * 表示主键或行号的数据类型{@link OH_ColumnType}。
     */
    int type;

    /**
     * 表示密钥信息的数据。
     *
     * @since 11
     */
    typedef union Rdb_KeyData {
        /**
         * 表示uint64_t类型的数据。
         */
        uint64_t integer;

        /**
         * 表示double类型的数据。
         */
        double real;

        /**
         * 表示const char *类型的数据。
         */
        const char *text;
    } *data;
} Rdb_KeyInfo;

/**
 * @brief 描述{@link Rdb_ChangeInfo}的版本。
 *
 * @since 11
 */
#define DISTRIBUTED_CHANGE_INFO_VERSION 1

/**
 * @brief 记录端云同步过程详情。
 *
 * @since 11
 */
typedef struct Rdb_ChangeInfo {
    /**
     * 用于唯一标识Rdb_ChangeInfo结构体的版本。
     */
    int version;

    /**
     * 表示发生变化的表的名称。
     */
    const char *tableName;

    /**
     * 表示发生变化的数据的类型，数据或者资产附件发生变化。
     */
    int ChangeType;

    /**
     * 记录插入数据的位置，如果该表的主键是string类型，该值是主键的值，否则该值表示插入数据的行号。
     */
    Rdb_KeyInfo inserted;

    /**
     * 记录更新数据的位置，如果该表的主键是string类型，该值是主键的值，否则该值表示更新数据的行号。
     */
    Rdb_KeyInfo updated;

    /**
     * 记录删除数据的位置，如果该表的主键是string类型，该值是主键的值，否则该值表示删除数据的行号。
     */
    Rdb_KeyInfo deleted;
} Rdb_ChangeInfo;

/**
 * @brief 描述订阅类型。
 *
 * @since 11
 */
typedef enum Rdb_SubscribeType {
    /**
     * @brief 订阅云端数据更改。
     *
     */
    RDB_SUBSCRIBE_TYPE_CLOUD,

    /**
     * @brief 订阅云端数据更改详情。
     *
     */
    RDB_SUBSCRIBE_TYPE_CLOUD_DETAILS,

    /**
     * @brief 订阅本地数据更改详情。
     *
     * @since 12
     */
    RDB_SUBSCRIBE_TYPE_LOCAL_DETAILS,
} Rdb_SubscribeType;

/**
 * @brief 端云数据更改事件的回调函数。
 *
 * @param context 表示数据观察者的上下文。
 * @param values 表示发生变更的云账号。
 * @param count 表示更改的端云帐户数量。
 * @since 11
 */
typedef void (*Rdb_BriefObserver)(void *context, const char *values[], uint32_t count);

/**
 * @brief 端云数据更改事件的细节的回调函数。
 *
 * @param context 表示数据观察者的上下文。
 * @param changeInfo 表示已更改表的信息{@link Rdb_ChangeInfo}。
 * @param count 表示更改的表的数量。
 * @see Rdb_ChangeInfo.
 * @since 11
 */
typedef void (*Rdb_DetailsObserver)(void *context, const Rdb_ChangeInfo **changeInfo, uint32_t count);

/**
 * @brief 表示回调函数。
 *
 * @since 11
 */
typedef union Rdb_SubscribeCallback {
    /**
     * 云端数据变更详情事件的回调函数。
     */
    Rdb_DetailsObserver detailsObserver;

    /**
     * 云端数据变更事件的回调函数。
     */
    Rdb_BriefObserver briefObserver;
} Rdb_SubscribeCallback;

/**
 * @brief 表示数据观察者。
 *
 * @since 11
 */
typedef struct Rdb_DataObserver {
    /**
     * 表示数据观察者的上下文。
     */
    void *context;

    /**
     * 数据观察者的回调。
     */
    Rdb_SubscribeCallback callback;
} Rdb_DataObserver;

/**
 * @brief 为数据库注册观察者。当分布式数据库或本地数据库中的数据发生更改时，将调用回调。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param type 表示在{@link Rdb_SubscribeType}中定义的订阅类型。如果其值为RDB_SUBSCRIBE_TYPE_LOCAL_DETAILS，则在本地数据库中的数据更改时调用回调。
 * @param observer 数据库中更改事件的观察者{@link Rdb_DataObserver}。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @see Rdb_DataObserver.
 * @since 11
 */
int OH_Rdb_Subscribe(OH_Rdb_Store *store, Rdb_SubscribeType type, const Rdb_DataObserver *observer);

/**
 * @brief 从数据库中删除指定类型的指定观察者。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param type 表示在{@link Rdb_SubscribeType}中定义的订阅类型。
 * @param observer 数据库中更改事件的观察者{@link Rdb_DataObserver}。如果这是nullptr，表示删除该类型的所有观察者。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @see Rdb_DataObserver.
 * @since 11
 */
int OH_Rdb_Unsubscribe(OH_Rdb_Store *store, Rdb_SubscribeType type, const Rdb_DataObserver *observer);

/**
 * @brief 表示数据库的同步模式。
 *
 * @since 11
 */
typedef enum Rdb_SyncMode {
    /**
     * @brief 表示数据从修改时间较近的一端同步到修改时间较远的一端。
     *
     */
    RDB_SYNC_MODE_TIME_FIRST,
    /**
     * @brief 表示数据从本地设备同步到云端。
     *
     */
    RDB_SYNC_MODE_NATIVE_FIRST,
    /**
     * @brief 表示数据从云端同步到本地设备。
     *
     */
    RDB_SYNC_MODE_CLOUD_FIRST
} Rdb_SyncMode;

/**
 * @brief 描述数据库表的端云同步过程的统计信息。
 *
 * @since 11
 */
typedef struct Rdb_Statistic {
    /**
     * 表示数据库表中需要端云同步的总行数。
     */
    int total;

    /**
     * 表示数据库表中端云同步成功的行数。
     */
    int successful;

    /**
     * 表示数据库表中端云同步失败的行数。
     */
    int failed;

    /**
     * 表示数据库表中端云同步剩余未执行的行数。
     */
    int remained;
} Rdb_Statistic;

/**
 * @brief 描述数据库表执行端云同步任务上传和下载的统计信息。
 *
 * @since 11
 */
typedef struct Rdb_TableDetails {
    /**
     * 数据库表名。
     */
    const char *table;

    /**
     * 表示数据库表中端云同步上传过程的统计信息。
     */
    Rdb_Statistic upload;

    /**
     * 表示数据库表中端云同步下载过程的统计信息。
     */
    Rdb_Statistic download;
} Rdb_TableDetails;

/**
 * 描述端云同步过程。
 * @since 11
 */
typedef enum Rdb_Progress {
    /**
     * @brief 表示端云同步过程开始。
     *
     */
    RDB_SYNC_BEGIN,

    /**
     * @brief 表示正在端云同步过程中。
     *
     */
    RDB_SYNC_IN_PROGRESS,

    /**
     * @brief 表示端云同步过程已完成。
     *
     */
    RDB_SYNC_FINISH
} Rdb_Progress;

/**
   * 表示端云同步过程的状态。
   * @since 11
   */
typedef enum Rdb_ProgressCode {
    /**
     * @brief 表示端云同步过程成功。
     *
     */
    RDB_SUCCESS,

    /**
     * @brief 表示端云同步过程遇到未知错误。
     *
     */
    RDB_UNKNOWN_ERROR,

    /**
     * @brief 表示端云同步过程遇到网络错误。
     *
     */
    RDB_NETWORK_ERROR,

    /**
     * @brief 表示云端不可用。
     *
     */
    RDB_CLOUD_DISABLED,

    /**
     * @brief 表示有其他设备正在端云同步，本设备无法进行端云同步。
     *
     */
    RDB_LOCKED_BY_OTHERS,

    /**
     * @brief 表示本次端云同步需要同步的条目或大小超出最大值。由云端配置最大值。
     *
     */
    RDB_RECORD_LIMIT_EXCEEDED,

    /**
     * 表示云空间剩余空间小于待同步的资产大小。
     */
    RDB_NO_SPACE_FOR_ASSET
} Rdb_ProgressCode;

/**
 * @brief 描述{@link Rdb_ProgressDetails}的版本。
 *
 * @since 11
 */
#define DISTRIBUTED_PROGRESS_DETAIL_VERSION 1

/**
 * @brief 描述数据库整体执行端云同步任务上传和下载的统计信息。
 *
 * @since 11
 */
typedef struct Rdb_ProgressDetails {
    /**
     * 表示Rdb_ProgressDetails结构体的版本。
     */
    int version;

    /**
     * 表示端云同步过程。
     */
    int schedule;

    /**
     * 表示端云同步过程的状态。
     */
    int code;

    /**
     * 表示端云同步的表的数量。
     */
    int32_t tableLength;
} Rdb_ProgressDetails;

/**
 * @brief 从端云同步任务的统计信息中获取数据库表的统计信息。
 *
 * @param progress 指向{@link Rdb_ProgressDetails}实例的指针。
 * @param version 表示当前{@link Rdb_ProgressDetails}的版本。
 * @return 如果操作成功，会返回一个{@link Rdb_TableDetails}结构体的指针，否则返回NULL。
 * @see Rdb_ProgressDetails
 * @see Rdb_TableDetails
 * @since 11
 */
Rdb_TableDetails *OH_Rdb_GetTableDetails(Rdb_ProgressDetails *progress, int32_t version);

/**
 * @brief 端云同步进度的回调函数。
 *
 * @param context 回调数据的上下文。
 * @param progressDetails 端云同步进度的详细信息。
 * @see Rdb_ProgressDetails.
 * @since 11
 */
typedef void (*Rdb_ProgressCallback)(void *context, Rdb_ProgressDetails *progressDetails);

/**
 * @brief 数据库端云同步的回调函数。
 *
 * @param progressDetails 数据库端云同步的统计信息。
 * @see Rdb_ProgressDetails.
 * @since 11
 */
typedef void (*Rdb_SyncCallback)(Rdb_ProgressDetails *progressDetails);

/**
 * @brief 端云同步进度观察者。
 *
 * @since 11
 */
typedef struct Rdb_ProgressObserver {
    /**
     * 端云同步进度观察者的上下文。
     */
    void *context;

    /**
     * 端云同步进度观察者的回调函数。
     */
    Rdb_ProgressCallback callback;
} Rdb_ProgressObserver;

/**
 * @brief 进行端云同步。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param mode 表示同步过程的类型{@link Rdb_SyncMode}。
 * @param tables 表示要同步的表名。
 * @param count 同步的表的数量，如果传入的值为0，同步数据库的所有表。
 * @param observer 端云同步进度的观察者{@link Rdb_ProgressObserver}。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @see Rdb_ProgressObserver.
 * @since 11
 */
int OH_Rdb_CloudSync(OH_Rdb_Store *store, Rdb_SyncMode mode, const char *tables[], uint32_t count,
    const Rdb_ProgressObserver *observer);

/**
 * @brief 订阅RDB存储的自动同步进度。
 * <br>当收到自动同步进度的通知时，将调用回调。
 *
 * @param store 指向目标{@link OH_Rdb_Store}实例的指针。
 * @param observer 用于自动同步进度的观察者{@link Rdb_ProgressObserver}。表示调用返回自动同步进度的回调。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @see Rdb_ProgressObserver.
 * @since 11
 **/
int OH_Rdb_SubscribeAutoSyncProgress(OH_Rdb_Store *store, const Rdb_ProgressObserver *observer);

/**
 * @brief 取消订阅RDB存储的自动同步进程。
 *
 * @param store 指向目标{@link OH_Rdb_Store}实例的指针。
 * @param observer 表示自动同步进度的观察者{@link Rdb_ProgressObserver}。如果是空指针，则自动同步进程的所有回调都将被取消注册。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store.
 * @see Rdb_ProgressObserver.
 * @since 11
 */
int OH_Rdb_UnsubscribeAutoSyncProgress(OH_Rdb_Store *store, const Rdb_ProgressObserver *observer);

/**
 * @brief 根据指定的条件锁定数据库中的数据，锁定数据不执行端云同步。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param predicates 指向{@link OH_Predicates}实例的指针，指定锁定条件。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store, OH_Predicates, OH_Rdb_ErrCode.
 * @since 12
 */
int OH_Rdb_LockRow(OH_Rdb_Store *store, OH_Predicates *predicates);

/**
 * @brief 根据指定的条件解锁数据库中的数据。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param predicates 指向{@link OH_Predicates}实例的指针，指定解锁条件。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store, OH_Predicates, OH_Rdb_ErrCode.
 * @since 12
 */
int OH_Rdb_UnlockRow(OH_Rdb_Store *store, OH_Predicates *predicates);

/**
 * @brief 根据指定条件查询数据库中锁定的数据。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param predicates 指向{@link OH_Predicates}实例的指针，指定查询条件。
 * @param columnNames 表示要查询的列。如果值为空，则查询应用于所有列。
 * @param length 该参数为输入参数，表示开发者传入的columnNames数组的长度。若length大于columnNames数组的实际长度，则会访问越界。
 * @return 如果查询成功则返回一个指向{@link OH_Cursor}结构体实例的指针，否则返回NULL。
 * @see OH_Rdb_Store, OH_Predicates, OH_Cursor.
 * @since 12
 */
OH_Cursor *OH_Rdb_QueryLockedRow(
    OH_Rdb_Store *store, OH_Predicates *predicates, const char *const *columnNames, int length);

/**
 * @brief 创建一个事务对象。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param options 指向{@link OH_RDB_TransOptions}实例的指针。
 * @param trans 输出参数，表示执行成功时指向{@link OH_Rdb_Transaction}实例的指针。否则返回nullptr。
 *     <br>使用完成后，必须通过{@link OH_RdbTrans_Destroy}接口释放内存。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示成功。
 *     <br>返回RDB_E_ERROR表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示无效参数。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已关闭。
 *     <br>返回RDB_E_DATABASE_BUSY表示数据库无响应。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误: 数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库已损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误: 访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误: 数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误: 数据库内存不足。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误: 磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_CANT_OPEN表示SQLite错误: 无法打开数据库文件。
 * @see OH_RdbTrans_Destroy.
 * @since 18
 */
int OH_Rdb_CreateTransaction(OH_Rdb_Store *store, const OH_RDB_TransOptions *options, OH_Rdb_Transaction **trans);

/**
 * @brief 将数据库文件附加到当前连接的数据库。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param config 指向与此RDB存储相关的数据库配置{@link OH_Rdb_ConfigV2}的指针。
 * @param attachName 表示数据库的别名。
 * @param waitTime 表示附加数据库的最大允许时间，范围为1到300，单位为秒。
 * @param attachedNumber 表示已附加的数据库数量，作为输出参数。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示执行成功。
 *     <br>返回RDB_E_ERROR 表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示输入参数无效。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已关闭。
 *     <br>返回RDB_E_NOT_SUPPORTED表示不支持的操作。
 *     <br>返回RDB_E_DATABASE_BUSY表示数据库无响应。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库已损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误：违反约束导致操作中止。
 * @since 20
 */
int OH_Rdb_Attach(OH_Rdb_Store *store, const OH_Rdb_ConfigV2 *config, const char *attachName, int64_t waitTime,
    size_t *attachedNumber);

/**
 * @brief 从当前数据库中分离指定的数据库。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param attachName 表示数据库的别名。
 * @param waitTime 表示分离数据库的最大允许时间，范围为1到300，单位为秒。
 * @param attachedNumber 表示已附加的数据库数量，作为输出参数。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示执行成功。
 *     <br>返回RDB_E_ERROR 表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示输入参数无效。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已关闭。
 *     <br>返回RDB_E_NOT_SUPPORTED表示不支持的操作。
 *     <br>返回RDB_E_DATABASE_BUSY表示数据库无响应。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库已损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误：违反约束导致操作中止。
 * @see OH_Rdb_Store, OH_Rdb_ErrCode.
 * @since 20
 */
int OH_Rdb_Detach(OH_Rdb_Store *store, const char *attachName, int64_t waitTime, size_t *attachedNumber);

/**
 * @brief 支持不同语言的排序规则。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param locale 与语言相关的区域设置，例如 zh。该值符合 ISO 639 标准。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示执行成功。
 *     <br>返回RDB_ERR表示函数执行异常。
 *     <br>返回RDB_E_INVALID_ARGS表示输入参数无效。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已关闭。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误：数据库内存不足。
 * @see OH_Rdb_Store.
 * @since 20
 */
int OH_Rdb_SetLocale(OH_Rdb_Store *store, const char *locale);

/**
 * @brief 数据库异常处理的回调函数。
 *
 * @param context 表示数据异常处理的上下文，生命周期由业务自身管理。
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置，不可在回调函数外部使用。
 * @param store 指向{@link OH_Rdb_Store}实例的指针，该指针由系统产生，回调函数结束后即刻释放，不可在回调函数外部使用。
 * @since 22
 */
typedef void (*Rdb_CorruptedHandler)(void *context, OH_Rdb_ConfigV2 *config, OH_Rdb_Store *store);

/**
 * @brief 注册数据库异常处理。当数据库发生异常时，将调用异常处理的回调函数。
 * <br>异常处理逻辑为用户自定义，回调时触发的业务需要用户自行保障。
 * <br>每个路径只允许注册一次。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置。
 * @param context 表示数据异常处理的上下文。
 * @param handler 数据库异常处理的回调函数。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。
 *     <br>返回RDB_E_SUB_LIMIT_REACHED表示注册数量超过限制。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_RegisterCorruptedHandler.
 * @since 22
 */
int OH_Rdb_RegisterCorruptedHandler(const OH_Rdb_ConfigV2 *config, void *context, const Rdb_CorruptedHandler handler);

/**
 * @brief 取消注册的数据库异常处理的回调函数。
 * <br>handler和context必须要和订阅时保持一致，否则取消失败。
 *
 * @param config 指向{@link OH_Rdb_ConfigV2}对象的指针，即与此RDB存储相关的数据库配置。
 * @param context 表示数据异常处理的上下文。
 * @param handler 数据库异常处理的回调函数。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_UnregisterCorruptedHandler.
 * @since 22
 */
int OH_Rdb_UnregisterCorruptedHandler(const OH_Rdb_ConfigV2 *config, void *context, const Rdb_CorruptedHandler handler);

/**
 * @brief 更改加密数据库密钥。
 * <br>不支持对非WAL模式的数据库进行密钥更新。
 * <br>手动更新时需要独占访问数据库，此时若存在任何未释放的结果集、事务或其他进程打开的数据库均会导致更新失败。
 * <br>支持加密数据库的参数更新，以及加密数据库与非加密数据库之间的相互转换。
 * <br>数据库越大，执行更新所需的时间越长。
 * <br>加密参数变更需谨慎，调用OH_Rdb_CreateOrOpen时需要传入正确的加密参数，否则可能打开数据库失败。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param param 指向{@link OH_Rdb_CryptoParam}实例的指针。
 * @return 返回执行结果。
 *     <br>返回RDB_OK表示执行成功。
 *     <br>返回RDB_E_ERROR 表示数据库常见错误。
 *     <br>返回RDB_E_INVALID_ARGS表示输入参数无效。
 *     <br>返回RDB_E_ALREADY_CLOSED表示数据库已关闭。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库已损坏。
 *     <br>返回RDB_E_SQLITE_PERM表示SQLite错误：访问权限被拒绝。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_NOMEM表示SQLite错误：数据库内存不足。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误：磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误：数据库已满。
 * @since 22
 */
int OH_Rdb_RekeyEx(OH_Rdb_Store *store, OH_Rdb_CryptoParam *param);

/**
 * @brief 将批量数据插入目标表，并将变更信息输出到上下文中。
 * <br>一次最多可以插入32766个参数。如果参数数量超过上限，则返回错误代码RDB_E_INVALID_ARGS。
 * <br>参数数量计算方式为插入数据条数乘以插入数据时所有字段的并集大小。
 * <br>例如：插入数据的所有字段的并集大小为10则最多可以插入3276条数据（3276*10=32760）。
 * <br>请确保在调用接口时遵守此限制，以避免因参数数量过多而导致错误。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param table 要插入的目标表名。
 * @param rows 要插入到表中的行数据。
 * @param resolution 发生冲突时的解决策略Rdb_ConflictResolution，不建议使用RDB_CONFLICT_FAIL，因为失败时会抛异常，
 *     <br>无法正常获取实际的变更数据。
 * @param context 指向{@link OH_RDB_ReturningContext}实例的指针。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL文件大小超过默认限制。
 *     <br>返回RDB_E_NOT_SUPPORTED表示不支持的操作。
 *     <br>返回RDB_E_DATABASE_BUSY表示数据库忙。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误：发生某种磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误：由于违反约束而中止。
 *     <br>返回RDB_E_SQLITE_ERROR表示SQLite错误。可能原因：语法错误，例如表或列不存在。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store, OH_Data_VBuckets, OH_Rdb_ErrCode, OH_RDB_ReturningContext.
 * @since 23
 */
int OH_Rdb_BatchInsertWithReturning(OH_Rdb_Store *store, const char *table, const OH_Data_VBuckets *rows,
    Rdb_ConflictResolution resolution, OH_RDB_ReturningContext *context);

/**
 * @brief 根据指定条件更新数据库中的数据并输出更改信息到上下文。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param row 要更新到表中的行数据。
 * @param predicates 指向{@link OH_Predicates}实例的指针。
 * @param resolution 发生冲突时的解决策略Rdb_ConflictResolution，不建议使用RDB_CONFLICT_FAIL，因为失败时会抛异常，
 *     <br>无法正常获取实际的变更数据。
 * @param context 指向{@link OH_RDB_ReturningContext}实例的指针。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL文件大小超过默认限制。
 *     <br>返回RDB_E_NOT_SUPPORTED表示不支持的操作。
 *     <br>返回RDB_E_EMPTY_VALUES_BUCKET表示值桶为空。
 *     <br>返回RDB_E_DATABASE_BUSY表示数据库忙。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误：发生某种磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_CONSTRAINT表示SQLite错误：由于违反约束而中止。
 *     <br>返回RDB_E_SQLITE_ERROR表示SQLite错误。可能原因：语法错误，例如表或列不存在。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store, OH_Data_VBuckets, OH_Predicates, OH_Rdb_ErrCode, OH_RDB_ReturningContext.
 * @since 23
 */
int OH_Rdb_UpdateWithReturning(OH_Rdb_Store *store, OH_VBucket *row, OH_Predicates *predicates,
    Rdb_ConflictResolution resolution, OH_RDB_ReturningContext *context);

/**
 * @brief 根据指定条件从数据库中删除数据并输出更改信息到上下文。
 *
 * @param store 指向{@link OH_Rdb_Store}实例的指针。
 * @param predicates 指向{@link OH_Predicates}实例的指针。
 * @param context 指向{@link OH_RDB_ReturningContext}实例的指针。
 * @return 返回操作是否成功，出错时返回对应的错误码。
 *     <br>RDB_OK 表示成功。
 *     <br>RDB_E_INVALID_ARGS 表示无效参数。
 *     <br>返回RDB_E_WAL_SIZE_OVER_LIMIT表示WAL文件大小超过默认限制。
 *     <br>返回RDB_E_NOT_SUPPORTED表示不支持的操作。
 *     <br>返回RDB_E_DATABASE_BUSY表示数据库忙。
 *     <br>返回RDB_E_SQLITE_FULL表示SQLite错误：数据库已满。
 *     <br>返回RDB_E_SQLITE_CORRUPT表示数据库损坏。
 *     <br>返回RDB_E_SQLITE_BUSY表示SQLite错误：数据库文件被锁定。
 *     <br>返回RDB_E_SQLITE_LOCKED表示SQLite错误：数据库中的表被锁定。
 *     <br>返回RDB_E_SQLITE_READONLY表示SQLite错误：尝试写入只读数据库。
 *     <br>返回RDB_E_SQLITE_IOERR表示SQLite错误：发生某种磁盘I/O错误。
 *     <br>返回RDB_E_SQLITE_TOO_BIG表示SQLite错误：TEXT或BLOB超出大小限制。
 *     <br>返回RDB_E_SQLITE_MISMATCH表示SQLite错误：数据类型不匹配。
 *     <br>返回RDB_E_SQLITE_ERROR表示SQLite错误。可能原因：语法错误，例如表或列不存在。详细信息请参阅{@link OH_Rdb_ErrCode}。
 * @see OH_Rdb_Store, OH_Predicates, OH_Rdb_ErrCode, OH_RDB_ReturningContext.
 * @since 23
 */
int OH_Rdb_DeleteWithReturning(OH_Rdb_Store *store, OH_Predicates *predicates, OH_RDB_ReturningContext *context);
#ifdef __cplusplus
};
#endif

/** @} */

#endif // RELATIONAL_STORE_ZH_CN_H
