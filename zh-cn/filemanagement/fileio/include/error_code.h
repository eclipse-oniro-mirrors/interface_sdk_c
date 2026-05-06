/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup FileIO
 * @{
 *
 * @brief 提供文件管理模块的错误码定义。
 *
 * @since 12
 */

/**
 * @file error_code.h
 *
 * @brief Declare the error codes of file management module.
 *
 * @library NA
 * @kit CoreFileKit
 * @syscap SystemCapability.FileManagement.File.FileIO
 * @since 12
 */

 #ifndef FILE_MANAGEMENT_FILEIO_ERROR_CODE_H
 #define FILE_MANAGEMENT_FILEIO_ERROR_CODE_H

 #ifdef __cplusplus
 extern "C" {
 #endif

 /**
  * @brief error codes of file management
  *
  * @since 12
  */
 typedef enum FileManagement_ErrCode {
     /**
      * @brief 接口调用成功。
      *
      * @since 12
      */
     ERR_OK = 0,
     /**
      * @brief 接口权限校验失败。
      *
      * @since 12
      */
     ERR_PERMISSION_ERROR = 201,
     /**
      * @brief 无效入参。
      *
      * @since 12
      */
     ERR_INVALID_PARAMETER = 401,
     /**
      * @brief 当前设备不支持此接口。
      *
      * @since 12
      */
     ERR_DEVICE_NOT_SUPPORTED = 801,
     /**
      * @brief 操作不被允许。
      *
      * @since 12
      */
     ERR_EPERM = 13900001,
     /**
      * @brief 不存在此文件或文件夹。
      *
      * @since 12
      */
     ERR_ENOENT = 13900002,
     /**
      * @brief 内存溢出。
      *
      * @since 12
      */
     ERR_ENOMEM = 13900011,
     /**
      * @brief 内部未知错误。
      *
      * @since 12
      */
     ERR_UNKNOWN = 13900042
 } FileManagement_ErrCode;

 #ifdef __cplusplus
 }
 #endif
 /** @} */
 #endif // FILE_MANAGEMENT_FILEIO_ERROR_CODE_H