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
 * @addtogroup Preferences
 * @{
 *
 * @brief 用户首选项为应用提供Key-Value键值型的数据处理能力，支持应用持久化轻量级数据，并对其修改和查询。
 * 数据存储采用键值对形式，键为字符串类型，值可为数字、字符串、布尔类型、数组、Uint8Array、object或bigint。
 *
 * @since 13
 */

/**
 * @file oh_preferences.h
 *
 * @brief 提供访问Preferences对象的接口与数据结构。
 * 
 * @kit ArkData
 * @library libohpreferences.so
 * @syscap SystemCapability.DistributedDataManager.Preferences.Core
 *
 * @since 13
 */

#ifndef OH_PREFERENCES_H
#define OH_PREFERENCES_H

#include <stdbool.h>
#include <stdint.h>

#include "oh_preferences_value.h"
#include "oh_preferences_option.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义Preferences对象类型。
 * 
 * @since 13
 */
typedef struct OH_Preferences OH_Preferences;

/**
 * @brief 定义数据变更触发的回调函数类型。
 * 
 * @param context 应用上下文的指针。
 * @param pairs 发生变更的键值对（KV）数据的指针。
 * @param count 发生变更的键值对（KV）数据的数量。
 * @see OH_PreferencesPair.
 * @since 13
 */
typedef void (*OH_PreferencesDataObserver)(void *context, const OH_PreferencesPair *pairs, uint32_t count);

/**
 * @brief 打开一个Preferences实例对象并创建指向它的指针。
 * <br>当不再需要使用指针时，请使用{@link OH_Preferences_Close}关闭实例对象。
 * 
 * @param option 指向Preferences配置选项{@link OH_PreferencesOption}的指针。
 * @param errCode 该参数作为出参使用，表示指向返回错误码的指针，详见{@link OH_Preferences_ErrCode}。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_NOT_SUPPORTED，表示系统能力不支持。
 *     <br>若错误码为PREFERENCES_ERROR_DELETE_FILE，表示删除文件失败。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @return 当操作成功时，返回指向打开的Preferences对象{@link OH_Preferences}实例对象的指针，失败返回空指针。
 * @see OH_Preferences OH_PreferencesOption.
 * @since 13
 */
OH_Preferences *OH_Preferences_Open(OH_PreferencesOption *option, int *errCode);

/**
 * @brief 关闭一个Preferences实例对象。
 * 
 * @param preference 指向需要关闭的Preferences{@link OH_Preferences}实例对象的指针。
 * @return 返回执行的错误码，详见{@link OH_Preferences_ErrCode}。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_Close(OH_Preferences *preference);

/**
 * @brief 删除指定的Preferences对象。
 * 
 * @param option 指向Preferences配置选项{@link OH_PreferencesOption}的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_NOT_SUPPORTED，表示系统能力不支持。
 *     <br>若错误码为PREFERENCES_ERROR_DELETE_FILE，表示删除文件失败。
 * @see OH_Preferences.
 * @since 23
 */
int OH_Preferences_DeletePreferences(OH_PreferencesOption *option);

/**
 * @brief 获取Preferences实例对象中Key对应的整型值。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例对象的指针。
 * @param key 需要获取的Key的指针。
 * @param value 该参数作为出参使用，表示指向获取到的整型值的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 *     <br>若错误码为PREFERENCES_ERROR_KEY_NOT_FOUND，表示查询的Key不存在。
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_GetInt(OH_Preferences *preference, const char *key, int *value);

/**
 * @brief 获取Preferences实例对象中Key对应的布尔值。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例对象的指针。
 * @param key 需要获取的Key的指针。
 * @param value 该参数作为出参使用，表示指向获取到的布尔值的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 *     <br>若错误码为PREFERENCES_ERROR_KEY_NOT_FOUND，表示查询的Key不存在。
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_GetBool(OH_Preferences *preference, const char *key, bool *value);

/**
 * @brief 获取Preferences实例对象中Key对应的字符串。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例对象的指针。
 * @param key 需要获取的Key的指针。
 * @param value 该参数作为出参使用，表示指向获取到的字符串的二级指针，使用完毕后需要调用释放函数{@link OH_Preferences_FreeString}释放内存。
 * @param valueLen 该参数作为出参使用，表示获取到的字符串长度的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 *     <br>若错误码为PREFERENCES_ERROR_KEY_NOT_FOUND，表示查询的Key不存在。
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_GetString(OH_Preferences *preference, const char *key, char **value, uint32_t *valueLen);

/**
 * @brief 释放从Preferences实例对象中获取的字符串。
 * 
 * @param string 需要释放的字符串指针。
 * @see OH_Preferences.
 * @since 13
 */
void OH_Preferences_FreeString(char *string);

/**
 * @brief 根据Key设置Preferences实例对象中的整型值。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例对象的指针。
 * @param key 指向需要设置的Key的指针。
 * @param value 需要设置的整型值。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_SetInt(OH_Preferences *preference, const char *key, int value);

/**
 * @brief 根据Key设置Preferences实例对象中的布尔值。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例对象的指针。
 * @param key 指向需要设置的Key的指针。
 * @param value 需要设置的布尔值。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_SetBool(OH_Preferences *preference, const char *key, bool value);

/**
 * @brief 根据Key设置Preferences实例对象中的字符串。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例对象的指针。
 * @param key 指向需要设置的Key的指针。
 * @param value 指向需要设置的字符串指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_SetString(OH_Preferences *preference, const char *key, const char *value);

/**
 * @brief 在Preferences实例对象中删除Key对应的KV数据。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例对象的指针。
 * @param key 指向需要删除的Key的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_Delete(OH_Preferences *preference, const char *key);

/**
 * @brief 对选取的Key注册数据变更订阅。订阅的Key的值发生变更后，并且在调用OH_Preferences_Close()后触发回调。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例对象的指针。
 * @param context 应用上下文的指针。
 * @param observer 订阅数据变更关联的回调函数{@link OH_PreferencesDataObserver}。
 * @param keys Pointer to the keys to observe.
 * @param keyCount 需要订阅的Key的数量。取值范围大于等于1，必须与keys数组的实际长度一致。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 *     <br>若错误码为PREFERENCES_ERROR_GET_DATAOBSMGRCLIENT，表示获取数据变更订阅服务失败。
 * @see OH_Preferences OH_PreferencesDataObserver.
 * @since 13
 */
int OH_Preferences_RegisterDataObserver(OH_Preferences *preference, void *context,
    OH_PreferencesDataObserver observer, const char *keys[], uint32_t keyCount);

/**
 * @brief 取消注册选取Key的数据变更订阅。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例对象的指针。
 * @param context 应用上下文的指针。
 * @param observer 订阅数据变更关联的回调函数{@link OH_PreferencesDataObserver}。
 * @param keys Pointer to the keys observed. If this parameter is null, this API unregisters the listening for all keys.
 * @param keyCount 需要取消订阅的Key的数量。取值范围大于等于1，必须与keys数组的实际长度一致。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_Preferences OH_PreferencesDataObserver.
 * @since 13
 */
int OH_Preferences_UnregisterDataObserver(OH_Preferences *preference, void *context,
    OH_PreferencesDataObserver observer, const char *keys[], uint32_t keyCount);

/**
 * @brief 校验当前平台是否支持对应存储模式。
 *
 * @param type 要校验是否支持的存储模式。
 * @param isSupported 校验结果的指针，作为出参使用。true表示当前平台支持当前校验的存储模式，false表示当前平台不支持当前校验的存储模式。
 * @return 返回接口操作执行的状态码。
 *     <br>返回结果为PREFERENCES_OK，表示操作成功。
 *     <br>返回结果为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 * @since 18
 */
int OH_Preferences_IsStorageTypeSupported(Preferences_StorageType type, bool *isSupported);

/**
 * @brief 在Preferences对象中设置值{@link OH_PreferencesValue}。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例的指针。
 * @param key 指向需要设置的Key的指针。
 * @param value 指向需要设置的{@link OH_PreferencesValue}值的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_Preferences.
 * @since 23
 */
int OH_Preferences_SetValue(OH_Preferences *preference, const char *key, OH_PreferencesValue *value);

/**
 * @brief 根据给定的Key获取Preferences对象中的值。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例的指针。
 * @param key 指向需要获取值的Key的指针。
 * @param value 指向获取到的{@link OH_PreferencesValue}值的二级指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 *     <br>若错误码为PREFERENCES_ERROR_KEY_NOT_FOUND，表示查询的Key不存在。
 * @see OH_Preferences.
 * @since 23
 */
int OH_Preferences_GetValue(OH_Preferences *preference, const char *key, OH_PreferencesValue **value);

/**
 * @brief 获取Preferences对象中的所有值。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例的指针。
 * @param pairs 指向要获取的KV数据的指针。当不再需要此KV数据时，用户需要调用{@link OH_Preferences_FreeString}释放内存。
 * @param count 指向获取到的所有值的数量的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 *     <br>若错误码为PREFERENCES_ERROR_KEY_NOT_FOUND，表示查询的Key不存在。
 * @see OH_Preferences.
 * @since 23
 */
int OH_Preferences_GetAll(OH_Preferences *preference, OH_PreferencesPair **pairs, uint32_t *count);

/**
 * @brief 检查Preferences对象是否包含与指定Key匹配的KV数据，若包含则返回true，否则返回false。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例的指针。
 * @param key 指向需要检查的Key的指针。
 * @return 返回true则表示Preferences对象包含与指定Key匹配的KV数据，否则返回false。
 * @see OH_Preferences.
 * @since 23
 */
bool OH_Preferences_HasKey(OH_Preferences *preference, const char *key);

/**
 * @brief 将{@link OH_Preferences}对象的缓存保存到xml文件中。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_NOT_SUPPORTED，表示系统能力不支持。
 * @see OH_Preferences.
 * @since 23
 */
int OH_Preferences_Flush(OH_Preferences *preference);

/**
 * @brief 清除{@link OH_Preferences}对象缓存中的所有值。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_NOT_SUPPORTED，表示系统能力不支持。
 * @see OH_Preferences.
 * @since 23
 */
int OH_Preferences_ClearCache(OH_Preferences *preference);

/**
 * @brief 为Preferences对象注册一个多进程数据观察者。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例的指针。
 * @param context 指向数据观察者上下文的指针。
 * @param observer 要注册的{@link OH_PreferencesDataObserver}回调函数。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 *     <br>若错误码为PREFERENCES_ERROR_GET_DATAOBSMGRCLIENT，表示获取数据变更订阅服务失败。
 * @see OH_Preferences OH_PreferencesDataObserver.
 * @since 23
 */
int OH_Preferences_RegisterMultiProcessDataObserver(OH_Preferences *preference, void *context,
    OH_PreferencesDataObserver observer);

/**
 * @brief 取消注册Preferences对象的多进程数据观察者。
 * 
 * @param preference 指向目标{@link OH_Preferences}实例的指针。
 * @param context 指向数据观察者上下文的指针。
 * @param observer 要取消注册的{@link OH_PreferencesDataObserver}回调函数。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_Preferences OH_PreferencesDataObserver.
 * @since 23
 */
int OH_Preferences_UnregisterMultiProcessDataObserver(OH_Preferences *preference, void *context,
    OH_PreferencesDataObserver observer);

#ifdef __cplusplus
};
#endif

/** @} */
#endif // OH_PREFERENCES_H