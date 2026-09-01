/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @brief 系统剪贴板支持复制和粘贴多种类型的数据。可以使用此模块接口操作纯文本、HTML、URI、PixelMap等多种类型的数据。
 *
 * @since 13
 */

/**
 * @file oh_pasteboard_err_code.h
 *
 * @brief 声明剪贴板框架错误码信息。剪贴板错误码用于标识剪贴板操作过程中的执行结果，开发者可通过错误码判断操作是否成功以及失败的具体原因。
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
 * @brief 剪贴板错误码枚举，用于标识剪贴板操作的执行结果，开发者可通过错误码判断操作是否成功以及失败的具体原因。
 *
 * @since 13
 */
typedef enum PASTEBOARD_ErrCode {
    /**
     * @error 执行成功。
     */
    ERR_OK = 0,
    /**
     * @error 权限校验失败。
     */
    ERR_PERMISSION_ERROR = 201,
    /**
     * @error 非法参数。
     */
    ERR_INVALID_PARAMETER = 401,
    /**
     * @error 设备能力不支持。
     */
    ERR_DEVICE_NOT_SUPPORTED = 801,
    /**
     * @error 内部错误。
     */
    ERR_INNER_ERROR = 12900000,
    /**
     * @error 系统忙。
     */
    ERR_BUSY = 12900003,
    /**
     * @error 文件拷贝失败。
     * @since 15
     */
    ERR_PASTEBOARD_COPY_FILE_ERROR = 12900007,
    /**
     * @error 拉起进度显示失败。
     * @since 15
     */
    ERR_PASTEBOARD_PROGRESS_START_ERROR = 12900008,
    /**
     * @error 进度显示异常。
     * @since 15
     */
    ERR_PASTEBOARD_PROGRESS_ABNORMAL = 12900009,
    /**
     * @error 获取剪贴板数据失败。
     * @since 15
     */
    ERR_PASTEBOARD_GET_DATA_FAILED = 12900010,
} PASTEBOARD_ErrCode;
#ifdef __cplusplus
};
#endif

/** @} */
#endif