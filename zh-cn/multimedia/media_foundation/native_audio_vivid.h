/*
 * Copyright (C) 2026 Huawei Device Co., Ltd.
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
 * @brief Core模块提供的Audio Vivid元数据构建器。
 *
 * @since 26.0.0
 */

/**
 * @file native_audio_vivid.h
 *
 * @brief 声明Audio Vivid相关的函数和枚举。
 *
 * @kit AVCodecKit
 * @library libnative_media_core.so
 * @include <multimedia/player_framework/native_audio_vivid.h>
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 26.0.0
 */

#ifndef NATIVE_AUDIO_VIVID_H
#define NATIVE_AUDIO_VIVID_H

#include "native_avformat.h"
#include "native_averrors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Audio Vivid编码器信号格式枚举。
 *
 * @since 26.0.0
 */
typedef enum OH_AudioVividSignalFormat {
    /**
     * @brief Audio Vivid信号格式为单声道，编码器接收单声道数据，内部标记声道布局为{@link OH_AudioChannelLayout}.CH_LAYOUT_MONO。
     */
    OH_AUDIO_VIVID_SIGNAL_FORMAT_MONO = 0,
    /**
     * @brief Audio Vivid信号格式为立体声，编码器接收双声道数据，内部标记声道布局为{@link OH_AudioChannelLayout}.CH_LAYOUT_STEREO。
     */
    OH_AUDIO_VIVID_SIGNAL_FORMAT_STEREO = 1,
    /**
     * @brief Audio Vivid信号格式为多声道，编码器支持声道布局{@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1POINT2、{@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1POINT4、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1、{@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1POINT2、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1POINT4。
     */
    OH_AUDIO_VIVID_SIGNAL_FORMAT_MC = 2,
    /**
     * @brief Audio Vivid信号格式为混合模式，包含声床（Bed）和对象（object）。声床的声道布局支持{@link OH_AudioChannelLayout}.CH_LAYOUT_STEREO、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1、{@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1POINT2、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1POINT4、{@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1POINT2、{@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1POINT4。
     */
    OH_AUDIO_VIVID_SIGNAL_FORMAT_MIX = 4,
} OH_AudioVividSignalFormat;

/**
 * @brief 表示对象声源在笛卡尔坐标系（Cartesian coordinate system）中的位置。
 *
 * 笛卡尔坐标系使用x、y、z轴定义三维空间中的位置。
 *
 * @since 26.0.0
 */
typedef struct OH_CartesianPosition {
    /**
     * @brief 对象声源在笛卡尔坐标系中的归一化（Normalization，将数值按比例转换到指定范围内）X坐标，表示左/右维度。\n
     * 取值范围为[-1.0, 1.0]。
     */
    float x;
    /**
     * @brief 对象声源在笛卡尔坐标系中的归一化Y坐标，表示前/后维度。\n
     * 取值范围为[-1.0, 1.0]。
     */
    float y;
    /**
     * @brief 对象声源在笛卡尔坐标系中的归一化Z坐标，表示上/下维度。\n
     * 取值范围为[-1.0, 1.0]。
     */
    float z;
} OH_CartesianPosition;

/**
 * @brief 表示极坐标系（polar coordinate system，也叫球坐标系）中的位置。
 *
 * 极坐标系使用方位角、俯仰角和距离定义对象声源在三维空间中的位置。
 * @since 26.0.0
 */
typedef struct OH_PolarPosition {
    /**
     * @brief 极坐标系下对象声源所在位置的方位角。\n
     * 取值范围为[-180.0, 180.0]，其中0.0表示正前方，90.0表示左侧，-90.0表示右侧，-180.0或180.0表示正后方。
     */
    float azimuth;
    /**
     * @brief 极坐标系下对象声源所在位置的俯仰角。\n
     * 取值范围为[-90.0, 90.0]，其中0.0表示水平，90.0表示正上方，-90.0表示正下方。
     */
    float elevation;
    /**
     * @brief 极坐标系下对象声源所在位置的归一化距离。\n
     * 取值范围为[0.0, 1.0]。
     */
    float distance;
} OH_PolarPosition;

/**
 * @brief 表示音频对象声源在三维空间中的位置。
 *
 * 该位置可以用笛卡尔坐标或极坐标表示。
 *
 * @since 26.0.0
 */
typedef struct OH_AudioObjectPosition {
    /**
     * @brief 对象声源是否使用笛卡尔坐标表示。\n
     * true表示使用笛卡尔坐标，false表示不使用笛卡尔坐标系，使用极坐标系。
     */
    bool isCartesian;
    /**
     * @brief 包含笛卡尔坐标或极坐标位置数据的联合体。
     */
    union {
        /**
         * @brief 笛卡尔坐标表示的位置。
         */
        OH_CartesianPosition cartesian;
        /**
         * @brief 极坐标表示的位置。
         */
        OH_PolarPosition polar;
    } pos;
} OH_AudioObjectPosition;

/**
 * @brief OH_AudioVividMetaBuilder的前向声明。
 *
 * @since 26.0.0
 */
typedef struct OH_AudioVividMetaBuilderStruct OH_AudioVividMetaBuilder;

/**
 * @brief 创建Audio Vivid元数据构建器。
 *
 * @note **生命周期管理：**\n
 * 通过本函数创建的实例不再使用时，必须调用{@link OH_AudioVividMetaBuilder_Destroy}手动释放，以避免内存泄漏。
 * @param builder 输出参数，用于获取OH_AudioVividMetaBuilder实例指针的指针。
 * @param format 指向包含音频格式信息的OH_AVFormat指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：参数builder或format为空指针或无效。\n
 *         AV_ERR_UNSUPPORT：当前设备不支持此功能。\n
 *         AV_ERR_UNKNOWN：创建构建器失败，属于未知错误，请查看日志获取详细信息。
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_Create(OH_AudioVividMetaBuilder **builder, const OH_AVFormat *format);

/**
 * @brief 更新Audio Vivid信号格式为{@link OH_AudioVividSignalFormat}.OH_AUDIO_VIVID_SIGNAL_FORMAT_MIX时的音频对象位置。
 *
 * 在此信号格式下，输入编码的PCM（Pulse Code Modulation）数据中，声道排列顺序为：声床声道在前，对象声道在后。\n
 * 对象声道按顺序与objectIndex对应，从0开始编号。
 *
 * @param builder 指向OH_AudioVividMetaBuilder的指针。
 * @param objectIndex 要更新的音频对象索引，从0开始，不超过在{@link OH_AudioVividMetaBuilder_Create}创建builder时入参format
 * 设置的{@link OH_MD_KEY_AUDIO_OBJECT_NUMBER}对应的值。
 * @param pos 音频对象声源的新位置。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：参数builder为空指针或无效，objectIndex或pos无效。
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_UpdateObjectPos(OH_AudioVividMetaBuilder *builder,
    int32_t objectIndex, OH_AudioObjectPosition pos);

/**
 * @brief 更新Audio Vivid信号格式为{@link OH_AudioVividSignalFormat}.OH_AUDIO_VIVID_SIGNAL_FORMAT_MIX时的音频对象渲染的线性增益。
 *
 * @param builder 指向OH_AudioVividMetaBuilder的指针。
 * @param objectIndex 要更新的音频对象索引，从0开始，不超过在{@link OH_AudioVividMetaBuilder_Create}创建builder时入参format
 * 设置的{@link OH_MD_KEY_AUDIO_OBJECT_NUMBER}对应的值。
 * @param gain 对象渲染时应用的线性增益值，范围为[0.0, 6.0]，线性增益0.0为静音，1.0为不变。此参数可选，如未设置则不应用增益。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：参数builder为空指针或无效，objectIndex或gain无效。
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_UpdateObjectGain(OH_AudioVividMetaBuilder *builder,
    int32_t objectIndex, float gain);

/**
 * @brief 获取元数据长度。
 *
 * @param builder 指向OH_AudioVividMetaBuilder的指针。
 * @param withStaticMeta 设置输出的长度是否包含静态元数据。true表示输出长度包含静态元数据；false表示输出长度仅包含动态元数据。
 * @param len 用于接收元数据长度的指针。单位为字节。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：参数builder为空指针或无效，len为空指针。
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_GetMetaLen(const OH_AudioVividMetaBuilder *builder, bool withStaticMeta,
    int32_t *len);

/**
 * @brief 获取元数据缓冲区。
 *
 * @param builder 指向OH_AudioVividMetaBuilder的指针。
 * @param withStaticMeta 设置输出的长度是否包含静态元数据。true表示输出缓冲区包含静态元数据；false表示输出缓冲区仅包含动态元数据。
 * @param buffer 用于接收元数据内容的缓冲区指针。
 * @param len 缓冲区长度。单位为字节。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：builder为空指针或无效，buffer为空指针或len不足。
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_GetMeta(const OH_AudioVividMetaBuilder *builder, bool withStaticMeta,
    uint8_t *buffer, int32_t len);

/**
 * @brief 销毁Audio Vivid元数据构建器并释放资源。
 *
 * @param builder 指向待销毁的OH_AudioVividMetaBuilder的指针。
 * @return AV_ERR_OK：执行成功。\n
 *         AV_ERR_INVALID_VAL：参数builder为空指针。
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_Destroy(OH_AudioVividMetaBuilder *builder);

#ifdef __cplusplus
}
#endif

/**
 * @brief 创建一个空的Audio Vivid元数据构建器。
 *
 * 该函数用于合并Audio Vivid元数据的场景。在创建一个空的元数据构造器后，
 * 用户可以通过调用{@link OH_AudioVividMetaBuilder_UpdateBaseMeta}接口来增加、修改或者删除音频对象。
 *
 * @note 生命周期管理：
 * 通过本函数创建的实例不再使用时，必须调用{@link OH_AudioVividMetaBuilder_Destroy}手动释放，以避免内存泄漏。
 * @param builder 输出参数，用于获取OH_AudioVividMetaBuilder实例指针的指针。
 * @return <ul>
 *         <li>AV_ERR_OK：执行成功。</li>
 *         <li>AV_ERR_INVALID_VAL：参数builder为空指针或无效。</li>
 *         <li>AV_ERR_UNSUPPORT：当前设备不支持此功能。</li>
 *         <li>AV_ERR_UNKNOWN：创建构建器失败，属于未知错误，请查看日志获取详细信息。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_CreateEmptyBuilder(OH_AudioVividMetaBuilder **builder);

/**
 * @brief 更新Audio Vivid元数据构造器的基础元数据。
 *
 * buffer需要包含完整的Audio Vivid元数据。
 * 构造器会将元数据里的音频声床和音频对象信息保留下来。
 *
 * @note 约束条件：
 * 基础元数据内音频的声床声道数 + 对象数必须小于等于16个。
 * @param builder 指向OH_AudioVividMetaBuilder的指针。
 * @param buffer 指向包含基础元数据的指针。
 * @param len 缓冲区长度。单位为字节（Byte）。
 * @return <ul>
 *         <li>AV_ERR_OK：执行成功。</li>
 *         <li>AV_ERR_INVALID_VAL：参数builder、format为空指针或无效。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_UpdateBaseMeta(OH_AudioVividMetaBuilder *builder, const uint8_t *buffer,
    int32_t len);

/**
 * @brief Audio Vivid元数据构造器内添加一个音频对象。
 *
 * 添加音频对象后，可以通过{@link OH_AudioVividMetaBuilder_UpdateObjectPos}和{@link OH_AudioVividMetaBuilder_UpdateObjectGain}接口，
 * 更新该对象的位置和对象渲染的线性增益。
 *
 * @note 约束条件：
 * 音频的声床声道数 + 对象数必须小于等于16个。
 * @param builder 指向OH_AudioVividMetaBuilder的指针。
 * @param objectIndex 输出参数，用于输出新增对象的索引。
 * @return <ul>
 *         <li>AV_ERR_OK：执行成功。</li>
 *         <li>AV_ERR_INVALID_VAL：参数builder、objectIndex为空指针或无效。</li>
 *         <li>AV_ERR_UNKNOWN：添加对象失败，属于未知错误，请查看日志获取详细信息。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_AddObject(OH_AudioVividMetaBuilder *builder, int32_t *objectIndex);

/**
 * @brief 从Audio Vivid元数据构造器内删除一个音频对象。
 *
 * 只有通过{@link OH_AudioVividMetaBuilder_AddObject}函数创建的音频对象可以被删除。
 * 通过{@link OH_AudioVividMetaBuilder_Destroy}函数新增的音频对象无法删除。
 * 删除音频对象后，其他音频对象的索引保持不变。
 *
 * @param builder 指向OH_AudioVividMetaBuilder的指针。
 * @param objectIndex 要移除的音频对象的索引。
 * @return <ul>
 *         <li>AV_ERR_OK：执行成功。</li>
 *         <li>AV_ERR_INVALID_VAL：</li>
 *         <li>    1. 参数builder为空指针或无效；</li>
 *         <li>    2. 参数objectIndex无效。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AVErrCode OH_AudioVividMetaBuilder_RemoveObject(OH_AudioVividMetaBuilder *builder, int32_t objectIndex);

#endif // NATIVE_AUDIO_VIVID_H

/** @} */