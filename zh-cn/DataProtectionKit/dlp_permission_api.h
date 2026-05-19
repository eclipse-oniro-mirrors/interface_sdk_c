/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @brief Provides the capability to access the data loss prevention (DLP) files.
 *
 * @since 14
 */

/**
 * @file dlp_permission_api.h
 *
 * @brief 声明用于跨设备的文件的权限管理、加密存储、授权访问等能力的接口。
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
 * @brief DLP错误码的枚举。
 *
 * @since 14
 */
typedef enum {
    /**
     * 表示操作成功。
     */
    ERR_OH_SUCCESS = 0,
    /**
     * 表示入参错误。
     */
    ERR_OH_INVALID_PARAMETER = 19100001,
    /**
     * 表示非DLP沙箱应用。
     */
    ERR_OH_API_ONLY_FOR_SANDBOX = 19100006,
    /**
     * 表示DLP沙箱应用不允许调用此接口。
     */
    ERR_OH_API_NOT_FOR_SANDBOX = 19100007,
    /**
     * 表示系统服务工作异常。
     */
    ERR_OH_SYSTEM_SERVICE_EXCEPTION = 19100011,
    /**
     * 表示内存申请失败。
     */
    ERR_OH_OUT_OF_MEMORY = 19100012,
    /**
     * 表示应用未授权。
     */
    ERR_OH_APPLICATION_NOT_AUTHORIZED = 19100018,
} DLP_ErrCode;

/**
 * @brief DLP文件授权类型的枚举。
 *
 * @since 14
 */
typedef enum {
    /**
     * 表示无文件权限。
     */
    NO_PERMISSION = 0,
    /**
     * 表示文件的只读权限。
     */
    READ_ONLY = 1,
    /**
     * 表示文件的编辑权限。
     */
    CONTENT_EDIT = 2,
    /**
     * 表示文件的完全控制权限。
     */
    FULL_CONTROL = 3
} DLP_FileAccess;

/**
 * @brief 查询 DLP 文件的权限信息
 *
 * @param dlpFileAccess 表示DLP文件针对用户的授权类型，例如：只读。
 * @param flags 表示DLP文件的详细操作权限，操作权限的具体含义为：
 *     <br>0x00000000-表示无文件权限。
 *     <br>0x00000001-表示文件的查看权限。
 *     <br>0x00000002-表示文件的保存权限。
 *     <br>0x00000004-表示文件的另存为权限。
 *     <br>0x00000008-表示文件的编辑权限。
 *     <br>0x00000010-表示文件的截屏权限。
 *     <br>0x00000020-表示文件的共享屏幕权限。
 *     <br>0x00000040-表示文件的录屏权限。
 *     <br>0x00000080-表示文件的复制权限。
 *     <br>0x00000100-表示文件的打印权限。
 *     <br>0x00000200-表示文件的导出权限。
 *     <br>0x00000400-表示文件的修改文件权限。
 * @return 0 - 操作成功。
 *     <br>19100001 - 入参错误。
 *     <br>19100006 - 非DLP沙箱应用。
 *     <br>19100011 - 系统服务工作异常。
 *     <br>19100012 - 内存申请失败。
 * @since 14
 */
DLP_ErrCode OH_DLP_GetDlpPermissionInfo(DLP_FileAccess *dlpFileAccess, uint32_t *flags);

/**
 * @brief 获取指定DLP文件名的原始文件名。
 *
 * @param fileName 指定要查询的文件名。
 * @param originalFileName DLP文件的原始文件名。
 * @return 0 - 操作成功。
 *     <br>19100001 - 入参错误。
 *     <br>19100012 - 内存申请失败。
 * @since 14
 */
DLP_ErrCode OH_DLP_GetOriginalFileName(const char *fileName, char **originalFileName);

/**
 * @brief 查询当前应用是否运行在DLP沙箱环境。
 *
 * @param isInSandbox true表示当前应用运行在DLP沙箱环境，false表示当前应用不是运行在DLP沙箱环境。
 * @return 0 - 操作成功。
 *     <br>19100011 - 系统服务工作异常。
 *     <br>19100012 - 内存申请失败。
 * @since 14
 */
DLP_ErrCode OH_DLP_IsInSandbox(bool *isInSandbox);

/**
 * @brief 设置沙箱应用配置信息。
 *
 * @param configInfo 沙箱应用配置信息。
 * @return 0 - 操作成功。
 *     <br>19100001 - 入参错误。
 *     <br>19100007 - DLP沙箱应用不允许调用此接口。
 *     <br>19100011 - 系统服务工作异常。
 *     <br>19100018 - 应用未授权。
 * @since 14
 */
DLP_ErrCode OH_DLP_SetSandboxAppConfig(const char *configInfo);

/**
 * @brief 获取沙箱应用配置信息。
 *
 * @param configInfo 沙箱应用配置信息。
 * @return 0 - 操作成功。
 *     <br>19100011 - 系统服务工作异常。
 *     <br>19100012 - 内存申请失败。
 *     <br>19100018 - 应用未授权。
 * @since 14
 */
DLP_ErrCode OH_DLP_GetSandboxAppConfig(char **configInfo);

/**
 * @brief 清理沙箱应用配置信息。
 *
 * @return 0 - 操作成功。
 *     <br>19100007 - DLP沙箱应用不允许调用此接口。
 *     <br>19100011 - 系统服务工作异常。
 *     <br>19100018 - 应用未授权。
 * @since 14
 */
DLP_ErrCode OH_DLP_CleanSandboxAppConfig();

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* DLP_PERMISSION_API_H */