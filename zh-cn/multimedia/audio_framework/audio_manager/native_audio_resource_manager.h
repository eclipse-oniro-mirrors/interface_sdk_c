/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup OHAudio
 * @{
 *
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 20
 */

/**
 * @file native_audio_resource_manager.h
 *
 * @brief 本文件提供音频资源管理功能的接口。
 * <br>音频播放或录制都需要持续对音频数据进行处理，消耗系统CPU资源。
 * 当处理性能不足时，会出现杂音或卡顿问题，因此系统提供资源管理接口帮助应用开发者优化音频处理线程的性能。
 * <br>音频资源管理主要通过音频工作组实现。音频工作组是一组音频数据处理线程集合，
 * 开发者通过接口将应用内音频数据处理相关线程添加到音频工作组，合理设置数据处理的预期完成时间，系统会平衡功耗和性能，
 * 按照工作组内线程负载分配不同CPU资源，保障数据按时处理完成。
 * <br>音频工作组必须配合音频播放业务使用，支持的音频场景包括音乐、视频、听书、导航和语音通话。
 * 没有音频流播放时，系统不会对线程性能进行优化。
 * <br>音频工作组的使用数量也存在约束，每个应用进程最多创建2个工作组，且进程内所有工作组总共最多添加4个处理线程。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 20
 */

#ifndef NATIVE_AUDIO_RESOURCE_MANAGER_H
#define NATIVE_AUDIO_RESOURCE_MANAGER_H

#include "native_audio_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 声明音频资源管理结构体，该结构体用于调用音频资源管理和线程调度优化功能接口。
 *
 * @since 20
 */
typedef struct OH_AudioResourceManager OH_AudioResourceManager;

/**
 * @brief 获取音频资源管理器实例，该实例为单例，用于调用音频资源管理功能接口。
 *
 * @param resourceManager [out] 用于接收获取的音频资源管理器实例。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数resourceManager为空指针。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioResourceManager(OH_AudioResourceManager **resourceManager);

/**
 * @brief 声明音频工作组结构体，该结构体表示一组用于协同处理音频数据任务的线程，
 * 系统会以工作组为单元管理其使用的CPU资源。
 *
 * @since 20
 */
typedef struct OH_AudioWorkgroup OH_AudioWorkgroup;

/**
 * @brief 创建音频工作组。
 * <br>每个应用进程最多创建2个音频工作组，不再使用的音频工作组，
 * 及时通过{@link OH_AudioResourceManager_ReleaseWorkgroup}接口释放。
 *
 * @param resourceManager [in] 指向{@link OH_AudioManager_GetAudioResourceManager}创建的
 *     音频资源管理器实例OH_AudioResourceManager。
 * @param name [in] 创建的音频工作组名称。
 * @param group [out] 用于接收创建的音频工作组实例。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}
 *             1. 参数resourceManager为空指针；2. 参数name为空指针；3. 参数group为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_NO_MEMORY} 系统资源不足。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioResourceManager_CreateWorkgroup(OH_AudioResourceManager *resourceManager,
    const char *name, OH_AudioWorkgroup **group);

/**
 * @brief 释放音频工作组。
 *
 * @param resourceManager [in] 指向{@link OH_AudioManager_GetAudioResourceManager}创建的音频资源管理器实例。
 * @param group [in] 指向{@link OH_AudioResourceManager_CreateWorkgroup}创建的音频工作组实例。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}
 *             1. 参数resourceManager为空指针；2. 参数group为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioResourceManager_ReleaseWorkgroup(OH_AudioResourceManager *resourceManager,
    OH_AudioWorkgroup *group);

/**
 * @brief 添加当前线程到音频工作组。
 * <br>添加完成后，系统会为此线程分配一个标识符，可在{@link OH_AudioWorkgroup_RemoveThread}接口通过此标识符移除线程。
 * <br>添加到工作组的线程将参与工作组的统一调度，系统会根据工作组的任务时间要求动态调整线程的CPU资源分配。
 * <br>进程内所有工作组总共最多添加4个处理线程。
 *
 * @param group [in] 指向{@link OH_AudioResourceManager_CreateWorkgroup}创建的音频工作组实例。
 * @param tokenId [out] 用于接收系统为添加到音频工作组的线程分配的标识符。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1. 参数group为空指针；2. 参数tokenId为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_NO_MEMORY} 系统资源不足。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioWorkgroup_AddCurrentThread(OH_AudioWorkgroup *group, int32_t *tokenId);

/**
 * @brief 从音频工作组移除指定线程。
 *
 * @param group [in] 指向{@link OH_AudioResourceManager_CreateWorkgroup}创建的音频工作组实例。
 * @param tokenId [in] 待移除线程的标识符，标识符是从{@link OH_AudioWorkgroup_AddCurrentThread}接口获取的。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1. 参数group为空指针；2. 参数tokenId无效。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioWorkgroup_RemoveThread(OH_AudioWorkgroup *group, int32_t tokenId);

/**
 * @brief 通知系统音频工作组开始执行任务。此接口应在每个周期的音频数据处理前调用，
 * 处理完成后需要调用{@link OH_AudioWorkgroup_Stop}。
 * <br>系统会基于任务启动时间和预期完成时间，对音频工作组内的所有线程进行优先级调整和CPU资源分配。
 * <br>请合理设置启动和预期完成时间，如果时间间隔过短，系统无法确保音频任务能够及时完成。
 *
 * @param group [in] 指向{@link OH_AudioResourceManager_CreateWorkgroup}创建的音频工作组实例。
 * @param startTime [in] 当前音频任务的启动时间点，使用UTC时间戳，单位为ms。
 * @param deadlineTime [in] 当前音频任务的预期完成时间，使用UTC时间戳，单位为ms。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}
 *             1. 参数group为空指针；2. 参数startTime无效；3. 参数deadlineTime无效。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioWorkgroup_Start(OH_AudioWorkgroup *group, uint64_t startTime, uint64_t deadlineTime);

/**
 * @brief 通知系统音频工作组任务执行完成。此接口应在每个周期的音频数据处理完成后调用。
 *
 * @param group [in] 指向{@link OH_AudioResourceManager_CreateWorkgroup}创建的音频工作组实例。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数group为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioWorkgroup_Stop(OH_AudioWorkgroup *group);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_RESOURCE_MANAGER_H
/** @} */