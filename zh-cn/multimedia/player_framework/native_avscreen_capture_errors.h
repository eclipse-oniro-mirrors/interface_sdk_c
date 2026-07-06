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
 * @brief 声明用于运行屏幕录制过程中接口调用的错误码说明。
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
 * @brief 屏幕录制过程中产生的不同结果码。
 * 
 * @since 10
 */

typedef enum OH_AVSCREEN_CAPTURE_ErrCode {
    /**
     * 接口调用错误返回的基础值。
     */
    AV_SCREEN_CAPTURE_ERR_BASE = 0,
    /**
     * 操作成功。
     */
    AV_SCREEN_CAPTURE_ERR_OK = AV_SCREEN_CAPTURE_ERR_BASE,
    /**
     * 内存不足。
     */
    AV_SCREEN_CAPTURE_ERR_NO_MEMORY = AV_SCREEN_CAPTURE_ERR_BASE + 1,
    /**
     * 不允许操作。
     */
    AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT = AV_SCREEN_CAPTURE_ERR_BASE + 2,
    /**
     * 无效参数。
     */
    AV_SCREEN_CAPTURE_ERR_INVALID_VAL = AV_SCREEN_CAPTURE_ERR_BASE + 3,
    /**
     * 输入输出流异常。
     */
    AV_SCREEN_CAPTURE_ERR_IO = AV_SCREEN_CAPTURE_ERR_BASE + 4,
    /**
     * 网络超时。
     */
    AV_SCREEN_CAPTURE_ERR_TIMEOUT = AV_SCREEN_CAPTURE_ERR_BASE + 5,
    /**
     * 未知错误。
     */
    AV_SCREEN_CAPTURE_ERR_UNKNOWN = AV_SCREEN_CAPTURE_ERR_BASE + 6,
    /**
     * 媒体服务已终止。
     */
    AV_SCREEN_CAPTURE_ERR_SERVICE_DIED = AV_SCREEN_CAPTURE_ERR_BASE + 7,
    /**
     * 当前状态不支持此操作。
     */
    AV_SCREEN_CAPTURE_ERR_INVALID_STATE = AV_SCREEN_CAPTURE_ERR_BASE + 8,
    /**
     * 不支持的接口。
     */
    AV_SCREEN_CAPTURE_ERR_UNSUPPORT = AV_SCREEN_CAPTURE_ERR_BASE + 9,
    /**
     * 预期之外的错误。
     */
    AV_SCREEN_CAPTURE_ERR_EXTEND_START = AV_SCREEN_CAPTURE_ERR_BASE + 100,
} OH_AVSCREEN_CAPTURE_ErrCode;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSCREEN_CAPTURE_ERRORS_H
/** @} */