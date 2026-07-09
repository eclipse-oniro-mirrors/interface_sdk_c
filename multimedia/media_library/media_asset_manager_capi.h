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
 * @file media_asset_manager_capi.h
 *
 * @brief The file declares the APIs of the media asset manager. You can use the functions to request media assets in
 * the media library.
 *
 * @kit MediaLibraryKit
 * @syscap SystemCapability.FileManagement.PhotoAccessHelper.Core
 * @library libmedia_asset_manager.so
 * @since 12
 */

#ifndef MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_MANAGER_H
#define MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_MANAGER_H

#include <stdbool.h>

#include "media_asset_base_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an **OH_MediaAssetManager** instance.
 *
 * @return Returns a pointer to an OH_MediaAssetManager instance.
 * @since 12
*/
OH_MediaAssetManager* OH_MediaAssetManager_Create(void);

/**
 * @brief Requests an image in the specified directory.
 *
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param manager Pointer to an **OH_MediaAssetManager** instance.
 * @param uri Pointer to the URI of the requested image.
 * @param requestOptions Options related to the media asset quality and delivery mode.
 * @param destPath Pointer to the destination directory of the requested image.
 * @param callback Callback to be invoked when the requested image is ready.
 * @return Return Request id.
 * @since 12
*/
MediaLibrary_RequestId OH_MediaAssetManager_RequestImageForPath(OH_MediaAssetManager* manager, const char* uri,
    MediaLibrary_RequestOptions requestOptions, const char* destPath, OH_MediaLibrary_OnDataPrepared callback);

/**
 * @brief Requests a video in the specified directory.
 *
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param manager Pointer to an **OH_MediaAssetManager** instance.
 * @param uri Pointer to the URI of the requested video.
 * @param requestOptions Options related to the media asset quality and delivery mode.
 * @param destPath Pointer to the destination directory of the requested video.
 * @param callback Callback to be invoked when the requested video is ready.
 * @return Return Request id.
 * @since 12
*/
MediaLibrary_RequestId OH_MediaAssetManager_RequestVideoForPath(OH_MediaAssetManager* manager, const char* uri,
    MediaLibrary_RequestOptions requestOptions, const char* destPath, OH_MediaLibrary_OnDataPrepared callback);

/**
 * @brief Cancels a request based on the request ID.
 *
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param manager Pointer to an **OH_MediaAssetManager** instance.
 * @param requestId ID of the request to cancel.
 * @return Returns true if the request is canceled successfully; returns false otherwise.
 * @since 12
*/
bool OH_MediaAssetManager_CancelRequest(OH_MediaAssetManager* manager, const MediaLibrary_RequestId requestId);

/**
 * @brief Requests a moving photo based on different policies.
 *
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param manager Pointer to an {@link OH_MediaAssetManager} instance.
 * @param mediaAsset Pointer to the {@link OH_MediaAsset} instance to be requested.
 * @param requestOptions Options related to the media asset quality and delivery mode.
 *     The options are specified by {@link MediaLibrary_RequestOptions}.
 * @param requestId Pointer to the request ID, which is specified by {@link MediaLibrary_RequestId}.
 * @param callback Callback to be invoked when the requested moving photo is ready.
 *     The callback is specified by {@link OH_MediaLibrary_OnMovingPhotoDataPrepared}.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED if operation is not supported.
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED if permission is denied.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAssetManager_RequestMovingPhoto(OH_MediaAssetManager* manager,
    OH_MediaAsset* mediaAsset, MediaLibrary_RequestOptions requestOptions, MediaLibrary_RequestId* requestId,
    OH_MediaLibrary_OnMovingPhotoDataPrepared callback);

/**
 * @brief Requests an image based on different policies.
 *
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param manager Pointer to an {@link OH_MediaAssetManager} instance.
 * @param mediaAsset Pointer to the {@link OH_MediaAsset} instance to be requested.
 * @param requestOptions Options related to the media asset quality and delivery mode. The options are specified
 *     by {@link MediaLibrary_RequestOptions}.
 * @param requestId Pointer to the request ID, which is specified by {@link MediaLibrary_RequestId}.
 * @param callback Callback to be invoked when the requested image is ready. The callback is specified
 *     by {@link OH_MediaLibrary_OnImageDataPrepared}.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED if operation is not supported.
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED if permission is denied.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAssetManager_RequestImage(OH_MediaAssetManager* manager, OH_MediaAsset* mediaAsset,
    MediaLibrary_RequestOptions requestOptions, MediaLibrary_RequestId* requestId,
    OH_MediaLibrary_OnImageDataPrepared callback);

/**
 * @brief Releases an {@link OH_MediaAssetManager} instance.
 *
 * @param manager Pointer to an {@link OH_MediaAssetManager} instance.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAssetManager_Release(OH_MediaAssetManager* manager);

/**
 * @brief Requests an image based on different policies.
 *
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param manager Pointer to an **OH_MediaAssetManager** instance.
 * @param mediaAsset Pointer to the **OH_MediaAsset** instance to be requested.
 * @param requestOptions **MediaLibrary_RequestOptions** used for the image request policy mode.
 * @param requestId Pointer to the **MediaLibrary_RequestId** instance of the request. This parameter is an output
 *     parameter.
 * @param callback The **OH_MediaLibrary_OnQuickImageDataPrepared** method called when the requested source data is
 *     ready.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED if operation is not supported.
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED if permission is denied.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 23
 */
MediaLibrary_ErrorCode OH_MediaAssetManager_QuickRequestImage(OH_MediaAssetManager* manager, OH_MediaAsset* mediaAsset,
    MediaLibrary_RequestOptions requestOptions, MediaLibrary_RequestId* requestId,
    OH_MediaLibrary_OnQuickImageDataPrepared callback);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_MANAGER_H
/** @} */
