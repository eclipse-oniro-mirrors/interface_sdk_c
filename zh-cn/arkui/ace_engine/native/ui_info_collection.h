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
 * @brief Provides UI perception capabilities of ArkUI on the native side for in-app intelligent
 * agents and UI automation, enabling observation of user interaction events and hit nodes.
 *
 * @since 26.2.0
 */

/**
 * @file ui_info_collection.h
 *
 * @brief Declares the APIs used by in-app intelligent agents and UI automation to observe UI
 * interaction events and hit nodes.
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @include <arkui/ui_info_collection.h>
 * @library libace_ndk.z.so
 * @kit ArkUI
 * @since 26.2.0
 */

#ifndef ARKUI_NATIVE_UI_INFO_COLLECTION_H
#define ARKUI_NATIVE_UI_INFO_COLLECTION_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "multimedia/image_framework/image/pixelmap_native.h"

#include "common_type.h"
#include "error_code.h"
#include "ui_json_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 枚举可观察的UI交互事件类型。
 *
 * 这些值是位标志。它们用于构建传递给的eventMask
 * {@link OH_ArkUI_NativeModule_UIInfoCollectionRegisterInteractionObserver}。
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief 无事件。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_NONE = 0,
    /**
     * @brief 点击手势。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_TAP = 1 << 0,
    /**
     * @brief 单击。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_CLICK = 1 << 1,
    /**
     * @brief 长按手势。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_LONG_PRESS = 1 << 2,
    /**
     * @brief 平移手势。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_PAN = 1 << 3,
    /**
     * @brief 捏合手势。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_PINCH = 1 << 4,
    /**
     * @brief 旋转手势。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_ROTATION = 1 << 5,
    /**
     * @brief 滑动手势。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_SWIPE = 1 << 6,
    /**
     * @brief 统一拖放。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_DRAG = 1 << 7,
    /**
     * @brief 原始触地或向上触地。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_TOUCH = 1 << 8
} OH_ArkUI_NativeModule_UIInfoCollection_InteractionEventType;

/**
 * @brief 接收感知到的交互事件的回调类型。
 *
 * 该回调携带一个借用的{@link OH_ArkUI_NativeModule_UIJsonWrapper}对象，该对象持有
 * 事件负载。对象仅在回调调用内有效；回调不能
 * 保留或销毁它。有效载荷中的所有位置坐标都是相对于屏幕的
 * （显示），以物理像素（px）为单位。负载的顶层结构是：
 *
 * { "schemaVersion": 1, "type": "<事件类型>",...}
 *
 * 事件相关字段如下：
 * -点击或点击：id，点，计数，手指。
 * -长按：id、point、realDuration（毫秒）、action（结束）。
 * -平移：id，点，方向，动作（"开始"|"结束"|"取消"）。
 * - Pinch: id, point（【x,y】的数组）,point,action("start"|"end"|"cancel");scale是
 * 仅在“结束”时出现。
 * -旋转：id，点（【x,y】的数组），手指，动作（"开始"|"结束"|"取消"）；角度
 * （度）只出现在“端”上。
 * - Swipe: id、downPoint（【x,y】的数组）、upPoint（【x,y】的数组）、方向、速度、
 * 实际速度。
 * -拖动：action ("start" | "end"); "start"携带id、point、hostName、realDuration;"end"
 * 携带点，dropResult（"成功"|"失败"）,id（目标，仅在成功时出现）,hostName。
 * - Touch: action（“向下”|“向上”）,findId,point；“向下”还携带id（命中节点ID）。
 *
 * @param json [in] 借用的JSON对象。仅在回调调用时有效。
 * @param userData [in] 注册时传递的自定义用户数据。可以为空。框架
 * 不拥有、取消引用或释放它。
 * @since 26.2.0
 */
typedef void (*OH_ArkUI_NativeModule_UIInfoCollectionInteractionJsonCallback)(
    const OH_ArkUI_NativeModule_UIJsonWrapper *json, void *userData);

/**
 * @brief 注册UI交互事件的观察者。
 *
 * 观察者只接收eventMask中包含的事件类型的回调。
 * 可以为同一个UI实例注册多个观察者。注册相同的回调和userData
 * pair再次创建一个具有新注册ID的额外独立观察者。
 *
 * 记得注销回调{@link OH_ArkUI_NativeModule_UIInfoCollectionUnregisterInteractionObserver}
 * 当它不再使用时。
 *
 * @param uiContext [in] 指向UI实例的指针。不能为空。
 * @param eventMask [in] {@link OH_ArkUI_NativeModule_UIInfoCollection_InteractionEventType}的位掩码
 * 要观察的值，与按位OR运算符结合使用。支持的位数为
 * OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_TAP至
 * OH_ARKUI_NATIVEMODULE_UIINFOCOLLECTION_INTERACTION_EVENT_TOUCH。此范围之外的位
 * 忽略。如果没有设置支持的位，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param registerID [out] 成功时接收观察者注册ID。不能为空。
 * 不需要初始化，失败时设置为0。
 * @param callback [in] 匹配事件发生时调用的回调。不能为空。
 * @param userData [in] 传递给回调的自定义用户数据。可以为空。框架做了
 * 而不是取得它的所有权；调用者必须保持它有效，直到观察者未注册为止。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果操作成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果需要的指针为空或事件掩码
 * 不包含任何支持的位。</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} 如果UI上下文无效。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIInfoCollectionRegisterInteractionObserver(
    ArkUI_ContextHandle uiContext,
    uint32_t eventMask,
    uint32_t *registerID,
    OH_ArkUI_NativeModule_UIInfoCollectionInteractionJsonCallback callback,
    void *userData);

/**
 * @brief 注销交互观察者。
 *
 * 此调用完成后，关联的回调不再被调用。
 *
 * 这个函数是线程安全的，可以从任何线程调用，不会阻塞调用者，并且是
 * 而不是async-signal-safe。
 *
 * @param registerID [in] 注册成功返回的注册ID。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果操作成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果注册ID无效。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIInfoCollectionUnregisterInteractionObserver(uint32_t registerID);

/**
 * @brief 声明一个UI树采集请求结构体。
 *
 * @since 26.2.0
 */
typedef struct OH_ArkUI_NativeModule_UIAgentTreeRequest OH_ArkUI_NativeModule_UIAgentTreeRequest;

/**
 * @brief UI树采集类型的枚举。
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief 收集全量UI树，包括不可见节点、透明节点、离屏节点、阻塞节点。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_AGENT_TREE_FULL = 0,
    /**
     * @brief 采集可视、裁剪、离屏、遮挡过滤后的可见树。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVE_MODULE_UI_AGENT_TREE_VISIBLE = 1
} OH_ArkUI_NativeModule_UIAgentTreeType;

/**
 * @brief 声明异步JSON树请求完成后调用的回调。
 *
 * 对于每个接受的请求，在UI线程上只调用一次回调。回调接收控件树json的所有权
 * 只有errorCode为ARKUI_ERROR_CODE_NO_ERROR时，才为非空的JSON对象。调用者使用完后必须调用OH_ArkUI_NativeModule_UIJsonWrapperDestroy释放对象避免内存泄漏。
 *
 * @param context [in] 用于指定本次采集结果对应的UI上下文。
 * @param requestId [in] 分配给被接受的请求的标识符。
 * @param errorCode [in] 采集请求的结果。
 * @param json [in] 不可变的JSON结果，如果请求失败，则为NULL。否则为Json结构的控件树。这个对象在使用完毕后需要开发者显示释放。
 * @param userData [in] 传递给OH_ArkUI_NativeModule_UIAgent_GetTreeJsonAsync的调用方提供的数据。
 * @release ui_json_wrapper/OH_ArkUI_NativeModule_UIJsonWrapperDestroy {json}.
 * @since 26.2.0
 */
typedef void (*OH_ArkUI_NativeModule_UIAgentJsonCallback)(ArkUI_ContextHandle context, uint64_t requestId, 
    ArkUI_ErrorCode errorCode, OH_ArkUI_NativeModule_UIJsonWrapper *json, void *userData);

/**
 * @brief 创建UI树收集请求。
 * @param treeType [in] 树型。该值必须是OH_ArkUI_NativeModule_UIAgentTreeType的成员。
 * @param request [out] 输出请求对象。调用者必须通过调用来释放它
 * OH_ArkUI_NativeModule_UIAgentTreeRequest_Destroy.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果请求创建成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果输入或输出参数无效。</li>
 *     <li>{@link ARKUI_ERROR_CODE_RESOURCE_EXHAUSTED} 如果分配失败。</li>
 *     </ul>
 * @release OH_ArkUI_NativeModule_UIAgentTreeRequestDestroy {request}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestCreate(OH_ArkUI_NativeModule_UIAgentTreeType treeType,
    OH_ArkUI_NativeModule_UIAgentTreeRequest **request);

/**
 * @brief 销毁UI树收集请求对象。
 *
 * 传递NULL没有任何效果。
 * @param request [in] 销毁的请求。
 * @since 26.2.0
 */
void OH_ArkUI_NativeModule_UIAgentTreeRequestDestroy(OH_ArkUI_NativeModule_UIAgentTreeRequest *request);

/**
 * @brief 设置是否从返回的树中过滤纯布局节点。
 *
 * 默认情况下，过滤是禁用的。启用时，已筛选节点的保留后代将附加到
 * 最近的保留祖先，同时保持它们的相对顺序。
 *
 * @param request [in] 配置的请求。
 * @param enabled [in] 是否过滤纯布局节点。
 * @return <ul>
 *     <li> {@link ARKUI_ERROR_CODE_NO_ERROR} 如果选项设置成功。</li>
 *     <li> {@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果请求为空。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetFilterPureLayoutNodes(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, bool enabled);

/**
 * @brief 设置是否从返回的树中过滤完全遮挡的节点。
 *
 * 默认情况下，过滤是禁用的，只能为可见树启用
 * 请求。禁用此选项不会禁用可见性、剪切、
 * 屏幕外，或完全透明的节点过滤。
 *
 * 遮挡器不透明度阈值可通过以下方式单独配置：
 * {@link OH_ArkUI_NativeModule_UIAgentTreeRequestSetOcclusionOpacityThreshold}。
 * 更改此选项不会更改该阈值。
 *
 * @param request [in] 配置的请求。它不能为NULL。
 * @param enabled [in] true表示启用遮挡过滤；false表示禁用遮挡过滤。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果选项设置成功。
 * 为全树请求设置false也会成功</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果请求为NULL。</li>
 *     <li>{@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} （如果启用）
 * 对于全树请求为true。请求保持不变。
 * 使用可见树请求来启用此选项。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetFilterOccludedNodes(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, bool enabled);

/**
 * @brief 设置节点作为遮挡物参与的最小最终不透明度。
 *
 * 默认值为1.0。仅可见树请求支持该选项。仅删除目标节点
 * 当合格封堵器区域的结合完全覆盖其有效可见区域时。
 *
 * 如果过滤器选项未启用，则此阈值将不起作用
 * {@link OH_ArkUI_NativeModule_UIAgentTreeRequestSetFilterOccludedNodes}。
 *
 * @param request [in] UI树收集请求。
 * @param threshold [in] 范围【0.0,1.0】内的不透明度阈值。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果设置成功</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果请求为空。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} 如果阈值超出有效范围</li>
 *     <li>{@link ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED} 如果请求的是完整的树。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetOcclusionOpacityThreshold(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, float threshold);

/**
 * @brief 设置是否收集附加交互信息。
 *
 * 默认情况下，是关闭收集的。启用时，结果包括
 * 支持的交互信息，如节点是否可点击。
 * 可聚焦，或可编辑。此选项不注册事件观察者
 * 或者改变任意节点的交互行为。
 *
 * 禁用此选项不会删除默认选项中包含的字段
 * 简化的结果。高级属性集合不会隐式地
 * 启用此选项或收集为此选项保留的字段。
 *
 * @param request [in] 配置的请求。它不能为NULL。
 * @param enabled [in] 表示收集交互信息为true，否则为false。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果选项设置成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果请求为NULL。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetInteractionInfo(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, bool enabled);

/**
 * @brief 设置是否收集其他辅助功能信息。
 *
 * 默认情况下，是关闭收集的。启用时，结果包括
 * 支持的辅助功能信息，例如辅助功能内容。
 * 此选项不会启用辅助功能服务或更改节点行为。
 *
 * 禁用此选项不会删除默认选项中包含的字段
 * 简化的结果。高级属性集合不会隐式地
 * 启用此选项或收集为此选项保留的字段。
 *
 * @param request [in] 配置的请求。它不能为NULL。
 * @param enabled [in] 为true则收集可访问性信息；否则为false。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果选项设置成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果请求为NULL。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetAccessibilityInfo(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, bool enabled);

/**
 * @brief 设置是否收集高级视觉属性。
 *
 * 默认情况下，是关闭收集的。启用后，结果会额外
 * 包括描述可直接感知外观的支持属性，
 * 例如视觉样式和显示的状态。
 *
 * 已包含在默认简化结果中的属性不
 * 重复。为交互或可访问性集合保留的字段
 * 都被排除在此属性组中，无论这些选项是什么。
 * 从不包含内部诊断属性。
 *
 * 此选项独立于高级函数属性集合
 * 并且不会改变树中保留的节点。
 *
 * @param request [in] 配置的请求。它不能为NULL。
 * @param enabled [in] true表示收集高级视觉属性，否则为false。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果选项设置成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果请求为NULL。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetCollectVisualProperties(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, bool enabled);

/**
 * @brief 设置是否收集高级功能属性。
 *
 * 默认情况下，是关闭收集的。启用后，结果会额外
 * 包括描述开发人员配置的组件的支持属性
 * 行为和功能能力。
 *
 * 已包含在默认简化结果中的属性不
 * 重复。为交互或可访问性集合保留的字段
 * 都被排除在此属性组中，无论这些选项是什么。
 * 从不包含内部诊断属性。
 *
 * 此选项独立于高级视觉特性集合
 * 并且不会改变树中保留的节点。
 *
 * @param request [in] 配置的请求。它不能为NULL。
 * @param enabled [in] true表示收集高级函数属性，否则为false。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果选项设置成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果请求为NULL。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentTreeRequestSetCollectFunctionalProperties(
    OH_ArkUI_NativeModule_UIAgentTreeRequest *request, bool enabled);

/**
 * @brief 同步收集UI树并以JSON形式返回。
 *
 * 此函数必须在UI线程上调用。最多包含5000个节点，且不能超过5MiB。
 * 大小限制是使用规范的紧凑型JSON来测量的。如果输出本身超过5 MiB，请求也
 * 失败，没有返回部分JSON。
 *
 * @param context [in] 收集其树的UI上下文。
 * @param request [in] 催缴请求。
 * @param format [in] JSON输出格式。
 * @param json [out] 输出不可变的JSON对象。调用者必须通过调用来释放它
 * OH_ArkUI_NativeModule_UIJsonWrapperDestroy.
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果收集成功</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果参数或格式无效。</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} 如果上下文无效。</li>
 *     <li>{@link ARKUI_ERROR_CODE_NODE_ON_INVALID_THREAD} 如果在UI线程外部调用。</li>
 *     <li>{@link ARKUI_ERROR_CODE_RESULT_TOO_LARGE} 如果超过结果限制。</li>
 *     <li>{@link ARKUI_ERROR_CODE_RESOURCE_EXHAUSTED} 如果分配失败。</li>
 *     <li>{@link ARKUI_ERROR_CODE_INTERNAL_ERROR} 如果发生其他内部错误。</li>
 *     </ul>
 * @release ui_json_wrapper/OH_ArkUI_NativeModule_UIJsonWrapperDestroy {json}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentGetTreeJson(ArkUI_ContextHandle context,
    const OH_ArkUI_NativeModule_UIAgentTreeRequest *request,
    OH_ArkUI_NativeModule_UIJsonFormat format,
    OH_ArkUI_NativeModule_UIJsonWrapper **json);

/**
 * @brief 发起异步UI树收集请求。通过异步回调接收集合。
 * 此函数必须在UI线程上调用。函数在返回之前复制请求和格式，因此
 * 调用方可以在调用后立即销毁或重用请求。每个接受的请求仅完成一次
 * 在UI线程上。
 * @param context [in] 收集其树的UI上下文。
 * @param request [in] 催缴请求。
 * @param format [in] JSON输出格式。
 * @param callback [in] 完成回调。成功后，回调将接收JSON对象的所有权，并且必须
 * 通过调用OH_ArkUI_NativeModule_UIJsonWrapperDestroy来释放它。
 * @param userData [in] 传递给回调的调用方提供的数据。
 * @param requestId [out] 接受的请求的输出标识符。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果请求被接受。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果参数或格式无效。</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} 如果上下文无效。</li>
 *     <li>{@link ARKUI_ERROR_CODE_NODE_ON_INVALID_THREAD} 如果在UI线程外部调用。</li>
 *     <li>{@link ARKUI_ERROR_CODE_COMMAND_UNFINISHED} 如果最后一个请求未完成。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentGetTreeJsonAsync(ArkUI_ContextHandle context,
    const OH_ArkUI_NativeModule_UIAgentTreeRequest *request,
    OH_ArkUI_NativeModule_UIJsonFormat format,
    OH_ArkUI_NativeModule_UIAgentJsonCallback callback, void *userData, uint64_t *requestId);

/**
 * @brief 同步采集当前ArkUI页面的文本，并将文本以JSON格式输出。每个JSON项
 * 包含一个整数“id”。
 * 识别控件、相对于目标窗口的矩形“rect”和文本内容
 * 字符串“content”。使用完后，使用OH_ArkUI_NativeModule_UIJsonWrapperDestroy来释放结果
 * 记忆。
 * 函数必须在UI线程上调用。输出格式如下：
 * @param uiContext [in] 文本收集的目标UI实例的上下文
 * @param pageText [out] 输出槽，由调用者初始化为NULL。
 * 失败时将有效槽设置为NULL；空页仍然返回
 * 包装纸。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果pageText为NULL。</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} 如果uiContext为NULL或不再有效。</li>
 *     <li>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} 如果本机实现不可用。</li>
 *     <li>{@link ARKUI_ERROR_CODE_INTERNAL_ERROR} 如果当前页面不存在、JSON负载大小无法用uint32_t表示，
 * 或收集/序列化失败。</li>
 *     </ul>
 * @release ui_json_wrapper/OH_ArkUI_NativeModule_UIJsonWrapperDestroy {pageText}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIAgentGetPageText(
    ArkUI_ContextHandle uiContext, OH_ArkUI_NativeModule_UIJsonWrapper** pageText);

/**
 * @brief 声明ArkUI内容变更事件结构体。
 * @since 26.2.0
 */
typedef struct OH_ArkUI_NativeModule_UIContentChangeEvent OH_ArkUI_NativeModule_UIContentChangeEvent;

/**
 * @brief UI内容变化事件类别枚举
 * @since 26.2.0
 */
typedef enum OH_ArkUI_NativeModule_UIContentChangeEventCategory {
    /**
     * @brief 页面切换事件，包括导航、路由、滑动、Tabs切换事件。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_CATEGORY_PAGE = 1U << 0,
    /**
     * @brief 滚动事件。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_CATEGORY_SCROLL = 1U << 1,
    /**
     * @brief 叠加事件。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_CATEGORY_OVERLAY = 1U << 2,
    /**
     * @brief 所有支持的事件类别。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_CATEGORY_ALL = ~0U
} OH_ArkUI_NativeModule_UIContentChangeEventCategory;

/**
 * @brief UI内容更改事件忽略枚举
 * @since 26.2.0
 */
typedef enum OH_ArkUI_NativeModule_UIContentChangeIgnoreType {
    /**
     * @brief 按事件滚动。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CONTENTCHANGE_IGNORE_SCROLLBY = 1U << 0,
    /**
     * @brief 滚动到事件。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CONTENTCHANGE_IGNORE_SCROLLTO = 1U << 1,
    /**
     * @brief Toast事件。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_CONTENTCHANGE_IGNORE_TOAST = 1U << 2
} OH_ArkUI_NativeModule_UIContentChangeIgnoreType;

/**
 * @brief ArkUI内容变化事件枚举类型。
 *
 * @since 26.2.0
 */
typedef enum OH_ArkUI_NativeModule_UIContentChangeEventType {
    /**
     * @brief 页面更改的开始。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_PAGE_CHANGE_START = 0,
    /**
     * @brief 换页结束
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_PAGE_CHANGE_END = 1,
    /**
     * @brief 滚动事件开始
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_SCROLL_START = 2,
    /**
     * @brief 一个滚动交互和任何后续的惯性滚动都已经结束。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_SCROLL_END = 3,
    /**
     * @brief 覆盖层已完成显示。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_OVERLAY_SHOW = 4,
    /**
     * @brief 覆盖层已完成消失。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_OVERLAY_HIDE = 5,
    /**
     * @brief 一个滑动器交互已经开始。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_SWIPER_START = 6,
    /**
     * @brief 滑动器交互已经完成，包括其过渡动画（如果存在）。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_SWIPER_END = 7,
    /**
     * @brief Swiper切换事件返回起始索引。
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_SWIPER_CANCEL = 8,
    /**
     * @brief 选项卡开始事件
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_TABS_START = 9,
    /**
     * @brief 选项卡结束事件
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_TABS_END = 10,
    /**
     * @brief Tabs开关启动后，取消事件。指数启动后反弹
     *
     * @since 26.2.0
     */
    OH_ARKUI_NATIVEMODULE_EVENT_TABS_CANCEL = 11
} OH_ArkUI_NativeModule_UIContentChangeEventType;

/**
 * @brief 声明注册的ArkUI内容变化事件的回调。
 *
 * 回调在与注册的上下文关联的用户界面线程上运行。事件快照为
 * 不可变且仅在此回调返回前有效。ArkUI借用但不访问或释放userData。
 *
 * @param event [in] 指向不可变事件对象的指针。
 * @param userData [in] 注册回调时提供的指针。指针可以为NULL。
 * @since 26.2.0
 */
typedef void (*OH_ArkUI_NativeModule_UIContentChangeEventCallback)(
    const OH_ArkUI_NativeModule_UIContentChangeEvent* event, void* userData);

/**
 * @brief 注册指定UI实例内容变化事件监听
 *
 * 每次成功调用都会创建一个独立的订阅。返回的ID非零且在
 * 上下文。在上下文的用户界面线程上同步调用回调。ArkUI借用uiContext
 * 和userData，并且不释放这两个值。如果操作失败，则不修改subscribeId。
 * 此函数必须在UI线程上调用；从非UI线程调用它将中止进程。
 *
 * @param uiContext [in] 要观察的用户界面上下文。句柄必须对订阅保持有效。
 * @param withStart [in] 是否上报开始事件。设置为true时，启动事件(如页面更改开始和
 * 如果设置为false，则只报告结束事件。
 * @param eventMask [in] {@link OH_ArkUI_NativeModule_UIContentChangeEventCategory}值的按位或组合。
 * 不能为零。{@link OH_ARKUI_NATIVEMODULE_EVENT_CATEGORY_SCROLL}类别可以执行以下操作：
 * 不区分滚动子类型。设置对应的
 * {@link OH_ARKUI_NATIVEMODULE_CONTENTCHANGE_IGNORE_SCROLLTO}或
 * 忽略掩码中的{@link OH_ARKUI_NATIVEMODULE_CONTENTCHANGE_IGNORE_SCROLLBY}位以忽略这些事件。
 * @param ignoreMask [in] {@link OH_ArkUI_NativeModule_UIContentChangeIgnoreType}值的按位或组合。
 * @param userData [in] 传递给回调的用户定义数据。指针可以是NULL，并且由调用者拥有。
 * @param callback [in] 匹配事件调用的回调。回调不能为NULL。
 * @param subscriptionId [out] 操作成功时写入的非零订阅ID指针。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果操作成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} 如果uiContext为NULL或不再活动。</li>
 *     <li>{@link ARKUI_ERROR_CODE_CALLBACK_INVALID} 如果回调为NULL。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果eventMask或subscriptionId无效。</li>
 *     <li>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} 如果本机C API未初始化。</li></ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_RegisterUIContentChangeEvent(
    ArkUI_ContextHandle uiContext, bool withStart, uint32_t eventMask, uint32_t ignoreMask, void* userData, 
    OH_ArkUI_NativeModule_UIContentChangeEventCallback callback,
    uint64_t* subscriptionId);

/**
 * @brief 从用户界面上下文中取消注册活动的ArkUI状态更改事件订阅。
 *
 * 此函数成功返回后，后续事件将不再调用已移除的订阅。然后，调用者可以
 * 释放其userData。取消订阅回调不会更改当前正在调度的回调批次。
 * 此函数必须在UI线程上调用；从非UI线程调用它将中止进程。
 *
 * @param uiContext [in] 拥有订阅的用户界面上下文。
 * @param subscriptionId [in] uiContext拥有的活动订阅的非零ID。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果操作成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID} 如果uiContext为NULL或不再活动。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果subscriptionId为零、未知或已被移除。</li>
 *     <li>{@link ARKUI_ERROR_CODE_CAPI_INIT_ERROR} 如果原生C API未初始化。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UnRegisterUIContentChangeEvent(
    ArkUI_ContextHandle uiContext, uint64_t subscriptionId);

/**
 * @brief 从ArkUI状态变化事件快照中获取事件类型。
 *
 * @param event [in] 事件快照指针。该指针仅在回调运行时有效。
 * @param type [out] 操作成功时写入的事件类型指针。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果操作成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果事件或类型为NULL。</li></ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIContentChangeEventGetType(
    const OH_ArkUI_NativeModule_UIContentChangeEvent* event, OH_ArkUI_NativeModule_UIContentChangeEventType* type);

/**
 * @brief 获取ArkUI状态变化事件快照的单调时间戳。
 *
 * 时间戳在事件完成点捕获，以纳秒表示，不是挂钟时间。
 *
 * @param event [in] 事件快照指针。该指针仅在回调运行时有效。
 * @param nanoTimestamp [out] 操作成功时写入的以纳秒为单位的单调时间戳指针。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果操作成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果事件或nano时间戳为NULL。</li></ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIContentChangeEventGetTimestamp(
    const OH_ArkUI_NativeModule_UIContentChangeEvent* event, uint64_t* nanoTimestamp);

/**
 * @brief 获取ArkUI状态变化事件快照关联的用户界面上下文。
 *
 * 返回的句柄是借用的，在回调返回后，调用者不得释放或使用它。
 *
 * @param event [in] 事件快照指针。该指针仅在回调运行时有效。
 * @param uiContext [out] 操作成功时写入的用户界面上下文句柄指针。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果操作成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果事件或uiContext为NULL。</li></ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIContentChangeEventGetContext(
    const OH_ArkUI_NativeModule_UIContentChangeEvent* event, ArkUI_ContextHandle* uiContext);

/**
 * @brief 从ArkUI状态变更事件快照中获取内容变更事件详情，作为JSON包装器。
 *
 * JSON输出包括内容变化类型、触发节点、目标节点、覆盖类型和可选的
 * 子树转储取决于事件类别：
 *
 * 页面事件标识目标页面。滚动事件标识滚动节点。重叠事件标识
 * 覆盖节点，并提供覆盖类型（例如“对话框”）。触发节点是启动
 * 内容更改；它适用于覆盖事件和一般开始/结束场景，对于页面和
 * 当没有触发器节点可以暴露时，滚动事件。操作成功并写入一个空的JSON包装器，当
 * 不能暴露任何目标节点。JSON包装器中引用的句柄是借用的，不能被释放
 * 或在回调返回后使用。
 *
 * @param event [in] 事件快照指针。该指针仅在回调运行时有效。
 * @param json [out] 接收到内容变更事件的{@link OH_ArkUI_NativeModule_UIJsonWrapper}指针
 * .在回调返回后，调用者不得释放包装器或使用它。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果操作成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果事件或json为NULL。</li></ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_UIContentChangeEventGetContentChangeEventJson(
    const OH_ArkUI_NativeModule_UIContentChangeEvent* event, const OH_ArkUI_NativeModule_UIJsonWrapper** json);

/**
 * @brief ArkUI图像采集结果结构体声明
 * @since 26.2.0
 */
typedef struct OH_ArkUI_NativeModule_ImageCollection OH_ArkUI_NativeModule_ImageCollection;

/**
 * @brief 定义ArkUI节点图片采集结果返回的回调。
 *
 * 对于每个接受的请求，框架在UI线程上调用此回调仅一次。
 * 当<b>errorCode</b>为{@link ARKUI_ERROR_CODE_NO_ERROR}时，框架将转移non-<b>null</b>的所有权
 * 向主叫方发送<b>collection</b>。当<b>errorCode</b>为{@link ARKUI_ERROR_CODE_INTERNAL_ERROR}或
 * {@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID},<b>collection</b>为<b>null</b>。
 *
 * 框架在不取消引用的情况下返回不变的<b>userData</b>，
 * 复制，或者释放它所指向的对象。打电话的人一定要留着
 * 对象在回调结束使用之前有效。
 *
 * @param errorCode [in] 表示请求的整体结果。
 * <ul<li>>{@link ARKUI_ERROR_CODE_NO_ERROR}表示采集成功。</li>
 * <li>{@link ARKUI_ERROR_CODE_INTERNAL_ERROR}表示内部采集失败。</li>
 * <li>{@link ARKUI_ERROR_CODE_UI_CONTEXT_INVALID}上下文在请求被接受后变得无效。</li></ul>
 * @param collection [in] 表示结果集合。该值为non-<b>null</b>表示总体成功，
 * <b>null</b>表示总体误差。
 * @param userData [in] 表示调用者定义的上下文指针。取值范围：<b>null</b>。
 * @release OH_ArkUI_NativeModule_ImageCollectionDestroy {collection}
 * @since 26.2.0
 */
typedef void (*OH_ArkUI_NativeModule_ImageCollectionCallback)(ArkUI_ErrorCode errorCode,
    OH_ArkUI_NativeModule_ImageCollection* collection, void* userData);

/**
 * @brief 异步采集指定ArkUI节点ID的镜像。
 *
 * 该框架接受从<b>0</b>到<b>20</b>的唯一节点ID
 * 在此函数返回之前，请求并复制<b>nodeIds</b>数组。
 * 框架接受<b>count</b>等于<b>0</b>的请求，
 * 通过回调返回一个non-<b>null</b>空集合。
 *
 * 每个接受的节点ID在集合中都有一个结果，包括一个结果
 * 对于找不到或无法抓取图像的节点ID。
 * <b>Image</b>节点在可用时返回其完整的源<b>PixelMap</b>
 * 否则返回到捕获节点内的呈现内容
 * 边界。non-<b>Image</b>节点使用相同的节点边界捕获行为。
 * 节点不需要是可见的。
 *
 * 如果找不到请求的节点ID对应的ArkUI节点，则
 * 对应的收集项报表
 * <b>ARKUI_ERROR_CODE_PARAM_INVALID</b>；调用方应检查节点ID。
 * A捕获超时报告
 * <b>ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT</b>；调用方可以重试
 * 请求。另一个内部捕获失败报告
 * 该项目的<b>ARKUI_ERROR_CODE_INTERNAL_ERROR</b>；调用方可以重试
 * 处理失败后的请求。项目失败不会改变
 * 请求的整体成功结果。
 *
 * 调用者可以从任何线程调用此函数。对于每一个接受
 * 请求时，框架将在UI线程上调用<b>callback</b>一次
 * 与<b>context</b>关联。并发请求是独立的，而
 * 框架不保证它们的回调顺序。
 *
 * @param context [in] 表示用于处理请求的ArkUI上下文。
 * 参数不能为<b>null</b>。
 * @param nodeIds [in] 表示数组的第一个元素，包含
 * <b>count</b>唯一的ArkUI节点ID。参数不能为NULL。
 * @param count [in] 表示节点ID的个数。有效范围为(0, 20]
 * @param callback [in] 表示用于接收结果的回调。
 * 参数不能为<b>null</b>。
 * @param userData [in] 表示传递的调用者定义的上下文指针
 * 与回调保持一致。取值范围：<b>null</b>。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果框架接受请求。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果上下文或回调为空。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE} 计数超出范围(0, 20]。</li>
 *     <li>{@link ARKUI_ERROR_CODE_COMMAND_UNFINISHED} 如果最后一个请求未完成。</li></ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_GetImagesByNodeIdAsync(ArkUI_ContextHandle context, const int32_t* nodeIds,
    uint32_t count, OH_ArkUI_NativeModule_ImageCollectionCallback callback, void* userData);

/**
 * @brief 消费指定节点ID的结果。
 *
 * 对于成功的图像结果，此函数将
 * 向主叫方发送<b>PixelMap</b>。调用者必须通过调用来释放它
 * <b>OH_PixelmapNative_Destroy</b>。此函数也会消耗失败的映像
 * 在这种情况下，它将<b>*outPixelmap</b>设置为<b>null</b>并写入
 * 项错误到<b>*outItemError</b>。集合中的每个节点ID可以为
 * 只消费一次。
 *
 * 销毁集合仅释放<b>PixelMap</b>实例
 * 调用方未使用且未使转移的<b>PixelMap</b>无效。
 *
 * 调用者不能与另一个集合同时调用此函数
 * 同一个集合的api。
 *
 * @param collection [in] 表示被消费的图片集合。参数不能为空。
 * @param nodeId [in] 表示要消费的item的ArkUI节点ID。
 * @param outPixelmap [out] 接收传入的PixelMap的输出指针。参数不能
 * 为null。对于失败的项目，该函数将outPixelmap设置为null。
 * @param outItemError [out] 表示指向该项目的结果代码的输出指针。参数不能为
 * null。函数为成功的项写入{@link ARKUI_ERROR_CODE_NO_ERROR}。
 * {@link ARKUI_ERROR_CODE_NODE_NOT_FOUND}如果请求的节点ID对应的ArkUI节点不能
 * 在收集其图像时发现，{@link ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT}捕获超时，或
 * {@link ARKUI_ERROR_CODE_INTERNAL_ERROR}如果再次捕获失败，调用者可以重试请求。
 * @return <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 如果此函数消耗项目，包括失败的图像结果。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 如果所需指针为NULL、nodeId不对应集合中的任何项，
 * 或者调用者已经消费了该项。要解决此错误，请提供所有必需的指针
 * 并使用nodeId来标识集合中的未消费项。</li></ul>
 * @release multimedia/image_framework/image/OH_PixelmapNative_Destroy {outPixelmap}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImageCollectionTakeItemByNodeId(
    OH_ArkUI_NativeModule_ImageCollection* collection, int32_t nodeId,
    OH_PixelmapNative** outPixelmap, ArkUI_ErrorCode* outItemError);

/**
 * @brief 销毁镜像集合，释放未消费的<b>PixelMap</b>实例。
 *
 * 调用方必须销毁回调的每个non-<b>null</b>集合
 * 返回，包括一个空集合或一个在调用者有
 * 消耗了它所有的物品。此功能不会释放或失效
 * 调用方通过获取的<b>PixelMap</b>实例
 * <b>OH_ArkUI_NativeModule_ImageCollection_TakeItemByNodeId</b>.
 *
 * 调用者不能与另一个集合同时调用此函数
 * 同一个集合的api。
 *
 * @param collection [in] 表示要销毁的图像集合。
 * 参数可以是<b>null</b>。如果<b>collection</b>为<b>null</b>，则此
 * 函数什么也不做。
 * @since 26.2.0
 */
void OH_ArkUI_NativeModule_ImageCollectionDestroy(OH_ArkUI_NativeModule_ImageCollection* collection);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_UI_INFO_COLLECTION_H
/** @} */