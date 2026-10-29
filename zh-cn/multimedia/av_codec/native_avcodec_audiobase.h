/*
 * Copyright (C) 2026 Huawei Device Co., Ltd.
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
 * @brief CodecBase模块提供了用于音视频封装、解封装、编解码基础功能的变量、属性以及函数。
 *
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 9
 */
/**
 * @file native_avcodec_audiobase.h
 *
 * @brief 声明用于基础音频编解码功能以及音频特定配置和参数的Native API。
 *
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_avcodec_audiobase.h>
 * @library libnative_media_codecbase.so
 * @syscap SystemCapability.Multimedia.Media.CodecBase
 * @since 26.1.0
 */

#ifndef NATIVE_AVCODEC_AUDIOBASE_H
#define NATIVE_AVCODEC_AUDIOBASE_H
#include <stdint.h>
#include "native_avformat.h"
#include "native_averrors.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief DSD解码类型的键，值类型为int32_t，取值请参见{@link OH_AVCodec_DSDCodecType}。
 * 该键是可选参数，只用来标记DSD解码类型，默认值为OH_AVCODEC_DSD_CODEC_LSBF_PLANAR(0)。
 *
 * @since 26.1.0
 */
extern const char *OH_MD_KEY_AUDIO_DSD_CODEC_TYPE;

/**
 * @brief DSD编解码类型。
 *
 * @since 26.1.0
 */
typedef enum OH_AVCodec_DSDCodecType {
    /**
     * @brief 适用于LSB first和平面排布的dsf容器格式。
     *
     * @since 26.1.0
     */
    OH_AVCODEC_DSD_CODEC_LSBF_PLANAR = 0,
    /**
     * @brief MSB first和平面排布的dsf容器格式。
     *
     * @since 26.1.0
     */
    OH_AVCODEC_DSD_CODEC_MSBF_PLANAR = 1,
    /**
     * @brief MSB first和交织排布的dff容器格式。
     *
     * @since 26.1.0
     */
    OH_AVCODEC_DSD_CODEC_MSBF = 2,
} OH_AVCodec_DSDCodecType;

#ifdef __cplusplus
}
#endif
#endif // NATIVE_AVCODEC_AUDIOBASE_H
/** @} */
