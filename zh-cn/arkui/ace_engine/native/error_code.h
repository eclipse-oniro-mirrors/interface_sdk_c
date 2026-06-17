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
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file error_code.h
 *
 * @brief Defines the error code for the native module.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_ERROR_CODE_H
#define ARKUI_NATIVE_ERROR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Enumerates the error codes.
*
* @since 12
*/
typedef enum {
    /**
     * 没有错误。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NO_ERROR = 0,
    /**
     * 参数错误。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_PARAM_INVALID = 401,
    /**
     * API初始化错误。
     * @since 18
     */
    ARKUI_ERROR_CODE_CAPI_INIT_ERROR = 500,
    /**
     * 内部错误，例如由于内部环境问题导致的失败，或者由于内部原因导致的操作失败。
     * 执行错误。
     * @since 15
     */
    ARKUI_ERROR_CODE_INTERNAL_ERROR = 100001,
    /**
     * 参数错误。错误码请参见{@link 100023参数错误}。
     * @since 21
     */
    ARKUI_ERROR_CODE_PARAM_ERROR = 100023,
    /**
     * **XComponent**处于无效或不受支持的状态。详细信息请参见{@link XComponent错误码}。
     * @since 18
     */
    ARKUI_ERROR_CODE_XCOMPONENT_STATE_INVALID = 103501,
    /**
     * 组件不支持特定属性或事件。具体操作请参见
     * {@link 交互事件错误码}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED = 106102,
    /**
     * ArkTS创建的节点无法进行相应的操作。错误码的详细信息请参见。
     * 请参见{@link 106103 ArkTS创建的节点不允许操作}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED = 106103,
    /**
     * 懒加载的适配器没有绑定到组件上。错误码的详细信息请参见。
     * {@link 106104适配器未绑定}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ADAPTER_NOT_BOUND = 106104,
    /**
     * 适配器已存在。错误码请参见{@link 106105适配器已存在}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ADAPTER_EXIST = 106105,
    /**
     * 添加适配器失败，对应节点已存在子节点。错误码的详细信息请参见。
     * 请参见{@link 106106子节点存在}。
     * @since 12
     */
    ARKUI_ERROR_CODE_CHILD_NODE_EXIST = 106106,
    /**
     * 参数事件中的参数长度超过限制。错误码的详细信息请参见。
     * {@link 106107索引超出范围}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE = 106107,
    /**
     * 该数据在组件事件中不存在。错误码的详细信息请参见。
     * {@link 106108数据未找到}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID = 106108,
    /**
     * 组件事件不支持返回值。错误码的详细信息请参见。
     * {@link 106109不支持返回值}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_EVENT_NO_RETURN = 106109,
    /**
     * 不支持此事件类型。错误码请参见{@link 106110 Unsupported Event Type}。
     * @since 21
     */
    ARKUI_ERROR_CODE_NODE_UNSUPPORTED_EVENT_TYPE = 106110,
    /**
     * 无效的索引，<br>错误码请参见{@link 106200无效的索引值}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_INDEX_INVALID = 106200,
    /**
     * 获取路由导航信息失败。<br>错误码请参见
     * {@link 106201获取路由导航信息失败}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_GET_INFO_FAILED = 106201,
    /**
     * 传递的缓冲区大小无效（数据太大）。<br>有关错误代码的详细信息，请参阅
     * {@link 106202无效的缓冲区大小}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR = 106202,
    /**
     * 传入的节点未挂载到组件树中。错误码的详细信息请参见。
     * {@link 106203传递的节点未挂载到组件树}。
     * @since 15
     */
    ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE = 106203,
    /**
     * 不支持在非UI线程上对提供的节点进行操作。错误码的详细信息请参见。
     * {@link 106204不支持在非UI线程上对提供的节点进行操作}。
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_ON_INVALID_THREAD = 106204,
    /**
     * 反色能力入参错误。错误码的详细信息请参见。
     * {@link 106205反色能力入参非法}。
     * @since 20
     */
    ARKUI_ERROR_CODE_FORCE_DARK_CONFIG_INVALID = 106205,
    /**
     * 该节点已被接受为辅助节点。错误码的详细信息请参见。
     * {@link 106206节点已被接受为辅助节点}。
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_IS_ADOPTED = 106206,
    /**
     * 接受的节点已经有父节点。错误码的详细信息请参见。
     * {@link 106207要接受的辅助节点有一个父节点}。
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_HAS_PARENT = 106207,
    /**
     * 不能接受该节点作为辅助节点。错误码的详细信息请参见。
     * {@link 106208无法接受节点为辅助节点}。
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_CAN_NOT_BE_ADOPTED = 106208,
    /**
     * 该节点不能接受其他节点。错误码的详细信息请参见。
     * {@link 106209节点无法接受其他节点}。
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_CAN_NOT_ADOPT_TO = 106209,
    /**
     * 该节点不是目标节点接受的辅助节点。错误码的详细信息请参见。
     * {@link 106210该节点不是目标节点接受的附属节点}。
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_IS_NOT_IN_ADOPTED_CHILDREN = 106210,
    /**
     * 当前节点不是自定义节点。详细信息请参见{@link渲染节点错误码}。
     * @since 20
     */
    ARKUI_ERROR_CODE_NOT_CUSTOM_NODE = 106401,
    /**
     * 当前节点已经存在子节点。详细信息请参见{@link渲染节点错误码}。
     * @since 20
     */
    ARKUI_ERROR_CODE_CHILD_EXISTED = 106402,
    /**
     * 当前渲染节点有一个父组件。详细信息请参见{@link渲染节点错误码}。
     * @since 20
     */
    ARKUI_ERROR_CODE_RENDER_PARENT_EXISTED = 106403,
    /**
     * 找不到对应的渲染子节点。详细信息请参见{@link渲染节点错误码}。
     * @since 20
     */
    ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST = 106404,
    /**
     * 参数值超出范围。详细信息请参见{@link渲染节点错误码}。
     * @since 20
     */
    ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE = 106405,
    /**
     * 从{@link FrameNode}中获取当前渲染节点。错误码的详细信息请参见。
     * {@link 106406从FrameNode获取当前渲染节点}。
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE = 106406,
    /**
     * 当前渲染节点是从{@link FrameNode}中获取的，并且{@link FrameNode}还没有被作为
     * 关联节点或已被处理。错误码的详细信息请参见。
     * {@link 106407当前渲染节点从FrameNode获取，FrameNode被废弃或不再使用}。
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE = 106407,
    /**
     * 当前节点不处于被采用状态。错误码的详细信息请参见。
     * {@link 106408当前节点未处于启用状态}。
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_NOT_ADOPTED_NODE = 106408,
    /**
     * 当前节点不可聚焦。具体错误码请参见{@link 150001组件不可聚焦}。
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE = 150001,
    /**
     * 当前节点的祖先是不可聚焦的。错误码的详细信息请参见。
     * {@link 150002祖先组件不可聚焦}。
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE_ANCESTOR = 150002,
    /**
     * 当前节点不存在。错误码请参见{@link 150003组件不存在}。
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT = 150003,
    /**
     * 抓拍超时。详细信息请参见{@link快照错误码}。
     * @since 15
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT = 160002,
    /**
     * 不支持提供的颜色空间或动态范围模式。详细信息请参见{@link快照错误码}。
     * @since 23
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_MODE_NOT_SUPPORTED = 160003,
    /**
     * 离屏节点抓拍不支持色彩空间或动态范围模式的**isAuto**设置。
     * 详细信息请参见{@link快照错误码}。
     * @since 23
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_AUTO_NOT_SUPPORTED = 160004,
    /**
     * 组件不是可滚动容器。请参见{@link 交互事件错误码}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NON_SCROLLABLE_CONTAINER = 180001,
    /**
     * 缓冲区不够大。请参见{@link 交互事件错误码}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH = 180002,
    /**
     * 事件不是克隆事件。请参见{@link 交互事件错误码}。
     * @since 15
     */
    ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT = 180003,
    /**
     * 组件状态异常。请参见{@link 交互事件错误码}。
     * @since 15
     */
    ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL = 180004,
    /**
     * 没有组件命中响应事件。请参见{@link 交互事件错误码}。
     * @since 15
     */
    ARKUI_ERROR_CODE_POST_CLONED_NO_COMPONENT_HIT_TO_RESPOND_TO_THE_EVENT = 180005,
    /**
     * 不支持的输入事件类型。
     * @since 20
     */
    ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED = 180006,
    /**
     * 无效的样式字符串。请参见{@link样式字符串错误码}。
     * @since 14
     */
    ARKUI_ERROR_CODE_INVALID_STYLED_STRING = 180101,
    /**
     * 无效的UIContext对象。详细信息请参见{@link UI上下文错误码}。
     * @since 18
     */
    ARKUI_ERROR_CODE_UI_CONTEXT_INVALID = 190001,
    /**
     * 回调函数无效。详细信息请参见{@link UI上下文错误码}。
     * @since 18
     */
    ARKUI_ERROR_CODE_CALLBACK_INVALID = 190002,
    /**
     * 不支持手势识别器类型。请参见{@link 交互事件错误码}。
     * @since 18
     */
    ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED = 180102,
    /**
     * 当前阶段不允许该操作。详细信息请参见{@link 拖拽事件错误码}。
     * @since 19
     */
    ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED = 190004
} ArkUI_ErrorCode;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_ERROR_CODE_H
/** @} */