/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup MediaAssetManager
 * @{
 *
 * @brief 提供媒体库资源请求能力的API。
 *
 * OH_MediaAssetManager 结构和 MediaLibrary_RequestId 类型用于请求媒体库资源。
 * 可以使用请求ID取消该请求。
 *
 * @since 12
 */
/**
 * @file media_asset_base_capi.h
 *
 * @brief 定义了媒体资产管理器的结构和枚举。
 *
 * @kit MediaLibraryKit
 * @syscap SystemCapability.FileManagement.PhotoAccessHelper.Core
 * @library libmedia_asset_manager.so
 * @since 12
 */

#ifndef MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_BASE_H
#define MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_BASE_H

#include <stdint.h>

#include "multimedia/image_framework/image/image_source_native.h"
#include "multimedia/image_framework/image/picture_native.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义UUID最大长度。这个常量定义了UUID字符串的最大长度。
 *
 * @since 12
 */
static const int32_t UUID_STR_MAX_LENGTH = 37;

/**
 * @brief Maximum length of a request ID.
 *
 * @since 12
 */
static const int32_t UUID_STR_MAX_LENGTH = 37;

/**
 * @brief 定义媒体资产管理器。<br>此结构提供了请求媒体库资源的能力。<br>如果创建失败，则返回空指针。
 *
 * @since 12
 */
typedef struct OH_MediaAssetManager OH_MediaAssetManager;

/**
 * @brief 定义媒体资产更改请求。<br>此结构体提供了处理媒体资产更改请求的能力。
 *
 * @since 12
 */
typedef struct OH_MediaAssetChangeRequest OH_MediaAssetChangeRequest;

/**
 * @brief 定义动态照片。<br>此结构体提供了获取关于动态照片的信息的能力。
 *
 * @since 13
 */
typedef struct OH_MovingPhoto OH_MovingPhoto;

/**
 * @brief 定义媒体资产。<br>此结构体提供了封装文件资源属性的能力。
 *
 * @since 12
 */
typedef struct OH_MediaAsset OH_MediaAsset;

/**
 * @brief 定义请求ID。<br>当请求媒体库资源时，会返回此类型。<br>请求ID可用于取消请求。<br>如果请求失败，值将全为零，如 "00000000-0000-0000-0000-000000000000"。
 *
 * @since 12
 */
typedef struct MediaLibrary_RequestId {
/*request id*/
    char requestId[UUID_STR_MAX_LENGTH];
} MediaLibrary_RequestId;

/**
 * @brief 媒体库错误代码的枚举。
 *
 * @since 12
 */
typedef enum MediaLibrary_ErrorCode {
    /**
     * 媒体库结果正常。
     */
    MEDIA_LIBRARY_OK = 0,

    /**
     * 权限被拒绝。
     */
    MEDIA_LIBRARY_PERMISSION_DENIED = 201,

    /**
     * 强制参数未指定，参数类型不正确或参数验证失败。
     */
    MEDIA_LIBRARY_PARAMETER_ERROR = 401,

    /**
     * 文件不存在。
     */
    MEDIA_LIBRARY_NO_SUCH_FILE = 23800101,

    /**
     * 显示名称无效。
     */
    MEDIA_LIBRARY_INVALID_DISPLAY_NAME = 23800102,

    /**
     * 资产uri无效。
     */
    MEDIA_LIBRARY_INVALID_ASSET_URI = 23800103,

    /**
     * PhotoKey无效。
     */
    MEDIA_LIBRARY_INVALID_PHOTO_KEY = 23800104,

    /**
     * 不支持该操作。
     */
    MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED = 23800201,

    /**
     * 内部系统错误。建议重试并检查日志。可能的原因：<br>1. 数据库已损坏。<br>2. 文件系统异常。<br>3. IPC请求超时。
     */
    MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR = 23800301
} MediaLibrary_ErrorCode;

/**
 * @brief 请求资源分发模式。
 * <br>快速分发：不考虑资源质量，直接基于现有资源返回。
 * <br>高质量分发：返回高质量资源，若没有，则触发生成高质量资源，成功后才返回。
 * <br>均衡分发：若存在高质量资源，则直接返回高质量资源。否则，先返回低质量资源，并触发生成高质量资源，成功后再返回一次高质量资源。
 *
 * @since 12
 */
typedef enum MediaLibrary_DeliveryMode {
    /*delivery fast mode*/
    MEDIA_LIBRARY_FAST_MODE = 0,
    /*delivery high quality mode*/
    MEDIA_LIBRARY_HIGH_QUALITY_MODE = 1,
    /*delivery balanced mode*/
    MEDIA_LIBRARY_BALANCED_MODE = 2
} MediaLibrary_DeliveryMode;

/**
 * @brief 请求策略模式配置项。<br>此结构体为媒体资源请求策略模式配置项。
 *
 * @since 12
 */
typedef struct MediaLibrary_RequestOptions {
/*delivery mode*/
    MediaLibrary_DeliveryMode deliveryMode;
} MediaLibrary_RequestOptions;

/**
 * @brief 媒体类型的枚举。
 *
 * @since 12
 */
typedef enum MediaLibrary_MediaType {
    /*image asset*/
    MEDIA_LIBRARY_IMAGE = 1,
    /*video asset*/
    MEDIA_LIBRARY_VIDEO = 2
} MediaLibrary_MediaType;

/**
 * @brief 媒体资源子类型的枚举。
 *
 * @since 12
 */
typedef enum MediaLibrary_MediaSubType {
    /*default Photo Type*/
    MEDIA_LIBRARY_DEFAULT = 0,
    /*moving Photo Type*/
    MEDIA_LIBRARY_MOVING_PHOTO = 3,
    /*burst Photo Type*/
    MEDIA_LIBRARY_BURST = 4
} MediaLibrary_MediaSubType;

/**
 * @brief 资源类型的枚举。
 *
 * @since 12
 */
typedef enum MediaLibrary_ResourceType {
    /*image resource*/
    MEDIA_LIBRARY_IMAGE_RESOURCE = 1,
    /*video resource*/
    MEDIA_LIBRARY_VIDEO_RESOURCE = 2
} MediaLibrary_ResourceType;

/**
 * @brief 图像文件类型的枚举。
 *
 * @since 12
 */
typedef enum MediaLibrary_ImageFileType {
    /*JPEG type*/
    MEDIA_LIBRARY_IMAGE_JPEG = 1,
    /**
     * @brief MPEG.
     *
     * @since 19
     */
    MEDIA_LIBRARY_FILE_VIDEO = 3,
    /**
     * @brief HEIF.
     *
     * @since 23
     */
    MEDIA_LIBRARY_IMAGE_HEIF = 2
} MediaLibrary_ImageFileType;

/**
 * @brief 媒体资源质量枚举。
 * <br>此枚举与请求媒体资源时定义的分发模式有关。
 * <br>快速分发：不考虑资源质量，直接基于现有资源返回。
 * <br>高质量分发：返回高质量资源，若没有，则触发生成高质量资源，成功后才返回。
 * <br>均衡分发：若存在高质量资源，则直接返回高质量资源。否则，先返回低质量资源，并触发生成高质量资源，成功后再返回一次高质量资源。
 *
 * @since 12
 */
typedef enum MediaLibrary_MediaQuality {
    /*fast quality*/
    MEDIA_LIBRARY_QUALITY_FAST = 1,
    /*full quality*/
    MEDIA_LIBRARY_QUALITY_FULL = 2
} MediaLibrary_MediaQuality;

/**
 * @brief 媒体内容类型的枚举。
 *
 * @since 12
 */
typedef enum MediaLibrary_MediaContentType {
    /*compressed media content type*/
    MEDIA_LIBRARY_COMPRESSED = 1,
    /*picture object media content type*/
    MEDIA_LIBRARY_PICTURE_OBJECT = 2
} MediaLibrary_MediaContentType;

/**
 * @brief 当所请求的媒体资源准备完成时会触发回调。
 *
 * @param result 请求资源处理的结果。
 * @param requestId 请求Id。
 * @since 12
 */
typedef void (*OH_MediaLibrary_OnDataPrepared)(int32_t result, MediaLibrary_RequestId requestId);

/**
 * @brief 当请求的图像源准备就绪时会触发回调。
 *
 * @param result 处理所请求资源的结果{@link MediaLibrary_ErrorCode}。
 * @param requestId 请求的{@link MediaLibrary_RequestId}。
 * @param mediaQuality 请求源的{@link MediaLibrary_MediaQuality}。
 * @param type 请求源的{@link MediaLibrary_MediaContentType}。
 * @param imageSourceNative 当请求的图像源准备就绪时获取{@link OH_ImageSourceNative}。
 * @since 12
 */
typedef void (*OH_MediaLibrary_OnImageDataPrepared)(MediaLibrary_ErrorCode result,
    MediaLibrary_RequestId requestId, MediaLibrary_MediaQuality mediaQuality, MediaLibrary_MediaContentType type,
    OH_ImageSourceNative* imageSourceNative);

/**
 * @brief 当请求的动态照片准备就绪时会触发回调。
 *
 * @param result 处理所请求资源的结果{@link MediaLibrary_ErrorCode}。
 * @param requestId 请求的{@link MediaLibrary_RequestId}。
 * @param mediaQuality 请求资源的{@link MediaLibrary_MediaQuality}。
 * @param type 请求资源的{@link MediaLibrary_MediaContentType}。
 * @param movingPhoto 当请求的动态图片准备就绪时获取{@link OH_MovingPhoto}。
 * @since 13
 */
typedef void (*OH_MediaLibrary_OnMovingPhotoDataPrepared)(MediaLibrary_ErrorCode result,
    MediaLibrary_RequestId requestId, MediaLibrary_MediaQuality mediaQuality, MediaLibrary_MediaContentType type,
    OH_MovingPhoto* movingPhoto);

/**
 * @brief 当请求的图像源准备就绪时调用此函数。如果系统中存在图像缓冲区，则会返回一个图片对象，从而减少编码时间。
 *
 * @param result 处理所请求资源的结果。
 * @param requestId 请求资源的MediaLibrary_RequestId。
 * @param mediaQuality 请求资源的MediaLibrary_MediaQuality。
 * @param type 请求来源的MediaLibrary_MediaContentType。
 * @param imageSourceNative 用于在准备图像文件时获取OH_ImageSourceNative信息，否则imageSourceNative为null。
 * @param pictureNative 用于在准备图像源时获取OH_PictureNative信息，否则pictureNative为null。
 * @since 23
 */
typedef void (*OH_MediaLibrary_OnQuickImageDataPrepared)(MediaLibrary_ErrorCode result,
    MediaLibrary_RequestId requestId, MediaLibrary_MediaQuality mediaQuality, MediaLibrary_MediaContentType type,
    OH_ImageSourceNative* imageSourceNative, OH_PictureNative* pictureNative);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_BASE_H
/** @} */