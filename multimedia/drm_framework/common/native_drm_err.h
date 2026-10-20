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
 * @brief Provides APIs of Drm.
 * @kit DrmKit
 * @since 11
 * @version 1.0
 */
/**
 * @file native_drm_err.h
 * @brief The file declares the DRM error codes.
 * 
 * @library libnative_drm.so
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
 * @brief Enumerates the DRM error codes.
 * 
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */
typedef enum Drm_ErrCode {
    /**
     * Operation successful.
     */
    DRM_ERR_OK = 0,
    /**
     * Base error code.
     */
    DRM_CAPI_ERR_BASE = 24700500,
    /**
     * Insufficient memory.
     */
    DRM_ERR_NO_MEMORY = DRM_CAPI_ERR_BASE + 1,
    /**
     * Operation not permitted.
     */
    DRM_ERR_OPERATION_NOT_PERMITTED = DRM_CAPI_ERR_BASE + 2,
    /**
     * Invalid parameter.
     */
    DRM_ERR_INVALID_VAL = DRM_CAPI_ERR_BASE + 3,
    /**
     * I/O error.
     */
    DRM_ERR_IO = DRM_CAPI_ERR_BASE + 4,
    /**
     * Network timeout.
     */
    DRM_ERR_TIMEOUT = DRM_CAPI_ERR_BASE + 5,
    /**
     * Unknown error.
     */
    DRM_ERR_UNKNOWN = DRM_CAPI_ERR_BASE + 6,
    /**
     * DRM service unavailable.
     */
    DRM_ERR_SERVICE_DIED = DRM_CAPI_ERR_BASE + 7,
    /**
     * Invalid operation state.
     */
    DRM_ERR_INVALID_STATE = DRM_CAPI_ERR_BASE + 8,
    /**
     * Unsupported operation.
     */
    DRM_ERR_UNSUPPORTED = DRM_CAPI_ERR_BASE + 9,
    /**
     * Too many MediaKeySystem instances.
     */
    DRM_ERR_MAX_SYSTEM_NUM_REACHED = DRM_CAPI_ERR_BASE + 10,
    /**
     * Too many MediaKeySession instances.
     */
    DRM_ERR_MAX_SESSION_NUM_REACHED = DRM_CAPI_ERR_BASE + 11,
    /**
     * Extended error codes start.
     */
    DRM_ERR_EXTEND_START  = DRM_CAPI_ERR_BASE + 100,
} Drm_ErrCode;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_DRM_ERR_H
/** @} */