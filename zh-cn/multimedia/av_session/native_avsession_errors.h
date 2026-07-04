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
 * @brief Provide the definition of the C interface for the avsession module.
 * @since 13
 */

/**
 * @file native_avsession_errors.h
 *
 * @brief Declare avsession related error.
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
 * @brief AVSession error code
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /**
     * @error The operation completed successfully.
     */
    AV_SESSION_ERR_SUCCESS = 0,

    /**
     * @error Invalid parameter.
     */
    AV_SESSION_ERR_INVALID_PARAMETER = 401,

    /**
     * @error Service exception.
     */
    AV_SESSION_ERR_SERVICE_EXCEPTION = 6600101,

    /**
     * @error The session does not exist.
     */
    AV_SESSION_ERR_CODE_SESSION_NOT_EXIST = 6600102,

    /**
     * @error Invalid session command.
     */
    AV_SESSION_ERR_CODE_COMMAND_INVALID = 6600105,

    /**
     * @error The session is not activated.
     */
    AV_SESSION_ERR_CODE_SESSION_INACTIVE = 6600106,

    /**
     * @error Too many commands or events.
     */
    AV_SESSION_ERR_CODE_MESSAGE_OVERLOAD = 6600107,

    /**
     * @error 远端链接未建立
     * @since 23
     */
    AV_SESSION_ERR_CODE_REMOTE_CONNECTION_NOT_EXIST = 6600109,

    /**
     * 由投播控制器中的未知错误引起。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_UNSPECIFIED = 6611000,

    /**
     * 由远端设备中的未知错误引起。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_REMOTE_ERROR = 6611001,

    /**
     * 加载位置超过投播视频的总进度导致。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_BEHIND_LIVE_WINDOW = 6611002,

    /**
     * 投播控制器加载超时。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_TIMEOUT = 6611003,

    /**
     * 运行时检查失败。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_RUNTIME_CHECK_FAILED = 6611004,

    /**
     * 跨设备数据传输被锁定。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PLAYER_NOT_WORKING = 6611100,

    /**
     * 不支持当前进度条模式。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_SEEK_MODE_UNSUPPORTED = 6611101,

    /**
     * 非法seek目标。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_ILLEGAL_SEEK_TARGET = 6611102,

    /**
     * 不支持当前播放模式。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PLAY_MODE_UNSUPPORTED = 6611103,

    /**
     * 不支持当前播放速度。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PLAY_SPEED_UNSUPPORTED = 6611104,

    /**
     * 设备吊销
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DEVICE_MISSING = 6611105,

    /**
     * 传入非法参数。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_INVALID_PARAM = 6611106,

    /**
     * 分配内存失败。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_NO_MEMORY = 6611107,

    /**
     * 不允许进行当前操作。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_OPERATION_NOT_ALLOWED = 6611108,

    /**
     * 由未知的输入/输出错误引起。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_UNSPECIFIED = 6612000,

    /**
     * 网络连接失败。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_NETWORK_CONNECTION_FAILED = 6612001,

    /**
     * 网络超时导致服务器完成请求耗时过长。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_NETWORK_CONNECTION_TIMEOUT = 6612002,

    /**
     * 返回的是无效的“Content-Type”HTTP头。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_INVALID_HTTP_CONTENT_TYPE = 6612003,

    /**
     * 由HTTP服务器返回异常的HTTP响应状态码引起。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_BAD_HTTP_STATUS = 6612004,

    /**
     * 文件不存在。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_FILE_NOT_FOUND = 6612005,

    /**
     * 缺少执行IO操作的权限。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_NO_PERMISSION = 6612006,

    /**
     * 当播放器尝试访问明文HTTP流时，应用的网络安全配置不允许此操作。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_CLEARTEXT_NOT_PERMITTED = 6612007,

    /**
     * 读取数据超出数据范围。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_READ_POSITION_OUT_OF_RANGE = 6612008,

    /**
     * 媒体资源中不包含任何可播放的内容。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_NO_CONTENTS = 6612100,

    /**
     * 媒体资源无法被读取。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_READ_ERROR = 6612101,

    /**
     * 该资源在使用中。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_CONTENT_BUSY = 6612102,

    /**
     * 内容使用有效期已过。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_CONTENT_EXPIRED = 6612103,

    /**
     * 不允许使用请求的内容。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_USE_FORBIDDEN = 6612104,

    /**
     * 无法验证允许使用的内容。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_NOT_VERIFIED = 6612105,

    /**
     * 请求使用此内容的次数已达到允许使用的最大次数。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_EXHAUSTED_ALLOWED_USES = 6612106,

    /**
     * 本端向远端发资源包失败。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_IO_NETWORK_PACKET_SENDING_FAILED = 6612107,

    /**
     * 由未知的解析错误引起。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PARSING_UNSPECIFIED = 6613000,

    /**
     * 非法类型。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PARSING_CONTAINER_MALFORMED = 6613001,

    /**
     * 相关媒体清单的解析错误。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PARSING_MANIFEST_MALFORMED = 6613002,

    /**
     * 不支持该媒体格式。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PARSING_CONTAINER_UNSUPPORTED = 6613003,

    /**
     * 媒体清单中不支持此功能。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_PARSING_MANIFEST_UNSUPPORTED = 6613004,

    /**
     * 由未知的解码错误引起。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DECODING_UNSPECIFIED = 6614000,

    /**
     * 解码器初始化失败。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DECODING_INIT_FAILED = 6614001,

    /**
     * 解码器查询失败。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DECODING_QUERY_FAILED = 6614002,

    /**
     * 解码媒体样本时失败。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DECODING_FAILED = 6614003,

    /**
     * 所需解码的内容格式超出设备能力导致失败。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DECODING_FORMAT_EXCEEDS_CAPABILITIES = 6614004,

    /**
     * 解码不支持的内容格式而导致失败。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_DECODING_FORMAT_UNSUPPORTED = 6614005,

    /**
     * 音频渲染器相关的未知错误引起。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_AUDIO_RENDERER_UNSPECIFIED = 6615000,

    /**
     * AudioTrack初始化失败。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_AUDIO_RENDERER_INIT_FAILED = 6615001,

    /**
     * AudioTrack写操作失败。
     * @since 23
     */
    AV_SESSION_ERR_CODE_CAST_CONTROL_AUDIO_RENDERER_WRITE_FAILED = 6615002
} AVSession_ErrCode;

/**
 * @brief Defines enumeration of avsession callback result.
 *
 * @since 13
 */
typedef enum {
    /**
     * @brief Result of avsession callback is success.
     */
    AVSESSION_CALLBACK_RESULT_SUCCESS = 0,

    /**
     * @brief Result of avsession callback failed.
     */
    AVSESSION_CALLBACK_RESULT_FAILURE = -1
} AVSessionCallback_Result;

/**
 * @brief AVMetadata error code
 *
 * @since 13
 * @version 1.0
 */
typedef enum {
    /**
     * @error The call was successful.
     */
    AVMETADATA_SUCCESS = 0,

    /**
     * @error This means that the function was executed with an invalid input parameter.
     */
    AVMETADATA_ERROR_INVALID_PARAM = 1,

    /**
     * @error This means there is no memory left.
     */
    AVMETADATA_ERROR_NO_MEMORY = 2
} AVMetadata_Result;

/**
 * @brief AVQUEUEITEM构造的异常错误码
 *
 * @since 23
 * @version 1.0
 */
typedef enum {
    /**
     * @error 构造成功 */
     * @since 23
     */
    AVQUEUEITEM_SUCCESS = 0,

    /**
     * @error 参数错误异常 */
     * @since 23
     */
    AVQUEUEITEM_ERROR_INVALID_PARAM = 1,

    /**
     * @error 内存不足异常 */
     * @since 23
     */
    AVQUEUEITEM_ERROR_NO_MEMORY = 2
} AVQueueItem_Result;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSESSION_ERRORS_H
/** @} */