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
 * @brief 本文件提供音频流管理功能的接口。
 * <br>音频流是对系统内音频播放和录制流的统称。音频系统会根据音频流的配置，如播放流的{@link OH_AudioStream_Usage}和录制流的{@link OH_AudioStream_SourceType}，
 * 为音频流选择合适的音频通路，以达到最佳的音频体验。
 * <br>在不同设备上，通路支持的情况存在差异，本模块提供了能力查询接口，开发者可传入待播放或录制音频流的基础属性和用途进行查询。
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
 * @brief 声明音频流管理结构体，该结构体用于调用系统音频流能力查询功能接口。
 *
 * @since 19
 */
typedef struct OH_AudioStreamManager OH_AudioStreamManager;

/**
 * @brief 获取音频流管理器实例，该实例为单例，用于调用音频流能力查询接口。
 *
 * @param streamManager [out] 用于接收获取的音频流管理器实例。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 系统状态错误。</li>
 *         </ul>
 * @since 19
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioStreamManager(OH_AudioStreamManager **streamManager);

/**
 * @brief 查询当前设备在特定的音频基础格式信息和使用场景下支持的直通通路播放模式。
 *
 * @param audioStreamManager [in] 通过 {@link OH_AudioManager_GetAudioStreamManager}获取的音频流管理器实例。
 * @param streamInfo [in] 音频播放流基础格式信息指针。
 * @param usage [in] 音频播放流使用场景。
 * @param directPlaybackMode [out] 用于获取支持的直通通路播放模式。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} <br>1. 参数audioStreamManager为空指针；<br>2. 参数streamInfo为空指针；<br>3. 参数usage无效；<br>4. 参数directPlaybackMode为空指针。</li>
 *         </ul>
 * @since 19
 */
OH_AudioCommon_Result OH_AudioStreamManager_GetDirectPlaybackSupport(
    OH_AudioStreamManager *audioStreamManager, OH_AudioStreamInfo *streamInfo,
    OH_AudioStream_Usage usage, OH_AudioStream_DirectPlaybackMode *directPlaybackMode);

/**
 * @brief 查询当前设备在特定的音频录制流使用场景下是否支持回声消除。
 *
 * @param streamManager [in] 通过 {@link OH_AudioManager_GetAudioStreamManager}获取的音频流管理器实例。
 * @param sourceType [in] 音频录制流使用场景。
 * @param supported [out] 用于获取是否支持回声消除的结果。true表示支持，false表示不支持。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} <br>1.参数streamManager为空指针；<br>2.参数sourceType无效；<br>3.参数supported为空指针。</li>
 *         </ul>
 * @since 20
 */
OH_AudioCommon_Result OH_AudioStreamManager_IsAcousticEchoCancelerSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStream_SourceType sourceType, bool *supported);

/**
 * @brief 查询当前设备在特定音频播放流信息和使用场景下是否支持低时延播放。
 *
 * @param streamManager [in] 通过 {@link OH_AudioManager_GetAudioStreamManager}获取的音频流管理器实例。
 * @param streamInfo [in] 音频播放流基础格式信息指针。
 * @param usage [in] 音频播放流使用场景。
 * @return 返回true时表示支持低时延播放，返回false时表示不支持。当输入参数为空指针或无效值时，也会返回false。
 * @since 20
 */
bool OH_AudioStreamManager_IsFastPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage);

/**
 * @brief 查询当前设备在特定音频录制流信息和使用场景下是否支持低时延录制。
 *
 * @param streamManager [in] 通过 {@link OH_AudioManager_GetAudioStreamManager}获取的音频流管理器实例。
 * @param streamInfo [in] 音频录制流基础格式信息指针。
 * @param source [in] 音频录制流使用场景。
 * @return 返回true时表示支持低时延录制，返回false时表示不支持。当输入参数为空指针或无效值时，也会返回false。
 * @since 20
 */
bool OH_AudioStreamManager_IsFastRecordingSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_SourceType source);

/**
 * @brief 查询在当前音频设备连接状态下，特定使用场景录音流的智能降噪开关是否已开启。
 *
 * @param streamManager [in] 通过 {@link OH_AudioManager_GetAudioStreamManager}获取的音频流管理器实例。
 * @param source [in] 音频录制流使用场景。
 * @return 返回true时表示智能降噪开关已打开，返回false时表示开关已关闭。当输入参数为空指针或无效值时，也会返回false。
 * @since 21
 */
bool OH_AudioStreamManager_IsIntelligentNoiseReductionEnabledForCurrentDevice(
    OH_AudioStreamManager *streamManager, OH_AudioStream_SourceType source);

/**
 * @brief 查询当前设备在特定音频播放流信息和使用场景下是否支持多声道播放。
 *
 * @param streamManager [in] 通过 {@link OH_AudioManager_GetAudioStreamManager}获取的音频流管理器实例。
 * @param streamInfo [in] 音频播放流基础格式信息指针。
 * @param usage [in] 音频播放流使用场景。
 * @return 返回true时表示支持多声道播放，返回false时表示不支持。当输入参数为空指针或无效值时，也会返回false。
 * @since 26.0.0
 */
bool OH_AudioStreamManager_IsMultichannelPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage);

/**
 * @brief 查询当前设备在特定音频播放流信息和使用场景下是否支持直通播放。
 *
 * @param streamManager [in] 通过 {@link OH_AudioManager_GetAudioStreamManager}获取的音频流管理器实例。
 * @param streamInfo [in] 音频播放流基础格式信息指针。
 * @param usage [in] 音频播放流使用场景。
 * @return 返回true时表示支持直通播放，返回false时表示不支持。当输入参数为空指针或无效值时，也会返回false。
 * @since 26.0.0
 */
bool OH_AudioStreamManager_IsDirectPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage);

/**
 * @brief 查询当前设备在特定音频播放流信息和使用场景下是否支持低功耗播放。
 *
 * @param streamManager [in] 通过 {@link OH_AudioManager_GetAudioStreamManager}获取的音频流管理器实例。
 * @param streamInfo [in] 音频播放流基础格式信息指针。
 * @param usage [in] 音频播放流使用场景。
 * @return 返回true时表示支持低功耗播放，返回false时表示不支持。当输入参数为空指针或无效值时，也会返回false。
 * @since 26.0.0
 */
bool OH_AudioStreamManager_IsOffloadPlaybackSupported(
    OH_AudioStreamManager *streamManager, OH_AudioStreamInfo *streamInfo, OH_AudioStream_Usage usage);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_ROUTING_MANAGER_H
/** @} */