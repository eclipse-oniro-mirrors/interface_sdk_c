/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup Core
 * @{
 *
 * @brief Core模块提供用于媒体系统的基础骨干能力，包含内存、错误码、媒体数据结构等相关函数。
 *
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */

/**
 * @file native_averrors.h
 *
 * @brief 媒体框架错误码。
 *
 * @kit AVCodecKit
 * @include <multimedia/player_framework/native_averrors.h>
 * @library libnative_media_core.so
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */

#ifndef NATIVE_AVERRORS_H
#define NATIVE_AVERRORS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 媒体框架错误码。
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 * @version 1.0
 */
typedef enum OH_AVErrCode {
    /**
     * 操作成功。
     */
    AV_ERR_OK = 0,
    /**
     * 无内存。
     */
    AV_ERR_NO_MEMORY = 1,
    /**
     * 操作不允许。
     */
    AV_ERR_OPERATE_NOT_PERMIT = 2,
    /**
     * 无效值。
     */
    AV_ERR_INVALID_VAL = 3,
    /**
     * IO错误。
     */
    AV_ERR_IO = 4,
    /**
     * 超时错误。
     */
    AV_ERR_TIMEOUT = 5,
    /**
     * 未知错误。
     */
    AV_ERR_UNKNOWN = 6,
    /**
     * 服务死亡。
     */
    AV_ERR_SERVICE_DIED = 7,
    /**
     * 当前状态不支持此操作。
     */
    AV_ERR_INVALID_STATE = 8,
    /**
     * 未支持的接口。
     */
    AV_ERR_UNSUPPORT = 9,
    /**
     * @error 输入数据错误。
     * @since 12
     */
    AV_ERR_INPUT_DATA_ERROR = 10,
    /**
     * @error 不支持的格式。
     * @since 18
     */
    AV_ERR_UNSUPPORTED_FORMAT = 11,
    /**
     * 扩展错误码初始值。
     */
    AV_ERR_EXTEND_START = 100,
    /**
     * @error DRM起始错误码。
     * @since 12
     */
    AV_ERR_DRM_BASE = 200,
    /**
     * @error DRM解密失败。
     * @since 12
     */
    AV_ERR_DRM_DECRYPT_FAILED = 201,
    /** 
     * @error 视频起始错误码。
     * @since 12
     */
    AV_ERR_VIDEO_BASE = 300,
    /** 
     * @error 视频不支持色彩空间转换。
     * @since 12
     */
    AV_ERR_VIDEO_UNSUPPORTED_COLOR_SPACE_CONVERSION = 301,
     /**
     * @error 无法找到主机，可能服务器地址错误。
     * @since 14
     */
    AV_ERR_IO_CANNOT_FIND_HOST = 5411001,
    /**
     * @error 网络连接超时。
     * @since 14
     */
    AV_ERR_IO_CONNECTION_TIMEOUT = 5411002,
    /**
     * @error 网络异常导致连接失败。
     * @since 14
     */
    AV_ERR_IO_NETWORK_ABNORMAL = 5411003,
    /**
     * @error 网络不可用导致连接失败。
     * @since 14
     */
    AV_ERR_IO_NETWORK_UNAVAILABLE = 5411004,
    /**
     * @error 无网络访问权限。
     * @since 14
     */
    AV_ERR_IO_NO_PERMISSION = 5411005,
    /**
     * @error 客户端请求参数错误或超出处理能力。
     * @since 14
     */
    AV_ERR_IO_NETWORK_ACCESS_DENIED = 5411006,
    /**
     * @error 无法找到可用网络资源。
     * @since 14
     */
    AV_ERR_IO_RESOURCE_NOT_FOUND = 5411007,
    /**
     * @error 由于未携带客户端证书、证书无效或过期导致服务器验证失败。
     * @since 14
     */
    AV_ERR_IO_SSL_CLIENT_CERT_NEEDED = 5411008,
    /**
     * @error 由于未携带服务器证书、证书无效或过期导致客户端验证失败。
     * @since 14
     */
    AV_ERR_IO_SSL_CONNECT_FAIL = 5411009,
    /**
     * @error SSL服务器证书不受信任。
     * @since 14
     */
    AV_ERR_IO_SSL_SERVER_CERT_UNTRUSTED = 5411010,
    /**
     * @error 网络协议不支持该请求。
     * @since 14
     */
    AV_ERR_IO_UNSUPPORTED_REQUEST = 5411011,
    /**
     * @error 不允许HTTP明文访问。
     * @since 23
     */
    AV_ERR_IO_CLEARTEXT_NOT_PERMITTED = 5411012,
    /**
     * @error 同步模式下流格式发生变更。
     * 可以通过调用接口{@link OH_VideoEncoder_GetOutputDescription}（视频编码）、{@link OH_VideoDecoder_GetOutputDescription}（视频解码）、
     * {@link OH_AudioCodec_GetOutputDescription}音频编解码来获取更新后流的配置信息。
     * @since 20
     */
    AV_ERR_STREAM_CHANGED = 5410005,
    /**
     * @error 同步模式下临时缓冲区查询失败，建议等待短暂间隔后重试操作。
     * @since 20
     */
    AV_ERR_TRY_AGAIN_LATER = 5410006,
    /**
     * @error 该媒体源或者当前设备不支持超分。
     * @since 23
     */
    AV_ERR_SUPER_RESOLUTION_UNSUPPORTED = 5410003,
    /**
     * @error 未使能超分。
     * @since 23
     */
    AV_ERR_SUPER_RESOLUTION_NOT_ENABLED = 5410004,
} OH_AVErrCode;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVERRORS_H
/** @} */
