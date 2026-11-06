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
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides the general key event APIs of ArkUI on the native side.
 *
 * @since 14
 */

/**
 * @file native_key_event.h
 *
 * @brief 提供NativeKeyEvent相关接口定义。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 14
 */

#ifndef ARKUI_NATIVE_KEY_EVENT_H
#define ARKUI_NATIVE_KEY_EVENT_H

#include <stdint.h>
#include <stdbool.h>

#include "native_type.h"
#include "ui_input_event.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 按键事件的键码。
 *
 * @since 14
 */
typedef enum {
    /**
     * 未知按键。
     */
    ARKUI_KEYCODE_UNKNOWN = -1,

    /**
     * 功能（Fn）键。
     */
    ARKUI_KEYCODE_FN = 0,

    /**
     * 音量增加键。
     */
    ARKUI_KEYCODE_VOLUME_UP = 16,

    /**
     * 音量减小键。
     */
    ARKUI_KEYCODE_VOLUME_DOWN = 17,

    /**
     * 电源键。
     */
    ARKUI_KEYCODE_POWER = 18,

    /**
     * 拍照键。
     */
    ARKUI_KEYCODE_CAMERA = 19,

    /**
     * 扬声器静音键。
     */
    ARKUI_KEYCODE_VOLUME_MUTE = 22,

    /**
     * 话筒静音键。
     */
    ARKUI_KEYCODE_MUTE = 23,

    /**
     * 亮度调节按键，调亮。
     */
    ARKUI_KEYCODE_BRIGHTNESS_UP = 40,

    /**
     * 亮度调节按键，调暗。
     */
    ARKUI_KEYCODE_BRIGHTNESS_DOWN = 41,

    /**
     * 按键'0'。
     */
    ARKUI_KEYCODE_0 = 2000,

    /**
     * 按键'1'。
     */
    ARKUI_KEYCODE_1 = 2001,

    /**
     * 按键'2'。
     */
    ARKUI_KEYCODE_2 = 2002,

    /**
     * 按键'3'。
     */
    ARKUI_KEYCODE_3 = 2003,

    /**
     * 按键'4'。
     */
    ARKUI_KEYCODE_4 = 2004,

    /**
     * 按键'5'。
     */
    ARKUI_KEYCODE_5 = 2005,

    /**
     * 按键'6'。
     */
    ARKUI_KEYCODE_6 = 2006,

    /**
     * 按键'7'。
     */
    ARKUI_KEYCODE_7 = 2007,

    /**
     * 按键'8'。
     */
    ARKUI_KEYCODE_8 = 2008,

    /**
     * 按键'9'。
     */
    ARKUI_KEYCODE_9 = 2009,

    /**
     * 按键'+'。
     */
    ARKUI_KEYCODE_STAR = 2010,

    /**
     * 按键'#'。
     */
    ARKUI_KEYCODE_POUND = 2011,

    /**
     * 导航键，向上。
     */
    ARKUI_KEYCODE_DPAD_UP = 2012,

    /**
     * 导航键，向下。
     */
    ARKUI_KEYCODE_DPAD_DOWN = 2013,

    /**
     * 导航键，向左。
     */
    ARKUI_KEYCODE_DPAD_LEFT = 2014,

    /**
     * 导航键，向右。
     */
    ARKUI_KEYCODE_DPAD_RIGHT = 2015,

    /**
     * 导航键，确定键。
     */
    ARKUI_KEYCODE_DPAD_CENTER = 2016,

    /**
     * 按键'A'。
     */
    ARKUI_KEYCODE_A = 2017,

    /**
     * 按键'B'。
     */
    ARKUI_KEYCODE_B = 2018,

    /**
     * 按键'C'。
     */
    ARKUI_KEYCODE_C = 2019,

    /**
     * 按键'D'。
     */
    ARKUI_KEYCODE_D = 2020,

    /**
     * 按键'E'。
     */
    ARKUI_KEYCODE_E = 2021,

    /**
     * 按键'F'。
     */
    ARKUI_KEYCODE_F = 2022,

    /**
     * 按键'G'。
     */
    ARKUI_KEYCODE_G = 2023,

    /**
     * 按键'H'。
     */
    ARKUI_KEYCODE_H = 2024,

    /**
     * 按键'I'。
     */
    ARKUI_KEYCODE_I = 2025,

    /**
     * 按键'J'。
     */
    ARKUI_KEYCODE_J = 2026,

    /**
     * 按键'K'。
     */
    ARKUI_KEYCODE_K = 2027,

    /**
     * 按键'L'。
     */
    ARKUI_KEYCODE_L = 2028,

    /**
     * 按键'M'。
     */
    ARKUI_KEYCODE_M = 2029,

    /**
     * 按键'N'。
     */
    ARKUI_KEYCODE_N = 2030,

    /**
     * 按键'O'。
     */
    ARKUI_KEYCODE_O = 2031,

    /**
     * 按键'P'。
     */
    ARKUI_KEYCODE_P = 2032,

    /**
     * 按键'Q'。
     */
    ARKUI_KEYCODE_Q = 2033,

    /**
     * 按键'R'。
     */
    ARKUI_KEYCODE_R = 2034,

    /**
     * 按键'S'。
     */
    ARKUI_KEYCODE_S = 2035,

    /**
     * 按键'T'。
     */
    ARKUI_KEYCODE_T = 2036,

    /**
     * 按键'U'。
     */
    ARKUI_KEYCODE_U = 2037,

    /**
     * 按键'V'。
     */
    ARKUI_KEYCODE_V = 2038,

    /**
     * 按键'W'。
     */
    ARKUI_KEYCODE_W = 2039,

    /**
     * 按键'X'。
     */
    ARKUI_KEYCODE_X = 2040,

    /**
     * 按键'Y'。
     */
    ARKUI_KEYCODE_Y = 2041,

    /**
     * 按键'Z'。
     */
    ARKUI_KEYCODE_Z = 2042,

    /**
     * 按键','。
     */
    ARKUI_KEYCODE_COMMA = 2043,

    /**
     * 按键'.'。
     */
    ARKUI_KEYCODE_PERIOD = 2044,

    /**
     * 左Alt键。
     */
    ARKUI_KEYCODE_ALT_LEFT = 2045,

    /**
     * 右Alt键。
     */
    ARKUI_KEYCODE_ALT_RIGHT = 2046,

    /**
     * 左Shift键。
     */
    ARKUI_KEYCODE_SHIFT_LEFT = 2047,

    /**
     * 右Shift键。
     */
    ARKUI_KEYCODE_SHIFT_RIGHT = 2048,

    /**
     * Tab键。
     */
    ARKUI_KEYCODE_TAB = 2049,

    /**
     * 空格键。
     */
    ARKUI_KEYCODE_SPACE = 2050,

    /**
     * 符号修改器按键。
     */
    ARKUI_KEYCODE_SYM = 2051,

    /**
     * 浏览器功能键，此键用于启动浏览器应用程序。
     */
    ARKUI_KEYCODE_EXPLORER = 2052,

    /**
     * 电子邮件功能键，此键用于启动电子邮件应用程序。
     */
    ARKUI_KEYCODE_ENVELOPE = 2053,

    /**
     * 回车键。
     */
    ARKUI_KEYCODE_ENTER = 2054,

    /**
     * 退格键。
     */
    ARKUI_KEYCODE_DEL = 2055,

    /**
     * 按键'`'。
     */
    ARKUI_KEYCODE_GRAVE = 2056,

    /**
     * 按键'-'。
     */
    ARKUI_KEYCODE_MINUS = 2057,

    /**
     * 按键'='。
     */
    ARKUI_KEYCODE_EQUALS = 2058,

    /**
     * 按键'['。
     */
    ARKUI_KEYCODE_LEFT_BRACKET = 2059,

    /**
     * 按键']'。
     */
    ARKUI_KEYCODE_RIGHT_BRACKET = 2060,

    /**
     * 按键'\'。
     */
    ARKUI_KEYCODE_BACKSLASH = 2061,

    /**
     * 按键';'。
     */
    ARKUI_KEYCODE_SEMICOLON = 2062,

    /**
     * 按键''' (单引号)。
     */
    ARKUI_KEYCODE_APOSTROPHE = 2063,

    /**
     * 按键'/'。
     */
    ARKUI_KEYCODE_SLASH = 2064,

    /**
     * 按键 '@'。
     */
    ARKUI_KEYCODE_AT = 2065,

    /**
     * 按键'+'。
     */
    ARKUI_KEYCODE_PLUS = 2066,

    /**
     * 菜单键。
     */
    ARKUI_KEYCODE_MENU = 2067,

    /**
     * 向上翻页键。
     */
    ARKUI_KEYCODE_PAGE_UP = 2068,

    /**
     * 向下翻页键。
     */
    ARKUI_KEYCODE_PAGE_DOWN = 2069,

    /**
     * ESC键。
     */
    ARKUI_KEYCODE_ESCAPE = 2070,

    /**
     * 删除键。
     */
    ARKUI_KEYCODE_FORWARD_DEL = 2071,

    /**
     * 左Ctrl键。
     */
    ARKUI_KEYCODE_CTRL_LEFT = 2072,

    /**
     * 右Ctrl键。
     */
    ARKUI_KEYCODE_CTRL_RIGHT = 2073,

    /**
     * 大写锁定键。
     */
    ARKUI_KEYCODE_CAPS_LOCK = 2074,

    /**
     * 滚动锁定键。
     */
    ARKUI_KEYCODE_SCROLL_LOCK = 2075,

    /**
     * 左元修改器键。
     */
    ARKUI_KEYCODE_META_LEFT = 2076,

    /**
     * 右元修改器键。
     */
    ARKUI_KEYCODE_META_RIGHT = 2077,

    /**
     * 功能键。
     */
    ARKUI_KEYCODE_FUNCTION = 2078,

    /**
     * 系统请求/打印屏幕键。
     */
    ARKUI_KEYCODE_SYSRQ = 2079,

    /**
     * Break/Pause键。
     */
    ARKUI_KEYCODE_BREAK = 2080,

    /**
     * 光标移动到开始键。
     */
    ARKUI_KEYCODE_MOVE_HOME = 2081,

    /**
     * 光标移动到末尾键。
     */
    ARKUI_KEYCODE_MOVE_END = 2082,

    /**
     * 插入键。
     */
    ARKUI_KEYCODE_INSERT = 2083,

    /**
     * 前进键。
     */
    ARKUI_KEYCODE_FORWARD = 2084,

    /**
     * 多媒体键，播放。
     */
    ARKUI_KEYCODE_MEDIA_PLAY = 2085,

    /**
     * 多媒体键，暂停。
     */
    ARKUI_KEYCODE_MEDIA_PAUSE = 2086,

    /**
     * 多媒体键，关闭。
     */
    ARKUI_KEYCODE_MEDIA_CLOSE = 2087,

    /**
     * 多媒体键，弹出。
     */
    ARKUI_KEYCODE_MEDIA_EJECT = 2088,

    /**
     * 多媒体键，录音。
     */
    ARKUI_KEYCODE_MEDIA_RECORD = 2089,

    /**
     * 按键'F1'。
     */
    ARKUI_KEYCODE_F1 = 2090,

    /**
     * 按键'F2'。
     */
    ARKUI_KEYCODE_F2 = 2091,

    /**
     * 按键'F3'。
     */
    ARKUI_KEYCODE_F3 = 2092,

    /**
     * 按键'F4'。
     */
    ARKUI_KEYCODE_F4 = 2093,

    /**
     * 按键'F5'。
     */
    ARKUI_KEYCODE_F5 = 2094,

    /**
     * 按键'F6'。
     */
    ARKUI_KEYCODE_F6 = 2095,

    /**
     * 按键'F7'。
     */
    ARKUI_KEYCODE_F7 = 2096,

    /**
     * 按键'F8'。
     */
    ARKUI_KEYCODE_F8 = 2097,

    /**
     * 按键'F9'。
     */
    ARKUI_KEYCODE_F9 = 2098,

    /**
     * 按键'F10'。
     */
    ARKUI_KEYCODE_F10 = 2099,

    /**
     * 按键'F11'。
     */
    ARKUI_KEYCODE_F11 = 2100,

    /**
     * 按键'F12'。
     */
    ARKUI_KEYCODE_F12 = 2101,

    /**
     * 小键盘锁。
     */
    ARKUI_KEYCODE_NUM_LOCK = 2102,

    /**
     * 小键盘按键'0'。
     */
    ARKUI_KEYCODE_NUMPAD_0 = 2103,

    /**
     * 小键盘按键'1'。
     */
    ARKUI_KEYCODE_NUMPAD_1 = 2104,

    /**
     * 小键盘按键'2'。
     */
    ARKUI_KEYCODE_NUMPAD_2 = 2105,

    /**
     * 小键盘按键'3'。
     */
    ARKUI_KEYCODE_NUMPAD_3 = 2106,

    /**
     * 小键盘按键'4'。
     */
    ARKUI_KEYCODE_NUMPAD_4 = 2107,

    /**
     * 小键盘按键'5'。
     */
    ARKUI_KEYCODE_NUMPAD_5 = 2108,

    /**
     * 小键盘按键'6'。
     */
    ARKUI_KEYCODE_NUMPAD_6 = 2109,

    /**
     * 小键盘按键'7'。
     */
    ARKUI_KEYCODE_NUMPAD_7 = 2110,

    /**
     * 小键盘按键'8'。
     */
    ARKUI_KEYCODE_NUMPAD_8 = 2111,

    /**
     * 小键盘按键'9'。
     */
    ARKUI_KEYCODE_NUMPAD_9 = 2112,

    /**
     * 小键盘按键'/'。
     */
    ARKUI_KEYCODE_NUMPAD_DIVIDE = 2113,

    /**
     * 小键盘按键'*'。
     */
    ARKUI_KEYCODE_NUMPAD_MULTIPLY = 2114,

    /**
     * 小键盘按键'-'。
     */
    ARKUI_KEYCODE_NUMPAD_SUBTRACT = 2115,

    /**
     * 小键盘按键'+'。
     */
    ARKUI_KEYCODE_NUMPAD_ADD = 2116,

    /**
     * 小键盘按键'.'。
     */
    ARKUI_KEYCODE_NUMPAD_DOT = 2117,

    /**
     * 小键盘按键','。
     */
    ARKUI_KEYCODE_NUMPAD_COMMA = 2118,

    /**
     * 小键盘按键回车。
     */
    ARKUI_KEYCODE_NUMPAD_ENTER = 2119,

    /**
     * 小键盘按键'='。
     */
    ARKUI_KEYCODE_NUMPAD_EQUALS = 2120,

    /**
     * 小键盘按键'('。
     */
    ARKUI_KEYCODE_NUMPAD_LEFT_PAREN = 2121,

    /**
     * 小键盘按键')'。
     */
    ARKUI_KEYCODE_NUMPAD_RIGHT_PAREN = 2122,

    /**
     * 游戏手柄按键'A'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_A = 2301,

    /**
     * 游戏手柄按键'B'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_B = 2302,

    /**
     * 游戏手柄按键'X'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_X = 2304,

    /**
     * 游戏手柄按键'Y'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_Y = 2305,

    /**
     * 游戏手柄按键'L1'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_L1 = 2307,

    /**
     * 游戏手柄按键'R1'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_R1 = 2308,

    /**
     * 游戏手柄按键'L2'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_L2 = 2309,

    /**
     * 游戏手柄按键'R2'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_R2 = 2310,

    /**
     * 游戏手柄按键'Select'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_SELECT = 2311,

    /**
     * 游戏手柄按键'Start'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_START = 2312,

    /**
     * 游戏手柄按键'Mode'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_MODE = 2313,

    /**
     * 游戏手柄按键'THUMBL'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_THUMBL = 2314,

    /**
     * 游戏手柄按键'THUMBR'。
     * @since 15
     */
    ARKUI_KEYCODE_BUTTON_THUMBR = 2315
} ArkUI_KeyCode;

/**
 * @brief 按键的类型。
 *
 * @since 14
 */
typedef enum {
    /**
     * 未知类型。
     */
    ARKUI_KEY_EVENT_UNKNOWN = -1,

    /**
     * 按键按下。
     */
    ARKUI_KEY_EVENT_DOWN = 0,

    /**
     * 按键松开。
     */
    ARKUI_KEY_EVENT_UP = 1,

    /**
     * 按键长按。
     */
    ARKUI_KEY_EVENT_LONG_PRESS = 2,

    /**
     * 按键点击。
     */
    ARKUI_KEY_EVENT_CLICK = 3
} ArkUI_KeyEventType;

/**
 * @brief 触发当前按键的输入设备类型。
 *
 * @since 14
 */
typedef enum {
    /**
     * 未知类型。
     */
    ARKUI_KEY_SOURCE_UNKNOWN = 0,

    /**
     * 鼠标。
     */
    ARKUI_KEY_SOURCE_TYPE_MOUSE = 1,

    /**
     * 键盘。
     */
    ARKUI_KEY_SOURCE_TYPE_KEYBOARD = 4,

    /**
    * @brief 游戏手柄。
    *
    * @since 15
    */
    ARKUI_KEY_SOURCE_TYPE_JOYSTICK = 5
} ArkUI_KeySourceType;

/**
 * @brief 按键对应的意图。
 *
 * @since 14
 */
typedef enum {
    /**
     * 未知意图。
     */
    ARKUI_KEY_INTENSION_UNKNOWN = -1,

    /**
     * 向上。
     */
    ARKUI_KEY_INTENSION_UP = 1,

    /**
     * 向下。
     */
    ARKUI_KEY_INTENSION_DOWN = 2,

    /**
     * 向左。
     */
    ARKUI_KEY_INTENSION_LEFT = 3,

    /**
     * 向右。
     */
    ARKUI_KEY_INTENSION_RIGHT = 4,

    /**
     * 选中。
     */
    ARKUI_KEY_INTENSION_SELECT = 5,

    /**
     * 返回。
     */
    ARKUI_KEY_INTENSION_ESCAPE = 6,

    /**
     * 后退。
     */
    ARKUI_KEY_INTENSION_BACK = 7,

    /**
     * 前进。
     */
    ARKUI_KEY_INTENSION_FORWARD = 8,

    /**
     * 菜单。
     */
    ARKUI_KEY_INTENSION_MENU = 9,

    /**
     * 主页。
     */
    ARKUI_KEY_INTENSION_HOME = 10,

    /**
     * 上一页。
     */
    ARKUI_KEY_INTENSION_PAGE_UP = 11,

    /**
     * 下一页。
     */
    ARKUI_KEY_INTENSION_PAGE_DOWN = 12,

    /**
     * 缩小。
     */
    ARKUI_KEY_INTENSION_ZOOM_OUT = 13,

    /**
     * 放大。
     */
    ARKUI_KEY_INTENSION_ZOOM_IN = 14,

    /**
     * 播放/暂停。
     */
    ARKUI_KEY_INTENTION_MEDIA_PLAY_PAUSE = 100,

    /**
     * 快进。
     */
    ARKUI_KEY_INTENTION_MEDIA_FAST_FORWARD = 101,

    /**
     * 快速播放。
     */
    ARKUI_KEY_INTENTION_MEDIA_FAST_PLAYBACK = 103,

    /**
     * 下一首。
     */
    ARKUI_KEY_INTENTION_MEDIA_NEXT = 104,

    /**
     * 上一首。
     */
    ARKUI_KEY_INTENTION_MEDIA_PREVIOUS = 105,

    /**
     * 静音。
     */
    ARKUI_KEY_INTENTION_MEDIA_MUTE = 106,

    /**
     * 音量增加。
     */
    ARKUI_KEY_INTENTION_VOLUME_UP = 107,

    /**
     * 音量降低。
     */
    ARKUI_KEY_INTENTION_VOLUME_DOWN = 108,

    /**
     * 接听电话。
     */
    ARKUI_KEY_INTENTION_CALL = 200,

    /**
     * 拍照。
     */
    ARKUI_KEY_INTENTION_CAMERA = 300
} ArkUI_KeyIntension;

/**
 * @brief 按键事件意图类型的正确拼写别名。
 *
 * 原类型名 {@link ArkUI_KeyIntension} 将保留以兼容已有接口。
 *
 * @since 26.1.0
 */
typedef ArkUI_KeyIntension OH_ArkUI_KeyIntention;

/**
 * @brief 创建可通过 {@link OH_ArkUI_KeyEvent_Dispatch} 分发的按键事件。
 *
 * @param event [out] 二级指针，指向创建的 **ArkUI_UIInputEvent** 对象，不能为空。成功时创建的事件写入
 *     **event**，事件归调用方所有，必须调用{@link OH_ArkUI_KeyEvent_Destroy}释放。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空。</li>
 *     </ul>
 * @release arkui/OH_ArkUI_KeyEvent_Destroy {event}
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_Create(ArkUI_UIInputEvent** event);

/**
 * @brief 销毁通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件，并将事件指针置空。
 *
 * 当 **event** 不为空且 **event** 指向的事件指针为空时，函数执行成功。
 *
 * @param event [in] 二级指针，指向待销毁的 **ArkUI_UIInputEvent** 对象，不能为空。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或者输入事件不是通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_Destroy(ArkUI_UIInputEvent** event);

/**
 * @brief 设置通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件类型。
 *
 * @param event [in] 目标 **ArkUI_UIInputEvent** 对象的指针，不能为空，且必须是
 *     通过{@link OH_ArkUI_KeyEvent_Create}创建的按键事件。
 * @param type [in] 按键事件类型。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或不是通过 {@link OH_ArkUI_KeyEvent_Create}创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_SetType(ArkUI_UIInputEvent* event, ArkUI_KeyEventType type);

/**
 * @brief 设置通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件键码。
 *
 * @param event [in] 目标 **ArkUI_UIInputEvent** 对象的指针，不能为空，且必须是
 *     通过{@link OH_ArkUI_KeyEvent_Create}创建的按键事件。
 * @param keyCode [in] 按键键码，取值由 {@link ArkUI_KeyCode} 定义。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或不是通过 {@link OH_ArkUI_KeyEvent_Create}创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_SetKeyCode(ArkUI_UIInputEvent* event, int32_t keyCode);

/**
 * @brief 设置通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件键值。
 *
 * 本函数会复制 **keyText**。函数返回后，调用方可以释放或复用原字符串。
 *
 * @param event [in] 目标 **ArkUI_UIInputEvent** 对象的指针，不能为空，且必须是
 *     通过{@link OH_ArkUI_KeyEvent_Create}创建的按键事件。
 * @param keyText [in] 以空字符结尾的按键键值，UTF-8编码，不能为空。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或不是通过 {@link OH_ArkUI_KeyEvent_Create}创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_SetKeyText(ArkUI_UIInputEvent* event, const char* keyText);

/**
 * @brief 设置通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件输入设备类型。
 *
 * @param event [in] 目标 **ArkUI_UIInputEvent** 对象的指针，不能为空，且必须是
 *     通过{@link OH_ArkUI_KeyEvent_Create}创建的按键事件。
 * @param keySource [in] 输入设备类型。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或不是通过 {@link OH_ArkUI_KeyEvent_Create}创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_SetKeySource(ArkUI_UIInputEvent* event, ArkUI_KeySourceType keySource);

/**
 * @brief 设置通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件设备ID。
 *
 * @param event [in] 目标 **ArkUI_UIInputEvent** 对象的指针，不能为空，且必须是
 *     通过{@link OH_ArkUI_KeyEvent_Create}创建的按键事件。
 * @param deviceId [in] 设备ID，由系统分配的输入设备标识。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或不是通过 {@link OH_ArkUI_KeyEvent_Create}创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_SetDeviceId(ArkUI_UIInputEvent* event, int32_t deviceId);

/**
 * @brief 设置通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件Unicode码值。
 *
 * @param event [in] 目标 **ArkUI_UIInputEvent** 对象的指针，不能为空，且必须是
 *     通过{@link OH_ArkUI_KeyEvent_Create}创建的按键事件。
 * @param unicode [in] Unicode码值，必须为有效的Unicode码位。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或不是通过 {@link OH_ArkUI_KeyEvent_Create}创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_SetUnicode(ArkUI_UIInputEvent* event, uint32_t unicode);

/**
 * @brief 设置通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件发生时间。
 *
 * @param event [in] 目标 **ArkUI_UIInputEvent** 对象的指针，不能为空，且必须是
 *     通过{@link OH_ArkUI_KeyEvent_Create}创建的按键事件。
 * @param timestamp [in] 事件发生时间，单位为ns，时间基准与{@link OH_ArkUI_UIInputEvent_GetEventTime}一致。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或不是通过 {@link OH_ArkUI_KeyEvent_Create}创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_SetEventTime(ArkUI_UIInputEvent* event, int64_t timestamp);

/**
 * @brief 设置通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件中所有已按下的按键。
 *
 * 本函数会复制 **pressedKeyCodes**。函数返回后，调用方可以释放或复用原数组。
 * 将 **pressedKeyCodes** 传入空指针、**length** 传入 **0** 可以清空已按下的按键。
 *
 * @param event [in] 目标 **ArkUI_UIInputEvent** 对象的指针，不能为空，且必须是
 *     通过{@link OH_ArkUI_KeyEvent_Create}创建的按键事件。
 * @param pressedKeyCodes [in] 所有已按下按键的键码数组，仅当 **length** 为 **0** 时可以为 <b>nullptr</b>。
 *     每个元素的取值由 {@link ArkUI_KeyCode} 定义。
 * @param length [in] **pressedKeyCodes** 中的元素个数，必须大于等于 **0**。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或不是通过 {@link OH_ArkUI_KeyEvent_Create}创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_SetPressedKeys(
    ArkUI_UIInputEvent* event, const int32_t* pressedKeyCodes, int32_t length);

/**
 * @brief 设置通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件意图码。
 *
 * @param event [in] 目标 **ArkUI_UIInputEvent** 对象的指针，不能为空，且必须是
 *     通过{@link OH_ArkUI_KeyEvent_Create}创建的按键事件。
 * @param intentionCode [in] 按键事件关联的意图码。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或不是通过 {@link OH_ArkUI_KeyEvent_Create}创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_SetKeyIntentionCode(
    ArkUI_UIInputEvent* event, OH_ArkUI_KeyIntention intentionCode);

/**
 * @brief 设置通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件NumLock状态。
 *
 * @param event [in] 目标 **ArkUI_UIInputEvent** 对象的指针，不能为空，且必须是
 *     通过{@link OH_ArkUI_KeyEvent_Create}创建的按键事件。
 * @param isNumLockOn [in] NumLock是否激活。true表示处于激活状态，false表示处于未激活状态。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或不是通过 {@link OH_ArkUI_KeyEvent_Create}创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_SetNumLockOn(ArkUI_UIInputEvent* event, bool isNumLockOn);

/**
 * @brief 设置通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件CapsLock状态。
 *
 * @param event [in] 目标 **ArkUI_UIInputEvent** 对象的指针，不能为空，且必须是
 *     通过{@link OH_ArkUI_KeyEvent_Create}创建的按键事件。
 * @param isCapsLockOn [in] CapsLock是否激活。true表示处于激活状态，false表示处于未激活状态。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或不是通过 {@link OH_ArkUI_KeyEvent_Create}创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_SetCapsLockOn(ArkUI_UIInputEvent* event, bool isCapsLockOn);

/**
 * @brief 设置通过 {@link OH_ArkUI_KeyEvent_Create} 创建的按键事件ScrollLock状态。
 *
 * @param event [in] 目标 **ArkUI_UIInputEvent** 对象的指针，不能为空，且必须是
 *     通过{@link OH_ArkUI_KeyEvent_Create}创建的按键事件。
 * @param isScrollLockOn [in] ScrollLock是否激活。true表示处于激活状态，false表示处于未激活状态。
 * @return 错误码。
 *     <ul>
 *     <li>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。</li>
 *     <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} **event** 为空，或不是通过 {@link OH_ArkUI_KeyEvent_Create}创建的按键事件。</li>
 *     </ul>
 * @since 26.1.0
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_SetScrollLockOn(ArkUI_UIInputEvent* event, bool isScrollLockOn);

/**
 * @brief 获取按键的类型。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return ArkUI_KeyEventType 按键的类型。
 * @since 14
 */
ArkUI_KeyEventType OH_ArkUI_KeyEvent_GetType(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取按键的键码。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return 按键的键码。
 * @since 14
 */
int32_t OH_ArkUI_KeyEvent_GetKeyCode(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取按键的键值。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return 按键的键值。
 * @since 14
 */
const char *OH_ArkUI_KeyEvent_GetKeyText(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取当前按键的输入设备类型。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return ArkUI_KeySourceType 当前按键的输入设备类型。
 * @since 14
 */
ArkUI_KeySourceType OH_ArkUI_KeyEvent_GetKeySource(const ArkUI_UIInputEvent* event);

/**
 * @brief 阻塞事件冒泡传递。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param stopPropagation 表示是否阻止事件冒泡。true表示阻止事件冒泡，false表示不阻止事件冒泡。
 * @since 14
 */
void OH_ArkUI_KeyEvent_StopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation);

/**
 * @brief 获取按键对应的意图。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return ArkUI_KeyIntension 按键对应的意图。
 * @since 14
 */
ArkUI_KeyIntension OH_ArkUI_KeyEvent_GetKeyIntensionCode(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取按键的Unicode码值。支持范围为非空格的基本拉丁字符：0x0021-0x007E，不支持字符为0。组合键场景下，返回当前keyEvent对应按键的Unicode码值。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return Unicode码值。
 * @since 14
 */
uint32_t OH_ArkUI_KeyEvent_GetUnicode(const ArkUI_UIInputEvent* event);

/**
 * @brief 在按键事件回调中，设置事件是否被该回调消费。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param isConsumed 事件是否被该回调消费。true表示事件被消费，false表示事件未被消费。
 * @since 14
 */
void OH_ArkUI_KeyEvent_SetConsumed(const ArkUI_UIInputEvent* event, bool isConsumed);

/**
 * @brief 将按键事件分发到特定组件节点。
 *
 * @param node 指定的节点。
 * @param event ArkUI_UIInputEvent事件指针。
 * @since 15
 */
void OH_ArkUI_KeyEvent_Dispatch(ArkUI_NodeHandle node, const ArkUI_UIInputEvent* event);

/**
 * @brief 获取按键事件发生时NumLock的状态。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param state 输出参数，返回NumLock的状态。true表示处于激活状态，false表示处于未激活状态。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_IsNumLockOn(const ArkUI_UIInputEvent* event, bool* state);

/**
 * @brief 获取按键事件发生时CapsLock的状态。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param state 输出参数，返回CapsLock的状态。true表示处于激活状态，false表示处于未激活状态。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_IsCapsLockOn(const ArkUI_UIInputEvent* event, bool* state);

/**
 * @brief 获取按键事件发生时ScrollLock的状态。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param state 输出参数，返回ScrollLock的状态。true表示处于激活状态，false表示处于未激活状态。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 19
 */
ArkUI_ErrorCode OH_ArkUI_KeyEvent_IsScrollLockOn(const ArkUI_UIInputEvent* event, bool* state);

/**
 * @brief 枚举键盘快捷键支持的修饰键。
 *
 * 枚举值为位标志，可以使用按位或运算符进行组合。
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief 不使用修饰键。该值仅可与功能键一起使用。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_MODIFIER_NONE = 0,
    /**
     * @brief Ctrl键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_MODIFIER_CTRL = 1,
    /**
     * @brief Shift键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_MODIFIER_SHIFT = 2,
    /**
     * @brief Alt键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_MODIFIER_ALT = 4,
} OH_ArkUI_KeyboardShortcutModifierKey;

/**
 * @brief 枚举键盘快捷键支持的功能键。
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief Esc键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_ESC = 0,
    /**
     * @brief F1键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_F1 = 1,
    /**
     * @brief F2键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_F2 = 2,
    /**
     * @brief F3键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_F3 = 3,
    /**
     * @brief F4键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_F4 = 4,
    /**
     * @brief F5键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_F5 = 5,
    /**
     * @brief F6键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_F6 = 6,
    /**
     * @brief F7键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_F7 = 7,
    /**
     * @brief F8键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_F8 = 8,
    /**
     * @brief F9键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_F9 = 9,
    /**
     * @brief F10键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_F10 = 10,
    /**
     * @brief F11键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_F11 = 11,
    /**
     * @brief F12键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_F12 = 12,
    /**
     * @brief Tab键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_TAB = 13,
    /**
     * @brief 向上方向键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_DPAD_UP = 14,
    /**
     * @brief 向下方向键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_DPAD_DOWN = 15,
    /**
     * @brief 向左方向键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_DPAD_LEFT = 16,
    /**
     * @brief 向右方向键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_DPAD_RIGHT = 17,
    /**
     * @brief CapsLock键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_CAPS_LOCK = 18,
    /**
     * @brief PrintScreen键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_PRINT_SCREEN = 19,
    /**
     * @brief ScrollLock键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_SCROLL_LOCK = 20,
    /**
     * @brief Pause/Break键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_PAUSE_BREAK = 21,
    /**
     * @brief NumLock键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_NUM_LOCK = 22,
    /**
     * @brief Insert键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_INSERT = 23,
    /**
     * @brief Delete键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_DELETE = 24,
    /**
     * @brief Home键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_HOME = 25,
    /**
     * @brief End键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_END = 26,
    /**
     * @brief Page Up键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_PAGE_UP = 27,
    /**
     * @brief Page Down键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_PAGE_DOWN = 28,
    /**
     * @brief Enter键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_ENTER = 29,
    /**
     * @brief Backspace键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_BACKSPACE = 30,
    /**
     * @brief Space键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_SPACE = 31,
} OH_ArkUI_KeyboardShortcutFunctionKey;

/**
 * @brief 枚举键盘快捷键支持的按键类型。
 *
 * @since 26.2.0
 */
typedef enum {
    /**
     * @brief 字符键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_KEY_TYPE_CHARACTER = 0,
    /**
     * @brief 功能键。
     *
     * @since 26.2.0
     */
    OH_ARKUI_KEYBOARD_SHORTCUT_KEY_TYPE_FUNCTION_KEY = 1,
} OH_ArkUI_KeyboardShortcutKeyType;

/**
 * @brief 定义键盘快捷键按键结构体，描述快捷键按键的设计逻辑，如按键类型和按键值。应用可注册和管理自定义快捷键。
 * @see OH_ArkUI_KeyboardShortcutKey_Create
 * @see OH_ArkUI_KeyboardShortcutKey_Destroy
 *
 * @since 26.2.0
 */
typedef struct OH_ArkUI_KeyboardShortcutKey OH_ArkUI_KeyboardShortcutKey;

/**
 * @brief 创建键盘快捷键按键对象。可调用{@link OH_ArkUI_KeyboardShortcutKey_Destroy}销毁键盘快捷键按键对象。
 *
 * @return 键盘快捷键按键对象。
 *     <ul>
 *     <li>成功时返回归调用方所有的{@link OH_ArkUI_KeyboardShortcutKey}对象，调用方必须通过
 *     {@link OH_ArkUI_KeyboardShortcutKey_Destroy}释放。</li>
 *     <li>操作失败时（例如内存分配失败）返回<b>nullptr</b>。</li>
 *     </ul>
 * @release arkui/OH_ArkUI_KeyboardShortcutKey_Destroy {return}
 * @since 26.2.0
 */
OH_ArkUI_KeyboardShortcutKey* OH_ArkUI_KeyboardShortcutKey_Create(void);

/**
 * @brief 销毁键盘快捷键按键对象。
 *
 * @param key [in] 键盘快捷键按键对象。
 * @since 26.2.0
 */
void OH_ArkUI_KeyboardShortcutKey_Destroy(OH_ArkUI_KeyboardShortcutKey** key);

/**
 * @brief 设置键盘快捷键按键的类型。
 *
 * @param key [in] 键盘快捷键按键对象指针。
 * @param type [in] 按键类型。
 * @since 26.2.0
 */
void OH_ArkUI_KeyboardShortcutKey_SetType(OH_ArkUI_KeyboardShortcutKey* key, OH_ArkUI_KeyboardShortcutKeyType type);

/**
 * @brief 获取键盘快捷键按键的类型。
 *
 * @param key [in] 键盘快捷键按键对象指针。
 * @return 按键类型。
 *     <ul>
 *     <li>按键类型。</li>
 *     <li>如果<b>key</b>为<b>nullptr</b>，则返回{@link OH_ARKUI_KEYBOARD_SHORTCUT_KEY_TYPE_CHARACTER}。</li>
 *     </ul>
 * @since 26.2.0
 */
OH_ArkUI_KeyboardShortcutKeyType OH_ArkUI_KeyboardShortcutKey_GetType(const OH_ArkUI_KeyboardShortcutKey* key);

/**
 * @brief 设置字符键盘快捷键按键的字符。调用此函数前，按键类型必须已设置为
 * {@link OH_ARKUI_KEYBOARD_SHORTCUT_KEY_TYPE_CHARACTER}。
 *
 * @param key [in] 键盘快捷键按键对象指针。
 * @param character [in] 可通过键盘输入的单个字符。
 * @since 26.2.0
 */
void OH_ArkUI_KeyboardShortcutKey_SetCharacter(OH_ArkUI_KeyboardShortcutKey* key, char character);

/**
 * @brief 获取字符键盘快捷键按键的字符。
 *
 * @param key [in] 键盘快捷键按键对象指针。
 * @return 字符。
 *     <ul>
 *     <li>字符。</li>
 *     <li>如果<b>key</b>为<b>nullptr</b>，则返回<b>'\\0'</b>。</li>
 *     </ul>
 * @since 26.2.0
 */
char OH_ArkUI_KeyboardShortcutKey_GetCharacter(const OH_ArkUI_KeyboardShortcutKey* key);

/**
 * @brief 设置功能键盘快捷键按键的功能键。调用此函数前，按键类型必须已设置为
 * {@link OH_ARKUI_KEYBOARD_SHORTCUT_KEY_TYPE_FUNCTION_KEY}。
 *
 * @param key [in] 键盘快捷键按键对象指针。
 * @param functionKey [in] 功能键。
 * @since 26.2.0
 */
void OH_ArkUI_KeyboardShortcutKey_SetFunctionKey(
    OH_ArkUI_KeyboardShortcutKey* key, OH_ArkUI_KeyboardShortcutFunctionKey functionKey);

/**
 * @brief 获取功能键盘快捷键按键的功能键。
 *
 * @param key [in] 键盘快捷键按键对象指针。
 * @return 功能键。
 *     <ul>
 *     <li>功能键。</li>
 *     <li>如果<b>key</b>为<b>nullptr</b>，则返回{@link OH_ARKUI_KEYBOARD_SHORTCUT_FUNCTION_KEY_ESC}。</li>
 *     </ul>
 * @since 26.2.0
 */
OH_ArkUI_KeyboardShortcutFunctionKey OH_ArkUI_KeyboardShortcutKey_GetFunctionKey(
    const OH_ArkUI_KeyboardShortcutKey* key);

/**
 * @brief 定义组件级键盘快捷键触发时调用的回调函数。
 *
 * @param userData [out] 注册快捷键时传入的用户自定义数据。该值不会被复制，在快捷键注销前必须保持有效。
 * @since 26.2.0
 */
typedef void (*OH_ArkUI_KeyboardShortcutCallback)(void* userData);

/**
 * @brief 为组件注册键盘快捷键。同一组件重复注册相同快捷键时，以最后一次注册为准。组件级快捷键的触发优先级
 * 高于相同的应用级快捷键。
 *
 * @param node [in] 目标组件节点。
 * @param key [in] 指向键盘快捷键按键对象的指针，不能为<b>nullptr</b>。该对象通过
 *     {@link OH_ArkUI_KeyboardShortcutKey_Create}创建。字符键通过
 *     {@link OH_ArkUI_KeyboardShortcutKey_SetCharacter}设置的字符必须为单个可通过键盘输入的字符。
 * @param modifierKeys [in] 修饰键位掩码。使用{@link OH_ArkUI_KeyboardShortcutModifierKey}中的值进行按位或组合。功能键可使用
 *     {@link OH_ARKUI_KEYBOARD_SHORTCUT_MODIFIER_NONE}注册不带修饰键的快捷键，字符键至少需要指定一个修饰键。
 *     仅接受{@link OH_ArkUI_KeyboardShortcutModifierKey}中定义的位，设置其他位时返回
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param userData [in] 传递给回调函数的用户自定义数据，可以为<b>nullptr</b>。该值不会被复制，
 *     在快捷键注销前必须保持有效。
 * @param callback [in] 快捷键触发时调用的回调函数。如果为<b>nullptr</b>，则触发组件的点击事件。
 * @return 返回执行结果。
 *     <ul>
 *     <li>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。</li>
 *     <li>如果参数无效，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NodeKeyboardShortcut_Register(ArkUI_NodeHandle node, const OH_ArkUI_KeyboardShortcutKey* key,
    uint32_t modifierKeys, void* userData, OH_ArkUI_KeyboardShortcutCallback callback);

/**
 * @brief 注销组件的键盘快捷键。如果没有注册匹配的快捷键，该操作仍然成功。
 *
 * @param node [in] 目标组件节点。
 * @param key [in] 指向注册时所用键盘快捷键按键对象的指针，不能为<b>nullptr</b>。
 * @param modifierKeys [in] 注册时使用的修饰键位掩码。仅接受{@link OH_ArkUI_KeyboardShortcutModifierKey}
 *     中定义的位，设置其他位时返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @return 返回执行结果。
 *     <ul>
 *     <li>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。</li>
 *     <li>如果参数无效，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NodeKeyboardShortcut_Unregister(
    ArkUI_NodeHandle node, const OH_ArkUI_KeyboardShortcutKey* key, uint32_t modifierKeys);

/**
 * @brief 定义应用级键盘快捷键的回调信息。
 *
 * @since 26.2.0
 */
typedef struct OH_ArkUI_ApplicationShortcutCallbackInfo OH_ArkUI_ApplicationShortcutCallbackInfo;

/**
 * @brief 定义应用级键盘快捷键触发时调用的回调函数。该回调在触发快捷键的UI实例对应的UI线程上执行。
 *
 * @param info [out] 指向触发快捷键的UI实例回调信息对象的指针，不能为空。使用
 *     {@link OH_ArkUI_ApplicationShortcutCallbackInfo_GetUIContext}获取对应的UI上下文。该对象仅在回调执行期间
 *     有效，不得持有。
 * @param userData [out] 注册快捷键时传入的用户自定义数据。该值不会被复制，在快捷键注销前必须保持有效。
 * @since 26.2.0
 */
typedef void (*OH_ArkUI_ApplicationShortcutCallback)(const OH_ArkUI_ApplicationShortcutCallbackInfo* info, void* userData);

/**
 * @brief 获取触发应用级键盘快捷键的UI实例对应的UI上下文。
 *
 * @param info [in] 指向{@link OH_ArkUI_ApplicationShortcutCallback}接收到的单个回调信息对象的指针，
 *     不能为空。
 * @return UI上下文。
 *     <ul>
 *     <li>触发快捷键的UI实例对应的UI上下文。</li>
 *     <li>如果<b>info</b>无效，则返回<b>nullptr</b>。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ContextHandle OH_ArkUI_ApplicationShortcutCallbackInfo_GetUIContext(
    const OH_ArkUI_ApplicationShortcutCallbackInfo* info);

/**
 * @brief 注册应用级键盘快捷键。该快捷键在应用内全局生效。
 * 如果存在匹配的组件级快捷键，则优先触发组件级快捷键。
 *
 * 每次注册生成一个应用内唯一的正整数注册标识符，即使快捷键和回调相同，标识符也不同。
 * 同一个快捷键的多次注册均被保留，仅最近一次未注销的注册生效。
 * 注册标识符在应用运行期间不复用。
 *
 * @param key [in] 指向键盘快捷键按键对象的指针，不能为<b>nullptr</b>。该对象通过
 *     {@link OH_ArkUI_KeyboardShortcutKey_Create}创建。字符键通过
 *     {@link OH_ArkUI_KeyboardShortcutKey_SetCharacter}设置的字符必须为单个可通过键盘输入的字符。
 * @param modifierKeys [in] 修饰键位掩码。使用{@link OH_ArkUI_KeyboardShortcutModifierKey}中的值进行按位或组合。功能键可使用
 *     {@link OH_ARKUI_KEYBOARD_SHORTCUT_MODIFIER_NONE}注册不带修饰键的快捷键，字符键至少需要指定一个修饰键。
 *     仅接受{@link OH_ArkUI_KeyboardShortcutModifierKey}中定义的位，设置其他位时返回
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @param userData [in] 传递给回调函数的用户自定义数据，可以为<b>nullptr</b>。该值不会被复制，
 *     在快捷键注销前必须保持有效。
 * @param callback [in] 快捷键触发时调用的回调函数，不能为<b>nullptr</b>。
 * @param registrationId [out] 用于接收本次快捷键绑定注册标识符的输出指针，不能为<b>nullptr</b>。
 *     仅在注册成功时写入，注册失败时保持原值。
 * @return 返回执行结果。
 *     <ul>
 *     <li>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。</li>
 *     <li>如果参数无效，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。</li>
 *     </ul>
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_ApplicationShortcut_Register(const OH_ArkUI_KeyboardShortcutKey* key, uint32_t modifierKeys,
    void* userData, OH_ArkUI_ApplicationShortcutCallback callback, int32_t* registrationId);

/**
 * @brief 注销指定注册标识符对应的应用级键盘快捷键绑定。
 *
 * 仅移除该标识符对应的绑定，其他绑定不受影响。如果移除的是当前生效的绑定，
 * 则最近一次仍未注销的同快捷键绑定恢复生效。标识符不存在或已注销时，不执行任何操作，仍返回成功。
 *
 * @param registrationId [in] 注册快捷键时获得的注册标识符。
 * @return 返回执行结果。
 *     <br>如果操作成功或注册标识符不存在，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_ApplicationShortcut_Unregister(int32_t registrationId);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_KEY_EVENT_H
/** @} */
