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
     * default input node type, this input node type support get audio data from application.
     *
     * @since 22
     */
    INPUT_NODE_TYPE_DEFAULT = 1,
    /**
     * default output node type, this output node type support provide audio data to application .
     *
     * @since 22
     */
    OUT_NODE_TYPE_DEFAULT = 101,
    /**
     * Equalization node type.
     * The audio format output by the equalizer node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 2.
     *
     * @since 22
     */
    EFFECT_NODE_TYPE_EQUALIZER = 201,
    /**
     * Noise reduction node type.
     * The audio format output by the noise reduction node is as follows:
     * Sample rate: 16000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 1.
     *
     * @since 22
     */
    EFFECT_NODE_TYPE_NOISE_REDUCTION = 202,
    /**
     * Sound field node type. Support sound field type {@link OH_SoundFieldType}.
     * The audio format output by the sound field node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 2.
     *
     * @since 22
     */
    EFFECT_NODE_TYPE_SOUND_FIELD = 203,
    /**
     * Audio Separation node type, it can only connect to output node.
     * The audio format output by the scene effect node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_F32LE}.
     * Channels: 4(First 2 channels for vocals; last 2 channels for accompaniment).
     *
     * @since 22
     */
    EFFECT_MULTII_OUTPUT_NODE_TYPE_AUDIO_SEPARATION = 204,
    /**
     * Voice beautifier node type. Support beautifier type{@link OH_VoiceBeautifierType}.
     * The audio format output by the voice beautifier node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 2.
     *
     * @since 22
     */
    EFFECT_NODE_TYPE_VOICE_BEAUTIFIER = 205,
    /**
     * Scene effect node type.
     * The audio format output by the scene effect node is as follows:
     * Sample rate: 48000 Hz.
     * Sample format: {@link AUDIO_SAMPLE_S16LE}.
     * Channels: 2.
     *
     * @since 22
     */
    EFFECT_NODE_TYPE_ENVIRONMENT_EFFECT = 206,
    /**
     * Audio mixer node type.
     * The audio format output by the scene effect node is as follows:
     * Sample rate: The highest sampling rate in the input sampling rate.
     * Sample format: {@link AUDIO_SAMPLE_F32LE}.
     * Channels: 2.
     *
     * @since 22
     */
    EFFECT_NODE_TYPE_AUDIO_MIXER = 207,
} OH_AudioNode_Type;
/**
 * @brief Define pipeline work mode
 *
 * @since 22
 */
typedef enum {
    /**
     * The pipeline supports creating various effect nodes in suite mode.
     *
     * @since 22
     */
    AUDIOSUITE_PIPELINE_EDIT_MODE = 1,
    /**
     * If you need to play audio after effect processing, you should select this mode.
     * In real-time rendering mode, the pipeline only supports EQ effect processing.
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
     * The pipeline is in a stopped state.
     *
     * @since 22
     */
    AUDIOSUITE_PIPELINE_STOPPED = 1,
    /**
     * The pipeline is in a running state.
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
     * @error An system error has occurred.
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
     * @error audio engine not exist.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_ENGINE_NOT_EXIST = 5,
    /**
     * @error audio pipeline not exist.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_PIPELINE_NOT_EXIST = 6,
    /**
     * @error audio pipeline not exist.
     *
     * @since 22
     */
    AUDIOSUITE_ERROR_NODE_NOT_EXIST = 7,
    /**
     * @error the connect or disconnect betwen the nodes is unsupported.
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
} OH_AudioSuite_Result;

/**
 * @brief Define the audio sample format.
 *
 * @since 22
 */
typedef enum {
    /**
     * Unsigned 8 format.
     *
     * @since 22
     */
    AUDIO_SAMPLE_U8 = 0,
    /**
     * Signed 16 bit integer, little endian.
     *
     * @since 22
     */
    AUDIO_SAMPLE_S16LE = 1,
    /**
     * Signed 24 bit integer, little endian.
     *
     * @since 22
     */
    AUDIO_SAMPLE_S24LE = 2,
    /**
     * Signed 32 bit integer, little endian.
     *
     * @since 22
     */
    AUDIO_SAMPLE_S32LE = 3,
    /**
     * 32 bit IEEE floating point, little endian.
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
     * PCM encoding type.
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
     * 8kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_8000 = 8000,
    /**
     * 11.025kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_11025 = 11025,
    /**
     * 12kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_12000 = 12000,
    /**
     * 16kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_16000 = 16000,
    /**
     * 22.05kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_22050 = 22050,
    /**
     * 24kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_24000 = 24000,
    /**
     * 32kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_32000 = 32000,
    /**
     * 44.1kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_44100 = 44100,
    /**
     * 48kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_48000 = 48000,
    /**
     * 64kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_64000 = 64000,
    /**
     * 88.2kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_88200 = 88200,
    /**
     * 96kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_96000 = 96000,
    /**
     * 176.4kHz sample rate.
     * @since 22
     */
    SAMPLE_RATE_176400 = 176400,
    /**
     * 192kHz sample rate.
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
 * @brief Define the audio data array structure,
 * This structure is used to get the processed audio data after acquisition processing during multi-channel rendering.
 * @since 22
 */
typedef struct OH_AudioDataArray {
    /**
     * @brief Audio audioDataArray mail.
     *
     * @since 22
     */
    void **audioDataArray;
    /**
     * @brief Audio arraySize.
     *
     * @since 22
     */
    int arraySize;
    /**
     * @brief Audio requestFrameSize count.
     *
     * @since 22
     */
    int32_t requestFrameSize;
} OH_AudioDataArray;

/**
 * @brief Define the sound field type.
 *
 * @since 22
 */
typedef enum {
    /**
     * Front facing sound field type.
     *
     * @since 22
     */
    SOUND_FIELD_FRONT_FACING = 1,
    /**
     * Grand sound field type.
     *
     * @since 22
     */
    SOUND_FIELD_GRAND = 2,
    /**
     * Near sound field type.
     *
     * @since 22
     */
    SOUND_FIELD_NEAR = 3,
    /**
     * Near sound field type.
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
     * Broadcast environment effect type.
     *
     * @since 22
     */
    ENVIRONMENT_TYPE_BROADCAST = 1,
    /**
     * Earpiece environment effect type.
     *
     * @since 22
     */
    ENVIRONMENT_TYPE_EARPIECE = 2,
    /**
     * UnderWater environment effect type.
     *
     * @since 22
     */
    ENVIRONMENT_TYPE_UNDERWATER = 3,
    /**
     * Gramophone environment effect type.
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
     * Clear voice beautifier type.
     *
     * @since 22
     */
    VOICE_BEAUTIFIER_TYPE_CLEAR = 1,
    /**
     * Theatre voice beautifier type.
     *
     * @since 22
     */
    VOICE_BEAUTIFIER_TYPE_THEATRE = 2,
    /**
     * CD voice beautifier type.
     *
     * @since 22
     */
    VOICE_BEAUTIFIER_TYPE_CD = 3,
    /**
     * Recording studio voice beautifier type.
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
 * @brief Declare the audio engine.
 * The handle of audio suite engine is used for audio suite engine related functions.
 *
 * @since 22
 */
typedef struct OH_AudioSuiteEngineStruct OH_AudioSuiteEngine;

/**
 * @brief Declare the audio pipe line.
 * The handle of audio suite pipe line is used for audio pipe line related functions.
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

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_AUDIO_SUITE_BASE_H