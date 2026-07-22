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
 * @addtogroup AudioAccessoryManager
 * @{
 *
 * @brief Provide audio accessory manager C interface.
 *
 * @since 26.0.0
 */

/**
 * @file native_audio_accessory_manager.h
 *
 * @brief Declare audio accessory manager related interfaces.
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
 * @brief 配件降噪模式切换回调。
 *
 * <b>When Called:</b>当系统请求更改噪音时
 * 附件上的还原模式。此回调可以在任何时候调用
 * 连接附件后。
 *
 * @param accessory 音频配件。
 * @param mode 要在附件上设置的降噪模式。
 * @return <ul>
 * <li>`true`如果请求的模式处理成功</li>
 * <li>`false`否则。</li>
 * </ul>
 * @since 26.0.0
 */
typedef bool (*OH_AudioAccessory_SetNoiseReductionCallback)(
    OH_AudioAccessory *accessory, OH_AudioNoiseReductionMode mode);

/**
 * @brief 获取音频配件管理器实例。
 *
 * @param outManager 【out】返回指向管理器句柄的指针。
 * 注意句柄由系统管理，不能释放
 * 被调用者调用，否则可能会出现异常。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}如果管理器为空。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioManager_GetAccessoryManager(
    OH_AudioAccessoryManager **outManager);

/**
 * @brief 创建输入音频配件实例并注册其能力。
 *
 * 该函数只创建音频附件实例。它不会创造
 * 任何输入流。
 *
 * 框架会对附件名称、制造商、
 * modelNumber和macAddress字段。调用方可以释放这些缓冲区
 * 在此函数返回后。
 * 该框架还执行streamProperties数组的深拷贝
 * 的能力。调用者可以在此函数返回后释放此数组。
 *
 * 成功后，框架会分配一个{@link OH_AudioAccessory}句柄，
 * 通过辅助指针返回。
 *
 * 输入流是由框架懒创建的，当应用程序
 * 实际上是从这个附件开始录制的。当时，框架
 * 创建一个新的{@link OH_AudioAccessoryInputStream}句柄并调用
 * 开流。回调接收新创建的流句柄
 * 和请求的流信息，并且是调用者必须注册的位置
 * 所需的流回调。
 *
 * 流句柄由框架管理，不能由
 * 调用者。流一直有效，直到框架调用
 * 该流的{@链接OH_AudioAccessoryInputStream_ReleaseCallback}。之后
 * release回调返回，则流句柄无效，不能
 * 被再次使用。在一个辅助句柄的生命周期内，输入流
 * 可以多次创建和释放。
 *
 * @param manager 【in】音频附件管理器指针。
 * @param info 【in】附件基本信息指针。不能为空。
 * @param capabilities 【in】指向附件功能的指针。不能为空。
 * @param openInputStream 【in】当框架打开输入流时调用的回调。
 * 不能为空。只有当框架创建时，才会调用回调
 * 此附件的流，而不是在调用此函数时。
 * @param outOwnedAccessory 【out】返回创建的辅助句柄。
 * @release Call {@link OH_AudioAccessoryManager_Disconnected} to disconnect
 *     the accessory first if it has been connected, and then call
 *     {@link OH_AudioAccessoryManager_Destroy} to destroy the accessory handle.
 *     After a successful destroy, the accessory handle becomes invalid and must
 *     not be used again.
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * <li>如果任何参数为null，则{@link AudioCOMMON_RESULT_ERROR_INVALID_PARAM}。</li>
 * 如果管理器未初始化，则为<li>{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_CreateInput(
    OH_AudioAccessoryManager *manager,
    const OH_AudioAccessoryInfo *info,
    const OH_AudioAccessoryCapabilities *capabilities,
    OH_AudioAccessory_OpenInputStreamCallback openInputStream,
    OH_AudioAccessory **outOwnedAccessory);

/**
 * @brief 设置音频附件的关联MAC地址列表。
 *
 * 此接口替换现有的关联MAC地址列表
 * 链接到附件实例。它设计用于多发射机
 * 场景（例如，1对2、1对4系统），其中连接的组
 * 发射器可能会动态更改。在创建附件后调用此选项
 * 以报告与主MAC关联的所有当前活动的发送器。
 * 如果更换变送器或断开变送器，请使用
 * 更新列表以覆盖先前的状态。在活动期间安全呼叫
 * 录制会话。
 *
 * @param manager 音频配件管理器指针。
 * @param accessory 指向附件句柄的指针。
 * @param macAddresses 要关联的MAC地址数组。
 * <b>Can be null if count is 0</b>，表示所有关联的MAC地址。
 * 应清除（例如，当所有辅助变送器断开时）。
 * 如果不为null，框架将对这些字符串执行深拷贝。
 * @param count 数组中的MAC地址数。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * 如果参数无效，则<li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}。</li>
 * <li>{@link AudioCOMMON_RESULT_ERROR_ILA_STATE}如果未创建配件。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_SetAssociatedMacAddresses(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory,
    const char **macAddresses,
    uint32_t count);

/**
 * @brief 注册音频配件降噪能力。
 *
 * 框架对支持的Modes数组和其他
 * 能力结构中的字段。调用方可以释放该能力
 * 结构，并在此函数返回后返回支持的Modes数组。
 *
 * @param manager 音频配件管理器指针。
 * @param accessory CreateInput创建的辅助句柄指针。
 * @param capability 降噪能力指针。不能为空。
 * @param onNoiseReduction 框架时调用的回调
 * 请求更改降噪模式。如果附件，则可能为空
 * 不支持动态模式切换。如果提供，则回调必须
 * 成功时返回`true`，失败时返回`false`。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * 如果参数无效，则<li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}。</li>
 * <li>{@link AudioCOMMON_RESULT_ERROR_ILA_STATE}如果未创建配件。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_RegisterNoiseReductionCapability(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory,
    const OH_AudioAccessoryNoiseReductionCapability *capability,
    OH_AudioAccessory_SetNoiseReductionCallback onNoiseReduction);

/**
 * @brief 设置音频附件的降噪模式。
 *
 * 该功能允许附件服务主动同步
 * 当前降噪模式为框架。它通常用于
 * 通过其他手段(例如，硬件按钮或
 * )，确保框架与附件保持同步更新
 * 实际状态。
 *
 * @param manager 音频配件管理器指针。
 * @param accessory 指向附件句柄的指针。
 * @param mode 要设置的降噪模式。一定是模式之一
 * 通过RegisterNoiseReduceCapability注册。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * 如果参数无效，则<li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}。</li>
 * <li>{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}如果未连接配件。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_UNSUPPORTED}如果该模式不受支持。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_SetNoiseReductionMode(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory,
    OH_AudioNoiseReductionMode mode);

/**
 * @brief 将音频配件连接到音频框架。
 *
 * 在调用此函数之前，必须注册所有必需的能力。
 *
 * <b>Recommendation:</b>建议第三方音频配件
 * 优先考虑与智慧生活APP的集成。这确保了一致的
 * 设备发现和连接的用户体验，允许附件
 * 服务，避免直接进行权限管理。
 *
 * @permission ohos.permission.MANAGE_AUDIO_ACCESSORY
 * @param manager 音频配件管理器指针。
 * @param accessory 指向要连接的附件句柄的指针。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * <li>{@link AudioCommon_RESULT_ERROR_PERATION_DENIED}如果调用者没有
 * 需要权限。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}如果附件为空。</li>
 * <li>{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}如果功能未注册或
 * 配件已连接。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}如果音频服务器进程已死。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_Connected(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory);

/**
 * @brief 断开音频附件与音频框架的连接。
 *
 * @permission ohos.permission.MANAGE_AUDIO_ACCESSORY
 * @param manager 音频配件管理器指针。
 * @param accessory 指针类型，指向要断开连接的附件句柄。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * <li>{@link AudioCommon_RESULT_ERROR_PERATION_DENIED}如果调用者没有
 * 需要权限。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}如果附件为空。</li>
 * <li>{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}如果未连接配件。</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_SYSTEM}如果音频服务器进程已死。</li>
 * </ul>
 * @since 26.0.0
 */
OH_AudioCommon_Result OH_AudioAccessoryManager_Disconnected(
    OH_AudioAccessoryManager *manager,
    OH_AudioAccessory *accessory);

/**
 * @brief 销毁音频附件实例。
 *
 * 销毁前必须断开附件。
 *
 * @param manager 【in】音频附件管理器指针。
 * @param accessory 【in】指向要销毁的辅助句柄的指针。
 * @return <ul>
 * <li>如果执行成功，则返回</li>
 * <li>{@link AUDIOCOMMON_RESULT_ERROR_INVALID_PARAM}如果附件为空。</li>
 * 如果配件仍处于连接状态，则显示<li>{@link AudioCOMMON_RESULT_ERROR_ILAL_STATE}。</li>
 * </ul>
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