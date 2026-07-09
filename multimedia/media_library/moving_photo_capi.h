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
 * @since 13
 */
/**
 * @file moving_photo_capi.h
 *
 * @brief The file declares the APIs related to moving photos. You can use the APIs to obtain moving photo information.
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
 * @brief Obtains the URI of a moving photo.
 * 
 * @param movingPhoto Pointer to an {@link OH_MovingPhoto} instance.
 * @param uri Double pointer to the URI of the moving photo obtained.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MovingPhoto_GetUri(OH_MovingPhoto* movingPhoto, const char** uri);

/**
 * @brief Requests the image data and video data of a moving photo and writes them to the specified URIs, respectively.
 * 
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param movingPhoto Pointer to an {@link OH_MovingPhoto} instance.
 * @param imageUri Pointer to the URI of the file, to which the image data is written.
 * @param videoUri Pointer to the URI of the file, to which the video data is written.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED if permission is denied.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MovingPhoto_RequestContentWithUris(OH_MovingPhoto* movingPhoto, char* imageUri,
    char* videoUri);

/**
 * @brief Requests the moving photo content of the specified resource type and writes it to the specified URI.
 *
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param movingPhoto Pointer to an {@link OH_MovingPhoto} instance.
 * @param resourceType Resource type, which is specified by {@link MediaLibrary_ResourceType}.
 * @param uri Pointer to the URI of the file, to which the data is written.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED if permission is denied.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MovingPhoto_RequestContentWithUri(OH_MovingPhoto* movingPhoto,
    MediaLibrary_ResourceType resourceType, char* uri);

/**
 * @brief Requests the moving photo content of the specified resource type and returns it in ArrayBuffer format.
 * 
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param movingPhoto Pointer to an {@link OH_MovingPhoto} instance.
 * @param resourceType Resource type, which is specified by {@link MediaLibrary_ResourceType}.
 * @param buffer Double pointer to the buffer for storing the target file data.
 * @param size Pointer to the buffer size.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED if permission is denied.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MovingPhoto_RequestContentWithBuffer(OH_MovingPhoto* movingPhoto,
    MediaLibrary_ResourceType resourceType, const uint8_t** buffer, uint32_t* size);

/**
 * @brief Releases an {@link OH_MovingPhoto} instance.
 * 
 * @param movingPhoto Pointer to an {@link OH_MovingPhoto} instance.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MovingPhoto_Release(OH_MovingPhoto* movingPhoto);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MOVING_PHOTO_H
/** @} */