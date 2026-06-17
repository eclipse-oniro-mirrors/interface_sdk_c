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
 * @brief The file declares the constants used by the AVMetadataExtractor.
 * 
 * @kit MediaKit
 * @library libavmetadata_extractor.so
 * @since 18
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_BASE_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_BASE_H

#include <stdint.h>

#include "native_avformat.h"
#include "multimedia/image_framework/image/pixelmap_native.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the result status of the frame extraction operation.
 * 
 * @since 23
 */
typedef enum OH_AVMetadataExtractor_FetchState {
    /**
     * The extraction operation failed.
     */
    OH_AVMETADATA_EXTRACTOR_FETCH_FAILED = 0,

    /**
     * The extraction operation succeeded.
     */
    OH_AVMETADATA_EXTRACTOR_FETCH_SUCCEEDED = 1,

    /**
     * The extraction operation was canceled by the user.
     */
    OH_AVMETADATA_EXTRACTOR_FETCH_CANCELED = 2,
} OH_AVMetadataExtractor_FetchState;

/**
 * @brief Defines a struct for the output parameters of a frame extracted by **AVMetadataExtractor**.
 * 
 * @since 23
 */
typedef struct OH_AVMetadataExtractor_OutputParam OH_AVMetadataExtractor_OutputParam;

/**
 * @brief Defines the information about a frame extracted from a video.
 * 
 * @since 23
 */
typedef struct OH_AVMetadataExtractor_FrameInfo {
    /**
     * Time when the user sends the request.
     */
    int64_t requestTimeUs;

    /**
     * Time when the frame is actually extracted. If the extraction fails, the value is **-1**.
     */
    int64_t actualTimeUs;

    /**
     * Frame image extracted from the video. If the extraction fails, the value is a null pointer.
     */
    OH_PixelmapNative* image;

    /**
     * Result status of the frame extraction operation.
     */
    OH_AVMetadataExtractor_FetchState result;
} OH_AVMetadataExtractor_FrameInfo;

/**
 * @brief Pointer to the key for obtaining the title of the album. The value type is const char*.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_ALBUM = "album";

/**
 * @brief Pointer to the key for obtaining the artist of the album. The value type is const char*.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_ALBUM_ARTIST = "albumArtist";

/**
 * @brief Pointer to the key for obtaining the artist of the media asset. The value type is const char*.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_ARTIST = "artist";

/**
 * @brief Pointer to the key for obtaining the author of the media asset. The value type is const char*.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_AUTHOR = "author";

/**
 * @brief Pointer to the key for obtaining the creation time of the media asset. The value type is const char*.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_DATE_TIME = "dateTime";

/**
 * @brief Pointer to the key for obtaining the creation time of the media asset. The value type is const char* and the
 * output format is YYYY-MM-DD HH:mm:ss.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_DATE_TIME_FORMAT = "dateTimeFormat";

/**
 * @brief Pointer to the key for obtaining the composer of the media asset. The value type is const char*.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_COMPOSER = "composer";

/**
 * @brief Pointer to the key for obtaining the duration of the media asset, in ms. The value type is int64_t.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_DURATION = "duration";

/**
 * @brief Pointer to the key for obtaining the type or genre of the media asset. The value type is const char*.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_GENRE = "genre";

/**
 * @brief Pointer to the key for obtaining the flag indicating whether the media asset contains audio. The value type
 * is int32_t.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_HAS_AUDIO = "hasAudio";

/**
 * @brief Pointer to the key for obtaining the flag indicating whether the media asset contains video. The value type
 * is int32_t.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_HAS_VIDEO = "hasVideo";

/**
 * @brief Pointer to the key for obtaining the MIME type of the media asset. The value type is const char*, for example,
 *  video/mp4, audio/mp4, and audio/amr wb.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_MIME_TYPE = "mimeType";

/**
 * @brief Pointer to the key for obtaining the number of tracks of the media asset. The value type is int32_t.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_TRACK_COUNT = "trackCount";

/**
 * @brief Pointer to the key for obtaining the audio sample rate, in Hz. The value type is int32_t.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_SAMPLE_RATE = "sampleRate";

/**
 * @brief Pointer to the key for obtaining the title of the media asset. The value type is const char*.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_TITLE = "title";

/**
 * @brief Pointer to the key for obtaining the video height, in px. The value type is int32_t.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_VIDEO_HEIGHT = "videoHeight";

/**
 * @brief Pointer to the key for obtaining the video weight, in px. The value type is int32_t.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_VIDEO_WIDTH = "videoWidth";

/**
 * @brief Pointer to the key for obtaining the video rotation direction, in degrees (°). The value type is int32_t.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_VIDEO_ORIENTATION = "videoOrientation";

/**
 * @brief Pointer to the key for obtaining the flag indicating whether the video is an HDR Vivid video. The value type
 * is int32_t.
 * For details, see {@link OH_Core_HdrType} in **media_types.h**.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_VIDEO_IS_HDR_VIVID = "hdrType";

/**
 * @brief Pointer to the key for obtaining the latitude in the geographical location. The value type is float.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_LOCATION_LATITUDE = "latitude";

/**
 * @brief Pointer to the key for obtaining the longitude in the geographical location. The value type is float.
 * 
 * @since 18
 */
static const char* OH_AVMETADATA_EXTRACTOR_LOCATION_LONGITUDE = "longitude";

#ifdef __cplusplus
}
#endif
#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETADATA_EXTRACTOR_BASE_H
/** @} */
