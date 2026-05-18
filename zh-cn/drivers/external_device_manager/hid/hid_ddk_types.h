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
 * @file hid_ddk_types.h
 *
 * @brief 提供HID DDK中的枚举变量与结构体定义。
 *
 * @library libhid.z.so
 * @syscap SystemCapability.Driver.HID.Extension
 * @since 11
 * @version 1.0
 */

#ifndef HID_DDK_TYPES_H
#define HID_DDK_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief 事件信息。
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_EmitItem {
    /**
     * 事件类型
     */
    uint16_t type;
    /**
     * 事件编码
     */
    uint16_t code;
    /**
     * 事件值
     */
    uint32_t value;
} Hid_EmitItem;

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

/**
 * @brief 设备基本信息。
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_Device {
    /**
     * 设备名称
     */
    const char *deviceName;
    /**
     * 厂商ID
     */
    uint16_t vendorId;
    /**
     * 产品ID
     */
    uint16_t productId;
    /**
     * 版本号
     */
    uint16_t version;
    /**
     * 总线类型
     */
    uint16_t bustype;
    /**
     * 由{@link Hid_DeviceProp}表示的设备特性
     */
    Hid_DeviceProp *properties;
    /**
     * 设备特性数量
     */
    uint16_t propLength;
} Hid_Device;

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
     * 预留
     */
    HID_REL_RESERVED = 0x0a,
    /**
     * 高分辨率滚轮
     */
    HID_REL_WHEEL_HI_RES = 0x0b,
    /**
     * 高分辨率水平滚轮
     */
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

/**
 * @brief 事件类型编码数组。
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_EventTypeArray {
    /**
     * 事件类型编码
     */
    Hid_EventType *hidEventType;
    /**
     * 数组的有效长度
     */
    uint16_t length;
} Hid_EventTypeArray;

/**
 * @brief 键值属性数组。
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_KeyCodeArray {
    /**
     * 键值编码
     */
    Hid_KeyCode *hidKeyCode;
    /**
     * 数组的有效长度
     */
    uint16_t length;
} Hid_KeyCodeArray;

/**
 * @brief 绝对坐标属性数组。
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_AbsAxesArray {
    /**
     * 绝对坐标属性编码
     */
    Hid_AbsAxes *hidAbsAxes;
    /**
     * 数组的有效长度
     */
    uint16_t length;
} Hid_AbsAxesArray;

/**
 * @brief 相对坐标属性数组。
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_RelAxesArray {
    /**
     * 相对坐标属性编码
     */
    Hid_RelAxes *hidRelAxes;
    /**
     * 数组的有效长度
     */
    uint16_t length;
} Hid_RelAxesArray;

/**
 * @brief 其他特殊事件属性数组。
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_MscEventArray {
    /**
     * 其他特殊事件属性编码
     */
    Hid_MscEvent *hidMscEvent;
    /**
     * 数组的有效长度
     */
    uint16_t length;
} Hid_MscEventArray;

/**
 * @brief 设备关注事件属性。
 *
 * @since 11
 * @version 1.0
 */
typedef struct Hid_EventProperties {
    /**
     * 事件类型属性编码数组
     */
    struct Hid_EventTypeArray hidEventTypes;
    /**
     * 键值属性编码数组
     */
    struct Hid_KeyCodeArray hidKeys;
    /**
     * 绝对坐标属性编码数组
     */
    struct Hid_AbsAxesArray hidAbs;
    /**
     * 相对坐标属性编码数组
     */
    struct Hid_RelAxesArray hidRelBits;
    /**
     * 其它特殊事件属性编码数组
     */
    struct Hid_MscEventArray hidMiscellaneous;

    /**
     * 绝对坐标属性最大值
     */
    int32_t hidAbsMax[64];
    /**
     * 绝对坐标属性最小值
     */
    int32_t hidAbsMin[64];
    /**
     * 绝对坐标属性模糊值
     */
    int32_t hidAbsFuzz[64];
    /**
     * 绝对坐标属性固定值
     */
    int32_t hidAbsFlat[64];
} Hid_EventProperties;

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

/**
 * @brief 最大报告缓冲区大小。
 *
 * @since 18
 */
#define HID_MAX_REPORT_BUFFER_SIZE (16 * 1024 - 1)

/**
 * @brief 不透明的USB HID设备结构。
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

/**
 * @brief 原始设备信息定义。
 *
 * @since 18
 */
typedef struct Hid_RawDevInfo {
    /**
     * 总线类型
     */
    uint32_t busType;
    /**
     * 供应商ID
     */
    uint16_t vendor;
    /**
     * 产品ID
     */
    uint16_t product;
} Hid_RawDevInfo;
#ifdef __cplusplus
}
/** @} */
#endif /* __cplusplus */
#endif // HID_DDK_TYPES_H
