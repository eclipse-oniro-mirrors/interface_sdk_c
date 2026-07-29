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
 * @file native_drm_common.h
 *
 * @brief 定义DRM数据类型。
 * 
 * @library libnative_drm.z.so
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */

#ifndef NATIVE_DRM_COMMON_H
#define NATIVE_DRM_COMMON_H

#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  *
  * @brief 监听事件类型。
  * 
  * @since 11
  * @version 1.0
*/
typedef enum DRM_EventType {
    /**
     * DRM基础事件。
     */
    EVENT_DRM_BASE = 200,
    /**
     * 设备证书请求事件。
     */
    EVENT_PROVISION_REQUIRED = 201,
    /**
     * 密钥请求事件。
     */
    EVENT_KEY_REQUIRED = 202,
    /**
     * 密钥过期事件。
     */
    EVENT_KEY_EXPIRED = 203,
    /**
     * DRM解决方案自定义事件。
     */
    EVENT_VENDOR_DEFINED = 204,
    /**
     * 密钥过期更新事件。
     */
    EVENT_EXPIRATION_UPDATE = 206,
  } DRM_EventType;

/**
 * @brief 内容保护级别。
 * 
 * @since 11
 * @version 1.0
 */
typedef enum DRM_ContentProtectionLevel {
    /**
     * 未知级别。
     */
    CONTENT_PROTECTION_LEVEL_UNKNOWN = 0,
    /**
     * 软件安全级别。
     */
    CONTENT_PROTECTION_LEVEL_SW_CRYPTO,
    /**
     * 硬件安全级别。
     */
    CONTENT_PROTECTION_LEVEL_HW_CRYPTO,
    /**
     * 硬件增强级别。
     */
    CONTENT_PROTECTION_LEVEL_ENHANCED_HW_CRYPTO,
    /**
     * 最大安全级别。
     */
    CONTENT_PROTECTION_LEVEL_MAX,
} DRM_ContentProtectionLevel;

/**
 * @brief 媒体密钥类型。
 * 
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */
typedef enum DRM_MediaKeyType {
    /**
     * 离线。
     */
    MEDIA_KEY_TYPE_OFFLINE = 0,
    /**
     * 在线。
     */
    MEDIA_KEY_TYPE_ONLINE,
} DRM_MediaKeyType;

/**
 * @brief 媒体密钥请求类型。
 * 
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */
typedef enum DRM_MediaKeyRequestType {
    /**
     * 未知请求类型。
     */
    MEDIA_KEY_REQUEST_TYPE_UNKNOWN = 0,
    /**
     * 初始化请求。
     */
    MEDIA_KEY_REQUEST_TYPE_INITIAL,
    /**
     * 续订请求。
     */
    MEDIA_KEY_REQUEST_TYPE_RENEWAL,
    /**
     * 释放请求。
     */
    MEDIA_KEY_REQUEST_TYPE_RELEASE,
    /**
     * 无请求。
     */
    MEDIA_KEY_REQUEST_TYPE_NONE,
    /**
     * 更新请求。
     */
    MEDIA_KEY_REQUEST_TYPE_UPDATE,
} DRM_MediaKeyRequestType;

/**
 * @brief 离线媒体密钥状态。
 * 
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */
typedef enum DRM_OfflineMediaKeyStatus {
    /**
     * 未知状态。
     */
    OFFLINE_MEDIA_KEY_STATUS_UNKNOWN = 0,
    /**
     * 可用状态。
     */
    OFFLINE_MEDIA_KEY_STATUS_USABLE,
    /**
     * 失活状态。
     */
    OFFLINE_MEDIA_KEY_STATUS_INACTIVE,
} DRM_OfflineMediaKeyStatus;

/**
 * @brief 设备DRM证书状态。
 * 
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */
typedef enum DRM_CertificateStatus {
    /**
     * 设备已安装设备DRM证书。
     */
    CERT_STATUS_PROVISIONED = 0,
    /**
     * 设备未安装设备DRM证书或证书状态异常。
     */
    CERT_STATUS_NOT_PROVISIONED,
    /**
     * 设备DRM证书过期。
     */
    CERT_STATUS_EXPIRED,
    /**
     * 设备DRM证书无效。
     */
    CERT_STATUS_INVALID,
    /**
     * 设备DRM证书不可用。
     */
    CERT_STATUS_UNAVAILABLE,
} DRM_CertificateStatus;

/**
 * @brief 媒体密钥请求可选数据的最大数量。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_REQUEST_OPTION_COUNT 16
/**
 * @brief 媒体密钥请求可选数据名称的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_REQUEST_OPTION_NAME_LEN 64
/**
 * @brief 媒体密钥请求可选数据的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_REQUEST_OPTION_DATA_LEN 128
/**
 * @brief 媒体密钥请求初始化数据的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_INIT_DATA_LEN 2048
/**
 * @brief 媒体mimetype的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MIMETYPE_LEN 64

/**
 * @brief 媒体密钥请求信息。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct DRM_MediaKeyRequestInfo {
    /**
     * 密钥类型。
     */
    DRM_MediaKeyType type;
    /**
     * 初始数据长度。
     */
    int32_t initDataLen;
    /**
     * PSSH info.
     */
    uint8_t initData[MAX_INIT_DATA_LEN];
    /**
     * Media content mime type.
     */
    char mimeType[MAX_MIMETYPE_LEN];
    /**
     * 选项数据计数。
     */
    uint32_t optionsCount;
    /**
     * Options name the application set to drm framework.
     */
    char optionName[MAX_MEDIA_KEY_REQUEST_OPTION_COUNT][MAX_MEDIA_KEY_REQUEST_OPTION_NAME_LEN];
    /**
     * Options data the application set to drm framework.
     */
    char optionData[MAX_MEDIA_KEY_REQUEST_OPTION_COUNT][MAX_MEDIA_KEY_REQUEST_OPTION_DATA_LEN];
} DRM_MediaKeyRequestInfo;

/**
 * @brief 媒体密钥请求数据的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_REQUEST_DATA_LEN 8192
/**
 * @brief URL最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_DEFAULT_URL_LEN 2048
/**
 * @brief 媒体密钥请求。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct DRM_MediaKeyRequest {
    /**
     * 媒体密钥请求类型。
     */
    DRM_MediaKeyRequestType type;
    /**
     * 媒体密钥请求数据长度。
     */
    int32_t dataLen;
    /**
     * Media key request data sent to media key server.
     */
    uint8_t data[MAX_MEDIA_KEY_REQUEST_DATA_LEN];
    /**
     * Media key server URL.
     */
    char defaultUrl[MAX_DEFAULT_URL_LEN];
} DRM_MediaKeyRequest;

/**
 * @brief 度量记录的最大数量。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_STATISTICS_COUNT 10
/**
 * @brief 度量记录名称的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_STATISTICS_NAME_LEN 64
/**
 * @brief 度量记录缓冲区的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_STATISTICS_BUFFER_LEN 256

/**
 * @brief MediaKeySystem的度量信息。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct DRM_Statistics {
    /* Statistics count. */
    uint32_t statisticsCount;
    /* Statistics name. */
    char statisticsName[MAX_STATISTICS_COUNT][MAX_STATISTICS_NAME_LEN];
    /* Statistics description. */
    char statisticsDescription[MAX_STATISTICS_COUNT][MAX_STATISTICS_BUFFER_LEN];
} DRM_Statistics;

/**
 * @brief 离线媒体密钥标识的最大数量。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_OFFLINE_MEDIA_KEY_ID_COUNT 512
/**
 * @brief 离线媒体密钥标识的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_OFFLINE_MEDIA_KEY_ID_LEN 64

/**
 * @brief 离线媒体密钥ID数组。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct DRM_OfflineMediakeyIdArray {
    /* Ids count. */
    uint32_t idsCount;
    /* Ids len. */
    int32_t idsLen[MAX_OFFLINE_MEDIA_KEY_ID_COUNT];
    /* Ids. */
    uint8_t ids[MAX_OFFLINE_MEDIA_KEY_ID_COUNT][MAX_OFFLINE_MEDIA_KEY_ID_LEN];
} DRM_OfflineMediakeyIdArray;

/**
 * @brief 密钥信息的最大数量。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_KEY_INFO_COUNT 64
/**
 * @brief 密钥标识的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_KEY_ID_LEN 16
/**
 * @brief 密钥状态值的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_KEY_STATUS_VALUE_LEN 128

/**
 * @brief 媒体密钥信息。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct DRM_KeysInfo {
    /* Keys count. */
    uint32_t keysInfoCount;
    /* Key id. */
    uint8_t keyId[MAX_KEY_INFO_COUNT][MAX_KEY_ID_LEN];
    /* Key status value. */
    char statusValue[MAX_KEY_INFO_COUNT][MAX_KEY_STATUS_VALUE_LEN];
} DRM_KeysInfo;

/**
 * @brief 媒体密钥状态的最大数量。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_STATUS_COUNT 64
/**
 * @brief 媒体密钥状态名称的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_STATUS_NAME_LEN 64
/**
 * @brief 媒体密钥状态值的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_STATUS_VALUE_LEN 256

/**
 * @brief 媒体密钥状态。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct DRM_MediaKeyStatus {
    /* Status count. */
    uint32_t statusCount;
    /* Status name. */
    char statusName[MAX_MEDIA_KEY_STATUS_COUNT][MAX_MEDIA_KEY_STATUS_NAME_LEN];
    /* Status value. */
    char statusValue[MAX_MEDIA_KEY_STATUS_COUNT][MAX_MEDIA_KEY_STATUS_VALUE_LEN];
} DRM_MediaKeyStatus;

/**
 * @brief DRM解决方案的UUID长度。
 * 
 * @since 11
 * @version 1.0
 */
#define DRM_UUID_LEN 16
/**
 * @brief PSSH（Protected System Specific Header）信息的最大长度。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_PSSH_DATA_LEN 2048

/**
 * @brief DRM内容保护系统专用头（Protection System Specific Header）信息。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct DRM_PsshInfo {
    /**
     * Uuid.
     */
    uint8_t uuid[DRM_UUID_LEN];
    /**
     * PSSH数据长度。
     */
    int32_t dataLen;
    /**
     * uint8_t PSSH data.
     */
    uint8_t data[MAX_PSSH_DATA_LEN];
} DRM_PsshInfo;

/**
 * @brief PSSH（Protected System Specific Header）信息的最大数量。
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_PSSH_INFO_COUNT 8

/**
 * @brief 加密媒体内容的DRM信息。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct DRM_MediaKeySystemInfo {
    /* PSSH count. */
    uint32_t psshCount;
    /* PSSH info. */
    DRM_PsshInfo psshInfo[MAX_PSSH_INFO_COUNT];
} DRM_MediaKeySystemInfo;

/**
* @brief 应用为从媒体源获取DRM信息而设置的回调函数。
* 
* @since 11
* @version 1.0
*/
typedef void (*DRM_MediaKeySystemInfoCallback)(DRM_MediaKeySystemInfo *mediaKeySystemInfo);

/**
 * @brief MediaKeySystem结构。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct MediaKeySystem MediaKeySystem;

/**
 * @brief MediaKeySession结构。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct MediaKeySession MediaKeySession;
/**
 * @brief MediaKeySystem名称的最大长度。
 * 
 * @since 12
 * @version 1.0
 */
#define MAX_MEDIA_KEY_SYSTEM_NAME_LEN 128

/**
 * @brief MediaKeySystem的最大数量。
 * 
 * @since 12
 * @version 1.0
 */
#define MAX_MEDIA_KEY_SYSTEM_NUM 8

/**
 * @brief DRM解决方案名称及其UUID的列表。
 * 
 * @since 12
 * @version 1.0
 */
typedef struct DRM_MediaKeySystemDescription {
    /* Name of DRM plugin. */
    char name[MAX_MEDIA_KEY_SYSTEM_NAME_LEN];
    /* uuid. */
    uint8_t uuid[DRM_UUID_LEN];
} DRM_MediaKeySystemDescription;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_DRM_COMMON_H
/** @} */
