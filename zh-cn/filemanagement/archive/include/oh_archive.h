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
 * @{
 *
 * @brief 提供文件压缩及解压缩、数据的流式压缩及解压缩、缓冲区压缩及解压缩的能力。
 * @since 26.0.0
 */

/**
 * @file oh_archive.h
 *
 * @brief 压缩解压缩模块接口定义，提供文件压缩解压缩、数据的流式压缩解压缩，缓冲区压缩解压缩的native接口。
 * @kit CoreFileKit
 * @include <filemanagement/archive/oh_archive.h>
 * @library liboharchive.so
 * @syscap SystemCapability.FileManagement.File.FileIO
 * @since 26.0.0
 */
#ifndef FILE_MANAGEMENT_ARCHIVE_OH_ARCHIVE_H
#define FILE_MANAGEMENT_ARCHIVE_OH_ARCHIVE_H

#include <stdint.h>
#include "oh_archive_errcode.h"

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */
/**
 * @brief 文件压缩器的上下文结构体指针。
 * @since 26.0.0
 */
typedef struct ArchiveWriteCtx *OH_Archive_Writer_Ctx;
/**
 * @brief 文件解压缩器的上下文结构体指针。
 * @since 26.0.0
 */
typedef struct ArchiveReadCtx *OH_Archive_Reader_Ctx;
/**
 * @brief 流式压缩器的上下文结构体指针。
 * @since 26.0.0
 */
typedef struct ArchiveStreamWriteCtx *OH_Archive_StreamWrite_Ctx;
/**
 * @brief 流式解压缩器的上下文结构体指针。
 * @since 26.0.0
 */
typedef struct ArchiveStreamReadCtx *OH_Archive_StreamRead_Ctx;

/**
 * @brief 文件格式枚举。
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief ZIP格式。
     * @since 26.0.0
     */
    OH_ARCHIVE_FMT_ZIP = 0
} OH_Archive_Format;

/**
 * @brief 压缩算法枚举。
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief 不压缩。
     * @since 26.0.0
     */
    OH_ARCHIVE_NO_COMPRESSION = 0,
    /**
     * @brief DEFLATE压缩算法。
     * @since 26.0.0
     */
    OH_ARCHIVE_COMPRESS_DEFLATE = 8
} OH_Archive_CompressMethod;

/**
 * @brief 文件打开模式枚举。
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief 创建模式。新建一个文件，如果文件已存在，则覆盖。
     * @since 26.0.0
     */
    OH_ARCHIVE_OPEN_MODE_CREATE = 0
} OH_Archive_OpenMode;

/**
 * @brief 文件进度控制类型枚举。
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief 继续压缩/解压缩操作。
     * @since 26.0.0
     */
    OH_ARCHIVE_PROGRESS_CONTINUE = 0,
    /**
     * @brief 取消压缩/解压缩操作。
     * @since 26.0.0
     */
    OH_ARCHIVE_PROGRESS_CANCEL = 1
} OH_Archive_ProgressType;

/**
 * @brief 流式压缩/解压缩信息结构体。
 * @since 26.0.0
 */
typedef struct {
    /**
     * @brief 压缩/解压缩前输入数据大小，单位为bytes。
     * @since 26.0.0
     */
    uint64_t totalInSize;
    /**
     * @brief 压缩/解压缩后输出数据大小，单位为bytes。
     * @since 26.0.0
     */
    uint64_t totalOutSize;
    /**
     * @brief 未压缩数据的校验和。当{@link OH_Archive_StreamChecksumAlg}设置为OH_ARCHIVE_NO_CHECKSUM时，checksum为0。
     * @since 26.0.0
     */
    uint32_t checksum;
} OH_Archive_StreamInfo;

/**
 * @brief 用于计算校验和的哈希算法。
 * @since 26.0.0
 */
typedef enum {
    /**
     * @brief 不额外计算哈希值。
     * @since 26.0.0
     */
    OH_ARCHIVE_NO_CHECKSUM = 0,
    /**
     * @brief 使用CRC32（Cyclic Redundancy Check，循环冗余校验）计算校验和。
     * @since 26.0.0
     */
    OH_ARCHIVE_CRC32 = 1
} OH_Archive_StreamChecksumAlg;

/**
 * @brief 流式压缩配置结构体。
 * @since 26.0.0
 */
typedef struct {
    /**
     * @brief 内存块大小，单位为bytes。当{@link OH_Archive_CompressMethod}设置为OH_ARCHIVE_COMPRESS_DEFLATE时，blockSize需不小于32768bytes。
     * @since 26.0.0
     */
    uint32_t blockSize;
    /**
     * @brief 线程数，取值为正整数，如果大于设备核数，则使用设备核数。
     * @since 26.0.0
     */
    int32_t threadNum;
    /**
     * @brief 用于计算校验和的哈希算法。
     * @since 26.0.0
     */
    OH_Archive_StreamChecksumAlg checksum;
    /**
     * @brief 压缩算法。流式压缩和流式解压缩只支持OH_ARCHIVE_COMPRESS_DEFLATE。
     * @since 26.0.0
     */
    OH_Archive_CompressMethod method;
} OH_Archive_Stream_Config;

/**
 * @brief 定义进度处理回调函数的类型。
 * @param progress 处理进度百分比，取值范围为[0, 100]。
 * @param userData 指向用户自定义数据的指针，在调用回调时传入。
 * @return OH_ARCHIVE_PROGRESS_CONTINUE - 继续当前压缩/解压缩操作。\n
 *         OH_ARCHIVE_PROGRESS_CANCEL - 取消当前压缩/解压缩操作。
 * @since 26.0.0
 */
typedef OH_Archive_ProgressType (*OH_Archive_ProgressHandlerWithData)(int32_t progress, void *userData);

/**
 * @brief 用户自定义回调函数指针类型，用于处理压缩后的数据。
 * @param userData 用户自定义上下文，将在回调中传回。
 * @param data 指向压缩数据的指针。
 * @param size 压缩数据的长度。
 * @return 成功处理的字节数。
 * @since 26.0.0
 */
typedef uint64_t (*OH_Archive_Stream_OutputHandler)(const void* data, uint64_t size, void* userData);

/**
 * @brief 打开文件进行读取。
 * @param infile 源文件的路径，应用需要有读取权限，绝对路径长度需不超过4096bytes。
 * @return 返回文件读取器的上下文结构体，操作失败时返回NULL。
 * @since 26.0.0
 * @release archive/OH_Archive_Reader_Close {return}
 */
OH_Archive_Reader_Ctx OH_Archive_Reader_OpenFile(const char *infile);

/**
 * @brief 设置文件解压缩器的进度回调函数及用户数据。
 * @param arc 文件解压缩器上下文句柄。
 * @param progressHandler 用于处理进度更新的回调函数。
 * @param userData 用户处理进度回调时自定义的上下文数据。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Reader_SetProgressHandlerWithData(OH_Archive_Reader_Ctx arc,
                                                                OH_Archive_ProgressHandlerWithData progressHandler,
                                                                void *userData);
/**
 * @brief 从压缩包中提取所有文件。
 * @param arc 文件解压缩器上下文句柄。
 * @param outDir 输出目录路径，应用需要有写入权限。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Reader_ExtractAllFile(OH_Archive_Reader_Ctx arc, const char *outDir);

/**
 * @brief 关闭已打开的压缩文件并释放相关资源。
 * @param arc 文件解压缩器上下文句柄。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Reader_Close(OH_Archive_Reader_Ctx arc);

/**
 * @brief 创建并打开压缩文件。
 * @param outfile 目标压缩文件的路径，应用需有写入权限，绝对路径长度需不超过4096bytes。
 * @param openMode 文件打开模式。
 * @param fmt 压缩包格式。
 * @return 返回文件压缩器上下文句柄，操作失败时返回NULL。
 * @since 26.0.0
 * @release archive/OH_Archive_Writer_Close {return}
 */
OH_Archive_Writer_Ctx OH_Archive_Writer_OpenFile(const char *outfile,
                                                 OH_Archive_OpenMode openMode,
                                                 OH_Archive_Format fmt);

/**
 * @brief 设置压缩文件的压缩算法。
 * @param arc 文件压缩器的上下文句柄。
 * @param method 压缩算法。
 * @param compressLevel 压缩等级。对于OH_ARCHIVE_COMPRESS_DEFLATE，压缩级别为0到9，默认等级为6。0表示不压缩，压缩等级越高，压缩率越高，速度越慢。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Writer_SetCompressMethod(OH_Archive_Writer_Ctx arc,
                                                       OH_Archive_CompressMethod method, int32_t compressLevel);

/**
 * @brief 设置文件压缩器的进度回调函数及用户数据。
 * @param arc 文件压缩器上下文句柄。
 * @param progressHandler 用于处理进度更新的回调函数。
 * @param userData 用户处理进度回调时自定义的上下文数据。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Writer_SetProgressHandlerWithData(OH_Archive_Writer_Ctx arc,
                                                                OH_Archive_ProgressHandlerWithData progressHandler,
                                                                void *userData);

/**
 * @brief 向压缩包中添加文件列表。
 * @param arc 文件压缩器上下文句柄。
 * @param infiles 待压缩的文件。
 * @param fileNum 文件数量。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Writer_Add(OH_Archive_Writer_Ctx arc, const char **infiles, uint64_t fileNum);

/**
 * @brief 关闭文件压缩器。
 * 该函数完成压缩包写入过程，将缓冲数据刷新到输出，并释放与文件压缩器的上下文结构体相关的资源。
 * @param arc 文件压缩器上下文句柄。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Writer_Close(OH_Archive_Writer_Ctx arc);

/**
 * @brief 计算给定源数据长度的最大压缩后数据大小。
 * @param method 压缩算法类型。当前仅支持OH_ARCHIVE_COMPRESS_DEFLATE。
 * @param sourceLen 待压缩源数据的长度，单位为bytes。
 * @return 返回压缩后数据大小的最大值，单位为bytes。
 * @since 26.0.0
 */
uint64_t OH_Archive_BufferWriteCompressBound(OH_Archive_CompressMethod method, uint64_t sourceLen);

/**
 * @brief 向缓冲区写入数据并进行压缩。
 * @param dstBuffer 指向目标缓冲区的指针，用于存储压缩后的数据。
 * @param dstSize 指向目标缓冲区大小的指针，传入缓冲区大小，输出实际写入的大小，单位为bytes。
 * @param srcBuffer 指向包含待压缩数据的源缓冲区的指针。
 * @param srcSize 源缓冲区数据的大小，单位为bytes。
 * @param method 压缩算法类型。当前仅支持OH_ARCHIVE_COMPRESS_DEFLATE。
 * @param compressLevel 压缩等级。对于OH_ARCHIVE_COMPRESS_DEFLATE，压缩级别为0到9，默认等级为6。0表示不压缩，压缩等级越高，压缩率越高，速度越慢。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_BufferWrite(uint8_t *dstBuffer, uint64_t *dstSize,
                                          const uint8_t *srcBuffer, uint64_t srcSize,
                                          OH_Archive_CompressMethod method, int32_t compressLevel);


/**
 * @brief 从缓冲区读取数据并进行解压缩。
 * @param dstBuffer 指向目标缓冲区的指针，用于存储解压缩后的数据。
 * @param dstSize 指向目标缓冲区大小的指针，传入缓冲区大小，输出实际解压缩后的大小，单位为bytes。
 * @param srcBuffer 指向包含待解压缩数据的源缓冲区的指针。
 * @param srcSize 源缓冲区数据的大小，单位为bytes。
 * @param method 解压缩算法类型。当前仅支持OH_ARCHIVE_COMPRESS_DEFLATE。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_BufferRead(uint8_t *dstBuffer, uint64_t *dstSize,
                                         const uint8_t *srcBuffer, uint64_t srcSize,
                                         OH_Archive_CompressMethod method);

/**
 * @brief 创建流式压缩的上下文结构体。
 * @param config 压缩配置。
 * @return 返回流式压缩的上下文结构体。创建失败时返回NULL。
 * @since 26.0.0
 * @release archive/OH_Archive_StreamWrite_Destroy {return}
 */
OH_Archive_StreamWrite_Ctx OH_Archive_StreamWrite_Create(OH_Archive_Stream_Config config);

/**
 * @brief 启动压缩任务，初始化用户回调函数和用户数据。
 * @param ctx 流式压缩的上下文结构体。
 * @param outputHandler 用户自定义的压缩数据回调函数。
 * @param userData 用户自定义上下文，将在回调中传回。userData由调用方持有，在{@link OH_Archive_StreamWrite_End}完成前必须保持有效。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamWrite_Start(OH_Archive_StreamWrite_Ctx ctx,
                                                OH_Archive_Stream_OutputHandler outputHandler, void* userData);

/**
 * @brief 设置流式压缩的压缩级别。
 * @param ctx 流式压缩的上下文结构体。
 * @param compressLevel 压缩等级。对于OH_ARCHIVE_COMPRESS_DEFLATE，压缩级别为0到9，默认等级为6。0表示不压缩，压缩等级越高，压缩率越高，速度越慢。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamWrite_SetCompressLevel(OH_Archive_StreamWrite_Ctx ctx, int32_t compressLevel);

/**
 * @brief 强制取消当前压缩操作。
 * @param ctx 流式压缩的上下文结构体。
 * @return 返回接口执行的结果。取消成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamWrite_Cancel(OH_Archive_StreamWrite_Ctx ctx);

/**
 * @brief 提交压缩数据。
 * @param ctx 流式压缩的上下文结构体。
 * @param data 待压缩的原始数据。
 * @param size 待压缩数据的大小，单位为bytes。
 * @return 返回接口执行的结果。压缩成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamWrite_Update(OH_Archive_StreamWrite_Ctx ctx, const uint8_t* data, uint64_t size);


/**
 * @brief 结束压缩，刷新所有剩余数据。
 * @param ctx 流式压缩的上下文结构体。
 * @param streamInfo 压缩信息，包括原始数据大小、压缩后数据大小和CRC32值。
 * @return 返回接口执行的结果。压缩成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamWrite_End(OH_Archive_StreamWrite_Ctx ctx, OH_Archive_StreamInfo *streamInfo);

/**
 * @brief 销毁压缩实例并释放相关资源。
 * @param ctx 流式压缩的上下文结构体。
 * @since 26.0.0
 */
void OH_Archive_StreamWrite_Destroy(OH_Archive_StreamWrite_Ctx ctx);

/**
 * @brief 创建流式解压缩的上下文结构体。
 * @param config 解压缩配置信息。
 * @return 返回流式解压缩的上下文结构体。创建失败时返回NULL。
 * @since 26.0.0
 * @release archive/OH_Archive_StreamRead_Destroy {return}
 */
OH_Archive_StreamRead_Ctx OH_Archive_StreamRead_Create(OH_Archive_Stream_Config config);

/**
 * @brief 启动解压缩任务，初始化用户回调函数和用户数据。
 * @param ctx 流式解压缩的上下文结构体。
 * @param outputHandler 用户自定义的解压缩数据回调函数。
 * @param userData 用户自定义上下文数据，将在回调中传回。userData由调用方拥有，在{@link OH_Archive_StreamRead_End}完成前必须保持有效。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamRead_Start(OH_Archive_StreamRead_Ctx ctx,
                                               OH_Archive_Stream_OutputHandler outputHandler, void* userData);

/**
 * @brief 强制取消当前解压缩操作。
 * @param ctx 流式解压缩的上下文结构体。
 * @return 返回接口执行的结果。取消成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamRead_Cancel(OH_Archive_StreamRead_Ctx ctx);

/**
 * @brief 提交解压缩数据。
 * @param ctx 流式解压缩的上下文结构体。
 * @param data 待解压缩的数据。
 * @param size 数据大小，单位为bytes。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamRead_Update(OH_Archive_StreamRead_Ctx ctx, const uint8_t* data, uint64_t size);

/**
 * @brief 结束解压缩，刷新所有剩余数据并清理内存。
 * @param ctx 流式解压缩的上下文结构体。
 * @param streamInfo 解压缩信息，包括原始数据大小、压缩后数据大小和CRC32值。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamRead_End(OH_Archive_StreamRead_Ctx ctx, OH_Archive_StreamInfo *streamInfo);

/**
 * @brief 销毁解压缩实例并释放相关资源。
 * @param ctx 流式解压缩的上下文结构体。
 * @since 26.0.0
 */
void OH_Archive_StreamRead_Destroy(OH_Archive_StreamRead_Ctx ctx);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */
/** @} */
#endif /* FILE_MANAGEMENT_ARCHIVE_OH_ARCHIVE_H */