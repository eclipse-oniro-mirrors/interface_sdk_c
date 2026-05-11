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
 * @brief Provides the definition of the C interface for the BatteryInfo module.
 *
 * @since 13
 * @version 1.0
 */
/**
 * @file ohbattery_info.h
 *
 * @brief Declares the battery APIs that are used to obtain the current battery capacity and power supply type and
 * define common battery events.
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
 * @brief Defines the common event indicating a battery capacity change.
 *
 * @since 13
 * @version 1.0
 */
static const char* COMMON_EVENT_KEY_CAPACITY = "soc";
/**
 * @brief Defines the common event indicating a charging status change.
 *
 * @since 13
 * @version 1.0
 */
static const char* COMMON_EVENT_KEY_CHARGE_STATE = "chargeState";
/**
 * @brief Defines the common event indicating a battery plugged type change.
 *
 * @since 13
 * @version 1.0
 */
static const char* COMMON_EVENT_KEY_PLUGGED_TYPE = "pluggedType";

/**
 * @brief Enumerates the battery plugged types.
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /**
    * No power supply.
    *
    * @since 13
    */
    PLUGGED_TYPE_NONE,
    /**
    * AC charging.
    *
    * @since 13
    */
    PLUGGED_TYPE_AC,
    /**
    * USB DC charging.
    *
    * @since 13
    */
    PLUGGED_TYPE_USB,
    /**
    * Wireless charging.
    *
    * @since 13
    */
    PLUGGED_TYPE_WIRELESS,
    /**
    * Reserved.
    *
    * @since 13
    */
    PLUGGED_TYPE_BUTT
} BatteryInfo_BatteryPluggedType;

/**
 * @brief Obtains the current battery capacity in percent.
 *
 * @return A number in the range from 0 to 100.
 * @since 13
 */
int32_t OH_BatteryInfo_GetCapacity();

/**
 * @brief Obtains the battery plugged type.
 *
 * @return {@link BatteryInfo_BatteryPluggedType#PLUGGED_TYPE_NONE} if there is no power supply;
 *         {@link PLUGGED_TYPE_AC} if the power supply is in AC charging mode;
 *         {@link PLUGGED_TYPE_USB} if the power supply is in USB DC charging mode;
 *         {@link PLUGGED_TYPE_WIRELESS} if the power supply is in wireless charging mode;
 *         {@link PLUGGED_TYPE_BUTT} if the battery plugged type is unknown.
 * @since 13
 */
BatteryInfo_BatteryPluggedType OH_BatteryInfo_GetPluggedType();
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* OHBATTERY_INFO_HEADER */

/** @} */