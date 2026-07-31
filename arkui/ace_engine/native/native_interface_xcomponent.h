/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
 * @addtogroup OH_NativeXComponent Native XComponent
 * @{
 *
 * @brief Describes the surface and touch event held by the ArkUI XComponent, which can be used for the EGL/OpenGL ES\n
 *        and media data input and displayed on the ArkUI XComponent.
 *
 * @since 8
 * @version 1.0
 */

/**
 * @file native_interface_xcomponent.h
 *
 * @brief Declares the APIs for accessing Native XComponent features.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 8
 * @version 1.0
 */

#ifndef _NATIVE_INTERFACE_XCOMPONENT_H_
#define _NATIVE_INTERFACE_XCOMPONENT_H_

#include <stdbool.h>
#include <stdint.h>
#ifdef __cplusplus
#include <vector>
#endif

#include "arkui/native_interface_accessibility.h"
#include "arkui/native_type.h"
#include "arkui/ui_input_event.h"

#include "native_xcomponent_key_event.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OH_NATIVE_XCOMPONENT_OBJ ("__NATIVE_XCOMPONENT_OBJ__")
#define OH_NATIVE_XCOMPONENT_MAX_TOUCH_POINTS_NUMBER 10

const uint32_t OH_XCOMPONENT_ID_LEN_MAX = 128;
const uint32_t OH_MAX_TOUCH_POINTS_NUMBER = 10;

/**
 * @brief Enumerates the API access states.
 *
 * @since 8
 * @version 1.0
 */
enum {
    /** Successful. */
    OH_NATIVEXCOMPONENT_RESULT_SUCCESS = 0,
    /** Failed. */
    OH_NATIVEXCOMPONENT_RESULT_FAILED = -1,
    /** Invalid parameters. */
    OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER = -2,
};

/**
 * @brief Status code for AI analyzer.
 *
 * @since 18
 */
typedef enum {
    /**
     * AI analyzer execution is finished.
     * @since 18
     */
    ARKUI_XCOMPONENT_AI_ANALYSIS_FINISHED = 0,
    /**
     * AI analyzer is disabled.
     * @since 18
     */
    ARKUI_XCOMPONENT_AI_ANALYSIS_DISABLED = 110000,
    /**
     * AI analyzer is unsupported.
     * @since 18
     */
    ARKUI_XCOMPONENT_AI_ANALYSIS_UNSUPPORTED = 110001,
    /**
     * AI analyzer is ongoing.
     * @since 18
     */
    ARKUI_XCOMPONENT_AI_ANALYSIS_ONGOING = 110002,
    /**
     * AI analyzer is stopped.
     * @since 18
     */
    ARKUI_XCOMPONENT_AI_ANALYSIS_STOPPED = 110003
} ArkUI_XComponent_ImageAnalyzerState;

/**
 * @brief Enumerates the touch event types.
 *
 * @since 8
 * @version 1.0
 */
typedef enum {
    /**
     * The touch event is triggered when a finger is pressed.
     * @since 8
     */
    OH_NATIVEXCOMPONENT_DOWN = 0,
    /**
     * The touch event is triggered when a finger is lifted.
     * @since 8
     */
    OH_NATIVEXCOMPONENT_UP,
    /**
     * The touch event is triggered when a finger is moved on the screen.
     * @since 8
     */
    OH_NATIVEXCOMPONENT_MOVE,
    /**
     * The event is triggered when a touch event is canceled.
     * @since 8
     */
    OH_NATIVEXCOMPONENT_CANCEL,
    /**
     * Invalid touch type.
     * @since 8
     */
    OH_NATIVEXCOMPONENT_UNKNOWN
} OH_NativeXComponent_TouchEventType;

/**
 * @brief Enumerates the touch point tool types.
 *
 * @since 9
 * @version 1.0
 */
typedef enum {
    /**
     * Unknown tool type.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN = 0,
    /**
     * Finger.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_FINGER,
    /**
     * Stylus.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_PEN,
    /**
     * Rubber.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_RUBBER,
    /**
     * Brush.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_BRUSH,
    /**
     * Pencil.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_PENCIL,
    /**
     * Brush.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_AIRBRUSH,
    /**
     * Mouse.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_MOUSE,
    /**
     * Lens.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_LENS
} OH_NativeXComponent_TouchPointToolType;

/**
 * @brief Enumerates the touch event source types.
 *
 * @since 9
 * @version 1.0
 */
typedef enum {
    /**
     * Unknown source type.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN = 0,
    /**
     * Source that generates a mouse multi-click event.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_SOURCE_TYPE_MOUSE,
    /**
     * Source that generates a touchscreen multitouch event.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHSCREEN,
    /**
     * Source that generates a touchpad multitouch event.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHPAD,
    /**
     * Source that generates a joystick multitouch event.
     * @since 9
     */
    OH_NATIVEXCOMPONENT_SOURCE_TYPE_JOYSTICK,
    /**
     * @brief Source that generates a key event.
     *
     * @since 10
     * @version 1.0
     */
    OH_NATIVEXCOMPONENT_SOURCE_TYPE_KEYBOARD
} OH_NativeXComponent_EventSourceType;

/**
 * @brief Enumerates the mouse event actions.
 *
 * @since 9
 * @version 1.0
 */
typedef enum {
    OH_NATIVEXCOMPONENT_MOUSE_NONE = 0,
    OH_NATIVEXCOMPONENT_MOUSE_PRESS,
    OH_NATIVEXCOMPONENT_MOUSE_RELEASE,
    OH_NATIVEXCOMPONENT_MOUSE_MOVE,
    /**
     * Mouse button canceling.<br> Note: Mouse button canceling is typically triggered in the following scenarios:<br>1.
     *  Component focus loss: A currently focused **XComponent** loses focus due to a system event (such as pop-up
     * interruption or app switching).<br> 2. Event interruption: During a mouse operation, a higher-priority event
     * occurs (such as a system-level gesture or forced event stream recycling), causing the current mouse operation to
     * be forcibly terminated.<br>3. Abnormal state exit: In scenarios such as component destruction or abnormal
     * rendering environment, unfinished mouse events are marked as canceled.
     * @since 18
     */
    OH_NATIVEXCOMPONENT_MOUSE_CANCEL
} OH_NativeXComponent_MouseEventAction;

/**
 * @brief Enumerates the mouse event buttons.
 *
 * @since 9
 * @version 1.0
 */
typedef enum {
    OH_NATIVEXCOMPONENT_NONE_BUTTON = 0,
    OH_NATIVEXCOMPONENT_LEFT_BUTTON = 0x01,
    OH_NATIVEXCOMPONENT_RIGHT_BUTTON = 0x02,
    OH_NATIVEXCOMPONENT_MIDDLE_BUTTON = 0x04,
    OH_NATIVEXCOMPONENT_BACK_BUTTON = 0x08,
    OH_NATIVEXCOMPONENT_FORWARD_BUTTON = 0x10
} OH_NativeXComponent_MouseEventButton;

/**
 * @brief Enumerates the source tool types of touch events.
 *
 * @since 10
 * @version 1.0
 */
typedef enum {
    OH_NATIVEXCOMPONENT_SOURCETOOL_UNKNOWN = 0,
    OH_NATIVEXCOMPONENT_SOURCETOOL_FINGER = 1,
    OH_NATIVEXCOMPONENT_SOURCETOOL_PEN = 2,
    OH_NATIVEXCOMPONENT_SOURCETOOL_RUBBER = 3,
    OH_NATIVEXCOMPONENT_SOURCETOOL_BRUSH = 4,
    OH_NATIVEXCOMPONENT_SOURCETOOL_PENCIL = 5,
    OH_NATIVEXCOMPONENT_SOURCETOOL_AIRBRUSH = 6,
    OH_NATIVEXCOMPONENT_SOURCETOOL_MOUSE = 7,
    OH_NATIVEXCOMPONENT_SOURCETOOL_LENS = 8,
    OH_NATIVEXCOMPONENT_SOURCETOOL_TOUCHPAD = 9
} OH_NativeXComponent_TouchEvent_SourceTool;

/**
 * @brief Represents a historical touch point.
 *
 * @since 10
 * @version 1.0
 */
typedef struct {
    /**
     * Unique identifier of the finger.
     * @since 10
     */
    int32_t id;
    /**
     * X-coordinate of the touch point relative to the upper left corner of the application window where the XComponent
     * is located.
     * @since 10
     */
    float screenX;
    /**
     * Y-coordinate of the touch point relative to the upper left corner of the application window where the XComponent
     * is located.
     * @since 10
     */
    float screenY;
    /**
     * X-coordinate of the touch point relative to the left edge of the XComponent.
     * @since 10
     */
    float x;
    /**
     * Y-coordinate of the touch point relative to the upper edge of the XComponent.
     * @since 10
     */
    float y;
    /**
     * Touch type of the touch event.
     * @since 10
     */
    OH_NativeXComponent_TouchEventType type;
    /**
     * Contact area between the finger pad and the screen.
     * @since 10
     */
    double size;
    /**
     * Pressure of the touch event.
     * @since 10
     */
    float force;
    /**
     * Timestamp of the touch event. It is interval between the time when the event is triggered and the time when the
     * system starts, in nanoseconds.
     * @since 10
     */
    int64_t timeStamp;
    /**
     * Angle between the projection on the x-y plane and the z-axis of the touch event.
     * @since 10
     */
    float titlX;
    /**
     * Angle between the projection on the y-z plane and the z-axis of the current touch event.
     * @since 10
     */
    float titlY;
    /**
     * Source tool of the touch event.
     * @since 10
     */
    OH_NativeXComponent_TouchEvent_SourceTool sourceTool;
} OH_NativeXComponent_HistoricalPoint;

/**
 * @brief Describes the touch point of the touch event.
 *
 * @since 8
 * @version 1.0
 */
typedef struct {
    /**
     * Unique identifier of the finger.
     * @since 8
     */
    int32_t id;
    /**
     * X-coordinate of the touch point relative to the upper left corner of the application window where the XComponent
     * is located.
     * @since 8
     */
    float screenX;
    /**
     * Y-coordinate of the touch point relative to the upper left corner of the application window where the XComponent
     * is located.
     * @since 8
     */
    float screenY;
    /**
     * X-coordinate of the touch point relative to the left edge of the XComponent.
     * @since 8
     */
    float x;
    /**
     * Y-coordinate of the touch point relative to the upper edge of the XComponent.
     * @since 8
     */
    float y;
    /**
     * Touch type of the touch event.
     * @since 8
     */
    OH_NativeXComponent_TouchEventType type;
    /**
     * Contact area between the finger pad and the screen.
     * @since 8
     */
    double size;
    /**
     * Pressure of the touch event.
     * @since 8
     */
    float force;
    /**
     * Timestamp of the touch event. It is interval between the time when the event is triggered and the time when the
     * system starts, in nanoseconds.
     * @since 8
     */
    int64_t timeStamp;
    /**
     * Whether the current point is pressed. **true** when the point is pressed, **false** when it is released.
     * @since 8
     */
    bool isPressed;
} OH_NativeXComponent_TouchPoint;

/**
 * @brief Defines the touch event.
 *
 * @since 8
 * @version 1.0
 */
typedef struct {
    /**
     * Unique identifier of the finger.
     * @since 8
     */
    int32_t id;
    /**
     * X-coordinate of the touch point relative to the upper left corner of the application window where the XComponent
     * is located.
     * @since 8
     */
    float screenX;
    /**
     * Y-coordinate of the touch point relative to the upper left corner of the application window where the XComponent
     * is located.
     * @since 8
     */
    float screenY;
    /**
     * X-coordinate of the touch point relative to the left edge of the XComponent.
     * @since 8
     */
    float x;
    /**
     * Y-coordinate of the touch point relative to the upper edge of the XComponent.
     * @since 8
     */
    float y;
    /**
     * Touch type of the touch event.
     * @since 8
     */
    OH_NativeXComponent_TouchEventType type;
    /**
     * Contact area between the finger pad and the screen.
     * @since 8
     */
    double size;
    /**
     * Pressure of the touch event.
     * @since 8
     */
    float force;
    /**
     * ID of the device where the current touch event is triggered.
     * @since 8
     */
    int64_t deviceId;
    /**
     * Timestamp of the touch event. It is interval between the time when the event is triggered and the time when the
     * system starts, in nanoseconds.
     * @since 8
     */
    int64_t timeStamp;
    /**
     * Array of the current touch points.
     * @since 8
     */
    OH_NativeXComponent_TouchPoint touchPoints[OH_NATIVE_XCOMPONENT_MAX_TOUCH_POINTS_NUMBER];
    /**
     * Number of current touch points. The value **1** indicates single-finger touch, while a value greater than **1**
     * indicates multi-finger touch.
     * @since 8
     */
    uint32_t numPoints;
} OH_NativeXComponent_TouchEvent;

/**
 * @brief Defines a mouse event.
 *
 * @since 9
 * @version 1.0
 */
typedef struct {
    /**
     * X coordinate of the clicked point relative to the upper left corner of the component. Unit: vp.
     * @since 9
     */
    float x;
    /**
     * Y coordinate of the clicked point relative to the upper left corner of the component. Unit: vp.
     * @since 9
     */
    float y;
    /**
     * X coordinate of the click point relative to the upper left corner of the application screen where the XComponent
     * is located. Unit: vp.
     * @since 9
     */
    float screenX;
    /**
     * Y coordinate of the click point relative to the upper left corner of the application screen where the XComponent
     * is located. Unit: vp.
     * @since 9
     */
    float screenY;
    /**
     * Timestamp of the mouse event. It is interval between the time when the event is triggered and the time when the
     * system starts, in nanoseconds.
     * @since 9
     */
    int64_t timestamp;
    /**
     * Action of the mouse event.
     * @since 9
     */
    OH_NativeXComponent_MouseEventAction action;
    /**
     * Button of the mouse event.
     * @since 9
     */
    OH_NativeXComponent_MouseEventButton button;
} OH_NativeXComponent_MouseEvent;

/**
 * @brief Provides an encapsulated **OH_NativeXComponent** instance.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_NativeXComponent OH_NativeXComponent;

/**
 * @brief Registers callbacks for the surface lifecycle and touch event.
 *
 * @since 8
 * @version 1.0
 */
typedef struct OH_NativeXComponent_Callback {
    /**
     * Invoked when a surface is created.
     * @since 8
     */
    void (*OnSurfaceCreated)(OH_NativeXComponent* component, void* window);
    /**
     * Invoked when the surface changes.
     * @since 8
     */
    void (*OnSurfaceChanged)(OH_NativeXComponent* component, void* window);
    /**
     * Invoked when the surface is destroyed.
     * @since 8
     */
    void (*OnSurfaceDestroyed)(OH_NativeXComponent* component, void* window);
    /**
     * Invoked when a touch event is triggered.
     * @since 8
     */
    void (*DispatchTouchEvent)(OH_NativeXComponent* component, void* window);
} OH_NativeXComponent_Callback;

/**
 * @brief Registers callbacks for the mouse event.
 *
 * @since 9
 * @version 1.0
 */
typedef struct OH_NativeXComponent_MouseEvent_Callback {
    /**
     * Invoked when a mouse event is triggered.
     * @since 9
     */
    void (*DispatchMouseEvent)(OH_NativeXComponent* component, void* window);
    /**
     * Invoked when a hover event is triggered.
     * @since 9
     */
    void (*DispatchHoverEvent)(OH_NativeXComponent* component, bool isHover);
} OH_NativeXComponent_MouseEvent_Callback;

struct OH_NativeXComponent_KeyEvent;
/**
 * @brief Provides an encapsulated **OH_NativeXComponent_KeyEvent** instance.
 *
 * @since 10
 * @version 1.0
 */
typedef struct OH_NativeXComponent_KeyEvent OH_NativeXComponent_KeyEvent;

/**
 * @brief Defines the expected frame rate range.
 *
 * @since 11
 * @version 1.0
 */
typedef struct {
    /**
     * Minimum value of the expected frame rate range. The unit is frame/second.
     * @since 11
     */
    int32_t min;
    /**
     * Maximum value of the expected frame rate range. The unit is frame/second.
     * @since 11
     */
    int32_t max;
    /**
     * Expected frame rate. The unit is frame/second.
     * @since 11
     */
    int32_t expected;
} OH_NativeXComponent_ExpectedRateRange;

/**
 * @brief Obtains the ID of ArkUI XComponent.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param id Pointer to the character buffer for storing the ID of the {@link OH_NativeXComponent} instance. Note that
 *     null terminators will be attached to the character buffer, so the size of the character buffer should be at
 *     least one unit greater than the length of the real ID. The recommended size is \[
 *     {@link OH_XCOMPONENT_ID_LEN_MAX} + 1].
 * @param size Pointer to the length of the ID, used to receive the length information of the ID.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetXComponentId(OH_NativeXComponent* component, char* id, uint64_t* size);

/**
 * @brief Obtains the size of the surface held by the ArkUI XComponent.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param window Handle to the **NativeWindow** instance.
 * @param width Pointer to the width of the current surface. Unit: vp.
 * @param height Pointer to the height of the current surface. Unit: vp.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetXComponentSize(
    OH_NativeXComponent* component, const void* window, uint64_t* width, uint64_t* height);

/**
 * @brief Obtains the offset of the surface held by the XComponent relative to the upper left corner of its parent
 * component.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param window Handle to the **NativeWindow** instance.
 * @param x Pointer to the x-coordinate of the current surface relative to the upper left corner of the **XComponent**'
 *     s parent component. Unit: vp.
 * @param y Pointer to the y-coordinate of the current surface relative to the upper left corner of the **XComponent**'
 *     s parent component. Unit: vp.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetXComponentOffset(
    OH_NativeXComponent* component, const void* window, double* x, double* y);

/**
 * @brief Obtains the touch event scheduled by the ArkUI XComponent.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param window Handle to the **NativeWindow** instance.
 * @param touchEvent Pointer to the current touch event.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchEvent(
    OH_NativeXComponent* component, const void* window, OH_NativeXComponent_TouchEvent* touchEvent);

/**
 * @brief Obtains the ArkUI XComponent touch point tool type.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param pointIndex Pointer to the index of the touch point.
 * @param toolType Pointer to the tool type.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointToolType(
    OH_NativeXComponent* component, uint32_t pointIndex, OH_NativeXComponent_TouchPointToolType* toolType);

/**
 * @brief Obtains the angle between the Y-Z plane of the ArkUI XComponent touch point and the x-axis.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param pointIndex Pointer to the index of the touch point.
 * @param tiltX Pointer to the angle between the Y-Z plane of the touch point and the x-axis.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointTiltX(OH_NativeXComponent* component, uint32_t pointIndex, float* tiltX);

/**
 * @brief Obtains the angle between the X-Z plane of the ArkUI XComponent touch point and the y-axis.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param pointIndex Pointer to the index of the touch point.
 * @param tiltY Pointer to the angle between the X-Z plane of the touch point and the y-axis.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointTiltY(OH_NativeXComponent* component, uint32_t pointIndex, float* tiltY);

/**
 * @brief Obtains the x-coordinate of the touch point relative to the upper left corner of the application window where
 * the ArkUI XComponent is located.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param pointIndex Pointer to the index of the touch point.
 * @param windowX Pointer to the x-coordinate of the touch point relative to the upper left corner of the application
 *     window.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if the component, windowX,
 *             or native XComponent is a null pointer.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointWindowX(OH_NativeXComponent* component, uint32_t pointIndex, float* windowX);

/**
 * @brief Obtains the y-coordinate of the touch point relative to the upper left corner of the application window where
 * the ArkUI XComponent is located.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param pointIndex Pointer to the index of the touch point.
 * @param windowY Pointer to the y-coordinate of the touch point relative to the upper left corner of the application
 *     window.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if the component, windowY,
 *             or native XComponent is a null pointer.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointWindowY(OH_NativeXComponent* component, uint32_t pointIndex, float* windowY);

/**
 * @brief Obtains the x-coordinate of the touch point relative to the upper left corner of the screen where the ArkUI
 * XComponent is located.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param pointIndex Pointer to the index of the touch point.
 * @param displayX Pointer to the x-coordinate of the touch point relative to the upper left corner of the screen.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if the component, displayX,
 *             or native XComponent is a null pointer.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointDisplayX(OH_NativeXComponent* component, uint32_t pointIndex, float* displayX);

/**
 * @brief Obtains the y-coordinate of the touch point relative to the upper left corner of the screen where the ArkUI
 * XComponent is located.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param pointIndex Pointer to the index of the touch point.
 * @param displayY Pointer to the y-coordinate of the touch point relative to the upper left corner of the screen.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if the component, displayY,
 *             or native XComponent is a null pointer.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchPointDisplayY(OH_NativeXComponent* component, uint32_t pointIndex, float* displayY);

/**
 * @brief Obtains the historical touch point data for the touch event of an **OH_NativeXComponent** instance. Some
 * input devices report touch points at very high frequencies (up to 1 ms intervals). However, since UI updates
 * typically do not require such high-frequency updates, the system consolidates touch events and reports them once per
 * frame. All touch points collected during the current frame are preserved as historical touch points for applications
 * that need direct access to this raw data.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param window Handle to the **NativeWindow** instance.
 * @param size Length of the historical touch point array.
 * @param historicalPoints Pointer to the historical touch point array.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetHistoricalPoints(OH_NativeXComponent* component, const void* window,
    int32_t* size, OH_NativeXComponent_HistoricalPoint** historicalPoints);

/**
 * @brief Obtains the mouse event scheduled by the ArkUI XComponent.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param window Handle to the **NativeWindow** instance.
 * @param mouseEvent Pointer to the current mouse event.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetMouseEvent(
    OH_NativeXComponent* component, const void* window, OH_NativeXComponent_MouseEvent* mouseEvent);

/**
 * @brief Registers a callback for this {@link OH_NativeXComponent} instance.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param callback Pointer to the surface lifecycle and touch event callback.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 8
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterCallback(OH_NativeXComponent* component, OH_NativeXComponent_Callback* callback);

/**
 * @brief Registers a mouse event callback for this {@link OH_NativeXComponent} instance.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param callback Pointer to the mouse event callback.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 9
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterMouseEventCallback(
    OH_NativeXComponent* component, OH_NativeXComponent_MouseEvent_Callback* callback);

/**
 * @brief Provides an encapsulated instance of extended mouse event information.
 *
 * @since 20
 * @version 1.0
 */
typedef struct OH_NativeXComponent_ExtraMouseEventInfo OH_NativeXComponent_ExtraMouseEventInfo;

/**
 * @brief Obtains extended mouse event information from this {@link OH_NativeXComponent} instance.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param extraMouseEventInfo Address of a pointer to the {@link OH_NativeXComponent_ExtraMouseEventInfo} type.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 20
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetExtraMouseEventInfo(OH_NativeXComponent* component, OH_NativeXComponent_ExtraMouseEventInfo** extraMouseEventInfo);

/**
 * @brief Obtains the state of modifier keys from an {@link OH_NativeXComponent_ExtraMouseEventInfo} instance.
 *
 * @param extraMouseEventInfo Pointer to the extended mouse event information instance.
 * @param keys Address of a 64-bit unsigned integer to receive the modifier key press state information.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 20
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetMouseEventModifierKeyStates(
    OH_NativeXComponent_ExtraMouseEventInfo* extraMouseEventInfo, uint64_t* keys);

/**
 * @brief Registers a focus event callback for this {@link OH_NativeXComponent} instance.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param callback Indicates the pointer to a focus event callback.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterFocusEventCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window));

/**
 * @brief Registers a key event callback for this {@link OH_NativeXComponent} instance.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param callback Indicates the pointer to a key event callback.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterKeyEventCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window));

/**
 * @brief Registers a key event callback with a return value for this {@link OH_NativeXComponent} instance.
 * The callback must return a result (true or false). If the callback returns true, the event will not be
 *  further propagated.
 * If it returns false, the event will continue to be processed according to the normal event handling flow.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param callback Indicates the pointer to a key event callback. The callback must return a result.
 *     When the return value is true, the event will not be further propagated.
 *     When the return value is false, the event will continue to be processed according to
 *     the normal event handling flow.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_FAILED} if any other error occurs</li>
 *         </ul>
 * @since 14
 */
int32_t OH_NativeXComponent_RegisterKeyEventCallbackWithResult(
    OH_NativeXComponent* component, bool (*callback)(OH_NativeXComponent* component, void* window));

/**
 * @brief Registers a blur event callback for this {@link OH_NativeXComponent} instance.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param callback Indicates the pointer to a blur event callback.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterBlurEventCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window));

/**
 * @brief Obtains the key event scheduled by the ArkUI XComponent.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param keyEvent Pointer to the current key event.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEvent(OH_NativeXComponent* component, OH_NativeXComponent_KeyEvent** keyEvent);

/**
 * @brief Obtains the action of the specified key event.
 *
 * @param keyEvent Pointer to an {@link OH_NativeXComponent_KeyEvent} instance.
 * @param action Pointer to the key event action.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventAction(
    OH_NativeXComponent_KeyEvent* keyEvent, OH_NativeXComponent_KeyAction* action);

/**
 * @brief Obtains the key code of the specified key event.
 *
 * @param keyEvent Pointer to an {@link OH_NativeXComponent_KeyEvent} instance.
 * @param code Pointer to the key code of the key event.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventCode(OH_NativeXComponent_KeyEvent* keyEvent, OH_NativeXComponent_KeyCode* code);

/**
 * @brief Obtains the source type of the specified key event.
 *
 * @param keyEvent Pointer to an {@link OH_NativeXComponent_KeyEvent} instance.
 * @param sourceType Pointer to the source type of the key event.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventSourceType(
    OH_NativeXComponent_KeyEvent* keyEvent, OH_NativeXComponent_EventSourceType* sourceType);

/**
 * @brief Obtains the device ID of the specified key event.
 *
 * @param keyEvent Pointer to an {@link OH_NativeXComponent_KeyEvent} instance.
 * @param deviceId Pointer to the device ID of the key event.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventDeviceId(OH_NativeXComponent_KeyEvent* keyEvent, int64_t* deviceId);

/**
 * @brief Obtains the timestamp of the specified key event.
 *
 * @param keyEvent Pointer to an {@link OH_NativeXComponent_KeyEvent} instance.
 * @param timestamp Pointer to the timestamp of the key event.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 10
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventTimestamp(OH_NativeXComponent_KeyEvent* keyEvent, int64_t* timestamp);

/**
 * @brief Obtains the state of modifier keys from a key event.
 *
 * @param keyEvent Pointer to the key event.
 * @param keys Address of a 64-bit unsigned integer to receive the modifier key press state information.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 20
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventModifierKeyStates(OH_NativeXComponent_KeyEvent* keyEvent, uint64_t* keys);

/**
 * @brief Obtains the state of the NumLock key from a key event.
 *
 * @param keyEvent Pointer to the key event.
 * @param isNumLockOn Pointer to a boolean variable to receive the state of the NumLock key. **true**: NumLock is
 *     enabled. **false**: NumLock is disabled.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 20
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventNumLockState(OH_NativeXComponent_KeyEvent* keyEvent, bool* isNumLockOn);

/**
 * @brief Obtains the state of the CapsLock key from a key event.
 *
 * @param keyEvent Pointer to the key event.
 * @param isCapsLockOn Pointer to a boolean variable to receive the state of the CapsLock key. **true**: CapsLock is
 *     enabled. **false**: CapsLock is disabled.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 20
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventCapsLockState(OH_NativeXComponent_KeyEvent* keyEvent, bool* isCapsLockOn);

/**
 * @brief Obtains the state of the ScrollLock key from a key event.
 *
 * @param keyEvent Pointer to the key event.
 * @param isScrollLockOn Pointer to a boolean variable to receive the state of the ScrollLock key. **true**: ScrollLock
 *     is enabled. **false**: ScrollLock is disabled.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 20
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetKeyEventScrollLockState(OH_NativeXComponent_KeyEvent* keyEvent, bool* isScrollLockOn);

/**
 * @brief Sets the expected frame rate range.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param range Pointer to the expected frame rate information object of the
 *     {@link OH_NativeXComponent_ExpectedRateRange} type.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 11
 * @version 1.0
 */
int32_t OH_NativeXComponent_SetExpectedFrameRateRange(
    OH_NativeXComponent* component, OH_NativeXComponent_ExpectedRateRange* range);

/**
 * @brief Registers the display update callback for this {@link OH_NativeXComponent} instance and enables the callback
 * for each frame.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param callback Indicates the pointer to a onFrame callback.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 11
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterOnFrameCallback(OH_NativeXComponent* component,
    void (*callback)(OH_NativeXComponent* component, uint64_t timestamp, uint64_t targetTimestamp));

/**
 * @brief Deregisters the display update callback for this {@link OH_NativeXComponent} instance and disables the
 * callback for each frame.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 11
 * @version 1.0
 */
int32_t OH_NativeXComponent_UnregisterOnFrameCallback(OH_NativeXComponent* component);

/**
 * @brief Attaches the UI component created through the native API of ArkUI to this **OH_NativeXComponent** instance.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param root Pointer to the component instance created through the native API.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 12
 * @deprecated since 20
 * @useinstead OH_ArkUI_NodeContent_AddNode
 */
int32_t OH_NativeXComponent_AttachNativeRootNode(OH_NativeXComponent* component, ArkUI_NodeHandle root);

/**
 * @brief Detaches the native component of ArkUI from this **OH_NativeXComponent** instance.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param root Pointer to the component instance created through the native API.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 12
 * @deprecated since 20
 * @useinstead OH_ArkUI_NodeContent_RemoveNode
 */
int32_t OH_NativeXComponent_DetachNativeRootNode(OH_NativeXComponent* component, ArkUI_NodeHandle root);

/**
 * @brief Registers a UI input event callback for this {@link OH_NativeXComponent} instance and enables this callback
 * to be invoked when a UI input event is received. Currently, only axis events are supported.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param callback Indicates the pointer to the UI input event callback.
 * @param type Type of the current UI input event.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_NativeXComponent_RegisterUIInputEventCallback(
    OH_NativeXComponent* component,
    void (*callback)(OH_NativeXComponent* component, ArkUI_UIInputEvent* event,
                     ArkUI_UIInputEvent_Type type),
    ArkUI_UIInputEvent_Type type);

/**
 * @brief Sets whether the soft keyboard is required for this {@link OH_NativeXComponent} instance.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param needSoftKeyboard Whether the soft keyboard is required for the current {@link OH_NativeXComponent} instance. *
 *     *true** if the soft keyboard is required, **false** otherwise. The default value is **false**.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_SetNeedSoftKeyboard(OH_NativeXComponent* component, bool needSoftKeyboard);

/**
 * @brief Registers a surface display callback for this {@link OH_NativeXComponent} instance. This callback is invoked
 * after the application is switched to the foreground.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param callback Indicates the pointer to a surface show event callback.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterSurfaceShowCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window));

/**
 * @brief Registers a surface hiding callback for this {@link OH_NativeXComponent} instance. This callback is invoked
 * after the application is switched to the background.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param callback Indicates the pointer to a surface hide event callback.
 * @return Result code.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_RegisterSurfaceHideCallback(
    OH_NativeXComponent* component, void (*callback)(OH_NativeXComponent* component, void* window));

/**
 * @brief Registers a custom event intercept callback for this {@link OH_NativeXComponent} instance and enables this
 * callback to be invoked during hit testing. UI input–related operations are not supported on event objects received
 * through this callback. For full functionality, use the {@link NODE_ON_TOUCH_INTERCEPT} event on native nodes instead.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param callback Indicates the pointer to the custom event intercept callback.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_NativeXComponent_RegisterOnTouchInterceptCallback(
    OH_NativeXComponent* component, HitTestMode (*callback)(OH_NativeXComponent* component, ArkUI_UIInputEvent* event));

/**
 * @brief Obtains the touch event source type of an ArkUI XComponent instance.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param pointId ID of the touch point. The touch event source type can be correctly returned only when the ID passed
 *     in is the ID of the touch point that triggers the touch event. Otherwise, **
 *     OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER** is returned.
 * @param sourceType Pointer to the touch event source type.
 * @return Returns {@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_FAILED} if any other error occurs.</li>
 *         </ul>
 * @since 12
 * @version 1.0
 */
int32_t OH_NativeXComponent_GetTouchEventSourceType(
    OH_NativeXComponent* component, int32_t pointId, OH_NativeXComponent_EventSourceType* sourceType);

/**
 * @brief Obtains a pointer of the {@link OH_NativeXComponent} type based on the specified component instance created
 * by the native API.
 *
 * @param node Pointer to the component instance created through the native API.
 * @return Pointer to an {@link OH_NativeXComponent} instance.
 * @since 12
 * @version 1.0
 */
OH_NativeXComponent* OH_NativeXComponent_GetNativeXComponent(ArkUI_NodeHandle node);

/**
 * @brief Obtains the accessibility provider handle for an ArkUI XComponent.
 *
 * @param component Pointer to an {@link OH_NativeXComponent} instance.
 * @param handle Pointer to an {@link ArkUI_AccessibilityProvider} instance.
 * @return Returns {@link OH_NATIVEXCOMPONENT_RESULT_SUCCESS} if the operation is successful.
 *         <ul>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER} if a parameter error occurs.</li>
 *         <li>{@link OH_NATIVEXCOMPONENT_RESULT_FAILED} if any other error occurs.</li>
 *         </ul>
 * @since 13
 */
int32_t OH_NativeXComponent_GetNativeAccessibilityProvider(
    OH_NativeXComponent* component, ArkUI_AccessibilityProvider** handle);

/**
 * @brief Starts AI image analysis for this XComponent instance.
 * Before calling this API, make sure the AI image analyzer is enabled.
 *
 * @param node XComponent instance.
 * @param userData Pointer to the data that the developer needs to retrieve when the callback function is executed.
 * @param callback Callback function triggered when the image AI analysis status changes.
 *     statusCode: One of the parameters of the callback function, indicating the current image analysis status.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 18
 */
int32_t OH_ArkUI_XComponent_StartImageAnalyzer(
    ArkUI_NodeHandle node, void* userData,
    void (*callback)(ArkUI_NodeHandle node, ArkUI_XComponent_ImageAnalyzerState statusCode, void* userData));

/**
 * @brief Stops AI image analysis for this XComponent instance.
 *
 * @param node XComponent instance.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 18
 */
int32_t OH_ArkUI_XComponent_StopImageAnalyzer(ArkUI_NodeHandle node);

/**
 * @brief Provides an encapsulated **OH_ArkUI_SurfaceHolder** instance.
 *
 * @since 19
 */
typedef struct OH_ArkUI_SurfaceHolder OH_ArkUI_SurfaceHolder;

/**
 * @brief Creates an {@link OH_ArkUI_SurfaceHolder} object for an **XComponent**.
 *
 * @param node Pointer to the XComponent instance created through the native API.
 * @return Pointer to the created {@link OH_ArkUI_SurfaceHolder} object.
 * @since 19
 */
OH_ArkUI_SurfaceHolder* OH_ArkUI_SurfaceHolder_Create(ArkUI_NodeHandle node);

/**
 * @brief Disposes of an {@link OH_ArkUI_SurfaceHolder} object.
 *
 * @param surfaceHolder Indicates the pointer to <b>OH_ArkUI_SurfaceHolder</b> object needed to dispose.
 * @since 19
 */
void OH_ArkUI_SurfaceHolder_Dispose(OH_ArkUI_SurfaceHolder* surfaceHolder);

/**
 * @brief Stores custom data in an {@link OH_ArkUI_SurfaceHolder} instance.
 *
 * @param surfaceHolder Pointer to the target {@link OH_ArkUI_SurfaceHolder} instance.
 * @param userData Pointer to the custom data to be stored.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 19
 */
int32_t OH_ArkUI_SurfaceHolder_SetUserData(OH_ArkUI_SurfaceHolder* surfaceHolder, void* userData);

/**
 * @brief Obtains the custom data stored in an {@link OH_ArkUI_SurfaceHolder} instance.
 *
 * @param surfaceHolder Pointer to the target {@link OH_ArkUI_SurfaceHolder} instance.
 * @return Custom data.
 * @since 19
 */
void* OH_ArkUI_SurfaceHolder_GetUserData(OH_ArkUI_SurfaceHolder* surfaceHolder);

/**
 * @brief Defines surface lifecycle callbacks.
 *
 * @since 19
 */
typedef struct OH_ArkUI_SurfaceCallback OH_ArkUI_SurfaceCallback;

/**
 * @brief Creates an {@link OH_ArkUI_SurfaceCallback} object.
 *
 * @return Pointer to the created {@link OH_ArkUI_SurfaceCallback} object.
 * @since 19
 */
OH_ArkUI_SurfaceCallback* OH_ArkUI_SurfaceCallback_Create();

/**
 * @brief Disposes of an {@link OH_ArkUI_SurfaceCallback} object.
 *
 * @param callback Pointer to the target {@link OH_ArkUI_SurfaceCallback} instance.
 * @since 19
 */
void OH_ArkUI_SurfaceCallback_Dispose(OH_ArkUI_SurfaceCallback* callback);

/**
 * @brief Sets the creation callback event in the surface lifecycle callbacks.
 *
 * @param callback Pointer to the surface lifecycle callback.
 * @param onSurfaceCreated Indicates the surface created callback event
 *     which will called when the surface is created.
 * @since 19
 */
void OH_ArkUI_SurfaceCallback_SetSurfaceCreatedEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceCreated)(OH_ArkUI_SurfaceHolder* surfaceHolder));

/**
 * @brief Sets the size change callback event in the surface lifecycle callbacks.
 *
 * @param callback Pointer to the surface lifecycle callback.
 * @param onSurfaceChanged Indicates the surface changed callback event
 *     which will called when the surface is changed.
 * @since 19
 */
void OH_ArkUI_SurfaceCallback_SetSurfaceChangedEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceChanged)(OH_ArkUI_SurfaceHolder* surfaceHolder, uint64_t width, uint64_t height));

/**
 * @brief Sets the destruction callback event in the surface lifecycle callbacks.
 *
 * @param callback Pointer to the surface lifecycle callback.
 * @param onSurfaceDestroyed Indicates the surface destroyed callback event
 *     which will called when the surface is destroyed.
 * @since 19
 */
void OH_ArkUI_SurfaceCallback_SetSurfaceDestroyedEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceDestroyed)(OH_ArkUI_SurfaceHolder* surfaceHolder));

/**
 * @brief Adds a surface lifecycle callback to an {@link OH_ArkUI_SurfaceHolder} instance.
 *
 * @param surfaceHolder Pointer to the target {@link OH_ArkUI_SurfaceHolder} instance.
 * @param callback Pointer to the new callback.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 19
 */
int32_t OH_ArkUI_SurfaceHolder_AddSurfaceCallback(
    OH_ArkUI_SurfaceHolder* surfaceHolder,
    OH_ArkUI_SurfaceCallback* callback);

/**
 * @brief Removes a previously added surface lifecycle callback from an {@link OH_ArkUI_SurfaceHolder} instance.
 *
 * @param surfaceHolder Pointer to the target {@link OH_ArkUI_SurfaceHolder} instance.
 * @param callback Pointer to the callback to be removed.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 19
 */
int32_t OH_ArkUI_SurfaceHolder_RemoveSurfaceCallback(
    OH_ArkUI_SurfaceHolder* surfaceHolder,
    OH_ArkUI_SurfaceCallback* callback);

/**
 * @brief Provides an encapsulated **NativeWindow** instance.
 *
 * @since 19
 */
typedef struct NativeWindow OHNativeWindow;

/**
 * @brief Obtains the **NativeWindow** instance associated with an {@link OH_ArkUI_SurfaceHolder} instance.
 *
 * @param surfaceHolder Pointer to the target {@link OH_ArkUI_SurfaceHolder} instance.
 * @return **NativeWindow** instance associated with the {@link OH_ArkUI_SurfaceHolder} instance.
 * @since 19
 */
OHNativeWindow* OH_ArkUI_XComponent_GetNativeWindow(OH_ArkUI_SurfaceHolder* surfaceHolder);

/**
 * @brief Sets whether the **XComponent** component needs to automatically initialize the surface.
 *
 * @param node Pointer to the **XComponent** component instance.
 * @param autoInitialize Whether the **XComponent** component needs to automatically initialize the surface. If **
 *     autoInitialize** is **true**, the **OnSurfaceCreated** callback will be triggered when the component is attached
 *     to the tree, and the **OnSurfaceDestroyed** callback will be triggered when the component is detached from the
 *     tree. If the value is **false**, the component does not need to automatically initialize the surface.
 *     <br>The default value of **autoInitialize** is **true**.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 19
 */
int32_t OH_ArkUI_XComponent_SetAutoInitialize(ArkUI_NodeHandle node, bool autoInitialize);

/**
 * @brief Initializes the surface held by the **XComponent** component.
 *
 * @param node Pointer to the **XComponent** component instance.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_XCOMPONENT_STATE_INVALID} if the surface held by the
 *             **XComponent** component has been initialized.</li>
 *         </ul>
 * @since 19
 */
int32_t OH_ArkUI_XComponent_Initialize(ArkUI_NodeHandle node);

/**
 * @brief Destroys the surface held by the **XComponent** component.
 *
 * @param node Pointer to the **XComponent** component instance.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_XCOMPONENT_STATE_INVALID} if the surface held by the
 *              **XComponent** component has been destroyed.</li>
 *         </ul>
 * @since 19
 */
int32_t OH_ArkUI_XComponent_Finalize(ArkUI_NodeHandle node);

/**
 * @brief Checks whether the surface held by the **XComponent** component is initialized.
 *
 * @param node Pointer to the **XComponent** component instance.
 * @param isInitialized Whether the surface held by the **XComponent** component is initialized. **true**: The surface
 *     is initialized. **false**: The surface is not initialized.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 19
 */
int32_t OH_ArkUI_XComponent_IsInitialized(ArkUI_NodeHandle node, bool* isInitialized);

/**
 * @brief Sets the expected frame rate range for the XComponent.
 *
 * @param node XComponent instance.
 * @param range Expected frame rate information object of the {@link OH_NativeXComponent_ExpectedRateRange} type.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 20
 * @version 1.0
 */
int32_t OH_ArkUI_XComponent_SetExpectedFrameRateRange(
    ArkUI_NodeHandle node, OH_NativeXComponent_ExpectedRateRange range);

/**
 * @brief Registers a frame callback function for the XComponent.
 *
 * @param node XComponent instance.
 * @param callback Indicates the pointer to an onFrame callback.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 20
 * @version 1.0
 */
int32_t OH_ArkUI_XComponent_RegisterOnFrameCallback(ArkUI_NodeHandle node,
    void (*callback)(ArkUI_NodeHandle node, uint64_t timestamp, uint64_t targetTimestamp));

/**
 * @brief Unregisters the frame callback function for the XComponent.
 *
 * @param node XComponent instance.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 20
 * @version 1.0
 */
int32_t OH_ArkUI_XComponent_UnregisterOnFrameCallback(ArkUI_NodeHandle node);

/**
 * @brief Sets whether the soft keyboard is required for the XComponent.
 *
 * @param node XComponent instance.
 * @param needSoftKeyboard Whether the soft keyboard is required. **true** if the soft keyboard is required, **false**
 *     otherwise. The default value is **false**.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 20
 */
int32_t OH_ArkUI_XComponent_SetNeedSoftKeyboard(ArkUI_NodeHandle node, bool needSoftKeyboard);

/**
 * @brief Creates an {@link ArkUI_AccessibilityProvider} instance for this **XComponent** instance.
 *
 * @param node XComponent instance.
 * @return Pointer of the {@link ArkUI_AccessibilityProvider} type.
 * @since 20
 */
ArkUI_AccessibilityProvider* OH_ArkUI_AccessibilityProvider_Create(ArkUI_NodeHandle node);

/**
 * @brief Disposes of the {@link ArkUI_AccessibilityProvider} instance created using
 * {@link OH_ArkUI_AccessibilityProvider_Create}.
 *
 * @param provider {@link ArkUI_AccessibilityProvider} instance created using
 *     {@link OH_ArkUI_AccessibilityProvider_Create}.
 * @since 20
 */
void OH_ArkUI_AccessibilityProvider_Dispose(ArkUI_AccessibilityProvider* provider);

/**
 * @brief Sets a surface display callback for this {@link OH_ArkUI_SurfaceCallback} instance. This callback is invoked
 * when the application window has moved from the background to the foreground.
 *
 * @param callback Pointer to the target {@link OH_ArkUI_SurfaceCallback} instance.
 * @param onSurfaceShow Pointer to the surface display callback. - **surfaceHolder**: pointer to the target
 *     {@link OH_ArkUI_SurfaceHolder} instance.
 * @since 20
 */
void OH_ArkUI_SurfaceCallback_SetSurfaceShowEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceShow)(OH_ArkUI_SurfaceHolder* surfaceHolder));

/**
 * @brief Sets a surface hiding callback for this {@link OH_ArkUI_SurfaceCallback} instance. This callback is invoked
 * when the application window has moved from the foreground to the background.
 *
 * @param callback Pointer to the target {@link OH_ArkUI_SurfaceCallback} instance.
 * @param onSurfaceHide Pointer to the surface hiding callback. - **surfaceHolder**: pointer to the target
 *     {@link OH_ArkUI_SurfaceHolder} instance.
 * @since 20
 */
void OH_ArkUI_SurfaceCallback_SetSurfaceHideEvent(
    OH_ArkUI_SurfaceCallback* callback,
    void (*onSurfaceHide)(OH_ArkUI_SurfaceHolder* surfaceHolder));

/**
 * @brief Defines the surface configuration for the **XComponent**, which specifies whether the **XComponent**'s
 * surface should be treated as opaque during rendering.
 *
 * @since 22
 */
typedef struct ArkUI_XComponentSurfaceConfig ArkUI_XComponentSurfaceConfig;

/**
 * @brief Creates an {@link ArkUI_XComponentSurfaceConfig} object for an **XComponent**.
 *
 * @return Pointer to the created {@link ArkUI_XComponentSurfaceConfig} object.
 * @since 22
 */
ArkUI_XComponentSurfaceConfig* OH_ArkUI_XComponentSurfaceConfig_Create();

/**
 * @brief Disposes of an {@link ArkUI_XComponentSurfaceConfig} object.
 *
 * @param config Pointer to the target {@link ArkUI_XComponentSurfaceConfig} object.
 * @since 22
 */
void OH_ArkUI_XComponentSurfaceConfig_Dispose(ArkUI_XComponentSurfaceConfig* config);

/**
 * @brief Sets whether the surface held by the **XComponent** should be treated as opaque during rendering, regardless
 * of the actual pixel transparency.
 *
 * @param config Pointer to the target {@link ArkUI_XComponentSurfaceConfig} instance.
 * @param isOpaque Whether the surface held by the **XComponent** should be treated as opaque during rendering. **true**
 *     if the surface should be treated as opaque, **false** otherwise. The default value is **false**, which means
 *     pixel opacity of the surface content will be applied during rendering.
 * @since 22
 */
void OH_ArkUI_XComponentSurfaceConfig_SetIsOpaque(ArkUI_XComponentSurfaceConfig* config, bool isOpaque);

/**
 * @brief Sets the surface configuration for the {@link OH_ArkUI_SurfaceHolder} instance.
 *
 * @param surfaceHolder Pointer to the target {@link OH_ArkUI_SurfaceHolder} instance.
 * @param config Pointer to the target {@link ArkUI_XComponentSurfaceConfig} instance.
 * @return Result code.
 *         <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.</li>
 *         </ul>
 * @since 22
 */
int32_t OH_ArkUI_SurfaceHolder_SetSurfaceConfig(
    OH_ArkUI_SurfaceHolder *surfaceHolder,
    ArkUI_XComponentSurfaceConfig *config);
#ifdef __cplusplus
};
#endif
#endif // _NATIVE_INTERFACE_XCOMPONENT_H_
/** @} */