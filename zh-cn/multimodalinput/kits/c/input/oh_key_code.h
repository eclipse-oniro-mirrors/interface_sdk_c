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
 * @file oh_key_code.h
 *
 * @brief Defines the key event structure and related enumeration values.
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
     * 未知按键
     */
    KEYCODE_UNKNOWN = -1,

    /**
     * 功能（Fn）键
     */
    KEYCODE_FN = 0,
    /**
     * 功能（Home）键
     * @since 22
     */
    KEYCODE_HOME = 1,
    /**
     * 返回键
     * @since 22
     */
    KEYCODE_BACK = 2,

    /**
     * 搜索键
     * @since 22
     */
    KEYCODE_SEARCH = 9,
    /**
     * 多媒体键：播放/暂停。
     * 与KEYCODE_PLAYPAUSE的区别为：
     * KEYCODE_PLAYPAUSE是较早的定义，KEYCODE_MEDIA_PLAY_PAUSE为现代媒体键设备设计，常见于较新的媒体键设备。
     * @since 22
     */
    KEYCODE_MEDIA_PLAY_PAUSE = 10,
    /**
     * 光盘停止键
     * @since 22
     */
    KEYCODE_MEDIA_STOP = 11,
    /**
     * 多媒体键：下一首
     * @since 22
     */
    KEYCODE_MEDIA_NEXT = 12,
    /**
     * 多媒体键：上一首
     * @since 22
     */
    KEYCODE_MEDIA_PREVIOUS = 13,
    /**
     * 多媒体键：快退
     * @since 22
     */
    KEYCODE_MEDIA_REWIND = 14,
    /**
     * 多媒体键：快进
     * @since 22
     */
    KEYCODE_MEDIA_FAST_FORWARD = 15,

    /**
     * 音量增加键
     */
    KEYCODE_VOLUME_UP = 16,

    /**
     * 音量减小键
     */
    KEYCODE_VOLUME_DOWN = 17,

    /**
     * 电源键
     */
    KEYCODE_POWER = 18,

    /**
     * 拍照键
     */
    KEYCODE_CAMERA = 19,

    /**
     * 扬声器静音键
     */
    KEYCODE_VOLUME_MUTE = 22,

    /**
     * 话筒静音键
     */
    KEYCODE_MUTE = 23,

    /**
     * 亮度调节按键：调亮
     */
    KEYCODE_BRIGHTNESS_UP = 40,

    /**
     * 亮度调节按键：调暗
     */
    KEYCODE_BRIGHTNESS_DOWN = 41,

    /**
     * 按键'0'
     */
    KEYCODE_0 = 2000,

    /**
     * 按键'1'
     */
    KEYCODE_1 = 2001,

    /**
     * 按键'2'
     */
    KEYCODE_2 = 2002,

    /**
     * 按键'3'
     */
    KEYCODE_3 = 2003,

    /**
     * 按键'4'
     */
    KEYCODE_4 = 2004,

    /**
     * 按键'5'
     */
    KEYCODE_5 = 2005,

    /**
     * 按键'6'
     */
    KEYCODE_6 = 2006,

    /**
     * 按键'7'
     */
    KEYCODE_7 = 2007,

    /**
     * 按键'8'
     */
    KEYCODE_8 = 2008,

    /**
     * 按键'9'
     */
    KEYCODE_9 = 2009,

    /**
     * 按键'*'
     */
    KEYCODE_STAR = 2010,

    /**
     * 按键'#'
     */
    KEYCODE_POUND = 2011,

    /**
     * 导航键：向上
     */
    KEYCODE_DPAD_UP = 2012,

    /**
     * 导航键：向下
     */
    KEYCODE_DPAD_DOWN = 2013,

    /**
     * 导航键：向左
     */
    KEYCODE_DPAD_LEFT = 2014,

    /**
     * 导航键：向右
     */
    KEYCODE_DPAD_RIGHT = 2015,

    /**
     * 导航键：确定键
     */
    KEYCODE_DPAD_CENTER = 2016,

    /**
     * 按键'A'
     */
    KEYCODE_A = 2017,

    /**
     * 按键'B'
     */
    KEYCODE_B = 2018,

    /**
     * 按键'C'
     */
    KEYCODE_C = 2019,

    /**
     * 按键'D'
     */
    KEYCODE_D = 2020,

    /**
     * 按键'E'
     */
    KEYCODE_E = 2021,

    /**
     * 按键'F'
     */
    KEYCODE_F = 2022,

    /**
     * 按键'G'
     */
    KEYCODE_G = 2023,

    /**
     * 按键'H'
     */
    KEYCODE_H = 2024,

    /**
     * 按键'I'
     */
    KEYCODE_I = 2025,

    /**
     * 按键'J'
     */
    KEYCODE_J = 2026,

    /**
     * 按键'K'
     */
    KEYCODE_K = 2027,

    /**
     * 按键'L'
     */
    KEYCODE_L = 2028,

    /**
     * 按键'M'
     */
    KEYCODE_M = 2029,

    /**
     * 按键'N'
     */
    KEYCODE_N = 2030,

    /**
     * 按键'O'
     */
    KEYCODE_O = 2031,

    /**
     * 按键'P'
     */
    KEYCODE_P = 2032,

    /**
     * 按键'Q'
     */
    KEYCODE_Q = 2033,

    /**
     * 按键'R'
     */
    KEYCODE_R = 2034,

    /**
     * 按键'S'
     */
    KEYCODE_S = 2035,

    /**
     * 按键'T'
     */
    KEYCODE_T = 2036,

    /**
     * 按键'U'
     */
    KEYCODE_U = 2037,

    /**
     * 按键'V'
     */
    KEYCODE_V = 2038,

    /**
     * 按键'W'
     */
    KEYCODE_W = 2039,

    /**
     * 按键'X'
     */
    KEYCODE_X = 2040,

    /**
     * 按键'Y'
     */
    KEYCODE_Y = 2041,

    /**
     * 按键'Z'
     */
    KEYCODE_Z = 2042,

    /**
     * 按键','
     */
    KEYCODE_COMMA = 2043,

    /**
     * 按键'.'
     */
    KEYCODE_PERIOD = 2044,

    /**
     * 左Alt键
     */
    KEYCODE_ALT_LEFT = 2045,

    /**
     * 右Alt键
     */
    KEYCODE_ALT_RIGHT = 2046,

    /**
     * 左Shift键
     */
    KEYCODE_SHIFT_LEFT = 2047,

    /**
     * 右Shift键
     */
    KEYCODE_SHIFT_RIGHT = 2048,

    /**
     * Tab键
     */
    KEYCODE_TAB = 2049,

    /**
     * 空格键
     */
    KEYCODE_SPACE = 2050,

    /**
     * 符号修改器按键
     */
    KEYCODE_SYM = 2051,

    /**
     * 浏览器功能键，此键用于启动浏览器应用程序。
     */
    KEYCODE_EXPLORER = 2052,

    /**
     * 电子邮件功能键，此键用于启动电子邮件应用程序。
     */
    KEYCODE_ENVELOPE = 2053,

    /**
     * 回车键
     */
    KEYCODE_ENTER = 2054,

    /**
     * 退格键
     */
    KEYCODE_DEL = 2055,

    /**
     * 按键'*'
     */
    KEYCODE_GRAVE = 2056,

    /**
     * 按键'-'
     */
    KEYCODE_MINUS = 2057,

    /**
     * 按键'='
     */
    KEYCODE_EQUALS = 2058,

    /**
     * 按键'['
     */
    KEYCODE_LEFT_BRACKET = 2059,

    /**
     * 按键']'
     */
    KEYCODE_RIGHT_BRACKET = 2060,

    /**
     * 按键'\'
     */
    KEYCODE_BACKSLASH = 2061,

    /**
     * 按键';'
     */
    KEYCODE_SEMICOLON = 2062,

    /**
     * 按键''' (单引号)
     */
    KEYCODE_APOSTROPHE = 2063,

    /**
     * 按键'/'
     */
    KEYCODE_SLASH = 2064,

    /**
     * Key @
     */
    KEYCODE_AT = 2065,

    /**
     * 按键'+'
     */
    KEYCODE_PLUS = 2066,

    /**
     * 菜单键
     */
    KEYCODE_MENU = 2067,

    /**
     * 向上翻页键
     */
    KEYCODE_PAGE_UP = 2068,

    /**
     * 向下翻页键
     */
    KEYCODE_PAGE_DOWN = 2069,

    /**
     * Esc键
     */
    KEYCODE_ESCAPE = 2070,

    /**
     * 删除键
     */
    KEYCODE_FORWARD_DEL = 2071,

    /**
     * 左Ctrl键
     */
    KEYCODE_CTRL_LEFT = 2072,

    /**
     * 右Ctrl键
     */
    KEYCODE_CTRL_RIGHT = 2073,

    /**
     * 大写锁定键
     */
    KEYCODE_CAPS_LOCK = 2074,

    /**
     * 滚动锁定键
     */
    KEYCODE_SCROLL_LOCK = 2075,

    /**
     * 左Meta键
     */
    KEYCODE_META_LEFT = 2076,

    /**
     * 右Meta键
     */
    KEYCODE_META_RIGHT = 2077,

    /**
     * 功能键
     */
    KEYCODE_FUNCTION = 2078,

    /**
     * 系统请求/打印屏幕键
     */
    KEYCODE_SYSRQ = 2079,

    /**
     * Break/Pause键
     */
    KEYCODE_BREAK = 2080,

    /**
     * 光标移动到开始键
     */
    KEYCODE_MOVE_HOME = 2081,

    /**
     * 光标移动到末尾键
     */
    KEYCODE_MOVE_END = 2082,

    /**
     * 插入键
     */
    KEYCODE_INSERT = 2083,

    /**
     * 前进键
     */
    KEYCODE_FORWARD = 2084,

    /**
     * 多媒体键：播放
     */
    KEYCODE_MEDIA_PLAY = 2085,

    /**
     * 光盘暂停键
     */
    KEYCODE_MEDIA_PAUSE = 2086,

    /**
     * 光盘关闭键
     */
    KEYCODE_MEDIA_CLOSE = 2087,

    /**
     * 光盘弹出键
     */
    KEYCODE_MEDIA_EJECT = 2088,

    /**
     * 多媒体键：录音
     */
    KEYCODE_MEDIA_RECORD = 2089,

    /**
     * 按键'F1'
     */
    KEYCODE_F1 = 2090,

    /**
     * 按键'F2'
     */
    KEYCODE_F2 = 2091,

    /**
     * 按键'F3'
     */
    KEYCODE_F3 = 2092,

    /**
     * 按键'F4'
     */
    KEYCODE_F4 = 2093,

    /**
     * 按键'F5'
     */
    KEYCODE_F5 = 2094,

    /**
     * 按键'F6'
     */
    KEYCODE_F6 = 2095,

    /**
     * 按键'F7'
     */
    KEYCODE_F7 = 2096,

    /**
     * 按键'F8'
     */
    KEYCODE_F8 = 2097,

    /**
     * 按键'F9'
     */
    KEYCODE_F9 = 2098,

    /**
     * 按键'F10'
     */
    KEYCODE_F10 = 2099,

    /**
     * 按键'F11'
     */
    KEYCODE_F11 = 2100,

    /**
     * 按键'F12'
     */
    KEYCODE_F12 = 2101,

    /**
     * 小键盘锁
     */
    KEYCODE_NUM_LOCK = 2102,

    /**
     * 小键盘按键'0'
     */
    KEYCODE_NUMPAD_0 = 2103,

    /**
     * 小键盘按键'1'
     */
    KEYCODE_NUMPAD_1 = 2104,

    /**
     * 小键盘按键'2'
     */
    KEYCODE_NUMPAD_2 = 2105,

    /**
     * 小键盘按键'3'
     */
    KEYCODE_NUMPAD_3 = 2106,

    /**
     * 小键盘按键'4'
     */
    KEYCODE_NUMPAD_4 = 2107,

    /**
     * 小键盘按键'5'
     */
    KEYCODE_NUMPAD_5 = 2108,

    /**
     * 小键盘按键'6'
     */
    KEYCODE_NUMPAD_6 = 2109,

    /**
     * 小键盘按键'7'
     */
    KEYCODE_NUMPAD_7 = 2110,

    /**
     * 小键盘按键'8'
     */
    KEYCODE_NUMPAD_8 = 2111,

    /**
     * 小键盘按键'9'
     */
    KEYCODE_NUMPAD_9 = 2112,

    /**
     * 小键盘按键'/'
     */
    KEYCODE_NUMPAD_DIVIDE = 2113,

    /**
     * 小键盘按键'*'
     */
    KEYCODE_NUMPAD_MULTIPLY = 2114,

    /**
     * 小键盘按键'-'
     */
    KEYCODE_NUMPAD_SUBTRACT = 2115,

    /**
     * 小键盘按键'+'
     */
    KEYCODE_NUMPAD_ADD = 2116,

    /**
     * 小键盘按键'.'
     */
    KEYCODE_NUMPAD_DOT = 2117,

    /**
     * 小键盘按键','
     */
    KEYCODE_NUMPAD_COMMA = 2118,

    /**
     * 小键盘按键回车
     */
    KEYCODE_NUMPAD_ENTER = 2119,

    /**
     * 小键盘按键'='
     */
    KEYCODE_NUMPAD_EQUALS = 2120,

    /**
     * 小键盘按键'('
     */
    KEYCODE_NUMPAD_LEFT_PAREN = 2121,

    /**
     * 小键盘按键')'
     */
    KEYCODE_NUMPAD_RIGHT_PAREN = 2122,
    /**
     * 虚拟多任务键
     * @since 22
     */
    KEYCODE_VIRTUAL_MULTITASK = 2210,
    /**
     * 游戏手柄按键'A'
     * @since 22
     */
    KEYCODE_BUTTON_A = 2301,
    /**
     * 游戏手柄按键'B'
     * @since 22
     */
    KEYCODE_BUTTON_B = 2302,
    /**
     * 游戏手柄按键'X'
     * @since 22
     */
    KEYCODE_BUTTON_X = 2304,
    /**
     * 游戏手柄按键'Y'
     * @since 22
     */
    KEYCODE_BUTTON_Y = 2305,
    /**
     * 游戏手柄按键'L1'
     * @since 22
     */
    KEYCODE_BUTTON_L1 = 2307,
    /**
     * 游戏手柄按键'R1'
     * @since 22
     */
    KEYCODE_BUTTON_R1 = 2308,
    /**
     * 游戏手柄按键'L2'
     * @since 22
     */
    KEYCODE_BUTTON_L2 = 2309,
    /**
     * 游戏手柄按键'R2'
     * @since 22
     */
    KEYCODE_BUTTON_R2 = 2310,
    /**
     * 游戏手柄按键'Select'
     * @since 22
     */
    KEYCODE_BUTTON_SELECT = 2311,
    /**
     * 游戏手柄按键'Start'
     * @since 22
     */
    KEYCODE_BUTTON_START = 2312,
    /**
     * 游戏手柄按键'Mode'
     * @since 22
     */
    KEYCODE_BUTTON_MODE = 2313,
    /**
     * 游戏手柄按键'THUMBL'
     * @since 22
     */
    KEYCODE_BUTTON_THUMBL = 2314,
    /**
     * 游戏手柄按键'THUMBR'
     * @since 22
     */
    KEYCODE_BUTTON_THUMBR = 2315,
    /**
     *睡眠键
     * @since 22
     */
    KEYCODE_SLEEP = 2600,
    /**
     * 日文全宽/半宽键
     * @since 22
     */
    KEYCODE_ZENKAKU_HANKAKU = 2601,
    /**
     *国际键盘扩展键
     * @since 22
     */
    KEYCODE_102ND = 2602,
    /**
     * 日文Ro键
     * @since 22
     */
    KEYCODE_RO = 2603,
    /**
     * 日文片假名键
     * @since 22
     */
    KEYCODE_KATAKANA = 2604,
    /**
     * 日文平假名键
     * @since 22
     */
    KEYCODE_HIRAGANA = 2605,
    /**
     * 日文转换键
     * @since 22
     */
    KEYCODE_HENKAN = 2606,
    /**
     * 日语片假名/平假名键
     * @since 22
     */
    KEYCODE_KATAKANA_HIRAGANA = 2607,
    /**
     * 日文非转换键
     * @since 22
     */
    KEYCODE_MUHENKAN = 2608,
    /**
     * 换行键
     * @since 22
     */
    KEYCODE_LINEFEED = 2609,
    /**
     * 宏键
     * @since 22
     */
    KEYCODE_MACRO = 2610,
    /**
     * 数字键盘上的加号/减号键
     * @since 22
     */
    KEYCODE_NUMPAD_PLUSMINUS = 2611,
    /**
     * 扩展键
     * @since 22
     */
    KEYCODE_SCALE = 2612,
    /**
     * 日文韩语键
     * @since 22
     */
    KEYCODE_HANGUEL = 2613,
    /**
     * 日文汉语键
     * @since 22
     */
    KEYCODE_HANJA = 2614,
    /**
     * 日元键
     * @since 22
     */
    KEYCODE_YEN = 2615,
    /**
     * 停止键
     * @since 22
     */
    KEYCODE_STOP = 2616,
    /**
     * 重复键
     * @since 22
     */
    KEYCODE_AGAIN = 2617,
    /**
     * 道具键
     * @since 22
     */
    KEYCODE_PROPS = 2618,
    /**
     * 撤消键
     * @since 22
     */
    KEYCODE_UNDO = 2619,
    /**
     * 复制键
     * @since 22
     */
    KEYCODE_COPY = 2620,
    /**
     * 打开键
     * @since 22
     */
    KEYCODE_OPEN = 2621,
    /**
     * 粘贴键
     * @since 22
     */
    KEYCODE_PASTE = 2622,
    /**
     * 查找键
     * @since 22
     */
    KEYCODE_FIND = 2623,
    /**
     * 剪切键
     * @since 22
     */
    KEYCODE_CUT = 2624,
    /**
     * 帮助键
     * @since 22
     */
    KEYCODE_HELP = 2625,
    /**
     * 计算器特殊功能键，用于启动计算器应用程序。
     * @since 22
     */
    KEYCODE_CALC = 2626,
    /**
     * 文件按键
     * @since 22
     */
    KEYCODE_FILE = 2627,
    /**
     * 书签键
     * @since 22
     */
    KEYCODE_BOOKMARKS = 2628,
    /**
     * Page Down键
     * @since 22
     */
    KEYCODE_NEXT = 2629,
    /**
     * 多媒体键：播放/暂停。
     * 与KEYCODE_MEDIA_PLAY_PAUSE的区别为：
     * KEYCODE_PLAYPAUSE是较早的定义，KEYCODE_MEDIA_PLAY_PAUSE为现代媒体键设备设计，常见于较新的媒体键设备。
     * @since 22
     */
    KEYCODE_PLAYPAUSE = 2630,
    /**
     * Page Up键
     * @since 22
     */
    KEYCODE_PREVIOUS = 2631,
    /**
     * CD停止键
     * @since 22
     */
    KEYCODE_STOPCD = 2632,
    /**
     * 配置键
     * @since 22
     */
    KEYCODE_CONFIG = 2634,
    /**
     * 刷新键
     * @since 22
     */
    KEYCODE_REFRESH = 2635,
    /**
     * 退出键
     * @since 22
     */
    KEYCODE_EXIT = 2636,
    /**
     * 编辑键
     * @since 22
     */
    KEYCODE_EDIT = 2637,
    /**
     * 向上滚动键
     * @since 22
     */
    KEYCODE_SCROLLUP = 2638,
    /**
     * 向下滚动键
     * @since 22
     */
    KEYCODE_SCROLLDOWN = 2639,
    /**
     * 新建键
     * @since 22
     */
    KEYCODE_NEW = 2640,
    /**
     * 恢复键
     * @since 22
     */
    KEYCODE_REDO = 2641,
    /**
     * 关闭键
     * @since 22
     */
    KEYCODE_CLOSE = 2642,
    /**
     * 播放键
     * @since 22
     */
    KEYCODE_PLAY = 2643,
    /**
     *低音增强键
     * @since 22
     */
    KEYCODE_BASSBOOST = 2644,
    /**
     * 打印键
     * @since 22
     */
    KEYCODE_PRINT = 2645,
    /**
     * 聊天键
     * @since 22
     */
    KEYCODE_CHAT = 2646,
    /**
     * 金融键
     * @since 22
     */
    KEYCODE_FINANCE = 2647,
    /**
     * 取消键
     * @since 22
     */
    KEYCODE_CANCEL = 2648,
    /**
     * 键盘灯光切换键
     * @since 22
     */
    KEYCODE_KBDILLUM_TOGGLE = 2649,
    /**
     * 键盘灯光调暗键
     * @since 22
     */
    KEYCODE_KBDILLUM_DOWN = 2650,
    /**
     * 键盘灯光调亮键
     * @since 22
     */
    KEYCODE_KBDILLUM_UP = 2651,
    /**
     * 发送键
     * @since 22
     */
    KEYCODE_SEND = 2652,
    /**
     * 答复键
     * @since 22
     */
    KEYCODE_REPLY = 2653,
    /**
     * 邮件转发键
     * @since 22
     */
    KEYCODE_FORWARDMAIL = 2654,
    /**
     * 保存键
     * @since 22
     */
    KEYCODE_SAVE = 2655,
    /**
     * 文件键
     * @since 22
     */
    KEYCODE_DOCUMENTS = 2656,
    /**
     * 下一个视频键
     * @since 22
     */
    KEYCODE_VIDEO_NEXT = 2657,
    /**
     * 上一个视频键
     * @since 22
     */
    KEYCODE_VIDEO_PREV = 2658,
    /**
     * 背光渐变键
     * @since 22
     */
    KEYCODE_BRIGHTNESS_CYCLE = 2659,
    /**
     * 亮度调节为0键
     * @since 22
     */
    KEYCODE_BRIGHTNESS_ZERO = 2660,
    /**
     * 显示关闭键
     * @since 22
     */
    KEYCODE_DISPLAY_OFF = 2661,
    /**
     * 游戏手柄上的各种按键
     * @since 22
     */
    KEYCODE_BTN_MISC = 2662,
    /**
     * 进入键
     * @since 22
     */
    KEYCODE_GOTO = 2663,
    /**
     * 信息查看键
     * @since 22
     */
    KEYCODE_INFO = 2664,
    /**
     * 程序键
     * @since 22
     */
    KEYCODE_PROGRAM = 2665,
    /**
     * 个人录像机（PVR）键
     * @since 22
     */
    KEYCODE_PVR = 2666,
    /**
     * 字幕键
     * @since 22
     */
    KEYCODE_SUBTITLE = 2667,
    /**
     * 全屏键
     * @since 22
     */
    KEYCODE_FULL_SCREEN = 2668,
    /**
     * 键盘
     * @since 22
     */
    KEYCODE_KEYBOARD = 2669,
    /**
     * 屏幕纵横比调节键
     * @since 22
     */
    KEYCODE_ASPECT_RATIO = 2670,
    /**
     * 端口控制键
     * @since 22
     */
    KEYCODE_PC = 2671,
    /**
     * TV键
     * @since 22
     */
    KEYCODE_TV = 2672,
    /**
     * TV键2
     * @since 22
     */
    KEYCODE_TV2 = 2673,
    /**
     * 录像机开启键
     * @since 22
     */
    KEYCODE_VCR = 2674,
    /**
     * 录像机开启键2
     * @since 22
     */
    KEYCODE_VCR2 = 2675,
    /**
     * SIM卡应用工具包（SAT）键
     * @since 22
     */
    KEYCODE_SAT = 2676,
    /**
     * CD键
     * @since 22
     */
    KEYCODE_CD = 2677,
    /**
     * 磁带键
     * @since 22
     */
    KEYCODE_TAPE = 2678,
    /**
     * 调谐器键
     * @since 22
     */
    KEYCODE_TUNER = 2679,
    /**
     * 播放器键
     * @since 22
     */
    KEYCODE_PLAYER = 2680,
    /**
     * DVD键
     * @since 22
     */
    KEYCODE_DVD = 2681,
    /**
     * 音频键
     * @since 22
     */
    KEYCODE_AUDIO = 2682,
    /**
     * 视频键
     * @since 22
     */
    KEYCODE_VIDEO = 2683,
    /**
     * 备忘录键
     * @since 22
     */
    KEYCODE_MEMO = 2684,
    /**
     * 日历键
     * @since 22
     */
    KEYCODE_CALENDAR = 2685,
    /**
     * 红色指示器
     * @since 22
     */
    KEYCODE_RED = 2686,
    /**
     * 绿色指示器
     * @since 22
     */
    KEYCODE_GREEN = 2687,
    /**
     * 黄色指示器
     * @since 22
     */
    KEYCODE_YELLOW = 2688,
    /**
     * 蓝色指示器
     * @since 22
     */
    KEYCODE_BLUE = 2689,
    /**
     * 频道向上键
     * @since 22
     */
    KEYCODE_CHANNELUP = 2690,
    /**
     * 频道向下键
     * @since 22
     */
    KEYCODE_CHANNELDOWN = 2691,
    /**
     * 末尾键
     * @since 22
     */
    KEYCODE_LAST = 2692,
    /**
     * 重启键
     * @since 22
     */
    KEYCODE_RESTART = 2693,
    /**
     * 慢速键
     * @since 22
     */
    KEYCODE_SLOW = 2694,
    /**
     * 随机播放键
     * @since 22
     */
    KEYCODE_SHUFFLE = 2695,
    /**
     * 可视电话键
     * @since 22
     */
    KEYCODE_VIDEOPHONE = 2696,
    /**
     * 游戏键
     * @since 22
     */
    KEYCODE_GAMES = 2697,
    /**
     * 放大键
     * @since 22
     */
    KEYCODE_ZOOMIN = 2698,
    /**
     * 缩小键
     * @since 22
     */
    KEYCODE_ZOOMOUT = 2699,
    /**
     * 缩放重置键
     * @since 22
     */
    KEYCODE_ZOOMRESET = 2700,
    /**
     * 文字处理键
     * @since 22
     */
    KEYCODE_WORDPROCESSOR = 2701,
    /**
     * 编辑器键
     * @since 22
     */
    KEYCODE_EDITOR = 2702,
    /**
     * 电子表格键
     * @since 22
     */
    KEYCODE_SPREADSHEET = 2703,
    /**
     * 图形编辑器键
     * @since 22
     */
    KEYCODE_GRAPHICSEDITOR = 2704,
    /**
     * 演示文稿键
     * @since 22
     */
    KEYCODE_PRESENTATION = 2705,
    /**
     * 数据库键
     * @since 22
     */
    KEYCODE_DATABASE = 2706,
    /**
     * 新闻键
     * @since 22
     */
    KEYCODE_NEWS = 2707,
    /**
     * 语音信箱
     * @since 22
     */
    KEYCODE_VOICEMAIL = 2708,
    /**
     * 通讯簿
     * @since 22
     */
    KEYCODE_ADDRESSBOOK = 2709,
    /**
     * 通信键
     * @since 22
     */
    KEYCODE_MESSENGER = 2710,
    /**
     * 亮度切换键
     * @since 22
     */
    KEYCODE_BRIGHTNESS_TOGGLE = 2711,
    /**
     * 拼写检查键
     * @since 22
     */
    KEYCODE_SPELLCHECK = 2712,
    /**
     * 终端锁/屏幕保护程序
     * @since 22
     */
    KEYCODE_COFFEE = 2713,
    /**
     * 媒体循环键
     * @since 22
     */
    KEYCODE_MEDIA_REPEAT = 2714,
    /**
     * 图像键
     * @since 22
     */
    KEYCODE_IMAGES = 2715,
    /**
     * 按键配置键
     * @since 22
     */
    KEYCODE_BUTTONCONFIG = 2716,
    /**
     * 任务管理器
     * @since 22
     */
    KEYCODE_TASKMANAGER = 2717,
    /**
     * 日志按键
     * @since 22
     */
    KEYCODE_JOURNAL = 2718,
    /**
     * 控制面板键
     * @since 22
     */
    KEYCODE_CONTROLPANEL = 2719,
    /**
     * 应用程序选择键
     * @since 22
     */
    KEYCODE_APPSELECT = 2720,
    /**
     * 屏幕保护程序键
     * @since 22
     */
    KEYCODE_SCREENSAVER = 2721,
    /**
     * 智慧键
     * @since 22
     */
    KEYCODE_ASSISTANT = 2722,
    /**
     * 下一个键盘布局键
     * @since 22
     */
    KEYCODE_KBD_LAYOUT_NEXT = 2723,
    /**
     * 最小亮度键
     * @since 22
     */
    KEYCODE_BRIGHTNESS_MIN = 2724,
    /**
     * 最大亮度键
     * @since 22
     */
    KEYCODE_BRIGHTNESS_MAX = 2725,
    /**
     * 键盘输入Assist_Previous，查看输入法输入记录。
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_PREV = 2726,
    /**
     * 键盘输入Assist_Next，查看输入法输入拓展。
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_NEXT = 2727,
    /**
     * 键盘输入Assist_Previous，切换输入组中上一个输入法。
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_PREVGROUP = 2728,
    /**
     * 键盘输入Assist_Next，切换输入组中下一个输入法。
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_NEXTGROUP = 2729,
    /**
     * 键盘输入Assist_Accept
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_ACCEPT = 2730,
    /**
     * 键盘输入Assist_Cancel
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_CANCEL = 2731,
    /**
     * 鼠标AI助手键
     * @since 26.0.0
     */
    KEYCODE_MOUSE_ASSISTANT = 2732,
    /**
     * 鼠标智慧框选键
     * @since 26.0.0
     */
    KEYCODE_MOUSE_INTELLIGENCE_SELECTION = 2733,
    /**
     * 手机触摸屏单击事件，在熄屏显示状态下使用。
     * @since 26.0.0
     */
    KEYCODE_AOD_SINGLE_CLICK = 2740,
    /**
     * 挡风玻璃除雾器开关
     * @since 22
     */
    KEYCODE_FRONT = 2800,
    /**
     * 设置键
     * @since 22
     */
    KEYCODE_SETUP = 2801,
    /**
     * 唤醒键
     * @since 22
     */
    KEYCODE_WAKEUP = 2802,
    /**
     * 发送文件按键
     * @since 22
     */
    KEYCODE_SENDFILE = 2803,
    /**
     * 删除文件按键
     * @since 22
     */
    KEYCODE_DELETEFILE = 2804,
    /**
     * 文件传输（XFER）按键
     * @since 22
     */
    KEYCODE_XFER = 2805,
    /**
     * 程序键1
     * @since 22
     */
    KEYCODE_PROG1 = 2806,
    /**
     * 程序键2
     * @since 22
     */
    KEYCODE_PROG2 = 2807,
    /**
     * DOS面板键
     * @since 22
     */
    KEYCODE_MSDOS = 2808,
    /**
     * 屏幕锁定键
     * @since 22
     */
    KEYCODE_SCREENLOCK = 2809,
    /**
     * 方向旋转显示键
     * @since 22
     */
    KEYCODE_DIRECTION_ROTATE_DISPLAY = 2810,
    /**
     * 窗口切换键
     * @since 22
     */
    KEYCODE_CYCLEWINDOWS = 2811,
    /**
     * 按键
     * @since 22
     */
    KEYCODE_COMPUTER = 2812,
    /**
     * 弹出CD键
     * @since 22
     */
    KEYCODE_EJECTCLOSECD = 2813,
    /**
     * ISO键
     * @since 22
     */
    KEYCODE_ISO = 2814,
    /**
     * 移动键
     * @since 22
     */
    KEYCODE_MOVE = 2815,
    /**
     * 按键'F13'
     * @since 22
     */
    KEYCODE_F13 = 2816,
    /**
     * 按键'F14'
     * @since 22
     */
    KEYCODE_F14 = 2817,
    /**
     * 按键'F15'
     * @since 22
     */
    KEYCODE_F15 = 2818,
    /**
     * 按键'F16'
     * @since 22
     */
    KEYCODE_F16 = 2819,
    /**
     * 按键'F17'
     * @since 22
     */
    KEYCODE_F17 = 2820,
    /**
     * 按键'F18'
     * @since 22
     */
    KEYCODE_F18 = 2821,
    /**
     * 按键'F19'
     * @since 22
     */
    KEYCODE_F19 = 2822,
    /**
     * 按键'F20'
     * @since 22
     */
    KEYCODE_F20 = 2823,
    /**
     * 按键'F21'
     * @since 22
     */
    KEYCODE_F21 = 2824,
    /**
     * 按键'F22'
     * @since 22
     */
    KEYCODE_F22 = 2825,
    /**
     * 按键'F23'
     * @since 22
     */
    KEYCODE_F23 = 2826,
    /**
     * 按键'F24'
     * @since 22
     */
    KEYCODE_F24 = 2827,
    /**
     * 程序键3
     * @since 22
     */
    KEYCODE_PROG3 = 2828,
    /**
     * 程序键4
     * @since 22
     */
    KEYCODE_PROG4 = 2829,
    /**
     * 仪表板
     * @since 22
     */
    KEYCODE_DASHBOARD = 2830,
    /**
     * 挂起键
     * @since 22
     */
    KEYCODE_SUSPEND = 2831,
    /**
     * 高阶路径键
     * @since 22
     */
    KEYCODE_HP = 2832,
    /**
     * 音量键
     * @since 22
     */
    KEYCODE_SOUND = 2833,
    /**
     * 疑问按键
     * @since 22
     */
    KEYCODE_QUESTION = 2834,
    /**
     * 连接键
     * @since 22
     */
    KEYCODE_CONNECT = 2836,
    /**
     * 运动按键
     * @since 22
     */
    KEYCODE_SPORT = 2837,
    /**
     * 商城键
     * @since 22
     */
    KEYCODE_SHOP = 2838,
    /**
     * 交替键
     * @since 22
     */
    KEYCODE_ALTERASE = 2839,
    /**
     * 在可用视频之间循环输出（监视器/LCD/TV输出/等）。
     * @since 22
     */
    KEYCODE_SWITCHVIDEOMODE = 2841,
    /**
     * 电池按键
     * @since 22
     */
    KEYCODE_BATTERY = 2842,
    /**
     * 蓝牙按键
     * @since 22
     */
    KEYCODE_BLUETOOTH = 2843,
    /**
     * 无线局域网
     * @since 22
     */
    KEYCODE_WLAN = 2844,
    /**
     * 超宽带控制键
     * @since 22
     */
    KEYCODE_UWB = 2845,
    /**
     * 移动网络控制键
     * @since 22
     */
    KEYCODE_WWAN_WIMAX = 2846,
    /**
     * 控制所有收音机的键
     * @since 22
     */
    KEYCODE_RFKILL = 2847,
    /**
     * 向上频道键
     * @since 22
     */
    KEYCODE_CHANNEL = 3001,
    /**
     *按键0
     * @since 22
     */
    KEYCODE_BTN_0 = 3100,
    /**
     * 按键1
     * @since 22
     */
    KEYCODE_BTN_1 = 3101,
    /**
     * 按键2
     * @since 22
     */
    KEYCODE_BTN_2 = 3102,
    /**
     * 按键3
     * @since 22
     */
    KEYCODE_BTN_3 = 3103,
    /**
     * 按键4
     * @since 22
     */
    KEYCODE_BTN_4 = 3104,
    /**
     * 按键5
     * @since 22
     */
    KEYCODE_BTN_5 = 3105,
    /**
     * 按键6
     * @since 22
     */
    KEYCODE_BTN_6 = 3106,
    /**
     * 按键7
     * @since 22
     */
    KEYCODE_BTN_7 = 3107,
    /**
     * 按键8
     * @since 22
     */
    KEYCODE_BTN_8 = 3108,
    /**
     * 按键9
     * @since 22
     */
    KEYCODE_BTN_9 = 3109,
    /**
     * 智能手表智感窗按键单击
     * @since 22
     */
    KEYCODE_DAGGER_CLICK = 3211,
    /**
     * 智能手表智感窗按键双击
     * @since 22
     */
    KEYCODE_DAGGER_DOUBLE_CLICK = 3212,
    /**
     * 智能手表智感窗按键长按
     * @since 22
     */
    KEYCODE_DAGGER_LONG_PRESS = 3213,
    /**
     * 智能手表左按键
     * @since 22
     */
    KEYCODE_DIV = 3220,
    /**
     * 自定义快捷键
     * @since 26.0.0
     */
    KEYCODE_XKEY = 3232,
    /**
     * 智控键上滑
     * @since 26.0.0
     */
    KEYCODE_FINGERPRINT_SLIDE_UP = 3233,
    /**
     * 智控键下滑
     * @since 26.0.0
     */
    KEYCODE_FINGERPRINT_SLIDE_DOWN = 3234
} Input_KeyCode;

#ifdef __cplusplus
}
#endif

#endif /* OH_KEY_CODE_H */

/** @} */