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
 * @brief Provides APIs of request capability for Media Source.
 *
 * The OH_MediaAssetManager structure and MediaLibrary_RequestId type are used to request media library resources.
 * The request can be cancelled using the request ID.
 *
 * @since 12
 */
/**
 * @file media_asset_base_capi.h
 *
 * @brief The file declares the structs and enums for the media asset manager.
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
 * @brief Maximum length of a request ID.
 *
 * @since 12
 */
static const int32_t UUID_STR_MAX_LENGTH = 37;

/**
 * @brief The struct describes the media asset manager.
 *
 * @since 12
 */
typedef struct OH_MediaAssetManager OH_MediaAssetManager;

/**
 * @brief The struct describes a media asset change request.
 *
 * @since 12
 */
typedef struct OH_MediaAssetChangeRequest OH_MediaAssetChangeRequest;

/**
 * @brief The struct describes a moving photo.
 *
 * @since 13
 */
typedef struct OH_MovingPhoto OH_MovingPhoto;

/**
 * @brief The struct describes a media asset.
 *
 * @since 12
 */
typedef struct OH_MediaAsset OH_MediaAsset;

/**
 * @brief Defines a struct for the request ID.
 *
 * @since 12
 */
typedef struct MediaLibrary_RequestId {
    /*request id*/
    char requestId[UUID_STR_MAX_LENGTH];
} MediaLibrary_RequestId;

/**
 * @brief Enumerates the error codes of the media library.
 *
 * @since 12
 */
typedef enum MediaLibrary_ErrorCode {
    /**
     * Operation success.
     */
    MEDIA_LIBRARY_OK = 0,

    /**
     * No access permission.
     */
    MEDIA_LIBRARY_PERMISSION_DENIED = 201,

    /**
     * A mandatory parameter is not specified, the parameter type is incorrect, or parameter verification failed.
     */
    MEDIA_LIBRARY_PARAMETER_ERROR = 401,

    /**
     * The file does not exist.
     */
    MEDIA_LIBRARY_NO_SUCH_FILE = 23800101,

    /**
     * Invalid display name.
     */
    MEDIA_LIBRARY_INVALID_DISPLAY_NAME = 23800102,

    /**
     * Invalid asset URI.
     */
    MEDIA_LIBRARY_INVALID_ASSET_URI = 23800103,

    /**
     * Invalid PhotoKey.
     */
    MEDIA_LIBRARY_INVALID_PHOTO_KEY = 23800104,

    /**
     * Unsupported operation.
     */
    MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED = 23800201,

    /**
     * Internal system error. Retry the operation and check logs. Possible causes:
     *     <br>1. The database is corrupted.
     *     <br>2. The file system is abnormal.
     *     <br>3. The IPC request timed out.
     */
    MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR = 23800301,
} MediaLibrary_ErrorCode;

/**
 * @brief Enumerates the delivery modes of the requested media asset.
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
 * @brief The struct defines how media assets are requested and processed.
 *
 * @since 12
 */
typedef struct MediaLibrary_RequestOptions {
    /*delivery mode*/
    MediaLibrary_DeliveryMode deliveryMode;
} MediaLibrary_RequestOptions;

/**
 * @brief Enumerates the media asset types.
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
 * @brief Enumerates the media asset subtypes.
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
 * @brief Enumerates the media library resource types.
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
 * @brief Enumerates the image file types.
 *
 * @since 12
 */
typedef enum MediaLibrary_ImageFileType {
    /*JPEG type*/
    MEDIA_LIBRARY_IMAGE_JPEG = 1,
    /**
     * @brief HEIF.
     *
     * @since 23
     */
    MEDIA_LIBRARY_IMAGE_HEIF = 2,
    /**
     * @brief MPEG.
     *
     * @since 19
     */
    MEDIA_LIBRARY_FILE_VIDEO = 3,
} MediaLibrary_ImageFileType;

/**
 * @brief Enumerates the media resource quality,
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
 * @brief Enumerates the media content types.
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
 * @brief Called when the requested media asset is ready.
 *
 * @param result Request processing result.
 * @param requestId Request ID.
 * @since 12
 */
typedef void (*OH_MediaLibrary_OnDataPrepared)(int32_t result, MediaLibrary_RequestId requestId);

/**
 * @brief Called when the requested image is ready.
 *
 * @param result Request processing result, which is specified by {@link MediaLibrary_ErrorCode}.
 * @param requestId Request ID, which is specified by {@link MediaLibrary_RequestId}.
 * @param mediaQuality Quality of the requested source, which is specified by {@link MediaLibrary_MediaQuality}.
 * @param type Media content type of the requested source, which is specified by {@link MediaLibrary_MediaContentType}.
 * @param imageSourceNative Pointer to the {@link OH_ImageSourceNative} instance obtained when the requested image is
 *     ready.
 * @since 12
 */
typedef void (*OH_MediaLibrary_OnImageDataPrepared)(MediaLibrary_ErrorCode result,
    MediaLibrary_RequestId requestId, MediaLibrary_MediaQuality mediaQuality, MediaLibrary_MediaContentType type,
    OH_ImageSourceNative* imageSourceNative);

/**
 * @brief Called when the requested moving photo is ready.
 *
 * @param result Request processing result, which is specified by {@link MediaLibrary_ErrorCode}.
 * @param requestId Request ID, which is specified by {@link MediaLibrary_RequestId}.
 * @param mediaQuality Quality of the requested resource, which is specified by {@link MediaLibrary_MediaQuality}.
 * @param type Media content type of the requested resource, which is specified
 *     by {@link MediaLibrary_MediaContentType}.
 * @param movingPhoto Pointer to the {@link OH_MovingPhoto} instance obtained when the requested moving photo is ready.
 * @since 13
 */
typedef void (*OH_MediaLibrary_OnMovingPhotoDataPrepared)(MediaLibrary_ErrorCode result,
    MediaLibrary_RequestId requestId, MediaLibrary_MediaQuality mediaQuality, MediaLibrary_MediaContentType type,
    OH_MovingPhoto* movingPhoto);

/**
 * @brief This callback is called when the requested image source is ready. If an image buffer exists in the system, an
 * image object is returned, reducing the encoding time.
 *
 * @param result Result of processing the requested resource.
 * @param requestId **MediaLibrary_RequestId** of the requested resource.
 * @param mediaQuality **MediaLibrary_MediaQuality** of the requested resource.
 * @param type **MediaLibrary_MediaContentType** of the requested resource.
 * @param imageSourceNative Used to obtain the **OH_ImageSourceNative** information when preparing the image file.
 *     Otherwise, **imageSourceNative** is null.
 * @param pictureNative Used to obtain the **OH_PictureNative** information when preparing the image source. Otherwise,
 *     **pictureNative** is null.
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
