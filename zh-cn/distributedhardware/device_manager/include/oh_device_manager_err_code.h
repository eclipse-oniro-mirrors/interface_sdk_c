/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @brief 分布式设备管理模块，用于获取可信设备和本地设备的基本信息。
 * 可信设备指已通过设备认证建立信任关系的设备，基本信息包括设备名称、设备类型、设备标识、设备状态等。
 * 该模块提供设备发现、设备绑定、设备信息查询、设备状态监听等功能，适用于分布式跨设备协同、设备互联等场景，实现业务协同与数据共享。
 *
 * 开发者可通过该模块提供的接口获取设备信息，完成分布式设备管理相关的开发任务。模块设计逻辑和使用说明，请参见分布式设备管理开发指导。
 * @since 20
 */
/**
 * @file oh_device_manager_err_code.h
 *
 * @brief 声明设备管理模块错误码信息。
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
 * @brief 分布式设备管理错误码信息。
 *
 * @since 20
 */

typedef enum DeviceManager_ErrorCode {
    /**
     * @brief 执行成功。
     *
     * @since 20
     */
    ERR_OK = 0,
    /**
     * @brief 权限校验失败。
     *
     * @since 20
     */
    ERR_PERMISSION_ERROR = 201,
    /**
     * @brief 非法参数。
     *
     * @since 20
     */
    ERR_INVALID_PARAMETER = 401,
    /**
     * @brief 函数执行失败。
     *
     * @since 20
     */
    DM_ERR_FAILED = 11600101,
    /**
     * @brief 获取设备管理服务失败。
     *
     * @since 20
     */
    DM_ERR_OBTAIN_SERVICE = 11600102,
    /**
     * @brief 获取bundleName失败。
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
