/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @addtogroup OHAudioSuite
 * @{
 *
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 22
 * @version 1.0
 */
/**
 * @file native_audio_suite_base.h
 *
 * @brief 声明音频编创相关底层数据结构。
 *
 * @library libohaudiosuite.so
 * @syscap SystemCapability.Multimedia.Audio.SuiteEngine
 * @kit AudioKit
 * @since 22
 * @version 1.0
 */
#ifndef NATIVE_AUDIO_SUITE_BASE_H
#define NATIVE_AUDIO_SUITE_BASE_H
#include <stdint.h>
#include "multimedia/native_audio_channel_layout.h"
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 定义音频编创节点类型。
 *
 * @since 22
 */
typedef enum {
    /**
     * 输入节点，支持从应用程序获取音频数据。
     * @since 22
     */
    INPUT_NODE_TYPE_DEFAULT = 1,
    /**
     * 输出节点，支持向应用程序提供音频数据。
     * @since 22
     */
    OUTPUT_NODE_TYPE_DEFAULT = 101,
    /**
     * 均衡器效果节点。均衡器效果节点输出的音频格式如下：<br> 采样率：48000Hz。<br> 采样格式：{@link OH_Audio_SampleFormat}.AUDIO_SAMPLE_S16LE。<br> 声道数：2。
     * @since 22
     */
    EFFECT_NODE_TYPE_EQUALIZER = 201,
    /**
     * 降噪效果节点。降噪效果节点输出的音频格式如下：<br> 采样率：16000Hz。<br> 采样格式：{@link OH_Audio_SampleFormat}.AUDIO_SAMPLE_S16LE。<br> 声道数：1。
     * @since 22
     */
    EFFECT_NODE_TYPE_NOISE_REDUCTION = 202,
    /**
     * 声场效果节点。声场效果节点支持的声场类型：{@link OH_SoundFieldType}。<br> 声场效果节点输出的音频格式如下：<br> 采样率：48000Hz。<br> 采样格式：
     * {@link OH_Audio_SampleFormat}.AUDIO_SAMPLE_S16LE。<br> 声道数：2。
     * @since 22
     */
    EFFECT_NODE_TYPE_SOUND_FIELD = 203,
    /**
     * 音源分离效果节点。音源分离效果节点只能连接输出节点。<br> 音源分离效果节点输出的音频格式如下：<br> 采样率：48000Hz。<br> 采样格式：{@link OH_Audio_SampleFormat}.
     * AUDIO_SAMPLE_F32LE。<br> 声道数：4（前2个声道用于人声，后2个声道用于伴奏）。
     * @since 22
     */
    EFFECT_MULTII_OUTPUT_NODE_TYPE_AUDIO_SEPARATION = 204,
    /**
     * 声音美化效果节点。声音美化效果节点支持的声音美化类型：{@link OH_VoiceBeautifierType}。<br> 声音美化效果节点输出的音频格式如下：<br> 采样率：48000Hz。<br> 采样格式：
     * {@link OH_Audio_SampleFormat}.AUDIO_SAMPLE_S16LE。<br> 声道数：2。
     * @since 22
     */
    EFFECT_NODE_TYPE_VOICE_BEAUTIFIER = 205,
    /**
     * 环境效果节点。环境效果节点输出的音频格式如下：<br> 采样率：48000Hz。<br> 采样格式：{@link OH_Audio_SampleFormat}.AUDIO_SAMPLE_S16LE。<br> 声道数：2。
     * @since 22
     */
    EFFECT_NODE_TYPE_ENVIRONMENT_EFFECT = 206,
    /**
     * 混音效果节点。混音效果节点输出的音频格式如下：<br> 采样率：{@link OH_Audio_SampleRate}。<br> 采样格式：{@link OH_Audio_SampleFormat}.
     * AUDIO_SAMPLE_F32LE。<br> 声道数：2。
     * @since 22
     */
    EFFECT_NODE_TYPE_AUDIO_MIXER = 207,
    /**
     * 空间渲染效果节点。空间渲染效果节点输出的音频格式如下：<br> 采样率：48000Hz。<br> 采样格式：{@link OH_Audio_SampleFormat}.AUDIO_SAMPLE_S16LE。<br> 声道数：
     * 2。
     * @since 23
     */
    EFFECT_NODE_TYPE_SPACE_RENDER = 208,
    /**
     * 传统变声效果节点。传统变声效果节点输出的音频格式如下：<br> 采样率：16000Hz。<br> 采样格式：{@link OH_Audio_SampleFormat}.AUDIO_SAMPLE_S16LE。<br> 声道数：
     * 1。
     * @since 23
     */
    EFFECT_NODE_TYPE_PURE_VOICE_CHANGE = 209,
    /**
     * 通用变声效果节点。通用变声效果节点的输出音频格式如下：<br> 采样率：48000Hz。<br> 采样格式：{@link OH_Audio_SampleFormat}.AUDIO_SAMPLE_S16LE。<br> 声道数：
     * 2。
     * @since 23
     */
    EFFECT_NODE_TYPE_GENERAL_VOICE_CHANGE = 210,
    /**
     * 变速变调效果节点。变速变调效果节点的输出音频格式如下：<br> 采样率：48000Hz。<br> 采样格式：{@link OH_Audio_SampleFormat}.AUDIO_SAMPLE_S16LE。<br> 声道数：
     * 1。
     * @since 23
     */
    EFFECT_NODE_TYPE_TEMPO_PITCH = 211,
    /**
     * HOA（High-Order Ambisonics）转双耳空间音频节点。HOA转双耳空间音频节点输入的音频格式如下：<br> 采样率：{@link OH_Audio_SampleRate}.SAMPLE_RATE_16000、
     * {@link OH_Audio_SampleRate}.SAMPLE_RATE_48000。<br> 采样格式：{@link OH_Audio_SampleFormat}。<br> 声道布局：1阶至3阶HOA，取值如下：<
     * br> {@link OH_AudioChannelLayout}.CH_LAYOUT_AMB_ORDER1_ACN_N3D、{@link OH_AudioChannelLayout}.
     * CH_LAYOUT_AMB_ORDER1_ACN_SN3D、{@link OH_AudioChannelLayout}.CH_LAYOUT_AMB_ORDER1_FUMA、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_AMB_ORDER2_ACN_N3D、{@link OH_AudioChannelLayout}.
     * CH_LAYOUT_AMB_ORDER2_ACN_SN3D、{@link OH_AudioChannelLayout}.CH_LAYOUT_AMB_ORDER2_FUMA、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_AMB_ORDER3_ACN_N3D、{@link OH_AudioChannelLayout}.
     * CH_LAYOUT_AMB_ORDER3_ACN_SN3D、{@link OH_AudioChannelLayout}.CH_LAYOUT_AMB_ORDER3_FUMA。HOA转双耳空间音频节点的输出音频格式如下：<br>
     * 采样率：48000Hz。<br> 采样格式：{@link OH_Audio_SampleFormat}.AUDIO_SAMPLE_S32LE。<br> 声道数：2。<br> 该节点的前置节点必须连接音频格式为HOA的输入节点，
     * 如果未正确连接，在调用{@link OH_AudioSuiteEngine_StartPipeline}接口时将会报错。
     * @since 26.0.0
     */
    EFFECT_NODE_TYPE_HOA_SPACE_RENDER = 212
} OH_AudioNode_Type;

/**
 * @brief 定义音频节点系统类型。
 * @systemapi
 * @since 26.0.0
 */
typedef enum OH_AudioSuite_SystemNodeType {
    /**
     * 对话增强系统效果节点。
     *
     * @since 26.0.0
     */
    OH_AUDIOSUITE_EFFECT_NODE_SYSTEM_TYPE_DIALOGUE_ENHANCE = 301,
    /**
     * 语音美化系统效果节点。
     *
     * @since 26.0.0
     */
    OH_AUDIOSUITE_EFFECT_NODE_SYSTEM_TYPE_VOICE_BEAUTIFIER = 302
} OH_AudioSuite_SystemNodeType;

/**
 * @brief 定义音频编创管线工作模式。
 *
 * @since 22
 */
typedef enum {
    /**
     * 编辑模式，管线处于该工作模式下可创建多种效果节点进行音频处理。
     * @since 22
     */
    AUDIOSUITE_PIPELINE_EDIT_MODE = 1,
    /**
     * 实时预览模式，即在音频处理过程中实时预览已处理的音频。<br> 在API version 23之前，实时预览模式下管线仅支持均衡器效果节点；<br> 在API version 23及以后，实时预览模式下管线支持所有效果节点。
     * @since 22
     */
    AUDIOSUITE_PIPELINE_REALTIME_MODE = 2
} OH_AudioSuite_PipelineWorkMode;
/**
 * @brief 定义音频编创管线运行状态。
 *
 * @since 22
 */
typedef enum {
    /**
     * 管线处于停止状态。
     * @since 22
     */
    AUDIOSUITE_PIPELINE_STOPPED = 1,
    /**
     * 管线处于运行状态。
     * @since 22
     */
    AUDIOSUITE_PIPELINE_RUNNING = 2
} OH_AudioSuite_PipelineState;
/**
 * @brief 音频编创错误码。
 *
 * @since 22
 */
typedef enum {
    /**
     * @error
     * 调用成功。
     * @since 22
     */
    AUDIOSUITE_SUCCESS = 0,
    /**
     * @error
     * 输入参数无效。
     * @since 22
     */
    AUDIOSUITE_ERROR_INVALID_PARAM = 1,
    /**
     * @error
     * 非法状态。
     * @since 22
     */
    AUDIOSUITE_ERROR_INVALID_STATE = 2,
    /**
     * @error
     * 系统通用错误。
     * @since 22
     */
    AUDIOSUITE_ERROR_SYSTEM = 3,
    /**
     * @error
     * 不支持的音频格式，如不支持的编码类型、采样格式等。
     * @since 22
     */
    AUDIOSUITE_ERROR_UNSUPPORTED_FORMAT = 4,
    /**
     * @error
     * 引擎不存在。
     * @since 22
     */
    AUDIOSUITE_ERROR_ENGINE_NOT_EXIST = 5,
    /**
     * @error
     * 管线不存在。
     * @since 22
     */
    AUDIOSUITE_ERROR_PIPELINE_NOT_EXIST = 6,
    /**
     * @error
     * 节点不存在。
     * @since 22
     */
    AUDIOSUITE_ERROR_NODE_NOT_EXIST = 7,
    /**
     * @error
     * 节点之间不支持连接。
     * @since 22
     */
    AUDIOSUITE_ERROR_UNSUPPORTED_CONNECT = 8,
    /**
     * @error
     * 不支持的操作。例如，效果节点不支持设置音频格式。
     * @since 22
     */
    AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION = 9,
    /**
     * @error
     * 创建管线或者节点超过系统最大数量限制。具体情况如下：<br> 引擎最多支持创建10条管线（其中，实时预览管线最多创建1条）。<br> 每一个管线中，输出节点的数量不超过1个，混音节点的数量不超过3个，
     * 音源分离节点的数量不超过1个。<br> 在API version 24之前，每一个管线中，输入节点的数量不超过5个，其余效果节点的数量不超过5个；在API version 24及以后，每一个管线中，输入节点的数量不超过15个，
     * 其余效果节点的数量不超过15个。
     * @since 22
     */
    AUDIOSUITE_ERROR_CREATED_EXCEED_SYSTEM_LIMITS = 10,
    /**
     * @error
     * 参数缺少必要参数。例如，输入节点未设置回调函数、输出节点未设置音频格式。
     * @since 22
     */
    AUDIOSUITE_ERROR_REQUIRED_PARAMETERS_MISSING = 11,
    /**
     * @error
     * 操作超时。
     * @since 22
     */
    AUDIOSUITE_ERROR_TIMEOUT = 12,
    /**
     * @error
     * 内存申请失败。
     * @since 22
     */
    AUDIOSUITE_ERROR_MEMORY_ALLOC_FAILED = 13
} OH_AudioSuite_Result;
/**
 * @brief 定义音频编创节点音频流的位深度。
 *
 * @since 22
 */
typedef enum {
    /**
     * Unsigned 8位。
     * @since 22
     */
    AUDIO_SAMPLE_U8 = 0,
    /**
     * Short 16位小端。
     * @since 22
     */
    AUDIO_SAMPLE_S16LE = 1,
    /**
     * Short 24位小端。
     * @since 22
     */
    AUDIO_SAMPLE_S24LE = 2,
    /**
     * Short 32位小端。
     * @since 22
     */
    AUDIO_SAMPLE_S32LE = 3,
    /**
     * Float 32位小端。
     * @since 22
     */
    AUDIO_SAMPLE_F32LE = 4
} OH_Audio_SampleFormat;
/**
 * @brief 定义音频流编码类型。
 *
 * @since 22
 */
typedef enum {
    /**
     * PCM编码。
     * @since 22
     */
    AUDIO_ENCODING_TYPE_RAW = 0
} OH_Audio_EncodingType;

/**
 * @brief 定义音频采样率。
 *
 * @since 22
 */
typedef enum {
    /**
     * 采样率8kHz。
     * @since 22
     */
    SAMPLE_RATE_8000 = 8000,
    /**
     * 采样率11.025kHz。
     * @since 22
     */
    SAMPLE_RATE_11025 = 11025,
    /**
     * 采样率12kHz。
     * @since 22
     */
    SAMPLE_RATE_12000 = 12000,
    /**
     * 采样率16kHz。
     * @since 22
     */
    SAMPLE_RATE_16000 = 16000,
    /**
     * 采样率22.05kHz。
     * @since 22
     */
    SAMPLE_RATE_22050 = 22050,
    /**
     * 采样率24kHz。
     * @since 22
     */
    SAMPLE_RATE_24000 = 24000,
    /**
     * 采样率32kHz。
     * @since 22
     */
    SAMPLE_RATE_32000 = 32000,
    /**
     * 采样率44.1kHz。
     * @since 22
     */
    SAMPLE_RATE_44100 = 44100,
    /**
     * 采样率48kHz。
     * @since 22
     */
    SAMPLE_RATE_48000 = 48000,
    /**
     * 采样率64kHz。
     * @since 22
     */
    SAMPLE_RATE_64000 = 64000,
    /**
     * 采样率88.2kHz。
     * @since 22
     */
    SAMPLE_RATE_88200 = 88200,
    /**
     * 采样率96kHz。
     * @since 22
     */
    SAMPLE_RATE_96000 = 96000,
    /**
     * 采样率176.4kHz。
     * @since 22
     */
    SAMPLE_RATE_176400 = 176400,
    /**
     * 采样率192kHz。
     * @since 22
     */
    SAMPLE_RATE_192000 = 192000
} OH_Audio_SampleRate;

/**
 * @brief 定义音频编创的音频流信息，用于描述基本音频格式。
 *
 * @since 22
 */
typedef struct OH_AudioFormat {
    /**
     * @brief 音频流采样率。
     *
     * @since 22
     */
    OH_Audio_SampleRate samplingRate;
    /**
     * @brief 音频流声道布局。<br>在API版本26.0.0之前，仅支持CH_LAYOUT_MONO和CH_LAYOUT_STEREO。<br>在API版本26.0.0及以后，支持CH_LAYOUT_MONO、
     * CH_LAYOUT_STEREO、CH_LAYOUT_STEREO_DOWNMIX、CH_LAYOUT_2POINT1、CH_LAYOUT_3POINT0、CH_LAYOUT_SURROUND、
     * CH_LAYOUT_3POINT1、CH_LAYOUT_4POINT0、CH_LAYOUT_QUAD_SIDE、CH_LAYOUT_QUAD、CH_LAYOUT_2POINT0POINT2、CH_LAYOUT_4POINT1、
     * CH_LAYOUT_5POINT0、CH_LAYOUT_5POINT0_BACK、CH_LAYOUT_2POINT1POINT2、CH_LAYOUT_3POINT0POINT2、CH_LAYOUT_5POINT1、
     * CH_LAYOUT_5POINT1_BACK、CH_LAYOUT_6POINT0、CH_LAYOUT_3POINT1POINT2、CH_LAYOUT_6POINT0_FRONT、CH_LAYOUT_HEXAGONAL、
     * CH_LAYOUT_6POINT1、CH_LAYOUT_6POINT1_BACK、CH_LAYOUT_6POINT1_FRONT、CH_LAYOUT_7POINT0、CH_LAYOUT_7POINT0_FRONT、
     * CH_LAYOUT_7POINT1、CH_LAYOUT_OCTAGONAL、CH_LAYOUT_5POINT1POINT2、CH_LAYOUT_7POINT1_WIDE、CH_LAYOUT_7POINT1_WIDE_BACK、
     * CH_LAYOUT_AMB_ORDER1_ACN_N3D、CH_LAYOUT_AMB_ORDER1_ACN_SN3D、CH_LAYOUT_AMB_ORDER1_FUMA、
     * CH_LAYOUT_AMB_ORDER2_ACN_N3D、CH_LAYOUT_AMB_ORDER2_ACN_SN3D、CH_LAYOUT_AMB_ORDER2_FUMA、
     * CH_LAYOUT_AMB_ORDER3_ACN_N3D、CH_LAYOUT_AMB_ORDER3_ACN_SN3D、CH_LAYOUT_AMB_ORDER3_FUMA。
     *
     * @since 22
     */
    OH_AudioChannelLayout channelLayout;
    /**
     * @brief 音频流声道数。<br>在API版本26.0.0之前，仅支持1声道和2声道。<br>在API版本26.0.0及以后，支持1至9声道及16声道。
     *
     * @since 22
     */
    uint32_t channelCount;
    /**
     * @brief 音频流编码类型。
     *
     * @since 22
     */
    OH_Audio_EncodingType encodingType;
    /**
     * @brief 音频流采样格式。
     *
     * @since 22
     */
    OH_Audio_SampleFormat sampleFormat;
} OH_AudioFormat;

/**
 * @brief 定义音频格式信息结构，用于描述系统节点的基本音频格式。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_AudioSuite_SystemNodeFormat {
    /**
     * @brief 音频采样率。
     *
     * @since 26.0.0
     */
    OH_Audio_SampleRate samplingRate;
    /**
     * @brief 声道布局。
     *
     * @since 26.0.0
     */
    OH_AudioChannelLayout channelLayout;
    /**
     * @brief 音频通道数。
     *
     * @since 26.0.0
     */
    uint32_t channelCount;
    /**
     * @brief 音频编码格式。
     *
     * @since 26.0.0
     */
    int32_t encoding;
    /**
     * @brief 音频样本格式。
     *
     * @since 26.0.0
     */
    OH_Audio_SampleFormat sampleFormat;
} OH_AudioSuite_SystemNodeFormat;

/**
 * @brief 定义多路输出渲染接口的输出数据描述。当管线中存在多输出效果节点时，通过多输出渲染接口获取处理过后的音频数据。
 *
 * @since 22
 */
typedef struct OH_AudioDataArray {
    /**
     * @brief 输出的音频数据地址。
     *
     * @since 22
     */
    void **audioDataArray;
    /**
     * @brief 音频数据audioDataArray数组的元素个数。
     *
     * @since 22
     */
    int32_t arraySize;
    /**
     * @brief audioDataArray数组中每个地址指向的内存大小，单位为字节（Byte）。应确保每个地址指向的内存大小均为requestFrameSize字节。
     *
     * @since 22
     */
    int32_t requestFrameSize;
} OH_AudioDataArray;

/**
 * @brief 定义音频元数据帧结构。
 * 该结构用于将音频数据和元数据一起传递。
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_AudioSuite_MetaFrame {
    /**
     * @brief 音频数据指针。
     *
     * @since 26.0.0
     */
    void* audioData;
    /**
     * @brief 音频数据大小。
     *
     * @since 26.0.0
     */
    int32_t audioDataSize;
    /**
     * @brief 元数据指针。
     *
     * @since 26.0.0
     */
    void* metaData;
    /**
     * @brief 元数据大小。
     *
     * @since 26.0.0
     */
    int32_t metaDataSize;
} OH_AudioSuite_MetaFrame;

/**
 * @brief 定义音频编创声场效果节点的效果模式。
 *
 * @since 22
 */
typedef enum {
    /**
     * 前置声场效果。
     * @since 22
     */
    SOUND_FIELD_FRONT_FACING = 1,
    /**
     * 宏大声场效果。
     * @since 22
     */
    SOUND_FIELD_GRAND = 2,
    /**
     * 聆听声场效果。
     * @since 22
     */
    SOUND_FIELD_NEAR = 3,
    /**
     * 宽广声场效果。
     * @since 22
     */
    SOUND_FIELD_WIDE = 4
} OH_SoundFieldType;
/**
 * @brief 定义音频编创环境效果节点的模式。
 *
 * @since 22
 */
typedef enum {
    /**
     * 环境节点效果为广播。
     * @since 22
     */
    ENVIRONMENT_TYPE_BROADCAST = 1,
    /**
     * 环境节点效果为电话听筒。
     * @since 22
     */
    ENVIRONMENT_TYPE_EARPIECE = 2,
    /**
     * 环境节点效果为水下。
     * @since 22
     */
    ENVIRONMENT_TYPE_UNDERWATER = 3,
    /**
     * 环境节点效果为留声机。
     * @since 22
     */
    ENVIRONMENT_TYPE_GRAMOPHONE = 4
} OH_EnvironmentType;
/**
 * @brief 定义音频编创美化效果节点模式。
 *
 * @since 22
 */
typedef enum {
    /**
     * 声音美化节点效果为清澈。
     * @since 22
     */
    VOICE_BEAUTIFIER_TYPE_CLEAR = 1,
    /**
     * 声音美化节点效果为剧场。
     * @since 22
     */
    VOICE_BEAUTIFIER_TYPE_THEATRE = 2,
    /**
     * 声音美化节点效果为CD。
     * @since 22
     */
    VOICE_BEAUTIFIER_TYPE_CD = 3,
    /**
     * 声音美化节点效果为录音棚。
     * @since 22
     */
    VOICE_BEAUTIFIER_TYPE_RECORDING_STUDIO = 4
} OH_VoiceBeautifierType;
/**
 * @brief 定义均衡器频带数量为10个。
 *
 * @since 22
 */
#define EQUALIZER_BAND_NUM (10)

/**
 * @brief 定义音频编创均衡器效果节点配置参数。
 *
 * @since 22
 */
typedef struct OH_EqualizerFrequencyBandGains {
    /**
     * The equalizer supports gain adjustment for 10 specific frequencies.
     * Frequencies: 31 Hz, 62 Hz, 125 Hz, 250 Hz, 500 Hz, 1 kHz, 2 kHz, 4 kHz, 8 kHz, 16 kHz.
     *
     * @since 22
     */
    int32_t gains[EQUALIZER_BAND_NUM];
} OH_EqualizerFrequencyBandGains;

/**
 * Default equalization effect band gains.
 * Gains is {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_DEFAULT;
/**
 * Ballad equalization effect band gains.
 * Gains is {3, 5, 2, -4, 1, 2, -3, 1, 4, 5}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_BALLADS;

/**
 * Chinese style equalization effect band gains.
 * Gains is {0, 0, 2, 0, 0, 4, 4, 2, 2, 5}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_CHINESE_STYLE;

/**
 * Classic equalization effect band gains.
 * Gains is {2, 3, 2, 1, 0, 0, -5, -5, -5, -6}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_CLASSICAL;

/**
 * Dance music equalization effect band gains.
 * Gains is {4, 3, 2, -3, 0, 0, 5, 4, 2, 0}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_DANCE_MUSIC;

/**
 * Jazz equalization effect band gains.
 * Gains is {2, 0, 2, 3, 6, 5, -1, 3, 4, 4}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_JAZZ;

/**
 * Pop equalization effect band gains.
 * Gains is {5, 2, 1, -1, -5, -5, -2, 1, 2, 4}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_POP;

/**
 * R&B equalization effect band gains.
 * Gains is {1, 4, 5, 3, -2, -2, 2, 3, 5, 5}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_RB;

/**
 * Rock equalization effect band gains.
 * Gains is {6, 4, 4, 2, 0, 1, 3, 3, 5, 4}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_ROCK;

/**
 * @brief 声明音频编创引擎，用来管理音频编创管线。
 *
 * @since 22
 */
typedef struct OH_AudioSuiteEngineStruct OH_AudioSuiteEngine;

/**
 * @brief 声明音频编创管线，用来管理音频编创节点。
 *
 * @since 22
 */
typedef struct OH_AudioSuitePipelineStruct OH_AudioSuitePipeline;

/**
 * @brief 声明音频编创节点，用于描述音频编创节点实例。
 *
 * @since 22
 */
typedef struct OH_AudioNodeStruct OH_AudioNode;

/**
 * @brief 声明音频编创节点的构造器。用于构建{@link OH_AudioNode}，配置输入/输出节点数据格式，配置输入节点回调接口。
 *
 * @since 22
 */
typedef struct OH_AudioNodeBuilderStruct OH_AudioNodeBuilder;

/**
 * @brief 定义3D空间渲染效果节点固定摆位模式的配置参数。<br>左手坐标系：伸出左手，用拇指和食指形成一个“L”形。拇指指向右侧，食指向上，其余手指指向前。此时形成了一个3D的左手坐标系。在这个坐标系中，拇指、
 * 食指和其他手指分别代表x轴、y轴和z轴的正方向。
 *
 * @since 23
 */
typedef struct OH_AudioSuite_SpaceRenderPositionParams {
    /**
     * 空间中的X坐标。取值范围为[-5.0, 5.0]，单位为米。
     * @since 23
     */
    float x;
    /**
     * 空间中的Y坐标。取值范围为[-5.0, 5.0]，单位为米。
     * @since 23
     */
    float y;
    /**
     * 空间中的Z坐标。取值范围为[-5.0, 5.0]，单位为米。
     * @since 23
     */
    float z;
} OH_AudioSuite_SpaceRenderPositionParams;

/**
 * @brief 定义空间渲染效果节点旋转模式环绕方向。
 *
 * @since 23
 */
typedef enum {
    /**
     * 逆时针旋转。
     * @since 23
     */
    SPACE_RENDER_CCW = 0,
    /**
     * 顺时针旋转。
     * @since 23
     */
    SPACE_RENDER_CW = 1
} OH_AudioSuite_SurroundDirection;

/**
 * @brief 定义空间渲染效果节点旋转模式配置参数。
 *
 * @since 23
 */
typedef struct OH_AudioSuite_SpaceRenderRotationParams {
    /**
     * 空间中的X坐标。取值范围为[-5.0, 5.0]，单位为米。
     * @since 23
     */
    float x;
    /**
     * 空间中的Y坐标。取值范围为[-5.0, 5.0]，单位为米。
     * @since 23
     */
    float y;
    /**
     * 空间中的Z坐标。取值范围为[-5.0, 5.0]，单位为米。
     * @since 23
     */
    float z;
    /**
     * 单周环绕时间。取值范围为[2, 40]，单位为秒。
     * @since 23
     */
    int32_t surroundTime;
    /**
     * 单周环绕方向。取值范围为[0, 1]。
     * @since 23
     */
    OH_AudioSuite_SurroundDirection surroundDirection;
} OH_AudioSuite_SpaceRenderRotationParams;

/**
 * @brief 定义空间渲染效果节点扩展模式配置参数。
 *
 * @since 23
 */
typedef struct OH_AudioSuite_SpaceRenderExtensionParams {
    /**
     * 扩展半径。取值范围为[1.0, 5.0]，单位为米。
     * @since 23
     */
    float extRadius;
    /**
     * 扩展角度。取值范围为(0, 360)，单位为度。
     * @since 23
     */
    int32_t extAngle;
} OH_AudioSuite_SpaceRenderExtensionParams;

/**
 * @brief 定义音频编创传统变声效果节点的性别。
 *
 * @since 23
 */
typedef enum {
    /**
     * 设置女声。
     * @since 23
     */
    PURE_VOICE_CHANGE_FEMALE = 1,
    /**
     * 设置男声。
     * @since 23
     */
    PURE_VOICE_CHANGE_MALE = 2
} OH_AudioSuite_PureVoiceChangeGenderOption;

/**
 * @brief 定义音频编创传统变声效果节点的变声类型。
 *
 * @since 23
 */
typedef enum {
    /**
     * 传统变声效果节点为卡通类型。
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_CARTOON = 1,
    /**
     * 传统变声效果节点为萝莉类型。
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_CUTE = 2,
    /**
     * 传统变声效果节点为女声类型。
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_FEMALE = 3,
    /**
     * 传统变声效果节点为男声类型。
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_MALE = 4,
    /**
     * 传统变声效果节点为怪兽类型。
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_MONSTER = 5,
    /**
     * 传统变声效果节点为机器人类型。
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_ROBOTS = 6,
    /**
     * 传统变声效果节点为大叔类型。
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_SEASONED = 7
} OH_AudioSuite_PureVoiceChangeType;

/**
 * Use system recommended pitch.
 * Use in {@link OH_AudioSuite_PureVoiceChangeOption}.
 *
 * @since 23
 */
#define OH_PURE_VOICE_DEFAULT_PITCH (0.0f)

/**
 * @brief 定义音频编创传统变声选项。
 *
 * @since 23
 */
typedef struct OH_AudioSuite_PureVoiceChangeOption {
    /**
     * 指定传统变声性别。
     * @since 23
     */
    OH_AudioSuite_PureVoiceChangeGenderOption optionGender;
    /**
     * 指定传统变声类型。
     * @since 23
     */
    OH_AudioSuite_PureVoiceChangeType optionType;
    /**
     * 指定传统变声音调。如果使用系统中的默认音调以获得最佳效果, 设置为{@link 宏定义}中的OH_PURE_VOICE_DEFAULT_PITCH。<br> 设置自定义音调的取值范围为[0.3f, 3.0f]。
     * @since 23
     */
    float pitch;
} OH_AudioSuite_PureVoiceChangeOption;

/**
 * @brief 定义音频编创通用变声的节点类型。
 *
 * @since 23
 */
typedef enum {
    /**
     * 传统变声效果节点为萝莉类型。
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_CUTE = 1,
    /**
     * 通用变声效果节点为赛博朋克类型。
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_CYBERPUNK = 2,
    /**
     * 传统变声效果节点为女声类型。
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_FEMALE = 3,
    /**
     * 传统变声效果节点为男声类型。
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_MALE = 4,
    /**
     * 通用变声效果节点为混响类型。
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_MIX = 5,
    /**
     * 传统变声效果节点为怪兽类型。
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_MONSTER = 6,
    /**
     * 传统变声效果节点为大叔类型。
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_SEASONED = 7,
    /**
     * 通用变声效果节点为合成器类型。
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_SYNTH = 8,
    /**
     * 通用变声效果节点为颤音类型。
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_TRILL = 9,
    /**
     * 通用变声效果节点为战争类型。
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_WAR = 10
} OH_AudioSuite_GeneralVoiceChangeType;

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_AUDIO_SUITE_BASE_H