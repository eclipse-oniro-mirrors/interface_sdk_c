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
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 10
 * @version 1.0
 */

/**
 * @file native_audiostream_base.h
 *
 * @brief 声明OHAudio基础的数据结构。
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
     * @error
     * 操作成功
     * @since 10
     */
    AUDIOSTREAM_SUCCESS = 0,

    /**
     * @error
     * 入参错误。
     * @since 10
     */
    AUDIOSTREAM_ERROR_INVALID_PARAM = 1,

    /**
     * @error
     * 非法状态。
     * @since 10
     */
    AUDIOSTREAM_ERROR_ILLEGAL_STATE = 2,

    /**
     * @error
     * 系统通用错误。
     * @since 10
     */
    AUDIOSTREAM_ERROR_SYSTEM = 3,

    /**
     * @error
     * 不支持的音频格式，如不支持的编码类型、采样格式等。
     * @since 19
     */
    AUDIOSTREAM_ERROR_UNSUPPORTED_FORMAT = 4,

    /**
     * @error
     * 不支持的音频流功能，包括功能和配置。
     *
     * @since 26.0.0
     */
    AUDIOSTREAM_ERROR_UNSUPPORTED_ABILITY = 6800104,

    /**
     * @error
     * 音频服务器进程死掉。
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
     * 该类型代表音频流是输出流。
     * @since 10
     */
    AUDIOSTREAM_TYPE_RENDERER = 1,

    /**
     * 该类型代表音频流是输入流。
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
    AUDIOSTREAM_ENCODING_TYPE_E_AC3 = 2
} OH_AudioStream_EncodingType;

/**
 * @brief 定义音频流信息结构体，用于描述基本音频格式。
 *
 * @since 19
 */
typedef struct OH_AudioStreamInfo {
    /**
     * @brief 音频流采样率。单位为赫兹（Hz）。
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
     * @brief 音频流编码类型。
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
 * @brief 定义音频流使用场景。
 * <br>通常用来描述音频输出流的使用场景。
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
     * 游戏。
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
     * 该模式代表一个普通时延的音频流。
     * @since 10
     */
    AUDIOSTREAM_LATENCY_MODE_NORMAL = 0,
    /**
     * 该模式代表一个低时延的音频流。
     * @since 10
     */
    AUDIOSTREAM_LATENCY_MODE_FAST = 1
} OH_AudioStream_LatencyMode;

/**
 * @brief 定义音频流direct通路播放模式。
 *
 * @since 19
 */
typedef enum {
    /**
     * 该模式代表不支持direct通路播放。
     * @since 19
     */
    AUDIOSTREAM_DIRECT_PLAYBACK_NOT_SUPPORTED = 0,
    /**
     * 该模式代表支持不解码的direct通路播放。
     * @since 19
     */
    AUDIOSTREAM_DIRECT_PLAYBACK_BITSTREAM_SUPPORTED = 1,
    /**
     * 该模式代表支持PCM编码的direct通路播放。
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
 * @brief 定义音频中断类型。
 * <br>当用户监听到音频中断时，将获取此信息。
 * <br>此类型表示本次音频打断的操作是否已由系统强制执行，具体操作信息（如音频暂停、停止等）可通过{@link OH_AudioInterrupt_Hint}获取。
 *
 * @since 10
 */
typedef enum {
    /**
     * 强制打断类型，即具体操作已由系统强制执行。
     * @since 10
     */
    AUDIOSTREAM_INTERRUPT_FORCE = 0,
    /**
     * 共享打断类型，即系统不执行具体操作，通过{@link OH_AudioInterrupt_Hint}提示并建议应用操作，应用可自行决策下一步处理方式。
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
     * 提示音频恢复，应用可主动触发开始渲染或开始采集的相关操作。<br> 此操作无法由系统强制执行，其对应的{@link OH_AudioInterrupt_ForceType}
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
 * @brief 定义音频流使用场景。
 * <br>通常用来描述音频输入流的使用场景。
 *
 * @since 10
 */
typedef enum {
    /**
     * 不合法状态。
     * @since 10
     */
    AUDIOSTREAM_SOURCE_TYPE_INVALID = -1,
    /**
     * 录音。
     * @since 10
     */
    AUDIOSTREAM_SOURCE_TYPE_MIC = 0,
    /**
     * 语音识别。
     * @since 10
     */
    AUDIOSTREAM_SOURCE_TYPE_VOICE_RECOGNITION = 1,
    /**
     * 播放录音。<br>**废弃版本：** 12<br>**替代接口：** {@link OH_AVScreenCapture}
     * @deprecated since 12
     * @useinstead OH_AVScreenCapture in native interface.
     * @since 10
     */
    AUDIOSTREAM_SOURCE_TYPE_PLAYBACK_CAPTURE = 2,
    /**
     * 通话。
     * @since 10
     */
    AUDIOSTREAM_SOURCE_TYPE_VOICE_COMMUNICATION = 7,
    /**
     * 语音消息。
     * @since 12
     */
    AUDIOSTREAM_SOURCE_TYPE_VOICE_MESSAGE = 10,
    /**
     * 录像。
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
     * 蜂窝通话下行录音（通话中对方声音）。使用此输入流的音频采集器应在蜂窝通话开始后创建。使用{@link OH_AudioStreamBuilder_GenerateCapturer}创建采集流时需要ohos.
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
     * 共享模式。
     */
    AUDIOSTREAM_INTERRUPT_MODE_SHARE = 0,
    /**
     * 独立模式。
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
     */
    AUDIOSTREAM_FASTSTATUS_FAST = 1
} OH_AudioStream_FastStatus;

/**
 * @brief 声明音频流的构造器。构造器实例用于设置音频流属性和创建音频流。
 *
 * @since 10
 */
typedef struct OH_AudioStreamBuilderStruct OH_AudioStreamBuilder;

/**
 * @brief 声明输出音频渲染器。输出音频渲染器的实例被用来播放音频数据。
 *
 * @since 10
 */
typedef struct OH_AudioRendererStruct OH_AudioRenderer;

/**
 * @brief 声明音频采集器结构体。音频采集器的实例用于获取输入音频（录音）数据。
 *
 * @since 10
 */
typedef struct OH_AudioCapturerStruct OH_AudioCapturer;

/**
 * @brief 声明输出音频流的回调函数指针。<br>为了避免不可预期的行为，在设置音频回调函数时，请确保该结构体的每一个成员变量都被自定义的回调函数或空指针初始化。<br>可参考
 * {@link 推荐使用OHAudio开发音频播放功能(C/C++)}。
 *
 * @deprecated since 20
 * @useinstead Use the callback type: OH_AudioRenderer_OnWriteDataCallback, OH_AudioRenderer_OutputDeviceChangeCallback,
 * OH_AudioRenderer_OnInterruptEvent, OH_AudioRenderer_OnErrorCallback separately.
 * @since 10
 */
typedef struct OH_AudioRenderer_Callbacks_Struct {
    /**
     * This function pointer will point to the callback function that
     * is used to write audio data
     *
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
     * This function pointer will point to the callback function that
     * is used to handle audio renderer stream events.
     *
     * @deprecated since 20
     * @useinstead OH_AudioRenderer_OutputDeviceChangeCallback.
     * @since 10
     */
    int32_t (*OH_AudioRenderer_OnStreamEvent)(
            OH_AudioRenderer* renderer,
            void* userData,
            OH_AudioStream_Event event);

    /**
     * This function pointer will point to the callback function that
     * is used to handle audio interrupt events.
     *
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
     * This function pointer will point to the callback function that
     * is used to handle audio error result.
     *
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
 * @brief 声明用于音频采集器的回调函数指针。<br>为了避免不可预期的行为，在设置音频回调函数时，请确保该结构体的每一个成员变量都
 * 被自定义的回调方法或空指针初始化。可参考{@link 推荐使用OHAudio开发音频录制功能(C/C++)}。
 *
 * @deprecated since 20
 * @useinstead Use the callback type: OH_AudioCapturer_OnReadDataCallback, OH_AudioCapturer_OnDeviceChangeCallback,
 *     OH_AudioCapturer_OnInterruptCallback and OH_AudioCapturer_OnErrorCallback separately.
 * @since 10
 */
typedef struct OH_AudioCapturer_Callbacks_Struct {
    /**
     * This function pointer will point to the callback function that
     * is used to read audio data.
     *
     * @deprecated since 20
     * @useinstead OH_AudioCapturer_OnReadDataCallback
     * @since 10
     */
    int32_t (*OH_AudioCapturer_OnReadData)(
        OH_AudioCapturer* capturer,
        void* userData,
        void* buffer,
        int32_t length);

    /**
     * This function pointer will point to the callback function that
     * is used to handle audio capturer stream events.
     *
     * @deprecated since 20
     * @useinstead OH_AudioCapturer_OnDeviceChangeCallback
     * @since 10
     */
    int32_t (*OH_AudioCapturer_OnStreamEvent)(
        OH_AudioCapturer* capturer,
        void* userData,
        OH_AudioStream_Event event);

    /**
     * This function pointer will point to the callback function that
     * is used to handle audio interrupt events.
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
     * This function pointer will point to the callback function that
     * is used to handle audio error result.
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
    /* Unknown. */
    REASON_UNKNOWN = 0,
    /* New Device available. */
    REASON_NEW_DEVICE_AVAILABLE = 1,
    REASON_OLD_DEVICE_UNAVAILABLE = 2,
    /* Device is overrode by user or system. */
    REASON_OVERRODE = 3,
    /**
     * @brief 音频会话激活触发的设备切换。
     *
     * @since 20
     */
    REASON_SESSION_ACTIVATED = 4,
    /**
     * @brief 更高优先级的音频流出现导致的系统设备切换。
     *
     * @since 20
     */
    REASON_STREAM_PRIORITY_CHANGED = 5
} OH_AudioStream_DeviceChangeReason;

/**
 * @brief 输出音频流设备变更的回调函数。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @param reason 流设备变更原因。
 * @since 11
 */
typedef void (*OH_AudioRenderer_OutputDeviceChangeCallback)(OH_AudioRenderer* renderer, void* userData,
    OH_AudioStream_DeviceChangeReason reason);

/**
 * @brief 到达标记位置时回调。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param samplePos 设置目标标记位置。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @since 12
 */
typedef void (*OH_AudioRenderer_OnMarkReachedCallback)(OH_AudioRenderer* renderer, uint32_t samplePos, void* userData);

/**
 * @brief 该函数指针将指向用于同时写入音频数据和元数据的回调函数。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @param audioData 指向用户写入的音频数据的指针。
 * @param audioDataSize 用户写入的音频数据的数据长度，以字节为单位。
 * @param metadata 指向用户写入的元数据的指针。
 * @param metadataSize 用户写入的元数据的数据长度，以字节为单位。
 * @return 用户返回的回调函数的错误码。
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
    /** 表示音频流可以被其他应用录制或屏幕投射，不包含隐私类型的流。
     * @since 12
     */
    AUDIO_STREAM_PRIVACY_TYPE_PUBLIC = 0,
    /** 表示音频流不可以被其他应用录制或屏幕投射。
     * @since 12
     */
    AUDIO_STREAM_PRIVACY_TYPE_PRIVATE = 1,
    /**
     * 表示音频流可以被其他应用录制或屏幕投射，包含隐私类型的流。<br>     例如，在PRIVACY_TYPE_PUBLIC策略下，{@link AUDIOSTREAM_USAGE_VOICE_COMMUNICATION}
     * 类型音频流不会被其他应用录制或屏幕投射。然而，在PRIVACY_TYPE_SHARED策略下，这些音频流将会允许被其他应用录制或屏幕投射。
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
 * @brief 该函数指针将指向用于写入音频数据的回调函数。
 * <br>回调函数仅用来写入音频数据，请勿在回调函数中调用AudioRenderer相关接口。
 * <br>该函数的返回结果表示填充到缓冲区的数据是否有效。如果结果无效，用户填写的数据将不被播放。
 * <br>回调函数结束后，音频服务会把audioData指针数据放入队列里等待播放，因此请勿在回调外再次更改audioData指向的数据，且务必保证往audioData填满audioDataSize长度的待播放数据，
 * 否则会导致音频服务播放杂音。
 * <br>参数audioDataSize可以通过{@link OH_AudioStreamBuilder_SetFrameSizeInCallback}设置。
 * <br>为避免音频播放启动和停止时数据不连续可能出现的杂音，系统通常会在启动和停止时对音频数据做20ms以内的淡入淡出处理。
 *
 * @param renderer 指向{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频流实例。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @param audioData 指向用户写入的音频数据的指针。
 * @param audioDataSize 用户写入的音频数据的数据长度，以字节为单位。
 * @return AUDIO_DATA_CALLBACK_RESULT_INVALID：音频数据回调结果无效，音频数据不播放。
 *     <br>AUDIO_DATA_CALLBACK_RESULT_VALID：音频数据回调结果有效，音频数据将被播放。
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
     * 系统级音量（默认模式）。
     * @since 19
     */
    AUDIOSTREAM_VOLUMEMODE_SYSTEM_GLOBAL = 0,

    /**
     * 应用级音量。<br> 设置为该模式后可以通过提供的接口设置、查询应用音量。
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
 * @brief 表示内录（录制设备内部应用的声音）的过滤类型，每种过滤类型可录制不同的播放流类型。该API暂不对外支持。
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
     * 媒体模式。获取媒体、语音消息和未知流等。
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
 * @brief 定义内录的启动状态，该状态在调用{@link OH_AudioCapturer_RequestPlaybackCaptureStart}函数后异步返回。该API暂不对外支持。
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