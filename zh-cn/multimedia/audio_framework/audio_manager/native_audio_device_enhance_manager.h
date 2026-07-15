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
 * @addtogroup OHAudio
 * @{
 *
 * @brief Provide the definition of the C interface for the audio module.
 *
 * @since 26.0.0
 */

/**
 * @file native_audio_device_enhance_manager.h
 *
 * @brief 声明音频设备增强管理器相关接口。本文件中的接口用于获取OH_AudioDeviceEnhanceManager句柄，为应用或音频流切换输入输出设备，以及执行其他与音频设备或路由相关的增强功能。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 26.0.0
 */

#ifndef NATIVE_AUDIO_DEVICE_ENHANCE_MANAGER_H
#define NATIVE_AUDIO_DEVICE_ENHANCE_MANAGER_H

#include "native_audio_device_base.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义音频设备增强管理器的句柄类型，音频设备增强管理功能，用于应用级音频设备选择及流维度音频设备选择。
 *
 * @since 26.0.0
 */
typedef struct OH_AudioDeviceEnhanceManager OH_AudioDeviceEnhanceManager;

/**
 * @brief 获取音频设备增强管理器句柄。
 *
 * @param audioDeviceEnhanceManager 指向OH_AudioDeviceEnhanceManager句柄的指针，用于接收函数返回的管理器实例。
 * @return AUDIOCOMMON_RESULT_SUCCESS: 函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM: 参数audioDeviceEnhanceManager为nullptr。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioDeviceEnhanceManager(
    OH_AudioDeviceEnhanceManager **audioDeviceEnhanceManager);

/**
 * @brief 查询系统是否支持当前管理器提供的增强路由功能。
 *
 * @param audioDeviceEnhanceManager 通过{@link OH_AudioManager_GetAudioDeviceEnhanceManager}获取的音频设备增强管理器句柄。
 * @param supported 查询结果，即系统是否支持音频设备增强管理功能。true表示支持，false表示不支持。
 * @return AUDIOCOMMON_RESULT_SUCCESS: 函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM: 参数audioDeviceEnhanceManager或supported为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM: 音频客户端调用音频服务失败或系统错误。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDeviceEnhanceManager_IsEnhancedRoutingSupported(
    OH_AudioDeviceEnhanceManager *audioDeviceEnhanceManager, bool *supported);

/**
 * @brief 为应用选择输出设备。
 *
 * @param audioDeviceEnhanceManager 通过{@link OH_AudioManager_GetAudioDeviceEnhanceManager}获取的音频设备增强管理器句柄。
 * @param deviceDescriptor 目标设备。可用设备需从{@link OH_AudioRoutingManager_GetAvailableDevices}返回的设备列表中获取。传入nullptr时，
 *     系统会清除上一次选择，并为应用恢复默认输出设备。
 * @return AUDIOCOMMON_RESULT_SUCCESS: 函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM: 参数audioDeviceEnhanceManager为nullptr，
 *     <br>参数deviceDescriptor无效或指定输出设备已离线。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM: 音频客户端调用音频服务失败或系统错误。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDeviceEnhanceManager_SelectOutputDevice(
    OH_AudioDeviceEnhanceManager *audioDeviceEnhanceManager, OH_AudioDeviceDescriptor *deviceDescriptor);

/**
 * @brief 为应用选择输入设备。
 *
 * @param audioDeviceEnhanceManager 通过{@link OH_AudioManager_GetAudioDeviceEnhanceManager}获取的音频设备增强管理器句柄。
 * @param deviceDescriptor 目标设备。可用设备需从{@link OH_AudioRoutingManager_GetAvailableDevices}返回的设备列表中获取。传入nullptr时，
 *     系统会清除上一次选择，并为应用恢复默认输入设备。
 * @return AUDIOCOMMON_RESULT_SUCCESS: 函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM: 参数audioDeviceEnhanceManager为nullptr，
 *     <br>参数deviceDescriptor无效或指定输入设备已离线。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM: 音频客户端调用音频服务失败或系统错误。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDeviceEnhanceManager_SelectInputDevice(
    OH_AudioDeviceEnhanceManager *audioDeviceEnhanceManager, OH_AudioDeviceDescriptor *deviceDescriptor);

/**
 * @brief 为指定音频播放流选择输出设备。
 *
 * @param audioDeviceEnhanceManager 通过{@link OH_AudioManager_GetAudioDeviceEnhanceManager}获取的音频设备增强管理器句柄。
 * @param renderer 通过{@link OH_AudioStreamBuilder_GenerateRenderer}创建的音频播放流实例。
 * @param deviceDescriptor 目标设备。可用设备需从{@link OH_AudioRoutingManager_GetAvailableDevices}返回的设备列表中获取。传入nullptr时，
 *     系统会清除上一次选择，并为该音频播放流恢复默认输出设备。
 * @return AUDIOCOMMON_RESULT_SUCCESS: 函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM: 参数audioDeviceEnhanceManager或renderer为nullptr，
 *     <br>参数deviceDescriptor无效或指定输出设备已离线。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM: 音频客户端调用音频服务失败或系统错误。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDeviceEnhanceManager_SelectOutputDeviceForAudioRenderer(
    OH_AudioDeviceEnhanceManager *audioDeviceEnhanceManager, OH_AudioRenderer *renderer,
    OH_AudioDeviceDescriptor *deviceDescriptor);

/**
 * @brief 为指定音频录制流选择输入设备。
 *
 * @param audioDeviceEnhanceManager 通过{@link OH_AudioManager_GetAudioDeviceEnhanceManager}获取的音频设备增强管理器句柄。
 * @param capturer 通过{@link OH_AudioStreamBuilder_GenerateCapturer}创建的音频录制流实例。
 * @param deviceDescriptor 目标设备。可用设备需从{@link OH_AudioRoutingManager_GetAvailableDevices}返回的设备列表中获取。传入nullptr时，
 *     系统会清除上一次选择，并为该音频录制流恢复默认输入设备。
 * @return AUDIOCOMMON_RESULT_SUCCESS: 函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM: 参数audioDeviceEnhanceManager或capturer为nullptr，
 *     <br>参数deviceDescriptor无效或指定输入设备已离线。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM: 音频客户端调用音频服务失败或系统错误。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioDeviceEnhanceManager_SelectInputDeviceForAudioCapturer(
    OH_AudioDeviceEnhanceManager *audioDeviceEnhanceManager, OH_AudioCapturer *capturer,
    OH_AudioDeviceDescriptor *deviceDescriptor);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_DEVICE_ENHANCE_MANAGER_H
/** @} */