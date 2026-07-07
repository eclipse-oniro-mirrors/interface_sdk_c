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
 * @brief 声明QoS（Quality of Service）提供的C接口，用于设置、获取和取消线程QoS等级，帮助系统根据任务重要程度进行差异化调度。本文件同时提供格物服务（Gewu service，端侧AI推理加速服务）
 * 相关C接口，用于创建会话、提交推理请求、接收回复、中止请求和销毁会话等操作，适用于需要在本地执行AI模型推理并精细控制资源调度的场景。
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
 * @brief 描述QoS等级。
 *
 * @since 12
 */
typedef enum QoS_Level {
    /**
     * @brief 表示QoS等级为用户不可见任务。
     *
     */
    QOS_BACKGROUND = 0,

    /**
     * @brief 表示QoS等级为后台重要任务。
     *
     */
    QOS_UTILITY,

    /**
     * @brief 表示QoS等级为默认。
     *
     */
    QOS_DEFAULT,

    /**
     * @brief 表示QoS等级为用户触发任务。
     *
     */
    QOS_USER_INITIATED,

    /**
     * @brief 表示QoS等级为限时任务。
     *
     */
    QOS_DEADLINE_REQUEST,

    /**
     * @brief 表示QoS等级为用户交互任务。
     *
     */
    QOS_USER_INTERACTIVE
} QoS_Level;

/**
 * @brief 为当前线程设置QoS等级。系统会根据QoS等级调整线程调度优先级和资源分配策略，等级越高的任务通常获得更及时的调度。例如：在执行后台下载或数据同步等用户不可见任务时，可设置QOS_BACKGROUND以降低资源占用；
 * 在处理用户交互或前台渲染等高优先级任务时，可设置QOS_USER_INTERACTIVE以获得更快的响应速度。
 *
 * @param level 表示设置的QoS等级。设置为不同等级会影响线程的调度优先级和资源分配：QOS_BACKGROUND适用于降低后台任务资源占用，QOS_USER_INTERACTIVE适用于提升交互任务响应速度，
 *     QOS_DEFAULT表示默认调度策略。详见{@link QoS_Level}。
 * @return 成功返回0，如果级别超出范围或内部错误失败则返回-1。
 * @see QoS_Level
 * @since 12
 */
int OH_QoS_SetThreadQoS(QoS_Level level);

/**
 * @brief 重置当前线程的QoS等级，线程将恢复为系统默认调度策略。例如：当之前设置的高优先级任务执行完毕后，调用此接口恢复默认等级，避免不必要的资源占用。
 *
 * @return 成功返回0，如果内部错误失败则返回-1。
 * @see QoS_Level
 * @since 12
 */
int OH_QoS_ResetThreadQoS();

/**
 * @brief 获取当前线程的QoS等级。该接口用于读取当前线程已设置的QoS等级，如果当前线程未设置QoS等级或发生内部错误则返回-1。例如：在需要根据线程当前优先级进行条件判断的场景中，可先调用此接口获取QoS等级，再决定后续操作。
 *
 * @param level 输出参数，线程的QoS等级会以{@link QoS_Level}形式写入该变量。此参数不允许为NULL，传入NULL将导致函数返回-1。
 * @return 成功返回0，如果当前线程未设置QoS等级或内部错误失败则返回-1。
 * @see QoS_Level
 * @since 12
 */
int OH_QoS_GetThreadQoS(QoS_Level *level);

/**
 * @brief 会话句柄。
 *
 * @since 20
 */
typedef unsigned int OH_QoS_GewuSession;

/**
 * @brief 无效会话句柄，用于错误返回。
 *
 * @since 20
 */
#define OH_QOS_GEWU_INVALID_SESSION_ID ((OH_QoS_GewuSession)(0xffffffffU))
/**
 * @brief 请求句柄。
 *
 * @since 20
 */
typedef unsigned int OH_QoS_GewuRequest;

/**
 * @brief 无效请求句柄，用于错误返回。
 *
 * @since 20
 */
#define OH_QOS_GEWU_INVALID_REQUEST_ID ((OH_QoS_GewuRequest)(0xffffffffU))
/**
 * @brief 格物错误码。
 *
 * @since 20
 */
typedef enum {
    /**
     * @brief 成功。
     *
     * @since 20
     */
    OH_QOS_GEWU_OK     = 0,
    /**
     * @brief 权限错误。可能原因：调用者缺少所需权限。解决措施：请确认已申请相关权限。
     *
     * @since 20
     */
    OH_QOS_GEWU_NOPERM = 201,
    /**
     * @brief 内存错误。可能原因：系统内存不足。解决措施：请释放资源后重试。
     *
     * @since 20
     */
    OH_QOS_GEWU_NOMEM  = 203,
    /**
     * @brief 参数错误。可能原因：参数类型不正确或参数值无效。解决措施：请检查参数类型和取值范围。
     *
     * @since 20
     */
    OH_QOS_GEWU_INVAL  = 401,
    /**
     * @brief 已存在句柄。可能原因：重复创建已存在的会话或请求。解决措施：请勿重复创建，或先销毁已有句柄。
     *
     * @since 20
     */
    OH_QOS_GEWU_EXIST  = 501,
    /**
     * @brief 找不到句柄。可能原因：传入的会话或请求句柄无效或已被销毁。解决措施：请检查句柄是否有效。
     *
     * @since 20
     */
    OH_QOS_GEWU_NOENT  = 502,
    /**
     * @brief 找不到符号。可能原因：依赖的库或模块未正确加载。解决措施：请检查依赖库是否正确安装。
     *
     * @since 20
     */
    OH_QOS_GEWU_NOSYS  = 801,
    /**
     * @brief 其他错误。可能原因：未覆盖的内部系统错误。解决措施：请检查系统日志获取详细错误信息，或联系技术支持。
     *
     * @since 20
     */
    OH_QOS_GEWU_FAULT  = 901
} OH_QoS_GewuErrorCode;

/**
 * @brief OH_QoS_GewuCreateSession()接口的返回结果，用于封装格物会话创建操作的执行状态。该结构体支持统一处理会话创建成功和失败两种场景：创建会话成功时，`session`字段包含创建的会话句柄；失败时，`
 * error`字段保存错误码，便于开发者定位和处理异常。
 *
 * @since 20
 */
typedef struct {
    /**
     * @brief 创建会话成功后返回的会话句柄。仅在`error`为`OH_QOS_GEWU_OK`时有效。
     *
     * @since 20
     */
    OH_QoS_GewuSession session;
    /**
     * @brief 错误码。
     *     <br>- `OH_QOS_GEWU_OK`：创建会话成功。
     *     <br>- `OH_QOS_GEWU_NOMEM`：内存不足，表示没有足够的内存创建会话，建议释放系统资源后重新创建会话。
     *     <br>- `OH_QOS_GEWU_INVAL`：参数错误，表示输入参数不符合接口要求，请检查`attributes`中的字段类型、格式和取值。
     *     <br>- `OH_QOS_GEWU_NOPERM`：权限不足，表示调用者缺少接口所需权限，请检查应用权限配置。
     *     <br>- `OH_QOS_GEWU_EXIST`：会话已存在，表示重复创建已存在的会话，请确认会话创建流程。
     *     <br>- `OH_QOS_GEWU_NOSYS`：找不到符号，表示系统不支持相关功能或依赖符号不可用，请确认系统版本和依赖库状态。
     *     <br>上述枚举值与数字的对应关系：`OH_QOS_GEWU_OK`=0、`OH_QOS_GEWU_NOPERM`=201、`
     * OH_QOS_GEWU_NOMEM`=203、`OH_QOS_GEWU_INVAL`=401、`OH_QOS_GEWU_EXIST`=501、`OH_QOS_GEWU_NOSYS`=801。
     *
     * @since 20
     */
    OH_QoS_GewuErrorCode error;
} OH_QoS_GewuCreateSessionResult;

/**
 * @brief OH_QoS_GewuSubmitRequest()接口的返回结果，用于获取格物服务（Gewu service，端侧AI推理加速服务）推理请求的提交状态和结果。请求提交成功时，`request`字段包含创建的请求句柄，
 * 可用于后续中止该请求；失败时，`error`字段保存错误码，便于开发者根据具体错误原因进行处理。该结构体适用于提交端侧AI推理请求后判断请求是否成功进入会话并获取请求句柄的场景。
 *
 * @since 20
 */
typedef struct {
    /**
     * @brief 请求提交成功后创建的请求句柄，可用于后续中止该请求。仅在`error`为`OH_QOS_GEWU_OK`时有效，失败时该字段无效。
     *
     * @since 20
     */
    OH_QoS_GewuRequest request;
    /**
     * @brief 错误码。
     *     <br>- `OH_QOS_GEWU_OK`：请求提交成功。
     *     <br>- `OH_QOS_GEWU_NOMEM`：内存不足，表示没有足够的内存处理该请求，建议释放资源后重试。
     *     <br>- `OH_QOS_GEWU_INVAL`：参数错误，表示传入的会话句柄、请求内容或回调等参数无效，请检查参数类型、格式和取值。
     *     <br>- `OH_QOS_GEWU_NOENT`：找不到会话，表示指定的会话不存在或已被销毁，请确认会话是否已成功创建且仍然有效。
     *     <br>- `OH_QOS_GEWU_NOPERM`：权限不足，表示调用者缺少接口所需权限，请检查应用权限配置。
     *     <br>- `OH_QOS_GEWU_NOSYS`：找不到符号，表示系统不支持相关功能或依赖符号不可用，请确认系统版本和依赖库状态。
     *     <br>上述枚举值与数字的对应关系：`OH_QOS_GEWU_OK`=0、`OH_QOS_GEWU_NOPERM`=201、`
     * OH_QOS_GEWU_NOMEM`=203、`OH_QOS_GEWU_INVAL`=401、`OH_QOS_GEWU_NOENT`=502、`OH_QOS_GEWU_NOSYS`=801。
     *
     * @since 20
     */
    OH_QoS_GewuErrorCode error;
} OH_QoS_GewuSubmitRequestResult;

/**
 * @brief 用于接收格物服务回复的回调。格物服务在推理完成后异步调用该回调函数，非流式推理时调用一次，流式推理时根据生成过程多次调用。例如：在使用格物服务进行对话式AI推理时，可通过此回调接收模型生成的回复内容。
 *
 * @param context 提交请求时指定的用户上下文指针。该指针会在收到回复时原样传递给OH_QoS_GewuOnResponse回调函数，用于关联请求和响应数据。
 * @param response 回复的JSON字符串，包含以下字段：
 *     <br>- message: 对象，包含role和content两个字段。其中role为string类型，表示消息的角色类型，应为"assistant"；content为string类型，表示模型生成返回给用户的消息。
 *     <br>- finish_reason: string or null，停止原因，可能的值如下：
 *     <br>&nbsp;&nbsp;&nbsp;&nbsp;- null: 表示没有停止。流式推理中会有多次回复，只有最后一次回复有非空的"finish_reason"。而非流式推理只有一次回复，且"finish_reason"
 *     非空。
 *     <br>&nbsp;&nbsp;&nbsp;&nbsp;- "stop": 正常停止。
 *     <br>&nbsp;&nbsp;&nbsp;&nbsp;- "abort": 用户主动提前中止。
 *     <br>&nbsp;&nbsp;&nbsp;&nbsp;- "length": token数超过限制。
 * @since 20
 */
typedef void (*OH_QoS_GewuOnResponse)(void* context, const char* response);

/**
 * @brief 创建格物会话。调用此接口前，需确保系统支持格物服务能力并已申请接口所需权限。该函数会根据会话属性加载指定的AI模型并初始化推理环境，为后续推理请求做好准备。
 * 会话对象的生命周期从OH_QoS_GewuCreateSession函数返回开始，到调用OH_QoS_GewuDestroySession为止。在生命周期内，可以创建多个请求；建议在销毁会话前等待所有请求完成或中止，
 * 否则这些请求会被自动中止且不再收到回复；销毁后会话句柄无法再使用。会话属性通过JSON字符串传入，该JSON字符串支持以下字段：
 * <br>- model: string（必选），表示会话使用的模型路径。
 * <br>`attributes` JSON字符串例子：
 * <br>{
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;"model": "/data/storage/el2/base/files/qwen2/"
 * <br>&nbsp;}
 * @param attributes 输入参数，会话属性的JSON字符串，用于指定会话使用的模型路径。支持的字段包括：model（string，必选，表示会话使用的模型路径，支持应用沙箱可访问的路径）。详见函数说明中的JSON示例。
 * @return 格物创建会话结果。
 *     <br>- 表示创建会话成功，返回值`OH_QoS_GewuCreateSessionResult`里的`error`为`OH_QOS_GEWU_OK`，`session`为会话句柄。
 *     <br>- 表示创建会话失败，返回值`OH_QoS_GewuCreateSessionResult`里的`error`为错误原因，其中`OH_QOS_GEWU_NOMEM`表示没有足够的内存创建会话，`
 *     OH_QOS_GEWU_INVAL`表示参数错误，`OH_QOS_GEWU_NOPERM`表示权限不足，`OH_QOS_GEWU_EXIST`表示会话已存在，`OH_QOS_GEWU_NOSYS`表示找不到符号。
 * @since 20
 */
OH_QoS_GewuCreateSessionResult OH_QoS_GewuCreateSession(const char* attributes);

/**
 * @brief 销毁格物会话。该函数会释放会话相关资源并清理内部状态。建议等待至所有请求都已完成或中止后再调用此接口。如果调用时还有正在进行的请求，这些请求将会被中止，且不再收到回复，请求句柄无法再被使用。注意，在调用完该接口后，
 * 会话对象无法再被使用。
 *
 * @param session 要销毁的会话句柄。
 * @return 错误码。
 *     <br>- 表示会话销毁成功，返回值为`OH_QOS_GEWU_OK`。
 *     <br>- 表示找不到会话，返回`OH_QOS_GEWU_NOENT`。
 *     <br>- 表示参数无效，返回`OH_QOS_GEWU_INVAL`。
 *     <br>- 表示找不到符号，返回`OH_QOS_GEWU_NOSYS`。
 *     <br>- 表示其他内部错误，返回`OH_QOS_GEWU_FAULT`。
 * @since 20
 */
OH_QoS_GewuErrorCode OH_QoS_GewuDestroySession(OH_QoS_GewuSession session);

/**
 * @brief 停止指定的请求。该函数会请求格物服务中止正在进行的推理计算，并清理该请求相关状态。调用此接口前，需确保传入的会话句柄有效（未通过OH_QoS_GewuDestroySession销毁），且请求句柄有效（
 * 已通过OH_QoS_GewuSubmitRequest提交）。典型使用场景包括用户主动取消正在进行的推理请求，或应用需要释放资源时提前终止不需要的请求。成功调用该函数后，客户端不会再收到该请求的回复，且该请求句柄无法再被使用。
 *
 * @param session 请求提交到的会话句柄。
 * @param request 请求的句柄。
 * @return 错误码。
 *     <br>- 表示成功停止请求，返回`OH_QOS_GEWU_OK`。
 *     <br>- 表示找不到请求，返回`OH_QOS_GEWU_NOENT`。
 *     <br>- 表示参数无效，返回`OH_QOS_GEWU_INVAL`。
 *     <br>- 表示找不到符号，返回`OH_QOS_GEWU_NOSYS`。
 * @since 20
 */
OH_QoS_GewuErrorCode OH_QoS_GewuAbortRequest(OH_QoS_GewuSession session, OH_QoS_GewuRequest request);

/**
 * @brief 提交请求。该函数会将推理请求提交到指定会话，由格物服务调度执行。调用此接口前，需确保传入的会话句柄有效（
 * 已通过OH_QoS_GewuCreateSession创建且未通过OH_QoS_GewuDestroySession销毁）。request参数为请求的JSON字符串，支持以下字段：
 * <br>- messages: array，必填，表示消息的数组，其中每个元素支持以下字段：
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;- role: string，消息的角色类型，可选值包括：
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "developer"：开发者或系统提供的指示。
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "user"：用户输入。
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- "assistant"：模型生成结果。
 * <br>&nbsp;&nbsp;&nbsp;&nbsp;- content: string，消息内容。
 * <br>- stream: boolean or null，可选，是否使能流式推理。传入true启用流式推理，适用于需要逐步接收模型生成内容、降低首字延迟的场景，回调会被多次调用；传入false或null使用非流式推理，
 * 适用于需要一次性获取完整结果的场景，回调仅调用一次。不传入时默认为非流式。JSON字符串例子：
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
 * @param session 会话句柄，请求要提交的会话。
 * @param request 请求的JSON字符串，支持的字段包括：messages（array，消息数组，每个元素包含role和content字段，其中role可选值为developer、user、assistant）、
 *     stream（boolean或null，可选，是否启用流式推理，不传时默认为非流式）。详见函数说明中的JSON示例。
 * @param callback 接收回复的回调。
 * @param context 要传给回调的用户上下文指针。
 * @return 格物提交请求结果。`error`字段为枚举{@link OH_QoS_GewuErrorCode}，枚举值与数字对应关系详见{@link OH_QoS_GewuErrorCode}枚举说明。
 *     <br>- 表示提交请求成功，返回值`OH_QoS_GewuSubmitRequestResult`里的`error`为`OH_QOS_GEWU_OK`（数值0），`request`为请求句柄。
 *     <br>- 表示提交请求失败，返回值`OH_QoS_GewuSubmitRequestResult`里的`error`为错误原因，其中`OH_QOS_GEWU_NOMEM`（数值203）表示没有足够的内存处理该请求，`
 *     OH_QOS_GEWU_INVAL`（数值401）表示参数错误，`OH_QOS_GEWU_NOENT`（数值502）表示找不到会话，`OH_QOS_GEWU_NOPERM`（数值201）表示权限不足，`
 *     OH_QOS_GEWU_NOSYS`（数值801）表示找不到符号。
 * @since 20
 */
OH_QoS_GewuSubmitRequestResult OH_QoS_GewuSubmitRequest(OH_QoS_GewuSession session,
    const char* request, OH_QoS_GewuOnResponse callback, void* context);
#ifdef __cplusplus
};
#endif
#endif // QOS_H

/** @} */
