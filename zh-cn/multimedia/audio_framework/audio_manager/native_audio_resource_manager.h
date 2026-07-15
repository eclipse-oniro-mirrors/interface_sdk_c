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
 * @brief 声明音频资源管理相关的接口。
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
 * @brief 声明音频资源管理器。用于管理音频资源相关功能。
 *
 * @since 20
 */
typedef struct OH_AudioResourceManager OH_AudioResourceManager;

/**
 * @brief 获取音频资源管理器。
 * <br>使用音频资源管理器相关功能，首先需要获取音频资源管理器实例。
 *
 * @param resourceManager 指向OH_AudioResourceManager指针的地址，用于接收创建的音频资源管理器实例。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr
 * @since 20
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioResourceManager(OH_AudioResourceManager **resourceManager);

/**
 * @brief 声明音频工作组。用于对关键音频线程进行分组管理。
 *
 * @since 20
 */
typedef struct OH_AudioWorkgroup OH_AudioWorkgroup;

/**
 * @brief 创建音频工作组。
 *
 * @param resourceManager 指向{@link OH_AudioManager_GetAudioResourceManager}创建的音频资源管理器实例OH_AudioResourceManager。
 * @param name 要创建的音频工作组的名称。
 * @param group 指向OH_AudioWorkgroup指针的地址，用于接收返回的音频工作组实例的指针。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr
 *     {@link #AUDIOCOMMON_RESULT_ERROR_NO_MEMORY} out of workgroup resources
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 20
 */
OH_AudioCommon_Result OH_AudioResourceManager_CreateWorkgroup(OH_AudioResourceManager *resourceManager,
    const char *name, OH_AudioWorkgroup **group);

/**
 * @brief 释放音频工作组。
 *
 * @param resourceManager 指向{@link OH_AudioManager_GetAudioResourceManager}创建的音频资源管理器实例OH_AudioResourceManager。
 * @param group 指向{@link OH_AudioResourceManager_CreateWorkgroup}创建的音频工作组实例OH_AudioWorkgroup。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 20
 */
OH_AudioCommon_Result OH_AudioResourceManager_ReleaseWorkgroup(OH_AudioResourceManager *resourceManager,
    OH_AudioWorkgroup *group);

/**
 * @brief 将当前线程加入group指向的音频工作组。
 *
 * @param group 指向{@link OH_AudioResourceManager_CreateWorkgroup}创建的音频工作组实例OH_AudioWorkgroup。
 * @param tokenId 用于接收加入音频工作组的线程号。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr
 *     {@link #AUDIOCOMMON_RESULT_ERROR_NO_MEMORY} out of resources for the new thread
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 20
 */
OH_AudioCommon_Result OH_AudioWorkgroup_AddCurrentThread(OH_AudioWorkgroup *group, int32_t *tokenId);

/**
 * @brief 将tokenId对应的线程从group音频工作组中移除。
 *
 * @param group 指向{@link OH_AudioResourceManager_CreateWorkgroup}创建的音频工作组实例OH_AudioWorkgroup。
 * @param tokenId 要从音频工作组中移除的线程号。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数group为nullptr；
 *     <br>2. 参数tokenId无效。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统处理错误。
 * @since 20
 */
OH_AudioCommon_Result OH_AudioWorkgroup_RemoveThread(OH_AudioWorkgroup *group, int32_t tokenId);

/**
 * @brief 通知系统group指向的音频工作组开始工作，并告知系统当前工作组预期完成时间。
 *
 * @param group 指向{@link OH_AudioResourceManager_CreateWorkgroup}创建的音频工作组实例OH_AudioWorkgroup。
 * @param startTime 当前音频工作组启动的时间点，单位为毫秒（ms）。
 * @param deadlineTime 当前音频工作组预期完成的时间，单位为毫秒（ms）。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr, or time is invalid
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 20
 */
OH_AudioCommon_Result OH_AudioWorkgroup_Start(OH_AudioWorkgroup *group, uint64_t startTime, uint64_t deadlineTime);

/**
 * @brief 通知系统group指向的音频工作组任务已完成。
 *
 * @param group 指向{@link OH_AudioResourceManager_CreateWorkgroup}创建的音频工作组实例OH_AudioWorkgroup。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 20
 */
OH_AudioCommon_Result OH_AudioWorkgroup_Stop(OH_AudioWorkgroup *group);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_RESOURCE_MANAGER_H
/** @} */