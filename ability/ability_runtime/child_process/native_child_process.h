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

#include <stdbool.h>
#include "AbilityKit/ability_runtime/child_process_info.h"
#include "IPCKit/ipc_cparcel.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines an enum for the error codes used by the native child process module.
 * @since 12
 */
typedef enum Ability_NativeChildProcess_ErrCode {
    /**
     * Operation successful.
     *
     * @since 12
     */
    NCP_NO_ERROR = 0,

    /**
     * Invalid parameter.
     *
     * @since 12
     */
    NCP_ERR_INVALID_PARAM = 401,

    /**
     * Creating a native child process is not supported.
     *
     * @since 12
     */
    NCP_ERR_NOT_SUPPORTED = 801,

    /**
     * Internal error.
     *
     * @since 12
     */
    NCP_ERR_INTERNAL = 16000050,

    /**
     * A new child process cannot be created during the startup of another native child process. You can try again
     * after the child process is started. This function is deprecated since API version 15.
     *
     * @since 12
     */
    NCP_ERR_BUSY = 16010001,

    /**
     * Starting the native child process times out.
     *
     * @since 12
     */
    NCP_ERR_TIMEOUT = 16010002,

    /**
     * Server error.
     *
     * @since 12
     */
    NCP_ERR_SERVICE_ERROR = 16010003,

    /**
     * The multi-process mode is disabled. A child process cannot be started.
     *
     * @since 12
     */
    NCP_ERR_MULTI_PROCESS_DISABLED = 16010004,

    /**
     * A process cannot be created in a child process.
     *
     * @since 12
     */
    NCP_ERR_ALREADY_IN_CHILD = 16010005,

    /**
     * The number of native child processes reaches the maximum.
     *
     * @since 12
     */
    NCP_ERR_MAX_CHILD_PROCESSES_REACHED = 16010006,

    /**
     * The child process fails to load the dynamic library because the file does not exist or the corresponding method
     * is not implemented or exported.
     *
     * @since 12
     */
    NCP_ERR_LIB_LOADING_FAILED = 16010007,

    /**
     * The child process fails to call the OnConnect method of the dynamic library. An invalid IPC object pointer may
     * be returned.
     *
     * @since 12
     */
    NCP_ERR_CONNECTION_FAILED = 16010008,

    /**
     * The parent process calls the **OH_Ability_UnregisterNativeChildProcessExitCallback** function to unregister a
     * callback function, but the callback function is not found.<br>**Since**: 20
     *
     * @since 20
     */
    NCP_ERR_CALLBACK_NOT_EXIST = 16010009,

    /**
     * The specified PID does not exist, does not belong to a child process of the current process, or belongs to a
     * child process started in SELF_FORK mode by calling {@link childProcessManager.startChildProcess}.<br>**Since**:
     * 22
     *
     * @since 22
     */
    NCP_ERR_INVALID_PID = 16010010
} Ability_NativeChildProcess_ErrCode;

/**
 * @brief Enumerates the sharing modes available for the data sandbox and network environment of a native child process.
 * @since 13
 */
typedef enum NativeChildProcess_IsolationMode {
    /**
     * In normal mode, the parent and child processes share the same sandbox or network environment.
     *
     * @since 13
     */
    NCP_ISOLATION_MODE_NORMAL = 0,

    /**
     * In isolated mode, the parent and child processes each have their own separate sandbox and network environment.
     *
     * @since 13
     */
    NCP_ISOLATION_MODE_ISOLATED = 1
} NativeChildProcess_IsolationMode;

/**
 * @brief The struct describes the configuration information about a child process, including the child process name
 * and the sharing mode of the data sandbox and network environment.
 * @since 20
 */
typedef struct Ability_ChildProcessConfigs Ability_ChildProcessConfigs;

/**
 * @brief Creates a child process configuration object. When this object is no longer needed,
 * call {@link OH_Ability_DestroyChildProcessConfigs} to destroy the object to prevent memory leakage.
 *
 * @return Pointer to the {@link Ability_ChildProcessConfigs} object: The call is successful.
 *      nullptr: An internal error occurs or memory allocation fails.
 * @since 20
 */
Ability_ChildProcessConfigs* OH_Ability_CreateChildProcessConfigs();

/**
 * @brief Destroys a child process configuration object and releases its memory. After this function is called, do not
 * use the destroyed object.
 *
 * @param configs Pointer to a child process configuration object. After this function is called, the object pointer
 *      becomes invalid.
 * @return **NCP_NO_ERROR**: The call is successful.
 *      **NCP_ERR_INVALID_PARAM**: An input parameter is nullptr.
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_DestroyChildProcessConfigs(Ability_ChildProcessConfigs* configs);

/**
 * @brief Sets the sharing mode of the data sandbox and network environment for a child process configuration object.
 * For details, see {@link NativeChildProcess_IsolationMode}. This setting takes effect only when
 * {@link OH_Ability_StartNativeChildProcessWithConfigs} or
 * {@link OH_Ability_CreateNativeChildProcessWithConfigs} is called.
 *
 * @param configs Pointer to a child process configuration object. The value cannot be nullptr.
 * @param isolationMode Sharing mode of the data sandbox and network environment. For details, see **
 *      NativeChildProcess_IsolationMode**.
 * @return **NCP_NO_ERROR**: The call is successful.
 *      **NCP_ERR_INVALID_PARAM**: The parameter **configs** is nullptr.
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_ChildProcessConfigs_SetIsolationMode(
    Ability_ChildProcessConfigs* configs, NativeChildProcess_IsolationMode isolationMode);

/**
 * @brief Sets whether the child process uses an independent UID. For example, in browser security hardening scenarios,
 * you can isolate the UIDs of the main process and its child processes.
 *
 * @param configs Pointer to a child process configuration object. The value cannot be nullptr.
 * @param isolationUid Whether the child process uses an independent UID. **true** if the child process uses an
 *      independent UID; **false** if the child process and the main process share the same UID.
 * @return **NCP_NO_ERROR**: The call is successful.
 *      **NCP_ERR_INVALID_PARAM**: The parameter **configs** is nullptr.
 * @since 21
 */
Ability_NativeChildProcess_ErrCode OH_Ability_ChildProcessConfigs_SetIsolationUid(
    Ability_ChildProcessConfigs* configs, bool isolationUid);

/**
 * @brief Sets the process name in a child process configuration object.
 *
 * @param configs Pointer to a child process configuration object. The pointer cannot be null.
 * @param processName Pointer to the process name, which must be a non-empty string accepting only letters, digits, and
 *      underscores (_). The string contains a maximum of 64 characters. The final process name is in the format of {
 *      bundleName}:{processName}.
 * @return <ul>
 *      <li>{@link NCP_NO_ERROR} if the call is successful.</li>
 *      <li>{@link NCP_ERR_INVALID_PARAM} if the input parameter **configs** is nullptr, or **processName** contains
 *      characters other than letters, digits, and underscores (_).</li>
 *      </ul>
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_ChildProcessConfigs_SetProcessName(Ability_ChildProcessConfigs* configs,
    const char* processName);

/**
 * @brief Defines a callback function for notifying the child process startup result.
 *
 * @param errCode Error code returned by the callback function.
 *      {@link NCP_NO_ERROR}: The child process is created successfully.
 *      {@link NCP_ERR_LIB_LOADING_FAILED}: Loading the dynamic library file fails or the necessary export function is
 *      not implemented in the dynamic library.
 *      {@link NCP_ERR_CONNECTION_FAILED}: The **OnConnect** method implemented in the dynamic library does not return
 *      a valid IPC stub pointer.
 *      For details, see {@link Ability_NativeChildProcess_ErrCode}.
 * @param remoteProxy Pointer to the IPC object of the child process. If an exception occurs, the value may be nullptr.
 *      The object must be released by calling {@link OH_IPCRemoteProxy_Destroy} when it is no longer needed.
 * @see OH_Ability_CreateNativeChildProcess
 * @see OH_IPCRemoteProxy_Destroy
 * @since 12
 */
typedef void (*OH_Ability_OnNativeChildProcessStarted)(int errCode, OHIPCRemoteProxy *remoteProxy);

/**
 * @brief Creates a child process, loads the specified dynamic library file, and returns the startup result
 * asynchronously through a callback parameter. The callback notification is an independent thread. When implementing
 * the callback function, pay attention to thread synchronization and do not perform time-consuming operations to avoid
 * long-time blocking.
 * The dynamic library specified must implement and export the following functions:
 *   1. OHIPCRemoteStub* NativeChildProcess_OnConnect()
 *   2. void NativeChildProcess_MainProc()
 *
 * The processing logic sequence is shown in the following pseudocode:
 *   Main process:
 *     1. OH_Ability_CreateNativeChildProcess(libName, onProcessStartedCallback)
 *   Child process:
 *     2. dlopen(libName)
 *     3. dlsym("NativeChildProcess_OnConnect")
 *     4. dlsym("NativeChildProcess_MainProc")
 *     5. ipcRemote = NativeChildProcess_OnConnect()
 *     6. NativeChildProcess_MainProc()
 * Main process:
 *     7. onProcessStartedCallback(ipcRemote, errCode)
 * Child process:
 *     8. The child process exits after the NativeChildProcess_MainProc() function is returned.
 *
 * @param libName Pointer to the name of the dynamic library file loaded in the child process. The value cannot be
 *      nullptr.
 * @param onProcessStarted Pointer to the callback function for notifying the child process startup result. The value
 *      cannot be nullptr. For details, see {@link OH_Ability_OnNativeChildProcessStarted}.
 * @return {@link NCP_NO_ERROR}: The call is successful, but the actual startup result is notified by the callback
 *      function.
 *      {@link NCP_ERR_INVALID_PARAM}: The dynamic library name or callback function pointer is invalid.
 *      {@link NCP_ERR_NOT_SUPPORTED}: The device does not support the creation of native child processes.
 *      {@link NCP_ERR_MULTI_PROCESS_DISABLED}: Multi-process mode is disabled on the device.
 *      {@link NCP_ERR_ALREADY_IN_CHILD}: A process cannot be created in a child process.
 *      {@link NCP_ERR_MAX_CHILD_PROCESSES_REACHED}: The number of native child processes reaches the maximum.
 *      For details, see {@link Ability_NativeChildProcess_ErrCode}.
 * @see OH_Ability_OnNativeChildProcessStarted
 * @since 12
 */
int OH_Ability_CreateNativeChildProcess(const char* libName,
                                        OH_Ability_OnNativeChildProcessStarted onProcessStarted);

/**
 * @brief Creates a child process based on a child process configuration object and loads the specified dynamic library
 * file. The startup result is asynchronously communicated to the caller via a callback. The callback runs in a
 * separate thread. You must ensure thread synchronization and avoid time-consuming operations to prevent delays.
 *
 * @param libName Pointer to the name of the dynamic library file loaded in the child process. The value cannot be
 *      nullptr.
 * @param configs Pointer to a child process configuration object. The value cannot be nullptr.
 * @param onProcessStarted Pointer to the callback function for notifying the child process startup result. The value
 *      cannot be nullptr. For details, see **OH_Ability_OnNativeChildProcessStarted**.
 * @return <ul>
 *      <li>{@link NCP_NO_ERROR} if the call is successful.</li>
 *      <li>{@link NCP_ERR_INVALID_PARAM} if an input parameter is invalid.</li>
 *      <li>{@link NCP_ERR_NOT_SUPPORTED} if the device does not support the creation of native child processes.</li>
 *      <li>{@link NCP_ERR_MULTI_PROCESS_DISABLED} if multi-process mode is disabled on the device, and the child
 *      process cannot be started.</li>
 *      <li>{@link NCP_ERR_ALREADY_IN_CHILD} if a process cannot be created in a child process.</li>
 *      <li>{@link NCP_ERR_MAX_CHILD_PROCESSES_REACHED} if the maximum number of native child processes has been
 *      reached.</li>
 *      </ul>
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
 * @brief Starts a native child process, loads the specified dynamic library file, and calls the entry function.
 * The specified dynamic library must implement and export a function that accepts {@link NativeChildProcess_Args}
 * as its parameter (you can customize the function name). Arguments can be passed to the child process.
 * The ArkTS basic runtime environment cannot be created in the child process.
 *
 * The processing logic sequence is shown in the following pseudocode:
 *   Main process:
 *     1. OH_Ability_StartNativeChildProcess(entryPoint, args, options)
 *   Child process:
 *     2. dlopen(libName)
 *     3. dlsym("Main")
 *     4. Main(args)
 *     5. The child process exits after the Main(args) function is returned
 *
 * @param entry Pointer to the dynamic library and entry function to be loaded by the child process, for example,
 *      **libEntry.so: Main**. The value cannot be nullptr.
 * @param args Parameters passed to the child process.
 * @param options Child process options.
 * @param pid Pointer to the ID of the child process.
 * @return **NCP_NO_ERROR**: The call is successful.
 *      **NCP_ERR_INVALID_PARAM**: The dynamic library name or callback function pointer is invalid.
 *      **NCP_ERR_NOT_SUPPORTED**: The device does not support the creation of native child processes.
 *      **NCP_ERR_ALREADY_IN_CHILD**: Multi-process mode is disabled on the device.
 *      **NCP_ERR_MAX_CHILD_PROCESSES_REACHED**: The maximum number of native child processes has been reached.
 *      For details about the error codes, see **Ability_NativeChildProcess_ErrCode**.
 * @see OH_Ability_OnNativeChildProcessStarted
 * @since 13
 */
Ability_NativeChildProcess_ErrCode OH_Ability_StartNativeChildProcess(
    const char* entry, NativeChildProcess_Args args,
    NativeChildProcess_Options options, int32_t *pid);

/**
 * @brief Starts a native child process based on the child process configuration object, loads the specified dynamic
 * library file, and calls the entry function. Arguments can be passed to the child process. The specified dynamic
 * library must implement and export a function that accepts {@link NativeChildProcess_Args} as its parameter (you can
 * customize the function name).
 *
 * The processing logic sequence is shown in the following pseudocode:
 *   Main process:
 *     1. OH_Ability_StartNativeChildProcessWithConfigs(entryPoint, args, configs, &pid)
 *   Child process:
 *     2. dlopen(libName)
 *     3. dlsym("Main")
 *     4. Main(args)
 *     5. The child process exits after the Main(args) function is returned
 *
 * @param entry Pointer to the symbol and entry function of the dynamic library called in the child process, separated
 *      by a colon (:), for example, **libentry.so:Main**. The value cannot be nullptr.
 * @param args Parameters passed to the child process.
 * @param configs Pointer to a child process configuration object.
 * @param pid Pointer to the ID of the child process.
 * @return **NCP_NO_ERROR**: The call is successful.
 *      **NCP_ERR_INVALID_PARAM**: An input parameter is invalid.
 *      **NCP_ERR_NOT_SUPPORTED**: The device does not support the creation of native child processes.
 *      **NCP_ERR_ALREADY_IN_CHILD**: A process cannot be created in a child process.
 *      **NCP_ERR_MAX_CHILD_PROCESSES_REACHED**: The maximum number of native child processes has been reached.
 *      For details about the error codes, see **Ability_NativeChildProcess_ErrCode**.
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_StartNativeChildProcessWithConfigs(
    const char* entry, NativeChildProcess_Args args, Ability_ChildProcessConfigs* configs, int32_t *pid);

/**
 * @brief Used by a child process, after being started by calling {@link OH_Ability_StartNativeChildProcess}, to obtain
 * the startup parameter {@link NativeChildProcess_Args} from any .so file or child thread.
 *
 * @return Pointer to the startup parameters of the child process.
 * @since 17
 */
NativeChildProcess_Args* OH_Ability_GetCurrentChildProcessArgs();

/**
 * @brief Defines a callback to listen for child process exit.
 *
 * @param pid Pointer to the ID of the child process.
 * @param signal Signal for child process exit.
 * @since 20
 */
typedef void (*OH_Ability_OnNativeChildProcessExit)(int32_t pid, int32_t signal);

/**
 * @brief Registers a callback to listen for child process exit. When a child process started by calling
 * {@link OH_Ability_StartNativeChildProcess} or
 * {@link startNativeChildProcess in @ohos.app.ability.childProcessManager} exits abnormally, the callback function
 * is invoked. If the same callback function is registered multiple times, the callback function is executed only once
 * when the child process exits.
 *
 * @param onProcessExit Entry point of the callback function to be called when the child process exits. The value
 *      cannot be nullptr.
 * @return **NCP_NO_ERROR**: The call is successful.
 *      **NCP_ERR_INVALID_PARAM**: An input parameter is invalid.
 *      **NCP_ERR_INTERNAL**: An internal error occurs.
 *      For details, see **Ability_NativeChildProcess_ErrCode**.
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_RegisterNativeChildProcessExitCallback(
    OH_Ability_OnNativeChildProcessExit onProcessExit);

/**
 * @brief Unregisters the callback used to listen for child process exit.
 *
 * @param onProcessExit Entry point of the callback function to be called when the child process exits. The value
 *      cannot be nullptr.
 * @return **NCP_NO_ERROR**: The call is successful.
 *      **NCP_ERR_INVALID_PARAM**: An input parameter is invalid.
 *      **NCP_ERR_INTERNAL**: An internal error occurs.
 *      **NCP_ERR_CALLBACK_NOT_EXIST**: The callback function is not found.
 *      For details, see **Ability_NativeChildProcess_ErrCode**.
 * @since 20
 */
Ability_NativeChildProcess_ErrCode OH_Ability_UnregisterNativeChildProcessExitCallback(
    OH_Ability_OnNativeChildProcessExit onProcessExit);

/**
 * @brief Terminates a child process created by the current process.
 *
 * @param pid PID of the child process to terminate.
 * @return **NCP_NO_ERROR**: The call is successful.
 *      **NCP_ERR_SERVICE_ERROR**: Server error.
 *      **NCP_ERR_INVALID_PID**: The input PID is invalid.
 *      For details, see **Ability_NativeChildProcess_ErrCode**.
 * @since 22
 */
Ability_NativeChildProcess_ErrCode OH_Ability_KillChildProcess(int32_t pid);

/**
 * @brief Check whether the caller is allowed to use native process capabilities.
 *
 * @return true if the caller is allowed to create native child processes, false otherwise.
 * @since 26.0.0
 */
bool OH_Ability_IsNativeChildProcessSupported();

/**
 * @brief Acquires child process infos of the current application.
 *
 * Includes child processes created via:
 * - OH_Ability_CreateNativeChildProcess / OH_Ability_CreateNativeChildProcessWithConfigs
 * - OH_Ability_StartNativeChildProcess / OH_Ability_StartNativeChildProcessWithConfigs
 * - childProcessManager.startChildProcess (non-SELF_FORK mode)
 * - childProcessManager.startArkChildProcess
 * - childProcessManager.startNativeChildProcess
 *
 * @param infos [out] Pointer to child process info collection. It must not be NULL.
 *      When no child processes exist, the dereferenced value of the pointer **infos** is set to nullptr.
 * @param count [out] Pointer to the number of child processes. It must not be NULL.
 * @return <ul>
 *      <li>{@link NCP_NO_ERROR} if the operation is successful.</li>
 *      <li>{@link NCP_ERR_INVALID_PARAM} if infos or count is nullptr.</li>
 *      <li>{@link NCP_ERR_INTERNAL} if an internal error occurs, such as connect system service failed.</li>
 *      </ul>
 * @release OH_AbilityRuntime_ReleaseChildProcessInfos {infos}
 * @since 26.1.0
 */
Ability_NativeChildProcess_ErrCode OH_Ability_AcquireChildProcessInfos(
    OH_AbilityRuntime_ChildProcessInfosHandle* infos, uint32_t* count);

#ifdef __cplusplus
} // extern "C"
#endif

/** @} */
#endif // OHOS_ABILITY_RUNTIME_C_NATIVE_CHILD_PROCESS_H