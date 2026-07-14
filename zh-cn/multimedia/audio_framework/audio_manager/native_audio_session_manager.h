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
 *
 * @addtogroup OHAudio
 * @{
 *
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file native_audio_session_manager.h
 *
 * @brief 声明音频会话管理相关的接口。
 * <br>包含创建音频会话管理器、激活/停用音频会话、检查音频会话是否已激活，以及监听音频会话停用事件。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 12
 * @version 1.0
 */

#ifndef NATIVE_AUDIO_SESSION_MANAGER_H
#define NATIVE_AUDIO_SESSION_MANAGER_H

#include <stdbool.h>
#include "native_audio_common.h"
#include "native_audio_session_base.h"
#include "native_audiostream_base.h"
#include "native_audio_device_base.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 音频会话管理器结构体。用于管理音频会话。
 *
 * @since 12
 */
typedef struct OH_AudioSessionManager OH_AudioSessionManager;

/**
 * @brief 音频会话场景。
 *
 * @since 20
 */
typedef enum {
    /**
     * @brief 媒体音频会话场景。
     *
     */
    AUDIO_SESSION_SCENE_MEDIA = 0,

    /**
     * @brief 游戏音频会话场景。
     *
     */
    AUDIO_SESSION_SCENE_GAME = 1,

    /**
     * @brief VoIP语音通话音频会话场景。
     *
     */
    AUDIO_SESSION_SCENE_VOICE_COMMUNICATION = 2
} OH_AudioSession_Scene;

/**
 * @brief 音频会话状态变更的提示信息。
 *
 * @since 20
 */
typedef enum {
    /**
     * @brief 提示音频会话恢复，应用可主动触发开始渲染等相关操作。
     */
    AUDIO_SESSION_STATE_CHANGE_HINT_RESUME = 0,
    /**
     * @brief 提示音频会话暂停，暂时失去音频焦点。当焦点再次可用时，会收到AUDIO_SESSION_STATE_CHANGE_HINT_RESUME事件。
     */
    AUDIO_SESSION_STATE_CHANGE_HINT_PAUSE = 1,
    /**
     * @brief 提示音频会话在焦点被抢占后停止，彻底失去音频焦点。
     */
    AUDIO_SESSION_STATE_CHANGE_HINT_STOP = 2,
    /**
     * @brief 提示长时间没有音频业务，音频会话将被系统停止，彻底失去音频焦点。
     */
    AUDIO_SESSION_STATE_CHANGE_HINT_TIME_OUT_STOP = 3,
    /**
     * @brief 提示音频会话躲避开始，降低音量播放。如果已启用{@link OH_AudioSessionManager_EnableMuteSuggestionWhenMixWithOthers}，此时可以选择执行静音操作。
     */
    AUDIO_SESSION_STATE_CHANGE_HINT_DUCK = 4,
    /**
     * @brief 提示音频会话躲避结束，恢复音量播放。如果已启用{@link OH_AudioSessionManager_EnableMuteSuggestionWhenMixWithOthers}，此时可取消静音。
     */
    AUDIO_SESSION_STATE_CHANGE_HINT_UNDUCK = 5,

    /**
     * @brief 静音播放建议。当其他应用程序开始播放不可混音的音频时，应用程序可以自行决定是否静音。
     *
     * @since 23
     */
    AUDIO_SESSION_STATE_CHANGE_HINT_MUTE_SUGGESTION = 6,

    /**
     * @brief 取消静音播放建议。当其他应用程序不可混音的音频已结束，该应用程序可自行决定是否取消静音。
     *
     * @since 23
     */
    AUDIO_SESSION_STATE_CHANGE_HINT_UNMUTE_SUGGESTION = 7,
    /**
     * @brief 提示音频会话静音。该提示仅在以下条件满足后才会收到：通过接口{@link OH_AudioSessionManager_SetBehavior}设置参数
     * {@link OH_AudioSession_BehaviorFlags}.MUTE_WHEN_INTERRUPTED，并已调用{@link OH_AudioSessionManager_SetScene}，且音频会话已激活。
     *
     * @since 24
     */
    AUDIO_SESSION_STATE_CHANGE_HINT_MUTE = 8,
    /**
     * @brief 提示音频会话解除静音。该提示仅在以下条件满足后才会收到：通过接口{@link OH_AudioSessionManager_SetBehavior}设置参数
     * {@link OH_AudioSession_BehaviorFlags}.MUTE_WHEN_INTERRUPTED，并已调用{@link OH_AudioSessionManager_SetScene}，且音频会话已激活。
     *
     * @since 24
     */
    AUDIO_SESSION_STATE_CHANGE_HINT_UNMUTE = 9
} OH_AudioSession_StateChangeHint;

/**
 * @brief 输出设备变更后推荐的操作。
 * <br>常见场景示例：耳机设备和外放设备之间进行切换。当佩戴耳机时，从外放设备切换到耳机设备，系统会推荐继续播放，提示应用无需停止当前播放。当摘下耳机设备切换到外放设备时，系统会推荐停止播放。
 *
 * @since 20
 */
typedef enum {
    /**
     * @brief 推荐继续播放（该事件作为播放维持提示，作用是告知应用本次设备变动音频无需停止播放，但不可将其作为启动音频播放的判断依据）。
     *
     */
    DEVICE_CHANGE_RECOMMEND_TO_CONTINUE = 0,

    /**
     * @brief 推荐停止播放。
     *
     */
    DEVICE_CHANGE_RECOMMEND_TO_STOP = 1
} OH_AudioSession_OutputDeviceChangeRecommendedAction;

/**
 * @brief 音频会话停用原因。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 应用焦点被抢占。
     *
     */
    DEACTIVATED_LOWER_PRIORITY = 0,

    /**
     * @brief 应用停流后超时。
     *
     */
    DEACTIVATED_TIMEOUT = 1
} OH_AudioSession_DeactivatedReason;

/**
 * @brief 在使用蓝牙或星闪进行录音时，应用程序的设备偏好分类。
 *
 * @since 21
 */
typedef enum {
    /**
     * @brief 无指定设备偏好。
     *
     */
    PREFERRED_NONE = 0,

    /**
     * @brief 更偏好使用蓝牙或星闪录音。是否使用低延迟或高质量录音取决于系统。
     *
     */
    PREFERRED_DEFAULT = 1,

    /**
     * @brief 更偏好使用蓝牙或星闪低延迟模式进行录音。
     *
     */
    PREFERRED_LOW_LATENCY = 2,

    /**
     * @brief 更偏好使用蓝牙或星闪高质量模式进行录音。
     *
     */
    PREFERRED_HIGH_QUALITY = 3
} OH_AudioSession_BluetoothAndNearlinkPreferredRecordCategory;

/**
 * @brief 音频会话已停用事件。
 *
 * @since 12
 */
typedef struct OH_AudioSession_DeactivatedEvent {
    /**
     * @brief 音频会话停用原因。
     *
     */
    OH_AudioSession_DeactivatedReason reason;
} OH_AudioSession_DeactivatedEvent;
/**
 * @brief 音频会话状态变更事件。
 *
 * @since 20
 */
typedef struct OH_AudioSession_StateChangedEvent {
    /**
     * @brief 音频会话停用的具体原因。
     *
     */
    OH_AudioSession_StateChangeHint stateChangeHint;
} OH_AudioSession_StateChangedEvent;

/**
 * @brief 该函数指针将指向用于监听音频会话状态变更事件的回调函数。
 *
 * @param event 音频会话状态变更事件。
 * @since 20
 */
typedef void (*OH_AudioSession_StateChangedCallback) (
    OH_AudioSession_StateChangedEvent event);

/**
 * @brief 此函数指针将指向用于返回变化的音频设备描述符的回调函数，可能会返回多个音频设备描述符。
 *
 * @param type 设备连接状态类型，已连接或断开。
 * @param audioDeviceDescriptorArray 音频设备描述符数组。
 *     <br>不再继续使用audioDeviceDescriptorArray指针时，请使用{@link OH_AudioSessionManager_ReleaseDevices}进行释放。
 * @since 21
 */
typedef void (*OH_AudioSession_AvailableDeviceChangedCallback) (
    OH_AudioDevice_ChangeType type,
    OH_AudioDeviceDescriptorArray *audioDeviceDescriptorArray);

/**
 * @brief 这个函数指针将指向用于监听当前输入设备变化事件的回调函数。
 *
 * @param audioDeviceDescriptorArray the {@link OH_AudioDeviceDescriptorArray}
 *     pointer variable which will be set the audio input device descriptors value.
 *     Do not release the audioDeviceDescriptorArray pointer separately
 *     instead call {@link OH_AudioSessionManager_ReleaseDevices}
 *     to release the DeviceDescriptor array when it is no use anymore.
 * @param changeReason 设备变更原因。
 * @since 21
 */
typedef void (*OH_AudioSession_CurrentInputDeviceChangedCallback) (
    OH_AudioDeviceDescriptorArray *devices,
    OH_AudioStream_DeviceChangeReason changeReason);
/**
 * @brief 这个函数指针将指向用于监听当前输出设备变化事件的回调函数。
 *
 * @param audioDeviceDescriptorArray the {@link OH_AudioDeviceDescriptorArray}
 *     pointer variable which will be set the audio device descriptors value.
 *     Do not release the audioDeviceDescriptorArray pointer separately
 *     instead call {@link OH_AudioSessionManager_ReleaseDevices} to release the DeviceDescriptor array when it is no
 *     use anymore.
 * @param changeReason 指向{@link OH_AudioStream_DeviceChangeReason}，用于接收设备变更原因。
 * @param recommendedAction 指向{@link OH_AudioSession_OutputDeviceChangeRecommendedAction}，用于接收设备变更后推荐的操作。
 * @since 20
 */
typedef void (*OH_AudioSession_CurrentOutputDeviceChangedCallback) (
    OH_AudioDeviceDescriptorArray *devices,
    OH_AudioStream_DeviceChangeReason changeReason,
    OH_AudioSession_OutputDeviceChangeRecommendedAction recommendedAction);

/**
 * @brief 这个函数指针将指向用于监听音频会话停用事件的回调函数。
 *
 * @param event 音频会话已停用事件。
 * @since 12
 */
typedef int32_t (*OH_AudioSession_DeactivatedCallback) (
    OH_AudioSession_DeactivatedEvent event);

/**
 * @brief 获取音频会话管理器。使用音频会话管理器相关功能，首先需要获取音频会话管理器实例。
 *
 * @param audioSessionManager 音频会话管理器实例。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统错误。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioSessionManager(
    OH_AudioSessionManager **audioSessionManager);

/**
 * @brief 激活音频会话。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param strategy 指向{@link OH_AudioSession_Strategy}，用于设置音频会话策略。
 * @return 函数返回值：
 *     <br>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数strategy无效。
 *     <br>AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：非法状态。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioSessionManager_ActivateAudioSession(
    OH_AudioSessionManager *audioSessionManager, const OH_AudioSession_Strategy *strategy);

/**
 * @brief 停用音频会话。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数audioSessionManager为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：非法状态。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioSessionManager_DeactivateAudioSession(
    OH_AudioSessionManager *audioSessionManager);

/**
 * @brief 检查音频会话是否已激活。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @return 用于返回当前应用的音频会话是否已激活，true表示已激活，false表示已停用。
 * @since 12
 */
bool OH_AudioSessionManager_IsAudioSessionActivated(
    OH_AudioSessionManager *audioSessionManager);

/**
 * @brief 注册音频会话停用事件回调。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param callback 用于接收音频会话已停用事件。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数callback为nullptr。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioSessionManager_RegisterSessionDeactivatedCallback(
    OH_AudioSessionManager *audioSessionManager, OH_AudioSession_DeactivatedCallback callback);

/**
 * @brief 取消注册音频会话停用事件回调。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param callback 用于接收音频会话已停用事件。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数callback为nullptr。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioSessionManager_UnregisterSessionDeactivatedCallback(
    OH_AudioSessionManager *audioSessionManager, OH_AudioSession_DeactivatedCallback callback);

/**
 * @brief 设置音频会话场景参数。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param scene 指向{@link OH_AudioSession_Scene}要设置的音频会话场景。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数scene为枚举范围外的值。
 *     <br>AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：系统当前状态下不允许设置，例如audio session未处于ready态。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 20
 */
OH_AudioCommon_Result OH_AudioSessionManager_SetScene(
    OH_AudioSessionManager *audioSessionManager, OH_AudioSession_Scene scene);

/**
 * @brief 注册音频会话状态变更事件回调。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param callback 用于接收音频会话状态变更事件。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数callback为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_NO_MEMORY：系统内存申请异常。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 20
 */
OH_AudioCommon_Result OH_AudioSessionManager_RegisterStateChangeCallback(
    OH_AudioSessionManager *audioSessionManager, OH_AudioSession_StateChangedCallback callback);

/**
 * @brief 取消音频会话状态变更事件回调。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param callback 用于接收音频会话状态变更事件。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数callback为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 20
 */
OH_AudioCommon_Result OH_AudioSessionManager_UnregisterStateChangeCallback(
    OH_AudioSessionManager *audioSessionManager, OH_AudioSession_StateChangedCallback callback);

/**
 * @brief 设置默认本机内置发声设备。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param deviceType 指向{@link OH_AudioDevice_Type}用于设置发声设备类型。可设置的设备类型包括：
 *     <br>AUDIO_DEVICE_TYPE_EARPIECE：听筒。
 *     <br>AUDIO_DEVICE_TYPE_SPEAKER：扬声器。
 *     <br>AUDIO_DEVICE_TYPE_DEFAULT：系统默认设备。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数deviceType超出枚举OH_AudioDevice_Type范围。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 20
 */
OH_AudioCommon_Result OH_AudioSessionManager_SetDefaultOutputDevice(
    OH_AudioSessionManager *audioSessionManager, OH_AudioDevice_Type deviceType);

/**
 * @brief 获取通过{@link OH_AudioSessionManager_SetDefaultOutputDevice}设置的默认发声设备。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param deviceType 指向{@link OH_AudioDevice_Type}用于获取发声设备类型参数指针。返回的设备类型包括：
 *     <br>AUDIO_DEVICE_TYPE_EARPIECE：听筒。
 *     <br>AUDIO_DEVICE_TYPE_SPEAKER：扬声器。
 *     <br>AUDIO_DEVICE_TYPE_DEFAULT：系统默认设备。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数deviceType为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：系统当前状态下不允许获取默认设备类型，例如audio session未处于ready态。
 * @since 20
 */
OH_AudioCommon_Result OH_AudioSessionManager_GetDefaultOutputDevice(
    OH_AudioSessionManager *audioSessionManager, OH_AudioDevice_Type *deviceType);

/**
 * @brief 释放音频设备描述符数组对象。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param audioDeviceDescriptorArray 需要释放的音频设备描述符数组。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数audioDeviceDescriptorArray为nullptr。
 * @since 20
 */
OH_AudioCommon_Result OH_AudioSessionManager_ReleaseDevices(
    OH_AudioSessionManager *audioSessionManager,
    OH_AudioDeviceDescriptorArray *audioDeviceDescriptorArray);

/**
 * @brief 注册当前输出设备变化回调。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param callback 用于返回音频设备变更信息的回调函数。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数callback为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_NO_MEMORY：系统内存申请异常。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 20
 */
OH_AudioCommon_Result OH_AudioSessionManager_RegisterCurrentOutputDeviceChangeCallback(
    OH_AudioSessionManager *audioSessionManager,
    OH_AudioSession_CurrentOutputDeviceChangedCallback callback);

/**
 * @brief 取消注册当前输出设备变化回调。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param callback 用于返回音频设备变更信息的回调函数。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数callback为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 20
 */
OH_AudioCommon_Result OH_AudioSessionManager_UnregisterCurrentOutputDeviceChangeCallback(
    OH_AudioSessionManager *audioSessionManager,
    OH_AudioSession_CurrentOutputDeviceChangedCallback callback);

/**
 * @brief 获取音频可选设备列表。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param deviceUsage 用于设置要获取的设备种类。
 * @param audioDeviceDescriptorArray 音频设备描述符数组。
 *     <br>不再继续使用audioDeviceDescriptorArray指针时，请使用{@link OH_AudioSessionManager_ReleaseDevices}进行释放。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1.参数audioSessionManager为nullptr；
 *     <br>2.参数deviceUsage无效;
 *     <br>3.参数audioDeviceDescriptorArray为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 21
 */
OH_AudioCommon_Result OH_AudioSessionManager_GetAvailableDevices(
    OH_AudioSessionManager *audioSessionManager,
    OH_AudioDevice_Usage deviceUsage, OH_AudioDeviceDescriptorArray **audioDeviceDescriptorArray);

/**
 * @brief 注册可用设备更改回调。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param deviceUsage 用于设置要获取的设备种类。
 * @param callback 用于返回可用音频设备变更信息的回调函数。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数deviceUsage无效；
 *     <br>3. 参数callback为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 21
 */
OH_AudioCommon_Result OH_AudioSessionManager_RegisterAvailableDevicesChangeCallback(
    OH_AudioSessionManager *audioSessionManager, OH_AudioDevice_Usage deviceUsage,
    OH_AudioSession_AvailableDeviceChangedCallback callback);

/**
 * @brief 取消注册可用设备更改回调。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param callback 用于返回可用音频设备变更信息的回调函数。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数callback为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 21
 */
OH_AudioCommon_Result OH_AudioSessionManager_UnregisterAvailableDevicesChangeCallback(
    OH_AudioSessionManager *audioSessionManager,
    OH_AudioSession_AvailableDeviceChangedCallback callback);

/**
 * @brief 设置媒体输入设备。此功能不适用于呼叫录音，即{@link SourceType}为SOURCE_TYPE_VOICE_COMMUNICATION的场景不适用。
 * <br>在存在更高优先级的并发录音流的场景中，应用程序实际使用的输入设备可能与所选设备不同。
 * <br>应用程序可以使用{@link OH_AudioSessionManager_RegisterCurrentInputDeviceChangeCallback}注册一个回调来监听实际的输入设备。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param deviceDescriptor 目标设备。可用设备必须位于由{@link OH_AudioSessionManager_GetAvailableDevices}返回的数组中。
 *     <br>当传递nullptr时，系统将清除上一次的设置。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数audioSessionManager为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 21
 */
OH_AudioCommon_Result OH_AudioSessionManager_SelectMediaInputDevice(
    OH_AudioSessionManager *audioSessionManager, OH_AudioDeviceDescriptor *deviceDescriptor);

/**
 * @brief 获得通过{@link OH_AudioSessionManager_SelectMediaInputDevice}设置的媒体输入设备。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param audioDeviceDescriptor 通过{@link OH_AudioSessionManager_SelectMediaInputDevice}设置的媒体设备，如果没有设置，
 *     返回一个类型为AUDIO_DEVICE_TYPE_INVALID的设备。
 *     <br>不再继续使用audioDeviceDescriptor指针时，请使用{@link OH_AudioSessionManager_ReleaseDevice}进行释放。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数audioDeviceDescriptor为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 21
 */
OH_AudioCommon_Result OH_AudioSessionManager_GetSelectedMediaInputDevice(
    OH_AudioSessionManager *audioSessionManager, OH_AudioDeviceDescriptor **audioDeviceDescriptor);

/**
 * @brief 设置在使用蓝牙或星闪进行录音时，应用程序的设备偏好分类。应用程序可以在蓝牙或星闪连接之前设置此分类，系统将在设备连接时优先使用蓝牙或星闪进行录音。
 * <br>在更高优先级的并发录音流的场景中，应用程序实际使用的输入设备可能与当前设置的偏好设备不同。
 * <br>应用程序可以使用{@link OH_AudioSessionManager_RegisterCurrentInputDeviceChangeCallback}注册一个回调来监听实际的输入设备。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param category 在使用蓝牙或星闪进行录音时，应用程序的设备偏好分类。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数category错误。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 21
 */
OH_AudioCommon_Result OH_AudioSessionManager_SetBluetoothAndNearlinkPreferredRecordCategory(
    OH_AudioSessionManager *audioSessionManager,
    OH_AudioSession_BluetoothAndNearlinkPreferredRecordCategory category);

/**
 * @brief 获取应用程序设置的在使用蓝牙或星闪进行录音时的设备偏好分类。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param category 在使用蓝牙或星闪进行录音时，应用程序的设备偏好分类。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数category为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 21
 */
OH_AudioCommon_Result OH_AudioSessionManager_GetBluetoothAndNearlinkPreferredRecordCategory(
    OH_AudioSessionManager *audioSessionManager,
    OH_AudioSession_BluetoothAndNearlinkPreferredRecordCategory *category);

/**
 * @brief 注册音频会话管理器的输入设备更改回调。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param callback 用于返回音频输入设备变更信息的回调函数。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数callback为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_NO_MEMORY：内存不足。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 21
 */
OH_AudioCommon_Result OH_AudioSessionManager_RegisterCurrentInputDeviceChangeCallback(
    OH_AudioSessionManager *audioSessionManager,
    OH_AudioSession_CurrentInputDeviceChangedCallback callback);

/**
 * @brief 取消注册音频会话管理器的输入设备更改回调。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param callback 用于返回音频输入设备变更信息的回调函数。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数callback为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 21
 */
OH_AudioCommon_Result OH_AudioSessionManager_UnregisterCurrentInputDeviceChangeCallback(
    OH_AudioSessionManager *audioSessionManager,
    OH_AudioSession_CurrentInputDeviceChangedCallback callback);

/**
 * @brief 释放音频设备描述符对象。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param audioDeviceDescriptor 需要被释放的音频设备描述符对象。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioSessionManager为nullptr；
 *     <br>2. 参数audioDeviceDescriptor为nullptr。
 * @since 21
 */
OH_AudioCommon_Result OH_AudioSessionManager_ReleaseDevice(
    OH_AudioSessionManager *audioSessionManager,
    OH_AudioDeviceDescriptor *audioDeviceDescriptor);

/**
 * @brief 检查是否有其他应用正在播放MUSIC、MOVIE、AUDIOBOOK、GAME四种媒体类型的音频，已激活媒体类型的音频会话也将会被检查。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @return 是否有其他应用正在播放媒体类型的音频。true表示有，false表示没有。
 * @since 23
 */
bool OH_AudioSessionManager_IsOtherMediaPlaying(OH_AudioSessionManager *audioSessionManager);

/**
 * @brief 启用混音播放下接收静音播放建议通知功能。通常，当使用混音模式时，如果有其他应用的音频同时播放，此时两者会混合播放。部分场景下（如游戏或广播），应用可以通过启用静音建议通知，以为用户提供更好的体验。如果启用此功能，
 * 当订阅音频会话状态更改事件后静音建议和取消静音建议提示将通过{@link OH_AudioSession_StateChangedCallback}回调发送，该回调由
 * {@link OH_AudioSessionManager_RegisterStateChangeCallback}注册。
 * <br>收到静音建议表示其他应用程序开始播放音频，且播放的音频和本应用的音频不能混音。此功能仅支持已设置{@link OH_AudioSession_Scene}并激活模式为
 * {@link OH_AudioSession_ConcurrencyMode}.CONCURRENCY_MIX_WITH_OTHERS的音频会话使用。
 * <br>并且仅在激活音频会话期间生效一次，每次激活音频会话前都必须重新启用。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param enable 表示是否启用静音建议回调功能。true表示启用，false表示不启用。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数audioSessionManager为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：
 *     <br>1. 未设置音频会话场景。
 *     <br>2. 音频会话激活后调用此函数。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 23
 */
OH_AudioCommon_Result OH_AudioSessionManager_EnableMuteSuggestionWhenMixWithOthers(
    OH_AudioSessionManager *audioSessionManager, bool enable);

/**
 * @brief 设置音频会话行为参数（支持多种标志位的组合使用）。当音频会话在激活状态时调用此接口后，必须重新调用
 * 接口{@link OH_AudioSessionManager_ActivateAudioSession}使其生效。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}创建的音频会话管理实例。
 * @param behavior 音频会话行为标志，可以是单个标志，也可以是多个标志的按位OR组合。当前支持的音频会话行为
 *     详见{@link OH_AudioSession_BehaviorFlags}。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数为空指针或超出范围。
 *     <br>AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：非法状态。
 * @since 24
 */
OH_AudioCommon_Result OH_AudioSessionManager_SetBehavior(
    OH_AudioSessionManager *audioSessionManager, uint32_t behavior);

/**
 * @brief 应用将当前音频会话内录音流的自身静音状态传递给系统音频模块。该接口用于向系统音频模块上报当前音频会话内录音流的静音状态，不会改变录音流的实际静音状态。当前仅在部分PC/2in1设备上，
 * 系统音频模块会基于设置的状态调整策略以降低功耗。该接口仅在当前音频会话存在运行中的录音流时允许调用，否则返回错误码AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE。若某条录音流同时调用了流级接口和本接口，
 * 流级接口设置优先级更高，以流级接口设置值为准。
 *
 * @param audioSessionManager 指向{@link OH_AudioManager_GetAudioSessionManager}返回的音频会话管理实例。
 * @param mute 当应用自身已将录音流静音时，传入true，表示将当前应用下的录音流标记为静音。解除静音时，传入false。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数audioSessionManager为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：操作状态异常，当前进程不存在运行中的录音流。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：系统异常，例如系统服务异常退出等。
 * @since 24
 */
OH_AudioCommon_Result OH_AudioSessionManager_SetCaptureMuteHint(
    OH_AudioSessionManager *audioSessionManager, bool mute);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_SESSION_MANAGER_H
/** @} */