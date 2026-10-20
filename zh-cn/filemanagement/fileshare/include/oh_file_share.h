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
 * @addtogroup fileShare
 * @{
 *
 * @brief 此模块提供文件分享功能，支持将公共目录文件的统一资源标识符（URI）授权给其他应用程序，使其他应用可按授权访问对应文件或目录。\n
 * 该模块适用于跨应用文件共享场景，通过URI授权机制管理文件访问权限。
 * @since 12
 */

/**
 * @file oh_file_share.h
 * @kit CoreFileKit
 *
 * @brief 提供基于URI的文件及目录持久化授权、取消持久化授权、权限激活、权限查询等方法，适用于跨应用文件共享场景。\n
 * 持久化授权用于保存访问策略，权限激活用于使已持久化的权限生效。
 * @library libohfileshare.so
 * @syscap SystemCapability.FileManagement.AppFileService.FolderAuthorization
 * @since 12
 */

#ifndef FILE_MANAGEMENT_OH_FILE_SHARE_H
#define FILE_MANAGEMENT_OH_FILE_SHARE_H

#include "error_code.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief URI操作模式枚举值。
 *
 * @since 12
 */
typedef enum FileShare_OperationMode {
    /**
     * @brief 读取权限，可单独使用，也可与WRITE_MODE组合使用。
     */
    READ_MODE = 1 << 0,

    /**
     * @brief 写入权限，可单独使用，也可与READ_MODE组合使用。
     */
    WRITE_MODE = 1 << 1
} FileShare_OperationMode;

/**
 * @brief 授予或激活权限策略失败的URI对应的错误码。
 *
 * @since 12
 */
typedef enum FileShare_PolicyErrorCode {
    /**
     * @brief URI禁止被持久化，例如远端URI不支持持久化。
     */
    PERSISTENCE_FORBIDDEN = 1,

    /**
     * @brief 无效的模式，例如权限模式值不在支持范围内。
     */
    INVALID_MODE = 2,

    /**
     * @brief 无效路径。
     */
    INVALID_PATH = 3,

    /**
     * @brief 权限没有被持久化。
     */
    PERMISSION_NOT_PERSISTED = 4
} FileShare_PolicyErrorCode;

/**
 * @brief 授予或激活权限失败的URI策略结果，用于记录失败URI、错误码和失败原因。
 *
 * @since 12
 */
typedef struct FileShare_PolicyErrorResult {
    /**
     * 授予或激活权限失败的URI。
     */
    char *uri;

    /**
     * 授予或激活权限失败的URI对应的错误码。
     */
    FileShare_PolicyErrorCode code;

    /**
     * 授予或激活权限失败的URI对应的原因，由系统管理，无需手动释放。
     */
    char *message;
} FileShare_PolicyErrorResult;

/**
 * @brief 需要授予或激活URI访问权限的策略信息，用于描述跨应用文件共享场景中的目标URI和访问模式。
 *
 * @syscap SystemCapability.FileManagement.AppFileService.FolderAuthorization
 * @since 12
 */
typedef struct FileShare_PolicyInfo {
    /**
     * 需要授予或激活访问权限的URI，需符合系统URI格式规范。
     */
    char *uri;

    /**
     * uri指向字符串的字节长度，不包含字符串结束符'\0'。
     */
    unsigned int length;

    /**
     * 授予或激活权限的URI访问模式。READ_MODE表示读取权限，WRITE_MODE表示写入权限。\n
     * 示例：FileShare_OperationMode.READ_MODE、FileShare_OperationMode.WRITE_MODE。\n
     * 或者FileShare_OperationMode.READ_MODE|FileShare_OperationMode.WRITE_MODE。
     */
    unsigned int operationMode;
} FileShare_PolicyInfo;

/**
 * @brief 对所选择的多个文件或目录URI持久化授权。\n
 * 完成持久化授权后，可调用OH_FileShare_ActivatePermission()激活权限。
 *
 * @permission ohos.permission.FILE_ACCESS_PERSIST
 * @param policies 指向FileShare_PolicyInfo实例数组的指针，表示需要持久化授权的文件或目录URI策略信息。
 * @param policyNum FileShare_PolicyInfo实例数组的元素个数，取值范围为[1, 500]。
 * @param result 输出参数，指向FileShare_PolicyErrorResult数组指针。\n
 * 请使用OH_FileShare_ReleasePolicyErrorResult()进行资源释放。
 * @param resultNum 输出参数，表示FileShare_PolicyErrorResult数组的元素个数。
 * @return 返回FileManagement模块错误码{@link FileManagement_ErrCode}。\n
 *         {@link ERR_INVALID_PARAMETER} 401 - 输入参数无效。可能的原因有：\n
 *             1. 参数policies或参数result或参数resultNum为空指针；\n
 *             2. 参数policyNum值为0或者超过最大长度(500)；\n
 *             3. 参数policies中携带的uri为空或者length为0或者uri的长度与length不一致。\n
 *         {@link ERR_DEVICE_NOT_SUPPORTED} 801 - 当前设备类型不支持此接口。\n
 *         {@link ERR_PERMISSION_ERROR} 201 - 接口权限校验失败。\n
 *         {@link ERR_ENOMEM} 13900011 - 分配或者拷贝内存失败。\n
 *         {@link ERR_EPERM} 13900001 - 操作不被允许。\n
 *         {@link ERR_OK} 0 - 接口调用成功。
 * @since 12
 */
FileManagement_ErrCode OH_FileShare_PersistPermission(const FileShare_PolicyInfo *policies, unsigned int policyNum,
    FileShare_PolicyErrorResult **result, unsigned int *resultNum);

/**
 * @brief 对所选择的多个文件或目录URI取消持久化授权。\n
 * 调用此接口前，需要先完成持久化授权。
 *
 * @permission ohos.permission.FILE_ACCESS_PERSIST
 * @param policies 指向FileShare_PolicyInfo实例数组的指针，表示需要取消持久化授权的文件或目录URI策略信息。
 * @param policyNum FileShare_PolicyInfo实例数组的元素个数，取值范围为[1, 500]。
 * @param result 输出参数，指向FileShare_PolicyErrorResult数组指针。\n
 * 请使用OH_FileShare_ReleasePolicyErrorResult()进行资源释放。
 * @param resultNum 输出参数，表示FileShare_PolicyErrorResult数组的元素个数。
 * @return 返回FileManagement模块错误码{@link FileManagement_ErrCode}。\n
 *         {@link ERR_INVALID_PARAMETER} 401 - 输入参数无效。可能的原因有：\n
 *             1. 参数policies或参数result或参数resultNum为空指针；\n
 *             2. 参数policyNum值为0或者超过最大长度(500)；\n
 *             3. 参数policies中携带的uri为空或者length为0或者uri的长度与length不一致。\n
 *         {@link ERR_DEVICE_NOT_SUPPORTED} 801 - 当前设备类型不支持此接口。\n
 *         {@link ERR_PERMISSION_ERROR} 201 - 接口权限校验失败。\n
 *         {@link ERR_ENOMEM} 13900011 - 分配或者拷贝内存失败。\n
 *         {@link ERR_EPERM} 13900001 - 操作不被允许。\n
 *         {@link ERR_OK} 0 - 接口调用成功。
 * @since 12
 */
FileManagement_ErrCode OH_FileShare_RevokePermission(const FileShare_PolicyInfo *policies, unsigned int policyNum,
    FileShare_PolicyErrorResult **result, unsigned int *resultNum);

/**
 * @brief 激活多个已经持久化授权的文件或目录。\n
 * 调用此接口前，需要先调用OH_FileShare_PersistPermission()完成持久化授权，激活后权限生效。
 *
 * @permission ohos.permission.FILE_ACCESS_PERSIST
 * @param policies 指向FileShare_PolicyInfo实例数组的指针，表示需要激活权限的文件或目录URI策略信息。
 * @param policyNum FileShare_PolicyInfo实例数组的元素个数，取值范围为[1, 500]。
 * @param result 输出参数，指向FileShare_PolicyErrorResult数组指针。\n
 * 请使用OH_FileShare_ReleasePolicyErrorResult()进行资源释放。
 * @param resultNum 输出参数，表示FileShare_PolicyErrorResult数组的元素个数。
 * @return 返回FileManagement模块错误码{@link FileManagement_ErrCode}。\n
 *         {@link ERR_INVALID_PARAMETER} 401 - 输入参数无效。可能的原因有：\n
 *             1. 参数policies或参数result或参数resultNum为空指针；\n
 *             2. 参数policyNum值为0或者超过最大长度(500)；\n
 *             3. 参数policies中携带的uri为空或者length为0或者uri的长度与length不一致。\n
 *         {@link ERR_DEVICE_NOT_SUPPORTED} 801 - 当前设备类型不支持此接口。\n
 *         {@link ERR_PERMISSION_ERROR} 201 - 接口权限校验失败。\n
 *         {@link ERR_ENOMEM} 13900011 - 分配或者拷贝内存失败。\n
 *         {@link ERR_EPERM} 13900001 - 操作不被允许。\n
 *         {@link ERR_OK} 0 - 接口调用成功。
 * @since 12
 */
FileManagement_ErrCode OH_FileShare_ActivatePermission(const FileShare_PolicyInfo *policies, unsigned int policyNum,
    FileShare_PolicyErrorResult **result, unsigned int *resultNum);

/**
 * @brief 取消激活持久化授权过的多个文件或目录。\n
 * 调用此接口前，需要先调用OH_FileShare_ActivatePermission()激活权限。\n
 * 取消激活后，持久化授权仍保留。
 *
 * @permission ohos.permission.FILE_ACCESS_PERSIST
 * @param policies 指向FileShare_PolicyInfo实例数组的指针，表示需要取消激活权限的文件或目录URI策略信息。
 * @param policyNum FileShare_PolicyInfo实例数组的元素个数，取值范围为[1, 500]。
 * @param result 输出参数，指向FileShare_PolicyErrorResult数组指针。\n
 * 请使用OH_FileShare_ReleasePolicyErrorResult()进行资源释放。
 * @param resultNum 输出参数，表示FileShare_PolicyErrorResult数组的元素个数。
 * @return 返回FileManagement模块错误码{@link FileManagement_ErrCode}。\n
 *         {@link ERR_INVALID_PARAMETER} 401 - 输入参数无效。可能的原因有：\n
 *             1. 参数policies或参数result或参数resultNum为空指针；\n
 *             2. 参数policyNum值为0或者超过最大长度(500)；\n
 *             3. 参数policies中携带的uri为空或者length为0或者uri的长度与length不一致。\n
 *         {@link ERR_DEVICE_NOT_SUPPORTED} 801 - 当前设备类型不支持此接口。\n
 *         {@link ERR_PERMISSION_ERROR} 201 - 接口权限校验失败。\n
 *         {@link ERR_ENOMEM} 13900011 - 分配或者拷贝内存失败。\n
 *         {@link ERR_EPERM} 13900001 - 操作不被允许。\n
 *         {@link ERR_OK} 0 - 接口调用成功。
 * @since 12
 */
FileManagement_ErrCode OH_FileShare_DeactivatePermission(const FileShare_PolicyInfo *policies, unsigned int policyNum,
    FileShare_PolicyErrorResult **result, unsigned int *resultNum);

/**
 * @brief 校验所选择的多个文件或目录URI的持久化授权。\n
 * 可在激活权限前调用该接口，确认目标URI是否已经完成持久化授权。
 *
 * @permission ohos.permission.FILE_ACCESS_PERSIST
 * @param policies 指向FileShare_PolicyInfo实例数组的指针，表示需要校验持久化授权的文件或目录URI策略信息。
 * @param policyNum FileShare_PolicyInfo实例数组的元素个数，取值范围为[1, 500]。
 * @param result 输出参数，指向授权校验结果数组。数组元素与policies数组元素一一对应，true表示有持久化授权；false表示不具有持久化授权。\n
 * 需要使用standard library标准库的free()方法释放申请的资源。
 * @param resultNum 输出参数，表示校验结果数组的元素个数。
 * @return 返回FileManagement模块错误码{@link FileManagement_ErrCode}。\n
 *         {@link ERR_INVALID_PARAMETER} 401 - 输入参数无效。可能的原因有：\n
 *             1. 参数policies或参数result或参数resultNum为空指针；\n
 *             2. 参数policyNum值为0或者超过最大长度(500)；\n
 *             3. 参数policies中携带的uri为空或者length为0或者uri的长度与length不一致。\n
 *         {@link ERR_DEVICE_NOT_SUPPORTED} 801 - 当前设备类型不支持此接口。\n
 *         {@link ERR_PERMISSION_ERROR} 201 - 接口权限校验失败。\n
 *         {@link ERR_ENOMEM} 13900011 - 分配或者拷贝内存失败。\n
 *         {@link ERR_EPERM} 13900001 - 操作不被允许。可能的原因为policies中携带的所有uri都不符合规范或者uri转换出来的路径不存在。\n
 *         {@link ERR_OK} 0 - 接口调用成功。
 * @since 12
 */
FileManagement_ErrCode OH_FileShare_CheckPersistentPermission(
    const FileShare_PolicyInfo *policies, unsigned int policyNum, bool **result, unsigned int *resultNum);

/**
 * @brief 释放FileShare_PolicyErrorResult指针指向的内存资源。\n
 * 该资源由OH_FileShare_PersistPermission、OH_FileShare_RevokePermission、OH_FileShare_ActivatePermission
 * 和OH_FileShare_DeactivatePermission通过result输出。
 *
 * @param errorResult 指向FileShare_PolicyErrorResult实例数组的指针。
 * @param resultNum FileShare_PolicyErrorResult实例数组的元素个数。
 * @since 12
 */
void OH_FileShare_ReleasePolicyErrorResult(FileShare_PolicyErrorResult *errorResult, unsigned int resultNum);
#ifdef __cplusplus
};
#endif
/** @} */
#endif // FILE_MANAGEMENT_OH_FILE_SHARE_H
