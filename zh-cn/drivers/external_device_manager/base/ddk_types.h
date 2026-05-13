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
#ifndef DDK_TYPES_H

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
#define DDK_TYPES_H
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#ifdef __cplusplus
}
#endif /* __cplusplus */

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

*/
typedef enum {
    /** @error Operation success */
    DDK_SUCCESS = 0,

    /** @error Operation failed */
    DDK_FAILURE = 28600001,

    /** @error Invalid parameter */
    DDK_INVALID_PARAMETER = 28600002,

    /** @error Invalid operation */
    DDK_INVALID_OPERATION = 28600003,

    /** @error Null pointer exception */
    DDK_NULL_PTR = 28600004
} DDK_RetCode;

/**
 * @brief Device memory map created by calling **OH_DDK_CreateAshmem**. A buffer using the device memory map can
 * provide better performance.
 * 
 * @since 12
 */
typedef struct DDK_Ashmem {
    /**
     * File descriptor of the **Ashmem** object.
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
     * from the specified address.
     */
    uint32_t offset;
    /**
     * Length of the buffer. By default, the value is equal to that of **size**, indicating that the entire buffer is
     * used.
     */
    uint32_t bufferLength;
    /**
     * Length of the transferred data.
     */
    uint32_t transferredLength;
} DDK_Ashmem;

/**
 * @brief Device memory map created by calling {@link OH_DDK_CreateAshmem}. A buffer using the device memory map can
 * provide better performance.
 * 
 * @since 12
 */
typedef struct DDK_Ashmem {
    /**
     * File descriptor of the **Ashmem** object.
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
     * from the specified address.
     */
    uint32_t offset;
    /**
     * Length of the buffer. By default, the value is equal to that of **size**, indicating that the entire buffer is
     * used.
     */
    uint32_t bufferLength;
    /**
     * Length of the transferred data.
     */
    uint32_t transferredLength;
} DDK_Ashmem;

/** @} */
#endif // DDK_TYPES_H