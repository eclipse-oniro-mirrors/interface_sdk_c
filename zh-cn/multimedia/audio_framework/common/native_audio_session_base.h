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
 * @brief 声明音频会话基础数据结构。
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
 * @brief 音频会话行为标志。
 *
 * @since 24
 */
typedef enum {
    /**
     * @brief 默认行为，用于清除会话行为标记。
     *
     * @since 24
     */
    DEFAULT_BEHAVIOR = 0x00000000,

    /**
     * @brief 当系统需要停止或暂停音频流时，执行强制静音替代。
     * <br>调用{@link OH_AudioSessionManager_SetBehavior}接口配置该行为时，必须同步调用{@link OH_AudioSessionManager_SetScene}接口，
     * 否则配置将无法生效。
     * <br>在音频会话场景下，当音频流静音或恢复时，应用将分别收到{@link OH_AudioSession_StateChangeHint}.AUDIO_SESSION_STATE_CHANGE_HINT_MUTE与
     * {@link OH_AudioSession_StateChangeHint}.AUDIO_SESSION_STATE_CHANGE_HINT_UNMUTE的通知。
     * <br>在OH_AudioRenderer和OH_AudioCapturer场景下，当音频流静音或恢复时，应用将分别收到{@link OH_AudioInterrupt_Hint}.
     * AUDIOSTREAM_INTERRUPT_HINT_MUTE与{@link OH_AudioInterrupt_Hint}.AUDIOSTREAM_INTERRUPT_HINT_UNMUTE的通知。
     * **注意：** 该标志不能与PAUSE_WHEN_INTERRUPTED共存，若同时设置，仅PAUSE_WHEN_INTERRUPTED生效。
     *
     * @since 24
     */
    MUTE_WHEN_INTERRUPTED = 0x00000002,

    /**
     * @brief 当系统需要停止音频流时，执行暂停替代。
     * <br>调用{@link OH_AudioSessionManager_SetBehavior}接口配置该行为时，必须同步调用{@link OH_AudioSessionManager_SetScene}接口，
     * 否则配置将无法生效。
     * <br>在音频会话场景下，当音频流暂停或恢复时，应用将分别收到{@link OH_AudioSession_StateChangeHint}.AUDIO_SESSION_STATE_CHANGE_HINT_PAUSE与
     * {@link OH_AudioSession_StateChangeHint}.AUDIO_SESSION_STATE_CHANGE_HINT_RESUME的通知。
     * <br>在OH_AudioRenderer和OH_AudioCapturer场景下，当音频流暂停或恢复时，应用将分别收到{@link OH_AudioInterrupt_Hint}.
     * AUDIOSTREAM_INTERRUPT_HINT_PAUSE与{@link OH_AudioInterrupt_Hint}.AUDIOSTREAM_INTERRUPT_HINT_RESUME的通知。
     * **注意：** 该标志不能与MUTE_WHEN_INTERRUPTED共存，若同时设置，仅该标志生效。
     *
     * @since 26.0.0
     */
    PAUSE_WHEN_INTERRUPTED = 0x00000004
} OH_AudioSession_BehaviorFlags;

/**
 * @brief 音频并发模式。
 * <br>从API version 24开始，此枚举由native_audio_session_manager.h移动至此头文件。
 * <br>在API version 24之前，使用该枚举请引用native_audio_session_manager.h头文件；从API version 24开始，引用native_audio_session_manager.
 * h或native_audio_session_base.h均可正常使用该枚举。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 默认使用系统策略。
     *
     */
    CONCURRENCY_DEFAULT = 0,

    /**
     * @brief 当前应用与其他应用混音播放。
     *
     */
    CONCURRENCY_MIX_WITH_OTHERS = 1,

    /**
     * @brief 当前应用播放时会压低其他正在播放的应用音量。
     *
     */
    CONCURRENCY_DUCK_OTHERS = 2,

    /**
     * @brief 当前应用播放时会暂停其他正在播放的应用。
     *
     */
    CONCURRENCY_PAUSE_OTHERS = 3
} OH_AudioSession_ConcurrencyMode;

/**
 * @brief 音频会话策略。<br>从API version 24开始，此结构体由native_audio_session_manager.h移动至native_audio_session_base.h文件。<br>在API
 * version 24之前，使用该结构体请引用native_audio_session_manager.h头文件；从API version 24开始，引用native_audio_session_manager.
 * h或native_audio_session_base.h均可正常使用该结构体。
 *
 * @since 12
 */
typedef struct OH_AudioSession_Strategy {
    /**
     * @brief 音频并发模式。
     *
     */
    OH_AudioSession_ConcurrencyMode concurrencyMode;
} OH_AudioSession_Strategy;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_SESSION_BASE_H
/** @} */