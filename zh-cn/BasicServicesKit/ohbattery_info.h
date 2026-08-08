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
 * @brief 声明电池API以获取设备当前剩余的电池电量百分比和连接的充电器类型，定义电池相关常见事件等。
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
 * @brief 标识剩余电池电量百分比变化后发送的常见事件。
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
 * @brief 标识连接的充电器类型更改后发送的常见事件。
 *
 * @since 13
 * @version 1.0
 */
static const char* COMMON_EVENT_KEY_PLUGGED_TYPE = "pluggedType";

/**
 * @brief 定义连接的充电器类型。
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
    * 电源是USB充电。
    *
    * @since 13
    */
    PLUGGED_TYPE_USB,
    /**
    * 电源是无线充电。
    *
    * @since 13
    */
    PLUGGED_TYPE_WIRELESS,
    /**
    * 未知类型。
    *
    * @since 13
    */
    PLUGGED_TYPE_BUTT
} BatteryInfo_BatteryPluggedType;

/**
 * @brief 返回当前电池电量百分比。可用于电池监控应用显示电量信息、低电量提醒功能判断是否需要提示用户、省电模式触发判断等场景。
 *
 * @return 表示当前电池电量百分比，取值范围为0到100之间的整数（包含0和100）。
 * @since 13
 */
int32_t OH_BatteryInfo_GetCapacity();

/**
 * @brief 返回连接的充电器类型。可用于充电状态检测应用判断当前充电方式、充电提醒功能展示充电类型图标、省电策略根据充电类型调整等场景。
 *
 * @return <ul>
 *         <li>{@link PLUGGED_TYPE_NONE} 如果电源被拔下。</li>
 *         <li>{@link PLUGGED_TYPE_AC} 如果电源是交流充电。</li>
 *         <li>{@link PLUGGED_TYPE_USB} 如果电源是USB充电。</li>
 *         <li>{@link PLUGGED_TYPE_WIRELESS} 如果电源是无线充电。</li>
 *         <li>{@link PLUGGED_TYPE_BUTT} 如果电源类型未知。</li>
 *         </ul>
 * @since 13
 */
BatteryInfo_BatteryPluggedType OH_BatteryInfo_GetPluggedType();
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* OHBATTERY_INFO_HEADER */

/** @} */