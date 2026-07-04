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
 * @brief Provide the definition of the C interface for the avsession module.
 *
 * @syscap SystemCapability.Multimedia.AVSession.Core
 *
 * @since 13
 * @version 1.0
 */

/**
 * @file native_avsession.h
 *
 * @brief Declare avsession interface.
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
 * @brief AVSession object
 *
 * A pointer can be created using {@link OH_AVSession_Create} method.
 *
 * @since 13
 * @version 1.0
 */
typedef struct OH_AVSession OH_AVSession;

/**
 * @brief OH_AVSession_GetAVCastController对象定义
 *
 * @since 23
 * @version 1.0
 */
typedef struct OH_AVCastController OH_AVCastController;

/**
 * @brief Declaring the callback struct for playback command
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
 * @brief Declaring the callback struct for forward command
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
 * @brief Declaring the callback struct for rewind command
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
 * @brief Declaring the callback struct for seek command
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
 * @brief Declaring the callback struct for set loop mode command
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
 * @brief Declaring the callback struct for toggle favorite command
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
 * @brief 设备回调函数定义
 *
 * @param session 传入的OH_AVSession对象
 * @param state 设备连接状态
 * @param outputDeviceInfothe 返回的 AVSession_OutputDeviceInfo 对象指针
 * @since 23
 * @version 1.0
 */
typedef AVSessionCallback_Result (*OH_AVSessionCallback_OutputDeviceChange)(OH_AVSession* session,
    AVSession_ConnectionState state, AVSession_OutputDeviceInfo* outputDeviceInfo);

/**
 * @brief 创建OH_AVSession对象
 *
 * @param sessionType 会话类型
 * @param sessionTag 会话TAG
 * @param bundleName 应用包名
 * @param abilityName 应用abilityname
 * @param avsession 返回的OH_AVSession指针对象
 * @return 返回创建结果
 * @since 13
 */
AVSession_ErrCode OH_AVSession_Create(AVSession_Type sessionType, const char* sessionTag,
    const char* bundleName, const char* abilityName, OH_AVSession** avsession);

/**
 * @brief Request to destroy the avsession.
 *
 * @param avsession The avsession instance pointer
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER} The param of avsession is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_Destroy(OH_AVSession* avsession);

/**
 * @brief Activate the avsession.
 *
 * @param avsession The avsession instance pointer
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER} The param of avsession is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_Activate(OH_AVSession* avsession);

/**
 * @brief Deactivate the avsession.
 *
 * @param avsession The avsession instance pointer
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER} The param of avsession is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_Deactivate(OH_AVSession* avsession);

/**
 * @brief Get session type.
 *
 * @param avsession The avsession instance pointer
 * @param sessionType The returned session type
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is invalid.
 *                                                 2. The param of sessionType is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_GetSessionType(OH_AVSession* avsession, AVSession_Type* sessionType);

/**
 * @brief Get session id.
 *
 * @param avsession The avsession instance pointer
 * @param sessionId The returned session id
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of sessionId is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_GetSessionId(OH_AVSession* avsession, const char** sessionId);

/**
 * @brief Request to set av metadata.
 *
 * @param avsession The avsession instance pointer
 * @param avmetadata The metadata to set
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of avmetadata is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_SetAVMetadata(OH_AVSession* avsession, OH_AVMetadata* avmetadata);

/**
 * @brief Request to set av playbackstate.
 *
 * @param avsession The avsession instance pointer
 * @param playbackState The playbackState to set
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of playbackState is invalid.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_SetPlaybackState(OH_AVSession* avsession,
    AVSession_PlaybackState playbackState);

/**
 * @brief Request to set playback position.
 *
 * @param avsession The avsession instance pointer
 * @param playbackPosition The playbackPosition to set
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of playbackPosition is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_SetPlaybackPosition(OH_AVSession* avsession,
    AVSession_PlaybackPosition* playbackPosition);

/**
 * @brief Request to set favorite state.
 *
 * @param avsession The avsession instance pointer
 * @param favorite true means making the resource to be liked, false means dislike.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER} The param of avsession is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_SetFavorite(OH_AVSession* avsession, bool favorite);

/**
 * @brief Request to set loop mode.
 *
 * @param avsession The avsession instance pointer
 * @param loopMode The loopmode to be set for playback.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of loopMode is invalid.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_SetLoopMode(OH_AVSession* avsession, AVSession_LoopMode loopMode);

/**
 * @brief 使能投播
 *
 * @param avsession OH_AVSession对象指针
 * @param enabled 是否使能投播
 * @return 返回调用执行结果
 * @since 23
 */
AVSession_ErrCode OH_AVSession_SetRemoteCastEnabled(OH_AVSession* avsession, bool enabled);

/**
 * @brief Request to register command callback.
 *
 * @param avsession The avsession instance pointer
 * @param command The control command type to be registered.
 * @param callback the {@link OH_AVSessionCallback_OnCommand} to be registered.
 * @param userData User data which is passed by user.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_CODE_COMMAND_INVALID} The command is invalid.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of callback is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_RegisterCommandCallback(OH_AVSession* avsession,
    AVSession_ControlCommand command, OH_AVSessionCallback_OnCommand callback, void* userData);

/**
 * @brief Request to unregister command callback.
 *
 * @param avsession The avsession instance pointer
 * @param command The control command type to be unregistered.
 * @param callback the {@link OH_AVSessionCallback_OnCommand} to be unregistered.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_CODE_COMMAND_INVALID} The command is invalid.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of callback is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_UnregisterCommandCallback(OH_AVSession* avsession,
    AVSession_ControlCommand command, OH_AVSessionCallback_OnCommand callback);

/**
 * @brief Request to register fastforward callback.
 *
 * @param avsession The avsession instance pointer
 * @param callback the {@link OH_AVSessionCallback_OnFastForward} to be registered.
 * @param userData User data which is passed by user.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of callback is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_RegisterForwardCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnFastForward callback, void* userData);

/**
 * @brief Request to unregister fastforward callback.
 *
 * @param avsession The avsession instance pointer
 * @param callback the {@link OH_AVSessionCallback_OnFastForward} to be unregistered.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of callback is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_UnregisterForwardCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnFastForward callback);

/**
 * @brief Request to register rewind callback.
 *
 * @param avsession The avsession instance pointer
 * @param callback the {@link OH_AVSessionCallback_OnRewind} to be registered.
 * @param userData User data which is passed by user.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of callback is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_RegisterRewindCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnRewind callback, void* userData);

/**
 * @brief Request to unregister rewind callback.
 *
 * @param avsession The avsession instance pointer
 * @param callback the {@link OH_AVSessionCallback_OnRewind} to be unregistered.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of callback is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_UnregisterRewindCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnRewind callback);

/**
 * @brief Request to register seek callback.
 *
 * @param avsession The avsession instance pointer
 * @param callback the {@link OH_AVSessionCallback_OnSeek} to be registered.
 * @param userData User data which is passed by user.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of callback is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_RegisterSeekCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnSeek callback, void* userData);

/**
 * @brief Request to unregister seek callback.
 *
 * @param avsession The avsession instance pointer
 * @param callback the {@link OH_AVSessionCallback_OnSeek} to be unregistered.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of callback is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_UnregisterSeekCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnSeek callback);

/**
 * @brief Request to register set loopmode callback.
 *
 * @param avsession The avsession instance pointer
 * @param callback the {@link OH_AVSessionCallback_OnSetLoopMode} to be registered.
 * @param userData User data which is passed by user.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of callback is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_RegisterSetLoopModeCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnSetLoopMode callback, void* userData);

/**
 * @brief Request to unregister set loopmode callback.
 *
 * @param avsession The avsession instance pointer
 * @param callback the {@link OH_AVSessionCallback_OnSetLoopMode} to be unregistered.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of callback is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_UnregisterSetLoopModeCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnSetLoopMode callback);

/**
 * @brief Request to register toggle favorite callback.
 *
 * @param avsession The avsession instance pointer
 * @param callback the {@link OH_AVSessionCallback_OnToggleFavorite} to be registered.
 * @param userData User data which is passed by user.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of callback is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_RegisterToggleFavoriteCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnToggleFavorite callback, void* userData);

/**
 * @brief Request to unregister toggle favorite callback.
 *
 * @param avsession The avsession instance pointer
 * @param callback the {@link OH_AVSessionCallback_OnToggleFavorite} to be unregistered.
 * @return Function result code：
 *         {@link AV_SESSION_ERR_SUCCESS} If the execution is successful.
 *         {@link AV_SESSION_ERR_SERVICE_EXCEPTION} Internal server error.
 *         {@link AV_SESSION_ERR_INVALID_PARAMETER}
 *                                                 1. The param of avsession is nullptr.
 *                                                 2. The param of callback is nullptr.
 * @since 13
 */
AVSession_ErrCode OH_AVSession_UnregisterToggleFavoriteCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OnToggleFavorite callback);

/**
 * @brief 注册设备回调
 *
 * @param avsession OH_AVSession对象指针
 * @param callback 设备回调
 * @return 返回调用执行结果
 * @since 23
 */
AVSession_ErrCode OH_AVSession_RegisterOutputDeviceChangeCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OutputDeviceChange callback);

/**
 * @brief 去注册设备回调
 *
 * @param avsession OH_AVSession对象指针
 * @param callback 设备回调
 * @return 返回调用执行结果
 * @since 23
 */
AVSession_ErrCode OH_AVSession_UnregisterOutputDeviceChangeCallback(OH_AVSession* avsession,
    OH_AVSessionCallback_OutputDeviceChange callback);

/**
 * @brief 获取当前已经存在的OH_AVSession对象
 *
 * @param sessionTag 会话tag
 * @param bundleName 创建会话的应用包名
 * @param abilityName 创建会话的ability名称
 * @param avsession 返回的指向OH_AVSession的指针
 * @return 返回执行结果
 * @since 23
 */
AVSession_ErrCode OH_AVSession_AcquireSession(const char* sessionTag, const char* bundleName, const char* abilityName,
    OH_AVSession** avsession);

/**
 * @brief 创建AVCastController 对象用于投播
 *
 * @param avsession OHAVSession对象指针
 * @param avcastcontroller 接收返回的OH_AVCastController对象指针
 * @return 返回执行结果
 * @since 23
 */
AVSession_ErrCode OH_AVSession_CreateAVCastController(OH_AVSession* avsession, OH_AVCastController** avcastcontroller);

/**
 * @brief 结束投播
 *
 * @param avsession OH_AVSession对象指针
 * @return 返回调用执行结果
 *
 * @since 23
 */
AVSession_ErrCode OH_AVSession_StopCasting(OH_AVSession* avsession);

/**
 * @brief 获取当前输出设备对象
 *
 * @param avsession OHAVSession对象指针
 * @param outputDeviceInfo 返回的接收AVSession_OutputDeviceInfo对象的指针
 * @return 返回执行结果
 * @since 23
 */
AVSession_ErrCode OH_AVSession_AcquireOutputDevice(OH_AVSession* avsession,
    AVSession_OutputDeviceInfo** outputDeviceInfo);

/**
 * @brief 释放当前投播的对象
 *
 * @param avsession OH_AVSession对象指针
 * @param outputDeviceInfo 要释放的OutputDeviceInfo对象指针
 * @return 返回调用执行结果
 * @since 23
 */
AVSession_ErrCode OH_AVSession_ReleaseOutputDevice(OH_AVSession* avsession,
    AVSession_OutputDeviceInfo *outputDeviceInfo);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSESSION_H
/** @} */