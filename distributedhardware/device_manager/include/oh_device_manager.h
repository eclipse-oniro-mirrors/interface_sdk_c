/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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
 * @addtogroup DeviceManager
 * @{
 *
 * @brief Distributed device management module, used to obtain basic information about trusted
 * devices and local devices.
 * Trusted devices refer to devices that have established trust relationships through device
 * authentication. Basic information includes device name, device type, device identifier, device
 * status, etc.
 * This module provides functions such as device discovery, device binding, device information
 * query, and device status monitoring. It is applicable to scenarios such as distributed
 * cross-device collaboration and device interconnection, enabling service collaboration and
 * data sharing.
 *
 * Developers can use the APIs provided by this module to obtain device information and complete
 * development tasks related to distributed device management. For module design logic and usage
 * instructions, see the Distributed Device Management Development Guide.
 * @since 20
 */
/**
 * @file oh_device_manager.h
 *
 * @brief Provides APIs to obtain information about trusted devices and local devices.
 *
 * @include <distributedhardware/device_manager/oh_device_manager.h>
 * @kit DistributedServiceKit
 * @library libdevicemanager_ndk.so
 * @syscap SystemCapability.DistributedHardware.DeviceManager
 *
 * @since 20
 */

#ifndef OH_DEVICE_MANAGER_H
#define OH_DEVICE_MANAGER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
/**
  * @brief Obtains the display name of the local device.
  * The device display name involves user privacy.
  * You need to provide a privacy statement to declare the purpose of the device display name.
  *
  * @permission ohos.permission.READ_LOCAL_DEVICE_NAME
  * @param localDeviceName Pointer to the display name of the local device.
  *     After using this API, you need to manually release resources to free up space.
  *     If the application has the ohos.permission.READ_LOCAL_DEVICE_NAME permission,
  *     the device display name is returned.
  *     Otherwise, the default device name is returned.
  * @param len Character length of the display name of the local device.
  * @return Error code. For details about the error code definitions, see {@link DeviceManager_ErrorCode}.
  *      <br>Returns {@link ERR_OK} is returned if the execution is successful.
  *      <br>Returns {@link DM_ERR_FAILED} is returned if the function fails to be executed.
  *      <br>Returns {@link DM_ERR_OBTAIN_SERVICE} is returned if the device management service fails to be obtained.
  *      <br>Returns {@link DM_ERR_OBTAIN_BUNDLE_NAME} is returned if the bundle name fails to be obtained.
  *      <br>Returns {@link ERR_INVALID_PARAMETER} is returned if the localDeviceName is nullptr or
  *                                            *localDeviceName is not nullptr.
  * @since 20
  * @deprecated since 26.0.0
  * @useinstead OH_DeviceManager_GetLocalDeviceNameC
  */
int32_t OH_DeviceManager_GetLocalDeviceName(char **localDeviceName, unsigned int &len);

#endif

/**
  * @brief Obtains the display name of the local device.
  * The device display name involves user privacy.
  * You need to provide a privacy statement to declare the purpose of the device display name.
  *
  * @permission ohos.permission.READ_LOCAL_DEVICE_NAME
  * @param localDeviceName Pointer to the display name of the local device.
  *     After using this API, you need to manually release resources to free up space.
  *     If the application has the ohos.permission.READ_LOCAL_DEVICE_NAME permission,
  *     the device display name is returned.
  *     Otherwise, the default device name is returned.
  * @param len Pointer to the length of the display name of the local device.
  *     After using this API, you need to manually release resources to free up space.
  * @return Error code. For details about the error code definitions, see {@link DeviceManager_ErrorCode}.
  *      <br>Returns {@link ERR_OK} is returned if the execution is successful.
  *      <br>Returns {@link DM_ERR_FAILED} is returned if the function fails to be executed.
  *      <br>Returns {@link DM_ERR_OBTAIN_SERVICE} is returned if the device management service fails to be obtained.
  *      <br>Returns {@link DM_ERR_OBTAIN_BUNDLE_NAME} is returned if the bundle name fails to be obtained.
  *      <br>Returns {@link ERR_INVALID_PARAMETER} is returned if the localDeviceName is nullptr or
  *                                            *localDeviceName is not nullptr or len is nullptr.
  * @since 26.0.0
  */
int32_t OH_DeviceManager_GetLocalDeviceNameC(char **localDeviceName, unsigned int *len);

#ifdef __cplusplus
};
#endif

/** @} */
#endif
