/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup OHAVSession
 * @{
 *
 * @brief 提供媒体会话模块C接口定义。
 *
 * @since 23
 * @version 1.0
 */

/**
 * @file native_avsession_base.h
 *
 * @brief 声明AVSession基本信息。
 *
 * @library libohavsession.so
 * @syscap SystemCapability.Multimedia.AVSession.Core
 * @kit AVSessionKit
 * @since 23
 * @version 1.0
 */

#ifndef NATIVE_AVSESSION_BASE_H
#define NATIVE_AVSESSION_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 会话类型枚举。
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /**
     * @brief 音频会话类型（指媒体类音频，如音乐）。
     */
    SESSION_TYPE_AUDIO = 0,

    /**
     * @brief 视频会话类型（指媒体类投屏视频）。
     */
    SESSION_TYPE_VIDEO = 1,

    /**
     * @brief 音频通话会话类型（指人机交互相关的音频，如语音助手）。
     */
    SESSION_TYPE_VOICE_CALL = 2,

    /**
     * @brief 视频通话会话类型（指视频电话）。
     */
    SESSION_TYPE_VIDEO_CALL = 3,

    /**
     * @brief 相片会话类型。
     */
    SESSION_TYPE_PHOTO = 4
} AVSession_Type;

/**
 * @brief 媒体播放状态的相关属性枚举。
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /**
     * @brief 初始状态。
     */
    PLAYBACK_STATE_INITIAL = 0,

    /**
     * @brief 准备播放状态。表示媒体资源还未处于可播放状态。
     */
    PLAYBACK_STATE_PREPARING = 1,

    /**
     * @brief 正在播放状态。
     */
    PLAYBACK_STATE_PLAYING = 2,

    /**
     * @brief 暂停播放状态。
     */
    PLAYBACK_STATE_PAUSED = 3,

    /**
     * @brief 快进状态。
     */
    PLAYBACK_STATE_FAST_FORWARDING = 4,

    /**
     * @brief 快退状态。
     */
    PLAYBACK_STATE_REWINDED = 5,

    /**
     * @brief 停止状态。
     */
    PLAYBACK_STATE_STOPPED = 6,

    /**
     * @brief 播放完成状态。
     */
    PLAYBACK_STATE_COMPLETED = 7,

    /**
     * @brief 释放状态。
     */
    PLAYBACK_STATE_RELEASED = 8,

    /**
     * @brief 错误状态。
     */
    PLAYBACK_STATE_ERROR = 9,

    /**
     * @brief 空闲状态。
     */
    PLAYBACK_STATE_IDLE = 10,

    /**
     * @brief 缓冲状态。
     */
    PLAYBACK_STATE_BUFFERING = 11,

    /**
     * @brief 最大状态（当状态值为12时，返回错误码401）。
     */
    PLAYBACK_STATE_MAX = 12
} AVSession_PlaybackState;

/**
 * @brief 定义媒体播放循环模式。
 *
 * @since 13
 */
typedef enum {
    /**
     * @brief 按顺序播放。
     */
    LOOP_MODE_SEQUENCE = 0,

    /**
     * @brief 单曲循环。
     */
    LOOP_MODE_SINGLE = 1,

    /**
     * @brief 按表单循环。
     */
    LOOP_MODE_LIST = 2,

    /**
     * @brief 随机播放。
     */
    LOOP_MODE_SHUFFLE = 3,

    /**
     * @brief 自定义播放。
     */
    LOOP_MODE_CUSTOM = 4
} AVSession_LoopMode;

/**
 * @brief 播控命令枚举。
 *
 * @since 13
 * @version 1.0
 */
typedef enum AVSession_ControlCommand {
    /**
     * @brief 无效控制命令。
     */
    CONTROL_CMD_INVALID = -1,

    /**
     * @brief 播放命令。
     */
    CONTROL_CMD_PLAY = 0,

    /**
     * @brief 暂停命令。
     */
    CONTROL_CMD_PAUSE = 1,

    /**
     * @brief 停止命令。
     */
    CONTROL_CMD_STOP = 2,

    /**
     * @brief 播放下一首命令。
     */
    CONTROL_CMD_PLAY_NEXT = 3,

    /**
     * @brief 播放上一首命令。
     */
    CONTROL_CMD_PLAY_PREVIOUS = 4
} AVSession_ControlCommand;

/**
 * @brief 定义快进或快退的时间间隔。
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /**
     * @brief 时间间隔为10秒。
     */
    SECONDS_10 = 10,

    /**
     * @brief 时间间隔为15秒。
     */
    SECONDS_15 = 15,

    /**
     * @brief 时间间隔为30秒。
     */
    SECONDS_30 = 30
} AVMetadata_SkipIntervals;

/**
 * @brief 当前媒体资源的金标枚举，即应用媒体音源的特殊类型标识。
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /**
     * @brief 高清音频。
     */
    AVSESSION_DISPLAYTAG_AUDIO_VIVID = 1
} AVMetadata_DisplayTag;

/**
 * @brief 设备连接状态枚举。
 *
 * @since 23
 * @version 1.0
 */
typedef enum AVSession_ConnectionState {
    /**
     * @brief 表示设备正处于连接状态。
     */
     * @since 23
     */
    STATE_CONNECTING = 0,

    /**
     * @brief 表示设备处于已连接状态。
     */
     * @since 23
     */
    STATE_CONNECTED = 1,

    /**
     * @brief 表示设备已处于断开默认连接的状态。
     */
     * @since 23
     */
    STATE_DISCONNECTED = 6
} AVSession_ConnectionState;

/**
 * @brief 表示不同播放场景的投播类别枚举。
 *
 * @since 23
 * @version 1.0
 */
typedef enum AVSession_AVCastCategory {
    /**
     * @brief 默认投播类别是本地。
     * 默认投屏类型为本地。媒体本地路由支持内置扬声器、音频插孔、A2DP（Advanced Audio Distribution Profile）设备。
     */
    CATEGORY_LOCAL = 0,

    /**
     * @brief 远程类别。
     * 表示媒体正在远程设备上展示，应用需要一个{@link OH_AVCastController}来控制远程播放。
     */
    CATEGORY_REMOTE = 1
} AVSession_AVCastCategory;

/**
 * @brief 设备类型枚举。
 *
 * @since 23
 * @version 1.0
 */
typedef enum AVSession_DeviceType {
    /**
     * @brief 一种设备类型，标识音频路由为设备自身的内置扬声器或音频插孔。
     */
     * @since 23
     */
    DEVICE_TYPE_LOCAL = 0,

    /**
     * @brief 一种设备类型，标识音频路由为电视端。
     */
     * @since 23
     */
    DEVICE_TYPE_TV = 2,

    /**
     * @brief 一种设备类型，标识音频路由为智能音箱端。
     */
     * @since 23
     */
    DEVICE_TYPE_SMART_SPEAKER = 3,

    /**
     * @brief 一种设备类型，标识音频路由为蓝牙设备端。
     */
     * @since 23
     */
    DEVICE_TYPE_BLUETOOTH = 10
} AVSession_DeviceType;

/**
 * @brief 协议类型枚举。
 *
 * @since 23
 * @version 1.0
 */
typedef enum AVSession_ProtocolType {
    /**
     * @brief 默认为本地设备。
     * 包括设备本身的内置扬声器或音频插孔，A2DP（Advanced Audio Distribution Profile）设备。
     */
     * @since 23
     */
    TYPE_LOCAL = 0,

    /**
     * @brief Cast+的Stream模式。
     * 表示媒体正在其他设备上展示，应用需要一个AVCastController来控制远程播放。
     */
     * @since 23
     */
    TYPE_CAST_PLUS_STREAM = 2,

    /**
     * @brief DLNA（DIGITAL LIVING NETWORK ALLIANCE）协议。
     * 表示设备支持DLNA协议，应用需要一个AVCastController来控制远程播放。
     */
     * @since 23
     */
    TYPE_DLNA = 4,

    /**
     * @brief 表示该设备支持高清晰度的音频投播，以获得更好的音质。
     */
     * @since 23
     */
    TYPE_CAST_PLUS_AUDIO = 8
} AVSession_ProtocolType;

/**
 * @brief 命令类型枚举。
 *
 * @since 23
 * @version 1.0
 */
typedef enum AVSession_AVCastControlCommandType {
    /**
     * @brief 播放命令。
     */
     * @since 23
     */
    CAST_CONTROL_CMD_PLAY = 0,
    /**
     * @brief 暂停命令。
     */
     * @since 23
     */
    CAST_CONTROL_CMD_PAUSE = 1,
    /**
     * @brief 停止命令。
     */
     * @since 23
     */
    CAST_CONTROL_CMD_STOP = 2,
    /**
     * @brief 下一首命令。
     */
     * @since 23
     */
    CAST_CONTROL_CMD_PLAY_NEXT = 3,
    /**
     * @brief 上一首命令。
     */
     * @since 23
     */
    CAST_CONTROL_CMD_PLAY_PREVIOUS = 4,
    /**
     * @brief 快进命令。
     */
     * @since 23
     */
    CAST_CONTROL_CMD_FAST_FORWARD = 5,
    /**
     * @brief 快退命令。
     */
     * @since 23
     */
    CAST_CONTROL_CMD_REWIND = 6,
    /**
     * @brief 跳转到指定播放位置命令。
     */
     * @since 23
     */
    CAST_CONTROL_CMD_SEEK = 7,
    /**
     * @brief 设置音量命令。
     */
     * @since 23
     */
    CAST_CONTROL_CMD_SET_VOLUME = 8,
    /**
     * @brief 设置播放倍速命令。
     */
     * @since 23
     */
    CAST_CONTROL_CMD_SET_SPEED = 9
} AVSession_AVCastControlCommandType;

/**
 * @brief 播放倍速类型枚举。
 *
 * @since 23
 * @version 1.0
 */
typedef enum AVSession_PlaybackSpeed {
    /**
     * @brief 以正常播速的0.75倍速播放音视频。
     */
     * @since 23
     */
    SPEED_FORWARD_0_75_X = 0,
    /**
     * @brief 以正常播速（1.00x）播放音视频。
     */
     * @since 23
     */
    SPEED_FORWARD_1_00_X = 1,

    /**
     * @brief 以正常播速的1.25倍速播放音视频。
     */
     * @since 23
     */
    SPEED_FORWARD_1_25_X = 2,

    /**
     * @brief 以正常播速的1.75倍速播放音视频。
     */
     * @since 23
     */
    SPEED_FORWARD_1_75_X = 3,

    /**
     * @brief 以正常播速的2倍速播放音视频。
     */
     * @since 23
     */
    SPEED_FORWARD_2_00_X = 4,

    /**
     * @brief 以正常播速的0.5倍速播放音视频。
     */
     * @since 23
     */
    SPEED_FORWARD_0_50_X = 5,

    /**
     * @brief 以正常播速的1.5倍速播放音视频。
     */
     * @since 23
     */
    SPEED_FORWARD_1_50_X = 6
} AVSession_PlaybackSpeed;

/**
 * @brief 播放状态过滤器枚举。
 *
 * @since 23
 * @version 1.0
 */
typedef enum AVSession_PlaybackFilter {
    /**
     * @brief 过滤状态。
     */
     * @since 23
     */
    FILTER_STATE = 1 << 0,

    /**
     * @brief 过滤位置。
     */
     * @since 23
     */
    FILTER_POSITION = 1 << 1,

    /**
     * @brief 过滤倍速。
     */
     * @since 23
     */
    FILTER_SPEED = 1 << 2,

    /**
     * @brief 过滤音量。
     */
     * @since 23
     */
    FILTER_VOLUME = 1 << 3
} AVSession_PlaybackFilter;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSESSION_BASE_H
/** @} */