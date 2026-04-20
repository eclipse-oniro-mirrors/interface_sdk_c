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
 * @brief Provides the c interface to obtain resources, and relies on librawfile.z.so when used.
 *
 * @since 12
 */
/**
 * @file resmgr_common.h
 *
 * @brief Provides the enum types and structures for resource manager APIs.
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
     * Resource referenced cyclically.
     */
    ERROR_CODE_RES_REF_TOO_MUCH = 9001006,
    /**
     * Failed to format the resource obtained based on the specified resource ID.
     */
    ERROR_CODE_RES_ID_FORMAT_ERROR = 9001007,
    /**
     * Failed to format the resource obtained based on the specified resource name.
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
     * Vertical direction.
     */
    DIRECTION_VERTICAL = 0,
    /**
     * Horizontal direction.
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
     * Smartphone
     */
    DEVICE_TYPE_PHONE = 0X00,
    /**
     * Tablet
     */
    DEVICE_TYPE_TABLET = 0x01,
    /**
     * Automobile
     */
    DEVICE_TYPE_CAR = 0x02,
    /**
     * Computer
     */
    DEVICE_TYPE_PC = 0x03,
    /**
     * TV.
     */
    DEVICE_TYPE_TV = 0x04,
    /**
     * Wearable
     */
    DEVICE_TYPE_WEARABLE = 0x06,
    /**
     * 2-in-1 device
     */
    DEVICE_TYPE_2IN1 = 0x07,
} ResourceManager_DeviceType;

/**
 * @brief Enumerates screen density types.
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
 * @brief Enumerates device states.
 *
 * @since 12
 */
typedef struct ResourceManager_Configuration {
    /**
     * Screen orientation.
     */
    ResourceManager_Direction direction;
    /**
     * Locale, for example, zh-Hans-CN.
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
    /** Reserved attributes. */
    uint32_t reserved[20];
} ResourceManager_Configuration;
#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_RESMGR_COMMON_H
