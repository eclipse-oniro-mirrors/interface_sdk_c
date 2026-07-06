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
 * @brief 提供接口所需要的枚举类型和结构体。
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
 * @brief 资源管理错误码。
 *
 * @since 12
 */
typedef enum ResourceManager_ErrorCode {
    /**
     * 成功。
     */
    SUCCESS = 0,
    /**
     * 输入参数无效。
     */
    ERROR_CODE_INVALID_INPUT_PARAMETER = 401,
    /**
     * 无效的资源ID。
     */
    ERROR_CODE_RES_ID_NOT_FOUND = 9001001,
    /**
     * 没有根据资源ID找到匹配的资源。
     */
    ERROR_CODE_RES_NOT_FOUND_BY_ID = 9001002,
    /**
     * 无效的资源名称。
     */
    ERROR_CODE_RES_NAME_NOT_FOUND = 9001003,
    /**
     * 没有根据资源名称找到匹配的资源。
     */
    ERROR_CODE_RES_NOT_FOUND_BY_NAME = 9001004,
    /**
     * 无效的相对路径。
     */
    ERROR_CODE_RES_PATH_INVALID = 9001005,
    /**
     * 资源被循环引用。
     */
    ERROR_CODE_RES_REF_TOO_MUCH = 9001006,
    /**
     * 无法格式化基于资源ID获得的资源。
     */
    ERROR_CODE_RES_ID_FORMAT_ERROR = 9001007,
    /**
     * 无法格式化基于资源名称获得的资源。
     */
    ERROR_CODE_RES_NAME_FORMAT_ERROR = 9001008,
    /**
     * 访问系统资源失败。
     */
    ERROR_CODE_SYSTEM_RES_MANAGER_GET_FAILED = 9001009,
    /**
     * 无效的overlay路径。
     */
    ERROR_CODE_OVERLAY_RES_PATH_INVALID = 9001010,
    /**
     * 内存溢出。
     */
    ERROR_CODE_OUT_OF_MEMORY = 9001100,
} ResourceManager_ErrorCode;

/**
 * @brief 屏幕方向的枚举。
 *
 * @since 12
 */
typedef enum ResourceManager_Direction {
    /**
     * 表示垂直方向。
     */
    DIRECTION_VERTICAL = 0,
    /**
     * 表示水平方向。
     */
    DIRECTION_HORIZONTAL = 1,
} ResourceManager_Direction;

/**
 * @brief 颜色模式的枚举。
 *
 * @since 12
 */
typedef enum ResourceManager_ColorMode {
    /**
     * 表示深色模式。
     */
    COLOR_MODE_DARK = 0,
    /**
     * 表示浅色模式。
     */
    COLOR_MODE_LIGHT = 1,
} ResourceManager_ColorMode;

/**
 * @brief 设备类型的枚举。
 *
 * @since 12
 */
typedef enum ResourceManager_DeviceType {
    /**
     * 手机。
     */
    DEVICE_TYPE_PHONE = 0X00,
    /**
     * 平板。
     */
    DEVICE_TYPE_TABLET = 0x01,
    /**
     * 汽车。
     */
    DEVICE_TYPE_CAR = 0x02,
    /**
     * 电脑。
     */
    DEVICE_TYPE_PC = 0x03,
    /**
     * 电视。
     */
    DEVICE_TYPE_TV = 0x04,
    /**
     * 穿戴。
     */
    DEVICE_TYPE_WEARABLE = 0x06,
    /**
     * 2in1设备。
     */
    DEVICE_TYPE_2IN1 = 0x07,
} ResourceManager_DeviceType;

/**
 * @brief 屏幕密度类型的枚举。
 *
 * @since 12
 */
typedef enum ScreenDensity {
    /**
     * 表示小屏幕密度。
     */
    SCREEN_SDPI = 120,
    /**
     * 表示中屏幕密度。
     */
    SCREEN_MDPI = 160,
    /**
     * 表示大屏幕密度。
     */
    SCREEN_LDPI = 240,
    /**
     * 表示特大屏幕密度。
     */
    SCREEN_XLDPI = 320,
    /**
     * 表示超大屏幕密度。
     */
    SCREEN_XXLDPI = 480,
    /**
     * 表示超特大屏幕密度。
     */
    SCREEN_XXXLDPI = 640,
} ScreenDensity;

/**
 * @brief 设备状态的枚举。
 *
 * @since 12
 */
typedef struct ResourceManager_Configuration {
    /**
     * 表示屏幕方向。
     */
    ResourceManager_Direction direction;
    /**
     * 表示语言文字国家地区，如zh-Hans-CN。
     */
    char* locale;
    /**
     * 表示设备类型。
     */
    ResourceManager_DeviceType deviceType;
    /**
     * 表示屏幕密度。
     */
    ScreenDensity screenDensity;
    /**
     * 表示颜色模式。
     */
    ResourceManager_ColorMode colorMode;
    /**
     * 表示移动国家码。
     */
    uint32_t mcc;
    /**
     * 表示移动网络码。
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
