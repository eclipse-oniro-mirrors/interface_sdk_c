/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup AVMetadataExtractor
 * @{
 *
 * @brief Provides APIs of metadata capability for Media Source.
 *
 * @syscap SystemCapability.Multimedia.Media.AVMetadataExtractor
 * @since 18
 */
/**
 * @file avmetadata_extractor_base.h
 *
 * @brief 定义AVMetadataExtractor常量。
 * 
 * @kit MediaKit
 * @library libavmetadata_extractor.so
 * @since 18
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_BASE_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_BASE_H

#include <stdint.h>

#include "native_avformat.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 枚举帧提取操作的结果状态。
 * 
 * @since 23
 */
typedef enum OH_AVMetadataExtractor_FetchState {
    /**
     * 提取操作失败。
     */
    OH_AVMETADATA_EXTRACTOR_FETCH_FAILED = 0,

    /**
     * 提取操作成功。
     */
    OH_AVMETADATA_EXTRACTOR_FETCH_SUCCEEDED = 1,

    /**
     * 提取操作被用户取消。
     */
    OH_AVMETADATA_EXTRACTOR_FETCH_CANCELED = 2,
} OH_AVMetadataExtractor_FetchState;

/**
 * @brief 定义由AVMetadataExtractor提取的帧的输出参数。
 * 
 * @since 23
 */
typedef struct OH_AVMetadataExtractor_OutputParam OH_AVMetadataExtractor_OutputParam;

/**
 * @brief 定义从视频中提取出的帧的信息。
 * 
 * @since 23
 */
typedef struct OH_AVMetadataExtractor_FrameInfo {
    /**
     * 用户传入的请求时间。
     */
    int64_t requestTimeUs;

    /**
     * 实际提取到的帧的时间；若提取失败，则为-1。
     */
    int64_t actualTimeUs;

    /**
     * 从视频中提取出的帧图像；若提取失败，则为空指针。
     */
    OH_PixelmapNative* image;

    /**
     * 本次帧提取操作的结果状态。
     */
    OH_AVMetadataExtractor_FetchState result;
} OH_AVMetadataExtractor_FrameInfo;

/**
 * @brief 获取专辑标题的关键字，对应值类型为const char*。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_ALBUM = "album";

/**
 * @brief 获取专辑艺术家的关键字，对应值类型为const char*。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_ALBUM_ARTIST = "albumArtist";

/**
 * @brief 获取媒体资源艺术家的关键字，对应值类型为const char*。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_ARTIST = "artist";

/**
 * @brief 获取媒体资源作者的关键字，对应值类型为const char*。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_AUTHOR = "author";

/**
 * @brief 获取媒体资源创建时间的关键字，对应值类型为const char*。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_DATE_TIME = "dateTime";

/**
 * @brief 获取媒体资源创建时间的关键字，对应值类型为const char*，按YYYY-MM-DD HH:mm:ss格式输出。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_DATE_TIME_FORMAT = "dateTimeFormat";

/**
 * @brief 获取媒体资源作曲家的关键字，对应值类型为const char*。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_COMPOSER = "composer";

/**
 * @brief 获取媒体资源时长的关键字，对应值类型为int64_t，单位为毫秒（ms）。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_DURATION = "duration";

/**
 * @brief 获取媒体资源类型或体裁的关键字，对应值类型为const char*。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_GENRE = "genre";

/**
 * @brief 获取媒体资源是否包含音频的关键字，对应值类型为int32_t。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_HAS_AUDIO = "hasAudio";

/**
 * @brief 获取媒体资源是否包含视频的关键字，对应值类型为int32_t。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_HAS_VIDEO = "hasVideo";

/**
 * @brief 获取媒体资源mime类型的关键字，对应值类型为const char*，例如：“video/mp4”、“audio/mp4”和“audio/amr wb”。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_MIME_TYPE = "mimeType";

/**
 * @brief 获取媒体资源轨道数量的关键字，对应值类型为int32_t。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_TRACK_COUNT = "trackCount";

/**
 * @brief 获取音频采样率的关键字，对应值类型为int32_t，单位为赫兹（Hz）。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_SAMPLE_RATE = "sampleRate";

/**
 * @brief 获取媒体资源标题的关键字，对应值类型为const char*。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_TITLE = "title";

/**
 * @brief 获取视频高度的关键字，对应值类型为int32_t，单位为像素。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_VIDEO_HEIGHT = "videoHeight";

/**
 * @brief 获取视频宽度的关键字，对应值类型为int32_t，单位为像素。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_VIDEO_WIDTH = "videoWidth";

/**
 * @brief 获取视频旋转方向的关键字，对应值类型为int32_t，单位为度（°）。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_VIDEO_ORIENTATION = "videoOrientation";

/**
 * @brief 获取是否是HDR Vivid视频的关键字，对应值类型为int32_t。
 * 详情请参阅media_types.h中的{@link OH_Core_HdrType}。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_VIDEO_IS_HDR_VIVID = "hdrType";

/**
 * @brief 获取地理位置中的纬度值的关键字，对应值类型为float。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_LOCATION_LATITUDE = "latitude";

/**
 * @brief 获取地理位置中的经度值的关键字，对应值类型为float。
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_LOCATION_LONGITUDE = "longitude";

#ifdef __cplusplus
}
#endif
#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_BASE_H
/** @} */
