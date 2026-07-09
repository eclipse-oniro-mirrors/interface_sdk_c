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
 * @file media_asset_capi.h
 *
 * @brief The file declares the APIs related to media assets. You can use the APIs to obtain image or video information.
 *
 * @kit MediaLibraryKit
 * @syscap SystemCapability.FileManagement.PhotoAccessHelper.Core
 * @library libmedia_asset_manager.so
 * @since 12
 */

#ifndef MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_H
#define MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_H

#include "media_asset_base_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Obtains the URI of a media asset.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param uri Double pointer to the URI obtained.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetUri(OH_MediaAsset* mediaAsset, const char** uri);

/**
 * @brief Obtains the type of a media asset.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param mediaType Pointer to the media asset type obtained.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetMediaType(OH_MediaAsset* mediaAsset, MediaLibrary_MediaType* mediaType);

/**
 * @brief Obtains the subtype of a media asset.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param mediaSubType Pointer to the media asset subtype obtained.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetMediaSubType(OH_MediaAsset* mediaAsset,
    MediaLibrary_MediaSubType* mediaSubType);

/**
 * @brief Obtains the display name of a media asset.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param displayName Double pointer to the display name obtained.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetDisplayName(OH_MediaAsset* mediaAsset, const char** displayName);

/**
 * @brief Obtains the size of a media asset file.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param size Pointer to the file size obtained, in bytes.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetSize(OH_MediaAsset* mediaAsset, uint32_t* size);

/**
 * @brief Obtains the date when a media asset was added.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param dateAdded Pointer to the date obtained. The value is the number of seconds elapsed since the Unix Epoch time (
 * 00:00:00 UTC on January 1, 1970).
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetDateAdded(OH_MediaAsset* mediaAsset, uint32_t* dateAdded);

/**
 * @brief Obtains the date when a media asset (content not the media asset name) was last modified.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param dateModified Pointer to the date obtained. The value is the number of milliseconds elapsed since the Unix
 * Epoch time.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetDateModified(OH_MediaAsset* mediaAsset, uint32_t* dateModified);

/**
 * @brief Obtains the date when a media asset was taken.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param dateTaken Pointer to the date obtained. The value is the number of seconds elapsed since the Unix Epoch time.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetDateTaken(OH_MediaAsset* mediaAsset, uint32_t* dateTaken);

/**
 * @brief Obtains the date when a media asset was added, in ms.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param dateAddedMs Pointer to the date obtained, in ms. The value is the number of milliseconds elapsed since the
 * Unix Epoch time.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetDateAddedMs(OH_MediaAsset* mediaAsset, uint32_t* dateAddedMs);

/**
 * @brief Obtains the date when a media asset (content not the media asset name) was last modified, in ms.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param dateModifiedMs Pointer to the date obtained, in ms. The value is the number of milliseconds elapsed since the
 * Unix Epoch time.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetDateModifiedMs(OH_MediaAsset* mediaAsset, uint32_t* dateModifiedMs);

/**
 * @brief Obtains the duration of a media asset, in ms.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param duration Pointer to the duration obtained, in ms.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetDuration(OH_MediaAsset* mediaAsset, uint32_t* duration);

/**
 * @brief Obtains the image width (in pixels) of a media asset.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param width Pointer to the image width obtained, in pixels.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetWidth(OH_MediaAsset* mediaAsset, uint32_t* width);

/**
 * @brief Obtains the image height (in pixels) of a media asset.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param height Pointer to the image height obtained, in pixels.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetHeight(OH_MediaAsset* mediaAsset, uint32_t* height);

/**
 * @brief Obtains the orientation of a media asset, in degrees.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param orientation Pointer to the orientation of the image obtained, in degrees.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetOrientation(OH_MediaAsset* mediaAsset, uint32_t* orientation);

/**
 * @brief Checks whether a media asset is favorited.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param favorite Pointer to the favorite status obtained.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAsset_IsFavorite(OH_MediaAsset* mediaAsset, uint32_t* favorite);

/**
 * @brief Obtains the title of a media asset.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @param title Pointer to the media asset title obtained.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR if internal system error.
 * @since 13
*/
MediaLibrary_ErrorCode OH_MediaAsset_GetTitle(OH_MediaAsset* mediaAsset, const char** title);

/**
 * @brief Releases a media asset.
 *
 * @param mediaAsset Pointer to an {@link OH_MediaAsset} instance.
 * @return MEDIA_LIBRARY_OK if the method call succeeds.
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR Parameter error. Possible causes:
 *     <br>1. Mandatory parameters are left unspecified.
 *     <br>2. Incorrect parameter types.
 *     <br>3. Parameter verification failed.
 * @since 12
*/
MediaLibrary_ErrorCode OH_MediaAsset_Release(OH_MediaAsset* mediaAsset);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_H
/** @} */