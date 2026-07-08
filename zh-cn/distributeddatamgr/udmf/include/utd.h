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
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 * @since 12
 */
/**
 * @file utd.h
 *
 * @brief 提供标准化数据类型描述相关接口和数据结构。当参数类型为char*时，字符串必须以空字符（'\0'）结尾。
 * 
 * @kit ArkData
 * @library libudmf.so
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 * @since 12
 */

#ifndef UTD_H
#define UTD_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 统一数据类型描述符。
 * 
 * @since 12
 */
typedef struct OH_Utd OH_Utd;

/**
 * @brief 创建统一数据类型{@link OH_Utd}指针及实例对象。
 * 
 * @param typeId 表示统一数据类型ID。
 * @return 执行成功则返回一个指向统一数据类型{@link OH_Utd}实例对象的指针，否则返回nullptr。
 * 当不再需要使用指针时，请使用{@link OH_Utd_Destroy}销毁实例对象，否则会导致内存泄漏。
 * @see OH_Utd.
 * @since 12
 */
OH_Utd* OH_Utd_Create(const char* typeId);

/**
 * @brief 销毁统一数据类型{@link OH_Utd}指针指向的实例对象。销毁后指针失效，不可再使用，否则会导致未定义行为。
 * 
 * @param pThis 表示指向统一数据类型{@link OH_Utd}实例的指针。
 * @see OH_Utd.
 * @since 12
 */
void OH_Utd_Destroy(OH_Utd* pThis);

/**
 * @brief 获取统一数据类型{@link OH_Utd}中的类型ID。
 * 
 * @param pThis 表示一个指向统一数据类型{@link OH_Utd}对象的指针。
 * @return 当入参有效时返回指向类型ID的字符串指针，否则返回nullptr。
 * @see OH_Utd.
 * @since 12
 */
const char* OH_Utd_GetTypeId(OH_Utd* pThis);

/**
 * @brief 获取统一数据类型{@link OH_Utd}中的描述信息。
 * 
 * @param pThis 表示一个指向统一数据类型{@link OH_Utd}对象的指针。
 * @return 当入参有效时返回指向描述信息的字符串指针，否则返回nullptr。
 * @see OH_Utd.
 * @since 12
 */
const char* OH_Utd_GetDescription(OH_Utd* pThis);

/**
 * @brief 获取统一数据类型{@link OH_Utd}中的URL信息。
 * 
 * @param pThis 表示一个指向统一数据类型{@link OH_Utd}对象的指针。
 * @return 当入参有效时返回指向URL信息的字符串指针，否则返回nullptr。
 * @see OH_Utd.
 * @since 12
 */
const char* OH_Utd_GetReferenceUrl(OH_Utd* pThis);

/**
 * @brief 获取统一数据类型{@link OH_Utd}中的默认图标文件路径。
 * 
 * @param pThis 表示一个指向统一数据类型{@link OH_Utd}对象的指针。
 * @return 当入参有效时返回指向默认图标文件路径的字符串指针，否则返回nullptr。
 * @see OH_Utd.
 * @since 12
 */
const char* OH_Utd_GetIconFile(OH_Utd* pThis);

/**
 * @brief 获取统一数据类型{@link OH_Utd}中的归属关系结果集。
 * 
 * @param pThis 表示一个指向统一数据类型{@link OH_Utd}对象的指针。
 * @param count 输出参数，结果集中的类型数量会写入该变量。
 * @return 当入参有效时返回归属关系结果集的字符串指针列表，否则返回nullptr。
 * 当不再需要使用指针时，请及时使用{@link OH_Utd_DestroyStringList}销毁对应的实例，否则会导致内存泄漏。
 * @see OH_Utd.
 * @since 12
 */
const char** OH_Utd_GetBelongingToTypes(OH_Utd* pThis, unsigned int* count);

/**
 * @brief 获取统一数据类型{@link OH_Utd}所关联的文件名后缀结果集。
 * 
 * @param pThis 表示一个指向统一数据类型{@link OH_Utd}对象的指针。
 * @param count 该参数是输出参数，结果集中的文件后缀名数量会写入该变量。
 * @return 当入参有效时返回文件名后缀结果集的字符串指针列表，否则返回nullptr。
 * 当不再需要使用指针时，请及时使用{@link OH_Utd_DestroyStringList}销毁对应的实例，否则会导致内存泄漏。
 * @see OH_Utd.
 * @since 12
 */
const char** OH_Utd_GetFilenameExtensions(OH_Utd* pThis, unsigned int* count);

/**
 * @brief 获取{@link OH_Utd}所关联的MIME类型结果集。
 * 
 * @param pThis 表示一个指向统一数据类型{@link OH_Utd}对象的指针。
 * @param count 该参数是输出参数，结果集中的MIME类型数量会写入该变量。
 * @return 当入参有效时返回MIME类型结果集的字符串指针列表，否则返回nullptr。
 * 当不再需要使用指针时，请及时使用{@link OH_Utd_DestroyStringList}销毁对应的实例，否则会导致内存泄漏。
 * @see OH_Utd.
 * @since 12
 */
const char** OH_Utd_GetMimeTypes(OH_Utd* pThis, unsigned int* count);

/**
 * @brief 通过文件名后缀获取关联的统一标准数据描述类型结果集。
 * 
 * @param extension 表示文件名后缀。
 * @param count 该参数是输出参数，结果集中的类型数量会写入该变量。
 * @return 当入参有效时返回标准数据描述类型结果集字符串列表，否则返回nullptr。
 * 当不再需要使用指针时，请及时使用{@link OH_Utd_DestroyStringList}销毁对应的实例，否则会导致内存泄漏。
 * @since 12
 */
const char** OH_Utd_GetTypesByFilenameExtension(const char* extension, unsigned int* count);

/**
 * @brief 通过MIME类型获取所关联的标准数据类型结果集。
 * 
 * @param mimeType 表示MIME类型字符串。
 * @param count 该参数是输出参数，结果集中的类型数量会写入该变量。
 * @return 当入参有效时返回标准数据描述类型结果集字符串列表，否则返回nullptr。
 * 当不再需要使用指针时，请及时使用{@link OH_Utd_DestroyStringList}销毁对应的实例，否则会导致内存泄漏。
 * @since 12
 */
const char** OH_Utd_GetTypesByMimeType(const char* mimeType, unsigned int* count);

/**
 * @brief 判断两个标准化数据描述类型是否存在归属关系。
 * 
 * @param srcTypeId 表示原标准化数据类型。
 * @param destTypeId 表示目标标准化数据类型。
 * @return false表示原类型不属于目标类型，true表示原类型属于目标类型。
 * @since 12
 */
bool OH_Utd_BelongsTo(const char* srcTypeId, const char* destTypeId);

/**
 * @brief 判断原标准化数据类型是否是目标标准化数据类型的低层级类型。例如TYPE_SCRIPT为SOURCE_CODE的低层级类型，TYPE_SCRIPT和SOURCE_CODE为PLAIN_TEXT的低层级类型。
 * 
 * @param srcTypeId 表示原标准化数据类型。
 * @param destTypeId 表示目标标准化数据类型。
 * @return false表示原类型不低于目标类型；true表示原类型低于目标类型。
 * @since 12
 */
bool OH_Utd_IsLower(const char* srcTypeId, const char* destTypeId);

/**
 * @brief 判断原标准化数据类型是否是目标标准化数据类型的高层级类型。例如SOURCE_CODE为TYPE_SCRIPT的高层级类型，PLAIN_TEXT为SOURCE_CODE和TYPE_SCRIPT的高层级类型。
 * 
 * @param srcTypeId 表示原标准化数据类型。
 * @param destTypeId 表示目标标准化数据类型。
 * @return false表示原类型不高于目标类型，true表示原类型高于目标类型。
 * @since 12
 */
bool OH_Utd_IsHigher(const char* srcTypeId, const char* destTypeId);

/**
 * @brief 判断两个标准化数据描述类型是否相等。
 * 
 * @param utd1 表示一个指向标准化数据描述类型{@link OH_Utd}对象的指针。
 * @param utd2 表示一个指向标准化数据描述类型{@link OH_Utd}对象的指针。
 * @return false表示两种类型不相等，true表示两种类型相等。
 * @since 12
 */
bool OH_Utd_Equals(OH_Utd* utd1, OH_Utd* utd2);

/**
 * @brief 销毁标准数据描述类型结果集字符串列表。销毁后列表指针失效，不可再使用，否则会导致未定义行为。
 * 
 * @param list 表示字符串列表指针。
 * @param count 表示字符串列表list参数中的列表长度。
 * @since 12
 */
void OH_Utd_DestroyStringList(const char** list, unsigned int count);

#ifdef __cplusplus
};
#endif

/** @} */
#endif