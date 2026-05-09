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
 * @addtogroup WindowManager
 * @{
 *
 * @brief Provides abilities of window on the native side.
 * @since 15
 */

/**
 * @file oh_window.h
 *
 * @brief The file declares the window management APIs. You can use the APIs to set and obtain the properties of a
 * window, and set its status bar style and navigation bar style.
 * 
 * @library libnative_window_manager.so
 * @kit ArkUI
 * @syscap SystemCapability.Window.SessionManager
 * @since 15
 */

#ifndef OH_WINDOW_H
#define OH_WINDOW_H
#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#include "stdbool.h"
#include "stdint.h"

#include "oh_window_comm.h"
#include "multimodalinput/oh_input_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 设置主窗口是否显示状态栏。
 * 
 * @param windowId 主窗口id。传入非主窗口id时调用无效。不存在对应窗口id时接口返回错误码WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL。
 * @param enabled 设置状态栏是否显示。true表示设置状态栏显示，false表示设置状态栏隐藏。
 * @param enableAnimation 设置是否开启状态栏的显隐动画。true表示开启状态栏的显隐动画，false表示关闭状态栏的显隐动画。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示不支持功能。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 15
 */
int32_t OH_WindowManager_SetWindowStatusBarEnabled(int32_t windowId, bool enabled, bool enableAnimation);

/**
 * @brief 设置主窗口的状态栏内容颜色。
 * 
 * @param windowId 主窗口id。传入非主窗口id时调用无效。不存在对应窗口id时接口返回错误码WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL。
 * @param color 要设置的颜色值，格式为ARGB。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示不支持功能。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 15
 */
int32_t OH_WindowManager_SetWindowStatusBarColor(int32_t windowId, int32_t color);

/**
 * @brief 设置主窗口是否显示导航栏。<!--RP2--><!--RP2End-->
 * 
 * @param windowId 主窗口id。传入非主窗口id时调用无效。不存在对应窗口id时接口返回错误码WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL。
 * @param enabled 设置导航栏是否显示。true表示设置导航栏显示，false表示设置导航栏隐藏。
 * @param enableAnimation 设置是否开启导航栏的显隐动画。true表示开启导航栏的显隐动画，false表示关闭导航栏的显隐动画。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示不支持功能。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 15
 */
int32_t OH_WindowManager_SetWindowNavigationBarEnabled(int32_t windowId, bool enabled, bool enableAnimation);

/**
 * @brief 获取指定窗口的避让区域。
 * 
 * @param windowId 创建窗口时的窗口id。默认值为0。该参数为整数。
 * @param type 避让区域的类型。
 * @param avoidArea 返回指向指定窗口的避让区域的指针，作为出参使用。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功，返回指向对应窗口id的避让区域的指针。
 *     返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示参数错误。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 15
 */
int32_t OH_WindowManager_GetWindowAvoidArea(
    int32_t windowId, WindowManager_AvoidAreaType type, WindowManager_AvoidArea* avoidArea);

/**
 * @brief 判断指定窗口是否显示。
 * 
 * @param windowId 创建窗口时的窗口id。默认值为0。该参数为整数。
 * @param isShow 返回指定窗口是否显示的结果。true表示指定窗口显示，false表示指定窗口不显示，作为出参使用。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示参数错误。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 * @since 15
 */
int32_t OH_WindowManager_IsWindowShown(int32_t windowId, bool* isShow);

/**
 * @brief 显示指定窗口。
 * 
 * @param windowId 创建窗口时的窗口id。默认值为0。该参数为整数。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 15
 */
int32_t OH_WindowManager_ShowWindow(int32_t windowId);

/**
 * @brief 设置指定窗口是否可触。
 * 
 * @param windowId 创建窗口时的窗口id。默认值为0。该参数为整数。
 * @param isTouchable 窗口是否可触。true表示窗口可触，false表示窗口不可触。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 15
 */
int32_t OH_WindowManager_SetWindowTouchable(int32_t windowId, bool isTouchable);

/**
 * @brief 设置指定窗口是否可获焦。
 * 
 * @param windowId 创建窗口时的窗口id。默认值为0。该参数为整数。
 * @param isFocusable 窗口是否可获焦。true表示窗口可获焦，false表示窗口不可获焦。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 15
 */
int32_t OH_WindowManager_SetWindowFocusable(int32_t windowId, bool isFocusable);

/**
 * @brief 设置指定窗口背景颜色。
 * 
 * @param windowId 创建窗口时的窗口id。默认值为0。该参数为整数。
 * @param color 设置窗口的背景色。该参数为字符串类型，格式为十六进制RGB或ARGB颜色。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示参数错误。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 * @since 18
 */
int32_t OH_WindowManager_SetWindowBackgroundColor(int32_t windowId, const char* color);

/**
 * @brief 指定主窗口设置窗口亮度。当窗口处于前台且获焦时，窗口亮度生效。
 * 
 * @param windowId 创建窗口时的窗口id。默认值为0。该参数为整数。
 * @param brightness 指定的屏幕亮度值。该参数为浮点数，取值范围为[0.0, 1.0]或-1.0。1.0表示最亮，-1.0表示恢复成设置窗口亮度前的系统控制中心亮度。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示参数错误。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 18
 */
int32_t OH_WindowManager_SetWindowBrightness(int32_t windowId, float brightness);

/**
 * @brief 设置指定窗口是否开启屏幕常亮。
 * 
 * @param windowId 创建窗口时的窗口id。默认值为0。该参数为整数。
 * @param isKeepScreenOn 指定窗口是否开启屏幕常亮。true表示开启屏幕常亮，false表示关闭屏幕常亮。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 15
 */
int32_t OH_WindowManager_SetWindowKeepScreenOn(int32_t windowId, bool isKeepScreenOn);

/**
 * @brief 设置指定窗口是否开启隐私模式。
 * 
 * @permission ohos.permission.PRIVACY_WINDOW
 * @param windowId 创建窗口时的窗口id。默认值为0。该参数为整数。
 * @param isPrivacy 指定窗口是否开启隐私模式。true表示开启隐私模式，false表示关闭隐私模式。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYST