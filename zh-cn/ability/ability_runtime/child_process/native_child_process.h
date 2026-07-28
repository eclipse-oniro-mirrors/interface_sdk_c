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
 * @addtogroup ChildProcess
 * @{
 *
 * @brief Provides the APIs to manage child processes.
 *
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 12
 */

/**
 * @file native_child_process.h
 *
 * @brief Declares the APIs used to create a native child process and establish an IPC channel between the parent and
 * child processes.
 *
 * @kit AbilityKit
 * @library libchild_process.so
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 12
 */

#ifndef OHOS_ABILITY_RUNTIME_C_NATIVE_CHILD_PROCESS_H
#define OHOS_ABILITY_RUNTIME_C_NATIVE_CHILD_PROCESS_H

#include "IPCKit/ipc_cparcel.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义Native子进程模块错误码。
 *
 * @since 12
 */
typedef enum Ability_NativeChildProcess_ErrCode {
    /**
     * 操作成功。
     *
     * @since 12
     */
    NCP_NO_ERROR = 0,

    /**
     * 无效参数。
     *
     * @since 12
     */
    NCP_ERR_INVALID_PARAM = 401,

    /**
     * 不支持创建Native子进程。
     *
     * @since 12
     */
    NCP_ERR_NOT_SUPPORTED = 801,

    /**
     * 内部错误。
     *
     * @since 12
     */
    NCP_ERR_INTERNAL = 16000050,

    /**
     * 在Native子进程的启动过程中不能再次创建新的子进程，可以等待当前子进程启动完成后再次尝试。从API version 15开始被废弃。
     *
     * @since 12
     */
    NCP_ERR_BUSY = 16010001,

    /**
     * 启动Native子进程超时。
     *
     * @since 12
     */
    NCP_ERR_TIMEOUT = 16010002,

    /**
     * 服务端出错。
     *
     * @since 12
     */
    NCP_ERR_SERVICE_ERROR = 16010003,

    /**
     * 多进程模式已关闭，不允许启动子进程。
     *
     * @since 12
     */
    NCP_ERR_MULTI_PROCESS_DISABLED = 16010004,

    /**
     * 不允许在子进程中再次创建进程。
     *
     * @since 12
     */
    NCP_ERR_ALREADY_IN_CHILD = 16010005,

    /**
     * 到达最大Native子进程数量限制，不能再创建子进程。
     *
     * @since 12
     */
    NCP_ERR_MAX_CHILD_PROCESSES_REACHED = 16010006,

    /**
     * 子进程加载动态库失败，文件不存在或者未实现对应的方法并导出。
     *
     * @since 12
     */
    NCP_ERR_LIB_LOADING_FAILED = 16010007,

    /**
     * 子进程调用动态库的OnConnect方法失败，可能返回了无效的IPC对象指针。
     *
     * @since 12
     */
    NCP_ERR_CONNECTION_FAILED = 16010008,

    /**
     * 父进程调用解注册Native子进程退出回调，未找到注册的回调函数。<br>**起始版本：** 20
     *
     * @since 20
     */
    NCP_ERR_CALLBACK_NOT_EXIST = 16010009,

    /**
     * 该进程pid不存在，或并非当前进程的子进程pid，或属于{@link childProcessManager.startChildProcess}接口在SELF_FORK模式下启动的子进程。 <br>**起始版本：** 22
     *
     * @since 22
     */
    NCP_ERR_INVALID_PID = 16010010
} Ability_NativeChildProcess_ErrCode;

/**
 * @brief 定义Native子进程数据沙箱与网络环境的共享模式。
 *
 * @since 13
 */
typedef enum NativeChildProcess_IsolationMode {
    /**
     * 普通隔离模式下，父进程与子进程共享同一沙箱环境或网络环境。
     *
     * @since 13
     */
    NCP_ISOLATION_MODE_NORMAL = 0,

    /**
     * 在隔离模式下，父进程与子进程不共享同一沙箱环境或网络环境。
     *
     * @since 13
     */
    NCP_ISOLATION_MODE_ISOLATED = 1
} NativeChildProcess_IsolationMode;

/**
 * @brief 启动子进程的配置信息，包括子进程的进程名、以及数据沙箱与网络环境的共享模式。
 *
 * @since 20
 */
typedef struct Ability_ChildProcessConfigs Ability_ChildProcessConfigs;

/**
 * @brief 创建一个子进程配置信息对象。创建对象成功后需要通过调用{@link OH_Ability_DestroyChildProcessConfigs}来销毁对象从而避免内存泄漏。
 *
 * @return 返回一个指向{@link Ability_ChildProcessConfigs}对象的指针 - 子进程配置信息对象创建成功。
 *      返回nullptr - 发生内部错误或者内存分配失败。
 * @since 20
 */
Ability_ChildProcessConfigs* OH_Ability_CreateChildProcessConfigs();

/**
 * @brief 销毁一个子进程配置信息对象，并释放其内存，在调用该接口后，要避免继续使用已销毁的configs对象。
 *
 * @param configs 需要销毁的子进程配置信息对象指针。在调用该接口后，对象指针将失效，避免继续使用该指针。允许传入空指针，空指针不会触发任何操作。
 * @return NCP_NO_ERROR - 操作成功。
 *      NCP_ERR_INVALID_PARAM - 传入参数为nullptr。
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_DestroyChildProcessConfigs(Ability_ChildProcessConfigs* configs);

/**
 * @brief 设置子进程配置信息对象的数据沙箱与网络环境的共享模式，详见{@link NativeChildProcess_IsolationMode}。
 * 该设置仅当调用{@link OH_Ability_StartNativeChildProcessWithConfigs}、
 * {@link OH_Ability_CreateNativeChildProcessWithConfigs}接口时生效。
 *
 * @param configs 子进程的配置信息对象指针。不可以为空指针。
 * @param isolationMode 要设置的数据沙箱与网络环境的共享模式，详见NativeChildProcess_IsolationMode。
 * @return NCP_NO_ERROR - 执行成功。
 *      NCP_ERR_INVALID_PARAM - 传入参数configs为nullptr。
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_ChildProcessConfigs_SetIsolationMode(
    Ability_ChildProcessConfigs* configs, NativeChildProcess_IsolationMode isolationMode);

/**
 * @brief 设置子进程配置信息对象的uid是否隔离。例如用于浏览器的安全加固场景，设置主进程与子进程的uid隔离。
 *
 * @param configs 子进程的配置信息对象指针。不可以为空指针。
 * @param isolationUid 控制子进程是否使用独立的uid。true表示子进程拥有独立的uid，false表示子进程与主进程拥有相同uid。
 * @return NCP_NO_ERROR - 执行成功。
 *      NCP_ERR_INVALID_PARAM - 传入参数configs为nullptr。
 * @since 21
 */
Ability_NativeChildProcess_ErrCode OH_Ability_ChildProcessConfigs_SetIsolationUid(
    Ability_ChildProcessConfigs* configs, bool isolationUid);

/**
 * @brief 设置子进程配置信息对象中的进程名称。
 *
 * @param configs 子进程的配置信息对象指针。不能为空指针。
 * @param processName 设置的子进程名字符串必须是非空字符串，并且只能由字母、数字和下划线构成。最大长度为64字符。最终的进程名是{bundleName}:{processName}。
 * @return NCP_NO_ERROR - 执行成功。
 *      NCP_ERR_INVALID_PARAM - 传入参数configs为nullptr，或者processName包含除字母、数字、下划线以外的字符。
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_ChildProcessConfigs_SetProcessName(Ability_ChildProcessConfigs* configs,
    const char* processName);

/**
 * @brief 定义通知子进程启动结果的回调函数。
 *
 * @param errCode 回调函数返回的错误码，可用的值如下：
 *      {@link NCP_NO_ERROR} - 创建子进程成功。
 *      {@link NCP_ERR_LIB_LOADING_FAILED} - 加载动态库文件失败或动态库中未实现必要的导出函数。
 *      {@link NCP_ERR_CONNECTION_FAILED} - 动态库中实现的OnConnect方法未返回有效的IPC Stub指针。
 *      详见{@link Ability_NativeChildProcess_ErrCode}定义。
 * @param remoteProxy 子进程的IPC对象指针，出现异常时可能为nullptr：使用完毕后需要调用{@link OH_IPCRemoteProxy_Destroy}方法释放。
 * @see OH_Ability_CreateNativeChildProcess
 * @see OH_IPCRemoteProxy_Destroy
 * @since 12
 */
typedef void (*OH_Ability_OnNativeChildProcessStarted)(int errCode, OHIPCRemoteProxy *remoteProxy);

/**
 * @brief 创建子进程并加载参数中指定的动态链接库文件，进程启动结果通过回调参数异步通知，需注意回调通知为独立线程，回调函数实现需要注意线程同步，且不能执行高耗时操作避免长时间阻塞。
 *
 * @param libName 子进程中加载的动态库文件名称，不能为nullptr。
 * @param onProcessStarted 通知子进程启动结果的回调函数指针，不能为nullptr。详见{@link OH_Ability_OnNativeChildProcessStarted}。
 * @return {@link NCP_NO_ERROR} - 调用成功，但子进程的实际启动结果由回调函数通知。
 *      {@link NCP_ERR_INVALID_PARAM} - 无效的动态库名称或者回调函数指针。
 *      {@link NCP_ERR_NOT_SUPPORTED} - 当前设备不支持创建Native子进程。
 *      {@link NCP_ERR_MULTI_PROCESS_DISABLED} - 当前设备已关闭多进程模式。
 *      {@link NCP_ERR_ALREADY_IN_CHILD} - 不允许在子进程中再次创建子进程。
 *      {@link NCP_ERR_MAX_CHILD_PROCESSES_REACHED} - 到达最大Native子进程数限制。
 *      详见{@link Ability_NativeChildProcess_ErrCode}定义。
 * @see OH_Ability_OnNativeChildProcessStarted
 * @since 12
 */
int OH_Ability_CreateNativeChildProcess(const char* libName,
                                        OH_Ability_OnNativeChildProcessStarted onProcessStarted);

/**
 * @brief 根据传入的子进程配置信息创建子进程，并加载参数中指定的动态链接库文件。子进程的启动结果通过回调参数异步通知调用方。该回调在独立线程中执行，需要确保线程同步，且不能执行高耗时操作避免长时间阻塞。
 *
 * @param libName 子进程中加载的动态库文件名称，不能为nullptr。
 * @param configs 子进程的配置信息参数，不能为nullptr。
 * @param onProcessStarted 通知子进程启动结果的回调函数指针，不能为nullptr，详见OH_Ability_OnNativeChildProcessStarted。
 * @return NCP_NO_ERROR - 执行成功。
 *      NCP_ERR_INVALID_PARAM - 传入参数无效。
 *      NCP_ERR_NOT_SUPPORTED - 当前设备不支持创建Native子进程。
 *      NCP_ERR_MULTI_PROCESS_DISABLED - 当前设备已关闭多进程模式，不允许启动子进程。
 *      NCP_ERR_ALREADY_IN_CHILD - 不允许在子进程中再次创建子进程。
 *      NCP_ERR_MAX_CHILD_PROCESSES_REACHED - 超过最大Native子进程数限制。
 *      详见Ability_NativeChildProcess_ErrCode定义。
 * @see OH_Ability_OnNativeChildProcessStarted
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_CreateNativeChildProcessWithConfigs(const char* libName,
    Ability_ChildProcessConfigs* configs, OH_Ability_OnNativeChildProcessStarted onProcessStarted);

/**
 * @brief The struct describes the information about the file descriptor passed to the child process.
 * @since 13
 */
typedef struct NativeChildProcess_Fd {
    /**
     * Pointer to the name of the file descriptor. It contains a maximum of 20 characters.
     *
     * @since 13
     */
    char* fdName;

    /**
     * Value of the file descriptor.
     *
     * @since 13
     */
    int32_t fd;

    /**
     * Pointer to the next file descriptor.
     *
     * @since 13
     */
    struct NativeChildProcess_Fd* next;
} NativeChildProcess_Fd;

/**
 * @brief The struct describes a list of file descriptors passed to the child process. The list can contain a maximum
 * of 16 entries.
 * @since 13
 */
typedef struct NativeChildProcess_FdList {
    /**
     * Pointer to the first file descriptor in the linked list passed to the child process.
     *
     * @since 13
     */
    struct NativeChildProcess_Fd* head;
} NativeChildProcess_FdList;

/**
 * @brief The struct describes the options used for starting a child process.
 * @since 13
 */
typedef struct NativeChildProcess_Options {
    /**
     * Isolation mode of the child process.
     *
     * @since 13
     */
    NativeChildProcess_IsolationMode isolationMode;

    /**
     * Reserved for future use.
     *
     * @since 13
     */
    int64_t reserved;
} NativeChildProcess_Options;

/**
 * @brief The struct describes the parameters passed to the child process.
 * @since 13
 */
typedef struct NativeChildProcess_Args {
    /**
     * Pointer to the entry parameters. The size cannot exceed 150 KB.
     *
     * @since 13
     */
    char* entryParams;

    /**
     * List of file descriptors passed to the child process.
     *
     * @since 13
     */
    struct NativeChildProcess_FdList fdList;
} NativeChildProcess_Args;

/**
 * @brief 启动Native子进程，并加载参数中指定的动态链接库文件并调用入口函数。指定的动态库必须实现一个以{@link NativeChildProcess_Args}为参数的函数（函数名称可自定义），并导出该函数。
 * 支持传参到子进程。子进程中不支持创建ArkTS基础运行时环境。
 *
 * @param entry 子进程中加载的动态库及入口函数，例如"libEntry.so:Main"，不能为nullptr。
 * @param args 传递给子进程的参数。
 * @param options 子进程选项。
 * @param pid 启动的子进程id。
 * @return NCP_NO_ERROR - 调用成功。
 *      NCP_ERR_INVALID_PARAM - 无效的动态库名称或者回调函数指针。
 *      NCP_ERR_NOT_SUPPORTED - 当前设备不支持创建Native子进程。
 *      NCP_ERR_ALREADY_IN_CHILD - 当前设备已关闭多进程模式。
 *      NCP_ERR_MAX_CHILD_PROCESSES_REACHED - 到达最大Native子进程数限制。
 *      详见Ability_NativeChildProcess_ErrCode定义。
 * @see OH_Ability_OnNativeChildProcessStarted
 * @since 13
 */
Ability_NativeChildProcess_ErrCode OH_Ability_StartNativeChildProcess(
    const char* entry, NativeChildProcess_Args args,
    NativeChildProcess_Options options, int32_t *pid);

/**
 * @brief 根据参数中子进程配置信息启动Native子进程，加载参数中指定的动态链接库文件并调用入口函数。支持传参到子进程。指定的动态库必须实现一个以{@link NativeChildProcess_Args}为参数的函数（
 * 函数名称可自定义），并导出该函数。
 *
 * @param entry 子进程中调用动态库的符号和入口函数，中间用“:”隔开（例如“libentry.so:Main”），不能为nullptr。
 * @param args 传给子进程的参数。
 * @param configs 子进程的配置信息参数。
 * @param pid 被启动的子进程号。
 * @return NCP_NO_ERROR - 执行成功。
 *      NCP_ERR_INVALID_PARAM - 传入参数无效。
 *      NCP_ERR_NOT_SUPPORTED - 当前设备不支持创建Native子进程。
 *      NCP_ERR_ALREADY_IN_CHILD - 不允许在子进程中再次创建子进程。
 *      NCP_ERR_MAX_CHILD_PROCESSES_REACHED - 超过最大Native子进程数限制。
 *      详见Ability_NativeChildProcess_ErrCode定义。
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_StartNativeChildProcessWithConfigs(
    const char* entry, NativeChildProcess_Args args, Ability_ChildProcessConfigs* configs, int32_t *pid);

/**
 * @brief 通过{@link OH_Ability_StartNativeChildProcess}启动子进程后，子进程能够在任意so和任意子线程中获取启动参数{@link NativeChildProcess_Args}。
 *
 * @return 返回指向当前子进程启动参数的指针。
 * @since 17
 */
NativeChildProcess_Args* OH_Ability_GetCurrentChildProcessArgs();

/**
 * @brief 感知Native子进程退出的回调函数。
 *
 * @param pid 启动的子进程id。
 * @param signal 子进程退出信号。
 * @since 20
 */
typedef void (*OH_Ability_OnNativeChildProcessExit)(int32_t pid, int32_t signal);

/**
 * @brief 注册Native子进程退出回调函数。只有{@link OH_Ability_StartNativeChildProcess}、
 * {@link OH_Ability_StartNativeChildProcessWithConfigs}
 * 和{@link @ohos.app.ability.childProcessManager的startNativeChildProcess}启动的子进程退出时才会触发所注册的回调函数。当重复注册同一个回调函数时，
 * 子进程退出时只会执行一次回调函数。
 *
 * @param onProcessExit 子进程退出的回调函数入口，不能为nullptr。
 * @return NCP_NO_ERROR - 调用成功。
 *      NCP_ERR_INVALID_PARAM - 参数不合法。
 *      NCP_ERR_INTERNAL - 内部错误。
 *      详见Ability_NativeChildProcess_ErrCode。
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_RegisterNativeChildProcessExitCallback(
    OH_Ability_OnNativeChildProcessExit onProcessExit);

/**
 * @brief 解注册子进程退出回调。
 *
 * @param onProcessExit 子进程退出的回调函数入口，不能为nullptr。
 * @return NCP_NO_ERROR - 调用成功。
 *      NCP_ERR_INVALID_PARAM - 参数不合法。
 *      NCP_ERR_INTERNAL - 内部错误。
 *      NCP_ERR_CALLBACK_NOT_EXIST - 未找到回调函数。
 *      详见Ability_NativeChildProcess_ErrCode。
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_UnregisterNativeChildProcessExitCallback(
    OH_Ability_OnNativeChildProcessExit onProcessExit);

/**
 * @brief 终止当前进程创建的子进程。
 *
 * @param pid 要终止的子进程pid。
 * @return NCP_NO_ERROR - 调用成功。
 *      NCP_ERR_SERVICE_ERROR - 服务端出错。
 *      NCP_ERR_INVALID_PID - 所传入的子进程pid不合法。
 *      详见Ability_NativeChildProcess_ErrCode。
 * @since 22
 */
Ability_NativeChildProcess_ErrCode OH_Ability_KillChildProcess(int32_t pid);

/**
 * @brief 检查是否允许调用者在此设备上创建本机子进程。
 *
 * @return 如果允许调用者创建本机子进程，则为true，否则为false。
 * @since 26.0.0
 */
bool OH_Ability_IsNativeChildProcessSupported();

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
#endif // OHOS_ABILITY_RUNTIME_C_NATIVE_CHILD_PROCESS_H