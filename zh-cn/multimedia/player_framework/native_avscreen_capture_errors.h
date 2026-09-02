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
 * @brief 提供屏幕录制的请求能力接口。
 * @since 10
 */
/**
 * @file native_avscreen_capture_errors.h
 *
 * @brief 声明屏幕录制接口调用的错误码，帮助开发者识别和处理屏幕录制中的各类异常情况，适用于屏幕录制故障排查和错误处理的开发场景。
 * @include <multimedia/player_framework/native_avscreen_capture_errors.h>
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
     * 错误码的基础值，其他错误码在此基础上递增，用于标识不同的错误类型。
     */
    AV_SCREEN_CAPTURE_ERR_BASE = 0,
    /**
     * 操作成功。
     */
    AV_SCREEN_CAPTURE_ERR_OK = AV_SCREEN_CAPTURE_ERR_BASE,
    /**
     * 内存不足。<br>
     * 可能原因：系统可用内存不足。<br>
     * 解决措施：请检查录制参数或系统内存状况。
     */
    AV_SCREEN_CAPTURE_ERR_NO_MEMORY = AV_SCREEN_CAPTURE_ERR_BASE + 1,
    /**
     * 不允许操作。<br>
     * 可能原因：当前操作未获得必要权限或处于非法状态。<br>
     * 解决措施：请检查操作权限和当前状态后重试。
     */
    AV_SCREEN_CAPTURE_ERR_OPERATE_NOT_PERMIT = AV_SCREEN_CAPTURE_ERR_BASE + 2,
    /**
     * 无效参数。<br>
     * 可能原因：传入的参数不符合接口要求或取值范围不正确。<br>
     * 解决措施：请检查参数类型和取值范围后重试。
     */
    AV_SCREEN_CAPTURE_ERR_INVALID_VAL = AV_SCREEN_CAPTURE_ERR_BASE + 3,
    /**
     * 输入输出流异常。<br>
     * 可能原因：文件读写失败或数据传输错误。<br>
     * 解决措施：请检查文件路径、权限和存储空间后重试。
     */
    AV_SCREEN_CAPTURE_ERR_IO = AV_SCREEN_CAPTURE_ERR_BASE + 4,
    /**
     * 网络超时。<br>
     * 可能原因：网络连接不稳定或服务器响应超时。<br>
     * 解决措施：请检查网络连接状态后重试。
     */
    AV_SCREEN_CAPTURE_ERR_TIMEOUT = AV_SCREEN_CAPTURE_ERR_BASE + 5,
    /**
     * 未知错误。<br>
     * 可能原因：发生了未预期的异常情况。<br>
     * 解决措施：请检查日志信息。
     */
    AV_SCREEN_CAPTURE_ERR_UNKNOWN = AV_SCREEN_CAPTURE_ERR_BASE + 6,
    /**
     * 媒体服务已终止。<br>
     * 可能原因：媒体服务进程崩溃或被系统终止。<br>
     * 解决措施：请检查系统资源或重启服务。
     */
    AV_SCREEN_CAPTURE_ERR_SERVICE_DIED = AV_SCREEN_CAPTURE_ERR_BASE + 7,
    /**
     * 当前状态不支持此操作。<br>
     * 可能原因：调用接口时实例处于错误状态。<br>
     * 解决措施：请检查当前状态并按正确流程调用接口。
     */
    AV_SCREEN_CAPTURE_ERR_INVALID_STATE = AV_SCREEN_CAPTURE_ERR_BASE + 8,
    /**
     * 不支持的接口。<br>
     * 可能原因：当前版本不支持此接口或功能。<br>
     * 解决措施：请检查API版本或设备兼容性。
     */
    AV_SCREEN_CAPTURE_ERR_UNSUPPORT = AV_SCREEN_CAPTURE_ERR_BASE + 9,
    /**
     * 预期之外的错误。<br>
     * 可能原因：发生了扩展的错误情况。<br>
     * 解决措施：请查看详细错误信息。
     */
    AV_SCREEN_CAPTURE_ERR_EXTEND_START = AV_SCREEN_CAPTURE_ERR_BASE + 100,
} OH_AVSCREEN_CAPTURE_ErrCode;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSCREEN_CAPTURE_ERRORS_H
/** @} */