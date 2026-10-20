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
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Defines APIs for ArkUI to register gesture callbacks on the native side.
 *
 * @since 12
 */

/**
 * @file native_gesture.h
 *
 * @brief Declares the APIs of **NativeGesture**, supporting capabilities such as gesture recognizers, gesture
 * events, gesture interruption, touch recognizers, gesture collection intervention, and gesture parameter query
 * and setting. It is suitable for scenarios where an application processes gesture recognition, gesture conflicts,
 * and gesture collection intervention through native APIs. The gesture recognition pipeline performs recognition
 * based on priority and competition rules, and gestures can be intercepted through interruption callbacks. The
 * gesture collection intervention mechanism allows dynamic intervention in the gesture collection process during
 * the gesture collection phase.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_GESTURE_H
#define ARKUI_NATIVE_GESTURE_H

#include "ui_input_event.h"
#include "native_type.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines a gesture component object, which is used to represent a gesture recognizer object in the ArkUI
 * gesture recognition APIs. After a gesture recognizer is bound to a UI component, it listens for touch events and
 * notifies you through a callback when the recognition conditions of the corresponding gesture type are met.
 * Different types of recognizers can be used for gestures such as tap, long press, pan, pinch, rotation, and swipe.
 * For details about the mechanism and usage, see the gesture API description in native_gesture.h.
 *
 * @since 12
 */
typedef struct ArkUI_GestureRecognizer ArkUI_GestureRecognizer;

/**
 * @brief Defines gesture interruption event information. This struct is used to pass information such as the gesture
 * recognizer, response chain gesture recognizer, and touch recognizer to the gesture interruption callback. The
 * callback can return a continue or reject result based on this information. For details about the gesture
 * interruption mechanism and APIs, see the gesture interruption API description in native_gesture.h.
 *
 * @since 12
 */
typedef struct ArkUI_GestureInterruptInfo ArkUI_GestureInterruptInfo;

/**
 * @brief Defines the object of gesture event data, which is used to carry and transfer gesture event-related data
 * during gesture event processing. It supports obtaining key information such as the gesture event type,
 * coordinates, and timestamp. This struct is applicable to scenarios that require processing touch gesture
 * interactions, such as tap, long-pressing, drag, and pinch gesture recognition and response. You can obtain event
 * information through related gesture event APIs.
 *
 * @since 12
 */
typedef struct ArkUI_GestureEvent ArkUI_GestureEvent;

/**
 * @brief Enumerates gesture event types.
 *
 * @since 12
 */
typedef enum {
    /**
     * Triggered.
     */
    GESTURE_EVENT_ACTION_ACCEPT = 0x01,

    /**
     * Updated.
     */
    GESTURE_EVENT_ACTION_UPDATE = 0x02,

    /**
     * Ended.
     */
    GESTURE_EVENT_ACTION_END = 0x04,

    /**
     * Canceled.
     */
    GESTURE_EVENT_ACTION_CANCEL = 0x08,
} ArkUI_GestureEventActionType;

/**
 * @brief Defines a set of gesture event types. Example: ArkUI_GestureEventActionTypeMask actions =
 * GESTURE_EVENT_ACTION_ACCEPT \| GESTURE_EVENT_ACTION_UPDATE
 *
 * @since 12
 */
typedef uint32_t ArkUI_GestureEventActionTypeMask;

/**
 * @brief Enumerates gesture priorities. **NORMAL** applies to default gesture recognition scenarios; **PRIORITY**
 * applies to scenarios where a specific gesture needs to be prioritized (for example, prioritizing a tap over a
 * swipe); **PARALLEL** applies to scenarios where multiple gestures need to respond independently and simultaneously
 * (for example, recognizing pinch and rotation at the same time).
 *
 * @since 12
 */
typedef enum {
    /**
     * Normal.
     */
    NORMAL = 0,

    /**
     * High priority.
     */
    PRIORITY = 1,

    /**
     * Parallel.
     */
    PARALLEL = 2,
} ArkUI_GesturePriority;

/**
 * @brief Enumerates gesture group modes. **SEQUENTIAL_GROUP** applies to scenarios where gestures need to be
 * recognized step by step (for example, long press followed by swipe); **PARALLEL_GROUP** applies to scenarios where
 * multiple gestures need to be recognized independently and simultaneously (for example, listening for pinch and
 * rotation at the same time); **EXCLUSIVE_GROUP** applies to scenarios where multiple gestures compete exclusively
 * and only one needs to succeed (for example, swipe and long press being mutually exclusive).
 *
 * @since 12
 */
typedef enum {
    /**
     * Sequential recognition. Gestures are recognized in the registration sequence until all gestures are recognized
     * successfully. Once one gesture fails to be recognized, all subsequent gestures fail to be recognized. Only the
     * last gesture in the gesture group can respond to the end event.
     */
    SEQUENTIAL_GROUP = 0,

    /**
     * Parallel recognition. Registered gestures are recognized concurrently until all gestures are recognized. The
     * recognition result of each gesture does not affect each other.
     */
    PARALLEL_GROUP = 1,

    /**
     * Exclusive recognition. Registered gestures are identified concurrently. If one gesture is successfully
     * recognized, gesture recognition ends.
     */
    EXCLUSIVE_GROUP = 2,
} ArkUI_GroupGestureMode;

/**
 * @brief Enumerates gesture directions.
 *
 * @since 12
 */
typedef enum {
    /**
     * All directions.
     */
    GESTURE_DIRECTION_ALL = 0b1111,

    /**
     * Horizontal direction.
     */
    GESTURE_DIRECTION_HORIZONTAL = 0b0011,

    /**
     * Vertical direction.
     */
    GESTURE_DIRECTION_VERTICAL = 0b1100,

    /**
     * Leftward.
     */
    GESTURE_DIRECTION_LEFT = 0b0001,

    /**
     * Rightward.
     */
    GESTURE_DIRECTION_RIGHT = 0b0010,

    /**
     * Upward.
     */
    GESTURE_DIRECTION_UP = 0b0100,

    /**
     * Downward.
     */
    GESTURE_DIRECTION_DOWN = 0b1000,

    /**
     * None.
     */
    GESTURE_DIRECTION_NONE = 0,
} ArkUI_GestureDirection;

/**
 * @brief Defines a set of gesture directions.
 * <br>Example: ArkUI_GestureDirectionMask directions = GESTURE_DIRECTION_LEFT \| GESTURE_DIRECTION_RIGHT
 * <br>This example indicates that the leftward and rightward directions are supported.
 *
 * @since 12
 */
typedef uint32_t ArkUI_GestureDirectionMask;

/**
 * @brief Enumerates gesture masking modes. **NORMAL_GESTURE_MASK** applies to default scenarios, where child
 * component gestures are recognized in the normal order; **IGNORE_INTERNAL_GESTURE_MASK** applies to scenarios where
 * the parent component needs exclusive gesture control (for example, blocking gesture interference from child
 * components during full-screen swiping), and it masks child component gestures, including system built-in gestures.
 *
 * @since 12
 */
typedef enum {
    /**
     * The gestures of child components are enabled and recognized based on the default gesture recognition sequence.
     */
    NORMAL_GESTURE_MASK = 0,

    /**
     * The gestures of child components are disabled, including the built-in gestures.
     */
    IGNORE_INTERNAL_GESTURE_MASK,
} ArkUI_GestureMask;

/**
 * @brief Enumerates gesture recognizer types.
 *
 * @since 12
 */
typedef enum {
    /**
     * Tap.
     */
    TAP_GESTURE = 0,

    /**
     * Long press.
     */
    LONG_PRESS_GESTURE,

    /**
     * Pan.
     */
    PAN_GESTURE,

    /**
     * Pinch.
     */
    PINCH_GESTURE,

    /**
     * Rotate.
     */
    ROTATION_GESTURE,

    /**
     * Swipe.
     */
    SWIPE_GESTURE,

    /**
     * A group of gestures.
     */
    GROUP_GESTURE,

    /**
     * Click gesture registered with **onClick**.
     * @since 20
     */
    CLICK_GESTURE,

    /**
     * Drag-and-drop gesture.
     * @since 20
     */
    DRAG_DROP,
} ArkUI_GestureRecognizerType;

/**
 * @brief Enumerates gesture interruption results.
 *
 * @since 12
 */
typedef enum {
    /**
     * The gesture recognition process continues.
     */
    GESTURE_INTERRUPT_RESULT_CONTINUE = 0,

    /**
     * The gesture recognition process is paused.
     */
    GESTURE_INTERRUPT_RESULT_REJECT,
} ArkUI_GestureInterruptResult;

/**
 * @brief Enumerates the gesture recognizer states.
 *
 * @since 12
 */
typedef enum {
    /**
     * Ready.
     */
    ARKUI_GESTURE_RECOGNIZER_STATE_READY = 0,

    /**
     * Detecting.
     */
    ARKUI_GESTURE_RECOGNIZER_STATE_DETECTING = 1,

    /**
     * Pending.
     */
    ARKUI_GESTURE_RECOGNIZER_STATE_PENDING = 2,

    /**
     * Blocked.
     */
    ARKUI_GESTURE_RECOGNIZER_STATE_BLOCKED = 3,

    /**
     * Successful.
     */
    ARKUI_GESTURE_RECOGNIZER_STATE_SUCCESSFUL = 4,

    /**
     * Failed.
     */
    ARKUI_GESTURE_RECOGNIZER_STATE_FAILED = 5,
} ArkUI_GestureRecognizerState;

/**
 * @brief Defines the intervention types for gesture and event collection.
 *
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief Continues the normal gesture and event collection flow. No intervention is performed.
     *
     * @since 26.0.0
     */
    OH_ARKUI_GESTURE_COLLECT_INTERVENTION_CONTINUE = 0,

    /**
     * @brief Discards all low-priority gestures and events to be collected.
     * <br>The gestures of the left sibling node and ancestor nodes (parent nodes and above) are discarded.
     * <br>Only the gestures already collected on the current node and higher-priority nodes are retained.
     *
     * @since 26.0.0
     */
    OH_ARKUI_GESTURE_COLLECT_INTERVENTION_DISCARD_LOWER = 1,

    /**
     * @brief Discards all collected high-priority gestures and events.
     * <br>The gestures of the right sibling node and the current node are discarded.
     * <br>Continues processing the collection flow for lower-priority gestures (left sibling and ancestor nodes).
     *
     * @since 26.0.0
     */
    OH_ARKUI_GESTURE_COLLECT_INTERVENTION_DISCARD_HIGHER = 2,

    /**
     * @brief Discards the gestures and events of the current node.
     * <br>The gestures and events of the current node are excluded from the gesture tree.
     * <br>The gestures of the sibling nodes (left and right) and the ancestor nodes are still collected.
     *
     * @since 26.0.0
     */
    OH_ARKUI_GESTURE_COLLECT_INTERVENTION_DISCARD_SELF = 3,

    /**
     * @brief Discards the gestures and events to be collected from the left sibling node.
     * <br>The gestures and events of the current node and the collected gestures and events of the right sibling node
     * are retained.
     * <br>Continues processing the collection flow for the parent and ancestor nodes.
     *
     * @since 26.0.0
     */
    OH_ARKUI_GESTURE_COLLECT_INTERVENTION_DISCARD_LOWER_PRIORITY_SIBLINGS = 4,
} OH_ArkUI_GestureCollectIntervention;

/**
 * @brief Defines the gesture recognizer handle, which is an alias wrapper of the **ArkUI_GestureRecognizer** pointer
 * type and is used to represent a gesture recognizer object in the ArkUI native gesture APIs. This handle can be
 * used as an object reference in scenarios such as gesture recognizer creation, property configuration, and event
 * callback listening, facilitating unified passing, management, and operation of gesture recognizers at the native
 * layer. For details about how to obtain and use it, see native_gesture.h.
 *
 * @since 12
 */
typedef ArkUI_GestureRecognizer* ArkUI_GestureRecognizerHandle;

/**
 * @brief Defines a gesture recognizer handle array, which is used to represent or pass multiple gesture recognizer
 * handles, for example, to obtain the collection of gesture recognizers in the response chain. For details about the
 * mechanism and usage, see the gesture API description in native_gesture.h.
 *
 * @since 12
 */
typedef ArkUI_GestureRecognizerHandle* ArkUI_GestureRecognizerHandleArray;

/**
 * @brief Defines gesture event target information. This struct is used to query the status of the gesture event
 * target object, such as scroll start and scroll end, during gesture processing. It is mainly applicable to
 * scrollable container components. You can obtain this object from the gesture recognizer through
 * {@link OH_ArkUI_GetGestureEventTargetInfo}, and read the target status through the target information query API.
 *
 * @since 12
 */
typedef struct ArkUI_GestureEventTargetInfo ArkUI_GestureEventTargetInfo;

/**
 * @brief Defines a parallel inner gesture event. This struct is passed as a parameter of the
 * {@link setInnerGestureParallelTo} callback function. It contains the current built-in gesture recognizer, the
 * conflicting gesture recognizer in the response chain, and user-defined data, so that the callback can select the
 * object to be recognized in parallel with the current built-in gesture.
 *
 * @since 12
 */
typedef struct ArkUI_ParallelInnerGestureEvent ArkUI_ParallelInnerGestureEvent;

/**
 * @brief Defines a parallel gesture event. This struct is passed as a parameter of the {@link setGestureParallelTo}
 * callback function. It contains the current gesture recognizer, the conflicting gesture recognizer in the response
 * chain, and user-defined data, for the callback to select the object that needs to be recognized in parallel with
 * the current gesture.
 *
 * @since 26.0.0
 */
typedef struct ArkUI_ParallelGestureEvent ArkUI_ParallelGestureEvent;

/**
 * @brief Defines a touch recognizer. A touch recognizer is used to represent the touch event processing object
 * returned in gesture interruption or gesture collection interception information. You can obtain its node handle
 * or cancel the touch event through related APIs. For details about the APIs, see native_gesture.h.
 *
 * @since 15
 */
typedef struct ArkUI_TouchRecognizer ArkUI_TouchRecognizer;

/**
 * @brief Defines a touch recognizer handle, which is used to represent a touch recognizer object and pass the object
 * in APIs such as gesture interruption and gesture collection interception. For details about the APIs, see
 * native_gesture.h.
 *
 * @since 15
 */
typedef ArkUI_TouchRecognizer* ArkUI_TouchRecognizerHandle;

/**
 * @brief Defines a touch recognizer handle array, which is used when managing multiple touch recognizers in batches,
 * for example, obtaining multiple touch recognizer handles from gesture interruption information.
 *
 * @since 15
 */
typedef ArkUI_TouchRecognizerHandle* ArkUI_TouchRecognizerHandleArray;

/**
 * @brief Defines a callback function for notifying gesture recognizer destruction.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param userData Pointer to user-defined data.
 * @since 12
 */
typedef void (*ArkUI_GestureRecognizerDisposeNotifyCallback)(ArkUI_GestureRecognizer* recognizer, void* userData);

/**
 * @brief Checks whether a gesture is a system built-in gesture.
 *
 * @param event Pointer to the gesture interruption callback event.
 * @return Returns **true** if the gesture is a built-in gesture; returns **false** otherwise.
 * @since 12
 */
bool OH_ArkUI_GestureInterruptInfo_GetSystemFlag(const ArkUI_GestureInterruptInfo* event);

/**
 * @brief Obtains the pointer to the interrupted gesture recognizer.
 *
 * @param event Pointer to the gesture interruption callback event.
 * @return Pointer to the interrupted gesture recognizer.
 * @since 12
 */
ArkUI_GestureRecognizer* OH_ArkUI_GestureInterruptInfo_GetRecognizer(const ArkUI_GestureInterruptInfo* event);

/**
 * @brief Obtains the pointer to the interrupted gesture event.
 *
 * @param event Pointer to the gesture interruption callback event.
 * @return Pointer to the interrupted gesture event.
 * @since 12
 */
ArkUI_GestureEvent* OH_ArkUI_GestureInterruptInfo_GetGestureEvent(const ArkUI_GestureInterruptInfo* event);

/**
 * @brief Obtains the type of the system built-in gesture to trigger.
 *
 * @param event Pointer to the gesture interruption callback event.
 * @return Type of the system built-in gesture to trigger. The value is defined in {@link ArkUI_GestureRecognizerType}.
 *     If the triggered gesture is not a built-in gesture, **-1** is returned.
 * @since 12
 */
int32_t OH_ArkUI_GestureInterruptInfo_GetSystemRecognizerType(const ArkUI_GestureInterruptInfo* event);

/**
 * @brief Obtains touch recognizers from gesture interruption information.
 *
 * @param info Pointer to the gesture interruption information.
 * @param recognizers Pointer to the touch recognizer handle array.
 * @param size Pointer to the size of the touch recognizer array.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_GestureInterruptInfo_GetTouchRecognizers(const ArkUI_GestureInterruptInfo* info,
    ArkUI_TouchRecognizerHandleArray* recognizers, int32_t* size);

/**
 * @brief Obtains the component handle corresponding to a touch recognizer.
 *
 * @param recognizer Handle to the touch recognizer.
 * @return Component handle corresponding to the touch recognizer.
 * @since 15
 */
ArkUI_NodeHandle OH_ArkUI_TouchRecognizer_GetNodeHandle(const ArkUI_TouchRecognizerHandle recognizer);

/**
 * @brief Sends a cancel touch event to a touch recognizer in a gesture interruption callback. This API is suitable
 * for scenarios such as nested scrolling, where the parent component needs to take over scroll control. This API
 * can be used to cancel the touch event of the child component touch recognizer to avoid gesture conflicts.
 *
 * @param recognizer Handle to the touch recognizer.
 * @param info Pointer to the gesture interruption information.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_TouchRecognizer_CancelTouch(ArkUI_TouchRecognizerHandle recognizer, ArkUI_GestureInterruptInfo* info);

/**
 * @brief Obtains the gesture event type.
 *
 * @param event Pointer to the gesture event.
 * @return Gesture event action type.
 * @since 12
 */
ArkUI_GestureEventActionType OH_ArkUI_GestureEvent_GetActionType(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the original input event of the gesture.
 *
 * @param event Pointer to the gesture event.
 * @return Pointer to the input event of the gesture event.
 * @since 12
 */
const ArkUI_UIInputEvent* OH_ArkUI_GestureEvent_GetRawInputEvent(const ArkUI_GestureEvent* event);

/**
 * @brief Checks whether the event is a repeated trigger event.
 *
 * @param event Pointer to the gesture event.
 * @return Whether the event is a repeated trigger event. The value **1** means that the event is a repeated trigger
 *     event, and **0** means the opposite.
 * @since 12
 */
int32_t OH_ArkUI_LongPress_GetRepeatCount(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the velocity of a pan gesture along the main axis.
 *
 * @param event Pointer to the gesture event.
 * @return Velocity of the current gesture along the main axis, which is the arithmetic square root of the sum of the
 *     squares of the velocity on the x-axis and y-axis, in px/s.
 * @since 12
 */
float OH_ArkUI_PanGesture_GetVelocity(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the velocity of a pan gesture along the x-axis.
 *
 * @param event Pointer to the gesture event.
 * @return Velocity of the current gesture along the x-axis, in px/s.
 * @since 12
 */
float OH_ArkUI_PanGesture_GetVelocityX(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the velocity of a pan gesture along the y-axis.
 *
 * @param event Pointer to the gesture event.
 * @return Velocity of the current gesture along the y-axis, in px/s.
 * @since 12
 */
float OH_ArkUI_PanGesture_GetVelocityY(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the relative offset of a pan gesture along the x-axis.
 *
 * @param event Pointer to the gesture event.
 * @return Relative offset of the gesture along the x-axis, in px.
 * @since 12
 */
float OH_ArkUI_PanGesture_GetOffsetX(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the relative offset of a pan gesture along the y-axis.
 *
 * @param event Pointer to the gesture event.
 * @return Relative offset of the gesture along the y-axis, in px.
 * @since 12
 */
float OH_ArkUI_PanGesture_GetOffsetY(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the angle information of the swipe gesture, that is, the angle between the instantaneous direction
 * of the finger swipe and the positive horizontal direction. Based on the positive horizontal direction, if the swipe
 * direction is on the clockwise side of the positive horizontal direction, the angle ranges from 0 to 180 degrees; if
 * the swipe direction is on the counterclockwise side of the positive horizontal direction, the angle ranges from 0
 * to –180 degrees.
 *
 * @param event Pointer to the gesture event.
 * @return Angle of the swipe gesture, that is, the angle between the instantaneous direction of finger swipe and the
 *     positive horizontal direction, in deg.
 * @since 12
 */
float OH_ArkUI_SwipeGesture_GetAngle(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the average velocity of all fingers used in the swipe gesture.
 *
 * @param event Pointer to the gesture event.
 * @return Average velocity of all fingers used in the swipe gesture, in px/s.
 * @since 12
 */
float OH_ArkUI_SwipeGesture_GetVelocity(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the angle information of a rotation gesture.
 *
 * @param event Pointer to the gesture event.
 * @return Rotation angle. The unit is deg.
 * @since 12
 */
float OH_ArkUI_RotationGesture_GetAngle(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the scale ratio of a pinch gesture.
 *
 * @param event Pointer to the gesture event.
 * @return Scale factor of the pinch gesture. A value greater than 1 indicates zooming in, and a value less than 1
 *     indicates zooming out.
 * @since 12
 */
float OH_ArkUI_PinchGesture_GetScale(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the x-coordinate of the center of the pinch gesture, relative to the upper left corner of the
 * current component.
 *
 * @param event Pointer to the gesture event.
 * @return X-coordinate of the center of the pinch gesture, in px, relative to the upper left corner of the current
 *     component.
 * @since 12
 */
float OH_ArkUI_PinchGesture_GetCenterX(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the y-coordinate of the center of the pinch gesture, relative to the upper left corner of the
 * current component.
 *
 * @param event Pointer to the gesture event.
 * @return Y-coordinate of the center of the pinch gesture, in px, relative to the upper left corner of the current
 *     component.
 * @since 12
 */
float OH_ArkUI_PinchGesture_GetCenterY(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the ArkUI component to which the gesture is bound.
 *
 * @param event Pointer to the gesture event.
 * @return ArkUI component to which the gesture is bound. Returns **NULL** if the event is invalid.
 * @since 12
 */
ArkUI_NodeHandle OH_ArkUI_GestureEvent_GetNode(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains information about a gesture response chain.
 *
 * @param event Pointer to the gesture interruption callback event.
 * @param responseChain Pointer to an array of gesture recognizer handles on the response chain.
 * @param count Pointer to the number of gesture recognizer handles on the response chain.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_GetResponseRecognizersFromInterruptInfo(const ArkUI_GestureInterruptInfo* event,
    ArkUI_GestureRecognizerHandleArray* responseChain, int32_t* count);

/**
 * @brief Sets the enabled state of a gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param enabled Whether to enable the gesture recognizer. The value **true** means to enable, and **false** means
 *     the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_SetGestureRecognizerEnabled(ArkUI_GestureRecognizer* recognizer, bool enabled);

/**
 * @brief Sets whether to enable strict finger count checking. If this feature is enabled and the actual number of touch
 * fingers does not match the set number, the gesture recognition fails.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param limitFingerCount Whether to enable strict finger count checking.
 *     <br>**true**: Enforce the exact number of fingers touching the screen.
 *     <br>**false**: Do not enforce the exact number of fingers touching the screen.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 15
 */
int32_t OH_ArkUI_SetGestureRecognizerLimitFingerCount(ArkUI_GestureRecognizer* recognizer, bool limitFingerCount);

/**
 * @brief Obtains the enabled state of a gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @return **true**: enabled.
 *     <br>**false**: disabled.
 * @since 12
 */
bool OH_ArkUI_GetGestureRecognizerEnabled(ArkUI_GestureRecognizer* recognizer);

/**
 * @brief Obtains the state of a gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param state Pointer to the state of the gesture recognizer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_GetGestureRecognizerState(ArkUI_GestureRecognizer* recognizer, ArkUI_GestureRecognizerState* state);

/**
 * @brief Obtains the information about a gesture event target.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param info Double pointer to the information about a gesture event target.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_GetGestureEventTargetInfo(ArkUI_GestureRecognizer* recognizer, ArkUI_GestureEventTargetInfo** info);

/**
 * @brief Obtains whether this scrollable container component is scrolled to the top.
 *
 * @param info Pointer to the information about a gesture event target.
 * @param ret Pointer to the **ret** parameter indicating whether this scrollable container component is scrolled to the
 *     top. The value **true** means that the component is scrolled to the top, and **false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NON_SCROLLABLE_CONTAINER} if the component is not a scrollable container.
 * @since 12
 */
int32_t OH_ArkUI_GestureEventTargetInfo_IsScrollBegin(ArkUI_GestureEventTargetInfo* info, bool* ret);

/**
 * @brief Obtains whether this scrollable container component is scrolled to the bottom.
 *
 * @param info Pointer to the information about a gesture event target.
 * @param ret Pointer to the **ret** parameter indicating whether this scrollable container component is scrolled to the
 *     bottom. The value **true** means that the component is scrolled to the bottom, and **false** means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NON_SCROLLABLE_CONTAINER} if the component is not a scrollable container.
 * @since 12
 */
int32_t OH_ArkUI_GestureEventTargetInfo_IsScrollEnd(ArkUI_GestureEventTargetInfo* info, bool* ret);

/**
 * @brief Obtains the direction of a pan gesture. It is recommended to use **OH_ArkUI_GetGestureParam_DirectMask**
 * (API version 18) first, which is a unified parameter query API. **OH_ArkUI_GetPanGestureDirectionMask** is an
 * earlier API (API version 12) with the same functionality as **OH_ArkUI_GetGestureParam_DirectMask**.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param directionMask Pointer to the pan direction.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_GetPanGestureDirectionMask(ArkUI_GestureRecognizer* recognizer,
    ArkUI_GestureDirectionMask* directionMask);

/**
 * @brief Obtains whether a gesture is a built-in gesture.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @return **true**: built-in gesture.
 *     <br>**false**: non-built-in gesture.
 * @since 12
 */
bool OH_ArkUI_IsBuiltInGesture(ArkUI_GestureRecognizer* recognizer);

/**
 * @brief Obtains the tag of a gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param buffer Pointer to the output buffer.
 * @param bufferSize Size of the buffer, which limits the length of the gesture recognizer tag string that can be
 *     written.
 * @param result Pointer to the length of the copied string.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH} if the storage space is insufficient.
 * @since 12
 */
int32_t OH_ArkUI_GetGestureTag(ArkUI_GestureRecognizer* recognizer, char* buffer, int32_t bufferSize, int32_t* result);

/**
 * @brief Obtains the ID of the component bound to a gesture recognizer (in string format, that is, the value of the
 * **nodeId** attribute you set on the ArkUI component). To obtain the system-assigned integer unique identifier,
 * use **OH_ArkUI_GetGestureBindNodeUniqueId**.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param nodeId Pointer to the component ID.
 * @param size Size of the **nodeId** buffer, which limits the length of the component ID string that can be written.
 * @param result Pointer to the length of the copied string.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH} if the storage space is insufficient.
 * @since 12
 */
int32_t OH_ArkUI_GetGestureBindNodeId(ArkUI_GestureRecognizer* recognizer, char* nodeId, int32_t size,
    int32_t* result);

/**
 * @brief Obtains whether a gesture recognizer is valid.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @return **true**: The gesture recognizer is valid.
 *     <br>**false**: The gesture recognizer is invalid.
 * @since 12
 */
bool OH_ArkUI_IsGestureRecognizerValid(ArkUI_GestureRecognizer* recognizer);

/**
 * @brief Obtains custom data in the parallel built-in gesture event.
 *
 * @param event Pointer to the parallel built-in gesture event.
 * @return Pointer to user-defined data.
 * @since 12
 */
void* OH_ArkUI_ParallelInnerGestureEvent_GetUserData(ArkUI_ParallelInnerGestureEvent* event);

/**
 * @brief Obtains the current gesture recognizer in a parallel built-in gesture event.
 *
 * @param event Pointer to the parallel built-in gesture event.
 * @return Pointer to the current gesture recognizer.
 * @since 12
 */
ArkUI_GestureRecognizer* OH_ArkUI_ParallelInnerGestureEvent_GetCurrentRecognizer(
    ArkUI_ParallelInnerGestureEvent* event);

/**
 * @brief Obtains the conflicting gesture recognizers in a parallel built-in gesture event.
 *
 * @param event Pointer to the parallel built-in gesture event.
 * @param array Pointer to the array of conflicting gesture recognizers.
 * @param size Pointer to the size of the array of conflicting gesture recognizers.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_ParallelInnerGestureEvent_GetConflictRecognizers(ArkUI_ParallelInnerGestureEvent* event,
    ArkUI_GestureRecognizerHandleArray* array, int32_t* size);

/**
 * @brief Sets a callback function for notifying gesture recognizer destruction.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param callback Callback for notifying gesture recognizer destruction.
 * @param userData Pointer to the user-defined data, which is passed through to the caller in the gesture recognizer
 *     object destruction notification callback.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 12
 */
int32_t OH_ArkUI_SetArkUIGestureRecognizerDisposeNotify(ArkUI_GestureRecognizer* recognizer,
    ArkUI_GestureRecognizerDisposeNotifyCallback callback, void* userData);

/**
 * @brief Obtains the swipe direction of a gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param directMask Pointer to the swipe direction of the gesture recognizer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_DirectMask(
    ArkUI_GestureRecognizer* recognizer, ArkUI_GestureDirectionMask* directMask);

/**
 * @brief Obtains the number of fingers used by a gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param finger Pointer to the number of fingers used by the gesture recognizer.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_FingerCount(ArkUI_GestureRecognizer* recognizer, int* finger);

/**
 * @brief Checks whether a gesture recognizer has a finger count limit.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param isLimited Pointer to the parameter indicating whether the gesture recognizer has a finger count limit.
 * **true** indicates that the gesture recognizer has a finger count limit.
 * **false** indicates that the gesture recognizer does not have a finger count limit.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_limitFingerCount(ArkUI_GestureRecognizer* recognizer, bool* isLimited);

/**
 * @brief Checks whether a gesture recognizer continuously triggers event callbacks.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param isRepeat Pointer to the parameter indicating whether the gesture recognizer continuously triggers event
 *     callbacks. The value **true** means to continuously trigger event callbacks, and false means the opposite.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} if the gesture recognizer type is not
 *     supported.
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_repeat(ArkUI_GestureRecognizer* recognizer, bool* isRepeat);

/**
 * @brief Obtains the allowed movement distance range for a gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param distance Pointer to the allowed movement distance range of the gesture recognizer. The unit is px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} if the gesture recognizer type is not
 *     supported.
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_distance(ArkUI_GestureRecognizer* recognizer, double* distance);

/**
 * @brief Obtains the minimum swipe speed recognized by a gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param speed Pointer to the minimum swipe speed recognized by the gesture recognizer. The unit is px/s.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} if the gesture recognizer type is not
 *     supported.
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_speed(ArkUI_GestureRecognizer* recognizer, double* speed);

/**
 * @brief Obtains the minimum duration required to trigger a long press by a gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param duration Pointer to the minimum duration for a long press. The unit is ms.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} if the gesture recognizer type is not
 *     supported.
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_duration(ArkUI_GestureRecognizer* recognizer, int* duration);

/**
 * @brief Obtains the minimum angle change required for a rotation gesture to be recognized by a gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param angle Pointer to the minimum angle change. The unit is deg.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} if the gesture recognizer type is not
 *     supported.
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_angle(ArkUI_GestureRecognizer* recognizer, double* angle);

/**
 * @brief Obtains the movement threshold distance for gesture recognition.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param distanceThresHold Pointer to the movement distance threshold of the gesture recognizer. The unit is px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} if the gesture recognizer type is not
 *     supported.
 * @since 18
 */
int32_t OH_ArkUI_GetGestureParam_distanceThreshold(ArkUI_GestureRecognizer* recognizer, double* distanceThreshold);

/**
 * @brief Obtains the maximum movement distance allowed for gesture recognition by the long press gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param allowableMovement Pointer to the maximum movement distance of the gesture recognized by the long-press
 *     gesture recognizer, in px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} if the gesture recognizer type is not
 *     supported.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_LongPressGesture_GetAllowableMovement(ArkUI_GestureRecognizer* recognizer,
    double* allowableMovement);

/**
 * @brief Sets the minimum sliding distance threshold mapping for gesture recognition, which is used for scenarios
 * where the pan gesture recognition threshold needs to be configured based on different input tool types.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param size Number of elements in the **toolTypeArray** and **distanceArray** arrays. The value must be greater
 *     than 0 and must match the actual number of elements in **toolTypeArray** and **distanceArray**.
 * @param toolTypeArray Pointer to the array of input event tool types. The element values are specified by
 *     {@link UI_INPUT_EVENT_TOOL_TYPE}_XXX. If a value outside this range is set, the setting does not take effect.
 * @param distanceArray Pointer to the array of minimum sliding distance thresholds. The value range is (0, +∞), in
 *     px. If 0 or a negative number is passed in, the setting does not take effect. **distanceArray[i]** indicates
 *     the minimum sliding distance threshold for the tool type corresponding to **toolTypeArray[i]**.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} if the gesture recognizer type is not
 *     supported.
 * @since 19
 */
ArkUI_ErrorCode OH_ArkUI_PanGesture_SetDistanceMap(
    ArkUI_GestureRecognizer* recognizer, int size, int* toolTypeArray, double* distanceArray);

/**
 * @brief Obtains the gesture movement threshold of the gesture recognizer. This API only supports querying
 * thresholds for device types that have been modified through **OH_ArkUI_PanGesture_SetDistanceMap**. The default
 * sliding threshold can be obtained by querying the {@link UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN} type. Other types that
 * have not been set will not return the corresponding sliding thresholds.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param toolType Tool type of the input event. The value specified by {@link UI_INPUT_EVENT_TOOL_TYPE}_XXX. Only
 *     threshold querying for device types modified by **OH_ArkUI_PanGesture_SetDistanceMap** and the
 *     {@link UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN} type is supported. Other types that have not been set will not return
 *     corresponding thresholds.
 * @param distance Pointer to the movement distance threshold of the gesture recognizer. The unit is px.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} if the gesture recognizer type is not
 *     supported.
 * @since 19
 */
ArkUI_ErrorCode OH_ArkUI_PanGesture_GetDistanceByToolType(
    ArkUI_GestureRecognizer* recognizer, int toolType, double* distance);

/**
 * @brief Registers a callback that is executed after all gesture recognizers are collected. When the user begins
 * touching the screen, the system performs hit testing and collects gesture recognizers based on the touch location.
 * Subsequently, before processing any move events, the component can use this API to determine the gesture recognizers
 * that will participate in and compete for recognition.
 *
 * @param node Handle to the node on which the callback is to be set.
 * @param userData Pointer to the user-defined data, which is passed back to the caller as the **userData** parameter
 *     in the **touchTestDone** callback.
 * @param touchTestDone Callback for completion of gesture recognizer collection. **event** indicates the basic
 *     information about the gesture, **recognizers** indicates the gesture recognizer array, **count** indicates the
 *     number of gesture recognizers, and **userData** indicates the user-defined data.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_SetTouchTestDoneCallback(
    ArkUI_NodeHandle node,
    void* userData,
    void (*touchTestDone)(
        ArkUI_GestureEvent* event,
        ArkUI_GestureRecognizerHandleArray recognizers,
        int32_t count,
        void* userData
    )
);

/**
 * @brief Obtains the custom data from a gesture interruption event.
 *
 * @param event Pointer to the gesture interruption information.
 * @return Pointer to user-defined data.
 * @since 18
 */
void* OH_ArkUI_GestureInterrupter_GetUserData(ArkUI_GestureInterruptInfo* event);

/**
 * @brief Prevents a gesture recognizer from participating in the current gesture recognition before all fingers are
 * lifted. This is suitable for scenarios where a specified gesture recognizer needs to be dynamically excluded
 * during the gesture competition process. If the system has already determined the result of the gesture recognizer
 * (regardless of success or failure), calling this API will be ineffective.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 20
 */
ArkUI_ErrorCode OH_ArkUI_PreventGestureRecognizerBegin(ArkUI_GestureRecognizer* recognizer);

/**
 * @brief Sets the maximum movement distance allowed for gesture recognition by the long press gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param allowableMovement Maximum movement distance of the gesture recognized by the long-press gesture recognizer.
 *     <br>Unit: px.
 *     <br>Value range: (0, +∞). If the value is set to less than or equal to 0, the default value **15** is used.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_RECOGNIZER_TYPE_NOT_SUPPORTED} if the gesture recognizer type is not
 *     supported.
 * @since 22
 */
ArkUI_ErrorCode OH_ArkUI_LongPressGesture_SetAllowableMovement(
    ArkUI_GestureRecognizer* recognizer, double allowableMovement);

/**
 * @brief Obtains gesture recognizer handles from gesture collection interception information.
 *
 * @param info Pointer to the gesture collection interception information.
 * @param array Pointer to the gesture recognizer handle array.
 * @param size Pointer to the size of the gesture recognizer handle array.
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_GestureCollectInterceptInfo_GetResponseRecognizers(
    const ArkUI_GestureCollectInterceptInfo* info, ArkUI_GestureRecognizerHandleArray* array, int32_t* size);

/**
 * @brief Obtains touch recognizer handles from gesture collection interception information.
 *
 * @param info Pointer to the gesture collection interception information.
 * @param recognizers Pointer to the touch recognizer handle array.
 * @param size Pointer to the size of the touch recognizer handle array.
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_GestureCollectInterceptInfo_GetTouchRecognizers(const ArkUI_GestureCollectInterceptInfo* info,
    ArkUI_TouchRecognizerHandleArray* recognizers, int32_t* size);

/**
 * @brief Sets the intervention mode for gesture collection.
 *
 * @param info Pointer to the gesture collection interception information.
 * @param intervention Gesture collection intervention mode, which is of the
 *     {@link OH_ArkUI_GestureCollectIntervention} type.
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_GestureCollectInterceptInfo_SetGestureCollectIntervention(
    ArkUI_GestureCollectInterceptInfo* info, OH_ArkUI_GestureCollectIntervention intervention);

/**
 * @brief Obtains the unique ID of the component bound to a gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer.
 * @param uniqueId Pointer to the unique ID of the component bound to the gesture recognizer.
 * @return {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_GetGestureBindNodeUniqueId(const ArkUI_GestureRecognizer* recognizer, int32_t* uniqueId);

/**
 * @brief Checks whether the node bound to the touch recognizer is a descendant node of the passed component.
 *
 * @param recognizer Touch recognizer handle.
 * @param uniqueId Unique ID of the component, which can be obtained by
 *     {@link OH_ArkUI_GetGestureBindNodeUniqueId}.
 * @return **true** if the node bound to the touch recognizer is a descendant node of the passed component; **false**
 *     otherwise.
 * @since 26.0.0
 */
bool OH_ArkUI_TouchRecognizer_IsHostBelongsTo(const ArkUI_TouchRecognizerHandle recognizer, int32_t uniqueId);

/**
 * @brief Checks whether the node bound to the gesture recognizer is a descendant node of the passed component.
 *
 * @param recognizer Pointer to the gesture recognizer.
 * @param uniqueId Unique ID of the component, which can be obtained by
 *     {@link OH_ArkUI_GetGestureBindNodeUniqueId}.
 * @return **true** if the node bound to the gesture recognizer is a descendant node of the passed component; **false**
 *     otherwise.
 * @since 26.0.0
 */
bool OH_ArkUI_GestureRecognizer_IsHostBelongsTo(const ArkUI_GestureRecognizer* recognizer, int32_t uniqueId);

/**
 * @brief Defines the APIs for creating tap, long press, pan, pinch, rotation, and fling gestures as well as gesture
 * groups. This struct also supports binding gestures, removing gestures, and setting gesture interruption callbacks
 * and parallel internal gesture callbacks, for configuring and managing touch interaction recognition and event
 * processing of components.
 *
 * When using this module to configure gestures, it is recommended to follow the process below: call APIs such as
 * {@link createTapGesture} to create a gesture recognizer, call {@link setGestureEventTarget} to register the gesture
 * event callback, and then call {@link addGestureToNode} to bind the gesture recognizer to a component node. When
 * the gesture is no longer used, call {@link dispose} to release the gesture resources. If you need to unbind the
 * node first, call {@link removeGestureFromNode} before calling **dispose()**. For gesture competition scenarios,
 * you can configure the response policy through the gesture priority, mask mode, or
 * {@link setGestureInterrupterToNode}. For scenarios where internal gestures of a component and external custom
 * gestures need to be recognized in parallel, call {@link setInnerGestureParallelTo} to set the parallel internal
 * gesture event callback.
 *
 * @since 12
 */
typedef struct {
    /**
     * The struct version is 1.
     */
    int32_t version;

    /**
     * @brief Creates a tap gesture. The gesture recognizer returned after the gesture is created successfully can
     * be added to a node through **addGestureToNode()**. When the gesture is no longer used, call **dispose()** to
     * release the resources. After the release, the gesture recognizer must not be used again. If you need to unbind
     * the node first, call **removeGestureFromNode()** before **dispose()**.
     * 1. This API is used to trigger a tap gesture with one, two, or more taps.
     * 2. When multi-tap is configured, the timeout between the last finger up of the previous tap and the first
     *    finger down of the next tap is 300 ms.
     * 3. If the distance between the last tapped position and the current tapped position exceeds 60 vp, gesture
     *    recognition fails.
     * 4. When multiple fingers are configured for a gesture, the recognition fails if the number of fingers touching
     *    the screen within 300 ms of the first finger's being pressed is less than the required count, or if the
     *    number of fingers lifted from the screen within 300 ms of the first finger's being lifted is less than the
     *    required count.
     * 5. When the number of fingers touching the screen exceeds the set value, the gesture can be recognized.
     *
     * @param countNum Number of consecutive taps to recognize. The value is an integer greater than 0. If the value
     *     is less than 1, the default value **1** is used.
     * @param fingersNum Number of fingers that trigger the tap. The minimum value is 1 and the maximum value is 10.
     *     If the value is less than 1, the minimum value **1** is used. If the value is greater than 10, the
     *     maximum value **10** is used.
     * @return Pointer to the created tap gesture recognizer, which can be used to bind a node, register a callback,
     *     or manage tap gesture recognition.
     */
    ArkUI_GestureRecognizer* (*createTapGesture)(int32_t countNum, int32_t fingersNum);

    /**
     * @brief Creates a long press gesture. The gesture recognizer returned after the gesture is created successfully
     * can be added to a node through **addGestureToNode()**. When the gesture is no longer used, call **dispose()**
     * to release the resources. After the release, the gesture recognizer must not be used again. If you need to
     * unbind the node first, call **removeGestureFromNode()** before **dispose()**.
     * 1. This API is used to trigger a long press gesture, which requires one or more fingers with a minimum 500 ms
     *    hold-down time.
     * 2. In components that support drag actions by default, such as **Text**, **TextInput**, **TextArea**,
     *    **HyperLink**, **Image**, and **RichEditor**, the long press gesture may conflict with the drag action. If
     *    this occurs, the event priority is determined as follows: If the duration of the long press gesture is less
     *    than 500 ms, the long press gesture receives a higher response priority than the drag action. If the
     *    duration of the long press gesture is greater than or equal to 500 ms, the drag action receives a higher
     *    response priority than the long press gesture.
     * 3. If a finger moves more than 15 px after being pressed, the gesture recognition fails.
     *
     * @param fingersNum Minimum number of fingers that triggers the long press. The value ranges from 1 to 10. If
     *     the value is out of range, the default value **1** is used.
     * @param repeatResult Whether to trigger the event callback continuously.
     *     <br>**true**: triggers continuously; **false**: does not trigger continuously.
     * @param durationNum Minimum duration that triggers the long press, in milliseconds (ms). The valid value is
     *     greater than 0. If the value is less than or equal to 0, the default value 500 ms is used. When the
     *     component supports dragging by default, if the long press trigger time is less than 500 ms, the long press
     *     event takes precedence over the drag event; if the long press trigger time is greater than or equal to
     *     500 ms, the drag event takes precedence over the long press event.
     * @return Pointer to the created long press gesture recognizer, which can be used to bind a node, register a
     *     callback, or manage long press gesture recognition.
     */
    ArkUI_GestureRecognizer* (*createLongPressGesture)(int32_t fingersNum, bool repeatResult, int32_t durationNum);

    /**
     * @brief Creates a pan gesture. Different from {@link createSwipeGesture} (swipe gesture), the pan gesture is
     * triggered based on the minimum drag distance, while the swipe gesture is triggered based on the minimum swipe
     * speed. The gesture recognizer returned after the gesture is created successfully can be added to a node
     * through **addGestureToNode()**. When the gesture is no longer used, call **dispose()** to release the
     * resources. After the release, the gesture recognizer must not be used again. If you need to unbind the node
     * first, call **removeGestureFromNode()** before **dispose()**.
     * 1. This API is used to trigger a pan gesture when the movement distance of a finger on the screen exceeds the
     *    minimum value.
     * 2. If a swipe on the **Tabs** component and this pan gesture event occur at the same time, set **distanceNum**
     *    to **1** to make dragging more sensitive and avoid response conflicts between the **Tabs** component swipe
     *    event and this pan gesture event.
     *
     * @param fingersNum Minimum number of fingers that trigger the pan gesture. The value ranges from 1 to 10. If
     *     the value is out of range, the default value **1** is used.
     * @param directions Gesture direction that triggers the pan gesture. This enumerated value supports the logical
     *     AND (&) and logical OR (\|) operations. You can select the direction based on your service requirements:
     *     **GESTURE_DIRECTION_HORIZONTAL** applies to scenarios where only horizontal panning is recognized,
     *     **GESTURE_DIRECTION_VERTICAL** applies to scenarios where only vertical panning is recognized,
     *     **GESTURE_DIRECTION_LEFT/RIGHT/UP/DOWN** applies to scenarios where only a single panning direction is
     *     recognized, **GESTURE_DIRECTION_ALL** applies to scenarios where the gesture is triggered in any
     *     direction, and **GESTURE_DIRECTION_NONE** indicates that the gesture event is not triggered in any
     *     direction.
     * @param distanceNum Minimum pan distance that triggers the pan gesture event, in px. The value range is
     *     (0, +∞). If the value is less than or equal to 0, the default value **5px** is used.
     * @return Pointer to the created pan gesture recognizer, which can be used to bind a node, register a callback,
     *     or manage pan gesture recognition.
     */
    ArkUI_GestureRecognizer* (*createPanGesture)(
        int32_t fingersNum, ArkUI_GestureDirectionMask directions, double distanceNum);

    /**
     * @brief Creates a pinch gesture. The gesture recognizer returned after the gesture is created successfully can
     * be added to a node through **addGestureToNode()**. When the gesture is no longer used, call **dispose()** to
     * release the resources. After the release, the gesture recognizer must not be used again. If you need to unbind
     * the node first, call **removeGestureFromNode()** before **dispose()**.
     * 1. This API is used to trigger a pinch gesture, which requires two to five fingers with a minimum pinch
     *    distance of pixels specified by **distanceNum**.
     * 2. The number of fingers triggering the gesture can be greater than the value of **fingersNum**, but only the
     *    first fingers equal to the value of **fingersNum** participate in the gesture calculation.
     *
     * @param fingersNum Minimum number of fingers required to trigger a pinch gesture. The value ranges from 2 to 5.
     *     If the value is out of range, the default value **2** is used.
     * @param distanceNum Minimum recognition distance, in px. The value range is (0, +∞). If the value is less than
     *     or equal to 0, the default value **5px** is used.
     * @return Pointer to the created pinch gesture recognizer, which can be used to bind a node, register a
     *     callback, or manage pinch gesture recognition.
     */
    ArkUI_GestureRecognizer* (*createPinchGesture)(int32_t fingersNum, double distanceNum);

    /**
     * @brief Creates a rotation gesture. The gesture recognizer returned after the gesture is created successfully
     * can be added to a node through **addGestureToNode()**. When the gesture is no longer used, call **dispose()**
     * to release the resources. After the release, the gesture recognizer must not be used again. If you need to
     * unbind the node first, call **removeGestureFromNode()** before **dispose()**.
     * 1. This API is used to trigger a rotation gesture, which requires two to five fingers with a minimum 1-degree
     *    rotation angle (specified by **angleNum**).
     * 2. The number of fingers triggering the gesture can be greater than the value of **fingersNum**, but only the
     *    first two fingers that are pressed participate in the gesture calculation.
     *
     * @param fingersNum Minimum number of fingers required to trigger rotation. The value ranges from 2 to 5. If the
     *     value is out of range, the default value **2** is used.
     * @param angleNum Minimum angle change required to trigger the rotation gesture. The value ranges from (0, 360],
     *     in deg. Default value: **1deg**. If the value passed is less than or equal to 0 or greater than 360, it is
     *     converted to the default value **1**.
     * @return Pointer to the created rotation gesture recognizer, which can be used to bind a node, register a
     *     callback, or manage rotation gesture recognition.
     */
    ArkUI_GestureRecognizer* (*createRotationGesture)(int32_t fingersNum, double angleNum);

    /**
     * @brief Creates a swipe gesture. The gesture recognizer returned after the gesture is created successfully can
     * be added to a node through **addGestureToNode()**. When the gesture is no longer used, call **dispose()** to
     * release the resources. After the release, the gesture recognizer must not be used again. If you need to unbind
     * the node first, call **removeGestureFromNode()** before **dispose()**. This API is used to implement a swipe
     * gesture, which can be recognized when the swipe speed (px/s) is higher than that specified by **speedNum**.
     *
     * @param fingersNum Minimum number of fingers required to trigger the swipe. The value ranges from 1 to 10. If
     *     the value is out of range, the default value **1** is used.
     * @param directions Swipe direction that triggers the swipe gesture. Select the direction based on the swipe
     *     direction to be recognized: **GESTURE_DIRECTION_HORIZONTAL** applies to horizontal swipe scenarios,
     *     **GESTURE_DIRECTION_VERTICAL** applies to vertical swipe scenarios,
     *     **GESTURE_DIRECTION_LEFT/RIGHT/UP/DOWN** applies to scenarios where only a single specified swipe
     *     direction is recognized, **GESTURE_DIRECTION_ALL** applies to scenarios where a swipe in any direction can
     *     be triggered, and **GESTURE_DIRECTION_NONE** indicates that no gesture event is triggered in any
     *     direction.
     * @param speedNum Minimum speed for recognizing the swipe, in px/s. The value range is (0, +∞). If the value is
     *     less than or equal to 0, the default value **100px/s** is used.
     * @return Pointer to the created swipe gesture recognizer, which can be used to bind a node, register a
     *     callback, or manage swipe gesture recognition.
     */
    ArkUI_GestureRecognizer* (*createSwipeGesture)(
        int32_t fingersNum, ArkUI_GestureDirectionMask directions, double speedNum);

    /**
     * @brief Creates a gesture group. After it is created successfully, call **addChildGesture()** to add child
     * gestures to the gesture group, and then bind the gesture group to a node through **addGestureToNode()**. When
     * a child gesture is no longer used, call **removeChildGesture()** as needed to remove the child gesture, and
     * call **dispose()** to release the resources. After the release, the gesture group must not be used again. If
     * you need to unbind the node first, call **removeGestureFromNode()** before **dispose()**.
     *
     * @param gestureMode Gesture group mode. **SEQUENTIAL_GROUP** applies to scenarios where multiple gestures need
     *     to be recognized in registration order. **PARALLEL_GROUP** applies to scenarios where multiple gestures
     *     need to be recognized simultaneously without affecting each other. **EXCLUSIVE_GROUP** applies to mutually
     *     exclusive scenarios where multiple gestures compete at the same time and the recognition of the others
     *     ends once any gesture is recognized successfully.
     * @return Pointer to the created gesture group, which can be used to add, remove, or manage child gestures in
     *     group.
     */
    ArkUI_GestureRecognizer* (*createGroupGesture)(ArkUI_GroupGestureMode gestureMode);

    /**
     * @brief Disposes of the gesture created through **createTapGesture()**, **createLongPressGesture()**,
     * **createPanGesture()**, **createPinchGesture()**, **createRotationGesture()**, **createSwipeGesture()**,
     * **createGroupGesture()**, or **createTapGestureWithDistanceThreshold()** to release the resources. If the
     * gesture has been added to a node through **addGestureToNode()**, it is recommended to call
     * **removeGestureFromNode()** to unbind the node before calling **dispose()**. After **dispose()** is called,
     * the gesture pointer must not be used again.
     *
     * @param recognizer Pointer to the gesture to be disposed of.
     */
    void (*dispose)(ArkUI_GestureRecognizer* recognizer);

    /**
     * @brief Adds a child gesture to the gesture group created through **createGroupGesture()**. You need to create
     * the gesture group and the child gesture first, and then call **addChildGesture()** to establish the
     * association. After the child gesture is added, it participates in the recognition process of the gesture
     * group. When the child gesture no longer needs to participate in the gesture group recognition, call
     * **removeChildGesture()** to remove the association.
     *
     * @param group Pointer to the gesture group to which the child gesture is to be added.
     * @param child Pointer to the child gesture recognizer to be added to the gesture group.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs, for example, adding a
     *     gesture to a non-gesture-group object.
     */
    int32_t (*addChildGesture)(ArkUI_GestureRecognizer* group, ArkUI_GestureRecognizer* child);

    /**
     * @brief Removes the child gesture that has been added through **addChildGesture()** from the gesture group.
     * After the call, the child gesture no longer participates in the gesture group recognition as a child gesture
     * of the gesture group.
     *
     * @param group Pointer to the gesture group from which the child gesture is to be removed.
     * @param child Pointer to the child gesture recognizer to be removed from the gesture group.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*removeChildGesture)(ArkUI_GestureRecognizer* group, ArkUI_GestureRecognizer* child);

    /**
     * @brief Sets the gesture association callback, for scenarios where you need to listen for events such as
     * gesture triggering, updating, or ending and perform business processing. You need to create a gesture
     * recognizer through APIs such as **createTapGesture()** and **createLongPressGesture()** first, call
     * **setGestureEventTarget()** to set the event callback, and bind the gesture to a node through
     * **addGestureToNode()**. It is recommended to call **setGestureEventTarget()** before **addGestureToNode()**
     * to ensure that the gesture can respond to events immediately after being bound to the node.
     *
     * @param recognizer Pointer to the gesture recognizer to which the callback event is bound.
     * @param actionTypeMask Set of gesture event types to respond to. Multiple event types can be registered at a
     *     time, and the callback event type is distinguished in the callback. Example: **actionTypeMask =
     *     GESTURE_EVENT_ACTION_ACCEPT \| GESTURE_EVENT_ACTION_UPDATE;**
     * @param extraParams Pointer to the context data passed when **targetReceiver** is called. Pass the
     *     corresponding data pointer when custom service data needs to be accessed in the callback.
     * @param targetReceiver Gesture event callback function, with the signature **void (*targetReceiver)
     *     (ArkUI_GestureEvent* event, void* extraParams)**, used to process events of the registered gesture types.
     *     Here, **event** indicates the gesture callback data, and **extraParams** indicates the context data passed
     *     during registration. No value is returned.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*setGestureEventTarget)(
        ArkUI_GestureRecognizer* recognizer, ArkUI_GestureEventActionTypeMask actionTypeMask, void* extraParams,
        void (*targetReceiver)(ArkUI_GestureEvent* event, void* extraParams));

    /**
     * @brief Adds the gesture created through APIs such as **createTapGesture()** and **createLongPressGesture()**
     * to a UI component. You should create a gesture recognizer first, and then call **addGestureToNode()** to bind
     * the gesture to the node. When the node no longer needs to respond to the gesture, call
     * **removeGestureFromNode()** to unbind it, and call **dispose()** when releasing resources.
     *
     * @param node Pointer to the ArkUI component node to which the gesture is to be bound.
     * @param recognizer Pointer to the gesture recognizer to be bound to this node.
     * @param mode Gesture priority mode, which is used to set the response priority of the gesture after it is
     *     added to the node and its competition relationship with other gestures.
     * @param mask Gesture mask mode, which is used to control the masking or pass-through relationship between the
     *     gesture and other gestures after it is added to the node.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*addGestureToNode)(
        ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer, ArkUI_GesturePriority mode, ArkUI_GestureMask mask);

    /**
     * @brief Removes the gesture that has been added through **addGestureToNode()** from the node. After the call,
     * the node no longer responds to the gesture. If you need to release the gesture resources, it is recommended
     * to call **removeGestureFromNode()** to unbind the node first, and then call **dispose()**.
     *
     * @param node Pointer to the node from which the gesture is to be removed.
     * @param recognizer Pointer to the gesture recognizer to be removed.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*removeGestureFromNode)(ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer);

    /**
     * @brief Sets the node gesture interruption callback, for scenarios where you need to determine whether the
     * gesture continues to be recognized based on service conditions, such as handling gesture conflicts between
     * parent and child nodes or dynamically controlling gesture responses. This callback applies to gestures added
     * to the node through **addGestureToNode()** and built-in gestures of the component. It is triggered during
     * gesture recognition, and you can determine whether the gesture continues to be recognized or is interrupted
     * through the callback result.
     *
     * @param node Pointer to the ArkUI node for which the gesture interruption callback is to be set.
     * @param interrupter Pointer to the interruption callback. **info** returns the gesture interruption data. If
     *     **interrupter** returns **GESTURE_INTERRUPT_RESULT_CONTINUE**, the gesture recognition process continues.
     *     If it returns **GESTURE_INTERRUPT_RESULT_REJECT**, the gesture recognition process is paused. If this
     *     parameter is set to a null pointer, the callback function is unregistered.
     *     <br>**Note:** After the event interruption callback is registered, it will be available in subsequent
     *     single-gesture processing. That is, even if you use the **setGestureInterrupterToNode** API to reset the
     *     gesture interruption callback to **nullptr** or use the **dispose** API to dispose of the gesture that is
     *     about to be triggered, the callback will still respond when the trigger condition is met. If the object
     *     used in this callback has been released before the callback is triggered, ensure that the object is still
     *     valid when the callback is triggered, for example, by checking whether the object has been released
     *     before use, or by extending the object's lifecycle until after the callback is triggered.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*setGestureInterrupterToNode)(
        ArkUI_NodeHandle node, ArkUI_GestureInterruptResult (*interrupter)(ArkUI_GestureInterruptInfo* info));

    /**
     * @brief Obtains the gesture type.
     *
     * @param recognizer Pointer to the gesture recognizer.
     * @return Gesture type of the gesture recognizer.
     */
    ArkUI_GestureRecognizerType (*getGestureType)(ArkUI_GestureRecognizer* recognizer);

    /**
     * @brief Sets the parallel inner gesture event callback, for scenarios where internal gestures of a component
     * and external custom gestures need to be recognized in parallel. You need to create a custom gesture recognizer
     * through APIs such as **createPanGesture()** first, bind the gesture to the node through **addGestureToNode()**,
     * and call **setInnerGestureParallelTo()** to set the parallel inner gesture event callback. The gesture
     * recognizer returned by the callback function **parallelInnerGesture** should be a custom gesture recognizer
     * created through the **create** series APIs, used for parallel recognition with the inner gestures of the
     * component.
     *
     * Note: This callback is triggered only when the gestures bound to the node include a pan gesture (created by
     * **createPanGesture**). If the node has no pan gesture bound, this callback is not triggered.
     *
     * @param node Pointer to the ArkUI node for which the parallel inner gesture event callback is to be set.
     * @param userData Pointer to the user-defined data, which is passed through as the context data of the parallel
     *     inner gesture event callback after being set, for you to use when processing the callback. Pass
     *     **nullptr** when no additional context needs to be passed.
     * @param parallelInnerGesture Parallel inner gesture event callback, with the signature
     *     ArkUI_GestureRecognizer* (*parallelInnerGesture)(ArkUI_ParallelInnerGestureEvent* event), used to return
     *     the pointer to the gesture recognizer that needs to be recognized in parallel with the inner gesture based
     *     on the parallel inner gesture event data. Here, **event** indicates the parallel inner gesture event data,
     *     and the return value is the pointer to the gesture recognizer that needs to be recognized in parallel.
     * @return Result code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*setInnerGestureParallelTo)(
        ArkUI_NodeHandle node, void* userData, ArkUI_GestureRecognizer* (*parallelInnerGesture)(
            ArkUI_ParallelInnerGestureEvent* event));

    /**
     * @brief Creates a tap gesture with a movement range limit. The gesture recognizer returned after the gesture is
     * created successfully can be added to a node through **addGestureToNode()**. When the gesture is no longer
     * used, call **dispose()** to release the resources. After the release, the gesture recognizer must not be used
     * again. If you need to unbind the node first, call **removeGestureFromNode()** before **dispose()**.
     * 1. This API is used to trigger a tap gesture with one, two, or more taps.
     * 2. If multi-tap is configured, the timeout between the last finger up of the previous tap and the first finger
     *    down of the next tap is 300 ms.
     * 3. If the distance between the last tapped position and the current tapped position exceeds 60 vp, gesture
     *    recognition fails.
     * 4. When multiple fingers are configured for a gesture, the recognition fails if the number of fingers touching
     *    the screen within 300 ms of the first finger's being pressed is less than the required count, or if the
     *    number of fingers lifted from the screen within 300 ms of the first finger's being lifted is less than the
     *    required count.
     * 5. When the number of fingers touching the screen exceeds the set value, the gesture can be recognized.
     * 6. If the finger moves beyond the preset distance limit, gesture recognition fails.
     *
     * @param countNum Number of consecutive taps to recognize. The value is a positive integer. If the value is set
     *     to less than 1, it is converted to the default value **1**.
     * @param fingersNum Number of fingers that trigger the tap. The minimum is 1 and the maximum is 10. If the value
     *     is set to less than 1, it is processed as the minimum value **1**. If the value is set to greater than 10,
     *     it is processed as the maximum value **10**.
     * @param distanceThreshold Allowed movement distance range of the fingers, in vp. The value range is (0, +∞).
     *     If the value is set to less than or equal to 0, it is converted to the default value (infinity).
     * @return Pointer to the created tap gesture recognizer with a movement range limit. It can be used to bind a
     *     node, register a callback, or manage tap gesture recognition.
     */
    ArkUI_GestureRecognizer* (*createTapGestureWithDistanceThreshold)(
        int32_t countNum, int32_t fingersNum, double distanceThreshold);
} ArkUI_NativeGestureAPI_1;

/**
 * @brief Defines a collection of gesture APIs. Based on {@link ArkUI_NativeGestureAPI_1}, the capability of setting
 * a gesture interruption event callback function is extended, which is used to continue or interrupt a gesture based
 * on the callback result during gesture recognition. You can access basic gesture APIs through **gestureApi1** and
 * use {@link setGestureInterrupterToNode} to handle gesture interruption.
 *
 * @since 18
 */
typedef struct {
    /**
     * @brief Pointer to the **ArkUI_NativeGestureAPI_1** struct.
     *
     */
    ArkUI_NativeGestureAPI_1* gestureApi1;

    /**
     * @brief Sets the callback function for gesture interruption events. It is applicable to scenarios where you
     * need to decide, based on the current interaction state during gesture recognition, whether the gesture
     * continues to respond or is interrupted.
     *
     * @param node ArkUI node handle for which you want to set a gesture interruption callback function.
     * @param userData Pointer to the user-defined data, which is used by the gesture interruption callback function
     *     to associate context. If no context needs to be associated, pass a null pointer, in which case the custom
     *     context data cannot be obtained in the callback function. If a non-null pointer is passed, ensure that
     *     the data can still be safely accessed while the callback function is being triggered.
     * @param interrupter Pointer to the gesture interruption callback function. **info** returns the gesture
     *     interruption data. If **interrupter** returns **GESTURE_INTERRUPT_RESULT_CONTINUE**, the gesture
     *     recognition process continues. If it returns **GESTURE_INTERRUPT_RESULT_REJECT**, the gesture recognition
     *     process is paused. If this parameter is set to a null pointer, the callback function is unregistered.
     *     <br>**Note:** After the gesture interruption callback function is registered, it will be available in
     *     subsequent single-gesture processing. That is, even if you reset the callback function to **nullptr** in
     *     the same gesture processing flow or use the **dispose** API to dispose of the gesture that is about to be
     *     triggered, the callback function will still respond when the trigger condition is met. If the object
     *     referenced in the callback function may have been released before the callback is triggered, ensure that
     *     the object can still be safely accessed while the callback function is being triggered.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*setGestureInterrupterToNode)(ArkUI_NodeHandle node, void* userData,
        ArkUI_GestureInterruptResult (*interrupter)(ArkUI_GestureInterruptInfo* info));
} ArkUI_NativeGestureAPI_2;

/**
 * @brief Defines a collection of gesture APIs, including gesture APIs in the {@link ArkUI_NativeGestureAPI_1} and
 * {@link ArkUI_NativeGestureAPI_2} structs as well as new gesture APIs.
 *
 * This API collection supports setting parallel gesture event callbacks for ArkUI nodes. The callback can select,
 * from the conflicting gesture recognizers on the response chain, the object that needs to be recognized in
 * parallel with the current gesture. For details about the related event data, see
 * {@link ArkUI_ParallelGestureEvent}.
 *
 * @since 26.0.0
 */
typedef struct {
    /**
     * @brief Pointer to the **ArkUI_NativeGestureAPI_2** struct.
     *
     * @since 26.0.0
     */
    ArkUI_NativeGestureAPI_2* gestureApi2;

    /**
     * @brief Sets the callback function for parallel gesture events. When the callback is triggered, you can
     * return, from the conflicting gesture recognizers provided by the event, an object that needs to be recognized
     * in parallel with the current gesture. This API applies to scenarios where your custom gesture needs to be
     * processed in parallel with gestures of other components on the response chain.
     *
     * @param node ArkUI node handle for which you want to set a parallel gesture event callback.
     * @param userData Pointer to the user-defined data, used to pass your custom context information in the parallel
     *     gesture event callback. You can pass **nullptr** when no context needs to be associated. If a non-null
     *     pointer is passed, you must ensure the security of the data lifecycle. If the data is released during the
     *     callback, the callback execution may be abnormal.
     * @param parallelGesture Pointer to the callback function for a parallel gesture event. **event** indicates the
     *     parallel gesture event object, which contains the gesture event information when this callback is
     *     triggered. **parallelGesture** returns the pointer to the recognizer for the gesture that needs to be
     *     recognized parallelly.
     * @return {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     * @since 26.0.0
     */
    ArkUI_ErrorCode (*setGestureParallelTo)(
        ArkUI_NodeHandle node, void* userData, ArkUI_GestureRecognizer* (*parallelGesture)(
            ArkUI_ParallelGestureEvent* event));
} ArkUI_NativeGestureAPI_3;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_GESTURE_H
/** @} */