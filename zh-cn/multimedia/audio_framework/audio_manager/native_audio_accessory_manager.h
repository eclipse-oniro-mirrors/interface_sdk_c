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
 * @brief 提供音频模块C接口定义。
 *
 * @syscap SystemCapability.Multimedia.Audio.Core
 *
 * @since 26.0.0
 */

/**
 * @file native_audio_accessory_manager.h
 *
 * @brief 声明音频配件管理相关的接口。
 *
 * 该文件接口用于管理音频配件的创建、连接、断开和销毁等功能。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @since 26.0.0
 */
#ifndef NATIVE_AUDIO_ACCESSORY_MANAGER_H
#define NATIVE_AUDIO_ACCESSORY_MANAGER_H

#include <stdbool.h>
#include "native_audio_accessory_input_stream_manager.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 音频配件降噪模式变更回调函数。
 *
 * <b>触发时机：</b>当配件的降噪模式发生变更时触发，此回调可以在配件连接后的任意时间触发。
 *
 * @param accessory [in] 音频配件。
 * @param mode [in] 配件当前的降噪模式。
 * @return <ul>
 *         <li>true：请求的降噪模式处理成功。</li>
 *         <li>false：请求的降噪模式处理失败。</li>
 *         </ul>
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessory_SetNoiseReductionCallback)(
    OH_AudioAccessory *accessory, OH_AudioNoiseReductionMode mode);

/**
 * @brief 获取音频配件管理器实例。
 *
 * @param outManager [out] 指向OH_AudioAccessoryManager指针的地址。该指针地址由系统管理，调用方不得释放，否则可能导致使用异常。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS}：函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}：参数outManager为NULL。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioManager_GetAccessoryManager(
    OH_AudioAccessoryManager **outManager);

/**
 * @brief 创建音频配件实例并注册其能力。
 *
 * 此函数仅用于创建音频配件实例，不会创建任何输入流。
 * 函数执行成功时，系统通过outOwnedAccessory指针返回创建好的{@link OH_AudioAccessory}句柄。
 * 当应用请求从该音频配件采集音频时，系统会触发openInputStream回调函数。
 * 在一个音频配件的生命周期内，输入流可能被创建和释放多次。
 *
 * @param manager [in] 指向通过{@link OH_AudioManager_GetAccessoryManager}获取的音频配件管理器实例。
 * @param info [in] 指向配件基本信息的指针，不可为NULL。
 * @param capabilities [in] 指向配件能力的指针，不可为NULL。
 * @param openInputStream [in] 音频配件打开输入流的回调函数，不可为NULL。
 *     此回调仅在应用请求从该音频配件采集音频时调用，而非在调用此函数时调用。
 * @param outOwnedAccessory [out] 指向OH_AudioAccessory指针的地址，用于接收创建好的音频配件实例。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS}：函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}：参数无效，包括info为NULL、capabilities为NULL、
 *             openInputStream为NULL、outOwnedAccessory为NULL、info信息未全部填写、
 *             capabilities信息未全部填写，或outOwnedAccessory已通过
 *             {@link OH_AudioAccessoryManager_CreateInput}创建。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}：参数manager未通过
 *             {@link OH_AudioManager_GetAccessoryManager}进行初始化。</li>
 *         </ul>
 * @release native_audio_accessory_manager/OH_AudioAccessoryManager_Destroy {outOwnedAccessory}
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_CreateInput(
    OH_AudioAccessoryManager *manager,
    const OH_AudioAccessoryInfo *info,
    const OH_AudioAccessoryCapabilities *capabilities,
    OH_AudioAccessory_OpenInputStreamCallback openInputStream,
    OH_AudioAccessory **outOwnedAccessory);

/**
 * @brief 设置与主音频配件组合使用的副配件MAC地址列表。
 *
 * 此函数适用于多配件组合场景（如二合一、四合一），支持动态管理配件组合：
 * - 初始化：配件创建后，调用此接口设置初始副配件列表。
 * - 动态更新：副配件替换或断开连接时，调用此接口覆盖旧的MAC列表
 * - 线程安全：录音期间可安全调用。
 * - 限制：此接口仅用于更新副配件MAC地址列表，不用于更新主配件MAC地址。
 *   主配件断开连接或主配件MAC地址变化时，应先断开并销毁原有配件句柄，再使用新的主配件信息重新创建配件实例。
 *
 * @param manager [in] 指向通过{@link OH_AudioManager_GetAccessoryManager}获取的音频配件管理器实例。
 * @param accessory [in] 指向主配件句柄的指针。
 * @param macAddresses [in] 副配件MAC地址数组。
 *     <b>当count为0时可以为空</b>，表示清除副配件MAC列表（例如所有副配件断开连接时）。
 *     每个元素必须符合以下规则：
 *     - 必须是以冒号分隔的十六进制表示的NUL终止ASCII字符串，例如"00:11:22:33:44:55"。
 *       接受大写和小写十六进制数字（A-F / a-f）。
 *     - 必须为非空、非零长度字符串。
 *     - 同一数组中的重复地址将被忽略，仅每个唯一地址的首次出现生效。
 * @param count [in] MAC地址数组中的元素数量。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS}：函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}：参数无效，包括manager为NULL、
 *             manager未通过{@link OH_AudioManager_GetAccessoryManager}进行初始化、accessory为NULL，
 *             或macAddresses传入的个数与count不一致。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}：参数accessory未通过
 *             {@link OH_AudioAccessoryManager_CreateInput}创建。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_SetAssociatedMacAddresses(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory,
    const char **macAddresses,
    uint32_t count);

/**
 * @brief 注册音频配件的降噪能力。
 *
 * @param manager [in] 指向通过{@link OH_AudioManager_GetAccessoryManager}获取的音频配件管理器实例。
 * @param accessory [in] 指向通过{@link OH_AudioAccessoryManager_CreateInput}获取的音频配件实例。
 * @param capability [in] 指向降噪能力的指针，不可为NULL。
 * @param onNoiseReduction [in] 音频配件的降噪模式发生变更时调用的回调函数。
 *     如果配件不支持动态模式切换，可以为NULL。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS}：函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}：参数无效，包括manager为NULL、
 *             manager未通过{@link OH_AudioManager_GetAccessoryManager}进行初始化、accessory为NULL、
 *             capability为NULL，或capability中的supportedModes为NULL或supportedModeCount为0。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}：参数accessory未通过
 *             {@link OH_AudioAccessoryManager_CreateInput}创建。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_RegisterNoiseReductionCapability(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory,
    const OH_AudioAccessoryNoiseReductionCapability *capability,
    OH_AudioAccessory_SetNoiseReductionCallback onNoiseReduction);

/**
 * @brief 设置音频配件的降噪模式。
 *
 * 此函数由配件关联的服务或应用来调用，它更新配件当前降噪模式到系统，
 * 通常在通过其他方式（如硬件按钮或配套应用）更改降噪模式时使用，
 * 以确保系统侧的降噪模式与配件实际降噪模式保持一致。
 *
 * @param manager [in] 指向通过{@link OH_AudioManager_GetAccessoryManager}获取的音频配件管理器实例。
 * @param accessory [in] 指向通过{@link OH_AudioAccessoryManager_CreateInput}获取的音频配件实例。
 * @param mode [in] 要设置的降噪模式。必须是通过RegisterNoiseReductionCapability注册的模式之一。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS}：函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}：参数accessory为NULL。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}：参数accessory未通过
 *             {@link OH_AudioAccessoryManager_CreateInput}创建，或未通过
 *             {@link OH_AudioAccessoryManager_Connected}连接。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_UNSUPPORTED}：设置的降噪模式未通过
 *             {@link OH_AudioAccessoryManager_RegisterNoiseReductionCapability}注册。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_SetNoiseReductionMode(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory,
    OH_AudioNoiseReductionMode mode);

/**
 * @brief 将音频配件连接到音频系统。
 *
 * 调用此函数前，必须通过{@link OH_AudioManager_GetAccessoryManager}获取的音频配件管理器实例，
 * 并通过{@link OH_AudioAccessoryManager_CreateInput}创建accessory实例。
 *
 * <b>建议：</b>建议音频配件管理程序优先接入智慧生活应用，为用户提供设备发现与连接体验的一致性；
 * 若以独立音频配件管理应用方式，需要申请ACL权限ohos.permission.MANAGE_AUDIO_ACCESSORY
 *
 * @permission ohos.permission.MANAGE_AUDIO_ACCESSORY
 * @param manager [in] 指向通过{@link OH_AudioManager_GetAccessoryManager}获取的音频配件管理器实例。
 * @param accessory [in] 指向通过{@link OH_AudioAccessoryManager_CreateInput}获取的音频配件实例。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS}：函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_PERMISSION_DENIED}：调用方没有
 *             ohos.permission.MANAGE_AUDIO_ACCESSORY权限。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}：参数无效，包括manager为NULL、
 *             manager未通过{@link OH_AudioManager_GetAccessoryManager}进行初始化，或accessory为NULL。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}：参数accessory未通过
 *             {@link OH_AudioAccessoryManager_CreateInput}创建，或accessory已通过
 *             {@link OH_AudioAccessoryManager_Connected}连接。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}：音频服务进程死亡。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_Connected(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory);

/**
 * @brief 将音频配件从音频系统断开连接。
 *
 * @permission ohos.permission.MANAGE_AUDIO_ACCESSORY
 * @param manager [in] 指向通过{@link OH_AudioManager_GetAccessoryManager}获取的音频配件管理器实例。
 * @param accessory [in] 指向通过{@link OH_AudioAccessoryManager_CreateInput}获取的音频配件实例。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS}：函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_PERMISSION_DENIED}：调用方没有
 *             ohos.permission.MANAGE_AUDIO_ACCESSORY权限。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}：参数accessory为NULL。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}：参数accessory未通过
 *             {@link OH_AudioAccessoryManager_Connected}连接。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}：音频服务进程死亡。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_Disconnected(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory);

/**
 * @brief 销毁音频配件实例。
 *
 * 销毁前必须先断开配件连接。
 *
 * @param manager [in] 指向通过{@link OH_AudioManager_GetAccessoryManager}获取的音频配件管理器实例。
 * @param accessory [in] 指向通过{@link OH_AudioAccessoryManager_CreateInput}获取的音频配件实例。
 * @return <ul>
 *         <li>{@link AUDIOCOMMON_RESULT_SUCCESS}：函数执行成功。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}：参数无效，包括manager为NULL、
 *             manager未通过{@link OH_AudioManager_GetAccessoryManager}进行初始化，或accessory为NULL。</li>
 *         <li>{@link AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE}：参数accessory未通过
 *             {@link OH_AudioAccessoryManager_Disconnected}断开连接。</li>
 *         </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_Destroy(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // NATIVE_AUDIO_ACCESSORY_MANAGER_H
