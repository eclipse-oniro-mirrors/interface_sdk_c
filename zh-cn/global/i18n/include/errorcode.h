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
 * @addtogroup i18n
 * @{
 *
 * @brief 为应用提供国际化能力，依赖libohi18n.z.so。
 * @since 22
 */

/**
 * @file errorcode.h
 *
 * @brief i18n错误码。
 *
 * @library libohi18n.so
 * @kit LocalizationKit
 * @syscap SystemCapability.Global.I18n
 * @since 22
 */

#ifndef GLOBAL_I18N_ERRORCODE_H
#define GLOBAL_I18N_ERRORCODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief i18n错误码
 * @since 22
 */
typedef enum I18n_ErrorCode {
    /** @error 成功*/
    SUCCESS = 0,

    /** @error 无效的参数 */
    ERROR_INVALID_PARAMETER = 8900001,

    /** @error 意外错误，例如内存错误 */
    UNEXPECTED_ERROR = 8900050,
} I18n_ErrorCode;

#ifdef __cplusplus
};
#endif
#endif // GLOBAL_I18N_ERRORCODE_H

/** @} */
