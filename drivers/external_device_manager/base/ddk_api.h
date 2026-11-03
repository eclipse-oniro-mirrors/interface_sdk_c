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
 * @brief Provides Base DDK APIs, including creating the shared memory, mapping the shared memory,\n
 * unmapping the shared memory, and destroying the shared memory.
 *
 * @since 12
 */

/**
 * @file ddk_api.h
 *
 * @brief Declares the BASE DDK APIs used by the host and provides APIs for creating, mapping, unmapping, and
 * destroying the shared memory. This module helps you efficiently manage shared memory resources in drivers. It is
 * applicable to scenarios where data needs to be shared with the driver, helping simplify memory management and
 * improve data transmission efficiency.
 *
 * @include <ddk/ddk_api.h>
 * @library libddk_base.z.so
 * @kit DriverDevelopmentKit
 * @syscap SystemCapability.Driver.DDK.Extension
 * @since 12
 */

#ifndef DDK_API_H
#define DDK_API_H

#include <stdint.h>
#include "ddk_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Creates shared memory. To prevent resource leaks, call {@link OH_DDK_DestroyAshmem} to destroy the shared
 * memory when it is no longer needed.
 *
 * @param name Pointer to the name string of the shared memory. The name is used to identify the shared memory. The
 *     value of **name** cannot be null. You are advised to use a unique name to avoid conflicts.
 * @param size Size of the buffer corresponding to the shared memory, in bytes. The value must be greater than 0. If
 *     the value is too large, the memory usage will be too high, affecting the running performance.
 * @param ashmem Pointer to the shared memory object created.
 * @return {@link DDK_SUCCESS}: The API call is successful. The shared memory has been successfully created and
 *     initialized.
 *     <br>{@link DDK_INVALID_PARAMETER}: The input **name** is a null pointer, the value of **size** is **0**, or the
 *     input **ashmem** is a null pointer. Check the input parameter values.
 *     <br>{@link DDK_FAILURE}: The shared memory or the **DDK_Ashmem** struct fails to be created. Check the size of
 *     the allocated memory and related permissions.
 * @since 12
 */
DDK_RetCode OH_DDK_CreateAshmem(const uint8_t *name, uint32_t size, DDK_Ashmem **ashmem);

/**
 * @brief Maps the created shared memory to the user space. Call {@link OH_DDK_CreateAshmem} to create shared memory
 * first. Call {@link OH_DDK_UnmapAshmem} to unmap the shared memory that is no longer needed.
 *
 * @param ashmem Pointer to the descriptor of the shared memory to be mapped.
 * @param ashmemMapType Protection permission value of the shared memory. For details, see the general definition of
 *     the Ashmem protection permission.
 * @return {@link DDK_SUCCESS}: The API call is successful. The shared memory has been mapped to the user space.
 *     <br>{@link DDK_NULL_PTR}: The input **ashmem** is a null pointer. Check the input parameter values.
 *     <br>{@link DDK_FAILURE}: The file descriptor of the shared memory is invalid or the shared memory has not been
 *     created. Check whether the shared memory has been created and ensure that the file descriptor is not closed.
 *     <br>{@link DDK_INVALID_OPERATION}: The shared memory fails to be mapped. The possible causes include abnormal
 *     mapping status or insufficient permissions. Check the mapping status and permissions of the shared memory and
 *     try again.
 * @since 12
 */
DDK_RetCode OH_DDK_MapAshmem(DDK_Ashmem *ashmem, const uint8_t ashmemMapType);

/**
 * @brief Unmaps the shared memory. Call {@link OH_DDK_MapAshmem} to map the shared memory first. Unmap the shared
 * memory when it is no longer accessed to save address space.
 *
 * @param ashmem Pointer to the descriptor of the shared memory to be unmapped.
 * @return {@link DDK_SUCCESS}: The API call is successful. The shared memory has been successfully unmapped from the
 *     user space.
 *     <br>{@link DDK_NULL_PTR}: The input **ashmem** is a null pointer. Check the input parameter values.
 *     <br>{@link DDK_FAILURE}: The file descriptor of the shared memory is invalid or the mapping has not been
 *     performed.
 * @since 12
 */
DDK_RetCode OH_DDK_UnmapAshmem(DDK_Ashmem *ashmem);

/**
 * @brief Destroys the shared memory created by {@link OH_DDK_CreateAshmem}. You are advised to call
 * {@link OH_DDK_UnmapAshmem} to unmap the shared memory first. Destroy the shared memory in a timely manner when it is
 * no longer used to release system resources.
 *
 * @param ashmem Pointer to the descriptor of the shared memory to be destroyed.
 * @return {@link DDK_SUCCESS}: The API call is successful. The shared memory has been successfully destroyed and
 *     released.
 *     <br>{@link DDK_NULL_PTR}: The input ashmem is a null pointer. Check the input parameter values.
 *     <br>{@link DDK_FAILURE}: The file descriptor of the shared memory is invalid. The possible cause is that the
 *     shared memory has been released or destroyed multiple times. Check the status of the shared memory.
 * @since 12
 */
DDK_RetCode OH_DDK_DestroyAshmem(DDK_Ashmem *ashmem);
#ifdef __cplusplus
}
/** @} */
#endif /* __cplusplus */
#endif // DDK_APIS_H