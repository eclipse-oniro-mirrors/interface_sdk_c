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
#ifndef DDK_TYPES_H
#define DDK_TYPES_H

/**
 * @addtogroup Ddk
 * @{
 *
 * @brief 提供Base DDK接口，包括创建、映射、取消映射以及销毁共享内存。
 *
 * @since 12
 */

/**
 * @file ddk_types.h
 *
 * @brief 提供基础DDK接口所使用的Base DDK类型、枚举值和数据结构。
 *
 * @include <ddk/ddk_types.h>
 * @library libddk_base.z.so
 * @kit DriverDevelopmentKit
 * @syscap SystemCapability.Driver.DDK.Extension
 * @since 12
 */

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief 定义通过接口{@link OH_DDK_CreateAshmem}创建的共享内存。共享内存的缓冲区提供更好的性能，适用于多个模块之间高效共享大数据量、驱动程序与应用程序之间快速数据交换等需要高性能数据共享的场景。
 *
 * @since 12
 */
typedef struct DDK_Ashmem {
    /**
     * 共享内存的文件描述符。
     */
    int32_t ashmemFd;
    /**
     * 缓冲区地址。
     */
    const uint8_t* address;
    /**
     * 缓冲区大小。
     */
    const uint32_t size;
    /**
     * 已使用缓冲区的偏移量。默认值为0，表示没有偏移，缓冲区从address指定地址开始。offset与bufferLength之和不超过size，否则会导致越界访问。
     */
    uint32_t offset;
    /**
     * 使用的缓冲区长度。该值在默认情况下等于size（表示使用整个缓冲区），且offset与bufferLength之和不能大于size，否则会导致越界访问。
     */
    uint32_t bufferLength;
    /**
     * 已传输数据的长度。单位：字节。在数据传输完成后由接口更新。
     */
    uint32_t transferredLength;
} DDK_Ashmem;

/**
 * @brief 枚举基本DDK中使用的错误代码。开发者调用DDK接口后，通过检查这些错误码来判断操作是否成功，并根据具体错误码（如参数无效、空指针异常等）进行相应的错误处理。
 *
 * @since 12
 */
typedef enum {
    /**
     * 接口调用成功完成，操作按预期执行。
     */
    DDK_SUCCESS = 0,
    /**
     * 接口调用过程中发生通用错误，操作无法完成。表示操作因非特定原因失败（如资源不足、内部错误等通用错误场景）。
     */
    DDK_FAILURE = 28600001,
    /**
     * 传入的参数不符合接口要求，如参数值为空、超出范围或类型不匹配。
     */
    DDK_INVALID_PARAMETER = 28600002,
    /**
     * 执行了不支持或禁止的操作，如在错误的设备状态下执行操作。
     */
    DDK_INVALID_OPERATION = 28600003,
    /**
     * 检测到必要的指针参数为NULL，导致无法继续执行操作。
     */
    DDK_NULL_PTR = 28600004
} DDK_RetCode;
#ifdef __cplusplus
}
/** @} */
#endif /* __cplusplus */
#endif // DDK_TYPES_H