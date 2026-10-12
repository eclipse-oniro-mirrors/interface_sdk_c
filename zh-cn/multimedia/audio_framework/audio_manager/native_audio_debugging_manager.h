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
 * @brief 提供音频模块C接口定义，可用于实现音频播放、录制和相关的音量、设备、会话管理等功能，
 * 服务于媒体播放、语音通话、游戏音频等音频业务开发场景。
 *
 * @since 26.0.0
 */

/**
 * @file native_audio_debugging_manager.h
 *
 * @brief 本文件提供适用于音频调试场景使用的接口。
 * <br>针对音频开发的特点和常见问题，系统将开发者调试音频功能所需要的系统内部信息通过接口提供出去，
 * 便于开发者查看应用内音频业务对象的状态，用于定位用户音频功能问题。
 * <br>使用调试接口首先需要通过{@link OH_AudioManager_GetAudioDebuggingManager}
 * 获取音频调试管理器实例，通过该对象调用其他音频调试接口，包括应用快照、音频播放快照、音频录制快照等。
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
#include "native_audio_session_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 声明音频调试管理结构体，该结构体用于调用输出音频调试信息功能接口。
 *
 * @since 26.0.0
 */
typedef struct OH_AudioDebuggingManager OH_AudioDebuggingManager;

/**
 * @brief 获取音频调试管理器实例，该实例为单例，用于调用其他音频调试功能接口。
 *
 * @param manager [out] 指向OH_AudioDebuggingManager指针的地址，用于接收音频调试管理器实例。
 * @return <ul>
 *         <li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *         <li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数manager为空指针。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioDebuggingManager(OH_AudioDebuggingManager **manager);

/**
 * @brief 打印当前进程中所有音频模块的快照信息。
 * <br>应用快照包含当前应用进程中所有播放快照、录音快照、耳返快照和会话快照信息，是不同场景快照的汇总，
 * 适用于需要一次性获取整体音频运行状态的场景。
 *
 * @param manager [in] 通过{@link OH_AudioManager_GetAudioDebuggingManager}获取的音频调试管理器实例。
 * @param fd [in] 文件描述符。当fd小于0或不可写时，快照信息将输出到运行日志，否则输出到fd指向的文件。
 * @return <ul>
 *         <li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *         <li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数manager为空指针。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintAppInfo(OH_AudioDebuggingManager *manager, int32_t fd);

/**
 * @brief 打印指定音频播放实例的快照信息。
 * <br>音频播放快照记录播放流参数、通路信息、音量、设备信息、焦点状态、历史错误记录等信息，
 * 适用于排查播放无声、音量异常、焦点被抢占等问题。
 *
 * @param manager [in] 通过{@link OH_AudioManager_GetAudioDebuggingManager}获取的音频调试管理器实例。
 * @param renderer [in] 指向目标音频播放实例的指针，用于打印快照信息。
 * @param fd [in] 文件描述符。当fd小于0或不可写时，快照信息将输出到运行日志，否则输出到fd指向的文件。
 * @return <ul>
 *         <li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *         <li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数manager或renderer为空指针。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintRendererInfo(OH_AudioDebuggingManager *manager,
    OH_AudioRenderer *renderer, int32_t fd);

/**
 * @brief 打印指定录音实例的快照信息。
 * <br>录音快照记录录音流参数、通路信息、录音时间戳、设备信息、溢出计数、历史错误记录等信息，
 * 适用于排查录音无数据、录音卡顿等问题。
 *
 * @param manager [in] 通过{@link OH_AudioManager_GetAudioDebuggingManager}获取的音频调试管理器实例。
 * @param capturer [in] 指向目标录音实例的指针，用于打印快照信息。
 * @param fd [in] 文件描述符。当fd小于0或不可写时，快照信息将输出到运行日志，否则输出到fd指向的文件。
 * @return <ul>
 *         <li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *         <li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数manager或capturer为空指针。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintCapturerInfo(OH_AudioDebuggingManager *manager,
    OH_AudioCapturer *capturer, int32_t fd);

/**
 * @brief 打印指定音频会话的快照信息。
 * <br>音频会话快照记录会话状态、并发策略、场景类型、设备信息、关联音频流等信息，
 * 适用于排查会话激活异常、并发策略不生效等问题。
 *
 * @param manager [in] 通过{@link OH_AudioManager_GetAudioDebuggingManager}获取的音频调试管理器实例。
 * @param session [in] 指向目标会话管理器实例的指针，用于打印快照信息。
 * @param fd [in] 文件描述符。当fd小于0或不可写时，快照信息将输出到运行日志，否则输出到fd指向的文件。
 * @return <ul>
 *         <li>AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。</li>
 *         <li>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数manager或session为空指针。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDebuggingManager_PrintSessionInfo(OH_AudioDebuggingManager *manager,
    OH_AudioSessionManager *session, int32_t fd);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_DEBUGGING_MANAGER_H
/** @} */