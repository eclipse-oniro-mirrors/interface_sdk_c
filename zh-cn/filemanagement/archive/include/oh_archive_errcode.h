/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * You may not use this file except in compliance with the License.
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
 * @addtogroup Archive
 *
 * @brief 提供文件压缩及解压、数据的流式压缩及解压、缓冲区压缩及解压的能力。
 * @{
 * @since 26.0.0
 */

/**
 * @file oh_archive_errcode.h
 *
 * @brief 提供压缩解压模块错误码的声明。
 * @kit CoreFileKit
 * @include <filemanagement/archive/oh_archive_errcode.h>
 * @library liboharchive.so
 * @syscap SystemCapability.FileManagement.File.FileIO
 * @since 26.0.0
 */
#ifndef FILE_MANAGEMENT_ARCHIVE_OH_ARCHIVE_ERRCODE_H
#define FILE_MANAGEMENT_ARCHIVE_OH_ARCHIVE_ERRCODE_H

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief 压缩解压模块错误码。
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief 操作成功。
     * @since 26.0.0
     */
    OH_ARCHIVE_OK = 0,
    /**
     * @brief 无效入参。
     * @since 26.0.0
     */
    OH_ARCHIVE_PARAM_ERROR = 401,
    /**
     * @brief 未知错误。
     * @since 26.0.0
     */
    OH_ARCHIVE_UNKNOWN_ERROR = 13900100,
    /**
     * @brief 用户取消操作。
     * @since 26.0.0
     */
    OH_ARCHIVE_CANCEL_ERROR = 13900101,
    /**
     * @brief 不支持当前压缩算法。
     * @since 26.0.0
     */
    OH_ARCHIVE_UNSUPPORTED_ERROR = 13900102,
    /**
     * @brief 内存分配失败。
     * @since 26.0.0
     */
    OH_ARCHIVE_MEM_ERROR = 13900103,
    /**
     * @brief 打开压缩包文件失败。
     * @since 26.0.0
     */
    OH_ARCHIVE_OPEN_ERROR = 13900104,
    /**
     * @brief 写操作失败。
     * @since 26.0.0
     */
    OH_ARCHIVE_WRITE_ERROR = 13900105,
    /**
     * @brief 读操作失败。
     * @since 26.0.0
     */
    OH_ARCHIVE_READ_ERROR = 13900106,
    /**
     * @brief 流输出错误。
     * @since 26.0.0
     */
    OH_ARCHIVE_STREAM_OUTPUT_ERROR = 13900107,
    /**
     * @brief 输出缓冲区空间不足。
     * @since 26.0.0
     */
    OH_ARCHIVE_INSUFFICIENT_OUTBUF_ERROR = 13900108,
    /**
     * @brief 磁盘空间不足。
     * @since 26.0.0
     */
    OH_ARCHIVE_NO_SPACE_ERROR = 13900200,
    /**
     * @brief 路径不存在。
     * @since 26.0.0
     */
    OH_ARCHIVE_PATH_NOT_EXIST_ERROR = 13900201,
    /**
     * @brief 路径已存在。
     * @since 26.0.0
     */
    OH_ARCHIVE_PATH_EXISTS_ERROR = 13900202,
    /**
     * @brief 路径访问错误。
     * @since 26.0.0
     */
    OH_ARCHIVE_PATH_ACCESS_ERROR = 13900203,
    /**
     * @brief 文件名过长。
     * @since 26.0.0
     */
    OH_ARCHIVE_NAME_TOO_LONG_ERROR = 13900204,
    /**
     * @brief 完整路径过长。
     * @since 26.0.0
     */
    OH_ARCHIVE_FULL_PATH_TOO_LONG_ERROR = 13900205,
    /**
     * @brief 数据完整性错误。
     * @since 26.0.0
     */
    OH_ARCHIVE_DATA_ERROR = 13900300,
    /**
     * @brief CRC校验错误。
     * @since 26.0.0
     */
    OH_ARCHIVE_CRC_ERROR = 13900301,
    /**
     * @brief DEFLATE算法错误。
     * @since 26.0.0
     */
    OH_ARCHIVE_DEFLATE_ERROR = 13900302
} OH_Archive_ErrCode;

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */
/** @} */
#endif /* FILE_MANAGEMENT_ARCHIVE_OH_ARCHIVE_ERRCODE_H */