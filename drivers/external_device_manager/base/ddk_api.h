/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @brief Declares the BASE DDK APIs used by the USB host to access USB devices.
 *
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
 * @brief Creates an **Ashmem** object. To prevent resource leakage, call **OH_DDK_DestroyAshmem** to destroy the
 * **Ashmem** object when it is no longer needed.
 *
 * @param name Pointer to the name of the **Ashmem** object.
 * @param size Buffer size of the **Ashmem** object.
 * @param ashmem Pointer to the **Ashmem** object.
 * @return {@link DDK_SUCCESS}: The API call is successful.
 *     {@link DDK_INVALID_PARAMETER}: The input **name** is a null pointer, the value of **size** is 0, or the input
 *     **ashmem** is a null pointer.
 *     {@link DDK_FAILURE}: The attempt to create an **Ashmem** object or the DDK_Ashmem structure fails.
 * @since 12
 */
DDK_RetCode OH_DDK_CreateAshmem(const uint8_t *name, uint32_t size, DDK_Ashmem **ashmem);

/**
 * @brief Maps the created **Ashmem** object to the user space. Call **OH_DDK_UnmapAshmem** to unmap the **Ashmem**
 * object when it is no longer needed.
 *
 * @param ashmem Pointer to the **Ashmem** object.
 * @param ashmemMapType Mapping type for the **Ashmem** object.
 * @return {@link DDK_SUCCESS}: The API call is successful.
 *     {@link DDK_NULL_PTR}: The input **ashmem** is a null pointer.
 *     {@link DDK_FAILURE}: The file descriptor of the **Ashmem** object is invalid.
 *     {@link DDK_INVALID_OPERATION}: The attempt to call MapAshmem fails.
 * @since 12
 */
DDK_RetCode OH_DDK_MapAshmem(DDK_Ashmem *ashmem, const uint8_t ashmemMapType);

/**
 * @brief Unmaps an **Ashmem** object.
 *
 * @param ashmem Pointer to the **Ashmem** object.
 * @return {@link DDK_SUCCESS}: The API call is successful.
 *     {@link DDK_NULL_PTR}: The input **ashmem** is a null pointer.
 *     {@link DDK_FAILURE}: The file descriptor of the **Ashmem** object is invalid.
 * @since 12
 */
DDK_RetCode OH_DDK_UnmapAshmem(DDK_Ashmem *ashmem);

/**
 * @brief Destroys an **Ashmem** object.
 *
 * @param ashmem Pointer to the **Ashmem** object.
 * @return {@link DDK_SUCCESS}: The API call is successful.
 *     {@link DDK_NULL_PTR}: The input **ashmem** is a null pointer.
 *     {@link DDK_FAILURE}: The file descriptor of the **Ashmem** object is invalid.
 * @since 12
 */
DDK_RetCode OH_DDK_DestroyAshmem(DDK_Ashmem *ashmem);
#ifdef __cplusplus
}
/** @} */
#endif /* __cplusplus */
#endif // DDK_APIS_H