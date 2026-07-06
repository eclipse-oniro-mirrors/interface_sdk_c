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
 * @addtogroup Environment
 * @{
 *
 * @brief environment模块接口定义，使用environment提供的native接口，获取公共文件根目录的沙箱路径。
 * @since 12
 */

/**
 * @file oh_environment.h
 *
 * @brief Provide environment APIS.
 *
 * @library libohenvironment.so
 * @kit CoreFileKit
 * @syscap SystemCapability.FileManagement.File.Environment.FolderObtain
 * @since 12
 */

 #ifndef FILE_MANAGEMENT_ENVIRONMENT_OH_ENVIRONMENT_H
 #define FILE_MANAGEMENT_ENVIRONMENT_OH_ENVIRONMENT_H

 #include "error_code.h"

 #ifdef __cplusplus
 extern "C" {
 #endif
 /**
  * @brief 获取Download根目录沙箱路径。
  *
  * @param result Download根目录路径指针。请引用头文件malloc.h并使用free()进行资源释放。
  * @return 返回FileManagement模块错误码。
  *         {@link ERR_INVALID_PARAMETER} 401 - Invalid input parameter, pointer is null.
  *         {@link ERR_DEVICE_NOT_SUPPORTED} 801 - Device not supported.
  *         {@link ERR_ENOMEM} 13900011 - Failed to apply for memory.
  * @since 12
  */
 FileManagement_ErrCode OH_Environment_GetUserDownloadDir(char **result);

 /**
  * @brief 获取Desktop根目录沙箱路径。
  *
  * @param result Desktop根目录路径指针。请引用头文件malloc.h并使用free()进行资源释放。
  * @return 返回FileManagement模块错误码。
  *         {@link ERR_INVALID_PARAMETER} 401 - Invalid input parameter, pointer is null.
  *         {@link ERR_DEVICE_NOT_SUPPORTED} 801 - Device not supported.
  *         {@link ERR_ENOMEM} 13900011 - Failed to apply for memory.
  * @since 12
  */
 FileManagement_ErrCode OH_Environment_GetUserDesktopDir(char **result);

 /**
  * @brief 获取Document根目录沙箱路径。
  *
  * @param result Document根目录路径指针。请引用头文件malloc.h并使用free()进行资源释放。
  * @return 返回FileManagement模块错误码。
  *         {@link ERR_INVALID_PARAMETER} 401 - Invalid input parameter, pointer is null.
  *         {@link ERR_DEVICE_NOT_SUPPORTED} 801 - Device not supported.
  *         {@link ERR_ENOMEM} 13900011 - Failed to apply for memory.
  * @since 12
  */
 FileManagement_ErrCode OH_Environment_GetUserDocumentDir(char **result);

 #ifdef __cplusplus
 };
 #endif
 /** @} */
 #endif //FILE_MANAGEMENT_ENVIRONMENT_OH_ENVIRONMENT_H