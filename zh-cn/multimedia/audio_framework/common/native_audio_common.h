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
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file native_audio_common.h
 *
 * @brief 声明音频公共基础数据结构。
 * <br>定义音频接口的公共返回值的类型。
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
 * @brief 音频错误码。
 *
 * @since 12
 */
typedef enum {
    /**
     * @error
     * 操作成功。
     */
    AUDIOCOMMON_RESULT_SUCCESS = 0,

    /**
     * @error
     * 调用者没有请求权限。
     *
     * @since 26.0.0
     */
    AUDIOCOMMON_RESULT_ERROR_PERMISSION_DENIED = 201,

    /**
     * @error
     * 入参错误。
     */
    AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM = 6800101,

    /**
     * @error
     * 无内存。
     */
    AUDIOCOMMON_RESULT_ERROR_NO_MEMORY = 6800102,

    /**
     * @error
     * 非法状态。
     */
    AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE = 6800103,

    /**
     * @error
     * 操作不支持。
     */
    AUDIOCOMMON_RESULT_ERROR_UNSUPPORTED = 6800104,

    /**
     * @error
     * 操作超时。
     */
    AUDIOCOMMON_RESULT_ERROR_TIMEOUT = 6800105,

    /**
     * @error
     * 达到系统可支持的最大数量。
     */
    AUDIOCOMMON_RESULT_ERROR_STREAM_LIMIT = 6800201,

    /**
     * @error
     * 系统通用错误。
     */
    AUDIOCOMMON_RESULT_ERROR_SYSTEM = 6800301,

    /**
     * @error
     * 输入的音频数据不匹配请求的帧长。
     *
     * @since 26.0.0
     */
    AUDIOCOMMON_RESULT_ERROR_FRAME_LENGTH_MISMATCH = 6800106
} OH_AudioCommon_Result;

/**
 * @brief 定义音频场景。
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
 * @brief 定义铃音模式。
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
 * @brief 枚举降噪模式。
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief 保真模式，无降噪功能。
     *
     * @since 26.0.0
     */
    AUDIO_NOISE_REDUCTION_MODE_FIDELITY = 0,

    /**
     * @brief 纯人声模式，强降噪。
     *
     * @since 26.0.0
     */
    AUDIO_NOISE_REDUCTION_MODE_PURE_VOCALS = 1,

    /**
     * @brief 标准模式，弱降噪。
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