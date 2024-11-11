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
 * @addtogroup Pasteboard
 * @{
 *
 * @brief Provides the copy and paste support for the system Pasteboard.
 * You can use the APIs of this module to operate the Pasteboard content of the plain text, HTML,
 * URI, Want, pixel map, and other types.
 *
 * @since 13
 */

/**
 * @file oh_pasteboard_err_code.h
 *
 * @brief Declaration error code information.
 *
 * @kit BasicServicesKit
 * @library libpasteboard.so
 * @syscap SystemCapability.MiscServices.Pasteboard
 *
 * @since 13
 */


#ifndef OH_PASTEBOARD_ERR_CODE_H
#define OH_PASTEBOARD_ERR_CODE_H

#include <filemanagement/file_uri/error_code.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the error codes.
 *
 * @since 13
 */
typedef enum PASTEBOARD_ErrCode {
    /**
     * @error The operation is successful.
     */
    PASTEBOARD_ERR_OK = ERR_OK,
    /**
     * @error Permission verification failed.
     */
    PASTEBOARD_ERR_PERMISSION_ERROR = 201,
    /**
     * @error Invalid parameter is detected.
     */
    PASTEBOARD_ERR_INVALID_PARAMETER = 401,
    /**
     * @error The capability is not supported.
     */
    PASTEBOARD_ERR_DEVICE_NOT_SUPPORTED = 801,
    /**
     * @error Inner error.
     */
    PASTEBOARD_ERR_INNER_ERROR = 12900000,
    ERR_INNER_ERROR = PASTEBOARD_ERR_INNER_ERROR,
    /**
     * @error Another copy is in progress.
     */
    PASTEBOARD_ERR_BUSY = 12900003,
    ERR_BUSY = PASTEBOARD_ERR_BUSY,
} PASTEBOARD_ErrCode;
#ifdef __cplusplus
};
#endif

/** @} */
#endif
