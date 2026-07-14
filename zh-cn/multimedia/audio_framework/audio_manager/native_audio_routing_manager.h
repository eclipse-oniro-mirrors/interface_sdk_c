/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @since 12
 * @version 1.0
 */

/**
 * @file native_audio_routing_manager.h
 *
 * @brief 声明与音频路由管理器相关的接口。
 * <br>包含用于创建audioRoutingManager，设备连接状态发生变化时的注册和注销功能，以及存储设备信息的指针数组的释放。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 12
 * @version 1.0
 */

#ifndef NATIVE_AUDIO_ROUTING_MANAGER_H
#define NATIVE_AUDIO_ROUTING_MANAGER_H

#include <stdbool.h>
#include "native_audio_device_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 声明音频路由管理器，用于路由和设备相关功能的音频路由管理器的句柄。
 *
 * @since 12
 */
typedef struct OH_AudioRoutingManager OH_AudioRoutingManager;

/**
 * @brief 此函数指针将指向用于返回更改的音频设备描述符的回调函数，可能返回多个音频设备描述符。
 *
 * @param type 设备连接状态类型。 {@link OH_AudioDevice_ChangeType}已连接或断开。
 * @param audioDeviceDescriptorArray 音频设备描述符数组，指向{@link OH_AudioDeviceDescriptorArray}设置音频设备描述符值的指针变量，
 *     不要单独释放audioDeviceDescriptorArray指针，而是调用{@link OH_AudioRoutingManager_ReleaseDevices} 来释放DeviceDescriptor数组。
 * @since 12
 */
typedef int32_t (*OH_AudioRoutingManager_OnDeviceChangedCallback) (
    OH_AudioDevice_ChangeType type,
    OH_AudioDeviceDescriptorArray *audioDeviceDescriptorArray
);

/**
 * @brief 此函数指针指向用于返回优先级最高的输出设备描述符的回调函数，该回调函数会返回一个或多个音频设备描述符。
 *
 * @param audioDeviceDescriptorArray 音频设备描述符数组。
 *     <br>设置音频设备描述符值的指针变量，不能单独释放audioDeviceDescriptorArray指针，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}
 *     来释放DeviceDescriptor数组。
 * @since 26.0.0
 */
typedef int32_t (*OH_AudioRoutingManager_OnPreferredOutputDeviceChangedCallback) (
    OH_AudioDeviceDescriptorArray *audioDeviceDescriptorArray);

/**
 * @brief 此函数指针指向用于返回优先级最高的输入设备描述符的回调函数，该回调函数会返回一个或多个音频设备描述符。
 *
 * @param audioDeviceDescriptorArray 音频设备描述符数组。
 *     <br>设置音频设备描述符值的指针变量，不能单独释放audioDeviceDescriptorArray指针，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}
 *     来释放DeviceDescriptor数组。
 * @since 26.0.0
 */
typedef int32_t (*OH_AudioRoutingManager_OnPreferredInputDeviceChangedCallback) (
    OH_AudioDeviceDescriptorArray *audioDeviceDescriptorArray);

/**
 * @brief 查询音频路由管理器句柄，该句柄应设置为路由相关函数中的第一个参数。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取句柄。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioRoutingManager(OH_AudioRoutingManager **audioRoutingManager);

/**
 * @brief 根据输入的deviceFlag查询可用的设备。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取句柄。
 * @param deviceFlag 音频设备标志，用于选择目标设备的滤波器参数。
 * @param audioDeviceDescriptorArray 音频设备描述符数组。设置音频设备描述符值的指针变量，不要单独释放audioDeviceDescriptorArray指针，而是调用
 *     {@link OH_AudioRoutingManager_ReleaseDevices}来释放DeviceDescriptor数组。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioRoutingManager为nullptr；
 *     <br>2. 参数deviceFlag无效；
 *     <br>3. 参数audioDeviceDescriptorArray为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_NO_MEMORY：内存不足。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_GetDevices(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioDevice_Flag deviceFlag,
    OH_AudioDeviceDescriptorArray **audioDeviceDescriptorArray);

/**
 * @brief 获取音频可选设备列表。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取句柄。
 * @param deviceUsage 指向{@link OH_AudioDevice_Usage}用于设置要获取的设备种类。
 * @param audioDeviceDescriptorArray 音频设备描述符数组。设置音频设备描述符值的指针变量，不要单独释放audioDeviceDescriptorArray指针，而是调用
 *     {@link OH_AudioRoutingManager_ReleaseDevices}来释放DeviceDescriptor数组。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1.参数audioRoutingManager为nullptr；
 *     <br>2.参数deviceUsage无效;
 *     <br>3.参数audioDeviceDescriptorArray为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_NO_MEMORY：内存不足。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_GetAvailableDevices(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioDevice_Usage deviceUsage, OH_AudioDeviceDescriptorArray **audioDeviceDescriptorArray);

/**
 * @brief 根据音频输出流的使用场景，获取优先级最高的输出设备。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取句柄。
 * @param streamUsage 指向{@link OH_AudioStream_Usage}用于设置音频输出流的使用场景。
 * @param audioDeviceDescriptorArray 音频设备描述符数组。设置音频设备描述符值的指针变量，不要单独释放audioDeviceDescriptorArray指针，而是调用
 *     {@link OH_AudioRoutingManager_ReleaseDevices}来释放DeviceDescriptor数组。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1.参数audioRoutingManager为nullptr;
 *     <br>2.参数streamUsage无效;
 *     <br>3.参数audioDeviceDescriptorArray为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_NO_MEMORY：内存不足。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_GetPreferredOutputDevice(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioStream_Usage streamUsage, OH_AudioDeviceDescriptorArray **audioDeviceDescriptorArray);

/**
 * @brief 根据音频输入流的使用场景，获取优先级最高的输入设备。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取句柄。
 * @param sourceType 指向{@link OH_AudioStream_SourceType}用于设置音频输入流的使用场景。
 * @param audioDeviceDescriptorArray 音频设备描述符数组。设置音频设备描述符值的指针变量，不要单独释放audioDeviceDescriptorArray指针，而是调用
 *     {@link OH_AudioRoutingManager_ReleaseDevices}来释放DeviceDescriptor数组。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1.参数audioRoutingManager为nullptr;
 *     <br>2.参数sourceType无效;
 *     <br>3.参数audioDeviceDescriptorArray为nullptr。
 *     <br>AUDIOCOMMON_RESULT_ERROR_NO_MEMORY：内存不足。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_GetPreferredInputDevice(OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioStream_SourceType sourceType, OH_AudioDeviceDescriptorArray **audioDeviceDescriptorArray);
/**
 * @brief 注册音频路由管理器的设备更改回调。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取句柄。
 * @param deviceFlag 音频设备标志，用来注册回调。
 * @param callback 函数指针将指向用于返回更改的音频设备描述符的回调函数。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioRoutingManager为nullptr；
 *     <br>2. 参数deviceFlag无效；
 *     <br>3. 参数callback为nullptr。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_RegisterDeviceChangeCallback(
    OH_AudioRoutingManager *audioRoutingManager, OH_AudioDevice_Flag deviceFlag,
    OH_AudioRoutingManager_OnDeviceChangedCallback callback);

/**
 * @brief 取消注册音频路由管理器的设备更改回调。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取句柄。
 * @param callback 函数指针将指向用于返回更改的音频设备描述符的回调函数。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioRoutingManager为nullptr；
 *     <br>2. 参数callback为nullptr。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_UnregisterDeviceChangeCallback(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioRoutingManager_OnDeviceChangedCallback callback);

/**
 * @brief 注册音频路由管理器的最高优先级输出设备变更回调。当指定播放流类型的最高优先级输出设备发生变化时，已注册的客户端将收到回调。
 * <br>为避免资源浪费或其他异常情况，当应用程序不再需要此回调时，必须通过调用{@link OH_AudioRoutingManager_UnregisterPreferredOutputDevicesChangeCallback}
 * 来释放回调。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取。
 * @param streamUsage 指向OH_AudioStream_Usage，用于注册最高优先级输出设备变化事件的过滤参数设置。
 * @param callback 指向OH_AudioRoutingManager_OnPreferredOutputDeviceChangedCallback，用于接收最高优先级输出设备变化事件。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数校验失败。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：音频客户端在调用音频服务的过程中遇到系统错误，导致调用失败。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioRoutingManager_RegisterPreferredOutputDevicesChangeCallback(
    OH_AudioRoutingManager *audioRoutingManager, OH_AudioStream_Usage streamUsage,
    OH_AudioRoutingManager_OnPreferredOutputDeviceChangedCallback callback);

/**
 * @brief 取消通过{@link OH_AudioRoutingManager_RegisterPreferredOutputDevicesChangeCallback} 注册的音频路由管理器最高优先级输出设备变更回调。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取。
 * @param callback 指向OH_AudioRoutingManager_OnPreferredOutputDeviceChangedCallback，用于接收最高优先级输出设备变化事件。传入nullptr时，
 *     系统将取消所有已注册的最高优先级输出设备变化回调。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数校验失败。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：音频客户端在调用音频服务的过程中遇到系统错误，导致调用失败。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioRoutingManager_UnregisterPreferredOutputDevicesChangeCallback(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioRoutingManager_OnPreferredOutputDeviceChangedCallback callback);

/**
 * @brief 注册音频路由管理器的最高优先级输入设备变更回调。当指定播放流类型的最高优先级输入设备发生变化时，已注册的客户端将收到回调。
 * <br>为避免资源浪费或其他异常情况，当应用程序不再需要此回调时，必须通过调用{@link OH_AudioRoutingManager_UnregisterPreferredInputDevicesChangeCallback}
 * 来释放回调。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取。
 * @param sourceType 指向OH_AudioStream_SourceType，用于注册最高优先级输入设备变化事件的过滤参数设置。
 * @param callback 指向OH_AudioRoutingManager_OnPreferredInputDeviceChangedCallback，用于接收最高优先级输入设备变化事件。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数校验失败。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：音频客户端在调用音频服务的过程中遇到系统错误，导致调用失败。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioRoutingManager_RegisterPreferredInputDevicesChangeCallback(
    OH_AudioRoutingManager *audioRoutingManager, OH_AudioStream_SourceType sourceType,
    OH_AudioRoutingManager_OnPreferredInputDeviceChangedCallback callback);

/**
 * @brief 取消通过{@link OH_AudioRoutingManager_RegisterPreferredInputDevicesChangeCallback} 注册的音频路由管理器最高优先级输入设备变更回调。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取。
 * @param callback 指向OH_AudioRoutingManager_OnPreferredInputDeviceChangedCallback，用于接收最高优先级输入设备变化事件。传入nullptr时，
 *     系统将取消所有已注册的最高优先级输入设备变化回调。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数校验失败。
 *     <br>AUDIOCOMMON_RESULT_ERROR_SYSTEM：音频客户端在调用音频服务的过程中遇到系统错误，导致调用失败。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioRoutingManager_UnregisterPreferredInputDevicesChangeCallback(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioRoutingManager_OnPreferredInputDeviceChangedCallback callback);

/**
 * @brief 释放音频设备描述符数组对象。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取句柄。
 * @param audioDeviceDescriptorArray 音频设备描述符数组应当被释放，获取请调用{@link OH_AudioRoutingManager_GetDevices}接口。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1. 参数audioRoutingManager为nullptr；
 *     <br>2. 参数audioDeviceDescriptorArray为nullptr。
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_ReleaseDevices(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioDeviceDescriptorArray *audioDeviceDescriptorArray);

/**
 * @brief 此函数指针将指向用于返回音频设备堵塞状态的回调函数，可能返回多个音频设备描述符。
 *
 * @param audioDeviceDescriptorArray 音频设备描述符数组应当被释放，获取请调用{@link OH_AudioRoutingManager_GetDevices}接口。设置音频设备描述符值的指针变量，
 *     不要单独释放audioDeviceDescriptorArray指针，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}来释放DeviceDescriptor数组。
 * @param status 音频设备的堵塞状态。
 * @param userData 用户自定义数据指针。
 * @since 13
 */
typedef void (*OH_AudioRoutingManager_OnDeviceBlockStatusCallback)(
    OH_AudioDeviceDescriptorArray *audioDeviceDescriptorArray,
    OH_AudioDevice_BlockStatus status,
    void *userData);

/**
 * @brief 查询当前设备是否支持麦克风堵塞状态检测。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取句柄。
 * @param supported 查询当前设备是否支持麦克风堵塞状态检测的结果。true表示支持，false表示不支持。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1.参数audioRoutingManager为nullptr；
 *     <br>2.参数supported为nullptr。
 * @since 13
 */
OH_AudioCommon_Result OH_AudioRoutingManager_IsMicBlockDetectionSupported(
    OH_AudioRoutingManager *audioRoutingManager,
    bool *supported);

/**
 * @brief 设置麦克风是否堵塞状态回调。
 * <br>在使用此功能之前，用户应查询当前设备是否支持检测，应用只有在使用麦克风录音时，并且所使用的麦克风的堵塞状态发生改变，才会收到回调，目前此检测功能仅支持麦克风位于本地设备上。
 *
 * @param audioRoutingManager 音频路由管理器句柄。通过{@link OH_AudioManager_GetAudioRoutingManager}获取句柄。
 * @param callback 函数指针将指向用于返回接受设备麦克风堵塞状态{@link OH_AudioRoutingManager_OnDeviceBlockStatusCallback}。
 * @param userData 用户自定义数据指针。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。
 *     <br>AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：
 *     <br>1.参数audioRoutingManager为nullptr；
 *     <br>2.参数callback为nullptr。
 * @since 13
 */
OH_AudioCommon_Result OH_AudioRoutingManager_SetMicBlockStatusCallback(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioRoutingManager_OnDeviceBlockStatusCallback callback,
    void *userData);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AUDIO_ROUTING_MANAGER_H
/** @} */