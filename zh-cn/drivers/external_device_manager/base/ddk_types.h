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

/**
 * @addtogroup Ddk
 * @{
 *
 * @brief Provides Base DDK types and declares the macros, enums, and\n
 * data structs used by the Base DDK APIs.
 *
 * @since 12
 */

/**
 * @file ddk_types.h
 *
 * @brief 提供基础DDK接口所使用的Base DDK类型，宏定义，枚举值和数据结构。
 *
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
 * @brief 定义通过接口{@link OH_DDK_CreateAshmem}创建的共享内存，共享内存的缓冲区提供更好的性能。
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
    const uint8_t *address;
    /**
     * 缓冲区大小。
     */
    const uint32_t size;
    /**
     * 已使用缓冲区的偏移量。默认值为0，表示没有偏移，缓冲区从指定地址开始。
     */
    uint32_t offset;
    /**
     * 使用的缓冲区长度。默认情况下，该值等于size，表示使用整个缓冲区。
     */
    uint32_t bufferLength;
    /**
     * 已传输数据的长度。
     */
    uint32_t transferredLength;
} DDK_Ashmem;

/**
 * @brief 枚举基本DDK中使用的错误代码。
 *
 * @since 12
 */
typedef enum {
    /**
     * 操作成功
     */
    DDK_SUCCESS = 0,
    /**
     * 操作失败
     */
    DDK_FAILURE = 28600001,
    /**
     * 无效参数
     */
    DDK_INVALID_PARAMETER = 28600002,
    /**
     * 无效操作
     */
    DDK_INVALID_OPERATION = 28600003,
    /**
     * 空指针异常
     */
    DDK_NULL_PTR = 28600004
} DDK_RetCode;
#ifdef __cplusplus
}
/** @} */
#endif /* __cplusplus */
#endif // DDK_TYPES_H