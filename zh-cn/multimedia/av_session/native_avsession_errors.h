/*
 * Copyright (C) 2024-2026 Huawei Device Co., Ltd.
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
 * @addtogroup OHAVSession
 * @{
 *
 * @brief 提供媒体会话模块C接口定义。
 * @since 13
 */

/**
 * @file native_avsession_errors.h
 *
 * @brief 提供播控错误码的定义。
 *
 * @library libohavsession.so
 * @syscap SystemCapability.Multimedia.AVSession.Core
 * @kit AVSessionKit
 * @since 13
 */

#ifndef NATIVE_AVSESSION_ERRORS_H
#define NATIVE_AVSESSION_ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 播控错误码。
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /**
     * @error 操作成功。
     */
    AV_SESSION_ERR_SUCCESS = 0,

    /**
     * @error 参数检查失败。
     */
    AV_SESSION_ERR_INVALID_PARAMETER = 401,

    /**
     * @error 会话服务端异常。
     */
    AV_SESSION_ERR_SERVICE_EXCEPTION = 6600101,

    /**
     * @error 会话不存在。
     */
    AV_SESSION_ERR_CODE_SESSION_NOT_EXIST = 6600102,

    /**
     * @error 无效会话命令。
     */
    AV_SESSION_ERR_CODE_COMMAND_INVALID = 6600105,

    /**
     * @error 会话未激活。
     */
    AV_SESSION_ERR_CODE_SESSION_INACTIVE = 6600106,

    /**
     * @error 命令和消息过载。
     */
    AV_SESSION_ERR_CODE_MESSAGE_OVERLOAD = 6600107,

    /**
     * @error 远端会话不存在。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_REMOTE_CONNECTION_NOT_EXIST = 6600109,

    /**投播控制器出现未知错误。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_UNSPECIFIED = 6611000,

    /**远端设备出现未知错误。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_REMOTE_ERROR = 6611001,

    /**加载位置超过投播视频的总进度。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_BEHIND_LIVE_WINDOW = 6611002,

    /**投播控制器加载超时。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_TIMEOUT = 6611003,

    /**运行时检查失败。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_RUNTIME_CHECK_FAILED = 6611004,

    /**跨设备数据传输被锁定。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PLAYER_NOT_WORKING = 6611100,

    /**不支持当前进度条模式。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_SEEK_MODE_UNSUPPORTED = 6611101,

    /**不支持跳转位置越界或异常跳转模式。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_ILLEGAL_SEEK_TARGET = 6611102,

    /**不支持当前播放模式。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PLAY_MODE_UNSUPPORTED = 6611103,

    /**不支持当前播放速度。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PLAY_SPEED_UNSUPPORTED = 6611104,

    /**媒体接收设备已离线，操作执行失败。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DEVICE_MISSING = 6611105,

    /**参数无效，如播放地址非法。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_INVALID_PARAM = 6611106,

    /**内存分配失败。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_NO_MEMORY = 6611107,

    /**不允许进行当前操作。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_OPERATION_NOT_ALLOWED = 6611108,

    /**未知的输入/输出错误。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_UNSPECIFIED = 6612000,

    /**网络连接失败。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_NETWORK_CONNECTION_FAILED = 6612001,

    /**网络超时。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_NETWORK_CONNECTION_TIMEOUT = 6612002,

    /**HTTP请求头中的Content-Type字段不合法。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_INVALID_HTTP_CONTENT_TYPE = 6612003,

    /**HTTP服务器返回异常的HTTP响应状态码。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_BAD_HTTP_STATUS = 6612004,

    /**文件不存在。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_FILE_NOT_FOUND = 6612005,

    /**缺少执行IO（输入/输出）操作的权限。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_NO_PERMISSION = 6612006,

    /**网络安全配置不允许此操作。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_CLEARTEXT_NOT_PERMITTED = 6612007,

    /**读取数据超出数据范围。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_READ_POSITION_OUT_OF_RANGE = 6612008,

    /**缺少可播放的媒体资源。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_NO_CONTENTS = 6612100,

    /**媒体无法被读取，如存储介质沾灰、出现划痕。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_READ_ERROR = 6612101,

    /**资源正在使用。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_CONTENT_BUSY = 6612102,

    /**内容使用有效期已过。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_CONTENT_EXPIRED = 6612103,

    /**不允许使用请求的内容。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_USE_FORBIDDEN = 6612104,

    /**无法验证授权内容的使用权限。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_NOT_VERIFIED = 6612105,

    /**该媒体内容的按需请求使用次数，已触达系统最大允许使用次数上限。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_EXHAUSTED_ALLOWED_USES = 6612106,

    /**本端向远端发送资源包失败。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_NETWORK_PACKET_SENDING_FAILED = 6612107,

    /**媒体内容解析过程中出现未明确具体类型的错误。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PARSING_UNSPECIFIED = 6613000,

    /**媒体容器格式码流解析错误。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PARSING_CONTAINER_MALFORMED = 6613001,

    /**媒体清单解析错误。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PARSING_MANIFEST_MALFORMED = 6613002,

    /**提取文件失败，不支持该媒体容器格式。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PARSING_CONTAINER_UNSUPPORTED = 6613003,

    /**媒体无法读取，如介质有灰尘、划痕。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PARSING_MANIFEST_UNSUPPORTED = 6613004,

    /**未知的解码错误。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DECODING_UNSPECIFIED = 6614000,

    /**解码器初始化失败。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DECODING_INIT_FAILED = 6614001,

    /**解码器查询失败。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DECODING_QUERY_FAILED = 6614002,

    /**解码媒体样本时失败。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DECODING_FAILED = 6614003,

    /**内容请求使用次数达最大限制。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DECODING_FORMAT_EXCEEDS_CAPABILITIES = 6614004,

    /**解码不支持的内容格式。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DECODING_FORMAT_UNSUPPORTED = 6614005,

    /**音频渲染器出现未明确具体类型的异常错误。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_AUDIO_RENDERER_UNSPECIFIED = 6615000,

    /**音频渲染器初始化异常。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_AUDIO_RENDERER_INIT_FAILED = 6615001,

    /**音频渲染器写数据异常。
     *
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_AUDIO_RENDERER_WRITE_FAILED = 6615002,
} AVSession_ErrCode;

/**
 * @brief 定义音视频会话回调结果枚举。
 *
 * @since 13
 */
typedef enum {
    /**
     * @brief 会话的回调结果为执行成功。
     */
    AVSESSION_CALLBACK_RESULT_SUCCESS = 0,

    /**
     * @brief 会话的回调结果为执行失败。
     */
    AVSESSION_CALLBACK_RESULT_FAILURE = -1,
} AVSessionCallback_Result;

/**
 * @brief 播控元数据错误码。
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /**
     * @error 接口执行成功。
     */
    AVMETADATA_SUCCESS = 0,

    /**
     * @error 该函数是使用无效的输入参数执行的。
     */
    AVMETADATA_ERROR_INVALID_PARAM = 1,

    /**
     * @error 内存分配失败。
     */
    AVMETADATA_ERROR_NO_MEMORY = 2,
} AVMetadata_Result;

/**
 * @brief 播放列表中单项的错误码。
 *
 * @since 23
 * @version 1.0
 */
typedef enum {
    /**
     * @error 接口执行成功。
     *
     * @since 23
     */
    AVQUEUEITEM_SUCCESS = 0,

    /**
     * @error 该函数是使用无效的输入参数执行的。
     *
     * @since 23
     */
    AVQUEUEITEM_ERROR_INVALID_PARAM = 1,

    /**
     * @error 内存分配失败。
     *
     * @since 23
     */
    AVQUEUEITEM_ERROR_NO_MEMORY = 2,
} AVQueueItem_Result;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSESSION_ERRORS_H
/** @} */