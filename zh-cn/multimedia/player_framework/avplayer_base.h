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
 * @brief Provides APIs of Playback capability for Media Source.
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

typedef struct OH_AVPlayer OH_AVPlayer;

/**
 * @brief SEI消息数组的结构体类型。
 * 
 * @since 23
 */
typedef struct OH_AVSeiMessageArray OH_AVSeiMessageArray;

/**
 * @brief 音视频播放策略的结构体类型。
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
    /* idle states */
    AV_IDLE = 0,
    /* initialized states */
    AV_INITIALIZED = 1,
    /* prepared states */
    AV_PREPARED = 2,
    /* playing states */
    AV_PLAYING = 3,
    /* paused states */
    AV_PAUSED = 4,
    /* stopped states */
    AV_STOPPED = 5,
    /* Play to the end states */
    AV_COMPLETED = 6,
    /* released states */
    AV_RELEASED = 7,
    /* error states */
    AV_ERROR = 8,
} AVPlayerState;

/**
 * @brief 跳转模式。
 * 
 * @since 11
 */
typedef enum AVPlayerSeekMode {
    /* sync to keyframes after the time point. */
    AV_SEEK_NEXT_SYNC = 0,
    /* sync to keyframes before the time point. */
    AV_SEEK_PREVIOUS_SYNC,
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
    /* Video playback at 0.75x normal speed */
    AV_SPEED_FORWARD_0_75_X,
    /* Video playback at normal speed */
    AV_SPEED_FORWARD_1_00_X,
    /* Video playback at 1.25x normal speed */
    AV_SPEED_FORWARD_1_25_X,
    /* Video playback at 1.75x normal speed */
    AV_SPEED_FORWARD_1_75_X,
    /* Video playback at 2.0x normal speed */
    AV_SPEED_FORWARD_2_00_X,
    /**
     * @brief 0.5倍速播放。
     * 
     * @since 12
     */
    AV_SPEED_FORWARD_0_50_X,
    /**
     * @brief 1.5倍速播放。
     * 
     * @since 12
     */
    AV_SPEED_FORWARD_1_50_X,
    /**
     * @brief 3.0倍速播放。
     * 
     * @since 13
    */
    AV_SPEED_FORWARD_3_00_X,
    /**
     * @brief 0.25倍速播放。
     * 
     * @since 13
    */
    AV_SPEED_FORWARD_0_25_X,
    /**
     * @brief 0.125倍速播放。
     * 
     * @since 13
    */
    AV_SPEED_FORWARD_0_125_X,
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
    /* return the message when seeking done. */
    AV_INFO_TYPE_SEEKDONE = 0,
    /* return the message when speeding done. */
    AV_INFO_TYPE_SPEEDDONE = 1,
    /* return the message when select bitrate done */
    AV_INFO_TYPE_BITRATEDONE = 2,
    /* return the message when playback is end of steam. */
    AV_INFO_TYPE_EOS = 3,
    /* return the message when PlayerStates changed. */
    AV_INFO_TYPE_STATE_CHANGE = 4,
    /* return the current posion of playback automatically. */
    AV_INFO_TYPE_POSITION_UPDATE = 5,
    /* return the playback message. */
    AV_INFO_TYPE_MESSAGE = 6,
    /* return the message when volume changed. */
    AV_INFO_TYPE_VOLUME_CHANGE = 7,
    /* return the message when video size is first known or updated. */
    AV_INFO_TYPE_RESOLUTION_CHANGE = 8,
    /* return multiqueue buffering time. */
    AV_INFO_TYPE_BUFFERING_UPDATE = 9,
    /* return hls bitrate.
       Bitrate is to convert data into uint8_t array storage,
       which needs to be forcibly converted to uint32_t through offset access. */
    AV_INFO_TYPE_BITRATE_COLLECT = 10,
    /* return the message when audio focus changed. */
    AV_INFO_TYPE_INTERRUPT_EVENT = 11,
    /* return the duration of playback. */
    AV_INFO_TYPE_DURATION_UPDATE = 12,
    /* return the playback is live stream. */
    AV_INFO_TYPE_IS_LIVE_STREAM = 13,
    /* return the message when track changes. */
    AV_INFO_TYPE_TRACKCHANGE = 14,
    /* return the message when subtitle track info updated. */
    AV_INFO_TYPE_TRACK_INFO_UPDATE = 15,
    /* return the subtitle of playback. */
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
 * @brief Result of Video output.
 * @since 26.0.0
 */
typedef enum OH_VideoOutputResult {
    /**
     * @brief Output one decoded video frame.
     * @since 26.0.0
     */
    OH_VIDEO_OUTPUT_OK = 0,
    /**
     * @brief No frame ready to render.
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
 * @brief 获取音量的关键字，对应值类型是float。
 * 
 * @since 12
 */
extern const char* OH_PLAYER_VOLUME;

/**
 * @brief 获取比特率列表的关键字，对应值类型是uint8_t字节数组。通过该关键字获取信息时：
 * 需要先使用uint8_t类型指针变量保存比特率列表，使用size_t类型变量保存字节数组长度。
 * 然后分配若干个uint32_t类型的存储空间，接收将uint8_t字节数组转换为uint32_t类型比特率整数值。
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
 * Sei message key for payload type.
 * @since 23
 */
extern const char* OH_PLAYER_SEI_PAYLOAD_TYPE;

/**
 * Sei message key for payload content.
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
 * @brief 在API version 9以上的版本发生错误时调用。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param errorCode 错误码。
 * AV_ERR_NO_MEMORY：无内存，取值为1。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不允许，取值为2。
 * AV_ERR_INVALID_VAL：无效值，取值为3。
 * AV_ERR_IO：IO错误，取值为4。
 * AV_ERR_TIMEOUT：超时错误，取值为5。
 * AV_ERR_UNKNOWN：未知错误，取值为6。
 * AV_ERR_SERVICE_DIED：服务死亡，取值为7。
 * AV_ERR_INVALID_STATE：当前状态不支持此操作，取值为8。
 * AV_ERR_UNSUPPORT：未支持的接口，取值为9。
 * AV_ERR_EXTEND_START：扩展错误码初始值，取值为100。
 * @param errorMsg Error message.
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
 * AV_ERR_NO_MEMORY：无内存，取值为1。
 * AV_ERR_OPERATE_NOT_PERMIT：操作不允许，取值为2。
 * AV_ERR_INVALID_VAL：无效值，取值为3。
 * AV_ERR_IO：IO错误。API version 12-13取值为4；API version 14及以后，对应错误细化为错误码5411001~5411011。
 * AV_ERR_TIMEOUT：超时错误，取值为5。
 * AV_ERR_UNKNOWN：未知错误，取值为6。
 * AV_ERR_SERVICE_DIED：服务死亡，取值为7。
 * AV_ERR_INVALID_STATE：当前状态不支持此操作，取值为8。
 * AV_ERR_UNSUPPORT：未支持的接口，取值为9。
 * AV_ERR_EXTEND_START：扩展错误码初始值，取值为100。
 * @param errorMsg Error message, only valid in callback function.
 * @param userData Pointer to user specific data.
 * @since 12
 */
typedef void (*OH_AVPlayerOnErrorCallback)(OH_AVPlayer *player, int32_t errorCode, const char *errorMsg,
    void *userData);

/**
 * @brief 包含了OH_AVPlayerOnInfo和OH_AVPlayerOnError回调函数指针的集合。应用需注册此实例结构体到OH_AVPlayer实例中，并对回调上报的信息进行处理，保证AVPlayer的正常运行。
 * 
 * @param onInfo Monitor OH_AVPlayer operation information, refer to {@link OH_AVPlayerOnInfo}
 * @param onError Monitor OH_AVPlayer operation errors, refer to {@link OH_AVPlayerOnError}
 * @since 11
 * @deprecated since 12
 * @useinstead {@link OH_AVPlayerOnInfoCallback} {@link OH_AVPlayerOnErrorCallback}
 */
typedef struct AVPlayerCallback {
    OH_AVPlayerOnInfo onInfo;
    OH_AVPlayerOnError onError;
} AVPlayerCallback;

/**
 * @brief 当计算出最大音频电平值时调用。
 * 
 * @param player Pointer to an OH_AVPlayer instance.
 * @param amplitudes The pointer to the maximum audio level values array.
 * Note: the amplitudes array will be released after callback automatically.
 * If necessary, user need copy the data for the further use.
 * @param size 最大音频电平值数组的大小。
 * @param userData Pointer to user specific data.
 * @since 23
 */
typedef void (*OH_AVPlayerOnAmplitudeUpdateCallback)(OH_AVPlayer *player, double *amplitudes, uint32_t size,
    void *userData);

/**
 * @brief 用于获取SEI消息的回调处理函数。在订阅SEI消息事件时使用，回调返回详细的SEI信息。
 * 
 * @param player Pointer to an OH_AVPlayer instance
 * @param message SEI message array.
 * Note: the message array will be released after callback automatically.
 * If necessary, user need copy the data for the further use.
 * @param playbackPosition 播放位置。
 * @param userData Pointer to user specific data
 * @since 23
 */
typedef void (*OH_AVPlayerOnSeiMessageReceivedCallback)(OH_AVPlayer *player, OH_AVSeiMessageArray *message,
    int32_t playbackPosition, void *userData);

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
 * Playback info key for server ip address.
 * @since 23
 */
extern const char* OH_PLAYER_SERVER_IP_ADDRESS;

/**
 * Playback info key for downloading state.
 * @since 23
 */
extern const char* OH_PLAYER_IS_DOWNLOADING;

/**
 * Playback info key for buffer duration.
 * @since 23
 */
extern const char* OH_PLAYER_BUFFER_DURATION;

/**
 * Playback info key for download rate.
 * @since 23
 */
extern const char* OH_PLAYER_DOWNLOAD_RATE;

/**
 * Playback info key for average download rate.
 * @since 23
 */
extern const char* OH_PLAYER_AVG_DOWNLOAD_RATE;

#ifdef __cplusplus
}
#endif
#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVPLAYER_BASH_H
