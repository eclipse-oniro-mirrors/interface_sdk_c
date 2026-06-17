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
 * @addtogroup AVScreenCapture
 * @{
 *
 * @brief Provides APIs of request capability for Screen Capture.
 * @since 10
 */
/**
 * @file native_avscreen_capture_errors.h
 *
 * @brief The file declares the error codes generated during screen capture.
 * 
 * @library libnative_avscreen_capture.so
 * @syscap SystemCapability.Multimedia.Media.AVScreenCapture
 * @kit MediaKit
 * @since 10
 */
 
#ifndef NATIVE_AVSCREEN_CAPTURE_ERRORS_H
#define NATIVE_AVSCREEN_CAPTURE_ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the error codes generated during screen capture.
 * 
 * @since 10
 */

typedef enum OH_AVSCREEN_CAPTURE_ErrCode {
    /**
     * Basic value returned when an API call error occurs.
     */
    AV_SCREEN_CAPTURE_ERR_BASE = 0,
    /**
     * Operation successful.
     */
    AV_SCREEN_CAPTURE_ERR_OK = AV_SCREEN_CAPTURE_ERR_BASE,
    /**
     * Insufficient memory.
     */
    AV_SCREEN_CAPTURE_ERR_NO_MEMORY = AV_SCREEN_CAPTURE_ERR_BASE + 1,
    /**
     * Operation not allowed.
     */
    AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT = AV_SCREEN_CAPTURE_ERR_BASE + 2,
    /**
     * Invalid parameter.
     */
    AV_SCREEN_CAPTURE_ERR_INVALID_VAL = AV_SCREEN_CAPTURE_ERR_BASE + 3,
    /**
     * Abnormal input and output streams.
     */
    AV_SCREEN_CAPTURE_ERR_IO = AV_SCREEN_CAPTURE_ERR_BASE + 4,
    /**
     * Network timeout.
     */
    AV_SCREEN_CAPTURE_ERR_TIMEOUT = AV_SCREEN_CAPTURE_ERR_BASE + 5,
    /**
     * Unknown error.
     */
    AV_SCREEN_CAPTURE_ERR_UNKNOWN = AV_SCREEN_CAPTURE_ERR_BASE + 6,
    /**
     * Media service terminated.
     */
    AV_SCREEN_CAPTURE_ERR_SERVICE_DIED = AV_SCREEN_CAPTURE_ERR_BASE + 7,
    /**
     * Unsupported operation in this state.
     */
    AV_SCREEN_CAPTURE_ERR_INVALID_STATE = AV_SCREEN_CAPTURE_ERR_BASE + 8,
    /**
     * Unsupported interface.
     */
    AV_SCREEN_CAPTURE_ERR_UNSUPPORT = AV_SCREEN_CAPTURE_ERR_BASE + 9,
    /**
     * Unexpected error.
     */
    AV_SCREEN_CAPTURE_ERR_EXTEND_START = AV_SCREEN_CAPTURE_ERR_BASE + 100,
} OH_AVSCREEN_CAPTURE_ErrCode;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSCREEN_CAPTURE_ERRORS_H
/** @} */