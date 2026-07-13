/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup AssetApi
 * @{
 *
 * @brief Provides APIs for storing and managing short sensitive data of users, including adding, deleting, updating,
 * and querying the data.
 * The short sensitive data refers to sensitive data shorter than 1024 bytes, including the user passwords
 * (accounts/passwords), token data (application credentials), and critical data in plaintext (bank card numbers).
 *
 * @since 11
 */

/**
 * @file asset_api.h
 *
 * @brief Declares the APIs for accessing assets.
 *
 * @library libasset_ndk.z.so
 * @kit AssetStoreKit
 * @syscap SystemCapability.Security.Asset
 * @since 11
 */
#ifndef ASSET_API_H
#define ASSET_API_H
#include <stdint.h>
#include <stdlib.h>
#include "asset_type.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 新增一条关键资产。
 *
 * @param attributes 待新增关键资产的属性集合。
 * @param attrCnt 待新增关键资产的属性数量。
 * @return {@link ASSET_SUCCESS} 0 - 操作成功。
 *     {@link ASSET_PERMISSION_DENIED} 201 - 调用者没有权限。
 *     {@link ASSET_INVALID_ARGUMENT} 401 - 参数错误。可能原因:
 *         1. 必选参数未指定。
 *         2. 参数类型错误。
 *         3. 参数校验失败。
 *     {@link ASSET_SERVICE_UNAVAILABLE} 24000001 - 关键资产服务不可用。
 *     {@link ASSET_DUPLICATED} 24000003 - 关键资产已存在。
 *     {@link ASSET_STATUS_MISMATCH} 24000005 - 锁屏状态不匹配。
 *     {@link ASSET_OUT_OF_MEMORY} 24000006 - 系统内存不足。
 *     {@link ASSET_DATA_CORRUPTED} 24000007 - 关键资产损坏。
 *     {@link ASSET_DATABASE_ERROR} 24000008 - 数据库操作失败。
 *     {@link ASSET_CRYPTO_ERROR} 24000009 - 算法库操作失败。
 *     {@link ASSET_IPC_ERROR} 24000010 - 进程通信错误。
 *     {@link ASSET_BMS_ERROR} 24000011 - 包管理服务异常。
 *     {@link ASSET_ACCOUNT_ERROR} 24000012 - 账号系统服务异常。
 *     {@link ASSET_ACCESS_TOKEN_ERROR} 24000013 - 访问控制服务异常。
 *     {@link ASSET_FILE_OPERATION_ERROR} 24000014 - 文件操作失败。
 *     {@link ASSET_GET_SYSTEM_TIME_ERROR} 24000015 - 获取系统时间失败。
 * @since 11
 */
int32_t OH_Asset_Add(const Asset_Attr *attributes, uint32_t attrCnt);

/**
 * @brief 删除符合条件的一条或多条关键资产。
 *
 * @param query 待删除关键资产的搜索条件。
 * @param queryCnt 待删除关键资产搜索条件的个数。
 * @return {@link ASSET_SUCCESS} 0 - 操作成功。
 *     {@link ASSET_INVALID_ARGUMENT} 401 - 参数错误。可能原因:
 *         1. 参数类型错误。
 *         2. 参数校验失败。
 *     {@link ASSET_SERVICE_UNAVAILABLE} 24000001 - 关键资产服务不可用。
 *     {@link ASSET_NOT_FOUND} 24000002 - 未找到关键资产。
 *     {@link ASSET_OUT_OF_MEMORY} 24000006 - 系统内存不足。
 *     {@link ASSET_DATA_CORRUPTED} 24000007 - 关键资产损坏。
 *     {@link ASSET_DATABASE_ERROR} 24000008 - 数据库操作失败。
 *     {@link ASSET_IPC_ERROR} 24000010 - 进程通信错误。
 *     {@link ASSET_BMS_ERROR} 24000011 - 包管理服务异常。
 *     {@link ASSET_ACCOUNT_ERROR} 24000012 - 账号系统服务异常。
 *     {@link ASSET_ACCESS_TOKEN_ERROR} 24000013 - 访问控制服务异常。
 *     {@link ASSET_GET_SYSTEM_TIME_ERROR} 24000015 - 获取系统时间失败。
 * @since 11
 */
int32_t OH_Asset_Remove(const Asset_Attr *query, uint32_t queryCnt);

/**
 * @brief 更新符合条件的一条关键资产。
 *
 * @param query 待更新关键资产的搜索条件。
 * @param queryCnt 待更新关键资产搜索条件的个数。
 * @param attributesToUpdate 待更新关键资产的属性集合。
 * @param updateCnt 待更新关键资产的属性数量。
 * @return {@link ASSET_SUCCESS} 0 - 操作成功。
 *     {@link ASSET_INVALID_ARGUMENT} 401 - 参数错误。可能原因:
 *         1. 必选参数未指定。
 *         2. 参数类型错误。
 *         3. 参数校验失败。
 *     {@link ASSET_SERVICE_UNAVAILABLE} 24000001 - 关键资产服务不可用。
 *     {@link ASSET_NOT_FOUND} 24000002 - 未找到关键资产。
 *     {@link ASSET_STATUS_MISMATCH} 24000005 - 锁屏状态不匹配。
 *     {@link ASSET_OUT_OF_MEMORY} 24000006 - 系统内存不足。
 *     {@link ASSET_DATA_CORRUPTED} 24000007 - 关键资产损坏。
 *     {@link ASSET_DATABASE_ERROR} 24000008 - 数据库操作失败。
 *     {@link ASSET_CRYPTO_ERROR} 24000009 - 算法库操作失败。
 *     {@link ASSET_IPC_ERROR} 24000010 - 进程通信错误。
 *     {@link ASSET_BMS_ERROR} 24000011 - 包管理服务异常。
 *     {@link ASSET_ACCOUNT_ERROR} 24000012 - 账号系统服务异常。
 *     {@link ASSET_ACCESS_TOKEN_ERROR} 24000013 - 访问控制服务异常。
 *     {@link ASSET_GET_SYSTEM_TIME_ERROR} 24000015 - 获取系统时间失败。
 * @since 11
 */
int32_t OH_Asset_Update(const Asset_Attr *query, uint32_t queryCnt,
    const Asset_Attr *attributesToUpdate, uint32_t updateCnt);

/**
 * @brief 查询的预处理，用于需要用户认证的关键资产。
 *
 * @param query 关键资产的查询条件。
 * @param queryCnt 关键资产查询条件的个数。
 * @param challenge 挑战值，在后续调用{@link OH_Asset_Query}时使用。
 * @return {@link ASSET_SUCCESS} 0 - 操作成功。
 *     {@link ASSET_INVALID_ARGUMENT} 401 - 参数错误。可能原因:
 *         1. 参数类型错误。
 *         2. 参数校验失败。
 *     {@link ASSET_SERVICE_UNAVAILABLE} 24000001 - 关键资产服务不可用。
 *     {@link ASSET_NOT_FOUND} 24000002 - 未找到关键资产。
 *     {@link ASSET_STATUS_MISMATCH} 24000005 - 锁屏状态不匹配。
 *     {@link ASSET_OUT_OF_MEMORY} 24000006 - 系统内存不足。
 *     {@link ASSET_DATA_CORRUPTED} 24000007 - 关键资产损坏。
 *     {@link ASSET_DATABASE_ERROR} 24000008 - 数据库操作失败。
 *     {@link ASSET_CRYPTO_ERROR} 24000009 - 算法库操作失败。
 *     {@link ASSET_IPC_ERROR} 24000010 - 进程通信错误。
 *     {@link ASSET_BMS_ERROR} 24000011 - 包管理服务异常。
 *     {@link ASSET_ACCOUNT_ERROR} 24000012 - 账号系统服务异常。
 *     {@link ASSET_ACCESS_TOKEN_ERROR} 24000013 - 访问控制服务异常。
 *     {@link ASSET_LIMIT_EXCEEDED} 24000016 - 缓存数量超限。
 *     {@link ASSET_UNSUPPORTED} 24000017 - 该子功能不支持。
 * @since 11
 */
int32_t OH_Asset_PreQuery(const Asset_Attr *query, uint32_t queryCnt, Asset_Blob *challenge);

/**
 * @brief 查询一条或多条符合条件的关键资产。
 *
 * @param query 关键资产的查询条件。
 * @param queryCnt 关键资产查询条件的个数。
 * @param resultSet 查询结果列表。
 * @return {@link ASSET_SUCCESS} 0 - 操作成功。
 *     {@link ASSET_INVALID_ARGUMENT} 401 - 参数错误。可能原因:
 *         1. 参数类型错误。
 *         2. 参数校验失败。
 *     {@link ASSET_SERVICE_UNAVAILABLE} 24000001 - 关键资产服务不可用。
 *     {@link ASSET_NOT_FOUND} 24000002 - 未找到关键资产。
 *     {@link ASSET_ACCESS_DENIED} 24000004 - 访问被拒绝。
 *     {@link ASSET_STATUS_MISMATCH} 24000005 - 锁屏状态不匹配。
 *     {@link ASSET_OUT_OF_MEMORY} 24000006 - 系统内存不足。
 *     {@link ASSET_DATA_CORRUPTED} 24000007 - 关键资产损坏。
 *     {@link ASSET_DATABASE_ERROR} 24000008 - 数据库操作失败。
 *     {@link ASSET_CRYPTO_ERROR} 24000009 - 算法库操作失败。
 *     {@link ASSET_IPC_ERROR} 24000010 - 进程通信错误。
 *     {@link ASSET_BMS_ERROR} 24000011 - 包管理服务异常。
 *     {@link ASSET_ACCOUNT_ERROR} 24000012 - 账号系统服务异常。
 *     {@link ASSET_ACCESS_TOKEN_ERROR} 24000013 - 访问控制服务异常。
 *     {@link ASSET_UNSUPPORTED} 24000017 - 该子功能不支持。
 * @since 11
 */
int32_t OH_Asset_Query(const Asset_Attr *query, uint32_t queryCnt, Asset_ResultSet *resultSet);

/**
 * @brief 查询的后置处理，用于需要用户认证的关键资产。
 *
 * @param handle 待处理的查询句柄，当前包含{@link OH_Asset_PreQuery}执行成功返回的挑战值。
 * @param handleCnt 句柄属性集合中元素的个数。
 * @return {@link ASSET_SUCCESS} 0 - 操作成功。
 *     {@link ASSET_INVALID_ARGUMENT} 401 - 参数错误。可能原因:
 *         1. 必选参数未指定。
 *         2. 参数类型错误。
 *         3. 参数校验失败。
 *     {@link ASSET_SERVICE_UNAVAILABLE} 24000001 - 关键资产服务不可用。
 *     {@link ASSET_OUT_OF_MEMORY} 24000006 - 系统内存不足。
 *     {@link ASSET_IPC_ERROR} 24000010 - 进程通信错误。
 *     {@link ASSET_BMS_ERROR} 24000011 - 包管理服务异常。
 *     {@link ASSET_ACCOUNT_ERROR} 24000012 - 账号系统服务异常。
 *     {@link ASSET_ACCESS_TOKEN_ERROR} 24000013 - 访问控制服务异常。
 * @since 11
 */
int32_t OH_Asset_PostQuery(const Asset_Attr *handle, uint32_t handleCnt);

/**
 * @brief 查询关键资产的同步结果。
 *
 * @param query 关键资产同步结果的查询条件。
 * @param queryCnt 关键资产同步结果的查询条件个数。
 * @param syncResult 查询到的关键资产同步结果。
 * @return {@link ASSET_SUCCESS} 0 - 操作成功。
 *     {@link ASSET_SERVICE_UNAVAILABLE} 24000001 - 关键资产服务不可用。
 *     {@link ASSET_OUT_OF_MEMORY} 24000006 - 系统内存不足。
 *     {@link ASSET_IPC_ERROR} 24000010 - 进程通信错误。
 *     {@link ASSET_BMS_ERROR} 24000011 - 包管理服务异常。
 *     {@link ASSET_ACCOUNT_ERROR} 24000012 - 账号系统服务异常。
 *     {@link ASSET_ACCESS_TOKEN_ERROR} 24000013 - 访问控制服务异常。
 *     {@link ASSET_FILE_OPERATION_ERROR} 24000014 - 文件操作失败。
 *     {@link ASSET_PARAM_VERIFICATION_FAILED} 24000018 - 参数校验失败。
 * @since 20
 */
int32_t OH_Asset_QuerySyncResult(const Asset_Attr *query, uint32_t queryCnt, Asset_SyncResult *syncResult);

/**
 * @brief 解析查询结果，并获取指定的属性值。
 *
 * @param result 从{@link OH_Asset_Query}中获取的查询结果。
 * @param tag 待获取的属性标签。
 * @return 如果操作成功，则以<b>Asset_Attr</b>的形式返回属性，该属性不需要业务进行释放；否则返回<b>NULL</b>。
 * @since 11
 */
Asset_Attr *OH_Asset_ParseAttr(const Asset_Result *result, Asset_Tag tag);

/**
 * @brief 释放挑战值所占用的内存。
 *
 * @param blob 从{@link OH_Asset_PreQuery}获取的挑战值。
 * @since 11
 */
void OH_Asset_FreeBlob(Asset_Blob *blob);

/**
 * @brief 释放查询结果所占用的内存。
 *
 * @param resultSet 从{@link OH_Asset_Query}得到的查询结果列表。
 * @since 11
 */
void OH_Asset_FreeResultSet(Asset_ResultSet *resultSet);
#ifdef __cplusplus
}
#endif

/** @} */
#endif // ASSET_API_H