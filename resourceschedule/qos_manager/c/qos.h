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
 * @addtogroup QoS
 * @{
 *
 * @brief QoS provides APIs.
 *
 * @since 12
 */
/**
 * @file qos.h
 *
 * @brief Declares the QoS interfaces in C.
 *
 * Quality-of-service (QoS) refers to the priority scheduling attribute of tasks
 * in OpenHarmony. Developers can use QoS to categorize tasks to be executed to
 * indicate the degree of their relevance to user interactions, the system can
 * schedule the time and running order of tasks according to the QoS set by the tasks.
 *
 * @library libqos.so
 * @kit KernelEnhanceKit
 * @syscap SystemCapability.Resourceschedule.QoS.Core
 * @since 12
 */
#ifndef QOS_H

#define QOS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the QoS levels.
 *
 * @since 12
 */
typedef enum QoS_Level {
    /**
     * @brief Means the QoS level is background.
     */
    QOS_BACKGROUND = 0,

    /**
     * @brief Means the QoS level is utility.
     */
    QOS_UTILITY,

    /**
     * @brief Means the QoS level is default.
     */
    QOS_DEFAULT,

    /**
     * @brief Means the QoS level is user-initiated.
     */
    QOS_USER_INITIATED,

    /**
     * @brief Means the QoS level is user-request.
     */
    QOS_DEADLINE_REQUEST,

    /**
     * @brief Means the QoS level is user-interactive.
     */
    QOS_USER_INTERACTIVE
} QoS_Level;

/**
 * @brief Sets the QoS level for the calling thread.
 *
 * @param level Sets the QoS level. For details, see {@link QoS_Level}.
 * @return **0** is returned if the operation is successful; **-1** is returned if level is out of range or internal
 *     error failed.
 * @see QoS_Level
 * @since 12
 */
int OH_QoS_SetThreadQoS(QoS_Level level);

/**
 * @brief Cancels the QoS level of the calling thread.
 *
 * @return **0** is returned if the operation is successful; **-1** is returned if level is out of range or internal
 *     error failed.
 * @see QoS_Level
 * @since 12
 */
int OH_QoS_ResetThreadQoS();

/**
 * @brief Obtains the QoS level of the calling thread.
 *
 * @param level QoS level of the calling thread. The parameter is an output parameter and is written to this variable
 *     in {@link QoS_Level} format.
 * @return **0** is returned if the operation is successful; **-1** is returned if level is out of range or internal
 *     error failed.
 * @see QoS_Level
 * @since 12
 */
int OH_QoS_GetThreadQoS(QoS_Level *level);

/**
 * @brief Session id
 *
 * @since 20
 */
typedef unsigned int OH_QoS_GewuSession;

#define OH_QOS_GEWU_INVALID_SESSION_ID (static_cast<OH_QoS_GewuSession>(0xffffffffU))
/**
 * @brief Request id
 *
 * @since 20
 */
typedef unsigned int OH_QoS_GewuRequest;

#define OH_QOS_GEWU_INVALID_REQUEST_ID (static_cast<OH_QoS_GewuRequest>(0xffffffffU))
/**
 * @brief Enumerates the Gewu error codes.
 *
 * @since 20
 */
typedef enum {
    /**
     * @brief Means the result is OK
     *
     * @since 20
     */
    OH_QOS_GEWU_OK     = 0,
    /**
     * @brief No permission
     *
     * @since 20
     */
    OH_QOS_GEWU_NOPERM = 201,
    /**
     * @brief No memory
     *
     * @since 20
     */
    OH_QOS_GEWU_NOMEM  = 203,
    /**
     * @brief Invalid input
     *
     * @since 20
     */
    OH_QOS_GEWU_INVAL  = 401,
    /**
     * @brief Already exists
     *
     * @since 20
     */
    OH_QOS_GEWU_EXIST  = 501,
    /**
     * @brief No entity
     *
     * @since 20
     */
    OH_QOS_GEWU_NOENT  = 502,
    /**
     * @brief Subsystem does not exist
     *
     * @since 20
     */
    OH_QOS_GEWU_NOSYS  = 801,
    /**
     * @brief All other faults
     *
     * @since 20
     */
    OH_QOS_GEWU_FAULT  = 901
} OH_QoS_GewuErrorCode;

/**
 * @brief Defines a struct for the return results of the **OH_QoS_GewuCreateSession()** API.
 * If the operation is successful,
 * the created session is returned. If the operation fails, the corresponding error code is returned.
 * @param session The created session id
 * @param error Error code of CreateSession
 *              - OH_QOS_GEWU_OK will be returned if the session is created successfully.
 *              - OH_QOS_GEWU_NOMEM will be returned if the system does not have sufficient memory to
 *                create the session.
 *
 * @since 20
 */
typedef struct {
    /** 
     * @brief Handle of the session
     * 
     * @since 20
     */
    OH_QoS_GewuSession session;
    /** 
     * @brief Error code of creating a session
     * 
     * @since 20
     */
    OH_QoS_GewuErrorCode error;
} OH_QoS_GewuCreateSessionResult;

/**
 * @brief Defines a struct for the return result of the **OH_QoS_GewuSubmitRequest()** API.
 * If the operation is successful, a handle of the request is returned.
 * If the operation fails, the corresponding error code is returned.
 * @param request The created request id
 * @param error Error code of request submission.
 *              - OH_QOS_GEWU_OK will be returned if the request is submitted successfully.
 *              - OH_QOS_GEWU_NOMEM will be returned if the system does not have sufficient memory to
 *                submit the request.
 *
 * @since 20
 */
typedef struct {
    /** 
     * @brief Handle of the request
     * @since 20
     */
    OH_QoS_GewuRequest request;
    /**
     * @brief Error code of submitting a Gewu request
     * @since 20
     */
    OH_QoS_GewuErrorCode error;
} OH_QoS_GewuSubmitRequestResult;

/**
 * @brief Callback to receive response of the request.
 *
 * @param context User context handle specified when the request is submitted.
 * @param reponse The json string of the response, including the following parameters:
 *        - message: A message that contains the following fields.
 *            - role: string. Must be "assistant".
 *            - content: string. The message generated by the model in response to user messages.
 *        - finish_reason: string or null. The reason the inference stopped. Possible values:
 *            - null: Not finished yet, only present in streaming mode.
 *            - "stop": The model stopped natually.
 *            - "abort": The inference request was aborted.
 *            - "length": The generated tokens reached the limit.
 *
 * @since 20
 */
typedef void (*OH_QoS_GewuOnResponse)(void* context, const char* response);

/**
 * @brief Creates a Gewu session. The lifecycle of the session object starts when the **CreateSession** function
 * returns and ends when **DestroySession** is called.
 *
 * `const char* attributes`: JSON string of the session attributes, which
 * supports the following fields:
 *     - **model**: String. Path to model directory for the session.
 *
 * An example of json string of session attributes:
 * @code{.json}
 * {
 *     "model": "/data/storage/el2/base/files/qwen2/"
 * }
 * @endcode
 *
 * @param attributes JSON string of session attributes.
 * @return Result of creating a session.
 * @since 20
 */
OH_QoS_GewuCreateSessionResult OH_QoS_GewuCreateSession(const char* attributes);

/**
 * @brief Destroys a Gewu session.
 * You are advised to wait until all requests are completed or aborted before calling
 * this API. If there are ongoing requests when this API is called, the requests will be aborted,
 * and no further response will be recevied.
 * Note that after this API is called, the session object can no longer be used.
 *
 * @param session Handle of the session to destroy.
 *
 * @return Error code.
 *     <ul>
 *         <li>{@link OH_QOS_GEWU_OK} The session is destroyed successfully.</li>
 *         <li>{@link OH_QOS_GEWU_NOENT} The session is not found. </li>
 *     </ul>
 *
 * @since 20
 */
OH_QoS_GewuErrorCode OH_QoS_GewuDestroySession(OH_QoS_GewuSession session);

/**
 * @brief Abort the specified request.
 * After this function is successfully called, the client will not receive any
 * response to the request, and the request handle cannot be used.
 *
 * @param session Handle of the session to which the request is submitted.
 * @param request Handle of the request.
 * @return Error code.
 *     <ul>
 *         <li>{@link OH_QOS_GEWU_OK} The request is aborted successfully.</li>
 *         <li>{@link OH_QOS_GEWU_NOENT} The request is not found. </li>
 *     </ul>
 *
 * @since 20
 */
OH_QoS_GewuErrorCode OH_QoS_GewuAbortRequest(OH_QoS_GewuSession session, OH_QoS_GewuRequest request);

/**
 * @brief Submits a request.
 * @code{.json} {
 *      "messages": [
 *          {
 *              "role": "developer",
 *              "content": "Your are a helpful assistant."
 *          },
 *          {
 *              "role": "user",
 *              "content": "What is OpenHarmony"
 *          }
 *      ],
 *      "stream": true
 * }
 * @endcode
 * @param session Session to which the request is submitted.
 * @param request JSON string of the request.
 * @param callback Callback for receiving the response.
 * @param context Pointer to the user context to be passed to the callback.
 * @return Result code.
 * - OH_QOS_GEWU_OK: The request is successfully submitted.
 * - OH_QOS_GEWU_NOMEM: The request fails to be submitted due to insufficient memory.
 *
 * @since 20
 */
OH_QoS_GewuSubmitRequestResult OH_QoS_GewuSubmitRequest(OH_QoS_GewuSession session,
    const char* request, OH_QoS_GewuOnResponse callback, void* context);
#ifdef __cplusplus
};
#endif
#endif // QOS_H

/** @} */