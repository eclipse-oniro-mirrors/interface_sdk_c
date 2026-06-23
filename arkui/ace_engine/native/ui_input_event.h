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
 * @brief Defines a UI input event.
 *
 * @since 12
 */
typedef struct ArkUI_UIInputEvent ArkUI_UIInputEvent;

/**
 * @brief Defines the coasting axis event.
 *
 * @since 22
 */
typedef struct ArkUI_CoastingAxisEvent ArkUI_CoastingAxisEvent;

/**
 * @brief Defines touch test information.
 *
 * @since 22
 */
typedef struct ArkUI_TouchTestInfo ArkUI_TouchTestInfo;

/**
 * @brief Defines touch test information items. The touch test information items contain information about
 * subcomponents involved in a touch test. You can obtain the subcomponent information via the
 * {@link OH_ArkUI_TouchTestInfoItem_GetXXX} APIs.
 *
 * @since 22
 */
typedef struct ArkUI_TouchTestInfoItem ArkUI_TouchTestInfoItem;

/**
 * @brief Defines the touch test info item handle.
 *
 * @since 22
 */
typedef ArkUI_TouchTestInfoItem* ArkUI_TouchTestInfoItemHandle;

/**
 * @brief Defines the gesture recognizer handle array.
 *
 * @since 22
 */
typedef ArkUI_TouchTestInfoItemHandle* ArkUI_TouchTestInfoItemArray;

/**
 * @brief Enumerates the UI input event types.
 *
 * @since 12
 */
typedef enum {
    ARKUI_UIINPUTEVENT_TYPE_UNKNOWN = 0,
    ARKUI_UIINPUTEVENT_TYPE_TOUCH = 1,
    ARKUI_UIINPUTEVENT_TYPE_AXIS = 2,
    /**
     * Mouse event.
     */
    ARKUI_UIINPUTEVENT_TYPE_MOUSE = 3,
    /**
     * @brief Key event.
     *
     * @since 20
     */
    ARKUI_UIINPUTEVENT_TYPE_KEY = 4,
    /**
     * @brief Crown event.
     *
     * @since 24
     */
    ARKUI_UIINPUTEVENT_TYPE_DIGITAL_CROWN = 5,
} ArkUI_UIInputEvent_Type;

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
 * @brief Enumerates the hit test modes.
 *
 * @since 12
 */
typedef enum {
    /**
     * Default hit test mode. The node itself and its child nodes respond to the hit test, but block the hit test of
     * sibling nodes. It does not affect the hit test of ancestor nodes.
     */
    HTM_DEFAULT = 0,

    /**
     * The node itself responds to the hit test and blocks the hit test of child nodes, sibling nodes, and ancestor
     * nodes.
     */
    HTM_BLOCK,

    /**
     * The node itself and its child nodes respond to the hit test, preventing all sibling nodes and parent nodes with
     * lower priority from participating in the hit test.
     */
    HTM_TRANSPARENT,

    /**
     * The node itself does not respond to the hit test and does not block the hit test of child nodes, sibling nodes,
     * and ancestor nodes.
     */
    HTM_NONE,

/**
 * The node and its child nodes participate in hit tests, while blocking hit tests for all sibling nodes and parent
 * nodes with lower priority.
 *
 * @since 20
 */
    HTM_BLOCK_HIERARCHY,

    /**
     * The node itself does not respond to the hit test, and all its descendants (children, grandchildren, and more)
     * also do not respond to the hit test. It does not affect the hit test of ancestor nodes.
     * @since 20
     */
    HTM_BLOCK_DESCENDANTS,
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
 * @brief Enumerates the modifier keys.
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
     * Fn (for debugging purposes only; typically, the Fn key state is not reported)
     */
    ARKUI_MODIFIER_KEY_FN = 1 << 3,
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
 * @brief Defines the phases of a crown event.
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
    ARKUI_CROWNEVENT_ACTION_END = 2,
} ArkUI_CrownEvent_Action;

/**
 * @brief Defines whether the touch event is from the left or right hand.
 *
 * @since 15
 */
typedef enum {
    /**
     * Unknown.
     */
    ARKUI_EVENT_HAND_NONE = 0,
    /**
     * Left hand.
     */
    ARKUI_EVENT_HAND_LEFT = 1,
    /**
     * Right hand.
     */
    ARKUI_EVENT_HAND_RIGHT = 2,
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
 * @brief Enumerates the phases of coasting axis events.
 *
 * @since 22
 */
typedef enum {
    /**
     * Invalid coasting axis event phase, serving as an abnormal default value. You can verify that the coasting axis
     * phase is not this value to confirm event validity.
     */
    ARKUI_COASTING_AXIS_EVENT_PHASE_NONE = 0,
    /**
     * The coasting axis event begins. This is the initial event in the coasting phase.
     */
    ARKUI_COASTING_AXIS_EVENT_PHASE_BEGIN = 1,
    /**
     * The coasting axis event updates. In this phase, you can obtain the coasting axis delta value to handle scroll
     * offset calculations.
     */
    ARKUI_COASTING_AXIS_EVENT_PHASE_UPDATE = 2,
    /**
     * The coasting axis event ends. This phase is triggered when coasting stops due to braking (for example, the user
     * re-engages the touchpad during coasting, or interacts via a mouse or touchscreen) or natural decay to rest. Upon
     * reaching this phase, immediately terminate the coasting scroll effect.
     */
    ARKUI_COASTING_AXIS_EVENT_PHASE_END = 3,
} ArkUI_CoastingAxisEventPhase;

/**
 * @brief Defines the touch test policy.
 *
 * @since 22
 */
typedef enum {
    /**
     * Custom dispatch has no effect. The system dispatches events based on the hit status of the current node.
     */
    ARKUI_TOUCH_TEST_STRATEGY_DEFAULT = 0,
    /**
     * The event is dispatched to a specified child node, and the system determines whether to dispatch events to other
     * sibling nodes.
     */
    ARKUI_TOUCH_TEST_STRATEGY_FORWARD_COMPETITION = 1,
    /**
     * The event is dispatched to a specified child node, and the system will not dispatch events to other sibling
     * nodes.
     */
    ARKUI_TOUCH_TEST_STRATEGY_FORWARD = 2,
} ArkUI_TouchTestStrategy;

/**
 * @brief Strategy that determines whether the gesture identification result between the event injector and the
 * injected end is in a competition scenario. This strategy determines how the event injector interacts with the
 * gesture processing logic of the injected end. In non-competition scenarios, the gestures of the two parties are
 * triggered simultaneously. In competition scenarios, only the gesture of one party is triggered.
 *
 * @since 24
 */
typedef enum {
    /**
     * Non-competition strategy. The injected event does not compete with any existing gesture. The injected event and
     * existing gestures can be processed independently and concurrently.
     */
    ARKUI_COMPETITION_STRATEGY_DEFAULT = 0,
    /**
     * Competition strategy The gestures between the event injector and the injected end are in competition, and only
     * the gestures of one party can be processed.
     */
    ARKUI_COMPETITION_STRATEGY_COMPETITION = 1,
} ArkUI_CompetitionStrategy;

/**
 * @brief Obtains the type of a UI input event. Before accessing an **ArkUI_UIInputEvent** pointer, use this API to
 * determine the type of the input event. This API returns a value from the {@link ArkUI_UIInputEvent_Type} enum. It
 * helps ensure compatibility with subsequent accessors. For example, if the event is a touch event, which is
 * directional, you can use OH_ArkUI_UIInputEvent_GetXXX or OH_ArkUI_PointerEvent_GetXXX for access. Using
 * OH_ArkUI_KeyEvent_GetXXX to access the event may produce undefined behavior. For unsupported event types, this API
 * returns the default value **0**.
 *
 * @param event Pointer to the UI input event.
 * @return Type of the UI input event. Returns **0** if any parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_UIInputEvent_GetType(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the action type of an input event. The action type defines the phase of a basic event (for example,
 * start or end) and characterizes its behavior, such as touch down or touch up. Action types are specific to the event
 * category: {@link UI_TOUCH_EVENT_ACTION} for touch events and {@link UI_MOUSE_EVENT_ACTION} for mouse events. For
 * axis events, use {@link OH_ArkUI_AxisEvent_GetAxisAction} to obtain the action type, which returns
 * {@link UI_AXIS_EVENT_ACTION}. For key events, use {@link OH_ArkUI_KeyEvent_GetType} to obtain the action type, which
 * returns {@link ArkUI_KeyEventType}.
 *
 * @note
 * 1. For axis events, use {@link OH_ArkUI_AxisEvent_GetAxisAction} to obtain the action type,
 *    which returns UI_AXIS_EVENT_ACTION_XXX.
 * 2. For key events, use {@link OH_ArkUI_KeyEvent_GetType} instead.
 *
 * @param event Pointer to the UI input event.
 * @return Action type of the UI input event. Returns **-1** if any parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_UIInputEvent_GetAction(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the source type of a UI input event. The source represents the physical device, such as a touchscreen
 * or mouse device, that generates the input event. It is defined by {@link UI_INPUT_EVENT_SOURCE_TYPE}. This is
 * different from the input tool, which is the device used to interact with the source, for example, a finger or stylus.
 *  However, in certain cases, the input source and the input tool can be the same. For example, a mouse device acts as
 * both the source and tool for click events. For key events, obtaining the source type is not supported, and in such
 * cases, the API will return an **unknown** value.
 *
 * @note For key events, obtaining the source type is not supported, and in such cases,
 *     the API will return an <b>unknown</b> value.
 *
 * @param event Pointer to the UI input event.
 * @return Source type of the UI input event.
 * @since 12
 */
int32_t OH_ArkUI_UIInputEvent_GetSourceType(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the tool type of a UI input event. The input tool is the device used to interact with the input
 * source, such as a finger or stylus. These tools themselves do not generate events but can drive the input source
 * device to continuously generate events. The returned type is defined by the enumerated value of
 * {@link UI_INPUT_EVENT_TOOL_TYPE}. For key events, obtaining the tool type is not supported, and in such cases, the
 * API will return an **unknown** value.
 *
 * @note For key events, obtaining the tool type is not supported, and in such cases,
 *     the API will return an <b>unknown</b> value.
 *
 * @param event Pointer to the UI input event.
 * @return Tool type of the UI input event.
 * @since 12
 */
int32_t OH_ArkUI_UIInputEvent_GetToolType(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the time when a specified UI input event occurs. The unit is ns.
 *
 * @param event Pointer to the UI input event.
 * @return Time when the UI input event occurs. Returns **0** if any parameter error occurs.
 * @since 12
 */
int64_t OH_ArkUI_UIInputEvent_GetEventTime(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the number of contact points from a pointer event (such as a touch, mouse, or axis event). Pointer
 * events are typically events that carry position information, such as touch events, where the location of the event
 * can be determined. Non-pointer events, such as key events, do not have position information and do not involve
 * points, so this API always returns **0**. For touch events, this API returns the number of active touch points, for
 * example, fingers on the screen. For mouse and axis events, this API always returns **1**, as they are single-pointer
 * interactions.
 *
 * @param event Pointer to the UI input event.
 * @return Number of contact points in the pointer event.
 * @since 12
 */
uint32_t OH_ArkUI_PointerEvent_GetPointerCount(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the unique ID of a contact point from a pointer event (such as a touch, mouse, or axis event). The ID
 * distinguishes between multiple touch points from the same input device. The return value itself does not have any
 * other meaning beyond identifying the touch point.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Unique ID of the specific contact point.
 * @since 12
 */
int32_t OH_ArkUI_PointerEvent_GetPointerId(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the ID of the touch pointer that triggers the current touch event.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_GetChangedPointerId(const ArkUI_UIInputEvent* event, uint32_t* pointerIndex);

/**
 * @brief Obtains the x-coordinate relative to the upper left corner of the current component from a pointer event (
 * such as a touch, mouse, or axis event).
 *
 * @param event Pointer to the UI input event.
 * @return X-coordinate relative to the upper left corner of the current component, in px. Returns **0.0f** if a
 *     parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetX(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the x-coordinate of a specific contact point relative to the upper left corner of the current
 * component from a pointer event (such as a touch, mouse, or axis event). For mouse and axis events, this API returns
 * the default value of **0.0f** if the given index is greater than 0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return X-coordinate of the specific contact point relative to the upper left corner of the current component, in px.
 *      Returns **0.0f** if a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the y-coordinate relative to the upper left corner of the current component from a pointer event (
 * such as a touch, mouse, or axis event).
 *
 * @param event Pointer to the UI input event.
 * @return Y-coordinate relative to the upper left corner of the current component, in px. Returns **0.0f** if a
 *     parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetY(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the y-coordinate of a specific contact point relative to the upper left corner of the current
 * component from a pointer event (such as a touch, mouse, or axis event). For mouse and axis events, this API returns
 * the default value of **0.0f** if the given index is greater than 0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Y-coordinate of the specific contact point relative to the upper left corner of the current component, in px.
 *      Returns **0.0f** if a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the X coordinate relative to the upper left corner of the current component from a
 * {@link pointer event}(such as a touch event, mouse event, or axis event) based on the real-time location.
 *
 * @param event Pointer to the UI input event.
 * @return X coordinate of the current pointer event relative to the upper left corner of the current component. The
 *     default unit is px, which can vary according to the setting of {@link setLengthMetricUnit}. If a parameter error
 *     occurs, **0.0f** is returned.
 * @since 26.0.0
 */
float OH_ArkUI_PointerEvent_GetCurrentLocalX(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the X coordinate of a specific contact point relative to the upper left corner of the current
 * component from a {@link pointer event}(such as a touch event, mouse event, or axis event) based on the real-time
 * location.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return X coordinate of the specific contact point relative to the upper left corner of the current component. The
 *     default unit is px, which can vary according to the setting of {@link setLengthMetricUnit}. If a parameter error
 *     occurs, **0.0f** is returned.
 * @since 26.0.0
 */
float OH_ArkUI_PointerEvent_GetCurrentLocalXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the Y coordinate relative to the upper left corner of the current component from a
 * {@link pointer event}(such as a touch event, mouse event, or axis event) based on the real-time location.
 *
 * @param event Pointer to the UI input event.
 * @return Y coordinate of the current pointer event relative to the upper left corner of the current component. The
 *     default unit is px, which can vary according to the setting of {@link setLengthMetricUnit}. If a parameter error
 *     occurs, **0.0f** is returned.
 * @since 26.0.0
 */
float OH_ArkUI_PointerEvent_GetCurrentLocalY(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the Y coordinate of a specific contact point relative to the upper left corner of the current
 * component from a {@link pointer event}(such as a touch event, mouse event, or axis event) based on the real-time
 * location.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Y coordinate of the specific contact point relative to the upper left corner of the current component. The
 *     default unit is px, which can vary according to the setting of {@link setLengthMetricUnit}. If a parameter error
 *     occurs, **0.0f** is returned.
 * @since 26.0.0
 */
float OH_ArkUI_PointerEvent_GetCurrentLocalYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the x-coordinate relative to the upper left corner of the current application window from a pointer
 * event (such as a touch, mouse, or axis event).
 *
 * @param event Pointer to the UI input event.
 * @return X-coordinate relative to the upper left corner of the current application window, in px. Returns **0.0f** if
 *     a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetWindowX(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the x-coordinate of a specific contact point relative to the upper left corner of the current
 * application window from a pointer event (such as a touch, mouse, or axis event). For mouse and axis events, this API
 * returns the default value of **0.0f** if the given index is greater than 0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return X-coordinate of the specific contact point relative to the upper left corner of the current application
 *     window, in px. Returns **0.0f** if a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetWindowXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the y-coordinate relative to the upper left corner of the current application window from a pointer
 * event (such as a touch, mouse, or axis event).
 *
 * @param event Pointer to the UI input event.
 * @return Y-coordinate relative to the upper left corner of the current application window, in px. Returns **0.0f** if
 *     a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetWindowY(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the y-coordinate of a specific contact point relative to the upper left corner of the current
 * application window from a pointer event (such as a touch, mouse, or axis event). For mouse and axis events, this API
 * returns the default value of **0.0f** if the given index is greater than 0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Y-coordinate of the specific contact point relative to the upper left corner of the current application
 *     window, in px. Returns **0.0f** if a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetWindowYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the x-coordinate relative to the upper left corner of the current screen from a pointer event (such
 * as a touch, mouse, or axis event).
 *
 * @param event Pointer to the UI input event.
 * @return X-coordinate relative to the upper left corner of the current screen, in px. Returns **0.0f** if a parameter
 *     error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetDisplayX(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the x-coordinate of a specific contact point relative to the upper left corner of the current screen
 * from a pointer event (such as a touch, mouse, or axis event). For mouse and axis events, this API returns the
 * default value of **0.0f** if the given index is greater than 0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return X-coordinate of the specific contact point relative to the upper left corner of the current screen, in px.
 *     Returns **0.0f** if a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetDisplayXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the y-coordinate relative to the upper left corner of the current screen from a pointer event (such
 * as a touch, mouse, or axis event).
 *
 * @param event Pointer to the UI input event.
 * @return Y-coordinate relative to the upper left corner of the current screen, in px. Returns **0.0f** if a parameter
 *     error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetDisplayY(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the y-coordinate of a specific contact point relative to the upper left corner of the current screen
 * from a pointer event (such as a touch, mouse, or axis event). For mouse and axis events, this API returns the
 * default value of **0.0f** if the given index is greater than 0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Y-coordinate of the specific contact point relative to the upper left corner of the current screen, in px.
 *     Returns **0.0f** if a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetDisplayYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the x-coordinate relative to the global display from a pointer event (such as a touch, mouse, or axis
 * event). The position information can be obtained only from a {@link ArkUI_UIInputEvent} event.
 *
 * @param event Pointer to the UI input event.
 * @return X-coordinate relative to the global display, in px. **0.0f** is returned if any parameter error occurs (for
 *     example, if the event does not contain position information).
 * @since 20
 */
float OH_ArkUI_PointerEvent_GetGlobalDisplayX(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the x-coordinate relative to the global display from a pointer event (such as a touch, mouse, or axis
 * event). Position information can only be obtained from pointer events. For mouse and axis events, if the provided **
 * pointerIndex** is greater than 0, this API always returns the default value **0.0f**.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list. Valid value range: [0,
 *     {@link OH_ArkUI_PointerEvent_GetPointerCount()} – 1]
 * @return X-coordinate of the specific contact point relative to the global display, in px. Returns **0.0f** if any
 *     parameter error occurs.
 * @since 20
 */
float OH_ArkUI_PointerEvent_GetGlobalDisplayXByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the y-coordinate relative to the global display from a pointer event (such as a touch, mouse, or axis
 * event). The position information can be obtained only from a {@link ArkUI_UIInputEvent} event.
 *
 * @param event Pointer to the UI input event.
 * @return Y-coordinate relative to the global display, in px. **0.0f** is returned if any parameter error occurs (for
 *     example, if the event does not contain position information).
 * @since 20
 */
float OH_ArkUI_PointerEvent_GetGlobalDisplayY(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the y-coordinate relative to the global display from a pointer event (such as a touch, mouse, or axis
 * event). Position information can only be obtained from pointer events. For mouse and axis events, if the provided **
 * pointerIndex** is greater than 0, this API always returns the default value **0.0f**.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list. Valid value range: [0,
 *     {@link OH_ArkUI_PointerEvent_GetPointerCount()} – 1]
 * @return Y-coordinate relative to the global display, in px. Returns **0.0f** if any parameter error occurs.
 * @since 20
 */
float OH_ArkUI_PointerEvent_GetGlobalDisplayYByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the pressure applied to the touchscreen from a pointer event (such as a touch event).
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Touch pressure generated by the current pointer event. The value range is [0, 1]. The pressure is positively
 *     correlated with the value. If the parameter is abnormal, the default value **0.0f** is returned. On some devices,
 *      the return value may be greater than 1 due to different hardware parameter configurations.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetPressure(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the angle relative to the YZ plane from a pointer event (for example, a touch event). The value range
 * is [-90, 90], in deg. A positive value indicates a rightward tilt. This API is applicable only to stylus-based touch
 * events from devices that support tilt angle reporting.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Angle relative to the YZ plane.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetTiltX(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the angle relative to the XZ plane from a pointer event (for example, a touch event). The value range
 * is [-90, 90], in deg. A positive value indicates a downward tilt. This API is applicable only to stylus-based touch
 * events from devices that support tilt angle reporting.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Angle relative to the XZ plane.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetTiltY(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the rotation angle of the stylus around the z-axis from a UI input event.
 *
 * @param event Pointer to the current UI input event.
 * @param rollAngle Rotation angle of the stylus around the z-axis, in deg.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 17
 */
int32_t OH_ArkUI_PointerEvent_GetRollAngle(const ArkUI_UIInputEvent* event, double* rollAngle);

/**
 * @brief Obtains the width of the touch area for a pointer event. This API is applicable only to finger-based touch
 * events, and the return value typically represents the radius of a circular touch area.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Width of the touch area, in px.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetTouchAreaWidth(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the height of the touch area for a pointer event. This API is applicable only to finger-based touch
 * events, and the return value typically represents the radius of a circular touch area.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Height of the touch area, in px.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetTouchAreaHeight(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Checks whether an event is triggered by a left-hand or right-hand tap. This API is only effective on some
 * touch devices.
 *
 * @note The value is not available immediately upon press. Until the system infers the result, this API will return
 *     <b>NONE</b>. Do not rely on the return value for critical functionality.
 *
 * @param event Pointer to the UI input event.
 * @param hand Whether the touch point is from the left or right hand.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_GetInteractionHand(const ArkUI_UIInputEvent *event, ArkUI_InteractionHand *hand);

/**
 * @brief Checks whether an event is triggered by a left-hand or right-hand tap. This API is only effective on some
 * touch devices.
 *
 * @note The value is not available immediately upon press. Until the system infers the result,
 *     this API will return <b>NONE</b>. Do not rely on the return value for critical functionality.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param hand Whether the touch point is from the left or right hand.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_GetInteractionHandByIndex(
    const ArkUI_UIInputEvent *event, int32_t pointerIndex, ArkUI_InteractionHand *hand);

/**
 * @brief Obtains the number of historical events from a {@link pointer event}. Pointer events supported by this API
 * contain only touch and mouse events. A historical event is the raw event that occurs between the current event and
 * the previous event. This API is applicable only to the move phase (touch or mouse movement) of a pointer event. If
 * this API is called in other states, the default value **0** is returned. Touch events are supported since API
 * version 12, and mouse events are supported since API version 26.0.0.
 *
 * @param event Pointer to the UI input event.
 * @return Number of historical events.
 * @since 12
 */
uint32_t OH_ArkUI_PointerEvent_GetHistorySize(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the occurrence time of a historical event from a pointer event. Pointer events supported by this API
 * contain only touch and mouse events. Touch events are supported since API version 12, and mouse events are supported
 * since API version 26.0.0.
 *
 * @param event Pointer to the UI input event.
 * @param historyIndex Index of the target historical event.
 * @return Time when the UI input event occurs, in ns. Returns **0** if a parameter error occurs.
 * @since 12
 */
int64_t OH_ArkUI_PointerEvent_GetHistoryEventTime(const ArkUI_UIInputEvent* event, uint32_t historyIndex);

/**
 * @brief Obtains the number of contact points in a specific historical event from a pointer event. Pointer events
 * supported by this API contain only touch events.
 *
 * @param event Pointer to the UI input event.
 * @param historyIndex Index of the target historical event.
 * @return Number of contact points in the specified historical event.
 * @since 12
 */
uint32_t OH_ArkUI_PointerEvent_GetHistoryPointerCount(const ArkUI_UIInputEvent* event, uint32_t historyIndex);

/**
 * @brief Obtains the unique ID of a contact point in a specific historical event from a pointer event. Pointer events
 * supported by this API contain only touch events. The ID distinguishes between multiple touch points from the same
 * input device. The return value itself does not have any other meaning beyond identifying the touch point.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param historyIndex Index of the target historical event.
 * @return ID of the corresponding contact point in the specified historical event.
 * @since 12
 */
int32_t OH_ArkUI_PointerEvent_GetHistoryPointerId(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the X-coordinate of a specific contact point in a specific historical event relative to the upper
 * left corner of the current component from a pointer event. Pointer events supported by this API contain only touch
 * and mouse events. For mouse events, this API returns the default value **0.0f** if the given value of **pointerIndex*
 * * is greater than **0**. Touch events are supported since API version 12, and mouse events are supported since API
 * version 26.0.0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param historyIndex Index of the target historical event.
 * @return X-coordinate of the specific contact point in the specific historical event relative to the upper left
 *     corner of the current component, in px. Returns **0.0f** if a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryX(const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the Y-coordinate of a specific contact point in a specific historical event relative to the upper
 * left corner of the current component from a pointer event. Pointer events supported by this API contain only touch
 * and mouse events. For mouse events, this API returns the default value **0.0f** if the given value of **pointerIndex*
 * * is greater than **0**. Touch events are supported since API version 12, and mouse events are supported since API
 * version 26.0.0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param historyIndex Index of the target historical event.
 * @return Y-coordinate of the specific contact point in the specific historical event relative to the upper left
 *     corner of the current component, in px. Returns **0.0f** if a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryY(const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the X-coordinate of a specific contact point in a specific historical event relative to the upper
 * left corner of the current application window from a pointer event. Pointer events supported by this API contain
 * only touch and mouse events. For mouse events, this API returns the default value **0.0f** if the given value of **
 * pointerIndex** is greater than **0**. Touch events are supported since API version 12, and mouse events are
 * supported since API version 26.0.0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param historyIndex Index of the target historical event.
 * @return X-coordinate of the specific contact point in the specific historical event relative to the upper left
 *     corner of the current application window, in px. Returns **0.0f** if a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryWindowX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the Y-coordinate of a specific contact point in a specific historical event relative to the upper
 * left corner of the current application window from a pointer event. Pointer events supported by this API contain
 * only touch and mouse events. For mouse events, this API returns the default value **0.0f** if the given value of **
 * pointerIndex** is greater than **0**. Touch events are supported since API version 12, and mouse events are
 * supported since API version 26.0.0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param historyIndex Index of the target historical event.
 * @return Y-coordinate of the specific contact point in the specific historical event relative to the upper left
 *     corner of the current application window, in px. Returns **0.0f** if a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryWindowY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the X-coordinate of a specific contact point in a specific historical event relative to the upper
 * left corner of the current screen from a pointer event. Pointer events supported by this API contain only touch and
 * mouse events. For mouse events, this API returns the default value **0.0f** if the given value of **pointerIndex**
 * is greater than **0**. Touch events are supported since API version 12, and mouse events are supported since API
 * version 26.0.0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param historyIndex Index of the target historical event.
 * @return X-coordinate of the specific contact point in the specific historical event relative to the upper left
 *     corner of the current screen, in px. Returns **0.0f** if a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryDisplayX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the Y-coordinate of a specific contact point in a specific historical event relative to the upper
 * left corner of the current screen from a pointer event. Pointer events supported by this API contain only touch and
 * mouse events. For mouse events, this API returns the default value **0.0f** if the given value of **pointerIndex**
 * is greater than **0**. Touch events are supported since API version 12, and mouse events are supported since API
 * version 26.0.0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param historyIndex Index of the target historical event.
 * @return Y-coordinate of the specific contact point in the specific historical event relative to the upper left
 *     corner of the current screen, in px. Returns **0.0f** if a parameter error occurs.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryDisplayY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the X-coordinate relative to the global display for a specific touch point in a historical event from
 * a pointer event at the given pointer index and history index. Pointer events supported by this API contain only
 * touch and mouse events. Position information can only be obtained from pointer events. For mouse events, this API
 * returns the default value **0.0f** if the given value of **pointerIndex** is greater than **0**. Touch events are
 * supported since API version 20, and mouse events are supported since API version 26.0.0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list. Valid value range: [0,
 *     {@link OH_ArkUI_PointerEvent_GetPointerCount()} – 1]
 * @param historyIndex Historical value to be returned. The value must be less than
 *     {@link OH_ArkUI_PointerEvent_GetHistorySize}.
 * @return X-coordinate of the specific contact point in the specific historical event relative to the global display,
 *     in px. Returns **0.0f** if any parameter error occurs.
 * @since 20
 */
float OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the Y-coordinate relative to the global display for a specific touch point in a historical event from
 * a pointer event at the given pointer index and history index. Pointer events supported by this API contain only
 * touch and mouse events. Position information can only be obtained from pointer events. For mouse events, this API
 * returns the default value **0.0f** if the given value of **pointerIndex** is greater than **0**. Touch events are
 * supported since API version 20, and mouse events are supported since API version 26.0.0.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list. Valid value range: [0,
 *     {@link OH_ArkUI_PointerEvent_GetPointerCount()} – 1]
 * @param historyIndex Historical value to be returned. The value must be less than
 *     {@link OH_ArkUI_PointerEvent_GetHistorySize}.
 * @return Y-coordinate of the specific contact point in the specific historical event relative to the global display,
 *     in px. Returns **0.0f** if any parameter error occurs.
 * @since 20
 */
float OH_ArkUI_PointerEvent_GetHistoryGlobalDisplayY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the pressure applied to the touchscreen in a specific historical event from a pointer event (such as
 * a touch event).
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param historyIndex Index of the target historical event.
 * @return Touch pressure generated by the current pointer event. The value range is [0, 1]. The pressure is positively
 *     correlated with the value. If the parameter is abnormal, the default value **0.0f** is returned. On some devices,
 *      the return value may be greater than 1 due to different hardware parameter configurations.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryPressure(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the angle relative to the YZ plane in a specific historical event from a pointer event (such as a
 * touch event). The value range is [-90, 90], in deg. A positive value indicates a rightward tilt.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param historyIndex Index of the target historical event.
 * @return Angle relative to the YZ plane.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryTiltX(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the angle relative to the XZ plane in a specific historical event from a pointer event (such as a
 * touch event). The value range is [-90, 90], in deg. A positive value indicates a downward tilt.
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param historyIndex Index of the target historical event.
 * @return Angle relative to the XZ plane.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryTiltY(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the width of the touch area in a specific historical event from a pointer event (such as a touch
 * event).
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param historyIndex Index of the target historical event.
 * @return Width of the touch area, in px.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryTouchAreaWidth(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the height of the touch area in a specific historical event from a pointer event (such as a touch
 * event).
 *
 * @param event Pointer to the UI input event.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @param historyIndex Index of the target historical event.
 * @return Height of the touch area, in px.
 * @since 12
 */
float OH_ArkUI_PointerEvent_GetHistoryTouchAreaHeight(
    const ArkUI_UIInputEvent* event, uint32_t pointerIndex, uint32_t historyIndex);

/**
 * @brief Obtains the value of the vertical scroll axis for this axis event. This value is typically generated by mouse
 * wheel scrolling or two-finger vertical swiping on a touchpad. If the value is generated by mouse wheel scrolling: 1.
 * The reported value is in degrees and represents the angular increment of a single scroll, not the total accumulation.
 *  2. The reported value includes the user's scroll step configuration (see {@link OH_ArkUI_AxisEvent_GetScrollStep}).
 * 3. The sign of the value indicates the direction: positive for backward scrolling and negative for forward scrolling.
 *  If the value is generated by two-finger vertical swiping on a touchpad: 1. The reported value is in px and
 * represents the scroll increment, not the total accumulation. 2. The reported value does not include the user's
 * scroll step configuration {@link OH_ArkUI_AxisEvent_GetScrollStep}. 3. The sign of the value indicates the direction:
 *  positive for swiping up and negative for swiping down. 4. The direction is affected by the system settings for
 * natural scrolling. Under normal circumstances, vertical scroll axis events only drive vertical swipe gestures.
 * However, if the mouse pointer is over a scrollable area where the scrollable directions are consistent, the vertical
 * scroll axis event can drive the swipe gestures in this scrollable area, even if they are defined as horizontal.
 *
 * @param event Pointer to the UI input event.
 * @return Value of the vertical scroll axis of the current axis event. Returns **0.0** if any parameter error occurs.
 * @since 12
 */
double OH_ArkUI_AxisEvent_GetVerticalAxisValue(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the value of the horizontal scroll axis for this axis event. This value is generated by two-finger
 * horizontal swiping on a touchpad.
 *
 * @note
 * 1. The reported value is in px and represents the incremental scroll amount, not the total scroll amount.
 * 2. The reported value does not include the user's scroll step configuration.
 * 3. The sign of the value indicates the direction: positive for swiping right and negative for swiping left.
 * 4. The direction is affected by the system settings for natural scrolling.
 *
 * @param event Pointer to the UI input event.
 * @return Value of the horizontal scroll axis of the current axis event. Returns **0.0** if any parameter error occurs.
 * @since 12
 */
double OH_ArkUI_AxisEvent_GetHorizontalAxisValue(const ArkUI_UIInputEvent* event);

/**
 * Obtains the scale value of the pinch axis for this axis event. This value is generated by a two-finger pinch gesture
 * on a touchpad. The reported scale value is relative to the initial state when the system first detects the pinch
 * gesture, with an initial scale value of 1.0. During the pinch operation, the scale value decreases from 1.0 towards
 * 0.0 when the user pinches inward and increases from 1.0 when the user spreads fingers outward.
 * @param event Pointer to the UI input event.
 * @return Scale value of the pinch axis of the current axis event. Returns **0.0** if any parameter error occurs.
 * @since 12
 */
double OH_ArkUI_AxisEvent_GetPinchAxisScaleValue(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the action type of this axis event.
 *
 * @param event Pointer to the UI input event.
 * @return Action type of the current axis event. For details, see {@link anonymous7}. If a non-axis event is input, **
 *     0** is returned by default.
 * @since 15
 */
int32_t OH_ArkUI_AxisEvent_GetAxisAction(const ArkUI_UIInputEvent* event);

/**
 * @brief Checks whether this axis event contains the specified axis type.
 *
 * @param event Pointer to the UI input event.
 * @param axis Axis type of the axis event, specified using {@link UI_AXIS_TYPE}.
 * @return Whether the current axis event contains the specified axis type. Returns **true** if the axis event contains
 *     the specified axis type, and **false** otherwise.
 * @since 22
 */
int32_t OH_ArkUI_AxisEvent_HasAxis(const ArkUI_UIInputEvent* event, int32_t axis);

/**
 * @brief Sets the touch test mode. This API only applies to scenarios raw input events are received, such as when **
 * NODE_ON_TOUCH** is used for touch event handling. It cannot be used with **ArkUI_UIInputEvent** objects obtained
 * from gesture events through {@link OH_ArkUI_GestureEvent_GetRawInputEvent}.
 *
 * @param event Pointer to the UI input event.
 * @param mode Touch test mode. The parameter type is {@link HitTestMode}.
 * @return Result code.
 * @since 12
 */
int32_t OH_ArkUI_PointerEvent_SetInterceptHitTestMode(const ArkUI_UIInputEvent* event, HitTestMode mode);

/**
 * @brief Obtains the button type of a mouse event.
 *
 * @param event Pointer to the UI input event.
 * @return Mouse button type. The value is defined by the {@link anonymous5} enumeration. If the API is called in a non-
 *     mouse event, the return value is **-1**.
 * @since 12
 */
int32_t OH_ArkUI_MouseEvent_GetMouseButton(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the action type of a mouse event.
 *
 * @param event Pointer to the UI input event.
 * @return Mouse action type. The value is defined by the {@link anonymous4} enumeration. If the API is called in a non-
 *     mouse event, the return value is **-1**.
 * @since 12
 */
int32_t OH_ArkUI_MouseEvent_GetMouseAction(const ArkUI_UIInputEvent* event);

/**
 * @brief Sets whether to stop event propagation. This API only applies to scenarios raw input events are received,
 * such as when **NODE_ON_TOUCH** is used for touch event handling, and does not apply to axis events. It cannot be
 * used with **ArkUI_UIInputEvent** objects obtained from gesture events through
 * {@link OH_ArkUI_GestureEvent_GetRawInputEvent}.
 *
 * @param event Pointer to the UI input event.
 * @param stopPropagation Whether to stop event propagation. The value **true** means to stop event propagation, and **
 *     false** means the opposite.
 * @return Result code. Returns **0** if the operation is successful; returns **401** if the operation fails, possibly
 *     because a parameter error, for example, null pointer for the **event** parameter, occurs.
 * @since 12
 */
int32_t OH_ArkUI_PointerEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation);

/**
 * @brief Obtains the device ID of the current UI input event.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @return Device ID of the current UI input event.
 * @since 14
 */
int32_t OH_ArkUI_UIInputEvent_GetDeviceId(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains all pressed keys. Currently, only key events are supported.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param pressedKeyCodes Array of all pressed keys. The caller is responsible for allocating the memory space to which
 *     the array points.
 * @param length Dual-purpose parameter: As input, it indicates the length of the provided **pressedKeyCodes** array;
 *     as output, it indicates the number of pressed keys.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH} if the memory is insufficient.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 14
 */
int32_t OH_ArkUI_UIInputEvent_GetPressedKeys(
    const ArkUI_UIInputEvent* event, int32_t* pressedKeyCodes, int32_t* length);

/**
 * @brief Obtains the axis value of a focus axis event.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param axis Axis type of the focus axis event. For details, see {@link anonymous6}.
 * @return Axis value of the focus axis event. Returns **0.0** if any parameter error occurs.
 * @since 15
 */
double OH_ArkUI_FocusAxisEvent_GetAxisValue(const ArkUI_UIInputEvent* event, int32_t axis);

/**
 * @brief Sets whether to prevent a focus axis event from bubbling up.
 *
 * @param event Pointer to the UI input event.
 * @param stopPropagation Whether to stop event propagation. The value **true** means to stop event propagation, and **
 *     false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_FocusAxisEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation);

/**
* @brief Obtains the width of the component hit by an event.
*
* @param event Pointer to the **ArkUI_UIInputEvent** object.
* @return Width of the component hit by an event, in pixels. If any parameter error occurs, **0.0f** is returned.
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetWidth(const ArkUI_UIInputEvent* event);

/**
* @brief Obtains the height of the component hit by an event.
*
* @param event Pointer to the **ArkUI_UIInputEvent** object.
* @return Height of the component hit by an event, in pixels. If any parameter error occurs, **0.0f** is returned.
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetHeight(const ArkUI_UIInputEvent* event);

/**
* @brief Obtains the x-coordinate of the component hit by an event.
*
* @param event Pointer to the **ArkUI_UIInputEvent** object.
* @return X-coordinate of the component hit by an event, in pixels. If any parameter error occurs, **0.0f** is returned.
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetPositionX(const ArkUI_UIInputEvent* event);

/**
* @brief Obtains the y-coordinate of the component hit by an event.
*
* @param event Pointer to the **ArkUI_UIInputEvent** object.
* @return Y-coordinate of the component hit by an event, in pixels. If any parameter error occurs, **0.0f** is returned.
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetPositionY(const ArkUI_UIInputEvent* event);

/**
* @brief Obtains the global x-coordinate of the component hit by an event.
*
* @param event Pointer to the **ArkUI_UIInputEvent** object.
* @return Global x-coordinate of the component hit by an event, in pixels. If any parameter error occurs, **0.0f** is
*     returned.
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionX(const ArkUI_UIInputEvent* event);

/**
* @brief Obtains the global y-coordinate of the component hit by an event.
*
* @param event Pointer to the **ArkUI_UIInputEvent** object.
* @return Global y-coordinate of the component hit by an event, in pixels. If any parameter error occurs, **0.0f** is
*     returned.
* @since 17
*/
float OH_ArkUI_UIInputEvent_GetEventTargetGlobalPositionY(const ArkUI_UIInputEvent* event);

/**
* @brief Checks whether the cursor is hovering over this component.
*
* @param event Pointer to the target **ArkUI_UIInputEvent** object.
* @return Returns **true** if the cursor is hovering over the current component.
*     <br>Returns **false** if the cursor is not hovering over the current component.
* @since 17
*/
bool OH_ArkUI_HoverEvent_IsHovered(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the modifier key states for a UI input event. This API outputs the state of all modifier keys at the
 * time of the event through the **keys** parameter. You can determine which keys are pressed by performing bitwise
 * operations with the modifier key types defined in {@link ArkUI_ModifierKeyName}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param keys Pointer to the combination of pressed modifier keys. The application can use bitwise operations to
 *     determine which keys are pressed.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 17
 */
int32_t OH_ArkUI_UIInputEvent_GetModifierKeyStates(const ArkUI_UIInputEvent* event, uint64_t* keys);

/**
* @brief Obtains the press time of a specific touch point. This API is effective only for touch events.
*
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Press time of the specific touch point, in ns. Returns **0** if any parameter error occurs.
 * @since 15
 */
int64_t OH_ArkUI_PointerEvent_GetPressedTimeByIndex(const ArkUI_UIInputEvent* event, uint32_t pointerIndex);

/**
 * @brief Obtains the movement delta of the mouse along the X axis in a two-dimensional plane. The value is the
 * original movement data of the mouse hardware, which is expressed in the unit of the mouse movement distance in the
 * physical world. The reported value is determined by the hardware, not the physical or logical pixels of the screen.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @return Movement delta of the mouse device along the X axis in the two-dimensional plane, which is expressed in the
 *     unit of the mouse movement distance in the physical world. If any parameter error occurs, **0.0f** is returned.
 *     <br>Note: In versions earlier than API version 26.0.0, the return value is not the original movement data of the
 *     mouse hardware. Instead, the original data is scaled down by a factor of *X*, where *X* is the system display
 *     size rate. Since API version 26.0.0, the return value is the original movement data of the mouse hardware.
 * @since 15
 */
float OH_ArkUI_MouseEvent_GetRawDeltaX(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the movement delta of the mouse along the Y axis in a two-dimensional plane. The value is the
 * original movement data of the mouse hardware, which is expressed in the unit of the mouse movement distance in the
 * physical world. The reported value is determined by the hardware, not the physical or logical pixels of the screen.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @return Movement delta of the mouse device along the Y axis in the two-dimensional plane, which is expressed in the
 *     unit of the mouse movement distance in the physical world. If any parameter error occurs, **0.0f** is returned.
 *     <br>Note: In versions earlier than API version 26.0.0, the return value is not the original movement data of the
 *     mouse hardware. Instead, the original data is scaled down by a factor of *X*, where *X* is the system display
 *     size rate. Since API version 26.0.0, the return value is the original movement data of the mouse hardware.
 * @since 15
 */
float OH_ArkUI_MouseEvent_GetRawDeltaY(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the pressed buttons from a mouse event.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param pressedButtons Array of the pressed buttons. Create an integer array to store the button values. For button
 *     code definitions, see {@link anonymous5}.
 * @param length Total length of the array.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the input buffer size is invalid.
 * @since 15
 */
int32_t OH_ArkUI_MouseEvent_GetPressedButtons(
    const ArkUI_UIInputEvent* event, int32_t* pressedButtons, int32_t* length);

/**
 * @brief Obtains the ID of the screen where the UI input event occurs.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @return Screen ID. Returns **0** if any parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_UIInputEvent_GetTargetDisplayId(const ArkUI_UIInputEvent* event);

/**
 * @brief Sets whether to enable axis event propagation (bubbling). By default, axis events do not bubble and are only
 * sent to the first component that can respond to axis events. You can enable axis event bubbling when an axis event
 * is received to allow the event to be passed to the next ancestor component in the response chain that can handle
 * axis events. This API cannot be used on axis events obtained from gesture events.
 *
 * @param event Pointer to the UI input event.
 * @param propagation Whether to enable event propagation. The value **true** means to enable event propagation, and **
 *     false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 17
 */
int32_t OH_ArkUI_AxisEvent_SetPropagation(const ArkUI_UIInputEvent* event, bool propagation);

/**
 * @brief Obtains the scroll step coefficient for a wheel-based axis event. This API returns the user-configured scroll
 * scale factor.
 *
 * @param event Pointer to the **ArkUI_UIInputEvent** object.
 * @return Scroll step configuration of the mouse wheel axis event. For non-mouse events, the default value **0** is
 *     returned.
 * @since 17
 */
int32_t OH_ArkUI_AxisEvent_GetScrollStep(const ArkUI_UIInputEvent* event);

/**
 * @brief Creates a cloned event pointer based on an event pointer. This API is effective only for touch events.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param clonedEvent Pointer to the target **ArkUI_UIInputEvent** object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_CreateClonedEvent(const ArkUI_UIInputEvent* event, ArkUI_UIInputEvent** clonedEvent);

/**
 * @brief Destroys a cloned event pointer.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_DestroyClonedEvent(const ArkUI_UIInputEvent* event);

/**
 * @brief Sets the x-coordinate and y-coordinate of a cloned event relative to the upper left corner of the current
 * component.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param x X-coordinate relative to the upper left corner of the current component, in px.
 * @param y Y-coordinate relative to the upper left corner of the current component, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventLocalPosition(const ArkUI_UIInputEvent* event, float x, float y);

/**
 * @brief Sets the x-coordinate and y-coordinate of a specific contact point of a cloned event relative to the upper
 * left corner of the current component.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param x X-coordinate relative to the upper left corner of the current component, in px.
 * @param y Y-coordinate relative to the upper left corner of the current component, in px.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventLocalPositionByIndex(
    const ArkUI_UIInputEvent* event, float x, float y, int32_t pointerIndex);

/**
 * @brief Sets the action type of a cloned event.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param actionType Action type of the cloned event.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventActionType(const ArkUI_UIInputEvent* event, int32_t actionType);

/**
 * @brief Sets the touch point ID of a cloned pointer event.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param fingerId ID of the touch point that triggers the event.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventChangedFingerId(const ArkUI_UIInputEvent* event, int32_t fingerId);

/**
 * @brief Sets the touch point ID of a specific contact point of a cloned event.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param fingerId Touch point ID of the specific contact point.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_SetClonedEventFingerIdByIndex(
    const ArkUI_UIInputEvent* event, int32_t fingerId, int32_t pointerIndex);

/**
 * @brief Posts a cloned event to a specific node.
 *
 * @param node Target node.
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL} if the component status is abnormal.
 *     <br>Returns {@link ARKUI_ERROR_CODE_POST_CLONED_NO_COMPONENT_HIT_TO_RESPOND_TO_THE_EVENT} if no component is hit
 *     to respond to the event.
 * @since 15
 */
int32_t OH_ArkUI_PointerEvent_PostClonedEvent(ArkUI_NodeHandle node, const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the result code of the most recent API call related to an **ArkUI_UIInputEvent** object. This API is
 * typically unnecessary for normal operations, but can be used to verify ambiguous return values
 *
 * @return Result code of the most recent API call related to the **ArkUI_UIInputEvent** object.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_UIInputEvent_GetLatestStatus();

/**
 * @brief Obtains the coasting axis event from the specified component event. A valid event is available only when the
 * user slides two fingers a certain distance on the touchpad and quickly releases them, and a component registered
 * with the {@link NODE_ON_COASTING_AXIS_EVENT} event exists at the pointer position. This API must be called after the
 * {@link ArkUI_UIInputEvent} object is obtained from the {@link ArkUI_NodeEvent} object.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @return Pointer to the coasting axis event. Returns a null pointer if no coasting axis event occurs or if parameters
 *     are invalid.
 * @since 22
 */
ArkUI_CoastingAxisEvent* OH_ArkUI_UIInputEvent_GetCoastingAxisEvent(ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the time when a coasting axis event occurs.
 *
 * @param event Pointer to the coasting axis event.
 * @return Time when the UI input event occurs, in ns. If any parameter error occurs, **0** is returned.
 * @since 22
 */
int64_t OH_ArkUI_CoastingAxisEvent_GetEventTime(ArkUI_CoastingAxisEvent* event);

/**
 * @brief Obtains the scroll phase of the specified coasting axis event.
 *
 * @param event Pointer to the coasting axis event.
 * @return Event phase. For details, see {@link ArkUI_CoastingAxisEventPhase}.
 *     <br>Returns **ARKUI_COASTING_AXIS_EVENT_PHASE_NONE** if any parameter error occurs.
 * @since 22
 */
ArkUI_CoastingAxisEventPhase OH_ArkUI_CoastingAxisEvent_GetPhase(ArkUI_CoastingAxisEvent* event);

/**
 * @brief Obtains the horizontal delta value of the specified coasting axis event. Unit: px, representing the single
 * scroll increment (not the total scroll amount). Positive values indicate a rightward direction (fingers swiping from
 * right to left), and negative values indicate a leftward direction (fingers swiping from left to right).
 *
 * @param event Pointer to the coasting axis event.
 * @return X-axis delta value, in px. Returns **0.0f** if any parameter error occurs.
 * @since 22
 */
float OH_ArkUI_CoastingAxisEvent_GetDeltaX(ArkUI_CoastingAxisEvent* event);

/**
 * @brief Obtains the vertical delta value of the specified coasting axis event. Unit: px, representing the single
 * scroll increment (not the total scroll amount). Negative values indicate a downward direction (fingers swiping from
 * top to bottom), and positive values indicate an upward direction (fingers swiping from bottom to top).
 *
 * @param event Pointer to the coasting axis event.
 * @return Y-axis delta value, in px. Returns **0.0f** if any parameter error occurs.
 * @since 22
 */
float OH_ArkUI_CoastingAxisEvent_GetDeltaY(ArkUI_CoastingAxisEvent* event);

/**
 * @brief Sets whether to enable event propagation for the specified coasting axis event. By default, event propagation
 * is disabled.
 *
 * @param event Pointer to the coasting axis event.
 * @param propagation Whether to enable event propagation. **true**: enable; **false**: disable.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
int32_t OH_ArkUI_CoastingAxisEvent_SetPropagation(ArkUI_CoastingAxisEvent* event, bool propagation);

/**
 * @brief Obtains the array of touch test information items.
 *
 * @param info Pointer to the touch test information.
 * @param array Pointer to the array of touch test information items.
 * @param size Size of the array of touch test information items.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TouchTestInfo_GetTouchTestInfoList(ArkUI_TouchTestInfo* info,
    ArkUI_TouchTestInfoItemArray* array, int32_t* size);

/**
 * @brief Obtains the X coordinate relative to the upper left corner of the child component from the touch test
 * information item, in px.
 *
 * @param info Pointer to a touch test information item.
 * @return X coordinate relative to the upper left corner of the child component, in px. If the parameter value is
 *     incorrect, **0.0f** is returned.
 * @since 22
 */
float OH_ArkUI_TouchTestInfoItem_GetX(const ArkUI_TouchTestInfoItem* info);

/**
 * @brief Obtains the Y coordinate relative to the upper left corner of the child component from the touch test
 * information item, in px.
 *
 * @param info Pointer to a touch test information item.
 * @return Y coordinate relative to the upper left corner of the child component, in px. If the parameter value is
 *     incorrect, **0.0f** is returned.
 * @since 22
 */
float OH_ArkUI_TouchTestInfoItem_GetY(const ArkUI_TouchTestInfoItem* info);

/**
 * @brief Obtains the X coordinate relative to the upper left corner of the current application window from the touch
 * test information item, in px.
 *
 * @param info Pointer to a touch test information item.
 * @return X coordinate relative to the upper left corner of the current application window, in px. If the parameter
 *     value is incorrect, **0.0f** is returned.
 * @since 22
 */
float OH_ArkUI_TouchTestInfoItem_GetWindowX(const ArkUI_TouchTestInfoItem* info);

/**
 * @brief Obtains the Y coordinate relative to the upper left corner of the current application window from the touch
 * test information item, in px.
 *
 * @param info Pointer to a touch test information item.
 * @return Y coordinate relative to the upper left corner of the current application window, in px. If the parameter
 *     value is incorrect, **0.0f** is returned.
 * @since 22
 */
float OH_ArkUI_TouchTestInfoItem_GetWindowY(const ArkUI_TouchTestInfoItem* info);

/**
 * @brief Obtains the X coordinate relative to the upper left corner of the parent component from the touch test
 * information item, in px.
 *
 * @param info Pointer to a touch test information item.
 * @return X coordinate relative to the upper left corner of the parent component, in px. If the parameter value is
 *     incorrect, **0.0f** is returned.
 * @since 22
 */
float OH_ArkUI_TouchTestInfoItem_GetXRelativeToParent(const ArkUI_TouchTestInfoItem* info);

/**
 * @brief Obtains the Y coordinate relative to the upper left corner of the parent component from the touch test
 * information item, in px.
 *
 * @param info Pointer to a touch test information item.
 * @return Y coordinate relative to the upper left corner of the parent component, in px. If the parameter value is
 *     incorrect, **0.0f** is returned.
 * @since 22
 */
float OH_ArkUI_TouchTestInfoItem_GetYRelativeToParent(const ArkUI_TouchTestInfoItem* info);

/**
 * @brief Obtains the boundary rectangle information of the child component from the touch test information item.
 *
 * @param info Pointer to a touch test information item.
 * @param childRect Pointer to the boundary rectangle of the child component, which is used to store the obtained
 *     boundary rectangle information.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TouchTestInfoItem_GetChildRect(const ArkUI_TouchTestInfoItem* info, ArkUI_Rect* childRect);

/**
 * @brief Obtains the ID of the child component from the touch test information item.
 *
 * @param info Pointer to a touch test information item.
 * @param buffer Storage buffer.
 * @param bufferSize Buffer size.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH} if the buffer space is insufficient.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TouchTestInfoItem_GetChildId(const ArkUI_TouchTestInfoItem* info, char* buffer,
    int32_t bufferSize);

/**
 * @brief Sets the touch test policy, that is, the behavior of a component and its child components in a hit test.
 *
 * @param {pointer} info Indicates the pointer to a touch test info.
 * @param {ArkUI_TouchTestStrategy} strategy The touch test strategy.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TouchTestInfo_SetTouchResultStrategy(ArkUI_TouchTestInfo* info,
    ArkUI_TouchTestStrategy strategy);

/**
 * @brief Sets the ID of a child component involved in a hit test.
 *
 * @param {pointer} info Indicates the pointer to a touch test info.
 * @param {pointer} id The sub component's name.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_TouchTestInfo_SetTouchResultId(ArkUI_TouchTestInfo* info, const char* id);

/**
 * @brief Obtains the time when a crown event occurs. The unit is ns.
 *
 * @param event Pointer to the UI input event.
 * @return Time when the UI input event occurs. If a parameter error occurs, **0** is returned.
 * @since 24
 */
int64_t OH_ArkUI_DigitalCrownEvent_GetEventTime(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the angular velocity at which a crown event occurs. The unit is °/s.
 *
 * @param event Pointer to the UI input event.
 * @return Angular velocity at which the UI input event occurs. If a parameter error occurs, **0.0** is returned.
 * @since 24
 */
double OH_ArkUI_DigitalCrownEvent_GetAngularVelocity(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the rotation angle at which a crown event occurs. The unit is °.
 *
 * @param event Pointer to the UI input event.
 * @return Rotation angle at which the UI input event occurs. If a parameter error occurs, **0.0** is returned.
 * @since 24
 */
double OH_ArkUI_DigitalCrownEvent_GetDegree(const ArkUI_UIInputEvent* event);

/**
 * @brief Obtains the phase at which a crown event occurs.
 *
 * @param event Pointer to the UI input event.
 * @return Action of rotating the crown when the UI input event occurs. If a parameter error occurs,
 *     {@link ARKUI_CROWNEVENT_ACTION_UNKNOWN} is returned.
 * @since 24
 */
ArkUI_CrownEvent_Action OH_ArkUI_DigitalCrownEvent_GetAction(const ArkUI_UIInputEvent* event);

/**
 * @brief Sets whether to stop event propagation. This API applies only when the input parameter **UIInputEvent**
 * contains a crown event object.
 *
 * @param event Pointer to the UI input event.
 * @param stopPropagation Whether to stop event propagation. The value **true** means to stop event propagation, and **
 *     false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DigitalCrownEvent_SetStopPropagation(const ArkUI_UIInputEvent* event, bool stopPropagation);

/**
 * @brief Creates a clone event for a specified event. This API applies to touch, mouse, and axis events.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param clonedEvent Pointer to the target **ArkUI_UIInputEvent** object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_PointerEvent_CreateClonedPointerEvent(const ArkUI_UIInputEvent* event,
    ArkUI_UIInputEvent** clonedEvent);

/**
 * @brief Creates a new event (not clone the existing event). This API applies to touch, mouse, and axis events.
 *
 * @param event Double pointer to the new **ArkUI_UIInputEvent** object.
 * @param type Event type of **ArkUI_UIInputEvent**. The value can be {@link ARKUI_UIINPUTEVENT_TYPE_TOUCH},
 *     {@link ARKUI_UIINPUTEVENT_TYPE_AXIS}, or {@link ARKUI_UIINPUTEVENT_TYPE_MOUSE}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_PointerEvent_CreatePointerEvent(ArkUI_UIInputEvent** event, ArkUI_UIInputEvent_Type type);

/**
 * @brief Destroys a cloned event pointer. This API applies to touch, mouse, and axis events. This API can be used only
 * for the **ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_PointerEvent_DestroyClonedPointerEvent(const ArkUI_UIInputEvent* event);

/**
 * @brief Sets an action type for a cloned event. This API applies to touch, mouse, and axis events. This API can be
 * used only for the **ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}
 * and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param type Type of the cloned event, including {@link UI_TOUCH_EVENT_ACTION} for the touch event,
 *     {@link UI_MOUSE_EVENT_ACTION} for the mouse event, and {@link UI_AXIS_EVENT_ACTION} for the axis event.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetActionType(const ArkUI_UIInputEvent* event, int32_t type);

/**
 * @brief Sets a source type for a cloned event. This API applies to touch, mouse, and axis events. This API can be
 * used only for the **ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}
 * and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param sourceType Source type of the clone event. The value is an integer within the range of [0,5]. The value **0**
 *     indicates unknown, **1** indicates the mouse, **2** indicates the touchscreen, **4** indicates the keyboard, and
 *     **5** indicates the handle control.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetSourceType(const ArkUI_UIInputEvent* event, int32_t sourceType);

/**
 * @brief Sets a tool type for a cloned event. This API applies to touch, mouse, and axis events. This API can be used
 * only for the **ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param toolType Tool type of the cloned event. The value is defined in the {@link UI_INPUT_EVENT_TOOL_TYPE}
 *     enumeration.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetToolType(const ArkUI_UIInputEvent* event, int32_t toolType);

/**
 * @brief Sets the pressure applied to a touchscreen for a cloned event. This API applies to touch events. This API can
 * be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param pressure Pressure applied to the touchscreen. The value range is [0,1]. For some devices, the value may be
 *     greater than **1**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetPressure(const ArkUI_UIInputEvent* event, float pressure);

/**
 * @brief Sets the pressure applied to a touchscreen for a specific touch point in a cloned event. This API applies to
 * touch events. This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param pressure Pressure applied to the touchscreen. The value range is [0,1]. For some devices, the value may be
 *     greater than **1**.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetPressureByIndex(const ArkUI_UIInputEvent* event, float pressure,
    int32_t pointerIndex);

/**
 * @brief Sets the time when a cloned UI input event occurs. This API applies to touch, mouse, and axis events. This
 * API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param timestamp Time when the cloned UI input event occurs, in ns.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetEventTime(const ArkUI_UIInputEvent* event, int64_t timestamp);

/**
 * @brief Sets the ID of the device that triggers a cloned UI input event. This API applies to touch, mouse, and axis
 * events. This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param deviceId ID of the device that triggers the cloned UI input event, which can be obtained by calling
 *     {@link OH_ArkUI_UIInputEvent_GetDeviceId}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetDeviceId(const ArkUI_UIInputEvent* event, int32_t deviceId);

/**
 * @brief Sets the ID of the display where a cloned UI input event occurs. This API applies to touch, mouse, and axis
 * events. This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param targetDisplayId ID of the display where the cloned UI input event occurs, which can be obtained by calling
 *     {@link OH_ArkUI_UIInputEvent_GetTargetDisplayId}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetTargetDisplayId(const ArkUI_UIInputEvent* event, int32_t targetDisplayId);

/**
 * @brief Sets the touch point ID for a cloned pointer event. This API applies to touch events. This API can be used
 * only for the **ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param fingerId ID of the touch point that triggers the event, which can be obtained by calling
 *     {@link OH_ArkUI_PointerEvent_GetPointerId}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetChangedFingerId(const ArkUI_UIInputEvent* event, int32_t fingerId);

/**
 * @brief Sets the touch point ID of a specific contact point in a cloned event. This API applies to touch events. This
 * API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param fingerId Touch point ID of the specific contact point, which can be obtained by calling
 *     {@link OH_ArkUI_PointerEvent_GetChangedPointerId}.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetFingerIdByIndex(
    const ArkUI_UIInputEvent* event, int32_t fingerId, int32_t pointerIndex);

/**
 * @brief Sets the X-coordinate and Y-coordinate of a cloned event relative to the upper left corner of the current
 * window. This API applies to touch, mouse, and axis events. This API can be used only for the **ArkUI_UIInputEvent**
 * objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param x X-coordinate of the event relative to the upper left corner of the current window, in px.
 * @param y Y-coordinate of the event relative to the upper left corner of the current window, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetChangedWindowPosition(const ArkUI_UIInputEvent* event, float x, float y);

/**
 * @brief Sets the X-coordinate and Y-coordinate of a specific contact point of a cloned event relative to the upper
 * left corner of the current window. This API applies to touch events. This API can be used only for the **
 * ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param x X-coordinate of the event relative to the upper left corner of the current window, in px.
 * @param y Y-coordinate of the event relative to the upper left corner of the current window, in px.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetWindowPositionByIndex(
    const ArkUI_UIInputEvent* event, float x, float y, int32_t pointerIndex);

/**
 * @brief Sets the X-coordinate and Y-coordinate of a cloned event relative to the upper left corner of the current
 * screen. This API applies to touch, mouse, and axis events. This API can be used only for the **ArkUI_UIInputEvent**
 * objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param x X-coordinate of the event relative to the upper left corner of the current screen, in px.
 * @param y Y-coordinate of the event relative to the upper left corner of the current screen, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetChangedScreenPosition(const ArkUI_UIInputEvent* event, float x, float y);

/**
 * @brief Sets the X-coordinate and Y-coordinate of a specific contact point of a cloned event relative to the upper
 * left corner of the current screen. This API applies to touch events. This API can be used only for the **
 * ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param x X-coordinate of the event relative to the upper left corner of the current screen, in px.
 * @param y Y-coordinate of the event relative to the upper left corner of the current screen, in px.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetScreenPositionByIndex(
    const ArkUI_UIInputEvent* event, float x, float y, int32_t pointerIndex);

/**
 * @brief Sets the coordinates of a cloned event in the {@link global coordinate system}. This API applies to touch
 * events. This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param x X-coordinate of the event relative to the global display, in px.
 * @param y Y-coordinate of the event relative to the global display, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetChangedGlobalDisplayPosition(const ArkUI_UIInputEvent* event, float x, float y);

/**
 * @brief Sets the coordinates of a cloned event in the {@link global coordinate system}. This API applies to touch
 * events. This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param x X-coordinate of the event relative to the global display, in px.
 * @param y Y-coordinate of the event relative to the global display, in px.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetGlobalDisplayPositionByIndex(
    const ArkUI_UIInputEvent* event, float x, float y, int32_t pointerIndex);

/**
 * @brief Sets the unique handle of an event processing session. This handle must be used for any further operations on
 * the event. For a given finger, only one event with this handle is in the active state at a time. This API applies to
 * touch, mouse, and axis events. This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param eventHandleId Unique handle of an event processing session.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetHandleId(const ArkUI_UIInputEvent* event, int32_t eventHandleId);

/**
 * @brief Sets the tilt angle of a cloned event relative to the XZ and YZ planes. The value range is [-90, 90]. A
 * positive value indicates a tilt to the right. This API applies to touch events. This API can be used only for the **
 * ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param tiltX Tilt angle of the cloned event relative to the YZ plane, in deg.
 * @param tiltY Tilt angle of the cloned event relative to the XZ plane, in deg.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetTiltAngle(const ArkUI_UIInputEvent* event, float tiltX, float tiltY);

/**
 * @brief Sets the rotation angle of the stylus around the Z-axis in a cloned event. This API applies to touch events.
 * This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param rollAngle Rotation angle of the stylus around the Z-axis in the cloned event, in deg.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetRollAngle(const ArkUI_UIInputEvent* event, float rollAngle);

/**
 * @brief Sets all pressed keys in a cloned event. This API applies to touch, mouse, and axis events. This API can be
 * used only for the **ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent}
 * and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param pressedKeyCodes Array of all pressed key values. The value is {@link ArkUI_KeyCode}.
 * @param length Length of the array of the pressed keys.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetPressedKeys(
    const ArkUI_UIInputEvent* event, int32_t* pressedKeyCodes, int32_t length);

/**
 * @brief Sets the width and height of the finger contact area for a cloned event. This API applies to touch events.
 * This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param width Width of the touch area of the cloned event, in px.
 * @param height Height of the touch area of the cloned event, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetChangedTouchArea(const ArkUI_UIInputEvent* event, float width, float height);

/**
 * @brief Sets the width and height of the finger contact area for a specific contact point of a cloned event. This API
 * applies to touch events. This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param width Width of the touch area of the cloned event, in px.
 * @param height Height of the touch area of the cloned event, in px.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetTouchAreaByIndex(const ArkUI_UIInputEvent* event, float width, float height,
    int32_t pointerIndex);

/**
 * @brief Sets whether a cloned event is triggered by the left or right hand. This API applies to touch events. This
 * API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param hand Whether the touch point is on the left or right hand. {@link ARKUI_EVENT_HAND_LEFT} indicates the left
 *     hand, and {@link ARKUI_EVENT_HAND_RIGHT} indicates the right hand.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetChangedInteractionHand(const ArkUI_UIInputEvent* event, int32_t hand);

/**
 * @brief Sets whether a specific contact point of a cloned event is triggered by the left or right hand. This API
 * applies to touch events. This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param hand Whether the touch point is on the left or right hand. {@link ARKUI_EVENT_HAND_LEFT} indicates the left
 *     hand, and {@link ARKUI_EVENT_HAND_RIGHT} indicates the right hand.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetInteractionHandByIndex(const ArkUI_UIInputEvent* event,
    int32_t hand, int32_t pointerIndex);

/**
 * @brief Sets the time when a specific touch point is pressed in a cloned event. This API applies to touch events.
 * This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param pressedTime Time when the specific touch point, in ns.
 * @param pointerIndex Index of the target touch point in the multi-touch data list.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetPressedTimeByIndex(const ArkUI_UIInputEvent* event,
    int64_t pressedTime, int32_t pointerIndex);

/**
 * Sets the pinch axis scaling value for a cloned event. This API applies to axis events. This API can be used only for
 * the **ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param pinchAxisScaleValue Scaling value of the pinch axis, in vp. The value range is [0, +∞).
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetPinchAxisScaleValue(const ArkUI_UIInputEvent* event,
    double pinchAxisScaleValue);

/**
 * Sets the horizontal axis scaling value for a cloned event. This API applies to axis events. This API can be used
 * only for the **ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param horizontalAxisScaleValue Horizontal axis scaling value, in vp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetHorizontalAxisScaleValue(const ArkUI_UIInputEvent* event,
    double horizontalAxisScaleValue);

/**
 * Sets the vertical axis scaling value for a cloned event. This API applies to axis events. This API can be used only
 * for the **ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param verticalAxisScaleValue Vertical axis scaling value, in vp.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetVerticalAxisScaleValue(const ArkUI_UIInputEvent* event,
    double verticalAxisScaleValue);

/**
 * @brief Sets the scrolling step coefficient for a cloned event. This API applies to axis events. This API can be used
 * only for the **ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param scrollStep Scrolling step coefficient of the cloned event. The value is an integer within the range of [0,
 *     65535].
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetScrollStep(const ArkUI_UIInputEvent* event, int32_t scrollStep);

/**
 * @brief Sets a button type for a cloned event. This API applies to mouse events. This API can be used only for the **
 * ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param button Mouse button type of the clone event. The value is defined by the {@link anonymous5} enumeration.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetMouseButton(const ArkUI_UIInputEvent* event, int32_t button);

/**
 * @brief Sets the movement delta of the mouse along the x-axis in a two-dimensional plane. The value is the original
 * movement data of the mouse hardware, which is expressed in the unit of the mouse movement distance in the physical
 * world. This API applies to mouse events. This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param rawDeltaX X-axis offset of the mouse position relative to the position in the previously reported mouse event.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetRawDeltaX(const ArkUI_UIInputEvent* event, float rawDeltaX);

/**
 * @brief Sets the movement delta of the mouse along the y-axis in a two-dimensional plane. The value is the original
 * movement data of the mouse hardware, which is expressed in the unit of the mouse movement distance in the physical
 * world. This API applies to mouse events. This API can be used only for the **ArkUI_UIInputEvent** objects created by
 * {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param rawDeltaY Y-axis offset of the mouse position relative to the position in the previously reported mouse event.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetRawDeltaY(const ArkUI_UIInputEvent* event, float rawDeltaY);

/**
 * @brief Sets the pressed keys in a cloned event. This API applies to mouse events. This API can be used only for the *
 * *ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param pressedButtons Pointer to the array of the pressed keys. For the values of the keys, see {@link anonymous5}.
 * @param length Length of the array of the pressed keys.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_INPUT_EVENT_TYPE_NOT_SUPPORTED} if the event type is not supported.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ClonedEvent_SetPressedButtons(
    const ArkUI_UIInputEvent* event, const int32_t* pressedButtons, int32_t length);

/**
 * @brief Posts a cloned event to a specific node using a specified competition strategy. This API can be used only for
 * the **ArkUI_UIInputEvent** objects created by {@link OH_ArkUI_PointerEvent_CreateClonedPointerEvent} and
 * {@link OH_ArkUI_PointerEvent_CreatePointerEvent}.
 *
 * @param node Target node.
 * @param event Pointer to the target **ArkUI_UIInputEvent** object.
 * @param strategy Competition strategy. The value is {@link ArkUI_CompetitionStrategy}.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NOT_CLONED_POINTER_EVENT} if the input event pointer is not a cloned event
 *     pointer.
 *     <br>Returns {@link ARKUI_ERROR_CODE_POST_CLONED_COMPONENT_STATUS_ABNORMAL} if the component status is abnormal.
 *     <br>Returns {@link ARKUI_ERROR_CODE_POST_CLONED_NO_COMPONENT_HIT_TO_RESPOND_TO_THE_EVENT} if no component is hit
 *     to respond to the event.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_PointerEvent_PostClonedEventWithStrategy(ArkUI_NodeHandle node,
    const ArkUI_UIInputEvent* event, ArkUI_CompetitionStrategy strategy);


#ifdef __cplusplus
};
#endif

#endif // _ARKUI_UI_INPUT_EVENT_H_
/** @} */
