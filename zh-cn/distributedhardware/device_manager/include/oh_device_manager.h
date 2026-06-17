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
 * @brief Distributed device management module,
 * which provides APIs to obtain information about trusted devices and local devices.
 *
 * @since 20
 */
/**
 * @file oh_device_manager.h
 *
 * @brief 提供访问可信设备和本地设备信息的接口。
 *
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
#endif

/**
  * @brief 获取本地设备显示名。
  * 设备显示名称涉及用户的隐私数据，需要应用提供相关隐私声明，声明设备显示名的用途。
  *
  * @permission ohos.permission.READ_LOCAL_DEVICE_NAME
  * @param localDeviceName 表示本地设备显示名字符串的地址指针。使用后需要手动释放空间资源。
  *     应用具备 ohos.permission.READ_LOCAL_DEVICE_NAME 权限，返回设备显示名称；否则返回设备默认名称。
  * @param len Length of the display name of the local device.
  * @return 返回执行的错误码。错误码定义详见{@link DeviceManager_ErrorCode}。
  *          返回{@link ERR_OK}，表示执行成功。
  *          返回{@link DM_ERR_FAILED}，表示函数执行失败。
  *          返回{@link DM_ERR_OBTAIN_SERVICE}，表示获取设备管理服务失败。
  *          返回{@link DM_ERR_OBTAIN_BUNDLE_NAME}，表示获取bundleName失败。
  *          返回{@link ERR_INVALID_PARAMETER}，表示参数localDeviceName是空指针或者*localDeviceName是非空指针。
  * @since 20
  */
int32_t OH_DeviceManager_GetLocalDeviceName(char **localDeviceName, unsigned int &len);

#ifdef __cplusplus
};
#endif

/** @} */
#endif
