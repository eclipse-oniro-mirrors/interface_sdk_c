/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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
 * @addtogroup HiAppEvent
 * @{
 *
 * @brief Provides application event logging functions.
 *
 * Provides the event logging function for applications to log the fault, statistical, security, and user behavior
 * events reported during running. Based on event information, you will be able to analyze the running status of
 * applications.
 *
 * @since 8
 * @version 1.0
 */

/**
 * @file hiappevent.h
 *
 * @brief The **HiAppEvent** module provides event subscription and event logging function definitions. Before
 * performing application event logging, you must construct a parameter list object to store the input event parameters
 * and specify the event domain, event name, and event type. <p>Event domain: domain associated with the application
 * event. <p>Event name: name of the application event. <p>Event type: fault, statistics, security, or behavior. <p>
 * Parameter list: a linked list used to store event parameters. Each parameter consists of a parameter name and a
 * parameter value.
 *
 * @kit PerformanceAnalysisKit
 * @library libhiappevent_ndk.z.so
 * @syscap SystemCapability.HiviewDFX.HiAppEvent
 * @since 8
 * @version 1.0
 */
#ifndef HIVIEWDFX_HIAPPEVENT_H
#define HIVIEWDFX_HIAPPEVENT_H
#include <stdbool.h>
#include <stdint.h>
#include "hiappevent_cfg.h"
#include "hiappevent_event.h"
#include "hiappevent_param.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 错误码定义。
 * 
 * @since 15
 */
typedef enum {
    /**/**
     * 操作成功。
     */
     * @since 15
     */
    HIAPPEVENT_SUCCESS = 0,

    /**
     * @error 无效的参数值长度
     * @since 18
     */
    HIAPPEVENT_INVALID_PARAM_VALUE_LENGTH = 4,

    /**
     * @error 处理器为空
     * @since 18
     */
    HIAPPEVENT_PROCESSOR_IS_NULL = -7,

    /**
     * @error 找不到处理器
     * @since 18
     */
    HIAPPEVENT_PROCESSOR_NOT_FOUND = -8,

    /**/**
     * 参数值非法。
     */
     * @since 15
     */
    HIAPPEVENT_INVALID_PARAM_VALUE = -9,

    /**/**
     * 事件配置为空。
     */
     * @since 15
     */
    HIAPPEVENT_EVENT_CONFIG_IS_NULL = -10,

    /**
     * @error 操作失败
     * @since 18
     */
    HIAPPEVENT_OPERATE_FAILED = -100,

    /**
     * @error 无效的uid
     * @since 18
     */
    HIAPPEVENT_INVALID_UID = -200,
    /**
 * @error 报告频率超过。
 * @since 26.0.0
 */
    HIAPPEVENT_REPORT_FREQUENCY_EXCEEDED = -300
} HiAppEvent_ErrorCode;

/**
 * @brief Enumerates the event types. You are advised to select different event types based on application scenarios.
 * 
 * @since 8
 * @version 1.0
 */
enum {
    /* Fault event type */
    FAULT = 1,

    /* Statistic event type */
    STATISTIC = 2,

    /* Security event type */
    SECURITY = 3,

    /* Behavior event type */
    BEHAVIOR = 4
} EventType ;

/**
 * @brief Defines a struct for the information about a single event, including the domain, name, type, and 
 * parameter list in JSON string format.
 * 
 * @since 12
 * @version 1.0
 */
typedef struct HiAppEvent_AppEventInfo {
    /* The domain of the event. */
    const char* domain;
    /* The name of the event. */
    const char* name;
    /* The type of the event. */
    enum EventType type;
    /* The json string of the parameter. */
    const char* params;
} HiAppEvent_AppEventInfo;

/**
 * @brief Defines the information of an event group, including its name, the array of event information grouped by name,
 * and the length of the event array.
 *
 * @syscap SystemCapability.HiviewDFX.HiAppEvent
 * @since 12
 * @version 1.0
 */
typedef struct HiAppEvent_AppEventGroup {
    /* The name of the event. */
    const char* name;
    /* The event array which is group by the name. */
    const struct HiAppEvent_AppEventInfo* appEventInfos;
    /* The length of appEventInfos array. */
    uint32_t infoLen;
} HiAppEvent_AppEventGroup;

/**
 * @brief 事件参数列表节点。
 * 
 * @since 8
 * @version 1.0
 */
typedef struct ParamListNode* ParamList;

/**
 * @brief 用于接收app事件的监听器。
 * 
 * @syscap SystemCapability.HiviewDFX.HiAppEvent
 * @since 12
 * @version 1.0
 */
typedef struct HiAppEvent_Watcher HiAppEvent_Watcher;

/**
 * @brief 应用事件上报的处理者。
 * 
 * @since 18
 */
typedef struct HiAppEvent_Processor HiAppEvent_Processor;

/**
 * @brief 用于设置系统事件触发条件的配置对象。
 * 
 * @since 15
 */
typedef struct HiAppEvent_Config HiAppEvent_Config;

/**
 * @brief 监听器接收到事件后，将触发该回调，将事件内容传递给调用方。注意：回调中的指针所指对象的生命周期仅限于该回调函数内，请勿在该回调函数外直接使用该指针，若需缓存该信息，请对指针指向的内容进行深拷贝。
 * 
 * @param domain 接收到的app事件的领域。
 * @param appEventGroups 按照不同事件名称分组的事件组数组。
 * @param groupLen 事件组数组的长度。
 * @since 12
 * @version 1.0
 */
typedef void (*OH_HiAppEvent_OnReceive)(
    const char* domain, const struct HiAppEvent_AppEventGroup* appEventGroups, uint32_t groupLen);

/**
 * @brief 监听器收到事件后，若监听器中未设置OH_HiAppEvent_OnReceive回调，将保存该事件。
 * 当保存的事件满足通过OH_HiAppEvent_SetTriggerCondition设定的条件后，将触发该回调。回调结束后，当新保存的事件消息再次满足设定的条件后，将再次进行回调。
 * 
 * @param row 监听器新接收到的事件消息的数量。
 * @param size 监听器新接收的事件消息的大小总和（单个事件大小计算方式为：将消息转换为json字符串后，字符串的长度）。
 * @since 12
 * @version 1.0
 */
typedef void (*OH_HiAppEvent_OnTrigger)(int row, int size);

/**
 * @brief 使用OH_HiAppEvent_TakeWatcherData获取监听器接收到的事件时，监听器接收到的事件将通过该回调函数传递给调用者。注意：回调中的指针所指对象的生命周期仅限于该回调函数内，
 * 请勿在该回调函数外直接使用该指针。若需缓存该信息，请对指针指向的内容进行深拷贝。
 * 
 * @param events The event json string array.
 * @param eventLen 事件数组大小。
 * @since 12
 * @version 1.0
 */
typedef void (*OH_HiAppEvent_OnTake)(const char* const *events, uint32_t eventLen);

/**
 * @brief 创建一个指向参数列表对象的指针。
 * 
 * @return 指向参数列表对象的指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_CreateParamList(void);

/**
 * @brief 销毁一个指向参数列表对象的指针，释放其分配内存。
 * 
 * @param list 参数列表对象指针。
 * @since 8
 * @version 1.0
 */
void OH_HiAppEvent_DestroyParamList(ParamList list);

/**
 * @brief 添加一个布尔参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param boolean 需要添加的布尔参数值。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddBoolParam(ParamList list, const char* name, bool boolean);

/**
 * @brief 添加一个布尔数组参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param booleans 需要添加的布尔数组参数值。
 * @param arrSize 需要添加的参数数组大小。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddBoolArrayParam(ParamList list, const char* name, const bool* booleans, int arrSize);

/**
 * @brief 添加一个int8_t参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param num 需要添加的int8_t参数值。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt8Param(ParamList list, const char* name, int8_t num);

/**
 * @brief 添加一个int8_t数组参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param nums 需要添加的int8_t数组参数值。
 * @param arrSize 需要添加的参数数组大小。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt8ArrayParam(ParamList list, const char* name, const int8_t* nums, int arrSize);

/**
 * @brief 添加一个int16_t参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param num 需要添加的int16_t参数值。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt16Param(ParamList list, const char* name, int16_t num);

/**
 * @brief 添加一个int16_t数组参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param nums 需要添加的int16_t数组参数值。
 * @param arrSize 需要添加的参数数组大小。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt16ArrayParam(ParamList list, const char* name, const int16_t* nums, int arrSize);

/**
 * @brief 添加一个int32_t参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param num 需要添加的int32_t参数值。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt32Param(ParamList list, const char* name, int32_t num);

/**
 * @brief 添加一个int32_t数组参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param nums 需要添加的int32_t数组参数值。
 * @param arrSize 需要添加的参数数组大小。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt32ArrayParam(ParamList list, const char* name, const int32_t* nums, int arrSize);

/**
 * @brief 添加一个int64_t参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param num 需要添加的int64_t参数值。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt64Param(ParamList list, const char* name, int64_t num);

/**
 * @brief 添加一个int64_t数组参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param nums 需要添加的int64_t数组参数值。
 * @param arrSize 需要添加的参数数组大小。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt64ArrayParam(ParamList list, const char* name, const int64_t* nums, int arrSize);

/**
 * @brief 添加一个float参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param num 需要添加的float参数值。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddFloatParam(ParamList list, const char* name, float num);

/**
 * @brief 添加一个float数组参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param nums 需要添加的float数组参数值。
 * @param arrSize 需要添加的参数数组大小。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddFloatArrayParam(ParamList list, const char* name, const float* nums, int arrSize);

/**
 * @brief 添加一个double参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param num 需要添加的double参数值。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddDoubleParam(ParamList list, const char* name, double num);

/**
 * @brief 添加一个double数组参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param nums 需要添加的double数组参数值。
 * @param arrSize 需要添加的参数数组大小。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddDoubleArrayParam(ParamList list, const char* name, const double* nums, int arrSize);

/**
 * @brief 添加一个字符串参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param str 需要添加的字符串参数值。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddStringParam(ParamList list, const char* name, const char* str);

/**
 * @brief 添加一个字符串数组参数到参数列表中。
 * 
 * @param list 需要添加参数的参数列表指针。
 * @param name 需要添加的参数名称。
 * @param strs 需要添加的字符串数组参数值。
 * @param arrSize 需要添加的参数数组大小。
 * @return 添加参数后的参数列表指针。
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddStringArrayParam(ParamList list, const char* name, const char * const *strs, int arrSize);

/**
 * @brief 实现对参数为列表类型的应用事件打点。在应用事件打点前，该接口会先对该事件的参数进行校验。如果校验成功，则接口会将事件写入事件文件。
 * 
 * @param domain 事件领域。开发者可以根据需要自定义事件领域。
 *     事件领域名称支持数字、字母、下划线字符，需要以字母开头且不能以下划线结尾，长度非空且不超过32个字符。
 * @param name 事件名称。开发者可以根据需要自定义事件名称。
 *     首字符必须为字母字符或$字符，中间字符必须为数字字符、字母字符或下划线字符，结尾字符必须为数字字符或字母字符，长度非空且不超过48个字符。
 * @param type 事件类型，在{@link EventType}中定义。
 * @param list 事件参数列表，每个参数由参数名和参数值组成，其规格定义如下：
 *     <br>1、参数名为字符串类型。
 *     首字符必须为字母字符或$字符，中间字符必须为数字字符、字母字符或下划线字符，结尾字符必须为数字字符或字母字符，长度非空且不超过32个字符。
 *     <br>2、参数值支持字符串、数值、布尔、数组类型。字符串类型参数长度需在8 * 1024个字符以内，超出会做丢弃处理；
 *     数组类型参数中的元素类型只能为字符串、数值、布尔中的一种，且元素个数需在100以内，超出会做丢弃处理。
 *     <br>3、参数个数需在32个以内，超出的参数会做丢弃处理。
 * @return 如果事件参数校验成功，则返回0，将事件写入事件文件；
 *     如果事件中存在无效参数，则返回正值，丢弃无效参数后将事件写入事件文件；
 *     如果事件参数校验失败，则返回负值，并且事件将不会写入事件文件。
 *     <br>0 事件参数校验成功。
 *     <br>-1 非法的事件名称。
 *     <br>-4 非法的事件领域名称。
 *     <br>-99 打点功能被关闭。
 *     <br>1 非法的事件参数名称。
 *     <br>4 非法的事件参数字符串长度。
 *     <br>5 非法的事件参数数量。
 *     <br>6 非法的事件参数数组长度。
 *     <br>8 重复的事件参数名称。
 * @since 8
 * @version 1.0
 */
int OH_HiAppEvent_Write(const char* domain, const char* name, enum EventType type, const ParamList list);

/**
 * @brief 实现应用事件打点的配置功能。应用事件打点配置接口，用于配置事件打点开关、事件文件目录存储配额大小等功能。
 * 
 * @param name 配置项名称。名称可填{@link DISABLE}和{@link MAX_STORAGE}。
 * @param value 配置项值。如果配置项名称是{@link DISABLE}，值可以填“true”或者“false”；
 *     如果配置项名称是{@link MAX_STORAGE}，配额值字符串只由数字字符和大小单位字符（单位字符支持[b\|k\|kb\|m\|mb\|g\|gb\|t\|tb]，不区分大小写）构成。
 *     配额值字符串必须以数字开头，后面可以选择不传单位字符（默认使用byte作为单位），或者以单位字符结尾。
 * @return 配置结果。如果配置成功，则返回true；如果配置失败则返回false。
 * @since 8
 * @version 1.0
 */
bool OH_HiAppEvent_Configure(const char* name, const char* value);

/**
 * @brief 创建一个用于监听app事件的监听器。
 * 
 * @param name 监听器名称。
 * @return 接口调用成功时返回指向的新建监听器的指针，name参数异常时返回nullptr。
 * @since 12
 * @version 1.0
 */
HiAppEvent_Watcher* OH_HiAppEvent_CreateWatcher(const char* name);

/**
 * @brief 销毁已创建的监听器。注意：已创建的监听器不再使用后，需要将其销毁，释放内存，防止内存泄漏，销毁后需将对应指针置空。
 * 
 * @param watcher 指向监听器的指针（即OH_HiAppEvent_CreateWatcher接口返回的指针）。
 * @since 12
 * @version 1.0
 */
void OH_HiAppEvent_DestroyWatcher(HiAppEvent_Watcher* watcher);

/**
 * @brief 用于设置监听器OH_HiAppEvent_OnTrigger回调的触发条件。
 * 分别可以从监视器新接收事件数量、新接收事件大小、onTrigger触发超时时间，设置触发条件。调用方应至少保证从一个方面设置触发条件。
 * 
 * @param watcher 指向监听器的指针（即OH_HiAppEvent_CreateWatcher接口返回的指针）。
 * @param row 当输入值大于0，且新接收事件的数量大于等于该值时，将调用设置的onTrigger回调函数；
 *     当输入值小于等于0时，不再以接收数量多少为维度来触发onTrigger回调。
 * @param size 当输入值大于0，且新接收事件的大小(单个事件大小计算方式为，将事件转换为json字符串后，字符串的长度)大于等于该值时，将调用设置的onTrigger回调函数；
 *     当输入值小于等于0时，不再以新接收事件大小为维度触发onTrigger回调。
 * @param timeOut 单位为秒，实际生效值为timeOut * 30秒。timeOut>0时，每timeOut * 30秒检查新事件，有则触发onTrigger，触发后重新计时；
 *     触发onTrigger后，经过timeOut秒后将再次检查是否存在新接收到的事件。
 *     timeOut≤0时不启用超时触发。
 * @return 0：接口调用成功；-5：watcher入参空指针。
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_SetTriggerCondition(HiAppEvent_Watcher* watcher, int row, int size, int timeOut);

/**
 * @brief 用于设置监听器需要监听的事件的类型。该函数可以重复调用，可添加多个过滤规则，而非替换，监听器将收到满足任一过滤规则的事件的通知。
 * 
 * @param watcher 指向监听器的指针（即OH_HiAppEvent_CreateWatcher接口返回的指针）。
 * @param domain 需要监听事件的领域。
 * @param eventTypes 需要监听事件的事件类型。使用按位与方式进行匹配，可支持监听多种类型的事件。
 *     <br>第一位为1（数值为1）表示支持监听故障类型的事件；
 *     <br>第二位为1（数值为2）表示支持监听统计类型的事件；
 *     <br>第三位为1（数值为4）表示支持监听安全类型的事件；
 *     <br>第四位为1（数值为8）表示支持监听行为类型的事件。
 *     <br>都为1（数值为15）或者都为0（数值为0）表示支持所有类型事件。
 * @param names 需要监听的事件名称数组。
 * @param namesLen 监听的事件名称的数组长度。
 * @return 0：接口调用成功；-1：names参数异常；-4：domain参数异常；-5：watcher入参空指针。
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_SetAppEventFilter(HiAppEvent_Watcher* watcher, const char* domain, uint8_t eventTypes,
    const char* const *names, int namesLen);

/**
 * @brief 用于设置监听器onTrigger回调的接口。
 * 如果未设置OnReceive回调或已将其设置为nullptr，则将保存观察者接收到的应用事件。当保存的应用事件满足onTrigger回调的触发条件时，将调用onTrigger回调。
 * 
 * @param watcher 指向监听器的指针（即OH_HiAppEvent_CreateWatcher接口返回的指针）。
 * @param onTrigger 需要设置的回调。
 * @return 0：接口调用成功；-5：watcher入参空指针。
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_SetWatcherOnTrigger(HiAppEvent_Watcher* watcher, OH_HiAppEvent_OnTrigger onTrigger);

/**
 * @brief 用于设置监听器onReceive回调函数的接口。当监听器监听到相应事件后，onReceive回调函数将被调用。
 * 
 * @param watcher 指向监听器的指针（即OH_HiAppEvent_CreateWatcher接口返回的指针）。
 * @param onReceive 回调函数的函数指针。
 * @return 0：接口调用成功；-5：watcher入参空指针。
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_SetWatcherOnReceive(HiAppEvent_Watcher* watcher, OH_HiAppEvent_OnReceive onReceive);

/**
 * @brief 用于获取监听器收到后保存的事件。
 * 
 * @param watcher 指向监听器的指针（即OH_HiAppEvent_CreateWatcher接口返回的指针）。
 * @param eventNum 当输入值小于等于0时，取全部已保存事件；当输入值大于0时，按照事件发生时间倒序排列，取指定数量的已保存事件。
 * @param onTake 回调函数指针，事件通过调用该函数返回事件信息。
 * @return 0：接口调用成功；-5：watcher入参空指针；-6：还未调用OH_HiAppEvent_AddWatcher，操作顺序有误。
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_TakeWatcherData(HiAppEvent_Watcher* watcher, uint32_t eventNum, OH_HiAppEvent_OnTake onTake);

/**
 * @brief 添加监听器的接口，监听器开始监听系统消息。
 * 
 * @param watcher 指向监听器的指针（即OH_HiAppEvent_CreateWatcher接口返回的指针）。
 * @return 0：接口调用成功；-5：watcher入参空指针。
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_AddWatcher(HiAppEvent_Watcher* watcher);

/**
 * @brief 移除监听器的接口，监听器停止监听系统消息。注意：该接口仅仅使监听器停止监听系统消息，并未销毁该监听器，该监听器依然常驻内存，直至调用OH_HiAppEvent_DestroyWatcher接口，内存才会释放。
 * 
 * @param watcher 指向监听器的指针（即OH_HiAppEvent_CreateWatcher接口返回的指针）。
 * @return 0：接口调用成功；-5：watcher入参空指针；-6：还未调用OH_HiAppEvent_AddWatcher，操作顺序有误。
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_RemoveWatcher(HiAppEvent_Watcher* watcher);

/**
 * @brief 清除所有监视器保存的所有事件。
 * 
 * @since 12
 * @version 1.0
 */
void OH_HiAppEvent_ClearData();

/**
 * @brief 创建一个用于处理app事件上报的处理者。
 * 
 * @param name 处理者名称。只能包含大小写字母、数字、下划线和$，不能以数字开头，长度非空且不超过256个字符。
 * @return 接口调用成功时返回指向的新建处理者的指针，name参数异常时返回nullptr。
 * @since 18
 */
HiAppEvent_Processor* OH_HiAppEvent_CreateProcessor(const char* name);

/**
 * @brief 设置处理者事件上报路由的接口。
 * 
 * @param processor 指向处理者的指针（即OH_HiAppEvent_CreateProcessor接口返回的指针）。
 * @param appId 处理者的应用ID。
 * @param routeInfo 服务器位置信息，默认为空字符串。传入字符串长度不能超8KB，超过时会被置为默认值。
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} 接口调用成功</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} processor入参为空</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} 参数值无效</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} 用户标识无效</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE_LENGTH} 参数值长度无效</li>
 *         </ul>
 *     具体可参考{@link HiAppEvent_ErrorCode}。
 * @since 18
 */
int OH_HiAppEvent_SetReportRoute(HiAppEvent_Processor* processor, const char* appId, const char* routeInfo);

/**
 * @brief 设置处理者事件上报策略的接口。
 * 
 * @param processor 指向处理者的指针（即OH_HiAppEvent_CreateProcessor接口返回的指针）。
 * @param periodReport 事件定时上报周期，单位为秒。
 * @param batchReport 事件上报阈值，当事件条数达到阈值时上报事件。
 * @param onStartReport 数据处理者在启动时是否上报事件。配置值为true表示上报事件，false表示不上报事件。
 * @param onBackgroundReport 应用程序进入后台时是否上报事件。配置值为true表示上报事件，false表示不上报事件。
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} 接口调用成功</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} processor入参为空</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} 参数值无效</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} 用户标识无效</li>
 *         </ul>
 *     具体可参考{@link HiAppEvent_ErrorCode}。
 * @since 18
 */
int OH_HiAppEvent_SetReportPolicy(HiAppEvent_Processor* processor, int periodReport, int batchReport,
    bool onStartReport, bool onBackgroundReport);

/**
 * @brief 设置处理者上报事件的接口。
 * 
 * @param processor 指向处理者的指针（即OH_HiAppEvent_CreateProcessor接口返回的指针）。
 * @param domain 上报事件的领域。
 * @param name 上报事件的名称。
 * @param isRealTime 是否实时上报。配置为true表示实时上报，false表示不实时上报
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} 接口调用成功</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} processor入参为空</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} 参数值无效</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} 用户标识无效</li>
 *         </ul>
 *     具体可参考{@link HiAppEvent_ErrorCode}。
 * @since 18
 */
int OH_HiAppEvent_SetReportEvent(HiAppEvent_Processor* processor, const char* domain, const char* name,
    bool isRealTime);

/**
 * @brief 设置处理者自定义扩展参数的接口。
 * 
 * @param processor 指向处理者的指针（即OH_HiAppEvent_CreateProcessor接口返回的指针）。
 * @param key 参数名，长度不超过32个字符。
 * @param value 参数值，长度不超过1024个字符。
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} 接口调用成功</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} processor入参为空</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} 参数值无效</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} 用户标识无效</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE_LENGTH} 参数值长度无效</li>
 *         </ul>
 *     具体可参考{@link HiAppEvent_ErrorCode}。
 * @since 18
 */
int OH_HiAppEvent_SetCustomConfig(HiAppEvent_Processor* processor, const char* key, const char* value);

/**
 * @brief 设置处理者配置id的接口。
 * 
 * @param processor 指向处理者的指针（即OH_HiAppEvent_CreateProcessor接口返回的指针）。
 * @param configId 数据处理者配置id，自然数。
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} 接口调用成功</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} processor入参为空</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} 参数值无效</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} 用户标识无效</li>
 *         </ul>
 *     具体可参考{@link HiAppEvent_ErrorCode}。
 * @since 18
 */
int OH_HiAppEvent_SetConfigId(HiAppEvent_Processor* processor, int configId);

/**
 * @brief 设置处理者的配置名称的接口。
 * 
 * @param processor 指向处理者的指针（即OH_HiAppEvent_CreateProcessor接口返回的指针）。
 * @param configName <!--RP1-->数据处理者的配置名称。只能包含大小写字母、数字、下划线和$，不能以数字开头，长度非空且不超过256个字符。<!--RP1End-->
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} 接口调用成功</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} processor入参为空</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} 参数值无效</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} 用户标识无效</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE_LENGTH} 参数值长度无效</li>
 *         </ul>
 *     具体可参考{@link HiAppEvent_ErrorCode}。
 * @since 20
 */
int OH_HiAppEvent_SetConfigName(HiAppEvent_Processor* processor, const char* configName);

/**
 * @brief 设置处理者用户ID的接口。
 * 
 * @param processor 指向处理者的指针（即OH_HiAppEvent_CreateProcessor接口返回的指针）。
 * @param userIdNames 处理者可以上报的用户ID的name数组。
 * @param size 用户ID的name数组长度。
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS}：接口调用成功；</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL}：processor入参为空；</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE}：参数值无效；</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID}：用户标识无效；</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE_LENGTH}：参数值长度无效。</li>
 *         </ul>
 *     具体可参考{@link HiAppEvent_ErrorCode}。
 * @since 18
 */
int OH_HiAppEvent_SetReportUserId(HiAppEvent_Processor* processor, const char* const * userIdNames, int size);

/**
 * @brief 设置处理者用户属性的接口。
 * 
 * @param processor 指向处理者的指针（即OH_HiAppEvent_CreateProcessor接口返回的指针）。
 * @param userPropertyNames 处理者可以上报的用户属性数组。
 * @param size 用户属性数组的长度。
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS}：接口调用成功；</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL}：processor入参为空；</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE}：参数值无效；</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID}：用户标识无效；</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE_LENGTH}：参数值长度无效。</li>
 *         </ul>
 *     具体可参考{@link HiAppEvent_ErrorCode}。
 * @since 18
 */
int OH_HiAppEvent_SetReportUserProperty(HiAppEvent_Processor* processor, const char* const * userPropertyNames,
    int size);

/**
 * @brief 添加数据处理者的接口。开发者可添加数据处理者，用于提供事件上云功能。数据处理者的实现可预置在设备中，开发者可根据数据处理者的约束设置属性。注意：Processor的配置信息需要由数据处理者提供，
 * 目前设备内暂未预置可供交互的数据处理者，因此当前事件上云功能不可用。
 * 
 * @param processor 指向处理者的指针（即OH_HiAppEvent_CreateProcessor接口返回的指针）。
 * @return <ul>
 *         <li>调用成功时返回处理者唯一ID，大于0；</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL}：processor入参为空；</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE}：参数值无效；</li>
 *         <li>{@link HIAPPEVENT_OPERATE_FAILED}：数据处理者名称未找到或注册失败；</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID}：用户标识无效。</li>
 *         </ul>
 *     具体可参考{@link HiAppEvent_ErrorCode}。
 * @since 18
 */
int64_t OH_HiAppEvent_AddProcessor(HiAppEvent_Processor* processor);

/**
 * @brief 销毁已创建的数据处理者。注意：已创建的处理者不再使用后，需要将其销毁，释放内存，防止内存泄漏，销毁后需将对应指针置空。
 * 
 * @param processor 指向处理者的指针（即OH_HiAppEvent_CreateProcessor接口返回的指针）。
 * @since 18
 */
void OH_HiAppEvent_DestroyProcessor(HiAppEvent_Processor* processor);

/**
 * @brief 移除数据处理者的接口，处理者停止上报事件。注意：该接口仅仅使处理者停止上报事件，并未销毁该处理者，该处理者依然常驻内存，直至调用OH_HiAppEvent_DestroyProcessor接口，内存才会释放。
 * 
 * @param processorId 处理者唯一ID。
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS}：接口调用成功；</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_NOT_FOUND}：事件处理者不存在；</li>
 *         <li>{@link HIAPPEVENT_OPERATE_FAILED}：操作失败；</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID}：用户标识无效。</li>
 *         </ul>
 *     具体可参考{@link HiAppEvent_ErrorCode}。
 * @since 18
 */
int OH_HiAppEvent_RemoveProcessor(int64_t processorId);

/**
 * @brief 创建一个指向设置系统事件触发条件的配置对象的指针。
 * 
 * @return 指向设置系统事件触发条件的配置对象的指针。
 * @since 15
 */
HiAppEvent_Config* OH_HiAppEvent_CreateConfig(void);

/**
 * @brief 销毁已创建的配置对象。注意：已创建的配置对象不再使用后，需要将其销毁，释放内存，防止内存泄漏，销毁后需要将对应指针置空。
 * 
 * @param config 指向配置对象的指针（即OH_HiAppEvent_CreateConfig接口返回的指针）。
 * @since 15
 */
void OH_HiAppEvent_DestroyConfig(HiAppEvent_Config* config);

/**
 * @brief 设置配置对象中的配置项。
 * 
 * @param config 指向配置对象的指针（即OH_HiAppEvent_CreateConfig接口返回的指针）。
 * @param itemName 待设定配置项的名称。
 * @param itemValue 待设定配置项的值。
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS}：接口调用成功；</li>
 *         <li>{@link HIAPPEVENT_EVENT_CONFIG_IS_NULL}：传入的指向配置对象的指针为空；</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE}：设定的配置项无效。</li>
 *         </ul>
 *     具体可参考{@link HiAppEvent_ErrorCode}。
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} The operation is successful.</li>
 *         <li>{@link HIAPPEVENT_EVENT_CONFIG_IS_NULL} The event config is null.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} The item is invalid.</li>
 *         </ul>
 *     For details, see {@link HiAppEvent_ErrorCode}.
 * @since 15
 */
int OH_HiAppEvent_SetConfigItem(HiAppEvent_Config* config, const char* itemName, const char* itemValue);

/**
 * @brief 事件相关的配置参数设置方法。
 * 不同的事件有不同的配置项，目前仅支持以下事件：
 * MAIN_THREAD_JANK（参数配置详见{@link 主线程超时事件检测}）
 * MAIN_THREAD_JANK_V2（参数配置详见{@link 主线程超时事件检测}）
 * EVENT_APP_CRASH（参数配置详见{@link 崩溃事件介绍}），从API version 24开始支持该事件。
 * 
 * @param name 系统事件的名称。
 * @param config 指向配置对象的指针（即OH_HiAppEvent_CreateConfig接口返回的指针）。
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS}：接口调用成功；</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE}：设置的参数无效。</li>
 *         </ul>
 * 具体可参考{@link HiAppEvent_ErrorCode}。
 * @since 15
 */
int OH_HiAppEvent_SetEventConfig(const char* name, HiAppEvent_Config* config);

/**
 * @brief 框架类型。
 *
 * 建议根据不同的使用场景选择不同的框架类型。
 *
 * @since 26.0.0
 */
typedef enum OH_HiAppEvent_FrameworkType {
    /**
 * Flutter_dart类型。
 *
 * @since 26.0.0
 */
    OH_FLUTTER_DART,

    /**
 * React_native_hermes类型。
 *
 * @since 26.0.0
 */
    OH_REACT_NATIVE_HERMES,

    /**
 * Kmp_kotlin类型。
 *
 * @since 26.0.0
 */
    OH_KMP_KOTLIN
} OH_HiAppEvent_FrameworkType;

/**
 * @brief 当框架发生内存泄漏上报事件。
 * 
 * @param frameworkType 框架类型。
 * @param frameworkVersion 框架版本号。
 * @param description 框架内存泄漏事件的描述。
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} 操作成功。</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} 参数值无效。</li>
 *         <li>{@link HIAPPEVENT_OPERATE_FAILED} 系统/应用事件写入失败或时间戳提取失败。</li>
 *         <li>{@link HIAPPEVENT_REPORT_FREQUENCY_EXCEEDED} 报告频率超出。</li>
 *         </ul>
 * @since 26.0.0
 */
int OH_HiAppEvent_ReportFrameworkMemAnomaly(
    enum OH_HiAppEvent_FrameworkType frameworkType, const char* frameworkVersion, const char* description);

/**
 * @brief 系统事件类型。
 *
 *建议根据不同的使用场景选择不同的系统事件类型。
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * 崩溃事件。
     *
     * @since 26.0.0
     */
    OH_APP_CRASH = 1,

    /**
     * 应用冻屏事件。
     *
     * @since 26.0.0
     */
    OH_APP_FREEZE = 2,

    /**
     * 资源泄漏事件。
     *
     * @since 26.0.0
     */
    OH_RESOURCE_OVERLIMIT = 3,

    /**
     * 地址越界事件。
     *
     * @since 26.0.0
     */
    OH_ADDRESS_SANITIZER = 4,

    /**
     * 主线程超时事件。
     *
     * @since 26.0.0
     */
    OH_MAIN_THREAD_JANK = 5,

    /**
     * 任务执行超时事件。
     *
     * @since 26.0.0
     */
    OH_APP_HICOLLIE = 6,

    /**
     * 音频卡顿事件。
     *
     * @since 26.0.0
     */
    OH_SCROLL_JANK = 7,

    /**
     * CPU高负载事件。
     *
     * @since 26.0.0
     */
    OH_CPU_USAGE_HIGH = 8
} OH_HiAppEvent_SysEvent;

/**
 * @brief The OH_HiAppEvent_ExternalLog structure is used to describe external log information, including
 * the file path, the generation timestamp, file size, and type of system event.
 *
 * @since 26.0.0
 */
typedef struct OH_HiAppEvent_ExternalLog {
    /**
     * The log file path.
     *
     * @since 26.0.0
     */
    const char* filePath;
    /**
     * The timestamp of the file generation in ms.
     *
     * @since 26.0.0
     */
    long long generationTs;
    /**
     * The file size in kb.
     *
     * @since 26.0.0
     */
    long fileSize;
    /**
     * The system event type.
     *
     * @since 26.0.0
     */
    enum OH_HiAppEvent_SysEvent event;
} OH_HiAppEvent_ExternalLog;

/**
 * @brief OH_HiAppEvent_RegExternalLogCapacityReachedCallback函数的参数
 *    当外部日志目录容量达到时，作为回调函数。
 *
 * @param externalLogArr 外部日志信息数组。
 * @param arrLen 外部LogArr的长度。
 * @since 26.0.0
 */
typedef void (*OH_HiAppEvent_ExternalLogCapacityReachedCallback)(
    OH_HiAppEvent_ExternalLog* externalLogArr, uint32_t arrLen);

/**
 * @brief 设置外部日志目录容量达到时的回调。
 *
 * @param callback 当外部日志目录容量达到时的回调函数。
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} 操作成功。</li>
 *         <li>{@link HIAPPEVENT_OPERATE_FAILED} 操作失败。</li>
 *         </ul>
 * @since 26.0.0
 */
int OH_HiAppEvent_RegExternalLogCapacityReachedCallback(OH_HiAppEvent_ExternalLogCapacityReachedCallback callback);
#ifdef __cplusplus
}
#endif

/** @} */
#endif // HIVIEWDFX_HIAPPEVENT_H