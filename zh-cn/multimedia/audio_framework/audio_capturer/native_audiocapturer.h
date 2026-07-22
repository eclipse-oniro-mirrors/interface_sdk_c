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
 * @addtogroup AudioCapturer
 * @{
 *
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 10
 */

/**
 * @file native_audiocapturer.h
 *
 * @brief Declare audio stream related interfaces for input type.
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 10
 */

#ifndef NATIVE_AUDIOCAPTURER_H
#define NATIVE_AUDIOCAPTURER_H

#include <stdbool.h>
#include <time.h>
#include "native_audiostream_base.h"
#include "native_audio_device_base.h"
#include "native_audio_session_base.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 释放输入音频流。
 *
 * @permission ohos.permission.MICROPHONE
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 *  @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_Release(OH_AudioCapturer* capturer);
/**
 * @brief 启动音频采集器，开始获取音频数据。
 *
 * @permission ohos.permission.MICROPHONE
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_Start(OH_AudioCapturer* capturer);
/**
 * @brief 暂停输入音频流。在暂停音频后，后续需要恢复录音的场景，建议使用pause。
 *
 * @permission ohos.permission.MICROPHONE
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_Pause(OH_AudioCapturer* capturer);
/**
 * @brief 停止音频采集器，停止输入音频流后，如果需要彻底结束录音，建议使用stop。
 *
 * @permission ohos.permission.MICROPHONE
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_Stop(OH_AudioCapturer* capturer);

/**
 * @brief 丢弃获取的音频数据。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_Flush(OH_AudioCapturer* capturer);
/**
 * @brief 查询当前音频流状态。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param state 指向一个用来接收音频流状态的变量。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数capturer为nullptr。
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetCurrentState(OH_AudioCapturer* capturer, OH_AudioStream_State* state);

/**
 * @brief Query the latency mode of the capturer client.
 *
 * @param capturer Reference created by OH_AudioStreamBuilder_GenerateCapturer()
 * @param latencyMode Pointer to a variable that will be set for the latency mode.
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetLatencyMode(OH_AudioCapturer* capturer,
    OH_AudioStream_LatencyMode* latencyMode);

/**
 * @brief Query the stream id of the capturer client.
 *
 * @param capturer Reference created by OH_AudioStreamBuilder_GenerateCapturer()
 * @param streamId Pointer to a variable that will be set for the stream id.
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetStreamId(OH_AudioCapturer* capturer, uint32_t* streamId);

/**
 * @brief Query the sample rate value of the capturer client.
 *
 * This function will return the capturer sample rate value without updating the state.
 *
 * @param capturer Reference created by OH_AudioStreamBuilder_GenerateCapturer()
 * @param rate Pointer to a variable that will be set for the sampling rate.
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetSamplingRate(OH_AudioCapturer* capturer, int32_t* rate);

/**
 * @brief Query the channel count of the capturer client.
 *
 * @param capturer Reference created by OH_AudioStreamBuilder_GenerateCapturer()
 * @param channelCount Pointer to a variable that will be set for the channel count.
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetChannelCount(OH_AudioCapturer* capturer, int32_t* channelCount);

/**
 * @brief 查询当前输入音频流采样格式。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param sampleFormat 指向一个用来接收音频流采样格式的变量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetSampleFormat(OH_AudioCapturer* capturer,
    OH_AudioStream_SampleFormat* sampleFormat);

/**
 * @brief 查询当前音频流编码类型。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param encodingType 指向一个用来接收音频流编码类型的变量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetEncodingType(OH_AudioCapturer* capturer,
    OH_AudioStream_EncodingType* encodingType);

/**
 * @brief 查询当前音频流工作场景类型。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param sourceType 指向一个用来接收输入类型音频流的工作场景的变量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetCapturerInfo(OH_AudioCapturer* capturer,
    OH_AudioStream_SourceType* sourceType);

/**
 * @brief 查询回调帧数。frameSize表示每次回调对应的采样帧数。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param frameSize 指向将为采样帧数设置的变量的指针。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetFrameSizeInCallback(OH_AudioCapturer* capturer, int32_t* frameSize);

/**
 * @brief 获取输入音频流时间戳和当前数据帧位置信息。
 * <br>该接口可以获取到音频通道实际录制位置（framePosition）以及录制到该位置时的时间戳（timestamp），时间戳单位为纳秒。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param clockId 时钟标识符，使用CLOCK_MONOTONIC。
 * @param framePosition 指向要接收位置的变量的指针。
 * @param timestamp 指向接收时间戳的变量的指针，单位为纳秒。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}:
 *                                                 1.The param of capturer is nullptr;
 *                                                 2.The param of clockId invalid.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} Execution status exception.</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetTimestamp(OH_AudioCapturer* capturer,
    clockid_t clockId, int64_t* framePosition, int64_t* timestamp);

/**
 * @brief 查询自创建流以来已读取的帧数。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param frames 指向将为帧计数设置的变量的指针。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数capturer为nullptr。
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetFramesRead(OH_AudioCapturer* capturer, int64_t* frames);

/**
 * @brief Gets the overflow count on this stream.
 *
 * @param capturer Capturer generated by OH_AudioStreamBuilder_GenerateCapturer()
 * @param count Pointer to a variable that will be set for the overflow count number.
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} If the execution is successful.</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} The param of capturer is nullptr.</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioCapturer_GetOverflowCount(OH_AudioCapturer* capturer, uint32_t* count);

/**
 * @brief 读取音频数据的回调函数。为了消除麦克风硬件设计带来的上电杂音，通常会对录音启动后的前100ms数据进行静音。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param userData 指向应用自定义的数据存储区域，方便应用给自身传递数据。
 * @param audioData 指向录制数据存储区域，用于应用读取录制数据。
 * @param audioDataSize 录制数据的长度，单位为字节。
 * @see OH_AudioCapturer_Callbacks_Struct.OH_AudioCapturer_OnReadData
 * @since 20
 */
typedef void (*OH_AudioCapturer_OnReadDataCallback)(OH_AudioCapturer* capturer, void* userData, void* audioData,
    int32_t audioDataSize);

/**
 * @brief 音频录制流的设备变化事件回调函数。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param userData 指向应用自定义的数据存储区域。
 * @param deviceArray 音频设备描述符数组。
 * @see OH_AudioCapturer_Callbacks_Struct.OH_AudioCapturer_OnStreamEvent
 * @since 20
 */
typedef void (*OH_AudioCapturer_OnDeviceChangeCallback)(OH_AudioCapturer* capturer, void* userData,
    OH_AudioDeviceDescriptorArray* deviceArray);

/**
 * @brief 音频录制流的中断事件回调函数。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param userData 指向应用自定义的数据存储区域。
 * @param type 音频流中断类型。
 * @param hint 音频流中断提示类型。
 * @see OH_AudioCapturer_Callbacks_Struct.OH_AudioCapturer_OnInterruptEvent.
 * @since 20
 */
typedef void (*OH_AudioCapturer_OnInterruptCallback)(OH_AudioCapturer* capturer, void* userData,
    OH_AudioInterrupt_ForceType type, OH_AudioInterrupt_Hint hint);

/**
 * @brief 音频录制流的错误事件回调函数。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param userData 指向应用自定义的数据存储区域。
 * @param error 音频流录制错误结果。
 * @see OH_AudioCapturer_Callbacks_Struct.OH_AudioCapturer_OnError
 * @since 20
 */
typedef void (*OH_AudioCapturer_OnErrorCallback)(OH_AudioCapturer* capturer, void* userData,
    OH_AudioStream_Result error);
/**
 * @brief 获取音频录制过程中的运行状态，是否在低时延状态下工作。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param status 指向接收低时延状态的指针。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数capturer为nullptr。
 *     <br>AUDIOSTREAM_ERROR_ILLEGAL_STATE：执行状态异常，仅在释放状态之前可用。
 * @since 20
 */
OH_AudioStream_Result OH_AudioCapturer_GetFastStatus(OH_AudioCapturer* capturer,
    OH_AudioStream_FastStatus* status);

/**
 * @brief 音频录制过程中低时延状态改变事件的回调函数。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param userData 指向应用自定义的数据存储区域。
 * @param status 返回当前低时延状态。
 * @since 20
 */
typedef void (*OH_AudioCapturer_OnFastStatusChange)(
    OH_AudioCapturer* capturer,
    void* userData,
    OH_AudioStream_FastStatus status
);

/**
 * @brief 音频录制过程中用于内录（录制的是设备内部应用的声音）启动结果的回调函数。该API暂不对外支持。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param userData 通过{@link OH_AudioCapturer_RequestPlaybackCaptureStart}指向应用自定义的数据存储区域。
 * @param state 表示内录请求是否成功的状态。
 * @since 23
 */
typedef void (*OH_AudioCapturer_OnPlaybackCaptureStartCallback)(
    OH_AudioCapturer* capturer,
    void* userData,
    OH_AudioStream_PlaybackCaptureStartState state);
/**
 * 异步请求启动内录流。
 * 该函数是非阻塞的，意味着系统在接收到启动请求后，将继续处理用户授权和内录流的启动。最终结果将通过回调函数返回。
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param callback 用于接收启动请求最终结果的回调函数。
 * @param userData 指向应用自定义的数据存储区域, 该结构将传递给回调函数。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：capturer或callback是无效的。
 *     <br>AUDIOSTREAM_ERROR_ILLEGAL_STATE：如果流已经在运行中或者已释放则是非法状态。
 *     <br>AUDIOSTREAM_ERROR_SYSTEM：系统内部错误，比如音频服务错误。
 * @since 23
 */
OH_AudioStream_Result OH_AudioCapturer_RequestPlaybackCaptureStart(OH_AudioCapturer* capturer,
    OH_AudioCapturer_OnPlaybackCaptureStartCallback callback, void* userData);
/**
 * @brief 应用将当前录音流的自身静音状态传递给系统音频模块。
 * 该接口用于向系统音频模块上报应用自身的静音状态，不会改变录音流的实际静音状态。
 * 当前仅在部分PC/2in1设备上，系统音频模块会基于设置的状态调整策略以降低功耗。
 * 该接口仅在录音流处于运行态时允许调用，否则返回错误AUDIOSTREAM_ERROR_ILLEGAL_STATE。
 * 同一录音流同时设置流级静音提示接口（本接口）和会话级静音提示接口时，流级（本接口）优先级更高，
 * 数值以流级（本接口）设置值为准。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param mute 应用向系统音频模块上报的自身静音状态，作用于第一个参数`capturer`指定的录制流实例。
 *     true表示上报该录制流为静音状态，false表示上报该录制流为非静音状态。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数capturer为nullptr。
 *     <br>AUDIOSTREAM_ERROR_ILLEGAL_STATE：操作状态异常，录音流未处于running状态。
 *     <br>AUDIOSTREAM_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 24
 */
OH_AudioStream_Result OH_AudioCapturer_SetMuteHint(OH_AudioCapturer* capturer, bool mute);
/**
 * @brief 设置独立的音频会话策略和行为参数。当音频采集器在运行状态时调用此接口后，
 * 必须重新调用接口{@link OH_AudioCapturer_Start}使其生效。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param strategy 用于设置独立的音频会话策略。
 * @param behavior 音频会话行为标志，可以是单个标志，也可以是多个标志的按位OR组合。
 *     当前支持的音频会话行为详见{@link OH_AudioSession_BehaviorFlags}。
 * @return AUDIOSTREAM_SUCCESS：函数执行成功。
 *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM：参数为空指针或超出范围。
 *     <br>AUDIOSTREAM_ERROR_ILLEGAL_STATE：执行状态异常。
 * @since 24
 */
OH_AudioStream_Result OH_AudioCapturer_SetIndependentAudioSessionStrategy(
    OH_AudioCapturer* capturer, const OH_AudioSession_Strategy *strategy, uint32_t behavior);

/**
 * @brief 蜂窝通话录音场景下，风险提示语播放结束的回调函数。
 * 应用必须等待回调返回许可结果，且isPermitted为true时，方可开始蜂窝通话录音。
 *
 * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param userData 通过{@link OH_AudioStreamBuilder_SetSensitiveRecordPermitCallback}指向应用自定义的数据存储区域。
 * @param isPermitted 表示风险提示语是否播放结束。若结果为true，表示可以开始录音；若为false，表示录音未被允许。
 * @since 26.0.0
 */
typedef void (*OH_AudioCapturer_SensitiveRecordPermitCallback)(
    OH_AudioCapturer* capturer,
    void* userData,
    bool isPermitted);

/**
 * @brief 设置当前录音流的降噪模式。
 * 建议先调用OH_AudioCapturer_GetSupportedNoiseReductionModes获取当前录音流支持的降噪模式后，再通过本接口进行设置。
 * 当前仅支持使用AUDIOSTREAM_SOURCE_TYPE_VOICE_MESSAGE创建的录音流进行降噪模式设置，其他录音流默认仅
 * 支持AUDIO_NOISE_REDUCTION_MODE_FIDELITY。降噪效果受设备平台、音频设备和录音并发情况影响。
 * 存在多个录音流同时运行时，设置的降噪模式可能不生效。
 * 该接口仅可在录音流创建后未开始录音，或停止录音后调用。
 *
 * @param capturer [in] 指向OH_AudioStreamBuilder_GenerateCapturer创建的音频流实例。
 * @param noiseReductionMode [in] 要设置的降噪模式。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS}函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}参数capturer为nullptr，或参数noiseReductionMode无效。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE}录音流处于运行态或已释放。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_UNSUPPORTED_ABILITY}设置的降噪模式不支持。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_SERVICE_DIED}音频服务进程异常结束。</li>
 *     </ul>
 * @since 26.0.0
 */
OH_AudioStream_Result OH_AudioCapturer_SetNoiseReductionMode(OH_AudioCapturer* capturer,
    OH_AudioNoiseReductionMode noiseReductionMode);

/**
 * @brief 获取当前录音流的降噪模式。返回结果仅反映当前录音流的降噪模式。默认值为AUDIO_NOISE_REDUCTION_MODE_FIDELITY。
 *
 * @param capturer [in] 指向OH_AudioStreamBuilder_GenerateCapturer创建的音频流实例。
 * @param noiseReductionMode [out] 指向接收当前降噪模式的变量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS}函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}参数capturer为nullptr，或参数noiseReductionMode为nullptr。</li>
 *     </ul>
 * @since 26.0.0
 */
OH_AudioStream_Result OH_AudioCapturer_GetNoiseReductionMode(OH_AudioCapturer* capturer,
    OH_AudioNoiseReductionMode* noiseReductionMode);

/**
 * @brief 获取当前设备平台支持的录音降噪模式。
 * 当前仅使用AUDIOSTREAM_SOURCE_TYPE_VOICE_MESSAGE创建的录音流会根据设备平台查询支持的降噪模式，其他录音流
 * 默认仅返回AUDIO_NOISE_REDUCTION_MODE_FIDELITY。
 * 返回结果仅考虑音频格式和设备平台，不考虑当前输入设备和录音并发情况。
 * 当支持的模式数量大于入参inModeArraySize时，仅向noiseReductionModeArray写入前inModeArraySize个模式，
 * outModeArraySize等于inModeArraySize。
 * 建议应用预留较大的数组长度，例如20，以兼容后续新增模式。
 * @param capturer [in] 指向OH_AudioStreamBuilder_GenerateCapturer创建的音频流实例。
 * @param noiseReductionModeArray [out] 指向应用分配的数组，用于接收支持的录音降噪模式，
 *     默认支持AUDIO_NOISE_REDUCTION_MODE_FIDELITY。
 * @param inModeArraySize [in] noiseReductionModeArray数组的元素个数。
 * @param outModeArraySize [out] 指向接收实际写入模式数量的变量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS}函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM}参数capturer为nullptr，或参数noiseReductionModeArray为nullptr，
 *             或参数outModeArraySize为nullptr。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_SERVICE_DIED}音频服务进程死亡。</li>
 *     </ul>
 * @since 26.0.0
 */
OH_AudioStream_Result OH_AudioCapturer_GetSupportedNoiseReductionModes(OH_AudioCapturer* capturer,
    OH_AudioNoiseReductionMode* noiseReductionModeArray, uint32_t inModeArraySize, uint32_t *outModeArraySize);

#ifdef __cplusplus
}
#endif
#endif // NATIVE_AUDIOCAPTURER_H
/** @} */