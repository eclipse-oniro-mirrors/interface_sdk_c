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
 * @brief 内容嵌入（ContentEmbed）模块提供对象编辑（Object Editor，简称OE）功能框架与技术，支持应用间文档的嵌入与协同编辑。
 * 通过OE技术实现的被嵌入文档（简称OE文档），在客户端界面中可能呈现为缩略图或者快照（Snapshot），
 * 也可能以标准格式序列化为一段二进制数据保存在内存或者某个文件（称为OE格式文件）中。
 *
 * @syscap SystemCapability.ContentEmbed.ObjectEditor
 * @since 24
 */

/**
 * @file content_embed_common.h
 *
 * @brief 提供内容嵌入模块的错误码定义和嵌入文档支持能力的类型枚举描述。
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
 * @brief 表示被嵌入文档的标识符OEID的最大字符串长度。
 *
 * @since 24
 */
#define MAX_OEID_LENGTH (1 * 40)

/**
 * @brief 提供内容嵌入模块的错误码定义。
 *
 * @since 24
 */
typedef enum ContentEmbed_ErrorCode {
    /**
     * @brief 操作成功。
     *
     * @since 24
     */
    CE_ERR_OK = 0,
    /**
     * @brief 权限校验失败。
     *
     * @since 24
     */
    CE_PERMISSION_DENIED = 201,
    /**
     * @brief 参数不合法。
     *
     * @since 24
     */
    CE_ERR_PARAM_INVALID = 401,
    /**
     * @brief 当前设备不支持此功能。
     *
     * @since 24
     */
    CE_ERR_DEVICE_NOT_SUPPORTED = 801,
    /**
     * @brief 返回空指针，可能是内存分配失败或内部错误。
     *
     * @since 24
     */
    CE_ERR_NULL_POINTER = 35300001,
    /**
     * @brief 客户端未注册对应的回调函数。
     *
     * @since 24
     */
    CE_ERR_CLIENT_CALLBACK_NOT_REGISTERED = 35300002,
    /**
     * @brief OE Extension发生未知错误。
     *
     * @since 24
     */
    CE_ERR_EXTENSION_ERROR = 35300003,
    /**
     * @brief 系统服务出现异常，可能是服务未启动、连接中断或权限不足。
     *
     * @since 24
     */
    CE_ERR_SYSTEM_ABNORMAL = 35300004,
    /**
     * @brief OE文档Storage对象相关操作失败。
     *
     * @since 24
     */
    CE_ERR_STORAGE_OPERATION_FAILED = 35300005,
    /**
     * @brief OE文档Stream对象相关操作失败。
     *
     * @since 24
     */
    CE_ERR_STREAM_OPERATION_FAILED = 35300006,
    /**
     * @brief 文件操作失败，可能是文件不存在、权限不足、路径错误或磁盘空间不足。
     *
     * @since 24
     */
    CE_ERR_FILE_OPERATION_FAILED = 35300007,
    /**
     * @brief 当前应用正在DLP沙箱环境中运行，暂不支持调用相关功能。
     *
     * @since 24
     */
    CE_ERR_IN_DLP_SANDBOX = 35300008,
    /**
     * @brief ImagePacker操作失败。
     *
     * @since 24
     */
    CE_ERR_IMAGE_PACKER_OPERATION_FAILED = 35300009,
    /**
     * @brief 客户端注册的回调函数在执行过程中发生异常。
     *
     * @since 24
     */
    CE_ERR_CLIENT_CALLBACK_FAILED = 35300010,
    /**
     * @brief OE Extension意外退出。
     *
     * @since 24
     */
    CE_ERR_EXTENSION_ABNORMAL_EXIT = 35300011,
    /**
     * @brief 链接到不允许被链接目录中的文件，如应用沙箱目录内的文件。
     *
     * @since 24
     */
    CE_ERR_INVALID_LINKING_PATH = 35300012,
    /**
     * @brief 当前OE Extension连接超出限制。
     *
     * @since 24
     */
    CE_ERR_CONNECT_LIMIT_EXCEED = 35300013,
    /**
     * @brief 当前文件未授权。
     *
     * @since 24
     */
    CE_ERR_FILE_NOT_GRANT = 35300014,
    /**
     * @brief 当前磁盘空间不足。
     *
     * @since 24
     */
    CE_ERR_DISK_FULL = 35300015,
    /**
     * @brief 当前OE Extension不支持该能力。
     *
     * @since 24
     */
    CE_ERR_EXTENSION_NOT_SUPPORT = 35300016,
} ContentEmbed_ErrorCode;

/**
 * @brief 嵌入文档对象支持的功能枚举，并支持通过位掩码组合多个能力值。
 *
 * @since 24
 */
typedef enum ContentEmbed_CapabilityCode {
    /**
     * @brief 表示支持获取OE文档的快照图像。
     *
     * @since 24
     */
    CE_CAPABILITY_SUPPORT_SNAPSHOT = 1 << 0,
    /**
     * @brief 表示支持对OE文档进行编辑操作。
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