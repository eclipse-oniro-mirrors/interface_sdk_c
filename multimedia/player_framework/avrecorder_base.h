/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup AVRecorder
 * @{
 *
 * @brief Provides APIs of request capability for Recorder.
 *
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 * @}
 */
/**
 * @file avrecorder_base.h
 *
 * @brief The file declares the struct and enums used by the AVRecorder.
 * 
 * @kit MediaKit
 * @library libavrecorder.so
 * @since 18
 */
 
#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_BASE_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_BASE_H

#include <string>
#include <stdint.h>
#include "multimedia/media_library/media_asset_base_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct initializes an AVRecorder.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder OH_AVRecorder;

/**
 * @brief Enumerates the audio source types of the AVRecorder.
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_AudioSourceType {
    /* Default audio source type. */
    AVRECORDER_DEFAULT = 0,
    /* Source type mic. */
    AVRECORDER_MIC = 1,
    /* Source type Voice recognition. */
    AVRECORDER_VOICE_RECOGNITION = 2,
    /* Source type Voice communication. */
    AVRECORDER_VOICE_COMMUNICATION = 7,
    /* Source type Voice message. */
    AVRECORDER_VOICE_MESSAGE = 10,
    /* Source type Camcorder. */
    AVRECORDER_CAMCORDER = 13,
} OH_AVRecorder_AudioSourceType;

/**
 * @brief Enumerates the video source types of the AVRecorder.
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_VideoSourceType {
    /* Surface raw data. */
    AVRECORDER_SURFACE_YUV = 0,
    /* Surface ES data. */
    AVRECORDER_SURFACE_ES = 1,
} OH_AVRecorder_VideoSourceType;

/**
 * @brief Enumerates the MIME types of the encoder.
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_CodecMimeType {
    /* H.264 codec MIME type. */
    AVRECORDER_VIDEO_AVC = 2,
    /* AAC codec MIME type. */
    AVRECORDER_AUDIO_AAC = 3,
    /* mp3 codec MIME type. */
    AVRECORDER_AUDIO_MP3 = 4,
    /* G711-mulaw codec MIME type. */
    AVRECORDER_AUDIO_G711MU = 5,
    /* MPEG4 codec MIME type. */
    AVRECORDER_VIDEO_MPEG4 = 6,
    /* H.265 codec MIME type. */
    AVRECORDER_VIDEO_HEVC = 8,
    /* AMR-NB codec MIME type. */
    AVRECORDER_AUDIO_AMR_NB = 9,
    /* AMR-WB codec MIME type. */
    AVRECORDER_AUDIO_AMR_WB = 10,
} OH_AVRecorder_CodecMimeType;

/**
 * @brief Enumerates the Container Format Types (CFTs).
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_ContainerFormatType {
    /* A video container format type mp4. */
    AVRECORDER_CFT_MPEG_4 = 2,
    /* An audio container format type m4a. */
    AVRECORDER_CFT_MPEG_4A = 6,
    /* An audio container format type amr. */
    AVRECORDER_CFT_AMR = 8,
    /* An audio container format type mp3. */
    AVRECORDER_CFT_MP3 = 9,
    /* An audio container format type wav. */
    AVRECORDER_CFT_WAV = 10,
    
    /**
     * @brief Audio container format aac (with ADTS header).
     *  
     * @since 20
     */
    AVRECORDER_CFT_AAC = 11,
} OH_AVRecorder_ContainerFormatType;

/**
 * @brief Enumerates the AVRecorder states.
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_State {
    /* idle states */
    AVRECORDER_IDLE = 0,
    /* prepared states */
    AVRECORDER_PREPARED = 1,
    /* started states */
    AVRECORDER_STARTED = 2,
    /* paused states */
    AVRECORDER_PAUSED = 3,
    /* stopped states */
    AVRECORDER_STOPPED = 4,
    /* released states */
    AVRECORDER_RELEASED = 5,
    /* error states */
    AVRECORDER_ERROR = 6,
} OH_AVRecorder_State;

/**
 * @brief Enumerates the reasons for AVRecorder state changes.
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_StateChangeReason {
    /* State changed by user operation */
    AVRECORDER_USER = 0,
    /* State changed by background action */
    AVRECORDER_BACKGROUND = 1,
} OH_AVRecorder_StateChangeReason;

/**
 * @brief Enumerates the modes available for creating a recording file.
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_FileGenerationMode {
    /* Application Creation */
    AVRECORDER_APP_CREATE = 0,
    /* System Creation. Valid only in camera scene */
    AVRECORDER_AUTO_CREATE_CAMERA_SCENE = 1,
} OH_AVRecorder_FileGenerationMode;

/**
 * @brief The struct describes the parameters used for audio and video recording.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Profile {
    /* Indicates the audio bitrate, in bit/s */
    int32_t audioBitrate;
    /* Indicates the number of audio channels */
    int32_t audioChannels;
    /* Indicates the audio encoding format */
    OH_AVRecorder_CodecMimeType audioCodec;
    /* Indicates the audio sampling rate, in Hz */
    int32_t audioSampleRate;
    /* Indicates the output file format */
    OH_AVRecorder_ContainerFormatType fileFormat;
    /* Indicates the video bitrate, in bit/s */
    int32_t videoBitrate;
    /* Indicates the video encoding format */
    OH_AVRecorder_CodecMimeType videoCodec;
    /* Indicates the video width, in px */
    int32_t videoFrameWidth;
    /* Indicates the video height, in px */
    int32_t videoFrameHeight;
    /* Indicates the video frame rate, in fps */
    int32_t videoFrameRate;
    /* Whether to record HDR video */
    bool isHdr;
    /* Whether to encode the video in temporal scale mode */
    bool enableTemporalScale;
} OH_AVRecorder_Profile;

/**
 * @brief The struct describes the geographical location information about a media asset.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Location {
    /* Latitude */
    float latitude;
    /* Longitude */
    float longitude;
} OH_AVRecorder_Location;

/**
 * @brief The struct describes the basic template of metadata.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_MetadataTemplate {
    /* key value of the metadata */
    char *key;
    /* contents of the metadata */
    char *value;
} OH_AVRecorder_MetadataTemplate;

/**
 * @brief The struct describes the metadata.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Metadata {
    /* The metadata to retrieve the content type or genre of the data source */
    char *genre;
    /* The metadata to retrieve the information about the video orientation */
    char *videoOrientation;
    /* The geographical location info of the video */
    OH_AVRecorder_Location location;
    /* Custom parameter key-value map read from moov.meta.list */
    OH_AVRecorder_MetadataTemplate customInfo;
} OH_AVRecorder_Metadata;

/**
 * @brief The struct describes the AVRecorder configuration.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Config {
    /* Indicates the recording audio source type */
    OH_AVRecorder_AudioSourceType audioSourceType;
    /* Indicates the recording video source type */
    OH_AVRecorder_VideoSourceType videoSourceType;
    /* Contains the audio and video encoding profile settings */
    OH_AVRecorder_Profile profile;
    /* Defines the file URL */
    char *url;
    /* Specifies the file generation mode for recording output */
    OH_AVRecorder_FileGenerationMode fileGenerationMode;
    /* Contains additional metadata for the recorded media */
    OH_AVRecorder_Metadata metadata;
    /* Set the longest duration allowed for current recording */
    int32_t maxDuration;
} OH_AVRecorder_Config;

/**
 * @brief The struct describes the range.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Range {
    /* lower limit of the range */
    int32_t min;
    /* upper limit of the range */
    int32_t max;
} OH_AVRecorder_Range;

/**
 * @brief The struct describes the encoder information.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_EncoderInfo {
    /* encoder format MIME */
    OH_AVRecorder_CodecMimeType mimeType;
    /* encoder type, audio or video */
    char *type;
    /* audio or video encoder bitRate range */
    OH_AVRecorder_Range bitRate;
    /* video encoder frame rate range */
    OH_AVRecorder_Range frameRate;
    /* video encoder width range */
    OH_AVRecorder_Range width;
    /* video encoder height range */
    OH_AVRecorder_Range height;
    /* audio encoder channel range */
    OH_AVRecorder_Range channels;
    /* audio encoder sample rate collection */
    int32_t *sampleRate;
    /* length of sampleRate list */
    int32_t sampleRateLen;
} OH_AVRecorder_EncoderInfo;

/**
 * @brief Called when the AVRecorder state changes.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param state AVRecorder state.
 * @param reason Reason for the AVRecorder state change.
 * @param userData Pointer to user-defined data.
 * @since 18
 */
typedef void (*OH_AVRecorder_OnStateChange)(OH_AVRecorder *recorder,
    OH_AVRecorder_State state, OH_AVRecorder_StateChangeReason reason, void *userData);

/**
 * @brief Called when an error occurs during recording.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param errorCode Error code. For details, see {@link OH_AVErrCode}.
 * @param errorMsg Pointer to the error message.
 * @param userData Pointer to user-defined data.
 * @since 18
 */
typedef void (*OH_AVRecorder_OnError)(OH_AVRecorder *recorder, int32_t errorCode, const char *errorMsg,
    void *userData);

/**
 * @brief Called when the recording is in {@link OH_AVRecorder_FileGenerationMode}.AVRECORDER_AUTO_CREATE_CAMERA_SCENE
 * mode.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param asset Pointer to the OH_MediaAsset instance.
 * @param userData Pointer to user-defined data.
 * @since 18
 */
typedef void (*OH_AVRecorder_OnUri)(OH_AVRecorder *recorder, OH_MediaAsset *asset, void *userData);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_BASE_H
