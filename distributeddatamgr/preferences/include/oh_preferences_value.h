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
 * @brief Provides APIs for processing data in the form of key-value (KV) pairs.
 * You can use the APIs provided by the Preferences module to query, modify, and persist KV pairs.
 * The key is of the string type, and the value can be a number, a string, a boolean value.
 *
 * @since 13
 */
/**
 * @file oh_preferences_value.h
 *
 * @brief Provides APIs, enums, and structs for accessing the **PreferencesValue** object.
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
 * @brief Enumerates the data types of **PreferencesValue**.
 * 
 * @since 13
 */
typedef enum Preference_ValueType {
    /**
     * @brief Null.
     * 
     */
    PREFERENCE_TYPE_NULL = 0,
    /**
     * @brief Integer.
     * 
     */
    PREFERENCE_TYPE_INT,
    /**
     * @brief Boolean.
     * 
     */
    PREFERENCE_TYPE_BOOL,
    /**
     * @brief String.
     * 
     */
    PREFERENCE_TYPE_STRING,
    /**
     * @brief 64-bit integer.
     * 
     * @since 23
     */
    PREFERENCE_TYPE_INT64,
    /**
     * @brief Double.
     * 
     * @since 23
     */
    PREFERENCE_TYPE_DOUBLE,
    /**
     * @brief Integer array.
     * 
     * @since 23
     */
    PREFERENCE_TYPE_INT_ARRAY,
    /**
     * @brief Boolean array.
     * 
     * @since 23
     */
    PREFERENCE_TYPE_BOOL_ARRAY,
    /**
     * @brief String array.
     * 
     * @since 23
     */
    PREFERENCE_TYPE_STRING_ARRAY,
    /**
     * @brief 64-bit integer array.
     * 
     * @since 23
     */
    PREFERENCE_TYPE_INT64_ARRAY,
    /**
     * @brief Double array.
     * 
     * @since 23
     */
    PREFERENCE_TYPE_DOUBLE_ARRAY,
    /**
     * @brief Blob.
     * 
     * @since 23
     */
    PREFERENCE_TYPE_BLOB,
    /**
     * @brief End type.
     * 
     */
    PREFERENCE_TYPE_BUTT
} Preference_ValueType;

/**
 * @brief Defines a struct for the **Preferences** data in KV format.
 * 
 * @since 13
 */
typedef struct OH_PreferencesPair OH_PreferencesPair;

/**
 * @brief Defines the struct for a **PreferencesValue** object.
 * 
 * @since 13
 */
typedef struct OH_PreferencesValue OH_PreferencesValue;

/**
 * @brief Obtains the key based on the specified index from the KV data.
 * 
 * @param pairs Pointer to the target {@link OH_PreferencesPair}.
 * @param index Index of the target {@link OH_PreferencesPair}.
 * @return Returns the pointer to the key obtained if the operation is successful; returns a null pointer if the
 * operation fails or invalid parameters are specified.
 * @see OH_PreferencesPair.
 * @since 13
 */
const char *OH_PreferencesPair_GetKey(const OH_PreferencesPair *pairs, uint32_t index);

/**
 * @brief Obtains the value based on the specified index from the KV pairs.
 * 
 * @param pairs Pointer to the target {@link OH_PreferencesPair}.
 * @param index Index of the target {@link OH_PreferencesPair}.
 * @return Returns the pointer to the value obtained if the operation is successful; returns a null pointer if the
 * operation fails or invalid parameters are specified.
 * @see OH_PreferencesValue.
 * @since 13
 */
const OH_PreferencesValue *OH_PreferencesPair_GetPreferencesValue(const OH_PreferencesPair *pairs, uint32_t index);

/**
 * @brief Destroys an {@link OH_PreferencesPair} instance.
 * 
 * @param pairs Pointer to the target {@link OH_PreferencesPair} instance.
 * @param count Size of the KV array to be destroyed.
 * @see OH_PreferencesPair.
 * @since 23
 */
void OH_PreferencesPair_Destroy(OH_PreferencesPair *pairs, uint32_t count);

/**
 * @brief Obtains the data type of a **PreferencesValue** instance.
 * 
 * @param object Pointer to the {@link OH_PreferencesValue} instance.
 * @return Returns the obtained data type. If **PREFERENCE_TYPE_NULL** is returned, invalid parameters are passed in.
 * @see OH_PreferencesValue.
 * @since 13
 */
Preference_ValueType OH_PreferencesValue_GetValueType(const OH_PreferencesValue *object);

/**
 * @brief Obtains an integer from an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the {@link OH_PreferencesValue} instance.
 * @param value Pointer to the integer value obtained.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 13
 */
int OH_PreferencesValue_GetInt(const OH_PreferencesValue *object, int *value);

/**
 * @brief Obtains a Boolean value from an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the {@link OH_PreferencesValue} instance.
 * @param value Pointer to the Boolean value obtained.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 13
 */
int OH_PreferencesValue_GetBool(const OH_PreferencesValue *object, bool *value);

/**
 * @brief Obtains a string from an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the {@link OH_PreferencesValue} instance.
 * @param value Double pointer to the string obtained. If the string is not required, you can use
 * {@link OH_Preferences_FreeString} to free the string (release the memory occupied by the string).
 * @param valueLen Pointer to the length of the string obtained.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 13
 */
int OH_PreferencesValue_GetString(const OH_PreferencesValue *object, char **value, uint32_t *valueLen);

/**
 * @brief Creates an {@link OH_PreferencesValue} instance.
 * 
 * @return Returns the pointer to the {@link OH_PreferencesValue} object; returns a null pointer otherwise.
 * @see OH_PreferencesValue.
 * @since 23
 */
OH_PreferencesValue* OH_PreferencesValue_Create(void);

/**
 * @brief Destroys an {@link OH_PreferencesValue} instance.
 * 
 * @param value Pointer to the target {@link OH_PreferencesValue} instance.
 * @see OH_PreferencesValue.
 * @since 23
 */
void OH_PreferencesValue_Destroy(OH_PreferencesValue *value);

/**
 * @brief Sets an integer value for an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Integer value to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetInt(const OH_PreferencesValue *object, int value);

/**
 * @brief Sets a boolean value for an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Boolean value to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetBool(const OH_PreferencesValue *object, bool value);

/**
 * @brief Sets a string value for an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value String value to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetString(const OH_PreferencesValue *object, const char *value);

/**
 * @brief Sets an int64 value for an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Int64 value to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetInt64(const OH_PreferencesValue *object, int64_t value);

/**
 * @brief Obtains an int64 value from an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Pointer to the obtained int64 value.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetInt64(const OH_PreferencesValue *object, int64_t *value);

/**
 * @brief Sets a double value for an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Double value to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetDouble(const OH_PreferencesValue *object, double value);

/**
 * @brief Obtains a double value from an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Pointer to the obtained double value.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetDouble(const OH_PreferencesValue *object, double *value);

/**
 * @brief Sets an integer array for an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Integer array to be set.
 * @param count Pointer to the size of the array to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetIntArray(const OH_PreferencesValue *object, const int *value, uint32_t count);

/**
 * @brief Obtains an integer array from an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Double pointer to the obtained integer array.
 * @param count Pointer to the size of the array obtained.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetIntArray(const OH_PreferencesValue *object, int **value, uint32_t *count);

/**
 * @brief Sets a boolean array for an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Boolean array to be set.
 * @param count Pointer to the size of the array to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetBoolArray(const OH_PreferencesValue *object, const bool *value, uint32_t count);

/**
 * @brief Obtains a boolean array from an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Double pointer to the obtained boolean array.
 * @param count Pointer to the size of the array obtained.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetBoolArray(const OH_PreferencesValue *object, bool **value, uint32_t *count);

/**
 * @brief Sets a string array for an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value String array to be set.
 * @param count Pointer to the size of the array to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetStringArray(const OH_PreferencesValue *object, const char **value, uint32_t count);

/**
 * @brief Obtains a string array of an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Double pointer to the obtained string array.
 * @param count Pointer to the size of the array obtained.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetStringArray(const OH_PreferencesValue *object, char ***value, uint32_t *count);

/**
 * @brief Sets an int64 array for an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Int64 array to be set.
 * @param count Pointer to the size of the array to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetInt64Array(const OH_PreferencesValue *object, const int64_t *value, uint32_t count);

/**
 * @brief Obtains an int64 array from an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Double pointer to the obtained int64 array.
 * @param count Pointer to the size of the array obtained.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetInt64Array(const OH_PreferencesValue *object, int64_t **value, uint32_t *count);

/**
 * @brief Sets a double array for an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Double array to be set.
 * @param count Pointer to the size of the array to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetDoubleArray(const OH_PreferencesValue *object, const double *value, uint32_t count);

/**
 * @brief Obtains a double array of an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Double pointer to the obtained double array.
 * @param count Pointer to the size of the array obtained.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetDoubleArray(const OH_PreferencesValue *object, double **value, uint32_t *count);

/**
 * @brief Sets a blob value for an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Blob value to be set.
 * @param count Pointer to the size of the blob value to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_SetBlob(const OH_PreferencesValue *object, const uint8_t *value, uint32_t count);

/**
 * @brief Obtains a blob value from an {@link OH_PreferencesValue} instance.
 * 
 * @param object Pointer to the target {@link OH_PreferencesValue} instance.
 * @param value Double pointer to the obtained blob value.
 * @param count Pointer to the size of the blob value obtained.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_PreferencesValue.
 * @since 23
 */
int OH_PreferencesValue_GetBlob(const OH_PreferencesValue *object, uint8_t **value, uint32_t *count);
#ifdef __cplusplus
};
#endif
/** @} */
#endif // OH_PREFERENCES_VALUE_H