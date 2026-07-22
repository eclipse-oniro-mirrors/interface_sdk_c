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
 * @addtogroup AudioConverter
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
     * @error
     * 函数调用成功。
     * @since 26.0.0
     */
    AUDIOCONVERTER_SUCCESS = 0,
    /**
     * @error
     * 函数输入参数无效。例如传入的格式转换器指针为nullptr。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_INVALID_PARAM = 1,
    /**
     * @error
     * 不支持的音频格式。例如不支持的编码类型、采样格式等。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_UNSUPPORTED_FORMAT = 2,
    /**
     * @error
     * 系统错误。例如使用已销毁的格式转换器执行格式转换。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_SYSTEM = 3,
    /**
     * @error
     * 内存分配失败。例如内部输出数据缓冲区内存分配失败。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_MEMORY_ALLOC_FAILED = 4,
    /**
     * @error
     * 输出缓存容量不足。例如设置的存储输出数据的容量不足以存储一帧输出数据量。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_BUFFER_TOO_SMALL = 5,
    /**
     * @error
     * 音频转换器实例未初始化。例如未创建格式转换器直接执行格式转换处理函数。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_NOT_INITIALIZED = 6,
    /**
     * @error
     * 输入回调函数无效。例如输入回调函数返回数据量小于0或大于最大值400KB。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_CALLBACK_INVALID = 7,
    /**
     * @error
     * 未设置回调函数。例如输入回调函数指针为nullptr。
     * @since 26.0.0
     */
    AUDIOCONVERTER_ERROR_CALLBACK_NOT_SET = 8
} OH_AudioConverter_Result;

/**
 * @brief 创建音频转换器。
 *
 * @param inputFormat 指向输入音频格式的指针。
 * @param outputFormat 指向输出音频格式的指针。
 * @param converter 指向可用的音频转换器的指针。
 * @return AUDIOCONVERTER_SUCCESS：创建格式转换器成功，可以正常执行后续流程。
 *     <br>AUDIOCONVERTER_ERROR_INVALID_PARAM：函数输入参数无效，需要检查传入的格式转换器指针是否非nullptr。
 *     <br>AUDIOCONVERTER_ERROR_UNSUPPORTED_FORMAT：音频输入/输出格式组合不支持，输入或输出格式超出允许范围，需要检查配置的音频格式。
 *     <br>AUDIOCONVERTER_ERROR_SYSTEM：系统错误，需要检查是否使用已销毁的格式转换器执行格式转换。
 * @release OH_AudioConverter_Destroy {converter}
 * @since 26.0.0
 */
OH_AudioConverter_Result OH_AudioConverter_Create(
    const OH_AudioConverter_Format* inputFormat,
    const OH_AudioConverter_Format* outputFormat,
    OH_AudioConverter** converter);

/**
 * @brief 请求释放转换器。
 *
 * @param converter 由{@link OH_AudioConverter_Create}函数创建的转换器。
 * @since 26.0.0
 */
void OH_AudioConverter_Destroy(OH_AudioConverter* converter);

/**
 * @brief 定义回调函数{@link OH_AudioConverter_RequestDataCallback}提供的输入音频数据的状态。转换器使用此状态来确定如何处理后续的转换逻辑。例如，继续提取数据，暂停或清除缓存数据。
 * <br>注意：即使回调返回AUDIOCONVERTER_INPUT_DATA_FINISHED，也必须重复调用OH_AudioConverter_Process，直到{@link OH_AudioConverter_Process}
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
    AUDIOCONVERTER_INPUT_DATA_FINISHED = 3
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
 * @brief 设置转换器请求数据回调函数。此函数绑定音频转换器的输入数据回调函数。回调函数由{@link OH_AudioConverter_Process}调用，获取输入音频数据并进行处理。
 *
 * @param converter 由{@link OH_AudioConverter_Create}函数创建转换器。
 * @param callback 回调函数用于写入音频数据。
 * @param userData 指向将传递给回调函数的应用程序数据结构的指针。
 * @return AUDIOCONVERTER_SUCCESS：设置输入回调函数成功，可以正常执行后续流程。
 *     <br>AUDIOCONVERTER_ERROR_INVALID_PARAM：函数输入参数无效，需要检查传入的格式转换器指针是否非nullptr。
 *     <br>AUDIOCONVERTER_ERROR_NOT_INITIALIZED：格式转换器未初始化，需要检查当前格式转换器是否有效。
 *     <br>AUDIOCONVERTER_ERROR_CALLBACK_INVALID：回调函数无效，需要检查输入回调函数返回数据量是否在允许范围内。
 *     <br>AUDIOCONVERTER_ERROR_CALLBACK_NOT_SET：回调函数未设置，需要检查回调函数指针是否非空。
 *     <br>AUDIOCONVERTER_ERROR_SYSTEM：系统错误，需要检查是否使用已销毁的格式转换器执行格式转换。
 * @since 26.0.0
 */
OH_AudioConverter_Result OH_AudioConverter_SetInputCallback(
    OH_AudioConverter* converter,
    OH_AudioConverter_RequestDataCallback callback,
    void* userData
);

/**
 * @brief 执行音频格式转换处理函数。该函数执行音频转换过程，将输入音频转换为目标格式，需要注意：该函数必须在{@link OH_AudioConverter_SetInputCallback}之后调用，
 * 并且最终转换结果写入的输出缓冲区必须由调用方分配和管理。
 *
 * @param converter 由{@link OH_AudioConverter_Create}函数创建转换器。
 * @param outputData 指向调用者分配的输出缓冲区的指针。
 * @param outputCapacity 调用者指定的输出缓冲区大小。
 * @param outputSize 系统实际写入输出缓冲区数据的大小。
 * @return AUDIOCONVERTER_SUCCESS：PCM音频数据格式转换成功，可以正常执行后续流程。
 *     <br>AUDIOCONVERTER_ERROR_INVALID_PARAM：函数输入参数无效，需要检查传入的格式转换器指针是否非nullptr。
 *     <br>AUDIOCONVERTER_ERROR_NOT_INITIALIZED：格式转换器未初始化，需要检查当前格式转换器是否有效。
 *     <br>AUDIOCONVERTER_ERROR_CALLBACK_INVALID：输入回调函数无效，需要检查输入回调函数返回数据量是否在允许范围内。
 *     <br>AUDIOCONVERTER_ERROR_CALLBACK_NOT_SET：回调函数未设置，需要检查回调函数是否已成功设置并且函数指针是否非空。
 *     <br>AUDIOCONVERTER_ERROR_BUFFER_TOO_SMALL：输出缓冲区容量不足，需要检查设置的存储输出数据的缓冲区容量是否足够存放一帧输出数据。
 *     <br>AUDIOCONVERTER_ERROR_SYSTEM：系统错误，需要检查是否使用已销毁的格式转换器执行格式转换。
 * @since 26.0.0
 */
OH_AudioConverter_Result OH_AudioConverter_Process(
    OH_AudioConverter* converter,
    void* outputData,
    int32_t outputCapacity,
    int32_t* outputSize
);

#ifdef __cplusplus
}
#endif
/** @} */
#endif // NATIVE_AUDIO_CONVERTER_H