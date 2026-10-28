/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
 * @brief 提供音频模块C接口定义，可用于实现音频播放、录制和相关的音量、设备、会话管理等功能，
 * 服务于媒体播放、语音通话、游戏音频等音频业务开发场景。
 *
 * @since 10
 * @version 1.0
 */

/**
 * @file native_audiostream_base.h
 *
 * @brief 声明音频播放和录制流模块使用的基础数据结构和枚举定义。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 10
 * @version 1.0
 */
#ifndef NATIVE_AUDIOSTREAM_BASE_H
#define NATIVE_AUDIOSTREAM_BASE_H
#include <stdint.h>
#include "multimedia/native_audio_channel_layout.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 音频错误码。
 *
 * @since 10
 */
typedef enum {
    /**
     * @error 操作成功
     * @since 10
     */
    AUDIOSTREAM_SUCCESS = 0,

    /**
     * @error 入参错误。
     * @since 10
     */
    AUDIOSTREAM_ERROR_INVALID_PARAM = 1,

    /**
     * @error 非法状态。
     * @since 10
     */
    AUDIOSTREAM_ERROR_ILLEGAL_STATE = 2,

    /**
     * @error 系统通用错误。
     * @since 10
     */
    AUDIOSTREAM_ERROR_SYSTEM = 3,

    /**
     * @error 不支持的音频格式，如不支持的编码类型、采样格式等。
     * @since 19
     */
    AUDIOSTREAM_ERROR_UNSUPPORTED_FORMAT = 4,

    /**
     * @error 不支持的音频流功能，包括功能和配置。
     *
     * @since 26.0.0
     */
    AUDIOSTREAM_ERROR_UNSUPPORTED_ABILITY = 6800104,

    /**
     * @error 音频服务器进程死掉。
     *
     * @since 26.0.0
     */
    AUDIOSTREAM_ERROR_SERVICE_DIED = 6800302
} OH_AudioStream_Result;

/**
 * @brief 音频流类型。
 *
 * @since 10
 */
typedef enum {
    /**
     * 表示音频播放流。
     * @since 10
     */
    AUDIOSTREAM_TYPE_RENDERER = 1,

    /**
     * 表示音频录制流。
     * @since 10
     */
    AUDIOSTREAM_TYPE_CAPTURER = 2
} OH_AudioStream_Type;

/**
 * @brief 定义音频流采样格式。
 *
 * @since 10
 */
typedef enum {
    /**
     * Unsigned 8位。
     * @since 10
     */
    AUDIOSTREAM_SAMPLE_U8 = 0,

    /**
     * Signed 16位小端。
     * @since 10
     */
    AUDIOSTREAM_SAMPLE_S16LE = 1,

    /**
     * Signed 24位小端。
     * @since 10
     */
    AUDIOSTREAM_SAMPLE_S24LE = 2,

    /**
     * Signed 32位小端。
     * @since 10
     */
    AUDIOSTREAM_SAMPLE_S32LE = 3,

    /**
     * Float 32位小端。
     * @since 17
     */
    AUDIOSTREAM_SAMPLE_F32LE = 4
} OH_AudioStream_SampleFormat;

/**
 * @brief 定义音频流编码类型。
 *
 * @since 10
 */
typedef enum {
    /**
     * PCM编码。
     * @since 10
     */
    AUDIOSTREAM_ENCODING_TYPE_RAW = 0,

    /**
     * Audio Vivid编码。
     * @since 12
     */
    AUDIOSTREAM_ENCODING_TYPE_AUDIOVIVID = 1,

    /**
     * E_AC3编码。
     * @since 19
     */
    AUDIOSTREAM_ENCODING_TYPE_E_AC3 = 2,
} OH_AudioStream_EncodingType;

/**
 * @brief 声明音频流信息结构体，该结构体用于表示音频基础格式，包括采样率、声道布局、编码格式和采样格式信息。
 *
 * @since 19
 */
typedef struct OH_AudioStreamInfo {
    /**
     * @brief 音频流采样率，单位为Hz。
     *
     * @since 19
     */
    int32_t samplingRate;
    /**
     * @brief 音频流声道布局。
     *
     * @since 19
     */
    OH_AudioChannelLayout channelLayout;
    /**
     * @brief 音频流编码格式。
     *
     * @since 19
     */
    OH_AudioStream_EncodingType encodingType;
    /**
     * @brief 音频流采样格式。
     *
     * @since 19
     */
    OH_AudioStream_SampleFormat sampleFormat;
} OH_AudioStreamInfo;

/**
 * @brief 定义音频播放流使用场景。
 * <br>使用场景影响音频播放流的音效、音量、设备与焦点策略。
 *
 * @since 10
 */
typedef enum {
    /**
     * 未知类型。
     * @since 10
     */
    AUDIOSTREAM_USAGE_UNKNOWN = 0,

    /**
     * 音乐。
     * @since 10
     */
    AUDIOSTREAM_USAGE_MUSIC = 1,

    /**
     * VoIP语音通话。
     * @since 10
     */
    AUDIOSTREAM_USAGE_VOICE_COMMUNICATION = 2,

    /**
     * 语音播报。
     * @since 10
     */
    AUDIOSTREAM_USAGE_VOICE_ASSISTANT = 3,

    /**
     * 闹钟。
     * @since 10
     */
    AUDIOSTREAM_USAGE_ALARM = 4,

    /**
     * 语音消息。
     * @since 10
     */
    AUDIOSTREAM_USAGE_VOICE_MESSAGE = 5,

    /**
     * 铃声。
     * @since 10
     */
    AUDIOSTREAM_USAGE_RINGTONE = 6,

    /**
     * 通知。
     * @since 10
     */
    AUDIOSTREAM_USAGE_NOTIFICATION = 7,

    /**
     * 无障碍。
     * @since 10
     */
    AUDIOSTREAM_USAGE_ACCESSIBILITY = 8,

    /**
     * 电影或视频。
     * @since 10
     */
    AUDIOSTREAM_USAGE_MOVIE = 10,

    /**
     * 游戏（包括游戏音效和背景音）。
     * @since 10
     */
    AUDIOSTREAM_USAGE_GAME = 11,

    /**
     * 有声读物（包括听书、相声、评书）、听新闻、播客等。
     * @since 10
     */
    AUDIOSTREAM_USAGE_AUDIOBOOK = 12,

    /**
     * 导航。
     * @since 10
     */
    AUDIOSTREAM_USAGE_NAVIGATION = 13,

    /**
     * VoIP视频通话。
     * @since 12
     */
    AUDIOSTREAM_USAGE_VIDEO_COMMUNICATION = 17
} OH_AudioStream_Usage;

/**
 * @brief 定义音频时延模式。
 *
 * @since 10
 */
typedef enum {
    /**
     * 普通时延模式。默认模式，常规的媒体、通话和录音录像场景均推荐使用此模式。
     * @since 10
     */
    AUDIOSTREAM_LATENCY_MODE_NORMAL = 0,

    /**
     * 低时延模式。使用此模式进行音频播放或录制，会消耗更多系统CPU资源，适用于游戏和K歌场景。
     * @since 10
     */
    AUDIOSTREAM_LATENCY_MODE_FAST = 1,
} OH_AudioStream_LatencyMode;

/**
 * @brief 定义音频流直通通路播放模式。
 * <br>使用直通通路的音频播放流，不会与其他播放流混音，系统也不会对数据进行处理，直接输出到底层硬件。
 * 通常用于高音质音源播放场景。
 *
 * @since 19
 */
typedef enum {
    /**
     * 该模式表示不支持直通通路播放。
     * @since 19
     */
    AUDIOSTREAM_DIRECT_PLAYBACK_NOT_SUPPORTED = 0,
    /**
     * 该模式表示支持编码格式的直通通路播放。
     * @since 19
     */
    AUDIOSTREAM_DIRECT_PLAYBACK_BITSTREAM_SUPPORTED = 1,
    /**
     * 该模式表示支持PCM编码的直通通路播放。
     * @since 19
     */
    AUDIOSTREAM_DIRECT_PLAYBACK_PCM_SUPPORTED = 2
} OH_AudioStream_DirectPlaybackMode;

/**
 * @brief 定义音频事件。
 *
 * @deprecated since 20
 * @useinstead OH_AudioRenderer_OutputDeviceChangeCallback.
 * @since 10
 */
typedef enum {
    /**
     * 音频的路由已更改。
     * @deprecated since 20
     * @useinstead OH_AudioRenderer_OutputDeviceChangeCallback.
     * @since 10
     */
    AUDIOSTREAM_EVENT_ROUTING_CHANGED = 0
} OH_AudioStream_Event;

/**
 * @brief 定义音频流的状态。
 *
 * @since 10
 */
typedef enum {
    /**
     * 不合法的状态。
     * @since 10
     */
    AUDIOSTREAM_STATE_INVALID = -1,

    /**
     * 新创建时的状态。
     * @since 10
     */
    AUDIOSTREAM_STATE_NEW = 0,

    /**
     * 准备状态。
     * @since 10
     */
    AUDIOSTREAM_STATE_PREPARED = 1,

    /**
     * 工作状态。
     * @since 10
     */
    AUDIOSTREAM_STATE_RUNNING = 2,

    /**
     * 停止状态。
     * @since 10
     */
    AUDIOSTREAM_STATE_STOPPED = 3,

    /**
     * 释放状态。
     * @since 10
     */
    AUDIOSTREAM_STATE_RELEASED = 4,

    /**
     * 暂停状态。
     * @since 10
     */
    AUDIOSTREAM_STATE_PAUSED = 5
} OH_AudioStream_State;

/**
 * @brief 定义音频中断是否由系统强制执行。
 * <br>当用户监听到音频中断时，将获取此信息。
 * <br>此类型表示音频中断提示{@link OH_AudioInterrupt_Hint}对应的操作是否已由系统强制执行，具体操作信息（如音频暂停、停止等）可通过{@link OH_AudioInterrupt_Hint}获取。
 * <br>其中，AUDIOSTREAM_INTERRUPT_HINT_RESUME对应的{@link OH_AudioInterrupt_ForceType}一定为AUDIOSTREAM_INTERRUPT_SHARE，即恢复操作无法由系统强制执行，需应用自行触发。
 *
 * @since 10
 */
typedef enum {
    /**
     * 强制执行类型，即中断提示{@link OH_AudioInterrupt_Hint}对应的操作已由系统强制执行。
     * @since 10
     */
    AUDIOSTREAM_INTERRUPT_FORCE = 0,

    /**
     * 非强制执行类型，即系统不执行对应操作，仅通过{@link OH_AudioInterrupt_Hint}提示应用操作，应用可自行决策下一步处理方式。
     * @since 10
     */
    AUDIOSTREAM_INTERRUPT_SHARE = 1
} OH_AudioInterrupt_ForceType;

/**
 * @brief 定义音频中断提示类型。
 * <br>当用户监听到音频中断时，将获取此信息。
 * <br>此类型表示根据焦点策略，当前需要对音频流的具体操作（如暂停、调整音量等）。
 * <br>可以结合{@link OH_AudioInterrupt_ForceType}信息，判断该操作是否已由系统强制执行。
 *
 * @since 10
 */
typedef enum {
    /**
     * 不提示。
     * @since 10
     */
    AUDIOSTREAM_INTERRUPT_HINT_NONE = 0,

    /**
     * 提示音频恢复，应用可主动触发开始渲染或开始采集的相关操作。
     * <br> 此操作无法由系统强制执行，其对应的{@link OH_AudioInterrupt_ForceType}
     * 一定为AUDIOSTREAM_INTERRUPT_SHARE类型。
     * @since 10
     */
    AUDIOSTREAM_INTERRUPT_HINT_RESUME = 1,

    /**
     * 提示音频暂停，暂时失去音频焦点。<br> 后续待焦点可用时，会出现AUDIOSTREAM_INTERRUPT_HINT_RESUME事件。
     * @since 10
     */
    AUDIOSTREAM_INTERRUPT_HINT_PAUSE = 2,

    /**
     * 提示音频停止，彻底失去音频焦点。
     * @since 10
     */
    AUDIOSTREAM_INTERRUPT_HINT_STOP = 3,

    /**
     * 提示音频躲避开始，音频降低音量播放，而不会停止。
     * @since 10
     */
    AUDIOSTREAM_INTERRUPT_HINT_DUCK = 4,

    /**
     * 提示音量躲避结束，音频恢复正常音量。
     * @since 10
     */
    AUDIOSTREAM_INTERRUPT_HINT_UNDUCK = 5,

    /**
     * 提示音频静音。
     * @since 20
     */
    AUDIOSTREAM_INTERRUPT_HINT_MUTE = 6,

    /**
     * 提示音频解除静音。
     * @since 20
     */
    AUDIOSTREAM_INTERRUPT_HINT_UNMUTE = 7
} OH_AudioInterrupt_Hint;

/**
 * @brief 定义音频录制流使用场景。
 * <br>使用场景影响音频录制流的音效、设备与焦点策略。
 *
 * @since 10
 */
typedef enum {
    /**
     * 无效类型。
     * @since 10
     */
    AUDIOSTREAM_SOURCE_TYPE_INVALID = -1,

    /**
     * 常规麦克风录音。
     * @since 10
     */
    AUDIOSTREAM_SOURCE_TYPE_MIC = 0,

    /**
     * 语音识别。
     * @since 10
     */
    AUDIOSTREAM_SOURCE_TYPE_VOICE_RECOGNITION = 1,

    /**
     * 内录（录制设备内部应用的声音）。
     * @deprecated since 12
     * @useinstead OH_AVScreenCapture in native interface.
     * @since 10
     */
    AUDIOSTREAM_SOURCE_TYPE_PLAYBACK_CAPTURE = 2,

    /**
     * 语音通话。
     * @since 10
     */
    AUDIOSTREAM_SOURCE_TYPE_VOICE_COMMUNICATION = 7,

    /**
     * 语音消息。
     * @since 12
     */
    AUDIOSTREAM_SOURCE_TYPE_VOICE_MESSAGE = 10,

    /**
     * 相机录像。
     * @since 13
     */
    AUDIOSTREAM_SOURCE_TYPE_CAMCORDER = 13,

    /**
     * 麦克风纯净录音（系统不做任何算法处理）。
     * @since 14
     */
    AUDIOSTREAM_SOURCE_TYPE_UNPROCESSED = 14,

    /**
     * 直播。
     * @since 20
     */
    AUDIOSTREAM_SOURCE_TYPE_LIVE = 17,

    /**
     * 蜂窝通话下行录音（通话中对方声音）。使用此输入流的音频采集器应在蜂窝通话开始后创建。
     * 使用{@link OH_AudioStreamBuilder_GenerateCapturer}创建采集流时需要ohos.
     * permission.CAPTURE_PLAYBACK_DOWNLINK权限，否则函数将返回错误。
     * @since 26.0.0
     */
    AUDIOSTREAM_SOURCE_TYPE_VOICE_DOWNLINK = 22
} OH_AudioStream_SourceType;

/**
 * @brief 定义音频中断模式。
 *
 * @since 12
 */
typedef enum {
    /**
     * 共享模式。应用进程的不同音频流共享一个焦点，不会相互打断。
     */
    AUDIOSTREAM_INTERRUPT_MODE_SHARE = 0,

    /**
     * 独立模式。应用进程的不同音频流焦点独立，根据系统默认的焦点策略，可以相互打断。
     */
    AUDIOSTREAM_INTERRUPT_MODE_INDEPENDENT = 1
} OH_AudioInterrupt_Mode;

/**
 * @brief 定义音效模式。
 *
 * @since 12
 */
typedef enum {
    /**
     * 无音效模式。
     * @since 12
     */
    EFFECT_NONE = 0,

    /**
     * 默认音效模式。
     * @since 12
     */
    EFFECT_DEFAULT = 1
} OH_AudioStream_AudioEffectMode;

/**
 * @brief 定义低时延状态。
 *
 * @since 20
 */
typedef enum {
    /**
     * 普通音频流状态。
     */
    AUDIOSTREAM_FASTSTATUS_NORMAL = 0,
    /**
     * 低时延音频流状态。
     * @since 20
     */
    AUDIOSTREAM_FASTSTATUS_FAST = 1
} OH_AudioStream_FastStatus;

/**
 * @brief 声明音频流构造器结构体，该结构体用于调用设置音频流属性和创建音频流功能接口。
 *
 * @since 10
 */
typedef struct OH_AudioStreamBuilderStruct OH_AudioStreamBuilder;

/**
 * @brief 声明音频渲染器结构体。该结构体用于调用音频播放流功能接口。
 *
 * @since 10
 */
typedef struct OH_AudioRendererStruct OH_AudioRenderer;

/**
 * @brief 声明音频采集器结构体，该结构体用于调用音频采集流功能接口。
 *
 * @since 10
 */
typedef struct OH_AudioCapturerStruct OH_AudioCapturer;

/**
 * @brief 声明用于同时设置音频渲染器的4个回调函数的结构体，
 * 包括写入音频数据、音频播放流事件、音频播放中断事件和音频播放错误回调函数。
 * {@link OH_AudioStreamBuilder_SetRendererCallback}接口会用此结构体设置回调。
 * <br>注意，在设置音频回调函数时，请确保该结构体的每一个成员变量都被自定义的回调函数或空指针初始化，
 * 避免未初始化的回调函数被系统调用，引起不可预知的行为。可参考开发指南-推荐使用OHAudio开发音频播放功能(C/C++)。
 *
 * @deprecated since 20
 * @useinstead Use the callback type: OH_AudioRenderer_OnWriteDataCallback, OH_AudioRenderer_OutputDeviceChangeCallback,
 * OH_AudioRenderer_OnInterruptCallback, OH_AudioRenderer_OnErrorCallback separately.
 * @since 10
 */
typedef struct OH_AudioRenderer_Callbacks_Struct {
    /**
     * 指向用于写入音频数据的回调函数。当渲染器处于运行状态，此回调会周期性地触发，让开发者持续写入播放数据。
     * 由于系统会将buffer内的全部数据用于播放，开发者需确保每次写入音频数据都填满buffer，
     * 否则会因播放未初始化的数据导致不可预期的行为。
     * 回调函数每次执行完成后，音频系统会将buffer数据暂时放入内部队列中等待处理，
     * 因此请勿在回调函数返回后修改buffer指向的数据，否则会导致播放出现杂音。
     * 注意，回调函数仅用来写入音频数据，请勿在回调函数中调用AudioRenderer的状态切换接口，避免引起死锁问题。
     * 请确保该结构体成员变量被自定义的回调函数或空指针初始化，避免未初始化的回调函数被系统调用，引起不可预知的行为。
     * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
     * @param userData 指向开发者在{@link OH_AudioStreamBuilder_SetRendererCallback}接口传入的userdata数据。
     * @param buffer 指向播放数据存储区域，开发者可从此buffer写入播放数据。
     * 每次写入都需要填满buffer，否则会因播放未初始化的数据导致不可预期的行为。
     * @param length buffer的长度，单位为字节(Byte)。
     * @return 回调函数返回值，当前版本系统并不处理，建议返回0。
     * @deprecated since 20
     * @useinstead OH_AudioRenderer_OnWriteDataCallback.
     * @since 10
     */
    int32_t (*OH_AudioRenderer_OnWriteData)(
            OH_AudioRenderer* renderer,
            void* userData,
            void* buffer,
            int32_t length);

    /**
     * 指向用于处理音频播放流事件的回调函数，但当前版本此回调不会被触发。
     * 请确保该结构体成员变量被自定义的回调函数或空指针初始化，避免未初始化的回调函数被系统调用，引起不可预知的行为。
     * 从API version 11开始，开发者如果需要监听音频设备变化，
     * 可直接使用{@link OH_AudioRenderer_OutputDeviceChangeCallback}替代。
     * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
     * @param userData 指向开发者在{@link OH_AudioStreamBuilder_SetRendererCallback}接口传入的userdata数据。
     * @param event 音频播放流状态变化事件类型。
     * @return 回调函数返回值，当前版本系统并不处理，建议返回0。
     * @deprecated since 20
     * @useinstead OH_AudioRenderer_OutputDeviceChangeCallback.
     * @since 10
     */
    int32_t (*OH_AudioRenderer_OnStreamEvent)(
            OH_AudioRenderer* renderer,
            void* userData,
            OH_AudioStream_Event event);

    /**
     * 指向用于处理音频播放中断事件的回调函数。当播放流被系统中其他高优先级音频打断，会触发此回调。
     * 请确保该结构体成员变量被自定义的回调函数或空指针初始化，避免未初始化的回调函数被系统调用，引起不可预知的行为。
     * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
     * @param userData 指向开发者在{@link OH_AudioStreamBuilder_SetRendererCallback}接口传入的userdata数据。
     * @param type 音频中断强制类型。
     * @param hint 音频中断提示类型。
     * @return 回调函数返回值，当前版本系统并不处理，建议返回0。
     * @deprecated since 20
     * @useinstead OH_AudioRenderer_OnInterruptCallback.
     * @since 10
     */
    int32_t (*OH_AudioRenderer_OnInterruptEvent)(
            OH_AudioRenderer* renderer,
            void* userData,
            OH_AudioInterrupt_ForceType type,
            OH_AudioInterrupt_Hint hint);

    /**
     * 指向用于处理音频播放错误结果的回调函数。当播放流在使用过程中出现错误情况，会触发此回调。
     * 请确保该结构体成员变量被自定义的回调函数或空指针初始化，避免未初始化的回调函数被系统调用，引起不可预知的行为。
     * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
     * @param userData 指向开发者在{@link OH_AudioStreamBuilder_SetRendererCallback}接口传入的userdata数据。
     * @param error 音频播放错误类型，常见错误包括：
     *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM（入参错误，请检查输入参数类型和有效范围）
     *     <br>AUDIOSTREAM_ERROR_ILLEGAL_STATE（非法状态，请检查当前状态是否允许执行该操作）
     *     <br>AUDIOSTREAM_ERROR_SYSTEM（系统通用错误，请检查系统状态或重试）
     * @return 回调函数返回值，当前版本系统并不处理，建议返回0。
     * @deprecated since 20
     * @useinstead OH_AudioRenderer_OnErrorCallback.
     * @since 10
     */
    int32_t (*OH_AudioRenderer_OnError)(
            OH_AudioRenderer* renderer,
            void* userData,
            OH_AudioStream_Result error);
} OH_AudioRenderer_Callbacks;

/**
 * @brief 声明用于同时设置音频采集器的4个回调函数的结构体，
 * 包括读取音频数据、音频录制流事件、音频录制中断事件和音频录制错误回调函数。
 * {@link OH_AudioStreamBuilder_SetCapturerCallback}接口会用此结构体设置回调。
 * <br>注意，在设置音频回调函数时，请确保该结构体的每一个成员变量都被自定义的回调函数或空指针初始化，
 * 避免未初始化的回调函数被系统调用，引起不可预知的行为。可参考开发指南-推荐使用OHAudio开发音频录制功能(C/C++)。
 *
 * 说明，以下回调接口的返回值均没有对应枚举定义，当前版本系统并不处理返回值，
 * 但考虑到后续系统版本的可扩展性，建议使用0作为返回值。
 *
 * @deprecated since 20
 * @useinstead Use the callback type: OH_AudioCapturer_OnReadDataCallback, OH_AudioCapturer_OnDeviceChangeCallback,
 * OH_AudioCapturer_OnInterruptCallback and OH_AudioCapturer_OnErrorCallback separately.
 * @since 10
 */
typedef struct OH_AudioCapturer_Callbacks_Struct {
    /**
     * 该指向用于读取音频数据的回调函数。当采集器处于运行状态，此回调会周期性地触发，让开发者持续读取录音数据。
     * 注意，回调函数仅用来读取音频数据，请勿在回调函数中调用AudioCapturer的状态切换接口，避免引起死锁问题。
     * 请确保该结构体成员变量被自定义的回调函数或空指针初始化，避免未初始化的回调函数被系统调用，引起不可预知的行为。
     * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
     * @param userData 指向开发者在{@link OH_AudioStreamBuilder_SetCapturerCallback}接口传入的userdata数据。
     * @param buffer 指向录音数据存储区域，开发者可从此buffer读取录音数据。系统会将录音数据填满buffer。
     * @param length buffer的长度，单位为字节(Byte)。
     * @return 回调函数返回值，当前版本系统并不处理，建议返回0。
     * @deprecated since 20
     * @useinstead OH_AudioCapturer_OnReadDataCallback
     * @since 10
     */
    int32_t (*OH_AudioCapturer_OnReadData)( OH_AudioCapturer* capturer, void* userData, void* buffer, int32_t length);

    /**
     * 指向用于处理音频录制流事件的回调函数。当音频录制流的状态发生变化，如音频设备路由变化，会触发此回调。
     * 请确保该结构体成员变量被自定义的回调函数或空指针初始化，避免未初始化的回调函数被系统调用，引起不可预知的行为。
     * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
     * @param userData 指向开发者在{@link OH_AudioStreamBuilder_SetCapturerCallback}接口传入的userdata数据。
     * @param event 音频录制流状态变化事件类型。
     * @return 回调函数返回值，当前版本系统并不处理，建议返回0。
     * @deprecated since 20
     * @useinstead OH_AudioCapturer_OnDeviceChangeCallback
     * @since 10
     */
    int32_t (*OH_AudioCapturer_OnStreamEvent)(
        OH_AudioCapturer* capturer,
        void* userData,
        OH_AudioStream_Event event);

    /**
     * 指向用于处理音频录制中断事件的回调函数。当音频录制流被系统中其他高优先级音频打断，会触发此回调。
     * 请确保该结构体成员变量被自定义的回调函数或空指针初始化，避免未初始化的回调函数被系统调用，引起不可预知的行为。
     * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
     * @param userData 指向开发者在{@link OH_AudioStreamBuilder_SetCapturerCallback}接口传入的userdata数据。
     * @param type 音频中断强制类型。
     * @param hint 音频中断提示类型。
     * @return 回调函数返回值，当前版本系统并不处理，建议返回0。
     *
     * @deprecated since 20
     * @useinstead OH_AudioCapturer_OnInterruptCallback
     * @since 10
     */
    int32_t (*OH_AudioCapturer_OnInterruptEvent)(
        OH_AudioCapturer* capturer,
        void* userData,
        OH_AudioInterrupt_ForceType type,
        OH_AudioInterrupt_Hint hint);

    /**
     * 指向用于处理音频录制错误结果的回调函数。当录制流在使用过程中出现错误情况，会触发此回调。
     * 请确保该结构体成员变量被自定义的回调函数或空指针初始化，避免未初始化的回调函数被系统调用，引起不可预知的行为。
     * @param capturer 指向{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频流实例。
     * @param userData 指向开发者在{@link OH_AudioStreamBuilder_SetCapturerCallback}接口传入的userdata数据。
     * @param error 音频录制错误类型，常见错误包括：
     *     <br>AUDIOSTREAM_ERROR_INVALID_PARAM（入参错误，请检查输入参数类型和有效范围）
     *     <br>AUDIOSTREAM_ERROR_ILLEGAL_STATE（非法状态，请检查当前状态是否允许执行该操作）
     *     <br>AUDIOSTREAM_ERROR_SYSTEM（系统通用错误，请检查系统状态或重试）
     * @return 回调函数返回值，当前版本系统并不处理，建议返回0。
     *
     * @deprecated since 20
     * @useinstead OH_AudioCapturer_OnErrorCallback
     * @since 10
     */
    int32_t (*OH_AudioCapturer_OnError)(
        OH_AudioCapturer* capturer,
        void* userData,
        OH_AudioStream_Result error);
} OH_AudioCapturer_Callbacks;

/**
 * @brief 流设备变更原因。
 *
 * @since 11
 */
typedef enum {
    /**
     * @brief 未知原因。
     *
     */
    REASON_UNKNOWN = 0,

    /**
     * @brief 新设备可用。例如，音频播放过程中连接有线/蓝牙耳机。
     *
     */
    REASON_NEW_DEVICE_AVAILABLE = 1,

    /**
     * @brief 旧设备不可用。例如，音频播放过程中断开有线/蓝牙耳机。当报告此原因时，应用程序应考虑暂停音频播放。
     *
     */
    REASON_OLD_DEVICE_UNAVAILABLE = 2,

    /**
     * @brief 用户或系统强制选择切换。例如，在播控中心强选设备。
     *
     */
    REASON_OVERRODE = 3,

    /**
     * @brief 音频会话管理中激活音频会话触发的设备切换。
     *
     * @since 20
     */
    REASON_SESSION_ACTIVATED = 4,

    /**
     * @brief 更高优先级的音频流出现导致的系统设备切换。例如，音乐播放过程中来电，通话流优先级更高导致音乐设备被切换。
     *
     * @since 20
     */
    REASON_STREAM_PRIORITY_CHANGED = 5
} OH_AudioStream_DeviceChangeReason;

/**
 * @brief 音频播放流输出设备变化回调函数的原型定义。
 *
 * @param renderer 指向触发回调的音频播放流实例。
 * @param userData 指向开发者在注册回调函数时传入的userData数据。
 * @param reason 播放流设备变化原因。
 * @since 11
 */
typedef void (*OH_AudioRenderer_OutputDeviceChangeCallback)(OH_AudioRenderer* renderer, void* userData,
    OH_AudioStream_DeviceChangeReason reason);

/**
 * @brief 音频播放到达标记位置事件回调函数的原型定义。
 *
 * @param renderer 指向触发回调的音频播放流实例。
 * @param samplePos 设置的播放到达标记位置，单位为采样点数。
 * @param userData 指向开发者在注册回调函数时传入的userData数据。
 * @since 12
 */
typedef void (*OH_AudioRenderer_OnMarkReachedCallback)(OH_AudioRenderer* renderer, uint32_t samplePos, void* userData);

/**
 * @brief 音频播放流写入音频数据和元数据回调函数的原型定义。
 * <br>回调函数仅用来写入音频数据，请勿在回调函数中调用AudioRenderer相关接口。
 * <br>回调函数结束后，音频服务会把audioData指针数据放入队列里等待播放，
 * 因此请勿在回调外再次更改audioData指向的数据，且务必保证往audioData填满audioDataSize长度的待播放数据，
 * 否则会导致音频服务播放杂音。
 *
 * @param renderer 指向触发回调的音频播放流实例。
 * @param userData 指向开发者在注册回调函数时传入的userData数据。
 * @param audioData 指向让应用写入的音频数据。
 * @param audioDataSize 应用需写入音频数据的数据长度，单位为字节(Byte)。
 * @param metadata 指向让应用写入的元数据，元数据内容与音频流编码格式类型相关。
 * @param metadataSize 应用需写入元数据的数据长度，单位为字节(Byte)。
 * @return 应用返回的回调函数的错误码。
 * @since 12
 */
typedef int32_t (*OH_AudioRenderer_WriteDataWithMetadataCallback)(OH_AudioRenderer* renderer,
    void* userData, void* audioData, int32_t audioDataSize, void* metadata, int32_t metadataSize);

/**
 * @brief 用于标识对应播放音频流是否支持被其他应用录制。
 *
 * @since 12
 */
typedef enum {
    /**
     * 公开类型，表示音频流不包含隐私内容，当音频流不是通话类型时，允许被其他应用录制或进行屏幕投射。
     * @since 12
     */
    AUDIO_STREAM_PRIVACY_TYPE_PUBLIC = 0,

    /**
     * 隐私类型，表示音频流包含隐私内容，不允许被其他应用录制或进行屏幕投射。
     * @since 12
     */
    AUDIO_STREAM_PRIVACY_TYPE_PRIVATE = 1,

    /**
     * 共享类型，表示音频流包含隐私内容，但允许被其他应用录制或进行屏幕投射。
     * <br>例如，在AUDIO_STREAM_PRIVACY_TYPE_PUBLIC策略下，
     * {@link AUDIOSTREAM_USAGE_VOICE_COMMUNICATION}类型的音频流不会被其他应用录制或进行屏幕投射。
     * 然而，在AUDIO_STREAM_PRIVACY_TYPE_SHARED策略下，这种音频流将会允许被其他应用录制或进行屏幕投射。
     * @since 21
     */
    AUDIO_STREAM_PRIVACY_TYPE_SHARED = 2
} OH_AudioStream_PrivacyType;

/**
 * @brief 定义音频数据回调结果。
 *
 * @since 12
 */
typedef enum {
    /**
     * 表示音频数据回调结果无效，音频数据不播放。
     */
    AUDIO_DATA_CALLBACK_RESULT_INVALID = -1,

    /**
     * 表示音频数据回调结果有效，音频数据将被播放。
     */
    AUDIO_DATA_CALLBACK_RESULT_VALID = 0
} OH_AudioData_Callback_Result;

/**
 * @brief 音频播放流写入音频数据回调函数的原型定义。
 * <br>回调函数仅用来写入音频数据，请勿在回调函数中调用AudioRenderer相关接口。
 * <br>该函数的返回结果表示填充到缓冲区的数据是否有效。如果结果是无效，用户填写的数据将不被播放。
 * <br>回调函数结束后，音频服务会把audioData指针数据放入队列里等待播放，
 * 因此请勿在回调外再次更改audioData指向的数据，且务必保证往audioData填满audioDataSize长度的待播放数据，
 * 否则会导致音频服务播放杂音。
 * <br>参数audioDataSize可以通过{@link OH_AudioStreamBuilder_SetFrameSizeInCallback}设置。
 * <br>为避免音频播放启动和停止时数据不连续可能出现的杂音，系统通常会在启动和停止时对音频数据做20ms以内的淡入淡出处理。
 *
 * @param renderer 指向触发回调的音频播放流实例。
 * @param userData 指向开发者在注册回调函数时传入的userData数据。
 * @param audioData 指向让应用写入的音频数据。
 * @param audioDataSize 应用需写入音频数据的数据长度，单位为字节(Byte)。
 * @return <ul>
 *         <li>{@link AUDIO_DATA_CALLBACK_RESULT_INVALID} 音频数据回调结果无效，音频数据不播放。</li>
 *         <li>{@link AUDIO_DATA_CALLBACK_RESULT_VALID} 音频数据回调结果有效，音频数据将被播放。</li>
 *         </ul>
 * @see OH_AudioRenderer_Callbacks_Struct.OH_AudioRenderer_OnWriteData
 * @since 12
 */
typedef OH_AudioData_Callback_Result (*OH_AudioRenderer_OnWriteDataCallback)(OH_AudioRenderer* renderer, void* userData,
    void* audioData, int32_t audioDataSize);

/**
 * @brief 定义音频流音量模式。
 *
 * @since 19
 */
typedef enum {
    /**
     * 系统级音量（默认模式）。音频流音量仅受系统音量影响。
     * @since 19
     */
    AUDIOSTREAM_VOLUMEMODE_SYSTEM_GLOBAL = 0,
    /**
     * 应用级音量。音频流音量会同时受系统音量和应用级音量影响。
     * @since 19
     */
    AUDIOSTREAM_VOLUMEMODE_APP_INDIVIDUAL = 1
} OH_AudioStream_VolumeMode;

/**
 * @brief 定义音频时延类型。
 *
 * @since 23
 */
typedef enum {
    /**
     * 获取包含软件与硬件在内的整体音频处理时延。
     * @since 23
     */
    AUDIOSTREAM_LATENCY_TYPE_ALL = 0,

    /**
     * 获取软件部分的时延，包括软件侧音效处理。
     * @since 23
     */
    AUDIOSTREAM_LATENCY_TYPE_SOFTWARE = 1,

    /**
     * 获取硬件部分的时延，包括硬件抽象层（HAL） 、驱动与硬件侧音效处理。
     * @since 23
     */
    AUDIOSTREAM_LATENCY_TYPE_HARDWARE = 2
} OH_AudioStream_LatencyType;

/**
 * @brief 表示内录（录制设备内部应用的声音）的过滤类型，每种过滤类型可录制不同的播放流类型。
 * 该API最初仅对特定系统应用可用，从API版本26.0.0开始，支持任意应用使用。
 *
 * @since 23
 */
typedef enum {
    /**
     * 默认模式。录制大部分音频流，但不包括提示音流和隐私流。
     * @since 23
     */
    AUDIOSTREAM_PLAYBACKCAPTURE_MODE_DEFAULT = 0x0,
    /**
     * 媒体模式。获取媒体、语音消息和未知流。
     * @since 23
     */
    AUDIOSTREAM_PLAYBACKCAPTURE_MODE_MEDIA = 0x1,
    /**
     * 排除自身模式。获取除应用自身播放的音频以外的流。
     * @since 23
     */
    AUDIOSTREAM_PLAYBACKCAPTURE_MODE_EXCLUDING_SELF = 0x8000
} OH_AudioStream_PlaybackCaptureMode;

/**
 * @brief 定义内录的启动状态，该状态在调用{@link OH_AudioCapturer_RequestPlaybackCaptureStart}函数后异步返回。
 * 该API最初仅对特定系统应用可用，从API版本26.0.0开始，支持任意应用使用。
 *
 * @since 23
 */
typedef enum {
    /**
     * 启动内录成功。
     * @since 23
     */
    AUDIOSTREAM_PLAYBACKCAPTURE_START_STATE_SUCCESS = 0,

    /**
     * 启动内录失败。原因是请求焦点（根据流类型做优先级的选择）过程中被打断，或发生系统内部错误。
     * @since 23
     */
    AUDIOSTREAM_PLAYBACKCAPTURE_START_STATE_FAILED = 1,

    /**
     * 用户未授权，启动内录失败。
     * @since 23
     */
    AUDIOSTREAM_PLAYBACKCAPTURE_START_STATE_NOT_AUTHORIZED = 2
} OH_AudioStream_PlaybackCaptureStartState;

#ifdef __cplusplus
}
#endif
#endif // NATIVE_AUDIOSTREAM_BASE_H
/** @} */