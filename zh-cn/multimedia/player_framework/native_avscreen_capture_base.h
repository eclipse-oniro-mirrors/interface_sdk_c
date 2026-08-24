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
 * @addtogroup AVScreenCapture
 * @{
 *
 * @brief 提供屏幕录制的请求能力接口。
 * @since 10
 */
/**
 * @file native_avscreen_capture_base.h
 *
 * @brief 声明用于运行屏幕录制相关的结构体、字符常量、枚举、变量和函数。屏幕录制通过配置参数设置录制模式与音视频信息，
 * 通过回调函数获取录制数据、状态变更和隐私保护事件通知。
 * 支持多种录制模式（主屏幕、指定屏幕、指定窗口）、音频源类型（麦克风、内录、指定应用音频）配置及隐私保护、内容过滤等功能，
 * 适用于需要捕获屏幕画面和音频数据的应用场景。详细设计逻辑请参见AVScreenCapture。
 * 
 * @include <multimedia/player_framework/native_avscreen_capture_base.h>
 * @library libnative_avscreen_capture.so
 * @syscap SystemCapability.Multimedia.Media.AVScreenCapture
 * @kit MediaKit
 * @since 10
 */
 
#ifndef NATIVE_AVSCREEN_CAPTURE_BASE_H
#define NATIVE_AVSCREEN_CAPTURE_BASE_H

#include <stdbool.h>
#include <stdint.h>
#include "native_avbuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 提供录屏的视频原始数据缓冲区结构体。OH_NativeBuffer提供录屏的视频原始数据处理能力，支持对录屏过程中产生的视频原始数据
 * 进行封装、传输和管理。
 * 
 * 用于在AVScreenCapture录屏场景中承载获取的视频帧原始数据。可用于录屏数据的二次处理场景，如视频编辑应用中对录屏帧数据
 * 进行像素级操作、直播推流场景中对原始码流进行编码推送等。
 * 
 *
 * @since 10
 */
typedef struct OH_NativeBuffer OH_NativeBuffer;

/**
 * @brief 通过OH_AVScreenCapture可以获取视频与音频的原始码流。
 * 
 * 开发者需通过相关接口创建实例并配置采集参数后进行屏幕录制以获取码流数据。详细的模块设计逻辑与实现机制请参见AVScreenCapture。
 * 适用于屏幕录制、直播推流等需要捕获屏幕内容及系统/麦克风音频的场景，可帮助应用实现高质量的屏幕采集与音视频数据获取。
 *
 * @since 10
 */
typedef struct OH_AVScreenCapture OH_AVScreenCapture;

/**
 * @brief 通过OH_AVScreenCapture_ContentFilter过滤音视频内容。开发者可以配置过滤规则，实现对屏幕录制内容中音视频流的筛选和控制，
 * 满足不同场景下的内容处理需求。
 * 
 * 适用于隐私保护（如过滤敏感界面）、指定应用音视频排除等场景，可有效提升录屏内容的可控性。
 *
 * @since 12
 */
typedef struct OH_AVScreenCapture_ContentFilter OH_AVScreenCapture_ContentFilter;

/**
 * @brief 枚举，表示屏幕录制的不同模式。
 * 
 *
 * @since 10
 */
typedef enum OH_CaptureMode {
    /* capture home screen */
    OH_CAPTURE_HOME_SCREEN = 0,
    /* capture a specified screen */
    OH_CAPTURE_SPECIFIED_SCREEN = 1,
    /* capture a specified window */
    OH_CAPTURE_SPECIFIED_WINDOW = 2,
    OH_CAPTURE_INVAILD = -1
} OH_CaptureMode;

/**
 * @brief 枚举，表示屏幕录制时的音频源类型。
 * 
 * 适用于不同的音频录制需求：OH_MIC适用于需要录制外部声音（如解说、旁白）的场景；OH_ALL_PLAYBACK适用于需要录制系统播放的所有
 * 内部音频流（如系统音效、应用音频）的场景；OH_APP_PLAYBACK适用于需要仅录制指定应用播放音频的场景。
 * 
 *
 * @since 10
 */
typedef enum OH_AudioCaptureSourceType {
    /* 无效音频源。 */
    OH_SOURCE_INVALID = -1,
    /* 默认音频源，默认为麦克风。 */
    OH_SOURCE_DEFAULT = 0,
    /* 麦克风录制的外部音频流。 */
    OH_MIC = 1,
    /* 系统播放的所有内部音频流。 */
    OH_ALL_PLAYBACK = 2,
    /* 指定应用播放的内部音频流。*/
    OH_APP_PLAYBACK = 3,
} OH_AudioCaptureSourceType;

/**
 * @brief 枚举，表示音频编码格式。
 * 
 * OH_AUDIO_DEFAULT为默认编码，适用于大多数音视频录制场景；OH_AAC_LC为AAC_LC编码，
 * 适用于需要较好音质和较小文件大小的通用音视频应用场景。
 * 
 *
 * @since 10
 */
typedef enum OH_AudioCodecFormat {
    /* 默认音频编码，默认为AAC_LC。 */
    OH_AUDIO_DEFAULT = 0,
    /* AAC_LC音频编码。 */
    OH_AAC_LC = 3,
    /* 无效格式。 */
    OH_AUDIO_CODEC_FORMAT_BUTT,
} OH_AudioCodecFormat;

/**
 * @brief 枚举，表示视频编码格式。
 * 
 *
 * @since 10
 */
typedef enum OH_VideoCodecFormat {
    /* 默认视频编码，默认为H.264。 */
    OH_VIDEO_DEFAULT = 0,
    /* H.264。适用于大多数录制场景，兼容性最好，是最广泛支持的视频编码格式。 */
    OH_H264 = 2,
    /* H.265/HEVC。适用于对压缩效率要求高的场景，相同画质下文件更小，但兼容性低于H.264。 */
    OH_H265 = 4,
    /* MPEG4。适用于对兼容性要求不高的场景，压缩效率低于H.264/H.265。 */
    OH_MPEG4 = 6,
    /* VP8。适用于Web场景的开源编码格式，兼容性有限。 */
    OH_VP8 = 8,
    /* VP9。适用于Web高清场景的开源编码格式，压缩效率优于VP8，兼容性有限。 */
    OH_VP9 = 10,
    /* 无效格式。 */
    OH_VIDEO_CODEC_FORMAT_BUTT,
} OH_VideoCodecFormat;

/**
 * @brief 枚举，表示屏幕录制流的数据格式。
 * 
 * 根据使用需求选择合适的数据格式：原始流格式适用于需要实时处理音视频数据的场景（如实时预览、流式传输）；
 * 保存文件格式适用于直接录制为文件的场景。
 * 
 * 当前仅支持原始流格式和保存文件格式。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVScreenCapture
 *
 * @since 10
 */
typedef enum OH_DataType {
    /* 原始流格式，如YUV/RGBA/PCM等。 */
    OH_ORIGINAL_STREAM = 0,
    /* 编码流格式，如H.264/AAC等。当前版本暂不支持。 */
    OH_ENCODED_STREAM = 1,
    /* 保存文件格式，支持mp4。 */
    OH_CAPTURE_FILE = 2,
    /* 无效格式。 */
    OH_INVAILD = -1
} OH_DataType;

/**
 * @brief 枚举，表示视频源格式。此枚举类型当前仅支持RGBA格式。
 * 
 *
 * @since 10
 */
typedef enum OH_VideoSourceType {
    /**
     * YUV格式。当前版本暂不支持。
     */
    OH_VIDEO_SOURCE_SURFACE_YUV = 0,
    /* raw格式。当前版本暂不支持。 */
    OH_VIDEO_SOURCE_SURFACE_ES,
    /* RGBA格式。 */
    OH_VIDEO_SOURCE_SURFACE_RGBA,
    /* 无效格式。 */
    OH_VIDEO_SOURCE_BUTT
} OH_VideoSourceType;

/**
 * @brief 枚举，表示屏幕录制生成的文件类型。
 * 
 * 适用于不同的文件输出需求：CFT_MPEG_4A为音频格式m4a，适用于仅需要录制音频的场景；CFT_MPEG_4为视频格式mp4，
 * 适用于需要同时录制音视频的场景。
 * 
 *
 * @since 10
 */
typedef enum OH_ContainerFormatType {
    /* 音频格式 m4a。 */
    CFT_MPEG_4A = 0,
    /* 视频格式 mp4。 */
    CFT_MPEG_4 = 1
} OH_ContainerFormatType;

/**
 * @brief 音频采样信息。
 * 
 * 用于配置屏幕录制中的音频采集参数，包括采样率、声道数和音频源类型。
 * 开发者可通过设置audioSampleRate和audioChannels参数来控制录制音频的质量和声道布局，
 * 适用于屏幕录制时需要采集系统音频或麦克风音频的场景。
 * 
 * 当audioSampleRate和audioChannels同时为0时，忽略该类型音频相关参数，不录制该类型音频数据。
 *
 * @since 10
 */
typedef struct OH_AudioCaptureInfo {
    /**
     * 音频采样率，支持列表请查阅Audio Kit的AudioSamplingRate。单位为赫兹（Hz）。当audioSampleRate与audioChannels同时为0时，
     * 将忽略该类型音频相关参数。
     */
    int32_t audioSampleRate;
    /**
     * 音频声道数，用于配置音频录制的声道数量。具体支持的范围请参考相关音频设备的能力AudioChannel。
     * 当audioSampleRate与audioChannels同时为0时，将忽略该类型音频相关参数。
     */
    int32_t audioChannels;
    /**
     * 音频源，用于指定录制的音频来源，如系统音频或麦克风录音等。可选值请参考{@link OH_AudioCaptureSourceType}。
     */
    OH_AudioCaptureSourceType audioSource;
} OH_AudioCaptureInfo;

/**
 * @brief 音频编码信息。
 * 
 * 用于配置屏幕录制场景下的音频编码参数，包括音频编码比特率和音频编码格式。
 * 通过设置这些参数，开发者可以控制音频的质量和文件大小，适用于需要在屏幕录制场景中指定音频编码质量和编码方式的场景。
 * 支持的编码格式详见{@link OH_AudioCodecFormat}枚举定义。
 *
 * @since 10
 */
typedef struct OH_AudioEncInfo {
    /**
     * 音频编码比特率，用于设置音频编码的输出比特率。取值范围需参考具体编码格式支持的比特率范围，常见取值有48000、96000和128000。
     * 单位为比特每秒（bit/s）。超出编码格式支持范围时可能导致编码失败。
     */
    int32_t audioBitrate;
    /**
     * 音频编码格式，用于指定屏幕录制时音频数据所采用的编码格式。不同编码格式对应不同的编码算法、压缩效率、兼容性和质量表现，
     * 选择合适的编码格式会影响音频文件的大小、播放兼容性和音质。支持的编码格式详见{@link OH_AudioCodecFormat}枚举定义。
     */
    OH_AudioCodecFormat audioCodecformat;
} OH_AudioEncInfo;

/**
 * @brief 音频信息。
 * 
 * OH_AudioInfo作为OH_ScreenCaptureConfig的音频配置成员，包含麦克风采集信息、内录采集信息和音频编码信息三个部分，开发者需根据
 * 采集场景选择配置麦克风采集信息或内录采集信息，并在需要编码输出时配置音频编码信息。适用于需要在屏幕录制中采集音频数据的场景。
 * 
 * 同时采集音频麦克风和音频内录数据时，两路音频的audioSampleRate和audioChannels采集参数需要相同，因为两路音频数据将合并为
 * 同一音频流输出，采集参数不一致会导致音频同步异常或采集失败。
 * 
 *
 * @since 10
 */
typedef struct OH_AudioInfo {
    /* 音频麦克风采集信息，用于配置麦克风音频采集的采集参数。 */
    OH_AudioCaptureInfo micCapInfo;
    /* 音频内录采集信息，用于配置内录音频采集的采集参数。 */
    OH_AudioCaptureInfo innerCapInfo;
    /* 音频编码信息。采集原始码流时不需要设置编码参数。未设置时默认不进行音频编码。 */
    OH_AudioEncInfo audioEncInfo;
} OH_AudioInfo;

/**
 * @brief 视频采集配置信息。用于配置屏幕录制时的视频参数。该结构体需要配合captureMode使用：在CAPTURE_SPECIFIED_SCREEN模式下需设置displayId指定物理屏；在CAPTURE_SPECIFIED_WINDOW模式下需设置missionIDs指定窗口。适用于屏幕录制应用、视频会议录制、直播推流、游戏录制等场景。当videoFrameWidth和videoFrameHeight同时为0时，系统将忽略视频采集相关配置参数，不录制屏幕视频数据。通过该结构体可以灵活控制录屏的视频采集行为。
 * 
 *
 * @since 10
 */
typedef struct OH_VideoCaptureInfo {
    /**
     * 采集物理屏ID，设置后录制指定物理屏幕的内容。使用该参数需要在captureMode为CAPTURE_SPECIFIED_SCREEN模式下使用，
     * 其他模式下此参数不生效。可通过系统显示管理接口获取有效的displayId值。取值范围大于等于0。传入无效ID时录制失败。
     */
    uint64_t displayId;
    /**
     * 指定窗口ID数组，设置后录制指定窗口内容。适用于仅录制特定应用窗口内容的场景，如录制单个应用操作演示、
     * 避免录制桌面背景和隐私信息等。使用该参数需要在captureMode为CAPTURE_SPECIFIED_WINDOW模式下使用，其他模式下此参数不生效。
     * 可通过窗口接口getWindowProperties获取有效的missionID值。列表长度需与missionIDsLen匹配，ID取值为整数。
     * 传入无效ID时录制失败。
     */
    int32_t *missionIDs;
    /**
     * 指定窗口ID数组的长度，使用该参数需要在captureMode为CAPTURE_SPECIFIED_WINDOW模式下使用，其他模式下此参数不生效。
     * 取值需大于0，且与missionIDs列表实际长度一致。
     */
    int32_t missionIDsLen;
    /**
     * 采集视频的宽度设置，单位为像素（px）。取值范围需大于等于0。传入负数或超出设备支持分辨率时，屏幕录制将失败。
     * 当videoFrameWidth与videoFrameHeight同时为0时，系统将忽略视频采集相关配置参数，不录制屏幕视频数据。
     */
    int32_t videoFrameWidth;
    /**
     * 采集视频的高度设置，单位为像素（px）。取值范围需大于等于0。传入负数或超出设备支持分辨率时，屏幕录制将失败。
     * 当videoFrameWidth与videoFrameHeight同时为0时，系统将忽略视频采集相关配置参数，不录制屏幕视频数据。
     */
    int32_t videoFrameHeight;
    /**
     * 视频采集格式设置，目前仅支持RGBA格式。不设置时默认使用RGBA格式。RGBA格式适用于需要获取原始像素数据进一步处理的场景，
     * 详情请参考{@link OH_VideoSourceType}。设置其他格式时不支持该采集行为。当videoFrameWidth和videoFrameHeight同时为0时，
     * 此参数不生效。
     */
    OH_VideoSourceType videoSource;
} OH_VideoCaptureInfo;

/**
 * @brief 视频编码参数。
 * 
 * 用于配置屏幕录制的视频编码参数，支持设置编码格式、比特率和帧率。videoCodec指定编码格式（如H.264、H.265等），
 * videoBitrate影响视频清晰度和文件大小，videoFrameRate影响视频流畅度。通常在调用屏幕录制接口前设置这些参数。
 * 
 * @syscap SystemCapability.Multimedia.Media.AVScreenCapture
 *
 * @since 10
 */
typedef struct OH_VideoEncInfo {
    /**
     * 视频编码格式。不同编码格式影响视频的压缩效率与兼容性，具体各格式效果参见OH_VideoCodecFormat枚举说明。
     */
    OH_VideoCodecFormat videoCodec;
    /**
     * 视频编码比特率，单位为比特每秒（bit/s）。取值范围需根据编码格式和实际需求确定，默认取值为10000000，
     * 值越大画质越好但文件也越大。
     */
    int32_t videoBitrate;
    /**
     * 视频编码帧率，单位为帧每秒（FPS）。常见取值范围为15~60 FPS。
     */
    int32_t videoFrameRate;
} OH_VideoEncInfo;

/**
 * @brief 视频信息。
 * 
 * 用于配置屏幕录制时的视频采集参数和编码参数。该结构体包含视频采集参数（如分辨率、采集格式等）和视频编码参数，
 * 适用于需要自定义屏幕录制视频输出参数的场景。开发者根据实际需求配置相关参数后，在调用屏幕录制相关接口时使用。
 * 
 *
 * @since 10
 */
typedef struct OH_VideoInfo {
    /**
     * 视频采集信息，用于配置屏幕录制时的视频采集区域、分辨率等参数。
     */
    OH_VideoCaptureInfo videoCapInfo;
    /**
     * 视频编码参数，用于配置屏幕录制输出的编码格式、比特率和帧率，不同编码配置将影响输出视频的画质、文件大小和编码效率。
     */
    OH_VideoEncInfo videoEncInfo;
} OH_VideoInfo;

/**
 * @brief 录制文件信息。
 * 
 * OH_RecorderInfo用于存储屏幕录制文件的输出信息，包括录制文件的URL地址、URL长度及文件格式，
 * 适用于需要配置屏幕录制输出目标及格式的场景，帮助开发者灵活指定录制文件的存储路径和封装格式。
 * 
 *
 * @since 10
 */
typedef struct OH_RecorderInfo {
    /**
     * 录制文件的URL，用于指定录屏文件的输出位置。仅支持本地文件路径URL格式。需与urlLen配合使用。
     */
    char *url;
    /**
     * 录制文件的URL的长度值，表示url参数所指字符串的字节长度（不包括终止空字符）。需与url参数配合使用，不匹配时可能导致录制异常。
     */
    uint32_t urlLen;
    /**
     * 录制文件的容器封装格式类型，用于指定录屏输出的文件封装格式。可选值：CFT_MPEG_4A（M4A格式，适用于仅需要录制音频的场景）、
     * CFT_MPEG_4（MP4格式，适用于需要同时录制音视频的场景）。可选值为{@link OH_ContainerFormatType}中定义的格式类型。
     */
    OH_ContainerFormatType fileFormat;
} OH_RecorderInfo;

/**
 * @brief 屏幕录制配置参数。
 * 
 * 用于配置屏幕录制的模式、数据格式、音频参数、视频参数及录制文件参数等，适用于需要自定义屏幕录制行为（如选择录制模式、
 * 指定数据输出格式、设置音视频编码参数等）的场景。
 *
 * @since 10
 */
typedef struct OH_AVScreenCaptureConfig {
    /**
     * 屏幕录制的模式，用于指定屏幕录制的捕获方式。不同的captureMode值决定录制内容的范围和交互方式，
     * 开发者应根据需要录制的屏幕区域和交互需求选择合适的模式。可取值包括OH_CAPTURE_HOME_SCREEN（录制主屏幕）
     * 和OH_CAPTURE_SPECIFIED_WINDOW（录制指定窗口）等，具体枚举值见{@link OH_CaptureMode}。
     */
    OH_CaptureMode captureMode;
    /**
     * 屏幕录制流的数据格式，例如需要实时处理录制流数据时可选择流数据格式，需要保存为文件时可选择文件数据格式。
     * 取值原则参考OH_DataType枚举定义。当数据格式为OH_CAPTURE_FILE时，必须设置{@link OH_RecorderInfo}。
     */
    OH_DataType dataType;
    /**
     * 音频录制参数，用于配置录制的音频相关属性。包含音频编码格式、采样率、声道数等配置项，具体属性见{@link OH_AudioInfo}。
     */
    OH_AudioInfo audioInfo;
    /**
     * 视频录制参数，用于配置录制的视频相关属性。包含视频编码格式、分辨率、帧率等配置项，具体属性见{@link OH_VideoInfo}。
     */
    OH_VideoInfo videoInfo;
    /**
     * 录制文件参数，当数据格式为OH_CAPTURE_FILE时必须设置，未设置时录制无法正常启动。
     */
    OH_RecorderInfo recorderInfo;
} OH_AVScreenCaptureConfig;

/**
 * @brief 隐私保护信息结构体。
 * 
 * 用于在屏幕录制场景中对系统窗口和敏感应用进行隐私保护。通过设置该结构体的成员变量，可以控制是否开启系统窗口隐私保护和
 * 敏感应用隐私保护，避免在屏幕录制过程中泄露隐私信息。systemWindowProtection控制系统窗口级别的隐私保护，
 * sensitiveAppProtection控制敏感应用级别的隐私保护，适用于需要在屏幕录制时保护用户隐私数据的场景。如屏幕录制或截图时，
 * 需要保护敏感窗口（如银行应用、聊天窗口）不被捕获；金融类应用需要保护用户输入的敏感信息；
 * 视频会议应用需要保护共享屏幕中的隐私内容的场景。
 * 
 * @since 24
 */
typedef struct OH_PrivacyProtectInfo {
    /**
     * @brief 是否开启系统窗口隐私保护。true表示开启隐私保护，false表示关闭隐私保护，默认值为true。
     * 系统窗口是指系统级应用（如设置、通知等）的窗口；需在屏幕录制启动前配置该参数，开启后录屏时该类窗口内容将被保护处理。
     * 典型场景：在屏幕录制或共享时，开启此项可保护通知栏、弹窗等系统窗口中的隐私信息不被录制或共享出去。
     * @since 24
     */
    bool systemWindowProtection;
    /**
     * @brief 是否开启敏感应用的隐私保护。true表示开启隐私保护，false表示关闭隐私保护，默认值为true。
     * 敏感应用是指包含用户隐私数据的应用；需在屏幕录制启动前配置该参数，开启后录屏时该类应用窗口内容将被保护处理。
     * 典型场景：在屏幕录制或共享时，开启此项可保护银行、社交等敏感应用的内容不被录制或共享出去。
     * @since 24
     */
    bool sensitiveAppProtection;
} OH_PrivacyProtectInfo;

/**
 * @brief 当OH_AVScreenCapture实例运行出错时，系统将调用该函数指针通知应用程序。
 * 从API version 12开始，推荐使用接口{@link OH_AVScreenCapture_OnError}替代。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param errorCode 指定错误码，具体错误码值及含义请参考{@link OH_AVSCREEN_CAPTURE_ErrCode}说明。
 * @since 10
 */
typedef void (*OH_AVScreenCaptureOnError)(OH_AVScreenCapture *capture, int32_t errorCode);

/**
 * @brief 当OH_AVScreenCapture实例操作期间音频缓冲区可用时，系统将调用该函数指针通知应用程序。
 * 从API版本12开始，推荐使用接口OH_AVScreenCapture_OnBufferAvailable替代。OH_AVScreenCapture_OnBufferAvailable将音频和
 * 视频缓冲区回调统一为一个接口，通过bufferType参数区分缓冲区数据类型，同时增加了timestamp和userData参数支持，
 * 开发者无需分别注册音频和视频回调。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param isReady 音频缓冲区是否可用。true表示音频缓冲区可用，false表示音频缓冲区不可用。
 * @param type 音频源类型，用于标识音频数据的来源。OH_MIC表示麦克风音频数据；OH_ALL_PLAYBACK表示系统内录音频数据；
 * OH_APP_PLAYBACK表示指定应用播放的音频数据。开发者应根据type值对音频数据进行相应处理。
 * @since 10
 */
typedef void (*OH_AVScreenCaptureOnAudioBufferAvailable)(OH_AVScreenCapture *capture, bool isReady,
    OH_AudioCaptureSourceType type);

/**
 * @brief 当OH_AVScreenCapture实例操作期间视频缓冲区可用时，系统将调用该函数指针通知应用程序。
 * 从API version 12开始，推荐使用接口{@link OH_AVScreenCapture_OnBufferAvailable}替代。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param isReady 视频缓冲区是否可用。true表示视频缓冲区可用，false表示视频缓冲区不可用。
 * @since 10
 */
typedef void (*OH_AVScreenCaptureOnVideoBufferAvailable)(OH_AVScreenCapture *capture, bool isReady);

/**
 * @brief OH_AVScreenCaptureCallback是OH_AVScreenCapture中所有异步回调函数指针的集合。
 * 应用将该结构体的实例注册到OH_AVScreenCapture实例中，以便处理回调上报的信息，从而保证OH_AVScreenCapture的正常运行。
 * 该回调集合用于监控录屏过程中的错误、音频数据和视频数据的产生，适用于需要实时获取和处理录屏数据的场景，具有异步处理的特点，
 * 能有效提升录屏数据处理的效率。
 * 
 * 从API version 12开始，推荐使用接口OH_AVScreenCapture_OnError、OH_AVScreenCapture_OnBufferAvailable替代。
 * 
 *
 * @since 10
 */
typedef struct OH_AVScreenCaptureCallback {
    /**
     * 录屏调用操作发生错误时触发的回调函数。当录屏过程中出现权限缺失、编码异常等错误时触发回调，
     * 开发者可根据错误类型进行重试或向用户提示。需先将包含该回调的结构体实例注册到OH_AVScreenCapture实例中，
     * 才能接收错误回调上报信息。可能上报的错误码请参考{@link OH_AVSCREEN_CAPTURE_ErrCode}。从API version 12开始，
     * 推荐使用接口{@link OH_AVScreenCapture_OnError}替代。
     */
    OH_AVScreenCaptureOnError onError;
    /**
     * 音频缓冲区有数据可用时触发的回调函数，当录屏过程中音频数据就绪时触发回调，开发者可在此回调中获取音频缓冲区数据进行音频录制、
     * 编码或直播推流等处理。需先将包含该回调的结构体实例注册到OH_AVScreenCapture实例中，才能接收音频数据回调上报信息。
     * 从API version 12开始，推荐使用接口{@link OH_AVScreenCapture_OnBufferAvailable}替代。
     */
    OH_AVScreenCaptureOnAudioBufferAvailable onAudioBufferAvailable;
    /**
     * 视频缓冲区有数据可用时触发的回调函数，当录屏过程中视频数据就绪时触发回调，开发者可在此回调中获取视频缓冲区数据进行视频录制、
     * 编码或直播推流等处理。需先将包含该回调的结构体实例注册到OH_AVScreenCapture实例中，
     * 才能接收视频数据回调上报信息。从API version 12开始，推荐使用接口{@link OH_AVScreenCapture_OnBufferAvailable}替代。
     */
    OH_AVScreenCaptureOnVideoBufferAvailable onVideoBufferAvailable;
} OH_AVScreenCaptureCallback;

/**
 * @brief 定义录屏界面的位置和尺寸。包含位置坐标和尺寸信息。可用于精确控制录屏范围，支持自定义区域录制、局部录制等场景。
 * 
 * 适用于教学/演示录制中只录制重点操作区域、会议录制中只录制演示文稿区域和游戏录制中只录制游戏画面区域等场景。
 * 
 *
 * @since 10
 */
typedef struct OH_Rect {
    /**
     * 录屏界面的X坐标，相对于屏幕左上角。取值需大于等于0，单位为像素（px）。
     */
    int32_t x;
    /**
     * 录屏界面的Y坐标，相对于屏幕左上角。取值需大于等于0，单位为像素（px）。
     */
    int32_t y;
    /**
     * 录屏区域的宽度，取值需大于0，单位为像素（px）。传入0或负数时录屏不生效。
     */
    int32_t width;
    /**
     * 录屏区域的高度，取值需大于0，单位为像素（px）。传入0或负数时录屏不生效。
     */
    int32_t height;
} OH_Rect;


/**
 * @brief 定义了音频缓冲区数据及其大小、类型、时间戳等属性信息。
 * 
 * 在屏幕录制过程中，该结构体由系统通过音频数据回调填充，开发者可从中读取录制的音频帧数据及其时间戳，用于后续音频处理或编码。
 * 适用于需要获取屏幕录制音频帧数据的场景。
 *
 * @since 10
 */
typedef struct OH_AudioBuffer {
    /**
     * 指向音频缓冲区内存的指针。由系统分配和释放，开发者无需手动管理。音频缓冲区用于存储录制的音频采样数据，
     * 数据格式为PCM原始字节流，需配合size字段确定数据长度。
     */
    uint8_t *buf;
    /**
     * 音频缓冲区内存大小，单位为字节（Byte），表示buf指针所指音频数据的字节长度。
     * 取值范围大于等于0，由系统填充，值为负数时将报错。
     */
    int32_t size;
    /**
     * 音频缓冲区时间戳，表示该音频帧的时间位置。单位为纳秒（ns）。
     */
    int64_t timestamp;
    /**
     * 音频录制源类型。其值由OH_AudioCaptureInfo中配置的{@link OH_AudioCaptureSourceType}决定。
     */
    OH_AudioCaptureSourceType type;
} OH_AudioBuffer;

/**
 * @brief 枚举，表示状态码。
 * 
 * 状态码反映了录屏的生命周期变化，包括开始、暂停、恢复、停止、中断及隐私场景切换等状态，
 * 状态变更通过OH_AVScreenCapture_OnStateChange回调通知应用。
 * 
 *
 * @since 12
 */
typedef enum OH_AVScreenCaptureStateCode {
    /* 	已开始录屏。 */
    OH_SCREEN_CAPTURE_STATE_STARTED = 0,
    /* 已取消录屏。 */
    OH_SCREEN_CAPTURE_STATE_CANCELED = 1,
    /* 已停止录屏。 */
    OH_SCREEN_CAPTURE_STATE_STOPPED_BY_USER = 2,
    /* 录屏被其他录屏中断。 */
    OH_SCREEN_CAPTURE_STATE_INTERRUPTED_BY_OTHER = 3,
    /* 录屏被通话中断。 */
    OH_SCREEN_CAPTURE_STATE_STOPPED_BY_CALL = 4,
    /* 麦克风不可用。 */
    OH_SCREEN_CAPTURE_STATE_MIC_UNAVAILABLE = 5,
    /* 麦克风被静音。 */
    OH_SCREEN_CAPTURE_STATE_MIC_MUTED_BY_USER = 6,
    /* 麦克风被取消静音。 */
    OH_SCREEN_CAPTURE_STATE_MIC_UNMUTED_BY_USER = 7,
    /* 进入隐私界面。 */
    OH_SCREEN_CAPTURE_STATE_ENTER_PRIVATE_SCENE = 8,
    /* 隐私界面退出。 */
    OH_SCREEN_CAPTURE_STATE_EXIT_PRIVATE_SCENE = 9,
    /* 系统用户切换，录屏中断。 */
    OH_SCREEN_CAPTURE_STATE_STOPPED_BY_USER_SWITCHES = 10,
    /**
     * @brief 用户暂停屏幕录制。
     * @since 26.0.0
     */
    OH_SCREEN_CAPTURE_STATE_PAUSED_BY_USER = 11,
    /**
     * @brief 用户恢复屏幕录制。
     * @since 26.0.0
     */
    OH_SCREEN_CAPTURE_STATE_RESUMED_BY_USER = 12,
    /**
     * @brief 应用暂停屏幕录制。
     * @since 26.0.0
     */
    OH_SCREEN_CAPTURE_STATE_PAUSED_BY_APP = 13,
    /**
     * @brief 应用恢复屏幕录制。
     * @since 26.0.0
     */
    OH_SCREEN_CAPTURE_STATE_RESUMED_BY_APP = 14,
} OH_AVScreenCaptureStateCode;

/**
 * @brief 枚举，表示buffer类型。
 * 
 *
 * @since 12
 */
typedef enum OH_AVScreenCaptureBufferType {
    /* Buffer of video data from screen */
    OH_SCREEN_CAPTURE_BUFFERTYPE_VIDEO = 0,
    /* Buffer of audio data from inner capture */
    OH_SCREEN_CAPTURE_BUFFERTYPE_AUDIO_INNER = 1,
    /* Buffer of audio data from microphone */
    OH_SCREEN_CAPTURE_BUFFERTYPE_AUDIO_MIC = 2,
} OH_AVScreenCaptureBufferType;

/**
 * @brief 枚举，表示buffer类型。
 * 
 *
 * @since 12
 */
typedef enum OH_AVScreenCaptureFilterableAudioContent {
    /* Audio content of notification sound */
    OH_SCREEN_CAPTURE_NOTIFICATION_AUDIO = 0,
    /* Audio content of the sound of the app itself */
    OH_SCREEN_CAPTURE_CURRENT_APP_AUDIO = 1,
} OH_AVScreenCaptureFilterableAudioContent;

/**
 * @brief 当OH_AVScreenCapture实例操作期间发生状态变更时，将调用函数指针。
 * 需通过OH_AVScreenCapture相关接口设置该回调后方可生效，未设置时回调不会被调用。
 * 此回调通过stateCode参数返回状态码。状态变更包括录屏开始、暂停、恢复、停止、中断及隐私场景切换等，
 * 具体状态码见{@link OH_AVScreenCaptureStateCode}。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param stateCode 指定状态码，用于标识录屏状态的变化。常见状态包括：OH_SCREEN_CAPTURE_STATE_STARTED（录屏已开始）、
 * OH_SCREEN_CAPTURE_STATE_CANCELED（用户取消录屏）、OH_SCREEN_CAPTURE_STATE_STOPPED_BY_USER（用户停止录屏）等。
 * 开发者应根据不同状态执行相应操作。
 * @param userData 指向应用设置该回调处理方法时提供的自定义数据的指针。
 * @since 12
 */
typedef void (*OH_AVScreenCapture_OnStateChange)(struct OH_AVScreenCapture *capture,
    OH_AVScreenCaptureStateCode stateCode, void *userData);

/**
 * @brief 当OH_AVScreenCapture实例操作期间发生错误时，系统将调用该函数指针通知应用程序。
 * 使用前需将该回调注册到OH_AVScreenCapture实例中。应在录屏开始前注册该错误回调以便及时处理错误。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param errorCode 指定错误码，具体错误码值及含义请参考{@link OH_AVSCREEN_CAPTURE_ErrCode}说明。
 * @param userData 指向应用设置该回调处理方法时提供的自定义数据的指针。
 * @since 12
 */
typedef void (*OH_AVScreenCapture_OnError)(OH_AVScreenCapture *capture, int32_t errorCode, void *userData);

/**
 * @brief 当OH_AVScreenCapture实例操作期间音频或视频缓冲区可用时，系统将调用该函数指针通知应用程序。
 * 使用前需将该回调注册到OH_AVScreenCapture实例中。
 * 
 * 该回调方法执行结束返回后，数据缓冲区不再有效，应用需要在回调内及时处理数据。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param buffer 指向OH_AVBuffer缓冲区实例的指针，该回调方法执行结束返回后，数据缓冲区不再有效。
 * @param bufferType 可用缓冲区的数据类型，指示当前可用缓冲区的数据类型。
 * OH_SCREEN_CAPTURE_BUFFERTYPE_VIDEO表示视频数据缓冲区可用；
 * OH_SCREEN_CAPTURE_BUFFERTYPE_AUDIO_INNER表示内录音频缓冲区可用；
 * OH_SCREEN_CAPTURE_BUFFERTYPE_AUDIO_MIC表示麦克风音频缓冲区可用。
 * 开发者应根据bufferType类型对buffer数据进行相应处理。
 * @param timestamp 时间戳，单位：纳秒（ns）。
 * @param userData 指向应用设置该回调处理方法时提供的自定义数据的指针。
 * @since 12
 */
typedef void (*OH_AVScreenCapture_OnBufferAvailable)(OH_AVScreenCapture *capture, OH_AVBuffer *buffer,
    OH_AVScreenCaptureBufferType bufferType, int64_t timestamp, void *userData);

/**
 * @brief 当录屏事件开始时，将调用函数指针。使用前需将该回调注册到OH_AVScreenCapture实例中。应在录屏开始前完成注册。
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param displayId 录屏屏幕的ID。用于标识用户选择的具体屏幕。
 * @param userData 指向应用设置该回调处理方法时提供的自定义数据的指针。
 *
 * @since 15
 */
typedef void (*OH_AVScreenCapture_OnDisplaySelected)(OH_AVScreenCapture *capture, uint64_t displayId, void *userData);

/**
 * @brief 枚举，表示录屏内容变更事件。
 * 
 *
 * @since 20
 */
typedef enum OH_AVScreenCaptureContentChangedEvent_Enum {
    /**
     * 录屏内容变为隐藏。
     */
    OH_SCREEN_CAPTURE_CONTENT_HIDE = 0,
    /**
     * 录屏内容变为可见。
     */
    OH_SCREEN_CAPTURE_CONTENT_VISIBLE = 1,
    /**
     * 录屏内容状态变化为不可用，如录屏窗口关闭。
     */
    OH_SCREEN_CAPTURE_CONTENT_UNAVAILABLE = 2,
} OH_AVScreenCaptureContentChangedEvent;

/**
 * @brief 当OH_AVScreenCapture实例操作期间录屏内容变化时，将调用函数指针。使用前需将该回调注册到OH_AVScreenCapture实例中。
 * 此回调通过event参数返回内容变更事件，具体事件值参见{@link OH_AVScreenCaptureContentChangedEvent}枚举。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param event 录屏内容变更事件，指示录屏内容的状态变化。
 * OH_SCREEN_CAPTURE_CONTENT_HIDE表示录屏内容变为隐藏（如进入隐私界面）；
 * OH_SCREEN_CAPTURE_CONTENT_VISIBLE表示录屏内容从隐藏变为可见；
 * OH_SCREEN_CAPTURE_CONTENT_UNAVAILABLE表示录屏内容不可用（如窗口关闭）。
 * 开发者应根据不同事件类型调整录屏状态。
 * @param area 录屏内容可见时，对应位置信息；录屏内容隐藏或不可见时，该参数无效。
 * @param userData 指向应用设置该回调处理方法时提供的自定义数据的指针。
 *
 * @since 20
 */
typedef void (*OH_AVScreenCapture_OnCaptureContentChanged)(OH_AVScreenCapture* capture, OH_AVScreenCaptureContentChangedEvent event,
    OH_Rect* area, void *userData);

/**
 * @brief 表示高亮边框的样式，用于在录屏场景中标记被录制区域的边界，包括高亮边框的模式、边框宽度和边框颜色。
 * 通过配置高亮边框，可帮助用户清晰区分录屏区域与非录屏区域，提升录屏交互体验。
 * 该配置通常用于屏幕录制场景中高亮显示特定区域，例如：录制操作教程时高亮标注操作区域、
 * 录制应用演示时突出显示重点内容、录制游戏时标注关注区域等。
 * 
 * @since 22
 */
typedef struct OH_AVScreenCaptureHighlightConfig {
    /**
     * 高亮边框的模式，各枚举值的意义及与数字的对应关系请参见{@link OH_ScreenCaptureHighlightMode}枚举定义
     * 。方形全包边框：适用于常规录制场景，高亮效果更明显。四角包裹边框：适用于需要减少视觉干扰的场景。
     * 未指定时默认为方形全包边框（即边框完全包围捕获区域的所有边）；其他模式请根据录制区域的显示需求选择。
     */
    OH_ScreenCaptureHighlightMode mode;
    /**
     * 高亮边框的宽度，不设置默认不显示线宽（即线宽为0或未绘制），宽度有效值范围在[1, 8]，单位为虚拟像素（vp）。
     * 超出有效值范围的设置不生效。设置后会以指定的宽度在录制区域周围绘制高亮边框，宽度越大边框越粗。
     */
    uint32_t lineThickness;
    /**
     * 	高亮边框的颜色，不设置默认为黑色（0x000000），颜色有效值为RGB（0x000000-0xffffff）格式和
     * 非透明的ARGB（0xff000000-0xffffffff）格式，超出有效值范围的设置不生效。设置后会以指定的颜色在录制区域周围绘制高亮边框，
     * 可用于区分不同的录制区域或提高可视性。
     */
    uint32_t lineColor;  
} OH_AVScreenCaptureHighlightConfig;

/**
 * @brief 枚举，表示屏幕录制高亮边框的模式。
 * 
 * @since 22
 */
typedef enum OH_ScreenCaptureHighlightMode {
    /**
     * 默认模式，用方形全包边框高亮显示录制区域。
     */
    OH_HIGHLIGHT_MODE_CLOSED = 0,
    /**
     * 用四角包裹边框高亮显示录制区域。
     */
    OH_HIGHLIGHT_MODE_CORNER_WRAP = 1,
} OH_ScreenCaptureHighlightMode;

/**
 * @brief 图像填充模式。
 * 
 * @since 20
 */
typedef enum OH_AVScreenCapture_FillMode {
    /**
     * 保持图像原始宽高比匹配目标图像大小，若比例不一致可能存在黑边。
     */
    OH_SCREENCAPTURE_FILLMODE_ASPECT_SCALE_FIT = 0,
    /**
     * 图像拉伸匹配目标图像大小，若比例不一致图像变形。
     */
    OH_SCREENCAPTURE_FILLMODE_SCALE_TO_FILL = 1,
} OH_AVScreenCapture_FillMode;

/**
 * @brief 枚举，表示Picker显示模式。
 * 
 * @since 22
 */
typedef enum OH_CapturePickerMode {
    /**
     * 仅显示窗口模式。
     */
    OH_CAPTURE_PICKER_MODE_WINDOW_ONLY = 0,

    /**
     * 仅显示屏幕模式。
     */
    OH_CAPTURE_PICKER_MODE_SCREEN_ONLY = 1,

    /**
     * 显示屏幕和窗口模式（默认模式）。
     */
    OH_CAPTURE_PICKER_MODE_SCREEN_AND_WINDOW = 2,
} OH_CapturePickerMode;

/**
 * @brief 通过OH_AVScreenCapture_CaptureStrategy设置录屏策略。用于配置录屏行为，如录制内容范围、输出格式、性能参数等。
 * 支持配置录屏参数、调整录制质量、管理录制资源等。
 * 
 * 录屏策略需在录屏启动之前通过OH_AVScreenCapture_SetCaptureStrategy接口设置，录屏启动后设置将不生效。
 * 
 * 支持开发者根据业务需求灵活配置录屏捕获行为，适用于需要定制录屏策略的场景，可提升录屏功能的适用性和可控性。
 * 
 *
 * @since 20
 */
typedef struct OH_AVScreenCapture_CaptureStrategy OH_AVScreenCapture_CaptureStrategy;

/**
 * @brief 开发者可通过OH_AVScreenCapture_UserSelectionInfo获取用户在授权界面（选择界面）选择的参数（如捕获类型，捕获窗口等）。
 * 例如，在屏幕录制应用中，用户可以选择录制区域、录制音频源等参数后，使用该结构体获取用户的选择结果。
 * 
 * 该结构体用于在屏幕录制授权流程中承载用户的选择结果，开发者可在授权完成后通过此结构体读取用户的授权选择信息。
 * 适用于应用需要根据用户授权选择来配置录屏行为的场景，帮助开发者灵活适配用户的录屏偏好。
 *
 * @since 20
 */
typedef struct OH_AVScreenCapture_UserSelectionInfo OH_AVScreenCapture_UserSelectionInfo;

/**
 * @brief 当用户在授权界面（选择界面）选择参数时，系统通过该回调函数将用户选择的参数返回给应用程序。
 * 
 * 需要通过相关注册方法设置到OH_AVScreenCapture实例中。应在启动授权流程前完成注册以便接收用户选择结果。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param selections 用户在授权界面选择的录制参数信息。
 * @param userData 指向应用设置该回调处理方法时提供的自定义数据的指针。
 *
 * @since 20
 */
typedef void (*OH_AVScreenCapture_OnUserSelected)(OH_AVScreenCapture* capture, 
    OH_AVScreenCapture_UserSelectionInfo* selections, void *userData);

/**
 * @brief 多屏幕录制能力信息。多屏场景下，用户选择的多屏幕是否支持联合录制，以及联合录制的屏幕宽度和高度。
 * 联合录制指将多个屏幕的内容同时录制到一个视频文件中。该结构体支持查询多屏设备的联合录制能力，
 * 帮助开发者判断当前设备是否支持同时对多个屏幕进行录制，适用于会议演示、游戏录制、教学场景等需要跨屏录制的应用场景。
 * 通过联合录制能力，用户可以一次性捕获多个屏幕的内容，提升录制效率和内容完整性。
 * 
 * @since 24
 */
typedef struct OH_MultiDisplayCapability {
    /**
     * 是否支持多屏幕联合录制，true表示支持多屏幕联合录制，此时width和height为联合录制区域尺寸；
     * false表示不支持多屏幕联合录制，此时width和height无效。
     */
    bool isMultiDisplaySupport;
    /**
     * 多屏幕联合录制的屏幕区域宽度（单位：像素）。当isMultiDisplaySupport为true时，该值为所有选中屏幕联合录制区域的宽度；
     * 当isMultiDisplaySupport为false时，该值无效。
     */
    uint32_t width;
    /**
     * 多屏幕联合录制的屏幕区域高度（单位：像素）。当isMultiDisplaySupport为true时，该值为所有选中屏幕联合录制区域的高度；
     * 当isMultiDisplaySupport为false时，该值无效。
     */
    uint32_t height;
} OH_MultiDisplayCapability;

/**
 * @brief 当{@link OH_AVScreenCapture}实例在运行过程中发生隐私保护事件时，函数指针将被调用。
 * 
 * @param capture 指向OH_AVScreenCapture实例的指针。
 * @param privacyProtect 隐私保护信息指针。指向包含隐私保护事件详细信息的结构体，用于处理录屏过程中的隐私保护回调事件。
 * @param userData 指向应用设置该回调处理方法时提供的自定义数据的指针。
 * @since 24
 */
typedef void (*OH_AVScreenCapture_OnPrivacyProtect)(OH_AVScreenCapture* capture,
    OH_PrivacyProtectInfo* privacyProtect, void *userData);

/**
* @brief 获取录屏图像帧中有效内容区域信息的key。
* 通过此key获取到的返回值是一个int32_t数组，单位为像素（px）。
* 数组长度为4。数组元素定义为[top, left, width, height]，其中top表示矩形窗口左上角纵坐标，left表示矩形窗口左上角横坐标，
* width表示矩形窗口的宽度，height表示矩形窗口的高度。数组元素可以从OH_AVFormat_GetIntBuffer中获取。
* @since 26.0.0
*/
extern const char *OH_SCREEN_CAPTURE_CONTENT_RECT;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSCREEN_CAPTURE_BASE_H
/** @} */
