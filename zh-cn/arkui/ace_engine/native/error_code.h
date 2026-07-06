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
 * @brief 定义错误码枚举值。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 无错误。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NO_ERROR = 0,
    /**
     * @brief 参数错误。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_PARAM_INVALID = 401,
    /**
     * @brief 接口初始化错误。
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_CAPI_INIT_ERROR = 500,
    /**
     * @brief 出现内部错误，例如内部环境错误导致失败，或者由于内部执行失败导致操作失败。
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_INTERNAL_ERROR = 100001,
    /**
     * @brief 参数错误。错误码的详细介绍请参见{@link 100023 参数错误}。
     *
     * @since 21
     */
    ARKUI_ERROR_CODE_PARAM_ERROR = 100023,
    /**
     * @brief 当前XComponent状态异常，方法调用失败。错误码的详细介绍请参见{@link XComponent组件错误码}。
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_XCOMPONENT_STATE_INVALID = 103501,
    /**
     * @brief 组件不支持特定的属性或者事件。错误码的详细介绍请参见{@link 交互事件错误码}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ATTRIBUTE_OR_EVENT_NOT_SUPPORTED = 106102,
    /**
     * @brief 不支持对ArkTS创建的节点执行对应的操作。错误码的详细介绍请参见{@link 106103 对应的操作不支持ArkTS创建的节点}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ARKTS_NODE_NOT_SUPPORTED = 106103,
    /**
     * @brief 懒加载适配器未绑定到组件上。错误码的详细介绍请参见{@link 106104 适配器未绑定}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ADAPTER_NOT_BOUND = 106104,
    /**
     * @brief 适配器已存在。错误码的详细介绍请参见{@link 106105 适配器已存在}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_ADAPTER_EXIST = 106105,
    /**
     * @brief 对应节点已存在子节点，无法添加适配器。错误码的详细介绍请参见{@link 106106 子节点已存在}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_CHILD_NODE_EXIST = 106106,
    /**
     * @brief 组件事件中参数长度超限。错误码的详细介绍请参见{@link 106107 参数下标越界}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INDEX_OUT_OF_RANGE = 106107,
    /**
     * @brief 组件事件中不存在该数据。错误码的详细介绍请参见{@link 106108 数据不存在}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_EVENT_PARAM_INVALID = 106108,
    /**
     * @brief 组件事件不支持返回值。错误码的详细介绍请参见{@link 106109 不支持返回值}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_EVENT_NO_RETURN = 106109,
    /**
     * @brief 暂不支持该事件类型。错误码的详细介绍请参见{@link 106110 暂不支持该事件类型}。
     *
     * @since 21
     */
    ARKUI_ERROR_CODE_NODE_UNSUPPORTED_EVENT_TYPE = 106110,
    /**
     * @brief 传入的索引值非法。
     * 错误码的详细介绍请参见{@link 106200 传入的索引值非法}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NODE_INDEX_INVALID = 106200,
    /**
     * @brief 查询路由导航信息失败。
     * 错误码的详细介绍请参见{@link 106201 查询路由导航信息失败}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_GET_INFO_FAILED = 106201,
    /**
     * @brief 传入的buffer size异常（数据过大）。
     * 错误码的详细介绍请参见{@link 106202 传入的buffer size异常}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR = 106202,
    /**
     * @brief 传入的节点未挂载到组件树上。错误码的详细介绍请参见{@link 106203 传入的节点未挂载到组件树上}。
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_NODE_NOT_ON_MAIN_TREE = 106203,
    /**
     * @brief 不支持在非UI线程操作传入的节点。错误码的详细介绍请参见{@link 106204 不支持在非UI线程操作传入的节点}。
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_ON_INVALID_THREAD = 106204,
    /**
     * @brief 反色能力入参错误。错误码的详细介绍请参见{@link 106205 反色能力入参错误}。
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_FORCE_DARK_CONFIG_INVALID = 106205,
    /**
     * @brief 节点已被接纳为附属节点。错误码的详细介绍请参见{@link 106206 节点已被接纳为附属节点}。
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_IS_ADOPTED = 106206,
    /**
     * @brief 被接纳的节点已有父节点。错误码的详细介绍请参见{@link 106207 被接纳的附属节点已有父节点}。
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_HAS_PARENT = 106207,
    /**
     * @brief 节点无法被接纳为附属节点。错误码的详细介绍请参见{@link 106208 节点无法被接纳为附属节点}。
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_CAN_NOT_BE_ADOPTED = 106208,
    /**
     * @brief 节点无法接纳其他节点。错误码的详细介绍请参见{@link 106209 节点无法接纳其他节点}。
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_CAN_NOT_ADOPT_TO = 106209,
    /**
     * @brief 节点不是被目标节点接纳的附属节点。错误码的详细介绍请参见{@link 106210 节点不是被目标节点接纳的附属节点}。
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_NODE_IS_NOT_IN_ADOPTED_CHILDREN = 106210,
    /**
     * @brief 当前节点不是自定义节点。错误码的详细介绍请参见{@link 渲染节点错误码}。
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_NOT_CUSTOM_NODE = 106401,
    /**
     * @brief 当前节点已存在子节点。错误码的详细介绍请参见{@link 渲染节点错误码}。
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_CHILD_EXISTED = 106402,
    /**
     * @brief 当前渲染节点存在父组件。错误码的详细介绍请参见{@link 渲染节点错误码}。
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_RENDER_PARENT_EXISTED = 106403,
    /**
     * @brief 未找到对应的渲染子节点。错误码的详细介绍请参见{@link 渲染节点错误码}。
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_RENDER_CHILD_NOT_EXIST = 106404,
    /**
     * @brief 参数值超出范围。错误码的详细介绍请参见{@link 渲染节点错误码}。
     *
     * @since 20
     */
    ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE = 106405,
    /**
     * @brief 当前渲染节点从{@link FrameNode}中获取。错误码的详细介绍请参见{@link 106406 当前渲染节点从FrameNode中获取}。
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_IS_FROM_FRAME_NODE = 106406,
    /**
     * @brief 当前渲染节点从{@link FrameNode}中获取且该{@link FrameNode}已被取消接纳为附属节点或销毁。错误码的详细介绍请参见
     * {@link 106407 当前渲染节点从FrameNode中获取且该FrameNode已被取消接纳为附属节点或销毁}。
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_HAS_INVALID_FRAME_NODE = 106407,
    /**
     * @brief 当前节点不处于被接纳状态。错误码的详细介绍请参见{@link 106408 当前节点不处于被接纳状态}。
     *
     * @since 22
     */
    ARKUI_ERROR_CODE_RENDER_NOT_ADOPTED_NODE = 106408,
    /**
     * @brief 当前节点无法获得焦点。错误码的详细介绍请参见{@link 150001 节点无法获得焦点}。
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE = 150001,
    /**
     * @brief 当前节点对应的祖先节点中存在无法获焦节点。错误码的详细介绍请参见{@link 150002 祖先节点无法获得焦点}。
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_FOCUSABLE_ANCESTOR = 150002,
    /**
     * @brief 当前节点不存在。错误码的详细介绍请参见{@link 150003 节点不存在}。
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT = 150003,
    /**
     * @brief 截图超时。错误码的详细介绍请参见{@link 截图错误码}。
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_TIMEOUT = 160002,
    /**
     * @brief 截图选项不支持的色彩空间或动态范围模式。错误码的详细介绍请参见{@link 截图错误码}。
     *
     * @since 23
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_MODE_NOT_SUPPORTED = 160003,
    /**
     * @brief 离屏节点截图不支持色彩空间或动态范围模式的isAuto参数设置为true。错误码的详细介绍请参见{@link 截图错误码}。
     *
     * @since 23
     */
    ARKUI_ERROR_CODE_COMPONENT_SNAPSHOT_AUTO_NOT_SUPPORTED = 160004,
    /**
     * @brief 非滚动类容器。错误码的详细介绍请参见{@link 交互事件错误码}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_NON_SCROLLABLE_CONTAINER = 180001,
    /**
     * @brief 存储区大小不足。错误码的详细介绍请参见{@link 交互事件错误码}。
     *
     * @since 12
     */
    ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH = 180002,
    /**
     * @brief 该事件不是克隆事件。错误码的详细介绍请参见{@link 交互事件错误码}。
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT = 180003,
    /**
     * @brief 组件状态异常。错误码的详细介绍请参见{@link 交互事件错误码}。
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL = 180004,
    /**
     * @brief 未命中可响应事件的组件。错误码的详细介绍请参见{@link 交互事件错误码}。
     *
     * @since 15
     */
    ARKUI_ERROR_CODE_POST_CLONED_NO_COMPONENT_HIT_TO_RESPOND_TO_THE_EVENT = 180005,
    /**
     * @brief 接口不支持此输入事件类型。
     *
     * @since 20
     */
    ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED = 180006,
    /**
     * @brief 无效的属性字符串。错误码的详细介绍请参见{@link 属性字符串错误码}。
     *
     * @since 14
     */
    ARKUI_ERROR_CODE_INVALID_STYLED_STRING = 180101,
    /**
     * @brief 无效的UIContext对象。错误码的详细介绍请参见{@link UI上下文错误码}。
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_UI_CONTEXT_INVALID = 190001,
    /**
     * @brief 无效的回调函数。错误码的详细介绍请参见{@link UI上下文错误码}。
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_CALLBACK_INVALID = 190002,
    /**
     * @brief 不支持手势识别器类型。错误码的详细介绍请参见{@link 交互事件错误码}。
     *
     * @since 18
     */
    ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED = 180102,
    /**
     * @brief 当前阶段不允许该操作。错误码的详细介绍请参见{@link 拖拽事件错误码}。
     *
     * @since 19
     */
    ARKUI_ERROR_CODE_DRAG_DROP_OPERATION_NOT_ALLOWED = 190004,
} ArkUI_ErrorCode;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_ERROR_CODE_H
/** @} */
