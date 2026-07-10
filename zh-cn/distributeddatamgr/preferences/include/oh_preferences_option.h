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
 * @file oh_preferences_option.h
 *
 * @brief 提供访问Preferences配置选项（PreferencesOption）的接口与数据结构。
 * 
 * @kit ArkData
 * @library libohpreferences.so
 * @syscap SystemCapability.DistributedDataManager.Preferences.Core
 *
 * @since 13
 */

#ifndef OH_PREFERENCES_OPTION_H
#define OH_PREFERENCES_OPTION_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义Preferences配置选项的数据结构。
 * 
 * @since 13
 */
typedef struct OH_PreferencesOption OH_PreferencesOption;

/**
 * @brief 首选项配置选项的存储模式枚举。
 * 
 * @since 18
 */
typedef enum Preferences_StorageType {
    /**
     * XML存储模式，对数据的操作发生在内存中，调用{@link OH_Preferences_Close}时落盘，不支持多进程。
    */
    PREFERENCES_STORAGE_XML = 0,
    /**
     * GSKV存储模式，对数据的操作实时落盘，可支持多进程。
     */
    PREFERENCES_STORAGE_GSKV
} Preferences_StorageType;

/**
 * @brief 创建一个Preferences配置选项的{@link OH_PreferencesOption}实例对象以及指向它的指针。
 * <br>当不再需要使用指针时，请使用{@link OH_PreferencesOption_Destroy}销毁实例对象，否则会导致内存泄漏。
 * 
 * @return 如果操作成功，返回指向Preferences配置选项{@link OH_PreferencesOption}实例对象的指针。失败返回空指针。
 * @see OH_PreferencesOption.
 * @since 13
 */
OH_PreferencesOption *OH_PreferencesOption_Create(void);

/**
 * @brief 设置Preferences配置选项{@link OH_PreferencesOption}实例对象的文件名称。
 * 
 * @param option 指向Preferences配置选项{@link OH_PreferencesOption}实例对象的指针。
 * @param fileName 需要设置的文件名称。文件名称长度需大于零且小于等于255字节，名称中不能包含'/'且不能以'/'结尾。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 * @see OH_PreferencesOption.
 * @since 13
 */
int OH_PreferencesOption_SetFileName(OH_PreferencesOption *option, const char *fileName);

/**
 * @brief 设置Preferences配置选项{@link OH_PreferencesOption}实例对象的包名称。
 * 
 * @param option 配置选项{@link OH_PreferencesOption}实例对象的指针。
 * @param bundleName 需要设置的包名称。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 * @see OH_PreferencesOption.
 * @since 13
 */
int OH_PreferencesOption_SetBundleName(OH_PreferencesOption *option, const char *bundleName);

/**
 * @brief 设置Preferences配置选项{@link OH_PreferencesOption}实例对象的应用组ID。
 * <br>设置应用组ID后，会指定在此应用组ID对应的沙箱路径下创建Preferences实例。应用组ID需要向应用市场获取，暂不支持。
 * <br>当传入的应用组ID为空字符串时，默认在本应用沙箱目录下创建Preferences实例。
 * 
 * @param option 配置选项{@link OH_PreferencesOption}实例对象的指针。
 * @param dataGroupId 需要设置的应用组ID。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 * @see OH_PreferencesOption.
 * @since 13
 */
int OH_PreferencesOption_SetDataGroupId(OH_PreferencesOption *option, const char *dataGroupId);

/**
 * @brief 设置Preferences实例对象的存储模式。
 * 
 * @param option 指向要设置存储模式的配置项的指针。
 * @param type 需要设置的存储模式。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 * @see OH_PreferencesOption.
 * @since 18
 */
int OH_PreferencesOption_SetStorageType(OH_PreferencesOption *option, Preferences_StorageType type);

/**
 * @brief 销毁Preferences配置选项{@link OH_PreferencesOption}实例。
 * 
 * @param option 配置选项{@link OH_PreferencesOption}实例对象的指针。
 * @return 返回接口操作执行的状态码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 * @see OH_PreferencesOption.
 * @since 13
 */
int OH_PreferencesOption_Destroy(OH_PreferencesOption *option);
#ifdef __cplusplus
};
#endif
/** @} */
#endif // OH_PREFERENCES_OPTION_H