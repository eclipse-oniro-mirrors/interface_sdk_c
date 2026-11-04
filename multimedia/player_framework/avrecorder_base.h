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
 * @brief AVRecorder enables media recording and supports configuration of recording parameters and real-time status
 * callback. It is suitable for scenarios where audio and video need to be recorded and saved as files, such as video
 * call recording and voice notes.<br>
 * You can refer to the corresponding development guide and samples based on your development requirements.<br>
 * - [Using AVRecorder to Record Audio (C/C++)](../../../media/media/using-ndk-avrecorder-for-audio-recording.md)<br>
 * - [Using AVRecorder to Record Videos (C/C++)](../../../media/media/using-ndk-avrecorder-for-video-recording.md)<br>
 *
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 * @}
 */
/**
 * @file avrecorder_base.h
 *
 * @brief Defines the struct, enums, and callbacks used by AVRecorder.
 * 
 * @include <multimedia/player_framework/avrecorder_base.h>
 * @library libavrecorder.so
 * @kit MediaKit
 * @since 18
 */
 
#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_BASE_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_BASE_H

#include <stdbool.h>
#include <stdint.h>
#include "multimedia/media_library/media_asset_base_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines a struct for audio and video recording, which is used to represent an AVRecorder instance. It supports
 * audio and video data collection and recording, and provides capabilities such as recording process control and
 * callbacks for event listeners. It is applicable to scenarios where audio and video need to be recorded and saved as
 * files, such as video conference recording, screen recording apps, and security surveillance recording.
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
    /**
     * @brief Default audio source. This parameter is applicable to common recording scenarios where no specific audio
     * source type needs to be specified.
     * 
     * @since 18
     */
    AVRECORDER_DEFAULT = 0,
    /**
     * @brief Microphone audio source.
     * 
     * @since 18
     */
    AVRECORDER_MIC = 1,
    /**
     * @brief Audio source in speech recognition scenarios.
     * 
     * @since 18
     */
    AVRECORDER_VOICE_RECOGNITION = 2,
    /**
     * @brief Voice communication source.
     * 
     * @since 18
     */
    AVRECORDER_VOICE_COMMUNICATION = 7,
    /**
     * @brief Voice message source.
     * 
     * @since 18
     */
    AVRECORDER_VOICE_MESSAGE = 10,
    /**
     * @brief Audio source in camera recording scenarios.
     * 
     * @since 18
     */
    AVRECORDER_CAMCORDER = 13,
} OH_AVRecorder_AudioSourceType;

/**
 * @brief Enumerates the video source types of the AVRecorder.
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_VideoSourceType {
    /**
     * @brief Raw data surface. This parameter is applicable to scenarios where the original video frame data needs to
     * be encoded.
     * 
     * @since 18
     */
    AVRECORDER_SURFACE_YUV = 0,
    /**
     * @brief ES data surface. This parameter is applicable to scenarios where the existing encoded data (such as the
     * hard coding output) does not need to be encoded again.
     * 
     * @since 18
     */
    AVRECORDER_SURFACE_ES = 1,
} OH_AVRecorder_VideoSourceType;

/**
 * @brief Enumerates the MIME types of the encoder, which are used to specify the encoding format of audio and video
 * data during recording. The encoder type must match the container format. If they do not match, the recording will
 * fail. For details about the mapping, see the description of the corresponding encoder type.
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_CodecMimeType {
    /**
     * @brief MIME type of the H.264 video encoder. It must be used together with the MP4 container format.
     * 
     * @since 18
     */
    AVRECORDER_VIDEO_AVC = 2,
    /**
     * @brief MIME type of the AAC audio encoder. It must be used together with the AAC, MP4, or M4A container format.
     * 
     * @since 18
     */
    AVRECORDER_AUDIO_AAC = 3,
    /**
     * @brief MIME type of the MP3 audio encoder. It must be used together with the MP3 container format.
     * 
     * @since 18
     */
    AVRECORDER_AUDIO_MP3 = 4,
    /**
     * @brief MIME type of the G711-mulaw audio encoder. It must be used together with the WAV container format.
     * 
     * @since 18
     */
    AVRECORDER_AUDIO_G711MU = 5,
    /**
     * @brief MIME type of the MPEG4 video encoder. It must be used together with the MP4 container format.
     * 
     * @since 18
     */
    AVRECORDER_VIDEO_MPEG4 = 6,
    /**
     * @brief MIME type of the H.265 video encoder. It must be used together with the MP4 container format.
     * 
     * @since 18
     */
    AVRECORDER_VIDEO_HEVC = 8,
    /**
     * @brief MIME type of the AMR_NB audio encoder. It must be used together with the AMR container format.
     * 
     * @since 18
     */
    AVRECORDER_AUDIO_AMR_NB = 9,
    /**
     * @brief MIME type of the AMR_WB audio encoder. It must be used together with the AMR container format.
     * 
     * @since 18
     */
    AVRECORDER_AUDIO_AMR_WB = 10,
} OH_AVRecorder_CodecMimeType;

/**
 * @brief Enumerates the Container Format Types (CFTs), which are used to specify the encapsulation format of recording
 * files. The container format must be compatible with the MIME type of the encoder. If they are incompatible, the
 * recording will fail. For details about the encoder types supported by each container format, see the description of
 * the corresponding container format.
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_ContainerFormatType {
    /**
     * @brief Video container format mp4. AAC audio encoder and MPEG4, H.264, or H.265 video encoder are supported.
     * 
     * @since 18
     */
    AVRECORDER_CFT_MPEG_4 = 2,
    /**
     * @brief Audio container format m4a. AAC audio encoder is supported.
     * 
     * @since 18
     */
    AVRECORDER_CFT_MPEG_4A = 6,
    /**
     * @brief Audio container format amr. AMR_NB and AMR_WB audio encoders are supported.
     * 
     * @since 18
     */
    AVRECORDER_CFT_AMR = 8,
    /**
     * @brief Audio container format mp3. MP3 audio encoder is supported.
     * 
     * @since 18
     */
    AVRECORDER_CFT_MP3 = 9,
    /**
     * @brief Audio container format wav. G711-mulaw audio encoder is supported.
     * 
     * @since 18
     */
    AVRECORDER_CFT_WAV = 10,
    /**
     * @brief Audio container format aac (with ADTS header). AAC audio encoder is supported.
     *  
     * @since 20
     */
    AVRECORDER_CFT_AAC = 11,
} OH_AVRecorder_ContainerFormatType;

/**
 * @brief Enumerates the AVRecorder states, which indicate the different phases of the recorder in its lifecycle. The
 * operations that can be performed vary depending on the state.
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_State {
    /**
     * @brief Idle. This is the default initial state after an AVRecorder instance is created. In this state, you can
     * call [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} to set recording parameters, and the AVRecorder
     * transitions to the **AVRECORDER_PREPARED** state.
     * 
     * @since 18
     */
    AVRECORDER_IDLE = 0,
    /**
     * @brief Prepared. After the parameters are set, you can call [OH_AVRecorder_Start]{@link OH_AVRecorder_Start} to
     * start recording, and the AVRecorder transitions to the **AVRECORDER_STARTED** state.
     * 
     * @since 18
     */
    AVRECORDER_PREPARED = 1,
    /**
     * @brief Started. Recording is in progress. In this case, you can call
     * [OH_AVRecorder_Pause]{@link OH_AVRecorder_Pause} to pause recording, and the AVRecorder transitions to the
     * **AVRECORDER_PAUSED** state.<br>You can also call [OH_AVRecorder_Stop]{@link OH_AVRecorder_Stop} to stop
     * recording, and the AVRecorder transitions to the **AVRECORDER_STOPPED** state.
     * 
     * @since 18
     */
    AVRECORDER_STARTED = 2,
    /**
     * @brief Paused. In this state, you can call [OH_AVRecorder_Resume]{@link OH_AVRecorder_Resume} to resume
     * recording, and the AVRecorder transitions to the **AVRECORDER_STARTED** state.<br>You can also call
     * [OH_AVRecorder_Stop]{@link OH_AVRecorder_Stop} to stop recording, and the AVRecorder transitions to the
     * **AVRECORDER_STOPPED** state.
     * 
     * @since 18
     */
    AVRECORDER_PAUSED = 3,
    /**
     * @brief Stopped. In this state, you can call [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} to set recording
     * parameters, and the AVRecorder reenters the **AVRECORDER_PREPARED** state.
     * 
     * @since 18
     */
    AVRECORDER_STOPPED = 4,
    /**
     * @brief Released. The recording resources are released. No operation can be performed at this time. In any other
     * state, you can call [OH_AVRecorder_Release]{@link OH_AVRecorder_Release} to transition to the
     * **AVRECORDER_RELEASED** state.
     * 
     * @since 18
     */
    AVRECORDER_RELEASED = 5,
    /**
     * @brief Error state. AVRecorder transitions to this state when an irreversible error occurs in the AVRecorder
     * instance. <br>You should call [OH_AVRecorder_Reset]{@link OH_AVRecorder_Reset} to reset the AVRecorder instance
     * or call [OH_AVRecorder_Release]{@link OH_AVRecorder_Release} to release resources in the **AVRECORDER_ERROR**
     * state. The recording cannot continue.
     * 
     * @since 18
     */
    AVRECORDER_ERROR = 6,
} OH_AVRecorder_State;

/**
 * @brief Enumerates the reasons for AVRecorder state changes, which are used to determine whether the state change is
 * triggered by a user operation or a background event. This helps the app execute the corresponding processing logic
 * based on the reason.
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_StateChangeReason {
    /**
     * @brief The state change is caused by user operations. For example, when the user proactively calls the **Start**,
     * **Pause**, **Resume**, or **Stop** API.
     * 
     * @since 18
     */
    AVRECORDER_USER = 0,
    /**
     * @brief The state change is caused by background operations. For example, when the recording state is
     * automatically changed due to audio interruption or recording timeout.
     * 
     * @since 18
     */
    AVRECORDER_BACKGROUND = 1,
} OH_AVRecorder_StateChangeReason;

/**
 * @brief Defines the mode for generating a recording file. This mode specifies how media files are created. It is
 * applicable to recording scenarios where you need to choose whether the app or the system automatically manages the
 * files.
 * 
 * @since 18
 */
typedef enum OH_AVRecorder_FileGenerationMode {
    /**
     * @brief The app creates a media file in the sandbox. In this mode, the
     * [OH_AVRecorder_OnUri]{@link OH_AVRecorder_OnUri} callback will not be triggered.
     * 
     * @since 18
     */
    AVRECORDER_APP_CREATE = 0,
    /**
     * @brief The system creates a media file. In this mode, the [OH_AVRecorder_OnUri]{@link OH_AVRecorder_OnUri}
     * callback will be triggered. The app can obtain the media resource object generated during recording through the
     * callback.
     * 
     * @since 18
     */
    AVRECORDER_AUTO_CREATE_CAMERA_SCENE = 1,
} OH_AVRecorder_FileGenerationMode;

/**
 * @brief Describes the parameters used for audio and video recording. By configuring parameters such as the audio/video
 * encoding format, bitrate, sampling rate, frame rate, resolution, container format, HDR recording, and whether to
 * enable temporally scalable video encoding, you can flexibly control the recording quality and file size. This is
 * applicable to scenarios where you need to customize the recording quality, select the recording content type
 * (audio-only, video-only, or both), and enable HDR recording or temporally scalable video encoding.<br>You can choose
 * to record only audio, only video, or both by setting the parameters.<br>1. When **audioBitrate** or **audioChannels**
 * is set to **0**, audio recording is disabled.<br>2. When **videoFrameWidth** or **videoFrameHeight** is set to **0**,
 * video recording is disabled.<br>For details about the value range of each parameter, see
 * [AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9).
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Profile {
    /**
     * @brief Audio encoding bit rate, in bit/s. A larger value indicates better audio quality but a larger file size.
     * For details about the value range, see [AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9). The default
     * value is **0**, indicating that audio is not recorded. If the value is beyond the valid range, the recording
     * fails.
     * 
     * @since 18
     */
    int32_t audioBitrate;
    /**
     * @brief Number of audio channels. A larger value indicates stronger audio spatiality but a larger file size. For
     * details about the value range, see [AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9). The default
     * value is **0**, indicating that audio is not recorded. If the value is beyond the valid range, the recording
     * fails.
     * 
     * @since 18
     */
    int32_t audioChannels;
    /**
     * @brief MIME type of the audio encoder. Different types of audio encoders have different audio quality, file size,
     * and compatibility. For details about the encoder types, see
     * [OH_AVRecorder_CodecMimeType]{@link OH_AVRecorder_CodecMimeType}. This parameter is valid only when audio is
     * being recorded.
     * 
     * @since 18
     */
    OH_AVRecorder_CodecMimeType audioCodec;
    /**
     * @brief Audio sampling rate. The unit is Hz. For details about the value range, see
     * [AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9). A higher sampling rate indicates better audio
     * quality but a larger file size. If the value is beyond the valid range, the recording fails. The default value is
     * **0**. This parameter is valid only when audio is being recorded.
     * 
     * @since 18
     */
    int32_t audioSampleRate;
    /**
     * @brief Container format. The container format determines the storage format of the recorded file and the
     * supported audio/video encoding types. For details about the formats, see
     * [OH_AVRecorder_ContainerFormatType]{@link OH_AVRecorder_ContainerFormatType}.
     * 
     * @since 18
     */
    OH_AVRecorder_ContainerFormatType fileFormat;
    /**
     * @brief Video encoding bit rate, in bit/s. For details about the value range, see
     * [AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9). A larger value indicates better video quality but
     * a larger file size. A low bit rate is suitable for scenarios where network transmission or storage is limited,
     * while a high bit rate is suitable for local high-quality storage. If the value is out of the valid range, the
     * recording fails. The default value is **0**. This parameter is valid only during video recording.
     * 
     * @since 18
     */
    int32_t videoBitrate;
    /**
     * @brief MIME type of the video encoder. Different types of video encoders have different compression efficiency,
     * image quality, and compatibility. For details about the encoder types, see
     * [OH_AVRecorder_CodecMimeType]{@link OH_AVRecorder_CodecMimeType}. When **isHdr** is set to **true**, the value of
     * **videoCodec** must be **AVRECORDER_VIDEO_HEVC**. This parameter is valid only during video recording.
     * 
     * @since 18
     */
    OH_AVRecorder_CodecMimeType videoCodec;
    /**
     * @brief Video frame width, in pixels. For details about the value range, see
     * [AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9). A larger value indicates higher video definition
     * but a larger file size. The default value is **0**. If the value is **0**, video recording is not performed. If
     * the value is out of the valid range, the recording fails.
     * 
     * @since 18
     */
    int32_t videoFrameWidth;
    /**
     * @brief Video frame height, in pixels. For details about the value range, see
     * [AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9). A larger value indicates higher video definition
     * but a larger file size. The default value is **0**. If the value is **0**, video recording is not performed. If
     * the value is out of the valid range, the recording fails.
     * 
     * @since 18
     */
    int32_t videoFrameHeight;
    /**
     * @brief Video frame rate. A higher frame rate indicates smoother video playback but a larger file size. The unit
     * is frames per second (FPS). For details about the value range, see
     * [AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9). If the value is beyond the valid range, the
     * recording fails. The default value is **0**. This parameter is valid only during video recording.
     * 
     * @since 18
     */
    int32_t videoFrameRate;
    /**
     * @brief Whether HDR videos are recorded.<br> The value **true** indicates that HDR encoding is enabled. In this
     * case, the value of **videoCodec** must be **AVRECORDER_VIDEO_HEVC**. Otherwise, the recording preparation fails.
     * The value **false** indicates that HDR encoding is disabled, and there is no requirement on the encoding format.
     * <br> The default value is **false**. This parameter is valid only during video recording.
     * 
     * @since 18
     */
    bool isHdr;
    /**
     * @brief Whether to enable temporally scalable video encoding.<br> **true** indicates that some frames in the
     * encoded output stream can be skipped to optimize encoding efficiency. This is applicable to scenarios where the
     * encoding frame rate needs to be dynamically adjusted based on the network bandwidth or device performance (such
     * as live video streaming and video conferencing). **false** indicates that all frames in the encoded output stream
     * must be encoded without skipping. For details, see
     * [Temporally Scalable Video Coding](../../media/avcodec/video-encoding-temporal-scalability.md).<br> The default
     * value is **false**. This parameter is valid only during video recording.
     * 
     * @since 18
     */
    bool enableTemporalScale;
} OH_AVRecorder_Profile;

/**
 * @brief Describes the geographical location information about a media asset and supports the annotation of latitude
 * and longitude during audio and video recording. This struct uses the
 * [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} API of AVRecorder to write the latitude and longitude
 * information into the metadata of the recording file. You need to set the latitude and longitude parameters of this
 * structure before recording. During recording, the geographical location information is automatically embedded into
 * the generated media file. This struct is applicable to scenarios where geographical locations need to be embedded in
 * the recording result, such as marking the shooting location during video shooting, marking the track location in
 * activity record apps, and recording the itinerary coordinates in travel diary apps. This facilitates subsequent
 * retrieval and classification management of media resources by location.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Location {
    /**
     * @brief Latitude. The value range is [-90,90], in degrees (°). This parameter must be used together with longitude
     * to provide complete geographical location information. If the value is out of the range, an error occurs.
     * 
     * @since 18
     */
    float latitude;
    /**
     * @brief Longitude. The value range is [-180,180], in degrees (°). This parameter must be used together with
     * latitude to provide complete geographical location information. If the value is out of the range, an error
     * occurs.
     * 
     * @since 18
     */
    float longitude;
} OH_AVRecorder_Location;

/**
 * @brief Defines the basic template of metadata during audio and video recording. Metadata is organized in key-value
 * pair format. This struct is applicable to scenarios where custom metadata (such as title, author, and description)
 * needs to be added to the recording output, facilitating the classification, retrieval, and management of recorded
 * files. You can use the [OH_AVRecorder_Prepare]{@link OH_AVRecorder_Prepare} API of AVRecorder to set the metadata in
 * this struct to the recording output file.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_MetadataTemplate {
    /**
     * @brief Metadata key.
     * 
     * @since 18
     */
    char *key;
    /**
     * @brief Metadata value.
     * 
     * @since 18
     */
    char *value;
} OH_AVRecorder_MetadataTemplate;

/**
 * @brief Defines the metadata structure for recording, which is used to describe the genre, video rotation angle,
 * geographical location, and custom parameters of media resources. This struct is applicable to scenarios where media
 * metadata needs to be carried or read during recording.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Metadata {
    /**
     * @brief Genre of a media resource. If this parameter is not set, the genre information is not carried.
     * 
     * @since 18
     */
    char *genre;
    /**
     * @brief Video orientation, in degrees (°). Only the following angle values are supported: **0°**: no rotation, the
     * video remains in the original orientation; **90°**: rotates 90° clockwise; **180°**: rotates 180°; **270°**:
     * rotates 270° clockwise. If this parameter is not specified, the default value **0°** is used. If an unsupported
     * angle is passed, the setting fails.
     * 
     * @since 18
     */
    char *videoOrientation;
    /**
     * @brief Geographical location information of a media asset, including the latitude and longitude. The value range
     * of latitude is [–90, 90], and that of longitude is [–180, 180]. The unit is degree (°). If the input value is out
     * of the value range, the setting fails. If this parameter is not specified, geographical location information is
     * not carried.
     * 
     * @since 18
     */
    OH_AVRecorder_Location location;
    /**
     * @brief Custom parameter key-value mapping written to **moov.meta.list**. Both the key and value are of the string
     * type. This parameter is used to carry the metadata tag customized by the app during recording, for example,
     * adding a service ID or extended attribute. If this parameter is not specified, custom metadata information is not
     * carried.
     * 
     * @since 18
     */
    OH_AVRecorder_MetadataTemplate customInfo;
} OH_AVRecorder_Metadata;

/**
 * @brief Describes the AVRecorder configuration, which is used to set the audio source type, video source type,
 * encoding configuration, output file URL, file generation mode, metadata, and maximum recording duration during audio
 * and video recording. This struct is applicable to scenarios where custom recording configurations are required.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Config {
    /**
     * @brief Audio source type, which specifies the audio input source.
     * 
     * @since 18
     */
    OH_AVRecorder_AudioSourceType audioSourceType;
    /**
     * @brief Video source type, which specifies the video input source.
     * 
     * @since 18
     */
    OH_AVRecorder_VideoSourceType videoSourceType;
    /**
     * @brief Profile, including detailed parameters for audio and video recording, such as the encoding format,
     * bitrate, and resolution.
     * 
     * @since 18
     */
    OH_AVRecorder_Profile profile;
    /**
     * @brief URL of the recording output file, in the format of **fd://xx**, where **xx** is the value of the file
     * descriptor (FD), which must be a non-negative integer. This parameter is mandatory when the
     * **fileGenerationMode** is created by the app. It is not required when the **fileGenerationMode** is created by
     * the system. If the input URL is not in this format, the recording preparation fails. Ensure that the FD remains
     * valid during recording to prevent recording exceptions caused by an invalid FD.
     * 
     * @since 18
     */
    char *url;
    /**
     * @brief Mode for generating the recording output file. In recording scenarios where the output file URL needs to
     * be customized, the mode of creating files by the app is applicable. In recording scenarios where the output file
     * URL does not need to be specified, the mode of creating files by the system is applicable. In this mode, the app
     * obtains the media resource file generated during recording by triggering the **OH_AVRecorder_OnUri** callback
     * notification. The default value is the mode of creating files by the app.
     * 
     * @since 18
     */
    OH_AVRecorder_FileGenerationMode fileGenerationMode;
    /**
     * @brief Metadata of the recorded media. This parameter is used to add descriptive attributes to the recorded file,
     * such as genre, video rotation orientation, geographical location, and custom parameters. This parameter is left
     * empty by default.
     * 
     * @since 18
     */
    OH_AVRecorder_Metadata metadata;
    /**
     * @brief Maximum recording duration, in seconds. If the value is less than or equal to 0, there is no duration
     * limit. The default value is **0**. When the maximum recording duration is reached, the recording automatically
     * stops.
     * 
     * @since 18
     */
    int32_t maxDuration;
} OH_AVRecorder_Config;

/**
 * @brief Defines the value range of AVRecorder parameters (such as the bit rate and frame rate) to limit the
 * configurable range of recording parameters. You can use the
 * [OH_AVRecorder_GetAvailableEncoder]{@link OH_AVRecorder_GetAvailableEncoder} API to obtain the value range of encoder
 * parameters and set the parameter values within the range from **min** to **max** to ensure that the configuration is
 * valid.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Range {
    /**
     * @brief Minimum value of an AVRecorder parameter. The unit is the same as that of the described parameter.
     * 
     * @since 18
     */
    int32_t min;
    /**
     * @brief Maximum value of an AVRecorder parameter. The unit is the same as that of the described parameter.
     * 
     * @since 18
     */
    int32_t max;
} OH_AVRecorder_Range;

/**
 * @brief Provides AVRecorder encoder capability information, including the MIME type, bit rate range, and frame rate
 * range of the encoder. This struct is applicable to scenarios where you need to query and select a proper audio or
 * video encoder configuration before recording, helping you select the optimal encoding configuration based on the
 * encoder capability parameters. You can obtain this struct object by calling
 * [OH_AVRecorder_GetAvailableEncoder]{@link OH_AVRecorder_GetAvailableEncoder}.
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_EncoderInfo {
    /**
     * @brief MIME type of the encoder. The value corresponds to **type**. If **type** is **audio**, the value is the
     * audio MIME type. If **type** is **video**, the value is the video MIME type.
     * 
     * @since 18
     */
    OH_AVRecorder_CodecMimeType mimeType;
    /**
     * @brief Encoder type. The value **audio** means an audio encoder, and **video** means a video encoder.
     * 
     * @since 18
     */
    char *type;
    /**
     * @brief Bit rates supported by the encoder, in bit/s. This parameter is applicable to both audio and video
     * encoders.
     * 
     * @since 18
     */
    OH_AVRecorder_Range bitRate;
    /**
     * @brief Video frame rates supported by the encoder, in FPS. This parameter is applicable only to video encoders.
     * 
     * @since 18
     */
    OH_AVRecorder_Range frameRate;
    /**
     * @brief Video frame widths supported by the encoder, in pixels. This parameter is applicable only to video
     * encoders.
     * 
     * @since 18
     */
    OH_AVRecorder_Range width;
    /**
     * @brief Video frame heights supported by the encoder, in pixels. This parameter is applicable only to video
     * encoders.
     * 
     * @since 18
     */
    OH_AVRecorder_Range height;
    /**
     * @brief Number of audio channels supported by the encoder. The value is determined by the encoder capability of
     * the device. The common values are **1** (mono) or **2** (stereo). This parameter is applicable only to audio
     * encoders.
     * 
     * @since 18
     */
    OH_AVRecorder_Range channels;
    /**
     * @brief List of audio sampling rates supported by the encoder. The value is determined by the encoder capability
     * of the device. Common values include **8000**, **16000**, **44100**, and **48000**, in Hz. This parameter is used
     * together with the **sampleRateLen** field, which indicates the length of the list. This parameter is applicable
     * only to audio encoders.
     * 
     * @since 18
     */
    int32_t *sampleRate;
    /**
     * @brief Length of the audio sampling rate list. The value is an integer greater than 0. This parameter is used
     * together with the **sampleRate** field to indicate the number of elements in the **sampleRate** array. This
     * parameter is applicable only to audio encoders.
     * 
     * @since 18
     */
    int32_t sampleRateLen;
} OH_AVRecorder_EncoderInfo;

/**
 * @brief Called when the AVRecorder state changes.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param state AVRecorder state.
 * @param reason Reason for the AVRecorder state change.
 * @param userData Pointer to the custom data passed during callback registration. When the callback is triggered, the
 *     system returns the custom data to the caller.
 * @since 18
 */
typedef void (*OH_AVRecorder_OnStateChange)(OH_AVRecorder *recorder,
    OH_AVRecorder_State state, OH_AVRecorder_StateChangeReason reason, void *userData);

/**
 * @brief Called when an error occurs during recording.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param errorCode Error code. For details, see {@link OH_AVErrCode}.
 * @param errorMsg A character string that describes the error message.
 * @param userData Pointer to the custom data passed during callback registration. When the callback is triggered, the
 *     system returns the custom data to the caller.
 * @since 18
 */
typedef void (*OH_AVRecorder_OnError)(OH_AVRecorder *recorder, int32_t errorCode, const char *errorMsg,
    void *userData);

/**
 * @brief Called when the recording file is generated in
 * [OH_AVRecorder_FileGenerationMode]{@link OH_AVRecorder_FileGenerationMode}.AVRECORDER_AUTO_CREATE_CAMERA_SCENE mode
 * to notify the app to obtain the media resources generated during recording.
 * 
 * @param recorder Pointer to the OH_AVRecorder instance.
 * @param asset Pointer to the **OH_MediaAsset** instance, which is used to return the media resource object
 *     automatically created by the system. Your app can use this object to access the media file generated after
 *     recording.
 * @param userData Pointer to the custom data passed during callback registration. When the callback is triggered, the
 *     system returns the custom data to the caller.
 * @since 18
 */
typedef void (*OH_AVRecorder_OnUri)(OH_AVRecorder *recorder, OH_MediaAsset *asset, void *userData);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_BASE_H
