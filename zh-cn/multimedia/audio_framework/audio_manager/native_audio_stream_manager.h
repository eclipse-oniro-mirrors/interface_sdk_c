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
 * @since 19
 */

/**
 * @file native_audio_stream_manager.h
 *
 * @brief 声明音频流管理器相关的接口。
 * <br>该文件接口用于创建AudioStreamManager以及音频流设置和管理。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 19
 */

#ifndef NATIVE_AUDIO_STREAM_MANAGER_H
#define NATIVE_AUDIO_STREAM_MANAGER_H

#include <stdbool.h>
#include "native_audio_common.h"
#include "native_audiostream_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 声明音频流管理器，用于管理音频流相关功能。
 *
 * @since 19
 */
typedef struct OH_AudioStreamManager OH_AudioStreamManager;

/**
 * @brief 获取音频流管理器句柄。
 *
 * @param streamManager 音频流管理器句柄。
 * @return
 *     {@link #AUDIOCOMMON_RESULT_SUCCESS} if execution succeeds
 *     {@link #AUDIOCOMMON_RESULT_ERROR_SYSTEM} if system state error
 * @since 19
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioStreamManager(OH_AudioStreamManager **streamManager);

/**
 * @brief 获取当前音频流支持的direct通路播放模式。
 *
 * @param audioStreamManager 音频流管理器句柄。通过 {@link OH_AudioManager_GetAudioStreamManager}获取句柄。
 * @param streamInfo 音频流信息指针。
 * @param usage 音频流使用场景。
 * @param directPlaybackMode 指向 {@link OH_AudioStream_DirectPlaybackMode}，用于获取当前音频流支持的direct通路播放模式。
 * @return AUDIOCOMMON_RESULT_SUCCESS = 0：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM = 6800101：
 *     <br>1. 参数audioStreamManager为nullptr；
 *     <br>2. 参数streamInfo为nullptr；
 *     <br>3. 参数usage无效；
 *     <br>4. 参数directPlaybackMode为nullptr。
 * @since 19
 */
OH_AudioCommon_Result OH_AudioStreamManager_GetDirectPlaybackSupport(
    OH_AudioStreamManager *audioStreamManager, OH_AudioStreamInfo *streamInfo,
    OH_AudioStream_Usage usage, OH_AudioStream_DirectPlaybackMode *directPlaybackMode);
/**
 * @brief 查询指定的录音流类型使用场景是否支持回声消除。
 *
 * @param streamManager 音频流管理器句柄。通过 {@link OH_AudioManager_GetAudioStreamManager}获取句柄。
 * @param sourceType 指定音频输入流的使用场景。
 * @param supported 查询指定的source type是否支持回声消除的结果。true表示支持回声消除，false表示不支持回声消除。
 * @return AUDIOCOMMON_RESULT_SUCCESS = 0 ：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM = 6800101 ：
 *     <br>1.参数audioStreamManager为nullptr；
 *     <br>2.参数sourceType无效；
 *     <br>3.参数supported为nullptr。
 * @since 20
 */
OH_AudioCommon_Result OH_AudioStreamManager_IsAcousticEchoCancelerSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStream_SourceType sourceType, bool *supported);

/**
 * @brief 查询当前设备在特定音频流信息和使用场景下是否支持低时延播放。
 *
 * @param streamManager 音频流管理器句柄。通过{@link OH_AudioManager_GetAudioStreamManager}获取句柄。
 * @param streamInfo 音频流信息指针。
 * @param usage 音频流使用场景。
 * @return 返回true时表示支持低时延播放，返回false时表示不支持。
 * @since 20
 */
bool OH_AudioStreamManager_IsFastPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage);

/**
 * @brief 查询当前设备在特定音频流信息和使用场景下是否支持低时延录制。
 *
 * @param streamManager 音频流管理器句柄。通过{@link OH_AudioManager_GetAudioStreamManager}获取句柄。
 * @param streamInfo 音频流信息指针。
 * @param source 音频流使用场景。
 * @return 返回true时表示支持低时延录制，返回false时表示不支持。
 * @since 20
 */
bool OH_AudioStreamManager_IsFastRecordingSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_SourceType source);

/**
 * @brief 查询指定录音流类型的智能降噪开关是否已开启。
 *
 * @param streamManager 音频流管理器句柄。通过{@link OH_AudioManager_GetAudioStreamManager}获取句柄。
 * @param source 根据音频设备和管道类型选择结果得出的音频流使用场景。
 * @return 返回true时表示智能降噪开关已打开，返回false时表示开关已关闭。
 * @since 21
 */
bool OH_AudioStreamManager_IsIntelligentNoiseReductionEnabledForCurrentDevice(
    OH_AudioStreamManager *streamManager, OH_AudioStream_SourceType source);

/**
 * @brief 查询当前设备在特定音频流信息和使用场景下是否支持多声道播放。
 *
 * @param streamManager 音频流管理器句柄。通过{@link OH_AudioManager_GetAudioStreamManager}获取句柄。
 * @param streamInfo 音频流信息指针，用于描述基础音频格式。
 * @param usage 音频流使用场景，用于决定音频设备和通路类型的选择结果。
 * @return 返回true时表示支持多声道播放，返回false时表示不支持。
 * @since 26.0.0
 */
bool OH_AudioStreamManager_IsMultichannelPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage);

/**
 * @brief 查询当前设备在特定音频流信息和使用场景下是否支持直通播放。
 *
 * @param streamManager 音频流管理器句柄。通过{@link OH_AudioManager_GetAudioStreamManager}获取句柄。
 * @param streamInfo 音频流信息指针，用于描述基础音频格式。
 * @param usage 音频流使用场景，用于决定音频设备和通路类型的选择结果。
 * @return 返回true时表示支持直通播放，返回false时表示不支持。
 * @since 26.0.0
 */
bool OH_AudioStreamManager_IsDirectPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage);

/**
 * @brief 查询当前设备在特定音频流信息和使用场景下是否支持低功耗播放。
 *
 * @param streamManager 音频流管理器句柄。通过{@link OH_AudioManager_GetAudioStreamManager}获取句柄。
 * @param streamInfo 音频流信息指针，用于描述基础音频格式。
 * @param usage 音频流使用场景，用于决定音频设备和通路类型的选择结果。
 * @return 返回true时表示支持低功耗播放，返回false时表示不支持。
 * @since 26.0.0
 */
bool OH_AudioStreamManager_IsOffloadPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_STREAM_MANAGER_H
/** @} */