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
 * @brief 统一数据管理框架旨在定义数据跨应用、跨设备以及跨平台过程中的各项标准，
 * 提供统一的OpenHarmony数据语言和标准化的数据接入与读取通路。
 *
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */
/**
 * @file udmf_err_code.h
 *
 * @brief 声明统一数据管理框架错误码信息。
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
 * @brief 错误码信息。
 *
 * @since 12
 */
typedef enum Udmf_ErrCode {
    /**
     * 执行成功。
     */
    UDMF_E_OK = 0,
    /**
     * @brief 通用错误码。
     *
     */
    UDMF_ERR = 20400000,
    /**
     * @brief 非法参数。
     *
     */
    UDMF_E_INVALID_PARAM = (UDMF_ERR + 1),
} Udmf_ErrCode;

/**
 * @brief 异步获取数据时的状态码枚举。
 *
 * @since 15
 */
typedef enum Udmf_ListenerStatus {
    /**
     * 表示获取数据成功。
     */
    UDMF_FINISHED = 0,
    /**
     * @brief 表示正在处理中。
     *
     */
    UDMF_PROCESSING,
    /**
     * @brief 表示本次任务已被取消。
     *
     */
    UDMF_CANCELED,
    /**
     * @brief 表示有内部错误发生。
     *
     */
    UDMF_INNER_ERROR = 200,
    /**
     * @brief 表示包含无效参数。
     *
     */
    UDMF_INVALID_PARAMETERS,
    /**
     * @brief 表示没有获取到数据。
     *
     */
    UDMF_DATA_NOT_FOUND,
    /**
     * @brief 表示同步数据过程中出现错误。
     *
     */
    UDMF_SYNC_FAILED,
    /**
     * @brief 表示文件拷贝过程中出现错误。
     *
     */
    UDMF_COPY_FILE_FAILED,
} Udmf_ListenerStatus;

#ifdef __cplusplus
};
#endif

/** @} */
#endif
