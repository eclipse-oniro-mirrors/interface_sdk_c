/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @since 26.0.0
 * @version 1.0
 */
/**
 * @file native_audio_converter.h
 *
 * @brief Declare underlying data structure.
 *
 * @library libohaudiosuite.so
 * @syscap SystemCapability.Multimedia.Audio.SuiteEngine
 * @kit AudioKit
 * @since 26.0.0
 * @version 1.0
 */
#ifndef NATIVE_AUDIO_CONVERTER_H
#define NATIVE_AUDIO_CONVERTER_H
#include <stdint.h>
#include "multimedia/native_audio_channel_layout.h"
#include "native_audio_suite_base.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Define the audio converter format info structure, used to describe basic audio format.
 *
 * @since 26.0.0
 */
typedef struct OH_AudioConverter_Format {
    /**
     * @brief Audio encoding format type.
     *
     * @since 26.0.0
     */
    OH_Audio_EncodingType encodingType;
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
     * @brief Audio sample format.
     *
     * @since 26.0.0
     */
    OH_Audio_SampleFormat sampleFormat;
} OH_AudioConverter_Format;

/**
 * @brief Defines the format information of the extended audio converter, which is used to describe the audio format
 * that supports any sampling rate.
 *
 * @since 26.1.0
 */
typedef struct OH_AudioSuite_ConverterFormatEx {
    /**
     * @brief Audio encoding format type.
     *
     * @since 26.1.0
     */
    OH_Audio_EncodingType encodingType;
    /**
     * @brief Audio sampling rate, in Hz.
     * The sampling rate is an integer multiple of 10 Hz in the range [8000, 5644800] and 11025 Hz.
     *
     * @since 26.1.0
     */
    int32_t samplingRate;
    /**
     * @brief Audio channel layout.
     * The supported value range is {@link OH_AudioChannelLayout}.CH_LAYOUT_MONO,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_STEREO, {@link OH_AudioChannelLayout}.CH_LAYOUT_STEREO_DOWNMIX,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_2POINT1, {@link OH_AudioChannelLayout}.CH_LAYOUT_3POINT0,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_SURROUND, {@link OH_AudioChannelLayout}.CH_LAYOUT_3POINT1,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_4POINT0, {@link OH_AudioChannelLayout}.CH_LAYOUT_QUAD_SIDE,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_QUAD, {@link OH_AudioChannelLayout}.CH_LAYOUT_2POINT0POINT2,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_4POINT1, {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT0,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT0_BACK, {@link OH_AudioChannelLayout}.CH_LAYOUT_2POINT1POINT2,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_3POINT0POINT2, {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1_BACK, {@link OH_AudioChannelLayout}.CH_LAYOUT_6POINT0,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_3POINT1POINT2, {@link OH_AudioChannelLayout}.CH_LAYOUT_6POINT0_FRONT,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_HEXAGONAL, {@link OH_AudioChannelLayout}.CH_LAYOUT_6POINT1,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_6POINT1_BACK, {@link OH_AudioChannelLayout}.CH_LAYOUT_6POINT1_FRONT,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT0, {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT0_FRONT,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1, {@link OH_AudioChannelLayout}.CH_LAYOUT_OCTAGONAL,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1POINT2, {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1_WIDE,
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1_WIDE_BACK.
     *
     * @since 26.1.0
     */
    OH_AudioChannelLayout channelLayout;
    /**
     * @brief Audio sampling format.
     *
     * @since 26.1.0
     */
    OH_Audio_SampleFormat sampleFormat;
} OH_AudioSuite_ConverterFormatEx;

/**
 * @brief Defines the input data structure of the audio converter.
 *
 * @since 26.1.0
 */
typedef struct OH_AudioSuite_ConverterInputInfo {
    /**
     * @brief Pointer to the input audio data buffer, which points to the original audio data and is allocated by the
     * caller.
     * The specific data type is determined by the sampling format {@link OH_Audio_SampleFormat}.
     * Must remain valid during a call to {@link OH_AudioSuite_ConverterDirectProcess}. The value cannot be NULL.
     *
     * @since 26.1.0
     */
    const void *data;
    /**
     * @brief Indicates the size of the input buffer, in bytes. Must be greater than 0.
     *
     * @since 26.1.0
     */
    uint32_t size;
} OH_AudioSuite_ConverterInputInfo;

/**
 * @brief Defines the output data structure of the audio converter, which is used to receive the converted audio data in
 * direct processing mode.
 *
 * @since 26.1.0
 */
typedef struct OH_AudioSuite_ConverterOutputInfo {
    /**
     * @brief Pointer to the buffer of the output audio data, which is allocated by the caller.
     * Conversion results will be written to this buffer.
     * The specific data type is determined by the sampling format {@link OH_Audio_SampleFormat}.
     * Must remain valid during a call to {@link OH_AudioSuite_ConverterDirectProcess}. The value cannot be NULL.
     *
     * @since 26.1.0
     */
    void *data;
    /**
     * @brief Size of the output buffer, in bytes. The value must be greater than 0.
     *
     * @since 26.1.0
     */
    uint32_t size;
    /**
     * @brief Output parameter, which returns the number of bytes actually written to the output buffer.
     * No initialization is required before invoking. No content is written when the call fails.
     *
     * @since 26.1.0
     */
    uint32_t writeSize;
} OH_AudioSuite_ConverterOutputInfo;

/**
 * @brief Declare the audio converter.
 * The handle of audio converter is used for audio converter related functions.
 *
 * @since 26.0.0
 */
typedef struct OH_AudioConverterStruct OH_AudioConverter;

/**
 * @brief Define the result of the function execution.
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * @error The call was successful.
     *
     * @since 26.0.0
     */
    AUDIOCONVERTER_SUCCESS = 0,
    /**
     * @error This means that the function was executed with an invalid input parameter.
     *
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_INVALID_PARAM = 1,
    /**
     * @error Unsupported audio format, such as unsupported encoding type, sample format etc.
     *
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_UNSUPPORTED_FORMAT = 2,
    /**
     * @error A system error has occurred.
     *
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_SYSTEM = 3,
    /**
     * @error Memory allocation failed.
     *
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_MEMORY_ALLOC_FAILED = 4,
    /**
     * @error Buffer capacity is insufficient.
     *
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_BUFFER_TOO_SMALL = 5,
    /**
     * @error Audio converter instance is not initialized.
     *
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_NOT_INITIALIZED = 6,
    /**
     * @error Callback is invalid.
     *
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_CALLBACK_INVALID = 7,
    /**
     * @error Callback is not set.
     *
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_CALLBACK_NOT_SET = 8,
    /**
     * @brief Permission verification failed. A non-system application invokes the system API.
     * @since 26.1.0
     */
    AUDIOCONVERTER_ERROR_NOT_SYSTEM_APP = 202,
    /**
     * @brief The operation is not supported.
     * @since 26.1.0
     */
    AUDIOCONVERTER_ERROR_UNSUPPORTED_OPERATION = 6800104,
} OH_AudioConverter_Result;

/**
 * @brief Request to create the audio converter.
 *
 * The converter instance created by this function must be explicitly destroyed via {@link OH_AudioConverter_Destroy}.
 * Supported audio format specifications (valid for Input/Output)
 * The converter only supports PCM (Pulse Code Modulation) audio formats.
 * Sample rate supports 8000 Hz, 11025 Hz, 12000 Hz, 16000 Hz, 22050 Hz, 24000 Hz, 32000 Hz, 44100 Hz, 48000 Hz,
 * 64000 Hz, 88200 Hz, 96000 Hz, 176400 Hz and 192000 Hz.
 * Channel layout supports {@link CH_LAYOUT_MONO}, {@link CH_LAYOUT_STEREO}, {@link CH_LAYOUT_STEREO_DOWNMIX},
 * {@link CH_LAYOUT_2POINT1}, {@link CH_LAYOUT_3POINT0}, {@link CH_LAYOUT_SURROUND}, {@link CH_LAYOUT_3POINT1},
 * {@link CH_LAYOUT_4POINT0}, {@link CH_LAYOUT_QUAD_SIDE}, {@link CH_LAYOUT_QUAD}, {@link CH_LAYOUT_2POINT0POINT2},
 * {@link CH_LAYOUT_4POINT1}, {@link CH_LAYOUT_5POINT0}, {@link CH_LAYOUT_5POINT0_BACK},
 * {@link CH_LAYOUT_2POINT1POINT2}, {@link CH_LAYOUT_3POINT0POINT2}, {@link CH_LAYOUT_5POINT1},
 * {@link CH_LAYOUT_5POINT1_BACK}, {@link CH_LAYOUT_6POINT0}, {@link CH_LAYOUT_3POINT1POINT2},
 * {@link CH_LAYOUT_6POINT0_FRONT}, {@link CH_LAYOUT_HEXAGONAL}, {@link CH_LAYOUT_6POINT1},
 * {@link CH_LAYOUT_6POINT1_BACK}, {@link CH_LAYOUT_6POINT1_FRONT}, {@link CH_LAYOUT_7POINT0},
 * {@link CH_LAYOUT_7POINT0_FRONT}, {@link CH_LAYOUT_7POINT1}, {@link CH_LAYOUT_OCTAGONAL},
 * {@link CH_LAYOUT_5POINT1POINT2}, {@link CH_LAYOUT_7POINT1_WIDE} and {@link CH_LAYOUT_7POINT1_WIDE_BACK}.
 * Sample format (bit depth) supports SAMPLE_U8 (8-bit unsigned PCM),
 * SAMPLE_S16LE (16-bit short little-endian PCM), SAMPLE_S24LE (24-bit short little-endian PCM),
 * SAMPLE_S32LE (32-bit short little-endian PCM), and SAMPLE_F32LE (32-bit float little-endian PCM).
 *
 * @param inputFormat Pointer to the input audio format configuration.
 * @param outputFormat Pointer to the output audio format configuration.
 * @param converter Pointer to a variable that receives the created audio converter instance.
 * @return <ul>
 *         <li>{@link #AUDIOCONVERTER_SUCCESS} if execution succeeds.</li>
 *         <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM} if the input parameters are invalid</li>
 *         <li>{@link #AUDIOCONVERTER_ERROR_UNSUPPORTED_FORMAT}
 *             if the specified input/output format combination is unsupported</li>
 *         <li>{@link #AUDIOCONVERTER_ERROR_MEMORY_ALLOC_FAILED} if memory allocation failed</li>
 *         <li>{@link #AUDIOCONVERTER_ERROR_SYSTEM} if the system has other abnormalities</li>
 *         </ul>
 * @release OH_AudioConverter_Destroy {converter}
 * @since 26.0.0
 */
OH_AudioConverter_Result OH_AudioConverter_Create(
    const OH_AudioConverter_Format* inputFormat,
    const OH_AudioConverter_Format* outputFormat,
    OH_AudioConverter** converter);

/**
 * @brief Request to release the converter.
 *
 * @param converter Reference created by OH_AudioConverter_Create.
 * @since 26.0.0
 */
void OH_AudioConverter_Destroy(OH_AudioConverter* converter);


/**
 * @brief Define the status of input audio data provided by the callback {@link OH_AudioConverter_RequestDataCallback}.
 * The converter uses this status to determine how to handle subsequent conversion logic (e.g., continue pulling data,
 * pause, or flush cached data).
 * Note for callers: Even if the callback returns {@link AUDIOCONVERTER_INPUT_DATA_FINISHED},
 * {@link OH_AudioConverter_Process} must be called repeatedly
 * until it returns {@link AUDIOCONVERTER_SUCCESS} with outputSize
 * being 0 (indicating all cached data has been flushed).
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief Valid input data is available and provided.
     *
     * @since 26.0.0
     */
    AUDIOCONVERTER_INPUT_HAVE_DATA = 1,
    /**
     * @brief No input data is available temporarily.
     *
     * @since 26.0.0
     */
    AUDIOCONVERTER_INPUT_NO_AVAILABLE_DATA = 2,
    /**
     * @brief The input data stream is complete.
     *
     * @since 26.0.0
     */
    AUDIOCONVERTER_INPUT_DATA_FINISHED = 3,
} OH_AudioConverter_InputStatus;

/**
 * @brief Callback function of request data.
 *
 * The converter invokes this callback to actively request input audio data during {@link OH_AudioConverter_Process}.
 * The caller must populate the output parameters (outInputData, outStatus) and return the valid size of input data.
 * The maximum data size returned by a single callback is 400KB.
 * The memory pointed to by outInputData must remain valid until {@link OH_AudioConverter_Process} returns.
 * @param userData User-defined data passed to the callback.
 * @param outInputData Pointer to a pointer that the callback sets to point to the input audio data buffer.
 * @param outStatus Set by the callback to inform the converter about the current state of input data availability.
 * @return Size of valid input data pointed to by outInputData.
 * @since 26.0.0
 */
typedef int32_t (*OH_AudioConverter_RequestDataCallback)(
    void* userData,
    const void** outInputData,
    OH_AudioConverter_InputStatus* outStatus
);

/**
 * @brief Set converter request data callback.
 *
 * This function binds the input data callback function for the audio converter.
 * The callback is used by {@link OH_AudioConverter_Process} to pull input audio data dynamically.
 *
 * @param converter Reference created by OH_AudioConverter_Create.
 * @param callback Callback function that will be invoked during {@link OH_AudioConverter_Process}
 * to actively request input audio data.
 * @param userData Pointer to an application data structure that will be passed to the callback functions.
 * @return<ul>
 * <li>{@link #AUDIOCONVERTER_SUCCESS} Succeeded in setting the input callback function, and subsequent processes can be
 * properly executed. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM} The input parameter of the function is invalid,
 * Check whether the input audio format converter pointer is a non-null pointer. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_NOT_INITIALIZATION}The audio format converter is not initialized,
 * Check whether the current audio format converter is valid. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_CALLBACK_INVALID} The callback function is invalid,
 * Check whether the amount of data returned by the input callback function is within the allowed range. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_CALLBACK_NOT_SET}The callback function is not set. Check whether the callback
 * function pointer is empty. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_SYSTEM} System error. Check whether the format conversion is performed using the
 * destroyed audio format converter. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_UNSUPPORTED_OPERATION} The current processing process does not support callback
 * setting. [since 26.1.0]</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioConverter_Result OH_AudioConverter_SetInputCallback(
    OH_AudioConverter* converter,
    OH_AudioConverter_RequestDataCallback callback,
    void* userData
);

/**
 * @brief Executing the audio format conversion.
 *
 * This function executes audio conversion to convert to the target format, and writes the result to the user-provided
 * output buffer. This function must be called after {@link OH_AudioConverter_SetInputCallback}.
 * The output buffer must be allocated and managed by the caller.
 *
 * @param converter Reference created by {@link OH_AudioConverter_Create}.
 * @param outputData Pointer to the output buffer allocated by the caller to receive converted audio data.
 * @param outputCapacity Size of the output buffer in bytes specified by the user.
 * @param outputSize Size of output buffer the system really writes.
 * Returns the number of bytes actually written on success.
 * When {@link AUDIOCONVERTER_SUCCESS} is returned but outputSize is 0,
 * it indicates that all buffered data has been fully flushed.
 * @return <ul>
 *         <li>{@link #AUDIOCONVERTER_SUCCESS} if execution succeeds.</li>
 *         <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM} if parameter is invalid,
 *             e.g. converter is nullptr, e.t.c.</li>
 *         <li>{@link #AUDIOCONVERTER_ERROR_NOT_INITIALIZED} if the converter instance is not initialized</li>
 *         <li>{@link #AUDIOCONVERTER_ERROR_CALLBACK_INVALID} if callback is invalid,
 *             e.g. callback returned an invalid value, e.t.c.</li>
 *         <li>{@link #AUDIOCONVERTER_ERROR_CALLBACK_NOT_SET} if no input callback is bound to the converter</li>
 *         <li>{@link #AUDIOCONVERTER_ERROR_BUFFER_TOO_SMALL} if output buffer capacity is insufficient</li>
 *         <li>{@link #AUDIOCONVERTER_ERROR_SYSTEM} if the system has other abnormalities</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioConverter_Result OH_AudioConverter_Process(
    OH_AudioConverter* converter,
    void* outputData,
    int32_t outputCapacity,
    int32_t* outputSize
);

/**
 * @brief Create an audio converter that supports extended formats.
 *
 * @systemapi
 * @param inputFormat [Input parameter] Pointer to the input audio format. Cannot be NULL and must remain valid for
 *     the duration of the call.
 * @param outputFormat [Input parameter] Pointer to the output audio format. Cannot be NULL and must remain valid
 *     for the duration of the call.
 * @param outOwnedConverter [Output parameter] Pointer to the created audio converter instance. The caller owns the
 *     result and must use the
 * {@link OH_AudioConverter_Destroy} Release. The value cannot be NULL and does not need to be initialized. No content
 * is written when the call fails.
 * @return<ul>
 * <li>{@link #AUDIOCONVERTER_SUCCESS} Execution succeeded. </li>
 * <li>202 Permission verification failed because a non-system application uses the system API. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM}The parameter is invalid. The possible causes are as follows:
 * <br>1. The value of inputFormat is NULL.
 * <br>2. The value of outputFormat is NULL.
 * <br>3. outOwnedConverter is NULL. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_UNSUPPORTED_FORMAT}The audio format in inputFormat/outputFormat is not supported.
 * </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_MEMORY_ALLOC_FAILED} Memory allocation failed. </li>
 * </ul>
 * @release ohaudiosuite/OH_AudioConverter_Destroy {outOwnedConverter}
 * @since 26.1.0
 */
OH_AudioConverter_Result OH_AudioSuite_ConverterCreateEx(
    const OH_AudioSuite_ConverterFormatEx *inputFormat,
    const OH_AudioSuite_ConverterFormatEx *outputFormat,
    OH_AudioConverter **outOwnedConverter);

/**
 * @brief Calculate the minimum number of input bytes and the corresponding number of output bytes to ensure that the
 * output is an integer sample number.
 *
 * The minimum number of bytes is determined by the input and output formats set when the converter was created, and is
 * related to the sampling rate, number of channels, and bit depth.
 * @systemapi
 * @param converter [Input parameter] Converter instance created by the {@link OH_AudioSuite_ConverterCreateEx} or
 *     {@link OH_AudioConverter_Create}.
 * cannot be null and must remain valid during the call.
 * @param inputMinSize [Output parameter] Minimum number of input bytes, in bytes. The value cannot be NULL and does
 *     not need to be initialized. No content is written when the call fails.
 * @param outputMinSize [Output parameter] Minimum number of output bytes, in bytes. The value cannot be NULL and
 *     does not need to be initialized. No content is written when the call fails.
 * @return<ul>
 * <li>{@link #AUDIOCONVERTER_SUCCESS} Execution succeeded. </li>
 * <li>202 Permission verification failed because a non-system application uses the system API. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM}The parameter is invalid. The possible causes are as follows:
 * <br>1. The converter is NULL.
 * <br>2. The value of inputMinSize is NULL.
 * <br>3. The value of outputMinSize is NULL. </li>
 * </ul>
 * @since 26.1.0
 */
OH_AudioConverter_Result OH_AudioSuite_ConverterGetMinInOutSizes(
    OH_AudioConverter *converter, uint32_t *inputMinSize, uint32_t *outputMinSize);

/**
 * @brief Converts the audio format and transfers the input data to the invoking party.
 *
 * This interface processes the input data directly transferred by the invoker. A maximum of 1000 ms audio data can be
 * input each time the interface is invoked.
 * The same converter instance cannot set callback through {@link OH_AudioConverter_SetInputCallback} or transfer data
 * through this interface at the same time.
 * When the input and output sampling rates are different, the first call and the first call after each call
 * {@link OH_AudioSuite_ConverterFlush} are called,
 * The output data is preceded by a certain length of silence data. No padding is performed when the sampling rate is
 * the same.
 * The number of bytes to fill in the silence data can be obtained from {@link OH_AudioSuite_ConverterGetDelaySize}.
 * @systemapi
 * @param converter [Input parameter] Converter instance created by the {@link OH_AudioSuite_ConverterCreateEx} or
 *     {@link OH_AudioConverter_Create}.
 * cannot be null and must remain valid during the call.
 * @param inData [Input parameter] Pointer to the input audio data descriptor. Cannot be NULL and must remain valid
 *     for the duration of the call.
 * **inData->size** indicates the number of input bytes, which must be an integer multiple of the minimum number of
 * input bytes returned by the {@link OH_AudioSuite_ConverterGetMinInOutSizes}.
 * @param outData [Input parameter, output parameter] Pointer to the output audio data descriptor. Cannot be NULL
 *     and must remain valid for the duration of the call.
 * <br>The caller needs to allocate the output buffer and set **outData->data** and **outData->size**.
 * If **inData->size** is k times the minimum number of input bytes, **outData->size** must be greater than k times the
 * minimum number of output bytes,
 * The minimum number of input bytes and the minimum number of output bytes are obtained from
 * {@link OH_AudioSuite_ConverterGetMinInOutSizes}.
 * <br>The conversion result is written to **outData->data**. The actual number of written bytes is returned through
 * **outData->writeSize**.
 * <br>No content is written when the call fails.
 * @return<ul>
 * <li>{@link #AUDIOCONVERTER_SUCCESS} Execution succeeded. </li>
 * <li>202 Permission verification failed because a non-system application uses the system API. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM}The parameter is invalid. The possible causes are as follows:
 * <br>1. The converter is NULL.
 * <br>2. The value of inData is NULL.
 * <br>3. **inData->data** is NULL.
 * <br>4. **inData->size** is 0.
 * <br>5. **inData->size** is not an integer multiple of the minimum number of input bytes returned by the
 * {@link OH_AudioSuite_ConverterGetMinInOutSizes}.
 * <br>6. **inData->size** The audio duration exceeds 1000 ms.
 * <br>7. The value of outData is NULL.
 * <br>8. **outData->data** is NULL. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_UNSUPPORTED_OPERATION} The callback has been set through
 * {@link OH_AudioConverter_SetInputCallback}. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_BUFFER_TOO_SMALL}The output buffer is insufficient. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_SYSTEM} An internal system error occurs. </li>
 * </ul>
 * @since 26.1.0
 */
OH_AudioConverter_Result OH_AudioSuite_ConverterDirectProcess(
    OH_AudioConverter *converter,
    const OH_AudioSuite_ConverterInputInfo *inData,
    OH_AudioSuite_ConverterOutputInfo *outData);

/**
 * @brief Obtains the number of silent data bytes padded before the first output data during sampling rate conversion.
 *
 * This interface is invoked after the {@link OH_AudioSuite_ConverterDirectProcess} generates mute filling.
 * The mute padding is re-created after {@link OH_AudioSuite_ConverterFlush} is called.
 * If the sampling rates are the same, 0 is returned.
 * @systemapi
 * @param converter [Input parameter] Converter instance created by the {@link OH_AudioSuite_ConverterCreateEx} or
 *     {@link OH_AudioConverter_Create}.
 * cannot be null and must remain valid during the call.
 * @param delaySize [Output parameter] Number of bytes filled before the first output data, in bytes.
 * cannot be NULL and does not need to be initialized. No content is written when the call fails.
 * @return<ul>
 * <li>{@link #AUDIOCONVERTER_SUCCESS} Execution succeeded. </li>
 * <li>202 Permission verification failed because a non-system application uses the system API. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM}The parameter is invalid. The possible causes are as follows:
 * <br>1. The converter is NULL.
 * <br>2. The value of delaySize is NULL. </li>
 * </ul>
 * @since 26.1.0
 */
OH_AudioConverter_Result OH_AudioSuite_ConverterGetDelaySize(OH_AudioConverter *converter, uint32_t *delaySize);

/**
 * @brief Clears the internal buffer and processing status of the audio converter.
 *
 * when the audio data is discontinuous(e.g., fast forward, fast rewind scene), or when a new audio stream is restarted
 * before the processing of an audio stream is completed,
 * This interface needs to be called to clear the internal cache and processing status of the converter. Restore the
 * converter to its original state.
 * After the call, the converter can continue to receive new audio data for conversion without destroying and
 * rebuilding.
 * @systemapi
 * @param converter [Input parameter] Converter instance created by the {@link OH_AudioSuite_ConverterCreateEx} or
 *     {@link OH_AudioConverter_Create}.
 * cannot be null and must remain valid during the call.
 * @return<ul>
 * <li>{@link #AUDIOCONVERTER_SUCCESS} Execution succeeded. </li>
 * <li>202 Permission verification failed because a non-system application uses the system API. </li>
 * <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM} The parameter is invalid. The converter is NULL. </li>
 * </ul>
 * @since 26.1.0
 */
OH_AudioConverter_Result OH_AudioSuite_ConverterFlush(OH_AudioConverter *converter);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_AUDIO_CONVERTER_H
