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
 * @brief Provides APIs for Core.
 *
 * @since 11
 */

/**
 * @file native_audio_channel_layout.h
 *
 * @brief The file declares the functions related to the speaker layout during recording and playback.
 *
 * @kit AVCodecKit
 * @library NA
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 11
 */

#ifndef NATIVE_AUDIO_CHANNEL_LAYOUT_H
#define NATIVE_AUDIO_CHANNEL_LAYOUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the audio channels.
 *
 * Each channel is mapped to a variable of int64_t.
 *
 * @since 11
 */
typedef enum OH_AudioChannelSet {
    /**
     * Front left channel.
     *
     * @since 11
     */
    CH_SET_FRONT_LEFT = 1ULL << 0U,

    /**
     * Front right channel.
     *
     * @since 11
     */
    CH_SET_FRONT_RIGHT = 1ULL << 1U,

    /**
     * Front center channel.
     *
     * @since 11
     */
    CH_SET_FRONT_CENTER = 1ULL << 2U,

    /**
     * Low-frequency channel.
     *
     * @since 11
     */
    CH_SET_LOW_FREQUENCY = 1ULL << 3U,

    /**
     * Rear left channel.
     *
     * @since 11
     */
    CH_SET_BACK_LEFT = 1ULL << 4U,

    /**
     * Rear right channel.
     *
     * @since 11
     */
    CH_SET_BACK_RIGHT = 1ULL << 5U,

    /**
     * Front left center channel.
     *
     * @since 11
     */
    CH_SET_FRONT_LEFT_OF_CENTER = 1ULL << 6U,

    /**
     * Front right center channel.
     *
     * @since 11
     */
    CH_SET_FRONT_RIGHT_OF_CENTER = 1ULL << 7U,

    /**
     * Rear center channel.
     *
     * @since 11
     */
    CH_SET_BACK_CENTER = 1ULL << 8U,

    /**
     * Left channel.
     *
     * @since 11
     */
    CH_SET_SIDE_LEFT = 1ULL << 9U,

    /**
     * Right channel.
     *
     * @since 11
     */
    CH_SET_SIDE_RIGHT = 1ULL << 10U,

    /**
     * Top center channel.
     *
     * @since 11
     */
    CH_SET_TOP_CENTER = 1ULL << 11U,

    /**
     * Top left front channel.
     *
     * @since 11
     */
    CH_SET_TOP_FRONT_LEFT = 1ULL << 12U,

    /**
     * Top center front channel.
     *
     * @since 11
     */
    CH_SET_TOP_FRONT_CENTER = 1ULL << 13U,

    /**
     * Top right front channel.
     *
     * @since 11
     */
    CH_SET_TOP_FRONT_RIGHT = 1ULL << 14U,

    /**
     * Top left rear channel.
     *
     * @since 11
     */
    CH_SET_TOP_BACK_LEFT = 1ULL << 15U,

    /**
     * Top center rear channel.
     *
     * @since 11
     */
    CH_SET_TOP_BACK_CENTER = 1ULL << 16U,

    /**
     * Top right rear channel.
     *
     * @since 11
     */
    CH_SET_TOP_BACK_RIGHT = 1ULL << 17U,

    /**
     * Stereo left channel.
     *
     * @since 11
     */
    CH_SET_STEREO_LEFT = 1ULL << 29U,

    /**
     * Stereo right channel.
     *
     * @since 11
     */
    CH_SET_STEREO_RIGHT = 1ULL << 30U,

    /**
     * Wide left channel.
     *
     * @since 11
     */
    CH_SET_WIDE_LEFT = 1ULL << 31U,

    /**
     * Wide right channel.
     *
     * @since 11
     */
    CH_SET_WIDE_RIGHT = 1ULL << 32U,

    /**
     * Left surround channel.
     *
     * @since 11
     */
    CH_SET_SURROUND_DIRECT_LEFT = 1ULL << 33U,

    /**
     * Right surround channel.
     *
     * @since 11
     */
    CH_SET_SURROUND_DIRECT_RIGHT = 1ULL << 34U,

    /**
     * Low-frequency channel 2.
     *
     * @since 11
     */
    CH_SET_LOW_FREQUENCY_2 = 1ULL << 35U,

    /**
     * Top left channel.
     *
     * @since 11
     */
    CH_SET_TOP_SIDE_LEFT = 1ULL << 36U,

    /**
     * Top right channel.
     *
     * @since 11
     */
    CH_SET_TOP_SIDE_RIGHT = 1ULL << 37U,

    /**
     * Bottom center front channel.
     *
     * @since 11
     */
    CH_SET_BOTTOM_FRONT_CENTER = 1ULL << 38U,

    /**
     * Bottom left front channel.
     *
     * @since 11
     */
    CH_SET_BOTTOM_FRONT_LEFT = 1ULL << 39U,

    /**
     * Bottom right front channel.
     *
     * @since 11
     */
    CH_SET_BOTTOM_FRONT_RIGHT = 1ULL << 40U
} OH_AudioChannelSet;

/**
 * @brief Ambisonic attribute set.
 *
 * A set of 64-bit integers indicate the ambisonic attributes.
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 11
 */
typedef enum OH_AmbAttributeSet {
    /** Ambisonic attribute: order 1 */
    AMB_ORD_1 = 1ULL << 0U,

    /** Ambisonic attribute: order 2 */
    AMB_ORD_2 = 2ULL << 0U,

    /** Ambisonic attribute: order 3 */
    AMB_ORD_3 = 3ULL << 0U,

    /** Ambisonic attribute: ACN Component Ordering */
    AMB_COM_ACN = 0ULL << 8U,

    /** Ambisonic attribute: FUMA Component Ordering */
    AMB_COM_FUMA = 1ULL << 8U,

    /** Ambisonic attribute: N3D Normalization */
    AMB_NOR_N3D = 0ULL << 12U,

    /** Ambisonic attribute: SN3D Normalization */
    AMB_NOR_SN3D = 1ULL << 12U,

    /** Channel layout: Ambisonic mode */
    AMB_MODE = 1ULL << 44U
} OH_AmbAttributeSet;

/**
 * @brief Enumerates the layouts of audio channels.
 *
 * Int64 integers are used to indicate the appearance and sequence of speakers during recording or playback.
 *
 * @since 11
 */
typedef enum OH_AudioChannelLayout {
    /**
     * Unknown.
     *
     * @since 11
     */
    CH_LAYOUT_UNKNOWN = 0ULL,

    /**
     * Mono layout; 1 audio channel in total.
     *
     * @since 11
     */
    CH_LAYOUT_MONO = CH_SET_FRONT_CENTER,

    /**
     * Stereo layout; 2 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_STEREO = CH_SET_FRONT_LEFT | CH_SET_FRONT_RIGHT,

    /**
     * Stereo downmix layout; 2 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_STEREO_DOWNMIX = CH_SET_STEREO_LEFT | CH_SET_STEREO_RIGHT,

    /**
     * 2.1 layout; 3 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_2POINT1 = CH_LAYOUT_STEREO | CH_SET_LOW_FREQUENCY,

    /**
     * 3.0 layout; 3 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_3POINT0 = CH_LAYOUT_STEREO | CH_SET_BACK_CENTER,

    /**
     * Surround; 3 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_SURROUND = CH_LAYOUT_STEREO | CH_SET_FRONT_CENTER,

    /**
     * 3.1 layout; 4 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_3POINT1 = CH_LAYOUT_SURROUND | CH_SET_LOW_FREQUENCY,

    /**
     * 4.0 layout; 4 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_4POINT0 = CH_LAYOUT_SURROUND | CH_SET_BACK_CENTER,

    /**
     * Quad side layout; 4 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_QUAD_SIDE = CH_LAYOUT_STEREO | CH_SET_SIDE_LEFT | CH_SET_SIDE_RIGHT,

    /**
     * Quad layout; 4 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_QUAD = CH_LAYOUT_STEREO | CH_SET_BACK_LEFT | CH_SET_BACK_RIGHT,

    /**
     * 2.0.2 layout; 4 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_2POINT0POINT2 = CH_LAYOUT_STEREO | CH_SET_TOP_SIDE_LEFT | CH_SET_TOP_SIDE_RIGHT,

    /**
     * First-order FOA layout in ACN_N3D (ITU standards); 4 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_AMB_ORDER1_ACN_N3D = AMB_MODE | AMB_ORD_1 | AMB_COM_ACN | AMB_NOR_N3D,

    /**
     * First-order FOA layout in ACN_SN3D (ITU standards); 4 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_AMB_ORDER1_ACN_SN3D = AMB_MODE | AMB_ORD_1 | AMB_COM_ACN | AMB_NOR_SN3D,

    /**
     * First-order FOA layout in FUMA (ITU standards); 4 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_AMB_ORDER1_FUMA = AMB_MODE | AMB_ORD_1 | AMB_COM_FUMA,

    /**
     * 4.1 layout; 5 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_4POINT1 = CH_LAYOUT_4POINT0 | CH_SET_LOW_FREQUENCY,

    /**
     * 5.0 layout; 5 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_5POINT0 = CH_LAYOUT_SURROUND | CH_SET_SIDE_LEFT | CH_SET_SIDE_RIGHT,

    /**
     * 5.0 rear layout; 5 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_5POINT0_BACK = CH_LAYOUT_SURROUND | CH_SET_BACK_LEFT | CH_SET_BACK_RIGHT,

    /**
     * 2.1.2 layout; 5 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_2POINT1POINT2 = CH_LAYOUT_2POINT0POINT2 | CH_SET_LOW_FREQUENCY,

    /**
     * 3.0.2 layout; 5 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_3POINT0POINT2 = CH_LAYOUT_2POINT0POINT2 | CH_SET_FRONT_CENTER,

    /**
     * 5.1 layout; 6 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_5POINT1 = CH_LAYOUT_5POINT0 | CH_SET_LOW_FREQUENCY,

    /**
     * 5.1 rear layout; 6 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_5POINT1_BACK = CH_LAYOUT_5POINT0_BACK | CH_SET_LOW_FREQUENCY,

    /**
     * 6.0 layout; 6 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_6POINT0 = CH_LAYOUT_5POINT0 | CH_SET_BACK_CENTER,

    /**
     * 3.1.2 layout; 6 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_3POINT1POINT2 = CH_LAYOUT_3POINT1 | CH_SET_TOP_FRONT_LEFT | CH_SET_TOP_FRONT_RIGHT,

    /**
     * 6.0 front layout; 6 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_6POINT0_FRONT = CH_LAYOUT_QUAD_SIDE | CH_SET_FRONT_LEFT_OF_CENTER | CH_SET_FRONT_RIGHT_OF_CENTER,

    /**
     * Hexagonal layout; 6 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_HEXAGONAL = CH_LAYOUT_5POINT0_BACK | CH_SET_BACK_CENTER,

    /**
     * 6.1 layout; 7 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_6POINT1 = CH_LAYOUT_5POINT1 | CH_SET_BACK_CENTER,

    /**
     * 6.1 rear layout; 7 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_6POINT1_BACK = CH_LAYOUT_5POINT1_BACK | CH_SET_BACK_CENTER,

    /**
     * 6.1 front layout; 7 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_6POINT1_FRONT = CH_LAYOUT_6POINT0_FRONT | CH_SET_LOW_FREQUENCY,

    /**
     * 7.0 layout; 7 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_7POINT0 = CH_LAYOUT_5POINT0 | CH_SET_BACK_LEFT | CH_SET_BACK_RIGHT,

    /**
     * 7.0 front layout; 7 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_7POINT0_FRONT = CH_LAYOUT_5POINT0 | CH_SET_FRONT_LEFT_OF_CENTER | CH_SET_FRONT_RIGHT_OF_CENTER,

    /**
     * 7.1 layout; 8 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_7POINT1 = CH_LAYOUT_5POINT1 | CH_SET_BACK_LEFT | CH_SET_BACK_RIGHT,

    /**
     * Octagonal layout; 8 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_OCTAGONAL = CH_LAYOUT_5POINT0 | CH_SET_BACK_LEFT | CH_SET_BACK_CENTER | CH_SET_BACK_RIGHT,

    /**
     * 5.1.2 layout; 8 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_5POINT1POINT2 = CH_LAYOUT_5POINT1 | CH_SET_TOP_SIDE_LEFT | CH_SET_TOP_SIDE_RIGHT,

    /**
     * 7.1 wide layout; 8 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_7POINT1_WIDE = CH_LAYOUT_5POINT1 | CH_SET_FRONT_LEFT_OF_CENTER | CH_SET_FRONT_RIGHT_OF_CENTER,

    /**
     * 7.1 rear wide layout; 8 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_7POINT1_WIDE_BACK = CH_LAYOUT_5POINT1_BACK | CH_SET_FRONT_LEFT_OF_CENTER | CH_SET_FRONT_RIGHT_OF_CENTER,

    /**
     * Second-order HOA layout in ACN_N3D (ITU standards); 9 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_AMB_ORDER2_ACN_N3D = AMB_MODE | AMB_ORD_2 | AMB_COM_ACN | AMB_NOR_N3D,

    /**
     * Second-order HOA layout in ACN_SN3D (ITU standards); 9 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_AMB_ORDER2_ACN_SN3D = AMB_MODE | AMB_ORD_2 | AMB_COM_ACN | AMB_NOR_SN3D,

    /**
     * Second-order HOA layout in FUMA (ITU standards); 9 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_AMB_ORDER2_FUMA = AMB_MODE | AMB_ORD_2 | AMB_COM_FUMA,

    /**
     * 5.1.4 layout; 10 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_5POINT1POINT4 = CH_LAYOUT_5POINT1 | CH_SET_TOP_FRONT_LEFT | CH_SET_TOP_FRONT_RIGHT |
                              CH_SET_TOP_BACK_LEFT | CH_SET_TOP_BACK_RIGHT,

    /**
     * 7.1.2 layout; 10 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_7POINT1POINT2 = CH_LAYOUT_7POINT1 | CH_SET_TOP_SIDE_LEFT | CH_SET_TOP_SIDE_RIGHT,

    /**
     * 7.1.4 layout; 12 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_7POINT1POINT4 = CH_LAYOUT_7POINT1 | CH_SET_TOP_FRONT_LEFT | CH_SET_TOP_FRONT_RIGHT |
                              CH_SET_TOP_BACK_LEFT | CH_SET_TOP_BACK_RIGHT,

    /**
     * 10.2 layout; 12 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_10POINT2 = CH_SET_FRONT_LEFT | CH_SET_FRONT_RIGHT | CH_SET_FRONT_CENTER | CH_SET_TOP_FRONT_LEFT |
                         CH_SET_TOP_FRONT_RIGHT | CH_SET_BACK_LEFT | CH_SET_BACK_RIGHT | CH_SET_BACK_CENTER |
                         CH_SET_SIDE_LEFT | CH_SET_SIDE_RIGHT | CH_SET_WIDE_LEFT | CH_SET_WIDE_RIGHT,

    /**
     * 9.1.4 layout; 14 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_9POINT1POINT4 = CH_LAYOUT_7POINT1POINT4 | CH_SET_WIDE_LEFT | CH_SET_WIDE_RIGHT,

    /**
     * 9.1.6 layout; 16 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_9POINT1POINT6 = CH_LAYOUT_9POINT1POINT4 | CH_SET_TOP_SIDE_LEFT | CH_SET_TOP_SIDE_RIGHT,

    /**
     * Hexadecagonal layout; 16 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_HEXADECAGONAL = CH_LAYOUT_OCTAGONAL | CH_SET_WIDE_LEFT | CH_SET_WIDE_RIGHT | CH_SET_TOP_BACK_LEFT |
                              CH_SET_TOP_BACK_RIGHT | CH_SET_TOP_BACK_CENTER | CH_SET_TOP_FRONT_CENTER |
                              CH_SET_TOP_FRONT_LEFT | CH_SET_TOP_FRONT_RIGHT,

    /**
     * Third-order HOA layout in ACN_N3D (ITU standards); 16 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_AMB_ORDER3_ACN_N3D = AMB_MODE | AMB_ORD_3 | AMB_COM_ACN | AMB_NOR_N3D,

    /**
     * Third-order HOA layout in ACN_SN3D (ITU standards); 16 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_AMB_ORDER3_ACN_SN3D = AMB_MODE | AMB_ORD_3 | AMB_COM_ACN | AMB_NOR_SN3D,

    /**
     * Third-order HOA layout in FUMA (ITU standards); 16 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_AMB_ORDER3_FUMA = AMB_MODE | AMB_ORD_3 | AMB_COM_FUMA,

    /**
     * 22.2 layout; 24 audio channels in total.
     *
     * @since 11
     */
    CH_LAYOUT_22POINT2 = CH_LAYOUT_7POINT1POINT4 | CH_SET_FRONT_LEFT_OF_CENTER | CH_SET_FRONT_RIGHT_OF_CENTER |
                         CH_SET_BACK_CENTER | CH_SET_TOP_CENTER | CH_SET_TOP_FRONT_CENTER | CH_SET_TOP_BACK_CENTER |
                         CH_SET_TOP_SIDE_LEFT | CH_SET_TOP_SIDE_RIGHT | CH_SET_BOTTOM_FRONT_LEFT |
                         CH_SET_BOTTOM_FRONT_RIGHT | CH_SET_BOTTOM_FRONT_CENTER | CH_SET_LOW_FREQUENCY_2
} OH_AudioChannelLayout;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_CHANNEL_LAYOUT_H

/** @} */