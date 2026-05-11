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
 * @addtogroup WindowManager
 * @{
 *
 * @brief Provides  abilities of windowManager on the native side, such as key event
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
 * @brief Defines a function for filtering multimodal key events
 * @param keyEvent multimodal keyEvent
 * @since 12
 */
typedef bool (*OH_NativeWindowManager_KeyEventFilter)(Input_KeyEvent* keyEvent);

/**
 * @brief 注册按键事件的过滤函数。
 * 
 * @param windowId 需要过滤按键事件的窗口ID。
 * @param keyEventFilter 多模按键的过滤函数。
 * @return 返回窗口管理接口的通用状态码，具体可见{@link WindowManager_ErrorCode}。
 * @since 12
 */
WindowManager_ErrorCode OH_NativeWindowManager_RegisterKeyEventFilter(int32_t windowId,
    OH_NativeWindowManager_KeyEventFilter keyEventFilter);

/**
 * @brief 取消注册窗口的按键事件过滤函数。
 * 
 * @param windowId 需要取消过滤按键事件的窗口ID。
 * @return 返回窗口管理接口的通用状态码，具体可见{@link WindowManager_ErrorCode}。
 * @since 12
 */
WindowManager_ErrorCode OH_NativeWindowManager_UnregisterKeyEventFilter(int32_t windowId);

/**
 * @brief Defines a function for filtering multimodal mouse events
 * @param mouseEvent multimodal mouseEvent
 * @since 15
 */
typedef bool (*OH_NativeWindowManager_MouseEventFilter)(Input_MouseEvent* mouseEvent);

/**
 * @brief 注册鼠标事件的过滤函数。
 * 
 * @param windowId 需要过滤鼠标事件的窗口ID。
 * @param mouseEventFilter 多模鼠标事件的过滤函数。
 * @return 返回窗口管理接口的通用状态码，具体可见{@link WindowManager_ErrorCode}。
 * @since 15
 */
WindowManager_ErrorCode OH_NativeWindowManager_RegisterMouseEventFilter(int32_t windowId,
    OH_NativeWindowManager_MouseEventFilter mouseEventFilter);

/**
 * @brief 取消注册窗口的鼠标事件过滤函数。
 * 
 * @param windowId 需要取消过滤鼠标事件的窗口ID。
 * @return 返回窗口管理接口的通用状态码，具体可见{@link WindowManager_ErrorCode}。
 * @since 15
 */
WindowManager_ErrorCode OH_NativeWindowManager_UnregisterMouseEventFilter(int32_t windowId);

/**
 * @brief Defines a function for filtering multimodal touch events
 * @param touchEvent multimodal touchEvent
 * @since 15
 */
typedef bool (*OH_NativeWindowManager_TouchEventFilter)(Input_TouchEvent* touchEvent);

/**
 * @brief 注册触摸事件的过滤函数。
 *
 * @param windowId 需要过滤触摸事件的窗口ID。
 * @param touchEventFilter 多模触摸事件的过滤函数。
 * @return 返回窗口管理接口的通用状态码，具体可见{@link WindowManager_ErrorCode}。
 * @since 15
 */
WindowManager_ErrorCode OH_NativeWindowManager_RegisterTouchEventFilter(int32_t windowId,
    OH_NativeWindowManager_TouchEventFilter touchEventFilter);

/**
 * @brief 取消注册窗口的触摸事件过滤函数。
 * 
 * @param windowId 需要取消过滤触摸事件的窗口ID。
 * @return 返回窗口管理接口的通用状态码，具体可见{@link WindowManager_ErrorCode}。
 * @since 15
 */
WindowManager_ErrorCode OH_NativeWindowManager_UnregisterTouchEventFilter(int32_t windowId);
#ifdef __cplusplus
}
#endif
#endif // INCLUDE_OH_WINDOW_EVENT_FILTER_H

/** @} */