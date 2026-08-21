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
 * @file native_drm_common.h
 *
 * @brief 定义DRM数据类型，包括媒体密钥请求、内容保护级别、证书状态等核心数据结构，用于支持DRM（数字版权管理）功能的开发，帮助应用实现受版权保护的多媒体内容的播放和管理。
 * 
 * @library libnative_drm.so
 * @include <multimedia/drm_framework/native_drm_common.h>
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
  * @syscap SystemCapability.Multimedia.Drm.Core
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
 * @syscap SystemCapability.Multimedia.Drm.Core
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
     * 媒体密钥类型，指定请求的密钥用途。取值为MEDIA_KEY_TYPE_ONLINE（在线）或MEDIA_KEY_TYPE_OFFLINE（离线）。
     */
    DRM_MediaKeyType type;
    /**
     * 初始化数据的长度，表示initData数组中有效数据的字节数。单位为字节（Byte），取值范围为[1, MAX_INIT_DATA_LEN]。
     */
    int32_t initDataLen;
    /**
     * 初始化数据，包含DRM内容保护系统特定头（PSSH）格式的数据，通常从媒体内容的PSSH box中提取。数组长度由MAX_INIT_DATA_LEN宏定义。
     */
    uint8_t initData[MAX_INIT_DATA_LEN];
    /**
     * 媒体内容的MIME类型，用于标识媒体内容的格式。常见取值如"video/mp4"、"video/webm"等，具体支持类型由DRM解决方案决定。数组长度由MAX_MIMETYPE_LEN宏定义。
     */
    char mimeType[MAX_MIMETYPE_LEN];
    /**
     * 选项数据的数量，表示optionName和optionData数组中有效元素的个数。取值范围为[0, MAX_MEDIA_KEY_REQUEST_OPTION_COUNT]。
     */
    uint32_t optionsCount;
    /**
     * 选项名称数组，每行存储一个选项的名称。选项名称由DRM解决方案定义，用于传递特定的请求参数。
     * 数组维度由MAX_MEDIA_KEY_REQUEST_OPTION_COUNT和MAX_MEDIA_KEY_REQUEST_OPTION_NAME_LEN宏定义。
     */
    char optionName[MAX_MEDIA_KEY_REQUEST_OPTION_COUNT][MAX_MEDIA_KEY_REQUEST_OPTION_NAME_LEN];
    /**
     * 选项数据数组，每行存储对应optionName的选项值。数组维度由MAX_MEDIA_KEY_REQUEST_OPTION_COUNT和MAX_MEDIA_KEY_REQUEST_OPTION_DATA_LEN宏定义。
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
     * 媒体密钥请求类型，指示请求的用途。常见类型包括MEDIA_KEY_REQUEST_TYPE_INITIAL（初始请求）、MEDIA_KEY_REQUEST_TYPE_RENEWAL（续期请求）等，具体类型由DRM解决方案决定。
     */
    DRM_MediaKeyRequestType type;
    /**
     * 媒体密钥请求数据的长度，表示data数组中有效数据的字节数。单位为字节（Byte），取值范围为[0, MAX_MEDIA_KEY_REQUEST_DATA_LEN]。
     */
    int32_t dataLen;
    /**
     * 媒体密钥请求数据，需要发送到许可证服务器的数据。数据格式由DRM解决方案定义，通常为特定格式的二进制数据或JSON格式。数组长度由MAX_MEDIA_KEY_REQUEST_DATA_LEN宏定义。
     */
    uint8_t data[MAX_MEDIA_KEY_REQUEST_DATA_LEN];
    /**
     * 许可证服务器的默认URL，用于获取媒体密钥。该URL由DRM解决方案提供，应用可使用此URL或自定义URL发送请求。数组长度由MAX_DEFAULT_URL_LEN宏定义。
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
 * @brief MediaKeySystem的统计信息。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct DRM_Statistics {
    /* 度量信息的数量，表示statisticsName和statisticsDescription数组中有效元素的个数。取值范围为[0, MAX_STATISTICS_COUNT]。 */
    uint32_t statisticsCount;
    /* 度量信息名称数组，每行存储一个度量项的名称，具体名称由DRM解决方案定义。数组维度由MAX_STATISTICS_COUNT和MAX_STATISTICS_NAME_LEN宏定义。 */
    char statisticsName[MAX_STATISTICS_COUNT][MAX_STATISTICS_NAME_LEN];
    /* 度量信息描述数组，每行存储对应statisticsName的度量值。数组维度由MAX_STATISTICS_COUNT和MAX_STATISTICS_BUFFER_LEN宏定义。 */
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
    /* 离线媒体密钥ID的数量，表示idsLen和ids数组中有效元素的个数。取值范围为[0, MAX_OFFLINE_MEDIA_KEY_ID_COUNT]。 */
    uint32_t idsCount;
    /* 离线媒体密钥ID长度数组，每个元素表示对应ids数组行中有效数据的字节数。数组长度由MAX_OFFLINE_MEDIA_KEY_ID_COUNT宏定义。 */
    int32_t idsLen[MAX_OFFLINE_MEDIA_KEY_ID_COUNT];
    /* 离线媒体密钥ID数据数组，用于存储离线媒体密钥的标识符。每行存储一个密钥ID，有效长度由对应的idsLen元素指定。
       数组维度由MAX_OFFLINE_MEDIA_KEY_ID_COUNT和MAX_OFFLINE_MEDIA_KEY_ID_LEN宏定义。 */
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
    /* 媒体密钥信息的数量，表示keyId和statusValue数组中有效元素的个数。取值范围为[0, MAX_KEY_INFO_COUNT]。 */
    uint32_t keysInfoCount;
    /* 媒体密钥ID数组，每行存储一个密钥的标识符。密钥ID用于标识唯一的一个媒体密钥。数组维度由MAX_KEY_INFO_COUNT和MAX_KEY_ID_LEN宏定义。 */
    uint8_t keyId[MAX_KEY_INFO_COUNT][MAX_KEY_ID_LEN];
    /* 媒体密钥状态值数组，每行存储对应keyId的密钥状态。状态值由DRM解决方案定义，常见状态包括"usable"（可用）、"expired"（已过期）等。
       数组维度由MAX_KEY_INFO_COUNT和MAX_KEY_STATUS_VALUE_LEN宏定义。 */
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
    /* 媒体密钥状态项的数量，表示statusName和statusValue数组中有效元素的个数。取值范围为[0, MAX_MEDIA_KEY_STATUS_COUNT]。 */
    uint32_t statusCount;
    /* 媒体密钥状态名称数组，每行存储一个状态的名称。常见状态名称包括"Usable"（可用）、"Expired"（已过期）、
       "OutputRestricted"（输出受限）等，具体由DRM解决方案定义。数组维度由MAX_MEDIA_KEY_STATUS_COUNT和MAX_MEDIA_KEY_STATUS_NAME_LEN宏定义。 */
    char statusName[MAX_MEDIA_KEY_STATUS_COUNT][MAX_MEDIA_KEY_STATUS_NAME_LEN];
    /* 媒体密钥状态值数组，每行存储对应statusName的状态值。状态值格式由DRM解决方案定义，可能包含时间戳、级别等信息。
       数组维度由MAX_MEDIA_KEY_STATUS_COUNT和MAX_MEDIA_KEY_STATUS_VALUE_LEN宏定义。 */
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
 * @brief PSSH（Protection System Specific Header）信息的最大长度。
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
     * DRM系统的UUID（通用唯一标识符），用于唯一标识一个DRM内容保护系统。UUID长度为16字节，由DRM解决方案提供商分配。
     */
    uint8_t uuid[DRM_UUID_LEN];
    /**
     * PSSH数据的长度，表示data数组中有效数据的字节数。单位为字节（Byte），取值范围为[0, MAX_PSSH_DATA_LEN]。
     */
    int32_t dataLen;
    /**
     * PSSH数据，包含DRM系统特定的初始化数据。数据格式通常包含密钥ID、内容ID等信息。数组长度由MAX_PSSH_DATA_LEN宏定义。
     */
    uint8_t data[MAX_PSSH_DATA_LEN];
} DRM_PsshInfo;

/**
 * @brief PSSH（Protection System Specific Header）信息的最大数量。
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
    /* PSSH信息的数量，表示psshInfo数组中有效元素的个数。一个媒体文件可能包含多个DRM系统的PSSH，取值范围为[0, MAX_PSSH_INFO_COUNT]。 */
    uint32_t psshCount;
    /* PSSH信息数组，每项包含一个DRM内容保护系统专用头的信息。数组长度由MAX_PSSH_INFO_COUNT宏定义，每项包含DRM系统UUID和初始化数据。 */
    DRM_PsshInfo psshInfo[MAX_PSSH_INFO_COUNT];
} DRM_MediaKeySystemInfo;

/**
* @brief 应用为从媒体源获取DRM信息而设置的回调函数。
* 
* @param mediaKeySystemInfo 输出参数，从媒体源获取的DRM信息，包含DRM内容保护系统的唯一标识和PSSH数据。
* @since 11
* @version 1.0
*/
typedef void (*DRM_MediaKeySystemInfoCallback)(DRM_MediaKeySystemInfo *mediaKeySystemInfo);

/**
 * @brief MediaKeySystem结构，用于表示一个媒体密钥系统实例。MediaKeySystem提供数字版权保护能力，
 * 负责DRM插件配置管理、设备证书管理、统计信息获取、内容保护级别查询以及创建MediaKeySession等功能。
 * 通过OH_MediaKeySystem_Create接口创建实例，通过OH_MediaKeySystem_Destroy接口销毁实例。
 * 
 * @since 11
 * @version 1.0
 */
typedef struct MediaKeySystem MediaKeySystem;

/**
 * @brief MediaKeySession结构，用于表示一个媒体密钥会话实例。MediaKeySession是DRM解密流程的核心组件，
 * 负责生成许可证请求、处理许可证响应、管理密钥状态等功能。每个MediaKeySession实例对应一个播放会话的密钥解密过程。
 * 通过OH_MediaKeySystem_CreateMediaKeySession接口创建实例，通过OH_MediaKeySession_Destroy接口销毁实例。
 * 每个MediaKeySystem可创建多个MediaKeySession实例，用于处理不同的播放会话。
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
    /* DRM插件的名称，用于唯一标识一个DRM解决方案。名称格式由DRM解决方案定义，如"com.clearplay.drm"等。数组长度由MAX_MEDIA_KEY_SYSTEM_NAME_LEN宏定义。 */
    char name[MAX_MEDIA_KEY_SYSTEM_NAME_LEN];
    /* DRM系统的UUID（通用唯一标识符），用于唯一标识一个DRM内容保护系统。UUID长度为16字节（DRM_UUID_LEN），由DRM解决方案提供商分配。UUID与name对应同一DRM解决方案的不同表示形式。 */
    uint8_t uuid[DRM_UUID_LEN];
} DRM_MediaKeySystemDescription;

#ifdef __cplusplus
}
#endif

#endif // NATIVE_DRM_COMMON_H
/** @} */
