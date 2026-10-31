/*
 * Copyright (C) 2024-2026 Huawei Device Co., Ltd.
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
 * @addtogroup OHIPCParcel
 * @{
 *
 * @brief This file provides C APIs for IPC serialization and deserialization, which are used to serialize and
 * deserialize data during IPC communication.
 */
/**
 * @file ipc_cparcel.h
 *
 * @brief This file provides C APIs for IPC serialization and deserialization, which are used to serialize and
 * deserialize data during IPC communication.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @include <IPCKit/ipc_cparcel.h>
 * @library libipc_capi.so
 * @kit IPCKit
 * @since 12
 */

#ifndef CAPI_INCLUDE_IPC_CPARCEL_H
#define CAPI_INCLUDE_IPC_CPARCEL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief IPC serialization object, used for serializing and deserializing data in cross-process communication. This
 * object must be created and destroyed through related functions. You must follow the lifecycle management
 * specifications of the object and properly manage memory resources.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
struct OHIPCParcel;

/**
 * @brief IPC serialization object, used for serializing and deserializing data in cross-process communication. This
 * object must be created and destroyed through related functions. You must follow the lifecycle management
 * specifications of the object and properly manage memory resources.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
typedef struct OHIPCParcel OHIPCParcel;

/**
 * @brief IPC remote proxy object, which is used on the client side to proxy the capabilities of a remote service to
 * implement cross-process communication. This object encapsulates a reference to the remote service and supports
 * sending requests to and receiving responses from the remote service. It is applicable to scenarios that require
 * cross-process service capability invocation, such as cross-process service calls, system service access, and
 * cross-application data sharing. Using this object simplifies the implementation of cross-process communication and
 * improves development efficiency.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
struct OHIPCRemoteProxy;

/**
 * @brief IPC remote proxy object, which is used on the client side to proxy the capabilities of a remote service to
 * implement cross-process communication. This object encapsulates a reference to the remote service and supports
 * sending requests to and receiving responses from the remote service. It is applicable to scenarios that require
 * cross-process service capability invocation, such as cross-process service calls, system service access, and
 * cross-application data sharing. Using this object simplifies the implementation of cross-process communication and
 * improves development efficiency.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
typedef struct OHIPCRemoteProxy OHIPCRemoteProxy;

/**
 * @brief Defines an IPC remote service object. This struct is used to represent a remote service on the server. As the
 * service agent of the server in IPC, it processes requests from the client and implements cross-process communication.
 * **OHIPCRemoteStub** is a core struct provided by IPC Kit. It simplifies the IPC service development process and
 * provides a unified request processing mechanism, helping you quickly implement cross-process communication
 * capabilities.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
struct OHIPCRemoteStub;

/**
 * @brief Defines an IPC remote service object. This struct is used to represent a remote service on the server. As the
 * service agent of the server in IPC, it processes requests from the client and implements cross-process communication.
 * **OHIPCRemoteStub** is a core struct provided by IPC Kit. It simplifies the IPC service development process and
 * provides a unified request processing mechanism, helping you quickly implement cross-process communication
 * capabilities.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @since 12
 */
typedef struct OHIPCRemoteStub OHIPCRemoteStub;

/**
 * @brief Defines the memory allocation function type, which is used to customize the memory allocation policy for IPC
 * communication. This function is commonly used in scenarios that require special memory management, such as shared
 * memory transmission, memory pool management, and limiting memory usage.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param len Length of the memory to be allocated, in bytes. The value must be greater than 0.
 * @return Returns the address of the memory allocated if the operation is successful; returns NULL otherwise.
 * @since 12
 */
typedef void* (*OH_IPC_MemAllocator)(int32_t len);

/**
 * @brief Creates an {@link OHIPCParcel} object for data serialization in IPC communication.
 * When this function is called:
 * - An {@link OHIPCParcel} object is allocated and initialized in memory.
 * - The object is initially empty, and its serializable size must not exceed 204800 bytes.
 * - The returned object pointer can be used for subsequent data read and write operations.
 * - Concurrent access to the same object from multiple threads is not supported.
 * - Typical usage flow: {@link OH_IPCParcel_Create()} ? Data read/write operations ? {@link OH_IPCParcel_Destroy()}
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @return Returns the pointer to the **OHIPCParcel** object created if the operation is successful; returns NULL
 *     otherwise.
 * @since 12
 */
OHIPCParcel* OH_IPCParcel_Create(void);

/**
 * @brief Destroys an {@link OHIPCParcel} object.
 * When this function is called:
 * - The memory buffer occupied by the {@link OHIPCParcel} object is released.
 * - All data in the object is released. The memory occupied by the object itself is released.
 * - The input pointer becomes invalid and should not be used any more.
 * - Before calling this function, ensure that no other thread is using the object.
 * - It is advised to set the pointer to NULL to avoid dangling pointers.
 * - This function and {@link OH_IPCParcel_Create()} must be used in pairs.
 * - Ensure that all required data has been read before destroying the object.
 * - Do not call the destruction function multiple times for the same object.
 * - Only objects created by {@link OH_IPCParcel_Create()} can be destroyed.
 * - The object cannot be accessed after destruction.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object to be destroyed. It cannot be NULL.
 * @since 12
 */
void OH_IPCParcel_Destroy(OHIPCParcel *parcel);

/**
 * @brief Obtains the size of the data contained in an {@link OHIPCParcel} object. This function is commonly used in
 * scenarios such as monitoring data transmission progress, checking whether the IPC serialization size limit has been
 * exceeded, and debugging data read/write processes.
 * When this function is called:
 * - The total number of bytes of data that has been written to the **Parcel** object is calculated.
 * - The total size of the written data is returned.
 * - The read/write position and the data content remain unchanged.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @return Total size of data that has been written to the **Parcel** object, in bytes. If the parameter is invalid, **-
 *     1** is returned.
 * @since 12
 */
int OH_IPCParcel_GetDataSize(const OHIPCParcel *parcel);

/**
 * @brief Obtains the number of bytes that can be written to an {@link OHIPCParcel} object. This function is commonly
 * used in scenarios such as checking whether there is enough space to write more data, preventing write overflow, and
 * performing pre-checks before batch writes.
 * When this function is called:
 * - The size of the remaining writable space in the **Parcel** object is calculated.
 * - The number of writable bytes is returned.
 * - Neither the read/write position nor the data content of the **Parcel** object is changed.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @return Size of the writable bytes, in bytes. If the parameter is invalid, **-1** is returned.
 * @since 12
 */
int OH_IPCParcel_GetWritableBytes(const OHIPCParcel *parcel);

/**
 * @brief Obtains the number of bytes that can be read from an {@link OHIPCParcel} object. This function is commonly
 * used in scenarios such as checking how much data is available to read, reading data cyclically, and debugging the
 * data reading process.
 * When this function is called:
 * - The number of bytes of unread data in the **Parcel** object is calculated.
 * - The number of readable bytes is returned.
 * - Neither the read/write position nor the data content of the **Parcel** object is changed.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @return Size of the readable bytes, in bytes. If the parameter is invalid, **-1** is returned.
 * @since 12
 */
int OH_IPCParcel_GetReadableBytes(const OHIPCParcel *parcel);

/**
 * @brief Obtains the position where data is read in an {@link OHIPCParcel} object. This function is commonly used in
 * scenarios such as recording the read position for later restoration, working with
 * {@link OH_IPCParcel_RewindReadPosition()} to enable repeated reads, and debugging the data reading progress.
 * When this function is called:
 * - The current read position of the **Parcel** object is returned.
 * - The read position and data content remain unchanged.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @return Current read position, in bytes. If the parameter is invalid, **-1** is returned.
 * @since 12
 */
int OH_IPCParcel_GetReadPosition(const OHIPCParcel *parcel);

/**
 * @brief Obtains the position where data is written in an {@link OHIPCParcel} object. This function is commonly used
 * in scenarios such as recording the write position, working with {@link OH_IPCParcel_RewindWritePosition()} to
 * correct write errors, and debugging the data write progress.
 * When this function is called:
 * - The current write position of the **Parcel** object is returned.
 * - The write position and data content remain unchanged.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @return Current write position, in bytes. If the parameter is invalid, **-1** is returned.
 * @since 12
 */
int OH_IPCParcel_GetWritePosition(const OHIPCParcel *parcel);

/**
 * @brief Resets the read position of the {@link OHIPCParcel} object to the specified position. This function is
 * commonly used in scenarios where data needs to be parsed repeatedly.
 * When this function is called:
 * - The read position pointer is moved to the position specified by **newReadPos**, which must be within the range of
 * [0, current data size].
 * - The data already written remains unchanged.
 * - Subsequent read operations start from the new position.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param newReadPos New position to read data, in bytes. The value ranges from 0 to the current data size. If the
 *     value is out of range, the **OH_IPC_CHECK_PARAM_ERROR** error is returned.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 * @since 12
 */
int OH_IPCParcel_RewindReadPosition(OHIPCParcel *parcel, uint32_t newReadPos);

/**
 * @brief Resets the write position of the {@link OHIPCParcel} object to the specified position. This function is
 * usually used in scenarios where data errors need to be corrected after data is written, data needs to be rewritten
 * by segment, or some write operations need to be canceled.
 * When this function is called:
 * - The write position pointer is moved to the position specified by **newWritePos**, which must be within the range of
 * [0, current data size].
 * - Resetting the position may cause some data to be overwritten or invalidated. Use this function with caution.
 * - Subsequent write operations start from the new position.
 * - Resetting the write position does not affect the read position.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param newWritePos New position to write data, in bytes. The value ranges from 0 to the current data size. If the
 *     value is out of range, the **OH_IPC_CHECK_PARAM_ERROR** error is returned.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 * @since 12
 */
int OH_IPCParcel_RewindWritePosition(OHIPCParcel *parcel, uint32_t newWritePos);

/**
 * @brief Writes an int8_t value to an {@link OHIPCParcel} object. Concurrent access to the same object from multiple
 * threads is not supported. The size of written data cannot exceed the total size of IPC serialized data (see
 * {@link OH_IPCParcel_Create()}).
 * - This function and {@link OH_IPCParcel_ReadInt8()} must be used in pairs.
 * - Calling sequence: First you call **OH_IPCParcel_WriteInt8()** to write the data, and then the receiving side calls
 * {@link OH_IPCParcel_ReadInt8()} to read the data.
 * - Incorrect pairing: If the functions are not called in the correct sequence or the read type does not match, the
 * read operation will fail or the data will be incorrect.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value int8_t data value to be written, which is used for IPC data serialization.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 12
 */
int OH_IPCParcel_WriteInt8(OHIPCParcel *parcel, int8_t value);

/**
 * @brief Reads an int8_t value from an {@link OHIPCParcel} object. Concurrent access to the same object from multiple
 * threads is not supported.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value Pointer to store the read int8_t data. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} if the read operation fails.
 * @since 12
 */
int OH_IPCParcel_ReadInt8(const OHIPCParcel *parcel, int8_t *value);

/**
 * @brief Writes an int16_t value to an {@link OHIPCParcel} object. The size of written data cannot exceed the total
 * size of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 * - This function and {@link OH_IPCParcel_ReadInt16()} must be used in pairs.
 * - Calling sequence: First you call **OH_IPCParcel_WriteInt16()** to write the data, and then the receiving side calls
 * {@link OH_IPCParcel_ReadInt16()} to read the data.
 * - Incorrect pairing: If the functions are not called in the correct sequence or the read type does not match, the
 * read operation will fail or the data will be incorrect.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value int16_t data value to be written, which is used for IPC data serialization.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 12
 */
int OH_IPCParcel_WriteInt16(OHIPCParcel *parcel, int16_t value);

/**
 * @brief Reads an int16_t value from an {@link OHIPCParcel} object.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value Pointer to store the read int16_t data. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} if the read operation fails.
 * @since 12
 */
int OH_IPCParcel_ReadInt16(const OHIPCParcel *parcel, int16_t *value);

/**
 * @brief Writes an int32_t value to an {@link OHIPCParcel} object. The size of written data cannot exceed the total
 * size of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 * - This function and {@link OH_IPCParcel_ReadInt32()} must be used in pairs.
 * - Calling sequence: First you call **OH_IPCParcel_WriteInt32()** to write the data, and then the receiving side calls
 * {@link OH_IPCParcel_ReadInt32()} to read the data.
 * - Incorrect pairing: If the functions are not called in the correct sequence or the read type does not match, the
 * read operation will fail or the data will be incorrect.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value int32_t data value to be written, which is used for IPC data serialization.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 12
 */
int OH_IPCParcel_WriteInt32(OHIPCParcel *parcel, int32_t value);

/**
 * @brief Reads an int32_t value from an {@link OHIPCParcel} object.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value Pointer to store the read data. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} if the read operation fails.
 * @since 12
 */
int OH_IPCParcel_ReadInt32(const OHIPCParcel *parcel, int32_t *value);

/**
 * @brief Writes an int64_t value to an {@link OHIPCParcel} object. The size of written data cannot exceed the total
 * size of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value int64_t data value to be written, which is used for IPC data serialization.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 12
 */
int OH_IPCParcel_WriteInt64(OHIPCParcel *parcel, int64_t value);

/**
 * @brief Reads an int64_t value from an {@link OHIPCParcel} object.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value Pointer to store the read data. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} if the read operation fails.
 * @since 12
 */
int OH_IPCParcel_ReadInt64(const OHIPCParcel *parcel, int64_t *value);

/**
 * @brief Writes a uint8_t value to an {@link OHIPCParcel} object. The size of written data cannot exceed the total
 * size of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 *
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value uint8_t data value to be written, which is used for IPC data serialization.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 26.0.0
 */
int OH_IPCParcel_WriteUint8(OHIPCParcel *parcel, uint8_t value);

/**
 * @brief Reads a uint8_t value from an {@link OHIPCParcel} object.
 *
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value Pointer to store the read data. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} if the read operation fails.
 * @since 26.0.0
 */
int OH_IPCParcel_ReadUint8(const OHIPCParcel *parcel, uint8_t *value);

/**
 * @brief Writes a uint16_t value to an {@link OHIPCParcel} object. The size of written data cannot exceed the total
 * size of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 *
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value uint16_t data value to be written, which is used for IPC data serialization.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 26.0.0
 */
int OH_IPCParcel_WriteUint16(OHIPCParcel *parcel, uint16_t value);

/**
 * @brief Reads a uint16_t value from an {@link OHIPCParcel} object.
 *
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value Pointer to store the read data. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} if the read operation fails.
 * @since 26.0.0
 */
int OH_IPCParcel_ReadUint16(const OHIPCParcel *parcel, uint16_t *value);

/**
 * @brief Writes a uint32_t value to an {@link OHIPCParcel} object. The size of written data cannot exceed the total
 * size of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 *
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value uint32_t data value to be written, which is used for IPC data serialization.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 26.0.0
 */
int OH_IPCParcel_WriteUint32(OHIPCParcel *parcel, uint32_t value);

/**
 * @brief Reads a uint32_t value from an {@link OHIPCParcel} object.
 *
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value Pointer to store the read data. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} if the read operation fails.
 * @since 26.0.0
 */
int OH_IPCParcel_ReadUint32(const OHIPCParcel *parcel, uint32_t *value);

/**
 * @brief Writes a uint64_t value to an {@link OHIPCParcel} object. The size of written data cannot exceed the total
 * size of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 *
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value uint64_t data value to be written, which is used for IPC data serialization.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 26.0.0
 */
int OH_IPCParcel_WriteUint64(OHIPCParcel *parcel, uint64_t value);

/**
 * @brief Reads a uint64_t value from an {@link OHIPCParcel} object.
 *
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value Pointer to store the read data. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} if the read operation fails.
 * @since 26.0.0
 */
int OH_IPCParcel_ReadUint64(const OHIPCParcel *parcel, uint64_t *value);

/**
 * @brief Writes a float value to an {@link OHIPCParcel} object. The size of written data cannot exceed the total size
 * of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value float data value to be written, which is used for IPC data serialization.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 12
 */
int OH_IPCParcel_WriteFloat(OHIPCParcel *parcel, float value);

/**
 * @brief Reads a float value from an {@link OHIPCParcel} object.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value Pointer to store the read data. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} if the read operation fails.
 * @since 12
 */
int OH_IPCParcel_ReadFloat(const OHIPCParcel *parcel, float *value);

/**
 * @brief Writes a double value to an {@link OHIPCParcel} object. The size of written data cannot exceed the total size
 * of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value Double data value to be written, which is used for IPC data serialization.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 12
 */
int OH_IPCParcel_WriteDouble(OHIPCParcel *parcel, double value);

/**
 * @brief Reads a double value from an {@link OHIPCParcel} object.
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param value Pointer to store the read data. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} if the read operation fails.
 * @since 12
 */
int OH_IPCParcel_ReadDouble(const OHIPCParcel *parcel, double *value);

/**
 * @brief Writes a string including a string terminator to an {@link OHIPCParcel} object. The size of written data
 * cannot exceed the total size of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param str Pointer to the string to write, which is used for string data transmission in IPC communication. It
 *     cannot be NULL. The length range is [0, 204800], in bytes (including the null terminator. The actual length is
 *     dynamically affected by the data already written to the parcel and the overhead of the terminator). The length
 *     of the written string is subject to the IPC serialization size limit (see {@link OH_IPCParcel_Create()}). If the
 *     limit is exceeded, the **OH_IPC_PARCEL_WRITE_ERROR** error is returned.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 12
 */
int OH_IPCParcel_WriteString(OHIPCParcel *parcel, const char *str);

/**
 * @brief Reads a string from an {@link OHIPCParcel} object. You can obtain the length of the string from **strlen**.
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @return Returns the address of the string read if the operation is successful; returns NULL if the operation fails
 *     or invalid parameters are found.
 * @since 12
 */
const char* OH_IPCParcel_ReadString(const OHIPCParcel *parcel);

/**
 * @brief Writes data of the specified length from the memory to an {@link OHIPCParcel} object. This function is
 * commonly used in scenarios such as writing binary data, image data, custom structures, and shared memory content.
 * The size of written data cannot exceed the total size of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param buffer Starting address of the memory to be written. This is the starting address of the data buffer to be
 *     written, pointing to the binary data to be transmitted via IPC. It cannot be NULL. The buffer must have
 *     sufficient memory space allocated in advance.
 * @param len Length of the data to be written, in bytes. The value range is [0, available writable bytes of the parcel]
 *     . The size of the written data is subject to the IPC serialization size limit (see {@link OH_IPCParcel_Create()})
 *     . If a negative value is passed, the **OH_IPC_CHECK_PARAM_ERROR** error is returned. If the value exceeds the
 *     available writable bytes, the **OH_IPC_PARCEL_WRITE_ERROR** error is returned.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 12
 */
int OH_IPCParcel_WriteBuffer(OHIPCParcel *parcel, const uint8_t *buffer, int32_t len);

/**
 * @brief Reads memory information of the specified length from an {@link OHIPCParcel} object. This function is
 * commonly used in scenarios such as reading binary data, image data, custom structures, and shared memory content.
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param len Length of memory to be read, in bytes. The value range is [0, the number of remaining readable bytes in
 *     the parcel]. If the value exceeds the readable bytes, NULL is returned.
 * @return Returns the memory address read if the operation is successful; returns NULL if invalid parameters are found
 *     or **len** exceeds the readable length of **parcel**.
 * @since 12
 */
const uint8_t* OH_IPCParcel_ReadBuffer(const OHIPCParcel *parcel, int32_t len);

/**
 * @brief Writes an {@link OHIPCRemoteStub} object to an {@link OHIPCParcel} object. This function is commonly used in
 * scenarios such as passing service objects across processes, implementing remote calls in an IPC server, and sharing
 * service objects. The size of written data cannot exceed the total size of IPC serialized data (see
 * {@link OH_IPCParcel_Create()}).
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param stub Pointer to the **OHIPCRemoteStub** object to write. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 12
 */
int OH_IPCParcel_WriteRemoteStub(OHIPCParcel *parcel, const OHIPCRemoteStub *stub);

/**
 * @brief Reads the {@link OHIPCRemoteStub} object from an {@link OHIPCParcel} object. This function is commonly used
 * in scenarios such as receiving service objects across processes, implementing remote calls in an IPC server, and
 * sharing service objects.
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @return Returns the pointer to the **OHIPCRemoteStub** object read if the operation is successful; returns NULL
 *     otherwise.
 * @since 12
 */
OHIPCRemoteStub* OH_IPCParcel_ReadRemoteStub(const OHIPCParcel *parcel);

/**
 * @brief Writes an {@link OHIPCRemoteProxy} object to an {@link OHIPCParcel} object. This function is commonly used in
 * scenarios such as passing proxy objects across processes, implementing remote calls in an IPC client, and sharing
 * proxy objects. The size of written data cannot exceed the total size of IPC serialized data (see
 * {@link OH_IPCParcel_Create()}).
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param proxy Pointer to the **OHIPCRemoteProxy** object to write. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 12
 */
int OH_IPCParcel_WriteRemoteProxy(OHIPCParcel *parcel, const OHIPCRemoteProxy *proxy);

/**
 * @brief Reads the {@link OHIPCRemoteProxy} object from an {@link OHIPCParcel} object. This function is commonly used
 * in scenarios such as receiving proxy objects across processes, implementing remote calls in an IPC client, and
 * sharing proxy objects.
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @return Returns the pointer to the **OHIPCRemoteProxy** object created if the operation is successful; returns NULL
 *     otherwise.
 * @since 12
 */
OHIPCRemoteProxy* OH_IPCParcel_ReadRemoteProxy(const OHIPCParcel *parcel);

/**
 * @brief Writes a file descriptor to an {@link OHIPCParcel} object. This function is commonly used in scenarios such
 * as passing file handles across processes, shared memory file descriptors, and pipe file descriptors. The size of
 * written data cannot exceed the total size of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param fd File descriptor to write. The value must be a valid file descriptor, which is a non-negative integer. If a
 *     negative value or an invalid file descriptor is passed, the **OH_IPC_CHECK_PARAM_ERROR** error is returned.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 12
 */
int OH_IPCParcel_WriteFileDescriptor(OHIPCParcel *parcel, int32_t fd);

/**
 * @brief Reads a file descriptor from an {@link OHIPCParcel} object. This function is commonly used in scenarios such
 * as receiving file handles across processes, shared memory file descriptors, and pipe file descriptors. Concurrent
 * access to the same object from multiple threads is not supported.
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param fd Pointer to store the read file descriptor. It cannot be NULL. Before reading, ensure that valid file
 *     descriptor data has been written to the parcel.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} if the read operation fails.
 * @since 12
 */
int OH_IPCParcel_ReadFileDescriptor(const OHIPCParcel *parcel, int32_t *fd);

/**
 * @brief Appends data to an {@link OHIPCParcel} object. This function is commonly used in scenarios such as merging
 * data from multiple parcels, packet assembly, and merging data written in segments. The size of appended data cannot
 * exceed the total size of IPC serialized data (see {@link OH_IPCParcel_Create()}).
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param data Pointer to source **OHIPCParcel** object. It cannot be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the concatenation fails.
 * @since 12
 */
int OH_IPCParcel_Append(OHIPCParcel *parcel, const OHIPCParcel *data);

/**
 * @brief Writes an interface token to an {@link OHIPCParcel} object for interface identity verification. This function
 * is commonly used in security verification scenarios in IPC communication, such as preventing malicious processes
 * from sending forged requests, ensuring that messages are sent to the correct service API, and distinguishing
 * different API calls in multi-API services. Concurrent access to the same object from multiple threads is not
 * supported. The size of written data cannot exceed the total size of IPC serialized data (see
 * {@link OH_IPCParcel_Create()}).
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param token Pointer to the interface token to write. It cannot be NULL. The interface token is usually the fully
 *     qualified name or a unique identifier string of an interface, and is used for interface identity verification.
 *     The string length range is (0, remaining writable space of the parcel]. The unit is bytes. If the limit is
 *     exceeded, the **OH_IPC_PARCEL_WRITE_ERROR** error is returned.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_WRITE_ERROR} if the write operation fails.
 * @since 12
 */
int OH_IPCParcel_WriteInterfaceToken(OHIPCParcel *parcel, const char *token);

/**
 * @brief Reads an interface token from an {@link OHIPCParcel} object for interface identity verification.
 * <br>When this function is called:
 *
 * @syscap SystemCapability.Communication.IPC.Core
 * @param parcel Pointer to the **OHIPCParcel** object. It cannot be NULL.
 * @param token Memory address for storing the interface token information. The memory is allocated using the user-
 *     provided allocator, and must be explicitly freed by the user after use. It must not be NULL. If an error code is
 *     returned, you still need to check whether the memory is empty and release the memory. Otherwise, memory leaks
 *     may occur.
 * @param len Pointer to store the length of the read interface token (including the null terminator). The unit is
 *     bytes. It must not be NULL.
 * @param allocator Memory allocator specified by the user for allocating the memory for **token**. It must not be NULL.
 * @return Returns {@link OH_IPC_ErrorCode#OH_IPC_SUCCESS} if the operation is successful.
 *     <br>Returns {@link OH_IPC_ErrorCode#OH_IPC_CHECK_PARAM_ERROR} if invalid parameters are found. Returns
 *     {@link OH_IPC_ErrorCode#OH_IPC_PARCEL_READ_ERROR} if the read operation fails.
 * @since 12
 */
int OH_IPCParcel_ReadInterfaceToken(const OHIPCParcel *parcel, char **token, int32_t *len,
    OH_IPC_MemAllocator allocator);

#ifdef __cplusplus
}
#endif

/** @} */
#endif