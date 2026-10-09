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
 * @brief 本文件提供音频音量管理功能的接口。
 * <br>在介绍音量管理能力前，需要先了解如下概念：
 * <br>音量类型：系统将不同场景的音频播放流按{@link OH_AudioStream_Usage}划分。由于OH_AudioStream_Usage种类很多，为便于管理音量，系统将其进行分组，
 * 每组OH_AudioStream_Usage对应一种音量类型，例如AUDIOSTREAM_USAGE_MUSIC和AUDIOSTREAM_USAGE_MOVIE都对应媒体音量，当一种类型的音量改变，
 * 此类型对应的所有音频播放流音量都会受到影响。
 * <br>音量等级：系统是以音量等级为单位进行音量大小调节的，实际的音量增益会基于音量等级计算得出，确保调节时音量听感变化均匀。不同的音量类型，可设置的音量等级范围可以是不同的。
 * <br>铃声模式：系统内用于控制铃声和通知音行为的状态，分为响铃、振动、静音三种模式，通常在具备通话能力的设备中使用。铃声模式与铃声类型的音量存在联动关系。
 * <br>本文件提供的接口，支持开发者查询指定OH_AudioStream_Usage下的最大、最小音量等级，以及当前系统设置的音量等级和静音状态，支持监听系统音量变化，也支持查询和监听系统当前铃声模式信息。
 * <br>由于系统不希望在没有用户感知的情况下发生音量变化，本文件不提供直接设置系统音量的接口。如果开发者需要实现调节系统音量的功能，推荐使用{@link AVVolumePanel}。
 * <br>当前系统并未提供录音音量的管理功能，如果开发者需要调整录音音量，可在获取录音原始数据后自行调整数据增益。
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
 * @brief 声明音频音量管理结构体，该结构体用于调用系统音量和铃声模式查询功能接口。
 *
 * @since 20
 */
typedef struct OH_AudioVolumeManager OH_AudioVolumeManager;

/**
 * @brief 音量变化回调函数的原型定义，用于传递给{@link OH_AudioVolumeManager_RegisterStreamVolumeChangeCallback}。
 *
 * @param userData 指向开发者在{@link OH_AudioVolumeManager_RegisterStreamVolumeChangeCallback}接口传入的userData数据。
 * @param usage 对应音量被调整的流的用途类型。
 * @param volumeLevel 变化后的音量等级。
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
 * @param userData 指向开发者在{@link OH_AudioVolumeManager_RegisterRingerModeChangeCallback}接口传入的userData数据。
 * @param ringerMode 变化后的铃声模式。
 * @since 20
 */
typedef void (*OH_AudioVolumeManager_OnRingerModeChangeCallback)(
    void *userData,
    OH_AudioRingerMode ringerMode
);

/**
 * @brief 获取音量管理器实例，该实例为单例，用于调用系统音量和铃声模式查询和监听功能接口。
 *
 * @param volumeManager [out] 指向OH_AudioVolumeManager指针的地址，用于接收获取的音量管理器实例。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数volumeManager为空指针。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioVolumeManager(
    OH_AudioVolumeManager **volumeManager);

/**
 * @brief 获取指定用途类型音频流的最大音量等级。
 *
 * @param volumeManager [in] 指向通过{@link OH_AudioManager_GetAudioVolumeManager}获取的音量管理器实例。
 * @param usage [in] 用于映射特定音量类型的音频流用途类型。
 * @param maxVolumeLevel [out] 用于接收返回的最大音量等级。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数volumeManager或maxVolumeLevel为空指针，或usage是无效值。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_GetMaxVolumeByUsage(OH_AudioVolumeManager *volumeManager,
    OH_AudioStream_Usage usage, int32_t *maxVolumeLevel);

/**
 * @brief 获取指定用途类型音频流的最小音量等级。
 *
 * @param volumeManager [in] 指向通过{@link OH_AudioManager_GetAudioVolumeManager}获取的音量管理器实例。
 * @param usage [in] 用于映射特定音量类型的音频流用途类型。
 * @param minVolumeLevel [out] 用于接收返回的最小音量等级。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数volumeManager或minVolumeLevel为空指针，或usage是无效值。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_GetMinVolumeByUsage(OH_AudioVolumeManager *volumeManager,
    OH_AudioStream_Usage usage, int32_t *minVolumeLevel);

/**
 * @brief 获取指定用途类型音频流的系统音量等级。
 *
 * @param volumeManager [in] 指向通过{@link OH_AudioManager_GetAudioVolumeManager}获取的音量管理器实例。
 * @param usage [in] 用于映射特定音量类型的音频流用途类型。
 * @param volumeLevel [out] 用于接收返回的系统音量等级。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数volumeManager或volumeLevel为空指针，或usage是无效值。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_GetVolumeByUsage(OH_AudioVolumeManager *volumeManager,
    OH_AudioStream_Usage usage, int32_t *volumeLevel);

/**
 * @brief 检查指定用途类型的音频流是否处于静音状态。
 *
 * @param volumeManager [in] 指向通过{@link OH_AudioManager_GetAudioVolumeManager}获取的音量管理器实例。
 * @param usage [in] 用于映射特定音量类型的音频流用途类型。
 * @param muted [out] 用于接收返回的音频流是否静音。true表示静音，false表示未静音。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数volumeManager或muted为空指针，或usage是无效值。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_IsMuteByUsage(OH_AudioVolumeManager *volumeManager,
    OH_AudioStream_Usage usage, bool *muted);

/**
 * @brief 注册音频流音量变化回调函数。
 * <br>多次注册同一个OH_AudioStream_Usage的变化回调时，系统会保存所有不同的回调函数，在其音量变化时遍历触发。同一个回调函数，也只能用于注册一个OH_AudioStream_Usage的变化回调。
 * <br>若不再需要监听音频流音量变化，可调用{@link OH_AudioVolumeManager_UnregisterStreamVolumeChangeCallback}取消注册。
 *
 * @param volumeManager [in] 指向通过{@link OH_AudioManager_GetAudioVolumeManager}获取的音量管理器实例。
 * @param usage [in] 用于映射特定音量类型的音频流用途类型。
 * @param callback [in] 监听的音频流音量发生变化时，将调用此回调函数。
 * @param userData [in] 用户自定义数据指针，回调函数触发时会携带。若无需传递数据，可传入空指针。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数volumeManager、usage或callback为空指针，或usage是无效值。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_RegisterStreamVolumeChangeCallback(
    OH_AudioVolumeManager *volumeManager, OH_AudioStream_Usage usage,
    OH_AudioVolumeManager_OnStreamVolumeChangeCallback callback, void *userData);

/**
 * @brief 取消注册音频流音量变化回调函数。
 *
 * @param volumeManager [in] 指向通过{@link OH_AudioManager_GetAudioVolumeManager}获取的音量管理器实例。
 * @param callback [in] 需要取消注册的回调函数，该函数应与{@link OH_AudioVolumeManager_RegisterStreamVolumeChangeCallback}注册时的回调函数一致。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数volumeManager或callback为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_UnregisterStreamVolumeChangeCallback(
    OH_AudioVolumeManager *volumeManager,
    OH_AudioVolumeManager_OnStreamVolumeChangeCallback callback);

/**
 * @brief 获取系统当前的铃声模式。
 *
 * @param volumeManager [in] 指向通过{@link OH_AudioManager_GetAudioVolumeManager}获取的音量管理器实例。
 * @param ringerMode [out] 用于接收返回的铃声模式。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数volumeManager或ringerMode为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_GetRingerMode(OH_AudioVolumeManager *volumeManager,
    OH_AudioRingerMode *ringerMode);

/**
 * @brief 注册铃声模式变化回调函数。
 * <br>多次注册时，系统会保存所有不同的回调函数，在铃声模式变化时遍历触发。
 * <br>若不再需要监听铃声模式变化，可调用{@link OH_AudioVolumeManager_UnregisterRingerModeChangeCallback}取消注册。
 *
 * @param volumeManager [in] 指向通过{@link OH_AudioManager_GetAudioVolumeManager}获取的音量管理器实例。
 * @param callback [in] 当监听到铃声模式发生变化时，将调用此回调函数。
 * @param userData [in] 用户自定义数据指针，回调函数触发时会携带。若无需传递数据，可传入空指针。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数volumeManager或callback为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioVolumeManager_RegisterRingerModeChangeCallback(
    OH_AudioVolumeManager *volumeManager,
    OH_AudioVolumeManager_OnRingerModeChangeCallback callback, void *userData);

/**
 * @brief 取消注册铃声模式变化回调函数。
 *
 * @param volumeManager [in] 指向通过{@link OH_AudioManager_GetAudioVolumeManager}获取的音量管理器实例。
 * @param callback [in] 需要取消注册的回调函数，该函数应与{@link OH_AudioVolumeManager_RegisterRingerModeChangeCallback}注册时的回调函数一致。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数volumeManager或callback为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统处理错误。</li>
 *         </ul>
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