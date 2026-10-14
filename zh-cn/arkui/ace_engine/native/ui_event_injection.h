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
 * @brief 在Native侧提供ArkUI的UI控制能力，适用于应用内智能体和UI自动化场景，
 * 支持向指定UI节点注入控制命令。
 *
 * @since 26.2.0
 */

/**
 * @file ui_event_injection.h
 *
 * @brief 声明供应用内智能体和UI自动化使用的接口，用于向指定UI节点注入控制命令。
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
 * 用于通知命令的派发结果和组件对命令的即时处理结果，不等待组件延迟效果或渲染完成。
 * 每个已受理请求在注入函数返回后，在原UI线程恰好回调一次。不同UI线程上的回调不保证全局串行执行。
 *
 * @param result [in] 注入执行的结果码。详情参见
 *     {@link OH_ArkUI_NativeModule_UIEventInjection_ResultCode}。
 * @param userData [in] 注入时传入的自定义用户数据指针。如果注入时传入NULL，则此处为NULL。
 *        框架仅保存指针值以供此回调使用，不访问该指针指向的数据，也不复制、释放该数据或接管其所有权。
 *        请求受理后，调用方必须保持非NULL数据有效，直到回调返回。
 * @since 26.2.0
 */
typedef void (*OH_ArkUI_NativeModule_UIEventInjectionCallback)(
    OH_ArkUI_NativeModule_UIEventInjection_ResultCode result, void *userData);

/**
 * @brief 向目标UI节点异步注入控制命令。
 *
 * 本接口不提供取消操作或固定的完成超时，完成依赖UI线程的任务处理。
 * 调用方等待超时不会取消已受理请求。
 * 实例销毁不会取消已受理请求的完成回调。
 *
 * @param uiContext [in] UI实例指针，不能为NULL。调用方必须在该实例的UI线程上调用；
 *        检测到线程违规时，将触发致命错误并终止进程。uniqueId必须能够解析为此实例内的节点。
 *        uiContext需在本函数调用期间保持有效。
 * @param uniqueId [in] 目标节点的唯一Id。框架在uiContext实例中将此Id解析为对应的节点。
 * @param command [in] 命令数据，不能为NULL，由{@link OH_ArkUI_NativeModule_UIJsonWrapperCreate}创建的
 *        {@link OH_ArkUI_NativeModule_UIJsonWrapper}对象承载。命令内容的顶层结构为：
 *        {"schemaVersion": 1, "cmd": {"type": "<命令类型>", "action_info": { ... }}}
 *        支持的命令类型、action_info 字段约束及示例，请参见接口开发指南。
 *        函数返回前会在内部复制JSON数据；调用方拥有的command可在本函数返回后销毁。
 * @param callback [in] 完成回调，不能为NULL；请求受理后，须保持可调用直至回调返回，
 *        即使调用方等待超时也不能提前释放回调资源。
 * @param userData [in] 传递给回调的自定义用户数据指针，可以为NULL。
 *        用户数据由调用方管理。请求受理后，非NULL数据须保持有效直至回调返回，即使调用方等待超时也不能提前释放。
 * @return 返回0表示请求已受理，执行结果通过callback报告；返回非零值表示请求被拒绝，不执行命令，也不触发回调。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 请求已受理。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} command或callback为NULL、
 *     命令数据无效，或命令提交失败。</li>
 *     <li>{@link ARKUI_ERROR_CODE_NODE_NOT_FOUND} uniqueId无法解析为uiContext实例内的节点。</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} uiContext为NULL，或对应的UI实例正在销毁或已失效。</li>
 *     <li>{@link ARKUI_ERROR_CODE_COMMAND_UNFINISHED} 当前进程中，前一命令对后续请求的限制尚未解除。
 *     命令受理后，同一进程内的其他有效请求均返回此错误码。框架在调用完成回调前解除此限制。
 *     可在回调中再次提交命令，仍需满足参数和UI线程要求。被拒绝的请求可在限制解除后重试，
 *     能否受理仍取决于进程内的其他请求。</li>
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
