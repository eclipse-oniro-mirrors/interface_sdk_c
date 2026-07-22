/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @addtogroup OHAVSession
 * @{
 *
 * @brief 提供媒体会话模块C接口定义。
 *
 * @syscap SystemCapability.Multimedia.AVSession.Core
 *
 * @since 23
 * @version 1.0
 */

/**
 * @file native_deviceinfo.h
 *
 * @brief 提供播控设备信息的定义。
 *
 * @library libohavsession.so
 * @syscap SystemCapability.Multimedia.AVSession.Core
 * @kit AVSessionKit
 * @since 23
 * @version 1.0
 */

#ifndef NATIVE_DEVICEINFO_H
#define NATIVE_DEVICEINFO_H

#include <stdint.h>
#include "native_avsession_base.h"
#include "native_avsession_errors.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 设备信息的结构体声明。
 * 该结构体用于存储设备信息及详细属性。
 *
 * @since 23
 */
typedef struct AVSession_DeviceInfo AVSession_DeviceInfo;

/**
 * @brief 输出设备信息的定义。
 *
 * @since 23
 */

typedef struct AVSession_OutputDeviceInfo {
    /**
     * @brief 设备信息数组的大小。
     */
    uint32_t size;
    /**
     * @brief 设备信息数组。
     */
    AVSession_DeviceInfo **deviceInfos;
} AVSession_OutputDeviceInfo;

/**
 * @brief 获取目标设备的投播类别。
 *
 * @param deviceInfo 表示设备信息实例指针。
 * @param aVCastCategory 返回aVCastCategory值的指针变量。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数deviceInfo为nullptr。\n
 *                                         2. 参数aVCastCategory为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_DeviceInfo_GetAVCastCategory(AVSession_DeviceInfo *deviceInfo,
    AVSession_AVCastCategory *aVCastCategory);

/**
 * @brief 获取目标设备的设备ID。
 *
 * @param deviceInfo 表示设备信息实例指针。
 * @param deviceId 用于获取设备ID字符串指针。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数deviceInfo为nullptr。\n
 *                                         2. 参数deviceId为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_DeviceInfo_GetDeviceId(AVSession_DeviceInfo *deviceInfo, char **deviceId);

/**
 * @brief 获取目标设备的设备名称。
 *
 * @param deviceInfo 表示设备信息实例指针。
 * @param deviceName 用于获取设备名称字符串指针。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数deviceInfo为nullptr。\n
 *                                         2. 参数deviceName为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_DeviceInfo_GetDeviceName(AVSession_DeviceInfo *deviceInfo, char **deviceName);

/**
 * @brief 获取目标设备的设备类型。
 *
 * @param deviceInfo 表示设备信息实例指针。
 * @param deviceType 返回设备类型的指针变量。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数deviceInfo为nullptr。\n
 *                                         2. 参数deviceType为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_DeviceInfo_GetDeviceType(AVSession_DeviceInfo *deviceInfo, AVSession_DeviceType *deviceType);

/**
 * @brief 获取目标设备支持的协议。
 *
 * @param deviceInfo 表示设备信息实例指针。
 * @param deviceProtocolType 用于获取设备支持协议类型的指针。
 * @return AV_SESSION_ERR_SUCCESS：函数执行成功。\n
 *         AV_SESSION_ERR_INVALID_PARAMETER：\n
 *                                         1. 参数deviceInfo为nullptr。\n
 *                                         2. 参数deviceProtocolType为nullptr。
 * @since 23
 */
AVSession_ErrCode OH_DeviceInfo_GetSupportedProtocols(AVSession_DeviceInfo *deviceInfo,
    uint32_t *deviceProtocolType);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_DEVICEINFO_H
/** @} */