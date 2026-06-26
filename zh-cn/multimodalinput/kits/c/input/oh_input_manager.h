/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
 * @file oh_input_manager.h
 *
 * @brief Provides functions such as input event injection, key state query, device hot swapping listener, event
 * interception, hotkey management, mouse cursor management, input device information query, and injection permission
 * management.
 *
 * @kit InputKit
 * @syscap SystemCapability.MultimodalInput.Input.Core
 * @library liboh_input.so
 * @since 12
 */

#ifndef OH_INPUT_MANAGER_H
#define OH_INPUT_MANAGER_H

#include <stdint.h>

#include "oh_axis_type.h"
#include "oh_key_code.h"
#include "oh_pointer_style.h"

#ifdef __cplusplus
extern "C" {
#endif

struct OH_PixelmapNative;

/**
* @brief 按键状态的枚举值。
*
* @since 12
*/
typedef enum Input_KeyStateAction {
    /**
* 默认状态。
*/
    KEY_DEFAULT = -1,

    /**
* 按键按下。
*/
    KEY_PRESSED = 0,

    /**
* 按键抬起。
*/
    KEY_RELEASED = 1,

    /**
* 按键开关使能。
*/
    KEY_SWITCH_ON = 2,

    /**
* 按键开关去使能。
*/
    KEY_SWITCH_OFF = 3
} Input_KeyStateAction;

/**
* @brief 按键事件类型的枚举值。
*
* @since 12
*/
typedef enum Input_KeyEventAction {
    /**
* 按键动作取消。
*/
    KEY_ACTION_CANCEL = 0,

    /**
* 按键按下。
*/
    KEY_ACTION_DOWN = 1,

    /**
* 按键抬起。
*/
    KEY_ACTION_UP = 2
} Input_KeyEventAction;

/**
* @brief 鼠标动作的枚举值。
*
* @since 12
*/
typedef enum Input_MouseEventAction {
    /**
* 取消鼠标动作。
*/
    MOUSE_ACTION_CANCEL = 0,

    /**
* 移动鼠标。
*/
    MOUSE_ACTION_MOVE = 1,

    /**
* 按下鼠标。
*/
    MOUSE_ACTION_BUTTON_DOWN = 2,

    /**
* 抬起鼠标按键。
*/
    MOUSE_ACTION_BUTTON_UP = 3,

    /**
* 鼠标轴事件开始。
*/
    MOUSE_ACTION_AXIS_BEGIN = 4,

    /**
* 更新鼠标轴事件。
*/
    MOUSE_ACTION_AXIS_UPDATE = 5,

    /**
* 鼠标轴事件结束。
*/
    MOUSE_ACTION_AXIS_END = 6
} Input_MouseEventAction;

/**
* @brief 鼠标轴事件类型。
*
* @since 12
*/
typedef enum InputEvent_MouseAxis {
    /**
* 垂直滚动轴。
*/
    MOUSE_AXIS_SCROLL_VERTICAL = 0,

    /**
* 水平滚动轴。
*/
    MOUSE_AXIS_SCROLL_HORIZONTAL = 1
} InputEvent_MouseAxis;

/**
* @brief 鼠标按键的枚举值。
*
* @since 12
*/
typedef enum Input_MouseEventButton {
    /**
* 无效按键。
*/
    MOUSE_BUTTON_NONE = -1,

    /**
* 鼠标左键。
*/
    MOUSE_BUTTON_LEFT = 0,

    /**
* 鼠标中间键。
*/
    MOUSE_BUTTON_MIDDLE = 1,

    /**
* 鼠标右键。
*/
    MOUSE_BUTTON_RIGHT = 2,

    /**
* 鼠标前进键。
*/
    MOUSE_BUTTON_FORWARD = 3,

    /**
* 鼠标返回键。
*/
    MOUSE_BUTTON_BACK = 4
} Input_MouseEventButton;

/**
* @brief 触屏动作的枚举值。
*
* @since 12
*/
typedef enum Input_TouchEventAction {
    /**
* 触屏取消。
*/
    TOUCH_ACTION_CANCEL = 0,

    /**
* 触屏按下。
*/
    TOUCH_ACTION_DOWN = 1,

    /**
* 触屏移动。
*/
    TOUCH_ACTION_MOVE = 2,

    /**
* 触屏抬起。
*/
    TOUCH_ACTION_UP = 3
} Input_TouchEventAction;

/**
* @brief 输入设备的键盘类型。
*
* @since 13
*/
typedef enum Input_KeyboardType {
    /**
* 表示无按键设备。
*/
    KEYBOARD_TYPE_NONE = 0,

    /**
* 表示未知按键设备。
*/
    KEYBOARD_TYPE_UNKNOWN = 1,

    /**
* 表示全键盘设备。
*/
    KEYBOARD_TYPE_ALPHABETIC = 2,

    /**
* 表示数字键盘设备。
*/
    KEYBOARD_TYPE_DIGITAL = 3,

    /**
* 表示手写笔设备。
*/
    KEYBOARD_TYPE_STYLUS = 4,

    /**
* 表示遥控器设备。
*/
    KEYBOARD_TYPE_REMOTE_CONTROL = 5
} Input_KeyboardType;

/**
* @brief 注入权限状态枚举值。
*
* @since 20
*/
typedef enum Input_InjectionStatus {
    /**
* 未授权。
*/
    UNAUTHORIZED = 0,

    /**
* 授权中。
*/
    AUTHORIZING = 1,

    /**
* 已授权。
*/
    AUTHORIZED = 2
} Input_InjectionStatus;

/**
* @brief 输入事件源类型。
*
* @since 12
*/
typedef enum InputEvent_SourceType {
    /**
* 表示输入源生成鼠标光标移动、按键按下和释放以及滚轮滚动的事件。
* @since 12
*/
    SOURCE_TYPE_MOUSE = 1,

    /**
* 表示输入源产生触摸屏多点触屏输入事件。
* @since 12
*/
    SOURCE_TYPE_TOUCHSCREEN = 2,

    /**
* 表示输入源产生触控板多点触屏输入事件。
* @since 12
*/
    SOURCE_TYPE_TOUCHPAD = 3
} InputEvent_SourceType;

/**
* @brief 定义按键信息，用于标识按键行为。例如，“Ctrl”按键信息包含键值和键状态。适用于快捷键处理、输入事件状态管理、按键状态检测等场景。
*
* @since 12
*/
typedef struct Input_KeyState Input_KeyState;

/**
* @brief 按键事件对象，用于表示用户按键操作产生的输入事件，包含按键码、按键状态等信息，可用于处理键盘输入和实现按键响应功能。
*
* @since 12
*/
typedef struct Input_KeyEvent Input_KeyEvent;
/**
* @brief 鼠标事件对象，用于表示用户鼠标操作产生的输入事件，包含点击信息、坐标、点击动作事件等信息，可用于处理鼠标事件输入和实现鼠标事件响应的功能。
*
* @since 12
*/
typedef struct Input_MouseEvent Input_MouseEvent;
/**
* @brief 触屏输入事件对象，用于表示触屏输入的详细信息，包括触摸点位置、触摸状态、时间戳等。
*
* @since 12
*/
typedef struct Input_TouchEvent Input_TouchEvent;
/**
* @brief 轴事件对象。用于表示输入设备的轴事件数据，如游戏手柄的摇杆移动、鼠标滚轮滚动等场景。开发者可以通过轴事件获取输入设备的轴值变化，实现精细的输入控制，提升用户交互体验。
*
* @since 12
*/
typedef struct Input_AxisEvent Input_AxisEvent;
/**
* @brief 定义快捷键结构体，用于描述快捷键的按键组合、触发条件和回调处理等设计逻辑，支持应用注册和管理自定义快捷键。
*
* @since 14
*/
typedef struct Input_Hotkey Input_Hotkey;
/**
* @brief 定义鼠标光标信息，用于在输入系统中管理和控制鼠标光标的显示行为和外观属性。包括光标显示状态、光标样式、光标大小档位、光标颜色。
*
* @since 22
*/
typedef struct Input_CursorInfo Input_CursorInfo;

/**
* @brief 返回值枚举值。
*
* @since 12
*/
typedef enum Input_Result {
    /**
* 操作成功。
*/
    INPUT_SUCCESS = 0,

    /**
* 权限验证失败。
*/
    INPUT_PERMISSION_DENIED = 201,

    /**
* 非系统应用。
*/
    INPUT_NOT_SYSTEM_APPLICATION = 202,

    /**
* 参数检查失败。
*/
    INPUT_PARAMETER_ERROR = 401,

    /**
* 表示不支持该功能。
*/
    INPUT_DEVICE_NOT_SUPPORTED = 801,

    /**
* 服务异常。
*/
    INPUT_SERVICE_EXCEPTION = 3800001,

    /**
* 应用创建拦截后，再次执行创建拦截的操作。
*/
    INPUT_REPEAT_INTERCEPTOR = 4200001,
    /**
* 已经被系统应用占用。。
* @since 14
*/
    INPUT_OCCUPIED_BY_SYSTEM = 4200002,
    /**
* 已经被其他应用占用。。
* @since 14
*/
    INPUT_OCCUPIED_BY_OTHER = 4200003,
    /**
* 未连接键盘设备。。
* @since 15
*/
    INPUT_KEYBOARD_DEVICE_NOT_EXIST = 3900002,
    /**
* 正在授权中。。
* @since 20
*/
    INPUT_INJECTION_AUTHORIZING = 3900005,
    /**
* 重复请求。。
* @since 20
*/
    INPUT_INJECTION_OPERATION_FREQUENT = 3900006,
    /**
* 当前应用已经授权。。
* @since 20
*/
    INPUT_INJECTION_AUTHORIZED = 3900007,
    /**
* 其它应用已经授权。。
* @since 20
*/
    INPUT_INJECTION_AUTHORIZED_OTHERS = 3900008,
    /**
* 当前应用不是焦点应用。。
* @since 20
*/
    INPUT_APP_NOT_FOCUSED = 3900009,
    /**
* 无鼠标类输入外设。。
* @since 20
*/
    INPUT_DEVICE_NO_POINTER = 3900010,
    /**
* 无效的窗口ID。。
* @since 22
*/
    INPUT_INVALID_WINDOWID = 26500001
} Input_Result;

/**
* @brief 输入设备的触屏事件工具类型。
*
* @since 24
*/
typedef enum Input_TouchEventToolType {
    /**
* 表示手指。
* @since 24
*/
    TOOL_TYPE_FINGER = 0,

    /**
* 表示手写笔设备。
* @since 24
*/
    TOOL_TYPE_PEN = 1,

    /**
* 表示橡皮檫类设备。
* @since 24
*/
    TOOL_TYPE_RUBBER = 2,

    /**
* 表示画笔类设备。
* @since 24
*/
    TOOL_TYPE_BRUSH = 3,

    /**
* 表示铅笔类设备。
* @since 24
*/
    TOOL_TYPE_PENCIL = 4,

    /**
* 表示喷枪类设备。
* @since 24
*/
    TOOL_TYPE_AIRBRUSH = 5,

    /**
* 表示鼠标设备。
* @since 24
*/
    TOOL_TYPE_MOUSE = 6,

    /**
 * 透镜
 * @since 24
 */
    TOOL_TYPE_LENS = 7
} Input_TouchEventToolType;

/**
* @brief 回调函数，用于回调快捷键事件。
*
* @since 14
*/
typedef void (*Input_HotkeyCallback)(Input_Hotkey* hotkey);

/**
* @brief 输入设备信息，用于描述输入设备的基本信息和能力特征，包括设备类型、设备ID等属性。开发者可以通过此结构体获取和管理输入设备的详细信息，便于设备识别和配置管理。
*
* @since 13
*/
typedef struct Input_DeviceInfo Input_DeviceInfo;

/**
* @brief 自定义鼠标光标像素图资源。
*
* @since 22
*/
typedef struct Input_CustomCursor Input_CustomCursor;
/**
* @brief 自定义鼠标光标配置，用于定义和管理应用程序中鼠标光标的显示样式和交互行为。支持设置不同类型的光标样式（如默认、手形、文本输入等），为用户提供更直观的操作反馈，提升用户体验。
*
* @since 22
*/
typedef struct Input_CursorConfig Input_CursorConfig;
/**
* @brief 按键事件的回调函数，keyEvent的生命周期为回调函数内。
*
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @since 12
*/
typedef void (*Input_KeyEventCallback)(const Input_KeyEvent* keyEvent);

/**
* @brief 鼠标事件的回调函数，mouseEvent的生命周期为回调函数内。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @since 12
*/
typedef void (*Input_MouseEventCallback)(const Input_MouseEvent* mouseEvent);
/**
* @brief 触屏输入事件的回调函数，touchEvent的生命周期为回调函数内。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @since 12
*/
typedef void (*Input_TouchEventCallback)(const Input_TouchEvent* touchEvent);
/**
* @brief 轴事件的回调函数，axisEvent的生命周期为回调函数内。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @since 12
*/
typedef void (*Input_AxisEventCallback)(const Input_AxisEvent* axisEvent);
/**
* @brief 回调函数，用于接收输入设备的热插事件。
*
* @param deviceId 输入设备的唯一标识，同一个物理设备反复插拔或重启，设备ID可能会发生变化。
* @since 13
*/
typedef void (*Input_DeviceAddedCallback)(int32_t deviceId);
/**
* @brief 回调函数，用于接收输入设备的热拔事件。
*
* @param deviceId 输入设备的唯一标识，同一个物理设备反复插拔或重启，设备ID可能会发生变化。
* @since 13
*/
typedef void (*Input_DeviceRemovedCallback)(int32_t deviceId);
/**
* @brief 回调函数，用于获取注入权限状态。
*
* @param authorizedStatus 注入权限状态。
* @since 20
*/
typedef void (*Input_InjectAuthorizeCallback)(Input_InjectionStatus authorizedStatus);

/**
* @brief Defines the structure for the interceptor of event callbacks,
* including mouseCallback, touchCallback, and axisCallback.
* @since 12
*/
typedef struct Input_InterceptorEventCallback {
    /** Defines a lifecycle callback for **mouseEvent**. */
    Input_MouseEventCallback mouseCallback;
    /** Defines a lifecycle callback for **touchEvent**. */
    Input_TouchEventCallback touchCallback;
    /** Defines a lifecycle callback for **axisEvent**. */
    Input_AxisEventCallback axisCallback;
} Input_InterceptorEventCallback;

/**
* @brief Defines the struct for listening for device hot swapping. It is applicable to applications that need to
* respond to input device connection and disconnection in real time, such as games and music players. By listening for
* device hot swapping events, applications can update the input status in a timely manner, improving user experience
* and avoiding exceptions caused by device disconnection.
*
* @since 13
*/
typedef struct Input_DeviceListener {
    /** Callback for device addition events */
    Input_DeviceAddedCallback deviceAddedCallback;

    /** Callback for device removal events */
    Input_DeviceRemovedCallback deviceRemovedCallback;
} Input_DeviceListener;

/**
* @brief 事件拦截选项，用于配置输入事件拦截的参数和规则，支持按键事件、鼠标事件、触屏事件和轴事件的拦截控制。
*
* @since 12
*/
typedef struct Input_InterceptorOptions Input_InterceptorOptions;

/**
* @brief 查询按键状态的枚举对象。
*
* @param keyState 按键状态的枚举对象，具体请参考{@link Input_KeyStateAction}。
* @return 操作成功返回{@link INPUT_SUCCESS}；参数校验失败返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_GetKeyState(struct Input_KeyState* keyState);

/**
* @brief 创建按键状态的枚举对象。通过调用{@link OH_Input_DestroyKeyState}销毁按键状态的枚举对象。
*
* @return 操作成功返回一个{@link Input_KeyState}指针对象；否则返回空指针。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
struct Input_KeyState* OH_Input_CreateKeyState();

/**
* @brief 销毁按键状态的枚举对象。
*
* @param keyState 按键状态的枚举对象，具体请参考{@link Input_KeyStateAction}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_DestroyKeyState(struct Input_KeyState** keyState);

/**
* @brief 设置按键状态对象的键值。
*
* @param keyState 按键状态的枚举对象，具体请参考{@link Input_KeyStateAction}。
* @param keyCode 按键键值，具体请参考{@link KeyCode}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetKeyCode(struct Input_KeyState* keyState, int32_t keyCode);

/**
* @brief 获取按键状态对象的键值。
*
* @param keyState 按键状态的枚举对象，具体请参考{@link Input_KeyStateAction}。
* @return 返回按键状态对象的键值。相关取值可参考{@link Input_KeyStateAction}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetKeyCode(const struct Input_KeyState* keyState);

/**
* @brief 设置按键状态对象的按键是否按下。
*
* @param keyState 按键状态的枚举对象，具体请参考{@link Input_KeyStateAction}。
* @param keyAction 按键是否按下，具体请参考{@link Input_KeyEventAction}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetKeyPressed(struct Input_KeyState* keyState, int32_t keyAction);

/**
* @brief 获取按键状态对象的按键是否按下。
*
* @param keyState 按键状态的枚举对象，具体请参考{@link Input_KeyStateAction}。
* @return 返回按键状态对象的按键按下状态。相关取值可参考{@link Input_KeyStateAction}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetKeyPressed(const struct Input_KeyState* keyState);

/**
* @brief 设置按键状态对象的按键开关。
*
* @param keyState 按键状态的枚举对象，具体请参考{@link Input_KeyStateAction}。
* @param keySwitch 按键开关。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetKeySwitch(struct Input_KeyState* keyState, int32_t keySwitch);

/**
* @brief 注入按键事件。
* <br>如果当前处于用户未授权状态，且调用方未持有ohos.permission.CONTROL_DEVICE权限，调用该接口注入事件不生效。
* <br>从API version 20开始，建议先使用{@link OH_Input_RequestInjection}请求授权。然后通过{@link OH_Input_QueryAuthorizedStatus}查询授权状态，
* 当授权状态为{@link AUTHORIZED}时，再使用该接口。
* <br>从API version 22开始，如果注入了修饰键（KEYCODE_META_LEFT、KEYCODE_META_RIGHT、KEYCODE_CTRL_LEFT、KEYCODE_CTRL_RIGHT、
* KEYCODE_ALT_LEFT、KEYCODE_ALT_RIGHT、KEYCODE_SHIFT_LEFT、KEYCODE_SHIFT_RIGHT、KEYCODE_CAPS_LOCK、KEYCODE_SCROLL_LOCK、
* KEYCODE_NUM_LOCK）的按压事件（KEY_ACTION_DOWN）时，请及时注入该按键的抬起事件（KEY_ACTION_UP），以避免该按键长时间处于按压状态。
* <br>从API版本26.0.0开始，持有ohos.permission.CONTROL_DEVICE权限的调用方也可以直接使用本接口。
*
* @permission ohos.permission.CONTROL_DEVICE
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。并通过{@link OH_Input_SetKeyEventKeyCode}、
*     {@link OH_Input_SetKeyEventAction}接口可以设置按键事件的键值和按键事件的类型。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @return OH_Input_InjectKeyEvent 函数返回值。
*     <br>若注入成功，返回{@link INPUT_SUCCESS}；
*     <br>若缺少权限，返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若参数错误，返回{@link INPUT_PARAMETER_ERROR}。
* @since 12
*/
int32_t OH_Input_InjectKeyEvent(const struct Input_KeyEvent* keyEvent);

/**
* @brief 获取按键状态对象的按键开关。
*
* @param keyState 按键状态的枚举对象，具体请参考{@link Input_KeyStateAction}。
* @return 返回按键状态对象的按键开关。相关取值可参考{@link Input_KeyStateAction}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetKeySwitch(const struct Input_KeyState* keyState);

/**
* @brief 创建按键事件对象。通过调用{@link OH_Input_DestroyKeyEvent}销毁按键事件对象。
*
* @return 如果操作成功返回一个{@link Input_KeyEvent}指针对象，否则返回空指针。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
struct Input_KeyEvent* OH_Input_CreateKeyEvent();

/**
* @brief 销毁按键事件对象。
*
* @param keyEvent 按键事件对象。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_DestroyKeyEvent(struct Input_KeyEvent** keyEvent);
/**
* @brief 设置按键事件类型。
*
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @param action 按键事件类型。相关取值可参考{@link Input_KeyEventAction}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetKeyEventAction(struct Input_KeyEvent* keyEvent, int32_t action);
/**
* @brief 获取按键事件类型。
*
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @return 返回按键事件类型。相关取值可参考{@link Input_KeyEventAction}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetKeyEventAction(const struct Input_KeyEvent* keyEvent);
/**
* @brief 设置按键事件的键值。
*
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @param keyCode 按键键值，具体请参考{@link KeyCode}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetKeyEventKeyCode(struct Input_KeyEvent* keyEvent, int32_t keyCode);
/**
* @brief 获取按键事件的键值。
*
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @return 返回按键事件的键值。相关取值可参考{@link Input_KeyCode}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetKeyEventKeyCode(const struct Input_KeyEvent* keyEvent);
/**
* @brief 设置按键事件发生的时间。
*
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @param actionTime 按键事件发生的时间，表示系统启动运行至今逝去的微秒数，单位为微秒（μs）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetKeyEventActionTime(struct Input_KeyEvent* keyEvent, int64_t actionTime);
/**
* @brief 获取按键事件发生的时间。
*
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @return 返回按键事件发生的时间，表示系统启动运行至今逝去的微秒数，单位为微秒（μs）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int64_t OH_Input_GetKeyEventActionTime(const struct Input_KeyEvent* keyEvent);
/**
* @brief 设置按键事件的窗口ID。
*
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @param windowId 按键事件对应的窗口ID。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
void OH_Input_SetKeyEventWindowId(struct Input_KeyEvent* keyEvent, int32_t windowId);
/**
* @brief 获取按键事件的窗口ID。
*
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @return 按键事件的窗口ID。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
int32_t OH_Input_GetKeyEventWindowId(const struct Input_KeyEvent* keyEvent);
/**
* @brief 设置按键事件的屏幕ID。
*
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @param displayId 按键事件对应的屏幕ID。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
void OH_Input_SetKeyEventDisplayId(struct Input_KeyEvent* keyEvent, int32_t displayId);
/**
* @brief 获取按键事件的屏幕ID。
*
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @return 按键事件的屏幕ID。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
int32_t OH_Input_GetKeyEventDisplayId(const struct Input_KeyEvent* keyEvent);

/**
* @brief 获取按键事件的ID。
*
* @param keyEvent 按键事件对象，通过{@link OH_Input_CreateKeyEvent}接口可以创建按键事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyKeyEvent}接口销毁按键事件对象。
* @param eventId 按键事件的ID。
* @return OH_Input_GetKeyEventId 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
* @since 21
*/
Input_Result OH_Input_GetKeyEventId(const struct Input_KeyEvent* keyEvent, int32_t* eventId);

/**
* @brief 添加一个按键事件拦截钩子函数。
* <br>添加后可以通过{@link OH_Input_RemoveKeyEventHook}接口移除。一个进程仅支持设置一个钩子，一个应用支持多个钩子函数，后添加的生效优先级更高。
*
* @permission ohos.permission.HOOK_KEY_EVENT
* @param callback 钩子函数，用于拦截待分发的所有按键事件。
* @return OH_Input_AddKeyEventHook 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
*     <br>{@link INPUT_DEVICE_NOT_SUPPORTED} 表示不支持该功能。
*     <br>{@link INPUT_PERMISSION_DENIED} 表示权限验证失败。
*     <br>{@link INPUT_REPEAT_INTERCEPTOR} 表示重复设置钩子。一个进程仅支持设置一个钩子。
*     <br>{@link INPUT_SERVICE_EXCEPTION} 表示服务异常，请重试。
* @since 21
*/
Input_Result OH_Input_AddKeyEventHook(Input_KeyEventCallback callback);

/**
* @brief 移除按键事件拦截钩子函数。
* <br>通常与{@link OH_Input_AddKeyEventHook}接口配合使用。
*
* @param callback 钩子函数，用于拦截待分发的所有按键事件。
* @return OH_Input_RemoveKeyEventHook 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。如果之前没有添加对应钩子，移除时也会返回成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
*     <br>{@link INPUT_SERVICE_EXCEPTION} 表示服务异常，请重试。
* @since 21
*/
Input_Result OH_Input_RemoveKeyEventHook(Input_KeyEventCallback callback);

/**
* @brief 重新分发按键事件。
* <br>只有被钩子拦截的按键事件才能被重新分发，重新分发的事件必须保持原有优先级顺序。
* <br>调用该接口后，按键事件可在3秒内重新分发。如果超过3秒，将返回{@link INPUT_PARAMETER_ERROR}。
* <br>重新分发的事件需要保证配对关系。如果重新分发了一个或多个按键按下事件{@link KEY_ACTION_DOWN}，再重新分发按键抬起事件{@link KEY_ACTION_UP}或按键动作取消事件
* {@link KEY_ACTION_CANCEL}可以成功。
* <br>如果仅分发{@link KEY_ACTION_UP}或{@link KEY_ACTION_CANCEL}按键事件，接口可以调用成功，但不会执行实际的分发动作。
* <br>如果分发的事件未被钩子拦截，函数调用会成功，但不会执行实际的分发动作。
*
* @param eventId 按键事件的ID。可以通过{@link OH_Input_GetKeyEventId}接口获取。
* @return OH_Input_DispatchToNextHandler 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。可通过{@link OH_Input_GetKeyEventId}查看传入的eventId是否准确。
*     <br>{@link INPUT_SERVICE_EXCEPTION} 表示服务异常，请重试。
* @since 21
*/
Input_Result OH_Input_DispatchToNextHandler(int32_t eventId);

/**
* @brief 使用以指定屏幕左上角为原点的相对坐标系的坐标注入鼠标事件。
* <br>如果当前处于用户未授权状态，且调用方未持有ohos.permission.CONTROL_DEVICE权限，调用该接口注入事件不生效。
* <br>从API version 20开始，建议先使用{@link OH_Input_RequestInjection}请求授权。然后通过{@link OH_Input_QueryAuthorizedStatus}查询授权状态，
* 当授权状态为{@link AUTHORIZED}时，再使用该接口。
* <br>从API版本26.0.0开始，持有ohos.permission.CONTROL_DEVICE权限的调用方也可以直接使用本接口。
*
* @permission ohos.permission.CONTROL_DEVICE
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return OH_Input_InjectMouseEvent 函数返回值。
*     <br>{@link INPUT_SUCCESS} 表示注入成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数错误。
*     <br>{@link INPUT_PERMISSION_DENIED} 表示缺少权限。
* @since 12
*/
int32_t OH_Input_InjectMouseEvent(const struct Input_MouseEvent* mouseEvent);

/**
* @brief 使用以主屏左上角为原点的全局坐标系的坐标注入鼠标事件。
* <br>如果当前处于用户未授权状态，且调用方未持有ohos.permission.CONTROL_DEVICE权限，调用该接口注入事件不生效。
* <br>从API version 20开始，建议先使用{@link OH_Input_RequestInjection}请求授权。然后通过{@link OH_Input_QueryAuthorizedStatus}查询授权状态，
* 当授权状态为{@link AUTHORIZED}时，再使用该接口。
* <br>从API版本26.0.0开始，持有ohos.permission.CONTROL_DEVICE权限的调用方也可以直接使用本接口。
*
* @permission ohos.permission.CONTROL_DEVICE
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return OH_Input_InjectMouseEventGlobal 函数返回值。
*     <br>{@link INPUT_SUCCESS} 表示注入成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数错误。
*     <br>{@link INPUT_PERMISSION_DENIED} 表示缺少权限。
* @since 20
*/
int32_t OH_Input_InjectMouseEventGlobal(const struct Input_MouseEvent* mouseEvent);

/**
* @brief 创建鼠标事件对象。通过调用{@link OH_Input_DestroyMouseEvent}销毁鼠标事件对象。
*
* @return 如果操作成功返回一个{@link Input_MouseEvent}指针对象，否则返回空指针。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
struct Input_MouseEvent* OH_Input_CreateMouseEvent();

/**
* @brief 销毁鼠标事件对象。
*
* @param mouseEvent 鼠标事件对象。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_DestroyMouseEvent(struct Input_MouseEvent** mouseEvent);
/**
* @brief 设置鼠标事件的动作。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @param action 鼠标的动作。相关取值可参考{@link Input_MouseEventAction}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetMouseEventAction(struct Input_MouseEvent* mouseEvent, int32_t action);
/**
* @brief 获取鼠标事件的动作。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return 鼠标的动作。相关取值可参考{@link Input_MouseEventAction}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetMouseEventAction(const struct Input_MouseEvent* mouseEvent);

/**
* @brief 设置鼠标事件以指定屏幕左上角为原点的相对坐标系的X坐标。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @param displayX 鼠标事件以指定屏幕左上角为原点的相对坐标系的X坐标，单位为像素（px）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetMouseEventDisplayX(struct Input_MouseEvent* mouseEvent, int32_t displayX);

/**
* @brief 获取鼠标事件以指定屏幕左上角为原点的相对坐标系的X坐标。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return 鼠标事件以指定屏幕左上角为原点的相对坐标系的X坐标，单位为像素（px）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetMouseEventDisplayX(const struct Input_MouseEvent* mouseEvent);

/**
* @brief 设置鼠标事件以指定屏幕左上角为原点的相对坐标系的Y坐标。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @param displayY 鼠标事件以指定屏幕左上角为原点的相对坐标系的Y坐标，单位为像素（px）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetMouseEventDisplayY(struct Input_MouseEvent* mouseEvent, int32_t displayY);

/**
* @brief 获取鼠标事件以指定屏幕左上角为原点的相对坐标系的Y坐标。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return 鼠标事件以指定屏幕左上角为原点的相对坐标系的Y坐标，单位为像素（px）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetMouseEventDisplayY(const struct Input_MouseEvent* mouseEvent);
/**
* @brief 设置鼠标事件的按键。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @param button 鼠标按键。相关取值可参考{@link Input_MouseEventButton}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetMouseEventButton(struct Input_MouseEvent* mouseEvent, int32_t button);
/**
* @brief 获取鼠标事件的按键。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return 鼠标按键。相关取值可参考{@link Input_MouseEventButton}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetMouseEventButton(const struct Input_MouseEvent* mouseEvent);

/**
* @brief 设置鼠标轴事件的类型。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @param axisType 鼠标轴类型，比如垂直轴、水平轴。相关取值可参考{@link InputEvent_MouseAxis}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetMouseEventAxisType(struct Input_MouseEvent* mouseEvent, int32_t axisType);
/**
* @brief 获取鼠标轴事件的类型。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return 鼠标轴类型。相关取值可参考{@link InputEvent_MouseAxis}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetMouseEventAxisType(const struct Input_MouseEvent* mouseEvent);
/**
* @brief 设置鼠标轴事件的值。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @param axisValue 轴事件的值，正数向前滚动（例如，1.0表示向前滚动一个单位），负数向后滚动（例如，-1.0表示向后滚动一个单位）,零表示没有滚动。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetMouseEventAxisValue(struct Input_MouseEvent* mouseEvent, float axisValue);
/**
* @brief 获取鼠标轴事件的值。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return 轴事件的值。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
float OH_Input_GetMouseEventAxisValue(const struct Input_MouseEvent* mouseEvent);

/**
* @brief 设置鼠标事件发生的时间。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @param actionTime 鼠标事件发生的时间，表示系统启动运行至今逝去的微秒数，单位为微秒（μs）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetMouseEventActionTime(struct Input_MouseEvent* mouseEvent, int64_t actionTime);

/**
* @brief 获取鼠标事件发生的时间。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return 返回鼠标事件发生的时间，表示系统启动运行至今逝去的微秒数，单位为微秒（μs）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int64_t OH_Input_GetMouseEventActionTime(const struct Input_MouseEvent* mouseEvent);
/**
* @brief 设置鼠标事件的窗口ID。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @param windowId 鼠标事件的窗口ID。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
void OH_Input_SetMouseEventWindowId(struct Input_MouseEvent* mouseEvent, int32_t windowId);
/**
* @brief 获取鼠标事件的窗口ID。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return 鼠标事件的窗口ID。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
int32_t OH_Input_GetMouseEventWindowId(const struct Input_MouseEvent* mouseEvent);
/**
* @brief 设置鼠标事件的屏幕ID。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @param displayId 鼠标事件的屏幕ID。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
void OH_Input_SetMouseEventDisplayId(struct Input_MouseEvent* mouseEvent, int32_t displayId);
/**
* @brief 获取鼠标事件的屏幕ID。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return 若获取鼠标事件的屏幕ID成功，则返回鼠标事件的屏幕ID；若mouseEvent为NULL，则返回-1。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
int32_t OH_Input_GetMouseEventDisplayId(const struct Input_MouseEvent* mouseEvent);

/**
* @brief 设置鼠标事件以主屏左上角为原点的全局坐标系的X坐标。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @param globalX 鼠标事件以主屏左上角为原点的全局坐标系的X坐标，单位为像素（px）。
* @since 20
*/
void OH_Input_SetMouseEventGlobalX(struct Input_MouseEvent* mouseEvent, int32_t globalX);

/**
* @brief 获取鼠标事件以主屏左上角为原点的全局坐标系的X坐标。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return 鼠标事件以主屏左上角为原点的全局坐标系的X坐标，单位为像素（px）。
* @since 20
*/
int32_t OH_Input_GetMouseEventGlobalX(const struct Input_MouseEvent* mouseEvent);

/**
* @brief 设置鼠标事件以主屏左上角为原点的全局坐标系的Y坐标。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @param globalY 鼠标事件以主屏左上角为原点的全局坐标系的Y坐标，单位为像素（px）。
* @since 20
*/
void OH_Input_SetMouseEventGlobalY(struct Input_MouseEvent* mouseEvent, int32_t globalY);

/**
* @brief 获取鼠标事件以主屏左上角为原点的全局坐标系的Y坐标。
*
* @param mouseEvent 鼠标事件对象，通过{@link OH_Input_CreateMouseEvent}接口可以创建鼠标事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyMouseEvent}接口销毁鼠标事件对象。
* @return 鼠标事件以主屏左上角为原点的全局坐标系的Y坐标，单位为像素（px）。
* @since 20
*/
int32_t OH_Input_GetMouseEventGlobalY(const struct Input_MouseEvent* mouseEvent);

/**
* @brief 使用以指定屏幕左上角为原点的相对坐标系的坐标注入触屏输入事件。
* <br>如果当前处于用户未授权状态，且调用方未持有ohos.permission.CONTROL_DEVICE权限，调用该接口注入事件不生效。
* <br>从API version 20开始，建议先使用{@link OH_Input_RequestInjection}请求授权。然后通过{@link OH_Input_QueryAuthorizedStatus}查询授权状态，
* 当授权状态为{@link AUTHORIZED}时，再使用该接口。
* <br>从API版本26.0.0开始，持有ohos.permission.CONTROL_DEVICE权限的调用方也可以直接使用本接口。
*
* @permission ohos.permission.CONTROL_DEVICE
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return OH_Input_InjectTouchEvent 函数返回值。
*     <br>{@link INPUT_SUCCESS} 表示注入成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数错误。
* @since 12
*/
int32_t OH_Input_InjectTouchEvent(const struct Input_TouchEvent* touchEvent);

/**
* @brief 使用以主屏左上角为原点的全局坐标系的坐标注入触屏输入事件。
* <br>如果当前未获得事件注入授权，且调用方未持有ohos.permission.CONTROL_DEVICE权限，调用该接口注入事件不生效。
* <br>从API version 20开始，建议先使用{@link OH_Input_RequestInjection}请求授权。然后通过{@link OH_Input_QueryAuthorizedStatus}查询授权状态，
* 当授权状态为{@link AUTHORIZED}时，再使用该接口。
* <br>从API版本26.0.0开始，持有ohos.permission.CONTROL_DEVICE权限的调用方也可以直接使用本接口。
*
* @permission ohos.permission.CONTROL_DEVICE
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return OH_Input_InjectTouchEventGlobal 函数返回值。
*     <br>{@link INPUT_SUCCESS} 表示注入成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数错误。
*     <br>{@link INPUT_PERMISSION_DENIED} 表示缺少权限。
* @since 20
*/
int32_t OH_Input_InjectTouchEventGlobal(const struct Input_TouchEvent* touchEvent);

/**
* @brief 创建触屏输入事件对象。通过调用{@link OH_Input_DestroyTouchEvent}销毁触屏输入事件对象。
*
* @return 如果操作成功返回一个{@link Input_TouchEvent}指针对象，否则返回空指针。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
struct Input_TouchEvent* OH_Input_CreateTouchEvent();

/**
* @brief 销毁触屏输入事件对象。
*
* @param touchEvent 触屏输入事件对象。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_DestroyTouchEvent(struct Input_TouchEvent** touchEvent);
/**
* @brief 设置触屏输入事件的动作。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param action 触屏的动作。相关取值可参考{@link Input_TouchEventAction}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetTouchEventAction(struct Input_TouchEvent* touchEvent, int32_t action);
/**
* @brief 获取触屏输入事件的动作。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 触屏的动作。相关取值可参考{@link Input_TouchEventAction}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetTouchEventAction(const struct Input_TouchEvent* touchEvent);
/**
* @brief 设置触屏输入事件的手指ID。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param id 触屏的手指ID。第一个手指碰到屏幕，ID就是0，第二个手指碰到屏幕，ID就是1，依次累加。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetTouchEventFingerId(struct Input_TouchEvent* touchEvent, int32_t id);
/**
* @brief 获取触屏输入事件的手指ID。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 触屏的手指ID。第一个手指碰到屏幕，ID就是0，第二个手指碰到屏幕，ID就是1，依次累加。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetTouchEventFingerId(const struct Input_TouchEvent* touchEvent);

/**
* @brief 设置触屏输入事件以指定屏幕左上角为原点的相对坐标系的X坐标。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param displayX 触屏输入事件以指定屏幕左上角为原点的相对坐标系的X坐标，单位为像素（px）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetTouchEventDisplayX(struct Input_TouchEvent* touchEvent, int32_t displayX);

/**
* @brief 获取触屏输入事件以指定屏幕左上角为原点的相对坐标系的X坐标。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 触屏输入事件以指定屏幕左上角为原点的相对坐标系的X坐标，单位为像素（px）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetTouchEventDisplayX(const struct Input_TouchEvent* touchEvent);

/**
* @brief 设置触屏输入事件以指定屏幕左上角为原点的相对坐标系的Y坐标。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param displayY 触屏输入事件以指定屏幕左上角为原点的相对坐标系的Y坐标，单位为像素（px）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetTouchEventDisplayY(struct Input_TouchEvent* touchEvent, int32_t displayY);

/**
* @brief 获取触屏输入事件以指定屏幕左上角为原点的相对坐标系的Y坐标。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 触屏输入事件以指定屏幕左上角为原点的相对坐标系的Y坐标，单位为像素（px）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int32_t OH_Input_GetTouchEventDisplayY(const struct Input_TouchEvent* touchEvent);
/**
* @brief 设置触屏输入事件发生的时间。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param actionTime 触屏输入事件发生的时间，表示系统启动运行至今逝去的微秒数，单位为微秒（μs）。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_SetTouchEventActionTime(struct Input_TouchEvent* touchEvent, int64_t actionTime);
/**
* @brief 获取触屏输入事件发生的时间。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 返回触屏输入事件发生的时间。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
int64_t OH_Input_GetTouchEventActionTime(const struct Input_TouchEvent* touchEvent);
/**
* @brief 设置触屏输入事件的窗口ID。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param windowId 触屏输入事件的窗口ID。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
void OH_Input_SetTouchEventWindowId(struct Input_TouchEvent* touchEvent, int32_t windowId);
/**
* @brief 获取触屏输入事件的窗口ID。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 触屏输入事件的窗口ID。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
int32_t OH_Input_GetTouchEventWindowId(const struct Input_TouchEvent* touchEvent);
/**
* @brief 设置触屏输入事件的屏幕ID。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param displayId 触屏输入事件的屏幕ID。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
void OH_Input_SetTouchEventDisplayId(struct Input_TouchEvent* touchEvent, int32_t displayId);
/**
* @brief 获取触屏输入事件的屏幕ID。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 触屏输入事件的屏幕ID。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
int32_t OH_Input_GetTouchEventDisplayId(const struct Input_TouchEvent* touchEvent);

/**
* @brief 设置触屏输入事件以主屏左上角为原点的全局坐标系的X坐标。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param globalX 触屏输入事件以主屏左上角为原点的全局坐标系的X坐标，单位为像素（px）。
* @since 20
*/
void OH_Input_SetTouchEventGlobalX(struct Input_TouchEvent* touchEvent, int32_t globalX);

/**
* @brief 获取触屏输入事件以主屏左上角为原点的全局坐标系的X坐标。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 触屏输入事件以主屏左上角为原点的全局坐标系的X坐标，单位为像素（px）。
* @since 20
*/
int32_t OH_Input_GetTouchEventGlobalX(const struct Input_TouchEvent* touchEvent);

/**
* @brief 设置触屏输入事件以主屏左上角为原点的全局坐标系的Y坐标。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param globalY 触屏输入事件以主屏左上角为原点的全局坐标系的Y坐标，单位为像素（px）。
* @since 20
*/
void OH_Input_SetTouchEventGlobalY(struct Input_TouchEvent* touchEvent, int32_t globalY);

/**
* @brief 获取触屏输入事件以主屏左上角为原点的全局坐标系的Y坐标。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 触屏输入事件以主屏左上角为原点的全局坐标系的Y坐标，单位为像素（px）。
* @since 20
*/
int32_t OH_Input_GetTouchEventGlobalY(const struct Input_TouchEvent* touchEvent);

/**
* @brief 设置触屏输入事件的压力。如果未设置压力值，或者不在合法范围内，默认值是0.0。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param pressure 压力值，范围[0.0, 1.0]，当前触屏可感知的最小压力程度为0.0，最大压力程度为1.0，无单位。
* @return OH_Input_SetTouchEventPressure 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
* @since 24
*/
Input_Result OH_Input_SetTouchEventPressure(struct Input_TouchEvent* touchEvent, double pressure);
/**
* @brief 获取触屏输入事件的压力。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 压力值，无单位。
* @since 24
*/
double OH_Input_GetTouchEventPressure(const struct Input_TouchEvent* touchEvent);

/**
* @brief 设置触屏输入事件以指定窗口左上角为原点的相对坐标系的X坐标。如果未设置，默认值是0。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param windowX 指定窗口左上角为原点的相对坐标系的X坐标，单位为像素（px）。
* @since 24
*/
void OH_Input_SetTouchEventWindowX(struct Input_TouchEvent* touchEvent, int32_t windowX);

/**
* @brief 获取触屏输入事件以指定窗口左上角为原点的相对坐标系的X坐标。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 指定窗口左上角为原点的相对坐标系的X坐标，单位为像素（px）。
* @since 24
*/
int32_t OH_Input_GetTouchEventWindowX(const struct Input_TouchEvent* touchEvent);

/**
* @brief 设置触屏输入事件以指定窗口左上角为原点的相对坐标系的Y坐标。如果未设置，默认值是0。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param windowY 指定窗口左上角为原点的相对坐标系的Y坐标，单位为像素（px）。
* @since 24
*/
void OH_Input_SetTouchEventWindowY(struct Input_TouchEvent* touchEvent, int32_t windowY);

/**
* @brief 获取触屏输入事件以指定窗口左上角为原点的相对坐标系的Y坐标。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 指定窗口左上角为原点的相对坐标系的Y坐标，单位为像素（px）。
* @since 24
*/
int32_t OH_Input_GetTouchEventWindowY(const struct Input_TouchEvent* touchEvent);

/**
* @brief 设置当前触屏事件对应手指/其他触屏外设最近一次按下事件发生的时间。如果未设置，默认值是0。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param downTime 当前触屏事件对应手指/其他触屏外设最近一次按下事件发生的时间，表示系统启动运行至今逝去的微秒数，单位为微秒（μs）。
* @since 24
*/
void OH_Input_SetTouchEventDownTime(struct Input_TouchEvent* touchEvent, int64_t downTime);

/**
* @brief 获取当前触屏事件对应手指/其他触屏外设最近一次按下事件发生的时间。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 当前触屏事件对应手指/其他触屏外设最近一次按下事件发生的时间，表示系统启动运行至今逝去的微秒数，单位为微秒（μs）。
* @since 24
*/
int64_t OH_Input_GetTouchEventDownTime(const struct Input_TouchEvent* touchEvent);

/**
* @brief 设置触屏输入事件的工具类型。如果未设置toolType，默认值是Input_TouchEventToolType.TOOL_TYPE_FINGER。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @param toolType 工具类型。
* @return OH_Input_SetTouchEventToolType 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
* @since 24
*/
Input_Result OH_Input_SetTouchEventToolType(struct Input_TouchEvent* touchEvent, Input_TouchEventToolType toolType);
/**
* @brief 获取触屏输入事件的工具类型。
*
* @param touchEvent 触屏输入事件对象，通过{@link OH_Input_CreateTouchEvent}接口可以创建触屏输入事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyTouchEvent}接口销毁触屏输入事件对象。
* @return 工具类型。
* @since 24
*/
Input_TouchEventToolType OH_Input_GetTouchEventToolType(const struct Input_TouchEvent* touchEvent);

/**
* @brief 当前应用申请注入权限，包括申请注入按键事件{@link OH_Input_InjectKeyEvent}、注入触屏输入事件{@link OH_Input_InjectTouchEvent}、注入鼠标事件
* {@link OH_Input_InjectMouseEvent}等注入操作的权限。
* <br>从API版本26.0.0开始，在已授予ohos.permission.CONTROL_DEVICE权限的情况下，无需再申请注入授权。本接口的行为与ohos.permission.CONTROL_DEVICE权限无关。
*
* @param callback 授权状态回调，具体请参考{@link Input_InjectAuthorizeCallback}。
* @return 函数返回值，参见{@link Input_Result}。
*     <br>INPUT_SUCCESS = 0 申请授权成功，等待用户授权结果并回调授权状态。
*     <br>INPUT_PARAMETER_ERROR = 401  参数错误，参数callback为空。
*     <br>INPUT_DEVICE_NOT_SUPPORTED = 801  表示不支持该功能。
*     <br>INPUT_SERVICE_EXCEPTION = 3800001  服务异常。
*     <br>INPUT_INJECTION_AUTHORIZING =  3900005 正在授权中。
*     <br>INPUT_INJECTION_OPERATION_FREQUENT = 3900006 重复请求（当前应用连续申请授权弹窗成功，间隔时间不超过3秒）。
*     <br>INPUT_INJECTION_AUTHORIZED = 3900007 当前应用已经授权。
*     <br>INPUT_INJECTION_AUTHORIZED_OTHERS = 3900008   其它应用已经授权。
* @since 20
*/
Input_Result OH_Input_RequestInjection(Input_InjectAuthorizeCallback callback);

/**
* @brief 取消事件注入并撤销授权。
*
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
void OH_Input_CancelInjection();

/**
* @brief 查询当前应用注入的权限状态。
* <br>从API版本26.0.0开始，本接口仅返回弹窗授权状态，不表示调用方是否因持有ohos.permission.CONTROL_DEVICE权限而具备注入能力。
*
* @param status 当前应用注入权限状态。参见{@link Input_InjectionStatus}。
* @return 函数返回值，参见{@link Input_Result}。
*     <br>INPUT_SUCCESS = 0 查询成功。
*     <br>INPUT_PARAMETER_ERROR = 401  参数错误，参数status为空。
*     <br>INPUT_SERVICE_EXCEPTION = 3800001  服务异常。
* @since 20
*/
Input_Result OH_Input_QueryAuthorizedStatus(Input_InjectionStatus* status);

/**
* @brief 创建轴事件对象。通过调用{@link OH_Input_DestroyAxisEvent}销毁轴事件对象。
*
* @return 成功返回{@link Input_AxisEvent}对象实例，失败则返回null。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_AxisEvent* OH_Input_CreateAxisEvent(void);

/**
* @brief 销毁轴事件对象。
*
* @param axisEvent 轴事件对象实例的指针。
* @return 若销毁成功，则返回{@link INPUT_SUCCESS}；若axisEvent为NULL或者axisEvent为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_DestroyAxisEvent(Input_AxisEvent** axisEvent);

/**
* @brief 设置轴事件的动作。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param action 轴事件动作，具体请参考{@link InputEvent_AxisAction}。
* @return 若设置轴事件的动作成功，则返回{@link INPUT_SUCCESS}；若axisEvent为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_SetAxisEventAction(Input_AxisEvent* axisEvent, InputEvent_AxisAction action);

/**
* @brief 获取轴事件的动作。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param action action 出参，返回轴事件动作，具体请参考在{@link InputEvent_AxisAction}。
* @return 若获取轴事件的动作成功，则返回{@link INPUT_SUCCESS}；若axisEvent或者action为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_GetAxisEventAction(const Input_AxisEvent* axisEvent, InputEvent_AxisAction *action);

/**
* @brief 设置轴事件以指定屏幕左上角为原点的相对坐标系的X坐标。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param displayX 轴事件以指定屏幕左上角为原点的相对坐标系的X坐标，单位为像素（px）。
* @return 若设置轴事件的X坐标成功，则返回{@link INPUT_SUCCESS}；若axisEvent为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_SetAxisEventDisplayX(Input_AxisEvent* axisEvent, float displayX);

/**
* @brief 获取轴事件以指定屏幕左上角为原点的相对坐标系的X坐标。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param displayX 出参，返回轴事件以指定屏幕左上角为原点的相对坐标系的X坐标，单位为像素（px）。
* @return 若获取轴事件的X坐标成功，则返回{@link INPUT_SUCCESS}；若axisEvent或者displayX为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_GetAxisEventDisplayX(const Input_AxisEvent* axisEvent, float* displayX);

/**
* @brief 设置轴事件以指定屏幕左上角为原点的相对坐标系的Y坐标。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param displayY 轴事件以指定屏幕左上角为原点的相对坐标系的Y坐标，单位为像素（px）。
* @return 若设置轴事件的Y坐标成功，则返回{@link INPUT_SUCCESS}；若axisEvent为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_SetAxisEventDisplayY(Input_AxisEvent* axisEvent, float displayY);

/**
* @brief 获取轴事件以指定屏幕左上角为原点的相对坐标系的Y坐标。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param displayY 出参，返回轴事件以指定屏幕左上角为原点的相对坐标系的Y坐标，单位为像素（px）。
* @return 若获取轴事件的Y坐标成功，则返回{@link INPUT_SUCCESS}；若axisEvent或者displayY为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_GetAxisEventDisplayY(const Input_AxisEvent* axisEvent, float* displayY);

/**
* @brief 设置轴事件指定轴类型的轴值。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param axisType 轴类型，具体请参考{@link InputEvent_AxisType}。
* @param axisValue 轴事件的值，正数向前滚动（例如，1.0表示向前滚动一个单位），负数向后滚动（例如，-1.0表示向后滚动一个单位），零表示没有滚动。
* @return 若设置轴事件指定轴类型的轴值成功，则返回{@link INPUT_SUCCESS}；若axisEvent为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_SetAxisEventAxisValue(Input_AxisEvent* axisEvent,
                                            InputEvent_AxisType axisType, double axisValue);

/**
* @brief 获取轴事件指定轴类型的轴值。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param axisType 轴类型，具体请参考{@link InputEvent_AxisType}。
* @param axisValue 出参，返回轴事件的值，正数向前滚动（例如，1.0表示向前滚动一个单位），负数向后滚动（例如，-1.0表示向后滚动一个单位）,零表示没有滚动。
* @return 若获取轴事件指定轴类型的轴值成功，则返回{@link INPUT_SUCCESS}；若axisEvent或者axisValue为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_GetAxisEventAxisValue(const Input_AxisEvent* axisEvent,
                                            InputEvent_AxisType axisType, double* axisValue);

/**
* @brief 设置轴事件发生的时间。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param actionTime 轴事件发生的时间，表示系统启动运行至今逝去的微秒数，单位为微秒（μs）。
* @return 若设置轴事件发生的时间成功，则返回{@link INPUT_SUCCESS}；若axisEvent为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_SetAxisEventActionTime(Input_AxisEvent* axisEvent, int64_t actionTime);

/**
* @brief 获取轴事件发生的时间。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param actionTime 出参，返回轴事件发生的时间，表示系统启动运行至今逝去的微秒数，单位为微秒（μs）。
* @return 若获取轴事件发生的时间成功，则返回{@link INPUT_SUCCESS}；若axisEvent或者actionTime为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_GetAxisEventActionTime(const Input_AxisEvent* axisEvent, int64_t* actionTime);

/**
* @brief 设置轴事件类型。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param axisEventType 轴事件类型，具体请参考{@link InputEvent_AxisEventType}。
* @return 若设置轴事件类型成功，则返回{@link INPUT_SUCCESS}；若axisEvent为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_SetAxisEventType(Input_AxisEvent* axisEvent, InputEvent_AxisEventType axisEventType);

/**
* @brief 获取轴事件类型。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param axisEventType 出参，返回轴事件类型，具体请参考{@link InputEvent_AxisEventType}。
* @return 若获取轴事件类型成功，则返回{@link INPUT_SUCCESS}；若axisEvent或者axisEventType为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_GetAxisEventType(const Input_AxisEvent* axisEvent, InputEvent_AxisEventType* axisEventType);

/**
* @brief 设置轴事件源类型。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param sourceType 轴事件源类型，具体请参考{@link InputEvent_SourceType}。
* @return 若设置轴事件源类型成功，则返回{@link INPUT_SUCCESS}；若axisEvent为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_SetAxisEventSourceType(Input_AxisEvent* axisEvent, InputEvent_SourceType sourceType);

/**
* @brief 获取轴事件源类型。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param sourceType 出参，返回轴事件源类型，具体请参考{@link InputEvent_SourceType}。
* @return 若获取轴事件源类型成功，则返回{@link INPUT_SUCCESS}；若axisEvent或者sourceType为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_GetAxisEventSourceType(const Input_AxisEvent* axisEvent, InputEvent_SourceType* sourceType);

/**
* @brief 设置轴事件的窗口ID。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param windowId 轴事件窗口ID。
* @return 若设置轴事件的窗口ID成功，则返回{@link INPUT_SUCCESS}；若axisEvent为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
Input_Result OH_Input_SetAxisEventWindowId(Input_AxisEvent* axisEvent, int32_t windowId);

/**
* @brief 获取轴事件的窗口ID。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param windowId 出参，返回轴事件窗口ID。
* @return 若获取轴事件的窗口ID成功，则返回{@link INPUT_SUCCESS}；若axisEvent或者windowId为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
Input_Result OH_Input_GetAxisEventWindowId(const Input_AxisEvent* axisEvent, int32_t* windowId);

/**
* @brief 设置轴事件的屏幕ID。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param displayId 轴事件屏幕ID。
* @return 若设置轴事件的屏幕ID成功，则返回{@link INPUT_SUCCESS}；若axisEvent为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
Input_Result OH_Input_SetAxisEventDisplayId(Input_AxisEvent* axisEvent, int32_t displayId);

/**
* @brief 获取轴事件的屏幕ID。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param displayId 出参，返回轴事件屏幕ID。
* @return 若获取轴事件的屏幕ID成功，则返回{@link INPUT_SUCCESS}；若axisEvent或者displayId为NULL，则返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
Input_Result OH_Input_GetAxisEventDisplayId(const Input_AxisEvent* axisEvent, int32_t* displayId);

/**
* @brief 设置轴事件以主屏左上角为原点的全局坐标系的X坐标。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param globalX 轴事件以主屏左上角为原点的全局坐标系的X坐标，单位为像素（px）。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示axisEvent是空指针。
* @since 20
*/
Input_Result OH_Input_SetAxisEventGlobalX(struct Input_AxisEvent* axisEvent, int32_t globalX);

/**
* @brief 获取轴事件以主屏左上角为原点的全局坐标系的X坐标。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param globalX 轴事件以主屏左上角为原点的全局坐标系的X坐标，单位为像素（px）。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示axisEvent或者globalX是空指针。
* @since 20
*/
Input_Result OH_Input_GetAxisEventGlobalX(const Input_AxisEvent* axisEvent, int32_t* globalX);

/**
* @brief 设置轴事件以主屏左上角为原点的全局坐标系的Y坐标。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param globalY 轴事件以主屏左上角为原点的全局坐标系的Y坐标，单位为像素（px）。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示axisEvent是空指针。
* @since 20
*/
Input_Result OH_Input_SetAxisEventGlobalY(struct Input_AxisEvent* axisEvent, int32_t globalY);

/**
* @brief 获取轴事件以主屏左上角为原点的全局坐标系的Y坐标。
*
* @param axisEvent 轴事件对象，通过{@link OH_Input_CreateAxisEvent}接口可以创建轴事件对象。
*     <br>使用完需使用{@link OH_Input_DestroyAxisEvent}接口销毁轴事件对象。
* @param globalY 轴事件以主屏左上角为原点的全局坐标系的Y坐标，单位为像素（px）。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示axisEvent或者globalY是空指针。
* @since 20
*/
Input_Result OH_Input_GetAxisEventGlobalY(const Input_AxisEvent* axisEvent, int32_t* globalY);

/**
* @brief 添加按键事件监听。重复添加只有第一次生效，后续添加请求将被忽略。
*
* @permission ohos.permission.INPUT_MONITORING
* @param callback 回调函数，用于接收按键事件。
* @return 若添加按键事件监听成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若callback为空，则返回{@link INPUT_PARAMETER_ERROR}；若服务异常，则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_AddKeyEventMonitor(Input_KeyEventCallback callback);

/**
* @brief 添加鼠标事件监听，包含鼠标点击，移动，不包含滚轮事件，滚轮事件归属于轴事件。
* <br>该接口处于录屏场景时才允许调用，否则调用该接口不生效。
*
* @permission ohos.permission.INPUT_MONITORING
* @param callback 回调函数，用于接收鼠标事件。
* @return 若添加鼠标事件监听成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若callback为空，则返回{@link INPUT_PARAMETER_ERROR}；若服务异常，则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_AddMouseEventMonitor(Input_MouseEventCallback callback);

/**
* @brief 添加触屏输入事件监听。
*
* @permission ohos.permission.INPUT_MONITORING
* @param callback 回调函数，用于接收触屏输入事件。
* @return 若添加触屏输入事件监听成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若callback为空，则返回{@link INPUT_PARAMETER_ERROR}；若服务异常，则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_AddTouchEventMonitor(Input_TouchEventCallback callback);

/**
* @brief 添加所有类型轴事件监听，轴事件类型定义在{@link InputEvent_AxisEventType}中。
*
* @permission ohos.permission.INPUT_MONITORING
* @param callback 回调函数，用于接收轴事件。
* @return 若添加轴事件监听成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若callback为空，则返回{@link INPUT_PARAMETER_ERROR}；若服务异常，则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_AddAxisEventMonitorForAll(Input_AxisEventCallback callback);

/**
* @brief 添加指定类型的轴事件监听，轴事件类型定义在{@link InputEvent_AxisEventType}中。
*
* @permission ohos.permission.INPUT_MONITORING
* @param axisEventType 要监听的轴事件类型，轴事件类型定义在{@link InputEvent_AxisEventType}中。
* @param callback 回调函数，用于接收指定类型的轴事件。
* @return 若添加轴事件监听成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若callback为空，则返回{@link INPUT_PARAMETER_ERROR}；若服务异常，则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_AddAxisEventMonitor(InputEvent_AxisEventType axisEventType, Input_AxisEventCallback callback);

/**
* @brief 移除按键事件监听。
*
* @permission ohos.permission.INPUT_MONITORING
* @param callback 指定要被移除的用于按键事件监听的回调函数。
* @return 若移除按键事件监听成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若callback为空或者没有被添加监听，则返回{@link INPUT_PARAMETER_ERROR}；若服务异常，则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_RemoveKeyEventMonitor(Input_KeyEventCallback callback);

/**
* @brief 移除鼠标事件监听。
*
* @permission ohos.permission.INPUT_MONITORING
* @param callback 指定要被移除的用于鼠标事件监听的回调函数。
* @return 若移除鼠标事件监听成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若callback为空或者没有被添加监听，则返回{@link INPUT_PARAMETER_ERROR}；若服务异常，则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_RemoveMouseEventMonitor(Input_MouseEventCallback callback);

/**
* @brief 移除触屏输入事件监听。
*
* @permission ohos.permission.INPUT_MONITORING
* @param callback 指定要被移除的用于触屏输入事件监听的回调函数。
* @return 若移除触屏输入事件监听成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若callback为空或者没有被添加监听，则返回{@link INPUT_PARAMETER_ERROR}；若服务异常，则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_RemoveTouchEventMonitor(Input_TouchEventCallback callback);

/**
* @brief 移除所有类型轴事件监听。
*
* @permission ohos.permission.INPUT_MONITORING
* @param callback 指定要被移除的用于所有类型轴事件监听的回调函数。
* @return 若移除轴事件监听成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若callback为空或者没有被添加监听，则返回{@link INPUT_PARAMETER_ERROR}；若服务异常，则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_RemoveAxisEventMonitorForAll(Input_AxisEventCallback callback);

/**
* @brief 移除指定类型轴事件监听，轴事件类型定义在{@link InputEvent_AxisEventType}中。
*
* @permission ohos.permission.INPUT_MONITORING
* @param axisEventType 指定要移除监听的轴事件类型，轴事件类型定义在{@link InputEvent_AxisEventType}中。
* @param callback 指定要被移除的用于指定类型轴事件监听的回调函数。
* @return 若移除轴事件监听成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若callback为空或者没有被添加监听，则返回{@link INPUT_PARAMETER_ERROR}；若服务异常，则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_RemoveAxisEventMonitor(InputEvent_AxisEventType axisEventType, Input_AxisEventCallback callback);

/**
* @brief 添加按键事件的拦截，重复添加只有第一次生效，后续添加请求返回错误码{@link INPUT_REPEAT_INTERCEPTOR}。仅在应用获焦时拦截按键事件。
*
* @permission ohos.permission.INTERCEPT_INPUT_EVENT
* @param callback 回调函数，用于接收按键事件。
* @param option option 输入事件拦截的可选项，传null则使用默认值。
* @return 若添加按键事件的拦截成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若callback为空，则返回{@link INPUT_PARAMETER_ERROR}；若重复添加拦截器，则返回{@link INPUT_REPEAT_INTERCEPTOR}；
*     <br>若服务异常；则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_AddKeyEventInterceptor(Input_KeyEventCallback callback, Input_InterceptorOptions *option);

/**
* @brief 添加输入事件拦截，包括鼠标、触屏和轴事件。重复添加只有第一次生效，后续添加请求返回错误码{@link INPUT_REPEAT_INTERCEPTOR}。仅命中应用窗口时拦截输入事件。
*
* @permission ohos.permission.INTERCEPT_INPUT_EVENT
* @param callback callback 用于回调输入事件的结构体指针，请参考定义{@link Input_InterceptorEventCallback}。
* @param option option 输入事件拦截的可选项，传null则使用默认值。
* @return 若添加输入事件的拦截成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若callback为空，则返回{@link INPUT_PARAMETER_ERROR}；若重复添加拦截器，则返回{@link INPUT_REPEAT_INTERCEPTOR}；
*     <br>若服务异常；则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_AddInputEventInterceptor(Input_InterceptorEventCallback *callback,
                                               Input_InterceptorOptions *option);

/**
* @brief 移除按键事件拦截。
*
* @permission ohos.permission.INTERCEPT_INPUT_EVENT
* @return 若移除按键事件拦截成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若服务异常，则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_RemoveKeyEventInterceptor(void);

/**
* @brief 移除输入事件拦截，包括鼠标、触屏和轴事件。
*
* @permission ohos.permission.INTERCEPT_INPUT_EVENT
* @return 若移除输入事件拦截成功，则返回{@link INPUT_SUCCESS}；若权限校验失败，则返回{@link INPUT_PERMISSION_DENIED}；
*     <br>若服务异常，则返回{@link INPUT_SERVICE_EXCEPTION}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 12
*/
Input_Result OH_Input_RemoveInputEventInterceptor(void);

/**
* @brief 获取距离上次系统输入事件的时间间隔。
*
* @param timeInterval timeInterval 时间间隔，单位为微秒（μs）。
* @return OH_Input_GetIntervalSinceLastInput 函数返回值。
*     <br>若获取时间间隔成功，则返回{@link INPUT_SUCCESS}；若服务异常，返回{@link INPUT_SERVICE_EXCEPTION}；若参数错误，返回
*     {@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
Input_Result OH_Input_GetIntervalSinceLastInput(int64_t *timeInterval);

/**
* @brief 创建快捷键对象。通过调用{@link OH_Input_DestroyHotkey}销毁快捷键对象。
*
* @return 如果操作成功，则返回一个{@link Input_Hotkey}指针对象。否则，返回一个空指针，可能的原因是内存分配失败。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
Input_Hotkey *OH_Input_CreateHotkey(void);

/**
* @brief 销毁快捷键对象。
*
* @param hotkey hotkey 快捷键对象的实例。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
void OH_Input_DestroyHotkey(Input_Hotkey **hotkey);

/**
* @brief 设置修饰键。
*
* @param hotkey hotkey 快捷键对象的实例。
* @param preKeys preKeys 修饰键列表。
* @param size 修饰键个数， 取值范围1~2个。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
void OH_Input_SetPreKeys(Input_Hotkey *hotkey, int32_t *preKeys, int32_t size);

/**
* @brief 获取修饰键。
*
* @param hotkey hotkey 快捷键对象的实例。
* @param preKeys preKeys 返回修饰键列表。
* @param preKeyCount preKeyCount 返回修饰键个数。
* @return OH_Input_GetPreKeys 函数返回值。
*     <br>若获取成功，返回{@link INPUT_SUCCESS}；若获取失败，返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
Input_Result OH_Input_GetPreKeys(const Input_Hotkey *hotkey, int32_t **preKeys, int32_t *preKeyCount);

/**
* @brief 设置被修饰键。
*
* @param hotkey 快捷键对象的实例。
* @param finalKey 被修饰键值，被修饰键值只能是1个。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
void OH_Input_SetFinalKey(Input_Hotkey *hotkey, int32_t finalKey);

/**
* @brief 获取被修饰键。
*
* @param hotkey 快捷键对象的实例。
* @param finalKeyCode finalKeyCode 返回被修饰键键值。
* @return OH_Input_GetFinalKey 函数返回值。
*     <br>若获取成功，返回{@link INPUT_SUCCESS}；
*     <br>若获取失败，返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
Input_Result OH_Input_GetFinalKey(const Input_Hotkey *hotkey, int32_t *finalKeyCode);

/**
* @brief 创建{@link Input_Hotkey}类型实例的数组。通过调用{@link OH_Input_GetAllSystemHotkeys}获取有效的count参数。通过调用
* {@link OH_Input_DestroyAllSystemHotkeys}销毁{@link Input_Hotkey}实例数组并回收内存。
*
* @param count 创建{@link Input_Hotkey}实例的数量。
* @return OH_Input_CreateAllSystemHotkeys 函数返回值。
*     <br>{@link INPUT_SUCCESS} 创建实例数组的双指针成功。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
Input_Hotkey **OH_Input_CreateAllSystemHotkeys(int32_t count);

/**
* @brief 销毁{@link Input_Hotkey}实例数组并回收内存。
*
* @param hotkeys hotkeys 指向{@link Input_Hotkey}实例数组的双指针。
* @param count 销毁{@link Input_Hotkey}实例的数量。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
void OH_Input_DestroyAllSystemHotkeys(Input_Hotkey **hotkeys, int32_t count);

/**
* @brief 获取设置的所有快捷键。
*
* @param hotkey hotkey 返回{@link Input_Hotkey} 类型实例数组。首次调用可传入NULL，可获取数组长度。
* @param count count 返回支持快捷键的个数。
* @return OH_Input_GetAllSystemHotkeys 函数返回值。
*     <br>若获取成功，返回{@link INPUT_SUCCESS}；
*     <br>若获取失败，返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
Input_Result OH_Input_GetAllSystemHotkeys(Input_Hotkey **hotkey, int32_t *count);

/**
* @brief 设置是否上报重复key事件。
*
* @param hotkey 快捷键对象的实例。
* @param isRepeat 是否上报重复key事件。true表示上报，false表示不上报。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
void OH_Input_SetRepeat(Input_Hotkey* hotkey, bool isRepeat);

/**
* @brief 获取是否上报重复key事件。
*
* @param hotkey 快捷键对象的实例。
* @param isRepeat isRepeat 返回Key事件是否重复。true表示重复，false表示不重复。
* @return OH_Input_GetRepeat 函数返回值。
*     <br>若获取成功，返回{@link INPUT_SUCCESS}；
*     <br>若获取失败，返回{@link INPUT_PARAMETER_ERROR}。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
Input_Result OH_Input_GetRepeat(const Input_Hotkey* hotkey, bool *isRepeat);

/**
* @brief 订阅快捷键事件。
*
* @param hotkey 指定要订阅的快捷键对象。
* @param callback 回调函数，用于回调快捷键事件。
* @return OH_Input_AddHotkeyMonitor 函数返回值。
*     <br>{@link INPUT_SUCCESS} 表示订阅组合按键成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 参数检查失败。
*     <br>{@link INPUT_OCCUPIED_BY_SYSTEM} 该快捷键已被系统占用，可以通过接口{@link OH_Input_GetAllSystemHotkeys}查询所有的系统快捷键。
*     <br>{@link INPUT_OCCUPIED_BY_OTHER} 已被抢占订阅。
*     <br>{@link INPUT_DEVICE_NOT_SUPPORTED} 表示不支持该功能。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
Input_Result OH_Input_AddHotkeyMonitor(const Input_Hotkey* hotkey, Input_HotkeyCallback callback);

/**
* @brief 取消订阅快捷键。
*
* @param hotkey 指定要取消订阅的快捷键对象。
* @param callback 回调函数，用于回调快捷键事件。
* @return OH_Input_RemoveHotkeyMonitor 函数返回值。
*     <br>{@link INPUT_SUCCESS} 取消订阅组合按键成功， {@link INPUT_PARAMETER_ERROR} 参数检查失败。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 14
*/
Input_Result OH_Input_RemoveHotkeyMonitor(const Input_Hotkey* hotkey, Input_HotkeyCallback callback);

/**
* @brief 获取所有输入设备的ID列表。
*
* @param deviceIds deviceIds 保存输入设备ID的列表。
* @param inSize 保存输入设备ID列表的大小。
* @param outSize outSize 输出输入设备ID列表的长度，值小于等于inSize长度。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示deviceIds或outSize为空指针或inSize小于0。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_GetDeviceIds(int32_t *deviceIds, int32_t inSize, int32_t *outSize);

/**
* @brief 获取输入设备信息。
*
* @param deviceId 输入设备的唯一标识，同一个物理设备反复插拔或重启，设备ID可能会发生变化。
* @param deviceInfo deviceInfo 指向输入设备信息{@link Input_DeviceInfo}的指针。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示deviceInfo为空指针或deviceId无效。
*     <br>可以通过 {@link OH_Input_GetDeviceIds} 表示接口查询系统支持的设备ID。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_GetDevice(int32_t deviceId, Input_DeviceInfo **deviceInfo);
/**
* @brief 创建输入设备信息的对象。通过调用{@link OH_Input_DestroyDeviceInfo}销毁输入设备信息的对象。
*
* @return 如果操作成功，返回设备信息{@link Input_DeviceInfo}实例的指针。否则返回空指针，可能的原因是分配内存失败。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_DeviceInfo* OH_Input_CreateDeviceInfo(void);

/**
* @brief 销毁输入设备信息的对象。
*
* @param deviceInfo deviceInfo 设备信息的对象。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
void OH_Input_DestroyDeviceInfo(Input_DeviceInfo **deviceInfo);

/**
* @brief 获取输入设备的键盘类型。
*
* @param deviceId 输入设备的唯一标识，同一个物理设备反复插拔或重启，设备ID可能会发生变化。
* @param keyboardType keyboardType 指向输入设备的键盘指针。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示设备ID为无效值或者keyboardType是空指针。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_GetKeyboardType(int32_t deviceId, int32_t *keyboardType);

/**
* @brief 获取输入设备的ID。
*
* @param deviceInfo deviceInfo 输入设备信息{@link Input_DeviceInfo}。
* @param id id 指向输入设备ID的指针。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示deviceInfo或者ID是空指针。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_GetDeviceId(Input_DeviceInfo *deviceInfo, int32_t *id);

/**
* @brief 获取输入设备的名称。
*
* @param deviceInfo deviceInfo 输入设备信息{@link Input_DeviceInfo}。
* @param name name 指向输入设备名称的指针。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示deviceInfo或者name是空指针。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_GetDeviceName(Input_DeviceInfo *deviceInfo, char **name);

/**
* @brief 获取有关输入设备能力信息，比如设备是触摸屏、触控板、键盘等。
*
* @param deviceInfo deviceInfo 输入设备信息{@link Input_DeviceInfo}。
* @param capabilities capabilities 指向输入设备能力信息的指针。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示deviceInfo或者capabilities是空指针。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_GetCapabilities(Input_DeviceInfo *deviceInfo, int32_t *capabilities);

/**
* @brief 获取输入设备的版本信息。
*
* @param deviceInfo deviceInfo 输入设备信息{@link Input_DeviceInfo}。
* @param version version 指向输入设备版本信息的指针。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示deviceInfo或者version是空指针。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_GetDeviceVersion(Input_DeviceInfo *deviceInfo, int32_t *version);

/**
* @brief 获取输入设备的产品信息。
*
* @param deviceInfo deviceInfo 输入设备信息{@link Input_DeviceInfo}。
* @param product product 指向输入设备产品信息的指针。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示deviceInfo或者product是空指针。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_GetDeviceProduct(Input_DeviceInfo *deviceInfo, int32_t *product);

/**
* @brief 获取输入设备的厂商信息。
*
* @param deviceInfo deviceInfo 输入设备信息{@link Input_DeviceInfo}。
* @param vendor vendor 指向输入设备厂商信息的指针。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示deviceInfo或者vendor是空指针。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_GetDeviceVendor(Input_DeviceInfo *deviceInfo, int32_t *vendor);

/**
* @brief 获取输入设备的物理地址。
*
* @param deviceInfo deviceInfo 输入设备信息{@link Input_DeviceInfo}。
* @param address address 指向输入设备物理地址的指针。
* @return {@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示deviceInfo或者address是空指针。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_GetDeviceAddress(Input_DeviceInfo *deviceInfo, char **address);

/**
* @brief 注册设备热插拔的监听器。
*
* @param listener 指向设备热插拔监听器{@link Input_DeviceListener}的指针。
* @return OH_Input_RegisterDeviceListener 函数返回值。
*     <br>{@link INPUT_SUCCESS} 表示注册成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示listener 为NULL。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_RegisterDeviceListener(Input_DeviceListener* listener);

/**
* @brief 取消注册设备热插拔的监听。
*
* @param listener 指向设备热插拔监听器{@link Input_DeviceListener}的指针。
* @return OH_Input_UnregisterDeviceListener 函数返回值。
*     <br>{@link INPUT_SUCCESS} 表示取消注册成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示listener 为 NULL 或者 listener 未被注册。
*     <br>{@link INPUT_SERVICE_EXCEPTION} 表示由于服务异常调用失败。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_UnregisterDeviceListener(Input_DeviceListener* listener);

/**
* @brief 取消注册所有的设备热插拔的监听。
*
* @return OH_Input_UnregisterDeviceListener 函数返回值。
*     <br>{@link INPUT_SUCCESS} 表示调用成功。
*     <br>{@link INPUT_SERVICE_EXCEPTION} 表示由于服务异常调用失败。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 13
*/
Input_Result OH_Input_UnregisterDeviceListeners();

/**
* @brief 获取功能键状态。
*
* @param keyCode 功能键值。目前仅支持CapsLock键，键值为1。
* @param state state 功能键状态。0表示功能键关闭，1表示功能键打开。
* @return OH_Input_GetFunctionKeyState 函数返回值。
*     <br>{@link INPUT_SUCCESS} 表示获取状态成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数错误。
*     <br>{@link INPUT_KEYBOARD_DEVICE_NOT_EXIST} 表示键盘设备不存在。
* @syscap SystemCapability.MultimodalInput.Input.Core
* @since 15
*/
Input_Result OH_Input_GetFunctionKeyState(int32_t keyCode, int32_t *state);

/**
* @brief 查询设备支持的最大触屏报点数。
*
* @param count 设备支持的最大触屏报点数，count取值范围为0-10，-1表示未知数量。
* @return OH_Input_QueryMaxTouchPoints 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示查询成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数错误。
* @since 20
*/
Input_Result OH_Input_QueryMaxTouchPoints(int32_t *count);

/**
* @brief 获取当前屏幕上鼠标的坐标点。
* <br>从API版本26.0.0开始，非焦点应用持有ohos.permission.INPUT_DEVICE_CONFIGURATOR权限，可调用该接口。
*
* @param displayId 当前屏幕的屏幕ID。
* @param displayX 鼠标在当前屏幕的X坐标，单位为像素（px）。
* @param displayY 鼠标在当前屏幕的Y坐标，单位为像素（px）。
* @return OH_Input_GetPointerLocation 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示查询成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数错误。
*     <br>{@link INPUT_SERVICE_EXCEPTION} 表示服务异常。
*     <br>{@link INPUT_APP_NOT_FOCUSED} 表示当前应用不是焦点应用。
*     <br>{@link INPUT_DEVICE_NO_POINTER} 表示无鼠标类输入外设。
* @since 20
*/
Input_Result OH_Input_GetPointerLocation(int32_t *displayId, double *displayX, double *displayY);
/**
* @brief 创建鼠标光标信息对象。通过调用{@link OH_Input_CursorInfo_Destroy}销毁鼠标光标信息对象。
*
* @return 创建成功返回一个{@link Input_CursorInfo}对象，否则返回空指针，可能原因是内存分配失败。
* @since 22
*/
struct Input_CursorInfo* OH_Input_CursorInfo_Create();

/**
* @brief 销毁鼠标光标信息对象。
*
* @param cursorInfo 鼠标光标信息对象。
* @since 22
*/
void OH_Input_CursorInfo_Destroy(Input_CursorInfo** cursorInfo);

/**
* @brief 获取指定鼠标光标信息对象对应的光标显示状态。
*
* @param cursorInfo 指定鼠标光标信息对象。可以通过{@link OH_Input_GetMouseEventCursorInfo}查询指定鼠标事件的鼠标光标信息、或通过
*     {@link OH_Input_GetCursorInfo}接口查询当前的鼠标光标信息。
* @param visible 鼠标光标显示或隐藏状态。true代表显示状态，false代表隐藏状态。
* @return OH_Input_CursorInfo_IsVisible 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
* @since 22
*/
Input_Result OH_Input_CursorInfo_IsVisible(Input_CursorInfo* cursorInfo, bool* visible);

/**
* @brief 获取指定鼠标光标信息对象对应的光标样式。
*
* @param cursorInfo 指定鼠标光标信息对象。可以通过{@link OH_Input_GetMouseEventCursorInfo}查询指定鼠标事件的鼠标光标信息、或通过
*     {@link OH_Input_GetCursorInfo}接口查询当前的鼠标光标信息。
* @param style Cursor style of the cursorInfo.
* @return OH_Input_CursorInfo_GetStyle 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败或者光标不可见。
* @since 22
*/
Input_Result OH_Input_CursorInfo_GetStyle(Input_CursorInfo* cursorInfo, Input_PointerStyle* style);

/**
* @brief 获取指定鼠标光标信息对象对应的光标大小档位。
*
* @param cursorInfo 指定鼠标光标信息对象。可以通过{@link OH_Input_GetMouseEventCursorInfo}查询指定鼠标事件的鼠标光标信息、或通过
*     {@link OH_Input_GetCursorInfo}接口查询当前的鼠标光标信息。
* @param sizeLevel 鼠标光标信息的光标大小档位。取值范围为整数1~7，数值越大则光标越大。应用自定义光标{@link DEVELOPER_DEFINED_ICON}请以实际位图大小为准。
* @return OH_Input_CursorInfo_GetSizeLevel 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败或者光标不可见。
* @since 22
*/
Input_Result OH_Input_CursorInfo_GetSizeLevel(Input_CursorInfo* cursorInfo, int32_t* sizeLevel);

/**
* @brief 获取指定鼠标光标信息对象对应的光标颜色，使用32位ARGB整数表示。
*
* @param cursorInfo 指定鼠标光标信息对象。可以通过{@link OH_Input_GetMouseEventCursorInfo}查询指定鼠标事件的鼠标光标信息、或通过
*     {@link OH_Input_GetCursorInfo}接口查询当前的鼠标光标信息。
* @param color 鼠标光标信息的光标颜色，使用32位ARGB整数表示。应用自定义光标{@link DEVELOPER_DEFINED_ICON}请以实际位图颜色为准。
* @return OH_Input_CursorInfo_GetColor 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败或者光标不可见。
* @since 22
*/
Input_Result OH_Input_CursorInfo_GetColor(Input_CursorInfo* cursorInfo, uint32_t* color);

/**
* @brief Obtains the mouse pointer information of the mouse event, including the pointer visible status, pointer style,
* pointer size level, and pointer color.
*
* @param mouseEvent Mouse event object. You can obtain the mouse event object from the callback of
*     {@link OH_Input_AddMouseEventMonitor()} or {@link OH_Input_AddInputEventInterceptor()}.
* @param cursorInfo Mouse pointer information object. You can call {@link OH_Input_CursorInfo_Create()} to create a
*     mouse pointer information object.
* @return Return value of the **OH_Input_GetMouseEventCursorInfo** function.
*     <br>{@link INPUT_SUCCESS} if the operation is successful;
*     <br>{@link INPUT_PARAMETER_ERROR} if the parameter verification fails.
* @since 22
*/
Input_Result OH_Input_GetMouseEventCursorInfo(const struct Input_MouseEvent* mouseEvent, Input_CursorInfo* cursorInfo);

/**
* @brief 查询当前鼠标光标信息，包括光标显示状态、光标样式、光标大小档位、光标颜色。如果pixelmap参数非空，且光标样式为{@link DEVELOPER_DEFINED_ICON}，
* 则会同时返回光标的PixelMap位图对象。
*
* @param cursorInfo 鼠标光标信息对象，可以通过{@link OH_Input_CursorInfo_Create}接口创建鼠标光标信息对象。
* @param pixelmap PixelMap位图对象，如果该参数非空且光标为应用自定义，则会返回光标的PixelMap位图对象，否则不返回PixelMap位图对象。首先通过
*     {@link OH_PixelmapInitializationOptions_Create}接口创建OH_PixelmapInitializationOptions对象，然后调用
*     {@link OH_PixelmapInitializationOptions_SetWidth}接口设置大于0的宽度，调用{@link OH_PixelmapInitializationOptions_SetHeight}
*     接口设置大于0的高度，最后以该OH_PixelmapInitializationOptions对象作为入参调用{@link OH_PixelmapNative_CreateEmptyPixelmap}
*     接口创建PixelMap位图对象。
*     <br>使用完需要先调用{@link OH_PixelmapNative_Release}接口释放PixelMap位图对象，然后调用{@link OH_PixelmapNative_Destroy}
*     接口销毁PixelMap位图对象。
* @return OH_Input_GetCursorInfo 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
*     <br>{@link INPUT_SERVICE_EXCEPTION} 表示服务异常，请重试。
* @since 22
*/
Input_Result OH_Input_GetCursorInfo(Input_CursorInfo* cursorInfo, OH_PixelmapNative** pixelmap);

/**
* @brief 像素图，用于表示和操作像素图像数据，支持图像的创建、读取、修改和渲染等操作。
*
* @since 22
*/
typedef struct OH_PixelmapNative OH_PixelmapNative;

/**
* @brief 设置当前窗口的鼠标光标的显示或隐藏状态。
*
* @param visible 鼠标光标是否显示。true表示显示，false表示不显示。
* @return OH_Input_SetPointerVisible 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_DEVICE_NOT_SUPPORTED} 表示设备不支持。
*     <br>{@link INPUT_SERVICE_EXCEPTION} 表示服务异常，请重试。
* @since 22
*/
Input_Result OH_Input_SetPointerVisible(bool visible);

/**
* @brief 获取指定窗口的鼠标光标样式。此接口仅支持获取本应用进程内窗口的鼠标光标样式。
*
* @param windowId 窗口ID。取值范围为大于等于-1的整数，取值为-1时表示全局窗口。
*     <br>仅支持传入当前窗口和全局窗口的ID，传入其他ID返回全局窗口的默认光标样式，当前窗口ID可以通过{@link getWindowProperties}获取。
* @param pointerStyle 鼠标光标样式，取值为{@link Input_PointerStyle}的枚举值。
* @return OH_Input_GetPointerStyle 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
*     <br>{@link INPUT_SERVICE_EXCEPTION} 表示服务异常，请重试。
* @since 22
*/
Input_Result OH_Input_GetPointerStyle(int32_t windowId, int32_t *pointerStyle);

/**
* @brief 设置指定窗口的鼠标光标样式。此接口仅支持设置本应用进程内窗口的鼠标光标样式。
*
* @param windowId 窗口ID。取值范围为大于等于0的整数。
*     <br>仅支持传入当前窗口的光标样式，传入其他窗口ID本接口可以运行成功但设置不生效，当前窗口ID可以通过{@link getWindowProperties}获取。
* @param pointerStyle 鼠标光标样式，取值为{@link Input_PointerStyle}的枚举值。
* @return OH_Input_SetPointerStyle 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
*     <br>{@link INPUT_SERVICE_EXCEPTION} 表示服务异常，请重试。
* @since 22
*/
Input_Result OH_Input_SetPointerStyle(int32_t windowId, int32_t pointerStyle);

/**
* @brief 创建自定义鼠标光标资源对象。通过调用{@link OH_Input_CustomCursor_Destroy}销毁自定义鼠标光标资源对象。
*
* @param pixelMap {@link OH_PixelmapNative}自定义鼠标光标像素图。最小限制为资源图本身的最小限制。最大限制为256 x 256px。
* @param anchorX 自定义鼠标光标焦点的水平坐标。该坐标受自定义鼠标光标大小的限制。最小值为0，最大值为资源图的宽度最大值，单位为像素（px）。
* @param anchorY 自定义鼠标光标焦点的垂直坐标。该坐标受自定义鼠标光标大小的限制。最小值为0，最大值为资源图的高度最大值，单位为像素（px）。
* @return {@link Input_CustomCursor}对象。操作成功时返回自定义鼠标光标资源对象的指针。异常时返回空指针。
* @since 22
*/
Input_CustomCursor* OH_Input_CustomCursor_Create(OH_PixelmapNative* pixelMap, int32_t anchorX, int32_t anchorY);

/**
* @brief 销毁自定义鼠标光标资源对象。
*
* @param customCursor 自定义鼠标光标资源{@link Input_CustomCursor}。
* @since 22
*/
void OH_Input_CustomCursor_Destroy(Input_CustomCursor** customCursor);

/**
* @brief 获取指定自定义鼠标光标资源的自定义鼠标光标像素图。
*
* @param customCursor 自定义鼠标光标资源{@link Input_CustomCursor}。
* @param pixelMap {@link OH_PixelmapNative}自定义鼠标光标像素图。
* @return OH_Input_CustomCursor_GetPixelMap 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
* @since 22
*/
Input_Result OH_Input_CustomCursor_GetPixelMap(Input_CustomCursor* customCursor, OH_PixelmapNative** pixelMap);

/**
* @brief 获取指定自定义鼠标光标资源的焦点坐标。
*
* @param customCursor 自定义鼠标光标资源{@link Input_CustomCursor}。
* @param anchorX 自定义鼠标光标资源的焦点水平坐标，单位为像素（px）。
* @param anchorY 自定义鼠标光标资源的焦点垂直坐标，单位为像素（px）。
* @return OH_Input_CustomCursor_GetAnchor 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
* @since 22
*/
Input_Result OH_Input_CustomCursor_GetAnchor(Input_CustomCursor* customCursor, int32_t* anchorX, int32_t* anchorY);
/**
* @brief 创建自定义鼠标光标配置对象。通过调用{@link OH_Input_CursorConfig_Destroy}销毁自定义鼠标光标配置对象。
*
* @param followSystem 是否根据系统设置调整鼠标光标大小。false表示使用自定义鼠标光标样式大小，true表示根据系统设置调整鼠标光标大小，可调整范围为：[光标资源图大小，256×256]，单位为像素（px）。
* @return 自定义鼠标光标配置{@link Input_CursorConfig}对象。
* @since 22
*/
Input_CursorConfig* OH_Input_CursorConfig_Create(bool followSystem);

/**
* @brief 销毁自定义鼠标光标配置对象。
*
* @param cursorConfig 自定义鼠标光标配置{@link Input_CursorConfig}对象。
* @since 22
*/
void OH_Input_CursorConfig_Destroy(Input_CursorConfig** cursorConfig);

/**
* @brief 查询自定义鼠标光标配置是否跟随系统设置调整光标大小。
*
* @param cursorConfig 自定义鼠标光标配置{@link Input_CursorConfig}。
* @param followSystem 是否根据系统设置调整光标大小，取值为true表示根据系统设置调整鼠标光标大小，取值为false表示使用自定义鼠标光标样式大小。
* @return OH_Input_CursorConfig_IsFollowSystem 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
* @since 22
*/
Input_Result OH_Input_CursorConfig_IsFollowSystem(Input_CursorConfig *cursorConfig, bool *followSystem);

/**
* @brief 设置自定义鼠标光标样式。
* <br>应用窗口布局改变、热区切换、页面跳转、光标移出再回到窗口、光标在窗口不同区域移动，以上场景可能导致光标切换回系统样式，需要开发者重新设置光标样式。此接口仅支持设置本应用进程内窗口的自定义鼠标光标样式。
*
* @param windowId 窗口ID。取值范围为大于等于0的整数，仅支持传入当前窗口的光标样式。
* @param customCursor 自定义鼠标光标资源{@link Input_CustomCursor}。
* @param cursorConfig 自定义鼠标光标配置{@link Input_CursorConfig}。
* @return OH_Input_SetCustomCursor 函数返回值：
*     <br>{@link INPUT_SUCCESS} 表示操作成功。
*     <br>{@link INPUT_PARAMETER_ERROR} 表示参数检查失败。
*     <br>{@link INPUT_INVALID_WINDOWID} 表示窗口ID无效。
*     <br>{@link INPUT_DEVICE_NOT_SUPPORTED} 表示设备不支持。
*     <br>{@link INPUT_SERVICE_EXCEPTION} 表示服务异常，请重试。
* @since 22
*/
Input_Result OH_Input_SetCustomCursor(int32_t windowId, Input_CustomCursor* customCursor,
                                      Input_CursorConfig* cursorConfig);

/**
* @brief 绑定指定输入设备到指定屏幕。
*
* @permission ohos.permission.INPUT_DEVICE_CONFIGURATOR
* @param inputDeviceId 指定输入设备的设备ID。
* @param displayId 指定屏幕的屏幕ID。
* @return OH_Input_BindInputDeviceToDisplay函数返回值：
*     <br>{@link INPUT_SUCCESS}表示操作成功。
*     <br>{@link INPUT_PERMISSION_DENIED}表示权限校验失败。
*     <br>{@link INPUT_PARAMETER_ERROR}表示参数检查失败（输入设备不存在，显示屏设备不存在，或者输入设备不是手写笔设备）。
*     <br>{@link INPUT_SERVICE_EXCEPTION}表示服务异常，请重试。
* @since 26.0.0
*/
Input_Result OH_Input_BindInputDeviceToDisplay(int32_t inputDeviceId, int32_t displayId);
#ifdef __cplusplus
}
#endif

#endif /* OH_INPUT_MANAGER_H */

/** @} */