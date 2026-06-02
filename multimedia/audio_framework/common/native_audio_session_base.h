/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * You may not use this file except in compliance with the License.
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
 * @brief Provides the definition of the C interface for the audio module.
 *
 * @since 24
 * @version 1.0
 */

/**
 * @file native_audio_session_base.h
 *
 * @brief Declares the audio session base data structure.
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 24
 * @version 1.0
 */

#ifndef NATIVE_AUDIO_SESSION_BASE_H
#define NATIVE_AUDIO_SESSION_BASE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the audio session behavior flags.
 *
 * @since 24
 */
typedef enum {
    /**
     * @brief Default behavior, used to clear behavior settings.
     *
     * @since 24
     */
    DEFAULT_BEHAVIOR  = 0x00000000,

    /**
     * @brief Non-privacy VoIP, allowed to be recorded.
     *
     * @since 26.0.0
     */
    VOIP_PRIVACY_TYPE_PUBLIC = 0x00000001,

    /**
     * @brief When the system needs to stop or pause the audio stream, it performs a forced mute instead.
     * In the audio session scenario, the application will receive a notification
     * {@link AUDIO_SESSION_STATE_CHANGE_HINT_MUTE} when muted
     * and a notification {@link AUDIO_SESSION_STATE_CHANGE_HINT_UNMUTE} when resumed.
     * In the OH_AudioRenderer and OH_AudioCapturer scenarios, the application will receive a notification
     * {@link AUDIOSTREAM_INTERRUPT_HINT_MUTE} when muted
     * and a notification {@link AUDIOSTREAM_INTERRUPT_HINT_UNMUTE} when resumed.
     * This flag cannot coexist with {@link PAUSE_WHEN_INTERRUPTED}; if both flags are set,
     * only {@link PAUSE_WHEN_INTERRUPTED} will take effect.
     *
     * @since 24
     */
    MUTE_WHEN_INTERRUPTED = 0x00000002,

    /**
     * @brief When the system needs to stop the audio stream, it performs a pause instead.
     * In the audio session scenario, the application will receive a notification
     * {@link AUDIO_SESSION_STATE_CHANGE_HINT_PAUSE} when paused
     * and a notification {@link AUDIO_SESSION_STATE_CHANGE_HINT_RESUME} when resumed.
     * In the OH_AudioRenderer and OH_AudioCapturer scenarios, the application will receive a notification
     * {@link AUDIOSTREAM_INTERRUPT_HINT_PAUSE} when paused
     * and a notification {@link AUDIOSTREAM_INTERRUPT_HINT_RESUME} when resumed.
     * This flag cannot coexist with {@link MUTE_WHEN_INTERRUPTED}; if both flags are set,
     * only this flag will take effect.
     *
     * @since 26.0.0
     */
    PAUSE_WHEN_INTERRUPTED = 0x00000004,
} OH_AudioSession_BehaviorFlags;

/**
 * @brief Declares the audio concurrency modes.
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief Default mode
     */
    CONCURRENCY_DEFAULT = 0,

    /**
     * @brief Mix with others mode
     */
    CONCURRENCY_MIX_WITH_OTHERS = 1,

    /**
     * @brief Duck others mode
     */
    CONCURRENCY_DUCK_OTHERS = 2,

    /**
     * @brief Pause others mode
     */
    CONCURRENCY_PAUSE_OTHERS = 3,
} OH_AudioSession_ConcurrencyMode;

/**
 * @brief Declares the audio session strategy.
 *
 * @since 12
 */
typedef struct OH_AudioSession_Strategy {
    /**
     * @brief Audio session concurrency mode
     */
    OH_AudioSession_ConcurrencyMode concurrencyMode;
} OH_AudioSession_Strategy;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_SESSION_BASE_H
/** @} */
