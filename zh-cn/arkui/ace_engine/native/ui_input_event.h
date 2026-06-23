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
 * @addtogroup ArkUI_EventModule
 * @{
 *
 * @brief Declares the UI input event capabilities provided by ArkUI on the native side.
 *
 * @since 12
 */

/**
 * @file ui_input_event.h
 *
 * @brief Provides ArkUI event definitions on the native side.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef _ARKUI_UI_INPUT_EVENT_H_

#define _ARKUI_UI_INPUT_EVENT_H_

#include "native_type.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief UI输入事件定义。
 *
 * @since 12
 */
typedef struct ArkUI_UIInputEvent ArkUI_UIInputEvent;

/**
 * @brief 定义惯性滚动轴事件。
 *
 * @since 22
 */
typedef struct ArkUI_CoastingAxisEvent ArkUI_CoastingAxisEvent;

/**
 * @brief 定义触摸测试信息。
 *
 * @since 22
 */
typedef struct ArkUI_TouchTestInfo ArkUI_TouchTestInfo;

/**
 * @brief 定义触摸测试信息项。触摸测试信息项包含触摸测试中子组件的信息，可以通过{@link OH_ArkUI_TouchTestInfoItem_GetXXX}系列接口获取子组件信息。
 *
 * @since 22
 */
typedef struct ArkUI_TouchTestInfoItem ArkUI_TouchTestInfoItem;

/**
 * @brief 定义触摸测试信息项句柄。
 *
 * @since 22
 */
typedef ArkUI_TouchTestInfoItem* ArkUI_TouchTestInfoItemHandle;

/**
 * @brief 定义触摸测试信息项句柄数组。
 *
 * @since 22
 */
typedef ArkUI_TouchTestInfoItemHandle* ArkUI_TouchTestInfoItemArray;

/**
 * @brief UI输入事件类型定义。
 *
 * @since 12
 */
typedef enum {
    ARKUI_UIINPUTEVENT_TYPE_UNKNOWN = 0,

    ARKUI_UIINPUTEVENT_TYPE_TOUCH = 1,

    /**
     * 鼠标事件。
     */
    ARKUI_UIINPUTEVENT_TYPE_MOUSE = 3,

        ARKUI_UIINPUTEVENT_TYPE_AXIS = 2,

    /**
     * @brief 按键事件。
     *
     * @since 20
     */
    ARKUI_UIINPUTEVENT_TYPE_KEY = 4,

    /**
     * @brief 表冠事件。
     *
     * @since 24
     */
    ARKUI_UIINPUTEVENT_TYPE_DIGITAL_CROWN = 5
} ArkUI_UIInputEvent_Type;

/**
 * @brief 定义表冠事件的阶段。
 *
 * @since 24
 */
typedef enum {
    /**
     * @brief Unknown phase of the crown event.
     */
    ARKUI_CROWNEVENT_ACTION_UNKNOWN = 0,

    /**
     * @brief The crown event is updated.
     */
    ARKUI_CROWNEVENT_ACTION_UPDATE = 1,

    /**
     * @brief The crown event ends.
     */
    ARKUI_CROWNEVENT_ACTION_END = 2
} ArkUI_CrownEvent_Action;

/**
 * @brief 定义惯性滚动轴事件的阶段。
 *
 * @since 22
 */
typedef enum {
    /**
     * 非惯性轴事件阶段，异常默认值，可以通过检查惯性轴阶段值不为该值来判断当前惯性轴事件是有效的。
     */
    ARKUI_COASTING_AXIS_EVENT_PHASE_NONE = 0,

    /**
     * 惯性滚动轴事件开始，此为惯性阶段的第一个事件。
     */
    ARKUI_COASTING_AXIS_EVENT_PHASE_BEGIN = 1,

    /**
     * 惯性滚动轴事件更新，此阶段可以获取惯性轴值增量来处理滚动偏移。
     */
    ARKUI_COASTING_AXIS_EVENT_PHASE_UPDATE = 2,

    /**
     * 惯性滚动轴事件结束，此值在惯性被刹停（惯性滚动阶段用户重新触摸触控板或通过鼠标及触屏与组件产生交互等）或惯性衰减至自然停止时发送，到达此阶段时，应立即停止惯性滚动效果。
     */
    ARKUI_COASTING_AXIS_EVENT_PHASE_END = 3
} ArkUI_CoastingAxisEventPhase;

/**
 * @brief 事件的注入方和被注入方间手势识别结果是否为竞争场景的策略。该策略决定了事件的注入方如何与被注入方的手势处理逻辑交互，非竞争场景会同时触发手势，竞争场景只触发其中一个。
 *
 * @since 24
 */
typedef enum {
    /**
     * 无竞争策略。注入的事件不与任何现有手势竞争。注入的事件和现有手势可以独立并行处理。
     */
    ARKUI_COMPETITION_STRATEGY_DEFAULT = 0,

    /**
     * 竞争策略。事件注入方和被注入方间的手势为竞争关系，只能处理其中一方的手势。
     */
    ARKUI_COMPETITION_STRATEGY_COMPETITION = 1
} ArkUI_CompetitionStrategy;

/**
 * @brief Defines the action types of the input event.
 *
 * @since 12
 */
enum {
    /** Cancellation of touch. */
    UI_TOUCH_EVENT_ACTION_CANCEL = 0,

    /** Pressing of a touch point. */
    UI_TOUCH_EVENT_ACTION_DOWN = 1,

    /** Moving of a touch point. */
    UI_TOUCH_EVENT_ACTION_MOVE = 2,

    /** Lifting of a touch point. */
    UI_TOUCH_EVENT_ACTION_UP = 3,
};

/**
 * @brief Defines the tool type of the touch event.
 *
 * @since 12
 */
enum {
    /** Unknown tool type. */
    UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN = 0,

    /** Finger. */
    UI_INPUT_EVENT_TOOL_TYPE_FINGER = 1,

    /** Pen. */
    UI_INPUT_EVENT_TOOL_TYPE_PEN = 2,

    /** Mouse. */
    UI_INPUT_EVENT_TOOL_TYPE_MOUSE = 3,

    /** TouchPad. */
    UI_INPUT_EVENT_TOOL_TYPE_TOUCHPAD = 4,

    /** JoyStick. */
    UI_INPUT_EVENT_TOOL_TYPE_JOYSTICK = 5,
};

/**
 * @brief Defines the source type of the touch event.
 *
 * @since 12
 */
enum {
    /** Unknown source type. */
    UI_INPUT_EVENT_SOURCE_TYPE_UNKNOWN = 0,

    /** Mouse. */
    UI_INPUT_EVENT_SOURCE_TYPE_MOUSE = 1,

    /** Touchscreen. */
    UI_INPUT_EVENT_SOURCE_TYPE_TOUCH_SCREEN = 2,

    /**
     * @brief The key type.
     *
     * @since 22
     */
    UI_INPUT_EVENT_SOURCE_TYPE_KEY = 4,

    /**
     * @brief The joystick type.
     *
     * @since 22
     */
    UI_INPUT_EVENT_SOURCE_TYPE_JOYSTICK = 5,
};

/**
 * @brief 定义触摸测试类型的枚举值。
 *
 * @since 12
 */
typedef enum {
    /**
     * 默认触摸测试效果。自身及子节点响应触摸测试，但阻塞兄弟节点的触摸测试，不影响祖先节点的触摸测试。
     */
    HTM_DEFAULT = 0,

    /**
     * 自身响应触摸测试，阻塞子节点、兄弟节点和祖先节点的触摸测试。
     */
    HTM_BLOCK,

    /**
     * 自身和子节点都响应触摸测试，不会阻塞兄弟节点和祖先节点的触摸测试。
     */
    HTM_TRANSPARENT,

    /**
     * 自身不响应触摸测试，不会阻塞子节点、兄弟节点和祖先节点的触摸测试。
     */
    HTM_NONE,

    /**
     * 自身和子节点响应触摸测试，阻止所有优先级较低的兄弟节点和父节点参与触摸测试。
     *
     * @since 20
     */
    HTM_BLOCK_HIERARCHY,

    /**
     * 自身不响应触摸测试，并且所有的后代（孩子，孙子等）也不响应触摸测试，不会影响祖先节点的触摸测试。
     * @since 20
     */
    HTM_BLOCK_DESCENDANTS
} HitTestMode;

/**
 * @brief Define the action types of the mouse event.
 *
 * @since 12
 */
enum {
    /** Unknown action. */
    UI_MOUSE_EVENT_ACTION_UNKNOWN = 0,

    /** The mouse button is pressed. */
    UI_MOUSE_EVENT_ACTION_PRESS = 1,

    /** The mouse button is released. */
    UI_MOUSE_EVENT_ACTION_RELEASE = 2,

    /** The mouse cursor moves. */
    UI_MOUSE_EVENT_ACTION_MOVE = 3,

    /** The mouse button action is canceled.
        * @since 18
        */
    UI_MOUSE_EVENT_ACTION_CANCEL = 13,
};

/**
 * @brief Define the button type for mouse events.
 *
 * @since 12
 */
enum {
    /** No button. */
    UI_MOUSE_EVENT_BUTTON_NONE = 0,

    /** Left button. */
    UI_MOUSE_EVENT_BUTTON_LEFT = 1,

    /** Right button. */
    UI_MOUSE_EVENT_BUTTON_RIGHT = 2,

    /** Middle button. */
    UI_MOUSE_EVENT_BUTTON_MIDDLE = 3,

    /** Back button on the left of the mouse. */
    UI_MOUSE_EVENT_BUTTON_BACK = 4,

    /** Forward button on the left of the mouse. */
    UI_MOUSE_EVENT_BUTTON_FORWARD = 5,
};

/**
 * @brief 定义modifier按键。
 *
 * @since 12
 */
typedef enum {
    /**
     * Ctrl.
     */
    ARKUI_MODIFIER_KEY_CTRL = 1 << 0,

    /**
     * Shift.
     */
    ARKUI_MODIFIER_KEY_SHIFT = 1 << 1,

    /**
     * Alt.
     */
    ARKUI_MODIFIER_KEY_ALT = 1 << 2,

    /**
     * Fn（仅调试使用，通常不上报Fn状态）.
     */
    ARKUI_MODIFIER_KEY_FN = 1 << 3
} ArkUI_ModifierKeyName;

/**
 * @brief Defines an enum for the axis types for focus axis events.
 *
 * @since 15
 */
enum {
    /** Game controller X-axis. */
    UI_FOCUS_AXIS_EVENT_ABS_X = 0,
    /** Game controller Y-axis. */
    UI_FOCUS_AXIS_EVENT_ABS_Y = 1,
    /** Game controller Z-axis. */
    UI_FOCUS_AXIS_EVENT_ABS_Z = 2,
    /** Game controller RZ-axis. */
    UI_FOCUS_AXIS_EVENT_ABS_RZ = 3,
    /** Game controller GAS-axis. */
    UI_FOCUS_AXIS_EVENT_ABS_GAS = 4,
    /** Game controller BRAKE-axis. */
    UI_FOCUS_AXIS_EVENT_ABS_BRAKE = 5,
    /** Game controller HAT0X-axis. */
    UI_FOCUS_AXIS_EVENT_ABS_HAT0X = 6,
    /** Game controller HAT0Y-axiS. */
    UI_FOCUS_AXIS_EVENT_ABS_HAT0Y = 7,
    /**
     * Game controller RX-axis.
     *
     * @since 23
     */
    UI_FOCUS_AXIS_EVENT_ABS_RX = 8,
    /**
     * Game controller RY-axis.
     *
     * @since 23
     */
    UI_FOCUS_AXIS_EVENT_ABS_RY = 9,
    /**
     * Game controller THROTTLE-axis.
     *
     * @since 23
     */
    UI_FOCUS_AXIS_EVENT_ABS_THROTTLE = 10,
    /**
     * Game controller RUDDER-axis.
     *
     * @since 23
     */
    UI_FOCUS_AXIS_EVENT_ABS_RUDDER = 11,
    /**
     * Game controller WHEEL-axis.
     *
     * @since 23
     */
    UI_FOCUS_AXIS_EVENT_ABS_WHEEL = 12,
    /**
     * Game controller HAT1X-axis.
     *
     * @since 23
     */
    UI_FOCUS_AXIS_EVENT_ABS_HAT1X = 13,
    /**
     * Game controller HAT1Y-axis.
     *
     * @since 23
     */
    UI_FOCUS_AXIS_EVENT_ABS_HAT1Y = 14,
    /**
     * Game controller HAT2X-axis.
     *
     * @since 23
     */
    UI_FOCUS_AXIS_EVENT_ABS_HAT2X = 15,
    /**
     * Game controller HAT2Y-axis.
     *
     * @since 23
     */
    UI_FOCUS_AXIS_EVENT_ABS_HAT2Y = 16,
    /**
     * Game controller HAT3X-axis.
     *
     * @since 23
     */
    UI_FOCUS_AXIS_EVENT_ABS_HAT3X = 17,
    /**
     * Game controller HAT3Y-axis.
     *
     * @since 23
     */
    UI_FOCUS_AXIS_EVENT_ABS_HAT3Y = 18,
};

/**
 * @brief Enumerates the axis types for axis events.
 *
 * @since 21
 */
enum {
    /** Vertical scroll axis. */
    UI_AXIS_TYPE_VERTICAL_AXIS = 0,
    /** Horizontal scroll axis. */
    UI_AXIS_TYPE_HORIZONTAL_AXIS = 1,
    /** Pinch axis. */
    UI_AXIS_TYPE_PINCH_AXIS = 2,
};

/**
 * @brief 定义触摸事件是左手还是右手。
 *
 * @since 15
 */
typedef enum {
    /**
     * 未知。
     */
    ARKUI_EVENT_HAND_NONE = 0,

    /**
     * 左手。
     */
    ARKUI_EVENT_HAND_LEFT = 1,

    /**
     * 右手。
     */
    ARKUI_EVENT_HAND_RIGHT = 2
} ArkUI_InteractionHand;

/**
 * @brief Enumerates the action types for axis events.
 *
 * @since 15
 */
enum {
    /** The axis event is abnormal. */
    UI_AXIS_EVENT_ACTION_NONE = 0,
    /** The axis event begins. */
    UI_AXIS_EVENT_ACTION_BEGIN = 1,
    /** The axis event is updated. */
    UI_AXIS_EVENT_ACTION_UPDATE = 2,
    /** The axis event ends. */
    UI_AXIS_EVENT_ACTION_END = 3,
    /** The axis event is canceled. */
    UI_AXIS_EVENT_ACTION_CANCEL = 4,
};

/**
 * @brief 定义触摸测试策略。
 *
 * @since 22
 */
typedef enum {
    /**
     * 自定义分发不产生影响，系统按当前节点命中状态分发事件。
     */
    ARKUI_TOUCH_TEST_STRATEGY_DEFAULT = 0,

    /**
     * 应用指定分发事件到某个子节点，其他兄弟节点是否分发事件交由系统决定。
     */
    ARKUI_TOUCH_TEST_STRATEGY_FORWARD_COMPETITION = 1,

    /**
     * 应用指定分发事件到某个子节点，系统不再分发事件到其他兄弟节点。
     */
    ARKUI_TOUCH_TEST_STRATEGY_FORWARD = 2
} ArkUI_TouchTestStrategy;

/**
 * @brief 获取UI输入事件的类型。在访问一个ArkUI_UIInputEvent指针对象之前，推荐使用该方法判断该输入事件的类型，该接口会返回{@link ArkUI_UIInputEvent_Type}枚举中的一种。比如，
 * 当事件是一个触控类型时，由于触控类型是指向性事件，那么使用OH_ArkUI_UIInputEvent_GetXXX及OH_ArkUI_PointerEvent_GetXXX系列接口，均可以正常访问；
 * 而如果使用OH_ArkUI_KeyEvent_GetXXX相关接口去访问它，则会有无法预期的结果。对于还未支持的事件类型，接口返回默认值0。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前UI输入事件的类型，如果参数异常则返回0。
 * @since 12
 */
int32_t OH_ArkUI_UIInputEvent_GetType(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取输入事件的action类型。action类型为基础事件在不同阶段的类型定义，通常代表了事件的特点，并表征事件的开始与结束，如touch down, touch up。触控事件的action类型为
 * UI_TOUCH_EVENT_ACTION_XXX，鼠标事件的action类型为UI_MOUSE_EVENT_ACTION_XXX。
 *
 * @note
 * 1. For axis events, use {@link OH_ArkUI_AxisEvent_GetAxisAction} to obtain the action type,
 *    which returns UI_AXIS_EVENT_ACTION_XXX.
 * 2. For key events, use {@link OH_ArkUI_KeyEvent_GetType} instead.
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前UI输入事件的操作类型，如果参数异常则返回-1。
 * @since 12
 */
int32_t OH_ArkUI_UIInputEvent_GetAction(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取UI输入事件的触发源类型。输入源为产生输入事件的真实物理设备，如触摸屏，鼠标等，由{@link UI_INPUT_EVENT_SOURCE_TYPE_XXX}定义，而输入工具为操作输入源设备来产生事件的工具，如手指、
 * 触控笔。在某些情况下两者可能容易发生混淆，比如当用户在操作鼠标时，鼠标既是输入源，也是输入工具。
 *
 * @note For key events, obtaining the source type is not supported, and in such cases,
 *     the API will return an <b>unknown</b> value.
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回产生当前UI输入事件的来源类型。
 * @since 12
 */
int32_t OH_ArkUI_UIInputEvent_GetSourceType(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取UI输入事件的工具类型。输入工具为操作输入源设备来产生事件的操作方，如手指、触控笔，他们自身不真实产生事件，但可以驱动输入源设备不断产生事件。返回的类型由
 * {@link UI_INPUT_EVENT_TOOL_TYPE_XXX}枚举值定义。
 *
 * @note For key events, obtaining the tool type is not supported, and in such cases,
 *     the API will return an <b>unknown</b> value.
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回产生当前UI输入事件的工具类型。
 * @since 12
 */
int32_t OH_ArkUI_UIInputEvent_GetToolType(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取UI输入事件发生的时间。单位为ns。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回UI输入事件发生的时间，如果参数异常则返回0。
 * @since 12
 */
int64_t OH_ArkUI_UIInputEvent_GetEventTime(const ArkUI_UIInputEvent* event);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取多点触控的接触点数量。指向性事件一般是附带有事件发生位置信息的事件，如触摸事件，用户操作时，可以感知事件在什么位置发生。而非指向性事件，如按键事件，一般没有位置信息，
 * 没有触点的说法，该接口永远返回0。对于触摸事件，该接口多用于处理多指触控，判断用户有几根手指在操作当前控件。而对于鼠标和轴事件，可认为触点只有1个，该接口永远返回1。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前指向性输入事件的接触点数量。
 * @since 12
 */
uint32_t OH_ArkUI_PointerEvent_GetPointerCount(const ArkUI_UIInputEvent* event);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取多点触控的接触点标识。返回事件发生时，事件触点的唯一标识符，用于区分同类输入设备的多点触控信息。其数值没有除标识触点外的其他含义。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回特定接触点标识。
 * @since 12
 */
int32_t OH_ArkUI_PointerEvent_GetPointerId(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 获取触发当前事件的对应的手指id。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_GetChangedPointerId(const ArkUI_UIInputEvent* event, uint32_t* pointerIndex);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取相对于当前组件左上角的X坐标。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前指向性输入事件相对于当前组件左上角的X坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetX(const ArkUI_UIInputEvent* event);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取特定接触点相对于当前组件左上角的X坐标。对于鼠标和轴事件，当给定的索引大于0时，返回默认值0.0f。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回指向性输入事件中特定接触点相对于当前组件左上角的X坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取相对于当前组件左上角的Y坐标。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前指向性输入事件相对于当前组件左上角的Y坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetY(const ArkUI_UIInputEvent* event);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取特定接触点相对于当前组件左上角的Y坐标。对于鼠标和轴事件，当给定的索引大于0时，返回默认值0.0f。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回指向性输入事件事件中特定接触点相对于当前组件左上角的Y坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从{@link 指向性输入事件}（如触摸事件、鼠标事件、轴事件）中根据实时位置获取相对于当前组件左上角的X坐标。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前指向性输入事件相对于当前组件左上角的X坐标；默认单位为px，单位可跟随{@link setLengthMetricUnit}的设置而变化；如果参数异常则返回0.0f。
 * @since 26.0.0
 */
float OH_ArkUI_PointerEvent_GetCurrentLocalX(const ArkUI_UIInputEvent* event);

/**
 * @brief 从{@link 指向性输入事件}（如触摸事件、鼠标事件、轴事件）中根据实时位置获取特定接触点相对于当前组件左上角的X坐标。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。
 * @return 返回特定接触点相对于当前组件左上角的X坐标；默认单位为px，单位可跟随{@link setLengthMetricUnit}的设置而变化；如果参数异常则返回0.0f。
 * @since 26.0.0
 */
float OH_ArkUI_PointerEvent_GetCurrentLocalXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从{@link 指向性输入事件}（如触摸事件、鼠标事件、轴事件）中根据实时位置获取相对于当前组件左上角的Y坐标。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前指向性输入事件相对于当前组件左上角的Y坐标；默认单位为px，单位可跟随{@link setLengthMetricUnit}的设置而变化；如果参数异常则返回0.0f。
 * @since 26.0.0
 */
float OH_ArkUI_PointerEvent_GetCurrentLocalY(const ArkUI_UIInputEvent* event);

/**
 * @brief 从{@link 指向性输入事件}（如触摸事件、鼠标事件、轴事件）中根据实时位置获取特定接触点相对于当前组件左上角的Y坐标。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。
 * @return 返回特定接触点相对于当前组件左上角的Y坐标；默认单位为px，单位可跟随{@link setLengthMetricUnit}的设置而变化；如果参数异常则返回0.0f。
 * @since 26.0.0
 */
float OH_ArkUI_PointerEvent_GetCurrentLocalYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取相对于当前应用窗口左上角的X坐标。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前指向性输入事件相对于当前应用窗口左上角的X坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetWindowX(const ArkUI_UIInputEvent* event);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取特定接触点相对于当前应用窗口左上角的X坐标。对于鼠标和轴事件，当给定的索引大于0时，总是返回默认值0.0f。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回指向性输入事件中特定接触点相对于当前应用窗口左上角的X坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetWindowXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取相对于当前应用窗口左上角的Y坐标。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前指向性输入事件相对于当前应用窗口左上角的Y坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetWindowY(const ArkUI_UIInputEvent* event);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取特定接触点相对于当前应用窗口左上角的Y坐标。对于鼠标和轴事件，当给定的索引大于0时，总是返回默认值0.0f。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回指向性输入事件中特定接触点相对于当前应用窗口左上角的Y坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetWindowYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取相对于当前屏幕左上角的X坐标。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前指向性输入事件相对于当前屏幕左上角的X坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetDisplayX(const ArkUI_UIInputEvent* event);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取特定接触点相对于当前屏幕左上角的X坐标。对于鼠标和轴事件，当给定的索引大于0时，总是返回默认值0.0f。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回指向性输入事件中特定接触点相对于当前屏幕左上角的X坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetDisplayXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取相对于当前屏幕左上角的Y坐标。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前指向性输入事件相对于当前屏幕左上角的Y坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetDisplayY(const ArkUI_UIInputEvent* event);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取特定接触点相对于当前屏幕左上角的Y坐标。对于鼠标和轴事件，当给定的索引大于0时，总是返回默认值0.0f。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回指向性输入事件中特定接触点相对于当前屏幕左上角的Y坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetDisplayYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取相对于全局显示的X坐标。只能从{@link ArkUI_UIInputEvent}事件中获取位置信息。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回相对于全局显示的X坐标，单位为px。如果发生任何参数错误，例如传递的一个事件没有位置信息，则返回0.0f。
 * @since 20
 */
float OH_ArkUI_PointerEvent_GetGlobalDisplayX(const ArkUI_UIInputEvent* event);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取相对于全局显示的X坐标。只能从指针事件中获取位置信息，对于鼠标和轴事件，当给定的pointerIndex大于0时，始终返回默认值0.0f。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。有效值范围[0, {@link OH_ArkUI_PointerEvent_GetPointerCount()} - 1]
 * @return 返回指向性输入事件中特定接触点相对于全局显示的X坐标，单位为px。如果发生任何参数错误，则返回0.0f。
 * @since 20
 */
float OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取相对于全局显示的Y坐标。只能从{@link ArkUI_UIInputEvent}事件中获取位置信息。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return float 返回相对于全局显示的Y坐标，单位为px。如果发生任何参数错误，例如传递的一个事件没有位置信息，则返回0.0f。
 * @since 20
 */
float OH_ArkUI_PointerEvent_GetGlobalDisplayY(const ArkUI_UIInputEvent* event);

/**
 * @brief 从指向性输入事件（如触摸事件、鼠标事件、轴事件）中获取相对于全局显示的Y坐标。只能从指针事件中获取位置信息，对于鼠标和轴事件，当给定的pointerIndex大于0时，始终返回默认值0.0f。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。有效值范围[0, {@link OH_ArkUI_PointerEvent_GetPointerCount()} - 1]
 * @return float 返回相对于全局显示的Y坐标，单位为px。如果发生任何参数错误，则返回0.0f。
 * @since 20
 */
float OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从指向性输入事件（如触摸事件）中获取触屏压力。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回当前指向性输入事件产生的触屏压力。取值范围为[0, 1]，压感大小与数值正相关。如果参数异常则返回默认值0.0f。在部分设备中，由于设备的硬件参数配置不同，可能会返回大于1的值。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetPressure(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从指向性输入事件（如触摸事件）中获取相对YZ平面的角度，取值的范围[-90, 90]，单位为deg，其中正值是向右倾斜。仅适用于支持倾角上报的触控笔操作产生的触控事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回当前指向性输入事件中相对YZ平面的角度。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetTiltX(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从指向性输入事件（如触摸事件）中获取相对XZ平面的角度，取值的范围[-90, 90]，单位为deg，其中正值是向下倾斜。仅适用于支持倾角上报的触控笔操作产生的触控事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回当前指向性输入事件中相对XZ平面的角度。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetTiltY(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 获取触控笔绕Z轴旋转的角度。
 *
 * @param event 指向当前UI输入事件的指针。
 * @param rollAngle 触控笔绕Z轴旋转的角度，单位为deg。
 * @return 错误码。
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 17
 */
int32_t OH_ArkUI_PointerEvent_GetRollAngle(const ArkUI_UIInputEvent* event, double* rollAngle);

/**
 * @brief 从指向性输入事件（如触摸事件）中获取触屏区域的宽度。仅适用于手指操作产生的触控事件，这通常是一个圆形区域的半径。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回当前指向性输入事件中触屏区域的宽度，单位为px。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetTouchAreaWidth(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 从指向性输入事件（如触摸事件）中获取触屏区域的高度。仅适用于手指操作产生的触控事件，这通常是一个圆形区域的半径。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回当前指向性输入事件中触屏区域的高度，单位为px。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetTouchAreaHeight(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 获取当前触摸事件是左手点击触发还是右手点击触发。仅在部分触控产品上有效。
 *
 * @note The value is not available immediately upon press. Until the system infers the result, this API will return
 *     <b>NONE</b>. Do not rely on the return value for critical functionality.
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param hand 表示触摸点是左手还是右手。
 * @return 返回结果。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果发生参数异常，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_GetInteractionHand(const ArkUI_UIInputEvent *event, ArkUI_InteractionHand *hand);

/**
 * @brief 获取当前触摸事件是左手点击触发还是右手点击触发。仅在部分触控产品上有效。
 *
 * @note The value is not available immediately upon press. Until the system infers the result,
 *     this API will return <b>NONE</b>. Do not rely on the return value for critical functionality.
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。
 * @param hand 表示触摸点是左手还是右手。
 * @return 返回结果。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果发生参数异常，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_GetInteractionHandByIndex(
    const ArkUI_UIInputEvent *event, int32_t pointerIndex, ArkUI_InteractionHand *hand);

/**
 * @brief 从{@link 指向性输入事件}中获取历史事件数量。本接口支持的指向性输入事件仅包含触摸事件、鼠标事件。历史事件为此次事件与上一次事件之间发生的原始事件，仅在指向性输入事件的移动阶段（即触摸移动或鼠标移动）中适用，
 * 在其他状态中调用返回默认值0。从API version 12开始支持触摸事件，从API version 26.0.0开始支持鼠标事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前历史事件数量。
 * @since 12
 */
uint32_t OH_ArkUI_PointerEvent_GetHistorySize(const ArkUI_UIInputEvent* event);

/**
 * @brief 从指向性输入事件中获取历史事件发生的时间。本接口支持的指向性输入事件仅包含触摸事件、鼠标事件。从API version 12开始支持触摸事件，从API version 26.0.0开始支持鼠标事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回UI输入事件发生的时间，单位为ns。如果参数异常则返回0。
 * @since 12
 */
int64_t OH_ArkUI_PointerEvent_GetHistoryEventTime(const ArkUI_UIInputEvent* event, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件中获取特定历史事件中多点触控的接触点数量。本接口支持的指向性输入事件仅包含触摸事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 特定历史事件中多点触控的接触点数量。
 * @since 12
 */
uint32_t OH_ArkUI_PointerEvent_GetHistoryPointerCount(const ArkUI_UIInputEvent* event, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件的历史点中获取多点触控的接触点标识。本接口支持的指向性输入事件仅包含触摸事件。返回事件发生时，事件触点的唯一标识符，用于区分同类输入设备的多点触控信息。其数值没有除标识触点外的其他含义。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表的序号。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回特定历史事件中的特定接触点标识。
 * @since 12
 */
int32_t OH_ArkUI_PointerEvent_GetHistoryPointerId(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件中获取特定历史事件中特定接触点相对于当前组件左上角的X坐标。本接口支持的指向性输入事件仅包含触摸事件、鼠标事件。对于鼠标事件，当给定的pointerIndex大于0时，始终返回默认值0.0f。从API
 * version 12开始支持触摸事件，从API version 26.0.0开始支持鼠标事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表的序号。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回在指向性输入事件中，特定历史事件内特定接触点相对于当前组件左上角的X坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryX(const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件中获取特定历史事件中特定接触点相对于当前组件左上角的Y坐标。本接口支持的指向性输入事件仅包含触摸事件、鼠标事件。对于鼠标事件，当给定的pointerIndex大于0时，始终返回默认值0.0f。从API
 * version 12开始支持触摸事件，从API version 26.0.0开始支持鼠标事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表的序号。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回在指向性输入事件中，特定历史事件内特定接触点相对于当前组件左上角的Y坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryY(const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件中获取特定历史事件中特定接触点相对于当前应用窗口左上角的X坐标。本接口支持的指向性输入事件仅包含触摸事件、鼠标事件。对于鼠标事件，当给定的pointerIndex大于0时，始终返回默认值0.0f。
 * 从API version 12开始支持触摸事件，从API version 26.0.0开始支持鼠标事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表的序号。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回在指向性输入事件中，特定历史事件内特定接触点相对于当前应用窗口左上角的X坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryWindowX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件中获取特定历史事件中特定接触点相对于当前应用窗口左上角的Y坐标。本接口支持的指向性输入事件仅包含触摸事件、鼠标事件。对于鼠标事件，当给定的pointerIndex大于0时，始终返回默认值0.0f。
 * 从API version 12开始支持触摸事件，从API version 26.0.0开始支持鼠标事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表的序号。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回在指向性输入事件中，特定历史事件内特定接触点相对于当前应用窗口左上角的Y坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryWindowY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件中获取特定历史事件中特定接触点相对于当前屏幕左上角的X坐标。本接口支持的指向性输入事件仅包含触摸事件、鼠标事件。对于鼠标事件，当给定的pointerIndex大于0时，始终返回默认值0.0f。从API
 * version 12开始支持触摸事件，从API version 26.0.0开始支持鼠标事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表的序号。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回在指向性输入事件中，特定历史事件内特定接触点相对于当前屏幕左上角的X坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryDisplayX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件中获取特定历史事件中特定接触点相对于当前屏幕左上角的Y坐标。本接口支持的指向性输入事件仅包含触摸事件、鼠标事件。对于鼠标事件，当给定的pointerIndex大于0时，始终返回默认值0.0f。从API
 * version 12开始支持触摸事件，从API version 26.0.0开始支持鼠标事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表的序号。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回在指向性输入事件中，特定历史事件内特定接触点相对于当前屏幕左上角的Y坐标，单位为px。如果参数异常则返回0.0f。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryDisplayY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从给定指针索引和历史记录索引的指向性输入事件中获取历史事件中相对于全局显示的特定触摸点的X坐标。本接口支持的指向性输入事件仅包含触摸事件、鼠标事件。只能从指针事件中获取位置信息，对于鼠标事件，
 * 当给定的pointerIndex大于0时，始终返回默认值0.0f。从API version 20开始支持触摸事件，从API version 26.0.0开始支持鼠标事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。有效值范围[0,  {@link OH_ArkUI_PointerEvent_GetPointerCount()} - 1]
 * @param historyIndex 表示要返回的历史值，必须小于{@link OH_ArkUI_PointerEvent_GetHistorySize}。
 * @return 返回在指向性输入事件中，特定历史事件内特定接触点相对于全局显示的X坐标，单位为px。如果发生任何参数错误，则返回0.0f。
 * @since 20
 */
float OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从给定指针索引和历史记录索引的指向性输入事件中获取历史事件中相对于全局显示的特定触摸点的Y坐标。本接口支持的指向性输入事件仅包含触摸事件、鼠标事件。只能从指针事件中获取位置信息，对于鼠标事件，
 * 当给定的pointerIndex大于0时，始终返回默认值0.0f。从API version 20开始支持触摸事件，从API version 26.0.0开始支持鼠标事件。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。有效值范围[0, {@link OH_ArkUI_PointerEvent_GetPointerCount()} - 1]
 * @param historyIndex 表示要返回的历史值，必须小于{@link OH_ArkUI_PointerEvent_GetHistorySize}。
 * @return 返回在指向性输入事件中，特定历史事件内特定接触点相对于全局显示的Y坐标，单位为px。如果发生任何参数错误，则返回0.0f。
 * @since 20
 */
float OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件（如触摸事件）中获取特定历史事件中的触屏压力。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回当前指向性输入事件产生的触屏压力。取值范围为[0, 1]，压感大小与数值正相关。如果参数异常则返回默认值0.0f。在部分设备中，由于设备的硬件参数配置不同，可能会返回大于1的值。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryPressure(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件（如触摸事件）中获取特定历史事件中的相对YZ平面的角度，取值的范围[-90, 90]，单位为deg，其中正值是向右倾斜。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回当前指向性输入事件中相对YZ平面的角度。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryTiltX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件（如触摸事件）中获取特定历史事件中的相对XZ平面的角度，值的范围[-90, 90]，单位为deg，其中正值是向下倾斜。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回当前指向性输入事件中相对XZ平面的角度。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryTiltY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件（如触摸事件）中获取特定历史事件中的触屏区域的宽度。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回当前指向性输入事件中触屏区域的宽度，单位为px。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 从指向性输入事件（如触摸事件）中获取特定历史事件中的触屏区域的高度。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @param historyIndex 表示历史事件数据列表的序号。
 * @return 返回当前指向性输入事件中触屏区域的高度，单位为px。
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief 获取当前轴事件的垂直滚动轴的值。通常由鼠标滚轮，或用户在触控板上双指竖向滑动产生。当通过鼠标滚动触发时：1.上报的数值单位为角度，为单次滚动角度增量，非滚动总量；2.上报的数值已与用户配置的放大系数
 * {@link OH_ArkUI_AxisEvent_GetScrollStep}叠加运算；3.数值的正负代表方向，向前滚动鼠标滚轮时上报数值为负数，向后滚动鼠标滚轮时上报数值为正数；当通过触控板双指竖向滑动时：1.
 * 上报的数值单位为PX，为单次滚动增量，非滚动总量；2.上报的数值不受用户配置的放大系数{@link OH_ArkUI_AxisEvent_GetScrollStep}影响；3.数值的正负代表方向，双指从上往下滑动时上报数值为负数，
 * 双指从下往上滑动时上报数值为正数；4.方向会受系统设置中"自然滚动"配置的影响。通常情况下，垂直滚动轴事件只能驱动竖向的滑动手势响应，但当鼠标指针下命中的可滑动手势里，如果可响应的方向都是一致的，
 * 那么垂直滚动轴事件可以驱动这些滑动手势得到响应，即使这些手势所定义的方向是横向的。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前轴事件的垂直滚动轴的值，如果参数异常则返回0.0。
 * @since 12
 */
double OH_ArkUI_AxisEvent_GetVerticalAxisValue(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取当前轴事件的水平滚动轴的值，通过在触控板上双指横向滑动产生。
 *
 * @note
 * 1. The reported value is in px and represents the incremental scroll amount, not the total scroll amount.
 * 2. The reported value does not include the user's scroll step configuration.
 * 3. The sign of the value indicates the direction: positive for swiping right and negative for swiping left.
 * 4. The direction is affected by the system settings for natural scrolling.
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前轴事件的水平滚动轴的值，如果参数异常则返回0.0。
 * @since 12
 */
double OH_ArkUI_AxisEvent_GetHorizontalAxisValue(const ArkUI_UIInputEvent* event);

/**
 * 获取当前轴事件的捏合轴缩放的值。通过触控板双指缩放/捏合操作产生。上报的scale数值，为相对于初始状态时的当前scale值。初始状态为系统识别到用户通过触控板发生了捏合操作时的两指位置状态，此时的scale数值为1.0。
 * 在手指抬起前的本次捏合操作过程中，所上报的scale数值均将初始状态作为参考系，从初始状态往中心捏合，则上报的scale会从1.0逐步往0.0缩小；当从初始化状态往外扩大双指距离时，会从1.0逐步变大。
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前轴事件的捏合轴缩放的值，如果参数异常则返回0.0。
 * @since 12
 */
double OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取当前轴事件的操作类型。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回当前轴事件的操作类型，取值可参考{@link anonymous7}。当输入非轴事件时，默认返回0。
 * @since 15
 */
int32_t OH_ArkUI_AxisEvent_GetAxisAction(const ArkUI_UIInputEvent* event);

/**
 * @brief 检测此轴事件是否包含指定的轴类型。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param axis 表示轴事件的轴类型{@link UI_AXIS_TYPE_XXX}。
 * @return 返回此轴事件是否包含指定的轴类型。返回true表示包含指定的轴类型，返回false表示不包含指定的轴类型。
 * @since 22
 */
int32_t OH_ArkUI_AxisEvent_HasAxis(const ArkUI_UIInputEvent* event, int32_t axis);

/**
 * @brief 配置触摸测试模式。仅适用于接收基础事件的场景，如使用NODE_ON_TOUCH接收触摸事件场景。对于通过{@link OH_ArkUI_GestureEvent_GetRawInputEvent}
 * 接口从一个手势事件中获取到的ArkUI_UIInputEvent对象，无法使用该接口。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param mode 指定触摸测试模式，参数类型{@link HitTestMode}。
 * @return 返回执行的状态代码。
 * @since 12
 */
int32_t OH_ArkUI_PointerEvent_SetInterceptHitTestMode(const ArkUI_UIInputEvent* event, HitTestMode mode);

/**
 * @brief 获取鼠标事件的按键类型的值。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回鼠标按键类型，取值由{@link anonymous5}枚举定义，但在非鼠标事件中调用时返回值为-1。
 * @since 12
 */
int32_t OH_ArkUI_MouseEvent_GetMouseButton(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取鼠标事件的鼠标动作类型的值。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回鼠标动作类型，取值由{@link anonymous4}枚举定义，但在非鼠标事件中调用时返回值为-1。
 * @since 12
 */
int32_t OH_ArkUI_MouseEvent_GetMouseAction(const ArkUI_UIInputEvent* event);

/**
 * @brief 设置是否阻止事件冒泡。仅适用于接收基础事件的场景，如使用NODE_ON_TOUCH接收触摸事件场景，不适用于轴事件。对于通过{@link OH_ArkUI_GestureEvent_GetRawInputEvent}
 * 接口从一个手势事件中获取到的ArkUI_UIInputEvent对象，无法使用该接口。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param stopPropagation 表示是否阻止事件冒泡。true表示阻止事件冒泡，false表示不阻止事件冒泡。
 * @return 返回执行的状态代码。返回0表示设置成功，如果返回401，表示返回失败，可能的原因是参数异常，例如event是一个空指针。
 * @since 12
 */
int32_t OH_ArkUI_PointerEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation);

/**
 * @brief 获取当前UI输入事件的设备ID。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return 当前UI输入事件的设备ID。
 * @since 14
 */
int32_t OH_ArkUI_UIInputEvent_GetDeviceId(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取所有按下的按键，当前只支持按键事件。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param pressedKeyCodes 输出参数，表示所有按下键的数组，指向的内存空间需要调用者申请。
 * @param length 作为输入参数表示传入的pressedKeyCodes数组长度，作为输出参数表示实际按下按键的个数。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH} 内存分配不足。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 14
 */
int32_t OH_ArkUI_UIInputEvent_GetPressedKeys(
    const ArkUI_UIInputEvent* event, int32_t* pressedKeyCodes, int32_t* length);

/**
 * @brief 获取焦点轴事件的轴值。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param axis 焦点轴事件的轴类型，取值可参考{@link anonymous6}。
 * @return 焦点轴事件的轴值，如果参数异常则返回0.0。
 * @since 15
 */
double OH_ArkUI_FocusAxisEvent_GetAxisValue(const ArkUI_UIInputEvent* event, int32_t axis);

/**
 * @brief 设置是否阻止焦点轴事件冒泡。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param stopPropagation 表示是否阻止事件冒泡。true表示阻止事件冒泡，false表示不阻止事件冒泡。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常。
 * @since 15
 */
int32_t OH_ArkUI_FocusAxisEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation);

/**
* @brief 获取事件命中的组件的宽度。
*
* @param event 指向ArkUI_UIInputEvent对象的指针。
* @return 返回事件命中的组件的宽度，单位为px；如果发生任何参数错误，则返回 0.0f。
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetWidth(const ArkUI_UIInputEvent* event);

/**
* @brief 获取事件命中的组件的高度。
*
* @param event 指向ArkUI_UIInputEvent对象的指针。
* @return 返回事件命中的组件的高度，单位为px；如果发生任何参数错误，则返回 0.0f。
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetHeight(const ArkUI_UIInputEvent* event);

/**
* @brief 获取事件命中的组件的X坐标。
*
* @param event 指向ArkUI_UIInputEvent对象的指针。
* @return 返回事件命中的组件的X坐标，单位为px；如果发生任何参数错误，则返回 0.0f。
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetPositionX(const ArkUI_UIInputEvent* event);

/**
* @brief 获取事件命中的组件的Y坐标。
*
* @param event 指向ArkUI_UIInputEvent对象的指针。
* @return 返回事件命中的组件的Y坐标，单位为px；如果发生任何参数错误，则返回 0.0f。
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetPositionY(const ArkUI_UIInputEvent* event);

/**
* @brief 获取事件命中的组件的全局X坐标。
*
* @param event 指向ArkUI_UIInputEvent对象的指针。
* @return 返回事件命中的组件的全局X坐标，单位为px；如果发生任何参数错误，则返回 0.0f。
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event);

/**
* @brief 获取事件命中的组件的全局Y坐标。
*
* @param event 指向ArkUI_UIInputEvent对象的指针。
* @return 返回事件命中的组件的全局Y坐标，单位为px；如果发生任何参数错误，则返回 0.0f。
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event);

/**
* @brief 获取鼠标是否悬浮在当前组件上
*
* @param event ArkUI_UIInputEvent事件指针。
* @return 如果鼠标悬浮在当前组件上则返回true。
*     <br>如果鼠标没有悬浮在当前组件上，返回false
* @since 17
*/
bool OH_ArkUI_HoverEvent_IsHovered(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取UI输入事件的修饰键状态。该接口会通过keys传出当前事件发生时所有修饰键的状态，你可以通过与{@link ArkUI_ModifierKeyName}中定义的修饰键类型进行位计算操作获取哪些键处于按下状态。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param keys 返回当前处于按下状态的修饰键组合，应用可通过位运算进行判断。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 函数参数异常。
 * @since 17
 */
int32_t OH_ArkUI_UIInputEvent_GetModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys);

/**
* @brief 获取指定触点的按下时间。仅对触摸事件有效。
*
 * @param event ArkUI_UIInputEvent事件指针。
 * @param pointerIndex 指示多点触控数据列表中目标触控点的索引。
 * @return 返回特定触摸点的按下时间，单位为ns；如果发生任何参数错误，则返回0。
 * @since 15
 */
int64_t OH_ArkUI_PointerEvent_GetPressedTimeByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief 获取鼠标设备在二维平面X轴的移动增量。其数值为鼠标硬件的原始移动数据，使用物理世界中鼠标移动的距离单位进行表示。上报数值由硬件本身决定，并非屏幕的物理/逻辑像素。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return 返回鼠标设备在二维平面X轴的移动增量，使用物理世界中鼠标移动的距离单位进行表示；如果发生任何参数错误，则返回0.0f。
 *     **说明：** API版本26.0.0之前，返回值并非鼠标硬件的原始移动数据，而是原始数据缩小了X倍，X为系统的显示大小比例。API版本26.0.0开始，返回值为鼠标硬件的原始移动数据。
 * @since 15
 */
float OH_ArkUI_MouseEvent_GetRawDeltaX(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取鼠标设备在二维平面Y轴的移动增量。其数值为鼠标硬件的原始移动数据，使用物理世界中鼠标移动的距离单位进行表示。上报数值由硬件本身决定，并非屏幕的物理/逻辑像素。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return 返回鼠标设备在二维平面Y轴的移动增量，使用物理世界中鼠标移动的距离单位进行表示；如果发生任何参数错误，则返回0.0f。
 *     **说明：** API版本26.0.0之前，返回值并非鼠标硬件的原始移动数据，而是原始数据缩小了X倍，X为系统的显示大小比例。API版本26.0.0开始，返回值为鼠标硬件的原始移动数据。
 * @since 15
 */
float OH_ArkUI_MouseEvent_GetRawDeltaY(const ArkUI_UIInputEvent* event);

/**
 * @brief 从鼠标事件中获取按下的按键。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param pressedButtons 指示按下按键的列表。需要先创建一个int数组，用来储存按下的按键，按键的值请参考{@link anonymous5}。
 * @param length 指示列表数组的总长度。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果传入的缓冲区大小异常，则返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}。
 * @since 15
 */
int32_t OH_ArkUI_MouseEvent_GetPressedButtons(
    const ArkUI_UIInputEvent* event, int32_t* pressedButtons, int32_t* length);

/**
 * @brief 获取发生UI输入事件的屏幕ID。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return 返回屏幕ID；如果发生任何参数错误，则返回0。
 * @since 15
 */
int32_t OH_ArkUI_UIInputEvent_GetTargetDisplayId(const ArkUI_UIInputEvent* event);

/**
 * @brief 设置是否使能轴事件冒泡。默认不会进行冒泡传递，仅发送给第一个可响应轴事件的控件。可在接收到轴事件时，主动使能冒泡传递，以便当前事件可以继续传递给响应链上的下一个可响应轴事件的祖先组件处理。
 * 不支持对从手势事件中获取到的轴事件进行设置。
 *
 * @param event 表示指向当前 UI 输入事件的指针。
 * @param propagation 表示是否激活事件冒泡。true表示激活事件冒泡，false表示不激活事件冒泡。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常。
 * @since 17
 */
int32_t OH_ArkUI_AxisEvent_SetPropagation(const ArkUI_UIInputEvent* event, bool propagation);

/**
 * @brief 获取滚动轴事件的滚动步长系数，适用于鼠标滚轮产生的轴事件。这个值可以告诉你用户所配置的滚动放大系数。
 *
 * @param event 指向 ArkUI_UIInputEvent事件指针。
 * @return 返回鼠标滚轮轴滚动步长配置。在非鼠标事件返回默认值0。
 * @since 17
 */
int32_t OH_ArkUI_AxisEvent_GetScrollStep(const ArkUI_UIInputEvent* event);

/**
 * @brief 基于原始事件指针创建克隆事件指针。仅对触摸事件有效。
 *
 * @param event ArkUI_UIInputEvent克隆事件指针。
 * @param clonedEvent ArkUI_UIInputEvent克隆事件指针。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_CreateClonedEvent(const ArkUI_UIInputEvent* event, ArkUI_UIInputEvent** clonedEvent);

/**
 * @brief 销毁克隆事件指针。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_DestroyClonedEvent(const ArkUI_UIInputEvent* event);

/**
 * @brief 设置指向性事件相对于当前组件左上角的X坐标和Y坐标。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param x 当前指向性输入事件相对于当前组件左上角的X坐标，单位为px。
 * @param y 当前指向性输入事件相对于当前组件左上角的Y坐标，单位为px。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(const ArkUI_UIInputEvent* event, float x, float y);

/**
 * @brief 设置指向性事件特有接触点相对于当前组件左上角的X坐标和Y坐标。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param x 当前指向性输入事件相对于当前组件左上角的X坐标，单位为px。
 * @param y 当前指向性输入事件相对于当前组件左上角的Y坐标，单位为px。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(
    const ArkUI_UIInputEvent* event, float x, float y, int32_t pointerIndex);

/**
 * @brief 设置当前带有指向性的克隆输入事件的事件类型。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param actionType ArkUI_UIInputEvent克隆事件类型。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventActionType(const ArkUI_UIInputEvent* event, int32_t actionType);

/**
 * @brief 设置当前带有指向性的克隆输入事件的触摸点ID。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param fingerId 触发当前事件指针的触摸点ID。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(const ArkUI_UIInputEvent* event, int32_t fingerId);

/**
 * @brief 设置带有指向性的克隆输入事件特定接触点的触摸点ID。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param fingerId 指向性的输入事件特定接触点的触摸点ID。
 * @param pointerIndex 表示多点触控数据列表中的序号。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(
    const ArkUI_UIInputEvent* event, int32_t fingerId, int32_t pointerIndex);

/**
 * @brief 创建指定事件的克隆事件。该接口适用于触摸事件、鼠标事件和轴事件。
 *
 * @param event ArkUI_UIInputEvent克隆事件指针。
 * @param clonedEvent ArkUI_UIInputEvent克隆事件指针。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_PointerEvent_CreateClonedPointerEvent(const ArkUI_UIInputEvent* event,
    ArkUI_UIInputEvent** clonedEvent);

/**
 * @brief 创建新事件，不克隆现有事件。该接口适用于触摸事件、鼠标事件和轴事件。
 *
 * @param event 指向新的ArkUI_UIInputEvent对象的指针。
 * @param type ArkUI_UIInputEvent的事件类型。支持取值{@link ARKUI_UIINPUTEVENT_TYPE_TOUCH}、{@link ARKUI_UIINPUTEVENT_TYPE_AXIS}和
 *     {@link ARKUI_UIINPUTEVENT_TYPE_MOUSE}。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_PointerEvent_CreatePointerEvent(ArkUI_UIInputEvent** event, ArkUI_UIInputEvent_Type type);

/**
 * @brief 销毁克隆事件指针。该接口适用于触摸事件、鼠标事件和轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_PointerEvent_DestroyClonedPointerEvent(const ArkUI_UIInputEvent* event);

/**
 * @brief 设置克隆事件的动作类型。该接口适用于触摸事件、鼠标事件和轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param type 克隆事件的类型，包括触摸事件的{@link UI_TOUCH_EVENT_ACTION}，鼠标事件的{@link UI_MOUSE_EVENT_ACTION}，轴事件的
 *     {@link UI_AXIS_EVENT_ACTION}。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetActionType(const ArkUI_UIInputEvent* event, int32_t type);

/**
 * @brief 设置克隆事件的源类型。该接口适用于触摸事件、鼠标事件和轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param sourceType 克隆事件的源类型。取值范围为[0,5]的整数，其中0表示未知，1表示鼠标，2表示触屏，4表示键盘，5表示手柄。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetSourceType(const ArkUI_UIInputEvent* event, int32_t sourceType);

/**
 * @brief 设置克隆事件的工具类型。该接口适用于触摸事件、鼠标事件和轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param toolType 克隆事件的工具类型。由{@link UI_INPUT_EVENT_TOOL_TYPE_XXX}枚举定义。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetToolType(const ArkUI_UIInputEvent* event, int32_t toolType);

/**
 * @brief 设置克隆事件应用于触摸屏的压力。该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param pressure 应用于触摸屏的压力，取值范围为[0,1]中的任意数值，部分设备中可能大于1。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetPressure(const ArkUI_UIInputEvent* event, float pressure);

/**
 * @brief 设置克隆事件指定触摸点应用于触摸屏的压力。该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param pressure 应用于触摸屏的压力，取值范围为[0,1]中的任意数值，部分设备中可能大于1。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetPressureByIndex(const ArkUI_UIInputEvent* event, float pressure,
    int32_t pointerIndex);

/**
 * @brief 设置克隆UI输入事件发生的时间。该接口适用于触摸事件、鼠标事件和轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param timestamp 克隆UI输入事件发生的时间，单位为ns。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetEventTime(const ArkUI_UIInputEvent* event, int64_t timestamp);

/**
 * @brief 设置触发克隆UI输入事件的设备ID。该接口适用于触摸事件、鼠标事件和轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param deviceId 触发克隆UI输入事件的设备ID，可用{@link OH_ArkUI_UIInputEvent_GetDeviceId}接口获取。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetDeviceId(const ArkUI_UIInputEvent* event, int32_t deviceId);

/**
 * @brief 设置克隆UI输入事件发生的屏幕ID。该接口适用于触摸事件、鼠标事件和轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param targetDisplayId 克隆UI输入事件发生的屏幕ID，可用{@link OH_ArkUI_UIInputEvent_GetTargetDisplayId}接口获取。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetTargetDisplayId(const ArkUI_UIInputEvent* event, int32_t targetDisplayId);

/**
 * @brief 设置克隆指针事件的触摸点ID。该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param fingerId 触发事件的触摸点ID，可以通过{@link OH_ArkUI_PointerEvent_GetPointerId}接口获取。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetChangedFingerId(const ArkUI_UIInputEvent* event, int32_t fingerId);

/**
 * @brief 设置克隆事件特定接触点的触摸点ID。该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param fingerId 特定接触点的触摸点ID，可以通过{@link OH_ArkUI_PointerEvent_GetChangedPointerId}接口获取。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetFingerIdByIndex(
    const ArkUI_UIInputEvent* event, int32_t fingerId, int32_t pointerIndex);

/**
 * @brief 设置克隆事件相对于当前窗口左上角的X坐标和Y坐标。该接口适用于触摸事件、鼠标事件和轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param x 事件相对于当前窗口左上角的X坐标，单位为px。
 * @param y 事件相对于当前窗口左上角的Y坐标，单位为px。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetChangedWindowPosition(const ArkUI_UIInputEvent* event, float x, float y);

/**
 * @brief 设置克隆事件特定接触点相对于当前窗口左上角的X坐标和Y坐标。该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param x 事件相对于当前窗口左上角的X坐标，单位为px。
 * @param y 事件相对于当前窗口左上角的Y坐标，单位为px。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetWindowPositionByIndex(
    const ArkUI_UIInputEvent* event, float x, float y, int32_t pointerIndex);

/**
 * @brief 设置克隆事件相对于当前屏幕左上角的X坐标和Y坐标。该接口适用于触摸事件、鼠标事件和轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param x 事件相对于当前屏幕左上角的X坐标，单位为px。
 * @param y 事件相对于当前屏幕左上角的Y坐标，单位为px。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetChangedScreenPosition(const ArkUI_UIInputEvent* event, float x, float y);

/**
 * @brief 设置克隆事件特定接触点相对于当前屏幕左上角的X坐标和Y坐标。该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param x 事件相对于当前屏幕左上角的X坐标，单位为px。
 * @param y 事件相对于当前屏幕左上角的Y坐标，单位为px。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetScreenPositionByIndex(
    const ArkUI_UIInputEvent* event, float x, float y, int32_t pointerIndex);

/**
 * @brief 设置克隆事件在{@link 全局坐标系}的坐标。该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param x 事件相对于全局显示的X坐标，单位为px。
 * @param y 事件相对于全局显示的Y坐标，单位为px。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetChangedGlobalDisplayPosition(const ArkUI_UIInputEvent* event, float x, float y);

/**
 * @brief 设置克隆事件在{@link 全局坐标系}的坐标。该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param x 事件相对于全局显示的X坐标，单位为px。
 * @param y 事件相对于全局显示的Y坐标，单位为px。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetGlobalDisplayPositionByIndex(
    const ArkUI_UIInputEvent* event, float x, float y, int32_t pointerIndex);

/**
 * @brief 设置事件处理会话的唯一句柄。该句柄必须用于对该事件的任何进一步操作。对于给定的手指，同一时间只有一个具有此句柄的事件处于活动状态。该接口适用于触摸事件、鼠标事件和轴事件。只有通过
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和{@link OH_ArkUI_PointerEvent_CreatePointerEvent}
 * 接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param eventHandleId 事件处理会话的唯一句柄。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetHandleId(const ArkUI_UIInputEvent* event, int32_t eventHandleId);

/**
 * @brief 设置克隆事件相对于XZ平面和YZ平面的倾斜角度。取值范围为[-90, 90]，其中正值表示向右倾斜。该接口适用于触摸事件。只有通过
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和{@link OH_ArkUI_PointerEvent_CreatePointerEvent}
 * 接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param tiltX 克隆事件相对于YZ平面的倾斜角度，单位为deg。
 * @param tiltY 克隆事件相对于XZ平面的倾斜角度，单位为deg。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetTiltAngle(const ArkUI_UIInputEvent* event, float tiltX, float tiltY);

/**
 * @brief 设置克隆事件触控笔绕Z轴的旋转角度。该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param rollAngle 克隆事件触控笔绕Z轴的旋转角度，单位为deg。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetRollAngle(const ArkUI_UIInputEvent* event, float rollAngle);

/**
 * @brief 设置克隆事件中所有按下的按键。该接口适用于触摸事件、鼠标事件和轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param pressedKeyCodes 所有按下的按键键值数组，键值取值为{@link ArkUI_KeyCode}。
 * @param length 按下的按键数组长度。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetPressedKeys(
    const ArkUI_UIInputEvent* event, int32_t* pressedKeyCodes, int32_t length);

/**
 * @brief 设置克隆事件的手指接触区域的宽度和高度，该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param width 克隆事件的接触区域的宽度，单位为px。
 * @param height 克隆事件的接触区域的高度，单位为px。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetChangedTouchArea(const ArkUI_UIInputEvent* event, float width, float height);

/**
 * @brief 设置克隆事件特定接触点的手指接触区域的宽度和高度，该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param width 克隆事件的接触区域的宽度，单位为px。
 * @param height 克隆事件的接触区域的高度，单位为px。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetTouchAreaByIndex(const ArkUI_UIInputEvent* event, float width, float height,
    int32_t pointerIndex);

/**
 * @brief 设置克隆事件是左手或右手触发。该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param hand 触摸点是左手还是右手，{@link ARKUI_EVENT_HAND_LEFT}为左手，{@link ARKUI_EVENT_HAND_RIGHT}为右手。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetChangedInteractionHand(const ArkUI_UIInputEvent* event, int32_t hand);

/**
 * @brief 设置克隆事件特定接触点由左手或右手触发。该接口适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param hand 触摸点是左手还是右手，{@link ARKUI_EVENT_HAND_LEFT}为左手，{@link ARKUI_EVENT_HAND_RIGHT}为右手。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetInteractionHandByIndex(const ArkUI_UIInputEvent* event,
    int32_t hand, int32_t pointerIndex);

/**
 * @brief 设置克隆事件指定触摸点的按下时间。该接口仅适用于触摸事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param pressedTime 指定触摸点的按下时间，单位为ns。
 * @param pointerIndex 表示多点触控数据列表中目标触控点的索引。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetPressedTimeByIndex(const ArkUI_UIInputEvent* event,
    int64_t pressedTime, int32_t pointerIndex);

/**
 * 设置克隆事件的捏合轴缩放值。该接口仅适用于轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 * @param event ArkUI_UIInputEvent事件指针。
 * @param pinchAxisScaleValue 捏合轴的缩放值，单位为vp，取值[0, +∞)。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetPinchAxisScaleValue(const ArkUI_UIInputEvent* event,
    double pinchAxisScaleValue);

/**
 * 设置克隆事件水平滚动轴的值。该接口仅适用于轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 * @param event ArkUI_UIInputEvent事件指针。
 * @param horizontalAxisScaleValue 水平滚动轴的值，单位为vp。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetHorizontalAxisScaleValue(const ArkUI_UIInputEvent* event,
    double horizontalAxisScaleValue);

/**
 * 设置克隆事件垂直滚动轴的值。该接口仅适用于轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 * @param event ArkUI_UIInputEvent事件指针。
 * @param verticalAxisScaleValue 垂直滚动轴的值，单位为vp。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetVerticalAxisScaleValue(const ArkUI_UIInputEvent* event,
    double verticalAxisScaleValue);

/**
 * @brief 设置克隆事件的滚动步长系数。该接口仅适用于轴事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param scrollStep 克隆事件的滚动步长系数，取值为[0, 65535]的整数。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetScrollStep(const ArkUI_UIInputEvent* event, int32_t scrollStep);

/**
 * @brief 设置克隆事件的按钮类型值。该接口仅适用于鼠标事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param button 克隆事件的鼠标按钮类型，取值由{@link anonymous5}枚举定义。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetMouseButton(const ArkUI_UIInputEvent* event, int32_t button);

/**
 * @brief 设置鼠标设备在二维平面X轴的移动增量。其数值为鼠标硬件的原始移动数据，使用物理世界中鼠标移动的距离单位进行表示。该接口仅适用于鼠标事件。只有通过
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和{@link OH_ArkUI_PointerEvent_CreatePointerEvent}
 * 接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param rawDeltaX 鼠标位置相对于之前上报的鼠标事件中位置的X轴偏移量。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetRawDeltaX(const ArkUI_UIInputEvent* event, float rawDeltaX);

/**
 * @brief 设置鼠标设备在二维平面Y轴的移动增量。其数值为鼠标硬件的原始移动数据，使用物理世界中鼠标移动的距离单位进行表示。该接口仅适用于鼠标事件。只有通过
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和{@link OH_ArkUI_PointerEvent_CreatePointerEvent}
 * 接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param rawDeltaY 鼠标位置相对于之前上报的鼠标事件中位置的Y轴偏移量。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetRawDeltaY(const ArkUI_UIInputEvent* event, float rawDeltaY);

/**
 * @brief 设置克隆事件的按下的按键。该接口仅适用于鼠标事件。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @param pressedButtons 按下的按键数组，按键的值请参考{@link anonymous5}
 * @param length 按下的按键数组长度。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果事件类型不支持，则返回{@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetPressedButtons(
    const ArkUI_UIInputEvent* event, const int32_t* pressedButtons, int32_t length);

/**
 * @brief 使用指定的竞争策略将克隆事件发送到特定节点。只有通过{@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}和
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}接口创建的ArkUI_UIInputEvent对象才能使用此接口。
 *
 * @param node 目标节点。
 * @param event ArkUI_UIInputEvent事件指针。
 * @param strategy 竞争策略，取值为{@link ArkUI_CompetitionStrategy}。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果组件状态异常，则返回{@link ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL}。
 *     <br>如果未命中可响应事件的组件，则返回{@link ARKUI_ERROR_CODE_POST_CLONED_NO_COMPONENT_HIT_TO_RESPOND_TO_THE_EVENT}。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_PointerEvent_PostClonedEventWithStrategy(ArkUI_NodeHandle node,
    const ArkUI_UIInputEvent* event, ArkUI_CompetitionStrategy strategy);

/**
 * @brief 转发克隆事件到特定节点。
 *
 * @param node 目标节点。
 * @param event ArkUI_UIInputEvent事件指针。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果输入的事件指针不是克隆事件指针，则返回{@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT}。
 *     <br>如果组件状态异常，则返回{@link ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL}。
 *     <br>如果未命中可响应事件的组件，则返回{@link ARKUI_ERROR_CODE_POST_CLONED_NO_COMPONENT_HIT_TO_RESPOND_TO_THE_EVENT}。
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_PostClonedEvent(ArkUI_NodeHandle node, const ArkUI_UIInputEvent* event);

/**
 * @brief 调用该方法获取最近一次UIInput相关方法的执行情况。通常情况下不需要使用该方法，仅在返回值结果不确定是否异常时使用。
 *
 * @return 返回最近一次调用UIInput方法产生的结果代码。
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_UIInputEvent_GetLatestStatus();

/**
 * @brief 从组件事件中获取惯性滚动轴事件，仅当用户在触摸板上使用双指滑动一定距离并快速抬手，且指针位置下存在注册了{@link NODE_ON_COASTING_AXIS_EVENT}事件的组件时，才能获取到有效事件。在从
 * {@link ArkUI_NodeEvent}对象获取到{@link ArkUI_UIInputEvent}对象后调用此方法。
 *
 * @param event ArkUI_UIInputEvent事件指针。
 * @return 返回指向惯性滚动轴事件的指针，如果未发生任何惯性滚动轴事件或发生任何参数错误，则返回空指针。
 * @since 22
 */
ArkUI_CoastingAxisEvent* OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(ArkUI_UIInputEvent* event);

/**
 * @brief 获取惯性滚动轴事件发生的时间。
 *
 * @param event ArkUI_CoastingAxisEvent事件指针。
 * @return 返回UI输入事件发生的时间，单位为ns；如果发生任何参数错误则返回0。
 * @since 22
 */
int64_t OH_ArkUI_CoastingAxisEvent_GetEventTime(ArkUI_CoastingAxisEvent* event);

/**
 * @brief 获取惯性滚动轴事件发生时的滚动阶段。
 *
 * @param event ArkUI_CoastingAxisEvent事件指针。
 * @return 返回事件阶段，参见{@link ArkUI_CoastingAxisEventPhase}。
 *     <br>如果发生任何参数错误则返回ARKUI_COASTING_AXIS_EVENT_PHASE_NONE。
 * @since 22
 */
ArkUI_CoastingAxisEventPhase OH_ArkUI_CoastingAxisEvent_GetPhase(ArkUI_CoastingAxisEvent* event);

/**
 * @brief 获取惯性滚动轴事件水平方向的增量值。单位为px，表示为单次滚动增量，非滚动总量。数值的正负代表方向，双指从左往右滑动时为负数，双指从右往左滑动时为正数。
 *
 * @param event ArkUI_CoastingAxisEvent事件指针。
 * @return 返回X轴增量值，以px为单位；如果发生任何参数错误则返回0.0f。
 * @since 22
 */
float OH_ArkUI_CoastingAxisEvent_GetDeltaX(ArkUI_CoastingAxisEvent* event);

/**
 * @brief 获取惯性滚动轴事件垂直方向的增量值。单位为px，表示为单次滚动增量，非滚动总量。数值的正负代表方向，双指从上往下滑动时为负数，双指从下往上滑动时为正数。
 *
 * @param event ArkUI_CoastingAxisEvent事件指针。
 * @return 返回Y轴增量值，以px为单位；如果发生任何参数错误则返回0.0f。
 * @since 22
 */
float OH_ArkUI_CoastingAxisEvent_GetDeltaY(ArkUI_CoastingAxisEvent* event);

/**
 * @brief 设置惯性滚动轴事件是否启用冒泡，默认禁止冒泡。
 *
 * @param event ArkUI_CoastingAxisEvent事件指针。
 * @param propagation 是否启用事件冒泡。true表示启用，false表示禁用。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 22
 */
int32_t OH_ArkUI_CoastingAxisEvent_SetPropagation(ArkUI_CoastingAxisEvent* event, bool propagation);

/**
 * @brief 获取触摸测试信息项数组。
 *
 * @param info 指向触摸测试信息的指针。
 * @param array 指向触摸测试信息项数组的指针。
 * @param size 触摸测试信息项数组的大小。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TouchTestInfo_GetTouchTestInfoList(ArkUI_TouchTestInfo* info,
    ArkUI_TouchTestInfoItemArray* array, int32_t* size);

/**
 * @brief 从触摸测试信息项中获取相对于子组件左上角的X坐标，单位为px。
 *
 * @param info 指向触摸测试信息项的指针。
 * @return 相对于子组件左上角的X坐标，单位为px。若参数错误，返回0.0f。
 * @since 22
 */
float OH_ArkUI_TouchTestInfoItem_GetX(const ArkUI_TouchTestInfoItem* info);

/**
 * @brief 从触摸测试信息项中获取相对于子组件左上角的Y坐标，单位为px。
 *
 * @param info 指向触摸测试信息项的指针。
 * @return 相对于子组件左上角的Y坐标，单位为px。若参数错误，返回0.0f。
 * @since 22
 */
float OH_ArkUI_TouchTestInfoItem_GetY(const ArkUI_TouchTestInfoItem* info);

/**
 * @brief 从触摸测试信息项中获取相对于当前应用窗口左上角的X坐标，单位为px。
 *
 * @param info 指向触摸测试信息项的指针。
 * @return 相对于当前应用窗口左上角的X坐标，单位为px。若参数错误，返回0.0f。
 * @since 22
 */
float OH_ArkUI_TouchTestInfoItem_GetWindowX(const ArkUI_TouchTestInfoItem* info);

/**
 * @brief 从触摸测试信息项中获取相对于当前应用窗口左上角的Y坐标，单位为px。
 *
 * @param info 指向触摸测试信息项的指针。
 * @return 相对于当前应用窗口左上角的Y坐标，单位为px。若参数错误，返回0.0f。
 * @since 22
 */
float OH_ArkUI_TouchTestInfoItem_GetWindowY(const ArkUI_TouchTestInfoItem* info);

/**
 * @brief 从触摸测试信息项中获取相对于父组件左上角的X坐标，单位为px。
 *
 * @param info 指向触摸测试信息项的指针。
 * @return 相对于父组件左上角的X坐标，单位为px。若参数错误，返回0.0f。
 * @since 22
 */
float OH_ArkUI_TouchTestInfoItem_GetXRelativeToParent(const ArkUI_TouchTestInfoItem* info);

/**
 * @brief 从触摸测试信息项中获取相对于父组件左上角的Y坐标，单位为px。
 *
 * @param info 指向触摸测试信息项的指针。
 * @return 相对于父组件左上角的Y坐标，单位为px。若参数错误，返回0.0f。
 * @since 22
 */
float OH_ArkUI_TouchTestInfoItem_GetYRelativeToParent(const ArkUI_TouchTestInfoItem* info);

/**
 * @brief 从触摸测试信息项中获取子组件的边界矩形信息。
 *
 * @param info 指向触摸测试信息项的指针。
 * @param childRect 指向子组件边界矩形的指针，用于存储获取到的边界矩形信息。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TouchTestInfoItem_GetChildRect(const ArkUI_TouchTestInfoItem* info, ArkUI_Rect* childRect);

/**
 * @brief 从触摸测试信息项中获取子组件的ID。
 *
 * @param info 指向触摸测试信息项的指针。
 * @param buffer 存储结果的缓冲区。
 * @param bufferSize 缓冲区的大小。
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 *     <br>如果缓冲区空间不足，则返回{@link ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH}。
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TouchTestInfoItem_GetChildId(const ArkUI_TouchTestInfoItem* info, char* buffer,
    int32_t bufferSize);

/**
 * @brief 设置触摸测试策略，即组件及其子组件在命中测试过程中的行为方式。
 *
 * @param {pointer} info Indicates the pointer to a touch test info.
 * @param {ArkUI_TouchTestStrategy} strategy The touch test strategy.
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TouchTestInfo_SetTouchResultStrategy(ArkUI_TouchTestInfo* info,
    ArkUI_TouchTestStrategy strategy);

/**
 * @brief 设置命中测试过程中需要作用的子组件ID。
 *
 * @param {pointer} info Indicates the pointer to a touch test info.
 * @param {pointer} id The sub component's name.
 * @return 返回结果代码。
 *     <br>如果操作成功，则返回{@link ARKUI_ERROR_CODE_NO_ERROR}。
 *     <br>如果入参错误，则返回{@link ARKUI_ERROR_CODE_PARAM_INVALID}。
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TouchTestInfo_SetTouchResultId(ArkUI_TouchTestInfo* info, const char* id);

/**
 * @brief 获取表冠事件发生的时间。单位为ns。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回UI输入事件发生的时间，如果参数有误，则返回<b>0</b>。
 * @since 24
 */
int64_t OH_ArkUI_DigitalCrownEvent_GetEventTime(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取表冠事件发生的角速度。单位为°/s。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回UI输入事件发生的角速度，如果参数有误，则返回<b>0.0</b>。
 * @since 24
 */
double OH_ArkUI_DigitalCrownEvent_GetAngularVelocity(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取表冠事件发生的旋转角度。单位为°。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回UI输入事件发生的旋转角度，如果参数有误，则返回<b>0.0</b>。
 * @since 24
 */
double OH_ArkUI_DigitalCrownEvent_GetDegree(const ArkUI_UIInputEvent* event);

/**
 * @brief 获取表冠事件发生的阶段。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @return 返回UI输入事件发生时旋转表冠的行为。如果入参错误，则返回<b>{@link ARKUI_CROWNEVENT_ACTION_UNKNOWN}</b>。
 * @since 24
 */
ArkUI_CrownEvent_Action OH_ArkUI_DigitalCrownEvent_GetAction(const ArkUI_UIInputEvent* event);

/**
 * @brief 设置是否阻止事件冒泡。仅适用于入参event里存储的是表冠事件对象的场景。
 *
 * @param event 表示指向当前UI输入事件的指针。
 * @param stopPropagation 表示是否阻止事件冒泡。true表示阻止事件冒泡，false表示不阻止事件冒泡。
 * @return 错误码。
 *     <br>{@link ARKUI_ERROR_CODE_NO_ERROR} 成功。
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} 参数异常。
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DigitalCrownEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation);

#ifdef __cplusplus
};
#endif

#endif // _ARKUI_UI_INPUT_EVENT_H_

/** @} */