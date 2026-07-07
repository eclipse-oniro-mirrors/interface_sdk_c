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
 * @since 12
 */
/**
 * @file media_asset_change_request_capi.h
 *
 * @brief The file declares the APIs related to media asset change requests. You can use the APIs to change media
 * assets.
 * 
 * @kit MediaLibraryKit
 * @syscap SystemCapability.FileManagement.PhotoAccessHelper.Core
 * @library libmedia_asset_manager.so
 * @since 12
 */

#ifndef MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_CHANGE_REQUEST_H
#define MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_CHANGE_REQUEST_H

#include "media_asset_base_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an {@link OH_MediaAssetChangeRequest} instance.
 * 
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 12
*/
OH_MediaAssetChangeRequest* OH_MediaAssetChangeRequest_Create(OH_MediaAsset* mediaAsset);

/**
 * @brief Adds a resource of the given URI.
 * 
 * @param changeRequest Pointer to an {@link OH_MediaAssetChangeRequest} instance.
 * @param resourceType Type of the resource to add, which is specified by {@link MediaLibrary_ResourceType}.
 * @param fileUri Pointer to the URI of the file.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_NO_SUCH_FILE if file does not exist.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED if operation is not supported.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAssetChangeRequest_AddResourceWithUri(OH_MediaAssetChangeRequest* changeRequest,
    MediaLibrary_ResourceType resourceType, char* fileUri);

/**
 * @brief Adds a resource using ArrayBuffer data.
 * 
 * @param changeRequest Pointer to an {@link OH_MediaAssetChangeRequest} instance.
 * @param resourceType Type of the resource to add.
 * @param buffer Pointer to the data buffer.
 * @param length Length of the data buffer.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED if operation is not supported.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAssetChangeRequest_AddResourceWithBuffer(OH_MediaAssetChangeRequest* changeRequest,
    MediaLibrary_ResourceType resourceType, uint8_t* buffer, uint32_t length);

/**
 * @brief Obtains the handler used for writing a file to cache.
 * 
 * @permission ohos.permission.WRITE_IMAGEVIDEO
 * @param changeRequest Pointer to an {@link OH_MediaAssetChangeRequest} instance.
 * @param fd Pointer to the file descriptor (FD) obtained.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED if permission is denied.
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED if operation is not supported.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAssetChangeRequest_GetWriteCacheHandler(OH_MediaAssetChangeRequest* changeRequest,
    int32_t* fd);

/**
 * @brief Saves the photo taken by the camera.
 * 
 * @param changeRequest Pointer to an {@link OH_MediaAssetChangeRequest} instance.
 * @param imageFileType Type of the image file of the photo.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED if operation is not supported.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAssetChangeRequest_SaveCameraPhoto(OH_MediaAssetChangeRequest* changeRequest,
    MediaLibrary_ImageFileType imageFileType);

/**
 * @brief Discards the photo taken by the camera.
 * 
 * @param changeRequest Pointer to an {@link OH_MediaAssetChangeRequest} instance.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED if operation is not supported.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAssetChangeRequest_DiscardCameraPhoto(OH_MediaAssetChangeRequest* changeRequest);

/**
 * @brief Releases an {@link OH_MediaAssetChangeRequest} instance.
 * 
 * @param changeRequest Pointer to an {@link OH_MediaAssetChangeRequest} instance.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAssetChangeRequest_Release(OH_MediaAssetChangeRequest* changeRequest);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_CHANGE_REQUEST_H
/** @} */
