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
 * @brief The file declares the DRM data types.
 * 
 * @library libnative_drm.so
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
  * @brief Enumerates the types of events that can be subscribed to.
  * 
  * @since 11
  * @version 1.0
*/
typedef enum DRM_EventType {
    /**
     * DRM event.
     */
    EVENT_DRM_BASE = 200,
    /**
     * Event indicating that the application needs to request a device certificate.
     */
    EVENT_PROVISION_REQUIRED = 201,
    /**
     * Event indicating that the application needs to request a media key.
     */
    EVENT_KEY_REQUIRED = 202,
    /**
     * Event indicating that the media key expires.
     */
    EVENT_KEY_EXPIRED = 203,
    /**
     * Vendor-defined event.
     */
    EVENT_VENDOR_DEFINED = 204,
    /**
     * Event indicating that the media key is updated on expiry.
     */
    EVENT_EXPIRATION_UPDATE = 206,
  } DRM_EventType;

/**
 * @brief Enumerates the content protection levels.
 * 
 * @since 11
 * @version 1.0
 */
typedef enum DRM_ContentProtectionLevel {
    /**
     * Unknown level.
     */
    CONTENT_PROTECTION_LEVEL_UNKNOWN = 0,
    /**
     * Software-based content protection.
     */
    CONTENT_PROTECTION_LEVEL_SW_CRYPTO,
    /**
     * Hardware-based content protection.
     */
    CONTENT_PROTECTION_LEVEL_HW_CRYPTO,
    /**
     * Enhanced hardware-based content protection.
     */
    CONTENT_PROTECTION_LEVEL_ENHANCED_HW_CRYPTO,
    /**
     * Maximum content protection level.
     */
    CONTENT_PROTECTION_LEVEL_MAX,
} DRM_ContentProtectionLevel;

/**
 * @brief Enumerates the types of media keys.
 * 
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */
typedef enum DRM_MediaKeyType {
    /**
     * Offline media key.
     */
    MEDIA_KEY_TYPE_OFFLINE = 0,
    /**
     * Online media key.
     */
    MEDIA_KEY_TYPE_ONLINE,
} DRM_MediaKeyType;

/**
 * @brief Enumerates the types of media key requests.
 * 
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */
typedef enum DRM_MediaKeyRequestType {
    /**
     * Unknown type.
     */
    MEDIA_KEY_REQUEST_TYPE_UNKNOWN = 0,
    /**
     * Initialization request.
     */
    MEDIA_KEY_REQUEST_TYPE_INITIAL,
    /**
     * Renewal request.
     */
    MEDIA_KEY_REQUEST_TYPE_RENEWAL,
    /**
     * Release request.
     */
    MEDIA_KEY_REQUEST_TYPE_RELEASE,
    /**
     * No request.
     */
    MEDIA_KEY_REQUEST_TYPE_NONE,
    /**
     * Update request.
     */
    MEDIA_KEY_REQUEST_TYPE_UPDATE,
} DRM_MediaKeyRequestType;

/**
 * @brief Enumerates the statuses of offline media keys.
 * 
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */
typedef enum DRM_OfflineMediaKeyStatus {
    /**
     * Unknown status.
     */
    OFFLINE_MEDIA_KEY_STATUS_UNKNOWN = 0,
    /**
     * The media key is available.
     */
    OFFLINE_MEDIA_KEY_STATUS_USABLE,
    /**
     * The media key is inactive.
     */
    OFFLINE_MEDIA_KEY_STATUS_INACTIVE,
} DRM_OfflineMediaKeyStatus;

/**
 * @brief Enumerates the device certificate statuses.
 * 
 * @syscap SystemCapability.Multimedia.Drm.Core
 * @since 11
 * @version 1.0
 */
typedef enum DRM_CertificateStatus {
    /**
     * A device certificate is provisioned.
     */
    CERT_STATUS_PROVISIONED = 0,
    /**
     * No device certificate is provisioned or the certificate status is abnormal.
     */
    CERT_STATUS_NOT_PROVISIONED,
    /**
     * The device certificate has expired.
     */
    CERT_STATUS_EXPIRED,
    /**
     * The device certificate is invalid.
     */
    CERT_STATUS_INVALID,
    /**
     * The device certificate is unavailable.
     */
    CERT_STATUS_UNAVAILABLE,
} DRM_CertificateStatus;

/**
 * @brief Maximum number of optional data entries in a media key request.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_REQUEST_OPTION_COUNT 16
/**
 * @brief Maximum length of an optional data name in a media key request.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_REQUEST_OPTION_NAME_LEN 64
/**
 * @brief Maximum length of optional data in a media key request.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_REQUEST_OPTION_DATA_LEN 128
/**
 * @brief Maximum length of initialization data for a media key request.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_INIT_DATA_LEN 2048
/**
 * @brief Maximum length of a MIME type.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MIMETYPE_LEN 64

/**
 * @brief The struct describes the information about a media key request.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct DRM_MediaKeyRequestInfo {
    /**
     * Type of the media key request.
     */
    DRM_MediaKeyType type;
    /**
     * Length of the initialization data.
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
     * Number of options.
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
 * @brief Maximum length of data in a media key request.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_REQUEST_DATA_LEN 8192
/**
 * @brief Maximum length of a URL.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_DEFAULT_URL_LEN 2048
/**
 * @brief The struct describes a media key request.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct DRM_MediaKeyRequest {
    /**
     * Type of the media key request.
     */
    DRM_MediaKeyRequestType type;
    /**
     * Length of data in the media key request.
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
 * @brief Maximum number of metric records.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_STATISTICS_COUNT 10
/**
 * @brief Maximum length of a metric name.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_STATISTICS_NAME_LEN 64
/**
 * @brief Maximum length of a metric buffer.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_STATISTICS_BUFFER_LEN 256

/**
 * @brief The struct describes the metrics for a media key system.
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
 * @brief Maximum number of offline media key IDs.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_OFFLINE_MEDIA_KEY_ID_COUNT 512
/**
 * @brief Maximum length of an offline media key ID.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_OFFLINE_MEDIA_KEY_ID_LEN 64

/**
 * @brief The struct describes an array of offline media key IDs.
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
 * @brief Maximum number of key information entries.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_KEY_INFO_COUNT 64
/**
 * @brief Maximum length of a key ID.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_KEY_ID_LEN 16
/**
 * @brief Maximum length of a key status value.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_KEY_STATUS_VALUE_LEN 128

/**
 * @brief The struct describes the information about media keys.
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
 * @brief Maximum number of media key statuses.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_STATUS_COUNT 64
/**
 * @brief Maximum length of a media key status name.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_STATUS_NAME_LEN 64
/**
 * @brief Maximum length of a media key status value.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_MEDIA_KEY_STATUS_VALUE_LEN 256

/**
 * @brief The struct describes the media key status.
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
 * @brief Length of the UUID of a DRM solution.
 * 
 * @since 11
 * @version 1.0
 */
#define DRM_UUID_LEN 16
/**
 * @brief Maximum length of PSSH data.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_PSSH_DATA_LEN 2048

/**
 * @brief The struct describes the Protection System Specific Header (PSSH) data for a DRM system.
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
     * Length of the PSSH data payload.
     */
    int32_t dataLen;
    /**
     * uint8_t PSSH data.
     */
    uint8_t data[MAX_PSSH_DATA_LEN];
} DRM_PsshInfo;

/**
 * @brief Maximum number of PSSH data entries.
 * 
 * @since 11
 * @version 1.0
 */
#define MAX_PSSH_INFO_COUNT 8

/**
 * @brief The struct describes the DRM information for encrypted content.
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
* @brief Defines the callback used to obtain DRM information from a media source.
* 
* @since 11
* @version 1.0
*/
typedef void (*DRM_MediaKeySystemInfoCallback)(DRM_MediaKeySystemInfo *mediaKeySystemInfo);

/**
 * @brief The struct describes a media key system.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct MediaKeySystem MediaKeySystem;

/**
 * @brief The struct describes a media key session.
 * 
 * @since 11
 * @version 1.0
 */
typedef struct MediaKeySession MediaKeySession;
/**
 * @brief Maximum length of a MediaKeySystem instance name.
 * 
 * @since 12
 * @version 1.0
 */
#define MAX_MEDIA_KEY_SYSTEM_NAME_LEN 128

/**
 * @brief Maximum number of MediaKeySystem instances.
 * 
 * @since 12
 * @version 1.0
 */
#define MAX_MEDIA_KEY_SYSTEM_NUM 8

/**
 * @brief The struct describes the DRM solution name and UUID list.
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
