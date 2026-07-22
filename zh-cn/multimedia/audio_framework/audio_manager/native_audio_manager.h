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
 * @brief 声明音频管理相关的接口。
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
 * @brief 声明音频管理器。用于管理音频管理相关功能。
 *
 * @since 12
 */
typedef struct OH_AudioManager OH_AudioManager;

/**
 * @brief 音频场景变化回调函数的原型定义，用于传递给{@link OH_AudioManager_RegisterAudioSceneChangeCallback}。
 *
 * @param userData 用户自定义数据指针。
 * @param scene 切换后的音频场景。
 * @since 20
 */
typedef void (*OH_AudioManager_OnAudioSceneChangeCallback) (
    void *userData,
    OH_AudioScene scene
);

/**
 * @brief 获取音频管理器。
 * <br>使用音频管理器相关功能，首先需要获取音频管理器实例。
 *
 * @param audioManager 指向{@link OH_AudioManager}用于接收创建的音频管理器实例。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数audioManager为nullptr。
 * @since 12
 */
OH_AudioCommon_Result OH_GetAudioManager(OH_AudioManager **audioManager);
/**
 * @brief 获取音频场景模式。
 *
 * @param manager the {@link OH_AudioManager} handle received from {@link OH_GetAudioManager}.
 * @param scene 指向{@link OH_AudioScene}用于接收返回的音频场景模式。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1.参数audioManager为nullptr;
 *     <br>2.参数scene为nullptr。
 * @since 12
 */
OH_AudioCommon_Result OH_GetAudioScene(OH_AudioManager* manager, OH_AudioScene *scene);

/**
 * @brief 注册音频场景切换回调函数。
 *
 * @param manager 指向{@link OH_AudioManager}用于接收创建的音频管理器实例。
 * @param callback 当音频场景切换时，将调用此回调函数{@link OH_AudioManager_OnAudioSceneChangeCallback}。
 * @param userData 用户自定义数据指针。
 * @return
 *     {@link AUDIOCOMMON_RESULT_SUCCESS} if the execution is successful
 *     {@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}
 *                                                   1.param of manager is nullptr
 *                                                   2.param of callback is nullptr
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 20
 */
OH_AudioCommon_Result OH_AudioManager_RegisterAudioSceneChangeCallback(OH_AudioManager *manager,
    OH_AudioManager_OnAudioSceneChangeCallback callback, void *userData);

/**
 * @brief 取消注册音频场景切换回调函数。
 *
 * @param manager 指向{@link OH_AudioManager}用于接收创建的音频管理器实例。
 * @param callback 指向{@link OH_AudioManager_OnAudioSceneChangeCallback}传入的回调函数，用于取消注册。
 * @return
 *     {@link AUDIOCOMMON_RESULT_SUCCESS} if the execution is successful
 *     {@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}
 *                                                   1.param of manager is nullptr
 *                                                   2.param of callback is nullptr
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 * @since 20
 */
OH_AudioCommon_Result OH_AudioManager_UnregisterAudioSceneChangeCallback(OH_AudioManager *manager,
    OH_AudioManager_OnAudioSceneChangeCallback callback);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_MANAGER_H
/** @} */