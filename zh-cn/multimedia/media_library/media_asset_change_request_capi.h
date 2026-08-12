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
 * @since 12
 */
/**
 * @file media_asset_change_request_capi.h
 *
 * @brief 定义与媒体资产更改请求相关的API。提供更改资产的能力。
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
 * @brief 创建{@link OH_MediaAssetChangeRequest}实例。
 * 
 * @param mediaAsset {@link OH_MediaAsset}实例。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 12
 */
OH_MediaAssetChangeRequest* OH_MediaAssetChangeRequest_Create(OH_MediaAsset* mediaAsset);

/**
 * @brief 通过文件uri添加资源。
 * 
 * @param changeRequest {@link OH_MediaAssetChangeRequest}实例。
 * @param resourceType 要添加的资源的{@link MediaLibrary_ResourceType}。
 * @param fileUri 文件uri。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_NO_SUCH_FILE：文件不存在。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED：不支持该操作。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAssetChangeRequest_AddResourceWithUri(OH_MediaAssetChangeRequest* changeRequest,
    MediaLibrary_ResourceType resourceType, char* fileUri);

/**
 * @brief 通过ArrayBuffer数据添加资源。
 * 
 * @param changeRequest {@link OH_MediaAssetChangeRequest}实例。
 * @param resourceType 要添加的资源的类型。
 * @param buffer 要添加的数据缓冲区。
 * @param length 数据缓冲区的长度。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED：不支持该操作。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAssetChangeRequest_AddResourceWithBuffer(OH_MediaAssetChangeRequest* changeRequest,
    MediaLibrary_ResourceType resourceType, uint8_t* buffer, uint32_t length);

/**
 * @brief 获取临时文件写句柄。
 * 
 * @permission ohos.permission.WRITE_IMAGEVIDEO
 * @param changeRequest {@link OH_MediaAssetChangeRequest}实例。
 * @param fd 临时文件写句柄。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED：没有权限。
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED：不支持该操作。
 * @since 13
 */
MediaLibrary_ErrorCode OH_MediaAssetChangeRequest_GetWriteCacheHandler(OH_MediaAssetChangeRequest* changeRequest,
    int32_t* fd);

/**
 * @brief 拍照场景下，使用该接口保存相机拍摄的照片资源。
 * <br>非YUV拍摄模式下，照片资源保存的编码格式与{@link Camera_Format}中的编码格式保持一致。
 * <br>YUV拍摄模式下，该接口根据{@link MediaLibrary_ImageFileType}将YUV对象编码保存为指定格式。
 * <br>当该接口与{@link OH_MediaAssetChangeRequest_AddResourceWithUri}或
 * {@link OH_MediaAssetChangeRequest_AddResourceWithBuffer}组合使用时，照片资源保存的编码格式与
 * {@link OH_MediaAssetChangeRequest_AddResourceWithUri}或{@link OH_MediaAssetChangeRequest_AddResourceWithBuffer}
 * 添加资源的编码格式保持一致。
 *
 * @param changeRequest {@link OH_MediaAssetChangeRequest}实例。
 * @param imageFileType 要保存的照片的图像文件类型。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED：不支持该操作。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAssetChangeRequest_SaveCameraPhoto(OH_MediaAssetChangeRequest* changeRequest,
    MediaLibrary_ImageFileType imageFileType);

/**
 * @brief 丢弃相机拍摄的照片资源。
 * 
 * @param changeRequest {@link OH_MediaAssetChangeRequest}实例。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 *     <br>MEDIA_LIBRARY_OPERATION_NOT_SUPPORTED：不支持该操作。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAssetChangeRequest_DiscardCameraPhoto(OH_MediaAssetChangeRequest* changeRequest);

/**
 * @brief 释放{@link OH_MediaAssetChangeRequest}实例。
 * 
 * @param changeRequest {@link OH_MediaAssetChangeRequest}实例。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAssetChangeRequest_Release(OH_MediaAssetChangeRequest* changeRequest);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ASSET_CHANGE_REQUEST_H
/** @} */