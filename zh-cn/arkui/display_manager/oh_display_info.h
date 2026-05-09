
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
 * @brief ��Ļ˳ʱ�����ת�Ƕȡ�
 * 
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * ������Ļ˳ʱ����ת�Ƕ�0�ȡ�
     */
    DISPLAY_MANAGER_ROTATION_0 = 0,

    /**
     * ������Ļ˳ʱ����ת�Ƕ�90�ȡ�
     */
    DISPLAY_MANAGER_ROTATION_90 = 1,

    /**
     * ������Ļ˳ʱ����ת�Ƕ�180�ȡ�
     */
    DISPLAY_MANAGER_ROTATION_180 = 2,

    /**
     * ������Ļ˳ʱ����ת�Ƕ�270�ȡ�
     */
    DISPLAY_MANAGER_ROTATION_270 = 3
} NativeDisplayManager_Rotation;

/**
 * @brief ��Ļ����ת����
 * 
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * ��ʾ�豸��ǰ��������ʽ��ʾ��
     */
    DISPLAY_MANAGER_PORTRAIT = 0,

    /**
     * ��ʾ�豸��ǰ�Ժ�����ʽ��ʾ��
     */
    DISPLAY_MANAGER_LANDSCAPE = 1,

    /**
     * ��ʾ�豸��ǰ�Է���������ʽ��ʾ��
     */
    DISPLAY_MANAGER_PORTRAIT_INVERTED = 2,

    /**
     * ��ʾ�豸��ǰ�Է��������ʽ��ʾ��
     */
    DISPLAY_MANAGER_LANDSCAPE_INVERTED = 3,

    /**
     * ��ʾ��ʾδʶ����Ļ����
     */
    DISPLAY_MANAGER_UNKNOWN
} NativeDisplayManager_Orientation;

/**
 * @brief ��Ļ�����ӿڷ���״̬��ö�١�
 * 
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * �ɹ���
     */
    DISPLAY_MANAGER_OK = 0,

    /**
     * Ȩ��У��ʧ�ܣ�Ӧ����Ȩ��ʹ�ø�API����Ҫ����Ȩ�ޡ�
     */
    DISPLAY_MANAGER_ERROR_NO_PERMISSION = 201,

    /**
     * Ȩ��У��ʧ�ܣ���ϵͳӦ��ʹ����ϵͳAPI��
     */
    DISPLAY_MANAGER_ERROR_NOT_SYSTEM_APP = 202,

    /**
     * �������ʧ�ܡ�
     */
    DISPLAY_MANAGER_ERROR_INVALID_PARAM = 401,

    /**
     * ���豸��֧�ִ�API��
     */
    DISPLAY_MANAGER_ERROR_DEVICE_NOT_SUPPORTED = 801,

    /**
     * ��������ʾ�豸��Ч��
     */
    DISPLAY_MANAGER_ERROR_INVALID_SCREEN = 1400001,

    /**
     * ��ǰ���������޲���Ȩ�ޡ�
     */
    DISPLAY_MANAGER_ERROR_INVALID_CALL = 1400002,

    /**
     * ϵͳ�������쳣��
     */
    DISPLAY_MANAGER_ERROR_SYSTEM_ABNORMAL = 1400003,

    /**
     * �Ƿ�������
     * @since 20
     */
    DISPLAY_MANAGER_ERROR_ILLEGAL_PARAM = 1400004
} NativeDisplayManager_ErrorCode;

/**
 * @brief ���۵��豸����ʾģʽö�١�
 * 
 * @since 12
 * @version 1.0
 */
typedef enum {
    /**
     * ��ʾ�豸��ǰ�۵���ʾģʽδ֪��
     */
    DISPLAY_MANAGER_FOLD_DISPLAY_MODE_UNKNOWN = 0,

    /**
     * ��ʾ�豸��ǰȫ����ʾ��
     */
    DISPLAY_MANAGER_FOLD_DISPLAY_MODE_FULL = 1,

    /**
     * ��ʾ�豸��ǰ����Ļ��ʾ��
     */
    DISPLAY_MANAGER_FOLD_DISPLAY_MODE_MAIN = 2,

    /**
     * ��ʾ�豸��ǰ����Ļ��ʾ��
     */
    DISPLAY_MANAGER_FOLD_DISPLAY_MODE_SUB = 3,

    /**
     * ��ʾ�豸��ǰ˫��Эͬ��ʾ��
     */
    DISPLAY_MANAGER_FOLD_DISPLAY_MODE_COORDINATION = 4
} NativeDisplayManager_FoldDisplayMode;

/**
 * @brief ��������
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
 * @brief �ٲ������沿����ʾ����
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
 * @brief �ڿ��������������ٲ����Ȳ�������Ļ������Ϣ��
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
 * @brief ��ʾ�豸��״̬ö�١�
 * 
 * @since 14
 * @version 1.0
 */
typedef enum {
    /**
     * ��ʾ��ʾ�豸״̬δ֪��
     */
    DISPLAY_MANAGER_DISPLAY_STATE_UNKNOWN = 0,

    /**
     * ��ʾ��ʾ�豸״̬Ϊ�رա�
     */
    DISPLAY_MANAGER_DISPLAY_STATE_OFF = 1,

    /**
     * ��ʾ��ʾ�豸״̬Ϊ������
     */
    DISPLAY_MANAGER_DISPLAY_STATE_ON = 2,

    /**
     * ��ʾ��ʾ�豸Ϊ�͵��ģʽ��
     */
    DISPLAY_MANAGER_DISPLAY_STATE_DOZE = 3,

    /**
     * ��ʾ��ʾ�豸Ϊ˯��ģʽ��CPUΪ����״̬��
     */
    DISPLAY_MANAGER_DISPLAY_STATE_DOZE_SUSPEND = 4,

    /**
     * ��ʾ��ʾ�豸ΪVRģʽ��
     */
    DISPLAY_MANAGER_DISPLAY_STATE_VR = 5,

    /**
     * ��ʾ��ʾ�豸Ϊ����״̬��CPUΪ����״̬��
     */
    DISPLAY_MANAGER_DISPLAY_STATE_ON_SUSPEND = 6
} NativeDisplayManager_DisplayState;

/**
 * @brief �豸����ʾģʽö�١�
 * 
 * @since 20
 * @version 1.0
 */
typedef enum {
    /**
     * ��ʾ�豸��ǰδʹ�á�
     */
    DISPLAY_SOURCE_MODE_NONE = 0,

    /**
     * ��ʾ�豸��ǰΪ������
     */
    DISPLAY_SOURCE_MODE_MAIN = 1,

    /**
     * ��ʾ�豸��ǰΪ������ʾģʽ��
     */
    DISPLAY_SOURCE_MODE_MIRROR = 2,

    /**
     * ��ʾ�豸��ǰΪ��չ��ʾģʽ��
     */
    DISPLAY_SOURCE_MODE_EXTEND = 3,

    /**
     * ��ʾ�豸��ǰΪ��Դ��ʾģʽ��
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