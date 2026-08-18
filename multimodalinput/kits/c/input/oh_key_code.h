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
 * @brief Provides C APIs of the multimodal input module, supporting event processing for various input devices such as
 *  touch, key, and mouse. It enables unified access to multiple devices, improving development efficiency and
 *  application interaction experience.
 *
 * @since 12
 */

/**
 * @brief Defines key codes of the key device.
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
 * @brief Enumerates the key codes.
 *
 * @since 12
 */
typedef enum {
    /**
     * @brief Unknown key
     */
    KEYCODE_UNKNOWN = -1,

    /**
     * @brief Function (Fn) key
     */
    KEYCODE_FN = 0,
    /**
     * @brief Function (Home) key
     * @since 22
     */
    KEYCODE_HOME = 1,
    /**
     * @brief Back button
     * @since 22
     */
    KEYCODE_BACK = 2,

    /**
     * @brief Search key
     * @since 22
     */
    KEYCODE_SEARCH = 9,
    /**
     * @brief Media: Play/Pause key<br>Difference between this key and **KEYCODE_PLAYPAUSE**:<br> **KEYCODE_PLAYPAUSE**
     * is an
     * earlier definition, while **KEYCODE_MEDIA_PLAY_PAUSE** is designed for modern media key devices.
     * @since 22
     */
    KEYCODE_MEDIA_PLAY_PAUSE = 10,
    /**
     * @brief Media: Stop Key
     * @since 22
     */
    KEYCODE_MEDIA_STOP = 11,
    /**
     * @brief Media: Next key
     * @since 22
     */
    KEYCODE_MEDIA_NEXT = 12,
    /**
     * @brief Media: Previous key
     * @since 22
     */
    KEYCODE_MEDIA_PREVIOUS = 13,
    /**
     * @brief Media: Rewind key
     * @since 22
     */
    KEYCODE_MEDIA_REWIND = 14,
    /**
     * @brief Media: Fast Forward key
     * @since 22
     */
    KEYCODE_MEDIA_FAST_FORWARD = 15,

    /**
     * @brief Volume Up key
     */
    KEYCODE_VOLUME_UP = 16,

    /**
     * @brief Volume Down key
     */
    KEYCODE_VOLUME_DOWN = 17,

    /**
     * @brief Power key
     */
    KEYCODE_POWER = 18,

    /**
     * @brief Camera key
     */
    KEYCODE_CAMERA = 19,

    /**
     * @brief Speaker Mute key
     */
    KEYCODE_VOLUME_MUTE = 22,

    /**
     * @brief Mute key
     */
    KEYCODE_MUTE = 23,

    /**
     * @brief Brightness Up key
     */
    KEYCODE_BRIGHTNESS_UP = 40,

    /**
     * @brief Brightness Down key
     */
    KEYCODE_BRIGHTNESS_DOWN = 41,

    /**
     * @brief Key 0
     */
    KEYCODE_0 = 2000,

    /**
     * @brief Key 1
     */
    KEYCODE_1 = 2001,

    /**
     * @brief Key 2
     */
    KEYCODE_2 = 2002,

    /**
     * @brief Key 3
     */
    KEYCODE_3 = 2003,

    /**
     * @brief Key 4
     */
    KEYCODE_4 = 2004,

    /**
     * @brief Key 5
     */
    KEYCODE_5 = 2005,

    /**
     * @brief Key 6
     */
    KEYCODE_6 = 2006,

    /**
     * @brief Key 7
     */
    KEYCODE_7 = 2007,

    /**
     * @brief Key 8
     */
    KEYCODE_8 = 2008,

    /**
     * @brief Key 9
     */
    KEYCODE_9 = 2009,

    /**
     * @brief Key '*'
     */
    KEYCODE_STAR = 2010,

    /**
     * @brief Key #
     */
    KEYCODE_POUND = 2011,

    /**
     * @brief Up key on D-pad
     */
    KEYCODE_DPAD_UP = 2012,

    /**
     * @brief Down key on D-pad
     */
    KEYCODE_DPAD_DOWN = 2013,

    /**
     * @brief Left key on D-pad
     */
    KEYCODE_DPAD_LEFT = 2014,

    /**
     * @brief Right key on D-pad
     */
    KEYCODE_DPAD_RIGHT = 2015,

    /**
     * @brief Center key on D-pad
     */
    KEYCODE_DPAD_CENTER = 2016,

    /**
     * @brief Key A
     */
    KEYCODE_A = 2017,

    /**
     * @brief Key B
     */
    KEYCODE_B = 2018,

    /**
     * @brief Key C
     */
    KEYCODE_C = 2019,

    /**
     * @brief Key D
     */
    KEYCODE_D = 2020,

    /**
     * @brief Key E
     */
    KEYCODE_E = 2021,

    /**
     * @brief Key F
     */
    KEYCODE_F = 2022,

    /**
     * @brief Key G
     */
    KEYCODE_G = 2023,

    /**
     * @brief Key H
     */
    KEYCODE_H = 2024,

    /**
     * @brief Key I
     */
    KEYCODE_I = 2025,

    /**
     * @brief Key J
     */
    KEYCODE_J = 2026,

    /**
     * @brief Key K
     */
    KEYCODE_K = 2027,

    /**
     * @brief Key L
     */
    KEYCODE_L = 2028,

    /**
     * @brief Key M
     */
    KEYCODE_M = 2029,

    /**
     * @brief Key N
     */
    KEYCODE_N = 2030,

    /**
     * @brief Key O
     */
    KEYCODE_O = 2031,

    /**
     * @brief Key P
     */
    KEYCODE_P = 2032,

    /**
     * @brief Key Q
     */
    KEYCODE_Q = 2033,

    /**
     * @brief Key R
     */
    KEYCODE_R = 2034,

    /**
     * @brief Key S
     */
    KEYCODE_S = 2035,

    /**
     * @brief Key T
     */
    KEYCODE_T = 2036,

    /**
     * @brief Key U
     */
    KEYCODE_U = 2037,

    /**
     * @brief Key V
     */
    KEYCODE_V = 2038,

    /**
     * @brief Key W
     */
    KEYCODE_W = 2039,

    /**
     * @brief Key X
     */
    KEYCODE_X = 2040,

    /**
     * @brief Key Y
     */
    KEYCODE_Y = 2041,

    /**
     * @brief Key Z
     */
    KEYCODE_Z = 2042,

    /**
     * @brief Key ,
     */
    KEYCODE_COMMA = 2043,

    /**
     * @brief Key .
     */
    KEYCODE_PERIOD = 2044,

    /**
     * @brief Left Alt key
     */
    KEYCODE_ALT_LEFT = 2045,

    /**
     * @brief Right Alt key
     */
    KEYCODE_ALT_RIGHT = 2046,

    /**
     * @brief Left Shift key
     */
    KEYCODE_SHIFT_LEFT = 2047,

    /**
     * @brief Right Shift key
     */
    KEYCODE_SHIFT_RIGHT = 2048,

    /**
     * @brief Tab key
     */
    KEYCODE_TAB = 2049,

    /**
     * @brief Space key
     */
    KEYCODE_SPACE = 2050,

    /**
     * @brief Symbol key
     */
    KEYCODE_SYM = 2051,

    /**
     * @brief Browser function key, used to launch the browser application.
     */
    KEYCODE_EXPLORER = 2052,

    /**
     * @brief Email function key, used to launch the email application.
     */
    KEYCODE_ENVELOPE = 2053,

    /**
     * @brief Enter key
     */
    KEYCODE_ENTER = 2054,

    /**
     * @brief Delete key
     */
    KEYCODE_DEL = 2055,

    /**
     * @brief Key `
     */
    KEYCODE_GRAVE = 2056,

    /**
     * @brief Key -
     */
    KEYCODE_MINUS = 2057,

    /**
     * @brief Key =
     */
    KEYCODE_EQUALS = 2058,

    /**
     * @brief Key [
     */
    KEYCODE_LEFT_BRACKET = 2059,

    /**
     * @brief Key ]
     */
    KEYCODE_RIGHT_BRACKET = 2060,

    /**
     * @brief Key |
     */
    KEYCODE_BACKSLASH = 2061,

    /**
     * @brief Key ;
     */
    KEYCODE_SEMICOLON = 2062,

    /**
     * @brief Key '
     */
    KEYCODE_APOSTROPHE = 2063,

    /**
     * @brief Key '/'
     */
    KEYCODE_SLASH = 2064,

    /**
     * @brief Key @
     */
    KEYCODE_AT = 2065,

    /**
     * @brief Key +
     */
    KEYCODE_PLUS = 2066,

    /**
     * @brief Menu key
     */
    KEYCODE_MENU = 2067,

    /**
     * @brief Page Up key
     */
    KEYCODE_PAGE_UP = 2068,

    /**
     * @brief Page Down key
     */
    KEYCODE_PAGE_DOWN = 2069,

    /**
     * @brief Esc key
     */
    KEYCODE_ESCAPE = 2070,

    /**
     * @brief Forward Delete key
     */
    KEYCODE_FORWARD_DEL = 2071,

    /**
     * @brief Left Ctrl key
     */
    KEYCODE_CTRL_LEFT = 2072,

    /**
     * @brief Right Ctrl key
     */
    KEYCODE_CTRL_RIGHT = 2073,

    /**
     * @brief Caps Lock key
     */
    KEYCODE_CAPS_LOCK = 2074,

    /**
     * @brief Scroll Lock key
     */
    KEYCODE_SCROLL_LOCK = 2075,

    /**
     * @brief Left Meta key
     */
    KEYCODE_META_LEFT = 2076,

    /**
     * @brief Right Meta key
     */
    KEYCODE_META_RIGHT = 2077,

    /**
     * @brief Function key
     */
    KEYCODE_FUNCTION = 2078,

    /**
     * @brief System Request/Print Screen key
     */
    KEYCODE_SYSRQ = 2079,

    /**
     * @brief Break/Pause key
     */
    KEYCODE_BREAK = 2080,

    /**
     * @brief Move to Home key
     */
    KEYCODE_MOVE_HOME = 2081,

    /**
     * @brief Move to End key
     */
    KEYCODE_MOVE_END = 2082,

    /**
     * @brief Insert key
     */
    KEYCODE_INSERT = 2083,

    /**
     * @brief Forward key
     */
    KEYCODE_FORWARD = 2084,

    /**
     * @brief Media: Play key
     */
    KEYCODE_MEDIA_PLAY = 2085,

    /**
     * @brief Media: Pause key
     */
    KEYCODE_MEDIA_PAUSE = 2086,

    /**
     * @brief Media: Close key
     */
    KEYCODE_MEDIA_CLOSE = 2087,

    /**
     * @brief Media: Reject key
     */
    KEYCODE_MEDIA_EJECT = 2088,

    /**
     * @brief Media: Record key
     */
    KEYCODE_MEDIA_RECORD = 2089,

    /**
     * @brief F1 key
     */
    KEYCODE_F1 = 2090,

    /**
     * @brief F2 key
     */
    KEYCODE_F2 = 2091,

    /**
     * @brief F3 key
     */
    KEYCODE_F3 = 2092,

    /**
     * @brief F4 key
     */
    KEYCODE_F4 = 2093,

    /**
     * @brief F5 key
     */
    KEYCODE_F5 = 2094,

    /**
     * @brief F6 key
     */
    KEYCODE_F6 = 2095,

    /**
     * @brief F7 key
     */
    KEYCODE_F7 = 2096,

    /**
     * @brief F8 key
     */
    KEYCODE_F8 = 2097,

    /**
     * @brief F9 key
     */
    KEYCODE_F9 = 2098,

    /**
     * @brief F10 key
     */
    KEYCODE_F10 = 2099,

    /**
     * @brief F11 key
     */
    KEYCODE_F11 = 2100,

    /**
     * @brief F12 key
     */
    KEYCODE_F12 = 2101,

    /**
     * @brief Number Lock key
     */
    KEYCODE_NUM_LOCK = 2102,

    /**
     * @brief Key 0 on numeric keypad
     */
    KEYCODE_NUMPAD_0 = 2103,

    /**
     * @brief Key 1 on numeric keypad
     */
    KEYCODE_NUMPAD_1 = 2104,

    /**
     * @brief Key 2 on numeric keypad
     */
    KEYCODE_NUMPAD_2 = 2105,

    /**
     * @brief Key 3 on numeric keypad
     */
    KEYCODE_NUMPAD_3 = 2106,

    /**
     * @brief Key 4 on numeric keypad
     */
    KEYCODE_NUMPAD_4 = 2107,

    /**
     * @brief Key 5 on numeric keypad
     */
    KEYCODE_NUMPAD_5 = 2108,

    /**
     * @brief Key 6 on numeric keypad
     */
    KEYCODE_NUMPAD_6 = 2109,

    /**
     * @brief Key 7 on numeric keypad
     */
    KEYCODE_NUMPAD_7 = 2110,

    /**
     * @brief Key 8 on numeric keypad
     */
    KEYCODE_NUMPAD_8 = 2111,

    /**
     * @brief Key 9 on numeric keypad
     */
    KEYCODE_NUMPAD_9 = 2112,

    /**
     * @brief Key / on numeric keypad
     */
    KEYCODE_NUMPAD_DIVIDE = 2113,

    /**
     * @brief Key * on numeric keypad
     */
    KEYCODE_NUMPAD_MULTIPLY = 2114,

    /**
     * @brief Key - on numeric keypad
     */
    KEYCODE_NUMPAD_SUBTRACT = 2115,

    /**
     * @brief Key + on numeric keypad
     */
    KEYCODE_NUMPAD_ADD = 2116,

    /**
     * @brief Key . on numeric keypad
     */
    KEYCODE_NUMPAD_DOT = 2117,

    /**
     * @brief Key , on numeric keypad
     */
    KEYCODE_NUMPAD_COMMA = 2118,

    /**
     * @brief Enter key on numeric keypad
     */
    KEYCODE_NUMPAD_ENTER = 2119,

    /**
     * @brief Key = on numeric keypad
     */
    KEYCODE_NUMPAD_EQUALS = 2120,

    /**
     * @brief Key ( on numeric keypad
     */
    KEYCODE_NUMPAD_LEFT_PAREN = 2121,

    /**
     * @brief Key ) on numeric keypad
     */
    KEYCODE_NUMPAD_RIGHT_PAREN = 2122,
    /**
     * @brief Multi-task key
     * @since 22
     */
    KEYCODE_VIRTUAL_MULTITASK = 2210,
    /**
     * @brief Joystick key A
     * @since 22
     */
    KEYCODE_BUTTON_A = 2301,
    /**
     * @brief Joystick key B
     * @since 22
     */
    KEYCODE_BUTTON_B = 2302,
    /**
     * @brief Joystick key X
     * @since 22
     */
    KEYCODE_BUTTON_X = 2304,
    /**
     * @brief Joystick key Y
     * @since 22
     */
    KEYCODE_BUTTON_Y = 2305,
    /**
     * @brief Joystick key L1
     * @since 22
     */
    KEYCODE_BUTTON_L1 = 2307,
    /**
     * @brief Joystick key R1
     * @since 22
     */
    KEYCODE_BUTTON_R1 = 2308,
    /**
     * @brief Joystick key L2
     * @since 22
     */
    KEYCODE_BUTTON_L2 = 2309,
    /**
     * @brief Joystick key R2
     * @since 22
     */
    KEYCODE_BUTTON_R2 = 2310,
    /**
     * @brief Joystick key Select
     * @since 22
     */
    KEYCODE_BUTTON_SELECT = 2311,
    /**
     * @brief Joystick key Start
     * @since 22
     */
    KEYCODE_BUTTON_START = 2312,
    /**
     * @brief Joystick key Mode
     * @since 22
     */
    KEYCODE_BUTTON_MODE = 2313,
    /**
     * @brief Joystick key THUMBL
     * @since 22
     */
    KEYCODE_BUTTON_THUMBL = 2314,
    /**
     * @brief Joystick key THUMBR
     * @since 22
     */
    KEYCODE_BUTTON_THUMBR = 2315,
    /**
     * @brief Sleep key
     * @since 22
     */
    KEYCODE_SLEEP = 2600,
    /**
     * @brief Zenkaku/Hankaku key
     * @since 22
     */
    KEYCODE_ZENKAKU_HANKAKU = 2601,
    /**
     * @brief International Keyboard Extension key
     * @since 22
     */
    KEYCODE_102ND = 2602,
    /**
     * @brief Ro key
     * @since 22
     */
    KEYCODE_RO = 2603,
    /**
     * @brief Katakana key
     * @since 22
     */
    KEYCODE_KATAKANA = 2604,
    /**
     * @brief Hiragana key
     * @since 22
     */
    KEYCODE_HIRAGANA = 2605,
    /**
     * @brief Henkan key
     * @since 22
     */
    KEYCODE_HENKAN = 2606,
    /**
     * @brief Katakana/Hiragana key
     * @since 22
     */
    KEYCODE_KATAKANA_HIRAGANA = 2607,
    /**
     * @brief Muhenkan key
     * @since 22
     */
    KEYCODE_MUHENKAN = 2608,
    /**
     * @brief Linefeed key
     * @since 22
     */
    KEYCODE_LINEFEED = 2609,
    /**
     * @brief Macro key
     * @since 22
     */
    KEYCODE_MACRO = 2610,
    /**
     * @brief Plus/Minus key on the numeric keypad
     * @since 22
     */
    KEYCODE_NUMPAD_PLUSMINUS = 2611,
    /**
     * @brief Scale key
     * @since 22
     */
    KEYCODE_SCALE = 2612,
    /**
     * @brief Hanguel key
     * @since 22
     */
    KEYCODE_HANGUEL = 2613,
    /**
     * @brief Hanja key
     * @since 22
     */
    KEYCODE_HANJA = 2614,
    /**
     * @brief Yen key
     * @since 22
     */
    KEYCODE_YEN = 2615,
    /**
     * @brief Stop key
     * @since 22
     */
    KEYCODE_STOP = 2616,
    /**
     * @brief Again key
     * @since 22
     */
    KEYCODE_AGAIN = 2617,
    /**
     * @brief Props key
     * @since 22
     */
    KEYCODE_PROPS = 2618,
    /**
     * @brief Undo key
     * @since 22
     */
    KEYCODE_UNDO = 2619,
    /**
     * @brief Copy key
     * @since 22
     */
    KEYCODE_COPY = 2620,
    /**
     * @brief Open key
     * @since 22
     */
    KEYCODE_OPEN = 2621,
    /**
     * @brief Paste key
     * @since 22
     */
    KEYCODE_PASTE = 2622,
    /**
     * @brief Find key
     * @since 22
     */
    KEYCODE_FIND = 2623,
    /**
     * @brief Cut key
     * @since 22
     */
    KEYCODE_CUT = 2624,
    /**
     * @brief Help key
     * @since 22
     */
    KEYCODE_HELP = 2625,
    /**
     * @brief Calculator special function key, used to launch the calculator application.
     * @since 22
     */
    KEYCODE_CALC = 2626,
    /**
     * @brief File key
     * @since 22
     */
    KEYCODE_FILE = 2627,
    /**
     * @brief Bookmarks key
     * @since 22
     */
    KEYCODE_BOOKMARKS = 2628,
    /**
     * @brief Page Down key
     * @since 22
     */
    KEYCODE_NEXT = 2629,
    /**
     * @brief Media: Play/Pause key<br>Difference between this key and **KEYCODE_MEDIA_PLAY_PAUSE**:<br>
     * **KEYCODE_PLAYPAUSE** is an earlier definition, while **KEYCODE_MEDIA_PLAY_PAUSE** is designed for
     * modern media key devices.
     * @since 22
     */
    KEYCODE_PLAYPAUSE = 2630,
    /**
     * @brief Page Up key
     * @since 22
     */
    KEYCODE_PREVIOUS = 2631,
    /**
     * @brief Stop CD key
     * @since 22
     */
    KEYCODE_STOPCD = 2632,
    /**
     * @brief Configuration key
     * @since 22
     */
    KEYCODE_CONFIG = 2634,
    /**
     * @brief Refresh key
     * @since 22
     */
    KEYCODE_REFRESH = 2635,
    /**
     * @brief Exit key
     * @since 22
     */
    KEYCODE_EXIT = 2636,
    /**
     * @brief Edit key
     * @since 22
     */
    KEYCODE_EDIT = 2637,
    /**
     * @brief Scroll Up key
     * @since 22
     */
    KEYCODE_SCROLLUP = 2638,
    /**
     * @brief Scroll Down key
     * @since 22
     */
    KEYCODE_SCROLLDOWN = 2639,
    /**
     * @brief New key
     * @since 22
     */
    KEYCODE_NEW = 2640,
    /**
     * @brief Redo key
     * @since 22
     */
    KEYCODE_REDO = 2641,
    /**
     * @brief Close key
     * @since 22
     */
    KEYCODE_CLOSE = 2642,
    /**
     * @brief Play key
     * @since 22
     */
    KEYCODE_PLAY = 2643,
    /**
     * @brief Bass Boost key
     * @since 22
     */
    KEYCODE_BASSBOOST = 2644,
    /**
     * @brief Print key
     * @since 22
     */
    KEYCODE_PRINT = 2645,
    /**
     * @brief Chat key
     * @since 22
     */
    KEYCODE_CHAT = 2646,
    /**
     * @brief Finance key
     * @since 22
     */
    KEYCODE_FINANCE = 2647,
    /**
     * @brief Cancel key
     * @since 22
     */
    KEYCODE_CANCEL = 2648,
    /**
     * @brief Keyboard Illumination Toggle key
     * @since 22
     */
    KEYCODE_KBDILLUM_TOGGLE = 2649,
    /**
     * @brief Keyboard Illumination Down key
     * @since 22
     */
    KEYCODE_KBDILLUM_DOWN = 2650,
    /**
     * @brief Keyboard Illumination Up key
     * @since 22
     */
    KEYCODE_KBDILLUM_UP = 2651,
    /**
     * @brief Send key
     * @since 22
     */
    KEYCODE_SEND = 2652,
    /**
     * @brief Reply key
     * @since 22
     */
    KEYCODE_REPLY = 2653,
    /**
     * @brief Forward Mail key
     * @since 22
     */
    KEYCODE_FORWARDMAIL = 2654,
    /**
     * @brief Save key
     * @since 22
     */
    KEYCODE_SAVE = 2655,
    /**
     * @brief Documents key
     * @since 22
     */
    KEYCODE_DOCUMENTS = 2656,
    /**
     * @brief Next Video key
     * @since 22
     */
    KEYCODE_VIDEO_NEXT = 2657,
    /**
     * @brief Previous Video key
     * @since 22
     */
    KEYCODE_VIDEO_PREV = 2658,
    /**
     * @brief Brightness Cycle key
     * @since 22
     */
    KEYCODE_BRIGHTNESS_CYCLE = 2659,
    /**
     * @brief Brightness Zero key
     * @since 22
     */
    KEYCODE_BRIGHTNESS_ZERO = 2660,
    /**
     * @brief Display Off Key
     * @since 22
     */
    KEYCODE_DISPLAY_OFF = 2661,
    /**
     * @brief Misc Button key
     * @since 22
     */
    KEYCODE_BTN_MISC = 2662,
    /**
     * @brief Goto key
     * @since 22
     */
    KEYCODE_GOTO = 2663,
    /**
     * @brief Info key
     * @since 22
     */
    KEYCODE_INFO = 2664,
    /**
     * @brief Program key
     * @since 22
     */
    KEYCODE_PROGRAM = 2665,
    /**
     * @brief PVR key
     * @since 22
     */
    KEYCODE_PVR = 2666,
    /**
     * @brief Subtitle key
     * @since 22
     */
    KEYCODE_SUBTITLE = 2667,
    /**
     * @brief Full Screen key
     * @since 22
     */
    KEYCODE_FULL_SCREEN = 2668,
    /**
     * @brief Keyboard
     * @since 22
     */
    KEYCODE_KEYBOARD = 2669,
    /**
     * @brief Aspect Ratio key
     * @since 22
     */
    KEYCODE_ASPECT_RATIO = 2670,
    /**
     * @brief Port Control key
     * @since 22
     */
    KEYCODE_PC = 2671,
    /**
     * @brief TV key
     * @since 22
     */
    KEYCODE_TV = 2672,
    /**
     * @brief TV key 2
     * @since 22
     */
    KEYCODE_TV2 = 2673,
    /**
     * @brief VCR key
     * @since 22
     */
    KEYCODE_VCR = 2674,
    /**
     * @brief VCR key 2
     * @since 22
     */
    KEYCODE_VCR2 = 2675,
    /**
     * @brief SAT key
     * @since 22
     */
    KEYCODE_SAT = 2676,
    /**
     * @brief CD key
     * @since 22
     */
    KEYCODE_CD = 2677,
    /**
     * @brief Tape key
     * @since 22
     */
    KEYCODE_TAPE = 2678,
    /**
     * @brief Tuner key
     * @since 22
     */
    KEYCODE_TUNER = 2679,
    /**
     * @brief Player key
     * @since 22
     */
    KEYCODE_PLAYER = 2680,
    /**
     * @brief DVD key
     * @since 22
     */
    KEYCODE_DVD = 2681,
    /**
     * @brief Audio key
     * @since 22
     */
    KEYCODE_AUDIO = 2682,
    /**
     * @brief Video key
     * @since 22
     */
    KEYCODE_VIDEO = 2683,
    /**
     * @brief Memo key
     * @since 22
     */
    KEYCODE_MEMO = 2684,
    /**
     * @brief Calendar key
     * @since 22
     */
    KEYCODE_CALENDAR = 2685,
    /**
     * @brief Red indicator
     * @since 22
     */
    KEYCODE_RED = 2686,
    /**
     * @brief Green indicator
     * @since 22
     */
    KEYCODE_GREEN = 2687,
    /**
     * @brief Yellow indicator
     * @since 22
     */
    KEYCODE_YELLOW = 2688,
    /**
     * @brief Blue indicator
     * @since 22
     */
    KEYCODE_BLUE = 2689,
    /**
     * @brief Channel Up key
     * @since 22
     */
    KEYCODE_CHANNELUP = 2690,
    /**
     * @brief Channel Down key
     * @since 22
     */
    KEYCODE_CHANNELDOWN = 2691,
    /**
     * @brief Last key
     * @since 22
     */
    KEYCODE_LAST = 2692,
    /**
     * @brief Restart key
     * @since 22
     */
    KEYCODE_RESTART = 2693,
    /**
     * @brief Slow key
     * @since 22
     */
    KEYCODE_SLOW = 2694,
    /**
     * @brief Shuffle key
     * @since 22
     */
    KEYCODE_SHUFFLE = 2695,
    /**
     * @brief Videophone key
     * @since 22
     */
    KEYCODE_VIDEOPHONE = 2696,
    /**
     * @brief Games key
     * @since 22
     */
    KEYCODE_GAMES = 2697,
    /**
     * @brief Zoom In key
     * @since 22
     */
    KEYCODE_ZOOMIN = 2698,
    /**
     * @brief Zoom Out key
     * @since 22
     */
    KEYCODE_ZOOMOUT = 2699,
    /**
     * @brief Zoom Reset key
     * @since 22
     */
    KEYCODE_ZOOMRESET = 2700,
    /**
     * @brief Word Processor key
     * @since 22
     */
    KEYCODE_WORDPROCESSOR = 2701,
    /**
     * @brief Editor key
     * @since 22
     */
    KEYCODE_EDITOR = 2702,
    /**
     * @brief Spreadsheet key
     * @since 22
     */
    KEYCODE_SPREADSHEET = 2703,
    /**
     * @brief Graphics Editor key
     * @since 22
     */
    KEYCODE_GRAPHICSEDITOR = 2704,
    /**
     * @brief Presentation key
     * @since 22
     */
    KEYCODE_PRESENTATION = 2705,
    /**
     * @brief Database key
     * @since 22
     */
    KEYCODE_DATABASE = 2706,
    /**
     * @brief News key
     * @since 22
     */
    KEYCODE_NEWS = 2707,
    /**
     * @brief Voice mailbox
     * @since 22
     */
    KEYCODE_VOICEMAIL = 2708,
    /**
     * @brief Address book key
     * @since 22
     */
    KEYCODE_ADDRESSBOOK = 2709,
    /**
     * @brief Messenger key
     * @since 22
     */
    KEYCODE_MESSENGER = 2710,
    /**
     * @brief Brightness Toggle key
     * @since 22
     */
    KEYCODE_BRIGHTNESS_TOGGLE = 2711,
    /**
     * @brief Spell Check key
     * @since 22
     */
    KEYCODE_SPELLCHECK = 2712,
    /**
     * @brief Coffee key, which is used to launch screen lock or screen saver
     * @since 22
     */
    KEYCODE_COFFEE = 2713,
    /**
     * @brief Media Repeat key
     * @since 22
     */
    KEYCODE_MEDIA_REPEAT = 2714,
    /**
     * @brief Images key
     * @since 22
     */
    KEYCODE_IMAGES = 2715,
    /**
     * @brief Button Configuration key
     * @since 22
     */
    KEYCODE_BUTTONCONFIG = 2716,
    /**
     * @brief Task Manager
     * @since 22
     */
    KEYCODE_TASKMANAGER = 2717,
    /**
     * @brief Log key
     * @since 22
     */
    KEYCODE_JOURNAL = 2718,
    /**
     * @brief Control Panel key
     * @since 22
     */
    KEYCODE_CONTROLPANEL = 2719,
    /**
     * @brief App Select key
     * @since 22
     */
    KEYCODE_APPSELECT = 2720,
    /**
     * @brief Screen Saver key
     * @since 22
     */
    KEYCODE_SCREENSAVER = 2721,
    /**
     * @brief Assistant key
     * @since 22
     */
    KEYCODE_ASSISTANT = 2722,
    /**
     * @brief Next Keyboard Layout key
     * @since 22
     */
    KEYCODE_KBD_LAYOUT_NEXT = 2723,
    /**
     * @brief Min Brightness key
     * @since 22
     */
    KEYCODE_BRIGHTNESS_MIN = 2724,
    /**
     * @brief Max Brightness key
     * @since 22
     */
    KEYCODE_BRIGHTNESS_MAX = 2725,
    /**
     * @brief Keyboard Input Assist_Previous, used to view input method input history.
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_PREV = 2726,
    /**
     * @brief Keyboard Input Assist_Next, used to view input method input extensions.
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_NEXT = 2727,
    /**
     * @brief Keyboard Input Assist_Previous, used to switch to the previous input method in the input group.
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_PREVGROUP = 2728,
    /**
     * @brief Keyboard Input Assist_Next, used to switch to the next input method in the input group.
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_NEXTGROUP = 2729,
    /**
     * @brief Keyboard Input-assisted Accept key
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_ACCEPT = 2730,
    /**
     * @brief Keyboard Input-assisted Cancel key
     * @since 22
     */
    KEYCODE_KBDINPUTASSIST_CANCEL = 2731,
    /**
     * @brief Mouse AI Assistant key
     * @since 26.0.0
     */
    KEYCODE_MOUSE_ASSISTANT = 2732,
    /**
     * @brief Mouse Smart Selection key
     * @since 26.0.0
     */
    KEYCODE_MOUSE_INTELLIGENCE_SELECTION = 2733,
    /**
     * @brief Phone touchscreen single-click event, used in Always-On Display state.
     * @since 26.0.0
     */
    KEYCODE_AOD_SINGLE_CLICK = 2740,
    /**
     * @brief Front key, which is used to launch the windshield defogger
     * @since 22
     */
    KEYCODE_FRONT = 2800,
    /**
     * @brief Setup key
     * @since 22
     */
    KEYCODE_SETUP = 2801,
    /**
     * @brief Wakeup key
     * @since 22
     */
    KEYCODE_WAKEUP = 2802,
    /**
     * @brief Send File key
     * @since 22
     */
    KEYCODE_SENDFILE = 2803,
    /**
     * @brief Delete File key
     * @since 22
     */
    KEYCODE_DELETEFILE = 2804,
    /**
     * @brief XFER key, which is used to start file transfer
     * @since 22
     */
    KEYCODE_XFER = 2805,
    /**
     * @brief Program key 1
     * @since 22
     */
    KEYCODE_PROG1 = 2806,
    /**
     * @brief Program key 2
     * @since 22
     */
    KEYCODE_PROG2 = 2807,
    /**
     * @brief DOS key
     * @since 22
     */
    KEYCODE_MSDOS = 2808,
    /**
     * @brief Screen Lock key
     * @since 22
     */
    KEYCODE_SCREENLOCK = 2809,
    /**
     * @brief Directional Rotation Display key
     * @since 22
     */
    KEYCODE_DIRECTION_ROTATE_DISPLAY = 2810,
    /**
     * @brief Window Cycle key
     * @since 22
     */
    KEYCODE_CYCLEWINDOWS = 2811,
    /**
     * @brief Computer key
     * @since 22
     */
    KEYCODE_COMPUTER = 2812,
    /**
     * @brief Eject CD key
     * @since 22
     */
    KEYCODE_EJECTCLOSECD = 2813,
    /**
     * @brief ISO key
     * @since 22
     */
    KEYCODE_ISO = 2814,
    /**
     * @brief Move key
     * @since 22
     */
    KEYCODE_MOVE = 2815,
    /**
     * @brief F13 key
     * @since 22
     */
    KEYCODE_F13 = 2816,
    /**
     * @brief F14 key
     * @since 22
     */
    KEYCODE_F14 = 2817,
    /**
     * @brief F15 key
     * @since 22
     */
    KEYCODE_F15 = 2818,
    /**
     * @brief F16 key
     * @since 22
     */
    KEYCODE_F16 = 2819,
    /**
     * @brief F17 key
     * @since 22
     */
    KEYCODE_F17 = 2820,
    /**
     * @brief F18 key
     * @since 22
     */
    KEYCODE_F18 = 2821,
    /**
     * @brief F19 key
     * @since 22
     */
    KEYCODE_F19 = 2822,
    /**
     * @brief F20 key
     * @since 22
     */
    KEYCODE_F20 = 2823,
    /**
     * @brief F21 key
     * @since 22
     */
    KEYCODE_F21 = 2824,
    /**
     * @brief F22 key
     * @since 22
     */
    KEYCODE_F22 = 2825,
    /**
     * @brief F23 key
     * @since 22
     */
    KEYCODE_F23 = 2826,
    /**
     * @brief F24 key
     * @since 22
     */
    KEYCODE_F24 = 2827,
    /**
     * @brief Program key 3
     * @since 22
     */
    KEYCODE_PROG3 = 2828,
    /**
     * @brief Program key 4
     * @since 22
     */
    KEYCODE_PROG4 = 2829,
    /**
     * @brief Dashboard
     * @since 22
     */
    KEYCODE_DASHBOARD = 2830,
    /**
     * @brief Suspend key
     * @since 22
     */
    KEYCODE_SUSPEND = 2831,
    /**
     * @brief HP key
     * @since 22
     */
    KEYCODE_HP = 2832,
    /**
     * @brief Sound key
     * @since 22
     */
    KEYCODE_SOUND = 2833,
    /**
     * @brief Question key
     * @since 22
     */
    KEYCODE_QUESTION = 2834,
    /**
     * @brief Connect key
     * @since 22
     */
    KEYCODE_CONNECT = 2836,
    /**
     * @brief Sport key
     * @since 22
     */
    KEYCODE_SPORT = 2837,
    /**
     * @brief Shop key
     * @since 22
     */
    KEYCODE_SHOP = 2838,
    /**
     * @brief Alternate key
     * @since 22
     */
    KEYCODE_ALTERASE = 2839,
    /**
     * @brief Cycle output between available videos (monitor/LCD/TV output/more)
     * @since 22
     */
    KEYCODE_SWITCHVIDEOMODE = 2841,
    /**
     * @brief Battery key
     * @since 22
     */
    KEYCODE_BATTERY = 2842,
    /**
     * @brief Bluetooth key
     * @since 22
     */
    KEYCODE_BLUETOOTH = 2843,
    /**
     * @brief WLAN key
     * @since 22
     */
    KEYCODE_WLAN = 2844,
    /**
     * @brief Ultra-wideband key
     * @since 22
     */
    KEYCODE_UWB = 2845,
    /**
     * @brief Mobile Network Control key
     * @since 22
     */
    KEYCODE_WWAN_WIMAX = 2846,
    /**
     * @brief RF Kill key
     * @since 22
     */
    KEYCODE_RFKILL = 2847,
    /**
     * @brief Channel key
     * @since 22
     */
    KEYCODE_CHANNEL = 3001,
    /**
     * @brief Button 0
     * @since 22
     */
    KEYCODE_BTN_0 = 3100,
    /**
     * @brief Button 1
     * @since 22
     */
    KEYCODE_BTN_1 = 3101,
    /**
     * @brief Button 2
     * @since 22
     */
    KEYCODE_BTN_2 = 3102,
    /**
     * @brief Button 3
     * @since 22
     */
    KEYCODE_BTN_3 = 3103,
    /**
     * @brief Button 4
     * @since 22
     */
    KEYCODE_BTN_4 = 3104,
    /**
     * @brief Button 5
     * @since 22
     */
    KEYCODE_BTN_5 = 3105,
    /**
     * @brief Button 6
     * @since 22
     */
    KEYCODE_BTN_6 = 3106,
    /**
     * @brief Button 7
     * @since 22
     */
    KEYCODE_BTN_7 = 3107,
    /**
     * @brief Button 8
     * @since 22
     */
    KEYCODE_BTN_8 = 3108,
    /**
     * @brief Button 9
     * @since 22
     */
    KEYCODE_BTN_9 = 3109,
    /**
     * @brief Single tapping the smart watch's X-TAP sensor
     * @since 22
     */
    KEYCODE_DAGGER_CLICK = 3211,
    /**
     * @brief Double tapping the smart watch's X-TAP sensor
     * @since 22
     */
    KEYCODE_DAGGER_DOUBLE_CLICK = 3212,
    /**
     * @brief Long-pressing the smart watch's X-TAP sensor
     * @since 22
     */
    KEYCODE_DAGGER_LONG_PRESS = 3213,
    /**
     * @brief Left button of the smart watch
     * @since 22
     */
    KEYCODE_DIV = 3220,
    /**
     * @brief Custom Shortcut Keys
     * @since 26.0.0
     */
    KEYCODE_XKEY = 3232,
    /**
     * @brief Smart control Key slide-up
     * @since 26.0.0
     */
    KEYCODE_FINGERPRINT_SLIDE_UP = 3233,
    /**
     * @brief Smart control Key slide-down
     * @since 26.0.0
     */
    KEYCODE_FINGERPRINT_SLIDE_DOWN = 3234
} Input_KeyCode;

#ifdef __cplusplus
}
#endif

#endif /* OH_KEY_CODE_H */
/** @} */