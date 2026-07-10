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
 * @addtogroup Core
 * @{
 *
 * @brief Core模块提供用于媒体系统的基础骨干能力，包含内存、错误码、媒体数据结构等相关函数。
 *
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */


/**
 * @file native_avbuffer_info.h
 *
 * @brief 声明了媒体数据结构AVBuffer属性的定义。
 * @sample [AVCodec](https://gitcode.com/openharmony/applications_app_samples/tree/master/code/BasicFeature/Media/AVCodec)
 *
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avbuffer_info.h>
 * @library libnative_media_core.so
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */

#ifndef NATIVE_AVBUFFER_INFO_H
#define NATIVE_AVBUFFER_INFO_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 枚举OH_AVCodec缓冲区标记的类别。
 *
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */
typedef enum OH_AVCodecBufferFlags {
    /** 表示为普通帧。 */
    AVCODEC_BUFFER_FLAGS_NONE = 0,
    /** 表示缓冲区是流结束帧。 */
    AVCODEC_BUFFER_FLAGS_EOS = 1 << 0,
    /** 表示缓冲区包含关键帧。 */
    AVCODEC_BUFFER_FLAGS_SYNC_FRAME = 1 << 1,
    /** 表示缓冲区中的数据只是帧的一部分。 */
    AVCODEC_BUFFER_FLAGS_INCOMPLETE_FRAME = 1 << 2,
    /** 表示缓冲区包含编解码特定数据。 */
    AVCODEC_BUFFER_FLAGS_CODEC_DATA = 1 << 3,
    /**
     * @brief 表示缓冲区被解码依赖，解码之后的数据可丢弃。
     * @since 12
     */
    AVCODEC_BUFFER_FLAGS_DISCARD = 1 << 4,
    /**
     * @brief 表示缓冲区不被参考可直接丢弃。
     * @since 12
     */
    AVCODEC_BUFFER_FLAGS_DISPOSABLE = 1 << 5,
} OH_AVCodecBufferFlags;

/**
 * @brief 定义OH_AVCodec的缓冲区描述信息。
 *
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */
typedef struct OH_AVCodecBufferAttr {
    /** 此缓冲区的显示时间戳（以微秒为单位）。 */
    int64_t pts;
    /** 缓冲区中包含的数据的大小（以字节为单位）。 */
    int32_t size;
    /** 此缓冲区中有效数据的起始偏移量。 */
    int32_t offset;
    /** 此缓冲区具有的标志，请参阅{@link OH_AVCodecBufferFlags}。 */
    uint32_t flags;
} OH_AVCodecBufferAttr;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVBUFFER_INFO_H

/** @} */
