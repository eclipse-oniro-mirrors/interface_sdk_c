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
 * @brief Provides APIs of request capability for Recorder.
 *
 * @syscap SystemCapability.Multimedia.Media.AVRecorder
 * @since 18
 * @}
 */
/**
 * @file avrecorder.h
 *
 * @brief 定义AVRecorder接口。应用可使用媒体AVRecorder提供的接口录制媒体数据。
 * 
 * @kit MediaKit
 * @library libavrecorder.so
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
 * @brief 创建AVRecorder实例。调用成功之后进入AVRECORDER_IDLE状态。
 * 
 * @return 成功时返回指向OH_AVRecorder实例的指针，失败时返回nullptr。
 * @since 18
*/
OH_AVRecorder *OH_AVRecorder_Create(void);

/**
 * @brief 配置AVRecorder参数，准备录制。必须在{@link OH_AVRecorder_Create}成功触发之后调用，调用成功之后进入AVRECORDER_PREPARED状态。
 * 若只录制音频，则无需配置视频相关参数；同理，若只录制视频，则无需配置音频相关参数。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param config 指向OH_AVRecorder_Config实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或者准备失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Prepare(OH_AVRecorder *recorder, OH_AVRecorder_Config *config);

/**
 * @brief 获取当前的录制参数。此接口必须在录制准备完成后调用。
 * 传入的*config必须为nullptr，由框架层统一分配和释放内存，以避免内存管理混乱，防止内存泄漏或重复释放等问题。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param config 指向OH_AVRecorder_Config实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或\*config不为nullptr。
 * AV_ERR_NO_MEMORY：内存不足，\*config内存分配失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_GetAVRecorderConfig(OH_AVRecorder *recorder, OH_AVRecorder_Config **config);

/**
 * @brief 获取输入Surface。必须在{@link OH_AVRecorder_Prepare}成功触发之后，{@link OH_AVRecorder_Start}之前调用。
 * 此Surface提供给调用者，调用者从此Surface中获取Surface Buffer，填入相应的视频数据。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param window 指向OHNativeWindow实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_GetInputSurface(OH_AVRecorder *recorder, OHNativeWindow **window);

/**
 * @brief 更新视频旋转角度。必须在{@link OH_AVRecorder_Prepare}成功触发之后，{@link OH_AVRecorder_Start}之前调用。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param rotation 视频旋转角度，必须是整数 [0, 90, 180, 270] 中的一个。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或输入的rotation不符合要求或更新方向失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_UpdateRotation(OH_AVRecorder *recorder, int32_t rotation);

/**
 * @brief 开始录制。必须在{@link OH_AVRecorder_Prepare}成功触发之后调用，调用成功之后进入AVRECORDER_STARTED状态。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或启动失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Start(OH_AVRecorder *recorder);

/**
 * @brief 暂停录制。必须在{@link OH_AVRecorder_Start}成功触发之后，处于AVRECORDER_STARTED状态时调用，调用成功之后进入AVRECORDER_PAUSED状态。
 * 之后可以通过调用{@link OH_AVRecorder_Resume}恢复录制，重新进入AVRECORDER_STARTED状态。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或暂停失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Pause(OH_AVRecorder *recorder);

/**
 * @brief 恢复录制。必须在{@link OH_AVRecorder_Pause}成功触发之后，处于PAUSED状态时调用，调用成功之后重新进入AVRECORDER_STARTED状态。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或恢复失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Resume(OH_AVRecorder *recorder);

/**
 * @brief 停止录制。必须在{@link OH_AVRecorder_Start}成功触发之后调用，调用成功之后进入AVRECORDER_STOPPED状态。
 * 纯音频录制时，需要重新调用{@link OH_AVRecorder_Prepare}接口才能重新录制。
 * 纯视频录制、音视频录制时，需要重新调用{@link OH_AVRecorder_Prepare}和{@link OH_AVRecorder_GetInputSurface}接口才能重新录制。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或停止失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Stop(OH_AVRecorder *recorder);

/**
 * @brief 重置录制状态。必须在非AVRECORDER_RELEASED状态下调用，调用成功之后进入AVRECORDER_IDLE状态。
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
 * @brief 释放录制资源。调用成功之后进入AVRECORDER_RELEASED状态。
 * 调用此接口释放录制资源后，recorder内存将释放，应用层需要显式地将recorder指针置空，避免访问野指针。释放音视频录制资源之后，该OH_AVRecorder实例不能再进行任何操作。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或释放失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_Release(OH_AVRecorder *recorder);

/**
 * @brief 获取AVRecorder可用的编码器和编码器信息。
 * 参数*info必须为nullptr，由框架层统一分配和释放内存，以避免内存管理混乱，防止内存泄漏或重复释放等问题。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param info 指向OH_AVRecorder_EncoderInfo实例的指针。
 * @param length 可用编码器的长度。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的 recorder 为nullptr。
 * AV_ERR_NO_MEMORY：内存不足，\*info内存分配失败。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_GetAvailableEncoder(OH_AVRecorder *recorder, OH_AVRecorder_EncoderInfo **info,
    int32_t *length);

/**
 * @brief 设置状态回调函数，以便应用能够响应AVRecorder生成的状态变化事件。此接口必须在{@link OH_AVRecorder_Start}调用之前调用。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param callback 状态回调函数。
 * @param userData 指向用户特定数据的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或回调函数为nullptr。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_SetStateCallback(
    OH_AVRecorder *recorder, OH_AVRecorder_OnStateChange callback, void *userData);

/**
 * @brief 设置错误回调函数，以便应用能够响应AVRecorder生成的错误事件。此接口必须在{@link OH_AVRecorder_Start}调用之前调用。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param callback 错误回调函数。
 * @param userData 指向用户特定数据的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或回调函数为nullptr。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_SetErrorCallback(OH_AVRecorder *recorder, OH_AVRecorder_OnError callback, void *userData);

/**
 * @brief 设置URI回调函数，以便应用能够响应AVRecorder生成的URI事件。此接口必须在{@link OH_AVRecorder_Start}调用之前调用。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param callback URI回调函数。
 * @param userData 指向用户特定数据的指针。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或回调函数为nullptr。
 * @since 18
 */
OH_AVErrCode OH_AVRecorder_SetUriCallback(OH_AVRecorder *recorder, OH_AVRecorder_OnUri callback, void *userData);

/**
 * @brief 设置是否开启静音打断模式。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param muteWhenInterrupted 设置是否开启静音打断模式。设置成true表示当应用需要录制时保持静音而不是被打断，设置成false表示应用录制打断时停止录音而不是保持静音。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的recorder为nullptr或回调函数为nullptr。
 * AV_ERR_INVALID_STATE：函数在无效状态下调用，应先处于准备状态。
 * @since 20
 */
OH_AVErrCode OH_AVRecorder_SetWillMuteWhenInterrupted(OH_AVRecorder *recorder, bool muteWhenInterrupted);

/**
 * @brief 获取当前音频最大振幅。获取到的值为最近两次调用之间的最大振幅。例如，在1s时获取过一次最大振幅，然后在2s时再次调用该方法，那么返回值是1s到2s之间的最大振幅值。
 * 该方法只能在{@link OH_AVRecorder_Prepare}方法调用之后，且必须在{@link OH_AVRecorder_Stop}方法之前调用。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param amplitude 获取到的音频最大振幅。
 * @return AV_ERR_OK：执行成功。
 * AV_ERR_INVALID_VAL：输入的参数recorder或amplitude为nullptr。
 * AV_ERR_INVALID_STATE：不支持在当前状态下调用，应当在OH_AVRecorder_Prepare之后和OH_AVRecorder_Stop之前调用此接口。
 * AV_ERR_NO_MEMORY：内存不足。
 * AV_ERR_UNKNOWN：未知错误。
 * @since 26.0.0
 */
OH_AVErrCode OH_AVRecorder_GetAudioCapturerMaxAmplitude(OH_AVRecorder *recorder, int32_t* amplitude);

/**
 * @brief 设置录制的元数据信息。如果metadata参数与config.metadata.customInfo（参考{@link OH_AVRecorder_Prepare}和{@link OH_AVRecorder_Config}
 * ）中存在相同的键，前者的对应值将覆盖后者。
 * 该方法只能在OH_AVRecorder_Prepare方法调用之后，且必须在{@link OH_AVRecorder_Stop}方法之前调用。
 * 
 * @param recorder 指向OH_AVRecorder实例的指针。
 * @param metadata 设置的元数据信息。格式为字符串键值对，其中，键需要以"com.openharmony."开头，且值的长度不能超过256个字节。
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
