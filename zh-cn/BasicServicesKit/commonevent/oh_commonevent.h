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
 * @brief 定义公共事件订阅与退订API接口与枚举错误码。
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
 * @brief 枚举错误码。
 *
 * @since 12
 * @version 1.0
 */
typedef enum CommonEvent_ErrCode {
    /**
     * 成功。
     *
     * @since 12
     */
    COMMONEVENT_ERR_OK = 0,

    /**
     * 权限错误。
     *
     * @since 12
     */
    COMMONEVENT_ERR_PERMISSION_ERROR = 201,

    /**
     * 参数错误。
     *
     * @since 12
     */
    COMMONEVENT_ERR_INVALID_PARAMETER = 401,

    /**
     * 事件发送频率过高。
     *
     * @since 20
     */
    COMMONEVENT_ERR_SENDING_LIMIT_EXCEEDED = 1500003,

    /**
     * 三方应用无法发送系统公共事件。
     *
     * @since 12
     */
    COMMONEVENT_ERR_NOT_SYSTEM_SERVICE = 1500004,

    /**
     * IPC发送失败。
     *
     * @since 12
     */
    COMMONEVENT_ERR_SENDING_REQUEST_FAILED = 1500007,

    /**
     * 服务未初始化。
     *
     * @since 12
     */
    COMMONEVENT_ERR_INIT_UNDONE = 1500008,

    /**
     * 系统错误。
     *
     * @since 12
     */
    COMMONEVENT_ERR_OBTAIN_SYSTEM_PARAMS = 1500009,

    /**
     * 订阅者数量超过限制。
     *
     * @since 12
     */
    COMMONEVENT_ERR_SUBSCRIBER_NUM_EXCEEDED = 1500010,

    /**
     * 内存分配失败。
     *
     * @since 12
     */
    COMMONEVENT_ERR_ALLOC_MEMORY_FAILED = 1500011,
} CommonEvent_ErrCode;

/**
 * @brief 提供CommonEvent_SubscribeInfo订阅者信息结构体声明。
 *
 * @since 12
 */
typedef struct CommonEvent_SubscribeInfo CommonEvent_SubscribeInfo;

/**
 * @brief  提供CommonEvent_Subscriber订阅者结构体声明。
 *
 * @since 12
 */
typedef void CommonEvent_Subscriber;

/**
 * @brief 发布公共事件时使用的公共事件属性对象。
 *
 * @since 18
 */
typedef struct CommonEvent_PublishInfo CommonEvent_PublishInfo;

/**
 * @brief 提供CommonEvent_RcvData公共事件回调数据结构体声明。
 *
 * @since 12
 */
typedef struct CommonEvent_RcvData CommonEvent_RcvData;

/**
 * @brief  提供CommonEvent_RcvData公共事件附加信息结构体声明。
 *
 * @since 12
 */
typedef void CommonEvent_Parameters;

/**
 * @brief 提供CommonEvent_ReceiveCallback回调函数声明。
 *
 * @param data 公共事件回调数据。
 * @since 12
 */
typedef void (*CommonEvent_ReceiveCallback)(const CommonEvent_RcvData *data);

/**
 * @brief 创建订阅者信息。
 *
 * @param events Indicates the subscribed events.
 * @param eventsNum 订阅的公共事件数量。
 * @return 成功则返回订阅者信息,失败则返回NULL。
 * @since 12
 */
CommonEvent_SubscribeInfo* OH_CommonEvent_CreateSubscribeInfo(const char* events[], int32_t eventsNum);

/**
 * @brief 设置发布方权限。
 *
 * @param info 订阅者信息。
 * @param permission 权限名称。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 12
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublisherPermission(CommonEvent_SubscribeInfo* info, const char* permission);

/**
 * @brief 设置发布方包名称。
 *
 * @param info 订阅者信息。
 * @param bundleName 包名称。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 12
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublisherBundleName(CommonEvent_SubscribeInfo* info, const char* bundleName);

/**
 * @brief 释放订阅者信息。
 *
 * @param info 订阅者信息。
 * @since 12
 */
void OH_CommonEvent_DestroySubscribeInfo(CommonEvent_SubscribeInfo* info);

/**
 * @brief 创建订阅者。
 *
 * @param info 订阅者信息。
 * @param callback 公共事件回调函数
 * @return 成功则返回订阅者,失败则返回NULL。
 * @since 12
 */
CommonEvent_Subscriber* OH_CommonEvent_CreateSubscriber(const CommonEvent_SubscribeInfo* info,
    CommonEvent_ReceiveCallback callback);

/**
 * @brief 释放订阅者。
 *
 * @param subscriber 订阅者。
 * @since 12
 */
void OH_CommonEvent_DestroySubscriber(CommonEvent_Subscriber* subscriber);

/**
 * @brief 订阅公共事件。
 *
 * @param subscriber 订阅者。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数subscriber无效。
 *     <br>返回{@link COMMONEVENT_ERR_SENDING_REQUEST_FAILED}表示IPC请求发送失败。
 *     <br>返回{@link COMMONEVENT_ERR_INIT_UNDONE}表示公共事件服务未初始化。
 *     <br>返回{@link COMMONEVENT_ERR_SUBSCRIBER_NUM_EXCEEDED}表示进程订阅者数量超过200个。
 *     <br>返回{@link COMMONEVENT_ERR_ALLOC_MEMORY_FAILED}系统分配内存失败。
 * @since 12
 */
CommonEvent_ErrCode OH_CommonEvent_Subscribe(const CommonEvent_Subscriber* subscriber);

/**
 * @brief 退订公共事件。
 *
 * @param subscriber 订阅者。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数subscriber无效。
 *     <br>返回{@link COMMONEVENT_ERR_SENDING_REQUEST_FAILED}表示IPC请求发送失败。
 *     <br>返回{@link COMMONEVENT_ERR_INIT_UNDONE}表示公共事件服务未初始化。
 * @since 12
 */
CommonEvent_ErrCode OH_CommonEvent_UnSubscribe(const CommonEvent_Subscriber* subscriber);

/**
 * @brief 获取当前接收的公共事件名称。
 *
 * @param rcvData 公共事件回调数据。
 * @return 返回事件名称。
 * @since 12
 */
const char* OH_CommonEvent_GetEventFromRcvData(const CommonEvent_RcvData* rcvData);

/**
 * @brief 获取公共事件传递的数据，整数类型。
 *
 * @param rcvData 公共事件回调数据。
 * @return 返回公共事件传递的数据，整数类型。
 * @since 12
 */
int32_t OH_CommonEvent_GetCodeFromRcvData(const CommonEvent_RcvData* rcvData);

/**
 * @brief 获取公共事件传递的数据，字符串类型。
 *
 * @param rcvData 公共事件回调数据。
 * @return 返回公共事件传递的数据，字符串类型。
 * @since 12
 */
const char* OH_CommonEvent_GetDataStrFromRcvData(const CommonEvent_RcvData* rcvData);

/**
 * @brief 获取接收到的公共事件的包名称信息。
 *
 * @param rcvData 公共事件回调数据。
 * @return 返回公共事件的包名称。
 * @since 12
 */
const char* OH_CommonEvent_GetBundleNameFromRcvData(const CommonEvent_RcvData* rcvData);

/**
 * @brief 获取公共事件附加信息。
 *
 * @param rcvData 公共事件回调数据。
 * @return 返回公共事件附加信息。
 * @since 12
 */
const CommonEvent_Parameters* OH_CommonEvent_GetParametersFromRcvData(const CommonEvent_RcvData* rcvData);

/**
 * @brief 创建公共事件属性对象。
 *
 * @param ordered 是否为有序公共事件。
 *     <br>true：有序公共事件。
 *     <br>false：无序公共事件。
 * @return 创建的公共事件属性对象，创建失败时，返回null。
 * @since 18
 */
CommonEvent_PublishInfo* OH_CommonEvent_CreatePublishInfo(bool ordered);

/**
 * @brief 销毁公共事件属性对象。
 *
 * @param info 要销毁的公共事件属性对象。
 * @since 18
 */
void OH_CommonEvent_DestroyPublishInfo(CommonEvent_PublishInfo* info);

/**
 * @brief 设置公共事件订阅者包名称。
 *
 * @param info 公共事件属性对象。
 * @param bundleName 设置的订阅者包名称。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublishInfoBundleName(CommonEvent_PublishInfo* info, const char* bundleName);

/**
 * @brief 设置公共事件订阅者权限。
 *
 * @param info 公共事件属性对象。
 * @param permissions Indicates the array of permissions.
 * @param num 权限的数量。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublishInfoPermissions(CommonEvent_PublishInfo* info,
    const char* permissions[], int32_t num);

/**
 * @brief 设置公共事件传递的数据，整数类型。
 *
 * @param info 公共事件属性对象。
 * @param code 公共事件传递的数据，整数类型。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublishInfoCode(CommonEvent_PublishInfo* info, int32_t code);

/**
 * @brief 设置公共事件传递的数据，字符串类型。
 *
 * @param info 公共事件属性对象。
 * @param data 公共事件传递的数据，字符串类型，实际有效数据长度为`length`和`data`字符串长度的最小值。
 * @param length 结果数据的长度。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublishInfoData(CommonEvent_PublishInfo* info,
    const char* data, size_t length);

/**
 * @brief 设置公共事件附加信息。
 *
 * @param info 公共事件属性对象。
 * @param param 设置的附加信息。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetPublishInfoParameters(CommonEvent_PublishInfo* info,
    CommonEvent_Parameters* param);

/**
 * @brief 创建公共事件附加信息对象。
 *
 * @return 返回公共事件附加信息，创建失败时，返回null。
 * @since 18
 */
CommonEvent_Parameters* OH_CommonEvent_CreateParameters();

/**
 * @brief 销毁公共事件附加信息对象。
 *
 * @param param 公共事件附加信息。
 * @since 18
 */
void OH_CommonEvent_DestroyParameters(CommonEvent_Parameters* param);

/**
 * @brief 检查附加信息中是否包含键值对信息。
 *
 * @param para 公共事件附加信息。
 * @param key 数据键。
 * @return 返回数据键是否存在。
 *     <br>true：存在。
 *     <br>false：不存在。
 * @since 12
 */
bool OH_CommonEvent_HasKeyInParameters(const CommonEvent_Parameters* para, const char* key);

/**
 * @brief 获取公共事件附加信息中键为key的int类型内容。
 *
 * @param para 公共事件附加信息。
 * @param key 数据键。
 * @param defaultValue 默认值。
 * @return 返回查询的int类型数据。
 * @since 12
 */
int OH_CommonEvent_GetIntFromParameters(const CommonEvent_Parameters* para, const char* key, const int defaultValue);

/**
 * @brief 设置公共事件附加信息的int类型内容。
 *
 * @param param 公共事件附加信息。
 * @param key 数据键。
 * @param value 设置的int类型内容。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetIntToParameters(CommonEvent_Parameters* param, const char* key, int value);

/**
 * @brief 获取公共事件附加信息中键为key的int数组数据。
 *
 * @param para 公共事件附加信息。
 * @param key 数据键。
 * @param array 查询的数组。
 * @return 返回查询的数组长度，默认值为0。
 * @since 12
 */
int32_t OH_CommonEvent_GetIntArrayFromParameters(const CommonEvent_Parameters* para, const char* key, int** array);

/**
 * @brief 设置公共事件附加信息的int数组内容。
 *
 * @param param 公共事件附加信息。
 * @param key 数据键。
 * @param value 设置的int数组内容。
 * @param num 设置的int数组内容中元素的个数。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 *     <br>返回{@link COMMONEVENT_ERR_ALLOC_MEMORY_FAILED}表示内存分配失败。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetIntArrayToParameters(CommonEvent_Parameters* param, const char* key,
    const int* value, size_t num);

/**
 * @brief 获取公共事件附加信息中键为key的long类型数据。
 *
 * @param para 公共事件附加信息。
 * @param key 数据键。
 * @param defaultValue 默认值。
 * @return 返回查询的long类型数据。
 * @since 12
 */
long OH_CommonEvent_GetLongFromParameters(const CommonEvent_Parameters* para, const char* key, const long defaultValue);

/**
 * @brief 设置公共事件附加信息的long类型内容。
 *
 * @param param 公共事件附加信息。
 * @param key 数据键。
 * @param value 设置的long类型内容。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetLongToParameters(CommonEvent_Parameters* param, const char* key, long value);

/**
 * @brief 获取公共事件附加信息的long数组内容。
 *
 * @param para 公共事件附加信息。
 * @param key 数据键。
 * @param array 查询的数组。
 * @return 返回查询的数组长度，默认值为0。
 * @since 12
 */
int32_t OH_CommonEvent_GetLongArrayFromParameters(const CommonEvent_Parameters* para, const char* key, long** array);

/**
 * @brief 设置公共事件附加信息的long数组内容。
 *
 * @param param 公共事件附加信息。
 * @param key 数据键。
 * @param value 设置的long数组内容。
 * @param num 设置的long数组内容中元素的个数。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 *     <br>返回{@link COMMONEVENT_ERR_ALLOC_MEMORY_FAILED}表示内存分配失败。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetLongArrayToParameters(CommonEvent_Parameters* param, const char* key,
    const long* value, size_t num);

/**
 * @brief 获取公共事件附加信息中键为key的布尔类型数据。
 *
 * @param para 公共事件附加信息。
 * @param key 数据键。
 * @param defaultValue 默认值。
 * @return 返回查询的bool类型数据。
 * @since 12
 */
bool OH_CommonEvent_GetBoolFromParameters(const CommonEvent_Parameters* para, const char* key, const bool defaultValue);

/**
 * @brief 设置公共事件附加信息的布尔类型内容。
 *
 * @param param 公共事件附加信息。
 * @param key 数据键。
 * @param value 设置的布尔类型内容。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetBoolToParameters(CommonEvent_Parameters* param, const char* key, bool value);

/**
 * @brief 获取公共事件附加信息的布尔数组内容。
 *
 * @param para 公共事件附加信息。
 * @param key 数据键。
 * @param array 查询的数组。
 * @return 返回查询的数组长度，默认值为0。
 * @since 12
 */
int32_t OH_CommonEvent_GetBoolArrayFromParameters(const CommonEvent_Parameters* para, const char* key, bool** array);

/**
 * @brief 设置公共事件附加信息的布尔数组内容。
 *
 * @param param 公共事件附加信息。
 * @param key 数据键。
 * @param value 设置的布尔数组内容。
 * @param num 设置的布尔数组内容中元素的个数。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 *     <br>返回{@link COMMONEVENT_ERR_ALLOC_MEMORY_FAILED}表示内存分配失败。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetBoolArrayToParameters(CommonEvent_Parameters* param, const char* key,
    const bool* value, size_t num);

/**
 * @brief 获取公共事件附加信息中键为key的字符类型数据。
 *
 * @param para 公共事件附加信息。
 * @param key 数据键。
 * @param defaultValue 默认值。
 * @return 返回查询的char类型数据。
 * @since 12
 */
char OH_CommonEvent_GetCharFromParameters(const CommonEvent_Parameters* para, const char* key, const char defaultValue);

/**
 * @brief 设置公共事件附加信息的字符类型内容。
 *
 * @param param 公共事件附加信息。
 * @param key 数据键。
 * @param value 设置的字符类型内容。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetCharToParameters(CommonEvent_Parameters* param, const char* key, char value);

/**
 * @brief 获取公共事件附加信息的字符数组内容。
 *
 * @param para 公共事件附加信息。
 * @param key 数据键。
 * @param array 查询的数组。
 * @return 返回查询的数组长度，默认值为0。
 * @since 12
 */
int32_t OH_CommonEvent_GetCharArrayFromParameters(const CommonEvent_Parameters* para, const char* key, char** array);

/**
 * @brief 设置公共事件附加信息的字符数组内容。
 *
 * @param param 公共事件附加信息。
 * @param key 数据键。
 * @param value 设置的字符数组内容。
 * @param num 设置的字符数组内容中元素的个数。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetCharArrayToParameters(CommonEvent_Parameters* param, const char* key,
    const char* value, size_t num);

/**
 * @brief 获取公共事件附加信息的double类型内容。
 *
 * @param para 公共事件附加信息。
 * @param key 数据键。
 * @param defaultValue 默认值。
 * @return 返回查询的double类型数据。
 * @since 12
 */
double OH_CommonEvent_GetDoubleFromParameters(const CommonEvent_Parameters* para, const char* key,
    const double defaultValue);

/**
 * @brief 设置公共事件附加信息的double类型内容。
 *
 * @param param 公共事件附加信息。
 * @param key 数据键。
 * @param value 设置的double类型内容。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetDoubleToParameters(CommonEvent_Parameters* param, const char* key,
    double value);

/**
 * @brief 获取公共事件附加信息中键为key的double数组数据。
 *
 * @param para 公共事件附加信息。
 * @param key 数据键。
 * @param array 查询的数组。
 * @return 返回查询的数组长度，默认值为0。
 * @since 12
 */
int32_t OH_CommonEvent_GetDoubleArrayFromParameters(const CommonEvent_Parameters* para, const char* key,
    double** array);

/**
 * @brief 设置公共事件附加信息的double数组内容。
 *
 * @param param 公共事件附加信息。
 * @param key 数据键。
 * @param value 设置的double数组内容。
 * @param num 设置的double数组内容中元素的个数。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 *     <br>返回{@link COMMONEVENT_ERR_ALLOC_MEMORY_FAILED}表示内存分配失败。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_SetDoubleArrayToParameters(CommonEvent_Parameters* param, const char* key,
    const double* value, size_t num);

/**
 * @brief 发布公共事件。
 *
 * @param event 公共事件名称。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 *     <br>返回{@link COMMONEVENT_ERR_SENDING_LIMIT_EXCEEDED}表示事件发送频率过高。
 *     <br>返回{@link COMMONEVENT_ERR_SENDING_REQUEST_FAILED}表示IPC请求发送失败。
 *     <br>返回{@link COMMONEVENT_ERR_INIT_UNDONE}表示公共事件服务未初始化。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_Publish(const char* event);

/**
 * @brief 发布带有指定属性的公共事件。
 *
 * @param event 公共事件名称。
 * @param info 设置的公共事件属性。
 * @return 返回错误码。
 *     <br>返回{@link COMMONEVENT_ERR_OK}表示成功。
 *     <br>返回{@link COMMONEVENT_ERR_INVALID_PARAMETER}表示参数错误。
 *     <br>返回{@link COMMONEVENT_ERR_SENDING_LIMIT_EXCEEDED}表示事件发送频率过高。
 *     <br>返回{@link COMMONEVENT_ERR_SENDING_REQUEST_FAILED}表示IPC请求发送失败。
 *     <br>返回{@link COMMONEVENT_ERR_INIT_UNDONE}表示公共事件服务未初始化。
 * @since 18
 */
CommonEvent_ErrCode OH_CommonEvent_PublishWithInfo(const char* event, const CommonEvent_PublishInfo* info);

/**
 * @brief 查询当前公共事件是否为有序公共事件。
 *
 * @param subscriber 公共事件的订阅者对象。
 * @return 返回true表示有序公共事件；返回false表示无序公共事件。
 * @since 18
 */
bool OH_CommonEvent_IsOrderedCommonEvent(const CommonEvent_Subscriber* subscriber);

/**
 * @brief 用于订阅者结束对当前有序公共事件的处理。
 *
 * @param subscriber 公共事件的订阅者对象。
 * @return 返回true表示操作成功；返回false表示操作失败。
 * @since 18
 */
bool OH_CommonEvent_FinishCommonEvent(CommonEvent_Subscriber* subscriber);

/**
 * @brief 获取当前有序公共事件是否处于中止状态。
 *
 * @param subscriber 公共事件的订阅者对象。
 * @return 返回true表示当前有序公共事件处于中止状态；返回false表示当前有序公共事件没有处于中止状态。
 * @since 18
 */
bool OH_CommonEvent_GetAbortCommonEvent(const CommonEvent_Subscriber* subscriber);

/**
 * @brief 该接口与{@link OH_CommonEvent_FinishCommonEvent}配合使用，可以中止当前的有序公共事件，使该公共事件不再向下一个订阅者传递。
 *
 * @param subscriber 公共事件的订阅者对象。
 * @return 返回true表示操作成功；返回false表示操作失败。
 * @since 18
 */
bool OH_CommonEvent_AbortCommonEvent(CommonEvent_Subscriber* subscriber);

/**
 * @brief 该接口与{@link OH_CommonEvent_FinishCommonEvent}配合使用，可以取消当前有序公共事件的中止状态，使该公共事件继续向下一个订阅者传递。
 *
 * @param subscriber 公共事件的订阅者对象。
 * @return 返回true表示操作成功；返回false表示操作失败。
 * @since 18
 */
bool OH_CommonEvent_ClearAbortCommonEvent(CommonEvent_Subscriber* subscriber);

/**
 * @brief 获取有序公共事件传递的数据，整数类型。
 *
 * @param subscriber 公共事件的订阅者对象。
 * @return 返回有序公共事件传递的数据，整数类型，无法获取时返回0。
 * @since 18
 */
int32_t OH_CommonEvent_GetCodeFromSubscriber(const CommonEvent_Subscriber* subscriber);

/**
 * @brief 设置有序公共事件传递的数据，整数类型。
 *
 * @param subscriber 公共事件的订阅者对象。
 * @param code 有序公共事件传递的数据，整数类型。
 * @return 返回true表示操作成功；返回false表示操作失败。
 * @since 18
 */
bool OH_CommonEvent_SetCodeToSubscriber(CommonEvent_Subscriber* subscriber, int32_t code);

/**
 * @brief 获取有序公共事件传递的数据，字符串类型。
 *
 * @param subscriber 公共事件的订阅者对象。
 * @return 返回有序公共事件传递的数据，字符串类型，无法获取时返回null。
 * @since 18
 */
const char* OH_CommonEvent_GetDataFromSubscriber(const CommonEvent_Subscriber* subscriber);

/**
 * @brief 设置有序公共事件传递的数据，字符串类型。
 *
 * @param subscriber 公共事件的订阅者对象。
 * @param data 有序公共事件传递的数据，字符串类型，实际有效数据长度为`length`与`data`字符串长度的较小值。
 * @param length 数据的长度。
 * @return 返回true表示操作成功；返回false表示操作失败。
 * @since 18
 */
bool OH_CommonEvent_SetDataToSubscriber(CommonEvent_Subscriber* subscriber, const char* data, size_t length);

#ifdef __cplusplus
}
#endif
#endif // OH_COMMONEVENT_H
/** @} */