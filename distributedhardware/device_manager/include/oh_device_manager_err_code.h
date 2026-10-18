/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @file oh_device_manager_err_code.h
 *
 * @brief Declares the error codes of the distributed device management module.
 *
 * @include <distributedhardware/device_manager/oh_device_manager_err_code.h>
 * @kit DistributedServiceKit
 * @library libdevicemanager_ndk.so
 * @syscap SystemCapability.DistributedHardware.DeviceManager
 *
 * @since 20
 */


#ifndef OH_DEVICE_MANAGER_ERR_CODE_H
#define OH_DEVICE_MANAGER_ERR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Error codes of the distributed device management module.
 *
 * @since 20
 */

typedef enum DeviceManager_ErrorCode {
    /**
     * @brief Operation success.
     *
     * @since 20
     */
    ERR_OK = 0,
    /**
     * @brief Permission verification failed.
     *
     * @since 20
     */
    ERR_PERMISSION_ERROR = 201,
    /**
     * @brief Invalid parameter.
     *
     * @since 20
     */
    ERR_INVALID_PARAMETER = 401,
    /**
     * @brief Function execution failed.
     *
     * @since 20
     */
    DM_ERR_FAILED = 11600101,
    /**
     * @brief Failed to obtain the device management service.
     *
     * @since 20
     */
    DM_ERR_OBTAIN_SERVICE = 11600102,
    /**
     * @brief Failed to obtain the bundle name.
     *
     * @since 20
     */
    DM_ERR_OBTAIN_BUNDLE_NAME = 11600109,
} DeviceManager_ErrorCode;
#ifdef __cplusplus
};
#endif

/** @} */
#endif
