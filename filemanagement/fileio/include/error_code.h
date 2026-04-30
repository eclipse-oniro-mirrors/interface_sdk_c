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
 * @brief Provide the definition of the error codes.
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
     * @brief The API is called successfully.
     *
     * @since 12
     */
    ERR_OK = 0,
    /**
     * @brief The permission verification fails.
     *
     * @since 12
     */
    ERR_PERMISSION_ERROR = 201,
    /**
     * @brief Invalid parameter.
     *
     * @since 12
     */
    ERR_INVALID_PARAMETER = 401,
    /**
     * @brief The device does not support this API.
     *
     * @since 12
     */
    ERR_DEVICE_NOT_SUPPORTED = 801,
    /**
     * @brief The operation is not allowed.
     *
     * @since 12
     */
    ERR_EPERM = 13900001,
    /**
     * @brief The file or folder does not exist.
     *
     * @since 12
     */
    ERR_ENOENT = 13900002,
    /**
     * @brief out of memory.
     *
     * @since 12
     */
    ERR_ENOMEM = 13900011,
    /**
     * @brief Internal unknown error.
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