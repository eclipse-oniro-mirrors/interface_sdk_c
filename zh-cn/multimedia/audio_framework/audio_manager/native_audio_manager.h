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
 * @addtogroup OHAudio
 * @{
 *
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file native_audio_manager.h
 *
 * @brief 本文件提供音频基础管理功能的接口。
 * <br>当前支持音频场景信息的查询以及音频场景变化的监听。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 12
 * @version 1.0
 */
#ifndef NATIVE_AUDIO_MANAGER_H
#define NATIVE_AUDIO_MANAGER_H

#include "native_audio_common.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 声明音频管理结构体，该结构体用于调用音频基础管理功能接口，如查询系统音频场景。
 *
 * @since 12
 */
typedef struct OH_AudioManager OH_AudioManager;

/**
 * @brief 音频场景变化回调函数的原型定义，用于{@link OH_AudioManager_RegisterAudioSceneChangeCallback}接口。
 *
 * @param userData 指向开发者在{@link OH_AudioManager_RegisterAudioSceneChangeCallback}接口传入的userData数据。
 * @param scene 变化后的音频场景。
 * @since 20
 */
typedef void (*OH_AudioManager_OnAudioSceneChangeCallback) (
    void *userData,
    OH_AudioScene scene
);

/**
 * @brief 获取音频基础管理器实例，该实例为单例，用于调用音频基础管理功能接口。
 *
 * @param audioManager [out] 指向OH_AudioManager指针的地址，用于接收获取的音频管理器实例。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数audioManager为空指针。</li>
 *         </ul>
 * @since 12
 */
OH_AudioCommon_Result OH_GetAudioManager(OH_AudioManager **audioManager);

/**
 * @brief 获取音频场景。
 * <br>音频场景主要用于表示音频通话相关的系统状态，调用者可通过音频场景识别系统是否处于语音通话或通话响铃状态。
 *
 * @param audioManager the {@link OH_AudioManager} handle received from {@link OH_GetAudioManager}.
 * @param scene [out] 用于接收获取的音频场景。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} <br>1. 参数manager为空指针；<br>2. 参数scene为空指针。</li>
 *         </ul>
 * @since 12
 */
OH_AudioCommon_Result OH_GetAudioScene(OH_AudioManager* manager, OH_AudioScene *scene);

/**
 * @brief 注册音频场景变化回调函数。
 * <br>音频场景主要用于表示音频通话相关的系统状态，调用者可通过此接口监听系统是否进入或退出通话状态。
 * <br>若不再需要监听音频场景变化，可调用{@link OH_AudioManager_UnregisterAudioSceneChangeCallback}取消注册。
 *
 * @param manager [in] 指向通过{@link OH_GetAudioManager}获取的音频管理器实例。
 * @param callback [in] 当音频场景变化时，将触发此回调函数。
 * @param userData [in] 用户自定义数据指针，回调函数触发时会携带。若无需传递数据，可传入空指针。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} <br>1. 参数manager为空指针；<br>2. 参数callback为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统错误，主要为系统服务异常。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioManager_RegisterAudioSceneChangeCallback(OH_AudioManager *manager,
    OH_AudioManager_OnAudioSceneChangeCallback callback, void *userData);

/**
 * @brief 取消注册音频场景变化回调函数。
 *
 * @param manager [in] 指向通过{@link OH_GetAudioManager}获取的音频管理器实例。
 * @param callback [in] 指向{@link OH_AudioManager_RegisterAudioSceneChangeCallback}传入的回调函数，用于取消注册。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} <br>1. 参数manager为空指针；<br>2. 参数callback为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统错误，主要为系统服务异常。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioManager_UnregisterAudioSceneChangeCallback(OH_AudioManager *manager,
    OH_AudioManager_OnAudioSceneChangeCallback callback);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_MANAGER_H
/** @} */