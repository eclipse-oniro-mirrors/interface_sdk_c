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
 * @brief 声明音频配件管理器相关接口。\n
 *
 * 该文件接口用于管理音频配件的创建、连接、断开和销毁等功能。
 *
 * @library libohaudio.so
 * @syscap SystemCapability.Multimedia.Audio.Core
 * @kit AudioKit
 * @include <ohaudio/native_audio_accessory_manager.h>
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
 * <b>触发时机：</b>当系统请求更改配件的降噪模式时触发。
 * 此回调可以在配件连接后的任意时间被调用。
 *
 * @param accessory 音频配件。
 * @param mode 要在配件上设置的降噪模式。
 * @return true：请求的模式处理成功。\n
 *         false：请求的模式处理失败。
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessory_SetNoiseReductionCallback)(
    OH_AudioAccessory *accessory, OH_AudioNoiseReductionMode mode);

/**
 * @brief 获取音频配件管理器实例。\n
 *
 * @param outManager 返回管理器句柄指针。该句柄由系统管理，调用方不得释放，否则可能导致异常。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数outManager为空。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioManager_GetAccessoryManager(
    OH_AudioAccessoryManager **outManager);

/**
 * @brief 创建输入音频配件实例并注册其能力。\n
 *
 * 此函数仅创建音频配件实例，不会立即创建任何输入流。\n
 *
 * 框架会对accessoryName、manufacturer、modelNumber和macAddress字段进行深拷贝，
 * 调用方可在此函数返回后释放这些缓冲区。
 * 框架也会对capabilities中的streamProperties数组进行深拷贝，
 * 调用方可在此函数返回后释放该数组。\n
 *
 * 成功时，框架分配{@link OH_AudioAccessory}句柄并通过accessory指针返回。\n
 *
 * 输入流由框架延迟创建，当应用实际开始从该配件录音时，框架会创建新的
 * {@link OH_AudioAccessoryInputStream}句柄并调用打开输入流回调。
 * 回调接收新创建的流句柄和请求的流信息，调用方必须在回调中注册必需的流回调。\n
 *
 * 流句柄由框架管理，调用方不得释放。流在框架调用
 * {@link OH_AudioAccessoryInputStream_ReleaseCallback}之前保持有效。
 * 释放回调返回后，流句柄变为无效，不得继续使用。
 * 在一个配件句柄的生命周期内，输入流可能被创建和释放多次。
 *
 * @param manager 音频配件管理器指针。
 * @param info 配件基本信息指针，不可为空。
 * @param capabilities 配件能力指针，不可为空。
 * @param openInputStream 框架打开输入流时调用的回调函数，不可为空。
 *     此回调仅在框架为该配件创建流时调用，而非在调用此函数时调用。
 * @param outOwnedAccessory 返回创建的配件句柄。
 * @release 若配件已连接，需先调用{@link OH_AudioAccessoryManager_Disconnected}断开配件，
 *     再调用{@link OH_AudioAccessoryManager_Destroy}销毁配件句柄。
 *     销毁成功后，配件句柄变为无效，不得继续使用。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：任意参数为空。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：管理器未初始化。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_CreateInput(
    OH_AudioAccessoryManager *manager,
    const OH_AudioAccessoryInfo *info,
    const OH_AudioAccessoryCapabilities *capabilities,
    OH_AudioAccessory_OpenInputStreamCallback openInputStream,
    OH_AudioAccessory **outOwnedAccessory);

/**
 * @brief 设置音频配件的关联MAC地址列表。\n
 *
 * 此接口替换与配件实例关联的现有MAC地址列表，用于多发射器场景（如1对2、1对4系统），
 * 其中连接的发射器组可能动态变化。在配件创建后调用此接口报告与主MAC关联的当前所有活动发射器。
 * 如果发射器被替换或断开连接，使用更新后的列表再次调用此接口以覆盖之前的状态。
 * 在活跃录音会话期间可安全调用此接口。
 *
 * @param manager 音频配件管理器指针。
 * @param accessory 配件句柄指针。
 * @param macAddresses 要关联的MAC地址数组。\n
 *     <b>当count为0时可以为空</b>，表示清除所有关联的MAC地址（例如所有辅助发射器断开连接时）。
 *     如果不为空，框架会对这些字符串进行深拷贝。
 *     每个元素必须符合以下规则：\n
 *     - 必须是以冒号分隔的十六进制表示的NUL终止ASCII字符串，例如"00:11:22:33:44:55"。
 *       接受大写和小写十六进制数字（A-F / a-f）。\n
 *     - 必须为非空、非零长度字符串。\n
 *     - 同一数组中的重复地址将被忽略，仅每个唯一地址的首次出现生效。
 * @param count MAC地址数组中的元素数量。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数无效。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：配件未创建。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_SetAssociatedMacAddresses(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory,
    const char **macAddresses,
    uint32_t count);

/**
 * @brief 注册音频配件的降噪能力。\n
 *
 * 框架会对supportedModes数组及能力结构体中的其他字段进行深拷贝，
 * 调用方可在此函数返回后释放能力结构体和supportedModes数组。
 *
 * @param manager 音频配件管理器指针。
 * @param accessory 通过CreateInput创建的配件句柄指针。
 * @param capability 降噪能力指针，不可为空。
 * @param onNoiseReduction 框架请求降噪模式变更时调用的回调函数。
 *     如果配件不支持动态模式切换，可以为空。
 *     如果提供，回调必须在成功时返回true，失败时返回false。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数无效。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：配件未创建。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_RegisterNoiseReductionCapability(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory,
    const OH_AudioAccessoryNoiseReductionCapability *capability,
    OH_AudioAccessory_SetNoiseReductionCallback onNoiseReduction);

/**
 * @brief 设置音频配件的降噪模式。\n
 *
 * 此函数允许配件服务主动将当前降噪模式同步给框架，
 * 通常在通过其他方式（如硬件按钮或配套应用）更改模式时使用，
 * 确保框架保持与配件实际状态的同步。
 *
 * @param manager 音频配件管理器指针。
 * @param accessory 配件句柄指针。
 * @param mode 要设置的降噪模式。必须是通过RegisterNoiseReductionCapability注册的模式之一。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数无效。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：配件未连接。\n
 *         AUDIOCOMMON_RESULT_ERROR_UNSUPPORTED：不支持该模式。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_SetNoiseReductionMode(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory,
    OH_AudioNoiseReductionMode mode);

/**
 * @brief 将音频配件连接到音频框架。\n
 *
 * 调用此函数前，必须注册所有必需的能力。\n
 *
 * <b>建议：</b>建议第三方音频配件优先与智慧生活应用集成，
 * 以确保设备发现和连接用户体验的一致性，使配件服务无需直接管理权限。
 *
 * @permission ohos.permission.MANAGE_AUDIO_ACCESSORY
 * @param manager 音频配件管理器指针。
 * @param accessory 要连接的配件句柄指针。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_PERMISSION_DENIED：调用方没有所需权限。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数accessory为空。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：能力未注册或配件已连接。\n
 *         AUDIOCOMMON_RESULT_ERROR_SYSTEM：音频服务进程死亡。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_Connected(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory);

/**
 * @brief 将音频配件从音频框架断开连接。
 *
 * @permission ohos.permission.MANAGE_AUDIO_ACCESSORY
 * @param manager 音频配件管理器指针。
 * @param accessory 要断开连接的配件句柄指针。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_PERMISSION_DENIED：调用方没有所需权限。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数accessory为空。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：配件未连接。\n
 *         AUDIOCOMMON_RESULT_ERROR_SYSTEM：音频服务进程死亡。
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_Disconnected(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory);

/**
 * @brief 销毁音频配件实例。\n
 *
 * 销毁前必须先断开配件连接。
 *
 * @param manager 音频配件管理器指针。
 * @param accessory 要销毁的配件句柄指针。
 * @return AUDIOCOMMON_RESULT_SUCCESS：函数执行成功。\n
 *         AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM：参数accessory为空。\n
 *         AUDIOCOMMON_RESULT_ERROR_ILLEGAL_STATE：配件仍处于连接状态。
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
