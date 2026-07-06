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
 * @addtogroup HiCollie
 * @{
 *
 * @brief Provides the ability to detect thread stuck or jank of your own business thread
 * pls note it should not be the same as main thread.
 *
 * You can use it in these two scenario:
 * (1)The Business thread stuck for 6 seconds;
 * (2)The Business thread jank for a short time, usually it is less than one second.
 *
 * @since 12
 */

/**
 * @file hicollie.h
 *
 * @brief Defines the interface of the HiCollie module.
 *
 * @library libohhicollie.so
 * @kit PerformanceAnalysisKit
 * @syscap SystemCapability.HiviewDFX.HiCollie
 * @since 12
 */

#ifndef HIVIEWDFX_HICOLLIE_H
#define HIVIEWDFX_HICOLLIE_H

#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @brief Enumerates the error codes used in the HiCollie module.
 *
 * @since 12
 */
typedef enum HiCollie_ErrorCode {
    /**
     * The operation is successful.
     *
     * @since 12
     */
    HICOLLIE_SUCCESS = 0,
    /**
     * The parameter is invalid.
     *
     * @since 12
     */
    HICOLLIE_INVALID_ARGUMENT = 401,
    /**
     * The called thread is incorrect.
     *
     * @since 12
     */
    HICOLLIE_WRONG_THREAD_CONTEXT = 29800001,
    /**
     * The remote call fails.
     *
     * @since 12
     */
    HICOLLIE_REMOTE_FAILED = 29800002,
    /**
     * The timer name is invalid.
     *
     * @since 18
     */
    HICOLLIE_INVALID_TIMER_NAME = 29800003,
    /**
     * The function execution timeout value is invalid.
     *
     * @since 18
     */
    HICOLLIE_INVALID_TIMEOUT_VALUE = 29800004,
    /**
     * The process to be accessed is incorrect.
     *
     * @since 18
     */
    HICOLLIE_WRONG_PROCESS_CONTEXT = 29800005,
    /**
     * The pointer used to save the returned timer ID is null.
     *
     * @since 18
     */
    HICOLLIE_WRONG_TIMER_ID_OUTPUT_PARAM = 29800006,
    /**
     * The reporting frequency exceeds the limit.
     *
     * @since 24
     */
    OH_HICOLLIE_REACH_REPORT_LIMIT = 29800007,
} HiCollie_ErrorCode;

/**
 * @brief Checks whether a service thread is stuck.
 * This function is called by HiCollie every 3 seconds in a service thread.
 * For example, this function can be used to send a message to a service thread and set a flag after the service thread
 * receives the message. Then the flag is checked to determine whether the service thread is stuck.
 *
 * @since 12
 */
typedef void (*OH_HiCollie_Task)(void);

/**
 * @brief In jank scenario, you need to insert two stub functions before and after
 * each event processing of your business thread.
 * By checking these two function executing timestamp, HiCollie will know consuming time for every event.
 * If it exceeds the preset threshold, a jank event will be reported.
 * This is the stub function inserted before each event processing.
 *
 * @param eventName Business thread processing event name.
 * @since 12
 */
typedef void (*OH_HiCollie_BeginFunc)(const char* eventName);

/**
 * @brief Records the end time when a service thread processes an event. This function is used in the jank event
 * detection.
 * HiCollie checks the execution time of the event. If the duration exceeds the preset threshold, a jank event is
 * reported.
 * This is the stub function inserted after each event processing.
 *
 * @param eventName Name of the service thread event.
 * @since 12
 */
typedef void (*OH_HiCollie_EndFunc)(const char* eventName);

/**
 * @brief Defines the parameters of the jank event detection. Note that this struct is supported since API 12.
 *
 * @since 12
 */
typedef struct HiCollie_DetectionParam {
    /**
     * In jank scenario, it's the threshold exceed which sample stack will be collected.
     *
     * @since 12
     */
    int sampleStackTriggerTime;
    /**
     * Extended parameter for future use.
     *
     * @since 12
     */
    int reserved;
} HiCollie_DetectionParam;

/**
 * @brief Registers a callback used to periodically detect service thread stuck events.
 * By default, the **BUSSINESS_THREAD_BLOCK_3S** event is reported when the thread is blocked for 3s and the **
 * BUSSINESS_THREAD_BLOCK_6S** event is reported when the thread is blocked for 6s.
 *
 * @param task A periodic detection task that is executed every 3 seconds to check whether a service thread is stuck.
 * @return {@link HICOLLIE_SUCCESS} 0 - Operation successful.
 * {@link HICOLLIE_WRONG_THREAD_CONTEXT} 29800001 - Incorrect calling thread. This function should be called in a non-
 * main thread.
 * For details, see {@link HiCollie_ErrorCode}.
 * @since 12
 */
HiCollie_ErrorCode OH_HiCollie_Init_StuckDetection(OH_HiCollie_Task task);

/**
 * @brief Registers a callback used to periodically detect service thread stuck events.
 * You can set the interval for the stuck event detection. The value range is [3, 15], in seconds.
 *
 * @param task Periodic detection task that is executed every **stuckTimeout** time to check whether a service thread
 * is stuck.
 * @param stuckTimeout Threshold for reporting a service thread stuck event, in seconds. When the task execution time
 * exceeds the value of **stuckTimeout**, a stuck warning event is reported. When the task execution time exceeds twice
 * the value of **stuckTimeout**, a stuck event is reported.
 * The maximum value is **15s** and the minimum value is **3s**.
 * @return {@link HICOLLIE_SUCCESS} 0 - Operation successful.
 * {@link HICOLLIE_INVALID_ARGUMENT} 401 - Invalid detection time.
 * {@link HICOLLIE_WRONG_THREAD_CONTEXT} 29800001 - Incorrect calling thread. This function should be called in a non-
 * main thread.
 * For details, see {@link HiCollie_ErrorCode}.
 * @since 18
 */
HiCollie_ErrorCode OH_HiCollie_Init_StuckDetectionWithTimeout(OH_HiCollie_Task task, uint32_t stuckTimeout);

/**
 * @brief Registers a callback used to detect service thread jank events.
 * To monitor service thread jank events, you can implement two callbacks as instrumentation functions, placing them
 * before and after the service thread event.
 *
 * @param beginFunc Function used before the service thread event detection.
 * @param endFunc Function used after the service thread event detection.
 * @param param Extended parameter for future use.
 * @return {@link HICOLLIE_SUCCESS} 0 - Operation successful.
 * {@link HICOLLIE_INVALID_ARGUMENT} 401 - The begin and end functions are not both set or both unset; they must either
 * both have valid values or both be empty.
 * {@link HICOLLIE_WRONG_THREAD_CONTEXT} 29800001 - Incorrect calling thread. This function should be called in a non-
 * main thread.
 * For details, see {@link HiCollie_ErrorCode}.
 * @since 12
 */
HiCollie_ErrorCode OH_HiCollie_Init_JankDetection(OH_HiCollie_BeginFunc* beginFunc,
    OH_HiCollie_EndFunc* endFunc, HiCollie_DetectionParam param);

/**
 * @brief Reports a service thread stuck event and generates logs to help locate application stuck issues.
 * Call **OH_HiCollie_Init_StuckDetection()** or **OH_HiCollie_Init_StuckDetectionWithTimeout()** to initialize the
 * detection task.
 * If the task times out, call **OH_HiCollie_Report()** to report the stuck event based on the service logic.
 *
 * @param isSixSecond Pointer to a Boolean value.  If the service thread is stuck for 6s, the value is **true**. If the
 * service thread is stuck for 3s, the value is **false**.
 * @return {@link HICOLLIE_SUCCESS} 0 - Operation successful.
 * {@link HICOLLIE_INVALID_ARGUMENT} 401 - The begin and end functions are not both set or both unset; they must either
 * both have valid values or both be empty.
 * {@link HICOLLIE_WRONG_THREAD_CONTEXT} 29800001 - Incorrect calling thread. This function should be called in a non-
 * main thread.
 * {@link HICOLLIE_REMOTE_FAILED} 29800002 - Remote call error. The IPC remote service fails to be called.
 * For details, see {@link HiCollie_ErrorCode}.
 * @since 12
 */
HiCollie_ErrorCode OH_HiCollie_Report(bool* isSixSecond);

/**
 * @brief Reports an application input unresponsive event and generates logs to help locate application freeze issues.
 * On a PC or tablet, a dialog box is displayed, prompting the user to wait or close the application. On other devices,
 * no dialog box is displayed. You are advised to use this API in either of the following ways:
 * Method 1 (recommended): Use this API together with **OH_HiCollie_Report**, **OH_HiCollie_Init_StuckDetection**, or **
 * OH_HiCollie_Init_StuckDetectionWithTimeout**. The service thread periodically checks whether it is frozen through
 * the preceding APIs. When the service thread is frozen and an input event (such as screen tapping, mouse clicking, or
 * keyboard input) occurs, the service thread calls **OH_HiCollie_ReportInputBlock**.
 * Method 2: If the service thread can detect its own freeze without using the **OH_HiCollie_Report**, **
 * OH_HiCollie_Init_StuckDetection**, or **OH_HiCollie_Init_StuckDetectionWithTimeout** API, the application calls the *
 * *OH_HiCollie_ReportInputBlock** API based on the service thread freeze and input event.
 *
 * @return {@link HICOLLIE_SUCCESS} 0 - Operation successful.
 * {@link HICOLLIE_REMOTE_FAILED} 29800002 - Remote call error. The IPC remote service fails to be called.
 * For details, see {@link HiCollie_ErrorCode}.
 * @since 24
 */
HiCollie_ErrorCode OH_HiCollie_ReportInputBlock();

/**
 * @brief Triggered when {@link OH_HiCollie_CancelTimer} is not called within
 * the custom task timeout period after {@link OH_HiCollie_SetTimer} is called.
 *
 * @since 18
 */
typedef void (*OH_HiCollie_Callback)(void*);

/**
 * @brief Enumerates the actions to be performed when a function times out.
 *
 * @since 18
 */
typedef enum HiCollie_Flag {
    /**
     * Default action is generate log file and do recovery.
     *
     * @since 18
     */
    HICOLLIE_FLAG_DEFAULT = (~0),
    /**
     * Do nothing except call the callback function
     *
     * @since 18
     */
    HICOLLIE_FLAG_NOOP = (0),
    /**
     * Generate log file
     *
     * @since 18
     */
    HICOLLIE_FLAG_LOG = (1 << 0),
    /**
     * Do recovery by call the exit syscall
     *
     * @since 18
     */
    HICOLLIE_FLAG_RECOVERY = (1 << 1)
} HiCollie_Flag;

/**
 * @brief Defines the input parameters of the **OH_HiCollie_SetTimer** function.
 *
 * @since 18
 */
typedef struct HiCollie_SetTimerParam {
    /**
     * The timer name
     *
     * @since 18
     */
    const char *name;
    /**
     * Task timeout threshold, in seconds.
     *
     * @since 18
     */
    unsigned int timeout;
    /**
     * Callback executed when a timeout occurs.
     *
     * @since 18
     */
    OH_HiCollie_Callback func;
    /**
     * The callback function's parameter.
     *
     * @since 18
     */
    void *arg;
    /**
     * Action performed when a timeout occurs. For details, see {@link HiCollie_Flag}.
     *
     * @since 18
     */
    HiCollie_Flag flag;
} HiCollie_SetTimerParam;

/**
 * @brief Registers a timer to check whether the execution time of a function or code block exceeds the custom time.
 * This API is used together with the **OH_HiCollie_CancelTimer** API.
 *
 * @param param Input parameters.
 * @param id Pointer to the returned timer ID, which should not be NULL.
 * @return {@link HICOLLIE_SUCCESS} 0 - Operation successful.
 * {@link HICOLLIE_INVALID_TIMER_NAME} 29800003 - Invalid timer name. The timer name cannot be NULL or an empty string.
 * {@link HICOLLIE_INVALID_TIMEOUT_VALUE} 29800004 - Invalid timeout value.
 * {@link HICOLLIE_WRONG_PROCESS_CONTEXT} 29800005 - Invalid process context for detection. This function cannot be
 * called in the **appspawn** and **nativespawn** processes.
 * {@link HICOLLIE_WRONG_TIMER_ID_OUTPUT_PARAM} 29800006 - The pointer used to save the returned timer ID is NULL.
 * For details, see {@link HiCollie_ErrorCode}.
 * @since 18
 */
HiCollie_ErrorCode OH_HiCollie_SetTimer(HiCollie_SetTimerParam param, int *id);

/**
 * @brief Cancels a timer based on the ID.
 * This API is used together with the **OH_HiCollie_SetTimer** API. It must be used after the function or code block is
 * executed.
 * If a timer is not canceled within the custom time, a callback function is executed to generate fault logs for the
 * specified timeout event.
 *
 * @param id Timer ID updated after the {@link OH_HiCollie_SetTimer} function is executed.
 * @since 18
 */
void OH_HiCollie_CancelTimer(int id);

/**
 * @brief Enumerates the freeze event types returned by **FreezeCallback**.
 *
 * @since 24
 */
typedef enum OH_HiCollie_Freeze_Type {
    /**
     * @brief The main thread times out for one period.
     *
     * @since 24
     */
    OH_THREAD_BLOCK_3S,
    /**
     * @brief The main thread times out for two periods.
     *
     * @since 24
     */
    OH_THREAD_BLOCK_6S,
    /**
     * @brief The ability lifecycle times out for one period.
     *
     * @since 24
     */
    OH_LIFECYCLE_HALF_TIMEOUT,
    /**
     * @brief The ability lifecycle times out for two periods.
     *
     * @since 24
     */
    OH_LIFECYCLE_TIMEOUT,
    /**
     * @brief Input event processing timeout.
     *
     * @since 24
     */
    OH_APP_INPUT_BLOCK,
    /**
     * @brief A 3s freeze event is reported through {@link OH_HiCollie_Report}.
     *
     * @since 24
     */
    OH_BUSINESS_THREAD_BLOCK_3S,
    /**
     * @brief A 6s freeze event is reported through {@link OH_HiCollie_Report}.
     *
     * @since 24
     */
    OH_BUSINESS_THREAD_BLOCK_6S,
    /**
     * @brief A freeze event is reported through {@link OH_HiCollie_ReportInputBlock}.
     *
     * @since 24
     */
    OH_BUSINESS_INPUT_BLOCK
} OH_HiCollie_Freeze_Type;

/**
 * @brief the freeze callback used in {@link OH_HiCollie_SetFreezeCallback}
 *
 * @param type Freeze event type in {@link OH_HiCollie_Freeze_Type}
 * @param buffer log buffer provided by the system, whose content will be moved to APP_FREEZE or APP_HICOLLIE
 *                 HiAppEvent
 * @param size buffer size can be used
 * @return used buffer size
 * @since 24
 */
typedef size_t (*OH_HiCollie_FreezeCallback)(OH_HiCollie_Freeze_Type type, void* buffer, size_t size);

/**
 * @brief Sets the freeze event callback in the system. The system calls this function when a freeze event occurs.
 *
 * @param callback Callback function.
 * @return Callback function passed last time in the current process.
 * @since 24
 */
void* OH_HiCollie_SetFreezeCallback(OH_HiCollie_FreezeCallback callback);

/**
 * @brief Reports a freeze event of a process. In this case, a **HiAppEvent** event of the **APP_HICOLLIE** type is
 * generated.
 *
 * @param isFreezeEvent Type of the reported event. **true**: A 6s freeze event. **false**: A 3s freeze event.
 * @return **HICOLLIE_SUCCESS**: 0 - The operation is successful.
 * **OH_HICOLLIE_REACH_REPORT_LIMIT**: 29800007 - The reporting frequency is too high.
 * @since 24
 */
HiCollie_ErrorCode OH_HiCollie_AssociateProcessReport(bool isFreezeEvent);
#ifdef __cplusplus
}
#endif
/** @} */

#endif // HIVIEWDFX_HICOLLIE_H
