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
 * @brief 通过resourcemanager模块，开发者可以在Native层通过资源ID或资源名称获取应用资源或系统资源，实现多语言、多设备和多屏幕密度的
 * 资源适配。具体包括：
 * <br>- 获取基础类型资源：获取颜色值（ARGB格式）、整数、浮点数、布尔值等基础类型资源。
 * <br>- 获取字符串资源：获取普通字符串、格式化字符串（支持%d、%s、%f占位符）、字符串数组、复数字符串。
 * <br>- 获取媒体资源：获取媒体资源的原始二进制数据或Base64编码。
 * <br>- 资源覆盖：运行时动态加载和移除overlay资源，实现主题切换或资源覆盖。
 * <br>本模块依赖rawfile模块，需先通过rawfile模块获取NativeResourceManager对象。
 *
 * @since 12
 */
/**
 * @file resmgr_common.h
 *
 * @brief 提供resourcemanager模块所需的枚举类型和结构体定义。
 * <br>本头文件定义了错误码、屏幕方向、颜色模式、设备类型、屏幕密度等枚举，以及设备配置结构体，为ohresmgr.h中的资源获取函数提供数据类型支持。
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
     * 根据资源ID未找到匹配的资源。
     */
    ERROR_CODE_RES_NOT_FOUND_BY_ID = 9001002,
    /**
     * 无效的资源名称。
     */
    ERROR_CODE_RES_NAME_NOT_FOUND = 9001003,
    /**
     * 根据资源名称未找到匹配的资源。
     */
    ERROR_CODE_RES_NOT_FOUND_BY_NAME = 9001004,
    /**
     * 无效的相对路径。
     */
    ERROR_CODE_RES_PATH_INVALID = 9001005,
    /**
     * 资源存在循环引用。
     */
    ERROR_CODE_RES_REF_TOO_MUCH = 9001006,
    /**
     * 根据资源ID获得的资源格式化失败。
     */
    ERROR_CODE_RES_ID_FORMAT_ERROR = 9001007,
    /**
     * 根据资源名称获得的资源格式化失败。
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
     * 表示竖屏。
     */
    DIRECTION_VERTICAL = 0,
    /**
     * 表示横屏。
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
     * 车机。
     */
    DEVICE_TYPE_CAR = 0x02,
    /**
     * PC设备。
     */
    DEVICE_TYPE_PC = 0x03,
    /**
     * 智慧屏。
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
 * @brief 设备状态的结构体。
 *
 * @since 12
 */
typedef struct ResourceManager_Configuration {
    /**
     * 表示屏幕方向。
     */
    ResourceManager_Direction direction;
    /**
     * 表示语言、文字、国家或地区，如zh_Hans_CN。
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
    /**
     * 保留属性。
     */
    uint32_t reserved[20];
} ResourceManager_Configuration;
#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_RESMGR_COMMON_H