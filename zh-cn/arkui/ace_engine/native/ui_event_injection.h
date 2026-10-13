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
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief 在Native侧提供ArkUI的宽松UI控制能力，适用于应用内智能体和UI自动化场景，
 * 支持注入无需指定具体组件的非精确交互命令。
 *
 * @since 26.2.0
 */

/**
 * @file ui_event_injection.h
 *
 * @brief 声明供应用内智能体和UI自动化使用的接口，用于向UI注入宽松的非精确控制操作。
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @include <arkui/ui_event_injection.h>
 * @library libace_ndk.z.so
 * @kit ArkUI
 * @since 26.2.0
 */

#ifndef ARKUI_NATIVE_UI_EVENT_INJECTION_H
#define ARKUI_NATIVE_UI_EVENT_INJECTION_H

#include <stdint.h>
#include <stddef.h>

#include "common_type.h"
#include "error_code.h"
#include "ui_json_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 枚举UI事件注入的结果码。
 *
 * 所有注入接口共用此枚举，包括宽松交互注入（非精确）和面向指定组件的精确注入。
 * 非零结果码表示执行失败，其具体值表示失败原因。
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief 注入的命令执行成功。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_EVENT_INJECTION_RESULT_SUCCESS = 0,
    /**
     * @brief 未找到能够响应注入命令的组件或目标。
     *
     * 例如，点击坐标未命中任何组件，或无法定位执行模式所需的目标。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_EVENT_INJECTION_RESULT_TARGET_NOT_FOUND = 1,
    /**
     * @brief 当前UI上下文无法执行该命令。
     *
     * 命令结构有效，但当前UI状态不支持该命令的类型或执行模式。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_EVENT_INJECTION_RESULT_COMMAND_NOT_SUPPORTED = 2,
    /**
     * @brief 注入的命令被用户操作中断。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_EVENT_INJECTION_RESULT_INTERRUPTED_BY_USER = 3,
} OH_ArkUI_NativeModule_UIEventInjection_ResultCode;

/**
 * @brief 注入完成回调。
 *
 * 注入的命令执行结束时，无论成功与否，均调用此回调一次。
 *
 * @param result [in] 注入执行的结果码。详情参见
 *     {@link OH_ArkUI_NativeModule_UIEventInjection_ResultCode}。
 * @param userData [in] 注入时传入的自定义用户数据指针。如果注入时传入NULL，则此处为NULL。
 *        所指向数据的类型、所有权和生命周期完全由调用方定义。
 *        框架不会解引用或保留此指针，仅将其传回此回调。
 *        该指针必须在回调被调用之前保持有效。
 * @since 26.2.0
 */
typedef void (*OH_ArkUI_NativeModule_UIEventInjectionCallback)(
    OH_ArkUI_NativeModule_UIEventInjection_ResultCode result, void *userData);

/**
 * @brief 向目标UI节点异步注入控制命令。
 *
 * 目标节点通过唯一ID标识，该ID与OH_ArkUI_NodeUtils_GetNodeHandleByUniqueId使用的ID相同。
 * 框架在uiContext指定的UI实例中，将此唯一ID解析为对应的节点。
 *
 * 命令由通过OH_ArkUI_NativeModule_UIJsonWrapper_Create创建的
 * OH_ArkUI_NativeModule_UIJsonWrapper对象承载。命令内容的顶层结构如下：
 * {"schemaVersion": 1, "cmd": {"type": "<命令类型>", "action_info": { ... }}}
 *
 * 支持的命令类型及其action_info参数请参见开发指南。
 *
 * uniqueId对应的节点必须与uiContext属于同一UI实例。如果节点属于其他实例，
 * 框架将无法在uiContext中解析该节点，并返回ARKUI_ERROR_CODE_PARAM_INVALID。
 *
 * 必须在uiContext指定的UI实例的UI线程上调用此函数。如果在非UI线程上调用，
 * 框架将输出致命错误日志并终止进程。这是为防止跨线程访问UI导致未定义行为而采用的快速失败设计。
 *
 * @param uiContext [in] UI实例指针，不能为NULL。调用方必须在该实例的UI线程上调用；
 *        在其他线程上调用将触发致命错误并终止进程。uniqueId必须能够解析为此实例内的节点。
 * @param uniqueId [in] 目标节点的唯一ID，与OH_ArkUI_NodeUtils_GetNodeHandleByUniqueId使用的ID相同。
 *        框架在uiContext实例中将此ID解析为对应的节点。
 * @param command [in] 已配置的JSON命令对象指针，不能为NULL。
 *        函数返回前会在内部复制JSON数据；调用方保留对象所有权，可在函数返回后立即销毁该对象。
 * @param callback [in] 可选的完成回调。如果无需接收执行结果，可传入NULL。
 *        如果不为NULL，则在UI线程上恰好调用一次。
 * @param userData [in] 传递给回调的自定义用户数据指针，可以为NULL。
 *        如果不为NULL，则必须在回调被调用之前保持有效。框架不会解引用或保留此指针。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 命令成功加入队列。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数无效，包括callback为NULL、缺少必填字段或JSON转换失败。</li>
 *     <li>{@link ARKUI_ERROR_CODE_NODE_NOT_FOUND} uniqueId无法解析为uiContext实例内的节点。</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} UI上下文无效。</li>
 *     <li>{@link ARKUI_ERROR_CODE_COMMAND_UNFINISHED} 当前进程中仍有其他复合命令正在执行；
 *     新命令不会加入队列，也不会调用回调。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIEventInjectCompositeCommand(
    ArkUI_ContextHandle uiContext,
    uint32_t uniqueId,
    const OH_ArkUI_NativeModule_UIJsonWrapper *command,
    OH_ArkUI_NativeModule_UIEventInjectionCallback callback,
    void *userData);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_UI_EVENT_INJECTION_H
/** @} */
