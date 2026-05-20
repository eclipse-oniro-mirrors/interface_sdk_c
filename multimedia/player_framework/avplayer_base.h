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
 * @{
 *
 * @brief Provides APIs of Playback capability for Media Source.
 *
 * @Syscap SystemCapability.Multimedia.Media.AVPlayer
 * @since 11
 */
/**
 * @file avplayer_base.h
 *
 * @brief The file declares the structs and enums of the AVPlayer.
 * 
 * @kit MediaKit
 * @library libavplayer.so
 * @since 11
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVPLAYER_BASH_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVPLAYER_BASH_H

#include <stdint.h>

#include "native_avformat.h"
#include "native_avbuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OH_AVPlayer OH_AVPlayer;

/**
 * @brief Defines a struct for the SEI message array.
 * 
 * @since 23
 */
typedef struct OH_AVSeiMessageArray OH_AVSeiMessageArray;

/**
 * @brief Defines a struct for the audio and video playback strategy.
 * 
 * @since 23
 */
typedef struct OH_AVPlaybackStrategy OH_AVPlaybackStrategy;

/**
 * @brief Enumerates the AVPlayer states.
 * 
 * @since 11
 */
typedef enum AVPlayerState {
    /* idle states */
    AV_IDLE = 0,
    /* initialized states */
    AV_INITIALIZED = 1,
    /* prepared states */
    AV_PREPARED = 2,
    /* playing states */
    AV_PLAYING = 3,
    /* paused states */
    AV_PAUSED = 4,
    /* stopped states */
    AV_STOPPED = 5,
    /* Play to the end states */
    AV_COMPLETED = 6,
    /* released states */
    AV_RELEASED = 7,
    /* error states */
    AV_ERROR = 8,
} AVPlayerState;

/**
 * @brief Enumerates the seek modes.
 * 
 * @since 11
 */
typedef enum AVPlayerSeekMode {
    /* sync to keyframes after the time point. */
    AV_SEEK_NEXT_SYNC = 0,
    /* sync to keyframes before the time point. */
    AV_SEEK_PREVIOUS_SYNC,
    /**
     * @brief Seeks to the frame closest to the specified position.
     * 
     * @since 12
     */
    AV_SEEK_CLOSEST = 2,
    /**
     * Seeks in continuous drag mode. This mode provides a smoother drag experience, but the device must support
     * continuous seeking for the current stream. Before using this mode, check whether continuous seeking is supported.
     *  For details, see {@link OH_AVPlayer_IsSeekContinuousSupported}.<br>**Since**: 23
     */
    AV_SEEK_CONTINUOUS = 3,
} AVPlayerSeekMode;

/**
 * @brief Enumerates the playback speeds of the AVPlayer.
 * 
 * @since 11
 */
typedef enum AVPlaybackSpeed {
    /* Video playback at 0.75x normal speed */
    AV_SPEED_FORWARD_0_75_X,
    /* Video playback at normal speed */
    AV_SPEED_FORWARD_1_00_X,
    /* Video playback at 1.25x normal speed */
    AV_SPEED_FORWARD_1_25_X,
    /* Video playback at 1.75x normal speed */
    AV_SPEED_FORWARD_1_75_X,
    /* Video playback at 2.0x normal speed */
    AV_SPEED_FORWARD_2_00_X,
    /**
     * @brief Plays the video at 0.5 times the normal speed.
     * 
     * @since 12
     */
    AV_SPEED_FORWARD_0_50_X,
    /**
     * @brief Plays the video at 1.5 times the normal speed.
     * 
     * @since 12
     */
    AV_SPEED_FORWARD_1_50_X,
    /**
     * @brief Plays the video at 3.0 times the normal speed.
     * 
     * @since 13
    */
    AV_SPEED_FORWARD_3_00_X,
    /**
     * @brief Plays the video at 0.25 times the normal speed.
     * 
     * @since 13
    */
    AV_SPEED_FORWARD_0_25_X,
    /**
     * @brief Plays the video at 0.125 times the normal speed.
     * 
     * @since 13
    */
    AV_SPEED_FORWARD_0_125_X,
} AVPlaybackSpeed;

/**
 * @brief Enumerates the types of messages received by the AVPlayer.
 * The enum can be used in **OH_AVPlayerOnInfoCallback** and **OH_AVPlayerOnInfo** (deprecated) to indicate the type of
 * information received by the AVPlayer.
 * Starting from API version 12, you are advised to use {@link OH_AVPlayerOnInfoCallback} instead. Different
 * information (**infoBody**) can be obtained for different **OnInfo** types. **infoBody** contains the key-value pairs.
 *  For details, see the following enumerated value table.
 * If you are using API version 11 for development, use **OH_AVPlayerOnInfo (deprecated)**. For details about the
 * mappings used in this deprecated API, see {@link OH_AVPlayerOnInfo}.
 * 
 * @since 11
 */
typedef enum AVPlayerOnInfoType {
    /* return the message when seeking done. */
    AV_INFO_TYPE_SEEKDONE = 0,
    /* return the message when speeding done. */
    AV_INFO_TYPE_SPEEDDONE = 1,
    /* return the message when select bitrate done */
    AV_INFO_TYPE_BITRATEDONE = 2,
    /* return the message when playback is end of steam. */
    AV_INFO_TYPE_EOS = 3,
    /* return the message when PlayerStates changed. */
    AV_INFO_TYPE_STATE_CHANGE = 4,
    /* return the current posion of playback automatically. */
    AV_INFO_TYPE_POSITION_UPDATE = 5,
    /* return the playback message. */
    AV_INFO_TYPE_MESSAGE = 6,
    /* return the message when volume changed. */
    AV_INFO_TYPE_VOLUME_CHANGE = 7,
    /* return the message when video size is first known or updated. */
    AV_INFO_TYPE_RESOLUTION_CHANGE = 8,
    /* return multiqueue buffering time. */
    AV_INFO_TYPE_BUFFERING_UPDATE = 9,
    /* return hls bitrate.
       Bitrate is to convert data into uint8_t array storage,
       which needs to be forcibly converted to uint32_t through offset access. */
    AV_INFO_TYPE_BITRATE_COLLECT = 10,
    /* return the message when audio focus changed. */
    AV_INFO_TYPE_INTERRUPT_EVENT = 11,
    /* return the duration of playback. */
    AV_INFO_TYPE_DURATION_UPDATE = 12,
    /* return the playback is live stream. */
    AV_INFO_TYPE_IS_LIVE_STREAM = 13,
    /* return the message when track changes. */
    AV_INFO_TYPE_TRACKCHANGE = 14,
    /* return the message when subtitle track info updated. */
    AV_INFO_TYPE_TRACK_INFO_UPDATE = 15,
    /* return the subtitle of playback. */
    AV_INFO_TYPE_SUBTITLE_UPDATE = 16,
    /**
     * Message returned when the audio output device changes.<br> If **key** is set to **
     * OH_PLAYER_AUDIO_DEVICE_CHANGE_REASON**, the value type is int32_t. The system uses int32_t to transfer the value,
     *  and the application uses int32_t to obtain the value.
     */
    AV_INFO_TYPE_AUDIO_OUTPUT_DEVICE_CHANGE = 17,

    /**
     * @brief Message returned when the playback rate is applied.
     *  If **key** is set to **OH_PLAYER_PLAYBACK_RATE**, the value type is float. The system uses float to transfer the value, and the application uses float to obtain the value.
     * 
     * @since 20
     */
    AV_INFO_TYPE_PLAYBACK_RATE_DONE = 18,
  
    /**
     * @brief Message returned when the super resolution changes.
     * 
     * @since 23
     */
    AV_INFO_TYPE_SUPER_RESOLUTION_CHANGED = 19,
} AVPlayerOnInfoType;

/**
 * @brief Enumerates the types of buffer messages of the AVPlayer.
 * 
 * @since 12
 */
typedef enum AVPlayerBufferingType {
    /**
     * Buffering start message.
     */
    AVPLAYER_BUFFERING_START = 1,

    /**
     * Buffering end message.
     */
    AVPLAYER_BUFFERING_END,

    /**
     * Buffer execution progress, in percentage. The value is an integer in the range [0, 100].
     */
    AVPLAYER_BUFFERING_PERCENT,

    /**
     * Duration that cached data can be played, in milliseconds.
     */
    AVPLAYER_BUFFERING_CACHED_DURATION,
} AVPlayerBufferingType;

/**
 * @brief Enumerates the track switching modes.
 * 
 * @since 23
 */
typedef enum AVPlayerTrackSwitchMode {
    /**
     * Switch tracks smoothly.
     */
    AV_TRACK_SWITCH_MODE_SMOOTH = 0,
    /**
     * Switch tracks by segment.
     */
    AV_TRACK_SWITCH_MODE_SEGMENT = 1,
    /**
     * Switch to the closest track.
     */
    AV_TRACK_SWITCH_MODE_CLOSEST = 2,
} AVPlayerTrackSwitchMode;

/**
 * @brief Result of Video output.
 * @since 26.0.0
 */
typedef enum OH_VideoOutputResult {
    /**
     * @brief Output one decoded video frame.
     * @since 26.0.0
     */
    OH_VIDEO_OUTPUT_OK = 0,
    /**
     * @brief No frame ready to render.
     * @since 26.0.0
     */
    OH_VIDEO_OUTPUT_NO_IMAGE = 1,
} OH_VideoOutputResult;

/**
 * @brief Pointer to the key for obtaining the AVPlayer state. The value is of the int32_t type.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_STATE;

/**
 * @brief Pointer to the key for obtaining the AVPlayer state change reason. The value is of the int32_t type.
 * The value **1** means that the change is triggered by user operations, and **2** means that the change is triggered
 * by the system.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_STATE_CHANGE_REASON;

/**
 * @brief Pointer to the key for obtaining the volume. The value type is float.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_VOLUME;

/**
 * @brief Pointer to the key for obtaining the bit rate array. The value is of the uint8_t byte array type. When this
 * key is used to obtain information, you need to:
 * Use a pointer variable of the uint8_t type to store the bit rate list and use a variable of the size_t type to store
 * the byte array length.
 * Then it allocates several storage spaces of the uint32_t type to receive the bit rate integer of the uint32_t type,
 * which is converted from the uint8_t byte array.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_BITRATE_ARRAY;

/**
 * @brief Pointer to the key for obtaining the audio interruption type. The value is of the int32_t type.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_AUDIO_INTERRUPT_TYPE;

/**
 * @brief Pointer to the key for obtaining the FORCE type of audio interruption. The value is of the int32_t type.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_AUDIO_INTERRUPT_FORCE;

/**
 * @brief Pointer to the key for obtaining the HINT type of audio interruption. The value is of the int32_t type.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_AUDIO_INTERRUPT_HINT;

/**
 * @brief Pointer to the key for obtaining the audio device change reason. The value is of the int32_t type.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_AUDIO_DEVICE_CHANGE_REASON;

/**
 * @brief Pointer to the key for obtaining the type of the buffer update message. The value type is {@link AVPlayerBufferingType}.
 * When this key is used to obtain information, you must use a variable of the int32_t type to save the result and then
 * convert the result to a value of AVPlayerBufferingType.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_BUFFERING_TYPE;

/**
 * @brief Pointer to the key for obtaining the value of the buffer update message. The value is of the int32_t type.
 * For details, see {@link AVPlayerBufferingType}.
 * This parameter is valid only when the buffer update message type is **AVPLAYER_BUFFERING_PERCENT** or **
 * AVPLAYER_BUFFERING_CACHED_DURATION**.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_BUFFERING_VALUE;

/**
 * @brief Pointer to the key for obtaining the playback progress after the seek operation. The value is of the int32_t
 * type.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_SEEK_POSITION;

/**
 * @brief Pointer to the key for obtaining the playback speed. The value type is {@link AVPlaybackSpeed}.
 * When this key is used to obtain information, you must use a variable of the int32_t type to save the result and then
 * convert the result to a value of AVPlaybackSpeed.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_PLAYBACK_SPEED;

/**
 * @brief Pointer to the key for obtaining the bit rate array. The value is of the uint8_t byte array type. When this
 * key is used to obtain information, you need to:
 * Use a pointer variable of the uint8_t type to store the bit rate list and use a variable of the size_t type to store
 * the byte array length.
 * Then it allocates several storage spaces of the uint32_t type to receive the bit rate integer of the uint32_t type,
 * which is converted from the uint8_t byte array.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_BITRATE;

/**
 * @brief Pointer to the key for obtaining the playback progress information. The value is of the int32_t type.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_CURRENT_POSITION;

/**
 * @brief Pointer to the key for obtaining the media asset duration. The value type is int64_t.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_DURATION;

/**
 * @brief Pointer to the key for obtaining the video width. The value is of the int32_t type.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_VIDEO_WIDTH;

/**
 * @brief Pointer to the key for obtaining the video height. The value is of the int32_t type.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_VIDEO_HEIGHT;

/**
 * @brief Pointer to the key for obtaining the type of message received by the AVPlayer. The value is of the int32_t
 * type.
 * The value **1** means that the video frame starts to be rendered.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_MESSAGE_TYPE;

/**
 * @brief Pointer to the key for checking whether a media asset is live streaming. The value is of the int32_t type.
 * The value **1** means live streaming.
 * 
 * @since 12
 */
extern const char* OH_PLAYER_IS_LIVE_STREAM;

/**
 * Sei message key for payload type.
 * @since 23
 */
extern const char* OH_PLAYER_SEI_PAYLOAD_TYPE;

/**
 * Sei message key for payload content.
 * @since 23
 */
extern const char* OH_PLAYER_SEI_PAYLOAD_CONTENT;

/**
 * @brief Pointer to the key for indicating the enable state of the super resolution feature. The value type is int32_t.
 *  The value **1** indicates that the feature is enabled, and **0** indicates the opposite. It is used for information
 * callback when the super resolution state changes.
 * 
 * @since 23
 */
extern const char* OH_PLAYER_SUPER_RESOLUTION_ENABLE_STATE;

/**
 * @brief Pointer to the key for indicating the track index in the track change information. The value type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_PLAYER_TRACH_CHANGE_INFO_TRACK_INDEX;

/**
 * @brief Pointer to the key for indicating whether the track is selected in the track change information. The value
 * type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_PLAYER_TRACH_CHANGE_INFO_TRACK_SELECTED;

/**
 * @brief Pointer to the key for indicating the duration in the subtitle update information. The value type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_PLAYER_SUBTITLE_UPDATE_INFO_DURATION;

/**
 * @brief Pointer to the key for indicating the start time in the subtitle update information. The value type is
 * int32_t.
 * 
 * @since 23
 */
extern const char* OH_PLAYER_SUBTITLE_UPDATE_INFO_START_TIME;

/**
 * @brief Pointer to the key for indicating the subtitle text content in the subtitle update information. The value
 * type is string.
 * 
 * @since 23
 */
extern const char* OH_PLAYER_SUBTITLE_UPDATE_INFO_TEXT;

/**
 * @brief Pointer to the key for obtaining the playback rate. The value is a floating-point number.
 * 
 * @since 20
 */
extern const char* OH_PLAYER_PLAYBACK_RATE;
 
/**
 * @brief Pointer to the key for obtaining whether the media resource contains video tracks. The value is of the
 * int32_t type.
 * The value **1** means that the media resource contains video tracks, and the value **0** means the opposite.
 * 
 * @since 22
 */
extern const char* OH_PLAYER_MD_KEY_HAS_VIDEO;
 
/**
 * @brief Pointer to the key for obtaining whether the media resource contains audio tracks. The value is of the
 * int32_t type.
 * The value **1** means that the media resource contains audio tracks, and the value **0** means the opposite.
 * 
 * @since 22
 */
extern const char* OH_PLAYER_MD_KEY_HAS_AUDIO;
 
/**
 * @brief Pointer to the key for obtaining whether the media resource contains subtitle tracks. The value is of the
 * int32_t type.
 * The value **1** means that the media resource contains subtitle tracks, and the value **0** means the opposite.
 * 
 * @since 22
 */
extern const char* OH_PLAYER_MD_KEY_HAS_SUBTITLE;
 
/**
 * @brief Pointer to the key for obtaining the track index information of a media resource. The value is of the int32_t
 * type.
 * 
 * @since 22
 */
extern const char* OH_PLAYER_MD_KEY_TRACK_INDEX;

/**
 * @brief Called when the AVPlayer receives a message.
 * 
 * @param player Pointer to an OH_AVPlayer instance.
 * @param type Message type. For details about the available options, see {@link AVPlayerOnInfoType}. For details about
 * the mappings between **type** and **extra** values, see the function description.
 * @param extra Other information, such as the start time and position of the media file to play.
 * @since 11
 * @deprecated since 12
 * @useinstead {@link OH_AVPlayerOnInfoCallback}
 */
typedef void (*OH_AVPlayerOnInfo)(OH_AVPlayer *player, AVPlayerOnInfoType type, int32_t extra);

/**
 * @brief Called when the AVPlayer receives a message. If this callback is successfully set, the **OH_AVPlayerOnInfo**
 * function will not be invoked.
 * 
 * @param player Pointer to an OH_AVPlayer instance.
 * @param type Message type. For details about the available options, see {@link AVPlayerOnInfoType}.
 * @param infoBody Pointer to the message. The pointer is valid only in this callback.
 * @param userData Pointer to the instance provided by the caller when setting the callback function.
 * @since 12
 */
typedef void (*OH_AVPlayerOnInfoCallback)(OH_AVPlayer *player, AVPlayerOnInfoType type, OH_AVFormat* infoBody,
    void *userData);

/**
 * @brief Called when an error occurs in the AVPlayer. This callback is available in API version 9 or later.
 * 
 * @param player Pointer to an OH_AVPlayer instance.
 * @param errorCode Error code.
 * **AV_ERR_NO_MEMORY**: No memory. The value is **1**.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The value is **2**.
 * {@link AV_ERR_INVALID_VA}: Invalid value. The value is **3**.
 * **AV_ERR_IO**: I/O error. The value is **4**.
 * **AV_ERR_TIMEOUT**: Timeout. The value is **5**.
 * **AV_ERR_UNKNOWN**: Unknown error. The value is **6**.
 * {@link AV_ERR_SERVICE_DIED}: The service is dead. The value is **7**.
 * **AV_ERR_INVALID_STATE**: The operation is not supported in the current state. The value is **8**.
 * {@link AV_ERR_UNSUPPORT}: The function is not supported. The value is **9**.
 * **AV_ERR_EXTEND_START**: Initial value for extended error codes. The value is **100**.
 * @param errorMsg Error message.
 * @since 11
 * @deprecated since 12
 * @useinstead {@link OH_AVPlayerOnErrorCallback}
 */
typedef void (*OH_AVPlayerOnError)(OH_AVPlayer *player, int32_t errorCode, const char *errorMsg);

/**
 * @brief Called when an error occurs in the AVPlayer. If this callback is successfully set, the **OH_AVPlayerOnError**
 * function will not be invoked.
 * 
 * @param player Pointer to an OH_AVPlayer instance.
 * @param errorCode Error code.
 * **AV_ERR_NO_MEMORY**: No memory. The value is **1**.
 * {@link AV_ERR_OPERATE_NOT_PERMIT}: The operation is not allowed. The value is **2**.
 * {@link AV_ERR_INVALID_VA}: Invalid value. The value is **3**.
 * **AV_ERR_IO**: I/O error. For API versions 12 and 13, the value is **4**. Starting from API version 14, it
 * corresponds to more specific error codes ranging from 5411001 to 5411011.
 * **AV_ERR_TIMEOUT**: Timeout. The value is **5**.
 * **AV_ERR_UNKNOWN**: Unknown error. The value is **6**.
 * {@link AV_ERR_SERVICE_DIED}: The service is dead. The value is **7**.
 * **AV_ERR_INVALID_STATE**: The operation is not supported in the current state. The value is **8**.
 * {@link AV_ERR_UNSUPPORT}: The function is not supported. The value is **9**.
 * **AV_ERR_EXTEND_START**: Initial value for extended error codes. The value is **100**.
 * @param errorMsg Error message, only valid in callback function.
 * @param userData Pointer to user specific data.
 * @since 12
 */
typedef void (*OH_AVPlayerOnErrorCallback)(OH_AVPlayer *player, int32_t errorCode, const char *errorMsg,
    void *userData);

/**
 * @brief The struct contains the set of the **OH_AVPlayerOnInfo** and **OH_AVPlayerOnError** callback function
 * pointers. To ensure the normal running of OH_AVPlayer, you must register the instance of this struct with the
 * OH_AVPlayer instance and process the information reported by the callback functions.
 * 
 * @param onInfo Monitor OH_AVPlayer operation information, refer to {@link OH_AVPlayerOnInfo}
 * @param onError Monitor OH_AVPlayer operation errors, refer to {@link OH_AVPlayerOnError}
 * @since 11
 * @deprecated since 12
 * @useinstead {@link OH_AVPlayerOnInfoCallback} {@link OH_AVPlayerOnErrorCallback}
 */
typedef struct AVPlayerCallback {
    OH_AVPlayerOnInfo onInfo;
    OH_AVPlayerOnError onError;
} AVPlayerCallback;

/**
 * @brief Called when the maximum audio amplitude is calculated.
 * 
 * @param player Pointer to an OH_AVPlayer instance.
 * @param amplitudes The pointer to the maximum audio level values array.
 * Note: the amplitudes array will be released after callback automatically.
 * If necessary, user need copy the data for the further use.
 * @param size Size of the maximum audio amplitude array.
 * @param userData Pointer to user specific data.
 * @since 23
 */
typedef void (*OH_AVPlayerOnAmplitudeUpdateCallback)(OH_AVPlayer *player, double *amplitudes, uint32_t size,
    void *userData);

/**
 * @brief Called for obtaining SEI messages. This function is used to subscribe to SEI message events and returns
 * detailed SEI information.
 * 
 * @param player Pointer to an OH_AVPlayer instance
 * @param message SEI message array.
 * Note: the message array will be released after callback automatically.
 * If necessary, user need copy the data for the further use.
 * @param playbackPosition Playback position.
 * @param userData Pointer to user specific data
 * @since 23
 */
typedef void (*OH_AVPlayerOnSeiMessageReceivedCallback)(OH_AVPlayer *player, OH_AVSeiMessageArray *message,
    int32_t playbackPosition, void *userData);

/** 
 * @brief Describes the handle used to obtain the decoded audio PCM data. 
 * @param player Pointer to an OH_AVPlayer instance 
 * @param pcmBuffer Decoded PCM audio data. The pcmBuffer is valid only within this callback, 
 *     and released by the player after the callback returns. 
 * @param userData Pointer to user specific data 
 * @since 26.0.0 
 */ 
typedef void (*OH_AVPlayerPCMOutputCallback)(OH_AVPlayer *player, OH_AVBuffer *pcmBuffer, void *userData);

/**
 * @brief This callback provides a PCM buffer for processing.
 * @param player Pointer to an OH_AVPlayer instance
 * @param pcmBuffer Decoded PCM audio data.
 * @param userData Pointer to user specific data
 * @since 26.0.0
 */
typedef void (*OH_AVPlayerPCMProcessorCallback)(OH_AVPlayer *player, OH_AVBuffer *pcmBuffer, void *userData);

/**
 * @brief Pointer to the key for obtaining the preparation duration in the statistic metric information. The value type
 * is uint32_t, and the unit is millisecond.
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_PREPARE_DURATION;

/**
 * @brief Pointer to the key for obtaining the resource connection duration in the statistic metric information. The
 * value type is uint32_t, and the unit is millisecond.
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_RESOURCE_CONNECTION_DURATION;

/**
 * @brief Pointer to the key for obtaining the first-frame decapsulation duration in the statistic metric information.
 * The value type is uint32_t, and the unit is millisecond.
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_FIRST_FRAME_DECAPSULATION_DURATION;

/**
 * @brief Pointer to the key for obtaining the total playback duration in the statistic metric information. The value
 * type is uint32_t, and the unit is millisecond.
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_TOTAL_PLAYING_TIME;

/**
 * @brief Pointer to the key for obtaining the total number of media resource loading requests in the statistic metric
 * information. The value type is uint32_t.
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_DOWNLOAD_REQUEST_COUNT;

/**
 * @brief Pointer to the key for obtaining the total media resource loading duration in the statistic metric
 * information. The value type is uint32_t, and the unit is millisecond.
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_DOWNLOAD_TOTAL_TIME;

/**
 * @brief Pointer to the key for obtaining the total size of loaded media resources in the statistic metric information.
 *  The value type is int64_t.
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_DOWNLOAD_TOTAL_SIZE;

/**
 * @brief Pointer to the key for obtaining the total number of stalling times in the statistic metric information. The
 * value type is uint32_t.
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_STALLING_COUNT;

/**
 * @brief Pointer to the key for obtaining the total stalling duration in the statistic metric information. The value
 * type is uint32_t, and the unit is millisecond.
 * 
 * @since 23
 */
extern const char* OH_MEDIA_EVENT_INFO_TOTAL_STALLING_TIME;

/**
 * Playback info key for server ip address.
 * @since 23
 */
extern const char* OH_PLAYER_SERVER_IP_ADDRESS;

/**
 * Playback info key for downloading state.
 * @since 23
 */
extern const char* OH_PLAYER_IS_DOWNLOADING;

/**
 * Playback info key for buffer duration.
 * @since 23
 */
extern const char* OH_PLAYER_BUFFER_DURATION;

/**
 * Playback info key for download rate.
 * @since 23
 */
extern const char* OH_PLAYER_DOWNLOAD_RATE;

/**
 * Playback info key for average download rate.
 * @since 23
 */
extern const char* OH_PLAYER_AVG_DOWNLOAD_RATE;

#ifdef __cplusplus
}
#endif
#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVPLAYER_BASH_H
