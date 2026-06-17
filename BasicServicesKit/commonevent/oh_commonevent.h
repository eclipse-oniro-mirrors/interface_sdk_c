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
 * @addtogroup OH_CommonEvent
 * @{
 *
 * @brief Provides the APIs of common event service.
 *
 * @since 12
 */

/**
 * @file oh_commonevent.h
 *
 * @brief Defines the APIs for subscribing to and unsubscribing from common events and enumerates the error codes.
 *
 * @library libohcommonevent.so
 * @kit BasicServicesKit
 * @syscap SystemCapability.Notification.CommonEvent
 * @since 12
 * @version 1.0
 */

#ifndef OH_COMMONEVENT_H
#define OH_COMMONEVENT_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the error codes.
 *
 * @since 12
 * @version 1.0
 */
typedef enum CommonEvent_ErrCode {
    /**
     * Operation successful.
     *
     * @since 12
     */
    COMMONEVENT_ERR_OK = 0,

    /**
     * Permission denied.
     *
     * @since 12
     */
    COMMONEVENT_ERR_PERMISSION_ERROR = 201,

    /**
     * Invalid parameter.
     *
     * @since 12
     */
    COMMONEVENT_ERR_INVALID_PARAMETER = 401,

    /**
     * Event sending frequency is too high.
     *
     * @since 20
     */
    COMMONEVENT_ERR_SENDING_LIMIT_EXCEEDED = 1500003,

    /**
     * The third-party application fails to send system common events.
     *
     * @since 12
     */
    COMMONEVENT_ERR_NOT_SYSTEM_SERVICE = 1500004,

    /**
     * Failed to send IPC requests.
     *
     * @since 12
     */
    COMMONEVENT_ERR_SENDING_REQUEST_FAILED = 1500007,

    /**
     * Services not initialized.
     *
     * @since 12
     */
    COMMONEVENT_ERR_INIT_UNDONE = 1500008,

    /**
     * System error.
     *
     * @since 12
     */
    COMMONEVENT_ERR_OBTAIN_SYSTEM_PARAMS = 1500009,

    /**
     * The number of subscribers exceeds the upper limit.
     *
     * @since 12
     */
    COMMONEVENT_ERR_SUBSCRIBER_NUM_EXCEEDED = 1500010,

    /**
     * Failed to allocate memory.
     *
     * @since 12
     */
    COMMONEVENT_ERR_ALLOC_MEMORY_FAILED = 1500011,
} CommonEvent_ErrCode;

/**
 * @brief Defines a struct for the subscriber information.
 *
 * @since 12
 */
typedef struct CommonEvent_SubscribeInfo CommonEvent_SubscribeInfo;

/**
 * @brief  Defines a handle for the subscriber.
 *
 * @since 12
 */
typedef void CommonEvent_Subscriber;

/**
 * @brief Defines the property object used for publishing a common event.
 *
 * @since 18
 */
typedef struct CommonEvent_PublishInfo CommonEvent_PublishInfo;

/**
 * @brief Defines a struct for the common event data.
 *
 * @since 12
 */
typedef struct CommonEvent_RcvData CommonEvent_RcvData;

/**
 * @brief  Defines a handler for the additional information of a common event.
 *
 * @since 12
 */
typedef void CommonEvent_Parameters;

/**
 * @brief Defines the callback function of a common event.
 *
 * @param data Pointer to the callback data of a common event.
 * @since 12
 */
typedef void (*CommonEvent_ReceiveCallback)(const CommonEvent_RcvData *data);

/**
 * @brief Creates the subscriber information.
 *
 * @param events Pointer to the common events. The valid number of subscribed common events is the smaller value
 *     between **eventsNum** and the length of the **events[]**.
 * @param eventsNum Number of common events to subscribe.
 * @return Returns the subscriber information created if the operation is successful; returns **NULL** otherwise.
 * @since 12
 */
CommonEvent_SubscribeInfo* OH_CommonEvent_CreateSubscribeInfo(const char* events[], int32_t eventsNum);

/**
 * @brief Sets the permission of the publisher.
 *
 * @param info Pointer to the subscriber information.
 * @param permission Pointer to the permission name.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 12
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublisherPermission(CommonEvent_SubscribeInfo* info, const char* permission);

/**
 * @brief Sets a bundle name of the publisher.
 *
 * @param info Pointer to the subscriber information.
 * @param bundleName Pointer to the bundle name.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 12
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublisherBundleName(CommonEvent_SubscribeInfo* info, const char* bundleName);

/**
 * @brief Destroys the subscriber information.
 *
 * @param info Pointer to the subscriber information.
 * @since 12
 */
void OH_CommonEvent_DestroySubscribeInfo(CommonEvent_SubscribeInfo* info);

/**
 * @brief Creates a subscriber.
 *
 * @param info Pointer to the subscriber information.
 * @param callback Callback to be invoked when a common event is triggered.
 * @return Returns the subscriber created if the operation is successful; returns **NULL** otherwise.
 * @since 12
 */
CommonEvent_Subscriber* OH_CommonEvent_CreateSubscriber(const CommonEvent_SubscribeInfo* info,
    CommonEvent_ReceiveCallback callback);

/**
 * @brief Destroys a subscriber.
 *
 * @param subscriber Pointer to the common event subscriber.
 * @since 12
 */
void OH_CommonEvent_DestroySubscriber(CommonEvent_Subscriber* subscriber);

/**
 * @brief Subscribes to a common event.
 *
 * @param subscriber Pointer to the common event subscriber.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 *     <br>{@link COMMONEVENT_ERR_SENDING_REQUEST_FAILED}: Failed to send IPC requests.
 *     <br>{@link COMMONEVENT_ERR_INIT_UNDONE}: Services not initialized.
 *     <br>{@link COMMONEVENT_ERR_SUBSCRIBER_NUM_EXCEEDED}: The number of subscribers exceeds the upper limit.
 *     <br>{@link COMMONEVENT_ERR_ALLOC_MEMORY_FAILED}: Failed to allocate memory.
 * @since 12
 */
CommonEvent_ErrCode OH_CommonEvent_Subscribe(const CommonEvent_Subscriber* subscriber);

/**
 * @brief Unsubscribes from a common event.
 *
 * @param subscriber Pointer to the common event subscriber.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 *     <br>{@link COMMONEVENT_ERR_SENDING_REQUEST_FAILED}: Failed to send IPC requests.
 *     <br>{@link COMMONEVENT_ERR_INIT_UNDONE}: Services not initialized.
 * @since 12
 */
CommonEvent_ErrCode OH_CommonEvent_UnSubscribe(const CommonEvent_Subscriber* subscriber);

/**
 * @brief Obtains the name of a common event.
 *
 * @param rcvData Pointer to the callback data of a common event.
 * @return Event name obtained.
 * @since 12
 */
const char* OH_CommonEvent_GetEventFromRcvData(const CommonEvent_RcvData* rcvData);

/**
 * @brief Obtains the result code (integer type) of a common event.
 *
 * @param rcvData Pointer to the callback data of a common event.
 * @return Result code obtained.
 * @since 12
 */
int32_t OH_CommonEvent_GetCodeFromRcvData(const CommonEvent_RcvData* rcvData);

/**
 * @brief Obtains the result data (string type) of a common event.
 *
 * @param rcvData Pointer to the callback data of a common event.
 * @return Result data obtained.
 * @since 12
 */
const char* OH_CommonEvent_GetDataStrFromRcvData(const CommonEvent_RcvData* rcvData);

/**
 * @brief Obtains the bundle name of a common event.
 *
 * @param rcvData Pointer to the callback data of a common event.
 * @return Bundle name obtained.
 * @since 12
 */
const char* OH_CommonEvent_GetBundleNameFromRcvData(const CommonEvent_RcvData* rcvData);

/**
 * @brief Obtains the additional information of a common event.
 *
 * @param rcvData Pointer to the callback data of a common event.
 * @return Additional information obtained.
 * @since 12
 */
const CommonEvent_Parameters* OH_CommonEvent_GetParametersFromRcvData(const CommonEvent_RcvData* rcvData);

/**
 * @brief Creates a property object of a common event.
 *
 * @param ordered Whether the common event is an ordered one.
 *     <br>- **true**: ordered common event.
 *     <br>- **false**: unordered common event.
 * @return Returns the property object if the operation is successful; returns **null** otherwise.
 * @since 18
 */
CommonEvent_PublishInfo* OH_CommonEvent_CreatePublishInfo(bool ordered);

/**
 * @brief Destroys a property object of a common event.
 *
 * @param info Pointer to the property object of the common event to destroy.
 * @since 18
 */
void OH_CommonEvent_DestroyPublishInfo(CommonEvent_PublishInfo* info);

/**
 * @brief Sets the bundle name of a common event.
 *
 * @param info Pointer to the property object of a common event.
 * @param bundleName Pointer to the bundle name to set.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublishInfoBundleName(CommonEvent_PublishInfo* info, const char* bundleName);

/**
 * @brief Sets permissions for a common event.
 *
 * @param info Pointer to the property object of a common event.
 * @param permissions Pointer to the array of permission names. The valid number of permissions is the smaller value
 *     between **num** and the length of the **permissions[]**.
 * @param num Number of permissions.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublishInfoPermissions(CommonEvent_PublishInfo* info,
    const char* permissions[], int32_t num);

/**
 * @brief Sets the result code (integer type) of a common event.
 *
 * @param info Pointer to the property object of a common event.
 * @param code Result code to set.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublishInfoCode(CommonEvent_PublishInfo* info, int32_t code);

/**
 * @brief Sets the result data (string type) of a common event.
 *
 * @param info Pointer to the property object of a common event.
 * @param data Pointer to the result data to set. The effective data length is the smaller of **length** and
 *     the length of the **data** string.
 * @param length Length of the result data.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublishInfoData(CommonEvent_PublishInfo* info,
    const char* data, size_t length);

/**
 * @brief Sets the additional information of a common event.
 *
 * @param info Pointer to the property object of a common event.
 * @param param Pointer to the additional information to set.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublishInfoParameters(CommonEvent_PublishInfo* info,
    CommonEvent_Parameters* param);

/**
 * @brief Creates an additional information object of a common event.
 *
 * @return Returns additional information of the common event if operation is successful; returns **null** otherwise.
 * @since 18
 */
CommonEvent_Parameters* OH_CommonEvent_CreateParameters();

/**
 * @brief Destroys the additional information object of a common event.
 *
 * @param param Pointer to the additional information to destroy.
 * @since 18
 */
void OH_CommonEvent_DestroyParameters(CommonEvent_Parameters* param);

/**
 * @brief Checks whether the additional information of a common event contains a KV pair.
 *
 * @param para Pointer to the additional information to check.
 * @param key Pointer to the key.
 * @return Returns the check result.
 *     <br>- **true**: The key exists.
 *     <br>- **false**: The key does not exist.
 * @since 12
 */
bool OH_CommonEvent_HasKeyInParameters(const CommonEvent_Parameters* para, const char* key);

/**
 * @brief Obtains the int data with a specific key from the additional information of a common event.
 *
 * @param para Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param defaultValue Default value.
 * @return The int data obtained.
 * @since 12
 */
int OH_CommonEvent_GetIntFromParameters(const CommonEvent_Parameters* para, const char* key, const int defaultValue);

/**
 * @brief Sets the int data with a specific key for the additional information of a common event.
 *
 * @param param Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param value The int data to set.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetIntToParameters(CommonEvent_Parameters* param, const char* key, int value);

/**
 * @brief Obtains the int array with a specific key from the additional information of a common event.
 *
 * @param para Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param array Double pointer to the int array to obtain.
 * @return Length of the array obtained. The default value is **0**.
 * @since 12
 */
int32_t OH_CommonEvent_GetIntArrayFromParameters(const CommonEvent_Parameters* para, const char* key, int** array);

/**
 * @brief Sets the int array with a specific key for the additional information of a common event.
 *
 * @param param Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param value The int array to set.
 * @param num Number of elements in the int array.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 *     <br>{@link COMMONEVENT_ERR_ALLOC_MEMORY_FAILED}: Failed to allocate memory.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetIntArrayToParameters(CommonEvent_Parameters* param, const char* key,
    const int* value, size_t num);

/**
 * @brief Obtains the long data with a specific key from the additional information of a common event.
 *
 * @param para Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param defaultValue Default value.
 * @return The long data obtained.
 * @since 12
 */
long OH_CommonEvent_GetLongFromParameters(const CommonEvent_Parameters* para, const char* key, const long defaultValue);

/**
 * @brief Sets the long data with a specific key for the additional information of a common event.
 *
 * @param param Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param value The long data to set.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetLongToParameters(CommonEvent_Parameters* param, const char* key, long value);

/**
 * @brief Obtains the long array with a specific key from the additional information of a common event.
 *
 * @param para Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param array Double pointer to the long array to obtain.
 * @return Length of the array obtained. The default value is **0**.
 * @since 12
 */
int32_t OH_CommonEvent_GetLongArrayFromParameters(const CommonEvent_Parameters* para, const char* key, long** array);

/**
 * @brief Sets the long array for the additional information of a common event.
 *
 * @param param Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param value Pointer to the long array to set.
 * @param num Number of elements in the long array.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 *     <br>{@link COMMONEVENT_ERR_ALLOC_MEMORY_FAILED}: Failed to allocate memory.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetLongArrayToParameters(CommonEvent_Parameters* param, const char* key,
    const long* value, size_t num);

/**
 * @brief Obtains the Boolean data with a specific key from the additional information of a common event.
 *
 * @param para Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param defaultValue Default value.
 * @return The Boolean data obtained.
 * @since 12
 */
bool OH_CommonEvent_GetBoolFromParameters(const CommonEvent_Parameters* para, const char* key, const bool defaultValue);

/**
 * @brief Sets the Boolean data with a specific key for the additional information of a common event.
 *
 * @param param Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param value The Boolean data to set.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetBoolToParameters(CommonEvent_Parameters* param, const char* key, bool value);

/**
 * @brief Obtains the Boolean array with a specific key from the additional information of a common event.
 *
 * @param para Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param array Double pointer to the Boolean array to obtain.
 * @return Length of the array obtained. The default value is **0**.
 * @since 12
 */
int32_t OH_CommonEvent_GetBoolArrayFromParameters(const CommonEvent_Parameters* para, const char* key, bool** array);

/**
 * @brief Sets the Boolean array with a specific key for the additional information of a common event.
 *
 * @param param Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param value Pointer to the Boolean array to set.
 * @param num Number of elements in the Boolean array.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 *     <br>{@link COMMONEVENT_ERR_ALLOC_MEMORY_FAILED}: Failed to allocate memory.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetBoolArrayToParameters(CommonEvent_Parameters* param, const char* key,
    const bool* value, size_t num);

/**
 * @brief Obtains the character data with a specific key from the additional information of a common event.
 *
 * @param para Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param defaultValue Default value.
 * @return The character data obtained.
 * @since 12
 */
char OH_CommonEvent_GetCharFromParameters(const CommonEvent_Parameters* para, const char* key, const char defaultValue);

/**
 * @brief Sets the character data with a specific key for the additional information of a common event.
 *
 * @param param Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param value The character data to set.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetCharToParameters(CommonEvent_Parameters* param, const char* key, char value);

/**
 * @brief Obtains the character array with a specific key from the additional information of a common event.
 *
 * @param para Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param array Double pointer to the character array to obtain.
 * @return Length of the array obtained. The default value is **0**.
 * @since 12
 */
int32_t OH_CommonEvent_GetCharArrayFromParameters(const CommonEvent_Parameters* para, const char* key, char** array);

/**
 * @brief Sets the character array with a specific key for the additional information of a common event.
 *
 * @param param Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param value Pointer to the character array to set.
 * @param num Number of elements in the character array.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetCharArrayToParameters(CommonEvent_Parameters* param, const char* key,
    const char* value, size_t num);

/**
 * @brief Obtains the double data with a specific key from the additional information of a common event.
 *
 * @param para Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param defaultValue Default value.
 * @return The double data obtained.
 * @since 12
 */
double OH_CommonEvent_GetDoubleFromParameters(const CommonEvent_Parameters* para, const char* key,
    const double defaultValue);

/**
 * @brief Sets the double data with a specific key for the additional information of a common event.
 *
 * @param param Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param value The double data to set.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetDoubleToParameters(CommonEvent_Parameters* param, const char* key,
    double value);

/**
 * @brief Obtains the double array with a specific key from the additional information of a common event.
 *
 * @param para Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param array Double pointer to the double array to obtain.
 * @return Length of the array obtained. The default value is **0**.
 * @since 12
 */
int32_t OH_CommonEvent_GetDoubleArrayFromParameters(const CommonEvent_Parameters* para, const char* key,
    double** array);

/**
 * @brief Sets the double array with a specific key for the additional information of a common event.
 *
 * @param param Pointer to the additional information of a common event.
 * @param key Pointer to the key.
 * @param value Pointer to the double array to set.
 * @param num Number of elements in the double array.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 *     <br>{@link COMMONEVENT_ERR_ALLOC_MEMORY_FAILED}: Failed to allocate memory.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetDoubleArrayToParameters(CommonEvent_Parameters* param, const char* key,
    const double* value, size_t num);

/**
 * @brief Publishes a common event.
 *
 * @param event Pointer to the name of the common event.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 *     <br>{@link COMMONEVENT_ERR_SENDING_LIMIT_EXCEEDED}: Event sending frequency is too high.
 *     <br>{@link COMMONEVENT_ERR_SENDING_REQUEST_FAILED}: Failed to send IPC requests.
 *     <br>{@link COMMONEVENT_ERR_INIT_UNDONE}: Services not initialized.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_Publish(const char* event);

/**
 * @brief Publishes a common event with specified properties.
 *
 * @param event Pointer to the name of the common event.
 * @param info Pointer to the property object of a common event.
 * @return Returns an execution result.
 *     <br>{@link COMMONEVENT_ERR_OK}: Operation successful.
 *     <br>{@link COMMONEVENT_ERR_INVALID_PARAMETER}: Invalid parameter.
 *     <br>{@link COMMONEVENT_ERR_SENDING_LIMIT_EXCEEDED}: Event sending frequency is too high.
 *     <br>{@link COMMONEVENT_ERR_SENDING_REQUEST_FAILED}: Failed to send IPC requests.
 *     <br>{@link COMMONEVENT_ERR_INIT_UNDONE}: Services not initialized.
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_PublishWithInfo(const char* event, const CommonEvent_PublishInfo* info);

/**
 * @brief Checks whether a common event is an ordered one.
 *
 * @param subscriber Pointer to the common event subscriber.
 * @return Returns **true** if the common event is an ordered one; returns **false** if the common event is an
 *     unordered one.
 * @since 18
 */
bool OH_CommonEvent_IsOrderedCommonEvent(const CommonEvent_Subscriber* subscriber);

/**
 * @brief Finishes an ordered common event.
 *
 * @param subscriber Pointer to the common event subscriber.
 * @return Returns **true** if the operation is successful; returns **false** otherwise.
 * @since 18
 */
bool OH_CommonEvent_FinishCommonEvent(CommonEvent_Subscriber* subscriber);

/**
 * @brief Checks whether an ordered common event is aborted.
 *
 * @param subscriber Pointer to the common event subscriber.
 * @return Returns **true** if the ordered common event is in the abort state; returns **false** otherwise.
 * @since 18
 */
bool OH_CommonEvent_GetAbortCommonEvent(const CommonEvent_Subscriber* subscriber);

/**
 * @brief Aborts an ordered common event when used with {@link OH_CommonEvent_FinishCommonEvent}. After the abort, the
 * common event is not sent to the next subscriber.
 *
 * @param subscriber Pointer to the common event subscriber.
 * @return Returns **true** if the operation is successful; returns **false** otherwise.
 * @since 18
 */
bool OH_CommonEvent_AbortCommonEvent(CommonEvent_Subscriber* subscriber);

/**
 * @brief Clears the abort state of an ordered common event when used with {@link OH_CommonEvent_FinishCommonEvent}.
 * After the clearance, the common event is sent to the next subscriber.
 *
 * @param subscriber Pointer to the common event subscriber.
 * @return Returns **true** if the operation is successful; returns **false** otherwise.
 * @since 18
 */
bool OH_CommonEvent_ClearAbortCommonEvent(CommonEvent_Subscriber* subscriber);

/**
 * @brief Obtains the result code (integer type) of an ordered common event.
 *
 * @param subscriber Pointer to the common event subscriber.
 * @return Returns the result code obtained if the operation is successful; returns **0** otherwise.
 * @since 18
 */
int32_t OH_CommonEvent_GetCodeFromSubscriber(const CommonEvent_Subscriber* subscriber);

/**
 * @brief Sets the result code (integer type) of an ordered common event.
 *
 * @param subscriber Pointer to the common event subscriber.
 * @param code Result code to set.
 * @return Returns **true** if the operation is successful; returns **false** otherwise.
 * @since 18
 */
bool OH_CommonEvent_SetCodeToSubscriber(CommonEvent_Subscriber* subscriber, int32_t code);

/**
 * @brief Obtains the result data (string type) of an ordered common event.
 *
 * @param subscriber Pointer to the common event subscriber.
 * @return Returns the result data obtained if the operation is successful; returns **null** otherwise.
 * @since 18
 */
const char* OH_CommonEvent_GetDataFromSubscriber(const CommonEvent_Subscriber* subscriber);

/**
 * @brief Sets the result data (string type) of an ordered common event.
 *
 * @param subscriber Pointer to the common event subscriber.
 * @param data Pointer to the result data to set. The effective data length is the smaller of **length** and
 *     the length of the **data** string
 * @param length Data length.
 * @return Returns **true** if the operation is successful; returns **false** otherwise.
 * @since 18
 */
bool OH_CommonEvent_SetDataToSubscriber(CommonEvent_Subscriber* subscriber, const char* data, size_t length);

#ifdef __cplusplus
}
#endif
#endif // OH_COMMONEVENT_H
/** @} */
