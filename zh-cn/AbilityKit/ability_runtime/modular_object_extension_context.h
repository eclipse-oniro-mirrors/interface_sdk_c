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
 * @addtogroup AbilityRuntime
 * @{
 *
 * @brief 提供ModularObjectExtensionAbility上下文的C接口定义。
 *
 * @since 26.0.0
 */

/**
 * @file modular_object_extension_context.h
 *
 * @brief 声明ModularObjectExtensionAbility的上下文接口，包括启动UIAbility、销毁ModularObjectExtensionAbility自身、创建和销毁IPC对象等功能。
 *
 * @library libability_runtime.so
 * @kit AbilityKit
 * @syscap SystemCapability.Ability.AbilityRuntime.Core
 * @since 26.0.0
 */

#ifndef ABILITY_RUNTIME_MODULAR_OBJECT_EXTENSION_CONTEXT_H
#define ABILITY_RUNTIME_MODULAR_OBJECT_EXTENSION_CONTEXT_H

#include "AbilityKit/ability_base/want.h"
#include "ability_runtime_common.h"
#include "context.h"
#include "IPCKit/ipc_cremote_object.h"
#include "start_options.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 表示ModularObjectExtensionAbility上下文的句柄。
 *
 * @since 26.0.0
 */
typedef struct OH_AbilityRuntime_ModularObjectExtensionContext* OH_AbilityRuntime_ModObjExtensionContextHandle;

/**
 * @brief 从ModularObjectExtensionAbility上下文中获取基础上下文。
 *
 * @param modObjExtensionContext 指向ModularObjectExtensionAbility上下文的指针。
 * @param baseContext 指向{@link AbilityRuntime_ContextHandle}的指针，用于接收结果。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} 参数校验失败。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjExtensionContext_GetBaseContext(
    OH_AbilityRuntime_ModObjExtensionContextHandle modObjExtensionContext, AbilityRuntime_ContextHandle* baseContext);

/**
 * @brief 启动当前应用的UIAbility。
 *
 * @permission ohos.permission.NDK_START_SELF_UI_ABILITY
 * @param context 指向ModularObjectExtensionAbility上下文的指针。
 * @param want 启动当前应用UIAbility时需要的Want信息。详细内容参考{@link AbilityBase_Want}。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PERMISSION_DENIED} 调用方无正确权限。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} 传入参数无效。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED} 设备不支持启动当前应用的UIAbility。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_SUCH_ABILITY} 目标Ability不存在。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE} Ability类型不正确。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_CROWDTEST_EXPIRED} 众测应用已过期。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_WUKONG_MODE} 无法在Wukong模式下启动Ability。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_CONTROLLED} 应用被管控。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_EDM_CONTROLLED} 应用被EDM管控。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_CROSS_APP} 调用方尝试启动不同应用。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NOT_TOP_ABILITY} 调用方进程不在前台。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_MULTI_APP_NOT_SUPPORTED} 不支持应用分身和多实例。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INVALID_APP_INSTANCE_KEY} 应用实例Key无效。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_UPPER_LIMIT_REACHED} 应用实例数量已达上限。
 *     <br>{@link ABILITY_RUNTIME_ERROR_MULTI_INSTANCE_NOT_SUPPORTED} 不支持应用多实例。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_APP_INSTANCE_KEY_NOT_SUPPORTED} 不允许设置APP_INSTANCE_KEY。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjExtensionContext_StartSelfUIAbility(
    OH_AbilityRuntime_ModObjExtensionContextHandle context, const AbilityBase_Want *want);

/**
 * @brief 通过StartOptions启动当前应用的UIAbility。
 *
 * @permission ohos.permission.NDK_START_SELF_UI_ABILITY
 * @param context 指向ModularObjectExtensionAbility上下文的指针。
 * @param want 启动当前应用UIAbility时需要的Want信息。详细内容参考{@link AbilityBase_Want}。
 * @param options 启动当前应用UIAbility时需要的StartOptions信息。详细内容参考{@link AbilityRuntime_StartOptions}。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PERMISSION_DENIED} 调用方无正确权限。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} 传入参数无效。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NOT_SUPPORTED} 设备不支持启动当前应用的UIAbility。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_SUCH_ABILITY} 目标Ability不存在。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INCORRECT_ABILITY_TYPE} Ability类型不正确。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_CROWDTEST_EXPIRED} 众测应用已过期。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_WUKONG_MODE} 无法在Wukong模式下启动Ability。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_CONTROLLED} 应用被管控。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_EDM_CONTROLLED} 应用被EDM管控。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_CROSS_APP} 调用方尝试启动不同应用。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NOT_TOP_ABILITY} 调用方非前台进程。
 *     <br>{@link ABILITY_RUNTIME_ERROR_VISIBILITY_SETTING_DISABLED} 可见性设置已禁用。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_MULTI_APP_NOT_SUPPORTED} 不支持应用分身和多实例。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INVALID_APP_INSTANCE_KEY} 应用实例Key无效。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_UPPER_LIMIT_REACHED} 应用实例数量已达上限。
 *     <br>{@link ABILITY_RUNTIME_ERROR_MULTI_INSTANCE_NOT_SUPPORTED} 不支持应用多实例。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_APP_INSTANCE_KEY_NOT_SUPPORTED} 不允许设置APP_INSTANCE_KEY。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjExtensionContext_StartSelfUIAbilityWithStartOptions(
    OH_AbilityRuntime_ModObjExtensionContextHandle context, const AbilityBase_Want *want,
    const AbilityRuntime_StartOptions *options);

/**
 * @brief 销毁ModularObjectExtensionAbility自身。
 *
 * @param context 指向ModularObjectExtensionAbility上下文的指针。
 * @return 返回特定的错误码。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_NO_ERROR} 接口调用成功。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_PARAM_INVALID} 传入参数无效。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_WUKONG_MODE} 无法在Wukong模式下销毁Ability。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_CONTEXT_NOT_EXIST} 上下文不存在。
 *     <br>{@link ABILITY_RUNTIME_ERROR_CODE_INTERNAL} 内部错误。
 * @since 26.0.0
 */
AbilityRuntime_ErrorCode OH_AbilityRuntime_ModObjExtensionContext_TerminateSelf(
    OH_AbilityRuntime_ModObjExtensionContextHandle context);

/**
 * @brief 创建一个OHIPCRemoteStub对象，回调函数将在ExtensionAbility指定的线程上运行。requestCallback和destroyCallback将在由ExtensionAbility的
 * {@link OH_AbilityRuntime_ThreadMode}决定的线程上按顺序执行。调用
 * {@link OH_AbilityRuntime_ModObjExtensionContext_DestroyIPCRemoteStub}后，不会再有新的requestCallback回调，
 * 且正在执行的requestCallback完成后才会回调destroyCallback。调用方需调用
 * {@link OH_AbilityRuntime_ModObjExtensionContext_DestroyIPCRemoteStub}销毁返回的对象，避免内存泄漏。
 *
 * @param context 指向ModularObjectExtensionAbility上下文的指针。
 * @param descriptor 指向待创建的OHIPCRemoteStub对象描述符的指针，不能为NULL。创建过程中会内部拷贝该字符串，调用方可在本函数返回后释放该描述符。
 * @param requestCallback 处理数据请求的回调函数，不能为NULL。
 * @param destroyCallback 对象销毁时调用的回调函数，可以为NULL。
 * @param userData 指向用户数据的指针，可以为NULL，须在对象销毁前保持有效。
 * @return 操作成功时返回创建的OHIPCRemoteStub对象指针；否则返回NULL。
 * @since 26.0.0
 */
OHIPCRemoteStub* OH_AbilityRuntime_ModObjExtensionContext_CreateIPCRemoteStub(
    OH_AbilityRuntime_ModObjExtensionContextHandle context, const char *descriptor,
    OH_OnRemoteRequestCallback requestCallback, OH_OnRemoteDestroyCallback destroyCallback, void *userData);

/**
 * @brief 销毁OHIPCRemoteStub对象。
 *
 * @param context 指向ModularObjectExtensionAbility上下文的指针。
 * @param stub 指向待销毁的OHIPCRemoteStub对象的指针。
 * @since 26.0.0
 */
void OH_AbilityRuntime_ModObjExtensionContext_DestroyIPCRemoteStub(
    OH_AbilityRuntime_ModObjExtensionContextHandle context, OHIPCRemoteStub *stub);

#ifdef __cplusplus
}
#endif

/** @} */
#endif // ABILITY_RUNTIME_MODULAR_OBJECT_EXTENSION_CONTEXT_H
