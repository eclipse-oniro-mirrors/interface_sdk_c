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
 * @since 26.1.0
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
 * @since 26.1.0
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
 * @since 26.1.0
 */
typedef enum {
    /**
     * @brief 注入的命令执行成功。
     *
     * @since 26.1.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_EVENT_INJECTION_RESULT_SUCCESS = 0,
    /**
     * @brief 未找到能够响应注入命令的组件或目标。
     *
     * 例如，点击坐标未命中任何组件，或无法定位执行模式所需的目标。
     *
     * @since 26.1.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_EVENT_INJECTION_RESULT_TARGET_NOT_FOUND = 1,
    /**
     * @brief 当前UI上下文无法执行该命令。
     *
     * 命令结构有效，但当前UI状态不支持该命令的类型或执行模式。
     *
     * @since 26.1.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_EVENT_INJECTION_RESULT_COMMAND_NOT_SUPPORTED = 2,
    /**
     * @brief 注入的命令被用户操作中断。
     *
     * @since 26.1.0
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
 * @since 26.1.0
 */
typedef void (*OH_ArkUI_NativeModule_UIEventInjectionCallback)(
    OH_ArkUI_NativeModule_UIEventInjection_ResultCode result, void *userData);

/**
 * @brief 异步向UI注入宽松的交互命令。
 *
 * 该命令表达了一个高层次的交互意图(点击、content_switch、scroll、backpress、
 * 或关键)，而不针对特定的组件；系统根据
 * 模式。
 *
 * 该命令由使用创建的{@链接OH_ArkUI_NativeModule_UIJsonWrapper}对象携带
 * {@链接OH_ArkUI_NativeModule_UIJsonWrapper_Create}。命令负载的顶层结构是：
 *
 * { "schemaVersion": 1, "cmd": { "type": "<命令类型>","mode":"<执行模式>","action_info":{...}}}
 *
 * 命令特定的参数如下；除非标记为必需，否则action_info字段
 * 可选：
 * -单击：模式（可选，默认为“auto”）;action_info.坐标与x1和y1（都是必需的）。
 * - content_switch: mode必须为“target”；action_info.count必须为正整数(可选，
 * default 1); action_info.direct（"前向"|"后向"，可选，默认"前向"）；
 * 带有x和y的action_info.codices.pos（必需）。
 * - scroll：模式（可选，默认为“auto”）;action_info.direct(“向前”|“向后”|“向左”
 * | "right" | "up" | "down"，可选，默认"forward";action_info.mote，非负
 * 物理像素值（可选，默认为窗口高度的三分之一）;action_info.坐标
 * 其中x1和y1是必需的，x2和y2是可选的。
 * - backpress：无参数。
 * - key: action_info.code，密钥的虚拟密钥代码，必须是有效的密钥代码
 * （必填项）。
 *
 * 所有位置坐标都是相对于窗口的，以物理像素（px）为单位。如果需要
 * 字段缺失或值超出其有效范围，
 * 返回{@link RKUI_ERROR_CODE_PARAM_INVALID}。
 *
 * 这个函数是线程安全的，可以从任何线程调用，不会阻塞调用者，并且是
 * 而不是async-signal-safe。
 *
 * @param uiContext 【in】指向UI实例的指针。不能为空。
 * @param command 【in】配置的JSON命令。它不能为空，并且必须对
 * 呼叫的持续时间。被调用方不保留。
 * @param callback 【in】可选回调，当注入的命令执行完成时调用一次。
 * 可以为空。
 * @param userData 【in】传递给回调的自定义用户数据。可以为空。框架做了
 * 而不是取得它的所有权；调用者必须保持它有效，直到回调完成。
 * @return <ul>
 * <li>{@link RKUI_ERROR_CODE_NO_ERROR}如果命令排队成功。</li>
 * <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID}如果参数无效或缺少必填字段。</li>
 * 如果UI上下文无效，则<li>{@link RKUI_ERROR_CODE_UI_CONTEXT_INVALID}。</li>
 * </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIEventInjectRelaxedInteraction(
    ArkUI_ContextHandle uiContext,
    const OH_ArkUI_NativeModule_UIJsonWrapper *command,
    OH_ArkUI_NativeModule_UIEventInjectionCallback callback,
    void *userData);

/**
 * @brief 向指定UI实例异步注入宽松交互命令，无需指定节点ID。
 *
 * 支持click、content_switch、scroll、backpress和key五类命令。命令由
 * {@link OH_ArkUI_NativeModule_UIJsonWrapperCreate}创建的
 * {@link OH_ArkUI_NativeModule_UIJsonWrapper}对象承载，顶层结构为：
 * {"schemaVersion": 1, "cmd": {"type": "<命令类型>", "action_info": { ... }}}
 * schemaVersion必须为数字1。
 *
 * 本接口可从任意线程调用，返回前完成JSON参数校验和复制，执行和回调在目标实例的UI线程进行。
 * 返回0表示请求已受理，执行结果通过callback报告；返回非零值表示请求被拒绝，不执行命令，也不触发回调。
 *
 * callback非NULL时，每个已受理请求在命令执行完成后回调一次，不等待动画或渲染完成。
 * 目标UI线程调用时，回调在本函数返回后执行；其他线程调用时，回调可能在本函数返回前执行。
 * 可同时提交多个命令，不保证执行或回调顺序。请求受理后实例不可用时，回调报告
 * {@link OH_ARKUI_NATIVE_MODULE_UI_EVENT_INJECTION_RESULT_TARGET_NOT_FOUND}。
 *
 * @param uiContext [in] 目标UI实例句柄，不能为NULL，调用期间必须有效。调用方须同步句柄自身的销毁。
 * @param command [in] 已配置的JSON命令对象，不能为NULL，调用期间必须有效。
 *     对象由调用方管理，可在本函数返回后销毁。
 * @param callback [in] 完成回调，可以为NULL。非NULL时，须保持可调用直至回调返回。
 * @param userData [in] 原样传递给callback的自定义用户数据指针，可以为NULL。
 *     框架仅保存指针值，不访问、复制、释放所指数据，也不接管其所有权。
 *     callback非NULL时，数据须在调用前准备好，并保持有效直至回调返回；运行环境关闭时须同步回调完成。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 请求已受理。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} command为NULL、JSON格式或命令参数非法、
 *     缺少必填字段，或命令投递失败。</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} uiContext为NULL，或目标实例、任务执行器不可用。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIEventInjectRelaxedInteraction(
    ArkUI_ContextHandle uiContext,
    const OH_ArkUI_NativeModule_UIJsonWrapper *command,
    OH_ArkUI_NativeModule_UIEventInjectionCallback callback,
    void *userData);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_UI_EVENT_INJECTION_H
/** @} */
