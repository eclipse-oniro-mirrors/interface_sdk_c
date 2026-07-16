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
 * @file native_avplaybackstate.h
 *
 * @brief 提供播放状态的定义。
 *
 * @library libohavsession.so
 * @syscap SystemCapability.Multimedia.AVSession.Core
 * @kit AVSessionKit
 * @since 23
 * @version 1.0
 */

#ifndef NATIVE_AVPLAYBACKSTATE_H
#define NATIVE_AVPLAYBACKSTATE_H

#include <stdint.h>
#include "native_avsession_base.h"
#include "native_avsession_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 播放状态对象。
 *
 * @since 23
 * @version 1.0
 */
typedef struct OH_AVSession_AVPlaybackState OH_AVSession_AVPlaybackState;

/**
 * @brief 媒体播放位置的相关属性。
 *
 * @since 13
 */
typedef struct AVSession_PlaybackPosition {
    /**
     * @brief 已用时间，单位毫秒（ms）。
     */
    int64_t elapsedTime;

    /**
     * @brief 更新时间，单位毫秒（ms）。
     */
    int64_t updateTime;
} AVSession_PlaybackPosition;

/**
 * @brief 获取播放的状态。
 *
 * @param playbackState 表示播放状态实例对象。
 * @param state 指针变量将返回播放状态值。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER 参数验证失败原因如下：\n
 *                                                         1. 参数playbackState为nullptr。\n
 *                                                         2. 参数state为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVSession_GetPlaybackState(OH_AVSession_AVPlaybackState* playbackState,
    AVSession_PlaybackState* state);

/**
 * @brief 获取播放状态的位置。
 *
 * @param playbackState 表示播放状态实例对象。
 * @param position 指针变量将返回播放位置值。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER 参数验证失败原因如下：\n
 *                                                         1. 参数playbackState为nullptr。\n
 *                                                         2. 参数position为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVSession_GetPlaybackPosition(OH_AVSession_AVPlaybackState* playbackState,
    AVSession_PlaybackPosition* position);

/**
 * @brief 获取播放状态的倍速。
 *
 * @param playbackState 表示播放状态实例对象。
 * @param speed 指针变量将返回播放倍速值。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER 参数验证失败原因如下：\n
 *                                                         1. 参数playbackState为nullptr。\n
 *                                                         2. 参数speed为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVSession_GetPlaybackSpeed(OH_AVSession_AVPlaybackState* playbackState,
    int32_t* speed);

/**
 * @brief 获取投播音量
 *
 * @param playbackState OH_AVSession_AVPlaybackState对象指针
 * @param volume 返回的音量
 * @return 返回调用执行结果
 * @since 23
 */
AVSession_ErrCode OH_AVSession_GetPlaybackVolume(OH_AVSession_AVPlaybackState* playbackState,
    int32_t* volume);

#ifdef __cplusplus
}
#endif

#endif /* NATIVE_AVPLAYBACKSTATE_H */
/** @} */