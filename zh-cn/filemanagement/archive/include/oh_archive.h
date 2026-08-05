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
 * @addtogroup Archive
 * @{
 *
 * @brief 压缩解压缩模块接口定义，提供文件压缩解压缩、数据的流式压缩解压缩，缓冲区压缩解压缩的native接口。
 * @since 26.0.0
 */

/**
 * @file oh_archive.h
 *
 * @brief Provides archive APIs.
 * @kit CoreFileKit
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
     * @brief 压缩前的总输入字节数。
     * @since 26.0.0
     */
    uint64_t totalInSize;
    /**
     * @brief 压缩后的总输出字节数。
     * @since 26.0.0
     */
    uint64_t totalOutSize;
    /**
     * @brief 校验和，如果设置为OH_ARCHIVE_NO_CHECKSUM则为零。
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
     * @brief 每个内存块的大小，单位为bytes（例如32768 bytes、65536 bytes）。
     * 对于OH_ARCHIVE_COMPRESS_DEFLATE，blockSize需大于等于32768 bytes。
     * @since 26.0.0
     */
    uint32_t blockSize;
    /**
     * @brief 线程数量。
     * @since 26.0.0
     */
    int32_t threadNum;
    /**
     * @brief 用于计算校验和的哈希算法。
     * @since 26.0.0
     */
    OH_Archive_StreamChecksumAlg checksum;
    /**
     * @brief 压缩算法。
     * @since 26.0.0
     */
    OH_Archive_CompressMethod method;
} OH_Archive_Stream_Config;

/**
 * @brief 定义进度处理回调函数的类型。
 * @param progress 处理进度百分比，取值范围为[0, 100]。
 * @param userData 指向用户自定义数据的指针，在调用回调时传入。
 * @return 返回压缩/解压缩的OH_Archive_ProgressType值。
 *         {@link OH_ARCHIVE_PROGRESS_CONTINUE} - continue current compression/decompression operation.
 *         {@link OH_ARCHIVE_PROGRESS_CANCEL} - cancel current compression/decompression operation.
 * @since 26.0.0
 */
typedef OH_Archive_ProgressType (*OH_Archive_ProgressHandlerWithData)(int32_t progress, void *userData);

/**
 * @brief 用户自定义回调函数指针类型，用于处理压缩后的数据。
 * @param data 指向压缩数据的指针。
 * @param size 压缩数据的长度。
 * @param userData 用户自定义上下文，将在回调中传回。
 * @return 成功处理的字节数。
 * @since 26.0.0
 */
typedef uint64_t (*OH_Archive_Stream_OutputHandler)(const void* data, uint64_t size, void* userData);

/**
 * @brief Opens an archive file for reading.
 * @note The returned context must be freed by calling OH_Archive_Reader_Close() to release allocated resources.
 * @param infile 源文件的路径，应用需要有读取权限，绝对路径长度需不超过4096bytes。
 * @return 返回文件读取器的上下文结构体，操作失败时返回NULL。
 * @since 26.0.0
 * @release archive/OH_Archive_Reader_Close {return}
 */
OH_Archive_Reader_Ctx OH_Archive_Reader_OpenFile(const char *infile);

/**
 * @brief Sets the progress callback function with user data for the archive reader.
 * @param arc 文件解压缩器上下文句柄。
 * @param progressHandler 用于处理进度更新的回调函数。
 * @param userData 用户处理进度回调时自定义的上下文数据。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 *         {@link OH_ARCHIVE_OK} - Execution successful
 *         {@link OH_ARCHIVE_PARAM_ERROR} - Invalid input parameters.
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Reader_SetProgressHandlerWithData(OH_Archive_Reader_Ctx arc,
                                                                OH_Archive_ProgressHandlerWithData progressHandler,
                                                                void *userData);
/**
 * @brief Extract all files from the archive.
 * @param arc 文件解压缩器上下文句柄。
 * @param outDir 输出目录路径，应用需要有写入权限。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Reader_ExtractAllFile(OH_Archive_Reader_Ctx arc, const char *outDir);

/**
 * @brief Closes an opened archive file and releases associated resources.
 * @param arc 文件解压缩器上下文句柄。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Reader_Close(OH_Archive_Reader_Ctx arc);

/**
 * @brief Creates and opens an archive file.
 * @note The returned context must be freed by calling OH_Archive_Writer_Close() to release allocated resources.
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
 * @brief Set the compression method for the archive file
 * @param arc 文件压缩器的上下文句柄。
 * @param method 压缩算法。
 * @param compressLevel 压缩等级。对于OH_ARCHIVE_COMPRESS_DEFLATE，压缩级别为0到9，默认等级为6。0表示不压缩，压缩等级越高，压缩率越高，速度越慢。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 *         {@link OH_ARCHIVE_OK} - Execution successful.
 *         {@link OH_ARCHIVE_PARAM_ERROR} - Invalid input parameters.
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Writer_SetCompressMethod(OH_Archive_Writer_Ctx arc,
                                                       OH_Archive_CompressMethod method, int32_t compressLevel);

/**
 * @brief Set the compression progress function for the archive file.
 * @param arc 文件压缩器上下文句柄。
 * @param progressHandler 用于处理进度更新的回调函数。
 * @param userData 用户处理进度回调时自定义的上下文数据。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 *         {@link OH_ARCHIVE_OK} - Execution successful
 *         {@link OH_ARCHIVE_PARAM_ERROR} - Invalid input parameters.
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Writer_SetProgressHandlerWithData(OH_Archive_Writer_Ctx arc,
                                                                OH_Archive_ProgressHandlerWithData progressHandler,
                                                                void *userData);

/**
 * @brief Adds a list of files to the archive.
 * @param arc 文件压缩器上下文句柄。
 * @param infiles 待压缩的文件。
 * @param fileNum 文件数量。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Writer_Add(OH_Archive_Writer_Ctx arc, const char **infiles, uint64_t fileNum);

/**
 * @brief Closes the archive writer.
 * This function finalizes the archive writing process, flushes any buffered data to the output,
 * and releases the resources associated with the archive context.
 * @param arc 文件压缩器上下文句柄。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_Writer_Close(OH_Archive_Writer_Ctx arc);

/**
 * @brief Calculates the maximum compressed data size for a given source length.
 * @param method 压缩算法类型。当前仅支持OH_ARCHIVE_COMPRESS_DEFLATE。
 * @param sourceLen 待压缩源数据的长度，单位为bytes。
 * @return 返回压缩后数据大小的最大值，单位为bytes。
 * @since 26.0.0
 */
uint64_t OH_Archive_BufferWriteCompressBound(OH_Archive_CompressMethod method, uint64_t sourceLen);

/**
 * @brief Writes data to buffer and compresses it.
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
 * @brief Reads data from buffer and decompresses it.
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
 * @brief Creates a compression instance.
 * @param config 压缩配置。
 * @return 返回流式压缩的上下文结构体。创建失败时返回NULL。
 * @since 26.0.0
 * @release archive/OH_Archive_StreamWrite_Destroy {return}
 */
OH_Archive_StreamWrite_Ctx OH_Archive_StreamWrite_Create(OH_Archive_Stream_Config config);

/**
 * @brief Starts a compression task, initializing user callback function and user data.
 * @param ctx 流式压缩的上下文结构体。
 * @param outputHandler 用户自定义的压缩数据回调函数。
 * @param userData 用户自定义上下文，将在回调中传回。userData由调用方持有，在OH_Archive_StreamWrite_End完成前必须保持有效。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamWrite_Start(OH_Archive_StreamWrite_Ctx ctx,
                                                OH_Archive_Stream_OutputHandler outputHandler, void* userData);

/**
 * @brief Sets the compression level for StreamCompress.
 * @param ctx 流式压缩的上下文结构体。
 * @param compressLevel 压缩等级。对于OH_ARCHIVE_COMPRESS_DEFLATE，压缩级别为0到9，默认等级为6。0表示不压缩，压缩等级越高，压缩率越高，速度越慢。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamWrite_SetCompressLevel(OH_Archive_StreamWrite_Ctx ctx, int32_t compressLevel);

/**
 * @brief Forces cancellation of the current blocking operation and wakes up all waiting threads.
 * @param ctx 流式压缩的上下文结构体。
 * @return 返回接口执行的结果。取消成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamWrite_Cancel(OH_Archive_StreamWrite_Ctx ctx);

/**
 * @brief Submits compression data. This interface will block when the memory pool is full.
 * @param ctx 流式压缩的上下文结构体。
 * @param data 待压缩的原始数据。
 * @param size 待压缩数据的大小，单位为bytes。
 * @return 返回接口执行的结果。压缩成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamWrite_Update(OH_Archive_StreamWrite_Ctx ctx, const uint8_t* data, uint64_t size);


/**
 * @brief Ends the compression, flushes all remaining data, and cleans up memory.
 * @param ctx 流式压缩的上下文结构体。
 * @param streamInfo 压缩信息，包括原始数据大小、压缩后数据大小和CRC32值。
 * @return 返回接口执行的结果。压缩成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamWrite_End(OH_Archive_StreamWrite_Ctx ctx, OH_Archive_StreamInfo *streamInfo);

/**
 * @brief Destroys the compression instance and releases associated resources.
 * @param ctx 流式压缩的上下文结构体。
 * @since 26.0.0
 */
void OH_Archive_StreamWrite_Destroy(OH_Archive_StreamWrite_Ctx ctx);

/**
 * @brief Create a decompression instance
 * @param config 解压缩配置信息。
 * @return 返回流式解压缩的上下文结构体。创建失败时返回NULL。
 * @since 26.0.0
 * @release archive/OH_Archive_StreamRead_Destroy {return}
 */
OH_Archive_StreamRead_Ctx OH_Archive_StreamRead_Create(OH_Archive_Stream_Config config);

/**
 * @brief Start a decompression task, initialize user callback function and user data
 * @param ctx 流式解压缩的上下文结构体。
 * @param outputHandler 用户自定义的解压缩数据回调函数。
 * @param userData 用户自定义上下文数据，将在回调中传回。userData由调用方拥有，在OH_Archive_StreamRead_End完成前必须保持有效。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamRead_Start(OH_Archive_StreamRead_Ctx ctx,
                                               OH_Archive_Stream_OutputHandler outputHandler, void* userData);

/**
 * @brief Force cancellation of the current blocking operation and wake up all waiting threads
 * @param ctx 流式解压缩的上下文结构体。
 * @return 返回接口执行的结果。取消成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamRead_Cancel(OH_Archive_StreamRead_Ctx ctx);

/**
 * @brief Submit decompression data. This interface will block when the memory pool is full
 * @param ctx 流式解压缩的上下文结构体。
 * @param data 待解压缩的数据。
 * @param size 数据大小，单位为bytes。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamRead_Update(OH_Archive_StreamRead_Ctx ctx, const uint8_t* data, uint64_t size);

/**
 * @brief End the decompression, flush all remaining data, and clean up memory
 * @param ctx 流式解压缩的上下文结构体。
 * @param streamInfo 解压缩信息，包括原始数据大小、压缩后数据大小和CRC32值。
 * @return 返回接口执行的结果。成功返回OH_ARCHIVE_OK，失败返回对应错误码。
 * @since 26.0.0
 */
OH_Archive_ErrCode OH_Archive_StreamRead_End(OH_Archive_StreamRead_Ctx ctx, OH_Archive_StreamInfo *streamInfo);

/**
 * @brief Destroy the decompression instance and release associated resources
 * @param ctx 流式解压缩的上下文结构体。
 * @since 26.0.0
 */
void OH_Archive_StreamRead_Destroy(OH_Archive_StreamRead_Ctx ctx);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */
/** @} */
#endif /* FILE_MANAGEMENT_ARCHIVE_OH_ARCHIVE_H */
