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
 * @brief 提供音频编创相关C接口定义，包含多种专业级音频效果处理功能，服务于音频编辑和创作类应用场景。
 *
 * @since 26.0.0
 * @version 1.0
 */
/**
 * @file native_audio_converter.h
 *
 * @brief 声明输入音频格式、输出音频格式底层数据结构和格式转换接口。
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
 * @brief 定义音频转换器格式数据结构，用于描述基本音频格式。
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
 * @brief 定义扩展音频转换器格式信息结构体，用于描述支持任意采样率的音频格式。
 *
 * @since 26.1.0
 */
typedef struct OH_AudioSuite_ConverterFormatEx {
    /**
     * @brief 音频编码格式类型。
     *
     * @since 26.1.0
     */
    OH_Audio_EncodingType encodingType;
    /**
     * @brief 音频采样率，单位为赫兹（Hz）。
     * 支持[8000, 5644800]范围内10Hz整数倍的采样率，以及11025Hz。
     *
     * @since 26.1.0
     */
    int32_t samplingRate;
    /**
     * @brief 音频声道布局。
     * 支持的取值范围为{@link OH_AudioChannelLayout}.CH_LAYOUT_MONO、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_STEREO、{@link OH_AudioChannelLayout}.CH_LAYOUT_STEREO_DOWNMIX、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_2POINT1、{@link OH_AudioChannelLayout}.CH_LAYOUT_3POINT0、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_SURROUND、{@link OH_AudioChannelLayout}.CH_LAYOUT_3POINT1、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_4POINT0、{@link OH_AudioChannelLayout}.CH_LAYOUT_QUAD_SIDE、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_QUAD、{@link OH_AudioChannelLayout}.CH_LAYOUT_2POINT0POINT2、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_4POINT1、{@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT0、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT0_BACK、{@link OH_AudioChannelLayout}.CH_LAYOUT_2POINT1POINT2、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_3POINT0POINT2、{@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1_BACK、{@link OH_AudioChannelLayout}.CH_LAYOUT_6POINT0、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_3POINT1POINT2、{@link OH_AudioChannelLayout}.CH_LAYOUT_6POINT0_FRONT、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_HEXAGONAL、{@link OH_AudioChannelLayout}.CH_LAYOUT_6POINT1、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_6POINT1_BACK、{@link OH_AudioChannelLayout}.CH_LAYOUT_6POINT1_FRONT、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT0、{@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT0_FRONT、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1、{@link OH_AudioChannelLayout}.CH_LAYOUT_OCTAGONAL、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_5POINT1POINT2、{@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1_WIDE、
     * {@link OH_AudioChannelLayout}.CH_LAYOUT_7POINT1_WIDE_BACK。
     *
     * @since 26.1.0
     */
    OH_AudioChannelLayout channelLayout;
    /**
     * @brief 音频采样格式。
     *
     * @since 26.1.0
     */
    OH_Audio_SampleFormat sampleFormat;
} OH_AudioSuite_ConverterFormatEx;

/**
 * @brief 定义音频转换器输入数据结构体。
 *
 * @since 26.1.0
 */
typedef struct OH_AudioSuite_ConverterInputInfo {
    /**
     * @brief 输入音频数据缓冲区指针，指向音频原始数据，由调用者分配。
     * 具体数据类型由采样格式{@link OH_Audio_SampleFormat}决定。
     * 调用{@link OH_AudioSuite_ConverterDirectProcess}期间必须保持有效。不能为NULL。
     *
     * @since 26.1.0
     */
    const void *data;
    /**
     * @brief 输入缓冲区容量，单位为字节。必须大于0。
     *
     * @since 26.1.0
     */
    uint32_t size;
} OH_AudioSuite_ConverterInputInfo;

/**
 * @brief 定义音频转换器输出数据结构体，用于直接处理模式接收转换后的音频数据。
 *
 * @since 26.1.0
 */
typedef struct OH_AudioSuite_ConverterOutputInfo {
    /**
     * @brief 输出音频数据缓冲区指针，由调用者分配。
     * 转换结果将写入此缓冲区。
     * 具体数据类型由采样格式{@link OH_Audio_SampleFormat}决定。
     * 调用{@link OH_AudioSuite_ConverterDirectProcess}期间必须保持有效。不能为NULL。
     *
     * @since 26.1.0
     */
    void *data;
    /**
     * @brief 输出缓冲区容量，单位为字节，必须大于0。
     *
     * @since 26.1.0
     */
    uint32_t size;
    /**
     * @brief 输出参数，返回实际写入输出缓冲区的字节数。
     * 调用前无需初始化；调用失败时不会写入内容。
     *
     * @since 26.1.0
     */
    uint32_t writeSize;
} OH_AudioSuite_ConverterOutputInfo;

/**
 * @brief 声明音频格式转换器。<br> 音频格式转换器句柄用于执行音频格式转换相关功能。
 *
 * @since 26.0.0
 */
typedef struct OH_AudioConverterStruct OH_AudioConverter;

/**
 * @brief 定义函数执行的返回结果。
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * @error 函数调用成功。
     * @since 26.0.0
     */
    AUDIOCONVERTER_SUCCESS = 0,
    /**
     * @error 函数输入参数无效。例如传入的格式转换器指针为nullptr。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_INVALID_PARAM = 1,
    /**
     * @error 不支持的音频格式。例如不支持的编码类型、采样格式等。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_UNSUPPORTED_FORMAT = 2,
    /**
     * @error 系统错误。例如使用已销毁的格式转换器执行格式转换。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_SYSTEM = 3,
    /**
     * @error 内存分配失败。例如内部输出数据缓冲区内存分配失败。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_MEMORY_ALLOC_FAILED = 4,
    /**
     * @error 输出缓存容量不足。例如设置的存储输出数据的容量不足以存储一帧输出数据量。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_BUFFER_TOO_SMALL = 5,
    /**
     * @error 音频转换器实例未初始化。例如未创建格式转换器直接执行格式转换处理函数。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_NOT_INITIALIZED = 6,
    /**
     * @error 输入回调函数无效。例如输入回调函数返回数据量小于0或大于最大值400KB。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_CALLBACK_INVALID = 7,
    /**
     * @error 未设置回调函数。例如输入回调函数指针为空指针。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_CALLBACK_NOT_SET = 8,
    /**
     * @brief 权限校验失败，非系统应用调用了系统API。
     * @since 26.1.0
     */
    AUDIOCONVERTER_ERROR_NOT_SYSTEM_APP = 202,
    /**
     * @brief 操作不支持。
     * @since 26.1.0
     */
    AUDIOCONVERTER_ERROR_UNSUPPORTED_OPERATION = 6800104,
} OH_AudioConverter_Result;

/**
 * @brief 创建音频格式转换器。
 *
 * @param inputFormat 指向输入音频格式的指针。
 * @param outputFormat 指向输出音频格式的指针。
 * @param converter 指向可用的音频格式转换器的指针。
 * @return AUDIOCONVERTER_SUCCESS：创建音频格式转换器成功，可以正常执行后续流程。
 *     <br>AUDIOCONVERTER_ERROR_INVALID_PARAM：函数输入参数无效，需要检查传入的音频格式转换器指针是否非空指针。
 *     <br>AUDIOCONVERTER_ERROR_UNSUPPORTED_FORMAT：音频输入/输出格式组合不支持，输入或输出格式超出允许范围，
 *     需要检查配置的音频格式。
 *     <br>AUDIOCONVERTER_ERROR_SYSTEM：系统错误，需要检查是否使用已销毁的音频格式转换器执行格式转换。
 * @release OH_AudioConverter_Destroy {converter}
 * @since 26.0.0
 */
OH_AudioConverter_Result OH_AudioConverter_Create(
    const OH_AudioConverter_Format* inputFormat,
    const OH_AudioConverter_Format* outputFormat,
    OH_AudioConverter** converter);

/**
 * @brief 销毁音频格式转换器。
 *
 * @param converter 由{@link OH_AudioConverter_Create}函数创建的转换器。
 * @since 26.0.0
 */
void OH_AudioConverter_Destroy(OH_AudioConverter* converter);

/**
 * @brief 定义回调函数{@link OH_AudioConverter_RequestDataCallback}提供的输入音频数据的状态。
 * 转换器使用此状态来确定如何处理后续的转换逻辑。例如，继续提取数据，暂停或清除缓存数据。
 * <br>注意：即使回调返回AUDIOCONVERTER_INPUT_DATA_FINISHED，也必须重复调用OH_AudioConverter_Process，
 * 直到{@link OH_AudioConverter_Process}
 * 返回AUDIOCONVERTER_SUCCESS，并且outputSize=0（表示所有缓存数据均已处理完成）。
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * 提供的输入数据有效。
     * @since 26.0.0
     */
    AUDIOCONVERTER_INPUT_HAVE_DATA = 1,
    /**
     * 暂时没有可用的输入数据。
     * @since 26.0.0
     */
    AUDIOCONVERTER_INPUT_NO_AVAILABLE_DATA = 2,
    /**
     * 输入数据流已完成。
     * @since 26.0.0
     */
    AUDIOCONVERTER_INPUT_DATA_FINISHED = 3,
} OH_AudioConverter_InputStatus;

/**
 * @brief 请求数据的回调函数。转换器在{@link OH_AudioConverter_Process}期间调用此回调函数以主动请求输入音频数据。
 * <br>调用者必须填充输出参数（outInputData，outStatus），并返回通过回调函数读取的数据大小。
 * <br>单个回调返回的最大数据大小为400KB。
 * <br>outInputData指向的内存必须保持有效，直到OH_AudioConverter_Process返回处理完成为止。
 *
 * @param userData 传递给回调函数的用户自定义数据。
 * @param outInputData 指向回调函数设置的指向输入音频数据缓冲区的指针。
 * @param outStatus 通过回调函数设置，用于通知转换器输入数据的状态。
 * @return 通过outInputData指针指向有效的输入数据的大小。
 * @since 26.0.0
 */
typedef int32_t (*OH_AudioConverter_RequestDataCallback)(
    void* userData,
    const void** outInputData,
    OH_AudioConverter_InputStatus* outStatus
);

/**
 * @brief 设置转换器请求数据回调函数。此函数绑定音频格式转换器的输入数据回调函数。
 * 回调函数由{@link OH_AudioConverter_Process}调用，获取输入音频数据并进行处理。
 *
 * @param converter 由{@link OH_AudioConverter_Create}函数创建转换器。
 * @param callback 回调函数用于写入音频数据。
 * @param userData 指向将传递给回调函数的应用程序数据结构的指针。
 * @return <ul>
 *     <li>{@link #AUDIOCONVERTER_SUCCESS} 设置输入回调函数成功，可以正常执行后续流程。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM} 函数输入参数无效，
 *     需要检查传入的音频格式转换器指针是否非空指针。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_NOT_INITIALIZED} 音频格式转换器未初始化，
 *     需要检查当前音频格式转换器是否有效。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_CALLBACK_INVALID} 回调函数无效，
 *     需要检查输入回调函数返回数据量是否在允许范围内。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_CALLBACK_NOT_SET} 回调函数未设置，需要检查回调函数指针是否非空。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_SYSTEM} 系统错误，需要检查是否使用已销毁的音频格式转换器执行格式转换。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_UNSUPPORTED_OPERATION} 当前处理流程不支持设置回调。[since 26.1.0]</li>
 *     </ul>
 * @since 26.0.0
 */
OH_AudioConverter_Result OH_AudioConverter_SetInputCallback(
    OH_AudioConverter* converter,
    OH_AudioConverter_RequestDataCallback callback,
    void* userData
);

/**
 * @brief 执行音频格式转换处理函数。该函数执行音频转换过程，将输入音频转换为目标格式，
 * 需要注意：该函数必须在{@link OH_AudioConverter_SetInputCallback}之后调用，
 * 并且最终转换结果写入的输出缓冲区必须由调用方分配和管理。即使回调返回AUDIOCONVERTER_INPUT_DATA_FINISHED，
 * 也必须重复调用此函数，
 * 直到返回AUDIOCONVERTER_SUCCESS且outputSize=0（表示所有缓存数据均已处理完成）。
 *
 * @param converter 由{@link OH_AudioConverter_Create}函数创建转换器。
 * @param outputData 指向调用者分配的输出缓冲区的指针。
 * @param outputCapacity 调用者指定的输出缓冲区大小。
 * @param outputSize 系统实际写入输出缓冲区数据的大小。
 * @return AUDIOCONVERTER_SUCCESS：PCM音频数据格式转换成功，可以正常执行后续流程。
 *     <br>AUDIOCONVERTER_ERROR_INVALID_PARAM：函数输入参数无效，需要检查传入的音频格式转换器指针是否非空指针。
 *     <br>AUDIOCONVERTER_ERROR_NOT_INITIALIZED：音频格式转换器未初始化，需要检查当前音频格式转换器是否有效。
 *     <br>AUDIOCONVERTER_ERROR_CALLBACK_INVALID：输入回调函数无效，需要检查输入回调函数返回数据量是否在允许范围内。
 *     <br>AUDIOCONVERTER_ERROR_CALLBACK_NOT_SET：回调函数未设置，需要检查回调函数是否已成功设置并且函数指针是否非空。
 *     <br>AUDIOCONVERTER_ERROR_BUFFER_TOO_SMALL：输出缓冲区容量不足，
 *     需要检查设置的存储输出数据的缓冲区容量是否足够存放一帧输出数据。
 *     <br>AUDIOCONVERTER_ERROR_SYSTEM：系统错误，需要检查是否使用已销毁的音频格式转换器执行格式转换。
 * @since 26.0.0
 */
OH_AudioConverter_Result OH_AudioConverter_Process(
    OH_AudioConverter* converter,
    void* outputData,
    int32_t outputCapacity,
    int32_t* outputSize
);

/**
 * @brief 创建支持扩展格式的音频转换器。
 *
 * @systemapi
 * @param inputFormat [入参] 输入音频格式配置指针。不能为NULL，调用期间必须保持有效。
 * @param outputFormat [入参] 输出音频格式配置指针。不能为NULL，调用期间必须保持有效。
 * @param outOwnedConverter [出参] 用于接收创建的音频转换器实例的指针。调用方拥有该结果并必须使用
 *     {@link OH_AudioConverter_Destroy}释放。不能为NULL，无需初始化。调用失败时不会写入内容。
 * @return <ul>
 *     <li>{@link #AUDIOCONVERTER_SUCCESS} 执行成功。</li>
 *     <li>202 权限校验失败，非系统应用使用了系统API。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM} 参数无效，可能原因如下：
 *     <br>1. inputFormat为NULL。
 *     <br>2. outputFormat为NULL。
 *     <br>3. outOwnedConverter为NULL。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_UNSUPPORTED_FORMAT} inputFormat/outputFormat中的音频格式不支持。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_MEMORY_ALLOC_FAILED} 内存分配失败。</li>
 *     </ul>
 * @release ohaudiosuite/OH_AudioConverter_Destroy {outOwnedConverter}
 * @since 26.1.0
 */
OH_AudioConverter_Result OH_AudioSuite_ConverterCreateEx(
    const OH_AudioSuite_ConverterFormatEx *inputFormat,
    const OH_AudioSuite_ConverterFormatEx *outputFormat,
    OH_AudioConverter **outOwnedConverter);

/**
 * @brief 计算保证输出为整数采样数的最小输入字节数及对应输出字节数。
 *
 * 最小字节数由创建转换器时设置的输入和输出格式共同决定，与采样率、通道数、位深均相关。
 * @systemapi
 * @param converter [入参] 由{@link OH_AudioSuite_ConverterCreateEx}或{@link OH_AudioConverter_Create}创建的转换器实例。
 *     不能为NULL，调用期间必须保持有效。
 * @param inputMinSize [出参] 返回最小输入字节数，单位为字节。不能为NULL，无需初始化；调用失败时不会写入内容。
 * @param outputMinSize [出参] 返回对应最小输出字节数，单位为字节。不能为NULL，无需初始化；调用失败时不会写入内容。
 * @return <ul>
 *     <li>{@link #AUDIOCONVERTER_SUCCESS} 执行成功。</li>
 *     <li>202 权限校验失败，非系统应用使用了系统API。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM} 参数无效，可能原因如下：
 *     <br>1. converter为NULL。
 *     <br>2. inputMinSize为NULL。
 *     <br>3. outputMinSize为NULL。</li>
 *     </ul>
 * @since 26.1.0
 */
OH_AudioConverter_Result OH_AudioSuite_ConverterGetMinInOutSizes(
    OH_AudioConverter *converter, uint32_t *inputMinSize, uint32_t *outputMinSize);

/**
 * @brief 执行音频格式转换，由调用方直接传入输入数据。
 *
 * 该接口处理调用者直接传入的输入数据，每次调用最多支持输入1000ms长度的音频数据。
 * 同一转换器实例不可同时通过{@link OH_AudioConverter_SetInputCallback}设置回调或由本接口传入数据，二者只能选择一种。
 * 当输入和输出采样率不同时，首次调用及每次调用{@link OH_AudioSuite_ConverterFlush}后的首次调用，
 * 会在输出数据前面填充一定长度的静音数据。采样率相同时不会填充。
 * 填充静音数据的字节数可通过{@link OH_AudioSuite_ConverterGetDelaySize}获取。
 * @systemapi
 * @param converter [入参] 由{@link OH_AudioSuite_ConverterCreateEx}或{@link OH_AudioConverter_Create}创建的转换器实例。
 *     不能为NULL，调用期间必须保持有效。
 * @param inData [入参] 输入音频数据描述符指针。不能为NULL，调用期间必须保持有效。
 *     **inData->size**为输入字节数，必须是{@link OH_AudioSuite_ConverterGetMinInOutSizes}返回的最小输入字节数的整数倍。
 * @param outData [入参，出参] 输出音频数据描述符指针。不能为NULL，调用期间必须保持有效。
 *     <br>调用者需分配输出缓冲区并设置**outData->data**和**outData->size**。
 *     若**inData->size**是最小输入字节数的k倍，则**outData->size**必须大于最小输出字节数的k倍，
 *     其中最小输入字节数和最小输出字节数由{@link OH_AudioSuite_ConverterGetMinInOutSizes}获取。
 *     <br>转换结果写入**outData->data**，实际写入字节数通过**outData->writeSize**返回。
 *     <br>调用失败时不会写入内容。
 * @return <ul>
 *     <li>{@link #AUDIOCONVERTER_SUCCESS} 执行成功。</li>
 *     <li>202 权限校验失败，非系统应用使用了系统API。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM} 参数无效，可能原因如下：
 *     <br>1. converter为NULL。
 *     <br>2. inData为NULL。
 *     <br>3. **inData->data**为NULL。
 *     <br>4. **inData->size**为0。
 *     <br>5. **inData->size**不是{@link OH_AudioSuite_ConverterGetMinInOutSizes}返回的最小输入字节数的整数倍。
 *     <br>6. **inData->size**对应的音频时长超过1000毫秒。
 *     <br>7. outData为NULL。
 *     <br>8. **outData->data**为NULL。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_UNSUPPORTED_OPERATION} 已通过{@link OH_AudioConverter_SetInputCallback}设置回调。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_BUFFER_TOO_SMALL} 输出缓冲区不足。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_SYSTEM} 系统内部错误。</li>
 *     </ul>
 * @since 26.1.0
 */
OH_AudioConverter_Result OH_AudioSuite_ConverterDirectProcess(
    OH_AudioConverter *converter,
    const OH_AudioSuite_ConverterInputInfo *inData,
    OH_AudioSuite_ConverterOutputInfo *outData);

/**
 * @brief 获取采样率转换时首次输出数据前面填充的静音数据字节数。
 *
 * 需在{@link OH_AudioSuite_ConverterDirectProcess}产生静音填充后调用。
 * 调用{@link OH_AudioSuite_ConverterFlush}后静音填充会重新产生。
 * 采样率相同时返回0。
 * @systemapi
 * @param converter [入参] 由{@link OH_AudioSuite_ConverterCreateEx}或{@link OH_AudioConverter_Create}创建的转换器实例。
 *     不能为NULL，调用期间必须保持有效。
 * @param delaySize [出参] 返回首次输出数据前面填充的静音数据字节数，单位为字节。
 *     不能为NULL，无需初始化；调用失败时不会写入内容。
 * @return <ul>
 *     <li>{@link #AUDIOCONVERTER_SUCCESS} 执行成功。</li>
 *     <li>202 权限校验失败，非系统应用使用了系统API。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM} 参数无效，可能原因如下：
 *     <br>1. converter为NULL。
 *     <br>2. delaySize为NULL。</li>
 *     </ul>
 * @since 26.1.0
 */
OH_AudioConverter_Result OH_AudioSuite_ConverterGetDelaySize(OH_AudioConverter *converter, uint32_t *delaySize);

/**
 * @brief 清空音频转换器内部缓存和处理状态。
 *
 * 当音频数据不连续时（例如快进、快退场景），或者在一个音频流处理结束前、重新开始一个新的音频流时，
 * 需要调用此接口清空转换器内部缓存和处理状态。使转换器恢复到初始状态。
 * 调用后转换器可继续接收新的音频数据进行转换，无需销毁重建。
 * @systemapi
 * @param converter [入参] 由{@link OH_AudioSuite_ConverterCreateEx}或{@link OH_AudioConverter_Create}创建的转换器实例。
 *     不能为NULL，调用期间必须保持有效。
 * @return <ul>
 *     <li>{@link #AUDIOCONVERTER_SUCCESS} 执行成功。</li>
 *     <li>202 权限校验失败，非系统应用使用了系统API。</li>
 *     <li>{@link #AUDIOCONVERTER_ERROR_INVALID_PARAM} 参数无效，converter为NULL。</li>
 *     </ul>
 * @since 26.1.0
 */
OH_AudioConverter_Result OH_AudioSuite_ConverterFlush(OH_AudioConverter *converter);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_AUDIO_CONVERTER_H
