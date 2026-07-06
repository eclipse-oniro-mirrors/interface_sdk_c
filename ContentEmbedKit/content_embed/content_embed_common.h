/*
 * Copyright (c) 2026-2026 Huawei Device Co., Ltd.
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
 * @addtogroup ContentEmbed
 * @{
 *
 * @brief The ContentEmbed module provides the Object Editor (OE) framework and technologies to support document
 * embedding and collaborative editing between applications.
 * An embedded document (OE document for short) implemented by using the OE technology may be presented as a thumbnail
 * or a snapshot on a client UI, or may be serialized into a segment of binary data in a standard format and stored in
 * a memory or a file (referred to as an OE format file).
 * @since 24
 */

/**
 * @file content_embed_common.h
 *
 * @brief Provides the error code definitions for the ContentEmbed module and the type enumeration descriptions for the
 * capabilities supported by embedded documents.
 *
 * @library libcontent_embed_ndk.so
 * @kit ContentEmbedKit
 * @syscap SystemCapability.ContentEmbed.ObjectEditor
 * @since 24
 */

#ifndef OHOS_CONTENT_EMBED_COMMON_H
#define OHOS_CONTENT_EMBED_COMMON_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Indicates the maximum string length of the OEID of an embedded document.
 *
 * @since 24
 */
#define MAX_OEID_LENGTH (1 * 40)

/**
 * @brief Defines the error codes of the Content Embed Kit.
 *
 * @since 24
 */
typedef enum ContentEmbed_ErrorCode {
    /**
     * @brief The operation is successful.
     *
     * @since 24
     */
    CE_ERR_OK = 0,
    /**
     * @brief Permission verification failed.
     *
     * @since 24
     */
    CE_PERMISSION_DENIED = 201,
    /**
     * @brief Invalid parameter.
     *
     * @since 24
     */
    CE_ERR_PARAM_INVALID = 401,
    /**
     * @brief This feature isn\'t supported on your device.
     *
     * @since 24
     */
    CE_ERR_DEVICE_NOT_SUPPORTED = 801,
    /**
     * @brief A null pointer is returned, which may be caused by memory allocation failure or internal error.
     *
     * @since 24
     */
    CE_ERR_NULL_POINTER = 35300001,
    /**
     * @brief The client has not registered the corresponding callback function.
     *
     * @since 24
     */
    CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED = 35300002,
    /**
     * @brief An unknown error occurs in the OE Extension.
     *
     * @since 24
     */
    CE_ERR_EXTENSION_ERROR = 35300003,
    /**
     * @brief The system service is abnormal, possibly because the service is not started, the connection is
     * interrupted, or the permission is insufficient.
     *
     * @since 24
     */
    CE_ERR_SYSTEM_ABNORMAL = 35300004,
    /**
     * @brief Operations on the Storage object of the OE document failed.
     *
     * @since 24
     */
    CE_ERR_STORAGE_OPERATION_FAILED = 35300005,
    /**
     * @brief Operations on the Stream object of the OE document failed.
     *
     * @since 24
     */
    CE_ERR_STREAM_OPERATION_FAILED = 35300006,
    /**
     * @brief The file operation failed, possibly because the file does not exist, the permission is insufficient, the
     * path is incorrect, or the disk space is insufficient.
     *
     * @since 24
     */
    CE_ERR_FILE_OPERATION_FAILED = 35300007,
    /**
     * @brief The current application is running in the DLP sandbox environment and cannot call related functions.
     *
     * @since 24
     */
    CE_ERR_IN_DLP_SANDBOX = 35300008,
    /**
     * @brief The ImagePacker operation failed.
     *
     * @since 24
     */
    CE_ERR_IMAGE_PACKER_OPERATION_FAILED = 35300009,
    /**
     * @brief An exception occurred during the execution of the callback function registered by the client.
     *
     * @since 24
     */
    CE_ERR_CLIENT_CALLBACK_FAILED = 35300010,
    /**
     * @brief The OE Extension exits unexpectedly.
     *
     * @since 24
     */
    CE_ERR_EXTENSION_ABNORMAL_EXIT = 35300011,
    /**
     * @brief A file that is linked to a directory that cannot be linked to, such as a file in the app sandbox
     * directory.
     *
     * @since 24
     */
    CE_ERR_INVALID_LINKING_PATH = 35300012,
    /**
     * @brief The number of connected OE Extensions exceeds the upper limit.
     *
     * @since 24
     */
    CE_ERR_CONNECT_LIMIT_EXCEED = 35300013,
    /**
     * @brief The current file is not authorized.
     *
     * @since 24
     */
    CE_ERR_FILE_NOT_GRANT = 35300014,
    /**
     * @brief The current disk space is insufficient.
     *
     * @since 24
     */
    CE_ERR_DISK_FULL = 35300015,
    /**
     * @brief The current OE Extension does not support this capability.
     *
     * @since 24
     */
    CE_ERR_EXTENSION_NOT_SUPPORT = 35300016,
} ContentEmbed_ErrorCode;

/**
 * @brief Enumerates the functions supported by embedded document objects. Multiple capability values can be combined
 * using bit masks.
 *
 * @since 24
 */
typedef enum ContentEmbed_CapabilityCode {
    /**
     * @brief Indicates that the snapshot image of an OE document can be obtained.
     *
     * @since 24
     */
    CE_CAPABILITY_SUPPORT_SNAPSHOT = 1 << 0,
    /**
     * @brief Indicates that the OE document can be edited.
     *
     * @since 24
     */
    CE_CAPABILITY_SUPPORT_DO_EDIT = 1 << 1,
} ContentEmbed_CapabilityCode;

#ifdef __cplusplus
}
#endif /* __cplusplus */
/** @} */
#endif // OHOS_CONTENT_EMBED_COMMON_H