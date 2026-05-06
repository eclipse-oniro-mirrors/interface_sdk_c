/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @addtogroup AVSource
 * @{
 *
 * @brief The AVSource module provides functions for constructing media resource object functionality.
 *
 * @since 10
 */
/**
 * @file native_avsource.h
 *
 * @brief The file declares the APIs for parsing audio and video media data.
 *
 * @kit AVCodecKit
 * @library libnative_media_avsource.so
 * @syscap SystemCapability.Multimedia.Media.Spliter
 * @since 10
 */

#ifndef NATIVE_AVSOURCE_H
#define NATIVE_AVSOURCE_H

#include <stdint.h>
#include "native_avcodec_base.h"
#include "native_averrors.h"
#include "native_avformat.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The struct describes a native object for the media resource interface.
 *
 * @since 10
 */
typedef struct OH_AVSource OH_AVSource;

/**
 * @brief Creates an OH_AVSource instance with a user-defined data source. You can release the instance by calling
 * {@link OH_AVSource_Destroy}.
 *
 * The lifecycle of **dataSource** must be the same as that of the returned OH_AVSource * pointer.
 *
 * @param dataSource Pointer to user-defined data source.
 * @return Pointer to the OH_AVSource instance created. If the operation fails, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **dataSource** is nullptr.
 *     <br>2. The size of the data source is 0.
 *     <br>3. Setting the data source fails.
 *     <br>4. The memory is insufficient.
 *     <br>5. The decoder engine is nullptr.
 *     <br>6. dataSource-&gt;readAt == nullptr.
 * @since 12
 */
OH_AVSource *OH_AVSource_CreateWithDataSource(OH_AVDataSource *dataSource);

/**
 * @brief Creates an OH_AVSource instance with a user-defined data source. You can release the instance by calling
 * {@link OH_AVSource_Destroy}.
 *
 * User-defined data can be passed to its callback functions through the **userData** parameter.
 *
 * The lifecycle of **dataSource** must be the same as that of the returned OH_AVSource * pointer.
 *
 * @param dataSource Pointer to the data source struct, which is used to obtain the input data.
 * @param userData Pointer to user-defined data.
 * @return Pointer to the OH_AVSource instance created. If the operation fails, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **dataSource** is nullptr.
 *     <br>2. The size of the data source is 0.
 *     <br>3. Setting the data source fails.
 *     <br>4. The memory is insufficient.
 *     <br>5. The decoder engine is nullptr.
 *     <br>6. dataSource-&gt;readAt == nullptr.
 * @since 20
 */
OH_AVSource *OH_AVSource_CreateWithDataSourceExt(OH_AVDataSourceExt *dataSource, void *userData);

/**
 * @brief Creates an OH_AVSource instance based on a URI. You can release the instance by calling
 * {@link OH_AVSource_Destroy}. This function supports only HTTP progressive streaming media,
 * but not HLS/DASH streaming media. For HLS/DASH streaming media playback, use the AVPlayer for development.
 *
 * @param uri URI of the media resource.
 * @return Pointer to the OH_AVSource instance created. If the operation fails, NULL is returned.
 *  The possible causes of an operation failure are as follows:
 *     <br>1. The network is abnormal.
 *     <br>2. The resource is invalid.
 *     <br>3. The file format is not supported.
 *     <br>4. The application configuration is intercepted because it contains plaintext data.
 * @since 10
 */
OH_AVSource *OH_AVSource_CreateWithURI(char *uri);

/**
 * @brief Creates an OH_AVSource instance based on an FD. You can release the instance by calling
 * {@link OH_AVSource_Destroy}.
 *
 * If **offset** is not the start position of the file or **size** is not the file size, undefined errors such as
 * creation failure and demultiplexing failure may occur due to incomplete data obtained.
 *
 * @param fd FD of a media resource file.
 * @param offset Position from which data is to read.
 * @param size File size, in bytes.
 * @return Pointer to the OH_AVSource instance created. If the operation fails, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The FD is invalid.
 *     <br>2. The offset is not the start position of the file.
 *     <br>3. The size is incorrect.
 *     <br>4. The resource is invalid.
 *     <br>5. The file format is not supported.
 * @since 10
 */
OH_AVSource *OH_AVSource_CreateWithFD(int32_t fd, int64_t offset, int64_t size);

/**
 * @brief Destroys an OH_AVSource instance and clears internal resources.
 *
 * An instance can be destroyed only once. The destroyed instance cannot be used until it is re-created.
 * You are advised to set the pointer to NULL after the instance is destroyed.
 *
 * @param source Pointer to an OH_AVSource instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}:
 *     <br>1. The value of **source** is nullptr.
 *     <br>2. The value of **source** does not point to an OH_AVSource instance.
 * @since 10
 */
OH_AVErrCode OH_AVSource_Destroy(OH_AVSource *source);

/**
 * @brief Obtains the basic information about a media resource file.
 *
 * You must call {@link OH_AVFormat_Destroy} to release the OH_AVFormat instance when its lifecycle ends.
 *
 * @param source Pointer to an OH_AVSource instance.
 * @return Basic information about the file. If the operation fails, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **source** is nullptr.
 *     <br>2. The pointer is null or does not point to an OH_AVSource instance.
 *     <br>3. The source is not initialized.
 * @since 10
 */
OH_AVFormat *OH_AVSource_GetSourceFormat(OH_AVSource *source);

/**
 * @brief Obtains the basic information about a track.
 *
 * You must call {@link OH_AVFormat_Destroy} to release the OH_AVFormat instance when its lifecycle ends.
 *
 * @param source Pointer to an OH_AVSource instance.
 * @param trackIndex Index of the track whose information is to be obtained.
 * @return Basic information about the track. If the operation fails, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **source** is invalid (either nullptr or a pointer to a non-OH_AVSource instance).
 *     <br>2. The track index is out of range.
 *     <br>3. The source is not initialized.
 * @since 10
 */
OH_AVFormat *OH_AVSource_GetTrackFormat(OH_AVSource *source, uint32_t trackIndex);

/**
 * @brief Obtains the basic information about custom metadata.
 *
 * You must call {@link OH_AVFormat_Destroy} to release the OH_AVFormat instance when its lifecycle ends.
 *
 * @param source Pointer to an OH_AVSource instance.
 * @return Basic information about the metadata. If the operation fails, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **source** is nullptr.
 *     <br>2. The pointer is null or does not point to an OH_AVSource instance.
 *     <br>3. The source is not initialized.
 * @since 18
 */
OH_AVFormat *OH_AVSource_GetCustomMetadataFormat(OH_AVSource *source);

#ifdef __cplusplus
}
#endif

#endif // NATIVE_AVSOURCE_H
/** @} */