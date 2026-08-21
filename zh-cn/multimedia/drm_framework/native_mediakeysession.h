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
 * @file native_mediakeysession.h
 * @brief 定义DRM MediaKeySession API。提供以下功能：\n
 * 生成媒体密钥请求、处理媒体密钥响应、事件监听、获取内容保护级别、检查媒体密钥状态、删除媒体密钥等。
 * 
 * @library libnative_drm.so
 * @include <multimedia/drm_framework/native_mediakeysession.h>
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
 *     <br>DRM_ERR_INVALID_VAL：参数检查失败。
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
     * 正常事件回调函数指针，用于处理密钥过期等常规事件。当MediaKeySession状态发生常规变化时，系统会调用此回调函数通知应用。
     */
    MediaKeySession_EventCallback eventCallback;
    /**
     * 密钥更改事件回调函数指针，用于处理密钥状态变化事件。当密钥状态发生变化（如密钥可用、密钥过期等）时，系统会调用此回调函数通知应用，回调参数中包含变化的密钥信息。
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
 *     <br>DRM_ERR_INVALID_VAL：参数检查失败。
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
     * 正常事件回调函数指针，用于处理密钥过期等常规事件。当MediaKeySession状态发生常规变化时，系统会调用此回调函数通知应用。
     */
    OH_MediaKeySession_EventCallback eventCallback;
    /**
     * 密钥更改事件回调函数指针，用于处理密钥状态变化事件。当密钥状态发生变化（如密钥可用、密钥过期等）时，系统会调用此回调函数通知应用，回调参数中包含变化的密钥信息。
     */
    OH_MediaKeySession_KeyChangeCallback keyChangeCallback;
} OH_MediaKeySession_Callback;

/**
 * @brief 生成媒体密钥请求。
 * @param mediaKeySession 输入参数，MediaKeySession实例。
 * @param info 媒体密钥请求信息。
 * @param mediaKeyRequest 媒体密钥请求。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_NO_MEMORY：内存不足，内存分配失败。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySession为空指针或无效，或输入参数info为空指针，或输入参数mediaKeyRequest为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_GenerateMediaKeyRequest(MediaKeySession *mediaKeySession,
    DRM_MediaKeyRequestInfo *info, DRM_MediaKeyRequest *mediaKeyRequest);

/**
 * @brief 处理媒体密钥请求响应。
 * @param mediaKeySession MediaKeySession实例。
 * @param response 媒体密钥请求响应。
 * @param responseLen 媒体密钥请求响应长度。
 * @param offlineMediaKeyId 离线媒体密钥标识。
 * @param offlineMediaKeyIdLen 离线媒体密钥标识的长度。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_NO_MEMORY：内存不足，内存分配失败。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySession为空指针或无效，或其他指针类型输入参数为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_ProcessMediaKeyResponse(MediaKeySession *mediaKeySession,
    uint8_t *response, int32_t responseLen, uint8_t *offlineMediaKeyId, int32_t *offlineMediaKeyIdLen);

/**
 * @brief 检查媒体密钥状态。
 * @param mediaKeySession 输入参数，必填，MediaKeySession实例。
 * @param mediaKeyStatus 输出参数，必填，媒体密钥状态。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_NO_MEMORY：内存不足，内存分配失败。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySession为空指针或无效，或输入参数mediaKeyStatus为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_CheckMediaKeyStatus(MediaKeySession *mediaKeySession,
    DRM_MediaKeyStatus *mediaKeyStatus);

/**
 * @brief 清除当前会话的媒体密钥。
 * @param mediaKeySession MediaKeySession实例。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySession为空指针或无效。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_ClearMediaKeys(MediaKeySession *mediaKeySession);

/**
 * @brief 生成离线媒体密钥释放请求。
 * @param mediaKeySession 输入参数，MediaKeySession实例。
 * @param offlineMediaKeyId 输入参数，离线媒体密钥标识。取值范围为[1, 64]，单位为字节。
 * @param offlineMediaKeyIdLen 输入参数，离线媒体密钥标识长度，取值范围为[1, 64]。
 * @param releaseRequest 输出参数，离线媒体密钥释放请求。
 * @param releaseRequestLen 输出参数，离线媒体密钥释放请求长度。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_NO_MEMORY：内存不足，内存分配失败。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySession为空指针或无效，或其他指针类型输入参数为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误或设备上的DRM解决方案不支持离线媒体密钥释放，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_GenerateOfflineReleaseRequest(MediaKeySession *mediaKeySession,
    uint8_t *offlineMediaKeyId, int32_t offlineMediaKeyIdLen, uint8_t *releaseRequest,
    int32_t *releaseRequestLen);

/**
 * @brief 处理离线媒体密钥释放请求响应。
 * @param mediaKeySession MediaKeySession实例。
 * @param offlineMediaKeyId 离线媒体密钥标识。
 * @param offlineMediaKeyIdLen 离线媒体密钥标识长度。
 * @param releaseResponse 媒体密钥释放请求响应。
 * @param releaseResponseLen 媒体密钥释放请求响应长度。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySession为空指针或无效，或其他指针类型输入参数为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误或设备上的DRM解决方案不支持离线媒体密钥释放，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_ProcessOfflineReleaseResponse(MediaKeySession *mediaKeySession,
    uint8_t *offlineMediaKeyId, int32_t offlineMediaKeyIdLen, uint8_t *releaseResponse,
    int32_t releaseResponseLen);

/**
 * @brief 恢复离线媒体密钥到当前会话。
 * @param mediaKeySession MediaKeySession实例。
 * @param offlineMediaKeyId 离线媒体密钥标识。
 * @param offlineMediaKeyIdLen 离线媒体密钥标识长度。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySession为空指针或无效，或其他指针类型输入参数为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_RestoreOfflineMediaKeys(MediaKeySession *mediaKeySession,
    uint8_t *offlineMediaKeyId, int32_t offlineMediaKeyIdLen);

/**
 * @brief 获取会话的内容保护级别。
 * @param mediaKeySession MediaKeySession实例。
 * @param contentProtectionLevel 内容保护级别。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySession为空指针或无效，或输入参数contentProtectionLevel为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_GetContentProtectionLevel(MediaKeySession *mediaKeySession,
    DRM_ContentProtectionLevel *contentProtectionLevel);

/**
 * @brief 是否需要安全解码。
 * @param mediaKeySession MediaKeySession实例。
 * @param mimeType 媒体类型，支持的媒体类型取决于DRM解决方案，如：video/avc、video/hevc。
 * @param status 安全解码模块状态。true表示需要安全解码模块，false表示不需要安全解码模块。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySession为空指针或无效，或其他指针类型输入参数为空指针。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_RequireSecureDecoderModule(MediaKeySession *mediaKeySession,
    const char *mimeType, bool *status);

/**
 * @brief 设置MediaKeySession事件回调。该回调不返回MediaKeySession实例，适用于单个MediaKeySession场景。
 * @param mediaKeySession MediaKeySession实例。
 * @param callback 输入参数，MediaKeySession的回调结构体。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySession为空指针或无效，或输入参数callback为空指针。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_SetMediaKeySessionCallback(MediaKeySession *mediaKeySession,
    MediaKeySession_Callback *callback);

/**
 * @brief 设置MediaKeySession事件回调。该回调返回MediaKeySession实例，适用于多个MediaKeySession场景。
 * @param mediaKeySession MediaKeySession实例。
 * @param callback 输入参数，MediaKeySession的回调结构体。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySession为空指针或无效，或输入参数callback为空指针。
 * @since 12
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_SetCallback(MediaKeySession *mediaKeySession,
    OH_MediaKeySession_Callback *callback);

/**
 * @brief 销毁MediaKeySession实例。
 * @param mediaKeySession MediaKeySession实例。
 * @return DRM_ERR_OK：执行成功。
 *     <br>DRM_ERR_INVALID_VAL：输入参数mediaKeySession为空指针或无效。
 *     <br>DRM_ERR_UNKNOWN：发生内部错误，请查看日志详细信息。
 * @since 11
 * @version 1.0
 */
Drm_ErrCode OH_MediaKeySession_Destroy(MediaKeySession *mediaKeySession);

#ifdef __cplusplus
}
#endif

#endif // OHOS_DRM_NATIVE_MEDIA_KEY_SESSION_H
