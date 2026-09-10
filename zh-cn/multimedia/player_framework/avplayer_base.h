/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @addtogroup AVPlayer
 * @{
 *
 * @brief 提供媒体源的播放能力接口。
 *
 * @Syscap SystemCapability.Multimedia.Media.AVPlayer
 * @since 11
 */
/**
 * @file avplayer_base.h
 *
 * @brief 定义AVPlayer的结构体和枚举。
 * 
 * @kit MediaKit
 * @include <multimedia/player_framework/avplayer_base.h>
 * @library libavplayer.so
 * @since 11
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVPLAYER_BASH_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVPLAYER_BASH_H

#include <stdint.h>

#include "native_avformat.h"
#include "native_avbuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AVPlayerCallback AVPlayerCallback;

/**
 * @brief 声明OH_AVPlayer结构体类型。
 * 
 * @since 11
 */
typedef struct OH_AVPlayer OH_AVPlayer;

/**
 * @brief SEI（Supplemental Enhancement Information）消息数组的结构体类型。用于存储和管理SEI消息，支持批量获取和处理视频流中的SEI消息，适用于需要解析视频补充增强信息的场景。
 * 
 * @since 23
 */
typedef struct OH_AVSeiMessageArray OH_AVSeiMessageArray;

/**
 * @brief 音视频播放策略的结构体类型，用于配置播放器在播放音视频内容时的策略参数，适用于需要精细控制播放行为的场景。若未设置该策略参数，播放器将采用默认播放策略。
 * 
 * @since 23
 */
typedef struct OH_AVPlaybackStrategy OH_AVPlaybackStrategy;

/**
 * @brief 播放状态。
 * 
 * @since 11
 */
typedef enum AVPlayerState {
    /* 空闲 */
    AV_IDLE = 0,
    /* 初始化 */
    AV_INITIALIZED = 1,
    /* 准备 */
    AV_PREPARED = 2,
    /* 播放 */
    AV_PLAYING = 3,
    /* 暂停 */
    AV_PAUSED = 4,
    /* 停止 */
    AV_STOPPED = 5,
    /* 结束 */
    AV_COMPLETED = 6,
    /* 释放 */
    AV_RELEASED = 7,
    /* 错误 */
    AV_ERROR = 8,
} AVPlayerState;

/**
 * @brief 跳转模式。
 * 
 * @since 11
 */
typedef enum AVPlayerSeekMode {
    /* 同步到时间点之后的关键帧。*/
    AV_SEEK_NEXT_SYNC = 0,
    /* 同步到时间点之前的关键帧。*/
    AV_SEEK_PREVIOUS_SYNC = 1,
    /**
     * @brief 同步到距离指定时间点最近的帧。
     * 
     * @since 12
     */
    AV_SEEK_CLOSEST = 2,
    /**
     * 连续拖动模式下的跳转（seek）。该模式可提供更流畅的拖拽体验，但要求设备支持对当前流执行连续跳转。在调用连续跳转前，请先检查是否支持，参见{@link OH_AVPlayer_IsSeekContinuousSupported}
     * 。
     * **起始版本：** 23
     */
    AV_SEEK_CONTINUOUS = 3,
} AVPlayerSeekMode;

/**
 * @brief 播放速度。
 * 
 * @since 11
 */
typedef enum AVPlaybackSpeed {
    /* 0.75倍速播放。 */
    AV_SPEED_FORWARD_0_75_X = 0,
    /* 正常播放。 */
    AV_SPEED_FORWARD_1_00_X = 1,
    /* 1.25倍速播放。 */
    AV_SPEED_FORWARD_1_25_X = 2,
    /* 1.75倍速播放。 */
    AV_SPEED_FORWARD_1_75_X = 3,
    /* 2.0倍速播放。 */
    AV_SPEED_FORWARD_2_00_X = 4,
    /**
     * @brief 0.5倍速播放。
     * 
     * @since 12
     */
    AV_SPEED_FORWARD_0_50_X = 5,
    /**
     * @brief 1.5倍速播放。
     * 
     * @since 12
     */
    AV_SPEED_FORWARD_1_50_X = 6,
    /**
     * @brief 3.0倍速播放。
     * 
     * @since 13
    */
    AV_SPEED_FORWARD_3_00_X = 7,
    /**
     * @brief 0.25倍速播放。
     * 
     * @since 13
    */
    AV_SPEED_FORWARD_0_25_X = 8,
    /**
     * @brief 0.125倍速播放。
     * 
     * @since 13
    */
    AV_SPEED_FORWARD_0_125_X = 9,
} AVPlaybackSpeed;

/**
 * @brief OnInfo类型。
 * 可用于OH_AVPlayerOnInfoCallback和OH_AVPlayerOnInfo(已废弃)，用于表示收到的播放器信息类型。
 * 从API version 12开始，推荐用户使用{@link OH_AVPlayerOnInfoCallback}。不同的OnInfo类型，可获取到不同信息（infoBody），infoBody中包含key-value关系表，
 * 详见下述枚举值表。
 * 使用API version 11版本的开发者，需要使用旧接口。针对已废弃接口OH_AVPlayerOnInfo中使用的对应关系，可直接参考{@link OH_AVPlayerOnInfo}的API说明。
 * 
 * @since 11
 */
typedef enum AVPlayerOnInfoType {
    /* 跳转到对应播放位置时返回消息。 */
    AV_INFO_TYPE_SEEKDONE = 0,
    /* 播放倍速设置完成时返回消息。 */
    AV_INFO_TYPE_SPEEDDONE = 1,
    /* 比特率设置完成时返回消息。 */
    AV_INFO_TYPE_BITRATEDONE = 2,
    /* 播放完成时返回消息。 */
    AV_INFO_TYPE_EOS = 3,
    /* 状态改变时返回消息。 */
    AV_INFO_TYPE_STATE_CHANGE = 4,
    /* 返回当前播放位置。 */
    AV_INFO_TYPE_POSITION_UPDATE = 5,
    /* 视频开始渲染时返回消息。 */
    AV_INFO_TYPE_MESSAGE = 6,
    /* 音量改变时返回消息。 */
    AV_INFO_TYPE_VOLUME_CHANGE = 7,
    /*  首次获取视频大小或视频大小更新时返回消息。 */
    AV_INFO_TYPE_RESOLUTION_CHANGE = 8,
    /* 返回多队列缓冲时间。 */
    AV_INFO_TYPE_BUFFERING_UPDATE = 9,
    /* 上报HLS视频比特率列表消息。 */
    AV_INFO_TYPE_BITRATE_COLLECT = 10,
    /* 音频焦点改变时返回消息。 */
    AV_INFO_TYPE_INTERRUPT_EVENT = 11,
    /* 返回播放时长。 */
    AV_INFO_TYPE_DURATION_UPDATE = 12,
    /* 播放为直播流时返回消息。 */
    AV_INFO_TYPE_IS_LIVE_STREAM = 13,
    /* 轨道改变时返回消息。 */
    AV_INFO_TYPE_TRACKCHANGE = 14,
    /* 轨道更新时返回消息。 */
    AV_INFO_TYPE_TRACK_INFO_UPDATE = 15,
    /* 字幕信息更新时返回消息。 */
    AV_INFO_TYPE_SUBTITLE_UPDATE = 16,
    /**
     * 音频输出设备改变时返回消息。<br> key为OH_PLAYER_AUDIO_DEVICE_CHANGE_REASON：取值类型int32_t。系统通过int32_t传递value，应用需通过int32_t获取。
     */
    AV_INFO_TYPE_AUDIO_OUTPUT_DEVICE_CHANGE = 17,

    /**
     * @brief 播放速率成功应用时返回消息。
     *  key为OH_PLAYER_PLAYBACK_RATE：取值类型float。系统通过float传递value，应用通过float获取。
     * 
     * @since 20
     */
    AV_INFO_TYPE_PLAYBACK_RATE_DONE = 18,
  
    /**
     * @brief 超分辨率变化时返回消息。
     * 
     * @since 23
     */
    AV_INFO_TYPE_SUPER_RESOLUTION_CHANGED = 19,
} AVPlayerOnInfoType;

/**
 * @brief 播放缓冲消息类型定义。
 * 
 * @since 12
 */
typedef enum AVPlayerBufferingType {
    /**
     * 缓冲开始消息。
     */
    AVPLAYER_BUFFERING_START = 1,

    /**
     * 缓冲结束消息。
     */
    AVPLAYER_BUFFERING_END,

    /**
     * 缓冲执行进度百分比，取值范围：整数，[0, 100]。
     */
    AVPLAYER_BUFFERING_PERCENT,

    /**
     * 缓冲数据可播放时长，单位：毫秒。
     */
    AVPLAYER_BUFFERING_CACHED_DURATION,
} AVPlayerBufferingType;

/**
 * @brief 枚举轨道切换模式。
 * 
 * @since 23
 */
typedef enum AVPlayerTrackSwitchMode {
    /**
     * 平滑切换轨道。
     */
    AV_TRACK_SWITCH_MODE_SMOOTH = 0,
    /**
     * 按片段切换轨道。
     */
    AV_TRACK_SWITCH_MODE_SEGMENT = 1,
    /**
     * 切换到最接近的轨道。
     */
    AV_TRACK_SWITCH_MODE_CLOSEST = 2,
} AVPlayerTrackSwitchMode;

/**
 * @brief 视频输出的结果。
 * @since 26.0.0
 */
typedef enum OH_VideoOutputResult {
    /**
     * @brief 输出一个已解码的视频帧。
     * @since 26.0.0
     */
    OH_VIDEO_OUTPUT_OK = 0,
    /**
     * @brief 无帧可渲染。
     * @since 26.0.0
     */
    OH_VIDEO_OUTPUT_NO_IMAGE = 1,
} OH_VideoOutputResult;

/**
 * @brief 获取播放状态的关键字，对应值类型是int32_t。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_STATE;

/**
 * @brief 获取播放状态变更原因的关键字，对应值类型是int32_t。
 * 1：用户操作触发；2：系统变更触发。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_STATE_CHANGE_REASON;

/**
 * @brief 获取音量的关键字，对应值类型是float，取值范围[0.0，1.0]。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_VOLUME;

/**
 * @brief 获取比特率列表的关键字，对应值类型是uint8_t字节数组。通过该关键字获取信息时：
 * 需要先使用uint8_t类型指针变量保存比特率列表，使用size_t类型变量保存字节数组长度。
 * 然后分配若干个uint32_t类型的存储空间，接收将uint8_t字节数组转换为uint32_t类型比特率整数值，单位为bps。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_BITRATE_ARRAY;

/**
 * @brief 获取音频打断类型的关键字，对应值类型是int32_t。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_AUDIO_INTERRUPT_TYPE;

/**
 * @brief 获取音频打断FORCE类型的关键字，对应值类型是int32_t。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_AUDIO_INTERRUPT_FORCE;

/**
 * @brief 获取音频打断HINT类型的关键字，对应值类型是int32_t。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_AUDIO_INTERRUPT_HINT;

/**
 * @brief 获取音频设备变更原因的关键字，对应值类型是int32_t。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_AUDIO_DEVICE_CHANGE_REASON;

/**
 * @brief 获取缓冲更新消息类型的关键字，对应值类型是{@link AVPlayerBufferingType}。
 * 通过该关键字获取信息时，需要先使用int32_t类型变量保存结果，再转换为AVPlayerBufferingType类型。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_BUFFERING_TYPE;

/**
 * @brief 获取缓冲更新消息数值的关键字，对应值类型是int32_t，参见{@link AVPlayerBufferingType}。
 * 当缓冲更新消息类型是AVPLAYER_BUFFERING_PERCENT、AVPLAYER_BUFFERING_CACHED_DURATION时有效。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_BUFFERING_VALUE;

/**
 * @brief 获取Seek后播放进度的关键字，对应值类型是int32_t。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_SEEK_POSITION;

/**
 * @brief 获取播放倍速信息的关键字, 对应值类型是{@link AVPlaybackSpeed}。
 * 通过该关键字获取信息时，需要先使用int32_t类型变量保存结果，再转换为AVPlaybackSpeed类型。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_PLAYBACK_SPEED;

/**
 * @brief 获取比特率列表的关键字，对应值类型是uint8_t字节数组。通过该关键字获取信息时：
 * 需要先使用uint8_t类型指针变量保存比特率列表，使用size_t类型变量保存字节数组长度。
 * 然后分配若干个uint32_t类型的存储空间，接收将uint8_t字节数组转换为uint32_t类型比特率整数值。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_BITRATE;

/**
 * @brief 获取播放进度信息的关键字，对应值类型是int32_t。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_CURRENT_POSITION;

/**
 * @brief 获取媒体资源时长信息的关键字，对应值类型是int64_t。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_DURATION;

/**
 * @brief 获取视频宽度信息的关键字，对应值类型是int32_t。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_VIDEO_WIDTH;

/**
 * @brief 获取视频高度信息的关键字，对应值类型是int32_t。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_VIDEO_HEIGHT;

/**
 * @brief 获取播放器消息信息的关键字，对应值类型是int32_t。
 * 1：视频帧开始渲染。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_MESSAGE_TYPE;

/**
 * @brief 获取媒体资源是否为直播类型信息的关键字，对应值类型是int32_t。
 * 1：直播。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_IS_LIVE_STREAM;

/**
 * SEI消息中表示负载类型的关键字。
 * @since 23
 */
extern const char* OH_PLAYER_SEI_PAYLOAD_TYPE;

/**
 * SEI消息中表示负载内容的关键字。
 * @since 23
 */
extern const char* OH_PLAYER_SEI_PAYLOAD_CONTENT;

/**
 * @brief 超分辨率功能启用状态关键字，值类型为int32_t。值为1表示已启用，0表示未启用；用于超分辨率状态变化时的信息回调。
 * 
 * @since 23
 */
extern const char* OH_PLAYER_SUPER_RESOLUTION_ENABLE_STATE;

/**
 * @brief 轨道切换信息中表示轨道索引的关键字，值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_PLAYER_TRACH_CHANGE_INFO_TRACK_INDEX;

/**
 * @brief 轨道切换信息中表示轨道是否被选中的标志关键字，值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_PLAYER_TRACH_CHANGE_INFO_TRACK_SELECTED;

/**
 * @brief 字幕更新信息中表示持续时间的关键字，值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_PLAYER_SUBTITLE_UPDATE_INFO_DURATION;

/**
 * @brief 字幕更新信息中表示起始时间的关键字，值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_PLAYER_SUBTITLE_UPDATE_INFO_START_TIME;

/**
 * @brief 字幕更新信息中表示字幕文本内容的关键字，值类型为字符串（string）。
 * 
 * @since 23
 */
extern const char* OH_PLAYER_SUBTITLE_UPDATE_INFO_TEXT;

/**
 * @brief 获取有效播放速率的关键字，对应值类型是浮点数。
 * 
 * @since 20
 */
extern const char* OH_PLAYER_PLAYBACK_RATE;
 
/**
 * @brief 获取媒体资源是否包含视频轨信息的关键字，对应值类型int32_t。
 * 1：包含视频轨，0：不包含视频轨。
 * 
 * @since 22
 */
extern const char* OH_PLAYER_MD_KEY_HAS_VIDEO;
 
/**
 * @brief 获取媒体资源是否包含音频轨信息的关键字，对应值类型int32_t。
 * 1：包含音频轨，0：不包含音频轨。
 * 
 * @since 22
 */
extern const char* OH_PLAYER_MD_KEY_HAS_AUDIO;
 
/**
 * @brief 获取媒体资源是否包含字幕轨信息的关键字，对应值类型int32_t。
 * 1：包含字幕轨，0：不包含字幕轨。
 * 
 * @since 22
 */
extern const char* OH_PLAYER_MD_KEY_HAS_SUBTITLE;
 
/**
 * @brief 获取媒体资源轨道下标信息的关键字，对应值类型int32_t。
 * 
 * @since 22
 */
extern const char* OH_PLAYER_MD_KEY_TRACK_INDEX;

/**
 * @brief 收到播放器消息时调用。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param type 信息类型。类型为{@link AVPlayerOnInfoType}，与extra的对应关系可见方法描述。
 * @param extra 其他信息，如播放文件的开始时间位置。
 * 信息类型（type）：对应的extra描述
 * AV_INFO_TYPE_SEEKDONE	跳转到对应播放位置时返回消息，extra表示跳转到的位置。
 * AV_INFO_TYPE_SPEEDDONE	播放倍速设置完成时返回消息，extra表示播放倍速信息，具体请参考AVPlaybackSpeed。
 * AV_INFO_TYPE_BITRATEDONE	比特率设置完成时返回消息，extra表示比特率信息。
 * AV_INFO_TYPE_EOS	播放完成时返回消息。
 * AV_INFO_TYPE_STATE_CHANGE	状态改变时返回消息，extra表示当前播放状态，具体请参见AVPlayerState。
 * AV_INFO_TYPE_POSITION_UPDATE	返回当前播放位置，extra表示当前位置。
 * AV_INFO_TYPE_MESSAGE	视频开始渲染时返回消息，extra表示视频首帧渲染。
 * AV_INFO_TYPE_VOLUME_CHANGE	音量改变时返回消息，此场景下extra未定义。
 * AV_INFO_TYPE_RESOLUTION_CHANGE	首次获取视频大小或视频大小更新时返回消息，此场景下extra未定义。
 * AV_INFO_TYPE_BUFFERING_UPDATE	返回缓冲更新消息。此场景下extra表示缓冲相关数据，建议使用OH_AVPlayerOnInfoCallback获取详细的缓冲信息。
 * AV_INFO_TYPE_BITRATE_COLLECT	上报HLS视频比特率列表消息。上报时每个比特率已经转化为uint8_t字节数组，使用者需要将uint8_t字节数组强制转换为uint32_t整型数组。
 * AV_INFO_TYPE_INTERRUPT_EVENT	音频焦点改变时返回消息，extra表示音频打断提示，具体请参见OH_AudioInterrupt_Hint，应用可决定是否根据打断提示作进一步处理。
 * AV_INFO_TYPE_DURATION_UPDATE	返回播放时长，extra表示视频时长。
 * AV_INFO_TYPE_IS_LIVE_STREAM	播放为直播流时返回消息，extra表示是否为直播流，0表示非直播流，1表示直播流。
 * AV_INFO_TYPE_TRACKCHANGE	轨道改变时返回消息，此场景extra未定义。
 * AV_INFO_TYPE_TRACK_INFO_UPDATE	轨道更新时返回消息，此场景下extra参数无特定含义。
 * AV_INFO_TYPE_SUBTITLE_UPDATE	字幕信息更新时返回消息，此场景extra未定义。
 * AV_INFO_TYPE_AUDIO_OUTPUT_DEVICE_CHANGE	音频输出设备改变时返回消息，extra表示设备改变原因，具体请参见OH_AudioStream_DeviceChangeReason。
 * @since 11
 * @deprecated since 12
 * @useinstead {@link OH_AVPlayerOnInfoCallback}
 */
typedef void (*OH_AVPlayerOnInfo)(OH_AVPlayer *player, AVPlayerOnInfoType type, int32_t extra);

/**
 * @brief 收到播放器消息时被调用。如果应用成功设置该回调，则不会回调OH_AVPlayerOnInfo函数。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param type 信息类型。具体请参见{@link AVPlayerOnInfoType}。
 * @param infoBody 指向携带具体消息的指针，仅在该回调方法内有效。
 * @param userData 指向应用调用者设置该回调函数时提供的实例的指针。
 * @since 12
 */
typedef void (*OH_AVPlayerOnInfoCallback)(OH_AVPlayer *player, AVPlayerOnInfoType type, OH_AVFormat* infoBody,
    void *userData);

/**
 * @brief 在API version 11以上的版本发生错误时调用。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param errorCode 错误码。
 * AV_ERR_NO_MEMORY：无内存，取值为1。可能原因：系统内存不足。处理方法：释放不必要的资源后重试。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不允许，取值为2。可能原因：当前状态下不允许执行该操作。处理方法：检查当前状态，在合适的状态下执行操作。
 * AV_ERR_INVALID_VAL：无效值，取值为3。可能原因：传入的参数值无效。处理方法：检查参数值是否在有效范围内。
 * AV_ERR_IO：IO错误，取值为4。可能原因：文件读写失败或网络IO异常。处理方法：检查文件是否存在或网络连接是否正常。
 * AV_ERR_TIMEOUT：超时错误，取值为5。可能原因：操作超时。处理方法：检查网络状况或增大超时时间。
 * AV_ERR_UNKNOWN：未知错误，取值为6。可能原因：发生未知错误。处理方法：查看日志或联系技术支持。
 * AV_ERR_SERVICE_DIED：服务死亡，取值为7。可能原因：媒体服务异常终止。处理方法：重新创建播放器实例。
 * AV_ERR_INVALID_STATE：当前状态不支持此操作，取值为8。可能原因：在错误的状态下调用了该方法。处理方法：检查播放器当前状态是否支持该操作。
 * AV_ERR_UNSUPPORT：未支持的接口，取值为9。可能原因：调用了不支持的接口。处理方法：检查API版本支持情况。
 * AV_ERR_EXTEND_START：扩展错误码初始值，取值为100。可能原因：扩展错误。处理方法：根据具体错误码进行处理。
 * @param errorMsg 错误消息。由播放器返回的错误描述信息，具体内容取决于错误类型，可能为NULL或空字符串。
 * @since 11
 * @deprecated since 12
 * @useinstead {@link OH_AVPlayerOnErrorCallback}
 */
typedef void (*OH_AVPlayerOnError)(OH_AVPlayer *player, int32_t errorCode, const char *errorMsg);

/**
 * @brief 发生错误时被调用。如果应用成功设置该回调，则不会调用OH_AVPlayerOnError函数。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param errorCode 错误码。
 * AV_ERR_NO_MEMORY：无内存，取值为1。可能原因：系统内存不足。处理方法：释放不必要的资源后重试。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不允许，取值为2。可能原因：当前状态下不允许执行该操作。处理方法：检查当前状态，在合适的状态下执行操作。
 * AV_ERR_INVALID_VAL：无效值，取值为3。可能原因：传入的参数值无效。处理方法：检查参数值是否在有效范围内。
 * AV_ERR_IO：IO错误。API version 12-13取值为4；API version 14及以后，对应错误细化为错误码5411001~5411011。可能原因：文件读写失败或网络IO异常。处理方法：检查文件是否存在或网络连接是否正常。
 * AV_ERR_TIMEOUT：超时错误，取值为5。可能原因：操作超时。处理方法：检查网络状况或增大超时时间。
 * AV_ERR_UNKNOWN：未知错误，取值为6。可能原因：发生未知错误。处理方法：查看日志或联系技术支持。
 * AV_ERR_SERVICE_DIED：服务死亡，取值为7。可能原因：媒体服务异常终止。处理方法：重新创建播放器实例。
 * AV_ERR_INVALID_STATE：当前状态不支持此操作，取值为8。可能原因：在错误的状态下调用了该方法。处理方法：检查播放器当前状态是否支持该操作。
 * AV_ERR_UNSUPPORT：未支持的接口，取值为9。可能原因：调用了不支持的接口。处理方法：检查API版本支持情况。
 * AV_ERR_EXTEND_START：扩展错误码初始值，取值为100。可能原因：扩展错误。处理方法：根据具体错误码进行处理。
 * @param errorMsg 错误消息，只在回调函数中有效。
 * @param userData 指向用户特定数据的指针。
 * @since 12
 */
typedef void (*OH_AVPlayerOnErrorCallback)(OH_AVPlayer *player, int32_t errorCode, const char *errorMsg,
    void *userData);

/**
 * @brief AVPlayerCallback（AVPlayer回调）是AVPlayer（音视频播放器）的回调管理结构体，包含了播放过程信息OH_AVPlayerOnInfo和错误信息OH_AVPlayerOnError的回调函数指针。
 * 应用需注册此实例结构体到OH_AVPlayer实例中，并对回调上报的信息进行处理，保证AVPlayer的正常运行。
 * 通过注册这些回调，开发者可以实时监控AVPlayer的播放状态、获取播放过程信息（如缓冲进度、播放位置等）和错误事件，及时响应和处理播放过程中的各种事件。
 * 适用于需要对播放流程进行细粒度控制（Fine-grained Control）和监控的场景，如音乐播放器、视频播放器、直播应用等需要实时监控播放状态和异常处理的应用。
 * 
 * @param onInfo 监控OH_AVPlayer运行信息，参见{@link OH_AVPlayerOnInfo}
 * @param onError 监控OH_AVPlayer运行错误，参阅{@link OH_AVPlayerOnError}
 * @since 11
 * @deprecated since 12
 * @useinstead {@link OH_AVPlayerOnInfoCallback}或{@link OH_AVPlayerOnErrorCallback}。
 */
typedef struct AVPlayerCallback {
    OH_AVPlayerOnInfo onInfo;
    OH_AVPlayerOnError onError;
} AVPlayerCallback;

/**
 * @brief 当计算出最大音频电平值时调用。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param amplitudes 指向最大音频电平值数组的指针。
 * 注意：最大音频电平值数组会在回调后自动释放。
 * 如有需要，用户需自行拷贝数据以供后续使用。
 * @param size 最大音频电平值数组的大小。
 * @param userData 指向用户特定数据的指针。
 * @since 23
 */
typedef void (*OH_AVPlayerOnAmplitudeUpdateCallback)(OH_AVPlayer *player, double *amplitudes, uint32_t size,
    void *userData);

/**
 * @brief 用于获取SEI消息的回调处理函数。在订阅SEI消息事件时使用，回调返回详细的SEI信息。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param message SEI消息数组。
 * 注意：SEI消息数组会在回调后自动释放。
 * 如有需要，用户需自行拷贝数据以供后续使用。
 * @param playbackPosition 播放位置。
 * @param userData 指向用户特定数据的指针。
 * @since 23
 */
typedef void (*OH_AVPlayerOnSeiMessageReceivedCallback)(OH_AVPlayer *player, OH_AVSeiMessageArray *message,
    int32_t playbackPosition, void *userData);

/** 
 * @brief 如果应用成功设置该回调，则会获取音频PCM数据输出。PCM数据为原始音频数据，格式（采样率、声道数、位深等）与媒体源一致。回调在音频解码后触发，数据仅在此回调期间有效，需及时处理或拷贝。适用于音频分析、特效处理等场景。
 *
 * @param player 指向OH_AVPlayer实例的指针。 
 * @param pcmBuffer 音频PCM数据。音频PCM数据仅在此回调期间有效，回调返回后由播放器释放。
 * @param userData 指向用户指定数据的指针。
 * @since 26.0.0 
 */ 
typedef void (*OH_AVPlayerPCMOutputCallback)(OH_AVPlayer *player, OH_AVBuffer *pcmBuffer, void *userData);

/**
 * @brief 如果应用成功设置该回调，则AVPlayer需要使用处理后的数据进行音频播放，且处理必须在回调返回前及时完成，否则会阻塞播放。
 *        使用本方法期间请勿更改采样率、声道数或采样格式，避免数据获取出现异常。
 *
 * @param player 指向OH_AVPlayer实例的指针。
 * @param pcmBuffer 音频PCM数据。音频PCM数据仅在此回调期间有效，回调返回后由播放器释放。
 * @param userData 	指向用户指定数据的指针。
 * @since 26.0.0
 */
typedef void (*OH_AVPlayerPCMProcessorCallback)(OH_AVPlayer *player, OH_AVBuffer *pcmBuffer, void *userData);

/**
 * @brief 获取统计指标信息中的准备时长的关键字，对应值类型为uint32_t，单位为毫秒。
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_PREPARE_DURATION;

/**
 * @brief 获取统计指标信息中的资源链接建立时长的关键字，对应值类型为uint32_t，单位为毫秒。
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_RESOURCE_CONNECTION_DURATION;

/**
 * @brief 获取统计指标信息中的首帧解封装时长的关键字，对应值类型为uint32_t，单位为毫秒。
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_FIRST_FRAME_DECAPSULATION_DURATION;

/**
 * @brief 获取统计指标信息中的累计播放时长的关键字，对应值类型为uint32_t，单位为毫秒。
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_TOTAL_PLAYING_TIME;

/**
 * @brief 获取统计指标信息中的媒体资源加载请求累计次数的关键字，对应值类型为uint32_t。
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_DOWNLOAD_REQUEST_COUNT;

/**
 * @brief 获取统计指标信息中的媒体资源加载总时长的关键字，对应值类型为uint32_t，单位为毫秒。
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_DOWNLOAD_TOTAL_TIME;

/**
 * @brief 获取统计指标信息中的已加载媒体资源累计字节数的关键字，对应值类型为int64_t。
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_DOWNLOAD_TOTAL_SIZE;

/**
 * @brief 获取统计指标信息中的累计卡顿次数的关键字，对应值类型为uint32_t。
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_STALLING_COUNT;

/**
 * @brief 获取统计指标信息中的累计卡顿时长的关键字，对应值类型为uint32_t，单位为毫秒。
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_TOTAL_STALLING_TIME;

/**
 * @brief 播放信息中表示服务器IP地址的关键字，对应值类型为字符串。
 *
 * @since 23
 */
extern const char* OH_PLAYER_SERVER_IP_ADDRESS;

/**
 * @brief 播放信息中表示当前是否处于下载状态的关键字，值类型为int32_t。值为1表示正在下载，0表示未下载。
 *
 * @since 23
 */
extern const char* OH_PLAYER_IS_DOWNLOADING;

/**
 * @brief 播放信息中表示缓冲区时长的关键字，值类型为int32_t，单位为毫秒。
 *
 * @since 23
 */
extern const char* OH_PLAYER_BUFFER_DURATION;

/**
 * @brief 播放信息中表示当前下载速率的关键字，对应值类型是int32_t，下载速率的单位为比特率（bps）。
 *
 * @since 23
 */
extern const char* OH_PLAYER_DOWNLOAD_RATE;

/**
 * @brief 播放信息中表示平均下载速率的关键字，对应值类型是int32_t，下载速率的单位为比特率（bps）。
 *
 * @since 23
 */
extern const char* OH_PLAYER_AVG_DOWNLOAD_RATE;

#ifdef __cplusplus
}
#endif
#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVPLAYER_BASH_H
