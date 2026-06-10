/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
 * @addtogroup WindowManager
 * @{
 *
 * @brief Provides abilities of WindowManager on the native side, such as key event.
 * filtration.
 *
 * @since 12
 */

/**
 * @file oh_window_event_filter.h
 *
 * @brief The file declares the APIs for a window to filter multimodal key events. When a multimodal input event passes
 * through the window, the window can interrupt the event to prevent it from being further distributed.
 *
 * @syscap SystemCapability.Window.SessionManager
 * @library libnative_window_manager.so
 * @kit ArkUI
 * @since 12
 */

#ifndef INCLUDE_OH_WINDOW_EVENT_FILTER_H
#define INCLUDE_OH_WINDOW_EVENT_FILTER_H
#include "stdbool.h"
#include "stdint.h"
#include "oh_window_comm.h"
#include "multimodalinput/oh_input_manager.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines a function for filtering multimodal key events.
 * @param keyEvent multimodal key event. For details, see {@link Input_KeyEvent}.
 * @return Returns whether to filter this event. Returning true prevents the window from dispatching it further;
 *         Returns false indicates that the event is not intercepted.
 * @since 12
 */
typedef bool (*OH_NativeWindowManager_KeyEventFilter)(Input_KeyEvent* keyEvent);

/**
 * @brief Registers a function for filtering multimodal key events.
 *
 * @param windowId ID of the window.
 * @param keyEventFilter Filter function for multimodal key event.
 * @return Returns the status code of the execution.
 *     <ul>
 *     <li>Returns {@link OK} if the operation is successful.</li>
 *     <li>Returns {@link INVALID_WINDOW_ID} if the windowId is invalid.</li>
 *     <li>Returns {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} if the keyEventFilter is invalid.</li>
 *     <li>Returns {@link SERVICE_ERROR} if the window manager service error occurs.</li>
 *     </ul>
 * @since 12
 */
WindowManager_ErrorCode OH_NativeWindowManager_RegisterKeyEventFilter(int32_t windowId,
    OH_NativeWindowManager_KeyEventFilter keyEventFilter);

/**
 * @brief Unregisters a function for filtering multimodal key events.
 *
 * @param windowId ID of the window.
 * @return Returns the status code of the execution.
 *     <ul>
 *     <li>Returns {@link OK} if the operation is successful.</li>
 *     <li>Returns {@link INVALID_WINDOW_ID} if the windowId is invalid.</li>
 *     <li>Returns {@link SERVICE_ERROR} if the window manager service error occurs.</li>
 *     </ul>
 * @since 12
 */
WindowManager_ErrorCode OH_NativeWindowManager_UnregisterKeyEventFilter(int32_t windowId);

/**
 * @brief Defines a function for filtering multimodal mouse events.
 * @param mouseEvent multimodal mouse event. For details, see {@link Input_MouseEvent}.
 * @return Returns whether to filter this event. Returning true prevents the window from dispatching it further;
 *         returning false indicates that the event is not intercepted.
 * @since 15
 */
typedef bool (*OH_NativeWindowManager_MouseEventFilter)(Input_MouseEvent* mouseEvent);

/**
 * @brief Registers a function for filtering multimodal mouse events.
 *
 * @param windowId ID of the window.
 * @param mouseEventFilter Filter function for multimodal mouse event.
 * @return Returns the status code of the execution.
 *     <ul>
 *     <li>Returns {@link OK} if the operation is successful.</li>
 *     <li>Returns {@link INVALID_WINDOW_ID} if the windowId is invalid.</li>
 *     <li>Returns {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} if the mouseEventFilter is invalid.</li>
 *     <li>Returns {@link SERVICE_ERROR} if the window manager service error occurs.</li>
 *     </ul>
 * @since 15
 */
WindowManager_ErrorCode OH_NativeWindowManager_RegisterMouseEventFilter(int32_t windowId,
    OH_NativeWindowManager_MouseEventFilter mouseEventFilter);

/**
 * @brief Unregisters a function for filtering multimodal mouse events.
 *
 * @param windowId ID of the window.
 * @return Returns the status code of the execution.
 *     <ul>
 *     <li>Returns {@link OK} if the operation is successful.</li>
 *     <li>Returns {@link INVALID_WINDOW_ID} if the windowId is invalid.</li>
 *     <li>Returns {@link SERVICE_ERROR} if the window manager service error occurs.</li>
 *     </ul>
 * @since 15
 */
WindowManager_ErrorCode OH_NativeWindowManager_UnregisterMouseEventFilter(int32_t windowId);

/**
 * @brief Defines a function for filtering multimodal touch events.
 * @param touchEvent multimodal touchEvent. For details, see {@link Input_TouchEvent}.
 * @return Returns whether to filter this event. Returning true prevents the window from dispatching it further;
 *         returning false indicates that the event is not intercepted.
 * @since 15
 */
typedef bool (*OH_NativeWindowManager_TouchEventFilter)(Input_TouchEvent* touchEvent);

/**
 * @brief Registers a function for filtering multimodal touch events.
 *
 * @param windowId ID of the window.
 * @param touchEventFilter Filter function for multimodal touch event.
 * @return Returns the status code of the execution.
 *     <ul>
 *     <li>Returns {@link OK} if the operation is successful.</li>
 *     <li>Returns {@link INVALID_WINDOW_ID} if the windowId is invalid.</li>
 *     <li>Returns {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} if the touchEventFilter is invalid.</li>
 *     <li>Returns {@link SERVICE_ERROR} if the window manager service error occurs.</li>
 *     </ul>
 * @since 15
 */
WindowManager_ErrorCode OH_NativeWindowManager_RegisterTouchEventFilter(int32_t windowId,
    OH_NativeWindowManager_TouchEventFilter touchEventFilter);

/**
 * @brief Unregisters a function for filtering multimodal touch events.
 * 
 * @param windowId ID of the window for which the function is unregistered.
 * @return Returns the status code of the execution.
 *     <ul>
 *     <li>Returns {@link OK} if the operation is successful.</li>
 *     <li>Returns {@link INVAILD_WINDOW_ID} if the window id is invalid.</li>
 *     <li>Returns {@link SERVICE_ERROR} if the window manager service error occurs.</li>
 *     </ul>
 * @since 15
 */
WindowManager_ErrorCode OH_NativeWindowManager_UnregisterTouchEventFilter(int32_t windowId);

/**
 * @brief Gets the key event filter callback for the window.
 *
 * @param windowId ID of the window.
 * @param outKeyEventFilter Output parameter for the registered key event filter callback.
 *                          If no filter has been registered, *outKeyEventFilter will return NULL.
 * @return Returns the error code defined by {@link WindowManager_ErrorCode}.
 *     <ul>
 *     <li>Returns {@link OK} if the operation is successful.</li>
 *     <li>Returns {@link INVALID_WINDOW_ID} if the windowId is invalid.</li>
 *     <li>Returns {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} if the outKeyEventFilter is NULL.</li>
 *     </ul>
 * @since 26.0.0
 */
WindowManager_ErrorCode OH_NativeWindowManager_GetKeyEventFilter(int32_t windowId,
    OH_NativeWindowManager_KeyEventFilter* outKeyEventFilter);

/**
 * @brief Gets the mouse event filter callback for the window.
 *
 * @param windowId ID of the window.
 * @param outMouseEventFilter Output parameter for the registered mouse event filter callback.
 *                            If no filter has been registered, *outMouseEventFilter will return NULL.
 * @return Returns the error code defined by {@link WindowManager_ErrorCode}.
 *     <ul>
 *     <li>Returns {@link OK} if the operation is successful.</li>
 *     <li>Returns {@link INVALID_WINDOW_ID} if the windowId is invalid.</li>
 *     <li>Returns {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} if the outMouseEventFilter is NULL.</li>
 *     </ul>
 * @since 26.0.0
 */
WindowManager_ErrorCode OH_NativeWindowManager_GetMouseEventFilter(int32_t windowId,
    OH_NativeWindowManager_MouseEventFilter* outMouseEventFilter);

/**
 * @brief Gets the touch event filter callback for the window.
 *
 * @param windowId ID of the window.
 * @param outTouchEventFilter Output parameter for the registered touch event filter callback.
 *                            If no filter has been registered, *outTouchEventFilter will return NULL.
 * @return Returns the error code defined by {@link WindowManager_ErrorCode}.
 *     <ul>
 *     <li>Returns {@link OK} if the operation is successful.</li>
 *     <li>Returns {@link INVALID_WINDOW_ID} if the windowId is invalid.</li>
 *     <li>Returns {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} if the outTouchEventFilter is NULL.</li>
 *     </ul>
 * @since 26.0.0
 */
WindowManager_ErrorCode OH_NativeWindowManager_GetTouchEventFilter(int32_t windowId,
    OH_NativeWindowManager_TouchEventFilter* outTouchEventFilter);

#ifdef __cplusplus
}
#endif
#endif // INCLUDE_OH_WINDOW_EVENT_FILTER_H

/** @} */