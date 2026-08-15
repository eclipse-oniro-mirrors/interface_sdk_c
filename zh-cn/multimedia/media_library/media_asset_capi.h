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
 * @since 12
 */
/**
 * @file media_asset_capi.h
 *
 * @brief 定义与媒体资源相关的API。提供获取图像或视频信息的能力。
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
 * @brief 获取媒体资产的uri。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param uri 媒体资产的uri。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetUri(OH_MediaAsset* mediaAsset, const char** uri);

/**
 * @brief 获取媒体资源类型。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param mediaType 媒体资源类型。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetMediaType(OH_MediaAsset* mediaAsset, MediaLibrary_MediaType* mediaType);

/**
 * @brief 获取媒体资源子类型。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param mediaSubType 媒体资源子类型。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetMediaSubType(OH_MediaAsset* mediaAsset,
    MediaLibrary_MediaSubType* mediaSubType);

/**
 * @brief 获取媒体资源的显示名称。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param displayName 媒体资源的显示名称。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetDisplayName(OH_MediaAsset* mediaAsset, const char** displayName);

/**
 * @brief 获取媒体资产的文件大小。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param size 媒体资源的文件大小（以字节为单位）。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetSize(OH_MediaAsset* mediaAsset, uint32_t* size);

/**
 * @brief 获取资产添加日期。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param dateAdded 资产添加日期。该值是添加文件时间距1970年1月1日的秒数值。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetDateAdded(OH_MediaAsset* mediaAsset, uint32_t* dateAdded);

/**
 * @brief 获取资产的修改日期。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param dateModified 资产的修改日期。该值是修改文件时间距1970年1月1日的秒数值，修改文件名不会改变此值，当文件内容发生修改时才会更新。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetDateModified(OH_MediaAsset* mediaAsset, uint32_t* dateModified);

/**
 * @brief 获取资产的拍摄日期。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param dateTaken 资产的拍摄日期。该值是文件拍照时间距1970年1月1日的秒数值。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetDateTaken(OH_MediaAsset* mediaAsset, uint32_t* dateTaken);

/**
 * @brief 获取资产的添加时间（毫秒）。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param dateAddedMs 资产的添加时间（毫秒）。该值是添加文件时间距1970年1月1日的毫秒数值。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetDateAddedMs(OH_MediaAsset* mediaAsset, uint32_t* dateAddedMs);

/**
 * @brief 获取资产的修改时间（毫秒）。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param dateModifiedMs 资产的修改时间（毫秒）。该值是修改文件时间距1970年1月1日的毫秒数值，修改文件名不会改变此值，当文件内容发生修改时才会更新。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetDateModifiedMs(OH_MediaAsset* mediaAsset, uint32_t* dateModifiedMs);

/**
 * @brief 获取媒体资源的持续时间（毫秒）。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param duration 媒体资源的持续时间（毫秒）。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetDuration(OH_MediaAsset* mediaAsset, uint32_t* duration);

/**
 * @brief 获取媒体资源的图像宽度（像素）。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param width 媒体资源的图像宽度（像素）。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetWidth(OH_MediaAsset* mediaAsset, uint32_t* width);

/**
 * @brief 获取媒体资源的图像高度（像素）。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param height 媒体资源的图像高度（像素）。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetHeight(OH_MediaAsset* mediaAsset, uint32_t* height);

/**
 * @brief 获取图像的旋转角度，单位为度（°）。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param orientation 图像的旋转角度，单位为度（°）。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetOrientation(OH_MediaAsset* mediaAsset, uint32_t* orientation);

/**
 * @brief 获取资产的收藏状态。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param favorite 资产的收藏状态。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAsset_IsFavorite(OH_MediaAsset* mediaAsset, uint32_t* favorite);

/**
 * @brief 获取媒体资产的标题。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @param title 媒体资产的标题。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAsset_GetTitle(OH_MediaAsset* mediaAsset, const char** title);

/**
 * @brief 释放媒体资产。
 *
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAsset_Release(OH_MediaAsset* mediaAsset);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_H
/** @} */