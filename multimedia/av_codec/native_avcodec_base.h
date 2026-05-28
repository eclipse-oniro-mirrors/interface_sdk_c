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
 * @addtogroup CodecBase
 * @{
 *
 * @brief The CodecBase module provides variables, properties, and functions
 * for audio and video muxer, demuxer, and basic encoding and decoding functions.
 * 
 * @since 9
 */

/**
 * @file native_avcodec_base.h
 *
 * @brief Declare the Native API used for audio and video muxer,
 * demuxer and basic encoding and decoding functions.
 * 
 * @kit AVCodecKit
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
 * @brief Describes a native object for the graphics interface.
 * 
 * @since 9
 */
typedef struct NativeWindow OHNativeWindow;

/**
 * @brief Describes a native object for the audio and video codec interface.
 * 
 * @since 9
 */
typedef struct OH_AVCodec OH_AVCodec;

/**
 * @brief Defines the pointer to the function that is called to report error information when an error occurs during
 * the running of an OH_AVCodec instance.
 * 
 * | Use Case| Error Code|
 * | -------- | -------- |
 * | Audio encoding/decoding| **AV_ERR_DRM_DECRYPT_FAILED**: DRM decryption failed. |
 * | Video encoding/decoding| **AV_ERROR_NO_MEMORY**: System resources are insufficient.<br>**AV_ERROR_UNKNOWN**: An unknown error occurs. Analyze the error based on specific logs.<br>**AV_ERR_SERVICE_DIED**: The service is dead. |
 * | Video decoding| **AV_ERR_VIDEO_UNSUPPORTED_COLOR_SPACE_CONVERSION**: The current input does not support CSC. |
 * <!--RP1--><!--RP1End-->
 * 
 * @param codec Pointer to an OH_AVCodec instance.
 * @param errorCode Error code.
 * @param userData Pointer to the data on which the caller depends when executing the callback.
 * @since 9
 */
typedef void (*OH_AVCodecOnError)(OH_AVCodec *codec, int32_t errorCode, void *userData);

/**
 * @brief Defines the pointer to the function that is called to report the new stream description when the resolution
 * of the input video stream being decoded or the output video stream that has been encoded changes.
 *
 * Starting from API version 15, this function pointer is called to report the new stream description when the stream
 * sampling rate, number of audio channels, or audio sampling format changes during audio decoding. The decoding
 * formats that can detect these changes include <!--RP3--><!--RP3End-->AAC, FLAC, MP3, and VORBIS.
 *
 * Note that the lifecycle of the pointer to the OH_AVFormat instance is valid only when the function pointer is being
 * called. Do not access the pointer to the instance after the function pointer is called.
 * 
 * @param codec Pointer to an OH_AVCodec instance.
 * @param format Pointer to the description information about the new output stream.
 * @param userData Pointer to the data on which the caller depends when executing the callback.
 * @since 9
 */
typedef void (*OH_AVCodecOnStreamChanged)(OH_AVCodec *codec, OH_AVFormat *format, void *userData);

/**
 * @brief Defines the pointer to the function that is called when new input data is required during the running of an
 * OH_AVCodec instance. The function carries a buffer to fill in new input data.
 * 
 * @param codec Pointer to an OH_AVCodec instance.
 * @param index Index of the new input buffer.
 * @param data Pointer to the data to fill in the new input buffer.
 * @param userData Pointer to the data on which the caller depends when executing the callback.
 * @deprecated since 11
 * @useinstead OH_AVCodecOnNeedInputBuffer
 * @since 9
 */
typedef void (*OH_AVCodecOnNeedInputData)(OH_AVCodec *codec, uint32_t index, OH_AVMemory *data, void *userData);

/**
 * @brief Defines the pointer to the function that is called when new output data is generated during the running of an
 * OH_AVCodec instance. The function carries a buffer filled with new output data. Note that the lifecycle of the
 * pointer to the OH_AVCodecBufferAttr instance is valid only when the function pointer is being called. Do not access
 * the pointer to the instance after the function pointer is called.
 * 
 * @param codec Pointer to an OH_AVCodec instance.
 * @param index Index of the new output buffer.
 * @param data Pointer to the data filled in the new output buffer.
 * @param attr Pointer to the description information about the new output buffer.
 * @param userData Pointer to the data on which the caller depends when executing the callback.
 * @deprecated since 11
 * @useinstead OH_AVCodecOnNewOutputBuffer
 * @since 9
 */
typedef void (*OH_AVCodecOnNewOutputData)(OH_AVCodec *codec, uint32_t index, OH_AVMemory *data,
                                          OH_AVCodecBufferAttr *attr, void *userData);

/**
 * @brief Defines the pointer to the function that is called when new input data is required during the running of an
 * OH_AVCodec instance. The function carries a buffer to fill in new input data.
 * 
 * @param codec Pointer to an OH_AVCodec instance.
 * @param index Index of the new input buffer.
 * @param buffer Pointer to the data to fill in the new input buffer.
 * @param userData Pointer to the data on which the caller depends when executing the callback.
 * @since 11
 */
typedef void (*OH_AVCodecOnNeedInputBuffer)(OH_AVCodec *codec, uint32_t index, OH_AVBuffer *buffer, void *userData);

/**
 * @brief Defines the pointer to the function that is called when new output data is generated during the running of an
 * OH_AVCodec instance. The function carries a buffer filled with new output data.
 * 
 * @param codec Pointer to an OH_AVCodec instance.
 * @param index Index of the new output buffer.
 * @param buffer Pointer to the data filled in the new output buffer.
 * @param userData Pointer to the data on which the caller depends when executing the callback.
 * @since 11
 */
typedef void (*OH_AVCodecOnNewOutputBuffer)(OH_AVCodec *codec, uint32_t index, OH_AVBuffer *buffer, void *userData);

/**
 * @brief The struct defines all the asynchronous callback function pointers of an OH_AVCodec instance. To ensure the
 * normal running of OH_AVCodec, you must register the instance of this struct with the OH_AVCodec instance and process
 * the information reported by the callback function.
 * 
 * @param onError Monitor OH_AVCodec operation errors, refer to {@link OH_AVCodecOnError}
 * @param onStreamChanged Monitor codec stream information, refer to {@link OH_AVCodecOnStreamChanged}
 * @param onNeedInputData Monitoring codec requires input data, refer to {@link OH_AVCodecOnNeedInputData}
 * @param onNeedOutputData Monitor codec to generate output data, refer to {@link OH_AVCodecOnNewOutputData}
 * @deprecated since 11
 * @useinstead OH_AVCodecCallback
 * @since 9
 */
typedef struct OH_AVCodecAsyncCallback {
    OH_AVCodecOnError onError;
    OH_AVCodecOnStreamChanged onStreamChanged;
    OH_AVCodecOnNeedInputData onNeedInputData;
    OH_AVCodecOnNewOutputData onNeedOutputData;
} OH_AVCodecAsyncCallback;

/**
 * @brief The struct defines all the asynchronous callback function pointers of an OH_AVCodec instance. To ensure the
 * normal running of OH_AVCodec, you must register the instance of this struct with the OH_AVCodec instance and process
 * the information reported by the callback function.
 * 
 * @param onError Monitor OH_AVCodec operation errors, refer to {@link OH_AVCodecOnError}
 * @param onStreamChanged Monitor codec stream information, refer to {@link OH_AVCodecOnStreamChanged}
 * @param onNeedInputBuffer Monitoring codec requires input buffer, refer to {@link OH_AVCodecOnNeedInputBuffer}
 * @param onNewOutputBuffer Monitor codec to generate output buffer, refer to {@link OH_AVCodecOnNewOutputBuffer}
 * @since 11
 */
typedef struct OH_AVCodecCallback {
    OH_AVCodecOnError onError;
    OH_AVCodecOnStreamChanged onStreamChanged;
    OH_AVCodecOnNeedInputBuffer onNeedInputBuffer;
    OH_AVCodecOnNewOutputBuffer onNewOutputBuffer;
} OH_AVCodecCallback;

/**
 * @brief Defines a function pointer used to provide the capability of obtaining user-defined media data.
 * 
 * @param data Pointer to the buffer to be filled in.
 * @param length Length of the data to read.
 * @param pos Offset from which the data is read.
 * @return Actual length of the data read to the buffer.
 * @since 12
 */
typedef int32_t (*OH_AVDataSourceReadAt)(OH_AVBuffer *data, int32_t length, int64_t pos);

/**
 * @brief The struct describes a user-defined data source.
 *
 * @since 12
 */
typedef struct OH_AVDataSource {
    /**
     * Size of the data source.
     * @since 12
     */
    int64_t size;
    /**
     * Callback of the data source.
     * @since 12
     */
    OH_AVDataSourceReadAt readAt;
} OH_AVDataSource;

/**
 * @brief Defines a function pointer used to provide the capability of obtaining user-defined media data.
 * 
 * @param data Pointer to the buffer to be filled in.
 * @param length Length of the data to read.
 * @param pos Offset from which the data is read.
 * @param userData Pointer to user-defined data.
 * @return Actual length of the data read to the buffer.
 * @since 20
 */
typedef int32_t (*OH_AVDataSourceReadAtExt)(OH_AVBuffer *data, int32_t length, int64_t pos, void *userData);

/**
 * @brief The struct describes a user-defined data source. User-defined data can be passed to its callback functions
 * through the **userData** parameter.
 *
 * @since 20
 */
typedef struct OH_AVDataSourceExt {
    /**
     * Size of the data source.
     * @since 20
     */
    int64_t size;
    /**
     * Callback of the data source.
     * @since 20
     */
    OH_AVDataSourceReadAtExt readAt;
} OH_AVDataSourceExt;

/**
 * @brief Pointer to the key that describes the MIME type of the AVC (H.264) video codec.
 * 
 * @since 9
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_AVC;

/**
 * @brief Pointer to the key that describes the MIME type of the AAC audio codec.
 * 
 * @since 9
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_AAC;

/**
 * @brief Pointer to the key that describes the MIME type of the FLAC audio codec.
 * 
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_FLAC;

/**
 * @brief Pointer to the key that describes the MIME type of the Vorbis audio decoder.
 * 
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_VORBIS;

/**
 * @brief Pointer to the key that describes the MIME type of the MP3 audio codec.
 * 
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_MPEG;

/**
 * @brief Pointer to the key that describes the MIME type of the HEVC (H.265) video codec.
 * 
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_HEVC;

/**
 * @brief Pointer to the key that describes the MIME type of the MPEG4 video encoder, which is used only for
 * multiplexing MPEG4 video streams.
 * 
 * @deprecated since 11
 * @useinstead OH_AVCODEC_MIMETYPE_VIDEO_MPEG4_PART2
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_MPEG4;

/**
 * @brief Pointer to the key that describes the MIME type of the JPG image encoder, which is used only for multiplexing
 * JPG covers.
 * 
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_IMAGE_JPG;

/**
 * @brief Pointer to the key that describes the MIME type of the PNG image encoder, which is used only for multiplexing
 * PNG covers.
 * 
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_IMAGE_PNG;

/**
 * @brief Pointer to the key that describes the MIME type of the BMP image encoder, which is used only for multiplexing
 * BMP covers.
 * 
 * @since 10
 */
extern const char *OH_AVCODEC_MIMETYPE_IMAGE_BMP;

/**
 * @brief Pointer to the key that describes the MIME type of the Audio Vivid audio codec.
 * 
 * @since 11
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_VIVID;

/**
 * @brief Pointer to the key that describes the MIME type of the AMR-NB audio <!--RP4--><!--RP4End--> decoder.
 * 
 * @since 11
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_AMR_NB;

/**
 * @brief Pointer to the key that describes the MIME type of the AMR-WB audio <!--RP4--><!--RP4End--> decoder.
 * 
 * @since 11
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_AMR_WB;

/**
 * @brief Pointer to the key that describes the MIME type of the Opus audio codec.
 * 
 * @since 11
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_OPUS;

/**
 * @brief Pointer to the key that describes the MIME type of the G.711 mu-law audio codec.
 * 
 * @since 11
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_G711MU;

/**
 * @brief Pointer to the key that describes the MIME type of the APE audio decoder.
 * 
 * @since 12
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_APE;

/**
 * @brief Pointer to the key that describes the MIME type of the VVC (H.266) video codec.
 * 
 * @since 12
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_VVC;

/**
 * @brief Pointer to the key that describes the MIME type of the SRT subtitle demuxer.
 * 
 * @since 12
 */
extern const char *OH_AVCODEC_MIMETYPE_SUBTITLE_SRT;

/**
 * @brief Pointer to the key that describes the MIME type of the WEBVTT subtitle demuxer.
 * 
 * @since 12
 */
extern const char *OH_AVCODEC_MIMETYPE_SUBTITLE_WEBVTT;

/**
 * @brief Pointer to the key that describes the MIME type of raw audio streams.
 * 
 * @since 18
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_RAW;

/**
 * @brief Pointer to the key that describes the MIME type of the G.711 a-law audio decoder.
 * 
 * @since 20
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_G711A;

/**
 * @brief Pointer to the key that describes the MIME type of the Apple Lossless Audio Codec (ALAC) audio decoder.
 * 
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_ALAC;

/**
 * @brief Pointer to the key that describes the MIME type of the Dolby Audio Coding 3 (AC 3) audio decoder.
 * 
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_AC3;

/**
 * @brief Pointer to the key that describes the MIME type of the Enhanced AC-3 (EAC3) audio decoder.
 * 
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_EAC3;

/**
 * @brief Pointer to the key that describes the MIME type of the Windows Media Audio (WMA) V1 audio decoder.
 * 
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_WMAV1;

/**
 * @brief Pointer to the key that describes the MIME type of the WMA V2 audio decoder.
 * 
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_WMAV2;

/**
 * @brief Pointer to the key that describes the MIME type of the WMA Pro audio decoder.
 * 
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_WMAPRO;

/**
 * @brief Size of the audio data block, in bytes. The value type is int32_t. This key is used only for WMA (V1, V2, and
 * PRO) decoders.
 *
 * The allowed MIME types include **OH_AVCODEC_MIMETYPE_AUDIO_WMAV1**, **OH_AVCODEC_MIMETYPE_AUDIO_WMAV2**, and **
 * OH_AVCODEC_MIMETYPE_AUDIO_WMAPRO**.
 * 
 * @since 22
 */
extern const char *OH_MD_KEY_BLOCK_ALIGN;

/**
 * @brief Pointer to the key that describes the MIME type of the Global System for Mobile Communications (GSM) audio
 * decoder.
 * 
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_GSM;

/**
 * @brief Pointer to the key that describes the MIME type of the GSM Microsoft variant (MS) audio decoder.
 * 
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_GSM_MS;

/**
 * @brief Pointer to the key that describes the MIME type of the Transform-domain Weighted Interleave Vector
 * Quantization (TWINVQ) audio decoder.
 * 
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_TWINVQ;

/**
 * @brief Pointer to the key that describes the MIME type of the Internet Low Bitrate Codec (ILBC) audio decoder.
 *
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_ILBC;

/**
 * @brief Pointer to the key that describes the MIME type of the True High Definition (TRUEHD) audio decoder.
 * 
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_TRUEHD;

/**
 * @brief MIME type of the DVAUDIO (Digital Video Audio) audio decoder.
 * 
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_DVAUDIO;

/**
 * @brief MIME type of the DTS (Digital Theater Systems) audio decoder.
 * 
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_DTS;

/**
 * @brief MIME type of the Cook (RealAudio Cook) audio decoder.
 * 
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_AUDIO_COOK;

/**
 * @brief Pointer to the key that describes the MIME type of the MPEG2 video codec.
 * 
 * @since 17
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_MPEG2;

/**
 * @brief Pointer to the key that describes the MIME type of the MPEG4 video encoder, which is used only for
 * multiplexing MPEG4 video streams.
 * 
 * @since 17
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_MPEG4_PART2;

/**
 * @brief Pointer to the key that describes the MIME type of the H.263 video codec.
 * 
 * @since 17
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_H263;

/**
 * @brief Pointer to the key that describes the MIME type of the VC-1 video codec.
 * 
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_VC1;

/**
* @brief MIME type of the AV1 video codec.
 * 
 * @since 23
 * */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_AV1;

/**
 * @brief MIME type of the VP9 video codec.
 * 
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_VP9;

/**
 * @brief MIME type of the VP8 video codec.
 * 
 * @since 23
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_VP8;

/**
 * @brief MIME type of the RV30 video codec.
 * 
 * @since 23
 * */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_RV30;

/**
 * @brief MIME type of the RV40 video codec.
 * 
 * @since 23
 * */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_RV40;

/**
 * @brief MIME type of the WVC1 video codec.
 * 
 * @since 23
 * */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_WVC1;

/**
 * @brief MIME type of the DVVIDEO (Digital Video) video codec. Supports DV NTSC, DV PAL, and DVCPRO HD.
 * 
 * @since 23
 * */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_DVVIDEO;

/**
 * @brief MIME type of the RAWVIDEO video codec.
 * 
 * @since 23
 * */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_RAWVIDEO;

/**
 * @brief MIME type of the MPEG1 video codec.
 * 
 * @since 23
 * */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_MPEG1;

/**
 * @brief MIME type of the Cinepak video codec.
 *
 * @since 24
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_CINEPAK;

/**
 * @brief Pointer to the key that describes the MIME type of the Microsoft Video 1 (MSVIDEO1) video codec.
 * 
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_MSVIDEO1;

/**
 * @brief Pointer to the key that describes the MIME type of the WMV3 video codec.
 * 
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_WMV3;

/**
 * @brief Pointer to the key that describes the MIME type of the Motion JPEG (MJPEG) video codec.
 * 
 * @since 22
 */
extern const char *OH_AVCODEC_MIMETYPE_VIDEO_MJPEG;

/**
 * @brief Pointer to the key that describes the surface buffer timestamp. The value is of the int64_t type.
 * 
 * @deprecated since 14
 * @since 9
 */
extern const char *OH_ED_KEY_TIME_STAMP;

/**
 * @brief Pointer to the key that describes the end of stream for the surface buffer. The value type is int32_t.
 * 
 * @deprecated since 14
 * @since 9
 */
extern const char *OH_ED_KEY_EOS;

/**
 * @brief Pointer to the key that describes the track type in a media file. The value type is int32_t. For details, see
 * {@link OH_MediaType}.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_TRACK_TYPE;

/**
 * @brief Pointer to the key that describes the MIME type of the codec. The value type is char *.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_CODEC_MIME;

/**
 * @brief Pointer to the key that describes the duration in a media file, in microseconds. The value type is int64_t.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_DURATION;

/**
 * @brief Pointer to the key that describes the bit rate. The value type is int64_t.
 * You can call {@link OH_AVCapability_GetEncoderBitrateRange} to obtain the value range.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_BITRATE;

/**
 * @brief Pointer to the key that describes the maximum size of an input stream to decode. The value type is int32_t.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_MAX_INPUT_SIZE;

/**
 * @brief Pointer to the key that describes the video width. The value type is int32_t.
 *
 * For video encoding, this key sets the target encoding resolution.
 * For video decoding, this key is a resolution hint used by the decoder to pre-allocate internal buffers.
 * The actual decoded output dimensions are provided via {@link OH_MD_KEY_VIDEO_PIC_WIDTH}.
 *
 * While this key primarily governs memory allocation,
 * the recommended value range can be referenced from {@link OH_AVCapability_GetVideoWidthRange},
 * which defines the codec's supported decoding width range.
 *
 * @since 9
 */
extern const char *OH_MD_KEY_WIDTH;

/**
 * @brief Pointer to the key that describes the video height. The value type is int32_t.
 *
 * For video encoding, this key is used to set the target encoding resolution. For video decoding,
 * this key serves as a resolution hint for the decoder to pre-allocate internal buffers.
 * The actual decoded output dimensions are provided by **OH_MD_KEY_VIDEO_PIC_HEIGHT**.
 * This key is mainly used to control memory allocation. You can call {@link OH_AVCapability_GetVideoHeightRange}
 * to obtain the recommended value range. This API defines the decoding height range supported by the codec.
 *
 * @since 9
 */
extern const char *OH_MD_KEY_HEIGHT;

/**
 * @brief Pointer to the key that describes the video pixel format. The value type is int32_t.
 * For details, see {@link OH_AVPixelFormat}.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_PIXEL_FORMAT;

/**
 * @brief Pointer to the key that describes the original audio format. The value type is int32_t.
 * For details, see {@link OH_BitsPerSample}.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_AUDIO_SAMPLE_FORMAT;

/**
 * @brief Pointer to the key that describes the video frame rate. The value type is double. The value must be greater
 * than **0**. You can call {@link OH_AVCapability_GetVideoFrameRateRange} to obtain the value range.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_FRAME_RATE;

/**
 * @brief Pointer to the key that describes the video encoding bit rate mode. The value type is int32_t. For details,
 * see {@link OH_BitrateMode}.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_VIDEO_ENCODE_BITRATE_MODE;

/**
 * @brief Pointer to the key that describes the encoding grading. The value type is int32_t. For details,
 * see {@link OH_AVCProfile}, {@link OH_HEVCProfile}, and {@link OH_AACProfile}.
 * You can call {@link OH_AVCapability_GetSupportedProfiles} to obtain the supported profiles.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_PROFILE;

/**
 * @brief Pointer to the key that describes the number of audio channels. The value type is int32_t.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_AUD_CHANNEL_COUNT;

/**
 * @brief Pointer to the key that describes the audio sampling rate. The value type is int32_t.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_AUD_SAMPLE_RATE;

/**
 * @brief Pointer to the key that describes the key frame interval, in milliseconds. The value type is int32_t. This
 * key is optional and is used only for video encoding.
 *
 * A negative value means that only the first frame is a keyframe. The value **0** means that all frames are keyframes.
 * A positive value means one keyframe every (frameRate * value)/1000 frames. The default value is **1000**.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_I_FRAME_INTERVAL;

/**
 * @brief Pointer to the key that describes the rotation angle of the surface, with a clockwise direction. The value
 * type is int32_t, and the value range is {0, 90, 180, 270}. The default value is 0.
 * 
 * This key is optional and is used only for video decoding in surface mode
 * 
 * You are advised to use the **OH_MD_KEY_VIDEO_TRANSFORM_TYPE** key to set the rotation angle of the surface for video
 * decoding.
 * 
 * @since 9
 */
extern const char *OH_MD_KEY_ROTATION;

/**
 * @brief Key for video transform type, value type is int32_t, see {@link OH_NativeBuffer_TransformType}.
 *
 * This key is used to set the surface transform for video decoders (surface mode).
 * If not specified, the default value is 0 ({@link NATIVEBUFFER_ROTATE_NONE}).
 * 
 * This key and {@link OH_MD_KEY_ROTATION} are mutually exclusive. If both are provided,
 * OH_MD_KEY_VIDEO_TRANSFORM_TYPE takes precedence.
 * 
 * Note that the degrees specified in {@link OH_NativeBuffer_TransformType} represent counter-clockwise rotation,
 * which are opposite to the direction of rotation defined by {@link OH_MD_KEY_ROTATION}.
 * 
 *The correspondence is:
 *
 * - {@link NATIVEBUFFER_ROTATE_NONE}  => same as OH_MD_KEY_ROTATION = 0
 *
 * - {@link NATIVEBUFFER_ROTATE_90}    => same as OH_MD_KEY_ROTATION = 270
 *
 * - {@link NATIVEBUFFER_ROTATE_180}   => same as OH_MD_KEY_ROTATION = 180
 *
 * - {@link NATIVEBUFFER_ROTATE_270}   => same as OH_MD_KEY_ROTATION = 90
 * 
 * @since 22
 */
extern const char *OH_MD_KEY_VIDEO_TRANSFORM_TYPE;

/**
 * @brief Pointer to the key that describes the video YUV value range flag. The value type is int32_t. The value **1**
 * means a full range, and **0** means a limited range. The default value is **0**. If this parameter is set to a non-
 * zero value, the value **1** is used.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_RANGE_FLAG;

/**
 * @brief Pointer to the key that describes the video primary colors. The value type is int32_t. The default value is
 * **COLOR_PRIMARY_UNSPECIFIED**. For details, see {@link OH_ColorPrimary}. The value complies with Table 2 in H.273.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_COLOR_PRIMARIES;

/**
 * @brief Pointer to the key that describes the video transfer characteristics. The value type is int32_t. The default
 * value is **TRANSFER_CHARACTERISTIC_UNSPECIFIED**. For details, see {@link OH_TransferCharacteristic}. The value
 * complies with Table 3 in H.273.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_TRANSFER_CHARACTERISTICS;

/**
 * @brief Pointer to the key that describes the video matrix coefficients. The value type is int32_t. The default value
 * is **MATRIX_COEFFICIENT_UNSPECIFIED**. For details, see {@link OH_MatrixCoefficient}. The value must comply with
 * Table 4 in H.273.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_MATRIX_COEFFICIENTS;

/**
 * @brief Pointer to the key that describes the request for immediate encoding of I-frames. The value type is int32_t.
 * This key is used in {@link OH_VideoEncoder_SetParameter} or takes effect immediately with each frame.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_REQUEST_I_FRAME;

/**
 * @brief Pointer to the key that describes the required encoding quality. The value type is int32_t. The default value
 * is **50**. In H.264 and H.265 encoding scenarios, the value range can be obtained by calling
 * {@link OH_AVCapability_GetEncoderQualityRange}. This key applies only to the encoder in constant quality mode.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_QUALITY;

/**
 * @brief Pointer to the key that describes the codec-specific data. In the case of video, data carried in **SPS/PPS**
 * is transferred. In the case of audio, data carried in **extraData** is transferred. The value type is uint8_t\*.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_CODEC_CONFIG;

/**
 * @brief Pointer to the key that describes the title of a media file . The value type is char *.
 *
 * @since 10
 */
extern const char *OH_MD_KEY_TITLE;

/**
 * @brief Pointer to the key that describes the artist in a media file. The value type is char *.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_ARTIST;

/**
 * @brief Pointer to the key that describes the album in a media file. The value type is char *.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_ALBUM;

/**
 * @brief Pointer to the key that describes the album artist of the input media. The value type is char *.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_ALBUM_ARTIST;

/**
 * @brief Pointer to the key that describes the date in a media file, for example, 2024. The value type is char *.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_DATE;

/**
 * @brief Pointer to the key that describes the comment in a media file. The value type is char *.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_COMMENT;

/**
 * @brief Pointer to the key that describes the genre in a media file. The value type is char *.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_GENRE;

/**
 * @brief Pointer to the key that describes the copyright of a media file. The value type is char *.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_COPYRIGHT;

/**
 * @brief Pointer to the key that describes language of a media file. The value type is char *.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_LANGUAGE;

/**
 * @brief Pointer to the key that describes the description of a media file. The value type is char *.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_DESCRIPTION;

/**
 * @brief Pointer to the key that describes the lyrics in a media file. The value type is char *.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_LYRICS;

/**
 * @brief Pointer to the key that describes the number of tracks in a media file. The value type is int32_t.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_TRACK_COUNT;

/**
 * @brief Pointer to the key that describes the required encoding channel layout. The value type is int64_t. This key
 * applies only to encoders. For details, see {@link OH_AudioChannelLayout}.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_CHANNEL_LAYOUT;

/**
 * @brief Pointer to the key that describes the number of bits per sample. The value type is int32_t.
 *
 * In versions earlier than API version 20, this parameter must be set to **1** for FLAC encoding. Otherwise,
 * {@link OH_AudioCodec_Configure} returns the error code {@link AV_ERR_INVALID_VAL}.
 * However, this parameter has no actual effect and does not affect the encoding result.
 *
 * Starting from API version 20, you do not need to set it anymore.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_BITS_PER_CODED_SAMPLE;

/**
 * @brief Pointer to the key that describes the AAC format, which can be ADTS or LATM. The value type is int32_t. The
 * value **0** means the LATM format, and **1** means the ADTS format. This key is supported by AAC decoders.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_AAC_IS_ADTS;

/**
 * @brief Pointer to the key that describes the AAC SBR format. The value type is int32_t. This key applies to AAC
 * encoders.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_SBR;

/**
 * @brief Pointer to the key that describes the FLAC compliance level. The value type is int32_t. This key is used only
 * for audio encoding.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_COMPLIANCE_LEVEL;

/**
 * @brief Pointer to the key that describes the vorbis identification header. The value type is uint8_t*. This key
 * applies only to Vorbis decoders.
 * 
 * @since 10
 */
extern const char *OH_MD_KEY_IDENTIFICATION_HEADER;

/**
 * @brief Pointer to the key that describes the vorbis setup header. The value type is uint8_t*. This key applies only
 * to Vorbis decoders.
 *
 * @since 10
 */
extern const char *OH_MD_KEY_SETUP_HEADER;

/**
 * @brief Pointer to the key that describes the video scaling mode. The value type is int32_t.
 * For details, see {@link OH_ScalingMode}.
 * 
 * You are advised to set the scaling mode by calling {@link OH_NativeWindow_NativeWindowSetScalingModeV2}. This key is
 * optional and is used only for video decoding in surface mode.
 * 
 * @deprecated since 14
 * @useinstead OH_NativeWindow_NativeWindowSetScalingModeV2
 * @since 10
 */
extern const char *OH_MD_KEY_SCALING_MODE;

/**
 * @brief Pointer to the key that describes the maximum number of input buffers. The value type is int32_t.
 * 
 * @since 10
 */
extern const char *OH_MD_MAX_INPUT_BUFFER_COUNT;

/**
 * @brief Pointer to the key that describes the maximum number of output buffers. The value type is int32_t.
 * 
 * @since 10
 */
extern const char *OH_MD_MAX_OUTPUT_BUFFER_COUNT;

/**
 * @brief Pointer to the key that describes the audio codec compression level. The value type is int32_t type. This key
 * is used only for audio encoding.
 * 
 * @since 11
 */
extern const char *OH_MD_KEY_AUDIO_COMPRESSION_LEVEL;

/**
 * @brief Pointer to the key that specifies whether the video track in a media file is HDR Vivid. The value type is
 * int32_t. This key is used for both multiplexing and demultiplexing.
 *
 * The value **1** means the HDR Vivid video track, and **0** means other cases.
 * 
 * @since 11
 */
extern const char *OH_MD_KEY_VIDEO_IS_HDR_VIVID;

/**
 * @brief Pointer to the key that describes the number of audio objects. The value type is int32_t. This key is used
 * for Audio Vivid.
 * 
 * @since 11
 */
extern const char *OH_MD_KEY_AUDIO_OBJECT_NUMBER;

/**
 * @brief Pointer to the key that describes the Audio Vivid metadata. The value type is uint8_t*. This key is used
 * for Audio Vivid.
 * 
 * @since 11
 */
extern const char *OH_MD_KEY_AUDIO_VIVID_METADATA;

/**
 * @brief Pointer to the key that describes the maximum number of long-term reference (LTR) frames obtained during
 * video encoding. The value type is int32_t.
 *
 * You can use the API {@link OH_AVCapability_GetFeatureProperties} and the enumerated value
 * **VIDEO_ENCODER_LONG_TERM_REFERENCE** in {@link OH_AVCapabilityFeature} to query the maximum number.
 * 
 * @since 12
 */
extern const char *OH_FEATURE_PROPERTY_KEY_VIDEO_ENCODER_MAX_LTR_FRAME_COUNT;

/**
 * @brief Pointer to the key that describes the enabled status of temporal scalability. The value type is int32_t. **1**
 *  if enabled, **0** otherwise. The default value is **0**. If this parameter is set to a non-zero value, the value **
 * 1** is used.
 *
 * You can use the API {@link OH_AVCapability_IsFeatureSupported} and the enumerated value
 * **VIDEO_ENCODER_TEMPORAL_SCALABILITY** in {@link OH_AVCapabilityFeature}
 * to check whether the current video encoder supports temporal scalability.
 *
 * For details, see {@link Temporally Scalable Video Coding}.
 *
 * This key is optional and used only in the configuration phase of video encoding.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_ENABLE_TEMPORAL_SCALABILITY;

/**
 * @brief Pointer to the key that describes the size of a temporal image group. The value type is int32_t. This key is
 * valid only when temporal scalability is enabled.
 *
 * This key is optional and used only in the configuration phase of video encoding.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_TEMPORAL_GOP_SIZE;

/**
 * @brief Pointer to the key that describes the reference mode in a temporal image group. The value type is int32_t.
 * For details, see {@link OH_TemporalGopReferenceMode}. This key is valid only when temporal scalability is enabled.
 *
 * This key is optional and used only in the configuration phase of video encoding.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_TEMPORAL_GOP_REFERENCE_MODE;

/**
 * @brief Pointer to the key that describes the temporal layer ID in a group of pictures (GOP).
 * The value type is int32_t.
 *
 * Temporal layer ID **0** indicates the base layer. Temporal layer IDs **1** and above indicate enhancement layers.
 * The maximum temporal layer ID is determined by **OH_MD_KEY_VIDEO_ENCODER_TEMPORAL_GOP_REFERENCE_MODE** and
 * **OH_MD_KEY_VIDEO_ENCODER_TEMPORAL_GOP_SIZE**.
 * Currently, this key is used only to query the temporal layer ID carried in **AVBuffer** output by the encoder.
 * The process is as follows:
 * 1. Use {@link OH_AVCodecOnNewOutputBuffer} or {@link OH_VideoEncoder_GetOutputBuffer} to
 * obtain the buffer instance (**AVBuffer**).
 * 2. Use {@link OH_AVBuffer_GetParameter} to obtain the parameter instance (**OH_AVFormat**),
 * which does not contain basic properties.
 * 3. Use {@link OH_AVFormat_GetIntValue} and this key to obtain the temporal layer ID of the corresponding frame.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_TEMPORAL_LAYER_ID;

/**
 * @brief Key for describing the downsampling width in video encoder preprocess, value type is int32_t.
 *
 * It is used in configure or set parameter.
 * This key must be used with {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_HEIGHT} together.
 *
 * Using restrictions:
 * 1. The downsampling width and height must be configured or set together.
 *    If only one of them is configured, {@link AV_ERR_INVALID_VAL} will be returned.
 * 2. When the downsampling width and height are the same and qualified as zero, the downsampling is disabled.
 * 3. When the downsampling width and height are within the supported range, the downsampling is enabled.
 *    It's recommended to query the supported downsampling range through
 *    the interface {@link OH_AVCapability_IsVideoSizeSupported}.
 * 4. When the downsampling width and height are not within the supported range,
 *    {@link AV_ERR_INVALID_VAL} will be returned.
 * 5. Cannot be used together with crop parameters ({@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_LEFT},
 *    {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_TOP}, {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_RIGHT},
 *    {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_BOTTOM}).
 *    If both downsampling and crop parameters are set through {@link OH_VideoEncoder_Configure} or
 *    {@link OH_VideoEncoder_SetParameter}, {@link AV_ERR_INVALID_VAL} will be returned.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_WIDTH;

/**
 * @brief Key for describing the downsampling height in video encoder preprocess, value type is int32_t.
 *
 * It is used in configure or set parameter.
 * This key must be used with {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_WIDTH} together.
 * Refer to {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_WIDTH} for more details on usage and restrictions.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_HEIGHT;

/**
 * @brief Key for describing the left-coordinate (x) of the crop rectangle in video encoder preprocess,
 * value type is int32_t.
 *
 * The value represents the left-most column included in the crop frame, where column indices start at 0.
 * The Caller must use "left, top, right, bottom" together to define the crop rectangle, corresponding to:
 * - {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_LEFT}
 * - {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_TOP}
 * - {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_RIGHT}
 * - {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_BOTTOM}
 * (left, top) is the coordinate of the top-left corner of the crop rectangle.
 * (right, bottom) is the coordinate of the bottom-right corner of the crop rectangle.
 * The width and height of the crop rectangle can be calculated as:
 * - width = right - left + 1
 * - height = bottom - top + 1
 *
 * Using restrictions:
 * 1. Crop left, top, right, bottom must be configured together. If only part of them is configured,
 *    {@link AV_ERR_INVALID_VAL} will be returned.
 * 2. When crop left, top, right, bottom are all 0, the crop is disabled.
 * 3. When the crop width, height are within the supported range, the crop is enabled.
 *    It's recommended to query the supported crop range through
 *    the interface {@link OH_AVCapability_IsVideoSizeSupported}.
 * 4. When the crop values are not within the supported range,
 *    {@link AV_ERR_INVALID_VAL} will be returned.
 * 5. Cannot be used together with downsampling parameters
 *    ({@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_WIDTH},
 *    {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_HEIGHT}).
 *    If both crop and downsampling parameters are set through {@link OH_VideoEncoder_Configure} or
 *    {@link OH_VideoEncoder_SetParameter}, {@link AV_ERR_INVALID_VAL} will be returned.
 * 6. When crop is enabled, the encoder will only encode the cropped area of the input frame.
 *    The content outside the crop rectangle will be discarded and not participate in encoding.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_LEFT;

/**
 * @brief Key for describing the top-coordinate (y) of the crop rectangle in video encoder preprocess,
 * value type is int32_t.
 *
 * The value represents the top-most row included in the crop frame, where row indices start at 0.
 * Refer to {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_LEFT} for more details on usage and restrictions.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_TOP;

/**
 * @brief Key for describing the right-coordinate (x) of the crop rectangle in video encoder preprocess,
 * value type is int32_t.
 *
 * The value represents the right-most column included in the crop frame, where column indices start at 0.
 * Refer to {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_LEFT} for more details on usage and restrictions.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_RIGHT;

/**
 * @brief Key for describing the bottom-coordinate (y) of the crop rectangle in video encoder preprocess,
 * value type is int32_t.
 *
 * The value represents the bottom-most row included in the crop frame, where row indices start at 0.
 * Refer to {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_LEFT} for more details on usage and restrictions.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_BOTTOM;

/**
 * @brief Key for describing the drop frame rate in video encoder preprocess, value type is double.
 *
 * It is used in configure or set parameter.
 * The caller must ensure original frame rate is set, refer to {@link OH_MD_KEY_FRAME_RATE}.
 * The value precision is retained to 2 decimal places using round half up.
 *
 * Using restrictions:
 * 1. When value is set to 0.0, the drop frame is disabled.
 * 2. When value is set to positive value and less than original frame rate,
 *    it will drop frames to match the set frame rate.
 * 3. When value is set to negative value or equal to or greater than original frame rate,
 *    {@link AV_ERR_INVALID_VAL} will be returned.
 * 4. Can be used together with downsampling parameters
 *    ({@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_WIDTH},
 *    {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_DOWNSAMPLING_HEIGHT}).
 * 5. Can be used together with crop parameters
 *    ({@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_LEFT},
 *    {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_TOP},
 *    {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_RIGHT},
 *    {@link OH_MD_KEY_VIDEO_ENCODER_PREPROC_CROP_BOTTOM}).
 * 6. Processing order when combined: drop frame will be executed first, then downsampling or crop.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PREPROC_DROP_TO_FRAME_RATE;

/**
 * @brief Pointer to the key that describes the number of LTR frames. The value type is int32_t. The value must be
 * within the supported value range.
 *
 * Before using this key, you can use the API {@link OH_AVCapability_GetFeatureProperties} and the enumerated value
 * **VIDEO_ENCODER_LONG_TERM_REFERENCE** in {@link OH_AVCapabilityFeature} to query the number of supported LTR frames.
 * This key is optional and used only in the configuration phase of video encoding.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_LTR_FRAME_COUNT;

/**
 * @brief Pointer to the key that specifies whether the current frame is marked as an LTR frame. The value type is
 * int32_t. **1** if marked, **0** otherwise. The default value is **0**. If this parameter is set to a non-zero value,
 * the value **1** is used.
 * 
 * This key takes effect only after the number of LTR frames is configured.
 *
 * This key is optional and is used only for video encoding input rotation. The configuration takes effect immediately.
 *
 * For details, see {@link Temporally Scalable Video Coding}.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PER_FRAME_MARK_LTR;

/**
 * @brief Pointer to the key that describes the POC number of the LTR frame referenced by the current frame. The value
 * type is int32_t.
 *
 * This key is optional and is used only for video encoding input rotation. The configuration takes effect immediately.
 * 
 * For details, see {@link Temporally Scalable Video Coding}.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_PER_FRAME_USE_LTR;

/**
 * @brief Pointer to the key that specifies whether the frame corresponding to the stream output from the current
 * OH_AVBuffer is marked as an LTR frame. The value type is int32_t. **1** if marked, **0** otherwise. The default
 * value is **0**. If this parameter is set to a non-zero value, the value **1** is used.
 *
 * This key is optional and is used only for video encoding output rotation.
 *
 * It indicates the attribute of a frame.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_PER_FRAME_IS_LTR;

/**
 * @brief Pointer to the key that describes the POC of the frame. The value type is int32_t.
 *
 * This key is optional and is used only for video encoding output rotation.
 *
 * It indicates the attribute of a frame.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_PER_FRAME_POC;

/**
 * @brief Pointer to the key that describes the top coordinate (y) of the cropped rectangle. The value type is int32_t.
 *
 * The row at the top of the cropped rectangle is contained, and the row index starts from 0.
 *
 * This key is used only for video decoding.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_CROP_TOP;

/**
 * @brief Pointer to the key that describes the bottom coordinate (y) of the cropped rectangle. The value type is
 * int32_t.
 *
 * The row at the bottom of the cropped rectangle is contained, and the row index starts from 0.
 *
 * This key is used only for video decoding.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_CROP_BOTTOM;

/**
 * @brief Pointer to the key that describes the left coordinate (x) of the cropped rectangle. The value type is int32_t.
 *
 * The leftmost column of the cropped rectangle is contained, and the column index starts from 0.
 *
 * This key is used only for video decoding.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_CROP_LEFT;

/**
 * @brief Pointer to the key that describes the right coordinate (x) of the cropped rectangle. The value type is
 * int32_t.
 *
 * The rightmost column of the cropped rectangle is contained, and the column index starts from 0.
 *
 * This key is used only for video decoding.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_CROP_RIGHT;

/**
 * @brief Pointer to the key that describes the stride of the video frame. The value type is int32_t.
 *
 * Stride indicates the byte distance between the start positions of two consecutive rows in memory.
 * Due to hardware alignment requirements, the stride is typically greater than or equal to the image's active width.
 * When the stride equals the width, there is no horizontal padding. You should always obtain the actual stride through
 * {@link OH_VideoEncoder_GetInputDescription} (for encoding),
 * {@link OH_VideoDecoder_GetOutputDescription} (for decoding), or **OH_AVFormat** in
 * the {@link OH_AVCodecOnStreamChanged} callback, instead of assuming a fixed value.
 * For details about the example, see step 8 in [video encoding](docroot://media/avcodec/video-encoding.md#buffer-mode)
 * in buffer mode or step 11 in [video decoding](docroot://media/avcodec/video-decoding.md#buffer-mode) in buffer mode.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_STRIDE;

/**
 * @brief Pointer to the key that describes the height of the video frame. The value type is int32_t.
 *
 * Height indicates the total number of rows allocated in the memory for a single plane. Due to hardware alignment
 * requirements, **sliceHeight** is typically greater than or equal to the image's active height.
 * The offset of the start address of the U plane relative to the origin of the Y plane is **sliceHeight** x **stride**.
 * You should always obtain the actual height through {@link OH_VideoEncoder_GetInputDescription} (for encoding),
 * {@link OH_VideoDecoder_GetOutputDescription} (for decoding), or **OH_AVFormat** in
 * the {@link OH_AVCodecOnStreamChanged} callback, instead of assuming a fixed value.
 * For details about the example, see step 8 in [video encoding](docroot://media/avcodec/video-encoding.md#buffer-mode)
 * in buffer mode or step 11 in [video decoding](docroot://media/avcodec/video-decoding.md#buffer-mode) in buffer mode.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_SLICE_HEIGHT;

/**
 * @brief Pointer to the key that describes the actual active width of a decoded video frame. The value type is int32_t.
 * This key is read-only and used only for video decoding.
 *
 * You can obtain the width from the returned **OH_AVFormat** instance when {@link OH_VideoDecoder_GetOutputDescription}
 * is called or decoded output stream changes are detected through the {@link OH_AVCodecOnStreamChanged}
 * callback. This value indicates the visible width after cropping, which is different from **OH_MD_KEY_WIDTH** set in
 * the configuration phase. The latter is a configuration hint used for pre-allocating buffers. When cropping is
 * applied, this value (rather than the stride) should be used as the actual width for displaying or saving the image.
 * For details about the image layout and usage example, see step 8 in
 * [video encoding](docroot://media/avcodec/video-encoding.md#buffer-mode) in buffer mode or
 * step 11 in [video decoding](docroot://media/avcodec/video-decoding.md#buffer-mode) in buffer mode.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_PIC_WIDTH;

/**
 * @brief Pointer to the key that describes the actual active height of a decoded video frame.
 * The value type is int32_t. This key is read-only and used only for video decoding.
 *
 * You can obtain the height from the returned **OH_AVFormat** instance when
 * {@link OH_VideoDecoder_GetOutputDescription} is called or decoded output bitstream changes are detected through
 * the {@link OH_AVCodecOnStreamChanged} callback. This value indicates the visible height after cropping,
 * which is different from **OH_MD_KEY_HEIGHT** set in the configuration phase. The latter is a configuration hint used
 * for pre-allocating buffers. When cropping is applied, this value (rather than **sliceHeight**) should be used as the
 * actual height for displaying or saving the image.
 * For details about the image layout and usage example, see step 8
 * in [video encoding](docroot://media/avcodec/video-encoding.md#buffer-mode) in buffer mode or
 * step 11 in [video decoding](docroot://media/avcodec/video-decoding.md#buffer-mode) in buffer mode.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_PIC_HEIGHT;

/**
 * @brief Pointer to the key that describes the enabled status of low-latency video decoding. The value type is int32_t.
 * **1** if enabled, **0** otherwise. The default value is **0**. If this parameter is set to a non-zero value, the
 * value **1** is used.
 *
 * This key is optional and used only in the configuration phase.
 *
 * If enabled, the input and output data held by the video decoder does not exceed the amount required by the decoder
 * standard.
 *
 * You can call {@link OH_AVCapability_IsFeatureSupported} to check whether a specific decoder supports low-latency
 * decoding. If supported, the video decoder outputs frames in the decoding sequence when low-latency video codec is
 * enabled.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENABLE_LOW_LATENCY;

/**
 * @brief Pointer to the key that describes the maximum Quantization Parameter (QP) allowed by the video encoder. The
 * value type is int32_t.
 *
 * Tt is used in configure/setparameter or takes effect immediately with the frame.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_QP_MAX;

/**
 * @brief Pointer to the key that describes the minimum QP allowed by the video encoder. The value type is int32_t.
 *
 * It is used in configure/setparameter or takes effect immediately with the frame.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_QP_MIN;

/**
 * @brief Pointer to the key that describes the average QP of video frames. The value type is int32_t.
 *
 * Pointer to the key that describes the average QP value of the current frame encoding block.
 * It is output with {@link OH_AVBuffer}.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_QP_AVERAGE;

/**
 * @brief Pointer to the key that describes the Mean Squared Error (MSE) of video frames. The value type is double.
 *
 * Pointer to the key that describes the average MSE value of the current frame encoding block.
 * It is output with {@link OH_AVBuffer}.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_MSE;

/**
 * @brief Pointer to the key that describes the decoding timestamp corresponding to the audio, video, or subtitle
 * sample carried in AVBuffer, in microseconds. The value type is int64_t.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_DECODING_TIMESTAMP;

/**
 * @brief Pointer to the key that describes the duration corresponding to the audio, video, or subtitle sample carried
 * in AVBuffer, in microseconds. The value type is int64_t.
 *
 * @since 12
 */
extern const char *OH_MD_KEY_BUFFER_DURATION;

/**
 * @brief Pointer to the key that describes the aspect ratio of the sample. The value type is double.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_SAR;

/**
 * @brief Pointer to the key that describes the start time of the first frame in a media file, measured in microseconds.
 *  The value type is int64_t.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_START_TIME;

/**
 * @brief Pointer to the key that describes the start time of the track, measured in microseconds. The value type is
 * int64_t.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_TRACK_START_TIME;

/**
 * @brief Pointer to the key that describes the output color space of the video decoder. The value type is int32_t.
 *
 * The supported value is **OH_COLORSPACE_BT709_LIMIT**. For details, see {@link OH_NativeBuffer_ColorSpace}.
 *
 * It is used in {@link OH_VideoDecoder_Configure}.
 *
 * Before calling {@link OH_VideoDecoder_Start}, you must call {@link OH_VideoDecoder_Prepare}.
 *
 * If Color Space Conversion (CSC) is supported and this key is configured, the video decoder automatically transcodes
 * the HDR Vivid video to the specified color space.
 *
 * If CSC is not supported, the error code **AV_ERR_VIDEO_UNSUPPORTED_COLOR_SPACE_CONVERSION** in {@link OH_AVErrCode}
 * is returned when {@link OH_VideoDecoder_Configure} is called. If the input video is not an HDR Vivid video,
 * the callback function {@link OH_AVCodecOnError} is invoked to report the error code
 * **AV_ERR_VIDEO_UNSUPPORTED_COLOR_SPACE_CONVERSION** in {@link OH_AVErrCode}.
 * 
 * @since 12
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_OUTPUT_COLOR_SPACE;

/**
 * @brief Pointer to the key that specifies whether the decoder enables the video variable frame rate feature. The
 * value type is int32_t.
 * **1** if enabled, **0** otherwise.
 * 
 * @since 15
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_OUTPUT_ENABLE_VRR;

/**
 * @brief Pointer to the key that describes the media file creation time. The value type is char *. The value must be
 * in the UTC time format complying with ISO 8601. Time format example: 2024-12-28T00:00:00:000000Z
 * 
 * @since 14
 */
extern const char *OH_MD_KEY_CREATION_TIME;

/**
 * @brief Pointer to the key that describes the duration (in milliseconds) for which the last frame will be resubmitted
 * repeatedly, if no new frame is available after the previous frame is submitted to the encoder. The value type is
 * int32_t.
 *
 * This key is used only in the configuration phase of video encoding in surface mode.
 *
 * Configured value:
 *
 * - If the value is less than or equal to 0, the request is intercepted in the configuration phase and {@link ERROR
 * AV_ERR_INVALID_VAL} is returned.
 *
 * - If the value is greater than 0, the last frame will be resubmitted repeatedly in the specified duration, measured
 * in milliseconds.
 * 
 * @since 18
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_REPEAT_PREVIOUS_FRAME_AFTER;

/**
 * @brief Pointer to the key that describes the maximum number of times the encoder can repeat encoding the previous
 * frame when no new frame is available. The value type is int32_t.
 *
 * This key takes effect only when **OH_MD_KEY_VIDEO_ENCODER_REPEAT_PREVIOUS_FRAME_AFTER** is available and is used
 * only in the configuration phase.
 *
 * Configured value.
 *
 * - If the value is equal to 0, the request is intercepted in the configuration phase and **ERROR AV_ERR_INVALID_VAL**
 * is returned.
 *
 * - If the value is less than 0 and no new frame is available, the encoder repeatedly encodes the previous frame until
 * the upper limit of the system is reached.
 *
 * - If the value is greater than 0 and no new frame is available, the encoder repeatedly encodes the previous frame
 * until the maximum number specified is reached.
 * 
 * @since 18
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_REPEAT_PREVIOUS_MAX_COUNT;

/**
 * @brief Pointer to the key that describes the enabled status of B-frame encoding. The value type is int32_t (**0** or
 * **1**). **1** if enabled, **0** otherwise. This key is optional and used only for video encoding. The default value
 * is **0**.
 *
 * If enabled, the video encoder uses B-frames, resulting in a different decoding order from the display order.
 *
 * If the platform does not support this feature, the configuration of this key does not take effect.
 *
 * To check whether the platform supports B-frame encoding, use the {@link OH_AVCapability_IsFeatureSupported} API and
 * the enumerated value {@link OH_AVCapabilityFeature} VIDEO_ENCODER_B_FRAME.
 *
 * This key is used only in the configuration phase.
 * 
 * @since 20
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_ENABLE_B_FRAME;

/**
 * @brief Pointer to the key that describes the maximum number of consecutive B-frames supported by the video encoder.
 * The value type is int32_t. Note: This key is used only to query the encoder capability.
 *
 * The usage specifications are as follows:
 *
 * 1. To check whether the platform supports B-frame encoding, use the {@link OH_AVCapability_IsFeatureSupported} API
 * and the enumerated value {@link OH_AVCapabilityFeature} VIDEO_ENCODER_B_FRAME.
 *
 * 2. Obtain the OH_AVFormat pointer through the {@link OH_AVCapability_GetFeatureProperties} API and
 * the enumerated value {@link OH_AVCapabilityFeature} VIDEO_ENCODER_B_FRAME.
 *
 * 3. Obtain the maximum number of B-frames through the {@link OH_AVFormat_GetIntValue} API and this key.
 *
 * @since 20
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_MAX_B_FRAMES;

/**
 * @brief Key to set the region of interest(ROI) parameters. Value type is string in the format
 * "Top1,Left1-Bottom1,Right1[=Params1];Top2,Left2-Bottom2,Right2[=Params2];".
 * Each "Top,Left-Bottom,Right" represents the coordinate information of one ROI.
 * The "[=Params]" is optional and supports two formats for backward compatibility:
 * 1. Legacy format: A single integer representing the quantization parameter offset (e.g., "=Offset").
 * 2. Key-Value format (Recommended): Comma-separated key-value pairs (e.g., "=dqp:-6,slb:1").
 * Supported keys:
 * - "dqp": Quantization parameter offset.
 * - "slb": Semantic label. The value must correspond to {@link OH_ROI_METADATA_SEMANTIC_LABEL_TYPE}.
 * If "=Params" is omitted entirely, like "Top1,Left1-Bottom1,Right1;Top2,Left2-Bottom2,Right2=dqp:-6;",
 * the encoder will use the default parameters to perform the ROI encoding on the first ROI and
 * use the specified parameters on the second ROI.
 * Note that the number of ROIs that can be applied simultaneously does not exceed six, and the total area must
 * not exceed one-fifth of the total image area.
 *
 * This is an optional key that applies only to video encoder.
 * It is used in running process and is set with each frame.
 * In surface mode, it is used in {@link OH_VideoEncoder_OnNeedInputParameter}.
 * In buffer mode, it is configured via {@link OH_AVBuffer_SetParameter}.
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 20
 */
extern const char *OH_MD_KEY_VIDEO_ENCODER_ROI_PARAMS;

/**
 *
 * @brief Pointer to the key that specifies whether the moov metadata should be at the front of a media file. The value
 * type is int32_t. The value **1** indicates that the moov metadata should be at the front of a media file, and **0**
 * indicates that the moov metadata should not be at the front of a media file. The default value is **0**.
 * 
 * @since 20
 */
extern const char *OH_MD_KEY_ENABLE_MOOV_FRONT;

/**
 * @brief Pointer to the key that describes the quality parameter in SQR mode. The value range is [0, 51] (same as the
 * QP value in encoding). A smaller value indicates a higher output bit rate and better quality.
 *
 * It is used in the configuration or parameter setting phase.
 * 
 * @since 20
 */
extern const char *OH_MD_KEY_SQR_FACTOR;

/**
 * @brief Pointer to the key that describes the maximum bit rate in SQR mode. The value range can be obtained by
 * calling {@link OH_AVCapability_GetEncoderBitrateRange} and is the same as that of **OH_MD_KEY_BITRATE**. The unit is
 * bit/s. The value type is int64_t.
 *
 * It is used in the configuration or parameter setting phase.
 * 
 * @since 20
 */
extern const char *OH_MD_KEY_MAX_BITRATE;

/**
 * @brief Pointer to the key that describes the reference relationship between media file tracks. The value type is
 * int32_t*.
 * 
 * @since 20
 */
extern const char *OH_MD_KEY_REFERENCE_TRACK_IDS;

/**
 * @brief Pointer to the key that describes the auxiliary track type of a media file. The value type is char *.
 * 
 * @since 20
 */
extern const char *OH_MD_KEY_TRACK_REFERENCE_TYPE;

/**
 * @brief Pointer to the key that describes the auxiliary track description of a media file. The value type is char *.
 * 
 * @since 20
 */
extern const char *OH_MD_KEY_TRACK_DESCRIPTION;

/**
 * @brief Pointer to the key that describes the enabled status of the PTS-based bit rate control mode. The value type
 * is int32_t. **1** if enabled, **0** otherwise. The default value is **0**. If this parameter is set to a non-zero
 * value, the value **1** is used.
 *
 * This key is optional and is used only for video encoding.
 *
 * If this feature is enabled, each video frame must contain PTS information and be sent to the encoder. In surface
 * mode, the PTS is set by calling {@link OH_NativeWindow_NativeWindowHandleOpt}, in units of nanosecond (ns).
 * In buffer mode, the PTS is set by calling {@link OH_AVBuffer_SetBufferAttr}, in units of microsecond (us).
 *
 * It is used in the configuration phase.
 * 
 * @since 20
*/
extern const char *OH_MD_KEY_VIDEO_ENCODER_ENABLE_PTS_BASED_RATECONTROL;

/**
 * @brief Pointer to the key that describes the enabled status of audio/video codec synchronization. The value type is
 * int32_t. **1** if enabled, **0** otherwise. The default value is **0**. If this parameter is set to a non-zero value,
 *  the value **1** is used. This key is optional.
 *
 * If this feature is enabled, pay attention to the following:
 * 1. The codec cannot have a callback function.
 * 2. You must use the buffer query API instead of the callback function.
 * 3. The key can be used only in the configuration phase.
 *
 * @since 20
 */
extern const char *OH_MD_KEY_ENABLE_SYNC_MODE;

/**
 * @brief Pointer to the key that specifies whether to output blank frames when the video decoder is disabled. The
 * value type is int32_t. **1** to output, **0** otherwise. The default value is **0**. If this parameter is set to a
 * non-zero value, the value **1** is used. This key is optional and is used only for video decoding in surface mode.
 * 
 * After this function is enabled, the video decoder outputs a blank frame (usually black) when the
 * {@link OH_VideoDecoder_Stop} or {@link OH_VideoDecoder_Destroy} API is called.
 * This mechanism prevents frozen frames caused by sudden termination of the decoder.
 * 
 * @since 20
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_BLANK_FRAME_ON_SHUTDOWN;

/**
 * @brief Pointer to the key that is used to query the native buffer pixel format in video encoding and decoding. The
 * value type is int32_t.
 *
 * For details, see the pixel formats defined in {@link OH_NativeBuffer_Format}. This key is used in the following
 * scenarios:
 *
 * 1. Video decoding: Call {@link OH_VideoDecoder_GetOutputDescription} or {@link OH_AVCodecOnStreamChanged} to obtain
 * the current output format from the returned OH_AVFormat object.
 *
 * 2. Video encoding: Call {@link OH_VideoEncoder_GetInputDescription} to obtain the current input format from the
 * returned OH_AVFormat object.
 * 
 * @since 22
 */
extern const char *OH_MD_KEY_VIDEO_NATIVE_BUFFER_FORMAT;

/**
 * @brief Pointer to the key carried in the OH_AVBuffer used to skip part of the decoded audio data. It is measured in
 * sample points, with a value type of uint8_t*. This key is supported when using MP3, Vorbis, or OPUS decoders.
 *
 * It is carried only by the first and last frames of an audio stream and is optional. Method 1: Obtain the information
 * during demultiplexing and set it to the input OH_AVBuffer used for decoding.
 *
 * 1. Obtain the OH_AVBuffer used for decoding from the callback function {@link OH_AVCodecOnNeedInputBuffer} of
 * {@link OH_AVCodecCallback}.
 *
 * 2. Call {@link OH_AVDemuxer_ReadSampleBuffer} to read audio data. This function automatically sets **
 * OH_MD_KEY_BUFFER_SKIP_SAMPLES_INFO** when needed.
 *
 * 3. Call {@link OH_AudioCodec_PushInputBuffer} to push the input OH_AVBuffer for decoding.
 *
 * Method 2: Construct the data required by the key and set it to the input OH_AVBuffer used for decoding.
 *
 * Create a 10-byte uint8_t[] array with the structure as follows:
 *
 * 1. Bytes 0-3 (uint32_t, little-endian): number of samples to skip from the beginning of this frame.
 *
 * 2. Bytes 4-7 (uint32_t, little-endian): number of samples to skip from the end of this frame (must not exceed the
 * frame's total sample count).
 *
 * 3. Bytes 8-9: reserved; set to **0**.
 * 
 * @since 23
 */
extern const char *OH_MD_KEY_BUFFER_SKIP_SAMPLES_INFO;

/**
 * @brief Pointer to the key for enabling {@link OH_MD_KEY_BUFFER_SKIP_SAMPLES_INFO} in the audio decoder.
 * The value type is int32_t. **1** to enable, **0** otherwise. The default value is **0**.
 * If this parameter is set to a value other than **1**, the value **0** is used.
 * 
 * This key is optional. It is for the audio decoder only.
 *
 * @since 24
 */
extern const char *OH_MD_KEY_ENABLE_BUFFER_SKIP_SAMPLES;

/**
 * @brief Key for latitude, value type is float, The range is [-90.0, 90.0].
 *
 * Represents the latitude of the geographic location.
 * 
 * @since 24
 */
extern const char *OH_MD_KEY_LATITUDE;

/**
 * @brief Longitude key. The value is of the float type, and the value range is [-180.0, 180.0]. It indicates the
 * longitude in geographic location information.
 * 
 * @since 24
 */
extern const char *OH_MD_KEY_LONGITUDE;

/**
 * @brief Altitude key. The value is of the float type. This key is optional. It indicates the altitude in geographic
 * location information.
 * 
 * @since 24
 */
extern const char *OH_MD_KEY_ALTITUDE;

/**
 * @brief Key for getting screen capture rectangular window. Value type is a int32_t array, the array length is 4.
 * Get the rectangular window in captured screen, represent [top, left, width, height] in the int32_t array,
 * which can be obtained by calling {@link OH_AVFormat_GetIntBuffer}.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_SCREEN_CAPTURE_WINDOW_RECT;

/**
 * @brief Key for setting the Audio Vivid signal input format.
 *
 * Required for Audio Vivid encoder. Specifies the signal format of input data.
 * The value should be from {@link OH_AudioVividSignalFormat}.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_AUDIO_VIVID_SIGNAL_FORMAT;

/**
 * @brief Key for setting the soundbed channel layout.
 *
 * Configures the channel layout for soundbed. The value should be from {@link OH_AudioChannelLayout}.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_AUDIO_SOUNDBED_LAYOUT;

/**
 * @brief Key for setting the soundbed bitrate in bits per second.
 *
 * Configures the bitrate for soundbed channels. The actual bitrate may be adjusted by the encoder
 * based on codec capabilities and constraints.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_AUDIO_SOUNDBED_BITRATE;

/**
 * @brief Key for setting the audio object bitrate in bits per second.
 *
 * Configures the bitrate for audio objects. The actual bitrate may be adjusted by the encoder
 * based on codec capabilities and constraints.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_AUDIO_OBJECT_BITRATE;

/**
 * @brief Key for setting the video decoding frame retention mode. The value type is int32_t.
 *
 * The value represents a frame retention mode defined in {@link OH_FRAME_RETENTION_MODE}.
 * Please refer to the enumeration definition for detailed descriptions of each mode
 * and their behaviors.This key can be configured via the {@link OH_VideoDecoder_Configure} and
 * {@link OH_VideoDecoder_SetParameter} interfaces.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_FRAME_RETENTION_MODE;

/**
 * @brief Key for setting the video decoding frame retention ratio. The value type is double.
 *
 * This parameter takes effect when {@link OH_MD_KEY_VIDEO_DECODER_FRAME_RETENTION_MODE} is set to
 * {@link OH_FRAME_RETENTION_MODE#OH_FRAME_RETENTION_MODE_UNIFORM}, or when the retention mode is not
 * configured (implicitly defaulting to uniform behavior). This configuration is ignored ONLY when
 * the retention mode is explicitly set to {@link OH_FRAME_RETENTION_MODE#OH_FRAME_RETENTION_MODE_ADAPTIVE}
 * or {@link OH_FRAME_RETENTION_MODE#OH_FRAME_RETENTION_MODE_FULL}.
 * The valid range is [0.01, 1.0] (where 1.0 means all frames retained and 0.01 is the minimum limit);
 * any value outside this range is considered invalid and will be ignored. This key can be configured
 * via the {@link OH_VideoDecoder_Configure} and {@link OH_VideoDecoder_SetParameter} interfaces.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_FRAME_RETENTION_RATIO;

/**
 * @brief Key for configuring the video decoder playback speed. The value type is double.
 *
 * This key specifies the target playback speed of the video. It is primarily recommended
 * for use in conjunction with {@link OH_FRAME_RETENTION_MODE#OH_FRAME_RETENTION_MODE_ADAPTIVE}
 * to assist the adaptive algorithm in accurately evaluating the perceptual impact of frame
 * drops. The value must be strictly greater than 0.0, with recommended standard values
 * including 0.5, 0.75, 1.0 (normal speed), 1.25, 1.5, 2.0, and 3.0; any value less than
 * or equal to 0.0 is considered invalid. This key can be configured via the
 * {@link OH_VideoDecoder_Configure} and {@link OH_VideoDecoder_SetParameter} interfaces.
 *
 * @since 26.0.0
 */
extern const char *OH_MD_KEY_VIDEO_DECODER_SPEED;

/**
 * @brief Enumerates the media types.
 * 
 * @since 9
 */
typedef enum OH_MediaType {
    /**
     * Audio track.
     * @since 9
     */
    MEDIA_TYPE_AUD = 0,

    /**
     * Video track.
     * @since 9
     */
    MEDIA_TYPE_VID = 1,

    /**
     * Subtitle track.
     * @since 12
     */
    MEDIA_TYPE_SUBTITLE = 2,

    /**
     * Timed metadata track.
     * @since 20
     */
    MEDIA_TYPE_TIMED_METADATA = 5,

    /**
     * Auxiliary track.
     * @since 20
     */
    MEDIA_TYPE_AUXILIARY = 6
} OH_MediaType;

/**
 * @brief Enumerates the AAC profiles.
 * 
 * @since 9
 */
typedef enum OH_AACProfile {
    /**
     * AAC profile of the low complexity level.
     * @since 9
     */
    AAC_PROFILE_LC = 0,

    /**
     * AAC profile of the high efficiency level. Audio object types AAC LC and SBR are included.
     * @since 14
     */
    AAC_PROFILE_HE = 3,

    /**
     * AAC profile of the high efficiency V2 level. Audio object types AAC LC, SBR, and PS are included.
     * @since 14
     */
    AAC_PROFILE_HE_V2 = 4
} OH_AACProfile;

/**
 * @brief Enumerates the AVC profiles.
 * 
 * @since 9
 */
typedef enum OH_AVCProfile {
    /**
     * AVC baseline profile.
     * @since 9
     */
    AVC_PROFILE_BASELINE = 0,

    /**
     * AVC high profile.
     * @since 9
     */
    AVC_PROFILE_HIGH = 4,

    /**
     * AVC main profile.
     * @since 9
     */
    AVC_PROFILE_MAIN = 8
} OH_AVCProfile;

/**
 * @brief Enumerates the HEVC profiles.
 * 
 * @since 10
 */
typedef enum OH_HEVCProfile {
    /**
     * HEVC profile of the main level.
     * @since 10
     */
    HEVC_PROFILE_MAIN = 0,

    /**
     * HEVC profile of the 10-bit main level.
     * @since 10
     */
    HEVC_PROFILE_MAIN_10 = 1,

    /**
     * HEVC profile of the main still picture level.
     * @since 10
     */
    HEVC_PROFILE_MAIN_STILL = 2,

    /**
     * HEVC profile of the main 10 HDR10 level.
     * @deprecated since 14
     * @since 10
     */
    HEVC_PROFILE_MAIN_10_HDR10 = 3,

    /**
     * HEVC profile of the main 10 HDR10+ level.
     * @deprecated since 14
     * @since 10
     */
    HEVC_PROFILE_MAIN_10_HDR10_PLUS = 4
} OH_HEVCProfile;

/**
 * @brief Enumerates the VVC profiles.
 * 
 * @since 15
 */
typedef enum OH_VVCProfile {
    /**
     * VVC profile of the 10-bit main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_10 = 1,

    /**
     * VVC profile of the 12-bit main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_12 = 2,

    /**
     * VVC profile of the 12-bit intra main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_12_INTRA = 10,

    /**
     * VVC profile of the 10-bit main level for multi-layer encoding.
     * @since 15
     */
    VVC_PROFILE_MULTI_MAIN_10 = 17,

    /**
     * VVC profile of the 10-bit full-sample main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_10_444 = 33,

    /**
     * VVC profile of the 12-bit full-sample main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_12_444 = 34,

    /**
     * VVC profile of the 16-bit full-sample main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_16_444 = 36,

    /**
     * VVC profile of the 12-bit full-sample intra main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_12_444_INTRA = 42,

    /**
     * VVC profile of the 16-bit full-sample intra main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_16_444_INTRA = 44,

    /**
     * VVC profile of the 10-bit full-sample main level for multi-layer encoding.
     * @since 15
     */
    VVC_PROFILE_MULTI_MAIN_10_444 = 49,

    /**
     * VVC profile of the 10-bit still picture main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_10_STILL = 65,

    /**
     * VVC profile of the 12-bit still picture main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_12_STILL = 66,

    /**
     * VVC profile of the 10-bit full-sample still picture main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_10_444_STILL = 97,

    /**
     * VVC profile of the 12-bit full-sample still picture main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_12_444_STILL = 98,

    /**
     * VVC profile of the 16-bit full-sample still picture main level.
     * @since 15
     */
    VVC_PROFILE_MAIN_16_444_STILL = 100
} OH_VVCProfile;

/**
 * @brief Enumerates the MPEG2 profiles.
 * 
 * @since 17
 */
typedef enum OH_MPEG2Profile {
    /**
     * Simple profile.
     * @since 17
     */
    MPEG2_PROFILE_SIMPLE = 0,

    /**
     * Main profile.
     * @since 17
     */
    MPEG2_PROFILE_MAIN = 1,

    /**
     * Signal-to-Noise Ratio (SNR) scalable profile.
     * @since 17
     */
    MPEG2_PROFILE_SNR_SCALABLE = 2,

    /**
     * Spatial scalable profile.
     * @since 17
     */
    MPEG2_PROFILE_SPATIALLY_SCALABLE = 3,

    /**
     * High profile.
     * @since 17
     */
    MPEG2_PROFILE_HIGH = 4,

    /**
     * 4:2:2 profile.
     * @since 17
     */
    MPEG2_PROFILE_422 = 5
} OH_MPEG2Profile;

/**
 * @brief Enumerates the MPEG4 profiles.
 * 
 * @since 17
 */
typedef enum OH_MPEG4Profile {
    /**
     * Simple profile.
     * @since 17
     */
    MPEG4_PROFILE_SIMPLE = 0,

    /**
     * Simple scalable profile.
     * @since 17
     */
    MPEG4_PROFILE_SIMPLE_SCALABLE = 1,

    /**
     * Core profile.
     * @since 17
     */
    MPEG4_PROFILE_CORE = 2,

    /**
     * Main profile.
     * @since 17
     */
    MPEG4_PROFILE_MAIN = 3,

    /**
     * N-bit profile.
     * @since 17
     */
    MPEG4_PROFILE_N_BIT = 4,

    /**
     * Hybrid profile.
     * @since 17
     */
    MPEG4_PROFILE_HYBRID = 5,

    /**
     * Basic animated texture profile.
     * @since 17
     */
    MPEG4_PROFILE_BASIC_ANIMATED_TEXTURE = 6,

    /**
     * Scalable texture profile.
     * @since 17
     */
    MPEG4_PROFILE_SCALABLE_TEXTURE = 7,

    /**
     * Simple FA profile.
     * @since 17
     */
    MPEG4_PROFILE_SIMPLE_FA = 8,

    /**
     * Advanced real-time simple profile.
     * @since 17
     */
    MPEG4_PROFILE_ADVANCED_REAL_TIME_SIMPLE = 9,

    /**
     * Core scalable profile.
     * @since 17
     */
    MPEG4_PROFILE_CORE_SCALABLE = 10,

    /**
     * Advanced coding efficiency profile.
     * @since 17
     */
    MPEG4_PROFILE_ADVANCED_CODING_EFFICIENCY = 11,

    /**
     * Advanced core profile.
     * @since 17
     */
    MPEG4_PROFILE_ADVANCED_CORE = 12,

    /**
     * Advanced scalable texture profile.
     * @since 17
     */
    MPEG4_PROFILE_ADVANCED_SCALABLE_TEXTURE = 13,

    /**
     * Advanced simple profile.
     * @since 17
     */
    MPEG4_PROFILE_ADVANCED_SIMPLE = 17
} OH_MPEG4Profile;

/**
 * @brief Enumerates the H.263 profiles.
 * 
 * @since 17
 */
typedef enum OH_H263Profile {
    /**
     * Baseline profile.
     * @since 17
     */
    H263_PROFILE_BASELINE = 0,

    /**
     * Version 1 backward compatibility.
     * @since 17
     */
    H263_PROFILE_VERSION_1_BACKWARD_COMPATIBILITY = 2
} OH_H263Profile;

/**
 * @brief Enumerates the VC-1 profiles.
 * 
 * @since 22
 */
typedef enum OH_VC1Profile {
    /**
     * Simple profile.
     * @since 22
     */
    VC1_PROFILE_SIMPLE = 0,

    /**
     * Main profile.
     * @since 22
     */
    VC1_PROFILE_MAIN = 1,

    /**
     * High profile.
     * @since 22
     */
    VC1_PROFILE_ADVANCED = 2
} OH_VC1Profile;

/**
 * @brief AV1 profile.
 * 
 * @since 23
 */
typedef enum OH_AV1Profile {
    /**
     * Main profile.
     * @since 23
     */
    AV1_PROFILE_MAIN = 0,

    /**
     * High profile.
     * @since 23
     */
    AV1_PROFILE_HIGH = 1,

    /**
     * Professional profile.
     * @since 23
     */
    AV1_PROFILE_PROFESSIONAL = 2
} OH_AV1Profile;

/**
* @brief VP9 profile.
* 
* @since 23
*/
typedef enum OH_VP9Profile {
    /**
     * Profile 0.
     * @since 23
     */
    VP9_PROFILE_0 = 0,

    /**
     * Profile 1.
     * @since 23
     */
    VP9_PROFILE_1 = 1,

    /**
     * Profile 2.
     * @since 23
     */
    VP9_PROFILE_2 = 2,

    /**
     * Profile 3.
     * @since 23
     */
    VP9_PROFILE_3 = 3
} OH_VP9Profile;

/**
* @brief WVC1 profile.
* 
* @since 23
*/
typedef enum OH_WVC1Profile {
    /**
     * High profile.
     * @since 23
     */
    WVC1_PROFILE_ADVANCED = 0
} OH_WVC1Profile;

/**
 * @brief Enumerates the WMV3 profiles.
 * 
 * @since 22
 */
typedef enum OH_WMV3Profile {
    /**
     * Simple profile.
     * @since 22
     */
    WMV3_PROFILE_SIMPLE = 0,

    /**
     * Main profile.
     * @since 22
     */
    WMV3_PROFILE_MAIN = 1
} OH_WMV3Profile;

/**
 * @brief Enumerates the output file formats supported by a muxer.
 * 
 * @since 10
 */
typedef enum OH_AVOutputFormat {
    /**
     * @brief Default format, which is MP4.
     * 
     * @since 10
     */
    AV_OUTPUT_FORMAT_DEFAULT = 0,

    /**
     * @brief The muxer output MP4 file format.
     * 
     * @since 10
     */
    AV_OUTPUT_FORMAT_MPEG_4 = 2,

    /**
     * @brief The muxer output M4A file format.
     * 
     * @since 10
     */
    AV_OUTPUT_FORMAT_M4A = 6,

    /**
     * @brief The muxer output amr file format.
     * 
     * @since 12
     */
    AV_OUTPUT_FORMAT_AMR = 8,

    /**
     * @brief The muxer output mp3 file format.
     * 
     * @since 12
     */
    AV_OUTPUT_FORMAT_MP3 = 9,

    /**
     * @brief The muxer output wav file format.
     * 
     * @since 12
     */
    AV_OUTPUT_FORMAT_WAV = 10,

    /**
     * @brief The muxer output aac file format.
     * 
     * @since 18
     */
    AV_OUTPUT_FORMAT_AAC = 11,

    /**
     * @brief The muxer output flac file format.
     * 
     * @since 20
     */
    AV_OUTPUT_FORMAT_FLAC = 12,

    /**
     * @brief The muxer output ogg file format.
     * 
     * @since 23
     */
    AV_OUTPUT_FORMAT_OGG = 13,

    /**
     * @brief The muxer output flv file format.
     *
     * @since 26.0.0
     */
    AV_OUTPUT_FORMAT_FLV = 14
} OH_AVOutputFormat;

/**
 * @brief Enumerates the seek modes.
 * 
 * @since 10
 */
typedef enum OH_AVSeekMode {
    /**
     * @brief Seeks to the next I-frame at the specified position. If there is no I-frame after the specified position,
     * the seek operation may fail.
     * 
     * @since 10
     */
    SEEK_MODE_NEXT_SYNC = 0,

    /**
     * @brief Seeks to the previous I-frame at the specified position.
     * 
     * @since 10
     */
    SEEK_MODE_PREVIOUS_SYNC,

    /**
     * @brief seek to sync sample closest to time.
     * 
     * @since 10
     */
    SEEK_MODE_CLOSEST_SYNC
} OH_AVSeekMode;

/**
 * @brief Enumerates the scaling modes. This enum is used only in surface mode.
 * 
 * @deprecated since 14
 * @useinstead OHScalingModeV2
 * @since 10
 */
typedef enum OH_ScalingMode {
    /**
     * @brief Scales the image based on the window size.
     * @deprecated since 14
     * @useinstead OH_SCALING_MODE_SCALE_TO_WINDOW_V2
     * @since 10
     */
    SCALING_MODE_SCALE_TO_WINDOW = 1,

    /**
     * @brief Crops the image based on the window size.
     * @deprecated since 14
     * @useinstead OH_SCALING_MODE_SCALE_CROP_V2
     * @since 10
     */
    SCALING_MODE_SCALE_CROP = 2
} OH_ScalingMode;

/**
 * @brief Enumerates the number of audio bits for each coded sample.
 * 
 * @since 10
 */
typedef enum OH_BitsPerSample {
    /**
     * 8-bit unsigned integer sampling.
     * @since 10
     */
    SAMPLE_U8 = 0,

    /**
     * 16-bit signed integer sampling.
     * @since 10
     */
    SAMPLE_S16LE = 1,

    /**
     * 24-bit signed integer sampling.
     * @since 10
     */
    SAMPLE_S24LE = 2,

    /**
     * 32-bit signed integer sampling.
     * @since 10
     */
    SAMPLE_S32LE = 3,

    /**
     * 32-bit floating-point sampling.
     * @since 10
     */
    SAMPLE_F32LE = 4,

    /**
     * 8-bit unsigned integer plane sampling.
     * @since 10
     */
    SAMPLE_U8P = 5,

    /**
     * 16-bit signed integer plane sampling.
     * @since 10
     */
    SAMPLE_S16P = 6,

    /**
     * 24-bit signed integer plane sampling.
     * @since 10
     */
    SAMPLE_S24P = 7,

    /**
     * 32-bit signed integer plane sampling.
     * @since 10
     */
    SAMPLE_S32P = 8,

    /**
     * 32-bit floating-point plane sampling.
     * @since 10
     */
    SAMPLE_F32P = 9,

    /**
     * Invalid sampling format.
     * @since 10
     */
    INVALID_WIDTH = -1
} OH_BitsPerSample;

/**
 * @brief Enumerates the primary colors. This enum is used for both encoding and decoding.
 * 
 * @since 10
 */
typedef enum OH_ColorPrimary {
    /**
     * BT709 color gamut.
     * @since 10
     */
    COLOR_PRIMARY_BT709 = 1,

    /**
     * Unspecified color gamut.
     * @since 10
     */
    COLOR_PRIMARY_UNSPECIFIED = 2,

    /**
     * BT470_M color gamut.
     * @since 10
     */
    COLOR_PRIMARY_BT470_M = 4,

    /**
     * BT601_625 color gamut.
     * @since 10
     */
    COLOR_PRIMARY_BT601_625 = 5,

    /**
     * BT601_525 color gamut.
     * @since 10
     */
    COLOR_PRIMARY_BT601_525 = 6,

    /**
     * SMPTE_ST240 color gamut.
     * @since 10
     */
    COLOR_PRIMARY_SMPTE_ST240 = 7,

    /**
     * GENERIC_FILM color gamut.
     * @since 10
     */
    COLOR_PRIMARY_GENERIC_FILM = 8,

    /**
     * BT2020 color gamut.
     * @since 10
     */
    COLOR_PRIMARY_BT2020 = 9,

    /**
     * SMPTE_ST428 color gamut.
     * @since 10
     */
    COLOR_PRIMARY_SMPTE_ST428 = 10,

    /**
     * P3DCI color gamut.
     * @since 10
     */
    COLOR_PRIMARY_P3DCI = 11,

    /**
     * P3D65 color gamut.
     * @since 10
     */
    COLOR_PRIMARY_P3D65 = 12
} OH_ColorPrimary;

/**
 * @brief Enumerates the transfer characteristics. This enum is used for both encoding and decoding.
 * 
 * @since 10
 */
typedef enum OH_TransferCharacteristic {
    /**
     * BT709 transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_BT709 = 1,

    /**
     * Unspecified transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_UNSPECIFIED = 2,

    /**
     * GAMMA_2_2 transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_GAMMA_2_2 = 4,

    /**
     * GAMMA_2_8 transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_GAMMA_2_8 = 5,

    /**
     * BT601 transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_BT601 = 6,

    /**
     * SMPTE_ST240 transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_SMPTE_ST240 = 7,

    /**
     * Linear transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_LINEAR = 8,

    /**
     * Log transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_LOG = 9,

    /**
     * LOG_SQRT transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_LOG_SQRT = 10,

    /**
     * IEC_61966_2_4 transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_IEC_61966_2_4 = 11,

    /**
     * BT1361 transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_BT1361 = 12,

    /**
     * IEC_61966_2_1 transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_IEC_61966_2_1 = 13,

    /**
     * BT2020_10BIT transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_BT2020_10BIT = 14,

    /**
     * BT2020_12BIT transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_BT2020_12BIT = 15,

    /**
     * PQ transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_PQ = 16,

    /**
     * SMPTE_ST428 transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_SMPTE_ST428 = 17,

    /**
     * HLG transfer function.
     * @since 10
     */
    TRANSFER_CHARACTERISTIC_HLG = 18
} OH_TransferCharacteristic;

/**
 * @brief Enumerates the matrix coefficients. This enum is used for both encoding and decoding.
 * 
 * @since 10
 */
typedef enum OH_MatrixCoefficient {
    /**
     * Identity matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_IDENTITY = 0,

    /**
     * BT709 conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_BT709 = 1,

    /**
     * Unspecified conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_UNSPECIFIED = 2,

    /**
     * FCC conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_FCC = 4,

    /**
     * BT601_625 conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_BT601_625 = 5,

    /**
     * BT601_525 conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_BT601_525 = 6,

    /**
     * SMPTE_ST240 conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_SMPTE_ST240 = 7,

    /**
     * YCGCO conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_YCGCO = 8,

    /**
     * BT2020_NCL conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_BT2020_NCL = 9,

    /**
     * BT2020_CL conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_BT2020_CL = 10,

    /**
     * SMPTE_ST2085 conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_SMPTE_ST2085 = 11,

    /**
     * CHROMATICITY_NCL conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_CHROMATICITY_NCL = 12,

    /**
     * CHROMATICITY_CL conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_CHROMATICITY_CL = 13,

    /**
     * ICTCP conversion matrix.
     * @since 10
     */
    MATRIX_COEFFICIENT_ICTCP = 14
} OH_MatrixCoefficient;

/**
 * @brief Enumerates the AVC levels.
 * 
 * @since 12
 */
typedef enum OH_AVCLevel {
    /**
     * Level 1.
     * @since 12
     */
    AVC_LEVEL_1 = 0,

    /**
     * Level 1b.
     * @since 12
     */
    AVC_LEVEL_1b = 1,

    /**
     * Level 1.1.
     * @since 12
     */
    AVC_LEVEL_11 = 2,

    /**
     * Level 1.2.
     * @since 12
     */
    AVC_LEVEL_12 = 3,

    /**
     * Level 1.3.
     * @since 12
     */
    AVC_LEVEL_13 = 4,

    /**
     * Level 2.
     * @since 12
     */
    AVC_LEVEL_2 = 5,

    /**
     * Level 2.1.
     * @since 12
     */
    AVC_LEVEL_21 = 6,

    /**
     * Level 2.2.
     * @since 12
     */
    AVC_LEVEL_22 = 7,

    /**
     * Level 3.
     * @since 12
     */
    AVC_LEVEL_3 = 8,

    /**
     * Level 3.1.
     * @since 12
     */
    AVC_LEVEL_31 = 9,

    /**
     * Level 3.2.
     * @since 12
     */
    AVC_LEVEL_32 = 10,

    /**
     * Level 4.
     * @since 12
     */
    AVC_LEVEL_4 = 11,

    /**
     * Level 4.1.
     * @since 12
     */
    AVC_LEVEL_41 = 12,

    /**
     * Level 4.2.
     * @since 12
     */
    AVC_LEVEL_42 = 13,

    /**
     * Level 5.
     * @since 12
     */
    AVC_LEVEL_5 = 14,

    /**
     * Level 5.1.
     * @since 12
     */
    AVC_LEVEL_51 = 15,

    /**
     * Level 5.2.
     * @since 12
     */
    AVC_LEVEL_52 = 16,

    /**
     * Level 6.
     * @since 12
     */
    AVC_LEVEL_6 = 17,

    /**
     * Level 6.1.
     * @since 12
     */
    AVC_LEVEL_61 = 18,

    /**
     * Level 6.2.
     * @since 12
     */
    AVC_LEVEL_62 = 19
} OH_AVCLevel;

/**
 * @brief Enumerates the HEVC levels.
 * 
 * @since 12
 */
typedef enum OH_HEVCLevel {
    /**
     * Level 1.
     * @since 12
     */
    HEVC_LEVEL_1 = 0,

    /**
     * Level 2.
     * @since 12
     */
    HEVC_LEVEL_2 = 1,

    /**
     * Level 2.1.
     * @since 12
     */
    HEVC_LEVEL_21 = 2,

    /**
     * Level 3.
     * @since 12
     */
    HEVC_LEVEL_3 = 3,

    /**
     * Level 3.1.
     * @since 12
     */
    HEVC_LEVEL_31 = 4,

    /**
     * Level 4.
     * @since 12
     */
    HEVC_LEVEL_4 = 5,

    /**
     * Level 4.1.
     * @since 12
     */
    HEVC_LEVEL_41 = 6,

    /**
     * Level 5.
     * @since 12
     */
    HEVC_LEVEL_5 = 7,

    /**
     * Level 5.1.
     * @since 12
     */
    HEVC_LEVEL_51 = 8,

    /**
     * Level 5.2.
     * @since 12
     */
    HEVC_LEVEL_52 = 9,

    /**
     * Level 6.
     * @since 12
     */
    HEVC_LEVEL_6 = 10,

    /**
     * Level 6.1.
     * @since 12
     */
    HEVC_LEVEL_61 = 11,

    /**
     * Level 6.2.
     * @since 12
     */
    HEVC_LEVEL_62 = 12
} OH_HEVCLevel;

/**
 * @brief Enumerates the VVC levels.
 * 
 * @since 15
 */
typedef enum OH_VVCLevel {
    /**
     * Level 1.0.
     * @since 15
     */
    VVC_LEVEL_1 = 16,

    /**
     * Level 2.0.
     * @since 15
     */
    VVC_LEVEL_2 = 32,

    /**
     * Level 2.1.
     * @since 15
     */
    VVC_LEVEL_21 = 35,

    /**
     * Level 3.0.
     * @since 15
     */
    VVC_LEVEL_3 = 48,

    /**
     * Level 3.1.
     * @since 15
     */
    VVC_LEVEL_31 = 51,

    /**
     * Level 4.0.
     * @since 15
     */
    VVC_LEVEL_4 = 64,

    /**
     * Level 4.1.
     * @since 15
     */
    VVC_LEVEL_41 = 67,

    /**
     * Level 5.0.
     * @since 15
     */
    VVC_LEVEL_5 = 80,

    /**
     * Level 5.1.
     * @since 15
     */
    VVC_LEVEL_51 = 83,

    /**
     * Level 5.2.
     * @since 15
     */
    VVC_LEVEL_52 = 86,

    /**
     * Level 6.0.
     * @since 15
     */
    VVC_LEVEL_6 = 96,

    /**
     * Level 6.1.
     * @since 15
     */
    VVC_LEVEL_61 = 99,

    /**
     * Level 6.2.
     * @since 15
     */
    VVC_LEVEL_62 = 102,

    /**
     * Level 6.3.
     * @since 15
     */
    VVC_LEVEL_63 = 105,

    /**
     * Level 15.5.
     * @since 15
     */
    VVC_LEVEL_155 = 255
} OH_VVCLevel;

/**
 * @brief Enumerates the MPEG2 levels.
 * 
 * @since 17
 */
typedef enum OH_MPEG2Level {
    /**
     * Low level.
     * @since 17
     */
    MPEG2_LEVEL_LOW = 0,

    /**
     * Main level.
     * @since 17
     */
    MPEG2_LEVEL_MAIN = 1,

    /**
     * High 1440 level.
     * @since 17
     */
    MPEG2_LEVEL_HIGH_1440 = 2,

    /**
     * High level.
     * @since 17
     */
    MPEG2_LEVEL_HIGH = 3
} OH_MPEG2Level;

/**
 * @brief Enumerates the MPEG4 levels.
 * 
 * @since 17
 */
typedef enum OH_MPEG4Level {
    /**
     * Level 0.
     * @since 17
     */
    MPEG4_LEVEL_0 = 0,

    /**
     * Level 0B.
     * @since 17
     */
    MPEG4_LEVEL_0B = 1,

    /**
     * Level 1.
     * @since 17
     */
    MPEG4_LEVEL_1 = 2,

    /**
     * Level 2.
     * @since 17
     */
    MPEG4_LEVEL_2 = 3,

    /**
     * Level 3.
     * @since 17
     */
    MPEG4_LEVEL_3 = 4,

    /**
     * Level 3B.
     * @since 17
     */
    MPEG4_LEVEL_3B = 5,

    /**
     * Level 4.
     * @since 17
     */
    MPEG4_LEVEL_4 = 6,

    /**
     * Level 4A.
     * @since 17
     */
    MPEG4_LEVEL_4A = 7,

    /**
     * Level 5.
     * @since 17
     */
    MPEG4_LEVEL_5 = 8,

    /**
     * Level 6.
     * @since 17
     */
    MPEG4_LEVEL_6 = 9
} OH_MPEG4Level;

/**
 * @brief Enumerates the H.263 levels.
 * 
 * @since 17
 */
typedef enum OH_H263Level {
    /**
     * Level 10.
     * @since 17
     */
    H263_LEVEL_10 = 0,

    /**
     * Level 20.
     * @since 17
     */
    H263_LEVEL_20 = 1,

    /**
     * Level 30.
     * @since 17
     */
    H263_LEVEL_30 = 2,

    /**
     * Level 40.
     * @since 17
     */
    H263_LEVEL_40 = 3,

    /**
     * Level 45.
     * @since 17
     */
    H263_LEVEL_45 = 4,

    /**
     * Level 50.
     * @since 17
     */
    H263_LEVEL_50 = 5,

    /**
     * Level 60.
     * @since 17
     */
    H263_LEVEL_60 = 6,

    /**
     * Level 70.
     * @since 17
     */
    H263_LEVEL_70 = 7
} OH_H263Level;

/**
 * @brief Enumerates the VC-1 levels.
 * 
 * @since 22
 */
typedef enum OH_VC1Level {
    /**
     * Level L0.
     * @since 22
     */
    VC1_LEVEL_L0 = 0,

    /**
     * Level L1.
     * @since 22
     */
    VC1_LEVEL_L1 = 1,

    /**
     * Level L2.
     * @since 22
     */
    VC1_LEVEL_L2 = 2,

    /**
     * Level L3.
     * @since 22
     */
    VC1_LEVEL_L3 = 3,

    /**
     * Level L4.
     * @since 22
     */
    VC1_LEVEL_L4 = 4,

    /**
     * Low level.
     * @since 22
     */
    VC1_LEVEL_LOW = 5,

    /**
     * Medium level.
     * @since 22
     */
    VC1_LEVEL_MEDIUM = 6,

    /**
     * High level.
     * @since 22
     */
    VC1_LEVEL_HIGH = 7
} OH_VC1Level;

/**
 * @brief AV1 level.
 * 
 * @since 23
 */
typedef enum OH_AV1Level {
    /**
     * Level 2.0.
     * @since 23
     */
    AV1_LEVEL_20 = 0,

    /**
     * Level 2.1.
     * @since 23
     */
    AV1_LEVEL_21 = 1,

    /**
     * Level 2.2.
     * @since 23
     */
    AV1_LEVEL_22 = 2,

    /**
     * Level 2.3.
     * @since 23
     */
    AV1_LEVEL_23 = 3,

    /**
     * Level 3.0.
     * @since 23
     */
    AV1_LEVEL_30 = 4,

    /**
     * Level 3.1.
     * @since 23
     */
    AV1_LEVEL_31 = 5,

    /**
     * Level 3.2.
     * @since 23
     */
    AV1_LEVEL_32 = 6,

    /**
     * Level 3.3.
     * @since 23
     */
    AV1_LEVEL_33 = 7,

    /**
     * Level 4.0.
     * @since 23
     */
    AV1_LEVEL_40 = 8,

    /**
     * Level 4.1.
     * @since 23
     */
    AV1_LEVEL_41 = 9,

    /**
     * Level 4.2.
     * @since 23
     */
    AV1_LEVEL_42 = 10,

    /**
     * Level 4.3.
     * @since 23
     */
    AV1_LEVEL_43 = 11,

    /**
     * Level 5.0.
     * @since 23
     */
    AV1_LEVEL_50 = 12,

    /**
     * Level 5.1.
     * @since 23
     */
    AV1_LEVEL_51 = 13,

    /**
     * Level 5.2.
     * @since 23
     */
    AV1_LEVEL_52 = 14,

    /**
     * Level 5.3.
     * @since 23
     */
    AV1_LEVEL_53 = 15,

    /**
     * Level 6.0.
     * @since 23
     */
    AV1_LEVEL_60 = 16,

    /**
     * Level 6.1.
     * @since 23
     */
    AV1_LEVEL_61 = 17,

    /**
     * Level 6.2.
     * @since 23
     */
    AV1_LEVEL_62 = 18,

    /**
     * Level 6.3.
     * @since 23
     */
    AV1_LEVEL_63 = 19,

    /**
     * Level 7.0.
     * @since 23
     */
    AV1_LEVEL_70 = 20,

    /**
     * Level 7.1.
     * @since 23
     */
    AV1_LEVEL_71 = 21,

    /**
     * Level 7.2.
     * @since 23
     */
    AV1_LEVEL_72 = 22,

    /**
     * Level 7.3.
     * @since 23
     */
    AV1_LEVEL_73 = 23
} OH_AV1Level;

/**
 * @brief VP9 level.
 * 
 * @since 23
 */
typedef enum OH_VP9Level {
    /**
     * Level 1.
     * @since 23
     */
    VP9_LEVEL_1 = 0,

    /**
     * Level 1.1.
     * @since 23
     */
    VP9_LEVEL_11 = 1,

    /**
     * Level 2.
     * @since 23
     */
    VP9_LEVEL_2 = 2,

    /**
     * Level 2.1.
     * @since 23
     */
    VP9_LEVEL_21 = 3,

    /**
     * Level 3.
     * @since 23
     */
    VP9_LEVEL_3 = 4,

    /**
     * Level 3.1.
     * @since 23
     */
    VP9_LEVEL_31 = 5,

    /**
     * Level 4.
     * @since 23
     */
    VP9_LEVEL_4 = 6,

    /**
     * Level 4.1.
     * @since 23
     */
    VP9_LEVEL_41 = 7,

    /**
     * Level 5.
     * @since 23
     */
    VP9_LEVEL_5 = 8,

    /**
     * Level 5.1.
     * @since 23
     */
    VP9_LEVEL_51 = 9,

    /**
     * Level 5.2.
     * @since 23
     */
    VP9_LEVEL_52 = 10,

    /**
     * Level 6.
     * @since 23
     */
    VP9_LEVEL_6 = 11,

    /**
     * Level 6.1.
     * @since 23
     */
    VP9_LEVEL_61 = 12,

    /**
     * Level 6.2.
     * @since 23
     */
    VP9_LEVEL_62 = 13
} OH_VP9Level;

/**
 * @brief WVC1 level.
 * 
 * @since 23
 */
typedef enum OH_WVC1Level {
    /**
     * Level L0.
     * @since 23
     */
    WVC1_LEVEL_L0 = 0,

    /**
     * Level L1.
     * @since 23
     */
    WVC1_LEVEL_L1 = 1,

    /**
     * Level L2.
     * @since 23
     */
    WVC1_LEVEL_L2 = 2,

    /**
     * Level L3.
     * @since 23
     */
    WVC1_LEVEL_L3 = 3,

    /**
     * Level L4.
     * @since 23
     */
    WVC1_LEVEL_L4 = 4
} OH_WVC1Level;

/**
 * @brief Enumerates the WMV3 levels.
 * 
 * @since 22
 */
typedef enum OH_WMV3Level {
    /**
     * Low level.
     * @since 22
     */
    WMV3_LEVEL_LOW = 0,

    /**
     * Medium level.
     * @since 22
     */
    WMV3_LEVEL_MEDIUM = 1,

    /**
     * High level.
     * @since 22
     */
    WMV3_LEVEL_HIGH = 2
} OH_WMV3Level;

/**
 * @brief Enumerates the reference modes of temporal image groups.
 * 
 * @since 12
 */
typedef enum OH_TemporalGopReferenceMode {
    /**
     * Refers to the nearest short-term reference frame.
     * @since 12
     */
    ADJACENT_REFERENCE = 0,

    /**
     * Refers to the latest LTR frame.
     * @since 12
     */
    JUMP_REFERENCE = 1,

    /**
     * Uniformly scaled reference structure, which has even distribution of video frames after drop the highest
     * enhance layer. The temporal group of pictures must be power of 2.
     * @since 12
     */
    UNIFORMLY_SCALED_REFERENCE = 2
} OH_TemporalGopReferenceMode;

/**
 * @brief Enumerates the bit rate modes of an encoder.
 * 
 * @since 10
 */
typedef enum OH_BitrateMode {
    /**
     * Constant bit rate.
     * @since 10
     */
    BITRATE_MODE_CBR = 0,

    /**
     * Variable bit rate.
     * @since 10
     */
    BITRATE_MODE_VBR = 1,

    /**
     * Constant quality.
     * @since 10
     */
    BITRATE_MODE_CQ = 2,

    /**
     * Stable Quality RateControl.
     * @since 20
     */
    BITRATE_MODE_SQR = 3,

    /**
     * @brief CBR for High Quality.
     * 
     * @since 26.0.0
     */
    BITRATE_MODE_CBR_HIGH_QUALITY = 4
} OH_BitrateMode;

/**
 * @brief The video decoding frame retention mode.
 *
 * @since 26.0.0
 */
typedef enum OH_FRAME_RETENTION_MODE {
    /**
     * @brief Full frame retention mode. The decoder operates in a transparent passthrough state,
     * retaining 100% of the input frames and effectively disabling the frame dropping feature.
     * All underlying visual perception algorithms are completely bypassed, resulting in
     * zero algorithmic overhead.
     * 
     * @since 26.0.0
     */
    OH_FRAME_RETENTION_MODE_FULL = 0,

    /**
     * @brief Adaptive frame retention mode. The decoder dynamically analyzes video characteristics to drop frames with
     * the least perceptual impact, preserving visual smoothness with minimal degradation to the playback experience.
     * For optimal algorithmic accuracy, it is highly recommended to explicitly configure
     * the current playback speed via {@link OH_MD_KEY_VIDEO_DECODER_SPEED}.
     * 
     * @since 26.0.0
     */
    OH_FRAME_RETENTION_MODE_ADAPTIVE = 1,

    /**
     * @brief Uniform frame retention mode. Retains frames evenly according to a user-configured retention ratio
     * (configured via {@link OH_MD_KEY_VIDEO_DECODER_FRAME_RETENTION_RATIO}).
     * If the retention ratio is not explicitly configured, the decoder limits the output to a maximum of 30 fps.
     * @since 26.0.0
     */
    OH_FRAME_RETENTION_MODE_UNIFORM = 2
} OH_FRAME_RETENTION_MODE;

#ifdef __cplusplus
}
#endif
#endif // NATIVE_AVCODEC_BASE_H

/** @} */