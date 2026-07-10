/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup CodecBase
 * @{
 *
 * @brief CodecBase模块提供用于音视频封装、解封装、编解码基础功能的变量、属性以及函数。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
 */

/**
 * @file native_avcodec_base.h
 *
 * @brief 声明用于音视频封装、解封装、编解码基础功能的Native API。
 * @sample [AVCodec](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/BasicFeature/Media/AVCodec)
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avcodec_base.h>
 * @library libnative_media_codecbase.so
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
 */

#ifndef NATIVE_AVCODEC_BASE_H
#define NATIVE_AVCODEC_BASE_H

#include <stdint.h>
#include <stdio.h>
#include "native_avbuffer.h"
#include "native_avmemory.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 为图形接口定义native层对象。
 * @since 9
 */
typedef struct NativeWindow OHNativeWindow;

/**
 * @brief 为音视频编解码接口定义native层对象。
 * @since 9
 */
typedef struct OH_AVCodec OH_AVCodec;

/**
 * @brief 当OH_AVCodec实例运行出错时，会调用来上报具体的错误信息的函数指针。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param codec OH_AVCodec实例。
 * @param errorCode 特定错误代码。
 * @param userData 开发者执行回调所依赖的数据。
 * @since 9
 * @version 1.0
 */
typedef void (*OH_AVCodecOnError)(OH_AVCodec *codec, int32_t errorCode, void *userData);

/**
 * @brief 当视频解码输入码流分辨率或者视频编码输出码流的分辨率发生变化时，调用此函数指针报告新的流描述信息。\n
 * 从API 15开始，支持音频解码时，码流采样率、声道数或者音频采样格式发生变化时，将调用此函数指针报告新的流描述信息，
 * 支持检测此变化的解码格式有：<!--RP3--><!--RP3End-->AAC，FLAC，MP3，VORBIS。\n
 * 需要注意的是，OH_AVFormat指针的生命周期只有在函数指针被调用时才有效，调用结束后禁止继续访问。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param codec OH_AVCodec实例。
 * @param format 新输出流描述信息。
 * @param userData 开发者执行回调所依赖的数据。
 * @since 9
 * @version 1.0
 */
typedef void (*OH_AVCodecOnStreamChanged)(OH_AVCodec *codec, OH_AVFormat *format, void *userData);

/**
 * @brief 当OH_AVCodec在运行过程中需要新的输入数据时，将调用此函数指针，并携带可用的缓冲区来填充新的输入数据。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param codec OH_AVCodec实例。
 * @param index 与新可用的输入缓冲区相对应的索引。
 * @param data 新的可用输入缓冲区。
 * @param userData 开发者执行回调所依赖的数据。
 * @deprecated since 11
 * @useinstead {@link OH_AVCodecOnNeedInputBuffer}
 * @since 9
 * @version 1.0
 */
typedef void (*OH_AVCodecOnNeedInputData)(OH_AVCodec *codec, uint32_t index, OH_AVMemory *data, void *userData);

/**
 * @brief 当OH_AVCodec运行过程中生成新的输出数据时，将调用此函数指针，并携带包含新输出数据的缓冲区。
 * 需要注意的是，OH_AVCodecBufferAttr指针的生命周期仅在调用函数指针时有效，这将禁止调用结束后继续访问。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param codec OH_AVCodec实例。
 * @param index 与新输出缓冲区对应的索引。
 * @param data 包含新输出数据的缓冲区。
 * @param attr 新输出缓冲区的说明。
 * @param userData 开发者执行回调所依赖的数据。
 * @deprecated since 11
 * @useinstead {@link OH_AVCodecOnNewOutputBuffer}
 * @since 9
 * @version 1.0
 */
typedef void (*OH_AVCodecOnNewOutputData)(OH_AVCodec *codec, uint32_t index, OH_AVMemory *data,
                                          OH_AVCodecBufferAttr *attr, void *userData);

/**
 * @brief 当OH_AVCodec在运行过程中需要新的输入数据时，将调用此函数指针，并携带可用的缓冲区来填充新的输入数据。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param codec OH_AVCodec实例。
 * @param index 与新可用的输入缓冲区相对应的索引。
 * @param buffer 新的可用输入缓冲区。
 * @param userData 开发者执行回调所依赖的数据。
 * @since 11
 */
typedef void (*OH_AVCodecOnNeedInputBuffer)(OH_AVCodec *codec, uint32_t index, OH_AVBuffer *buffer, void *userData);

/**
 * @brief 当OH_AVCodec运行过程中生成新的输出数据时，将调用此函数指针，并携带包含新输出数据的缓冲区。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param codec OH_AVCodec实例。
 * @param index 与新输出缓冲区对应的索引。
 * @param buffer 包含新输出数据的缓冲区。
 * @param userData 开发者执行回调所依赖的数据。
 * @since 11
 */
typedef void (*OH_AVCodecOnNewOutputBuffer)(OH_AVCodec *codec, uint32_t index, OH_AVBuffer *buffer, void *userData);

/**
 * @brief OH_AVCodec中所有异步回调函数指针的集合。将该结构体的实例注册到OH_AVCodec实例中，
 * 并处理回调上报的信息，以保证OH_AVCodec的正常运行。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @deprecated since 11
 * @useinstead {@link OH_AVCodecCallback}
 * @since 9
 * @version 1.0
 */
typedef struct OH_AVCodecAsyncCallback {
    /** 监控编解码器操作错误。 */
    OH_AVCodecOnError onError;
    /** 监控编解码器流变化。 */
    OH_AVCodecOnStreamChanged onStreamChanged;
    /** 监控编解码器需要输入数据。 */
    OH_AVCodecOnNeedInputData onNeedInputData;
    /** 监控编解码器已生成输出数据。 */
    OH_AVCodecOnNewOutputData onNeedOutputData;
} OH_AVCodecAsyncCallback;

/**
 * @brief OH_AVCodec中所有异步回调函数指针的集合。将该结构体的实例注册到OH_AVCodec实例中，
 * 并处理回调上报的信息，以保证OH_AVCodec的正常运行。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 11
 */
typedef struct OH_AVCodecCallback {
    /** 监控编解码器操作错误。 */
    OH_AVCodecOnError onError;
    /** 监控编解码器流变化。 */
    OH_AVCodecOnStreamChanged onStreamChanged;
    /** 监控编解码器需要输入数据。 */
    OH_AVCodecOnNeedInputBuffer onNeedInputBuffer;
    /** 监控编解码器已生成输出数据。 */
    OH_AVCodecOnNewOutputBuffer onNewOutputBuffer;
} OH_AVCodecCallback;

/**
 * @brief 函数指针定义，用于提供获取用户自定义媒体数据的能力。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param data 要填充的缓冲区。
 * @param length 要读取的数据长度。
 * @param pos 从偏移量位置读取。
 * @return 读取到缓冲区的数据的实际长度。
 * @since 12
*/
typedef int32_t (*OH_AVDataSourceReadAt)(OH_AVBuffer *data, int32_t length, int64_t pos);

/**
 * @brief 用户自定义数据源。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
*/
typedef struct OH_AVDataSource {
    /**
     * @brief 数据源的总大小。
     */
    int64_t size;
    /**
     * @brief 数据源的数据回调。
     */
    OH_AVDataSourceReadAt readAt;
} OH_AVDataSource;

/**
 * @brief 函数指针定义，用于提供获取用户自定义媒体数据的能力。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param data 要填充的缓冲区。
 * @param length 要读取的数据长度。
 * @param pos 从偏移量位置读取。
 * @param userData 用户自定义数据。
 * @return 读取到缓冲区的数据的实际长度。
 * @since 20
*/
typedef int32_t (*OH_AVDataSourceReadAtExt)(OH_AVBuffer *data, int32_t length, int64_t pos, void *userData);

/**
 * @brief 用户自定义数据源，回调支持通过userData传递用户自定义数据。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
*/
typedef struct OH_AVDataSourceExt {
    /**
     * @brief 数据源的总大小。
     */
    int64_t size;
    /**
     * @brief 数据源的数据回调。
     */
    OH_AVDataSourceReadAtExt readAt;
} OH_AVDataSourceExt;

/* 枚举音频和视频编解码器的MIME类型。 */

/** 
 * @brief AVC(H.264)视频编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
 * @version 1.0
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_AVC;
/**
 * @brief AAC音频编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_AAC;

/* 枚举音频和视频编解码器的MIME类型。 */

/**
 * @brief FLAC音频编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_FLAC;
/**
 * @brief VORBIS音频解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_VORBIS;
/**
 * @brief MP3音频编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_MPEG;
/**
 * @brief HEVC(H.265)视频编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_HEVC;

/* 枚举封装的视频类型。*/

/**
 * @brief MPEG4视频编码的MIME类型，仅用于封装MPEG4视频码流使用。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @deprecated since 11
 * @useinstead {@link OH_AVCODEC_MIMETYPE_VIDEO_MPEG4_PART2}
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_MPEG4;

/**
 * @brief 视频MPEG4 Part2编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 17
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_MPEG4_PART2;

/**
 * @brief 视频MPEG2编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 17
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_MPEG2;

/**
 * @brief H.263视频编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 17
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_H263;

/**
 * @brief VC-1视频编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_VC1;

/**
 * @brief AV1视频编解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_AV1;

/**
 * @brief VP9视频编解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_VP9;

/**
 * @brief VP8视频编解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_VP8;

/**
 * @brief RV30视频编解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_RV30;

/**
 * @brief RV40视频编解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_RV40;

/**
 * @brief WVC1视频编解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_WVC1;

/**
 * @brief DVVIDEO（Digital Video）视频编解码器的MIME类型。支持DV NTSC、DV PAL与DVCPRO HD。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_DVVIDEO;

/**
 * @brief RAWVIDEO视频编解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_RAWVIDEO;

/**
 * @brief MPEG1视频编解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_MPEG1;

/**
 * @brief Cinepak视频编解码器的MIME类型。
 *
 * @since 24
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_CINEPAK;

/**
 * @brief MSVIDEO1（Microsoft Video 1）视频编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_MSVIDEO1;

/**
 * @brief WMV3视频编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_WMV3;

/**
 * @brief MJPEG（Motion JPEG）视频编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_MJPEG;

/* 枚举封装的图片类型。 */

/**
 * @brief JPG图片编码的MIME类型，仅用于封装JPG封面时使用。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_IMAGE_JPG;
/**
 * @brief PNG图片编码的MIME类型，仅用于封装PNG封面时使用。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_IMAGE_PNG;
/**
 * @brief BMP图片编码的MIME类型，仅用于封装BMP封面时使用。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_IMAGE_BMP;

/* 枚举音频编解码器的MIME类型。 */
/**
 * @brief Audio Vivid音频解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 11
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_VIVID;
/**
 * @brief AMR_NB音频解码器的MIME类型。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 11
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_AMR_NB;
/**
 * @brief AMR_WB音频解码器的MIME类型。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 11
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_AMR_WB;
/**
 * @brief OPUS音频编解码器的MIME类型。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 11
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_OPUS;
/**
 * @brief G711MU音频编解码器的MIME类型。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 11
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_G711MU;

/**
 * @brief ALAC（Apple Lossless Audio Codec）音频解码器的MIME类型。
 *
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_ALAC;
/**
 * @brief AC3（Dolby Audio Coding 3）音频解码器的MIME类型。
 *
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_AC3;
/**
 * @brief EAC3（Enhanced AC-3）音频解码器的MIME类型。
 *
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_EAC3;
/**
 * @brief WMA（Windows Media Audio）V1音频解码器的MIME类型。
 *
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_WMAV1;
/**
 * @brief WMA（Windows Media Audio）V2音频解码器的MIME类型。
 *
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_WMAV2;
/**
 * @brief WMA（Windows Media Audio）Pro音频解码器的MIME类型。
 *
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_WMAPRO;
/**
 * @brief 划分音频数据块大小的键，单位为字节，值类型为int32_t。
 *
 * 该键仅用于WMA（V1、V2、PRO）解码器。\n
 * 允许的MIME类型包括{@link OH_AVCODEC_MIMETYPE_AUDIO_WMAV1}，{@link OH_AVCODEC_MIMETYPE_AUDIO_WMAV2}
 * 和{@link OH_AVCODEC_MIMETYPE_AUDIO_WMAPRO}。
 *
 * @since 22
*/
extern const char *OH_MD_KEY_BLOCK_ALIGN;
/**
 * @brief GSM（Global System for Mobile Communications）音频解码器的MIME类型。
 *
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_GSM;
/**
 * @brief GSM MS（Microsoft variant）音频解码器的MIME类型。
 *
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_GSM_MS;

/**
 * @brief TWINVQ（Transform-domain Weighted Interleave Vector Quantization）音频解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_TWINVQ;

/**
 * @brief ILBC（Internet Low Bitrate Codec） 音频解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_ILBC;

/**
 * @brief TRUEHD（True High Definition）音频解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_TRUEHD;

/**
 * @brief DVAUDIO（Digital Video Audio）音频解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_DVAUDIO;

/**
 * @brief DTS（Digital Theater Systems）音频解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_DTS;

/**
 * @brief COOK（RealAudio Cook）音频解码器的MIME类型。
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_COOK;

/**
 * @brief VVC(H.266)视频编解码器的MIME类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_VVC;
/**
 * @brief APE音频解码器的MIME类型。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_APE;
/**
 * @brief SRT字幕解封装器的MIME类型。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_AVCODEC_MIMETYPE_SUBTITLE_SRT;
/**
 * @brief WEBVTT字幕解封装器的MIME类型。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_AVCODEC_MIMETYPE_SUBTITLE_WEBVTT;

/**
 * @brief RAW音频码流的MIME类型。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 18
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_RAW;

/**
 * @brief G711A音频解码器的MIME类型。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_G711A;

/**
 * @brief 表示surfacebuffer时间戳的键，值类型为int64_t。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @deprecated since 14
 * @since 9
 * @version 1.0
 */
extern const char *OH_ED_KEY_TIME_STAMP;
/** 
* @brief 表示surfacebuffer流结束符的键，值类型为int32_t。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @deprecated since 14
 * @since 9
*/
extern const char *OH_ED_KEY_EOS;

/* 提供统一的键，用于存储媒体描述。 */
/**
 * @brief 轨道媒体类型的键，值类型为int32_t，请参见{@link OH_MediaType}。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
 * @version 1.0
 */
extern const char *OH_MD_KEY_TRACK_TYPE;
/**
 * @brief 编解码器MIME类型的键，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_CODEC_MIME;
/**
 * @brief 媒体文件持续时间的键，单位为微秒，值类型为int64_t。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_DURATION;
/**
 * @brief 比特率的键，值类型为int64_t。
 * 可以通过能力查询接口{@link OH_AVCapability_GetEncoderBitrateRange}接口来获取取值范围。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_BITRATE;
/**
 * @brief 设置解码输入码流大小最大值的键，值类型为int32_t。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_MAX_INPUT_SIZE;
/**
 * @brief 视频宽度的键，值类型为int32_t。\n
 * 对于视频编码，该键用于设置目标编码分辨率。对于视频解码，该键是解码器预分配内部缓冲区的分辨率提示。实际解码输出尺寸由OH_MD_KEY_VIDEO_PIC_WIDTH提供。\n
 * 虽然该键主要用于控制内存分配，但可参考{@link OH_AVCapability_GetVideoWidthRange}获取推荐值范围，该接口定义了编码器支持的解码宽度范围。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_WIDTH;
/**
 * @brief 视频高度键，值类型为int32_t。\n
 * 对于视频编码，该键用于设置目标编码分辨率。对于视频解码，该键是解码器预分配内部缓冲区的分辨率提示。实际解码输出尺寸由OH_MD_KEY_VIDEO_PIC_HEIGHT提供。\n
 * 虽然该键主要用于控制内存分配，但可参考{@link OH_AVCapability_GetVideoHeightRange}获取推荐值范围，该接口定义了编解码器支持的解码高度范围。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_HEIGHT;
/**
 * @brief 视频像素格式的键，值类型为int32_t，请参见{@link OH_AVPixelFormat}。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_PIXEL_FORMAT;
/**
 * @brief 音频原始格式的键，值类型为int32_t，请参见{@link OH_BitsPerSample}。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_AUDIO_SAMPLE_FORMAT;
/**
 * @brief 视频帧率的键，值类型为double。该值必须大于 0。
 * 可以通过能力查询接口{@link OH_AVCapability_GetVideoFrameRateRange}来获取取值范围。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_FRAME_RATE;
/**
 * @brief 视频编码码率模式，值类型为int32_t，请参见{@link OH_BitrateMode}。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_VIDEO_ENCODE_BITRATE_MODE;
/**
 * @brief 编码档次，值类型为int32_t，请参见{@link OH_AVCProfile}、{@link OH_HEVCProfile}、{@link OH_AACProfile}。
 * 可以通过能力查询接口{@link OH_AVCapability_GetSupportedProfiles}来获取支持的档次。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_PROFILE;
/**
 * @brief 音频通道计数键，值类型为int32_t。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_AUD_CHANNEL_COUNT;
/**
 * @brief 音频采样率键，值类型为int32_t。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_AUD_SAMPLE_RATE;
/**
 * @brief 关键帧间隔的键，值类型为int32_t，单位为ms。该键是可选的且只用于视频编码。\n
 * 负值表示只有第一帧是关键帧，0表示所有帧都是关键帧，正值表示每(frameRate * 设置值)/1000帧一个关键帧。默认值为1000。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_I_FRAME_INTERVAL;
/**
 * @brief surface旋转角度的键，旋转方向为顺时针。值类型为int32_t，值为{0, 90, 180, 270}，默认值为0。\n
 * 该键只在视频解码Surface模式下使用。\n
 * 设置视频解码surface模式旋转时，推荐使用OH_MD_KEY_VIDEO_TRANSFORM_TYPE键。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
*/
extern const char *OH_MD_KEY_ROTATION;
/**
 * @brief 视频翻转角度的键，值类型为int32_t，请参见{@link OH_NativeBuffer_TransformType}。\n
 *
 * 此键用于设置视频解码surface模式的翻转角度。若未指定，默认值为0 ({@link NATIVEBUFFER_ROTATE_NONE})。\n
 * 此键与{@link OH_MD_KEY_ROTATION}互斥。若两者同时设置，以OH_MD_KEY_VIDEO_TRANSFORM_TYPE为准，推荐使用OH_MD_KEY_VIDEO_TRANSFORM_TYPE键。\n
 * 注意：{@link OH_NativeBuffer_TransformType}中指定的角度表示逆时针旋转，这与{@link OH_MD_KEY_ROTATION}定义的旋转方向相反。\n
 * 对应关系如下:\n
 * - {@link NATIVEBUFFER_ROTATE_NONE}等同于OH_MD_KEY_ROTATION = 0。\n
 * - {@link NATIVEBUFFER_ROTATE_90}等同于OH_MD_KEY_ROTATION = 270。\n
 * - {@link NATIVEBUFFER_ROTATE_180}等同于OH_MD_KEY_ROTATION = 180。\n
 * - {@link NATIVEBUFFER_ROTATE_270}等同于OH_MD_KEY_ROTATION = 90。\n
 *
 * @since 22
 */
extern const char *OH_MD_KEY_VIDEO_TRANSFORM_TYPE;
/* 提供统一的键，用于存储媒体描述。 */
/**
 * @brief 视频YUV值域标志的键，值类型为int32_t，1表示full range，0表示limited range，默认值为0。配置非0值将按照配置1处理，表示full range。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_RANGE_FLAG;
/**
 * @brief 视频色域的键，值类型为int32_t，默认值为COLOR_PRIMARY_UNSPECIFIED。
 * 请参见{@link OH_ColorPrimary}，遵循H.273标准Table2。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_COLOR_PRIMARIES;
/**
 * @brief 视频传递函数的键，值类型为int32_t，默认值为TRANSFER_CHARACTERISTIC_UNSPECIFIED。
 * 请参见{@link OH_TransferCharacteristic}，遵循H.273标准Table3。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_TRANSFER_CHARACTERISTICS;
/**
 * @brief 视频矩阵系数的键，值类型为int32_t，默认值为MATRIX_COEFFICIENT_UNSPECIFIED。
 * 请参见{@link OH_MatrixCoefficient}，遵循H.273标准Table4。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_MATRIX_COEFFICIENTS;
/**
 * @brief 请求立即编码I帧的键。值类型为int32_t。在调用{@link OH_VideoEncoder_SetParameter}阶段使用，或随帧立即生效。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_REQUEST_I_FRAME;
/**
 * @brief 所需编码质量的键。
 *
 * 值类型为int32_t，默认值为50。在H.264、H.265编码场景值范围可以通过能力查询接口{@link OH_AVCapability_GetEncoderQualityRange}来获取取值范围，
 * 此键仅适用于配置在恒定质量模式下的编码器。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_QUALITY;
/**
 * @brief 编解码器特定数据的键，视频中表示传递SPS/PPS，音频中表示传递extraData，值类型为uint8_t\*。 <!--Del-->（视频编解码此功能暂未支持）<!--DelEnd-->
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_CODEC_CONFIG;
/**
 * @brief 媒体文件标题的键，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_TITLE;
/**
 * @brief 媒体文件艺术家的键，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_ARTIST;
/**
 * @brief 专辑的媒体文件的键，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_ALBUM;
/**
 * @brief 专辑艺术家的键，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_ALBUM_ARTIST;
/**
 * @brief 媒体文件日期的键，值类型为char *，例如2024年。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_DATE;
/**
 * @brief 媒体文件注释的键，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_COMMENT;
/**
 * @brief 媒体文件moov元数据是否前置标志，值类型为int32_t, 1表示前置， 0表示不前置, 默认为0。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
*/
extern const char *OH_MD_KEY_ENABLE_MOOV_FRONT;
/**
 * @brief 媒体文件流派的键，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_GENRE;
/**
 * @brief 媒体文件版权的键，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_COPYRIGHT;
/**
 * @brief 媒体文件语言的键，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_LANGUAGE;
/**
 * @brief 媒体文件描述的键，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_DESCRIPTION;
/**
 * @brief 媒体文件歌词的键，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_LYRICS;
/**
 * @brief 媒体文件轨道数量的键，值类型为int32_t。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_TRACK_COUNT;
/**
 * @brief 所需编码通道布局的键。值类型为int64_t，此键仅适用于编码器。请参见{@link OH_AudioChannelLayout}。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_CHANNEL_LAYOUT;
/**
 * @brief 每个编码样本位数的键，值类型为int32_t。\n
 * API 20前，FLAC编码必须设置此参数，设置为1即可；未设置此参数配置FLAC编码器时，调用OH_AudioCodec_Configure会返回错误码AV_ERR_INVALID_VAL。该值无实际作用，不会影响编码结果。\n
 * 从API 20开始，无需设置此参数。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_BITS_PER_CODED_SAMPLE;
/**
 * @brief aac格式的键，aac格式分为ADTS格式和LATM格式。值类型为int32_t，0表示LATM格式，1表示ADTS格式。aac解码器支持。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_AAC_IS_ADTS;
/**
 * @brief aac sbr模式的键，值类型为int32_t，aac编码器支持。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_SBR;
/**
 * @brief flac兼容性等级的键，值类型为int32_t，仅在音频编码使用。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_COMPLIANCE_LEVEL;
/**
 * @brief vorbis标识头的键，值类型为uint8_t*，仅vorbis解码器支持。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_IDENTIFICATION_HEADER;
/**
 * @brief vorbis设置头的键，值类型为uint8_t*，仅vorbis解码器支持。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_KEY_SETUP_HEADER;
/**
 * @brief 视频缩放模式，值类型为int32_t，请参见{@link OH_ScalingMode}。\n
 * 建议直接调用{@link OH_NativeWindow_NativeWindowSetScalingModeV2}接口进行设置。该键是可选的且只用于视频解码Surface模式。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 * @useinstead {@link OH_NativeWindow_NativeWindowSetScalingModeV2}
 * @deprecated since 14
*/
extern const char *OH_MD_KEY_SCALING_MODE;
/**
 * @brief 最大输入缓冲区个数的键，值类型为int32_t。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_MAX_INPUT_BUFFER_COUNT;
/**
 * @brief 最大输出缓冲区个数的键，值类型int32_t。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
*/
extern const char *OH_MD_MAX_OUTPUT_BUFFER_COUNT;

/**
 * @brief 音频编解码压缩水平的键，只在音频编码使用，值类型为int32_t。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 11
 */
extern const char *OH_MD_KEY_AUDIO_COMPRESSION_LEVEL;
/**
 * @brief 媒体文件中的视频轨是否为HDR Vivid的键，支持封装和解封装，值类型为int32_t。\n
 * 1表示是HDR Vivid视频轨，0表示不是HDR Vivid视频轨。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 11
 */
extern const char *OH_MD_KEY_VIDEO_IS_HDR_VIVID;
/**
 * @brief 音频对象数目的键. 值类型为int32_t，该键是可选的且仅用于Audio Vivid编解码器。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 11
 */
extern const char *OH_MD_KEY_AUDIO_OBJECT_NUMBER;
/**
 * @brief Audio Vivid元数据的键，值类型为uint8_t*，该键是可选的且仅用于Audio Vivid编解码器。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 11
 */
extern const char *OH_MD_KEY_AUDIO_VIVID_METADATA;

/**
 * @brief 在视频编码中获取长期参考帧（LTR）的最大个数的键，值类型为int32_t。\n
 * 可以通过{@link OH_AVCapability_GetFeatureProperties}接口和
 * 枚举值{@link OH_AVCapabilityFeature}中的VIDEO_ENCODER_LONG_TERM_REFERENCE来查询这个最大值。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_FEATURE_PROPERTY_KEY_VIDEO_ENCODER_MAX_LTR_FRAME_COUNT;
/**
 * @brief 使能分层编码的键，值类型为int32_t，1表示使能，0表示不使能，默认值为0。配置非0值将按照配置1处理，表示使能。\n
 * 使用前可以通过{@link OH_AVCapability_IsFeatureSupported}接口和枚举值{@link OH_AVCapabilityFeature}中的
 * VIDEO_ENCODER_TEMPORAL_SCALABILITY来查询当前视频编码器是否支持分层编码。\n
 * 该键是可选的且只用于视频编码，在Configure阶段使用。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_ENABLE_TEMPORAL_SCALABILITY;
/**
 * @brief 描述图片组基本层图片的间隔大小的键，值类型为int32_t，只在使能分层编码时生效。\n
 * 该键是可选的且只用于视频编码，在Configure阶段使用。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_TEMPORAL_GOP_SIZE;
/**
 * @brief 描述图片组内参考模式的键，值类型为int32_t，请参见{@link OH_TemporalGopReferenceMode}，只在使能分层编码时生效。\n
 * 该键是可选的且只用于视频编码，在Configure阶段使用。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_TEMPORAL_GOP_REFERENCE_MODE;
/**
 * @brief 描述图像组（GOP）内的时域层号ID键，数据类型为int32_t。\n
 * 时域层号为0时，表示基础层，1及以上时表示增强层，\n
 * 最大时域层号与{@link OH_MD_KEY_VIDEO_ENCODER_TEMPORAL_GOP_REFERENCE_MODE}参数,\n
 * 和{@link OH_MD_KEY_VIDEO_ENCODER_TEMPORAL_GOP_SIZE}相关。\n
 * 该键目前仅用于查询编码器输出的AVBuffer中携带的时域层号。\n
 * 使用流程如下：\n
 * 1. 通过{@link OH_AVCodecOnNewOutputBuffer}接口或{@link OH_VideoEncoder_GetOutputBuffer}获取缓冲区实例（AVBuffer）。\n
 * 2. 通过{@link OH_AVBuffer_GetParameter}获取除基础属性外的其他参数实例（OH_AVFormat）。\n
 * 3. 通过{@link OH_AVFormat_GetIntValue}接口和本键获取对应帧的时域层号。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_TEMPORAL_LAYER_ID;
/**
 * @brief 描述长期参考帧（LTR）个数的键，值类型为int32_t，必须在支持的值范围内使用。\n
 * 使用前可以通过{@link OH_AVCapability_GetFeatureProperties}接口和
 * 枚举值{@link OH_AVCapabilityFeature}中的VIDEO_ENCODER_LONG_TERM_REFERENCE来查询支持的长期参考帧（LTR）数目。\n
 * 该键是可选的且只用于视频编码，在Configure阶段使用。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_LTR_FRAME_COUNT;

/**
 * @brief 标记当前帧为长期参考帧（LTR）的键，值类型为int32_t，
 * 1表示被标记，0表示未被标记，默认值为0。
 * 配置非0值将按照配置1处理，表示被标记。\n
 * 只在长期参考帧（LTR）个数被配置后生效。\n
 * 该键是可选的且只用于视频编码输入轮转中，配置后立即生效。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PER_FRAME_MARK_LTR;

/**
 * @brief 描述当前帧参考的长期参考帧（LTR）的POC号的键，值类型为int32_t。\n
 * 该键是可选的且只用于视频编码输入轮转中，配置后立即生效。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PER_FRAME_USE_LTR;

/**
 * @brief 当前{@link OH_AVBuffer}中输出的码流对应的帧是否为长期参考帧（LTR）的键，
 * 值类型为int32_t，1表示是长期参考帧（LTR），0表示不是长期参考帧（LTR），
 * 默认值为0。配置非0值将按照配置1处理，表示是长期参考帧（LTR）。\n
 * 该键是可选的且只用于视频编码输出轮转中。\n
 * 表示帧的属性。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_PER_FRAME_IS_LTR;

/**
 * @brief 描述帧的POC的键，值类型为int32_t。\n
 * 该键是可选的且只用于视频编码输出轮转中。\n
 * 表示帧的属性。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_PER_FRAME_POC;
/**
 * @brief 描述裁剪矩形顶部坐标(y)值的键，值类型为int32_t。\n
 * 包含裁剪框顶部的行，行索引从0开始。\n
 * 该键只用于视频解码。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_CROP_TOP;
/**
 * @brief 描述裁剪矩形底部坐标(y)值的键，值类型为int32_t。\n
 * 包含裁剪框底部的行，行索引从0开始。\n
 * 该键只用于视频解码。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_CROP_BOTTOM;
/**
 * @brief 描述裁剪矩形左坐标(x)值的键，值类型为int32_t。\n
 * 包含裁剪框最左边的列，列索引从0开始。\n
 * 该键只用于视频解码。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_CROP_LEFT;
/**
 * @brief 描述裁剪矩形右坐标(x)值的键，值类型为int32_t。\n
 * 包含裁剪框最右边的列，列索引从0开始。\n
 * 该键只用于视频解码。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_CROP_RIGHT;
/**
 * @brief 描述视频帧宽跨距的键，值类型为int32_t。\n
 * 宽跨距表示内存中相邻两行数据起始位置之间的字节距离。由于硬件对齐要求，stride通常大于或等于图像有效宽度。当stride等于width，表示无水平填充。
 * 应始终通过OH_VideoEncoder_GetInputDescription（编码）、OH_VideoDecoder_GetOutputDescription（解码）
 * 或OH_AVCodecOnStreamChanged回调中的OH_AVFormat参数获取实际跨距值，而非假设固定值。\n
 * 使用示例详见[视频编码](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/media/
 * avcodec/video-encoding.md#buffer%E6%A8%A1%E5%BC%8F)Buffer模式的步骤8
 * 或[视频解码](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/media/
 * avcodec/video-decoding.md#buffer%E6%A8%A1%E5%BC%8F)Buffer模式的步骤11。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_STRIDE;
/**
 * @brief 描述视频帧高跨距的键，值类型为int32_t。\n
 * 高跨距表示内存中为单个平面分配的总行数。由于硬件对齐要求，sliceHeight通常大于或等于图像有效高度。U平面的起始地址相对于Y平面原点的偏移量为（sliceHeight * stride）。
 * 应始终通过OH_VideoEncoder_GetInputDescription（编码）、OH_VideoDecoder_GetOutputDescription（解码）
 * 或OH_AVCodecOnStreamChanged回调中的OH_AVFormat参数获取实际高跨距值，而非假设固定值。\n
 * 使用示例详见[视频编码](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/media/
 * avcodec/video-encoding.md#buffer%E6%A8%A1%E5%BC%8F)Buffer模式的步骤8
 * 或[视频解码](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/media/
 * avcodec/video-decoding.md#buffer%E6%A8%A1%E5%BC%8F)Buffer模式的步骤11。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_SLICE_HEIGHT;
/**
 * @brief 描述解码后视频帧实际有效宽度的键名。值类型为int32_t。该键为只读，仅用于视频解码。\n
 * 调用{@link OH_VideoDecoder_GetOutputDescription}时，或通过{@link OH_AVCodecOnStreamChanged}回调检测到解码输出流变化时，
 * 可从返回的OH_AVFormat实例中获取该值。该值表示图像有效宽度，与Configure阶段设置的OH_MD_KEY_WIDTH不同，后者是用于预分配缓冲区的配置提示。
 * 当需要获取显示或保存图像的实际宽度时，读取该值。\n
 * 图像排布和使用示例详见[视频编码](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/media/
 * avcodec/video-encoding.md#buffer%E6%A8%A1%E5%BC%8F)Buffer模式的步骤8
 * 或[视频解码](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/media/
 * avcodec/video-decoding.md#buffer%E6%A8%A1%E5%BC%8F)Buffer模式的步骤11。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_PIC_WIDTH;
/**
 * @brief 描述解码后视频帧实际有效高度的键名。值类型为int32_t。该键为只读，仅用于视频解码。\n
 * 调用{@link OH_VideoDecoder_GetOutputDescription}时，或通过{@link OH_AVCodecOnStreamChanged}回调检测到解码输出码流变化时，
 * 可从返回的OH_AVFormat实例中获取该值。该值表示图像有效高度，与Configure阶段设置的OH_MD_KEY_HEIGHT不同，后者是用于预分配缓冲区的配置提示。
 * 当需要获取显示或保存图像的实际高度时，读取该值。\n
 * 图像排布和使用示例详见[视频编码](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/media/
 * avcodec/video-encoding.md#buffer%E6%A8%A1%E5%BC%8F)Buffer模式的步骤8
 * 或[视频解码](https://gitcode.com/openharmony/docs/blob/master/zh-cn/application-dev/media/
 * avcodec/video-decoding.md#buffer%E6%A8%A1%E5%BC%8F)Buffer模式的步骤11。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_PIC_HEIGHT;
/**
 * @brief 使能低时延视频解码的键，值类型为int32_t，1表示使能，0表示不使能，默认值为0。配置非0值将按照配置1处理，表示使能。\n
 * 该键是可选的，在Configure阶段使用。\n
 * 如果使能，则视频解码器持有的输入和输出数据不会超过解码器标准所要求的数量。\n
 * 可以通过能力查询接口{@link OH_AVCapability_IsFeatureSupported}来查询特定解码器是否支持低时延。若解码器支持，使能此接口时，视频解码器将按照解码序输出帧。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENABLE_LOW_LATENCY;
/**
 * @brief 描述视频编码器允许的最大量化参数的键，值类型为int32_t。\n
 * 在Configure/SetParameter阶段使用，或随帧立即生效。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_QP_MAX;
/**
 * @brief 描述视频编码器允许的最小量化参数的键，值类型为int32_t。\n
 * 在Configure/SetParameter阶段使用，或随帧立即生效。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_QP_MIN;
/**
 * @brief 描述视频帧平均量化参数的键，值类型为int32_t。\n
 * 表示当前帧编码块的平均qp值，随{@link OH_AVBuffer}输出。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_QP_AVERAGE;
/**
 * @brief 描述视频帧平方误差的键，值类型为double。\n
 * 表示当前帧编码块的MSE统计值，随{@link OH_AVBuffer}输出。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_MSE;
/**
 * @brief AVBuffer中携带的音视频或字幕的sample对应的解码时间戳的键，以微秒为单位，值类型为int64_t。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_DECODING_TIMESTAMP;
/**
 * @brief AVBuffer中携带的音视频或字幕的sample对应的持续时间的键，以微秒为单位，值类型为int64_t。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_BUFFER_DURATION;
/**
 * @brief 样本长宽比的键，值类型为double。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_SAR;
/**
 * @brief 媒体文件中第一帧起始位置开始时间的键，以微秒为单位，值类型为int64_t。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_START_TIME;
/**
 * @brief 轨道开始时间的键，以微秒为单位，值类型为int64_t。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_TRACK_START_TIME;
/**
 * @brief 设置视频解码器输出色彩空间的键，值类型为int32_t。\n
 * 支持的值为OH_COLORSPACE_BT709_LIMIT，请参见{@link OH_NativeBuffer_ColorSpace}。\n
 * 在视频解码调用{@link OH_VideoDecoder_Configure}接口时使用此接口。\n
 * 在启动OH_VideoDecoder_Start接口前，必须要先调用OH_VideoDecoder_Prepare接口。\n
 * 如果支持色彩空间转换功能并配置了此键，则视频解码器会自动将HDR Vivid视频转码为指定的色彩空间。\n
 * 如果不支持色彩空间转换功能，则接口{@link OH_VideoDecoder_Configure}返回错误码
 * {@link OH_AVErrCode}中的AV_ERR_VIDEO_UNSUPPORTED_COLOR_SPACE_CONVERSION。
 * 如果输入视频不是HDR Vivid视频，则会通过回调函数{@link OH_AVCodecOnError}报告错误
 * {@link OH_AVErrCode}中的AV_ERR_VIDEO_UNSUPPORTED_COLOR_SPACE_CONVERSION。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_OUTPUT_COLOR_SPACE;
/**
 * @brief 解码器是否打开视频可变帧率功能的键，值类型为int32_t。\n
 * 1代表使能视频可变帧率功能，0代表不使能。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 15
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_OUTPUT_ENABLE_VRR;
/**
 * @brief 媒体文件创建时间的元数据，值类型为char *。使用ISO 8601标准的时间格式且为UTC时间，时间格式参考："2024-12-28T00:00:00:000000Z"。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 14
 */
extern const char *OH_MD_KEY_CREATION_TIME;
/**
 * @brief 如果在上一帧提交给编码器之后没有新的帧可用，则会以毫秒为单位重复提交最后一帧，值类型为int32_t。\n
 * 该键只用于视频编码Surface模式，在Configure阶段使用。\n
 * 配置的值：\n
 * - 小于等于0：Configure阶段会被拦截，返回ERROR AV_ERR_INVALID_VAL。\n
 * - 大于0：如果在上一帧提交给编码器之后没有新的帧可用，则会以毫秒为单位重复提交最后一帧。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 18
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_REPEAT_PREVIOUS_FRAME_AFTER;
/**
 * @brief 描述编码器在没有新的帧可用的情况下，可以对之前的帧进行重复编码的最大次数，值类型为int32_t。\n
 * 该键仅在OH_MD_KEY_VIDEO_ENCODER_REPEAT_PREVIOUS_FRAME_AFTER可用时生效，在Configure阶段使用。\n
 * 配置的值：\n
 * - 等于0：Configure阶段会被拦截，返回ERROR AV_ERR_INVALID_VAL。\n
 * - 小于0：在没有新的帧提交给编码器的这段时间内，编码器会一直重复编上一帧，直到达到系统上限。\n
 * - 大于0：在没有新的帧提交给编码器的这段时间内，最多可以重复编码的帧数。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 18
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_REPEAT_PREVIOUS_MAX_COUNT;
/**
 * @brief 使能B帧编码的键，值类型为int32_t（0或1）：1表示使能，0表示不使能。
 *
 * 该键是可选项，仅用于视频编码器，默认值为0。\n
 * 如果使能，视频编码器将使用B帧，解码顺序与显示顺序会不同。\n
 * 对于不支持的平台，配置该键不会生效。\n
 * 可通过{@link OH_AVCapability_IsFeatureSupported}接口和枚举值{@link OH_AVCapabilityFeature}.VIDEO_ENCODER_B_FRAME查询平台能力。\n
 * 该键仅在configure阶段使用。\n
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_ENABLE_B_FRAME;
/**
 * @brief 描述视频编码器支持的最大连续B帧数的键，值类型为int32_t。
 *
 * 注意：该键目前仅用于查询编码器能力。\n
 * 使用规范如下：\n
 * 1. 通过{@link OH_AVCapability_IsFeatureSupported}接口和枚举值{@link OH_AVCapabilityFeature}.VIDEO_ENCODER_B_FRAME
 * 查询特性支持情况。\n
 * 2. 通过{@link OH_AVCapability_GetFeatureProperties}接口和枚举值{@link OH_AVCapabilityFeature}.VIDEO_ENCODER_B_FRAME
 * 获取OH_AVFormat指针。\n
 * 3. 通过{@link OH_AVFormat_GetIntValue}接口和本键获取最大B帧数。\n
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_MAX_B_FRAMES;

/**
 * @brief 用于设置感兴趣区域（ROI）参数的键。
 *     值类型为字符串，格式为"Top1,Left1-Bottom1,Right1[=Params1];Top2,Left2-Bottom2,Right2[=Params2];"。
 *
 * 每个"Top,Left-Bottom,Right"代表一个ROI的坐标信息。
 * "[=Params]"是可选的。
 * "[=Params]"的格式随版本变化：
 * - 在API版本26.0.0之前：仅支持单个代表量化参数偏移量的int32_t值（例如，"=Offset"）。
 * - 从API版本26.0.0开始：额外支持并推荐使用键值对（Key-Value）格式。
 * 参数使用逗号分隔的键值对（例如，"=dqp:-6,slb:1"）。
 * 支持的键包括：
 * - "dqp"：量化参数偏移量。
 * - "slb"：语义标签。该值必须与{@link OH_VideoMetadataRoiSemanticLabel}对应。
 *
 * 如果完全省略"=Params"，例如 "Top1,Left1-Bottom1,Right1;Top2,Left2-Bottom2,Right2=dqp:-6;"，
 * 编码器将使用默认参数对第一个ROI进行ROI编码，并使用指定的参数对第二个ROI进行编码。
 * 请注意，可同时应用的ROI数量不得超过6个，且总面积不得超过图像面积的1/5。
 *
 * 这是一个仅适用于视频编码器的可选键，在运行过程中按帧设置并生效。
 * 在Surface模式下，它用于{@link OH_VideoEncoder_OnNeedInputParameter}。
 * 在Buffer模式下，通过{@link OH_AVBuffer_SetParameter}进行配置。
 *
 * @note 从API版本26.0.0开始，推荐使用{@link OH_VideoMetadata_AppendRoiString}
 * 来安全地格式化和追加ROI配置，而不是手动拼接字符串。
 * @since 20
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_ROI_PARAMS;

/**
 * @brief 指定SQR码控模式的质量参数，取值范围为[0, 51]（同编码量化参数QP），值越小，编码输出码率越大，质量越好。\n
 * 在Configure/SetParameter阶段使用。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
 */
extern const char *OH_MD_KEY_SQR_FACTOR;
/**
 * @brief 指定SQR码控模式的最大码率，使用{@link OH_AVCapability_GetEncoderBitrateRange}方法获取取值范围（同OH_MD_KEY_BITRATE），
 * 单位bps，值类型为int64_t。\n
 * 在Configure/SetParameter阶段使用。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
 */
extern const char *OH_MD_KEY_MAX_BITRATE;
/**
 * @brief 使能基于显示时间戳(PTS)的码控模式的键，值类型为int32_t，1表示使能，0表示不使能，默认值为0。配置非0值将按照配置1处理，表示使能。\n
 *
 * 该键值是可选的且只用于视频编码。\n
 * 如果使能，则必须在每个视频帧中携带PTS信息，并发送到编码器。
 * Surface模式下，通过{@link OH_NativeWindow_NativeWindowHandleOpt}接口设置PTS，时间单位为纳秒(ns)；
 * Buffer模式下，通过{@link OH_AVBuffer_SetBufferAttr}接口设置PTS，时间单位为微秒(us)。\n
 * 在Configure阶段使用。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_ENABLE_PTS_BASED_RATECONTROL;
/**
 * @brief 媒体文件轨道间参考、被参考关系，值类型为int32_t*。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
*/
extern const char *OH_MD_KEY_REFERENCE_TRACK_IDS;
/**
 * @brief 媒体文件辅助轨类型，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
*/
extern const char *OH_MD_KEY_TRACK_REFERENCE_TYPE;
/**
 * @brief 媒体文件辅助轨描述信息，值类型为char *。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
*/
extern const char *OH_MD_KEY_TRACK_DESCRIPTION;
/**
 * @brief 使能音视频编解码同步模式的键，值类型为int32_t，1表示使能，0表示不使能，默认值为0。配置非0值将按照配置1处理，表示使能。该键是可选。\n
 *
 * 如果使能，需要注意：\n
 * 1. 编解码器不可设置回调函数。\n
 * 2. 必须使用缓冲区查询接口替代回调。\n
 * 3. 只能在Configure阶段使用。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
 */
extern const char *OH_MD_KEY_ENABLE_SYNC_MODE;
/**
 * @brief 用于指定视频解码器关闭时是否输出空白帧的键，值类型为int32_t，1表示使能，0表示不使能，默认值为0。配置非0值将按照配置1处理，表示使能。
 * 该键是可选的且仅用于视频解码Surface模式。\n
 * 使能后，调用{@OH_VideoDecoder_Stop}接口或者{@OH_VideoDecoder_Destroy}接口时，视频解码器将输出空白帧（通常为黑色）。
 * 该机制可避免因解码器突然终止导致的显示残留。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_BLANK_FRAME_ON_SHUTDOWN;
/**
 * @brief 用于查询视频编解码中native buffer像素格式的键，值类型为int32_t。\n
 * 具体取值请参见{@link OH_NativeBuffer_Format}中定义的像素格式。
 * 
 * 该键主要用于以下两种场景：\n
 * 1. 视频解码：调用{@link OH_VideoDecoder_GetOutputDescription}接口或
 *    {@link OH_AVCodecOnStreamChanged}，从返回的OH_AVFormat对象中获取当前输出格式。\n
 * 2. 视频编码：调用{@link OH_VideoEncoder_GetInputDescription}接口，
 *    从返回的OH_AVFormat对象中获取当前输入格式。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 22
 */
extern const char *OH_MD_KEY_VIDEO_NATIVE_BUFFER_FORMAT;

/**
 * @brief OH_AVBuffer中携带的键，仅解封装支持。在解封装输出音频的起始、末尾帧可能携带此键。\n
 * 此键对应一个10字节的uint8_t[]类型的数组，记录的是音频文件元数据中解码后需跳过的音频采样点数。\n
 *
 * 具体结构如下：\n
 * 1. 数组0~3，这4个字节表示从当前帧第一个采样点开始往后跳过的采样点数，以小端序存储uint32_t值。\n
 * 2. 数组4~7，这4个字节表示从当前帧最后一个采样点开始往前跳过的采样点数（不大于1帧采样点数），以小端序存储uint32_t值。\n
 * 3. 数组8~9，这2个字节表示保留位，默认输出为0。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 23
 */
extern const char *OH_MD_KEY_BUFFER_SKIP_SAMPLES_INFO;

/**
 * @brief 在音频解码器中使能OH_MD_KEY_BUFFER_SKIP_SAMPLES_INFO功能的键，值类型为int32_t。
 * 1表示使能，0表示不使能，默认值为0。配置非1值将按照配置0处理，表示不使能。\n
 * 该键是可选的。仅用于音频解码器。
 *
 * @since 24
 */
extern const char *OH_MD_KEY_ENABLE_BUFFER_SKIP_SAMPLES;

/**
 * @brief 纬度的键，值类型为float，范围为[-90.0, 90.0]。
 * 表示地理位置信息中的纬度。
 *
 * @since 24
 */
extern const char *OH_MD_KEY_LATITUDE;

/**
 * @brief 经度的键, 值类型为float，范围为[-180.0, 180.0]。
 * 表示地理位置信息中的经度。
 *
 * @since 24
 */
extern const char *OH_MD_KEY_LONGITUDE;

/**
 * @brief 海拔的键, 值类型为float。
 * 该键是可选的。表示地理位置信息中的海拔。
 *
 * @since 24
 */
extern const char *OH_MD_KEY_ALTITUDE;

/**
 * @brief 视频编码器待处理帧数量的键值，值类型为int32_t。
 *
 * 该键是只读的，用于查询当前待编码帧的数量。
 * 可通过{@link OH_VideoEncoder_GetInputDescription}接口获取。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_NUMBER_OF_PENDING_FRAMES;

/**
 * @brief 解码器输出模式的键值。值类型为int32_t，取值为0或1。
 * 1表示解码器按解码顺序输出帧；0表示解码器按显示顺序输出帧，默认值为0。
 *
 * 该键是可选的，仅用于视频解码，且仅可在Configure阶段使用。
 * 设置该键前，可通过{@link OH_AVCapability_IsFeatureSupported}接口和枚举值
 * {@link OH_AVCapabilityFeature}.VIDEO_DECODER_OUTPUT_IN_DECODING_ORDER查询是否支持该特性。
 * 如果视频解码不支持该特性，通过{@link OH_VideoDecoder_Configure}接口设置该键将返回{@link AV_ERR_INVALID_VAL}。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_OUTPUT_IN_DECODING_ORDER;

/**
 * @brief 视频编码器在输出压缩帧前允许缓存的最大帧数的键值。
 * 值类型为int32_t，取值范围为[1，5]。
 *
 * 该键是可选的，仅用于视频编码，且仅可在Configure阶段使用。
 * 取值在[1，5]区间内时可正常生效；若超出该范围（小于1或大于5），调用{@link OH_VideoEncoder_Configure}接口会返回{@link AV_ERR_INVALID_VAL}。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_MAX_FRAME_DELAY_COUNT;

/**
 * @brief 码流同步帧前置参数集的键值。
 * 值类型为int32_t，取值为0或1，1表示使能，0表示不使能，默认值为0。
 *
 * 该键是可选的，仅用于视频编码，且仅可在Configure阶段使用。
 * 开启后，编码器会在每个同步帧前插入前置参数集数据（例如H.264/H.265格式对应的SPS、PPS）。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_REPEAT_HEADER_BEFORE_SYNC_FRAMES;

/**
 * @brief 设置Audio Vivid输入信号格式的键，值类型为int32_t，该键仅用于Audio Vivid编码器。\n
 * 具体取值请参见{@link OH_AudioVividSignalFormat}。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_AUDIO_VIVID_SIGNAL_FORMAT;

/**
 * @brief 设置音频声床的通道布局的键，值类型为int64_t，该键是可选的且仅用于Audio Vivid编码器。\n
 * 具体取值请参见{@link OH_AudioChannelLayout}。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_AUDIO_SOUNDBED_LAYOUT;

/**
 * @brief 设置音频声床编码比特率的键，值类型为int64_t，该键是可选的且仅用于Audio Vivid编码器。\n
 * 实际编码比特率可能会根据编码器的能力调整。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_AUDIO_SOUNDBED_BITRATE;

/**
 * @brief 设置音频对象编码比特率的键，值类型为int64_t，该键是可选的且仅用于Audio Vivid编码器。\n
 * 实际编码比特率可能会根据编码器的能力调整。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_AUDIO_OBJECT_BITRATE;

/**
 * @brief 设置或查询音频编码器最大输入缓冲区大小的键。单位为字节（Byte），值类型为int32_t。
 *
 * 该键用于配置或获取音频编码器输入缓冲区的最大值。
 * 实际缓冲区大小受编码器实现限制，设置超过编码器最大支持的值时不会生效。
 * 该配置为可选项，如果不设置，编码器将使用默认的缓冲区大小。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_AUDIO_MAX_INPUT_BUFFER_SIZE;

/**
 * @brief 配置音频编码器PTS（Presentation Time Stamp，显示时间戳）输出模式的键。
 *
 * 设置PTS输出行为模式，值类型为int32_t，请参见{@link OH_AudioEncoderPTSMode}。
 * 该键为可选项，如果不设置，默认值为{@link OH_AUDIO_ENCODER_PTS_MODE_DEFAULT}。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_AUDIO_ENCODER_PTS_MODE;

/**
 * @brief 使能音频编码器采样格式转换的键。
 * 值类型为int32_t，取值为0或1，1表示使能，0表示不使能，默认值为0。
 *
 * 音频编码器仅支持有限的采样格式。使能此配置后，如果使用了不支持的采样格式，音频编码器会将采样格式
 * 转换为支持的格式后进行编码。转换前支持的采样格式如下：{@link SAMPLE_U8}、{@link SAMPLE_S16LE}、
 * {@link SAMPLE_S24LE}、{@link SAMPLE_S32LE}、{@link SAMPLE_F32LE}。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_AUDIO_ENCODER_ENABLE_SAMPLE_FORMAT_CONVERT;

/**
 * @brief 视频编码前处理降采样目标宽度的键，值类型为int32_t。\n
 *
 * 该键是可选的，降采样功能默认关闭。该键与OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_HEIGHT必须同时配置，当都设置为0时则关闭降采样功能，
 * 可以通过{@link OH_AVCapability_IsVideoSizeSupported}查询支持的降采样宽高范围。降采样参数与裁剪参数互斥，降采样功能与裁剪功能不可同时启用。\n
 * 该键仅用于支持前处理的视频编码器或一入二出编码场景，可在Configure阶段配置或通过SetParameter运行时动态调整。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_WIDTH;

/**
 * @brief 视频编码前处理降采样目标高度的键，值类型为int32_t。\n
 *
 * 该键是可选的，降采样功能默认关闭。该键与OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_WIDTH必须同时配置，当都设置为0时则关闭降采样功能，
 * 可以通过{@link OH_AVCapability_IsVideoSizeSupported}查询支持的降采样宽高范围。降采样参数与裁剪参数互斥，降采样功能与裁剪功能不可同时启用。\n
 * 该键仅用于支持前处理的视频编码器或一入二出编码场景，可在Configure阶段配置或通过SetParameter运行时动态调整。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_HEIGHT;

/**
 * @brief 视频编码前处理裁剪区域左边坐标（x）的键，值类型为int32_t。\n
 *
 * 该键是可选的，裁剪功能默认关闭。OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_LEFT/TOP/RIGHT/BOTTOM 4个参数必须同时配置，当全部设置为0时则关闭裁剪功能，
 * 默认坐标原点为输入视频帧左上角(0, 0)，坐标取值不可超过输入视频帧宽高，且需满足(0, 0) <= (LEFT, TOP) < (RIGHT, BOTTOM) < (输入视频帧宽度，输入视频帧高度)。
 * 降采样参数与裁剪参数互斥，降采样功能与裁剪功能不可同时启用。\n
 * 该键仅用于支持前处理的视频编码器或一入二出编码场景，可在Configure阶段配置或通过SetParameter运行时动态调整。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_LEFT;

/**
 * @brief 视频编码前处理裁剪区域顶部坐标（y）的键，值类型为int32_t。\n
 *
 * 该键是可选的，裁剪功能默认关闭。OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_LEFT/TOP/RIGHT/BOTTOM 4个参数必须同时配置，当全部设置为0时则关闭裁剪功能，
 * 默认坐标原点为输入视频帧左上角(0, 0)，坐标取值不可超过输入视频帧宽高，且需满足(0, 0) <= (LEFT, TOP) < (RIGHT, BOTTOM) < (输入视频帧宽度，输入视频帧高度)。
 * 降采样参数与裁剪参数互斥，降采样功能与裁剪功能不可同时启用。\n
 * 该键仅用于支持前处理的视频编码器或一入二出编码场景，可在Configure阶段配置或通过SetParameter运行时动态调整。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_TOP;

/**
 * @brief 视频编码前处理裁剪区域右边坐标（x）的键，值类型为int32_t。\n
 *
 * 该键是可选的，裁剪功能默认关闭。OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_LEFT/TOP/RIGHT/BOTTOM 4个参数必须同时配置，当全部设置为0时则关闭裁剪功能，
 * 默认坐标原点为输入视频帧左上角(0, 0)，坐标取值不可超过输入视频帧宽高，且需满足(0, 0) <= (LEFT, TOP) < (RIGHT, BOTTOM) < (输入视频帧宽度，输入视频帧高度)。
 * 降采样参数与裁剪参数互斥，降采样功能与裁剪功能不可同时启用。\n
 * 该键仅用于支持前处理的视频编码器或一入二出编码场景，可在Configure阶段配置或通过SetParameter运行时动态调整。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_RIGHT;

/**
 * @brief 视频编码前处理裁剪区域底部坐标（y）的键，值类型为int32_t。\n
 *
 * 该键是可选的，裁剪功能默认关闭。OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_LEFT/TOP/RIGHT/BOTTOM 4个参数必须同时配置，当全部设置为0时则关闭裁剪功能，
 * 默认坐标原点为输入视频帧左上角(0, 0)，坐标取值不可超过输入视频帧宽高，且需满足(0, 0) <= (LEFT, TOP) < (RIGHT, BOTTOM) < (输入视频帧宽度，输入视频帧高度)。
 * 降采样参数与裁剪参数互斥，降采样功能与裁剪功能不可同时启用。\n
 * 该键仅用于支持前处理的视频编码器或一入二出编码场景，可在Configure阶段配置或通过SetParameter运行时动态调整。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_BOTTOM;

/**
 * @brief 视频编码前处理丢帧目标帧率的键，值类型为double，数值精度保留2位小数。\n
 *
 * 该键是可选的，丢帧功能默认关闭。当设置0.00时则关闭丢帧功能，配置值时自动四舍五入保留两位小数。可独立使用，也可与降采样或裁剪组合使用。\n
 * 该键仅用于支持前处理的视频编码器或一入二出编码场景，可在Configure阶段配置或通过SetParameter运行时动态调整。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_DROP_TO_FRAME_RATE;

/**
 * @brief 媒体类型。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
 * @version 1.0
 */
typedef enum OH_MediaType {
    /** 音频轨。*/
    MEDIA_TYPE_AUD = 0,
    /** 视频轨。 */
    MEDIA_TYPE_VID = 1,
    /**
     * @brief 字幕轨。
     * @since 12
     */
    MEDIA_TYPE_SUBTITLE = 2,
     /** 
     * @brief timed metadata轨。
     * @since 20
     */
    MEDIA_TYPE_TIMED_METADATA = 5,
    /** 
     * @brief 辅助轨。
     * @since 20
     */
    MEDIA_TYPE_AUXILIARY = 6,
} OH_MediaType;

/**
 * @brief AAC档次。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
 * @version 1.0
 */
typedef enum OH_AACProfile {
    /** AAC编码档次为Low Complexity级别。*/
    AAC_PROFILE_LC = 0,
    /**
     * @brief AAC编码档次为High Efficiency级别。包含音频对象类型：AAC LC和SBR。
     * @since 14
     */
    AAC_PROFILE_HE = 3,
    /**
     * @brief AAC编码档次为High Efficiency v2级别。包含音频对象类型：AAC LC、SBR和PS。
     * @since 14
     */
    AAC_PROFILE_HE_V2 = 4,
} OH_AACProfile;

/**
 * @brief AVC档次。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
 * @version 1.0
 */
typedef enum OH_AVCProfile {
    /** AVC编码档次为基本档次。*/
    AVC_PROFILE_BASELINE = 0,
    /** AVC编码档次为高档次。*/
    AVC_PROFILE_HIGH = 4,
    /** AVC编码档次为主档次。*/
    AVC_PROFILE_MAIN = 8,
} OH_AVCProfile;

/**
 * @brief HEVC档次。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
typedef enum OH_HEVCProfile {
    /** HEVC编码档次为主档次。*/
    HEVC_PROFILE_MAIN = 0,
    /** HEVC编码档次为10bit主档次。*/
    HEVC_PROFILE_MAIN_10 = 1,
    /** HEVC编码档次为静止图像主档次。*/
    HEVC_PROFILE_MAIN_STILL = 2,
    /**
     * @brief HEVC编码档次为HDR10主档次。
     * @deprecated since 14
     */
    HEVC_PROFILE_MAIN_10_HDR10 = 3,
    /**
     * @brief HEVC编码档次为HDR10+主档次。
     * @deprecated since 14
     */
    HEVC_PROFILE_MAIN_10_HDR10_PLUS = 4,
} OH_HEVCProfile;

/**
 * @brief VVC档次。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 15
 */
typedef enum OH_VVCProfile {
    /** VVC编码档次为10bit主档次。 */
    VVC_PROFILE_MAIN_10 = 1,
    /** VVC编码档次为12bit主档次。 */
    VVC_PROFILE_MAIN_12 = 2,
    /** VVC编码档次为12bit帧内主档次。 */
    VVC_PROFILE_MAIN_12_INTRA = 10,
    /** VVC编码档次为多层编码10bit主档次。 */
    VVC_PROFILE_MULTI_MAIN_10 = 17,
    /** VVC编码档次为10bit全采样主档次。 */
    VVC_PROFILE_MAIN_10_444 = 33,
    /** VVC编码档次为12bit全采样主档次。 */
    VVC_PROFILE_MAIN_12_444 = 34,
    /** VVC编码档次为16bit全采样主档次。 */
    VVC_PROFILE_MAIN_16_444 = 36,
    /** VVC编码档次为12bit全采样帧内主档次。 */
    VVC_PROFILE_MAIN_12_444_INTRA = 42,
    /** VVC编码档次为16bit全采样帧内主档次。 */
    VVC_PROFILE_MAIN_16_444_INTRA = 44,
    /** VVC编码档次为多层编码10bit全采样主档次。 */
    VVC_PROFILE_MULTI_MAIN_10_444 = 49,
    /** VVC编码档次为10bit静止图像主档次。 */
    VVC_PROFILE_MAIN_10_STILL = 65,
    /** VVC编码档次为12bit静止图像主档次。 */
    VVC_PROFILE_MAIN_12_STILL = 66,
    /** VVC编码档次为10bit全采样静止图像主档次。 */
    VVC_PROFILE_MAIN_10_444_STILL = 97,
    /** VVC编码档次为12bit全采样静止图像主档次。 */
    VVC_PROFILE_MAIN_12_444_STILL = 98,
    /** VVC编码档次为16bit全采样静止图像主档次。 */
    VVC_PROFILE_MAIN_16_444_STILL = 100,
} OH_VVCProfile;

/**
 * @brief MPEG2档次。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 17
 */
typedef enum OH_MPEG2Profile {
    /** 简单档次。 */
    MPEG2_PROFILE_SIMPLE = 0,
    /** 主档次。 */
    MPEG2_PROFILE_MAIN  = 1,
    /** 信噪比可分级档次。 */
    MPEG2_PROFILE_SNR_SCALABLE  = 2,
    /** 空间可分级档次。 */
    MPEG2_PROFILE_SPATIALLY_SCALABLE = 3,
    /** 高级档次。 */
    MPEG2_PROFILE_HIGH = 4,
    /** 4:2:2档次。 */
    MPEG2_PROFILE_422 = 5,
} OH_MPEG2Profile;

/**
 * @brief MPEG4档次。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 17
 */
typedef enum OH_MPEG4Profile {
    /** 简单档次。 */
    MPEG4_PROFILE_SIMPLE = 0,
    /** 简单可分级档次。 */
    MPEG4_PROFILE_SIMPLE_SCALABLE = 1,
    /** 核心档次。 */
    MPEG4_PROFILE_CORE = 2,
    /** 主档次。 */
    MPEG4_PROFILE_MAIN = 3,
    /** N位档次。 */
    MPEG4_PROFILE_N_BIT  = 4,
    /** 混合档次。 */
    MPEG4_PROFILE_HYBRID = 5,
    /** 基本动画纹理档次。 */
    MPEG4_PROFILE_BASIC_ANIMATED_TEXTURE = 6,
    /** 可分级纹理档次。 */
    MPEG4_PROFILE_SCALABLE_TEXTURE = 7,
    /** 简单FA档次。 */
    MPEG4_PROFILE_SIMPLE_FA = 8,
    /** 高级实时简单档次。 */
    MPEG4_PROFILE_ADVANCED_REAL_TIME_SIMPLE = 9,
    /** 核心可分级档次。 */
    MPEG4_PROFILE_CORE_SCALABLE = 10,
    /** 高级编码效率档次。 */
    MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY = 11,
    /** 高级核心档次。 */
    MPEG4_PROFILE_ADVANCED_CORE = 12,
    /** 高级可分级纹理档次。 */
    MPEG4_PROFILE_ADVANCED_SCALABLE_TEXTURE = 13,
    /** 高级简单档次。 */
    MPEG4_PROFILE_ADVANCED_SIMPLE = 17,
} OH_MPEG4Profile;

/**
 * @brief H.263档次。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 17
 */
typedef enum OH_H263Profile {
    /** 基线档次。 */
    H263_PROFILE_BASELINE = 0,
    /** 版本1向后兼容档次。 */
    H263_PROFILE_VERSION_1_BACKWARD_COMPATIBILITY = 2,
} OH_H263Profile;

/**
 * @brief VC-1档次。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 22
 */
typedef enum OH_VC1Profile {
    /** @brief 简单档次。  */
    VC1_PROFILE_SIMPLE = 0,
    /** @brief 主档次。 */
    VC1_PROFILE_MAIN = 1,
    /** @brief 高级档次。*/
    VC1_PROFILE_ADVANCED = 2,
} OH_VC1Profile;

/**
 * @brief AV1档次。
 *
 * @since 23
 */
typedef enum OH_AV1Profile {
    /** 主档次。 */
    AV1_PROFILE_MAIN = 0,
    /** 高级档次。 */
    AV1_PROFILE_HIGH = 1,
    /** 专业档次。 */
    AV1_PROFILE_PROFESSIONAL = 2,
} OH_AV1Profile;

/**
* @brief VP9档次。
*
* @since 23
*/
typedef enum OH_VP9Profile {
    /** 0档次。 */
    VP9_PROFILE_0 = 0,
    /** 1档次。 */
    VP9_PROFILE_1 = 1,
    /** 2档次。 */
    VP9_PROFILE_2 = 2,
    /** 3档次。 */
    VP9_PROFILE_3 = 3,
} OH_VP9Profile;

/**
* @brief WVC1档次。
*
* @since 23
*/
typedef enum OH_WVC1Profile {
    /** 高级档次。 */
    WVC1_PROFILE_ADVANCED = 0,
 } OH_WVC1Profile;

/**
 * @brief WMV3档次。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 22
 */
typedef enum OH_WMV3Profile {
    /** @brief 简单档次。 */
    WMV3_PROFILE_SIMPLE = 0,
    /** @brief 主档次。*/
    WMV3_PROFILE_MAIN = 1,
} OH_WMV3Profile;

/**
 * @brief 封装器支持的输出文件格式。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
typedef enum OH_AVOutputFormat {
    /** 输出文件格式默认值，默认为MP4格式。*/
    AV_OUTPUT_FORMAT_DEFAULT = 0,
    /** 输出文件格式为MP4格式。*/
    AV_OUTPUT_FORMAT_MPEG_4 = 2,
    /** 输出文件格式为M4A格式。*/
    AV_OUTPUT_FORMAT_M4A = 6,
	/**
     * @brief 输出文件格式为AMR格式。
     * @since 12
     */
    AV_OUTPUT_FORMAT_AMR = 8,
	/**
     * @brief 输出文件格式为MP3格式。
     * @since 12
     */
    AV_OUTPUT_FORMAT_MP3 = 9,
    /**
     * @brief 输出文件格式为WAV格式。
     * @since 12
     */
    AV_OUTPUT_FORMAT_WAV = 10,
    /**
     * @brief 输出文件格式为AAC格式。
     * @since 18
     */
    AV_OUTPUT_FORMAT_AAC = 11,
    /**
     * @brief 输出文件格式为FLAC格式。
     * @since 20
     */
    AV_OUTPUT_FORMAT_FLAC = 12,
    /**
     * @brief 输出文件格式为OGG格式。
     * @since 23
     */
    AV_OUTPUT_FORMAT_OGG = 13,
    /**
     * @brief 输出文件格式为FLV格式。
     * @since 26.0.0
     */
    AV_OUTPUT_FORMAT_FLV = 14,
} OH_AVOutputFormat;

/**
 * @brief 跳转模式。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
typedef enum OH_AVSeekMode {
    /** 指定时间位置的下一I帧。若时间点后没有I帧，该模式可能跳转失败。 */
    SEEK_MODE_NEXT_SYNC = 0,
    /** 指定时间位置的上一I帧。 */
    SEEK_MODE_PREVIOUS_SYNC,
    /** 指定时间位置的最近I帧。 */
    SEEK_MODE_CLOSEST_SYNC,
} OH_AVSeekMode;

/**
 * @brief 缩放模式，只在Surface模式下使用。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @deprecated since 14
 * @useinstead {@link OHScalingModeV2}
 * @since 10
 */
typedef enum OH_ScalingMode {
    /**
     * @brief 根据窗口尺寸自适应调整图像大小。
     * @deprecated since 14
     * @useinstead {@link OH_SCALING_MODE_SCALE_TO_WINDOW_V2}
    */
    SCALING_MODE_SCALE_TO_WINDOW = 1,
    /** 
     * 根据窗口尺寸裁剪图像大小。
     * @deprecated since 14
     * @useinstead {@link OH_SCALING_MODE_SCALE_CROP_V2}
    */
    SCALING_MODE_SCALE_CROP = 2,
} OH_ScalingMode;

/**
 * @brief 每个编码样本的音频位数。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
typedef enum OH_BitsPerSample {
    /** 8位无符号整数采样。 */
    SAMPLE_U8 = 0,
    /** 16位有符号整数交样。 */
    SAMPLE_S16LE = 1,
    /** 24位有符号整数采样。 */
    SAMPLE_S24LE = 2,
    /** 32位有符号整数采样。 */
    SAMPLE_S32LE = 3,
    /** 32位浮点采样。 */
    SAMPLE_F32LE = 4,
    /** 8位无符号整数平面采样。 */
    SAMPLE_U8P = 5,
    /** 16位有符号整数平面采样。 */
    SAMPLE_S16P = 6,
    /** 24位有符号整数平面采样。 */
    SAMPLE_S24P = 7,
    /** 32位有符号整数平面采样。 */
    SAMPLE_S32P = 8,
    /** 32位浮点平面采样。 */
    SAMPLE_F32P = 9,
    /** 无效采样格式。 */
    INVALID_WIDTH = -1
} OH_BitsPerSample;

/**
 * @brief 色域。编解码都支持。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
typedef enum OH_ColorPrimary {
    /** BT709色域。 */
    COLOR_PRIMARY_BT709 = 1,
    /** 未指定色域。 */
    COLOR_PRIMARY_UNSPECIFIED = 2,
    /** BT470_M色域。 */
    COLOR_PRIMARY_BT470_M = 4,
    /** BT601_625色域。 */
    COLOR_PRIMARY_BT601_625 = 5,
    /** BT601_525色域。 */
    COLOR_PRIMARY_BT601_525 = 6,
    /** SMPTE_ST240色域。 */
    COLOR_PRIMARY_SMPTE_ST240 = 7,
    /** GENERIC_FILM色域。 */
    COLOR_PRIMARY_GENERIC_FILM = 8,
    /** BT2020色域。 */
    COLOR_PRIMARY_BT2020 = 9,
    /** SMPTE_ST428色域。 */
    COLOR_PRIMARY_SMPTE_ST428 = 10,
    /** P3DCI色域。 */
    COLOR_PRIMARY_P3DCI = 11,
    /** P3D65色域。 */
    COLOR_PRIMARY_P3D65 = 12,
} OH_ColorPrimary;

/**
 * @brief 转移特性。编解码都支持。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
typedef enum OH_TransferCharacteristic {
    /** BT709传递函数。 */
    TRANSFER_CHARACTERISTIC_BT709 = 1,
    /** 未指定传递函数。 */
    TRANSFER_CHARACTERISTIC_UNSPECIFIED = 2,
    /** GAMMA_2_2传递函数。 */
    TRANSFER_CHARACTERISTIC_GAMMA_2_2 = 4,
    /** GAMMA_2_8传递函数。 */
    TRANSFER_CHARACTERISTIC_GAMMA_2_8 = 5,
    /** BT601传递函数。 */
    TRANSFER_CHARACTERISTIC_BT601 = 6,
    /** SMPTE_ST240传递函数。 */
    TRANSFER_CHARACTERISTIC_SMPTE_ST240 = 7,
    /** LINEAR传递函数。 */
    TRANSFER_CHARACTERISTIC_LINEAR = 8,
    /** LOG传递函数。 */
    TRANSFER_CHARACTERISTIC_LOG = 9,
    /** LOG_SQRT传递函数。 */
    TRANSFER_CHARACTERISTIC_LOG_SQRT = 10,
    /** IEC_61966_2_4传递函数。 */
    TRANSFER_CHARACTERISTIC_IEC_61966_2_4 = 11,
    /** BT1361传递函数。 */
    TRANSFER_CHARACTERISTIC_BT1361 = 12,
    /** IEC_61966_2_1传递函数。 */
    TRANSFER_CHARACTERISTIC_IEC_61966_2_1 = 13,
    /** BT2020_10BIT传递函数。 */
    TRANSFER_CHARACTERISTIC_BT2020_10BIT = 14,
    /** BT2020_12BIT传递函数。 */
    TRANSFER_CHARACTERISTIC_BT2020_12BIT = 15,
    /** PQ传递函数。 */
    TRANSFER_CHARACTERISTIC_PQ = 16,
    /** SMPTE_ST428传递函数。 */
    TRANSFER_CHARACTERISTIC_SMPTE_ST428 = 17,
    /** HLG传递函数。 */
    TRANSFER_CHARACTERISTIC_HLG = 18,
} OH_TransferCharacteristic;

/**
 * @brief 矩阵系数。编解码都支持。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
typedef enum OH_MatrixCoefficient {
    /** 单位矩阵。 */
    MATRIX_COEFFICIENT_IDENTITY = 0,
    /** BT709转换矩阵。 */
    MATRIX_COEFFICIENT_BT709 = 1,
    /** 未指定转换矩阵。 */
    MATRIX_COEFFICIENT_UNSPECIFIED = 2,
    /** FCC转换矩阵。 */
    MATRIX_COEFFICIENT_FCC = 4,
    /** BT601_625转换矩阵。 */
    MATRIX_COEFFICIENT_BT601_625 = 5,
    /** BT601_525转换矩阵。 */
    MATRIX_COEFFICIENT_BT601_525 = 6,
    /** SMPTE_ST240转换矩阵。 */
    MATRIX_COEFFICIENT_SMPTE_ST240 = 7,
    /** YCGCO转换矩阵。 */
    MATRIX_COEFFICIENT_YCGCO = 8,
    /** BT2020_NCL转换矩阵。 */
    MATRIX_COEFFICIENT_BT2020_NCL = 9,
    /** BT2020_CL转换矩阵。 */
    MATRIX_COEFFICIENT_BT2020_CL = 10,
    /** SMPTE_ST2085转换矩阵。 */
    MATRIX_COEFFICIENT_SMPTE_ST2085 = 11,
    /** CHROMATICITY_NCL转换矩阵。 */
    MATRIX_COEFFICIENT_CHROMATICITY_NCL = 12,
    /** CHROMATICITY_CL转换矩阵。 */
    MATRIX_COEFFICIENT_CHROMATICITY_CL = 13,
    /** ICTCP转换矩阵。 */
    MATRIX_COEFFICIENT_ICTCP = 14,
} OH_MatrixCoefficient;

/**
 * @brief AVC级别。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
typedef enum OH_AVCLevel {
	/** 级别1 */
    AVC_LEVEL_1 = 0,
	/** 级别1b */
    AVC_LEVEL_1b = 1,
	/** 级别1.1 */
    AVC_LEVEL_11 = 2,
	/** 级别1.2 */
    AVC_LEVEL_12 = 3,
	/** 级别1.3 */
    AVC_LEVEL_13 = 4,
	/** 级别2 */
    AVC_LEVEL_2 = 5,
	/** 级别2.1 */
    AVC_LEVEL_21 = 6,
	/** 级别2.2 */
    AVC_LEVEL_22 = 7,
	/** 级别3 */
    AVC_LEVEL_3 = 8,
	/** 级别3.1 */
    AVC_LEVEL_31 = 9,
	/** 级别3.2 */
    AVC_LEVEL_32 = 10,
	/** 级别4 */
    AVC_LEVEL_4 = 11,
	/** 级别4.1 */
    AVC_LEVEL_41 = 12,
	/** 级别4.2 */
    AVC_LEVEL_42 = 13,
	/** 级别5 */
    AVC_LEVEL_5 = 14,
	/** 级别5.1 */
    AVC_LEVEL_51 = 15,
    /** 级别5.2 */
    AVC_LEVEL_52 = 16,
	/** 级别6 */
    AVC_LEVEL_6 = 17,
	/** 级别6.1 */
    AVC_LEVEL_61 = 18,
    /** 级别6.2 */
    AVC_LEVEL_62 = 19,
} OH_AVCLevel;

/**
 * @brief HEVC级别。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
typedef enum OH_HEVCLevel {
	/** 级别1 */
    HEVC_LEVEL_1 = 0,
	/** 级别2 */
    HEVC_LEVEL_2 = 1,
	/** 级别2.1 */
    HEVC_LEVEL_21 = 2,
	/** 级别3 */
    HEVC_LEVEL_3 = 3,
	/** 级别3.1 */
    HEVC_LEVEL_31 = 4,
	/** 级别4 */
    HEVC_LEVEL_4 = 5,
	/** 级别4.1 */
    HEVC_LEVEL_41 = 6,
	/** 级别5 */
    HEVC_LEVEL_5 = 7,
	/** 级别5.1 */
    HEVC_LEVEL_51 = 8,
	/** 级别5.2 */
    HEVC_LEVEL_52 = 9,
	/** 级别6 */
    HEVC_LEVEL_6 = 10,
	/** 级别6.1 */
    HEVC_LEVEL_61 = 11,
	/** 级别6.2 */
    HEVC_LEVEL_62 = 12,
} OH_HEVCLevel;

/**
 * @brief VVC级别。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 15
 */
typedef enum OH_VVCLevel {
	/** 级别1.0 */
    VVC_LEVEL_1 = 16,
    /** 级别2.0 */
    VVC_LEVEL_2 = 32,
    /** 级别2.1 */
    VVC_LEVEL_21 = 35,
    /** 级别3.0 */
    VVC_LEVEL_3 = 48,
    /** 级别3.1 */
    VVC_LEVEL_31 = 51,
    /** 级别4.0 */
    VVC_LEVEL_4 = 64,
    /** 级别4.1 */
    VVC_LEVEL_41 = 67,
    /** 级别5.0 */
    VVC_LEVEL_5 = 80,
    /** 级别5.1 */
    VVC_LEVEL_51 = 83,
    /** 级别5.2 */
    VVC_LEVEL_52 = 86,
    /** 级别6.0 */
    VVC_LEVEL_6 = 96,
    /** 级别6.1 */
    VVC_LEVEL_61 = 99,
    /** 级别6.2 */
    VVC_LEVEL_62 = 102,
    /** 级别6.3 */
    VVC_LEVEL_63 = 105,
    /** 级别15.5 */
    VVC_LEVEL_155 = 255,
} OH_VVCLevel;

/**
 * @brief MPEG2级别。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 17
 */
typedef enum OH_MPEG2Level {
    /** 低级别。 */
    MPEG2_LEVEL_LOW = 0,
    /** 主级别。 */
    MPEG2_LEVEL_MAIN = 1,
    /** 高1440级别。 */
    MPEG2_LEVEL_HIGH_1440 = 2,
    /** 高级别。 */
    MPEG2_LEVEL_HIGH = 3,
} OH_MPEG2Level;

/**
 * @brief MPEG4级别。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 17
 */
typedef enum OH_MPEG4Level {
    /** 级别0 */
    MPEG4_LEVEL_0  = 0,
    /** 级别0B。  */
    MPEG4_LEVEL_0B = 1,
    /** 级别1。  */
    MPEG4_LEVEL_1  = 2,
    /** 级别2。  */
    MPEG4_LEVEL_2  = 3,
    /** 级别3。  */
    MPEG4_LEVEL_3  = 4,
    /** 级别3B。  */
    MPEG4_LEVEL_3B = 5,
    /** 级别4。 */
    MPEG4_LEVEL_4  = 6,
    /** 级别4A。 */
    MPEG4_LEVEL_4A = 7,
    /** 级别5。 */
    MPEG4_LEVEL_5  = 8,
    /** 级别6。 */
    MPEG4_LEVEL_6  = 9,
}OH_MPEG4Level;

/**
 * @brief H.263级别。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 17
 */
typedef enum OH_H263Level {
    /** 级别10。 */
    H263_LEVEL_10 = 0,
    /** 级别20。 */
    H263_LEVEL_20 = 1,
    /** 级别30。 */
    H263_LEVEL_30 = 2,
    /** 级别40。 */
    H263_LEVEL_40 = 3,
    /** 级别45。 */
    H263_LEVEL_45 = 4,
    /** 级别50。 */
    H263_LEVEL_50 = 5,
    /** 级别60。 */
    H263_LEVEL_60 = 6,
    /** 级别70。 */
    H263_LEVEL_70 = 7,
} OH_H263Level;

/**
 * @brief VC-1级别。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 22
 */
typedef enum OH_VC1Level {
    /** @brief 级别L0。 */
    VC1_LEVEL_L0 = 0,
    /** @brief 级别L1。*/
    VC1_LEVEL_L1 = 1,
    /** @brief 级别L2。 */
    VC1_LEVEL_L2 = 2,
    /** @brief 级别L3。 */
    VC1_LEVEL_L3 = 3,
    /** @brief 级别L4。 */
    VC1_LEVEL_L4 = 4,
    /** @brief 低级别。 */
    VC1_LEVEL_LOW = 5,
    /** @brief 中级别。 */
    VC1_LEVEL_MEDIUM = 6,
    /** @brief 高级别。 */
    VC1_LEVEL_HIGH = 7,
} OH_VC1Level;

/**
 * @brief AV1级别。
 *
 * @since 23
 */
typedef enum OH_AV1Level {
    /** 2.0级别。 */
    AV1_LEVEL_20 = 0,
    /** 2.1级别。 */
    AV1_LEVEL_21 = 1,
    /** 2.2级别。 */
    AV1_LEVEL_22 = 2,
    /** 2.3级别。 */
    AV1_LEVEL_23 = 3,
    /** 3.0级别。 */
    AV1_LEVEL_30 = 4,
    /** 3.1级别。 */
    AV1_LEVEL_31 = 5,
    /** 3.2级别。 */
    AV1_LEVEL_32 = 6,
    /** 3.3级别。 */
    AV1_LEVEL_33 = 7,
    /** 4.0级别。 */
    AV1_LEVEL_40 = 8,
    /** 4.1级别。 */
    AV1_LEVEL_41 = 9,
    /** 4.2级别。 */
    AV1_LEVEL_42 = 10,
    /** 4.3级别。 */
    AV1_LEVEL_43 = 11,
    /** 5.0级别。 */
    AV1_LEVEL_50 = 12,
    /** 5.1级别。 */
    AV1_LEVEL_51 = 13,
    /** 5.2级别。 */
    AV1_LEVEL_52 = 14,
    /** 5.3级别。 */
    AV1_LEVEL_53 = 15,
    /** 6.0级别。 */
    AV1_LEVEL_60 = 16,
    /** 6.1级别。 */
    AV1_LEVEL_61 = 17,
    /** 6.2级别。 */
    AV1_LEVEL_62 = 18,
    /** 6.3级别。 */
    AV1_LEVEL_63 = 19,
    /** 7.0级别。 */
    AV1_LEVEL_70 = 20,
    /** 7.1级别。 */
    AV1_LEVEL_71 = 21,
    /** 7.2级别。 */
    AV1_LEVEL_72 = 22,
    /** 7.3级别。 */
    AV1_LEVEL_73 = 23,
} OH_AV1Level;

/**
 * @brief VP9级别。
 *
 * @since 23
 */
typedef enum OH_VP9Level {
    /** 1级别。 */
    VP9_LEVEL_1 = 0,
    /** 1.1级别。 */
    VP9_LEVEL_11 = 1,
    /** 2级别。 */
    VP9_LEVEL_2 = 2,
    /** 2.1级别。 */
    VP9_LEVEL_21 = 3,
    /** 3级别。 */
    VP9_LEVEL_3 = 4,
    /** 3.1级别。 */
    VP9_LEVEL_31 = 5,
    /** 4级别。 */
    VP9_LEVEL_4 = 6,
    /** 4.1级别。 */
    VP9_LEVEL_41 = 7,
    /** 5级别。 */
    VP9_LEVEL_5 = 8,
    /** 5.1级别。 */
    VP9_LEVEL_51 = 9,
    /** 5.2级别。 */
    VP9_LEVEL_52 = 10,
    /** 6级别。 */
    VP9_LEVEL_6 = 11,
    /** 6.1级别。 */
    VP9_LEVEL_61 = 12,
    /** 6.2级别。 */
    VP9_LEVEL_62 = 13,
} OH_VP9Level;

/**
 * @brief WVC1级别。
 *
 * @since 23
 */
typedef enum OH_WVC1Level {
    /** L0级别。 */
    WVC1_LEVEL_L0 = 0,
    /** L1级别。 */
    WVC1_LEVEL_L1 = 1,
    /** L2级别。 */
    WVC1_LEVEL_L2 = 2,
    /** L3级别。 */
    WVC1_LEVEL_L3 = 3,
    /** L4级别。 */
    WVC1_LEVEL_L4 = 4,
} OH_WVC1Level;

/**
 * @brief WMV3级别。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 22
 */
typedef enum OH_WMV3Level {
    /** @brief 低级别。 */
    WMV3_LEVEL_LOW = 0,
    /** @brief 中级别。 */
    WMV3_LEVEL_MEDIUM = 1,
    /** @brief 高级别。 */
    WMV3_LEVEL_HIGH = 2,
} OH_WMV3Level;

/**
 * @brief 时域图片组参考模式。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
typedef enum OH_TemporalGopReferenceMode {
    /** 参考最近的短期参考帧。 */
    ADJACENT_REFERENCE = 0,
    /** 参考最近的长期参考帧。 */
    JUMP_REFERENCE = 1,
    /** 均匀分层参考结构，在丢弃最高层级视频帧后，视频帧均匀分布。其中时域图片组个数必须为2的幂。 */
    UNIFORMLY_SCALED_REFERENCE = 2,
} OH_TemporalGopReferenceMode;

/**
 * @brief 编码器的比特率模式。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
typedef enum OH_BitrateMode {
    /** 恒定比特率模式。 */
    BITRATE_MODE_CBR = 0,
    /** 可变比特率模式。 */
    BITRATE_MODE_VBR = 1,
    /** 恒定质量模式。 */
    BITRATE_MODE_CQ = 2,
    /**
     * @brief 质量稳定模式，仅支持H265（HEVC）。
     * @since 20
     */
    BITRATE_MODE_SQR = 3,
    /**
     * @brief 高质量恒定比特率模式，仅支持H265（HEVC）。
     * @since 26.0.0
     */
    BITRATE_MODE_CBR_HIGH_QUALITY = 4
} OH_BitrateMode;

/**
 * @brief 设置视频解码帧保留模式的键。取值类型为int32_t。
 *
 * 该值表示在{@link OH_FrameRetentionMode}中定义的帧保留模式。
 * 每种模式的详细说明及其行为请参考枚举定义OH_FrameRetentionMode。\n
 * 可以通过{@link OH_VideoDecoder_Configure}和{@link OH_VideoDecoder_SetParameter}接口进行配置。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_FRAME_RETENTION_MODE;

/**
 * @brief 设置视频解码帧保留比例的键。取值类型为double。
 *
 * 当{@link OH_MD_KEY_VIDEO_DECODER_FRAME_RETENTION_MODE}设置为
 * {@link OH_FrameRetentionMode#OH_FRAME_RETENTION_MODE_UNIFORM}时，
 * 或者未配置保留模式（隐式默认走到均匀逻辑）时，该参数生效。\n
 * 仅当保留模式显式设置为{@link OH_FrameRetentionMode#OH_FRAME_RETENTION_MODE_ADAPTIVE}
 * 或{@link OH_FrameRetentionMode#OH_FRAME_RETENTION_MODE_FULL}时，此配置才会被忽略。\n
 * 有效范围是[0.01, 1.0]（其中1.0表示保留所有帧，0.01为最小限制），
 * 任何超出此范围的值都将被视为无效并被忽略。\n
 * 可以通过{@link OH_VideoDecoder_Configure}和{@link OH_VideoDecoder_SetParameter}接口进行配置。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_FRAME_RETENTION_RATIO;

/**
 * @brief 配置视频解码器播放倍速的键。取值类型为double。
 *
 * 该键用于指定视频的目标播放倍速。主要推荐与
 * {@link OH_FrameRetentionMode#OH_FRAME_RETENTION_MODE_ADAPTIVE}模式结合使用，
 * 以辅助感知自适应算法准确评估丢帧对视觉感知的影响。\n
 * 取值必须严格大于0.0，推荐的标准值包括0.5、0.75、1.0（正常速度）、1.25、1.5、2.0 和 3.0，
 * 任何小于或等于0.0的值都会被视为无效。\n
 * 可以通过{@link OH_VideoDecoder_Configure}和{@link OH_VideoDecoder_SetParameter}接口进行配置。
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_SPEED;

/**
 * @brief 视频解码帧保留模式。
 *
 * @since 26.0.0
 */
typedef enum OH_FrameRetentionMode {
    /**
     * @brief 全量保留模式。解码器工作在透明直通状态，100%保留所有输入帧，
     * 实质上禁用了抽帧功能。所有底层的视觉感知算法将被完全跳过，实现零算法开销。
     * @since 26.0.0
     */
    OH_FRAME_RETENTION_MODE_FULL = 0,
    /**
     * @brief 感知自适应保留模式。解码器动态分析视频特征，优先丢弃对视觉感知影响最小的帧，
     * 在最小化播放体验损失的同时保持视觉平滑度。为了获得最佳的算法准确性，
     * 强烈建议通过{@link OH_MD_KEY_VIDEO_DECODER_SPEED}显式配置当前的播放倍速。
     * @since 26.0.0
     */
    OH_FRAME_RETENTION_MODE_ADAPTIVE = 1,
    /**
     * @brief 平滑定比保留模式。根据用户配置的保留比例（通过{@link OH_MD_KEY_VIDEO_DECODER_FRAME_RETENTION_RATIO}配置）
     * 均匀地保留视频帧。如果没有显式配置保留比例，解码器默认将输出限制在最高30fps。
     * @since 26.0.0
     */
    OH_FRAME_RETENTION_MODE_UNIFORM = 2
} OH_FrameRetentionMode;

/**
 * @brief 音频编码器PTS模式。
 *
 * @since 26.0.0
 */
typedef enum OH_AudioEncoderPTSMode {
    /**
     * @brief 音频编码器默认PTS模式，不同编码器可能有不同表现。
     *
     * @since 26.0.0
     */
    OH_AUDIO_ENCODER_PTS_MODE_DEFAULT = 0,
    /**
     * @brief 以0为起点的PTS模式。
     *
     * @since 26.0.0
     */
    OH_AUDIO_ENCODER_PTS_MODE_ZERO_START = 1,
    /**
     * @brief 以首个输入帧的PTS值为起点的PTS模式。
     *
     * @since 26.0.0
     */
    OH_AUDIO_ENCODER_PTS_MODE_FIRST_INPUT_START = 2
} OH_AudioEncoderPTSMode;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVCODEC_BASE_H
/** @} */
