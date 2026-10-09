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
 * @brief 本文件提供音频路由管理功能的接口。
 * <br>音频系统会为每个音频流选择默认的输入输出设备。对于音频播放流，系统会根据播放流的{@link OH_AudioStream_Usage}，在可用的输出设备中选择；对于音频录制流，系统会根据录制流的
 * {@link OH_AudioStream_SourceType}，在可用的输入设备中选择。
 * <br>本文件提供的接口，支持开发者查询在线设备，监听设备在线状态变化，查询首选输入或输出设备，监听首选设备变化，查询麦克风堵塞状态等。当前并不提供主动选择设备的能力。
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
 * @brief 声明音频路由管理结构体，该结构体用于调用音频设备和路由信息查询功能接口。
 *
 * @since 12
 */
typedef struct OH_AudioRoutingManager OH_AudioRoutingManager;

/**
 * @brief 音频设备在线状态变化回调函数的原型定义，用于{@link OH_AudioRoutingManager_RegisterDeviceChangeCallback}和
 * {@link OH_AudioRoutingManager_UnregisterDeviceChangeCallback}接口。
 * <br>可能存在多个音频设备同时发生状态变化。
 *
 * @param type 设备连接状态，连接或断开。
 * @param audioDeviceDescriptorArray 发生状态变化的音频设备描述符数组。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，在不使用时释放所有内存。
 * @since 12
 */
typedef int32_t (*OH_AudioRoutingManager_OnDeviceChangedCallback) (
    OH_AudioDevice_ChangeType type,
    OH_AudioDeviceDescriptorArray *audioDeviceDescriptorArray
);

/**
 * @brief 首选输出设备变化回调函数的原型定义，用于{@link OH_AudioRoutingManager_RegisterPreferredOutputDevicesChangeCallback}和
 * {@link OH_AudioRoutingManager_UnregisterPreferredOutputDevicesChangeCallback}接口。
 * <br>首选设备可以是多个音频输出设备。
 *
 * @param audioDeviceDescriptorArray 变化后的首选音频输出设备描述符数组。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，在不使用时释放所有内存。
 * @since 26.0.0
 */
typedef int32_t (*OH_AudioRoutingManager_OnPreferredOutputDeviceChangedCallback) (
    OH_AudioDeviceDescriptorArray *audioDeviceDescriptorArray);

/**
 * @brief 首选输入设备变化回调函数的原型定义，用于{@link OH_AudioRoutingManager_RegisterPreferredInputDevicesChangeCallback}和
 * {@link OH_AudioRoutingManager_UnregisterPreferredInputDevicesChangeCallback}接口。
 * <br>首选设备可以是多个音频输入设备。
 *
 * @param audioDeviceDescriptorArray 变化后的首选音频输入设备描述符数组。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，在不使用时释放所有内存。
 * @since 26.0.0
 */
typedef int32_t (*OH_AudioRoutingManager_OnPreferredInputDeviceChangedCallback) (
    OH_AudioDeviceDescriptorArray *audioDeviceDescriptorArray);

/**
 * @brief 获取音频路由管理器实例，该实例为单例，用于调用音频设备状态和路由变化查询功能接口。
 *
 * @param audioRoutingManager [out] 指向OH_AudioRoutingManager指针的地址，用于接收获取的音频路由管理器实例。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         </ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioManager_GetAudioRoutingManager(OH_AudioRoutingManager **audioRoutingManager);

/**
 * @brief 查询在线的音频设备，支持按照输入输出维度查询。
 * <br>在线设备包括内置的音频设备和连接的外设。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param deviceFlag [in] 音频设备标志，用于过滤输入或输出设备。
 * @param audioDeviceDescriptorArray [out] 音频设备描述符数组。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，在不使用时释放所有内存。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1. 参数audioRoutingManager为空指针；2. 参数deviceFlag无效；3. 参数audioDeviceDescriptorArray为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_NO_MEMORY} 内存不足。</li>
 *         </ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_GetDevices(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioDevice_Flag deviceFlag,
    OH_AudioDeviceDescriptorArray **audioDeviceDescriptorArray);

/**
 * @brief 查询指定场景的可用音频设备，支持按照设备使用场景和输入输出维度查询。
 * <br>音频系统会根据使用场景选择不同的输入输出设备，主要分为媒体和通话场景。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param deviceUsage [in] 要查询设备的使用场景和输入输出类型。
 * @param audioDeviceDescriptorArray [out] 可用音频设备的描述符数组。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，在不使用时释放所有内存。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1. 参数audioRoutingManager为空指针；2. 参数deviceUsage无效；3. 参数audioDeviceDescriptorArray为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_NO_MEMORY} 内存不足。</li>
 *         </ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_GetAvailableDevices(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioDevice_Usage deviceUsage, OH_AudioDeviceDescriptorArray **audioDeviceDescriptorArray);

/**
 * @brief 查询首选音频输出设备。
 * <br>音频系统会根据播放流的{@link OH_AudioStream_Usage}确定不同的首选输出设备。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param streamUsage [in] 用于确定首选设备的音频播放流使用场景。
 * @param audioDeviceDescriptorArray [out] 首选音频输出设备描述符数组。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，在不使用时释放所有内存。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1. 参数audioRoutingManager为空指针；2. 参数streamUsage无效；3. 参数audioDeviceDescriptorArray为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_NO_MEMORY} 内存不足。</li>
 *         </ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_GetPreferredOutputDevice(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioStream_Usage streamUsage, OH_AudioDeviceDescriptorArray **audioDeviceDescriptorArray);

/**
 * @brief 查询首选音频输入设备。
 * <br>音频系统会根据录制流的{@link OH_AudioStream_SourceType}确定不同的首选输入设备。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param sourceType [in] 用于确定首选设备的音频录制流使用场景。
 * @param audioDeviceDescriptorArray [out] 首选音频输入设备描述符数组。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，在不使用时释放所有内存。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1. 参数audioRoutingManager为空指针；2. 参数sourceType无效；3. 参数audioDeviceDescriptorArray为空指针。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_NO_MEMORY} 内存不足。</li>
 *         </ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_GetPreferredInputDevice(OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioStream_SourceType sourceType, OH_AudioDeviceDescriptorArray **audioDeviceDescriptorArray);
/**
 * @brief 注册音频在线设备变化回调。
 * <br>当音频外设连接和断连时，系统会触发此回调。
 * <br>为避免资源浪费或其他异常情况，当应用程序不再需要此回调时，必须通过调用{@link OH_AudioRoutingManager_UnregisterDeviceChangeCallback} 来释放回调。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param deviceFlag [in] 音频设备标志，用来筛选输入输出。
 * @param callback [in] 音频设备在线状态变化回调函数指针。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1. 参数audioRoutingManager为空指针；2. 参数deviceFlag无效；3. 参数callback为空指针。</li>
 *         </ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_RegisterDeviceChangeCallback(
    OH_AudioRoutingManager *audioRoutingManager, OH_AudioDevice_Flag deviceFlag,
    OH_AudioRoutingManager_OnDeviceChangedCallback callback);

/**
 * @brief 取消通过{@link OH_AudioRoutingManager_RegisterDeviceChangeCallback}注册的音频在线设备变化回调。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param callback [in] 已注册的音频设备在线状态变化回调函数指针，用于取消。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1. 参数audioRoutingManager为空指针；2. 参数callback为空指针。</li>
 *         </ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_UnregisterDeviceChangeCallback(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioRoutingManager_OnDeviceChangedCallback callback);

/**
 * @brief 注册音频首选输出设备变化回调。
 * <br>当指定播放流使用场景类型的首选输出设备发生变化时，系统会触发此回调。
 * <br>音频系统会根据播放流的{@link OH_AudioStream_Usage}确定不同的首选输出设备。
 * <br>为避免资源浪费或其他异常情况，当应用程序不再需要此回调时，必须通过调用{@link OH_AudioRoutingManager_UnregisterPreferredOutputDevicesChangeCallback}
 * 来释放回调。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param streamUsage [in] 用于确定首选设备的音频播放流使用场景。
 * @param callback [in] 指向OH_AudioRoutingManager_OnPreferredOutputDeviceChangedCallback，用于接收首选输出设备变化事件。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数校验失败。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 音频客户端在调用音频服务的过程中遇到系统错误，导致调用失败。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioRoutingManager_RegisterPreferredOutputDevicesChangeCallback(
    OH_AudioRoutingManager *audioRoutingManager, OH_AudioStream_Usage streamUsage,
    OH_AudioRoutingManager_OnPreferredOutputDeviceChangedCallback callback);

/**
 * @brief 取消通过{@link OH_AudioRoutingManager_RegisterPreferredOutputDevicesChangeCallback} 注册的音频首选输出设备变化回调。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param callback [in] 已注册的音频首选输出设备变化回调函数指针，用于取消。传入空指针时，系统将取消所有已注册的首选输出设备变化回调。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数校验失败。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 音频客户端在调用音频服务的过程中遇到系统错误，导致调用失败。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioRoutingManager_UnregisterPreferredOutputDevicesChangeCallback(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioRoutingManager_OnPreferredOutputDeviceChangedCallback callback);

/**
 * @brief 注册音频首选输入设备变化回调。
 * <br>当指定录制流使用场景类型的首选输入设备发生变化时，系统会触发此回调。
 * <br>音频系统会根据录制流的{@link OH_AudioStream_SourceType}确定不同的首选输入设备。
 * <br>为避免资源浪费或其他异常情况，当应用程序不再需要此回调时，必须通过调用{@link OH_AudioRoutingManager_UnregisterPreferredInputDevicesChangeCallback}
 * 来释放回调。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param sourceType [in] 用于确定首选设备的音频录制流使用场景。
 * @param callback [in] 指向OH_AudioRoutingManager_OnPreferredInputDeviceChangedCallback，用于接收首选输入设备变化事件。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数校验失败。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 音频客户端在调用音频服务的过程中遇到系统错误，导致调用失败。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioRoutingManager_RegisterPreferredInputDevicesChangeCallback(
    OH_AudioRoutingManager *audioRoutingManager, OH_AudioStream_SourceType sourceType,
    OH_AudioRoutingManager_OnPreferredInputDeviceChangedCallback callback);

/**
 * @brief 取消通过{@link OH_AudioRoutingManager_RegisterPreferredInputDevicesChangeCallback} 注册的音频首选输入设备变更回调。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param callback [in] 已注册的音频首选输入设备变化回调函数指针，用于取消。传入空指针时，系统将取消所有已注册的首选输入设备变化回调。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 参数校验失败。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM} 音频客户端在调用音频服务的过程中遇到系统错误，导致调用失败。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioRoutingManager_UnregisterPreferredInputDevicesChangeCallback(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioRoutingManager_OnPreferredInputDeviceChangedCallback callback);

/**
 * @brief 释放音频设备描述符数组对象。
 * <br>音频路由管理的查询和监听接口，返回的OH_AudioDeviceDescriptorArray均由系统侧申请内存。
 * 开发者不应通过free或delete释放OH_AudioDeviceDescriptorArray指针指向的内存，而需要调用此接口释放。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param audioDeviceDescriptorArray [in] 待释放的音频设备描述符数组。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1. 参数audioRoutingManager为空指针；2. 参数audioDeviceDescriptorArray为空指针。</li>
 *         </ul>
 * @since 12
 */
OH_AudioCommon_Result OH_AudioRoutingManager_ReleaseDevices(
    OH_AudioRoutingManager *audioRoutingManager,
    OH_AudioDeviceDescriptorArray *audioDeviceDescriptorArray);

/**
 * @brief 音频设备堵塞状态变化回调函数的原型定义，用于{@link OH_AudioRoutingManager_SetMicBlockStatusCallback}接口。
 *
 * @param audioDeviceDescriptorArray 发生状态变化的音频设备描述符数组。
 *     <br>不要单独释放此指针指向的内存，而是调用{@link OH_AudioRoutingManager_ReleaseDevices}，在不使用时释放所有内存。
 * @param status 音频设备的堵塞状态。
 * @param userData 指向开发者在{@link OH_AudioRoutingManager_SetMicBlockStatusCallback}接口传入的userData数据。
 * @since 13
 */
typedef void (*OH_AudioRoutingManager_OnDeviceBlockStatusCallback)(
    OH_AudioDeviceDescriptorArray *audioDeviceDescriptorArray,
    OH_AudioDevice_BlockStatus status,
    void *userData);

/**
 * @brief 查询当前设备是否支持麦克风堵塞状态检测。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param supported [out] 获取当前设备是否支持麦克风堵塞状态检测的结果。true表示支持，false表示不支持。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1. 参数audioRoutingManager为空指针；2. 参数supported为空指针。</li>
 *         </ul>
 * @since 13
 */
OH_AudioCommon_Result OH_AudioRoutingManager_IsMicBlockDetectionSupported(
    OH_AudioRoutingManager *audioRoutingManager,
    bool *supported);

/**
 * @brief 设置麦克风是否堵塞状态回调。
 * <br>当应用正在使用麦克风录音，此场景下麦克风堵塞状态发生变化，系统才会触发此回调。
 * <br>在使用此功能之前，应通过{@link OH_AudioRoutingManager_IsMicBlockDetectionSupported}查询当前设备是否支持检测。
 * <br>目前此检测功能仅支持本地设备的内置麦克风。
 *
 * @param audioRoutingManager [in] 指向通过{@link OH_AudioManager_GetAudioRoutingManager}获取的音频路由管理器实例。
 * @param callback [in] 用于接受麦克风堵塞状态变化事件的回调函数。
 * @param userData [in] 用户自定义数据指针，回调函数触发时会携带。若无需传递数据，可传入空指针。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS} 函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM} 1. 参数audioRoutingManager为空指针；2. 参数callback为空指针。</li>
 *         </ul>
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