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
 * @file native_avbuffer.h
 *
 * @brief The file declares the functions of the media struct AVBuffer.
 *
 * @kit AVCodecKit
 * @library libnative_media_core.so
 * @syscap SystemCapability.Multimedia.Media.Core
 * @since 11
 */

#ifndef NATIVE_AVBUFFER_H
#define NATIVE_AVBUFFER_H
#include <stdint.h>
#include <stdio.h>
#include "native_averrors.h"
#include "native_avformat.h"
#include "native_avbuffer_info.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Describes a native object for the media memory interface.
 *
 * @since 11
 */
typedef struct OH_AVBuffer OH_AVBuffer;
/**
 * @brief Describes a native object for the graphics memory interface.
 *
 * @since 11
 */
typedef struct OH_NativeBuffer OH_NativeBuffer;

/**
 * @brief Creates an OH_AVBuffer instance. You must call {@link OH_AVBuffer_Destroy} to manually release the
 * OH_AVBuffer instance returned.
 *
 * @param capacity Size of the created memory, in bytes.
 * @return Pointer to the OH_AVBuffer instance created. If the operation fails, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **capacity** is less than or equal to **0**.
 *     <br>2. An internal error occurs, or the system does not have resources.
 * @since 11
 */
OH_AVBuffer *OH_AVBuffer_Create(int32_t capacity);

/**
 * @brief Releases an OH_AVBuffer instance. A buffer cannot be destroyed repeatedly.
 *
 * @param buffer Pointer to an OH_AVBuffer instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The value of **buffer** is nullptr or fails format verification.
 *     <br>{@link AV_ERR_OPERATE_NOT_PERMIT}: The input buffer is not created by the user.
 * @since 11
 */
OH_AVErrCode OH_AVBuffer_Destroy(OH_AVBuffer *buffer);

/**
 * @brief Obtains the basic attributes, including **pts**, **size**, **offset**, and **flags**, of a buffer.
 *
 * @param buffer Pointer to an OH_AVBuffer instance.
 * @param attr Pointer to an OH_AVCodecBufferAttr instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The possible causes are as follows:
 *     <br>1. The value of **buffer** or **attr** is nullptr.
 *     <br>2. The value of **buffer** fails parameter structure verification.
 * @since 11
 */
OH_AVErrCode OH_AVBuffer_GetBufferAttr(OH_AVBuffer *buffer, OH_AVCodecBufferAttr *attr);

/**
 * @brief Sets the basic attributes, including **pts**, **size**, **offset**, and **flags**, of a buffer.
 *
 * @param buffer Pointer to an OH_AVBuffer instance.
 * @param attr Pointer to an OH_AVCodecBufferAttr instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     <br>{@link AV_ERR_INVALID_VAL}: The possible causes are as follows:
 *     <br>1. The value of **buffer** or **attr** is nullptr.
 *     <br>2. The value of **buffer** fails parameter structure verification.
 *     <br>3. The memory size or offset of the buffer is invalid.
 * @since 11
 */
OH_AVErrCode OH_AVBuffer_SetBufferAttr(OH_AVBuffer *buffer, const OH_AVCodecBufferAttr *attr);

/**
 * @brief Obtains parameters except basic attributes of a buffer. The information is carried in an OH_AVFormat instance.
 * You must call {@link OH_AVFormat_Destroy} to manually release the OH_AVFormat instance returned.
 *
 * @param buffer Pointer to an OH_AVBuffer instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The possible causes are as follows:
 *     <br>1. The value of **buffer** is nullptr.
 *     <br>2. The meta of the buffer is nullptr.
 *     <br>3. The value of **buffer** fails parameter structure verification.
 * @since 11
 */
OH_AVFormat *OH_AVBuffer_GetParameter(OH_AVBuffer *buffer);

/**
 * @brief Sets parameters except basic attributes of a buffer. The information is carried in an OH_AVFormat instance.
 *
 * @param buffer Pointer to an OH_AVBuffer instance.
 * @param format Pointer to an OH_AVFormat instance.
 * @return {@link AV_ERR_OK}: The operation is successful.
 *     {@link AV_ERR_INVALID_VAL}: The possible causes are as follows:
 *     <br>1. The value of **buffer** or **format** is nullptr.
 *     <br>2. The meta of the buffer is nullptr.
 *     <br>3. The value of **buffer** fails parameter structure verification.
 * @since 11
 */
OH_AVErrCode OH_AVBuffer_SetParameter(OH_AVBuffer *buffer, const OH_AVFormat *format);

/**
 * @brief Obtains the virtual address of a data buffer.
 *
 * @param buffer Pointer to an OH_AVBuffer instance.
 * @return Virtual address. If the operation fails, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **buffer** is a null pointer.
 *     <br>2. The value of **OH_AVBuffer** fails parameter structure verification.
 *     <br>3. An internal error occurs.
 * @since 11
 */
uint8_t *OH_AVBuffer_GetAddr(OH_AVBuffer *buffer);

/**
 * @brief Obtains the capacity (in bytes) of a buffer.
 *
 * @param buffer Pointer to an OH_AVBuffer instance.
 * @return Capacity. If the operation fails, **-1** is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **buffer** is a null pointer.
 *     <br>2. The value of **OH_AVBuffer** fails parameter structure verification.
 *     <br>3. An internal error occurs.
 * @since 11
 */
int32_t OH_AVBuffer_GetCapacity(OH_AVBuffer *buffer);

/**
 * @brief Obtains the pointer to an OH_NativeBuffer instance. You must call {@link OH_NativeBuffer_Unreference} to
 * manually release the OH_NativeBuffer instance returned.
 *
 * @param buffer Pointer to an OH_AVBuffer instance.
 * @return Pointer to the OH_NativeBuffer instance created. If the operation fails, NULL is returned.
 *     <br>The possible causes of an operation failure are as follows:
 *     <br>1. The value of **buffer** is a null pointer.
 *     <br>2. The value of **OH_AVBuffer** fails parameter structure verification.
 *     <br>3. An internal error occurs.
 * @since 11
 */
OH_NativeBuffer *OH_AVBuffer_GetNativeBuffer(OH_AVBuffer *buffer);
#ifdef __cplusplus
}
#endif
#endif // NATIVE_AVBUFFER_H
/** @} */