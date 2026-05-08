
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

/**
 * @addtogroup WindowManager
 * @{
 *
 * @brief Provides abilities of window on the native side.
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
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 *     返回WINDOW_MANAGER_ERRORCODE_NO_PERMISSION，权限校验错误。
 * @since 15
 */
int32_t OH_WindowManager_SetWindowPrivacyMode(int32_t windowId, bool isPrivacy);

/**
 * @brief 获取指定窗口属性。
 * 
 * @param windowId 创建窗口时的窗口id。默认值为0。该参数为整数。
 * @param windowProperties 返回指向指定窗口的属性的指针，作为出参使用。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功，在windowProperties中返回窗口属性的指针。
 *     返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示参数错误。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 * @since 15
 */
int32_t OH_WindowManager_GetWindowProperties(
    int32_t windowId, WindowManager_WindowProperties* windowProperties);

/**
 * @brief 获取指定窗口截图。
 * 
 * @param windowId 创建窗口时的窗口id。默认值为0。该参数为整数。
 *     窗口id非法或者窗口已经销毁，不能获取指定窗口截图，需要传入有效的窗口id才能成功获取指定窗口截图。
 *     请通过窗口对象调用{@link getWindowProperties()}接口（ArkTS接口）获取有效的窗口id。
 * @param pixelMap 返回指向指定窗口的截图的指针，作为出参使用。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功，在返回pixelMap中的像素图的指针。
 *     返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示参数错误。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 15
 */
int32_t OH_WindowManager_Snapshot(int32_t windowId, OH_PixelmapNative* pixelMap);

/**
 * @brief 获取指定屏幕上可见的窗口布局信息数组，按当前窗口层级排列，层级最高的对应数组下标为0。
 * 
 * @param displayId 指定屏幕的id。请通过窗口对象调用{@link getWindowProperties()}接口（ArkTS接口）获取有效的屏幕id。
 * @param windowLayoutInfoList 指定屏幕上可见的窗口布局信息数组的数组指针，作为出参使用。
 * @param windowLayoutInfoSize 指定屏幕上可见的窗口布局信息数组长度的指针，作为出参使用。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功，返回指定屏幕上可见的窗口布局信息数组的数组指针和数组长度的指针。
 *     返回WINDOW_MANAGER_ERRORCODE_INVALID_PARAM，表示参数错误。
 *     返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示不支持功能。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 17
 */
int32_t OH_WindowManager_GetAllWindowLayoutInfoList(int64_t displayId,
    WindowManager_Rect** windowLayoutInfoList, size_t* windowLayoutInfoSize);

/**
 * @brief 释放窗口布局信息数组占用的内存。
 * 
 * @param windowLayoutInfoList 指定屏幕上可见的窗口布局信息数组的数组指针，可通过{@link OH_WindowManager_GetAllWindowLayoutInfoList}接口获取。
 * @since 17
 */
void OH_WindowManager_ReleaseAllWindowLayoutInfoList(WindowManager_Rect* windowLayoutInfoList);

/**
 * @brief 将多模触摸事件注入给目标窗口，仅支持注入同进程窗口，且该注入不会触发窗口焦点和层级变化，不会触发窗口拖拽，事件会直接发送给ArkUI。该接口需要在指定窗口加载UI之后调用。
 * 
 * @param windowId 创建窗口时的窗口id。默认值为0。该参数为整数。
 * @param touchEvent 多模触摸事件，具体可见{@link Input_TouchEvent}，事件定义在oh_input_manager.h中。该参数包含的部分字段有参数限制，其中，
 *     action应为大于等于0且小于等于3的整数；id、displayX、displayY和actionTime应为不小于0的整数。
 *     以上参数不符合限制条件会返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示：窗口管理器服务异常。
 * @param windowX 注入事件相对于注入窗口的落点横坐标。该参数为整数。
 * @param windowY 注入事件相对于注入窗口的落点纵坐标。该参数为整数。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 20
 */
int32_t OH_WindowManager_InjectTouchEvent(
    int32_t windowId, Input_TouchEvent* touchEvent, int32_t windowX, int32_t windowY);

/**
 * @brief 获取全部主窗信息。
 * 
 * @permission ohos.permission.CUSTOM_SCREEN_CAPTURE
 * @param infoList 指向主窗口信息列表的指针，作为出参使用。
 * @param mainWindowInfoSize 指向主窗口信息数组长度的指针，作为出参使用。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_NO_PERMISSION，权限校验错误。
 *     返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示不支持功能。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 21
 */
int32_t OH_WindowManager_GetAllMainWindowInfo(
    WindowManager_MainWindowInfo** infoList, size_t* mainWindowInfoSize);

/**
 * @brief 释放主窗口信息列表的内存。
 * 
 * @param infoList 主窗信息列表。
 * @since 21
 */
void OH_WindowManager_ReleaseAllMainWindowInfo(WindowManager_MainWindowInfo* infoList);

/**
 * @brief 接收主窗口截图列表的回调接口。
 * 
 * @param snapshotPixelMapList 窗口截图列表。
 * @param snapshotListSize 窗口截图列表的大小。
 * @since 21
 */
typedef void (*OH_WindowManager_WindowSnapshotCallback)(const OH_PixelmapNative** snapshotPixelMapList,
    size_t snapshotListSize);

/**
 * @brief 获取一个或多个指定windowId的主窗口截图。
 * 
 * @permission ohos.permission.CUSTOM_SCREEN_CAPTURE
 * @param windowIdList 需要获取截图的主窗口ID列表。
 * @param windowIdListSize 主窗口ID列表的长度。
 * @param config 获取窗口截图时的配置信息。
 * @param callback 获取窗口截图的回调对象。用于返回窗口截图列表，并按照指定的窗口ID列表顺序排列。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_NO_PERMISSION，权限校验错误。
 *     返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示不支持功能。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 21
 */
int32_t OH_WindowManager_GetMainWindowSnapshot(int32_t* windowIdList, size_t windowIdListSize,
    WindowManager_WindowSnapshotConfig config, OH_WindowManager_WindowSnapshotCallback callback);

/**
 * @brief 释放主窗口截图列表的内存。
 * 
 * @param snapshotPixelMapList 窗口截图列表。
 * @since 21
 */
void OH_WindowManager_ReleaseMainWindowSnapshot(const OH_PixelmapNative* snapshotPixelMapList);

/**
 * @brief 锁定鼠标光标，控制鼠标光标不超过指定窗口区域，同时可控制光标是否跟随鼠标移动。仅支持获焦窗口调用，失焦之后会自动取消锁定。
 * 
 * @permission ohos.permission.LOCK_WINDOW_CURSOR
 * @param windowId 创建窗口时的窗口ID。该参数为整数。
 * @param isCursorFollowMovement 设置鼠标光标的锁定模式，若为true，则光标会跟随鼠标移动；若为false，则光标不会跟随鼠标移动。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_NO_PERMISSION，表示没有权限调用该接口。
 *     返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示不支持该设备。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 22
 */
int32_t OH_WindowManager_LockCursor(int32_t windowId, bool isCursorFollowMovement);

/**
 * @brief 清除窗口设置的鼠标光标指定的模式。
 * 
 * @permission ohos.permission.LOCK_WINDOW_CURSOR
 * @param windowId 创建窗口时的窗口ID。该参数为整数。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_NO_PERMISSION，表示没有权限调用该接口。
 *     返回WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED，表示不支持该设备。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL，表示窗口管理器服务异常。
 * @since 22
 */
int32_t OH_WindowManager_UnlockCursor(int32_t windowId);

/**
 * @brief 判断当前帧是否为首帧。
 *  
 * @param metrics 帧率指标数据对象。
 * @param isFirstDrawFrame 作为出参使用，表示当前帧是否为首帧，true表示是首帧，false表示不是首帧。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误，对应参数取值范围不合理。
 *     具体可见{@link WindowManager_ErrorCode}。
 * @since 26.0.0
 */
int32_t OH_WindowManager_FrameMetrics_IsFirstDrawFrame(
    const OH_WindowManager_FrameMetrics* metrics, bool* isFirstDrawFrame);

/**
 * @brief 获取当前帧中手势处理的耗时。
 * 
 * @param metrics 帧率指标数据对象。
 * @param duration 作为出参使用，表示当前帧中手势处理的耗时，单位为纳秒。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误，对应参数取值范围不合理。
 *     具体可见{@link WindowManager_ErrorCode}。
 * @since 26.0.0
 */
int32_t OH_WindowManager_FrameMetrics_GetInputHandlingDuration(
    const OH_WindowManager_FrameMetrics* metrics, uint64_t* duration);

/**
 * @brief 获取当前帧中布局测量的耗时。
 * 
 * @param metrics 帧率指标数据对象。
 * @param duration 作为出参使用，表示当前帧中布局测量的耗时，单位为纳秒。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误，对应参数取值范围不合理。
 *     具体可见{@link WindowManager_ErrorCode}。
 * @since 26.0.0
 */
int32_t OH_WindowManager_FrameMetrics_GetLayoutMeasureDuration(
    const OH_WindowManager_FrameMetrics* metrics, uint64_t* duration);

/**
 * @brief 获取当前帧开始的时间戳。
 * 
 * @param metrics 帧率指标数据对象。
 * @param timestamp 作为出参使用，表示当前帧开始的时间戳，单位为纳秒。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误，对应参数取值范围不合理。
 *     具体可见{@link WindowManager_ErrorCode}。
 * @since 26.0.0
 */
int32_t OH_WindowManager_FrameMetrics_GetVsyncTimestamp(
    const OH_WindowManager_FrameMetrics* metrics, uint64_t* timestamp);

/**
 * @brief 订阅窗口帧率指标变更监听事件。 
 *  该接口依赖窗口页面内容加载，即需要在ArkTS侧loadContent()接口或setUIContent()接口生效后调用。 
 *  应用注册帧率指标变更监听后，仅当客户端UI内容发生重绘（例如页面切换、响应式组件交互、设置背景色和透明度等）时才会触发已注册回调。 
 *  如需取消订阅，请使用{@link OH_WindowManager_UnregisterFrameMetricsMeasuredCallback}接口。
 * 
 * @param windowId 创建窗口时的窗口ID。
 * @param callback 用于返回帧率指标结果的回调函数。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。可能原因：
 *     1. 窗口未创建或已销毁；
 *     2. 窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误，对应参数取值范围不合理。
 *     具体可见{@link WindowManager_ErrorCode}。
 * @since 26.0.0
 */
int32_t OH_WindowManager_RegisterFrameMetricsMeasuredCallback(int32_t windowId, 
    OH_WindowManager_FrameMetricsMeasuredCallback callback);

/**
 * @brief 取消订阅窗口帧率指标变更监听事件。 
 *  该接口依赖窗口页面内容加载，即需要在ArkTS侧loadContent()接口或setUIContent()接口生效后调用。 
 *  如需订阅，请使用{@link OH_WindowManager_RegisterFrameMetricsMeasuredCallback}接口。
 * 
 * @param windowId 创建窗口时的窗口ID。
 * @param callback 用于返回帧率指标结果的回调函数。
 * @return 返回结果代码。
 *     返回OK，表示函数调用成功。
 *     返回WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL，表示窗口状态异常。可能原因：
 *     1. 窗口未创建或已销毁；
 *     2. 窗口状态异常。
 *     返回WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM，表示参数错误，对应参数取值范围不合理。
 *     具体可见{@link WindowManager_ErrorCode}。
 * @since 26.0.0
 */
int32_t OH_WindowManager_UnregisterFrameMetricsMeasuredCallback(int32_t windowId, 
    OH_WindowManager_FrameMetricsMeasuredCallback callback);

/**
 * @brief 获取窗口所在屏幕的系统默认显示大小缩放因子。
 *
 * @param info 显示当前窗口的大小缩放因子信息。
 * @param density 系统默认显示尺寸比例因子
 * @return 返回执行的状态代码。
 * {@link WS_OK}函数调用成功。
 * {@link WINDOWS_MANAGER_ERRORCODE_INCORRECT_PARAM}参数错误。可能原因：
 * 1.参数范围非法。
 * @since 24
 */
int32_t OH_WindowManager_DensityInfo_GetDefaultDensity(const OH_WindowManager_DensityInfo* info,
    float* density);

/**
 * @brief 获取窗口所在屏幕的系统显示大小缩放因子。
 *
 * @param info 显示当前窗口的大小缩放因子信息。
 * @param density 系统显示尺寸比例因子
 * @return 返回执行的状态代码。
 * {@link WS_OK}函数调用成功。
 * {@link WINDOWS_MANAGER_ERRORCODE_INCORRECT_PARAM}参数错误。可能原因：
 * 1.参数范围非法。
 * @since 24
 */
int32_t OH_WindowManager_DensityInfo_GetSystemDensity(const OH_WindowManager_DensityInfo* info,
    float* density);

/**
 * @brief 获取窗口的自定义显示大小缩放因子。
 *
 * @param info 当前窗口所在屏幕的显示大小缩放因子信息。
 * @param density 窗口的自定义显示大小缩放因子。返回值-1表示没有自定义
 * 已设置显示大小缩放因子，或已重置。
 * @return 返回执行的状态代码。
 * {@link WS_OK}函数调用成功。
 * {@link WINDOWS_MANAGER_ERRORCODE_INCORRECT_PARAM}参数错误。可能原因：
 * 1.参数范围非法。
 * @since 24
 */
int32_t OH_WindowManager_DensityInfo_GetCustomDensity(const OH_WindowManager_DensityInfo* info,
    float* density);

/**
 * @brief 获取窗口所在屏幕的系统显示大小缩放系数，窗口所在屏幕的系统默认显示大小缩放系数，
 * 以及当前窗口自定义设置的显示大小缩放系数。
 *
 * @param windowId 创建window时的WindowId。
 * @param info 显示当前窗口的显示密度信息。
 * 返回值NULL表示当前设备不支持此接口。
 * @return 返回执行的状态代码。
 * {@link WS_OK}函数调用成功。
 * {@link WINDOWS_MANAGER_ERRORCODE_STATE_ABNORMAL}此窗口状态不正常。可能原因：
 * 1.窗口不被创建或销毁；
 * 2.该窗口状态不正常。
 * {@link WINDOWS_MANAGER_ERRORCODE_INCORRECT_PARAM}参数错误。可能原因：
 * 1.参数范围非法。
 * @since 24
 */
int32_t OH_WindowManager_GetDensityInfoCopy(int32_t windowId,
    const OH_WindowManager_DensityInfo** info);

/**
 * @brief Listen for changes in the display size scaling factor information of the window. The callback function is
 *     triggered when any of the system display size scaling factor, system default display size scaling factor, or
 *     custom display size scaling factor of the screen where the window resides changes.
 *
 * @param windowId WindowId when window is created.
 * @param callback Callback used to return the result of density information.
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal. Possible cause:
 *             1. The window is not created or destroyed;
 *             2. This window state is abnormal.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 24
 */
int32_t OH_WindowManager_RegisterDensityInfoChangeCallback(int32_t windowId, 
    OH_WindowManager_DensityInfoCallback callback);

/**
 * @brief Unlisten for changes in the display size scaling factor information of the window. The callback function is
 *     triggered when any of the system display size scaling factor, system default display size scaling factor, or
 *     custom display size scaling factor of the screen where the window resides changes.
 *
 * @param windowId WindowId when window is created.
 * @param callback Callback used to return the result of density information.
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal. Possible cause:
 *             1. The window is not created or destroyed;
 *             2. This window state is abnormal.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 24
 */
int32_t OH_WindowManager_UnregisterDensityInfoChangeCallback(int32_t windowId, 
    OH_WindowManager_DensityInfoCallback callback);

/**
 * @brief 释放DensityInfo指针指向的内存空间
 *
 * @param info 显示当前窗口的DensityInfo。
 * @return 返回执行的状态代码。
 * {@link WS_OK}函数调用成功。
 * {@link WINDOWS_MANAGER_ERRORCODE_INCORRECT_PARAM}参数错误。可能原因：
 * 1.参数范围非法。
 * @since 24
 */
int32_t OH_WindowManager_DensityInfo_Release(const OH_WindowManager_DensityInfo* info);

#ifdef __cplusplus
}
#endif

#endif // OH_WINDOW_H
/** @} */