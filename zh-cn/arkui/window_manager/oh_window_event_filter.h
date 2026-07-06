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
 * @brief 定义多模按键的过滤函数。
 * @param keyEvent 多模按键事件，具体可见{@link Input_KeyEvent}，事件定义在oh_input_manager中。
 * @return 返回是否过滤该事件。返回true窗口不再往下分发，返回false表示不拦截。
 * @since 12
 */
typedef bool (*OH_NativeWindowManager_KeyEventFilter)(Input_KeyEvent* keyEvent);

/**
 * @brief 注册按键事件的过滤函数。
 *
 * @param windowId 窗口ID。
 * @param keyEventFilter 多模按键的过滤函数。
 * @return 函数返回的执行结果。
 *     <ul>
 *     <li>返回OK，表示接口调用成功。</li>
 *     <li>返回INVALID_WINDOW_ID，表示参数windowId无效。</li>
 *     <li>返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示参数keyEventFilter无效。</li>
 *     <li>返回SERVICE_ERROR，表示窗口管理服务异常。</li>
 *     </ul>
 * @since 12
 */
WindowManager_ErrorCode OH_NativeWindowManager_RegisterKeyEventFilter(int32_t windowId,
    OH_NativeWindowManager_KeyEventFilter keyEventFilter);

/**
 * @brief 取消注册窗口的按键事件过滤函数。
 *
 * @param windowId 窗口ID。
 * @return 函数返回的执行结果。
 *     <ul>
 *     <li>返回OK，表示接口调用成功。</li>
 *     <li>返回INVALID_WINDOW_ID，表示参数windowId无效。</li>
 *     <li>返回SERVICE_ERROR，表示窗口管理服务异常。</li>
 *     </ul>
 * @since 12
 */
WindowManager_ErrorCode OH_NativeWindowManager_UnregisterKeyEventFilter(int32_t windowId);

/**
 * @brief 定义多模鼠标事件的过滤函数。
 * @param mouseEvent 多模鼠标事件，具体可见{@link Input_MouseEvent}，事件定义在oh_input_manager中。
 * @return 返回是否过滤该事件。true表示过滤该事件，不会继续往下分发；false表示不过滤不拦截此事件，将会继续分发。
 * @since 15
 */
typedef bool (*OH_NativeWindowManager_MouseEventFilter)(Input_MouseEvent* mouseEvent);

/**
 * @brief 注册鼠标事件的过滤函数。
 *
 * @param windowId 窗口ID。
 * @param mouseEventFilter 多模鼠标事件的过滤函数。
 * @return 函数返回的执行结果。
 *     <ul>
 *     <li>返回OK，表示接口调用成功。</li>
 *     <li>返回INVALID_WINDOW_ID，表示参数windowId无效。</li>
 *     <li>返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示参数mouseEventFilter无效。</li>
 *     <li>返回SERVICE_ERROR，表示窗口管理服务异常。</li>
 *     </ul>
 * @since 15
 */
WindowManager_ErrorCode OH_NativeWindowManager_RegisterMouseEventFilter(int32_t windowId,
    OH_NativeWindowManager_MouseEventFilter mouseEventFilter);

/**
 * @brief 取消注册窗口的鼠标事件过滤函数。
 *
 * @param windowId 窗口ID。
 * @return 函数返回的执行结果。
 *     <ul>
 *     <li>返回OK，表示接口调用成功。</li>
 *     <li>返回INVALID_WINDOW_ID，表示参数windowId无效。</li>
 *     <li>返回SERVICE_ERROR，表示窗口管理服务异常。</li>
 *     </ul>
 * @since 15
 */
WindowManager_ErrorCode OH_NativeWindowManager_UnregisterMouseEventFilter(int32_t windowId);

/**
 * @brief 定义多模触摸事件的过滤函数。
 * @param touchEvent 多模触摸事件，具体可见{@link Input_TouchEvent}，事件定义在oh_input_manager中。
 * @return 返回是否过滤该事件。true表示过滤该事件，不会继续往下分发；false表示不过滤不拦截此事件，将会继续分发。
 * @since 15
 */
typedef bool (*OH_NativeWindowManager_TouchEventFilter)(Input_TouchEvent* touchEvent);

/**
 * @brief 注册触摸事件的过滤函数。
 *
 * @param windowId 窗口ID。
 * @param touchEventFilter 多模触摸事件的过滤函数。
 * @return 函数返回的执行结果。
 *     <ul>
 *     <li>返回OK，表示接口调用成功。</li>
 *     <li>返回INVALID_WINDOW_ID，表示参数windowId无效。</li>
 *     <li>返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示参数touchEventFilter无效。</li>
 *     <li>返回SERVICE_ERROR，表示窗口管理服务异常。</li>
 *     </ul>
 * @since 15
 */
WindowManager_ErrorCode OH_NativeWindowManager_RegisterTouchEventFilter(int32_t windowId,
    OH_NativeWindowManager_TouchEventFilter touchEventFilter);

/**
 * @brief 取消注册窗口的触摸事件过滤函数。
 *
 * @param windowId 窗口ID。
 * @return 函数返回的执行结果。
 *     <ul>
 *     <li>返回OK，表示接口调用成功。</li>
 *     <li>返回INVALID_WINDOW_ID，表示参数windowId无效。</li>
 *     <li>返回SERVICE_ERROR，表示窗口管理服务异常。</li>
 *     </ul>
 * @since 15
 */
WindowManager_ErrorCode OH_NativeWindowManager_UnregisterTouchEventFilter(int32_t windowId);

/**
 * @brief 获取指定窗口注册的多模按键事件过滤函数。
 *
 * @param windowId 窗口ID。
 * @param outKeyEventFilter 返回已注册的多模按键事件过滤函数指针。如果窗口没有注册过滤器，*outKeyEventFilter将返回NULL。
 * @return 函数返回的执行结果。
 *     <ul>
 *     <li>返回OK，表示接口调用成功。</li>
 *     <li>返回INVALID_WINDOW_ID，表示入参windowId无效。</li>
 *     <li>返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示入参outKeyEventFilter为NULL。</li>
 *     </ul>
 * @since 26.0.0
 */
WindowManager_ErrorCode OH_NativeWindowManager_GetKeyEventFilter(int32_t windowId,
    OH_NativeWindowManager_KeyEventFilter* outKeyEventFilter);

/**
 * @brief 获取指定窗口注册的多模鼠标事件过滤函数。
 *
 * @param windowId 窗口ID。
 * @param outMouseEventFilter 返回已注册的多模鼠标事件过滤函数指针。如果窗口没有注册过滤器，*outMouseEventFilter将返回NULL。
 * @return 函数返回的执行结果。
 *     <ul>
 *     <li>返回OK，表示接口调用成功。</li>
 *     <li>返回INVALID_WINDOW_ID，表示入参windowId无效。</li>
 *     <li>返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示入参outMouseEventFilter为NULL。</li>
 *     </ul>
 * @since 26.0.0
 */
WindowManager_ErrorCode OH_NativeWindowManager_GetMouseEventFilter(int32_t windowId,
    OH_NativeWindowManager_MouseEventFilter* outMouseEventFilter);

/**
 * @brief 获取指定窗口注册的多模触摸事件过滤函数。
 *
 * @param windowId 窗口ID。
 * @param outTouchEventFilter 返回已注册的多模触摸事件过滤函数指针。如果窗口没有注册过滤器，*outTouchEventFilter将返回NULL。
 * @return 函数返回的执行结果。
 *     <ul>
 *     <li>返回OK，表示接口调用成功。</li>
 *     <li>返回INVALID_WINDOW_ID，表示入参windowId无效。</li>
 *     <li>返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示入参outTouchEventFilter为NULL。</li>
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