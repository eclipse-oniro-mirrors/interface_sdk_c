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
 * @file native_avcastcontroller.h
 *
 * @brief 提供播控控制器的定义。
 *
 * @library libohavsession.so
 * @syscap SystemCapability.Multimedia.AVSession.Core
 * @kit AVSessionKit
 * @since 23
 * @version 1.0
 */

#ifndef NATIVE_AVCASTCONTROLLER_H
#define NATIVE_AVCASTCONTROLLER_H

#include <stdint.h>
#include "native_avsession_errors.h"
#include "native_avsession.h"
#include "native_avqueueitem.h"
#include "native_avplaybackstate.h"

#ifdef __cplusplus
extern "C" {
#endif

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
 * @brief 播放状态改变的回调函数。
 *
 * @param avcastcontroller the OH_AVCastController instance pointer.
 * @param playbackState the {@link OH_AVSession_AVPlaybackState}
 *     pointer variable which will be set the changed playback state.
 * @param userdata userdata which is passed by register.
 * @since 23
 * @version 1.0
 */
typedef AVSessionCallback_Result(*OH_AVCastControllerCallback_PlaybackStateChanged)(
    OH_AVCastController* avcastcontroller, OH_AVSession_AVPlaybackState* playbackState, void* userData);

/**
 * @brief 媒体项目变更的回调函数。
 *
 * @param avcastcontroller the OH_AVCastController instance pointer.
 * @param avQueueItem the {@link OH_AVSession_AVQueueItem}
 *     pointer variable which will be set the changed media item info.
 * @param userdata userdata which is passed by register
 * @since 23
 * @version 1.0
 */
typedef AVSessionCallback_Result(*OH_AVCastControllerCallback_MediaItemChange)(OH_AVCastController* avcastcontroller,
    OH_AVSession_AVQueueItem* avQueueItem, void* userData);

/**
 * @brief 播放下一首的回调函数。
 *
 * @param avcastcontroller the OH_AVCastController instance pointer.
 * @param userdata userdata which is passed by register.
 * @since 23
 * @version 1.0
 */
typedef AVSessionCallback_Result(*OH_AVCastControllerCallback_PlayNext)(OH_AVCastController* avcastcontroller,
    void* userData);

/**
 * @brief 播放上一首的回调函数。
 *
 * @param avcastcontroller the OH_AVCastController instance pointer.
 * @param userdata userdata which is passed by register.
 * @since 23
 * @version 1.0
 */
typedef AVSessionCallback_Result(*OH_AVCastControllerCallback_PlayPrevious)(OH_AVCastController* avcastcontroller,
    void* userData);

/**
 * @brief 跳转完成的回调函数。
 *
 * @param avcastcontroller the OH_AVCastController instance pointer.
 * @param position position value after seek.
 * @param userdata userdata which is passed by register.
 * @since 23
 * @version 1.0
 */
typedef AVSessionCallback_Result(*OH_AVCastControllerCallback_SeekDone)(OH_AVCastController* avcastcontroller,
    int32_t position, void* userData);

/**
 * @brief 播放流结束的回调函数。
 *
 * @param avcastcontroller the OH_AVCastController instance pointer.
 * @param userdata userdata which is passed by register.
 * @since 23
 * @version 1.0
 */
typedef AVSessionCallback_Result(*OH_AVCastControllerCallback_EndOfStream)(OH_AVCastController* avcastcontroller,
    void* userData);

/**
 * @brief 播放错误的回调函数。
 *
 * @param avcastcontroller the OH_AVCastController instance pointer.
 * @param userdata userdata which is passed by register.
 * @param error cast play error code
 * @since 23
 * @version 1.0
 */
typedef AVSessionCallback_Result(*OH_AVCastControllerCallback_Error)(OH_AVCastController* avcastcontroller,
    void* userData, AVSession_ErrCode error);

/**
 * @brief 请求销毁播控控制器对象。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：参数avcastcontroller为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_Destroy(OH_AVCastController* avcastcontroller);

/**
 * @brief 获取当前播放器的播放状态。
 *
 * 不要单独释放playbackState指针。\n
 * 当{@link OH_AVCastController_Destroy}被调用时，该指针将随播控控制器一同销毁。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param playbackState 返回的播放状态。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数playbackState为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_GetPlaybackState(OH_AVCastController* avcastcontroller,
    OH_AVSession_AVPlaybackState** playbackState);

/**
 * @brief 请求注册播放状态改变的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param filter 通过播放状态的过滤器{@link AVSession_PlaybackFilter}来决定需要包含在回调中的参数。
 * @param callback 要注册的回调函数。
 * @param userData 由用户传递的用户数据。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。\n
 *                                         3. 参数filter是无效的。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_RegisterPlaybackStateChangedCallback(OH_AVCastController* avcastcontroller,
    int32_t filter, OH_AVCastControllerCallback_PlaybackStateChanged callback, void* userData);

/**
 * @brief 请求取消注册播放状态改变的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要取消注册的回调函数。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_UnregisterPlaybackStateChangedCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_PlaybackStateChanged callback);

/**
 * @brief 请求注册当前播放的媒体资源发生改变的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要注册的回调函数。
 * @param userData 由用户传递的用户数据。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_RegisterMediaItemChangedCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_MediaItemChange callback, void* userData);

/**
 * @brief 请求取消注册当前播放的媒体资源发生改变的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要取消注册的回调函数。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_UnregisterMediaItemChangedCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_MediaItemChange callback);

/**
 * @brief 请求注册由远程端或媒体中心发送的播放下一首的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要注册的回调函数。
 * @param userData 由用户传递的用户数据。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_RegisterPlayNextCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_PlayNext callback, void* userData);

/**
 * @brief 请求取消注册由远程端或媒体中心发送的播放下一首的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要取消注册的回调函数。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_UnregisterPlayNextCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_PlayNext callback);

/**
 * @brief 请求注册由远程端或媒体中心发送的播放上一首的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要注册的回调函数。
 * @param userData 由用户传递的用户数据。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_RegisterPlayPreviousCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_PlayPrevious callback, void* userData);

/**
 * @brief 请求取消注册由远程端或媒体中心发送的播放上一首的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要取消注册的回调函数。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_UnregisterPlayPreviousCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_PlayPrevious callback);

/**
 * @brief 请求注册跳转完成的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要注册的回调函数。
 * @param userData 由用户传递的用户数据。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_RegisterSeekDoneCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_SeekDone callback, void* userData);

/**
 * @brief 请求取消注册跳转完成的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要取消注册的回调函数。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_UnregisterSeekDoneCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_SeekDone callback);

/**
 * @brief 请求注册播放流结束的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要注册的回调函数。
 * @param userData 由用户传递的用户数据。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_RegisterEndOfStreamCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_EndOfStream callback, void* userData);

/**
 * @brief 请求取消注册播放流结束的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要取消注册的回调函数。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_UnregisterEndOfStreamCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_EndOfStream callback);

/**
 * @brief 请求注册监听播放错误事件的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要注册的回调函数。
 * @param userData 由用户传递的用户数据。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_RegisterErrorCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_Error callback, void* userData);

/**
 * @brief 请求取消注册监听播放错误事件的回调函数。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param callback 要取消注册的回调函数。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数callback为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_UnregisterErrorCallback(OH_AVCastController* avcastcontroller,
    OH_AVCastControllerCallback_Error callback);

/**
 * @brief 请求发送普通命令到远程端。
 * 只支持发送播放、暂停、停止、播放下一首和播放上一首等命令。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param avCastControlcommand 控制命令。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：参数avcastcontroller为nullptr。\n
 *         AV_SESSION_ERR_CODE_COMMAND_INVALID：参数avCastControlcommand是无效的。\n
 *         AV_SESSION_ERR_CODE_REMOTE_CONNECTION_NOT_EXIST：远程连接未建立。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_SendCommonCommand(OH_AVCastController* avcastcontroller,
    AVSession_AVCastControlCommandType* avCastControlcommand);

/**
 * @brief 请求向远程端发送跳转命令。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param seekTimeMS 跳转时间。单位为毫秒（ms）。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数seekTimeMS是无效的。\n
 *         AV_SESSION_ERR_CODE_REMOTE_CONNECTION_NOT_EXIST：远程连接未建立。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_SendSeekCommand(OH_AVCastController* avcastcontroller, int32_t seekTimeMS);

/**
 * @brief 请求向远程端发送快进命令。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param forwardTimeS 快进时间。单位为秒（s）。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数forwardTimeS是无效的。\n
 *         AV_SESSION_ERR_CODE_REMOTE_CONNECTION_NOT_EXIST：远程连接未建立。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_SendFastForwardCommand(OH_AVCastController* avcastcontroller,
    int32_t forwardTimeS);

/**
 * @brief 请求向远程端发送快退命令。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param rewindTimeS 快退时间。单位为秒（s）。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数rewindTimeS是无效的。\n
 *         AV_SESSION_ERR_CODE_REMOTE_CONNECTION_NOT_EXIST：远程连接未建立。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_SendRewindCommand(OH_AVCastController* avcastcontroller, int32_t rewindTimeS);

/**
 * @brief 请求向远程端发送设置倍速命令。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param speed 倍速控制命令。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数speed是无效的。\n
 *         AV_SESSION_ERR_CODE_REMOTE_CONNECTION_NOT_EXIST：远程连接未建立。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_SendSetSpeedCommand(OH_AVCastController* avcastcontroller,
    AVSession_PlaybackSpeed speed);

/**
 * @brief 请求向远程端发送音量控制命令。
 *
 * @param avcastcontroller 播控控制器的实例对象。
 * @param volume 音量控制。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_SERVICE_EXCEPTION：服务器内部错误。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数avcastcontroller为nullptr。\n
 *                                         2. 参数volume是无效的。\n
 *         AV_SESSION_ERR_CODE_REMOTE_CONNECTION_NOT_EXIST：远程连接未建立。
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_SendVolumeCommand(OH_AVCastController* avcastcontroller, int32_t volume);

/**
 * @brief 准备启动投播资源
 *
 * @param avcastcontroller 投播控制器对象指针
 * @param avqueueItem  投播资源结构
 * @return 返回接口执行结果
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_Prepare(OH_AVCastController* avcastcontroller,
    OH_AVSession_AVQueueItem *avqueueItem);

/**
 * @brief 开始启动投播资源
 *
 * @param avcastcontroller 投播控制器对象指针
 * @param avqueueItem  投播资源结构
 * @return 返回接口执行结果
 * @since 23
 */
AVSession_ErrCode OH_AVCastController_Start(OH_AVCastController* avcastcontroller,
    OH_AVSession_AVQueueItem *avqueueItem);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVCASTCONTROLLER_H
/** @} */