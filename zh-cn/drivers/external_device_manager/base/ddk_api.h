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
#ifndef DDK_API_H
#define DDK_API_H

/**
 * @addtogroup Ddk
 * @{
 *
 * @brief 提供Base DDK接口，包括创建、映射、取消映射以及销毁共享内存。
 *
 * @since 12
 */

/**
 * @file ddk_api.h
 *
 * @brief 声明主机侧访问的Base DDK接口。提供共享内存的创建、映射、销毁等功能，支持开发者在驱动程序中高效管理共享内存资源，适用于需要与驱动侧共享数据的场景，有助于简化内存管理、提升数据传输效率。
 *
 * @include <ddk/ddk_api.h>
 * @library libddk_base.z.so
 * @kit DriverDevelopmentKit
 * @syscap SystemCapability.Driver.DDK.Extension
 * @since 12
 */

#include <stdint.h>
#include "ddk_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief 创建共享内存。为了防止资源泄漏，应通过调用{@link OH_DDK_DestroyAshmem}接口来销毁不再需要的共享内存。
 *
 * @param name 指向共享内存名称字符串的指针，该名称用于标识共享内存。name不能为NULL，建议使用具有唯一性的名称以避免冲突。
 * @param size 共享内存对应的缓冲区大小（单位：字节），必须大于0，过大会导致内存占用过高，影响运行性能。
 * @param ashmem 用于输出创建的共享内存对象的指针。
 * @return {@link DDK_SUCCESS} 调用接口成功。共享内存已成功创建并初始化完成。
 *     <br>{@link DDK_INVALID_PARAMETER} 入参name为空指针，size的大小为0或者入参ashmem是空指针。请检查传入的参数值。
 *     <br>{@link DDK_FAILURE} 创建共享内存失败或者创建结构体DDK_Ashmem失败。请检查申请的内存大小和权限。
 * @since 12
 */
DDK_RetCode OH_DDK_CreateAshmem(const uint8_t *name, uint32_t size, DDK_Ashmem **ashmem);

/**
 * @brief 映射创建的共享内存到用户空间。需先调用{@link OH_DDK_CreateAshmem}接口创建共享内存。通过调用{@link OH_DDK_UnmapAshmem}接口取消映射不需要的共享内存。
 *
 * @param ashmem 要映射的共享内存描述符指针。
 * @param ashmemMapType 共享内存的保护权限值，取值请参考Ashmem保护权限的通用定义范围。
 * @return {@link DDK_SUCCESS} 调用接口成功。共享内存已映射到用户空间。
 *     <br>{@link DDK_NULL_PTR} 入参ashmem为空指针。请检查传入的参数值。
 *     <br>{@link DDK_FAILURE} 共享内存的文件描述符无效或未先创建共享内存。请检查共享内存是否已被创建、确保文件描述符未被关闭。
 *     <br>{@link DDK_INVALID_OPERATION} 调用接口映射共享内存失败。可能原因包括映射状态异常或权限不足，请检查共享内存的映射状态和权限后重试。
 * @since 12
 */
DDK_RetCode OH_DDK_MapAshmem(DDK_Ashmem *ashmem, const uint8_t ashmemMapType);

/**
 * @brief 取消映射共享内存。需先调用{@link OH_DDK_MapAshmem}接口映射共享内存。不再访问共享内存时应取消映射，以节省地址空间。
 *
 * @param ashmem 要取消映射的共享内存描述符指针。
 * @return {@link DDK_SUCCESS} 调用接口成功。共享内存已成功从用户空间取消映射。
 *     <br>{@link DDK_NULL_PTR} 入参ashmem为空指针。请检查传入的参数值。
 *     <br>{@link DDK_FAILURE} 共享内存的文件描述符无效或未先执行映射。
 * @since 12
 */
DDK_RetCode OH_DDK_UnmapAshmem(DDK_Ashmem *ashmem);

/**
 * @brief 销毁由{@link OH_DDK_CreateAshmem}创建的共享内存。建议先调用{@link OH_DDK_UnmapAshmem}接口取消映射。共享内存不再使用时应及时销毁以释放系统资源。
 *
 * @param ashmem 要销毁的共享内存描述符指针。
 * @return {@link DDK_SUCCESS} 调用接口成功。共享内存已成功销毁释放。
 *     <br>{@link DDK_NULL_PTR} 入参ashmem为空指针。请检查传入的参数值。
 *     <br>{@link DDK_FAILURE} 共享内存的文件描述符无效。可能原因包括共享内存已被释放或多次销毁，请检查其状态。
 * @since 12
 */
DDK_RetCode OH_DDK_DestroyAshmem(DDK_Ashmem *ashmem);
#ifdef __cplusplus
}
/** @} */
#endif /* __cplusplus */
#endif // DDK_APIS_H