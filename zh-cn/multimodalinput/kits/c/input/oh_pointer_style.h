/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
 * @brief 鼠标光标的样式。
 *
 * @file oh_pointer_style.h
 * @include <multimodalinput/oh_pointer_style.h>
 *
 * @kit InputKit
 * @syscap SystemCapability.MultimodalInput.Input.Core
 * @library libohinput.so
 * @since 22
 */
#ifndef OH_POINTER_STYLE_H
#define OH_POINTER_STYLE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 鼠标光标样式。
 *
 * @since 22
 */
typedef enum Input_PointerStyle {
    /**
     * @brief 应用未设置时显示的光标样式。
     * @since 22
     */
    DEFAULT = 0,

    /**
     * @brief 向东箭头
     * @since 22
     */
    EAST = 1,

    /**
     * @brief 向西箭头
     * @since 22
     */
    WEST = 2,

    /**
     * @brief 向南箭头
     * @since 22
     */
    SOUTH = 3,

    /**
     * @brief 向北箭头
     * @since 22
     */
    NORTH = 4,

    /**
     * @brief 向西东箭头
     * @since 22
     */
    WEST_EAST = 5,

    /**
     * @brief 向北南箭头
     * @since 22
     */
    NORTH_SOUTH = 6,

    /**
     * @brief 向东北箭头
     * @since 22
     */
    NORTH_EAST = 7,

    /**
     * @brief 向西北箭头
     * @since 22
     */
    NORTH_WEST = 8,

    /**
     * @brief 向东南箭头
     * @since 22
     */
    SOUTH_EAST = 9,

    /**
     * @brief 向西南箭头
     * @since 22
     */
    SOUTH_WEST = 10,

    /**
     * @brief 东北西南调整
     * @since 22
     */
    NORTH_EAST_SOUTH_WEST = 11,

    /**
     * @brief 西北东南调整
     * @since 22
     */
    NORTH_WEST_SOUTH_EAST = 12,

    /**
     * @brief 准确选择
     * @since 22
     */
    CROSS = 13,

    /**
     * @brief 复制
     * @since 22
     */
    CURSOR_COPY = 14,

    /**
     * @brief 不可用
     * @since 22
     */
    CURSOR_FORBID = 15,

    /**
     * @brief 取色器
     * @since 22
     */
    COLOR_SUCKER = 16,

    /**
     * @brief 并拢的手
     * @since 22
     */
    HAND_GRABBING = 17,

    /**
     * @brief 张开的手
     * @since 22
     */
    HAND_OPEN = 18,

    /**
     * @brief 手形指针
     * @since 22
     */
    HAND_POINTING = 19,

    /**
     * @brief 帮助选择
     * @since 22
     */
    HELP = 20,

    /**
     * @brief 移动
     * @since 22
     */
    MOVE = 21,

    /**
     * @brief 内部左右调整
     * @since 22
     */
    RESIZE_LEFT_RIGHT = 22,

    /**
     * @brief 内部上下调整
     * @since 22
     */
    RESIZE_UP_DOWN = 23,

    /**
     * @brief 截图十字准星
     * @since 22
     */
    SCREENSHOT_CHOOSE = 24,

    /**
     * @brief 截图
     * @since 22
     */
    SCREENSHOT_CURSOR = 25,

    /**
     * @brief 文本选择
     * @since 22
     */
    TEXT_CURSOR = 26,

    /**
     * @brief 放大
     * @since 22
     */
    ZOOM_IN = 27,

    /**
     * @brief 缩小
     * @since 22
     */
    ZOOM_OUT = 28,

    /**
     * @brief 向东滚动
     * @since 22
     */
    MIDDLE_BTN_EAST = 29,

    /**
     * @brief 向西滚动
     * @since 22
     */
    MIDDLE_BTN_WEST = 30,

    /**
     * @brief 向南滚动
     * @since 22
     */
    MIDDLE_BTN_SOUTH = 31,

    /**
     * @brief 向北滚动
     * @since 22
     */
    MIDDLE_BTN_NORTH = 32,

    /**
     * @brief 向南北滚动
     * @since 22
     */
    MIDDLE_BTN_NORTH_SOUTH = 33,

    /**
     * @brief 向东北滚动
     * @since 22
     */
    MIDDLE_BTN_NORTH_EAST = 34,

    /**
     * @brief 向西北滚动
     * @since 22
     */
    MIDDLE_BTN_NORTH_WEST = 35,

    /**
     * @brief 向东南滚动
     * @since 22
     */
    MIDDLE_BTN_SOUTH_EAST = 36,

    /**
     * @brief 向西南滚动
     * @since 22
     */
    MIDDLE_BTN_SOUTH_WEST = 37,

    /**
     * @brief 四向锥形移动
     * @since 22
     */
    MIDDLE_BTN_NORTH_SOUTH_WEST_EAST = 38,

    /**
     * @brief 水平文本选择
     * @since 22
     */
    HORIZONTAL_TEXT_CURSOR = 39,

    /**
     * @brief 十字光标
     * @since 22
     */
    CURSOR_CROSS = 40,

    /**
     * @brief 圆形光标
     * @since 22
     */
    CURSOR_CIRCLE = 41,

    /**
     * @brief 正在载入动画光标
     * @since 22
     */
    LOADING = 42,

    /**
     * @brief 后台运行中动画光标
     * @since 22
     */
    RUNNING = 43,

    /**
     * @brief 向东西滚动
     * @since 22
     */
    MIDDLE_BTN_EAST_WEST = 44,

    /**
     * @brief 后台运行中动画光标(拓展1)
     * @since 22
     */
    RUNNING_LEFT = 45,

    /**
     * @brief 后台运行中动画光标(拓展2)
     * @since 22
     */
    RUNNING_RIGHT = 46,

    /**
     * @brief 圆形自定义光标
     * @since 22
     */
    AECH_DEVELOPER_DEFINED_ICON = 47,

    /**
     * @brief 录屏光标
     * @since 22
     */
    SCREENRECORDER_CURSOR = 48,

    /**
     * @brief 悬浮光标。手写笔进入空鼠模式时使用该光标，无法直接设置。<br>空鼠模式支持通过手写笔在空中转动来控制屏幕上虚拟光标的移动，并借助笔身按键实现上下翻页功能，用于演示PPT、隔空操作等场景。
     * @since 22
     */
    LASER_CURSOR = 49,

    /**
     * @brief 点击光标。手写笔进入空鼠模式时使用该光标，无法直接设置。<br>空鼠模式支持通过手写笔在空中转动来控制屏幕上虚拟光标的移动，并借助笔身按键实现上下翻页功能，用于演示PPT、隔空操作等场景。
     * @since 22
     */
    LASER_CURSOR_DOT = 50,

    /**
     * @brief 激光笔光标。手写笔进入空鼠模式时使用该光标，无法直接设置。<br>空鼠模式支持通过手写笔在空中转动来控制屏幕上虚拟光标的移动，并借助笔身按键实现上下翻页功能，用于演示PPT、隔空操作等场景。
     * @since 22
     */
    LASER_CURSOR_DOT_RED = 51,
    /**
     * @brief 自定义光标，开发者可使用{@link OH_Input_SetCustomCursor}设置自定义光标，不支持使用{@link OH_Input_SetPointerStyle}直接设置。
     * @since 22
     */
    DEVELOPER_DEFINED_ICON = -100
} Input_PointerStyle;

#ifdef __cplusplus
}
#endif

#endif /* OH_POINTER_STYLE_H */
/** @} */