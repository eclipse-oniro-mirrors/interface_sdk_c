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
 * @brief Declare underlying data structure.
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
 * @brief Define audio node type.
 *
 * @since 22
 */
typedef enum {
    /**
     * @brief Default input node type, this input node type supports getting audio data from application.
     *
     * @since 22
     */
    INPUT_NODE_TYPE_DEFAULT = 1,
    /**
     * @brief Default output node type, this output node type supports providing audio data to the application.
     *
     * @since 22
     */
    OUTPUT_NODE_TYPE_DEFAULT = 101,
    /**
     * @brief Equalization node type.
     * The audio format output by the equalizer node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 2.
     *
     * @since 22
     */
    EFFECT_NODE_TYPE_EQUALIZER = 201,
    /**
     * @brief Noise reduction node type.
     * The audio format output by the noise reduction node is as follows:
     * Sample rate: 16000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 1.
     *
     * @since 22
     */
    EFFECT_NODE_TYPE_NOISE_REDUCTION = 202,
    /**
     * @brief Sound field node type. Support sound field type {@link OH_SoundFieldType}.
     * The audio format output by the sound field node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 2.
     *
     * @since 22
     */
    EFFECT_NODE_TYPE_SOUND_FIELD = 203,
    /**
     * @brief Audio separation node type, it can only connect to output node.
     * The audio format output by the audio separation node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_F32LE}.
     * Channels: 4 (First 2 channels for vocals; last 2 channels for accompaniment).
     *
     * @since 22
     */
    EFFECT_MULTII_OUTPUT_NODE_TYPE_AUDIO_SEPARATION = 204,
    /**
     * @brief Voice beautifier node type. Supports beautifier type {@link OH_VoiceBeautifierType}.
     * The audio format output by the voice beautifier node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 2.
     *
     * @since 22
     */
    EFFECT_NODE_TYPE_VOICE_BEAUTIFIER = 205,
    /**
     * @brief Scene effect node type.
     * The audio format output by the environment node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 2.
     *
     * @since 22
     */
    EFFECT_NODE_TYPE_ENVIRONMENT_EFFECT = 206,
    /**
     * @brief Audio mixer node type.
     * The audio format output by the mixer node is as follows:
     * Sample rate: {@link OH_Audio_SampleRate}.
     * Sample format: {@link AUDIO_SAMPLE_F32LE}.
     * Channels: 2.
     *
     * @since 22
     */
    EFFECT_NODE_TYPE_AUDIO_MIXER = 207,
    /**
     * @brief Space render node type.
     * The audio format output by the space render node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 2.
     *
     * @since 23
     */
    EFFECT_NODE_TYPE_SPACE_RENDER = 208,
    /**
     * @brief Pure voice change node type.
     * The audio format output by the pure voice change node is as follows:
     * Sample rate: 16000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 1.
     *
     * @since 23
     */
    EFFECT_NODE_TYPE_PURE_VOICE_CHANGE = 209,
    /**
     * @brief General voice change node type.
     * The audio format output by the general voice change node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 2.
     *
     * @since 23
     */
    EFFECT_NODE_TYPE_GENERAL_VOICE_CHANGE = 210,
    /**
     * @brief Tempo and pitch node type.
     * The audio format output by the tempo and pitch node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 1.
     *
     * @since 23
     */
    EFFECT_NODE_TYPE_TEMPO_PITCH = 211,
    /**
     * @brief HOA input space render node type.
     * The audio format input by the HOA space render node is as follows:
     * Sample rate: {@link SAMPLE_RATE_16000}, {@link SAMPLE_RATE_48000}.
     * Sample format: {@link OH_Audio_SampleFormat}.
     * layout: 1st to 3rd order HOA, as one of the follows:
     * {@link CH_LAYOUT_AMB_ORDER1_ACN_N3D}, {@link CH_LAYOUT_AMB_ORDER1_ACN_SN3D}, {@link CH_LAYOUT_AMB_ORDER1_FUMA},
     * {@link CH_LAYOUT_AMB_ORDER2_ACN_N3D}, {@link CH_LAYOUT_AMB_ORDER2_ACN_SN3D}, {@link CH_LAYOUT_AMB_ORDER2_FUMA},
     * {@link CH_LAYOUT_AMB_ORDER3_ACN_N3D}, {@link CH_LAYOUT_AMB_ORDER3_ACN_SN3D}, {@link CH_LAYOUT_AMB_ORDER3_FUMA}.
     * The audio format output by the HOA space render node is as follows:
     * Sample rate: {@link SAMPLE_RATE_48000}.
     * Sample format: {@link AUDIO_SAMPLE_S32LE}.
     * Channels: 2.
     * This node must be connected to an input node with the audio format set to HOA.
     * If it is not connected, an error will be reported in the {@link OH_AudioSuiteEngine_StartPipeline} interface.
     *
     * @since 26.0.0
     */
    EFFECT_NODE_TYPE_HOA_SPACE_RENDER = 212,
} OH_AudioNode_Type;

/**
 * @brief Define audio node system type.
 * @systemapi
 * @since 26.0.0
 */
typedef enum OH_AudioSuite_SystemNodeType {
    /**
     * @brief Dialogue Algo System Effect Node.
     *
     * @since 26.0.0
     */
    OH_AUDIOSUITE_EFFECT_NODE_SYSTEM_TYPE_DIALOGUE_ENHANCE = 301,
    /**
     * @brief Voice Beautifier System Effect Node.
     *
     * @since 26.0.0
     */
    OH_AUDIOSUITE_EFFECT_NODE_SYSTEM_TYPE_VOICE_BEAUTIFIER = 302,
} OH_AudioSuite_SystemNodeType;

/**
 * @brief Define pipeline work mode
 *
 * @since 22
 */
typedef enum {
    /**
     * @brief The pipeline supports creating various effect nodes in suite mode.
     *
     * @since 22
     */
    AUDIOSUITE_PIPELINE_EDIT_MODE = 1,
    /**
     * @brief If you need to play audio after effect processing, you should select this mode.
     * Before API version 23, in real-time rendering mode, the pipeline only supports EQ effect processing.
     * In API version 23 and later, in real-time rendering mode, the pipeline supports all effect processing.
     *
     * @since 22
     */
    AUDIOSUITE_PIPELINE_REALTIME_MODE = 2,
} OH_AudioSuite_PipelineWorkMode;
/**
 * @brief Define pipeline state
 *
 * @since 22
 */
typedef enum {
    /**
     * @brief The pipeline is in a stopped state.
     *
     * @since 22
     */
    AUDIOSUITE_PIPELINE_STOPPED = 1,
    /**
     * @brief The pipeline is in a running state.
     *
     * @since 22
     */
    AUDIOSUITE_PIPELINE_RUNNING = 2,
} OH_AudioSuite_PipelineState;
/**
 * @brief Define the result of the function execution.
 *
 * @since 22
 */
typedef enum {
    /**
     * @error The call was successful.
     *
     * @since 22
     */
    AUDIOSUITE_SUCCESS = 0,
    /**
     * @error This means that the function was executed with an invalid input parameter.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_INVALID_PARAM = 1,
    /**
     * @error Execution status exception.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_INVALID_STATE = 2,
    /**
     * @error A system error has occurred.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_SYSTEM = 3,
    /**
     * @error Unsupported audio format, such as unsupported encoding type, sample format etc.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_UNSUPPORTED_FORMAT = 4,
    /**
     * @error audio engine does not exist.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_ENGINE_NOT_EXIST = 5,
    /**
     * @error audio pipeline does not exist.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_PIPELINE_NOT_EXIST = 6,
    /**
     * @error audio node does not exist.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_NODE_NOT_EXIST = 7,
    /**
     * @error the connect or disconnect between the nodes is unsupported.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_UNSUPPORTED_CONNECT = 8,
    /**
     * @error Unsupported operation.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_UNSUPPORTED_OPERATION = 9,
    /**
     * @error The application attempted to create an object that exceeds the system's maximum limit.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_CREATED_EXCEED_SYSTEM_LIMITS = 10,
    /**
     * @error Required parameters are missing.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_REQUIRED_PARAMETERS_MISSING = 11,
    /**
     * @error Operation timed out.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_TIMEOUT = 12,
    /**
     * @error Memory allocation failed.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_MEMORY_ALLOC_FAILED = 13,
} OH_AudioSuite_Result;
/**
 * @brief Define the audio sample format.
 *
 * @since 22
 */
typedef enum {
    /**
     * @brief Unsigned 8 format.
     *
     * @since 22
     */
    AUDIO_SAMPLE_U8 = 0,
    /**
     * @brief Signed 16 bit integer, little endian.
     *
     * @since 22
     */
    AUDIO_SAMPLE_S16LE = 1,
    /**
     * @brief Signed 24 bit integer, little endian.
     *
     * @since 22
     */
    AUDIO_SAMPLE_S24LE = 2,
    /**
     * @brief Signed 32 bit integer, little endian.
     *
     * @since 22
     */
    AUDIO_SAMPLE_S32LE = 3,
    /**
     * @brief 32 bit IEEE floating point, little endian.
     *
     * @since 22
     */
    AUDIO_SAMPLE_F32LE = 4,
} OH_Audio_SampleFormat;
/**
 * @brief Define the audio encoding type.
 *
 * @since 22
 */
typedef enum {
    /**
     * @brief PCM encoding type.
     *
     * @since 22
     */
    AUDIO_ENCODING_TYPE_RAW = 0,
} OH_Audio_EncodingType;

/**
 * @brief Define the audio sample rate.
 *
 * @since 22
 */
typedef enum {
    /**
     * @brief 8kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_8000 = 8000,
    /**
     * @brief 11.025kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_11025 = 11025,
    /**
     * @brief 12kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_12000 = 12000,
    /**
     * @brief 16kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_16000 = 16000,
    /**
     * @brief 22.05kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_22050 = 22050,
    /**
     * @brief 24kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_24000 = 24000,
    /**
     * @brief 32kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_32000 = 32000,
    /**
     * @brief 44.1kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_44100 = 44100,
    /**
     * @brief 48kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_48000 = 48000,
    /**
     * @brief 64kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_64000 = 64000,
    /**
     * @brief 88.2kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_88200 = 88200,
    /**
     * @brief 96kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_96000 = 96000,
    /**
     * @brief 176.4kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_176400 = 176400,
    /**
     * @brief 192kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_192000 = 192000
} OH_Audio_SampleRate;

/**
 * @brief Define the audio format info structure, used to describe basic audio format.
 *
 * @since 22
 */
typedef struct OH_AudioFormat {
    /**
     * @brief Audio sampling rate.
     *
     * @since 22
     */
    OH_Audio_SampleRate samplingRate;
    /**
     * @brief Audio channel layout.
     *
     * @since 22
     */
    OH_AudioChannelLayout channelLayout;
    /**
     * @brief Audio channel count.
     *
     * @since 22
     */
    uint32_t channelCount;
    /**
     * @brief Audio encoding format type.
     *
     * @since 22
     */
    OH_Audio_EncodingType encodingType;
    /**
     * @brief Audio sample format.
     *
     * @since 22
     */
    OH_Audio_SampleFormat sampleFormat;
} OH_AudioFormat;

/**
 * @brief Define the audio format info structure, used to describe basic audio format for system node.
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_AudioSuite_SystemNodeFormat {
    /**
     * @brief Audio sampling rate.
     *
     * @since 26.0.0
     */
    OH_Audio_SampleRate samplingRate;
    /**
     * @brief Audio channel layout.
     *
     * @since 26.0.0
     */
    OH_AudioChannelLayout channelLayout;
    /**
     * @brief Audio channel count.
     *
     * @since 26.0.0
     */
    uint32_t channelCount;
    /**
     * @brief Audio encoding format.
     *
     * @since 26.0.0
     */
    int32_t encoding;
    /**
     * @brief Audio sample format.
     *
     * @since 26.0.0
     */
    OH_Audio_SampleFormat sampleFormat;
} OH_AudioSuite_SystemNodeFormat;

/**
 * @brief Define the audio data array structure.
 * This structure is used to get the processed audio data after acquisition processing during multi-channel rendering.
 * @since 22
 */
typedef struct OH_AudioDataArray {
    /**
     * @brief Pointer to the array of audio data pointers.
     *
     * @since 22
     */
    void **audioDataArray;
    /**
     * @brief Audio arraySize.
     *
     * @since 22
     */
    int32_t arraySize;
    /**
     * @brief The memory size pointed to by each address in the audioDataArray array, in bytes.
     * It should be ensured that the memory size pointed to by each address is requestFrameSize bytes.
     *
     * @since 22
     */
    int32_t requestFrameSize;
} OH_AudioDataArray;

/**
 * @brief Define the audio meta data frame structure.
 * This structure is used to pass audio data and meta data together.
 * @systemapi
 * @since 26.0.0
 */
typedef struct OH_AudioSuite_MetaFrame {
    /**
     * @brief Audio data pointer.
     *
     * @since 26.0.0
     */
    void* audioData;
    /**
     * @brief Audio data size.
     *
     * @since 26.0.0
     */
    int32_t audioDataSize;
    /**
     * @brief Meta data pointer.
     *
     * @since 26.0.0
     */
    void* metaData;
    /**
     * @brief Meta data size.
     *
     * @since 26.0.0
     */
    int32_t metaDataSize;
} OH_AudioSuite_MetaFrame;

/**
 * @brief Define the sound field type.
 *
 * @since 22
 */
typedef enum {
    /**
     * @brief Front facing sound field type.
     *
     * @since 22
     */
    SOUND_FIELD_FRONT_FACING = 1,
    /**
     * @brief Grand sound field type.
     *
     * @since 22
     */
    SOUND_FIELD_GRAND = 2,
    /**
     * @brief Near sound field type.
     *
     * @since 22
     */
    SOUND_FIELD_NEAR = 3,
    /**
     * @brief Wide sound field type.
     *
     * @since 22
     */
    SOUND_FIELD_WIDE = 4,
} OH_SoundFieldType;
/**
 * @brief Define the environment type.
 *
 * @since 22
 */
typedef enum {
    /**
     * @brief Broadcast environment effect type.
     *
     * @since 22
     */
    ENVIRONMENT_TYPE_BROADCAST = 1,
    /**
     * @brief Earpiece environment effect type.
     *
     * @since 22
     */
    ENVIRONMENT_TYPE_EARPIECE = 2,
    /**
     * @brief UnderWater environment effect type.
     *
     * @since 22
     */
    ENVIRONMENT_TYPE_UNDERWATER = 3,
    /**
     * @brief Gramophone environment effect type.
     *
     * @since 22
     */
    ENVIRONMENT_TYPE_GRAMOPHONE = 4
} OH_EnvironmentType;
/**
 * @brief Define voice beautifier type.
 *
 * @since 22
 */
typedef enum {
    /**
     * @brief Clear voice beautifier type.
     *
     * @since 22
     */
    VOICE_BEAUTIFIER_TYPE_CLEAR = 1,
    /**
     * @brief Theatre voice beautifier type.
     *
     * @since 22
     */
    VOICE_BEAUTIFIER_TYPE_THEATRE = 2,
    /**
     * @brief CD voice beautifier type.
     *
     * @since 22
     */
    VOICE_BEAUTIFIER_TYPE_CD = 3,
    /**
     * @brief Recording studio voice beautifier type.
     *
     * @since 22
     */
    VOICE_BEAUTIFIER_TYPE_RECORDING_STUDIO = 4
} OH_VoiceBeautifierType;
/**
 * @brief Define the number of equalizer frequency bands
 *
 * @since 22
 */
#define EQUALIZER_BAND_NUM (10)

/**
 * @brief Specify equalizer frequency band gains.
 *
 * @since 22
 */
typedef struct OH_EqualizerFrequencyBandGains {
    /**
     * @brief The equalizer supports gain adjustment for 10 specific frequencies.
     * Frequencies: 31 Hz, 62 Hz, 125 Hz, 250 Hz, 500 Hz, 1 kHz, 2 kHz, 4 kHz, 8 kHz, 16 kHz.
     *
     * @since 22
     */
    int32_t gains[EQUALIZER_BAND_NUM];
} OH_EqualizerFrequencyBandGains;

/**
 * @brief Default equalization effect band gains.
 * Gains is {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_DEFAULT;
/**
 * @brief Ballad equalization effect band gains.
 * Gains is {3, 5, 2, -4, 1, 2, -3, 1, 4, 5}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_BALLADS;

/**
 * @brief Chinese style equalization effect band gains.
 * Gains is {0, 0, 2, 0, 0, 4, 4, 2, 2, 5}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_CHINESE_STYLE;

/**
 * @brief Classic equalization effect band gains.
 * Gains is {2, 3, 2, 1, 0, 0, -5, -5, -5, -6}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_CLASSICAL;

/**
 * @brief Dance music equalization effect band gains.
 * Gains is {4, 3, 2, -3, 0, 0, 5, 4, 2, 0}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_DANCE_MUSIC;

/**
 * @brief Jazz equalization effect band gains.
 * Gains is {2, 0, 2, 3, 6, 5, -1, 3, 4, 4}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_JAZZ;

/**
 * @brief Pop equalization effect band gains.
 * Gains is {5, 2, 1, -1, -5, -5, -2, 1, 2, 4}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_POP;

/**
 * @brief R&B equalization effect band gains.
 * Gains is {1, 4, 5, 3, -2, -2, 2, 3, 5, 5}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_RB;

/**
 * @brief Rock equalization effect band gains.
 * Gains is {6, 4, 4, 2, 0, 1, 3, 3, 5, 4}.
 *
 * @since 22
 */
extern const OH_EqualizerFrequencyBandGains OH_EQUALIZER_PARAM_ROCK;

/**
 * @brief Declare the audio engine.
 * The handle of audio suite engine is used for audio suite engine related functions.
 *
 * @since 22
 */
typedef struct OH_AudioSuiteEngineStruct OH_AudioSuiteEngine;

/**
 * @brief Declare the audio pipeline.
 * The handle of audio suite pipeline is used for audio pipeline related functions.
 *
 * @since 22
 */
typedef struct OH_AudioSuitePipelineStruct OH_AudioSuitePipeline;

/**
 * @brief Declare the audio node.
 * The handle of audio suite node is used for audio suite node related functions.
 *
 * @since 22
 */
typedef struct OH_AudioNodeStruct OH_AudioNode;

/**
 * @brief Declare the audio node builder.
 * The handle of audio node builder is used for audio node create.
 *
 * @since 22
 */
typedef struct OH_AudioNodeBuilderStruct OH_AudioNodeBuilder;

/**
 * @brief Definition of the parameter structure for fixed position mode in 3D spatial rendering.
 * Left-hand coordinate system: Extend your left hand, forming an "L" shape with your thumb and index finger.
 * Point the thumb to the right, the index finger upward, and the remaining fingers forward.
 * This establishes a left-hand coordinate system. In this system, the thumb, index finger,
 * and other fingers represent the positive directions of the x, y, and z axes, respectively.
 * @since 23
 */
typedef struct OH_AudioSuite_SpaceRenderPositionParams {
    /**
     * @brief X coordinate in space, value range: [-5.0, 5.0], unit: meters.
     * If the value is out of range, the setting will fail and return {@link AUDIOSUITE_ERROR_INVALID_PARAM}.
     *
     * @since 23
     */
    float x;
    /**
     * @brief Y coordinate in space, value range: [-5.0, 5.0], unit: meters.
     * If the value is out of range, the setting will fail and return {@link AUDIOSUITE_ERROR_INVALID_PARAM}.
     *
     * @since 23
     */
    float y;
    /**
     * @brief Z coordinate in space, value range: [-5.0, 5.0], unit: meters.
     * If the value is out of range, the setting will fail and return {@link AUDIOSUITE_ERROR_INVALID_PARAM}.
     *
     * @since 23
     */
    float z;
} OH_AudioSuite_SpaceRenderPositionParams;

/**
 * @brief Space rendering surround Direction
 *
 * @since 23
 */
typedef enum {
    /**
     * @brief Rotate counterclockwise
     *
     * @since 23
     */
    SPACE_RENDER_CCW = 0,
    /**
     * @brief Rotate clockwise
     *
     * @since 23
     */
    SPACE_RENDER_CW = 1,
} OH_AudioSuite_SurroundDirection;

/**
 * @brief Space rendering dynamic mode parameters.
 *
 * @since 23
 */
typedef struct OH_AudioSuite_SpaceRenderRotationParams {
    /**
     * @brief X coordinate in space, value range: [-5.0, 5.0], unit: meters.
     * If the value is out of range, the setting will fail and return {@link AUDIOSUITE_ERROR_INVALID_PARAM}.
     *
     * @since 23
     */
    float x;
    /**
     * @brief Y coordinate in space, value range: [-5.0, 5.0], unit: meters.
     * If the value is out of range, the setting will fail and return {@link AUDIOSUITE_ERROR_INVALID_PARAM}.
     *
     * @since 23
     */
    float y;
    /**
     * @brief Z coordinate in space, value range: [-5.0, 5.0], unit: meters.
     * If the value is out of range, the setting will fail and return {@link AUDIOSUITE_ERROR_INVALID_PARAM}.
     *
     * @since 23
     */
    float z;
    /**
     * @brief Single-week circumnavigation time, value range: [2, 40], unit: seconds.
     * If the value is out of range, the setting will fail and return {@link AUDIOSUITE_ERROR_INVALID_PARAM}.
     *
     * @since 23
     */
    int32_t surroundTime;
    /**
     * @brief Single-week circumnavigation direction.
     *
     * @since 23
     */
    OH_AudioSuite_SurroundDirection surroundDirection;
} OH_AudioSuite_SpaceRenderRotationParams;

 /**
  * @brief Space rendering extension mode parameters.
  *
  * @since 23
  */
typedef struct OH_AudioSuite_SpaceRenderExtensionParams {
    /**
     * @brief Expansion radius, value range: [1.0, 5.0], unit: meters.
     * If the value is out of range, the setting will fail and return {@link AUDIOSUITE_ERROR_INVALID_PARAM}.
     *
     * @since 23
     */
    float extRadius;
    /**
     * @brief Expansion angle, value range: (0, 360), unit: degrees.
     * If the value is out of range, the setting will fail and return {@link AUDIOSUITE_ERROR_INVALID_PARAM}.
     *
     * @since 23
     */
    int32_t extAngle;
} OH_AudioSuite_SpaceRenderExtensionParams;

/**
 * @brief Define speaker gender in change voice option
 *
 * @since 23
 */
typedef enum {
    /**
     * @brief Set female voice.
     *
     * @since 23
     */
    PURE_VOICE_CHANGE_FEMALE = 1,
    /**
     * @brief Set male voice.
     *
     * @since 23
     */
    PURE_VOICE_CHANGE_MALE = 2,
} OH_AudioSuite_PureVoiceChangeGenderOption;

/**
 * @brief Define voice type in change voice option
 *
 * @since 23
 */
typedef enum {
    /**
     * @brief Cartoon voice type.
     *
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_CARTOON = 1,
    /**
     * @brief Cute voice type.
     *
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_CUTE = 2,
    /**
     * @brief Female voice type.
     *
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_FEMALE = 3,
    /**
     * @brief Male voice type.
     *
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_MALE = 4,
    /**
     * @brief Monster voice type.
     *
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_MONSTER = 5,
    /**
     * @brief Robots voice type.
     *
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_ROBOTS = 6,
    /**
     * @brief Seasoned voice type.
     *
     * @since 23
     */
    PURE_VOICE_CHANGE_TYPE_SEASONED = 7,
} OH_AudioSuite_PureVoiceChangeType;

/**
 * @brief Use system recommended pitch.
 * Use in {@link OH_AudioSuite_PureVoiceChangeOption}.
 *
 * @since 23
 */
#define OH_PURE_VOICE_DEFAULT_PITCH (0.0f)

/**
 * @brief Define change voice option.
 *
 * @since 23
 */
typedef struct OH_AudioSuite_PureVoiceChangeOption {
    /**
     * @brief Define speaker gender.
     *
     * @since 23
     */
    OH_AudioSuite_PureVoiceChangeGenderOption optionGender;
    /**
     * @brief Define voice type.
     *
     * @since 23
     */
    OH_AudioSuite_PureVoiceChangeType optionType;
    /**
     * @brief Define voice pitch.
     * If using default pitch in system for best effect, set to {@link OH_PURE_VOICE_DEFAULT_PITCH}.
     * For custom pitch setting, specify a value with the valid range: [0.3f, 3.0f].
     * If the value is out of range, the setting will fail and return {@link AUDIOSUITE_ERROR_INVALID_PARAM}.
     *
     * @since 23
     */
    float pitch;
} OH_AudioSuite_PureVoiceChangeOption;

/**
 * @brief Define voice type in general voice change.
 *
 * @since 23
 */
typedef enum {
    /**
     * @brief Cute voice type.
     *
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_CUTE = 1,
    /**
     * @brief Cyberpunk voice type.
     *
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_CYBERPUNK = 2,
    /**
     * @brief Female voice type.
     *
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_FEMALE = 3,
    /**
     * @brief Male voice type.
     *
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_MALE = 4,
    /**
     * @brief Mix voice type.
     *
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_MIX = 5,
    /**
     * @brief Monster voice type.
     *
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_MONSTER = 6,
    /**
     * @brief Seasoned voice type.
     *
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_SEASONED = 7,
    /**
     * @brief Synth voice type.
     *
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_SYNTH = 8,
    /**
     * @brief Trill voice type.
     *
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_TRILL = 9,
    /**
     * @brief War voice type.
     *
     * @since 23
     */
    GENERAL_VOICE_CHANGE_TYPE_WAR = 10,
} OH_AudioSuite_GeneralVoiceChangeType;

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_AUDIO_SUITE_BASE_H