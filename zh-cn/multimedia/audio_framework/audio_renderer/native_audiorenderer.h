/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
 * @addtogroup AudioRenderer
 * @{
 *
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 10
 */

/**
 * @file native_audiorenderer.h
 *
 * @brief Declare audio stream related interfaces for output type.
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 10
 */

#ifndef NATIVE_AUDIORENDERER_H
#define NATIVE_AUDIORENDERER_H

#include <stdbool.h>
#include <time.h>
#include "native_audiostream_base.h"
#include "native_audio_device_base.h"
#include "multimedia/native_audio_channel_layout.h"
#include "native_audio_session_base.h"
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 释放输出音频流。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_Release(OH_AudioRenderer* renderer);

/**
 * @brief 开始输出音频数据。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_Start(OH_AudioRenderer* renderer);

/**
 * @brief 暂停输出音频流。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_Pause(OH_AudioRenderer* renderer);

/**
 * @brief 停止输出音频流。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_Stop(OH_AudioRenderer* renderer);

/**
 * @brief 清空缓冲区的音频数据。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_Flush(OH_AudioRenderer* renderer);

/**
 * @brief 查询当前输出音频流状态。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param state 指向一个用来接收音频流状态的变量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_GetCurrentState(OH_AudioRenderer* renderer,
    OH_AudioStream_State* state);

/**
 * @brief 查询当前输出音频流采样率。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param rate 指向一个用来接收音频流采样率的变量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_GetSamplingRate(OH_AudioRenderer* renderer, int32_t* rate);

/**
 * @brief 查询当前输出音频流ID。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param streamId Pointer to a variable that will be set for the stream id.
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_GetStreamId(OH_AudioRenderer* renderer, uint32_t* streamId);

/**
 * @brief 查询当前输出音频流通道数。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param channelCount 指向一个用来接收音频流通道数的变量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_GetChannelCount(OH_AudioRenderer* renderer, int32_t* channelCount);

/**
 * @brief 查询当前输出音频流采样格式。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param sampleFormat 指向一个用来接收音频流采样格式的变量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_GetSampleFormat(OH_AudioRenderer* renderer,
    OH_AudioStream_SampleFormat* sampleFormat);

/**
 * @brief 查询当前输出音频流时延模式。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param latencyMode 指向一个用来接收音频流时延模式的变量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_GetLatencyMode(OH_AudioRenderer* renderer,
    OH_AudioStream_LatencyMode* latencyMode);
/**
 * @brief 查询当前输出音频流的使用类型。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param usage 指向一个用来接收输出类型音频流的使用类型的变量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_GetRendererInfo(OH_AudioRenderer* renderer,
    OH_AudioStream_Usage* usage);

/**
 * @brief 查询当前输出音频流编码类型。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param encodingType 指向一个用来接收音频流编码类型的变量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_GetEncodingType(OH_AudioRenderer* renderer,
    OH_AudioStream_EncodingType* encodingType);

/**
 * @brief 查询自创建流以来已写入的帧数。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param frames 指向用于接收已写入帧数的变量的指针。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_GetFramesWritten(OH_AudioRenderer* renderer, int64_t* frames);

/**
 * @brief Query the time at which a particular frame was presented.
 *
 * It is recommended to use new api {@link OH_AudioRenderer_GetAudioTimestampInfo}
 * because it adapts to playback speed change, but current api does not. The
 * increasing speed for position will not change when speed become fast.
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param clockId 时钟标识符，使用CLOCK_MONOTONIC。
 * @param framePosition 指向要接收位置的变量的指针。
 * @param timestamp 指向接收时间戳的变量的指针，单位为纳秒。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of renderer is nullptr;
 *                                                 2.The param of clockId invalid.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_GetTimestamp(OH_AudioRenderer* renderer,
    clockid_t clockId, int64_t* framePosition, int64_t* timestamp);

/**
 * @brief 在回调中查询帧大小，它是一个固定的长度，每次回调都要填充流。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param frameSize 指向用于接收帧大小的变量的指针。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioRenderer_GetFrameSizeInCallback(OH_AudioRenderer* renderer, int32_t* frameSize);

/**
 * @brief 获取音频渲染速率。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param speed 指向接收播放倍速值的变量的指针。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 11
 */
OH_AudioStream_Result OH_AudioRenderer_GetSpeed(OH_AudioRenderer* renderer, float* speed);

/**
 * @brief 设置音频渲染速率。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param speed 设置播放的倍速值（倍速范围：[0.25, 4.0]）。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 11
 */
OH_AudioStream_Result OH_AudioRenderer_SetSpeed(OH_AudioRenderer* renderer, float speed);

/**
 * @brief Set volume of current renderer.
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param volume 设置当前音频流音量，音量值范围[0.0, 1.0]。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of renderer is nullptr;
 *                                                 2.The param of volume invalid.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_SYSTEM} An system error has occurred.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_SetVolume(OH_AudioRenderer* renderer, float volume);

/**
 * @brief Changes the volume with ramp for a duration.
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param volume 目标音量值，取值范围[0.0, 1.0]。
 * @param durationMs 音量渐变的持续时间，以毫秒为单位。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of renderer is nullptr;
 *                                                 2.The param of volume invalid.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_SYSTEM} An system error has occurred.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_SetVolumeWithRamp(OH_AudioRenderer* renderer, float volume, int32_t durationMs);

/**
 * @brief Get the volume of current renderer.
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param volume 指向一个用来接收当前音频流音量值的指针。音量值的范围是[0.0, 1.0]。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of renderer is nullptr;
 *                                                 2.The param of volume is nullptr.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_GetVolume(OH_AudioRenderer* renderer, float* volume);

/**
 * @brief 在当前渲染器上设置标记位置。调用此函数将覆盖已设置的标记位置。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param samplePos 设置目标标记位置。
 * @param callback 当到达目标标记位置时回调。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of renderer is nullptr;
 *                                                 2.The param of samplePos invalid.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_SYSTEM} An system error has occurred.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_SetMarkPosition(OH_AudioRenderer* renderer, uint32_t samplePos,
    OH_AudioRenderer_OnMarkReachedCallback callback, void* userData);

/**
 * @brief 取消由{@link OH_AudioRenderer_SetMarkPosition}设置的标记。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_CancelMark(OH_AudioRenderer* renderer);

/**
 * @brief 获取当前播放音频流欠载数。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param count 指向一个用来接收音频流欠载数的变量的指针。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of renderer is nullptr;
 *                                                 2.The param of count is nullptr.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_GetUnderflowCount(OH_AudioRenderer* renderer, uint32_t* count);

/**
 * @brief 查询当前音频流声道布局。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param channelLayout 指向一个用来接收音频流声道布局的变量的指针。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_GetChannelLayout(OH_AudioRenderer* renderer,
    OH_AudioChannelLayout* channelLayout);

/**
 * @brief 查询当前音频流音效模式。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param effectMode 指向一个用来接收音频流音效模式的变量的指针。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_GetEffectMode(OH_AudioRenderer* renderer,
    OH_AudioStream_AudioEffectMode* effectMode);

/**
 * @brief 设置当前音频流音效模式。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param effectMode 设置当前音频流的目标音效模式。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_SetEffectMode(OH_AudioRenderer* renderer,
    OH_AudioStream_AudioEffectMode effectMode);

/**
 * @brief 查询当前播放音频流是否会被其它应用录制。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param privacy 用于返回当前流的内录策略。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of renderer is nullptr.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_GetRendererPrivacy(OH_AudioRenderer* renderer,
    OH_AudioStream_PrivacyType* privacy);
/**
 * @brief 设置静音并发播放模式。
 * <br>当设置为true，打开静音并发播放模式，系统将让此音频流静音播放，并且不会打断其他音频流。设置为false，将关闭静音并发播放，音频流可根据系统焦点策略抢占焦点。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param on 设置当前音频流的静音并发状态。
 *     <br>true：设置当前播放的音频流静音播放，并且不会打断其它音频流播放。
 *     <br>false：取消当前播放的音频流静音播放，音频流可根据系统焦点策略抢占焦点。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数renderer为nullptr。
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_SetSilentModeAndMixWithOthers(
    OH_AudioRenderer* renderer, bool on);
/**
 * @brief 获取当前音频流是否开启静音并发播放。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param on 用于返回当前流的静音并发状态。返回true表示打开，返回false表示关闭。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数renderer为nullptr。
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_GetSilentModeAndMixWithOthers(
    OH_AudioRenderer* renderer, bool* on);
/**
 * @brief 设置默认本机内置发声设备。
 * <br>本接口仅适用于音频流类型{@link OH_AudioStream_Usage}为语音消息、VoIP语音通话或者VoIP视频通话的场景使用，以及可选的设备类型为听筒、扬声器和系统默认设备。
 * <br>本接口允许在AudioRenderer创建以后的任何时间被调用，系统会记录应用设置的默认本机内置发声设备。在应用启动播放时，若有外接设备如蓝牙耳机/有线耳机接入，系统优先从外接设备发声；
 * 否则系统遵循应用设置的默认本机内置发声设备发声。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param deviceType 指向{@link OH_AudioDevice_Type}用于设置发声设备类型。可设置的设备类型包括:
 *     <br>AUDIO_DEVICE_TYPE_EARPIECE：听筒
 *     <br>AUDIO_DEVICE_TYPE_SPEAKER：扬声器
 *     <br>AUDIO_DEVICE_TYPE_DEFAULT：系统默认设备
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：
 *     <br>1. 参数renderer为nullptr;
 *     <br>2. 参数deviceType无效。
 *     <br>AUDIOSTREAM_ERROR_ILLEGAL_STATE：执行状态异常。
 *     <br>AUDIOSTREAM_ERROR_SYSTEM：出现系统错误。
 * @since 12
 */
OH_AudioStream_Result OH_AudioRenderer_SetDefaultOutputDevice(
    OH_AudioRenderer* renderer, OH_AudioDevice_Type deviceType);
/**
 * @brief 获取输出音频流时间戳和位置信息，适配倍速接口。
 * <br>获取输出音频流时间戳和位置信息，通常用于进行音画同步对齐，播放位置单位为采样数（samples），时间戳单位为纳秒（nanosecond，ns）。
 * <br>当设备切换或暂停恢复时，由于播放通路本身需要一段时间恢复，调用该接口获取的播放位置和时间戳会短暂地保持在切换或暂停前的状态。
 * <br>该接口通常用来实现音画同步，调用频率建议高于200ms一次，推荐频率为每分钟一次。在能保证音画同步效果的情况下，不需要频繁地查询时间戳，避免出现功耗问题。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param framePosition 指向要接收位置的变量的指针。
 * @param timestamp 指向接收时间戳的变量的指针，单位为纳秒。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：
 *     <br>1. 参数renderer为nullptr；
 *     <br>2. 参数framePosition或timestamp为nullptr。
 *     <br>AUDIOSTREAM_ERROR_ILLEGAL_STATE：当前流状态不为合法状态时返回。
 *     <br>AUDIOSTREAM_ERROR_SYSTEM：
 *     <br>1. 系统进程崩溃或被阻塞；
 *     <br>2. 内部系统其他错误。
 * @since 15
 */
OH_AudioStream_Result OH_AudioRenderer_GetAudioTimestampInfo(OH_AudioRenderer* renderer,
    int64_t* framePosition, int64_t* timestamp);

/**
 * @brief 音频流中断事件回调函数。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param userData 指向应用自定义的数据存储区域。
 * @param type 音频流中断类型。
 * @param hint 音频流中断提示类型。
 * @see OH_AudioRenderer_Callbacks_Struct.OH_AudioRenderer_OnInterruptEvent.
 * @since 20
 */
typedef void (*OH_AudioRenderer_OnInterruptCallback)(OH_AudioRenderer* renderer, void* userData,
    OH_AudioInterrupt_ForceType type, OH_AudioInterrupt_Hint hint);

/**
 * @brief 音频流错误事件回调函数。系统内部故障时触发，如音频服务异常退出，非应用调用导致。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param userData 指向应用自定义的数据存储区域。
 * @param error 音频流播放错误结果。
 * @see OH_AudioRenderer_Callbacks_Struct.OH_AudioRenderer_OnError
 * @since 20
 */
typedef void (*OH_AudioRenderer_OnErrorCallback)(OH_AudioRenderer* renderer, void* userData,
    OH_AudioStream_Result error);
/**
 * @brief 获取音频播放过程中的运行状态，是否在低时延状态下工作。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param status 指向接收低时延状态的指针。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数renderer为nullptr。
 *     <br>AUDIOSTREAM_ERROR_ILLEGAL_STATE：执行状态异常，仅在释放状态之前可用。
 * @since 20
 */
OH_AudioStream_Result OH_AudioRenderer_GetFastStatus(OH_AudioRenderer* renderer,
    OH_AudioStream_FastStatus* status);

/**
 * @brief 音频播放过程中低时延状态改变事件的回调函数。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param userData 指向应用自定义的数据存储区域。
 * @param status 表示当前低时延状态。
 * @since 20
 */
typedef void (*OH_AudioRenderer_OnFastStatusChange)(
    OH_AudioRenderer* renderer,
    void* userData,
    OH_AudioStream_FastStatus status
);

/**
 * @brief 设置音频播放的响度值。默认的响度值是0.0dB。音频流播放类型必须是音乐{@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_MUSIC，
 * <br>电影或视频{@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_MOVIE，
 * <br>有声读物（包括听书、相声、评书）、听新闻、播客等{@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_AUDIOBOOK。
 * <br>音频流的时延模式必须是普通时延{@link OH_AudioStream_LatencyMode}.AUDIOSTREAM_LATENCY_MODE_NORMAL。
 * <br>本接口不支持通过高清通路播放的音频流设置响度。
 * <br>由于音频框架与硬件之间存在缓冲区，响度调节实际生效存在延迟，时长取决于缓冲区长度。
 * <br>建议在不同音频开始播放前预先设置响度，以实现最佳均衡效果。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param loudnessGain 设置播放的响度值（响度值范围为[-90.0, 24.0]，单位为dB）。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：
 *     <br>1. 参数renderer为nullptr，或音频流不支持设置响度；
 *     <br>2. 参数loudnessGain不在响度值范围内。
 * @since 20
 */
OH_AudioStream_Result OH_AudioRenderer_SetLoudnessGain(OH_AudioRenderer* renderer, float loudnessGain);
/**
 * @brief 获取音频流的响度值。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param loudnessGain 指向接收播放响度值的变量的指针，单位为分贝。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：
 *     <br>1. 参数renderer为nullptr；
 *     <br>2. 参数loudnessGain为nullptr。
 * @since 20
 */
OH_AudioStream_Result OH_AudioRenderer_GetLoudnessGain(OH_AudioRenderer* renderer, float* loudnessGain);

/**
 * @brief 该函数指针将指向用于写入音频数据的回调函数。不同于OH_AudioRenderer_OnWriteDataCallback，此函数允许应用填充[0, audioDataSize]长度的数据。
 * <br>其中audioDataSize为回调buffer的长度。调用方通过返回值告知系统写入的数据长度。
 * <br>如果返回0，回调线程将会sleep一段时间。
 * <br>否则，系统可能会立刻进行下一次回调。
 *
 * @param renderer 指向发生回调的实例。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @param audioData 指向让应用填充音频数据的指针。
 * @param audioDataSize 应用应写入音频数据的数据长度，以字节为单位。
 * @return 应用实际填充有效音频数据的长度。返回值必须在[0, audioDataSize]范围内。
 *     <br>如果返回值小于0，系统将调整为0。 并且，如果返回值大于audioDataSize，系统将其调整到audioDataSize。
 *     <br>注意返回值必须是单个采样点大小的整数倍。
 *     <br>比如，双声道S16格式的音频数据，必须是4(2 * 16 / 8)的整数倍。
 *     <br>否则，可能造成播放杂音。
 * @see OH_AudioRenderer_OnWriteDataCallback
 * @since 20
 */
typedef int32_t (*OH_AudioRenderer_OnWriteDataCallbackAdvanced)(OH_AudioRenderer* renderer, void* userData,
    void* audioData, int32_t audioDataSize);
/**
 * @brief 获取当前音频路由的估算时延（单位：毫秒）。无线连接的音频设备，时延估算可能存在误差，结果仅供参考。
 * <br>由于时延未计入实时缓冲区，建议仅在音频播放开始时获取，避免频繁调用，否则可能因路由切换而阻塞该接口调用。
 * <br>当音频数据输出到硬件后，建议使用{@link OH_AudioRenderer_GetAudioTimestampInfo}进行音视频同步。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param type 要获取的时延类型。
 * @param latencyMs 指向用于接收时延（毫秒）变量的指针。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：
 *     <br>1. 参数renderer为nullptr；
 *     <br>2. 参数latencyMs为nullptr；
 *     <br>3. 参数type无效。
 *     <br>AUDIOSTREAM_ERROR_SYSTEM：系统内部错误，例如音频服务异常。
 * @since 23
 */
OH_AudioStream_Result OH_AudioRenderer_GetLatency(OH_AudioRenderer* renderer,
    OH_AudioStream_LatencyType type, int32_t* latencyMs);
/**
 * @brief 设置独立的音频会话策略和行为参数。当音频渲染器在运行状态时调用此接口后，必须重新调用接口{@link OH_AudioRenderer_Start}使其生效。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param strategy 用于设置独立的音频会话策略。
 * @param behavior 音频会话行为标志，可以是单个标志，也可以是多个标志的按位OR组合。当前支持的音频会话行为详见{@link OH_AudioSession_BehaviorFlags}。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数为空指针或超出范围。
 *     <br>AUDIOSTREAM_ERROR_ILLEGAL_STATE：执行状态异常。
 * @since 24
 */
OH_AudioStream_Result OH_AudioRenderer_SetIndependentAudioSessionStrategy(
    OH_AudioRenderer* renderer, const OH_AudioSession_Strategy *strategy, uint32_t behavior);

#ifdef __cplusplus
}
#endif
#endif // NATIVE_AUDIORENDERER_H
/** @} */