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
 * @addtogroup Location
 * @{
 *
 * @brief 提供查询位置开关状态、启动定位、停止定位的接口。
 * @since 13
 */
/**
 * @file oh_location.h
 * @kit LocationKit
 * @brief 定义查询位置开关状态、启动定位、停止定位的接口。
 * @library liblocation_ndk.so
 * @syscap SystemCapability.Location.Location.Core
 * @since 13
 */

#ifndef OH_LOCATION_H
#define OH_LOCATION_H
#include <stdbool.h>
#include "oh_location_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 查询位置开关是否开启。
 *
 * @param enabled - bool类型的指针，用于接收位置开关状态值。
 * 等于true表示位置开关开启，false表示位置开关关闭。
 * 需要传入非空指针，否则会返回错误。
 * @return 	返回操作结果。\n
 *     详细定义参见Location_ResultCode{@link Location_ResultCode}。\n
 *     LOCATION_SUCCESS{@link LOCAION_SUCCESS}查询位置开关状态成功。\n
 *     LOCATION_INVALID_PARAM{@link LOCATION_INVALID_PARAM}入参是空指针。\n
 *     LOCATION_SERVICE_UNAVAILABLE{@link LOCATION_SERVICE_UNAVAILABLE}位置服务运行异常导致查询位置开关状态失败。\n
 * @since 13
 */
Location_ResultCode OH_Location_IsLocatingEnabled(bool* enabled);

/**
 * @brief 启动定位并订阅位置变化。
 *
 * @param requestConfig - 指向定位请求参数的指针，该参数用于指定发起定位的场景信息和位置上报间隔。
 * 详细定义请参考Location_RequestConfig{@link Location_RequestConfig}，\n
 * 可以使用OH_Location_CreateRequestConfig{@link OH_Location_CreateRequestConfig}创建。\n
 * @return 返回操作结果。\n
 *     详细定义参见Location_ResultCode{@link Location_ResultCode}。\n
 *     LOCATION_SUCCESS{@link LOCAION_SUCCESS}启动定位成功。
 *     LOCATION_INVALID_PARAM{@link LOCATION_INVALID_PARAM}入参requestConfig为空指针。
 *     LOCATION_PERMISSION_DENIED{@link LOCATION_PERMISSION_DENIED}权限校验失败。
 *     LOCATION_NOT_SUPPORTED{@link LOCATION_NOT_SUPPORTED}当前设备不支持该功能。
 *     LOCATION_SERVICE_UNAVAILABLE{@link LOCATION_SERVICE_UNAVAILABLE}位置服务运行异常。
 *     LOCATION_SWITCH_OFF{@link LOCATION_SWITCH_OFF}位置开关未打开导致无法启动定位。
 * @permission ohos.permission.APPROXIMATELY_LOCATION
 * @since 13
 */
Location_ResultCode OH_Location_StartLocating(const Location_RequestConfig* requestConfig);

/**
 * @brief 停止定位并取消订阅位置变化。
 *
 * @param requestConfig - 返回操作结果。\n
 * 详细定义参见Location_RequestConfig{@link Location_RequestConfig}。\n
 * 该参数需要与OH_Location_StartLocating{@link OH_Location_StartLocating}中的requestConfig是同一个指针。\n
 * @return 返回操作结果。\n
 *     详细定义参见Location_ResultCode{@link Location_ResultCode}。\n
 *     LOCATION_SUCCESS{@link LOCAION_SUCCESS}停止定位成功。\n
 *     {@link LOCATION_INVALID_PARAM} 1.The input parameter is a null pointer.\n
 *         2.Different from the requestConfig pointer passed from {@link OH_Location_StartLocating}.\n
 *     {@link LOCATION_PERMISSION_DENIED} Permission verification failed. The application does not have the\n
 *         permission required to call the API.\n
 *     {@link LOCATION_NOT_SUPPORTED} Capability not supported.\n
 *         Failed to call function due to limited device capabilities.\n
 *     {@link LOCATION_SERVICE_UNAVAILABLE} Possible reasons: 1. Abnormal startup of location services.\n
 *     {@link LOCATION_SWITCH_OFF} The location switch is off.\n
 * @permission ohos.permission.APPROXIMATELY_LOCATION
 * @since 13
 */
Location_ResultCode OH_Location_StopLocating(const Location_RequestConfig* requestConfig);
#ifdef __cplusplus
}
#endif
/** @} */
#endif // OH_LOCATION_H