
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file oh_display_info.h
 *
 * @brief The file declares the common enums and definitions of the display.
 * 
 * @kit ArkUI
 * @library libnative_display_manager.so
 * @syscap SystemCapability.WindowManager.WindowManager.Core
 * @since 12
 * @version 1.0
 */

/**
 * @addtogroup OH_DisplayManager
 * @{
 *
 * @brief Defines the data structures for the C APIs of the display module.
 *
 * @syscap SystemCapability.WindowManager.WindowManager.Core
 * @since 12
 * @version 1.0
 */
#ifndef OH_NATIVE_DISPLAY_INFO_H
#define OH_NATIVE_DISPLAY_INFO_H
#include "stdint.h"
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Maximum length of a display name.
 * 
 * @since 14
 */
#define OH_DISPLAY_NAME_LENGTH 32

/**
 * @brief 屏幕顺时针的旋转角度。
 * 
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 代表屏幕顺时针旋转角度0度。
     */
    DISPLAY_MANAGER_ROTATION_0 = 0,

    /**
     * 代表屏幕顺时针旋转角度90度。
     */
    DISPLAY_MANAGER_ROTATION_90 = 1,

    /**
     * 代表屏幕顺时针旋转角度180度。
     */
    DISPLAY_MANAGER_ROTATION_180 = 2,

    /**
     * 代表屏幕顺时针旋转角度270度。
     */
    DISPLAY_MANAGER_ROTATION_270 = 3
} NativeDisplayManager_Rotation;

/**
 * @brief 屏幕的旋转方向。
 * 
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 表示设备当前以竖屏方式显示。
     */
    DISPLAY_MANAGER_PORTRAIT = 0,

    /**
     * 表示设备当前以横屏方式显示。
     */
    DISPLAY_MANAGER_LANDSCAPE = 1,

    /**
     * 表示设备当前以反向竖屏方式显示。
     */
    DISPLAY_MANAGER_PORTRAIT_INVERTED = 2,

    /**
     * 表示设备当前以反向横屏方式显示。
     */
    DISPLAY_MANAGER_LANDSCAPE_INVERTED = 3,

    /**
     * 表示显示未识别屏幕方向。
     */
    DISPLAY_MANAGER_UNKNOWN
} NativeDisplayManager_Orientation;

/**
 * @brief 屏幕管理接口返回状态码枚举。
 * 
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 成功。
     */
    DISPLAY_MANAGER_OK = 0,

    /**
     * 权限校验失败，应用无权限使用该API，需要申请权限。
     */
    DISPLAY_MANAGER_ERROR_NO_PERMISSION = 201,

    /**
     * 权限校验失败，非系统应用使用了系统API。
     */
    DISPLAY_MANAGER_ERROR_NOT_SYSTEM_APP = 202,

    /**
     * 参数检查失败。
     */
    DISPLAY_MANAGER_ERROR_INVALID_PARAM = 401,

    /**
     * 该设备不支持此API。
     */
    DISPLAY_MANAGER_ERROR_DEVICE_NOT_SUPPORTED = 801,

    /**
     * 操作的显示设备无效。
     */
    DISPLAY_MANAGER_ERROR_INVALID_SCREEN = 1400001,

    /**
     * 当前操作对象无操作权限。
     */
    DISPLAY_MANAGER_ERROR_INVALID_CALL = 1400002,

    /**
     * 系统服务工作异常。
     */
    DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL = 1400003,

    /**
     * 非法参数。
     * @since 20
     */
    DISPLAY_MANAGER_ERROR_ILLEGAL_PARAM = 1400004
} NativeDisplayManager_ErrorCode;

/**
 * @brief 可折叠设备的显示模式枚举。
 * 
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * 表示设备当前折叠显示模式未知。
     */
    DISPLAY_MANAGER_FOLD_DISPLAY_MODE_UNKNOWN = 0,

    /**
     * 表示设备当前全屏显示。
     */
    DISPLAY_MANAGER_FOLD_DISPLAY_MODE_FULL = 1,

    /**
     * 表示设备当前主屏幕显示。
     */
    DISPLAY_MANAGER_FOLD_DISPLAY_MODE_MAIN = 2,

    /**
     * 表示设备当前子屏幕显示。
     */
    DISPLAY_MANAGER_FOLD_DISPLAY_MODE_SUB = 3,

    /**
     * 表示设备当前双屏协同显示。
     */
    DISPLAY_MANAGER_FOLD_DISPLAY_MODE_COORDINATION = 4
} NativeDisplayManager_FoldDisplayMode;

/**
 * @brief 矩形区域。
 * 
 * @since 12
 * @version 1.0
 */
typedef struct {
    /* rect left */
    int32_t left;
    /* rect top */
    int32_t top;
    /* rect width */
    uint32_t width;
    /* rect height */
    uint32_t height;
} NativeDisplayManager_Rect;

/**
 * @brief 瀑布屏曲面部分显示区域。
 * 
 * @since 12
 * @version 1.0
 */
typedef struct {
    /* waterfall left rect */
    NativeDisplayManager_Rect left;

    /* waterfall top rect */
    NativeDisplayManager_Rect top;

    /* waterfall right rect */
    NativeDisplayManager_Rect right;

    /* waterfall bottom rect */
    NativeDisplayManager_Rect bottom;
} NativeDisplayManager_WaterfallDisplayAreaRects;

/**
 * @brief 挖孔屏、刘海屏、瀑布屏等不可用屏幕区域信息。
 * 
 * @since 12
 * @version 1.0
 */
typedef struct {
    /* boundingRects length */
    int32_t boundingRectsLength;

    /* boundingRects info pointer */
    NativeDisplayManager_Rect *boundingRects;

    /* waterfallDisplayAreaRects info */
    NativeDisplayManager_WaterfallDisplayAreaRects waterfallDisplayAreaRects;
} NativeDisplayManager_CutoutInfo;

/**
 * @brief 显示设备的状态枚举。
 * 
 * @since 14
 * @version 1.0
 */
typedef enum {
    /**
     * 表示显示设备状态未知。
     */
    DISPLAY_MANAGER_DISPLAY_STATE_UNKNOWN = 0,

    /**
     * 表示显示设备状态为关闭。
     */
    DISPLAY_MANAGER_DISPLAY_STATE_OFF = 1,

    /**
     * 表示显示设备状态为开启。
     */
    DISPLAY_MANAGER_DISPLAY_STATE_ON = 2,

    /**
     * 表示显示设备为低电耗模式。
     */
    DISPLAY_MANAGER_DISPLAY_STATE_DOZE = 3,

    /**
     * 表示显示设备为睡眠模式，CPU为挂起状态。
     */
    DISPLAY_MANAGER_DISPLAY_STATE_DOZE_SUSPEND = 4,

    /**
     * 表示显示设备为VR模式。
     */
    DISPLAY_MANAGER_DISPLAY_STATE_VR = 5,

    /**
     * 表示显示设备为开启状态，CPU为挂起状态。
     */
    DISPLAY_MANAGER_DISPLAY_STATE_ON_SUSPEND = 6
} NativeDisplayManager_DisplayState;

/**
 * @brief 设备的显示模式枚举。
 * 
 * @since 20
 * @version 1.0
 */
typedef enum {
    /**
     * 表示设备当前未使用。
     */
    DISPLAY_SOURCE_MODE_NONE = 0,

    /**
     * 表示设备当前为主屏。
     */
    DISPLAY_SOURCE_MODE_MAIN = 1,

    /**
     * 表示设备当前为镜像显示模式。
     */
    DISPLAY_SOURCE_MODE_MIRROR = 2,

    /**
     * 表示设备当前为扩展显示模式。
     */
    DISPLAY_SOURCE_MODE_EXTEND = 3,

    /**
     * 表示设备当前为异源显示模式。
     */
    DISPLAY_SOURCE_MODE_ALONE = 4
} NativeDisplayManager_SourceMode;

/**
 * @brief The struct describes all the HDR formats supported by a display.
 * 
 * @since 14
 * @version 1.0
 */
typedef struct {
    /**
     * Number of HDR formats supported by the display.
     */
    uint32_t hdrFormatLength;

    /**
     * Data of the HDR formats supported by the display.
     */
    uint32_t *hdrFormats;
} NativeDisplayManager_DisplayHdrFormat;

/**
 * @brief The struct describes all the color spaces supported by a display.
 * 
 * @since 14
 * @version 1.0
 */
typedef struct {
    /**
     * Number of color spaces supported by the display.
     */
    uint32_t colorSpaceLength;

    /**
     * Data of the color spaces supported by the display.
     */
    uint32_t *colorSpaces;
} NativeDisplayManager_DisplayColorSpace;

/**
 * @brief The struct describes the information about a display.
 * 
 * @since 14
 * @version 1.0
 */
typedef struct {
    /**
     * ID of the display. The value must be a non-negative integer.
     */
    uint32_t id;

    /** display name */
    char name[OH_DISPLAY_NAME_LENGTH + 1];

    /**
     * Whether the display is active. **true** if active, **false** otherwise.
     */
    bool isAlive;

    /**
     * Width of the display, in px. The value must be a non-negative integer.
     */
    int32_t width;

    /**
     * Height of the display, in px. The value must be a non-negative integer.
     */
    int32_t height;

    /**
     * Physical width of the display, in px. The value must be a non-negative integer.
     */
    int32_t physicalWidth;

    /**
     * Physical height of the display, in px. The value must be a non-negative integer.
     */
    int32_t physicalHeight;

    /**
     * Refresh rate of the display, in Hz. The value must be a non-negative integer.
     */
    uint32_t refreshRate;

    /**
     * Width of the available area on a 2-in-1 device, in px. The value must be a non-negative integer.
     */
    uint32_t availableWidth;

    /**
     * Height of the available area on a 2-in-1 device, in px. The value is an integer greater than 0.
     */
    uint32_t availableHeight;

    /**
     * Physical pixel density of the display, that is, the number of pixels per inch. The value must be a floating-
     * point number greater than 0. The unit is px. Generally, the value is **160.0** or **480.0**. The actual value
     * depends on the optional values provided by the device in use.
     */
    float densityDPI;

    /**
     * Logical pixel density of the display, which is the scaling coefficient between physical pixels and logical
     * pixels. The value is a floating-point number greater than 0 and is restricted by the range of **densityDPI**.
     * The value range is [0.5, 4.0]. Generally, the value is **1.0** or **3.0**. The actual value depends on the
     * density DPI provided by the device in use.
     */
    float densityPixels;

    /**
     * Scaling factor for fonts displayed on the display. The value must be a floating-point number greater than 0.
     * Generally, the value is the same as that of **densityPixels**.
     */
    float scaledDensity;

    /**
     * Exact physical pixels per inch of the display in the X dimension. The value must be a floating-point number
     * greater than 0.
     */
    float xDPI;

    /**
     * Exact physical pixels per inch of the display in the Y dimension. The value must be a floating-point number
     * greater than 0.
     */
    float yDPI;

    /**
     * Clockwise rotation angle of the display.
     */
    NativeDisplayManager_Rotation rotation;

    /**
     * State of the display.
     */
    NativeDisplayManager_DisplayState state;

    /**
     * Orientation of the display.
     */
    NativeDisplayManager_Orientation orientation;

    /**
     * All the HDR formats supported by the display.
     */
    NativeDisplayManager_DisplayHdrFormat *hdrFormat;

    /**
     * All the color spaces supported by the display.
     */
    NativeDisplayManager_DisplayColorSpace *colorSpace;
} NativeDisplayManager_DisplayInfo;

/**
 * @brief The struct describes the information about displays of a device with multiple screens.
 * 
 * @since 14
 * @version 1.0
 */
typedef struct {
    /**
     * Number of displays of a device with multiple screens.
     */
    uint32_t displaysLength;

    /**
     * An array of NativeDisplayManager_DisplayInfo structs, each containing information about a display.
     */
    NativeDisplayManager_DisplayInfo *displaysInfo;
} NativeDisplayManager_DisplaysInfo;
#ifdef __cplusplus
}
#endif

/** @} */
#endif // OH_NATIVE_DISPLAY_INFO_H