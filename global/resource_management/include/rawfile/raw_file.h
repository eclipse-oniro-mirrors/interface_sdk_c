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
 * @brief Through the `rawfile` module, you can access the `rawfile` directory or resource files in the directory at
 * the native layer, including traversing, opening, reading, seeking, and closing.
 * <br>Traversing the directory: Open the `rawfile` directory, obtain the list of files under it, and iterate through
 * the file names. Multi‑level directory traversal is supported.
 * <br> Reading a file: Open a file, read file content, adjust the offset position of the file, obtain the file size
 * and current offset, and obtain the file descriptor. Files larger than 2 GB are supported.
 *
 * @since 8
 * @version 1.0
 */
/**
 * @file raw_file.h
 *
 * @brief Provides the capabilities to operate on rawfiles, including reading files, obtaining the file length,
 * obtaining the current offset, seeking to a specific position, obtaining the file descriptor, and closing the file
 * descriptor.
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
 * @brief `RawFile64` represents an opened rawfile object, which is used for accessing large files of 2 GB and above.
 * It is obtained through {@link OH_ResourceManager_OpenRawFile64}, and must be closed and released through
 * {@link OH_ResourceManager_CloseRawFile64} after use.
 *
 * @since 11
 * @version 1.0
 */
struct RawFile64;

/**
 * @brief `RawFile` represents an opened rawfile object. It is obtained through {@link OH_ResourceManager_OpenRawFile},
 * and must be closed and released through {@link OH_ResourceManager_CloseRawFile} after use.
 *
 * @since 8
 * @version 1.0
 */
typedef struct RawFile RawFile;

/**
 * @brief `RawFile64` represents an opened rawfile object, which is used for accessing large files of 2 GB and above.
 * It is obtained through {@link OH_ResourceManager_OpenRawFile64}, and must be closed and released through
 * {@link OH_ResourceManager_CloseRawFile64} after use.
 *
 * @since 11
 * @version 1.0
 */
typedef struct RawFile64 RawFile64;

/**
 * @brief Provides rawfile file descriptor information, including the file descriptor, start position within the HAP,
 * and file length.<br>This information is obtained through {@link OH_ResourceManager_GetRawFileDescriptorData}, and
 * must be released through {@link OH_ResourceManager_ReleaseRawFileDescriptorData} after use.
 *
 * @since 8
 * @version 1.0
 */
typedef struct {
    /**
     * File descriptor of the rawfile.
     */
    int fd;

    /**
     * Start position of the rawfile in the HAP, in bytes.
     */
    long start;

    /**
     * Length of the rawfile, in bytes.
     */
    long length;
} RawFileDescriptor;

/**
 * @brief Provides the rawfile file descriptor information, including the file descriptor, start position within the
 * HAP, and file length. Large files larger than 2 GB are supported.<br>This information is obtained through
 * {@link OH_ResourceManager_GetRawFileDescriptor64}, and must be released through
 * {@link OH_ResourceManager_ReleaseRawFileDescriptor64} after use.
 *
 * @since 11
 * @version 1.0
 */
typedef struct {
    /**
     * File descriptor of the rawfile.
     */
    int fd;

    /**
     * Start position of the rawfile in the HAP, in bytes.
     */
    int64_t start;

    /**
     * Length of the rawfile, in bytes.
     */
    int64_t length;
} RawFileDescriptor64;

/**
 * @brief Reads data of the specified length from the current offset position of a rawfile file. The offset position
 * moves forward by the specified length after the read operation. For example, if the current offset position is [0]
 * and the specified length is 10, the offset position after data reading is [10].
 *
 * @param rawFile Input parameter. Pointer to a `RawFile` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile}.
 * @param buf Output parameter. Pointer to the buffer for receiving the read data. The memory is allocated by you and
 *     needs to be freed after use.
 * @param length Input parameter. Expected length of data to be read, in bytes.
 * @return Length of the data read. If the file has been read and no data is available for reading, or if `rawFile` is
 *     `NULL`, `0` is returned.
 * @since 8
 * @version 1.0
 */
int OH_ResourceManager_ReadRawFile(const RawFile *rawFile, void *buf, size_t length);

/**
 * @brief Adjusts the offset position of a rawfile based on the specified offset and offset mode.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile}.
 * @param offset Input parameter. Specified offset. The value is an integer. A positive value indicates backward offset,
 *     and a negative value indicates forward offset. The unit is bytes.
 * @param whence Input parameter. Offset mode. The value can be `0`, `1`, or `2`.
 *     <br>`0`: The offset is calculated from the beginning of the file.
 *     <br>`1`: The offset is calculated from the current position.
 *     <br>`2`: The offset is calculated from the end of the file.
 * @return Seeking result.
 *     <br>**0**: The operation is successful and the file offset is moved to the specified position.
 *     <br>**-1**: The operation fails and the file offset remains unchanged. Possible cause: `rawFile` is `NULL`,
 *     `offset` is out the file range, or `whence` is invalid.
 * @since 8
 * @version 1.0
 */
int OH_ResourceManager_SeekRawFile(const RawFile *rawFile, long offset, int whence);

/**
 * @brief Obtains the length (in bytes) of a rawfile.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile}.
 * @return Length of the rawfile. If `rawFile` is `NULL`, `0` is returned.
 * @since 8
 * @version 1.0
 */
long OH_ResourceManager_GetRawFileSize(RawFile *rawFile);

/**
 * @brief Obtains the remaining length (in bytes) of a rawfile from the current offset position to the end of the file.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile}.
 * @return Remaining length of the rawfile. If `rawFile` is `NULL`, `0` is returned.
 * @since 11
 * @version 1.0
 */
long OH_ResourceManager_GetRawFileRemainingLength(const RawFile *rawFile);

/**
 * @brief Closes a `RawFile` object and releases all associated resources.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile}. After the release, the pointer becomes invalid and cannot be used for
 *     other operations.
 * @see {@link OH_ResourceManager_OpenRawFile}
 * @since 8
 * @version 1.0
 */
void OH_ResourceManager_CloseRawFile(RawFile *rawFile);

/**
 * @brief Obtains the current offset position (in bytes) of a rawfile. This information can be used to track progress
 * during segmented reading, or to confirm the current offset position after seeking.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile}.
 * @return Current offset position of the rawfile. If the `rawFile` is `NULL`, `0` is returned.
 * @since 8
 * @version 1.0
 */
long OH_ResourceManager_GetRawFileOffset(const RawFile *rawFile);

#ifdef __cplusplus
/**
 * @brief Obtains the rawfile descriptor information. After obtaining the file descriptor information, you can call
 * functions such as **pread** to read the rawfile.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile}.
 * @param descriptor Output parameter. Reference to the {@link RawFileDescriptor} object, After use, you must call
 *     {@link OH_ResourceManager_ReleaseRawFileDescriptor} to release the file descriptor, preventing file descriptor
 *     leakage.
 * @return <b>true</b> if the file is opened; returns <b>false</b> if the access to the file is rejected.
 * @since 8
 * @version 1.0
 * @deprecated since 12
 * @useinstead {@link OH_ResourceManager_GetRawFileDescriptorData}
 */
bool OH_ResourceManager_GetRawFileDescriptor(const RawFile *rawFile, RawFileDescriptor &descriptor);
#endif

/**
 * @brief Obtains the rawfile descriptor information. After obtaining the file descriptor information, you can call
 * functions such as **pread** to read the rawfile.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile}.
 * @param descriptor Output parameter. Pointer to the `RawFileDescriptor` object, which is used to return the file
 *     descriptor information. After use, you must call {@link OH_ResourceManager_ReleaseRawFileDescriptorData} to
 *     release the file descriptor, preventing file descriptor leakage.
 * @return Obtaining result. If the operation is successful, `true` is returned. If the operation fails, `false` is
 *     returned. The possible cause is that `rawFile` or `descriptor` is `NULL` or the access to the rawfile is denied.
 * @since 12
 * @version 1.0
 */
bool OH_ResourceManager_GetRawFileDescriptorData(const RawFile *rawFile, RawFileDescriptor *descriptor);

#ifdef __cplusplus
/**
 * @brief Releases the file descriptor of a rawfile. To prevent file descriptor leakage, you are advised to release a
 * rawfile descriptor immediately after use.
 *
 * @param descriptor Input parameter. Reference to the {@link RawFileDescriptor} object to be released.
 * @return Release result. If the operation is successful, `true` is returned. If the operation fails, `false` is
 *     returned. The possible cause is that `descriptor` is `NULL` or the file descriptor has been released.
 * @since 8
 * @version 1.0
 * @deprecated since 12
 * @useinstead {@link OH_ResourceManager_ReleaseRawFileDescriptorData}
 */
bool OH_ResourceManager_ReleaseRawFileDescriptor(const RawFileDescriptor &descriptor);
#endif

/**
 * @brief Releases rawfile file descriptor resources. After successful release, `fd` in `descriptor` becomes invalid
 * and cannot be used any more.
 *
 * @param descriptor Input parameter. Pointer to the {@link RawFileDescriptor} object to be released.
 * @return Release result. If the operation is successful, `true` is returned. If the operation fails, `false` is
 *     returned. The possible cause is that `descriptor` is `NULL` or the file descriptor has been released.
 * @since 12
 * @version 1.0
 */
bool OH_ResourceManager_ReleaseRawFileDescriptorData(const RawFileDescriptor *descriptor);

/**
 * @brief Reads data of the specified length from the current offset position of a rawfile file. The offset position
 * moves forward by the specified length after the read operation. For example, if the current offset position is [0]
 * and the specified length is 10, the offset position after data reading is [10].
 * <br>Files larger than 2 GB are supported.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile64` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile64}.
 * @param buf Output parameter. Pointer to the buffer for receiving the read data. The memory is allocated by you and
 *     needs to be freed after use.
 * @param length Input parameter. Expected length of data to be read, in bytes.
 * @return Length of the data read. If the file has been read and no data is available for reading, or if `rawFile` is
 *     `NULL`, `0` is returned.
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_ReadRawFile64(const RawFile64 *rawFile, void *buf, int64_t length);

/**
 * @brief Adjusts the offset position of a rawfile based on the specified offset and offset mode. Files larger than 2
 * GB are supported.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile64` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile64}.
 * @param offset Input parameter. Specified offset. The value is an integer. A positive value indicates backward offset,
 *     and a negative value indicates forward offset. The unit is bytes.
 * @param whence Input parameter. Offset mode. The value can be `0`, `1`, or `2`.
 *     <br>`0`: The offset is calculated from the beginning of the file.
 *     <br>`1`: The offset is calculated from the current position.
 *     <br>`2`: The offset is calculated from the end of the file.
 * @return Seeking result.
 *     <br>**0**: The operation is successful and the file offset is moved to the specified position.
 *     <br>**-1**: The operation fails and the file offset remains unchanged. Possible cause: `rawFile` is `NULL`,
 *     `offset` is out the file range, or `whence` is invalid.
 * @since 11
 * @version 1.0
 */
int OH_ResourceManager_SeekRawFile64(const RawFile64 *rawFile, int64_t offset, int whence);

/**
 * @brief Obtains the length (in bytes) of a rawfile. Files larger than 2 GB are supported.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile64` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile64}.
 * @return Length of the rawfile. If `rawFile` is `NULL`, `0` is returned.
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_GetRawFileSize64(RawFile64 *rawFile);

/**
 * @brief Obtains the remaining length (in bytes) of a rawfile from the current offset position to the end of the file.
 * Files larger than 2 GB are supported.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile64` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile64}.
 * @return Remaining length of the rawfile. If `rawFile` is `NULL`, `0` is returned.
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_GetRawFileRemainingLength64(const RawFile64 *rawFile);

/**
 * @brief Closes a `RawFile64` object and releases all associated resources.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile64` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile64}. After the release, the pointer becomes invalid and cannot be used for
 *     other operations.
 * @see {@link OH_ResourceManager_OpenRawFile64}
 * @since 11
 * @version 1.0
 */
void OH_ResourceManager_CloseRawFile64(RawFile64 *rawFile);

/**
 * @brief Obtains the current offset position (in bytes) of a rawfile. This information can be used to track progress
 * during segmented reading, or to confirm the current offset position after seeking.
 * <br>Files larger than 2 GB are supported.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile64` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile64}.
 * @return Current offset position of the rawfile. If the `rawFile` is `NULL`, `0` is returned.
 * @since 11
 * @version 1.0
 */
int64_t OH_ResourceManager_GetRawFileOffset64(const RawFile64 *rawFile);

/**
 * @brief Obtains the rawfile descriptor information. After obtaining the file descriptor information, you can call
 * functions such as **pread** to read the rawfile. Files larger than 2 GB are supported.
 *
 * @param rawFile Input parameter. Pointer to a `RawFile64` object, which is obtained through
 *     {@link OH_ResourceManager_OpenRawFile64}.
 * @param descriptor Output parameter. Pointer to the `RawFileDescriptor64` object, which is used to return the file
 *     descriptor information. After use, you must call {@link OH_ResourceManager_ReleaseRawFileDescriptor64} to
 *     release the file descriptor, preventing file descriptor leakage.
 * @return Obtaining result. If the operation is successful, `true` is returned. If the operation fails, `false` is
 *     returned. The possible cause is that `rawFile` or `descriptor` is `NULL` or the access to the rawfile is denied.
 * @since 11
 * @version 1.0
 */
bool OH_ResourceManager_GetRawFileDescriptor64(const RawFile64 *rawFile, RawFileDescriptor64 *descriptor);

/**
 * @brief Releases rawfile file descriptor resources. After successful release, `fd` in `descriptor` becomes invalid
 * and cannot be used any more.
 *
 * @param descriptor Input parameter. Pointer to the `RawFileDescriptor64` object to be released, which is obtained
 *     through {@link OH_ResourceManager_GetRawFileDescriptor64}.
 * @return Release result. If the operation is successful, `true` is returned. If the operation fails, `false` is
 *     returned. The possible cause is that `descriptor` is `NULL` or the file descriptor has been released.
 * @since 11
 * @version 1.0
 */
bool OH_ResourceManager_ReleaseRawFileDescriptor64(const RawFileDescriptor64 *descriptor);

#ifdef __cplusplus
};
#endif

/** @} */
#endif // GLOBAL_RAW_FILE_H