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
 * @brief Declares the APIs of **NativeGesture**.
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
 * @brief Defines a gesture recognizer.
 *
 * @since 12
 */
typedef struct ArkUI_GestureRecognizer ArkUI_GestureRecognizer;

/**
 * @brief Defines gesture interruption information.
 *
 * @since 12
 */
typedef struct ArkUI_GestureInterruptInfo ArkUI_GestureInterruptInfo;

/**
 * @brief Defines a gesture event.
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
 * @brief Enumerates gesture event modes.
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
 * @brief Enumerates gesture group modes.
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
 * @brief Enumerates gesture masking modes.
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
 * @brief Defines the gesture recognizer handle.
 *
 * @since 12
 */
typedef ArkUI_GestureRecognizer* ArkUI_GestureRecognizerHandle;

/**
 * @brief Defines the gesture recognizer handle array.
 *
 * @since 12
 */
typedef ArkUI_GestureRecognizerHandle* ArkUI_GestureRecognizerHandleArray;

/**
 * @brief Defines gesture event target information.
 *
 * @since 12
 */
typedef struct ArkUI_GestureEventTargetInfo ArkUI_GestureEventTargetInfo;

/**
 * @brief Defines a parallel internal gesture event.
 *
 * @since 12
 */
typedef struct ArkUI_ParallelInnerGestureEvent ArkUI_ParallelInnerGestureEvent;

/**
 * @brief Defines a parallel gesture event. This struct is used by the callback function {@link setGestureParallelTo}
 * for the parallel gesture event.
 *
 * @since 26.0.0
 */
typedef struct ArkUI_ParallelGestureEvent ArkUI_ParallelGestureEvent;

/**
 * @brief Defines a touch recognizer.
 *
 * @since 15
 */
typedef struct ArkUI_TouchRecognizer ArkUI_TouchRecognizer;

/**
 * @brief Defines a touch recognizer handle.
 *
 * @since 15
 */
typedef ArkUI_TouchRecognizer* ArkUI_TouchRecognizerHandle;

/**
 * @brief Defines an array of touch recognizer handle.
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
 * @brief Checks whether a gesture is a built-in gesture of the component.
 *
 * @param event Indicates the pointer to the gesture interruption information.
 * @return Returns <b>true</b> if the gesture is a built-in gesture; returns <b>false</b> otherwise.

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
 * @brief Sends a cancel touch event to a touch recognizer in a gesture interruption callback.
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
 * @return Type of the gesture event.
 * @since 12
 */
ArkUI_GestureEventActionType OH_ArkUI_GestureEvent_GetActionType(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains gesture input.
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
 * @return Velocity of the pan gesture along the main axis, in px/s. The value is the square root of the sum of the
 *     squares of the velocity on the x-axis and y-axis.
 * @since 12
 */
float OH_ArkUI_PanGesture_GetVelocity(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the velocity of a pan gesture along the x-axis.
 *
 * @param event Pointer to the gesture event.
 * @return Velocity of the pan gesture along the x-axis, in px/s.
 * @since 12
 */
float OH_ArkUI_PanGesture_GetVelocityX(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the velocity of a pan gesture along the y-axis.
 *
 * @param event Pointer to the gesture event.
 * @return Velocity of the pan gesture along the y-axis, in px/s.
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
 * @brief Angle of the swipe gesture, that is, the angle between the instantaneous direction of finger sliding and the
 * positive horizontal direction. The unit is deg.
 * With the positive horizontal direction as the reference, when the sliding direction is on the clockwise side of the
 * positive horizontal direction, the angle ranges from 0 to 180 degrees; when on the counterclockwise side, the angle
 * ranges from 0 to –180 degrees.
 *
 * @param event Pointer to the gesture event.
 * @return Angle of the swipe gesture, which is the result obtained based on the aforementioned formula.
 * The unit is deg.
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
 * @return Scale factor.
 * @since 12
 */
float OH_ArkUI_PinchGesture_GetScale(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the x-coordinate of the center of the pinch gesture, in vp, relative to the upper left corner of the
 * current component.
 *
 * @param event Pointer to the gesture event.
 * @return X-coordinate of the center of the pinch gesture, in px, relative to the upper left corner of the current
 *     component.
 * @since 12
 */
float OH_ArkUI_PinchGesture_GetCenterX(const ArkUI_GestureEvent* event);

/**
 * @brief Obtains the y-coordinate of the center of the pinch gesture, in vp, relative to the upper left corner of the
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
 * @param enabled Enabled state. The value **true** means that the gesture recognizer is enabled, and **false** means
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
 * @brief Obtains the direction of a pan gesture.
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
 * @param bufferSize Size of the output buffer.
 * @param result Pointer to the length of the copied string.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH} if the buffer is not large enough.
 * @since 12
 */
int32_t OH_ArkUI_GetGestureTag(ArkUI_GestureRecognizer* recognizer, char* buffer, int32_t bufferSize, int32_t* result);

/**
 * @brief Obtains the ID of the component linked to a gesture recognizer.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param nodeId Pointer to the component ID.
 * @param size Size of the output buffer.
 * @param result Pointer to the length of the copied string.
 * @return Result code.
 *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *     <br>Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_NOT_ENOUGH} if the buffer is not large enough.
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
 * @param callback Callback function for notifying gesture recognizer destruction.
 * @param userData Pointer to user-defined data.
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
 * @param distanceThresHold Movement threshold.
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
 * @param allowableMovement Pointer to the maximum movement distance allowed for gesture recognition by the long press
 *     gesture recognizer.
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
 * @brief Sets the minimum sliding distance threshold mapping for gesture recognition.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param size Size of the array of minimum sliding distance thresholds.
 * @param toolTypeArray Pointer to the array of tool types for which thresholds are set. If a value other than
 *     {@link UI_INPUT_EVENT_TOOL_TYPE}_XXX is set, the setting does not take effect.
 * @param distanceArray Pointer to the array of minimum sliding distances. The unit is px.
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
 * @brief Obtains the movement distance threshold for gesture recognition for a specific input device type. This API
 * only returns values for device types previously set using **OH_ArkUI_PanGesture_SetDistanceMap**. The default
 * movement distance threshold can be obtained by querying the {@link UI_INPUT_EVENT_TOOL_TYPE_UNKNOWN} type. Other
 * types that have not been set are not returned.
 *
 * @param recognizer Pointer to the gesture recognizer instance.
 * @param toolType Tool type for which you want to obtain the threshold.
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
 * @param userData Pointer to user-defined data.
 * @param touchTestDone Callback for completion of gesture recognizer collection.
 *     - event: Basic information of the gesture.
 *     - recognizers: Array of gesture recognizers.
 *     - count: Number of gesture recognizers.
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
 * lifted. If the system has already determined the result of the gesture recognizer (regardless of success or failure),
 *  calling this API will be ineffective.
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
 * @param allowableMovement Maximum movement distance allowed for gesture recognition by the long press gesture
 *     recognizer.
 *     <br>The unit is px.
 *     <br>Value range: (0, +∞). If the value is less than or equal to 0, the default value **15** is used.
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
 * @param uniqueId Unique ID of the component.
 * @return **true** if the node bound to the touch recognizer is a descendant node of the passed component; **false**
 *     otherwise.
 * @since 26.0.0
 */
bool OH_ArkUI_TouchRecognizer_IsHostBelongsTo(const ArkUI_TouchRecognizerHandle recognizer, int32_t uniqueId);

/**
 * @brief Checks whether the node bound to the gesture recognizer is a descendant node of the passed component.
 *
 * @param recognizer Pointer to the gesture recognizer.
 * @param uniqueId Unique ID of the component.
 * @return **true** if the node bound to the gesture recognizer is a descendant node of the passed component; **false**
 *     otherwise.
 * @since 26.0.0
 */
bool OH_ArkUI_GestureRecognizer_IsHostBelongsTo(const ArkUI_GestureRecognizer* recognizer, int32_t uniqueId);

/**
 * @brief Defines the gesture APIs.
 *
 * @since 12
 */
typedef struct {
    /**
     * The struct version is 1.
     */
    int32_t version;

    /**
     * @brief Creates a tap gesture.
     *
     * @param countNum Number of consecutive taps. If the value is less than 1 or is not set, the default value **1** is
     *     used.
     * @param fingersNum Number of fingers required to trigger the tap gesture. The value ranges from 1 to 10. If the
     *     value is less than 1 or is not set, the default value **1** is used.
     * @return Returns the pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createTapGesture)(int32_t countNum, int32_t fingersNum);

    /**
     * @brief Creates a long press gesture.
     *
     * @param fingersNum Minimum number of fingers to trigger a long press gesture. The value ranges from 1 to 10. If
     *     the value is out of the range, the default value **1** is used.
     * @param repeatResult Whether to continuously trigger the event callback.
     *     <br>The value **true** means to continuously trigger event callbacks, and **false** means the opposite.
     * @param durationNum Minimum hold-down time, in ms. If the value is less than or equal to 0, the default value **
     *     500** is used.
     * @return Returns the pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createLongPressGesture)(int32_t fingersNum, bool repeatResult, int32_t durationNum);

    /**
     * @brief Creates a swipe gesture.
     *
     * @param fingersNum Minimum number of fingers to trigger a pan gesture. The value ranges from 1 to 10. If the value
     *     is less than 1 or is not set, the default value **1** is used.
     * @param directions Pan direction. The value supports the AND (&) and OR (\|) operations.
     * @param distanceNum Minimum pan distance to trigger the gesture, in px. If this parameter is set to a value less
     *     than or equal to 0, the default value **5px** is used.
     * @return Pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createPanGesture)(
        int32_t fingersNum, ArkUI_GestureDirectionMask directions, double distanceNum);

    /**
     * @brief Creates a pinch gesture.
     *
     * @param fingersNum Minimum number of fingers required to trigger the pinch gesture. The value ranges from 2 to 5.
     *     If the value is out of the range, the default value **2** is used.
     * @param distanceNum Minimum recognition distance, in px. If this parameter is set to a value less than or equal to
     *     0, the default value **5px** is used.
     * @return Returns the pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createPinchGesture)(int32_t fingersNum, double distanceNum);

    /**
     * @brief Creates a rotation gesture.
     *
     * @param fingersNum Minimum number of fingers required to trigger the rotation gesture. The value ranges from 2 to
     *     5. If the value is out of the range, the default value **2** is used.
     * @param angleNum Minimum angle change required to trigger the rotation gesture, in degrees (deg). The default
     *     value is **1**. If this parameter is set to a value less than or equal to 0 or greater than 360, the default
     *     value **1** is used.
     * @return Returns the pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createRotationGesture)(int32_t fingersNum, double angleNum);

    /**
     * @brief Creates a swipe gesture.This API is used to implement a swipe gesture, which can be recognized when the
     * swipe speed (px/s) is higher than that specified by **speedNum**.
     *
     * @param fingersNum Minimum number of fingers required to trigger the swipe gesture. The value ranges from 1 to 10.
     * @param directions Directions in which the swipe gesture can be recognized.
     * @param speedNum Minimum speed required to recognize the swipe gesture, in px/s. If this parameter is set to a
     *     value less than or equal to 0, the default value **100px/s** is used.
     * @return Returns the pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createSwipeGesture)(
        int32_t fingersNum, ArkUI_GestureDirectionMask directions, double speedNum);

    /**
     * @brief Creates a gesture group.
     *
     * @param gestureMode Gesture group mode.
     * @return Returns the pointer to the created gesture group.
     */
    ArkUI_GestureRecognizer* (*createGroupGesture)(ArkUI_GroupGestureMode gestureMode);

    /**
     * @brief Disposes of a gesture to release resources.
     *
     * @param recognizer Pointer to the gesture to be disposed of.
     */
    void (*dispose)(ArkUI_GestureRecognizer* recognizer);

    /**
     * @brief Adds a gesture to a gesture group.
     *
     * @param group Pointer to the target gesture group.
     * @param child Pointer to the target gesture.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs, for example, attempting to
     *     add a gesture to an object that is not a gesture group.
     */
    int32_t (*addChildGesture)(ArkUI_GestureRecognizer* group, ArkUI_GestureRecognizer* child);

    /**
     * @brief Removes a gesture from a gesture group.
     *
     * @param group Pointer to the target gesture group.
     * @param child Pointer to the target gesture.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*removeChildGesture)(ArkUI_GestureRecognizer* group, ArkUI_GestureRecognizer* child);

    /**
     * @brief Registers a callback for gestures.
     *
     * @param recognizer Pointer to a gesture recognizer.
     * @param actionTypeMask Gesture event types. Multiple callbacks can be registered at once, with the callback event
     *     types distinguished in the callbacks. Example: actionTypeMask = GESTURE_EVENT_ACTION_ACCEPT \|
     *     GESTURE_EVENT_ACTION_UPDATE;
     * @param extraParams Context passed in the **targetReceiver** callback.
     * @param targetReceiver Callback to register for processing the gesture event types. **event** indicates the
     *     gesture callback data.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*setGestureEventTarget)(
        ArkUI_GestureRecognizer* recognizer, ArkUI_GestureEventActionTypeMask actionTypeMask, void* extraParams,
        void (*targetReceiver)(ArkUI_GestureEvent* event, void* extraParams));

    /**
     * @brief Adds a gesture to a UI component.
     *
     * @param node Pointer to the ArkUI component node to which you want to add the gesture.
     * @param recognizer Gesture to be added to the UI component.
     * @param mode Mode of the gesture.
     * @param mask Gesture masking mode.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*addGestureToNode)(
        ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer, ArkUI_GesturePriority mode, ArkUI_GestureMask mask);

    /**
     * @brief Removes a gesture from a node.
     *
     * @param node Pointer to the node from which you want to remove the gesture.
     * @param recognizer Gesture to be removed.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*removeGestureFromNode)(ArkUI_NodeHandle node, ArkUI_GestureRecognizer* recognizer);

    /**
     * @brief Sets a gesture interruption callback for a node.
     *
     * @param node Pointer to the ArkUI node for which you want to set a gesture interruption callback.
     * @param interrupter Indicates the gesture interruption callback to set.
     *     <b>info</b> indicates the gesture interruption data. If <b>interrupter</b> returns
     *     <b>GESTURE_INTERRUPT_RESULT_CONTINUE</b>, the gesture recognition process continues. If it returns
     *     <b>GESTURE_INTERRUPT_RESULT_REJECT</b>, the gesture recognition process is paused.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*setGestureInterrupterToNode)(
        ArkUI_NodeHandle node, ArkUI_GestureInterruptResult (*interrupter)(ArkUI_GestureInterruptInfo* info));

    /**
     * @brief Obtains the type of a gesture.
     *
     * @param recognizer Pointer to the gesture.
     * @return Returns the gesture type.
     */
    ArkUI_GestureRecognizerType (*getGestureType)(ArkUI_GestureRecognizer* recognizer);

    /**
     * @brief Sets the callback function for the parallel internal gesture event.
     *
     * @param node Pointer to the ArkUI node for which you want to set the callback of the parallel internal gesture
     *     event.
     * @param userData Custom data.
     * @param parallelInnerGesture Parallel internal gesture event. **event** returns the data of the parallel internal
     *     gesture event. **parallelInnerGesture** returns the pointer to the gesture recognizer that requires parallel
     *     recognition.
     * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*setInnerGestureParallelTo)(
        ArkUI_NodeHandle node, void* userData, ArkUI_GestureRecognizer* (*parallelInnerGesture)(
            ArkUI_ParallelInnerGestureEvent* event));

    /**
     * @brief Creates a tap gesture that is subject to distance restrictions.
     *
     * @param countNum Number of consecutive taps. If the value is less than 1 or is not set, the default value **1** is
     *     used.
     * @param fingersNum Number of fingers required to trigger the tap gesture. The value ranges from 1 to 10. If the
     *     value is less than 1 or is not set, the default value **1** is used.
     * @param distanceThreshold Allowed moving distance of a finger. If the value is less than 0 or is not set, it will
     *     be converted to the default value of infinity.
     * @return Returns the pointer to the created gesture.
     */
    ArkUI_GestureRecognizer* (*createTapGestureWithDistanceThreshold)(
        int32_t countNum, int32_t fingersNum, double distanceThreshold);
} ArkUI_NativeGestureAPI_1;

/**
 * @brief Defines a collection of gesture APIs.
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
     * @brief Sets the callback for gesture interruption events.
     *
     * @param node Pointer to the ArkUI node for which you want to set a gesture interruption callback.
     * @param userData Pointer to user-defined data.
     * @param interrupter Gesture interruption callback to set. <b>info</b> indicates the gesture interruption data.
     *     If <b>interrupter</b> returns <b>GESTURE_INTERRUPT_RESULT_CONTINUE</b>, the gesture recognition process
     *     proceeds
     *     properly. If it returns <b>GESTURE_INTERRUPT_RESULT_REJECT</b>, the gesture recognition process is paused.
     * @return Error code.
     *     <br>Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
     *     <br>Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
     */
    int32_t (*setGestureInterrupterToNode)(ArkUI_NodeHandle node, void* userData,
        ArkUI_GestureInterruptResult (*interrupter)(ArkUI_GestureInterruptInfo* info));
} ArkUI_NativeGestureAPI_2;

/**
 * @brief Defines a collection of gesture APIs, including gesture APIs in the {@link ArkUI_NativeGestureAPI_1} and
 * {@link ArkUI_NativeGestureAPI_2} structs and new gesture APIs.
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
     * @brief Sets the callback function for a parallel gesture event.
     *
     * @param node Pointer to the ArkUI node for which you want to set a parallel gesture event callback.
     * @param userData Pointer to the user-defined data. The caller must ensure the security of the data lifecycle.
     * @param parallelGesture Parallel gesture event. event returns the data of the parallel gesture event. \n
     *     ParallelGesture returns the pointer to the gesture recognizer that needs parallel recognition.
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