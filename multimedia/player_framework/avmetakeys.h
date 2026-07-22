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
 * @addtogroup AVMediaBase
 * @{
 *
 * @brief Defines the avmetakeys.
 *
 * @since 23
 */
/**
 * @file avmetakeys.h
 *
 * @brief Defines audio and video metadata keys.
 * 
 * @kit MediaKit
 * @library libavmedia_base.so
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 23
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETAKEYS_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETAKEYS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Track index. The value type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_TRACK_INDEX;

/**
 * @brief Track type. The value type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_TRACK_TYPE;

/**
 * @brief MIME type of the codec. The value type is string.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_MIME_TYPE;

/**
 * @brief Media duration, in microseconds. The value type is int64_t.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_DURATION;

/**
 * @brief Bit rate, in bit/s. The value type is int64_t.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_BITRATE;

/**
 * @brief Video frame rate (number of frames per 100 seconds). The value type is double.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_FRAME_RATE;

/**
 * @brief Video width. The value type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_WIDTH;

/**
 * @brief Video height. The value type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_HEIGHT;

/**
 * @brief Number of audio channels. The value type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_CHANNEL_COUNT;

/**
 * @brief Audio sampling rate (Hz). The value type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_SAMPLE_RATE;

/**
 * @brief Audio sampling bit depth. The value type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_SAMPLE_DEPTH;

/**
 * @brief Language ID. The value type is string.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_LANGUAGE;

/**
 * @brief Track name. The value type is string.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_TRACK_NAME;

/**
 * @brief HDR type. The value type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_HDR_TYPE;

/**
 * @brief Original video width. The value type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_ORIGINAL_WIDTH;

/**
 * @brief Original video height. The value type is int32_t.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_ORIGINAL_HEIGHT;

/**
 * @brief List of referenced track IDs, which is used only for the metadata extractor.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_REF_TRACK_IDS;

/**
 * @brief Track reference type, which is used only for the metadata extractor.
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_TRACK_REF_TYPE;

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETAKEYS_H
/** @} */
