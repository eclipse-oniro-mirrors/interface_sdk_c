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
 * @brief 提供数字版权保护能力的API。
 *
 * 开发者可根据开发需求，参考开发指南及样例：
 *
 * - [数字版权保护(C/C++)](docroot://media/drm/drm-c-dev-guide.md)
 * - [基于AVCodec播放DRM节目(C/C++)](docroot://media/drm/drm-avcodec-integration.md)
 *
 * @kit DrmKit
 * @since 11
 * @version 1.0
 */
/**
 * @file native_mediakeysystem.h
 * @brief 定义DRM MediaKeySystem API。提供以下功能：\n
 * 查询是否支持特定的DRM、创建媒体密钥会话、获取和设置配置、获取统计信息、获取内容保护级别、生成提供请求、处理提供响应、事件监听、管理离线媒体密钥等。
 * 
 * @library libnative_drm.so
 * @include <multimedia/drm_framework/native_mediakeysystem.h>
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
 *     <br>DRM_ERR_INVALID_VAL：输入参数无效。
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
 *     <br>DRM_ERR_INVALID_VAL：输入参数无效。
 * @since 12
 * @version 1.0
 */
typedef Drm_ErrCode (*OH_MediaKeySystem_Callback)(MediaKeySystem *mediaKeySystem, DRM_EventType eventType,
    uint8_t *info, int32_t infoLen, char *extra);

/**
 * @brief 设置MediaKeySystem事件回调。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param callback 回调函数。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效。
 * @since 12
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_SetCallback(MediaKeySystem *mediaKeySystem, OH_MediaKeySystem_Callback callback);

/**
 * @brief 获取设备支持的DRM解决方案的名称和唯一标识的列表。
 * @param descs DRM解决方案名称和唯一标识的列表。
 * @param count DRM解决方案名称和唯一标识的列表长度。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：
 *     <br>输入参数descs为空指针。
 *     <br>输入参数count为空指针。
 *     <br>输入参数descs长度不足。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
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
 * @brief 创建MediaKeySystem实例。
 * @param name DRM解决方案名称。
 * @param mediaKeySystem MediaKeySystem实例。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：
 *     <br>输入参数name为空指针。
 *     <br>输入参数name长度为0。
 *     <br>输入参数mediaKeySystem为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 *     <br>DRM_ERR_SERVICE_DIED：服务死亡。
 *     <br>DRM_ERR_MAX_SYSTEM_NUM_REACHED：已创建的MediaKeySystem数量达到最大限制（64个）。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_Create(const char *name, MediaKeySystem **mediaKeySystem);
/**
 * @brief 设置字符串类型的配置属性。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param configName 字符串类型配置属性名，不能为空，具体支持的属性名由设备上DRM解决方案决定。
 * @param value 字符串类型配置属性值，不能为空，具体支持的属性值由设备上DRM解决方案决定。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，输入参数configName为空指针，或输入参数value为空指针。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_SetConfigurationString(MediaKeySystem *mediaKeySystem,
    const char *configName, const char *value);
/**
 * @brief 获取字符串类型配置属性值。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param configName 字符串类型配置名。
 * @param value 字符串类型配置值，用于存储获取的配置属性值。该参数不能为空，具体支持的取值由设备上DRM解决方案决定。
 * @param valueLen 字符串类型配置值长度。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_NO_MEMORY：内存不足，内存分配失败。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，输入参数configName为空指针，或输入参数value为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetConfigurationString(MediaKeySystem *mediaKeySystem,
    const char *configName, char *value, int32_t valueLen);
/**
 * @brief 设置字符数组类型的配置属性值。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param configName 字符数组类型配置属性名称，不能为空，具体支持的属性名由设备上DRM解决方案决定。
 * @param value 字符数组类型配置属性值，不能为空，具体支持的属性值由设备上DRM解决方案决定。
 * @param valueLen 字符数组类型配置属性值长度。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_NO_MEMORY：内存不足，内存分配失败。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，输入参数configName为空指针，或输入参数value为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_SetConfigurationByteArray(MediaKeySystem *mediaKeySystem,
    const char *configName, uint8_t *value, int32_t valueLen);
/**
 * @brief 获取字符数组类型配置属性值。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param configName 字符数组类型配置属性名称，不能为空，具体支持的属性名由设备上DRM解决方案决定。
 * @param value 字符数组类型配置属性，用于存储获取的配置属性值。该参数不能为空，具体支持的取值由设备上DRM解决方案决定。
 * @param valueLen 字符数组类型配置属性长度。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_NO_MEMORY：内存不足，内存分配失败。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，输入参数configName为空指针，输入参数value为空指针，或valueLen为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetConfigurationByteArray(MediaKeySystem *mediaKeySystem,
    const char *configName, uint8_t *value, int32_t *valueLen);
/**
 * @brief 获取度量记录。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param statistics 度量记录。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_NO_MEMORY：内存不足，内存分配失败。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，或输入参数statistics为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetStatistics(MediaKeySystem *mediaKeySystem, DRM_Statistics *statistics);
/**
 * @brief 获取设备支持的最大内容保护级别。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param contentProtectionLevel 内容保护级别。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，或输入参数contentProtectionLevel为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetMaxContentProtectionLevel(MediaKeySystem *mediaKeySystem,
    DRM_ContentProtectionLevel *contentProtectionLevel);
/**
 * @brief 设置MediaKeySystem事件回调。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param callback 回调函数。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_SetMediaKeySystemCallback(MediaKeySystem *mediaKeySystem,
    MediaKeySystem_Callback callback);

/**
 * @brief 创建MediaKeySession会话实例。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param level 内容保护级别。可通过{@link OH_MediaKeySystem_GetMaxContentProtectionLevel}接口先获取设备支持的最大内容保护级别。
 * @param mediaKeySession MediaKeySession实例。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_NO_MEMORY：内存不足，内存分配失败。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，或输入参数level超出合理范围，或mediaKeySession为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 *     <br>DRM_ERR_SERVICE_DIED：服务死亡。
 *     <br>DRM_ERR_MAX_SESSION_NUM_REACHED：当前MediaKeySystem已创建的MediaKeySession数量达到最大限制（64个）。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_CreateMediaKeySession(MediaKeySystem *mediaKeySystem,
    DRM_ContentProtectionLevel *level, MediaKeySession **mediaKeySession);

/**
 * @brief 生成设备DRM证书请求。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param request 设备DRM证书请求。
 * @param requestLen 设备DRM证书请求的长度。
 * @param defaultUrl 设备DRM证书服务的URL。
 * @param defaultUrlLen 设备DRM证书服务的URL长度。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_NO_MEMORY：内存不足，内存分配失败。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，或其它指针类型输入参数为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GenerateKeySystemRequest(MediaKeySystem *mediaKeySystem, uint8_t *request,
    int32_t *requestLen, char *defaultUrl, int32_t defaultUrlLen);

/**
 * @brief 处理设备DRM证书请求响应。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param response 设备DRM证书请求响应。
 * @param responseLen 设备DRM证书请求响应长度。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，或输入参数response为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_ProcessKeySystemResponse(MediaKeySystem *mediaKeySystem,
    uint8_t *response, int32_t responseLen);

/**
 * @brief 获取离线媒体密钥标识列表，媒体密钥标识用于对离线媒体密钥的管理。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param offlineMediaKeyIds 离线媒体密钥的媒体密钥标识列表。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_NO_MEMORY：内存不足，内存分配失败。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，或输入参数offlineMediaKeyIds为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetOfflineMediaKeyIds(MediaKeySystem *mediaKeySystem,
    DRM_OfflineMediakeyIdArray *offlineMediaKeyIds);

/**
 * @brief 获取离线媒体密钥状态。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param offlineMediaKeyId 离线媒体密钥标识。
 * @param offlineMediaKeyIdLen 离线媒体密钥标识长度。
 * @param status 媒体密钥状态。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，或其它指针类型输入参数为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetOfflineMediaKeyStatus(MediaKeySystem *mediaKeySystem,
    uint8_t *offlineMediaKeyId, int32_t offlineMediaKeyIdLen, DRM_OfflineMediaKeyStatus *status);

/**
 * @brief 按ID清除离线媒体密钥。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param offlineMediaKeyId 离线媒体密钥标识。
 * @param offlineMediaKeyIdLen 离线媒体密钥标识长度。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，或输入参数offlineMediaKeyId为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_ClearOfflineMediaKeys(MediaKeySystem *mediaKeySystem,
    uint8_t *offlineMediaKeyId, int32_t offlineMediaKeyIdLen);

/**
 * @brief 获取设备DRM证书状态。
 * @param mediaKeySystem MediaKeySystem实例。
 * @param certStatus 设备DRM证书状态值。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效，或输入参数certStatus为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_GetCertificateStatus(MediaKeySystem *mediaKeySystem,
    DRM_CertificateStatus *certStatus);

/**
 * @brief 销毁MediaKeySystem实例。
 * @param mediaKeySystem MediaKeySystem实例。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySystem为空指针或无效。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySystem_Destroy(MediaKeySystem *mediaKeySystem);

#ifdef __cplusplus
}
#endif

#endif // OHOS_DRM_NATIVE_MEDIA_KEY_SYSTEM_H
/** @} */
