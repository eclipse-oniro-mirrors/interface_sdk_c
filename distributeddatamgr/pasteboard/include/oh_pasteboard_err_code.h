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
 * @include <database/pasteboard/oh_pasteboard_err_code.h>
 * @library libpasteboard.so
 * @syscap SystemCapability.MiscServices.Pasteboard
 *
 * @since 13
 */

#ifndef OH_PASTEBOARD_ERR_CODE_H
#define OH_PASTEBOARD_ERR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates pasteboard error codes, which are used to identify the pasteboard operation results. You can
 * determine whether an operation is successful and find the cause of a failure based on the error codes.
 *
 * @since 13
 */
typedef enum PASTEBOARD_ErrCode {
    /**
     * @brief Operation successful.
     */
    ERR_OK = 0,
    /**
     * @brief Permission verification failed.
     */
    ERR_PERMISSION_ERROR = 201,
    /**
     * @brief Invalid parameter.
     */
    ERR_INVALID_PARAMETER = 401,
    /**
     * @brief Device capability not supported.
     */
    ERR_DEVICE_NOT_SUPPORTED = 801,
    /**
     * @brief Internal error.
     */
    ERR_INNER_ERROR = 12900000,
    /**
     * @brief System busy.
     */
    ERR_BUSY = 12900003,
    /**
     * @brief Failed to copy files.
     * @since 15
     */
    ERR_PASTEBOARD_COPY_FILE_ERROR = 12900007,
    /**
     * @brief Failed to display the progress.
     * @since 15
     */
    ERR_PASTEBOARD_PROGRESS_START_ERROR = 12900008,
    /**
     * @brief Abnormal progress.
     * @since 15
     */
    ERR_PASTEBOARD_PROGRESS_ABNORMAL = 12900009,
    /**
     * @brief Failed to obtain the pasteboard data.
     * @since 15
     */
    ERR_PASTEBOARD_GET_DATA_FAILED = 12900010
} PASTEBOARD_ErrCode;
#ifdef __cplusplus
};
#endif

/** @} */
#endif