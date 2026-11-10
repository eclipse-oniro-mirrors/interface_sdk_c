/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
 * @addtogroup Ddk
 * @{
 *
 * @brief Provides BASE DDK APIs for creating, mapping, unmapping, and destroying the shared memory.
 *
 * @since 12
 */

/**
 * @file ddk_types.h
 *
 * @brief Provides BASE DDK types and declares enums and data structures required by the BASE DDK APIs.
 *
 * @include <ddk/ddk_types.h>
 * @library libddk_base.z.so
 * @kit DriverDevelopmentKit
 * @syscap SystemCapability.Driver.DDK.Extension
 * @since 12
 */

#ifndef DDK_TYPES_H
#define DDK_TYPES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Defines the shared memory created by calling {@link OH_DDK_CreateAshmem}. The buffer of the shared memory
 * provides better performance and is applicable to scenarios that require high-performance data sharing, such as
 * efficient sharing of a large amount of data between multiple modules and fast data exchange between drivers and apps.
 *
 * @since 12
 */
typedef struct DDK_Ashmem {
    /**
     * File descriptor of the shared memory.
     */
    int32_t ashmemFd;
    /**
     * Buffer address.
     */
    const uint8_t *address;
    /**
     * Buffer size.
     */
    const uint32_t size;
    /**
     * Offset of the used buffer. The default value is **0**, indicating that there is no offset and the buffer starts
     * from the address specified by **address**. The sum of **offset** and **bufferLength** cannot exceed **size**.
     * Otherwise, out-of-bounds access occurs.
     */
    uint32_t offset;
    /**
     * Length of the used buffer. By default, the value is equal to **size** (indicating that the entire buffer is used)
     * . The sum of **offset** and **bufferLength** cannot be greater than **size**. Otherwise, out-of-bounds access
     * occurs.
     */
    uint32_t bufferLength;
    /**
     * Length of the transferred data, in bytes. This value is updated by the API after data transfer is complete.
     */
    uint32_t transferredLength;
} DDK_Ashmem;

/**
 * @brief Enumerates error codes used in the BASE DDK. After calling a DDK API, you can check the return value to
 * determine whether the operation is successful, and handle the error based on the specific error code (for example,
 * invalid parameter or null pointer error).
 *
 * @since 12
 */
typedef enum {
    /**
     * The API call is successful, and the operation is performed as expected.
     */
    DDK_SUCCESS = 0,
    /**
     * A common error occurs during the API call, and the operation cannot be completed. The operation fails due to
     * unspecified reasons (such as common errors like insufficient resources or internal errors).
     */
    DDK_FAILURE = 28600001,
    /**
     * The input parameter does not meet the API requirements. For example, the parameter value is empty, out of range,
     * or does not match the expected type.
     */
    DDK_INVALID_PARAMETER = 28600002,
    /**
     * An unsupported or prohibited operation is performed, for example, an operation is performed when the device is
     * in an incorrect state.
     */
    DDK_INVALID_OPERATION = 28600003,
    /**
     * A mandatory pointer parameter is null, and the operation cannot be performed.
     */
    DDK_NULL_PTR = 28600004
} DDK_RetCode;
#ifdef __cplusplus
}
/** @} */
#endif /* __cplusplus */
#endif // DDK_TYPES_H