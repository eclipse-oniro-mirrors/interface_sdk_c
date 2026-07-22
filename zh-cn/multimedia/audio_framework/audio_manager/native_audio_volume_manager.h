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
 * @file native_audio_volume_manager.h
 *
 * @brief 声明音频音量管理器接口。
 * <br>该文件接口用于创建AudioVolumeManager。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 20
 */

#ifndef NATIVE_AUDIO_VOLUME_MANAGER_H
#define NATIVE_AUDIO_VOLUME_MANAGER_H

#include <stdbool.h>
#include "native_audio_common.h"
#include "native_audiostream_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 声明音频音量管理器。音频音量管理器提供多种函数，供开发人员获取系统音量信息。
 *
 * @since 20
 */
typedef struct OH_AudioVolumeManager OH_AudioVolumeManager;

/**
 * @brief 音量变化回调函数的原型定义，用于传递给{@link OH_AudioVolumeManager_RegisterStreamVolumeChangeCallback}。
 *
 * @param userData 用户自定义数据指针。
 * @param usage 对应音量被调整的流的用途类型。
 * @param volumeLevel 修改后的音量。
 * @param updateUi 是否在UI界面显示音量变化。true表示显示，false表示不显示。
 * @since 20
 */
typedef void (*OH_AudioVolumeManager_OnStreamVolumeChangeCallback)(
    void *userData,
    OH_AudioStream_Usage usage,
    int32_t volumeLevel,
    bool updateUi
);

/**
 * @brief 铃声模式变化回调函数的原型定义，用于传递给{@link OH_AudioVolumeManager_RegisterRingerModeChangeCallback}。
 *
 * @param userData 用户自定义数据指针。
 * @param ringerMode 切换后的铃声模式。
 * @since 20
 */
typedef void (*OH_AudioVolumeManager_OnRingerModeChangeCallback)(
    void *userData,
    OH_AudioRingerMode ringerMode
);

/**
 * @brief 使用音量管理器相关功能，首先需要获取音量管理器实例。
 *
 * @param volumeManager 指向OH_AudioVolumeManager用于接收创建的音量管理器实例。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr
 *
 * @since 20
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioVolumeManager(
    OH_AudioVolumeManager **volumeManager);

/**
 * @brief 获取指定用途类型音频流的最大音量等级。
 *
 * @param volumeManager 指向OH_AudioVolumeManager用于接收创建的音量管理器实例。
 * @param usage 用于映射特定音量类型的音频流用途类型。
 * @param maxVolumeLevel 用于接收返回的最大音量。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr or invalid
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 *
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_GetMaxVolumeByUsage(OH_AudioVolumeManager *volumeManager,
    OH_AudioStream_Usage usage, int32_t *maxVolumeLevel);

/**
 * @brief 获取指定用途类型音频流的最小音量等级。
 *
 * @param volumeManager 指向OH_AudioVolumeManager用于接收创建的音量管理器实例。
 * @param usage 用于映射特定音量类型的音频流用途类型。
 * @param minVolumeLevel 用于接收返回的最小音量。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr or invalid
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 *
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_GetMinVolumeByUsage(OH_AudioVolumeManager *volumeManager,
    OH_AudioStream_Usage usage, int32_t *minVolumeLevel);

/**
 * @brief 获取指定用途类型音频流的系统音量等级。
 *
 * @param volumeManager 指向OH_AudioVolumeManager用于接收创建的音量管理器实例。
 * @param usage 用于映射特定音量类型的音频流用途类型。
 * @param volumeLevel 用于接收返回的系统音量。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr or invalid
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 *
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_GetVolumeByUsage(OH_AudioVolumeManager *volumeManager,
    OH_AudioStream_Usage usage, int32_t *volumeLevel);

/**
 * @brief 检查指定用途类型的音频流是否处于静音状态。
 *
 * @param volumeManager 指向OH_AudioVolumeManager用于接收创建的音量管理器实例。
 * @param usage 用于映射特定音量类型的音频流用途类型。
 * @param muted 用于接收返回的音频流是否静音。true表示静音，false表示未静音。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr or invalid
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 *
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_IsMuteByUsage(OH_AudioVolumeManager *volumeManager,
    OH_AudioStream_Usage usage, bool *muted);
/**
 * @brief 注册音频流音量修改回调函数。
 *
 * @param volumeManager 指向OH_AudioVolumeManager用于接收创建的音量管理器实例。
 * @param usage 监听用于映射特定音量类型的音频流用途类型。
 * @param callback 监听的音频流音量发生时，将调用此回调函数{@link OH_AudioVolumeManager_OnStreamVolumeChangeCallback}。
 * @param userData 用户自定义数据指针。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数volumeManager、usage或callback为nullptr，或usage是无效值。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统处理错误。
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_RegisterStreamVolumeChangeCallback(
    OH_AudioVolumeManager *volumeManager, OH_AudioStream_Usage usage,
    OH_AudioVolumeManager_OnStreamVolumeChangeCallback callback, void *userData);

/**
 * @brief 取消注册音频流音量修改回调函数。
 *
 * @param volumeManager 指向OH_AudioVolumeManager用于接收创建的音量管理器实例。
 * @param callback 指向{@link OH_AudioVolumeManager_RegisterStreamVolumeChangeCallback}传入的回调函数，用于取消注册。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 *
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_UnregisterStreamVolumeChangeCallback(
    OH_AudioVolumeManager *volumeManager,
    OH_AudioVolumeManager_OnStreamVolumeChangeCallback callback);

/**
 * @brief 获取当前铃声模式。
 *
 * @param volumeManager 指向OH_AudioVolumeManager用于接收创建的音量管理器实例。
 * @param ringerMode 用于接收返回的铃声模式。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 *
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_GetRingerMode(OH_AudioVolumeManager *volumeManager,
    OH_AudioRingerMode *ringerMode);

/**
 * @brief 注册铃声模式切换回调函数。
 *
 * @param volumeManager 指向OH_AudioVolumeManager用于接收创建的音量管理器实例。
 * @param callback 监听的铃声模式发生切换时，将调用此回调函数{@link OH_AudioVolumeManager_OnRingerModeChangeCallback}。
 * @param userData 用户自定义数据指针。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 *
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_RegisterRingerModeChangeCallback(
    OH_AudioVolumeManager *volumeManager,
    OH_AudioVolumeManager_OnRingerModeChangeCallback callback, void *userData);

/**
 * @brief 取消注册铃声模式切换回调函数。
 *
 * @param volumeManager 指向OH_AudioVolumeManager用于接收创建的音量管理器实例。
 * @param callback 指向{@link OH_AudioVolumeManager_RegisterRingerModeChangeCallback}传入的回调函数，用于取消注册。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} if input param is nullptr
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} system process error occurs
 *
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_UnregisterRingerModeChangeCallback(
    OH_AudioVolumeManager *volumeManager,
    OH_AudioVolumeManager_OnRingerModeChangeCallback callback);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_VOLUME_MANAGER_H
/** @} */