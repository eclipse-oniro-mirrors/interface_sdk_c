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
 * @file oh_preferences.h
 *
 * @brief Provides APIs and structs for accessing the **Preferences** object.
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
 * @brief Represents a **Preferences** object.
 * 
 * @since 13
 */
typedef struct OH_Preferences OH_Preferences;

/**
 * @brief Defines a struct for the callback for data changes.
 * 
 * @param context Pointer to the application context.
 * @param pairs Pointer to the changed KV data.
 * @param count Number of KV pairs changed.
 * @see OH_PreferencesPair.
 * @since 13
 */
typedef void (*OH_PreferencesDataObserver)(void *context, const OH_PreferencesPair *pairs, uint32_t count);

/**
 * @brief Opens a **Preferences** instance and creates a pointer to it.
 * If this pointer is no longer required, use {@link OH_Preferences_Close} to close the instance.
 * 
 * @param option Pointer to the {@link OH_PreferencesOption} instance.
 * @param errCode Pointer to the error code returned. For details, see {@link OH_Preferences_ErrCode}.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_NOT_SUPPORTED** indicates the system capability is not supported.
 * **PREFERENCES_ERROR_DELETE_FILE** indicates the file fails to be deleted.
 * **PREFERENCES_ERROR_STORAGE** indicates the storage is abnormal.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @return Returns a pointer to the {@link OH_Preferences} instance opened if the operation is successful; returns a
 * null pointer otherwise.
 * @see OH_Preferences OH_PreferencesOption.
 * @since 13
 */
OH_Preferences *OH_Preferences_Open(OH_PreferencesOption *option, int *errCode);

/**
 * @brief Closes a **Preferences** instance.
 * 
 * @param preference Pointer to the {@link OH_Preferences} instance to close.
 * @return Returns an error code. For details, see {@link OH_Preferences_ErrCode}.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates the storage is abnormal.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_Close(OH_Preferences *preference);

/**
 * @brief Deletes the specified **Preferences** object.
 * 
 * @param option Pointer to the {@link OH_PreferencesOption} instance.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_NOT_SUPPORTED** indicates the system capability is not supported.
 * **PREFERENCES_ERROR_DELETE_FILE** indicates the file fails to be deleted.
 * @see OH_Preferences.
 * @since 23
 */
int OH_Preferences_DeletePreferences(OH_PreferencesOption *option);

/**
 * @brief Obtains an integer corresponding to the specified key in a **Preferences** instance.
 * 
 * @param preference Pointer to the {@link OH_Preferences} instance.
 * @param key Pointer to the key of the value to obtain.
 * @param value Pointer to the integer value obtained.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates the storage is abnormal.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * **PREFERENCES_ERROR_KEY_NOT_FOUND** indicates the specified key does not exist.
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_GetInt(OH_Preferences *preference, const char *key, int *value);

/**
 * @brief Obtains a Boolean value corresponding to the specified key in a **Preferences** instance.
 * 
 * @param preference Pointer to the {@link OH_Preferences} instance.
 * @param key Pointer to the key of the value to obtain.
 * @param value Pointer to the Boolean value obtained.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates the storage is abnormal.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * **PREFERENCES_ERROR_KEY_NOT_FOUND** indicates the specified key does not exist.
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_GetBool(OH_Preferences *preference, const char *key, bool *value);

/**
 * @brief Obtains a string corresponding to the specified key in a **Preferences** instance.
 * 
 * @param preference Pointer to the {@link OH_Preferences} instance.
 * @param key Pointer to the key of the value to obtain.
 * @param value Double pointer to the string obtained. If the string is not required, you can use
 * {@link OH_Preferences_FreeString} to free the string (release the memory occupied by the string).
 * @param valueLen Pointer to the length of the string obtained.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates the storage is abnormal.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * **PREFERENCES_ERROR_KEY_NOT_FOUND** indicates the specified key does not exist.
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_GetString(OH_Preferences *preference, const char *key, char **value, uint32_t *valueLen);

/**
 * @brief Releases a string obtained from a **Preferences** instance.
 * 
 * @param string Pointer to the string to release.
 * @see OH_Preferences.
 * @since 13
 */
void OH_Preferences_FreeString(char *string);

/**
 * @brief Sets an integer based on the specified key in a **Preferences** instance.
 * 
 * @param preference Pointer to the {@link OH_Preferences} instance.
 * @param key Pointer to the key of the value to set.
 * @param value Integer value to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates the storage is abnormal.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_SetInt(OH_Preferences *preference, const char *key, int value);

/**
 * @brief Sets a Boolean value based on the specified key in a **Preferences** instance.
 * 
 * @param preference Pointer to the {@link OH_Preferences} instance.
 * @param key Pointer to the key of the value to set.
 * @param value Boolean value to be set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates the storage is abnormal.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_SetBool(OH_Preferences *preference, const char *key, bool value);

/**
 * @brief Sets a string based on the specified key in a **Preferences** instance.
 * 
 * @param preference Pointer to the {@link OH_Preferences} instance.
 * @param key Pointer to the key of the value to set.
 * @param value Pointer to the string to set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates the storage is abnormal.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_SetString(OH_Preferences *preference, const char *key, const char *value);

/**
 * @brief Deletes the KV data corresponding to the specified key from a **Preferences** instance.
 * 
 * @param preference Pointer to the {@link OH_Preferences} instance.
 * @param key Pointer to the key of the KV pair to delete.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates the storage is abnormal.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_Preferences.
 * @since 13
 */
int OH_Preferences_Delete(OH_Preferences *preference, const char *key);

/**
 * @brief Subscribes to data changes of the specified keys. If the value of the specified key changes, a callback will
 * be invoked after **OH_Preferences_Close()** is called.
 * 
 * @param preference Pointer to the {@link OH_Preferences} instance.
 * @param context Pointer to the application context.
 * @param observer {@link OH_PreferencesDataObserver} callback to be invoked when data changes.
 * @param keys Pointer to the keys to observe.
 * @param keyCount Number of keys.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates the storage is abnormal.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * **PREFERENCES_ERROR_GET_DATAOBSMGRCLIENT** indicates a failure in obtaining the data change subscription service.
 * @see OH_Preferences OH_PreferencesDataObserver.
 * @since 13
 */
int OH_Preferences_RegisterDataObserver(OH_Preferences *preference, void *context,
    OH_PreferencesDataObserver observer, const char *keys[], uint32_t keyCount);

/**
 * @brief Unsubscribes from data changes of the specified keys.
 * 
 * @param preference Pointer to the {@link OH_Preferences} instance.
 * @param context Pointer to the application context.
 * @param observer {@link OH_PreferencesDataObserver} callback to be invoked when data changes.
 * @param keys Pointer to the keys observed. If this parameter is null, this API unregisters the listening for all keys.
 * @param keyCount Number of keys.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates the storage is abnormal.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_Preferences OH_PreferencesDataObserver.
 * @since 13
 */
int OH_Preferences_UnregisterDataObserver(OH_Preferences *preference, void *context,
    OH_PreferencesDataObserver observer, const char *keys[], uint32_t keyCount);

/**
 * @brief Check if a type is supported or not.
 *
 * @param type the storage type of {@Link Preferences_StorageType}.
 * @param isSupported Pointer to the Boolean value obtained.
 * @return Returns the status code of the execution.
 *         {@link PREFERENCES_OK} indicates the operation is successful.
 *         {@link PREFERENCES_ERROR_INVALID_PARAM} indicates invalid args are passed in.
 * @since 18
 */
int OH_Preferences_IsStorageTypeSupported(Preferences_StorageType type, bool *isSupported);

/**
 * @brief Sets {@link OH_PreferencesValue} in the **Preferences** object.
 * 
 * @param preference Pointer to the target {@link OH_Preferences} instance.
 * @param key Pointer to the key of the value to set.
 * @param value Pointer to the {@link OH_PreferencesValue} value to set.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * @see OH_Preferences.
 * @since 23
 */
int OH_Preferences_SetValue(OH_Preferences *preference, const char *key, OH_PreferencesValue *value);

/**
 * @brief Obtains the value from the **Preferences** object based on the given key.
 * 
 * @param preference Pointer to the target {@link OH_Preferences} instance.
 * @param key Pointer to the key of the value to obtain.
 * @param value Double pointer to {@link OH_PreferencesValue}.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * **PREFERENCES_ERROR_KEY_NOT_FOUND** indicates the specified key does not exist.
 * @see OH_Preferences.
 * @since 23
 */
int OH_Preferences_GetValue(OH_Preferences *preference, const char *key, OH_PreferencesValue **value);

/**
 * @brief Obtains all the values from the **Preferences** object.
 * 
 * @param preference Pointer to the target {@link OH_Preferences} instance.
 * @param pairs Pointer to the KV data to obtain. When the KV data is no longer needed, call
 * {@link OH_Preferences_FreeString} to free the memory.
 * @param count Pointer to the count of all obtained values.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * **PREFERENCES_ERROR_KEY_NOT_FOUND** indicates the specified key does not exist.
 * @see OH_Preferences.
 * @since 23
 */
int OH_Preferences_GetAll(OH_Preferences *preference, OH_PreferencesPair **pairs, uint32_t *count);

/**
 * @brief Checks whether the **Preferences** object contains KV data matching the specified key. Returns **true** if
 * present, and **false** otherwise.
 * 
 * @param preference Pointer to the target {@link OH_Preferences} instance.
 * @param key Pointer to the key to check.
 * @return Returns **true** if the **Preferences** object contains KV data that matches the specified key; returns **
 * false** otherwise.
 * @see OH_Preferences.
 * @since 23
 */
bool OH_Preferences_HasKey(OH_Preferences *preference, const char *key);

/**
 * @brief Saves the cache of the {@link OH_Preferences} object to an XML file.
 * 
 * @param preference Pointer to the target {@link OH_Preferences} instance.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_NOT_SUPPORTED** indicates the system capability is not supported.
 * @see OH_Preferences.
 * @since 23
 */
int OH_Preferences_Flush(OH_Preferences *preference);

/**
 * @brief Clears all values in the cache of the {@link OH_Preferences} object.
 * 
 * @param preference Pointer to the target {@link OH_Preferences} instance.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_NOT_SUPPORTED** indicates the system capability is not supported.
 * @see OH_Preferences.
 * @since 23
 */
int OH_Preferences_ClearCache(OH_Preferences *preference);

/**
 * @brief Registers a multi-process data observer for the **Preferences** object.
 * 
 * @param preference Pointer to the target {@link OH_Preferences} instance.
 * @param context Pointer to the data observer context.
 * @param observer The {@link OH_PreferencesDataObserver} callback function to register.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
 * **PREFERENCES_ERROR_GET_DATAOBSMGRCLIENT** indicates a failure in obtaining the data change subscription service.
 * @see OH_Preferences OH_PreferencesDataObserver.
 * @since 23
 */
int OH_Preferences_RegisterMultiProcessDataObserver(OH_Preferences *preference, void *context,
    OH_PreferencesDataObserver observer);

/**
 * @brief Unregisters the multi-process data observer of the **Preferences** object.
 * 
 * @param preference Pointer to the target {@link OH_Preferences} instance.
 * @param context Pointer to the data observer context.
 * @param observer The {@link OH_PreferencesDataObserver} callback function to unregister.
 * @return Returns an error code.
 * **PREFERENCES_OK** indicates the operation is successful.
 * **PREFERENCES_ERROR_INVALID_PARAM** indicates invalid parameters are specified.
 * **PREFERENCES_ERROR_STORAGE** indicates a storage exception.
 * **PREFERENCES_ERROR_MALLOC** indicates a failure in memory allocation.
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