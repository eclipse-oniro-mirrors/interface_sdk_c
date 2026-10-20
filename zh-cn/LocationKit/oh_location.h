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
 *     等于true表示位置开关开启，false表示位置开关关闭。
 *     需要传入非空指针，否则会返回错误。
 * @return 	返回操作结果。
 *     详细定义参见{@link Location_ResultCode}。
 *     {@link LOCAION_SUCCESS}查询位置开关状态成功。
 *     {@link LOCATION_INVALID_PARAM}入参是空指针。
 *     {@link LOCATION_SERVICE_UNAVAILABLE}位置服务运行异常导致查询位置开关状态失败。
 * @since 13
 */
Location_ResultCode OH_Location_IsLocatingEnabled(bool* enabled);

/**
 * @brief 启动定位并订阅位置变化。
 *
 * @param requestConfig - 指向定位请求参数的指针，该参数用于指定发起定位的场景信息和位置上报间隔。
 *     详细定义请参考{@link Location_RequestConfig}，可以使用{@link OH_Location_CreateRequestConfig}创建。
 * @return 返回操作结果。
 *     详细定义参见Location_ResultCode{@link Location_ResultCode}。
 *     {@link LOCAION_SUCCESS}启动定位成功。
 *     {@link LOCATION_INVALID_PARAM}入参requestConfig为空指针。
 *     {@link LOCATION_PERMISSION_DENIED}权限校验失败。
 *     {@link LOCATION_NOT_SUPPORTED}当前设备不支持该功能。
 *     {@link LOCATION_SERVICE_UNAVAILABLE}位置服务运行异常。
 *     {@link LOCATION_SWITCH_OFF}位置开关未打开导致无法启动定位。
 * @permission ohos.permission.APPROXIMATELY_LOCATION
 * @since 13
 */
Location_ResultCode OH_Location_StartLocating(const Location_RequestConfig* requestConfig);

/**
 * @brief 停止定位并取消订阅位置变化。
 *
 * @param requestConfig - 指向定位请求参数的指针。详细定义参见{@link Location_RequestConfig}。
 *     该参数需要与{@link OH_Location_StartLocating}中的requestConfig是同一个指针。需要传入非空指针，否则会返回错误。
 * @return 返回操作结果。详细定义参见{@link Location_ResultCode}。
 *     {@link LOCAION_SUCCESS}停止定位成功。
 *     {@link LOCATION_INVALID_PARAM} 1.入参为空指针。
 *         2.入参与{@link OH_Location_StartLocating}的requestConfig指针不同。
 *     {@link LOCATION_PERMISSION_DENIED} 权限校验失败。
 *     {@link LOCATION_NOT_SUPPORTED} 当前设备不支持该功能。
 *     {@link LOCATION_SERVICE_UNAVAILABLE} 位置服务运行异常。
 *     {@link LOCATION_SWITCH_OFF} 位置开关未打开。
 * @permission ohos.permission.APPROXIMATELY_LOCATION
 * @since 13
 */
Location_ResultCode OH_Location_StopLocating(const Location_RequestConfig* requestConfig);
#ifdef __cplusplus
}
#endif
/** @} */
#endif // OH_LOCATION_H