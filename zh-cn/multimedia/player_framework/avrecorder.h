/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup AVRecorder
 * @{
 *
 * @brief AVRecorder提供媒体录制能力，支持配置录制参数及实时状态回调，适用于视频通话录制、语音备忘录等需要将音视频内容录制保存为文件的场景。<br>
 *
 * 开发者可根据开发需求，参考对应的开发指南及样例：<br>
 *
 * - [使用AVRecorder录制音频（C/C++）](../../../media/media/using-ndk-avrecorder-for-audio-recording.md)<br>
 * - [使用AVRecorder录制视频（C/C++）](../../../media/media/using-ndk-avrecorder-for-video-recording.md)<br>
 *
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 * @}
 */
/**
 * @file avrecorder.h
 *
 * @brief 定义AVRecorder接口。AVRecorder提供媒体录制能力，支持音视频数据的采集与录制、完整的状态管理与回调监听、灵活的编码器选择与参数配置等，适用于需要将音视频内容录制保存为文件的场景。
 * 
 * @kit MediaKit
 * @include <multimedia/player_framework/avrecorder.h>
 * @library libavrecorder.so
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */

#ifndef MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_H
#define MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_H

#include <memory>
#include <stdint.h>
#include <stdio.h>
#include "avrecorder_base.h"
#include "native_averrors.h"
#include "native_window/external_window.h"
#include "native_avformat.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 创建AVRecorder实例。调用成功之后进入AVRECORDER_IDLE状态。必须在使用完毕后调用{@link OH_AVRecorder_Release}释放资源，否则会导致录制资源泄漏。
 * 
 * @return 成功时返回指向OH_AVRecorder实例的指针，用于后续的录制操作（如Prepare、Start、Pause等）；失败时返回nullptr。
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
*/
OH_AVRecorder *OH_AVRecorder_Create(void);

/**
 * @brief 配置AVRecorder参数，准备录制。
 * 必须在{@link OH_AVRecorder_Create}和{@link OH_AVRecorder_Start}之间调用，调用成功之后进入AVRECORDER_PREPARED状态。
 * 若未配置视频相关参数，则只录制音频；同理，若未配置音频相关参数，则只录制视频。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param config 指向OH_AVRecorder_Config实例的指针，用于配置录制的音视频参数，包括音频和视频的编码格式、采样率、分辨率等配置信息。
 * 若未配置视频相关参数，则只录制音频；若未配置音频相关参数，则只录制视频。不可为nullptr，否则返回AV_ERR_INVALID_VAL。
 * @return AV_ERR_OK：执行成功。<br>
 * AV_ERR_INVALID_VAL：输入的recorder/config为nullptr或准备失败。
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Prepare(OH_AVRecorder *recorder, OH_AVRecorder_Config *config);

/**
 * @brief 获取当前的录制参数。必须在{@link OH_AVRecorder_Prepare}之后调用。典型使用场景包括：录制开始前确认配置参数是否正确、在UI界面上展示当前录制设置信息等。
 * 传入的*config必须为nullptr，由框架层统一分配和释放内存，防止内存泄漏或重复释放等问题。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param config 指向OH_AVRecorder_Config实例指针的指针，用于获取当前的录制参数配置。传入时*config必须为nullptr，由框架层统一分配和释放内存，防止内存泄漏或重复释放等问题。
 * 调用成功后，*config指向框架层分配的配置实例。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或*config不为nullptr。
 * AV_ERR_NO_MEMORY：内存不足，*config内存分配失败，请释放资源后重试。
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_GetAVRecorderConfig(OH_AVRecorder *recorder, OH_AVRecorder_Config **config);

/**
 * @brief 获取输入Surface。必须在{@link OH_AVRecorder_Prepare}和{@link OH_AVRecorder_Start}之间调用。<br>
 * 传入的*window必须为nullptr，由框架层统一分配和释放内存，以避免内存管理混乱，防止内存泄漏或重复释放等问题。<br>
 * 此Surface提供给调用者，调用者从此Surface中获取Surface Buffer，填入待录制的视频数据。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param window 指向OHNativeWindow实例指针的指针，用于获取输入Surface。*window必须为nullptr，由框架层统一分配和释放内存，防止内存泄漏或重复释放等问题。
 * 调用成功后，*window指向框架层分配的OHNativeWindow实例，调用者可从此实例中获取Surface填入视频数据。若*window不为nullptr，将返回AV_ERR_INVALID_VAL错误。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或*window不为nullptr。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_GetInputSurface(OH_AVRecorder *recorder, OHNativeWindow **window);

/**
 * @brief 更新视频旋转角度。典型使用场景包括：设备横竖屏切换时调整视频方向、根据摄像头采集方向设置视频旋转角度等。
 * 必须在{@link OH_AVRecorder_Prepare}和{@link OH_AVRecorder_Start}之间调用。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param rotation 视频旋转角度，单位为度（°）。
 * 可选值：0°（无旋转，适用于正常方向录制）、90°（旋转90°，适用于设备顺时针横屏切换时调整视频方向）、180°（旋转180°，适用于倒置方向录制）、270°（旋转270°，适用于设备逆时针横屏切换时调整视频方向）。
 * 必须是上述值中的一个，传入其他角度值时返回AV_ERR_INVALID_VAL。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或输入的rotation不符合要求或更新方向失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_UpdateRotation(OH_AVRecorder *recorder, int32_t rotation);

/**
 * @brief 开始录制。必须在{@link OH_AVRecorder_Prepare}之后调用，调用成功之后进入AVRECORDER_STARTED状态。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或启动失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Start(OH_AVRecorder *recorder);

/**
 * @brief 暂停录制。必须在{@link OH_AVRecorder_Start}之后调用，调用成功之后进入AVRECORDER_PAUSED状态。<br>
 * 之后可以通过调用{@link OH_AVRecorder_Resume}恢复录制，重新进入AVRECORDER_STARTED状态。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或暂停失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Pause(OH_AVRecorder *recorder);

/**
 * @brief 恢复录制。必须在{@link OH_AVRecorder_Pause}之后调用，调用成功之后进入AVRECORDER_STARTED状态。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或恢复失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Resume(OH_AVRecorder *recorder);

/**
 * @brief 停止录制。必须在{@link OH_AVRecorder_Start}之后调用，调用成功之后进入AVRECORDER_STOPPED状态。
 * 纯音频录制时，需要重新调用{@link OH_AVRecorder_Prepare}接口才能重新录制。
 * 纯视频录制、音视频录制时，需要重新调用{@link OH_AVRecorder_Prepare}和{@link OH_AVRecorder_GetInputSurface}接口才能重新录制。
 * 当{@link OH_AVRecorder_FileGenerationMode}枚举设置为系统创建媒体文件时，Stop操作结束后会通过{@link OH_AVRecorder_SetUriCallback}设置的回调函数
 * 将{@link OH_MediaAsset}对象回调给应用。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或停止失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Stop(OH_AVRecorder *recorder);

/**
 * @brief 重置录制状态。必须在非AVRECORDER_RELEASED状态下调用，调用成功之后进入AVRECORDER_IDLE状态。
 * 典型使用场景包括：录制完成后希望重新配置参数进行新一轮录制、录制出错后需要重置到初始状态重新开始等。
 * 纯音频录制时，需要重新调用{@link OH_AVRecorder_Prepare}接口才能重新录制。
 * 纯视频录制、音视频录制时，需要重新调用{@link OH_AVRecorder_Prepare}和{@link OH_AVRecorder_GetInputSurface}接口才能重新录制。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或重置失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Reset(OH_AVRecorder *recorder);

/**
 * @brief 释放录制资源。必须在非AVRECORDER_RELEASED状态下调用，调用成功之后进入AVRECORDER_RELEASED状态。
 * 调用此接口后，recorder内存将释放。应用层需要显式地将recorder指针置空，以避免访问野指针。释放录制资源之后，该OH_AVRecorder实例不能再进行任何操作。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或释放失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Release(OH_AVRecorder *recorder);

/**
 * @brief 获取AVRecorder可用的编码器信息。必须在非AVRECORDER_RELEASED/AVRECORDER_ERROR状态下调用。
 * 典型使用场景包括：应用启动时查询设备支持的编码器、根据可用编码器选择合适的编码格式、在编码器选择界面展示可选列表等。
 * 参数*info必须为nullptr，由框架层统一分配和释放内存，防止内存泄漏或重复释放等问题。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param info 指向OH_AVRecorder_EncoderInfo实例指针的指针，用于获取可用编码器信息数组。传入时*info必须为nullptr，由框架层统一分配和释放内存，防止内存泄漏或重复释放等问题。
 * 调用成功后，*info指向框架层分配的编码器信息数组。
 * @param length 输出参数，用于返回可用编码器数组的元素个数。不可为nullptr，调用成功后，*length的值表示*info数组中编码器信息的数量，与info参数配合使用。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或*info不为nullptr。
 * AV_ERR_NO_MEMORY：内存不足，*info内存分配失败，请释放资源后重试。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_GetAvailableEncoder(OH_AVRecorder *recorder, OH_AVRecorder_EncoderInfo **info,
    int32_t *length);

/**
 * @brief 设置状态变化回调函数，以便应用能够响应AVRecorder生成的状态变化事件。必须在{@link OH_AVRecorder_Start}之前调用。<br>
 * 用户只能设置一个状态变化回调函数，当用户重复设置时，以最后一次设置的回调函数为准。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param callback 状态回调函数，用于接收AVRecorder状态变化事件。当AVRecorder状态发生切换时（如开始录制、暂停录制、停止录制等状态变更）触发此回调。必须为有效的函数指针，不能为nullptr。
 * @param userData 用户自定义数据指针，将在状态变化回调函数被触发时传递给回调函数，供应用层使用。不需要传递自定义数据时，可传入nullptr。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或回调函数为nullptr。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_SetStateCallback(
    OH_AVRecorder *recorder, OH_AVRecorder_OnStateChange callback, void *userData);

/**
 * @brief 设置错误回调函数，以便应用能够响应AVRecorder生成的错误事件。必须在{@link OH_AVRecorder_Start}之前调用。<br>
 * 用户只能设置一个错误回调函数，当用户重复设置时，以最后一次设置的回调函数为准。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param callback 错误回调函数，用于接收AVRecorder错误事件。当录制过程中发生错误时（如编码器异常、文件写入失败等）触发此回调。必须为有效的函数指针，不能为nullptr。
 * @param userData 用户自定义数据指针，将在错误回调函数被触发时传递给回调函数，供应用层使用。不需要传递自定义数据时，可传入nullptr。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或回调函数为nullptr。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_SetErrorCallback(OH_AVRecorder *recorder, OH_AVRecorder_OnError callback, void *userData);

/**
 * @brief 设置URI回调函数。当{@link OH_AVRecorder_FileGenerationMode}枚举设置为系统创建媒体文件时，
 * 此回调会在{@link OH_AVRecorder_Stop}操作结束后触发，将{@link OH_MediaAsset}对象回调给应用。
 * 典型使用场景包括：录制完成后获取输出文件的URI路径用于文件分享或展示、根据URI更新应用内的文件列表等。
 * 必须在{@link OH_AVRecorder_Start}之前调用。用户只能设置一个URI回调函数，当用户重复设置时，以最后一次设置的回调函数为准。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param callback URI回调函数，用于接收系统创建的资源文件。需在录制配置中将FileGenerationMode设置为系统创建媒体文件模式，录制完成后才会触发此回调。必须为有效的函数指针，不能为nullptr。
 * @param userData 用户自定义数据指针，将在URI回调函数被触发时传递给回调函数，供应用层使用。不需要传递自定义数据时，可传入nullptr。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或回调函数为nullptr。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_SetUriCallback(OH_AVRecorder *recorder, OH_AVRecorder_OnUri callback, void *userData);

/**
 * @brief 设置是否开启静音打断模式，用于控制音频流被打断时的处理行为。设置成true表示音频流被打断时录制静音，设置成false表示音频流被打断时停止录制，默认值为false。
 * 典型使用场景包括：在会议录制等需要持续录制内容的场景中开启静音打断模式，来电打断时保持静音录制以避免丢失后续内容；在普通录音场景中关闭静音打断模式，打断时直接停止录制以节省存储空间。
 * 必须在{@link OH_AVRecorder_Prepare}之前调用。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param muteWhenInterrupted 是否开启静音打断模式。true表示开启静音打断模式，音频流被打断时录制静音；false表示关闭静音打断模式，音频流被打断时停止录制，默认值为false。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr。
 * AV_ERR_INVALID_STATE：函数不支持在当前状态下调用，应当在{@link OH_AVRecorder_Prepare}之前调用。
 * @since 20
 */
OH_AVErrCode OH_AVRecorder_SetWillMuteWhenInterrupted(OH_AVRecorder *recorder, bool muteWhenInterrupted);

/**
 * @brief 获取当前音频最大振幅，典型使用场景包括：音频录制时实时显示音量级别、音频波形可视化、检测录制是否处于静音状态等。
 * 获取到的值为最近两次调用之间的最大振幅。例如，在1s时获取过一次最大振幅，然后在2s时再次调用该接口，那么返回值是1s到2s之间的最大振幅值。
 * 必须在{@link OH_AVRecorder_Prepare}和{@link OH_AVRecorder_Stop}之间调用。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param amplitude 输出参数，用于返回获取到的音频最大振幅值，表示最近两次调用之间音频信号的最大振幅。不可为nullptr，否则返回AV_ERR_INVALID_VAL。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的参数recorder或amplitude为nullptr。
 * AV_ERR_INVALID_STATE：不支持在当前状态下调用，应当在OH_AVRecorder_Prepare之后和OH_AVRecorder_Stop之前调用此接口。
 * AV_ERR_NO_MEMORY：内存不足。
 * AV_ERR_UNKNOWN：未知错误。
 * @since 26.0.0
 */
OH_AVErrCode OH_AVRecorder_GetAudioCapturerMaxAmplitude(OH_AVRecorder *recorder, int32_t* amplitude);

/**
 * @brief 设置录制的元数据信息。典型使用场景包括：在录制的视频或音频文件中添加作者信息、版权信息、地理位置、录制时间等自定义元数据。
 * 如果metadata参数与config.metadata.customInfo（参考{@link OH_AVRecorder_Prepare}和{@link OH_AVRecorder_Config}）中存在相同的键，
 * 前者的对应值将覆盖后者的对应值。
 * 必须在{@link OH_AVRecorder_Prepare}和{@link OH_AVRecorder_Stop}之间调用。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param metadata 设置的元数据信息，会嵌入到录制的媒体文件中。不可为nullptr，否则返回AV_ERR_INVALID_VAL。
 * 格式为字符串键值对，其中，键需要以"com.openharmony."开头，否则该键值对将被忽略；值的长度不能超过256个字节，否则返回AV_ERR_INVALID_VAL。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的参数recorder或metadata为nullptr，或者metadata中的值长度超过256字节。
 * AV_ERR_INVALID_STATE：不支持在当前状态下调用，应当在OH_AVRecorder_Prepare之后和OH_AVRecorder_Stop之前调用此接口。
 * AV_ERR_NO_MEMORY：内存不足。
 * AV_ERR_UNKNOWN：未知错误。
 * @since 26.0.0
 */
OH_AVErrCode OH_AVRecorder_SetMetadata(OH_AVRecorder *recorder, const OH_AVFormat *metadata);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_PLAYER_FRAMEWORK_NATIVE_AVRECORDER_H
