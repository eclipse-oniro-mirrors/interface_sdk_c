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
 * @brief Provides functions related to rawfiles, including searching for, reading, and closing rawfiles.
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
 * @brief Provides access to large rawfiles.
 *
 * @since 11
 * @version 1.0
 */
struct RawFile64;

/**
 * @brief Provides access to rawfiles.
 *
 * @since 8
 * @version 1.0
 */
typedef struct RawFile RawFile;

/**
 * @brief Provides access to large rawfiles.
 *
 * @since 11
 * @version 1.0
 */
typedef struct RawFile64 RawFile64;

/**
 * @brief Defines the file descriptor of a rawfile. **RawFileDescriptor** is an output parameter of
 * {@link OH_ResourceManager_GetRawFileDescriptor}. It contains the file descriptor of a rawfile and the start position
 * and length of the rawfile in the HAP.
 *
 * @since 8
 * @version 1.0
 */
typedef struct {
    /**
     * File descriptor of the rawfile, in int.
     */
    int fd;

    /**
     * Start position of the rawfile in the HAP, in long.
     */
    long start;

    /**
     * Length of the rawfile in the HAP, in long.
     */
    long length;
} RawFileDescriptor;

/**
 * @brief Defines the file descriptor of a rawfile. **RawFileDescriptor** is an output parameter of
 * {@link OH_ResourceManager_GetRawFileDescriptor}. It contains the file descriptor of a rawfile and the start position
 * and length of the rawfile in the HAP.
 *
 * @since 11
 * @version 1.0
 */
typedef struct {
    /**
     * File descriptor of the rawfile, in int.
     */
    int fd;

    /**
     * Start position of the rawfile in the HAP, in long.
     */
    int64_t start;

    /**
     * Length of the rawfile in the HAP, in long.
     */
    int64_t length;
} RawFileDescriptor64;

/**
 * @brief Reads data of the specified length from the current position in a rawfile.
 *
 * @param rawFile Pointer to {@link RawFile}.
 * @param buf Pointer to the buffer for receiving the read data.
 * @param length Length of the data to read.
 * @return Number of read bytes. If the read length exceeds the length of the file end or rawfile is empty, **0** is
 * returned.
 * @since 8
 * @version 1.0
 */
int OH_ResourceManager_ReadRawFile(const RawFile *rawFile, void *buf, size_t length);

/**
 * @brief Searches for the data read/write position in a rawfile based on the specified offset.
 *
 * @param rawFile Pointer to {@link RawFile}.
 * @param offset Specified offset.
 * @param whence Read/Write position. The options are as follows:
 * **0**: The read/write position is the start position of the file plus the offset.
 * **1**: The read/write position is the current position plus the offset.
 * **2**: The read/write position is the end position of the file plus the offset.
 * @return **0** if the search is successful; **-1** otherwise.
 * @since 8
 * @version 1.0
 */
int OH_ResourceManager_SeekRawFile(const RawFile *rawFile, long offset, int whence);

/**
 * @brief Obtains the length of the rawfile, in long.
 *
 * @param rawFile Pointer to {@link RawFile}.
 * @return Overall length of the rawfile. If the rawfile is empty, **0** is returned.
 * @since 8
 * @version 1.0
 */
long OH_ResourceManager_GetRawFileSize(RawFile *rawFile);

/**
 * @brief Obtains the remaining length of the rawfile, in long.
 *
 * @param rawFile Pointer to {@link RawFile}.
 * @return Remaining length of the rawfile. If the rawfile is empty, **0** is returned.
 * @since 11
 * @version 1.0
 */
long OH_ResourceManager_GetRawFileRemainingLength(const RawFile *rawFile);

/**
 * @brief Closes a {@link RawFile} and releases all associated resources.
 *
 * @param rawFile Pointer to {@link RawFile}.
 * @see OH_ResourceManager_OpenRawFile
 * @since 8
 * @version 1.0
 */
void OH_ResourceManager_CloseRawFile(RawFile *rawFile);

/**
 * @brief Obtains the current offset of a rawfile, in long. Current offset of the rawfile.
 *
 * @param rawFile Pointer to {@link RawFile}.
 * @return Current offset of the rawfile. If the rawfile is empty, **0** is returned.
 * @since 8
 * @version 1.0
 */
long OH_ResourceManager_GetRawFileOffset(const RawFile *rawFile);

/**
 * @brief Opens a rawfile based on the specified offset (in long) and file length (in long) and obtains the file
 * descriptor. The file descriptor obtained can be used to read the file.
 *
 * @param rawFile Pointer to {@link RawFile}.
 * @param descriptor Indicates the raw file's file descriptor, start position and the length in the HAP.
 * @return <b>true</b> if the file is opened; returns <b>false</b> if the access to the file is rejected.
 * @since 8
 * @version 1.0
 * @deprecated since 12
 * @useinstead OH_ResourceManager_GetRawFileDescriptorData
 */
bool OH_ResourceManager_GetRawFileDescriptor(const RawFile *rawFile, RawFileDescriptor &descriptor);

/**
 * @brief Opens a rawfile based on the specified offset (in long) and file length (in long) and obtains the file
 * descriptor. The file descriptor obtained can be used to read the file.
 *
 * @param rawFile Pointer to {@link RawFile}.
 * @param descriptor File descriptor of the rawfile, start position of the rawfile in the HAP, and length of the
 * rawfile.
 * @return <b>true</b> if the file is opened; returns <b>false</b> if the access to the file is rejected.
 * @since 12
 * @version 1.0
 */
bool OH_ResourceManager_GetRawFileDescriptorData(const RawFile *rawFile, RawFileDescriptor *descriptor);

/**
 * @brief Releases the file descriptor of a rawfile. To prevent file descriptor leakage, you are advised to release a
 * rawfile descriptor immediately after use.
 *
 * @param descriptor Indicates the raw file's file descriptor, start position and the length in the HAP.
 * @return Returns <b>true</b> if the file descriptor is released; returns <b>false</b> otherwise.
 * @since 8
 * @version 1.0
 * @deprecated since 12
 * @useinstead OH_ResourceManager_ReleaseRawFileDescriptorData
 */
bool OH_ResourceManager_ReleaseRawFileDescriptor(const RawFileDescriptor &descriptor);

/**
 * @brief Releases the file descriptor of a rawfile. To prevent file descriptor leakage, you are advised to release a
 * rawfile descriptor immediately after use.
 *
 * @param descriptor File descriptor of the rawfile. It contains the file descriptor, start position in the HAP, and
 * file length.
 * @return Returns <b>true</b> if the file descriptor is released; returns <b>false</b> otherwise.
 * @since 12
 * @version 1.0
 */
bool OH_ResourceManager_ReleaseRawFileDescriptorData(const RawFileDescriptor *descriptor);

/**
 * @brief Reads data of the specified length from the current position in a large rawfile.
 *
 * @param rawFile Pointer to {@link RawFile64}.
 * @param buf Pointer to the buffer for receiving the read data.
 * @param length Length of the data to read.
 * @return Number of read bytes. If the read length exceeds the length of the file end or rawfile is empty, **0** is
 * returned.
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_ReadRawFile64(const RawFile64 *rawFile, void *buf, int64_t length);

/**
 * @brief Searches for the data read/write position in a large rawfile based on the specified offset.
 *
 * @param rawFile Pointer to {@link RawFile64}.
 * @param offset Specified offset.
 * @param whence Read/Write position. The options are as follows:
 * **0**: The read/write position is the start position of the file plus the offset.
 * **1**: The read/write position is the current position plus the offset.
 * **2**: The read/write position is the end position of the file plus the offset.
 * @return **0** if the search is successful; **-1** otherwise.
 * @since 11
 * @version 1.0
 */
int OH_ResourceManager_SeekRawFile64(const RawFile64 *rawFile, int64_t offset, int whence);

/**
 * @brief Obtains the length of a large rawfile, in int64_t.
 *
 * @param rawFile Pointer to {@link RawFile64}.
 * @return Overall length of the rawfile. If the rawfile is empty, **0** is returned.
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_GetRawFileSize64(RawFile64 *rawFile);

/**
 * @brief Obtains the remaining length of a large rawfile, in int64_t.
 *
 * @param rawFile Pointer to {@link RawFile64}.
 * @return Remaining length of the rawfile. If the rawfile is empty, **0** is returned.
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_GetRawFileRemainingLength64(const RawFile64 *rawFile);

/**
 * @brief Closes an opened {@link RawFile64} and releases all associated resources.
 *
 * @param rawFile Pointer to {@link RawFile64}.
 * @see OH_ResourceManager_OpenRawFile64
 * @since 11
 * @version 1.0
 */
void OH_ResourceManager_CloseRawFile64(RawFile64 *rawFile);

/**
 * @brief Obtains the offset of a large rawfile, in int64_t.
 *
 * @param rawFile Pointer to {@link RawFile64}.
 * @return Current offset of the rawfile. If the rawfile is empty, **0** is returned.
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_GetRawFileOffset64(const RawFile64 *rawFile);

/**
 * @brief Opens a large rawfile based on the specified offset (in int64_t) and file length (in int64_t) and obtains the
 * file descriptor. The file descriptor obtained can be used to read the file.
 *
 * @param rawFile Pointer to {@link RawFile64}.
 * @param descriptor File descriptor of the rawfile, start position of the rawfile in the HAP, and length of the
 * rawfile.
 * @return <b>true</b> if the file is opened; returns <b>false</b> if the access to the file is rejected.
 * @since 11
 * @version 1.0
 */
bool OH_ResourceManager_GetRawFileDescriptor64(const RawFile64 *rawFile, RawFileDescriptor64 *descriptor);

/**
 * @brief Releases the file descriptor of a rawfile. To prevent file descriptor leakage, you are advised to release a
 * rawfile descriptor immediately after use.
 *
 * @param descriptor File descriptor of the rawfile. It contains the file descriptor, start position in the HAP, and
 * file length.
 * @return Returns <b>true</b> if the file descriptor is released; returns <b>false</b> otherwise.
 * @since 11
 * @version 1.0
 */
bool OH_ResourceManager_ReleaseRawFileDescriptor64(const RawFileDescriptor64 *descriptor);

#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_RAW_FILE_H
