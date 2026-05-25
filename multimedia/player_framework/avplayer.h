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
 * @brief The **avplayer.h** file declares the AVPlayer APIs. You can use the native AVPlayer APIs to play a media
 * asset.
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
 * @brief The MediaKeySession struct describes the media key session.
 * 
 * @since 12
 */
typedef struct MediaKeySession MediaKeySession;
/**
 * @brief The DRM_MediaKeySystemInfo struct describes the media key system information.
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
 * @brief Called when media key system information of the AVPlayer is updated.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param mediaKeySystemInfo Pointer to the media key system information.
 * @return void
 * @since 12
 */
typedef void (*Player_MediaKeySystemInfoCallback)(OH_AVPlayer *player, DRM_MediaKeySystemInfo* mediaKeySystemInfo);

/**
 * @brief Creates an OH_AVPlayer instance.
 * You are advised to create a maximum of 16 AVPlayer instances for an application in both audio and video playback
 * scenarios.
 * <!--Del-->The actual number of instances that can be created may be different. It depends on the specifications of
 * the device chip in use. For example, in the case of RK3568, you are advised to create a maximum of 6 AVPlayer
 * instances for an application in audio and video playback scenarios.<!--DelEnd-->
 * 
 * @return Pointer to the OH_AVPlayer instance created if the operation is successful; nullptr otherwise.
 * The possible causes of an operation failure are as follows:
 * 1. The execution of **PlayerFactory::CreatePlayer** fails.
 * 2. The execution of **new PlayerObject** fails.
 * @since 11
*/
OH_AVPlayer *OH_AVPlayer_Create(void);

/**
 * @brief Sets the HTTP URL of a media source to be played by an AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param url URL of the media source.
 * @return {@link AV_ERR_OK}: The setting is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, the input parameter **url** is null, or the
 * execution of **player SetUrlSource** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_SetURLSource(OH_AVPlayer *player, const char *url);

/**
 * @brief Sets the file descriptor of a media source to be played by an AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param fd File descriptor of the media source.
 * @param offset Offset of the media source in the file descriptor.
 * @param size Size of the media source.
 * @return {@link AV_ERR_OK}: The file descriptor is set successfully.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player SetFdSource** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_SetFDSource(OH_AVPlayer *player, int32_t fd, int64_t offset, int64_t size);

/**
 * @brief Sets the media source of the AVPlayer. The data of this media source is provided by the application.
 * 
 * @param player Pointer to an OH_AVPlayer instance
 * @param datasrc Pointer to an OH_AVDataSourceExt instance
 * @param userData The handle passed in by the user is used to pass in the callback
 * @return {@link AV_ERR_OK}: The setting is successful.
 * {@link AV_ERR_INVALID_VAL}: The **player** or **datasrc** parameter is nullptr.
 * @since 21
 */
OH_AVErrCode OH_AVPlayer_SetDataSource(OH_AVPlayer *player, OH_AVDataSourceExt* datasrc, void* userData);

/**
 * @brief Prepares the playback environment and buffers media data.
 * This function must be called after **SetSource**.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player Prepare** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_Prepare(OH_AVPlayer *player);

/**
 * @brief Starts playback.
 * This function must be called after {@link OH_AVPlayer_Prepare}.
 * In other words, you can call this function when the AVPlayer is in the prepared state.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player Play** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_Play(OH_AVPlayer *player);

/**
 * @brief Pauses playback.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player Pause** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_Pause(OH_AVPlayer *player);

/**
 * @brief Stops playback.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player Stop** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_Stop(OH_AVPlayer *player);

/**
 * @brief Restores the AVPlayer to the initial state.
 * After the function is called, you can call **SetSource** to set the media source to play, and then call {@link OH_AVPlayer_Prepare}
 * and {@link OH_AVPlayer_Play} in sequence.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player Reset** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_Reset(OH_AVPlayer *player);

/**
 * @brief Asynchronously releases an OH_AVPlayer instance.
 * The asynchronous function improves performance, but cannot ensure that the surface buffer of the playback window is
 * released. You must ensure the lifecycle of the playback window.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player Release** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_Release(OH_AVPlayer *player);

/**
 * @brief Synchronously releases an OH_AVPlayer instance.
 * The synchronous function ensures that the display buffer of the playback window is released, with a long time.
 * Therefore, you need to design an asynchronous mechanism.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player ReleaseSync** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_ReleaseSync(OH_AVPlayer *player);

/**
 * @brief Obtains the media source information for the AVPlayer. This function can be called when the playback resource
 * is configured and the AVPlayer is in the initialized, prepared, playing, paused, completed, or stopped state.
 * You must manually release the returned OH_AVFormat pointer object when it is no longer needed.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return Media source information obtained. If the operation fails, nullptr is returned.
 * Possible cause:
 * 1. The **player** pointer is invalid.
 * 2. The playback resource is invalid.
 * @since 22
 */
OH_AVFormat *OH_AVPlayer_GetMediaDescription(OH_AVPlayer *player);

/**
 * @brief Obtains the media source track information for the AVPlayer by index. This function can be called when the
 * playback resource is configured and the AVPlayer is in the initialized, prepared, playing, paused, completed, or
 * stopped state.
 * You must manually release the returned OH_AVFormat pointer object when it is no longer needed.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param index Index of the track.
 * @return Track information obtained. If the operation fails, nullptr is returned.
 * Possible cause:
 * 1. The **player** pointer is invalid.
 * 2. The playback resource is invalid.
 * 3. The track index is out of the range for the playback source file array.
 * @since 22
 */
OH_AVFormat *OH_AVPlayer_GetTrackDescription(OH_AVPlayer *player, uint32_t index);

/**
 * @brief Sets the volume for an AVPlayer.
 * This function can be used when the AVPlayer is in the playing or paused state. The value **0** means that the
 * AVPlayer is muted, and **1** means that the original volume is used.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param leftVolume Target volume of the left channel.
 * @param rightVolume Target volume of the right channel.
 * @return {@link AV_ERR_OK}: The volume is set successfully.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player SetVolume** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_SetVolume(OH_AVPlayer *player, float leftVolume, float rightVolume);

/**
 * @brief Seeks to a playback position.
 * This function can be used when the AVPlayer is in the playing or paused state.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param mSeconds Position to seek to, in ms.
 * @param mode Seek mode.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player Seek** fails.
 * @since 11
*/
OH_AVErrCode OH_AVPlayer_Seek(OH_AVPlayer *player, int32_t mSeconds, AVPlayerSeekMode mode);

/**
 * @brief Obtains the playback position, in milliseconds.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param currentTime Pointer to the playback position.
 * @return {@link AV_ERR_OK}: The playback position is obtained.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player GetCurrentTime**
 * fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetCurrentTime(OH_AVPlayer *player, int32_t *currentTime);

/**
 * @brief Obtains the video width.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param videoWidth Pointer to the video width.
 * @return {@link AV_ERR_OK}: The video width is obtained.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetVideoWidth(OH_AVPlayer *player, int32_t *videoWidth);

/**
 * @brief Obtains the video height.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param videoHeight Pointer to the video height.
 * @return {@link AV_ERR_OK}: The video height is obtained.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetVideoHeight(OH_AVPlayer *player, int32_t *videoHeight);

/**
 * @brief Sets the playback speed of the AVPlayer. For details about the playback speed, see {@link AVPlaybackSpeed}.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param speed Playback speed.
 * @return {@link AV_ERR_OK}: The playback speed is set successfully.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_SetPlaybackSpeed(OH_AVPlayer *player, AVPlaybackSpeed speed);

/**
 * @brief Obtains the playback speed of an AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param speed Pointer to the playback speed.
 * @return {@link AV_ERR_OK}: The playback rate is obtained.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player GetPlaybackSpeed**
 * fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetPlaybackSpeed(OH_AVPlayer *player, AVPlaybackSpeed *speed);

/**
 * @brief Obtains the playback rate of an AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param rate Pointer to the playback rate that can be obtained.
 * @return {@link AV_ERR_OK} if the playback rate of the AVPlayer is successfully obtained.
 * Otherwise, an error code defined in {@link native_averrors.h} is returned.
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_GetPlaybackRate(OH_AVPlayer *player, float *rate);

/**
 * @brief Sets the audio stream type for an AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param streamUsage Audio stream type.
 * @return {@link AV_ERR_OK}: The audio stream type is set successfully.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr or **streamUsage** is invalid.
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_SetAudioRendererInfo(OH_AVPlayer *player, OH_AudioStream_Usage streamUsage);

/**
 * @brief Sets the audio interruption mode for an AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param interruptMode Audio interruption mode.
 * @return {@link AV_ERR_OK}: The audio interruption mode is set successfully.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr or **interruptMode** is invalid.
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_SetAudioInterruptMode(OH_AVPlayer *player, OH_AudioInterrupt_Mode interruptMode);

/**
 * @brief Sets the audio effect mode for an AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param effectMode Audio effect mode.
 * @return {@link AV_ERR_OK}: The audio effect mode is set successfully.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr or **effectMode** is invalid.
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_SetAudioEffectMode(OH_AVPlayer *player, OH_AudioStream_AudioEffectMode effectMode);

/**
 * @brief Sets the bit rate used by an HLS player. This function is valid only for HLS network streams.
 * By default, the AVPlayer selects a proper bit rate and speed based on the network connection.
 * You can set a bit rate available in the valid bit rates reported in **INFO_TYPE_BITRATE_COLLECT**. The AVPlayer
 * selects a bit rate that is lower than and closest to the specified bit rate. When ready, you can query the selected
 * bit rate.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param bitRate Bit rate, in kbit/s.
 * @return {@link AV_ERR_OK}: The bit rate is set successfully.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player SelectBitRate**
 * fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_SelectBitRate(OH_AVPlayer *player, uint32_t bitRate);

/**
 * @brief Sets a playback window.
 * This function must be called after **SetSource** and before **Prepare**.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param window Pointer to the OHNativeWindow instance.
 * @return {@link AV_ERR_OK}: The playback window is set successfully.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** or **window** is nullptr, or the execution of **player
 * SetVideoSurface** fails.
 * @since 11
 */
OH_AVErrCode  OH_AVPlayer_SetVideoSurface(OH_AVPlayer *player, OHNativeWindow *window);

/**
 * @brief Obtains the total duration of a media file, in milliseconds.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param duration Pointer to the total duration.
 * @return {@link AV_ERR_OK}: The total duration is obtained.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player GetDuration** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetDuration(OH_AVPlayer *player, int32_t *duration);

/**
 * @brief Obtains the AVPlayer state.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param state Pointer to the state of the AVPlayer.
 * @return {@link AV_ERR_OK}: The AVPlayer state is obtained.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player GetState** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetState(OH_AVPlayer *player, AVPlayerState *state);

/**
 * @brief Checks whether an AVPlayer is playing.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return Check result for whether the AVPlayer is playing. **true** if yes, **false** if the AVPlayer is not playing
 * or the input parameter **player** is nullptr.
 * @since 11
 */
bool OH_AVPlayer_IsPlaying(OH_AVPlayer *player);

/**
 * @brief Checks whether an AVPlayer is looping.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return Check result for whether the AVPlayer is looping. **true** if yes, **false** if the AVPlayer is not looping
 * or the input parameter **player** is nullptr.
 * @since 11
 */
bool OH_AVPlayer_IsLooping(OH_AVPlayer *player);

/**
 * @brief Enables loop playback.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param loop Whether to enable loop playback. **true** to play in a loop, **false** otherwise.
 * @return {@link AV_ERR_OK}: Loop playback is enabled.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player SetLooping** fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_SetLooping(OH_AVPlayer *player, bool loop);

/**
 * @brief Sets an AVPlayer callback.
 * The callbacks {@link OH_AVPlayerOnInfo} and {@link OH_AVPlayerOnError} set by using this function can transfer
 * limited information. In addition, it is inconvenient for the application to distinguish between multiple AVPlayer
 * instances.
 * Starting from API version 12, {@link OH_AVPlayer_SetOnInfoCallback} and {@link OH_AVPlayer_SetOnErrorCallback} are provided to set the callbacks {@link OH_AVPlayerOnInfoCallback}
 * and {@link OH_AVPlayerOnErrorCallback}, respectively.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param callback Callback used to return the result.
 * @return {@link AV_ERR_OK}: The callback is set successfully.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, the input parameter **callback.onInfo** or **
 * onError** is null, or the execution of **player SetPlayerCallback** fails.
 * @since 11
 * @deprecated since 12
 * @useinstead {@link OH_AVPlayer_SetOnInfoCallback} {@link OH_AVPlayer_SetOnErrorCallback}
 */
OH_AVErrCode OH_AVPlayer_SetPlayerCallback(OH_AVPlayer *player, AVPlayerCallback callback);

/**
 * @brief Selects an audio or subtitle track.
 * By default, the first audio track with data is played, and the subtitle track is not played.
 * After the setting takes effect, the original track becomes invalid. Set the subtitle track to the prepared, playing,
 * paused, or completed state, and set the audio track to the prepared state.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param index Index of the track.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player SelectTrack** fails.
 * @since 11
*/
OH_AVErrCode OH_AVPlayer_SelectTrack(OH_AVPlayer *player, int32_t index);

/**
 * @brief Deselects an audio or subtitle track.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param index Index of the track.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player DeselectTrack**
 * fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_DeselectTrack(OH_AVPlayer *player, int32_t index);

/**
 * @brief Obtains the currently valid track. You can set the track to the prepared, playing, paused, or completed state.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param trackType Media type. The value **0** means audio and **1** means video.
 * @param index Pointer to the index of the track.
 * @return {@link AV_ERR_OK}: The track is obtained.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **player GetCurrentTrack**
 * fails.
 * @since 11
 */
OH_AVErrCode OH_AVPlayer_GetCurrentTrack(OH_AVPlayer *player, int32_t trackType, int32_t *index);

/**
 * @brief Sets a callback to return the media key system information for an AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param callback Callback.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** or **callback** is a null pointer, or the execution of **
 * player SetDrmSystemInfoCallback**
 * **SetDrmSystemInfoCallback** or **SetDrmSystemInfoCallback** fails.
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_SetMediaKeySystemInfoCallback(OH_AVPlayer *player,
    Player_MediaKeySystemInfoCallback callback);

/**
 * @brief Obtains the media key system information to create a media key session.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param mediaKeySystemInfo Pointer to the media key system information.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the memory is insufficient.
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_GetMediaKeySystemInfo(OH_AVPlayer *player, DRM_MediaKeySystemInfo *mediaKeySystemInfo);

/**
 * @brief Sets the decryption information.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param mediaKeySession Pointer to the media key session with the decryption feature.
 * @param secureVideoPath Whether a secure decoder is required. **true** if required, **false** otherwise.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or the execution of **SetDecryptionConfig** fails.
 * @since 12
*/
OH_AVErrCode OH_AVPlayer_SetDecryptionConfig(OH_AVPlayer *player, MediaKeySession *mediaKeySession,
    bool secureVideoPath);

/**
 * @brief Sets a callback for the event indicating that the AVPlayer receives a message.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param callback Pointer to the callback. If nullptr is passed in, the listening for AVPlayer messages is canceled.
 * @param userData Pointer to the instance set by the caller.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * **AV_ERR_NO_MEMORY**: Memory allocation fails.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr or the function fails to be executed.
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_SetOnInfoCallback(OH_AVPlayer *player, OH_AVPlayerOnInfoCallback callback, void *userData);

/**
 * @brief Sets a callback for the event indicating that an error occurs in the AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param callback Pointer to the callback. If nullptr is passed in, the listening for AVPlayer errors is canceled.
 * @param userData Pointer to the instance set by the caller.
 * @return {@link AV_ERR_OK}: The operation is successful.
 * **AV_ERR_NO_MEMORY**: Memory allocation fails.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr or the function fails to be executed.
 * @since 12
 */
OH_AVErrCode OH_AVPlayer_SetOnErrorCallback(OH_AVPlayer *player, OH_AVPlayerOnErrorCallback callback, void *userData);

/**
 * @brief Sets the audio volume mode for an AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param volumeMode Volume mode of the audio stream.
 * @return {@link AV_ERR_OK}: The audio volume mode is set successfully.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr or **volumeMode** is invalid.
 * **AV_ERR_INVALID_STATE**: The function is called in an invalid state. It must be in the prepared state.
 * {@link AV_ERR_SERVICE_DIED}: A system error occurs.
 * @since 19
 */
OH_AVErrCode OH_AVPlayer_SetVolumeMode(OH_AVPlayer *player, OH_AudioStream_VolumeMode volumeMode);

/**
 * @brief Sets the playback rate of an AVPlayer within the valid range.
 * The supported states are prepared, playing, paused, and completed.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param rate Playback rate. The value ranges from 0.125 to 4.
 * @return {@link AV_ERR_OK}: The playback speed is set successfully.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The function is called when the AVPlayer is not in the allowed state, or it is called
 * during live streaming.
 * {@link AV_ERR_INVALID_VAL}: The input parameter **player** is nullptr, or **rate** is out of range.
 * @since 20
 */
OH_AVErrCode OH_AVPlayer_SetPlaybackRate(OH_AVPlayer *player, float rate);

/**
 * @brief Sets the loudness of the AVPlayer. This function can be called when the AVPlayer is in the prepared, playing,
 * paused, completed, or stopped state.
 * The default loudness gain is 0.0 dB. The **usage** parameter of the AVPlayer stream must be {@link OH_AudioStream_Usage}.
 * AUDIOSTREAM_USAGE_MUSIC,
 * {@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_MOVIE, or {@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_AUDIOBOOK.
 * The latency mode of the audio renderer must be {@link OH_AudioStream_LatencyMode}.AUDIOSTREAM_LATENCY_MODE_NORMAL.
 * If the audio is played through the high-resolution pipeline, this operation is not supported.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param loudnessGain Loudness, in the range [-90.0, 24.0], in dB.
 * @return {@link AV_ERR_OK}: The loudness is set successfully.
 * {@link AV_ERR_INVALID_VAL}: The **player** parameter is nullptr, or the **loudnessGain** parameter is invalid.
 * **AV_ERR_INVALID_STATE**: The function is called in an abnormal state, or the **usage** parameter of **
 * audioRendererInfo** is not one of the following:
 * {@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_MUSIC,
 * {@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_MOVIE,
 * and {@link OH_AudioStream_Usage}.AUDIOSTREAM_USAGE_AUDIOBOOKs.
 * {@link AV_ERR_SERVICE_DIED}: A system error occurs.
 * @since 21
 */
OH_AVErrCode OH_AVPlayer_SetLoudnessGain(OH_AVPlayer *player, float loudnessGain);

/**
 * @brief Obtains the statistic metrics of the current AVPlayer. This API can be called when the playback resource is
 * set and the AVPlayer is in the prepared, playing, paused, completed, or stopped state.
 * Note that you need to manually release the lifecycle of the {@link OH_AVFormat} pointer object.
 * 
 * @param player Pointer to an OH_AVPlayer instance
 * @return If the operation is successful, the statistic metric information of the AVPlayer is returned. (For details
 * about the key values, see {@link statistic metric information}). Otherwise, **nullptr** is returned.
 * Possible failure cause: The input **player** pointer is invalid.
 * @since 23
 */
OH_AVFormat *OH_AVPlayer_GetPlaybackStatisticMetrics(OH_AVPlayer *player);

/**
 * @brief Adds the subtitle resource represented by the file descriptor to the player. Currently, the external subtitle
 * must be set after the **fdSrc** of the video resource is set in the AVPlayer.
 *  
 * @param player Pointer to an OH_AVPlayer instance
 * @param fd Indicates the file descriptor of subtitle source.
 * @param offset Indicates the offset of media source in file descriptor.
 * @param size Indicates the size of media source.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input player is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_AddFdSubtitleSource(OH_AVPlayer *player, int32_t fd, int64_t offset, int64_t size);

/**
 * @brief Adds the subtitle resource represented by the URL to the player. The external subtitle must be set after the
 * URL is set for the AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param url URL of the subtitle source.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input player is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_AddUrlSubtitleSource(OH_AVPlayer *player, const char *url);

/**
 * @brief Sets the start and end positions of the playback. After the setting, only the content within the specified
 * range of the audio and video file is played. This API can be called when the player is in the initialized, prepared,
 * paused, stopped, or completed state.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param mSecondsStart Start position of playback. The value must be in the range of [0, **duration**). The value **-1*
 * * indicates that the start position is not set, and the playback starts from 0.
 * @param mSecondsEnd End position of playback. The value must be in the range of (**startTimeMs**, **duration**]. The
 * value **-1** indicates that the end position is not set, and the playback ends at the end of the stream.
 * @param closestRange Whether to seek to the frame closest to the specified position.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input player is a null pointer.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed.
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetPlaybackRange(OH_AVPlayer *player, int32_t mSecondsStart, int32_t mSecondsEnd,
    bool closestRange);

/**
 * Mute the media stream. This API can be called only when the AVPlayer is in the prepared, playing,
 * paused, or completed state.
 * @param player Pointer to the OH_AVPlayer instance.
 * @param mediaType Media type. For details, see {@link OH_MediaType} in {@link native_avcodec_base.h}.
 * @param muted **true** indicates that the audio is muted, and **false** indicates that the audio is unmuted.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter is invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed.
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetMediaMuted(OH_AVPlayer *player, OH_MediaType mediaType, bool muted);

/**
 * @brief Obtains the playback position, in milliseconds. This API can be called only when the AVPlayer is in the
 * prepared, playing, paused, or completed state.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return Playback position, in milliseconds.
 * If **player** is a null pointer or invalid, **-1** is returned.
 * @since 23
 */
int32_t OH_AVPlayer_GetPlaybackPosition(OH_AVPlayer *player);

/**
 * @brief Checks whether the media source supports continuous seek. If this API is called when the AVPlayer is in the
 * prepared, playing, paused, or completed state, the actual value is returned. Other, **false** is returned. For
 * devices that do not support the {@link AV_SEEK_CONTINUOUS} mode, **false** is returned.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return @returns **true** indicates that continuous seek is supported.
 * **false** indicates that continuous seek is not supported or is uncertain.
 * @since 23
 */
bool OH_AVPlayer_IsSeekContinuousSupported(OH_AVPlayer *player);

/**
 * @brief Selects a track in the specified switching mode when playing a resource that contains multiple audio and
 * video tracks.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param index Index of the selected track.
 * @param mode Switching mode.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input parameter is invalid.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed.
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SelectTrackWithMode(OH_AVPlayer *player, int32_t index, AVPlayerTrackSwitchMode mode);

/**
 * @brief Subscribes to the maximum audio amplitude update event, which is reported periodically when audio resources
 * are played.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param callback Pointer to the callback function. **nullptr** indicates that the callback is deregistered.
 * @param userData Pointer to user-defined data.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input player is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetAmplitudeUpdateCallback(OH_AVPlayer *player, OH_AVPlayerOnAmplitudeUpdateCallback callback,
    void *userData);

/**
 * @brief Subscribes to the SEI message reception event. This API applies only to HTTP-FLV live streams and is
 * triggered when an SEI message exists in a video stream. This subscription must be initiated before **prepare** is
 * called.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param payloadTypes Load type array.
 * @param typeNum Size of the load type array.
 * @param callback Pointer to the callback function. **nullptr** indicates that the callback is deregistered.
 * @param userData Pointer to user-defined data.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input player is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetSeiReceivedCallback(OH_AVPlayer *player, const int32_t *payloadTypes, uint32_t typeNum,
    OH_AVPlayerOnSeiMessageReceivedCallback callback, void *userData);

/**
 * @brief Obtains the number of items in the SEI message array.
 * 
 * @param message Pointer to the **OH_AVSeiMessageArray** instance.
 * @return Number of items in the SEI message array.
 * @since 23
 */
uint32_t OH_AVSeiMessage_GetSeiCount(OH_AVSeiMessageArray *message);

/**
 * @brief Obtains an SEI message form the SEI message array by index.
 * 
 * @param message Pointer to the **OH_AVSeiMessageArray** instance.
 * @param index Index of the message item.
 * @return SEI of the message item.
 * @since 23
 */
OH_AVFormat *OH_AVSeiMessage_GetSei(OH_AVSeiMessageArray *message, uint32_t index);

/**
 * @brief Sets the video window size for super resolution. This API can be called when the AVPlayer is in the
 * initialized, prepared, playing, paused, completed, or stopped state. The input parameter value must be in the range
 * of 320 × 320 to 1920 × 1080 (pixels).
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param width Window width, in pixels. The value range is [320, 1920].
 * @param height Window height, in pixels. The value range is [320, 1080].
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input player is a null pointer or the parameter is incorrect.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed.
 * {@link AV_ERR_SUPER_RESOLUTION_UNSUPPORTED}: Super resolution is not supported.
 * {@link AV_ERR_SUPER_RESOLUTION_NOT_ENABLED}: Super resolution is not enabled in {@link OH_AVPlaybackStrategy}.
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetTargetVideoWindowSize(OH_AVPlayer *player, int32_t width, int32_t height);

/**
 * @brief Dynamically enables or disables super resolution. This API can be called when the AVPlayer is in the
 * initialized, prepared, playing, paused, completed, or stopped state. You must enable the super resolution feature in
 * {@link OH_AVPlaybackStrategy} before calling **prepare**.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param enabled **true** means to enable super resolution; **false** means the opposite.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input player is a null pointer or the parameter is incorrect.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed.
 * {@link AV_ERR_SUPER_RESOLUTION_UNSUPPORTED}: Super resolution is not supported.
 * {@link AV_ERR_SUPER_RESOLUTION_NOT_ENABLED}: Super resolution is not enabled in {@link OH_AVPlaybackStrategy}.
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetVideoSuperResolutionEnable(OH_AVPlayer *player, bool enabled);

/**
 * @brief Creates a playback strategy instance.
 * 
 * @return Playback strategy instance. If the operation fails, a null pointer is returned.
 * @since 23
 */
OH_AVPlaybackStrategy *OH_AVPlaybackStrategy_Create(void);

/**
 * @brief Releases a playback strategy instance.
 * 
 * @param strategy **OH_AVPlaybackStrategy** instance.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_Destroy(OH_AVPlaybackStrategy *strategy);

/**
 * @brief Selects a stream with width close to the specified value.
 * 
 * @param strategy **OH_AVPlaybackStrategy** used by the AVPlayer.
 * @param width Preferred width for playback when the AVPlayer is started.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredWidth(OH_AVPlaybackStrategy *strategy, int32_t width);

/**
 * @brief Selects a stream with height close to the specified value.
 * 
 * @param strategy **OH_AVPlaybackStrategy** used by the AVPlayer.
 * @param height Preferred height for playback when the AVPlayer is started.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredHeight(OH_AVPlaybackStrategy *strategy, int32_t height);

/**
 * @brief Selects the preferred buffer duration that is close to the specified value.
 * 
 * @param strategy **OH_AVPlaybackStrategy** used by the AVPlayer.
 * @param ms Preferred buffer duration for playback when the AVPlayer is started.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredBufferDuration(OH_AVPlaybackStrategy *strategy, int32_t ms);

/**
 * @brief Enables or disables the preferred HDR mode.
 * 
 * @param strategy Pointer to **OH_AVPlaybackStrategy**.
 * @param enabled The value **true** means to enable the preferred HDR mode, and the value **false** means the opposite.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredHdr(OH_AVPlaybackStrategy *strategy, bool enabled);

/**
 * @brief Sets the preferred subtitle language.
 * 
 * @param strategy Pointer to **OH_AVPlaybackStrategy**.
 * @param lang Pointer to subtitle language code (for example, **zh**).
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredSubtitleLanguage(OH_AVPlaybackStrategy *strategy, const char *lang);

/**
 * @brief Sets the preferred audio language.
 * 
 * @param strategy Pointer to **OH_AVPlaybackStrategy**.
 * @param lang Pointer to audio language code (for example, **en**).
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredAudioLanguage(OH_AVPlaybackStrategy *strategy, const char *lang);

/**
 * @brief Sets the media type to be muted during playback.
 * 
 * @param strategy Pointer to **OH_AVPlaybackStrategy**.
 * @param mediaType Type of the media to be muted.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetMutedMediaType(OH_AVPlaybackStrategy *strategy, OH_MediaType mediaType);

/**
 * @brief Sets whether to display the first frame during the **prepare** state.
 * 
 * @param strategy Pointer to **OH_AVPlaybackStrategy**.
 * @param enabled **true** to display, **false** otherwise.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetShowFirstFrameOnPrepare(OH_AVPlaybackStrategy *strategy, bool enabled);

/**
 * @brief Sets the threshold for automatic quick playback.
 * 
 * @param strategy Pointer to **OH_AVPlaybackStrategy**.
 * @param seconds Threshold for automatic quick playback.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetThresholdForAutoQuickPlay(OH_AVPlaybackStrategy *strategy, double seconds);

/**
 * @brief Sets whether to enable super resolution.
 * 
 * @param strategy Pointer to **OH_AVPlaybackStrategy**.
 * @param enabled **true** to enable, **false** otherwise.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetSuperResolutionEnable(OH_AVPlaybackStrategy *strategy, bool enabled);

/**
 * @brief Sets the preferred buffer duration during playback (double type, in seconds).
 * 
 * @param strategy Pointer to **OH_AVPlaybackStrategy**.
 * @param seconds Buffer duration, in seconds.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetPreferredBufferDurationForPlaying(OH_AVPlaybackStrategy *strategy,
    double seconds);

/**
 * @brief Sets whether to continue decoding when the audio is muted.
 * 
 * @param strategy Pointer to **OH_AVPlaybackStrategy**.
 * @param enabled The value **true** means to continue decoding when the audio is muted, and **false** means the
 * opposite.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input strategy is a null pointer.
 * @since 23
 */
OH_AVErrCode OH_AVPlaybackStrategy_SetKeepDecodingOnMute(OH_AVPlaybackStrategy *strategy, bool enabled);

/**
 * @brief Sets the playback strategy for the AVPlayer. This API can be called only when the AVPlayer is in the
 * initialized state.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param strategy Playback strategy instance.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input player is a null pointer.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed.
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetPlaybackStrategy(OH_AVPlayer *player, OH_AVPlaybackStrategy *strategy);

/**
 * @brief Obtains the statistics of the current AVPlayer. This API can be called only when the AVPlayer is in the
 * prepared, playing, or paused state.
 * 
 * @param player Pointer to an OH_AVPlayer instance
 * @return Pointer to the **OH_AVFormat** instance.
 * If the **player** is a null pointer or invalid, a null pointer is returned.
 * @since 23
 */
OH_AVFormat* OH_AVPlayer_GetPlaybackInfo(OH_AVPlayer *player);

/**
 * @brief Sets the **OH_AVMediaSource** to the AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param source Media source.
 * @return Execution result of the function.
 * {@link AV_ERR_OK}: The execution is successful.
 * {@link AV_ERR_INVALID_VAL}: The input **player** or **source** is a null pointer, or the **player** fails to set the URL
 * source.
 * @since 23
 */
OH_AVErrCode OH_AVPlayer_SetMediaSource(OH_AVPlayer *player, OH_AVMediaSource *source);

/**
 * @brief Obtains the number of tracks of the media source of the AVPlayer.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @return Number of tracks.
 * @since 23
 */
uint32_t OH_AVPlayer_GetTrackCount(OH_AVPlayer *player);

/**
 * @brief Obtains the track information of the AVPlayer by index.
 * 
 * @param player Pointer to the OH_AVPlayer instance.
 * @param trackIndex Index of the track array.
 * @return Pointer to the **OH_AVFormat** instance.
 * If **player** is a null pointer or invalid, or **trackIndex** is invalid, a null pointer is returned.
 * @since 23
 */
OH_AVFormat *OH_AVPlayer_GetTrackFormat(OH_AVPlayer *player, uint32_t trackIndex);

/** 
 * @brief Method to set audio pcm data callback. This API can be called only 
 *     when the avplayer is in the idle or initialized state. 
 * @param player Pointer to an OH_AVPlayer instance. 
 * @param callback Pointer to callback function, nullptr indicates unregister callback. 
 * @param userData Pointer to user specific data. 
 * @return Function result code. 
 *         {@link AV_ERR_OK} if the execution is successful. 
 *         {@link AV_ERR_INVALID_VAL} if input player is null or player SetPCMOutputCallback failed. 
 *         {@link AV_ERR_OPERATE_NOT_PERMIT} if called in unsupported state. 
 * @since 26.0.0 
 */ 
OH_AVErrCode OH_AVPlayer_SetPCMOutputCallback(OH_AVPlayer *player, OH_AVPlayerPCMOutputCallback callback, 
    void *userData);


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

/**
 * @brief Method to set audio pcm data process callback. This API can be called only 
 * when the avplayer is in the idle or initialized state.
 * @param player Pointer to an OH_AVPlayer instance.
 * @param callback Pointer to callback function, nullptr indicates unregister callback.
 * @param userData Pointer to user specific data.
 * @return Function result code.
 *         {@link AV_ERR_OK} if the execution is successful.
 *         {@link AV_ERR_INVALID_VAL} if input player is null or player SetPCMProcessorCallback failed.
 *         {@link AV_ERR_OPERATE_NOT_PERMIT} if called in unsupported state. 
 * @since 26.0.0
 */
OH_AVErrCode OH_AVPlayer_SetPCMProcessorCallback(OH_AVPlayer *player, OH_AVPlayerPCMProcessorCallback callback,
    void *userData);

/**
 * @brief Sets the maximum amount of data that can be returned at a time during audio post-processing.
 * Allows some PCM data to be cached and returned with the next PCM data. This API can be called only 
 * when the avplayer is in the idle or initialized state.
 * @param player Pointer to an OH_AVPlayer instance.
 * @param maxProcessedPCMLen the maximum amount of PCM data returned at one time, in the range (0, 5MB].
 *     OH_AVPlayerPCMProcessorCallback ensures that the returned pcmBuffer's Capacity is not less than this value.
 * @return Function result code.
 *         {@link AV_ERR_OK} if the execution is successful.
 *         {@link AV_ERR_INVALID_VAL} if input player is null or maxProcessedPCMLen is error.
 *         {@link AV_ERR_OPERATE_NOT_PERMIT} if called in unsupported state. 
 * @since 26.0.0
 */
OH_AVErrCode OH_AVPlayer_SetPCMProcessorMaxLen(OH_AVPlayer *player, int32_t maxProcessedPCMLen);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVPLAYER_H
