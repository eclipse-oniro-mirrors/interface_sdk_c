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
 * @addtogroup UDMF
 * @{
 *
 * @brief The Unified Data Management Framework(UDMF) aims to define various standards
 * for data across applications, devices, and platforms, providing a unified OpenHarmony
 * data language and standardized data access and reading paths.
 *
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */

/**
 * @file udmf_err_code.h
 *
 * @brief Declares the error codes used in the UDMF.
 *
 * @kit ArkData
 * @library libudmf.so
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */


#ifndef UDMF_ERR_CODE_H
#define UDMF_ERR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the error codes.
 *
 * @since 12
 */
typedef enum Udmf_ErrCode {
    /**
     * @brief Operation successful.
     *
     * @since 12
     */
    UDMF_E_OK = 0,
    /**
     * @brief Universal error codes.
     *
     * @since 12
     */
    UDMF_ERR = 20400000,
    /**
     * @brief Invalid parameter.
     *
     * @since 12
     */
    UDMF_E_INVALID_PARAM = (UDMF_ERR + 1),
} Udmf_ErrCode;

/**
 * @brief Enumerates the status codes returned when data is obtained asynchronously.
 *
 * @since 15
 */
typedef enum Udmf_ListenerStatus {
    /**
     * @brief Data is obtained successfully.
     *
     * @since 15
     */
    UDMF_FINISHED = 0,
    /**
     * @brief This task is being processed.
     *
     * @since 15
     */
    UDMF_PROCESSING,
    /**
     * @brief This task is canceled.
     *
     * @since 15
     */
    UDMF_CANCELED,
    /**
     * @brief An internal error occurs.
     *
     * @since 15
     */
    UDMF_INNER_ERROR = 200,
    /**
     * @brief Invalid parameters are contained.
     *
     * @since 15
     */
    UDMF_INVALID_PARAMETERS,
    /**
     * @brief No data is obtained.
     *
     * @since 15
     */
    UDMF_DATA_NOT_FOUND,
    /**
     * @brief An error occurs during data synchronization.
     *
     * @since 15
     */
    UDMF_SYNC_FAILED,
    /**
     * @brief Failed to copy the file.
     *
     * @since 15
     */
    UDMF_COPY_FILE_FAILED,
} Udmf_ListenerStatus;

#ifdef __cplusplus
};
#endif

/** @} */
#endif
