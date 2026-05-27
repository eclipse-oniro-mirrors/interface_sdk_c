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
 *
 * @brief Provides abilities of windowManager on the native side, such as key event
 * filtration.
 *
 * @since 12
 */

/**
 * @file oh_window_comm.h
 *
 * @brief The file declares the common enums and definitions of the window manager.
 *
 * @syscap SystemCapability.Window.SessionManager
 * @library libnative_window_manager.so
 * @kit ArkUI
 * @since 12
 */

#ifndef OH_WINDOW_COMM_H
#define OH_WINDOW_COMM_H
#include "stdint.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Describes the pixel image information.
 *
 * @since 15
 */
typedef struct OH_PixelmapNative;

/**
 * @brief 帧率指标数据对象。
 *
 * @since 26.0.0
 */
typedef struct OH_WindowManager_FrameMetrics OH_WindowManager_FrameMetrics;

/**
 * @brief 帧率指标回调类型。
 *
 * @since 26.0.0
 */
typedef void (*OH_WindowManager_FrameMetricsMeasuredCallback)(
    int32_t windowId, const OH_WindowManager_FrameMetrics* metrics);

/**
 * @brief Window density information, including the system display size scaling factor, system default display size
 *     scaling factor, and custom display size scaling factor of the screen where the window is located.
 *
 * @since 24
 */
typedef struct OH_WindowManager_DensityInfo OH_WindowManager_DensityInfo;

/**
 * @brief density信息回调类型。
 *
 * @since 24
 */
typedef void (*OH_WindowManager_DensityInfoCallback)(int32_t windowId, const OH_WindowManager_DensityInfo* info);

/**
 * @brief 窗口管理接口返回状态码枚举。
 *
 * @since 12
 */
typedef enum {
    /**
     * 成功。
     */
    OK = 0,

    /**
     * 无权限。
     * @since 15
     */
    WINDOW_MANAGER_ERRORCODE_NO_PERMISSION = 201,

    /**
     * 非法参数。
     * @since 15
     */
    WINDOW_MANAGER_ERRORCODE_INVALID_PARAM = 401,

    /**
     * 设备不支持。
     * @since 15
     */
    WINDOW_MANAGER_ERRORCODE_DEVICE_NOT_SUPPORTED = 801,

    /**
     * 非法窗口ID。
     */
    INVAILD_WINDOW_ID = 1000,

    /**
     * 服务异常。
     */
    SERVICE_ERROR = 2000,

    /**
     * 窗口状态异常。
     * @since 15
     */
    WINDOW_MANAGER_ERRORCODE_STATE_ABNORMAL = 1300002,

    /**
     * 窗口管理器服务异常。
     * @since 15
     */
    WINDOW_MANAGER_ERRORCODE_SYSTEM_ABNORMAL = 1300003,

    /**
     * 画中画销毁失败。
     * @since 20
     */
    WINDOW_MANAGER_ERRORCODE_PIP_DESTROY_FAILED = 1300011,

    /**
     * 画中画状态异常。
     * @since 20
     */
    WINDOW_MANAGER_ERRORCODE_PIP_STATE_ABNORMAL = 1300012,

    /**
     * 画中画创建失败。
     * @since 20
     */
    WINDOW_MANAGER_ERRORCODE_PIP_CREATE_FAILED = 1300013,

    /**
     * 画中画内部错误。可能原因：<br/>1.画中画依赖的窗口异常，可能窗口为空；2.画中画控制器异常。
     * @since 20
     */
    WINDOW_MANAGER_ERRORCODE_PIP_INTERNAL_ERROR = 1300014,

    /**
     * 画中画重复操作。
     * @since 20
     */
    WINDOW_MANAGER_ERRORCODE_PIP_REPEATED_OPERATION = 1300015,

    /**
     * 参数错误。可能原因：<br/>1.参数取值范围非法；2.参数数量非法；3.参数类型非法。
     * @since 20
     */
    WINDOW_MANAGER_ERRORCODE_INCORRECT_PARAM = 1300016
} WindowManager_ErrorCode;

/**
 * @brief 避让区域枚举类型。
 *
 * @since 15
 */
typedef enum {
    /**
     * 系统避让区域。
     */
    WINDOW_MANAGER_AVOID_AREA_TYPE_SYSTEM = 0,

    /**
     * 刘海屏避让。
     */
    WINDOW_MANAGER_AVOID_AREA_TYPE_CUTOUT = 1,

    /**
     * 系统手势区域。
     */
    WINDOW_MANAGER_AVOID_AREA_TYPE_SYSTEM_GESTURE = 2,

    /**
     * 键盘区域。
     */
    WINDOW_MANAGER_AVOID_AREA_TYPE_KEYBOARD = 3,

    /**
     * 导航条区域。
     */
    WINDOW_MANAGER_AVOID_AREA_TYPE_NAVIGATION_INDICATOR = 4
} WindowManager_AvoidAreaType;

/**
 * @brief 窗口类型。
 *
 * @since 15
 */
typedef enum {
    /**
     * 子窗口。
     */
    WINDOW_MANAGER_WINDOW_TYPE_APP = 0,

    /**
     * 主窗口。
     */
    WINDOW_MANAGER_WINDOW_TYPE_MAIN = 1,

    /**
     * 全局悬浮窗口。
     */
    WINDOW_MANAGER_WINDOW_TYPE_FLOAT = 8,

    /**
     * 对话窗口。
     */
    WINDOW_MANAGER_WINDOW_TYPE_DIALOG = 16
} WindowManager_WindowType;

/**
 * @brief The struct describes the window rectangle, including the window position, width, and height.
 *
 * @since 15
 */
typedef struct {
    /**
     * X coordinate of the window, in px. The value is an integer.
     */
    int32_t posX;
    /**
     * Y coordinate of the window, in px. The value is an integer.
     */
    int32_t posY;
    /**
     * Window width, in px. The value is an integer.
     */
    uint32_t width;
    /**
     * Window height, in px. The value is an integer.
     */
    uint32_t height;
} WindowManager_Rect;

/**
 * @brief Describes the configuration of the main window screenshot.
 *
 * @since 21
 */
typedef struct {
    /**
     * Whether the existing screenshot of the main window should be used. The default value is **true**. When it is set
     * to **true**, the system uses the existing screenshot of the main window, or captures the latest screenshot if no
     * existing screenshot is saved. When it is set to **false**, the system captures the latest screenshot of the main
     * window.
     */
    bool useCache;
} WindowManager_WindowSnapshotConfig;

/**
 * @brief The struct describes the main window information.
 *
 * @since 21
 */
typedef struct {
    /**
     * ID of the display to which the main window belongs.
     */
    uint64_t displayId;
    /**
     * Window ID. The default value is **0**, and the value is an integer.
     */
    int32_t windowId;
    /**
     * Foreground/Background status of the main window. **true** if the main window is in the foreground, **false**
     * otherwise.
     */
    bool showing;
    /**
     * Pointer to the task name of the main window.
     */
    const char* label;
} WindowManager_MainWindowInfo;

/**
 * @brief The struct describes the window properties.
 *
 * @since 15
*/
typedef struct {
    /**
     * Position and size of the window.
     */
    WindowManager_Rect windowRect;
    /**
     * Size of the drawable area within the window.
     */
    WindowManager_Rect drawableRect;
    /**
     * Window type.
     */
    WindowManager_WindowType type;
    /**
     * Whether the window is in full-screen mode. The default value is **false**. **true** if in full-screen mode, **
     * false** otherwise.
     */
    bool isFullScreen;
    /**
     * Whether the window layout is immersive. The default value is **false**. **true** if immersive, **false**
     * otherwise.
     */
    bool isLayoutFullScreen;
    /**
     * Whether the window is focusable. The default value is **true**. **true** if focusable, **false** otherwise.
     */
    bool focusable;
    /**
     * Whether the window is touchable. The default value is **true**. **true** if touchable, **false** otherwise.
     */
    bool touchable;
    /**
     * Screen brightness of the window. The value is a floating-point number in the range [0.0, 1.0] or is set to **-1.
     * 0**, where **1.0** indicates the brightest, and **-1.0** is the default brightness.
     */
    float brightness;
    /**
     * Whether the screen is steady on. The default value is **false**. **true** if steady on, **false** otherwise.
     */
    bool isKeepScreenOn;
    /**
     * Whether privacy mode is enabled for the window. The default value is **false**. **true** if enabled, **false**
     * otherwise.
     */
    bool isPrivacyMode;
    /**
     * Whether the window is transparent. The default value is **false**. **true** if transparent, **false** otherwise.
     */
    bool isTransparent;
    /**
     * Window ID. The default value is **0**, and the value is an integer.
     */
    uint32_t id;
    /**
     * ID of the screen where the window is located. By default, the ID of the primary screen is returned. The value is
     * an integer.
     */
    uint32_t displayId;
} WindowManager_WindowProperties;

/**
 * @brief The struct describes the avoid area.
 *
 * @since 15
 */
typedef struct {
    /**
     * Top rectangle of the avoid area.
     */
    WindowManager_Rect topRect;
    /**
     * Left rectangle of the avoid area.
     */
    WindowManager_Rect leftRect;
    /**
     * Right rectangle of the avoid area.
     */
    WindowManager_Rect rightRect;
    /**
     * Bottom rectangle of the avoid area.
     */
    WindowManager_Rect bottomRect;
} WindowManager_AvoidArea;
#ifdef __cplusplus
}
#endif
#endif // OH_WINDOW_COMM_H

/** @} */