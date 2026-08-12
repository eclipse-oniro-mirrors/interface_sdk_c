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
 * @addtogroup Drm
 * @{
 *
 * @brief Provides APIs of Drm.
 * @kit DrmKit
 * @since 11
 * @version 1.0
 */
/**
 * @file native_mediakeysystem.h
 * @brief 定义Drm MediaKeySystem API。提供以下功能：
 * 查询是否支持特定的drm、创建媒体密钥会话、获取和设置配置、获取统计信息、获取内容保护级别、生成提供请求、处理提供响应、事件监听、获取内容防护级别、管理离线媒体密钥等。
 * 
 * @library libnative_drm.z.so
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */

#ifndef OHOS_DRM_NATIVE_MEDIA_KEY_SYSTEM_H
#define OHOS_DRM_NATIVE_MEDIA_KEY_SYSTEM_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "native_drm_err.h"
#include "native_drm_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief MediaKeySystem事件触发时将调用的回调函数，不返回MediaKeySystem实例，适用于单个MediaKeySystem场景。
 * 
 * @param eventType 事件类型。
 * @param info 事件信息。
 * @param infoLen 事件信息长度。
 * @param extra 增量信息。
 * @return DRM_ERR_OK：执行成功。
 * DRM_ERR_INVALID_VAL：输入参数无效。
 * @since 11
 * @version 1.0
 */
typedef  Drm_ErrCode (*MediaKeySystem_Callback)(DRM_EventType eventType, uint8_t *info,
    int32_t infoLen, char *extra);

/**
 * @brief MediaKeySystem事件触发时将调用的回调函数，返回MediaKeySystem实例，适用于多个MediaKeySystem场景。
 * 
 * @param mediaKeySystem MediaKeySystem实例。
 * @param eventType 事件类型。
 * @param info 事件信息。
 * @param infoLen 事件信息长度。
 * @param extra 增量信息。
 * @return DRM_ERR_OK：执行成功。
 * DRM_ERR_INVALID_VAL：输入参数无效。
 * @since 12
 * @version 1.0
 */
typedef Drm_ErrCode (*OH_MediaKeySystem_Callback)(MediaKeySystem *mediaKeySystem, DRM_EventType eventType,
    uint8_t *info, int32_t infoLen, char *extra);

/**
 * @brief Set media key system event callback.
 * @param mediaKeySystem Media key system instance.
 * @param callback Callback to be set to the media key system.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - If the mediaKeySystem instance is nullptr or invalid,
 *         or the mediaKeySession is nullptr or invalid.
 * @since 12
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_SetCallback(MediaKeySystem *mediaKeySystem, OH_MediaKeySystem_Callback callback);

/**
 * @brief Acquire supported media key systems' name and uuid.
 * @param descs Array used to save media key systems' name and uuid.
 * @param count Used to indicate count of struct DRM_MediaKeySystemDescription.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - Probably caused by:
 *         1.the description or the count is nullptr.
 *         2. the size of the description array is smaller than the actual number obtained.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 12
 * @version 1.0
 */
Drm_ErrCode  OH_MediaKeySystem_GetMediaKeySystems(DRM_MediaKeySystemDescription *descs, uint32_t *count);

/**
 * @brief 查询设备是否支持对应的DRM解决方案。
 * 
 * @param name 输入参数，DRM解决方案名称。可通过{@link OH_MediaKeySystem_GetMediaKeySystems}接口获取设备支持的DRM解决方案名称。示例："com.clearplay.drm"。
 * @return 返回是否支持指定的DRM解决方案。true表示支持，false表示不支持。
 * @since 11
 * @version 1.0
 */
bool OH_MediaKeySystem_IsSupported(const char *name);
/**
 * @brief 查询设备是否支持对应的DRM解决方案名称及媒体类型。可通过{@link OH_MediaKeySystem_IsSupported}接口先确认name参数对应的DRM解决方案是否是设备支持的。
 * 
 * @param name 输入参数，DRM解决方案名称。可通过{@link OH_MediaKeySystem_GetMediaKeySystems}接口获取设备支持的DRM解决方案名称。
 * @param mimeType 输入参数，媒体类型，支持的媒体类型取决于DRM解决方案，如：video/avc、video/hevc。
 * @return 表示是否支持指定的DRM解决方案及媒体类型。当name和mimeType都支持时返回true，否则返回false。当name或mimeType参数为空或无效时返回false。
 * @since 11
 * @version 1.0
 */
bool OH_MediaKeySystem_IsSupported2(const char *name, const char *mimeType);
/**
 * @brief 查询设备是否支持对应的DRM解决方案、媒体类型、内容保护级别。可通过{@link OH_MediaKeySystem_IsSupported2}接口先判断mimeType是否支持。
 * 
 * @param name 输入参数，DRM解决方案名称。可通过{@link OH_MediaKeySystem_GetMediaKeySystems}接口获取设备支持的DRM解决方案名称。
 * @param mimeType 输入参数，媒体类型，支持的媒体类型取决于DRM解决方案，如：video/avc、video/hevc。
 * @param contentProtectionLevel 输入参数，内容保护级别。
 * @return 表示是否支持指定的DRM解决方案、媒体类型以及内容保护级别。当name、mimeType和contentProtectionLevel都支持时返回true，否则返回false。
 * @since 11
 * @version 1.0
 */
bool OH_MediaKeySystem_IsSupported3(const char *name, const char *mimeType,
    DRM_ContentProtectionLevel contentProtectionLevel);

/**
 * @brief Creates a media key system instance from the name.
 * @param name Specifies which drm system will be created by name.
 * @param mediaKeySystem Media key system instance.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - Probably caused by:
 *         1. the name is nullptr or the length of name is zero.
 *         2. the mediaKeySystem is nullptr.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 *         {@link DRM_ERR_SERVICE_DIED} 24700507 - Service died.
 *         {@link DRM_ERR_MAX_SYSTEM_NUM_REACHED} 24700510 - The maximum number of media key systems is reached.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_Create(const char *name, MediaKeySystem **mediaKeySystem);
/**
 * @brief Set media key system configuration value by name.
 * @param mediaKeySystem Media key system instance.
 * @param configName Configuration name string.
 * @param value Configuration value string to be set.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_SetConfigurationString(MediaKeySystem *mediaKeySystem,
    const char *configName, const char *value);
/**
 * @brief Get media key system configuration value by name.
 * @param mediaKeySystem Media key system instance.
 * @param configName Configuration name string.
 * @param value Configuration value string to be get.
 * @param valueLen Configuration value string len for in buffer.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_NO_MEMORY} 24700501 - Memory errors.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetConfigurationString(MediaKeySystem *mediaKeySystem,
    const char *configName, char *value, int32_t valueLen);
/**
 * @brief Set media key system configuration value by name.
 * @param mediaKeySystem Media key system instance.
 * @param configName Configuration name string.
 * @param value Configuration value in byte array to be set.
 * @param valueLen Value array len.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_NO_MEMORY} 24700501 - Memory errors.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_SetConfigurationByteArray(MediaKeySystem *mediaKeySystem,
    const char *configName, uint8_t *value, int32_t valueLen);
/**
 * @brief Get media key system configuration value by name.
 * @param mediaKeySystem Media key system instance.
 * @param configName Configuration name string.
 * @param value Configuration value in byte array to be get.
 * @param valueLen Configuration value len for in buffer and out data.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_NO_MEMORY} 24700501 - Memory errors.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetConfigurationByteArray(MediaKeySystem *mediaKeySystem,
    const char *configName, uint8_t *value, int32_t *valueLen);
/**
 * @brief Get media key system statistics info.
 * @param mediaKeySystem Media key system instance.
 * @param statistics Statistic info gotten.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_NO_MEMORY} 24700501 - Memory errors.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetStatistics(MediaKeySystem *mediaKeySystem, DRM_Statistics *statistics);
/**
 * @brief Get the max content protection level media key system supported.
 * @param mediaKeySystem Media key system instance.
 * @param contentProtectionLevel Content protection level.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetMaxContentProtectionLevel(MediaKeySystem *mediaKeySystem,
    DRM_ContentProtectionLevel *contentProtectionLevel);
/**
 * @brief Set media key system event callback.
 * @param mediaKeySystem Media key system instance.
 * @param callback Callback to be set to the media key system.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_SetMediaKeySystemCallback(MediaKeySystem *mediaKeySystem,
    MediaKeySystem_Callback callback);

/**
 * @brief Create a media key session instance.
 * @param mediaKeySystem Media key system instance which will create the media key session.
 * @param level Specifies the content protection level.
 * @param mediaKeySession Media key session instance.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_NO_MEMORY} 24700501 - Memory errors.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - Probably caused by:
 *         1. The parameter passed in is a null pointer or invalid.
 *         2. the level is beyond reasonable range.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 *         {@link DRM_ERR_SERVICE_DIED} 24700507 - Service died.
 *         {@link DRM_ERR_MAX_SESSION_NUM_REACHED} 24700511 - The maximum number of media key sessions is reached.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_CreateMediaKeySession(MediaKeySystem *mediaKeySystem,
    DRM_ContentProtectionLevel *level, MediaKeySession **mediaKeySession);

/**
 * @brief Generate a media key system provision request.
 * @param mediaKeySystem Media key system instance.
 * @param request Provision request data sent to provision server.
 * @param requestLen Provision request data len for in buffer and out data.
 * @param defaultUrl Provision server URL.
 * @param defaultUrlLen Provision server URL len for in buffer.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_NO_MEMORY} 24700501 - Memory errors.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GenerateKeySystemRequest(MediaKeySystem *mediaKeySystem, uint8_t *request,
    int32_t *requestLen, char *defaultUrl, int32_t defaultUrlLen);

/**
 * @brief Process a media key system provision response.
 * @param mediaKeySystem Media key system instance.
 * @param response The provision response will be processed.
 * @param responseLen The response len.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_ProcessKeySystemResponse(MediaKeySystem *mediaKeySystem,
    uint8_t *response, int32_t responseLen);

/**
 * @brief Get offline media key ids .
 * @param mediaKeySystem Media key system instance.
 * @param offlineMediaKeyIds Media key ids of all offline media keys.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_NO_MEMORY} 24700501 - Memory errors.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetOfflineMediaKeyIds(MediaKeySystem *mediaKeySystem,
    DRM_OfflineMediakeyIdArray *offlineMediaKeyIds);

/**
 * @brief Get offline media key status.
 * @param mediaKeySystem Media key system instance.
 * @param offlineMediaKeyId Offline media key identifier.
 * @param offlineMediaKeyIdLen Offline media key identifier len.
 * @param status The media key status gotten.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetOfflineMediaKeyStatus(MediaKeySystem *mediaKeySystem,
    uint8_t *offlineMediaKeyId, int32_t offlineMediaKeyIdLen, DRM_OfflineMediaKeyStatus *status);

/**
 * @brief Clear an offline media key by id.
 * @param mediaKeySystem Media key system instance.
 * @param offlineMediaKeyId Offline media key identifier.
 * @param offlineMediaKeyIdLen Offline media key identifier len.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_ClearOfflineMediaKeys(MediaKeySystem *mediaKeySystem,
    uint8_t *offlineMediaKeyId, int32_t offlineMediaKeyIdLen);

/**
 * @brief Get certificate status of media key system.
 * @param mediaKeySystem Media key system instance.
 * @param certStatus Status will be gotten.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetCertificateStatus(MediaKeySystem *mediaKeySystem,
    DRM_CertificateStatus *certStatus);

/**
 * @brief Destroy a media key system instance.
 * @param mediaKeySystem Specifies which media key system instance will be destroyed.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_Destroy(MediaKeySystem *mediaKeySystem);

#ifdef __cplusplus
}
#endif

#endif // OHOS_DRM_NATIVE_MEDIA_KEY_SYSTEM_H
/** @} */
