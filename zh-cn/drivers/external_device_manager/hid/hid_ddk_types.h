/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup HidDdk
 * @{
 *
 * @brief Provides HID DDK interfaces, including creating a device, sending an event, and destroying a device.
 *
 * @kit DriverDevelopmentKit
 * @syscap SystemCapability.Driver.HID.Extension
 * @since 11
 * @version 1.0
 */

/**
 * @brief 输入设备特性定义。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 指针设备
     */
    HID_PROP_POINTER = 0x00,

    /**
     * 直接输入设备
     */
    HID_PROP_DIRECT = 0x01,

    /**
     * 底部按键触摸设备
     */
    HID_PROP_BUTTON_PAD = 0x02,

    /**
     * 全多点触控设备
     */
    HID_PROP_SEMI_MT = 0x03,

    /**
     * 顶部软按键触摸设备
     */
    HID_PROP_TOP_BUTTON_PAD = 0x04,

    /**
     * 指点杆设备
     */
    HID_PROP_POINTING_STICK = 0x05,

    /**
     * 加速度传感器设备
     */
    HID_PROP_ACCELEROMETER = 0x06
} Hid_DeviceProp;

*/
typedef enum {
    /** Pointer device */
    HID_PROP_POINTER = 0x00,

    /** Direct input device */
    HID_PROP_DIRECT = 0x01,

    /** Touch device with bottom keys */
    HID_PROP_BUTTON_PAD = 0x02,

    /** Full multi-touch device */
    HID_PROP_SEMI_MT = 0x03,

    /** Touch device with top soft keys */
    HID_PROP_TOP_BUTTON_PAD = 0x04,

    /** Pointing stick */
    HID_PROP_POINTING_STICK = 0x05,

    /** Accelerometer */
    HID_PROP_ACCELEROMETER = 0x06
} Hid_DeviceProp;

/**
 * @brief 事件类型。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 同步事件
     */
    HID_EV_SYN = 0x00,

    /**
     * 按键事件
     */
    HID_EV_KEY = 0x01,

    /**
     * 相对坐标事件
     */
    HID_EV_REL = 0x02,

    /**
     * 绝对坐标事件
     */
    HID_EV_ABS = 0x03,

    /**
     * 特殊事件
     */
    HID_EV_MSC = 0x04
} Hid_EventType;

*/
typedef enum {
    /** Synchronization event */
    HID_EV_SYN = 0x00,

    /** Key event */
    HID_EV_KEY = 0x01,

    /** Relative coordinate event */
    HID_EV_REL = 0x02,

    /** Absolute coordinate event */
    HID_EV_ABS = 0x03,

    /** Other special event */
    HID_EV_MSC = 0x04
} Hid_EventType;

/**
 * @brief 同步事件编码。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 表示一个事件的结束
     */
    HID_SYN_REPORT = 0,

    /**
     * 表示配置同步
     */
    HID_SYN_CONFIG = 1,

    /**
     * 表示多点触摸的ABS数据包结束
     */
    HID_SYN_MT_REPORT = 2,

    /**
     * 表示该事件被丢弃
     */
    HID_SYN_DROPPED = 3
} Hid_SynEvent;

*/
typedef enum {
    /** Indicates the end of an event. */
    HID_SYN_REPORT = 0,

    /** Indicates configuration synchronization. */
    HID_SYN_CONFIG = 1,

    /** Indicates the end of a multi-touch ABS data packet. */
    HID_SYN_MT_REPORT = 2,

    /** Indicates that the event is discarded. */
    HID_SYN_DROPPED = 3
} Hid_SynEvent;

/**
 * @brief 键值编码。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 键A
     */
    HID_KEY_A = 30,

    /**
     * 键B
     */
    HID_KEY_B = 48,

    /**
     * 键C
     */
    HID_KEY_C = 46,

    /**
     * 键D
     */
    HID_KEY_D = 32,

    /**
     * 键E
     */
    HID_KEY_E = 18,

    /**
     * 键F
     */
    HID_KEY_F = 33,

    /**
     * 键G
     */
    HID_KEY_G = 34,

    /**
     * 键H
     */
    HID_KEY_H = 35,

    /**
     * 键I
     */
    HID_KEY_I = 23,

    /**
     * 键J
     */
    HID_KEY_J = 36,

    /**
     * 键K
     */
    HID_KEY_K = 37,

    /**
     * 键L
     */
    HID_KEY_L = 38,

    /**
     * 键M
     */
    HID_KEY_M = 50,

    /**
     * 键N
     */
    HID_KEY_N = 49,

    /**
     * 键O
     */
    HID_KEY_O = 24,

    /**
     * 键P
     */
    HID_KEY_P = 25,

    /**
     * 键Q
     */
    HID_KEY_Q = 16,

    /**
     * 键R
     */
    HID_KEY_R = 19,

    /**
     * 键S
     */
    HID_KEY_S = 31,

    /**
     * 键T
     */
    HID_KEY_T = 20,

    /**
     * 键U
     */
    HID_KEY_U = 22,

    /**
     * 键V
     */
    HID_KEY_V = 47,

    /**
     * 键W
     */
    HID_KEY_W = 17,

    /**
     * 键X
     */
    HID_KEY_X = 45,

    /**
     * 键Y
     */
    HID_KEY_Y = 21,

    /**
     * 键Z
     */
    HID_KEY_Z = 44,

    /**
     * 键ESC
     */
    HID_KEY_ESC = 1,

    /**
     * 键0
     */
    HID_KEY_0 = 11,

    /**
     * 键1
     */
    HID_KEY_1 = 2,

    /**
     * 键2
     */
    HID_KEY_2 = 3,

    /**
     * 键3
     */
    HID_KEY_3 = 4,

    /**
     * 键4
     */
    HID_KEY_4 = 5,

    /**
     * 键5
     */
    HID_KEY_5 = 6,

    /**
     * 键6
     */
    HID_KEY_6 = 7,

    /**
     * 键7
     */
    HID_KEY_7 = 8,

    /**
     * 键8
     */
    HID_KEY_8 = 9,

    /**
     * 键9
     */
    HID_KEY_9 = 10,

    /**
     * 键`
     */
    HID_KEY_GRAVE = 41,

    /**
     * 键-
     */
    HID_KEY_MINUS = 12,

    /**
     * 键=
     */
    HID_KEY_EQUALS = 13,

    /**
     * 键退格
     */
    HID_KEY_BACKSPACE = 14,

    /**
     * 键[
     */
    HID_KEY_LEFT_BRACKET = 26,

    /**
     * 键]
     */
    HID_KEY_RIGHT_BRACKET = 27,

    /**
     * 键回车
     */
    HID_KEY_ENTER = 28,

    /**
     * 键左shift
     */
    HID_KEY_LEFT_SHIFT = 42,

    /**
     * 键\
     */
    HID_KEY_BACKSLASH = 43,

    /**
     * 键;
     */
    HID_KEY_SEMICOLON = 39,

    /**
     * 键'
     */
    HID_KEY_APOSTROPHE = 40,

    /**
     * 键空格
     */
    HID_KEY_SPACE = 57,

    /**
     * 键/
     */
    HID_KEY_SLASH = 53,

    /**
     * 键,
     */
    HID_KEY_COMMA = 51,

    /**
     * 键.
     */
    HID_KEY_PERIOD = 52,

    /**
     * 键右shift
     */
    HID_KEY_RIGHT_SHIFT = 54,

    /**
     * 数字键0
     */
    HID_KEY_NUMPAD_0 = 82,

    /**
     * 数字键1
     */
    HID_KEY_NUMPAD_1 = 79,

    /**
     * 数字键2
     */
    HID_KEY_NUMPAD_2 = 80,

    /**
     * 数字键3
     */
    HID_KEY_NUMPAD_3 = 81,

    /**
     * 数字键4
     */
    HID_KEY_NUMPAD_4 = 75,

    /**
     * 数字键5
     */
    HID_KEY_NUMPAD_5 = 76,

    /**
     * 数字键6
     */
    HID_KEY_NUMPAD_6 = 77,

    /**
     * 数字键7
     */
    HID_KEY_NUMPAD_7 = 71,

    /**
     * 数字键8
     */
    HID_KEY_NUMPAD_8 = 72,

    /**
     * 数字键9
     */
    HID_KEY_NUMPAD_9 = 73,

    /**
     * 数字小键盘上的斜杠键（/）
     */
    HID_KEY_NUMPAD_DIVIDE = 70,

    /**
     * 数字小键盘上的星号键（*）
     */
    HID_KEY_NUMPAD_MULTIPLY = 55,

    /**
     * 数字键-
     */
    HID_KEY_NUMPAD_SUBTRACT = 74,

    /**
     * 数字键+
     */
    HID_KEY_NUMPAD_ADD = 78,

    /**
     * 数字键.
     */
    HID_KEY_NUMPAD_DOT = 83,

    /**
     * 键打印屏幕
     */
    HID_KEY_SYSRQ = 99,

    /**
     * 键删除
     */
    HID_KEY_DELETE = 111,

    /**
     * 键静音
     */
    HID_KEY_MUTE = 113,

    /**
     * 键音量-
     */
    HID_KEY_VOLUME_DOWN = 114,

    /**
     * 键音量+
     */
    HID_KEY_VOLUME_UP = 115,

    /**
     * 键亮度-
     */
    HID_KEY_BRIGHTNESS_DOWN = 224,

    /**
     * 键亮度+
     */
    HID_KEY_BRIGHTNESS_UP = 225,

    /**
     * 按钮0
     */
    HID_BTN_0 = 0x100,

    /**
     * 按钮1
     */
    HID_BTN_1 = 0x101,

    /**
     * 按钮2
     */
    HID_BTN_2 = 0x102,

    /**
     * 按钮3
     */
    HID_BTN_3 = 0x103,

    /**
     * 按钮4
     */
    HID_BTN_4 = 0x104,

    /**
     * 按钮5
     */
    HID_BTN_5 = 0x105,

    /**
     * 按钮6
     */
    HID_BTN_6 = 0x106,

    /**
     * 按钮7
     */
    HID_BTN_7 = 0x107,

    /**
     * 按钮8
     */
    HID_BTN_8 = 0x108,

    /**
     * 按钮9
     */
    HID_BTN_9 = 0x109,

    /**
     * 鼠标按键左键
     */
    HID_BTN_LEFT = 0x110,

    /**
     * 鼠标按键右键
     */
    HID_BTN_RIGHT = 0x111,

    /**
     * 鼠标按键中键
     */
    HID_BTN_MIDDLE = 0x112,

    /**
     * 鼠标侧面按键
     */
    HID_BTN_SIDE = 0x113,

    /**
     * 鼠标附加按键
     */
    HID_BTN_EXTRA = 0x114,

    /**
     * 鼠标向前按键
     */
    HID_BTN_FORWARD = 0x115,

    /**
     * 鼠标向后按键
     */
    HID_BTN_BACKWARD = 0x116,

    /**
     * 鼠标任务按键
     */
    HID_BTN_TASK = 0x117,

    /**
     * 画笔
     */
    HID_BTN_TOOL_PEN = 0x140,

    /**
     * 橡皮擦
     */
    HID_BTN_TOOL_RUBBER = 0x141,

    /**
     * 笔刷
     */
    HID_BTN_TOOL_BRUSH = 0x142,

    /**
     * 钢笔
     */
    HID_BTN_TOOL_PENCIL = 0x143,

    /**
     * 喷枪
     */
    HID_BTN_TOOL_AIRBRUSH = 0x144,

    /**
     * 手指
     */
    HID_BTN_TOOL_FINGER = 0x145,

    /**
     * 鼠标
     */
    HID_BTN_TOOL_MOUSE = 0x146,

    /**
     * 镜头
     */
    HID_BTN_TOOL_LENS = 0x147,

    /**
     * 五指触控
     */
    HID_BTN_TOOL_QUINT_TAP = 0x148,

    /**
     * 手写笔3
     */
    HID_BTN_STYLUS3 = 0x149,

    /**
     * 触摸
     */
    HID_BTN_TOUCH = 0x14a,

    /**
     * 手写笔
     */
    HID_BTN_STYLUS = 0x14b,

    /**
     * 手写笔2
     */
    HID_BTN_STYLUS2 = 0x14c,

    /**
     * 二指触控
     */
    HID_BTN_TOOL_DOUBLE_TAP = 0x14d,

    /**
     * 三指触控
     */
    HID_BTN_TOOL_TRIPLE_TAP = 0x14e,

    /**
     * 四指触控
     */
    HID_BTN_TOOL_QUAD_TAP = 0x14f,

    /**
     * 滚轮
     */
    HID_BTN_WHEEL = 0x150
} Hid_KeyCode;

*/
typedef enum {
    /** Key A */
    HID_KEY_A = 30,

    /** Key B */
    HID_KEY_B = 48,

    /** Key C */
    HID_KEY_C = 46,

    /** Key D */
    HID_KEY_D = 32,

    /** Key E */
    HID_KEY_E = 18,

    /** Key F */
    HID_KEY_F = 33,

    /** Key G */
    HID_KEY_G = 34,

    /** Key H */
    HID_KEY_H = 35,

    /** Key I */
    HID_KEY_I = 23,

    /** Key J */
    HID_KEY_J = 36,

    /** Key K */
    HID_KEY_K = 37,

    /** Key L */
    HID_KEY_L = 38,

    /** Key M */
    HID_KEY_M = 50,

    /** Key N */
    HID_KEY_N = 49,

    /** Key O */
    HID_KEY_O = 24,

    /** Key P */
    HID_KEY_P = 25,

    /** Key Q */
    HID_KEY_Q = 16,

    /** Key R */
    HID_KEY_R = 19,

    /** Key S */
    HID_KEY_S = 31,

    /** Key T */
    HID_KEY_T = 20,

    /** Key U */
    HID_KEY_U = 22,

    /** Key V */
    HID_KEY_V = 47,

    /** Key W */
    HID_KEY_W = 17,

    /** Key X */
    HID_KEY_X = 45,

    /** Key Y */
    HID_KEY_Y = 21,

    /** Key Z */
    HID_KEY_Z = 44,

    /** Key Esc */
    HID_KEY_ESC = 1,

    /** Key 0 */
    HID_KEY_0 = 11,

    /** Key 1 */
    HID_KEY_1 = 2,

    /** Key 2 */
    HID_KEY_2 = 3,

    /** Key 3 */
    HID_KEY_3 = 4,

    /** Key 4 */
    HID_KEY_4 = 5,

    /** Key 5 */
    HID_KEY_5 = 6,

    /** Key 6 */
    HID_KEY_6 = 7,

    /** Key 7 */
    HID_KEY_7 = 8,

    /** Key 8 */
    HID_KEY_8 = 9,

    /** Key 9 */
    HID_KEY_9 = 10,

    /** Key grave (`) */
    HID_KEY_GRAVE = 41,

    /** Key minum (-) */
    HID_KEY_MINUS = 12,

    /** Key equals (=) */
    HID_KEY_EQUALS = 13,

    /** Key backspace */
    HID_KEY_BACKSPACE = 14,

    /** Key left bracket ([) */
    HID_KEY_LEFT_BRACKET = 26,

    /** Key right bracket (]) */
    HID_KEY_RIGHT_BRACKET = 27,

    /** Key Enter */
    HID_KEY_ENTER = 28,

    /** Key left Shift */
    HID_KEY_LEFT_SHIFT = 42,

    /** Key backslash (\) */
    HID_KEY_BACKSLASH = 43,

    /** Key semicolon (;) */
    HID_KEY_SEMICOLON = 39,

    /** Key apostrophe (') */
    HID_KEY_APOSTROPHE = 40,

    /** Key space */
    HID_KEY_SPACE = 57,

    /** Key slash (/) */
    HID_KEY_SLASH = 53,

    /** Key comma (,) */
    HID_KEY_COMMA = 51,

    /** Key period (.) */
    HID_KEY_PERIOD = 52,

    /** Key right Shift */
    HID_KEY_RIGHT_SHIFT = 54,

    /** Numeral 0 on the numeric keypad */
    HID_KEY_NUMPAD_0 = 82,

    /** Numeral 1 on the numeric keypad */
    HID_KEY_NUMPAD_1 = 79,

    /** Numeral 2 on the numeric keypad */
    HID_KEY_NUMPAD_2 = 80,

    /** Numeral 3 on the numeric keypad */
    HID_KEY_NUMPAD_3 = 81,

    /** Numeral 4 on the numeric keypad */
    HID_KEY_NUMPAD_4 = 75,

    /** Numeral 5 on the numeric keypad */
    HID_KEY_NUMPAD_5 = 76,

    /** Numeral 6 on the numeric keypad*/
    HID_KEY_NUMPAD_6 = 77,

    /** Numeral 7 on the numeric keypad */
    HID_KEY_NUMPAD_7 = 71,

    /** Numeral 8 on the numeric keypad */
    HID_KEY_NUMPAD_8 = 72,

    /** Numeral 9 on the numeric keypad */
    HID_KEY_NUMPAD_9 = 73,

    /** Arithmetic operator / (division) on the numeric keypad */
    HID_KEY_NUMPAD_DIVIDE = 70,

    /** Arithmetic operator * (multiplication) on the numeric keypad */
    HID_KEY_NUMPAD_MULTIPLY = 55,

    /** Arithmetic operator - (subtraction) on the numeric keypad */
    HID_KEY_NUMPAD_SUBTRACT = 74,

    /** Arithmetic operator + (addition) on the numeric keypad */
    HID_KEY_NUMPAD_ADD = 78,

    /** Decimal point (.) on the numeric keypad */
    HID_KEY_NUMPAD_DOT = 83,

    /** Key Print Screen */
    HID_KEY_SYSRQ = 99,

    /** Key Delete */
    HID_KEY_DELETE = 111,

    /** Key Mute */
    HID_KEY_MUTE = 113,

    /** Key for volume down */
    HID_KEY_VOLUME_DOWN = 114,

    /** Key for volume up */
    HID_KEY_VOLUME_UP = 115,

    /** Key for decreasing brightness */
    HID_KEY_BRIGHTNESS_DOWN = 224,

    /** Key for increasing brightness */
    HID_KEY_BRIGHTNESS_UP = 225,

    /** Button 0 */
    HID_BTN_0 = 0x100,

    /** Button 1 */
    HID_BTN_1 = 0x101,

    /** Button 2 */
    HID_BTN_2 = 0x102,

    /** Button 3 */
    HID_BTN_3 = 0x103,

    /** Button 4 */
    HID_BTN_4 = 0x104,

    /** Button 5 */
    HID_BTN_5 = 0x105,

    /** Button 6 */
    HID_BTN_6 = 0x106,

    /** Button 7 */
    HID_BTN_7 = 0x107,

    /** Button 8 */
    HID_BTN_8 = 0x108,

    /** Button 9 */
    HID_BTN_9 = 0x109,

    /** Left mouse button */
    HID_BTN_LEFT = 0x110,

    /** Right mouse button */
    HID_BTN_RIGHT = 0x111,

    /** Middle mouse button */
    HID_BTN_MIDDLE = 0x112,

    /** Side mouse button */
    HID_BTN_SIDE = 0x113,

    /** Extra mouse button */
    HID_BTN_EXTRA = 0x114,

    /** Mouse forward button */
    HID_BTN_FORWARD = 0x115,

    /** Mouse backward button */
    HID_BTN_BACKWARD = 0x116,

    /** Mouse task button */
    HID_BTN_TASK = 0x117,

    /** Pen */
    HID_BTN_TOOL_PEN = 0x140,

    /** Rubber */
    HID_BTN_TOOL_RUBBER = 0x141,

    /** Brush */
    HID_BTN_TOOL_BRUSH = 0x142,

    /** Pencil */
    HID_BTN_TOOL_PENCIL = 0x143,

    /** Air brush */
    HID_BTN_TOOL_AIRBRUSH = 0x144,

    /** Finger */
    HID_BTN_TOOL_FINGER = 0x145,

    /** Mouse */
    HID_BTN_TOOL_MOUSE = 0x146,

    /** Lens */
    HID_BTN_TOOL_LENS = 0x147,

    /** Five-finger touch */
    HID_BTN_TOOL_QUINT_TAP = 0x148,

    /** Stylus 3 */
    HID_BTN_STYLUS3 = 0x149,

    /** Touch */
    HID_BTN_TOUCH = 0x14a,

    /** Stylus */
    HID_BTN_STYLUS = 0x14b,

    /** Stylus 2 */
    HID_BTN_STYLUS2 = 0x14c,

    /** Two-finger touch */
    HID_BTN_TOOL_DOUBLE_TAP = 0x14d,

    /** Three-finger touch */
    HID_BTN_TOOL_TRIPLE_TAP = 0x14e,

    /** Four-finger touch */
    HID_BTN_TOOL_QUAD_TAP = 0x14f,

    /** Scroll wheel */
    HID_BTN_WHEEL = 0x150
} Hid_KeyCode;

/**
 * @brief 绝对坐标编码。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * X轴
     */
    HID_ABS_X = 0x00,

    /**
     * Y轴
     */
    HID_ABS_Y = 0x01,

    /**
     * Z轴
     */
    HID_ABS_Z = 0x02,

    /**
     * 右模拟摇杆的 X 轴
     */
    HID_ABS_RX = 0x03,

    /**
     * 右模拟摇杆的 Y 轴
     */
    HID_ABS_RY = 0x04,

    /**
     * 右模拟摇杆的 Z 轴
     */
    HID_ABS_RZ = 0x05,

    /**
     * 油门
     */
    HID_ABS_THROTTLE = 0x06,

    /**
     * 舵
     */
    HID_ABS_RUDDER = 0x07,

    /**
     * 滚轮
     */
    HID_ABS_WHEEL = 0x08,

    /**
     * 气
     */
    HID_ABS_GAS = 0x09,

    /**
     * 制动
     */
    HID_ABS_BRAKE = 0x0a,

    /**
     * HAT0X
     */
    HID_ABS_HAT0X = 0x10,

    /**
     * HAT0Y
     */
    HID_ABS_HAT0Y = 0x11,

    /**
     * HAT1X
     */
    HID_ABS_HAT1X = 0x12,

    /**
     * HAT1Y
     */
    HID_ABS_HAT1Y = 0x13,

    /**
     * HAT2X
     */
    HID_ABS_HAT2X = 0x14,

    /**
     * HAT2Y
     */
    HID_ABS_HAT2Y = 0x15,

    /**
     * HAT3X
     */
    HID_ABS_HAT3X = 0x16,

    /**
     * HAT3Y
     */
    HID_ABS_HAT3Y = 0x17,

    /**
     * 压力
     */
    HID_ABS_PRESSURE = 0x18,

    /**
     * 距离
     */
    HID_ABS_DISTANCE = 0x19,

    /**
     * X轴倾斜度
     */
    HID_ABS_TILT_X = 0x1a,

    /**
     * Y轴倾斜度
     */
    HID_ABS_TILT_Y = 0x1b,

    /**
     * 触摸工具的宽度
     */
    HID_ABS_TOOL_WIDTH = 0x1c,

    /**
     * 音量
     */
    HID_ABS_VOLUME = 0x20,

    /**
     * 其它
     */
    HID_ABS_MISC = 0x28
} Hid_AbsAxes;

*/
typedef enum {
    /** X axis */
    HID_ABS_X = 0x00,

    /** Y axis */
    HID_ABS_Y = 0x01,

    /** Z axis */
    HID_ABS_Z = 0x02,

    /** X axis of the right analog stick */
    HID_ABS_RX = 0x03,

    /** Y axis of the right analog stick */
    HID_ABS_RY = 0x04,

    /** Z axis of the right analog stick */
    HID_ABS_RZ = 0x05,

    /** Throttle */
    HID_ABS_THROTTLE = 0x06,

    /** Rudder */
    HID_ABS_RUDDER = 0x07,

    /** Scroll wheel */
    HID_ABS_WHEEL = 0x08,

    /** Gas */
    HID_ABS_GAS = 0x09,

    /** Brake */
    HID_ABS_BRAKE = 0x0a,

    /** HAT0X */
    HID_ABS_HAT0X = 0x10,

    /** HAT0Y */
    HID_ABS_HAT0Y = 0x11,

    /** HAT1X */
    HID_ABS_HAT1X = 0x12,

    /** HAT1Y */
    HID_ABS_HAT1Y = 0x13,

    /** HAT2X */
    HID_ABS_HAT2X = 0x14,

    /** HAT2Y */
    HID_ABS_HAT2Y = 0x15,

    /** HAT3X */
    HID_ABS_HAT3X = 0x16,

    /** HAT3Y */
    HID_ABS_HAT3Y = 0x17,

    /** Pressure */
    HID_ABS_PRESSURE = 0x18,

    /** Distance */
    HID_ABS_DISTANCE = 0x19,

    /** Inclination of X axis */
    HID_ABS_TILT_X = 0x1a,

    /** Inclination of Y axis */
    HID_ABS_TILT_Y = 0x1b,

    /** Width of the touch tool */
    HID_ABS_TOOL_WIDTH = 0x1c,

    /** Volume */
    HID_ABS_VOLUME = 0x20,

    /** Others */
    HID_ABS_MISC = 0x28
} Hid_AbsAxes;

/**
 * @brief 相对坐标编码。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * X轴
     */
    HID_REL_X = 0x00,

    /**
     * Y轴
     */
    HID_REL_Y = 0x01,

    /**
     * Z轴
     */
    HID_REL_Z = 0x02,

    /**
     * 右模拟摇杆的 X 轴
     */
    HID_REL_RX = 0x03,

    /**
     * 右模拟摇杆的 Y 轴
     */
    HID_REL_RY = 0x04,

    /**
     * 右模拟摇杆的 Z 轴
     */
    HID_REL_RZ = 0x05,

    /**
     * 水平滚轮
     */
    HID_REL_HWHEEL = 0x06,

    /**
     * 刻度
     */
    HID_REL_DIAL = 0x07,

    /**
     * 滚轮
     */
    HID_REL_WHEEL = 0x08,

    /**
     * 其它
     */
    HID_REL_MISC = 0x09,

    /**
     * 高分辨率滚轮
     */
    HID_REL_WHEEL_HI_RES = 0x0b,

    /**
     * 高分辨率水平滚轮
     */
    HID_REL_HWHEEL_HI_RES = 0x0c
} Hid_RelAxes;

*/
typedef enum {
    /** X axis */
    HID_REL_X = 0x00,

    /** Y axis */
    HID_REL_Y = 0x01,

    /** Z axis */
    HID_REL_Z = 0x02,

    /** X axis of the right analog stick */
    HID_REL_RX = 0x03,

    /** Y axis of the right analog stick */
    HID_REL_RY = 0x04,

    /** Z axis of the right analog stick */
    HID_REL_RZ = 0x05,

    /** Horizontal scroll wheel */
    HID_REL_HWHEEL = 0x06,

    /** Scale */
    HID_REL_DIAL = 0x07,

    /** Scroll wheel */
    HID_REL_WHEEL = 0x08,

    /** Others */
    HID_REL_MISC = 0x09,

    /* Reserved */
    HID_REL_RESERVED = 0x0a,

    /** High-resolution scroll wheel */
    HID_REL_WHEEL_HI_RES = 0x0b,

    /** High-resolution horizontal scroll wheel */
    HID_REL_HWHEEL_HI_RES = 0x0c
} Hid_RelAxes;

/**
 * @brief 不适合其它类型的输入事件编码。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 序列号
     */
    HID_MSC_SERIAL = 0x00,

    /**
     * 脉冲
     */
    HID_MSC_PULSE_LED = 0x01,

    /**
     * 手势
     */
    HID_MSC_GESTURE = 0x02,

    /**
     * 开始事件
     */
    HID_MSC_RAW = 0x03,

    /**
     * 扫描
     */
    HID_MSC_SCAN = 0x04,

    /**
     * 时间戳
     */
    HID_MSC_TIMESTAMP = 0x05
} Hid_MscEvent;

*/
typedef enum {
    /** Serial number */
    HID_MSC_SERIAL = 0x00,

    /** Pulse */
    HID_MSC_PULSE_LED = 0x01,

    /** Gesture */
    HID_MSC_GESTURE = 0x02,

    /** Start event */
    HID_MSC_RAW = 0x03,

    /** Scan */
    HID_MSC_SCAN = 0x04,

    /** Timestamp */
    HID_MSC_TIMESTAMP = 0x05
} Hid_MscEvent;

/**
 * @brief HID DDK错误码定义。
 *
 * @since 11
 * @version 1.0
 */
typedef enum {
    /**
     * 操作成功。
     */
    HID_DDK_SUCCESS = 0,

    /**
     * 没有权限，从API 16起，取值由-6变更为201。
     */
    HID_DDK_NO_PERM = 201,

    /**
     * 非法参数，从API 16起，取值由-2变更为401。
     */
    HID_DDK_INVALID_PARAMETER = 401,

    /**
     * 操作失败，从API 16起，取值由-1变更为27300001。
     */
    HID_DDK_FAILURE = 27300001,

    /**
     * 空指针异常，从API 16起，取值由-4变更为27300002。
     */
    HID_DDK_NULL_PTR = 27300002,

    /**
     * 非法操作，从API 16起，取值由-3变更为27300003。
     */
    HID_DDK_INVALID_OPERATION = 27300003,

    /**
     * 超时，从API 16起，取值由-5变更为27300004。
     */
    HID_DDK_TIMEOUT = 27300004,

    /**
     * 初始化DDK失败或DDK未初始化。
     * @since 18
     */
    HID_DDK_INIT_ERROR = 27300005,

    /**
     * 服务通信过程中错误。
     * @since 18
     */
    HID_DDK_SERVICE_ERROR = 27300006,

    /**
     * 内存相关的错误，包括：内存数据拷贝失败、内存申请失败等。
     * @since 18
     */
    HID_DDK_MEMORY_ERROR  = 27300007,

    /**
     * I/O操作失败。
     * @since 18
     */
    HID_DDK_IO_ERROR = 27300008,

    /**
     * 设备未找到。
     * @since 18
     */
    HID_DDK_DEVICE_NOT_FOUND = 27300009
} Hid_DdkErrCode;

*/
typedef enum {
    /** @error Operation successful */
    HID_DDK_SUCCESS = 0,

    /** @error Permission denied */
    HID_DDK_NO_PERM = 201,

    /** @error Invalid parameter */
    HID_DDK_INVALID_PARAMETER = 401,

    /** @error Operation failed */
    HID_DDK_FAILURE = 27300001,

    /** @error Null pointer exception */
    HID_DDK_NULL_PTR = 27300002,

    /** @error Invalid operation */
    HID_DDK_INVALID_OPERATION = 27300003,

        HID_DDK_TIMEOUT = 27300004,

        HID_DDK_INIT_ERROR = 27300005,

        HID_DDK_SERVICE_ERROR = 27300006,

        HID_DDK_MEMORY_ERROR  = 27300007,

        HID_DDK_IO_ERROR = 27300008,

    /** @error Device not found.
     *  @since 18
     */
    HID_DDK_DEVICE_NOT_FOUND = 27300009
} Hid_DdkErrCode;

/**
 * @brief 不透明的USB HID设备结构。
 *
 * @since 18
 */
typedef struct Hid_DeviceHandle Hid_DeviceHandle;

/**
 * @brief Defines the opaque USB HID device structure.
 *
 * @since 18
 */
typedef struct Hid_DeviceHandle Hid_DeviceHandle;

/**
 * @brief 报告（HID设备与主机之间交换的数据包）类型定义。
 *
 * @since 18
 */
typedef enum {
    /**
     * 输入报告
     */
    HID_INPUT_REPORT = 0,

    /**
     * 输出报告
     */
    HID_OUTPUT_REPORT = 1,

    /**
     * 特性报告
     */
    HID_FEATURE_REPORT = 2
} Hid_ReportType;

*/
typedef enum {
    /** Input report */
    HID_INPUT_REPORT = 0,

    /** Output report */
    HID_OUTPUT_REPORT = 1,

    /** Feature report */
    HID_FEATURE_REPORT = 2
} Hid_ReportType;

/**
 * @brief Defines a struct for basic device information.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_Device {
    /**
     * Device name.
     */
    const char *deviceName;
    /**
     * Vendor ID.
     */
    uint16_t vendorId;
    /**
     * Product ID.
     */
    uint16_t productId;
    /**
     * Version number.
     */
    uint16_t version;
    /**
     * Bus type.
     */
    uint16_t bustype;
    /**
     * Device properties indicated by {@link Hid_DeviceProp}.
     */
    Hid_DeviceProp *properties;
    /**
     * Number of device properties.
     */
    uint16_t propLength;
} Hid_Device;

/**
 * @brief Defines a struct for basic device information.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_Device {
    /**
     * Device name.
     */
    const char *deviceName;
    /**
     * Vendor ID.
     */
    uint16_t vendorId;
    /**
     * Product ID.
     */
    uint16_t productId;
    /**
     * Version number.
     */
    uint16_t version;
    /**
     * Bus type.
     */
    uint16_t bustype;
    /**
     * Device properties indicated by {@link Hid_DeviceProp}.
     */
    Hid_DeviceProp *properties;
    /**
     * Number of device properties.
     */
    uint16_t propLength;
} Hid_Device;

/**
 * @brief Represents the event information.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_EmitItem {
    /**
     * Event type.
     */
    uint16_t type;
    /**
     * Event code.
     */
    uint16_t code;
    /**
     * Event value.
     */
    uint32_t value;
} Hid_EmitItem;

/**
 * @brief Represents the event information.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_EmitItem {
    /**
     * Event type.
     */
    uint16_t type;
    /**
     * Event code.
     */
    uint16_t code;
    /**
     * Event value.
     */
    uint32_t value;
} Hid_EmitItem;

/**
 * @brief Defines a struct for an array of event types.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_EventTypeArray {
    /**
     * Array of event types.
     */
    Hid_EventType *hidEventType;
    /**
     * Valid length of an array.
     */
    uint16_t length;
} Hid_EventTypeArray;

/**
 * @brief Defines a struct for an array of event types.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_EventTypeArray {
    /**
     * Array of event types.
     */
    Hid_EventType *hidEventType;
    /**
     * Valid length of an array.
     */
    uint16_t length;
} Hid_EventTypeArray;

/**
 * @brief Defines a struct for the event properties of a device.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_EventProperties {
    /**
     * Array of event types.
     */
    struct Hid_EventTypeArray hidEventTypes;
    /**
     * Array of key codes.
     */
    struct Hid_KeyCodeArray hidKeys;
    /**
     * Array of absolute coordinate properties.
     */
    struct Hid_AbsAxesArray hidAbs;
    /**
     * Array of relative coordinate properties.
     */
    struct Hid_RelAxesArray hidRelBits;
    /**
     * Array of miscellaneous events.
     */
    struct Hid_MscEventArray hidMiscellaneous;

    /** Maximum values of the absolute coordinates */
    int32_t hidAbsMax[64];
    /** Minimum values of the absolute coordinates */
    int32_t hidAbsMin[64];
    /** Fuzzy values of the absolute coordinates */
    int32_t hidAbsFuzz[64];
    /** Fixed values of the absolute coordinates */
    int32_t hidAbsFlat[64];
} Hid_EventProperties;

/**
 * @brief Defines a struct for the event properties of a device.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_EventProperties {
    /**
     * Array of event types.
     */
    struct Hid_EventTypeArray hidEventTypes;
    /**
     * Array of key codes.
     */
    struct Hid_KeyCodeArray hidKeys;
    /**
     * Array of absolute coordinate properties.
     */
    struct Hid_AbsAxesArray hidAbs;
    /**
     * Array of relative coordinate properties.
     */
    struct Hid_RelAxesArray hidRelBits;
    /**
     * Array of miscellaneous events.
     */
    struct Hid_MscEventArray hidMiscellaneous;

    /**
     * Maximum values of the absolute coordinates.
     */
    int32_t hidAbsMax[64];
    /**
     * Minimum values of the absolute coordinates.
     */
    int32_t hidAbsMin[64];
    /**
     * Fuzzy values of the absolute coordinates.
     */
    int32_t hidAbsFuzz[64];
    /**
     * Fixed values of the absolute coordinates.
     */
    int32_t hidAbsFlat[64];
} Hid_EventProperties;

/**
 * @brief 
 * 定义原始开发信息。
 * @since 18
 */
typedef struct Hid_RawDevInfo {
    /**
     * Bus type.
     */
    uint32_t busType;
    /**
     * Vendor ID.
     */
    uint16_t vendor;
    /**
     * Product ID.
     */
    uint16_t product;
} Hid_RawDevInfo;

/**
 * @brief 
 * 定义原始开发信息。
 * @since 18
 */
typedef struct Hid_RawDevInfo {
    /**
     * Bus type.
     */
    uint32_t busType;
    /**
     * Vendor ID.
     */
    uint16_t vendor;
    /**
     * Product ID.
     */
    uint16_t product;
} Hid_RawDevInfo;

/**
 * @brief Defines an array of miscellaneous events.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_MscEventArray {
    /**
     * Array of Miscellaneous events.
     */
    Hid_MscEvent *hidMscEvent;
    /**
     * Valid length of an array.
     */
    uint16_t length;
} Hid_MscEventArray;

/**
 * @brief Defines an array of miscellaneous events.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_MscEventArray {
    /**
     * Miscellaneous events.
     */
    Hid_MscEvent *hidMscEvent;
    /**
     * Valid length of an array.
     */
    uint16_t length;
} Hid_MscEventArray;

/**
 * @brief Defines a struct for the key code array.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_KeyCodeArray {
    /**
     * Key code array.
     */
    Hid_KeyCode *hidKeyCode;
    /**
     * Valid length of an array.
     */
    uint16_t length;
} Hid_KeyCodeArray;

/**
 * @brief Defines a struct for the key code array.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_KeyCodeArray {
    /**
     * Key code array.
     */
    Hid_KeyCode *hidKeyCode;
    /**
     * Valid length of an array.
     */
    uint16_t length;
} Hid_KeyCodeArray;

/**
 * @brief Defines an array of absolute coordinates.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_AbsAxesArray {
    /**
     * Array of absolute coordinates.
     */
    Hid_AbsAxes *hidAbsAxes;
    /**
     * Valid length of an array.
     */
    uint16_t length;
} Hid_AbsAxesArray;

/**
 * @brief Defines an array of absolute coordinates.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_AbsAxesArray {
    /**
     * Array of absolute coordinates.
     */
    Hid_AbsAxes *hidAbsAxes;
    /**
     * Valid length of an array.
     */
    uint16_t length;
} Hid_AbsAxesArray;

/**
 * @brief Defines an array of relative coordinates.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_RelAxesArray {
    /**
     * Array of relative coordinates.
     */
    Hid_RelAxes *hidRelAxes;
    /**
     * Valid length of an array.
     */
    uint16_t length;
} Hid_RelAxesArray;

/**
 * @brief Defines an array of relative coordinates.
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_RelAxesArray {
    /**
     * Array of relative coordinates.
     */
    Hid_RelAxes *hidRelAxes;
    /**
     * Valid length of an array.
     */
    uint16_t length;
} Hid_RelAxesArray;
#ifndef HID_DDK_TYPES_H
#define HID_DDK_TYPES_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/**
 * @brief max report buffer size.
 *
 * @since 18
 */
#define HID_MAX_REPORT_BUFFER_SIZE (16 * 1024 - 1)
/**
 * @brief Defines the maximum size of the report buffer.
 *
 * @since 18
 */
#define HID_MAX_REPORT_BUFFER_SIZE (16 * 1024 - 1)

#ifdef __cplusplus
}
#endif
#endif // HID_DDK_TYPES_H
/** @} */
#ifdef __cplusplus
}
#endif
/** @} */