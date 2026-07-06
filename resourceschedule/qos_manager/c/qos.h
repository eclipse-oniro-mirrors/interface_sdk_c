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
 * @brief This file declares the C APIs provided by Quality of Service (QoS) for setting, obtaining, and canceling
 * thread QoS levels, helping the system perform differentiated scheduling based on task priority. It also provides C
 * APIs related to the Gewu service (on-device AI inference acceleration service) for operations such as creating
 * sessions, submitting inference requests, receiving replies, canceling requests, and destroying sessions. These APIs
 * are applicable to scenarios where AI model inference needs to be executed locally with fine-grained control over
 * resource scheduling.
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
     * @brief QoS level for user invisible tasks.
     *
     */
    QOS_BACKGROUND = 0,

    /**
     * @brief QoS level for background critical tasks.
     *
     */
    QOS_UTILITY,

    /**
     * @brief Default QoS level.
     *
     */
    QOS_DEFAULT,

    /**
     * @brief QoS level for user triggered tasks.
     *
     */
    QOS_USER_INITIATED,

    /**
     * @brief QoS level for time limited tasks.
     *
     */
    QOS_DEADLINE_REQUEST,

    /**
     * @brief QoS level for user interactive tasks.
     *
     */
    QOS_USER_INTERACTIVE
} QoS_Level;

/**
 * @brief Sets the QoS level for the current thread. The system adjusts thread scheduling priority and resource
 * allocation policies based on the QoS level. Tasks with higher QoS levels generally receive more timely scheduling.
 * For example, for user-invisible tasks such as background downloads or data synchronization, you can use **
 * QOS_BACKGROUND** to reduce resource usage. For high-priority tasks such as user interaction or foreground rendering,
 * you can use **QOS_USER_INTERACTIVE** to achieve faster response times.
 *
 * @param level QoS level. Setting different levels affects thread scheduling priority and resource allocation: **
 *     QOS_BACKGROUND** is suitable for reducing resource usage of background tasks, **QOS_USER_INTERACTIVE** is
 *     suitable for improving the responsiveness of interactive tasks, and **QOS_DEFAULT** represents the default
 *     scheduling policy. For details, see {@link QoS_Level}.
 * @return If the operation is successful, **0** is returned. If the level is out of range or an internal error occurs,
 *     **-1** is returned.
 * @see QoS_Level
 * @since 12
 */
int OH_QoS_SetThreadQoS(QoS_Level level);

/**
 * @brief Resets the QoS level of the current thread. The thread will revert to the default system scheduling policy.
 * For example, after a high-priority task is complete, you can call this API to restore the default level to avoid
 * unnecessary resource usage.
 *
 * @return If the operation is successful, **0** is returned. If an internal error occurs, **-1** is returned.
 * @see QoS_Level
 * @since 12
 */
int OH_QoS_ResetThreadQoS();

/**
 * @brief Obtains the QoS level of the current thread. This API is used to read the QoS level of the current thread. If
 * no QoS level is set for the current thread or an internal error occurs, **-1** is returned. For example, in
 * scenarios where you need to make decisions based on the current priority of a thread, you can first call this API to
 * obtain the QoS level and then determine the subsequent operations accordingly.
 *
 * @param level Output parameter. The QoS level of the thread will be written to this variable as a {@link QoS_Level}
 *     value. This parameter cannot be set to NULL. If it is set to NULL, this API returns **-1**.
 * @return If the operation is successful, **0** is returned. If the QoS level is not set for the current thread or an
 *     internal error occurs, **-1** is returned.
 * @see QoS_Level
 * @since 12
 */
int OH_QoS_GetThreadQoS(QoS_Level *level);

/**
 * @brief Session handle.
 *
 * @since 20
 */
typedef unsigned int OH_QoS_GewuSession;

/**
 * @brief Indicates an invalid session handle, which is used for error return.
 *
 * @since 20
 */
#define OH_QOS_GEWU_INVALID_SESSION_ID ((OH_QoS_GewuSession)(0xffffffffU))
/**
 * @brief Request handle.
 *
 * @since 20
 */
typedef unsigned int OH_QoS_GewuRequest;

/**
 * @brief Indicates an invalid request handle, which is used for error return.
 *
 * @since 20
 */
#define OH_QOS_GEWU_INVALID_REQUEST_ID ((OH_QoS_GewuRequest)(0xffffffffU))
/**
 * @brief Enumerates the Gewu error codes.
 *
 * @since 20
 */
typedef enum {
    /**
     * @brief Success.
     *
     * @since 20
     */
    OH_QOS_GEWU_OK     = 0,
    /**
     * @brief Permission error. Possible cause: The caller does not have the required permission. Solution: Ensure that
     * the caller has the required permission.
     *
     * @since 20
     */
    OH_QOS_GEWU_NOPERM = 201,
    /**
     * @brief Memory error. Possible cause: The system memory is insufficient. Solution: Release the resources and try
     * again.
     *
     * @since 20
     */
    OH_QOS_GEWU_NOMEM  = 203,
    /**
     * @brief Parameter error. Possible cause: The parameter type is incorrect or the parameter value is invalid.
     * Solution: Verify the parameter type and value range.
     *
     * @since 20
     */
    OH_QOS_GEWU_INVAL  = 401,
    /**
     * @brief The handle already exists. Possible cause: An attempt was made to create an existing session or request.
     * Solution: Do not create the session or request repeatedly, or destroy the existing handle first.
     *
     * @since 20
     */
    OH_QOS_GEWU_EXIST  = 501,
    /**
     * @brief Handle not found. Possible cause: The input session or request handle is invalid or has been destroyed.
     * Solution: Ensure that the handle is valid.
     *
     * @since 20
     */
    OH_QOS_GEWU_NOENT  = 502,
    /**
     * @brief Symbol not found. Possible cause: The dependent library or module is not correctly loaded. Solution:
     * Ensure that the dependent library is correctly installed.
     *
     * @since 20
     */
    OH_QOS_GEWU_NOSYS  = 801,
    /**
     * @brief Other errors. Possible cause: An uncovered internal system error occurs. Solution: Check the system logs
     * for detailed error information or contact technical support.
     *
     * @since 20
     */
    OH_QOS_GEWU_FAULT  = 901
} OH_QoS_GewuErrorCode;

/**
 * @brief Return result of the **OH_QoS_GewuCreateSession()** API, used to encapsulate the execution status of the Gewu
 * session creation operation. This struct supports unified handling of both success and failure scenarios. Upon
 * success, the `session` field contains the handle to the created session. Upon failure, the `error` field stores the
 * error code, helping you locate and handle exceptions.
 *
 * @since 20
 */
typedef struct {
    /** 
     * @brief Session handle returned after a session is successfully created. This parameter is valid only when `error`
     *  is `OH_QOS_GEWU_OK`.
     * 
     * @since 20
     */
    OH_QoS_GewuSession session;
    /** 
     * @brief Error code.
     *     <br>- `OH_QOS_GEWU_OK`: The session is successfully created.
     *     <br>- `OH_QOS_GEWU_NOMEM`: Insufficient memory. There is not enough memory to create the session. You are
     *     advised to release system resources and retry the session creation.
     *     <br>- `OH_QOS_GEWU_INVAL`: Invalid parameter. The input parameter does not meet the API requirements. Verify
     *     the field types, formats, and values in `attributes`.
     *     <br>- `OH_QOS_GEWU_NOPERM`: Insufficient permission. The caller lacks the required permission for the API.
     *     Verify the application permission configuration.
     *     <br>- `OH_QOS_GEWU_EXIST`: The session already exists. An attempt was made to create a session that already
     *     exists. Verify the session creation process.
     *     <br>- `OH_QOS_GEWU_NOSYS`: Symbol not found. The system does not support the related function or the
     *     dependent symbols are unavailable. Check system version and the status of dependent libraries.
     *     <br>The mapping between the above enumerated values and
     * their numeric codes is as follows: `OH_QOS_GEWU_OK` = **0**, `OH_QOS_GEWU_NOPERM` = **201**, `OH_QOS_GEWU_NOMEM`
     * = **203**, `OH_QOS_GEWU_INVAL` = **401**, `OH_QOS_GEWU_EXIST` = **501**, and `OH_QOS_GEWU_NOSYS` = **801**.
     * 
     * @since 20
     */
    OH_QoS_GewuErrorCode error;
} OH_QoS_GewuCreateSessionResult;

/**
 * @brief Return result of the **OH_QoS_GewuSubmitRequest()** API, used to obtain the submission status and result of a
 * Gewu inference request. (The Gewu service is an on-device AI inference acceleration service.) Upon successful
 * submission, the `request` field contains the created request handle, which can be used to cancel the request later.
 * Upon failure, the `error` field stores the error code, helping you take appropriate action based on the specific
 * error cause. This struct is applicable in scenarios where you need to determine whether a submitted on-device AI
 * inference request has been successfully admitted into the session and obtain the request handle.
 *
 * @since 20
 */
typedef struct {
    /** 
     * @brief Request handle created after the request is successfully submitted. It can be used to cancel the request
     * later. This parameter is valid only when `error` is `OH_QOS_GEWU_OK`. If the operation fails, this parameter is
     * invalid.
     *
     * @since 20
     */
    OH_QoS_GewuRequest request;
    /**
     * @brief Error code.
     *     <br>- `OH_QOS_GEWU_OK`: The request is submitted successfully.
     *     <br>- `OH_QOS_GEWU_NOMEM`: Insufficient memory. There is not enough memory to process the request. You are
     *     advised to release resources and retry.
     *     <br>- `OH_QOS_GEWU_INVAL`: Invalid parameter. The input parameter such as the session handle,
     *     request content, or callback is invalid. Verify the parameter types, formats, and values.
     *     <br>- `OH_QOS_GEWU_NOENT`: Session not found. The specified session does not exist or has been destroyed.
     *     Verify that the session has been successfully created and is still valid.
     *     <br>- `OH_QOS_GEWU_NOPERM`: Insufficient permission. The caller lacks the required permission for the API.
     *     Verify the application permission configuration.
     *     <br>- `OH_QOS_GEWU_NOSYS`: Symbol not found. The system does not support the related function or the
     *     dependent symbols are unavailable. Check system version and the status of dependent libraries.
     *     <br>The mapping between the above enumerated values
     * and their numeric codes is as follows: OH_QOS_GEWU_OK = **0**, OH_QOS_GEWU_NOPERM = **201**, OH_QOS_GEWU_NOMEM =
     * **203**, OH_QOS_GEWU_INVAL = **401**, `OH_QOS_GEWU_NOENT` = **502**, and OH_QOS_GEWU_NOSYS = **801**.
     *
     * @since 20
     */
    OH_QoS_GewuErrorCode error;
} OH_QoS_GewuSubmitRequestResult;

/**
 * @brief Callback for receiving responses from the Gewu service. The Gewu service calls this callback asynchronously
 * upon completion of inference. For non-streaming inference, it is called once. For streaming inference, it is called
 * multiple times during the generation process. For example, when using the Gewu service for conversational AI
 * inference, you can receive the model-generated response content through this callback.
 *
 * @param context User context pointer specified when the request is submitted. This pointer is passed unchanged to the
 *     **OH_QoS_GewuOnResponse** callback when a reply is received, for correlating the request with its corresponding
 *     response data.
 * @param response JSON string of the response, which contains the following parameters:
 *     <br>- **message**: object, which contains the **role** and **content** fields. The value of **role** is of the
 *     string type, indicating the role type of the message. The value must be **assistant**. The value of **content**
 *     is of the string type, indicating the message generated by the model and returned to the user.
 *     <br>- **finish_reason: string or null**: stop reason, which can be:
 *     <br>&nbsp;&nbsp;&nbsp;&nbsp;- **null**: The request is not stopped. In streaming inference, there are multiple
 *     responses, and only the last response has a non-empty **finish_reason**. In non-streaming inference, there is
 *     only one response, and **finish_reason** is not empty.
 *     <br>&nbsp;&nbsp;&nbsp;&nbsp;- **"stop"**: The request is stopped normally.
 *     <br>&nbsp;&nbsp;&nbsp;&nbsp;- **"abort"**: The request is stopped by the user in advance.
 *     <br>&nbsp;&nbsp;&nbsp;&nbsp;- **"length"**: The number of tokens exceeds the upper limit.
 * @since 20
 */
typedef void (*OH_QoS_GewuOnResponse)(void* context, const char* response);

/**
 * @brief Creates a Gewu session. Before calling this API, ensure that the system supports the Gewu service and the
 * required permissions have been obtained. This function loads the specified AI model based on the session attributes
 * and initializes the inference environment to prepare for subsequent inference requests. The lifecycle of the session
 * object begins when the **OH_QoS_GewuCreateSession** function returns and ends when **OH_QoS_GewuDestroySession** is
 * called. Within the lifecycle, multiple requests can be created. You are advised to wait for all requests to complete
 * or abort them before destroying the session. Otherwise, they will be automatically aborted and no replies will be
 * received. After the session is destroyed, the session handle can no longer be used. The session attributes are
 * passed through a JSON string, which supports the following fields:
 * <br>- **model**: string, indicating the path of the model used by the session. It is mandatory.
 * <br>Example of the **attributes** JSON string
 * <br>{
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;"model": "/data/storage/el2/base/files/qwen2/"
 * <br>&nbsp;}
 *
 * @code{.json}
 * {
 *     "model": "/data/storage/el2/base/files/qwen2/"
 * }
 * @endcode
 *
 * @param attributes Input parameter, which is a JSON string of session attributes. It is used to specify the model
 *     path used by the session. Supported field: **model**. (The field is mandatory and of the string type, indicating
 *     the model path used by the session. Paths that can be accessed by the application sandbox are supported.) For
 *     details, see the JSON example in the function description.
 * @return Gewu session creation result.
 *     <br>- If the session is created successfully, the value of `error` in the return value `
 *     OH_QoS_GewuCreateSessionResult` is `OH_QOS_GEWU_OK`, and the value of `session` is the session handle.
 *     <br>- If the session fails to be created, `error` in the return value `OH_QoS_GewuCreateSessionResult` indicates
 *     the error cause. The value `OH_QOS_GEWU_NOMEM` indicates that the memory is insufficient for creating a session,
 *     the value `OH_QOS_GEWU_INVAL` indicates a parameter error, the value `OH_QOS_GEWU_NOPERM` indicates insufficient
 *     permission, the value `OH_QOS_GEWU_EXIST` indicates that the session already exists, and the value `
 *     OH_QOS_GEWU_NOSYS` indicates that the symbol cannot be found.
 * @since 20
 */
OH_QoS_GewuCreateSessionResult OH_QoS_GewuCreateSession(const char* attributes);

/**
 * @brief Destroys a Gewu session. This function releases session-related resources and cleans up the internal state.
 * You are advised to call this API after all requests are completed or aborted. If there are ongoing requests when
 * this API is called, the requests will be aborted, no response will be received, and the request handles cannot be
 * used anymore. Note that after this API is called, the session object cannot be used.
 *
 * @param session Handle to the session to destroy.
 * @return Error code.
 *     <br>- If the session is destroyed successfully, `OH_QOS_GEWU_OK` is returned.
 *     <br>- If the session is not found, `OH_QOS_GEWU_NOENT` is returned.
 *     <br>- If the parameter is invalid, `OH_QOS_GEWU_INVAL` is returned.
 *     <br>- If the symbol is not found, `OH_QOS_GEWU_NOSYS` is returned.
 *     <br>- If another internal error occurs, `OH_QOS_GEWU_FAULT` is returned.
 * @since 20
 */
OH_QoS_GewuErrorCode OH_QoS_GewuDestroySession(OH_QoS_GewuSession session);

/**
 * @brief Stops a specified request. This function requests the Gewu service to abort the ongoing inference computation
 * and cleans up the state associated with the request. Before calling this API, ensure that the passed session handle
 * is valid (not destroyed via **OH_QoS_GewuDestroySession**) and that the request handle is valid (already submitted
 * via **OH_QoS_GewuSubmitRequest**). Typical use cases include: a user actively cancels an ongoing inference request;
 * the application needs to release resources and terminate unnecessary requests in advance. After this function is
 * successfully called, the client will no longer receive any reply for the request, and the request handle can no
 * longer be used.
 *
 * @param session Handle to the session to which the request is submitted.
 * @param request Request handle.
 * @return Error code.
 *     <br>- If the request is successfully stopped, `OH_QOS_GEWU_OK` is returned.
 *     <br>- If the request is not found, `OH_QOS_GEWU_NOENT` is returned.
 *     <br>- If the parameter is invalid, `OH_QOS_GEWU_INVAL` is returned.
 *     <br>- If the symbol is not found, `OH_QOS_GEWU_NOSYS` is returned.
 * @since 20
 */
OH_QoS_GewuErrorCode OH_QoS_GewuAbortRequest(OH_QoS_GewuSession session, OH_QoS_GewuRequest request);

/**
 * @brief Submits a request. This function submits an inference request to a specified session, which is then scheduled
 * and executed by the Gewu service. Before calling this API, ensure that the input session handle is valid (already
 * created via **OH_QoS_GewuCreateSession** and not destroyed via **OH_QoS_GewuDestroySession**). The **request**
 * parameter is a JSON string that supports the following fields:
 * <br>- **messages: array** (mandatory): Array of messages, where each element supports the following fields:
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;- **role: string**: role type of the message. The options are as follows:
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- **"developer"**: instruction provided by the developer or
 * system.
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- **"user"**: user input.
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- **"assistant"**: model generation result.
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;- **content: string**: message content.
 * <br>- **stream: boolean or null** (optional): whether to enable streaming inference. If **true** is passed,
 * streaming inference is enabled. This is suitable for scenarios that require step-by-step reception of generated
 * content and lower time-to-first-token latency. In this case, the callback function will be called multiple times. If
 * **false** or **null** is passed, non-streaming inference is used. This is suitable for scenarios where you need to
 * obtain the complete result in a single response, and the callback function will be called only once. If no value is
 * passed, non-streaming inference is used by default. Example of the JSON string:
 * <br>{
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;"messages": [
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;{
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"role": "developer",
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"content": "You are a helpful assistant."
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;},
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;{
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"role": "user",
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"content": "What is OpenHarmony"
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;}
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;],
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;"stream": true
 * <br>}
 *
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
 * @param session Handle to the session, specifying the target session for request submission.
 * @param request JSON string of the request. The supported fields include: **messages** (message array, where each
 *     element contains the **role** and **content** fields, with **role** options being **developer**, **user**, and **
 *     assistant**), and **stream** (optional, specifying whether to enable streaming inference; the value can be **
 *     boolean** or **null**; if not passed, non-streaming is used by default). For details, see the JSON example in
 *     the function description.
 * @param callback Callback for receiving responses.
 * @param context Pointer to the user context to be passed to the callback.
 * @return Result of submitting a Gewu request. The **error** field is of the {@link OH_QoS_GewuErrorCode} type. For
 *     the mapping between the enumerated values and numeric codes, see the enum description of
 *     {@link OH_QoS_GewuErrorCode}.
 *     <br>- If the request is submitted successfully, `error` in `OH_QoS_GewuSubmitRequestResult` is `OH_QOS_GEWU_OK` (
 *     **0**), and **request** is the request handle.
 *     <br>- If the request fails to be submitted, `error` in the return value `OH_QoS_GewuSubmitRequestResult`
 *     indicates the error cause. The value `OH_QOS_GEWU_NOMEM` (**203**) indicates that there is no sufficient memory
 *     to process this request, the value `OH_QOS_GEWU_INVAL` (**401**) indicates a parameter error, the value `
 *     OH_QOS_GEWU_NOENT` (**502**) indicates that the session is not found, the value `OH_QOS_GEWU_NOPERM` (**201**)
 *     indicates insufficient permission, and the value `OH_QOS_GEWU_NOSYS` (**801**) indicates that the symbol is not
 *     found.
 * @since 20
 */
OH_QoS_GewuSubmitRequestResult OH_QoS_GewuSubmitRequest(OH_QoS_GewuSession session,
    const char* request, OH_QoS_GewuOnResponse callback, void* context);
#ifdef __cplusplus
};
#endif
#endif // QOS_H

/** @} */
