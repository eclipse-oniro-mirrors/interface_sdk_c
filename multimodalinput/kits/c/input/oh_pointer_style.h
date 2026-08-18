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
 * @brief Provides C APIs of the multimodal input module, supporting event processing for various input devices such as
 *  touch, key, and mouse. It enables unified access to multiple devices, improving development efficiency and
 *  application interaction experience.
 *
 * @since 12
 */

/**
 * @brief Defines the mouse pointer styles.
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
 * @brief Enumerates the pointer styles.
 *
 * @since 22
 */
typedef enum Input_PointerStyle {
    /**
     * @brief Cursor style displayed when no specific style is set by the application.
     * @since 22
     */
    DEFAULT = 0,

    /**
     * @brief East arrow
     * @since 22
     */
    EAST = 1,

    /**
     * @brief West arrow
     * @since 22
     */
    WEST = 2,

    /**
     * @brief South arrow
     * @since 22
     */
    SOUTH = 3,

    /**
     * @brief North arrow
     * @since 22
     */
    NORTH = 4,

    /**
     * @brief West-east arrow
     * @since 22
     */
    WEST_EAST = 5,

    /**
     * @brief North-south arrow
     * @since 22
     */
    NORTH_SOUTH = 6,

    /**
     * @brief North-east arrow
     * @since 22
     */
    NORTH_EAST = 7,

    /**
     * @brief North-west arrow
     * @since 22
     */
    NORTH_WEST = 8,

    /**
     * @brief South-east arrow
     * @since 22
     */
    SOUTH_EAST = 9,

    /**
     * @brief South-west arrow
     * @since 22
     */
    SOUTH_WEST = 10,

    /**
     * @brief North-east and south-west adjustment
     * @since 22
     */
    NORTH_EAST_SOUTH_WEST = 11,

    /**
     * @brief North-west and south-east adjustment
     * @since 22
     */
    NORTH_WEST_SOUTH_EAST = 12,

    /**
     * @brief Cross (accurate selection)
     * @since 22
     */
    CROSS = 13,

    /**
     * @brief Copy.
     * @since 22
     */
    CURSOR_COPY = 14,

    /**
     * @brief Forbid
     * @since 22
     */
    CURSOR_FORBID = 15,

    /**
     * @brief Color picker
     * @since 22
     */
    COLOR_SUCKER = 16,

    /**
     * @brief Grabbing hand
     * @since 22
     */
    HAND_GRABBING = 17,

    /**
     * @brief Opening hand
     * @since 22
     */
    HAND_OPEN = 18,

    /**
     * @brief Hand-shaped pointer
     * @since 22
     */
    HAND_POINTING = 19,

    /**
     * @brief Help
     * @since 22
     */
    HELP = 20,

    /**
     * @brief Move
     * @since 22
     */
    MOVE = 21,

    /**
     * @brief Left and right resizing
     * @since 22
     */
    RESIZE_LEFT_RIGHT = 22,

    /**
     * @brief Up and down resizing
     * @since 22
     */
    RESIZE_UP_DOWN = 23,

    /**
     * @brief Screenshot crosshair
     * @since 22
     */
    SCREENSHOT_CHOOSE = 24,

    /**
     * @brief Screenshot
     * @since 22
     */
    SCREENSHOT_CURSOR = 25,

    /**
     * @brief Text selection
     * @since 22
     */
    TEXT_CURSOR = 26,

    /**
     * @brief Zoom in
     * @since 22
     */
    ZOOM_IN = 27,

    /**
     * @brief Zoom out
     * @since 22
     */
    ZOOM_OUT = 28,

    /**
     * @brief Scrolling east
     * @since 22
     */
    MIDDLE_BTN_EAST = 29,

    /**
     * @brief Scrolling west
     * @since 22
     */
    MIDDLE_BTN_WEST = 30,

    /**
     * @brief Scrolling south
     * @since 22
     */
    MIDDLE_BTN_SOUTH = 31,

    /**
     * @brief Scrolling north
     * @since 22
     */
    MIDDLE_BTN_NORTH = 32,

    /**
     * @brief Scrolling north-south
     * @since 22
     */
    MIDDLE_BTN_NORTH_SOUTH = 33,

    /**
     * @brief Scrolling north-east
     * @since 22
     */
    MIDDLE_BTN_NORTH_EAST = 34,

    /**
     * @brief Scrolling north-west
     * @since 22
     */
    MIDDLE_BTN_NORTH_WEST = 35,

    /**
     * @brief Scrolling south-east
     * @since 22
     */
    MIDDLE_BTN_SOUTH_EAST = 36,

    /**
     * @brief Scrolling south-west
     * @since 22
     */
    MIDDLE_BTN_SOUTH_WEST = 37,

    /**
     * @brief Moving as a cone in four directions
     * @since 22
     */
    MIDDLE_BTN_NORTH_SOUTH_WEST_EAST = 38,

    /**
     * @brief Horizontal text selection
     * @since 22
     */
    HORIZONTAL_TEXT_CURSOR = 39,

    /**
     * @brief Cross
     * @since 22
     */
    CURSOR_CROSS = 40,

    /**
     * @brief Circle
     * @since 22
     */
    CURSOR_CIRCLE = 41,

    /**
     * @brief Loading
     * @since 22
     */
    LOADING = 42,

    /**
     * @brief Running in the background
     * @since 22
     */
    RUNNING = 43,

    /**
     * @brief Scrolling east-west
     * @since 22
     */
    MIDDLE_BTN_EAST_WEST = 44,

    /**
     * @brief Running in the background (extension 1)
     * @since 22
     */
    RUNNING_LEFT = 45,

    /**
     * @brief Running in the background (extension 2)
     * @since 22
     */
    RUNNING_RIGHT = 46,

    /**
     * @brief Custom circular pointer
     * @since 22
     */
    AECH_DEVELOPER_DEFINED_ICON = 47,

    /**
     * @brief Screen recording
     * @since 22
     */
    SCREENRECORDER_CURSOR = 48,

    /**
     * @brief Floating This pointer can be used only when the stylus enters the air mouse mode and cannot be directly
     * set.<br>
     * In air mouse mode, you can rotate the stylus in the air to control the movement of the virtual pointer on the
     * screen and press the button on the stylus to turn pages up or down. This mode is used PPT presentation and air
     * gesture control.
     * @since 22
     */
    LASER_CURSOR = 49,

    /**
     * @brief Click This pointer can be used only when the stylus enters the air mouse mode and cannot be directly
     * set.<br>In air mouse mode, you can rotate the stylus in the air to control the movement of the virtual pointer
     * on the screen and press the button on the stylus to turn pages up or down. This mode is used PPT presentation
     * and air gesture control.
     * @since 22
     */
    LASER_CURSOR_DOT = 50,

    /**
     * @brief Laser pointer This pointer can be used only when the stylus enters the air mouse mode and cannot be
     * directly set.
     * <br>In air mouse mode, you can rotate the stylus in the air to control the movement of the virtual pointer on
     * the screen and press the button on the stylus to turn pages up or down. This mode is used PPT presentation and
     * air gesture control.
     * @since 22
     */
    LASER_CURSOR_DOT_RED = 51,
    /**
     * @brief Custom pointer. You can use the {@link OH_Input_SetCustomCursor} to set a custom pointer, but not the
     * {@link OH_Input_SetPointerStyle}.
     * @since 22
     */
    DEVELOPER_DEFINED_ICON = -100
} Input_PointerStyle;

#ifdef __cplusplus
}
#endif

#endif /* OH_POINTER_STYLE_H */
/** @} */