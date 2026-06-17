/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @addtogroup AVPlayer
 *
 * @brief Provides APIs of Playback capability for Media Source.
 *
 * @Syscap SystemCapability.Multimedia.Media.AVPlayer
 * @since 11
 */
/**
 * @file avplayer.h
 *
 * @brief 定义AVPlayer接口。使用AVPlayer提供的Native API播放媒体源。
 * 
 * @kit MediaKit
 * @library libavplayer.so
 * @since 11
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVPLAYER_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVPLAYER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "native_averrors.h"
#include "avplayer_base.h"
#include "native_avcodec_base.h"
#include "native_window/external_window.h"
#include "ohaudio/native_audiostream_base.h"
#include "avmedia_source.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief MediaKeySession类型。
 * 
 * @since 12
 */
typedef struct MediaKeySession MediaKeySession;
/**
 * @brief DRM_MediaKeySystemInfo类型。
 * 
 * @since 12
 */
typedef struct DRM_MediaKeySystemInfo DRM_MediaKeySystemInfo;

/**
 * @brief OH_AVPlayerVideoOutput field.
 * @since 26.0.0
 */ 
typedef struct OH_AVPlayerVideoOutput OH_AVPlayerVideoOutput;

/**
 * @brief 播放器DRM信息更新时调用。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param mediaKeySystemInfo DRM信息。
 * @return void
 * @since 12
 */
typedef void (*Player_MediaKeySystemInfoCallback)(OH_AVPlayer *player, DRM_MediaKeySystemInfo* mediaKeySystemInfo);

/**
 * @brief 创建播放器。
 * 推荐单个应用创建的音视频播放器实例（即音频、视频、音视频三类相加）不超过16个。
 * <!--Del-->可创建的音视频播放器实例数量依赖于设备芯片的支持情况，如芯片支持创建的数量少于上述情况，请以芯片规格为准。如RK3568推荐单个应用创建6个以内的音视频播放器实例。<!--DelEnd-->
 * 
 * @return 如果创建成功返回指向OH_AVPlayer实例的指针，否则返回空指针。
 * 可能的失败原因：
 * 1.PlayerFactory::CreatePlayer执行失败。
 * 2.new PlayerObject执行失败。
 * @since 11
*/
OH_AVPlayer *OH_AVPlayer_Create(void);

/**
 * @brief 设置播放器的播放源。对应的源可以是http url。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param url 播放源。
 * @return AV_ERR_OK：设置成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，url为空或者player SetUrlSource执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_SetURLSource(OH_AVPlayer *player, const char *url);

/**
 * @brief 设置播放器的媒体文件描述符来源。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param fd 媒体源的文件描述符。
 * @param offset 媒体源在文件描述符中的偏移量。
 * @param size 表示媒体源的大小。
 * @return AV_ERR_OK：fd设置成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player SetFdSource执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_SetFDSource(OH_AVPlayer *player, int32_t fd, int64_t offset, int64_t size);

/**
 * @brief 设置播放器的媒体源，该媒体源的数据由应用程序提供。
 * 
 * @param player Pointer to an OH_AVPlayer instance
 * @param datasrc Pointer to an OH_AVDataSourceExt instance
 * @param userData The handle passed in by the user is used to pass in the callback
 * @return AV_ERR_OK：设置成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者输入datasrc为空指针。
 * @since 21
 */
OH_AVErrCode OH_AVPlayer_SetDataSource(OH_AVPlayer *player, OH_AVDataSourceExt* datasrc, void* userData);

/**
 * @brief 准备播放环境，异步缓存媒体数据。
 * 此函数必须在SetSource之后调用。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player Prepare执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_Prepare(OH_AVPlayer *player);

/**
 * @brief 开始播放。
 * 此函数必须在{@link OH_AVPlayer_Prepare}之后调用。
 * 如果播放器状态为\<Prepared>，调用此函数开始播放。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player Play执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_Play(OH_AVPlayer *player);

/**
 * @brief 暂停播放。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player Pause执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_Pause(OH_AVPlayer *player);

/**
 * @brief 停止播放。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player Stop执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_Stop(OH_AVPlayer *player);

/**
 * @brief 将播放器恢复到初始状态。
 * 函数调用完成后，调用SetSource添加播放源。调用{@link OH_AVPlayer_Prepare}后，再调用{@link OH_AVPlayer_Play}重新开始播放。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player Reset执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_Reset(OH_AVPlayer *player);

/**
 * @brief 异步释放播放器资源。
 * 异步释放可以提升性能，但不能确保播放画面的SurfaceBuffer已释放。调用者需要确保播放画面窗口的生命周期安全。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player Release执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_Release(OH_AVPlayer *player);

/**
 * @brief 同步释放播放器资源。
 * 同步过程保证了播放画面的SurfaceBuffer释放，但该过程耗时较长，建议调用者自行设计异步机制。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player ReleaseSync执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_ReleaseSync(OH_AVPlayer *player);

/**
 * @brief 获取播放器媒体源信息。设置完播放资源并且播放处于initialized/prepared/playing/paused/completed/stopped状态，可调用该接口。
 * 需要注意返回值OH_AVFormat指针对象的生命周期需要用户手动释放。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return 执行成功返回播放器媒体信息，否则返回nullptr。
 * 可能故障原因：
 * 1. 传入player指针不合法。
 * 2. 设置的播放资源不合法。
 * @since 22
 */
OH_AVFormat *OH_AVPlayer_GetMediaDescription(OH_AVPlayer *player);

/**
 * @brief 通过索引下标获取播放器媒体源轨道信息。设置完播放资源并且播放处于initialized/prepared/playing/paused/completed/stopped状态，可调用该接口。
 * 需要注意返回值OH_AVFormat指针对象的生命周期需要用户手动释放。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param index 轨道索引下标。
 * @return 执行成功按索引下标返回轨道信息，否则返回nullptr。
 * 可能故障原因：
 * 1. 传入player指针不合法。
 * 2. 设置的播放资源不合法。
 * 3. 轨道索引下标超出播放源文件数组界限。
 * @since 22
 */
OH_AVFormat *OH_AVPlayer_GetTrackDescription(OH_AVPlayer *player, uint32_t index);

/**
 * @brief 设置播放器的音量。
 * 可以在播放或暂停的过程中使用。0表示无声音，1为原始值。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param leftVolume 要设置的左声道目标音量。
 * @param rightVolume 要设置的右声道目标音量。
 * @return AV_ERR_OK：成功设置音量。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player SetVolume执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_SetVolume(OH_AVPlayer *player, float leftVolume, float rightVolume);

/**
 * @brief 改变播放位置。
 * 此函数可以在播放或暂停时使用。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param mSeconds 播放目标位置，精确到毫秒。
 * @param mode 播放器的跳转模式。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player Seek执行失败。
 * @since 11
*/
OH_AVErrCode OH_AVPlayer_Seek(OH_AVPlayer *player, int32_t mSeconds, AVPlayerSeekMode mode);

/**
 * @brief 获取播放位置，精确到毫秒。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param currentTime 播放位置。
 * @return AV_ERR_OK：成功获取当前播放位置。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player GetCurrentTime执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetCurrentTime(OH_AVPlayer *player, int32_t *currentTime);

/**
 * @brief 获取视频宽度。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param videoWidth 视频宽度。
 * @return AV_ERR_OK：成功获取视频宽度。
 * AV_ERR_INVALID_VAL：输入player为空指针。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetVideoWidth(OH_AVPlayer *player, int32_t *videoWidth);

/**
 * @brief 获取视频高度。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param videoHeight 视频高度。
 * @return AV_ERR_OK：成功获取视频高度。
 * AV_ERR_INVALID_VAL：输入player为空指针。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetVideoHeight(OH_AVPlayer *player, int32_t *videoHeight);

/**
 * @brief 根据指定的{@link AVPlaybackSpeed}，设置播放器的播放速率。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param speed 速率模式。
 * @return AV_ERR_OK：成功设置播放速率。
 * AV_ERR_INVALID_VAL：输入player为空指针。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_SetPlaybackSpeed(OH_AVPlayer *player, AVPlaybackSpeed speed);

/**
 * @brief 获取当前播放器的播放速率。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param speed 速率模式。
 * @return AV_ERR_OK：成功获取播放速率。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player GetPlaybackSpeed执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetPlaybackSpeed(OH_AVPlayer *player, AVPlaybackSpeed *speed);

/**
 * @brief 获取当前播放器播放速率。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param rate 可以获得的播放速率。
 * @return 如果成功获取当前播放器的播放速率，返回{@link AV_ERR_OK}；
 * 否则返回{@link native_averrors.h}中定义的错误码。
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_GetPlaybackRate(OH_AVPlayer *player, float *rate);

/**
 * @brief 设置player音频流类型。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param streamUsage player音频流设置的类型。
 * @return AV_ERR_OK：成功设置音频流类型。
 * AV_ERR_INVALID_VAL：输入player为空指针或者streamUsage值无效。
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_SetAudioRendererInfo(OH_AVPlayer *player, OH_AudioStream_Usage streamUsage);

/**
 * @brief 设置player音频流的打断模式。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param interruptMode player音频流使用的打断模式。
 * @return AV_ERR_OK：成功设置音频流的打断模式。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者interruptMode值无效。
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_SetAudioInterruptMode(OH_AVPlayer *player, OH_AudioInterrupt_Mode interruptMode);

/**
 * @brief 设置player音频流的音效模式。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param effectMode player音频流使用的音效模式。
 * @return AV_ERR_OK：成功设置音频流的音效模式。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者effectMode值无效。
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_SetAudioEffectMode(OH_AVPlayer *player, OH_AudioStream_AudioEffectMode effectMode);

/**
 * @brief 设置hls播放器使用的码率。仅对HLS协议网络流有效。
 * 默认情况下，播放器会根据网络连接情况选择合适的码率和速度。
 * 通过INFO_TYPE_BITRATE_COLLECT上报有效码率链表，设置并选择指定的码率，选择小于且最接近的码率。准备好后，读取以查询当前选择的比特率。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param bitRate 码率，单位为bps。
 * @return AV_ERR_OK：成功设置码率。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player SelectBitRate执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_SelectBitRate(OH_AVPlayer *player, uint32_t bitRate);

/**
 * @brief 设置播放画面窗口。
 * 此函数必须在SetSource之后，Prepare之前调用。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param window 指向OHNativeWindow实例的指针。
 * @return AV_ERR_OK：成功设置播放画面窗口。
 * AV_ERR_INVALID_VAL：输入player为空指针，输入window为空指针或者player SetVideoSurface执行失败。
 * @since 11
 */
OH_AVErrCode  OH_AVPlayer_SetVideoSurface(OH_AVPlayer *player, OHNativeWindow *window);

/**
 * @brief 获取媒体文件的总时长，精确到毫秒。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param duration 媒体文件的总时长。
 * @return AV_ERR_OK：成功获取媒体文件时长。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player GetDuration执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetDuration(OH_AVPlayer *player, int32_t *duration);

/**
 * @brief 获取当前播放状态。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param state 当前播放状态。
 * @return AV_ERR_OK：成功获取当前播放状态。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player GetState执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetState(OH_AVPlayer *player, AVPlayerState *state);

/**
 * @brief 判断播放器是否在播放。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return 如果正在播放，则返回true；如果不在播放或者输入player为空指针则返回false。
 * @since 11
 */
bool OH_AVPlayer_IsPlaying(OH_AVPlayer *player);

/**
 * @brief 判断是否循环播放。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return 如果是循环播放，则返回true；如果不是循环播放或者输入player为空指针则返回false。
 * @since 11
 */
bool OH_AVPlayer_IsLooping(OH_AVPlayer *player);

/**
 * @brief 设置循环播放。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param loop 循环播放开关。true表示开启循环播放，false表示关闭循环播放。
 * @return AV_ERR_OK：成功设置循环播放。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player SetLooping执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_SetLooping(OH_AVPlayer *player, bool loop);

/**
 * @brief 设置播放器回调函数。
 * 由于通过此方法设置的信息监听回调函数{@link OH_AVPlayerOnInfo}和错误监听回调函数{@link OH_AVPlayerOnError}可以传递的信息有限，也不便于应用区分多个播放器实例。
 * 从API version 12开始，应使用{@link OH_AVPlayer_SetOnInfoCallback}、{@link OH_AVPlayer_SetOnErrorCallback}接口分别设置信息监听回调函数{@link OH_AVPlayerOnInfoCallback}
 * 和错误监听回调函数{@link OH_AVPlayerOnErrorCallback}。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param callback 回调对象指针。
 * @return AV_ERR_OK：成功设置播放器回调。
 * AV_ERR_INVALID_VAL：输入player为空指针，callback.onInfo或onError为空，或者player SetPlayerCallback执行失败。
 * @since 11
 * @deprecated since 12
 * @useinstead {@link OH_AVPlayer_SetOnInfoCallback} {@link OH_AVPlayer_SetOnErrorCallback}
 */
OH_AVErrCode OH_AVPlayer_SetPlayerCallback(OH_AVPlayer *player, AVPlayerCallback callback);

/**
 * @brief 选择音频或字幕轨道。
 * 默认播放第一个带数据的音轨，不播放字幕轨道。
 * 设置生效后，原音轨将失效。请设置字幕处于准备/播放/暂停/完成状态，并将音轨设置为准备状态。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param index 索引。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player SelectTrack执行失败。
 * @since 11
*/
OH_AVErrCode OH_AVPlayer_SelectTrack(OH_AVPlayer *player, int32_t index);

/**
 * @brief 取消选择当前音频或字幕轨道。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param index 索引。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player DeselectTrack执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_DeselectTrack(OH_AVPlayer *player, int32_t index);

/**
 * @brief 获取当前有效的轨道索引。请将状态设置为准备/正在播放/暂停/完成。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param trackType 媒体类型。0：音频，1：视频。
 * @param index 索引。
 * @return AV_ERR_OK：成功获取轨道索引。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者player GetCurrentTrack执行失败。
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetCurrentTrack(OH_AVPlayer *player, int32_t trackType, int32_t *index);

/**
 * @brief 设置播放器媒体密钥系统信息回调的方法。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param callback 对象指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针，callback为空指针，player SetDrmSystemInfoCallback，
 * SetDrmSystemInfoCallback或SetDrmSystemInfoCallback执行失败。
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_SetMediaKeySystemInfoCallback(OH_AVPlayer *player,
    Player_MediaKeySystemInfoCallback callback);

/**
 * @brief 获取媒体密钥系统信息以创建媒体密钥会话。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param mediaKeySystemInfo 媒体密钥系统信息。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针或者内存不足。
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_GetMediaKeySystemInfo(OH_AVPlayer *player, DRM_MediaKeySystemInfo *mediaKeySystemInfo);

/**
 * @brief 设置解密信息。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param mediaKeySession 具有解密功能的媒体密钥会话实例。
 * @param secureVideoPath 是否需要安全解码器。true表示需要安全解码器，false表示不需要安全解码器。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入player为空指针或者player SetDecryptionConfig执行失败。
 * @since 12
*/
OH_AVErrCode OH_AVPlayer_SetDecryptionConfig(OH_AVPlayer *player, MediaKeySession *mediaKeySession,
    bool secureVideoPath);

/**
 * @brief 设置播放器消息回调监听函数。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param callback 执行回调监听函数的指针，空指针表示取消设置播放器消息回调监听。
 * @param userData 指向应用调用者设置的实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_NO_MEMORY：内存分配失败。
 * AV_ERR_INVALID_VAL： 输入player为空指针或者函数执行失败。
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_SetOnInfoCallback(OH_AVPlayer *player, OH_AVPlayerOnInfoCallback callback, void *userData);

/**
 * @brief 设置播放器错误回调监听函数。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param callback 执行回调监听函数的指针，空指针表示取消设置播放器错误回调监听。
 * @param userData 指向应用调用者设置的实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_NO_MEMORY：内存分配失败。
 * AV_ERR_INVALID_VAL： 输入player为空指针或者函数执行失败。
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_SetOnErrorCallback(OH_AVPlayer *player, OH_AVPlayerOnErrorCallback callback, void *userData);

/**
 * @brief 设置player音频流音量模式。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param volumeMode 指定音频流音量模式。
 * @return AV_ERR_OK：成功设置音频流音量模式。
 * AV_ERR_INVALID_VAL： 输入player为空指针或者volumeMode值无效。
 * AV_ERR_INVALID_STATE：函数在无效状态下调用，应先处于准备状态。
 * AV_ERR_SERVICE_DIED：系统错误。
 * @since 19
 */
OH_AVErrCode OH_AVPlayer_SetVolumeMode(OH_AVPlayer *player, OH_AudioStream_VolumeMode volumeMode);

/**
 * @brief 在有效范围内，设置播放器的播放速率。
 * 支持的状态：已准备/正在播放/已暂停/已完成。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param rate 播放速率，有效范围是0.125~4。
 * @return AV_ERR_OK：成功设置播放速率。
 * AV_ERR_OPERATE_NOT_PERMIT：如果在不支持的状态下调用或在直播期间调用。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者速率超出范围。
 * @since 20
 */
OH_AVErrCode OH_AVPlayer_SetPlaybackRate(OH_AVPlayer *player, float rate);

/**
 * @brief 设置播放器的响度。当播放处于prepared/playing/paused/completed/stopped状态时，可调用该接口。
 * 默认响度增益0.0dB。播放器流的usage参数必须是{@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_MUSIC，
 * {@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_MOVIE，{@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_AUDIOBOOK 之一。
 * 音频渲染器的延迟模式必须是{@link OH_AudioStream_LatencyMode}.AUDIOSTREAM_LATENCY_MODE_NORMAL。
 * 如果通过高分辨率管道播放，则不支持此操作。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param loudnessGain 设置播放器的响度值，单位为dB，响度范围为[-90.0, 24.0]。
 * @return AV_ERR_OK：成功设置响度。
 * AV_ERR_INVALID_VAL：输入player为空指针，或者输入的loudnessGain是无效参数。
 * AV_ERR_INVALID_STATE：函数在不正常的状态下调用，或者audioRendererInfo的usage参数不是
 * {@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_MUSIC，
 * {@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_MOVIE和
 * {@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_AUDIOBOOK之一。
 * AV_ERR_SERVICE_DIED：系统错误。
 * @since 21
 */
OH_AVErrCode OH_AVPlayer_SetLoudnessGain(OH_AVPlayer *player, float loudnessGain);

/**
 * @brief 获取当前播放器的统计指标信息。设置完播放资源，并且当播放处于准备（prepared）/播放（playing）/暂停（paused）/完成（completed）/停止（stopped）状态时，可调用该接口。
 * 需要注意返回值{@link OH_AVFormat}指针对象的生命周期需要用户手动释放。
 * 
 * @param player Pointer to an OH_AVPlayer instance
 * @return 执行成功返回播放器的统计指标信息（键值详情请参考avplayer_base.h中的{@link 变量}信息），否则返回nullptr。
 * 可能的失败原因：传入player指针不合法。
 * @since 23
 */
OH_AVFormat *OH_AVPlayer_GetPlaybackStatisticMetrics(OH_AVPlayer *player);

/**
 * @brief 将由文件描述符表示的字幕资源添加到播放器。目前，外挂字幕必须在AVPlayer设置完视频资源的fdSrc之后再设置。
 *  
 * @param player Pointer to an OH_AVPlayer instance
 * @param fd Indicates the file descriptor of subtitle source.
 * @param offset Indicates the offset of media source in file descriptor.
 * @param size Indicates the size of media source.
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的player为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_AddFdSubtitleSource(OH_AVPlayer *player, int32_t fd, int64_t offset, int64_t size);

/**
 * @brief 将由URL表示的字幕资源添加到播放器。外挂字幕必须在AVPlayer设置完url之后再设置。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param url 字幕源的URL。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的player为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_AddUrlSubtitleSource(OH_AVPlayer *player, const char *url);

/**
 * @brief 设置播放起始位置和结束位置。设置后，仅播放音视频文件中指定范围内的内容。可在初始化、已准备、暂停、停止或完成状态下调用。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param mSecondsStart 播放起始位置，应在[0, duration)范围内，-1 表示未设置起始位置，将从0开始播放。
 * @param mSecondsEnd 播放结束位置，通常应在(startTimeMs, duration]范围内，-1 表示未设置结束位置，将在流末尾结束播放。
 * @param closestRange 是否同步到距离指定时间点最近的帧。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的player为空指针。
 * AV_ERR_OPERATE_NOT_PERMIT：表示操作不允许。
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetPlaybackRange(OH_AVPlayer *player, int32_t mSecondsStart, int32_t mSecondsEnd,
    bool closestRange);

/**
 * Mute the media stream. This API can be called only when the AVPlayer is in the prepared, playing,
 * paused, or completed state.
 * @param player 指向OH_AVPlayer实例的指针。
 * @param mediaType 指定的媒体类型，参见{@link native_avcodec_base.h}中的{@link OH_MediaType}。
 * @param muted true表示静音，false表示取消静音。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入参数无效。
 * AV_ERR_OPERATE_NOT_PERMIT：表示操作不允许。
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetMediaMuted(OH_AVPlayer *player, OH_MediaType mediaType, bool muted);

/**
 * @brief 获取播放位置，精确到毫秒。此API仅可在AVPlayer处于已准备、播放中、暂停或完成状态时调用。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return 返回以毫秒为单位的播放位置。
 * 若player为空指针或无效，则返回-1。
 * @since 23
 */
int32_t OH_AVPlayer_GetPlaybackPosition(OH_AVPlayer *player);

/**
 * @brief 检查媒体源是否支持连续跳转。在已准备、播放中、暂停或完成状态下调用时返回实际值；在其他状态下调用时返回 false。对于不支持{@link AV_SEEK_CONTINUOUS}模式跳转操作的设备，返回false。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return @returns true表示支持连续跳转。
 * false表示不支持连续跳转或支持状态不确定。
 * @since 23
 */
bool OH_AVPlayer_IsSeekContinuousSupported(OH_AVPlayer *player);

/**
 * @brief 在播放包含多个音视频轨道的资源时，使用指定的切换模式选择轨道。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param index 所选轨道的索引。
 * @param mode 切换模式。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入参数无效。
 * AV_ERR_OPERATE_NOT_PERMIT：表示操作不允许。
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SelectTrackWithMode(OH_AVPlayer *player, int32_t index, AVPlayerTrackSwitchMode mode);

/**
 * @brief 订阅最大音频电平值的更新事件，该值在播放音频资源时周期性上报。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param callback 回调函数指针，nullptr表示取消注册回调。
 * @param userData 指向用户特定数据的指针。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的player为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetAmplitudeUpdateCallback(OH_AVPlayer *player, OH_AVPlayerOnAmplitudeUpdateCallback callback,
    void *userData);

/**
 * @brief 订阅接收到补充增强信息（SEI）消息的事件。仅适用于HTTP-FLV直播流，当视频流中存在SEI消息时触发。必须在调用prepare之前发起订阅。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param payloadTypes 负载类型数组。
 * @param typeNum 负载类型数组的大小。
 * @param callback 回调函数指针，nullptr表示取消注册回调。
 * @param userData 指向用户特定数据的指针。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的player为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetSeiReceivedCallback(OH_AVPlayer *player, const int32_t *payloadTypes, uint32_t typeNum,
    OH_AVPlayerOnSeiMessageReceivedCallback callback, void *userData);

/**
 * @brief 获取SEI消息数组中的消息项数量。
 * 
 * @param message 指向OH_AVSeiMessageArray实例的指针。
 * @return SEI消息数组中的消息项数量。
 * @since 23
 */
uint32_t OH_AVSeiMessage_GetSeiCount(OH_AVSeiMessageArray *message);

/**
 * @brief 通过索引获取SEI消息数组中某一项的SEI。
 * 
 * @param message 指向OH_AVSeiMessageArray实例的指针。
 * @param index 消息项的索引。
 * @return 该消息项的SEI。
 * @since 23
 */
OH_AVFormat *OH_AVSeiMessage_GetSei(OH_AVSeiMessageArray *message, uint32_t index);

/**
 * @brief 为超分辨率设置视频窗口大小。此API可在AVPlayer处于初始化、已准备、播放中、暂停、完成或停止状态时调用。输入参数值必须在320x320至1920x1080（像素）范围内。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param width 窗口宽度，取值范围[320-1920]，单位：像素。
 * @param height 窗口高度，取值范围[320-1080]，单位：像素。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的player为空指针或参数错误。
 * AV_ERR_OPERATE_NOT_PERMIT：表示操作不允许。
 * AV_ERR_SUPER_RESOLUTION_UNSUPPORTED：表示不支持超分辨率。
 * AV_ERR_SUPER_RESOLUTION_NOT_ENABLED：表示未在{@link OH_AVPlaybackStrategy}中启用超分辨率功能。
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetTargetVideoWindowSize(OH_AVPlayer *player, int32_t width, int32_t height);

/**
 * @brief 动态启用或禁用超分辨率。此API可在AVPlayer处于初始化、已准备、播放中、暂停、完成或停止状态时调用。必须在调用prepare之前在{@link OH_AVPlaybackStrategy}中启用超分辨率功能。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param enabled true：启用超分辨率；false：禁用超分辨率。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的player为空指针或参数错误。
 * AV_ERR_OPERATE_NOT_PERMIT：表示操作不允许。
 * AV_ERR_SUPER_RESOLUTION_UNSUPPORTED：表示不支持超分辨率。
 * AV_ERR_SUPER_RESOLUTION_NOT_ENABLED：表示未在{@link OH_AVPlaybackStrategy}中启用超分辨率功能。
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetVideoSuperResolutionEnable(OH_AVPlayer *player, bool enabled);

/**
 * @brief 创建一个播放策略实例。
 * 
 * @return 一个播放策略实例，失败时返回空指针。
 * @since 23
 */
OH_AVPlaybackStrategy *OH_AVPlaybackStrategy_Create(void);

/**
 * @brief 释放一个播放策略实例。
 * 
 * @param strategy OH_AVPlaybackStrategy实例。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_Destroy(OH_AVPlaybackStrategy *strategy);

/**
 * @brief 选择接近指定宽度的流。
 * 
 * @param strategy avplayer使用的OH_AVPlaybackStrategy。
 * @param width avplayer启动时选择播放的首选宽度。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredWidth(OH_AVPlaybackStrategy *strategy, int32_t width);

/**
 * @brief 选择接近指定高度的流。
 * 
 * @param strategy avplayer使用的OH_AVPlaybackStrategy。
 * @param height avplayer启动时选择播放的首选高度。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredHeight(OH_AVPlaybackStrategy *strategy, int32_t height);

/**
 * @brief 选择接近指定值的首选缓冲时长。
 * 
 * @param strategy avplayer使用的OH_AVPlaybackStrategy。
 * @param ms avplayer启动时选择播放的首选缓冲时长。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredBufferDuration(OH_AVPlaybackStrategy *strategy, int32_t ms);

/**
 * @brief 启用或禁用首选HDR模式。
 * 
 * @param strategy 指向OH_AVPlaybackStrategy的指针。
 * @param enabled true表示启用HDR，false表示禁用。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredHdr(OH_AVPlaybackStrategy *strategy, bool enabled);

/**
 * @brief 设置首选字幕语言。
 * 
 * @param strategy 指向OH_AVPlaybackStrategy的指针。
 * @param lang 字幕语言代码（例如"zh"）。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredSubtitleLanguage(OH_AVPlaybackStrategy *strategy, const char *lang);

/**
 * @brief 设置首选音频语言。
 * 
 * @param strategy 指向OH_AVPlaybackStrategy的指针。
 * @param lang 音频语言代码（例如"en"）。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredAudioLanguage(OH_AVPlaybackStrategy *strategy, const char *lang);

/**
 * @brief 设置播放时要静音的媒体类型。
 * 
 * @param strategy 指向OH_AVPlaybackStrategy的指针。
 * @param mediaType 要静音的媒体类型。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetMutedMediaType(OH_AVPlaybackStrategy *strategy, OH_MediaType mediaType);

/**
 * @brief 设置是否在prepare时显示首帧。
 * 
 * @param strategy 指向OH_AVPlaybackStrategy的指针。
 * @param enabled true表示显示，false表示不显示。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetShowFirstFrameOnPrepare(OH_AVPlaybackStrategy *strategy, bool enabled);

/**
 * @brief 设置自动快速播放的阈值。
 * 
 * @param strategy 指向OH_AVPlaybackStrategy的指针。
 * @param seconds 自动快速播放的阈值。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetThresholdForAutoQuickPlay(OH_AVPlaybackStrategy *strategy, double seconds);

/**
 * @brief 启用或禁用超分辨率。
 * 
 * @param strategy 指向OH_AVPlaybackStrategy的指针。
 * @param enabled true表示启用，false表示禁用。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetSuperResolutionEnable(OH_AVPlaybackStrategy *strategy, bool enabled);

/**
 * @brief 设置播放时的首选缓冲时长（秒，double类型）。
 * 
 * @param strategy 指向OH_AVPlaybackStrategy的指针。
 * @param seconds 缓冲时长（秒）。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredBufferDurationForPlaying(OH_AVPlaybackStrategy *strategy,
    double seconds);

/**
 * @brief 设置静音时是否继续解码。
 * 
 * @param strategy 指向OH_AVPlaybackStrategy的指针。
 * @param enabled true表示继续解码，false表示静音时暂停解码。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的strategy为空指针。
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetKeepDecodingOnMute(OH_AVPlaybackStrategy *strategy, bool enabled);

/**
 * @brief 将播放策略设置给avplayer。此API仅可在avplayer处于初始化状态时调用。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param strategy 播放策略实例。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的player为空指针。
 * AV_ERR_OPERATE_NOT_PERMIT：表示操作不允许。
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetPlaybackStrategy(OH_AVPlayer *player, OH_AVPlaybackStrategy *strategy);

/**
 * @brief 获取当前播放器的统计信息。此API仅可在avplayer处于已准备、播放中或暂停状态时调用。
 * 
 * @param player Pointer to an OH_AVPlayer instance
 * @return 返回指向OH_AVFormat实例的指针。
 * 若player为空指针或无效，则返回空指针。
 * @since 23
 */
OH_AVFormat* OH_AVPlayer_GetPlaybackInfo(OH_AVPlayer *player);

/**
 * @brief 将OH_AVMediaSource设置给播放器。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param source 媒体源。
 * @return 函数执行结果。
 * AV_ERR_OK：表示执行成功。
 * AV_ERR_INVALID_VAL：表示输入的player或者source为空指针，或player设置URL源失败。
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetMediaSource(OH_AVPlayer *player, OH_AVMediaSource *source);

/**
 * @brief 获取播放器媒体源的轨道数量。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @return 返回轨道数量。
 * @since 23
 */
uint32_t OH_AVPlayer_GetTrackCount(OH_AVPlayer *player);

/**
 * @brief 通过索引获取播放器轨道信息。
 * 
 * @param player 指向OH_AVPlayer实例的指针。
 * @param trackIndex 轨道数组索引。
 * @return 返回指向OH_AVFormat实例的指针。
 * 若player为空指针或无效，或trackIndex无效，则返回空指针。
 * @since 23
 */
OH_AVFormat *OH_AVPlayer_GetTrackFormat(OH_AVPlayer *player, uint32_t trackIndex);

/**
 * @brief Method to set video decoded frame output callback. This API can be called only
 *     when the avplayer is in the idle or initalized state.
 * @param player Pointer to an OH_AVPlayer instance.
 * @param window A pointer to a OHNativeWindow instance, see {@link OHNativeWindow}
 * @return Returns a pointer to an OH_AVPlayerVideoOutput instance, released by system when avplayer was
 *     reset or release. nullptr means failed.
 * @since 26.0.0
 */
OH_AVPlayerVideoOutput* OH_AVPlayer_SetVideoSideOutput(OH_AVPlayer *player, OHNativeWindow *window);

/**
 * @brief Method to get one video decoded frame. This API can be called only when the avplayer is
 *     in the paused or playing state.
 * @param videoOutput Pointer to an OH_AVPlayerVideoOutput instance returned by OH_AVPlayer_SetVideoSideOutput.
 * @return Returns OH_VIDEO_OUTPUT_OK when got a frame.
 *         Returns OH_VIDEO_OUTPUT_NO_IMAGE when there is no frame ready to render.
 * @since 26.0.0
 */
OH_VideoOutputResult OH_AVPlayerVideoOutput_GetNewestVideoSample(OH_AVPlayerVideoOutput *videoOutput);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVPLAYER_H
