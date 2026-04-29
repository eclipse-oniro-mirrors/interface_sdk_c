
/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
 * @addtogroup Core
 * @{
 *
 * @brief The Core module provides basic backbone capabilities for media frameworks,
 * including functions such as memory, error codes, and media data structures.
 *
 * @since 9
 */
/**
 * @file native_avmemory.h
 *
 * @brief The file declares the attribute definition of the media struct AVMemory.
 *
 * @kit AVCodecKit
 * @library libnative_media_core.so
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 9
 */

#ifndef NATIVE_AVMEMORY_H
#define NATIVE_AVMEMORY_H
#include <stdint.h>
#include "native_averrors.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Describes a native object for the audio and video memory interface.
 *
 * @since 9
 */
typedef struct OH_AVMemory OH_AVMemory;

/**
 * @brief Creates an OH_AVMemory instance.
 *
 * @param size Size of the created memory, in bytes.
 * @return Pointer to the OH_AVMemory instance created. If the operation fails, NULL is returned.
 *     <br>The instance must be released by calling {@link OH_AVMemory_Destroy} when it is no longer required.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **size** is less than or equal to **0**.
 *     <br>2. The OH_AVMemory instance fails to be created.
 *     <br>3. Memory allocation fails.
 * @deprecated since 11
 * @useinstead OH_AVBuffer_Create
 * @since 10
 */
OH_AVMemory *OH_AVMemory_Create(int32_t size);

/**
 * @brief Obtains the virtual memory address.
 *
 * @param mem Pointer to an OH_AVMemory instance.
 * @return Pointer to the virtual memory address. If the memory is invalid, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **mem** is nullptr.
 *     <br>2. The value of **mem** fails parameter structure verification.
 *     <br>3. The memory in the passed-in value of **mem** is nullptr.
 * @deprecated since 11
 * @useinstead OH_AVBuffer_GetAddr
 * @since 9
 * @version 1.0
 */
uint8_t *OH_AVMemory_GetAddr(struct OH_AVMemory *mem);

/**
 * @brief Obtains the memory length.
 *
 * @param mem Pointer to an OH_AVMemory instance.
 * @return Memory size. If the memory is invalid, **-1** is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **mem** is nullptr.
 *     <br>2. The value of **mem** fails parameter structure verification.
 *     <br>3. The memory in the passed-in value of **mem** is nullptr.
 * @deprecated since 11
 * @useinstead OH_AVBuffer_GetCapacity
 * @since 9
 * @version 1.0
 */
int32_t OH_AVMemory_GetSize(struct OH_AVMemory *mem);

/**
 * @brief Releases an OH_AVMemory instance.
 *
 * @param mem Pointer to an OH_AVMemory instance.
 * @return {@link AV_ERR_OK}: The release operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}:
 *     <br>1. The value of **mem** is nullptr.
 *     <br>2. The value of **mem** fails parameter structure verification.
 *     <br>3. The value of **mem** is not created by the caller.
 * @deprecated since 11
 * @useinstead OH_AVBuffer_Destroy
 * @since 10
 */
OH_AVErrCode OH_AVMemory_Destroy(struct OH_AVMemory *mem);
#ifdef __cplusplus
}
#endif
#endif // NATIVE_AVMEMORY_H
/** @} */