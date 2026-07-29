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
 * @file native_mediakeysession.h
 * @brief 定义Drm MediaKeySession API。提供以下功能：
 * 生成媒体密钥请求、处理媒体密钥响应、事件监听、获取内容保护级别、检查媒体密钥状态、删除媒体密钥等。
 * 
 * @library libnative_drm.z.so
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */

#ifndef OHOS_DRM_NATIVE_MEDIA_KEY_SESSION_H
#define OHOS_DRM_NATIVE_MEDIA_KEY_SESSION_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "native_drm_err.h"
#include "native_drm_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief MediaKeySession事件触发时将调用的回调函数，如密钥过期事件。
 * 
 * @param eventType 输入参数，事件类型。
 * @param info 输出参数，从媒体密钥会话获取的事件信息。
 * @param infoLen 输出参数，事件信息长度。
 * @param extra 输出参数，从媒体密钥会话中获得的额外信息。
 * @return 错误码。
 * @since 11
 * @version 1.0
 */
typedef  Drm_ErrCode (*MediaKeySession_EventCallback)(DRM_EventType eventType, uint8_t *info,
    int32_t infoLen, char *extra);

/**
 * @brief 密钥变更时将调用回调。
 * 
 * @param keysInfo 密钥信息。
 * @param newKeysAvailable 新密钥是否可用，true表示可用，false表示不可用。
 * @return DRM_ERR_OK：执行成功。
 * DRM_ERR_INVALID_VAL：参数检查失败。
 * @since 11
 * @version 1.0
 */
typedef  Drm_ErrCode (*MediaKeySession_KeyChangeCallback)(DRM_KeysInfo *keysInfo, bool newKeysAvailable);

/**
 * @brief MediaKeySession_Callback结构体，用于监听密钥过期、密钥更改等事件，不返回媒体密钥会话实例，适用于单媒体密钥会话解密场景。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct MediaKeySession_Callback {
    /**
     * 正常事件回调，如密钥过期等。
     */
    MediaKeySession_EventCallback eventCallback;
    /**
     * 密钥更改事件的密钥更改回调。
     */
    MediaKeySession_KeyChangeCallback keyChangeCallback;
} MediaKeySession_Callback;

/**
 * @brief 事件触发时将调用的回调函数。事件信息来源于媒体播放过程中的DRM事件，通过MediaKeySession实例触发。
 * 
 * @param mediaKeySession 输入参数，会话实例，用于标识事件来源。
 * @param eventType 输入参数，事件类型。
 * @param info 输出参数，事件信息，来源于DRM事件。
 * @param infoLen 输出参数，事件信息长度。
 * @param extra 输出参数，增量信息，来源于DRM事件。
 * @return 错误码。
 * @since 12
 * @version 1.0
 */
typedef Drm_ErrCode (*OH_MediaKeySession_EventCallback)(MediaKeySession *mediaKeySession, DRM_EventType eventType,
    uint8_t *info, int32_t infoLen, char *extra);

/**
 * @brief 密钥变更时将调用的回调。
 * 
 * @param mediaKeySession 媒体密钥会话实例。
 * @param keysInfo 密钥信息。
 * @param newKeysAvailable 新密钥是否可用，true表示可用，false表示不可用。
 * @return DRM_ERR_OK：执行成功。
 * DRM_ERR_INVALID_VAL：参数检查失败。
 * @since 12
 * @version 1.0
 */
typedef Drm_ErrCode (*OH_MediaKeySession_KeyChangeCallback)(MediaKeySession *mediaKeySession, DRM_KeysInfo *keysInfo,
    bool newKeysAvailable);

/**
 * @brief OH_MediaKeySession_Callback结构体，用于监听密钥过期、密钥更改等事件，返回媒体密钥会话实例，适用于多个媒体密钥会话的解密场景。
 * 
 * @since 12
 * @version 1.0
 */
typedef struct OH_MediaKeySession_Callback {
    /**
     * 正常事件回调，如密钥过期等。
     */
    OH_MediaKeySession_EventCallback eventCallback;
    /**
     * 密钥更改事件的密钥更改回调。
     */
    OH_MediaKeySession_KeyChangeCallback keyChangeCallback;
} OH_MediaKeySession_Callback;

/**
 * @brief Generate media key request.
 * @param mediaKeySession Media key session instance.
 * @param info Media key request info.
 * @param mediaKeyRequest Media key request.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_NO_MEMORY} 24700501 - Memory errors.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_GenerateMediaKeyRequest(MediaKeySession *mediaKeySession,
    DRM_MediaKeyRequestInfo *info, DRM_MediaKeyRequest *mediaKeyRequest);

/**
 * @brief Process media key response.
 * @param mediaKeySession Media key session instance.
 * @param response Media Key response.
 * @param responseLen Media Key response len.
 * @param offlineMediaKeyId Offline media key identifier.
 * @param offlineMediaKeyIdLen Offline media key identifier len for in buffer and out data.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_NO_MEMORY} 24700501 - Memory errors.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_ProcessMediaKeyResponse(MediaKeySession *mediaKeySession,
    uint8_t *response, int32_t responseLen, uint8_t *offlineMediaKeyId, int32_t *offlineMediaKeyIdLen);

/**
 * @brief Check media key status.
 * @param mediaKeySession Media key session instance.
 * @param mediaKeyStatus Media key status.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_NO_MEMORY} 24700501 - Memory errors.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_CheckMediaKeyStatus(MediaKeySession *mediaKeySession,
    DRM_MediaKeyStatus *mediaKeyStatus);

/**
 * @brief Clear media keys of the current session .
 * @param mediaKeySession Media key session instance.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_ClearMediaKeys(MediaKeySession *mediaKeySession);

/**
 * @brief Generate offline media key release request.
 * @param mediaKeySession Media key session instance.
 * @param offlineMediaKeyId Offline media key identifier.
 * @param offlineMediaKeyIdLen Offline media key identifier len.
 * @param releaseRequest Media Key release request.
 * @param releaseRequestLen Media Key release request len for in buffer and out data.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_NO_MEMORY} 24700501 - Memory errors.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_GenerateOfflineReleaseRequest(MediaKeySession *mediaKeySession,
    uint8_t *offlineMediaKeyId, int32_t offlineMediaKeyIdLen, uint8_t *releaseRequest,
    int32_t *releaseRequestLen);

/**
 * @brief Process offline media key release response.
 * @param mediaKeySession Media key session instance.
 * @param offlineMediaKeyId Offline media key identifier.
 * @param offlineMediaKeyIdLen Offline media key identifier len.
 * @param releaseResponse Media Key response.
 * @param releaseResponseLen Media Key response len.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_ProcessOfflineReleaseResponse(MediaKeySession *mediaKeySession,
    uint8_t *offlineMediaKeyId, int32_t offlineMediaKeyIdLen, uint8_t *releaseResponse,
    int32_t releaseResponseLen);

/**
 * @brief Restore offline media keys by ID.
 * @param mediaKeySession Media key session instance.
 * @param offlineMediaKeyId Offline media key identifier.
 * @param offlineMediaKeyIdLen Offline media key identifier len.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_RestoreOfflineMediaKeys(MediaKeySession *mediaKeySession,
    uint8_t *offlineMediaKeyId, int32_t offlineMediaKeyIdLen);

/**
 * @brief Get content protection level of the session.
 * @param mediaKeySession Media key session instance.
 * @param contentProtectionLevel Content protection level.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_GetContentProtectionLevel(MediaKeySession *mediaKeySession,
    DRM_ContentProtectionLevel *contentProtectionLevel);

/**
 * @brief Whether the encrypted content require a secure decoder or not.
 * @param mediaKeySession Media key session instance.
 * @param mimeType The media type.
 * @param status Whether secure decoder is required.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_RequireSecureDecoderModule(MediaKeySession *mediaKeySession,
    const char *mimeType, bool *status);

/**
 * @brief Set media key session event callback.
 * @param mediaKeySession Media key session instance.
 * @param callback Callback to be set to the media key session.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_SetMediaKeySessionCallback(MediaKeySession *mediaKeySession,
    MediaKeySession_Callback *callback);

/**
 * @brief Set media key session event callback.
 * @param mediaKeySession Media key session instance.
 * @param callback Callback to be set to the media key session.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 * @since 12
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_SetCallback(MediaKeySession *mediaKeySession,
    OH_MediaKeySession_Callback *callback);

/**
 * @brief Release the resource before the session going to be unused.
 * @param mediaKeySession Media key session instance.
 * @return {@link DRM_ERR_OK} 0 - Success.
 *         {@link DRM_ERR_INVALID_VAL} 24700503 - The parameter passed in is a null pointer or invalid.
 *         {@link DRM_ERR_UNKNOWN} 24700506 - Internal error occurred, it is recommended to check the logs.
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_Destroy(MediaKeySession *mediaKeySession);

#ifdef __cplusplus
}
#endif

#endif // OHOS_DRM_NATIVE_MEDIA_KEY_SESSION_H
