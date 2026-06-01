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
 * @brief Enumerates the error codes used in the HiAppEvent module.
 * 
 * @since 15
 */
typedef enum {
    /**
     * The operation is successful.
     * @since 15
     */
    HIAPPEVENT_SUCCESS = 0,

    /**
     * @error Invalid param value length
     * @since 18
     */
    HIAPPEVENT_INVALID_PARAM_VALUE_LENGTH = 4,

    /**
     * @error Processor is null
     * @since 18
     */
    HIAPPEVENT_PROCESSOR_IS_NULL = -7,

    /**
     * @error Processor not found
     * @since 18
     */
    HIAPPEVENT_PROCESSOR_NOT_FOUND = -8,

    /**
     * The parameter value is invalid.
     * @since 15
     */
    HIAPPEVENT_INVALID_PARAM_VALUE = -9,

    /**
     * The event configuration is null.
     * @since 15
     */
    HIAPPEVENT_EVENT_CONFIG_IS_NULL = -10,

    /**
     * @error Operate failed
     * @since 18
     */
    HIAPPEVENT_OPERATE_FAILED = -100,

    /**
     * @error Invalid uid
     * @since 18
     */
    HIAPPEVENT_INVALID_UID = -200,
    /**
 * @error Report frequency exceeded.
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
enum EventType {
    /* Fault event type */
    FAULT = 1,

    /* Statistic event type */
    STATISTIC = 2,

    /* Security event type */
    SECURITY = 3,

    /* Behavior event type */
    BEHAVIOR = 4
};

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
 * @brief Defines the event parameter list node.
 *
 * @since 8
 * @version 1.0
 */
typedef struct ParamListNode* ParamList;

/**
 * @brief Defines the watcher for application events.
 *
 * @syscap SystemCapability.HiviewDFX.HiAppEvent
 * @since 12
 * @version 1.0
 */
typedef struct HiAppEvent_Watcher HiAppEvent_Watcher;

/**
 * @brief Defines a processor for application events.
 *
 * @since 18
 */
typedef struct HiAppEvent_Processor HiAppEvent_Processor;

/**
 * @brief Defines the configuration object used to set the conditions for triggering system events.
 *
 * @since 15
 */
typedef struct HiAppEvent_Config HiAppEvent_Config;

/**
 * @brief Passes event content to the caller. Note: The lifecycle of the object pointed by the pointer in the callback
 * is limited to the callback function. Do not use the pointer outside of the callback function. If the information
 * needs to be cached, perform a deep copy of the content pointed by the pointer.
 * 
 * @param domain Domain of the received application event.
 * @param appEventGroups Event group array.
 * @param groupLen Length of the event group array.
 * @since 12
 * @version 1.0
 */
typedef void (*OH_HiAppEvent_OnReceive)(
    const char* domain, const struct HiAppEvent_AppEventGroup* appEventGroups, uint32_t groupLen);

/**
 * @brief Invoked if the event received by the watcher meets the conditions specified by **
 * OH_HiAppEvent_SetTriggerCondition**. When the **OH_HiAppEvent_OnReceive** callback is not set in the watcher, the
 * event received by the watcher will be saved.
 * After the callback is complete, if a newly saved event meets the specified condition, the callback is invoked again.
 * 
 * @param row Number of events newly received by the watcher.
 * @param size Total size of events newly received by the watcher, in bytes. The size of a single event is the length
 *     of the JSON string converted from the event.
 * @since 12
 * @version 1.0
 */
typedef void (*OH_HiAppEvent_OnTrigger)(int row, int size);

/**
 * @brief Passes the events received by the watcher to the caller when **OH_HiAppEvent_TakeWatcherData** is used to
 * obtain the events. Note: The lifecycle of the object pointed by the pointer in the callback is limited to the
 * callback function. Do not use the pointer outside of the callback function. If the information needs to be cached,
 * perform a deep copy of the content pointed by the pointer.
 * 
 * @param events The event json string array.
 * @param eventLen Size of the event array.
 * @since 12
 * @version 1.0
 */
typedef void (*OH_HiAppEvent_OnTake)(const char* const *events, uint32_t eventLen);

/**
 * @brief Creates a pointer to a parameter list object.
 * 
 * @return Pointer to the parameter list object.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_CreateParamList(void);

/**
 * @brief Destroys a pointer to a parameter list object and releases its allocated memory.
 *
 * @param list Pointer to the parameter list object.
 * @since 8
 * @version 1.0
 */
void OH_HiAppEvent_DestroyParamList(ParamList list);

/**
 * @brief Adds an event parameter of the Boolean type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param boolean Value of the parameter to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddBoolParam(ParamList list, const char* name, bool boolean);

/**
 * @brief Adds an event parameter of the Boolean array type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param booleans Value of the parameter to be added.
 * @param arrSize Size of the parameter array to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddBoolArrayParam(ParamList list, const char* name, const bool* booleans, int arrSize);

/**
 * @brief Adds an event parameter of the int8_t type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param num Value of the parameter to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt8Param(ParamList list, const char* name, int8_t num);

/**
 * @brief Adds an event parameter of the int8_t array type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param nums Value of the parameter to be added.
 * @param arrSize Size of the parameter array to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt8ArrayParam(ParamList list, const char* name, const int8_t* nums, int arrSize);

/**
 * @brief Adds an event parameter of the int16_t type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param num Value of the parameter to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt16Param(ParamList list, const char* name, int16_t num);

/**
 * @brief Adds an event parameter of the int16_t array type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param nums Value of the parameter to be added.
 * @param arrSize Size of the parameter array to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt16ArrayParam(ParamList list, const char* name, const int16_t* nums, int arrSize);

/**
 * @brief Adds an event parameter of the int32_t type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param num Value of the parameter to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt32Param(ParamList list, const char* name, int32_t num);

/**
 * @brief Adds an event parameter of the int32_t array type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param nums Value of the parameter to be added.
 * @param arrSize Size of the parameter array to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt32ArrayParam(ParamList list, const char* name, const int32_t* nums, int arrSize);

/**
 * @brief Adds an event parameter of the int64_t type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param num Value of the parameter to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt64Param(ParamList list, const char* name, int64_t num);

/**
 * @brief Adds an event parameter of the int64_t array type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param nums Value of the parameter to be added.
 * @param arrSize Size of the parameter array to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddInt64ArrayParam(ParamList list, const char* name, const int64_t* nums, int arrSize);

/**
 * @brief Adds an event parameter of the float type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param num Value of the parameter to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddFloatParam(ParamList list, const char* name, float num);

/**
 * @brief Adds an event parameter of the float array type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param nums Value of the parameter to be added.
 * @param arrSize Size of the parameter array to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddFloatArrayParam(ParamList list, const char* name, const float* nums, int arrSize);

/**
 * @brief Adds an event parameter of the Double type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param num Value of the parameter to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddDoubleParam(ParamList list, const char* name, double num);

/**
 * @brief Adds an event parameter of the double array type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param nums Value of the parameter to be added.
 * @param arrSize Size of the parameter array to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddDoubleArrayParam(ParamList list, const char* name, const double* nums, int arrSize);

/**
 * @brief Adds a parameter of the string type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param str Value of the parameter to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddStringParam(ParamList list, const char* name, const char* str);

/**
 * @brief Adds a parameter of the string array type to the parameter list.
 * 
 * @param list Pointer to the parameter list to which parameters need to be added.
 * @param name Name of the parameter to be added.
 * @param strs Value of the parameter to be added.
 * @param arrSize Size of the parameter array to be added.
 * @return Pointer to the parameter list that contains the parameters added.
 * @since 8
 * @version 1.0
 */
ParamList OH_HiAppEvent_AddStringArrayParam(ParamList list, const char* name, const char * const *strs, int arrSize);

/**
 * @brief Logs application events whose parameters are of the list type. Before application event logging, use this API
 * to verify parameters of the events. If the verification is successful, the API writes the events to the event file.
 * 
 * @param domain Event domain. You can customize event domains as required.
 *     The value is a string that contains a maximum of 32 characters, including digits (0 to 9), letters (a to z)
 *     (A to Z), and underscore (\_). It must start with a letter and cannot end with an underscore (\_).
 * @param name Event name. You can customize event names as required.
 *     The value is a string that contains a maximum of 48 characters, including digits (0 to 9), letters (a to z)
 *     (A to Z), underscore (\_), and dollar sign (`$`). It must start with a letter or dollar sign (`$`) and end with
 *     a digit or letter.
 * @param type Event type. For details, see {@link EventType}.
 * @param list List of event parameters, each of which consists of a parameter name and a parameter value. The
 *     specifications are as follows:
 *     <br>1. The value is a string that contains a maximum of 32 characters, including digits (0 to 9), letters
 *     (a to z)(A to Z),underscore (_), and dollar sign (`$`). It must start with a letter or dollar sign (`$`) and
 *     end with a digit or letter.
 *     <br>2. The parameter value can be a string, number, Boolean, or array. The length of a string must be less than
 *     8 * 1024 characters. If this limit is exceeded, excess characters will be truncated.
 *     The element type of an array parameter can only be a string, number, or Boolean, and the number of elements
 *     must be less than 100. If this limit is exceeded, excess elements will be discarded.
 *     <br>3. The maximum number of parameters is 32. If this limit is exceeded, excess parameters will be discarded.
 * @return If the event parameters are successfully verified, **0** is returned and the event is written into the event
 *     file.
 *     If an event contains invalid parameters, a positive value is returned. The event is written into the event file
 *     after the invalid parameters are discarded.
 *     If the event parameter fails to be verified, a negative value is returned and the event is not written to the
 *     event file.
 *     <br>**0**: Parameter verification successful.
 *     <br>**-1**: Invalid event name.
 *     <br>**-4**: Invalid event domain name.
 *     <br>**-99**: Application event logging disabled.
 *     <br>**1**: Invalid event parameter name.
 *     <br>**4**: Invalid event parameter string length.
 *     <br>**5**: Invalid number of event parameters.
 *     <br>**6**: Invalid event parameter array length.
 *     <br>**8**: Duplicate event parameter name.
 * @since 8
 * @version 1.0
 */
int OH_HiAppEvent_Write(const char* domain, const char* name, enum EventType type, const ParamList list);

/**
 * @brief Configures the application event logging function. This function is used to configure the event logging
 * function and the storage quota of the event file directory.
 *
 * @param name Configuration item name The value can be {@link DISABLE} or {@link MAX_STORAGE}.
 * @param value Configuration item value. If the configuration item name is {@link DISABLE}, the value can be **true**
 *     or **false**.
 *     If the configuration item name is {@link MAX_STORAGE}, the quota value consists of only digits and a unit
 *     (including b\|k\|kb\|m\|mb\|g\|gb\|t\|tb, which are case-insensitive).
 *     The quota value must start with a digit. You can determine whether to pass the unit. If the unit is left
 *     empty, **b**(that is, byte) is used by default.
 * @return Configuration result. The value **true** indicates that the configuration is successful, and the
 *     value **false** indicates the opposite.
 * @since 8
 * @version 1.0
 */
bool OH_HiAppEvent_Configure(const char* name, const char* value);

/**
 * @brief Creates a watcher for application events.
 * 
 * @param name Watcher name.
 * @return Pointer to the new watcher if the API is called successfully; **nullptr** if the **name** parameter is
 *     invalid.
 * @since 12
 * @version 1.0
 */
HiAppEvent_Watcher* OH_HiAppEvent_CreateWatcher(const char* name);

/**
 * @brief Destroys a created watcher. Note: If a created watcher is no longer used, destroy it to release memory to
 * prevent memory leaks. After the watcher is destroyed, set its pointer to null.
 * 
 * @param watcher Pointer to the watcher (that is, the pointer returned by OH_HiAppEvent_CreateWatcher).
 * @since 12
 * @version 1.0
 */
void OH_HiAppEvent_DestroyWatcher(HiAppEvent_Watcher* watcher);

/**
 * @brief Sets the trigger condition of the **OH_HiAppEvent_OnTrigger** callback.
 * You can set the trigger condition by the number and size of new events received by the watcher, and **onTrigger**
 * timeout interval. Ensure that at least one of the trigger conditions is set on the caller side.
 * 
 * @param watcher Pointer to the watcher (that is, the pointer returned by OH_HiAppEvent_CreateWatcher).
 * @param row Row count. If the input value is greater than 0 and the number of newly received events is greater than
 *     or equal to the value of this parameter, the configured **onTrigger** callback is called.
 *     If the input value is less than or equal to 0, the number of received events is not used as the condition to
 *     trigger the **onTrigger** callback.
 * @param size Size value, Unit: bytes. If the input value is greater than 0 and the size of the newly received event
 *     is greater than or equal to the value of this parameter, the configured **onTrigger** callback is called. The
 *     size of a single event is the length of the JSON string converted from the event.
 *     If the input value is less than or equal to 0, the size of received events is not used as the condition to
 *     trigger the **onTrigger** callback.
 * @param timeOut Timeout value, in seconds. If the input value is greater than 0, the system checks the watcher for
 *     newly received events based on the timeout * 30 interval. If there are any newly received events, the configured
 *     onTrigger callback is triggered.
 *     After the callback is complete, the system checks the watcher for newly received events when the timeout * 30
 *     value expires.
 *     If the input value is less than or equal to 0, the timeout interval is not used as the condition to trigger the
 *     onTrigger callback.
 * @return **0** if the API is called successfully; **-5** if the pointer to an input parameter is null.
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_SetTriggerCondition(HiAppEvent_Watcher* watcher, int row, int size, int timeOut);

/**
 * @brief Sets the type of events to listen for. This function can be called repeatedly. You can add multiple filtering
 * conditions instead of replacing them. The watcher will receive notifications of events that meet any of the
 * filtering conditions.
 * 
 * @param watcher Pointer to the watcher (that is, the pointer returned by OH_HiAppEvent_CreateWatcher).
 * @param domain Domain of events to be listened for.
 * @param eventTypes Types of events to be listened for. The bitwise AND matching mode is used. Multiple types of
 *     events can be listened for. If the first bit is **1** (the value is **1**), fault events can be listened for.
 *     <br>If the second bit is **1** (the value is **2**), statistics events can be listened for.
 *     <br>If the third bit is **1** (the value is **4**), security events can be listened for.
 *     <br>If the fourth digit is **1**(the value is **8**), events of the listening behavior type can be listened for.
 *     <br>If four digits are **1** (the value is **15**) or 0 (the value is **0**), events of all types can be
 *     <br>listened for.
 * @param names Array of the event names.
 * @param namesLen Length of the event name array.
 * @return **0** if the API is called successfully; **-1** if the **names** parameter is invalid; **-4** if the **
 *     domain** parameter is invalid; **-5** if the pointer to an input parameter is null.
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_SetAppEventFilter(HiAppEvent_Watcher* watcher, const char* domain, uint8_t eventTypes,
    const char* const *names, int namesLen);

/**
 * @brief Sets the **onTrigger** callback.
 * If **OnReceive** is not set or is set to **nullptr**, the application events received by the watcher will be saved.
 * If the saved application events meet the trigger conditions of the **onTrigger** callback, the **onTrigger**
 * callback will be called.
 * 
 * @param watcher Pointer to the watcher (that is, the pointer returned by OH_HiAppEvent_CreateWatcher).
 * @param onTrigger Callback to be set.
 * @return **0** if the API is called successfully; **-5** if the pointer to an input parameter is null.
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_SetWatcherOnTrigger(HiAppEvent_Watcher* watcher, OH_HiAppEvent_OnTrigger onTrigger);

/**
 * @brief Sets the **onReceive** callback. When the listener detects the corresponding event, the onReceive callback is
 * called.
 * 
 * @param watcher Pointer to the watcher (that is, the pointer returned by OH_HiAppEvent_CreateWatcher).
 * @param onReceive Pointer to the callback function.
 * @return **0** if the API is called successfully; **-5** if the pointer to an input parameter is null.
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_SetWatcherOnReceive(HiAppEvent_Watcher* watcher, OH_HiAppEvent_OnReceive onReceive);

/**
 * @brief Obtains the event saved by the watcher.
 * 
 * @param watcher Pointer to the watcher (that is, the pointer returned by OH_HiAppEvent_CreateWatcher).
 * @param eventNum If the input value is less than or equal to **0**, all saved events are obtained. If the input value
 *     is greater than **0**, events are sorted by time in descending order and a specified number of saved events are
 *     obtained.
 * @param onTake Pointer to the callback. The event information is returned through this callback.
 * @return **0** if the API is called successfully; **-5** if the pointer to an input parameter is null; **-6** if **
 *     OH_HiAppEvent_AddWatcher** has not been called to add a watcher.
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_TakeWatcherData(HiAppEvent_Watcher* watcher, uint32_t eventNum, OH_HiAppEvent_OnTake onTake);

/**
 * @brief Adds a watcher. Once a watcher is added, it starts to listen for system messages.
 *
 * @param watcher Pointer to the watcher (that is, the pointer returned by OH_HiAppEvent_CreateWatcher).
 * @return **0** if the API is called successfully; **-5** if the pointer to an input parameter is null.
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_AddWatcher(HiAppEvent_Watcher* watcher);

/**
 * @brief Removes a watcher. Once a watcher is removed, it stops listening for system messages. Note: This API only
 * enables the watcher to stop listening for system messages. It does not destroy the watcher. The watcher still
 * resides in the memory until the OH_HiAppEvent_DestroyWatcher API is called.
 * 
 * @param watcher Pointer to the watcher (that is, the pointer returned by OH_HiAppEvent_CreateWatcher).
 * @return **0** if the API is called successfully; **-5** if the pointer to an input parameter is null; **-6** if **
 *     OH_HiAppEvent_AddWatcher** has not been called to add a watcher.
 * @since 12
 * @version 1.0
 */
int OH_HiAppEvent_RemoveWatcher(HiAppEvent_Watcher* watcher);

/**
 * @brief Clears the events saved by all watchers.
 * 
 * @since 12
 * @version 1.0
 */
void OH_HiAppEvent_ClearData();

/**
 * @brief Creates a processor for application events.
 * 
 * @param name Processor name, which can contain only letters, digits, underscores (_), and dollar signs ($). It cannot
 *     start with a digit and cannot exceed 256 characters.
 * @return Pointer to the new processor if the API is called successfully; **nullptr** if the **name** parameter is
 *     invalid.
 * @since 18
 */
HiAppEvent_Processor* OH_HiAppEvent_CreateProcessor(const char* name);

/**
 * @brief Sets the report route for the processor.
 * 
 * @param processor Pointer to the processor, that is, the pointer returned by **OH_HiAppEvent_CreateProcessor**.
 * @param appId Application ID of the processor.
 * @param routeInfo Server location information. The default value is an empty string. The string length cannot exceed
 *     8 KB. Otherwise, the default value is used.
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} The operation is successful.</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} The processor is nullptr.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} Invalid Param value.</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} Invalid uid.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE_LENGTH} Invalid param value length.</li>
 *         </ul>
 *     For details, see {@link HiAppEvent_ErrorCode}.
 * @since 18
 */
int OH_HiAppEvent_SetReportRoute(HiAppEvent_Processor* processor, const char* appId, const char* routeInfo);

/**
 * @brief Sets the report policy for the processor.
 * 
 * @param processor Pointer to the processor, that is, the pointer returned by **OH_HiAppEvent_CreateProcessor**.
 * @param periodReport Period for reporting events, in seconds.
 * @param batchReport Threshold for reporting events. When the number of events reaches the threshold, an event is
 *     reported.
 * @param onStartReport Whether to report events during startup. **true**: yes; **false**: no.
 * @param onBackgroundReport Whether to report events after an application switches to the background. **true**:
 *     yes; **false**: no.
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} The operation is successful.</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} The processor is nullptr.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} Invalid Param value.</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} Invalid uid.</li>
 *         </ul>
 *     For details, see {@link HiAppEvent_ErrorCode}.
 * @since 18
 */
int OH_HiAppEvent_SetReportPolicy(HiAppEvent_Processor* processor, int periodReport, int batchReport,
    bool onStartReport, bool onBackgroundReport);

/**
 * @brief Sets the report event for the processor.
 * 
 * @param processor Pointer to the processor, that is, the pointer returned by **OH_HiAppEvent_CreateProcessor**.
 * @param domain Domain of the report event.
 * @param name Name of the report event.
 * @param isRealTime Whether to report events in real time. The value **true** means to report events in real time,
 *     and **false** means the opposite.
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} The operation is successful.</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} The processor is nullptr.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} Invalid Param value.</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} Invalid uid.</li>
 *         </ul>
 *     For details, see {@link HiAppEvent_ErrorCode}.
 * @since 18
 */
int OH_HiAppEvent_SetReportEvent(HiAppEvent_Processor* processor, const char* domain, const char* name,
    bool isRealTime);

/**
 * @brief Sets the custom extension parameters of the processor.
 * 
 * @param processor Pointer to the processor, that is, the pointer returned by **OH_HiAppEvent_CreateProcessor**.
 * @param key Parameter name, which contains a maximum of 32 characters.
 * @param value Parameter value, which contains a maximum of 1024 characters.
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} The operation is successful.</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} The processor is nullptr.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} Invalid Param value.</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} Invalid uid.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE_LENGTH} Invalid param value length.</li>
 *         </ul>
 *     For details, see {@link HiAppEvent_ErrorCode}.
 * @since 18
 */
int OH_HiAppEvent_SetCustomConfig(HiAppEvent_Processor* processor, const char* key, const char* value);

/**
 * @brief Sets the configuration ID of the processor.
 * 
 * @param processor Pointer to the processor, that is, the pointer returned by **OH_HiAppEvent_CreateProcessor**.
 * @param configId Configuration ID of the processor, which is a natural number.
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} The operation is successful.</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} The processor is nullptr.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} Invalid Param value.</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} Invalid uid.</li>
 *         </ul>
 *     For details, see {@link HiAppEvent_ErrorCode}.
 * @since 18
 */
int OH_HiAppEvent_SetConfigId(HiAppEvent_Processor* processor, int configId);

/**
 * @brief Sets the configuration name of the processor.
 * 
 * @param processor Pointer to the processor, that is, the pointer returned by **OH_HiAppEvent_CreateProcessor**.
 * @param configName Configuration name of the data processor, which can contain only letters, digits,
 *     underscores (_), and dollar signs ($). It cannot start with a digit and cannot exceed 256 characters.
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} The operation is successful.</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} The processor is nullptr.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} Invalid Param value.</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} Invalid uid.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE_LENGTH} Invalid param value length.</li>
 *         </ul>
 *     For details, see {@link HiAppEvent_ErrorCode}.
 * @since 20
 */
int OH_HiAppEvent_SetConfigName(HiAppEvent_Processor* processor, const char* configName);

/**
 * @brief Sets the report user ID of the processor.
 * 
 * @param processor Pointer to the processor, that is, the pointer returned by **OH_HiAppEvent_CreateProcessor**.
 * @param userIdNames Name array of user IDs that can be reported by the processor.
 * @param size Length of the name array of user IDs.
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} The operation is successful.</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} The processor is nullptr.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} Invalid Param value.</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} Invalid uid.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE_LENGTH} Invalid param value length.</li>
 *         </ul>
 *     For details, see {@link HiAppEvent_ErrorCode}.
 * @since 18
 */
int OH_HiAppEvent_SetReportUserId(HiAppEvent_Processor* processor, const char* const * userIdNames, int size);

/**
 * @brief Sets the report user property of the processor.
 * 
 * @param processor Pointer to the processor, that is, the pointer returned by **OH_HiAppEvent_CreateProcessor**.
 * @param userPropertyNames Name array of user properties that can be reported by the processor.
 * @param size Length of the name array of user properties.
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} The operation is successful.</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL} The processor is nullptr.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} Invalid Param value.</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID} Invalid uid.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE_LENGTH} Invalid param value length.</li>
 *         </ul>
 *     For details, see {@link HiAppEvent_ErrorCode}.
 * @since 18
 */
int OH_HiAppEvent_SetReportUserProperty(HiAppEvent_Processor* processor, const char* const * userPropertyNames,
    int size);

/**
 * @brief Adds a processor. You can add a processor to migrate event data to the cloud. You can preset the
 * implementation of the processor on the device and set its properties based on its constraints. Note that the
 * configuration information of **Processor** must be provided by the data processor. Yet, as no data processor is
 * preset in the device for interaction for the moment, migrating events to the cloud is unavailable.
 * 
 * @param processor Pointer to the processor, that is, the pointer returned by **OH_HiAppEvent_CreateProcessor**.
 * @return <ul>
 *         <li>process id if set is successful.</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_IS_NULL}: The processor is nullptr.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE}: Invalid Param value.</li>
 *         <li>{@link HIAPPEVENT_OPERATE_FAILED}: Name not found or register processor error.</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID}: Invalid uid.</li>
 *         </ul>
 *     For details, see {@link HiAppEvent_ErrorCode}.
 * @since 18
 */
int64_t OH_HiAppEvent_AddProcessor(HiAppEvent_Processor* processor);

/**
 * @brief Destroys a processor. Note: If a processor is no longer used, destroy it to release memory to prevent memory
 * leaks. After the processor is destroyed, set its pointer to null.
 * 
 * @param processor Pointer to the processor, that is, the pointer returned by **OH_HiAppEvent_CreateProcessor**.
 * @since 18
 */
void OH_HiAppEvent_DestroyProcessor(HiAppEvent_Processor* processor);

/**
 * @brief Removes a processor. Once a processor is removed, it stops reporting events. Note: This API only stops the
 * processor reporting events but does not destroy the processor. You can call **OH_HiAppEvent_DestroyProcessor** to
 * destroy the processor and release the memory.
 * 
 * @param processorId Unique ID of a processor.
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS}: The operation is successful.</li>
 *         <li>{@link HIAPPEVENT_PROCESSOR_NOT_FOUND}: Processor not add.</li>
 *         <li>{@link HIAPPEVENT_OPERATE_FAILED}: The operation is failed.</li>
 *         <li>{@link HIAPPEVENT_INVALID_UID}: Invalid uid.</li>
 *         </ul>
 *     For details, see {@link HiAppEvent_ErrorCode}.
 * @since 18
 */
int OH_HiAppEvent_RemoveProcessor(int64_t processorId);

/**
 * @brief Creates a pointer to the configuration object that sets the conditions for triggering system events.
 * 
 * @return Pointer to the configuration object that sets the conditions for triggering system events.
 * @since 15
 */
HiAppEvent_Config* OH_HiAppEvent_CreateConfig(void);

/**
 * @brief Destroys a configuration object. Note: If a configuration object is no longer used, destroy it to release
 * memory to prevent memory leaks. After the object is destroyed, set its pointer to null.
 * 
 * @param config Pointer to the configuration object, that is, the pointer returned by
 *     the **OH_HiAppEvent_CreateConfig** API.
 * @since 15
 */
void OH_HiAppEvent_DestroyConfig(HiAppEvent_Config* config);

/**
 * @brief Sets the items in the configuration object.
 *
 * @param config Pointer to the configuration object, that is, the pointer returned by
 *     the **OH_HiAppEvent_CreateConfig** API.
 * @param itemName Name of the configuration item.
 * @param itemValue Value of the configuration item.
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
 * @brief Sets event configuration parameters.
 * Configuration items vary depending on events. Currently, only the following events are supported:
 * **MAIN_THREAD_JANK**. (For details about the parameter configuration, see {@link Main Thread Jank Event Overview}.)
 * **MAIN_THREAD_JANK_V2**. (For details about the parameter configuration, see {@link Main Thread Jank Event Overview}.
 * )
 * **EVENT_APP_CRASH**. (For details about the parameter configuration, see {@link Crash Event Overview}.) This event
 * is supported since API version 24.
 * 
 * @param name Name of the system event.
 * @param config Pointer to the configuration object, that is, the pointer returned by
 *     the **OH_HiAppEvent_CreateConfig** API.
 * @return <ul>
 *         <li>{@link HIAPPEVENT_SUCCESS} The operation is successful.</li>
 *         <li>{@link HIAPPEVENT_INVALID_PARAM_VALUE} The config is invalid.</li>
 *         </ul>
 *     For details, see {@link HiAppEvent_ErrorCode}.
 * @since 15
 */
int OH_HiAppEvent_SetEventConfig(const char* name, HiAppEvent_Config* config);

/**
 * @brief Framework types.
 *
 * You are advised to select framework types based on their respective usage scenarios.
 *
 * @since 26.0.0
 */
typedef enum OH_HiAppEvent_FrameworkType {
    /**
     * Flutter_dart type.
     *
     * @since 26.0.0
    */
    OH_FLUTTER_DART,

    /**
     * React_native_hermes type.
     *
     * @since 26.0.0
     */
    OH_REACT_NATIVE_HERMES,

    /**
     * Kmp_kotlin type.
     *
     * @since 26.0.0
     */
    OH_KMP_KOTLIN
} OH_HiAppEvent_FrameworkType;

/**
 * @brief When a framework has a memory leak report event.
 * 
 * @param frameworkType Framework type.
 * @param frameworkVersion Framework version.
 * @param description Description of the framework memory leak event.
 * @return report result.
 *     {@link HIAPPEVENT_SUCCESS} The operation is successful.
 *     {@link HIAPPEVENT_INVALID_PARAM_VALUE} Invalid Param value.
 *     {@link HIAPPEVENT_OPERATE_FAILED} System/application event write failed, or timestamp retrieval failed.
 *     {@link HIAPPEVENT_REPORT_FREQUENCY_EXCEEDED} Report frequency exceeded.
 * @since 26.0.0
 */
int OH_HiAppEvent_ReportFrameworkMemAnomaly(
    enum OH_HiAppEvent_FrameworkType frameworkType, const char* frameworkVersion, const char* description);
#ifdef __cplusplus
}
#endif

/** @} */
#endif // HIVIEWDFX_HIAPPEVENT_H