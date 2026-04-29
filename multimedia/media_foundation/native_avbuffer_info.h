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
 * @addtogroup Core
 * @{
 *
 * @brief The Core module provides basic backbone capabilities for media frameworks,
 * including functions such as memory, error codes, and media data structures.
 *
 * @since 9
 */
/**
 * @file native_avbuffer_info.h
 *
 * @brief The file declares the attribute definition of the media struct AVBuffer.
 *
 * @kit AVCodecKit
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
 * @brief Enumerates the flags for the buffer of an OH_AVCodec instance.
 *
 * @since 9
 */
typedef enum OH_AVCodecBufferFlags {
    /**
     * Common frame.
     * @since 9
     */
    AVCODEC_BUFFER_FLAGS_NONE = 0,
    /**
     * The buffer is an end-of-stream frame.
     * @since 9
     */
    AVCODEC_BUFFER_FLAGS_EOS = 1 << 0,
    /**
     * The buffer contains key frames.
     * @since 9
     */
    AVCODEC_BUFFER_FLAGS_SYNC_FRAME = 1 << 1,
    /**
     * The data in the buffer is only part of the frame.
     * @since 9
     */
    AVCODEC_BUFFER_FLAGS_INCOMPLETE_FRAME = 1 << 2,
    /**
     * The buffer contains codec-specific data.
     * @since 9
     */
    AVCODEC_BUFFER_FLAGS_CODEC_DATA = 1 << 3,
    /**
     * Flag is used to discard packets which are required to maintain valid decoder state but are not required
     * for output and should be dropped after decoding.
     * @since 12
     */
    AVCODEC_BUFFER_FLAGS_DISCARD = 1 << 4,
    /**
     * Flag is used to indicate packets that contain frames that can be discarded by the decoder,
     * I.e. Non-reference frames.
     * @since 12
     */
    AVCODEC_BUFFER_FLAGS_DISPOSABLE = 1 << 5
} OH_AVCodecBufferFlags;

/**
 * @brief The struct describes the description information about the buffer of an OH_AVCodec instance.
 *
 * @since 9
 */
typedef struct OH_AVCodecBufferAttr {
    /**
     * Display timestamp of the buffer, in microseconds.
     * @since 9
     */
    int64_t pts;
    /**
     * Size of data contained in the buffer, in bytes.
     * @since 9
     */
    int32_t size;
    /**
     * Offset of valid data in the buffer.
     * @since 9
     */
    int32_t offset;
    /**
     * Flags of the buffer. For details, see {@link OH_AVCodecBufferFlags}.
     * @since 9
     */
    uint32_t flags;
} OH_AVCodecBufferAttr;
#ifdef __cplusplus
}
#endif
#endif // NATIVE_AVBUFFER_INFO_H

/** @} */