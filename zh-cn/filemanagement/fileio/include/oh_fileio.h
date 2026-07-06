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
 * @addtogroup FileIO
 * @{
 *
 * @brief fileio模块接口定义，提供获取文件存储位置的native接口。
 * @since 12
 */

 /**
 * @file oh_fileio.h
 *
 * @brief Provide fileio APIS.
 *
 * @library libohfileio.so
 * @kit CoreFileKit
 * @syscap SystemCapability.FileManagement.File.FileIO
 * @since 12
 */

 #ifndef FILE_MANAGEMENT_FILEIO_OH_FILEIO_H
 #define FILE_MANAGEMENT_FILEIO_OH_FILEIO_H

 #include "error_code.h"

 #ifdef __cplusplus
 extern "C" {
 #endif

 /**
  * @brief 文件存储位置枚举值。
  *
  * @since 12
  */
 typedef enum FileIO_FileLocation {
     /**
      * @brief 文件存储于本地。
      *
      * @since 12
      */
     LOCAL = 1,
     /**
      * @brief 文件存储于云侧。
      *
      * @since 12
      */
     CLOUD = 2,
     /**
      * @brief 文件存储于本地及云侧。
      *
      * @since 12
      */
     LOCAL_AND_CLOUD = 3
 } FileIO_FileLocation;

 /**
  * @brief Obtains the location of a file.
  *
  * @param uri 指向入参uri的指针。
  * @param uriLength 入参uri字符串的长度。
  * @param location 输出文件存储位置的指针。
  * @return 返回FileManagement模块错误码
  *         {@link ERR_INVALID_PARAMETER} 401 - Invalid input parameter, pointer is null.
  *         {@link ERR_ENOENT} 13900002 - No such file or directory.
  *         {@link ERR_ENOMEM} 13900011 - Failed to apply for memory.
  * @since 12
  */
 FileManagement_ErrCode OH_FileIO_GetFileLocation(char *uri, int uriLength,
     FileIO_FileLocation *location);

 #ifdef __cplusplus
 };
 #endif
 /** @} */
 #endif //FILE_MANAGEMENT_FILEIO_OH_FILEIO_H