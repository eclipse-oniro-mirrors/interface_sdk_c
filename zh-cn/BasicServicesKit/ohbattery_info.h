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
 * @addtogroup OH_BatteryInfo
 * @{
 *
 * @brief 提供BatteryInfo模块的C接口定义。
 *
 * @since 13
 * @version 1.0
 */
/**
 * @file ohbattery_info.h
 *
 * @brief 声明电池API以获取当前电池容量和电源类型的信息，定义电池相应常见事件。
 *
 * @library libohbattery_info.so
 * @kit BasicServicesKit
 * @syscap SystemCapability.PowerManager.BatteryManager.Core
 * @since 13
 * @version 1.0
 */

#ifndef OHBATTERY_INFO_HEADER
#define OHBATTERY_INFO_HEADER
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief 标识电池容量变化后发送的常见事件。
 *
 * @since 13
 * @version 1.0
 */
static const char* COMMON_EVENT_KEY_CAPACITY = "soc";
/**
 * @brief 标识充电状态更改后发送的常见事件。
 *
 * @since 13
 * @version 1.0
 */
static const char* COMMON_EVENT_KEY_CHARGE_STATE = "chargeState";
/**
 * @brief 标识插入类型更改后发送的常见事件。
 *
 * @since 13
 * @version 1.0
 */
static const char* COMMON_EVENT_KEY_PLUGGED_TYPE = "pluggedType";

/**
 * @brief 定义插入类型。
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /**
    * 电源已拔下。
    *
    * @since 13
    */
    PLUGGED_TYPE_NONE,
    /**
    * 电源是交流充电。
    *
    * @since 13
    */
    PLUGGED_TYPE_AC,
    /**
    * 电源是USB DC充电。
    *
    * @since 13
    */
    PLUGGED_TYPE_USB,
    /**
    * 电源为无线充电。
    *
    * @since 13
    */
    PLUGGED_TYPE_WIRELESS,
    /**
    * 预留枚举
    *
    * @since 13
    */
    PLUGGED_TYPE_BUTT
} BatteryInfo_BatteryPluggedType;

/**
 * @brief 返回当前电池容量。
 *
 * @return 返回介于0和100之间的数字。
 * @since 13
 */
int32_t OH_BatteryInfo_GetCapacity();

/**
 * @brief 返回当前插入的类型。
 *
 * @return {@link BatteryInfo_BatteryPluggedType#PLUGGED_TYPE_NONE} 如果电源被拔下。
 *         {@link BatteryInfo_BatteryPluggedType#PLUGGED_TYPE_AC} 如果电源是AC充电。
 *         {@link BatteryInfo_BatteryPluggedType#PLUGGED_TYPE_USB} 如果电源是USB DC充电。
 *         {@link BatteryInfo_BatteryPluggedType#PLUGGED_TYPE_WIRELESS} 如果电源是无线充电。
 *         {@link BatteryInfo_BatteryPluggedType#PLUGGED_TYPE_BUTT} 如果类型未知。
 * @since 13
 */
BatteryInfo_BatteryPluggedType OH_BatteryInfo_GetPluggedType();
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* OHBATTERY_INFO_HEADER */

/** @} */