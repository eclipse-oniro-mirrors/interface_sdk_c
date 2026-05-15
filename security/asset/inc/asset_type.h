/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @addtogroup AssetType
 * @{
 *
 * @brief Provides the enums, structs, and error codes used in the Asset APIs.
 *
 * @since 11
 */

/**
 * @file asset_type.h
 *
 * @brief Defines the enums, structs, and error codes used in the asset store service.
 *
 * @library libasset_ndk.z.so
 * @kit AssetStoreKit
 * @syscap SystemCapability.Security.Asset
 * @since 11
 */
#ifndef ASSET_TYPE_H
#define ASSET_TYPE_H
#include <stdbool.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the types of the keys of asset attributes.
 *
 * @since 11
 */
typedef enum {
    /**
     * Boolean.
     */
    ASSET_TYPE_BOOL = 0x1 << 28,

    /**
     * Number (uint32_t).
     */
    ASSET_TYPE_NUMBER = 0x2 << 28,

    /**
     * Bytes.
     */
    ASSET_TYPE_BYTES = 0x3 << 28
} Asset_TagType;

/**
 * @brief Enumerates the keys of asset attributes.
 *
 * @since 11
 */
typedef enum {
    /**
     * Sensitive user data in the form of bytes, such as passwords and tokens.
     */
    ASSET_TAG_SECRET = ASSET_TYPE_BYTES | 0x01,

    /**
     * Asset alias (identifier) in the form of bytes.
     */
    ASSET_TAG_ALIAS = ASSET_TYPE_BYTES | 0x02,

    /**
     * Access control based on the lock screen status. The value is of the uint32_t type.
     */
    ASSET_TAG_ACCESSIBILITY = ASSET_TYPE_NUMBER | 0x03,

    /**
     * A Boolean value indicating whether the asset is available only with a lock screen password.
     */
    ASSET_TAG_REQUIRE_PASSWORD_SET = ASSET_TYPE_BOOL | 0x04,

    /**
     * User authentication type for the asset. The value is of the uint32_t type.
     */
    ASSET_TAG_AUTH_TYPE = ASSET_TYPE_NUMBER | 0x05,

    /**
     * Validity period of the user authentication, in seconds. The value is of the uint32_t type, in seconds.
     */
    ASSET_TAG_AUTH_VALIDITY_PERIOD = ASSET_TYPE_NUMBER | 0x06,

    /**
     * Challenge value, in the form of bytes, used for anti-replay during the authentication.
     */
    ASSET_TAG_AUTH_CHALLENGE = ASSET_TYPE_BYTES | 0x07,

    /**
     * Authentication token, in the form of bytes, obtained after a successful user authentication.
     */
    ASSET_TAG_AUTH_TOKEN = ASSET_TYPE_BYTES | 0x08,

    /**
     * Asset sync type. The value is of the uint32_t type.
     */
    ASSET_TAG_SYNC_TYPE = ASSET_TYPE_NUMBER | 0x10,

    /**
     * Whether the asset needs to be stored persistently. Verification of **ohos.permission.STORE_PERSISTENT_DATA**
     * is required if **OH_Asset_Add** is called with this tag passed in.
     */
    ASSET_TAG_IS_PERSISTENT = ASSET_TYPE_BOOL | 0x11,

    /**
     * Custom data, which is of the bytes type and cannot be changed.
     */
    ASSET_TAG_DATA_LABEL_CRITICAL_1 = ASSET_TYPE_BYTES | 0x20,

    /**
     * Custom data, which is of the bytes type and cannot be changed.
     */
    ASSET_TAG_DATA_LABEL_CRITICAL_2 = ASSET_TYPE_BYTES | 0x21,

    /**
     * Custom data, which is of the bytes type and cannot be changed.
     */
    ASSET_TAG_DATA_LABEL_CRITICAL_3 = ASSET_TYPE_BYTES | 0x22,

    /**
     * Custom data, which is of the bytes type and cannot be changed.
     */
    ASSET_TAG_DATA_LABEL_CRITICAL_4 = ASSET_TYPE_BYTES | 0x23,

    /**
     * Custom data, which is of the bytes type and can be changed.
     */
    ASSET_TAG_DATA_LABEL_NORMAL_1 = ASSET_TYPE_BYTES | 0x30,

    /**
     * Custom data, which is of the bytes type and can be changed.
     */
    ASSET_TAG_DATA_LABEL_NORMAL_2 = ASSET_TYPE_BYTES | 0x31,

    /**
     * Custom data, which is of the bytes type and can be changed.
     */
    ASSET_TAG_DATA_LABEL_NORMAL_3 = ASSET_TYPE_BYTES | 0x32,

    /**
     * Custom data, which is of the bytes type and can be changed.
     */
    ASSET_TAG_DATA_LABEL_NORMAL_4 = ASSET_TYPE_BYTES | 0x33,

    /**
     * Custom data, which is of the bytes type, can be changed, but cannot be synced.
     * @since 12
     */
    ASSET_TAG_DATA_LABEL_NORMAL_LOCAL_1 = ASSET_TYPE_BYTES | 0x34,

    /**
     * Custom data, which is of the bytes type, can be changed, but cannot be synced.
     * @since 12
     */
    ASSET_TAG_DATA_LABEL_NORMAL_LOCAL_2 = ASSET_TYPE_BYTES | 0x35,

    /**
     * Custom data, which is of the bytes type, can be changed, but cannot be synced.
     * @since 12
     */
    ASSET_TAG_DATA_LABEL_NORMAL_LOCAL_3 = ASSET_TYPE_BYTES | 0x36,

    /**
     * Custom data, which is of the bytes type, can be changed, but cannot be synced.
     * @since 12
     */
    ASSET_TAG_DATA_LABEL_NORMAL_LOCAL_4 = ASSET_TYPE_BYTES | 0x37,

    /**
     * Type of asset information to return. The value is of the uint32_t type.
     */
    ASSET_TAG_RETURN_TYPE = ASSET_TYPE_NUMBER | 0x40,

    /**
     * Maximum number of assets that can be returned in a query operation. The value is of the uint32_t type.
     */
    ASSET_TAG_RETURN_LIMIT = ASSET_TYPE_NUMBER | 0x41,

    /**
     * Offset of the returned assets in a batch query. The value is of the uint32_t type.
     */
    ASSET_TAG_RETURN_OFFSET = ASSET_TYPE_NUMBER | 0x42,

    /**
     * Sorting order of the assets in the query result. The value is of the uint32_t type.
     */
    ASSET_TAG_RETURN_ORDERED_BY = ASSET_TYPE_NUMBER | 0x43,

    /**
     * Policy for resolving the conflict when an asset is added. The value is of the uint32_t type.
     */
    ASSET_TAG_CONFLICT_RESOLUTION = ASSET_TYPE_NUMBER | 0x44,

    /**
     * Asset update time, in timestamp format. The value is of the bytes type.
     * @since 12
     */
    ASSET_TAG_UPDATE_TIME = ASSET_TYPE_BYTES | 0x45,

    /**
     * Additional operation type. The value is of the uint32_t type.
     * @since 12
     */
    ASSET_TAG_OPERATION_TYPE = ASSET_TYPE_NUMBER | 0x46,

    /**
     * Whether to encrypt the additional information customized by the service. The value is of the Boolean type.
     * @since 14
     */
    ASSET_TAG_REQUIRE_ATTR_ENCRYPTED = ASSET_TYPE_BOOL | 0x47,

    /**
     * Group to which the asset belongs. The value is of the bytes type.
     * @since 18
     */
    ASSET_TAG_GROUP_ID = ASSET_TYPE_BYTES | 0x48,

    /**
     * Encrypted import/export type supported by the asset. The value is of the uint32_t type.
     * @since 18
     */
    ASSET_TAG_WRAP_TYPE = ASSET_TYPE_NUMBER | 0x49
} Asset_Tag;

/**
 * @brief Enumerates the result codes used in the ASSET APIs.
 *
 * @since 11
 */
typedef enum {
    /**
     * The operation is successful.
     */
    ASSET_SUCCESS = 0,

    /**
     * The caller does not have the required permission.
     */
    ASSET_PERMISSION_DENIED = 201,

    /**
     * The parameter is invalid.
     */
    ASSET_INVALID_ARGUMENT = 401,

    /**
     * The asset store service is unavailable.
     */
    ASSET_SERVICE_UNAVAILABLE = 24000001,

    /**
     * The asset is not found.
     */
    ASSET_NOT_FOUND = 24000002,

    /**
     * The asset already exists.
     */
    ASSET_DUPLICATED = 24000003,

    /**
     * The access to the asset is denied.
     */
    ASSET_ACCESS_DENIED = 24000004,

    /**
     * The lock screen status does not match.
     */
    ASSET_STATUS_MISMATCH = 24000005,

    /**
     * The system memory is insufficient.
     */
    ASSET_OUT_OF_MEMORY = 24000006,

    /**
     * The asset is corrupted.
     */
    ASSET_DATA_CORRUPTED = 24000007,

    /**
     * The database operation failed.
     */
    ASSET_DATABASE_ERROR = 24000008,

    /**
     * The cryptographic operation failed.
     */
    ASSET_CRYPTO_ERROR = 24000009,

    /**
     * The IPC failed.
     */
    ASSET_IPC_ERROR = 24000010,

    /**
     * The Bundle Manager service is abnormal.
     */
    ASSET_BMS_ERROR = 24000011,

    /**
     * The Account service is abnormal.
     */
    ASSET_ACCOUNT_ERROR = 24000012,

    /**
     * The Access Token service is abnormal.
     */
    ASSET_ACCESS_TOKEN_ERROR = 24000013,

    /**
     * The file operation failed.
     */
    ASSET_FILE_OPERATION_ERROR = 24000014,

    /**
     * Failed to obtain the system time.
     */
    ASSET_GET_SYSTEM_TIME_ERROR = 24000015,

    /**
     * The number of cached assets exceeds the limit.
     */
    ASSET_LIMIT_EXCEEDED = 24000016,

    /**
     * The function is not supported.
     */
    ASSET_UNSUPPORTED = 24000017,

    /**
     * The parameter verification fails.
     * @since 20
     */
    ASSET_PARAM_VERIFICATION_FAILED = 24000018
} Asset_ResultCode;

/**
 * @brief Enumerates the types of the access control based on the lock screen status.
 *
 * @since 11
 */
typedef enum {
    /**
     * The asset can be accessed after the device is powered on.
     */
    ASSET_ACCESSIBILITY_DEVICE_POWERED_ON = 0,

    /**
     * The asset can be accessed only after the device is unlocked for the first time.
     */
    ASSET_ACCESSIBILITY_DEVICE_FIRST_UNLOCKED = 1,

    /**
     * The asset can be accessed only after the device is unlocked.
     */
    ASSET_ACCESSIBILITY_DEVICE_UNLOCKED = 2
} Asset_Accessibility;

/**
 * @brief Enumerates the user authentication types supported by assets.
 *
 * @since 11
 */
typedef enum {
    /**
     * No user authentication is required before the asset is accessed.
     */
    ASSET_AUTH_TYPE_NONE = 0x00,

    /**
     * The asset can be accessed if any user authentication (such as PIN, facial, or fingerprint authentication) is
     * successful.
     */
    ASSET_AUTH_TYPE_ANY = 0xFF
} Asset_AuthType;

/**
 * @brief Asset sync type.
 *
 * @since 11
 */
typedef enum {
    /**
     * Asset sync is not allowed.
     */
    ASSET_SYNC_TYPE_NEVER = 0,

    /**
     * Asset sync is allowed only on the local device, for example, in data restore on the local device.
     */
    ASSET_SYNC_TYPE_THIS_DEVICE = 1 << 0,

    /**
     * Asset sync is allowed only between trusted devices, for example, in the case of cloning.
     */
    ASSET_SYNC_TYPE_TRUSTED_DEVICE = 1 << 1,

    /**
     * Asset sync is allowed only between the devices that are logged in with trusted accounts, for example, in cloud sync scenarios.
     * @since 12
     */
    ASSET_SYNC_TYPE_TRUSTED_ACCOUNT = 1 << 2
} Asset_SyncType;

/**
 * @brief Encrypted import/export type supported by the asset.
 *
 * @since 18
 */
typedef enum {
    /**
     * Encrypted import/export is not allowed for the asset.
     */
    ASSET_WRAP_TYPE_NEVER = 0,

    /**
     * Encrypted import/export is allowed for the asset only on devices where a trusted account is logged in.
     */
    ASSET_WRAP_TYPE_TRUSTED_ACCOUNT = 1
} Asset_WrapType;

/**
 * @brief Policy for resolving the conflict (for example, a duplicate alias).
 *
 * @since 11
 */
typedef enum {
    /**
     * Overwrite the original asset.
     */
    ASSET_CONFLICT_OVERWRITE = 0,

    /**
     * Throw an exception for the service to perform subsequent processing.
     */
    ASSET_CONFLICT_THROW_ERROR = 1
} Asset_ConflictResolution;

/**
 * @brief Type of the asset query result to return.
 *
 * @since 11
 */
typedef enum {
    /**
     * The query result contains the asset plaintext and its attributes.
     */
    ASSET_RETURN_ALL = 0,

    /**
     * The query result contains only the asset attributes.
     */
    ASSET_RETURN_ATTRIBUTES = 1
} Asset_ReturnType;

/**
 * @brief Enumerates the additional asset operation types.
 *
 * @since 12
 */
typedef enum {
    /**
     * Sync.
     */
    ASSET_NEED_SYNC = 0,

    /**
     * Logout.
     */
    ASSET_NEED_LOGOUT = 1
} Asset_OperationType;

/**
 * @brief Defines a binary array, that is, an array of bytes with variable length.
 *
 * @since 11
 */
typedef struct {
    /**
     * Size of the byte array.
     */
    uint32_t size;
    /**
     * Pointer to the byte array.
     */
    uint8_t *data;
} Asset_Blob;

/**
 * @brief Defines the value (content) of an asset attribute.
 *
 * @since 11
 */
typedef union {
    /**
     * Asset of the Boolean type.
     */
    bool boolean;
    /**
     * Asset of the uint32 type.
     */
    uint32_t u32;
    /**
     * Asset of the bytes type.
     */
    Asset_Blob blob;
} Asset_Value;

/**
 * @brief Defines an asset attribute, which consists of a tag and a value in the form of a key-value (KV) pair.
 *
 * @since 11
 */
typedef struct {
    /**
     * Name of the asset attribute. The tag (the key in the KV pair) uniquely identifies an attribute.
     */
    uint32_t tag;
    /**
     * Defines the value of the asset attribute.
     */
    Asset_Value value;
} Asset_Attr;

/**
 * @brief Represents the query result of an asset.
 *
 * @since 11
 */
typedef struct {
    /**
     * Number of asset attributes in the query result.
     */
    uint32_t count;
    /**
     * Pointer to the array of the asset attributes.
     */
    Asset_Attr *attrs;
} Asset_Result;

/**
 * @brief Represents the query result of multiple assets.
 *
 * @since 11
 */
typedef struct {
    /**
     * Number of assets in the query result.
     */
    uint32_t count;
    /**
     * Pointer to the array of the assets.
     */
    Asset_Result *results;
} Asset_ResultSet;

/**
 * @brief Represents the sync result of an asset.
 *
 * @since 20
 */
typedef struct {
    /**
     * Sync result code of an asset.
     */
    int32_t resultCode;
    /**
     * Total number of assets to be synced.
     */
    uint32_t totalCount;
    /**
     * Number of assets that fail to be synced.
     */
    uint32_t failedCount;
} Asset_SyncResult;
/**
 * @brief Defines the mask used to obtain the key type of an asset attribute.
 *
 * @since 11
 */
#define ASSET_TAG_TYPE_MASK (0xF << 28)
#ifdef __cplusplus
}
#endif

/** @} */
#endif // ASSET_TYPE_H