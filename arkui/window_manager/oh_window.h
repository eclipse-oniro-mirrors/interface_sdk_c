
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

#include <stdbool.h>
#include "stdint.h"

#include "oh_window_comm.h"
#include "multimodalinput/oh_input_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Sets whether to display the status bar in a window.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param enabled Whether to display the status bar. **true** to display, **false** otherwise.
 * @param enableAnimation Whether to enable the show/hide animation of the status bar. **true** to enable, **false**
 *     otherwise.
 * @return Returns the result code.
 *     {@link OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 15
 */
int32_t OH_WindowManager_SetWindowStatusBarEnabled(int32_t windowId, bool enabled, bool enableAnimation);

/**
 * @brief Sets the color of the status bar in a window.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param color Color to set, in ARGB format.
 * @return Returns the result code.
 *     {@link OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 15
 */
int32_t OH_WindowManager_SetWindowStatusBarColor(int32_t windowId, int32_t color);

/**
 * @brief Sets whether to display the navigation bar in a window.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param enabled Whether to display the navigation bar. **true** to display, **false** otherwise.
 * @param enableAnimation Whether to enable the show/hide animation of the navigation bar. **true** to enable, **false**
 *     otherwise.
 * @return Returns the result code.
 *     {@link OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 15
 */
int32_t OH_WindowManager_SetWindowNavigationBarEnabled(int32_t windowId, bool enabled, bool enableAnimation);

/**
 * @brief Obtains the avoid area of a window.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param type Type of the avoid area.
 * @param avoidArea Pointer to the avoid area.
 * @return Returns the result code.
 *     {@link OK} the function call is successful, return avoid area ptr in avoidArea.
 *     {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} parameter error.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 15
 */
int32_t OH_WindowManager_GetWindowAvoidArea(
    int32_t windowId, WindowManager_AvoidAreaType type, WindowManager_AvoidArea* avoidArea);

/**
 * @brief Checks whether a window is displayed.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param isShow Pointer to the check result for whether the window is displayed. **true** if displayed, **false**
 *     otherwise.
 * @return Returns the result code.
 *     {@link OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} parameter error.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 * @since 15
 */
int32_t OH_WindowManager_IsWindowShown(int32_t windowId, bool* isShow);

/**
 * @brief Shows a window.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @return Returns the result code.
 *     {@link OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 15
 */
int32_t OH_WindowManager_ShowWindow(int32_t windowId);

/**
 * @brief Sets whether a window is touchable.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param isTouchable Whether the window is touchable. **true** if touchable, **false** otherwise.
 * @return Returns the result code.
 *     {@link OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 15
 */
int32_t OH_WindowManager_SetWindowTouchable(int32_t windowId, bool isTouchable);

/**
 * @brief Sets whether a window is focusable.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param isFocusable Whether the window is focusable. **true** if focusable, **false** otherwise.
 * @return Returns the result code.
 *     {@link OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 15
 */
int32_t OH_WindowManager_SetWindowFocusable(int32_t windowId, bool isFocusable);

/**
 * @brief Sets the background color of a window.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param color Pointer to the background color. The value is a string in hexadecimal RGB or ARGB color format.
 * @return Returns the result code.
 *     {@link OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} parameter error.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 * @since 15
 */
int32_t OH_WindowManager_SetWindowBackgroundColor(int32_t windowId, const char* color);

/**
 * @brief Sets the window brightness for the main window. The window brightness takes effect only when the window is in
 * the foreground and has focus.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param brightness Screen brightness. The value is a floating-point number in the range [0.0, 1.0] or is set to **-1.
 *     0**. The value **1.0** means the brightest, and **-1.0** means that the window brightness resets to the original
 *     brightness set through Control Panel.
 * @return Returns the result code.
 *     {@link OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} parameter error.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 15
 */
int32_t OH_WindowManager_SetWindowBrightness(int32_t windowId, float brightness);

/**
 * @brief Sets whether to always keep the screen on for a window.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param isKeepScreenOn Whether to always keep the screen on. **true** to always keep the screen on, **false**
 *     otherwise.
 * @return Returns the result code.
 *     {@link OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 15
 */
int32_t OH_WindowManager_SetWindowKeepScreenOn(int32_t windowId, bool isKeepScreenOn);

/**
 * @brief Sets whether to enable privacy mode for a window.
 *
 * @permission ohos.permission.PRIVACY_WINDOW
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param isPrivacy Whether to enable privacy mode. **true** to enable, **false** otherwise.
 * @return Returns the result code.
 *     {@link OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 *     {@link WINDOW_MANAGER_ERRORCODE_NO_PERMISSION} permission verification failed.
 * @since 15
 */
int32_t OH_WindowManager_SetWindowPrivacyMode(int32_t windowId, bool isPrivacy);

/**
 * @brief Obtains the properties of a window.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param windowProperties Pointer to the properties.
 * @return Returns the result code.
 *     {@link OK} the function call is successful, return window properties ptr in windowProperties.
 *     {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} parameter error.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 * @since 15
 */
int32_t OH_WindowManager_GetWindowProperties(
    int32_t windowId, WindowManager_WindowProperties* windowProperties);

/**
 * @brief Obtains the snapshot of a window.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 *     If the window ID is invalid or the window has been destroyed, you cannot obtain the window snapshot. To
 *     successfully obtain a snapshot, a valid window ID is required.
 *     You can obtain a valid window ID by calling the ArkTS API {@link getWindowProperties()} on the window object
 * @param pixelMap Pointer to the snapshot.
 * @return Returns the result code.
 *     {@link OK} the function call is successful, return pixel map ptr in pixelMap.
 *     {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} parameter error.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 15
 */
int32_t OH_WindowManager_Snapshot(int32_t windowId, OH_PixelmapNative* pixelMap);

/**
 * @brief Obtains the layout information array of all windows visible on a display. The layout information is arranged
 * based on the current window stacking order, and the topmost window in the hierarchy is at index 0 of the array.
 *
 * @param displayId ID of the display. You can obtain a valid display ID by calling the ArkTS API
 *     {@link getWindowProperties()} on the window object
 * @param windowLayoutInfoList Double pointer to the layout information array of all windows visible. This parameter is
 *     used as an output parameter.
 * @param windowLayoutInfoSize Pointer to the length of the layout information array. This parameter is used as an
 *     output parameter.
 * @return Returns the result code.
 *     {@link OK} the function call is successful, return Window layout info list.
 *     {@link WINDOW_MANAGER_ERRORCODE_INVALID_PARAM} parameter error.
 *     {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 17
 */
int32_t OH_WindowManager_GetAllWindowLayoutInfoList(int64_t displayId,
    WindowManager_Rect** windowLayoutInfoList, size_t* windowLayoutInfoSize);

/**
 * @brief Releases the memory occupied by a window layout information array.
 *
 * @param windowLayoutInfoList Pointer to the layout information array of all windows visible on the display. You can
 *     obtain the array pointer by calling {@link OH_WindowManager_GetAllWindowLayoutInfoList}.
 * @since 17
 */
void OH_WindowManager_ReleaseAllWindowLayoutInfoList(WindowManager_Rect* windowLayoutInfoList);

/**
 * @brief Injects a multimodal touch event into the target window. This function is limited to injecting events into
 * windows that belong to the same process. The injection does not affect window focus or stacking order, nor does it
 * start window dragging. The event is forwarded directly to ArkUI. This function must be called after the target
 * window has completed its UI loading.
 *
 * @param windowId Window ID. The default value is **0**. The value is an integer.
 * @param touchEvent Pointer to the multimodal touch event. For details, see {@link Input_TouchEvent}. The event is
 *     defined in **oh_input_manager.h**. Certain fields in this parameter have specific constraints. Specifically, **
 *     action** should be an integer in the range [0, 3]; **id**, **displayX**, **displayY** should
 *     be an integer greater than or equal to 0. If these constraints are not met, the function returns **
 *     WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL**, indicating that the window manager service is abnormal.
 * @param windowX X coordinate of the event relative to the target window. The value is an integer.
 * @param windowY Y coordinate of the event relative to the target window. The value is an integer.
 * @return Returns the result code.
 *     {@link OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 20
 */
int32_t OH_WindowManager_InjectTouchEvent(
    int32_t windowId, Input_TouchEvent* touchEvent, int32_t windowX, int32_t windowY);

/**
 * @brief Obtains the information about all main windows.
 *
 * @permission ohos.permission.CUSTOM_SCREEN_CAPTURE
 * @param infoList Double pointer to the main window information list. This parameter is used as an output parameter.
 * @param mainWindowInfoSize Pointer to the size of the main window information list. This parameter is used as an
 *     output parameter.
 * @return Returns the status code of the execution.
 *     {@link WS_OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_NO_PERMISSION} permission verification failed.
 *     {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 21
 */
int32_t OH_WindowManager_GetAllMainWindowInfo(
    WindowManager_MainWindowInfo** infoList, size_t* mainWindowInfoSize);

/**
 * @brief Releases the memory used by the main window information list.
 *
 * @param infoList Pointer to the main window information list.
 * @since 21
 */
void OH_WindowManager_ReleaseAllMainWindowInfo(WindowManager_MainWindowInfo* infoList);

/**
 * @brief Defines the callback used for receiving the main window screenshot list.
 *
 * @param snapshotPixelMapList Double pointer to the list of window screenshots.
 * @param snapshotListSize Size of the window screenshot list.
 * @since 21
 */
typedef void (*OH_WindowManager_WindowSnapshotCallback)(const OH_PixelmapNative** snapshotPixelMapList,
    size_t snapshotListSize);

/**
 * @brief Obtains the screenshots of one or more main windows specified by **windowId**.
 *
 * @permission ohos.permission.CUSTOM_SCREEN_CAPTURE
 * @param windowIdList Pointer to the main window ID list.
 * @param windowIdListSize Size of the main window ID list.
 * @param config Configuration for obtaining the window screenshot.
 * @param callback Callback used to return the lists of window screenshots, in the order of the provided window ID
 *     array.
 * @return Returns the status code of the execution.
 *     {@link WS_OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_NO_PERMISSION} permission verification failed.
 *     {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 21
 */
int32_t OH_WindowManager_GetMainWindowSnapshot(int32_t* windowIdList, size_t windowIdListSize,
    WindowManager_WindowSnapshotConfig config, OH_WindowManager_WindowSnapshotCallback callback);

/**
 * @brief Releases the memory used by the main window screenshot list.
 *
 * @param snapshotPixelMapList Pointer to the list of window screenshots.
 * @since 21
 */
void OH_WindowManager_ReleaseMainWindowSnapshot(const OH_PixelmapNative* snapshotPixelMapList);

/**
 * @brief Locks the mouse cursor within the specified window area and controls whether the cursor follows mouse
 * movements. It is only supported by the window that currently has focus, and the lock is automatically released when
 * the window loses focus.
 *
 * @permission ohos.permission.LOCK_WINDOW_CURSOR
 * @param windowId Window ID. The value is an integer.
 * @param isCursorFollowMovement Behavior of the mouse cursor when locked. If it is set to **true**, the cursor moves
 *     along with the mouse. If it is set to **false**, the cursor remains stationary and does not follow mouse
 *     movements.
 * @return Returns the status code of the execution.
 *     {@link WS_OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_NO_PERMISSION} permission verification failed.
 *     {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 22
 */
int32_t OH_WindowManager_LockCursor(int32_t windowId, bool isCursorFollowMovement);

/**
 * @brief Clears the mouse cursor mode previously set for the window.
 *
 * @permission ohos.permission.LOCK_WINDOW_CURSOR
 * @param windowId Window ID. The value is an integer.
 * @return Returns the status code of the execution.
 *     {@link WS_OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_NO_PERMISSION} permission verification failed.
 *     {@link WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED} capability not supported.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL} the window manager service works abnormally.
 * @since 22
 */
int32_t OH_WindowManager_UnlockCursor(int32_t windowId);

/**
 * @brief Check whether the current frame is the first frame.
 *
 * @param metrics Frame metrics data object.
 * @param isFirstDrawFrame This parameter is the return value of the function,
 *     indicating whether the current frame is the first frame.
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 26.0.0
 */
int32_t OH_WindowManager_FrameMetrics_IsFirstDrawFrame(
    const OH_WindowManager_FrameMetrics* metrics, bool* isFirstDrawFrame);

/**
 * @brief Get the time taken to process external input events in one frame.
 *
 * @param metrics Frame metrics data object.
 * @param duration This parameter is the return value of the function,
 *     indicating the time taken to process external input events in one frame, in nanoseconds.
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 26.0.0
 */
int32_t OH_WindowManager_FrameMetrics_GetInputHandlingDuration(
    const OH_WindowManager_FrameMetrics* metrics, uint64_t* duration);

/**
 * @brief Get the time taken for layout measurement in one frame.
 *
 * @param metrics Frame metrics data object.
 * @param duration This parameter is the return value of the function,
 *     indicating the time taken for layout measurement in one frame, in nanoseconds.
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 26.0.0
 */
int32_t OH_WindowManager_FrameMetrics_GetLayoutMeasureDuration(
    const OH_WindowManager_FrameMetrics* metrics, uint64_t* duration);

/**
 * @brief Get the start timestamp of the current frame.
 *
 * @param metrics Frame metrics data object.
 * @param timestamp This parameter is the return value of the function,
 *     indicating the start timestamp of the current frame, in nanoseconds.
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 26.0.0
 */
int32_t OH_WindowManager_FrameMetrics_GetVsyncTimestamp(
    const OH_WindowManager_FrameMetrics* metrics, uint64_t* timestamp);

/**
 * @brief Registers a callback for window frame metric change events.
 * This API depends on the loading of the window page content. That is, this API can be called only after the **
 * loadContent()** or **setUIContent()** API in ArkTS takes effect.
 * The callback is triggered only when the client UI content is redrawn (for example, page switching, interaction with
 * responsive components, or background color and opacity setting).
 *  To cancel the registration, call the {@link OH_WindowManager_UnregisterFrameMetricsMeasuredCallback} API.
 *
 * @param windowId Window ID.
 * @param callback Callback used to return the result.
 * @return Returns the status code of the execution.
 *     {@link WS_OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal. Possible cause:
 *     1. The window is not created or destroyed;
 *     2. This window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *     1. Invalid parameter range.
 * @since 26.0.0
 */
int32_t OH_WindowManager_RegisterFrameMetricsMeasuredCallback(int32_t windowId,
    OH_WindowManager_FrameMetricsMeasuredCallback callback);

/**
 * @brief Unregisters the callback for window frame metric change events.
 * This API depends on the loading of the window page content. That is, this API can be called only after the **
 * loadContent()** or **setUIContent()** API in ArkTS takes effect.
 *  To register such a callback, call the {@link OH_WindowManager_RegisterFrameMetricsMeasuredCallback} API.
 *
 * @param windowId Window ID.
 * @param callback Callback used to return the result.
 * @return Returns the status code of the execution.
 *     {@link WS_OK} the function call is successful.
 *     {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal. Possible cause:
 *     1. The window is not created or destroyed;
 *     2. This window state is abnormal.
 *     {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *     1. Invalid parameter range.
 * @since 26.0.0
 */
int32_t OH_WindowManager_UnregisterFrameMetricsMeasuredCallback(int32_t windowId,
    OH_WindowManager_FrameMetricsMeasuredCallback callback);

/**
 * @brief Gets the system default display size scaling factor of the screen where the window is located.
 *
 * @param info Display size scaling factor information for the current window.
 * @param density System default display size scaling factor
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 24
 */
int32_t OH_WindowManager_DensityInfo_GetDefaultDensity(const OH_WindowManager_DensityInfo* info,
    float* density);

/**
 * @brief Gets the system display size scaling factor of the screen where the window is located.
 *
 * @param info Display size scaling factor information for the current window.
 * @param density System display size scaling factor
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 24
 */
int32_t OH_WindowManager_DensityInfo_GetSystemDensity(const OH_WindowManager_DensityInfo* info,
    float* density);

/**
 * @brief Gets the custom display size scaling factor of the window.
 *
 * @param info Display size scaling factor information for the current window.
 * @param density Custom display size scaling factor of the window. A return value of -1 indicates that no custom
 *     display size scaling factor has been set, or it has been reset.
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 24
 */
int32_t OH_WindowManager_DensityInfo_GetCustomDensity(const OH_WindowManager_DensityInfo* info,
    float* density);

/**
 * @brief Get the system display size scaling factor, the system default display size scaling factor,
 *     and the custom display size scaling factor information of the screen where the current window is located.
 *
 * @param windowId WindowId when window is created.
 * @param info Display size scaling factor information for the current window.
 *     A return value of NULL means this interface is not supported on the current device.
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL} this window state is abnormal. Possible cause:
 *             1. The window is not created or destroyed;
 *             2. This window state is abnormal.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 24
 */
int32_t OH_WindowManager_GetDensityInfoCopy(int32_t windowId,
    const OH_WindowManager_DensityInfo** info);

/**
 * @brief Listen for changes in the display size scaling factor information of the window. The callback function is
 *     triggered when any of the system display size scaling factor, system default display size scaling factor, or
 *     custom display size scaling factor of the screen where the window resides changes.
 *     To unlisten for changes in the display size scaling factor information of the window, call
 *     OH_WindowManager_UnregisterDensityInfoChangeCallback.
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
 *     To listen for changes in the display size scaling factor information of the window, call
 *     OH_WindowManager_RegisterDensityInfoChangeCallback.
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
 * @brief Releases the memory occupied by DensityInfo.
 *
 * @param info Display size scaling factor information for the current window.
 * @return Returns the status code of the execution.
 *         {@link WS_OK} the function call is successful.
 *         {@link WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM} Parameter error. Possible cause:
 *             1. Invalid parameter range.
 * @since 24
 */
int32_t OH_WindowManager_DensityInfo_Release(const OH_WindowManager_DensityInfo* info);

#ifdef __cplusplus
}
#endif

#endif // OH_WINDOW_H
/** @} */