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
 * @file media_asset_manager_capi.h
 *
 * @brief 定义媒体资产管理器的接口。使用由媒体资产管理器提供的C API来请求媒体库资源。
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
 * @brief 创建一个媒体资产管理器。
 * 
 * @return 返回一个指向OH_MediaAssetManager实例的指针。
 * @since 12
 */
OH_MediaAssetManager* OH_MediaAssetManager_Create(void);

/**
 * @brief 请求具有目标路径的图像资源。
 * 
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param manager 指向OH_MediaAssetManager实例的指针。
 * @param uri 请求的图像资源的uri。
 * @param requestOptions 请求策略模式配置项。
 * @param destPath 请求资源的目标地址。
 * @param callback 媒体资源处理器，当所请求的媒体资源准备完成时会触发回调。
 * @return 返回请求Id。
 * @since 12
 */
MediaLibrary_RequestId OH_MediaAssetManager_RequestImageForPath(OH_MediaAssetManager* manager, const char* uri,
    MediaLibrary_RequestOptions requestOptions, const char* destPath, OH_MediaLibrary_OnDataPrepared callback);

/**
 * @brief 请求具有目标路径的视频资源。
 * 
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param manager 指向OH_MediaAssetManager实例的指针。
 * @param uri 请求的视频资源的uri。
 * @param requestOptions 请求策略模式配置项。
 * @param destPath 请求资源的目标地址。
 * @param callback 媒体资源处理器，当所请求的媒体资源准备完成时会触发回调。
 * @return 返回请求Id。
 * @since 12
 */
MediaLibrary_RequestId OH_MediaAssetManager_RequestVideoForPath(OH_MediaAssetManager* manager, const char* uri,
    MediaLibrary_RequestOptions requestOptions, const char* destPath, OH_MediaLibrary_OnDataPrepared callback);

/**
 * @brief 通过请求Id取消请求。
 * 
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param manager 指向OH_MediaAssetManager实例的指针。
 * @param requestId 待取消的请求Id。
 * @return 如果请求成功取消，则返回true；否则返回false。
 * @since 12
 */
bool OH_MediaAssetManager_CancelRequest(OH_MediaAssetManager* manager, const MediaLibrary_RequestId requestId);

/**
 * @brief 根据不同的策略模式请求动态照片资源。
 * 
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param manager {@link OH_MediaAssetManager}实例指针。
 * @param mediaAsset 要请求的媒体文件对象的{@link OH_MediaAsset}实例。
 * @param requestOptions 用于图像请求策略模式的{@link MediaLibrary_RequestOptions}。
 * @param requestId 请求的{@link MediaLibrary_RequestId}，出参。
 * @param callback 当请求的动态照片准备就绪时调用{@link OH_MediaLibrary_OnMovingPhotoDataPrepared}。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED：不支持该操作。
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED：没有权限。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAssetManager_RequestMovingPhoto(OH_MediaAssetManager* manager,
    OH_MediaAsset* mediaAsset, MediaLibrary_RequestOptions requestOptions, MediaLibrary_RequestId* requestId,
    OH_MediaLibrary_OnMovingPhotoDataPrepared callback);

/**
 * @brief 根据不同的策略模式请求图像资源。
 * 
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param manager {@link OH_MediaAssetManager}实例指针。
 * @param mediaAsset 要请求的媒体文件对象的{@link OH_MediaAsset}实例。
 * @param requestOptions 用于图像请求策略模式的{@link MediaLibrary_RequestOptions}。
 * @param requestId 请求的{@link MediaLibrary_RequestId}，出参。
 * @param callback 当请求的图像源准备就绪时调用{@link OH_MediaLibrary_OnImageDataPrepared}。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED：不支持该操作。
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED：没有权限。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAssetManager_RequestImage(OH_MediaAssetManager* manager, OH_MediaAsset* mediaAsset,
    MediaLibrary_RequestOptions requestOptions, MediaLibrary_RequestId* requestId,
    OH_MediaLibrary_OnImageDataPrepared callback);

/**
 * @brief 根据不同的策略模式请求图像资源。
 * 
 * @permission ohos.permission.READ_IMAGEVIDEO
 * @param manager OH_MediaAssetManager的实例指针。
 * @param mediaAsset 要请求的媒体文件对象的OH_MediaAsset实例。
 * @param requestOptions 用于图像请求策略模式的MediaLibrary_RequestOptions。
 * @param requestId 请求的MediaLibrary_RequestId，该参数为输出参数。
 * @param callback 当请求的源数据准备就绪时，将会调用OH_MediaLibrary_OnQuickImageDataPrepared方法。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED：不支持该操作。
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED：没有权限。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 23
 */
MediaLibrary_ErrorCode OH_MediaAssetManager_QuickRequestImage(OH_MediaAssetManager* manager, OH_MediaAsset* mediaAsset,
    MediaLibrary_RequestOptions requestOptions, MediaLibrary_RequestId* requestId,
    OH_MediaLibrary_OnQuickImageDataPrepared callback);

/**
 * @brief 释放{@link OH_MediaAssetManager}实例。
 * 
 * @param manager 要释放的{@link OH_MediaAssetManager}实例。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAssetManager_Release(OH_MediaAssetManager* manager);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_MANAGER_H
/** @} */