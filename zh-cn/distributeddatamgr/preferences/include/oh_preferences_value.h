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
 * @file oh_preferences_value.h
 *
 * @brief 提供访问Preferences值（PreferencesValue）对象的接口、枚举类型与数据结构。
 * 
 * @kit ArkData
 * @library libohpreferences.so
 * @syscap SystemCapability.DistributedDataManager.Preferences.Core
 *
 * @since 13
 */

#ifndef OH_PREFERENCES_VALUE_H
#define OH_PREFERENCES_VALUE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义PreferencesValue的数据类型。
 * 
 * @since 13
 */
typedef enum Preference_ValueType {
    /**
     * @brief 空类型。
     * 
     */
    PREFERENCE_TYPE_NULL = 0,
    /**
     * @brief 整型类型。
     * 
     */
    PREFERENCE_TYPE_INT,
    /**
     * @brief 布尔类型。
     * 
     */
    PREFERENCE_TYPE_BOOL,
    /**
     * @brief 字符串类型。
     * 
     */
    PREFERENCE_TYPE_STRING,
    /**
     * @brief 64位整型类型。
     * 
     * @since 23
     */
    PREFERENCE_TYPE_INT64,
    /**
     * @brief 浮点型类型。
     * 
     * @since 23
     */
    PREFERENCE_TYPE_DOUBLE,
    /**
     * @brief 整型数组。
     * 
     * @since 23
     */
    PREFERENCE_TYPE_INT_ARRAY,
    /**
     * @brief 布尔数组。
     * 
     * @since 23
     */
    PREFERENCE_TYPE_BOOL_ARRAY,
    /**
     * @brief 字符串数组。
     * 
     * @since 23
     */
    PREFERENCE_TYPE_STRING_ARRAY,
    /**
     * @brief 64位整型数组。
     * 
     * @since 23
     */
    PREFERENCE_TYPE_INT64_ARRAY,
    /**
     * @brief 浮点型数组。
     * 
     * @since 23
     */
    PREFERENCE_TYPE_DOUBLE_ARRAY,
    /**
     * @brief 二进制数据。
     * 
     * @since 23
     */
    PREFERENCE_TYPE_BLOB,
    /**
     * @brief 结束类型。
     * 
     */
    PREFERENCE_TYPE_BUTT
} Preference_ValueType;

/**
 * @brief 定义Preferences使用的KV数据对象类型。
 * 
 * @since 13
 */
typedef struct OH_PreferencesPair OH_PreferencesPair;

/**
 * @brief 定义PreferencesValue对象类型。
 * 
 * @since 13
 */
typedef struct OH_PreferencesValue OH_PreferencesValue;

/**
 * @brief 获取键值对数据中索引对应数据的键。
 * 
 * @param pairs 目标键值对数据{@link OH_PreferencesPair}的指针。
 * @param index 目标键值对数据{@link OH_PreferencesPair}的索引值。
 * @return 如果操作成功，返回获取到的键的指针。操作失败或传参不合法返回空指针。
 * @see OH_PreferencesPair.
 * @since 13
 */
const char *OH_PreferencesPair_GetKey(const OH_PreferencesPair *pairs, uint32_t index);

/**
 * @brief 获取键值对数据数组中索引对应的值。
 * 
 * @param pairs 目标键值对数据{@link OH_PreferencesPair}的指针。
 * @param index 目标键值对数据{@link OH_PreferencesPair}的索引值，取值范围[0, count-1]（count为pairs数组长度）。
 * @return 如果操作成功，返回获取到的值对象的指针。操作失败或传参不合法返回空指针。
 * @see OH_PreferencesValue.
 * @since 13
 */
const OH_PreferencesValue *OH_PreferencesPair_GetPreferencesValue(const OH_PreferencesPair *pairs, uint32_t index);

/**
 * @brief 销毁一个{@link OH_PreferencesPair}实例。
 * 
 * @param pairs 指向目标{@link OH_PreferencesPair}实例的指针。
 * @param count 需要销毁的KV数组大小。
 * @see OH_PreferencesPair.
 * @since 23
 */
void OH_PreferencesPair_Destroy(OH_PreferencesPair *pairs, uint32_t count);

/**
 * @brief 获取PreferencesValue对象的数据类型。
 * 
 * @param object 对象{@link OH_PreferencesValue}的指针。
 * @return 返回获取到的数据类型枚举。若返回数据类型枚举为PREFERENCE_TYPE_NULL，代表传参不合法。
 * @see OH_PreferencesValue.
 * @since 13
 */
Preference_ValueType OH_PreferencesValue_GetValueType(const OH_PreferencesValue *object);

/**
 * @brief 从PreferencesValue对象{@link OH_PreferencesValue}中获取一个整型值。
 * 
 * @param object 对象{@link OH_PreferencesValue}的指针。
 * @param value 该参数作为出参使用，表示指向获取到的整型值的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 13
 */
int OH_PreferencesValue_GetInt(const OH_PreferencesValue *object, int *value);

/**
 * @brief 从PreferencesValue对象{@link OH_PreferencesValue}中获取一个布尔值。
 * 
 * @param object 对象{@link OH_PreferencesValue}的指针。
 * @param value 该参数作为出参使用，表示指向获取到的布尔值的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 13
 */
int OH_PreferencesValue_GetBool(const OH_PreferencesValue *object, bool *value);

/**
 * @brief 从PreferencesValue对象{@link OH_PreferencesValue}中获取字符串。
 * 
 * @param object 对象{@link OH_PreferencesValue}的指针。
 * @param value 该参数作为出参使用，表示指向获取到的字符串的二级指针，使用完毕后需要调用释放函数{@link OH_Preferences_FreeString}释放内存。
 * @param valueLen 该参数作为出参使用，表示指向获取到的字符串长度的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 13
 */
int OH_PreferencesValue_GetString(const OH_PreferencesValue *object, char **value, uint32_t *valueLen);

/**
 * @brief 创建一个{@link OH_PreferencesValue}实例。
 * 
 * @return 如果操作成功，返回指向{@link OH_PreferencesValue}值对象的指针，否则返回nullptr。
 * @see OH_PreferencesValue.
 * @since 23
 */
OH_PreferencesValue* OH_PreferencesValue_Create(void);

/**
 * @brief 销毁一个{@link OH_PreferencesValue}实例。
 * 
 * @param value 指向目标{@link OH_PreferencesValue}实例的指针。
 * @see OH_PreferencesValue.
 * @since 23
 */
void OH_PreferencesValue_Destroy(OH_PreferencesValue *value);

/**
 * @brief 为{@link OH_PreferencesValue}实例设置整型值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 需要设置的整型值。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetInt(const OH_PreferencesValue *object, int value);

/**
 * @brief 为{@link OH_PreferencesValue}实例设置布尔值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 需要设置的布尔值。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetBool(const OH_PreferencesValue *object, bool value);

/**
 * @brief 为{@link OH_PreferencesValue}实例设置字符串值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 需要设置的字符串值。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetString(const OH_PreferencesValue *object, const char *value);

/**
 * @brief 为{@link OH_PreferencesValue}实例设置int64值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 需要设置的int64值。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetInt64(const OH_PreferencesValue *object, int64_t value);

/**
 * @brief 获取{@link OH_PreferencesValue}实例的int64值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 指向获取到的int64值的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetInt64(const OH_PreferencesValue *object, int64_t *value);

/**
 * @brief 为{@link OH_PreferencesValue}实例设置double值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 需要设置的double值。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetDouble(const OH_PreferencesValue *object, double value);

/**
 * @brief 获取{@link OH_PreferencesValue}实例的double值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 指向获取到的double值的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetDouble(const OH_PreferencesValue *object, double *value);

/**
 * @brief 为{@link OH_PreferencesValue}实例设置整型数组值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 需要设置的整型数组值。
 * @param count 需要设置的数组大小。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetIntArray(const OH_PreferencesValue *object, const int *value, uint32_t count);

/**
 * @brief 获取{@link OH_PreferencesValue}实例的整型数组值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 指向获取到的整型数组值的二级指针。
 * @param count 指向获取到的数组大小的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetIntArray(const OH_PreferencesValue *object, int **value, uint32_t *count);

/**
 * @brief 为{@link OH_PreferencesValue}实例设置布尔数组值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 需要设置的布尔数组值。
 * @param count 需要设置的数组大小。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetBoolArray(const OH_PreferencesValue *object, const bool *value, uint32_t count);

/**
 * @brief 获取{@link OH_PreferencesValue}实例的布尔数组值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 指向获取到的布尔数组值的二级指针。
 * @param count 指向获取到的数组大小的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetBoolArray(const OH_PreferencesValue *object, bool **value, uint32_t *count);

/**
 * @brief 为{@link OH_PreferencesValue}实例设置字符串数组值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 需要设置的字符串数组值。
 * @param count 需要设置的数组大小。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetStringArray(const OH_PreferencesValue *object, const char **value, uint32_t count);

/**
 * @brief 获取{@link OH_PreferencesValue}实例的字符串数组值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 指向获取到的字符串数组值的三级指针。
 * @param count 指向获取到的数组大小的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetStringArray(const OH_PreferencesValue *object, char ***value, uint32_t *count);

/**
 * @brief 为{@link OH_PreferencesValue}实例设置int64数组值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 需要设置的int64数组值。
 * @param count 需要设置的数组大小。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetInt64Array(const OH_PreferencesValue *object, const int64_t *value, uint32_t count);

/**
 * @brief 获取{@link OH_PreferencesValue}实例的int64数组值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 指向获取到的int64数组值的二级指针。
 * @param count 指向获取到的数组大小的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetInt64Array(const OH_PreferencesValue *object, int64_t **value, uint32_t *count);

/**
 * @brief 为{@link OH_PreferencesValue}实例设置double数组值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 需要设置的double数组值。
 * @param count 需要设置的数组大小。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetDoubleArray(const OH_PreferencesValue *object, const double *value, uint32_t count);

/**
 * @brief 获取{@link OH_PreferencesValue}实例的double数组值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 指向获取到的double数组值的二级指针。
 * @param count 指向获取到的数组大小的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetDoubleArray(const OH_PreferencesValue *object, double **value, uint32_t *count);

/**
 * @brief 为{@link OH_PreferencesValue}实例设置二进制值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 需要设置的二进制值。
 * @param count 指向需要设置的二进制数据大小。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetBlob(const OH_PreferencesValue *object, const uint8_t *value, uint32_t count);

/**
 * @brief 获取{@link OH_PreferencesValue}实例的二进制值。
 * 
 * @param object 指向目标{@link OH_PreferencesValue}实例的指针。
 * @param value 指向获取到的二进制值的二级指针。
 * @param count 指向获取到的二进制大小的指针。
 * @return 返回执行的错误码。
 *     <br>若错误码为PREFERENCES_OK，表示操作成功。
 *     <br>若错误码为PREFERENCES_ERROR_INVALID_PARAM，表示参数不合法。
 *     <br>若错误码为PREFERENCES_ERROR_STORAGE，表示存储异常。
 *     <br>若错误码为PREFERENCES_ERROR_MALLOC，表示内存分配失败。
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetBlob(const OH_PreferencesValue *object, uint8_t **value, uint32_t *count);
#ifdef __cplusplus
};
#endif
/** @} */
#endif // OH_PREFERENCES_VALUE_H