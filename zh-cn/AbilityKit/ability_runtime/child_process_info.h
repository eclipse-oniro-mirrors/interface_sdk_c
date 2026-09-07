/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup AbilityRuntime
 * @{
 *
 * @brief Defines the child process info types and accessor APIs.
 *
 * @since 26.1.0
 */

/**
 * @file child_process_info.h
 *
 * @brief Defines the child process info type and accessor functions.
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 26.1.0
 */

#ifndef ABILITY_RUNTIME_CHILD_PROCESS_INFO_H
#define ABILITY_RUNTIME_CHILD_PROCESS_INFO_H

#include <stdint.h>
#include "ability_runtime_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义OH_AbilityRuntime_ChildProcessInfos指针。
 * @since 26.1.0
 */
typedef struct OH_AbilityRuntime_ChildProcessInfos *OH_AbilityRuntime_ChildProcessInfosHandle;

/**
 * @brief 定义OH_AbilityRuntime_ChildProcessInfo指针。
 * @since 26.1.0
 */
typedef struct OH_AbilityRuntime_ChildProcessInfo *OH_AbilityRuntime_ChildProcessInfoHandle;

/**
 * @brief 按其索引从集合中检索特定子进程信息句柄。
 *
 * @param infos 关于自身应用程序中所有子进程的信息。
 * @param index 要检索的子进程信息的索引。必须严格小于计数。
 * @param info 检索到的指定索引的单个子进程信息句柄。
 * @return <ul>
 * 如果操作成功，则返回<li>{@link_RUNTIME_ERROR_CODE_NO_ERROR}。</li>
 * <li>{@link_RUNTIME_ERROR_CODE_PARAM_INVALID}如果提供的参数无效。</li>
 * </ul>
 * @since 26.1.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_GetChildProcessInfoByIndex(
    OH_AbilityRuntime_ChildProcessInfosHandle infos, uint32_t index,
    OH_AbilityRuntime_ChildProcessInfoHandle *info);

/**
 * @brief 获取子进程信息的PID。
 *
 * @param info 指向子进程信息的指针。不能是nullptr。
 * @param pid 输出参数，返回子进程PID。不能是nullptr。
 * @return <ul>
 * 如果操作成功，则返回<li>{@link_RUNTIME_ERROR_CODE_NO_ERROR}。</li>
 * <li>{@link_RUNTIME_ERROR_CODE_PARAM_INVALID}如果提供的参数无效。</li>
 * </ul>
 * @since 26.1.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ChildProcessInfo_GetPid(
    OH_AbilityRuntime_ChildProcessInfoHandle info, int32_t *pid);

/**
 * @brief 获取子进程的父进程PID。
 *
 * @param info 指向子进程信息的指针。不能是nullptr。
 * @param parentPid 输出参数，返回父进程PID。不能是nullptr。
 * @return <ul>
 * 如果操作成功，则返回<li>{@link_RUNTIME_ERROR_CODE_NO_ERROR}。</li>
 * <li>{@link_RUNTIME_ERROR_CODE_PARAM_INVALID}如果提供的参数无效。</li>
 * </ul>
 * @since 26.1.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ChildProcessInfo_GetParentPid(
    OH_AbilityRuntime_ChildProcessInfoHandle info, int32_t *parentPid);

/**
 * @brief 获取子进程信息的进程名称。
 *
 * @param info 【in】指向子进程信息的指针。它不能为NULL。
 * @param processName 【out】表示接收进程名的缓冲区。
 * @param processNameSize 【in】表示缓冲区的大小（以字节为单位），包括尾随NUL。
 * @param requiredSize 【out】所需的大小（以字节为单位），包括尾随NUL。
 * @return <ul>
 * 如果操作成功，则返回<li>{@link_RUNTIME_ERROR_CODE_NO_ERROR}。</li>
 * <li>{@link_RUNTIME_ERROR_CODE_PARAM_INVALID}如果processName或requireSize为NULL，则
 * 或者processNameSize为0。</li>
 * <li>如果缓冲区太小，则会出现<li>{@link_RUNTIME_ERROR_CODE_BUFFER_TOO_SMALL}。</li>
 * <li>如果字符串拷贝操作失败，则会出现<li>{@link_RUNTIME_ERROR_CODE_INTERNAL}。</li>
 * </ul>
 * @since 26.1.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ChildProcessInfo_GetProcessName(
    OH_AbilityRuntime_ChildProcessInfoHandle info, char *processName, uint32_t processNameSize, uint32_t *requiredSize);

/**
 * @brief 发布子进程信息收集。
 *
 * @param infos 【in】要释放的子进程信息。它不能为NULL。
 * 释放后，handle将被设置为NULL。
 * @since 26.1.0
 */
void OH_AbilityRuntime_ReleaseChildProcessInfos(OH_AbilityRuntime_ChildProcessInfosHandle *infos);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // ABILITY_RUNTIME_CHILD_PROCESS_INFO_H