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
 * @brief 通过rawfile模块，开发者可以在Native层访问rawfile目录或目录下的资源文件，包括遍历、打开、读取、定位和关闭等。
 * <br> 遍历目录：打开rawfile目录，获取目录下的文件列表，遍历文件名称，支持多级目录遍历。
 * <br> 读取文件：打开rawfile文件，读取文件内容，调整文件偏移位置，获取文件大小和当前偏移量，获取文件描述符，支持2GB以上的大文件。
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file raw_file.h
 *
 * @brief 提供操作rawfile文件的能力，包括读取文件、获取文件长度、获取偏移位置、调整偏移位置、获取文件描述符，以及关闭文件描述符等。
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
 * @brief RawFile64表示一个已打开的rawfile对象，用于访问2GB及以上的大文件。通过{@link OH_ResourceManager_OpenRawFile64}函数获取，使用完后须调用
 * {@link OH_ResourceManager_CloseRawFile64}关闭并释放。
 *
 * @since 11
 * @version 1.0
 */
struct RawFile64;

/**
 * @brief RawFile表示一个已打开的rawfile对象。通过{@link OH_ResourceManager_OpenRawFile}函数获取，使用完后须调用
 * {@link OH_ResourceManager_CloseRawFile}关闭并释放。
 *
 * @since 8
 * @version 1.0
 */
typedef struct RawFile RawFile;

/**
 * @brief RawFile64表示一个已打开的rawfile对象，用于访问2GB及以上的大文件。通过{@link OH_ResourceManager_OpenRawFile64}函数获取，使用完后须调用
 * {@link OH_ResourceManager_CloseRawFile64}关闭并释放。
 *
 * @since 11
 * @version 1.0
 */
typedef struct RawFile64 RawFile64;

/**
 * @brief 提供rawfile文件描述符信息，包含rawfile的文件描述符、在HAP包中的起始位置和文件长度。<br>通过{@link OH_ResourceManager_GetRawFileDescriptorData}获取，
 * 使用完后须调用{@link OH_ResourceManager_ReleaseRawFileDescriptorData}释放文件描述符资源。
 *
 * @since 8
 * @version 1.0
 */
typedef struct {
    /**
     * rawfile文件描述符。
     */
    int fd;

    /**
     * rawfile文件在HAP包中的起始位置，单位为Byte。
     */
    long start;

    /**
     * rawfile文件的长度，单位为Byte。
     */
    long length;
} RawFileDescriptor;

/**
 * @brief 提供rawfile文件描述符信息，包含rawfile的文件描述符、在HAP包中的起始位置和文件长度。支持2GB以上的大文件。<br>通过
 * {@link OH_ResourceManager_GetRawFileDescriptor64}获取，使用完后须调用{@link OH_ResourceManager_ReleaseRawFileDescriptor64}
 * 释放文件描述符资源。
 *
 * @since 11
 * @version 1.0
 */
typedef struct {
    /**
     * rawfile文件描述符。
     */
    int fd;

    /**
     * rawfile文件在HAP包中的起始位置，单位为Byte。
     */
    int64_t start;

    /**
     * rawfile文件的长度，单位为Byte。
     */
    int64_t length;
} RawFileDescriptor64;

/**
 * @brief 从rawfile文件当前偏移位置读取指定长度的数据，同时偏移位置会跟随指定长度向后移动。如当前偏移位置为[0]，指定长度为10，读取数据后迁移位置为[10]。
 *
 * @param rawFile 输入参数。指向RawFile对象的指针，通过{@link OH_ResourceManager_OpenRawFile}获取。
 * @param buf 输出参数。指向接收读取数据的缓冲区的指针，由开发者自行分配内存，使用完后需自行释放。
 * @param length 输入参数。期望读取的数据长度，单位为Byte。
 * @return 返回已读取的数据长度。若文件已读完，无数据可读时，或rawFile为NULL，返回0。
 * @since 8
 * @version 1.0
 */
int OH_ResourceManager_ReadRawFile(const RawFile *rawFile, void *buf, size_t length);

/**
 * @brief 基于指定的偏移量和偏移方式，调整rawfile文件的偏移位置。
 *
 * @param rawFile 输入参数。指向RawFile对象的指针，通过{@link OH_ResourceManager_OpenRawFile}获取。
 * @param offset 输入参数。指定的偏移量，取值为整数，正数表示向后偏移，负数表示向前偏移。单位为Byte。
 * @param whence 输入参数。偏移方式，取值包括0、1、2。
 *     <br>0：从文件开头计算偏移位置。
 *     <br>1：从当前位置计算偏移位置。
 *     <br>2：从文件末尾计算偏移位置。
 * @return 返回定位结果。
 *     <br>返回0，表示成功，文件的偏移位置移动到指定位置。
 *     <br>返回-1，表示失败，文件的偏移位置不变。可能原因是rawFile为NULL、offset超出文件范围或whence值无效。
 * @since 8
 * @version 1.0
 */
int OH_ResourceManager_SeekRawFile(const RawFile *rawFile, long offset, int whence);

/**
 * @brief 获取rawfile文件长度，单位为Byte。
 *
 * @param rawFile 输入参数。指向RawFile对象的指针，通过{@link OH_ResourceManager_OpenRawFile}获取。
 * @return 返回rawfile文件长度。若rawFile为NULL，则返回0。
 * @since 8
 * @version 1.0
 */
long OH_ResourceManager_GetRawFileSize(RawFile *rawFile);

/**
 * @brief 获取rawfile文件从当前偏移位置到文件末尾的剩余长度，单位为Byte。
 *
 * @param rawFile 输入参数。指向RawFile对象的指针，通过{@link OH_ResourceManager_OpenRawFile}获取。
 * @return 返回rawfile文件的剩余长度。若rawFile为NULL，则返回0。
 * @since 11
 * @version 1.0
 */
long OH_ResourceManager_GetRawFileRemainingLength(const RawFile *rawFile);

/**
 * @brief 关闭已打开的RawFile对象并释放所有相关资源。
 *
 * @param rawFile 输入参数。指向RawFile对象的指针，通过{@link OH_ResourceManager_OpenRawFile}获取。释放后该指针失效，不可再用于其他操作。
 * @see {@link OH_ResourceManager_OpenRawFile}
 * @since 8
 * @version 1.0
 */
void OH_ResourceManager_CloseRawFile(RawFile *rawFile);

/**
 * @brief 获取rawfile文件当前的偏移位置，单位为Byte。可用于在分段读取过程中跟踪进度，或在调整偏移位置后确认当前偏移位置。
 *
 * @param rawFile 输入参数。指向RawFile对象的指针，通过{@link OH_ResourceManager_OpenRawFile}获取。
 * @return 返回rawfile当前的偏移位置，若rawFile为NULL，则返回0。
 * @since 8
 * @version 1.0
 */
long OH_ResourceManager_GetRawFileOffset(const RawFile *rawFile);

#ifdef __cplusplus
/**
 * @brief 获取rawfile文件描述符信息。获取文件描述符信息后，开发者可调用pread等函数读取rawfile文件。
 *
 * @param rawFile 输入参数。指向RawFile对象的指针，通过{@link OH_ResourceManager_OpenRawFile}获取。
 * @param descriptor 输出参数。指向{@link RawFileDescriptor}对象的引用，用于返回文件描述符信息。使用完后须调用
 *     {@link OH_ResourceManager_ReleaseRawFileDescriptor}释放文件描述符，防止文件描述符泄露。
 * @return 返回获取结果。true表示获取成功。false表示获取失败，可能原因是rawFile为NULL、descriptor为NULL或rawfile文件访问被拒绝。
 * @since 8
 * @version 1.0
 * @deprecated since 12
 * @useinstead {@link OH_ResourceManager_GetRawFileDescriptorData}
 */
bool OH_ResourceManager_GetRawFileDescriptor(const RawFile *rawFile, RawFileDescriptor &descriptor);
#endif

/**
 * @brief 获取rawfile文件描述符信息。获取文件描述符信息后，开发者可调用pread等函数读取rawfile文件。
 *
 * @param rawFile 输入参数。指向RawFile对象的指针，通过{@link OH_ResourceManager_OpenRawFile}获取。
 * @param descriptor 输出参数。指向RawFileDescriptor对象的指针，用于返回文件描述符信息。使用完后须调用
 *     {@link OH_ResourceManager_ReleaseRawFileDescriptorData}释放文件描述符，防止文件描述符泄露。
 * @return 返回获取结果。true表示获取成功。false表示获取失败，可能原因是rawFile为NULL、descriptor为NULL或rawfile文件访问被拒绝。
 * @since 12
 * @version 1.0
 */
bool OH_ResourceManager_GetRawFileDescriptorData(const RawFile *rawFile, RawFileDescriptor *descriptor);

#ifdef __cplusplus
/**
 * @brief 释放rawfile文件描述符资源。释放成功后，descriptor中的fd失效，不可再使用。
 *
 * @param descriptor 指向要释放的{@link RawFileDescriptor}对象的引用。
 * @return 返回释放结果。true表示释放成功，false表示释放失败，可能原因是descriptor为NULL或文件描述符已释放。
 * @since 8
 * @version 1.0
 * @deprecated since 12
 * @useinstead {@link OH_ResourceManager_ReleaseRawFileDescriptorData}
 */
bool OH_ResourceManager_ReleaseRawFileDescriptor(const RawFileDescriptor &descriptor);
#endif

/**
 * @brief 释放rawfile文件描述符资源。释放成功后，descriptor中的fd失效，不可再使用。
 *
 * @param descriptor 输入参数。指向要释放的{@link RawFileDescriptor}对象的指针。
 * @return 返回释放结果。true表示释放成功，false表示释放失败，可能原因是descriptor为NULL或文件描述符已释放。
 * @since 12
 * @version 1.0
 */
bool OH_ResourceManager_ReleaseRawFileDescriptorData(const RawFileDescriptor *descriptor);

/**
 * @brief 从rawfile文件当前偏移位置读取指定长度的数据，同时偏移位置会跟随指定长度向后移动。如当前偏移位置为[0]，指定长度为10，读取数据后迁移位置为[10]。
 * <br>支持2GB以上的大文件。
 *
 * @param rawFile 输入参数。指向RawFile64对象的指针，通过{@link OH_ResourceManager_OpenRawFile64}获取。
 * @param buf 输出参数。指向接收读取数据的缓冲区的指针，由开发者自行分配内存，使用完后需自行释放。
 * @param length 输入参数。期望读取的数据长度，单位为Byte。
 * @return 返回已读取的数据长度。若文件已读完，无数据可读时，或rawFile为NULL，返回0。
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_ReadRawFile64(const RawFile64 *rawFile, void *buf, int64_t length);

/**
 * @brief 基于指定的偏移量和偏移方式，调整rawfile文件的偏移位置。支持2GB以上的大文件。
 *
 * @param rawFile 输入参数。指向RawFile64对象的指针，通过{@link OH_ResourceManager_OpenRawFile64}获取。
 * @param offset 输入参数。指定的偏移量，取值为整数，正数表示向后偏移，负数表示向前偏移。单位为Byte。
 * @param whence 输入参数。偏移方式，取值包括0、1、2。
 *     <br>0：从文件开头计算偏移位置。
 *     <br>1：从当前位置计算偏移位置。
 *     <br>2：从文件末尾计算偏移位置。
 * @return 返回定位结果。
 *     <br>返回0，表示成功，文件的偏移位置移动到指定位置。
 *     <br>返回-1，表示失败，文件的偏移位置不变。可能原因是rawFile为NULL、offset超出文件范围或whence值无效。
 * @since 11
 * @version 1.0
 */
int OH_ResourceManager_SeekRawFile64(const RawFile64 *rawFile, int64_t offset, int whence);

/**
 * @brief 获取rawfile文件长度，单位为Byte。支持2GB以上的大文件。
 *
 * @param rawFile 输入参数。指向RawFile64对象的指针，通过{@link OH_ResourceManager_OpenRawFile64}获取。
 * @return 返回rawfile文件长度。若rawFile为NULL，则返回0。
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_GetRawFileSize64(RawFile64 *rawFile);

/**
 * @brief 获取rawfile文件从当前偏移位置到文件末尾的剩余长度，单位为Byte。支持2GB以上的大文件。
 *
 * @param rawFile 输入参数。指向RawFile64对象的指针，通过{@link OH_ResourceManager_OpenRawFile64}获取。
 * @return 返回rawfile文件的剩余长度。若rawFile为NULL，则返回0。
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_GetRawFileRemainingLength64(const RawFile64 *rawFile);

/**
 * @brief 关闭已打开的RawFile64对象并释放所有相关资源。
 *
 * @param rawFile 输入参数。指向RawFile64对象的指针，通过{@link OH_ResourceManager_OpenRawFile64}获取。释放后该指针失效，不可再用于其他操作。
 * @see {@link OH_ResourceManager_OpenRawFile64}
 * @since 11
 * @version 1.0
 */
void OH_ResourceManager_CloseRawFile64(RawFile64 *rawFile);

/**
 * @brief 获取rawfile文件当前的偏移位置，单位为Byte。可用于在分段读取过程中跟踪进度，或在调整偏移位置后确认当前偏移位置。
 * <br>支持2GB以上的大文件。
 *
 * @param rawFile 输入参数。指向RawFile64对象的指针，通过{@link OH_ResourceManager_OpenRawFile64}获取。
 * @return 返回rawfile当前的偏移位置，若rawFile为NULL，则返回0。
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_GetRawFileOffset64(const RawFile64 *rawFile);

/**
 * @brief 获取rawfile文件描述符信息。获取文件描述符信息后，开发者可调用pread等函数读取rawfile文件。支持2GB以上的大文件。
 *
 * @param rawFile 输入参数。指向RawFile64对象的指针，通过{@link OH_ResourceManager_OpenRawFile64}获取。
 * @param descriptor 输出参数。指向RawFileDescriptor64对象的指针，用于返回文件描述符信息。使用完后须调用
 *     {@link OH_ResourceManager_ReleaseRawFileDescriptor64}释放文件描述符，防止文件描述符泄露。
 * @return 返回获取结果。true表示获取成功。false表示获取失败，可能原因是rawFile为NULL、descriptor为NULL或rawfile文件访问被拒绝。
 * @since 11
 * @version 1.0
 */
bool OH_ResourceManager_GetRawFileDescriptor64(const RawFile64 *rawFile, RawFileDescriptor64 *descriptor);

/**
 * @brief 释放rawfile文件描述符资源。释放成功后，descriptor中的fd失效，不可再使用。
 *
 * @param descriptor 输入参数。指向要释放的RawFileDescriptor64对象的指针，通过{@link OH_ResourceManager_GetRawFileDescriptor64}获取。
 * @return 返回释放结果。true表示释放成功，false表示释放失败，可能原因是descriptor为NULL或文件描述符已释放。
 * @since 11
 * @version 1.0
 */
bool OH_ResourceManager_ReleaseRawFileDescriptor64(const RawFileDescriptor64 *descriptor);

#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_RAW_FILE_H