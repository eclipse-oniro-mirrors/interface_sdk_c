/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
 * @addtogroup rawfile
 * @{
 *
 * @brief Provides native functions for the resource manager to operate raw file directories and their raw files.
 *
 * You can use the resource manager to traverse, open, seek, read, and close raw files.
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file raw_file.h
 *
 * @brief 提供rawfile文件相关功能，功能包括搜索、读取和关闭。
 *
 * @syscap SystemCapability.Global.ResourceManager
 * @library librawfile.z.so
 * @kit LocalizationKit
 * @since 8
 * @version 1.0
 */
#ifndef GLOBAL_RAW_FILE_H
#define GLOBAL_RAW_FILE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct RawFile;

/**
 * @brief 提供对较大rawfile的访问功能。
 *
 * @since 11
 * @version 1.0
 */
struct RawFile64;

/**
 * @brief 提供对rawfile的访问功能。
 *
 * @since 8
 * @version 1.0
 */
typedef struct RawFile RawFile;

/**
 * @brief 提供对较大rawfile的访问功能。
 *
 * @since 11
 * @version 1.0
 */
typedef struct RawFile64 RawFile64;

/**
 * @brief 提供rawfile文件描述符信息。RawFileDescriptor是{@link OH_ResourceManager_GetRawFileDescriptor}的输出参数，
 * 涵盖了rawfile文件的文件描述符以及在HAP包中的起始位置和长度。
 *
 * @since 8
 * @version 1.0
 */
typedef struct {
    /**
     * rawfile文件描述符，单位为int。
     */
    int fd;

    /**
     * rawfile在HAP包中的起始位置，单位为long。
     */
    long start;

    /**
     * rawfile在HAP包中的长度，单位为long。
     */
    long length;
} RawFileDescriptor;

/**
 * @brief 提供较大rawfile文件描述符信息。RawFileDescriptor64是{@link OH_ResourceManager_GetRawFileDescriptor64}的输出参数,
 * 涵盖了rawfile文件的文件描述符以及在HAP包中的起始位置和长度。
 *
 * @since 11
 * @version 1.0
 */
typedef struct {
    /**
     * rawfile文件描述符，单位为int。
     */
    int fd;

    /**
     * rawfile在HAP包中的起始位置，单位为int64_t。
     */
    int64_t start;

    /**
     * rawfile在HAP包中的长度，单位为int64_t。
     */
    int64_t length;
} RawFileDescriptor64;

/**
 * @brief 读取rawfile内容，从当前位置读取指定长度的数据。
 *
 * @param rawFile 表示指向{@link RawFile}的指针。
 * @param buf 用于接收读取数据的缓冲区指针。
 * @param length 读取数据的字节长度。
 * @return 返回读取的字节数，如果读取长度超过文件末尾长度或者rawfile为空时，则返回0。
 * @since 8
 * @version 1.0
 */
int OH_ResourceManager_ReadRawFile(const RawFile *rawFile, void *buf, size_t length);

/**
 * @brief 基于指定的偏移量，在rawfile文件内搜索读写数据的位置。
 *
 * @param rawFile 表示指向{@link RawFile}的指针。
 * @param offset 表示指定的偏移量。
 * @param whence 读写位置，有以下场景:
 *     <br>0: 读写位置为文件起始位置加上offset。
 *     <br>1: 读写位置为当前位置加上offset。
 *     <br>2: 读写位置为文件末尾加上offset。
 * @return 如果搜索成功返回0，如果发生错误返回-1。
 * @since 8
 * @version 1.0
 */
int OH_ResourceManager_SeekRawFile(const RawFile *rawFile, long offset, int whence);

/**
 * @brief 获取rawfile长度，单位为long。
 *
 * @param rawFile 表示指向{@link RawFile}的指针。
 * @return 返回rawfile的整体长度，如果rawfile为空时返回0。
 * @since 8
 * @version 1.0
 */
long OH_ResourceManager_GetRawFileSize(RawFile *rawFile);

/**
 * @brief 获取rawfile的剩余长度，单位为long。
 *
 * @param rawFile 表示指向{@link RawFile}的指针。
 * @return 返回rawfile的剩余长度，如果rawfile为空时返回0。
 * @since 11
 * @version 1.0
 */
long OH_ResourceManager_GetRawFileRemainingLength(const RawFile *rawFile);

/**
 * @brief 关闭已打开的{@link RawFile} 以及释放所有相关联的资源。
 *
 * @param rawFile 表示指向{@link RawFile}的指针。
 * @see OH_ResourceManager_OpenRawFile
 * @since 8
 * @version 1.0
 */
void OH_ResourceManager_CloseRawFile(RawFile *rawFile);

/**
 * @brief 获取rawfile当前的偏移量，单位为long。
 *
 * @param rawFile 表示指向{@link RawFile}的指针。
 * @return 返回rawfile当前的偏移量，如果rawfile为空时返回0。
 * @since 8
 * @version 1.0
 */
long OH_ResourceManager_GetRawFileOffset(const RawFile *rawFile);

/**
 * @brief 基于偏移量（单位为long）和文件长度（单位为long）打开rawfile，并获取rawfile文件描述符。打开的文件描述符被用于读取rawfile。
 *
 * @param rawFile 表示指向{@link RawFile}的指针。
 * @param descriptor Indicates the raw file's file descriptor, start position and the length in the HAP.
 * @return 返回true表示打开rawfile文件描述符成功，返回false表示rawfile不允许被访问。
 * @since 8
 * @version 1.0
 * @deprecated since 12
 * @useinstead OH_ResourceManager_GetRawFileDescriptorData
 */
bool OH_ResourceManager_GetRawFileDescriptor(const RawFile *rawFile, RawFileDescriptor &descriptor);

/**
 * @brief 基于偏移量（单位为long）和文件长度（单位为long）打开rawfile，并获取rawfile文件描述符。打开的文件描述符被用于读取rawfile。
 *
 * @param rawFile 表示指向{@link RawFile}的指针。
 * @param descriptor 显示rawfile文件描述符，以及在HAP包中的起始位置和长度。
 * @return 返回true表示打开rawfile文件描述符成功，返回false表示rawfile不允许被访问。
 * @since 12
 * @version 1.0
 */
bool OH_ResourceManager_GetRawFileDescriptorData(const RawFile *rawFile, RawFileDescriptor *descriptor);

/**
 * @brief 关闭rawfile文件描述符。已打开的文件描述符在使用完以后必须释放，防止文件描述符泄露。
 *
 * @param descriptor Indicates the raw file's file descriptor, start position and the length in the HAP.
 * @return 返回true表示关闭文件描述符成功，返回false表示关闭文件描述符失败。
 * @since 8
 * @version 1.0
 * @deprecated since 12
 * @useinstead OH_ResourceManager_ReleaseRawFileDescriptorData
 */
bool OH_ResourceManager_ReleaseRawFileDescriptor(const RawFileDescriptor &descriptor);

/**
 * @brief 关闭rawfile文件描述符。已打开的文件描述符在使用完以后必须释放，防止文件描述符泄露。
 *
 * @param descriptor 包含rawfile文件描述符，以及在HAP包中的起始位置和长度。
 * @return 返回true表示关闭文件描述符成功，返回false表示关闭文件描述符失败。
 * @since 12
 * @version 1.0
 */
bool OH_ResourceManager_ReleaseRawFileDescriptorData(const RawFileDescriptor *descriptor);

/**
 * @brief 读取较大的rawfile文件内容，从当前位置读取指定长度的数据。
 *
 * @param rawFile 表示指向{@link RawFile64}的指针。
 * @param buf 用于接收读取数据的缓冲区指针。
 * @param length 读取数据的字节长度。
 * @return 返回读取的字节数，如果读取长度超过文件末尾长度或者rawfile为空时，则返回0。
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_ReadRawFile64(const RawFile64 *rawFile, void *buf, int64_t length);

/**
 * @brief 基于指定的偏移量，在较大的rawfile文件内搜索读写数据的位置。
 *
 * @param rawFile 表示指向{@link RawFile64}的指针。
 * @param offset 表示指定的偏移量。
 * @param whence 读写位置，有以下场景:
 *     <br>0: 读写位置为文件起始位置加上offset。
 *     <br>1: 读写位置为当前位置加上offset。
 *     <br>2: 读写位置为文件末尾加上offset。
 * @return 如果搜索成功返回0，如果发生错误返回-1。
 * @since 11
 * @version 1.0
 */
int OH_ResourceManager_SeekRawFile64(const RawFile64 *rawFile, int64_t offset, int whence);

/**
 * @brief 获取较大rawfile文件的长度，单位为int64_t。
 *
 * @param rawFile 表示指向{@link RawFile64}的指针。
 * @return 返回rawfile的整体长度，如果rawfile为空时返回0。
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_GetRawFileSize64(RawFile64 *rawFile);

/**
 * @brief 获取较大rawfile的剩余长度，单位为int64_t。
 *
 * @param rawFile 表示指向{@link RawFile64}的指针。
 * @return 返回rawfile的剩余长度，如果rawfile为空时返回0。
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_GetRawFileRemainingLength64(const RawFile64 *rawFile);

/**
 * @brief 关闭已打开的{@link RawFile64} 以及释放所有相关联的资源。
 *
 * @param rawFile 表示指向{@link RawFile64}的指针。
 * @see OH_ResourceManager_OpenRawFile64
 * @since 11
 * @version 1.0
 */
void OH_ResourceManager_CloseRawFile64(RawFile64 *rawFile);

/**
 * @brief 获取较大rawfile文件的偏移量，单位为int64_t。
 *
 * @param rawFile 表示指向{@link RawFile64}的指针。
 * @return 返回rawfile当前的偏移量，如果rawfile为空时返回0。
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_GetRawFileOffset64(const RawFile64 *rawFile);

/**
 * @brief 基于偏移量（单位为int64_t）和文件长度（单位为int64_t）打开较大的rawfile，并获取文件描述符。打开的文件描述符被用于读取rawfile。
 *
 * @param rawFile 表示指向{@link RawFile64}的指针。
 * @param descriptor 显示rawfile文件描述符，以及在HAP包中的起始位置和长度。
 * @return 返回true表示打开rawfile文件描述符成功，返回false表示rawfile不允许被访问。
 * @since 11
 * @version 1.0
 */
bool OH_ResourceManager_GetRawFileDescriptor64(const RawFile64 *rawFile, RawFileDescriptor64 *descriptor);

/**
 * @brief 关闭rawfile文件描述符。已打开的文件描述符在使用完以后必须释放，防止文件描述符泄露。
 *
 * @param descriptor 包含rawfile文件描述符，以及在HAP包中的起始位置和长度。
 * @return 返回true表示关闭文件描述符成功，返回false表示关闭文件描述符失败。
 * @since 11
 * @version 1.0
 */
bool OH_ResourceManager_ReleaseRawFileDescriptor64(const RawFileDescriptor64 *descriptor);

#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_RAW_FILE_H
