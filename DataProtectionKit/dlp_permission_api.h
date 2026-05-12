/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @addtogroup DlpPermissionApi
 * @{
 *
 * @brief Defines the APIs for cross-device file access management, encrypted storage, and access authorization.
 *
 * @since 14
 */

/**
 * @file dlp_permission_api.h
 *
 * @brief Declares the APIs for accessing the data loss prevention (DLP) files.
 *
 * @library libohdlp_permission.so
 * @kit DataProtectionKit
 * @syscap SystemCapability.Security.DataLossPrevention
 * @since 14
 */

#ifndef DLP_PERMISSION_API_H
#define DLP_PERMISSION_API_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the DLP error codes.
 *
 * @since 14
 */
typedef enum {
    /** 
     * The operation is successful.
     */
    ERR_OH_SUCCESS = 0,
    /** 
     * Invalid parameters are specified.
     */
    ERR_OH_INVALID_PARAMETER = 19100001,
    /** 
     * The caller is not a DLP sandbox application.
     */
    ERR_OH_API_ONLY_FOR_SANDBOX = 19100006,
    /** 
     * The API is not available to a DLP sandbox application
     */
    ERR_OH_API_NOT_FOR_SANDBOX = 19100007,
    /** 
     * The system service is abnormal
     */
    ERR_OH_SYSTEM_SERVICE_EXCEPTION = 19100011,
    /** 
     * The memory allocation fails.
     */
    ERR_OH_OUT_OF_MEMORY = 19100012,
    /** 
     * The application is not authorized to perform the operation.
     */
    ERR_OH_APPLICATION_NOT_AUTHORIZED = 19100018,
} DLP_ErrCode;

/**
 * @brief Enumerates the access permissions for a DLP file.
 *
 * @since 14
 */
typedef enum {
    /** 
     * No permission on the file.
     */
    NO_PERMISSION = 0,
    /** 
     * Read-only permission.
     */
    READ_ONLY = 1,
    /** 
     * Editing permission.
     */
    CONTENT_EDIT = 2,
    /** 
     * Full control.
     */
    FULL_CONTROL = 3
} DLP_FileAccess;

/**
 * @brief Obtains the permission information of this DLP file.
 *
 * @param dlpFileAccess User permission on the DLP file, for example, read-only.
 * @param flags Pointer to the operation permissions allowed for the DLP file. The options are as follows:
 *    <br>**0x00000000** indicates no permission on the file.
 *    <br>**0x00000001** indicates the permission for viewing the file.
 *    <br>**0x00000002** indicates the permission for saving the file.
 *    <br>**0x00000004** indicates the permission for saving the file as another file.
 *    <br>**0x00000008** indicates the permission for editing the file.<br>**0x00000010** indicates the permission for capturing screenshots of the file.
 *    <br>**0x00000020** indicates the permission for sharing the screen, on which the file is open.
 *    <br>**0x00000040** indicates the permission for recording the screen, on which the file is open.
 *    <br>**0x00000080** indicates the permission for copying the file.
 *    <br>**0x00000100** indicates the permission for printing the file.
 *    <br>**0x00000200** indicates the permission for exporting the file.
 *    <br>**0x00000400** indicates the permission for modifying the permissions on the file.
 * @return {@link DLP_ErrCode#ERR_OH_SUCCESS} 0 - If the operation is successful.
 *     {@link DLP_ErrCode#ERR_OH_INVALID_PARAMETER} 19100001 - If the parameter value is invalid.
 *     {@link DLP_ErrCode#ERR_OH_API_ONLY_FOR_SANDBOX} 19100006 - If no permission to
 *     call this API, which is available only for DLP sandbox applications.
 *     {@link DLP_ErrCode#ERR_OH_SYSTEM_SERVICE_EXCEPTION} 19100011 - If the system ability
 *     works abnormally.
 *     {@link DLP_ErrCode#ERR_OH_OUT_OF_MEMORY} 19100012 - If the memory error.
 * @since 14
 */
DLP_ErrCode OH_DLP_GetDlpPermissionInfo(DLP_FileAccess *dlpFileAccess, uint32_t *flags);

/**
 * @brief Obtains the original file name of a DLP file.
 *
 * @param fileName Pointer to the target file whose original file name is to be obtained.
 * @param originalFileName Double pointer to the original file name obtained.
 * @return {@link DLP_ErrCode#ERR_OH_SUCCESS} 0 - If the operation is successful.
 *     {@link DLP_ErrCode#ERR_OH_INVALID_PARAMS} 19100001 - If the parameter value is invalid.
 *     {@link DLP_ErrCode#ERR_OH_OUT_OF_MEMORY} 19100012 - If the memory error.
 * @since 14
 */
DLP_ErrCode OH_DLP_GetOriginalFileName(const char *fileName, char **originalFileName);

/**
 * @brief Checks whether this application is running in a DLP sandbox environment.
 *
 * @param isInSandbox Returns **true** if the application is running in a DLP sandbox; returns **false** otherwise.
 *                      {@code true} if current application is in a DLP sandbox, {@code false} otherwise.
 * @return {@link DLP_ErrCode#ERR_OH_SUCCESS} 0 - If the operation is successful.
 *     {@link DLP_ErrCode#ERR_OH_SYSTEM_SERVICE_EXCEPTION} 19100011 - If the system ability
 *     works abnormally.
 *     {@link DLP_ErrCode#ERR_OH_OUT_OF_MEMORY} 19100012 - If the memory error.
 * @since 14
 */
DLP_ErrCode OH_DLP_IsInSandbox(bool *isInSandbox);

/**
 * @brief Sets sandbox application configuration.
 *
 * @param configInfo Pointer to the sandbox application configuration obtained.
 * @return {@link DLP_ErrCode#ERR_OH_SUCCESS} 0 - If the operation is successful.
 *     {@link DLP_ErrCode#ERR_OH_INVALID_PARAMETER} 19100001 - If the parameter value is invalid.
 *     {@link DLP_ErrCode#ERR_OH_API_NOT_FOR_SANDBOX} 19100007 - If no permission to
 *     call this API, which is available only for non-DLP sandbox applications.
 *     {@link DLP_ErrCode#ERR_OH_SYSTEM_SERVICE_EXCEPTION} 19100011 - If the system ability
 *     works abnormally.
 *     {@link DLP_ErrCode#ERR_OH_APPLICATION_NOT_AUTHORIZED} 19100018 - If the application is not authorized.
 * @since 14
 */
DLP_ErrCode OH_DLP_SetSandboxAppConfig(const char *configInfo);

/**
 * @brief Obtains the sandbox application configuration.
 *
 * @param configInfo Pointer to the sandbox application configuration obtained.
 * @return {@link DLP_ErrCode#ERR_OH_SUCCESS} 0 - If the operation is successful.
 *     {@link DLP_ErrCode#ERR_OH_SYSTEM_SERVICE_EXCEPTION} 19100011 - If the system ability
 *     works abnormally.
 *     {@link DLP_ErrCode#ERR_OH_OUT_OF_MEMORY} 19100012 - If the memory error.
 *     {@link DLP_ErrCode#ERR_OH_APPLICATION_NOT_AUTHORIZED} 19100018 - If the application is not authorized.
 * @since 14
 */
DLP_ErrCode OH_DLP_GetSandboxAppConfig(char **configInfo);

/**
 * @brief Cleans the sandbox application configuration.
 *
 * @return {@link DLP_ErrCode#ERR_OH_SUCCESS} 0 - If the operation is successful.
 *     {@link DLP_ErrCode#ERR_OH_API_NOT_FOR_SANDBOX} 19100007 - If no permission to
 *     call this API, which is available only for non-DLP sandbox applications.
 *     {@link DLP_ErrCode#ERR_OH_SYSTEM_SERVICE_EXCEPTION} 19100011 - If the system ability
 *     works abnormally.
 *     {@link DLP_ErrCode#ERR_OH_APPLICATION_NOT_AUTHORIZED} 19100018 - If the application is not authorized.
 * @since 14
 */
DLP_ErrCode OH_DLP_CleanSandboxAppConfig();

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* DLP_PERMISSION_API_H */