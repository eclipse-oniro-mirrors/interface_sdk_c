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
 * @brief AVRecorder提供媒体录制能力，支持配置录制参数及实时状态回调，适用于视频通话录制、语音备忘录等需要将音视频内容录制保存为文件的场景。<br>
 *
 * 开发者可根据开发需求，参考对应的开发指南及样例：<br>
 *
 * - [使用AVRecorder录制音频（C/C++）](../../../media/media/using-ndk-avrecorder-for-audio-recording.md)<br>
 * - [使用AVRecorder录制视频（C/C++）](../../../media/media/using-ndk-avrecorder-for-video-recording.md)<br>
 *
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 * @}
 */
/**
 * @file avrecorder_base.h
 *
 * @brief 定义AVRecorder的结构体、枚举和回调函数类型。
 * 
 * @kit MediaKit
 * @include <multimedia/player_framework/avrecorder_base.h>
 * @library libavrecorder.so
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
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
 * @brief 音视频录制的结构体类型，用于表示AVRecorder实例，支持音视频数据的采集与录制，提供录制流程控制及回调事件监听等能力。适用于需要将音视频内容录制保存为文件的场景，如视频会议录制、屏幕录制应用、安防监控录像等。
 * 
 * @since 18
 */
typedef struct OH_AVRecorder OH_AVRecorder;

/**
 * @brief AVRecorder的音频源类型。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
typedef enum OH_AVRecorder_AudioSourceType {
    /* 默认音频源类型。适用于无需指定特定音频源类型的通用录制场景。 */
    AVRECORDER_DEFAULT = 0,
    /* 麦克风音频源类型。 */
    AVRECORDER_MIC = 1,
    /* 语音识别场景的音频源。 */
    AVRECORDER_VOICE_RECOGNITION = 2,
    /* 语音通话场景的音频源。 */
    AVRECORDER_VOICE_COMMUNICATION = 7,
    /* 语音消息的音频源。 */
    AVRECORDER_VOICE_MESSAGE = 10,
    /* 相机录像的音频源。 */
    AVRECORDER_CAMCORDER = 13,
} OH_AVRecorder_AudioSourceType;

/**
 * @brief AVRecorder的视频源类型。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
typedef enum OH_AVRecorder_VideoSourceType {
    /* 原始数据Surface。适用于需要对原始视频帧数据进行编码处理的场景。 */
    AVRECORDER_SURFACE_YUV = 0,
    /* ES数据Surface。适用于已有编码数据（如硬编码输出）无需再次编码的场景。 */
    AVRECORDER_SURFACE_ES = 1,
} OH_AVRecorder_VideoSourceType;

/**
 * @brief 编码器MIME类型，用于指定录制时音视频数据的编码格式。编码器类型需与容器格式类型匹配使用，不匹配时将导致录制失败，具体匹配关系请参见对应编码器类型的枚举项说明。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
typedef enum OH_AVRecorder_CodecMimeType {
    /* H.264视频编码器MIME类型。需与mp4容器格式匹配使用。 */
    AVRECORDER_VIDEO_AVC = 2,
    /* AAC音频编码器MIME类型。需与aac、mp4或m4a容器格式匹配使用。 */
    AVRECORDER_AUDIO_AAC = 3,
    /* MP3音频编码器MIME类型。需与mp3容器格式匹配使用。 */
    AVRECORDER_AUDIO_MP3 = 4,
    /* G711-mulaw音频编码器MIME类型。需与wav容器格式匹配使用。 */
    AVRECORDER_AUDIO_G711MU = 5,
    /* MPEG4视频编码器MIME类型。需与mp4容器格式匹配使用。 */
    AVRECORDER_VIDEO_MPEG4 = 6,
    /* H.265视频编码器MIME类型。需与mp4容器格式匹配使用。 */
    AVRECORDER_VIDEO_HEVC = 8,
    /* AMR_NB音频编码器MIME类型。需与amr容器格式匹配使用。 */
    AVRECORDER_AUDIO_AMR_NB = 9,
    /* AMR_WB音频编码器MIME类型。需与amr容器格式匹配使用。 */
    AVRECORDER_AUDIO_AMR_WB = 10,
} OH_AVRecorder_CodecMimeType;

/**
 * @brief 容器格式类型（CFT），用于指定录制文件的封装格式。容器格式需与编码器MIME类型兼容，不兼容时将导致录制失败，各容器格式支持的编码器类型请参见对应容器格式类型的枚举项说明。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
typedef enum OH_AVRecorder_ContainerFormatType {
    /* 视频容器格式类型mp4。支持AAC音频编码器及MPEG4、H.264或H.265视频编码器。 */
    AVRECORDER_CFT_MPEG_4 = 2,
    /* 音频容器格式类型m4a。支持AAC音频编码器。 */
    AVRECORDER_CFT_MPEG_4A = 6,
    /* 音频容器格式类型amr。支持AMR_NB、AMR_WB音频编码器。 */
    AVRECORDER_CFT_AMR = 8,
    /* 音频容器格式类型mp3。支持MP3音频编码器。 */
    AVRECORDER_CFT_MP3 = 9,
    /* 音频容器格式类型wav。支持G711-mulaw音频编码器。 */
    AVRECORDER_CFT_WAV = 10,
    
    /**
     * @brief 音频容器格式类型aac（带ADTS头）。支持AAC音频编码器。
     *  
     * @since 20
     */
    AVRECORDER_CFT_AAC = 11,
} OH_AVRecorder_ContainerFormatType;

/**
 * @brief AVRecorder状态，用于表示录制器在生命周期中的不同阶段，不同状态下可执行的操作不同。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
typedef enum OH_AVRecorder_State {
    /* 空闲状态，为AVRecorder实例创建后的默认初始状态。此时可以调用{@link OH_AVRecorder_Prepare}接口设置录制参数，进入AVRECORDER_PREPARED状态。 */
    AVRECORDER_IDLE = 0,
    /* 准备状态。参数设置完成，此时可以调用{@link OH_AVRecorder_Start}接口开始录制，进入AVRECORDER_STARTED状态。 */
    AVRECORDER_PREPARED = 1,
    /**
     * 启动状态。正在录制，此时可以调用{@link OH_AVRecorder_Pause}接口暂停录制，进入AVRECORDER_PAUSED状态。
     * 也可以调用{@link OH_AVRecorder_Stop}接口结束录制，进入AVRECORDER_STOPPED状态。
     */
    AVRECORDER_STARTED = 2,
    /**
     * 暂停状态。此时可以调用{@link OH_AVRecorder_Resume}接口继续录制，进入AVRECORDER_STARTED状态。
     * 也可以调用{@link OH_AVRecorder_Stop}接口结束录制，进入AVRECORDER_STOPPED状态。
     */
    AVRECORDER_PAUSED = 3,
    /* 停止状态。此时可以调用{@link OH_AVRecorder_Prepare}接口设置录制参数，重新进入AVRECORDER_PREPARED状态。 */
    AVRECORDER_STOPPED = 4,
    /* 释放状态。录制资源释放，此时不能再进行任何操作。在任何其他状态下，均可以通过调用{@link OH_AVRecorder_Release}接口进入AVRECORDER_RELEASED状态。 */
    AVRECORDER_RELEASED = 5,
    /**
     * 错误状态。当AVRecorder实例发生不可逆错误，会转换至该状态。在AVRECORDER_ERROR状态时，不能再进行录制相关操作，
     * 用户需要调用{@link OH_AVRecorder_Reset}接口重置AVRecorder实例，或者调用{@link OH_AVRecorder_Release}接口释放资源。 */
     */
    AVRECORDER_ERROR = 6,
} OH_AVRecorder_State;

/**
 * @brief AVRecorder状态变化的原因，用于区分状态变化是由用户操作还是后台事件触发，便于应用根据不同原因执行相应的处理逻辑。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
typedef enum OH_AVRecorder_StateChangeReason {
    /* 用户操作导致的状态变化。例如用户主动调用Start、Pause、Resume、Stop等接口时触发。 */
    AVRECORDER_USER = 0,
    /* 后台操作导致的状态变化。例如因音频打断、录制超时等原因自动改变录制状态时触发。 */
    AVRECORDER_BACKGROUND = 1,
} OH_AVRecorder_StateChangeReason;

/**
 * @brief 录制文件的生成模式，用于指定媒体文件的创建方式，适用于需要选择由应用自行管理文件还是由系统自动管理文件的录制场景。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
typedef enum OH_AVRecorder_FileGenerationMode {
    /* 由应用自行在沙箱中创建媒体文件，此模式下不会触发{@link OH_AVRecorder_OnUri}回调。 */
    AVRECORDER_APP_CREATE = 0,
    /* 由系统创建媒体文件，此模式下会触发{@link OH_AVRecorder_OnUri}回调，应用可通过回调获取录制生成的媒体资源对象。 */
    AVRECORDER_AUTO_CREATE_CAMERA_SCENE = 1,
} OH_AVRecorder_FileGenerationMode;

/**
 * @brief 定义音视频录制的详细参数。通过配置音频/视频编码格式、比特率、采样率、帧率、分辨率、容器格式、HDR录制、是否启用时域可分层视频编码功能等参数，可以灵活控制录制质量和录制文件大小，
 * 适用于需要自定义录制质量、选择录制内容类型（仅音频/仅视频/音视频同时录制）、启用HDR录制或时域可分层视频编码功能的场景。<br>
 *
 * 通过参数设置可以选择仅录制音频或视频，或者同时录制音视频：<br>
 * 1. 当 audioBitrate 或 audioChannels 为 0 时，不录制音频。<br>
 * 2. 当 videoFrameWidth 或 videoFrameHeight 为 0 时，不录制视频。<br>
 *
 * 各参数的范围请参见[AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9)。
 *
 * @since 18
 */
typedef struct OH_AVRecorder_Profile {
    /**
     * 音频编码比特率。单位为比特每秒（bit/s）。数值越大音频质量越好，但文件也越大。
     * 取值范围请参见[AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9)，默认值为0，取值为0时不录制音频，超出有效范围时录制失败。
     */
    int32_t audioBitrate;
    /**
     * 音频声道数。声道数越多音频空间感越强，但文件也越大。
     * 取值范围请参见[AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9)，默认值为0，取值为0时不录制音频，超出有效范围时录制失败。
     */
    int32_t audioChannels;
    /* 音频编码器MIME类型。选择不同的音频编码器将影响录制的音频质量、文件大小和兼容性，各编码器类型详见{@link OH_AVRecorder_CodecMimeType}。仅在录制音频时有效。 */
    OH_AVRecorder_CodecMimeType audioCodec;
    /**
     * 音频采样率。单位为赫兹（Hz）。
     * 取值范围请参见[AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9)，采样率越高音频质量越好，但文件也越大，超出有效范围时录制失败。默认值为0。
     * 仅在录制音频时有效。
     */
    int32_t audioSampleRate;
    /* 容器格式类型。选择不同的容器格式将决定录制文件的存储格式和支持的音视频编码类型，各格式类型详见{@link OH_AVRecorder_ContainerFormatType}。 */
    OH_AVRecorder_ContainerFormatType fileFormat;
    /**
     * 视频编码比特率。单位为比特每秒（bit/s）。取值范围请参见[AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9)，数值越大视频质量越好，但文件也越大。
     * 低比特率适合网络传输或存储受限场景，高比特率适合本地高质量存储场景。超出有效范围时录制失败。默认值为0。仅在录制视频时有效。
     */
    int32_t videoBitrate;
    /**
     * 视频编码器MIME类型。选择不同的视频编码器将影响录制的视频压缩效率、画质和兼容性，各编码器类型详见{@link OH_AVRecorder_CodecMimeType}。
     * 当isHdr为true时，videoCodec必须为AVRECORDER_VIDEO_HEVC。仅在录制视频时有效。
     */
    OH_AVRecorder_CodecMimeType videoCodec;
    /**
     * 视频帧宽度。单位为像素（px）。取值范围请参见[AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9)，数值越大视频清晰度越高，但文件也越大。
     * 默认值为0，取值为0时不录制视频。超出有效范围时录制失败。
     */
    int32_t videoFrameWidth;
    /**
     * 视频帧高度。单位为像素（px）。取值范围请参见[AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9)，数值越大视频清晰度越高，但文件也越大。
     * 默认值为0，取值为0时不录制视频。超出有效范围时录制失败。
     */
    int32_t videoFrameHeight;
    /**
     * 视频帧率。帧率越高视频越流畅，但文件也越大。单位为帧每秒（fps）。
     * 取值范围请参见[AVRecorderProfile](arkts-apis-media-i.md#avrecorderprofile9)，超出有效范围时录制失败。默认值为0。仅在录制视频时有效。
     */
    int32_t videoFrameRate;
    /**
     * 是否录制HDR视频。true表示启用HDR编码，此时videoCodec必须为AVRECORDER_VIDEO_HEVC，否则录制会准备失败；false表示不启用HDR编码，对编码格式无要求。
     * 默认值为false。仅在录制视频时有效。
     */
    bool isHdr;
    /**
     * 是否启用时域可分层视频编码功能。
     * true表示编码输出的码流中时域增强层帧可被跳过不编码，适用于需要根据网络带宽或设备性能动态调整编码帧率的场景（如视频直播、视频会议等），false表示编码输出的码流中所有帧均需编码。
     * 详情请参考[时域可分层视频编码](docroot://media/avcodec/video-encoding-temporal-scalability.md)。默认值为false。仅在录制视频时有效。
     */
    bool enableTemporalScale;
} OH_AVRecorder_Profile;

/**
 * @brief 提供媒体资源的地理位置信息，支持在音视频录制过程中标注纬度和经度。
 * 该结构体通过AVRecorder的{@link OH_AVRecorder_Prepare}接口将经纬度信息写入录制文件的元数据中，开发者需在录制前设置该结构体的latitude和longitude参数，
 * 录制过程中地理位置信息将自动嵌入到生成的媒体文件中。
 * 适用于需要在录制结果中嵌入地理位置的场景，如在视频拍摄时标记拍摄地点、运动记录应用中标记轨迹位置、旅行日记应用中记录行程坐标等，便于后续按位置检索和分类管理媒体资源。
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Location {
    /* 纬度，取值范围[-90, 90]，单位：度（°）。需与longitude配合使用以提供完整的地理位置信息，超出范围时将导致错误。 */
    float latitude;
    /* 经度，取值范围[-180, 180]，单位：度（°）。需与latitude配合使用以提供完整的地理位置信息，超出范围时将导致错误。 */
    float longitude;
} OH_AVRecorder_Location;

/**
 * @brief 定义音视频录制过程中元数据的基本模板，通过键值对（key-value）形式组织元数据，适用于需要在录制输出中附加自定义元数据（如标题、作者、描述等）的场景，便于对录制文件进行分类、检索和管理。
 * 开发者可通过AVRecorder的{@link OH_AVRecorder_Prepare}接口将该结构体中的元数据设置到录制输出文件中。
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_MetadataTemplate {
    /* 元数据的键。 */
    char *key;
    /* 元数据的值。 */
    char *value;
} OH_AVRecorder_MetadataTemplate;

/**
 * @brief 定义录制的元数据结构，用于描述媒体资源的体裁分类、视频旋转角度、地理位置及自定义参数等元数据信息，适用于录制过程中需要携带或读取媒体元数据的场景。
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Metadata {
    /* 媒体资源的体裁分类。不设置时不携带体裁分类信息。 */
    char *genre;
    /**
     * 视频的旋转角度，单位为度（°），仅支持特定角度值：0°（无旋转，视频保持原始方向）、90°（顺时针旋转90度）、180°（旋转180度）、270°（顺时针旋转270度）。
     * 不设置时默认为0°。传入不支持的角度值时，设置失败。
     */
    char *videoOrientation;
    /**
     * 媒体资源的地理位置信息，包含纬度（latitude）和经度（longitude）。其中latitude取值范围[-90, 90]，longitude取值范围[-180, 180]，单位为度（°）。
     * 传入超出取值范围的值时，设置失败。不设置时不携带地理位置信息。
     */
    OH_AVRecorder_Location location;
    /* 写入 moov.meta.list 的自定义参数键值映射，键和值均为字符串类型，用于在录制时携带应用自定义的元数据标签，如添加业务标识、扩展属性等。不设置时不携带自定义元数据信息。 */
    OH_AVRecorder_MetadataTemplate customInfo;
} OH_AVRecorder_Metadata;

/**
 * @brief 提供媒体AVRecorder的配置定义，用于设置音视频录制时的音频源类型、视频源类型、编码配置、输出文件URL、文件生成模式、元数据及最大录制时长参数，适用于需要自定义录制配置的场景。
 * 
 * @since 18
 */
typedef struct OH_AVRecorder_Config {
    /* 录制音频源类型，用于指定录制时采集音频的输入源。 */
    OH_AVRecorder_AudioSourceType audioSourceType;
    /* 录制视频源类型，用于指定录制时采集视频的输入源。 */
    OH_AVRecorder_VideoSourceType videoSourceType;
    /* 包含音视频录制的详细参数，如编码格式、比特率、分辨率等。 */
    OH_AVRecorder_Profile profile;
    /**
     * 指定录制输出文件的URL，格式为fd://xx，其中xx为文件描述符（fd）的数值，需为非负整数。
     * 当fileGenerationMode为应用创建模式时，必须设置此参数；当fileGenerationMode为系统创建模式时，无需设置此参数。
     * 传入不符合该格式的URL时，录制准备失败。使用时应确保文件描述符（fd）在录制期间保持有效，避免因fd失效导致录制异常。
     */
    char *url;
    /**
     * 指定录制输出文件的生成模式。应用创建模式适用于需要自定义输出文件URL的录制场景；
     * 系统创建模式适用于无需指定输出文件URL的录制场景，将通过触发OH_AVRecorder_OnUri回调通知应用获取录制生成的媒体资源文件。默认值为应用创建模式。
     */
    OH_AVRecorder_FileGenerationMode fileGenerationMode;
    /* 包含录制媒体的附加元数据。用于为录制文件添加描述性属性，如体裁分类、视频旋转方向、地理位置及自定义参数等。默认为空。 */
    OH_AVRecorder_Metadata metadata;
    /* 指定最大录制时长，单位为秒（s）。值小于等于0时表示无时长限制，默认值为0。达到最大录制时长后自动停止录制。 */
    int32_t maxDuration;
} OH_AVRecorder_Config;

/**
 * @brief 表示AVRecorder相关参数（如比特率、帧率等）的取值范围，用于限定录制参数的可配置范围。
 * 开发者可通过{@link OH_AVRecorder_GetAvailableEncoder}接口获取编码器相关参数取值范围，并在min和max所界定的范围内设置参数值，以确保配置有效。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
typedef struct OH_AVRecorder_Range {
    /* AVRecorder相关参数取值范围的最小值。单位与所描述的参数一致。 */
    int32_t min;
    /* AVRecorder相关参数取值范围的最大值。单位与所描述的参数一致。 */
    int32_t max;
} OH_AVRecorder_Range;

/**
 * @brief 提供AVRecorder编码器能力信息，包括编码器的MIME类型、比特率范围、帧率范围等参数，适用于在录制前查询和选择合适的音频或视频编码器配置的场景，帮助开发者根据编码器能力参数选择最优编码配置。
 * 开发者可通过{@link OH_AVRecorder_GetAvailableEncoder}接口获取该结构体对象。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
typedef struct OH_AVRecorder_EncoderInfo {
    /* 编码器MIME类型。值与type对应，type为audio时值为音频MIME类型，type为video时值为视频MIME类型。 */
    OH_AVRecorder_CodecMimeType mimeType;
    /* 编码器类型，audio表示音频编码器，video表示视频编码器。 */
    char *type;
    /* 编码器支持的比特率范围，单位为比特每秒（bit/s）。音频和视频编码器均适用。 */
    OH_AVRecorder_Range bitRate;
    /* 编码器支持的视频帧率范围，单位为帧每秒（fps）。仅适用于视频编码器。 */
    OH_AVRecorder_Range frameRate;
    /* 编码器支持的视频帧宽度范围，单位为像素（px）。仅适用于视频编码器。 */
    OH_AVRecorder_Range width;
    /* 编码器支持的视频帧高度范围，单位为像素（px）。仅适用于视频编码器。 */
    OH_AVRecorder_Range height;
    /* 编码器支持的音频声道数的范围，取值由设备编码器能力决定，常见取值为1（单声道）或2（立体声）。仅适用于音频编码器。 */
    OH_AVRecorder_Range channels;
    /**
     * 音频采样率列表，包含所有支持的音频采样率值，取值由设备编码器能力决定，常见取值如8000、16000、44100、48000等，单位为赫兹（Hz）。
     * 与sampleRateLen字段配合使用，sampleRateLen表示该列表的长度。仅适用于音频编码器。
     */
    int32_t *sampleRate;
    /* 音频采样率列表长度，取值为大于0的整数，与sampleRate字段配合使用，表示sampleRate数组中元素的个数。仅适用于音频编码器。 */
    int32_t sampleRateLen;
} OH_AVRecorder_EncoderInfo;

/**
 * @brief 当录制状态发生变化时调用。
 * 
 * @param recorder OH_AVRecorder实例的指针。
 * @param state 表示录制器状态。
 * @param reason 录制器状态变化的原因。
 * @param userData 用户注册回调时传入的自定义数据指针，在回调触发时由系统回传给调用方。
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
typedef void (*OH_AVRecorder_OnStateChange)(OH_AVRecorder *recorder,
    OH_AVRecorder_State state, OH_AVRecorder_StateChangeReason reason, void *userData);

/**
 * @brief 当录制过程中发生错误时调用。
 * 
 * @param recorder OH_AVRecorder实例的指针。
 * @param errorCode 错误码，详细说明请参见{@link OH_AVErrCode}。
 * @param errorMsg 描述错误详情的字符串。
 * @param userData 用户注册回调时传入的自定义数据指针，在回调触发时由系统回传给调用方。
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
typedef void (*OH_AVRecorder_OnError)(OH_AVRecorder *recorder, int32_t errorCode, const char *errorMsg,
    void *userData);

/**
 * @brief 当录制在{@link OH_AVRecorder_FileGenerationMode}.AVRECORDER_AUTO_CREATE_CAMERA_SCENE模式下时调用。
 * 
 * @param recorder OH_AVRecorder实例的指针。
 * @param asset OH_MediaAsset实例的指针，用于返回系统自动创建的媒体资源对象，应用可通过该对象访问录制生成的媒体文件。
 * @param userData 用户注册回调时传入的自定义数据指针，在回调触发时由系统回传给调用方。
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
typedef void (*OH_AVRecorder_OnUri)(OH_AVRecorder *recorder, OH_MediaAsset *asset, void *userData);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_BASE_H
