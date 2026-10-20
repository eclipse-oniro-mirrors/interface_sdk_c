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
 * @addtogroup resourcemanager
 * @{
 *
 * @brief Through the `resourcemanager` module, you can obtain application resources or system resources by resource ID
 * or resource name at the Native layer, enabling resource adaptation for multilingual, multi-device, and multi-screen-
 * density scenarios. Specifically:
 * <br>- Obtaining basic type resources: Obtain basic type resources such as color values (in ARGB format), integers,
 * floating-point numbers, and boolean values.
 * <br>- Obtaining string resources: Obtain plain strings, formatted strings (supporting %d, %s, and %f placeholders),
 * string arrays, and plural strings.
 * <br>- Obtaining media resources: Obtain raw binary data or Base64 encoding of media resources.
 * <br>- Resource overlay: Dynamically load and remove overlay resources at runtime to implement theme switching or
 * resource overlay.
 * <br>This module depends on the `rawfile` module. You must first obtain a **NativeResourceManager** object through
 * the `rawfile` module.
 *
 * @since 12
 */
/**
 * @file resmgr_common.h
 *
 * @brief Provides the enumeration and structure definitions required by the `resourcemanager` module.
 * <br>This header file defines enumerations such as error codes, screen orientations, color modes, device types, and
 * screen densities, as well as the device configuration structure, providing data type support for the resource
 * retrieval functions in `ohresmgr.h`.
 *
 * @syscap SystemCapability.Global.ResourceManager
 * @library libohresmgr.so
 * @kit LocalizationKit
 * @since 12
 */
#ifndef GLOBAL_RESMGR_COMMON_H
#define GLOBAL_RESMGR_COMMON_H

# include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates resource manager error codes.
 *
 * @since 12
 */
typedef enum ResourceManager_ErrorCode {
    /**
     * Operation successful.
     */
    SUCCESS = 0,
    /**
     * Invalid input parameter.
     */
    ERROR_CODE_INVALID_INPUT_PARAMETER = 401,
    /**
     * Invalid resource ID.
     */
    ERROR_CODE_RES_ID_NOT_FOUND = 9001001,
    /**
     * No matching resource found based on the resource ID.
     */
    ERROR_CODE_RES_NOT_FOUND_BY_ID = 9001002,
    /**
     * Invalid resource name.
     */
    ERROR_CODE_RES_NAME_NOT_FOUND = 9001003,
    /**
     * No matching resource found based on the resource name.
     */
    ERROR_CODE_RES_NOT_FOUND_BY_NAME = 9001004,
    /**
     * Invalid relative path.
     */
    ERROR_CODE_RES_PATH_INVALID = 9001005,
    /**
     * Circular reference exists in the resource.
     */
    ERROR_CODE_RES_REF_TOO_MUCH = 9001006,
    /**
     * Failed to format the resource obtained based on the resource ID.
     */
    ERROR_CODE_RES_ID_FORMAT_ERROR = 9001007,
    /**
     * Failed to format the resource obtained based on the resource name.
     */
    ERROR_CODE_RES_NAME_FORMAT_ERROR = 9001008,
    /**
     * Failed to access system resources.
     */
    ERROR_CODE_SYSTEM_RES_MANAGER_GET_FAILED = 9001009,
    /**
     * Invalid overlay path.
     */
    ERROR_CODE_OVERLAY_RES_PATH_INVALID = 9001010,
    /**
     * A memory overflow occurs.
     */
    ERROR_CODE_OUT_OF_MEMORY = 9001100,
} ResourceManager_ErrorCode;

/**
 * @brief Enumerates screen orientations.
 *
 * @since 12
 */
typedef enum ResourceManager_Direction {
    /**
     * Portrait orientation.
     */
    DIRECTION_VERTICAL = 0,
    /**
     * Landscape orientation.
     */
    DIRECTION_HORIZONTAL = 1,
} ResourceManager_Direction;

/**
 * @brief Enumerates color modes.
 *
 * @since 12
 */
typedef enum ResourceManager_ColorMode {
    /**
     * Dark mode.
     */
    COLOR_MODE_DARK = 0,
    /**
     * Light mode.
     */
    COLOR_MODE_LIGHT = 1,
} ResourceManager_ColorMode;

/**
 * @brief Enumerates device types.
 *
 * @since 12
 */
typedef enum ResourceManager_DeviceType {
    /**
     * Smartphone.
     */
    DEVICE_TYPE_PHONE = 0X00,
    /**
     * Tablet.
     */
    DEVICE_TYPE_TABLET = 0x01,
    /**
     * Car head unit.
     */
    DEVICE_TYPE_CAR = 0x02,
    /**
     * PC.
     */
    DEVICE_TYPE_PC = 0x03,
    /**
     * Smart screen.
     */
    DEVICE_TYPE_TV = 0x04,
    /**
     * Wearable.
     */
    DEVICE_TYPE_WEARABLE = 0x06,
    /**
     * 2-in-1 device.
     */
    DEVICE_TYPE_2IN1 = 0x07,
} ResourceManager_DeviceType;

/**
 * @brief Enumerates the screen density types.
 *
 * @since 12
 */
typedef enum ScreenDensity {
    /**
     * Screen density with small-scale dots per inch (SDPI).
     */
    SCREEN_SDPI = 120,
    /**
     * Screen density with medium-scale dots per inch (MDPI).
     */
    SCREEN_MDPI = 160,
    /**
     * Screen density with large-scale dots per inch (LDPI).
     */
    SCREEN_LDPI = 240,
    /**
     * Screen density with extra-large-scale dots per inch (XLDPI).
     */
    SCREEN_XLDPI = 320,
    /**
     * Screen density with extra-extra-large-scale dots per inch (XXLDPI).
     */
    SCREEN_XXLDPI = 480,
    /**
     * Screen density with extra-extra-extra-large-scale dots per inch (XXXLDPI).
     */
    SCREEN_XXXLDPI = 640,
} ScreenDensity;

/**
 * @brief Structure of the device status.
 *
 * @since 12
 */
typedef struct ResourceManager_Configuration {
    /**
     * Screen orientation.
     */
    ResourceManager_Direction direction;
    /**
     * Language, script, country or region, for example, `zh_Hans_CN`.
     */
    char* locale;
    /**
     * Device type.
     */
    ResourceManager_DeviceType deviceType;
    /**
     * Screen density.
     */
    ScreenDensity screenDensity;
    /**
     * Color mode.
     */
    ResourceManager_ColorMode colorMode;
    /**
     * Mobile country code (MCC).
     */
    uint32_t mcc;
    /**
     * Mobile network code (MNC).
     */
    uint32_t mnc;
    /**
     * Reserved attributes.
     */
    uint32_t reserved[20];
} ResourceManager_Configuration;
#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_RESMGR_COMMON_H