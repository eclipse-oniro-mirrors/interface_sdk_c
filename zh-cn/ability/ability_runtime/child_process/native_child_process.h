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
 * @brief 提供子进程的管理能力，支持创建Native子进程并在父子进程间建立IPC通道，用于实现多进程应用开发。
 * 创建的子进程不支持UI界面，也不支持Context相关的接口调用。通过本模块和childProcessManager启动的子进程总数最大为512个，
 * 其中childProcessManager在SELF_FORK模式下启动的子进程不计入总数。
 * 
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 12
 */

/**
 * @file native_child_process.h
 *
 * @brief 支持创建Native子进程，并在父子进程间建立IPC通道，适用于需要将耗时任务、高风险操作或独立业务逻辑隔离到独立进程执行的多种场景。该模块提供了进程隔离、IPC通信、灵活配置等核心能力，
 * 可以有效提升应用的稳定性和安全性，避免主进程阻塞或崩溃。通过子进程机制，开发者可以实现多进程架构，将计算密集型任务、媒体处理、网络请求等业务独立运行，提升应用的响应速度和用户体验。
 * <br>引用文件：<AbilityKit/native_child_process.h><br>库：libchild_process.so
 * 
 * ## 约束与限制
 * 
 * ### 功能限制
 * 
 * - 创建的子进程不支持创建UI界面。
 * - 创建的子进程不支持依赖Context的API调用（包括Context模块自身API及将Context实例作为入参的API）。
 * - 仅允许在主进程中创建子进程，子进程内不支持再次创建子进程。
 * 
 * ### 规格限制
 * 
 * - 通过本模块中定义的创建子进程的接口和childProcessManager中定义的创建子进程的接口启动的子进程总数最大为512个（系统资源充足情况下），
 * 其中startChildProcess接口在SELF_FORK模式下启动的子进程不计入总数内。
 *
 * @kit AbilityKit
 * @library libchild_process.so
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 12
 */

#ifndef OHOS_ABILITY_RUNTIME_C_NATIVE_CHILD_PROCESS_H
#define OHOS_ABILITY_RUNTIME_C_NATIVE_CHILD_PROCESS_H

#include <stdbool.h>
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
     */
    NCP_NO_ERROR = 0,

    /**
     * 无效参数。 请检查传入参数的类型、取值范围和是否是nullptr。
     */
    NCP_ERR_INVALID_PARAM = 401,

    /**
     * 当前设备类型不支持创建Native子进程，请使用其他类型的设备尝试。
     */
    NCP_ERR_NOT_SUPPORTED = 801,

    /**
     * 内部错误。请重启应用或设备再尝试。
     */
    NCP_ERR_INTERNAL = 16000050,

    /**
     * 在Native子进程的启动过程中不能再次创建新的子进程，可以等待当前子进程启动完成后再次尝试。从API version 15开始被废弃。
     */
    NCP_ERR_BUSY = 16010001,

    /**
     * 启动Native子进程超时。可能是系统资源不足或动态库加载耗时过长，请检查系统资源状态，优化动态库加载逻辑。
     */
    NCP_ERR_TIMEOUT = 16010002,

    /**
     * 服务端出错。请尝试重新执行操作，如问题持续存在请重启应用或设备再尝试。
     */
    NCP_ERR_SERVICE_ERROR = 16010003,

    /**
     * 多进程模式已关闭，不允许启动子进程。请更换其他类型的设备再尝试。
     */
    NCP_ERR_MULTI_PROCESS_DISABLED = 16010004,

    /**
     * 不允许在子进程中再次创建进程。请在主进程中创建子进程，避免在子进程中嵌套创建。
     */
    NCP_ERR_ALREADY_IN_CHILD = 16010005,

    /**
     * 到达最大子进程数量限制，不能再创建子进程。请先终止不需要的子进程后再创建新的子进程。
     */
    NCP_ERR_MAX_CHILD_PROCESSES_REACHED = 16010006,

    /**
     * 子进程加载动态库失败，文件不存在或者未实现对应的方法并导出。请检查动态库文件路径和名称是否正确，确保动态库实现并导出了对应的方法。
     */
    NCP_ERR_LIB_LOADING_FAILED = 16010007,

    /**
     * 子进程调用动态库的OnConnect方法失败，可能返回了无效的IPC对象指针。请检查NativeChildProcess_OnConnect函数的实现，确保返回有效的IPC对象指针。
     */
    NCP_ERR_CONNECTION_FAILED = 16010008,

    /**
     * 父进程调用解注册Native子进程退出回调，未找到注册的回调函数。
     * @since 20
     */
    NCP_ERR_CALLBACK_NOT_EXIST = 16010009,

    /**
     * 传入的进程pid不存在，或并非当前进程所创建的子进程pid，或属于{@link childProcessManager.startChildProcess}接口在SELF_FORK模式下启动的子进程。
     * @since 22
     */
    NCP_ERR_INVALID_PID = 16010010,
} Ability_NativeChildProcess_ErrCode;

/**
 * @brief 定义Native子进程数据沙箱与网络环境的共享模式。数据沙箱是进程的文件系统隔离环境，控制进程对文件和数据的访问权限；网络环境是进程的网络访问配置，控制进程的网络连接和通信能力。
 *
 * @since 13
 */
typedef enum NativeChildProcess_IsolationMode {
    /**
     * 普通隔离模式下，父进程与子进程共享同一沙箱环境或网络环境。
     */
    NCP_ISOLATION_MODE_NORMAL = 0,

    /**
     * 在隔离模式下，父进程与子进程不共享同一沙箱环境或网络环境。
     */
    NCP_ISOLATION_MODE_ISOLATED = 1,
} NativeChildProcess_IsolationMode;

/**
 * @brief 启动子进程的配置信息，包括子进程的进程名、数据沙箱与网络环境的共享模式、主进程与子进程的uid是否隔离的配置。开发者可以使用
 * {@link OH_Ability_ChildProcessConfigs_SetProcessName}、{@link OH_Ability_ChildProcessConfigs_SetIsolationMode}、
 * {@link OH_Ability_ChildProcessConfigs_SetIsolationUid}接口来修改相应的配置信息。
 *
 * @since 20
 */
typedef struct Ability_ChildProcessConfigs Ability_ChildProcessConfigs;

/**
 * @brief 创建一个子进程配置信息对象。创建对象成功后需要通过调用{@link OH_Ability_DestroyChildProcessConfigs}来销毁对象从而避免内存泄漏。
 *
 * @return 返回一个指向{@link Ability_ChildProcessConfigs}对象的指针 - 子进程配置信息对象创建成功。
 *     <br>返回nullptr - 发生内部错误或者内存分配失败。
 * @since 20
 */
Ability_ChildProcessConfigs* OH_Ability_CreateChildProcessConfigs();

/**
 * @brief 销毁一个子进程配置信息对象，并释放其内存，在调用该接口后，要避免继续使用该指针。
 *
 * @param configs 需要销毁的子进程配置信息对象指针。在调用该接口后，对象指针将失效，避免继续使用该指针。传入空指针时返回{@link NCP_ERR_INVALID_PARAM}错误码。
 * @return NCP_NO_ERROR - 操作成功。
 *     <br>NCP_ERR_INVALID_PARAM - 传入参数为nullptr。
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_DestroyChildProcessConfigs(Ability_ChildProcessConfigs* configs);

/**
 * @brief 设置子进程配置信息对象的数据沙箱与网络环境的共享模式，详见{@link NativeChildProcess_IsolationMode}。该设置仅当调用
 * {@link OH_Ability_StartNativeChildProcessWithConfigs}、{@link OH_Ability_CreateNativeChildProcessWithConfigs}接口时生效。
 *
 * @param configs 子进程的配置信息对象指针。不能为nullptr。
 * @param isolationMode 要设置的数据沙箱与网络环境的共享模式。NCP_ISOLATION_MODE_NORMAL适用于父子进程需要共享数据沙箱或网络环境的场景（如需要访问父进程文件、共享网络连接等），
 *     NCP_ISOLATION_MODE_ISOLATED适用于需要增强安全隔离的场景（如处理不受信任的数据、运行不受信任的代码等）。如果不设置默认为NCP_ISOLATION_MODE_NORMAL。
 * @return NCP_NO_ERROR - 执行成功。
 *     <br>NCP_ERR_INVALID_PARAM - 传入参数configs为nullptr。
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_ChildProcessConfigs_SetIsolationMode(
    Ability_ChildProcessConfigs* configs, NativeChildProcess_IsolationMode isolationMode);

/**
 * @brief 设置子进程配置信息对象的uid是否隔离。例如用于浏览器的安全加固场景，设置主进程与子进程的uid隔离。
 * <br>该设置仅在NativeChildProcess_IsolationMode为NCP_ISOLATION_MODE_ISOLATED时生效。不调用该接口设置isolationUid时，则默认为false，
 * 即子进程与主进程拥有相同uid。
 * <br>该设置仅当调用{@link OH_Ability_StartNativeChildProcessWithConfigs}、
 * {@link OH_Ability_CreateNativeChildProcessWithConfigs}接口时生效。
 *
 * @param configs 子进程的配置信息对象指针。不能为nullptr。
 * @param isolationUid 控制子进程是否使用独立的uid。true表示子进程拥有独立的uid（适用于需要增强安全隔离的场景，如浏览器安全加固、处理不受信任数据等），false表示子进程与主进程拥有相同uid（
 *     适用于父子进程需要共享资源的场景）。不调用该接口设置时默认为false。该设置仅在NativeChildProcess_IsolationMode为NCP_ISOLATION_MODE_ISOLATED时生效。
 * @return NCP_NO_ERROR - 执行成功。
 *     <br>NCP_ERR_INVALID_PARAM - 传入参数configs为nullptr。
 * @since 21
 */
Ability_NativeChildProcess_ErrCode OH_Ability_ChildProcessConfigs_SetIsolationUid(
    Ability_ChildProcessConfigs* configs, bool isolationUid);

/**
 * @brief 设置子进程配置信息对象中的进程名称。该设置仅当调用{@link OH_Ability_StartNativeChildProcessWithConfigs}、
 * {@link OH_Ability_CreateNativeChildProcessWithConfigs}接口时生效。
 *
 * @param configs 子进程的配置信息对象指针。不能为nullptr。
 * @param processName 设置的子进程名字符串必须是非空字符串，并且只能由字母、数字和下划线构成。最大长度为64字符。最终的进程名是{bundleName}:{processName}。
 * @return NCP_NO_ERROR - 执行成功。
 *     <br>NCP_ERR_INVALID_PARAM - 传入参数configs为nullptr，或者processName包含除字母、数字、下划线以外的字符，或者processName长度超过64字符，
 *     或者processName为空字符串。
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_ChildProcessConfigs_SetProcessName(Ability_ChildProcessConfigs* configs,
    const char* processName);

/**
 * @brief 定义通知子进程启动结果的回调函数。
 *
 * @param errCode 回调函数返回的错误码，可用的值如下：
 *     <br>{@link NCP_NO_ERROR} - 创建子进程成功。
 *     <br>{@link NCP_ERR_LIB_LOADING_FAILED} - 加载动态库文件失败或动态库中未实现必要的导出函数。
 *     <br>{@link NCP_ERR_CONNECTION_FAILED} - 动态库中实现的OnConnect方法未返回有效的IPC Stub指针。
 *     <br>详见{@link Ability_NativeChildProcess_ErrCode}定义。
 * @param remoteProxy 子进程的IPC对象指针，出现异常时可能为nullptr：使用完毕后需要调用{@link OH_IPCRemoteProxy_Destroy}方法释放。
 * @see OH_Ability_CreateNativeChildProcess
 * @see OH_IPCRemoteProxy_Destory
 * @since 12
 */
typedef void (*OH_Ability_OnNativeChildProcessStarted)(int errCode, OHIPCRemoteProxy *remoteProxy);

/**
 * @brief 创建子进程并加载参数中指定的动态链接库文件。子进程的启动结果通过回调异步通知调用方。该回调在独立线程中执行，需要确保线程同步，且不能执行高耗时操作避免长时间阻塞。
 * <br>参数所指定的动态库必须实现并导出下列函数：
 * <br>1. OHIPCRemoteStub* NativeChildProcess_OnConnect()
 * <br>2. void NativeChildProcess_MainProc()
 * <br>处理逻辑顺序如下列伪代码所示：
 * <br>主进程：
 * <br>1. OH_Ability_CreateNativeChildProcess(libName, onProcessStartedCallback)
 * <br>子进程：
 * <br>2. dlopen(libName)
 * <br>3. dlsym("NativeChildProcess_OnConnect")
 * <br>4. dlsym("NativeChildProcess_MainProc")
 * <br>5. ipcRemote = NativeChildProcess_OnConnect()
 * <br>6. NativeChildProcess_MainProc()
 * <br>主进程：
 * <br>7. onProcessStartedCallback(ipcRemote, errCode)
 * <br>子进程：
 * <br>8. 在NativeChildProcess_MainProc()函数返回后子进程退出。
 *
 * @param libName 子进程中加载的动态库文件名称，不能为nullptr。
 * @param onProcessStarted 通知子进程启动结果的回调函数指针，不能为nullptr。详见{@link OH_Ability_OnNativeChildProcessStarted}。
 * @return {@link NCP_NO_ERROR} - 调用成功，但子进程的实际启动结果由回调函数通知。
 *     <br>{@link NCP_ERR_INVALID_PARAM} - 无效的动态库名称或者回调函数指针。
 *     <br>{@link NCP_ERR_NOT_SUPPORTED} - 当前设备不支持创建Native子进程。
 *     <br>{@link NCP_ERR_MULTI_PROCESS_DISABLED} - 当前设备已关闭多进程模式。
 *     <br>{@link NCP_ERR_ALREADY_IN_CHILD} - 不允许在子进程中再次创建子进程。
 *     <br>{@link NCP_ERR_MAX_CHILD_PROCESSES_REACHED} - 到达最大Native子进程数限制。
 *     <br>详见{@link Ability_NativeChildProcess_ErrCode}定义。
 * @see OH_Ability_OnNativeChildProcessStarted
 * @since 12
 */
int OH_Ability_CreateNativeChildProcess(const char* libName,
                                        OH_Ability_OnNativeChildProcessStarted onProcessStarted);

/**
 * @brief 根据传入的子进程配置信息创建子进程，并加载参数中指定的动态链接库文件。子进程的启动结果通过回调异步通知调用方。该回调在独立线程中执行，需要确保线程同步，且不能执行高耗时操作避免长时间阻塞。
 * <br>参数所指定的动态库必须实现并导出下列函数：
 * <br>1. OHIPCRemoteStub* NativeChildProcess_OnConnect()
 * <br>2. void NativeChildProcess_MainProc()
 * <br>处理逻辑顺序如下列伪代码所示：
 * <br>主进程：
 * <br>1. OH_Ability_CreateNativeChildProcessWithConfigs(libName, configs, onProcessStartedCallback)
 * <br>子进程：
 * <br>2. dlopen(libName)
 * <br>3. dlsym("NativeChildProcess_OnConnect")
 * <br>4. dlsym("NativeChildProcess_MainProc")
 * <br>5. ipcRemote = NativeChildProcess_OnConnect()
 * <br>6. NativeChildProcess_MainProc()
 * <br>主进程：
 * <br>7. onProcessStartedCallback(ipcRemote, errCode)
 * <br>子进程：
 * <br>8. 在NativeChildProcess_MainProc()函数返回后子进程退出。
 *
 * @param libName 子进程中加载的动态库文件名称，不能为nullptr。
 * @param configs 子进程的配置信息参数，不能为nullptr。
 * @param onProcessStarted 通知子进程启动结果的回调函数指针，不能为nullptr，详见OH_Ability_OnNativeChildProcessStarted。
 * @return NCP_NO_ERROR - 执行成功。
 *     <br>NCP_ERR_INVALID_PARAM - 传入参数无效。
 *     <br>NCP_ERR_NOT_SUPPORTED - 当前设备不支持创建Native子进程。
 *     <br>NCP_ERR_MULTI_PROCESS_DISABLED - 当前设备已关闭多进程模式，不允许启动子进程。
 *     <br>NCP_ERR_ALREADY_IN_CHILD - 不允许在子进程中再次创建子进程。
 *     <br>NCP_ERR_MAX_CHILD_PROCESSES_REACHED - 超过最大Native子进程数限制。
 *     <br>详见Ability_NativeChildProcess_ErrCode定义。
 * @see OH_Ability_OnNativeChildProcessStarted
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_CreateNativeChildProcessWithConfigs(const char* libName,
    Ability_ChildProcessConfigs* configs, OH_Ability_OnNativeChildProcessStarted onProcessStarted);

/**
 * @brief 传递给子进程的文件描述符信息。
 *
 * @since 13
 */
typedef struct NativeChildProcess_Fd {
    /**
     * 文件描述符的键，最大长度为20字符。
     */
    char* fdName;

    /**
     * 文件描述符的值。
     */
    int32_t fd;

    /**
     * 下一个文件描述记录指针。
     */
    struct NativeChildProcess_Fd* next;
} NativeChildProcess_Fd;

/**
 * @brief 传递给子进程的文件描述符信息列表，文件描述符记录个数不能超过16个。
 *
 * @since 13
 */
typedef struct NativeChildProcess_FdList {
    /** 子进程文件描述符记录链表中的第一个记录。
     */
    struct NativeChildProcess_Fd* head;
} NativeChildProcess_FdList;

/**
 * @brief 启动子进程的配置选项。
 *
 * @since 13
 */
typedef struct NativeChildProcess_Options {
    /** 子进程所采用的隔离模式。
     */
    NativeChildProcess_IsolationMode isolationMode;

    /**
     * 预留字段，供未来扩展使用。
     */
    int64_t reserved;
} NativeChildProcess_Options;

/**
 * @brief 传递给子进程的参数。
 *
 * @since 13
 */
typedef struct NativeChildProcess_Args {
    /**
     * 入口参数，大小不能超过150KB。
     */
    char* entryParams;

    /** 传递给子进程的文件描述符信息列表。
     */
    struct NativeChildProcess_FdList fdList;
} NativeChildProcess_Args;

/**
 * @brief 启动Native子进程，加载参数中指定的动态链接库文件并调用入口函数。指定的动态库必须实现一个以{@link NativeChildProcess_Args}为参数的函数（函数名称可自定义），并导出该函数。
 * 支持传参到子进程。子进程中不支持创建ArkTS基础运行时环境。
 * <br>示例如下：
 * <br>void Main(NativeChildProcess_Args args);
 * <br>处理逻辑顺序如下列伪代码所示：
 * <br>主进程：
 * <br>1. OH_Ability_StartNativeChildProcess(entryPoint, args, options)
 * <br>子进程：
 * <br>2. dlopen(libName)
 * <br>3. dlsym("Main")
 * <br>4. Main(args)
 * <br>5. 子进程将在Main(args)函数返回后退出。
 *
 * @param entry 子进程中调用动态库的符号和入口函数，中间用“:”隔开（例如“libentry.so:Main”），不能为nullptr。
 * @param args 传递给子进程的参数。
 * @param options 子进程选项。
 * @param pid 输出参数，不能为nullptr，表示被启动的子进程号，只有当接口调用成功该子进程pid才有效。
 * @return NCP_NO_ERROR - 调用成功。
 *     <br>NCP_ERR_INVALID_PARAM - 无效的动态库名称或者回调函数指针。
 *     <br>NCP_ERR_NOT_SUPPORTED - 当前设备不支持创建Native子进程。
 *     <br>NCP_ERR_ALREADY_IN_CHILD - 不允许在子进程中再次创建子进程。
 *     <br>NCP_ERR_MAX_CHILD_PROCESSES_REACHED - 到达最大Native子进程数限制。
 *     <br>详见Ability_NativeChildProcess_ErrCode定义。
 * @see OH_Ability_OnNativeChildProcessStarted
 * @since 13
 */
Ability_NativeChildProcess_ErrCode OH_Ability_StartNativeChildProcess(
    const char* entry, NativeChildProcess_Args args,
    NativeChildProcess_Options options, int32_t *pid);

/**
 * @brief 根据参数中的子进程配置信息启动Native子进程，加载指定的动态链接库文件并调用入口函数。支持传参到子进程。指定的动态库必须实现一个以{@link NativeChildProcess_Args}为参数的函数（
 * 函数名称可自定义），并导出该函数。
 * <br>示例如下：
 * <br>void Main(NativeChildProcess_Args args);
 * <br>处理逻辑顺序如下列伪代码所示：
 * <br>主进程：
 * <br>1. OH_Ability_StartNativeChildProcessWithConfigs(entryPoint, args, configs, &pid)
 * <br>子进程：
 * <br>2. dlopen(libName)
 * <br>3. dlsym("Main")
 * <br>4. Main(args)
 * <br>5. 子进程将在Main(args)函数返回后退出。
 *
 * @param entry 子进程中调用动态库的符号和入口函数，中间用“:”隔开（例如“libentry.so:Main”），不能为nullptr。
 * @param args 传给子进程的参数，不能为nullptr。
 * @param configs 子进程的配置信息参数。
 * @param pid 输出参数，不能为nullptr，表示被启动的子进程号，只有当接口调用成功该子进程pid才有效。
 * @return NCP_NO_ERROR - 执行成功。
 *     <br>NCP_ERR_INVALID_PARAM - 传入参数无效。
 *     <br>NCP_ERR_NOT_SUPPORTED - 当前设备不支持创建Native子进程。
 *     <br>NCP_ERR_ALREADY_IN_CHILD - 不允许在子进程中再次创建子进程。
 *     <br>NCP_ERR_MAX_CHILD_PROCESSES_REACHED - 超过最大Native子进程数限制。
 *     <br>详见Ability_NativeChildProcess_ErrCode定义。
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_StartNativeChildProcessWithConfigs(
    const char* entry, NativeChildProcess_Args args, Ability_ChildProcessConfigs* configs, int32_t *pid);

/**
 * @brief 通过{@link OH_Ability_StartNativeChildProcess}或{@link OH_Ability_StartNativeChildProcessWithConfigs}启动子进程后，
 * 子进程能够在任意so和任意子线程中获取启动参数{@link NativeChildProcess_Args}。参数在子进程启动时传递并存储在进程全局上下文中，生命周期贯穿子进程整个运行期间，可在子进程任意位置随时获取。
 *
 * @return 返回指向当前子进程启动参数的指针。
 * @since 17
 */
NativeChildProcess_Args* OH_Ability_GetCurrentChildProcessArgs();

/**
 * @brief 用于获取Native子进程退出信息的回调函数。
 *
 * @param pid 启动的子进程id。
 * @param signal 子进程退出信号值，表示子进程的退出原因。常见的信号值包括：1（SIGHUP挂起）、2（SIGINT中断）、9（SIGKILL强制终止）、15（SIGTERM终止）等。
 * @since 20
 */
typedef void (*OH_Ability_OnNativeChildProcessExit)(int32_t pid, int32_t signal);

 /**
 * @brief 注册Native子进程退出回调函数。只有{@link OH_Ability_StartNativeChildProcess}、
 * {@link OH_Ability_StartNativeChildProcessWithConfigs}和{@link childProcessManager.startNativeChildProcess}
 * 启动的子进程退出时才会触发所注册的回调函数。回调函数在独立线程中执行，触发时机为子进程退出后，signal参数表示子进程退出信号类型。当重复注册同一个回调函数时，子进程退出时只会执行一次回调函数。回调函数实现需要注意线程同步，
 * 且不能执行高耗时操作。
 * <br>参数必须实现{@link OH_Ability_OnNativeChildProcessExit}入口函数。详见{@link 注册Native子进程退出回调}。
 *
 * @param onProcessExit 子进程退出的回调函数入口，不能为nullptr。
 * @return NCP_NO_ERROR - 调用成功。
 *     <br>NCP_ERR_INVALID_PARAM - 传入参数onProcessExit为nullptr或无效。
 *     <br>NCP_ERR_INTERNAL - 内部错误。
 *     <br>详见Ability_NativeChildProcess_ErrCode。
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_RegisterNativeChildProcessExitCallback(
    OH_Ability_OnNativeChildProcessExit onProcessExit);

 /**
 * @brief 解注册子进程退出回调。
 * <br>参数必须实现{@link OH_Ability_OnNativeChildProcessExit}入口函数。详见{@link 解注册Native子进程退出回调}。
 *
 * @param onProcessExit 子进程退出的回调函数入口，不能为nullptr。
 * @return NCP_NO_ERROR - 调用成功。
 *     <br>NCP_ERR_INVALID_PARAM - 参数不合法，传入参数onProcessExit为nullptr或无效。
 *     <br>NCP_ERR_INTERNAL - 内部错误。
 *     <br>NCP_ERR_CALLBACK_NOT_EXIST - 未找到回调函数。
 *     <br>详见Ability_NativeChildProcess_ErrCode。
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_UnregisterNativeChildProcessExitCallback(
    OH_Ability_OnNativeChildProcessExit onProcessExit);

/**
 * @brief 终止当前进程创建的子进程。该接口通过发送终止信号强制结束子进程，子进程立即停止执行并退出。终止后子进程资源被系统回收，如已注册退出回调则会被触发。
 *
 * @param pid 要终止的子进程pid。
 * @return NCP_NO_ERROR - 调用成功。
 *     <br>NCP_ERR_SERVICE_ERROR - 服务端出错。
 *     <br>NCP_ERR_INVALID_PID - 所传入的子进程pid不合法。传入的进程pid不存在，或并非当前进程所创建的子进程pid，或属于
 *     {@link childProcessManager.startChildProcess}接口在SELF_FORK模式下启动的子进程。
 *     <br>详见Ability_NativeChildProcess_ErrCode。
 * @since 22
 */
Ability_NativeChildProcess_ErrCode OH_Ability_KillChildProcess(int32_t pid);

/**
 * @brief 查询是否允许调用者在此设备上创建{@link Native子进程}。
 *
 * @return 是否允许调用者创建Native子进程。
 *     <br>true：允许创建Native子进程。
 *     <br>false：不允许创建Native子进程。
 *     <br>默认值：false。
 * @since 26.0.0
 */
bool OH_Ability_IsNativeChildProcessSupported();

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
#endif // OHOS_ABILITY_RUNTIME_C_NATIVE_CHILD_PROCESS_H
