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
 * @brief 按键设备的键值。
 *
 * @file oh_key_code.h
 * @include <multimodalinput/oh_key_code.h>
 *
 * @kit InputKit
 * @syscap SystemCapability.MultimodalInput.Input.Core
 * @library libohinput.so
 * @since 12
 */

#ifndef OH_KEY_CODE_H
#define OH_KEY_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 键值。
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief 未知按键
     */
    KEYCODE_UNKNOWN = -1,

    /**
     * @brief 功能（Fn）键
     */
    KEYCODE_FN = 0,
    /**
     * @brief 功能（Home）键
     * @since 22
     */
    KEYCODE_HOME = 1,
    /**
     * @brief 返回键
     * @since 22
     */
    KEYCODE_BACK = 2,

    /**
     * @brief 搜索键
     * @since 22
     */
    KEYCODE_SEARCH = 9,
    /**
     * @brief 多媒体键：播放/暂停。<br/>与KEYCODE_PLAYPAUSE的区别为：<br/>KEYCODE_PLAYPAUSE是较早的定义，
     * KEYCODE_MEDIA_PLAY_PAUSE为现代媒体键设备设计，常见于较新的媒体键设备。
     * @since 22
     */
    KEYCODE_MEDIA_PLAY_PAUSE = 10,
    /**
     * @brief 光盘停止键
     * @since 22
     */
    KEYCODE_MEDIA_STOP = 11,
    /**
     * @brief 多媒体键：下一首
     * @since 22
     */
    KEYCODE_MEDIA_NEXT = 12,
    /**
     * @brief 多媒体键：上一首
     * @since 22
     */
    KEYCODE_MEDIA_PREVIOUS = 13,
    /**
     * @brief 多媒体键：快退
     * @since 22
     */
    KEYCODE_MEDIA_REWIND = 14,
    /**
     * @brief 多媒体键：快进
     * @since 22
     */
    KEYCODE_MEDIA_FAST_FORWARD = 15,

    /**
     * @brief 音量增加键
     */
    KEYCODE_VOLUME_UP = 16,

    /**
     * @brief 音量减小键
     */
    KEYCODE_VOLUME_DOWN = 17,

    /**
     * @brief 电源键
     */
    KEYCODE_POWER = 18,

    /**
     * @brief 拍照键
     */
    KEYCODE_CAMERA = 19,

    /**
     * @brief 扬声器静音键
     */
    KEYCODE_VOLUME_MUTE = 22,

    /**
     * @brief 话筒静音键
     */
    KEYCODE_MUTE = 23,

    /**
     * @brief 亮度调节按键：调亮
     */
    KEYCODE_BRIGHTNESS_UP = 40,

    /**
     * @brief 亮度调节按键：调暗
     */
    KEYCODE_BRIGHTNESS_DOWN = 41,

    /**
     * @brief 按键'0'
     */
    KEYCODE_0 = 2000,

    /**
     * @brief 按键'1'
     */
    KEYCODE_1 = 2001,

    /**
     * @brief 按键'2'
     */
    KEYCODE_2 = 2002,

    /**
     * @brief 按键'3'
     */
    KEYCODE_3 = 2003,

    /**
     * @brief 按键'4'
     */
    KEYCODE_4 = 2004,

    /**
     * @brief 按键'5'
     */
    KEYCODE_5 = 2005,

    /**
     * @brief 按键'6'
     */
    KEYCODE_6 = 2006,

    /**
     * @brief 按键'7'
     */
    KEYCODE_7 = 2007,

    /**
     * @brief 按键'8'
     */
    KEYCODE_8 = 2008,

    /**
     * @brief 按键'9'
     */
    KEYCODE_9 = 2009,

    /**
     * @brief 按键'*'
     */
    KEYCODE_STAR = 2010,

    /**
     * @brief 按键'#'
     */
    KEYCODE_POUND = 2011,

    /**
     * @brief 导航键：向上
     */
    KEYCODE_DPAD_UP = 2012,

    /**
     * @brief 导航键：向下
     */
    KEYCODE_DPAD_DOWN = 2013,

    /**
     * @brief 导航键：向左
     */
    KEYCODE_DPAD_LEFT = 2014,

    /**
     * @brief 导航键：向右
     */
    KEYCODE_DPAD_RIGHT = 2015,

    /**
     * @brief 导航键：确定键
     */
    KEYCODE_DPAD_CENTER = 2016,

    /**
     * @brief 按键'A'
     */
    KEYCODE_A = 2017,

    /**
     * @brief 按键'B'
     */
    KEYCODE_B = 2018,

    /**
     * @brief 按键'C'
     */
    KEYCODE_C = 2019,

    /**
     * @brief 按键'D'
     */
    KEYCODE_D = 2020,

    /**
     * @brief 按键'E'
     */
    KEYCODE_E = 2021,

    /**
     * @brief 按键'F'
     */
    KEYCODE_F = 2022,

    /**
     * @brief 按键'G'
     */
    KEYCODE_G = 2023,

    /**
     * @brief 按键'H'
     */
    KEYCODE_H = 2024,

    /**
     * @brief 按键'I'
     */
    KEYCODE_I = 2025,

    /**
     * @brief 按键'J'
     */
    KEYCODE_J = 2026,

    /**
     * @brief 按键'K'
     */
    KEYCODE_K = 2027,

    /**
     * @brief 按键'L'
     */
    KEYCODE_L = 2028,

    /**
     * @brief 按键'M'
     */
    KEYCODE_M = 2029,

    /**
     * @brief 按键'N'
     */
    KEYCODE_N = 2030,

    /**
     * @brief 按键'O'
     */
    KEYCODE_O = 2031,

    /**
     * @brief 按键'P'
     */
    KEYCODE_P = 2032,

    /**
     * @brief 按键'Q'
     */
    KEYCODE_Q = 2033,

    /**
     * @brief 按键'R'
     */
    KEYCODE_R = 2034,

    /**
     * @brief 按键'S'
     */
    KEYCODE_S = 2035,

    /**
     * @brief 按键'T'
     */
    KEYCODE_T = 2036,

    /**
     * @brief 按键'U'
     */
    KEYCODE_U = 2037,

    /**
     * @brief 按键'V'
     */
    KEYCODE_V = 2038,

    /**
     * @brief 按键'W'
     */
    KEYCODE_W = 2039,

    /**
     * @brief 按键'X'
     */
    KEYCODE_X = 2040,

    /**
     * @brief 按键'Y'
     */
    KEYCODE_Y = 2041,

    /**
     * @brief 按键'Z'
     */
    KEYCODE_Z = 2042,

    /**
     * @brief 按键','
     */
    KEYCODE_COMMA = 2043,

    /**
     * @brief 按键'.'
     */
    KEYCODE_PERIOD = 2044,

    /**
     * @brief 左Alt键
     */
    KEYCODE_ALT_LEFT = 2045,

    /**
     * @brief 右Alt键
     */
    KEYCODE_ALT_RIGHT = 2046,

    /**
     * @brief 左Shift键
     */
    KEYCODE_SHIFT_LEFT = 2047,

    /**
     * @brief 右Shift键
     */
    KEYCODE_SHIFT_RIGHT = 2048,

    /**
     * @brief Tab键
     */
    KEYCODE_TAB = 2049,

    /**
     * @brief 空格键
     */
    KEYCODE_SPACE = 2050,

    /**
     * @brief 符号修改器按键
     */
    KEYCODE_SYM = 2051,

    /**
     * @brief 浏览器功能键，此键用于启动浏览器应用程序。
     */
    KEYCODE_EXPLORER = 2052,

    /**
     * @brief 电子邮件功能键，此键用于启动电子邮件应用程序。
     */
    KEYCODE_ENVELOPE = 2053,

    /**
     * @brief 回车键
     */
    KEYCODE_ENTER = 2054,

    /**
     * @brief 退格键
     */
    KEYCODE_DEL = 2055,

    /**
     * @brief 按键'`'
     */
    KEYCODE_GRAVE = 2056,

    /**
     * @brief 按键'-'
     */
    KEYCODE_MINUS = 2057,

    /**
     * @brief 按键'='
     */
    KEYCODE_EQUALS = 2058,

    /**
     * @brief 按键'['
     */
    KEYCODE_LEFT_BRACKET = 2059,

    /**
     * @brief 按键']'
     */
    KEYCODE_RIGHT_BRACKET = 2060,

    /**
     * @brief 按键'\'
     */
    KEYCODE_BACKSLASH = 2061,

    /**
     * @brief 按键';'
     */
    KEYCODE_SEMICOLON = 2062,

    /**
     * @brief 按键''' (单引号)
     */
    KEYCODE_APOSTROPHE = 2063,

    /**
     * @brief 按键'/'
     */
    KEYCODE_SLASH = 2064,

    /**
     * @brief 按键'@'
     */
    KEYCODE_AT = 2065,

    /**
     * @brief 按键'+'
     */
    KEYCODE_PLUS = 2066,

    /**
     * @brief 菜单键
     */
    KEYCODE_MENU = 2067,

    /**
     * @brief 向上翻页键
     */
    KEYCODE_PAGE_UP = 2068,

    /**
     * @brief 向下翻页键
     */
    KEYCODE_PAGE_DOWN = 2069,

    /**
     * @brief Esc键
     */
    KEYCODE_ESCAPE = 2070,

    /**
     * @brief 删除键
     */
    KEYCODE_FORWARD_DEL = 2071,

    /**
     * @brief 左Ctrl键
     */
    KEYCODE_CTRL_LEFT = 2072,

    /**
     * @brief 右Ctrl键
     */
    KEYCODE_CTRL_RIGHT = 2073,

    /**
     * @brief 大写锁定键
     */
    KEYCODE_CAPS_LOCK = 2074,

    /**
     * @brief 滚动锁定键
     */
    KEYCODE_SCROLL_LOCK = 2075,

    /**
     * @brief 左Meta键
     */
    KEYCODE_META_LEFT = 2076,

    /**
     * @brief 右Meta键
     */
    KEYCODE_META_RIGHT = 2077,

    /**
     * @brief 功能键
     */
    KEYCODE_FUNCTION = 2078,

    /**
     * @brief 系统请求/打印屏幕键
     */
    KEYCODE_SYSRQ = 2079,

    /**
     * @brief Break/Pause键
     */
    KEYCODE_BREAK = 2080,

    /**
     * @brief 光标移动到开始键
     */
    KEYCODE_MOVE_HOME = 2081,

    /**
     * @brief 光标移动到末尾键
     */
    KEYCODE_MOVE_END = 2082,

    /**
     * @brief 插入键
     */
    KEYCODE_INSERT = 2083,

    /**
     * @brief 前进键
     */
    KEYCODE_FORWARD = 2084,

    /**
     * @brief 多媒体键：播放
     */
    KEYCODE_MEDIA_PLAY = 2085,

    /**
     * @brief 光盘暂停键
     */
    KEYCODE_MEDIA_PAUSE = 2086,

    /**
     * @brief 光盘关闭键
     */
    KEYCODE_MEDIA_CLOSE = 2087,

    /**
     * @brief 光盘弹出键
     */
    KEYCODE_MEDIA_EJECT = 2088,

    /**
     * @brief 多媒体键：录音
     */
    KEYCODE_MEDIA_RECORD = 2089,

    /**
     * @brief 按键'F1'
     */
    KEYCODE_F1 = 2090,

    /**
     * @brief 按键'F2'
     */
    KEYCODE_F2 = 2091,

    /**
     * @brief 按键'F3'
     */
    KEYCODE_F3 = 2092,

    /**
     * @brief 按键'F4'
     */
    KEYCODE_F4 = 2093,

    /**
     * @brief 按键'F5'
     */
    KEYCODE_F5 = 2094,

    /**
     * @brief 按键'F6'
     */
    KEYCODE_F6 = 2095,

    /**
     * @brief 按键'F7'
     */
    KEYCODE_F7 = 2096,

    /**
     * @brief 按键'F8'
     */
    KEYCODE_F8 = 2097,

    /**
     * @brief 按键'F9'
     */
    KEYCODE_F9 = 2098,

    /**
     * @brief 按键'F10'
     */
    KEYCODE_F10 = 2099,

    /**
     * @brief 按键'F11'
     */
    KEYCODE_F11 = 2100,

    /**
     * @brief 按键'F12'
     */
    KEYCODE_F12 = 2101,

    /**
     * @brief 小键盘锁
     */
    KEYCODE_NUM_LOCK = 2102,

    /**
     * @brief 小键盘按键'0'
     */
    KEYCODE_NUMPAD_0 = 2103,

    /**
     * @brief 小键盘按键'1'
     */
    KEYCODE_NUMPAD_1 = 2104,

    /**
     * @brief 小键盘按键'2'
     */
    KEYCODE_NUMPAD_2 = 2105,

    /**
     * @brief 小键盘按键'3'
     */
    KEYCODE_NUMPAD_3 = 2106,

    /**
     * @brief 小键盘按键'4'
     */
    KEYCODE_NUMPAD_4 = 2107,

    /**
     * @brief 小键盘按键'5'
     */
    KEYCODE_NUMPAD_5 = 2108,

    /**
     * @brief 小键盘按键'6'
     */
    KEYCODE_NUMPAD_6 = 2109,

    /**
     * @brief 小键盘按键'7'
     */
    KEYCODE_NUMPAD_7 = 2110,

    /**
     * @brief 小键盘按键'8'
     */
    KEYCODE_NUMPAD_8 = 2111,

    /**
     * @brief 小键盘按键'9'
     */
    KEYCODE_NUMPAD_9 = 2112,

    /**
     * @brief 小键盘按键'/'
     */
    KEYCODE_NUMPAD_DIVIDE = 2113,

    /**
     * @brief 小键盘按键'*'
     */
    KEYCODE_NUMPAD_MULTIPLY = 2114,

    /**
     * @brief 小键盘按键'-'
     */
    KEYCODE_NUMPAD_SUBTRACT = 2115,

    /**
     * @brief 小键盘按键'+'
     */
    KEYCODE_NUMPAD_ADD = 2116,

    /**
     * @brief 小键盘按键'.'
     */
    KEYCODE_NUMPAD_DOT = 2117,

    /**
     * @brief 小键盘按键','
     */
    KEYCODE_NUMPAD_COMMA = 2118,

    /**
     * @brief 小键盘按键回车
     */
    KEYCODE_NUMPAD_ENTER = 2119,

    /**
     * @brief 小键盘按键'='
     */
    KEYCODE_NUMPAD_EQUALS = 2120,

    /**
     * @brief 小键盘按键'('
     */
    KEYCODE_NUMPAD_LEFT_PAREN = 2121,

    /**
     * @brief 小键盘按键')'
     */
    KEYCODE_NUMPAD_RIGHT_PAREN = 2122,
    /**
     * @brief 虚拟多任务键
     * @since 22
     */
    KEYCODE_VIRTUAL_MULTITASK = 2210,
    /**
     * @brief 游戏手柄按键'A'
     * @since 22
     */
    KEYCODE_BUTTON_A = 2301,
    /**
     * @brief 游戏手柄按键'B'
     * @since 22
     */
    KEYCODE_BUTTON_B = 2302,
    /**
     * @brief 游戏手柄按键'X'
     * @since 22
     */
    KEYCODE_BUTTON_X = 2304,
    /**
     * @brief 游戏手柄按键'Y'
     * @since 22
     */
    KEYCODE_BUTTON_Y = 2305,
    /**
     * @brief 游戏手柄按键'L1'
     * @since 22
     */
    KEYCODE_BUTTON_L1 = 2307,
    /**
     * @brief 游戏手柄按键'R1'
     * @since 22
     */
    KEYCODE_BUTTON_R1 = 2308,
    /**
     * @brief 游戏手柄按键'L2'
     * @since 22
     */
    KEYCODE_BUTTON_L2 = 2309,
    /**
     * @brief 游戏手柄按键'R2'
     * @since 22
     */
    KEYCODE_BUTTON_R2 = 2310,
    /**
     * @brief 游戏手柄按键'Select'
     * @since 22
     */
    KEYCODE_BUTTON_SELECT = 2311,
    /**
     * @brief 游戏手柄按键'Start'
     * @since 22
     */
    KEYCODE_BUTTON_START = 2312,
    /**
     * @brief 游戏手柄按键'Mode'
     * @since 22
     */
    KEYCODE_BUTTON_MODE = 2313,
    /**
     * @brief 游戏手柄按键'THUMBL'
     * @since 22
     */
    KEYCODE_BUTTON_THUMBL = 2314,
    /**
     * @brief 游戏手柄按键'THUMBR'
     * @since 22
     */
    KEYCODE_BUTTON_THUMBR = 2315,
    /**
     * @brief 睡眠键
     * @since 22
     */
    KEYCODE_SLEEP = 2600,
    /**
     * @brief 日文全宽/半宽键
     * @since 22
     */
    KEYCODE_ZENKAKU_HANKAKU = 2601,
    /**
     * @brief 国际键盘扩展键
     * @since 22
     */
    KEYCODE_102ND = 2602,
    /**
     * @brief 日文Ro键
     * @since 22
     */
    KEYCODE_RO = 2603,
    /**
     * @brief 日文片假名键
     * @since 22
     */
    KEYCODE_KATAKANA = 2604,
    /**
     * @brief 日文平假名键
     * @since 22
     */
    KEYCODE_HIRAGANA = 2605,
    /**
     * @brief 日文转换键
     * @since 22
     */
    KEYCODE_HENKAN = 2606,
    /**
     * @brief 日语片假名/平假名键
     * @since 22
     */
    KEYCODE_KATAKANA_HIRAGANA = 2607,
    /**
     * @brief 日文非转换键
     * @since 22
     */
    KEYCODE_MUHENKAN = 2608,
    /**
     * @brief 换行键
     * @since 22
     */
    KEYCODE_LINEFEED = 2609,
    /**
     * @brief 宏键
     * @since 22
     */
    KEYCODE_MACRO = 2610,
    /**
     * @brief 数字键盘上的加号/减号键
     * @since 22
     */
    KEYCODE_NUMPAD_PLUSMINUS = 2611,
    /**
     * @brief 扩展键
     * @since 22
     */
    KEYCODE_SCALE = 2612,
    /**
     * @brief 日文韩语键
     * @since 22
     */
    KEYCODE_HANGUEL = 2613,
    /**
     * @brief 日文汉语键
     * @since 22
     */
    KEYCODE_HANJA = 2614,
    /**
     * @brief 日元键
     * @since 22
     */
    KEYCODE_YEN = 2615,
    /**
     * @brief 停止键
     * @since 22
     */
    KEYCODE_STOP = 2616,
    /**
     * @brief 重复键
     * @since 22
     */
    KEYCODE_AGAIN = 2617,
    /**
     * @brief 道具键
     * @since 22
     */
    KEYCODE_PROPS = 2618,
    /**
     * @brief 撤销键
     * @since 22
     */
    KEYCODE_UNDO = 2619,
    /**
     * @brief 复制键
     * @since 22
     */
    KEYCODE_COPY = 2620,
    /**
     * @brief 打开键
     * @since 22
     */
    KEYCODE_OPEN = 2621,
    /**
     * @brief 粘贴键
     * @since 22
     */
    KEYCODE_PASTE = 2622,
    /**
     * @brief 查找键
     * @since 22
     */
    KEYCODE_FIND = 2623,
    /**
     * @brief 剪切键
     * @since 22
     */
    KEYCODE_CUT = 2624,
    /**
     * @brief 帮助键
     * @since 22
     */
    KEYCODE_HELP = 2625,
    /**
     * @brief 计算器特殊功能键，用于启动计算器应用程序。
     * @since 22
     */
    KEYCODE_CALC = 2626,
    /**
     * @brief 文件按键
     * @since 22
     */
    KEYCODE_FILE = 2627,
    /**
     * @brief 书签键
     * @since 22
     */
    KEYCODE_BOOKMARKS = 2628,
    /**
     * @brief Page Down键
     * @since 22
     */
    KEYCODE_NEXT = 2629,
    /**
     * @brief 多媒体键：播放/暂停。<br/>与KEYCODE_MEDIA_PLAY_PAUSE的区别为：<br/>KEYCODE_PLAYPAUSE是较早的定义，
     * KEYCODE_MEDIA_PLAY_PAUSE为现代媒体键设备设计，常见于较新的媒体键设备。
     * @since 22
     */
    KEYCODE_PLAYPAUSE = 2630,
    /**
     * @brief Page Up键
     * @since 22
     */
    KEYCODE_PREVIOUS = 2631,
    /**
     * @brief CD停止键
     * @since 22
     */
    KEYCODE_STOPCD = 2632,
    /**
     * @brief 配置键
     * @since 22
     */
    KEYCODE_CONFIG = 2634,
    /**
     * @brief 刷新键
     * @since 22
     */
    KEYCODE_REFRESH = 2635,
    /**
     * @brief 退出键
     * @since 22
     */
    KEYCODE_EXIT = 2636,
    /**
     * @brief 编辑键
     * @since 22
     */
    KEYCODE_EDIT = 2637,
    /**
     * @brief 向上滚动键
     * @since 22
     */
    KEYCODE_SCROLLUP = 2638,
    /**
     * @brief 向下滚动键
     * @since 22
     */
    KEYCODE_SCROLLDOWN = 2639,
    /**
     * @brief 新建键
     * @since 22
     */
    KEYCODE_NEW = 2640,
    /**
     * @brief 恢复键
     * @since 22
     */
    KEYCODE_REDO = 2641,
    /**
     * @brief 关闭键
     * @since 22
     */
    KEYCODE_CLOSE = 2642,
    /**
     * @brief 播放键
     * @since 22
     */
    KEYCODE_PLAY = 2643,
    /**
     * @brief 低音增强键
     * @since 22
     */
    KEYCODE_BASSBOOST = 2644,
    /**
     * @brief 打印键
     * @since 22
     */
    KEYCODE_PRINT = 2645,
    /**
     * @brief 聊天键
     * @since 22
     */
    KEYCODE_CHAT = 2646,
    /**
     * @brief 金融键
     * @since 22
     */
    KEYCODE_FINANCE = 2647,
    /**
     * @brief 取消键
     * @since 22
     */
    KEYCODE_CANCEL = 2648,
    /**
     * @brief 键盘灯光切换键
     * @since 22
     */
    KEYCODE_KBDILLUM_TOGGLE = 2649,
    /**
     * @brief 键盘灯光调暗键
     * @since 22
     */
    KEYCODE_KBDILLUM_DOWN = 2650,
    /**
     * @brief 键盘灯光调亮键
     * @since 22
     */
    KEYCODE_KBDILLUM_UP = 2651,
    /**
     * @brief 发送键
     * @since 22
     */
    KEYCODE_SEND = 2652,
    /**
     * @brief 答复键
     * @since 22
     */
    KEYCODE_REPLY = 2653,
    /**
     * @brief 邮件转发键
     * @since 22
     */
    KEYCODE_FORWARDMAIL = 2654,
    /**
     * @brief 保存键
     * @since 22
     */
    KEYCODE_SAVE = 2655,
    /**
     * @brief 文件键
     * @since 22
     */
    KEYCODE_DOCUMENTS = 2656,
    /**
     * @brief 下一个视频键
     * @since 22
     */
    KEYCODE_VIDEO_NEXT = 2657,
    /**
     * @brief 上一个视频键
     * @since 22
     */
    KEYCODE_VIDEO_PREV = 2658,
    /**
     * @brief 背光渐变键
     * @since 22
     */
    KEYCODE_BRIGHTNESS_CYCLE = 2659,
    /**
     * @brief 亮度调节为0键
     * @since 22
     */
    KEYCODE_BRIGHTNESS_ZERO = 2660,
    /**
     * @brief 显示关闭键
     * @since 22
     */
    KEYCODE_DISPLAY_OFF = 2661,
    /**
     * @brief 游戏手柄上的各种按键
     * @since 22
     */
    KEYCODE_BTN_MISC = 2662,
    /**
     * @brief 进入键
     * @since 22
     */
    KEYCODE_GOTO = 2663,
    /**
     * @brief 信息查看键
     * @since 22
     */
    KEYCODE_INFO = 2664,
    /**
     * @brief 程序键
     * @since 22
     */
    KEYCODE_PROGRAM = 2665,
    /**
     * @brief 个人录像机（PVR）键
     * @since 22
     */
    KEYCODE_PVR = 2666,
    /**
     * @brief 字幕键
     * @since 22
     */
    KEYCODE_SUBTITLE = 2667,
    /**
     * @brief 全屏键
     * @since 22
     */
    KEYCODE_FULL_SCREEN = 2668,
    /**
     * @brief 键盘
     * @since 22
     */
    KEYCODE_KEYBOARD = 2669,
    /**
     * @brief 屏幕纵横比调节键
     * @since 22
     */
    KEYCODE_ASPECT_RATIO = 2670,
    /**
     * @brief 端口控制键
     * @since 22
     */
    KEYCODE_PC = 2671,
    /**
     * @brief TV键
     * @since 22
     */
    KEYCODE_TV = 2672,
    /**
     * @brief TV键2
     * @since 22
     */
    KEYCODE_TV2 = 2673,
    /**
     * @brief 录像机开启键
     * @since 22
     */
    KEYCODE_VCR = 2674,
    /**
     * @brief 录像机开启键2
     * @since 22
     */
    KEYCODE_VCR2 = 2675,
    /**
     * @brief SIM卡应用工具包（SAT）键
     * @since 22
     */
    KEYCODE_SAT = 2676,
    /**
     * @brief CD键
     * @since 22
     */
    KEYCODE_CD = 2677,
    /**
     * @brief 磁带键
     * @since 22
     */
    KEYCODE_TAPE = 2678,
    /**
     * @brief 调谐器键
     * @since 22
     */
    KEYCODE_TUNER = 2679,
    /**
     * @brief 播放器键
     * @since 22
     */
    KEYCODE_PLAYER = 2680,
    /**
     * @brief DVD键
     * @since 22
     */
    KEYCODE_DVD = 2681,
    /**
     * @brief 音频键
     * @since 22
     */
    KEYCODE_AUDIO = 2682,
    /**
     * @brief 视频键
     * @since 22
     */
    KEYCODE_VIDEO = 2683,
    /**
     * @brief 备忘录键
     * @since 22
     */
    KEYCODE_MEMO = 2684,
    /**
     * @brief 日历键
     * @since 22
     */
    KEYCODE_CALENDAR = 2685,
    /**
     * @brief 红色指示器
     * @since 22
     */
    KEYCODE_RED = 2686,
    /**
     * @brief 绿色指示器
     * @since 22
     */
    KEYCODE_GREEN = 2687,
    /**
     * @brief 黄色指示器
     * @since 22
     */
    KEYCODE_YELLOW = 2688,
    /**
     * @brief 蓝色指示器
     * @since 22
     */
    KEYCODE_BLUE = 2689,
    /**
     * @brief 频道向上键
     * @since 22
     */
    KEYCODE_CHANNELUP = 2690,
    /**
     * @brief 频道向下键
     * @since 22
     */
    KEYCODE_CHANNELDOWN = 2691,
    /**
     * @brief 末尾键
     * @since 22
     */
    KEYCODE_LAST = 2692,
    /**
     * @brief 重启键
     * @since 22
     */
    KEYCODE_RESTART = 2693,
    /**
     * @brief 慢速键
     * @since 22
     */
    KEYCODE_SLOW = 2694,
    /**
     * @brief 随机播放键
     * @since 22
     */
    KEYCODE_SHUFFLE = 2695,
    /**
     * @brief 可视电话键
     * @since 22
     */
    KEYCODE_VIDEOPHONE = 2696,
    /**
     * @brief 游戏键
     * @since 22
     */
    KEYCODE_GAMES = 2697,
    /**
     * @brief 放大键
     * @since 22
     */
    KEYCODE_ZOOMIN = 2698,
    /**
     * @brief 缩小键
     * @since 22
     */
    KEYCODE_ZOOMOUT = 2699,
    /**
     * @brief 缩放重置键
     * @since 22
     */
    KEYCODE_ZOOMRESET = 2700,
    /**
     * @brief 文字处理键
     * @since 22
     */
    KEYCODE_WORDPROCESSOR = 2701,
    /**
     * @brief 编辑器键
     * @since 22
     */
    KEYCODE_EDITOR = 2702,
    /**
     * @brief 电子表格键
     * @since 22
     */
    KEYCODE_SPREADSHEET = 2703,
    /**
     * @brief 图形编辑器键
     * @since 22
     */
    KEYCODE_GRAPHICSEDITOR = 2704,
    /**
     * @brief 演示文稿键
     * @since 22
     */
    KEYCODE_PRESENTATION = 2705,
    /**
     * @brief 数据库键
     * @since 22
     */
    KEYCODE_DATABASE = 2706,
    /**
     * @brief 新闻键
     * @since 22
     */
    KEYCODE_NEWS = 2707,
    /**
     * @brief 语音信箱
     * @since 22
     */
    KEYCODE_VOICEMAIL = 2708,
    /**
     * @brief 通讯簿
     * @since 22
     */
    KEYCODE_ADDRESSBOOK = 2709,
    /**
     * @brief 通信键
     * @since 22
     */
    KEYCODE_MESSENGER = 2710,
    /**
     * @brief 亮度切换键
     * @since 22
     */
    KEYCODE_BRIGHTNESS_TOGGLE = 2711,
    /**
     * @brief 拼写检查键
     * @since 22
     */
    KEYCODE_SPELLCHECK = 2712,
    /**
     * @brief 终端锁/屏幕保护程序
     * @since 22
     */
    KEYCODE_COFFEE = 2713,
    /**
     * @brief 媒体循环键
     * @since 22
     */
    KEYCODE_MEDIA_REPEAT = 2714,
    /**
     * @brief 图像键
     * @since 22
     */
    KEYCODE_IMAGES = 2715,
    /**
     * @brief 按键配置键
     * @since 22
     */
    KEYCODE_BUTTONCONFIG = 2716,
    /**
     * @brief 任务管理器
     * @since 22
     */
    KEYCODE_TASKMANAGER = 2717,
    /**
     * @brief 日志按键
     * @since 22
     */
    KEYCODE_JOURNAL = 2718,
    /**
     * @brief 控制面板键
     * @since 22
     */
    KEYCODE_CONTROLPANEL = 2719,
    /**
     * @brief 应用程序选择键
     * @since 22
     */
    KEYCODE_APPSELECT = 2720,
    /**
     * @brief 屏幕保护程序键
     * @since 22
     */
    KEYCODE_SCREENSAVER = 2721,
    /**
     * @brief 智慧键
     * @since 22
     */
    KEYCODE_ASSISTANT = 2722,
    /**
     * @brief 下一个键盘布局键
     * @since 22
     */
    KEYCODE_KBD_LAYOUT_NEXT = 2723,
    /**
     * @brief 最小亮度键
     * @since 22
     */
    KEYCODE_BRIGHTNESS_MIN = 2724,
    /**
     * @brief 最大亮度键
     * @since 22
     */
    KEYCODE_BRIGHTNESS_MAX = 2725,
    /**
     * @brief 键盘输入Assist_Previous，查看输入法输入记录。
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_PREV = 2726,
    /**
     * @brief 键盘输入Assist_Next，查看输入法输入拓展。
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_NEXT = 2727,
    /**
     * @brief 键盘输入Assist_Previous，切换输入组中上一个输入法。
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_PREVGROUP = 2728,
    /**
     * @brief 键盘输入Assist_Next，切换输入组中下一个输入法。
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_NEXTGROUP = 2729,
    /**
     * @brief 键盘输入Assist_Accept
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_ACCEPT = 2730,
    /**
     * @brief 键盘输入Assist_Cancel
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_CANCEL = 2731,
    /**
     * @brief 鼠标AI助手键
     * @since 26.0.0
     */
    KEYCODE_MOUSE_ASSISTANT = 2732,
    /**
     * @brief 鼠标智慧框选键
     * @since 26.0.0
     */
    KEYCODE_MOUSE_INTELLIGENCE_SELECTION = 2733,
    /**
     * @brief 手机触摸屏单击事件，在熄屏显示状态下使用。
     * @since 26.0.0
     */
    KEYCODE_AOD_SINGLE_CLICK = 2740,
    /**
     * @brief 挡风玻璃除雾器开关
     * @since 22
     */
    KEYCODE_FRONT = 2800,
    /**
     * @brief 设置键
     * @since 22
     */
    KEYCODE_SETUP = 2801,
    /**
     * @brief 唤醒键
     * @since 22
     */
    KEYCODE_WAKEUP = 2802,
    /**
     * @brief 发送文件按键
     * @since 22
     */
    KEYCODE_SENDFILE = 2803,
    /**
     * @brief 删除文件按键
     * @since 22
     */
    KEYCODE_DELETEFILE = 2804,
    /**
     * @brief 文件传输（XFER）按键
     * @since 22
     */
    KEYCODE_XFER = 2805,
    /**
     * @brief 程序键1
     * @since 22
     */
    KEYCODE_PROG1 = 2806,
    /**
     * @brief 程序键2
     * @since 22
     */
    KEYCODE_PROG2 = 2807,
    /**
     * @brief DOS面板键
     * @since 22
     */
    KEYCODE_MSDOS = 2808,
    /**
     * @brief 屏幕锁定键
     * @since 22
     */
    KEYCODE_SCREENLOCK = 2809,
    /**
     * @brief 方向旋转显示键
     * @since 22
     */
    KEYCODE_DIRECTION_ROTATE_DISPLAY = 2810,
    /**
     * @brief 窗口切换键
     * @since 22
     */
    KEYCODE_CYCLEWINDOWS = 2811,
    /**
     * @brief 按键
     * @since 22
     */
    KEYCODE_COMPUTER = 2812,
    /**
     * @brief 弹出CD键
     * @since 22
     */
    KEYCODE_EJECTCLOSECD = 2813,
    /**
     * @brief ISO键
     * @since 22
     */
    KEYCODE_ISO = 2814,
    /**
     * @brief 移动键
     * @since 22
     */
    KEYCODE_MOVE = 2815,
    /**
     * @brief 按键'F13'
     * @since 22
     */
    KEYCODE_F13 = 2816,
    /**
     * @brief 按键'F14'
     * @since 22
     */
    KEYCODE_F14 = 2817,
    /**
     * @brief 按键'F15'
     * @since 22
     */
    KEYCODE_F15 = 2818,
    /**
     * @brief 按键'F16'
     * @since 22
     */
    KEYCODE_F16 = 2819,
    /**
     * @brief 按键'F17'
     * @since 22
     */
    KEYCODE_F17 = 2820,
    /**
     * @brief 按键'F18'
     * @since 22
     */
    KEYCODE_F18 = 2821,
    /**
     * @brief 按键'F19'
     * @since 22
     */
    KEYCODE_F19 = 2822,
    /**
     * @brief 按键'F20'
     * @since 22
     */
    KEYCODE_F20 = 2823,
    /**
     * @brief 按键'F21'
     * @since 22
     */
    KEYCODE_F21 = 2824,
    /**
     * @brief 按键'F22'
     * @since 22
     */
    KEYCODE_F22 = 2825,
    /**
     * @brief 按键'F23'
     * @since 22
     */
    KEYCODE_F23 = 2826,
    /**
     * @brief 按键'F24'
     * @since 22
     */
    KEYCODE_F24 = 2827,
    /**
     * @brief 程序键3
     * @since 22
     */
    KEYCODE_PROG3 = 2828,
    /**
     * @brief 程序键4
     * @since 22
     */
    KEYCODE_PROG4 = 2829,
    /**
     * @brief 仪表板
     * @since 22
     */
    KEYCODE_DASHBOARD = 2830,
    /**
     * @brief 挂起键
     * @since 22
     */
    KEYCODE_SUSPEND = 2831,
    /**
     * @brief 高阶路径键
     * @since 22
     */
    KEYCODE_HP = 2832,
    /**
     * @brief 音量键
     * @since 22
     */
    KEYCODE_SOUND = 2833,
    /**
     * @brief 疑问按键
     * @since 22
     */
    KEYCODE_QUESTION = 2834,
    /**
     * @brief 连接键
     * @since 22
     */
    KEYCODE_CONNECT = 2836,
    /**
     * @brief 运动按键
     * @since 22
     */
    KEYCODE_SPORT = 2837,
    /**
     * @brief 商城键
     * @since 22
     */
    KEYCODE_SHOP = 2838,
    /**
     * @brief 交替键
     * @since 22
     */
    KEYCODE_ALTERASE = 2839,
    /**
     * @brief 在可用视频之间循环输出（监视器/LCD/TV输出/等）。
     * @since 22
     */
    KEYCODE_SWITCHVIDEOMODE = 2841,
    /**
     * @brief 电池按键
     * @since 22
     */
    KEYCODE_BATTERY = 2842,
    /**
     * @brief 蓝牙按键
     * @since 22
     */
    KEYCODE_BLUETOOTH = 2843,
    /**
     * @brief 无线局域网
     * @since 22
     */
    KEYCODE_WLAN = 2844,
    /**
     * @brief 超宽带控制键
     * @since 22
     */
    KEYCODE_UWB = 2845,
    /**
     * @brief 移动网络控制键
     * @since 22
     */
    KEYCODE_WWAN_WIMAX = 2846,
    /**
     * @brief 控制所有收音机的键
     * @since 22
     */
    KEYCODE_RFKILL = 2847,
    /**
     * @brief 向上频道键
     * @since 22
     */
    KEYCODE_CHANNEL = 3001,
    /**
     * @brief 按键0
     * @since 22
     */
    KEYCODE_BTN_0 = 3100,
    /**
     * @brief 按键1
     * @since 22
     */
    KEYCODE_BTN_1 = 3101,
    /**
     * @brief 按键2
     * @since 22
     */
    KEYCODE_BTN_2 = 3102,
    /**
     * @brief 按键3
     * @since 22
     */
    KEYCODE_BTN_3 = 3103,
    /**
     * @brief 按键4
     * @since 22
     */
    KEYCODE_BTN_4 = 3104,
    /**
     * @brief 按键5
     * @since 22
     */
    KEYCODE_BTN_5 = 3105,
    /**
     * @brief 按键6
     * @since 22
     */
    KEYCODE_BTN_6 = 3106,
    /**
     * @brief 按键7
     * @since 22
     */
    KEYCODE_BTN_7 = 3107,
    /**
     * @brief 按键8
     * @since 22
     */
    KEYCODE_BTN_8 = 3108,
    /**
     * @brief 按键9
     * @since 22
     */
    KEYCODE_BTN_9 = 3109,
    /**
     * @brief 智能手表智感窗按键单击
     * @since 22
     */
    KEYCODE_DAGGER_CLICK = 3211,
    /**
     * @brief 智能手表智感窗按键双击
     * @since 22
     */
    KEYCODE_DAGGER_DOUBLE_CLICK = 3212,
    /**
     * @brief 智能手表智感窗按键长按
     * @since 22
     */
    KEYCODE_DAGGER_LONG_PRESS = 3213,
    /**
     * @brief 智能手表左按键
     * @since 22
     */
    KEYCODE_DIV = 3220,
    /**
     * @brief 自定义快捷键
     * @since 26.0.0
     */
    KEYCODE_XKEY = 3232,
    /**
     * @brief 智控键上滑
     * @since 26.0.0
     */
    KEYCODE_FINGERPRINT_SLIDE_UP = 3233,
    /**
     * @brief 智控键下滑
     * @since 26.0.0
     */
    KEYCODE_FINGERPRINT_SLIDE_DOWN = 3234
} Input_KeyCode;

#ifdef __cplusplus
}
#endif

#endif /* OH_KEY_CODE_H */
/** @} */