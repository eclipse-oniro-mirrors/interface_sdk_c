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
 * @addtogroup NativeWindow
 * @{
 *
 * @brief 定义错误码。
 *
 * @since 12
 * @version 1.0
 */

/**
 * @file graphic_error_code.h
 *
 * @brief 定义错误码。
 *
 * @kit ArkGraphics2D
 * @library libnative_window.so
 * @syscap SystemCapability.Graphic.Graphic2D.NativeWindow
 * @since 12
 * @version 1.0
 */

#ifndef INCLUDE_GRAPHIC_ERROR_CODE_H
#define INCLUDE_GRAPHIC_ERROR_CODE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 接口错误码说明（仅用于查询）。
 * @since 12
 */
typedef enum OHNativeErrorCode {
    /** 成功 */
    NATIVE_ERROR_OK = 0,
    /**
     * 内存操作错误
     * @since 15
     */
    NATIVE_ERROR_MEM_OPERATION_ERROR = 30001000,
    /** 入参无效 */
    NATIVE_ERROR_INVALID_ARGUMENTS = 40001000,
    /** 无权限操作 */
    NATIVE_ERROR_NO_PERMISSION = 40301000,
    /** 无空闲可用的buffer */
    NATIVE_ERROR_NO_BUFFER = 40601000,
    /**
     * 无效操作
     * @since 26.0.0
     */
    NATIVE_ERROR_INVALID_OPERATION = 41201000,
    /** 消费端不存在 */
    NATIVE_ERROR_NO_CONSUMER = 41202000,
    /** 未初始化 */
    NATIVE_ERROR_NOT_INIT = 41203000,
    /** 消费端已经被连接 */
    NATIVE_ERROR_CONSUMER_CONNECTED = 41206000,
    /** buffer状态不符合预期 */
    NATIVE_ERROR_BUFFER_STATE_INVALID = 41207000,
    /** buffer已在缓存队列中 */
    NATIVE_ERROR_BUFFER_IN_CACHE = 41208000,
    /** 队列已满 */
    NATIVE_ERROR_BUFFER_QUEUE_FULL = 41209000,
    /** buffer不在缓存队列中 */
    NATIVE_ERROR_BUFFER_NOT_IN_CACHE = 41210000,
    /** 消费端已经被断开连接 */
    NATIVE_ERROR_CONSUMER_DISCONNECTED = 41211000,
    /** 消费端未注册listener回调函数 */
    NATIVE_ERROR_CONSUMER_NO_LISTENER_REGISTERED = 41212000,
    /** 当前设备或平台不支持 */
    NATIVE_ERROR_UNSUPPORTED = 50102000,
    /** 未知错误，请查看日志 */
    NATIVE_ERROR_UNKNOWN = 50002000,
    /** HDI接口调用失败 */
    NATIVE_ERROR_HDI_ERROR = 50007000,
    /** 跨进程通信失败 */
    NATIVE_ERROR_BINDER_ERROR = 50401000,
    /** egl环境状态异常 */
    NATIVE_ERROR_EGL_STATE_UNKNOWN = 60001000,
    /** egl接口调用失败 */
    NATIVE_ERROR_EGL_API_FAILED = 60002000,
} OHNativeErrorCode;

#ifdef __cplusplus
}
#endif

/** @} */
#endif // INCLUDE_GRAPHIC_ERROR_CODE_H