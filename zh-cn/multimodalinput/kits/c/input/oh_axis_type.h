/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @addtogroup input
 * @{
 *
 * @brief 提供多模态输入域的C接口，支持触控、按键、鼠标等多种输入设备的事件处理，统一接入多设备，提升开发效率与应用交互体验。
 *
 * @since 12
 */

/**
 *
 * @brief 输入设备的轴事件结构和枚举，轴类型定义了输入设备在不同交互场景下的物理行为特征，系统通过轴类型来区分和传递不同的手势交互信息。
 *
 * @file oh_axis_type.h
 * @include <multimodalinput/oh_axis_type.h>
 *
 * @kit InputKit
 * @syscap SystemCapability.MultimodalInput.Input.Core
 * @library libohinput.so
 * @since 12
 */

#ifndef OH_AXIS_TYPE_H
#define OH_AXIS_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 输入设备的轴类型。
 *
 * @since 12
 */
typedef enum InputEvent_AxisType {
    /**
     * @brief 未知轴类型，通常作为初始值。
     * @since 12
     */
    AXIS_TYPE_UNKNOWN = 0,

    /**
     * @brief 垂直滚动轴，当您滚动鼠标滚轮或在触控板上进行单指或双指滑动时，垂直滚动轴的状态改变。
     * @since 12
     */
    AXIS_TYPE_SCROLL_VERTICAL = 1,

    /**
     * @brief 水平滚动轴，当您滚动鼠标滚轮或在触控板上进行双指滑动时，水平滚动轴的状态发生变化。
     * @since 12
     */
    AXIS_TYPE_SCROLL_HORIZONTAL = 2,

    /**
     * @brief 捏合轴，用于描述触控板上的双指捏合手势。
     * @since 12
     */
    AXIS_TYPE_PINCH = 3,

    /**
     * @brief 旋转轴，用于描述触控板上的双指旋转手势。
     * @since 12
     */
    AXIS_TYPE_ROTATE = 4
} InputEvent_AxisType;

/**
 * @brief 输入设备的轴事件类型。
 *
 * @since 12
 */
typedef enum InputEvent_AxisEventType {
    /**
     * @brief 双指捏合事件，包含AXIS_TYPE_PINCH和AXIS_TYPE_ROTATE两种{@link InputEvent_AxisType}。
     *
     * @since 12
     */
    AXIS_EVENT_TYPE_PINCH = 1,
    /**
     * @brief 滚轴事件，包含AXIS_TYPE_SCROLL_VERTICAL和AXIS_TYPE_SCROLL_HORIZONTAL两种{@link InputEvent_AxisType}，
     * 其中鼠标滚轮事件仅包含AXIS_TYPE_SCROLL_VERTICAL一种{@link InputEvent_AxisType}。
     *
     * @since 12
     */
    AXIS_EVENT_TYPE_SCROLL = 2
} InputEvent_AxisEventType;

/**
 * @brief 轴事件动作。
 *
 * @since 12
 */
typedef enum InputEvent_AxisAction {
    /**
     * @brief 轴事件取消。
     * @since 12
     */
    AXIS_ACTION_CANCEL = 0,

    /**
     * @brief 轴事件开始。
     * @since 12
     */
    AXIS_ACTION_BEGIN = 1,

    /**
     * @brief 轴事件更新。
     * @since 12
     */
    AXIS_ACTION_UPDATE = 2,

    /**
     * @brief 轴事件结束。
     * @since 12
     */
    AXIS_ACTION_END = 3
} InputEvent_AxisAction;

#ifdef __cplusplus
}
#endif
#endif
/** @} */