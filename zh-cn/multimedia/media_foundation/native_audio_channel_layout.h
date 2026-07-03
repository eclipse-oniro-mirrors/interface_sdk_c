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
 * @file native_audio_channel_layout.h
 *
 * @brief 在录制和播放时的扬声器布局。
 *
 * @kit AVCodecKit
 * @include <multimedia/native_audio_channel_layout.h>
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
 * @brief 音频声道集合。\n
 *
 * 将每一个声道映射为int64的变量。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 11
 */
typedef enum OH_AudioChannelSet {
    /** 左前声道 */
    CH_SET_FRONT_LEFT = 1ULL << 0U,

    /** 右前声道 */
    CH_SET_FRONT_RIGHT = 1ULL << 1U,

    /** 中前声道 */
    CH_SET_FRONT_CENTER = 1ULL << 2U,

    /** 低频声道 */
    CH_SET_LOW_FREQUENCY = 1ULL << 3U,

    /** 左后声道 */
    CH_SET_BACK_LEFT = 1ULL << 4U,

    /** 右后声道 */
    CH_SET_BACK_RIGHT = 1ULL << 5U,

    /** 左前中置声道 */
    CH_SET_FRONT_LEFT_OF_CENTER = 1ULL << 6U,

    /** 右前中置声道  */
    CH_SET_FRONT_RIGHT_OF_CENTER = 1ULL << 7U,

    /** 后方中置声道 */
    CH_SET_BACK_CENTER = 1ULL << 8U,

    /** 左侧声道 */
    CH_SET_SIDE_LEFT = 1ULL << 9U,

    /** 右侧声道 */
    CH_SET_SIDE_RIGHT = 1ULL << 10U,

    /** 上方中置声道 */
    CH_SET_TOP_CENTER = 1ULL << 11U,

    /** 上方左前声道 */
    CH_SET_TOP_FRONT_LEFT = 1ULL << 12U,

    /** 上方中前声道 */
    CH_SET_TOP_FRONT_CENTER = 1ULL << 13U,

    /** 上方右前声道 */
    CH_SET_TOP_FRONT_RIGHT = 1ULL << 14U,

    /** 上方左后声道 */
    CH_SET_TOP_BACK_LEFT = 1ULL << 15U,

    /** 上方中后声道 */
    CH_SET_TOP_BACK_CENTER = 1ULL << 16U,

    /** 上方右后声道 */
    CH_SET_TOP_BACK_RIGHT = 1ULL << 17U,

    /** 立体声左声道 */
    CH_SET_STEREO_LEFT = 1ULL << 29U,

    /** 立体声右声道 */
    CH_SET_STEREO_RIGHT = 1ULL << 30U,

    /** 宽左声道 */
    CH_SET_WIDE_LEFT = 1ULL << 31U,

    /** 宽右声道 */
    CH_SET_WIDE_RIGHT = 1ULL << 32U,

    /** 左环绕声道 */
    CH_SET_SURROUND_DIRECT_LEFT = 1ULL << 33U,

    /** 右环绕声道 */
    CH_SET_SURROUND_DIRECT_RIGHT = 1ULL << 34U,

    /** 低频声道2 */
    CH_SET_LOW_FREQUENCY_2 = 1ULL << 35U,

    /** 上方左侧声道 */
    CH_SET_TOP_SIDE_LEFT = 1ULL << 36U,

    /** 上方右侧声道 */
    CH_SET_TOP_SIDE_RIGHT = 1ULL << 37U,

    /** 下方中前声道 */
    CH_SET_BOTTOM_FRONT_CENTER = 1ULL << 38U,

    /** 下方左前声道 */
    CH_SET_BOTTOM_FRONT_LEFT = 1ULL << 39U,

    /** 下方右前声道 */
    CH_SET_BOTTOM_FRONT_RIGHT = 1ULL << 40U
} OH_AudioChannelSet;

/**
 * @brief 高保真立体声混响设置。\n
 *
 * 用int64整数来表示高保真立体声混响属性。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 11
 */
typedef enum OH_AmbAttributeSet {
    /** 一阶高保真立体声混响 */
    AMB_ORD_1 = 1ULL << 0U,

    /** 二阶高保真立体声混响 */
    AMB_ORD_2 = 2ULL << 0U,

    /** 三阶高保真立体声混响 */
    AMB_ORD_3 = 3ULL << 0U,

    /** ACN通道排序的高保真立体声混响 */
    AMB_COM_ACN = 0ULL << 8U,

    /** FUMA通道排序的高保真立体声混响 */
    AMB_COM_FUMA = 1ULL << 8U,

    /** N3D归一化的高保真立体声混响 */
    AMB_NOR_N3D = 0ULL << 12U,

    /** SN3D归一化的高保真立体声混响 */
    AMB_NOR_SN3D = 1ULL << 12U,

    /** 高保真立体声混响的声道布局 */
    AMB_MODE = 1ULL << 44U
} OH_AmbAttributeSet;

/**
 * @brief 音频声道布局。\n
 *
 * 用int64整数来表示在录制或播放时扬声器的外观和顺序。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 11
 */
typedef enum OH_AudioChannelLayout {
    /** 未知声道布局 */
    CH_LAYOUT_UNKNOWN = 0ULL,

    /** 单声道布局，共1个声道。 */
    CH_LAYOUT_MONO = CH_SET_FRONT_CENTER,

    /** 立体声布局，共2个声道。 */
    CH_LAYOUT_STEREO = CH_SET_FRONT_LEFT | CH_SET_FRONT_RIGHT,

    /** 立体声下混布局，共2个声道。 */
    CH_LAYOUT_STEREO_DOWNMIX = CH_SET_STEREO_LEFT | CH_SET_STEREO_RIGHT,

    /** 2.1布局，共3个声道。 */
    CH_LAYOUT_2POINT1 = CH_LAYOUT_STEREO | CH_SET_LOW_FREQUENCY,

    /** 3.0布局，共3个声道。 */
    CH_LAYOUT_3POINT0 = CH_LAYOUT_STEREO | CH_SET_BACK_CENTER,

    /** 环绕布局，共3个声道。 */
    CH_LAYOUT_SURROUND = CH_LAYOUT_STEREO | CH_SET_FRONT_CENTER,

    /** 3.1布局，共4个声道。 */
    CH_LAYOUT_3POINT1 = CH_LAYOUT_SURROUND | CH_SET_LOW_FREQUENCY,

    /** 4.0布局，共4个声道。 */
    CH_LAYOUT_4POINT0 = CH_LAYOUT_SURROUND | CH_SET_BACK_CENTER,

    /** QUAD_SIDE布局，共4个声道。 */
    CH_LAYOUT_QUAD_SIDE = CH_LAYOUT_STEREO | CH_SET_SIDE_LEFT | CH_SET_SIDE_RIGHT,

    /** QUAD布局，共4个声道。 */
    CH_LAYOUT_QUAD = CH_LAYOUT_STEREO | CH_SET_BACK_LEFT | CH_SET_BACK_RIGHT,

    /** 2.0.2布局，共4个声道。 */
    CH_LAYOUT_2POINT0POINT2 = CH_LAYOUT_STEREO | CH_SET_TOP_SIDE_LEFT | CH_SET_TOP_SIDE_RIGHT,

    /** ACN_N3D（根据ITU标准）的一阶FOA布局，共4个声道。 */
    CH_LAYOUT_AMB_ORDER1_ACN_N3D = AMB_MODE | AMB_ORD_1 | AMB_COM_ACN | AMB_NOR_N3D,

    /** ACN_SN3D（根据ITU标准）的一阶FOA布局，共4个声道。 */
    CH_LAYOUT_AMB_ORDER1_ACN_SN3D = AMB_MODE | AMB_ORD_1 | AMB_COM_ACN | AMB_NOR_SN3D,

    /** FUMA（根据ITU标准）的一阶FOA布局，共4个声道。 */
    CH_LAYOUT_AMB_ORDER1_FUMA = AMB_MODE | AMB_ORD_1 | AMB_COM_FUMA,

    /** 4.1布局，共5个声道。 */
    CH_LAYOUT_4POINT1 = CH_LAYOUT_4POINT0 | CH_SET_LOW_FREQUENCY,

    /** 5.0布局，共5个声道。 */
    CH_LAYOUT_5POINT0 = CH_LAYOUT_SURROUND | CH_SET_SIDE_LEFT | CH_SET_SIDE_RIGHT,

    /** 5.0-后置布局，共5个声道。 */
    CH_LAYOUT_5POINT0_BACK = CH_LAYOUT_SURROUND | CH_SET_BACK_LEFT | CH_SET_BACK_RIGHT,

    /** 2.1.2布局，共5个声道。 */
    CH_LAYOUT_2POINT1POINT2 = CH_LAYOUT_2POINT0POINT2 | CH_SET_LOW_FREQUENCY,

    /** 3.0.2布局，共5个声道。 */
    CH_LAYOUT_3POINT0POINT2 = CH_LAYOUT_2POINT0POINT2 | CH_SET_FRONT_CENTER,

    /** 5.1布局，共6个声道。 */
    CH_LAYOUT_5POINT1 = CH_LAYOUT_5POINT0 | CH_SET_LOW_FREQUENCY,

    /** 5.1-后置布局，共6个声道。 */
    CH_LAYOUT_5POINT1_BACK = CH_LAYOUT_5POINT0_BACK | CH_SET_LOW_FREQUENCY,

    /** 6.0布局，共6个声道。 */
    CH_LAYOUT_6POINT0 = CH_LAYOUT_5POINT0 | CH_SET_BACK_CENTER,

    /** 3.1.2布局，共6个声道。 */
    CH_LAYOUT_3POINT1POINT2 = CH_LAYOUT_3POINT1 | CH_SET_TOP_FRONT_LEFT | CH_SET_TOP_FRONT_RIGHT,

    /** 6.0-Front布局，共6个声道。 */
    CH_LAYOUT_6POINT0_FRONT = CH_LAYOUT_QUAD_SIDE | CH_SET_FRONT_LEFT_OF_CENTER | CH_SET_FRONT_RIGHT_OF_CENTER,

    /** HEXAGONAL布局，共6个声道。 */
    CH_LAYOUT_HEXAGONAL = CH_LAYOUT_5POINT0_BACK | CH_SET_BACK_CENTER,

    /** 6.1布局，共7个声道。 */
    CH_LAYOUT_6POINT1 = CH_LAYOUT_5POINT1 | CH_SET_BACK_CENTER,

    /** 6.1-后置布局，共7个声道。 */
    CH_LAYOUT_6POINT1_BACK = CH_LAYOUT_5POINT1_BACK | CH_SET_BACK_CENTER,

    /** 6.1-前置布局，共7个声道。 */
    CH_LAYOUT_6POINT1_FRONT = CH_LAYOUT_6POINT0_FRONT | CH_SET_LOW_FREQUENCY,

    /** 7.0布局，共7个声道。 */
    CH_LAYOUT_7POINT0 = CH_LAYOUT_5POINT0 | CH_SET_BACK_LEFT | CH_SET_BACK_RIGHT,

    /** 7.0-前置布局，共7个声道。 */
    CH_LAYOUT_7POINT0_FRONT = CH_LAYOUT_5POINT0 | CH_SET_FRONT_LEFT_OF_CENTER | CH_SET_FRONT_RIGHT_OF_CENTER,

    /** 7.1布局，共8个声道。 */
    CH_LAYOUT_7POINT1 = CH_LAYOUT_5POINT1 | CH_SET_BACK_LEFT | CH_SET_BACK_RIGHT,

    /** OCTAGONAL布局，共8个声道。 */
    CH_LAYOUT_OCTAGONAL = CH_LAYOUT_5POINT0 | CH_SET_BACK_LEFT | CH_SET_BACK_CENTER | CH_SET_BACK_RIGHT,

    /** 5.1.2布局，共8个声道。 */
    CH_LAYOUT_5POINT1POINT2 = CH_LAYOUT_5POINT1 | CH_SET_TOP_SIDE_LEFT | CH_SET_TOP_SIDE_RIGHT,

    /** 7.1-宽布局，共8个声道。 */
    CH_LAYOUT_7POINT1_WIDE = CH_LAYOUT_5POINT1 | CH_SET_FRONT_LEFT_OF_CENTER | CH_SET_FRONT_RIGHT_OF_CENTER,

    /** 7.1-后置宽布局，共8个声道。 */
    CH_LAYOUT_7POINT1_WIDE_BACK = CH_LAYOUT_5POINT1_BACK | CH_SET_FRONT_LEFT_OF_CENTER | CH_SET_FRONT_RIGHT_OF_CENTER,

    /** ACN_N3D（根据ITU标准）的二阶HOA布局，共9个声道。 */
    CH_LAYOUT_AMB_ORDER2_ACN_N3D = AMB_MODE | AMB_ORD_2 | AMB_COM_ACN | AMB_NOR_N3D,

    /** ACN_SN3D（根据ITU标准）的二阶HOA布局，共9个声道。 */
    CH_LAYOUT_AMB_ORDER2_ACN_SN3D = AMB_MODE | AMB_ORD_2 | AMB_COM_ACN | AMB_NOR_SN3D,

    /** FUMA（根据ITU标准）的二阶HOA布局，共9个声道。 */
    CH_LAYOUT_AMB_ORDER2_FUMA = AMB_MODE | AMB_ORD_2 | AMB_COM_FUMA,

    /** 5.1.4布局，共10个声道。 */
    CH_LAYOUT_5POINT1POINT4 = CH_LAYOUT_5POINT1 | CH_SET_TOP_FRONT_LEFT | CH_SET_TOP_FRONT_RIGHT |
                              CH_SET_TOP_BACK_LEFT | CH_SET_TOP_BACK_RIGHT,

    /** 7.1.2布局，共10个声道。 */
    CH_LAYOUT_7POINT1POINT2 = CH_LAYOUT_7POINT1 | CH_SET_TOP_SIDE_LEFT | CH_SET_TOP_SIDE_RIGHT,

    /** 7.1.4布局，共12个声道。 */
    CH_LAYOUT_7POINT1POINT4 = CH_LAYOUT_7POINT1 | CH_SET_TOP_FRONT_LEFT | CH_SET_TOP_FRONT_RIGHT |
                              CH_SET_TOP_BACK_LEFT | CH_SET_TOP_BACK_RIGHT,

    /** 10.2布局，共12个声道。 */
    CH_LAYOUT_10POINT2 = CH_SET_FRONT_LEFT | CH_SET_FRONT_RIGHT | CH_SET_FRONT_CENTER | CH_SET_TOP_FRONT_LEFT |
                         CH_SET_TOP_FRONT_RIGHT | CH_SET_BACK_LEFT | CH_SET_BACK_RIGHT | CH_SET_BACK_CENTER |
                         CH_SET_SIDE_LEFT | CH_SET_SIDE_RIGHT | CH_SET_WIDE_LEFT | CH_SET_WIDE_RIGHT,

    /** 9.1.4布局，共14个声道。 */
    CH_LAYOUT_9POINT1POINT4 = CH_LAYOUT_7POINT1POINT4 | CH_SET_WIDE_LEFT | CH_SET_WIDE_RIGHT,

    /** 9.1.6布局，共16个声道。 */
    CH_LAYOUT_9POINT1POINT6 = CH_LAYOUT_9POINT1POINT4 | CH_SET_TOP_SIDE_LEFT | CH_SET_TOP_SIDE_RIGHT,

    /** HEXADECAGONAL布局，共16个声道。 */
    CH_LAYOUT_HEXADECAGONAL = CH_LAYOUT_OCTAGONAL | CH_SET_WIDE_LEFT | CH_SET_WIDE_RIGHT | CH_SET_TOP_BACK_LEFT |
                              CH_SET_TOP_BACK_RIGHT | CH_SET_TOP_BACK_CENTER | CH_SET_TOP_FRONT_CENTER |
                              CH_SET_TOP_FRONT_LEFT | CH_SET_TOP_FRONT_RIGHT,

    /** ACN_N3D（根据ITU标准）的三阶HOA布局，共16个声道。 */
    CH_LAYOUT_AMB_ORDER3_ACN_N3D = AMB_MODE | AMB_ORD_3 | AMB_COM_ACN | AMB_NOR_N3D,

    /** ACN_SN3D（根据ITU标准）的三阶HOA布局，共16个声道。 */
    CH_LAYOUT_AMB_ORDER3_ACN_SN3D = AMB_MODE | AMB_ORD_3 | AMB_COM_ACN | AMB_NOR_SN3D,

    /** FUMA（根据ITU标准）的三阶HOA布局，共16个声道。 */
    CH_LAYOUT_AMB_ORDER3_FUMA = AMB_MODE | AMB_ORD_3 | AMB_COM_FUMA,

    /** 22.2布局，共24个声道。 */
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