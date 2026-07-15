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
 * @addtogroup OHAudio
 * @{
 *
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 26.0.0
 */

/**
 * @file native_audio_debugging_manager.h
 *
 * @brief Declare audio debugging manager related interfaces.
 *
 * The interfaces in this file are used for audio debugging, helping the developers to
 * analyze issues when implementing audio related functions more efficiently.
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 26.0.0
 */

#ifndef NATIVE_AUDIO_DEBUGGING_MANAGER_H
#define NATIVE_AUDIO_DEBUGGING_MANAGER_H

#include "native_audio_common.h"
#include "native_audiostream_base.h"
#include "native_audiorenderer.h"
#include "native_audiocapturer.h"
#include "native_audio_session_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 声明音频调试管理器。
 * 音频调试管理器为开发者提供了很多功能，可以通过
 * 音频系统运行时信息。
 *
 * @since 26.0.0
 */
typedef struct OH_AudioDebuggingManager OH_AudioDebuggingManager;

/**
 * @brief 获取音频调试管理器句柄，它是一个单例。
 *
 * @param manager 获取{@link OH_AudioDebugManager}实例的输出参数。
 * @return 如果执行成功，则返回{@link AUDIOCOMMON_RESULT_SUCCESS}。
 * {@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}管理器的参数为nullptr。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioDebuggingManager(OH_AudioDebuggingManager **manager);

/**
 * @brief 打印当前应用进程的完整音频运行时快照。
 * 快照将包含所有音频渲染器、捕获器、音频会话信息。
 * 请注意，不同版本的信息详情和格式可能会有所不同，它只能用于
 * 手动调试，用户不应依赖实际功能实现或文件的信息
 * 内容提取。
 *
 * @param manager {@link OH_AudioManager_GetAudioDebugsManager}提供的{@link OH_AudioDebugsManager}句柄。
 * @param fd 是一个文件描述符，表示快照信息将要写入的位置。
 * 如果fd小于0或者不可写，则会将快照信息打印到运行日志中。
 * 否则快照将写入文件。
 * @return 如果执行成功，则返回{@link AUDIOCOMMON_RESULT_SUCCESS}。
 * {@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}管理器的参数为nullptr。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintAppInfo(OH_AudioDebuggingManager *manager, int32_t fd);

/**
 * @brief 打印目标音频渲染器实例的完整音频运行时快照。
 * 快照将包含流、管道、卷和设备信息。
 * 请注意，不同版本的信息详情和格式可能会有所不同，它只能用于
 * 手动调试，用户不应依赖实际功能实现或文件的信息
 * 内容提取。
 *
 * @param manager {@link OH_AudioManager_GetAudioDebugsManager}提供的{@link OH_AudioDebugsManager}句柄。
 * @param renderer 指向要打印快照的目标音频渲染器实例的指针。
 * @param fd 是一个文件描述符，表示快照信息将要写入的位置。
 * 如果fd小于0或者不可写，则会将快照信息打印到运行日志中。
 * 否则快照将写入文件。
 * @return 如果执行成功，则返回{@link AUDIOCOMMON_RESULT_SUCCESS}。
 * {@链接AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1.管理器的参数为nullptr；
 * 2.渲染器的param为nullptr；
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintRendererInfo(OH_AudioDebuggingManager *manager,
    OH_AudioRenderer *renderer, int32_t fd);

/**
 * @brief 打印目标音频捕获程序实例的完整音频运行时快照。
 * 快照将包含流、管道、卷和设备信息。
 * 请注意，不同版本的信息详情和格式可能会有所不同，它只能用于
 * 手动调试，用户不应依赖实际功能实现或文件的信息
 * 内容提取。
 *
 * @param manager {@link OH_AudioManager_GetAudioDebugsManager}提供的{@link OH_AudioDebugsManager}句柄。
 * @param capturer 指向要打印快照的目标音频捕获器实例的指针。
 * @param fd 是一个文件描述符，表示快照信息将要写入的位置。
 * 如果fd小于0或者不可写，则会将快照信息打印到运行日志中。
 * 否则快照将写入文件。
 * @return 如果执行成功，则返回{@link AUDIOCOMMON_RESULT_SUCCESS}。
 * {@链接AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1.管理器的参数为nullptr；
 * 2.捕获器的参数为nullptr；
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintCapturerInfo(OH_AudioDebuggingManager *manager,
    OH_AudioCapturer *capturer, int32_t fd);

/**
 * @brief 打印目标音频会话管理器实例的完整音频运行时快照。
 * 快照将包含会话状态、场景、策略和设备信息。
 * 请注意，不同版本的信息详情和格式可能会有所不同，它只能用于
 * 手动调试，用户不应依赖实际功能实现或文件的信息
 * 内容提取。
 *
 * @param manager {@link OH_AudioManager_GetAudioDebugsManager}提供的{@link OH_AudioDebugsManager}句柄。
 * @param session 指向要打印快照的目标音频会话管理器实例的指针。
 * @param fd 是一个文件描述符，表示快照信息将要写入的位置。
 * 如果fd小于0或者不可写，则会将快照信息打印到运行日志中。
 * 否则快照将写入文件。
 * @return 如果执行成功，则返回{@link AUDIOCOMMON_RESULT_SUCCESS}。
 * {@链接AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1.管理器的参数为nullptr；
 * 2.session的param为nullptr；
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintSessionInfo(OH_AudioDebuggingManager *manager,
    OH_AudioSessionManager *session, int32_t fd);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_DEBUGGING_MANAGER_H
/** @} */