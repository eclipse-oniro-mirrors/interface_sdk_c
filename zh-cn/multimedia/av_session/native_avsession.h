/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @syscap SystemCapability.Multimedia.AVSession.Core
 *
 * @since 13
 * @version 1.0
 */

/**
 * @file native_avsession.h
 *
 * @brief 提供媒体会话定义，可用于设置元数据、播放状态信息等操作。
 *
 * @library libohavsession.so
 * @syscap SystemCapability.Multimedia.AVSession.Core
 * @kit AVSessionKit
 * @since 13
 * @version 1.0
 */

#ifndef NATIVE_AVSESSION_H
#define NATIVE_AVSESSION_H

#include <stdbool.h>
#include <stdint.h>
#include "native_avsession_errors.h"
#include "native_avsession_base.h"
#include "native_avmetadata.h"
#include "native_avplaybackstate.h"
#include "native_deviceinfo.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 播控会话结构体定义。
 *
 * 可通过{@link OH_AVSession_Create}创建一个会话对象。
 *
 * @since 13
 * @version 1.0
 */
typedef struct OH_AVSession OH_AVSession;

/**
 * @brief 声明投播控制器对象。
 *
 * 该对象可以使用{@link OH_AVSession_CreateAVCastController}函数创建。
 *
 * @since 23
 * @version 1.0
 */
typedef struct OH_AVCastController OH_AVCastController;

/**
 * @brief 通用的执行播控命令的回调。
 *
 * @param session the OH_AVSession instance pointer.
 * @param command playback command
 * @param userData userdata which is passed by register.
 * @since 13
 * @version 1.0
 */
typedef AVSessionCallback_Result (*OH_AVSessionCallback_OnCommand)(OH_AVSession* session,
    AVSession_ControlCommand command, void* userData);

/**
 * @brief 快进的回调。
 *
 * @param session the OH_AVSession instance pointer.
 * @param seekTime forward time, described by milliseconds.
 * @param userData userdata which is passed by register.
 * @since 13
 * @version 1.0
 */
typedef AVSessionCallback_Result (*OH_AVSessionCallback_OnFastForward)(OH_AVSession* session,
    uint32_t seekTime, void* userData);

/**
 * @brief 快退的回调。
 *
 * @param session the OH_AVSession instance pointer.
 * @param seekTime rewind time, described by milliseconds.
 * @param userData userdata which is passed by register.
 * @since 13
 * @version 1.0
 */
typedef AVSessionCallback_Result (*OH_AVSessionCallback_OnRewind)(OH_AVSession* session,
    uint32_t seekTime, void* userData);

/**
 * @brief 进度调节的回调。
 *
 * @param session the OH_AVSession instance pointer.
 * @param seekTime position after seek, described by milliseconds.
 * @param userData userdata which is passed by register.
 * @since 13
 * @version 1.0
 */
typedef AVSessionCallback_Result (*OH_AVSessionCallback_OnSeek)(OH_AVSession* session,
    uint64_t seekTime, void* userData);

/**
 * @brief 设置循环模式的回调。
 *
 * @param session the OH_AVSession instance pointer.
 * @param curLoopMode current loop mode.
 * @param userData userdata which is passed by register.
 * @since 13
 * @version 1.0
 */
typedef AVSessionCallback_Result (*OH_AVSessionCallback_OnSetLoopMode)(OH_AVSession* session,
    AVSession_LoopMode curLoopMode, void* userData);

/**
 * @brief 收藏的回调。
 *
 * @param session the OH_AVSession instance pointer.
 * @param assetId the assetId for which the favorite status needs to be switched.
 * @param userData userdata which is passed by register.
 * @since 13
 * @version 1.0
 */
typedef AVSessionCallback_Result (*OH_AVSessionCallback_OnToggleFavorite)(OH_AVSession* session,
    const char* assetId, void* userData);

/**
 * @brief 设备变化的回调。
 *
 * @param session the OH_AVSession instance pointer.
 * @param state the {@link AVSession_ConnectionState} of output device.
 * @param outputDeviceInfo the {@link AVSession_OutputDeviceInfo} pointer variable which will be set
 * current output device info. Do not release the outputDeviceInfo pointer separately,
 * instead call {@link OH_AVSession_ReleaseOutputDevice} to release the outputDeviceInfo when it is not used anymore.
 * @since 23
 * @version 1.0
 */
typedef AVSessionCallback_Result (*OH_AVSessionCallback_OutputDeviceChange)(OH_AVSession* session,
    AVSession_ConnectionState state, AVSession_OutputDeviceInfo* outputDeviceInfo);

/**
 * @brief 创建会话对象。
 *
 * @param sessionType 会话类型{@link AVSession_Type}。
 * @param sessionTag 会话标签。
 * @param bundleName 创建会话的包名。
 * @param abilityName 创建会话的Ability组件名。
 * @param avsession 返回的媒体会话对象。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数sessionType无效。\n
 *                                         2. 参数sessionTag为nullptr。\n
 *                                         3. 参数bundleName为nullptr。\n
 *                                         4. 参数abilityName为nullptr。\n
 *                                         5. 参数avsession为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_Create(AVSession_Type sessionType, const char* sessionTag,
    const char* bundleName, const char* abilityName, OH_AVSession** avsession);

/**
 * @brief 销毁会话对象。
 *
 * @param avsession 媒体会话对象。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：参数avsession为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_Destroy(OH_AVSession* avsession);

/**
 * @brief 激活会话。
 *
 * @param avsession 媒体会话对象。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：参数avsession为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_Activate(OH_AVSession* avsession);

/**
 * @brief 取消激活媒体会话。
 *
 * @param avsession 媒体会话对象。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：参数avsession为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_Deactivate(OH_AVSession* avsession);

/**
 * @brief 获取会话类型。
 *
 * @param avsession 媒体会话对象。
 * @param sessionType 返回的会话类型。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数sessionType为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_GetSessionType(OH_AVSession* avsession, AVSession_Type* sessionType);

/**
 * @brief 获取会话ID。
 *
 * @param avsession 媒体会话对象。
 * @param sessionId 返回的会话ID。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数sessionId为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_GetSessionId(OH_AVSession* avsession, const char** sessionId);

/**
 * @brief 设置媒体元数据。
 *
 * @param avsession 媒体会话对象。
 * @param avmetadata 设置媒体元数据信息。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数avmetadata为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_SetAVMetadata(OH_AVSession* avsession, OH_AVMetadata* avmetadata);

/**
 * @brief 设置播放状态。
 *
 * @param avsession 媒体会话对象。
 * @param playbackState 播放状态。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数playbackState是无效的。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_SetPlaybackState(OH_AVSession* avsession,
    AVSession_PlaybackState playbackState);

/**
 * @brief 设置播放位置。
 *
 * @param avsession 媒体会话对象。
 * @param playbackPosition 播放位置对象。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数playbackPosition为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_SetPlaybackPosition(OH_AVSession* avsession,
    AVSession_PlaybackPosition* playbackPosition);

/**
 * @brief 设置收藏状态。
 *
 * @param avsession 媒体会话对象。
 * @param favorite 收藏状态，true表示收藏，false表示取消收藏。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：参数avsession为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_SetFavorite(OH_AVSession* avsession, bool favorite);

/**
 * @brief 设置循环模式。
 *
 * @param avsession 媒体会话对象。
 * @param loopMode 循环模式。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数loopMode是无效的。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_SetLoopMode(OH_AVSession* avsession, AVSession_LoopMode loopMode);

/**
 * @brief 请求使能远程投播。
 *
 * @param avsession 媒体会话对象。
 * @param enabled 是否使能远程投播。true表示使能，false表示不使能。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_CODE_SESSION_NOT_EXIST：会话不存在。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：参数avsession为nullptr。\n
 * @since 23
 */
AVSession_ErrCode OH_AVSession_SetRemoteCastEnabled(OH_AVSession* avsession, bool enabled);

/**
 * @brief 注册通用播控的回调。
 *
 * @param avsession 媒体会话对象。
 * @param command 播控的控制命令。
 * @param callback 控制命令的回调。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_CODE_COMMAND_INVALID：控制命令无效。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_RegisterCommandCallback(OH_AVSession* avsession,
    AVSession_ControlCommand command, OH_AVSessionCallback_OnCommand callback, void* userData);

/**
 * @brief 取消注册通用播控的回调。
 *
 * @param avsession 媒体会话对象。
 * @param command 播控的控制命令。
 * @param callback 控制命令的回调。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_CODE_COMMAND_INVALID：控制命令无效。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_UnregisterCommandCallback(OH_AVSession* avsession,
    AVSession_ControlCommand command, OH_AVSessionCallback_OnCommand callback);

/**
 * @brief 注册快进的回调。
 *
 * @param avsession 媒体会话对象。
 * @param callback 快进命令的回调。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_RegisterForwardCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnFastForward callback, void* userData);

/**
 * @brief 取消注册快进的回调。
 *
 * @param avsession 媒体会话对象。
 * @param callback 快进命令的回调。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_UnregisterForwardCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnFastForward callback);

/**
 * @brief 注册快退的回调。
 *
 * @param avsession 媒体会话对象。
 * @param callback 快退命令的回调。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_RegisterRewindCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnRewind callback, void* userData);

/**
 * @brief 取消注册快退的回调。
 *
 * @param avsession 媒体会话对象。
 * @param callback 快退命令的回调。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_UnregisterRewindCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnRewind callback);

/**
 * @brief 注册跳转的回调。
 *
 * @param avsession 媒体会话对象。
 * @param callback 跳转命令的回调。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_RegisterSeekCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnSeek callback, void* userData);

/**
 * @brief 取消注册跳转的回调。
 *
 * @param avsession 媒体会话对象。
 * @param callback 跳转命令的回调。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_UnregisterSeekCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnSeek callback);

/**
 * @brief 注册设置循环模式的回调。
 *
 * @param avsession 媒体会话对象。
 * @param callback 设置循环模式命令的回调。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_RegisterSetLoopModeCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnSetLoopMode callback, void* userData);

/**
 * @brief 取消注册设置循环模式的回调。
 *
 * @param avsession 媒体会话对象。
 * @param callback 设置循环模式命令的回调。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_UnregisterSetLoopModeCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnSetLoopMode callback);

/**
 * @brief 设置收藏的回调。
 *
 * @param avsession 媒体会话对象。
 * @param callback 设置收藏命令的回调。
 * @param userData 指向通过回调函数传递的应用数据指针。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_RegisterToggleFavoriteCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnToggleFavorite callback, void* userData);

/**
 * @brief 取消设置收藏的回调。
 *
 * @param avsession 媒体会话对象。
 * @param callback 设置收藏命令的回调。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 13
 */
AVSession_ErrCode OH_AVSession_UnregisterToggleFavoriteCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnToggleFavorite callback);

/**
 * @brief 注册设备变化的回调。
 *
 * @param avsession 媒体会话对象。
 * @param callback 设置设备变化的回调。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVSession_RegisterOutputDeviceChangeCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OutputDeviceChange callback);

/**
 * @brief 取消注册设备变化的回调。
 *
 * @param avsession 媒体会话对象。
 * @param callback 设置设备变化的回调。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVSession_UnregisterOutputDeviceChangeCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OutputDeviceChange callback);

/**
 * @brief 获取已经存在的媒体会话对象。
 * 当不再使用媒体会话对象时，调用{@link OH_AVSession_Destroy}进行释放。
 *
 * @param sessionTag 应用设置的会话自定义标签。
 * @param bundleName 应用包名。
 * @param abilityName 应用的Ability组件名。
 * @param avsession 用于接收OH_AVSession的变量指针。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_CODE_SESSION_NOT_EXIST：会话不存在。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数sessionTag无效。\n
 *                                         2. 参数bundleName无效。\n
 *                                         3. 参数abilityName无效。\n
 *                                         4. 参数avsession为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVSession_AcquireSession(const char* sessionTag, const char* bundleName, const char* abilityName,
    OH_AVSession** avsession);

/**
 * @brief 创建投播控制器对象。
 * 当投播控制器对象不再使用时，调用{@link OH_AVCastController_Destroy}进行释放。
 *
 * @param avsession 媒体会话对象。
 * @param avcastcontroller 指向用于接收投播控制器OH_AVCastController的变量的指针。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_CODE_SESSION_NOT_EXIST：会话不存在。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数avcastcontroller为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVSession_CreateAVCastController(OH_AVSession* avsession, OH_AVCastController** avcastcontroller);

/**
 * @brief 停止当前投播并断开设备连接。
 *
 * @param avsession 媒体会话对象。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_CODE_SESSION_NOT_EXIST：会话不存在。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：参数avsession为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVSession_StopCasting(OH_AVSession* avsession);

/**
 * @brief 获取当前输出设备。
 *
 * @param avsession 媒体会话对象。
 * @param outputDeviceInfo 指向用于接收输出设备信息AVSession_OutputDeviceInfo的变量的指针。
 * 不可以单独释放outputDeviceInfo指针。
 * 当不再使用outputDeviceInfo时，调用{@link OH_AVSession_ReleaseOutputDevice}进行释放。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：会话服务异常。\n
 *         AV_SESSION_ERR_CODE_SESSION_NOT_EXIST：会话不存在。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数outputDeviceInfo为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVSession_AcquireOutputDevice(OH_AVSession* avsession,
    AVSession_OutputDeviceInfo** outputDeviceInfo);

/**
 * @brief 释放输出设备对象。
 *
 * @param avsession 媒体会话对象。
 * @param outputDeviceInfo 应当释放的输出设备。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avsession为nullptr。\n
 *                                         2. 参数outputDeviceInfo为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVSession_ReleaseOutputDevice(OH_AVSession* avsession,
    AVSession_OutputDeviceInfo *outputDeviceInfo);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSESSION_H
/** @} */
