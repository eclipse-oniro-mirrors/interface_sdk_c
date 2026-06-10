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
 * @brief 提供获取公共文件根目录路径的能力。
 * @since 12
 */

/**
 * @file oh_environment.h
 *
 * @brief environment模块接口定义，使用environment提供的native接口，获取公共文件根目录的沙箱路径。
 *
 * @library libohenvironment.so
 * @kit CoreFileKit
 * @include <filemanagement/environment/oh_environment.h>
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
  * @brief 获取当前用户下载目录的沙箱路径，用于访问对应目录中的文件。
  *
  * @param result 返回Download根目录的沙箱路径。该字符串由系统分配内存，调用者需在使用完毕后通过free()释放，避免内存泄漏。
  * @return 返回FileManagement模块错误码。
  *         {@link ERR_INVALID_PARAMETER} 401 - Invalid input parameter, pointer is null.
  *         {@link ERR_DEVICE_NOT_SUPPORTED} 801 - Device not supported.
  *         {@link ERR_ENOMEM} 13900011 - Failed to apply for memory.
  * @since 12
  */
 FileManagement_ErrCode OH_Environment_GetUserDownloadDir(char **result);

 /**
  * @brief 获取当前用户桌面目录的沙箱路径，用于访问对应目录中的文件。
  *
  * @param result 返回Desktop根目录的沙箱路径。该字符串由系统分配内存，调用者需在使用完毕后通过free()释放，避免内存泄漏。
  * @return 返回FileManagement模块错误码。
  *         {@link ERR_INVALID_PARAMETER} 401 - Invalid input parameter, pointer is null.
  *         {@link ERR_DEVICE_NOT_SUPPORTED} 801 - Device not supported.
  *         {@link ERR_ENOMEM} 13900011 - Failed to apply for memory.
  * @since 12
  */
 FileManagement_ErrCode OH_Environment_GetUserDesktopDir(char **result);

 /**
  * @brief 获取当前用户文档目录的沙箱路径，用于访问对应目录中的文件。
  *
  * @param result 返回Document根目录的沙箱路径。该字符串由系统分配内存，调用者需在使用完毕后通过free()释放，避免内存泄漏。
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