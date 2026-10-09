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
 * @addtogroup OHAudio
 * @{
 *
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 10
 */

/**
 * @file native_audiocapturer.h
 *
 * @brief OH_AudioCapturer提供音频录制流功能，目前主要用于录制PCM（Pulse Code Modulation）音频数据。在录制过程中，需要持续从系统读取已录到的音频数据，适用于需要在录制后对音频数据进行后处理、
 * 对录制过程有更灵活控制要求的场景，如专业媒体录制、语音识别、语音消息、语音通话等。不同录制场景需通过{@link OH_AudioStream_SourceType}配置合适的录音源类型，以便让系统匹配合适的音效、设备与焦点策略。
 * <br>使用OH_AudioCapturer实现音频录制功能时，需先设置音频核心参数（采样率、声道、编码类型、采样格式、使用场景等）并设置数据读取回调，通过
 * {@link OH_AudioStreamBuilder_GenerateCapturer}创建录制流实例，随后调用{@link OH_AudioCapturer_Start}开始录制。录制过程中可通过
 * {@link OH_AudioCapturer_Pause}控制录制暂停、{@link OH_AudioCapturer_Stop}控制录制停止，退出录制时通过{@link OH_AudioCapturer_Release}释放资源。
 * OH_AudioCapturer内具备状态机，仅在特定状态下调用相应方法才能正常工作。
 * <br>使用麦克风录制时，需申请ohos.permission.MICROPHONE权限，并且录制流只能在前台启动，启动后可退至后台保持运行。
 * <br>由于系统对音频流数量有限制，不再使用时应及时调用{@link OH_AudioCapturer_Release}释放资源，避免后续创建音频流失败。
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
#include "native_audio_session_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 释放音频录制流。
 * <br>输入的OH_AudioCapturer指针指向的内存也会释放，不能再被使用，建议开发者在释放后主动将指针置空。
 *
 * @permission ohos.permission.MICROPHONE
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} 执行状态异常。</li>
 *         </ul>
 *  @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_Release(OH_AudioCapturer* capturer);

/**
 * @brief 启动音频录制流。
 * <br>音频流开始运行后，注册的数据回调会被周期性的触发，让调用者读取已录到的音频数据。
 *
 * @permission ohos.permission.MICROPHONE
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} 执行状态异常。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_Start(OH_AudioCapturer* capturer);

/**
 * @brief 暂停音频录制流。
 * <br>在暂停音频后，后续需要恢复录音的场景，建议使用此接口。但在录音数据处理方面，此接口与OH_AudioCapturer_Stop无差异。
 *
 * @permission ohos.permission.MICROPHONE
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} 执行状态异常。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_Pause(OH_AudioCapturer* capturer);

/**
 * @brief 停止音频录制流。
 * <br>在需要彻底结束录音的场景，建议使用此接口。但在录音数据处理方面，此接口与OH_AudioCapturer_Pause无差异。
 *
 * @permission ohos.permission.MICROPHONE
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} 执行状态异常。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_Stop(OH_AudioCapturer* capturer);

/**
 * @brief 清空音频录制流缓冲区的音频数据。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} 执行状态异常。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_Flush(OH_AudioCapturer* capturer);

/**
 * @brief 获取当前音频录制流状态。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param state [out] 用于接收获取的音频录制流状态。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetCurrentState(OH_AudioCapturer* capturer, OH_AudioStream_State* state);

/**
 * @brief 获取当前音频录制流时延模式。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param latencyMode [out] 用于接收获取的音频录制流时延模式。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetLatencyMode(OH_AudioCapturer* capturer,
    OH_AudioStream_LatencyMode* latencyMode);

/**
 * @brief 获取当前音频录制流ID。
 * <br>音频系统会在创建时为每一个音频流分配全局唯一的音频流ID，此ID可以作为音频流的标识。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param streamId [out] 用于接收获取的音频流ID。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetStreamId(OH_AudioCapturer* capturer, uint32_t* streamId);

/**
 * @brief 获取当前音频录制流采样率，单位为Hz。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param rate [out] 用于接收获取的音频录制流采样率，单位为Hz。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetSamplingRate(OH_AudioCapturer* capturer, int32_t* rate);

/**
 * @brief 获取当前音频录制流声道数。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param channelCount [out] 用于接收获取的音频录制流声道数。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetChannelCount(OH_AudioCapturer* capturer, int32_t* channelCount);

/**
 * @brief 获取当前音频录制流采样格式。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param sampleFormat [out] 用于接收获取的音频录制流采样格式。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetSampleFormat(OH_AudioCapturer* capturer,
    OH_AudioStream_SampleFormat* sampleFormat);

/**
 * @brief 获取当前音频录制流编码类型。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param encodingType [out] 用于接收获取的音频录制流编码类型。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetEncodingType(OH_AudioCapturer* capturer,
    OH_AudioStream_EncodingType* encodingType);

/**
 * @brief 获取当前音频录制流的使用场景类型。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param sourceType [out] 用于接收获取的音频录制流使用场景类型。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetCapturerInfo(OH_AudioCapturer* capturer,
    OH_AudioStream_SourceType* sourceType);

/**
 * @brief 获取当前音频录制流每次数据回调可读取的音频数据帧长，单位为采样点数。
 * <br>当音频录制流运行模式发生变化时，如从低时延模式切换到普通模式，此帧长可能发生变化。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param frameSize [out] 用于接收获取的音频数据帧长，单位为采样点数。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} 执行状态异常。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetFrameSizeInCallback(OH_AudioCapturer* capturer, int32_t* frameSize);

/**
 * @brief 获取音频录制流时间戳和当前数据帧位置信息。
 * <br>该接口可以获取到音频通道实际录制位置（framePosition）以及录制到该位置时的时间戳（timestamp），时间戳单位为ns。主要用于录像音画同步场景。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param clockId [in] 时钟标识符，使用CLOCK_MONOTONIC。
 * @param framePosition [out] 用于接收获取的最近输入音频帧位置。
 * @param timestamp [out] 用于接收获取的最近输入音频帧时间戳，与位置对应，单位为ns。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 1. 参数capturer为空指针；2. 参数clockId无效。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} 执行状态异常。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetTimestamp(OH_AudioCapturer* capturer,
    clockid_t clockId, int64_t* framePosition, int64_t* timestamp);

/**
 * @brief 查询自创建音频录制流以来已读取的帧数，单位为采样点数。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param frames [out] 用于接收获取的已读取帧数，单位为采样点数。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         </ul>
 * @since 10
 */
OH_AudioStream_Result OH_AudioCapturer_GetFramesRead(OH_AudioCapturer* capturer, int64_t* frames);

/**
 * @brief 获取当前音频录制流过载次数。
 * <br>在录制过程中，如果调用者没有及时通过数据回调读取音频数据，系统内部缓存被录音数据填满，就会触发过载，新录到的数据会覆盖缓存内的历史数据，导致数据丢失。
 * <br>过载次数是按照音频系统的数据处理周期计算的，而不是以应用设置的回调长度作为周期。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param count [out] 用于接收获取的音频录制流过载次数。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         </ul>
 * @since 12
 */
OH_AudioStream_Result OH_AudioCapturer_GetOverflowCount(OH_AudioCapturer* capturer, uint32_t* count);

/**
 * @brief 音频录制流读取音频数据回调函数的原型定义。
 * <br>为了消除麦克风硬件设计带来的上电杂音，通常会对录音启动后的前100ms数据进行静音。
 *
 * @param capturer 指向触发回调的音频录制流实例。
 * @param userData 指向开发者在注册回调函数时传入的userData数据。
 * @param audioData 指向让应用读取的录制数据。
 * @param audioDataSize 应用可读取的录制数据的数据长度，单位为Byte。
 * @see OH_AudioCapturer_Callbacks_Struct.OH_AudioCapturer_OnReadData
 * @since 20
 */
typedef void (*OH_AudioCapturer_OnReadDataCallback)(OH_AudioCapturer* capturer, void* userData, void* audioData,
    int32_t audioDataSize);

/**
 * @brief 音频录制流设备变化事件回调函数的原型定义。
 *
 * @param capturer 指向触发回调的音频录制流实例。
 * @param userData 指向开发者在注册回调函数时传入的userData数据。
 * @param deviceArray 变化后的音频设备描述符数组。
 * @see OH_AudioCapturer_Callbacks_Struct.OH_AudioCapturer_OnStreamEvent
 * @since 20
 */
typedef void (*OH_AudioCapturer_OnDeviceChangeCallback)(OH_AudioCapturer* capturer, void* userData,
    OH_AudioDeviceDescriptorArray* deviceArray);

/**
 * @brief 音频录制流中断事件回调函数的原型定义。
 *
 * @param capturer 指向触发回调的音频录制流实例。
 * @param userData 指向开发者在注册回调函数时传入的userData数据。
 * @param type 音频流中断类型。
 * @param hint 音频流中断提示类型。
 * @see OH_AudioCapturer_Callbacks_Struct.OH_AudioCapturer_OnInterruptEvent.
 * @since 20
 */
typedef void (*OH_AudioCapturer_OnInterruptCallback)(OH_AudioCapturer* capturer, void* userData,
    OH_AudioInterrupt_ForceType type, OH_AudioInterrupt_Hint hint);

/**
 * @brief 音频录制流错误事件回调函数的原型定义。
 *
 * @param capturer 指向触发回调的音频录制流实例。
 * @param userData 指向开发者在注册回调函数时传入的userData数据。
 * @param error 音频流录制错误结果。
 * @see OH_AudioCapturer_Callbacks_Struct.OH_AudioCapturer_OnError
 * @since 20
 */
typedef void (*OH_AudioCapturer_OnErrorCallback)(OH_AudioCapturer* capturer, void* userData,
    OH_AudioStream_Result error);

/**
 * @brief 获取音频录制过程中的运行状态，是否在低时延运行状态下工作。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param status [out] 用于接收获取的低时延运行状态。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} 执行状态异常，仅在释放状态之前可用。</li>
 *         </ul>
 * @since 20
 */
OH_AudioStream_Result OH_AudioCapturer_GetFastStatus(OH_AudioCapturer* capturer,
    OH_AudioStream_FastStatus* status);

/**
 * @brief 音频录制流低时延状态变化事件回调函数的原型定义。
 *
 * @param capturer 指向触发回调的音频录制流实例。
 * @param userData 指向开发者在注册回调函数时传入的userData数据。
 * @param status 当前低时延运行状态。
 * @since 20
 */
typedef void (*OH_AudioCapturer_OnFastStatusChange)(
    OH_AudioCapturer* capturer,
    void* userData,
    OH_AudioStream_FastStatus status
);

/**
 * @brief 内录（录制系统内部音频）启动结果回调函数的原型定义。
 * <br>该API最初仅对特定系统应用可用，从API版本26.0.0开始，支持任意应用使用。
 *
 * @param capturer 指向触发回调的音频录制流实例。
 * @param userData 指向开发者通过{@link OH_AudioCapturer_RequestPlaybackCaptureStart}传入的userData数据。
 * @param state 表示内录请求是否成功的状态。
 * @since 23
 */
typedef void (*OH_AudioCapturer_OnPlaybackCaptureStartCallback)(
    OH_AudioCapturer* capturer,
    void* userData,
    OH_AudioStream_PlaybackCaptureStartState state);

/**
 * 异步请求启动内录（录制系统内部音频）。<br>该函数是非阻塞的，意味着系统在接收到启动请求后，将在函数返回后继续处理用户授权和内录流的启动。最终的启动结果将通过回调函数返回。<br>该API最初仅对特定系统应用可用，从API版本26.
 * 0.0开始，支持任意应用使用。
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param callback [in] 用于接收启动请求最终结果的回调函数。
 * @param userData [in] 用户自定义数据指针，回调函数触发时会携带。若无需传递数据，可传入空指针。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} capturer或callback是无效的。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} 如果流已经在运行中或者已释放则是非法状态。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_SYSTEM} 系统内部错误，比如音频服务错误。</li>
 *         </ul>
 * @since 23
 */
OH_AudioStream_Result OH_AudioCapturer_RequestPlaybackCaptureStart(OH_AudioCapturer* capturer,
    OH_AudioCapturer_OnPlaybackCaptureStartCallback callback, void* userData);

/**
 * @brief 将当前录制流的自身静音状态传递给音频系统。
 * <br>该接口用于在语音通话和语音会议场景，应用可向音频系统告知其进入录音静音状态（应用内实现录音静音），系统不会对录制流进行静音处理，而是会基于设置的状态调整数据处理策略以降低功耗。当前仅在部分PC/2in1设备上具备此效果。
 * <br>该接口仅在录制流处于运行态时允许调用，否则返回状态错误。
 * <br>应用同时设置音频流级静音提示接口（本接口）和会话级静音提示接口{@link OH_AudioSessionManager_SetCaptureMuteHint}时，本接口优先级更高。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param mute [in] 应用内录音静音状态。true表示该录制流为静音状态，false表示该录制流为非静音状态。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} 操作状态异常，录制流未处于运行状态。</li>
 *         </ul>
 * @since 24
 */
OH_AudioStream_Result OH_AudioCapturer_SetMuteHint(OH_AudioCapturer* capturer, bool mute);

/**
 * @brief 设置音频录制流的独立音频会话策略和行为参数，这些参数主要用于扩展音频流的默认并发策略。
 * <br>建议在音频流处于运行状态前设置。当在音频流运行时调用此接口，只会在下次调用接口{@link OH_AudioCapturer_Start}启动音频流后参数才会生效。
 * 
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param strategy [in] 用于设置独立的音频会话策略。
 * @param behavior [in] 音频会话行为标志，可以是单个标志，也可以是多个标志的按位OR组合。当前支持的音频会话行为详见{@link OH_AudioSession_BehaviorFlags}。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数为空指针或超出范围。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} 执行状态异常。</li>
 *         </ul>
 * @since 24
 */
OH_AudioStream_Result OH_AudioCapturer_SetIndependentAudioSessionStrategy(
    OH_AudioCapturer* capturer, const OH_AudioSession_Strategy *strategy, uint32_t behavior);

/**
 * @brief 蜂窝通话录音场景下，风险提示语播放结束回调函数的原型定义。
 * <br>应用必须等待回调返回许可结果，且isPermitted为true时，方可开始蜂窝通话录音。
 *
 * @param capturer 指向触发回调的音频录制流实例。
 * @param userData 指向开发者通过{@link OH_AudioStreamBuilder_SetSensitiveRecordPermitCallback}传入的userData数据。
 * @param isPermitted 表示风险提示语是否播放结束。若结果为true，表示可以开始录音；若为false，表示录音未被允许。
 * @since 26.0.0
 */
typedef void (*OH_AudioCapturer_SensitiveRecordPermitCallback)(
    OH_AudioCapturer* capturer,
    void* userData,
    bool isPermitted);

/**
 * @brief 设置当前录制流的降噪模式。建议先调用{@link OH_AudioCapturer_GetSupportedNoiseReductionModes}获取当前录制流支持的降噪模式后，再通过本接口进行设置。
 * <br>当前仅支持使用{@link AUDIOSTREAM_SOURCE_TYPE_VOICE_MESSAGE}创建的录制流进行降噪模式设置，其他录制流默认仅支持
 * {@link AUDIO_NOISE_REDUCTION_MODE_FIDELITY}。降噪效果受设备平台、音频设备和录音并发情况影响。存在多个录制流同时运行时，设置的降噪模式可能不生效。
 * <br>该接口仅可在录制流创建后未开始录音，或停止录音后调用；录制流处于运行态或已释放时调用将返回{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE}。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param noiseReductionMode [in] 要设置的降噪模式。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针，或参数noiseReductionMode无效。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_ILLEGAL_STATE} 录制流处于运行态或已释放。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_UNSUPPORTED_ABILITY} 设置的降噪模式不支持。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_SERVICE_DIED} 音频服务进程异常结束。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioStream_Result OH_AudioCapturer_SetNoiseReductionMode(OH_AudioCapturer* capturer,
    OH_AudioNoiseReductionMode noiseReductionMode);

/**
 * @brief 获取当前录制流的降噪模式。返回结果仅反映当前录制流的降噪模式。默认值为{@link AUDIO_NOISE_REDUCTION_MODE_FIDELITY}。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param noiseReductionMode [out] 用于接收获取的录制流降噪模式。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针，或参数noiseReductionMode为空指针。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioStream_Result OH_AudioCapturer_GetNoiseReductionMode(OH_AudioCapturer* capturer,
    OH_AudioNoiseReductionMode* noiseReductionMode);

/**
 * @brief 获取当前设备平台支持的录音降噪模式。当前仅使用{@link AUDIOSTREAM_SOURCE_TYPE_VOICE_MESSAGE}创建的录制流会根据设备平台查询支持的降噪模式，其他录制流默认仅返回
 * {@link AUDIO_NOISE_REDUCTION_MODE_FIDELITY}。返回结果仅考虑音频格式和设备平台，不考虑当前输入设备和录音并发情况。
 * <br>当支持的模式数量大于入参inModeArraySize时，仅向noiseReductionModeArray写入前inModeArraySize个模式，outModeArraySize等于inModeArraySize。
 * 建议应用预留较大的数组长度，例如20，以兼容后续新增模式。
 *
 * @param capturer [in] 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
 * @param noiseReductionModeArray [out] 由应用分配的数组，用于接收支持的录音降噪模式，默认支持{@link AUDIO_NOISE_REDUCTION_MODE_FIDELITY}。
 * @param inModeArraySize [in] noiseReductionModeArray数组的容量。
 * @param outModeArraySize [out] 用于接收实际获取的降噪模式数量。
 * @return <ul>
 *         <li>{@link AUDIOSTREAM_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_INVALID_PARAM} 参数capturer为空指针，或参数noiseReductionModeArray为空指针，或参数outModeArraySize为空指针。</li>
 *         <li>{@link AUDIOSTREAM_ERROR_SERVICE_DIED} 音频服务进程死亡。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioStream_Result OH_AudioCapturer_GetSupportedNoiseReductionModes(OH_AudioCapturer* capturer,
    OH_AudioNoiseReductionMode* noiseReductionModeArray, uint32_t inModeArraySize, uint32_t *outModeArraySize);

#ifdef __cplusplus
}
#endif
#endif // NATIVE_AUDIOCAPTURER_H
/** @} */