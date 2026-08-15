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
 * @since 13
 */
/**
 * @file moving_photo_capi.h
 *
 * @brief 定义与动态照片相关的API。提供获取动态照片信息的功能。
 *
 * @kit MediaLibraryKit
 * @syscap SystemCapability.FileManagement.PhotoAccessHelper.Core
 * @library libmedia_asset_manager.so
 * @since 13
 */

#ifndef MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MOVING_PHOTO_H
#define MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MOVING_PHOTO_H

#include "media_asset_base_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 获取动态照片的uri。
 *
 * @param movingPhoto {@link OH_MovingPhoto}实例。
 * @param uri 动态照片的uri。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MovingPhoto_GetUri(OH_MovingPhoto* movingPhoto, const char** uri);

/**
 * @brief 同时请求动态照片的图片内容和视频内容，并写入参数指定的对应的uri中。
 *
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param movingPhoto {@link OH_MovingPhoto}实例。
 * @param imageUri 用于保存图像数据的目标文件uri。
 * @param videoUri 用于保存视频数据的目标文件uri。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED：没有权限。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MovingPhoto_RequestContentWithUris(OH_MovingPhoto* movingPhoto, char* imageUri,
    char* videoUri);

/**
 * @brief 请求指定资源类型的动态照片内容，并写入参数指定的uri中。
 *
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param movingPhoto {@link OH_MovingPhoto}实例。
 * @param resourceType 指定的资源类型{@link MediaLibrary_ResourceType}。
 * @param uri 保存数据的目标文件uri。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED：没有权限。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MovingPhoto_RequestContentWithUri(OH_MovingPhoto* movingPhoto,
    MediaLibrary_ResourceType resourceType, char* uri);

/**
 * @brief 请求指定资源类型的动态照片内容，以ArrayBuffer的形式返回。
 *
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param movingPhoto {@link OH_MovingPhoto}实例。
 * @param resourceType 指定的资源类型{@link MediaLibrary_ResourceType}。
 * @param buffer 保存目标文件数据的缓冲区。
 * @param size 缓冲区的大小。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED：没有权限。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MovingPhoto_RequestContentWithBuffer(OH_MovingPhoto* movingPhoto,
    MediaLibrary_ResourceType resourceType, const uint8_t** buffer, uint32_t* size);

/**
 * @brief Release {@link OH_MovingPhoto}实例。
 *
 * @param movingPhoto 要释放的{@link OH_MovingPhoto}实例。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MovingPhoto_Release(OH_MovingPhoto* movingPhoto);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MOVING_PHOTO_H
/** @} */