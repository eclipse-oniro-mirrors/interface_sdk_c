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
 * @file media_access_helper_capi.h
 *
 * @brief 定义与相册管理模块相关的API。
 *
 * @kit MediaLibraryKit
 * @syscap SystemCapability.FileManagement.PhotoAccessHelper.Core
 * @library libmedia_asset_manager.so
 * @since 12
 */

#ifndef MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ACCESS_HELPER_H
#define MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ACCESS_HELPER_H

#include "media_asset_base_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 发起应用资产或相册的更改请求。
 *
 * @permission ohos.permission.WRITE_IMAGEVIDEO
 * @param changeRequest 变更请求实例。
 * @return MEDIA_LIBRARY_OK：方法调用成功。
 *     <br>MEDIA_LIBRARY_PARAMETER_ERROR：参数错误。可能的原因：
 *     <br>1. 未指定强制参数。
 *     <br>2. 参数类型不正确。
 *     <br>3. 参数验证失败。
 *     <br>MEDIA_LIBRARY_PERMISSION_DENIED：没有权限。
 *     <br>MEDIA_LIBRARY_INTERNAL_SYSTEM_ERROR：内部系统错误。
 * @since 12
 */
MediaLibrary_ErrorCode OH_MediaAccessHelper_ApplyChanges(OH_MediaAssetChangeRequest* changeRequest);

#ifdef __cplusplus
}
#endif

#endif // MULTIMEDIA_MEDIA_LIBRARY_NATIVE_MEDIA_ACCESS_HELPER_H
/** @} */