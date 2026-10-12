/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @since 12
 * @version 1.0
 */

/**
 * @file native_audio_common.h
 *
 * @brief 声明音频公共基础枚举定义，
 * 包括音频错误码、音频场景、铃声模式、录音降噪模式等，在音频播放、音频录制、音频管理相关接口中使用。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 12
 * @version 1.0
 */

#ifndef NATIVE_AUDIO_COMMON_H
#define NATIVE_AUDIO_COMMON_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 音频公共错误码枚举定义，用作音频管理接口的返回值。
 * <br>开发者可通过错误码确定报错类型，采取相应的处理步骤，解决报错场景的功能问题。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 操作成功。
     *
     * @since 12
     */
    AUDIOCOMMON_RESULT_SUCCESS = 0,

    /**
     * @brief 权限缺失。
     *
     * @since 26.0.0
     */
    AUDIOCOMMON_RESULT_ERROR_PERMISSION_DENIED = 201,

    /**
     * @brief 入参错误。
     *
     * @since 12
     */
    AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM = 6800101,

    /**
     * @brief 内存不足。
     *
     * @since 12
     */
    AUDIOCOMMON_RESULT_ERROR_NO_MEMORY = 6800102,

    /**
     * @brief 非法状态。
     *
     * @since 12
     */
    AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE = 6800103,

    /**
     * @brief 操作不支持。
     *
     * @since 12
     */
    AUDIOCOMMON_RESULT_ERROR_UNSUPPORTED = 6800104,

    /**
     * @brief 操作超时。
     *
     * @since 12
     */
    AUDIOCOMMON_RESULT_ERROR_TIMEOUT = 6800105,

    /**
     * @brief 输入音频数据与所需帧长度不匹配。
     *
     * @since 26.0.0
     */
    AUDIOCOMMON_RESULT_ERROR_FRAME_LENGTH_MISMATCH = 6800106,

    /**
     * @brief 达到系统可支持的最大数量。
     *
     * @since 12
     */
    AUDIOCOMMON_RESULT_ERROR_STREAM_LIMIT = 6800201,

    /**
     * @brief 系统通用错误。
     *
     * @since 12
     */
    AUDIOCOMMON_RESULT_ERROR_SYSTEM = 6800301,

    /**
     * @brief 系统服务进程死亡。
     * @since 26.0.1
     */
    AUDIOCOMMON_RESULT_ERROR_SERVICE_DIED = 6800302,

    /**
     * @brief 网络条件不满足接口要求。
     * @since 26.0.1
     */
    AUDIOCOMMON_RESULT_ERROR_NETWORK_CONDITION_NOT_MET = 6800501,

    /**
     * @brief 设备存储空间不足。
     * @since 26.0.1
     */
    AUDIOCOMMON_RESULT_ERROR_STORAGE_NOT_ENOUGH = 6800502
} OH_AudioCommon_Result;

/**
 * @brief 音频场景枚举定义。
 *
 * @since 12
 */
typedef enum {
    /**
     * 默认音频场景。
     * @since 12
     */
    AUDIO_SCENE_DEFAULT = 0,

    /**
     * 响铃场景。
     * @since 12
     */
    AUDIO_SCENE_RINGING = 1,

    /**
     * 电话场景。
     * @since 12
     */
    AUDIO_SCENE_PHONE_CALL = 2,

    /**
     * 语音聊天场景。
     * @since 12
     */
    AUDIO_SCENE_VOICE_CHAT = 3
} OH_AudioScene;

/**
 * @brief 铃声模式枚举定义。
 *
 * @since 20
 */
typedef enum {
    /**
     * 静音模式。
     * @since 20
     */
    AUDIO_RINGER_MODE_SILENT = 0,
    /**
     * 振动模式。
     * @since 20
     */
    AUDIO_RINGER_MODE_VIBRATE = 1,
    /**
     * 响铃模式。
     * @since 20
     */
    AUDIO_RINGER_MODE_NORMAL = 2
} OH_AudioRingerMode;

/**
 * @brief 录音降噪模式枚举定义。
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief 保真模式，不进行降噪。
     *
     * @since 26.0.0
     */
    AUDIO_NOISE_REDUCTION_MODE_FIDELITY = 0,

    /**
     * @brief 纯人声模式，强降噪，显著抑制周边环境声音。
     *
     * @since 26.0.0
     */
    AUDIO_NOISE_REDUCTION_MODE_PURE_VOCALS = 1,

    /**
     * @brief 标准模式，弱降噪，适当抑制周边环境声音。
     *
     * @since 26.0.0
     */
    AUDIO_NOISE_REDUCTION_MODE_STANDARD = 2
} OH_AudioNoiseReductionMode;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_COMMON_H
/** @} */