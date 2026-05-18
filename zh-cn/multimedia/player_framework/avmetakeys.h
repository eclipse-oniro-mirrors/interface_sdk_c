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
 * @addtogroup avmetakeys
 * @{
 *
 * @brief Defines the avmetakeys.
 *
 * @since 23
 */
/**
 * @file avmetakeys.h
 *
 * @brief 定义音视频元数据键。
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
 * @brief 轨道索引，值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_TRACK_INDEX;

/**
 * @brief 轨道类型，值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_TRACK_TYPE;

/**
 * @brief 编解码器MIME类型，值类型为字符串（string）。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_MIME_TYPE;

/**
 * @brief 媒体时长（单位：微秒），值类型为int64_t。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_DURATION;

/**
 * @brief 比特率（单位：bps），值类型为int64_t。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_BITRATE;

/**
 * @brief 视频帧率（每100秒的帧数），值类型为double。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_FRAME_RATE;

/**
 * @brief 视频宽度，值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_WIDTH;

/**
 * @brief 视频高度，值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_HEIGHT;

/**
 * @brief 音频声道数，值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_CHANNEL_COUNT;

/**
 * @brief 音频采样率（Hz），值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_SAMPLE_RATE;

/**
 * @brief 音频采样位深（bit depth），值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_SAMPLE_DEPTH;

/**
 * @brief 语言标识，值类型为字符串（string）。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_LANGUAGE;

/**
 * @brief 轨道名称，值类型为字符串（string）。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_TRACK_NAME;

/**
 * @brief HDR类型，值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_HDR_TYPE;

/**
 * @brief 原始视频宽度，值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_ORIGINAL_WIDTH;

/**
 * @brief 原始视频高度，值类型为int32_t。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_ORIGINAL_HEIGHT;

/**
 * @brief 被引用的轨道ID列表，仅用于元数据提取器。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_REF_TRACK_IDS;

/**
 * @brief 轨道引用类型，仅用于元数据提取器。
 * 
 * @since 23
 */
extern const char* OH_AVMETA_KEY_TRACK_REF_TYPE;

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVMETAKEYS_H
/** @} */
