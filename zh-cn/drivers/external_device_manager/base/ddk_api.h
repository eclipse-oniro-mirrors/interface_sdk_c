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
 * @brief 声明主机侧访问的Base DDK接口。
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
 * @brief 创建共享内存。为了防止资源泄漏，通过调用{@link OH_DDK_DestroyAshmem}接口来销毁不再需要的共享内存。
 *
 * @param name 指向要创建的共享内存的指针。
 * @param size 共享内存对应的缓冲区大小。
 * @param ashmem 指向创建的共享内存的指针。
 * @return {@link DDK_SUCCESS} 调用接口成功。
 *     {@link DDK_INVALID_PARAMETER} 入参name为空指针，size的大小为0或者入参ashmem是空指针。
 *     {@link DDK_FAILURE} 创建共享内存失败或者创建结构体DDK_Ashmem失败。
 * @since 12
 */
DDK_RetCode OH_DDK_CreateAshmem(const uint8_t *name, uint32_t size, DDK_Ashmem **ashmem);

/**
 * @brief 映射创建的共享内存到用户空间。通过调用{@link OH_DDK_UnmapAshmem}接口取消映射不需要的共享内存。
 *
 * @param ashmem 要映射的共享内存指针。
 * @param ashmemMapType 共享内存的保护权限值。
 * @return {@link DDK_SUCCESS} 调用接口成功。
 *     {@link DDK_NULL_PTR} 入参ashmem为空指针。
 *     {@link DDK_FAILURE} 共享内存的文件描述符无效。
 *     {@link DDK_INVALID_OPERATION} 调用接口MapAshmem失败.
 * @since 12
 */
DDK_RetCode OH_DDK_MapAshmem(DDK_Ashmem *ashmem, const uint8_t ashmemMapType);

/**
 * @brief 取消映射共享内存。
 *
 * @param ashmem 要取消映射的共享内存指针。
 * @return {@link DDK_SUCCESS} 调用接口成功。
 *     {@link DDK_NULL_PTR} 入参ashmem为空指针。
 *     {@link DDK_FAILURE} 共享内存的文件描述符无效。
 * @since 12
 */
DDK_RetCode OH_DDK_UnmapAshmem(DDK_Ashmem *ashmem);

/**
 * @brief 销毁共享内存。
 *
 * @param ashmem 要销毁的共享内存指针。
 * @return {@link DDK_SUCCESS} 调用接口成功。
 *     {@link DDK_NULL_PTR} 入参ashmem为空指针。
 *     {@link DDK_FAILURE} 共享内存的文件描述符无效。
 * @since 12
 */
DDK_RetCode OH_DDK_DestroyAshmem(DDK_Ashmem *ashmem);
#ifdef __cplusplus
}
/** @} */
#endif /* __cplusplus */
#endif // DDK_APIS_H