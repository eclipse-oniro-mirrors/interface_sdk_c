/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @addtogroup Drm
 * @{
 *
 * @brief 提供数字版权保护能力的API。
 *
 * 开发者可根据开发需求，参考开发指南及样例：
 *
 * - [数字版权保护(C/C++)](docroot://media/drm/drm-c-dev-guide.md)
 * - [基于AVCodec播放DRM节目(C/C++)](docroot://media/drm/drm-avcodec-integration.md)
 *
 * @kit DrmKit
 * @since 11
 * @version 1.0
 */
/**
 * @file native_drm_err.h
 * @brief 定义DRM错误码，用于标识DRM模块在运行过程中可能出现的各种异常情况。开发者可基于错误码进行错误处理和问题定位，提高DRM应用的稳定性和可维护性，适用于需要处理DRM功能异常的场景。
 * 
 * @library libnative_drm.so
 * @include <multimedia/drm_framework/native_drm_err.h>
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_DRM_ERR_H
#define NATIVE_DRM_ERR_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief DRM错误码。
 * 
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */
typedef enum Drm_ErrCode {
    /**
     * 操作成功。
     */
    DRM_ERR_OK = 0,
    /**
     * 错误码基准值，用于生成其他错误码。
     */
    DRM_CAPI_ERR_BASE = 24700500,
    /**
     * 内存不足。
     */
    DRM_ERR_NO_MEMORY = DRM_CAPI_ERR_BASE + 1,
    /**
     * 不支持的操作。
     */
    DRM_ERR_OPERATION_NOT_PERMITTED = DRM_CAPI_ERR_BASE + 2,
    /**
     * 无效参数。
     */
    DRM_ERR_INVALID_VAL = DRM_CAPI_ERR_BASE + 3,
    /**
     * IO错误。
     */
    DRM_ERR_IO = DRM_CAPI_ERR_BASE + 4,
    /**
     * 网络超时。
     */
    DRM_ERR_TIMEOUT = DRM_CAPI_ERR_BASE + 5,
    /**
     * 未知错误。
     */
    DRM_ERR_UNKNOWN = DRM_CAPI_ERR_BASE + 6,
    /**
     * DRM服务死亡。
     */
    DRM_ERR_SERVICE_DIED = DRM_CAPI_ERR_BASE + 7,
    /**
     * 无效的操作状态。
     */
    DRM_ERR_INVALID_STATE = DRM_CAPI_ERR_BASE + 8,
    /**
     * 不支持的操作。
     */
    DRM_ERR_UNSUPPORTED = DRM_CAPI_ERR_BASE + 9,
    /**
     * MediaKeySystem最大实例数。
     */
    DRM_ERR_MAX_SYSTEM_NUM_REACHED = DRM_CAPI_ERR_BASE + 10,
    /**
     * MediaKeySession最大实例数。
     */
    DRM_ERR_MAX_SESSION_NUM_REACHED = DRM_CAPI_ERR_BASE + 11,
    /**
     * 扩展错误。
     */
    DRM_ERR_EXTEND_START  = DRM_CAPI_ERR_BASE + 100,
} Drm_ErrCode;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_DRM_ERR_H
/** @} */
