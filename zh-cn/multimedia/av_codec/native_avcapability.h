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
 * @addtogroup AVCapability
 * @{
 *
 * @brief AVCapability模块提供用于编解码能力查询的函数。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */

/**
 * @file native_avcapability.h
 *
 * @brief 声明用于编解码能力查询到的Native API。
 * @sample [AVCodec](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/BasicFeature/Media/AVCodec)
 *
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avcapability.h>
 * @library libnative_media_codecbase.so
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */

#ifndef NATIVE_AVCAPABILITY_H
#define NATIVE_AVCAPABILITY_H

#include <stdint.h>
#include "native_averrors.h"
#include "native_avformat.h"
#include "native_avcodec_base.h"
#include "native_buffer.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 为OH_AVCapability接口定义native层对象。
 *
 * @since 10
 */
typedef struct OH_AVCapability OH_AVCapability;

/**
 * @brief 范围包含最小值和最大值。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
typedef struct OH_AVRange {
    /**最小值。 */
    int32_t minVal;
    /**最大值。 */
    int32_t maxVal;
} OH_AVRange;

/**
 * @brief 编解码器类别。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 10
 */
typedef enum OH_AVCodecCategory {
    /** 硬件编解码。 */
    HARDWARE = 0,
    /** 软件编解码。 */
    SOFTWARE
} OH_AVCodecCategory;

/**
 * @brief 编解码器类型。
 *
 * @since 24
 */
typedef enum OH_AVCodecType {
    /**
     * @brief 表示视频编码器。
     * @since 24
     */
    OH_AVCODEC_TYPE_VIDEO_ENCODER = 0,
    /**
     * @brief 表示视频解码器。
     * @since 24
     */
    OH_AVCODEC_TYPE_VIDEO_DECODER = 1,
    /**
     * @brief 表示音频编码器。
     * @since 24
     */
    OH_AVCODEC_TYPE_AUDIO_ENCODER = 2,
    /**
     * @brief 表示音频解码器。
     * @since 24
     */
    OH_AVCODEC_TYPE_AUDIO_DECODER = 3
} OH_AVCodecType;

/**
 * @brief 可以在特定编解码器场景中使用的可选特性。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 12
 */
typedef enum OH_AVCapabilityFeature {
    /** 编解码器支持时域可分层特性，只用于视频编码场景。 */
    VIDEO_ENCODER_TEMPORAL_SCALABILITY = 0,
    /** 编解码器支持长期参考帧特性，只用于视频编码场景。 */
    VIDEO_ENCODER_LONG_TERM_REFERENCE = 1,
    /** 编解码器支持低时延特性，只用于视频解码场景。 */
    VIDEO_LOW_LATENCY = 2,
    /** 编解码器支持B帧特性，只用于视频编码场景。
     * @since 20
     */
    VIDEO_ENCODER_B_FRAME = 7,
    /**
    * @brief 解码器支持按解码顺序输出帧特性，只用于视频解码场景。
    *
    * @since 26.0.0
    */
    VIDEO_DECODER_OUTPUT_IN_DECODING_ORDER = 8,
    /**
     * @brief 编码器支持视频编码前处理降采样特性，该能力仅适用于视频编码器。
     *
     * @note 仅当编码器通过{@link OH_VideoEncoder_CreatePrimaryWithPreproc}
     * 或{@link OH_VideoEncoder_CreateSecondaryFromPrimary}接口创建时，方可启用该能力。
     * @since 26.0.0
     */
    VIDEO_ENCODER_PREPROC_DOWNSAMPLING = 9,
    /**
     * @brief 编码器支持视频编码前处理裁剪特性，该特性仅适用于视频编码器。
     *
     * @note 仅当编码器通过{@link OH_VideoEncoder_CreatePrimaryWithPreproc}
     * 或{@link OH_VideoEncoder_CreateSecondaryFromPrimary}接口创建时，方可启用该能力。
     * @since 26.0.0
     */
    VIDEO_ENCODER_PREPROC_CROP = 10,
} OH_AVCapabilityFeature;

/**
 * @brief 获取系统推荐的编解码器能力。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param mime MIME类型描述字符串，请参阅{@link AVCODEC_MIME_TYPE}。
 * @param isEncoder 编码器为true，解码器为false。
 * @return 如果现有编解码器匹配，则返回能力实例，如果指定的MIME类型与任何现有编解码器不匹配，则返回NULL。
 * @since 10
 */
OH_AVCapability *OH_AVCodec_GetCapability(const char *mime, bool isEncoder);

/**
 * @brief 获取指定类别中的编解码器能力。
 * 通过指定类别，匹配的编解码器仅限于硬件编解码器或软件编解码器。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param mime MIME类型描述字符串，请参阅{@link AVCODEC_MIME_TYPE}。
 * @param isEncoder 编码器为true，解码器为false。
 * @param category 编解码器类别。
 * @return 如果现有编解码器匹配，则返回能力实例，如果指定的MIME类型与任何现有编解码器不匹配，则返回NULL。
 * @since 10
 */
OH_AVCapability *OH_AVCodec_GetCapabilityByCategory(const char *mime, bool isEncoder, OH_AVCodecCategory category);

/**
 * @brief 获取指定编解码器类型的能力列表。
 *
 * 此功能会根据提供的编解码器类型检索出系统支持的所有匹配的编解码器能力。
 * @note 编解码器能力列表的内存由系统底层全局维护，调用者无需管理其生命周期，不得手动分配或释放此内存。
 * @param codecType 指定要查询的编解码器类型。
 * @param count 输出参数。指向一个uint32_t变量的指针，用于存储匹配到的编解码器能力数量。
 * @return 如果找到匹配项，则返回指向OH_AVCapability实例数组的指针。\n
 *         如果未找到匹配的编解码器或发生错误，则返回NULL。
 * @since 24
 */
OH_AVCapability **OH_AVCodec_GetCapabilityList(OH_AVCodecType codecType, uint32_t *count);

/**
 * @brief 检查能力实例是否描述了硬件编解码器。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 编解码能力指针。
 * @return 如果能力实例描述的是硬件编解码器，则返回true，如果功能实例描述的是软件编解码器，则为false。
 * @since 10
 */
bool OH_AVCapability_IsHardware(OH_AVCapability *capability);

/**
 * @brief 检查能力实例是否描述了一个安全解码器。
 *
 * @param capability 编解码能力指针。
 * @return 如果能力实例描述的是安全解码器，则返回true。\n
 *         如果能力实例描述的是非安全解码器，则为false。
 * @since 24
 */
bool OH_AVCapability_IsSecure(OH_AVCapability *capability);

/**
 * @brief 获取编解码器名称。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 编解码能力指针。
 * @return 返回编解码器名称字符串。
 * @since 10
 */
const char *OH_AVCapability_GetName(OH_AVCapability *capability);

/**
 * @brief 获取编解码器的MIME类型。
 *
 * @param capability 编解码能力指针。
 * @return 返回编解码器的MIME类型字符串。
 * @since 24
 */
const char *OH_AVCapability_GetMimeType(OH_AVCapability *capability);

/**
 * @brief 检查编解码器的MIME类型是否与指定的MIME类型匹配。
 *
 * @param capability 编解码能力指针。
 * @param mimeType 要检查的目标MIME类型字符串。
 * @return 如果MIME类型匹配则返回true，否则返回false。
 * @since 24
 */
bool OH_AVCapability_CheckMimeType(OH_AVCapability *capability, const char *mimeType);

/**
 * @brief 获取编解码器支持的最大实例数。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 编解码能力指针。
 * @return 返回支持的最大编解码器实例数。
 * @since 10
 */
int32_t OH_AVCapability_GetMaxSupportedInstances(OH_AVCapability *capability);

/**
 * @brief 获取编码器支持的比特率范围。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 编码器能力指针。如果给的是解码器能力指针，会导致未定义行为。
 * @param bitrateRange 输出参数。编码器码率范围。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向编码器码率范围的指针为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetEncoderBitrateRange(OH_AVCapability *capability, OH_AVRange *bitrateRange);

/**
 * @brief 检查编码器是否支持特定的比特率模式。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 编码器能力指针。如果给的是解码器能力指针，会导致未定义行为。
 * @param bitrateMode 比特率模式。
 * @return 如果支持该比特率模式，则返回true；如果不支持该比特率模式，则返回false。
 * @since 10
 */
bool OH_AVCapability_IsEncoderBitrateModeSupported(OH_AVCapability *capability, OH_BitrateMode bitrateMode);

/**
 * @brief 获取编码器支持的质量范围。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 编码器能力指针。如果给的是解码器能力指针，会导致未定义行为。
 * @param qualityRange 输出参数。编码器质量范围。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向编码器质量范围的指针为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetEncoderQualityRange(OH_AVCapability *capability, OH_AVRange *qualityRange);

/**
 * @brief 获取编码器支持的编码器复杂性范围。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 编码器能力指针。如果给的是解码器能力指针，会导致未定义行为。
 * @param complexityRange 输出参数。编码器复杂度范围。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向编码器复杂度范围的指针为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetEncoderComplexityRange(OH_AVCapability *capability, OH_AVRange *complexityRange);

/**
 * @brief 获取音频编解码器支持的采样率。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 音频编解码能力指针。如果给的是视频编解码器能力指针，会导致未定义行为。
 * @param sampleRates 输出参数。指向采样率数组的指针。
 * @param sampleRateNum 输出参数。采样率数组的元素数目。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向采样率数组的指针为空指针，或者指向采样率数组的元素数目的指针为空指针。\n
 * AV_ERR_UNKNOWN：未知错误。\n
 * AV_ERR_NO_MEMORY：内部使用内存分配失败。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetAudioSupportedSampleRates(OH_AVCapability *capability, const int32_t **sampleRates,
                                                          uint32_t *sampleRateNum);

/**
 * @brief 获取音频编解码器支持的采样率范围。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 音频编解码能力指针。如果给的是视频编解码器能力指针，会导致未定义行为。
 * @param sampleRateRanges 输出参数。指向采样率范围数组的指针。
 * @param rangesNum 输出参数。采样率范围数组的元素数目。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向采样率范围数组的指针为空指针，或者指向采样率范围数组的元素数目的指针为空指针。\n
 * AV_ERR_UNKNOWN：未知错误。\n
 * AV_ERR_NO_MEMORY：内部使用内存分配失败。
 * @since 20
 */
OH_AVErrCode OH_AVCapability_GetAudioSupportedSampleRateRanges(OH_AVCapability *capability,
                                                               OH_AVRange **sampleRateRanges, uint32_t *rangesNum);

/**
 * @brief 获取音频编解码器支持的音频通道计数范围。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 音频编解码能力指针。如果给的是视频编解码器能力指针，会导致未定义行为。
 * @param channelCountRange 输出参数。音频通道计数范围。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向音频通道计数范围的指针为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetAudioChannelCountRange(OH_AVCapability *capability, OH_AVRange *channelCountRange);

/**
 * @brief 获取视频编解码器支持的视频宽度对齐。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 视频编解码能力指针。如果给的是音频编解码器能力指针，会导致未定义行为。
 * @param widthAlignment 输出参数。视频宽度对齐。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向视频宽度对齐的指针为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetVideoWidthAlignment(OH_AVCapability *capability, int32_t *widthAlignment);

/**
 * @brief 获取视频编解码器支持的视频高度对齐。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 视频编解码能力指针。如果给的是音频编解码器能力指针，会导致未定义行为。
 * @param heightAlignment 输出参数。视频高度对齐。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向视频高度对齐的指针为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetVideoHeightAlignment(OH_AVCapability *capability, int32_t *heightAlignment);

/**
 * @brief 获取指定高度情况下视频编解码器支持的视频宽度范围。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 视频编解码能力指针。如果给的是音频编解码器能力指针，会导致未定义行为。
 * @param height 视频垂直像素数。
 * @param widthRange 输出参数。视频宽度范围。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者高度不在通过{@link OH_AVCapability_GetVideoHeightRange}获取支持的高度范围中，或者指向宽度范围的指针为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetVideoWidthRangeForHeight(OH_AVCapability *capability, int32_t height,
                                                         OH_AVRange *widthRange);

/**
 * @brief 获取指定宽度情况下视频编解码器支持的视频高度范围。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 视频编解码能力指针。如果给的是音频编解码器能力指针，会导致未定义行为。
 * @param width 视频水平像素数。
 * @param heightRange 输出参数。视频高度范围。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者宽度不在通过{@link OH_AVCapability_GetVideoWidthRange}获取支持的宽度范围中，或者指向高度范围的指针为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetVideoHeightRangeForWidth(OH_AVCapability *capability, int32_t width,
                                                         OH_AVRange *heightRange);

/**
 * @brief 获取视频编解码器支持的视频宽度范围。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 视频编解码能力指针。如果给的是音频编解码器能力指针，会导致未定义行为。
 * @param widthRange 输出参数。视频宽度范围。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向视频宽度范围的指针为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetVideoWidthRange(OH_AVCapability *capability, OH_AVRange *widthRange);

/**
 * @brief 获取视频编解码器支持的视频高度范围。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 视频编解码能力指针。如果给的是音频编解码器能力指针，会导致未定义行为。
 * @param heightRange 输出参数。视频高度范围。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向视频高度范围的指针为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetVideoHeightRange(OH_AVCapability *capability, OH_AVRange *heightRange);

/**
 * @brief 检查视频编解码器是否支持特定的视频大小。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 视频编解码能力指针。如果给的是音频编解码器能力指针，会导致未定义行为。
 * @param width 视频水平像素数。
 * @param height 视频垂直像素数。
 * @return 如果支持该视频大小，则返回true，如果不支持该视频大小，则返回false。
 * @since 10
 */
bool OH_AVCapability_IsVideoSizeSupported(OH_AVCapability *capability, int32_t width, int32_t height);

/**
 * @brief 获取视频编解码器支持的视频帧率范围。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 视频编解码能力指针。如果给的是音频编解码器能力指针，会导致未定义行为。
 * @param frameRateRange 输出参数。视频帧率范围。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向视频帧率范围的指针为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetVideoFrameRateRange(OH_AVCapability *capability, OH_AVRange *frameRateRange);

/**
 * @brief 获取指定视频大小的视频编解码器支持的视频帧率范围。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 视频编解码能力指针。如果给的是音频编解码器能力指针，会导致未定义行为。
 * @param width 视频水平像素数。
 * @param height 视频垂直像素数。
 * @param frameRateRange 输出参数。视频帧率范围。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者宽度和高度组合不支持，或者指向帧率范围的指针为空指针。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetVideoFrameRateRangeForSize(OH_AVCapability *capability, int32_t width, int32_t height,
                                                           OH_AVRange *frameRateRange);

/**
 * @brief 检查视频编解码器是否支持视频大小和帧率的特定组合。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 视频编解码能力指针。如果给的是音频编解码器能力指针，会导致未定义行为。
 * @param width 视频水平像素数。
 * @param height 视频垂直像素数。
 * @param frameRate 每秒帧数。
 * @return 如果支持视频大小和帧率的组合，则返回true。如果不支持，则为false。
 * @since 10
 */
bool OH_AVCapability_AreVideoSizeAndFrameRateSupported(OH_AVCapability *capability, int32_t width, int32_t height,
                                                       int32_t frameRate);

/**
 * @brief 获取视频编解码器支持的视频像素格式。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 视频编解码能力指针。如果给的是音频编解码器能力指针，会导致未定义行为。
 * @param pixelFormats 输出参数。指向视频像素格式数组的指针。
 * @param pixelFormatNum 输出参数。像素格式数组的元素数目。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向视频像素格式数组的指针为空指针，或者指向像素格式数组的元素数目的指针为空指针。\n
 * AV_ERR_UNKNOWN：未知错误。\n
 * AV_ERR_NO_MEMORY：内部使用内存分配失败。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetVideoSupportedPixelFormats(OH_AVCapability *capability, const int32_t **pixelFormats,
                                                           uint32_t *pixelFormatNum);

/**
 *
 * @brief 获取视频编解码器支持的OH_NativeBuffer格式。
 *
 * 该函数提供了视频编解码器能够处理的OH_NativeBuffer格式信息，具体取值可见OH_NativeBuffer_Format。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 视频编解码能力指针。
 * @param nativeBufferFormats 输出参数。指向OH_NativeBuffer_Format数组的指针。
 * @param nativeBufferFormatNum 输出参数。OH_NativeBuffer_Format数组的元素数目。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：能力实例无效、能力实例是音频编码解码器能力、指向NativeBuffer格式数组的指针为空指针、
 * 或指向NativeBuffer格式数组的元素数目的指针为空指针。\n
 *         AV_ERR_UNKNOWN：未知错误。\n
 *         AV_ERR_NO_MEMORY：内部使用内存分配失败。
 * @since 22
 */
OH_AVErrCode OH_AVCapability_GetVideoSupportedNativeBufferFormats(OH_AVCapability *capability,
                                                                  const OH_NativeBuffer_Format **nativeBufferFormats,
                                                                  uint32_t *nativeBufferFormatNum);

/**
 * @brief 获取编解码器支持的档次。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 编解码能力指针。
 * @param profiles 输出参数。指向档次数组的指针。
 * @param profileNum 输出参数。档次数组的元素数目。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者指向档次数组的指针为空指针，或者指向档次数组的元素数目的指针为空指针。\n
 * AV_ERR_UNKNOWN：未知错误。\n
 * AV_ERR_NO_MEMORY：内部使用内存分配失败。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetSupportedProfiles(OH_AVCapability *capability, const int32_t **profiles,
                                                  uint32_t *profileNum);

/**
 * @brief 获取特定档次支持的编解码器级别。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 编解码能力指针。
 * @param profile 编解码器档次。
 * @param levels 输出参数。指向级别数组的指针。
 * @param levelNum 输出参数。级别数组的元素数目。
 * @return AV_ERR_OK：执行成功。\n
 * AV_ERR_INVALID_VAL：能力实例无效，或者档次不在通过{@link OH_AVCapability_GetSupportedProfiles}获取支持的档次数组中，
 * 或者指向级别数组的指针为空指针，或者指向级别数组的元素数目的指针为空指针。\n
 * AV_ERR_UNKNOWN：未知错误。\n
 * AV_ERR_NO_MEMORY：内部使用内存分配失败。
 * @since 10
 */
OH_AVErrCode OH_AVCapability_GetSupportedLevelsForProfile(OH_AVCapability *capability, int32_t profile,
                                                          const int32_t **levels, uint32_t *levelNum);

/**
 * @brief 检查编解码器是否支持档次和级别的特定组合。
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 编解码能力指针。
 * @param profile 编解码器档次。
 * @param level 编解码器级别。
 * @return 如果支持档次和级别的组合，则返回true。如果不支持，则为false。
 * @since 10
 */
bool OH_AVCapability_AreProfileAndLevelSupported(OH_AVCapability *capability, int32_t profile, int32_t level);

/**
 * @brief 检查编解码器是否支持指定特性。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 编解码能力指针。
 * @param feature 编解码特性。
 * @return 如果支持该特性，则返回true。如果不支持，则为false。
 * @since 12
 */
bool OH_AVCapability_IsFeatureSupported(OH_AVCapability *capability, OH_AVCapabilityFeature feature);

/**
 * @brief 获取指定特性的属性。
 * 需要注意的是，返回值指向的OH_AVFormat实例的生命周期需要调用者手动释放。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @param capability 编解码能力指针。
 * @param feature 编解码特性。
 * @return 返回指向OH_AVFormat实例的指针。
 * @since 12
 */
OH_AVFormat *OH_AVCapability_GetFeatureProperties(OH_AVCapability *capability, OH_AVCapabilityFeature feature);

#ifdef __cplusplus
}
#endif
#endif // NATIVE_AVCAPABILITY_H
/** @} */