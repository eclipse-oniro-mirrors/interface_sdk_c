/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @brief Provides the C interface in the multi-modal input domain.
 *
 * @since 12
 */

/**
 * @file oh_axis_type.h
 *
 * @brief Defines the device axis event struct and enumerates device axis events. The axis type defines the physical
 * behavior characteristics of an input device in different interaction scenarios. The system uses the axis type to
 * distinguish and transmit different gesture interaction information.
 *
 * @kit InputKit
 * @syscap SystemCapability.MultimodalInput.Input.Core
 * @library liboh_input.so
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
     * 未知轴类型，通常作为初始值。
     * @since 12
     */
    AXIS_TYPE_UNKNOWN,

    /**
     * 垂直滚动轴，当您滚动鼠标滚轮或在触控板上进行单指或双指滑动时，垂直滚动轴的状态改变。
     * @since 12
     */
    AXIS_TYPE_SCROLL_VERTICAL,

    /**
     * 水平滚动轴，当您滚动鼠标滚轮或在触控板上进行双指滑动时，水平滚动轴的状态发生变化。
     * @since 12
     */
    AXIS_TYPE_SCROLL_HORIZONTAL,

    /**
     * 捏合轴，用于描述触控板上的双指捏合手势。
     * @since 12
     */
    AXIS_TYPE_PINCH,

    /**
     * 旋转轴，用于描述触控板上的双指旋转手势。
     * @since 12
     */
    AXIS_TYPE_ROTATE
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
     * 轴事件取消。
     * @since 12
     */
    AXIS_ACTION_CANCEL = 0,

    /**
     * 轴事件开始。
     * @since 12
     */
    AXIS_ACTION_BEGIN,

    /**
     * 轴事件更新。
     * @since 12
     */
    AXIS_ACTION_UPDATE,

    /**
     * 轴事件结束。
     * @since 12
     */
    AXIS_ACTION_END
} InputEvent_AxisAction;

#ifdef __cplusplus
}
#endif
#endif

/** @} */